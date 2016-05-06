/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_isp_cc_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:21:28
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_ISP_CC.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_ISP_CC_INTERFACE_H__
#define __SOC_ISP_CC_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) CC
 ****************************************************************************/
/* 寄存器说明：filter mode configuration
   位域定义UNION结构:  SOC_ISP_CC_CCCFG_UNION */
#define SOC_ISP_CC_CCCFG_ADDR(base)                   ((base) + (0x000))

/* 寄存器说明：reciprocal for bright weight coefficient
   位域定义UNION结构:  SOC_ISP_CC_BRIGHTCOEFF_UNION */
#define SOC_ISP_CC_BRIGHTCOEFF_ADDR(base)             ((base) + (0x004))

/* 寄存器说明：recriprocals for dark weight coefficients
   位域定义UNION结构:  SOC_ISP_CC_DARKCOEFF_UNION */
#define SOC_ISP_CC_DARKCOEFF_ADDR(base)               ((base) + (0x008))

/* 寄存器说明：Coefficients for RGB to Luma conversion
   位域定义UNION结构:  SOC_ISP_CC_RGB2YCOEFF_UNION */
#define SOC_ISP_CC_RGB2YCOEFF_ADDR(base)              ((base) + (0x00C))

/* 寄存器说明：downsampling configuration
   位域定义UNION结构:  SOC_ISP_CC_DWNSAMPLECFG_UNION */
#define SOC_ISP_CC_DWNSAMPLECFG_ADDR(base)            ((base) + (0x010))

/* 寄存器说明：histogram configuration
   位域定义UNION结构:  SOC_ISP_CC_HISTCFG_UNION */
#define SOC_ISP_CC_HISTCFG_ADDR(base)                 ((base) + (0x014))

/* 寄存器说明：threshold configuration
   位域定义UNION结构:  SOC_ISP_CC_THRESA_UNION */
#define SOC_ISP_CC_THRESA_ADDR(base)                  ((base) + (0x018))

/* 寄存器说明：threshold configuration
   位域定义UNION结构:  SOC_ISP_CC_THRESB_UNION */
#define SOC_ISP_CC_THRESB_ADDR(base)                  ((base) + (0x01C))

/* 寄存器说明：threshold configuration
   位域定义UNION结构:  SOC_ISP_CC_THRESC_UNION */
#define SOC_ISP_CC_THRESC_ADDR(base)                  ((base) + (0x020))

/* 寄存器说明：SW Matrix configuration
   位域定义UNION结构:  SOC_ISP_CC_CCMATRIXA0_UNION */
#define SOC_ISP_CC_CCMATRIXA0_ADDR(base)              ((base) + (0x024))

/* 寄存器说明：SW Matrix configuration
   位域定义UNION结构:  SOC_ISP_CC_CCMATRIXA1_UNION */
#define SOC_ISP_CC_CCMATRIXA1_ADDR(base)              ((base) + (0x028))

/* 寄存器说明：SW Matrix configuration
   位域定义UNION结构:  SOC_ISP_CC_CCMATRIXA2_UNION */
#define SOC_ISP_CC_CCMATRIXA2_ADDR(base)              ((base) + (0x02C))

/* 寄存器说明：SW Matrix configuration
   位域定义UNION结构:  SOC_ISP_CC_CCMATRIXA3_UNION */
#define SOC_ISP_CC_CCMATRIXA3_ADDR(base)              ((base) + (0x030))

/* 寄存器说明：SW Matrix configuration
   位域定义UNION结构:  SOC_ISP_CC_CCMATRIXA4_UNION */
#define SOC_ISP_CC_CCMATRIXA4_ADDR(base)              ((base) + (0x034))

/* 寄存器说明：SW Matrix configuration
   位域定义UNION结构:  SOC_ISP_CC_CCMATRIXA5_UNION */
#define SOC_ISP_CC_CCMATRIXA5_ADDR(base)              ((base) + (0x038))

