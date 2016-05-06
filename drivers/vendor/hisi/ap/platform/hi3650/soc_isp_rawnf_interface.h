/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_isp_rawnf_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-04-08 11:47:09
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年4月8日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_ISP_RAWNF.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_ISP_RAWNF_INTERFACE_H__
#define __SOC_ISP_RAWNF_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) RAWNF
 ****************************************************************************/
/* 寄存器说明：Mode control for Denoising Pre-Filter block.
   位域定义UNION结构:  SOC_ISP_RAWNF_ISP_DPF_MODE_UNION */
#define SOC_ISP_RAWNF_ISP_DPF_MODE_ADDR(base)         ((base) + (0x0000))

/* 寄存器说明：Filter strength of the RED filter.
   位域定义UNION结构:  SOC_ISP_RAWNF_ISP_DPF_STRENGTH_R_UNION */
#define SOC_ISP_RAWNF_ISP_DPF_STRENGTH_R_ADDR(base)   ((base) + (0x0004))

/* 寄存器说明：Filter strength of the GREEN filter.
   位域定义UNION结构:  SOC_ISP_RAWNF_ISP_DPF_STRENGTH_G_UNION */
#define SOC_ISP_RAWNF_ISP_DPF_STRENGTH_G_ADDR(base)   ((base) + (0x0008))

/* 寄存器说明：Filter strength of the BLUE filter.
   位域定义UNION结构:  SOC_ISP_RAWNF_ISP_DPF_STRENGTH_B_UNION */
#define SOC_ISP_RAWNF_ISP_DPF_STRENGTH_B_ADDR(base)   ((base) + (0x000C))

/* 寄存器说明：Noise Level Lookup Coefficient.
   位域定义UNION结构:  SOC_ISP_RAWNF_ISP_DPF_NLL_COEFF_UNION */
#define SOC_ISP_RAWNF_ISP_DPF_NLL_COEFF_ADDR(base, Range16)  ((base) + (0x0010+0x4*(Range16)))

/* 寄存器说明：Noise function gain for red pixels.
   位域定义UNION结构:  SOC_ISP_RAWNF_ISP_DPF_NF_GAIN_R_UNION */
#define SOC_ISP_RAWNF_ISP_DPF_NF_GAIN_R_ADDR(base)    ((base) + (0x0054))

/* 寄存器说明：Noise function gain for green in red pixels.
   位域定义UNION结构:  SOC_ISP_RAWNF_ISP_DPF_NF_GAIN_GR_UNION */
#define SOC_ISP_RAWNF_ISP_DPF_NF_GAIN_GR_ADDR(base)   ((base) + (0x0058))

/* 寄存器说明：Noise function gain for green in blue pixels.
   位域定义UNION结构:  SOC_ISP_RAWNF_ISP_DPF_NF_GAIN_GB_UNION */
#define SOC_ISP_RAWNF_ISP_DPF_NF_GAIN_GB_ADDR(base)   ((base) + (0x005C))

/* 寄存器说明：Noise function gain for blue pixels.
   位域定义UNION结构:  SOC_ISP_RAWNF_ISP_DPF_NF_GAIN_B_UNION */
#define SOC_ISP_RAWNF_ISP_DPF_NF_GAIN_B_ADDR(base)    ((base) + (0x0060))

/* 寄存器说明：Green Imbalance Correction Control.
   位域定义UNION结构:  SOC_ISP_RAWNF_ISP_DPF_N_MODE_UNION */
#define SOC_ISP_RAWNF_ISP_DPF_N_MODE_ADDR(base)       ((base) + (0x0064))

/* 寄存器说明：Green Imbalance Correction Threshold.
   位域定义UNION结构:  SOC_ISP_RAWNF_ISP_DPF_GBGR_THR_UNION */
#define SOC_ISP_RAWNF_ISP_DPF_GBGR_THR_ADDR(base)     ((base) + (0x0068))

/* 寄存器说明：LSC Gain.
   位域定义UNION结构:  SOC_ISP_RAWNF_ISP_DPF_GAIN_DENOISE_UNION */
#define SOC_ISP_RAWNF_ISP_DPF_GAIN_DENOISE_ADDR(base) ((base) + (0x006C))

