/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_isp_blc_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:21:27
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_ISP_BLC.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_ISP_BLC_INTERFACE_H__
#define __SOC_ISP_BLC_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) BLC
 ****************************************************************************/
/* 寄存器说明：global control register
   位域定义UNION结构:  SOC_ISP_BLC_BLS_CTRL_UNION */
#define SOC_ISP_BLC_BLS_CTRL_ADDR(base)               ((base) + (0x0000))

/* 寄存器说明：samples register
   位域定义UNION结构:  SOC_ISP_BLC_BLS_SAMPLES_UNION */
#define SOC_ISP_BLC_BLS_SAMPLES_ADDR(base)            ((base) + (0x0004))

/* 寄存器说明：samples register
   位域定义UNION结构:  SOC_ISP_BLC_BLS_H1_START_UNION */
#define SOC_ISP_BLC_BLS_H1_START_ADDR(base)           ((base) + (0x0008))

/* 寄存器说明：samples register
   位域定义UNION结构:  SOC_ISP_BLC_BLS_H1_STOP_UNION */
#define SOC_ISP_BLC_BLS_H1_STOP_ADDR(base)            ((base) + (0x000C))

/* 寄存器说明：samples register
   位域定义UNION结构:  SOC_ISP_BLC_BLS_V1_START_UNION */
#define SOC_ISP_BLC_BLS_V1_START_ADDR(base)           ((base) + (0x0010))

/* 寄存器说明：samples register
   位域定义UNION结构:  SOC_ISP_BLC_BLS_V1_STOP_UNION */
#define SOC_ISP_BLC_BLS_V1_STOP_ADDR(base)            ((base) + (0x0014))

/* 寄存器说明：samples register
   位域定义UNION结构:  SOC_ISP_BLC_BLS_H2_START_UNION */
#define SOC_ISP_BLC_BLS_H2_START_ADDR(base)           ((base) + (0x0018))

/* 寄存器说明：samples register
   位域定义UNION结构:  SOC_ISP_BLC_BLS_H2_STOP_UNION */
#define SOC_ISP_BLC_BLS_H2_STOP_ADDR(base)            ((base) + (0x001C))

/* 寄存器说明：samples register
   位域定义UNION结构:  SOC_ISP_BLC_BLS_V2_START_UNION */
#define SOC_ISP_BLC_BLS_V2_START_ADDR(base)           ((base) + (0x0020))

/* 寄存器说明：samples register
   位域定义UNION结构:  SOC_ISP_BLC_BLS_V2_STOP_UNION */
#define SOC_ISP_BLC_BLS_V2_STOP_ADDR(base)            ((base) + (0x0024))

/* 寄存器说明：fixed black level A
   位域定义UNION结构:  SOC_ISP_BLC_BLS_A_FIXED_UNION */
#define SOC_ISP_BLC_BLS_A_FIXED_ADDR(base)            ((base) + (0x0028))

/* 寄存器说明：fixed black level B
   位域定义UNION结构:  SOC_ISP_BLC_BLS_B_FIXED_UNION */
#define SOC_ISP_BLC_BLS_B_FIXED_ADDR(base)            ((base) + (0x002C))

/* 寄存器说明：fixed black level C
   位域定义UNION结构:  SOC_ISP_BLC_BLS_C_FIXED_UNION */
#define SOC_ISP_BLC_BLS_C_FIXED_ADDR(base)            ((base) + (0x0030))

/* 寄存器说明：fixed black level D
   位域定义UNION结构:  SOC_ISP_BLC_BLS_D_FIXED_UNION */
#define SOC_ISP_BLC_BLS_D_FIXED_ADDR(base)            ((base) + (0x0034))

/* 寄存器说明：measured black level A
   位域定义UNION结构:  SOC_ISP_BLC_BLS_A_MEASURED_UNION */
#define SOC_ISP_BLC_BLS_A_MEASURED_ADDR(base)         ((base) + (0x0038))