/* 寄存器说明：histogram window configuration
   位域定义UNION结构:  SOC_ISP_CC_CROP_HIST_UNION */
#define SOC_ISP_CC_CROP_HIST_ADDR(base)               ((base) + (0x03C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_CC_HIST_ENABLE_UNION */
#define SOC_ISP_CC_HIST_ENABLE_ADDR(base)             ((base) + (0x0040))

/* 寄存器说明：Coefficient value of pixel's correct Y
   位域定义UNION结构:  SOC_ISP_CC_PIX_YCOEF_UNION */
#define SOC_ISP_CC_PIX_YCOEF_ADDR(base)               ((base) + (0x0044))

/* 寄存器说明：Histogram statistic
   位域定义UNION结构:  SOC_ISP_CC_STAT_HIST_UNION */
#define SOC_ISP_CC_STAT_HIST_ADDR(base, StatRange)    ((base) + (0x100+0x4*(StatRange)))





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
                     (1/1) CC
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_ISP_CC_CCCFG_UNION
 结构说明  : CCCFG 寄存器结构定义。地址偏移量:0x000，初值:0x00000000，宽度:32
 寄存器说明: filter mode configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bimplementcc : 1;  /* bit[0-0] : Color Correct enable- The bit is taken into account when the CC is not processing a frame (similar to shadowed) 
                                                       0: Color correct is disabled
                                                       1: Color correct is enabled */
        unsigned int  bpixyconst   : 1;  /* bit[1-1] : Pixel Y Constant enable- The bit is taken into account when the CC is not processing a frame (similar to shadowed) 
                                                       0: is disabled
                                                       1: is enabled */
        unsigned int  reserved     : 30; /* bit[2-31]:  */
    } reg;
} SOC_ISP_CC_CCCFG_UNION;
#endif
#define SOC_ISP_CC_CCCFG_bimplementcc_START  (0)
#define SOC_ISP_CC_CCCFG_bimplementcc_END    (0)
#define SOC_ISP_CC_CCCFG_bpixyconst_START    (1)
#define SOC_ISP_CC_CCCFG_bpixyconst_END      (1)


/*****************************************************************************
 结构名    : SOC_ISP_CC_BRIGHTCOEFF_UNION
 结构说明  : BRIGHTCOEFF 寄存器结构定义。地址偏移量:0x004，初值:0x00000000，宽度:32
 寄存器说明: reciprocal for bright weight coefficient
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  brightcoeffab : 15; /* bit[0-14] : Reciprocal for bright weight coefficient between AB u0.15
                                                         brightcoeffab=CC_brightCoefKab
                                                         brightcoeffab=1/(brightthres_1-brightthres_0) */
        unsigned int  reserved_0    : 1;  /* bit[15-15]:  */
        unsigned int  brightcoeffbc : 15; /* bit[16-30]: Reciprocal for bright weight coefficient between BC u0.15
                                                         brightcoeffbc=CC_brightCoefKbc
                                                         brightcoeffbc=1/(brightthres_2-brightthres_1) */
        unsigned int  reserved_1    : 1;  /* bit[31-31]:  */
    } reg;
} SOC_ISP_CC_BRIGHTCOEFF_UNION;
#endif
#define SOC_ISP_CC_BRIGHTCOEFF_brightcoeffab_START  (0)
#define SOC_ISP_CC_BRIGHTCOEFF_brightcoeffab_END    (14)
#define SOC_ISP_CC_BRIGHTCOEFF_brightcoeffbc_START  (16)
#define SOC_ISP_CC_BRIGHTCOEFF_brightcoeffbc_END    (30)