/* 寄存器说明：Luma.
   位域定义UNION结构:  SOC_ISP_RAWNF_ISP_DPF_LUMA_UNION */
#define SOC_ISP_RAWNF_ISP_DPF_LUMA_ADDR(base)         ((base) + (0x0070))

/* 寄存器说明：Blending.
   位域定义UNION结构:  SOC_ISP_RAWNF_ISP_DPF_BLEND_UNION */
#define SOC_ISP_RAWNF_ISP_DPF_BLEND_ADDR(base)        ((base) + (0x0074))

/* 寄存器说明：Red/Blue Gauss Coef.
   位域定义UNION结构:  SOC_ISP_RAWNF_ISP_DPF_GAUSS_RB_UNION */
#define SOC_ISP_RAWNF_ISP_DPF_GAUSS_RB_ADDR(base)     ((base) + (0x0078))

/* 寄存器说明：Green Gauss Coef.
   位域定义UNION结构:  SOC_ISP_RAWNF_ISP_DPF_GAUSS_G_UNION */
#define SOC_ISP_RAWNF_ISP_DPF_GAUSS_G_ADDR(base)      ((base) + (0x007C))

/* 寄存器说明：Edge Threshold.
   位域定义UNION结构:  SOC_ISP_RAWNF_ISP_DPF_EDGE_THLD_UNION */
#define SOC_ISP_RAWNF_ISP_DPF_EDGE_THLD_ADDR(base)    ((base) + (0x0080))

/* 寄存器说明：Diff Threshold.
   位域定义UNION结构:  SOC_ISP_RAWNF_ISP_DPF_DIFF_THLD_UNION */
