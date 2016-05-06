/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_g3d_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:20:35
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_G3D.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_G3D_INTERFACE_H__
#define __SOC_G3D_INTERFACE_H__

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
/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_GPU_ID_UNION */
#define SOC_G3D_GPU_ID_ADDR(base)                     ((base) + (0x0000))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_L2_FEATURES_UNION */
#define SOC_G3D_L2_FEATURES_ADDR(base)                ((base) + (0x0004))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_TILER_FEATURES_UNION */
#define SOC_G3D_TILER_FEATURES_ADDR(base)             ((base) + (0x000C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_MEM_FEATURES_UNION */
#define SOC_G3D_MEM_FEATURES_ADDR(base)               ((base) + (0x0010))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_MMU_FEATURES_UNION */
#define SOC_G3D_MMU_FEATURES_ADDR(base)               ((base) + (0x0014))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_AS_PRESENT_UNION */
#define SOC_G3D_AS_PRESENT_ADDR(base)                 ((base) + (0x0018))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_JS_PRESENT_UNION */
#define SOC_G3D_JS_PRESENT_ADDR(base)                 ((base) + (0x001C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_GPU_IRQ_RAWSTAT_UNION */
#define SOC_G3D_GPU_IRQ_RAWSTAT_ADDR(base)            ((base) + (0x0020))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_GPU_IRQ_CLEAR_UNION */
#define SOC_G3D_GPU_IRQ_CLEAR_ADDR(base)              ((base) + (0x0024))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_GPU_IRQ_MASK_UNION */
#define SOC_G3D_GPU_IRQ_MASK_ADDR(base)               ((base) + (0x0028))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_GPU_IRQ_STATUS_UNION */
#define SOC_G3D_GPU_IRQ_STATUS_ADDR(base)             ((base) + (0x002C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_GPU_COMMAND_UNION */
#define SOC_G3D_GPU_COMMAND_ADDR(base)                ((base) + (0x0030))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_GPU_STATUS_UNION */
#define SOC_G3D_GPU_STATUS_ADDR(base)                 ((base) + (0x0034))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_GPU_FAULTSTATUS_UNION */
#define SOC_G3D_GPU_FAULTSTATUS_ADDR(base)            ((base) + (0x003C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_GPU_FAULTADDRESS_LO_UNION */
#define SOC_G3D_GPU_FAULTADDRESS_LO_ADDR(base)        ((base) + (0x0040))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_GPU_FAULTADDRESS_HI_UNION */
#define SOC_G3D_GPU_FAULTADDRESS_HI_ADDR(base)        ((base) + (0x0044))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_PWR_KEY_UNION */
#define SOC_G3D_PWR_KEY_ADDR(base)                    ((base) + (0x0050))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_PWR_KEYOVERRIDE0_UNION */
#define SOC_G3D_PWR_KEYOVERRIDE0_ADDR(base)           ((base) + (0x0054))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_PWR_KEYOVERRIDE1_UNION */
#define SOC_G3D_PWR_KEYOVERRIDE1_ADDR(base)           ((base) + (0x0058))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_PRFCNT_BASE_LO_UNION */
#define SOC_G3D_PRFCNT_BASE_LO_ADDR(base)             ((base) + (0x0060))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_PRFCNT_BASE_HI_UNION */
#define SOC_G3D_PRFCNT_BASE_HI_ADDR(base)             ((base) + (0x0064))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_PRFCNT_CONFIG_UNION */
#define SOC_G3D_PRFCNT_CONFIG_ADDR(base)              ((base) + (0x0068))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_PRFCNT_JM_EN_UNION */
#define SOC_G3D_PRFCNT_JM_EN_ADDR(base)               ((base) + (0x006C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_PRFCNT_SHADER_EN_UNION */
#define SOC_G3D_PRFCNT_SHADER_EN_ADDR(base)           ((base) + (0x0070))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_PRFCNT_TILER_EN_UNION */
#define SOC_G3D_PRFCNT_TILER_EN_ADDR(base)            ((base) + (0x0074))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_PRFCNT_MMU_L2_EN_UNION */
#define SOC_G3D_PRFCNT_MMU_L2_EN_ADDR(base)           ((base) + (0x007C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_CYCLE_COUNT_LO_UNION */
#define SOC_G3D_CYCLE_COUNT_LO_ADDR(base)             ((base) + (0x0090))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_CYCLE_COUNT_HI_UNION */
#define SOC_G3D_CYCLE_COUNT_HI_ADDR(base)             ((base) + (0x0094))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_TIMESTAMP_LO_UNION */
#define SOC_G3D_TIMESTAMP_LO_ADDR(base)               ((base) + (0x0098))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_TIMESTAMP_HI_UNION */
#define SOC_G3D_TIMESTAMP_HI_ADDR(base)               ((base) + (0x009C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_THREAD_MAX_THREADS_UNION */
#define SOC_G3D_THREAD_MAX_THREADS_ADDR(base)         ((base) + (0x00A0))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_THREAD_MAX_WORKGROUP_UNION */
#define SOC_G3D_THREAD_MAX_WORKGROUP_ADDR(base)       ((base) + (0x00A4))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_THREAD_MAX_BARRIER_SIZE_UNION */
#define SOC_G3D_THREAD_MAX_BARRIER_SIZE_ADDR(base)    ((base) + (0x00A8))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_THREAD_FEATURES_UNION */
#define SOC_G3D_THREAD_FEATURES_ADDR(base)            ((base) + (0x00AC))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_TEXTURE_FEATURES_0_UNION */
#define SOC_G3D_TEXTURE_FEATURES_0_ADDR(base)         ((base) + (0x00B0))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_TEXTURE_FEATURES_1_UNION */
#define SOC_G3D_TEXTURE_FEATURES_1_ADDR(base)         ((base) + (0x00B4))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_TEXTURE_FEATURES_2_UNION */
#define SOC_G3D_TEXTURE_FEATURES_2_ADDR(base)         ((base) + (0x00B8))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_JS0_FEATURES_UNION */
#define SOC_G3D_JS0_FEATURES_ADDR(base)               ((base) + (0x00C0))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_JS1_FEATURES_UNION */
#define SOC_G3D_JS1_FEATURES_ADDR(base)               ((base) + (0x00C4))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_JS2_FEATURES_UNION */
#define SOC_G3D_JS2_FEATURES_ADDR(base)               ((base) + (0x00C8))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_SHADER_PRESENT_LO_UNION */
#define SOC_G3D_SHADER_PRESENT_LO_ADDR(base)          ((base) + (0x0100))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_SHADER_PRESENT_HI_UNION */
#define SOC_G3D_SHADER_PRESENT_HI_ADDR(base)          ((base) + (0x0104))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_TILER_PRESENT_LO_UNION */
#define SOC_G3D_TILER_PRESENT_LO_ADDR(base)           ((base) + (0x0110))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_TILER_PRESENT_HI_UNION */
#define SOC_G3D_TILER_PRESENT_HI_ADDR(base)           ((base) + (0x0114))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_L2_PRESENT_LO_UNION */
#define SOC_G3D_L2_PRESENT_LO_ADDR(base)              ((base) + (0x0120))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_L2_PRESENT_HI_UNION */
#define SOC_G3D_L2_PRESENT_HI_ADDR(base)              ((base) + (0x0124))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_SHADER_READY_LO_UNION */
#define SOC_G3D_SHADER_READY_LO_ADDR(base)            ((base) + (0x0140))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_SHADER_READY_HI_UNION */
#define SOC_G3D_SHADER_READY_HI_ADDR(base)            ((base) + (0x0144))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_TILER_READY_LO_UNION */
#define SOC_G3D_TILER_READY_LO_ADDR(base)             ((base) + (0x0150))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_TILER_READY_HI_UNION */
#define SOC_G3D_TILER_READY_HI_ADDR(base)             ((base) + (0x0154))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_L2_READY_LO_UNION */
#define SOC_G3D_L2_READY_LO_ADDR(base)                ((base) + (0x0160))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_L2_READY_HI_UNION */
#define SOC_G3D_L2_READY_HI_ADDR(base)                ((base) + (0x0164))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_SHADER_PWRON_LO_UNION */
#define SOC_G3D_SHADER_PWRON_LO_ADDR(base)            ((base) + (0x0180))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_SHADER_PWRON_HI_UNION */
#define SOC_G3D_SHADER_PWRON_HI_ADDR(base)            ((base) + (0x0184))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_TILER_PWRON_LO_UNION */
#define SOC_G3D_TILER_PWRON_LO_ADDR(base)             ((base) + (0x0190))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_TILER_PWRON_HI_UNION */
#define SOC_G3D_TILER_PWRON_HI_ADDR(base)             ((base) + (0x0194))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_L2_PWRON_LO_UNION */
#define SOC_G3D_L2_PWRON_LO_ADDR(base)                ((base) + (0x01A0))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_L2_PWRON_HI_UNION */
#define SOC_G3D_L2_PWRON_HI_ADDR(base)                ((base) + (0x01A4))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_SHADER_PWROFF_LO_UNION */
#define SOC_G3D_SHADER_PWROFF_LO_ADDR(base)           ((base) + (0x01C0))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_SHADER_PWROFF_HI_UNION */
#define SOC_G3D_SHADER_PWROFF_HI_ADDR(base)           ((base) + (0x01C4))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_TILER_PWROFF_LO_UNION */
#define SOC_G3D_TILER_PWROFF_LO_ADDR(base)            ((base) + (0x01D0))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_TILER_PWROFF_HI_UNION */
#define SOC_G3D_TILER_PWROFF_HI_ADDR(base)            ((base) + (0x01D4))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_L2_PWROFF_LO_UNION */
#define SOC_G3D_L2_PWROFF_LO_ADDR(base)               ((base) + (0x01E0))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_L2_PWROFF_HI_UNION */
#define SOC_G3D_L2_PWROFF_HI_ADDR(base)               ((base) + (0x01E4))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_SHADER_PWRTRANS_LO_UNION */
#define SOC_G3D_SHADER_PWRTRANS_LO_ADDR(base)         ((base) + (0x0200))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_SHADER_PWRTRANS_HI_UNION */
#define SOC_G3D_SHADER_PWRTRANS_HI_ADDR(base)         ((base) + (0x0204))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_TILER_PWRTRANS_LO_UNION */
#define SOC_G3D_TILER_PWRTRANS_LO_ADDR(base)          ((base) + (0x0210))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_TILER_PWRTRANS_HI_UNION */
#define SOC_G3D_TILER_PWRTRANS_HI_ADDR(base)          ((base) + (0x0214))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_L2_PWRTRANS_LO_UNION */
#define SOC_G3D_L2_PWRTRANS_LO_ADDR(base)             ((base) + (0x0220))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_L2_PWRTRANS_HI_UNION */
#define SOC_G3D_L2_PWRTRANS_HI_ADDR(base)             ((base) + (0x0224))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_SHADER_PWRACTIVE_LO_UNION */
#define SOC_G3D_SHADER_PWRACTIVE_LO_ADDR(base)        ((base) + (0x0240))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_SHADER_PWRACTIVE_HI_UNION */
#define SOC_G3D_SHADER_PWRACTIVE_HI_ADDR(base)        ((base) + (0x0244))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_TILER_PWRACTIVE_LO_UNION */
#define SOC_G3D_TILER_PWRACTIVE_LO_ADDR(base)         ((base) + (0x0250))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_TILER_PWRACTIVE_HI_UNION */
#define SOC_G3D_TILER_PWRACTIVE_HI_ADDR(base)         ((base) + (0x0254))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_L2_PWRACTIVE_LO_UNION */
#define SOC_G3D_L2_PWRACTIVE_LO_ADDR(base)            ((base) + (0x0260))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_L2_PWRACTIVE_HI_UNION */
#define SOC_G3D_L2_PWRACTIVE_HI_ADDR(base)            ((base) + (0x0264))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_REV_ID_UNION */
#define SOC_G3D_REV_ID_ADDR(base)                     ((base) + (0x0280))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_JM_CONFIG_UNION */
#define SOC_G3D_JM_CONFIG_ADDR(base)                  ((base) + (0x0F00))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_SHADER_CONFIG_UNION */
#define SOC_G3D_SHADER_CONFIG_ADDR(base)              ((base) + (0x0F04))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_TILER_CONFIG_UNION */
#define SOC_G3D_TILER_CONFIG_ADDR(base)               ((base) + (0x0F08))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_L2_MMU_CONFIG_UNION */
#define SOC_G3D_L2_MMU_CONFIG_ADDR(base)              ((base) + (0x0F0C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_JOB_IRQ_RAWSTAT_UNION */
#define SOC_G3D_JOB_IRQ_RAWSTAT_ADDR(base)            ((base) + (0x1000))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_JOB_IRQ_CLEAR_UNION */
#define SOC_G3D_JOB_IRQ_CLEAR_ADDR(base)              ((base) + (0x1004))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_JOB_IRQ_MASK_UNION */
#define SOC_G3D_JOB_IRQ_MASK_ADDR(base)               ((base) + (0x1008))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_JOB_IRQ_STATUS_UNION */
#define SOC_G3D_JOB_IRQ_STATUS_ADDR(base)             ((base) + (0x100C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_JOB_IRQ_JS_STATE_UNION */
#define SOC_G3D_JOB_IRQ_JS_STATE_ADDR(base)           ((base) + (0x1010))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_JOB_IRQ_THROTTLE_UNION */
#define SOC_G3D_JOB_IRQ_THROTTLE_ADDR(base)           ((base) + (0x1014))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_JS0_HEAD_LO_UNION */
#define SOC_G3D_JS0_HEAD_LO_ADDR(base)                ((base) + (0x1800))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_JS0_HEAD_HI_UNION */
#define SOC_G3D_JS0_HEAD_HI_ADDR(base)                ((base) + (0x1804))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_JS0_TAIL_LO_UNION */
#define SOC_G3D_JS0_TAIL_LO_ADDR(base)                ((base) + (0x1808))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_JS0_TAIL_HI_UNION */
#define SOC_G3D_JS0_TAIL_HI_ADDR(base)                ((base) + (0x180C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_JS0_AFFINITY_LO_UNION */
#define SOC_G3D_JS0_AFFINITY_LO_ADDR(base)            ((base) + (0x1810))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_JS0_AFFINITY_HI_UNION */
#define SOC_G3D_JS0_AFFINITY_HI_ADDR(base)            ((base) + (0x1814))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_JS0_CONFIG_UNION */
#define SOC_G3D_JS0_CONFIG_ADDR(base)                 ((base) + (0x1818))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_JS0_COMMAND_UNION */
#define SOC_G3D_JS0_COMMAND_ADDR(base)                ((base) + (0x1820))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_JS0_STATUS_UNION */
#define SOC_G3D_JS0_STATUS_ADDR(base)                 ((base) + (0x1824))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_JS0_HEAD_NEXT_LO_UNION */
#define SOC_G3D_JS0_HEAD_NEXT_LO_ADDR(base)           ((base) + (0x1840))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_JS0_HEAD_NEXT_HI_UNION */
#define SOC_G3D_JS0_HEAD_NEXT_HI_ADDR(base)           ((base) + (0x1844))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_JS0_AFFINITY_NEXT_LO_UNION */
#define SOC_G3D_JS0_AFFINITY_NEXT_LO_ADDR(base)       ((base) + (0x1850))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_JS0_AFFINITY_NEXT_HI_UNION */
#define SOC_G3D_JS0_AFFINITY_NEXT_HI_ADDR(base)       ((base) + (0x1854))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_JS0_CONFIG_NEXT_UNION */
#define SOC_G3D_JS0_CONFIG_NEXT_ADDR(base)            ((base) + (0x1858))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_JS0_COMMAND_NEXT_UNION */
#define SOC_G3D_JS0_COMMAND_NEXT_ADDR(base)           ((base) + (0x1860))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_JS1_HEAD_LO_UNION */
#define SOC_G3D_JS1_HEAD_LO_ADDR(base)                ((base) + (0x1880))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_JS1_HEAD_HI_UNION */
#define SOC_G3D_JS1_HEAD_HI_ADDR(base)                ((base) + (0x1884))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_JS1_TAIL_LO_UNION */
#define SOC_G3D_JS1_TAIL_LO_ADDR(base)                ((base) + (0x1888))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_JS1_TAIL_HI_UNION */
#define SOC_G3D_JS1_TAIL_HI_ADDR(base)                ((base) + (0x188C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_JS1_AFFINITY_LO_UNION */
#define SOC_G3D_JS1_AFFINITY_LO_ADDR(base)            ((base) + (0x1890))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_JS1_AFFINITY_HI_UNION */
#define SOC_G3D_JS1_AFFINITY_HI_ADDR(base)            ((base) + (0x1894))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_JS1_CONFIG_UNION */
#define SOC_G3D_JS1_CONFIG_ADDR(base)                 ((base) + (0x1898))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_JS1_COMMAND_UNION */
#define SOC_G3D_JS1_COMMAND_ADDR(base)                ((base) + (0x18A0))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_JS1_STATUS_UNION */
#define SOC_G3D_JS1_STATUS_ADDR(base)                 ((base) + (0x18A4))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_JS1_HEAD_NEXT_LO_UNION */
#define SOC_G3D_JS1_HEAD_NEXT_LO_ADDR(base)           ((base) + (0x18C0))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_JS1_HEAD_NEXT_HI_UNION */
#define SOC_G3D_JS1_HEAD_NEXT_HI_ADDR(base)           ((base) + (0x18C4))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_JS1_AFFINITY_NEXT_LO_UNION */
#define SOC_G3D_JS1_AFFINITY_NEXT_LO_ADDR(base)       ((base) + (0x18D0))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_JS1_AFFINITY_NEXT_HI_UNION */
#define SOC_G3D_JS1_AFFINITY_NEXT_HI_ADDR(base)       ((base) + (0x18D4))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_JS1_CONFIG_NEXT_UNION */
#define SOC_G3D_JS1_CONFIG_NEXT_ADDR(base)            ((base) + (0x18D8))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_JS1_COMMAND_NEXT_UNION */
#define SOC_G3D_JS1_COMMAND_NEXT_ADDR(base)           ((base) + (0x18E0))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_JS2_HEAD_LO_UNION */
#define SOC_G3D_JS2_HEAD_LO_ADDR(base)                ((base) + (0x1900))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_JS2_HEAD_HI_UNION */
#define SOC_G3D_JS2_HEAD_HI_ADDR(base)                ((base) + (0x1904))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_JS2_TAIL_LO_UNION */
#define SOC_G3D_JS2_TAIL_LO_ADDR(base)                ((base) + (0x1908))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_JS2_TAIL_HI_UNION */
#define SOC_G3D_JS2_TAIL_HI_ADDR(base)                ((base) + (0x190C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_JS2_AFFINITY_LO_UNION */
#define SOC_G3D_JS2_AFFINITY_LO_ADDR(base)            ((base) + (0x1910))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_JS2_AFFINITY_HI_UNION */
#define SOC_G3D_JS2_AFFINITY_HI_ADDR(base)            ((base) + (0x1914))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_JS2_CONFIG_UNION */
#define SOC_G3D_JS2_CONFIG_ADDR(base)                 ((base) + (0x1918))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_JS2_COMMAND_UNION */
#define SOC_G3D_JS2_COMMAND_ADDR(base)                ((base) + (0x1920))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_JS2_STATUS_UNION */
#define SOC_G3D_JS2_STATUS_ADDR(base)                 ((base) + (0x1924))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_JS2_HEAD_NEXT_LO_UNION */
#define SOC_G3D_JS2_HEAD_NEXT_LO_ADDR(base)           ((base) + (0x1940))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_JS2_HEAD_NEXT_HI_UNION */
#define SOC_G3D_JS2_HEAD_NEXT_HI_ADDR(base)           ((base) + (0x1944))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_JS2_AFFINITY_NEXT_LO_UNION */
#define SOC_G3D_JS2_AFFINITY_NEXT_LO_ADDR(base)       ((base) + (0x1950))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_JS2_AFFINITY_NEXT_HI_UNION */
#define SOC_G3D_JS2_AFFINITY_NEXT_HI_ADDR(base)       ((base) + (0x1954))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_JS2_CONFIG_NEXT_UNION */
#define SOC_G3D_JS2_CONFIG_NEXT_ADDR(base)            ((base) + (0x1958))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_JS2_COMMAND_NEXT_UNION */
#define SOC_G3D_JS2_COMMAND_NEXT_ADDR(base)           ((base) + (0x1960))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_MMU_IRQ_RAWSTAT_UNION */
#define SOC_G3D_MMU_IRQ_RAWSTAT_ADDR(base)            ((base) + (0x2000))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_MMU_IRQ_CLEAR_UNION */
#define SOC_G3D_MMU_IRQ_CLEAR_ADDR(base)              ((base) + (0x2004))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_MMU_IRQ_MASK_UNION */
#define SOC_G3D_MMU_IRQ_MASK_ADDR(base)               ((base) + (0x2008))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_MMU_IRQ_STATUS_UNION */
#define SOC_G3D_MMU_IRQ_STATUS_ADDR(base)             ((base) + (0x200C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_AS0_TRANSTAB_LO_UNION */
#define SOC_G3D_AS0_TRANSTAB_LO_ADDR(base)            ((base) + (0x2400))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_AS0_TRANSTAB_HI_UNION */
#define SOC_G3D_AS0_TRANSTAB_HI_ADDR(base)            ((base) + (0x2404))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_AS0_MEMATTR_LO_UNION */
#define SOC_G3D_AS0_MEMATTR_LO_ADDR(base)             ((base) + (0x2408))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_AS0_MEMATTR_HI_UNION */
#define SOC_G3D_AS0_MEMATTR_HI_ADDR(base)             ((base) + (0x240C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_AS0_LOCKADDR_LO_UNION */
#define SOC_G3D_AS0_LOCKADDR_LO_ADDR(base)            ((base) + (0x2410))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_AS0_LOCKADDR_HI_UNION */
#define SOC_G3D_AS0_LOCKADDR_HI_ADDR(base)            ((base) + (0x2414))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_AS0_COMMAND_UNION */
#define SOC_G3D_AS0_COMMAND_ADDR(base)                ((base) + (0x2418))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_AS0_FAULTSTATUS_UNION */
#define SOC_G3D_AS0_FAULTSTATUS_ADDR(base)            ((base) + (0x241C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_AS0_FAULTADDRESS_LO_UNION */
#define SOC_G3D_AS0_FAULTADDRESS_LO_ADDR(base)        ((base) + (0x2420))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_AS0_FAULTADDRESS_HI_UNION */
#define SOC_G3D_AS0_FAULTADDRESS_HI_ADDR(base)        ((base) + (0x2424))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_AS0_STATUS_UNION */
#define SOC_G3D_AS0_STATUS_ADDR(base)                 ((base) + (0x2428))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_AS1_TRANSTAB_LO_UNION */
#define SOC_G3D_AS1_TRANSTAB_LO_ADDR(base)            ((base) + (0x2440))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_AS1_TRANSTAB_HI_UNION */
#define SOC_G3D_AS1_TRANSTAB_HI_ADDR(base)            ((base) + (0x2444))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_AS1_MEMATTR_LO_UNION */
#define SOC_G3D_AS1_MEMATTR_LO_ADDR(base)             ((base) + (0x2448))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_AS1_MEMATTR_HI_UNION */
#define SOC_G3D_AS1_MEMATTR_HI_ADDR(base)             ((base) + (0x244C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_AS1_LOCKADDR_LO_UNION */
#define SOC_G3D_AS1_LOCKADDR_LO_ADDR(base)            ((base) + (0x2450))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_AS1_LOCKADDR_HI_UNION */
#define SOC_G3D_AS1_LOCKADDR_HI_ADDR(base)            ((base) + (0x2454))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_AS1_COMMAND_UNION */
#define SOC_G3D_AS1_COMMAND_ADDR(base)                ((base) + (0x2458))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_AS1_FAULTSTATUS_UNION */
#define SOC_G3D_AS1_FAULTSTATUS_ADDR(base)            ((base) + (0x245C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_AS1_FAULTADDRESS_LO_UNION */
#define SOC_G3D_AS1_FAULTADDRESS_LO_ADDR(base)        ((base) + (0x2460))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_AS1_FAULTADDRESS_HI_UNION */
#define SOC_G3D_AS1_FAULTADDRESS_HI_ADDR(base)        ((base) + (0x2464))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_AS1_STATUS_UNION */
#define SOC_G3D_AS1_STATUS_ADDR(base)                 ((base) + (0x2468))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_AS2_TRANSTAB_LO_UNION */
#define SOC_G3D_AS2_TRANSTAB_LO_ADDR(base)            ((base) + (0x2480))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_AS2_TRANSTAB_HI_UNION */
#define SOC_G3D_AS2_TRANSTAB_HI_ADDR(base)            ((base) + (0x2484))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_AS2_MEMATTR_LO_UNION */
#define SOC_G3D_AS2_MEMATTR_LO_ADDR(base)             ((base) + (0x2488))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_AS2_MEMATTR_HI_UNION */
#define SOC_G3D_AS2_MEMATTR_HI_ADDR(base)             ((base) + (0x248C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_AS2_LOCKADDR_LO_UNION */
#define SOC_G3D_AS2_LOCKADDR_LO_ADDR(base)            ((base) + (0x2490))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_AS2_LOCKADDR_HI_UNION */
#define SOC_G3D_AS2_LOCKADDR_HI_ADDR(base)            ((base) + (0x2494))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_AS2_COMMAND_UNION */
#define SOC_G3D_AS2_COMMAND_ADDR(base)                ((base) + (0x2498))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_AS2_FAULTSTATUS_UNION */
#define SOC_G3D_AS2_FAULTSTATUS_ADDR(base)            ((base) + (0x249C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_AS2_FAULTADDRESS_LO_UNION */
#define SOC_G3D_AS2_FAULTADDRESS_LO_ADDR(base)        ((base) + (0x24A0))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_AS2_FAULTADDRESS_HI_UNION */
#define SOC_G3D_AS2_FAULTADDRESS_HI_ADDR(base)        ((base) + (0x24A4))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_AS2_STATUS_UNION */
#define SOC_G3D_AS2_STATUS_ADDR(base)                 ((base) + (0x24A8))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_AS3_TRANSTAB_LO_UNION */
#define SOC_G3D_AS3_TRANSTAB_LO_ADDR(base)            ((base) + (0x24C0))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_AS3_TRANSTAB_HI_UNION */
#define SOC_G3D_AS3_TRANSTAB_HI_ADDR(base)            ((base) + (0x24C4))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_AS3_MEMATTR_LO_UNION */
#define SOC_G3D_AS3_MEMATTR_LO_ADDR(base)             ((base) + (0x24C8))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_AS3_MEMATTR_HI_UNION */
#define SOC_G3D_AS3_MEMATTR_HI_ADDR(base)             ((base) + (0x24CC))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_AS3_LOCKADDR_LO_UNION */
#define SOC_G3D_AS3_LOCKADDR_LO_ADDR(base)            ((base) + (0x24D0))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_AS3_LOCKADDR_HI_UNION */
#define SOC_G3D_AS3_LOCKADDR_HI_ADDR(base)            ((base) + (0x24D4))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_AS3_COMMAND_UNION */
#define SOC_G3D_AS3_COMMAND_ADDR(base)                ((base) + (0x24D8))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_AS3_FAULTSTATUS_UNION */
#define SOC_G3D_AS3_FAULTSTATUS_ADDR(base)            ((base) + (0x24DC))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_AS3_FAULTADDRESS_LO_UNION */
#define SOC_G3D_AS3_FAULTADDRESS_LO_ADDR(base)        ((base) + (0x24E0))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_AS3_FAULTADDRESS_HI_UNION */
#define SOC_G3D_AS3_FAULTADDRESS_HI_ADDR(base)        ((base) + (0x24E4))