/*****************************************************************************
 结构名    : SOC_ISP_CC_DARKCOEFF_UNION
 结构说明  : DARKCOEFF 寄存器结构定义。地址偏移量:0x008，初值:0x00000000，宽度:32
 寄存器说明: recriprocals for dark weight coefficients
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  darkcoeffab : 15; /* bit[0-14] : Reciprocal for dark coefficient between AB u0.15
                                                       darkcoeffab= CC_darkCoefKab
                                                       darkcoeffab=1/(darkthres_0-darkthres_1) */
        unsigned int  reserved_0  : 1;  /* bit[15-15]:  */
        unsigned int  darkcoeffbc : 15; /* bit[16-30]: Reciprocal for dark coefficient between BC u0.15
                                                       darkcoeffbc= CC_darkCoefKbc
                                                       darkcoeffbc=1/(darkthres_1-darkthres_2) */
        unsigned int  reserved_1  : 1;  /* bit[31-31]:  */
    } reg;
} SOC_ISP_CC_DARKCOEFF_UNION;
#endif
#define SOC_ISP_CC_DARKCOEFF_darkcoeffab_START  (0)
#define SOC_ISP_CC_DARKCOEFF_darkcoeffab_END    (14)
#define SOC_ISP_CC_DARKCOEFF_darkcoeffbc_START  (16)
#define SOC_ISP_CC_DARKCOEFF_darkcoeffbc_END    (30)


/*****************************************************************************
 结构名    : SOC_ISP_CC_RGB2YCOEFF_UNION
 结构说明  : RGB2YCOEFF 寄存器结构定义。地址偏移量:0x00C，初值:0x00000000，宽度:32
 寄存器说明: Coefficients for RGB to Luma conversion
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rgb2ycoeff0 : 9;  /* bit[0-8]  : Coefficient for RGB to Luma conversion with R u9.0
                                                       rgb2Ycoeff0=rgb2Ycoeff[0]
                                                       [0,0x100] */
        unsigned int  rgb2ycoeff1 : 9;  /* bit[9-17] : Coefficient for RGB to Luma conversion with G u9.0
                                                       rgb2Ycoeff1=rgb2Ycoeff[1]
                                                       [0,0x100] */
        unsigned int  rgb2ycoeff2 : 9;  /* bit[18-26]: Coefficient for RGB to Luma conversion with B u9.0 
                                                       rgb2Ycoeff2=rgb2Ycoeff[2]
                                                       [0,0x100] */
        unsigned int  reserved    : 5;  /* bit[27-31]:  */
    } reg;
} SOC_ISP_CC_RGB2YCOEFF_UNION;
#endif
#define SOC_ISP_CC_RGB2YCOEFF_rgb2ycoeff0_START  (0)
#define SOC_ISP_CC_RGB2YCOEFF_rgb2ycoeff0_END    (8)
#define SOC_ISP_CC_RGB2YCOEFF_rgb2ycoeff1_START  (9)
#define SOC_ISP_CC_RGB2YCOEFF_rgb2ycoeff1_END    (17)
#define SOC_ISP_CC_RGB2YCOEFF_rgb2ycoeff2_START  (18)
#define SOC_ISP_CC_RGB2YCOEFF_rgb2ycoeff2_END    (26)


/*****************************************************************************
 结构名    : SOC_ISP_CC_DWNSAMPLECFG_UNION
 结构说明  : DWNSAMPLECFG 寄存器结构定义。地址偏移量:0x010，初值:0x00000000，宽度:32
 寄存器说明: downsampling configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  factorx  : 4;  /* bit[0-3] : Downsample row for histogram
                                                   u4.0
                                                   factorx=downSampleFactorX
                                                   0,1 : 1 pixel out of 2 is used for histogram generation
                                                   N : 1 pixel out of N+1 is used for histogram generation */
        unsigned int  factory  : 4;  /* bit[4-7] : Downsample column for histogram
                                                   u4.0
                                                   factory=downSampleFactorY
                                                   0,1 : 1 line out of two is used for histogram generation
                                                   N : 1 line out of N+1 is for used for histogram generation */
        unsigned int  reserved : 24; /* bit[8-31]:  */
    } reg;
} SOC_ISP_CC_DWNSAMPLECFG_UNION;
#endif
#define SOC_ISP_CC_DWNSAMPLECFG_factorx_START   (0)
#define SOC_ISP_CC_DWNSAMPLECFG_factorx_END     (3)
#define SOC_ISP_CC_DWNSAMPLECFG_factory_START   (4)
#define SOC_ISP_CC_DWNSAMPLECFG_factory_END     (7)