/* 寄存器说明：measured black level B
   位域定义UNION结构:  SOC_ISP_BLC_BLS_B_MEASURED_UNION */
#define SOC_ISP_BLC_BLS_B_MEASURED_ADDR(base)         ((base) + (0x003C))

/* 寄存器说明：measured black level C
   位域定义UNION结构:  SOC_ISP_BLC_BLS_C_MEASURED_UNION */
#define SOC_ISP_BLC_BLS_C_MEASURED_ADDR(base)         ((base) + (0x0040))

/* 寄存器说明：measured black level D
   位域定义UNION结构:  SOC_ISP_BLC_BLS_D_MEASURED_UNION */
#define SOC_ISP_BLC_BLS_D_MEASURED_ADDR(base)         ((base) + (0x0044))





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
                     (1/1) BLC
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_ISP_BLC_BLS_CTRL_UNION
 结构说明  : BLS_CTRL 寄存器结构定义。地址偏移量:0x0000，初值:0x00000000，宽度:32
 寄存器说明: global control register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bls_enable : 1;  /* bit[0]   : 1: black level subtraction is enabled 
                                                     0: bypass the black level processing */
        unsigned int  bls_mode   : 1;  /* bit[1]   : 1: subtract measured values 
                                                     0: subtract fixed values */
        unsigned int  bls_win_en : 2;  /* bit[2-3] : 0: no measuring is performed 
                                                     1: only window 1 is measured 
                                                     2: only window 2 is measured 
                                                     3: both windows are measured */
        unsigned int  reserved   : 28; /* bit[4-31]: Reserved */
    } reg;
} SOC_ISP_BLC_BLS_CTRL_UNION;
#endif
#define SOC_ISP_BLC_BLS_CTRL_bls_enable_START  (0)
#define SOC_ISP_BLC_BLS_CTRL_bls_enable_END    (0)
#define SOC_ISP_BLC_BLS_CTRL_bls_mode_START    (1)
#define SOC_ISP_BLC_BLS_CTRL_bls_mode_END      (1)
#define SOC_ISP_BLC_BLS_CTRL_bls_win_en_START  (2)
#define SOC_ISP_BLC_BLS_CTRL_bls_win_en_END    (3)


/*****************************************************************************
 结构名    : SOC_ISP_BLC_BLS_SAMPLES_UNION
 结构说明  : BLS_SAMPLES 寄存器结构定义。地址偏移量:0x0004，初值:0x00000000，宽度:32
 寄存器说明: samples register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bls_samples : 5;  /* bit[0-4] : This number to the power of two gives the number of measure samples for each Bayer position. Range 0x00: 2^0=1 to 0x12: 2^18=262144. This number is also the divider for the accumulator for each Bayer position. The accumulation will be stopped, if the number of measured pixels for the current Bayer position is equal to the number of samples. 
                                                      The measure windows must be positioned that way that the number of included pixels of each Bayer position included by both windows is equal or greater than the number of measure samples calculated by 2^BLS_SAMPLES ! NOTE: The number of pixels of one Bayer position is 1/4 of the number of all Pixels included by the measure windows.
                                                      0: bypass the black level processing */
        unsigned int  reserved    : 27; /* bit[5-31]: Reserved */
    } reg;
} SOC_ISP_BLC_BLS_SAMPLES_UNION;
#endif
#define SOC_ISP_BLC_BLS_SAMPLES_bls_samples_START  (0)
#define SOC_ISP_BLC_BLS_SAMPLES_bls_samples_END    (4)


/*****************************************************************************
 结构名    : SOC_ISP_BLC_BLS_H1_START_UNION
 结构说明  : BLS_H1_START 寄存器结构定义。地址偏移量:0x0008，初值:0x00000000，宽度:32
 寄存器说明: samples register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bls_h1_start : 14; /* bit[0-13] : Black pixel window 1 horizontal start position */
        unsigned int  reserved     : 18; /* bit[14-31]: Reserved */
    } reg;
} SOC_ISP_BLC_BLS_H1_START_UNION;
#endif
#define SOC_ISP_BLC_BLS_H1_START_bls_h1_start_START  (0)
#define SOC_ISP_BLC_BLS_H1_START_bls_h1_start_END    (13)