/* 寄存器说明：
   位域定义UNION结构:  SOC_G3D_AS3_STATUS_UNION */
#define SOC_G3D_AS3_STATUS_ADDR(base)                 ((base) + (0x24E8))





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
 结构名    : SOC_G3D_GPU_ID_UNION
 结构说明  : GPU_ID 寄存器结构定义。地址偏移量:0x0000，初值:0x08800020，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  version_status : 4;  /* bit[0-3]  : release 版本的序列号，从0开始递增 */
        unsigned int  version_minor  : 8;  /* bit[4-11] : RxPx P版本. */
        unsigned int  version_major  : 4;  /* bit[12-15]: RxPx R版本 */
        unsigned int  product_id     : 16; /* bit[16-31]: The product ID. All other values are reserved. */
    } reg;
} SOC_G3D_GPU_ID_UNION;
#endif
#define SOC_G3D_GPU_ID_version_status_START  (0)
#define SOC_G3D_GPU_ID_version_status_END    (3)
#define SOC_G3D_GPU_ID_version_minor_START   (4)
#define SOC_G3D_GPU_ID_version_minor_END     (11)
#define SOC_G3D_GPU_ID_version_major_START   (12)
#define SOC_G3D_GPU_ID_version_major_END     (15)
#define SOC_G3D_GPU_ID_product_id_START      (16)
#define SOC_G3D_GPU_ID_product_id_END        (31)


/*****************************************************************************
 结构名    : SOC_G3D_L2_FEATURES_UNION
 结构说明  : L2_FEATURES 寄存器结构定义。地址偏移量:0x0004，初值:0x07130206，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  line_size          : 8;  /* bit[0-7]  : cache line:
                                                              64B */
        unsigned int  associativity      : 8;  /* bit[8-15] : assiciativity:
                                                              Level 2 cache associativity:
                                                              0x02 4 ways */
        unsigned int  cache_size         : 8;  /* bit[16-23]: l2 cache 大小
                                                              0x12:256KB
                                                              0x13:512KB */
        unsigned int  external_bus_width : 8;  /* bit[24-31]: AXI总线位宽
                                                              0x06:64bit
                                                              0x07;128bit */
    } reg;
} SOC_G3D_L2_FEATURES_UNION;
#endif
#define SOC_G3D_L2_FEATURES_line_size_START           (0)
#define SOC_G3D_L2_FEATURES_line_size_END             (7)
#define SOC_G3D_L2_FEATURES_associativity_START       (8)
#define SOC_G3D_L2_FEATURES_associativity_END         (15)
#define SOC_G3D_L2_FEATURES_cache_size_START          (16)
#define SOC_G3D_L2_FEATURES_cache_size_END            (23)
#define SOC_G3D_L2_FEATURES_external_bus_width_START  (24)
#define SOC_G3D_L2_FEATURES_external_bus_width_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_TILER_FEATURES_UNION
 结构说明  : TILER_FEATURES 寄存器结构定义。地址偏移量:0x000C，初值:0x00000809，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bin_size          : 6;  /* bit[0-5]  : bin_size:
                                                             0x09 - Log2 of the bin size, in bytes */
        unsigned int  reserved_0        : 2;  /* bit[6-7]  : reserved */
        unsigned int  max_active_levels : 4;  /* bit[8-11] : 0x08 - Maximum number of active hierarchy levels */
        unsigned int  reserved_1        : 20; /* bit[12-31]: Reserved, write as zero, read undefined. */
    } reg;
} SOC_G3D_TILER_FEATURES_UNION;
#endif
#define SOC_G3D_TILER_FEATURES_bin_size_START           (0)
#define SOC_G3D_TILER_FEATURES_bin_size_END             (5)
#define SOC_G3D_TILER_FEATURES_max_active_levels_START  (8)
#define SOC_G3D_TILER_FEATURES_max_active_levels_END    (11)


/*****************************************************************************
 结构名    : SOC_G3D_MEM_FEATURES_UNION
 结构说明  : MEM_FEATURES 寄存器结构定义。地址偏移量:0x0010，初值:0x00000001，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  COHERENT_CORE_GROUP : 1;  /* bit[0]    : 同一个core_group下的core共享memory
                                                               0：否
                                                               1：真 */
        unsigned int  COHERENT_SUPERGROUP : 1;  /* bit[1]    : set if the cores ina supergroup haver coherent memory with the other cores in that group */
        unsigned int  reserved_0          : 6;  /* bit[2-7]  : RSV */
        unsigned int  l2_slices           : 4;  /* bit[8-11] : L2 cache个数：
                                                               0:1个
                                                               1:2个 */
        unsigned int  reserved_1          : 20; /* bit[12-31]: Reserved, write as zero, read undefined */
    } reg;
} SOC_G3D_MEM_FEATURES_UNION;
#endif
#define SOC_G3D_MEM_FEATURES_COHERENT_CORE_GROUP_START  (0)
#define SOC_G3D_MEM_FEATURES_COHERENT_CORE_GROUP_END    (0)
#define SOC_G3D_MEM_FEATURES_COHERENT_SUPERGROUP_START  (1)
#define SOC_G3D_MEM_FEATURES_COHERENT_SUPERGROUP_END    (1)
#define SOC_G3D_MEM_FEATURES_l2_slices_START            (8)
#define SOC_G3D_MEM_FEATURES_l2_slices_END              (11)


/*****************************************************************************
 结构名    : SOC_G3D_MMU_FEATURES_UNION
 结构说明  : MMU_FEATURES 寄存器结构定义。地址偏移量:0x0014，初值:0x00002830，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  va_bits      : 8;  /* bit[0-7]  : 虚拟地址位宽48bit */
        unsigned int  pa_bits      : 8;  /* bit[8-15] : 真实地址位宽，40bit */
        unsigned int  mmu_features : 16; /* bit[16-31]: Reserved, write as zero, read undefined. */
    } reg;
} SOC_G3D_MMU_FEATURES_UNION;
#endif
#define SOC_G3D_MMU_FEATURES_va_bits_START       (0)
#define SOC_G3D_MMU_FEATURES_va_bits_END         (7)
#define SOC_G3D_MMU_FEATURES_pa_bits_START       (8)
#define SOC_G3D_MMU_FEATURES_pa_bits_END         (15)
#define SOC_G3D_MMU_FEATURES_mmu_features_START  (16)
#define SOC_G3D_MMU_FEATURES_mmu_features_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_AS_PRESENT_UNION
 结构说明  : AS_PRESENT 寄存器结构定义。地址偏移量:0x0018，初值:0x000000FF，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  as_present_low : 8;  /* bit[0-7] : 地址空间AS0~AS7S使能。 */
        unsigned int  as_present     : 24; /* bit[8-31]: Reserved, write as zero, read undefined. */
    } reg;
} SOC_G3D_AS_PRESENT_UNION;
#endif
#define SOC_G3D_AS_PRESENT_as_present_low_START  (0)
#define SOC_G3D_AS_PRESENT_as_present_low_END    (7)
#define SOC_G3D_AS_PRESENT_as_present_START      (8)
#define SOC_G3D_AS_PRESENT_as_present_END        (31)


/*****************************************************************************
 结构名    : SOC_G3D_JS_PRESENT_UNION
 结构说明  : JS_PRESENT 寄存器结构定义。地址偏移量:0x001C，初值:0x00000007，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  js_present_low : 4;  /* bit[0-3] : JS0~JS2使能。 */
        unsigned int  js_present     : 28; /* bit[4-31]: Reserved, write as zero, read undefined */
    } reg;
} SOC_G3D_JS_PRESENT_UNION;
#endif
#define SOC_G3D_JS_PRESENT_js_present_low_START  (0)
#define SOC_G3D_JS_PRESENT_js_present_low_END    (3)
#define SOC_G3D_JS_PRESENT_js_present_START      (4)
#define SOC_G3D_JS_PRESENT_js_present_END        (31)


/*****************************************************************************
 结构名    : SOC_G3D_GPU_IRQ_RAWSTAT_UNION
 结构说明  : GPU_IRQ_RAWSTAT 寄存器结构定义。地址偏移量:0x0020，初值:0x00000100，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gpu_fault              : 1;  /* bit[0-0]  : GPU失效中断。在GPU_FAULTADDRESS寄存器描述失效类型 */
        unsigned int  reserved_0             : 6;  /* bit[1-6]  : RSV */
        unsigned int  multi_gpu_fault        : 1;  /* bit[7]    : RSV */
        unsigned int  reset_completed        : 1;  /* bit[8]    : 复位完成 */
        unsigned int  power_change_single    : 1;  /* bit[9]    : 至少一个core完成上下电，置1 */
        unsigned int  power_change_all       : 1;  /* bit[10]   : 所有core完成上下电，置1 */
        unsigned int  reserved_1             : 5;  /* bit[11-15]: RSV */
        unsigned int  prfcnt_sample_complete : 1;  /* bit[16]   : 完成一次performance cout sample，置1 */
        unsigned int  clean_cache_completed  : 1;  /* bit[17]   : 完成clear cache操作，置1 */
        unsigned int  reserved_2             : 14; /* bit[18-31]: Reserved, write as zero, read undefined. */
    } reg;
} SOC_G3D_GPU_IRQ_RAWSTAT_UNION;
#endif
#define SOC_G3D_GPU_IRQ_RAWSTAT_gpu_fault_START               (0)
#define SOC_G3D_GPU_IRQ_RAWSTAT_gpu_fault_END                 (0)
#define SOC_G3D_GPU_IRQ_RAWSTAT_multi_gpu_fault_START         (7)
#define SOC_G3D_GPU_IRQ_RAWSTAT_multi_gpu_fault_END           (7)
#define SOC_G3D_GPU_IRQ_RAWSTAT_reset_completed_START         (8)
#define SOC_G3D_GPU_IRQ_RAWSTAT_reset_completed_END           (8)
#define SOC_G3D_GPU_IRQ_RAWSTAT_power_change_single_START     (9)
#define SOC_G3D_GPU_IRQ_RAWSTAT_power_change_single_END       (9)
#define SOC_G3D_GPU_IRQ_RAWSTAT_power_change_all_START        (10)
#define SOC_G3D_GPU_IRQ_RAWSTAT_power_change_all_END          (10)
#define SOC_G3D_GPU_IRQ_RAWSTAT_prfcnt_sample_complete_START  (16)
#define SOC_G3D_GPU_IRQ_RAWSTAT_prfcnt_sample_complete_END    (16)
#define SOC_G3D_GPU_IRQ_RAWSTAT_clean_cache_completed_START   (17)
#define SOC_G3D_GPU_IRQ_RAWSTAT_clean_cache_completed_END     (17)


/*****************************************************************************
 结构名    : SOC_G3D_GPU_IRQ_CLEAR_UNION
 结构说明  : GPU_IRQ_CLEAR 寄存器结构定义。地址偏移量:0x0024，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gpu_fault              : 1;  /* bit[0-0]  : 对应中断清除 */
        unsigned int  reserved_0             : 6;  /* bit[1-6]  : 对应中断清除 */
        unsigned int  multi_gpu_fault        : 1;  /* bit[7]    : 对应中断清除 */
        unsigned int  reset_completed        : 1;  /* bit[8]    : 对应中断清除 */
        unsigned int  power_change_single    : 1;  /* bit[9]    : 对应中断清除 */
        unsigned int  power_change_all       : 1;  /* bit[10]   : 对应中断清除 */
        unsigned int  reserved_1             : 5;  /* bit[11-15]: 对应中断清除 */
        unsigned int  prfcnt_sample_complete : 1;  /* bit[16]   : 对应中断清除 */
        unsigned int  clean_cache_completed  : 1;  /* bit[17]   : 对应中断清除，写1清除 */
        unsigned int  reserved_2             : 14; /* bit[18-31]: Job management clear Interrupts register */
    } reg;
} SOC_G3D_GPU_IRQ_CLEAR_UNION;
#endif
#define SOC_G3D_GPU_IRQ_CLEAR_gpu_fault_START               (0)
#define SOC_G3D_GPU_IRQ_CLEAR_gpu_fault_END                 (0)
#define SOC_G3D_GPU_IRQ_CLEAR_multi_gpu_fault_START         (7)
#define SOC_G3D_GPU_IRQ_CLEAR_multi_gpu_fault_END           (7)
#define SOC_G3D_GPU_IRQ_CLEAR_reset_completed_START         (8)
#define SOC_G3D_GPU_IRQ_CLEAR_reset_completed_END           (8)
#define SOC_G3D_GPU_IRQ_CLEAR_power_change_single_START     (9)
#define SOC_G3D_GPU_IRQ_CLEAR_power_change_single_END       (9)
#define SOC_G3D_GPU_IRQ_CLEAR_power_change_all_START        (10)
#define SOC_G3D_GPU_IRQ_CLEAR_power_change_all_END          (10)
#define SOC_G3D_GPU_IRQ_CLEAR_prfcnt_sample_complete_START  (16)
#define SOC_G3D_GPU_IRQ_CLEAR_prfcnt_sample_complete_END    (16)
#define SOC_G3D_GPU_IRQ_CLEAR_clean_cache_completed_START   (17)
#define SOC_G3D_GPU_IRQ_CLEAR_clean_cache_completed_END     (17)


/*****************************************************************************
 结构名    : SOC_G3D_GPU_IRQ_MASK_UNION
 结构说明  : GPU_IRQ_MASK 寄存器结构定义。地址偏移量:0x0028，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gpu_fault              : 1;  /* bit[0-0]  : 对应中断掩码 */
        unsigned int  reserved_0             : 6;  /* bit[1-6]  : 对应中断掩码 */
        unsigned int  multi_gpu_fault        : 1;  /* bit[7]    : 对应中断掩码 */
        unsigned int  reset_completed        : 1;  /* bit[8]    : 对应中断掩码 */
        unsigned int  power_change_single    : 1;  /* bit[9]    : 对应中断掩码 */
        unsigned int  power_change_all       : 1;  /* bit[10]   : 对应中断掩码 */
        unsigned int  reserved_1             : 5;  /* bit[11-15]: 对应中断掩码 */
        unsigned int  prfcnt_sample_complete : 1;  /* bit[16]   : 对应中断掩码 */
        unsigned int  clean_cache_completed  : 1;  /* bit[17]   : 对应中断掩码，写1允许对应中断 */
        unsigned int  reserved_2             : 14; /* bit[18-31]: Job management enable Interrupts register */
    } reg;
} SOC_G3D_GPU_IRQ_MASK_UNION;
#endif
#define SOC_G3D_GPU_IRQ_MASK_gpu_fault_START               (0)
#define SOC_G3D_GPU_IRQ_MASK_gpu_fault_END                 (0)
#define SOC_G3D_GPU_IRQ_MASK_multi_gpu_fault_START         (7)
#define SOC_G3D_GPU_IRQ_MASK_multi_gpu_fault_END           (7)
#define SOC_G3D_GPU_IRQ_MASK_reset_completed_START         (8)
#define SOC_G3D_GPU_IRQ_MASK_reset_completed_END           (8)
#define SOC_G3D_GPU_IRQ_MASK_power_change_single_START     (9)
#define SOC_G3D_GPU_IRQ_MASK_power_change_single_END       (9)
#define SOC_G3D_GPU_IRQ_MASK_power_change_all_START        (10)
#define SOC_G3D_GPU_IRQ_MASK_power_change_all_END          (10)
#define SOC_G3D_GPU_IRQ_MASK_prfcnt_sample_complete_START  (16)
#define SOC_G3D_GPU_IRQ_MASK_prfcnt_sample_complete_END    (16)
#define SOC_G3D_GPU_IRQ_MASK_clean_cache_completed_START   (17)
#define SOC_G3D_GPU_IRQ_MASK_clean_cache_completed_END     (17)


/*****************************************************************************
 结构名    : SOC_G3D_GPU_IRQ_STATUS_UNION
 结构说明  : GPU_IRQ_STATUS 寄存器结构定义。地址偏移量:0x002C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gpu_fault              : 1;  /* bit[0-0]  : 对应中断和掩码与逻辑后的值 */
        unsigned int  reserved_0             : 6;  /* bit[1-6]  : 对应中断和掩码与逻辑后的值 */
        unsigned int  multi_gpu_fault        : 1;  /* bit[7]    : 对应中断和掩码与逻辑后的值 */
        unsigned int  reset_completed        : 1;  /* bit[8]    : 对应中断和掩码与逻辑后的值 */
        unsigned int  power_change_single    : 1;  /* bit[9]    : 对应中断和掩码与逻辑后的值 */
        unsigned int  power_change_all       : 1;  /* bit[10]   : 对应中断和掩码与逻辑后的值 */
        unsigned int  reserved_1             : 5;  /* bit[11-15]: 对应中断和掩码与逻辑后的值 */
        unsigned int  prfcnt_sample_complete : 1;  /* bit[16]   : 对应中断和掩码与逻辑后的值 */
        unsigned int  clean_cache_completed  : 1;  /* bit[17]   : 对应中断和掩码与逻辑后的值 */
        unsigned int  reserved_2             : 14; /* bit[18-31]: Job management interrupt status register */
    } reg;
} SOC_G3D_GPU_IRQ_STATUS_UNION;
#endif
#define SOC_G3D_GPU_IRQ_STATUS_gpu_fault_START               (0)
#define SOC_G3D_GPU_IRQ_STATUS_gpu_fault_END                 (0)
#define SOC_G3D_GPU_IRQ_STATUS_multi_gpu_fault_START         (7)
#define SOC_G3D_GPU_IRQ_STATUS_multi_gpu_fault_END           (7)
#define SOC_G3D_GPU_IRQ_STATUS_reset_completed_START         (8)
#define SOC_G3D_GPU_IRQ_STATUS_reset_completed_END           (8)
#define SOC_G3D_GPU_IRQ_STATUS_power_change_single_START     (9)
#define SOC_G3D_GPU_IRQ_STATUS_power_change_single_END       (9)
#define SOC_G3D_GPU_IRQ_STATUS_power_change_all_START        (10)
#define SOC_G3D_GPU_IRQ_STATUS_power_change_all_END          (10)
#define SOC_G3D_GPU_IRQ_STATUS_prfcnt_sample_complete_START  (16)
#define SOC_G3D_GPU_IRQ_STATUS_prfcnt_sample_complete_END    (16)
#define SOC_G3D_GPU_IRQ_STATUS_clean_cache_completed_START   (17)
#define SOC_G3D_GPU_IRQ_STATUS_clean_cache_completed_END     (17)


/*****************************************************************************
 结构名    : SOC_G3D_GPU_COMMAND_UNION
 结构说明  : GPU_COMMAND 寄存器结构定义。地址偏移量:0x0030，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved          : 1;  /* bit[0]   : Reserved, write as zero, read undefined. */
        unsigned int  soft_reset        : 1;  /* bit[1]   : 软复位 */
        unsigned int  hard_reset        : 1;  /* bit[2]   : 硬复位 */
        unsigned int  prfcnt_clear      : 1;  /* bit[3]   : pfrcnt归0 */
        unsigned int  prfcnt_sample     : 1;  /* bit[4]   : 采样pfrcnt写入memory，并清除 */
        unsigned int  cycle_count_start : 1;  /* bit[5]   : pfrcnt开始计数 */
        unsigned int  cycle_count_stop  : 1;  /* bit[6]   : pfrcnt停止计数 */
        unsigned int  clean_caches      : 1;  /* bit[7]   : 清cache */
        unsigned int  clean_inv_caches  : 1;  /* bit[8]   : Cleans and invalidates all caches */
        unsigned int  gpu_command       : 23; /* bit[9-31]: Reserved, write as zero, read undefined. */
    } reg;
} SOC_G3D_GPU_COMMAND_UNION;
#endif
#define SOC_G3D_GPU_COMMAND_soft_reset_START         (1)
#define SOC_G3D_GPU_COMMAND_soft_reset_END           (1)
#define SOC_G3D_GPU_COMMAND_hard_reset_START         (2)
#define SOC_G3D_GPU_COMMAND_hard_reset_END           (2)
#define SOC_G3D_GPU_COMMAND_prfcnt_clear_START       (3)
#define SOC_G3D_GPU_COMMAND_prfcnt_clear_END         (3)
#define SOC_G3D_GPU_COMMAND_prfcnt_sample_START      (4)
#define SOC_G3D_GPU_COMMAND_prfcnt_sample_END        (4)
#define SOC_G3D_GPU_COMMAND_cycle_count_start_START  (5)
#define SOC_G3D_GPU_COMMAND_cycle_count_start_END    (5)
#define SOC_G3D_GPU_COMMAND_cycle_count_stop_START   (6)
#define SOC_G3D_GPU_COMMAND_cycle_count_stop_END     (6)
#define SOC_G3D_GPU_COMMAND_clean_caches_START       (7)
#define SOC_G3D_GPU_COMMAND_clean_caches_END         (7)
#define SOC_G3D_GPU_COMMAND_clean_inv_caches_START   (8)
#define SOC_G3D_GPU_COMMAND_clean_inv_caches_END     (8)
#define SOC_G3D_GPU_COMMAND_gpu_command_START        (9)
#define SOC_G3D_GPU_COMMAND_gpu_command_END          (31)