/*****************************************************************************
 结构名    : SOC_ISP_CC_HISTCFG_UNION
 结构说明  : HISTCFG 寄存器结构定义。地址偏移量:0x014，初值:0x00000000，宽度:32
 寄存器说明: histogram configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  histshiftbit : 4;  /* bit[0-3]  : shift pixel value to get sparse histogram u4.0
                                                        histshiftbit=histShiftBit */
        unsigned int  histminvalue : 14; /* bit[4-17] : base min value for histogram. Minimum value must allow at least 64 bin u14.0
                                                        histminvalue=histMinValue */
        unsigned int  reserved     : 14; /* bit[18-31]: high-band sharpen strength threhold Qu8.0 */
    } reg;
} SOC_ISP_CC_HISTCFG_UNION;
#endif
#define SOC_ISP_CC_HISTCFG_histshiftbit_START  (0)
#define SOC_ISP_CC_HISTCFG_histshiftbit_END    (3)
#define SOC_ISP_CC_HISTCFG_histminvalue_START  (4)
#define SOC_ISP_CC_HISTCFG_histminvalue_END    (17)


/*****************************************************************************
 结构名    : SOC_ISP_CC_THRESA_UNION
 结构说明  : THRESA 寄存器结构定义。地址偏移量:0x018，初值:0x00000000，宽度:32
 寄存器说明: threshold configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  brightthres_0 : 12; /* bit[0-11] : Bright pixel desaturation threshold u12.0
                                                         brightthres_0=brightThres[0]
                                                         darthres_0<brightthres_0=<brightthres_1 */
        unsigned int  reserved_0    : 4;  /* bit[12-15]:  */
        unsigned int  brightthres_1 : 12; /* bit[16-27]: Bright pixel desaturation threshold u12.0
                                                         brightthres_1=brightThres[1]
                                                         brightthres_0=<brightthres_1<=brightthres_2 */
        unsigned int  reserved_1    : 4;  /* bit[28-31]:  */
    } reg;
} SOC_ISP_CC_THRESA_UNION;
#endif
#define SOC_ISP_CC_THRESA_brightthres_0_START  (0)
#define SOC_ISP_CC_THRESA_brightthres_0_END    (11)
#define SOC_ISP_CC_THRESA_brightthres_1_START  (16)
#define SOC_ISP_CC_THRESA_brightthres_1_END    (27)


/*****************************************************************************
 结构名    : SOC_ISP_CC_THRESB_UNION
 结构说明  : THRESB 寄存器结构定义。地址偏移量:0x01C，初值:0x00000000，宽度:32
 寄存器说明: threshold configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  darthres_0  : 12; /* bit[0-11] : dark pixel desaturation threshold u12.0
                                                       darkthres_0=darkThres[0]
                                                       darkthres_1<=darthres_0<brightthres_0 */
        unsigned int  reserved_0  : 4;  /* bit[12-15]:  */
        unsigned int  darkthres_1 : 12; /* bit[16-27]: dark pixel desaturation threshold u12.0
                                                       darkthres_1=darkThres[1]
                                                       darkthres_2=<darkthres_1<=darthres_0 */
        unsigned int  reserved_1  : 4;  /* bit[28-31]:  */
    } reg;
} SOC_ISP_CC_THRESB_UNION;
#endif
#define SOC_ISP_CC_THRESB_darthres_0_START   (0)
#define SOC_ISP_CC_THRESB_darthres_0_END     (11)
#define SOC_ISP_CC_THRESB_darkthres_1_START  (16)
#define SOC_ISP_CC_THRESB_darkthres_1_END    (27)