/*****************************************************************************
 结构名    : SOC_ISP_BLC_BLS_H1_STOP_UNION
 结构说明  : BLS_H1_STOP 寄存器结构定义。地址偏移量:0x000C，初值:0x00000000，宽度:32
 寄存器说明: samples register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bls_h1_stop : 14; /* bit[0-13] : Black pixel window 1 horizontal stop position */
        unsigned int  reserved    : 18; /* bit[14-31]: Reserved */
    } reg;
} SOC_ISP_BLC_BLS_H1_STOP_UNION;
#endif
#define SOC_ISP_BLC_BLS_H1_STOP_bls_h1_stop_START  (0)
#define SOC_ISP_BLC_BLS_H1_STOP_bls_h1_stop_END    (13)


/*****************************************************************************
 结构名    : SOC_ISP_BLC_BLS_V1_START_UNION
 结构说明  : BLS_V1_START 寄存器结构定义。地址偏移量:0x0010，初值:0x00000000，宽度:32
 寄存器说明: samples register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bls_v1_start : 14; /* bit[0-13] : Black pixel window 1 vertical start position */
        unsigned int  reserved     : 18; /* bit[14-31]: Reserved */
    } reg;
} SOC_ISP_BLC_BLS_V1_START_UNION;
#endif
#define SOC_ISP_BLC_BLS_V1_START_bls_v1_start_START  (0)
#define SOC_ISP_BLC_BLS_V1_START_bls_v1_start_END    (13)


/*****************************************************************************
 结构名    : SOC_ISP_BLC_BLS_V1_STOP_UNION
 结构说明  : BLS_V1_STOP 寄存器结构定义。地址偏移量:0x0014，初值:0x00000000，宽度:32
 寄存器说明: samples register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bls_v1_stop : 14; /* bit[0-13] : Black pixel window 1 verticall stop position */
        unsigned int  reserved    : 18; /* bit[14-31]: Reserved */
    } reg;
} SOC_ISP_BLC_BLS_V1_STOP_UNION;
#endif
#define SOC_ISP_BLC_BLS_V1_STOP_bls_v1_stop_START  (0)
#define SOC_ISP_BLC_BLS_V1_STOP_bls_v1_stop_END    (13)


/*****************************************************************************
 结构名    : SOC_ISP_BLC_BLS_H2_START_UNION
 结构说明  : BLS_H2_START 寄存器结构定义。地址偏移量:0x0018，初值:0x00000000，宽度:32
 寄存器说明: samples register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bls_h2_start : 14; /* bit[0-13] : Black pixel window 2 horizontal start position */
        unsigned int  reserved     : 18; /* bit[14-31]: Reserved */
    } reg;
} SOC_ISP_BLC_BLS_H2_START_UNION;
#endif
#define SOC_ISP_BLC_BLS_H2_START_bls_h2_start_START  (0)
#define SOC_ISP_BLC_BLS_H2_START_bls_h2_start_END    (13)


/*****************************************************************************
 结构名    : SOC_ISP_BLC_BLS_H2_STOP_UNION
 结构说明  : BLS_H2_STOP 寄存器结构定义。地址偏移量:0x001C，初值:0x00000000，宽度:32
 寄存器说明: samples register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bls_h2_stop : 14; /* bit[0-13] : Black pixel window 2 horizontal stop position */
        unsigned int  reserved    : 18; /* bit[14-31]: Reserved */
    } reg;
} SOC_ISP_BLC_BLS_H2_STOP_UNION;
#endif
#define SOC_ISP_BLC_BLS_H2_STOP_bls_h2_stop_START  (0)
#define SOC_ISP_BLC_BLS_H2_STOP_bls_h2_stop_END    (13)