/*****************************************************************************
 结构名    : SOC_G3D_GPU_STATUS_UNION
 结构说明  : GPU_STATUS 寄存器结构定义。地址偏移量:0x0034，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gpu_active         : 1;  /* bit[0]   : The GPU, or part of the GPU, is active */
        unsigned int  pwr_active         : 1;  /* bit[1]   : The power controller is active, changing an area of the
                                                             power state of the GPU. */
        unsigned int  prfcnt_active      : 1;  /* bit[2]   : The performance counters are active, writing counter
                                                             values to memory */
        unsigned int  job_active         : 1;  /* bit[3]   : The job slots are active */
        unsigned int  page_fault         : 1;  /* bit[4]   : The page faults are active */
        unsigned int  irq_active         : 1;  /* bit[5]   : The interrupt signals are active */
        unsigned int  cycle_count_active : 1;  /* bit[6]   : The cycle counter is active */
        unsigned int  gpu_status         : 25; /* bit[7-31]: Reserved, write as zero, read undefined */
    } reg;
} SOC_G3D_GPU_STATUS_UNION;
#endif
#define SOC_G3D_GPU_STATUS_gpu_active_START          (0)
#define SOC_G3D_GPU_STATUS_gpu_active_END            (0)
#define SOC_G3D_GPU_STATUS_pwr_active_START          (1)
#define SOC_G3D_GPU_STATUS_pwr_active_END            (1)
#define SOC_G3D_GPU_STATUS_prfcnt_active_START       (2)
#define SOC_G3D_GPU_STATUS_prfcnt_active_END         (2)
#define SOC_G3D_GPU_STATUS_job_active_START          (3)
#define SOC_G3D_GPU_STATUS_job_active_END            (3)
#define SOC_G3D_GPU_STATUS_page_fault_START          (4)
#define SOC_G3D_GPU_STATUS_page_fault_END            (4)
#define SOC_G3D_GPU_STATUS_irq_active_START          (5)
#define SOC_G3D_GPU_STATUS_irq_active_END            (5)
#define SOC_G3D_GPU_STATUS_cycle_count_active_START  (6)
#define SOC_G3D_GPU_STATUS_cycle_count_active_END    (6)
#define SOC_G3D_GPU_STATUS_gpu_status_START          (7)
#define SOC_G3D_GPU_STATUS_gpu_status_END            (31)


/*****************************************************************************
 结构名    : SOC_G3D_GPU_FAULTSTATUS_UNION
 结构说明  : GPU_FAULTSTATUS 寄存器结构定义。地址偏移量:0x003C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  exception_type  : 8;  /* bit[0-7]  : 错误中断类型 */
        unsigned int  access_type     : 2;  /* bit[8-9]  : Access type that triggered the fault */
        unsigned int  gpu_faultstatus : 22; /* bit[10-31]: Reserved, write as zero, read undefined. */
    } reg;
} SOC_G3D_GPU_FAULTSTATUS_UNION;
#endif
#define SOC_G3D_GPU_FAULTSTATUS_exception_type_START   (0)
#define SOC_G3D_GPU_FAULTSTATUS_exception_type_END     (7)
#define SOC_G3D_GPU_FAULTSTATUS_access_type_START      (8)
#define SOC_G3D_GPU_FAULTSTATUS_access_type_END        (9)
#define SOC_G3D_GPU_FAULTSTATUS_gpu_faultstatus_START  (10)
#define SOC_G3D_GPU_FAULTSTATUS_gpu_faultstatus_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_GPU_FAULTADDRESS_LO_UNION
 结构说明  : GPU_FAULTADDRESS_LO 寄存器结构定义。地址偏移量:0x0040，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gpu_faultaddress_lo : 32; /* bit[0-31]: GPU exception fault address register  */
    } reg;
} SOC_G3D_GPU_FAULTADDRESS_LO_UNION;
#endif
#define SOC_G3D_GPU_FAULTADDRESS_LO_gpu_faultaddress_lo_START  (0)
#define SOC_G3D_GPU_FAULTADDRESS_LO_gpu_faultaddress_lo_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_GPU_FAULTADDRESS_HI_UNION
 结构说明  : GPU_FAULTADDRESS_HI 寄存器结构定义。地址偏移量:0x0044，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gpu_faultaddress_hi : 32; /* bit[0-31]: GPU exception fault address register */
    } reg;
} SOC_G3D_GPU_FAULTADDRESS_HI_UNION;
#endif
#define SOC_G3D_GPU_FAULTADDRESS_HI_gpu_faultaddress_hi_START  (0)
#define SOC_G3D_GPU_FAULTADDRESS_HI_gpu_faultaddress_hi_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_PWR_KEY_UNION
 结构说明  : PWR_KEY 寄存器结构定义。地址偏移量:0x0050，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pwr_key : 32; /* bit[0-31]: 写0x54,0x58寄存器之前必须配置该寄存器， The key value is
                                                  0x2968A819. */
    } reg;
} SOC_G3D_PWR_KEY_UNION;
#endif
#define SOC_G3D_PWR_KEY_pwr_key_START  (0)
#define SOC_G3D_PWR_KEY_pwr_key_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_PWR_KEYOVERRIDE0_UNION
 结构说明  : PWR_KEYOVERRIDE0 寄存器结构定义。地址偏移量:0x0054，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pwrup_override       : 2;  /* bit[0-1]  : Specifies overrides of the power domain PWRUP signal */
        unsigned int  isolate_override     : 2;  /* bit[2-3]  : Specifies overrides of the power domain ISOLATE signal */
        unsigned int  reset_override       : 2;  /* bit[4-5]  : Specifies overrides of the power domain RESET signal */
        unsigned int  clken_override       : 2;  /* bit[6-7]  : Specifies overrides of the power domain CLKEN signal */
        unsigned int  ack_override         : 2;  /* bit[8-9]  : Specifies overrides of the power domain PWRUP_ACK
                                                                signal */
        unsigned int  isolate_ack_override : 2;  /* bit[10-11]: Specifies overrides of the power domain ISOLATE_ACK
                                                                signal */
        unsigned int  reserved_0           : 4;  /* bit[12-15]: Reserved, write as zero, read undefined */
        unsigned int  powertrain_limt      : 6;  /* bit[16-21]: Maximum number of active power transactions at any time,
                                                                minus one.
                                                                The POWERTRANS_LIMIT field default of 0 enables a
                                                                single power domain to transition at a time. Setting this to a
                                                                higher value can speed up power transition, but also requires
                                                                that the device can handle the larger power requirements. */
        unsigned int  reserved_1           : 10; /* bit[22-31]: Reserved, write as zero, read undefined */
    } reg;
} SOC_G3D_PWR_KEYOVERRIDE0_UNION;
#endif
#define SOC_G3D_PWR_KEYOVERRIDE0_pwrup_override_START        (0)
#define SOC_G3D_PWR_KEYOVERRIDE0_pwrup_override_END          (1)
#define SOC_G3D_PWR_KEYOVERRIDE0_isolate_override_START      (2)
#define SOC_G3D_PWR_KEYOVERRIDE0_isolate_override_END        (3)
#define SOC_G3D_PWR_KEYOVERRIDE0_reset_override_START        (4)
#define SOC_G3D_PWR_KEYOVERRIDE0_reset_override_END          (5)
#define SOC_G3D_PWR_KEYOVERRIDE0_clken_override_START        (6)
#define SOC_G3D_PWR_KEYOVERRIDE0_clken_override_END          (7)
#define SOC_G3D_PWR_KEYOVERRIDE0_ack_override_START          (8)
#define SOC_G3D_PWR_KEYOVERRIDE0_ack_override_END            (9)
#define SOC_G3D_PWR_KEYOVERRIDE0_isolate_ack_override_START  (10)
#define SOC_G3D_PWR_KEYOVERRIDE0_isolate_ack_override_END    (11)
#define SOC_G3D_PWR_KEYOVERRIDE0_powertrain_limt_START       (16)
#define SOC_G3D_PWR_KEYOVERRIDE0_powertrain_limt_END         (21)


/*****************************************************************************
 结构名    : SOC_G3D_PWR_KEYOVERRIDE1_UNION
 结构说明  : PWR_KEYOVERRIDE1 寄存器结构定义。地址偏移量:0x0058，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: mtcmos上下电cnt计数配置
                                                   31：下电计数配置使能
                                                   30：上电计数配置使能
                                                   29:15;下电计数值
                                                   14:0：上电计数值 */
    } reg;
} SOC_G3D_PWR_KEYOVERRIDE1_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_G3D_PRFCNT_BASE_LO_UNION
 结构说明  : PRFCNT_BASE_LO 寄存器结构定义。地址偏移量:0x0060，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved       : 8;  /* bit[0-7] : Reserved, write as zero, read undefined. */
        unsigned int  prfcnt_base_lo : 24; /* bit[8-31]: The start address of the memory region where the
                                                         performance counter values can be written. The start
                                                         address is a virtual address in the address space
                                                         specified by the ADDRESS_SPACE field in the
                                                         PRCFNT_CONFIG register */
    } reg;
} SOC_G3D_PRFCNT_BASE_LO_UNION;
#endif
#define SOC_G3D_PRFCNT_BASE_LO_prfcnt_base_lo_START  (8)
#define SOC_G3D_PRFCNT_BASE_LO_prfcnt_base_lo_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_PRFCNT_BASE_HI_UNION
 结构说明  : PRFCNT_BASE_HI 寄存器结构定义。地址偏移量:0x0064，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  prfcnt_base_hi : 16; /* bit[0-15] : The start address of the memory region where the
                                                          performance counter values can be written. The start
                                                          address is a virtual address in the address space
                                                          specified by the ADDRESS_SPACE field in the
                                                          PRCFNT_CONFIG register */
        unsigned int  reserved       : 16; /* bit[16-31]: Reserved, write as zero, read undefined. */
    } reg;
} SOC_G3D_PRFCNT_BASE_HI_UNION;
#endif
#define SOC_G3D_PRFCNT_BASE_HI_prfcnt_base_hi_START  (0)
#define SOC_G3D_PRFCNT_BASE_HI_prfcnt_base_hi_END    (15)


/*****************************************************************************
 结构名    : SOC_G3D_PRFCNT_CONFIG_UNION
 结构说明  : PRFCNT_CONFIG 寄存器结构定义。地址偏移量:0x0068，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode          : 2;  /* bit[0-1] : Performance counter mode:
                                                        0 Off. The performance counters are disabled.
                                                        1 Manual. The performance counters are enabled.
                                                        2 to15 Reserved
                                                        To change mode, first change to mode OFF, then wait until the
                                                        PRFCNT_ACTIVE bit in the GPU_STATUS register is low, then
                                                        set the new mode. */
        unsigned int  address_space : 2;  /* bit[2-3] : The index of the address space to which the counters are written. */
        unsigned int  reserved      : 28; /* bit[4-31]: Reserved, write as zero, read undefined */
    } reg;
} SOC_G3D_PRFCNT_CONFIG_UNION;
#endif
#define SOC_G3D_PRFCNT_CONFIG_mode_START           (0)
#define SOC_G3D_PRFCNT_CONFIG_mode_END             (1)
#define SOC_G3D_PRFCNT_CONFIG_address_space_START  (2)
#define SOC_G3D_PRFCNT_CONFIG_address_space_END    (3)


/*****************************************************************************
 结构名    : SOC_G3D_PRFCNT_JM_EN_UNION
 结构说明  : PRFCNT_JM_EN 寄存器结构定义。地址偏移量:0x006C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pfrcnt_jm_en : 32; /* bit[0-31]: Enables the performance counter. */
    } reg;
} SOC_G3D_PRFCNT_JM_EN_UNION;
#endif
#define SOC_G3D_PRFCNT_JM_EN_pfrcnt_jm_en_START  (0)
#define SOC_G3D_PRFCNT_JM_EN_pfrcnt_jm_en_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_PRFCNT_SHADER_EN_UNION
 结构说明  : PRFCNT_SHADER_EN 寄存器结构定义。地址偏移量:0x0070，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pfrcnt_shader_en : 32; /* bit[0-31]: Enables a subset of the performance counter to be written out to memory */
    } reg;
} SOC_G3D_PRFCNT_SHADER_EN_UNION;
#endif
#define SOC_G3D_PRFCNT_SHADER_EN_pfrcnt_shader_en_START  (0)
#define SOC_G3D_PRFCNT_SHADER_EN_pfrcnt_shader_en_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_PRFCNT_TILER_EN_UNION
 结构说明  : PRFCNT_TILER_EN 寄存器结构定义。地址偏移量:0x0074，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pfrcnt_tiler_en : 32; /* bit[0-31]: Enables a subset of the performance counter to be written out to memory */
    } reg;
} SOC_G3D_PRFCNT_TILER_EN_UNION;
#endif
#define SOC_G3D_PRFCNT_TILER_EN_pfrcnt_tiler_en_START  (0)
#define SOC_G3D_PRFCNT_TILER_EN_pfrcnt_tiler_en_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_PRFCNT_MMU_L2_EN_UNION
 结构说明  : PRFCNT_MMU_L2_EN 寄存器结构定义。地址偏移量:0x007C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pfrcnt_mmu_en : 32; /* bit[0-31]: Enables a subset of the performance counter to be written out to memory */
    } reg;
} SOC_G3D_PRFCNT_MMU_L2_EN_UNION;
#endif
#define SOC_G3D_PRFCNT_MMU_L2_EN_pfrcnt_mmu_en_START  (0)
#define SOC_G3D_PRFCNT_MMU_L2_EN_pfrcnt_mmu_en_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_CYCLE_COUNT_LO_UNION
 结构说明  : CYCLE_COUNT_LO 寄存器结构定义。地址偏移量:0x0090，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cycle_count_lo : 32; /* bit[0-31]: Cycle counter register  */
    } reg;
} SOC_G3D_CYCLE_COUNT_LO_UNION;
#endif
#define SOC_G3D_CYCLE_COUNT_LO_cycle_count_lo_START  (0)
#define SOC_G3D_CYCLE_COUNT_LO_cycle_count_lo_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_CYCLE_COUNT_HI_UNION
 结构说明  : CYCLE_COUNT_HI 寄存器结构定义。地址偏移量:0x0094，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cycle_count_hi : 32; /* bit[0-31]: Cycle counter register  */
    } reg;
} SOC_G3D_CYCLE_COUNT_HI_UNION;
#endif
#define SOC_G3D_CYCLE_COUNT_HI_cycle_count_hi_START  (0)
#define SOC_G3D_CYCLE_COUNT_HI_cycle_count_hi_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_TIMESTAMP_LO_UNION
 结构说明  : TIMESTAMP_LO 寄存器结构定义。地址偏移量:0x0098，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  timestamp_lo : 32; /* bit[0-31]: Timestamp register :64-bit value of the global timestamp. The value is the current
                                                       broadcast value of the system time counter. */
    } reg;
} SOC_G3D_TIMESTAMP_LO_UNION;
#endif
#define SOC_G3D_TIMESTAMP_LO_timestamp_lo_START  (0)
#define SOC_G3D_TIMESTAMP_LO_timestamp_lo_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_TIMESTAMP_HI_UNION
 结构说明  : TIMESTAMP_HI 寄存器结构定义。地址偏移量:0x009C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  timestamp_hi : 32; /* bit[0-31]: Timestamp register :64-bit value of the global timestamp. The value is the current
                                                       broadcast value of the system time counter. */
    } reg;
} SOC_G3D_TIMESTAMP_HI_UNION;
#endif
#define SOC_G3D_TIMESTAMP_HI_timestamp_hi_START  (0)
#define SOC_G3D_TIMESTAMP_HI_timestamp_hi_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_THREAD_MAX_THREADS_UNION
 结构说明  : THREAD_MAX_THREADS 寄存器结构定义。地址偏移量:0x00A0，初值:0x00000100，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  thread_max_thread : 32; /* bit[0-31]: 单个shader core最大线程个数 */
    } reg;
} SOC_G3D_THREAD_MAX_THREADS_UNION;
#endif
#define SOC_G3D_THREAD_MAX_THREADS_thread_max_thread_START  (0)
#define SOC_G3D_THREAD_MAX_THREADS_thread_max_thread_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_THREAD_MAX_WORKGROUP_UNION
 结构说明  : THREAD_MAX_WORKGROUP 寄存器结构定义。地址偏移量:0x00A4，初值:0x00000100，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  thread_max_workgroup : 32; /* bit[0-31]: workgroup最大线程个数 */
    } reg;
} SOC_G3D_THREAD_MAX_WORKGROUP_UNION;
#endif
#define SOC_G3D_THREAD_MAX_WORKGROUP_thread_max_workgroup_START  (0)
#define SOC_G3D_THREAD_MAX_WORKGROUP_thread_max_workgroup_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_THREAD_MAX_BARRIER_SIZE_UNION
 结构说明  : THREAD_MAX_BARRIER_SIZE 寄存器结构定义。地址偏移量:0x00A8，初值:0x00000100，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  thread_max_barrier_size : 32; /* bit[0-31]: 在硬件barrier时的等待个数最大线程个数 */
    } reg;
} SOC_G3D_THREAD_MAX_BARRIER_SIZE_UNION;
#endif
#define SOC_G3D_THREAD_MAX_BARRIER_SIZE_thread_max_barrier_size_START  (0)
#define SOC_G3D_THREAD_MAX_BARRIER_SIZE_thread_max_barrier_size_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_THREAD_FEATURES_UNION
 结构说明  : THREAD_FEATURES 寄存器结构定义。地址偏移量:0x00AC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  max_registers          : 16; /* bit[0-15] : Maximum size fo register file available for each core. A register is 128bit wide. */
        unsigned int  max_task_queue         : 8;  /* bit[16-23]: Maximum number of tasks that can be sent to a core before it becomes blocked.Thsi value is an 8-bit unsigned integer */
        unsigned int  max_thread_group_split : 6;  /* bit[24-29]: maximum allowed thread group split value field in a job descriptor.This value is a 6-bit unsigned integer. */
        unsigned int  reserved               : 2;  /* bit[30-31]: Reserved, write as zero, read undefined */
    } reg;
} SOC_G3D_THREAD_FEATURES_UNION;
#endif
#define SOC_G3D_THREAD_FEATURES_max_registers_START           (0)
#define SOC_G3D_THREAD_FEATURES_max_registers_END             (15)
#define SOC_G3D_THREAD_FEATURES_max_task_queue_START          (16)
#define SOC_G3D_THREAD_FEATURES_max_task_queue_END            (23)
#define SOC_G3D_THREAD_FEATURES_max_thread_group_split_START  (24)
#define SOC_G3D_THREAD_FEATURES_max_thread_group_split_END    (29)