#define SOC_ISP_RAWNF_ISP_DPF_DIFF_THLD_ADDR(base)    ((base) + (0x0084))





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
                     (1/1) RAWNF
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_ISP_RAWNF_ISP_DPF_MODE_UNION
 结构说明  : ISP_DPF_MODE 寄存器结构定义。地址偏移量:0x0000，初值:0x00000000，宽度:32
 寄存器说明: Mode control for Denoising Pre-Filter block.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dpf_enable             : 1;  /* bit[0-0]  : 1: enable dpf 
                                                                  0: bypass dpf *Default* */
        unsigned int  b_filter_off           : 1;  /* bit[1-1]  : 1: disable filter processing for blue pixels (B) 
                                                                  0: filter B pixels *Default* */
        unsigned int  gb_filter_off          : 1;  /* bit[2-2]  : 1: disable filter processing for green pixels in green/blue lines (GB) 
                                                                  0: filter GB pixels *Default* */
        unsigned int  gr_filter_off          : 1;  /* bit[3-3]  : 1: disable filter processing for green pixels in green/red lines (GR) 
                                                                  0: filter GR pixels *Default* */
        unsigned int  r_filter_off           : 1;  /* bit[4-4]  : 1: disable filter processing for red pixels (R) 
                                                                  0: filter R pixels *Default* */
        unsigned int  nll_segmentation       : 1;  /* bit[5-5]  : 1: optimized logarithmic like segmentation for Noise Level Lookup (NLL) 
                                                                  0: equidistant segmentation for NLL *Default* */
        unsigned int  awb_gain_comp          : 1;  /* bit[6-6]  : 1: AWB gain or internal dpf_nf_gain will be processed 
                                                                  0: AWB gain or internal dpf_nf_gain will not be processed *Default* */
        unsigned int  lsc_gain_comp          : 1;  /* bit[7-7]  : 1: LSC gain will be processed 
                                                                  0: LSC gain will not be processed *Default* */
        unsigned int  lsc_gain_offset_enable : 1;  /* bit[8-8]  : 1: LSC gain offset will be processed 
                                                                  0: LSC gain offset will not be processed *Default* */
        unsigned int  dpf_filt_method        : 1;  /* bit[9-9]  : select dpf filtering method
                                                                  1: Non Local Mean (NLM)
                                                                  0: Bilateral */
        unsigned int  gauss_blend_enable     : 1;  /* bit[10-10]: 1: enable gauss filter blending
                                                                  0: disable gauss filter blending */
        unsigned int  orgn_blend_enable      : 1;  /* bit[11-11]:  */
        unsigned int  power_en               : 1;  /* bit[12-12]: 1: Power Optimization
                                                                  0: No Power Optimization */
        unsigned int  reserved               : 19; /* bit[13-31]:  */
    } reg;
} SOC_ISP_RAWNF_ISP_DPF_MODE_UNION;
#endif
#define SOC_ISP_RAWNF_ISP_DPF_MODE_dpf_enable_START              (0)
#define SOC_ISP_RAWNF_ISP_DPF_MODE_dpf_enable_END                (0)
#define SOC_ISP_RAWNF_ISP_DPF_MODE_b_filter_off_START            (1)
#define SOC_ISP_RAWNF_ISP_DPF_MODE_b_filter_off_END              (1)
#define SOC_ISP_RAWNF_ISP_DPF_MODE_gb_filter_off_START           (2)
#define SOC_ISP_RAWNF_ISP_DPF_MODE_gb_filter_off_END             (2)
#define SOC_ISP_RAWNF_ISP_DPF_MODE_gr_filter_off_START           (3)
#define SOC_ISP_RAWNF_ISP_DPF_MODE_gr_filter_off_END             (3)
#define SOC_ISP_RAWNF_ISP_DPF_MODE_r_filter_off_START            (4)
#define SOC_ISP_RAWNF_ISP_DPF_MODE_r_filter_off_END              (4)
#define SOC_ISP_RAWNF_ISP_DPF_MODE_nll_segmentation_START        (5)
#define SOC_ISP_RAWNF_ISP_DPF_MODE_nll_segmentation_END          (5)
#define SOC_ISP_RAWNF_ISP_DPF_MODE_awb_gain_comp_START           (6)
#define SOC_ISP_RAWNF_ISP_DPF_MODE_awb_gain_comp_END             (6)
#define SOC_ISP_RAWNF_ISP_DPF_MODE_lsc_gain_comp_START           (7)
#define SOC_ISP_RAWNF_ISP_DPF_MODE_lsc_gain_comp_END             (7)
#define SOC_ISP_RAWNF_ISP_DPF_MODE_lsc_gain_offset_enable_START  (8)
#define SOC_ISP_RAWNF_ISP_DPF_MODE_lsc_gain_offset_enable_END    (8)
#define SOC_ISP_RAWNF_ISP_DPF_MODE_dpf_filt_method_START         (9)
#define SOC_ISP_RAWNF_ISP_DPF_MODE_dpf_filt_method_END           (9)
#define SOC_ISP_RAWNF_ISP_DPF_MODE_gauss_blend_enable_START      (10)
#define SOC_ISP_RAWNF_ISP_DPF_MODE_gauss_blend_enable_END        (10)
#define SOC_ISP_RAWNF_ISP_DPF_MODE_orgn_blend_enable_START       (11)
#define SOC_ISP_RAWNF_ISP_DPF_MODE_orgn_blend_enable_END         (11)
#define SOC_ISP_RAWNF_ISP_DPF_MODE_power_en_START                (12)
#define SOC_ISP_RAWNF_ISP_DPF_MODE_power_en_END                  (12)


/*****************************************************************************
 结构名    : SOC_ISP_RAWNF_ISP_DPF_STRENGTH_R_UNION
 结构说明  : ISP_DPF_STRENGTH_R 寄存器结构定义。地址偏移量:0x0004，初值:0x00000040，宽度:32
 寄存器说明: Filter strength of the RED filter.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  inv_weight_r : 8;  /* bit[0-7] : Filter strength of the filter is determined by weight. Default is a weight of 1. A higher weight increases the filter strength. In this register the unsigned 8 bit value 64/weight is stored. 
                                                       
                                                       The following values show examples: 
                                                       weight=0.251 -> 255, weight=0.5 -> 128, 
                                                       weight=1 -> 64 *default* 
                                                       weight=1.25 -> 51, weight=1.5 -> 42, 
                                                       weight=1.75 -> 37, weight=2 -> 32 */
        unsigned int  reserved     : 24; /* bit[8-31]:  */
    } reg;
} SOC_ISP_RAWNF_ISP_DPF_STRENGTH_R_UNION;
#endif
#define SOC_ISP_RAWNF_ISP_DPF_STRENGTH_R_inv_weight_r_START  (0)
#define SOC_ISP_RAWNF_ISP_DPF_STRENGTH_R_inv_weight_r_END    (7)


