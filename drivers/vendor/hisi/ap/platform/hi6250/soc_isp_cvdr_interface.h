

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_ISP_CVDR_INTERFACE_H__
#define __SOC_ISP_CVDR_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) CVDR
 ****************************************************************************/
/* 寄存器说明：CVDR config register
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_CVDR_CFG_UNION */
#define SOC_ISP_CVDR_CVDR_CVDR_CFG_ADDR(base)         ((base) + (0x0))

/* 寄存器说明：CVDR debug register enable
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_CVDR_DEBUG_EN_UNION */
#define SOC_ISP_CVDR_CVDR_CVDR_DEBUG_EN_ADDR(base)    ((base) + (0x4))

/* 寄存器说明：CVDR debug register
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_CVDR_DEBUG_UNION */
#define SOC_ISP_CVDR_CVDR_CVDR_DEBUG_ADDR(base)       ((base) + (0x8))

/* 寄存器说明：AXI Write QOS/Pressure configuration
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_CVDR_WR_QOS_CFG_UNION */
#define SOC_ISP_CVDR_CVDR_CVDR_WR_QOS_CFG_ADDR(base)  ((base) + (0xC))

/* 寄存器说明：AXI Read QOS/Pressure configuration
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_CVDR_RD_QOS_CFG_UNION */
#define SOC_ISP_CVDR_CVDR_CVDR_RD_QOS_CFG_ADDR(base)  ((base) + (0x10))

/* 寄存器说明：Spare Other RO
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_OTHER_RO_UNION */
#define SOC_ISP_CVDR_CVDR_OTHER_RO_ADDR(base)         ((base) + (0x14))

/* 寄存器说明：Spare Other RW
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_OTHER_RW_UNION */
#define SOC_ISP_CVDR_CVDR_OTHER_RW_ADDR(base)         ((base) + (0x18))

/* 寄存器说明：Video port write Configuration
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_CFG_0_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_0_ADDR(base)      ((base) + (0x1C))

/* 寄存器说明：AXI address Frame start
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_0_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_0_ADDR(base)   ((base) + (0x20))

/* 寄存器说明：AXI line wrap and line stride
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_0_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_0_ADDR(base) ((base) + (0x24))

/* 寄存器说明：Configure the prefetch mechanism and must be aligned with the SMMU configuration.
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_0_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_0_ADDR(base) ((base) + (0x28))

/* 寄存器说明：Video port write Configuration
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_CFG_1_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_1_ADDR(base)      ((base) + (0x2C))

/* 寄存器说明：AXI address Frame start
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_1_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_1_ADDR(base)   ((base) + (0x30))

/* 寄存器说明：AXI line wrap and line stride
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_1_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_1_ADDR(base) ((base) + (0x34))

/* 寄存器说明：Configure the prefetch mechanism and must be aligned with the SMMU configuration.
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_1_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_1_ADDR(base) ((base) + (0x38))

/* 寄存器说明：Video port write Configuration
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_CFG_4_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_4_ADDR(base)      ((base) + (0x5C))

/* 寄存器说明：AXI address Frame start
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_4_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_4_ADDR(base)   ((base) + (0x60))

/* 寄存器说明：AXI line wrap and line stride
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_4_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_4_ADDR(base) ((base) + (0x64))

/* 寄存器说明：Configure the prefetch mechanism and must be aligned with the SMMU configuration.
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_4_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_4_ADDR(base) ((base) + (0x68))

/* 寄存器说明：Video port write Configuration
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_CFG_5_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_5_ADDR(base)      ((base) + (0x6C))

/* 寄存器说明：AXI address Frame start
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_5_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_5_ADDR(base)   ((base) + (0x70))

/* 寄存器说明：AXI line wrap and line stride
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_5_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_5_ADDR(base) ((base) + (0x74))

/* 寄存器说明：Configure the prefetch mechanism and must be aligned with the SMMU configuration.
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_5_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_5_ADDR(base) ((base) + (0x78))

/* 寄存器说明：Video port write Configuration
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_CFG_8_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_8_ADDR(base)      ((base) + (0x9C))

/* 寄存器说明：AXI address Frame start
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_8_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_8_ADDR(base)   ((base) + (0xA0))

/* 寄存器说明：AXI line wrap and line stride
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_8_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_8_ADDR(base) ((base) + (0xA4))

/* 寄存器说明：Configure the prefetch mechanism and must be aligned with the SMMU configuration.
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_8_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_8_ADDR(base) ((base) + (0xA8))

/* 寄存器说明：Video port write Configuration
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_CFG_9_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_9_ADDR(base)      ((base) + (0xAC))

/* 寄存器说明：AXI address Frame start
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_9_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_9_ADDR(base)   ((base) + (0xB0))

/* 寄存器说明：AXI line wrap and line stride
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_9_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_9_ADDR(base) ((base) + (0xB4))

/* 寄存器说明：Configure the prefetch mechanism and must be aligned with the SMMU configuration.
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_9_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_9_ADDR(base) ((base) + (0xB8))

/* 寄存器说明：Video port write Configuration
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_CFG_14_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_14_ADDR(base)     ((base) + (0xFC))

/* 寄存器说明：AXI address Frame start
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_14_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_14_ADDR(base)  ((base) + (0x100))

/* 寄存器说明：AXI line wrap and line stride
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_14_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_14_ADDR(base) ((base) + (0x104))

/* 寄存器说明：Configure the prefetch mechanism and must be aligned with the SMMU configuration.
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_14_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_14_ADDR(base) ((base) + (0x108))

/* 寄存器说明：Video port write Configuration
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_CFG_15_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_15_ADDR(base)     ((base) + (0x10C))

/* 寄存器说明：AXI address Frame start
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_15_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_15_ADDR(base)  ((base) + (0x110))

/* 寄存器说明：AXI line wrap and line stride
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_15_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_15_ADDR(base) ((base) + (0x114))

/* 寄存器说明：Configure the prefetch mechanism and must be aligned with the SMMU configuration.
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_15_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_15_ADDR(base) ((base) + (0x118))

/* 寄存器说明：Video port write Configuration
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_CFG_16_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_16_ADDR(base)     ((base) + (0x11C))

/* 寄存器说明：AXI address Frame start
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_16_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_16_ADDR(base)  ((base) + (0x120))

/* 寄存器说明：AXI line wrap and line stride
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_16_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_16_ADDR(base) ((base) + (0x124))

/* 寄存器说明：Configure the prefetch mechanism and must be aligned with the SMMU configuration.
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_16_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_16_ADDR(base) ((base) + (0x128))

/* 寄存器说明：Video port write Configuration
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_CFG_17_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_17_ADDR(base)     ((base) + (0x12C))

/* 寄存器说明：AXI address Frame start
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_17_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_17_ADDR(base)  ((base) + (0x130))

/* 寄存器说明：AXI line wrap and line stride
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_17_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_17_ADDR(base) ((base) + (0x134))

/* 寄存器说明：Configure the prefetch mechanism and must be aligned with the SMMU configuration.
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_17_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_17_ADDR(base) ((base) + (0x138))

/* 寄存器说明：Video port write Configuration
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_CFG_18_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_18_ADDR(base)     ((base) + (0x13C))

/* 寄存器说明：AXI address Frame start
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_18_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_18_ADDR(base)  ((base) + (0x140))

/* 寄存器说明：AXI line wrap and line stride
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_18_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_18_ADDR(base) ((base) + (0x144))

/* 寄存器说明：Configure the prefetch mechanism and must be aligned with the SMMU configuration.
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_18_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_18_ADDR(base) ((base) + (0x148))

/* 寄存器说明：Video port write Configuration
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_CFG_19_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_19_ADDR(base)     ((base) + (0x14C))

/* 寄存器说明：AXI address Frame start
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_19_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_19_ADDR(base)  ((base) + (0x150))

/* 寄存器说明：AXI line wrap and line stride
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_19_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_19_ADDR(base) ((base) + (0x154))

/* 寄存器说明：Configure the prefetch mechanism and must be aligned with the SMMU configuration.
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_19_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_19_ADDR(base) ((base) + (0x158))

/* 寄存器说明：Video port write Configuration
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_CFG_20_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_20_ADDR(base)     ((base) + (0x15C))

/* 寄存器说明：AXI address Frame start
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_20_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_20_ADDR(base)  ((base) + (0x160))

/* 寄存器说明：AXI line wrap and line stride
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_20_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_20_ADDR(base) ((base) + (0x164))

/* 寄存器说明：Configure the prefetch mechanism and must be aligned with the SMMU configuration.
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_20_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_20_ADDR(base) ((base) + (0x168))

/* 寄存器说明：Video port write Configuration
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_CFG_21_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_21_ADDR(base)     ((base) + (0x16C))

/* 寄存器说明：AXI address Frame start
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_21_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_21_ADDR(base)  ((base) + (0x170))

/* 寄存器说明：AXI line wrap and line stride
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_21_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_21_ADDR(base) ((base) + (0x174))

/* 寄存器说明：Configure the prefetch mechanism and must be aligned with the SMMU configuration.
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_21_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_21_ADDR(base) ((base) + (0x178))

/* 寄存器说明：Video port write Configuration
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_CFG_22_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_22_ADDR(base)     ((base) + (0x17C))

/* 寄存器说明：AXI address Frame start
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_22_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_22_ADDR(base)  ((base) + (0x180))

/* 寄存器说明：AXI line wrap and line stride
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_22_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_22_ADDR(base) ((base) + (0x184))

/* 寄存器说明：Configure the prefetch mechanism and must be aligned with the SMMU configuration.
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_22_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_22_ADDR(base) ((base) + (0x188))

/* 寄存器说明：Video port write Configuration
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_CFG_23_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_23_ADDR(base)     ((base) + (0x18C))

/* 寄存器说明：AXI address Frame start
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_23_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_23_ADDR(base)  ((base) + (0x190))

/* 寄存器说明：AXI line wrap and line stride
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_23_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_23_ADDR(base) ((base) + (0x194))

/* 寄存器说明：Configure the prefetch mechanism and must be aligned with the SMMU configuration.
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_23_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_23_ADDR(base) ((base) + (0x198))

/* 寄存器说明：Video port write Configuration
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_CFG_24_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_24_ADDR(base)     ((base) + (0x19C))

/* 寄存器说明：AXI address Frame start
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_24_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_24_ADDR(base)  ((base) + (0x1A0))

/* 寄存器说明：AXI line wrap and line stride
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_24_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_24_ADDR(base) ((base) + (0x1A4))

/* 寄存器说明：Configure the prefetch mechanism and must be aligned with the SMMU configuration.
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_24_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_24_ADDR(base) ((base) + (0x1A8))

/* 寄存器说明：Video port write Configuration
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_CFG_25_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_25_ADDR(base)     ((base) + (0x1AC))

/* 寄存器说明：AXI address Frame start
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_25_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_25_ADDR(base)  ((base) + (0x1B0))

/* 寄存器说明：AXI line wrap and line stride
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_25_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_25_ADDR(base) ((base) + (0x1B4))

/* 寄存器说明：Configure the prefetch mechanism and must be aligned with the SMMU configuration.
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_25_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_25_ADDR(base) ((base) + (0x1B8))

/* 寄存器说明：Video port write Configuration
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_CFG_26_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_26_ADDR(base)     ((base) + (0x1BC))

/* 寄存器说明：AXI address Frame start
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_26_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_26_ADDR(base)  ((base) + (0x1C0))

/* 寄存器说明：AXI line wrap and line stride
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_26_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_26_ADDR(base) ((base) + (0x1C4))

/* 寄存器说明：Configure the prefetch mechanism and must be aligned with the SMMU configuration.
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_26_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_26_ADDR(base) ((base) + (0x1C8))

/* 寄存器说明：Video port write Configuration
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_CFG_27_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_27_ADDR(base)     ((base) + (0x1CC))

/* 寄存器说明：AXI address Frame start
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_27_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_27_ADDR(base)  ((base) + (0x1D0))

/* 寄存器说明：AXI line wrap and line stride
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_27_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_27_ADDR(base) ((base) + (0x1D4))

/* 寄存器说明：Configure the prefetch mechanism and must be aligned with the SMMU configuration.
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_27_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_27_ADDR(base) ((base) + (0x1D8))

/* 寄存器说明：Video port write Access limiter
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_0_UNION */
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_0_ADDR(base)  ((base) + (0x400))

/* 寄存器说明：Video port write Access limiter
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_1_UNION */
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_1_ADDR(base)  ((base) + (0x404))

/* 寄存器说明：Video port write Access limiter
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_4_UNION */
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_4_ADDR(base)  ((base) + (0x410))

/* 寄存器说明：Video port write Access limiter
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_5_UNION */
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_5_ADDR(base)  ((base) + (0x414))

/* 寄存器说明：Video port write Access limiter
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_8_UNION */
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_8_ADDR(base)  ((base) + (0x420))

/* 寄存器说明：Video port write Access limiter
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_9_UNION */
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_9_ADDR(base)  ((base) + (0x424))

/* 寄存器说明：Video port write Access limiter
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_14_UNION */
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_14_ADDR(base) ((base) + (0x438))

/* 寄存器说明：Video port write Access limiter
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_15_UNION */
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_15_ADDR(base) ((base) + (0x43C))

/* 寄存器说明：Video port write Access limiter
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_16_UNION */
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_16_ADDR(base) ((base) + (0x440))

/* 寄存器说明：Video port write Access limiter
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_17_UNION */
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_17_ADDR(base) ((base) + (0x444))

/* 寄存器说明：Video port write Access limiter
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_18_UNION */
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_18_ADDR(base) ((base) + (0x448))

/* 寄存器说明：Video port write Access limiter
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_19_UNION */
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_19_ADDR(base) ((base) + (0x44C))

/* 寄存器说明：Video port write Access limiter
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_20_UNION */
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_20_ADDR(base) ((base) + (0x450))

/* 寄存器说明：Video port write Access limiter
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_21_UNION */
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_21_ADDR(base) ((base) + (0x454))

/* 寄存器说明：Video port write Access limiter
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_22_UNION */
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_22_ADDR(base) ((base) + (0x458))

/* 寄存器说明：Video port write Access limiter
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_23_UNION */
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_23_ADDR(base) ((base) + (0x45C))

/* 寄存器说明：Video port write Access limiter
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_24_UNION */
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_24_ADDR(base) ((base) + (0x460))

/* 寄存器说明：Video port write Access limiter
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_25_UNION */
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_25_ADDR(base) ((base) + (0x464))

/* 寄存器说明：Video port write Access limiter
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_26_UNION */
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_26_ADDR(base) ((base) + (0x468))

/* 寄存器说明：Video port write Access limiter
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_27_UNION */
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_27_ADDR(base) ((base) + (0x46C))

/* 寄存器说明：Video port read Configuration
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_RD_CFG_0_UNION */
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_0_ADDR(base)      ((base) + (0x500))

/* 寄存器说明：Line width generation
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_RD_LWG_0_UNION */
#define SOC_ISP_CVDR_CVDR_VP_RD_LWG_0_ADDR(base)      ((base) + (0x504))

/* 寄存器说明：Frame height generation
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_RD_FHG_0_UNION */
#define SOC_ISP_CVDR_CVDR_VP_RD_FHG_0_ADDR(base)      ((base) + (0x508))

/* 寄存器说明：AXI frame start
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_RD_AXI_FS_0_UNION */
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_FS_0_ADDR(base)   ((base) + (0x50C))

/* 寄存器说明：Line Wrap definition
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_0_UNION */
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_0_ADDR(base) ((base) + (0x510))

/* 寄存器说明：Configure the prefetch mechanism and must be aligned with the SMMU configuration.
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_0_UNION */
#define SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_0_ADDR(base) ((base) + (0x514))

/* 寄存器说明：Video Port Read DEBUG information
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_RD_DEBUG_0_UNION */
#define SOC_ISP_CVDR_CVDR_VP_RD_DEBUG_0_ADDR(base)    ((base) + (0x51C))

/* 寄存器说明：Video port read Configuration
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_RD_CFG_4_UNION */
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_4_ADDR(base)      ((base) + (0x580))

/* 寄存器说明：Line width generation
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_RD_LWG_4_UNION */
#define SOC_ISP_CVDR_CVDR_VP_RD_LWG_4_ADDR(base)      ((base) + (0x584))

/* 寄存器说明：Frame height generation
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_RD_FHG_4_UNION */
#define SOC_ISP_CVDR_CVDR_VP_RD_FHG_4_ADDR(base)      ((base) + (0x588))

/* 寄存器说明：AXI frame start
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_RD_AXI_FS_4_UNION */
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_FS_4_ADDR(base)   ((base) + (0x58C))

/* 寄存器说明：Line Wrap definition
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_4_UNION */
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_4_ADDR(base) ((base) + (0x590))

/* 寄存器说明：Configure the prefetch mechanism and must be aligned with the SMMU configuration.
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_4_UNION */
#define SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_4_ADDR(base) ((base) + (0x594))

/* 寄存器说明：Video Port Read DEBUG information
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_RD_DEBUG_4_UNION */
#define SOC_ISP_CVDR_CVDR_VP_RD_DEBUG_4_ADDR(base)    ((base) + (0x59C))

/* 寄存器说明：Video port read Configuration
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_RD_CFG_5_UNION */
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_5_ADDR(base)      ((base) + (0x5A0))

/* 寄存器说明：Line width generation
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_RD_LWG_5_UNION */
#define SOC_ISP_CVDR_CVDR_VP_RD_LWG_5_ADDR(base)      ((base) + (0x5A4))

/* 寄存器说明：Frame height generation
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_RD_FHG_5_UNION */
#define SOC_ISP_CVDR_CVDR_VP_RD_FHG_5_ADDR(base)      ((base) + (0x5A8))

/* 寄存器说明：AXI frame start
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_RD_AXI_FS_5_UNION */
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_FS_5_ADDR(base)   ((base) + (0x5AC))

/* 寄存器说明：Line Wrap definition
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_5_UNION */
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_5_ADDR(base) ((base) + (0x5B0))

/* 寄存器说明：Configure the prefetch mechanism and must be aligned with the SMMU configuration.
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_5_UNION */
#define SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_5_ADDR(base) ((base) + (0x5B4))

/* 寄存器说明：Video Port Read DEBUG information
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_RD_DEBUG_5_UNION */
#define SOC_ISP_CVDR_CVDR_VP_RD_DEBUG_5_ADDR(base)    ((base) + (0x5BC))

/* 寄存器说明：Video port read Configuration
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_RD_CFG_6_UNION */
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_6_ADDR(base)      ((base) + (0x5C0))

/* 寄存器说明：Line width generation
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_RD_LWG_6_UNION */
#define SOC_ISP_CVDR_CVDR_VP_RD_LWG_6_ADDR(base)      ((base) + (0x5C4))

/* 寄存器说明：Frame height generation
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_RD_FHG_6_UNION */
#define SOC_ISP_CVDR_CVDR_VP_RD_FHG_6_ADDR(base)      ((base) + (0x5C8))

/* 寄存器说明：AXI frame start
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_RD_AXI_FS_6_UNION */
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_FS_6_ADDR(base)   ((base) + (0x5CC))

/* 寄存器说明：Line Wrap definition
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_6_UNION */
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_6_ADDR(base) ((base) + (0x5D0))

/* 寄存器说明：Configure the prefetch mechanism and must be aligned with the SMMU configuration.
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_6_UNION */
#define SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_6_ADDR(base) ((base) + (0x5D4))

/* 寄存器说明：Video Port Read DEBUG information
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_RD_DEBUG_6_UNION */
#define SOC_ISP_CVDR_CVDR_VP_RD_DEBUG_6_ADDR(base)    ((base) + (0x5DC))

/* 寄存器说明：Video port read Configuration
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_RD_CFG_7_UNION */
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_7_ADDR(base)      ((base) + (0x5E0))

/* 寄存器说明：Line width generation
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_RD_LWG_7_UNION */
#define SOC_ISP_CVDR_CVDR_VP_RD_LWG_7_ADDR(base)      ((base) + (0x5E4))

/* 寄存器说明：Frame height generation
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_RD_FHG_7_UNION */
#define SOC_ISP_CVDR_CVDR_VP_RD_FHG_7_ADDR(base)      ((base) + (0x5E8))

/* 寄存器说明：AXI frame start
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_RD_AXI_FS_7_UNION */
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_FS_7_ADDR(base)   ((base) + (0x5EC))

/* 寄存器说明：Line Wrap definition
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_7_UNION */
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_7_ADDR(base) ((base) + (0x5F0))

/* 寄存器说明：Configure the prefetch mechanism and must be aligned with the SMMU configuration.
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_7_UNION */
#define SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_7_ADDR(base) ((base) + (0x5F4))

/* 寄存器说明：Video Port Read DEBUG information
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_RD_DEBUG_7_UNION */
#define SOC_ISP_CVDR_CVDR_VP_RD_DEBUG_7_ADDR(base)    ((base) + (0x5FC))

/* 寄存器说明：Video port read Configuration
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_RD_CFG_8_UNION */
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_8_ADDR(base)      ((base) + (0x600))

/* 寄存器说明：Line width generation
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_RD_LWG_8_UNION */
#define SOC_ISP_CVDR_CVDR_VP_RD_LWG_8_ADDR(base)      ((base) + (0x604))

/* 寄存器说明：Frame height generation
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_RD_FHG_8_UNION */
#define SOC_ISP_CVDR_CVDR_VP_RD_FHG_8_ADDR(base)      ((base) + (0x608))

/* 寄存器说明：AXI frame start
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_RD_AXI_FS_8_UNION */
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_FS_8_ADDR(base)   ((base) + (0x60C))

/* 寄存器说明：Line Wrap definition
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_8_UNION */
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_8_ADDR(base) ((base) + (0x610))

/* 寄存器说明：Configure the prefetch mechanism and must be aligned with the SMMU configuration.
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_8_UNION */
#define SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_8_ADDR(base) ((base) + (0x614))

/* 寄存器说明：Video Port Read DEBUG information
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_RD_DEBUG_8_UNION */
#define SOC_ISP_CVDR_CVDR_VP_RD_DEBUG_8_ADDR(base)    ((base) + (0x61C))

/* 寄存器说明：Video port read Configuration
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_RD_CFG_9_UNION */
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_9_ADDR(base)      ((base) + (0x620))

/* 寄存器说明：Line width generation
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_RD_LWG_9_UNION */
#define SOC_ISP_CVDR_CVDR_VP_RD_LWG_9_ADDR(base)      ((base) + (0x624))

/* 寄存器说明：Frame height generation
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_RD_FHG_9_UNION */
#define SOC_ISP_CVDR_CVDR_VP_RD_FHG_9_ADDR(base)      ((base) + (0x628))

/* 寄存器说明：AXI frame start
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_RD_AXI_FS_9_UNION */
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_FS_9_ADDR(base)   ((base) + (0x62C))

/* 寄存器说明：Line Wrap definition
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_9_UNION */
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_9_ADDR(base) ((base) + (0x630))

/* 寄存器说明：Configure the prefetch mechanism and must be aligned with the SMMU configuration.
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_9_UNION */
#define SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_9_ADDR(base) ((base) + (0x634))

/* 寄存器说明：Video Port Read DEBUG information
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_RD_DEBUG_9_UNION */
#define SOC_ISP_CVDR_CVDR_VP_RD_DEBUG_9_ADDR(base)    ((base) + (0x63C))

/* 寄存器说明：Video port read Configuration
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_RD_CFG_10_UNION */
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_10_ADDR(base)     ((base) + (0x640))

/* 寄存器说明：Line width generation
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_RD_LWG_10_UNION */
#define SOC_ISP_CVDR_CVDR_VP_RD_LWG_10_ADDR(base)     ((base) + (0x644))

/* 寄存器说明：Frame height generation
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_RD_FHG_10_UNION */
#define SOC_ISP_CVDR_CVDR_VP_RD_FHG_10_ADDR(base)     ((base) + (0x648))

/* 寄存器说明：AXI frame start
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_RD_AXI_FS_10_UNION */
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_FS_10_ADDR(base)  ((base) + (0x64C))

/* 寄存器说明：Line Wrap definition
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_10_UNION */
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_10_ADDR(base) ((base) + (0x650))

/* 寄存器说明：Configure the prefetch mechanism and must be aligned with the SMMU configuration.
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_10_UNION */
#define SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_10_ADDR(base) ((base) + (0x654))

/* 寄存器说明：Video Port Read DEBUG information
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_RD_DEBUG_10_UNION */
#define SOC_ISP_CVDR_CVDR_VP_RD_DEBUG_10_ADDR(base)   ((base) + (0x65C))

/* 寄存器说明：Video port read Access limiter
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_0_UNION */
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_0_ADDR(base)  ((base) + (0x880))

/* 寄存器说明：Video port read Access limiter
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_4_UNION */
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_4_ADDR(base)  ((base) + (0x890))

/* 寄存器说明：Video port read Access limiter
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_5_UNION */
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_5_ADDR(base)  ((base) + (0x894))

/* 寄存器说明：Video port read Access limiter
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_6_UNION */
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_6_ADDR(base)  ((base) + (0x898))

/* 寄存器说明：Video port read Access limiter
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_7_UNION */
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_7_ADDR(base)  ((base) + (0x89C))

/* 寄存器说明：Video port read Access limiter
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_8_UNION */
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_8_ADDR(base)  ((base) + (0x8A0))

/* 寄存器说明：Video port read Access limiter
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_9_UNION */
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_9_ADDR(base)  ((base) + (0x8A4))

/* 寄存器说明：Video port read Access limiter
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_10_UNION */
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_10_ADDR(base) ((base) + (0x8A8))

/* 寄存器说明：Initiator read Configuration
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_NR_RD_CFG_1_UNION */
#define SOC_ISP_CVDR_CVDR_NR_RD_CFG_1_ADDR(base)      ((base) + (0xA10))

/* 寄存器说明：Non-Raster Read DEBUG information
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_NR_RD_DEBUG_1_UNION */
#define SOC_ISP_CVDR_CVDR_NR_RD_DEBUG_1_ADDR(base)    ((base) + (0xA14))

/* 寄存器说明：NR RD Access limiter
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_LIMITER_NR_RD_1_UNION */
#define SOC_ISP_CVDR_CVDR_LIMITER_NR_RD_1_ADDR(base)  ((base) + (0xA18))

/* 寄存器说明：Initiator read Configuration
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_NR_RD_CFG_2_UNION */
#define SOC_ISP_CVDR_CVDR_NR_RD_CFG_2_ADDR(base)      ((base) + (0xA20))

/* 寄存器说明：Non-Raster Read DEBUG information
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_NR_RD_DEBUG_2_UNION */
#define SOC_ISP_CVDR_CVDR_NR_RD_DEBUG_2_ADDR(base)    ((base) + (0xA24))

/* 寄存器说明：NR RD Access limiter
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_LIMITER_NR_RD_2_UNION */
#define SOC_ISP_CVDR_CVDR_LIMITER_NR_RD_2_ADDR(base)  ((base) + (0xA28))

/* 寄存器说明：DEBUG information
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_DEBUG_0_UNION */
#define SOC_ISP_CVDR_CVDR_DEBUG_0_ADDR(base)          ((base) + (0xB00))

/* 寄存器说明：DEBUG information
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_DEBUG_1_UNION */
#define SOC_ISP_CVDR_CVDR_DEBUG_1_ADDR(base)          ((base) + (0xB04))

/* 寄存器说明：DEBUG information
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_DEBUG_2_UNION */
#define SOC_ISP_CVDR_CVDR_DEBUG_2_ADDR(base)          ((base) + (0xB08))

/* 寄存器说明：DEBUG information
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_DEBUG_3_UNION */
#define SOC_ISP_CVDR_CVDR_DEBUG_3_ADDR(base)          ((base) + (0xB0C))

/* 寄存器说明：DEBUG information
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_DEBUG_4_UNION */
#define SOC_ISP_CVDR_CVDR_DEBUG_4_ADDR(base)          ((base) + (0xB10))

/* 寄存器说明：DEBUG information
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_DEBUG_5_UNION */
#define SOC_ISP_CVDR_CVDR_DEBUG_5_ADDR(base)          ((base) + (0xB14))

/* 寄存器说明：DEBUG information
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_DEBUG_6_UNION */
#define SOC_ISP_CVDR_CVDR_DEBUG_6_ADDR(base)          ((base) + (0xB18))

/* 寄存器说明：DEBUG information
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_DEBUG_7_UNION */
#define SOC_ISP_CVDR_CVDR_DEBUG_7_ADDR(base)          ((base) + (0xB1C))

/* 寄存器说明：DEBUG information
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_DEBUG_8_UNION */
#define SOC_ISP_CVDR_CVDR_DEBUG_8_ADDR(base)          ((base) + (0xB20))

/* 寄存器说明：DEBUG information
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_DEBUG_9_UNION */
#define SOC_ISP_CVDR_CVDR_DEBUG_9_ADDR(base)          ((base) + (0xB24))

/* 寄存器说明：DEBUG information
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_DEBUG_10_UNION */
#define SOC_ISP_CVDR_CVDR_DEBUG_10_ADDR(base)         ((base) + (0xB28))

/* 寄存器说明：DEBUG information
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_DEBUG_11_UNION */
#define SOC_ISP_CVDR_CVDR_DEBUG_11_ADDR(base)         ((base) + (0xB2C))

/* 寄存器说明：DEBUG information
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_DEBUG_12_UNION */
#define SOC_ISP_CVDR_CVDR_DEBUG_12_ADDR(base)         ((base) + (0xB30))

/* 寄存器说明：DEBUG information
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_DEBUG_13_UNION */
#define SOC_ISP_CVDR_CVDR_DEBUG_13_ADDR(base)         ((base) + (0xB34))

/* 寄存器说明：DEBUG information
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_DEBUG_14_UNION */
#define SOC_ISP_CVDR_CVDR_DEBUG_14_ADDR(base)         ((base) + (0xB38))

/* 寄存器说明：DEBUG information
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_DEBUG_15_UNION */
#define SOC_ISP_CVDR_CVDR_DEBUG_15_ADDR(base)         ((base) + (0xB3C))

/* 寄存器说明：NR read Master ID
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_AXI_CFG_NR_RD_1_UNION */
#define SOC_ISP_CVDR_CVDR_AXI_CFG_NR_RD_1_ADDR(base)  ((base) + (0xC44))

/* 寄存器说明：NR read Master ID
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_AXI_CFG_NR_RD_2_UNION */
#define SOC_ISP_CVDR_CVDR_AXI_CFG_NR_RD_2_ADDR(base)  ((base) + (0xC48))

/* 寄存器说明：VP write master ID
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_0_UNION */
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_0_ADDR(base)  ((base) + (0xC80))

/* 寄存器说明：VP write master ID
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_1_UNION */
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_1_ADDR(base)  ((base) + (0xC84))

/* 寄存器说明：VP write master ID
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_4_UNION */
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_4_ADDR(base)  ((base) + (0xC90))

/* 寄存器说明：VP write master ID
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_5_UNION */
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_5_ADDR(base)  ((base) + (0xC94))

/* 寄存器说明：VP write master ID
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_8_UNION */
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_8_ADDR(base)  ((base) + (0xCA0))

/* 寄存器说明：VP write master ID
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_9_UNION */
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_9_ADDR(base)  ((base) + (0xCA4))

/* 寄存器说明：VP write master ID
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_14_UNION */
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_14_ADDR(base) ((base) + (0xCB8))

/* 寄存器说明：VP write master ID
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_15_UNION */
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_15_ADDR(base) ((base) + (0xCBC))

/* 寄存器说明：VP write master ID
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_16_UNION */
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_16_ADDR(base) ((base) + (0xCC0))

/* 寄存器说明：VP write master ID
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_17_UNION */
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_17_ADDR(base) ((base) + (0xCC4))

/* 寄存器说明：VP write master ID
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_18_UNION */
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_18_ADDR(base) ((base) + (0xCC8))

/* 寄存器说明：VP write master ID
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_19_UNION */
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_19_ADDR(base) ((base) + (0xCCC))

/* 寄存器说明：VP write master ID
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_20_UNION */
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_20_ADDR(base) ((base) + (0xCD0))

/* 寄存器说明：VP write master ID
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_21_UNION */
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_21_ADDR(base) ((base) + (0xCD4))

/* 寄存器说明：VP write master ID
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_22_UNION */
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_22_ADDR(base) ((base) + (0xCD8))

/* 寄存器说明：VP write master ID
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_23_UNION */
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_23_ADDR(base) ((base) + (0xCDC))

/* 寄存器说明：VP write master ID
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_24_UNION */
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_24_ADDR(base) ((base) + (0xCE0))

/* 寄存器说明：VP write master ID
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_25_UNION */
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_25_ADDR(base) ((base) + (0xCE4))

/* 寄存器说明：VP write master ID
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_26_UNION */
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_26_ADDR(base) ((base) + (0xCE8))

/* 寄存器说明：VP write master ID
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_27_UNION */
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_27_ADDR(base) ((base) + (0xCEC))

/* 寄存器说明：VP read master ID
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_0_UNION */
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_0_ADDR(base)  ((base) + (0xD80))

/* 寄存器说明：VP read master ID
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_4_UNION */
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_4_ADDR(base)  ((base) + (0xD90))

/* 寄存器说明：VP read master ID
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_5_UNION */
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_5_ADDR(base)  ((base) + (0xD94))

/* 寄存器说明：VP read master ID
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_6_UNION */
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_6_ADDR(base)  ((base) + (0xD98))

/* 寄存器说明：VP read master ID
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_7_UNION */
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_7_ADDR(base)  ((base) + (0xD9C))

/* 寄存器说明：VP read master ID
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_8_UNION */
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_8_ADDR(base)  ((base) + (0xDA0))

/* 寄存器说明：VP read master ID
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_9_UNION */
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_9_ADDR(base)  ((base) + (0xDA4))

/* 寄存器说明：VP read master ID
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_10_UNION */
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_10_ADDR(base) ((base) + (0xDA8))

/* 寄存器说明：Spare
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_SPARE_0_UNION */
#define SOC_ISP_CVDR_CVDR_SPARE_0_ADDR(base)          ((base) + (0xE00))