/*****************************************************************************
 结构名    : SOC_G3D_TEXTURE_FEATURES_0_UNION
 结构说明  : TEXTURE_FEATURES_0 寄存器结构定义。地址偏移量:0x00B0，初值:0x01FFFFDF，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  texture_features_0 : 32; /* bit[0-31]: 纹理压缩全支持 */
    } reg;
} SOC_G3D_TEXTURE_FEATURES_0_UNION;
#endif
#define SOC_G3D_TEXTURE_FEATURES_0_texture_features_0_START  (0)
#define SOC_G3D_TEXTURE_FEATURES_0_texture_features_0_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_TEXTURE_FEATURES_1_UNION
 结构说明  : TEXTURE_FEATURES_1 寄存器结构定义。地址偏移量:0x00B4，初值:0x0000FFFF，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  texture_features_1 : 32; /* bit[0-31]: RSV */
    } reg;
} SOC_G3D_TEXTURE_FEATURES_1_UNION;
#endif
#define SOC_G3D_TEXTURE_FEATURES_1_texture_features_1_START  (0)
#define SOC_G3D_TEXTURE_FEATURES_1_texture_features_1_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_TEXTURE_FEATURES_2_UNION
 结构说明  : TEXTURE_FEATURES_2 寄存器结构定义。地址偏移量:0x00B8，初值:0x9F81FFFF，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  texture_features_2 : 32; /* bit[0-31]: RSV */
    } reg;
} SOC_G3D_TEXTURE_FEATURES_2_UNION;
#endif
#define SOC_G3D_TEXTURE_FEATURES_2_texture_features_2_START  (0)
#define SOC_G3D_TEXTURE_FEATURES_2_texture_features_2_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_JS0_FEATURES_UNION
 结构说明  : JS0_FEATURES 寄存器结构定义。地址偏移量:0x00C0，初值:0x0000020E，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  js0_features : 32; /* bit[0-31]: JS0_FEATURES registers  */
    } reg;
} SOC_G3D_JS0_FEATURES_UNION;
#endif
#define SOC_G3D_JS0_FEATURES_js0_features_START  (0)
#define SOC_G3D_JS0_FEATURES_js0_features_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_JS1_FEATURES_UNION
 结构说明  : JS1_FEATURES 寄存器结构定义。地址偏移量:0x00C4，初值:0x000001FE，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  js1_features : 32; /* bit[0-31]: JS1_FEATURES registers */
    } reg;
} SOC_G3D_JS1_FEATURES_UNION;
#endif
#define SOC_G3D_JS1_FEATURES_js1_features_START  (0)
#define SOC_G3D_JS1_FEATURES_js1_features_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_JS2_FEATURES_UNION
 结构说明  : JS2_FEATURES 寄存器结构定义。地址偏移量:0x00C8，初值:0x0000007E，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  js2_features : 32; /* bit[0-31]: JS2_FEATURES registers */
    } reg;
} SOC_G3D_JS2_FEATURES_UNION;
#endif
#define SOC_G3D_JS2_FEATURES_js2_features_START  (0)
#define SOC_G3D_JS2_FEATURES_js2_features_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_SHADER_PRESENT_LO_UNION
 结构说明  : SHADER_PRESENT_LO 寄存器结构定义。地址偏移量:0x0100，初值:0x0000000F，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  shader_present_lo : 32; /* bit[0-31]: shader core 个数 */
    } reg;
} SOC_G3D_SHADER_PRESENT_LO_UNION;
#endif
#define SOC_G3D_SHADER_PRESENT_LO_shader_present_lo_START  (0)
#define SOC_G3D_SHADER_PRESENT_LO_shader_present_lo_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_SHADER_PRESENT_HI_UNION
 结构说明  : SHADER_PRESENT_HI 寄存器结构定义。地址偏移量:0x0104，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  shader_present_hi : 32; /* bit[0-31]: RSV */
    } reg;
} SOC_G3D_SHADER_PRESENT_HI_UNION;
#endif
#define SOC_G3D_SHADER_PRESENT_HI_shader_present_hi_START  (0)
#define SOC_G3D_SHADER_PRESENT_HI_shader_present_hi_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_TILER_PRESENT_LO_UNION
 结构说明  : TILER_PRESENT_LO 寄存器结构定义。地址偏移量:0x0110，初值:0x00000001，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tiler_present_lo : 32; /* bit[0-31]: tiler 个数 */
    } reg;
} SOC_G3D_TILER_PRESENT_LO_UNION;
#endif
#define SOC_G3D_TILER_PRESENT_LO_tiler_present_lo_START  (0)
#define SOC_G3D_TILER_PRESENT_LO_tiler_present_lo_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_TILER_PRESENT_HI_UNION
 结构说明  : TILER_PRESENT_HI 寄存器结构定义。地址偏移量:0x0114，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tiler_present_hi : 32; /* bit[0-31]: RSV */
    } reg;
} SOC_G3D_TILER_PRESENT_HI_UNION;
#endif
#define SOC_G3D_TILER_PRESENT_HI_tiler_present_hi_START  (0)
#define SOC_G3D_TILER_PRESENT_HI_tiler_present_hi_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_L2_PRESENT_LO_UNION
 结构说明  : L2_PRESENT_LO 寄存器结构定义。地址偏移量:0x0120，初值:0x00000001，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  l2_present_lo : 32; /* bit[0-31]: l2个数 */
    } reg;
} SOC_G3D_L2_PRESENT_LO_UNION;
#endif
#define SOC_G3D_L2_PRESENT_LO_l2_present_lo_START  (0)
#define SOC_G3D_L2_PRESENT_LO_l2_present_lo_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_L2_PRESENT_HI_UNION
 结构说明  : L2_PRESENT_HI 寄存器结构定义。地址偏移量:0x0124，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  l2_present_hi : 32; /* bit[0-31]: RSV */
    } reg;
} SOC_G3D_L2_PRESENT_HI_UNION;
#endif
#define SOC_G3D_L2_PRESENT_HI_l2_present_hi_START  (0)
#define SOC_G3D_L2_PRESENT_HI_l2_present_hi_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_SHADER_READY_LO_UNION
 结构说明  : SHADER_READY_LO 寄存器结构定义。地址偏移量:0x0140，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  shader_ready_lo : 32; /* bit[0-31]: shader core ready 个数 */
    } reg;
} SOC_G3D_SHADER_READY_LO_UNION;
#endif
#define SOC_G3D_SHADER_READY_LO_shader_ready_lo_START  (0)
#define SOC_G3D_SHADER_READY_LO_shader_ready_lo_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_SHADER_READY_HI_UNION
 结构说明  : SHADER_READY_HI 寄存器结构定义。地址偏移量:0x0144，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  shader_ready_hi : 32; /* bit[0-31]: RSV */
    } reg;
} SOC_G3D_SHADER_READY_HI_UNION;
#endif
#define SOC_G3D_SHADER_READY_HI_shader_ready_hi_START  (0)
#define SOC_G3D_SHADER_READY_HI_shader_ready_hi_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_TILER_READY_LO_UNION
 结构说明  : TILER_READY_LO 寄存器结构定义。地址偏移量:0x0150，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tiler_ready_lo : 32; /* bit[0-31]: tiler ready 个数 */
    } reg;
} SOC_G3D_TILER_READY_LO_UNION;
#endif
#define SOC_G3D_TILER_READY_LO_tiler_ready_lo_START  (0)
#define SOC_G3D_TILER_READY_LO_tiler_ready_lo_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_TILER_READY_HI_UNION
 结构说明  : TILER_READY_HI 寄存器结构定义。地址偏移量:0x0154，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tiler_ready_hi : 32; /* bit[0-31]: RSV */
    } reg;
} SOC_G3D_TILER_READY_HI_UNION;
#endif
#define SOC_G3D_TILER_READY_HI_tiler_ready_hi_START  (0)
#define SOC_G3D_TILER_READY_HI_tiler_ready_hi_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_L2_READY_LO_UNION
 结构说明  : L2_READY_LO 寄存器结构定义。地址偏移量:0x0160，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  l2_ready_lo : 32; /* bit[0-31]: l2 cache ready 个数 */
    } reg;
} SOC_G3D_L2_READY_LO_UNION;
#endif
#define SOC_G3D_L2_READY_LO_l2_ready_lo_START  (0)
#define SOC_G3D_L2_READY_LO_l2_ready_lo_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_L2_READY_HI_UNION
 结构说明  : L2_READY_HI 寄存器结构定义。地址偏移量:0x0164，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  l2_ready_hi : 32; /* bit[0-31]: RSV */
    } reg;
} SOC_G3D_L2_READY_HI_UNION;
#endif
#define SOC_G3D_L2_READY_HI_l2_ready_hi_START  (0)
#define SOC_G3D_L2_READY_HI_l2_ready_hi_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_SHADER_PWRON_LO_UNION
 结构说明  : SHADER_PWRON_LO 寄存器结构定义。地址偏移量:0x0180，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  shader_pwron_lo : 32; /* bit[0-31]: 配置shader core上电。如果shader core正在下电的时候下发上电命令，则命令会被缓存，在shader core下电完成后，在配置上电。 */
    } reg;
} SOC_G3D_SHADER_PWRON_LO_UNION;
#endif
#define SOC_G3D_SHADER_PWRON_LO_shader_pwron_lo_START  (0)
#define SOC_G3D_SHADER_PWRON_LO_shader_pwron_lo_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_SHADER_PWRON_HI_UNION
 结构说明  : SHADER_PWRON_HI 寄存器结构定义。地址偏移量:0x0184，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  shader_pwron_hi : 32; /* bit[0-31]: RSV */
    } reg;
} SOC_G3D_SHADER_PWRON_HI_UNION;
#endif
#define SOC_G3D_SHADER_PWRON_HI_shader_pwron_hi_START  (0)
#define SOC_G3D_SHADER_PWRON_HI_shader_pwron_hi_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_TILER_PWRON_LO_UNION
 结构说明  : TILER_PWRON_LO 寄存器结构定义。地址偏移量:0x0190，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tiler_pwron_lo : 32; /* bit[0-31]: 配置tiler 上电 */
    } reg;
} SOC_G3D_TILER_PWRON_LO_UNION;
#endif
#define SOC_G3D_TILER_PWRON_LO_tiler_pwron_lo_START  (0)
#define SOC_G3D_TILER_PWRON_LO_tiler_pwron_lo_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_TILER_PWRON_HI_UNION
 结构说明  : TILER_PWRON_HI 寄存器结构定义。地址偏移量:0x0194，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tiler_pwron_hi : 32; /* bit[0-31]: RSV */
    } reg;
} SOC_G3D_TILER_PWRON_HI_UNION;
#endif
#define SOC_G3D_TILER_PWRON_HI_tiler_pwron_hi_START  (0)
#define SOC_G3D_TILER_PWRON_HI_tiler_pwron_hi_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_L2_PWRON_LO_UNION
 结构说明  : L2_PWRON_LO 寄存器结构定义。地址偏移量:0x01A0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  l2_pwron_lo : 32; /* bit[0-31]: 配置l2 cache上电 */
    } reg;
} SOC_G3D_L2_PWRON_LO_UNION;
#endif
#define SOC_G3D_L2_PWRON_LO_l2_pwron_lo_START  (0)
#define SOC_G3D_L2_PWRON_LO_l2_pwron_lo_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_L2_PWRON_HI_UNION
 结构说明  : L2_PWRON_HI 寄存器结构定义。地址偏移量:0x01A4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  l2_pwron_hi : 32; /* bit[0-31]: RSV */
    } reg;
} SOC_G3D_L2_PWRON_HI_UNION;
#endif
#define SOC_G3D_L2_PWRON_HI_l2_pwron_hi_START  (0)
#define SOC_G3D_L2_PWRON_HI_l2_pwron_hi_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_SHADER_PWROFF_LO_UNION
 结构说明  : SHADER_PWROFF_LO 寄存器结构定义。地址偏移量:0x01C0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  shader_pwroff_lo : 32; /* bit[0-31]: 配置shader core 下电 */
    } reg;
} SOC_G3D_SHADER_PWROFF_LO_UNION;
#endif
#define SOC_G3D_SHADER_PWROFF_LO_shader_pwroff_lo_START  (0)
#define SOC_G3D_SHADER_PWROFF_LO_shader_pwroff_lo_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_SHADER_PWROFF_HI_UNION
 结构说明  : SHADER_PWROFF_HI 寄存器结构定义。地址偏移量:0x01C4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  shader_pwroff_hi : 32; /* bit[0-31]: RSV */
    } reg;
} SOC_G3D_SHADER_PWROFF_HI_UNION;
#endif
#define SOC_G3D_SHADER_PWROFF_HI_shader_pwroff_hi_START  (0)
#define SOC_G3D_SHADER_PWROFF_HI_shader_pwroff_hi_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_TILER_PWROFF_LO_UNION
 结构说明  : TILER_PWROFF_LO 寄存器结构定义。地址偏移量:0x01D0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tiler_pwroff_lo : 32; /* bit[0-31]: 配置tiler下电 */
    } reg;
} SOC_G3D_TILER_PWROFF_LO_UNION;
#endif
#define SOC_G3D_TILER_PWROFF_LO_tiler_pwroff_lo_START  (0)
#define SOC_G3D_TILER_PWROFF_LO_tiler_pwroff_lo_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_TILER_PWROFF_HI_UNION
 结构说明  : TILER_PWROFF_HI 寄存器结构定义。地址偏移量:0x01D4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tiler_pwroff_hi : 32; /* bit[0-31]: RSV */
    } reg;
} SOC_G3D_TILER_PWROFF_HI_UNION;
#endif
#define SOC_G3D_TILER_PWROFF_HI_tiler_pwroff_hi_START  (0)
#define SOC_G3D_TILER_PWROFF_HI_tiler_pwroff_hi_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_L2_PWROFF_LO_UNION
 结构说明  : L2_PWROFF_LO 寄存器结构定义。地址偏移量:0x01E0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  l2_pwroff_lo : 32; /* bit[0-31]: 配置l2 cache下电 */
    } reg;
} SOC_G3D_L2_PWROFF_LO_UNION;
#endif
#define SOC_G3D_L2_PWROFF_LO_l2_pwroff_lo_START  (0)
#define SOC_G3D_L2_PWROFF_LO_l2_pwroff_lo_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_L2_PWROFF_HI_UNION
 结构说明  : L2_PWROFF_HI 寄存器结构定义。地址偏移量:0x01E4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  l2_pwroff_hi : 32; /* bit[0-31]: RSV */
    } reg;
} SOC_G3D_L2_PWROFF_HI_UNION;
#endif
#define SOC_G3D_L2_PWROFF_HI_l2_pwroff_hi_START  (0)
#define SOC_G3D_L2_PWROFF_HI_l2_pwroff_hi_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_SHADER_PWRTRANS_LO_UNION
 结构说明  : SHADER_PWRTRANS_LO 寄存器结构定义。地址偏移量:0x0200，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: shader core正在上下电 */
    } reg;
} SOC_G3D_SHADER_PWRTRANS_LO_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_G3D_SHADER_PWRTRANS_HI_UNION
 结构说明  : SHADER_PWRTRANS_HI 寄存器结构定义。地址偏移量:0x0204，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: RSV */
    } reg;
} SOC_G3D_SHADER_PWRTRANS_HI_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_G3D_TILER_PWRTRANS_LO_UNION
 结构说明  : TILER_PWRTRANS_LO 寄存器结构定义。地址偏移量:0x0210，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tiler_pwrtrans_lo : 32; /* bit[0-31]: tiler正在上下电 */
    } reg;
} SOC_G3D_TILER_PWRTRANS_LO_UNION;
#endif
#define SOC_G3D_TILER_PWRTRANS_LO_tiler_pwrtrans_lo_START  (0)
#define SOC_G3D_TILER_PWRTRANS_LO_tiler_pwrtrans_lo_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_TILER_PWRTRANS_HI_UNION
 结构说明  : TILER_PWRTRANS_HI 寄存器结构定义。地址偏移量:0x0214，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tiler_pwrtrans_hi : 32; /* bit[0-31]: RSV */
    } reg;
} SOC_G3D_TILER_PWRTRANS_HI_UNION;
#endif
#define SOC_G3D_TILER_PWRTRANS_HI_tiler_pwrtrans_hi_START  (0)
#define SOC_G3D_TILER_PWRTRANS_HI_tiler_pwrtrans_hi_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_L2_PWRTRANS_LO_UNION
 结构说明  : L2_PWRTRANS_LO 寄存器结构定义。地址偏移量:0x0220，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  l2_pwrtrans_lo : 32; /* bit[0-31]: l2 cache正在下电 */
    } reg;
} SOC_G3D_L2_PWRTRANS_LO_UNION;
#endif
#define SOC_G3D_L2_PWRTRANS_LO_l2_pwrtrans_lo_START  (0)
#define SOC_G3D_L2_PWRTRANS_LO_l2_pwrtrans_lo_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_L2_PWRTRANS_HI_UNION
 结构说明  : L2_PWRTRANS_HI 寄存器结构定义。地址偏移量:0x0224，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  l2_pwrtrans_hi : 32; /* bit[0-31]: RSV */
    } reg;
} SOC_G3D_L2_PWRTRANS_HI_UNION;
#endif
#define SOC_G3D_L2_PWRTRANS_HI_l2_pwrtrans_hi_START  (0)
#define SOC_G3D_L2_PWRTRANS_HI_l2_pwrtrans_hi_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_SHADER_PWRACTIVE_LO_UNION
 结构说明  : SHADER_PWRACTIVE_LO 寄存器结构定义。地址偏移量:0x0240，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  shader_pwractive_lo : 32; /* bit[0-31]: shader core active */
    } reg;
} SOC_G3D_SHADER_PWRACTIVE_LO_UNION;
#endif
#define SOC_G3D_SHADER_PWRACTIVE_LO_shader_pwractive_lo_START  (0)
#define SOC_G3D_SHADER_PWRACTIVE_LO_shader_pwractive_lo_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_SHADER_PWRACTIVE_HI_UNION
 结构说明  : SHADER_PWRACTIVE_HI 寄存器结构定义。地址偏移量:0x0244，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  shader_pwractive_hi : 32; /* bit[0-31]: RSV */
    } reg;
} SOC_G3D_SHADER_PWRACTIVE_HI_UNION;
#endif
#define SOC_G3D_SHADER_PWRACTIVE_HI_shader_pwractive_hi_START  (0)
#define SOC_G3D_SHADER_PWRACTIVE_HI_shader_pwractive_hi_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_TILER_PWRACTIVE_LO_UNION
 结构说明  : TILER_PWRACTIVE_LO 寄存器结构定义。地址偏移量:0x0250，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tiler_pwractive_lo : 32; /* bit[0-31]: tiler active */
    } reg;
} SOC_G3D_TILER_PWRACTIVE_LO_UNION;
#endif
#define SOC_G3D_TILER_PWRACTIVE_LO_tiler_pwractive_lo_START  (0)
#define SOC_G3D_TILER_PWRACTIVE_LO_tiler_pwractive_lo_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_TILER_PWRACTIVE_HI_UNION
 结构说明  : TILER_PWRACTIVE_HI 寄存器结构定义。地址偏移量:0x0254，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tiler_pwractive_hi : 32; /* bit[0-31]: RSV */
    } reg;
} SOC_G3D_TILER_PWRACTIVE_HI_UNION;
#endif
#define SOC_G3D_TILER_PWRACTIVE_HI_tiler_pwractive_hi_START  (0)
#define SOC_G3D_TILER_PWRACTIVE_HI_tiler_pwractive_hi_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_L2_PWRACTIVE_LO_UNION
 结构说明  : L2_PWRACTIVE_LO 寄存器结构定义。地址偏移量:0x0260，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  l2_pwractive_lo : 32; /* bit[0-31]: l2 cache active */
    } reg;
} SOC_G3D_L2_PWRACTIVE_LO_UNION;
#endif
#define SOC_G3D_L2_PWRACTIVE_LO_l2_pwractive_lo_START  (0)
#define SOC_G3D_L2_PWRACTIVE_LO_l2_pwractive_lo_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_L2_PWRACTIVE_HI_UNION
 结构说明  : L2_PWRACTIVE_HI 寄存器结构定义。地址偏移量:0x0264，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  l2_pwractive_hi : 32; /* bit[0-31]: RSV */
    } reg;
} SOC_G3D_L2_PWRACTIVE_HI_UNION;
#endif
#define SOC_G3D_L2_PWRACTIVE_HI_l2_pwractive_hi_START  (0)
#define SOC_G3D_L2_PWRACTIVE_HI_l2_pwractive_hi_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_REV_ID_UNION
 结构说明  : REV_ID 寄存器结构定义。地址偏移量:0x0280，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rev_id : 32; /* bit[0-31]: RSV */
    } reg;
} SOC_G3D_REV_ID_UNION;
#endif
#define SOC_G3D_REV_ID_rev_id_START  (0)
#define SOC_G3D_REV_ID_rev_id_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_JM_CONFIG_UNION
 结构说明  : JM_CONFIG 寄存器结构定义。地址偏移量:0x0F00，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  jc_config : 32; /* bit[0-31]: RSV */
    } reg;
} SOC_G3D_JM_CONFIG_UNION;
#endif
#define SOC_G3D_JM_CONFIG_jc_config_START  (0)
#define SOC_G3D_JM_CONFIG_jc_config_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_SHADER_CONFIG_UNION
 结构说明  : SHADER_CONFIG 寄存器结构定义。地址偏移量:0x0F04，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved      : 3;  /* bit[0-2] : RSV */
        unsigned int  all_counters  : 1;  /* bit[3-3] : 0:无
                                                        1:1/8
                                                        2:1/4
                                                        3:1/2 */
        unsigned int  shader_config : 28; /* bit[4-31]: Reserved. write as zero, read undefined.  */
    } reg;
} SOC_G3D_SHADER_CONFIG_UNION;
#endif
#define SOC_G3D_SHADER_CONFIG_all_counters_START   (3)
#define SOC_G3D_SHADER_CONFIG_all_counters_END     (3)
#define SOC_G3D_SHADER_CONFIG_shader_config_START  (4)
#define SOC_G3D_SHADER_CONFIG_shader_config_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_TILER_CONFIG_UNION
 结构说明  : TILER_CONFIG 寄存器结构定义。地址偏移量:0x0F08，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tiler_config : 32; /* bit[0-31]: RSV */
    } reg;
} SOC_G3D_TILER_CONFIG_UNION;
#endif
#define SOC_G3D_TILER_CONFIG_tiler_config_START  (0)
#define SOC_G3D_TILER_CONFIG_tiler_config_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_L2_MMU_CONFIG_UNION
 结构说明  : L2_MMU_CONFIG 寄存器结构定义。地址偏移量:0x0F0C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved              : 24; /* bit[0-23] : RSV */
        unsigned int  limit_external_reads  : 2;  /* bit[24-25]: 0:无
                                                                 1:1/8
                                                                 2:1/4
                                                                 3:1/2 */
        unsigned int  limit_external_writes : 2;  /* bit[26-27]: 0:无
                                                                 1:1/8
                                                                 2:1/4
                                                                 3:1/2 */
        unsigned int  l2_mmu_config         : 4;  /* bit[28-31]: Reserved. write as zero, read undefined.  */
    } reg;
} SOC_G3D_L2_MMU_CONFIG_UNION;
#endif
#define SOC_G3D_L2_MMU_CONFIG_limit_external_reads_START   (24)
#define SOC_G3D_L2_MMU_CONFIG_limit_external_reads_END     (25)
#define SOC_G3D_L2_MMU_CONFIG_limit_external_writes_START  (26)
#define SOC_G3D_L2_MMU_CONFIG_limit_external_writes_END    (27)
#define SOC_G3D_L2_MMU_CONFIG_l2_mmu_config_START          (28)
#define SOC_G3D_L2_MMU_CONFIG_l2_mmu_config_END            (31)


/*****************************************************************************
 结构名    : SOC_G3D_JOB_IRQ_RAWSTAT_UNION
 结构说明  : JOB_IRQ_RAWSTAT 寄存器结构定义。地址偏移量:0x1000，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  job_done : 3;  /* bit[0-2]  : job done.1 bit 对应 1个slot */
        unsigned int  reserved_0: 13; /* bit[3-15] : Reserved. write as zero, read undefined. */
        unsigned int  job_fail : 3;  /* bit[16-18]: job fail.1 bit 对应 1个slot */
        unsigned int  reserved_1: 13; /* bit[19-31]: Reserved. write as zero, read undefined.  */
    } reg;
} SOC_G3D_JOB_IRQ_RAWSTAT_UNION;
#endif
#define SOC_G3D_JOB_IRQ_RAWSTAT_job_done_START  (0)
#define SOC_G3D_JOB_IRQ_RAWSTAT_job_done_END    (2)
#define SOC_G3D_JOB_IRQ_RAWSTAT_job_fail_START  (16)
#define SOC_G3D_JOB_IRQ_RAWSTAT_job_fail_END    (18)


/*****************************************************************************
 结构名    : SOC_G3D_JOB_IRQ_CLEAR_UNION
 结构说明  : JOB_IRQ_CLEAR 寄存器结构定义。地址偏移量:0x1004，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  job_done      : 3;  /* bit[0-2]  : 对应中断写1清除寄存器 */
        unsigned int  reserved      : 13; /* bit[3-15] : Interrupt clear register :Reserved, write as zero, read undefined. */
        unsigned int  job_fail      : 3;  /* bit[16-18]: 对应中断写1清除寄存器 */
        unsigned int  job_irq_clear : 13; /* bit[19-31]: Interrupt clear register :Reserved, write as zero, read undefined. */
    } reg;
} SOC_G3D_JOB_IRQ_CLEAR_UNION;
#endif
#define SOC_G3D_JOB_IRQ_CLEAR_job_done_START       (0)
#define SOC_G3D_JOB_IRQ_CLEAR_job_done_END         (2)
#define SOC_G3D_JOB_IRQ_CLEAR_job_fail_START       (16)
#define SOC_G3D_JOB_IRQ_CLEAR_job_fail_END         (18)
#define SOC_G3D_JOB_IRQ_CLEAR_job_irq_clear_START  (19)
#define SOC_G3D_JOB_IRQ_CLEAR_job_irq_clear_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_JOB_IRQ_MASK_UNION
 结构说明  : JOB_IRQ_MASK 寄存器结构定义。地址偏移量:0x1008，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  job_done : 3;  /* bit[0-2]  : 对应写1使能寄存器。 */
        unsigned int  reserved_0: 13; /* bit[3-15] : Reserved. write as zero, read undefined. */
        unsigned int  job_fail : 3;  /* bit[16-18]: 对应写1使能寄存器。 */
        unsigned int  reserved_1: 13; /* bit[19-31]: Interrupt mask register ：Reserved. write as zero, read undefined. */
    } reg;
} SOC_G3D_JOB_IRQ_MASK_UNION;
#endif
#define SOC_G3D_JOB_IRQ_MASK_job_done_START  (0)
#define SOC_G3D_JOB_IRQ_MASK_job_done_END    (2)
#define SOC_G3D_JOB_IRQ_MASK_job_fail_START  (16)
#define SOC_G3D_JOB_IRQ_MASK_job_fail_END    (18)


/*****************************************************************************
 结构名    : SOC_G3D_JOB_IRQ_STATUS_UNION
 结构说明  : JOB_IRQ_STATUS 寄存器结构定义。地址偏移量:0x100C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  job_done : 3;  /* bit[0-2]  : 状态和掩码与逻辑后状态 */
        unsigned int  reserved_0: 13; /* bit[3-15] : Reserved. write as zero, read undefined. */
        unsigned int  job_fail : 3;  /* bit[16-18]: 状态和掩码与逻辑后状态 */
        unsigned int  reserved_1: 13; /* bit[19-31]: Interrupt status register ：：Reserved. write as zero, read undefined. */
    } reg;
} SOC_G3D_JOB_IRQ_STATUS_UNION;
#endif
#define SOC_G3D_JOB_IRQ_STATUS_job_done_START  (0)
#define SOC_G3D_JOB_IRQ_STATUS_job_done_END    (2)
#define SOC_G3D_JOB_IRQ_STATUS_job_fail_START  (16)
#define SOC_G3D_JOB_IRQ_STATUS_job_fail_END    (18)


/*****************************************************************************
 结构名    : SOC_G3D_JOB_IRQ_JS_STATE_UNION
 结构说明  : JOB_IRQ_JS_STATE 寄存器结构定义。地址偏移量:0x1010，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  job_active_n      : 16; /* bit[0-15] : A job chain is queued in job slot n */
        unsigned int  job_next_active_n : 16; /* bit[16-31]: A job chain is queued in the NEXT registers in job slot n */
    } reg;
} SOC_G3D_JOB_IRQ_JS_STATE_UNION;
#endif
#define SOC_G3D_JOB_IRQ_JS_STATE_job_active_n_START       (0)
#define SOC_G3D_JOB_IRQ_JS_STATE_job_active_n_END         (15)
#define SOC_G3D_JOB_IRQ_JS_STATE_job_next_active_n_START  (16)
#define SOC_G3D_JOB_IRQ_JS_STATE_job_next_active_n_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_JOB_IRQ_THROTTLE_UNION
 结构说明  : JOB_IRQ_THROTTLE 寄存器结构定义。地址偏移量:0x1014，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  job_irq_throttle : 32; /* bit[0-31]: Interrupt throttle register：Writing a value to the register sets the value of a counter,
                                                           which then continuously counts down at the GPU clock
                                                           frequency. Reading this register returns the current value
                                                           of the counter. */
    } reg;
} SOC_G3D_JOB_IRQ_THROTTLE_UNION;
#endif
#define SOC_G3D_JOB_IRQ_THROTTLE_job_irq_throttle_START  (0)
#define SOC_G3D_JOB_IRQ_THROTTLE_job_irq_throttle_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_JS0_HEAD_LO_UNION
 结构说明  : JS0_HEAD_LO 寄存器结构定义。地址偏移量:0x1800，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved    : 6;  /* bit[0-5] : Reserved. write as zero, read undefined. */
        unsigned int  js0_head_lo : 26; /* bit[6-31]: Job queue head pointer for job slot register：Contains the virtual address for the current job
                                                      descriptor */
    } reg;
} SOC_G3D_JS0_HEAD_LO_UNION;
#endif
#define SOC_G3D_JS0_HEAD_LO_js0_head_lo_START  (6)
#define SOC_G3D_JS0_HEAD_LO_js0_head_lo_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_JS0_HEAD_HI_UNION
 结构说明  : JS0_HEAD_HI 寄存器结构定义。地址偏移量:0x1804，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  js0_head_hi : 16; /* bit[0-15] : Job queue head pointer for job slot register：Contains the virtual address for the current job
                                                       descriptor */
        unsigned int  reserved    : 16; /* bit[16-31]: Reserved. write as zero, read undefined. */
    } reg;
} SOC_G3D_JS0_HEAD_HI_UNION;
#endif
#define SOC_G3D_JS0_HEAD_HI_js0_head_hi_START  (0)
#define SOC_G3D_JS0_HEAD_HI_js0_head_hi_END    (15)