/*****************************************************************************
 结构名    : SOC_ISP_CC_THRESC_UNION
 结构说明  : THRESC 寄存器结构定义。地址偏移量:0x020，初值:0x00000000，宽度:32
 寄存器说明: threshold configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  brightthres_2 : 12; /* bit[0-11] : Bright pixel desaturation threshold u12.0
                                                         brightthres_2=brightThres[2]
                                                         brightthres_1<=brightthres_2 */
        unsigned int  reserved_0    : 4;  /* bit[12-15]:  */
        unsigned int  darkthres_2   : 12; /* bit[16-27]: dark pixel desaturation threshold u12.0
                                                         darkthres_1=darkThres[1]
                                                         darkthres_2=<darkthres_1 */
        unsigned int  reserved_1    : 4;  /* bit[28-31]:  */
    } reg;
} SOC_ISP_CC_THRESC_UNION;
#endif
#define SOC_ISP_CC_THRESC_brightthres_2_START  (0)
#define SOC_ISP_CC_THRESC_brightthres_2_END    (11)
#define SOC_ISP_CC_THRESC_darkthres_2_START    (16)
#define SOC_ISP_CC_THRESC_darkthres_2_END      (27)


/*****************************************************************************
 结构名    : SOC_ISP_CC_CCMATRIXA0_UNION
 结构说明  : CCMATRIXA0 寄存器结构定义。地址偏移量:0x024，初值:0x00000000，宽度:32
 寄存器说明: SW Matrix configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coeff0   : 14; /* bit[0-13] : Matrix coefficient Qs4.10
                                                    coeff0=colorCorrectMatA[0] */
        unsigned int  reserved_0: 2;  /* bit[14-15]:  */
        unsigned int  coeff1   : 14; /* bit[16-29]: Matrix coefficient Qs4.10
                                                    coeff1=colorCorrectMatA[1] */
        unsigned int  reserved_1: 2;  /* bit[30-31]:  */
    } reg;
} SOC_ISP_CC_CCMATRIXA0_UNION;
#endif
#define SOC_ISP_CC_CCMATRIXA0_coeff0_START    (0)
#define SOC_ISP_CC_CCMATRIXA0_coeff0_END      (13)
#define SOC_ISP_CC_CCMATRIXA0_coeff1_START    (16)
#define SOC_ISP_CC_CCMATRIXA0_coeff1_END      (29)


/*****************************************************************************
 结构名    : SOC_ISP_CC_CCMATRIXA1_UNION
 结构说明  : CCMATRIXA1 寄存器结构定义。地址偏移量:0x028，初值:0x00000000，宽度:32
 寄存器说明: SW Matrix configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coeff2   : 14; /* bit[0-13] : Matrix coefficient Qs4.10
                                                    coeff2=colorCorrectMatA[2] */
        unsigned int  reserved_0: 2;  /* bit[14-15]:  */
        unsigned int  coeff3   : 14; /* bit[16-29]: Matrix coefficient Qs4.10
                                                    coeff3=colorCorrectMatA[3] */
        unsigned int  reserved_1: 2;  /* bit[30-31]:  */
    } reg;
} SOC_ISP_CC_CCMATRIXA1_UNION;
#endif
#define SOC_ISP_CC_CCMATRIXA1_coeff2_START    (0)
#define SOC_ISP_CC_CCMATRIXA1_coeff2_END      (13)
#define SOC_ISP_CC_CCMATRIXA1_coeff3_START    (16)
#define SOC_ISP_CC_CCMATRIXA1_coeff3_END      (29)