/*****************************************************************************
 结构名    : SOC_ISP_RAWNF_ISP_DPF_STRENGTH_G_UNION
 结构说明  : ISP_DPF_STRENGTH_G 寄存器结构定义。地址偏移量:0x0008，初值:0x00000040，宽度:32
 寄存器说明: Filter strength of the GREEN filter.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  inv_weight_g : 8;  /* bit[0-7] : Filter strength of the filter is determined by weight. Default is a weight of 1. A higher weight increases the filter strength. In this register the unsigned 8 bit value 64/weight is stored. 
                                                       
                                                       The following values show examples: 
                                                       weight=0.251 -> 255, weight=0.5 -> 128, 
                                                       weight=1 -> 64 *default* 
                                                       weight=1.25 -> 51, weight=1.5 -> 42, 
                                                       weight=1.75 -> 37, weight=2 -> 32 */
        unsigned int  reserved     : 24; /* bit[8-31]:  */
    } reg;
} SOC_ISP_RAWNF_ISP_DPF_STRENGTH_G_UNION;
#endif
#define SOC_ISP_RAWNF_ISP_DPF_STRENGTH_G_inv_weight_g_START  (0)
#define SOC_ISP_RAWNF_ISP_DPF_STRENGTH_G_inv_weight_g_END    (7)


/*****************************************************************************
 结构名    : SOC_ISP_RAWNF_ISP_DPF_STRENGTH_B_UNION
 结构说明  : ISP_DPF_STRENGTH_B 寄存器结构定义。地址偏移量:0x000C，初值:0x00000040，宽度:32
 寄存器说明: Filter strength of the BLUE filter.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  inv_weight_b : 8;  /* bit[0-7] : Filter strength of the filter is determined by weight. Default is a weight of 1. A higher weight increases the filter strength. In this register the unsigned 8 bit value 64/weight is stored. 
                                                       
                                                       The following values show examples: 
                                                       weight=0.251 -> 255, weight=0.5 -> 128, 
                                                       weight=1 -> 64 *default* 
                                                       weight=1.25 -> 51, weight=1.5 -> 42, 
                                                       weight=1.75 -> 37, weight=2 -> 32 */
        unsigned int  reserved     : 24; /* bit[8-31]:  */
    } reg;
} SOC_ISP_RAWNF_ISP_DPF_STRENGTH_B_UNION;
#endif
#define SOC_ISP_RAWNF_ISP_DPF_STRENGTH_B_inv_weight_b_START  (0)
#define SOC_ISP_RAWNF_ISP_DPF_STRENGTH_B_inv_weight_b_END    (7)


/*****************************************************************************
 结构名    : SOC_ISP_RAWNF_ISP_DPF_NLL_COEFF_UNION
 结构说明  : ISP_DPF_NLL_COEFF 寄存器结构定义。地址偏移量:0x0010+0x4*(Range16)，初值:0x000003FF，宽度:32
 寄存器说明: Noise Level Lookup Coefficient.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  nll_coeff : 10; /* bit[0-9]  : Noise Level Lookup Table Coefficient nll_coeff_n 
                                                     10 bit unsigned, value range 1/1024 to 1023/1024 (*Default*) */
        unsigned int  reserved  : 22; /* bit[10-31]:  */
    } reg;
} SOC_ISP_RAWNF_ISP_DPF_NLL_COEFF_UNION;
#endif
#define SOC_ISP_RAWNF_ISP_DPF_NLL_COEFF_nll_coeff_START  (0)
#define SOC_ISP_RAWNF_ISP_DPF_NLL_COEFF_nll_coeff_END    (9)


/*****************************************************************************
 结构名    : SOC_ISP_RAWNF_ISP_DPF_NF_GAIN_R_UNION
 结构说明  : ISP_DPF_NF_GAIN_R 寄存器结构定义。地址偏移量:0x0054，初值:0x00000100，宽度:32
 寄存器说明: Noise function gain for red pixels.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dpf_nf_gain_r : 12; /* bit[0-11] : Noise Function (NF) Gain that replaces the AWB gain for red pixels. 
                                                         12 bit unsigned integer format: gain=1 -> 0x100 */
        unsigned int  reserved      : 20; /* bit[12-31]:  */
    } reg;
} SOC_ISP_RAWNF_ISP_DPF_NF_GAIN_R_UNION;
#endif
#define SOC_ISP_RAWNF_ISP_DPF_NF_GAIN_R_dpf_nf_gain_r_START  (0)
#define SOC_ISP_RAWNF_ISP_DPF_NF_GAIN_R_dpf_nf_gain_r_END    (11)