/*****************************************************************************
 结构名    : SOC_G3D_JS0_TAIL_LO_UNION
 结构说明  : JS0_TAIL_LO 寄存器结构定义。地址偏移量:0x1808，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved    : 6;  /* bit[0-5] : Reserved. write as zero, read undefined. */
        unsigned int  js0_tail_lo : 26; /* bit[6-31]: Contains the virtual address of the oldest job that has
                                                      finished issuing tasks, but is still running. */
    } reg;
} SOC_G3D_JS0_TAIL_LO_UNION;
#endif
#define SOC_G3D_JS0_TAIL_LO_js0_tail_lo_START  (6)
#define SOC_G3D_JS0_TAIL_LO_js0_tail_lo_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_JS0_TAIL_HI_UNION
 结构说明  : JS0_TAIL_HI 寄存器结构定义。地址偏移量:0x180C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  js0_tail_hi : 16; /* bit[0-15] : Contains the virtual address of the oldest job that has
                                                       finished issuing tasks, but is still running. */
        unsigned int  reserved    : 16; /* bit[16-31]: Reserved. write as zero, read undefined. */
    } reg;
} SOC_G3D_JS0_TAIL_HI_UNION;
#endif
#define SOC_G3D_JS0_TAIL_HI_js0_tail_hi_START  (0)
#define SOC_G3D_JS0_TAIL_HI_js0_tail_hi_END    (15)


/*****************************************************************************
 结构名    : SOC_G3D_JS0_AFFINITY_LO_UNION
 结构说明  : JS0_AFFINITY_LO 寄存器结构定义。地址偏移量:0x1810，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  js0_affinity_lo : 32; /* bit[0-31]: Core affinity mask for job slot register:Contains the address of the oldest job that has finished
                                                          issuing tasks, but is still running. */
    } reg;
} SOC_G3D_JS0_AFFINITY_LO_UNION;
#endif
#define SOC_G3D_JS0_AFFINITY_LO_js0_affinity_lo_START  (0)
#define SOC_G3D_JS0_AFFINITY_LO_js0_affinity_lo_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_JS0_AFFINITY_HI_UNION
 结构说明  : JS0_AFFINITY_HI 寄存器结构定义。地址偏移量:0x1814，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  js0_affinity_hi : 32; /* bit[0-31]: Core affinity mask register for job slot:Contains the address of the oldest job that has finished
                                                          issuing tasks, but is still running. */
    } reg;
} SOC_G3D_JS0_AFFINITY_HI_UNION;
#endif
#define SOC_G3D_JS0_AFFINITY_HI_js0_affinity_hi_START  (0)
#define SOC_G3D_JS0_AFFINITY_HI_js0_affinity_hi_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_JS0_CONFIG_UNION
 结构说明  : JS0_CONFIG 寄存器结构定义。地址偏移量:0x1818，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  address_space : 4;  /* bit[0-3]  : Selects which of the address spaces to use for jobs in
                                                         this slot. The address space configuration values are
                                                         read from the ASn registers. */
        unsigned int  reserved_0    : 4;  /* bit[4-7]  : Reserved, write as zero, read undefined. */
        unsigned int  start_flush   : 2;  /* bit[8-9]  : Cache flush action on job chain start. Specifies what
                                                         action the caches must take before starting the job chain.
                                                         0 No flush
                                                         1 Clean
                                                         2 Reserved
                                                         3 Clean and invalidate.
                                                         The selected action applies to all caches except the tiler
                                                         cache. */
        unsigned int  start_mmu     : 1;  /* bit[10]   : MMU action on job chain start. Causes the Job Manager
                                                         to issue an MMU update before the job chain is started. */
        unsigned int  reserved_1    : 1;  /* bit[11]   : Reserved, write as zero, read undefined. */
        unsigned int  end_flush     : 2;  /* bit[12-13]: Cache flush action on job end chain. Specifies what
                                                         action the caches must take after finishing the job chain.
                                                         0 No flush
                                                         1 Clean
                                                         2 Reserved
                                                         3 Clean and invalidate.
                                                         The selected action applies to all caches including the
                                                         tiler cache. */
        unsigned int  reserved_2    : 18; /* bit[14-31]: Reserved, write as zero, read undefined. */
    } reg;
} SOC_G3D_JS0_CONFIG_UNION;
#endif
#define SOC_G3D_JS0_CONFIG_address_space_START  (0)
#define SOC_G3D_JS0_CONFIG_address_space_END    (3)
#define SOC_G3D_JS0_CONFIG_start_flush_START    (8)
#define SOC_G3D_JS0_CONFIG_start_flush_END      (9)
#define SOC_G3D_JS0_CONFIG_start_mmu_START      (10)
#define SOC_G3D_JS0_CONFIG_start_mmu_END        (10)
#define SOC_G3D_JS0_CONFIG_end_flush_START      (12)
#define SOC_G3D_JS0_CONFIG_end_flush_END        (13)


/*****************************************************************************
 结构名    : SOC_G3D_JS0_COMMAND_UNION
 结构说明  : JS0_COMMAND 寄存器结构定义。地址偏移量:0x1820，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  nop       : 1;  /* bit[0]   : Writing to this value is ignored */
        unsigned int  start     : 1;  /* bit[1]   : Start processing a job chain */
        unsigned int  soft_stop : 1;  /* bit[2]   : A soft stop requests that no more tasks are issued for a
                                                    job, and when all running tasks are finished, the job
                                                    state is written to memory and the job suspended.
                                                    It is possible to recover from this state and continue the
                                                    job. */
        unsigned int  hard_stop : 1;  /* bit[3]   : A hard stop stops all running tasks for a job. No attempt
                                                    is made to finish, write partial results, or save state.
                                                    It is not possible to resume a job after a hard stop,
                                                    although it might be possible to restart it from scratch if
                                                    it does not write to its own inputs. */
        unsigned int  reserved  : 28; /* bit[4-31]: Reserved, write as zero, read undefined. */
    } reg;
} SOC_G3D_JS0_COMMAND_UNION;
#endif
#define SOC_G3D_JS0_COMMAND_nop_START        (0)
#define SOC_G3D_JS0_COMMAND_nop_END          (0)
#define SOC_G3D_JS0_COMMAND_start_START      (1)
#define SOC_G3D_JS0_COMMAND_start_END        (1)
#define SOC_G3D_JS0_COMMAND_soft_stop_START  (2)
#define SOC_G3D_JS0_COMMAND_soft_stop_END    (2)
#define SOC_G3D_JS0_COMMAND_hard_stop_START  (3)
#define SOC_G3D_JS0_COMMAND_hard_stop_END    (3)


/*****************************************************************************
 结构名    : SOC_G3D_JS0_STATUS_UNION
 结构说明  : JS0_STATUS 寄存器结构定义。地址偏移量:0x1824，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  exception_type : 8;  /* bit[0-7] : Contains the type of exception that caused the fault. */
        unsigned int  reserved       : 24; /* bit[8-31]: Status for job slot register:Reserved, write as zero, read undefined. */
    } reg;
} SOC_G3D_JS0_STATUS_UNION;
#endif
#define SOC_G3D_JS0_STATUS_exception_type_START  (0)
#define SOC_G3D_JS0_STATUS_exception_type_END    (7)


/*****************************************************************************
 结构名    : SOC_G3D_JS0_HEAD_NEXT_LO_UNION
 结构说明  : JS0_HEAD_NEXT_LO 寄存器结构定义。地址偏移量:0x1840，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  js0_head_next_lo : 32; /* bit[0-31]: Next job queue head pointer for job slot register */
    } reg;
} SOC_G3D_JS0_HEAD_NEXT_LO_UNION;
#endif
#define SOC_G3D_JS0_HEAD_NEXT_LO_js0_head_next_lo_START  (0)
#define SOC_G3D_JS0_HEAD_NEXT_LO_js0_head_next_lo_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_JS0_HEAD_NEXT_HI_UNION
 结构说明  : JS0_HEAD_NEXT_HI 寄存器结构定义。地址偏移量:0x1844，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  js0_head_next_hi : 32; /* bit[0-31]: Next job queue head pointer for job slot register */
    } reg;
} SOC_G3D_JS0_HEAD_NEXT_HI_UNION;
#endif
#define SOC_G3D_JS0_HEAD_NEXT_HI_js0_head_next_hi_START  (0)
#define SOC_G3D_JS0_HEAD_NEXT_HI_js0_head_next_hi_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_JS0_AFFINITY_NEXT_LO_UNION
 结构说明  : JS0_AFFINITY_NEXT_LO 寄存器结构定义。地址偏移量:0x1850，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: Next core affinity mask for job slot register */
    } reg;
} SOC_G3D_JS0_AFFINITY_NEXT_LO_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_G3D_JS0_AFFINITY_NEXT_HI_UNION
 结构说明  : JS0_AFFINITY_NEXT_HI 寄存器结构定义。地址偏移量:0x1854，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: Next core affinity mask for job slot register */
    } reg;
} SOC_G3D_JS0_AFFINITY_NEXT_HI_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_G3D_JS0_CONFIG_NEXT_UNION
 结构说明  : JS0_CONFIG_NEXT 寄存器结构定义。地址偏移量:0x1858，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  address_space : 4;  /* bit[0-3]  : Selects which of the address spaces to use for jobs in
                                                         this slot. The address space configuration values are
                                                         read from the ASn registers. */
        unsigned int  reserved_0    : 4;  /* bit[4-7]  : Reserved, write as zero, read undefined. */
        unsigned int  start_flush   : 2;  /* bit[8-9]  : Cache flush action on job chain start. Specifies what
                                                         action the caches must take before starting the job chain.
                                                         0 No flush
                                                         1 Clean
                                                         2 Reserved
                                                         3 Clean and invalidate.
                                                         The selected action applies to all caches except the tiler
                                                         cache. */
        unsigned int  start_mmu     : 1;  /* bit[10]   : MMU action on job chain start. Causes the Job Manager
                                                         to issue an MMU update before the job chain is started. */
        unsigned int  reserved_1    : 1;  /* bit[11]   : Reserved, write as zero, read undefined. */
        unsigned int  end_flush     : 2;  /* bit[12-13]: Cache flush action on job end chain. Specifies what
                                                         action the caches must take after finishing the job chain.
                                                         0 No flush
                                                         1 Clean
                                                         2 Reserved
                                                         3 Clean and invalidate.
                                                         The selected action applies to all caches including the
                                                         tiler cache. */
        unsigned int  reserved_2    : 18; /* bit[14-31]: Next configuration setting for job slot register
                                                         The JSn_CONFIG_NEXT register is an identical register used to construct job chains one ahead
                                                         so maintaining throughput. The values in the register are loaded into the JSn_CONFIG register
                                                         when the current job chain completes */
    } reg;
} SOC_G3D_JS0_CONFIG_NEXT_UNION;
#endif
#define SOC_G3D_JS0_CONFIG_NEXT_address_space_START  (0)
#define SOC_G3D_JS0_CONFIG_NEXT_address_space_END    (3)
#define SOC_G3D_JS0_CONFIG_NEXT_start_flush_START    (8)
#define SOC_G3D_JS0_CONFIG_NEXT_start_flush_END      (9)
#define SOC_G3D_JS0_CONFIG_NEXT_start_mmu_START      (10)
#define SOC_G3D_JS0_CONFIG_NEXT_start_mmu_END        (10)
#define SOC_G3D_JS0_CONFIG_NEXT_end_flush_START      (12)
#define SOC_G3D_JS0_CONFIG_NEXT_end_flush_END        (13)


/*****************************************************************************
 结构名    : SOC_G3D_JS0_COMMAND_NEXT_UNION
 结构说明  : JS0_COMMAND_NEXT 寄存器结构定义。地址偏移量:0x1860，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: Next command for job slot register */
    } reg;
} SOC_G3D_JS0_COMMAND_NEXT_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_G3D_JS1_HEAD_LO_UNION
 结构说明  : JS1_HEAD_LO 寄存器结构定义。地址偏移量:0x1880，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved    : 6;  /* bit[0-5] : Reserved. write as zero, read undefined. */
        unsigned int  js1_head_lo : 26; /* bit[6-31]: Job queue head pointer for job slot register：Contains the virtual address for the current job
                                                      descriptor */
    } reg;
} SOC_G3D_JS1_HEAD_LO_UNION;
#endif
#define SOC_G3D_JS1_HEAD_LO_js1_head_lo_START  (6)
#define SOC_G3D_JS1_HEAD_LO_js1_head_lo_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_JS1_HEAD_HI_UNION
 结构说明  : JS1_HEAD_HI 寄存器结构定义。地址偏移量:0x1884，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  js1_head_hi : 16; /* bit[0-15] : Job queue head pointer for job slot register：Contains the virtual address for the current job
                                                       descriptor */
        unsigned int  reserved    : 16; /* bit[16-31]: Reserved. write as zero, read undefined. */
    } reg;
} SOC_G3D_JS1_HEAD_HI_UNION;
#endif
#define SOC_G3D_JS1_HEAD_HI_js1_head_hi_START  (0)
#define SOC_G3D_JS1_HEAD_HI_js1_head_hi_END    (15)


/*****************************************************************************
 结构名    : SOC_G3D_JS1_TAIL_LO_UNION
 结构说明  : JS1_TAIL_LO 寄存器结构定义。地址偏移量:0x1888，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved    : 6;  /* bit[0-5] : Reserved. write as zero, read undefined. */
        unsigned int  js1_tail_lo : 26; /* bit[6-31]: Contains the virtual address of the oldest job that has
                                                      finished issuing tasks, but is still running. */
    } reg;
} SOC_G3D_JS1_TAIL_LO_UNION;
#endif
#define SOC_G3D_JS1_TAIL_LO_js1_tail_lo_START  (6)
#define SOC_G3D_JS1_TAIL_LO_js1_tail_lo_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_JS1_TAIL_HI_UNION
 结构说明  : JS1_TAIL_HI 寄存器结构定义。地址偏移量:0x188C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  js1_tail_hi : 16; /* bit[0-15] : Contains the virtual address of the oldest job that has
                                                       finished issuing tasks, but is still running. */
        unsigned int  reserved    : 16; /* bit[16-31]: Reserved. write as zero, read undefined. */
    } reg;
} SOC_G3D_JS1_TAIL_HI_UNION;
#endif
#define SOC_G3D_JS1_TAIL_HI_js1_tail_hi_START  (0)
#define SOC_G3D_JS1_TAIL_HI_js1_tail_hi_END    (15)


/*****************************************************************************
 结构名    : SOC_G3D_JS1_AFFINITY_LO_UNION
 结构说明  : JS1_AFFINITY_LO 寄存器结构定义。地址偏移量:0x1890，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  js1_affinity_lo : 32; /* bit[0-31]: Core affinity mask for job slot register */
    } reg;
} SOC_G3D_JS1_AFFINITY_LO_UNION;
#endif
#define SOC_G3D_JS1_AFFINITY_LO_js1_affinity_lo_START  (0)
#define SOC_G3D_JS1_AFFINITY_LO_js1_affinity_lo_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_JS1_AFFINITY_HI_UNION
 结构说明  : JS1_AFFINITY_HI 寄存器结构定义。地址偏移量:0x1894，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  js1_affinity_hi : 32; /* bit[0-31]: Core affinity mask register for job slot */
    } reg;
} SOC_G3D_JS1_AFFINITY_HI_UNION;
#endif
#define SOC_G3D_JS1_AFFINITY_HI_js1_affinity_hi_START  (0)
#define SOC_G3D_JS1_AFFINITY_HI_js1_affinity_hi_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_JS1_CONFIG_UNION
 结构说明  : JS1_CONFIG 寄存器结构定义。地址偏移量:0x1898，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  address_space : 4;  /* bit[0-3]  : Selects which of the address spaces to use for jobs in
                                                         this slot. The address space configuration values are
                                                         read from the ASn registers. */
        unsigned int  reserved_0    : 4;  /* bit[4-7]  : Reserved, write as zero, read undefined. */
        unsigned int  start_flush   : 2;  /* bit[8-9]  : Cache flush action on job chain start. Specifies what
                                                         action the caches must take before starting the job chain.
                                                         0 No flush
                                                         1 Clean
                                                         2 Reserved
                                                         3 Clean and invalidate.
                                                         The selected action applies to all caches except the tiler
                                                         cache. */
        unsigned int  start_mmu     : 1;  /* bit[10]   : MMU action on job chain start. Causes the Job Manager
                                                         to issue an MMU update before the job chain is started. */
        unsigned int  reserved_1    : 1;  /* bit[11]   : Reserved, write as zero, read undefined. */
        unsigned int  end_flush     : 2;  /* bit[12-13]: Cache flush action on job end chain. Specifies what
                                                         action the caches must take after finishing the job chain.
                                                         0 No flush
                                                         1 Clean
                                                         2 Reserved
                                                         3 Clean and invalidate.
                                                         The selected action applies to all caches including the
                                                         tiler cache. */
        unsigned int  reserved_2    : 18; /* bit[14-31]: Reserved, write as zero, read undefined. */
    } reg;
} SOC_G3D_JS1_CONFIG_UNION;
#endif
#define SOC_G3D_JS1_CONFIG_address_space_START  (0)
#define SOC_G3D_JS1_CONFIG_address_space_END    (3)
#define SOC_G3D_JS1_CONFIG_start_flush_START    (8)
#define SOC_G3D_JS1_CONFIG_start_flush_END      (9)
#define SOC_G3D_JS1_CONFIG_start_mmu_START      (10)
#define SOC_G3D_JS1_CONFIG_start_mmu_END        (10)
#define SOC_G3D_JS1_CONFIG_end_flush_START      (12)
#define SOC_G3D_JS1_CONFIG_end_flush_END        (13)


/*****************************************************************************
 结构名    : SOC_G3D_JS1_COMMAND_UNION
 结构说明  : JS1_COMMAND 寄存器结构定义。地址偏移量:0x18A0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  js1_command : 32; /* bit[0-31]: Command for job slot register */
    } reg;
} SOC_G3D_JS1_COMMAND_UNION;
#endif
#define SOC_G3D_JS1_COMMAND_js1_command_START  (0)
#define SOC_G3D_JS1_COMMAND_js1_command_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_JS1_STATUS_UNION
 结构说明  : JS1_STATUS 寄存器结构定义。地址偏移量:0x18A4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  js1_status : 32; /* bit[0-31]: Status for job slot register */
    } reg;
} SOC_G3D_JS1_STATUS_UNION;
#endif
#define SOC_G3D_JS1_STATUS_js1_status_START  (0)
#define SOC_G3D_JS1_STATUS_js1_status_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_JS1_HEAD_NEXT_LO_UNION
 结构说明  : JS1_HEAD_NEXT_LO 寄存器结构定义。地址偏移量:0x18C0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  js1_head_next_lo : 32; /* bit[0-31]: Next job queue head pointer for job slot register */
    } reg;
} SOC_G3D_JS1_HEAD_NEXT_LO_UNION;
#endif
#define SOC_G3D_JS1_HEAD_NEXT_LO_js1_head_next_lo_START  (0)
#define SOC_G3D_JS1_HEAD_NEXT_LO_js1_head_next_lo_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_JS1_HEAD_NEXT_HI_UNION
 结构说明  : JS1_HEAD_NEXT_HI 寄存器结构定义。地址偏移量:0x18C4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  js1_head_next_hi : 32; /* bit[0-31]: Next job queue head pointer for job slot register */
    } reg;
} SOC_G3D_JS1_HEAD_NEXT_HI_UNION;
#endif
#define SOC_G3D_JS1_HEAD_NEXT_HI_js1_head_next_hi_START  (0)
#define SOC_G3D_JS1_HEAD_NEXT_HI_js1_head_next_hi_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_JS1_AFFINITY_NEXT_LO_UNION
 结构说明  : JS1_AFFINITY_NEXT_LO 寄存器结构定义。地址偏移量:0x18D0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: Next core affinity mask for job slot register */
    } reg;
} SOC_G3D_JS1_AFFINITY_NEXT_LO_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_G3D_JS1_AFFINITY_NEXT_HI_UNION
 结构说明  : JS1_AFFINITY_NEXT_HI 寄存器结构定义。地址偏移量:0x18D4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: Next core affinity mask for job slot register */
    } reg;
} SOC_G3D_JS1_AFFINITY_NEXT_HI_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_G3D_JS1_CONFIG_NEXT_UNION
 结构说明  : JS1_CONFIG_NEXT 寄存器结构定义。地址偏移量:0x18D8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  address_space : 4;  /* bit[0-3]  : Selects which of the address spaces to use for jobs in
                                                         this slot. The address space configuration values are
                                                         read from the ASn registers. */
        unsigned int  reserved_0    : 4;  /* bit[4-7]  : Reserved, write as zero, read undefined. */
        unsigned int  start_flush   : 2;  /* bit[8-9]  : Cache flush action on job chain start. Specifies what
                                                         action the caches must take before starting the job chain.
                                                         0 No flush
                                                         1 Clean
                                                         2 Reserved
                                                         3 Clean and invalidate.
                                                         The selected action applies to all caches except the tiler
                                                         cache. */
        unsigned int  start_mmu     : 1;  /* bit[10]   : MMU action on job chain start. Causes the Job Manager
                                                         to issue an MMU update before the job chain is started. */
        unsigned int  reserved_1    : 1;  /* bit[11]   : Reserved, write as zero, read undefined. */
        unsigned int  end_flush     : 2;  /* bit[12-13]: Cache flush action on job end chain. Specifies what
                                                         action the caches must take after finishing the job chain.
                                                         0 No flush
                                                         1 Clean
                                                         2 Reserved
                                                         3 Clean and invalidate.
                                                         The selected action applies to all caches including the
                                                         tiler cache. */
        unsigned int  reserved_2    : 18; /* bit[14-31]: Next configuration setting for job slot register
                                                         The JSn_CONFIG_NEXT register is an identical register used to construct job chains one ahead
                                                         so maintaining throughput. The values in the register are loaded into the JSn_CONFIG register
                                                         when the current job chain completes */
    } reg;
} SOC_G3D_JS1_CONFIG_NEXT_UNION;
#endif
#define SOC_G3D_JS1_CONFIG_NEXT_address_space_START  (0)
#define SOC_G3D_JS1_CONFIG_NEXT_address_space_END    (3)
#define SOC_G3D_JS1_CONFIG_NEXT_start_flush_START    (8)
#define SOC_G3D_JS1_CONFIG_NEXT_start_flush_END      (9)
#define SOC_G3D_JS1_CONFIG_NEXT_start_mmu_START      (10)
#define SOC_G3D_JS1_CONFIG_NEXT_start_mmu_END        (10)
#define SOC_G3D_JS1_CONFIG_NEXT_end_flush_START      (12)
#define SOC_G3D_JS1_CONFIG_NEXT_end_flush_END        (13)