/*****************************************************************************
 结构名    : SOC_ISP_CC_CCMATRIXA2_UNION
 结构说明  : CCMATRIXA2 寄存器结构定义。地址偏移量:0x02C，初值:0x00000000，宽度:32
 寄存器说明: SW Matrix configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coeff4   : 14; /* bit[0-13] : Matrix coefficient Qs4.10
                                                    coeff4=colorCorrectMatA[4] */
        unsigned int  reserved_0: 2;  /* bit[14-15]:  */
        unsigned int  coeff5   : 14; /* bit[16-29]: Matrix coefficient Qs4.10
                                                    coeff5=colorCorrectMatA[5] */
        unsigned int  reserved_1: 2;  /* bit[30-31]:  */
    } reg;
} SOC_ISP_CC_CCMATRIXA2_UNION;
#endif
#define SOC_ISP_CC_CCMATRIXA2_coeff4_START    (0)
#define SOC_ISP_CC_CCMATRIXA2_coeff4_END      (13)
#define SOC_ISP_CC_CCMATRIXA2_coeff5_START    (16)
#define SOC_ISP_CC_CCMATRIXA2_coeff5_END      (29)


/*****************************************************************************
 结构名    : SOC_ISP_CC_CCMATRIXA3_UNION
 结构说明  : CCMATRIXA3 寄存器结构定义。地址偏移量:0x030，初值:0x00000000，宽度:32
 寄存器说明: SW Matrix configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coeff6   : 14; /* bit[0-13] : Matrix coefficient Qs4.10
                                                    coeff6=colorCorrectMatA[6] */
        unsigned int  reserved_0: 2;  /* bit[14-15]:  */
        unsigned int  coeff7   : 14; /* bit[16-29]: Matrix coefficient Qs4.10
                                                    coeff7=colorCorrectMatA[7] */
        unsigned int  reserved_1: 2;  /* bit[30-31]:  */
    } reg;
} SOC_ISP_CC_CCMATRIXA3_UNION;
#endif
#define SOC_ISP_CC_CCMATRIXA3_coeff6_START    (0)
#define SOC_ISP_CC_CCMATRIXA3_coeff6_END      (13)
#define SOC_ISP_CC_CCMATRIXA3_coeff7_START    (16)
#define SOC_ISP_CC_CCMATRIXA3_coeff7_END      (29)


/*****************************************************************************
 结构名    : SOC_ISP_CC_CCMATRIXA4_UNION
 结构说明  : CCMATRIXA4 寄存器结构定义。地址偏移量:0x034，初值:0x00000000，宽度:32
 寄存器说明: SW Matrix configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coeff8   : 14; /* bit[0-13] : Matrix coefficient Qs4.10
                                                    coeff8=colorCorrectMatA[8] */
        unsigned int  reserved_0: 2;  /* bit[14-15]:  */
        unsigned int  coeff9   : 14; /* bit[16-29]: Matrix coefficient Qs4.10
                                                    coeff9=colorCorrectMatA[9] */
        unsigned int  reserved_1: 2;  /* bit[30-31]:  */
    } reg;
} SOC_ISP_CC_CCMATRIXA4_UNION;
#endif
#define SOC_ISP_CC_CCMATRIXA4_coeff8_START    (0)
#define SOC_ISP_CC_CCMATRIXA4_coeff8_END      (13)
#define SOC_ISP_CC_CCMATRIXA4_coeff9_START    (16)
#define SOC_ISP_CC_CCMATRIXA4_coeff9_END      (29)


/*****************************************************************************
 结构名    : SOC_ISP_CC_CCMATRIXA5_UNION
 结构说明  : CCMATRIXA5 寄存器结构定义。地址偏移量:0x038，初值:0x00000000，宽度:32
 寄存器说明: SW Matrix configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coeff10  : 14; /* bit[0-13] : Matrix coefficient Qs14.0
                                                    coeff10=colorCorrectMatA[10] */
        unsigned int  reserved_0: 2;  /* bit[14-15]:  */
        unsigned int  coeff11  : 14; /* bit[16-29]: Matrix coefficient Qs14.0
                                                    coeff11=colorCorrectMatA[11] */
        unsigned int  reserved_1: 2;  /* bit[30-31]:  */
    } reg;
} SOC_ISP_CC_CCMATRIXA5_UNION;
#endif
#define SOC_ISP_CC_CCMATRIXA5_coeff10_START   (0)
#define SOC_ISP_CC_CCMATRIXA5_coeff10_END     (13)
#define SOC_ISP_CC_CCMATRIXA5_coeff11_START   (16)
#define SOC_ISP_CC_CCMATRIXA5_coeff11_END     (29)