/*****************************************************************************
 结构名    : SOC_ISP_BLC_BLS_V2_START_UNION
 结构说明  : BLS_V2_START 寄存器结构定义。地址偏移量:0x0020，初值:0x00000000，宽度:32
 寄存器说明: samples register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bls_v2_start : 14; /* bit[0-13] : Black pixel window 2 vertical start position */
        unsigned int  reserved     : 18; /* bit[14-31]: Reserved */
    } reg;
} SOC_ISP_BLC_BLS_V2_START_UNION;
#endif
#define SOC_ISP_BLC_BLS_V2_START_bls_v2_start_START  (0)
#define SOC_ISP_BLC_BLS_V2_START_bls_v2_start_END    (13)


/*****************************************************************************
 结构名    : SOC_ISP_BLC_BLS_V2_STOP_UNION
 结构说明  : BLS_V2_STOP 寄存器结构定义。地址偏移量:0x0024，初值:0x00000000，宽度:32
 寄存器说明: samples register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bls_v2_stop : 14; /* bit[0-13] : Black pixel window 2 verticall stop position */
        unsigned int  reserved    : 18; /* bit[14-31]: Reserved */
    } reg;
} SOC_ISP_BLC_BLS_V2_STOP_UNION;
#endif
#define SOC_ISP_BLC_BLS_V2_STOP_bls_v2_stop_START  (0)
#define SOC_ISP_BLC_BLS_V2_STOP_bls_v2_stop_END    (13)


/*****************************************************************************
 结构名    : SOC_ISP_BLC_BLS_A_FIXED_UNION
 结构说明  : BLS_A_FIXED 寄存器结构定义。地址偏移量:0x0028，初值:0x00000000，宽度:32
 寄存器说明: fixed black level A
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bls_a_fixed : 15; /* bit[0-14] : Fixed black level for A pixels – signed two's complement, value range from -4096 to +4095, a positive value will be subtracted from the pixel values */
        unsigned int  reserved    : 17; /* bit[15-31]: Reserved */
    } reg;
} SOC_ISP_BLC_BLS_A_FIXED_UNION;
#endif
#define SOC_ISP_BLC_BLS_A_FIXED_bls_a_fixed_START  (0)
#define SOC_ISP_BLC_BLS_A_FIXED_bls_a_fixed_END    (14)


/*****************************************************************************
 结构名    : SOC_ISP_BLC_BLS_B_FIXED_UNION
 结构说明  : BLS_B_FIXED 寄存器结构定义。地址偏移量:0x002C，初值:0x00000000，宽度:32
 寄存器说明: fixed black level B
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bls_b_fixed : 15; /* bit[0-14] : Fixed black level for B pixels – signed two's complement, value range from -4096 to +4095, a positive value will be subtracted from the pixel values */
        unsigned int  reserved    : 17; /* bit[15-31]: Reserved */
    } reg;
} SOC_ISP_BLC_BLS_B_FIXED_UNION;
#endif
#define SOC_ISP_BLC_BLS_B_FIXED_bls_b_fixed_START  (0)
#define SOC_ISP_BLC_BLS_B_FIXED_bls_b_fixed_END    (14)


/*****************************************************************************
 结构名    : SOC_ISP_BLC_BLS_C_FIXED_UNION
 结构说明  : BLS_C_FIXED 寄存器结构定义。地址偏移量:0x0030，初值:0x00000000，宽度:32
 寄存器说明: fixed black level C
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bls_c_fixed : 15; /* bit[0-14] : Fixed black level for C pixels – signed two's complement, value range from -4096 to +4095, a positive value will be subtracted from the pixel values */
        unsigned int  reserved    : 17; /* bit[15-31]: Reserved */
    } reg;
} SOC_ISP_BLC_BLS_C_FIXED_UNION;
#endif
#define SOC_ISP_BLC_BLS_C_FIXED_bls_c_fixed_START  (0)
#define SOC_ISP_BLC_BLS_C_FIXED_bls_c_fixed_END    (14)