/*****************************************************************************
 结构名    : SOC_G3D_JS1_COMMAND_NEXT_UNION
 结构说明  : JS1_COMMAND_NEXT 寄存器结构定义。地址偏移量:0x18E0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: Next command for job slot register */
    } reg;
} SOC_G3D_JS1_COMMAND_NEXT_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_G3D_JS2_HEAD_LO_UNION
 结构说明  : JS2_HEAD_LO 寄存器结构定义。地址偏移量:0x1900，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved    : 6;  /* bit[0-5] : Reserved. write as zero, read undefined. */
        unsigned int  js2_head_lo : 26; /* bit[6-31]: Job queue head pointer for job slot register：Contains the virtual address for the current job
                                                      descriptor */
    } reg;
} SOC_G3D_JS2_HEAD_LO_UNION;
#endif
#define SOC_G3D_JS2_HEAD_LO_js2_head_lo_START  (6)
#define SOC_G3D_JS2_HEAD_LO_js2_head_lo_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_JS2_HEAD_HI_UNION
 结构说明  : JS2_HEAD_HI 寄存器结构定义。地址偏移量:0x1904，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  js2_head_hi : 16; /* bit[0-15] : Job queue head pointer for job slot register：Contains the virtual address for the current job
                                                       descriptor */
        unsigned int  reserved    : 16; /* bit[16-31]: Reserved. write as zero, read undefined. */
    } reg;
} SOC_G3D_JS2_HEAD_HI_UNION;
#endif
#define SOC_G3D_JS2_HEAD_HI_js2_head_hi_START  (0)
#define SOC_G3D_JS2_HEAD_HI_js2_head_hi_END    (15)


/*****************************************************************************
 结构名    : SOC_G3D_JS2_TAIL_LO_UNION
 结构说明  : JS2_TAIL_LO 寄存器结构定义。地址偏移量:0x1908，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved    : 6;  /* bit[0-5] : Reserved. write as zero, read undefined. */
        unsigned int  js2_tail_lo : 26; /* bit[6-31]: Contains the virtual address of the oldest job that has
                                                      finished issuing tasks, but is still running. */
    } reg;
} SOC_G3D_JS2_TAIL_LO_UNION;
#endif
#define SOC_G3D_JS2_TAIL_LO_js2_tail_lo_START  (6)
#define SOC_G3D_JS2_TAIL_LO_js2_tail_lo_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_JS2_TAIL_HI_UNION
 结构说明  : JS2_TAIL_HI 寄存器结构定义。地址偏移量:0x190C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  js2_tail_hi : 16; /* bit[0-15] : Contains the virtual address of the oldest job that has
                                                       finished issuing tasks, but is still running. */
        unsigned int  reserved    : 16; /* bit[16-31]: Reserved. write as zero, read undefined. */
    } reg;
} SOC_G3D_JS2_TAIL_HI_UNION;
#endif
#define SOC_G3D_JS2_TAIL_HI_js2_tail_hi_START  (0)
#define SOC_G3D_JS2_TAIL_HI_js2_tail_hi_END    (15)


/*****************************************************************************
 结构名    : SOC_G3D_JS2_AFFINITY_LO_UNION
 结构说明  : JS2_AFFINITY_LO 寄存器结构定义。地址偏移量:0x1910，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  js2_affinity_lo : 32; /* bit[0-31]: Core affinity mask for job slot register */
    } reg;
} SOC_G3D_JS2_AFFINITY_LO_UNION;
#endif
#define SOC_G3D_JS2_AFFINITY_LO_js2_affinity_lo_START  (0)
#define SOC_G3D_JS2_AFFINITY_LO_js2_affinity_lo_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_JS2_AFFINITY_HI_UNION
 结构说明  : JS2_AFFINITY_HI 寄存器结构定义。地址偏移量:0x1914，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  js2_affinity_hi : 32; /* bit[0-31]: Core affinity mask register for job slot */
    } reg;
} SOC_G3D_JS2_AFFINITY_HI_UNION;
#endif
#define SOC_G3D_JS2_AFFINITY_HI_js2_affinity_hi_START  (0)
#define SOC_G3D_JS2_AFFINITY_HI_js2_affinity_hi_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_JS2_CONFIG_UNION
 结构说明  : JS2_CONFIG 寄存器结构定义。地址偏移量:0x1918，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  address_space : 4;  /* bit[0-3]  : Selects which of the address spaces to use for jobs in
                                                         this slot. The address space configuration values are
                                                         read from the ASn registers. */
        unsigned int  reserved_0    : 4;  /* bit[4-7]  : Reserved, write as zero, read undefined. */
        unsigned int  start_flush   : 2;  /* bit[8-9]  : Cache flush action on job chain start. Specifies what
                                                         action the caches must take before starting the job chain.
                                                         0 No flush
                                                         1 Clean
                                                         2 Reserved
                                                         3 Clean and invalidate.
                                                         The selected action applies to all caches except the tiler
                                                         cache. */
        unsigned int  start_mmu     : 1;  /* bit[10]   : MMU action on job chain start. Causes the Job Manager
                                                         to issue an MMU update before the job chain is started. */
        unsigned int  reserved_1    : 1;  /* bit[11]   : Reserved, write as zero, read undefined. */
        unsigned int  end_flush     : 2;  /* bit[12-13]: Cache flush action on job end chain. Specifies what
                                                         action the caches must take after finishing the job chain.
                                                         0 No flush
                                                         1 Clean
                                                         2 Reserved
                                                         3 Clean and invalidate.
                                                         The selected action applies to all caches including the
                                                         tiler cache. */
        unsigned int  reserved_2    : 18; /* bit[14-31]: Reserved, write as zero, read undefined. */
    } reg;
} SOC_G3D_JS2_CONFIG_UNION;
#endif
#define SOC_G3D_JS2_CONFIG_address_space_START  (0)
#define SOC_G3D_JS2_CONFIG_address_space_END    (3)
#define SOC_G3D_JS2_CONFIG_start_flush_START    (8)
#define SOC_G3D_JS2_CONFIG_start_flush_END      (9)
#define SOC_G3D_JS2_CONFIG_start_mmu_START      (10)
#define SOC_G3D_JS2_CONFIG_start_mmu_END        (10)
#define SOC_G3D_JS2_CONFIG_end_flush_START      (12)
#define SOC_G3D_JS2_CONFIG_end_flush_END        (13)


/*****************************************************************************
 结构名    : SOC_G3D_JS2_COMMAND_UNION
 结构说明  : JS2_COMMAND 寄存器结构定义。地址偏移量:0x1920，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  js2_command : 32; /* bit[0-31]: Command for job slot register */
    } reg;
} SOC_G3D_JS2_COMMAND_UNION;
#endif
#define SOC_G3D_JS2_COMMAND_js2_command_START  (0)
#define SOC_G3D_JS2_COMMAND_js2_command_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_JS2_STATUS_UNION
 结构说明  : JS2_STATUS 寄存器结构定义。地址偏移量:0x1924，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  js2_status : 32; /* bit[0-31]: Status for job slot register */
    } reg;
} SOC_G3D_JS2_STATUS_UNION;
#endif
#define SOC_G3D_JS2_STATUS_js2_status_START  (0)
#define SOC_G3D_JS2_STATUS_js2_status_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_JS2_HEAD_NEXT_LO_UNION
 结构说明  : JS2_HEAD_NEXT_LO 寄存器结构定义。地址偏移量:0x1940，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  js2_head_next_lo : 32; /* bit[0-31]: Next job queue head pointer for job slot register */
    } reg;
} SOC_G3D_JS2_HEAD_NEXT_LO_UNION;
#endif
#define SOC_G3D_JS2_HEAD_NEXT_LO_js2_head_next_lo_START  (0)
#define SOC_G3D_JS2_HEAD_NEXT_LO_js2_head_next_lo_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_JS2_HEAD_NEXT_HI_UNION
 结构说明  : JS2_HEAD_NEXT_HI 寄存器结构定义。地址偏移量:0x1944，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  js2_head_next_hi : 32; /* bit[0-31]: Next job queue head pointer for job slot register */
    } reg;
} SOC_G3D_JS2_HEAD_NEXT_HI_UNION;
#endif
#define SOC_G3D_JS2_HEAD_NEXT_HI_js2_head_next_hi_START  (0)
#define SOC_G3D_JS2_HEAD_NEXT_HI_js2_head_next_hi_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_JS2_AFFINITY_NEXT_LO_UNION
 结构说明  : JS2_AFFINITY_NEXT_LO 寄存器结构定义。地址偏移量:0x1950，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: Next core affinity mask for job slot register */
    } reg;
} SOC_G3D_JS2_AFFINITY_NEXT_LO_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_G3D_JS2_AFFINITY_NEXT_HI_UNION
 结构说明  : JS2_AFFINITY_NEXT_HI 寄存器结构定义。地址偏移量:0x1954，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: Next core affinity mask for job slot register */
    } reg;
} SOC_G3D_JS2_AFFINITY_NEXT_HI_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_G3D_JS2_CONFIG_NEXT_UNION
 结构说明  : JS2_CONFIG_NEXT 寄存器结构定义。地址偏移量:0x1958，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  address_space : 4;  /* bit[0-3]  : Selects which of the address spaces to use for jobs in
                                                         this slot. The address space configuration values are
                                                         read from the ASn registers. */
        unsigned int  reserved_0    : 4;  /* bit[4-7]  : Reserved, write as zero, read undefined. */
        unsigned int  start_flush   : 2;  /* bit[8-9]  : Cache flush action on job chain start. Specifies what
                                                         action the caches must take before starting the job chain.
                                                         0 No flush
                                                         1 Clean
                                                         2 Reserved
                                                         3 Clean and invalidate.
                                                         The selected action applies to all caches except the tiler
                                                         cache. */
        unsigned int  start_mmu     : 1;  /* bit[10]   : MMU action on job chain start. Causes the Job Manager
                                                         to issue an MMU update before the job chain is started. */
        unsigned int  reserved_1    : 1;  /* bit[11]   : Reserved, write as zero, read undefined. */
        unsigned int  end_flush     : 2;  /* bit[12-13]: Cache flush action on job end chain. Specifies what
                                                         action the caches must take after finishing the job chain.
                                                         0 No flush
                                                         1 Clean
                                                         2 Reserved
                                                         3 Clean and invalidate.
                                                         The selected action applies to all caches including the
                                                         tiler cache. */
        unsigned int  reserved_2    : 18; /* bit[14-31]: Next configuration setting for job slot register
                                                         The JSn_CONFIG_NEXT register is an identical register used to construct job chains one ahead
                                                         so maintaining throughput. The values in the register are loaded into the JSn_CONFIG register
                                                         when the current job chain completes */
    } reg;
} SOC_G3D_JS2_CONFIG_NEXT_UNION;
#endif
#define SOC_G3D_JS2_CONFIG_NEXT_address_space_START  (0)
#define SOC_G3D_JS2_CONFIG_NEXT_address_space_END    (3)
#define SOC_G3D_JS2_CONFIG_NEXT_start_flush_START    (8)
#define SOC_G3D_JS2_CONFIG_NEXT_start_flush_END      (9)
#define SOC_G3D_JS2_CONFIG_NEXT_start_mmu_START      (10)
#define SOC_G3D_JS2_CONFIG_NEXT_start_mmu_END        (10)
#define SOC_G3D_JS2_CONFIG_NEXT_end_flush_START      (12)
#define SOC_G3D_JS2_CONFIG_NEXT_end_flush_END        (13)


/*****************************************************************************
 结构名    : SOC_G3D_JS2_COMMAND_NEXT_UNION
 结构说明  : JS2_COMMAND_NEXT 寄存器结构定义。地址偏移量:0x1960，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: Next command for job slot register */
    } reg;
} SOC_G3D_JS2_COMMAND_NEXT_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_G3D_MMU_IRQ_RAWSTAT_UNION
 结构说明  : MMU_IRQ_RAWSTAT 寄存器结构定义。地址偏移量:0x2000，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  page_fault : 4;  /* bit[0-3]  : Page error for job slot n. */
        unsigned int  reserved_0 : 12; /* bit[4-15] : Reserved, write as zero, read undefined. */
        unsigned int  bus_error  : 4;  /* bit[16-19]: Bus error when reading page tables. */
        unsigned int  reserved_1 : 12; /* bit[20-31]: Raw interrupt status register:Reserved, write as zero, read undefined. */
    } reg;
} SOC_G3D_MMU_IRQ_RAWSTAT_UNION;
#endif
#define SOC_G3D_MMU_IRQ_RAWSTAT_page_fault_START  (0)
#define SOC_G3D_MMU_IRQ_RAWSTAT_page_fault_END    (3)
#define SOC_G3D_MMU_IRQ_RAWSTAT_bus_error_START   (16)
#define SOC_G3D_MMU_IRQ_RAWSTAT_bus_error_END     (19)


/*****************************************************************************
 结构名    : SOC_G3D_MMU_IRQ_CLEAR_UNION
 结构说明  : MMU_IRQ_CLEAR 寄存器结构定义。地址偏移量:0x2004，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  page_fault : 4;  /* bit[0-3]  : Writing a 1 to this register bit enables the
                                                      corresponding interrupt source. Writing a 0 to this
                                                      register bit disables the corresponding interrupt source. */
        unsigned int  reserved_0 : 12; /* bit[4-15] : Reserved, write as zero, read undefined */
        unsigned int  bus_error  : 4;  /* bit[16-19]: Writing a 1 to this register bit enables the
                                                      corresponding interrupt source. Writing a 0 to this
                                                      register bit disables the corresponding interrupt source. */
        unsigned int  reserved_1 : 12; /* bit[20-31]: Reserved, write as zero, read undefined */
    } reg;
} SOC_G3D_MMU_IRQ_CLEAR_UNION;
#endif
#define SOC_G3D_MMU_IRQ_CLEAR_page_fault_START  (0)
#define SOC_G3D_MMU_IRQ_CLEAR_page_fault_END    (3)
#define SOC_G3D_MMU_IRQ_CLEAR_bus_error_START   (16)
#define SOC_G3D_MMU_IRQ_CLEAR_bus_error_END     (19)


/*****************************************************************************
 结构名    : SOC_G3D_MMU_IRQ_MASK_UNION
 结构说明  : MMU_IRQ_MASK 寄存器结构定义。地址偏移量:0x2008，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  page_fault            : 8;  /* bit[0-7]  : Writing a 1 to this register bit enables the
                                                                 corresponding interrupt source. Writing a 0 to this
                                                                 register bit disables the corresponding interrupt source. */
        unsigned int  reserved              : 8;  /* bit[8-15] : reserved */
        unsigned int  bus_error             : 8;  /* bit[16-23]: Writing a 1 to this register bit enables the
                                                                 corresponding interrupt source. Writing a 0 to this
                                                                 register bit disables the corresponding interrupt source. */
        unsigned int  interruptmaskregister : 8;  /* bit[24-31]: interruptmaskregister */
    } reg;
} SOC_G3D_MMU_IRQ_MASK_UNION;
#endif
#define SOC_G3D_MMU_IRQ_MASK_page_fault_START             (0)
#define SOC_G3D_MMU_IRQ_MASK_page_fault_END               (7)
#define SOC_G3D_MMU_IRQ_MASK_bus_error_START              (16)
#define SOC_G3D_MMU_IRQ_MASK_bus_error_END                (23)
#define SOC_G3D_MMU_IRQ_MASK_interruptmaskregister_START  (24)
#define SOC_G3D_MMU_IRQ_MASK_interruptmaskregister_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_MMU_IRQ_STATUS_UNION
 结构说明  : MMU_IRQ_STATUS 寄存器结构定义。地址偏移量:0x200C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  page_fault     : 8;  /* bit[0-7]  : Writing a 1 to this register bit enables the
                                                          corresponding interrupt source. Writing a 0 to this
                                                          register bit disables the corresponding interrupt source. */
        unsigned int  reserved       : 8;  /* bit[8-15] : Reserved, write as zero, read undefined */
        unsigned int  bus_error      : 8;  /* bit[16-23]: Writing a 1 to this register bit enables the
                                                          corresponding interrupt source. Writing a 0 to this
                                                          register bit disables the corresponding interrupt source. */
        unsigned int  mmu_irq_status : 8;  /* bit[24-31]: Interrupt mask status register:Reserved, write as zero, read undefined */
    } reg;
} SOC_G3D_MMU_IRQ_STATUS_UNION;
#endif
#define SOC_G3D_MMU_IRQ_STATUS_page_fault_START      (0)
#define SOC_G3D_MMU_IRQ_STATUS_page_fault_END        (7)
#define SOC_G3D_MMU_IRQ_STATUS_bus_error_START       (16)
#define SOC_G3D_MMU_IRQ_STATUS_bus_error_END         (23)
#define SOC_G3D_MMU_IRQ_STATUS_mmu_irq_status_START  (24)
#define SOC_G3D_MMU_IRQ_STATUS_mmu_irq_status_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_AS0_TRANSTAB_LO_UNION
 结构说明  : AS0_TRANSTAB_LO 寄存器结构定义。地址偏移量:0x2400，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  transtab_adrmode    : 2;  /* bit[0-1]  : Address space mode can have the values shown in this
                                                               field. */
        unsigned int  transtab_read_inner : 1;  /* bit[2]    : Read allocation flag for inner coherence domain.
                                                               Sets the cache policy when reading items from the
                                                               translation table, for the inner coherence domain.
                                                               0 Do not allocate
                                                               1 Allocate */
        unsigned int  reserved_0          : 1;  /* bit[3]    : Reserved, write as zero, read undefined */
        unsigned int  share_out           : 1;  /* bit[4]    : Set the cache coherency policy when reading items
                                                               from the translation table. Indicates if accesses to the
                                                               outer coherency domain should be treated as shareable
                                                               or not.
                                                               1 Access is shareable
                                                               0 Access is not shareable */
        unsigned int  reserved_1          : 7;  /* bit[5-11] : Reserved, write as zero, read undefined */
        unsigned int  as0_transtab_lo     : 20; /* bit[12-31]: Translation table base address. The unused high bits
                                                               must be zero. */
    } reg;
} SOC_G3D_AS0_TRANSTAB_LO_UNION;
#endif
#define SOC_G3D_AS0_TRANSTAB_LO_transtab_adrmode_START     (0)
#define SOC_G3D_AS0_TRANSTAB_LO_transtab_adrmode_END       (1)
#define SOC_G3D_AS0_TRANSTAB_LO_transtab_read_inner_START  (2)
#define SOC_G3D_AS0_TRANSTAB_LO_transtab_read_inner_END    (2)
#define SOC_G3D_AS0_TRANSTAB_LO_share_out_START            (4)
#define SOC_G3D_AS0_TRANSTAB_LO_share_out_END              (4)
#define SOC_G3D_AS0_TRANSTAB_LO_as0_transtab_lo_START      (12)
#define SOC_G3D_AS0_TRANSTAB_LO_as0_transtab_lo_END        (31)


/*****************************************************************************
 结构名    : SOC_G3D_AS0_TRANSTAB_HI_UNION
 结构说明  : AS0_TRANSTAB_HI 寄存器结构定义。地址偏移量:0x2404，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  as0_transtab_hi : 8;  /* bit[0-7] : Translation table base address. The unused high bits
                                                          must be zero. */
        unsigned int  reserved        : 24; /* bit[8-31]: Translation table base address registers */
    } reg;
} SOC_G3D_AS0_TRANSTAB_HI_UNION;
#endif
#define SOC_G3D_AS0_TRANSTAB_HI_as0_transtab_hi_START  (0)
#define SOC_G3D_AS0_TRANSTAB_HI_as0_transtab_hi_END    (7)


/*****************************************************************************
 结构名    : SOC_G3D_AS0_MEMATTR_LO_UNION
 结构说明  : AS0_MEMATTR_LO 寄存器结构定义。地址偏移量:0x2408，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  as0_memattr_l3 : 8;  /* bit[0-7]  : Contains ATT attribute values for index 0 */
        unsigned int  as0_memattr_l2 : 8;  /* bit[8-15] : Contains ATT attribute values for index 1 */
        unsigned int  as0_memattr_l1 : 8;  /* bit[16-23]: Contains ATT attribute values for index 2 */
        unsigned int  as0_memattr_l0 : 8;  /* bit[24-31]: Contains ATT attribute values for index 3 */
    } reg;
} SOC_G3D_AS0_MEMATTR_LO_UNION;
#endif
#define SOC_G3D_AS0_MEMATTR_LO_as0_memattr_l3_START  (0)
#define SOC_G3D_AS0_MEMATTR_LO_as0_memattr_l3_END    (7)
#define SOC_G3D_AS0_MEMATTR_LO_as0_memattr_l2_START  (8)
#define SOC_G3D_AS0_MEMATTR_LO_as0_memattr_l2_END    (15)
#define SOC_G3D_AS0_MEMATTR_LO_as0_memattr_l1_START  (16)
#define SOC_G3D_AS0_MEMATTR_LO_as0_memattr_l1_END    (23)
#define SOC_G3D_AS0_MEMATTR_LO_as0_memattr_l0_START  (24)
#define SOC_G3D_AS0_MEMATTR_LO_as0_memattr_l0_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_AS0_MEMATTR_HI_UNION
 结构说明  : AS0_MEMATTR_HI 寄存器结构定义。地址偏移量:0x240C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  as0_memattr_h3 : 8;  /* bit[0-7]  : Contains ATT attribute values for index 4 */
        unsigned int  as0_memattr_h2 : 8;  /* bit[8-15] : Contains ATT attribute values for index 5 */
        unsigned int  as0_memattr_h1 : 8;  /* bit[16-23]: Contains ATT attribute values for index 6 */
        unsigned int  as0_memattr_h0 : 8;  /* bit[24-31]: Contains ATT attribute values for index 7 */
    } reg;
} SOC_G3D_AS0_MEMATTR_HI_UNION;
#endif
#define SOC_G3D_AS0_MEMATTR_HI_as0_memattr_h3_START  (0)
#define SOC_G3D_AS0_MEMATTR_HI_as0_memattr_h3_END    (7)
#define SOC_G3D_AS0_MEMATTR_HI_as0_memattr_h2_START  (8)
#define SOC_G3D_AS0_MEMATTR_HI_as0_memattr_h2_END    (15)
#define SOC_G3D_AS0_MEMATTR_HI_as0_memattr_h1_START  (16)
#define SOC_G3D_AS0_MEMATTR_HI_as0_memattr_h1_END    (23)
#define SOC_G3D_AS0_MEMATTR_HI_as0_memattr_h0_START  (24)
#define SOC_G3D_AS0_MEMATTR_HI_as0_memattr_h0_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_AS0_LOCKADDR_LO_UNION
 结构说明  : AS0_LOCKADDR_LO 寄存器结构定义。地址偏移量:0x2410，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lockaddr_size   : 6;  /* bit[0-5]  : Locked region size.
                                                           The region size field contains the log2 of the size of the
                                                           region to lock, minus 1. Only values in the range 11 to
                                                           63 are valid region sizes. Values in the range 0 to 10 are
                                                           undefined and must not be used. */
        unsigned int  reserved        : 6;  /* bit[6-11] : Reserved, write as zero, read undefined. */
        unsigned int  as0_lockaddr_l0 : 20; /* bit[12-31]: Lock region address for address space registers  */
    } reg;
} SOC_G3D_AS0_LOCKADDR_LO_UNION;
#endif
#define SOC_G3D_AS0_LOCKADDR_LO_lockaddr_size_START    (0)
#define SOC_G3D_AS0_LOCKADDR_LO_lockaddr_size_END      (5)
#define SOC_G3D_AS0_LOCKADDR_LO_as0_lockaddr_l0_START  (12)
#define SOC_G3D_AS0_LOCKADDR_LO_as0_lockaddr_l0_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_AS0_LOCKADDR_HI_UNION
 结构说明  : AS0_LOCKADDR_HI 寄存器结构定义。地址偏移量:0x2414，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  as0_lockaddr_hi : 16; /* bit[0-15] : The base address field contains the lowest address in the
                                                           region to be locked. The address is a virtual address in
                                                           this address space. Only the upper bits of the address are
                                                           used. */
        unsigned int  reserved        : 16; /* bit[16-31]: Lock region address for address space registers  */
    } reg;
} SOC_G3D_AS0_LOCKADDR_HI_UNION;
#endif
#define SOC_G3D_AS0_LOCKADDR_HI_as0_lockaddr_hi_START  (0)
#define SOC_G3D_AS0_LOCKADDR_HI_as0_lockaddr_hi_END    (15)


