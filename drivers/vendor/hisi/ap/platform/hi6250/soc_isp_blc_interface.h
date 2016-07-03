

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
        unsigned int  reserved_0 : 1;  /* bit[1]   : 1: subtract measured values 
                                                     0: subtract fixed values
                                                     removed the functionality ( BLS always substract fixed value) */
        unsigned int  reserved_1 : 2;  /* bit[2-3] : 0: no measuring is performed 
                                                     1: only window 1 is measured 
                                                     2: only window 2 is measured 
                                                     3: both windows are measured */
        unsigned int  reserved_2 : 28; /* bit[4-31]: Reserved */
    } reg;
} SOC_ISP_BLC_BLS_CTRL_UNION;
#endif
#define SOC_ISP_BLC_BLS_CTRL_bls_enable_START  (0)
#define SOC_ISP_BLC_BLS_CTRL_bls_enable_END    (0)


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
        unsigned int  reserved_0: 5;  /* bit[0-4] : Reserved (This number to the power of two gives the number of measure samples for each Bayer position. Range 0x00: 2^0=1 to 0x12: 2^18=262144. This number is also the divider for the accumulator for each Bayer position. The accumulation will be stopped, if the number of measured pixels for the current Bayer position is equal to the number of samples. 
                                                    The measure windows must be positioned that way that the number of included pixels of each Bayer position included by both windows is equal or greater than the number of measure samples calculated by 2^BLS_SAMPLES ! NOTE: The number of pixels of one Bayer position is 1/4 of the number of all Pixels included by the measure windows.
                                                    0: bypass the black level processing) */
        unsigned int  reserved_1: 27; /* bit[5-31]: Reserved */
    } reg;
} SOC_ISP_BLC_BLS_SAMPLES_UNION;
#endif


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
        unsigned int  reserved_0: 14; /* bit[0-13] : Reserved (Black pixel window 1 horizontal start position) */
        unsigned int  reserved_1: 18; /* bit[14-31]: Reserved */
    } reg;
} SOC_ISP_BLC_BLS_H1_START_UNION;
#endif


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
        unsigned int  reserved_0: 14; /* bit[0-13] : Reserved (Black pixel window 1 horizontal stop position) */
        unsigned int  reserved_1: 18; /* bit[14-31]: Reserved */
    } reg;
} SOC_ISP_BLC_BLS_H1_STOP_UNION;
#endif


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
        unsigned int  reserved_0: 14; /* bit[0-13] : Reserved (Black pixel window 1 vertical start position) */
        unsigned int  reserved_1: 18; /* bit[14-31]: Reserved */
    } reg;
} SOC_ISP_BLC_BLS_V1_START_UNION;
#endif


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
        unsigned int  reserved_0: 14; /* bit[0-13] : Reserved (Black pixel window 1 verticall stop position) */
        unsigned int  reserved_1: 18; /* bit[14-31]: Reserved */
    } reg;
} SOC_ISP_BLC_BLS_V1_STOP_UNION;
#endif


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
        unsigned int  reserved_0: 14; /* bit[0-13] : Reserved (Black pixel window 2 horizontal start position) */
        unsigned int  reserved_1: 18; /* bit[14-31]: Reserved */
    } reg;
} SOC_ISP_BLC_BLS_H2_START_UNION;
#endif


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
        unsigned int  reserved_0: 14; /* bit[0-13] : Reserved (Black pixel window 2 horizontal stop position) */
        unsigned int  reserved_1: 18; /* bit[14-31]: Reserved */
    } reg;
} SOC_ISP_BLC_BLS_H2_STOP_UNION;
#endif


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
        unsigned int  reserved_0: 14; /* bit[0-13] : Reserved (Black pixel window 2 vertical start position) */
        unsigned int  reserved_1: 18; /* bit[14-31]: Reserved */
    } reg;
} SOC_ISP_BLC_BLS_V2_START_UNION;
#endif


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
        unsigned int  reserved_0: 14; /* bit[0-13] : Reserved (Black pixel window 2 verticall stop position) */
        unsigned int  reserved_1: 18; /* bit[14-31]: Reserved */
    } reg;
} SOC_ISP_BLC_BLS_V2_STOP_UNION;
#endif


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
        unsigned int  bls_a_fixed : 15; /* bit[0-14] : Fixed black level for R pixels – signed two's complement, value range from -4096 to +4095, a positive value will be subtracted from the pixel values */
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
        unsigned int  bls_b_fixed : 15; /* bit[0-14] : Fixed black level for Gr pixels – signed two's complement, value range from -4096 to +4095, a positive value will be subtracted from the pixel values */
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
        unsigned int  bls_c_fixed : 15; /* bit[0-14] : Fixed black level for Gb pixels – signed two's complement, value range from -4096 to +4095, a positive value will be subtracted from the pixel values */
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
        unsigned int  bls_d_fixed : 15; /* bit[0-14] : Fixed black level for B pixels – signed two's complement, value range from -4096 to +4095, a positive value will be subtracted from the pixel values */
        unsigned int  reserved    : 17; /* bit[15-31]: Reserved */
    } reg;
} SOC_ISP_BLC_BLS_D_FIXED_UNION;
#endif
#define SOC_ISP_BLC_BLS_D_FIXED_bls_d_fixed_START  (0)
#define SOC_ISP_BLC_BLS_D_FIXED_bls_d_fixed_END    (14)






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