/*****************************************************************************
 结构名    : SOC_ISP_BLC_BLS_D_FIXED_UNION
 结构说明  : BLS_D_FIXED 寄存器结构定义。地址偏移量:0x0034，初值:0x00000000，宽度:32
 寄存器说明: fixed black level D
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bls_d_fixed : 15; /* bit[0-14] : Fixed black level for D pixels – signed two's complement, value range from -4096 to +4095, a positive value will be subtracted from the pixel values */
        unsigned int  reserved    : 17; /* bit[15-31]: Reserved */
    } reg;
} SOC_ISP_BLC_BLS_D_FIXED_UNION;
#endif
#define SOC_ISP_BLC_BLS_D_FIXED_bls_d_fixed_START  (0)
#define SOC_ISP_BLC_BLS_D_FIXED_bls_d_fixed_END    (14)


/*****************************************************************************
 结构名    : SOC_ISP_BLC_BLS_A_MEASURED_UNION
 结构说明  : BLS_A_MEASURED 寄存器结构定义。地址偏移量:0x0038，初值:0x00000000，宽度:32
 寄存器说明: measured black level A
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bls_a_measured : 14; /* bit[0-13] : Measured black level for A pixels */
        unsigned int  reserved       : 18; /* bit[14-31]: Reserved */
    } reg;
} SOC_ISP_BLC_BLS_A_MEASURED_UNION;
#endif
#define SOC_ISP_BLC_BLS_A_MEASURED_bls_a_measured_START  (0)
#define SOC_ISP_BLC_BLS_A_MEASURED_bls_a_measured_END    (13)


/*****************************************************************************
 结构名    : SOC_ISP_BLC_BLS_B_MEASURED_UNION
 结构说明  : BLS_B_MEASURED 寄存器结构定义。地址偏移量:0x003C，初值:0x00000000，宽度:32
 寄存器说明: measured black level B
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bls_b_measured : 14; /* bit[0-13] : Measured black level for B pixels  */
        unsigned int  reserved       : 18; /* bit[14-31]: Reserved */
    } reg;
} SOC_ISP_BLC_BLS_B_MEASURED_UNION;
#endif
#define SOC_ISP_BLC_BLS_B_MEASURED_bls_b_measured_START  (0)
#define SOC_ISP_BLC_BLS_B_MEASURED_bls_b_measured_END    (13)


/*****************************************************************************
 结构名    : SOC_ISP_BLC_BLS_C_MEASURED_UNION
 结构说明  : BLS_C_MEASURED 寄存器结构定义。地址偏移量:0x0040，初值:0x00000000，宽度:32
 寄存器说明: measured black level C
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bls_c_measured : 14; /* bit[0-13] : Measured black level for C pixels  */
        unsigned int  reserved       : 18; /* bit[14-31]: Reserved */
    } reg;
} SOC_ISP_BLC_BLS_C_MEASURED_UNION;
#endif
#define SOC_ISP_BLC_BLS_C_MEASURED_bls_c_measured_START  (0)
#define SOC_ISP_BLC_BLS_C_MEASURED_bls_c_measured_END    (13)


/*****************************************************************************
 结构名    : SOC_ISP_BLC_BLS_D_MEASURED_UNION
 结构说明  : BLS_D_MEASURED 寄存器结构定义。地址偏移量:0x0044，初值:0x00000000，宽度:32
 寄存器说明: measured black level D
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bls_d_measured : 14; /* bit[0-13] : Measured black level for D pixels  */
        unsigned int  reserved       : 18; /* bit[14-31]: Reserved */
    } reg;
} SOC_ISP_BLC_BLS_D_MEASURED_UNION;
#endif
#define SOC_ISP_BLC_BLS_D_MEASURED_bls_d_measured_START  (0)
#define SOC_ISP_BLC_BLS_D_MEASURED_bls_d_measured_END    (13)






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

#endif /* end of soc_isp_blc_interface.h */