/*****************************************************************************
 结构名    : SOC_G3D_AS0_COMMAND_UNION
 结构说明  : AS0_COMMAND 寄存器结构定义。地址偏移量:0x2418，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  nop       : 1;  /* bit[0]   : No operation, nothing happens */
        unsigned int  update    : 1;  /* bit[1]   : Broadcast the values in ASn_TRANSTAB and
                                                    ASn_MEMATTR to all MMUs.
                                                    Use this after changing the content of these registers.
                                                    This also reverts the effect of a LOCK set in the updated
                                                    address space. */
        unsigned int  lock      : 1;  /* bit[2]   : Issue a lock region command to all MMUs, using the
                                                    address and size set in the ASn_LOCKADDR register.
                                                    Use this before changing an in-memory page table.
                                                    Use a FLUSH command to unlock a memory region. */
        unsigned int  unlock    : 1;  /* bit[3]   : Issue an unlock region command to all MMUs, using
                                                    the address and size set in the ASn_LOCKADDR
                                                    register.
                                                    Unlocking a region will also revert the effect of any
                                                    LOCKs.
                                                    Use this when finished changing an in-memory page
                                                    table, except if the page table can be cached in the L2
                                                    cache, in which case, a FLUSH_MEM command must
                                                    be issued instead. */
        unsigned int  flush_pt  : 1;  /* bit[4]   : First flush all Level 2 caches.
                                                    Then issue a flush region command to all MMUs, using
                                                    the address and size set in the ASn_LOCKADDR
                                                    register.
                                                    Unlocking a region also reverts the effect of any
                                                    LOCKs.
                                                    Use this when finished changing an in-memory page
                                                    table, except if the page table can be cached in the L2
                                                    cache, in which case, a FLUSH_MEM command must
                                                    be issued instead. */
        unsigned int  flush_mem : 1;  /* bit[5]   : Wait until all memory accesses to a region locked by a
                                                    preceding LOCK command have completed and have
                                                    reached the nearest cache.
                                                    Flush the L1 cache in all shader cores forcing dirty data
                                                    for locked regions to be pushed out to the L2 cache.
                                                    Then flush all L2 caches forcing all dirty data for locked
                                                    regions to be written back to memory and page tables to
                                                    be invalidated.
                                                    Then issue an unlock region command to all MMUs,
                                                    using the address and size set in the ASn_LOCKADDR
                                                    register.
                                                    Unlocking a region will also revert the effect of any
                                                    LOCKs.
                                                    Use this when finished changing or removing entries in
                                                    an in-memory page table. */
        unsigned int  reserved  : 26; /* bit[6-31]: Reserved, write as zero, read undefined. */
    } reg;
} SOC_G3D_AS0_COMMAND_UNION;
#endif
#define SOC_G3D_AS0_COMMAND_nop_START        (0)
#define SOC_G3D_AS0_COMMAND_nop_END          (0)
#define SOC_G3D_AS0_COMMAND_update_START     (1)
#define SOC_G3D_AS0_COMMAND_update_END       (1)
#define SOC_G3D_AS0_COMMAND_lock_START       (2)
#define SOC_G3D_AS0_COMMAND_lock_END         (2)
#define SOC_G3D_AS0_COMMAND_unlock_START     (3)
#define SOC_G3D_AS0_COMMAND_unlock_END       (3)
#define SOC_G3D_AS0_COMMAND_flush_pt_START   (4)
#define SOC_G3D_AS0_COMMAND_flush_pt_END     (4)
#define SOC_G3D_AS0_COMMAND_flush_mem_START  (5)
#define SOC_G3D_AS0_COMMAND_flush_mem_END    (5)


/*****************************************************************************
 结构名    : SOC_G3D_AS0_FAULTSTATUS_UNION
 结构说明  : AS0_FAULTSTATUS 寄存器结构定义。地址偏移量:0x241C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  exception_type : 8;  /* bit[0-7]  : Type of exception that caused the fault. */
        unsigned int  access_type    : 2;  /* bit[8-9]  : Access type that triggered the fault */
        unsigned int  reserved       : 6;  /* bit[10-15]: Reserved, write as zero, read undefined. */
        unsigned int  source_id      : 16; /* bit[16-31]: ID of source that triggered the fault */
    } reg;
} SOC_G3D_AS0_FAULTSTATUS_UNION;
#endif
#define SOC_G3D_AS0_FAULTSTATUS_exception_type_START  (0)
#define SOC_G3D_AS0_FAULTSTATUS_exception_type_END    (7)
#define SOC_G3D_AS0_FAULTSTATUS_access_type_START     (8)
#define SOC_G3D_AS0_FAULTSTATUS_access_type_END       (9)
#define SOC_G3D_AS0_FAULTSTATUS_source_id_START       (16)
#define SOC_G3D_AS0_FAULTSTATUS_source_id_END         (31)


/*****************************************************************************
 结构名    : SOC_G3D_AS0_FAULTADDRESS_LO_UNION
 结构说明  : AS0_FAULTADDRESS_LO 寄存器结构定义。地址偏移量:0x2420，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  as0_faultaddress_lo : 32; /* bit[0-31]: Fault address for address space registers  */
    } reg;
} SOC_G3D_AS0_FAULTADDRESS_LO_UNION;
#endif
#define SOC_G3D_AS0_FAULTADDRESS_LO_as0_faultaddress_lo_START  (0)
#define SOC_G3D_AS0_FAULTADDRESS_LO_as0_faultaddress_lo_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_AS0_FAULTADDRESS_HI_UNION
 结构说明  : AS0_FAULTADDRESS_HI 寄存器结构定义。地址偏移量:0x2424，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  as0_faultaddress_hi : 32; /* bit[0-31]: Fault address for address space registers  */
    } reg;
} SOC_G3D_AS0_FAULTADDRESS_HI_UNION;
#endif
#define SOC_G3D_AS0_FAULTADDRESS_HI_as0_faultaddress_hi_START  (0)
#define SOC_G3D_AS0_FAULTADDRESS_HI_as0_faultaddress_hi_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_AS0_STATUS_UNION
 结构说明  : AS0_STATUS 寄存器结构定义。地址偏移量:0x2428，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mmu_flush_active : 1;  /* bit[0]   : MMU flush command is active */
        unsigned int  reserved         : 31; /* bit[1-31]: Reserved, write as zero, read undefined */
    } reg;
} SOC_G3D_AS0_STATUS_UNION;
#endif
#define SOC_G3D_AS0_STATUS_mmu_flush_active_START  (0)
#define SOC_G3D_AS0_STATUS_mmu_flush_active_END    (0)


/*****************************************************************************
 结构名    : SOC_G3D_AS1_TRANSTAB_LO_UNION
 结构说明  : AS1_TRANSTAB_LO 寄存器结构定义。地址偏移量:0x2440，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  transtab_adrmode    : 2;  /* bit[0-1]  : Address space mode can have the values shown in this
                                                               field. */
        unsigned int  transtab_read_inner : 1;  /* bit[2]    : Read allocation flag for inner coherence domain.
                                                               Sets the cache policy when reading items from the
                                                               translation table, for the inner coherence domain.
                                                               0 Do not allocate
                                                               1 Allocate */
        unsigned int  reserved_0          : 1;  /* bit[3]    : Reserved, write as zero, read undefined */
        unsigned int  share_out           : 1;  /* bit[4]    : Set the cache coherency policy when reading items
                                                               from the translation table. Indicates if accesses to the
                                                               outer coherency domain should be treated as shareable
                                                               or not.
                                                               1 Access is shareable
                                                               0 Access is not shareable */
        unsigned int  reserved_1          : 7;  /* bit[5-11] : Reserved, write as zero, read undefined */
        unsigned int  as1_transtab_lo     : 20; /* bit[12-31]: Translation table base address. The unused high bits
                                                               must be zero. */
    } reg;
} SOC_G3D_AS1_TRANSTAB_LO_UNION;
#endif
#define SOC_G3D_AS1_TRANSTAB_LO_transtab_adrmode_START     (0)
#define SOC_G3D_AS1_TRANSTAB_LO_transtab_adrmode_END       (1)
#define SOC_G3D_AS1_TRANSTAB_LO_transtab_read_inner_START  (2)
#define SOC_G3D_AS1_TRANSTAB_LO_transtab_read_inner_END    (2)
#define SOC_G3D_AS1_TRANSTAB_LO_share_out_START            (4)
#define SOC_G3D_AS1_TRANSTAB_LO_share_out_END              (4)
#define SOC_G3D_AS1_TRANSTAB_LO_as1_transtab_lo_START      (12)
#define SOC_G3D_AS1_TRANSTAB_LO_as1_transtab_lo_END        (31)


/*****************************************************************************
 结构名    : SOC_G3D_AS1_TRANSTAB_HI_UNION
 结构说明  : AS1_TRANSTAB_HI 寄存器结构定义。地址偏移量:0x2444，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  as1_transtab_hi : 8;  /* bit[0-7] : Translation table base address. The unused high bits
                                                          must be zero. */
        unsigned int  reserved        : 24; /* bit[8-31]: Translation table base address registers */
    } reg;
} SOC_G3D_AS1_TRANSTAB_HI_UNION;
#endif
#define SOC_G3D_AS1_TRANSTAB_HI_as1_transtab_hi_START  (0)
#define SOC_G3D_AS1_TRANSTAB_HI_as1_transtab_hi_END    (7)


/*****************************************************************************
 结构名    : SOC_G3D_AS1_MEMATTR_LO_UNION
 结构说明  : AS1_MEMATTR_LO 寄存器结构定义。地址偏移量:0x2448，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  as1_memattr_l3 : 8;  /* bit[0-7]  : Contains ATT attribute values for index 0 */
        unsigned int  as1_memattr_l2 : 8;  /* bit[8-15] : Contains ATT attribute values for index 1 */
        unsigned int  as1_memattr_l1 : 8;  /* bit[16-23]: Contains ATT attribute values for index 2 */
        unsigned int  as1_memattr_l0 : 8;  /* bit[24-31]: Contains ATT attribute values for index 3 */
    } reg;
} SOC_G3D_AS1_MEMATTR_LO_UNION;
#endif
#define SOC_G3D_AS1_MEMATTR_LO_as1_memattr_l3_START  (0)
#define SOC_G3D_AS1_MEMATTR_LO_as1_memattr_l3_END    (7)
#define SOC_G3D_AS1_MEMATTR_LO_as1_memattr_l2_START  (8)
#define SOC_G3D_AS1_MEMATTR_LO_as1_memattr_l2_END    (15)
#define SOC_G3D_AS1_MEMATTR_LO_as1_memattr_l1_START  (16)
#define SOC_G3D_AS1_MEMATTR_LO_as1_memattr_l1_END    (23)
#define SOC_G3D_AS1_MEMATTR_LO_as1_memattr_l0_START  (24)
#define SOC_G3D_AS1_MEMATTR_LO_as1_memattr_l0_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_AS1_MEMATTR_HI_UNION
 结构说明  : AS1_MEMATTR_HI 寄存器结构定义。地址偏移量:0x244C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  as1_memattr_h3 : 8;  /* bit[0-7]  : Contains ATT attribute values for index 4 */
        unsigned int  as1_memattr_h2 : 8;  /* bit[8-15] : Contains ATT attribute values for index 5 */
        unsigned int  as1_memattr_h1 : 8;  /* bit[16-23]: Contains ATT attribute values for index 6 */
        unsigned int  as1_memattr_h0 : 8;  /* bit[24-31]: Contains ATT attribute values for index 7 */
    } reg;
} SOC_G3D_AS1_MEMATTR_HI_UNION;
#endif
#define SOC_G3D_AS1_MEMATTR_HI_as1_memattr_h3_START  (0)
#define SOC_G3D_AS1_MEMATTR_HI_as1_memattr_h3_END    (7)
#define SOC_G3D_AS1_MEMATTR_HI_as1_memattr_h2_START  (8)
#define SOC_G3D_AS1_MEMATTR_HI_as1_memattr_h2_END    (15)
#define SOC_G3D_AS1_MEMATTR_HI_as1_memattr_h1_START  (16)
#define SOC_G3D_AS1_MEMATTR_HI_as1_memattr_h1_END    (23)
#define SOC_G3D_AS1_MEMATTR_HI_as1_memattr_h0_START  (24)
#define SOC_G3D_AS1_MEMATTR_HI_as1_memattr_h0_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_AS1_LOCKADDR_LO_UNION
 结构说明  : AS1_LOCKADDR_LO 寄存器结构定义。地址偏移量:0x2450，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lockaddr_size   : 6;  /* bit[0-5]  : Locked region size.
                                                           The region size field contains the log2 of the size of the
                                                           region to lock, minus 1. Only values in the range 11 to
                                                           63 are valid region sizes. Values in the range 0 to 10 are
                                                           undefined and must not be used. */
        unsigned int  reserved        : 6;  /* bit[6-11] : Reserved, write as zero, read undefined. */
        unsigned int  as1_lockaddr_l0 : 20; /* bit[12-31]: Lock region address for address space registers  */
    } reg;
} SOC_G3D_AS1_LOCKADDR_LO_UNION;
#endif
#define SOC_G3D_AS1_LOCKADDR_LO_lockaddr_size_START    (0)
#define SOC_G3D_AS1_LOCKADDR_LO_lockaddr_size_END      (5)
#define SOC_G3D_AS1_LOCKADDR_LO_as1_lockaddr_l0_START  (12)
#define SOC_G3D_AS1_LOCKADDR_LO_as1_lockaddr_l0_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_AS1_LOCKADDR_HI_UNION
 结构说明  : AS1_LOCKADDR_HI 寄存器结构定义。地址偏移量:0x2454，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  as1_lockaddr_hi : 16; /* bit[0-15] : The base address field contains the lowest address in the
                                                           region to be locked. The address is a virtual address in
                                                           this address space. Only the upper bits of the address are
                                                           used. */
        unsigned int  reserved        : 16; /* bit[16-31]: Lock region address for address space registers  */
    } reg;
} SOC_G3D_AS1_LOCKADDR_HI_UNION;
#endif
#define SOC_G3D_AS1_LOCKADDR_HI_as1_lockaddr_hi_START  (0)
#define SOC_G3D_AS1_LOCKADDR_HI_as1_lockaddr_hi_END    (15)


/*****************************************************************************
 结构名    : SOC_G3D_AS1_COMMAND_UNION
 结构说明  : AS1_COMMAND 寄存器结构定义。地址偏移量:0x2458，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  nop       : 1;  /* bit[0]   : No operation, nothing happens */
        unsigned int  update    : 1;  /* bit[1]   : Broadcast the values in ASn_TRANSTAB and
                                                    ASn_MEMATTR to all MMUs.
                                                    Use this after changing the content of these registers.
                                                    This also reverts the effect of a LOCK set in the updated
                                                    address space. */
        unsigned int  lock      : 1;  /* bit[2]   : Issue a lock region command to all MMUs, using the
                                                    address and size set in the ASn_LOCKADDR register.
                                                    Use this before changing an in-memory page table.
                                                    Use a FLUSH command to unlock a memory region. */
        unsigned int  unlock    : 1;  /* bit[3]   : Issue an unlock region command to all MMUs, using
                                                    the address and size set in the ASn_LOCKADDR
                                                    register.
                                                    Unlocking a region will also revert the effect of any
                                                    LOCKs.
                                                    Use this when finished changing an in-memory page
                                                    table, except if the page table can be cached in the L2
                                                    cache, in which case, a FLUSH_MEM command must
                                                    be issued instead. */
        unsigned int  flush_pt  : 1;  /* bit[4]   : First flush all Level 2 caches.
                                                    Then issue a flush region command to all MMUs, using
                                                    the address and size set in the ASn_LOCKADDR
                                                    register.
                                                    Unlocking a region also reverts the effect of any
                                                    LOCKs.
                                                    Use this when finished changing an in-memory page
                                                    table, except if the page table can be cached in the L2
                                                    cache, in which case, a FLUSH_MEM command must
                                                    be issued instead. */
        unsigned int  flush_mem : 1;  /* bit[5]   : Wait until all memory accesses to a region locked by a
                                                    preceding LOCK command have completed and have
                                                    reached the nearest cache.
                                                    Flush the L1 cache in all shader cores forcing dirty data
                                                    for locked regions to be pushed out to the L2 cache.
                                                    Then flush all L2 caches forcing all dirty data for locked
                                                    regions to be written back to memory and page tables to
                                                    be invalidated.
                                                    Then issue an unlock region command to all MMUs,
                                                    using the address and size set in the ASn_LOCKADDR
                                                    register.
                                                    Unlocking a region will also revert the effect of any
                                                    LOCKs.
                                                    Use this when finished changing or removing entries in
                                                    an in-memory page table. */
        unsigned int  reserved  : 26; /* bit[6-31]: Reserved, write as zero, read undefined. */
    } reg;
} SOC_G3D_AS1_COMMAND_UNION;
#endif
#define SOC_G3D_AS1_COMMAND_nop_START        (0)
#define SOC_G3D_AS1_COMMAND_nop_END          (0)
#define SOC_G3D_AS1_COMMAND_update_START     (1)
#define SOC_G3D_AS1_COMMAND_update_END       (1)
#define SOC_G3D_AS1_COMMAND_lock_START       (2)
#define SOC_G3D_AS1_COMMAND_lock_END         (2)
#define SOC_G3D_AS1_COMMAND_unlock_START     (3)
#define SOC_G3D_AS1_COMMAND_unlock_END       (3)
#define SOC_G3D_AS1_COMMAND_flush_pt_START   (4)
#define SOC_G3D_AS1_COMMAND_flush_pt_END     (4)
#define SOC_G3D_AS1_COMMAND_flush_mem_START  (5)
#define SOC_G3D_AS1_COMMAND_flush_mem_END    (5)


/*****************************************************************************
 结构名    : SOC_G3D_AS1_FAULTSTATUS_UNION
 结构说明  : AS1_FAULTSTATUS 寄存器结构定义。地址偏移量:0x245C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  exception_type : 8;  /* bit[0-7]  : Type of exception that caused the fault. */
        unsigned int  access_type    : 2;  /* bit[8-9]  : Access type that triggered the fault */
        unsigned int  reserved       : 6;  /* bit[10-15]: Reserved, write as zero, read undefined. */
        unsigned int  source_id      : 16; /* bit[16-31]: ID of source that triggered the fault */
    } reg;
} SOC_G3D_AS1_FAULTSTATUS_UNION;
#endif
#define SOC_G3D_AS1_FAULTSTATUS_exception_type_START  (0)
#define SOC_G3D_AS1_FAULTSTATUS_exception_type_END    (7)
#define SOC_G3D_AS1_FAULTSTATUS_access_type_START     (8)
#define SOC_G3D_AS1_FAULTSTATUS_access_type_END       (9)
#define SOC_G3D_AS1_FAULTSTATUS_source_id_START       (16)
#define SOC_G3D_AS1_FAULTSTATUS_source_id_END         (31)


/*****************************************************************************
 结构名    : SOC_G3D_AS1_FAULTADDRESS_LO_UNION
 结构说明  : AS1_FAULTADDRESS_LO 寄存器结构定义。地址偏移量:0x2460，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  as1_faultaddress_lo : 32; /* bit[0-31]: Fault address for address space registers  */
    } reg;
} SOC_G3D_AS1_FAULTADDRESS_LO_UNION;
#endif
#define SOC_G3D_AS1_FAULTADDRESS_LO_as1_faultaddress_lo_START  (0)
#define SOC_G3D_AS1_FAULTADDRESS_LO_as1_faultaddress_lo_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_AS1_FAULTADDRESS_HI_UNION
 结构说明  : AS1_FAULTADDRESS_HI 寄存器结构定义。地址偏移量:0x2464，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  as0_faultaddress_hi : 32; /* bit[0-31]: Fault address for address space registers  */
    } reg;
} SOC_G3D_AS1_FAULTADDRESS_HI_UNION;
#endif
#define SOC_G3D_AS1_FAULTADDRESS_HI_as0_faultaddress_hi_START  (0)
#define SOC_G3D_AS1_FAULTADDRESS_HI_as0_faultaddress_hi_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_AS1_STATUS_UNION
 结构说明  : AS1_STATUS 寄存器结构定义。地址偏移量:0x2468，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mmu_flush_active : 1;  /* bit[0]   : MMU flush command is active
                                                           1:active
                                                           0:not active */
        unsigned int  reserved         : 31; /* bit[1-31]: Reserved, write as zero, read undefined */
    } reg;
} SOC_G3D_AS1_STATUS_UNION;
#endif
#define SOC_G3D_AS1_STATUS_mmu_flush_active_START  (0)
#define SOC_G3D_AS1_STATUS_mmu_flush_active_END    (0)


/*****************************************************************************
 结构名    : SOC_G3D_AS2_TRANSTAB_LO_UNION
 结构说明  : AS2_TRANSTAB_LO 寄存器结构定义。地址偏移量:0x2480，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  transtab_adrmode    : 2;  /* bit[0-1]  : Address space mode can have the values shown in this
                                                               field. */
        unsigned int  transtab_read_inner : 1;  /* bit[2]    : Read allocation flag for inner coherence domain.
                                                               Sets the cache policy when reading items from the
                                                               translation table, for the inner coherence domain.
                                                               0 Do not allocate
                                                               1 Allocate */
        unsigned int  reserved_0          : 1;  /* bit[3]    : Reserved, write as zero, read undefined */
        unsigned int  share_out           : 1;  /* bit[4]    : Set the cache coherency policy when reading items
                                                               from the translation table. Indicates if accesses to the
                                                               outer coherency domain should be treated as shareable
                                                               or not.
                                                               1 Access is shareable
                                                               0 Access is not shareable */
        unsigned int  reserved_1          : 7;  /* bit[5-11] : Reserved, write as zero, read undefined */
        unsigned int  as2_transtab_lo     : 20; /* bit[12-31]: Translation table base address. The unused high bits
                                                               must be zero. */
    } reg;
} SOC_G3D_AS2_TRANSTAB_LO_UNION;
#endif
#define SOC_G3D_AS2_TRANSTAB_LO_transtab_adrmode_START     (0)
#define SOC_G3D_AS2_TRANSTAB_LO_transtab_adrmode_END       (1)
#define SOC_G3D_AS2_TRANSTAB_LO_transtab_read_inner_START  (2)
#define SOC_G3D_AS2_TRANSTAB_LO_transtab_read_inner_END    (2)
#define SOC_G3D_AS2_TRANSTAB_LO_share_out_START            (4)
#define SOC_G3D_AS2_TRANSTAB_LO_share_out_END              (4)
#define SOC_G3D_AS2_TRANSTAB_LO_as2_transtab_lo_START      (12)
#define SOC_G3D_AS2_TRANSTAB_LO_as2_transtab_lo_END        (31)


/*****************************************************************************
 结构名    : SOC_G3D_AS2_TRANSTAB_HI_UNION
 结构说明  : AS2_TRANSTAB_HI 寄存器结构定义。地址偏移量:0x2484，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  as2_transtab_hi : 8;  /* bit[0-7] : Translation table base address. The unused high bits
                                                          must be zero. */
        unsigned int  reserved        : 24; /* bit[8-31]: Translation table base address registers */
    } reg;
} SOC_G3D_AS2_TRANSTAB_HI_UNION;
#endif
#define SOC_G3D_AS2_TRANSTAB_HI_as2_transtab_hi_START  (0)
#define SOC_G3D_AS2_TRANSTAB_HI_as2_transtab_hi_END    (7)