/*****************************************************************************
 结构名    : SOC_ISP_CC_CROP_HIST_UNION
 结构说明  : CROP_HIST 寄存器结构定义。地址偏移量:0x03C，初值:0x00000000，宽度:32
 寄存器说明: histogram window configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ihleft_hist  : 13; /* bit[0-12] : Position of first pixel used for histogram generation u13.0:
                                                        0: first pixel
                                                        1: second pixel
                                                        2: 3th pixel
                                                        N: N+1 pixel
                                                        ihleft_hist<ihright_hist */
        unsigned int  reserved_0   : 3;  /* bit[13-15]:  */
        unsigned int  ihright_hist : 13; /* bit[16-28]: Position of last pixel used for histogram generation u13.0, 0x1FFF means no crop:
                                                        0: first pixel
                                                        1: second pixel
                                                        2: pixel
                                                        N: N+1 pixels 
                                                        ihleft_hist<ihright_hist */
        unsigned int  reserved_1   : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_CC_CROP_HIST_UNION;
#endif
#define SOC_ISP_CC_CROP_HIST_ihleft_hist_START   (0)
#define SOC_ISP_CC_CROP_HIST_ihleft_hist_END     (12)
#define SOC_ISP_CC_CROP_HIST_ihright_hist_START  (16)
#define SOC_ISP_CC_CROP_HIST_ihright_hist_END    (28)


/*****************************************************************************
 结构名    : SOC_ISP_CC_HIST_ENABLE_UNION
 结构说明  : HIST_ENABLE 寄存器结构定义。地址偏移量:0x0040，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hist_enable : 1;  /* bit[0-0] : Histogramm enable- It is taken into account by HW upon SOF and cleared by HW after histogram is done
                                                      0: histogram is disabled
                                                      1: histogram is enabled  */
        unsigned int  reserved    : 31; /* bit[1-31]:  */
    } reg;
} SOC_ISP_CC_HIST_ENABLE_UNION;
#endif
#define SOC_ISP_CC_HIST_ENABLE_hist_enable_START  (0)
#define SOC_ISP_CC_HIST_ENABLE_hist_enable_END    (0)


/*****************************************************************************
 结构名    : SOC_ISP_CC_PIX_YCOEF_UNION
 结构说明  : PIX_YCOEF 寄存器结构定义。地址偏移量:0x0044，初值:0x00000000，宽度:32
 寄存器说明: Coefficient value of pixel's correct Y
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pix_ycoef_val : 6;  /* bit[0-5] : Coefficient value of pixel's correct Y u6.0  */
        unsigned int  reserved      : 26; /* bit[6-31]:  */
    } reg;
} SOC_ISP_CC_PIX_YCOEF_UNION;
#endif
#define SOC_ISP_CC_PIX_YCOEF_pix_ycoef_val_START  (0)
#define SOC_ISP_CC_PIX_YCOEF_pix_ycoef_val_END    (5)


/*****************************************************************************
 结构名    : SOC_ISP_CC_STAT_HIST_UNION
 结构说明  : STAT_HIST 寄存器结构定义。地址偏移量:0x100+0x4*(StatRange)，初值:0x00000000，宽度:32
 寄存器说明: Histogram statistic
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stat     : 20; /* bit[0-19] : represents the pHist information 64 words of u20.0 */
        unsigned int  reserved : 12; /* bit[20-31]:  */
    } reg;
} SOC_ISP_CC_STAT_HIST_UNION;
#endif
#define SOC_ISP_CC_STAT_HIST_stat_START      (0)
#define SOC_ISP_CC_STAT_HIST_stat_END        (19)






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

#endif /* end of soc_isp_cc_interface.h */