/*****************************************************************************
 结构名    : SOC_ISP_RAWNF_ISP_DPF_NF_GAIN_GR_UNION
 结构说明  : ISP_DPF_NF_GAIN_GR 寄存器结构定义。地址偏移量:0x0058，初值:0x00000100，宽度:32
 寄存器说明: Noise function gain for green in red pixels.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dpf_nf_gain_gr : 12; /* bit[0-11] : Noise Function (NF) Gain that replaces the AWB gain for green pixels in a red line. 
                                                          12 bit unsigned integer format: gain=1 -> 0x100 */
        unsigned int  reserved       : 20; /* bit[12-31]:  */
    } reg;
} SOC_ISP_RAWNF_ISP_DPF_NF_GAIN_GR_UNION;
#endif
#define SOC_ISP_RAWNF_ISP_DPF_NF_GAIN_GR_dpf_nf_gain_gr_START  (0)
#define SOC_ISP_RAWNF_ISP_DPF_NF_GAIN_GR_dpf_nf_gain_gr_END    (11)


/*****************************************************************************
 结构名    : SOC_ISP_RAWNF_ISP_DPF_NF_GAIN_GB_UNION
 结构说明  : ISP_DPF_NF_GAIN_GB 寄存器结构定义。地址偏移量:0x005C，初值:0x00000100，宽度:32
 寄存器说明: Noise function gain for green in blue pixels.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dpf_nf_gain_gb : 12; /* bit[0-11] : Noise Function (NF) Gain that replaces the AWB gain for green pixels in a blue line. 
                                                          12 bit unsigned integer format: gain=1 -> 0x100 */
        unsigned int  reserved       : 20; /* bit[12-31]:  */
    } reg;
} SOC_ISP_RAWNF_ISP_DPF_NF_GAIN_GB_UNION;
#endif
#define SOC_ISP_RAWNF_ISP_DPF_NF_GAIN_GB_dpf_nf_gain_gb_START  (0)
#define SOC_ISP_RAWNF_ISP_DPF_NF_GAIN_GB_dpf_nf_gain_gb_END    (11)


/*****************************************************************************
 结构名    : SOC_ISP_RAWNF_ISP_DPF_NF_GAIN_B_UNION
 结构说明  : ISP_DPF_NF_GAIN_B 寄存器结构定义。地址偏移量:0x0060，初值:0x00000100，宽度:32
 寄存器说明: Noise function gain for blue pixels.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dpf_nf_gain_b : 12; /* bit[0-11] : Noise Function (NF) Gain that replaces the AWB gain for blue pixels. 
                                                         12 bit unsigned integer format: gain=1 -> 0x100 */
        unsigned int  reserved      : 20; /* bit[12-31]:  */
    } reg;
} SOC_ISP_RAWNF_ISP_DPF_NF_GAIN_B_UNION;
#endif
#define SOC_ISP_RAWNF_ISP_DPF_NF_GAIN_B_dpf_nf_gain_b_START  (0)
#define SOC_ISP_RAWNF_ISP_DPF_NF_GAIN_B_dpf_nf_gain_b_END    (11)


/*****************************************************************************
 结构名    : SOC_ISP_RAWNF_ISP_DPF_N_MODE_UNION
 结构说明  : ISP_DPF_N_MODE 寄存器结构定义。地址偏移量:0x0064，初值:0x00000000，宽度:32
 寄存器说明: Green Imbalance Correction Control.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  en       : 1;  /* bit[0-0] : GbGr Green Imbalance Correction Enable */
        unsigned int  thr_en   : 1;  /* bit[1-1] : GbGr Green Imbalance Correction Threshold Enable */
        unsigned int  reserved : 30; /* bit[2-31]:  */
    } reg;
} SOC_ISP_RAWNF_ISP_DPF_N_MODE_UNION;
#endif
#define SOC_ISP_RAWNF_ISP_DPF_N_MODE_en_START        (0)
#define SOC_ISP_RAWNF_ISP_DPF_N_MODE_en_END          (0)
#define SOC_ISP_RAWNF_ISP_DPF_N_MODE_thr_en_START    (1)
#define SOC_ISP_RAWNF_ISP_DPF_N_MODE_thr_en_END      (1)