/*****************************************************************************
 结构名    : SOC_G3D_AS2_MEMATTR_LO_UNION
 结构说明  : AS2_MEMATTR_LO 寄存器结构定义。地址偏移量:0x2488，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  as2_memattr_l3 : 8;  /* bit[0-7]  : Contains ATT attribute values for index 0 */
        unsigned int  as2_memattr_l2 : 8;  /* bit[8-15] : Contains ATT attribute values for index 1 */
        unsigned int  as2_memattr_l1 : 8;  /* bit[16-23]: Contains ATT attribute values for index 2 */
        unsigned int  as2_memattr_l0 : 8;  /* bit[24-31]: Contains ATT attribute values for index 3 */
    } reg;
} SOC_G3D_AS2_MEMATTR_LO_UNION;
#endif
#define SOC_G3D_AS2_MEMATTR_LO_as2_memattr_l3_START  (0)
#define SOC_G3D_AS2_MEMATTR_LO_as2_memattr_l3_END    (7)
#define SOC_G3D_AS2_MEMATTR_LO_as2_memattr_l2_START  (8)
#define SOC_G3D_AS2_MEMATTR_LO_as2_memattr_l2_END    (15)
#define SOC_G3D_AS2_MEMATTR_LO_as2_memattr_l1_START  (16)
#define SOC_G3D_AS2_MEMATTR_LO_as2_memattr_l1_END    (23)
#define SOC_G3D_AS2_MEMATTR_LO_as2_memattr_l0_START  (24)
#define SOC_G3D_AS2_MEMATTR_LO_as2_memattr_l0_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_AS2_MEMATTR_HI_UNION
 结构说明  : AS2_MEMATTR_HI 寄存器结构定义。地址偏移量:0x248C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  as2_memattr_h3 : 8;  /* bit[0-7]  : Contains ATT attribute values for index 4 */
        unsigned int  as2_memattr_h2 : 8;  /* bit[8-15] : Contains ATT attribute values for index 5 */
        unsigned int  as2_memattr_h1 : 8;  /* bit[16-23]: Contains ATT attribute values for index 6 */
        unsigned int  as2_memattr_h0 : 8;  /* bit[24-31]: Contains ATT attribute values for index 7 */
    } reg;
} SOC_G3D_AS2_MEMATTR_HI_UNION;
#endif
#define SOC_G3D_AS2_MEMATTR_HI_as2_memattr_h3_START  (0)
#define SOC_G3D_AS2_MEMATTR_HI_as2_memattr_h3_END    (7)
#define SOC_G3D_AS2_MEMATTR_HI_as2_memattr_h2_START  (8)
#define SOC_G3D_AS2_MEMATTR_HI_as2_memattr_h2_END    (15)
#define SOC_G3D_AS2_MEMATTR_HI_as2_memattr_h1_START  (16)
#define SOC_G3D_AS2_MEMATTR_HI_as2_memattr_h1_END    (23)
#define SOC_G3D_AS2_MEMATTR_HI_as2_memattr_h0_START  (24)
#define SOC_G3D_AS2_MEMATTR_HI_as2_memattr_h0_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_AS2_LOCKADDR_LO_UNION
 结构说明  : AS2_LOCKADDR_LO 寄存器结构定义。地址偏移量:0x2490，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lockaddr_size   : 6;  /* bit[0-5]  : Locked region size.
                                                           The region size field contains the log2 of the size of the
                                                           region to lock, minus 1. Only values in the range 11 to
                                                           63 are valid region sizes. Values in the range 0 to 10 are
                                                           undefined and must not be used. */
        unsigned int  reserved        : 6;  /* bit[6-11] : Reserved, write as zero, read undefined. */
        unsigned int  as2_lockaddr_l0 : 20; /* bit[12-31]: Lock region address for address space registers  */
    } reg;
} SOC_G3D_AS2_LOCKADDR_LO_UNION;
#endif
#define SOC_G3D_AS2_LOCKADDR_LO_lockaddr_size_START    (0)
#define SOC_G3D_AS2_LOCKADDR_LO_lockaddr_size_END      (5)
#define SOC_G3D_AS2_LOCKADDR_LO_as2_lockaddr_l0_START  (12)
#define SOC_G3D_AS2_LOCKADDR_LO_as2_lockaddr_l0_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_AS2_LOCKADDR_HI_UNION
 结构说明  : AS2_LOCKADDR_HI 寄存器结构定义。地址偏移量:0x2494，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  as2_lockaddr_hi : 16; /* bit[0-15] : The base address field contains the lowest address in the
                                                           region to be locked. The address is a virtual address in
                                                           this address space. Only the upper bits of the address are
                                                           used. */
        unsigned int  reserved        : 16; /* bit[16-31]: Lock region address for address space registers  */
    } reg;
} SOC_G3D_AS2_LOCKADDR_HI_UNION;
#endif
#define SOC_G3D_AS2_LOCKADDR_HI_as2_lockaddr_hi_START  (0)
#define SOC_G3D_AS2_LOCKADDR_HI_as2_lockaddr_hi_END    (15)


/*****************************************************************************
 结构名    : SOC_G3D_AS2_COMMAND_UNION
 结构说明  : AS2_COMMAND 寄存器结构定义。地址偏移量:0x2498，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  nop       : 1;  /* bit[0]   : No operation, nothing happens */
        unsigned int  update    : 1;  /* bit[1]   : Broadcast the values in ASn_TRANSTAB and
                                                    ASn_MEMATTR to all MMUs.
                                                    Use this after changing the content of these registers.
                                                    This also reverts the effect of a LOCK set in the updated
                                                    address space. */
        unsigned int  lock      : 1;  /* bit[2]   : Issue a lock region command to all MMUs, using the
                                                    address and size set in the ASn_LOCKADDR register.
                                                    Use this before changing an in-memory page table.
                                                    Use a FLUSH command to unlock a memory region. */
        unsigned int  unlock    : 1;  /* bit[3]   : Issue an unlock region command to all MMUs, using
                                                    the address and size set in the ASn_LOCKADDR
                                                    register.
                                                    Unlocking a region will also revert the effect of any
                                                    LOCKs.
                                                    Use this when finished changing an in-memory page
                                                    table, except if the page table can be cached in the L2
                                                    cache, in which case, a FLUSH_MEM command must
                                                    be issued instead. */
        unsigned int  flush_pt  : 1;  /* bit[4]   : First flush all Level 2 caches.
                                                    Then issue a flush region command to all MMUs, using
                                                    the address and size set in the ASn_LOCKADDR
                                                    register.
                                                    Unlocking a region also reverts the effect of any
                                                    LOCKs.
                                                    Use this when finished changing an in-memory page
                                                    table, except if the page table can be cached in the L2
                                                    cache, in which case, a FLUSH_MEM command must
                                                    be issued instead. */
        unsigned int  flush_mem : 1;  /* bit[5]   : Wait until all memory accesses to a region locked by a
                                                    preceding LOCK command have completed and have
                                                    reached the nearest cache.
                                                    Flush the L1 cache in all shader cores forcing dirty data
                                                    for locked regions to be pushed out to the L2 cache.
                                                    Then flush all L2 caches forcing all dirty data for locked
                                                    regions to be written back to memory and page tables to
                                                    be invalidated.
                                                    Then issue an unlock region command to all MMUs,
                                                    using the address and size set in the ASn_LOCKADDR
                                                    register.
                                                    Unlocking a region will also revert the effect of any
                                                    LOCKs.
                                                    Use this when finished changing or removing entries in
                                                    an in-memory page table. */
        unsigned int  reserved  : 26; /* bit[6-31]: Reserved, write as zero, read undefined. */
    } reg;
} SOC_G3D_AS2_COMMAND_UNION;
#endif
#define SOC_G3D_AS2_COMMAND_nop_START        (0)
#define SOC_G3D_AS2_COMMAND_nop_END          (0)
#define SOC_G3D_AS2_COMMAND_update_START     (1)
#define SOC_G3D_AS2_COMMAND_update_END       (1)
#define SOC_G3D_AS2_COMMAND_lock_START       (2)
#define SOC_G3D_AS2_COMMAND_lock_END         (2)
#define SOC_G3D_AS2_COMMAND_unlock_START     (3)
#define SOC_G3D_AS2_COMMAND_unlock_END       (3)
#define SOC_G3D_AS2_COMMAND_flush_pt_START   (4)
#define SOC_G3D_AS2_COMMAND_flush_pt_END     (4)
#define SOC_G3D_AS2_COMMAND_flush_mem_START  (5)
#define SOC_G3D_AS2_COMMAND_flush_mem_END    (5)


/*****************************************************************************
 结构名    : SOC_G3D_AS2_FAULTSTATUS_UNION
 结构说明  : AS2_FAULTSTATUS 寄存器结构定义。地址偏移量:0x249C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  exception_type : 8;  /* bit[0-7]  : Type of exception that caused the fault. */
        unsigned int  access_type    : 2;  /* bit[8-9]  : Access type that triggered the fault */
        unsigned int  reserved       : 6;  /* bit[10-15]: Reserved, write as zero, read undefined. */
        unsigned int  source_id      : 16; /* bit[16-31]: ID of source that triggered the fault */
    } reg;
} SOC_G3D_AS2_FAULTSTATUS_UNION;
#endif
#define SOC_G3D_AS2_FAULTSTATUS_exception_type_START  (0)
#define SOC_G3D_AS2_FAULTSTATUS_exception_type_END    (7)
#define SOC_G3D_AS2_FAULTSTATUS_access_type_START     (8)
#define SOC_G3D_AS2_FAULTSTATUS_access_type_END       (9)
#define SOC_G3D_AS2_FAULTSTATUS_source_id_START       (16)
#define SOC_G3D_AS2_FAULTSTATUS_source_id_END         (31)


/*****************************************************************************
 结构名    : SOC_G3D_AS2_FAULTADDRESS_LO_UNION
 结构说明  : AS2_FAULTADDRESS_LO 寄存器结构定义。地址偏移量:0x24A0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  as2_faultaddress_lo : 32; /* bit[0-31]: Fault address for address space registers  */
    } reg;
} SOC_G3D_AS2_FAULTADDRESS_LO_UNION;
#endif
#define SOC_G3D_AS2_FAULTADDRESS_LO_as2_faultaddress_lo_START  (0)
#define SOC_G3D_AS2_FAULTADDRESS_LO_as2_faultaddress_lo_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_AS2_FAULTADDRESS_HI_UNION
 结构说明  : AS2_FAULTADDRESS_HI 寄存器结构定义。地址偏移量:0x24A4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  as2_faultaddress_hi : 32; /* bit[0-31]: Fault address for address space registers  */
    } reg;
} SOC_G3D_AS2_FAULTADDRESS_HI_UNION;
#endif
#define SOC_G3D_AS2_FAULTADDRESS_HI_as2_faultaddress_hi_START  (0)
#define SOC_G3D_AS2_FAULTADDRESS_HI_as2_faultaddress_hi_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_AS2_STATUS_UNION
 结构说明  : AS2_STATUS 寄存器结构定义。地址偏移量:0x24A8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mmu_flush_active : 1;  /* bit[0]   : MMU flush command is active */
        unsigned int  reserved         : 31; /* bit[1-31]: Reserved, write as zero, read undefined */
    } reg;
} SOC_G3D_AS2_STATUS_UNION;
#endif
#define SOC_G3D_AS2_STATUS_mmu_flush_active_START  (0)
#define SOC_G3D_AS2_STATUS_mmu_flush_active_END    (0)


/*****************************************************************************
 结构名    : SOC_G3D_AS3_TRANSTAB_LO_UNION
 结构说明  : AS3_TRANSTAB_LO 寄存器结构定义。地址偏移量:0x24C0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  transtab_adrmode    : 2;  /* bit[0-1]  : Address space mode can have the values shown in this
                                                               field. */
        unsigned int  transtab_read_inner : 1;  /* bit[2]    : Read allocation flag for inner coherence domain.
                                                               Sets the cache policy when reading items from the
                                                               translation table, for the inner coherence domain.
                                                               0 Do not allocate
                                                               1 Allocate */
        unsigned int  reserved_0          : 1;  /* bit[3]    : Reserved, write as zero, read undefined */
        unsigned int  share_out           : 1;  /* bit[4]    : Set the cache coherency policy when reading items
                                                               from the translation table. Indicates if accesses to the
                                                               outer coherency domain should be treated as shareable
                                                               or not.
                                                               1 Access is shareable
                                                               0 Access is not shareable */
        unsigned int  reserved_1          : 7;  /* bit[5-11] : Reserved, write as zero, read undefined */
        unsigned int  as3_transtab_lo     : 20; /* bit[12-31]: Translation table base address. The unused high bits
                                                               must be zero. */
    } reg;
} SOC_G3D_AS3_TRANSTAB_LO_UNION;
#endif
#define SOC_G3D_AS3_TRANSTAB_LO_transtab_adrmode_START     (0)
#define SOC_G3D_AS3_TRANSTAB_LO_transtab_adrmode_END       (1)
#define SOC_G3D_AS3_TRANSTAB_LO_transtab_read_inner_START  (2)
#define SOC_G3D_AS3_TRANSTAB_LO_transtab_read_inner_END    (2)
#define SOC_G3D_AS3_TRANSTAB_LO_share_out_START            (4)
#define SOC_G3D_AS3_TRANSTAB_LO_share_out_END              (4)
#define SOC_G3D_AS3_TRANSTAB_LO_as3_transtab_lo_START      (12)
#define SOC_G3D_AS3_TRANSTAB_LO_as3_transtab_lo_END        (31)


/*****************************************************************************
 结构名    : SOC_G3D_AS3_TRANSTAB_HI_UNION
 结构说明  : AS3_TRANSTAB_HI 寄存器结构定义。地址偏移量:0x24C4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  as3_transtab_hi : 8;  /* bit[0-7] : Translation table base address. The unused high bits
                                                          must be zero. */
        unsigned int  reserved        : 24; /* bit[8-31]: Translation table base address registers */
    } reg;
} SOC_G3D_AS3_TRANSTAB_HI_UNION;
#endif
#define SOC_G3D_AS3_TRANSTAB_HI_as3_transtab_hi_START  (0)
#define SOC_G3D_AS3_TRANSTAB_HI_as3_transtab_hi_END    (7)


/*****************************************************************************
 结构名    : SOC_G3D_AS3_MEMATTR_LO_UNION
 结构说明  : AS3_MEMATTR_LO 寄存器结构定义。地址偏移量:0x24C8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  as3_memattr_l3 : 8;  /* bit[0-7]  : Contains ATT attribute values for index 0 */
        unsigned int  as3_memattr_l2 : 8;  /* bit[8-15] : Contains ATT attribute values for index 1 */
        unsigned int  as3_memattr_l1 : 8;  /* bit[16-23]: Contains ATT attribute values for index 2 */
        unsigned int  as3_memattr_l0 : 8;  /* bit[24-31]: Contains ATT attribute values for index 3 */
    } reg;
} SOC_G3D_AS3_MEMATTR_LO_UNION;
#endif
#define SOC_G3D_AS3_MEMATTR_LO_as3_memattr_l3_START  (0)
#define SOC_G3D_AS3_MEMATTR_LO_as3_memattr_l3_END    (7)
#define SOC_G3D_AS3_MEMATTR_LO_as3_memattr_l2_START  (8)
#define SOC_G3D_AS3_MEMATTR_LO_as3_memattr_l2_END    (15)
#define SOC_G3D_AS3_MEMATTR_LO_as3_memattr_l1_START  (16)
#define SOC_G3D_AS3_MEMATTR_LO_as3_memattr_l1_END    (23)
#define SOC_G3D_AS3_MEMATTR_LO_as3_memattr_l0_START  (24)
#define SOC_G3D_AS3_MEMATTR_LO_as3_memattr_l0_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_AS3_MEMATTR_HI_UNION
 结构说明  : AS3_MEMATTR_HI 寄存器结构定义。地址偏移量:0x24CC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  as3_memattr_h3 : 8;  /* bit[0-7]  : Contains ATT attribute values for index 4 */
        unsigned int  as3_memattr_h2 : 8;  /* bit[8-15] : Contains ATT attribute values for index 5 */
        unsigned int  as3_memattr_h1 : 8;  /* bit[16-23]: Contains ATT attribute values for index 6 */
        unsigned int  as3_memattr_h0 : 8;  /* bit[24-31]: Contains ATT attribute values for index 7 */
    } reg;
} SOC_G3D_AS3_MEMATTR_HI_UNION;
#endif
#define SOC_G3D_AS3_MEMATTR_HI_as3_memattr_h3_START  (0)
#define SOC_G3D_AS3_MEMATTR_HI_as3_memattr_h3_END    (7)
#define SOC_G3D_AS3_MEMATTR_HI_as3_memattr_h2_START  (8)
#define SOC_G3D_AS3_MEMATTR_HI_as3_memattr_h2_END    (15)
#define SOC_G3D_AS3_MEMATTR_HI_as3_memattr_h1_START  (16)
#define SOC_G3D_AS3_MEMATTR_HI_as3_memattr_h1_END    (23)
#define SOC_G3D_AS3_MEMATTR_HI_as3_memattr_h0_START  (24)
#define SOC_G3D_AS3_MEMATTR_HI_as3_memattr_h0_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_AS3_LOCKADDR_LO_UNION
 结构说明  : AS3_LOCKADDR_LO 寄存器结构定义。地址偏移量:0x24D0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lockaddr_size   : 6;  /* bit[0-5]  : Locked region size.
                                                           The region size field contains the log2 of the size of the
                                                           region to lock, minus 1. Only values in the range 11 to
                                                           63 are valid region sizes. Values in the range 0 to 10 are
                                                           undefined and must not be used. */
        unsigned int  reserved        : 6;  /* bit[6-11] : Reserved, write as zero, read undefined. */
        unsigned int  as3_lockaddr_l0 : 20; /* bit[12-31]: Lock region address for address space registers  */
    } reg;
} SOC_G3D_AS3_LOCKADDR_LO_UNION;
#endif
#define SOC_G3D_AS3_LOCKADDR_LO_lockaddr_size_START    (0)
#define SOC_G3D_AS3_LOCKADDR_LO_lockaddr_size_END      (5)
#define SOC_G3D_AS3_LOCKADDR_LO_as3_lockaddr_l0_START  (12)
#define SOC_G3D_AS3_LOCKADDR_LO_as3_lockaddr_l0_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_AS3_LOCKADDR_HI_UNION
 结构说明  : AS3_LOCKADDR_HI 寄存器结构定义。地址偏移量:0x24D4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  as3_lockaddr_hi : 16; /* bit[0-15] : The base address field contains the lowest address in the
                                                           region to be locked. The address is a virtual address in
                                                           this address space. Only the upper bits of the address are
                                                           used. */
        unsigned int  reserved        : 16; /* bit[16-31]: Lock region address for address space registers  */
    } reg;
} SOC_G3D_AS3_LOCKADDR_HI_UNION;
#endif
#define SOC_G3D_AS3_LOCKADDR_HI_as3_lockaddr_hi_START  (0)
#define SOC_G3D_AS3_LOCKADDR_HI_as3_lockaddr_hi_END    (15)


/*****************************************************************************
 结构名    : SOC_G3D_AS3_COMMAND_UNION
 结构说明  : AS3_COMMAND 寄存器结构定义。地址偏移量:0x24D8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  nop       : 1;  /* bit[0]   : No operation, nothing happens */
        unsigned int  update    : 1;  /* bit[1]   : Broadcast the values in ASn_TRANSTAB and
                                                    ASn_MEMATTR to all MMUs.
                                                    Use this after changing the content of these registers.
                                                    This also reverts the effect of a LOCK set in the updated
                                                    address space. */
        unsigned int  lock      : 1;  /* bit[2]   : Issue a lock region command to all MMUs, using the
                                                    address and size set in the ASn_LOCKADDR register.
                                                    Use this before changing an in-memory page table.
                                                    Use a FLUSH command to unlock a memory region. */
        unsigned int  unlock    : 1;  /* bit[3]   : Issue an unlock region command to all MMUs, using
                                                    the address and size set in the ASn_LOCKADDR
                                                    register.
                                                    Unlocking a region will also revert the effect of any
                                                    LOCKs.
                                                    Use this when finished changing an in-memory page
                                                    table, except if the page table can be cached in the L2
                                                    cache, in which case, a FLUSH_MEM command must
                                                    be issued instead. */
        unsigned int  flush_pt  : 1;  /* bit[4]   : First flush all Level 2 caches.
                                                    Then issue a flush region command to all MMUs, using
                                                    the address and size set in the ASn_LOCKADDR
                                                    register.
                                                    Unlocking a region also reverts the effect of any
                                                    LOCKs.
                                                    Use this when finished changing an in-memory page
                                                    table, except if the page table can be cached in the L2
                                                    cache, in which case, a FLUSH_MEM command must
                                                    be issued instead. */
        unsigned int  flush_mem : 1;  /* bit[5]   : Wait until all memory accesses to a region locked by a
                                                    preceding LOCK command have completed and have
                                                    reached the nearest cache.
                                                    Flush the L1 cache in all shader cores forcing dirty data
                                                    for locked regions to be pushed out to the L2 cache.
                                                    Then flush all L2 caches forcing all dirty data for locked
                                                    regions to be written back to memory and page tables to
                                                    be invalidated.
                                                    Then issue an unlock region command to all MMUs,
                                                    using the address and size set in the ASn_LOCKADDR
                                                    register.
                                                    Unlocking a region will also revert the effect of any
                                                    LOCKs.
                                                    Use this when finished changing or removing entries in
                                                    an in-memory page table. */
        unsigned int  reserved  : 26; /* bit[6-31]: Reserved, write as zero, read undefined. */
    } reg;
} SOC_G3D_AS3_COMMAND_UNION;
#endif
#define SOC_G3D_AS3_COMMAND_nop_START        (0)
#define SOC_G3D_AS3_COMMAND_nop_END          (0)
#define SOC_G3D_AS3_COMMAND_update_START     (1)
#define SOC_G3D_AS3_COMMAND_update_END       (1)
#define SOC_G3D_AS3_COMMAND_lock_START       (2)
#define SOC_G3D_AS3_COMMAND_lock_END         (2)
#define SOC_G3D_AS3_COMMAND_unlock_START     (3)
#define SOC_G3D_AS3_COMMAND_unlock_END       (3)
#define SOC_G3D_AS3_COMMAND_flush_pt_START   (4)
#define SOC_G3D_AS3_COMMAND_flush_pt_END     (4)
#define SOC_G3D_AS3_COMMAND_flush_mem_START  (5)
#define SOC_G3D_AS3_COMMAND_flush_mem_END    (5)


/*****************************************************************************
 结构名    : SOC_G3D_AS3_FAULTSTATUS_UNION
 结构说明  : AS3_FAULTSTATUS 寄存器结构定义。地址偏移量:0x24DC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  exception_type : 8;  /* bit[0-7]  : Type of exception that caused the fault. */
        unsigned int  access_type    : 2;  /* bit[8-9]  : Access type that triggered the fault */
        unsigned int  reserved       : 6;  /* bit[10-15]: Reserved, write as zero, read undefined. */
        unsigned int  source_id      : 16; /* bit[16-31]: ID of source that triggered the fault */
    } reg;
} SOC_G3D_AS3_FAULTSTATUS_UNION;
#endif
#define SOC_G3D_AS3_FAULTSTATUS_exception_type_START  (0)
#define SOC_G3D_AS3_FAULTSTATUS_exception_type_END    (7)
#define SOC_G3D_AS3_FAULTSTATUS_access_type_START     (8)
#define SOC_G3D_AS3_FAULTSTATUS_access_type_END       (9)
#define SOC_G3D_AS3_FAULTSTATUS_source_id_START       (16)
#define SOC_G3D_AS3_FAULTSTATUS_source_id_END         (31)


/*****************************************************************************
 结构名    : SOC_G3D_AS3_FAULTADDRESS_LO_UNION
 结构说明  : AS3_FAULTADDRESS_LO 寄存器结构定义。地址偏移量:0x24E0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  as3_faultaddress_lo : 32; /* bit[0-31]: Fault address for address space registers  */
    } reg;
} SOC_G3D_AS3_FAULTADDRESS_LO_UNION;
#endif
#define SOC_G3D_AS3_FAULTADDRESS_LO_as3_faultaddress_lo_START  (0)
#define SOC_G3D_AS3_FAULTADDRESS_LO_as3_faultaddress_lo_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_AS3_FAULTADDRESS_HI_UNION
 结构说明  : AS3_FAULTADDRESS_HI 寄存器结构定义。地址偏移量:0x24E4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  as3_faultaddress_hi : 32; /* bit[0-31]: Fault address for address space registers  */
    } reg;
} SOC_G3D_AS3_FAULTADDRESS_HI_UNION;
#endif
#define SOC_G3D_AS3_FAULTADDRESS_HI_as3_faultaddress_hi_START  (0)
#define SOC_G3D_AS3_FAULTADDRESS_HI_as3_faultaddress_hi_END    (31)


/*****************************************************************************
 结构名    : SOC_G3D_AS3_STATUS_UNION
 结构说明  : AS3_STATUS 寄存器结构定义。地址偏移量:0x24E8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mmu_flush_active : 1;  /* bit[0]   : MMU flush command is active
                                                           1:active
                                                           0:not active */
        unsigned int  reserved         : 31; /* bit[1-31]: Reserved, write as zero, read undefined */
    } reg;
} SOC_G3D_AS3_STATUS_UNION;
#endif
#define SOC_G3D_AS3_STATUS_mmu_flush_active_START  (0)
#define SOC_G3D_AS3_STATUS_mmu_flush_active_END    (0)






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

#endif /* end of soc_g3d_interface.h */
