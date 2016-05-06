/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_isp_irq_merger_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-04-08 11:46:56
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年4月8日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_ISP_IRQ_MERGER.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_ISP_IRQ_MERGER_INTERFACE_H__
#define __SOC_ISP_IRQ_MERGER_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) IRQ_MERGER
 ****************************************************************************/
/* 寄存器说明：[Interrupt Mask Register] DEBUG register (bloc 0 over 3).
   位域定义UNION结构:  SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_UNION */
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_ADDR(base) ((base) + (0x0))

/* 寄存器说明：[Raw Interrupt Status Register] DEBUG register (bloc 0 over 3).
   位域定义UNION结构:  SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_UNION */
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_ADDR(base) ((base) + (0x4))

/* 寄存器说明：[Masked Interrupt Status Register] DEBUG register (bloc 0 over 3).
   位域定义UNION结构:  SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_UNION */
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_ADDR(base) ((base) + (0x8))

/* 寄存器说明：[Interrupt Clear Register] DEBUG register (bloc 0 over 3).
   位域定义UNION结构:  SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_UNION */
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_ADDR(base) ((base) + (0xC))

/* 寄存器说明：[Interrupt Set Register] DEBUG register (bloc 0 over 3).
   位域定义UNION结构:  SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_UNION */
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_ADDR(base) ((base) + (0x10))

/* 寄存器说明：[Interrupt Mask Register] DEBUG register (bloc 1 over 3).
   位域定义UNION结构:  SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_UNION */
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_ADDR(base) ((base) + (0x20))

/* 寄存器说明：[Raw Interrupt Status Register] DEBUG register (bloc 1 over 3).
   位域定义UNION结构:  SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_UNION */
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_ADDR(base) ((base) + (0x24))

/* 寄存器说明：[Masked Interrupt Status Register] DEBUG register (bloc 1 over 3).
   位域定义UNION结构:  SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_UNION */
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_ADDR(base) ((base) + (0x28))

/* 寄存器说明：[Interrupt Clear Register] DEBUG register (bloc 1 over 3).
   位域定义UNION结构:  SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_UNION */
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_ADDR(base) ((base) + (0x2C))

/* 寄存器说明：[Interrupt Set Register] DEBUG register (bloc 1 over 3).
   位域定义UNION结构:  SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_UNION */
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_ADDR(base) ((base) + (0x30))

/* 寄存器说明：[Interrupt Mask Register] DEBUG register (bloc 2 over 3).
   位域定义UNION结构:  SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_UNION */
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_ADDR(base) ((base) + (0x40))

/* 寄存器说明：[Raw Interrupt Status Register] DEBUG register (bloc 2 over 3).
   位域定义UNION结构:  SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_UNION */
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_ADDR(base) ((base) + (0x44))

/* 寄存器说明：[Masked Interrupt Status Register] DEBUG register (bloc 2 over 3).
   位域定义UNION结构:  SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_UNION */
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_ADDR(base) ((base) + (0x48))

/* 寄存器说明：[Interrupt Clear Register] DEBUG register (bloc 2 over 3).
   位域定义UNION结构:  SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_UNION */
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_ADDR(base) ((base) + (0x4C))

/* 寄存器说明：[Interrupt Set Register] DEBUG register (bloc 2 over 3).
   位域定义UNION结构:  SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_UNION */
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_ADDR(base) ((base) + (0x50))

/* 寄存器说明：[Interrupt Mask Register] DEBUG register (bloc 3 over 3).
   位域定义UNION结构:  SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_3_UNION */
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_3_ADDR(base) ((base) + (0x60))

/* 寄存器说明：[Raw Interrupt Status Register] DEBUG register (bloc 3 over 3).
   位域定义UNION结构:  SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_3_UNION */
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_3_ADDR(base) ((base) + (0x64))

/* 寄存器说明：[Masked Interrupt Status Register] DEBUG register (bloc 3 over 3).
   位域定义UNION结构:  SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_3_UNION */
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_3_ADDR(base) ((base) + (0x68))

/* 寄存器说明：[Interrupt Clear Register] DEBUG register (bloc 3 over 3).
   位域定义UNION结构:  SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_3_UNION */
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_3_ADDR(base) ((base) + (0x6C))

/* 寄存器说明：[Interrupt Set Register] DEBUG register (bloc 3 over 3).
   位域定义UNION结构:  SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_3_UNION */
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_3_ADDR(base) ((base) + (0x70))

/* 寄存器说明：[Interrupt Mask Register] ERROR register (bloc 0 over 1).
   位域定义UNION结构:  SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_UNION */
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_ADDR(base) ((base) + (0x80))

/* 寄存器说明：[Raw Interrupt Status Register] ERROR register (bloc 0 over 1).
   位域定义UNION结构:  SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_UNION */
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_ADDR(base) ((base) + (0x84))

/* 寄存器说明：[Masked Interrupt Status Register] ERROR register (bloc 0 over 1).
   位域定义UNION结构:  SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_UNION */
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_ADDR(base) ((base) + (0x88))

/* 寄存器说明：[Interrupt Clear Register] ERROR register (bloc 0 over 1).
   位域定义UNION结构:  SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_UNION */
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_ADDR(base) ((base) + (0x8C))

/* 寄存器说明：[Interrupt Set Register] ERROR register (bloc 0 over 1).
   位域定义UNION结构:  SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_UNION */
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_ADDR(base) ((base) + (0x90))

/* 寄存器说明：[Interrupt Mask Register] ERROR register (bloc 1 over 1).
   位域定义UNION结构:  SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_1_UNION */
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_1_ADDR(base) ((base) + (0xA0))

/* 寄存器说明：[Raw Interrupt Status Register] ERROR register (bloc 1 over 1).
   位域定义UNION结构:  SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_1_UNION */
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_1_ADDR(base) ((base) + (0xA4))

/* 寄存器说明：[Masked Interrupt Status Register] ERROR register (bloc 1 over 1).
   位域定义UNION结构:  SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_1_UNION */
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_1_ADDR(base) ((base) + (0xA8))

/* 寄存器说明：[Interrupt Clear Register] ERROR register (bloc 1 over 1).
   位域定义UNION结构:  SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_1_UNION */
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_1_ADDR(base) ((base) + (0xAC))

/* 寄存器说明：[Interrupt Set Register] ERROR register (bloc 1 over 1).
   位域定义UNION结构:  SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_1_UNION */
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_1_ADDR(base) ((base) + (0xB0))

/* 寄存器说明：[Interrupt Mask Register] FRPROC register (bloc 0 over 1).
   位域定义UNION结构:  SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_UNION */
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_ADDR(base) ((base) + (0xC0))

/* 寄存器说明：[Raw Interrupt Status Register] FRPROC register (bloc 0 over 1).
   位域定义UNION结构:  SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_UNION */
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_ADDR(base) ((base) + (0xC4))

/* 寄存器说明：[Masked Interrupt Status Register] FRPROC register (bloc 0 over 1).
   位域定义UNION结构:  SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_UNION */
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_ADDR(base) ((base) + (0xC8))

/* 寄存器说明：[Interrupt Clear Register] FRPROC register (bloc 0 over 1).
   位域定义UNION结构:  SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_UNION */
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_ADDR(base) ((base) + (0xCC))

/* 寄存器说明：[Interrupt Set Register] FRPROC register (bloc 0 over 1).
   位域定义UNION结构:  SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_UNION */
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_ADDR(base) ((base) + (0xD0))

/* 寄存器说明：[Interrupt Mask Register] FRPROC register (bloc 1 over 1).
   位域定义UNION结构:  SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_UNION */
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_ADDR(base) ((base) + (0xE0))

/* 寄存器说明：[Raw Interrupt Status Register] FRPROC register (bloc 1 over 1).
   位域定义UNION结构:  SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_UNION */
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_ADDR(base) ((base) + (0xE4))

/* 寄存器说明：[Masked Interrupt Status Register] FRPROC register (bloc 1 over 1).
   位域定义UNION结构:  SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_UNION */
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_ADDR(base) ((base) + (0xE8))

/* 寄存器说明：[Interrupt Clear Register] FRPROC register (bloc 1 over 1).
   位域定义UNION结构:  SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_UNION */
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_ADDR(base) ((base) + (0xEC))

/* 寄存器说明：[Interrupt Set Register] FRPROC register (bloc 1 over 1).
   位域定义UNION结构:  SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_UNION */
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_ADDR(base) ((base) + (0xF0))





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
                     (1/1) IRQ_MERGER
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_UNION
 结构说明  : IRQ_MERGER_IMSC_DEBUG_0 寄存器结构定义。地址偏移量:0x0，初值:0x00000000，宽度:32
 寄存器说明: [Interrupt Mask Register] DEBUG register (bloc 0 over 3).
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  otap_1_1__cvdr_rt__dropped_vpwr_0       : 1;  /* bit[0-0]  : source: OTAP_1_1 [31 over 104] NC */
        unsigned int  otap_1_1__cvdr_rt__sof_vpwr_0           : 1;  /* bit[1-1]  : source: OTAP_1_1 [30 over 104] NC */
        unsigned int  otap_1_2__cvdr_rt__dropped_vpwr_1       : 1;  /* bit[2-2]  : source: OTAP_1_2 [29 over 104] NC */
        unsigned int  otap_1_2__cvdr_rt__sof_vpwr_1           : 1;  /* bit[3-3]  : source: OTAP_1_2 [28 over 104] NC */
        unsigned int  scaler_3_y__cvdr_rt__dropped_vpwr_2     : 1;  /* bit[4-4]  : source: SCALER_3(Y) [27 over 104] NC */
        unsigned int  scaler_3_y__cvdr_rt__sof_vpwr_2         : 1;  /* bit[5-5]  : source: SCALER_3(Y) [26 over 104] NC */
        unsigned int  scaler_3_uv__cvdr_rt__dropped_vpwr_3    : 1;  /* bit[6-6]  : source: SCALER_3(UV) [25 over 104] NC */
        unsigned int  scaler_3_uv__cvdr_rt__sof_vpwr_3        : 1;  /* bit[7-7]  : source: SCALER_3(UV) [24 over 104] NC */
        unsigned int  scaler_2_1_y__cvdr_rt__dropped_vpwr_4   : 1;  /* bit[8-8]  : source: SCALER_2_1(Y) [23 over 104] NC */
        unsigned int  scaler_2_1_y__cvdr_rt__sof_vpwr_4       : 1;  /* bit[9-9]  : source: SCALER_2_1(Y) [22 over 104] NC */
        unsigned int  scaler_2_1_uv__cvdr_rt__dropped_vpwr_5  : 1;  /* bit[10-10]: source: SCALER_2_1(UV) [21 over 104] NC */
        unsigned int  scaler_2_1_uv__cvdr_rt__sof_vpwr_5      : 1;  /* bit[11-11]: source: SCALER_2_1(UV) [20 over 104] NC */
        unsigned int  scaler_2_2_y__cvdr_rt__dropped_vpwr_6   : 1;  /* bit[12-12]: source: SCALER_2_2(Y) [19 over 104] NC */
        unsigned int  scaler_2_2_y__cvdr_rt__sof_vpwr_6       : 1;  /* bit[13-13]: source: SCALER_2_2(Y) [18 over 104] NC */
        unsigned int  scaler_2_2_uv__cvdr_rt__dropped_vpwr_7  : 1;  /* bit[14-14]: source: SCALER_2_2(UV) [17 over 104] NC */
        unsigned int  scaler_2_2_uv__cvdr_rt__sof_vpwr_7      : 1;  /* bit[15-15]: source: SCALER_2_2(UV) [16 over 104] NC */
        unsigned int  scaler_1_1_y__cvdr_rt__dropped_vpwr_8   : 1;  /* bit[16-16]: source: SCALER_1_1(Y) [15 over 104] NC */
        unsigned int  scaler_1_1_y__cvdr_rt__sof_vpwr_8       : 1;  /* bit[17-17]: source: SCALER_1_1(Y) [14 over 104] NC */
        unsigned int  scaler_1_1_uv__cvdr_rt__dropped_vpwr_9  : 1;  /* bit[18-18]: source: SCALER_1_1(UV) [13 over 104] NC */
        unsigned int  scaler_1_1_uv__cvdr_rt__sof_vpwr_9      : 1;  /* bit[19-19]: source: SCALER_1_1(UV) [12 over 104] NC */
        unsigned int  scaler_1_2_y__cvdr_rt__dropped_vpwr_10  : 1;  /* bit[20-20]: source: SCALER_1_2(Y) [11 over 104] NC */
        unsigned int  scaler_1_2_y__cvdr_rt__sof_vpwr_10      : 1;  /* bit[21-21]: source: SCALER_1_2(Y) [10 over 104] NC */
        unsigned int  scaler_1_2_uv__cvdr_rt__dropped_vpwr_11 : 1;  /* bit[22-22]: source: SCALER_1_2(UV) [9 over 104] NC */
        unsigned int  scaler_1_2_uv__cvdr_rt__sof_vpwr_11     : 1;  /* bit[23-23]: source: SCALER_1_2(UV) [8 over 104] NC */
        unsigned int  fbcyuv_1__cvdr_rt__dropped_vpwr_12      : 1;  /* bit[24-24]: source: FBCYUV_1 [7 over 104] NC */
        unsigned int  fbcyuv_1__cvdr_rt__sof_vpwr_12          : 1;  /* bit[25-25]: source: FBCYUV_1 [6 over 104] NC */
        unsigned int  fbcyuv_1__cvdr_rt__eof_vpwr_12          : 1;  /* bit[26-26]: source: FBCYUV_1 [5 over 104] NC */
        unsigned int  isp_be_2__cvdr_rt__dropped_vpwr_13      : 1;  /* bit[27-27]: source: ISP_BE_2 [4 over 104] NC */
        unsigned int  isp_be_2__cvdr_rt__sof_vpwr_13          : 1;  /* bit[28-28]: source: ISP_BE_2 [3 over 104] NC */
        unsigned int  isp_be_2__cvdr_rt__eof_vpwr_13          : 1;  /* bit[29-29]: source: ISP_BE_2 [2 over 104] NC */
        unsigned int  otap_2_1__cvdr_rt__dropped_vpwr_14      : 1;  /* bit[30-30]: source: OTAP_2_1 [1 over 104] NC */
        unsigned int  otap_2_1__cvdr_rt__sof_vpwr_14          : 1;  /* bit[31-31]: source: OTAP_2_1 [0 over 104] NC */
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_otap_1_1__cvdr_rt__dropped_vpwr_0_START        (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_otap_1_1__cvdr_rt__dropped_vpwr_0_END          (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_otap_1_1__cvdr_rt__sof_vpwr_0_START            (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_otap_1_1__cvdr_rt__sof_vpwr_0_END              (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_otap_1_2__cvdr_rt__dropped_vpwr_1_START        (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_otap_1_2__cvdr_rt__dropped_vpwr_1_END          (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_otap_1_2__cvdr_rt__sof_vpwr_1_START            (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_otap_1_2__cvdr_rt__sof_vpwr_1_END              (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_3_y__cvdr_rt__dropped_vpwr_2_START      (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_3_y__cvdr_rt__dropped_vpwr_2_END        (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_3_y__cvdr_rt__sof_vpwr_2_START          (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_3_y__cvdr_rt__sof_vpwr_2_END            (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_3_uv__cvdr_rt__dropped_vpwr_3_START     (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_3_uv__cvdr_rt__dropped_vpwr_3_END       (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_3_uv__cvdr_rt__sof_vpwr_3_START         (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_3_uv__cvdr_rt__sof_vpwr_3_END           (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_2_1_y__cvdr_rt__dropped_vpwr_4_START    (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_2_1_y__cvdr_rt__dropped_vpwr_4_END      (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_2_1_y__cvdr_rt__sof_vpwr_4_START        (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_2_1_y__cvdr_rt__sof_vpwr_4_END          (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_2_1_uv__cvdr_rt__dropped_vpwr_5_START   (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_2_1_uv__cvdr_rt__dropped_vpwr_5_END     (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_2_1_uv__cvdr_rt__sof_vpwr_5_START       (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_2_1_uv__cvdr_rt__sof_vpwr_5_END         (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_2_2_y__cvdr_rt__dropped_vpwr_6_START    (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_2_2_y__cvdr_rt__dropped_vpwr_6_END      (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_2_2_y__cvdr_rt__sof_vpwr_6_START        (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_2_2_y__cvdr_rt__sof_vpwr_6_END          (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_2_2_uv__cvdr_rt__dropped_vpwr_7_START   (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_2_2_uv__cvdr_rt__dropped_vpwr_7_END     (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_2_2_uv__cvdr_rt__sof_vpwr_7_START       (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_2_2_uv__cvdr_rt__sof_vpwr_7_END         (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_1_1_y__cvdr_rt__dropped_vpwr_8_START    (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_1_1_y__cvdr_rt__dropped_vpwr_8_END      (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_1_1_y__cvdr_rt__sof_vpwr_8_START        (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_1_1_y__cvdr_rt__sof_vpwr_8_END          (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_1_1_uv__cvdr_rt__dropped_vpwr_9_START   (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_1_1_uv__cvdr_rt__dropped_vpwr_9_END     (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_1_1_uv__cvdr_rt__sof_vpwr_9_START       (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_1_1_uv__cvdr_rt__sof_vpwr_9_END         (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_1_2_y__cvdr_rt__dropped_vpwr_10_START   (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_1_2_y__cvdr_rt__dropped_vpwr_10_END     (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_1_2_y__cvdr_rt__sof_vpwr_10_START       (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_1_2_y__cvdr_rt__sof_vpwr_10_END         (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_1_2_uv__cvdr_rt__dropped_vpwr_11_START  (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_1_2_uv__cvdr_rt__dropped_vpwr_11_END    (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_1_2_uv__cvdr_rt__sof_vpwr_11_START      (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_scaler_1_2_uv__cvdr_rt__sof_vpwr_11_END        (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_fbcyuv_1__cvdr_rt__dropped_vpwr_12_START       (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_fbcyuv_1__cvdr_rt__dropped_vpwr_12_END         (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_fbcyuv_1__cvdr_rt__sof_vpwr_12_START           (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_fbcyuv_1__cvdr_rt__sof_vpwr_12_END             (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_fbcyuv_1__cvdr_rt__eof_vpwr_12_START           (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_fbcyuv_1__cvdr_rt__eof_vpwr_12_END             (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_isp_be_2__cvdr_rt__dropped_vpwr_13_START       (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_isp_be_2__cvdr_rt__dropped_vpwr_13_END         (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_isp_be_2__cvdr_rt__sof_vpwr_13_START           (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_isp_be_2__cvdr_rt__sof_vpwr_13_END             (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_isp_be_2__cvdr_rt__eof_vpwr_13_START           (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_isp_be_2__cvdr_rt__eof_vpwr_13_END             (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_otap_2_1__cvdr_rt__dropped_vpwr_14_START       (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_otap_2_1__cvdr_rt__dropped_vpwr_14_END         (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_otap_2_1__cvdr_rt__sof_vpwr_14_START           (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_0_otap_2_1__cvdr_rt__sof_vpwr_14_END             (31)


/*****************************************************************************
 结构名    : SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_UNION
 结构说明  : IRQ_MERGER_RIS_DEBUG_0 寄存器结构定义。地址偏移量:0x4，初值:0x00000000，宽度:32
 寄存器说明: [Raw Interrupt Status Register] DEBUG register (bloc 0 over 3).
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  otap_1_1__cvdr_rt__dropped_vpwr_0       : 1;  /* bit[0-0]  : source: OTAP_1_1 [31 over 104] NC */
        unsigned int  otap_1_1__cvdr_rt__sof_vpwr_0           : 1;  /* bit[1-1]  : source: OTAP_1_1 [30 over 104] NC */
        unsigned int  otap_1_2__cvdr_rt__dropped_vpwr_1       : 1;  /* bit[2-2]  : source: OTAP_1_2 [29 over 104] NC */
        unsigned int  otap_1_2__cvdr_rt__sof_vpwr_1           : 1;  /* bit[3-3]  : source: OTAP_1_2 [28 over 104] NC */
        unsigned int  scaler_3_y__cvdr_rt__dropped_vpwr_2     : 1;  /* bit[4-4]  : source: SCALER_3(Y) [27 over 104] NC */
        unsigned int  scaler_3_y__cvdr_rt__sof_vpwr_2         : 1;  /* bit[5-5]  : source: SCALER_3(Y) [26 over 104] NC */
        unsigned int  scaler_3_uv__cvdr_rt__dropped_vpwr_3    : 1;  /* bit[6-6]  : source: SCALER_3(UV) [25 over 104] NC */
        unsigned int  scaler_3_uv__cvdr_rt__sof_vpwr_3        : 1;  /* bit[7-7]  : source: SCALER_3(UV) [24 over 104] NC */
        unsigned int  scaler_2_1_y__cvdr_rt__dropped_vpwr_4   : 1;  /* bit[8-8]  : source: SCALER_2_1(Y) [23 over 104] NC */
        unsigned int  scaler_2_1_y__cvdr_rt__sof_vpwr_4       : 1;  /* bit[9-9]  : source: SCALER_2_1(Y) [22 over 104] NC */
        unsigned int  scaler_2_1_uv__cvdr_rt__dropped_vpwr_5  : 1;  /* bit[10-10]: source: SCALER_2_1(UV) [21 over 104] NC */
        unsigned int  scaler_2_1_uv__cvdr_rt__sof_vpwr_5      : 1;  /* bit[11-11]: source: SCALER_2_1(UV) [20 over 104] NC */
        unsigned int  scaler_2_2_y__cvdr_rt__dropped_vpwr_6   : 1;  /* bit[12-12]: source: SCALER_2_2(Y) [19 over 104] NC */
        unsigned int  scaler_2_2_y__cvdr_rt__sof_vpwr_6       : 1;  /* bit[13-13]: source: SCALER_2_2(Y) [18 over 104] NC */
        unsigned int  scaler_2_2_uv__cvdr_rt__dropped_vpwr_7  : 1;  /* bit[14-14]: source: SCALER_2_2(UV) [17 over 104] NC */
        unsigned int  scaler_2_2_uv__cvdr_rt__sof_vpwr_7      : 1;  /* bit[15-15]: source: SCALER_2_2(UV) [16 over 104] NC */
        unsigned int  scaler_1_1_y__cvdr_rt__dropped_vpwr_8   : 1;  /* bit[16-16]: source: SCALER_1_1(Y) [15 over 104] NC */
        unsigned int  scaler_1_1_y__cvdr_rt__sof_vpwr_8       : 1;  /* bit[17-17]: source: SCALER_1_1(Y) [14 over 104] NC */
        unsigned int  scaler_1_1_uv__cvdr_rt__dropped_vpwr_9  : 1;  /* bit[18-18]: source: SCALER_1_1(UV) [13 over 104] NC */
        unsigned int  scaler_1_1_uv__cvdr_rt__sof_vpwr_9      : 1;  /* bit[19-19]: source: SCALER_1_1(UV) [12 over 104] NC */
        unsigned int  scaler_1_2_y__cvdr_rt__dropped_vpwr_10  : 1;  /* bit[20-20]: source: SCALER_1_2(Y) [11 over 104] NC */
        unsigned int  scaler_1_2_y__cvdr_rt__sof_vpwr_10      : 1;  /* bit[21-21]: source: SCALER_1_2(Y) [10 over 104] NC */
        unsigned int  scaler_1_2_uv__cvdr_rt__dropped_vpwr_11 : 1;  /* bit[22-22]: source: SCALER_1_2(UV) [9 over 104] NC */
        unsigned int  scaler_1_2_uv__cvdr_rt__sof_vpwr_11     : 1;  /* bit[23-23]: source: SCALER_1_2(UV) [8 over 104] NC */
        unsigned int  fbcyuv_1__cvdr_rt__dropped_vpwr_12      : 1;  /* bit[24-24]: source: FBCYUV_1 [7 over 104] NC */
        unsigned int  fbcyuv_1__cvdr_rt__sof_vpwr_12          : 1;  /* bit[25-25]: source: FBCYUV_1 [6 over 104] NC */
        unsigned int  fbcyuv_1__cvdr_rt__eof_vpwr_12          : 1;  /* bit[26-26]: source: FBCYUV_1 [5 over 104] NC */
        unsigned int  isp_be_2__cvdr_rt__dropped_vpwr_13      : 1;  /* bit[27-27]: source: ISP_BE_2 [4 over 104] NC */
        unsigned int  isp_be_2__cvdr_rt__sof_vpwr_13          : 1;  /* bit[28-28]: source: ISP_BE_2 [3 over 104] NC */
        unsigned int  isp_be_2__cvdr_rt__eof_vpwr_13          : 1;  /* bit[29-29]: source: ISP_BE_2 [2 over 104] NC */
        unsigned int  otap_2_1__cvdr_rt__dropped_vpwr_14      : 1;  /* bit[30-30]: source: OTAP_2_1 [1 over 104] NC */
        unsigned int  otap_2_1__cvdr_rt__sof_vpwr_14          : 1;  /* bit[31-31]: source: OTAP_2_1 [0 over 104] NC */
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_otap_1_1__cvdr_rt__dropped_vpwr_0_START        (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_otap_1_1__cvdr_rt__dropped_vpwr_0_END          (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_otap_1_1__cvdr_rt__sof_vpwr_0_START            (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_otap_1_1__cvdr_rt__sof_vpwr_0_END              (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_otap_1_2__cvdr_rt__dropped_vpwr_1_START        (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_otap_1_2__cvdr_rt__dropped_vpwr_1_END          (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_otap_1_2__cvdr_rt__sof_vpwr_1_START            (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_otap_1_2__cvdr_rt__sof_vpwr_1_END              (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_3_y__cvdr_rt__dropped_vpwr_2_START      (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_3_y__cvdr_rt__dropped_vpwr_2_END        (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_3_y__cvdr_rt__sof_vpwr_2_START          (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_3_y__cvdr_rt__sof_vpwr_2_END            (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_3_uv__cvdr_rt__dropped_vpwr_3_START     (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_3_uv__cvdr_rt__dropped_vpwr_3_END       (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_3_uv__cvdr_rt__sof_vpwr_3_START         (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_3_uv__cvdr_rt__sof_vpwr_3_END           (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_2_1_y__cvdr_rt__dropped_vpwr_4_START    (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_2_1_y__cvdr_rt__dropped_vpwr_4_END      (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_2_1_y__cvdr_rt__sof_vpwr_4_START        (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_2_1_y__cvdr_rt__sof_vpwr_4_END          (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_2_1_uv__cvdr_rt__dropped_vpwr_5_START   (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_2_1_uv__cvdr_rt__dropped_vpwr_5_END     (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_2_1_uv__cvdr_rt__sof_vpwr_5_START       (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_2_1_uv__cvdr_rt__sof_vpwr_5_END         (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_2_2_y__cvdr_rt__dropped_vpwr_6_START    (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_2_2_y__cvdr_rt__dropped_vpwr_6_END      (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_2_2_y__cvdr_rt__sof_vpwr_6_START        (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_2_2_y__cvdr_rt__sof_vpwr_6_END          (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_2_2_uv__cvdr_rt__dropped_vpwr_7_START   (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_2_2_uv__cvdr_rt__dropped_vpwr_7_END     (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_2_2_uv__cvdr_rt__sof_vpwr_7_START       (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_2_2_uv__cvdr_rt__sof_vpwr_7_END         (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_1_1_y__cvdr_rt__dropped_vpwr_8_START    (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_1_1_y__cvdr_rt__dropped_vpwr_8_END      (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_1_1_y__cvdr_rt__sof_vpwr_8_START        (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_1_1_y__cvdr_rt__sof_vpwr_8_END          (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_1_1_uv__cvdr_rt__dropped_vpwr_9_START   (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_1_1_uv__cvdr_rt__dropped_vpwr_9_END     (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_1_1_uv__cvdr_rt__sof_vpwr_9_START       (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_1_1_uv__cvdr_rt__sof_vpwr_9_END         (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_1_2_y__cvdr_rt__dropped_vpwr_10_START   (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_1_2_y__cvdr_rt__dropped_vpwr_10_END     (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_1_2_y__cvdr_rt__sof_vpwr_10_START       (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_1_2_y__cvdr_rt__sof_vpwr_10_END         (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_1_2_uv__cvdr_rt__dropped_vpwr_11_START  (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_1_2_uv__cvdr_rt__dropped_vpwr_11_END    (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_1_2_uv__cvdr_rt__sof_vpwr_11_START      (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_scaler_1_2_uv__cvdr_rt__sof_vpwr_11_END        (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_fbcyuv_1__cvdr_rt__dropped_vpwr_12_START       (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_fbcyuv_1__cvdr_rt__dropped_vpwr_12_END         (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_fbcyuv_1__cvdr_rt__sof_vpwr_12_START           (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_fbcyuv_1__cvdr_rt__sof_vpwr_12_END             (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_fbcyuv_1__cvdr_rt__eof_vpwr_12_START           (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_fbcyuv_1__cvdr_rt__eof_vpwr_12_END             (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_isp_be_2__cvdr_rt__dropped_vpwr_13_START       (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_isp_be_2__cvdr_rt__dropped_vpwr_13_END         (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_isp_be_2__cvdr_rt__sof_vpwr_13_START           (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_isp_be_2__cvdr_rt__sof_vpwr_13_END             (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_isp_be_2__cvdr_rt__eof_vpwr_13_START           (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_isp_be_2__cvdr_rt__eof_vpwr_13_END             (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_otap_2_1__cvdr_rt__dropped_vpwr_14_START       (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_otap_2_1__cvdr_rt__dropped_vpwr_14_END         (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_otap_2_1__cvdr_rt__sof_vpwr_14_START           (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_0_otap_2_1__cvdr_rt__sof_vpwr_14_END             (31)


/*****************************************************************************
 结构名    : SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_UNION
 结构说明  : IRQ_MERGER_MIS_DEBUG_0 寄存器结构定义。地址偏移量:0x8，初值:0x00000000，宽度:32
 寄存器说明: [Masked Interrupt Status Register] DEBUG register (bloc 0 over 3).
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  otap_1_1__cvdr_rt__dropped_vpwr_0       : 1;  /* bit[0-0]  : source: OTAP_1_1 [31 over 104] NC */
        unsigned int  otap_1_1__cvdr_rt__sof_vpwr_0           : 1;  /* bit[1-1]  : source: OTAP_1_1 [30 over 104] NC */
        unsigned int  otap_1_2__cvdr_rt__dropped_vpwr_1       : 1;  /* bit[2-2]  : source: OTAP_1_2 [29 over 104] NC */
        unsigned int  otap_1_2__cvdr_rt__sof_vpwr_1           : 1;  /* bit[3-3]  : source: OTAP_1_2 [28 over 104] NC */
        unsigned int  scaler_3_y__cvdr_rt__dropped_vpwr_2     : 1;  /* bit[4-4]  : source: SCALER_3(Y) [27 over 104] NC */
        unsigned int  scaler_3_y__cvdr_rt__sof_vpwr_2         : 1;  /* bit[5-5]  : source: SCALER_3(Y) [26 over 104] NC */
        unsigned int  scaler_3_uv__cvdr_rt__dropped_vpwr_3    : 1;  /* bit[6-6]  : source: SCALER_3(UV) [25 over 104] NC */
        unsigned int  scaler_3_uv__cvdr_rt__sof_vpwr_3        : 1;  /* bit[7-7]  : source: SCALER_3(UV) [24 over 104] NC */
        unsigned int  scaler_2_1_y__cvdr_rt__dropped_vpwr_4   : 1;  /* bit[8-8]  : source: SCALER_2_1(Y) [23 over 104] NC */
        unsigned int  scaler_2_1_y__cvdr_rt__sof_vpwr_4       : 1;  /* bit[9-9]  : source: SCALER_2_1(Y) [22 over 104] NC */
        unsigned int  scaler_2_1_uv__cvdr_rt__dropped_vpwr_5  : 1;  /* bit[10-10]: source: SCALER_2_1(UV) [21 over 104] NC */
        unsigned int  scaler_2_1_uv__cvdr_rt__sof_vpwr_5      : 1;  /* bit[11-11]: source: SCALER_2_1(UV) [20 over 104] NC */
        unsigned int  scaler_2_2_y__cvdr_rt__dropped_vpwr_6   : 1;  /* bit[12-12]: source: SCALER_2_2(Y) [19 over 104] NC */
        unsigned int  scaler_2_2_y__cvdr_rt__sof_vpwr_6       : 1;  /* bit[13-13]: source: SCALER_2_2(Y) [18 over 104] NC */
        unsigned int  scaler_2_2_uv__cvdr_rt__dropped_vpwr_7  : 1;  /* bit[14-14]: source: SCALER_2_2(UV) [17 over 104] NC */
        unsigned int  scaler_2_2_uv__cvdr_rt__sof_vpwr_7      : 1;  /* bit[15-15]: source: SCALER_2_2(UV) [16 over 104] NC */
        unsigned int  scaler_1_1_y__cvdr_rt__dropped_vpwr_8   : 1;  /* bit[16-16]: source: SCALER_1_1(Y) [15 over 104] NC */
        unsigned int  scaler_1_1_y__cvdr_rt__sof_vpwr_8       : 1;  /* bit[17-17]: source: SCALER_1_1(Y) [14 over 104] NC */
        unsigned int  scaler_1_1_uv__cvdr_rt__dropped_vpwr_9  : 1;  /* bit[18-18]: source: SCALER_1_1(UV) [13 over 104] NC */
        unsigned int  scaler_1_1_uv__cvdr_rt__sof_vpwr_9      : 1;  /* bit[19-19]: source: SCALER_1_1(UV) [12 over 104] NC */
        unsigned int  scaler_1_2_y__cvdr_rt__dropped_vpwr_10  : 1;  /* bit[20-20]: source: SCALER_1_2(Y) [11 over 104] NC */
        unsigned int  scaler_1_2_y__cvdr_rt__sof_vpwr_10      : 1;  /* bit[21-21]: source: SCALER_1_2(Y) [10 over 104] NC */
        unsigned int  scaler_1_2_uv__cvdr_rt__dropped_vpwr_11 : 1;  /* bit[22-22]: source: SCALER_1_2(UV) [9 over 104] NC */
        unsigned int  scaler_1_2_uv__cvdr_rt__sof_vpwr_11     : 1;  /* bit[23-23]: source: SCALER_1_2(UV) [8 over 104] NC */
        unsigned int  fbcyuv_1__cvdr_rt__dropped_vpwr_12      : 1;  /* bit[24-24]: source: FBCYUV_1 [7 over 104] NC */
        unsigned int  fbcyuv_1__cvdr_rt__sof_vpwr_12          : 1;  /* bit[25-25]: source: FBCYUV_1 [6 over 104] NC */
        unsigned int  fbcyuv_1__cvdr_rt__eof_vpwr_12          : 1;  /* bit[26-26]: source: FBCYUV_1 [5 over 104] NC */
        unsigned int  isp_be_2__cvdr_rt__dropped_vpwr_13      : 1;  /* bit[27-27]: source: ISP_BE_2 [4 over 104] NC */
        unsigned int  isp_be_2__cvdr_rt__sof_vpwr_13          : 1;  /* bit[28-28]: source: ISP_BE_2 [3 over 104] NC */
        unsigned int  isp_be_2__cvdr_rt__eof_vpwr_13          : 1;  /* bit[29-29]: source: ISP_BE_2 [2 over 104] NC */
        unsigned int  otap_2_1__cvdr_rt__dropped_vpwr_14      : 1;  /* bit[30-30]: source: OTAP_2_1 [1 over 104] NC */
        unsigned int  otap_2_1__cvdr_rt__sof_vpwr_14          : 1;  /* bit[31-31]: source: OTAP_2_1 [0 over 104] NC */
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_otap_1_1__cvdr_rt__dropped_vpwr_0_START        (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_otap_1_1__cvdr_rt__dropped_vpwr_0_END          (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_otap_1_1__cvdr_rt__sof_vpwr_0_START            (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_otap_1_1__cvdr_rt__sof_vpwr_0_END              (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_otap_1_2__cvdr_rt__dropped_vpwr_1_START        (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_otap_1_2__cvdr_rt__dropped_vpwr_1_END          (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_otap_1_2__cvdr_rt__sof_vpwr_1_START            (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_otap_1_2__cvdr_rt__sof_vpwr_1_END              (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_3_y__cvdr_rt__dropped_vpwr_2_START      (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_3_y__cvdr_rt__dropped_vpwr_2_END        (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_3_y__cvdr_rt__sof_vpwr_2_START          (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_3_y__cvdr_rt__sof_vpwr_2_END            (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_3_uv__cvdr_rt__dropped_vpwr_3_START     (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_3_uv__cvdr_rt__dropped_vpwr_3_END       (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_3_uv__cvdr_rt__sof_vpwr_3_START         (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_3_uv__cvdr_rt__sof_vpwr_3_END           (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_2_1_y__cvdr_rt__dropped_vpwr_4_START    (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_2_1_y__cvdr_rt__dropped_vpwr_4_END      (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_2_1_y__cvdr_rt__sof_vpwr_4_START        (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_2_1_y__cvdr_rt__sof_vpwr_4_END          (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_2_1_uv__cvdr_rt__dropped_vpwr_5_START   (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_2_1_uv__cvdr_rt__dropped_vpwr_5_END     (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_2_1_uv__cvdr_rt__sof_vpwr_5_START       (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_2_1_uv__cvdr_rt__sof_vpwr_5_END         (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_2_2_y__cvdr_rt__dropped_vpwr_6_START    (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_2_2_y__cvdr_rt__dropped_vpwr_6_END      (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_2_2_y__cvdr_rt__sof_vpwr_6_START        (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_2_2_y__cvdr_rt__sof_vpwr_6_END          (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_2_2_uv__cvdr_rt__dropped_vpwr_7_START   (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_2_2_uv__cvdr_rt__dropped_vpwr_7_END     (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_2_2_uv__cvdr_rt__sof_vpwr_7_START       (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_2_2_uv__cvdr_rt__sof_vpwr_7_END         (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_1_1_y__cvdr_rt__dropped_vpwr_8_START    (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_1_1_y__cvdr_rt__dropped_vpwr_8_END      (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_1_1_y__cvdr_rt__sof_vpwr_8_START        (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_1_1_y__cvdr_rt__sof_vpwr_8_END          (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_1_1_uv__cvdr_rt__dropped_vpwr_9_START   (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_1_1_uv__cvdr_rt__dropped_vpwr_9_END     (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_1_1_uv__cvdr_rt__sof_vpwr_9_START       (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_1_1_uv__cvdr_rt__sof_vpwr_9_END         (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_1_2_y__cvdr_rt__dropped_vpwr_10_START   (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_1_2_y__cvdr_rt__dropped_vpwr_10_END     (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_1_2_y__cvdr_rt__sof_vpwr_10_START       (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_1_2_y__cvdr_rt__sof_vpwr_10_END         (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_1_2_uv__cvdr_rt__dropped_vpwr_11_START  (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_1_2_uv__cvdr_rt__dropped_vpwr_11_END    (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_1_2_uv__cvdr_rt__sof_vpwr_11_START      (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_scaler_1_2_uv__cvdr_rt__sof_vpwr_11_END        (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_fbcyuv_1__cvdr_rt__dropped_vpwr_12_START       (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_fbcyuv_1__cvdr_rt__dropped_vpwr_12_END         (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_fbcyuv_1__cvdr_rt__sof_vpwr_12_START           (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_fbcyuv_1__cvdr_rt__sof_vpwr_12_END             (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_fbcyuv_1__cvdr_rt__eof_vpwr_12_START           (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_fbcyuv_1__cvdr_rt__eof_vpwr_12_END             (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_isp_be_2__cvdr_rt__dropped_vpwr_13_START       (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_isp_be_2__cvdr_rt__dropped_vpwr_13_END         (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_isp_be_2__cvdr_rt__sof_vpwr_13_START           (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_isp_be_2__cvdr_rt__sof_vpwr_13_END             (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_isp_be_2__cvdr_rt__eof_vpwr_13_START           (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_isp_be_2__cvdr_rt__eof_vpwr_13_END             (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_otap_2_1__cvdr_rt__dropped_vpwr_14_START       (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_otap_2_1__cvdr_rt__dropped_vpwr_14_END         (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_otap_2_1__cvdr_rt__sof_vpwr_14_START           (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_0_otap_2_1__cvdr_rt__sof_vpwr_14_END             (31)


/*****************************************************************************
 结构名    : SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_UNION
 结构说明  : IRQ_MERGER_ICR_DEBUG_0 寄存器结构定义。地址偏移量:0xC，初值:0x00000000，宽度:32
 寄存器说明: [Interrupt Clear Register] DEBUG register (bloc 0 over 3).
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  otap_1_1__cvdr_rt__dropped_vpwr_0       : 1;  /* bit[0-0]  : source: OTAP_1_1 [31 over 104] NC */
        unsigned int  otap_1_1__cvdr_rt__sof_vpwr_0           : 1;  /* bit[1-1]  : source: OTAP_1_1 [30 over 104] NC */
        unsigned int  otap_1_2__cvdr_rt__dropped_vpwr_1       : 1;  /* bit[2-2]  : source: OTAP_1_2 [29 over 104] NC */
        unsigned int  otap_1_2__cvdr_rt__sof_vpwr_1           : 1;  /* bit[3-3]  : source: OTAP_1_2 [28 over 104] NC */
        unsigned int  scaler_3_y__cvdr_rt__dropped_vpwr_2     : 1;  /* bit[4-4]  : source: SCALER_3(Y) [27 over 104] NC */
        unsigned int  scaler_3_y__cvdr_rt__sof_vpwr_2         : 1;  /* bit[5-5]  : source: SCALER_3(Y) [26 over 104] NC */
        unsigned int  scaler_3_uv__cvdr_rt__dropped_vpwr_3    : 1;  /* bit[6-6]  : source: SCALER_3(UV) [25 over 104] NC */
        unsigned int  scaler_3_uv__cvdr_rt__sof_vpwr_3        : 1;  /* bit[7-7]  : source: SCALER_3(UV) [24 over 104] NC */
        unsigned int  scaler_2_1_y__cvdr_rt__dropped_vpwr_4   : 1;  /* bit[8-8]  : source: SCALER_2_1(Y) [23 over 104] NC */
        unsigned int  scaler_2_1_y__cvdr_rt__sof_vpwr_4       : 1;  /* bit[9-9]  : source: SCALER_2_1(Y) [22 over 104] NC */
        unsigned int  scaler_2_1_uv__cvdr_rt__dropped_vpwr_5  : 1;  /* bit[10-10]: source: SCALER_2_1(UV) [21 over 104] NC */
        unsigned int  scaler_2_1_uv__cvdr_rt__sof_vpwr_5      : 1;  /* bit[11-11]: source: SCALER_2_1(UV) [20 over 104] NC */
        unsigned int  scaler_2_2_y__cvdr_rt__dropped_vpwr_6   : 1;  /* bit[12-12]: source: SCALER_2_2(Y) [19 over 104] NC */
        unsigned int  scaler_2_2_y__cvdr_rt__sof_vpwr_6       : 1;  /* bit[13-13]: source: SCALER_2_2(Y) [18 over 104] NC */
        unsigned int  scaler_2_2_uv__cvdr_rt__dropped_vpwr_7  : 1;  /* bit[14-14]: source: SCALER_2_2(UV) [17 over 104] NC */
        unsigned int  scaler_2_2_uv__cvdr_rt__sof_vpwr_7      : 1;  /* bit[15-15]: source: SCALER_2_2(UV) [16 over 104] NC */
        unsigned int  scaler_1_1_y__cvdr_rt__dropped_vpwr_8   : 1;  /* bit[16-16]: source: SCALER_1_1(Y) [15 over 104] NC */
        unsigned int  scaler_1_1_y__cvdr_rt__sof_vpwr_8       : 1;  /* bit[17-17]: source: SCALER_1_1(Y) [14 over 104] NC */
        unsigned int  scaler_1_1_uv__cvdr_rt__dropped_vpwr_9  : 1;  /* bit[18-18]: source: SCALER_1_1(UV) [13 over 104] NC */
        unsigned int  scaler_1_1_uv__cvdr_rt__sof_vpwr_9      : 1;  /* bit[19-19]: source: SCALER_1_1(UV) [12 over 104] NC */
        unsigned int  scaler_1_2_y__cvdr_rt__dropped_vpwr_10  : 1;  /* bit[20-20]: source: SCALER_1_2(Y) [11 over 104] NC */
        unsigned int  scaler_1_2_y__cvdr_rt__sof_vpwr_10      : 1;  /* bit[21-21]: source: SCALER_1_2(Y) [10 over 104] NC */
        unsigned int  scaler_1_2_uv__cvdr_rt__dropped_vpwr_11 : 1;  /* bit[22-22]: source: SCALER_1_2(UV) [9 over 104] NC */
        unsigned int  scaler_1_2_uv__cvdr_rt__sof_vpwr_11     : 1;  /* bit[23-23]: source: SCALER_1_2(UV) [8 over 104] NC */
        unsigned int  fbcyuv_1__cvdr_rt__dropped_vpwr_12      : 1;  /* bit[24-24]: source: FBCYUV_1 [7 over 104] NC */
        unsigned int  fbcyuv_1__cvdr_rt__sof_vpwr_12          : 1;  /* bit[25-25]: source: FBCYUV_1 [6 over 104] NC */
        unsigned int  fbcyuv_1__cvdr_rt__eof_vpwr_12          : 1;  /* bit[26-26]: source: FBCYUV_1 [5 over 104] NC */
        unsigned int  isp_be_2__cvdr_rt__dropped_vpwr_13      : 1;  /* bit[27-27]: source: ISP_BE_2 [4 over 104] NC */
        unsigned int  isp_be_2__cvdr_rt__sof_vpwr_13          : 1;  /* bit[28-28]: source: ISP_BE_2 [3 over 104] NC */
        unsigned int  isp_be_2__cvdr_rt__eof_vpwr_13          : 1;  /* bit[29-29]: source: ISP_BE_2 [2 over 104] NC */
        unsigned int  otap_2_1__cvdr_rt__dropped_vpwr_14      : 1;  /* bit[30-30]: source: OTAP_2_1 [1 over 104] NC */
        unsigned int  otap_2_1__cvdr_rt__sof_vpwr_14          : 1;  /* bit[31-31]: source: OTAP_2_1 [0 over 104] NC */
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_otap_1_1__cvdr_rt__dropped_vpwr_0_START        (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_otap_1_1__cvdr_rt__dropped_vpwr_0_END          (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_otap_1_1__cvdr_rt__sof_vpwr_0_START            (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_otap_1_1__cvdr_rt__sof_vpwr_0_END              (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_otap_1_2__cvdr_rt__dropped_vpwr_1_START        (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_otap_1_2__cvdr_rt__dropped_vpwr_1_END          (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_otap_1_2__cvdr_rt__sof_vpwr_1_START            (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_otap_1_2__cvdr_rt__sof_vpwr_1_END              (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_3_y__cvdr_rt__dropped_vpwr_2_START      (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_3_y__cvdr_rt__dropped_vpwr_2_END        (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_3_y__cvdr_rt__sof_vpwr_2_START          (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_3_y__cvdr_rt__sof_vpwr_2_END            (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_3_uv__cvdr_rt__dropped_vpwr_3_START     (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_3_uv__cvdr_rt__dropped_vpwr_3_END       (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_3_uv__cvdr_rt__sof_vpwr_3_START         (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_3_uv__cvdr_rt__sof_vpwr_3_END           (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_2_1_y__cvdr_rt__dropped_vpwr_4_START    (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_2_1_y__cvdr_rt__dropped_vpwr_4_END      (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_2_1_y__cvdr_rt__sof_vpwr_4_START        (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_2_1_y__cvdr_rt__sof_vpwr_4_END          (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_2_1_uv__cvdr_rt__dropped_vpwr_5_START   (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_2_1_uv__cvdr_rt__dropped_vpwr_5_END     (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_2_1_uv__cvdr_rt__sof_vpwr_5_START       (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_2_1_uv__cvdr_rt__sof_vpwr_5_END         (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_2_2_y__cvdr_rt__dropped_vpwr_6_START    (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_2_2_y__cvdr_rt__dropped_vpwr_6_END      (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_2_2_y__cvdr_rt__sof_vpwr_6_START        (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_2_2_y__cvdr_rt__sof_vpwr_6_END          (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_2_2_uv__cvdr_rt__dropped_vpwr_7_START   (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_2_2_uv__cvdr_rt__dropped_vpwr_7_END     (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_2_2_uv__cvdr_rt__sof_vpwr_7_START       (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_2_2_uv__cvdr_rt__sof_vpwr_7_END         (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_1_1_y__cvdr_rt__dropped_vpwr_8_START    (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_1_1_y__cvdr_rt__dropped_vpwr_8_END      (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_1_1_y__cvdr_rt__sof_vpwr_8_START        (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_1_1_y__cvdr_rt__sof_vpwr_8_END          (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_1_1_uv__cvdr_rt__dropped_vpwr_9_START   (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_1_1_uv__cvdr_rt__dropped_vpwr_9_END     (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_1_1_uv__cvdr_rt__sof_vpwr_9_START       (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_1_1_uv__cvdr_rt__sof_vpwr_9_END         (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_1_2_y__cvdr_rt__dropped_vpwr_10_START   (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_1_2_y__cvdr_rt__dropped_vpwr_10_END     (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_1_2_y__cvdr_rt__sof_vpwr_10_START       (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_1_2_y__cvdr_rt__sof_vpwr_10_END         (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_1_2_uv__cvdr_rt__dropped_vpwr_11_START  (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_1_2_uv__cvdr_rt__dropped_vpwr_11_END    (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_1_2_uv__cvdr_rt__sof_vpwr_11_START      (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_scaler_1_2_uv__cvdr_rt__sof_vpwr_11_END        (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_fbcyuv_1__cvdr_rt__dropped_vpwr_12_START       (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_fbcyuv_1__cvdr_rt__dropped_vpwr_12_END         (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_fbcyuv_1__cvdr_rt__sof_vpwr_12_START           (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_fbcyuv_1__cvdr_rt__sof_vpwr_12_END             (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_fbcyuv_1__cvdr_rt__eof_vpwr_12_START           (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_fbcyuv_1__cvdr_rt__eof_vpwr_12_END             (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_isp_be_2__cvdr_rt__dropped_vpwr_13_START       (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_isp_be_2__cvdr_rt__dropped_vpwr_13_END         (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_isp_be_2__cvdr_rt__sof_vpwr_13_START           (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_isp_be_2__cvdr_rt__sof_vpwr_13_END             (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_isp_be_2__cvdr_rt__eof_vpwr_13_START           (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_isp_be_2__cvdr_rt__eof_vpwr_13_END             (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_otap_2_1__cvdr_rt__dropped_vpwr_14_START       (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_otap_2_1__cvdr_rt__dropped_vpwr_14_END         (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_otap_2_1__cvdr_rt__sof_vpwr_14_START           (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_0_otap_2_1__cvdr_rt__sof_vpwr_14_END             (31)


/*****************************************************************************
 结构名    : SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_UNION
 结构说明  : IRQ_MERGER_ISR_DEBUG_0 寄存器结构定义。地址偏移量:0x10，初值:0x00000000，宽度:32
 寄存器说明: [Interrupt Set Register] DEBUG register (bloc 0 over 3).
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  otap_1_1__cvdr_rt__dropped_vpwr_0       : 1;  /* bit[0-0]  : source: OTAP_1_1 [31 over 104] NC */
        unsigned int  otap_1_1__cvdr_rt__sof_vpwr_0           : 1;  /* bit[1-1]  : source: OTAP_1_1 [30 over 104] NC */
        unsigned int  otap_1_2__cvdr_rt__dropped_vpwr_1       : 1;  /* bit[2-2]  : source: OTAP_1_2 [29 over 104] NC */
        unsigned int  otap_1_2__cvdr_rt__sof_vpwr_1           : 1;  /* bit[3-3]  : source: OTAP_1_2 [28 over 104] NC */
        unsigned int  scaler_3_y__cvdr_rt__dropped_vpwr_2     : 1;  /* bit[4-4]  : source: SCALER_3(Y) [27 over 104] NC */
        unsigned int  scaler_3_y__cvdr_rt__sof_vpwr_2         : 1;  /* bit[5-5]  : source: SCALER_3(Y) [26 over 104] NC */
        unsigned int  scaler_3_uv__cvdr_rt__dropped_vpwr_3    : 1;  /* bit[6-6]  : source: SCALER_3(UV) [25 over 104] NC */
        unsigned int  scaler_3_uv__cvdr_rt__sof_vpwr_3        : 1;  /* bit[7-7]  : source: SCALER_3(UV) [24 over 104] NC */
        unsigned int  scaler_2_1_y__cvdr_rt__dropped_vpwr_4   : 1;  /* bit[8-8]  : source: SCALER_2_1(Y) [23 over 104] NC */
        unsigned int  scaler_2_1_y__cvdr_rt__sof_vpwr_4       : 1;  /* bit[9-9]  : source: SCALER_2_1(Y) [22 over 104] NC */
        unsigned int  scaler_2_1_uv__cvdr_rt__dropped_vpwr_5  : 1;  /* bit[10-10]: source: SCALER_2_1(UV) [21 over 104] NC */
        unsigned int  scaler_2_1_uv__cvdr_rt__sof_vpwr_5      : 1;  /* bit[11-11]: source: SCALER_2_1(UV) [20 over 104] NC */
        unsigned int  scaler_2_2_y__cvdr_rt__dropped_vpwr_6   : 1;  /* bit[12-12]: source: SCALER_2_2(Y) [19 over 104] NC */
        unsigned int  scaler_2_2_y__cvdr_rt__sof_vpwr_6       : 1;  /* bit[13-13]: source: SCALER_2_2(Y) [18 over 104] NC */
        unsigned int  scaler_2_2_uv__cvdr_rt__dropped_vpwr_7  : 1;  /* bit[14-14]: source: SCALER_2_2(UV) [17 over 104] NC */
        unsigned int  scaler_2_2_uv__cvdr_rt__sof_vpwr_7      : 1;  /* bit[15-15]: source: SCALER_2_2(UV) [16 over 104] NC */
        unsigned int  scaler_1_1_y__cvdr_rt__dropped_vpwr_8   : 1;  /* bit[16-16]: source: SCALER_1_1(Y) [15 over 104] NC */
        unsigned int  scaler_1_1_y__cvdr_rt__sof_vpwr_8       : 1;  /* bit[17-17]: source: SCALER_1_1(Y) [14 over 104] NC */
        unsigned int  scaler_1_1_uv__cvdr_rt__dropped_vpwr_9  : 1;  /* bit[18-18]: source: SCALER_1_1(UV) [13 over 104] NC */
        unsigned int  scaler_1_1_uv__cvdr_rt__sof_vpwr_9      : 1;  /* bit[19-19]: source: SCALER_1_1(UV) [12 over 104] NC */
        unsigned int  scaler_1_2_y__cvdr_rt__dropped_vpwr_10  : 1;  /* bit[20-20]: source: SCALER_1_2(Y) [11 over 104] NC */
        unsigned int  scaler_1_2_y__cvdr_rt__sof_vpwr_10      : 1;  /* bit[21-21]: source: SCALER_1_2(Y) [10 over 104] NC */
        unsigned int  scaler_1_2_uv__cvdr_rt__dropped_vpwr_11 : 1;  /* bit[22-22]: source: SCALER_1_2(UV) [9 over 104] NC */
        unsigned int  scaler_1_2_uv__cvdr_rt__sof_vpwr_11     : 1;  /* bit[23-23]: source: SCALER_1_2(UV) [8 over 104] NC */
        unsigned int  fbcyuv_1__cvdr_rt__dropped_vpwr_12      : 1;  /* bit[24-24]: source: FBCYUV_1 [7 over 104] NC */
        unsigned int  fbcyuv_1__cvdr_rt__sof_vpwr_12          : 1;  /* bit[25-25]: source: FBCYUV_1 [6 over 104] NC */
        unsigned int  fbcyuv_1__cvdr_rt__eof_vpwr_12          : 1;  /* bit[26-26]: source: FBCYUV_1 [5 over 104] NC */
        unsigned int  isp_be_2__cvdr_rt__dropped_vpwr_13      : 1;  /* bit[27-27]: source: ISP_BE_2 [4 over 104] NC */
        unsigned int  isp_be_2__cvdr_rt__sof_vpwr_13          : 1;  /* bit[28-28]: source: ISP_BE_2 [3 over 104] NC */
        unsigned int  isp_be_2__cvdr_rt__eof_vpwr_13          : 1;  /* bit[29-29]: source: ISP_BE_2 [2 over 104] NC */
        unsigned int  otap_2_1__cvdr_rt__dropped_vpwr_14      : 1;  /* bit[30-30]: source: OTAP_2_1 [1 over 104] NC */
        unsigned int  otap_2_1__cvdr_rt__sof_vpwr_14          : 1;  /* bit[31-31]: source: OTAP_2_1 [0 over 104] NC */
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_otap_1_1__cvdr_rt__dropped_vpwr_0_START        (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_otap_1_1__cvdr_rt__dropped_vpwr_0_END          (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_otap_1_1__cvdr_rt__sof_vpwr_0_START            (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_otap_1_1__cvdr_rt__sof_vpwr_0_END              (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_otap_1_2__cvdr_rt__dropped_vpwr_1_START        (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_otap_1_2__cvdr_rt__dropped_vpwr_1_END          (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_otap_1_2__cvdr_rt__sof_vpwr_1_START            (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_otap_1_2__cvdr_rt__sof_vpwr_1_END              (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_3_y__cvdr_rt__dropped_vpwr_2_START      (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_3_y__cvdr_rt__dropped_vpwr_2_END        (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_3_y__cvdr_rt__sof_vpwr_2_START          (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_3_y__cvdr_rt__sof_vpwr_2_END            (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_3_uv__cvdr_rt__dropped_vpwr_3_START     (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_3_uv__cvdr_rt__dropped_vpwr_3_END       (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_3_uv__cvdr_rt__sof_vpwr_3_START         (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_3_uv__cvdr_rt__sof_vpwr_3_END           (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_2_1_y__cvdr_rt__dropped_vpwr_4_START    (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_2_1_y__cvdr_rt__dropped_vpwr_4_END      (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_2_1_y__cvdr_rt__sof_vpwr_4_START        (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_2_1_y__cvdr_rt__sof_vpwr_4_END          (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_2_1_uv__cvdr_rt__dropped_vpwr_5_START   (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_2_1_uv__cvdr_rt__dropped_vpwr_5_END     (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_2_1_uv__cvdr_rt__sof_vpwr_5_START       (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_2_1_uv__cvdr_rt__sof_vpwr_5_END         (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_2_2_y__cvdr_rt__dropped_vpwr_6_START    (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_2_2_y__cvdr_rt__dropped_vpwr_6_END      (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_2_2_y__cvdr_rt__sof_vpwr_6_START        (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_2_2_y__cvdr_rt__sof_vpwr_6_END          (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_2_2_uv__cvdr_rt__dropped_vpwr_7_START   (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_2_2_uv__cvdr_rt__dropped_vpwr_7_END     (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_2_2_uv__cvdr_rt__sof_vpwr_7_START       (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_2_2_uv__cvdr_rt__sof_vpwr_7_END         (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_1_1_y__cvdr_rt__dropped_vpwr_8_START    (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_1_1_y__cvdr_rt__dropped_vpwr_8_END      (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_1_1_y__cvdr_rt__sof_vpwr_8_START        (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_1_1_y__cvdr_rt__sof_vpwr_8_END          (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_1_1_uv__cvdr_rt__dropped_vpwr_9_START   (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_1_1_uv__cvdr_rt__dropped_vpwr_9_END     (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_1_1_uv__cvdr_rt__sof_vpwr_9_START       (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_1_1_uv__cvdr_rt__sof_vpwr_9_END         (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_1_2_y__cvdr_rt__dropped_vpwr_10_START   (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_1_2_y__cvdr_rt__dropped_vpwr_10_END     (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_1_2_y__cvdr_rt__sof_vpwr_10_START       (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_1_2_y__cvdr_rt__sof_vpwr_10_END         (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_1_2_uv__cvdr_rt__dropped_vpwr_11_START  (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_1_2_uv__cvdr_rt__dropped_vpwr_11_END    (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_1_2_uv__cvdr_rt__sof_vpwr_11_START      (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_scaler_1_2_uv__cvdr_rt__sof_vpwr_11_END        (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_fbcyuv_1__cvdr_rt__dropped_vpwr_12_START       (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_fbcyuv_1__cvdr_rt__dropped_vpwr_12_END         (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_fbcyuv_1__cvdr_rt__sof_vpwr_12_START           (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_fbcyuv_1__cvdr_rt__sof_vpwr_12_END             (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_fbcyuv_1__cvdr_rt__eof_vpwr_12_START           (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_fbcyuv_1__cvdr_rt__eof_vpwr_12_END             (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_isp_be_2__cvdr_rt__dropped_vpwr_13_START       (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_isp_be_2__cvdr_rt__dropped_vpwr_13_END         (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_isp_be_2__cvdr_rt__sof_vpwr_13_START           (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_isp_be_2__cvdr_rt__sof_vpwr_13_END             (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_isp_be_2__cvdr_rt__eof_vpwr_13_START           (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_isp_be_2__cvdr_rt__eof_vpwr_13_END             (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_otap_2_1__cvdr_rt__dropped_vpwr_14_START       (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_otap_2_1__cvdr_rt__dropped_vpwr_14_END         (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_otap_2_1__cvdr_rt__sof_vpwr_14_START           (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_0_otap_2_1__cvdr_rt__sof_vpwr_14_END             (31)


/*****************************************************************************
 结构名    : SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_UNION
 结构说明  : IRQ_MERGER_IMSC_DEBUG_1 寄存器结构定义。地址偏移量:0x20，初值:0x00000000，宽度:32
 寄存器说明: [Interrupt Mask Register] DEBUG register (bloc 1 over 3).
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  otap_2_2__cvdr_rt__dropped_vpwr_15         : 1;  /* bit[0-0]  : source: OTAP_2_2 [63 over 104] NC */
        unsigned int  otap_2_2__cvdr_rt__sof_vpwr_15             : 1;  /* bit[1-1]  : source: OTAP_2_2 [62 over 104] NC */
        unsigned int  isp_fe_1__cvdr_rt__dropped_vpwr_16         : 1;  /* bit[2-2]  : source: ISP_FE_1 [61 over 104] NC */
        unsigned int  isp_fe_1__cvdr_rt__sof_vpwr_16             : 1;  /* bit[3-3]  : source: ISP_FE_1 [60 over 104] NC */
        unsigned int  stream_router_1__cvdr_rt__dropped_vpwr_18b : 1;  /* bit[4-4]  : source: STREAM_ROUTER(1) [59 over 104] NC */
        unsigned int  stream_router_1__cvdr_rt__sof_vpwr_18b     : 1;  /* bit[5-5]  : source: STREAM_ROUTER(1) [58 over 104] NC */
        unsigned int  isp_fe_2__cvdr_rt__dropped_vpwr_17         : 1;  /* bit[6-6]  : source: ISP_FE_2 [57 over 104] NC */
        unsigned int  isp_fe_2__cvdr_rt__sof_vpwr_17             : 1;  /* bit[7-7]  : source: ISP_FE_2 [56 over 104] NC */
        unsigned int  stream_router_2__cvdr_rt__dropped_vpwr_19b : 1;  /* bit[8-8]  : source: STREAM_ROUTER(2) [55 over 104] NC */
        unsigned int  stream_router_2__cvdr_rt__sof_vpwr_19b     : 1;  /* bit[9-9]  : source: STREAM_ROUTER(2) [54 over 104] NC */
        unsigned int  stat3a_1__cvdr_rt__dropped_vpwr_20         : 1;  /* bit[10-10]: source: STAT3A_1 [53 over 104] NC */
        unsigned int  stat3a_1__cvdr_rt__sof_vpwr_20             : 1;  /* bit[11-11]: source: STAT3A_1 [52 over 104] NC */
        unsigned int  stat3a_2__cvdr_rt__dropped_vpwr_21         : 1;  /* bit[12-12]: source: STAT3A_2 [51 over 104] NC */
        unsigned int  stat3a_2__cvdr_rt__sof_vpwr_21             : 1;  /* bit[13-13]: source: STAT3A_2 [50 over 104] NC */
        unsigned int  stream_router_3__cvdr_rt__dropped_vpwr_22  : 1;  /* bit[14-14]: source: STREAM_ROUTER(3) [49 over 104] NC */
        unsigned int  stream_router_3__cvdr_rt__sof_vpwr_22      : 1;  /* bit[15-15]: source: STREAM_ROUTER(3) [48 over 104] NC */
        unsigned int  stream_router_4__cvdr_rt__dropped_vpwr_23  : 1;  /* bit[16-16]: source: STREAM_ROUTER(4) [47 over 104] NC */
        unsigned int  stream_router_4__cvdr_rt__sof_vpwr_23      : 1;  /* bit[17-17]: source: STREAM_ROUTER(4) [46 over 104] NC */
        unsigned int  stream_router_5__cvdr_rt__dropped_vpwr_24  : 1;  /* bit[18-18]: source: STREAM_ROUTER(5) [45 over 104] NC */
        unsigned int  stream_router_5__cvdr_rt__sof_vpwr_24      : 1;  /* bit[19-19]: source: STREAM_ROUTER(5) [44 over 104] NC */
        unsigned int  jpgenc__cvdr_rt__dropped_vpwr_25           : 1;  /* bit[20-20]: source: JPGENC [43 over 104] NC */
        unsigned int  jpgenc__cvdr_rt__sof_vpwr_25               : 1;  /* bit[21-21]: source: JPGENC [42 over 104] NC */
        unsigned int  fbdyuv_1__cvdr_rt__sof_vprd_0              : 1;  /* bit[22-22]: source: FBDYUV_1 [41 over 104] NC */
        unsigned int  fbdyuv_1__cvdr_rt__eof_vprd_0              : 1;  /* bit[23-23]: source: FBDYUV_1 [40 over 104] NC */
        unsigned int  scaler_x_2__cvdr_rt__sof_vprd_1            : 1;  /* bit[24-24]: source: SCALER_x_2 [39 over 104] NC */
        unsigned int  scaler_x_2__cvdr_rt__eof_vprd_1            : 1;  /* bit[25-25]: source: SCALER_x_2 [38 over 104] NC */
        unsigned int  isp_be_1__cvdr_rt__sof_vprd_2              : 1;  /* bit[26-26]: source: ISP_BE_1 [37 over 104] NC */
        unsigned int  isp_be_1__cvdr_rt__eof_vprd_2              : 1;  /* bit[27-27]: source: ISP_BE_1 [36 over 104] NC */
        unsigned int  isp_be_2__cvdr_rt__sof_vprd_3              : 1;  /* bit[28-28]: source: ISP_BE_2 [35 over 104] NC */
        unsigned int  isp_be_2__cvdr_rt__eof_vprd_3              : 1;  /* bit[29-29]: source: ISP_BE_2 [34 over 104] NC */
        unsigned int  itap_1_1__cvdr_rt__sof_vprd_4              : 1;  /* bit[30-30]: source: ITAP_1_1 [33 over 104] NC */
        unsigned int  itap_1_1__cvdr_rt__eof_vprd_4              : 1;  /* bit[31-31]: source: ITAP_1_1 [32 over 104] NC */
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_otap_2_2__cvdr_rt__dropped_vpwr_15_START          (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_otap_2_2__cvdr_rt__dropped_vpwr_15_END            (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_otap_2_2__cvdr_rt__sof_vpwr_15_START              (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_otap_2_2__cvdr_rt__sof_vpwr_15_END                (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_isp_fe_1__cvdr_rt__dropped_vpwr_16_START          (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_isp_fe_1__cvdr_rt__dropped_vpwr_16_END            (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_isp_fe_1__cvdr_rt__sof_vpwr_16_START              (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_isp_fe_1__cvdr_rt__sof_vpwr_16_END                (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_stream_router_1__cvdr_rt__dropped_vpwr_18b_START  (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_stream_router_1__cvdr_rt__dropped_vpwr_18b_END    (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_stream_router_1__cvdr_rt__sof_vpwr_18b_START      (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_stream_router_1__cvdr_rt__sof_vpwr_18b_END        (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_isp_fe_2__cvdr_rt__dropped_vpwr_17_START          (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_isp_fe_2__cvdr_rt__dropped_vpwr_17_END            (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_isp_fe_2__cvdr_rt__sof_vpwr_17_START              (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_isp_fe_2__cvdr_rt__sof_vpwr_17_END                (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_stream_router_2__cvdr_rt__dropped_vpwr_19b_START  (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_stream_router_2__cvdr_rt__dropped_vpwr_19b_END    (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_stream_router_2__cvdr_rt__sof_vpwr_19b_START      (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_stream_router_2__cvdr_rt__sof_vpwr_19b_END        (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_stat3a_1__cvdr_rt__dropped_vpwr_20_START          (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_stat3a_1__cvdr_rt__dropped_vpwr_20_END            (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_stat3a_1__cvdr_rt__sof_vpwr_20_START              (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_stat3a_1__cvdr_rt__sof_vpwr_20_END                (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_stat3a_2__cvdr_rt__dropped_vpwr_21_START          (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_stat3a_2__cvdr_rt__dropped_vpwr_21_END            (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_stat3a_2__cvdr_rt__sof_vpwr_21_START              (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_stat3a_2__cvdr_rt__sof_vpwr_21_END                (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_stream_router_3__cvdr_rt__dropped_vpwr_22_START   (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_stream_router_3__cvdr_rt__dropped_vpwr_22_END     (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_stream_router_3__cvdr_rt__sof_vpwr_22_START       (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_stream_router_3__cvdr_rt__sof_vpwr_22_END         (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_stream_router_4__cvdr_rt__dropped_vpwr_23_START   (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_stream_router_4__cvdr_rt__dropped_vpwr_23_END     (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_stream_router_4__cvdr_rt__sof_vpwr_23_START       (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_stream_router_4__cvdr_rt__sof_vpwr_23_END         (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_stream_router_5__cvdr_rt__dropped_vpwr_24_START   (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_stream_router_5__cvdr_rt__dropped_vpwr_24_END     (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_stream_router_5__cvdr_rt__sof_vpwr_24_START       (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_stream_router_5__cvdr_rt__sof_vpwr_24_END         (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_jpgenc__cvdr_rt__dropped_vpwr_25_START            (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_jpgenc__cvdr_rt__dropped_vpwr_25_END              (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_jpgenc__cvdr_rt__sof_vpwr_25_START                (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_jpgenc__cvdr_rt__sof_vpwr_25_END                  (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_fbdyuv_1__cvdr_rt__sof_vprd_0_START               (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_fbdyuv_1__cvdr_rt__sof_vprd_0_END                 (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_fbdyuv_1__cvdr_rt__eof_vprd_0_START               (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_fbdyuv_1__cvdr_rt__eof_vprd_0_END                 (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_scaler_x_2__cvdr_rt__sof_vprd_1_START             (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_scaler_x_2__cvdr_rt__sof_vprd_1_END               (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_scaler_x_2__cvdr_rt__eof_vprd_1_START             (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_scaler_x_2__cvdr_rt__eof_vprd_1_END               (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_isp_be_1__cvdr_rt__sof_vprd_2_START               (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_isp_be_1__cvdr_rt__sof_vprd_2_END                 (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_isp_be_1__cvdr_rt__eof_vprd_2_START               (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_isp_be_1__cvdr_rt__eof_vprd_2_END                 (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_isp_be_2__cvdr_rt__sof_vprd_3_START               (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_isp_be_2__cvdr_rt__sof_vprd_3_END                 (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_isp_be_2__cvdr_rt__eof_vprd_3_START               (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_isp_be_2__cvdr_rt__eof_vprd_3_END                 (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_itap_1_1__cvdr_rt__sof_vprd_4_START               (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_itap_1_1__cvdr_rt__sof_vprd_4_END                 (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_itap_1_1__cvdr_rt__eof_vprd_4_START               (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_1_itap_1_1__cvdr_rt__eof_vprd_4_END                 (31)


/*****************************************************************************
 结构名    : SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_UNION
 结构说明  : IRQ_MERGER_RIS_DEBUG_1 寄存器结构定义。地址偏移量:0x24，初值:0x00000000，宽度:32
 寄存器说明: [Raw Interrupt Status Register] DEBUG register (bloc 1 over 3).
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  otap_2_2__cvdr_rt__dropped_vpwr_15         : 1;  /* bit[0-0]  : source: OTAP_2_2 [63 over 104] NC */
        unsigned int  otap_2_2__cvdr_rt__sof_vpwr_15             : 1;  /* bit[1-1]  : source: OTAP_2_2 [62 over 104] NC */
        unsigned int  isp_fe_1__cvdr_rt__dropped_vpwr_16         : 1;  /* bit[2-2]  : source: ISP_FE_1 [61 over 104] NC */
        unsigned int  isp_fe_1__cvdr_rt__sof_vpwr_16             : 1;  /* bit[3-3]  : source: ISP_FE_1 [60 over 104] NC */
        unsigned int  stream_router_1__cvdr_rt__dropped_vpwr_18b : 1;  /* bit[4-4]  : source: STREAM_ROUTER(1) [59 over 104] NC */
        unsigned int  stream_router_1__cvdr_rt__sof_vpwr_18b     : 1;  /* bit[5-5]  : source: STREAM_ROUTER(1) [58 over 104] NC */
        unsigned int  isp_fe_2__cvdr_rt__dropped_vpwr_17         : 1;  /* bit[6-6]  : source: ISP_FE_2 [57 over 104] NC */
        unsigned int  isp_fe_2__cvdr_rt__sof_vpwr_17             : 1;  /* bit[7-7]  : source: ISP_FE_2 [56 over 104] NC */
        unsigned int  stream_router_2__cvdr_rt__dropped_vpwr_19b : 1;  /* bit[8-8]  : source: STREAM_ROUTER(2) [55 over 104] NC */
        unsigned int  stream_router_2__cvdr_rt__sof_vpwr_19b     : 1;  /* bit[9-9]  : source: STREAM_ROUTER(2) [54 over 104] NC */
        unsigned int  stat3a_1__cvdr_rt__dropped_vpwr_20         : 1;  /* bit[10-10]: source: STAT3A_1 [53 over 104] NC */
        unsigned int  stat3a_1__cvdr_rt__sof_vpwr_20             : 1;  /* bit[11-11]: source: STAT3A_1 [52 over 104] NC */
        unsigned int  stat3a_2__cvdr_rt__dropped_vpwr_21         : 1;  /* bit[12-12]: source: STAT3A_2 [51 over 104] NC */
        unsigned int  stat3a_2__cvdr_rt__sof_vpwr_21             : 1;  /* bit[13-13]: source: STAT3A_2 [50 over 104] NC */
        unsigned int  stream_router_3__cvdr_rt__dropped_vpwr_22  : 1;  /* bit[14-14]: source: STREAM_ROUTER(3) [49 over 104] NC */
        unsigned int  stream_router_3__cvdr_rt__sof_vpwr_22      : 1;  /* bit[15-15]: source: STREAM_ROUTER(3) [48 over 104] NC */
        unsigned int  stream_router_4__cvdr_rt__dropped_vpwr_23  : 1;  /* bit[16-16]: source: STREAM_ROUTER(4) [47 over 104] NC */
        unsigned int  stream_router_4__cvdr_rt__sof_vpwr_23      : 1;  /* bit[17-17]: source: STREAM_ROUTER(4) [46 over 104] NC */
        unsigned int  stream_router_5__cvdr_rt__dropped_vpwr_24  : 1;  /* bit[18-18]: source: STREAM_ROUTER(5) [45 over 104] NC */
        unsigned int  stream_router_5__cvdr_rt__sof_vpwr_24      : 1;  /* bit[19-19]: source: STREAM_ROUTER(5) [44 over 104] NC */
        unsigned int  jpgenc__cvdr_rt__dropped_vpwr_25           : 1;  /* bit[20-20]: source: JPGENC [43 over 104] NC */
        unsigned int  jpgenc__cvdr_rt__sof_vpwr_25               : 1;  /* bit[21-21]: source: JPGENC [42 over 104] NC */
        unsigned int  fbdyuv_1__cvdr_rt__sof_vprd_0              : 1;  /* bit[22-22]: source: FBDYUV_1 [41 over 104] NC */
        unsigned int  fbdyuv_1__cvdr_rt__eof_vprd_0              : 1;  /* bit[23-23]: source: FBDYUV_1 [40 over 104] NC */
        unsigned int  scaler_x_2__cvdr_rt__sof_vprd_1            : 1;  /* bit[24-24]: source: SCALER_x_2 [39 over 104] NC */
        unsigned int  scaler_x_2__cvdr_rt__eof_vprd_1            : 1;  /* bit[25-25]: source: SCALER_x_2 [38 over 104] NC */
        unsigned int  isp_be_1__cvdr_rt__sof_vprd_2              : 1;  /* bit[26-26]: source: ISP_BE_1 [37 over 104] NC */
        unsigned int  isp_be_1__cvdr_rt__eof_vprd_2              : 1;  /* bit[27-27]: source: ISP_BE_1 [36 over 104] NC */
        unsigned int  isp_be_2__cvdr_rt__sof_vprd_3              : 1;  /* bit[28-28]: source: ISP_BE_2 [35 over 104] NC */
        unsigned int  isp_be_2__cvdr_rt__eof_vprd_3              : 1;  /* bit[29-29]: source: ISP_BE_2 [34 over 104] NC */
        unsigned int  itap_1_1__cvdr_rt__sof_vprd_4              : 1;  /* bit[30-30]: source: ITAP_1_1 [33 over 104] NC */
        unsigned int  itap_1_1__cvdr_rt__eof_vprd_4              : 1;  /* bit[31-31]: source: ITAP_1_1 [32 over 104] NC */
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_otap_2_2__cvdr_rt__dropped_vpwr_15_START          (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_otap_2_2__cvdr_rt__dropped_vpwr_15_END            (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_otap_2_2__cvdr_rt__sof_vpwr_15_START              (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_otap_2_2__cvdr_rt__sof_vpwr_15_END                (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_isp_fe_1__cvdr_rt__dropped_vpwr_16_START          (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_isp_fe_1__cvdr_rt__dropped_vpwr_16_END            (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_isp_fe_1__cvdr_rt__sof_vpwr_16_START              (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_isp_fe_1__cvdr_rt__sof_vpwr_16_END                (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_stream_router_1__cvdr_rt__dropped_vpwr_18b_START  (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_stream_router_1__cvdr_rt__dropped_vpwr_18b_END    (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_stream_router_1__cvdr_rt__sof_vpwr_18b_START      (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_stream_router_1__cvdr_rt__sof_vpwr_18b_END        (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_isp_fe_2__cvdr_rt__dropped_vpwr_17_START          (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_isp_fe_2__cvdr_rt__dropped_vpwr_17_END            (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_isp_fe_2__cvdr_rt__sof_vpwr_17_START              (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_isp_fe_2__cvdr_rt__sof_vpwr_17_END                (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_stream_router_2__cvdr_rt__dropped_vpwr_19b_START  (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_stream_router_2__cvdr_rt__dropped_vpwr_19b_END    (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_stream_router_2__cvdr_rt__sof_vpwr_19b_START      (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_stream_router_2__cvdr_rt__sof_vpwr_19b_END        (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_stat3a_1__cvdr_rt__dropped_vpwr_20_START          (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_stat3a_1__cvdr_rt__dropped_vpwr_20_END            (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_stat3a_1__cvdr_rt__sof_vpwr_20_START              (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_stat3a_1__cvdr_rt__sof_vpwr_20_END                (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_stat3a_2__cvdr_rt__dropped_vpwr_21_START          (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_stat3a_2__cvdr_rt__dropped_vpwr_21_END            (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_stat3a_2__cvdr_rt__sof_vpwr_21_START              (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_stat3a_2__cvdr_rt__sof_vpwr_21_END                (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_stream_router_3__cvdr_rt__dropped_vpwr_22_START   (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_stream_router_3__cvdr_rt__dropped_vpwr_22_END     (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_stream_router_3__cvdr_rt__sof_vpwr_22_START       (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_stream_router_3__cvdr_rt__sof_vpwr_22_END         (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_stream_router_4__cvdr_rt__dropped_vpwr_23_START   (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_stream_router_4__cvdr_rt__dropped_vpwr_23_END     (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_stream_router_4__cvdr_rt__sof_vpwr_23_START       (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_stream_router_4__cvdr_rt__sof_vpwr_23_END         (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_stream_router_5__cvdr_rt__dropped_vpwr_24_START   (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_stream_router_5__cvdr_rt__dropped_vpwr_24_END     (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_stream_router_5__cvdr_rt__sof_vpwr_24_START       (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_stream_router_5__cvdr_rt__sof_vpwr_24_END         (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_jpgenc__cvdr_rt__dropped_vpwr_25_START            (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_jpgenc__cvdr_rt__dropped_vpwr_25_END              (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_jpgenc__cvdr_rt__sof_vpwr_25_START                (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_jpgenc__cvdr_rt__sof_vpwr_25_END                  (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_fbdyuv_1__cvdr_rt__sof_vprd_0_START               (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_fbdyuv_1__cvdr_rt__sof_vprd_0_END                 (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_fbdyuv_1__cvdr_rt__eof_vprd_0_START               (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_fbdyuv_1__cvdr_rt__eof_vprd_0_END                 (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_scaler_x_2__cvdr_rt__sof_vprd_1_START             (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_scaler_x_2__cvdr_rt__sof_vprd_1_END               (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_scaler_x_2__cvdr_rt__eof_vprd_1_START             (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_scaler_x_2__cvdr_rt__eof_vprd_1_END               (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_isp_be_1__cvdr_rt__sof_vprd_2_START               (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_isp_be_1__cvdr_rt__sof_vprd_2_END                 (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_isp_be_1__cvdr_rt__eof_vprd_2_START               (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_isp_be_1__cvdr_rt__eof_vprd_2_END                 (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_isp_be_2__cvdr_rt__sof_vprd_3_START               (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_isp_be_2__cvdr_rt__sof_vprd_3_END                 (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_isp_be_2__cvdr_rt__eof_vprd_3_START               (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_isp_be_2__cvdr_rt__eof_vprd_3_END                 (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_itap_1_1__cvdr_rt__sof_vprd_4_START               (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_itap_1_1__cvdr_rt__sof_vprd_4_END                 (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_itap_1_1__cvdr_rt__eof_vprd_4_START               (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_1_itap_1_1__cvdr_rt__eof_vprd_4_END                 (31)


/*****************************************************************************
 结构名    : SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_UNION
 结构说明  : IRQ_MERGER_MIS_DEBUG_1 寄存器结构定义。地址偏移量:0x28，初值:0x00000000，宽度:32
 寄存器说明: [Masked Interrupt Status Register] DEBUG register (bloc 1 over 3).
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  otap_2_2__cvdr_rt__dropped_vpwr_15         : 1;  /* bit[0-0]  : source: OTAP_2_2 [63 over 104] NC */
        unsigned int  otap_2_2__cvdr_rt__sof_vpwr_15             : 1;  /* bit[1-1]  : source: OTAP_2_2 [62 over 104] NC */
        unsigned int  isp_fe_1__cvdr_rt__dropped_vpwr_16         : 1;  /* bit[2-2]  : source: ISP_FE_1 [61 over 104] NC */
        unsigned int  isp_fe_1__cvdr_rt__sof_vpwr_16             : 1;  /* bit[3-3]  : source: ISP_FE_1 [60 over 104] NC */
        unsigned int  stream_router_1__cvdr_rt__dropped_vpwr_18b : 1;  /* bit[4-4]  : source: STREAM_ROUTER(1) [59 over 104] NC */
        unsigned int  stream_router_1__cvdr_rt__sof_vpwr_18b     : 1;  /* bit[5-5]  : source: STREAM_ROUTER(1) [58 over 104] NC */
        unsigned int  isp_fe_2__cvdr_rt__dropped_vpwr_17         : 1;  /* bit[6-6]  : source: ISP_FE_2 [57 over 104] NC */
        unsigned int  isp_fe_2__cvdr_rt__sof_vpwr_17             : 1;  /* bit[7-7]  : source: ISP_FE_2 [56 over 104] NC */
        unsigned int  stream_router_2__cvdr_rt__dropped_vpwr_19b : 1;  /* bit[8-8]  : source: STREAM_ROUTER(2) [55 over 104] NC */
        unsigned int  stream_router_2__cvdr_rt__sof_vpwr_19b     : 1;  /* bit[9-9]  : source: STREAM_ROUTER(2) [54 over 104] NC */
        unsigned int  stat3a_1__cvdr_rt__dropped_vpwr_20         : 1;  /* bit[10-10]: source: STAT3A_1 [53 over 104] NC */
        unsigned int  stat3a_1__cvdr_rt__sof_vpwr_20             : 1;  /* bit[11-11]: source: STAT3A_1 [52 over 104] NC */
        unsigned int  stat3a_2__cvdr_rt__dropped_vpwr_21         : 1;  /* bit[12-12]: source: STAT3A_2 [51 over 104] NC */
        unsigned int  stat3a_2__cvdr_rt__sof_vpwr_21             : 1;  /* bit[13-13]: source: STAT3A_2 [50 over 104] NC */
        unsigned int  stream_router_3__cvdr_rt__dropped_vpwr_22  : 1;  /* bit[14-14]: source: STREAM_ROUTER(3) [49 over 104] NC */
        unsigned int  stream_router_3__cvdr_rt__sof_vpwr_22      : 1;  /* bit[15-15]: source: STREAM_ROUTER(3) [48 over 104] NC */
        unsigned int  stream_router_4__cvdr_rt__dropped_vpwr_23  : 1;  /* bit[16-16]: source: STREAM_ROUTER(4) [47 over 104] NC */
        unsigned int  stream_router_4__cvdr_rt__sof_vpwr_23      : 1;  /* bit[17-17]: source: STREAM_ROUTER(4) [46 over 104] NC */
        unsigned int  stream_router_5__cvdr_rt__dropped_vpwr_24  : 1;  /* bit[18-18]: source: STREAM_ROUTER(5) [45 over 104] NC */
        unsigned int  stream_router_5__cvdr_rt__sof_vpwr_24      : 1;  /* bit[19-19]: source: STREAM_ROUTER(5) [44 over 104] NC */
        unsigned int  jpgenc__cvdr_rt__dropped_vpwr_25           : 1;  /* bit[20-20]: source: JPGENC [43 over 104] NC */
        unsigned int  jpgenc__cvdr_rt__sof_vpwr_25               : 1;  /* bit[21-21]: source: JPGENC [42 over 104] NC */
        unsigned int  fbdyuv_1__cvdr_rt__sof_vprd_0              : 1;  /* bit[22-22]: source: FBDYUV_1 [41 over 104] NC */
        unsigned int  fbdyuv_1__cvdr_rt__eof_vprd_0              : 1;  /* bit[23-23]: source: FBDYUV_1 [40 over 104] NC */
        unsigned int  scaler_x_2__cvdr_rt__sof_vprd_1            : 1;  /* bit[24-24]: source: SCALER_x_2 [39 over 104] NC */
        unsigned int  scaler_x_2__cvdr_rt__eof_vprd_1            : 1;  /* bit[25-25]: source: SCALER_x_2 [38 over 104] NC */
        unsigned int  isp_be_1__cvdr_rt__sof_vprd_2              : 1;  /* bit[26-26]: source: ISP_BE_1 [37 over 104] NC */
        unsigned int  isp_be_1__cvdr_rt__eof_vprd_2              : 1;  /* bit[27-27]: source: ISP_BE_1 [36 over 104] NC */
        unsigned int  isp_be_2__cvdr_rt__sof_vprd_3              : 1;  /* bit[28-28]: source: ISP_BE_2 [35 over 104] NC */
        unsigned int  isp_be_2__cvdr_rt__eof_vprd_3              : 1;  /* bit[29-29]: source: ISP_BE_2 [34 over 104] NC */
        unsigned int  itap_1_1__cvdr_rt__sof_vprd_4              : 1;  /* bit[30-30]: source: ITAP_1_1 [33 over 104] NC */
        unsigned int  itap_1_1__cvdr_rt__eof_vprd_4              : 1;  /* bit[31-31]: source: ITAP_1_1 [32 over 104] NC */
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_otap_2_2__cvdr_rt__dropped_vpwr_15_START          (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_otap_2_2__cvdr_rt__dropped_vpwr_15_END            (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_otap_2_2__cvdr_rt__sof_vpwr_15_START              (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_otap_2_2__cvdr_rt__sof_vpwr_15_END                (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_isp_fe_1__cvdr_rt__dropped_vpwr_16_START          (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_isp_fe_1__cvdr_rt__dropped_vpwr_16_END            (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_isp_fe_1__cvdr_rt__sof_vpwr_16_START              (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_isp_fe_1__cvdr_rt__sof_vpwr_16_END                (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_stream_router_1__cvdr_rt__dropped_vpwr_18b_START  (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_stream_router_1__cvdr_rt__dropped_vpwr_18b_END    (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_stream_router_1__cvdr_rt__sof_vpwr_18b_START      (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_stream_router_1__cvdr_rt__sof_vpwr_18b_END        (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_isp_fe_2__cvdr_rt__dropped_vpwr_17_START          (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_isp_fe_2__cvdr_rt__dropped_vpwr_17_END            (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_isp_fe_2__cvdr_rt__sof_vpwr_17_START              (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_isp_fe_2__cvdr_rt__sof_vpwr_17_END                (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_stream_router_2__cvdr_rt__dropped_vpwr_19b_START  (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_stream_router_2__cvdr_rt__dropped_vpwr_19b_END    (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_stream_router_2__cvdr_rt__sof_vpwr_19b_START      (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_stream_router_2__cvdr_rt__sof_vpwr_19b_END        (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_stat3a_1__cvdr_rt__dropped_vpwr_20_START          (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_stat3a_1__cvdr_rt__dropped_vpwr_20_END            (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_stat3a_1__cvdr_rt__sof_vpwr_20_START              (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_stat3a_1__cvdr_rt__sof_vpwr_20_END                (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_stat3a_2__cvdr_rt__dropped_vpwr_21_START          (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_stat3a_2__cvdr_rt__dropped_vpwr_21_END            (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_stat3a_2__cvdr_rt__sof_vpwr_21_START              (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_stat3a_2__cvdr_rt__sof_vpwr_21_END                (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_stream_router_3__cvdr_rt__dropped_vpwr_22_START   (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_stream_router_3__cvdr_rt__dropped_vpwr_22_END     (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_stream_router_3__cvdr_rt__sof_vpwr_22_START       (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_stream_router_3__cvdr_rt__sof_vpwr_22_END         (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_stream_router_4__cvdr_rt__dropped_vpwr_23_START   (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_stream_router_4__cvdr_rt__dropped_vpwr_23_END     (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_stream_router_4__cvdr_rt__sof_vpwr_23_START       (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_stream_router_4__cvdr_rt__sof_vpwr_23_END         (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_stream_router_5__cvdr_rt__dropped_vpwr_24_START   (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_stream_router_5__cvdr_rt__dropped_vpwr_24_END     (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_stream_router_5__cvdr_rt__sof_vpwr_24_START       (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_stream_router_5__cvdr_rt__sof_vpwr_24_END         (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_jpgenc__cvdr_rt__dropped_vpwr_25_START            (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_jpgenc__cvdr_rt__dropped_vpwr_25_END              (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_jpgenc__cvdr_rt__sof_vpwr_25_START                (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_jpgenc__cvdr_rt__sof_vpwr_25_END                  (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_fbdyuv_1__cvdr_rt__sof_vprd_0_START               (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_fbdyuv_1__cvdr_rt__sof_vprd_0_END                 (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_fbdyuv_1__cvdr_rt__eof_vprd_0_START               (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_fbdyuv_1__cvdr_rt__eof_vprd_0_END                 (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_scaler_x_2__cvdr_rt__sof_vprd_1_START             (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_scaler_x_2__cvdr_rt__sof_vprd_1_END               (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_scaler_x_2__cvdr_rt__eof_vprd_1_START             (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_scaler_x_2__cvdr_rt__eof_vprd_1_END               (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_isp_be_1__cvdr_rt__sof_vprd_2_START               (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_isp_be_1__cvdr_rt__sof_vprd_2_END                 (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_isp_be_1__cvdr_rt__eof_vprd_2_START               (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_isp_be_1__cvdr_rt__eof_vprd_2_END                 (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_isp_be_2__cvdr_rt__sof_vprd_3_START               (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_isp_be_2__cvdr_rt__sof_vprd_3_END                 (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_isp_be_2__cvdr_rt__eof_vprd_3_START               (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_isp_be_2__cvdr_rt__eof_vprd_3_END                 (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_itap_1_1__cvdr_rt__sof_vprd_4_START               (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_itap_1_1__cvdr_rt__sof_vprd_4_END                 (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_itap_1_1__cvdr_rt__eof_vprd_4_START               (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_1_itap_1_1__cvdr_rt__eof_vprd_4_END                 (31)


/*****************************************************************************
 结构名    : SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_UNION
 结构说明  : IRQ_MERGER_ICR_DEBUG_1 寄存器结构定义。地址偏移量:0x2C，初值:0x00000000，宽度:32
 寄存器说明: [Interrupt Clear Register] DEBUG register (bloc 1 over 3).
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  otap_2_2__cvdr_rt__dropped_vpwr_15         : 1;  /* bit[0-0]  : source: OTAP_2_2 [63 over 104] NC */
        unsigned int  otap_2_2__cvdr_rt__sof_vpwr_15             : 1;  /* bit[1-1]  : source: OTAP_2_2 [62 over 104] NC */
        unsigned int  isp_fe_1__cvdr_rt__dropped_vpwr_16         : 1;  /* bit[2-2]  : source: ISP_FE_1 [61 over 104] NC */
        unsigned int  isp_fe_1__cvdr_rt__sof_vpwr_16             : 1;  /* bit[3-3]  : source: ISP_FE_1 [60 over 104] NC */
        unsigned int  stream_router_1__cvdr_rt__dropped_vpwr_18b : 1;  /* bit[4-4]  : source: STREAM_ROUTER(1) [59 over 104] NC */
        unsigned int  stream_router_1__cvdr_rt__sof_vpwr_18b     : 1;  /* bit[5-5]  : source: STREAM_ROUTER(1) [58 over 104] NC */
        unsigned int  isp_fe_2__cvdr_rt__dropped_vpwr_17         : 1;  /* bit[6-6]  : source: ISP_FE_2 [57 over 104] NC */
        unsigned int  isp_fe_2__cvdr_rt__sof_vpwr_17             : 1;  /* bit[7-7]  : source: ISP_FE_2 [56 over 104] NC */
        unsigned int  stream_router_2__cvdr_rt__dropped_vpwr_19b : 1;  /* bit[8-8]  : source: STREAM_ROUTER(2) [55 over 104] NC */
        unsigned int  stream_router_2__cvdr_rt__sof_vpwr_19b     : 1;  /* bit[9-9]  : source: STREAM_ROUTER(2) [54 over 104] NC */
        unsigned int  stat3a_1__cvdr_rt__dropped_vpwr_20         : 1;  /* bit[10-10]: source: STAT3A_1 [53 over 104] NC */
        unsigned int  stat3a_1__cvdr_rt__sof_vpwr_20             : 1;  /* bit[11-11]: source: STAT3A_1 [52 over 104] NC */
        unsigned int  stat3a_2__cvdr_rt__dropped_vpwr_21         : 1;  /* bit[12-12]: source: STAT3A_2 [51 over 104] NC */
        unsigned int  stat3a_2__cvdr_rt__sof_vpwr_21             : 1;  /* bit[13-13]: source: STAT3A_2 [50 over 104] NC */
        unsigned int  stream_router_3__cvdr_rt__dropped_vpwr_22  : 1;  /* bit[14-14]: source: STREAM_ROUTER(3) [49 over 104] NC */
        unsigned int  stream_router_3__cvdr_rt__sof_vpwr_22      : 1;  /* bit[15-15]: source: STREAM_ROUTER(3) [48 over 104] NC */
        unsigned int  stream_router_4__cvdr_rt__dropped_vpwr_23  : 1;  /* bit[16-16]: source: STREAM_ROUTER(4) [47 over 104] NC */
        unsigned int  stream_router_4__cvdr_rt__sof_vpwr_23      : 1;  /* bit[17-17]: source: STREAM_ROUTER(4) [46 over 104] NC */
        unsigned int  stream_router_5__cvdr_rt__dropped_vpwr_24  : 1;  /* bit[18-18]: source: STREAM_ROUTER(5) [45 over 104] NC */
        unsigned int  stream_router_5__cvdr_rt__sof_vpwr_24      : 1;  /* bit[19-19]: source: STREAM_ROUTER(5) [44 over 104] NC */
        unsigned int  jpgenc__cvdr_rt__dropped_vpwr_25           : 1;  /* bit[20-20]: source: JPGENC [43 over 104] NC */
        unsigned int  jpgenc__cvdr_rt__sof_vpwr_25               : 1;  /* bit[21-21]: source: JPGENC [42 over 104] NC */
        unsigned int  fbdyuv_1__cvdr_rt__sof_vprd_0              : 1;  /* bit[22-22]: source: FBDYUV_1 [41 over 104] NC */
        unsigned int  fbdyuv_1__cvdr_rt__eof_vprd_0              : 1;  /* bit[23-23]: source: FBDYUV_1 [40 over 104] NC */
        unsigned int  scaler_x_2__cvdr_rt__sof_vprd_1            : 1;  /* bit[24-24]: source: SCALER_x_2 [39 over 104] NC */
        unsigned int  scaler_x_2__cvdr_rt__eof_vprd_1            : 1;  /* bit[25-25]: source: SCALER_x_2 [38 over 104] NC */
        unsigned int  isp_be_1__cvdr_rt__sof_vprd_2              : 1;  /* bit[26-26]: source: ISP_BE_1 [37 over 104] NC */
        unsigned int  isp_be_1__cvdr_rt__eof_vprd_2              : 1;  /* bit[27-27]: source: ISP_BE_1 [36 over 104] NC */
        unsigned int  isp_be_2__cvdr_rt__sof_vprd_3              : 1;  /* bit[28-28]: source: ISP_BE_2 [35 over 104] NC */
        unsigned int  isp_be_2__cvdr_rt__eof_vprd_3              : 1;  /* bit[29-29]: source: ISP_BE_2 [34 over 104] NC */
        unsigned int  itap_1_1__cvdr_rt__sof_vprd_4              : 1;  /* bit[30-30]: source: ITAP_1_1 [33 over 104] NC */
        unsigned int  itap_1_1__cvdr_rt__eof_vprd_4              : 1;  /* bit[31-31]: source: ITAP_1_1 [32 over 104] NC */
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_otap_2_2__cvdr_rt__dropped_vpwr_15_START          (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_otap_2_2__cvdr_rt__dropped_vpwr_15_END            (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_otap_2_2__cvdr_rt__sof_vpwr_15_START              (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_otap_2_2__cvdr_rt__sof_vpwr_15_END                (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_isp_fe_1__cvdr_rt__dropped_vpwr_16_START          (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_isp_fe_1__cvdr_rt__dropped_vpwr_16_END            (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_isp_fe_1__cvdr_rt__sof_vpwr_16_START              (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_isp_fe_1__cvdr_rt__sof_vpwr_16_END                (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_stream_router_1__cvdr_rt__dropped_vpwr_18b_START  (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_stream_router_1__cvdr_rt__dropped_vpwr_18b_END    (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_stream_router_1__cvdr_rt__sof_vpwr_18b_START      (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_stream_router_1__cvdr_rt__sof_vpwr_18b_END        (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_isp_fe_2__cvdr_rt__dropped_vpwr_17_START          (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_isp_fe_2__cvdr_rt__dropped_vpwr_17_END            (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_isp_fe_2__cvdr_rt__sof_vpwr_17_START              (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_isp_fe_2__cvdr_rt__sof_vpwr_17_END                (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_stream_router_2__cvdr_rt__dropped_vpwr_19b_START  (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_stream_router_2__cvdr_rt__dropped_vpwr_19b_END    (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_stream_router_2__cvdr_rt__sof_vpwr_19b_START      (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_stream_router_2__cvdr_rt__sof_vpwr_19b_END        (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_stat3a_1__cvdr_rt__dropped_vpwr_20_START          (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_stat3a_1__cvdr_rt__dropped_vpwr_20_END            (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_stat3a_1__cvdr_rt__sof_vpwr_20_START              (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_stat3a_1__cvdr_rt__sof_vpwr_20_END                (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_stat3a_2__cvdr_rt__dropped_vpwr_21_START          (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_stat3a_2__cvdr_rt__dropped_vpwr_21_END            (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_stat3a_2__cvdr_rt__sof_vpwr_21_START              (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_stat3a_2__cvdr_rt__sof_vpwr_21_END                (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_stream_router_3__cvdr_rt__dropped_vpwr_22_START   (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_stream_router_3__cvdr_rt__dropped_vpwr_22_END     (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_stream_router_3__cvdr_rt__sof_vpwr_22_START       (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_stream_router_3__cvdr_rt__sof_vpwr_22_END         (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_stream_router_4__cvdr_rt__dropped_vpwr_23_START   (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_stream_router_4__cvdr_rt__dropped_vpwr_23_END     (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_stream_router_4__cvdr_rt__sof_vpwr_23_START       (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_stream_router_4__cvdr_rt__sof_vpwr_23_END         (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_stream_router_5__cvdr_rt__dropped_vpwr_24_START   (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_stream_router_5__cvdr_rt__dropped_vpwr_24_END     (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_stream_router_5__cvdr_rt__sof_vpwr_24_START       (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_stream_router_5__cvdr_rt__sof_vpwr_24_END         (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_jpgenc__cvdr_rt__dropped_vpwr_25_START            (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_jpgenc__cvdr_rt__dropped_vpwr_25_END              (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_jpgenc__cvdr_rt__sof_vpwr_25_START                (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_jpgenc__cvdr_rt__sof_vpwr_25_END                  (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_fbdyuv_1__cvdr_rt__sof_vprd_0_START               (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_fbdyuv_1__cvdr_rt__sof_vprd_0_END                 (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_fbdyuv_1__cvdr_rt__eof_vprd_0_START               (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_fbdyuv_1__cvdr_rt__eof_vprd_0_END                 (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_scaler_x_2__cvdr_rt__sof_vprd_1_START             (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_scaler_x_2__cvdr_rt__sof_vprd_1_END               (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_scaler_x_2__cvdr_rt__eof_vprd_1_START             (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_scaler_x_2__cvdr_rt__eof_vprd_1_END               (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_isp_be_1__cvdr_rt__sof_vprd_2_START               (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_isp_be_1__cvdr_rt__sof_vprd_2_END                 (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_isp_be_1__cvdr_rt__eof_vprd_2_START               (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_isp_be_1__cvdr_rt__eof_vprd_2_END                 (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_isp_be_2__cvdr_rt__sof_vprd_3_START               (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_isp_be_2__cvdr_rt__sof_vprd_3_END                 (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_isp_be_2__cvdr_rt__eof_vprd_3_START               (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_isp_be_2__cvdr_rt__eof_vprd_3_END                 (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_itap_1_1__cvdr_rt__sof_vprd_4_START               (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_itap_1_1__cvdr_rt__sof_vprd_4_END                 (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_itap_1_1__cvdr_rt__eof_vprd_4_START               (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_1_itap_1_1__cvdr_rt__eof_vprd_4_END                 (31)


/*****************************************************************************
 结构名    : SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_UNION
 结构说明  : IRQ_MERGER_ISR_DEBUG_1 寄存器结构定义。地址偏移量:0x30，初值:0x00000000，宽度:32
 寄存器说明: [Interrupt Set Register] DEBUG register (bloc 1 over 3).
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  otap_2_2__cvdr_rt__dropped_vpwr_15         : 1;  /* bit[0-0]  : source: OTAP_2_2 [63 over 104] NC */
        unsigned int  otap_2_2__cvdr_rt__sof_vpwr_15             : 1;  /* bit[1-1]  : source: OTAP_2_2 [62 over 104] NC */
        unsigned int  isp_fe_1__cvdr_rt__dropped_vpwr_16         : 1;  /* bit[2-2]  : source: ISP_FE_1 [61 over 104] NC */
        unsigned int  isp_fe_1__cvdr_rt__sof_vpwr_16             : 1;  /* bit[3-3]  : source: ISP_FE_1 [60 over 104] NC */
        unsigned int  stream_router_1__cvdr_rt__dropped_vpwr_18b : 1;  /* bit[4-4]  : source: STREAM_ROUTER(1) [59 over 104] NC */
        unsigned int  stream_router_1__cvdr_rt__sof_vpwr_18b     : 1;  /* bit[5-5]  : source: STREAM_ROUTER(1) [58 over 104] NC */
        unsigned int  isp_fe_2__cvdr_rt__dropped_vpwr_17         : 1;  /* bit[6-6]  : source: ISP_FE_2 [57 over 104] NC */
        unsigned int  isp_fe_2__cvdr_rt__sof_vpwr_17             : 1;  /* bit[7-7]  : source: ISP_FE_2 [56 over 104] NC */
        unsigned int  stream_router_2__cvdr_rt__dropped_vpwr_19b : 1;  /* bit[8-8]  : source: STREAM_ROUTER(2) [55 over 104] NC */
        unsigned int  stream_router_2__cvdr_rt__sof_vpwr_19b     : 1;  /* bit[9-9]  : source: STREAM_ROUTER(2) [54 over 104] NC */
        unsigned int  stat3a_1__cvdr_rt__dropped_vpwr_20         : 1;  /* bit[10-10]: source: STAT3A_1 [53 over 104] NC */
        unsigned int  stat3a_1__cvdr_rt__sof_vpwr_20             : 1;  /* bit[11-11]: source: STAT3A_1 [52 over 104] NC */
        unsigned int  stat3a_2__cvdr_rt__dropped_vpwr_21         : 1;  /* bit[12-12]: source: STAT3A_2 [51 over 104] NC */
        unsigned int  stat3a_2__cvdr_rt__sof_vpwr_21             : 1;  /* bit[13-13]: source: STAT3A_2 [50 over 104] NC */
        unsigned int  stream_router_3__cvdr_rt__dropped_vpwr_22  : 1;  /* bit[14-14]: source: STREAM_ROUTER(3) [49 over 104] NC */
        unsigned int  stream_router_3__cvdr_rt__sof_vpwr_22      : 1;  /* bit[15-15]: source: STREAM_ROUTER(3) [48 over 104] NC */
        unsigned int  stream_router_4__cvdr_rt__dropped_vpwr_23  : 1;  /* bit[16-16]: source: STREAM_ROUTER(4) [47 over 104] NC */
        unsigned int  stream_router_4__cvdr_rt__sof_vpwr_23      : 1;  /* bit[17-17]: source: STREAM_ROUTER(4) [46 over 104] NC */
        unsigned int  stream_router_5__cvdr_rt__dropped_vpwr_24  : 1;  /* bit[18-18]: source: STREAM_ROUTER(5) [45 over 104] NC */
        unsigned int  stream_router_5__cvdr_rt__sof_vpwr_24      : 1;  /* bit[19-19]: source: STREAM_ROUTER(5) [44 over 104] NC */
        unsigned int  jpgenc__cvdr_rt__dropped_vpwr_25           : 1;  /* bit[20-20]: source: JPGENC [43 over 104] NC */
        unsigned int  jpgenc__cvdr_rt__sof_vpwr_25               : 1;  /* bit[21-21]: source: JPGENC [42 over 104] NC */
        unsigned int  fbdyuv_1__cvdr_rt__sof_vprd_0              : 1;  /* bit[22-22]: source: FBDYUV_1 [41 over 104] NC */
        unsigned int  fbdyuv_1__cvdr_rt__eof_vprd_0              : 1;  /* bit[23-23]: source: FBDYUV_1 [40 over 104] NC */
        unsigned int  scaler_x_2__cvdr_rt__sof_vprd_1            : 1;  /* bit[24-24]: source: SCALER_x_2 [39 over 104] NC */
        unsigned int  scaler_x_2__cvdr_rt__eof_vprd_1            : 1;  /* bit[25-25]: source: SCALER_x_2 [38 over 104] NC */
        unsigned int  isp_be_1__cvdr_rt__sof_vprd_2              : 1;  /* bit[26-26]: source: ISP_BE_1 [37 over 104] NC */
        unsigned int  isp_be_1__cvdr_rt__eof_vprd_2              : 1;  /* bit[27-27]: source: ISP_BE_1 [36 over 104] NC */
        unsigned int  isp_be_2__cvdr_rt__sof_vprd_3              : 1;  /* bit[28-28]: source: ISP_BE_2 [35 over 104] NC */
        unsigned int  isp_be_2__cvdr_rt__eof_vprd_3              : 1;  /* bit[29-29]: source: ISP_BE_2 [34 over 104] NC */
        unsigned int  itap_1_1__cvdr_rt__sof_vprd_4              : 1;  /* bit[30-30]: source: ITAP_1_1 [33 over 104] NC */
        unsigned int  itap_1_1__cvdr_rt__eof_vprd_4              : 1;  /* bit[31-31]: source: ITAP_1_1 [32 over 104] NC */
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_otap_2_2__cvdr_rt__dropped_vpwr_15_START          (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_otap_2_2__cvdr_rt__dropped_vpwr_15_END            (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_otap_2_2__cvdr_rt__sof_vpwr_15_START              (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_otap_2_2__cvdr_rt__sof_vpwr_15_END                (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_isp_fe_1__cvdr_rt__dropped_vpwr_16_START          (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_isp_fe_1__cvdr_rt__dropped_vpwr_16_END            (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_isp_fe_1__cvdr_rt__sof_vpwr_16_START              (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_isp_fe_1__cvdr_rt__sof_vpwr_16_END                (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_stream_router_1__cvdr_rt__dropped_vpwr_18b_START  (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_stream_router_1__cvdr_rt__dropped_vpwr_18b_END    (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_stream_router_1__cvdr_rt__sof_vpwr_18b_START      (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_stream_router_1__cvdr_rt__sof_vpwr_18b_END        (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_isp_fe_2__cvdr_rt__dropped_vpwr_17_START          (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_isp_fe_2__cvdr_rt__dropped_vpwr_17_END            (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_isp_fe_2__cvdr_rt__sof_vpwr_17_START              (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_isp_fe_2__cvdr_rt__sof_vpwr_17_END                (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_stream_router_2__cvdr_rt__dropped_vpwr_19b_START  (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_stream_router_2__cvdr_rt__dropped_vpwr_19b_END    (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_stream_router_2__cvdr_rt__sof_vpwr_19b_START      (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_stream_router_2__cvdr_rt__sof_vpwr_19b_END        (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_stat3a_1__cvdr_rt__dropped_vpwr_20_START          (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_stat3a_1__cvdr_rt__dropped_vpwr_20_END            (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_stat3a_1__cvdr_rt__sof_vpwr_20_START              (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_stat3a_1__cvdr_rt__sof_vpwr_20_END                (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_stat3a_2__cvdr_rt__dropped_vpwr_21_START          (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_stat3a_2__cvdr_rt__dropped_vpwr_21_END            (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_stat3a_2__cvdr_rt__sof_vpwr_21_START              (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_stat3a_2__cvdr_rt__sof_vpwr_21_END                (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_stream_router_3__cvdr_rt__dropped_vpwr_22_START   (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_stream_router_3__cvdr_rt__dropped_vpwr_22_END     (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_stream_router_3__cvdr_rt__sof_vpwr_22_START       (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_stream_router_3__cvdr_rt__sof_vpwr_22_END         (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_stream_router_4__cvdr_rt__dropped_vpwr_23_START   (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_stream_router_4__cvdr_rt__dropped_vpwr_23_END     (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_stream_router_4__cvdr_rt__sof_vpwr_23_START       (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_stream_router_4__cvdr_rt__sof_vpwr_23_END         (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_stream_router_5__cvdr_rt__dropped_vpwr_24_START   (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_stream_router_5__cvdr_rt__dropped_vpwr_24_END     (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_stream_router_5__cvdr_rt__sof_vpwr_24_START       (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_stream_router_5__cvdr_rt__sof_vpwr_24_END         (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_jpgenc__cvdr_rt__dropped_vpwr_25_START            (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_jpgenc__cvdr_rt__dropped_vpwr_25_END              (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_jpgenc__cvdr_rt__sof_vpwr_25_START                (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_jpgenc__cvdr_rt__sof_vpwr_25_END                  (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_fbdyuv_1__cvdr_rt__sof_vprd_0_START               (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_fbdyuv_1__cvdr_rt__sof_vprd_0_END                 (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_fbdyuv_1__cvdr_rt__eof_vprd_0_START               (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_fbdyuv_1__cvdr_rt__eof_vprd_0_END                 (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_scaler_x_2__cvdr_rt__sof_vprd_1_START             (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_scaler_x_2__cvdr_rt__sof_vprd_1_END               (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_scaler_x_2__cvdr_rt__eof_vprd_1_START             (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_scaler_x_2__cvdr_rt__eof_vprd_1_END               (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_isp_be_1__cvdr_rt__sof_vprd_2_START               (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_isp_be_1__cvdr_rt__sof_vprd_2_END                 (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_isp_be_1__cvdr_rt__eof_vprd_2_START               (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_isp_be_1__cvdr_rt__eof_vprd_2_END                 (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_isp_be_2__cvdr_rt__sof_vprd_3_START               (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_isp_be_2__cvdr_rt__sof_vprd_3_END                 (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_isp_be_2__cvdr_rt__eof_vprd_3_START               (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_isp_be_2__cvdr_rt__eof_vprd_3_END                 (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_itap_1_1__cvdr_rt__sof_vprd_4_START               (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_itap_1_1__cvdr_rt__sof_vprd_4_END                 (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_itap_1_1__cvdr_rt__eof_vprd_4_START               (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_1_itap_1_1__cvdr_rt__eof_vprd_4_END                 (31)


/*****************************************************************************
 结构名    : SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_UNION
 结构说明  : IRQ_MERGER_IMSC_DEBUG_2 寄存器结构定义。地址偏移量:0x40，初值:0x00000000，宽度:32
 寄存器说明: [Interrupt Mask Register] DEBUG register (bloc 2 over 3).
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  itap_2_1__cvdr_rt__sof_vprd_5 : 1;  /* bit[0-0]  : source: ITAP_2_1 [95 over 104] NC */
        unsigned int  itap_2_1__cvdr_rt__eof_vprd_5 : 1;  /* bit[1-1]  : source: ITAP_2_1 [94 over 104] NC */
        unsigned int  itap_1_2__cvdr_rt__sof_vprd_6 : 1;  /* bit[2-2]  : source: ITAP_1_2 [93 over 104] NC */
        unsigned int  itap_1_2__cvdr_rt__eof_vprd_6 : 1;  /* bit[3-3]  : source: ITAP_1_2 [92 over 104] NC */
        unsigned int  itap_2_2__cvdr_rt__sof_vprd_7 : 1;  /* bit[4-4]  : source: ITAP_2_2 [91 over 104] NC */
        unsigned int  itap_2_2__cvdr_rt__eof_vprd_7 : 1;  /* bit[5-5]  : source: ITAP_2_2 [90 over 104] NC */
        unsigned int  isp_fe_1__cvdr_rt__sof_vprd_8 : 1;  /* bit[6-6]  : source: ISP_FE_1 [89 over 104] NC */
        unsigned int  isp_fe_1__cvdr_rt__eof_vprd_8 : 1;  /* bit[7-7]  : source: ISP_FE_1 [88 over 104] NC */
        unsigned int  isp_fe_2__cvdr_rt__sof_vprd_9 : 1;  /* bit[8-8]  : source: ISP_FE_2 [87 over 104] NC */
        unsigned int  isp_fe_2__cvdr_rt__eof_vprd_9 : 1;  /* bit[9-9]  : source: ISP_FE_2 [86 over 104] NC */
        unsigned int  prescaler__start_of_frame1    : 1;  /* bit[10-10]: source: NA [85 over 104] NC */
        unsigned int  prescaler__start_of_frame2    : 1;  /* bit[11-11]: source: NA [84 over 104] NC */
        unsigned int  scaler_1_1__start_of_frame    : 1;  /* bit[12-12]: source: NA [83 over 104] NC */
        unsigned int  scaler_1_1__end_of_rescale    : 1;  /* bit[13-13]: source: NA [82 over 104] NC */
        unsigned int  scaler_2_1__start_of_frame    : 1;  /* bit[14-14]: source: NA [81 over 104] NC */
        unsigned int  scaler_2_1__end_of_rescale    : 1;  /* bit[15-15]: source: NA [80 over 104] NC */
        unsigned int  scaler_1_2__start_of_frame    : 1;  /* bit[16-16]: source: NA [79 over 104] NC */
        unsigned int  scaler_1_2__end_of_rescale    : 1;  /* bit[17-17]: source: NA [78 over 104] NC */
        unsigned int  scaler_2_2__start_of_frame    : 1;  /* bit[18-18]: source: NA [77 over 104] NC */
        unsigned int  scaler_2_2__end_of_rescale    : 1;  /* bit[19-19]: source: NA [76 over 104] NC */
        unsigned int  scaler_3__start_of_frame      : 1;  /* bit[20-20]: source: NA [75 over 104] NC */
        unsigned int  stream_router__eol_0          : 1;  /* bit[21-21]: source: NA [74 over 104] NC */
        unsigned int  stream_router__eol_1          : 1;  /* bit[22-22]: source: NA [73 over 104] NC */
        unsigned int  bas_1__start_of_frame         : 1;  /* bit[23-23]: source: NA [72 over 104] NC */
        unsigned int  bas_1__end_of_frame           : 1;  /* bit[24-24]: source: NA [71 over 104] NC */
        unsigned int  bas_2__start_of_frame         : 1;  /* bit[25-25]: source: NA [70 over 104] NC */
        unsigned int  bas_2__end_of_frame           : 1;  /* bit[26-26]: source: NA [69 over 104] NC */
        unsigned int  blc_1__frame_in               : 1;  /* bit[27-27]: source: NA [68 over 104] NC */
        unsigned int  blc_2__frame_in               : 1;  /* bit[28-28]: source: NA [67 over 104] NC */
        unsigned int  fbcraw_1__fbc_done            : 1;  /* bit[29-29]: source: NA [66 over 104] NC */
        unsigned int  fbcraw_2__fbc_done            : 1;  /* bit[30-30]: source: NA [65 over 104] NC */
        unsigned int  fbdraw_1__fbd_done            : 1;  /* bit[31-31]: source: NA [64 over 104] NC */
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_itap_2_1__cvdr_rt__sof_vprd_5_START  (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_itap_2_1__cvdr_rt__sof_vprd_5_END    (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_itap_2_1__cvdr_rt__eof_vprd_5_START  (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_itap_2_1__cvdr_rt__eof_vprd_5_END    (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_itap_1_2__cvdr_rt__sof_vprd_6_START  (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_itap_1_2__cvdr_rt__sof_vprd_6_END    (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_itap_1_2__cvdr_rt__eof_vprd_6_START  (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_itap_1_2__cvdr_rt__eof_vprd_6_END    (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_itap_2_2__cvdr_rt__sof_vprd_7_START  (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_itap_2_2__cvdr_rt__sof_vprd_7_END    (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_itap_2_2__cvdr_rt__eof_vprd_7_START  (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_itap_2_2__cvdr_rt__eof_vprd_7_END    (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_isp_fe_1__cvdr_rt__sof_vprd_8_START  (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_isp_fe_1__cvdr_rt__sof_vprd_8_END    (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_isp_fe_1__cvdr_rt__eof_vprd_8_START  (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_isp_fe_1__cvdr_rt__eof_vprd_8_END    (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_isp_fe_2__cvdr_rt__sof_vprd_9_START  (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_isp_fe_2__cvdr_rt__sof_vprd_9_END    (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_isp_fe_2__cvdr_rt__eof_vprd_9_START  (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_isp_fe_2__cvdr_rt__eof_vprd_9_END    (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_prescaler__start_of_frame1_START     (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_prescaler__start_of_frame1_END       (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_prescaler__start_of_frame2_START     (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_prescaler__start_of_frame2_END       (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_scaler_1_1__start_of_frame_START     (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_scaler_1_1__start_of_frame_END       (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_scaler_1_1__end_of_rescale_START     (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_scaler_1_1__end_of_rescale_END       (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_scaler_2_1__start_of_frame_START     (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_scaler_2_1__start_of_frame_END       (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_scaler_2_1__end_of_rescale_START     (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_scaler_2_1__end_of_rescale_END       (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_scaler_1_2__start_of_frame_START     (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_scaler_1_2__start_of_frame_END       (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_scaler_1_2__end_of_rescale_START     (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_scaler_1_2__end_of_rescale_END       (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_scaler_2_2__start_of_frame_START     (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_scaler_2_2__start_of_frame_END       (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_scaler_2_2__end_of_rescale_START     (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_scaler_2_2__end_of_rescale_END       (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_scaler_3__start_of_frame_START       (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_scaler_3__start_of_frame_END         (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_stream_router__eol_0_START           (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_stream_router__eol_0_END             (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_stream_router__eol_1_START           (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_stream_router__eol_1_END             (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_bas_1__start_of_frame_START          (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_bas_1__start_of_frame_END            (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_bas_1__end_of_frame_START            (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_bas_1__end_of_frame_END              (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_bas_2__start_of_frame_START          (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_bas_2__start_of_frame_END            (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_bas_2__end_of_frame_START            (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_bas_2__end_of_frame_END              (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_blc_1__frame_in_START                (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_blc_1__frame_in_END                  (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_blc_2__frame_in_START                (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_blc_2__frame_in_END                  (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_fbcraw_1__fbc_done_START             (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_fbcraw_1__fbc_done_END               (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_fbcraw_2__fbc_done_START             (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_fbcraw_2__fbc_done_END               (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_fbdraw_1__fbd_done_START             (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_2_fbdraw_1__fbd_done_END               (31)


/*****************************************************************************
 结构名    : SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_UNION
 结构说明  : IRQ_MERGER_RIS_DEBUG_2 寄存器结构定义。地址偏移量:0x44，初值:0x00000000，宽度:32
 寄存器说明: [Raw Interrupt Status Register] DEBUG register (bloc 2 over 3).
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  itap_2_1__cvdr_rt__sof_vprd_5 : 1;  /* bit[0-0]  : source: ITAP_2_1 [95 over 104] NC */
        unsigned int  itap_2_1__cvdr_rt__eof_vprd_5 : 1;  /* bit[1-1]  : source: ITAP_2_1 [94 over 104] NC */
        unsigned int  itap_1_2__cvdr_rt__sof_vprd_6 : 1;  /* bit[2-2]  : source: ITAP_1_2 [93 over 104] NC */
        unsigned int  itap_1_2__cvdr_rt__eof_vprd_6 : 1;  /* bit[3-3]  : source: ITAP_1_2 [92 over 104] NC */
        unsigned int  itap_2_2__cvdr_rt__sof_vprd_7 : 1;  /* bit[4-4]  : source: ITAP_2_2 [91 over 104] NC */
        unsigned int  itap_2_2__cvdr_rt__eof_vprd_7 : 1;  /* bit[5-5]  : source: ITAP_2_2 [90 over 104] NC */
        unsigned int  isp_fe_1__cvdr_rt__sof_vprd_8 : 1;  /* bit[6-6]  : source: ISP_FE_1 [89 over 104] NC */
        unsigned int  isp_fe_1__cvdr_rt__eof_vprd_8 : 1;  /* bit[7-7]  : source: ISP_FE_1 [88 over 104] NC */
        unsigned int  isp_fe_2__cvdr_rt__sof_vprd_9 : 1;  /* bit[8-8]  : source: ISP_FE_2 [87 over 104] NC */
        unsigned int  isp_fe_2__cvdr_rt__eof_vprd_9 : 1;  /* bit[9-9]  : source: ISP_FE_2 [86 over 104] NC */
        unsigned int  prescaler__start_of_frame1    : 1;  /* bit[10-10]: source: NA [85 over 104] NC */
        unsigned int  prescaler__start_of_frame2    : 1;  /* bit[11-11]: source: NA [84 over 104] NC */
        unsigned int  scaler_1_1__start_of_frame    : 1;  /* bit[12-12]: source: NA [83 over 104] NC */
        unsigned int  scaler_1_1__end_of_rescale    : 1;  /* bit[13-13]: source: NA [82 over 104] NC */
        unsigned int  scaler_2_1__start_of_frame    : 1;  /* bit[14-14]: source: NA [81 over 104] NC */
        unsigned int  scaler_2_1__end_of_rescale    : 1;  /* bit[15-15]: source: NA [80 over 104] NC */
        unsigned int  scaler_1_2__start_of_frame    : 1;  /* bit[16-16]: source: NA [79 over 104] NC */
        unsigned int  scaler_1_2__end_of_rescale    : 1;  /* bit[17-17]: source: NA [78 over 104] NC */
        unsigned int  scaler_2_2__start_of_frame    : 1;  /* bit[18-18]: source: NA [77 over 104] NC */
        unsigned int  scaler_2_2__end_of_rescale    : 1;  /* bit[19-19]: source: NA [76 over 104] NC */
        unsigned int  scaler_3__start_of_frame      : 1;  /* bit[20-20]: source: NA [75 over 104] NC */
        unsigned int  stream_router__eol_0          : 1;  /* bit[21-21]: source: NA [74 over 104] NC */
        unsigned int  stream_router__eol_1          : 1;  /* bit[22-22]: source: NA [73 over 104] NC */
        unsigned int  bas_1__start_of_frame         : 1;  /* bit[23-23]: source: NA [72 over 104] NC */
        unsigned int  bas_1__end_of_frame           : 1;  /* bit[24-24]: source: NA [71 over 104] NC */
        unsigned int  bas_2__start_of_frame         : 1;  /* bit[25-25]: source: NA [70 over 104] NC */
        unsigned int  bas_2__end_of_frame           : 1;  /* bit[26-26]: source: NA [69 over 104] NC */
        unsigned int  blc_1__frame_in               : 1;  /* bit[27-27]: source: NA [68 over 104] NC */
        unsigned int  blc_2__frame_in               : 1;  /* bit[28-28]: source: NA [67 over 104] NC */
        unsigned int  fbcraw_1__fbc_done            : 1;  /* bit[29-29]: source: NA [66 over 104] NC */
        unsigned int  fbcraw_2__fbc_done            : 1;  /* bit[30-30]: source: NA [65 over 104] NC */
        unsigned int  fbdraw_1__fbd_done            : 1;  /* bit[31-31]: source: NA [64 over 104] NC */
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_itap_2_1__cvdr_rt__sof_vprd_5_START  (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_itap_2_1__cvdr_rt__sof_vprd_5_END    (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_itap_2_1__cvdr_rt__eof_vprd_5_START  (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_itap_2_1__cvdr_rt__eof_vprd_5_END    (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_itap_1_2__cvdr_rt__sof_vprd_6_START  (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_itap_1_2__cvdr_rt__sof_vprd_6_END    (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_itap_1_2__cvdr_rt__eof_vprd_6_START  (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_itap_1_2__cvdr_rt__eof_vprd_6_END    (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_itap_2_2__cvdr_rt__sof_vprd_7_START  (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_itap_2_2__cvdr_rt__sof_vprd_7_END    (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_itap_2_2__cvdr_rt__eof_vprd_7_START  (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_itap_2_2__cvdr_rt__eof_vprd_7_END    (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_isp_fe_1__cvdr_rt__sof_vprd_8_START  (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_isp_fe_1__cvdr_rt__sof_vprd_8_END    (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_isp_fe_1__cvdr_rt__eof_vprd_8_START  (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_isp_fe_1__cvdr_rt__eof_vprd_8_END    (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_isp_fe_2__cvdr_rt__sof_vprd_9_START  (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_isp_fe_2__cvdr_rt__sof_vprd_9_END    (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_isp_fe_2__cvdr_rt__eof_vprd_9_START  (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_isp_fe_2__cvdr_rt__eof_vprd_9_END    (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_prescaler__start_of_frame1_START     (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_prescaler__start_of_frame1_END       (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_prescaler__start_of_frame2_START     (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_prescaler__start_of_frame2_END       (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_scaler_1_1__start_of_frame_START     (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_scaler_1_1__start_of_frame_END       (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_scaler_1_1__end_of_rescale_START     (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_scaler_1_1__end_of_rescale_END       (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_scaler_2_1__start_of_frame_START     (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_scaler_2_1__start_of_frame_END       (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_scaler_2_1__end_of_rescale_START     (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_scaler_2_1__end_of_rescale_END       (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_scaler_1_2__start_of_frame_START     (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_scaler_1_2__start_of_frame_END       (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_scaler_1_2__end_of_rescale_START     (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_scaler_1_2__end_of_rescale_END       (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_scaler_2_2__start_of_frame_START     (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_scaler_2_2__start_of_frame_END       (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_scaler_2_2__end_of_rescale_START     (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_scaler_2_2__end_of_rescale_END       (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_scaler_3__start_of_frame_START       (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_scaler_3__start_of_frame_END         (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_stream_router__eol_0_START           (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_stream_router__eol_0_END             (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_stream_router__eol_1_START           (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_stream_router__eol_1_END             (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_bas_1__start_of_frame_START          (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_bas_1__start_of_frame_END            (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_bas_1__end_of_frame_START            (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_bas_1__end_of_frame_END              (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_bas_2__start_of_frame_START          (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_bas_2__start_of_frame_END            (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_bas_2__end_of_frame_START            (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_bas_2__end_of_frame_END              (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_blc_1__frame_in_START                (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_blc_1__frame_in_END                  (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_blc_2__frame_in_START                (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_blc_2__frame_in_END                  (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_fbcraw_1__fbc_done_START             (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_fbcraw_1__fbc_done_END               (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_fbcraw_2__fbc_done_START             (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_fbcraw_2__fbc_done_END               (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_fbdraw_1__fbd_done_START             (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_2_fbdraw_1__fbd_done_END               (31)


/*****************************************************************************
 结构名    : SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_UNION
 结构说明  : IRQ_MERGER_MIS_DEBUG_2 寄存器结构定义。地址偏移量:0x48，初值:0x00000000，宽度:32
 寄存器说明: [Masked Interrupt Status Register] DEBUG register (bloc 2 over 3).
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  itap_2_1__cvdr_rt__sof_vprd_5 : 1;  /* bit[0-0]  : source: ITAP_2_1 [95 over 104] NC */
        unsigned int  itap_2_1__cvdr_rt__eof_vprd_5 : 1;  /* bit[1-1]  : source: ITAP_2_1 [94 over 104] NC */
        unsigned int  itap_1_2__cvdr_rt__sof_vprd_6 : 1;  /* bit[2-2]  : source: ITAP_1_2 [93 over 104] NC */
        unsigned int  itap_1_2__cvdr_rt__eof_vprd_6 : 1;  /* bit[3-3]  : source: ITAP_1_2 [92 over 104] NC */
        unsigned int  itap_2_2__cvdr_rt__sof_vprd_7 : 1;  /* bit[4-4]  : source: ITAP_2_2 [91 over 104] NC */
        unsigned int  itap_2_2__cvdr_rt__eof_vprd_7 : 1;  /* bit[5-5]  : source: ITAP_2_2 [90 over 104] NC */
        unsigned int  isp_fe_1__cvdr_rt__sof_vprd_8 : 1;  /* bit[6-6]  : source: ISP_FE_1 [89 over 104] NC */
        unsigned int  isp_fe_1__cvdr_rt__eof_vprd_8 : 1;  /* bit[7-7]  : source: ISP_FE_1 [88 over 104] NC */
        unsigned int  isp_fe_2__cvdr_rt__sof_vprd_9 : 1;  /* bit[8-8]  : source: ISP_FE_2 [87 over 104] NC */
        unsigned int  isp_fe_2__cvdr_rt__eof_vprd_9 : 1;  /* bit[9-9]  : source: ISP_FE_2 [86 over 104] NC */
        unsigned int  prescaler__start_of_frame1    : 1;  /* bit[10-10]: source: NA [85 over 104] NC */
        unsigned int  prescaler__start_of_frame2    : 1;  /* bit[11-11]: source: NA [84 over 104] NC */
        unsigned int  scaler_1_1__start_of_frame    : 1;  /* bit[12-12]: source: NA [83 over 104] NC */
        unsigned int  scaler_1_1__end_of_rescale    : 1;  /* bit[13-13]: source: NA [82 over 104] NC */
        unsigned int  scaler_2_1__start_of_frame    : 1;  /* bit[14-14]: source: NA [81 over 104] NC */
        unsigned int  scaler_2_1__end_of_rescale    : 1;  /* bit[15-15]: source: NA [80 over 104] NC */
        unsigned int  scaler_1_2__start_of_frame    : 1;  /* bit[16-16]: source: NA [79 over 104] NC */
        unsigned int  scaler_1_2__end_of_rescale    : 1;  /* bit[17-17]: source: NA [78 over 104] NC */
        unsigned int  scaler_2_2__start_of_frame    : 1;  /* bit[18-18]: source: NA [77 over 104] NC */
        unsigned int  scaler_2_2__end_of_rescale    : 1;  /* bit[19-19]: source: NA [76 over 104] NC */
        unsigned int  scaler_3__start_of_frame      : 1;  /* bit[20-20]: source: NA [75 over 104] NC */
        unsigned int  stream_router__eol_0          : 1;  /* bit[21-21]: source: NA [74 over 104] NC */
        unsigned int  stream_router__eol_1          : 1;  /* bit[22-22]: source: NA [73 over 104] NC */
        unsigned int  bas_1__start_of_frame         : 1;  /* bit[23-23]: source: NA [72 over 104] NC */
        unsigned int  bas_1__end_of_frame           : 1;  /* bit[24-24]: source: NA [71 over 104] NC */
        unsigned int  bas_2__start_of_frame         : 1;  /* bit[25-25]: source: NA [70 over 104] NC */
        unsigned int  bas_2__end_of_frame           : 1;  /* bit[26-26]: source: NA [69 over 104] NC */
        unsigned int  blc_1__frame_in               : 1;  /* bit[27-27]: source: NA [68 over 104] NC */
        unsigned int  blc_2__frame_in               : 1;  /* bit[28-28]: source: NA [67 over 104] NC */
        unsigned int  fbcraw_1__fbc_done            : 1;  /* bit[29-29]: source: NA [66 over 104] NC */
        unsigned int  fbcraw_2__fbc_done            : 1;  /* bit[30-30]: source: NA [65 over 104] NC */
        unsigned int  fbdraw_1__fbd_done            : 1;  /* bit[31-31]: source: NA [64 over 104] NC */
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_itap_2_1__cvdr_rt__sof_vprd_5_START  (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_itap_2_1__cvdr_rt__sof_vprd_5_END    (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_itap_2_1__cvdr_rt__eof_vprd_5_START  (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_itap_2_1__cvdr_rt__eof_vprd_5_END    (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_itap_1_2__cvdr_rt__sof_vprd_6_START  (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_itap_1_2__cvdr_rt__sof_vprd_6_END    (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_itap_1_2__cvdr_rt__eof_vprd_6_START  (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_itap_1_2__cvdr_rt__eof_vprd_6_END    (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_itap_2_2__cvdr_rt__sof_vprd_7_START  (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_itap_2_2__cvdr_rt__sof_vprd_7_END    (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_itap_2_2__cvdr_rt__eof_vprd_7_START  (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_itap_2_2__cvdr_rt__eof_vprd_7_END    (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_isp_fe_1__cvdr_rt__sof_vprd_8_START  (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_isp_fe_1__cvdr_rt__sof_vprd_8_END    (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_isp_fe_1__cvdr_rt__eof_vprd_8_START  (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_isp_fe_1__cvdr_rt__eof_vprd_8_END    (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_isp_fe_2__cvdr_rt__sof_vprd_9_START  (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_isp_fe_2__cvdr_rt__sof_vprd_9_END    (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_isp_fe_2__cvdr_rt__eof_vprd_9_START  (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_isp_fe_2__cvdr_rt__eof_vprd_9_END    (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_prescaler__start_of_frame1_START     (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_prescaler__start_of_frame1_END       (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_prescaler__start_of_frame2_START     (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_prescaler__start_of_frame2_END       (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_scaler_1_1__start_of_frame_START     (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_scaler_1_1__start_of_frame_END       (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_scaler_1_1__end_of_rescale_START     (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_scaler_1_1__end_of_rescale_END       (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_scaler_2_1__start_of_frame_START     (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_scaler_2_1__start_of_frame_END       (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_scaler_2_1__end_of_rescale_START     (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_scaler_2_1__end_of_rescale_END       (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_scaler_1_2__start_of_frame_START     (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_scaler_1_2__start_of_frame_END       (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_scaler_1_2__end_of_rescale_START     (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_scaler_1_2__end_of_rescale_END       (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_scaler_2_2__start_of_frame_START     (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_scaler_2_2__start_of_frame_END       (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_scaler_2_2__end_of_rescale_START     (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_scaler_2_2__end_of_rescale_END       (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_scaler_3__start_of_frame_START       (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_scaler_3__start_of_frame_END         (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_stream_router__eol_0_START           (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_stream_router__eol_0_END             (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_stream_router__eol_1_START           (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_stream_router__eol_1_END             (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_bas_1__start_of_frame_START          (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_bas_1__start_of_frame_END            (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_bas_1__end_of_frame_START            (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_bas_1__end_of_frame_END              (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_bas_2__start_of_frame_START          (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_bas_2__start_of_frame_END            (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_bas_2__end_of_frame_START            (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_bas_2__end_of_frame_END              (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_blc_1__frame_in_START                (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_blc_1__frame_in_END                  (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_blc_2__frame_in_START                (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_blc_2__frame_in_END                  (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_fbcraw_1__fbc_done_START             (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_fbcraw_1__fbc_done_END               (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_fbcraw_2__fbc_done_START             (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_fbcraw_2__fbc_done_END               (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_fbdraw_1__fbd_done_START             (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_2_fbdraw_1__fbd_done_END               (31)


/*****************************************************************************
 结构名    : SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_UNION
 结构说明  : IRQ_MERGER_ICR_DEBUG_2 寄存器结构定义。地址偏移量:0x4C，初值:0x00000000，宽度:32
 寄存器说明: [Interrupt Clear Register] DEBUG register (bloc 2 over 3).
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  itap_2_1__cvdr_rt__sof_vprd_5 : 1;  /* bit[0-0]  : source: ITAP_2_1 [95 over 104] NC */
        unsigned int  itap_2_1__cvdr_rt__eof_vprd_5 : 1;  /* bit[1-1]  : source: ITAP_2_1 [94 over 104] NC */
        unsigned int  itap_1_2__cvdr_rt__sof_vprd_6 : 1;  /* bit[2-2]  : source: ITAP_1_2 [93 over 104] NC */
        unsigned int  itap_1_2__cvdr_rt__eof_vprd_6 : 1;  /* bit[3-3]  : source: ITAP_1_2 [92 over 104] NC */
        unsigned int  itap_2_2__cvdr_rt__sof_vprd_7 : 1;  /* bit[4-4]  : source: ITAP_2_2 [91 over 104] NC */
        unsigned int  itap_2_2__cvdr_rt__eof_vprd_7 : 1;  /* bit[5-5]  : source: ITAP_2_2 [90 over 104] NC */
        unsigned int  isp_fe_1__cvdr_rt__sof_vprd_8 : 1;  /* bit[6-6]  : source: ISP_FE_1 [89 over 104] NC */
        unsigned int  isp_fe_1__cvdr_rt__eof_vprd_8 : 1;  /* bit[7-7]  : source: ISP_FE_1 [88 over 104] NC */
        unsigned int  isp_fe_2__cvdr_rt__sof_vprd_9 : 1;  /* bit[8-8]  : source: ISP_FE_2 [87 over 104] NC */
        unsigned int  isp_fe_2__cvdr_rt__eof_vprd_9 : 1;  /* bit[9-9]  : source: ISP_FE_2 [86 over 104] NC */
        unsigned int  prescaler__start_of_frame1    : 1;  /* bit[10-10]: source: NA [85 over 104] NC */
        unsigned int  prescaler__start_of_frame2    : 1;  /* bit[11-11]: source: NA [84 over 104] NC */
        unsigned int  scaler_1_1__start_of_frame    : 1;  /* bit[12-12]: source: NA [83 over 104] NC */
        unsigned int  scaler_1_1__end_of_rescale    : 1;  /* bit[13-13]: source: NA [82 over 104] NC */
        unsigned int  scaler_2_1__start_of_frame    : 1;  /* bit[14-14]: source: NA [81 over 104] NC */
        unsigned int  scaler_2_1__end_of_rescale    : 1;  /* bit[15-15]: source: NA [80 over 104] NC */
        unsigned int  scaler_1_2__start_of_frame    : 1;  /* bit[16-16]: source: NA [79 over 104] NC */
        unsigned int  scaler_1_2__end_of_rescale    : 1;  /* bit[17-17]: source: NA [78 over 104] NC */
        unsigned int  scaler_2_2__start_of_frame    : 1;  /* bit[18-18]: source: NA [77 over 104] NC */
        unsigned int  scaler_2_2__end_of_rescale    : 1;  /* bit[19-19]: source: NA [76 over 104] NC */
        unsigned int  scaler_3__start_of_frame      : 1;  /* bit[20-20]: source: NA [75 over 104] NC */
        unsigned int  stream_router__eol_0          : 1;  /* bit[21-21]: source: NA [74 over 104] NC */
        unsigned int  stream_router__eol_1          : 1;  /* bit[22-22]: source: NA [73 over 104] NC */
        unsigned int  bas_1__start_of_frame         : 1;  /* bit[23-23]: source: NA [72 over 104] NC */
        unsigned int  bas_1__end_of_frame           : 1;  /* bit[24-24]: source: NA [71 over 104] NC */
        unsigned int  bas_2__start_of_frame         : 1;  /* bit[25-25]: source: NA [70 over 104] NC */
        unsigned int  bas_2__end_of_frame           : 1;  /* bit[26-26]: source: NA [69 over 104] NC */
        unsigned int  blc_1__frame_in               : 1;  /* bit[27-27]: source: NA [68 over 104] NC */
        unsigned int  blc_2__frame_in               : 1;  /* bit[28-28]: source: NA [67 over 104] NC */
        unsigned int  fbcraw_1__fbc_done            : 1;  /* bit[29-29]: source: NA [66 over 104] NC */
        unsigned int  fbcraw_2__fbc_done            : 1;  /* bit[30-30]: source: NA [65 over 104] NC */
        unsigned int  fbdraw_1__fbd_done            : 1;  /* bit[31-31]: source: NA [64 over 104] NC */
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_itap_2_1__cvdr_rt__sof_vprd_5_START  (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_itap_2_1__cvdr_rt__sof_vprd_5_END    (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_itap_2_1__cvdr_rt__eof_vprd_5_START  (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_itap_2_1__cvdr_rt__eof_vprd_5_END    (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_itap_1_2__cvdr_rt__sof_vprd_6_START  (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_itap_1_2__cvdr_rt__sof_vprd_6_END    (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_itap_1_2__cvdr_rt__eof_vprd_6_START  (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_itap_1_2__cvdr_rt__eof_vprd_6_END    (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_itap_2_2__cvdr_rt__sof_vprd_7_START  (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_itap_2_2__cvdr_rt__sof_vprd_7_END    (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_itap_2_2__cvdr_rt__eof_vprd_7_START  (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_itap_2_2__cvdr_rt__eof_vprd_7_END    (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_isp_fe_1__cvdr_rt__sof_vprd_8_START  (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_isp_fe_1__cvdr_rt__sof_vprd_8_END    (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_isp_fe_1__cvdr_rt__eof_vprd_8_START  (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_isp_fe_1__cvdr_rt__eof_vprd_8_END    (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_isp_fe_2__cvdr_rt__sof_vprd_9_START  (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_isp_fe_2__cvdr_rt__sof_vprd_9_END    (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_isp_fe_2__cvdr_rt__eof_vprd_9_START  (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_isp_fe_2__cvdr_rt__eof_vprd_9_END    (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_prescaler__start_of_frame1_START     (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_prescaler__start_of_frame1_END       (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_prescaler__start_of_frame2_START     (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_prescaler__start_of_frame2_END       (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_scaler_1_1__start_of_frame_START     (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_scaler_1_1__start_of_frame_END       (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_scaler_1_1__end_of_rescale_START     (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_scaler_1_1__end_of_rescale_END       (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_scaler_2_1__start_of_frame_START     (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_scaler_2_1__start_of_frame_END       (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_scaler_2_1__end_of_rescale_START     (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_scaler_2_1__end_of_rescale_END       (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_scaler_1_2__start_of_frame_START     (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_scaler_1_2__start_of_frame_END       (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_scaler_1_2__end_of_rescale_START     (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_scaler_1_2__end_of_rescale_END       (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_scaler_2_2__start_of_frame_START     (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_scaler_2_2__start_of_frame_END       (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_scaler_2_2__end_of_rescale_START     (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_scaler_2_2__end_of_rescale_END       (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_scaler_3__start_of_frame_START       (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_scaler_3__start_of_frame_END         (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_stream_router__eol_0_START           (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_stream_router__eol_0_END             (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_stream_router__eol_1_START           (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_stream_router__eol_1_END             (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_bas_1__start_of_frame_START          (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_bas_1__start_of_frame_END            (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_bas_1__end_of_frame_START            (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_bas_1__end_of_frame_END              (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_bas_2__start_of_frame_START          (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_bas_2__start_of_frame_END            (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_bas_2__end_of_frame_START            (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_bas_2__end_of_frame_END              (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_blc_1__frame_in_START                (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_blc_1__frame_in_END                  (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_blc_2__frame_in_START                (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_blc_2__frame_in_END                  (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_fbcraw_1__fbc_done_START             (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_fbcraw_1__fbc_done_END               (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_fbcraw_2__fbc_done_START             (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_fbcraw_2__fbc_done_END               (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_fbdraw_1__fbd_done_START             (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_2_fbdraw_1__fbd_done_END               (31)


/*****************************************************************************
 结构名    : SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_UNION
 结构说明  : IRQ_MERGER_ISR_DEBUG_2 寄存器结构定义。地址偏移量:0x50，初值:0x00000000，宽度:32
 寄存器说明: [Interrupt Set Register] DEBUG register (bloc 2 over 3).
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  itap_2_1__cvdr_rt__sof_vprd_5 : 1;  /* bit[0-0]  : source: ITAP_2_1 [95 over 104] NC */
        unsigned int  itap_2_1__cvdr_rt__eof_vprd_5 : 1;  /* bit[1-1]  : source: ITAP_2_1 [94 over 104] NC */
        unsigned int  itap_1_2__cvdr_rt__sof_vprd_6 : 1;  /* bit[2-2]  : source: ITAP_1_2 [93 over 104] NC */
        unsigned int  itap_1_2__cvdr_rt__eof_vprd_6 : 1;  /* bit[3-3]  : source: ITAP_1_2 [92 over 104] NC */
        unsigned int  itap_2_2__cvdr_rt__sof_vprd_7 : 1;  /* bit[4-4]  : source: ITAP_2_2 [91 over 104] NC */
        unsigned int  itap_2_2__cvdr_rt__eof_vprd_7 : 1;  /* bit[5-5]  : source: ITAP_2_2 [90 over 104] NC */
        unsigned int  isp_fe_1__cvdr_rt__sof_vprd_8 : 1;  /* bit[6-6]  : source: ISP_FE_1 [89 over 104] NC */
        unsigned int  isp_fe_1__cvdr_rt__eof_vprd_8 : 1;  /* bit[7-7]  : source: ISP_FE_1 [88 over 104] NC */
        unsigned int  isp_fe_2__cvdr_rt__sof_vprd_9 : 1;  /* bit[8-8]  : source: ISP_FE_2 [87 over 104] NC */
        unsigned int  isp_fe_2__cvdr_rt__eof_vprd_9 : 1;  /* bit[9-9]  : source: ISP_FE_2 [86 over 104] NC */
        unsigned int  prescaler__start_of_frame1    : 1;  /* bit[10-10]: source: NA [85 over 104] NC */
        unsigned int  prescaler__start_of_frame2    : 1;  /* bit[11-11]: source: NA [84 over 104] NC */
        unsigned int  scaler_1_1__start_of_frame    : 1;  /* bit[12-12]: source: NA [83 over 104] NC */
        unsigned int  scaler_1_1__end_of_rescale    : 1;  /* bit[13-13]: source: NA [82 over 104] NC */
        unsigned int  scaler_2_1__start_of_frame    : 1;  /* bit[14-14]: source: NA [81 over 104] NC */
        unsigned int  scaler_2_1__end_of_rescale    : 1;  /* bit[15-15]: source: NA [80 over 104] NC */
        unsigned int  scaler_1_2__start_of_frame    : 1;  /* bit[16-16]: source: NA [79 over 104] NC */
        unsigned int  scaler_1_2__end_of_rescale    : 1;  /* bit[17-17]: source: NA [78 over 104] NC */
        unsigned int  scaler_2_2__start_of_frame    : 1;  /* bit[18-18]: source: NA [77 over 104] NC */
        unsigned int  scaler_2_2__end_of_rescale    : 1;  /* bit[19-19]: source: NA [76 over 104] NC */
        unsigned int  scaler_3__start_of_frame      : 1;  /* bit[20-20]: source: NA [75 over 104] NC */
        unsigned int  stream_router__eol_0          : 1;  /* bit[21-21]: source: NA [74 over 104] NC */
        unsigned int  stream_router__eol_1          : 1;  /* bit[22-22]: source: NA [73 over 104] NC */
        unsigned int  bas_1__start_of_frame         : 1;  /* bit[23-23]: source: NA [72 over 104] NC */
        unsigned int  bas_1__end_of_frame           : 1;  /* bit[24-24]: source: NA [71 over 104] NC */
        unsigned int  bas_2__start_of_frame         : 1;  /* bit[25-25]: source: NA [70 over 104] NC */
        unsigned int  bas_2__end_of_frame           : 1;  /* bit[26-26]: source: NA [69 over 104] NC */
        unsigned int  blc_1__frame_in               : 1;  /* bit[27-27]: source: NA [68 over 104] NC */
        unsigned int  blc_2__frame_in               : 1;  /* bit[28-28]: source: NA [67 over 104] NC */
        unsigned int  fbcraw_1__fbc_done            : 1;  /* bit[29-29]: source: NA [66 over 104] NC */
        unsigned int  fbcraw_2__fbc_done            : 1;  /* bit[30-30]: source: NA [65 over 104] NC */
        unsigned int  fbdraw_1__fbd_done            : 1;  /* bit[31-31]: source: NA [64 over 104] NC */
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_itap_2_1__cvdr_rt__sof_vprd_5_START  (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_itap_2_1__cvdr_rt__sof_vprd_5_END    (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_itap_2_1__cvdr_rt__eof_vprd_5_START  (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_itap_2_1__cvdr_rt__eof_vprd_5_END    (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_itap_1_2__cvdr_rt__sof_vprd_6_START  (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_itap_1_2__cvdr_rt__sof_vprd_6_END    (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_itap_1_2__cvdr_rt__eof_vprd_6_START  (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_itap_1_2__cvdr_rt__eof_vprd_6_END    (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_itap_2_2__cvdr_rt__sof_vprd_7_START  (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_itap_2_2__cvdr_rt__sof_vprd_7_END    (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_itap_2_2__cvdr_rt__eof_vprd_7_START  (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_itap_2_2__cvdr_rt__eof_vprd_7_END    (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_isp_fe_1__cvdr_rt__sof_vprd_8_START  (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_isp_fe_1__cvdr_rt__sof_vprd_8_END    (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_isp_fe_1__cvdr_rt__eof_vprd_8_START  (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_isp_fe_1__cvdr_rt__eof_vprd_8_END    (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_isp_fe_2__cvdr_rt__sof_vprd_9_START  (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_isp_fe_2__cvdr_rt__sof_vprd_9_END    (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_isp_fe_2__cvdr_rt__eof_vprd_9_START  (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_isp_fe_2__cvdr_rt__eof_vprd_9_END    (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_prescaler__start_of_frame1_START     (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_prescaler__start_of_frame1_END       (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_prescaler__start_of_frame2_START     (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_prescaler__start_of_frame2_END       (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_scaler_1_1__start_of_frame_START     (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_scaler_1_1__start_of_frame_END       (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_scaler_1_1__end_of_rescale_START     (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_scaler_1_1__end_of_rescale_END       (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_scaler_2_1__start_of_frame_START     (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_scaler_2_1__start_of_frame_END       (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_scaler_2_1__end_of_rescale_START     (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_scaler_2_1__end_of_rescale_END       (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_scaler_1_2__start_of_frame_START     (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_scaler_1_2__start_of_frame_END       (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_scaler_1_2__end_of_rescale_START     (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_scaler_1_2__end_of_rescale_END       (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_scaler_2_2__start_of_frame_START     (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_scaler_2_2__start_of_frame_END       (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_scaler_2_2__end_of_rescale_START     (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_scaler_2_2__end_of_rescale_END       (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_scaler_3__start_of_frame_START       (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_scaler_3__start_of_frame_END         (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_stream_router__eol_0_START           (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_stream_router__eol_0_END             (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_stream_router__eol_1_START           (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_stream_router__eol_1_END             (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_bas_1__start_of_frame_START          (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_bas_1__start_of_frame_END            (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_bas_1__end_of_frame_START            (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_bas_1__end_of_frame_END              (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_bas_2__start_of_frame_START          (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_bas_2__start_of_frame_END            (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_bas_2__end_of_frame_START            (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_bas_2__end_of_frame_END              (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_blc_1__frame_in_START                (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_blc_1__frame_in_END                  (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_blc_2__frame_in_START                (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_blc_2__frame_in_END                  (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_fbcraw_1__fbc_done_START             (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_fbcraw_1__fbc_done_END               (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_fbcraw_2__fbc_done_START             (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_fbcraw_2__fbc_done_END               (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_fbdraw_1__fbd_done_START             (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_2_fbdraw_1__fbd_done_END               (31)


/*****************************************************************************
 结构名    : SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_3_UNION
 结构说明  : IRQ_MERGER_IMSC_DEBUG_3 寄存器结构定义。地址偏移量:0x60，初值:0x00000000，宽度:32
 寄存器说明: [Interrupt Mask Register] DEBUG register (bloc 3 over 3).
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fbdraw_2__fbd_done             : 1;  /* bit[0-0]  : source: NA [127 over 104] NC */
        unsigned int  fbcyuv_1__fbc_done             : 1;  /* bit[1-1]  : source: NA [126 over 104] NC */
        unsigned int  reserved_0                     : 1;  /* bit[2-2]  : source: NA [125 over 104] NC */
        unsigned int  fbdyuv_1__fbd_done             : 1;  /* bit[3-3]  : source: NA [124 over 104] NC */
        unsigned int  reserved_1                     : 1;  /* bit[4-4]  : source: NA [123 over 104] NC */
        unsigned int  tnr_1__frame_filtering_done    : 1;  /* bit[5-5]  : source: NA [122 over 104] NC */
        unsigned int  flash__flash_cap               : 1;  /* bit[6-6]  : source: NA [121 over 104] NC */
        unsigned int  otap_2_1__cvdr_rt__eol_vpwr_14 : 1;  /* bit[7-7]  : source: OTAP_2_1 [120 over 104] NC */
        unsigned int  otap_2_2__cvdr_rt__eol_vpwr_15 : 1;  /* bit[8-8]  : source: OTAP_2_2 [119 over 104] NC */
        unsigned int  reserved_2                     : 1;  /* bit[9-9]  : - */
        unsigned int  reserved_3                     : 1;  /* bit[10-10]: - */
        unsigned int  reserved_4                     : 1;  /* bit[11-11]: - */
        unsigned int  reserved_5                     : 1;  /* bit[12-12]: - */
        unsigned int  reserved_6                     : 1;  /* bit[13-13]: - */
        unsigned int  reserved_7                     : 1;  /* bit[14-14]: - */
        unsigned int  reserved_8                     : 1;  /* bit[15-15]: - */
        unsigned int  reserved_9                     : 1;  /* bit[16-16]: - */
        unsigned int  reserved_10                    : 1;  /* bit[17-17]: - */
        unsigned int  reserved_11                    : 1;  /* bit[18-18]: - */
        unsigned int  reserved_12                    : 1;  /* bit[19-19]: - */
        unsigned int  reserved_13                    : 1;  /* bit[20-20]: - */
        unsigned int  reserved_14                    : 1;  /* bit[21-21]: - */
        unsigned int  reserved_15                    : 1;  /* bit[22-22]: - */
        unsigned int  reserved_16                    : 1;  /* bit[23-23]: - */
        unsigned int  reserved_17                    : 1;  /* bit[24-24]: - */
        unsigned int  reserved_18                    : 1;  /* bit[25-25]: - */
        unsigned int  reserved_19                    : 1;  /* bit[26-26]: - */
        unsigned int  reserved_20                    : 1;  /* bit[27-27]: - */
        unsigned int  reserved_21                    : 1;  /* bit[28-28]: - */
        unsigned int  reserved_22                    : 1;  /* bit[29-29]: - */
        unsigned int  reserved_23                    : 1;  /* bit[30-30]: - */
        unsigned int  reserved_24                    : 1;  /* bit[31-31]: - */
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_3_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_3_fbdraw_2__fbd_done_START              (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_3_fbdraw_2__fbd_done_END                (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_3_fbcyuv_1__fbc_done_START              (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_3_fbcyuv_1__fbc_done_END                (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_3_fbdyuv_1__fbd_done_START              (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_3_fbdyuv_1__fbd_done_END                (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_3_tnr_1__frame_filtering_done_START     (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_3_tnr_1__frame_filtering_done_END       (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_3_flash__flash_cap_START                (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_3_flash__flash_cap_END                  (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_3_otap_2_1__cvdr_rt__eol_vpwr_14_START  (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_3_otap_2_1__cvdr_rt__eol_vpwr_14_END    (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_3_otap_2_2__cvdr_rt__eol_vpwr_15_START  (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_DEBUG_3_otap_2_2__cvdr_rt__eol_vpwr_15_END    (8)


/*****************************************************************************
 结构名    : SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_3_UNION
 结构说明  : IRQ_MERGER_RIS_DEBUG_3 寄存器结构定义。地址偏移量:0x64，初值:0x00000000，宽度:32
 寄存器说明: [Raw Interrupt Status Register] DEBUG register (bloc 3 over 3).
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fbdraw_2__fbd_done             : 1;  /* bit[0-0]  : source: NA [127 over 104] NC */
        unsigned int  fbcyuv_1__fbc_done             : 1;  /* bit[1-1]  : source: NA [126 over 104] NC */
        unsigned int  reserved_0                     : 1;  /* bit[2-2]  : source: NA [125 over 104] NC */
        unsigned int  fbdyuv_1__fbd_done             : 1;  /* bit[3-3]  : source: NA [124 over 104] NC */
        unsigned int  reserved_1                     : 1;  /* bit[4-4]  : source: NA [123 over 104] NC */
        unsigned int  tnr_1__frame_filtering_done    : 1;  /* bit[5-5]  : source: NA [122 over 104] NC */
        unsigned int  flash__flash_cap               : 1;  /* bit[6-6]  : source: NA [121 over 104] NC */
        unsigned int  otap_2_1__cvdr_rt__eol_vpwr_14 : 1;  /* bit[7-7]  : source: OTAP_2_1 [120 over 104] NC */
        unsigned int  otap_2_2__cvdr_rt__eol_vpwr_15 : 1;  /* bit[8-8]  : source: OTAP_2_2 [119 over 104] NC */
        unsigned int  reserved_2                     : 1;  /* bit[9-9]  : - */
        unsigned int  reserved_3                     : 1;  /* bit[10-10]: - */
        unsigned int  reserved_4                     : 1;  /* bit[11-11]: - */
        unsigned int  reserved_5                     : 1;  /* bit[12-12]: - */
        unsigned int  reserved_6                     : 1;  /* bit[13-13]: - */
        unsigned int  reserved_7                     : 1;  /* bit[14-14]: - */
        unsigned int  reserved_8                     : 1;  /* bit[15-15]: - */
        unsigned int  reserved_9                     : 1;  /* bit[16-16]: - */
        unsigned int  reserved_10                    : 1;  /* bit[17-17]: - */
        unsigned int  reserved_11                    : 1;  /* bit[18-18]: - */
        unsigned int  reserved_12                    : 1;  /* bit[19-19]: - */
        unsigned int  reserved_13                    : 1;  /* bit[20-20]: - */
        unsigned int  reserved_14                    : 1;  /* bit[21-21]: - */
        unsigned int  reserved_15                    : 1;  /* bit[22-22]: - */
        unsigned int  reserved_16                    : 1;  /* bit[23-23]: - */
        unsigned int  reserved_17                    : 1;  /* bit[24-24]: - */
        unsigned int  reserved_18                    : 1;  /* bit[25-25]: - */
        unsigned int  reserved_19                    : 1;  /* bit[26-26]: - */
        unsigned int  reserved_20                    : 1;  /* bit[27-27]: - */
        unsigned int  reserved_21                    : 1;  /* bit[28-28]: - */
        unsigned int  reserved_22                    : 1;  /* bit[29-29]: - */
        unsigned int  reserved_23                    : 1;  /* bit[30-30]: - */
        unsigned int  reserved_24                    : 1;  /* bit[31-31]: - */
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_3_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_3_fbdraw_2__fbd_done_START              (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_3_fbdraw_2__fbd_done_END                (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_3_fbcyuv_1__fbc_done_START              (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_3_fbcyuv_1__fbc_done_END                (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_3_fbdyuv_1__fbd_done_START              (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_3_fbdyuv_1__fbd_done_END                (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_3_tnr_1__frame_filtering_done_START     (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_3_tnr_1__frame_filtering_done_END       (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_3_flash__flash_cap_START                (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_3_flash__flash_cap_END                  (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_3_otap_2_1__cvdr_rt__eol_vpwr_14_START  (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_3_otap_2_1__cvdr_rt__eol_vpwr_14_END    (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_3_otap_2_2__cvdr_rt__eol_vpwr_15_START  (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_DEBUG_3_otap_2_2__cvdr_rt__eol_vpwr_15_END    (8)


/*****************************************************************************
 结构名    : SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_3_UNION
 结构说明  : IRQ_MERGER_MIS_DEBUG_3 寄存器结构定义。地址偏移量:0x68，初值:0x00000000，宽度:32
 寄存器说明: [Masked Interrupt Status Register] DEBUG register (bloc 3 over 3).
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fbdraw_2__fbd_done             : 1;  /* bit[0-0]  : source: NA [127 over 104] NC */
        unsigned int  fbcyuv_1__fbc_done             : 1;  /* bit[1-1]  : source: NA [126 over 104] NC */
        unsigned int  reserved_0                     : 1;  /* bit[2-2]  : source: NA [125 over 104] NC */
        unsigned int  fbdyuv_1__fbd_done             : 1;  /* bit[3-3]  : source: NA [124 over 104] NC */
        unsigned int  reserved_1                     : 1;  /* bit[4-4]  : source: NA [123 over 104] NC */
        unsigned int  tnr_1__frame_filtering_done    : 1;  /* bit[5-5]  : source: NA [122 over 104] NC */
        unsigned int  flash__flash_cap               : 1;  /* bit[6-6]  : source: NA [121 over 104] NC */
        unsigned int  otap_2_1__cvdr_rt__eol_vpwr_14 : 1;  /* bit[7-7]  : source: OTAP_2_1 [120 over 104] NC */
        unsigned int  otap_2_2__cvdr_rt__eol_vpwr_15 : 1;  /* bit[8-8]  : source: OTAP_2_2 [119 over 104] NC */
        unsigned int  reserved_2                     : 1;  /* bit[9-9]  : - */
        unsigned int  reserved_3                     : 1;  /* bit[10-10]: - */
        unsigned int  reserved_4                     : 1;  /* bit[11-11]: - */
        unsigned int  reserved_5                     : 1;  /* bit[12-12]: - */
        unsigned int  reserved_6                     : 1;  /* bit[13-13]: - */
        unsigned int  reserved_7                     : 1;  /* bit[14-14]: - */
        unsigned int  reserved_8                     : 1;  /* bit[15-15]: - */
        unsigned int  reserved_9                     : 1;  /* bit[16-16]: - */
        unsigned int  reserved_10                    : 1;  /* bit[17-17]: - */
        unsigned int  reserved_11                    : 1;  /* bit[18-18]: - */
        unsigned int  reserved_12                    : 1;  /* bit[19-19]: - */
        unsigned int  reserved_13                    : 1;  /* bit[20-20]: - */
        unsigned int  reserved_14                    : 1;  /* bit[21-21]: - */
        unsigned int  reserved_15                    : 1;  /* bit[22-22]: - */
        unsigned int  reserved_16                    : 1;  /* bit[23-23]: - */
        unsigned int  reserved_17                    : 1;  /* bit[24-24]: - */
        unsigned int  reserved_18                    : 1;  /* bit[25-25]: - */
        unsigned int  reserved_19                    : 1;  /* bit[26-26]: - */
        unsigned int  reserved_20                    : 1;  /* bit[27-27]: - */
        unsigned int  reserved_21                    : 1;  /* bit[28-28]: - */
        unsigned int  reserved_22                    : 1;  /* bit[29-29]: - */
        unsigned int  reserved_23                    : 1;  /* bit[30-30]: - */
        unsigned int  reserved_24                    : 1;  /* bit[31-31]: - */
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_3_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_3_fbdraw_2__fbd_done_START              (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_3_fbdraw_2__fbd_done_END                (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_3_fbcyuv_1__fbc_done_START              (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_3_fbcyuv_1__fbc_done_END                (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_3_fbdyuv_1__fbd_done_START              (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_3_fbdyuv_1__fbd_done_END                (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_3_tnr_1__frame_filtering_done_START     (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_3_tnr_1__frame_filtering_done_END       (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_3_flash__flash_cap_START                (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_3_flash__flash_cap_END                  (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_3_otap_2_1__cvdr_rt__eol_vpwr_14_START  (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_3_otap_2_1__cvdr_rt__eol_vpwr_14_END    (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_3_otap_2_2__cvdr_rt__eol_vpwr_15_START  (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_DEBUG_3_otap_2_2__cvdr_rt__eol_vpwr_15_END    (8)


/*****************************************************************************
 结构名    : SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_3_UNION
 结构说明  : IRQ_MERGER_ICR_DEBUG_3 寄存器结构定义。地址偏移量:0x6C，初值:0x00000000，宽度:32
 寄存器说明: [Interrupt Clear Register] DEBUG register (bloc 3 over 3).
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fbdraw_2__fbd_done             : 1;  /* bit[0-0]  : source: NA [127 over 104] NC */
        unsigned int  fbcyuv_1__fbc_done             : 1;  /* bit[1-1]  : source: NA [126 over 104] NC */
        unsigned int  reserved_0                     : 1;  /* bit[2-2]  : source: NA [125 over 104] NC */
        unsigned int  fbdyuv_1__fbd_done             : 1;  /* bit[3-3]  : source: NA [124 over 104] NC */
        unsigned int  reserved_1                     : 1;  /* bit[4-4]  : source: NA [123 over 104] NC */
        unsigned int  tnr_1__frame_filtering_done    : 1;  /* bit[5-5]  : source: NA [122 over 104] NC */
        unsigned int  flash__flash_cap               : 1;  /* bit[6-6]  : source: NA [121 over 104] NC */
        unsigned int  otap_2_1__cvdr_rt__eol_vpwr_14 : 1;  /* bit[7-7]  : source: OTAP_2_1 [120 over 104] NC */
        unsigned int  otap_2_2__cvdr_rt__eol_vpwr_15 : 1;  /* bit[8-8]  : source: OTAP_2_2 [119 over 104] NC */
        unsigned int  reserved_2                     : 1;  /* bit[9-9]  : - */
        unsigned int  reserved_3                     : 1;  /* bit[10-10]: - */
        unsigned int  reserved_4                     : 1;  /* bit[11-11]: - */
        unsigned int  reserved_5                     : 1;  /* bit[12-12]: - */
        unsigned int  reserved_6                     : 1;  /* bit[13-13]: - */
        unsigned int  reserved_7                     : 1;  /* bit[14-14]: - */
        unsigned int  reserved_8                     : 1;  /* bit[15-15]: - */
        unsigned int  reserved_9                     : 1;  /* bit[16-16]: - */
        unsigned int  reserved_10                    : 1;  /* bit[17-17]: - */
        unsigned int  reserved_11                    : 1;  /* bit[18-18]: - */
        unsigned int  reserved_12                    : 1;  /* bit[19-19]: - */
        unsigned int  reserved_13                    : 1;  /* bit[20-20]: - */
        unsigned int  reserved_14                    : 1;  /* bit[21-21]: - */
        unsigned int  reserved_15                    : 1;  /* bit[22-22]: - */
        unsigned int  reserved_16                    : 1;  /* bit[23-23]: - */
        unsigned int  reserved_17                    : 1;  /* bit[24-24]: - */
        unsigned int  reserved_18                    : 1;  /* bit[25-25]: - */
        unsigned int  reserved_19                    : 1;  /* bit[26-26]: - */
        unsigned int  reserved_20                    : 1;  /* bit[27-27]: - */
        unsigned int  reserved_21                    : 1;  /* bit[28-28]: - */
        unsigned int  reserved_22                    : 1;  /* bit[29-29]: - */
        unsigned int  reserved_23                    : 1;  /* bit[30-30]: - */
        unsigned int  reserved_24                    : 1;  /* bit[31-31]: - */
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_3_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_3_fbdraw_2__fbd_done_START              (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_3_fbdraw_2__fbd_done_END                (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_3_fbcyuv_1__fbc_done_START              (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_3_fbcyuv_1__fbc_done_END                (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_3_fbdyuv_1__fbd_done_START              (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_3_fbdyuv_1__fbd_done_END                (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_3_tnr_1__frame_filtering_done_START     (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_3_tnr_1__frame_filtering_done_END       (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_3_flash__flash_cap_START                (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_3_flash__flash_cap_END                  (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_3_otap_2_1__cvdr_rt__eol_vpwr_14_START  (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_3_otap_2_1__cvdr_rt__eol_vpwr_14_END    (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_3_otap_2_2__cvdr_rt__eol_vpwr_15_START  (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_DEBUG_3_otap_2_2__cvdr_rt__eol_vpwr_15_END    (8)


/*****************************************************************************
 结构名    : SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_3_UNION
 结构说明  : IRQ_MERGER_ISR_DEBUG_3 寄存器结构定义。地址偏移量:0x70，初值:0x00000000，宽度:32
 寄存器说明: [Interrupt Set Register] DEBUG register (bloc 3 over 3).
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fbdraw_2__fbd_done             : 1;  /* bit[0-0]  : source: NA [127 over 104] NC */
        unsigned int  fbcyuv_1__fbc_done             : 1;  /* bit[1-1]  : source: NA [126 over 104] NC */
        unsigned int  reserved_0                     : 1;  /* bit[2-2]  : source: NA [125 over 104] NC */
        unsigned int  fbdyuv_1__fbd_done             : 1;  /* bit[3-3]  : source: NA [124 over 104] NC */
        unsigned int  reserved_1                     : 1;  /* bit[4-4]  : source: NA [123 over 104] NC */
        unsigned int  tnr_1__frame_filtering_done    : 1;  /* bit[5-5]  : source: NA [122 over 104] NC */
        unsigned int  flash__flash_cap               : 1;  /* bit[6-6]  : source: NA [121 over 104] NC */
        unsigned int  otap_2_1__cvdr_rt__eol_vpwr_14 : 1;  /* bit[7-7]  : source: OTAP_2_1 [120 over 104] NC */
        unsigned int  otap_2_2__cvdr_rt__eol_vpwr_15 : 1;  /* bit[8-8]  : source: OTAP_2_2 [119 over 104] NC */
        unsigned int  reserved_2                     : 1;  /* bit[9-9]  : - */
        unsigned int  reserved_3                     : 1;  /* bit[10-10]: - */
        unsigned int  reserved_4                     : 1;  /* bit[11-11]: - */
        unsigned int  reserved_5                     : 1;  /* bit[12-12]: - */
        unsigned int  reserved_6                     : 1;  /* bit[13-13]: - */
        unsigned int  reserved_7                     : 1;  /* bit[14-14]: - */
        unsigned int  reserved_8                     : 1;  /* bit[15-15]: - */
        unsigned int  reserved_9                     : 1;  /* bit[16-16]: - */
        unsigned int  reserved_10                    : 1;  /* bit[17-17]: - */
        unsigned int  reserved_11                    : 1;  /* bit[18-18]: - */
        unsigned int  reserved_12                    : 1;  /* bit[19-19]: - */
        unsigned int  reserved_13                    : 1;  /* bit[20-20]: - */
        unsigned int  reserved_14                    : 1;  /* bit[21-21]: - */
        unsigned int  reserved_15                    : 1;  /* bit[22-22]: - */
        unsigned int  reserved_16                    : 1;  /* bit[23-23]: - */
        unsigned int  reserved_17                    : 1;  /* bit[24-24]: - */
        unsigned int  reserved_18                    : 1;  /* bit[25-25]: - */
        unsigned int  reserved_19                    : 1;  /* bit[26-26]: - */
        unsigned int  reserved_20                    : 1;  /* bit[27-27]: - */
        unsigned int  reserved_21                    : 1;  /* bit[28-28]: - */
        unsigned int  reserved_22                    : 1;  /* bit[29-29]: - */
        unsigned int  reserved_23                    : 1;  /* bit[30-30]: - */
        unsigned int  reserved_24                    : 1;  /* bit[31-31]: - */
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_3_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_3_fbdraw_2__fbd_done_START              (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_3_fbdraw_2__fbd_done_END                (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_3_fbcyuv_1__fbc_done_START              (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_3_fbcyuv_1__fbc_done_END                (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_3_fbdyuv_1__fbd_done_START              (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_3_fbdyuv_1__fbd_done_END                (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_3_tnr_1__frame_filtering_done_START     (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_3_tnr_1__frame_filtering_done_END       (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_3_flash__flash_cap_START                (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_3_flash__flash_cap_END                  (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_3_otap_2_1__cvdr_rt__eol_vpwr_14_START  (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_3_otap_2_1__cvdr_rt__eol_vpwr_14_END    (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_3_otap_2_2__cvdr_rt__eol_vpwr_15_START  (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_DEBUG_3_otap_2_2__cvdr_rt__eol_vpwr_15_END    (8)


/*****************************************************************************
 结构名    : SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_UNION
 结构说明  : IRQ_MERGER_IMSC_ERROR_0 寄存器结构定义。地址偏移量:0x80，初值:0x00000000，宽度:32
 寄存器说明: [Interrupt Mask Register] ERROR register (bloc 0 over 1).
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cvdr_rt__axi_wr_full               : 1;  /* bit[0-0]  : source: NA [31 over 46] NC */
        unsigned int  cvdr_sram__axi_wr_full             : 1;  /* bit[1-1]  : source: NA [30 over 46] NC */
        unsigned int  isp_fe_1__fcm__short_wr_evt_0      : 1;  /* bit[2-2]  : source: ISP_FE_1 [29 over 46] NC */
        unsigned int  isp_fe_1__fcm__short_rd_evt_0      : 1;  /* bit[3-3]  : source: ISP_FE_1 [28 over 46] NC */
        unsigned int  isp_fe_2__fcm__short_wr_evt_1      : 1;  /* bit[4-4]  : source: ISP_FE_2 [27 over 46] NC */
        unsigned int  isp_fe_2__fcm__short_rd_evt_1      : 1;  /* bit[5-5]  : source: ISP_FE_2 [26 over 46] NC */
        unsigned int  scaler_1_1_y__fcm__short_wr_evt_2  : 1;  /* bit[6-6]  : source: SCALER_1_1(Y) [25 over 46] NC */
        unsigned int  scaler_1_1_y__fcm__short_rd_evt_2  : 1;  /* bit[7-7]  : source: SCALER_1_1(Y) [24 over 46] NC */
        unsigned int  scaler_1_1_uv__fcm__short_wr_evt_3 : 1;  /* bit[8-8]  : source: SCALER_1_1(UV) [23 over 46] NC */
        unsigned int  scaler_1_1_uv__fcm__short_rd_evt_3 : 1;  /* bit[9-9]  : source: SCALER_1_1(UV) [22 over 46] NC */
        unsigned int  scaler_1_2_y__fcm__short_wr_evt_4  : 1;  /* bit[10-10]: source: SCALER_1_2(Y) [21 over 46] NC */
        unsigned int  scaler_1_2_y__fcm__short_rd_evt_4  : 1;  /* bit[11-11]: source: SCALER_1_2(Y) [20 over 46] NC */
        unsigned int  scaler_1_2_uv__fcm__short_wr_evt_5 : 1;  /* bit[12-12]: source: SCALER_1_2(UV) [19 over 46] NC */
        unsigned int  scaler_1_2_uv__fcm__short_rd_evt_5 : 1;  /* bit[13-13]: source: SCALER_1_2(UV) [18 over 46] NC */
        unsigned int  prescaler__end_of_frame_error      : 1;  /* bit[14-14]: source: NA [17 over 46] NC */
        unsigned int  stream_router__cam_a_ovf           : 1;  /* bit[15-15]: source: NA [16 over 46] NC */
        unsigned int  stream_router__cam_b_ovf           : 1;  /* bit[16-16]: source: NA [15 over 46] NC */
        unsigned int  stream_router__cam_c_ovf           : 1;  /* bit[17-17]: source: NA [14 over 46] NC */
        unsigned int  stream_router__reformater_h_err_0  : 1;  /* bit[18-18]: source: NA [13 over 46] NC */
        unsigned int  stream_router__reformater_h_err_1  : 1;  /* bit[19-19]: source: NA [12 over 46] NC */
        unsigned int  stream_router__reformater_h_err_2  : 1;  /* bit[20-20]: source: NA [11 over 46] NC */
        unsigned int  stream_router__reformater_h_err_3  : 1;  /* bit[21-21]: source: NA [10 over 46] NC */
        unsigned int  stream_router__reformater_h_err_4  : 1;  /* bit[22-22]: source: NA [9 over 46] NC */
        unsigned int  stream_router__reformater_h_err_5  : 1;  /* bit[23-23]: source: NA [8 over 46] NC */
        unsigned int  stream_router__reformater_h_err_6  : 1;  /* bit[24-24]: source: NA [7 over 46] NC */
        unsigned int  stream_router__reformater_h_err_7  : 1;  /* bit[25-25]: source: NA [6 over 46] NC */
        unsigned int  stream_router__reformater_err_0    : 1;  /* bit[26-26]: source: NA [5 over 46] NC */
        unsigned int  stream_router__reformater_err_1    : 1;  /* bit[27-27]: source: NA [4 over 46] NC */
        unsigned int  stream_router__reformater_err_2    : 1;  /* bit[28-28]: source: NA [3 over 46] NC */
        unsigned int  stream_router__reformater_err_3    : 1;  /* bit[29-29]: source: NA [2 over 46] NC */
        unsigned int  stream_router__reformater_err_4    : 1;  /* bit[30-30]: source: NA [1 over 46] NC */
        unsigned int  stream_router__reformater_err_5    : 1;  /* bit[31-31]: source: NA [0 over 46] NC */
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_cvdr_rt__axi_wr_full_START                (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_cvdr_rt__axi_wr_full_END                  (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_cvdr_sram__axi_wr_full_START              (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_cvdr_sram__axi_wr_full_END                (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_isp_fe_1__fcm__short_wr_evt_0_START       (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_isp_fe_1__fcm__short_wr_evt_0_END         (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_isp_fe_1__fcm__short_rd_evt_0_START       (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_isp_fe_1__fcm__short_rd_evt_0_END         (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_isp_fe_2__fcm__short_wr_evt_1_START       (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_isp_fe_2__fcm__short_wr_evt_1_END         (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_isp_fe_2__fcm__short_rd_evt_1_START       (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_isp_fe_2__fcm__short_rd_evt_1_END         (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_scaler_1_1_y__fcm__short_wr_evt_2_START   (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_scaler_1_1_y__fcm__short_wr_evt_2_END     (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_scaler_1_1_y__fcm__short_rd_evt_2_START   (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_scaler_1_1_y__fcm__short_rd_evt_2_END     (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_scaler_1_1_uv__fcm__short_wr_evt_3_START  (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_scaler_1_1_uv__fcm__short_wr_evt_3_END    (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_scaler_1_1_uv__fcm__short_rd_evt_3_START  (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_scaler_1_1_uv__fcm__short_rd_evt_3_END    (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_scaler_1_2_y__fcm__short_wr_evt_4_START   (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_scaler_1_2_y__fcm__short_wr_evt_4_END     (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_scaler_1_2_y__fcm__short_rd_evt_4_START   (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_scaler_1_2_y__fcm__short_rd_evt_4_END     (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_scaler_1_2_uv__fcm__short_wr_evt_5_START  (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_scaler_1_2_uv__fcm__short_wr_evt_5_END    (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_scaler_1_2_uv__fcm__short_rd_evt_5_START  (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_scaler_1_2_uv__fcm__short_rd_evt_5_END    (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_prescaler__end_of_frame_error_START       (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_prescaler__end_of_frame_error_END         (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__cam_a_ovf_START            (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__cam_a_ovf_END              (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__cam_b_ovf_START            (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__cam_b_ovf_END              (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__cam_c_ovf_START            (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__cam_c_ovf_END              (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__reformater_h_err_0_START   (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__reformater_h_err_0_END     (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__reformater_h_err_1_START   (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__reformater_h_err_1_END     (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__reformater_h_err_2_START   (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__reformater_h_err_2_END     (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__reformater_h_err_3_START   (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__reformater_h_err_3_END     (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__reformater_h_err_4_START   (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__reformater_h_err_4_END     (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__reformater_h_err_5_START   (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__reformater_h_err_5_END     (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__reformater_h_err_6_START   (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__reformater_h_err_6_END     (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__reformater_h_err_7_START   (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__reformater_h_err_7_END     (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__reformater_err_0_START     (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__reformater_err_0_END       (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__reformater_err_1_START     (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__reformater_err_1_END       (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__reformater_err_2_START     (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__reformater_err_2_END       (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__reformater_err_3_START     (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__reformater_err_3_END       (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__reformater_err_4_START     (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__reformater_err_4_END       (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__reformater_err_5_START     (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_0_stream_router__reformater_err_5_END       (31)


/*****************************************************************************
 结构名    : SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_UNION
 结构说明  : IRQ_MERGER_RIS_ERROR_0 寄存器结构定义。地址偏移量:0x84，初值:0x00000000，宽度:32
 寄存器说明: [Raw Interrupt Status Register] ERROR register (bloc 0 over 1).
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cvdr_rt__axi_wr_full               : 1;  /* bit[0-0]  : source: NA [31 over 46] NC */
        unsigned int  cvdr_sram__axi_wr_full             : 1;  /* bit[1-1]  : source: NA [30 over 46] NC */
        unsigned int  isp_fe_1__fcm__short_wr_evt_0      : 1;  /* bit[2-2]  : source: ISP_FE_1 [29 over 46] NC */
        unsigned int  isp_fe_1__fcm__short_rd_evt_0      : 1;  /* bit[3-3]  : source: ISP_FE_1 [28 over 46] NC */
        unsigned int  isp_fe_2__fcm__short_wr_evt_1      : 1;  /* bit[4-4]  : source: ISP_FE_2 [27 over 46] NC */
        unsigned int  isp_fe_2__fcm__short_rd_evt_1      : 1;  /* bit[5-5]  : source: ISP_FE_2 [26 over 46] NC */
        unsigned int  scaler_1_1_y__fcm__short_wr_evt_2  : 1;  /* bit[6-6]  : source: SCALER_1_1(Y) [25 over 46] NC */
        unsigned int  scaler_1_1_y__fcm__short_rd_evt_2  : 1;  /* bit[7-7]  : source: SCALER_1_1(Y) [24 over 46] NC */
        unsigned int  scaler_1_1_uv__fcm__short_wr_evt_3 : 1;  /* bit[8-8]  : source: SCALER_1_1(UV) [23 over 46] NC */
        unsigned int  scaler_1_1_uv__fcm__short_rd_evt_3 : 1;  /* bit[9-9]  : source: SCALER_1_1(UV) [22 over 46] NC */
        unsigned int  scaler_1_2_y__fcm__short_wr_evt_4  : 1;  /* bit[10-10]: source: SCALER_1_2(Y) [21 over 46] NC */
        unsigned int  scaler_1_2_y__fcm__short_rd_evt_4  : 1;  /* bit[11-11]: source: SCALER_1_2(Y) [20 over 46] NC */
        unsigned int  scaler_1_2_uv__fcm__short_wr_evt_5 : 1;  /* bit[12-12]: source: SCALER_1_2(UV) [19 over 46] NC */
        unsigned int  scaler_1_2_uv__fcm__short_rd_evt_5 : 1;  /* bit[13-13]: source: SCALER_1_2(UV) [18 over 46] NC */
        unsigned int  prescaler__end_of_frame_error      : 1;  /* bit[14-14]: source: NA [17 over 46] NC */
        unsigned int  stream_router__cam_a_ovf           : 1;  /* bit[15-15]: source: NA [16 over 46] NC */
        unsigned int  stream_router__cam_b_ovf           : 1;  /* bit[16-16]: source: NA [15 over 46] NC */
        unsigned int  stream_router__cam_c_ovf           : 1;  /* bit[17-17]: source: NA [14 over 46] NC */
        unsigned int  stream_router__reformater_h_err_0  : 1;  /* bit[18-18]: source: NA [13 over 46] NC */
        unsigned int  stream_router__reformater_h_err_1  : 1;  /* bit[19-19]: source: NA [12 over 46] NC */
        unsigned int  stream_router__reformater_h_err_2  : 1;  /* bit[20-20]: source: NA [11 over 46] NC */
        unsigned int  stream_router__reformater_h_err_3  : 1;  /* bit[21-21]: source: NA [10 over 46] NC */
        unsigned int  stream_router__reformater_h_err_4  : 1;  /* bit[22-22]: source: NA [9 over 46] NC */
        unsigned int  stream_router__reformater_h_err_5  : 1;  /* bit[23-23]: source: NA [8 over 46] NC */
        unsigned int  stream_router__reformater_h_err_6  : 1;  /* bit[24-24]: source: NA [7 over 46] NC */
        unsigned int  stream_router__reformater_h_err_7  : 1;  /* bit[25-25]: source: NA [6 over 46] NC */
        unsigned int  stream_router__reformater_err_0    : 1;  /* bit[26-26]: source: NA [5 over 46] NC */
        unsigned int  stream_router__reformater_err_1    : 1;  /* bit[27-27]: source: NA [4 over 46] NC */
        unsigned int  stream_router__reformater_err_2    : 1;  /* bit[28-28]: source: NA [3 over 46] NC */
        unsigned int  stream_router__reformater_err_3    : 1;  /* bit[29-29]: source: NA [2 over 46] NC */
        unsigned int  stream_router__reformater_err_4    : 1;  /* bit[30-30]: source: NA [1 over 46] NC */
        unsigned int  stream_router__reformater_err_5    : 1;  /* bit[31-31]: source: NA [0 over 46] NC */
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_cvdr_rt__axi_wr_full_START                (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_cvdr_rt__axi_wr_full_END                  (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_cvdr_sram__axi_wr_full_START              (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_cvdr_sram__axi_wr_full_END                (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_isp_fe_1__fcm__short_wr_evt_0_START       (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_isp_fe_1__fcm__short_wr_evt_0_END         (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_isp_fe_1__fcm__short_rd_evt_0_START       (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_isp_fe_1__fcm__short_rd_evt_0_END         (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_isp_fe_2__fcm__short_wr_evt_1_START       (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_isp_fe_2__fcm__short_wr_evt_1_END         (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_isp_fe_2__fcm__short_rd_evt_1_START       (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_isp_fe_2__fcm__short_rd_evt_1_END         (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_scaler_1_1_y__fcm__short_wr_evt_2_START   (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_scaler_1_1_y__fcm__short_wr_evt_2_END     (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_scaler_1_1_y__fcm__short_rd_evt_2_START   (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_scaler_1_1_y__fcm__short_rd_evt_2_END     (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_scaler_1_1_uv__fcm__short_wr_evt_3_START  (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_scaler_1_1_uv__fcm__short_wr_evt_3_END    (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_scaler_1_1_uv__fcm__short_rd_evt_3_START  (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_scaler_1_1_uv__fcm__short_rd_evt_3_END    (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_scaler_1_2_y__fcm__short_wr_evt_4_START   (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_scaler_1_2_y__fcm__short_wr_evt_4_END     (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_scaler_1_2_y__fcm__short_rd_evt_4_START   (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_scaler_1_2_y__fcm__short_rd_evt_4_END     (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_scaler_1_2_uv__fcm__short_wr_evt_5_START  (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_scaler_1_2_uv__fcm__short_wr_evt_5_END    (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_scaler_1_2_uv__fcm__short_rd_evt_5_START  (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_scaler_1_2_uv__fcm__short_rd_evt_5_END    (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_prescaler__end_of_frame_error_START       (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_prescaler__end_of_frame_error_END         (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__cam_a_ovf_START            (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__cam_a_ovf_END              (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__cam_b_ovf_START            (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__cam_b_ovf_END              (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__cam_c_ovf_START            (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__cam_c_ovf_END              (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__reformater_h_err_0_START   (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__reformater_h_err_0_END     (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__reformater_h_err_1_START   (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__reformater_h_err_1_END     (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__reformater_h_err_2_START   (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__reformater_h_err_2_END     (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__reformater_h_err_3_START   (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__reformater_h_err_3_END     (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__reformater_h_err_4_START   (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__reformater_h_err_4_END     (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__reformater_h_err_5_START   (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__reformater_h_err_5_END     (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__reformater_h_err_6_START   (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__reformater_h_err_6_END     (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__reformater_h_err_7_START   (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__reformater_h_err_7_END     (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__reformater_err_0_START     (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__reformater_err_0_END       (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__reformater_err_1_START     (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__reformater_err_1_END       (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__reformater_err_2_START     (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__reformater_err_2_END       (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__reformater_err_3_START     (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__reformater_err_3_END       (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__reformater_err_4_START     (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__reformater_err_4_END       (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__reformater_err_5_START     (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_0_stream_router__reformater_err_5_END       (31)


/*****************************************************************************
 结构名    : SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_UNION
 结构说明  : IRQ_MERGER_MIS_ERROR_0 寄存器结构定义。地址偏移量:0x88，初值:0x00000000，宽度:32
 寄存器说明: [Masked Interrupt Status Register] ERROR register (bloc 0 over 1).
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cvdr_rt__axi_wr_full               : 1;  /* bit[0-0]  : source: NA [31 over 46] NC */
        unsigned int  cvdr_sram__axi_wr_full             : 1;  /* bit[1-1]  : source: NA [30 over 46] NC */
        unsigned int  isp_fe_1__fcm__short_wr_evt_0      : 1;  /* bit[2-2]  : source: ISP_FE_1 [29 over 46] NC */
        unsigned int  isp_fe_1__fcm__short_rd_evt_0      : 1;  /* bit[3-3]  : source: ISP_FE_1 [28 over 46] NC */
        unsigned int  isp_fe_2__fcm__short_wr_evt_1      : 1;  /* bit[4-4]  : source: ISP_FE_2 [27 over 46] NC */
        unsigned int  isp_fe_2__fcm__short_rd_evt_1      : 1;  /* bit[5-5]  : source: ISP_FE_2 [26 over 46] NC */
        unsigned int  scaler_1_1_y__fcm__short_wr_evt_2  : 1;  /* bit[6-6]  : source: SCALER_1_1(Y) [25 over 46] NC */
        unsigned int  scaler_1_1_y__fcm__short_rd_evt_2  : 1;  /* bit[7-7]  : source: SCALER_1_1(Y) [24 over 46] NC */
        unsigned int  scaler_1_1_uv__fcm__short_wr_evt_3 : 1;  /* bit[8-8]  : source: SCALER_1_1(UV) [23 over 46] NC */
        unsigned int  scaler_1_1_uv__fcm__short_rd_evt_3 : 1;  /* bit[9-9]  : source: SCALER_1_1(UV) [22 over 46] NC */
        unsigned int  scaler_1_2_y__fcm__short_wr_evt_4  : 1;  /* bit[10-10]: source: SCALER_1_2(Y) [21 over 46] NC */
        unsigned int  scaler_1_2_y__fcm__short_rd_evt_4  : 1;  /* bit[11-11]: source: SCALER_1_2(Y) [20 over 46] NC */
        unsigned int  scaler_1_2_uv__fcm__short_wr_evt_5 : 1;  /* bit[12-12]: source: SCALER_1_2(UV) [19 over 46] NC */
        unsigned int  scaler_1_2_uv__fcm__short_rd_evt_5 : 1;  /* bit[13-13]: source: SCALER_1_2(UV) [18 over 46] NC */
        unsigned int  prescaler__end_of_frame_error      : 1;  /* bit[14-14]: source: NA [17 over 46] NC */
        unsigned int  stream_router__cam_a_ovf           : 1;  /* bit[15-15]: source: NA [16 over 46] NC */
        unsigned int  stream_router__cam_b_ovf           : 1;  /* bit[16-16]: source: NA [15 over 46] NC */
        unsigned int  stream_router__cam_c_ovf           : 1;  /* bit[17-17]: source: NA [14 over 46] NC */
        unsigned int  stream_router__reformater_h_err_0  : 1;  /* bit[18-18]: source: NA [13 over 46] NC */
        unsigned int  stream_router__reformater_h_err_1  : 1;  /* bit[19-19]: source: NA [12 over 46] NC */
        unsigned int  stream_router__reformater_h_err_2  : 1;  /* bit[20-20]: source: NA [11 over 46] NC */
        unsigned int  stream_router__reformater_h_err_3  : 1;  /* bit[21-21]: source: NA [10 over 46] NC */
        unsigned int  stream_router__reformater_h_err_4  : 1;  /* bit[22-22]: source: NA [9 over 46] NC */
        unsigned int  stream_router__reformater_h_err_5  : 1;  /* bit[23-23]: source: NA [8 over 46] NC */
        unsigned int  stream_router__reformater_h_err_6  : 1;  /* bit[24-24]: source: NA [7 over 46] NC */
        unsigned int  stream_router__reformater_h_err_7  : 1;  /* bit[25-25]: source: NA [6 over 46] NC */
        unsigned int  stream_router__reformater_err_0    : 1;  /* bit[26-26]: source: NA [5 over 46] NC */
        unsigned int  stream_router__reformater_err_1    : 1;  /* bit[27-27]: source: NA [4 over 46] NC */
        unsigned int  stream_router__reformater_err_2    : 1;  /* bit[28-28]: source: NA [3 over 46] NC */
        unsigned int  stream_router__reformater_err_3    : 1;  /* bit[29-29]: source: NA [2 over 46] NC */
        unsigned int  stream_router__reformater_err_4    : 1;  /* bit[30-30]: source: NA [1 over 46] NC */
        unsigned int  stream_router__reformater_err_5    : 1;  /* bit[31-31]: source: NA [0 over 46] NC */
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_cvdr_rt__axi_wr_full_START                (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_cvdr_rt__axi_wr_full_END                  (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_cvdr_sram__axi_wr_full_START              (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_cvdr_sram__axi_wr_full_END                (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_isp_fe_1__fcm__short_wr_evt_0_START       (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_isp_fe_1__fcm__short_wr_evt_0_END         (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_isp_fe_1__fcm__short_rd_evt_0_START       (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_isp_fe_1__fcm__short_rd_evt_0_END         (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_isp_fe_2__fcm__short_wr_evt_1_START       (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_isp_fe_2__fcm__short_wr_evt_1_END         (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_isp_fe_2__fcm__short_rd_evt_1_START       (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_isp_fe_2__fcm__short_rd_evt_1_END         (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_scaler_1_1_y__fcm__short_wr_evt_2_START   (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_scaler_1_1_y__fcm__short_wr_evt_2_END     (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_scaler_1_1_y__fcm__short_rd_evt_2_START   (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_scaler_1_1_y__fcm__short_rd_evt_2_END     (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_scaler_1_1_uv__fcm__short_wr_evt_3_START  (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_scaler_1_1_uv__fcm__short_wr_evt_3_END    (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_scaler_1_1_uv__fcm__short_rd_evt_3_START  (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_scaler_1_1_uv__fcm__short_rd_evt_3_END    (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_scaler_1_2_y__fcm__short_wr_evt_4_START   (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_scaler_1_2_y__fcm__short_wr_evt_4_END     (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_scaler_1_2_y__fcm__short_rd_evt_4_START   (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_scaler_1_2_y__fcm__short_rd_evt_4_END     (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_scaler_1_2_uv__fcm__short_wr_evt_5_START  (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_scaler_1_2_uv__fcm__short_wr_evt_5_END    (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_scaler_1_2_uv__fcm__short_rd_evt_5_START  (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_scaler_1_2_uv__fcm__short_rd_evt_5_END    (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_prescaler__end_of_frame_error_START       (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_prescaler__end_of_frame_error_END         (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__cam_a_ovf_START            (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__cam_a_ovf_END              (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__cam_b_ovf_START            (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__cam_b_ovf_END              (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__cam_c_ovf_START            (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__cam_c_ovf_END              (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__reformater_h_err_0_START   (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__reformater_h_err_0_END     (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__reformater_h_err_1_START   (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__reformater_h_err_1_END     (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__reformater_h_err_2_START   (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__reformater_h_err_2_END     (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__reformater_h_err_3_START   (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__reformater_h_err_3_END     (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__reformater_h_err_4_START   (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__reformater_h_err_4_END     (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__reformater_h_err_5_START   (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__reformater_h_err_5_END     (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__reformater_h_err_6_START   (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__reformater_h_err_6_END     (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__reformater_h_err_7_START   (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__reformater_h_err_7_END     (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__reformater_err_0_START     (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__reformater_err_0_END       (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__reformater_err_1_START     (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__reformater_err_1_END       (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__reformater_err_2_START     (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__reformater_err_2_END       (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__reformater_err_3_START     (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__reformater_err_3_END       (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__reformater_err_4_START     (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__reformater_err_4_END       (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__reformater_err_5_START     (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_0_stream_router__reformater_err_5_END       (31)


/*****************************************************************************
 结构名    : SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_UNION
 结构说明  : IRQ_MERGER_ICR_ERROR_0 寄存器结构定义。地址偏移量:0x8C，初值:0x00000000，宽度:32
 寄存器说明: [Interrupt Clear Register] ERROR register (bloc 0 over 1).
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cvdr_rt__axi_wr_full               : 1;  /* bit[0-0]  : source: NA [31 over 46] NC */
        unsigned int  cvdr_sram__axi_wr_full             : 1;  /* bit[1-1]  : source: NA [30 over 46] NC */
        unsigned int  isp_fe_1__fcm__short_wr_evt_0      : 1;  /* bit[2-2]  : source: ISP_FE_1 [29 over 46] NC */
        unsigned int  isp_fe_1__fcm__short_rd_evt_0      : 1;  /* bit[3-3]  : source: ISP_FE_1 [28 over 46] NC */
        unsigned int  isp_fe_2__fcm__short_wr_evt_1      : 1;  /* bit[4-4]  : source: ISP_FE_2 [27 over 46] NC */
        unsigned int  isp_fe_2__fcm__short_rd_evt_1      : 1;  /* bit[5-5]  : source: ISP_FE_2 [26 over 46] NC */
        unsigned int  scaler_1_1_y__fcm__short_wr_evt_2  : 1;  /* bit[6-6]  : source: SCALER_1_1(Y) [25 over 46] NC */
        unsigned int  scaler_1_1_y__fcm__short_rd_evt_2  : 1;  /* bit[7-7]  : source: SCALER_1_1(Y) [24 over 46] NC */
        unsigned int  scaler_1_1_uv__fcm__short_wr_evt_3 : 1;  /* bit[8-8]  : source: SCALER_1_1(UV) [23 over 46] NC */
        unsigned int  scaler_1_1_uv__fcm__short_rd_evt_3 : 1;  /* bit[9-9]  : source: SCALER_1_1(UV) [22 over 46] NC */
        unsigned int  scaler_1_2_y__fcm__short_wr_evt_4  : 1;  /* bit[10-10]: source: SCALER_1_2(Y) [21 over 46] NC */
        unsigned int  scaler_1_2_y__fcm__short_rd_evt_4  : 1;  /* bit[11-11]: source: SCALER_1_2(Y) [20 over 46] NC */
        unsigned int  scaler_1_2_uv__fcm__short_wr_evt_5 : 1;  /* bit[12-12]: source: SCALER_1_2(UV) [19 over 46] NC */
        unsigned int  scaler_1_2_uv__fcm__short_rd_evt_5 : 1;  /* bit[13-13]: source: SCALER_1_2(UV) [18 over 46] NC */
        unsigned int  prescaler__end_of_frame_error      : 1;  /* bit[14-14]: source: NA [17 over 46] NC */
        unsigned int  stream_router__cam_a_ovf           : 1;  /* bit[15-15]: source: NA [16 over 46] NC */
        unsigned int  stream_router__cam_b_ovf           : 1;  /* bit[16-16]: source: NA [15 over 46] NC */
        unsigned int  stream_router__cam_c_ovf           : 1;  /* bit[17-17]: source: NA [14 over 46] NC */
        unsigned int  stream_router__reformater_h_err_0  : 1;  /* bit[18-18]: source: NA [13 over 46] NC */
        unsigned int  stream_router__reformater_h_err_1  : 1;  /* bit[19-19]: source: NA [12 over 46] NC */
        unsigned int  stream_router__reformater_h_err_2  : 1;  /* bit[20-20]: source: NA [11 over 46] NC */
        unsigned int  stream_router__reformater_h_err_3  : 1;  /* bit[21-21]: source: NA [10 over 46] NC */
        unsigned int  stream_router__reformater_h_err_4  : 1;  /* bit[22-22]: source: NA [9 over 46] NC */
        unsigned int  stream_router__reformater_h_err_5  : 1;  /* bit[23-23]: source: NA [8 over 46] NC */
        unsigned int  stream_router__reformater_h_err_6  : 1;  /* bit[24-24]: source: NA [7 over 46] NC */
        unsigned int  stream_router__reformater_h_err_7  : 1;  /* bit[25-25]: source: NA [6 over 46] NC */
        unsigned int  stream_router__reformater_err_0    : 1;  /* bit[26-26]: source: NA [5 over 46] NC */
        unsigned int  stream_router__reformater_err_1    : 1;  /* bit[27-27]: source: NA [4 over 46] NC */
        unsigned int  stream_router__reformater_err_2    : 1;  /* bit[28-28]: source: NA [3 over 46] NC */
        unsigned int  stream_router__reformater_err_3    : 1;  /* bit[29-29]: source: NA [2 over 46] NC */
        unsigned int  stream_router__reformater_err_4    : 1;  /* bit[30-30]: source: NA [1 over 46] NC */
        unsigned int  stream_router__reformater_err_5    : 1;  /* bit[31-31]: source: NA [0 over 46] NC */
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_cvdr_rt__axi_wr_full_START                (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_cvdr_rt__axi_wr_full_END                  (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_cvdr_sram__axi_wr_full_START              (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_cvdr_sram__axi_wr_full_END                (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_isp_fe_1__fcm__short_wr_evt_0_START       (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_isp_fe_1__fcm__short_wr_evt_0_END         (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_isp_fe_1__fcm__short_rd_evt_0_START       (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_isp_fe_1__fcm__short_rd_evt_0_END         (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_isp_fe_2__fcm__short_wr_evt_1_START       (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_isp_fe_2__fcm__short_wr_evt_1_END         (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_isp_fe_2__fcm__short_rd_evt_1_START       (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_isp_fe_2__fcm__short_rd_evt_1_END         (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_scaler_1_1_y__fcm__short_wr_evt_2_START   (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_scaler_1_1_y__fcm__short_wr_evt_2_END     (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_scaler_1_1_y__fcm__short_rd_evt_2_START   (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_scaler_1_1_y__fcm__short_rd_evt_2_END     (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_scaler_1_1_uv__fcm__short_wr_evt_3_START  (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_scaler_1_1_uv__fcm__short_wr_evt_3_END    (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_scaler_1_1_uv__fcm__short_rd_evt_3_START  (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_scaler_1_1_uv__fcm__short_rd_evt_3_END    (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_scaler_1_2_y__fcm__short_wr_evt_4_START   (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_scaler_1_2_y__fcm__short_wr_evt_4_END     (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_scaler_1_2_y__fcm__short_rd_evt_4_START   (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_scaler_1_2_y__fcm__short_rd_evt_4_END     (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_scaler_1_2_uv__fcm__short_wr_evt_5_START  (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_scaler_1_2_uv__fcm__short_wr_evt_5_END    (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_scaler_1_2_uv__fcm__short_rd_evt_5_START  (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_scaler_1_2_uv__fcm__short_rd_evt_5_END    (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_prescaler__end_of_frame_error_START       (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_prescaler__end_of_frame_error_END         (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__cam_a_ovf_START            (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__cam_a_ovf_END              (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__cam_b_ovf_START            (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__cam_b_ovf_END              (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__cam_c_ovf_START            (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__cam_c_ovf_END              (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__reformater_h_err_0_START   (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__reformater_h_err_0_END     (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__reformater_h_err_1_START   (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__reformater_h_err_1_END     (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__reformater_h_err_2_START   (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__reformater_h_err_2_END     (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__reformater_h_err_3_START   (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__reformater_h_err_3_END     (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__reformater_h_err_4_START   (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__reformater_h_err_4_END     (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__reformater_h_err_5_START   (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__reformater_h_err_5_END     (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__reformater_h_err_6_START   (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__reformater_h_err_6_END     (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__reformater_h_err_7_START   (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__reformater_h_err_7_END     (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__reformater_err_0_START     (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__reformater_err_0_END       (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__reformater_err_1_START     (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__reformater_err_1_END       (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__reformater_err_2_START     (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__reformater_err_2_END       (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__reformater_err_3_START     (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__reformater_err_3_END       (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__reformater_err_4_START     (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__reformater_err_4_END       (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__reformater_err_5_START     (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_0_stream_router__reformater_err_5_END       (31)


/*****************************************************************************
 结构名    : SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_UNION
 结构说明  : IRQ_MERGER_ISR_ERROR_0 寄存器结构定义。地址偏移量:0x90，初值:0x00000000，宽度:32
 寄存器说明: [Interrupt Set Register] ERROR register (bloc 0 over 1).
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cvdr_rt__axi_wr_full               : 1;  /* bit[0-0]  : source: NA [31 over 46] NC */
        unsigned int  cvdr_sram__axi_wr_full             : 1;  /* bit[1-1]  : source: NA [30 over 46] NC */
        unsigned int  isp_fe_1__fcm__short_wr_evt_0      : 1;  /* bit[2-2]  : source: ISP_FE_1 [29 over 46] NC */
        unsigned int  isp_fe_1__fcm__short_rd_evt_0      : 1;  /* bit[3-3]  : source: ISP_FE_1 [28 over 46] NC */
        unsigned int  isp_fe_2__fcm__short_wr_evt_1      : 1;  /* bit[4-4]  : source: ISP_FE_2 [27 over 46] NC */
        unsigned int  isp_fe_2__fcm__short_rd_evt_1      : 1;  /* bit[5-5]  : source: ISP_FE_2 [26 over 46] NC */
        unsigned int  scaler_1_1_y__fcm__short_wr_evt_2  : 1;  /* bit[6-6]  : source: SCALER_1_1(Y) [25 over 46] NC */
        unsigned int  scaler_1_1_y__fcm__short_rd_evt_2  : 1;  /* bit[7-7]  : source: SCALER_1_1(Y) [24 over 46] NC */
        unsigned int  scaler_1_1_uv__fcm__short_wr_evt_3 : 1;  /* bit[8-8]  : source: SCALER_1_1(UV) [23 over 46] NC */
        unsigned int  scaler_1_1_uv__fcm__short_rd_evt_3 : 1;  /* bit[9-9]  : source: SCALER_1_1(UV) [22 over 46] NC */
        unsigned int  scaler_1_2_y__fcm__short_wr_evt_4  : 1;  /* bit[10-10]: source: SCALER_1_2(Y) [21 over 46] NC */
        unsigned int  scaler_1_2_y__fcm__short_rd_evt_4  : 1;  /* bit[11-11]: source: SCALER_1_2(Y) [20 over 46] NC */
        unsigned int  scaler_1_2_uv__fcm__short_wr_evt_5 : 1;  /* bit[12-12]: source: SCALER_1_2(UV) [19 over 46] NC */
        unsigned int  scaler_1_2_uv__fcm__short_rd_evt_5 : 1;  /* bit[13-13]: source: SCALER_1_2(UV) [18 over 46] NC */
        unsigned int  prescaler__end_of_frame_error      : 1;  /* bit[14-14]: source: NA [17 over 46] NC */
        unsigned int  stream_router__cam_a_ovf           : 1;  /* bit[15-15]: source: NA [16 over 46] NC */
        unsigned int  stream_router__cam_b_ovf           : 1;  /* bit[16-16]: source: NA [15 over 46] NC */
        unsigned int  stream_router__cam_c_ovf           : 1;  /* bit[17-17]: source: NA [14 over 46] NC */
        unsigned int  stream_router__reformater_h_err_0  : 1;  /* bit[18-18]: source: NA [13 over 46] NC */
        unsigned int  stream_router__reformater_h_err_1  : 1;  /* bit[19-19]: source: NA [12 over 46] NC */
        unsigned int  stream_router__reformater_h_err_2  : 1;  /* bit[20-20]: source: NA [11 over 46] NC */
        unsigned int  stream_router__reformater_h_err_3  : 1;  /* bit[21-21]: source: NA [10 over 46] NC */
        unsigned int  stream_router__reformater_h_err_4  : 1;  /* bit[22-22]: source: NA [9 over 46] NC */
        unsigned int  stream_router__reformater_h_err_5  : 1;  /* bit[23-23]: source: NA [8 over 46] NC */
        unsigned int  stream_router__reformater_h_err_6  : 1;  /* bit[24-24]: source: NA [7 over 46] NC */
        unsigned int  stream_router__reformater_h_err_7  : 1;  /* bit[25-25]: source: NA [6 over 46] NC */
        unsigned int  stream_router__reformater_err_0    : 1;  /* bit[26-26]: source: NA [5 over 46] NC */
        unsigned int  stream_router__reformater_err_1    : 1;  /* bit[27-27]: source: NA [4 over 46] NC */
        unsigned int  stream_router__reformater_err_2    : 1;  /* bit[28-28]: source: NA [3 over 46] NC */
        unsigned int  stream_router__reformater_err_3    : 1;  /* bit[29-29]: source: NA [2 over 46] NC */
        unsigned int  stream_router__reformater_err_4    : 1;  /* bit[30-30]: source: NA [1 over 46] NC */
        unsigned int  stream_router__reformater_err_5    : 1;  /* bit[31-31]: source: NA [0 over 46] NC */
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_cvdr_rt__axi_wr_full_START                (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_cvdr_rt__axi_wr_full_END                  (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_cvdr_sram__axi_wr_full_START              (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_cvdr_sram__axi_wr_full_END                (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_isp_fe_1__fcm__short_wr_evt_0_START       (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_isp_fe_1__fcm__short_wr_evt_0_END         (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_isp_fe_1__fcm__short_rd_evt_0_START       (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_isp_fe_1__fcm__short_rd_evt_0_END         (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_isp_fe_2__fcm__short_wr_evt_1_START       (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_isp_fe_2__fcm__short_wr_evt_1_END         (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_isp_fe_2__fcm__short_rd_evt_1_START       (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_isp_fe_2__fcm__short_rd_evt_1_END         (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_scaler_1_1_y__fcm__short_wr_evt_2_START   (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_scaler_1_1_y__fcm__short_wr_evt_2_END     (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_scaler_1_1_y__fcm__short_rd_evt_2_START   (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_scaler_1_1_y__fcm__short_rd_evt_2_END     (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_scaler_1_1_uv__fcm__short_wr_evt_3_START  (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_scaler_1_1_uv__fcm__short_wr_evt_3_END    (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_scaler_1_1_uv__fcm__short_rd_evt_3_START  (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_scaler_1_1_uv__fcm__short_rd_evt_3_END    (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_scaler_1_2_y__fcm__short_wr_evt_4_START   (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_scaler_1_2_y__fcm__short_wr_evt_4_END     (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_scaler_1_2_y__fcm__short_rd_evt_4_START   (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_scaler_1_2_y__fcm__short_rd_evt_4_END     (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_scaler_1_2_uv__fcm__short_wr_evt_5_START  (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_scaler_1_2_uv__fcm__short_wr_evt_5_END    (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_scaler_1_2_uv__fcm__short_rd_evt_5_START  (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_scaler_1_2_uv__fcm__short_rd_evt_5_END    (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_prescaler__end_of_frame_error_START       (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_prescaler__end_of_frame_error_END         (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__cam_a_ovf_START            (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__cam_a_ovf_END              (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__cam_b_ovf_START            (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__cam_b_ovf_END              (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__cam_c_ovf_START            (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__cam_c_ovf_END              (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__reformater_h_err_0_START   (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__reformater_h_err_0_END     (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__reformater_h_err_1_START   (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__reformater_h_err_1_END     (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__reformater_h_err_2_START   (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__reformater_h_err_2_END     (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__reformater_h_err_3_START   (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__reformater_h_err_3_END     (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__reformater_h_err_4_START   (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__reformater_h_err_4_END     (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__reformater_h_err_5_START   (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__reformater_h_err_5_END     (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__reformater_h_err_6_START   (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__reformater_h_err_6_END     (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__reformater_h_err_7_START   (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__reformater_h_err_7_END     (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__reformater_err_0_START     (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__reformater_err_0_END       (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__reformater_err_1_START     (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__reformater_err_1_END       (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__reformater_err_2_START     (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__reformater_err_2_END       (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__reformater_err_3_START     (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__reformater_err_3_END       (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__reformater_err_4_START     (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__reformater_err_4_END       (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__reformater_err_5_START     (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_0_stream_router__reformater_err_5_END       (31)


/*****************************************************************************
 结构名    : SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_1_UNION
 结构说明  : IRQ_MERGER_IMSC_ERROR_1 寄存器结构定义。地址偏移量:0xA0，初值:0x00000000，宽度:32
 寄存器说明: [Interrupt Mask Register] ERROR register (bloc 1 over 1).
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stream_router__reformater_err_6           : 1;  /* bit[0-0]  : source: NA [63 over 46] NC */
        unsigned int  stream_router__reformater_err_7           : 1;  /* bit[1-1]  : source: NA [62 over 46] NC */
        unsigned int  stream_router__reformater_frame_dropped_0 : 1;  /* bit[2-2]  : source: NA [61 over 46] NC */
        unsigned int  stream_router__reformater_frame_dropped_1 : 1;  /* bit[3-3]  : source: NA [60 over 46] NC */
        unsigned int  stream_router__reformater_frame_dropped_2 : 1;  /* bit[4-4]  : source: NA [59 over 46] NC */
        unsigned int  stream_router__reformater_frame_dropped_3 : 1;  /* bit[5-5]  : source: NA [58 over 46] NC */
        unsigned int  stream_router__reformater_frame_dropped_4 : 1;  /* bit[6-6]  : source: NA [57 over 46] NC */
        unsigned int  stream_router__reformater_frame_dropped_5 : 1;  /* bit[7-7]  : source: NA [56 over 46] NC */
        unsigned int  stream_router__reformater_frame_dropped_6 : 1;  /* bit[8-8]  : source: NA [55 over 46] NC */
        unsigned int  stream_router__reformater_frame_dropped_7 : 1;  /* bit[9-9]  : source: NA [54 over 46] NC */
        unsigned int  frame_merger__end_of_frame_error          : 1;  /* bit[10-10]: source: NA [53 over 46] NC */
        unsigned int  cvdr_rt__axi_wr_resp_err                  : 1;  /* bit[11-11]: source: NA [52 over 46] NC */
        unsigned int  cvdr_rt__axi_rd_resp_err                  : 1;  /* bit[12-12]: source: NA [51 over 46] NC */
        unsigned int  reserved_0                                : 1;  /* bit[13-13]: source: NA [50 over 46] NC */
        unsigned int  reserved_1                                : 1;  /* bit[14-14]: source: NA [49 over 46] NC */
        unsigned int  reserved_2                                : 1;  /* bit[15-15]: - */
        unsigned int  reserved_3                                : 1;  /* bit[16-16]: - */
        unsigned int  reserved_4                                : 1;  /* bit[17-17]: - */
        unsigned int  reserved_5                                : 1;  /* bit[18-18]: - */
        unsigned int  reserved_6                                : 1;  /* bit[19-19]: - */
        unsigned int  reserved_7                                : 1;  /* bit[20-20]: - */
        unsigned int  reserved_8                                : 1;  /* bit[21-21]: - */
        unsigned int  reserved_9                                : 1;  /* bit[22-22]: - */
        unsigned int  reserved_10                               : 1;  /* bit[23-23]: - */
        unsigned int  reserved_11                               : 1;  /* bit[24-24]: - */
        unsigned int  reserved_12                               : 1;  /* bit[25-25]: - */
        unsigned int  reserved_13                               : 1;  /* bit[26-26]: - */
        unsigned int  reserved_14                               : 1;  /* bit[27-27]: - */
        unsigned int  reserved_15                               : 1;  /* bit[28-28]: - */
        unsigned int  reserved_16                               : 1;  /* bit[29-29]: - */
        unsigned int  reserved_17                               : 1;  /* bit[30-30]: - */
        unsigned int  reserved_18                               : 1;  /* bit[31-31]: - */
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_1_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_1_stream_router__reformater_err_6_START            (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_1_stream_router__reformater_err_6_END              (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_1_stream_router__reformater_err_7_START            (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_1_stream_router__reformater_err_7_END              (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_1_stream_router__reformater_frame_dropped_0_START  (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_1_stream_router__reformater_frame_dropped_0_END    (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_1_stream_router__reformater_frame_dropped_1_START  (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_1_stream_router__reformater_frame_dropped_1_END    (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_1_stream_router__reformater_frame_dropped_2_START  (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_1_stream_router__reformater_frame_dropped_2_END    (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_1_stream_router__reformater_frame_dropped_3_START  (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_1_stream_router__reformater_frame_dropped_3_END    (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_1_stream_router__reformater_frame_dropped_4_START  (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_1_stream_router__reformater_frame_dropped_4_END    (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_1_stream_router__reformater_frame_dropped_5_START  (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_1_stream_router__reformater_frame_dropped_5_END    (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_1_stream_router__reformater_frame_dropped_6_START  (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_1_stream_router__reformater_frame_dropped_6_END    (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_1_stream_router__reformater_frame_dropped_7_START  (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_1_stream_router__reformater_frame_dropped_7_END    (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_1_frame_merger__end_of_frame_error_START           (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_1_frame_merger__end_of_frame_error_END             (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_1_cvdr_rt__axi_wr_resp_err_START                   (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_1_cvdr_rt__axi_wr_resp_err_END                     (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_1_cvdr_rt__axi_rd_resp_err_START                   (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_ERROR_1_cvdr_rt__axi_rd_resp_err_END                     (12)


/*****************************************************************************
 结构名    : SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_1_UNION
 结构说明  : IRQ_MERGER_RIS_ERROR_1 寄存器结构定义。地址偏移量:0xA4，初值:0x00000000，宽度:32
 寄存器说明: [Raw Interrupt Status Register] ERROR register (bloc 1 over 1).
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stream_router__reformater_err_6           : 1;  /* bit[0-0]  : source: NA [63 over 46] NC */
        unsigned int  stream_router__reformater_err_7           : 1;  /* bit[1-1]  : source: NA [62 over 46] NC */
        unsigned int  stream_router__reformater_frame_dropped_0 : 1;  /* bit[2-2]  : source: NA [61 over 46] NC */
        unsigned int  stream_router__reformater_frame_dropped_1 : 1;  /* bit[3-3]  : source: NA [60 over 46] NC */
        unsigned int  stream_router__reformater_frame_dropped_2 : 1;  /* bit[4-4]  : source: NA [59 over 46] NC */
        unsigned int  stream_router__reformater_frame_dropped_3 : 1;  /* bit[5-5]  : source: NA [58 over 46] NC */
        unsigned int  stream_router__reformater_frame_dropped_4 : 1;  /* bit[6-6]  : source: NA [57 over 46] NC */
        unsigned int  stream_router__reformater_frame_dropped_5 : 1;  /* bit[7-7]  : source: NA [56 over 46] NC */
        unsigned int  stream_router__reformater_frame_dropped_6 : 1;  /* bit[8-8]  : source: NA [55 over 46] NC */
        unsigned int  stream_router__reformater_frame_dropped_7 : 1;  /* bit[9-9]  : source: NA [54 over 46] NC */
        unsigned int  frame_merger__end_of_frame_error          : 1;  /* bit[10-10]: source: NA [53 over 46] NC */
        unsigned int  cvdr_rt__axi_wr_resp_err                  : 1;  /* bit[11-11]: source: NA [52 over 46] NC */
        unsigned int  cvdr_rt__axi_rd_resp_err                  : 1;  /* bit[12-12]: source: NA [51 over 46] NC */
        unsigned int  reserved_0                                : 1;  /* bit[13-13]: source: NA [50 over 46] NC */
        unsigned int  reserved_1                                : 1;  /* bit[14-14]: source: NA [49 over 46] NC */
        unsigned int  reserved_2                                : 1;  /* bit[15-15]: - */
        unsigned int  reserved_3                                : 1;  /* bit[16-16]: - */
        unsigned int  reserved_4                                : 1;  /* bit[17-17]: - */
        unsigned int  reserved_5                                : 1;  /* bit[18-18]: - */
        unsigned int  reserved_6                                : 1;  /* bit[19-19]: - */
        unsigned int  reserved_7                                : 1;  /* bit[20-20]: - */
        unsigned int  reserved_8                                : 1;  /* bit[21-21]: - */
        unsigned int  reserved_9                                : 1;  /* bit[22-22]: - */
        unsigned int  reserved_10                               : 1;  /* bit[23-23]: - */
        unsigned int  reserved_11                               : 1;  /* bit[24-24]: - */
        unsigned int  reserved_12                               : 1;  /* bit[25-25]: - */
        unsigned int  reserved_13                               : 1;  /* bit[26-26]: - */
        unsigned int  reserved_14                               : 1;  /* bit[27-27]: - */
        unsigned int  reserved_15                               : 1;  /* bit[28-28]: - */
        unsigned int  reserved_16                               : 1;  /* bit[29-29]: - */
        unsigned int  reserved_17                               : 1;  /* bit[30-30]: - */
        unsigned int  reserved_18                               : 1;  /* bit[31-31]: - */
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_1_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_1_stream_router__reformater_err_6_START            (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_1_stream_router__reformater_err_6_END              (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_1_stream_router__reformater_err_7_START            (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_1_stream_router__reformater_err_7_END              (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_1_stream_router__reformater_frame_dropped_0_START  (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_1_stream_router__reformater_frame_dropped_0_END    (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_1_stream_router__reformater_frame_dropped_1_START  (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_1_stream_router__reformater_frame_dropped_1_END    (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_1_stream_router__reformater_frame_dropped_2_START  (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_1_stream_router__reformater_frame_dropped_2_END    (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_1_stream_router__reformater_frame_dropped_3_START  (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_1_stream_router__reformater_frame_dropped_3_END    (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_1_stream_router__reformater_frame_dropped_4_START  (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_1_stream_router__reformater_frame_dropped_4_END    (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_1_stream_router__reformater_frame_dropped_5_START  (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_1_stream_router__reformater_frame_dropped_5_END    (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_1_stream_router__reformater_frame_dropped_6_START  (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_1_stream_router__reformater_frame_dropped_6_END    (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_1_stream_router__reformater_frame_dropped_7_START  (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_1_stream_router__reformater_frame_dropped_7_END    (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_1_frame_merger__end_of_frame_error_START           (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_1_frame_merger__end_of_frame_error_END             (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_1_cvdr_rt__axi_wr_resp_err_START                   (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_1_cvdr_rt__axi_wr_resp_err_END                     (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_1_cvdr_rt__axi_rd_resp_err_START                   (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_ERROR_1_cvdr_rt__axi_rd_resp_err_END                     (12)


/*****************************************************************************
 结构名    : SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_1_UNION
 结构说明  : IRQ_MERGER_MIS_ERROR_1 寄存器结构定义。地址偏移量:0xA8，初值:0x00000000，宽度:32
 寄存器说明: [Masked Interrupt Status Register] ERROR register (bloc 1 over 1).
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stream_router__reformater_err_6           : 1;  /* bit[0-0]  : source: NA [63 over 46] NC */
        unsigned int  stream_router__reformater_err_7           : 1;  /* bit[1-1]  : source: NA [62 over 46] NC */
        unsigned int  stream_router__reformater_frame_dropped_0 : 1;  /* bit[2-2]  : source: NA [61 over 46] NC */
        unsigned int  stream_router__reformater_frame_dropped_1 : 1;  /* bit[3-3]  : source: NA [60 over 46] NC */
        unsigned int  stream_router__reformater_frame_dropped_2 : 1;  /* bit[4-4]  : source: NA [59 over 46] NC */
        unsigned int  stream_router__reformater_frame_dropped_3 : 1;  /* bit[5-5]  : source: NA [58 over 46] NC */
        unsigned int  stream_router__reformater_frame_dropped_4 : 1;  /* bit[6-6]  : source: NA [57 over 46] NC */
        unsigned int  stream_router__reformater_frame_dropped_5 : 1;  /* bit[7-7]  : source: NA [56 over 46] NC */
        unsigned int  stream_router__reformater_frame_dropped_6 : 1;  /* bit[8-8]  : source: NA [55 over 46] NC */
        unsigned int  stream_router__reformater_frame_dropped_7 : 1;  /* bit[9-9]  : source: NA [54 over 46] NC */
        unsigned int  frame_merger__end_of_frame_error          : 1;  /* bit[10-10]: source: NA [53 over 46] NC */
        unsigned int  cvdr_rt__axi_wr_resp_err                  : 1;  /* bit[11-11]: source: NA [52 over 46] NC */
        unsigned int  cvdr_rt__axi_rd_resp_err                  : 1;  /* bit[12-12]: source: NA [51 over 46] NC */
        unsigned int  reserved_0                                : 1;  /* bit[13-13]: source: NA [50 over 46] NC */
        unsigned int  reserved_1                                : 1;  /* bit[14-14]: source: NA [49 over 46] NC */
        unsigned int  reserved_2                                : 1;  /* bit[15-15]: - */
        unsigned int  reserved_3                                : 1;  /* bit[16-16]: - */
        unsigned int  reserved_4                                : 1;  /* bit[17-17]: - */
        unsigned int  reserved_5                                : 1;  /* bit[18-18]: - */
        unsigned int  reserved_6                                : 1;  /* bit[19-19]: - */
        unsigned int  reserved_7                                : 1;  /* bit[20-20]: - */
        unsigned int  reserved_8                                : 1;  /* bit[21-21]: - */
        unsigned int  reserved_9                                : 1;  /* bit[22-22]: - */
        unsigned int  reserved_10                               : 1;  /* bit[23-23]: - */
        unsigned int  reserved_11                               : 1;  /* bit[24-24]: - */
        unsigned int  reserved_12                               : 1;  /* bit[25-25]: - */
        unsigned int  reserved_13                               : 1;  /* bit[26-26]: - */
        unsigned int  reserved_14                               : 1;  /* bit[27-27]: - */
        unsigned int  reserved_15                               : 1;  /* bit[28-28]: - */
        unsigned int  reserved_16                               : 1;  /* bit[29-29]: - */
        unsigned int  reserved_17                               : 1;  /* bit[30-30]: - */
        unsigned int  reserved_18                               : 1;  /* bit[31-31]: - */
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_1_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_1_stream_router__reformater_err_6_START            (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_1_stream_router__reformater_err_6_END              (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_1_stream_router__reformater_err_7_START            (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_1_stream_router__reformater_err_7_END              (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_1_stream_router__reformater_frame_dropped_0_START  (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_1_stream_router__reformater_frame_dropped_0_END    (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_1_stream_router__reformater_frame_dropped_1_START  (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_1_stream_router__reformater_frame_dropped_1_END    (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_1_stream_router__reformater_frame_dropped_2_START  (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_1_stream_router__reformater_frame_dropped_2_END    (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_1_stream_router__reformater_frame_dropped_3_START  (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_1_stream_router__reformater_frame_dropped_3_END    (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_1_stream_router__reformater_frame_dropped_4_START  (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_1_stream_router__reformater_frame_dropped_4_END    (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_1_stream_router__reformater_frame_dropped_5_START  (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_1_stream_router__reformater_frame_dropped_5_END    (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_1_stream_router__reformater_frame_dropped_6_START  (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_1_stream_router__reformater_frame_dropped_6_END    (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_1_stream_router__reformater_frame_dropped_7_START  (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_1_stream_router__reformater_frame_dropped_7_END    (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_1_frame_merger__end_of_frame_error_START           (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_1_frame_merger__end_of_frame_error_END             (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_1_cvdr_rt__axi_wr_resp_err_START                   (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_1_cvdr_rt__axi_wr_resp_err_END                     (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_1_cvdr_rt__axi_rd_resp_err_START                   (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_ERROR_1_cvdr_rt__axi_rd_resp_err_END                     (12)


/*****************************************************************************
 结构名    : SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_1_UNION
 结构说明  : IRQ_MERGER_ICR_ERROR_1 寄存器结构定义。地址偏移量:0xAC，初值:0x00000000，宽度:32
 寄存器说明: [Interrupt Clear Register] ERROR register (bloc 1 over 1).
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stream_router__reformater_err_6           : 1;  /* bit[0-0]  : source: NA [63 over 46] NC */
        unsigned int  stream_router__reformater_err_7           : 1;  /* bit[1-1]  : source: NA [62 over 46] NC */
        unsigned int  stream_router__reformater_frame_dropped_0 : 1;  /* bit[2-2]  : source: NA [61 over 46] NC */
        unsigned int  stream_router__reformater_frame_dropped_1 : 1;  /* bit[3-3]  : source: NA [60 over 46] NC */
        unsigned int  stream_router__reformater_frame_dropped_2 : 1;  /* bit[4-4]  : source: NA [59 over 46] NC */
        unsigned int  stream_router__reformater_frame_dropped_3 : 1;  /* bit[5-5]  : source: NA [58 over 46] NC */
        unsigned int  stream_router__reformater_frame_dropped_4 : 1;  /* bit[6-6]  : source: NA [57 over 46] NC */
        unsigned int  stream_router__reformater_frame_dropped_5 : 1;  /* bit[7-7]  : source: NA [56 over 46] NC */
        unsigned int  stream_router__reformater_frame_dropped_6 : 1;  /* bit[8-8]  : source: NA [55 over 46] NC */
        unsigned int  stream_router__reformater_frame_dropped_7 : 1;  /* bit[9-9]  : source: NA [54 over 46] NC */
        unsigned int  frame_merger__end_of_frame_error          : 1;  /* bit[10-10]: source: NA [53 over 46] NC */
        unsigned int  cvdr_rt__axi_wr_resp_err                  : 1;  /* bit[11-11]: source: NA [52 over 46] NC */
        unsigned int  cvdr_rt__axi_rd_resp_err                  : 1;  /* bit[12-12]: source: NA [51 over 46] NC */
        unsigned int  reserved_0                                : 1;  /* bit[13-13]: source: NA [50 over 46] NC */
        unsigned int  reserved_1                                : 1;  /* bit[14-14]: source: NA [49 over 46] NC */
        unsigned int  reserved_2                                : 1;  /* bit[15-15]: - */
        unsigned int  reserved_3                                : 1;  /* bit[16-16]: - */
        unsigned int  reserved_4                                : 1;  /* bit[17-17]: - */
        unsigned int  reserved_5                                : 1;  /* bit[18-18]: - */
        unsigned int  reserved_6                                : 1;  /* bit[19-19]: - */
        unsigned int  reserved_7                                : 1;  /* bit[20-20]: - */
        unsigned int  reserved_8                                : 1;  /* bit[21-21]: - */
        unsigned int  reserved_9                                : 1;  /* bit[22-22]: - */
        unsigned int  reserved_10                               : 1;  /* bit[23-23]: - */
        unsigned int  reserved_11                               : 1;  /* bit[24-24]: - */
        unsigned int  reserved_12                               : 1;  /* bit[25-25]: - */
        unsigned int  reserved_13                               : 1;  /* bit[26-26]: - */
        unsigned int  reserved_14                               : 1;  /* bit[27-27]: - */
        unsigned int  reserved_15                               : 1;  /* bit[28-28]: - */
        unsigned int  reserved_16                               : 1;  /* bit[29-29]: - */
        unsigned int  reserved_17                               : 1;  /* bit[30-30]: - */
        unsigned int  reserved_18                               : 1;  /* bit[31-31]: - */
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_1_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_1_stream_router__reformater_err_6_START            (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_1_stream_router__reformater_err_6_END              (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_1_stream_router__reformater_err_7_START            (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_1_stream_router__reformater_err_7_END              (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_1_stream_router__reformater_frame_dropped_0_START  (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_1_stream_router__reformater_frame_dropped_0_END    (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_1_stream_router__reformater_frame_dropped_1_START  (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_1_stream_router__reformater_frame_dropped_1_END    (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_1_stream_router__reformater_frame_dropped_2_START  (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_1_stream_router__reformater_frame_dropped_2_END    (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_1_stream_router__reformater_frame_dropped_3_START  (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_1_stream_router__reformater_frame_dropped_3_END    (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_1_stream_router__reformater_frame_dropped_4_START  (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_1_stream_router__reformater_frame_dropped_4_END    (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_1_stream_router__reformater_frame_dropped_5_START  (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_1_stream_router__reformater_frame_dropped_5_END    (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_1_stream_router__reformater_frame_dropped_6_START  (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_1_stream_router__reformater_frame_dropped_6_END    (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_1_stream_router__reformater_frame_dropped_7_START  (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_1_stream_router__reformater_frame_dropped_7_END    (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_1_frame_merger__end_of_frame_error_START           (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_1_frame_merger__end_of_frame_error_END             (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_1_cvdr_rt__axi_wr_resp_err_START                   (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_1_cvdr_rt__axi_wr_resp_err_END                     (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_1_cvdr_rt__axi_rd_resp_err_START                   (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_ERROR_1_cvdr_rt__axi_rd_resp_err_END                     (12)


/*****************************************************************************
 结构名    : SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_1_UNION
 结构说明  : IRQ_MERGER_ISR_ERROR_1 寄存器结构定义。地址偏移量:0xB0，初值:0x00000000，宽度:32
 寄存器说明: [Interrupt Set Register] ERROR register (bloc 1 over 1).
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stream_router__reformater_err_6           : 1;  /* bit[0-0]  : source: NA [63 over 46] NC */
        unsigned int  stream_router__reformater_err_7           : 1;  /* bit[1-1]  : source: NA [62 over 46] NC */
        unsigned int  stream_router__reformater_frame_dropped_0 : 1;  /* bit[2-2]  : source: NA [61 over 46] NC */
        unsigned int  stream_router__reformater_frame_dropped_1 : 1;  /* bit[3-3]  : source: NA [60 over 46] NC */
        unsigned int  stream_router__reformater_frame_dropped_2 : 1;  /* bit[4-4]  : source: NA [59 over 46] NC */
        unsigned int  stream_router__reformater_frame_dropped_3 : 1;  /* bit[5-5]  : source: NA [58 over 46] NC */
        unsigned int  stream_router__reformater_frame_dropped_4 : 1;  /* bit[6-6]  : source: NA [57 over 46] NC */
        unsigned int  stream_router__reformater_frame_dropped_5 : 1;  /* bit[7-7]  : source: NA [56 over 46] NC */
        unsigned int  stream_router__reformater_frame_dropped_6 : 1;  /* bit[8-8]  : source: NA [55 over 46] NC */
        unsigned int  stream_router__reformater_frame_dropped_7 : 1;  /* bit[9-9]  : source: NA [54 over 46] NC */
        unsigned int  frame_merger__end_of_frame_error          : 1;  /* bit[10-10]: source: NA [53 over 46] NC */
        unsigned int  cvdr_rt__axi_wr_resp_err                  : 1;  /* bit[11-11]: source: NA [52 over 46] NC */
        unsigned int  cvdr_rt__axi_rd_resp_err                  : 1;  /* bit[12-12]: source: NA [51 over 46] NC */
        unsigned int  reserved_0                                : 1;  /* bit[13-13]: source: NA [50 over 46] NC */
        unsigned int  reserved_1                                : 1;  /* bit[14-14]: source: NA [49 over 46] NC */
        unsigned int  reserved_2                                : 1;  /* bit[15-15]: - */
        unsigned int  reserved_3                                : 1;  /* bit[16-16]: - */
        unsigned int  reserved_4                                : 1;  /* bit[17-17]: - */
        unsigned int  reserved_5                                : 1;  /* bit[18-18]: - */
        unsigned int  reserved_6                                : 1;  /* bit[19-19]: - */
        unsigned int  reserved_7                                : 1;  /* bit[20-20]: - */
        unsigned int  reserved_8                                : 1;  /* bit[21-21]: - */
        unsigned int  reserved_9                                : 1;  /* bit[22-22]: - */
        unsigned int  reserved_10                               : 1;  /* bit[23-23]: - */
        unsigned int  reserved_11                               : 1;  /* bit[24-24]: - */
        unsigned int  reserved_12                               : 1;  /* bit[25-25]: - */
        unsigned int  reserved_13                               : 1;  /* bit[26-26]: - */
        unsigned int  reserved_14                               : 1;  /* bit[27-27]: - */
        unsigned int  reserved_15                               : 1;  /* bit[28-28]: - */
        unsigned int  reserved_16                               : 1;  /* bit[29-29]: - */
        unsigned int  reserved_17                               : 1;  /* bit[30-30]: - */
        unsigned int  reserved_18                               : 1;  /* bit[31-31]: - */
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_1_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_1_stream_router__reformater_err_6_START            (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_1_stream_router__reformater_err_6_END              (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_1_stream_router__reformater_err_7_START            (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_1_stream_router__reformater_err_7_END              (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_1_stream_router__reformater_frame_dropped_0_START  (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_1_stream_router__reformater_frame_dropped_0_END    (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_1_stream_router__reformater_frame_dropped_1_START  (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_1_stream_router__reformater_frame_dropped_1_END    (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_1_stream_router__reformater_frame_dropped_2_START  (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_1_stream_router__reformater_frame_dropped_2_END    (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_1_stream_router__reformater_frame_dropped_3_START  (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_1_stream_router__reformater_frame_dropped_3_END    (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_1_stream_router__reformater_frame_dropped_4_START  (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_1_stream_router__reformater_frame_dropped_4_END    (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_1_stream_router__reformater_frame_dropped_5_START  (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_1_stream_router__reformater_frame_dropped_5_END    (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_1_stream_router__reformater_frame_dropped_6_START  (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_1_stream_router__reformater_frame_dropped_6_END    (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_1_stream_router__reformater_frame_dropped_7_START  (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_1_stream_router__reformater_frame_dropped_7_END    (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_1_frame_merger__end_of_frame_error_START           (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_1_frame_merger__end_of_frame_error_END             (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_1_cvdr_rt__axi_wr_resp_err_START                   (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_1_cvdr_rt__axi_wr_resp_err_END                     (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_1_cvdr_rt__axi_rd_resp_err_START                   (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_ERROR_1_cvdr_rt__axi_rd_resp_err_END                     (12)


/*****************************************************************************
 结构名    : SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_UNION
 结构说明  : IRQ_MERGER_IMSC_FRPROC_0 寄存器结构定义。地址偏移量:0xC0，初值:0x00000000，宽度:32
 寄存器说明: [Interrupt Mask Register] FRPROC register (bloc 0 over 1).
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  otap_1_1__cvdr_rt__eof_vpwr_0          : 1;  /* bit[0-0]  : source: OTAP_1_1 [31 over 63] NC */
        unsigned int  otap_1_2__cvdr_rt__eof_vpwr_1          : 1;  /* bit[1-1]  : source: OTAP_1_2 [30 over 63] NC */
        unsigned int  scaler_3_y__cvdr_rt__eof_vpwr_2        : 1;  /* bit[2-2]  : source: SCALER_3(Y) [29 over 63] NC */
        unsigned int  scaler_3_uv__cvdr_rt__eof_vpwr_3       : 1;  /* bit[3-3]  : source: SCALER_3(UV) [28 over 63] NC */
        unsigned int  scaler_2_1_y__cvdr_rt__eof_vpwr_4      : 1;  /* bit[4-4]  : source: SCALER_2_1(Y) [27 over 63] NC */
        unsigned int  scaler_2_1_uv__cvdr_rt__eof_vpwr_5     : 1;  /* bit[5-5]  : source: SCALER_2_1(UV) [26 over 63] NC */
        unsigned int  scaler_2_2_y__cvdr_rt__eof_vpwr_6      : 1;  /* bit[6-6]  : source: SCALER_2_2(Y) [25 over 63] NC */
        unsigned int  scaler_2_2_uv__cvdr_rt__eof_vpwr_7     : 1;  /* bit[7-7]  : source: SCALER_2_2(UV) [24 over 63] NC */
        unsigned int  scaler_1_1_y__cvdr_rt__eof_vpwr_8      : 1;  /* bit[8-8]  : source: SCALER_1_1(Y) [23 over 63] NC */
        unsigned int  scaler_1_1_uv__cvdr_rt__eof_vpwr_9     : 1;  /* bit[9-9]  : source: SCALER_1_1(UV) [22 over 63] NC */
        unsigned int  scaler_1_2_y__cvdr_rt__eof_vpwr_10     : 1;  /* bit[10-10]: source: SCALER_1_2(Y) [21 over 63] NC */
        unsigned int  scaler_1_2_uv__cvdr_rt__eof_vpwr_11    : 1;  /* bit[11-11]: source: SCALER_1_2(UV) [20 over 63] NC */
        unsigned int  otap_2_1__cvdr_rt__eof_vpwr_14         : 1;  /* bit[12-12]: source: OTAP_2_1 [19 over 63] NC */
        unsigned int  otap_2_2__cvdr_rt__eof_vpwr_15         : 1;  /* bit[13-13]: source: OTAP_2_2 [18 over 63] NC */
        unsigned int  isp_fe_1__cvdr_rt__eof_vpwr_16         : 1;  /* bit[14-14]: source: ISP_FE_1 [17 over 63] NC */
        unsigned int  stream_router_1__cvdr_rt__eof_vpwr_18b : 1;  /* bit[15-15]: source: STREAM_ROUTER(1) [16 over 63] NC */
        unsigned int  isp_fe_2__cvdr_rt__eof_vpwr_17         : 1;  /* bit[16-16]: source: ISP_FE_2 [15 over 63] NC */
        unsigned int  stream_router_2__cvdr_rt__eof_vpwr_19b : 1;  /* bit[17-17]: source: STREAM_ROUTER(2) [14 over 63] NC */
        unsigned int  stat3a_1__cvdr_rt__eof_vpwr_20         : 1;  /* bit[18-18]: source: STAT3A_1 [13 over 63] NC */
        unsigned int  stat3a_2__cvdr_rt__eof_vpwr_21         : 1;  /* bit[19-19]: source: STAT3A_2 [12 over 63] NC */
        unsigned int  stream_router_3__cvdr_rt__eof_vpwr_22  : 1;  /* bit[20-20]: source: STREAM_ROUTER(3) [11 over 63] NC */
        unsigned int  stream_router_4__cvdr_rt__eof_vpwr_23  : 1;  /* bit[21-21]: source: STREAM_ROUTER(4) [10 over 63] NC */
        unsigned int  stream_router_5__cvdr_rt__eof_vpwr_24  : 1;  /* bit[22-22]: source: STREAM_ROUTER(5) [9 over 63] NC */
        unsigned int  jpgenc__cvdr_rt__eof_vpwr_25           : 1;  /* bit[23-23]: source: JPGENC [8 over 63] NC */
        unsigned int  isp_fe_1__fcm__sw_wr_ack_0             : 1;  /* bit[24-24]: source: ISP_FE_1 [7 over 63] NC */
        unsigned int  isp_fe_1__fcm__sw_rd_ack_0             : 1;  /* bit[25-25]: source: ISP_FE_1 [6 over 63] NC */
        unsigned int  isp_fe_2__fcm__sw_wr_ack_1             : 1;  /* bit[26-26]: source: ISP_FE_2 [5 over 63] NC */
        unsigned int  isp_fe_2__fcm__sw_rd_ack_1             : 1;  /* bit[27-27]: source: ISP_FE_2 [4 over 63] NC */
        unsigned int  scaler_1_1_y__fcm__sw_wr_ack_2         : 1;  /* bit[28-28]: source: SCALER_1_1(Y) [3 over 63] NC */
        unsigned int  scaler_1_1_y__fcm__sw_rd_ack_2         : 1;  /* bit[29-29]: source: SCALER_1_1(Y) [2 over 63] NC */
        unsigned int  scaler_1_1_uv__fcm__sw_wr_ack_3        : 1;  /* bit[30-30]: source: SCALER_1_1(UV) [1 over 63] NC */
        unsigned int  scaler_1_1_uv__fcm__sw_rd_ack_3        : 1;  /* bit[31-31]: source: SCALER_1_1(UV) [0 over 63] NC */
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_otap_1_1__cvdr_rt__eof_vpwr_0_START           (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_otap_1_1__cvdr_rt__eof_vpwr_0_END             (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_otap_1_2__cvdr_rt__eof_vpwr_1_START           (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_otap_1_2__cvdr_rt__eof_vpwr_1_END             (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_scaler_3_y__cvdr_rt__eof_vpwr_2_START         (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_scaler_3_y__cvdr_rt__eof_vpwr_2_END           (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_scaler_3_uv__cvdr_rt__eof_vpwr_3_START        (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_scaler_3_uv__cvdr_rt__eof_vpwr_3_END          (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_scaler_2_1_y__cvdr_rt__eof_vpwr_4_START       (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_scaler_2_1_y__cvdr_rt__eof_vpwr_4_END         (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_scaler_2_1_uv__cvdr_rt__eof_vpwr_5_START      (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_scaler_2_1_uv__cvdr_rt__eof_vpwr_5_END        (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_scaler_2_2_y__cvdr_rt__eof_vpwr_6_START       (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_scaler_2_2_y__cvdr_rt__eof_vpwr_6_END         (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_scaler_2_2_uv__cvdr_rt__eof_vpwr_7_START      (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_scaler_2_2_uv__cvdr_rt__eof_vpwr_7_END        (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_scaler_1_1_y__cvdr_rt__eof_vpwr_8_START       (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_scaler_1_1_y__cvdr_rt__eof_vpwr_8_END         (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_scaler_1_1_uv__cvdr_rt__eof_vpwr_9_START      (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_scaler_1_1_uv__cvdr_rt__eof_vpwr_9_END        (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_scaler_1_2_y__cvdr_rt__eof_vpwr_10_START      (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_scaler_1_2_y__cvdr_rt__eof_vpwr_10_END        (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_scaler_1_2_uv__cvdr_rt__eof_vpwr_11_START     (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_scaler_1_2_uv__cvdr_rt__eof_vpwr_11_END       (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_otap_2_1__cvdr_rt__eof_vpwr_14_START          (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_otap_2_1__cvdr_rt__eof_vpwr_14_END            (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_otap_2_2__cvdr_rt__eof_vpwr_15_START          (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_otap_2_2__cvdr_rt__eof_vpwr_15_END            (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_isp_fe_1__cvdr_rt__eof_vpwr_16_START          (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_isp_fe_1__cvdr_rt__eof_vpwr_16_END            (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_stream_router_1__cvdr_rt__eof_vpwr_18b_START  (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_stream_router_1__cvdr_rt__eof_vpwr_18b_END    (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_isp_fe_2__cvdr_rt__eof_vpwr_17_START          (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_isp_fe_2__cvdr_rt__eof_vpwr_17_END            (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_stream_router_2__cvdr_rt__eof_vpwr_19b_START  (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_stream_router_2__cvdr_rt__eof_vpwr_19b_END    (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_stat3a_1__cvdr_rt__eof_vpwr_20_START          (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_stat3a_1__cvdr_rt__eof_vpwr_20_END            (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_stat3a_2__cvdr_rt__eof_vpwr_21_START          (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_stat3a_2__cvdr_rt__eof_vpwr_21_END            (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_stream_router_3__cvdr_rt__eof_vpwr_22_START   (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_stream_router_3__cvdr_rt__eof_vpwr_22_END     (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_stream_router_4__cvdr_rt__eof_vpwr_23_START   (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_stream_router_4__cvdr_rt__eof_vpwr_23_END     (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_stream_router_5__cvdr_rt__eof_vpwr_24_START   (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_stream_router_5__cvdr_rt__eof_vpwr_24_END     (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_jpgenc__cvdr_rt__eof_vpwr_25_START            (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_jpgenc__cvdr_rt__eof_vpwr_25_END              (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_isp_fe_1__fcm__sw_wr_ack_0_START              (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_isp_fe_1__fcm__sw_wr_ack_0_END                (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_isp_fe_1__fcm__sw_rd_ack_0_START              (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_isp_fe_1__fcm__sw_rd_ack_0_END                (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_isp_fe_2__fcm__sw_wr_ack_1_START              (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_isp_fe_2__fcm__sw_wr_ack_1_END                (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_isp_fe_2__fcm__sw_rd_ack_1_START              (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_isp_fe_2__fcm__sw_rd_ack_1_END                (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_scaler_1_1_y__fcm__sw_wr_ack_2_START          (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_scaler_1_1_y__fcm__sw_wr_ack_2_END            (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_scaler_1_1_y__fcm__sw_rd_ack_2_START          (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_scaler_1_1_y__fcm__sw_rd_ack_2_END            (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_scaler_1_1_uv__fcm__sw_wr_ack_3_START         (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_scaler_1_1_uv__fcm__sw_wr_ack_3_END           (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_scaler_1_1_uv__fcm__sw_rd_ack_3_START         (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_0_scaler_1_1_uv__fcm__sw_rd_ack_3_END           (31)


/*****************************************************************************
 结构名    : SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_UNION
 结构说明  : IRQ_MERGER_RIS_FRPROC_0 寄存器结构定义。地址偏移量:0xC4，初值:0x00000000，宽度:32
 寄存器说明: [Raw Interrupt Status Register] FRPROC register (bloc 0 over 1).
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  otap_1_1__cvdr_rt__eof_vpwr_0          : 1;  /* bit[0-0]  : source: OTAP_1_1 [31 over 63] NC */
        unsigned int  otap_1_2__cvdr_rt__eof_vpwr_1          : 1;  /* bit[1-1]  : source: OTAP_1_2 [30 over 63] NC */
        unsigned int  scaler_3_y__cvdr_rt__eof_vpwr_2        : 1;  /* bit[2-2]  : source: SCALER_3(Y) [29 over 63] NC */
        unsigned int  scaler_3_uv__cvdr_rt__eof_vpwr_3       : 1;  /* bit[3-3]  : source: SCALER_3(UV) [28 over 63] NC */
        unsigned int  scaler_2_1_y__cvdr_rt__eof_vpwr_4      : 1;  /* bit[4-4]  : source: SCALER_2_1(Y) [27 over 63] NC */
        unsigned int  scaler_2_1_uv__cvdr_rt__eof_vpwr_5     : 1;  /* bit[5-5]  : source: SCALER_2_1(UV) [26 over 63] NC */
        unsigned int  scaler_2_2_y__cvdr_rt__eof_vpwr_6      : 1;  /* bit[6-6]  : source: SCALER_2_2(Y) [25 over 63] NC */
        unsigned int  scaler_2_2_uv__cvdr_rt__eof_vpwr_7     : 1;  /* bit[7-7]  : source: SCALER_2_2(UV) [24 over 63] NC */
        unsigned int  scaler_1_1_y__cvdr_rt__eof_vpwr_8      : 1;  /* bit[8-8]  : source: SCALER_1_1(Y) [23 over 63] NC */
        unsigned int  scaler_1_1_uv__cvdr_rt__eof_vpwr_9     : 1;  /* bit[9-9]  : source: SCALER_1_1(UV) [22 over 63] NC */
        unsigned int  scaler_1_2_y__cvdr_rt__eof_vpwr_10     : 1;  /* bit[10-10]: source: SCALER_1_2(Y) [21 over 63] NC */
        unsigned int  scaler_1_2_uv__cvdr_rt__eof_vpwr_11    : 1;  /* bit[11-11]: source: SCALER_1_2(UV) [20 over 63] NC */
        unsigned int  otap_2_1__cvdr_rt__eof_vpwr_14         : 1;  /* bit[12-12]: source: OTAP_2_1 [19 over 63] NC */
        unsigned int  otap_2_2__cvdr_rt__eof_vpwr_15         : 1;  /* bit[13-13]: source: OTAP_2_2 [18 over 63] NC */
        unsigned int  isp_fe_1__cvdr_rt__eof_vpwr_16         : 1;  /* bit[14-14]: source: ISP_FE_1 [17 over 63] NC */
        unsigned int  stream_router_1__cvdr_rt__eof_vpwr_18b : 1;  /* bit[15-15]: source: STREAM_ROUTER(1) [16 over 63] NC */
        unsigned int  isp_fe_2__cvdr_rt__eof_vpwr_17         : 1;  /* bit[16-16]: source: ISP_FE_2 [15 over 63] NC */
        unsigned int  stream_router_2__cvdr_rt__eof_vpwr_19b : 1;  /* bit[17-17]: source: STREAM_ROUTER(2) [14 over 63] NC */
        unsigned int  stat3a_1__cvdr_rt__eof_vpwr_20         : 1;  /* bit[18-18]: source: STAT3A_1 [13 over 63] NC */
        unsigned int  stat3a_2__cvdr_rt__eof_vpwr_21         : 1;  /* bit[19-19]: source: STAT3A_2 [12 over 63] NC */
        unsigned int  stream_router_3__cvdr_rt__eof_vpwr_22  : 1;  /* bit[20-20]: source: STREAM_ROUTER(3) [11 over 63] NC */
        unsigned int  stream_router_4__cvdr_rt__eof_vpwr_23  : 1;  /* bit[21-21]: source: STREAM_ROUTER(4) [10 over 63] NC */
        unsigned int  stream_router_5__cvdr_rt__eof_vpwr_24  : 1;  /* bit[22-22]: source: STREAM_ROUTER(5) [9 over 63] NC */
        unsigned int  jpgenc__cvdr_rt__eof_vpwr_25           : 1;  /* bit[23-23]: source: JPGENC [8 over 63] NC */
        unsigned int  isp_fe_1__fcm__sw_wr_ack_0             : 1;  /* bit[24-24]: source: ISP_FE_1 [7 over 63] NC */
        unsigned int  isp_fe_1__fcm__sw_rd_ack_0             : 1;  /* bit[25-25]: source: ISP_FE_1 [6 over 63] NC */
        unsigned int  isp_fe_2__fcm__sw_wr_ack_1             : 1;  /* bit[26-26]: source: ISP_FE_2 [5 over 63] NC */
        unsigned int  isp_fe_2__fcm__sw_rd_ack_1             : 1;  /* bit[27-27]: source: ISP_FE_2 [4 over 63] NC */
        unsigned int  scaler_1_1_y__fcm__sw_wr_ack_2         : 1;  /* bit[28-28]: source: SCALER_1_1(Y) [3 over 63] NC */
        unsigned int  scaler_1_1_y__fcm__sw_rd_ack_2         : 1;  /* bit[29-29]: source: SCALER_1_1(Y) [2 over 63] NC */
        unsigned int  scaler_1_1_uv__fcm__sw_wr_ack_3        : 1;  /* bit[30-30]: source: SCALER_1_1(UV) [1 over 63] NC */
        unsigned int  scaler_1_1_uv__fcm__sw_rd_ack_3        : 1;  /* bit[31-31]: source: SCALER_1_1(UV) [0 over 63] NC */
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_otap_1_1__cvdr_rt__eof_vpwr_0_START           (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_otap_1_1__cvdr_rt__eof_vpwr_0_END             (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_otap_1_2__cvdr_rt__eof_vpwr_1_START           (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_otap_1_2__cvdr_rt__eof_vpwr_1_END             (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_scaler_3_y__cvdr_rt__eof_vpwr_2_START         (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_scaler_3_y__cvdr_rt__eof_vpwr_2_END           (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_scaler_3_uv__cvdr_rt__eof_vpwr_3_START        (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_scaler_3_uv__cvdr_rt__eof_vpwr_3_END          (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_scaler_2_1_y__cvdr_rt__eof_vpwr_4_START       (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_scaler_2_1_y__cvdr_rt__eof_vpwr_4_END         (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_scaler_2_1_uv__cvdr_rt__eof_vpwr_5_START      (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_scaler_2_1_uv__cvdr_rt__eof_vpwr_5_END        (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_scaler_2_2_y__cvdr_rt__eof_vpwr_6_START       (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_scaler_2_2_y__cvdr_rt__eof_vpwr_6_END         (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_scaler_2_2_uv__cvdr_rt__eof_vpwr_7_START      (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_scaler_2_2_uv__cvdr_rt__eof_vpwr_7_END        (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_scaler_1_1_y__cvdr_rt__eof_vpwr_8_START       (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_scaler_1_1_y__cvdr_rt__eof_vpwr_8_END         (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_scaler_1_1_uv__cvdr_rt__eof_vpwr_9_START      (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_scaler_1_1_uv__cvdr_rt__eof_vpwr_9_END        (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_scaler_1_2_y__cvdr_rt__eof_vpwr_10_START      (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_scaler_1_2_y__cvdr_rt__eof_vpwr_10_END        (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_scaler_1_2_uv__cvdr_rt__eof_vpwr_11_START     (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_scaler_1_2_uv__cvdr_rt__eof_vpwr_11_END       (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_otap_2_1__cvdr_rt__eof_vpwr_14_START          (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_otap_2_1__cvdr_rt__eof_vpwr_14_END            (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_otap_2_2__cvdr_rt__eof_vpwr_15_START          (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_otap_2_2__cvdr_rt__eof_vpwr_15_END            (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_isp_fe_1__cvdr_rt__eof_vpwr_16_START          (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_isp_fe_1__cvdr_rt__eof_vpwr_16_END            (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_stream_router_1__cvdr_rt__eof_vpwr_18b_START  (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_stream_router_1__cvdr_rt__eof_vpwr_18b_END    (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_isp_fe_2__cvdr_rt__eof_vpwr_17_START          (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_isp_fe_2__cvdr_rt__eof_vpwr_17_END            (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_stream_router_2__cvdr_rt__eof_vpwr_19b_START  (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_stream_router_2__cvdr_rt__eof_vpwr_19b_END    (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_stat3a_1__cvdr_rt__eof_vpwr_20_START          (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_stat3a_1__cvdr_rt__eof_vpwr_20_END            (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_stat3a_2__cvdr_rt__eof_vpwr_21_START          (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_stat3a_2__cvdr_rt__eof_vpwr_21_END            (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_stream_router_3__cvdr_rt__eof_vpwr_22_START   (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_stream_router_3__cvdr_rt__eof_vpwr_22_END     (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_stream_router_4__cvdr_rt__eof_vpwr_23_START   (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_stream_router_4__cvdr_rt__eof_vpwr_23_END     (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_stream_router_5__cvdr_rt__eof_vpwr_24_START   (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_stream_router_5__cvdr_rt__eof_vpwr_24_END     (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_jpgenc__cvdr_rt__eof_vpwr_25_START            (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_jpgenc__cvdr_rt__eof_vpwr_25_END              (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_isp_fe_1__fcm__sw_wr_ack_0_START              (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_isp_fe_1__fcm__sw_wr_ack_0_END                (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_isp_fe_1__fcm__sw_rd_ack_0_START              (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_isp_fe_1__fcm__sw_rd_ack_0_END                (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_isp_fe_2__fcm__sw_wr_ack_1_START              (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_isp_fe_2__fcm__sw_wr_ack_1_END                (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_isp_fe_2__fcm__sw_rd_ack_1_START              (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_isp_fe_2__fcm__sw_rd_ack_1_END                (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_scaler_1_1_y__fcm__sw_wr_ack_2_START          (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_scaler_1_1_y__fcm__sw_wr_ack_2_END            (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_scaler_1_1_y__fcm__sw_rd_ack_2_START          (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_scaler_1_1_y__fcm__sw_rd_ack_2_END            (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_scaler_1_1_uv__fcm__sw_wr_ack_3_START         (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_scaler_1_1_uv__fcm__sw_wr_ack_3_END           (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_scaler_1_1_uv__fcm__sw_rd_ack_3_START         (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_0_scaler_1_1_uv__fcm__sw_rd_ack_3_END           (31)


/*****************************************************************************
 结构名    : SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_UNION
 结构说明  : IRQ_MERGER_MIS_FRPROC_0 寄存器结构定义。地址偏移量:0xC8，初值:0x00000000，宽度:32
 寄存器说明: [Masked Interrupt Status Register] FRPROC register (bloc 0 over 1).
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  otap_1_1__cvdr_rt__eof_vpwr_0          : 1;  /* bit[0-0]  : source: OTAP_1_1 [31 over 63] NC */
        unsigned int  otap_1_2__cvdr_rt__eof_vpwr_1          : 1;  /* bit[1-1]  : source: OTAP_1_2 [30 over 63] NC */
        unsigned int  scaler_3_y__cvdr_rt__eof_vpwr_2        : 1;  /* bit[2-2]  : source: SCALER_3(Y) [29 over 63] NC */
        unsigned int  scaler_3_uv__cvdr_rt__eof_vpwr_3       : 1;  /* bit[3-3]  : source: SCALER_3(UV) [28 over 63] NC */
        unsigned int  scaler_2_1_y__cvdr_rt__eof_vpwr_4      : 1;  /* bit[4-4]  : source: SCALER_2_1(Y) [27 over 63] NC */
        unsigned int  scaler_2_1_uv__cvdr_rt__eof_vpwr_5     : 1;  /* bit[5-5]  : source: SCALER_2_1(UV) [26 over 63] NC */
        unsigned int  scaler_2_2_y__cvdr_rt__eof_vpwr_6      : 1;  /* bit[6-6]  : source: SCALER_2_2(Y) [25 over 63] NC */
        unsigned int  scaler_2_2_uv__cvdr_rt__eof_vpwr_7     : 1;  /* bit[7-7]  : source: SCALER_2_2(UV) [24 over 63] NC */
        unsigned int  scaler_1_1_y__cvdr_rt__eof_vpwr_8      : 1;  /* bit[8-8]  : source: SCALER_1_1(Y) [23 over 63] NC */
        unsigned int  scaler_1_1_uv__cvdr_rt__eof_vpwr_9     : 1;  /* bit[9-9]  : source: SCALER_1_1(UV) [22 over 63] NC */
        unsigned int  scaler_1_2_y__cvdr_rt__eof_vpwr_10     : 1;  /* bit[10-10]: source: SCALER_1_2(Y) [21 over 63] NC */
        unsigned int  scaler_1_2_uv__cvdr_rt__eof_vpwr_11    : 1;  /* bit[11-11]: source: SCALER_1_2(UV) [20 over 63] NC */
        unsigned int  otap_2_1__cvdr_rt__eof_vpwr_14         : 1;  /* bit[12-12]: source: OTAP_2_1 [19 over 63] NC */
        unsigned int  otap_2_2__cvdr_rt__eof_vpwr_15         : 1;  /* bit[13-13]: source: OTAP_2_2 [18 over 63] NC */
        unsigned int  isp_fe_1__cvdr_rt__eof_vpwr_16         : 1;  /* bit[14-14]: source: ISP_FE_1 [17 over 63] NC */
        unsigned int  stream_router_1__cvdr_rt__eof_vpwr_18b : 1;  /* bit[15-15]: source: STREAM_ROUTER(1) [16 over 63] NC */
        unsigned int  isp_fe_2__cvdr_rt__eof_vpwr_17         : 1;  /* bit[16-16]: source: ISP_FE_2 [15 over 63] NC */
        unsigned int  stream_router_2__cvdr_rt__eof_vpwr_19b : 1;  /* bit[17-17]: source: STREAM_ROUTER(2) [14 over 63] NC */
        unsigned int  stat3a_1__cvdr_rt__eof_vpwr_20         : 1;  /* bit[18-18]: source: STAT3A_1 [13 over 63] NC */
        unsigned int  stat3a_2__cvdr_rt__eof_vpwr_21         : 1;  /* bit[19-19]: source: STAT3A_2 [12 over 63] NC */
        unsigned int  stream_router_3__cvdr_rt__eof_vpwr_22  : 1;  /* bit[20-20]: source: STREAM_ROUTER(3) [11 over 63] NC */
        unsigned int  stream_router_4__cvdr_rt__eof_vpwr_23  : 1;  /* bit[21-21]: source: STREAM_ROUTER(4) [10 over 63] NC */
        unsigned int  stream_router_5__cvdr_rt__eof_vpwr_24  : 1;  /* bit[22-22]: source: STREAM_ROUTER(5) [9 over 63] NC */
        unsigned int  jpgenc__cvdr_rt__eof_vpwr_25           : 1;  /* bit[23-23]: source: JPGENC [8 over 63] NC */
        unsigned int  isp_fe_1__fcm__sw_wr_ack_0             : 1;  /* bit[24-24]: source: ISP_FE_1 [7 over 63] NC */
        unsigned int  isp_fe_1__fcm__sw_rd_ack_0             : 1;  /* bit[25-25]: source: ISP_FE_1 [6 over 63] NC */
        unsigned int  isp_fe_2__fcm__sw_wr_ack_1             : 1;  /* bit[26-26]: source: ISP_FE_2 [5 over 63] NC */
        unsigned int  isp_fe_2__fcm__sw_rd_ack_1             : 1;  /* bit[27-27]: source: ISP_FE_2 [4 over 63] NC */
        unsigned int  scaler_1_1_y__fcm__sw_wr_ack_2         : 1;  /* bit[28-28]: source: SCALER_1_1(Y) [3 over 63] NC */
        unsigned int  scaler_1_1_y__fcm__sw_rd_ack_2         : 1;  /* bit[29-29]: source: SCALER_1_1(Y) [2 over 63] NC */
        unsigned int  scaler_1_1_uv__fcm__sw_wr_ack_3        : 1;  /* bit[30-30]: source: SCALER_1_1(UV) [1 over 63] NC */
        unsigned int  scaler_1_1_uv__fcm__sw_rd_ack_3        : 1;  /* bit[31-31]: source: SCALER_1_1(UV) [0 over 63] NC */
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_otap_1_1__cvdr_rt__eof_vpwr_0_START           (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_otap_1_1__cvdr_rt__eof_vpwr_0_END             (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_otap_1_2__cvdr_rt__eof_vpwr_1_START           (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_otap_1_2__cvdr_rt__eof_vpwr_1_END             (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_scaler_3_y__cvdr_rt__eof_vpwr_2_START         (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_scaler_3_y__cvdr_rt__eof_vpwr_2_END           (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_scaler_3_uv__cvdr_rt__eof_vpwr_3_START        (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_scaler_3_uv__cvdr_rt__eof_vpwr_3_END          (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_scaler_2_1_y__cvdr_rt__eof_vpwr_4_START       (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_scaler_2_1_y__cvdr_rt__eof_vpwr_4_END         (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_scaler_2_1_uv__cvdr_rt__eof_vpwr_5_START      (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_scaler_2_1_uv__cvdr_rt__eof_vpwr_5_END        (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_scaler_2_2_y__cvdr_rt__eof_vpwr_6_START       (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_scaler_2_2_y__cvdr_rt__eof_vpwr_6_END         (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_scaler_2_2_uv__cvdr_rt__eof_vpwr_7_START      (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_scaler_2_2_uv__cvdr_rt__eof_vpwr_7_END        (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_scaler_1_1_y__cvdr_rt__eof_vpwr_8_START       (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_scaler_1_1_y__cvdr_rt__eof_vpwr_8_END         (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_scaler_1_1_uv__cvdr_rt__eof_vpwr_9_START      (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_scaler_1_1_uv__cvdr_rt__eof_vpwr_9_END        (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_scaler_1_2_y__cvdr_rt__eof_vpwr_10_START      (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_scaler_1_2_y__cvdr_rt__eof_vpwr_10_END        (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_scaler_1_2_uv__cvdr_rt__eof_vpwr_11_START     (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_scaler_1_2_uv__cvdr_rt__eof_vpwr_11_END       (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_otap_2_1__cvdr_rt__eof_vpwr_14_START          (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_otap_2_1__cvdr_rt__eof_vpwr_14_END            (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_otap_2_2__cvdr_rt__eof_vpwr_15_START          (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_otap_2_2__cvdr_rt__eof_vpwr_15_END            (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_isp_fe_1__cvdr_rt__eof_vpwr_16_START          (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_isp_fe_1__cvdr_rt__eof_vpwr_16_END            (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_stream_router_1__cvdr_rt__eof_vpwr_18b_START  (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_stream_router_1__cvdr_rt__eof_vpwr_18b_END    (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_isp_fe_2__cvdr_rt__eof_vpwr_17_START          (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_isp_fe_2__cvdr_rt__eof_vpwr_17_END            (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_stream_router_2__cvdr_rt__eof_vpwr_19b_START  (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_stream_router_2__cvdr_rt__eof_vpwr_19b_END    (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_stat3a_1__cvdr_rt__eof_vpwr_20_START          (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_stat3a_1__cvdr_rt__eof_vpwr_20_END            (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_stat3a_2__cvdr_rt__eof_vpwr_21_START          (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_stat3a_2__cvdr_rt__eof_vpwr_21_END            (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_stream_router_3__cvdr_rt__eof_vpwr_22_START   (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_stream_router_3__cvdr_rt__eof_vpwr_22_END     (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_stream_router_4__cvdr_rt__eof_vpwr_23_START   (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_stream_router_4__cvdr_rt__eof_vpwr_23_END     (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_stream_router_5__cvdr_rt__eof_vpwr_24_START   (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_stream_router_5__cvdr_rt__eof_vpwr_24_END     (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_jpgenc__cvdr_rt__eof_vpwr_25_START            (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_jpgenc__cvdr_rt__eof_vpwr_25_END              (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_isp_fe_1__fcm__sw_wr_ack_0_START              (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_isp_fe_1__fcm__sw_wr_ack_0_END                (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_isp_fe_1__fcm__sw_rd_ack_0_START              (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_isp_fe_1__fcm__sw_rd_ack_0_END                (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_isp_fe_2__fcm__sw_wr_ack_1_START              (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_isp_fe_2__fcm__sw_wr_ack_1_END                (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_isp_fe_2__fcm__sw_rd_ack_1_START              (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_isp_fe_2__fcm__sw_rd_ack_1_END                (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_scaler_1_1_y__fcm__sw_wr_ack_2_START          (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_scaler_1_1_y__fcm__sw_wr_ack_2_END            (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_scaler_1_1_y__fcm__sw_rd_ack_2_START          (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_scaler_1_1_y__fcm__sw_rd_ack_2_END            (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_scaler_1_1_uv__fcm__sw_wr_ack_3_START         (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_scaler_1_1_uv__fcm__sw_wr_ack_3_END           (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_scaler_1_1_uv__fcm__sw_rd_ack_3_START         (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_0_scaler_1_1_uv__fcm__sw_rd_ack_3_END           (31)


/*****************************************************************************
 结构名    : SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_UNION
 结构说明  : IRQ_MERGER_ICR_FRPROC_0 寄存器结构定义。地址偏移量:0xCC，初值:0x00000000，宽度:32
 寄存器说明: [Interrupt Clear Register] FRPROC register (bloc 0 over 1).
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  otap_1_1__cvdr_rt__eof_vpwr_0          : 1;  /* bit[0-0]  : source: OTAP_1_1 [31 over 63] NC */
        unsigned int  otap_1_2__cvdr_rt__eof_vpwr_1          : 1;  /* bit[1-1]  : source: OTAP_1_2 [30 over 63] NC */
        unsigned int  scaler_3_y__cvdr_rt__eof_vpwr_2        : 1;  /* bit[2-2]  : source: SCALER_3(Y) [29 over 63] NC */
        unsigned int  scaler_3_uv__cvdr_rt__eof_vpwr_3       : 1;  /* bit[3-3]  : source: SCALER_3(UV) [28 over 63] NC */
        unsigned int  scaler_2_1_y__cvdr_rt__eof_vpwr_4      : 1;  /* bit[4-4]  : source: SCALER_2_1(Y) [27 over 63] NC */
        unsigned int  scaler_2_1_uv__cvdr_rt__eof_vpwr_5     : 1;  /* bit[5-5]  : source: SCALER_2_1(UV) [26 over 63] NC */
        unsigned int  scaler_2_2_y__cvdr_rt__eof_vpwr_6      : 1;  /* bit[6-6]  : source: SCALER_2_2(Y) [25 over 63] NC */
        unsigned int  scaler_2_2_uv__cvdr_rt__eof_vpwr_7     : 1;  /* bit[7-7]  : source: SCALER_2_2(UV) [24 over 63] NC */
        unsigned int  scaler_1_1_y__cvdr_rt__eof_vpwr_8      : 1;  /* bit[8-8]  : source: SCALER_1_1(Y) [23 over 63] NC */
        unsigned int  scaler_1_1_uv__cvdr_rt__eof_vpwr_9     : 1;  /* bit[9-9]  : source: SCALER_1_1(UV) [22 over 63] NC */
        unsigned int  scaler_1_2_y__cvdr_rt__eof_vpwr_10     : 1;  /* bit[10-10]: source: SCALER_1_2(Y) [21 over 63] NC */
        unsigned int  scaler_1_2_uv__cvdr_rt__eof_vpwr_11    : 1;  /* bit[11-11]: source: SCALER_1_2(UV) [20 over 63] NC */
        unsigned int  otap_2_1__cvdr_rt__eof_vpwr_14         : 1;  /* bit[12-12]: source: OTAP_2_1 [19 over 63] NC */
        unsigned int  otap_2_2__cvdr_rt__eof_vpwr_15         : 1;  /* bit[13-13]: source: OTAP_2_2 [18 over 63] NC */
        unsigned int  isp_fe_1__cvdr_rt__eof_vpwr_16         : 1;  /* bit[14-14]: source: ISP_FE_1 [17 over 63] NC */
        unsigned int  stream_router_1__cvdr_rt__eof_vpwr_18b : 1;  /* bit[15-15]: source: STREAM_ROUTER(1) [16 over 63] NC */
        unsigned int  isp_fe_2__cvdr_rt__eof_vpwr_17         : 1;  /* bit[16-16]: source: ISP_FE_2 [15 over 63] NC */
        unsigned int  stream_router_2__cvdr_rt__eof_vpwr_19b : 1;  /* bit[17-17]: source: STREAM_ROUTER(2) [14 over 63] NC */
        unsigned int  stat3a_1__cvdr_rt__eof_vpwr_20         : 1;  /* bit[18-18]: source: STAT3A_1 [13 over 63] NC */
        unsigned int  stat3a_2__cvdr_rt__eof_vpwr_21         : 1;  /* bit[19-19]: source: STAT3A_2 [12 over 63] NC */
        unsigned int  stream_router_3__cvdr_rt__eof_vpwr_22  : 1;  /* bit[20-20]: source: STREAM_ROUTER(3) [11 over 63] NC */
        unsigned int  stream_router_4__cvdr_rt__eof_vpwr_23  : 1;  /* bit[21-21]: source: STREAM_ROUTER(4) [10 over 63] NC */
        unsigned int  stream_router_5__cvdr_rt__eof_vpwr_24  : 1;  /* bit[22-22]: source: STREAM_ROUTER(5) [9 over 63] NC */
        unsigned int  jpgenc__cvdr_rt__eof_vpwr_25           : 1;  /* bit[23-23]: source: JPGENC [8 over 63] NC */
        unsigned int  isp_fe_1__fcm__sw_wr_ack_0             : 1;  /* bit[24-24]: source: ISP_FE_1 [7 over 63] NC */
        unsigned int  isp_fe_1__fcm__sw_rd_ack_0             : 1;  /* bit[25-25]: source: ISP_FE_1 [6 over 63] NC */
        unsigned int  isp_fe_2__fcm__sw_wr_ack_1             : 1;  /* bit[26-26]: source: ISP_FE_2 [5 over 63] NC */
        unsigned int  isp_fe_2__fcm__sw_rd_ack_1             : 1;  /* bit[27-27]: source: ISP_FE_2 [4 over 63] NC */
        unsigned int  scaler_1_1_y__fcm__sw_wr_ack_2         : 1;  /* bit[28-28]: source: SCALER_1_1(Y) [3 over 63] NC */
        unsigned int  scaler_1_1_y__fcm__sw_rd_ack_2         : 1;  /* bit[29-29]: source: SCALER_1_1(Y) [2 over 63] NC */
        unsigned int  scaler_1_1_uv__fcm__sw_wr_ack_3        : 1;  /* bit[30-30]: source: SCALER_1_1(UV) [1 over 63] NC */
        unsigned int  scaler_1_1_uv__fcm__sw_rd_ack_3        : 1;  /* bit[31-31]: source: SCALER_1_1(UV) [0 over 63] NC */
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_otap_1_1__cvdr_rt__eof_vpwr_0_START           (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_otap_1_1__cvdr_rt__eof_vpwr_0_END             (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_otap_1_2__cvdr_rt__eof_vpwr_1_START           (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_otap_1_2__cvdr_rt__eof_vpwr_1_END             (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_scaler_3_y__cvdr_rt__eof_vpwr_2_START         (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_scaler_3_y__cvdr_rt__eof_vpwr_2_END           (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_scaler_3_uv__cvdr_rt__eof_vpwr_3_START        (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_scaler_3_uv__cvdr_rt__eof_vpwr_3_END          (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_scaler_2_1_y__cvdr_rt__eof_vpwr_4_START       (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_scaler_2_1_y__cvdr_rt__eof_vpwr_4_END         (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_scaler_2_1_uv__cvdr_rt__eof_vpwr_5_START      (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_scaler_2_1_uv__cvdr_rt__eof_vpwr_5_END        (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_scaler_2_2_y__cvdr_rt__eof_vpwr_6_START       (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_scaler_2_2_y__cvdr_rt__eof_vpwr_6_END         (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_scaler_2_2_uv__cvdr_rt__eof_vpwr_7_START      (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_scaler_2_2_uv__cvdr_rt__eof_vpwr_7_END        (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_scaler_1_1_y__cvdr_rt__eof_vpwr_8_START       (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_scaler_1_1_y__cvdr_rt__eof_vpwr_8_END         (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_scaler_1_1_uv__cvdr_rt__eof_vpwr_9_START      (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_scaler_1_1_uv__cvdr_rt__eof_vpwr_9_END        (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_scaler_1_2_y__cvdr_rt__eof_vpwr_10_START      (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_scaler_1_2_y__cvdr_rt__eof_vpwr_10_END        (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_scaler_1_2_uv__cvdr_rt__eof_vpwr_11_START     (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_scaler_1_2_uv__cvdr_rt__eof_vpwr_11_END       (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_otap_2_1__cvdr_rt__eof_vpwr_14_START          (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_otap_2_1__cvdr_rt__eof_vpwr_14_END            (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_otap_2_2__cvdr_rt__eof_vpwr_15_START          (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_otap_2_2__cvdr_rt__eof_vpwr_15_END            (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_isp_fe_1__cvdr_rt__eof_vpwr_16_START          (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_isp_fe_1__cvdr_rt__eof_vpwr_16_END            (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_stream_router_1__cvdr_rt__eof_vpwr_18b_START  (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_stream_router_1__cvdr_rt__eof_vpwr_18b_END    (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_isp_fe_2__cvdr_rt__eof_vpwr_17_START          (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_isp_fe_2__cvdr_rt__eof_vpwr_17_END            (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_stream_router_2__cvdr_rt__eof_vpwr_19b_START  (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_stream_router_2__cvdr_rt__eof_vpwr_19b_END    (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_stat3a_1__cvdr_rt__eof_vpwr_20_START          (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_stat3a_1__cvdr_rt__eof_vpwr_20_END            (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_stat3a_2__cvdr_rt__eof_vpwr_21_START          (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_stat3a_2__cvdr_rt__eof_vpwr_21_END            (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_stream_router_3__cvdr_rt__eof_vpwr_22_START   (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_stream_router_3__cvdr_rt__eof_vpwr_22_END     (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_stream_router_4__cvdr_rt__eof_vpwr_23_START   (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_stream_router_4__cvdr_rt__eof_vpwr_23_END     (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_stream_router_5__cvdr_rt__eof_vpwr_24_START   (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_stream_router_5__cvdr_rt__eof_vpwr_24_END     (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_jpgenc__cvdr_rt__eof_vpwr_25_START            (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_jpgenc__cvdr_rt__eof_vpwr_25_END              (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_isp_fe_1__fcm__sw_wr_ack_0_START              (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_isp_fe_1__fcm__sw_wr_ack_0_END                (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_isp_fe_1__fcm__sw_rd_ack_0_START              (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_isp_fe_1__fcm__sw_rd_ack_0_END                (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_isp_fe_2__fcm__sw_wr_ack_1_START              (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_isp_fe_2__fcm__sw_wr_ack_1_END                (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_isp_fe_2__fcm__sw_rd_ack_1_START              (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_isp_fe_2__fcm__sw_rd_ack_1_END                (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_scaler_1_1_y__fcm__sw_wr_ack_2_START          (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_scaler_1_1_y__fcm__sw_wr_ack_2_END            (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_scaler_1_1_y__fcm__sw_rd_ack_2_START          (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_scaler_1_1_y__fcm__sw_rd_ack_2_END            (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_scaler_1_1_uv__fcm__sw_wr_ack_3_START         (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_scaler_1_1_uv__fcm__sw_wr_ack_3_END           (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_scaler_1_1_uv__fcm__sw_rd_ack_3_START         (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_0_scaler_1_1_uv__fcm__sw_rd_ack_3_END           (31)


/*****************************************************************************
 结构名    : SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_UNION
 结构说明  : IRQ_MERGER_ISR_FRPROC_0 寄存器结构定义。地址偏移量:0xD0，初值:0x00000000，宽度:32
 寄存器说明: [Interrupt Set Register] FRPROC register (bloc 0 over 1).
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  otap_1_1__cvdr_rt__eof_vpwr_0          : 1;  /* bit[0-0]  : source: OTAP_1_1 [31 over 63] NC */
        unsigned int  otap_1_2__cvdr_rt__eof_vpwr_1          : 1;  /* bit[1-1]  : source: OTAP_1_2 [30 over 63] NC */
        unsigned int  scaler_3_y__cvdr_rt__eof_vpwr_2        : 1;  /* bit[2-2]  : source: SCALER_3(Y) [29 over 63] NC */
        unsigned int  scaler_3_uv__cvdr_rt__eof_vpwr_3       : 1;  /* bit[3-3]  : source: SCALER_3(UV) [28 over 63] NC */
        unsigned int  scaler_2_1_y__cvdr_rt__eof_vpwr_4      : 1;  /* bit[4-4]  : source: SCALER_2_1(Y) [27 over 63] NC */
        unsigned int  scaler_2_1_uv__cvdr_rt__eof_vpwr_5     : 1;  /* bit[5-5]  : source: SCALER_2_1(UV) [26 over 63] NC */
        unsigned int  scaler_2_2_y__cvdr_rt__eof_vpwr_6      : 1;  /* bit[6-6]  : source: SCALER_2_2(Y) [25 over 63] NC */
        unsigned int  scaler_2_2_uv__cvdr_rt__eof_vpwr_7     : 1;  /* bit[7-7]  : source: SCALER_2_2(UV) [24 over 63] NC */
        unsigned int  scaler_1_1_y__cvdr_rt__eof_vpwr_8      : 1;  /* bit[8-8]  : source: SCALER_1_1(Y) [23 over 63] NC */
        unsigned int  scaler_1_1_uv__cvdr_rt__eof_vpwr_9     : 1;  /* bit[9-9]  : source: SCALER_1_1(UV) [22 over 63] NC */
        unsigned int  scaler_1_2_y__cvdr_rt__eof_vpwr_10     : 1;  /* bit[10-10]: source: SCALER_1_2(Y) [21 over 63] NC */
        unsigned int  scaler_1_2_uv__cvdr_rt__eof_vpwr_11    : 1;  /* bit[11-11]: source: SCALER_1_2(UV) [20 over 63] NC */
        unsigned int  otap_2_1__cvdr_rt__eof_vpwr_14         : 1;  /* bit[12-12]: source: OTAP_2_1 [19 over 63] NC */
        unsigned int  otap_2_2__cvdr_rt__eof_vpwr_15         : 1;  /* bit[13-13]: source: OTAP_2_2 [18 over 63] NC */
        unsigned int  isp_fe_1__cvdr_rt__eof_vpwr_16         : 1;  /* bit[14-14]: source: ISP_FE_1 [17 over 63] NC */
        unsigned int  stream_router_1__cvdr_rt__eof_vpwr_18b : 1;  /* bit[15-15]: source: STREAM_ROUTER(1) [16 over 63] NC */
        unsigned int  isp_fe_2__cvdr_rt__eof_vpwr_17         : 1;  /* bit[16-16]: source: ISP_FE_2 [15 over 63] NC */
        unsigned int  stream_router_2__cvdr_rt__eof_vpwr_19b : 1;  /* bit[17-17]: source: STREAM_ROUTER(2) [14 over 63] NC */
        unsigned int  stat3a_1__cvdr_rt__eof_vpwr_20         : 1;  /* bit[18-18]: source: STAT3A_1 [13 over 63] NC */
        unsigned int  stat3a_2__cvdr_rt__eof_vpwr_21         : 1;  /* bit[19-19]: source: STAT3A_2 [12 over 63] NC */
        unsigned int  stream_router_3__cvdr_rt__eof_vpwr_22  : 1;  /* bit[20-20]: source: STREAM_ROUTER(3) [11 over 63] NC */
        unsigned int  stream_router_4__cvdr_rt__eof_vpwr_23  : 1;  /* bit[21-21]: source: STREAM_ROUTER(4) [10 over 63] NC */
        unsigned int  stream_router_5__cvdr_rt__eof_vpwr_24  : 1;  /* bit[22-22]: source: STREAM_ROUTER(5) [9 over 63] NC */
        unsigned int  jpgenc__cvdr_rt__eof_vpwr_25           : 1;  /* bit[23-23]: source: JPGENC [8 over 63] NC */
        unsigned int  isp_fe_1__fcm__sw_wr_ack_0             : 1;  /* bit[24-24]: source: ISP_FE_1 [7 over 63] NC */
        unsigned int  isp_fe_1__fcm__sw_rd_ack_0             : 1;  /* bit[25-25]: source: ISP_FE_1 [6 over 63] NC */
        unsigned int  isp_fe_2__fcm__sw_wr_ack_1             : 1;  /* bit[26-26]: source: ISP_FE_2 [5 over 63] NC */
        unsigned int  isp_fe_2__fcm__sw_rd_ack_1             : 1;  /* bit[27-27]: source: ISP_FE_2 [4 over 63] NC */
        unsigned int  scaler_1_1_y__fcm__sw_wr_ack_2         : 1;  /* bit[28-28]: source: SCALER_1_1(Y) [3 over 63] NC */
        unsigned int  scaler_1_1_y__fcm__sw_rd_ack_2         : 1;  /* bit[29-29]: source: SCALER_1_1(Y) [2 over 63] NC */
        unsigned int  scaler_1_1_uv__fcm__sw_wr_ack_3        : 1;  /* bit[30-30]: source: SCALER_1_1(UV) [1 over 63] NC */
        unsigned int  scaler_1_1_uv__fcm__sw_rd_ack_3        : 1;  /* bit[31-31]: source: SCALER_1_1(UV) [0 over 63] NC */
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_otap_1_1__cvdr_rt__eof_vpwr_0_START           (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_otap_1_1__cvdr_rt__eof_vpwr_0_END             (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_otap_1_2__cvdr_rt__eof_vpwr_1_START           (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_otap_1_2__cvdr_rt__eof_vpwr_1_END             (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_scaler_3_y__cvdr_rt__eof_vpwr_2_START         (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_scaler_3_y__cvdr_rt__eof_vpwr_2_END           (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_scaler_3_uv__cvdr_rt__eof_vpwr_3_START        (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_scaler_3_uv__cvdr_rt__eof_vpwr_3_END          (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_scaler_2_1_y__cvdr_rt__eof_vpwr_4_START       (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_scaler_2_1_y__cvdr_rt__eof_vpwr_4_END         (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_scaler_2_1_uv__cvdr_rt__eof_vpwr_5_START      (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_scaler_2_1_uv__cvdr_rt__eof_vpwr_5_END        (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_scaler_2_2_y__cvdr_rt__eof_vpwr_6_START       (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_scaler_2_2_y__cvdr_rt__eof_vpwr_6_END         (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_scaler_2_2_uv__cvdr_rt__eof_vpwr_7_START      (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_scaler_2_2_uv__cvdr_rt__eof_vpwr_7_END        (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_scaler_1_1_y__cvdr_rt__eof_vpwr_8_START       (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_scaler_1_1_y__cvdr_rt__eof_vpwr_8_END         (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_scaler_1_1_uv__cvdr_rt__eof_vpwr_9_START      (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_scaler_1_1_uv__cvdr_rt__eof_vpwr_9_END        (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_scaler_1_2_y__cvdr_rt__eof_vpwr_10_START      (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_scaler_1_2_y__cvdr_rt__eof_vpwr_10_END        (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_scaler_1_2_uv__cvdr_rt__eof_vpwr_11_START     (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_scaler_1_2_uv__cvdr_rt__eof_vpwr_11_END       (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_otap_2_1__cvdr_rt__eof_vpwr_14_START          (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_otap_2_1__cvdr_rt__eof_vpwr_14_END            (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_otap_2_2__cvdr_rt__eof_vpwr_15_START          (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_otap_2_2__cvdr_rt__eof_vpwr_15_END            (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_isp_fe_1__cvdr_rt__eof_vpwr_16_START          (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_isp_fe_1__cvdr_rt__eof_vpwr_16_END            (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_stream_router_1__cvdr_rt__eof_vpwr_18b_START  (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_stream_router_1__cvdr_rt__eof_vpwr_18b_END    (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_isp_fe_2__cvdr_rt__eof_vpwr_17_START          (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_isp_fe_2__cvdr_rt__eof_vpwr_17_END            (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_stream_router_2__cvdr_rt__eof_vpwr_19b_START  (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_stream_router_2__cvdr_rt__eof_vpwr_19b_END    (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_stat3a_1__cvdr_rt__eof_vpwr_20_START          (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_stat3a_1__cvdr_rt__eof_vpwr_20_END            (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_stat3a_2__cvdr_rt__eof_vpwr_21_START          (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_stat3a_2__cvdr_rt__eof_vpwr_21_END            (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_stream_router_3__cvdr_rt__eof_vpwr_22_START   (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_stream_router_3__cvdr_rt__eof_vpwr_22_END     (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_stream_router_4__cvdr_rt__eof_vpwr_23_START   (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_stream_router_4__cvdr_rt__eof_vpwr_23_END     (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_stream_router_5__cvdr_rt__eof_vpwr_24_START   (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_stream_router_5__cvdr_rt__eof_vpwr_24_END     (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_jpgenc__cvdr_rt__eof_vpwr_25_START            (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_jpgenc__cvdr_rt__eof_vpwr_25_END              (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_isp_fe_1__fcm__sw_wr_ack_0_START              (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_isp_fe_1__fcm__sw_wr_ack_0_END                (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_isp_fe_1__fcm__sw_rd_ack_0_START              (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_isp_fe_1__fcm__sw_rd_ack_0_END                (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_isp_fe_2__fcm__sw_wr_ack_1_START              (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_isp_fe_2__fcm__sw_wr_ack_1_END                (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_isp_fe_2__fcm__sw_rd_ack_1_START              (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_isp_fe_2__fcm__sw_rd_ack_1_END                (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_scaler_1_1_y__fcm__sw_wr_ack_2_START          (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_scaler_1_1_y__fcm__sw_wr_ack_2_END            (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_scaler_1_1_y__fcm__sw_rd_ack_2_START          (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_scaler_1_1_y__fcm__sw_rd_ack_2_END            (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_scaler_1_1_uv__fcm__sw_wr_ack_3_START         (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_scaler_1_1_uv__fcm__sw_wr_ack_3_END           (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_scaler_1_1_uv__fcm__sw_rd_ack_3_START         (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_0_scaler_1_1_uv__fcm__sw_rd_ack_3_END           (31)


/*****************************************************************************
 结构名    : SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_UNION
 结构说明  : IRQ_MERGER_IMSC_FRPROC_1 寄存器结构定义。地址偏移量:0xE0，初值:0x00000000，宽度:32
 寄存器说明: [Interrupt Mask Register] FRPROC register (bloc 1 over 1).
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scaler_1_2_y__fcm__sw_wr_ack_4        : 1;  /* bit[0-0]  : source: SCALER_1_2(Y) [63 over 63] NC */
        unsigned int  scaler_1_2_y__fcm__sw_rd_ack_4        : 1;  /* bit[1-1]  : source: SCALER_1_2(Y) [62 over 63] NC */
        unsigned int  scaler_1_2_uv__fcm__sw_wr_ack_5       : 1;  /* bit[2-2]  : source: SCALER_1_2(UV) [61 over 63] NC */
        unsigned int  scaler_1_2_uv__fcm__sw_rd_ack_5       : 1;  /* bit[3-3]  : source: SCALER_1_2(UV) [60 over 63] NC */
        unsigned int  scaler_3__end_of_rescale              : 1;  /* bit[4-4]  : source: NA [59 over 63] NC */
        unsigned int  stream_router__reformater_sof_0       : 1;  /* bit[5-5]  : source: NA [58 over 63] NC */
        unsigned int  stream_router__reformater_sof_1       : 1;  /* bit[6-6]  : source: NA [57 over 63] NC */
        unsigned int  stream_router__reformater_sof_2       : 1;  /* bit[7-7]  : source: NA [56 over 63] NC */
        unsigned int  stream_router__reformater_sof_3       : 1;  /* bit[8-8]  : source: NA [55 over 63] NC */
        unsigned int  stream_router__reformater_sof_4       : 1;  /* bit[9-9]  : source: NA [54 over 63] NC */
        unsigned int  stream_router__reformater_sof_5       : 1;  /* bit[10-10]: source: NA [53 over 63] NC */
        unsigned int  stream_router__reformater_sof_6       : 1;  /* bit[11-11]: source: NA [52 over 63] NC */
        unsigned int  stream_router__reformater_sof_7       : 1;  /* bit[12-12]: source: NA [51 over 63] NC */
        unsigned int  fd__process_finish                    : 1;  /* bit[13-13]: source: NA [50 over 63] NC */
        unsigned int  stat3a_1__3astats_ready               : 1;  /* bit[14-14]: source: NA [49 over 63] NC */
        unsigned int  stat3a_2__3astats_ready               : 1;  /* bit[15-15]: source: NA [48 over 63] NC */
        unsigned int  bas_1__end_of_filtering               : 1;  /* bit[16-16]: source: NA [47 over 63] NC */
        unsigned int  bas_2__end_of_filtering               : 1;  /* bit[17-17]: source: NA [46 over 63] NC */
        unsigned int  statdis_1__dis_ready                  : 1;  /* bit[18-18]: source: NA [45 over 63] NC */
        unsigned int  statdis_2__dis_ready                  : 1;  /* bit[19-19]: source: NA [44 over 63] NC */
        unsigned int  flash__flash_on                       : 1;  /* bit[20-20]: source: NA [43 over 63] NC */
        unsigned int  flash__flash_off                      : 1;  /* bit[21-21]: source: NA [42 over 63] NC */
        unsigned int  stream_router_5__cvdr_rt__eol_vpwr_24 : 1;  /* bit[22-22]: source: STREAM_ROUTER(5) [41 over 63] NC */
        unsigned int  ispss_ctrl__pwm_channel_0             : 1;  /* bit[23-23]: source: NA [40 over 63] NC */
        unsigned int  ispss_ctrl__pwm_channel_1             : 1;  /* bit[24-24]: source: NA [39 over 63] NC */
        unsigned int  cc_1__endofhist                       : 1;  /* bit[25-25]: source: NA [38 over 63] NC */
        unsigned int  cc_2__endofhist                       : 1;  /* bit[26-26]: source: NA [37 over 63] NC */
        unsigned int  ispss_ctrl__pwm_channel_2             : 1;  /* bit[27-27]: source: NA [36 over 63] NC */
        unsigned int  ispss_ctrl__pwm_channel_3             : 1;  /* bit[28-28]: source: NA [35 over 63] NC */
        unsigned int  ispss_ctrl__pwm_channel_4             : 1;  /* bit[29-29]: source: NA [34 over 63] NC */
        unsigned int  ispss_ctrl__pwm_channel_5             : 1;  /* bit[30-30]: source: NA [33 over 63] NC */
        unsigned int  ispss_ctrl__pwm_channel_6             : 1;  /* bit[31-31]: source: NA [32 over 63] NC */
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_scaler_1_2_y__fcm__sw_wr_ack_4_START         (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_scaler_1_2_y__fcm__sw_wr_ack_4_END           (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_scaler_1_2_y__fcm__sw_rd_ack_4_START         (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_scaler_1_2_y__fcm__sw_rd_ack_4_END           (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_scaler_1_2_uv__fcm__sw_wr_ack_5_START        (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_scaler_1_2_uv__fcm__sw_wr_ack_5_END          (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_scaler_1_2_uv__fcm__sw_rd_ack_5_START        (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_scaler_1_2_uv__fcm__sw_rd_ack_5_END          (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_scaler_3__end_of_rescale_START               (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_scaler_3__end_of_rescale_END                 (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_stream_router__reformater_sof_0_START        (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_stream_router__reformater_sof_0_END          (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_stream_router__reformater_sof_1_START        (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_stream_router__reformater_sof_1_END          (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_stream_router__reformater_sof_2_START        (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_stream_router__reformater_sof_2_END          (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_stream_router__reformater_sof_3_START        (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_stream_router__reformater_sof_3_END          (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_stream_router__reformater_sof_4_START        (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_stream_router__reformater_sof_4_END          (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_stream_router__reformater_sof_5_START        (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_stream_router__reformater_sof_5_END          (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_stream_router__reformater_sof_6_START        (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_stream_router__reformater_sof_6_END          (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_stream_router__reformater_sof_7_START        (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_stream_router__reformater_sof_7_END          (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_fd__process_finish_START                     (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_fd__process_finish_END                       (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_stat3a_1__3astats_ready_START                (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_stat3a_1__3astats_ready_END                  (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_stat3a_2__3astats_ready_START                (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_stat3a_2__3astats_ready_END                  (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_bas_1__end_of_filtering_START                (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_bas_1__end_of_filtering_END                  (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_bas_2__end_of_filtering_START                (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_bas_2__end_of_filtering_END                  (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_statdis_1__dis_ready_START                   (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_statdis_1__dis_ready_END                     (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_statdis_2__dis_ready_START                   (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_statdis_2__dis_ready_END                     (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_flash__flash_on_START                        (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_flash__flash_on_END                          (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_flash__flash_off_START                       (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_flash__flash_off_END                         (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_stream_router_5__cvdr_rt__eol_vpwr_24_START  (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_stream_router_5__cvdr_rt__eol_vpwr_24_END    (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_ispss_ctrl__pwm_channel_0_START              (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_ispss_ctrl__pwm_channel_0_END                (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_ispss_ctrl__pwm_channel_1_START              (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_ispss_ctrl__pwm_channel_1_END                (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_cc_1__endofhist_START                        (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_cc_1__endofhist_END                          (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_cc_2__endofhist_START                        (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_cc_2__endofhist_END                          (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_ispss_ctrl__pwm_channel_2_START              (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_ispss_ctrl__pwm_channel_2_END                (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_ispss_ctrl__pwm_channel_3_START              (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_ispss_ctrl__pwm_channel_3_END                (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_ispss_ctrl__pwm_channel_4_START              (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_ispss_ctrl__pwm_channel_4_END                (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_ispss_ctrl__pwm_channel_5_START              (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_ispss_ctrl__pwm_channel_5_END                (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_ispss_ctrl__pwm_channel_6_START              (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_IMSC_FRPROC_1_ispss_ctrl__pwm_channel_6_END                (31)


/*****************************************************************************
 结构名    : SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_UNION
 结构说明  : IRQ_MERGER_RIS_FRPROC_1 寄存器结构定义。地址偏移量:0xE4，初值:0x00000000，宽度:32
 寄存器说明: [Raw Interrupt Status Register] FRPROC register (bloc 1 over 1).
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scaler_1_2_y__fcm__sw_wr_ack_4        : 1;  /* bit[0-0]  : source: SCALER_1_2(Y) [63 over 63] NC */
        unsigned int  scaler_1_2_y__fcm__sw_rd_ack_4        : 1;  /* bit[1-1]  : source: SCALER_1_2(Y) [62 over 63] NC */
        unsigned int  scaler_1_2_uv__fcm__sw_wr_ack_5       : 1;  /* bit[2-2]  : source: SCALER_1_2(UV) [61 over 63] NC */
        unsigned int  scaler_1_2_uv__fcm__sw_rd_ack_5       : 1;  /* bit[3-3]  : source: SCALER_1_2(UV) [60 over 63] NC */
        unsigned int  scaler_3__end_of_rescale              : 1;  /* bit[4-4]  : source: NA [59 over 63] NC */
        unsigned int  stream_router__reformater_sof_0       : 1;  /* bit[5-5]  : source: NA [58 over 63] NC */
        unsigned int  stream_router__reformater_sof_1       : 1;  /* bit[6-6]  : source: NA [57 over 63] NC */
        unsigned int  stream_router__reformater_sof_2       : 1;  /* bit[7-7]  : source: NA [56 over 63] NC */
        unsigned int  stream_router__reformater_sof_3       : 1;  /* bit[8-8]  : source: NA [55 over 63] NC */
        unsigned int  stream_router__reformater_sof_4       : 1;  /* bit[9-9]  : source: NA [54 over 63] NC */
        unsigned int  stream_router__reformater_sof_5       : 1;  /* bit[10-10]: source: NA [53 over 63] NC */
        unsigned int  stream_router__reformater_sof_6       : 1;  /* bit[11-11]: source: NA [52 over 63] NC */
        unsigned int  stream_router__reformater_sof_7       : 1;  /* bit[12-12]: source: NA [51 over 63] NC */
        unsigned int  fd__process_finish                    : 1;  /* bit[13-13]: source: NA [50 over 63] NC */
        unsigned int  stat3a_1__3astats_ready               : 1;  /* bit[14-14]: source: NA [49 over 63] NC */
        unsigned int  stat3a_2__3astats_ready               : 1;  /* bit[15-15]: source: NA [48 over 63] NC */
        unsigned int  bas_1__end_of_filtering               : 1;  /* bit[16-16]: source: NA [47 over 63] NC */
        unsigned int  bas_2__end_of_filtering               : 1;  /* bit[17-17]: source: NA [46 over 63] NC */
        unsigned int  statdis_1__dis_ready                  : 1;  /* bit[18-18]: source: NA [45 over 63] NC */
        unsigned int  statdis_2__dis_ready                  : 1;  /* bit[19-19]: source: NA [44 over 63] NC */
        unsigned int  flash__flash_on                       : 1;  /* bit[20-20]: source: NA [43 over 63] NC */
        unsigned int  flash__flash_off                      : 1;  /* bit[21-21]: source: NA [42 over 63] NC */
        unsigned int  stream_router_5__cvdr_rt__eol_vpwr_24 : 1;  /* bit[22-22]: source: STREAM_ROUTER(5) [41 over 63] NC */
        unsigned int  ispss_ctrl__pwm_channel_0             : 1;  /* bit[23-23]: source: NA [40 over 63] NC */
        unsigned int  ispss_ctrl__pwm_channel_1             : 1;  /* bit[24-24]: source: NA [39 over 63] NC */
        unsigned int  cc_1__endofhist                       : 1;  /* bit[25-25]: source: NA [38 over 63] NC */
        unsigned int  cc_2__endofhist                       : 1;  /* bit[26-26]: source: NA [37 over 63] NC */
        unsigned int  ispss_ctrl__pwm_channel_2             : 1;  /* bit[27-27]: source: NA [36 over 63] NC */
        unsigned int  ispss_ctrl__pwm_channel_3             : 1;  /* bit[28-28]: source: NA [35 over 63] NC */
        unsigned int  ispss_ctrl__pwm_channel_4             : 1;  /* bit[29-29]: source: NA [34 over 63] NC */
        unsigned int  ispss_ctrl__pwm_channel_5             : 1;  /* bit[30-30]: source: NA [33 over 63] NC */
        unsigned int  ispss_ctrl__pwm_channel_6             : 1;  /* bit[31-31]: source: NA [32 over 63] NC */
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_scaler_1_2_y__fcm__sw_wr_ack_4_START         (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_scaler_1_2_y__fcm__sw_wr_ack_4_END           (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_scaler_1_2_y__fcm__sw_rd_ack_4_START         (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_scaler_1_2_y__fcm__sw_rd_ack_4_END           (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_scaler_1_2_uv__fcm__sw_wr_ack_5_START        (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_scaler_1_2_uv__fcm__sw_wr_ack_5_END          (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_scaler_1_2_uv__fcm__sw_rd_ack_5_START        (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_scaler_1_2_uv__fcm__sw_rd_ack_5_END          (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_scaler_3__end_of_rescale_START               (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_scaler_3__end_of_rescale_END                 (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_stream_router__reformater_sof_0_START        (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_stream_router__reformater_sof_0_END          (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_stream_router__reformater_sof_1_START        (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_stream_router__reformater_sof_1_END          (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_stream_router__reformater_sof_2_START        (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_stream_router__reformater_sof_2_END          (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_stream_router__reformater_sof_3_START        (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_stream_router__reformater_sof_3_END          (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_stream_router__reformater_sof_4_START        (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_stream_router__reformater_sof_4_END          (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_stream_router__reformater_sof_5_START        (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_stream_router__reformater_sof_5_END          (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_stream_router__reformater_sof_6_START        (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_stream_router__reformater_sof_6_END          (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_stream_router__reformater_sof_7_START        (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_stream_router__reformater_sof_7_END          (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_fd__process_finish_START                     (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_fd__process_finish_END                       (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_stat3a_1__3astats_ready_START                (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_stat3a_1__3astats_ready_END                  (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_stat3a_2__3astats_ready_START                (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_stat3a_2__3astats_ready_END                  (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_bas_1__end_of_filtering_START                (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_bas_1__end_of_filtering_END                  (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_bas_2__end_of_filtering_START                (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_bas_2__end_of_filtering_END                  (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_statdis_1__dis_ready_START                   (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_statdis_1__dis_ready_END                     (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_statdis_2__dis_ready_START                   (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_statdis_2__dis_ready_END                     (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_flash__flash_on_START                        (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_flash__flash_on_END                          (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_flash__flash_off_START                       (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_flash__flash_off_END                         (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_stream_router_5__cvdr_rt__eol_vpwr_24_START  (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_stream_router_5__cvdr_rt__eol_vpwr_24_END    (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_ispss_ctrl__pwm_channel_0_START              (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_ispss_ctrl__pwm_channel_0_END                (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_ispss_ctrl__pwm_channel_1_START              (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_ispss_ctrl__pwm_channel_1_END                (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_cc_1__endofhist_START                        (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_cc_1__endofhist_END                          (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_cc_2__endofhist_START                        (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_cc_2__endofhist_END                          (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_ispss_ctrl__pwm_channel_2_START              (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_ispss_ctrl__pwm_channel_2_END                (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_ispss_ctrl__pwm_channel_3_START              (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_ispss_ctrl__pwm_channel_3_END                (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_ispss_ctrl__pwm_channel_4_START              (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_ispss_ctrl__pwm_channel_4_END                (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_ispss_ctrl__pwm_channel_5_START              (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_ispss_ctrl__pwm_channel_5_END                (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_ispss_ctrl__pwm_channel_6_START              (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_RIS_FRPROC_1_ispss_ctrl__pwm_channel_6_END                (31)


/*****************************************************************************
 结构名    : SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_UNION
 结构说明  : IRQ_MERGER_MIS_FRPROC_1 寄存器结构定义。地址偏移量:0xE8，初值:0x00000000，宽度:32
 寄存器说明: [Masked Interrupt Status Register] FRPROC register (bloc 1 over 1).
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scaler_1_2_y__fcm__sw_wr_ack_4        : 1;  /* bit[0-0]  : source: SCALER_1_2(Y) [63 over 63] NC */
        unsigned int  scaler_1_2_y__fcm__sw_rd_ack_4        : 1;  /* bit[1-1]  : source: SCALER_1_2(Y) [62 over 63] NC */
        unsigned int  scaler_1_2_uv__fcm__sw_wr_ack_5       : 1;  /* bit[2-2]  : source: SCALER_1_2(UV) [61 over 63] NC */
        unsigned int  scaler_1_2_uv__fcm__sw_rd_ack_5       : 1;  /* bit[3-3]  : source: SCALER_1_2(UV) [60 over 63] NC */
        unsigned int  scaler_3__end_of_rescale              : 1;  /* bit[4-4]  : source: NA [59 over 63] NC */
        unsigned int  stream_router__reformater_sof_0       : 1;  /* bit[5-5]  : source: NA [58 over 63] NC */
        unsigned int  stream_router__reformater_sof_1       : 1;  /* bit[6-6]  : source: NA [57 over 63] NC */
        unsigned int  stream_router__reformater_sof_2       : 1;  /* bit[7-7]  : source: NA [56 over 63] NC */
        unsigned int  stream_router__reformater_sof_3       : 1;  /* bit[8-8]  : source: NA [55 over 63] NC */
        unsigned int  stream_router__reformater_sof_4       : 1;  /* bit[9-9]  : source: NA [54 over 63] NC */
        unsigned int  stream_router__reformater_sof_5       : 1;  /* bit[10-10]: source: NA [53 over 63] NC */
        unsigned int  stream_router__reformater_sof_6       : 1;  /* bit[11-11]: source: NA [52 over 63] NC */
        unsigned int  stream_router__reformater_sof_7       : 1;  /* bit[12-12]: source: NA [51 over 63] NC */
        unsigned int  fd__process_finish                    : 1;  /* bit[13-13]: source: NA [50 over 63] NC */
        unsigned int  stat3a_1__3astats_ready               : 1;  /* bit[14-14]: source: NA [49 over 63] NC */
        unsigned int  stat3a_2__3astats_ready               : 1;  /* bit[15-15]: source: NA [48 over 63] NC */
        unsigned int  bas_1__end_of_filtering               : 1;  /* bit[16-16]: source: NA [47 over 63] NC */
        unsigned int  bas_2__end_of_filtering               : 1;  /* bit[17-17]: source: NA [46 over 63] NC */
        unsigned int  statdis_1__dis_ready                  : 1;  /* bit[18-18]: source: NA [45 over 63] NC */
        unsigned int  statdis_2__dis_ready                  : 1;  /* bit[19-19]: source: NA [44 over 63] NC */
        unsigned int  flash__flash_on                       : 1;  /* bit[20-20]: source: NA [43 over 63] NC */
        unsigned int  flash__flash_off                      : 1;  /* bit[21-21]: source: NA [42 over 63] NC */
        unsigned int  stream_router_5__cvdr_rt__eol_vpwr_24 : 1;  /* bit[22-22]: source: STREAM_ROUTER(5) [41 over 63] NC */
        unsigned int  ispss_ctrl__pwm_channel_0             : 1;  /* bit[23-23]: source: NA [40 over 63] NC */
        unsigned int  ispss_ctrl__pwm_channel_1             : 1;  /* bit[24-24]: source: NA [39 over 63] NC */
        unsigned int  cc_1__endofhist                       : 1;  /* bit[25-25]: source: NA [38 over 63] NC */
        unsigned int  cc_2__endofhist                       : 1;  /* bit[26-26]: source: NA [37 over 63] NC */
        unsigned int  ispss_ctrl__pwm_channel_2             : 1;  /* bit[27-27]: source: NA [36 over 63] NC */
        unsigned int  ispss_ctrl__pwm_channel_3             : 1;  /* bit[28-28]: source: NA [35 over 63] NC */
        unsigned int  ispss_ctrl__pwm_channel_4             : 1;  /* bit[29-29]: source: NA [34 over 63] NC */
        unsigned int  ispss_ctrl__pwm_channel_5             : 1;  /* bit[30-30]: source: NA [33 over 63] NC */
        unsigned int  ispss_ctrl__pwm_channel_6             : 1;  /* bit[31-31]: source: NA [32 over 63] NC */
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_scaler_1_2_y__fcm__sw_wr_ack_4_START         (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_scaler_1_2_y__fcm__sw_wr_ack_4_END           (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_scaler_1_2_y__fcm__sw_rd_ack_4_START         (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_scaler_1_2_y__fcm__sw_rd_ack_4_END           (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_scaler_1_2_uv__fcm__sw_wr_ack_5_START        (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_scaler_1_2_uv__fcm__sw_wr_ack_5_END          (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_scaler_1_2_uv__fcm__sw_rd_ack_5_START        (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_scaler_1_2_uv__fcm__sw_rd_ack_5_END          (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_scaler_3__end_of_rescale_START               (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_scaler_3__end_of_rescale_END                 (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_stream_router__reformater_sof_0_START        (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_stream_router__reformater_sof_0_END          (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_stream_router__reformater_sof_1_START        (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_stream_router__reformater_sof_1_END          (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_stream_router__reformater_sof_2_START        (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_stream_router__reformater_sof_2_END          (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_stream_router__reformater_sof_3_START        (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_stream_router__reformater_sof_3_END          (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_stream_router__reformater_sof_4_START        (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_stream_router__reformater_sof_4_END          (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_stream_router__reformater_sof_5_START        (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_stream_router__reformater_sof_5_END          (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_stream_router__reformater_sof_6_START        (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_stream_router__reformater_sof_6_END          (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_stream_router__reformater_sof_7_START        (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_stream_router__reformater_sof_7_END          (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_fd__process_finish_START                     (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_fd__process_finish_END                       (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_stat3a_1__3astats_ready_START                (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_stat3a_1__3astats_ready_END                  (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_stat3a_2__3astats_ready_START                (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_stat3a_2__3astats_ready_END                  (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_bas_1__end_of_filtering_START                (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_bas_1__end_of_filtering_END                  (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_bas_2__end_of_filtering_START                (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_bas_2__end_of_filtering_END                  (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_statdis_1__dis_ready_START                   (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_statdis_1__dis_ready_END                     (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_statdis_2__dis_ready_START                   (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_statdis_2__dis_ready_END                     (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_flash__flash_on_START                        (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_flash__flash_on_END                          (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_flash__flash_off_START                       (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_flash__flash_off_END                         (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_stream_router_5__cvdr_rt__eol_vpwr_24_START  (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_stream_router_5__cvdr_rt__eol_vpwr_24_END    (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_ispss_ctrl__pwm_channel_0_START              (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_ispss_ctrl__pwm_channel_0_END                (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_ispss_ctrl__pwm_channel_1_START              (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_ispss_ctrl__pwm_channel_1_END                (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_cc_1__endofhist_START                        (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_cc_1__endofhist_END                          (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_cc_2__endofhist_START                        (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_cc_2__endofhist_END                          (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_ispss_ctrl__pwm_channel_2_START              (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_ispss_ctrl__pwm_channel_2_END                (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_ispss_ctrl__pwm_channel_3_START              (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_ispss_ctrl__pwm_channel_3_END                (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_ispss_ctrl__pwm_channel_4_START              (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_ispss_ctrl__pwm_channel_4_END                (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_ispss_ctrl__pwm_channel_5_START              (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_ispss_ctrl__pwm_channel_5_END                (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_ispss_ctrl__pwm_channel_6_START              (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_MIS_FRPROC_1_ispss_ctrl__pwm_channel_6_END                (31)


/*****************************************************************************
 结构名    : SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_UNION
 结构说明  : IRQ_MERGER_ICR_FRPROC_1 寄存器结构定义。地址偏移量:0xEC，初值:0x00000000，宽度:32
 寄存器说明: [Interrupt Clear Register] FRPROC register (bloc 1 over 1).
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scaler_1_2_y__fcm__sw_wr_ack_4        : 1;  /* bit[0-0]  : source: SCALER_1_2(Y) [63 over 63] NC */
        unsigned int  scaler_1_2_y__fcm__sw_rd_ack_4        : 1;  /* bit[1-1]  : source: SCALER_1_2(Y) [62 over 63] NC */
        unsigned int  scaler_1_2_uv__fcm__sw_wr_ack_5       : 1;  /* bit[2-2]  : source: SCALER_1_2(UV) [61 over 63] NC */
        unsigned int  scaler_1_2_uv__fcm__sw_rd_ack_5       : 1;  /* bit[3-3]  : source: SCALER_1_2(UV) [60 over 63] NC */
        unsigned int  scaler_3__end_of_rescale              : 1;  /* bit[4-4]  : source: NA [59 over 63] NC */
        unsigned int  stream_router__reformater_sof_0       : 1;  /* bit[5-5]  : source: NA [58 over 63] NC */
        unsigned int  stream_router__reformater_sof_1       : 1;  /* bit[6-6]  : source: NA [57 over 63] NC */
        unsigned int  stream_router__reformater_sof_2       : 1;  /* bit[7-7]  : source: NA [56 over 63] NC */
        unsigned int  stream_router__reformater_sof_3       : 1;  /* bit[8-8]  : source: NA [55 over 63] NC */
        unsigned int  stream_router__reformater_sof_4       : 1;  /* bit[9-9]  : source: NA [54 over 63] NC */
        unsigned int  stream_router__reformater_sof_5       : 1;  /* bit[10-10]: source: NA [53 over 63] NC */
        unsigned int  stream_router__reformater_sof_6       : 1;  /* bit[11-11]: source: NA [52 over 63] NC */
        unsigned int  stream_router__reformater_sof_7       : 1;  /* bit[12-12]: source: NA [51 over 63] NC */
        unsigned int  fd__process_finish                    : 1;  /* bit[13-13]: source: NA [50 over 63] NC */
        unsigned int  stat3a_1__3astats_ready               : 1;  /* bit[14-14]: source: NA [49 over 63] NC */
        unsigned int  stat3a_2__3astats_ready               : 1;  /* bit[15-15]: source: NA [48 over 63] NC */
        unsigned int  bas_1__end_of_filtering               : 1;  /* bit[16-16]: source: NA [47 over 63] NC */
        unsigned int  bas_2__end_of_filtering               : 1;  /* bit[17-17]: source: NA [46 over 63] NC */
        unsigned int  statdis_1__dis_ready                  : 1;  /* bit[18-18]: source: NA [45 over 63] NC */
        unsigned int  statdis_2__dis_ready                  : 1;  /* bit[19-19]: source: NA [44 over 63] NC */
        unsigned int  flash__flash_on                       : 1;  /* bit[20-20]: source: NA [43 over 63] NC */
        unsigned int  flash__flash_off                      : 1;  /* bit[21-21]: source: NA [42 over 63] NC */
        unsigned int  stream_router_5__cvdr_rt__eol_vpwr_24 : 1;  /* bit[22-22]: source: STREAM_ROUTER(5) [41 over 63] NC */
        unsigned int  ispss_ctrl__pwm_channel_0             : 1;  /* bit[23-23]: source: NA [40 over 63] NC */
        unsigned int  ispss_ctrl__pwm_channel_1             : 1;  /* bit[24-24]: source: NA [39 over 63] NC */
        unsigned int  cc_1__endofhist                       : 1;  /* bit[25-25]: source: NA [38 over 63] NC */
        unsigned int  cc_2__endofhist                       : 1;  /* bit[26-26]: source: NA [37 over 63] NC */
        unsigned int  ispss_ctrl__pwm_channel_2             : 1;  /* bit[27-27]: source: NA [36 over 63] NC */
        unsigned int  ispss_ctrl__pwm_channel_3             : 1;  /* bit[28-28]: source: NA [35 over 63] NC */
        unsigned int  ispss_ctrl__pwm_channel_4             : 1;  /* bit[29-29]: source: NA [34 over 63] NC */
        unsigned int  ispss_ctrl__pwm_channel_5             : 1;  /* bit[30-30]: source: NA [33 over 63] NC */
        unsigned int  ispss_ctrl__pwm_channel_6             : 1;  /* bit[31-31]: source: NA [32 over 63] NC */
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_scaler_1_2_y__fcm__sw_wr_ack_4_START         (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_scaler_1_2_y__fcm__sw_wr_ack_4_END           (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_scaler_1_2_y__fcm__sw_rd_ack_4_START         (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_scaler_1_2_y__fcm__sw_rd_ack_4_END           (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_scaler_1_2_uv__fcm__sw_wr_ack_5_START        (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_scaler_1_2_uv__fcm__sw_wr_ack_5_END          (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_scaler_1_2_uv__fcm__sw_rd_ack_5_START        (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_scaler_1_2_uv__fcm__sw_rd_ack_5_END          (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_scaler_3__end_of_rescale_START               (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_scaler_3__end_of_rescale_END                 (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_stream_router__reformater_sof_0_START        (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_stream_router__reformater_sof_0_END          (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_stream_router__reformater_sof_1_START        (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_stream_router__reformater_sof_1_END          (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_stream_router__reformater_sof_2_START        (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_stream_router__reformater_sof_2_END          (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_stream_router__reformater_sof_3_START        (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_stream_router__reformater_sof_3_END          (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_stream_router__reformater_sof_4_START        (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_stream_router__reformater_sof_4_END          (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_stream_router__reformater_sof_5_START        (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_stream_router__reformater_sof_5_END          (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_stream_router__reformater_sof_6_START        (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_stream_router__reformater_sof_6_END          (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_stream_router__reformater_sof_7_START        (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_stream_router__reformater_sof_7_END          (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_fd__process_finish_START                     (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_fd__process_finish_END                       (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_stat3a_1__3astats_ready_START                (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_stat3a_1__3astats_ready_END                  (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_stat3a_2__3astats_ready_START                (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_stat3a_2__3astats_ready_END                  (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_bas_1__end_of_filtering_START                (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_bas_1__end_of_filtering_END                  (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_bas_2__end_of_filtering_START                (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_bas_2__end_of_filtering_END                  (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_statdis_1__dis_ready_START                   (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_statdis_1__dis_ready_END                     (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_statdis_2__dis_ready_START                   (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_statdis_2__dis_ready_END                     (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_flash__flash_on_START                        (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_flash__flash_on_END                          (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_flash__flash_off_START                       (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_flash__flash_off_END                         (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_stream_router_5__cvdr_rt__eol_vpwr_24_START  (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_stream_router_5__cvdr_rt__eol_vpwr_24_END    (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_ispss_ctrl__pwm_channel_0_START              (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_ispss_ctrl__pwm_channel_0_END                (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_ispss_ctrl__pwm_channel_1_START              (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_ispss_ctrl__pwm_channel_1_END                (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_cc_1__endofhist_START                        (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_cc_1__endofhist_END                          (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_cc_2__endofhist_START                        (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_cc_2__endofhist_END                          (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_ispss_ctrl__pwm_channel_2_START              (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_ispss_ctrl__pwm_channel_2_END                (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_ispss_ctrl__pwm_channel_3_START              (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_ispss_ctrl__pwm_channel_3_END                (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_ispss_ctrl__pwm_channel_4_START              (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_ispss_ctrl__pwm_channel_4_END                (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_ispss_ctrl__pwm_channel_5_START              (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_ispss_ctrl__pwm_channel_5_END                (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_ispss_ctrl__pwm_channel_6_START              (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ICR_FRPROC_1_ispss_ctrl__pwm_channel_6_END                (31)


/*****************************************************************************
 结构名    : SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_UNION
 结构说明  : IRQ_MERGER_ISR_FRPROC_1 寄存器结构定义。地址偏移量:0xF0，初值:0x00000000，宽度:32
 寄存器说明: [Interrupt Set Register] FRPROC register (bloc 1 over 1).
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scaler_1_2_y__fcm__sw_wr_ack_4        : 1;  /* bit[0-0]  : source: SCALER_1_2(Y) [63 over 63] NC */
        unsigned int  scaler_1_2_y__fcm__sw_rd_ack_4        : 1;  /* bit[1-1]  : source: SCALER_1_2(Y) [62 over 63] NC */
        unsigned int  scaler_1_2_uv__fcm__sw_wr_ack_5       : 1;  /* bit[2-2]  : source: SCALER_1_2(UV) [61 over 63] NC */
        unsigned int  scaler_1_2_uv__fcm__sw_rd_ack_5       : 1;  /* bit[3-3]  : source: SCALER_1_2(UV) [60 over 63] NC */
        unsigned int  scaler_3__end_of_rescale              : 1;  /* bit[4-4]  : source: NA [59 over 63] NC */
        unsigned int  stream_router__reformater_sof_0       : 1;  /* bit[5-5]  : source: NA [58 over 63] NC */
        unsigned int  stream_router__reformater_sof_1       : 1;  /* bit[6-6]  : source: NA [57 over 63] NC */
        unsigned int  stream_router__reformater_sof_2       : 1;  /* bit[7-7]  : source: NA [56 over 63] NC */
        unsigned int  stream_router__reformater_sof_3       : 1;  /* bit[8-8]  : source: NA [55 over 63] NC */
        unsigned int  stream_router__reformater_sof_4       : 1;  /* bit[9-9]  : source: NA [54 over 63] NC */
        unsigned int  stream_router__reformater_sof_5       : 1;  /* bit[10-10]: source: NA [53 over 63] NC */
        unsigned int  stream_router__reformater_sof_6       : 1;  /* bit[11-11]: source: NA [52 over 63] NC */
        unsigned int  stream_router__reformater_sof_7       : 1;  /* bit[12-12]: source: NA [51 over 63] NC */
        unsigned int  fd__process_finish                    : 1;  /* bit[13-13]: source: NA [50 over 63] NC */
        unsigned int  stat3a_1__3astats_ready               : 1;  /* bit[14-14]: source: NA [49 over 63] NC */
        unsigned int  stat3a_2__3astats_ready               : 1;  /* bit[15-15]: source: NA [48 over 63] NC */
        unsigned int  bas_1__end_of_filtering               : 1;  /* bit[16-16]: source: NA [47 over 63] NC */
        unsigned int  bas_2__end_of_filtering               : 1;  /* bit[17-17]: source: NA [46 over 63] NC */
        unsigned int  statdis_1__dis_ready                  : 1;  /* bit[18-18]: source: NA [45 over 63] NC */
        unsigned int  statdis_2__dis_ready                  : 1;  /* bit[19-19]: source: NA [44 over 63] NC */
        unsigned int  flash__flash_on                       : 1;  /* bit[20-20]: source: NA [43 over 63] NC */
        unsigned int  flash__flash_off                      : 1;  /* bit[21-21]: source: NA [42 over 63] NC */
        unsigned int  stream_router_5__cvdr_rt__eol_vpwr_24 : 1;  /* bit[22-22]: source: STREAM_ROUTER(5) [41 over 63] NC */
        unsigned int  ispss_ctrl__pwm_channel_0             : 1;  /* bit[23-23]: source: NA [40 over 63] NC */
        unsigned int  ispss_ctrl__pwm_channel_1             : 1;  /* bit[24-24]: source: NA [39 over 63] NC */
        unsigned int  cc_1__endofhist                       : 1;  /* bit[25-25]: source: NA [38 over 63] NC */
        unsigned int  cc_2__endofhist                       : 1;  /* bit[26-26]: source: NA [37 over 63] NC */
        unsigned int  ispss_ctrl__pwm_channel_2             : 1;  /* bit[27-27]: source: NA [36 over 63] NC */
        unsigned int  ispss_ctrl__pwm_channel_3             : 1;  /* bit[28-28]: source: NA [35 over 63] NC */
        unsigned int  ispss_ctrl__pwm_channel_4             : 1;  /* bit[29-29]: source: NA [34 over 63] NC */
        unsigned int  ispss_ctrl__pwm_channel_5             : 1;  /* bit[30-30]: source: NA [33 over 63] NC */
        unsigned int  ispss_ctrl__pwm_channel_6             : 1;  /* bit[31-31]: source: NA [32 over 63] NC */
    } reg;
} SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_UNION;
#endif
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_scaler_1_2_y__fcm__sw_wr_ack_4_START         (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_scaler_1_2_y__fcm__sw_wr_ack_4_END           (0)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_scaler_1_2_y__fcm__sw_rd_ack_4_START         (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_scaler_1_2_y__fcm__sw_rd_ack_4_END           (1)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_scaler_1_2_uv__fcm__sw_wr_ack_5_START        (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_scaler_1_2_uv__fcm__sw_wr_ack_5_END          (2)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_scaler_1_2_uv__fcm__sw_rd_ack_5_START        (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_scaler_1_2_uv__fcm__sw_rd_ack_5_END          (3)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_scaler_3__end_of_rescale_START               (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_scaler_3__end_of_rescale_END                 (4)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_stream_router__reformater_sof_0_START        (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_stream_router__reformater_sof_0_END          (5)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_stream_router__reformater_sof_1_START        (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_stream_router__reformater_sof_1_END          (6)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_stream_router__reformater_sof_2_START        (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_stream_router__reformater_sof_2_END          (7)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_stream_router__reformater_sof_3_START        (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_stream_router__reformater_sof_3_END          (8)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_stream_router__reformater_sof_4_START        (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_stream_router__reformater_sof_4_END          (9)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_stream_router__reformater_sof_5_START        (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_stream_router__reformater_sof_5_END          (10)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_stream_router__reformater_sof_6_START        (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_stream_router__reformater_sof_6_END          (11)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_stream_router__reformater_sof_7_START        (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_stream_router__reformater_sof_7_END          (12)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_fd__process_finish_START                     (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_fd__process_finish_END                       (13)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_stat3a_1__3astats_ready_START                (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_stat3a_1__3astats_ready_END                  (14)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_stat3a_2__3astats_ready_START                (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_stat3a_2__3astats_ready_END                  (15)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_bas_1__end_of_filtering_START                (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_bas_1__end_of_filtering_END                  (16)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_bas_2__end_of_filtering_START                (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_bas_2__end_of_filtering_END                  (17)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_statdis_1__dis_ready_START                   (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_statdis_1__dis_ready_END                     (18)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_statdis_2__dis_ready_START                   (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_statdis_2__dis_ready_END                     (19)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_flash__flash_on_START                        (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_flash__flash_on_END                          (20)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_flash__flash_off_START                       (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_flash__flash_off_END                         (21)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_stream_router_5__cvdr_rt__eol_vpwr_24_START  (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_stream_router_5__cvdr_rt__eol_vpwr_24_END    (22)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_ispss_ctrl__pwm_channel_0_START              (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_ispss_ctrl__pwm_channel_0_END                (23)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_ispss_ctrl__pwm_channel_1_START              (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_ispss_ctrl__pwm_channel_1_END                (24)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_cc_1__endofhist_START                        (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_cc_1__endofhist_END                          (25)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_cc_2__endofhist_START                        (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_cc_2__endofhist_END                          (26)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_ispss_ctrl__pwm_channel_2_START              (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_ispss_ctrl__pwm_channel_2_END                (27)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_ispss_ctrl__pwm_channel_3_START              (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_ispss_ctrl__pwm_channel_3_END                (28)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_ispss_ctrl__pwm_channel_4_START              (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_ispss_ctrl__pwm_channel_4_END                (29)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_ispss_ctrl__pwm_channel_5_START              (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_ispss_ctrl__pwm_channel_5_END                (30)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_ispss_ctrl__pwm_channel_6_START              (31)
#define SOC_ISP_IRQ_MERGER_IRQ_MERGER_ISR_FRPROC_1_ispss_ctrl__pwm_channel_6_END                (31)






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

#endif /* end of soc_isp_irq_merger_interface.h */