/*****************************************************************************
 结构名    : SOC_ISP_RAWNF_ISP_DPF_GBGR_THR_UNION
 结构说明  : ISP_DPF_GBGR_THR 寄存器结构定义。地址偏移量:0x0068，初值:0x00000000，宽度:32
 寄存器说明: Green Imbalance Correction Threshold.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  thr      : 12; /* bit[0-11] : GbGr Green Imbalance Correction Threshold Value */
        unsigned int  reserved : 20; /* bit[12-31]:  */
    } reg;
} SOC_ISP_RAWNF_ISP_DPF_GBGR_THR_UNION;
#endif
#define SOC_ISP_RAWNF_ISP_DPF_GBGR_THR_thr_START       (0)
#define SOC_ISP_RAWNF_ISP_DPF_GBGR_THR_thr_END         (11)


/*****************************************************************************
 结构名    : SOC_ISP_RAWNF_ISP_DPF_GAIN_DENOISE_UNION
 结构说明  : ISP_DPF_GAIN_DENOISE 寄存器结构定义。地址偏移量:0x006C，初值:0x00000000，宽度:32
 寄存器说明: LSC Gain.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lsc_gain_offset_slope : 6;  /* bit[0-5]  : LSC gain offset slope */
        unsigned int  reserved_0            : 2;  /* bit[6-7]  :  */
        unsigned int  max_lsc_gain_offset   : 6;  /* bit[8-13] : Inverse strenght maximal vlaue */
        unsigned int  reserved_1            : 2;  /* bit[14-15]:  */
        unsigned int  lsc_offset_scale      : 6;  /* bit[16-21]: scale of lsc_gain offset for Gaussian filter blending */
        unsigned int  reserved_2            : 10; /* bit[22-31]:  */
    } reg;
} SOC_ISP_RAWNF_ISP_DPF_GAIN_DENOISE_UNION;
#endif
#define SOC_ISP_RAWNF_ISP_DPF_GAIN_DENOISE_lsc_gain_offset_slope_START  (0)
#define SOC_ISP_RAWNF_ISP_DPF_GAIN_DENOISE_lsc_gain_offset_slope_END    (5)
#define SOC_ISP_RAWNF_ISP_DPF_GAIN_DENOISE_max_lsc_gain_offset_START    (8)
#define SOC_ISP_RAWNF_ISP_DPF_GAIN_DENOISE_max_lsc_gain_offset_END      (13)
#define SOC_ISP_RAWNF_ISP_DPF_GAIN_DENOISE_lsc_offset_scale_START       (16)
#define SOC_ISP_RAWNF_ISP_DPF_GAIN_DENOISE_lsc_offset_scale_END         (21)


/*****************************************************************************
 结构名    : SOC_ISP_RAWNF_ISP_DPF_LUMA_UNION
 结构说明  : ISP_DPF_LUMA 寄存器结构定义。地址偏移量:0x0070，初值:0x000000ff，宽度:32
 寄存器说明: Luma.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  luma_offset_thld  : 8;  /* bit[0-7]  : threshold of luma for adjusting blending weight */
        unsigned int  luma_offset_slope : 8;  /* bit[8-15] : the slope for adjusting blending weight */
        unsigned int  luma_offset_max   : 8;  /* bit[16-23]: the max offset for adjust blending weight based on luma */
        unsigned int  reserved          : 8;  /* bit[24-31]:  */
    } reg;
} SOC_ISP_RAWNF_ISP_DPF_LUMA_UNION;
#endif
#define SOC_ISP_RAWNF_ISP_DPF_LUMA_luma_offset_thld_START   (0)
#define SOC_ISP_RAWNF_ISP_DPF_LUMA_luma_offset_thld_END     (7)
#define SOC_ISP_RAWNF_ISP_DPF_LUMA_luma_offset_slope_START  (8)
#define SOC_ISP_RAWNF_ISP_DPF_LUMA_luma_offset_slope_END    (15)
#define SOC_ISP_RAWNF_ISP_DPF_LUMA_luma_offset_max_START    (16)
#define SOC_ISP_RAWNF_ISP_DPF_LUMA_luma_offset_max_END      (23)