/* 寄存器说明：Spare
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_SPARE_1_UNION */
#define SOC_ISP_CVDR_CVDR_SPARE_1_ADDR(base)          ((base) + (0xE04))

/* 寄存器说明：Spare
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_SPARE_2_UNION */
#define SOC_ISP_CVDR_CVDR_SPARE_2_ADDR(base)          ((base) + (0xE08))

/* 寄存器说明：Spare
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_SPARE_3_UNION */
#define SOC_ISP_CVDR_CVDR_SPARE_3_ADDR(base)          ((base) + (0xE0C))

/* 寄存器说明：Video Port Write DEBUG information
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_0_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_0_ADDR(base)    ((base) + (0xF00))

/* 寄存器说明：Video Port Write DEBUG information
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_1_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_1_ADDR(base)    ((base) + (0xF04))

/* 寄存器说明：Video Port Write DEBUG information
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_4_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_4_ADDR(base)    ((base) + (0xF10))

/* 寄存器说明：Video Port Write DEBUG information
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_5_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_5_ADDR(base)    ((base) + (0xF14))

/* 寄存器说明：Video Port Write DEBUG information
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_8_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_8_ADDR(base)    ((base) + (0xF20))

/* 寄存器说明：Video Port Write DEBUG information
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_9_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_9_ADDR(base)    ((base) + (0xF24))

/* 寄存器说明：Video Port Write DEBUG information
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_14_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_14_ADDR(base)   ((base) + (0xF38))

/* 寄存器说明：Video Port Write DEBUG information
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_15_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_15_ADDR(base)   ((base) + (0xF3C))

/* 寄存器说明：Video Port Write DEBUG information
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_16_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_16_ADDR(base)   ((base) + (0xF40))

/* 寄存器说明：Video Port Write DEBUG information
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_17_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_17_ADDR(base)   ((base) + (0xF44))

/* 寄存器说明：Video Port Write DEBUG information
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_18_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_18_ADDR(base)   ((base) + (0xF48))

/* 寄存器说明：Video Port Write DEBUG information
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_19_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_19_ADDR(base)   ((base) + (0xF4C))

/* 寄存器说明：Video Port Write DEBUG information
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_20_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_20_ADDR(base)   ((base) + (0xF50))

/* 寄存器说明：Video Port Write DEBUG information
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_21_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_21_ADDR(base)   ((base) + (0xF54))

/* 寄存器说明：Video Port Write DEBUG information
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_22_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_22_ADDR(base)   ((base) + (0xF58))

/* 寄存器说明：Video Port Write DEBUG information
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_23_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_23_ADDR(base)   ((base) + (0xF5C))

/* 寄存器说明：Video Port Write DEBUG information
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_24_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_24_ADDR(base)   ((base) + (0xF60))

/* 寄存器说明：Video Port Write DEBUG information
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_25_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_25_ADDR(base)   ((base) + (0xF64))

/* 寄存器说明：Video Port Write DEBUG information
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_26_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_26_ADDR(base)   ((base) + (0xF68))

/* 寄存器说明：Video Port Write DEBUG information
   位域定义UNION结构:  SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_27_UNION */
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_27_ADDR(base)   ((base) + (0xF6C))





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
                     (1/1) CVDR
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_CVDR_CFG_UNION
 结构说明  : CVDR_CVDR_CFG 寄存器结构定义。地址偏移量:0x0，初值:0x01002000，宽度:32
 寄存器说明: CVDR config register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  du_write_threshold     : 6;  /* bit[0-5]  : "DataUnit write threshold (from 0 to 64) - AXI burst modeReturnToLineThis registers enables to define when the AXI write commands must be sent.ReturnToLineIf the number of valid DUs is higher than the du_write_threshold */
        unsigned int  reserved_0             : 2;  /* bit[6-7]  :  */
        unsigned int  stall_srt_du_threshold : 8;  /* bit[8-15] : "configuration register used to limit the impact of the srt (soft real time) initiators when the system is preforming refresh or any other stall on the DRAM. Once number_busy_write_DUs > stall_srt_du_threshold */
        unsigned int  max_axiread_id         : 5;  /* bit[16-20]: "Maximum value allowed on the ARID to access the memory.ReturnToLine0: only value 0x0 is allowed */
        unsigned int  reserved_1             : 3;  /* bit[21-23]:  */
        unsigned int  max_axiwrite_tx        : 5;  /* bit[24-28]: "max number of AXI write transactionsReturnToLine0: 1 transaction at a time maximumReturnToLine1: 2 transaction at a time maximumReturnToLineand so onReturnToLine31: 32 transactions maximum at a time (ordered)ReturnToLine[note] for v110 */
        unsigned int  reserved_2             : 1;  /* bit[29-29]:  */
        unsigned int  force_rd_clk_on        : 1;  /* bit[30-30]: "CVDR WR clock control ReturnToLine0: local clock gating is controlled by the hardwareReturnToLine1: local clock gating is disabled (clock is ON)" */
        unsigned int  force_wr_clk_on        : 1;  /* bit[31-31]: "CVDR WR clock control ReturnToLine0: local clock gating is controlled by the hardwareReturnToLine1: local clock gating is disabled (clock is ON)" */
    } reg;
} SOC_ISP_CVDR_CVDR_CVDR_CFG_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_CVDR_CFG_du_write_threshold_START      (0)
#define SOC_ISP_CVDR_CVDR_CVDR_CFG_du_write_threshold_END        (5)
#define SOC_ISP_CVDR_CVDR_CVDR_CFG_stall_srt_du_threshold_START  (8)
#define SOC_ISP_CVDR_CVDR_CVDR_CFG_stall_srt_du_threshold_END    (15)
#define SOC_ISP_CVDR_CVDR_CVDR_CFG_max_axiread_id_START          (16)
#define SOC_ISP_CVDR_CVDR_CVDR_CFG_max_axiread_id_END            (20)
#define SOC_ISP_CVDR_CVDR_CVDR_CFG_max_axiwrite_tx_START         (24)
#define SOC_ISP_CVDR_CVDR_CVDR_CFG_max_axiwrite_tx_END           (28)
#define SOC_ISP_CVDR_CVDR_CVDR_CFG_force_rd_clk_on_START         (30)
#define SOC_ISP_CVDR_CVDR_CVDR_CFG_force_rd_clk_on_END           (30)
#define SOC_ISP_CVDR_CVDR_CVDR_CFG_force_wr_clk_on_START         (31)
#define SOC_ISP_CVDR_CVDR_CVDR_CFG_force_wr_clk_on_END           (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_CVDR_DEBUG_EN_UNION
 结构说明  : CVDR_CVDR_DEBUG_EN 寄存器结构定义。地址偏移量:0x4，初值:0x00000000，宽度:32
 寄存器说明: CVDR debug register enable
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wr_peak_en : 1;  /* bit[0-0] : Enable the FIFO peak functionality over the write port */
        unsigned int  reserved_0 : 7;  /* bit[1-7] :  */
        unsigned int  rd_peak_en : 1;  /* bit[8-8] : Enable the FIFO peak functionality over the read port */
        unsigned int  reserved_1 : 23; /* bit[9-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_CVDR_DEBUG_EN_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_CVDR_DEBUG_EN_wr_peak_en_START  (0)
#define SOC_ISP_CVDR_CVDR_CVDR_DEBUG_EN_wr_peak_en_END    (0)
#define SOC_ISP_CVDR_CVDR_CVDR_DEBUG_EN_rd_peak_en_START  (8)
#define SOC_ISP_CVDR_CVDR_CVDR_DEBUG_EN_rd_peak_en_END    (8)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_CVDR_DEBUG_UNION
 结构说明  : CVDR_CVDR_DEBUG 寄存器结构定义。地址偏移量:0x8，初值:0x00000000，宽度:32
 寄存器说明: CVDR debug register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wr_peak  : 8;  /* bit[0-7]  : Peak number of Data Units used for the write functionality */
        unsigned int  rd_peak  : 8;  /* bit[8-15] : Peak number of Data Units used for the read functionality */
        unsigned int  reserved : 16; /* bit[16-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_CVDR_DEBUG_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_CVDR_DEBUG_wr_peak_START   (0)
#define SOC_ISP_CVDR_CVDR_CVDR_DEBUG_wr_peak_END     (7)
#define SOC_ISP_CVDR_CVDR_CVDR_DEBUG_rd_peak_START   (8)
#define SOC_ISP_CVDR_CVDR_CVDR_DEBUG_rd_peak_END     (15)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_CVDR_WR_QOS_CFG_UNION
 结构说明  : CVDR_CVDR_WR_QOS_CFG 寄存器结构定义。地址偏移量:0xC，初值:0xCC765432，宽度:32
 寄存器说明: AXI Write QOS/Pressure configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wr_qos_threshold_01_stop  : 4;  /* bit[0-3]  : same behavior as threshold_11 */
        unsigned int  wr_qos_threshold_01_start : 4;  /* bit[4-7]  : same behavior as threshold_11 */
        unsigned int  wr_qos_threshold_10_stop  : 4;  /* bit[8-11] : same behavior as threshold_11 */
        unsigned int  wr_qos_threshold_10_start : 4;  /* bit[12-15]: same behavior as threshold_11 */
        unsigned int  wr_qos_threshold_11_stop  : 4;  /* bit[16-19]: stop condition for internal Qos 11 */
        unsigned int  wr_qos_threshold_11_start : 4;  /* bit[20-23]: "Threshold level used for Qos generation (based on number of DUs in use). Real value = wr_threshold_qos * 8. Once reached */
        unsigned int  reserved                  : 2;  /* bit[24-25]:  */
        unsigned int  wr_qos_rt_min             : 2;  /* bit[26-27]: Minimum QoS value to generate for RT initiators */
        unsigned int  wr_qos_srt_max            : 2;  /* bit[28-29]: Maximum QoS value to generate for SRT initiators */
        unsigned int  wr_qos_sr                 : 2;  /* bit[30-31]: 2 bits register to configure the qos value to generate when pressure from SR is asserted. Note that the qos generated will be the highest value possible between the wr_qos_sr and the qos generated based on bumber of DUs in use */
    } reg;
} SOC_ISP_CVDR_CVDR_CVDR_WR_QOS_CFG_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_CVDR_WR_QOS_CFG_wr_qos_threshold_01_stop_START   (0)
#define SOC_ISP_CVDR_CVDR_CVDR_WR_QOS_CFG_wr_qos_threshold_01_stop_END     (3)
#define SOC_ISP_CVDR_CVDR_CVDR_WR_QOS_CFG_wr_qos_threshold_01_start_START  (4)
#define SOC_ISP_CVDR_CVDR_CVDR_WR_QOS_CFG_wr_qos_threshold_01_start_END    (7)
#define SOC_ISP_CVDR_CVDR_CVDR_WR_QOS_CFG_wr_qos_threshold_10_stop_START   (8)
#define SOC_ISP_CVDR_CVDR_CVDR_WR_QOS_CFG_wr_qos_threshold_10_stop_END     (11)
#define SOC_ISP_CVDR_CVDR_CVDR_WR_QOS_CFG_wr_qos_threshold_10_start_START  (12)
#define SOC_ISP_CVDR_CVDR_CVDR_WR_QOS_CFG_wr_qos_threshold_10_start_END    (15)
#define SOC_ISP_CVDR_CVDR_CVDR_WR_QOS_CFG_wr_qos_threshold_11_stop_START   (16)
#define SOC_ISP_CVDR_CVDR_CVDR_WR_QOS_CFG_wr_qos_threshold_11_stop_END     (19)
#define SOC_ISP_CVDR_CVDR_CVDR_WR_QOS_CFG_wr_qos_threshold_11_start_START  (20)
#define SOC_ISP_CVDR_CVDR_CVDR_WR_QOS_CFG_wr_qos_threshold_11_start_END    (23)
#define SOC_ISP_CVDR_CVDR_CVDR_WR_QOS_CFG_wr_qos_rt_min_START              (26)
#define SOC_ISP_CVDR_CVDR_CVDR_WR_QOS_CFG_wr_qos_rt_min_END                (27)
#define SOC_ISP_CVDR_CVDR_CVDR_WR_QOS_CFG_wr_qos_srt_max_START             (28)
#define SOC_ISP_CVDR_CVDR_CVDR_WR_QOS_CFG_wr_qos_srt_max_END               (29)
#define SOC_ISP_CVDR_CVDR_CVDR_WR_QOS_CFG_wr_qos_sr_START                  (30)
#define SOC_ISP_CVDR_CVDR_CVDR_WR_QOS_CFG_wr_qos_sr_END                    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_CVDR_RD_QOS_CFG_UNION
 结构说明  : CVDR_CVDR_RD_QOS_CFG 寄存器结构定义。地址偏移量:0x10，初值:0xCC122334，宽度:32
 寄存器说明: AXI Read QOS/Pressure configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rd_qos_threshold_01_stop  : 4;  /* bit[0-3]  : same behavior as threshold_11 */
        unsigned int  rd_qos_threshold_01_start : 4;  /* bit[4-7]  : same behavior as threshold_11 */
        unsigned int  rd_qos_threshold_10_stop  : 4;  /* bit[8-11] : same behavior as threshold_11 */
        unsigned int  rd_qos_threshold_10_start : 4;  /* bit[12-15]: same behavior as threshold_11 */
        unsigned int  rd_qos_threshold_11_stop  : 4;  /* bit[16-19]: stop condition for internal Qos 11 */
        unsigned int  rd_qos_threshold_11_start : 4;  /* bit[20-23]: "QOS=11 generated if number of DUs in use is less than the programmed value * 8.ReturnToLineWhen 0: the threshold check is disabledReturnToLineWhen 7: maximum number of DUs 56" */
        unsigned int  reserved                  : 2;  /* bit[24-25]:  */
        unsigned int  rd_qos_rt_min             : 2;  /* bit[26-27]: Minimum QoS value to generate for RT initiators */
        unsigned int  rd_qos_srt_max            : 2;  /* bit[28-29]: Maximum QoS value to generate for SRT initiators */
        unsigned int  rd_qos_sr                 : 2;  /* bit[30-31]: 2 bits register to configure the qos value to generate when pressure from SR is asserted. Note that the qos generated will be the highest value possible between the rd_qos_sr and the qos generated based on bumber of DUs in use */
    } reg;
} SOC_ISP_CVDR_CVDR_CVDR_RD_QOS_CFG_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_CVDR_RD_QOS_CFG_rd_qos_threshold_01_stop_START   (0)
#define SOC_ISP_CVDR_CVDR_CVDR_RD_QOS_CFG_rd_qos_threshold_01_stop_END     (3)
#define SOC_ISP_CVDR_CVDR_CVDR_RD_QOS_CFG_rd_qos_threshold_01_start_START  (4)
#define SOC_ISP_CVDR_CVDR_CVDR_RD_QOS_CFG_rd_qos_threshold_01_start_END    (7)
#define SOC_ISP_CVDR_CVDR_CVDR_RD_QOS_CFG_rd_qos_threshold_10_stop_START   (8)
#define SOC_ISP_CVDR_CVDR_CVDR_RD_QOS_CFG_rd_qos_threshold_10_stop_END     (11)
#define SOC_ISP_CVDR_CVDR_CVDR_RD_QOS_CFG_rd_qos_threshold_10_start_START  (12)
#define SOC_ISP_CVDR_CVDR_CVDR_RD_QOS_CFG_rd_qos_threshold_10_start_END    (15)
#define SOC_ISP_CVDR_CVDR_CVDR_RD_QOS_CFG_rd_qos_threshold_11_stop_START   (16)
#define SOC_ISP_CVDR_CVDR_CVDR_RD_QOS_CFG_rd_qos_threshold_11_stop_END     (19)
#define SOC_ISP_CVDR_CVDR_CVDR_RD_QOS_CFG_rd_qos_threshold_11_start_START  (20)
#define SOC_ISP_CVDR_CVDR_CVDR_RD_QOS_CFG_rd_qos_threshold_11_start_END    (23)
#define SOC_ISP_CVDR_CVDR_CVDR_RD_QOS_CFG_rd_qos_rt_min_START              (26)
#define SOC_ISP_CVDR_CVDR_CVDR_RD_QOS_CFG_rd_qos_rt_min_END                (27)
#define SOC_ISP_CVDR_CVDR_CVDR_RD_QOS_CFG_rd_qos_srt_max_START             (28)
#define SOC_ISP_CVDR_CVDR_CVDR_RD_QOS_CFG_rd_qos_srt_max_END               (29)
#define SOC_ISP_CVDR_CVDR_CVDR_RD_QOS_CFG_rd_qos_sr_START                  (30)
#define SOC_ISP_CVDR_CVDR_CVDR_RD_QOS_CFG_rd_qos_sr_END                    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_OTHER_RO_UNION
 结构说明  : CVDR_OTHER_RO 寄存器结构定义。地址偏移量:0x14，初值:0x00000000，宽度:32
 寄存器说明: Spare Other RO
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  other_ro : 32; /* bit[0-31]: "Bit 31:1: unusedReturnToLineBit 0: used for AXI flush mechanism (in conjonction with bit 0 in OTHER_RW)" */
    } reg;
} SOC_ISP_CVDR_CVDR_OTHER_RO_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_OTHER_RO_other_ro_START  (0)
#define SOC_ISP_CVDR_CVDR_OTHER_RO_other_ro_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_OTHER_RW_UNION
 结构说明  : CVDR_OTHER_RW 寄存器结构定义。地址偏移量:0x18，初值:0x00000000，宽度:32
 寄存器说明: Spare Other RW
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  other_rw : 32; /* bit[0-31]: "Bit 31:1: unusedReturnToLineBit 0: used for AXI flush mechanism (in conjonction with bit 0 in OTHER_RO)" */
    } reg;
} SOC_ISP_CVDR_CVDR_OTHER_RW_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_OTHER_RW_other_rw_START  (0)
#define SOC_ISP_CVDR_CVDR_OTHER_RW_other_rw_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_CFG_0_UNION
 结构说明  : CVDR_VP_WR_CFG_0 寄存器结构定义。地址偏移量:0x1C，初值:0x00000000，宽度:32
 寄存器说明: Video port write Configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_pixel_format_0    : 4;  /* bit[0-3]  : "Pixel formats supported (see ref. [1])ReturnToLine 0:3->1PF8:1PF14 ReturnToLine 4:7->2PF8:2PF14 ReturnToLine 9:11->3PF8:3PF14 ReturnToLine 12:D32 ReturnToLine 13:D48 ReturnToLine 14: D64" */
        unsigned int  vpwr_pixel_expansion_0 : 1;  /* bit[4-4]  : Pixel expansion can be used (see ref. [1]) */
        unsigned int  reserved               : 10; /* bit[5-14] :  */
        unsigned int  vpwr_last_page_0       : 17; /* bit[15-31]: "last 32KB page reserved to write the data. This page is not necessarely prefetched but is the last page reserved by the Software.ReturnToLineThe CVDR must prefetch the page used by the frame start (back to initial - in case of continuous mode) once the last page is equal to vpwr_last_page. ReturnToLineThis info must be aligned with the frame size (SW info) and the vpwr_line_wrap info (SW and HW) to be aligned with buffer size reserved by the SW.ReturnToLineSpecific case: long lines in 1 frame are possible (Jpeg case */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_CFG_0_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_0_vpwr_pixel_format_0_START     (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_0_vpwr_pixel_format_0_END       (3)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_0_vpwr_pixel_expansion_0_START  (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_0_vpwr_pixel_expansion_0_END    (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_0_vpwr_last_page_0_START        (15)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_0_vpwr_last_page_0_END          (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_0_UNION
 结构说明  : CVDR_VP_WR_AXI_FS_0 寄存器结构定义。地址偏移量:0x20，初值:0x00000000，宽度:32
 寄存器说明: AXI address Frame start
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved                   : 4;  /* bit[0-3] :  */
        unsigned int  vpwr_address_frame_start_0 : 28; /* bit[4-31]: "Start address of the frame (in 16 bytes boundary).ReturnToLineSince we are 128-bits */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_0_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_0_vpwr_address_frame_start_0_START  (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_0_vpwr_address_frame_start_0_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_0_UNION
 结构说明  : CVDR_VP_WR_AXI_LINE_0 寄存器结构定义。地址偏移量:0x24，初值:0x1FFF8000，宽度:32
 寄存器说明: AXI line wrap and line stride
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_line_stride_0 : 10; /* bit[0-9]  : "Stride to use on line starts (aligned to a 16 byte boundary: Max stride of 16 KBytes)ReturnToLine0: line stride disabled (continuous) (continuous mode : next line will start on a 128 bytes boundary)ReturnToLine1: 2*16 bytesReturnToLineand so onReturnToLine1023 : 1024*16 bytes" */
        unsigned int  reserved_0         : 5;  /* bit[10-14]:  */
        unsigned int  vpwr_line_wrap_0   : 14; /* bit[15-28]: "Line wrap: wrap to frame start location (14 bits)ReturnToLine0: wrap every lineReturnToLine1: wrap every 2 linesReturnToLineand so onReturnToLine0x3FFF: wrap every 16384 linesReturnToLineIn case of YUV420 */
        unsigned int  reserved_1         : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_0_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_0_vpwr_line_stride_0_START  (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_0_vpwr_line_stride_0_END    (9)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_0_vpwr_line_wrap_0_START    (15)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_0_vpwr_line_wrap_0_END      (28)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_0_UNION
 结构说明  : CVDR_VP_WR_PREFETCH_0 寄存器结构定义。地址偏移量:0x28，初值:0x00000100，宽度:32
 寄存器说明: Configure the prefetch mechanism and must be aligned with the SMMU configuration.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_index_id0_0       : 7;  /* bit[0-6]  : configurable index ID 0 */
        unsigned int  reserved_0             : 1;  /* bit[7-7]  :  */
        unsigned int  vpwr_index_id1_0       : 7;  /* bit[8-14] : configurable index ID 1 */
        unsigned int  reserved_1             : 16; /* bit[15-30]:  */
        unsigned int  vpwr_prefetch_bypass_0 : 1;  /* bit[31-31]: "Enables to bypass the prefetch mechanism.ReturnToLine0: prefetch functionality is enabledReturnToLine1: prefetch functionality is bypassed (Index ID is always vpwr_index_id0)" */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_0_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_0_vpwr_index_id0_0_START        (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_0_vpwr_index_id0_0_END          (6)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_0_vpwr_index_id1_0_START        (8)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_0_vpwr_index_id1_0_END          (14)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_0_vpwr_prefetch_bypass_0_START  (31)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_0_vpwr_prefetch_bypass_0_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_CFG_1_UNION
 结构说明  : CVDR_VP_WR_CFG_1 寄存器结构定义。地址偏移量:0x2C，初值:0x00000000，宽度:32
 寄存器说明: Video port write Configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_pixel_format_1    : 4;  /* bit[0-3]  : See previous definition on VP_WR_CFG_0 */
        unsigned int  vpwr_pixel_expansion_1 : 1;  /* bit[4-4]  : See previous definition on VP_WR_CFG_0 */
        unsigned int  reserved               : 10; /* bit[5-14] :  */
        unsigned int  vpwr_last_page_1       : 17; /* bit[15-31]: See previous definition on VP_WR_CFG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_CFG_1_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_1_vpwr_pixel_format_1_START     (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_1_vpwr_pixel_format_1_END       (3)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_1_vpwr_pixel_expansion_1_START  (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_1_vpwr_pixel_expansion_1_END    (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_1_vpwr_last_page_1_START        (15)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_1_vpwr_last_page_1_END          (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_1_UNION
 结构说明  : CVDR_VP_WR_AXI_FS_1 寄存器结构定义。地址偏移量:0x30，初值:0x00000000，宽度:32
 寄存器说明: AXI address Frame start
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved                   : 4;  /* bit[0-3] :  */
        unsigned int  vpwr_address_frame_start_1 : 28; /* bit[4-31]: See previous definition on VP_WR_AXI_FS_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_1_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_1_vpwr_address_frame_start_1_START  (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_1_vpwr_address_frame_start_1_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_1_UNION
 结构说明  : CVDR_VP_WR_AXI_LINE_1 寄存器结构定义。地址偏移量:0x34，初值:0x1FFF8000，宽度:32
 寄存器说明: AXI line wrap and line stride
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_line_stride_1 : 10; /* bit[0-9]  : See previous definition on VP_WR_AXI_LINE_0 */
        unsigned int  reserved_0         : 5;  /* bit[10-14]:  */
        unsigned int  vpwr_line_wrap_1   : 14; /* bit[15-28]: See previous definition on VP_WR_AXI_LINE_0 */
        unsigned int  reserved_1         : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_1_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_1_vpwr_line_stride_1_START  (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_1_vpwr_line_stride_1_END    (9)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_1_vpwr_line_wrap_1_START    (15)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_1_vpwr_line_wrap_1_END      (28)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_1_UNION
 结构说明  : CVDR_VP_WR_PREFETCH_1 寄存器结构定义。地址偏移量:0x38，初值:0x00000302，宽度:32
 寄存器说明: Configure the prefetch mechanism and must be aligned with the SMMU configuration.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_index_id0_1       : 7;  /* bit[0-6]  : See previous definition on VP_WR_PREFETCH_0 */
        unsigned int  reserved_0             : 1;  /* bit[7-7]  :  */
        unsigned int  vpwr_index_id1_1       : 7;  /* bit[8-14] : See previous definition on VP_WR_PREFETCH_0 */
        unsigned int  reserved_1             : 16; /* bit[15-30]:  */
        unsigned int  vpwr_prefetch_bypass_1 : 1;  /* bit[31-31]: See previous definition on VP_WR_PREFETCH_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_1_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_1_vpwr_index_id0_1_START        (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_1_vpwr_index_id0_1_END          (6)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_1_vpwr_index_id1_1_START        (8)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_1_vpwr_index_id1_1_END          (14)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_1_vpwr_prefetch_bypass_1_START  (31)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_1_vpwr_prefetch_bypass_1_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_CFG_4_UNION
 结构说明  : CVDR_VP_WR_CFG_4 寄存器结构定义。地址偏移量:0x5C，初值:0x00000000，宽度:32
 寄存器说明: Video port write Configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_pixel_format_4    : 4;  /* bit[0-3]  : See previous definition on VP_WR_CFG_0 */
        unsigned int  vpwr_pixel_expansion_4 : 1;  /* bit[4-4]  : See previous definition on VP_WR_CFG_0 */
        unsigned int  reserved               : 10; /* bit[5-14] :  */
        unsigned int  vpwr_last_page_4       : 17; /* bit[15-31]: See previous definition on VP_WR_CFG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_CFG_4_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_4_vpwr_pixel_format_4_START     (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_4_vpwr_pixel_format_4_END       (3)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_4_vpwr_pixel_expansion_4_START  (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_4_vpwr_pixel_expansion_4_END    (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_4_vpwr_last_page_4_START        (15)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_4_vpwr_last_page_4_END          (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_4_UNION
 结构说明  : CVDR_VP_WR_AXI_FS_4 寄存器结构定义。地址偏移量:0x60，初值:0x00000000，宽度:32
 寄存器说明: AXI address Frame start
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved                   : 4;  /* bit[0-3] :  */
        unsigned int  vpwr_address_frame_start_4 : 28; /* bit[4-31]: See previous definition on VP_WR_AXI_FS_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_4_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_4_vpwr_address_frame_start_4_START  (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_4_vpwr_address_frame_start_4_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_4_UNION
 结构说明  : CVDR_VP_WR_AXI_LINE_4 寄存器结构定义。地址偏移量:0x64，初值:0x1FFF8000，宽度:32
 寄存器说明: AXI line wrap and line stride
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_line_stride_4 : 10; /* bit[0-9]  : See previous definition on VP_WR_AXI_LINE_0 */
        unsigned int  reserved_0         : 5;  /* bit[10-14]:  */
        unsigned int  vpwr_line_wrap_4   : 14; /* bit[15-28]: See previous definition on VP_WR_AXI_LINE_0 */
        unsigned int  reserved_1         : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_4_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_4_vpwr_line_stride_4_START  (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_4_vpwr_line_stride_4_END    (9)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_4_vpwr_line_wrap_4_START    (15)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_4_vpwr_line_wrap_4_END      (28)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_4_UNION
 结构说明  : CVDR_VP_WR_PREFETCH_4 寄存器结构定义。地址偏移量:0x68，初值:0x00000504，宽度:32
 寄存器说明: Configure the prefetch mechanism and must be aligned with the SMMU configuration.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_index_id0_4       : 7;  /* bit[0-6]  : See previous definition on VP_WR_PREFETCH_0 */
        unsigned int  reserved_0             : 1;  /* bit[7-7]  :  */
        unsigned int  vpwr_index_id1_4       : 7;  /* bit[8-14] : See previous definition on VP_WR_PREFETCH_0 */
        unsigned int  reserved_1             : 16; /* bit[15-30]:  */
        unsigned int  vpwr_prefetch_bypass_4 : 1;  /* bit[31-31]: See previous definition on VP_WR_PREFETCH_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_4_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_4_vpwr_index_id0_4_START        (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_4_vpwr_index_id0_4_END          (6)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_4_vpwr_index_id1_4_START        (8)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_4_vpwr_index_id1_4_END          (14)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_4_vpwr_prefetch_bypass_4_START  (31)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_4_vpwr_prefetch_bypass_4_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_CFG_5_UNION
 结构说明  : CVDR_VP_WR_CFG_5 寄存器结构定义。地址偏移量:0x6C，初值:0x00000000，宽度:32
 寄存器说明: Video port write Configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_pixel_format_5    : 4;  /* bit[0-3]  : See previous definition on VP_WR_CFG_0 */
        unsigned int  vpwr_pixel_expansion_5 : 1;  /* bit[4-4]  : See previous definition on VP_WR_CFG_0 */
        unsigned int  reserved               : 10; /* bit[5-14] :  */
        unsigned int  vpwr_last_page_5       : 17; /* bit[15-31]: See previous definition on VP_WR_CFG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_CFG_5_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_5_vpwr_pixel_format_5_START     (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_5_vpwr_pixel_format_5_END       (3)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_5_vpwr_pixel_expansion_5_START  (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_5_vpwr_pixel_expansion_5_END    (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_5_vpwr_last_page_5_START        (15)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_5_vpwr_last_page_5_END          (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_5_UNION
 结构说明  : CVDR_VP_WR_AXI_FS_5 寄存器结构定义。地址偏移量:0x70，初值:0x00000000，宽度:32
 寄存器说明: AXI address Frame start
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved                   : 4;  /* bit[0-3] :  */
        unsigned int  vpwr_address_frame_start_5 : 28; /* bit[4-31]: See previous definition on VP_WR_AXI_FS_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_5_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_5_vpwr_address_frame_start_5_START  (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_5_vpwr_address_frame_start_5_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_5_UNION
 结构说明  : CVDR_VP_WR_AXI_LINE_5 寄存器结构定义。地址偏移量:0x74，初值:0x1FFF8000，宽度:32
 寄存器说明: AXI line wrap and line stride
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_line_stride_5 : 10; /* bit[0-9]  : See previous definition on VP_WR_AXI_LINE_0 */
        unsigned int  reserved_0         : 5;  /* bit[10-14]:  */
        unsigned int  vpwr_line_wrap_5   : 14; /* bit[15-28]: See previous definition on VP_WR_AXI_LINE_0 */
        unsigned int  reserved_1         : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_5_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_5_vpwr_line_stride_5_START  (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_5_vpwr_line_stride_5_END    (9)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_5_vpwr_line_wrap_5_START    (15)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_5_vpwr_line_wrap_5_END      (28)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_5_UNION
 结构说明  : CVDR_VP_WR_PREFETCH_5 寄存器结构定义。地址偏移量:0x78，初值:0x00000706，宽度:32
 寄存器说明: Configure the prefetch mechanism and must be aligned with the SMMU configuration.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_index_id0_5       : 7;  /* bit[0-6]  : See previous definition on VP_WR_PREFETCH_0 */
        unsigned int  reserved_0             : 1;  /* bit[7-7]  :  */
        unsigned int  vpwr_index_id1_5       : 7;  /* bit[8-14] : See previous definition on VP_WR_PREFETCH_0 */
        unsigned int  reserved_1             : 16; /* bit[15-30]:  */
        unsigned int  vpwr_prefetch_bypass_5 : 1;  /* bit[31-31]: See previous definition on VP_WR_PREFETCH_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_5_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_5_vpwr_index_id0_5_START        (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_5_vpwr_index_id0_5_END          (6)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_5_vpwr_index_id1_5_START        (8)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_5_vpwr_index_id1_5_END          (14)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_5_vpwr_prefetch_bypass_5_START  (31)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_5_vpwr_prefetch_bypass_5_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_CFG_8_UNION
 结构说明  : CVDR_VP_WR_CFG_8 寄存器结构定义。地址偏移量:0x9C，初值:0x00000000，宽度:32
 寄存器说明: Video port write Configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_pixel_format_8    : 4;  /* bit[0-3]  : See previous definition on VP_WR_CFG_0 */
        unsigned int  vpwr_pixel_expansion_8 : 1;  /* bit[4-4]  : See previous definition on VP_WR_CFG_0 */
        unsigned int  reserved               : 10; /* bit[5-14] :  */
        unsigned int  vpwr_last_page_8       : 17; /* bit[15-31]: See previous definition on VP_WR_CFG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_CFG_8_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_8_vpwr_pixel_format_8_START     (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_8_vpwr_pixel_format_8_END       (3)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_8_vpwr_pixel_expansion_8_START  (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_8_vpwr_pixel_expansion_8_END    (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_8_vpwr_last_page_8_START        (15)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_8_vpwr_last_page_8_END          (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_8_UNION
 结构说明  : CVDR_VP_WR_AXI_FS_8 寄存器结构定义。地址偏移量:0xA0，初值:0x00000000，宽度:32
 寄存器说明: AXI address Frame start
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved                   : 4;  /* bit[0-3] :  */
        unsigned int  vpwr_address_frame_start_8 : 28; /* bit[4-31]: See previous definition on VP_WR_AXI_FS_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_8_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_8_vpwr_address_frame_start_8_START  (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_8_vpwr_address_frame_start_8_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_8_UNION
 结构说明  : CVDR_VP_WR_AXI_LINE_8 寄存器结构定义。地址偏移量:0xA4，初值:0x1FFF8000，宽度:32
 寄存器说明: AXI line wrap and line stride
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_line_stride_8 : 10; /* bit[0-9]  : See previous definition on VP_WR_AXI_LINE_0 */
        unsigned int  reserved_0         : 5;  /* bit[10-14]:  */
        unsigned int  vpwr_line_wrap_8   : 14; /* bit[15-28]: See previous definition on VP_WR_AXI_LINE_0 */
        unsigned int  reserved_1         : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_8_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_8_vpwr_line_stride_8_START  (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_8_vpwr_line_stride_8_END    (9)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_8_vpwr_line_wrap_8_START    (15)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_8_vpwr_line_wrap_8_END      (28)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_8_UNION
 结构说明  : CVDR_VP_WR_PREFETCH_8 寄存器结构定义。地址偏移量:0xA8，初值:0x00000908，宽度:32
 寄存器说明: Configure the prefetch mechanism and must be aligned with the SMMU configuration.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_index_id0_8       : 7;  /* bit[0-6]  : See previous definition on VP_WR_PREFETCH_0 */
        unsigned int  reserved_0             : 1;  /* bit[7-7]  :  */
        unsigned int  vpwr_index_id1_8       : 7;  /* bit[8-14] : See previous definition on VP_WR_PREFETCH_0 */
        unsigned int  reserved_1             : 16; /* bit[15-30]:  */
        unsigned int  vpwr_prefetch_bypass_8 : 1;  /* bit[31-31]: See previous definition on VP_WR_PREFETCH_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_8_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_8_vpwr_index_id0_8_START        (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_8_vpwr_index_id0_8_END          (6)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_8_vpwr_index_id1_8_START        (8)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_8_vpwr_index_id1_8_END          (14)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_8_vpwr_prefetch_bypass_8_START  (31)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_8_vpwr_prefetch_bypass_8_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_CFG_9_UNION
 结构说明  : CVDR_VP_WR_CFG_9 寄存器结构定义。地址偏移量:0xAC，初值:0x00000000，宽度:32
 寄存器说明: Video port write Configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_pixel_format_9    : 4;  /* bit[0-3]  : See previous definition on VP_WR_CFG_0 */
        unsigned int  vpwr_pixel_expansion_9 : 1;  /* bit[4-4]  : See previous definition on VP_WR_CFG_0 */
        unsigned int  reserved               : 10; /* bit[5-14] :  */
        unsigned int  vpwr_last_page_9       : 17; /* bit[15-31]: See previous definition on VP_WR_CFG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_CFG_9_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_9_vpwr_pixel_format_9_START     (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_9_vpwr_pixel_format_9_END       (3)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_9_vpwr_pixel_expansion_9_START  (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_9_vpwr_pixel_expansion_9_END    (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_9_vpwr_last_page_9_START        (15)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_9_vpwr_last_page_9_END          (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_9_UNION
 结构说明  : CVDR_VP_WR_AXI_FS_9 寄存器结构定义。地址偏移量:0xB0，初值:0x00000000，宽度:32
 寄存器说明: AXI address Frame start
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved                   : 4;  /* bit[0-3] :  */
        unsigned int  vpwr_address_frame_start_9 : 28; /* bit[4-31]: See previous definition on VP_WR_AXI_FS_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_9_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_9_vpwr_address_frame_start_9_START  (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_9_vpwr_address_frame_start_9_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_9_UNION
 结构说明  : CVDR_VP_WR_AXI_LINE_9 寄存器结构定义。地址偏移量:0xB4，初值:0x1FFF8000，宽度:32
 寄存器说明: AXI line wrap and line stride
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_line_stride_9 : 10; /* bit[0-9]  : See previous definition on VP_WR_AXI_LINE_0 */
        unsigned int  reserved_0         : 5;  /* bit[10-14]:  */
        unsigned int  vpwr_line_wrap_9   : 14; /* bit[15-28]: See previous definition on VP_WR_AXI_LINE_0 */
        unsigned int  reserved_1         : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_9_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_9_vpwr_line_stride_9_START  (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_9_vpwr_line_stride_9_END    (9)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_9_vpwr_line_wrap_9_START    (15)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_9_vpwr_line_wrap_9_END      (28)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_9_UNION
 结构说明  : CVDR_VP_WR_PREFETCH_9 寄存器结构定义。地址偏移量:0xB8，初值:0x00000B0A，宽度:32
 寄存器说明: Configure the prefetch mechanism and must be aligned with the SMMU configuration.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_index_id0_9       : 7;  /* bit[0-6]  : See previous definition on VP_WR_PREFETCH_0 */
        unsigned int  reserved_0             : 1;  /* bit[7-7]  :  */
        unsigned int  vpwr_index_id1_9       : 7;  /* bit[8-14] : See previous definition on VP_WR_PREFETCH_0 */
        unsigned int  reserved_1             : 16; /* bit[15-30]:  */
        unsigned int  vpwr_prefetch_bypass_9 : 1;  /* bit[31-31]: See previous definition on VP_WR_PREFETCH_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_9_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_9_vpwr_index_id0_9_START        (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_9_vpwr_index_id0_9_END          (6)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_9_vpwr_index_id1_9_START        (8)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_9_vpwr_index_id1_9_END          (14)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_9_vpwr_prefetch_bypass_9_START  (31)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_9_vpwr_prefetch_bypass_9_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_CFG_14_UNION
 结构说明  : CVDR_VP_WR_CFG_14 寄存器结构定义。地址偏移量:0xFC，初值:0x00000000，宽度:32
 寄存器说明: Video port write Configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_pixel_format_14    : 4;  /* bit[0-3]  : See previous definition on VP_WR_CFG_0 */
        unsigned int  vpwr_pixel_expansion_14 : 1;  /* bit[4-4]  : See previous definition on VP_WR_CFG_0 */
        unsigned int  reserved                : 10; /* bit[5-14] :  */
        unsigned int  vpwr_last_page_14       : 17; /* bit[15-31]: See previous definition on VP_WR_CFG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_CFG_14_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_14_vpwr_pixel_format_14_START     (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_14_vpwr_pixel_format_14_END       (3)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_14_vpwr_pixel_expansion_14_START  (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_14_vpwr_pixel_expansion_14_END    (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_14_vpwr_last_page_14_START        (15)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_14_vpwr_last_page_14_END          (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_14_UNION
 结构说明  : CVDR_VP_WR_AXI_FS_14 寄存器结构定义。地址偏移量:0x100，初值:0x00000000，宽度:32
 寄存器说明: AXI address Frame start
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved                    : 4;  /* bit[0-3] :  */
        unsigned int  vpwr_address_frame_start_14 : 28; /* bit[4-31]: See previous definition on VP_WR_AXI_FS_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_14_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_14_vpwr_address_frame_start_14_START  (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_14_vpwr_address_frame_start_14_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_14_UNION
 结构说明  : CVDR_VP_WR_AXI_LINE_14 寄存器结构定义。地址偏移量:0x104，初值:0x1FFF8000，宽度:32
 寄存器说明: AXI line wrap and line stride
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_line_stride_14 : 10; /* bit[0-9]  : See previous definition on VP_WR_AXI_LINE_0 */
        unsigned int  reserved_0          : 5;  /* bit[10-14]:  */
        unsigned int  vpwr_line_wrap_14   : 14; /* bit[15-28]: See previous definition on VP_WR_AXI_LINE_0 */
        unsigned int  reserved_1          : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_14_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_14_vpwr_line_stride_14_START  (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_14_vpwr_line_stride_14_END    (9)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_14_vpwr_line_wrap_14_START    (15)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_14_vpwr_line_wrap_14_END      (28)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_14_UNION
 结构说明  : CVDR_VP_WR_PREFETCH_14 寄存器结构定义。地址偏移量:0x108，初值:0x00000D0C，宽度:32
 寄存器说明: Configure the prefetch mechanism and must be aligned with the SMMU configuration.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_index_id0_14       : 7;  /* bit[0-6]  : See previous definition on VP_WR_PREFETCH_0 */
        unsigned int  reserved_0              : 1;  /* bit[7-7]  :  */
        unsigned int  vpwr_index_id1_14       : 7;  /* bit[8-14] : See previous definition on VP_WR_PREFETCH_0 */
        unsigned int  reserved_1              : 16; /* bit[15-30]:  */
        unsigned int  vpwr_prefetch_bypass_14 : 1;  /* bit[31-31]: See previous definition on VP_WR_PREFETCH_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_14_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_14_vpwr_index_id0_14_START        (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_14_vpwr_index_id0_14_END          (6)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_14_vpwr_index_id1_14_START        (8)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_14_vpwr_index_id1_14_END          (14)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_14_vpwr_prefetch_bypass_14_START  (31)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_14_vpwr_prefetch_bypass_14_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_CFG_15_UNION
 结构说明  : CVDR_VP_WR_CFG_15 寄存器结构定义。地址偏移量:0x10C，初值:0x00000000，宽度:32
 寄存器说明: Video port write Configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_pixel_format_15    : 4;  /* bit[0-3]  : See previous definition on VP_WR_CFG_0 */
        unsigned int  vpwr_pixel_expansion_15 : 1;  /* bit[4-4]  : See previous definition on VP_WR_CFG_0 */
        unsigned int  reserved                : 10; /* bit[5-14] :  */
        unsigned int  vpwr_last_page_15       : 17; /* bit[15-31]: See previous definition on VP_WR_CFG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_CFG_15_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_15_vpwr_pixel_format_15_START     (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_15_vpwr_pixel_format_15_END       (3)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_15_vpwr_pixel_expansion_15_START  (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_15_vpwr_pixel_expansion_15_END    (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_15_vpwr_last_page_15_START        (15)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_15_vpwr_last_page_15_END          (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_15_UNION
 结构说明  : CVDR_VP_WR_AXI_FS_15 寄存器结构定义。地址偏移量:0x110，初值:0x00000000，宽度:32
 寄存器说明: AXI address Frame start
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved                    : 4;  /* bit[0-3] :  */
        unsigned int  vpwr_address_frame_start_15 : 28; /* bit[4-31]: See previous definition on VP_WR_AXI_FS_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_15_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_15_vpwr_address_frame_start_15_START  (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_15_vpwr_address_frame_start_15_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_15_UNION
 结构说明  : CVDR_VP_WR_AXI_LINE_15 寄存器结构定义。地址偏移量:0x114，初值:0x1FFF8000，宽度:32
 寄存器说明: AXI line wrap and line stride
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_line_stride_15 : 10; /* bit[0-9]  : See previous definition on VP_WR_AXI_LINE_0 */
        unsigned int  reserved_0          : 5;  /* bit[10-14]:  */
        unsigned int  vpwr_line_wrap_15   : 14; /* bit[15-28]: See previous definition on VP_WR_AXI_LINE_0 */
        unsigned int  reserved_1          : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_15_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_15_vpwr_line_stride_15_START  (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_15_vpwr_line_stride_15_END    (9)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_15_vpwr_line_wrap_15_START    (15)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_15_vpwr_line_wrap_15_END      (28)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_15_UNION
 结构说明  : CVDR_VP_WR_PREFETCH_15 寄存器结构定义。地址偏移量:0x118，初值:0x00000F0E，宽度:32
 寄存器说明: Configure the prefetch mechanism and must be aligned with the SMMU configuration.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_index_id0_15       : 7;  /* bit[0-6]  : See previous definition on VP_WR_PREFETCH_0 */
        unsigned int  reserved_0              : 1;  /* bit[7-7]  :  */
        unsigned int  vpwr_index_id1_15       : 7;  /* bit[8-14] : See previous definition on VP_WR_PREFETCH_0 */
        unsigned int  reserved_1              : 16; /* bit[15-30]:  */
        unsigned int  vpwr_prefetch_bypass_15 : 1;  /* bit[31-31]: See previous definition on VP_WR_PREFETCH_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_15_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_15_vpwr_index_id0_15_START        (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_15_vpwr_index_id0_15_END          (6)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_15_vpwr_index_id1_15_START        (8)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_15_vpwr_index_id1_15_END          (14)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_15_vpwr_prefetch_bypass_15_START  (31)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_15_vpwr_prefetch_bypass_15_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_CFG_16_UNION
 结构说明  : CVDR_VP_WR_CFG_16 寄存器结构定义。地址偏移量:0x11C，初值:0x00000000，宽度:32
 寄存器说明: Video port write Configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_pixel_format_16    : 4;  /* bit[0-3]  : See previous definition on VP_WR_CFG_0 */
        unsigned int  vpwr_pixel_expansion_16 : 1;  /* bit[4-4]  : See previous definition on VP_WR_CFG_0 */
        unsigned int  reserved                : 10; /* bit[5-14] :  */
        unsigned int  vpwr_last_page_16       : 17; /* bit[15-31]: See previous definition on VP_WR_CFG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_CFG_16_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_16_vpwr_pixel_format_16_START     (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_16_vpwr_pixel_format_16_END       (3)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_16_vpwr_pixel_expansion_16_START  (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_16_vpwr_pixel_expansion_16_END    (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_16_vpwr_last_page_16_START        (15)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_16_vpwr_last_page_16_END          (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_16_UNION
 结构说明  : CVDR_VP_WR_AXI_FS_16 寄存器结构定义。地址偏移量:0x120，初值:0x00000000，宽度:32
 寄存器说明: AXI address Frame start
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved                    : 4;  /* bit[0-3] :  */
        unsigned int  vpwr_address_frame_start_16 : 28; /* bit[4-31]: See previous definition on VP_WR_AXI_FS_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_16_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_16_vpwr_address_frame_start_16_START  (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_16_vpwr_address_frame_start_16_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_16_UNION
 结构说明  : CVDR_VP_WR_AXI_LINE_16 寄存器结构定义。地址偏移量:0x124，初值:0x1FFF8000，宽度:32
 寄存器说明: AXI line wrap and line stride
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_line_stride_16 : 10; /* bit[0-9]  : See previous definition on VP_WR_AXI_LINE_0 */
        unsigned int  reserved_0          : 5;  /* bit[10-14]:  */
        unsigned int  vpwr_line_wrap_16   : 14; /* bit[15-28]: See previous definition on VP_WR_AXI_LINE_0 */
        unsigned int  reserved_1          : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_16_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_16_vpwr_line_stride_16_START  (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_16_vpwr_line_stride_16_END    (9)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_16_vpwr_line_wrap_16_START    (15)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_16_vpwr_line_wrap_16_END      (28)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_16_UNION
 结构说明  : CVDR_VP_WR_PREFETCH_16 寄存器结构定义。地址偏移量:0x128，初值:0x00001110，宽度:32
 寄存器说明: Configure the prefetch mechanism and must be aligned with the SMMU configuration.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_index_id0_16       : 7;  /* bit[0-6]  : See previous definition on VP_WR_PREFETCH_0 */
        unsigned int  reserved_0              : 1;  /* bit[7-7]  :  */
        unsigned int  vpwr_index_id1_16       : 7;  /* bit[8-14] : See previous definition on VP_WR_PREFETCH_0 */
        unsigned int  reserved_1              : 16; /* bit[15-30]:  */
        unsigned int  vpwr_prefetch_bypass_16 : 1;  /* bit[31-31]: See previous definition on VP_WR_PREFETCH_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_16_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_16_vpwr_index_id0_16_START        (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_16_vpwr_index_id0_16_END          (6)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_16_vpwr_index_id1_16_START        (8)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_16_vpwr_index_id1_16_END          (14)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_16_vpwr_prefetch_bypass_16_START  (31)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_16_vpwr_prefetch_bypass_16_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_CFG_17_UNION
 结构说明  : CVDR_VP_WR_CFG_17 寄存器结构定义。地址偏移量:0x12C，初值:0x00000000，宽度:32
 寄存器说明: Video port write Configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_pixel_format_17    : 4;  /* bit[0-3]  : See previous definition on VP_WR_CFG_0 */
        unsigned int  vpwr_pixel_expansion_17 : 1;  /* bit[4-4]  : See previous definition on VP_WR_CFG_0 */
        unsigned int  reserved                : 10; /* bit[5-14] :  */
        unsigned int  vpwr_last_page_17       : 17; /* bit[15-31]: See previous definition on VP_WR_CFG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_CFG_17_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_17_vpwr_pixel_format_17_START     (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_17_vpwr_pixel_format_17_END       (3)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_17_vpwr_pixel_expansion_17_START  (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_17_vpwr_pixel_expansion_17_END    (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_17_vpwr_last_page_17_START        (15)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_17_vpwr_last_page_17_END          (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_17_UNION
 结构说明  : CVDR_VP_WR_AXI_FS_17 寄存器结构定义。地址偏移量:0x130，初值:0x00000000，宽度:32
 寄存器说明: AXI address Frame start
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved                    : 4;  /* bit[0-3] :  */
        unsigned int  vpwr_address_frame_start_17 : 28; /* bit[4-31]: See previous definition on VP_WR_AXI_FS_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_17_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_17_vpwr_address_frame_start_17_START  (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_17_vpwr_address_frame_start_17_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_17_UNION
 结构说明  : CVDR_VP_WR_AXI_LINE_17 寄存器结构定义。地址偏移量:0x134，初值:0x1FFF8000，宽度:32
 寄存器说明: AXI line wrap and line stride
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_line_stride_17 : 10; /* bit[0-9]  : See previous definition on VP_WR_AXI_LINE_0 */
        unsigned int  reserved_0          : 5;  /* bit[10-14]:  */
        unsigned int  vpwr_line_wrap_17   : 14; /* bit[15-28]: See previous definition on VP_WR_AXI_LINE_0 */
        unsigned int  reserved_1          : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_17_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_17_vpwr_line_stride_17_START  (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_17_vpwr_line_stride_17_END    (9)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_17_vpwr_line_wrap_17_START    (15)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_17_vpwr_line_wrap_17_END      (28)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_17_UNION
 结构说明  : CVDR_VP_WR_PREFETCH_17 寄存器结构定义。地址偏移量:0x138，初值:0x00001312，宽度:32
 寄存器说明: Configure the prefetch mechanism and must be aligned with the SMMU configuration.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_index_id0_17       : 7;  /* bit[0-6]  : See previous definition on VP_WR_PREFETCH_0 */
        unsigned int  reserved_0              : 1;  /* bit[7-7]  :  */
        unsigned int  vpwr_index_id1_17       : 7;  /* bit[8-14] : See previous definition on VP_WR_PREFETCH_0 */
        unsigned int  reserved_1              : 16; /* bit[15-30]:  */
        unsigned int  vpwr_prefetch_bypass_17 : 1;  /* bit[31-31]: See previous definition on VP_WR_PREFETCH_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_17_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_17_vpwr_index_id0_17_START        (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_17_vpwr_index_id0_17_END          (6)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_17_vpwr_index_id1_17_START        (8)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_17_vpwr_index_id1_17_END          (14)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_17_vpwr_prefetch_bypass_17_START  (31)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_17_vpwr_prefetch_bypass_17_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_CFG_18_UNION
 结构说明  : CVDR_VP_WR_CFG_18 寄存器结构定义。地址偏移量:0x13C，初值:0x00000000，宽度:32
 寄存器说明: Video port write Configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_pixel_format_18    : 4;  /* bit[0-3]  : See previous definition on VP_WR_CFG_0 */
        unsigned int  vpwr_pixel_expansion_18 : 1;  /* bit[4-4]  : See previous definition on VP_WR_CFG_0 */
        unsigned int  reserved                : 10; /* bit[5-14] :  */
        unsigned int  vpwr_last_page_18       : 17; /* bit[15-31]: See previous definition on VP_WR_CFG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_CFG_18_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_18_vpwr_pixel_format_18_START     (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_18_vpwr_pixel_format_18_END       (3)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_18_vpwr_pixel_expansion_18_START  (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_18_vpwr_pixel_expansion_18_END    (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_18_vpwr_last_page_18_START        (15)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_18_vpwr_last_page_18_END          (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_18_UNION
 结构说明  : CVDR_VP_WR_AXI_FS_18 寄存器结构定义。地址偏移量:0x140，初值:0x00000000，宽度:32
 寄存器说明: AXI address Frame start
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved                    : 4;  /* bit[0-3] :  */
        unsigned int  vpwr_address_frame_start_18 : 28; /* bit[4-31]: See previous definition on VP_WR_AXI_FS_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_18_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_18_vpwr_address_frame_start_18_START  (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_18_vpwr_address_frame_start_18_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_18_UNION
 结构说明  : CVDR_VP_WR_AXI_LINE_18 寄存器结构定义。地址偏移量:0x144，初值:0x1FFF8000，宽度:32
 寄存器说明: AXI line wrap and line stride
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_line_stride_18 : 10; /* bit[0-9]  : See previous definition on VP_WR_AXI_LINE_0 */
        unsigned int  reserved_0          : 5;  /* bit[10-14]:  */
        unsigned int  vpwr_line_wrap_18   : 14; /* bit[15-28]: See previous definition on VP_WR_AXI_LINE_0 */
        unsigned int  reserved_1          : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_18_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_18_vpwr_line_stride_18_START  (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_18_vpwr_line_stride_18_END    (9)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_18_vpwr_line_wrap_18_START    (15)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_18_vpwr_line_wrap_18_END      (28)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_18_UNION
 结构说明  : CVDR_VP_WR_PREFETCH_18 寄存器结构定义。地址偏移量:0x148，初值:0x00001514，宽度:32
 寄存器说明: Configure the prefetch mechanism and must be aligned with the SMMU configuration.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_index_id0_18       : 7;  /* bit[0-6]  : See previous definition on VP_WR_PREFETCH_0 */
        unsigned int  reserved_0              : 1;  /* bit[7-7]  :  */
        unsigned int  vpwr_index_id1_18       : 7;  /* bit[8-14] : See previous definition on VP_WR_PREFETCH_0 */
        unsigned int  reserved_1              : 16; /* bit[15-30]:  */
        unsigned int  vpwr_prefetch_bypass_18 : 1;  /* bit[31-31]: See previous definition on VP_WR_PREFETCH_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_18_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_18_vpwr_index_id0_18_START        (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_18_vpwr_index_id0_18_END          (6)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_18_vpwr_index_id1_18_START        (8)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_18_vpwr_index_id1_18_END          (14)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_18_vpwr_prefetch_bypass_18_START  (31)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_18_vpwr_prefetch_bypass_18_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_CFG_19_UNION
 结构说明  : CVDR_VP_WR_CFG_19 寄存器结构定义。地址偏移量:0x14C，初值:0x00000000，宽度:32
 寄存器说明: Video port write Configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_pixel_format_19    : 4;  /* bit[0-3]  : See previous definition on VP_WR_CFG_0 */
        unsigned int  vpwr_pixel_expansion_19 : 1;  /* bit[4-4]  : See previous definition on VP_WR_CFG_0 */
        unsigned int  reserved                : 10; /* bit[5-14] :  */
        unsigned int  vpwr_last_page_19       : 17; /* bit[15-31]: See previous definition on VP_WR_CFG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_CFG_19_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_19_vpwr_pixel_format_19_START     (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_19_vpwr_pixel_format_19_END       (3)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_19_vpwr_pixel_expansion_19_START  (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_19_vpwr_pixel_expansion_19_END    (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_19_vpwr_last_page_19_START        (15)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_19_vpwr_last_page_19_END          (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_19_UNION
 结构说明  : CVDR_VP_WR_AXI_FS_19 寄存器结构定义。地址偏移量:0x150，初值:0x00000000，宽度:32
 寄存器说明: AXI address Frame start
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved                    : 4;  /* bit[0-3] :  */
        unsigned int  vpwr_address_frame_start_19 : 28; /* bit[4-31]: See previous definition on VP_WR_AXI_FS_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_19_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_19_vpwr_address_frame_start_19_START  (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_19_vpwr_address_frame_start_19_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_19_UNION
 结构说明  : CVDR_VP_WR_AXI_LINE_19 寄存器结构定义。地址偏移量:0x154，初值:0x1FFF8000，宽度:32
 寄存器说明: AXI line wrap and line stride
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_line_stride_19 : 10; /* bit[0-9]  : See previous definition on VP_WR_AXI_LINE_0 */
        unsigned int  reserved_0          : 5;  /* bit[10-14]:  */
        unsigned int  vpwr_line_wrap_19   : 14; /* bit[15-28]: See previous definition on VP_WR_AXI_LINE_0 */
        unsigned int  reserved_1          : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_19_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_19_vpwr_line_stride_19_START  (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_19_vpwr_line_stride_19_END    (9)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_19_vpwr_line_wrap_19_START    (15)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_19_vpwr_line_wrap_19_END      (28)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_19_UNION
 结构说明  : CVDR_VP_WR_PREFETCH_19 寄存器结构定义。地址偏移量:0x158，初值:0x00001716，宽度:32
 寄存器说明: Configure the prefetch mechanism and must be aligned with the SMMU configuration.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_index_id0_19       : 7;  /* bit[0-6]  : See previous definition on VP_WR_PREFETCH_0 */
        unsigned int  reserved_0              : 1;  /* bit[7-7]  :  */
        unsigned int  vpwr_index_id1_19       : 7;  /* bit[8-14] : See previous definition on VP_WR_PREFETCH_0 */
        unsigned int  reserved_1              : 16; /* bit[15-30]:  */
        unsigned int  vpwr_prefetch_bypass_19 : 1;  /* bit[31-31]: See previous definition on VP_WR_PREFETCH_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_19_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_19_vpwr_index_id0_19_START        (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_19_vpwr_index_id0_19_END          (6)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_19_vpwr_index_id1_19_START        (8)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_19_vpwr_index_id1_19_END          (14)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_19_vpwr_prefetch_bypass_19_START  (31)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_19_vpwr_prefetch_bypass_19_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_CFG_20_UNION
 结构说明  : CVDR_VP_WR_CFG_20 寄存器结构定义。地址偏移量:0x15C，初值:0x00000000，宽度:32
 寄存器说明: Video port write Configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_pixel_format_20    : 4;  /* bit[0-3]  : See previous definition on VP_WR_CFG_0 */
        unsigned int  vpwr_pixel_expansion_20 : 1;  /* bit[4-4]  : See previous definition on VP_WR_CFG_0 */
        unsigned int  reserved                : 10; /* bit[5-14] :  */
        unsigned int  vpwr_last_page_20       : 17; /* bit[15-31]: See previous definition on VP_WR_CFG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_CFG_20_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_20_vpwr_pixel_format_20_START     (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_20_vpwr_pixel_format_20_END       (3)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_20_vpwr_pixel_expansion_20_START  (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_20_vpwr_pixel_expansion_20_END    (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_20_vpwr_last_page_20_START        (15)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_20_vpwr_last_page_20_END          (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_20_UNION
 结构说明  : CVDR_VP_WR_AXI_FS_20 寄存器结构定义。地址偏移量:0x160，初值:0x00000000，宽度:32
 寄存器说明: AXI address Frame start
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved                    : 4;  /* bit[0-3] :  */
        unsigned int  vpwr_address_frame_start_20 : 28; /* bit[4-31]: See previous definition on VP_WR_AXI_FS_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_20_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_20_vpwr_address_frame_start_20_START  (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_20_vpwr_address_frame_start_20_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_20_UNION
 结构说明  : CVDR_VP_WR_AXI_LINE_20 寄存器结构定义。地址偏移量:0x164，初值:0x1FFF8000，宽度:32
 寄存器说明: AXI line wrap and line stride
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_line_stride_20 : 10; /* bit[0-9]  : See previous definition on VP_WR_AXI_LINE_0 */
        unsigned int  reserved_0          : 5;  /* bit[10-14]:  */
        unsigned int  vpwr_line_wrap_20   : 14; /* bit[15-28]: See previous definition on VP_WR_AXI_LINE_0 */
        unsigned int  reserved_1          : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_20_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_20_vpwr_line_stride_20_START  (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_20_vpwr_line_stride_20_END    (9)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_20_vpwr_line_wrap_20_START    (15)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_20_vpwr_line_wrap_20_END      (28)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_20_UNION
 结构说明  : CVDR_VP_WR_PREFETCH_20 寄存器结构定义。地址偏移量:0x168，初值:0x00001918，宽度:32
 寄存器说明: Configure the prefetch mechanism and must be aligned with the SMMU configuration.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_index_id0_20       : 7;  /* bit[0-6]  : See previous definition on VP_WR_PREFETCH_0 */
        unsigned int  reserved_0              : 1;  /* bit[7-7]  :  */
        unsigned int  vpwr_index_id1_20       : 7;  /* bit[8-14] : See previous definition on VP_WR_PREFETCH_0 */
        unsigned int  reserved_1              : 16; /* bit[15-30]:  */
        unsigned int  vpwr_prefetch_bypass_20 : 1;  /* bit[31-31]: See previous definition on VP_WR_PREFETCH_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_20_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_20_vpwr_index_id0_20_START        (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_20_vpwr_index_id0_20_END          (6)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_20_vpwr_index_id1_20_START        (8)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_20_vpwr_index_id1_20_END          (14)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_20_vpwr_prefetch_bypass_20_START  (31)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_20_vpwr_prefetch_bypass_20_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_CFG_21_UNION
 结构说明  : CVDR_VP_WR_CFG_21 寄存器结构定义。地址偏移量:0x16C，初值:0x00000000，宽度:32
 寄存器说明: Video port write Configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_pixel_format_21    : 4;  /* bit[0-3]  : See previous definition on VP_WR_CFG_0 */
        unsigned int  vpwr_pixel_expansion_21 : 1;  /* bit[4-4]  : See previous definition on VP_WR_CFG_0 */
        unsigned int  reserved                : 10; /* bit[5-14] :  */
        unsigned int  vpwr_last_page_21       : 17; /* bit[15-31]: See previous definition on VP_WR_CFG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_CFG_21_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_21_vpwr_pixel_format_21_START     (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_21_vpwr_pixel_format_21_END       (3)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_21_vpwr_pixel_expansion_21_START  (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_21_vpwr_pixel_expansion_21_END    (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_21_vpwr_last_page_21_START        (15)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_21_vpwr_last_page_21_END          (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_21_UNION
 结构说明  : CVDR_VP_WR_AXI_FS_21 寄存器结构定义。地址偏移量:0x170，初值:0x00000000，宽度:32
 寄存器说明: AXI address Frame start
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved                    : 4;  /* bit[0-3] :  */
        unsigned int  vpwr_address_frame_start_21 : 28; /* bit[4-31]: See previous definition on VP_WR_AXI_FS_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_21_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_21_vpwr_address_frame_start_21_START  (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_21_vpwr_address_frame_start_21_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_21_UNION
 结构说明  : CVDR_VP_WR_AXI_LINE_21 寄存器结构定义。地址偏移量:0x174，初值:0x1FFF8000，宽度:32
 寄存器说明: AXI line wrap and line stride
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_line_stride_21 : 10; /* bit[0-9]  : See previous definition on VP_WR_AXI_LINE_0 */
        unsigned int  reserved_0          : 5;  /* bit[10-14]:  */
        unsigned int  vpwr_line_wrap_21   : 14; /* bit[15-28]: See previous definition on VP_WR_AXI_LINE_0 */
        unsigned int  reserved_1          : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_21_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_21_vpwr_line_stride_21_START  (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_21_vpwr_line_stride_21_END    (9)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_21_vpwr_line_wrap_21_START    (15)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_21_vpwr_line_wrap_21_END      (28)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_21_UNION
 结构说明  : CVDR_VP_WR_PREFETCH_21 寄存器结构定义。地址偏移量:0x178，初值:0x00001B1A，宽度:32
 寄存器说明: Configure the prefetch mechanism and must be aligned with the SMMU configuration.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_index_id0_21       : 7;  /* bit[0-6]  : See previous definition on VP_WR_PREFETCH_0 */
        unsigned int  reserved_0              : 1;  /* bit[7-7]  :  */
        unsigned int  vpwr_index_id1_21       : 7;  /* bit[8-14] : See previous definition on VP_WR_PREFETCH_0 */
        unsigned int  reserved_1              : 16; /* bit[15-30]:  */
        unsigned int  vpwr_prefetch_bypass_21 : 1;  /* bit[31-31]: See previous definition on VP_WR_PREFETCH_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_21_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_21_vpwr_index_id0_21_START        (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_21_vpwr_index_id0_21_END          (6)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_21_vpwr_index_id1_21_START        (8)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_21_vpwr_index_id1_21_END          (14)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_21_vpwr_prefetch_bypass_21_START  (31)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_21_vpwr_prefetch_bypass_21_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_CFG_22_UNION
 结构说明  : CVDR_VP_WR_CFG_22 寄存器结构定义。地址偏移量:0x17C，初值:0x00000000，宽度:32
 寄存器说明: Video port write Configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_pixel_format_22    : 4;  /* bit[0-3]  : See previous definition on VP_WR_CFG_0 */
        unsigned int  vpwr_pixel_expansion_22 : 1;  /* bit[4-4]  : See previous definition on VP_WR_CFG_0 */
        unsigned int  reserved                : 10; /* bit[5-14] :  */
        unsigned int  vpwr_last_page_22       : 17; /* bit[15-31]: See previous definition on VP_WR_CFG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_CFG_22_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_22_vpwr_pixel_format_22_START     (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_22_vpwr_pixel_format_22_END       (3)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_22_vpwr_pixel_expansion_22_START  (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_22_vpwr_pixel_expansion_22_END    (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_22_vpwr_last_page_22_START        (15)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_22_vpwr_last_page_22_END          (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_22_UNION
 结构说明  : CVDR_VP_WR_AXI_FS_22 寄存器结构定义。地址偏移量:0x180，初值:0x00000000，宽度:32
 寄存器说明: AXI address Frame start
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved                    : 4;  /* bit[0-3] :  */
        unsigned int  vpwr_address_frame_start_22 : 28; /* bit[4-31]: See previous definition on VP_WR_AXI_FS_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_22_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_22_vpwr_address_frame_start_22_START  (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_22_vpwr_address_frame_start_22_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_22_UNION
 结构说明  : CVDR_VP_WR_AXI_LINE_22 寄存器结构定义。地址偏移量:0x184，初值:0x1FFF8000，宽度:32
 寄存器说明: AXI line wrap and line stride
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_line_stride_22 : 10; /* bit[0-9]  : See previous definition on VP_WR_AXI_LINE_0 */
        unsigned int  reserved_0          : 5;  /* bit[10-14]:  */
        unsigned int  vpwr_line_wrap_22   : 14; /* bit[15-28]: See previous definition on VP_WR_AXI_LINE_0 */
        unsigned int  reserved_1          : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_22_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_22_vpwr_line_stride_22_START  (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_22_vpwr_line_stride_22_END    (9)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_22_vpwr_line_wrap_22_START    (15)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_22_vpwr_line_wrap_22_END      (28)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_22_UNION
 结构说明  : CVDR_VP_WR_PREFETCH_22 寄存器结构定义。地址偏移量:0x188，初值:0x00001D1C，宽度:32
 寄存器说明: Configure the prefetch mechanism and must be aligned with the SMMU configuration.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_index_id0_22       : 7;  /* bit[0-6]  : See previous definition on VP_WR_PREFETCH_0 */
        unsigned int  reserved_0              : 1;  /* bit[7-7]  :  */
        unsigned int  vpwr_index_id1_22       : 7;  /* bit[8-14] : See previous definition on VP_WR_PREFETCH_0 */
        unsigned int  reserved_1              : 16; /* bit[15-30]:  */
        unsigned int  vpwr_prefetch_bypass_22 : 1;  /* bit[31-31]: See previous definition on VP_WR_PREFETCH_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_22_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_22_vpwr_index_id0_22_START        (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_22_vpwr_index_id0_22_END          (6)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_22_vpwr_index_id1_22_START        (8)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_22_vpwr_index_id1_22_END          (14)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_22_vpwr_prefetch_bypass_22_START  (31)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_22_vpwr_prefetch_bypass_22_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_CFG_23_UNION
 结构说明  : CVDR_VP_WR_CFG_23 寄存器结构定义。地址偏移量:0x18C，初值:0x00000000，宽度:32
 寄存器说明: Video port write Configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_pixel_format_23    : 4;  /* bit[0-3]  : See previous definition on VP_WR_CFG_0 */
        unsigned int  vpwr_pixel_expansion_23 : 1;  /* bit[4-4]  : See previous definition on VP_WR_CFG_0 */
        unsigned int  reserved                : 10; /* bit[5-14] :  */
        unsigned int  vpwr_last_page_23       : 17; /* bit[15-31]: See previous definition on VP_WR_CFG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_CFG_23_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_23_vpwr_pixel_format_23_START     (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_23_vpwr_pixel_format_23_END       (3)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_23_vpwr_pixel_expansion_23_START  (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_23_vpwr_pixel_expansion_23_END    (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_23_vpwr_last_page_23_START        (15)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_23_vpwr_last_page_23_END          (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_23_UNION
 结构说明  : CVDR_VP_WR_AXI_FS_23 寄存器结构定义。地址偏移量:0x190，初值:0x00000000，宽度:32
 寄存器说明: AXI address Frame start
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved                    : 4;  /* bit[0-3] :  */
        unsigned int  vpwr_address_frame_start_23 : 28; /* bit[4-31]: See previous definition on VP_WR_AXI_FS_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_23_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_23_vpwr_address_frame_start_23_START  (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_23_vpwr_address_frame_start_23_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_23_UNION
 结构说明  : CVDR_VP_WR_AXI_LINE_23 寄存器结构定义。地址偏移量:0x194，初值:0x1FFF8000，宽度:32
 寄存器说明: AXI line wrap and line stride
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_line_stride_23 : 10; /* bit[0-9]  : See previous definition on VP_WR_AXI_LINE_0 */
        unsigned int  reserved_0          : 5;  /* bit[10-14]:  */
        unsigned int  vpwr_line_wrap_23   : 14; /* bit[15-28]: See previous definition on VP_WR_AXI_LINE_0 */
        unsigned int  reserved_1          : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_23_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_23_vpwr_line_stride_23_START  (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_23_vpwr_line_stride_23_END    (9)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_23_vpwr_line_wrap_23_START    (15)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_23_vpwr_line_wrap_23_END      (28)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_23_UNION
 结构说明  : CVDR_VP_WR_PREFETCH_23 寄存器结构定义。地址偏移量:0x198，初值:0x00001F1E，宽度:32
 寄存器说明: Configure the prefetch mechanism and must be aligned with the SMMU configuration.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_index_id0_23       : 7;  /* bit[0-6]  : See previous definition on VP_WR_PREFETCH_0 */
        unsigned int  reserved_0              : 1;  /* bit[7-7]  :  */
        unsigned int  vpwr_index_id1_23       : 7;  /* bit[8-14] : See previous definition on VP_WR_PREFETCH_0 */
        unsigned int  reserved_1              : 16; /* bit[15-30]:  */
        unsigned int  vpwr_prefetch_bypass_23 : 1;  /* bit[31-31]: See previous definition on VP_WR_PREFETCH_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_23_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_23_vpwr_index_id0_23_START        (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_23_vpwr_index_id0_23_END          (6)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_23_vpwr_index_id1_23_START        (8)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_23_vpwr_index_id1_23_END          (14)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_23_vpwr_prefetch_bypass_23_START  (31)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_23_vpwr_prefetch_bypass_23_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_CFG_24_UNION
 结构说明  : CVDR_VP_WR_CFG_24 寄存器结构定义。地址偏移量:0x19C，初值:0x00000000，宽度:32
 寄存器说明: Video port write Configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_pixel_format_24    : 4;  /* bit[0-3]  : See previous definition on VP_WR_CFG_0 */
        unsigned int  vpwr_pixel_expansion_24 : 1;  /* bit[4-4]  : See previous definition on VP_WR_CFG_0 */
        unsigned int  reserved                : 10; /* bit[5-14] :  */
        unsigned int  vpwr_last_page_24       : 17; /* bit[15-31]: See previous definition on VP_WR_CFG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_CFG_24_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_24_vpwr_pixel_format_24_START     (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_24_vpwr_pixel_format_24_END       (3)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_24_vpwr_pixel_expansion_24_START  (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_24_vpwr_pixel_expansion_24_END    (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_24_vpwr_last_page_24_START        (15)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_24_vpwr_last_page_24_END          (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_24_UNION
 结构说明  : CVDR_VP_WR_AXI_FS_24 寄存器结构定义。地址偏移量:0x1A0，初值:0x00000000，宽度:32
 寄存器说明: AXI address Frame start
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved                    : 4;  /* bit[0-3] :  */
        unsigned int  vpwr_address_frame_start_24 : 28; /* bit[4-31]: See previous definition on VP_WR_AXI_FS_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_24_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_24_vpwr_address_frame_start_24_START  (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_24_vpwr_address_frame_start_24_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_24_UNION
 结构说明  : CVDR_VP_WR_AXI_LINE_24 寄存器结构定义。地址偏移量:0x1A4，初值:0x1FFF8000，宽度:32
 寄存器说明: AXI line wrap and line stride
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_line_stride_24 : 10; /* bit[0-9]  : See previous definition on VP_WR_AXI_LINE_0 */
        unsigned int  reserved_0          : 5;  /* bit[10-14]:  */
        unsigned int  vpwr_line_wrap_24   : 14; /* bit[15-28]: See previous definition on VP_WR_AXI_LINE_0 */
        unsigned int  reserved_1          : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_24_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_24_vpwr_line_stride_24_START  (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_24_vpwr_line_stride_24_END    (9)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_24_vpwr_line_wrap_24_START    (15)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_24_vpwr_line_wrap_24_END      (28)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_24_UNION
 结构说明  : CVDR_VP_WR_PREFETCH_24 寄存器结构定义。地址偏移量:0x1A8，初值:0x00002120，宽度:32
 寄存器说明: Configure the prefetch mechanism and must be aligned with the SMMU configuration.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_index_id0_24       : 7;  /* bit[0-6]  : See previous definition on VP_WR_PREFETCH_0 */
        unsigned int  reserved_0              : 1;  /* bit[7-7]  :  */
        unsigned int  vpwr_index_id1_24       : 7;  /* bit[8-14] : See previous definition on VP_WR_PREFETCH_0 */
        unsigned int  reserved_1              : 16; /* bit[15-30]:  */
        unsigned int  vpwr_prefetch_bypass_24 : 1;  /* bit[31-31]: See previous definition on VP_WR_PREFETCH_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_24_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_24_vpwr_index_id0_24_START        (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_24_vpwr_index_id0_24_END          (6)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_24_vpwr_index_id1_24_START        (8)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_24_vpwr_index_id1_24_END          (14)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_24_vpwr_prefetch_bypass_24_START  (31)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_24_vpwr_prefetch_bypass_24_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_CFG_25_UNION
 结构说明  : CVDR_VP_WR_CFG_25 寄存器结构定义。地址偏移量:0x1AC，初值:0x00000000，宽度:32
 寄存器说明: Video port write Configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_pixel_format_25    : 4;  /* bit[0-3]  : See previous definition on VP_WR_CFG_0 */
        unsigned int  vpwr_pixel_expansion_25 : 1;  /* bit[4-4]  : See previous definition on VP_WR_CFG_0 */
        unsigned int  reserved                : 10; /* bit[5-14] :  */
        unsigned int  vpwr_last_page_25       : 17; /* bit[15-31]: See previous definition on VP_WR_CFG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_CFG_25_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_25_vpwr_pixel_format_25_START     (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_25_vpwr_pixel_format_25_END       (3)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_25_vpwr_pixel_expansion_25_START  (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_25_vpwr_pixel_expansion_25_END    (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_25_vpwr_last_page_25_START        (15)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_25_vpwr_last_page_25_END          (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_25_UNION
 结构说明  : CVDR_VP_WR_AXI_FS_25 寄存器结构定义。地址偏移量:0x1B0，初值:0x00000000，宽度:32
 寄存器说明: AXI address Frame start
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved                    : 4;  /* bit[0-3] :  */
        unsigned int  vpwr_address_frame_start_25 : 28; /* bit[4-31]: See previous definition on VP_WR_AXI_FS_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_25_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_25_vpwr_address_frame_start_25_START  (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_25_vpwr_address_frame_start_25_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_25_UNION
 结构说明  : CVDR_VP_WR_AXI_LINE_25 寄存器结构定义。地址偏移量:0x1B4，初值:0x1FFF8000，宽度:32
 寄存器说明: AXI line wrap and line stride
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_line_stride_25 : 10; /* bit[0-9]  : See previous definition on VP_WR_AXI_LINE_0 */
        unsigned int  reserved_0          : 5;  /* bit[10-14]:  */
        unsigned int  vpwr_line_wrap_25   : 14; /* bit[15-28]: See previous definition on VP_WR_AXI_LINE_0 */
        unsigned int  reserved_1          : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_25_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_25_vpwr_line_stride_25_START  (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_25_vpwr_line_stride_25_END    (9)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_25_vpwr_line_wrap_25_START    (15)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_25_vpwr_line_wrap_25_END      (28)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_25_UNION
 结构说明  : CVDR_VP_WR_PREFETCH_25 寄存器结构定义。地址偏移量:0x1B8，初值:0x00002322，宽度:32
 寄存器说明: Configure the prefetch mechanism and must be aligned with the SMMU configuration.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_index_id0_25       : 7;  /* bit[0-6]  : See previous definition on VP_WR_PREFETCH_0 */
        unsigned int  reserved_0              : 1;  /* bit[7-7]  :  */
        unsigned int  vpwr_index_id1_25       : 7;  /* bit[8-14] : See previous definition on VP_WR_PREFETCH_0 */
        unsigned int  reserved_1              : 16; /* bit[15-30]:  */
        unsigned int  vpwr_prefetch_bypass_25 : 1;  /* bit[31-31]: See previous definition on VP_WR_PREFETCH_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_25_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_25_vpwr_index_id0_25_START        (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_25_vpwr_index_id0_25_END          (6)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_25_vpwr_index_id1_25_START        (8)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_25_vpwr_index_id1_25_END          (14)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_25_vpwr_prefetch_bypass_25_START  (31)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_25_vpwr_prefetch_bypass_25_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_CFG_26_UNION
 结构说明  : CVDR_VP_WR_CFG_26 寄存器结构定义。地址偏移量:0x1BC，初值:0x00000000，宽度:32
 寄存器说明: Video port write Configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_pixel_format_26    : 4;  /* bit[0-3]  : See previous definition on VP_WR_CFG_0 */
        unsigned int  vpwr_pixel_expansion_26 : 1;  /* bit[4-4]  : See previous definition on VP_WR_CFG_0 */
        unsigned int  reserved                : 10; /* bit[5-14] :  */
        unsigned int  vpwr_last_page_26       : 17; /* bit[15-31]: See previous definition on VP_WR_CFG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_CFG_26_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_26_vpwr_pixel_format_26_START     (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_26_vpwr_pixel_format_26_END       (3)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_26_vpwr_pixel_expansion_26_START  (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_26_vpwr_pixel_expansion_26_END    (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_26_vpwr_last_page_26_START        (15)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_26_vpwr_last_page_26_END          (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_26_UNION
 结构说明  : CVDR_VP_WR_AXI_FS_26 寄存器结构定义。地址偏移量:0x1C0，初值:0x00000000，宽度:32
 寄存器说明: AXI address Frame start
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved                    : 4;  /* bit[0-3] :  */
        unsigned int  vpwr_address_frame_start_26 : 28; /* bit[4-31]: See previous definition on VP_WR_AXI_FS_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_26_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_26_vpwr_address_frame_start_26_START  (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_26_vpwr_address_frame_start_26_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_26_UNION
 结构说明  : CVDR_VP_WR_AXI_LINE_26 寄存器结构定义。地址偏移量:0x1C4，初值:0x1FFF8000，宽度:32
 寄存器说明: AXI line wrap and line stride
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_line_stride_26 : 10; /* bit[0-9]  : See previous definition on VP_WR_AXI_LINE_0 */
        unsigned int  reserved_0          : 5;  /* bit[10-14]:  */
        unsigned int  vpwr_line_wrap_26   : 14; /* bit[15-28]: See previous definition on VP_WR_AXI_LINE_0 */
        unsigned int  reserved_1          : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_26_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_26_vpwr_line_stride_26_START  (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_26_vpwr_line_stride_26_END    (9)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_26_vpwr_line_wrap_26_START    (15)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_26_vpwr_line_wrap_26_END      (28)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_26_UNION
 结构说明  : CVDR_VP_WR_PREFETCH_26 寄存器结构定义。地址偏移量:0x1C8，初值:0x00002524，宽度:32
 寄存器说明: Configure the prefetch mechanism and must be aligned with the SMMU configuration.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_index_id0_26       : 7;  /* bit[0-6]  : See previous definition on VP_WR_PREFETCH_0 */
        unsigned int  reserved_0              : 1;  /* bit[7-7]  :  */
        unsigned int  vpwr_index_id1_26       : 7;  /* bit[8-14] : See previous definition on VP_WR_PREFETCH_0 */
        unsigned int  reserved_1              : 16; /* bit[15-30]:  */
        unsigned int  vpwr_prefetch_bypass_26 : 1;  /* bit[31-31]: See previous definition on VP_WR_PREFETCH_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_26_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_26_vpwr_index_id0_26_START        (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_26_vpwr_index_id0_26_END          (6)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_26_vpwr_index_id1_26_START        (8)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_26_vpwr_index_id1_26_END          (14)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_26_vpwr_prefetch_bypass_26_START  (31)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_26_vpwr_prefetch_bypass_26_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_CFG_27_UNION
 结构说明  : CVDR_VP_WR_CFG_27 寄存器结构定义。地址偏移量:0x1CC，初值:0x00000000，宽度:32
 寄存器说明: Video port write Configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_pixel_format_27    : 4;  /* bit[0-3]  : See previous definition on VP_WR_CFG_0 */
        unsigned int  vpwr_pixel_expansion_27 : 1;  /* bit[4-4]  : See previous definition on VP_WR_CFG_0 */
        unsigned int  reserved                : 10; /* bit[5-14] :  */
        unsigned int  vpwr_last_page_27       : 17; /* bit[15-31]: See previous definition on VP_WR_CFG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_CFG_27_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_27_vpwr_pixel_format_27_START     (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_27_vpwr_pixel_format_27_END       (3)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_27_vpwr_pixel_expansion_27_START  (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_27_vpwr_pixel_expansion_27_END    (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_27_vpwr_last_page_27_START        (15)
#define SOC_ISP_CVDR_CVDR_VP_WR_CFG_27_vpwr_last_page_27_END          (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_27_UNION
 结构说明  : CVDR_VP_WR_AXI_FS_27 寄存器结构定义。地址偏移量:0x1D0，初值:0x00000000，宽度:32
 寄存器说明: AXI address Frame start
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved                    : 4;  /* bit[0-3] :  */
        unsigned int  vpwr_address_frame_start_27 : 28; /* bit[4-31]: See previous definition on VP_WR_AXI_FS_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_27_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_27_vpwr_address_frame_start_27_START  (4)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_FS_27_vpwr_address_frame_start_27_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_27_UNION
 结构说明  : CVDR_VP_WR_AXI_LINE_27 寄存器结构定义。地址偏移量:0x1D4，初值:0x1FFF8000，宽度:32
 寄存器说明: AXI line wrap and line stride
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_line_stride_27 : 10; /* bit[0-9]  : See previous definition on VP_WR_AXI_LINE_0 */
        unsigned int  reserved_0          : 5;  /* bit[10-14]:  */
        unsigned int  vpwr_line_wrap_27   : 14; /* bit[15-28]: See previous definition on VP_WR_AXI_LINE_0 */
        unsigned int  reserved_1          : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_27_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_27_vpwr_line_stride_27_START  (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_27_vpwr_line_stride_27_END    (9)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_27_vpwr_line_wrap_27_START    (15)
#define SOC_ISP_CVDR_CVDR_VP_WR_AXI_LINE_27_vpwr_line_wrap_27_END      (28)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_27_UNION
 结构说明  : CVDR_VP_WR_PREFETCH_27 寄存器结构定义。地址偏移量:0x1D8，初值:0x00002726，宽度:32
 寄存器说明: Configure the prefetch mechanism and must be aligned with the SMMU configuration.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_index_id0_27       : 7;  /* bit[0-6]  : See previous definition on VP_WR_PREFETCH_0 */
        unsigned int  reserved_0              : 1;  /* bit[7-7]  :  */
        unsigned int  vpwr_index_id1_27       : 7;  /* bit[8-14] : See previous definition on VP_WR_PREFETCH_0 */
        unsigned int  reserved_1              : 16; /* bit[15-30]:  */
        unsigned int  vpwr_prefetch_bypass_27 : 1;  /* bit[31-31]: See previous definition on VP_WR_PREFETCH_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_27_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_27_vpwr_index_id0_27_START        (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_27_vpwr_index_id0_27_END          (6)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_27_vpwr_index_id1_27_START        (8)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_27_vpwr_index_id1_27_END          (14)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_27_vpwr_prefetch_bypass_27_START  (31)
#define SOC_ISP_CVDR_CVDR_VP_WR_PREFETCH_27_vpwr_prefetch_bypass_27_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_0_UNION
 结构说明  : CVDR_LIMITER_VP_WR_0 寄存器结构定义。地址偏移量:0x400，初值:0x0F00FFFF，宽度:32
 寄存器说明: Video port write Access limiter
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_access_limiter_0_0      : 4;  /* bit[0-3]  : "CVDR RAM access limiter: maximum number of 128 bit write accesses allowed on a 32 clock cycle windowReturnToLine0: 0 access allowed (unexpected in regular SW)ReturnToLine1: 1 access maximum allowedReturnToLineand so onReturnToLine15: 15 accesses maximum allowed" */
        unsigned int  vpwr_access_limiter_1_0      : 4;  /* bit[4-7]  : see description of access_limiter_0 */
        unsigned int  vpwr_access_limiter_2_0      : 4;  /* bit[8-11] : see description of access_limiter_0 */
        unsigned int  vpwr_access_limiter_3_0      : 4;  /* bit[12-15]: see description of access_limiter_0 */
        unsigned int  reserved_0                   : 8;  /* bit[16-23]:  */
        unsigned int  vpwr_access_limiter_reload_0 : 4;  /* bit[24-27]: "Access limiter reload functionality: controls the throughput available for a given initiator over 128 cycles.ReturnToLineWhen 0xF */
        unsigned int  reserved_1                   : 4;  /* bit[28-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_0_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_0_vpwr_access_limiter_0_0_START       (0)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_0_vpwr_access_limiter_0_0_END         (3)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_0_vpwr_access_limiter_1_0_START       (4)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_0_vpwr_access_limiter_1_0_END         (7)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_0_vpwr_access_limiter_2_0_START       (8)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_0_vpwr_access_limiter_2_0_END         (11)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_0_vpwr_access_limiter_3_0_START       (12)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_0_vpwr_access_limiter_3_0_END         (15)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_0_vpwr_access_limiter_reload_0_START  (24)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_0_vpwr_access_limiter_reload_0_END    (27)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_1_UNION
 结构说明  : CVDR_LIMITER_VP_WR_1 寄存器结构定义。地址偏移量:0x404，初值:0x0F00FFFF，宽度:32
 寄存器说明: Video port write Access limiter
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_access_limiter_0_1      : 4;  /* bit[0-3]  : See previous definition on LIMITER_VP_WR_0 */
        unsigned int  vpwr_access_limiter_1_1      : 4;  /* bit[4-7]  : See previous definition on LIMITER_VP_WR_0 */
        unsigned int  vpwr_access_limiter_2_1      : 4;  /* bit[8-11] : See previous definition on LIMITER_VP_WR_0 */
        unsigned int  vpwr_access_limiter_3_1      : 4;  /* bit[12-15]: See previous definition on LIMITER_VP_WR_0 */
        unsigned int  reserved_0                   : 8;  /* bit[16-23]:  */
        unsigned int  vpwr_access_limiter_reload_1 : 4;  /* bit[24-27]: See previous definition on LIMITER_VP_WR_0 */
        unsigned int  reserved_1                   : 4;  /* bit[28-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_1_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_1_vpwr_access_limiter_0_1_START       (0)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_1_vpwr_access_limiter_0_1_END         (3)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_1_vpwr_access_limiter_1_1_START       (4)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_1_vpwr_access_limiter_1_1_END         (7)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_1_vpwr_access_limiter_2_1_START       (8)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_1_vpwr_access_limiter_2_1_END         (11)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_1_vpwr_access_limiter_3_1_START       (12)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_1_vpwr_access_limiter_3_1_END         (15)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_1_vpwr_access_limiter_reload_1_START  (24)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_1_vpwr_access_limiter_reload_1_END    (27)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_4_UNION
 结构说明  : CVDR_LIMITER_VP_WR_4 寄存器结构定义。地址偏移量:0x410，初值:0x0F00FFFF，宽度:32
 寄存器说明: Video port write Access limiter
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_access_limiter_0_4      : 4;  /* bit[0-3]  : See previous definition on LIMITER_VP_WR_0 */
        unsigned int  vpwr_access_limiter_1_4      : 4;  /* bit[4-7]  : See previous definition on LIMITER_VP_WR_0 */
        unsigned int  vpwr_access_limiter_2_4      : 4;  /* bit[8-11] : See previous definition on LIMITER_VP_WR_0 */
        unsigned int  vpwr_access_limiter_3_4      : 4;  /* bit[12-15]: See previous definition on LIMITER_VP_WR_0 */
        unsigned int  reserved_0                   : 8;  /* bit[16-23]:  */
        unsigned int  vpwr_access_limiter_reload_4 : 4;  /* bit[24-27]: See previous definition on LIMITER_VP_WR_0 */
        unsigned int  reserved_1                   : 4;  /* bit[28-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_4_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_4_vpwr_access_limiter_0_4_START       (0)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_4_vpwr_access_limiter_0_4_END         (3)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_4_vpwr_access_limiter_1_4_START       (4)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_4_vpwr_access_limiter_1_4_END         (7)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_4_vpwr_access_limiter_2_4_START       (8)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_4_vpwr_access_limiter_2_4_END         (11)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_4_vpwr_access_limiter_3_4_START       (12)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_4_vpwr_access_limiter_3_4_END         (15)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_4_vpwr_access_limiter_reload_4_START  (24)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_4_vpwr_access_limiter_reload_4_END    (27)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_5_UNION
 结构说明  : CVDR_LIMITER_VP_WR_5 寄存器结构定义。地址偏移量:0x414，初值:0x0F00FFFF，宽度:32
 寄存器说明: Video port write Access limiter
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_access_limiter_0_5      : 4;  /* bit[0-3]  : See previous definition on LIMITER_VP_WR_0 */
        unsigned int  vpwr_access_limiter_1_5      : 4;  /* bit[4-7]  : See previous definition on LIMITER_VP_WR_0 */
        unsigned int  vpwr_access_limiter_2_5      : 4;  /* bit[8-11] : See previous definition on LIMITER_VP_WR_0 */
        unsigned int  vpwr_access_limiter_3_5      : 4;  /* bit[12-15]: See previous definition on LIMITER_VP_WR_0 */
        unsigned int  reserved_0                   : 8;  /* bit[16-23]:  */
        unsigned int  vpwr_access_limiter_reload_5 : 4;  /* bit[24-27]: See previous definition on LIMITER_VP_WR_0 */
        unsigned int  reserved_1                   : 4;  /* bit[28-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_5_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_5_vpwr_access_limiter_0_5_START       (0)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_5_vpwr_access_limiter_0_5_END         (3)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_5_vpwr_access_limiter_1_5_START       (4)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_5_vpwr_access_limiter_1_5_END         (7)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_5_vpwr_access_limiter_2_5_START       (8)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_5_vpwr_access_limiter_2_5_END         (11)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_5_vpwr_access_limiter_3_5_START       (12)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_5_vpwr_access_limiter_3_5_END         (15)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_5_vpwr_access_limiter_reload_5_START  (24)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_5_vpwr_access_limiter_reload_5_END    (27)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_8_UNION
 结构说明  : CVDR_LIMITER_VP_WR_8 寄存器结构定义。地址偏移量:0x420，初值:0x0F00FFFF，宽度:32
 寄存器说明: Video port write Access limiter
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_access_limiter_0_8      : 4;  /* bit[0-3]  : See previous definition on LIMITER_VP_WR_0 */
        unsigned int  vpwr_access_limiter_1_8      : 4;  /* bit[4-7]  : See previous definition on LIMITER_VP_WR_0 */
        unsigned int  vpwr_access_limiter_2_8      : 4;  /* bit[8-11] : See previous definition on LIMITER_VP_WR_0 */
        unsigned int  vpwr_access_limiter_3_8      : 4;  /* bit[12-15]: See previous definition on LIMITER_VP_WR_0 */
        unsigned int  reserved_0                   : 8;  /* bit[16-23]:  */
        unsigned int  vpwr_access_limiter_reload_8 : 4;  /* bit[24-27]: See previous definition on LIMITER_VP_WR_0 */
        unsigned int  reserved_1                   : 4;  /* bit[28-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_8_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_8_vpwr_access_limiter_0_8_START       (0)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_8_vpwr_access_limiter_0_8_END         (3)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_8_vpwr_access_limiter_1_8_START       (4)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_8_vpwr_access_limiter_1_8_END         (7)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_8_vpwr_access_limiter_2_8_START       (8)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_8_vpwr_access_limiter_2_8_END         (11)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_8_vpwr_access_limiter_3_8_START       (12)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_8_vpwr_access_limiter_3_8_END         (15)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_8_vpwr_access_limiter_reload_8_START  (24)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_8_vpwr_access_limiter_reload_8_END    (27)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_9_UNION
 结构说明  : CVDR_LIMITER_VP_WR_9 寄存器结构定义。地址偏移量:0x424，初值:0x0F00FFFF，宽度:32
 寄存器说明: Video port write Access limiter
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_access_limiter_0_9      : 4;  /* bit[0-3]  : See previous definition on LIMITER_VP_WR_0 */
        unsigned int  vpwr_access_limiter_1_9      : 4;  /* bit[4-7]  : See previous definition on LIMITER_VP_WR_0 */
        unsigned int  vpwr_access_limiter_2_9      : 4;  /* bit[8-11] : See previous definition on LIMITER_VP_WR_0 */
        unsigned int  vpwr_access_limiter_3_9      : 4;  /* bit[12-15]: See previous definition on LIMITER_VP_WR_0 */
        unsigned int  reserved_0                   : 8;  /* bit[16-23]:  */
        unsigned int  vpwr_access_limiter_reload_9 : 4;  /* bit[24-27]: See previous definition on LIMITER_VP_WR_0 */
        unsigned int  reserved_1                   : 4;  /* bit[28-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_9_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_9_vpwr_access_limiter_0_9_START       (0)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_9_vpwr_access_limiter_0_9_END         (3)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_9_vpwr_access_limiter_1_9_START       (4)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_9_vpwr_access_limiter_1_9_END         (7)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_9_vpwr_access_limiter_2_9_START       (8)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_9_vpwr_access_limiter_2_9_END         (11)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_9_vpwr_access_limiter_3_9_START       (12)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_9_vpwr_access_limiter_3_9_END         (15)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_9_vpwr_access_limiter_reload_9_START  (24)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_9_vpwr_access_limiter_reload_9_END    (27)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_14_UNION
 结构说明  : CVDR_LIMITER_VP_WR_14 寄存器结构定义。地址偏移量:0x438，初值:0x0F00FFFF，宽度:32
 寄存器说明: Video port write Access limiter
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_access_limiter_0_14      : 4;  /* bit[0-3]  : See previous definition on LIMITER_VP_WR_0 */
        unsigned int  vpwr_access_limiter_1_14      : 4;  /* bit[4-7]  : See previous definition on LIMITER_VP_WR_0 */
        unsigned int  vpwr_access_limiter_2_14      : 4;  /* bit[8-11] : See previous definition on LIMITER_VP_WR_0 */
        unsigned int  vpwr_access_limiter_3_14      : 4;  /* bit[12-15]: See previous definition on LIMITER_VP_WR_0 */
        unsigned int  reserved_0                    : 8;  /* bit[16-23]:  */
        unsigned int  vpwr_access_limiter_reload_14 : 4;  /* bit[24-27]: See previous definition on LIMITER_VP_WR_0 */
        unsigned int  reserved_1                    : 4;  /* bit[28-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_14_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_14_vpwr_access_limiter_0_14_START       (0)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_14_vpwr_access_limiter_0_14_END         (3)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_14_vpwr_access_limiter_1_14_START       (4)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_14_vpwr_access_limiter_1_14_END         (7)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_14_vpwr_access_limiter_2_14_START       (8)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_14_vpwr_access_limiter_2_14_END         (11)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_14_vpwr_access_limiter_3_14_START       (12)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_14_vpwr_access_limiter_3_14_END         (15)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_14_vpwr_access_limiter_reload_14_START  (24)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_14_vpwr_access_limiter_reload_14_END    (27)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_15_UNION
 结构说明  : CVDR_LIMITER_VP_WR_15 寄存器结构定义。地址偏移量:0x43C，初值:0x0F00FFFF，宽度:32
 寄存器说明: Video port write Access limiter
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_access_limiter_0_15      : 4;  /* bit[0-3]  : See previous definition on LIMITER_VP_WR_0 */
        unsigned int  vpwr_access_limiter_1_15      : 4;  /* bit[4-7]  : See previous definition on LIMITER_VP_WR_0 */
        unsigned int  vpwr_access_limiter_2_15      : 4;  /* bit[8-11] : See previous definition on LIMITER_VP_WR_0 */
        unsigned int  vpwr_access_limiter_3_15      : 4;  /* bit[12-15]: See previous definition on LIMITER_VP_WR_0 */
        unsigned int  reserved_0                    : 8;  /* bit[16-23]:  */
        unsigned int  vpwr_access_limiter_reload_15 : 4;  /* bit[24-27]: See previous definition on LIMITER_VP_WR_0 */
        unsigned int  reserved_1                    : 4;  /* bit[28-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_15_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_15_vpwr_access_limiter_0_15_START       (0)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_15_vpwr_access_limiter_0_15_END         (3)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_15_vpwr_access_limiter_1_15_START       (4)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_15_vpwr_access_limiter_1_15_END         (7)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_15_vpwr_access_limiter_2_15_START       (8)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_15_vpwr_access_limiter_2_15_END         (11)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_15_vpwr_access_limiter_3_15_START       (12)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_15_vpwr_access_limiter_3_15_END         (15)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_15_vpwr_access_limiter_reload_15_START  (24)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_15_vpwr_access_limiter_reload_15_END    (27)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_16_UNION
 结构说明  : CVDR_LIMITER_VP_WR_16 寄存器结构定义。地址偏移量:0x440，初值:0x0F00FFFF，宽度:32
 寄存器说明: Video port write Access limiter
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_access_limiter_0_16      : 4;  /* bit[0-3]  : See previous definition on LIMITER_VP_WR_0 */
        unsigned int  vpwr_access_limiter_1_16      : 4;  /* bit[4-7]  : See previous definition on LIMITER_VP_WR_0 */
        unsigned int  vpwr_access_limiter_2_16      : 4;  /* bit[8-11] : See previous definition on LIMITER_VP_WR_0 */
        unsigned int  vpwr_access_limiter_3_16      : 4;  /* bit[12-15]: See previous definition on LIMITER_VP_WR_0 */
        unsigned int  reserved_0                    : 8;  /* bit[16-23]:  */
        unsigned int  vpwr_access_limiter_reload_16 : 4;  /* bit[24-27]: See previous definition on LIMITER_VP_WR_0 */
        unsigned int  reserved_1                    : 4;  /* bit[28-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_16_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_16_vpwr_access_limiter_0_16_START       (0)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_16_vpwr_access_limiter_0_16_END         (3)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_16_vpwr_access_limiter_1_16_START       (4)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_16_vpwr_access_limiter_1_16_END         (7)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_16_vpwr_access_limiter_2_16_START       (8)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_16_vpwr_access_limiter_2_16_END         (11)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_16_vpwr_access_limiter_3_16_START       (12)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_16_vpwr_access_limiter_3_16_END         (15)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_16_vpwr_access_limiter_reload_16_START  (24)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_16_vpwr_access_limiter_reload_16_END    (27)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_17_UNION
 结构说明  : CVDR_LIMITER_VP_WR_17 寄存器结构定义。地址偏移量:0x444，初值:0x0F00FFFF，宽度:32
 寄存器说明: Video port write Access limiter
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_access_limiter_0_17      : 4;  /* bit[0-3]  : See previous definition on LIMITER_VP_WR_0 */
        unsigned int  vpwr_access_limiter_1_17      : 4;  /* bit[4-7]  : See previous definition on LIMITER_VP_WR_0 */
        unsigned int  vpwr_access_limiter_2_17      : 4;  /* bit[8-11] : See previous definition on LIMITER_VP_WR_0 */
        unsigned int  vpwr_access_limiter_3_17      : 4;  /* bit[12-15]: See previous definition on LIMITER_VP_WR_0 */
        unsigned int  reserved_0                    : 8;  /* bit[16-23]:  */
        unsigned int  vpwr_access_limiter_reload_17 : 4;  /* bit[24-27]: See previous definition on LIMITER_VP_WR_0 */
        unsigned int  reserved_1                    : 4;  /* bit[28-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_17_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_17_vpwr_access_limiter_0_17_START       (0)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_17_vpwr_access_limiter_0_17_END         (3)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_17_vpwr_access_limiter_1_17_START       (4)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_17_vpwr_access_limiter_1_17_END         (7)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_17_vpwr_access_limiter_2_17_START       (8)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_17_vpwr_access_limiter_2_17_END         (11)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_17_vpwr_access_limiter_3_17_START       (12)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_17_vpwr_access_limiter_3_17_END         (15)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_17_vpwr_access_limiter_reload_17_START  (24)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_17_vpwr_access_limiter_reload_17_END    (27)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_18_UNION
 结构说明  : CVDR_LIMITER_VP_WR_18 寄存器结构定义。地址偏移量:0x448，初值:0x0F00FFFF，宽度:32
 寄存器说明: Video port write Access limiter
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_access_limiter_0_18      : 4;  /* bit[0-3]  : See previous definition on LIMITER_VP_WR_0 */
        unsigned int  vpwr_access_limiter_1_18      : 4;  /* bit[4-7]  : See previous definition on LIMITER_VP_WR_0 */
        unsigned int  vpwr_access_limiter_2_18      : 4;  /* bit[8-11] : See previous definition on LIMITER_VP_WR_0 */
        unsigned int  vpwr_access_limiter_3_18      : 4;  /* bit[12-15]: See previous definition on LIMITER_VP_WR_0 */
        unsigned int  reserved_0                    : 8;  /* bit[16-23]:  */
        unsigned int  vpwr_access_limiter_reload_18 : 4;  /* bit[24-27]: See previous definition on LIMITER_VP_WR_0 */
        unsigned int  reserved_1                    : 4;  /* bit[28-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_18_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_18_vpwr_access_limiter_0_18_START       (0)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_18_vpwr_access_limiter_0_18_END         (3)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_18_vpwr_access_limiter_1_18_START       (4)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_18_vpwr_access_limiter_1_18_END         (7)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_18_vpwr_access_limiter_2_18_START       (8)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_18_vpwr_access_limiter_2_18_END         (11)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_18_vpwr_access_limiter_3_18_START       (12)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_18_vpwr_access_limiter_3_18_END         (15)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_18_vpwr_access_limiter_reload_18_START  (24)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_18_vpwr_access_limiter_reload_18_END    (27)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_19_UNION
 结构说明  : CVDR_LIMITER_VP_WR_19 寄存器结构定义。地址偏移量:0x44C，初值:0x0F00FFFF，宽度:32
 寄存器说明: Video port write Access limiter
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_access_limiter_0_19      : 4;  /* bit[0-3]  : See previous definition on LIMITER_VP_WR_0 */
        unsigned int  vpwr_access_limiter_1_19      : 4;  /* bit[4-7]  : See previous definition on LIMITER_VP_WR_0 */
        unsigned int  vpwr_access_limiter_2_19      : 4;  /* bit[8-11] : See previous definition on LIMITER_VP_WR_0 */
        unsigned int  vpwr_access_limiter_3_19      : 4;  /* bit[12-15]: See previous definition on LIMITER_VP_WR_0 */
        unsigned int  reserved_0                    : 8;  /* bit[16-23]:  */
        unsigned int  vpwr_access_limiter_reload_19 : 4;  /* bit[24-27]: See previous definition on LIMITER_VP_WR_0 */
        unsigned int  reserved_1                    : 4;  /* bit[28-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_19_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_19_vpwr_access_limiter_0_19_START       (0)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_19_vpwr_access_limiter_0_19_END         (3)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_19_vpwr_access_limiter_1_19_START       (4)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_19_vpwr_access_limiter_1_19_END         (7)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_19_vpwr_access_limiter_2_19_START       (8)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_19_vpwr_access_limiter_2_19_END         (11)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_19_vpwr_access_limiter_3_19_START       (12)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_19_vpwr_access_limiter_3_19_END         (15)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_19_vpwr_access_limiter_reload_19_START  (24)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_19_vpwr_access_limiter_reload_19_END    (27)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_20_UNION
 结构说明  : CVDR_LIMITER_VP_WR_20 寄存器结构定义。地址偏移量:0x450，初值:0x0F00FFFF，宽度:32
 寄存器说明: Video port write Access limiter
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_access_limiter_0_20      : 4;  /* bit[0-3]  : See previous definition on LIMITER_VP_WR_0 */
        unsigned int  vpwr_access_limiter_1_20      : 4;  /* bit[4-7]  : See previous definition on LIMITER_VP_WR_0 */
        unsigned int  vpwr_access_limiter_2_20      : 4;  /* bit[8-11] : See previous definition on LIMITER_VP_WR_0 */
        unsigned int  vpwr_access_limiter_3_20      : 4;  /* bit[12-15]: See previous definition on LIMITER_VP_WR_0 */
        unsigned int  reserved_0                    : 8;  /* bit[16-23]:  */
        unsigned int  vpwr_access_limiter_reload_20 : 4;  /* bit[24-27]: See previous definition on LIMITER_VP_WR_0 */
        unsigned int  reserved_1                    : 4;  /* bit[28-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_20_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_20_vpwr_access_limiter_0_20_START       (0)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_20_vpwr_access_limiter_0_20_END         (3)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_20_vpwr_access_limiter_1_20_START       (4)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_20_vpwr_access_limiter_1_20_END         (7)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_20_vpwr_access_limiter_2_20_START       (8)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_20_vpwr_access_limiter_2_20_END         (11)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_20_vpwr_access_limiter_3_20_START       (12)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_20_vpwr_access_limiter_3_20_END         (15)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_20_vpwr_access_limiter_reload_20_START  (24)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_20_vpwr_access_limiter_reload_20_END    (27)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_21_UNION
 结构说明  : CVDR_LIMITER_VP_WR_21 寄存器结构定义。地址偏移量:0x454，初值:0x0F00FFFF，宽度:32
 寄存器说明: Video port write Access limiter
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_access_limiter_0_21      : 4;  /* bit[0-3]  : See previous definition on LIMITER_VP_WR_0 */
        unsigned int  vpwr_access_limiter_1_21      : 4;  /* bit[4-7]  : See previous definition on LIMITER_VP_WR_0 */
        unsigned int  vpwr_access_limiter_2_21      : 4;  /* bit[8-11] : See previous definition on LIMITER_VP_WR_0 */
        unsigned int  vpwr_access_limiter_3_21      : 4;  /* bit[12-15]: See previous definition on LIMITER_VP_WR_0 */
        unsigned int  reserved_0                    : 8;  /* bit[16-23]:  */
        unsigned int  vpwr_access_limiter_reload_21 : 4;  /* bit[24-27]: See previous definition on LIMITER_VP_WR_0 */
        unsigned int  reserved_1                    : 4;  /* bit[28-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_21_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_21_vpwr_access_limiter_0_21_START       (0)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_21_vpwr_access_limiter_0_21_END         (3)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_21_vpwr_access_limiter_1_21_START       (4)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_21_vpwr_access_limiter_1_21_END         (7)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_21_vpwr_access_limiter_2_21_START       (8)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_21_vpwr_access_limiter_2_21_END         (11)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_21_vpwr_access_limiter_3_21_START       (12)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_21_vpwr_access_limiter_3_21_END         (15)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_21_vpwr_access_limiter_reload_21_START  (24)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_21_vpwr_access_limiter_reload_21_END    (27)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_22_UNION
 结构说明  : CVDR_LIMITER_VP_WR_22 寄存器结构定义。地址偏移量:0x458，初值:0x0F00FFFF，宽度:32
 寄存器说明: Video port write Access limiter
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_access_limiter_0_22      : 4;  /* bit[0-3]  : See previous definition on LIMITER_VP_WR_0 */
        unsigned int  vpwr_access_limiter_1_22      : 4;  /* bit[4-7]  : See previous definition on LIMITER_VP_WR_0 */
        unsigned int  vpwr_access_limiter_2_22      : 4;  /* bit[8-11] : See previous definition on LIMITER_VP_WR_0 */
        unsigned int  vpwr_access_limiter_3_22      : 4;  /* bit[12-15]: See previous definition on LIMITER_VP_WR_0 */
        unsigned int  reserved_0                    : 8;  /* bit[16-23]:  */
        unsigned int  vpwr_access_limiter_reload_22 : 4;  /* bit[24-27]: See previous definition on LIMITER_VP_WR_0 */
        unsigned int  reserved_1                    : 4;  /* bit[28-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_22_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_22_vpwr_access_limiter_0_22_START       (0)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_22_vpwr_access_limiter_0_22_END         (3)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_22_vpwr_access_limiter_1_22_START       (4)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_22_vpwr_access_limiter_1_22_END         (7)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_22_vpwr_access_limiter_2_22_START       (8)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_22_vpwr_access_limiter_2_22_END         (11)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_22_vpwr_access_limiter_3_22_START       (12)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_22_vpwr_access_limiter_3_22_END         (15)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_22_vpwr_access_limiter_reload_22_START  (24)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_22_vpwr_access_limiter_reload_22_END    (27)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_23_UNION
 结构说明  : CVDR_LIMITER_VP_WR_23 寄存器结构定义。地址偏移量:0x45C，初值:0x0F00FFFF，宽度:32
 寄存器说明: Video port write Access limiter
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_access_limiter_0_23      : 4;  /* bit[0-3]  : See previous definition on LIMITER_VP_WR_0 */
        unsigned int  vpwr_access_limiter_1_23      : 4;  /* bit[4-7]  : See previous definition on LIMITER_VP_WR_0 */
        unsigned int  vpwr_access_limiter_2_23      : 4;  /* bit[8-11] : See previous definition on LIMITER_VP_WR_0 */
        unsigned int  vpwr_access_limiter_3_23      : 4;  /* bit[12-15]: See previous definition on LIMITER_VP_WR_0 */
        unsigned int  reserved_0                    : 8;  /* bit[16-23]:  */
        unsigned int  vpwr_access_limiter_reload_23 : 4;  /* bit[24-27]: See previous definition on LIMITER_VP_WR_0 */
        unsigned int  reserved_1                    : 4;  /* bit[28-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_23_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_23_vpwr_access_limiter_0_23_START       (0)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_23_vpwr_access_limiter_0_23_END         (3)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_23_vpwr_access_limiter_1_23_START       (4)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_23_vpwr_access_limiter_1_23_END         (7)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_23_vpwr_access_limiter_2_23_START       (8)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_23_vpwr_access_limiter_2_23_END         (11)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_23_vpwr_access_limiter_3_23_START       (12)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_23_vpwr_access_limiter_3_23_END         (15)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_23_vpwr_access_limiter_reload_23_START  (24)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_23_vpwr_access_limiter_reload_23_END    (27)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_24_UNION
 结构说明  : CVDR_LIMITER_VP_WR_24 寄存器结构定义。地址偏移量:0x460，初值:0x0F00FFFF，宽度:32
 寄存器说明: Video port write Access limiter
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_access_limiter_0_24      : 4;  /* bit[0-3]  : See previous definition on LIMITER_VP_WR_0 */
        unsigned int  vpwr_access_limiter_1_24      : 4;  /* bit[4-7]  : See previous definition on LIMITER_VP_WR_0 */
        unsigned int  vpwr_access_limiter_2_24      : 4;  /* bit[8-11] : See previous definition on LIMITER_VP_WR_0 */
        unsigned int  vpwr_access_limiter_3_24      : 4;  /* bit[12-15]: See previous definition on LIMITER_VP_WR_0 */
        unsigned int  reserved_0                    : 8;  /* bit[16-23]:  */
        unsigned int  vpwr_access_limiter_reload_24 : 4;  /* bit[24-27]: See previous definition on LIMITER_VP_WR_0 */
        unsigned int  reserved_1                    : 4;  /* bit[28-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_24_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_24_vpwr_access_limiter_0_24_START       (0)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_24_vpwr_access_limiter_0_24_END         (3)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_24_vpwr_access_limiter_1_24_START       (4)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_24_vpwr_access_limiter_1_24_END         (7)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_24_vpwr_access_limiter_2_24_START       (8)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_24_vpwr_access_limiter_2_24_END         (11)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_24_vpwr_access_limiter_3_24_START       (12)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_24_vpwr_access_limiter_3_24_END         (15)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_24_vpwr_access_limiter_reload_24_START  (24)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_24_vpwr_access_limiter_reload_24_END    (27)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_25_UNION
 结构说明  : CVDR_LIMITER_VP_WR_25 寄存器结构定义。地址偏移量:0x464，初值:0x0F00FFFF，宽度:32
 寄存器说明: Video port write Access limiter
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_access_limiter_0_25      : 4;  /* bit[0-3]  : See previous definition on LIMITER_VP_WR_0 */
        unsigned int  vpwr_access_limiter_1_25      : 4;  /* bit[4-7]  : See previous definition on LIMITER_VP_WR_0 */
        unsigned int  vpwr_access_limiter_2_25      : 4;  /* bit[8-11] : See previous definition on LIMITER_VP_WR_0 */
        unsigned int  vpwr_access_limiter_3_25      : 4;  /* bit[12-15]: See previous definition on LIMITER_VP_WR_0 */
        unsigned int  reserved_0                    : 8;  /* bit[16-23]:  */
        unsigned int  vpwr_access_limiter_reload_25 : 4;  /* bit[24-27]: See previous definition on LIMITER_VP_WR_0 */
        unsigned int  reserved_1                    : 4;  /* bit[28-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_25_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_25_vpwr_access_limiter_0_25_START       (0)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_25_vpwr_access_limiter_0_25_END         (3)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_25_vpwr_access_limiter_1_25_START       (4)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_25_vpwr_access_limiter_1_25_END         (7)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_25_vpwr_access_limiter_2_25_START       (8)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_25_vpwr_access_limiter_2_25_END         (11)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_25_vpwr_access_limiter_3_25_START       (12)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_25_vpwr_access_limiter_3_25_END         (15)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_25_vpwr_access_limiter_reload_25_START  (24)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_25_vpwr_access_limiter_reload_25_END    (27)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_26_UNION
 结构说明  : CVDR_LIMITER_VP_WR_26 寄存器结构定义。地址偏移量:0x468，初值:0x0F00FFFF，宽度:32
 寄存器说明: Video port write Access limiter
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_access_limiter_0_26      : 4;  /* bit[0-3]  : See previous definition on LIMITER_VP_WR_0 */
        unsigned int  vpwr_access_limiter_1_26      : 4;  /* bit[4-7]  : See previous definition on LIMITER_VP_WR_0 */
        unsigned int  vpwr_access_limiter_2_26      : 4;  /* bit[8-11] : See previous definition on LIMITER_VP_WR_0 */
        unsigned int  vpwr_access_limiter_3_26      : 4;  /* bit[12-15]: See previous definition on LIMITER_VP_WR_0 */
        unsigned int  reserved_0                    : 8;  /* bit[16-23]:  */
        unsigned int  vpwr_access_limiter_reload_26 : 4;  /* bit[24-27]: See previous definition on LIMITER_VP_WR_0 */
        unsigned int  reserved_1                    : 4;  /* bit[28-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_26_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_26_vpwr_access_limiter_0_26_START       (0)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_26_vpwr_access_limiter_0_26_END         (3)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_26_vpwr_access_limiter_1_26_START       (4)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_26_vpwr_access_limiter_1_26_END         (7)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_26_vpwr_access_limiter_2_26_START       (8)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_26_vpwr_access_limiter_2_26_END         (11)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_26_vpwr_access_limiter_3_26_START       (12)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_26_vpwr_access_limiter_3_26_END         (15)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_26_vpwr_access_limiter_reload_26_START  (24)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_26_vpwr_access_limiter_reload_26_END    (27)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_27_UNION
 结构说明  : CVDR_LIMITER_VP_WR_27 寄存器结构定义。地址偏移量:0x46C，初值:0x0F00FFFF，宽度:32
 寄存器说明: Video port write Access limiter
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vpwr_access_limiter_0_27      : 4;  /* bit[0-3]  : See previous definition on LIMITER_VP_WR_0 */
        unsigned int  vpwr_access_limiter_1_27      : 4;  /* bit[4-7]  : See previous definition on LIMITER_VP_WR_0 */
        unsigned int  vpwr_access_limiter_2_27      : 4;  /* bit[8-11] : See previous definition on LIMITER_VP_WR_0 */
        unsigned int  vpwr_access_limiter_3_27      : 4;  /* bit[12-15]: See previous definition on LIMITER_VP_WR_0 */
        unsigned int  reserved_0                    : 8;  /* bit[16-23]:  */
        unsigned int  vpwr_access_limiter_reload_27 : 4;  /* bit[24-27]: See previous definition on LIMITER_VP_WR_0 */
        unsigned int  reserved_1                    : 4;  /* bit[28-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_27_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_27_vpwr_access_limiter_0_27_START       (0)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_27_vpwr_access_limiter_0_27_END         (3)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_27_vpwr_access_limiter_1_27_START       (4)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_27_vpwr_access_limiter_1_27_END         (7)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_27_vpwr_access_limiter_2_27_START       (8)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_27_vpwr_access_limiter_2_27_END         (11)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_27_vpwr_access_limiter_3_27_START       (12)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_27_vpwr_access_limiter_3_27_END         (15)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_27_vpwr_access_limiter_reload_27_START  (24)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_WR_27_vpwr_access_limiter_reload_27_END    (27)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_RD_CFG_0_UNION
 结构说明  : CVDR_VP_RD_CFG_0 寄存器结构定义。地址偏移量:0x500，初值:0x00000000，宽度:32
 寄存器说明: Video port read Configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_pixel_format_0    : 4;  /* bit[0-3]  : "Pixel formats supported (see ref. [1])ReturnToLine 0:3->1PF8:1PF14 ReturnToLine 4:7->2PF8:2PF14 ReturnToLine 9:11->3PF8:3PF14 ReturnToLine 12:D32 ReturnToLine 13:D48 ReturnToLine 14: D64" */
        unsigned int  vprd_pixel_expansion_0 : 1;  /* bit[4-4]  : Pixel expansion can be used (see ref. [1]) */
        unsigned int  vprd_allocated_du_0    : 5;  /* bit[5-9]  : "Number of allocated DUsReturnToLineA maximum of 32 DUs can be allocated per video port" */
        unsigned int  reserved               : 5;  /* bit[10-14]:  */
        unsigned int  vprd_last_page_0       : 17; /* bit[15-31]: "last 32KB page reserved to read the data. This page is not necessarely prefetched but is the last page reserved by the Software.ReturnToLineThe CVDR must prefetch the page used by the frame start (back to initial - in case of continuous mode) once the last page is equal to vprd_last_page. ReturnToLineThis info must be aligned with the frame size (SW info) and the vprd_line_wrap info (SW and HW) to be aligned with buffer size reserved by the SW." */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_RD_CFG_0_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_0_vprd_pixel_format_0_START     (0)
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_0_vprd_pixel_format_0_END       (3)
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_0_vprd_pixel_expansion_0_START  (4)
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_0_vprd_pixel_expansion_0_END    (4)
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_0_vprd_allocated_du_0_START     (5)
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_0_vprd_allocated_du_0_END       (9)
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_0_vprd_last_page_0_START        (15)
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_0_vprd_last_page_0_END          (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_RD_LWG_0_UNION
 结构说明  : CVDR_VP_RD_LWG_0 寄存器结构定义。地址偏移量:0x504，初值:0x00000000，宽度:32
 寄存器说明: Line width generation
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_line_size_0           : 13; /* bit[0-12] : number of pixels per line (up to 8192 pixels) */
        unsigned int  reserved_0                 : 3;  /* bit[13-15]:  */
        unsigned int  vprd_horizontal_blanking_0 : 8;  /* bit[16-23]: "Horizontal blanking (number of clock cycles between 2 lines)ReturnToLineup to 256 clock cycles" */
        unsigned int  reserved_1                 : 8;  /* bit[24-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_RD_LWG_0_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_RD_LWG_0_vprd_line_size_0_START            (0)
#define SOC_ISP_CVDR_CVDR_VP_RD_LWG_0_vprd_line_size_0_END              (12)
#define SOC_ISP_CVDR_CVDR_VP_RD_LWG_0_vprd_horizontal_blanking_0_START  (16)
#define SOC_ISP_CVDR_CVDR_VP_RD_LWG_0_vprd_horizontal_blanking_0_END    (23)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_RD_FHG_0_UNION
 结构说明  : CVDR_VP_RD_FHG_0 寄存器结构定义。地址偏移量:0x508，初值:0x00000000，宽度:32
 寄存器说明: Frame height generation
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_frame_size_0        : 13; /* bit[0-12] : number of lines per frame (up to 8192 lines) */
        unsigned int  reserved_0               : 3;  /* bit[13-15]:  */
        unsigned int  vprd_vertical_blanking_0 : 8;  /* bit[16-23]: "Vertical blanking (number of dummy lines between 2 frames)ReturnToLineup to 256 lines" */
        unsigned int  reserved_1               : 8;  /* bit[24-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_RD_FHG_0_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_RD_FHG_0_vprd_frame_size_0_START         (0)
#define SOC_ISP_CVDR_CVDR_VP_RD_FHG_0_vprd_frame_size_0_END           (12)
#define SOC_ISP_CVDR_CVDR_VP_RD_FHG_0_vprd_vertical_blanking_0_START  (16)
#define SOC_ISP_CVDR_CVDR_VP_RD_FHG_0_vprd_vertical_blanking_0_END    (23)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_RD_AXI_FS_0_UNION
 结构说明  : CVDR_VP_RD_AXI_FS_0 寄存器结构定义。地址偏移量:0x50C，初值:0x00000000，宽度:32
 寄存器说明: AXI frame start
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved               : 4;  /* bit[0-3] :  */
        unsigned int  vprd_axi_frame_start_0 : 28; /* bit[4-31]: "Start address of the frame (in 16 bytes boundary).ReturnToLineSince we are 128-bits */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_RD_AXI_FS_0_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_FS_0_vprd_axi_frame_start_0_START  (4)
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_FS_0_vprd_axi_frame_start_0_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_0_UNION
 结构说明  : CVDR_VP_RD_AXI_LINE_0 寄存器结构定义。地址偏移量:0x510，初值:0x1FFF0000，宽度:32
 寄存器说明: Line Wrap definition
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_line_stride_0 : 10; /* bit[0-9]  : "Stride to use on line starts (aligned to a 16 byte boundary: Max stride of 16 KBytes)ReturnToLine0: line stride disabled (continuous) (continuous mode : next line will start on a 128 bytes boundary)ReturnToLine1: 2*16 bytesReturnToLineand so onReturnToLine1023 : 1024*16 bytes" */
        unsigned int  reserved_0         : 6;  /* bit[10-15]:  */
        unsigned int  vprd_line_wrap_0   : 13; /* bit[16-28]: "Line wrap: wrap to frame start location (13 bits)ReturnToLine0: wrap every lineReturnToLine1: wrap every 2 linesReturnToLineand so onReturnToLine8191: wrap every 8192 lines" */
        unsigned int  reserved_1         : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_0_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_0_vprd_line_stride_0_START  (0)
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_0_vprd_line_stride_0_END    (9)
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_0_vprd_line_wrap_0_START    (16)
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_0_vprd_line_wrap_0_END      (28)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_0_UNION
 结构说明  : CVDR_VP_RD_PREFETCH_0 寄存器结构定义。地址偏移量:0x514，初值:0x00000100，宽度:32
 寄存器说明: Configure the prefetch mechanism and must be aligned with the SMMU configuration.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_index_id0_0       : 7;  /* bit[0-6]  : configurable index ID 0 */
        unsigned int  reserved_0             : 1;  /* bit[7-7]  :  */
        unsigned int  vprd_index_id1_0       : 7;  /* bit[8-14] : configurable index ID 1 */
        unsigned int  reserved_1             : 16; /* bit[15-30]:  */
        unsigned int  vprd_prefetch_bypass_0 : 1;  /* bit[31-31]: "Enables to bypass the prefetch mechanism.ReturnToLine0: prefetch functionality is enabledReturnToLine1: prefetch functionality is bypassed (Index ID is always vprd_index_id0)" */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_0_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_0_vprd_index_id0_0_START        (0)
#define SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_0_vprd_index_id0_0_END          (6)
#define SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_0_vprd_index_id1_0_START        (8)
#define SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_0_vprd_index_id1_0_END          (14)
#define SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_0_vprd_prefetch_bypass_0_START  (31)
#define SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_0_vprd_prefetch_bypass_0_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_RD_DEBUG_0_UNION
 结构说明  : CVDR_VP_RD_DEBUG_0 寄存器结构定义。地址偏移量:0x51C，初值:0x00000000，宽度:32
 寄存器说明: Video Port Read DEBUG information
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vp_rd_debug_0 : 32; /* bit[0-31]: Video Port Read DEBUG information */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_RD_DEBUG_0_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_RD_DEBUG_0_vp_rd_debug_0_START  (0)
#define SOC_ISP_CVDR_CVDR_VP_RD_DEBUG_0_vp_rd_debug_0_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_RD_CFG_4_UNION
 结构说明  : CVDR_VP_RD_CFG_4 寄存器结构定义。地址偏移量:0x580，初值:0x00000000，宽度:32
 寄存器说明: Video port read Configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_pixel_format_4    : 4;  /* bit[0-3]  : See previous definition on VP_RD_CFG_0 */
        unsigned int  vprd_pixel_expansion_4 : 1;  /* bit[4-4]  : See previous definition on VP_RD_CFG_0 */
        unsigned int  vprd_allocated_du_4    : 5;  /* bit[5-9]  : See previous definition on VP_RD_CFG_0 */
        unsigned int  reserved               : 5;  /* bit[10-14]:  */
        unsigned int  vprd_last_page_4       : 17; /* bit[15-31]: See previous definition on VP_RD_CFG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_RD_CFG_4_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_4_vprd_pixel_format_4_START     (0)
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_4_vprd_pixel_format_4_END       (3)
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_4_vprd_pixel_expansion_4_START  (4)
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_4_vprd_pixel_expansion_4_END    (4)
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_4_vprd_allocated_du_4_START     (5)
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_4_vprd_allocated_du_4_END       (9)
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_4_vprd_last_page_4_START        (15)
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_4_vprd_last_page_4_END          (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_RD_LWG_4_UNION
 结构说明  : CVDR_VP_RD_LWG_4 寄存器结构定义。地址偏移量:0x584，初值:0x00000000，宽度:32
 寄存器说明: Line width generation
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_line_size_4           : 13; /* bit[0-12] : See previous definition on VP_RD_LWG_0 */
        unsigned int  reserved_0                 : 3;  /* bit[13-15]:  */
        unsigned int  vprd_horizontal_blanking_4 : 8;  /* bit[16-23]: See previous definition on VP_RD_LWG_0 */
        unsigned int  reserved_1                 : 8;  /* bit[24-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_RD_LWG_4_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_RD_LWG_4_vprd_line_size_4_START            (0)
#define SOC_ISP_CVDR_CVDR_VP_RD_LWG_4_vprd_line_size_4_END              (12)
#define SOC_ISP_CVDR_CVDR_VP_RD_LWG_4_vprd_horizontal_blanking_4_START  (16)
#define SOC_ISP_CVDR_CVDR_VP_RD_LWG_4_vprd_horizontal_blanking_4_END    (23)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_RD_FHG_4_UNION
 结构说明  : CVDR_VP_RD_FHG_4 寄存器结构定义。地址偏移量:0x588，初值:0x00000000，宽度:32
 寄存器说明: Frame height generation
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_frame_size_4        : 13; /* bit[0-12] : See previous definition on VP_RD_FHG_0 */
        unsigned int  reserved_0               : 3;  /* bit[13-15]:  */
        unsigned int  vprd_vertical_blanking_4 : 8;  /* bit[16-23]: See previous definition on VP_RD_FHG_0 */
        unsigned int  reserved_1               : 8;  /* bit[24-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_RD_FHG_4_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_RD_FHG_4_vprd_frame_size_4_START         (0)
#define SOC_ISP_CVDR_CVDR_VP_RD_FHG_4_vprd_frame_size_4_END           (12)
#define SOC_ISP_CVDR_CVDR_VP_RD_FHG_4_vprd_vertical_blanking_4_START  (16)
#define SOC_ISP_CVDR_CVDR_VP_RD_FHG_4_vprd_vertical_blanking_4_END    (23)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_RD_AXI_FS_4_UNION
 结构说明  : CVDR_VP_RD_AXI_FS_4 寄存器结构定义。地址偏移量:0x58C，初值:0x00000000，宽度:32
 寄存器说明: AXI frame start
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved               : 4;  /* bit[0-3] :  */
        unsigned int  vprd_axi_frame_start_4 : 28; /* bit[4-31]: See previous definition on VP_RD_AXI_FS_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_RD_AXI_FS_4_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_FS_4_vprd_axi_frame_start_4_START  (4)
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_FS_4_vprd_axi_frame_start_4_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_4_UNION
 结构说明  : CVDR_VP_RD_AXI_LINE_4 寄存器结构定义。地址偏移量:0x590，初值:0x1FFF0000，宽度:32
 寄存器说明: Line Wrap definition
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_line_stride_4 : 10; /* bit[0-9]  : See previous definition on VP_RD_AXI_LINE_0 */
        unsigned int  reserved_0         : 6;  /* bit[10-15]:  */
        unsigned int  vprd_line_wrap_4   : 13; /* bit[16-28]: See previous definition on VP_RD_AXI_LINE_0 */
        unsigned int  reserved_1         : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_4_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_4_vprd_line_stride_4_START  (0)
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_4_vprd_line_stride_4_END    (9)
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_4_vprd_line_wrap_4_START    (16)
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_4_vprd_line_wrap_4_END      (28)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_4_UNION
 结构说明  : CVDR_VP_RD_PREFETCH_4 寄存器结构定义。地址偏移量:0x594，初值:0x00000302，宽度:32
 寄存器说明: Configure the prefetch mechanism and must be aligned with the SMMU configuration.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_index_id0_4       : 7;  /* bit[0-6]  : See previous definition on VP_RD_PREFETCH_0 */
        unsigned int  reserved_0             : 1;  /* bit[7-7]  :  */
        unsigned int  vprd_index_id1_4       : 7;  /* bit[8-14] : See previous definition on VP_RD_PREFETCH_0 */
        unsigned int  reserved_1             : 16; /* bit[15-30]:  */
        unsigned int  vprd_prefetch_bypass_4 : 1;  /* bit[31-31]: See previous definition on VP_RD_PREFETCH_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_4_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_4_vprd_index_id0_4_START        (0)
#define SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_4_vprd_index_id0_4_END          (6)
#define SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_4_vprd_index_id1_4_START        (8)
#define SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_4_vprd_index_id1_4_END          (14)
#define SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_4_vprd_prefetch_bypass_4_START  (31)
#define SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_4_vprd_prefetch_bypass_4_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_RD_DEBUG_4_UNION
 结构说明  : CVDR_VP_RD_DEBUG_4 寄存器结构定义。地址偏移量:0x59C，初值:0x00000000，宽度:32
 寄存器说明: Video Port Read DEBUG information
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vp_rd_debug_4 : 32; /* bit[0-31]: See previous definition on VP_RD_DEBUG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_RD_DEBUG_4_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_RD_DEBUG_4_vp_rd_debug_4_START  (0)
#define SOC_ISP_CVDR_CVDR_VP_RD_DEBUG_4_vp_rd_debug_4_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_RD_CFG_5_UNION
 结构说明  : CVDR_VP_RD_CFG_5 寄存器结构定义。地址偏移量:0x5A0，初值:0x00000000，宽度:32
 寄存器说明: Video port read Configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_pixel_format_5    : 4;  /* bit[0-3]  : See previous definition on VP_RD_CFG_0 */
        unsigned int  vprd_pixel_expansion_5 : 1;  /* bit[4-4]  : See previous definition on VP_RD_CFG_0 */
        unsigned int  vprd_allocated_du_5    : 5;  /* bit[5-9]  : See previous definition on VP_RD_CFG_0 */
        unsigned int  reserved               : 5;  /* bit[10-14]:  */
        unsigned int  vprd_last_page_5       : 17; /* bit[15-31]: See previous definition on VP_RD_CFG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_RD_CFG_5_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_5_vprd_pixel_format_5_START     (0)
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_5_vprd_pixel_format_5_END       (3)
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_5_vprd_pixel_expansion_5_START  (4)
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_5_vprd_pixel_expansion_5_END    (4)
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_5_vprd_allocated_du_5_START     (5)
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_5_vprd_allocated_du_5_END       (9)
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_5_vprd_last_page_5_START        (15)
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_5_vprd_last_page_5_END          (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_RD_LWG_5_UNION
 结构说明  : CVDR_VP_RD_LWG_5 寄存器结构定义。地址偏移量:0x5A4，初值:0x00000000，宽度:32
 寄存器说明: Line width generation
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_line_size_5           : 13; /* bit[0-12] : See previous definition on VP_RD_LWG_0 */
        unsigned int  reserved_0                 : 3;  /* bit[13-15]:  */
        unsigned int  vprd_horizontal_blanking_5 : 8;  /* bit[16-23]: See previous definition on VP_RD_LWG_0 */
        unsigned int  reserved_1                 : 8;  /* bit[24-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_RD_LWG_5_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_RD_LWG_5_vprd_line_size_5_START            (0)
#define SOC_ISP_CVDR_CVDR_VP_RD_LWG_5_vprd_line_size_5_END              (12)
#define SOC_ISP_CVDR_CVDR_VP_RD_LWG_5_vprd_horizontal_blanking_5_START  (16)
#define SOC_ISP_CVDR_CVDR_VP_RD_LWG_5_vprd_horizontal_blanking_5_END    (23)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_RD_FHG_5_UNION
 结构说明  : CVDR_VP_RD_FHG_5 寄存器结构定义。地址偏移量:0x5A8，初值:0x00000000，宽度:32
 寄存器说明: Frame height generation
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_frame_size_5        : 13; /* bit[0-12] : See previous definition on VP_RD_FHG_0 */
        unsigned int  reserved_0               : 3;  /* bit[13-15]:  */
        unsigned int  vprd_vertical_blanking_5 : 8;  /* bit[16-23]: See previous definition on VP_RD_FHG_0 */
        unsigned int  reserved_1               : 8;  /* bit[24-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_RD_FHG_5_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_RD_FHG_5_vprd_frame_size_5_START         (0)
#define SOC_ISP_CVDR_CVDR_VP_RD_FHG_5_vprd_frame_size_5_END           (12)
#define SOC_ISP_CVDR_CVDR_VP_RD_FHG_5_vprd_vertical_blanking_5_START  (16)
#define SOC_ISP_CVDR_CVDR_VP_RD_FHG_5_vprd_vertical_blanking_5_END    (23)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_RD_AXI_FS_5_UNION
 结构说明  : CVDR_VP_RD_AXI_FS_5 寄存器结构定义。地址偏移量:0x5AC，初值:0x00000000，宽度:32
 寄存器说明: AXI frame start
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved               : 4;  /* bit[0-3] :  */
        unsigned int  vprd_axi_frame_start_5 : 28; /* bit[4-31]: See previous definition on VP_RD_AXI_FS_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_RD_AXI_FS_5_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_FS_5_vprd_axi_frame_start_5_START  (4)
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_FS_5_vprd_axi_frame_start_5_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_5_UNION
 结构说明  : CVDR_VP_RD_AXI_LINE_5 寄存器结构定义。地址偏移量:0x5B0，初值:0x1FFF0000，宽度:32
 寄存器说明: Line Wrap definition
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_line_stride_5 : 10; /* bit[0-9]  : See previous definition on VP_RD_AXI_LINE_0 */
        unsigned int  reserved_0         : 6;  /* bit[10-15]:  */
        unsigned int  vprd_line_wrap_5   : 13; /* bit[16-28]: See previous definition on VP_RD_AXI_LINE_0 */
        unsigned int  reserved_1         : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_5_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_5_vprd_line_stride_5_START  (0)
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_5_vprd_line_stride_5_END    (9)
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_5_vprd_line_wrap_5_START    (16)
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_5_vprd_line_wrap_5_END      (28)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_5_UNION
 结构说明  : CVDR_VP_RD_PREFETCH_5 寄存器结构定义。地址偏移量:0x5B4，初值:0x00000504，宽度:32
 寄存器说明: Configure the prefetch mechanism and must be aligned with the SMMU configuration.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_index_id0_5       : 7;  /* bit[0-6]  : See previous definition on VP_RD_PREFETCH_0 */
        unsigned int  reserved_0             : 1;  /* bit[7-7]  :  */
        unsigned int  vprd_index_id1_5       : 7;  /* bit[8-14] : See previous definition on VP_RD_PREFETCH_0 */
        unsigned int  reserved_1             : 16; /* bit[15-30]:  */
        unsigned int  vprd_prefetch_bypass_5 : 1;  /* bit[31-31]: See previous definition on VP_RD_PREFETCH_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_5_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_5_vprd_index_id0_5_START        (0)
#define SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_5_vprd_index_id0_5_END          (6)
#define SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_5_vprd_index_id1_5_START        (8)
#define SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_5_vprd_index_id1_5_END          (14)
#define SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_5_vprd_prefetch_bypass_5_START  (31)
#define SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_5_vprd_prefetch_bypass_5_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_RD_DEBUG_5_UNION
 结构说明  : CVDR_VP_RD_DEBUG_5 寄存器结构定义。地址偏移量:0x5BC，初值:0x00000000，宽度:32
 寄存器说明: Video Port Read DEBUG information
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vp_rd_debug_5 : 32; /* bit[0-31]: See previous definition on VP_RD_DEBUG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_RD_DEBUG_5_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_RD_DEBUG_5_vp_rd_debug_5_START  (0)
#define SOC_ISP_CVDR_CVDR_VP_RD_DEBUG_5_vp_rd_debug_5_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_RD_CFG_6_UNION
 结构说明  : CVDR_VP_RD_CFG_6 寄存器结构定义。地址偏移量:0x5C0，初值:0x00000000，宽度:32
 寄存器说明: Video port read Configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_pixel_format_6    : 4;  /* bit[0-3]  : See previous definition on VP_RD_CFG_0 */
        unsigned int  vprd_pixel_expansion_6 : 1;  /* bit[4-4]  : See previous definition on VP_RD_CFG_0 */
        unsigned int  vprd_allocated_du_6    : 5;  /* bit[5-9]  : See previous definition on VP_RD_CFG_0 */
        unsigned int  reserved               : 5;  /* bit[10-14]:  */
        unsigned int  vprd_last_page_6       : 17; /* bit[15-31]: See previous definition on VP_RD_CFG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_RD_CFG_6_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_6_vprd_pixel_format_6_START     (0)
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_6_vprd_pixel_format_6_END       (3)
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_6_vprd_pixel_expansion_6_START  (4)
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_6_vprd_pixel_expansion_6_END    (4)
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_6_vprd_allocated_du_6_START     (5)
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_6_vprd_allocated_du_6_END       (9)
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_6_vprd_last_page_6_START        (15)
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_6_vprd_last_page_6_END          (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_RD_LWG_6_UNION
 结构说明  : CVDR_VP_RD_LWG_6 寄存器结构定义。地址偏移量:0x5C4，初值:0x00000000，宽度:32
 寄存器说明: Line width generation
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_line_size_6           : 13; /* bit[0-12] : See previous definition on VP_RD_LWG_0 */
        unsigned int  reserved_0                 : 3;  /* bit[13-15]:  */
        unsigned int  vprd_horizontal_blanking_6 : 8;  /* bit[16-23]: See previous definition on VP_RD_LWG_0 */
        unsigned int  reserved_1                 : 8;  /* bit[24-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_RD_LWG_6_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_RD_LWG_6_vprd_line_size_6_START            (0)
#define SOC_ISP_CVDR_CVDR_VP_RD_LWG_6_vprd_line_size_6_END              (12)
#define SOC_ISP_CVDR_CVDR_VP_RD_LWG_6_vprd_horizontal_blanking_6_START  (16)
#define SOC_ISP_CVDR_CVDR_VP_RD_LWG_6_vprd_horizontal_blanking_6_END    (23)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_RD_FHG_6_UNION
 结构说明  : CVDR_VP_RD_FHG_6 寄存器结构定义。地址偏移量:0x5C8，初值:0x00000000，宽度:32
 寄存器说明: Frame height generation
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_frame_size_6        : 13; /* bit[0-12] : See previous definition on VP_RD_FHG_0 */
        unsigned int  reserved_0               : 3;  /* bit[13-15]:  */
        unsigned int  vprd_vertical_blanking_6 : 8;  /* bit[16-23]: See previous definition on VP_RD_FHG_0 */
        unsigned int  reserved_1               : 8;  /* bit[24-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_RD_FHG_6_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_RD_FHG_6_vprd_frame_size_6_START         (0)
#define SOC_ISP_CVDR_CVDR_VP_RD_FHG_6_vprd_frame_size_6_END           (12)
#define SOC_ISP_CVDR_CVDR_VP_RD_FHG_6_vprd_vertical_blanking_6_START  (16)
#define SOC_ISP_CVDR_CVDR_VP_RD_FHG_6_vprd_vertical_blanking_6_END    (23)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_RD_AXI_FS_6_UNION
 结构说明  : CVDR_VP_RD_AXI_FS_6 寄存器结构定义。地址偏移量:0x5CC，初值:0x00000000，宽度:32
 寄存器说明: AXI frame start
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved               : 4;  /* bit[0-3] :  */
        unsigned int  vprd_axi_frame_start_6 : 28; /* bit[4-31]: See previous definition on VP_RD_AXI_FS_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_RD_AXI_FS_6_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_FS_6_vprd_axi_frame_start_6_START  (4)
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_FS_6_vprd_axi_frame_start_6_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_6_UNION
 结构说明  : CVDR_VP_RD_AXI_LINE_6 寄存器结构定义。地址偏移量:0x5D0，初值:0x1FFF0000，宽度:32
 寄存器说明: Line Wrap definition
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_line_stride_6 : 10; /* bit[0-9]  : See previous definition on VP_RD_AXI_LINE_0 */
        unsigned int  reserved_0         : 6;  /* bit[10-15]:  */
        unsigned int  vprd_line_wrap_6   : 13; /* bit[16-28]: See previous definition on VP_RD_AXI_LINE_0 */
        unsigned int  reserved_1         : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_6_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_6_vprd_line_stride_6_START  (0)
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_6_vprd_line_stride_6_END    (9)
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_6_vprd_line_wrap_6_START    (16)
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_6_vprd_line_wrap_6_END      (28)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_6_UNION
 结构说明  : CVDR_VP_RD_PREFETCH_6 寄存器结构定义。地址偏移量:0x5D4，初值:0x00000706，宽度:32
 寄存器说明: Configure the prefetch mechanism and must be aligned with the SMMU configuration.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_index_id0_6       : 7;  /* bit[0-6]  : See previous definition on VP_RD_PREFETCH_0 */
        unsigned int  reserved_0             : 1;  /* bit[7-7]  :  */
        unsigned int  vprd_index_id1_6       : 7;  /* bit[8-14] : See previous definition on VP_RD_PREFETCH_0 */
        unsigned int  reserved_1             : 16; /* bit[15-30]:  */
        unsigned int  vprd_prefetch_bypass_6 : 1;  /* bit[31-31]: See previous definition on VP_RD_PREFETCH_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_6_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_6_vprd_index_id0_6_START        (0)
#define SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_6_vprd_index_id0_6_END          (6)
#define SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_6_vprd_index_id1_6_START        (8)
#define SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_6_vprd_index_id1_6_END          (14)
#define SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_6_vprd_prefetch_bypass_6_START  (31)
#define SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_6_vprd_prefetch_bypass_6_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_RD_DEBUG_6_UNION
 结构说明  : CVDR_VP_RD_DEBUG_6 寄存器结构定义。地址偏移量:0x5DC，初值:0x00000000，宽度:32
 寄存器说明: Video Port Read DEBUG information
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vp_rd_debug_6 : 32; /* bit[0-31]: See previous definition on VP_RD_DEBUG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_RD_DEBUG_6_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_RD_DEBUG_6_vp_rd_debug_6_START  (0)
#define SOC_ISP_CVDR_CVDR_VP_RD_DEBUG_6_vp_rd_debug_6_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_RD_CFG_7_UNION
 结构说明  : CVDR_VP_RD_CFG_7 寄存器结构定义。地址偏移量:0x5E0，初值:0x00000000，宽度:32
 寄存器说明: Video port read Configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_pixel_format_7    : 4;  /* bit[0-3]  : See previous definition on VP_RD_CFG_0 */
        unsigned int  vprd_pixel_expansion_7 : 1;  /* bit[4-4]  : See previous definition on VP_RD_CFG_0 */
        unsigned int  vprd_allocated_du_7    : 5;  /* bit[5-9]  : See previous definition on VP_RD_CFG_0 */
        unsigned int  reserved               : 5;  /* bit[10-14]:  */
        unsigned int  vprd_last_page_7       : 17; /* bit[15-31]: See previous definition on VP_RD_CFG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_RD_CFG_7_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_7_vprd_pixel_format_7_START     (0)
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_7_vprd_pixel_format_7_END       (3)
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_7_vprd_pixel_expansion_7_START  (4)
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_7_vprd_pixel_expansion_7_END    (4)
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_7_vprd_allocated_du_7_START     (5)
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_7_vprd_allocated_du_7_END       (9)
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_7_vprd_last_page_7_START        (15)
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_7_vprd_last_page_7_END          (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_RD_LWG_7_UNION
 结构说明  : CVDR_VP_RD_LWG_7 寄存器结构定义。地址偏移量:0x5E4，初值:0x00000000，宽度:32
 寄存器说明: Line width generation
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_line_size_7           : 13; /* bit[0-12] : See previous definition on VP_RD_LWG_0 */
        unsigned int  reserved_0                 : 3;  /* bit[13-15]:  */
        unsigned int  vprd_horizontal_blanking_7 : 8;  /* bit[16-23]: See previous definition on VP_RD_LWG_0 */
        unsigned int  reserved_1                 : 8;  /* bit[24-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_RD_LWG_7_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_RD_LWG_7_vprd_line_size_7_START            (0)
#define SOC_ISP_CVDR_CVDR_VP_RD_LWG_7_vprd_line_size_7_END              (12)
#define SOC_ISP_CVDR_CVDR_VP_RD_LWG_7_vprd_horizontal_blanking_7_START  (16)
#define SOC_ISP_CVDR_CVDR_VP_RD_LWG_7_vprd_horizontal_blanking_7_END    (23)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_RD_FHG_7_UNION
 结构说明  : CVDR_VP_RD_FHG_7 寄存器结构定义。地址偏移量:0x5E8，初值:0x00000000，宽度:32
 寄存器说明: Frame height generation
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_frame_size_7        : 13; /* bit[0-12] : See previous definition on VP_RD_FHG_0 */
        unsigned int  reserved_0               : 3;  /* bit[13-15]:  */
        unsigned int  vprd_vertical_blanking_7 : 8;  /* bit[16-23]: See previous definition on VP_RD_FHG_0 */
        unsigned int  reserved_1               : 8;  /* bit[24-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_RD_FHG_7_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_RD_FHG_7_vprd_frame_size_7_START         (0)
#define SOC_ISP_CVDR_CVDR_VP_RD_FHG_7_vprd_frame_size_7_END           (12)
#define SOC_ISP_CVDR_CVDR_VP_RD_FHG_7_vprd_vertical_blanking_7_START  (16)
#define SOC_ISP_CVDR_CVDR_VP_RD_FHG_7_vprd_vertical_blanking_7_END    (23)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_RD_AXI_FS_7_UNION
 结构说明  : CVDR_VP_RD_AXI_FS_7 寄存器结构定义。地址偏移量:0x5EC，初值:0x00000000，宽度:32
 寄存器说明: AXI frame start
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved               : 4;  /* bit[0-3] :  */
        unsigned int  vprd_axi_frame_start_7 : 28; /* bit[4-31]: See previous definition on VP_RD_AXI_FS_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_RD_AXI_FS_7_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_FS_7_vprd_axi_frame_start_7_START  (4)
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_FS_7_vprd_axi_frame_start_7_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_7_UNION
 结构说明  : CVDR_VP_RD_AXI_LINE_7 寄存器结构定义。地址偏移量:0x5F0，初值:0x1FFF0000，宽度:32
 寄存器说明: Line Wrap definition
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_line_stride_7 : 10; /* bit[0-9]  : See previous definition on VP_RD_AXI_LINE_0 */
        unsigned int  reserved_0         : 6;  /* bit[10-15]:  */
        unsigned int  vprd_line_wrap_7   : 13; /* bit[16-28]: See previous definition on VP_RD_AXI_LINE_0 */
        unsigned int  reserved_1         : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_7_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_7_vprd_line_stride_7_START  (0)
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_7_vprd_line_stride_7_END    (9)
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_7_vprd_line_wrap_7_START    (16)
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_7_vprd_line_wrap_7_END      (28)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_7_UNION
 结构说明  : CVDR_VP_RD_PREFETCH_7 寄存器结构定义。地址偏移量:0x5F4，初值:0x00000908，宽度:32
 寄存器说明: Configure the prefetch mechanism and must be aligned with the SMMU configuration.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_index_id0_7       : 7;  /* bit[0-6]  : See previous definition on VP_RD_PREFETCH_0 */
        unsigned int  reserved_0             : 1;  /* bit[7-7]  :  */
        unsigned int  vprd_index_id1_7       : 7;  /* bit[8-14] : See previous definition on VP_RD_PREFETCH_0 */
        unsigned int  reserved_1             : 16; /* bit[15-30]:  */
        unsigned int  vprd_prefetch_bypass_7 : 1;  /* bit[31-31]: See previous definition on VP_RD_PREFETCH_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_7_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_7_vprd_index_id0_7_START        (0)
#define SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_7_vprd_index_id0_7_END          (6)
#define SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_7_vprd_index_id1_7_START        (8)
#define SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_7_vprd_index_id1_7_END          (14)
#define SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_7_vprd_prefetch_bypass_7_START  (31)
#define SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_7_vprd_prefetch_bypass_7_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_RD_DEBUG_7_UNION
 结构说明  : CVDR_VP_RD_DEBUG_7 寄存器结构定义。地址偏移量:0x5FC，初值:0x00000000，宽度:32
 寄存器说明: Video Port Read DEBUG information
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vp_rd_debug_7 : 32; /* bit[0-31]: See previous definition on VP_RD_DEBUG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_RD_DEBUG_7_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_RD_DEBUG_7_vp_rd_debug_7_START  (0)
#define SOC_ISP_CVDR_CVDR_VP_RD_DEBUG_7_vp_rd_debug_7_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_RD_CFG_8_UNION
 结构说明  : CVDR_VP_RD_CFG_8 寄存器结构定义。地址偏移量:0x600，初值:0x00000000，宽度:32
 寄存器说明: Video port read Configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_pixel_format_8    : 4;  /* bit[0-3]  : See previous definition on VP_RD_CFG_0 */
        unsigned int  vprd_pixel_expansion_8 : 1;  /* bit[4-4]  : See previous definition on VP_RD_CFG_0 */
        unsigned int  vprd_allocated_du_8    : 5;  /* bit[5-9]  : See previous definition on VP_RD_CFG_0 */
        unsigned int  reserved               : 5;  /* bit[10-14]:  */
        unsigned int  vprd_last_page_8       : 17; /* bit[15-31]: See previous definition on VP_RD_CFG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_RD_CFG_8_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_8_vprd_pixel_format_8_START     (0)
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_8_vprd_pixel_format_8_END       (3)
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_8_vprd_pixel_expansion_8_START  (4)
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_8_vprd_pixel_expansion_8_END    (4)
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_8_vprd_allocated_du_8_START     (5)
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_8_vprd_allocated_du_8_END       (9)
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_8_vprd_last_page_8_START        (15)
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_8_vprd_last_page_8_END          (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_RD_LWG_8_UNION
 结构说明  : CVDR_VP_RD_LWG_8 寄存器结构定义。地址偏移量:0x604，初值:0x00000000，宽度:32
 寄存器说明: Line width generation
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_line_size_8           : 13; /* bit[0-12] : See previous definition on VP_RD_LWG_0 */
        unsigned int  reserved_0                 : 3;  /* bit[13-15]:  */
        unsigned int  vprd_horizontal_blanking_8 : 8;  /* bit[16-23]: See previous definition on VP_RD_LWG_0 */
        unsigned int  reserved_1                 : 8;  /* bit[24-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_RD_LWG_8_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_RD_LWG_8_vprd_line_size_8_START            (0)
#define SOC_ISP_CVDR_CVDR_VP_RD_LWG_8_vprd_line_size_8_END              (12)
#define SOC_ISP_CVDR_CVDR_VP_RD_LWG_8_vprd_horizontal_blanking_8_START  (16)
#define SOC_ISP_CVDR_CVDR_VP_RD_LWG_8_vprd_horizontal_blanking_8_END    (23)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_RD_FHG_8_UNION
 结构说明  : CVDR_VP_RD_FHG_8 寄存器结构定义。地址偏移量:0x608，初值:0x00000000，宽度:32
 寄存器说明: Frame height generation
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_frame_size_8        : 13; /* bit[0-12] : See previous definition on VP_RD_FHG_0 */
        unsigned int  reserved_0               : 3;  /* bit[13-15]:  */
        unsigned int  vprd_vertical_blanking_8 : 8;  /* bit[16-23]: See previous definition on VP_RD_FHG_0 */
        unsigned int  reserved_1               : 8;  /* bit[24-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_RD_FHG_8_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_RD_FHG_8_vprd_frame_size_8_START         (0)
#define SOC_ISP_CVDR_CVDR_VP_RD_FHG_8_vprd_frame_size_8_END           (12)
#define SOC_ISP_CVDR_CVDR_VP_RD_FHG_8_vprd_vertical_blanking_8_START  (16)
#define SOC_ISP_CVDR_CVDR_VP_RD_FHG_8_vprd_vertical_blanking_8_END    (23)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_RD_AXI_FS_8_UNION
 结构说明  : CVDR_VP_RD_AXI_FS_8 寄存器结构定义。地址偏移量:0x60C，初值:0x00000000，宽度:32
 寄存器说明: AXI frame start
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved               : 4;  /* bit[0-3] :  */
        unsigned int  vprd_axi_frame_start_8 : 28; /* bit[4-31]: See previous definition on VP_RD_AXI_FS_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_RD_AXI_FS_8_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_FS_8_vprd_axi_frame_start_8_START  (4)
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_FS_8_vprd_axi_frame_start_8_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_8_UNION
 结构说明  : CVDR_VP_RD_AXI_LINE_8 寄存器结构定义。地址偏移量:0x610，初值:0x1FFF0000，宽度:32
 寄存器说明: Line Wrap definition
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_line_stride_8 : 10; /* bit[0-9]  : See previous definition on VP_RD_AXI_LINE_0 */
        unsigned int  reserved_0         : 6;  /* bit[10-15]:  */
        unsigned int  vprd_line_wrap_8   : 13; /* bit[16-28]: See previous definition on VP_RD_AXI_LINE_0 */
        unsigned int  reserved_1         : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_8_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_8_vprd_line_stride_8_START  (0)
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_8_vprd_line_stride_8_END    (9)
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_8_vprd_line_wrap_8_START    (16)
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_8_vprd_line_wrap_8_END      (28)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_8_UNION
 结构说明  : CVDR_VP_RD_PREFETCH_8 寄存器结构定义。地址偏移量:0x614，初值:0x00000B0A，宽度:32
 寄存器说明: Configure the prefetch mechanism and must be aligned with the SMMU configuration.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_index_id0_8       : 7;  /* bit[0-6]  : See previous definition on VP_RD_PREFETCH_0 */
        unsigned int  reserved_0             : 1;  /* bit[7-7]  :  */
        unsigned int  vprd_index_id1_8       : 7;  /* bit[8-14] : See previous definition on VP_RD_PREFETCH_0 */
        unsigned int  reserved_1             : 16; /* bit[15-30]:  */
        unsigned int  vprd_prefetch_bypass_8 : 1;  /* bit[31-31]: See previous definition on VP_RD_PREFETCH_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_8_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_8_vprd_index_id0_8_START        (0)
#define SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_8_vprd_index_id0_8_END          (6)
#define SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_8_vprd_index_id1_8_START        (8)
#define SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_8_vprd_index_id1_8_END          (14)
#define SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_8_vprd_prefetch_bypass_8_START  (31)
#define SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_8_vprd_prefetch_bypass_8_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_RD_DEBUG_8_UNION
 结构说明  : CVDR_VP_RD_DEBUG_8 寄存器结构定义。地址偏移量:0x61C，初值:0x00000000，宽度:32
 寄存器说明: Video Port Read DEBUG information
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vp_rd_debug_8 : 32; /* bit[0-31]: See previous definition on VP_RD_DEBUG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_RD_DEBUG_8_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_RD_DEBUG_8_vp_rd_debug_8_START  (0)
#define SOC_ISP_CVDR_CVDR_VP_RD_DEBUG_8_vp_rd_debug_8_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_RD_CFG_9_UNION
 结构说明  : CVDR_VP_RD_CFG_9 寄存器结构定义。地址偏移量:0x620，初值:0x00000000，宽度:32
 寄存器说明: Video port read Configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_pixel_format_9    : 4;  /* bit[0-3]  : See previous definition on VP_RD_CFG_0 */
        unsigned int  vprd_pixel_expansion_9 : 1;  /* bit[4-4]  : See previous definition on VP_RD_CFG_0 */
        unsigned int  vprd_allocated_du_9    : 5;  /* bit[5-9]  : See previous definition on VP_RD_CFG_0 */
        unsigned int  reserved               : 5;  /* bit[10-14]:  */
        unsigned int  vprd_last_page_9       : 17; /* bit[15-31]: See previous definition on VP_RD_CFG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_RD_CFG_9_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_9_vprd_pixel_format_9_START     (0)
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_9_vprd_pixel_format_9_END       (3)
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_9_vprd_pixel_expansion_9_START  (4)
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_9_vprd_pixel_expansion_9_END    (4)
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_9_vprd_allocated_du_9_START     (5)
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_9_vprd_allocated_du_9_END       (9)
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_9_vprd_last_page_9_START        (15)
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_9_vprd_last_page_9_END          (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_RD_LWG_9_UNION
 结构说明  : CVDR_VP_RD_LWG_9 寄存器结构定义。地址偏移量:0x624，初值:0x00000000，宽度:32
 寄存器说明: Line width generation
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_line_size_9           : 13; /* bit[0-12] : See previous definition on VP_RD_LWG_0 */
        unsigned int  reserved_0                 : 3;  /* bit[13-15]:  */
        unsigned int  vprd_horizontal_blanking_9 : 8;  /* bit[16-23]: See previous definition on VP_RD_LWG_0 */
        unsigned int  reserved_1                 : 8;  /* bit[24-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_RD_LWG_9_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_RD_LWG_9_vprd_line_size_9_START            (0)
#define SOC_ISP_CVDR_CVDR_VP_RD_LWG_9_vprd_line_size_9_END              (12)
#define SOC_ISP_CVDR_CVDR_VP_RD_LWG_9_vprd_horizontal_blanking_9_START  (16)
#define SOC_ISP_CVDR_CVDR_VP_RD_LWG_9_vprd_horizontal_blanking_9_END    (23)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_RD_FHG_9_UNION
 结构说明  : CVDR_VP_RD_FHG_9 寄存器结构定义。地址偏移量:0x628，初值:0x00000000，宽度:32
 寄存器说明: Frame height generation
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_frame_size_9        : 13; /* bit[0-12] : See previous definition on VP_RD_FHG_0 */
        unsigned int  reserved_0               : 3;  /* bit[13-15]:  */
        unsigned int  vprd_vertical_blanking_9 : 8;  /* bit[16-23]: See previous definition on VP_RD_FHG_0 */
        unsigned int  reserved_1               : 8;  /* bit[24-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_RD_FHG_9_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_RD_FHG_9_vprd_frame_size_9_START         (0)
#define SOC_ISP_CVDR_CVDR_VP_RD_FHG_9_vprd_frame_size_9_END           (12)
#define SOC_ISP_CVDR_CVDR_VP_RD_FHG_9_vprd_vertical_blanking_9_START  (16)
#define SOC_ISP_CVDR_CVDR_VP_RD_FHG_9_vprd_vertical_blanking_9_END    (23)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_RD_AXI_FS_9_UNION
 结构说明  : CVDR_VP_RD_AXI_FS_9 寄存器结构定义。地址偏移量:0x62C，初值:0x00000000，宽度:32
 寄存器说明: AXI frame start
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved               : 4;  /* bit[0-3] :  */
        unsigned int  vprd_axi_frame_start_9 : 28; /* bit[4-31]: See previous definition on VP_RD_AXI_FS_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_RD_AXI_FS_9_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_FS_9_vprd_axi_frame_start_9_START  (4)
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_FS_9_vprd_axi_frame_start_9_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_9_UNION
 结构说明  : CVDR_VP_RD_AXI_LINE_9 寄存器结构定义。地址偏移量:0x630，初值:0x1FFF0000，宽度:32
 寄存器说明: Line Wrap definition
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_line_stride_9 : 10; /* bit[0-9]  : See previous definition on VP_RD_AXI_LINE_0 */
        unsigned int  reserved_0         : 6;  /* bit[10-15]:  */
        unsigned int  vprd_line_wrap_9   : 13; /* bit[16-28]: See previous definition on VP_RD_AXI_LINE_0 */
        unsigned int  reserved_1         : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_9_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_9_vprd_line_stride_9_START  (0)
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_9_vprd_line_stride_9_END    (9)
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_9_vprd_line_wrap_9_START    (16)
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_9_vprd_line_wrap_9_END      (28)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_9_UNION
 结构说明  : CVDR_VP_RD_PREFETCH_9 寄存器结构定义。地址偏移量:0x634，初值:0x00000D0C，宽度:32
 寄存器说明: Configure the prefetch mechanism and must be aligned with the SMMU configuration.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_index_id0_9       : 7;  /* bit[0-6]  : See previous definition on VP_RD_PREFETCH_0 */
        unsigned int  reserved_0             : 1;  /* bit[7-7]  :  */
        unsigned int  vprd_index_id1_9       : 7;  /* bit[8-14] : See previous definition on VP_RD_PREFETCH_0 */
        unsigned int  reserved_1             : 16; /* bit[15-30]:  */
        unsigned int  vprd_prefetch_bypass_9 : 1;  /* bit[31-31]: See previous definition on VP_RD_PREFETCH_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_9_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_9_vprd_index_id0_9_START        (0)
#define SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_9_vprd_index_id0_9_END          (6)
#define SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_9_vprd_index_id1_9_START        (8)
#define SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_9_vprd_index_id1_9_END          (14)
#define SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_9_vprd_prefetch_bypass_9_START  (31)
#define SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_9_vprd_prefetch_bypass_9_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_RD_DEBUG_9_UNION
 结构说明  : CVDR_VP_RD_DEBUG_9 寄存器结构定义。地址偏移量:0x63C，初值:0x00000000，宽度:32
 寄存器说明: Video Port Read DEBUG information
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vp_rd_debug_9 : 32; /* bit[0-31]: See previous definition on VP_RD_DEBUG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_RD_DEBUG_9_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_RD_DEBUG_9_vp_rd_debug_9_START  (0)
#define SOC_ISP_CVDR_CVDR_VP_RD_DEBUG_9_vp_rd_debug_9_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_RD_CFG_10_UNION
 结构说明  : CVDR_VP_RD_CFG_10 寄存器结构定义。地址偏移量:0x640，初值:0x00000000，宽度:32
 寄存器说明: Video port read Configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_pixel_format_10    : 4;  /* bit[0-3]  : See previous definition on VP_RD_CFG_0 */
        unsigned int  vprd_pixel_expansion_10 : 1;  /* bit[4-4]  : See previous definition on VP_RD_CFG_0 */
        unsigned int  vprd_allocated_du_10    : 5;  /* bit[5-9]  : See previous definition on VP_RD_CFG_0 */
        unsigned int  reserved                : 5;  /* bit[10-14]:  */
        unsigned int  vprd_last_page_10       : 17; /* bit[15-31]: See previous definition on VP_RD_CFG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_RD_CFG_10_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_10_vprd_pixel_format_10_START     (0)
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_10_vprd_pixel_format_10_END       (3)
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_10_vprd_pixel_expansion_10_START  (4)
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_10_vprd_pixel_expansion_10_END    (4)
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_10_vprd_allocated_du_10_START     (5)
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_10_vprd_allocated_du_10_END       (9)
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_10_vprd_last_page_10_START        (15)
#define SOC_ISP_CVDR_CVDR_VP_RD_CFG_10_vprd_last_page_10_END          (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_RD_LWG_10_UNION
 结构说明  : CVDR_VP_RD_LWG_10 寄存器结构定义。地址偏移量:0x644，初值:0x00000000，宽度:32
 寄存器说明: Line width generation
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_line_size_10           : 13; /* bit[0-12] : See previous definition on VP_RD_LWG_0 */
        unsigned int  reserved_0                  : 3;  /* bit[13-15]:  */
        unsigned int  vprd_horizontal_blanking_10 : 8;  /* bit[16-23]: See previous definition on VP_RD_LWG_0 */
        unsigned int  reserved_1                  : 8;  /* bit[24-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_RD_LWG_10_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_RD_LWG_10_vprd_line_size_10_START            (0)
#define SOC_ISP_CVDR_CVDR_VP_RD_LWG_10_vprd_line_size_10_END              (12)
#define SOC_ISP_CVDR_CVDR_VP_RD_LWG_10_vprd_horizontal_blanking_10_START  (16)
#define SOC_ISP_CVDR_CVDR_VP_RD_LWG_10_vprd_horizontal_blanking_10_END    (23)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_RD_FHG_10_UNION
 结构说明  : CVDR_VP_RD_FHG_10 寄存器结构定义。地址偏移量:0x648，初值:0x00000000，宽度:32
 寄存器说明: Frame height generation
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_frame_size_10        : 13; /* bit[0-12] : See previous definition on VP_RD_FHG_0 */
        unsigned int  reserved_0                : 3;  /* bit[13-15]:  */
        unsigned int  vprd_vertical_blanking_10 : 8;  /* bit[16-23]: See previous definition on VP_RD_FHG_0 */
        unsigned int  reserved_1                : 8;  /* bit[24-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_RD_FHG_10_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_RD_FHG_10_vprd_frame_size_10_START         (0)
#define SOC_ISP_CVDR_CVDR_VP_RD_FHG_10_vprd_frame_size_10_END           (12)
#define SOC_ISP_CVDR_CVDR_VP_RD_FHG_10_vprd_vertical_blanking_10_START  (16)
#define SOC_ISP_CVDR_CVDR_VP_RD_FHG_10_vprd_vertical_blanking_10_END    (23)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_RD_AXI_FS_10_UNION
 结构说明  : CVDR_VP_RD_AXI_FS_10 寄存器结构定义。地址偏移量:0x64C，初值:0x00000000，宽度:32
 寄存器说明: AXI frame start
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved                : 4;  /* bit[0-3] :  */
        unsigned int  vprd_axi_frame_start_10 : 28; /* bit[4-31]: See previous definition on VP_RD_AXI_FS_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_RD_AXI_FS_10_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_FS_10_vprd_axi_frame_start_10_START  (4)
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_FS_10_vprd_axi_frame_start_10_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_10_UNION
 结构说明  : CVDR_VP_RD_AXI_LINE_10 寄存器结构定义。地址偏移量:0x650，初值:0x1FFF0000，宽度:32
 寄存器说明: Line Wrap definition
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_line_stride_10 : 10; /* bit[0-9]  : See previous definition on VP_RD_AXI_LINE_0 */
        unsigned int  reserved_0          : 6;  /* bit[10-15]:  */
        unsigned int  vprd_line_wrap_10   : 13; /* bit[16-28]: See previous definition on VP_RD_AXI_LINE_0 */
        unsigned int  reserved_1          : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_10_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_10_vprd_line_stride_10_START  (0)
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_10_vprd_line_stride_10_END    (9)
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_10_vprd_line_wrap_10_START    (16)
#define SOC_ISP_CVDR_CVDR_VP_RD_AXI_LINE_10_vprd_line_wrap_10_END      (28)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_10_UNION
 结构说明  : CVDR_VP_RD_PREFETCH_10 寄存器结构定义。地址偏移量:0x654，初值:0x00000F0E，宽度:32
 寄存器说明: Configure the prefetch mechanism and must be aligned with the SMMU configuration.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_index_id0_10       : 7;  /* bit[0-6]  : See previous definition on VP_RD_PREFETCH_0 */
        unsigned int  reserved_0              : 1;  /* bit[7-7]  :  */
        unsigned int  vprd_index_id1_10       : 7;  /* bit[8-14] : See previous definition on VP_RD_PREFETCH_0 */
        unsigned int  reserved_1              : 16; /* bit[15-30]:  */
        unsigned int  vprd_prefetch_bypass_10 : 1;  /* bit[31-31]: See previous definition on VP_RD_PREFETCH_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_10_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_10_vprd_index_id0_10_START        (0)
#define SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_10_vprd_index_id0_10_END          (6)
#define SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_10_vprd_index_id1_10_START        (8)
#define SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_10_vprd_index_id1_10_END          (14)
#define SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_10_vprd_prefetch_bypass_10_START  (31)
#define SOC_ISP_CVDR_CVDR_VP_RD_PREFETCH_10_vprd_prefetch_bypass_10_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_RD_DEBUG_10_UNION
 结构说明  : CVDR_VP_RD_DEBUG_10 寄存器结构定义。地址偏移量:0x65C，初值:0x00000000，宽度:32
 寄存器说明: Video Port Read DEBUG information
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vp_rd_debug_10 : 32; /* bit[0-31]: See previous definition on VP_RD_DEBUG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_RD_DEBUG_10_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_RD_DEBUG_10_vp_rd_debug_10_START  (0)
#define SOC_ISP_CVDR_CVDR_VP_RD_DEBUG_10_vp_rd_debug_10_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_0_UNION
 结构说明  : CVDR_LIMITER_VP_RD_0 寄存器结构定义。地址偏移量:0x880，初值:0x0F00FFFF，宽度:32
 寄存器说明: Video port read Access limiter
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_access_limiter_0_0      : 4;  /* bit[0-3]  : "CVDR RAM access limiter: maximum number of read 128 bit accesses allowed on a 32 clock cycle windowReturnToLine0: 0 access allowed (unexpected in regular SW)ReturnToLine1: 1 access maximum allowedReturnToLineand so onReturnToLine15: 15 accesses maximum allowed" */
        unsigned int  vprd_access_limiter_1_0      : 4;  /* bit[4-7]  : see description of access_limiter_0 */
        unsigned int  vprd_access_limiter_2_0      : 4;  /* bit[8-11] : see description of access_limiter_0 */
        unsigned int  vprd_access_limiter_3_0      : 4;  /* bit[12-15]: see description of access_limiter_0 */
        unsigned int  reserved_0                   : 8;  /* bit[16-23]:  */
        unsigned int  vprd_access_limiter_reload_0 : 4;  /* bit[24-27]: "Access limiter reload functionality: controls the throughput available for a given initiator over 128 cycles.ReturnToLineWhen 0xF */
        unsigned int  reserved_1                   : 4;  /* bit[28-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_0_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_0_vprd_access_limiter_0_0_START       (0)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_0_vprd_access_limiter_0_0_END         (3)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_0_vprd_access_limiter_1_0_START       (4)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_0_vprd_access_limiter_1_0_END         (7)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_0_vprd_access_limiter_2_0_START       (8)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_0_vprd_access_limiter_2_0_END         (11)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_0_vprd_access_limiter_3_0_START       (12)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_0_vprd_access_limiter_3_0_END         (15)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_0_vprd_access_limiter_reload_0_START  (24)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_0_vprd_access_limiter_reload_0_END    (27)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_4_UNION
 结构说明  : CVDR_LIMITER_VP_RD_4 寄存器结构定义。地址偏移量:0x890，初值:0x0F00FFFF，宽度:32
 寄存器说明: Video port read Access limiter
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_access_limiter_0_4      : 4;  /* bit[0-3]  : See previous definition on LIMITER_VP_RD_0 */
        unsigned int  vprd_access_limiter_1_4      : 4;  /* bit[4-7]  : See previous definition on LIMITER_VP_RD_0 */
        unsigned int  vprd_access_limiter_2_4      : 4;  /* bit[8-11] : See previous definition on LIMITER_VP_RD_0 */
        unsigned int  vprd_access_limiter_3_4      : 4;  /* bit[12-15]: See previous definition on LIMITER_VP_RD_0 */
        unsigned int  reserved_0                   : 8;  /* bit[16-23]:  */
        unsigned int  vprd_access_limiter_reload_4 : 4;  /* bit[24-27]: See previous definition on LIMITER_VP_RD_0 */
        unsigned int  reserved_1                   : 4;  /* bit[28-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_4_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_4_vprd_access_limiter_0_4_START       (0)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_4_vprd_access_limiter_0_4_END         (3)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_4_vprd_access_limiter_1_4_START       (4)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_4_vprd_access_limiter_1_4_END         (7)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_4_vprd_access_limiter_2_4_START       (8)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_4_vprd_access_limiter_2_4_END         (11)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_4_vprd_access_limiter_3_4_START       (12)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_4_vprd_access_limiter_3_4_END         (15)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_4_vprd_access_limiter_reload_4_START  (24)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_4_vprd_access_limiter_reload_4_END    (27)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_5_UNION
 结构说明  : CVDR_LIMITER_VP_RD_5 寄存器结构定义。地址偏移量:0x894，初值:0x0F00FFFF，宽度:32
 寄存器说明: Video port read Access limiter
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_access_limiter_0_5      : 4;  /* bit[0-3]  : See previous definition on LIMITER_VP_RD_0 */
        unsigned int  vprd_access_limiter_1_5      : 4;  /* bit[4-7]  : See previous definition on LIMITER_VP_RD_0 */
        unsigned int  vprd_access_limiter_2_5      : 4;  /* bit[8-11] : See previous definition on LIMITER_VP_RD_0 */
        unsigned int  vprd_access_limiter_3_5      : 4;  /* bit[12-15]: See previous definition on LIMITER_VP_RD_0 */
        unsigned int  reserved_0                   : 8;  /* bit[16-23]:  */
        unsigned int  vprd_access_limiter_reload_5 : 4;  /* bit[24-27]: See previous definition on LIMITER_VP_RD_0 */
        unsigned int  reserved_1                   : 4;  /* bit[28-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_5_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_5_vprd_access_limiter_0_5_START       (0)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_5_vprd_access_limiter_0_5_END         (3)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_5_vprd_access_limiter_1_5_START       (4)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_5_vprd_access_limiter_1_5_END         (7)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_5_vprd_access_limiter_2_5_START       (8)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_5_vprd_access_limiter_2_5_END         (11)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_5_vprd_access_limiter_3_5_START       (12)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_5_vprd_access_limiter_3_5_END         (15)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_5_vprd_access_limiter_reload_5_START  (24)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_5_vprd_access_limiter_reload_5_END    (27)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_6_UNION
 结构说明  : CVDR_LIMITER_VP_RD_6 寄存器结构定义。地址偏移量:0x898，初值:0x0F00FFFF，宽度:32
 寄存器说明: Video port read Access limiter
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_access_limiter_0_6      : 4;  /* bit[0-3]  : See previous definition on LIMITER_VP_RD_0 */
        unsigned int  vprd_access_limiter_1_6      : 4;  /* bit[4-7]  : See previous definition on LIMITER_VP_RD_0 */
        unsigned int  vprd_access_limiter_2_6      : 4;  /* bit[8-11] : See previous definition on LIMITER_VP_RD_0 */
        unsigned int  vprd_access_limiter_3_6      : 4;  /* bit[12-15]: See previous definition on LIMITER_VP_RD_0 */
        unsigned int  reserved_0                   : 8;  /* bit[16-23]:  */
        unsigned int  vprd_access_limiter_reload_6 : 4;  /* bit[24-27]: See previous definition on LIMITER_VP_RD_0 */
        unsigned int  reserved_1                   : 4;  /* bit[28-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_6_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_6_vprd_access_limiter_0_6_START       (0)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_6_vprd_access_limiter_0_6_END         (3)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_6_vprd_access_limiter_1_6_START       (4)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_6_vprd_access_limiter_1_6_END         (7)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_6_vprd_access_limiter_2_6_START       (8)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_6_vprd_access_limiter_2_6_END         (11)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_6_vprd_access_limiter_3_6_START       (12)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_6_vprd_access_limiter_3_6_END         (15)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_6_vprd_access_limiter_reload_6_START  (24)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_6_vprd_access_limiter_reload_6_END    (27)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_7_UNION
 结构说明  : CVDR_LIMITER_VP_RD_7 寄存器结构定义。地址偏移量:0x89C，初值:0x0F00FFFF，宽度:32
 寄存器说明: Video port read Access limiter
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_access_limiter_0_7      : 4;  /* bit[0-3]  : See previous definition on LIMITER_VP_RD_0 */
        unsigned int  vprd_access_limiter_1_7      : 4;  /* bit[4-7]  : See previous definition on LIMITER_VP_RD_0 */
        unsigned int  vprd_access_limiter_2_7      : 4;  /* bit[8-11] : See previous definition on LIMITER_VP_RD_0 */
        unsigned int  vprd_access_limiter_3_7      : 4;  /* bit[12-15]: See previous definition on LIMITER_VP_RD_0 */
        unsigned int  reserved_0                   : 8;  /* bit[16-23]:  */
        unsigned int  vprd_access_limiter_reload_7 : 4;  /* bit[24-27]: See previous definition on LIMITER_VP_RD_0 */
        unsigned int  reserved_1                   : 4;  /* bit[28-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_7_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_7_vprd_access_limiter_0_7_START       (0)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_7_vprd_access_limiter_0_7_END         (3)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_7_vprd_access_limiter_1_7_START       (4)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_7_vprd_access_limiter_1_7_END         (7)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_7_vprd_access_limiter_2_7_START       (8)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_7_vprd_access_limiter_2_7_END         (11)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_7_vprd_access_limiter_3_7_START       (12)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_7_vprd_access_limiter_3_7_END         (15)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_7_vprd_access_limiter_reload_7_START  (24)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_7_vprd_access_limiter_reload_7_END    (27)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_8_UNION
 结构说明  : CVDR_LIMITER_VP_RD_8 寄存器结构定义。地址偏移量:0x8A0，初值:0x0F00FFFF，宽度:32
 寄存器说明: Video port read Access limiter
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_access_limiter_0_8      : 4;  /* bit[0-3]  : See previous definition on LIMITER_VP_RD_0 */
        unsigned int  vprd_access_limiter_1_8      : 4;  /* bit[4-7]  : See previous definition on LIMITER_VP_RD_0 */
        unsigned int  vprd_access_limiter_2_8      : 4;  /* bit[8-11] : See previous definition on LIMITER_VP_RD_0 */
        unsigned int  vprd_access_limiter_3_8      : 4;  /* bit[12-15]: See previous definition on LIMITER_VP_RD_0 */
        unsigned int  reserved_0                   : 8;  /* bit[16-23]:  */
        unsigned int  vprd_access_limiter_reload_8 : 4;  /* bit[24-27]: See previous definition on LIMITER_VP_RD_0 */
        unsigned int  reserved_1                   : 4;  /* bit[28-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_8_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_8_vprd_access_limiter_0_8_START       (0)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_8_vprd_access_limiter_0_8_END         (3)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_8_vprd_access_limiter_1_8_START       (4)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_8_vprd_access_limiter_1_8_END         (7)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_8_vprd_access_limiter_2_8_START       (8)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_8_vprd_access_limiter_2_8_END         (11)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_8_vprd_access_limiter_3_8_START       (12)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_8_vprd_access_limiter_3_8_END         (15)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_8_vprd_access_limiter_reload_8_START  (24)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_8_vprd_access_limiter_reload_8_END    (27)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_9_UNION
 结构说明  : CVDR_LIMITER_VP_RD_9 寄存器结构定义。地址偏移量:0x8A4，初值:0x0F00FFFF，宽度:32
 寄存器说明: Video port read Access limiter
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_access_limiter_0_9      : 4;  /* bit[0-3]  : See previous definition on LIMITER_VP_RD_0 */
        unsigned int  vprd_access_limiter_1_9      : 4;  /* bit[4-7]  : See previous definition on LIMITER_VP_RD_0 */
        unsigned int  vprd_access_limiter_2_9      : 4;  /* bit[8-11] : See previous definition on LIMITER_VP_RD_0 */
        unsigned int  vprd_access_limiter_3_9      : 4;  /* bit[12-15]: See previous definition on LIMITER_VP_RD_0 */
        unsigned int  reserved_0                   : 8;  /* bit[16-23]:  */
        unsigned int  vprd_access_limiter_reload_9 : 4;  /* bit[24-27]: See previous definition on LIMITER_VP_RD_0 */
        unsigned int  reserved_1                   : 4;  /* bit[28-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_9_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_9_vprd_access_limiter_0_9_START       (0)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_9_vprd_access_limiter_0_9_END         (3)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_9_vprd_access_limiter_1_9_START       (4)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_9_vprd_access_limiter_1_9_END         (7)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_9_vprd_access_limiter_2_9_START       (8)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_9_vprd_access_limiter_2_9_END         (11)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_9_vprd_access_limiter_3_9_START       (12)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_9_vprd_access_limiter_3_9_END         (15)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_9_vprd_access_limiter_reload_9_START  (24)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_9_vprd_access_limiter_reload_9_END    (27)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_10_UNION
 结构说明  : CVDR_LIMITER_VP_RD_10 寄存器结构定义。地址偏移量:0x8A8，初值:0x0F00FFFF，宽度:32
 寄存器说明: Video port read Access limiter
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_access_limiter_0_10      : 4;  /* bit[0-3]  : See previous definition on LIMITER_VP_RD_0 */
        unsigned int  vprd_access_limiter_1_10      : 4;  /* bit[4-7]  : See previous definition on LIMITER_VP_RD_0 */
        unsigned int  vprd_access_limiter_2_10      : 4;  /* bit[8-11] : See previous definition on LIMITER_VP_RD_0 */
        unsigned int  vprd_access_limiter_3_10      : 4;  /* bit[12-15]: See previous definition on LIMITER_VP_RD_0 */
        unsigned int  reserved_0                    : 8;  /* bit[16-23]:  */
        unsigned int  vprd_access_limiter_reload_10 : 4;  /* bit[24-27]: See previous definition on LIMITER_VP_RD_0 */
        unsigned int  reserved_1                    : 4;  /* bit[28-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_10_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_10_vprd_access_limiter_0_10_START       (0)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_10_vprd_access_limiter_0_10_END         (3)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_10_vprd_access_limiter_1_10_START       (4)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_10_vprd_access_limiter_1_10_END         (7)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_10_vprd_access_limiter_2_10_START       (8)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_10_vprd_access_limiter_2_10_END         (11)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_10_vprd_access_limiter_3_10_START       (12)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_10_vprd_access_limiter_3_10_END         (15)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_10_vprd_access_limiter_reload_10_START  (24)
#define SOC_ISP_CVDR_CVDR_LIMITER_VP_RD_10_vprd_access_limiter_reload_10_END    (27)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_NR_RD_CFG_1_UNION
 结构说明  : CVDR_NR_RD_CFG_1 寄存器结构定义。地址偏移量:0xA10，初值:0x00000000，宽度:32
 寄存器说明: Initiator read Configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0              : 5;  /* bit[0-4]  :  */
        unsigned int  nrrd_allocated_du_1     : 5;  /* bit[5-9]  : "Number of allocated DUsReturnToLineA maximum of 32 DUs can be allocated per video port" */
        unsigned int  reserved_1              : 4;  /* bit[10-13]:  */
        unsigned int  nr_rd_slowdown_enable_1 : 1;  /* bit[14-14]: "Enables the slow down mode on non-raster read interface.ReturnToLineWhen enabled */
        unsigned int  reserved_2              : 16; /* bit[15-30]:  */
        unsigned int  nrrd_enable_1           : 1;  /* bit[31-31]: Enable or stop the initiator acquisition (at any time) */
    } reg;
} SOC_ISP_CVDR_CVDR_NR_RD_CFG_1_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_NR_RD_CFG_1_nrrd_allocated_du_1_START      (5)
#define SOC_ISP_CVDR_CVDR_NR_RD_CFG_1_nrrd_allocated_du_1_END        (9)
#define SOC_ISP_CVDR_CVDR_NR_RD_CFG_1_nr_rd_slowdown_enable_1_START  (14)
#define SOC_ISP_CVDR_CVDR_NR_RD_CFG_1_nr_rd_slowdown_enable_1_END    (14)
#define SOC_ISP_CVDR_CVDR_NR_RD_CFG_1_nrrd_enable_1_START            (31)
#define SOC_ISP_CVDR_CVDR_NR_RD_CFG_1_nrrd_enable_1_END              (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_NR_RD_DEBUG_1_UNION
 结构说明  : CVDR_NR_RD_DEBUG_1 寄存器结构定义。地址偏移量:0xA14，初值:0x00000000，宽度:32
 寄存器说明: Non-Raster Read DEBUG information
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  nr_rd_debug_1 : 32; /* bit[0-31]: Non-Raster Read DEBUG information */
    } reg;
} SOC_ISP_CVDR_CVDR_NR_RD_DEBUG_1_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_NR_RD_DEBUG_1_nr_rd_debug_1_START  (0)
#define SOC_ISP_CVDR_CVDR_NR_RD_DEBUG_1_nr_rd_debug_1_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_LIMITER_NR_RD_1_UNION
 结构说明  : CVDR_LIMITER_NR_RD_1 寄存器结构定义。地址偏移量:0xA18，初值:0x0F00FFFF，宽度:32
 寄存器说明: NR RD Access limiter
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  nrrd_access_limiter_0_1      : 4;  /* bit[0-3]  : "CVDR RAM access limiter: maximum number of read 128 bit accesses allowed on a 32 clock cycle windowReturnToLine0: 0 access allowed (unexpected in regular SW)ReturnToLine1: 1 access maximum allowedReturnToLineand so onReturnToLine15: 15 accesses maximum allowed" */
        unsigned int  nrrd_access_limiter_1_1      : 4;  /* bit[4-7]  : see description of access_limiter_0 */
        unsigned int  nrrd_access_limiter_2_1      : 4;  /* bit[8-11] : see description of access_limiter_0 */
        unsigned int  nrrd_access_limiter_3_1      : 4;  /* bit[12-15]: see description of access_limiter_0 */
        unsigned int  reserved_0                   : 8;  /* bit[16-23]:  */
        unsigned int  nrrd_access_limiter_reload_1 : 4;  /* bit[24-27]: "Access limiter reload functionality: controls the throughput available for a given initiator over 128 cycles.ReturnToLineWhen 0xF */
        unsigned int  reserved_1                   : 4;  /* bit[28-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_LIMITER_NR_RD_1_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_LIMITER_NR_RD_1_nrrd_access_limiter_0_1_START       (0)
#define SOC_ISP_CVDR_CVDR_LIMITER_NR_RD_1_nrrd_access_limiter_0_1_END         (3)
#define SOC_ISP_CVDR_CVDR_LIMITER_NR_RD_1_nrrd_access_limiter_1_1_START       (4)
#define SOC_ISP_CVDR_CVDR_LIMITER_NR_RD_1_nrrd_access_limiter_1_1_END         (7)
#define SOC_ISP_CVDR_CVDR_LIMITER_NR_RD_1_nrrd_access_limiter_2_1_START       (8)
#define SOC_ISP_CVDR_CVDR_LIMITER_NR_RD_1_nrrd_access_limiter_2_1_END         (11)
#define SOC_ISP_CVDR_CVDR_LIMITER_NR_RD_1_nrrd_access_limiter_3_1_START       (12)
#define SOC_ISP_CVDR_CVDR_LIMITER_NR_RD_1_nrrd_access_limiter_3_1_END         (15)
#define SOC_ISP_CVDR_CVDR_LIMITER_NR_RD_1_nrrd_access_limiter_reload_1_START  (24)
#define SOC_ISP_CVDR_CVDR_LIMITER_NR_RD_1_nrrd_access_limiter_reload_1_END    (27)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_NR_RD_CFG_2_UNION
 结构说明  : CVDR_NR_RD_CFG_2 寄存器结构定义。地址偏移量:0xA20，初值:0x00000000，宽度:32
 寄存器说明: Initiator read Configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0              : 5;  /* bit[0-4]  :  */
        unsigned int  nrrd_allocated_du_2     : 5;  /* bit[5-9]  : See previous definition on NR_RD_CFG_1 */
        unsigned int  reserved_1              : 4;  /* bit[10-13]:  */
        unsigned int  nr_rd_slowdown_enable_2 : 1;  /* bit[14-14]: See previous definition on NR_RD_CFG_1 */
        unsigned int  reserved_2              : 16; /* bit[15-30]:  */
        unsigned int  nrrd_enable_2           : 1;  /* bit[31-31]: See previous definition on NR_RD_CFG_1 */
    } reg;
} SOC_ISP_CVDR_CVDR_NR_RD_CFG_2_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_NR_RD_CFG_2_nrrd_allocated_du_2_START      (5)
#define SOC_ISP_CVDR_CVDR_NR_RD_CFG_2_nrrd_allocated_du_2_END        (9)
#define SOC_ISP_CVDR_CVDR_NR_RD_CFG_2_nr_rd_slowdown_enable_2_START  (14)
#define SOC_ISP_CVDR_CVDR_NR_RD_CFG_2_nr_rd_slowdown_enable_2_END    (14)
#define SOC_ISP_CVDR_CVDR_NR_RD_CFG_2_nrrd_enable_2_START            (31)
#define SOC_ISP_CVDR_CVDR_NR_RD_CFG_2_nrrd_enable_2_END              (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_NR_RD_DEBUG_2_UNION
 结构说明  : CVDR_NR_RD_DEBUG_2 寄存器结构定义。地址偏移量:0xA24，初值:0x00000000，宽度:32
 寄存器说明: Non-Raster Read DEBUG information
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  nr_rd_debug_2 : 32; /* bit[0-31]: See previous definition on NR_RD_DEBUG_1 */
    } reg;
} SOC_ISP_CVDR_CVDR_NR_RD_DEBUG_2_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_NR_RD_DEBUG_2_nr_rd_debug_2_START  (0)
#define SOC_ISP_CVDR_CVDR_NR_RD_DEBUG_2_nr_rd_debug_2_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_LIMITER_NR_RD_2_UNION
 结构说明  : CVDR_LIMITER_NR_RD_2 寄存器结构定义。地址偏移量:0xA28，初值:0x0F00FFFF，宽度:32
 寄存器说明: NR RD Access limiter
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  nrrd_access_limiter_0_2      : 4;  /* bit[0-3]  : See previous definition on LIMITER_NR_RD_1 */
        unsigned int  nrrd_access_limiter_1_2      : 4;  /* bit[4-7]  : See previous definition on LIMITER_NR_RD_1 */
        unsigned int  nrrd_access_limiter_2_2      : 4;  /* bit[8-11] : See previous definition on LIMITER_NR_RD_1 */
        unsigned int  nrrd_access_limiter_3_2      : 4;  /* bit[12-15]: See previous definition on LIMITER_NR_RD_1 */
        unsigned int  reserved_0                   : 8;  /* bit[16-23]:  */
        unsigned int  nrrd_access_limiter_reload_2 : 4;  /* bit[24-27]: See previous definition on LIMITER_NR_RD_1 */
        unsigned int  reserved_1                   : 4;  /* bit[28-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_LIMITER_NR_RD_2_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_LIMITER_NR_RD_2_nrrd_access_limiter_0_2_START       (0)
#define SOC_ISP_CVDR_CVDR_LIMITER_NR_RD_2_nrrd_access_limiter_0_2_END         (3)
#define SOC_ISP_CVDR_CVDR_LIMITER_NR_RD_2_nrrd_access_limiter_1_2_START       (4)
#define SOC_ISP_CVDR_CVDR_LIMITER_NR_RD_2_nrrd_access_limiter_1_2_END         (7)
#define SOC_ISP_CVDR_CVDR_LIMITER_NR_RD_2_nrrd_access_limiter_2_2_START       (8)
#define SOC_ISP_CVDR_CVDR_LIMITER_NR_RD_2_nrrd_access_limiter_2_2_END         (11)
#define SOC_ISP_CVDR_CVDR_LIMITER_NR_RD_2_nrrd_access_limiter_3_2_START       (12)
#define SOC_ISP_CVDR_CVDR_LIMITER_NR_RD_2_nrrd_access_limiter_3_2_END         (15)
#define SOC_ISP_CVDR_CVDR_LIMITER_NR_RD_2_nrrd_access_limiter_reload_2_START  (24)
#define SOC_ISP_CVDR_CVDR_LIMITER_NR_RD_2_nrrd_access_limiter_reload_2_END    (27)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_DEBUG_0_UNION
 结构说明  : CVDR_DEBUG_0 寄存器结构定义。地址偏移量:0xB00，初值:0x00000000，宽度:32
 寄存器说明: DEBUG information
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  debug_0 : 32; /* bit[0-31]: DEBUG information */
    } reg;
} SOC_ISP_CVDR_CVDR_DEBUG_0_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_DEBUG_0_debug_0_START  (0)
#define SOC_ISP_CVDR_CVDR_DEBUG_0_debug_0_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_DEBUG_1_UNION
 结构说明  : CVDR_DEBUG_1 寄存器结构定义。地址偏移量:0xB04，初值:0x00000000，宽度:32
 寄存器说明: DEBUG information
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  debug_1 : 32; /* bit[0-31]: See previous definition on DEBUG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_DEBUG_1_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_DEBUG_1_debug_1_START  (0)
#define SOC_ISP_CVDR_CVDR_DEBUG_1_debug_1_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_DEBUG_2_UNION
 结构说明  : CVDR_DEBUG_2 寄存器结构定义。地址偏移量:0xB08，初值:0x00000000，宽度:32
 寄存器说明: DEBUG information
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  debug_2 : 32; /* bit[0-31]: See previous definition on DEBUG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_DEBUG_2_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_DEBUG_2_debug_2_START  (0)
#define SOC_ISP_CVDR_CVDR_DEBUG_2_debug_2_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_DEBUG_3_UNION
 结构说明  : CVDR_DEBUG_3 寄存器结构定义。地址偏移量:0xB0C，初值:0x00000000，宽度:32
 寄存器说明: DEBUG information
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  debug_3 : 32; /* bit[0-31]: See previous definition on DEBUG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_DEBUG_3_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_DEBUG_3_debug_3_START  (0)
#define SOC_ISP_CVDR_CVDR_DEBUG_3_debug_3_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_DEBUG_4_UNION
 结构说明  : CVDR_DEBUG_4 寄存器结构定义。地址偏移量:0xB10，初值:0x00000000，宽度:32
 寄存器说明: DEBUG information
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  debug_4 : 32; /* bit[0-31]: See previous definition on DEBUG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_DEBUG_4_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_DEBUG_4_debug_4_START  (0)
#define SOC_ISP_CVDR_CVDR_DEBUG_4_debug_4_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_DEBUG_5_UNION
 结构说明  : CVDR_DEBUG_5 寄存器结构定义。地址偏移量:0xB14，初值:0x00000000，宽度:32
 寄存器说明: DEBUG information
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  debug_5 : 32; /* bit[0-31]: See previous definition on DEBUG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_DEBUG_5_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_DEBUG_5_debug_5_START  (0)
#define SOC_ISP_CVDR_CVDR_DEBUG_5_debug_5_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_DEBUG_6_UNION
 结构说明  : CVDR_DEBUG_6 寄存器结构定义。地址偏移量:0xB18，初值:0x00000000，宽度:32
 寄存器说明: DEBUG information
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  debug_6 : 32; /* bit[0-31]: See previous definition on DEBUG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_DEBUG_6_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_DEBUG_6_debug_6_START  (0)
#define SOC_ISP_CVDR_CVDR_DEBUG_6_debug_6_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_DEBUG_7_UNION
 结构说明  : CVDR_DEBUG_7 寄存器结构定义。地址偏移量:0xB1C，初值:0x00000000，宽度:32
 寄存器说明: DEBUG information
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  debug_7 : 32; /* bit[0-31]: See previous definition on DEBUG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_DEBUG_7_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_DEBUG_7_debug_7_START  (0)
#define SOC_ISP_CVDR_CVDR_DEBUG_7_debug_7_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_DEBUG_8_UNION
 结构说明  : CVDR_DEBUG_8 寄存器结构定义。地址偏移量:0xB20，初值:0x00000000，宽度:32
 寄存器说明: DEBUG information
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  debug_8 : 32; /* bit[0-31]: See previous definition on DEBUG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_DEBUG_8_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_DEBUG_8_debug_8_START  (0)
#define SOC_ISP_CVDR_CVDR_DEBUG_8_debug_8_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_DEBUG_9_UNION
 结构说明  : CVDR_DEBUG_9 寄存器结构定义。地址偏移量:0xB24，初值:0x00000000，宽度:32
 寄存器说明: DEBUG information
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  debug_9 : 32; /* bit[0-31]: See previous definition on DEBUG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_DEBUG_9_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_DEBUG_9_debug_9_START  (0)
#define SOC_ISP_CVDR_CVDR_DEBUG_9_debug_9_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_DEBUG_10_UNION
 结构说明  : CVDR_DEBUG_10 寄存器结构定义。地址偏移量:0xB28，初值:0x00000000，宽度:32
 寄存器说明: DEBUG information
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  debug_10 : 32; /* bit[0-31]: See previous definition on DEBUG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_DEBUG_10_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_DEBUG_10_debug_10_START  (0)
#define SOC_ISP_CVDR_CVDR_DEBUG_10_debug_10_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_DEBUG_11_UNION
 结构说明  : CVDR_DEBUG_11 寄存器结构定义。地址偏移量:0xB2C，初值:0x00000000，宽度:32
 寄存器说明: DEBUG information
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  debug_11 : 32; /* bit[0-31]: See previous definition on DEBUG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_DEBUG_11_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_DEBUG_11_debug_11_START  (0)
#define SOC_ISP_CVDR_CVDR_DEBUG_11_debug_11_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_DEBUG_12_UNION
 结构说明  : CVDR_DEBUG_12 寄存器结构定义。地址偏移量:0xB30，初值:0x00000000，宽度:32
 寄存器说明: DEBUG information
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  debug_12 : 32; /* bit[0-31]: See previous definition on DEBUG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_DEBUG_12_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_DEBUG_12_debug_12_START  (0)
#define SOC_ISP_CVDR_CVDR_DEBUG_12_debug_12_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_DEBUG_13_UNION
 结构说明  : CVDR_DEBUG_13 寄存器结构定义。地址偏移量:0xB34，初值:0x00000000，宽度:32
 寄存器说明: DEBUG information
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  debug_13 : 32; /* bit[0-31]: See previous definition on DEBUG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_DEBUG_13_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_DEBUG_13_debug_13_START  (0)
#define SOC_ISP_CVDR_CVDR_DEBUG_13_debug_13_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_DEBUG_14_UNION
 结构说明  : CVDR_DEBUG_14 寄存器结构定义。地址偏移量:0xB38，初值:0x00000000，宽度:32
 寄存器说明: DEBUG information
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  debug_14 : 32; /* bit[0-31]: See previous definition on DEBUG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_DEBUG_14_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_DEBUG_14_debug_14_START  (0)
#define SOC_ISP_CVDR_CVDR_DEBUG_14_debug_14_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_DEBUG_15_UNION
 结构说明  : CVDR_DEBUG_15 寄存器结构定义。地址偏移量:0xB3C，初值:0x00000000，宽度:32
 寄存器说明: DEBUG information
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  debug_15 : 32; /* bit[0-31]: See previous definition on DEBUG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_DEBUG_15_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_DEBUG_15_debug_15_START  (0)
#define SOC_ISP_CVDR_CVDR_DEBUG_15_debug_15_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_AXI_CFG_NR_RD_1_UNION
 结构说明  : CVDR_AXI_CFG_NR_RD_1 寄存器结构定义。地址偏移量:0xC44，初值:0x0000000D，宽度:32
 寄存器说明: NR read Master ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  nr_rd_mid_1 : 5;  /* bit[0-4] : Master ID configuration register. A MID information is attached to AXI transactions (Commands) for SOC debug purpose */
        unsigned int  reserved    : 27; /* bit[5-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_AXI_CFG_NR_RD_1_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_AXI_CFG_NR_RD_1_nr_rd_mid_1_START  (0)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_NR_RD_1_nr_rd_mid_1_END    (4)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_AXI_CFG_NR_RD_2_UNION
 结构说明  : CVDR_AXI_CFG_NR_RD_2 寄存器结构定义。地址偏移量:0xC48，初值:0x0000000D，宽度:32
 寄存器说明: NR read Master ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  nr_rd_mid_2 : 5;  /* bit[0-4] : See previous definition on AXI_CFG_NR_RD_1 */
        unsigned int  reserved    : 27; /* bit[5-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_AXI_CFG_NR_RD_2_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_AXI_CFG_NR_RD_2_nr_rd_mid_2_START  (0)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_NR_RD_2_nr_rd_mid_2_END    (4)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_0_UNION
 结构说明  : CVDR_AXI_CFG_VP_WR_0 寄存器结构定义。地址偏移量:0xC80，初值:0x0000000A，宽度:32
 寄存器说明: VP write master ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vp_wr_mid_0 : 5;  /* bit[0-4]  : Master ID configuration register. A MID information is attached to AXI transactions (Commands) for SOC debug purpose */
        unsigned int  reserved_0  : 3;  /* bit[5-7]  :  */
        unsigned int  vp_wr_sid_0 : 6;  /* bit[8-13] : StreamID configuration register. Used by MMU */
        unsigned int  reserved_1  : 18; /* bit[14-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_0_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_0_vp_wr_mid_0_START  (0)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_0_vp_wr_mid_0_END    (4)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_0_vp_wr_sid_0_START  (8)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_0_vp_wr_sid_0_END    (13)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_1_UNION
 结构说明  : CVDR_AXI_CFG_VP_WR_1 寄存器结构定义。地址偏移量:0xC84，初值:0x0000010A，宽度:32
 寄存器说明: VP write master ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vp_wr_mid_1 : 5;  /* bit[0-4]  : See previous definition on AXI_CFG_VP_WR_0 */
        unsigned int  reserved_0  : 3;  /* bit[5-7]  :  */
        unsigned int  vp_wr_sid_1 : 6;  /* bit[8-13] : See previous definition on AXI_CFG_VP_WR_0 */
        unsigned int  reserved_1  : 18; /* bit[14-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_1_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_1_vp_wr_mid_1_START  (0)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_1_vp_wr_mid_1_END    (4)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_1_vp_wr_sid_1_START  (8)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_1_vp_wr_sid_1_END    (13)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_4_UNION
 结构说明  : CVDR_AXI_CFG_VP_WR_4 寄存器结构定义。地址偏移量:0xC90，初值:0x0000020A，宽度:32
 寄存器说明: VP write master ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vp_wr_mid_4 : 5;  /* bit[0-4]  : See previous definition on AXI_CFG_VP_WR_0 */
        unsigned int  reserved_0  : 3;  /* bit[5-7]  :  */
        unsigned int  vp_wr_sid_4 : 6;  /* bit[8-13] : See previous definition on AXI_CFG_VP_WR_0 */
        unsigned int  reserved_1  : 18; /* bit[14-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_4_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_4_vp_wr_mid_4_START  (0)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_4_vp_wr_mid_4_END    (4)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_4_vp_wr_sid_4_START  (8)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_4_vp_wr_sid_4_END    (13)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_5_UNION
 结构说明  : CVDR_AXI_CFG_VP_WR_5 寄存器结构定义。地址偏移量:0xC94，初值:0x0000030A，宽度:32
 寄存器说明: VP write master ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vp_wr_mid_5 : 5;  /* bit[0-4]  : See previous definition on AXI_CFG_VP_WR_0 */
        unsigned int  reserved_0  : 3;  /* bit[5-7]  :  */
        unsigned int  vp_wr_sid_5 : 6;  /* bit[8-13] : See previous definition on AXI_CFG_VP_WR_0 */
        unsigned int  reserved_1  : 18; /* bit[14-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_5_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_5_vp_wr_mid_5_START  (0)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_5_vp_wr_mid_5_END    (4)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_5_vp_wr_sid_5_START  (8)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_5_vp_wr_sid_5_END    (13)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_8_UNION
 结构说明  : CVDR_AXI_CFG_VP_WR_8 寄存器结构定义。地址偏移量:0xCA0，初值:0x0000040A，宽度:32
 寄存器说明: VP write master ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vp_wr_mid_8 : 5;  /* bit[0-4]  : See previous definition on AXI_CFG_VP_WR_0 */
        unsigned int  reserved_0  : 3;  /* bit[5-7]  :  */
        unsigned int  vp_wr_sid_8 : 6;  /* bit[8-13] : See previous definition on AXI_CFG_VP_WR_0 */
        unsigned int  reserved_1  : 18; /* bit[14-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_8_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_8_vp_wr_mid_8_START  (0)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_8_vp_wr_mid_8_END    (4)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_8_vp_wr_sid_8_START  (8)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_8_vp_wr_sid_8_END    (13)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_9_UNION
 结构说明  : CVDR_AXI_CFG_VP_WR_9 寄存器结构定义。地址偏移量:0xCA4，初值:0x0000050A，宽度:32
 寄存器说明: VP write master ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vp_wr_mid_9 : 5;  /* bit[0-4]  : See previous definition on AXI_CFG_VP_WR_0 */
        unsigned int  reserved_0  : 3;  /* bit[5-7]  :  */
        unsigned int  vp_wr_sid_9 : 6;  /* bit[8-13] : See previous definition on AXI_CFG_VP_WR_0 */
        unsigned int  reserved_1  : 18; /* bit[14-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_9_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_9_vp_wr_mid_9_START  (0)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_9_vp_wr_mid_9_END    (4)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_9_vp_wr_sid_9_START  (8)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_9_vp_wr_sid_9_END    (13)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_14_UNION
 结构说明  : CVDR_AXI_CFG_VP_WR_14 寄存器结构定义。地址偏移量:0xCB8，初值:0x0000060A，宽度:32
 寄存器说明: VP write master ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vp_wr_mid_14 : 5;  /* bit[0-4]  : See previous definition on AXI_CFG_VP_WR_0 */
        unsigned int  reserved_0   : 3;  /* bit[5-7]  :  */
        unsigned int  vp_wr_sid_14 : 6;  /* bit[8-13] : See previous definition on AXI_CFG_VP_WR_0 */
        unsigned int  reserved_1   : 18; /* bit[14-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_14_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_14_vp_wr_mid_14_START  (0)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_14_vp_wr_mid_14_END    (4)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_14_vp_wr_sid_14_START  (8)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_14_vp_wr_sid_14_END    (13)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_15_UNION
 结构说明  : CVDR_AXI_CFG_VP_WR_15 寄存器结构定义。地址偏移量:0xCBC，初值:0x0000070A，宽度:32
 寄存器说明: VP write master ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vp_wr_mid_15 : 5;  /* bit[0-4]  : See previous definition on AXI_CFG_VP_WR_0 */
        unsigned int  reserved_0   : 3;  /* bit[5-7]  :  */
        unsigned int  vp_wr_sid_15 : 6;  /* bit[8-13] : See previous definition on AXI_CFG_VP_WR_0 */
        unsigned int  reserved_1   : 18; /* bit[14-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_15_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_15_vp_wr_mid_15_START  (0)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_15_vp_wr_mid_15_END    (4)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_15_vp_wr_sid_15_START  (8)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_15_vp_wr_sid_15_END    (13)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_16_UNION
 结构说明  : CVDR_AXI_CFG_VP_WR_16 寄存器结构定义。地址偏移量:0xCC0，初值:0x0000080A，宽度:32
 寄存器说明: VP write master ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vp_wr_mid_16 : 5;  /* bit[0-4]  : See previous definition on AXI_CFG_VP_WR_0 */
        unsigned int  reserved_0   : 3;  /* bit[5-7]  :  */
        unsigned int  vp_wr_sid_16 : 6;  /* bit[8-13] : See previous definition on AXI_CFG_VP_WR_0 */
        unsigned int  reserved_1   : 18; /* bit[14-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_16_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_16_vp_wr_mid_16_START  (0)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_16_vp_wr_mid_16_END    (4)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_16_vp_wr_sid_16_START  (8)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_16_vp_wr_sid_16_END    (13)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_17_UNION
 结构说明  : CVDR_AXI_CFG_VP_WR_17 寄存器结构定义。地址偏移量:0xCC4，初值:0x0000090A，宽度:32
 寄存器说明: VP write master ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vp_wr_mid_17 : 5;  /* bit[0-4]  : See previous definition on AXI_CFG_VP_WR_0 */
        unsigned int  reserved_0   : 3;  /* bit[5-7]  :  */
        unsigned int  vp_wr_sid_17 : 6;  /* bit[8-13] : See previous definition on AXI_CFG_VP_WR_0 */
        unsigned int  reserved_1   : 18; /* bit[14-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_17_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_17_vp_wr_mid_17_START  (0)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_17_vp_wr_mid_17_END    (4)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_17_vp_wr_sid_17_START  (8)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_17_vp_wr_sid_17_END    (13)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_18_UNION
 结构说明  : CVDR_AXI_CFG_VP_WR_18 寄存器结构定义。地址偏移量:0xCC8，初值:0x00000A0A，宽度:32
 寄存器说明: VP write master ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vp_wr_mid_18 : 5;  /* bit[0-4]  : See previous definition on AXI_CFG_VP_WR_0 */
        unsigned int  reserved_0   : 3;  /* bit[5-7]  :  */
        unsigned int  vp_wr_sid_18 : 6;  /* bit[8-13] : See previous definition on AXI_CFG_VP_WR_0 */
        unsigned int  reserved_1   : 18; /* bit[14-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_18_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_18_vp_wr_mid_18_START  (0)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_18_vp_wr_mid_18_END    (4)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_18_vp_wr_sid_18_START  (8)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_18_vp_wr_sid_18_END    (13)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_19_UNION
 结构说明  : CVDR_AXI_CFG_VP_WR_19 寄存器结构定义。地址偏移量:0xCCC，初值:0x00000B0A，宽度:32
 寄存器说明: VP write master ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vp_wr_mid_19 : 5;  /* bit[0-4]  : See previous definition on AXI_CFG_VP_WR_0 */
        unsigned int  reserved_0   : 3;  /* bit[5-7]  :  */
        unsigned int  vp_wr_sid_19 : 6;  /* bit[8-13] : See previous definition on AXI_CFG_VP_WR_0 */
        unsigned int  reserved_1   : 18; /* bit[14-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_19_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_19_vp_wr_mid_19_START  (0)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_19_vp_wr_mid_19_END    (4)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_19_vp_wr_sid_19_START  (8)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_19_vp_wr_sid_19_END    (13)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_20_UNION
 结构说明  : CVDR_AXI_CFG_VP_WR_20 寄存器结构定义。地址偏移量:0xCD0，初值:0x00000C0A，宽度:32
 寄存器说明: VP write master ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vp_wr_mid_20 : 5;  /* bit[0-4]  : See previous definition on AXI_CFG_VP_WR_0 */
        unsigned int  reserved_0   : 3;  /* bit[5-7]  :  */
        unsigned int  vp_wr_sid_20 : 6;  /* bit[8-13] : See previous definition on AXI_CFG_VP_WR_0 */
        unsigned int  reserved_1   : 18; /* bit[14-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_20_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_20_vp_wr_mid_20_START  (0)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_20_vp_wr_mid_20_END    (4)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_20_vp_wr_sid_20_START  (8)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_20_vp_wr_sid_20_END    (13)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_21_UNION
 结构说明  : CVDR_AXI_CFG_VP_WR_21 寄存器结构定义。地址偏移量:0xCD4，初值:0x00000D0A，宽度:32
 寄存器说明: VP write master ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vp_wr_mid_21 : 5;  /* bit[0-4]  : See previous definition on AXI_CFG_VP_WR_0 */
        unsigned int  reserved_0   : 3;  /* bit[5-7]  :  */
        unsigned int  vp_wr_sid_21 : 6;  /* bit[8-13] : See previous definition on AXI_CFG_VP_WR_0 */
        unsigned int  reserved_1   : 18; /* bit[14-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_21_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_21_vp_wr_mid_21_START  (0)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_21_vp_wr_mid_21_END    (4)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_21_vp_wr_sid_21_START  (8)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_21_vp_wr_sid_21_END    (13)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_22_UNION
 结构说明  : CVDR_AXI_CFG_VP_WR_22 寄存器结构定义。地址偏移量:0xCD8，初值:0x00000E0A，宽度:32
 寄存器说明: VP write master ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vp_wr_mid_22 : 5;  /* bit[0-4]  : See previous definition on AXI_CFG_VP_WR_0 */
        unsigned int  reserved_0   : 3;  /* bit[5-7]  :  */
        unsigned int  vp_wr_sid_22 : 6;  /* bit[8-13] : See previous definition on AXI_CFG_VP_WR_0 */
        unsigned int  reserved_1   : 18; /* bit[14-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_22_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_22_vp_wr_mid_22_START  (0)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_22_vp_wr_mid_22_END    (4)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_22_vp_wr_sid_22_START  (8)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_22_vp_wr_sid_22_END    (13)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_23_UNION
 结构说明  : CVDR_AXI_CFG_VP_WR_23 寄存器结构定义。地址偏移量:0xCDC，初值:0x00000F0A，宽度:32
 寄存器说明: VP write master ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vp_wr_mid_23 : 5;  /* bit[0-4]  : See previous definition on AXI_CFG_VP_WR_0 */
        unsigned int  reserved_0   : 3;  /* bit[5-7]  :  */
        unsigned int  vp_wr_sid_23 : 6;  /* bit[8-13] : See previous definition on AXI_CFG_VP_WR_0 */
        unsigned int  reserved_1   : 18; /* bit[14-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_23_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_23_vp_wr_mid_23_START  (0)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_23_vp_wr_mid_23_END    (4)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_23_vp_wr_sid_23_START  (8)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_23_vp_wr_sid_23_END    (13)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_24_UNION
 结构说明  : CVDR_AXI_CFG_VP_WR_24 寄存器结构定义。地址偏移量:0xCE0，初值:0x0000100A，宽度:32
 寄存器说明: VP write master ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vp_wr_mid_24 : 5;  /* bit[0-4]  : See previous definition on AXI_CFG_VP_WR_0 */
        unsigned int  reserved_0   : 3;  /* bit[5-7]  :  */
        unsigned int  vp_wr_sid_24 : 6;  /* bit[8-13] : See previous definition on AXI_CFG_VP_WR_0 */
        unsigned int  reserved_1   : 18; /* bit[14-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_24_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_24_vp_wr_mid_24_START  (0)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_24_vp_wr_mid_24_END    (4)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_24_vp_wr_sid_24_START  (8)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_24_vp_wr_sid_24_END    (13)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_25_UNION
 结构说明  : CVDR_AXI_CFG_VP_WR_25 寄存器结构定义。地址偏移量:0xCE4，初值:0x0000110A，宽度:32
 寄存器说明: VP write master ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vp_wr_mid_25 : 5;  /* bit[0-4]  : See previous definition on AXI_CFG_VP_WR_0 */
        unsigned int  reserved_0   : 3;  /* bit[5-7]  :  */
        unsigned int  vp_wr_sid_25 : 6;  /* bit[8-13] : See previous definition on AXI_CFG_VP_WR_0 */
        unsigned int  reserved_1   : 18; /* bit[14-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_25_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_25_vp_wr_mid_25_START  (0)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_25_vp_wr_mid_25_END    (4)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_25_vp_wr_sid_25_START  (8)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_25_vp_wr_sid_25_END    (13)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_26_UNION
 结构说明  : CVDR_AXI_CFG_VP_WR_26 寄存器结构定义。地址偏移量:0xCE8，初值:0x0000120A，宽度:32
 寄存器说明: VP write master ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vp_wr_mid_26 : 5;  /* bit[0-4]  : See previous definition on AXI_CFG_VP_WR_0 */
        unsigned int  reserved_0   : 3;  /* bit[5-7]  :  */
        unsigned int  vp_wr_sid_26 : 6;  /* bit[8-13] : See previous definition on AXI_CFG_VP_WR_0 */
        unsigned int  reserved_1   : 18; /* bit[14-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_26_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_26_vp_wr_mid_26_START  (0)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_26_vp_wr_mid_26_END    (4)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_26_vp_wr_sid_26_START  (8)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_26_vp_wr_sid_26_END    (13)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_27_UNION
 结构说明  : CVDR_AXI_CFG_VP_WR_27 寄存器结构定义。地址偏移量:0xCEC，初值:0x0000130A，宽度:32
 寄存器说明: VP write master ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vp_wr_mid_27 : 5;  /* bit[0-4]  : See previous definition on AXI_CFG_VP_WR_0 */
        unsigned int  reserved_0   : 3;  /* bit[5-7]  :  */
        unsigned int  vp_wr_sid_27 : 6;  /* bit[8-13] : See previous definition on AXI_CFG_VP_WR_0 */
        unsigned int  reserved_1   : 18; /* bit[14-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_27_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_27_vp_wr_mid_27_START  (0)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_27_vp_wr_mid_27_END    (4)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_27_vp_wr_sid_27_START  (8)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_WR_27_vp_wr_sid_27_END    (13)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_0_UNION
 结构说明  : CVDR_AXI_CFG_VP_RD_0 寄存器结构定义。地址偏移量:0xD80，初值:0x0000140B，宽度:32
 寄存器说明: VP read master ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vp_rd_mid_0 : 5;  /* bit[0-4]  : Master ID configuration register. A MID information is attached to AXI transactions (Commands) for SOC debug purpose */
        unsigned int  reserved_0  : 3;  /* bit[5-7]  :  */
        unsigned int  vp_rd_sid_0 : 6;  /* bit[8-13] : StreamID configuration register. Used by MMU */
        unsigned int  reserved_1  : 18; /* bit[14-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_0_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_0_vp_rd_mid_0_START  (0)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_0_vp_rd_mid_0_END    (4)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_0_vp_rd_sid_0_START  (8)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_0_vp_rd_sid_0_END    (13)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_4_UNION
 结构说明  : CVDR_AXI_CFG_VP_RD_4 寄存器结构定义。地址偏移量:0xD90，初值:0x0000150B，宽度:32
 寄存器说明: VP read master ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vp_rd_mid_4 : 5;  /* bit[0-4]  : See previous definition on AXI_CFG_VP_RD_0 */
        unsigned int  reserved_0  : 3;  /* bit[5-7]  :  */
        unsigned int  vp_rd_sid_4 : 6;  /* bit[8-13] : See previous definition on AXI_CFG_VP_RD_0 */
        unsigned int  reserved_1  : 18; /* bit[14-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_4_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_4_vp_rd_mid_4_START  (0)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_4_vp_rd_mid_4_END    (4)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_4_vp_rd_sid_4_START  (8)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_4_vp_rd_sid_4_END    (13)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_5_UNION
 结构说明  : CVDR_AXI_CFG_VP_RD_5 寄存器结构定义。地址偏移量:0xD94，初值:0x0000160B，宽度:32
 寄存器说明: VP read master ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vp_rd_mid_5 : 5;  /* bit[0-4]  : See previous definition on AXI_CFG_VP_RD_0 */
        unsigned int  reserved_0  : 3;  /* bit[5-7]  :  */
        unsigned int  vp_rd_sid_5 : 6;  /* bit[8-13] : See previous definition on AXI_CFG_VP_RD_0 */
        unsigned int  reserved_1  : 18; /* bit[14-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_5_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_5_vp_rd_mid_5_START  (0)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_5_vp_rd_mid_5_END    (4)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_5_vp_rd_sid_5_START  (8)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_5_vp_rd_sid_5_END    (13)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_6_UNION
 结构说明  : CVDR_AXI_CFG_VP_RD_6 寄存器结构定义。地址偏移量:0xD98，初值:0x0000170B，宽度:32
 寄存器说明: VP read master ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vp_rd_mid_6 : 5;  /* bit[0-4]  : See previous definition on AXI_CFG_VP_RD_0 */
        unsigned int  reserved_0  : 3;  /* bit[5-7]  :  */
        unsigned int  vp_rd_sid_6 : 6;  /* bit[8-13] : See previous definition on AXI_CFG_VP_RD_0 */
        unsigned int  reserved_1  : 18; /* bit[14-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_6_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_6_vp_rd_mid_6_START  (0)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_6_vp_rd_mid_6_END    (4)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_6_vp_rd_sid_6_START  (8)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_6_vp_rd_sid_6_END    (13)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_7_UNION
 结构说明  : CVDR_AXI_CFG_VP_RD_7 寄存器结构定义。地址偏移量:0xD9C，初值:0x0000180B，宽度:32
 寄存器说明: VP read master ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vp_rd_mid_7 : 5;  /* bit[0-4]  : See previous definition on AXI_CFG_VP_RD_0 */
        unsigned int  reserved_0  : 3;  /* bit[5-7]  :  */
        unsigned int  vp_rd_sid_7 : 6;  /* bit[8-13] : See previous definition on AXI_CFG_VP_RD_0 */
        unsigned int  reserved_1  : 18; /* bit[14-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_7_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_7_vp_rd_mid_7_START  (0)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_7_vp_rd_mid_7_END    (4)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_7_vp_rd_sid_7_START  (8)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_7_vp_rd_sid_7_END    (13)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_8_UNION
 结构说明  : CVDR_AXI_CFG_VP_RD_8 寄存器结构定义。地址偏移量:0xDA0，初值:0x0000190B，宽度:32
 寄存器说明: VP read master ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vp_rd_mid_8 : 5;  /* bit[0-4]  : See previous definition on AXI_CFG_VP_RD_0 */
        unsigned int  reserved_0  : 3;  /* bit[5-7]  :  */
        unsigned int  vp_rd_sid_8 : 6;  /* bit[8-13] : See previous definition on AXI_CFG_VP_RD_0 */
        unsigned int  reserved_1  : 18; /* bit[14-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_8_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_8_vp_rd_mid_8_START  (0)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_8_vp_rd_mid_8_END    (4)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_8_vp_rd_sid_8_START  (8)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_8_vp_rd_sid_8_END    (13)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_9_UNION
 结构说明  : CVDR_AXI_CFG_VP_RD_9 寄存器结构定义。地址偏移量:0xDA4，初值:0x00001A0B，宽度:32
 寄存器说明: VP read master ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vp_rd_mid_9 : 5;  /* bit[0-4]  : See previous definition on AXI_CFG_VP_RD_0 */
        unsigned int  reserved_0  : 3;  /* bit[5-7]  :  */
        unsigned int  vp_rd_sid_9 : 6;  /* bit[8-13] : See previous definition on AXI_CFG_VP_RD_0 */
        unsigned int  reserved_1  : 18; /* bit[14-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_9_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_9_vp_rd_mid_9_START  (0)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_9_vp_rd_mid_9_END    (4)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_9_vp_rd_sid_9_START  (8)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_9_vp_rd_sid_9_END    (13)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_10_UNION
 结构说明  : CVDR_AXI_CFG_VP_RD_10 寄存器结构定义。地址偏移量:0xDA8，初值:0x00001B0B，宽度:32
 寄存器说明: VP read master ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vp_rd_mid_10 : 5;  /* bit[0-4]  : See previous definition on AXI_CFG_VP_RD_0 */
        unsigned int  reserved_0   : 3;  /* bit[5-7]  :  */
        unsigned int  vp_rd_sid_10 : 6;  /* bit[8-13] : See previous definition on AXI_CFG_VP_RD_0 */
        unsigned int  reserved_1   : 18; /* bit[14-31]:  */
    } reg;
} SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_10_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_10_vp_rd_mid_10_START  (0)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_10_vp_rd_mid_10_END    (4)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_10_vp_rd_sid_10_START  (8)
#define SOC_ISP_CVDR_CVDR_AXI_CFG_VP_RD_10_vp_rd_sid_10_END    (13)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_SPARE_0_UNION
 结构说明  : CVDR_SPARE_0 寄存器结构定义。地址偏移量:0xE00，初值:0x00000000，宽度:32
 寄存器说明: Spare
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  spare_0 : 32; /* bit[0-31]: spare register for ECOs */
    } reg;
} SOC_ISP_CVDR_CVDR_SPARE_0_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_SPARE_0_spare_0_START  (0)
#define SOC_ISP_CVDR_CVDR_SPARE_0_spare_0_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_SPARE_1_UNION
 结构说明  : CVDR_SPARE_1 寄存器结构定义。地址偏移量:0xE04，初值:0x00000000，宽度:32
 寄存器说明: Spare
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  spare_1 : 32; /* bit[0-31]: See previous definition on SPARE_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_SPARE_1_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_SPARE_1_spare_1_START  (0)
#define SOC_ISP_CVDR_CVDR_SPARE_1_spare_1_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_SPARE_2_UNION
 结构说明  : CVDR_SPARE_2 寄存器结构定义。地址偏移量:0xE08，初值:0x00000000，宽度:32
 寄存器说明: Spare
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  spare_2 : 32; /* bit[0-31]: See previous definition on SPARE_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_SPARE_2_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_SPARE_2_spare_2_START  (0)
#define SOC_ISP_CVDR_CVDR_SPARE_2_spare_2_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_SPARE_3_UNION
 结构说明  : CVDR_SPARE_3 寄存器结构定义。地址偏移量:0xE0C，初值:0x00000000，宽度:32
 寄存器说明: Spare
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  spare_3 : 32; /* bit[0-31]: See previous definition on SPARE_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_SPARE_3_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_SPARE_3_spare_3_START  (0)
#define SOC_ISP_CVDR_CVDR_SPARE_3_spare_3_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_0_UNION
 结构说明  : CVDR_VP_WR_DEBUG_0 寄存器结构定义。地址偏移量:0xF00，初值:0x00000000，宽度:32
 寄存器说明: Video Port Write DEBUG information
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vp_wr_debug_0 : 32; /* bit[0-31]: Video Port Write DEBUG information */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_0_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_0_vp_wr_debug_0_START  (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_0_vp_wr_debug_0_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_1_UNION
 结构说明  : CVDR_VP_WR_DEBUG_1 寄存器结构定义。地址偏移量:0xF04，初值:0x00000000，宽度:32
 寄存器说明: Video Port Write DEBUG information
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vp_wr_debug_1 : 32; /* bit[0-31]: See previous definition on VP_WR_DEBUG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_1_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_1_vp_wr_debug_1_START  (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_1_vp_wr_debug_1_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_4_UNION
 结构说明  : CVDR_VP_WR_DEBUG_4 寄存器结构定义。地址偏移量:0xF10，初值:0x00000000，宽度:32
 寄存器说明: Video Port Write DEBUG information
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vp_wr_debug_4 : 32; /* bit[0-31]: See previous definition on VP_WR_DEBUG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_4_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_4_vp_wr_debug_4_START  (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_4_vp_wr_debug_4_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_5_UNION
 结构说明  : CVDR_VP_WR_DEBUG_5 寄存器结构定义。地址偏移量:0xF14，初值:0x00000000，宽度:32
 寄存器说明: Video Port Write DEBUG information
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vp_wr_debug_5 : 32; /* bit[0-31]: See previous definition on VP_WR_DEBUG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_5_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_5_vp_wr_debug_5_START  (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_5_vp_wr_debug_5_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_8_UNION
 结构说明  : CVDR_VP_WR_DEBUG_8 寄存器结构定义。地址偏移量:0xF20，初值:0x00000000，宽度:32
 寄存器说明: Video Port Write DEBUG information
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vp_wr_debug_8 : 32; /* bit[0-31]: See previous definition on VP_WR_DEBUG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_8_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_8_vp_wr_debug_8_START  (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_8_vp_wr_debug_8_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_9_UNION
 结构说明  : CVDR_VP_WR_DEBUG_9 寄存器结构定义。地址偏移量:0xF24，初值:0x00000000，宽度:32
 寄存器说明: Video Port Write DEBUG information
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vp_wr_debug_9 : 32; /* bit[0-31]: See previous definition on VP_WR_DEBUG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_9_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_9_vp_wr_debug_9_START  (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_9_vp_wr_debug_9_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_14_UNION
 结构说明  : CVDR_VP_WR_DEBUG_14 寄存器结构定义。地址偏移量:0xF38，初值:0x00000000，宽度:32
 寄存器说明: Video Port Write DEBUG information
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vp_wr_debug_14 : 32; /* bit[0-31]: See previous definition on VP_WR_DEBUG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_14_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_14_vp_wr_debug_14_START  (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_14_vp_wr_debug_14_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_15_UNION
 结构说明  : CVDR_VP_WR_DEBUG_15 寄存器结构定义。地址偏移量:0xF3C，初值:0x00000000，宽度:32
 寄存器说明: Video Port Write DEBUG information
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vp_wr_debug_15 : 32; /* bit[0-31]: See previous definition on VP_WR_DEBUG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_15_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_15_vp_wr_debug_15_START  (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_15_vp_wr_debug_15_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_16_UNION
 结构说明  : CVDR_VP_WR_DEBUG_16 寄存器结构定义。地址偏移量:0xF40，初值:0x00000000，宽度:32
 寄存器说明: Video Port Write DEBUG information
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vp_wr_debug_16 : 32; /* bit[0-31]: See previous definition on VP_WR_DEBUG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_16_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_16_vp_wr_debug_16_START  (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_16_vp_wr_debug_16_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_17_UNION
 结构说明  : CVDR_VP_WR_DEBUG_17 寄存器结构定义。地址偏移量:0xF44，初值:0x00000000，宽度:32
 寄存器说明: Video Port Write DEBUG information
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vp_wr_debug_17 : 32; /* bit[0-31]: See previous definition on VP_WR_DEBUG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_17_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_17_vp_wr_debug_17_START  (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_17_vp_wr_debug_17_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_18_UNION
 结构说明  : CVDR_VP_WR_DEBUG_18 寄存器结构定义。地址偏移量:0xF48，初值:0x00000000，宽度:32
 寄存器说明: Video Port Write DEBUG information
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vp_wr_debug_18 : 32; /* bit[0-31]: See previous definition on VP_WR_DEBUG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_18_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_18_vp_wr_debug_18_START  (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_18_vp_wr_debug_18_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_19_UNION
 结构说明  : CVDR_VP_WR_DEBUG_19 寄存器结构定义。地址偏移量:0xF4C，初值:0x00000000，宽度:32
 寄存器说明: Video Port Write DEBUG information
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vp_wr_debug_19 : 32; /* bit[0-31]: See previous definition on VP_WR_DEBUG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_19_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_19_vp_wr_debug_19_START  (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_19_vp_wr_debug_19_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_20_UNION
 结构说明  : CVDR_VP_WR_DEBUG_20 寄存器结构定义。地址偏移量:0xF50，初值:0x00000000，宽度:32
 寄存器说明: Video Port Write DEBUG information
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vp_wr_debug_20 : 32; /* bit[0-31]: See previous definition on VP_WR_DEBUG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_20_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_20_vp_wr_debug_20_START  (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_20_vp_wr_debug_20_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_21_UNION
 结构说明  : CVDR_VP_WR_DEBUG_21 寄存器结构定义。地址偏移量:0xF54，初值:0x00000000，宽度:32
 寄存器说明: Video Port Write DEBUG information
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vp_wr_debug_21 : 32; /* bit[0-31]: See previous definition on VP_WR_DEBUG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_21_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_21_vp_wr_debug_21_START  (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_21_vp_wr_debug_21_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_22_UNION
 结构说明  : CVDR_VP_WR_DEBUG_22 寄存器结构定义。地址偏移量:0xF58，初值:0x00000000，宽度:32
 寄存器说明: Video Port Write DEBUG information
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vp_wr_debug_22 : 32; /* bit[0-31]: See previous definition on VP_WR_DEBUG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_22_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_22_vp_wr_debug_22_START  (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_22_vp_wr_debug_22_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_23_UNION
 结构说明  : CVDR_VP_WR_DEBUG_23 寄存器结构定义。地址偏移量:0xF5C，初值:0x00000000，宽度:32
 寄存器说明: Video Port Write DEBUG information
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vp_wr_debug_23 : 32; /* bit[0-31]: See previous definition on VP_WR_DEBUG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_23_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_23_vp_wr_debug_23_START  (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_23_vp_wr_debug_23_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_24_UNION
 结构说明  : CVDR_VP_WR_DEBUG_24 寄存器结构定义。地址偏移量:0xF60，初值:0x00000000，宽度:32
 寄存器说明: Video Port Write DEBUG information
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vp_wr_debug_24 : 32; /* bit[0-31]: See previous definition on VP_WR_DEBUG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_24_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_24_vp_wr_debug_24_START  (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_24_vp_wr_debug_24_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_25_UNION
 结构说明  : CVDR_VP_WR_DEBUG_25 寄存器结构定义。地址偏移量:0xF64，初值:0x00000000，宽度:32
 寄存器说明: Video Port Write DEBUG information
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vp_wr_debug_25 : 32; /* bit[0-31]: See previous definition on VP_WR_DEBUG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_25_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_25_vp_wr_debug_25_START  (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_25_vp_wr_debug_25_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_26_UNION
 结构说明  : CVDR_VP_WR_DEBUG_26 寄存器结构定义。地址偏移量:0xF68，初值:0x00000000，宽度:32
 寄存器说明: Video Port Write DEBUG information
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vp_wr_debug_26 : 32; /* bit[0-31]: See previous definition on VP_WR_DEBUG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_26_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_26_vp_wr_debug_26_START  (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_26_vp_wr_debug_26_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_27_UNION
 结构说明  : CVDR_VP_WR_DEBUG_27 寄存器结构定义。地址偏移量:0xF6C，初值:0x00000000，宽度:32
 寄存器说明: Video Port Write DEBUG information
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vp_wr_debug_27 : 32; /* bit[0-31]: See previous definition on VP_WR_DEBUG_0 */
    } reg;
} SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_27_UNION;
#endif
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_27_vp_wr_debug_27_START  (0)
#define SOC_ISP_CVDR_CVDR_VP_WR_DEBUG_27_vp_wr_debug_27_END    (31)






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

#endif /* end of soc_isp_cvdr_interface.h */