/*****************************************************************************
 结构名    : SOC_ISP_RAWNF_ISP_DPF_BLEND_UNION
 结构说明  : ISP_DPF_BLEND 寄存器结构定义。地址偏移量:0x0074，初值:0x01000000，宽度:32
 寄存器说明: Blending.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  base_blend_min : 8;  /* bit[0-7]  : the min blending weight of base filter result */
        unsigned int  diff_scale     : 6;  /* bit[8-13] :  */
        unsigned int  reserved_0     : 2;  /* bit[14-15]:  */
        unsigned int  edge_scale     : 9;  /* bit[16-24]:  */
        unsigned int  reserved_1     : 7;  /* bit[25-31]:  */
    } reg;
} SOC_ISP_RAWNF_ISP_DPF_BLEND_UNION;
#endif
#define SOC_ISP_RAWNF_ISP_DPF_BLEND_base_blend_min_START  (0)
#define SOC_ISP_RAWNF_ISP_DPF_BLEND_base_blend_min_END    (7)
#define SOC_ISP_RAWNF_ISP_DPF_BLEND_diff_scale_START      (8)
#define SOC_ISP_RAWNF_ISP_DPF_BLEND_diff_scale_END        (13)
#define SOC_ISP_RAWNF_ISP_DPF_BLEND_edge_scale_START      (16)
#define SOC_ISP_RAWNF_ISP_DPF_BLEND_edge_scale_END        (24)


/*****************************************************************************
 结构名    : SOC_ISP_RAWNF_ISP_DPF_GAUSS_RB_UNION
 结构说明  : ISP_DPF_GAUSS_RB 寄存器结构定义。地址偏移量:0x0078，初值:0x00034141，宽度:32
 寄存器说明: Red/Blue Gauss Coef.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rb_gauss_coef_0 : 6;  /* bit[0-5]  : gauss filter coefficient 0 for R/B channel, must meet:
                                                           2*rb_gauss_coef_0 + 2*rb_gauss_coef_1 + rb_gauss_coef_2 = 0x40 */
        unsigned int  rb_gauss_coef_1 : 6;  /* bit[6-11] : gauss filter coefficient 1 for R/B channel, must meet:
                                                           2*rb_gauss_coef_0 + 2*rb_gauss_coef_1 + rb_gauss_coef_2 = 0x40 */
        unsigned int  rb_gauss_coef_2 : 6;  /* bit[12-17]: gauss filter coefficient 2 for R/B channel, must meet:
                                                           2*rb_gauss_coef_0 + 2*rb_gauss_coef_1 + rb_gauss_coef_2 = 0x40 */
        unsigned int  reserved        : 14; /* bit[18-31]:  */
    } reg;
} SOC_ISP_RAWNF_ISP_DPF_GAUSS_RB_UNION;
#endif
#define SOC_ISP_RAWNF_ISP_DPF_GAUSS_RB_rb_gauss_coef_0_START  (0)
#define SOC_ISP_RAWNF_ISP_DPF_GAUSS_RB_rb_gauss_coef_0_END    (5)
#define SOC_ISP_RAWNF_ISP_DPF_GAUSS_RB_rb_gauss_coef_1_START  (6)
#define SOC_ISP_RAWNF_ISP_DPF_GAUSS_RB_rb_gauss_coef_1_END    (11)
#define SOC_ISP_RAWNF_ISP_DPF_GAUSS_RB_rb_gauss_coef_2_START  (12)
#define SOC_ISP_RAWNF_ISP_DPF_GAUSS_RB_rb_gauss_coef_2_END    (17)


/*****************************************************************************
 结构名    : SOC_ISP_RAWNF_ISP_DPF_GAUSS_G_UNION
 结构说明  : ISP_DPF_GAUSS_G 寄存器结构定义。地址偏移量:0x007C，初值:0x00034141，宽度:32
 寄存器说明: Green Gauss Coef.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g_gauss_coef_0 : 6;  /* bit[0-5]  : gauss filter coefficient 0 for Gr/Gb channel, must meet:
                                                          2*g_gauss_coef_0 + 2*g_gauss_coef_1 + g_gauss_coef_2 = 0x40 */
        unsigned int  g_gauss_coef_1 : 6;  /* bit[6-11] : gauss filter coefficient 1 for Gr/Gb channel, must meet:
                                                          2*g_gauss_coef_0 + 2*g_gauss_coef_1 + g_gauss_coef_2 = 0x40 */
        unsigned int  g_gauss_coef_2 : 6;  /* bit[12-17]: gauss filter coefficient 2 for Gr/Gb channel, must meet:
                                                          2*g_gauss_coef_0 + 2*g_gauss_coef_1 + g_gauss_coef_2 = 0x40 */
        unsigned int  reserved       : 14; /* bit[18-31]:  */
    } reg;
} SOC_ISP_RAWNF_ISP_DPF_GAUSS_G_UNION;
#endif
#define SOC_ISP_RAWNF_ISP_DPF_GAUSS_G_g_gauss_coef_0_START  (0)
#define SOC_ISP_RAWNF_ISP_DPF_GAUSS_G_g_gauss_coef_0_END    (5)
#define SOC_ISP_RAWNF_ISP_DPF_GAUSS_G_g_gauss_coef_1_START  (6)
#define SOC_ISP_RAWNF_ISP_DPF_GAUSS_G_g_gauss_coef_1_END    (11)
#define SOC_ISP_RAWNF_ISP_DPF_GAUSS_G_g_gauss_coef_2_START  (12)
#define SOC_ISP_RAWNF_ISP_DPF_GAUSS_G_g_gauss_coef_2_END    (17)


/*****************************************************************************
 结构名    : SOC_ISP_RAWNF_ISP_DPF_EDGE_THLD_UNION
 结构说明  : ISP_DPF_EDGE_THLD 寄存器结构定义。地址偏移量:0x0080，初值:0x00004000，宽度:32
 寄存器说明: Edge Threshold.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  edge_low_thld  : 8;  /* bit[0-7]  : edge_high_thld should be greater than edge_low_thld */
        unsigned int  edge_high_thld : 8;  /* bit[8-15] : edge_high_thld should be greater than edge_low_thld */
        unsigned int  reserved       : 16; /* bit[16-31]:  */
    } reg;
} SOC_ISP_RAWNF_ISP_DPF_EDGE_THLD_UNION;
#endif
#define SOC_ISP_RAWNF_ISP_DPF_EDGE_THLD_edge_low_thld_START   (0)
#define SOC_ISP_RAWNF_ISP_DPF_EDGE_THLD_edge_low_thld_END     (7)
#define SOC_ISP_RAWNF_ISP_DPF_EDGE_THLD_edge_high_thld_START  (8)
#define SOC_ISP_RAWNF_ISP_DPF_EDGE_THLD_edge_high_thld_END    (15)


/*****************************************************************************
 结构名    : SOC_ISP_RAWNF_ISP_DPF_DIFF_THLD_UNION
 结构说明  : ISP_DPF_DIFF_THLD 寄存器结构定义。地址偏移量:0x0084，初值:0x00800040，宽度:32
 寄存器说明: Diff Threshold.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  diff_low_thd  : 14; /* bit[0-13] : diff_high_thd should be greater than diff_low_thd */
        unsigned int  reserved_0    : 2;  /* bit[14-15]:  */
        unsigned int  diff_high_thd : 14; /* bit[16-29]: diff_high_thd should be greater than diff_low_thd */
        unsigned int  reserved_1    : 2;  /* bit[30-31]:  */
    } reg;
} SOC_ISP_RAWNF_ISP_DPF_DIFF_THLD_UNION;
#endif
#define SOC_ISP_RAWNF_ISP_DPF_DIFF_THLD_diff_low_thd_START   (0)
#define SOC_ISP_RAWNF_ISP_DPF_DIFF_THLD_diff_low_thd_END     (13)
#define SOC_ISP_RAWNF_ISP_DPF_DIFF_THLD_diff_high_thd_START  (16)
#define SOC_ISP_RAWNF_ISP_DPF_DIFF_THLD_diff_high_thd_END    (29)






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

#endif /* end of soc_isp_rawnf_interface.h */
