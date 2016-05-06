/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_isp_bas_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:21:25
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_ISP_BAS.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_ISP_BAS_INTERFACE_H__
#define __SOC_ISP_BAS_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) BAS
 ****************************************************************************/
/* 寄存器说明：working mode
   位域定义UNION结构:  SOC_ISP_BAS_BAS_MODE_UNION */
#define SOC_ISP_BAS_BAS_MODE_ADDR(base)               ((base) + (0x0000))

/* 寄存器说明：H first pixel
   位域定义UNION结构:  SOC_ISP_BAS_BAS_IHLEFT_UNION */
#define SOC_ISP_BAS_BAS_IHLEFT_ADDR(base)             ((base) + (0x0004))

/* 寄存器说明：H Last  pixel
   位域定义UNION结构:  SOC_ISP_BAS_BAS_IHRIGHT_UNION */
#define SOC_ISP_BAS_BAS_IHRIGHT_ADDR(base)            ((base) + (0x0008))

/* 寄存器说明：V first line
   位域定义UNION结构:  SOC_ISP_BAS_BAS_IVTOP_UNION */
#define SOC_ISP_BAS_BAS_IVTOP_ADDR(base)              ((base) + (0x000C))

/* 寄存器说明：V last line
   位域定义UNION结构:  SOC_ISP_BAS_BAS_IVBOTTOM_UNION */
#define SOC_ISP_BAS_BAS_IVBOTTOM_ADDR(base)           ((base) + (0x0010))

/* 寄存器说明：H Inc
   位域定义UNION结构:  SOC_ISP_BAS_BAS_IHINC_UNION */
#define SOC_ISP_BAS_BAS_IHINC_ADDR(base)              ((base) + (0x0014))

/* 寄存器说明：V Inc
   位域定义UNION结构:  SOC_ISP_BAS_BAS_IVINC_UNION */
#define SOC_ISP_BAS_BAS_IVINC_ADDR(base)              ((base) + (0x0018))

/* 寄存器说明：coef table select
   位域定义UNION结构:  SOC_ISP_BAS_BAS_COEF_ACTIVE_UNION */
#define SOC_ISP_BAS_BAS_COEF_ACTIVE_ADDR(base)        ((base) + (0x001C))

/* 寄存器说明：horizontal coefficient table
   位域定义UNION结构:  SOC_ISP_BAS_BAS_H_COEF_0_UNION */
#define SOC_ISP_BAS_BAS_H_COEF_0_ADDR(base, TAP6)     ((base) + (0x0100+0x4*(TAP6)))

/* 寄存器说明：horizontal coefficient table
   位域定义UNION结构:  SOC_ISP_BAS_BAS_H_COEF_1_UNION */
#define SOC_ISP_BAS_BAS_H_COEF_1_ADDR(base, TAP6)     ((base) + (0x0200+0x4*(TAP6)))

/* 寄存器说明：vertical 4tap coefficient table
   位域定义UNION结构:  SOC_ISP_BAS_BAS_V4TAP_COEF_0_UNION */
#define SOC_ISP_BAS_BAS_V4TAP_COEF_0_ADDR(base, TAP4)  ((base) + (0x0300+0x4*(TAP4)))

/* 寄存器说明：vertical 4tap coefficient table
   位域定义UNION结构:  SOC_ISP_BAS_BAS_V4TAP_COEF_1_UNION */
#define SOC_ISP_BAS_BAS_V4TAP_COEF_1_ADDR(base, TAP4)  ((base) + (0x0400+0x4*(TAP4)))

/* 寄存器说明：vertical 6tap coefficient table
   位域定义UNION结构:  SOC_ISP_BAS_BAS_V6TAP_COEF_0_UNION */
#define SOC_ISP_BAS_BAS_V6TAP_COEF_0_ADDR(base, TAP6)  ((base) + (0x0500+0x4*(TAP6)))

/* 寄存器说明：vertical 6tap coefficient table
   位域定义UNION结构:  SOC_ISP_BAS_BAS_V6TAP_COEF_1_UNION */
#define SOC_ISP_BAS_BAS_V6TAP_COEF_1_ADDR(base, TAP6)  ((base) + (0x0600+0x4*(TAP6)))





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
                     (1/1) BAS
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_ISP_BAS_BAS_MODE_UNION
 结构说明  : BAS_MODE 寄存器结构定义。地址偏移量:0x0000，初值:0x00000000，宽度:32
 寄存器说明: working mode
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode         : 2;  /* bit[0-1] : 00:bypass
                                                       01:down scale
                                                       10:1/2 phase correction (don't support crop)
                                                       11:reserved */
        unsigned int  v_filter_sel : 1;  /* bit[2]   : 0: R/B 2 tap; G 4 tap
                                                       1: R/B 4 tap; G 6 tap */
        unsigned int  reserved     : 29; /* bit[3-31]:  */
    } reg;
} SOC_ISP_BAS_BAS_MODE_UNION;
#endif
#define SOC_ISP_BAS_BAS_MODE_mode_START          (0)
#define SOC_ISP_BAS_BAS_MODE_mode_END            (1)
#define SOC_ISP_BAS_BAS_MODE_v_filter_sel_START  (2)
#define SOC_ISP_BAS_BAS_MODE_v_filter_sel_END    (2)


/*****************************************************************************
 结构名    : SOC_ISP_BAS_BAS_IHLEFT_UNION
 结构说明  : BAS_IHLEFT 寄存器结构定义。地址偏移量:0x0004，初值:0x00000000，宽度:32
 寄存器说明: H first pixel
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ihleft : 32; /* bit[0-31]: Position of first pixel in active area. Qu14.18 ( Qu n.m )
                                                 0:first pixel in input stream (n=0 , m=0 )
                                                 0x20000: first half pixel (n= 0, m=0.5)
                                                 0x40000:second pixel in input stream (n=1, m=0)
                                                 n.m :(n+1),m th pixel in input stream 
                                                 binning phase correction mode doesn't support crop, so this field must be 0x0 */
    } reg;
} SOC_ISP_BAS_BAS_IHLEFT_UNION;
#endif
#define SOC_ISP_BAS_BAS_IHLEFT_ihleft_START  (0)
#define SOC_ISP_BAS_BAS_IHLEFT_ihleft_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_BAS_BAS_IHRIGHT_UNION
 结构说明  : BAS_IHRIGHT 寄存器结构定义。地址偏移量:0x0008，初值:0x00000000，宽度:32
 寄存器说明: H Last  pixel
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ihright : 32; /* bit[0-31]: Position of last pixel in active area. Qu14.18 (Qu n.m )
                                                  0xFFFF_FFFF means no crop
                                                  , using this configuration requires ((ihsize-1)<<18 - ihleft)=hinc*N, N is integer.
                                                  For correct rescaling we should have ihright = ihleft+hinc*( ohsize-1):
                                                  0:first pixel in input stream (n=0, m=0)
                                                  0x20000: first half pixel (n=0,m=0,5)
                                                  0x40000:second pixel in input stream
                                                  n.m:(n+1),m th pixel in input stream */
    } reg;
} SOC_ISP_BAS_BAS_IHRIGHT_UNION;
#endif
#define SOC_ISP_BAS_BAS_IHRIGHT_ihright_START  (0)
#define SOC_ISP_BAS_BAS_IHRIGHT_ihright_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_BAS_BAS_IVTOP_UNION
 结构说明  : BAS_IVTOP 寄存器结构定义。地址偏移量:0x000C，初值:0x00000000，宽度:32
 寄存器说明: V first line
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ivtop : 32; /* bit[0-31]: Position of first line in active area. Qu14.18
                                                0:first line in input stream (n=0 , m=0 )
                                                0x20000: first half line (n= 0, m=0,5)
                                                0x40000:second line in input stream (n=1, m=0)
                                                n.m :(n+1),m th line in input stream 
                                                binning phase correction mode doesn't support crop, so this field must be 0x0 */
    } reg;
} SOC_ISP_BAS_BAS_IVTOP_UNION;
#endif
#define SOC_ISP_BAS_BAS_IVTOP_ivtop_START  (0)
#define SOC_ISP_BAS_BAS_IVTOP_ivtop_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_BAS_BAS_IVBOTTOM_UNION
 结构说明  : BAS_IVBOTTOM 寄存器结构定义。地址偏移量:0x0010，初值:0x00000000，宽度:32
 寄存器说明: V last line
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ivbottom : 32; /* bit[0-31]: Position of last line in active area. Qu14.18
                                                   0xFFFF_FFFF means no crop, using this configuration requires ((ivsize-1)<<18 - ivtop)=vinc*N,N is integer.
                                                   otherwise. For correct rescaling we should have ivbottom=ivtop+vinc(ovsize-1):
                                                   0:first line in input stream (n=0, m=0)
                                                   0x20000: first half line (n=0,m=0,5)
                                                   0x40000:second line in input stream
                                                   n.m:(n+1),m th line in input stream */
    } reg;
} SOC_ISP_BAS_BAS_IVBOTTOM_UNION;
#endif
#define SOC_ISP_BAS_BAS_IVBOTTOM_ivbottom_START  (0)
#define SOC_ISP_BAS_BAS_IVBOTTOM_ivbottom_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_BAS_BAS_IHINC_UNION
 结构说明  : BAS_IHINC 寄存器结构定义。地址偏移量:0x0014，初值:0x00040000，宽度:32
 寄存器说明: H Inc
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ihinc    : 22; /* bit[0-21] : Horizontal increment (Qu4.18) 
                                                    Ratio= Input Size/output Size.
                                                    IHINC = 2^18 * ratio
                                                    0x40000 means ratio 1
                                                    0x80000 means downscaling by 2 and ratio=2
                                                    upscaling not support, this fieild must >=0x40000
                                                    in binning phase correction mode, this field must be 0x40000 */
        unsigned int  reserved : 10; /* bit[22-31]:  */
    } reg;
} SOC_ISP_BAS_BAS_IHINC_UNION;
#endif
#define SOC_ISP_BAS_BAS_IHINC_ihinc_START     (0)
#define SOC_ISP_BAS_BAS_IHINC_ihinc_END       (21)


/*****************************************************************************
 结构名    : SOC_ISP_BAS_BAS_IVINC_UNION
 结构说明  : BAS_IVINC 寄存器结构定义。地址偏移量:0x0018，初值:0x00040000，宽度:32
 寄存器说明: V Inc
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ivinc    : 22; /* bit[0-21] : Vertical increment (Qu4.18) 
                                                    Ratio= Input Size/output size.
                                                    IVINC = 2^18 * ratio
                                                    0x40000 means ratio 1
                                                    0x80000 means downscaling by 2 and ratio=2
                                                    upscaling not support, this fieild must >=0x40000
                                                    in binning phase correction mode, this field must be 0x40000 */
        unsigned int  reserved : 10; /* bit[22-31]:  */
    } reg;
} SOC_ISP_BAS_BAS_IVINC_UNION;
#endif
#define SOC_ISP_BAS_BAS_IVINC_ivinc_START     (0)
#define SOC_ISP_BAS_BAS_IVINC_ivinc_END       (21)


/*****************************************************************************
 结构名    : SOC_ISP_BAS_BAS_COEF_ACTIVE_UNION
 结构说明  : BAS_COEF_ACTIVE 寄存器结构定义。地址偏移量:0x001C，初值:0x00000000，宽度:32
 寄存器说明: coef table select
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  h_coef_active      : 1;  /* bit[0]   : 0:h_coef_0 is used by the HW
                                                             1:h_coef_1 is used by the HW */
        unsigned int  v_coef_4tap_active : 1;  /* bit[1]   : 0:v_coef_4tap_0 is used by the HW
                                                             1:v_coef_4tap_1 is used by the HW */
        unsigned int  v_coef_6tap_active : 1;  /* bit[2]   : 0:v_coef_6tap_0 is used by the HW
                                                             1:v_coef_6tap_1 is used by the HW */
        unsigned int  reserved           : 29; /* bit[3-31]:  */
    } reg;
} SOC_ISP_BAS_BAS_COEF_ACTIVE_UNION;
#endif
#define SOC_ISP_BAS_BAS_COEF_ACTIVE_h_coef_active_START       (0)
#define SOC_ISP_BAS_BAS_COEF_ACTIVE_h_coef_active_END         (0)
#define SOC_ISP_BAS_BAS_COEF_ACTIVE_v_coef_4tap_active_START  (1)
#define SOC_ISP_BAS_BAS_COEF_ACTIVE_v_coef_4tap_active_END    (1)
#define SOC_ISP_BAS_BAS_COEF_ACTIVE_v_coef_6tap_active_START  (2)
#define SOC_ISP_BAS_BAS_COEF_ACTIVE_v_coef_6tap_active_END    (2)


/*****************************************************************************
 结构名    : SOC_ISP_BAS_BAS_H_COEF_0_UNION
 结构说明  : BAS_H_COEF_0 寄存器结构定义。地址偏移量:0x0100+0x4*(TAP6)，初值:0x00000000，宽度:32
 寄存器说明: horizontal coefficient table
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  h6tap_coef_0 : 20; /* bit[0-19] : can be 6tap or 4tap table decided by table contents
                                                        6tap, {5,7,8,8,7,5}=40bit, lower 20bit in even address, higher 20bit in odd address
                                                        4tap, {7,8,8,7}=30bit, lower 20bit in even address, higher 10bit in odd address */
        unsigned int  reserved     : 12; /* bit[20-31]:  */
    } reg;
} SOC_ISP_BAS_BAS_H_COEF_0_UNION;
#endif
#define SOC_ISP_BAS_BAS_H_COEF_0_h6tap_coef_0_START  (0)
#define SOC_ISP_BAS_BAS_H_COEF_0_h6tap_coef_0_END    (19)


/*****************************************************************************
 结构名    : SOC_ISP_BAS_BAS_H_COEF_1_UNION
 结构说明  : BAS_H_COEF_1 寄存器结构定义。地址偏移量:0x0200+0x4*(TAP6)，初值:0x00000000，宽度:32
 寄存器说明: horizontal coefficient table
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  h6tap_coef_1 : 20; /* bit[0-19] : can be 6tap or 4tap table decided by table contents */
        unsigned int  reserved     : 12; /* bit[20-31]:  */
    } reg;
} SOC_ISP_BAS_BAS_H_COEF_1_UNION;
#endif
#define SOC_ISP_BAS_BAS_H_COEF_1_h6tap_coef_1_START  (0)
#define SOC_ISP_BAS_BAS_H_COEF_1_h6tap_coef_1_END    (19)


/*****************************************************************************
 结构名    : SOC_ISP_BAS_BAS_V4TAP_COEF_0_UNION
 结构说明  : BAS_V4TAP_COEF_0 寄存器结构定义。地址偏移量:0x0300+0x4*(TAP4)，初值:0x00000000，宽度:32
 寄存器说明: vertical 4tap coefficient table
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  v4tap_coef_0 : 30; /* bit[0-29] : 32 phases table has symatricity, only 17 entries are needed.
                                                        each entry has 6 coefficients, bit width is {7,7,8,8,7}=30bits.
                                                        the example coefficient table is as following
                                                        
                                                        55,146,55,0,
                                                        52,145,59,0,
                                                        48,145,63,0,
                                                        45,144,67,0,
                                                        42,142,71,1,
                                                        39,141,75,1,
                                                        36,140,79,1,
                                                        33,138,83,2,
                                                        30,136,87,3,
                                                        27,135,90,4,
                                                        24,133,94,5,
                                                        22,130,98,6,
                                                        20,127,102,7,
                                                        18,124,106,8,
                                                        16,122,109,9,
                                                        14,118,113,11,
                                                        12,116,116,12, */
        unsigned int  reserved     : 2;  /* bit[30-31]:  */
    } reg;
} SOC_ISP_BAS_BAS_V4TAP_COEF_0_UNION;
#endif
#define SOC_ISP_BAS_BAS_V4TAP_COEF_0_v4tap_coef_0_START  (0)
#define SOC_ISP_BAS_BAS_V4TAP_COEF_0_v4tap_coef_0_END    (29)


/*****************************************************************************
 结构名    : SOC_ISP_BAS_BAS_V4TAP_COEF_1_UNION
 结构说明  : BAS_V4TAP_COEF_1 寄存器结构定义。地址偏移量:0x0400+0x4*(TAP4)，初值:0x00000000，宽度:32
 寄存器说明: vertical 4tap coefficient table
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  v4tap_coef_1 : 30; /* bit[0-29] :  */
        unsigned int  reserved     : 2;  /* bit[30-31]:  */
    } reg;
} SOC_ISP_BAS_BAS_V4TAP_COEF_1_UNION;
#endif
#define SOC_ISP_BAS_BAS_V4TAP_COEF_1_v4tap_coef_1_START  (0)
#define SOC_ISP_BAS_BAS_V4TAP_COEF_1_v4tap_coef_1_END    (29)


/*****************************************************************************
 结构名    : SOC_ISP_BAS_BAS_V6TAP_COEF_0_UNION
 结构说明  : BAS_V6TAP_COEF_0 寄存器结构定义。地址偏移量:0x0500+0x4*(TAP6)，初值:0x00000000，宽度:32
 寄存器说明: vertical 6tap coefficient table
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  v6tap_coef_0 : 20; /* bit[0-19] : 32 phases table has symatricity, only 17 entries need.
                                                        each entry has 6 coefficients, bit width is {5,7,7,8,8,7,5}=40bits
                                                        lower 20bit in even address, higher 20bit in odd address
                                                        the example coefficient table is as following
                                                        
                                                        16,64,96,64,16,0,
                                                        15,63,95,66,17,0,
                                                        14,61,95,68,18,0,
                                                        13,59,96,69,19,0,
                                                        12,58,94,71,20,1,
                                                        11,56,94,72,22,1,
                                                        10,54,94,74,23,1,
                                                        9,53,94,75,24,1,
                                                        9,51,92,77,26,1,
                                                        8,49,93,78,27,1,
                                                        7,47,92,80,28,2,
                                                        6,46,91,81,30,2,
                                                        6,44,91,82,31,2,
                                                        5,42,90,84,33,2,
                                                        5,41,88,85,34,3,
                                                        4,39,88,86,36,3,
                                                        4,37,87,87,37,4, */
        unsigned int  reserved     : 12; /* bit[20-31]:  */
    } reg;
} SOC_ISP_BAS_BAS_V6TAP_COEF_0_UNION;
#endif
#define SOC_ISP_BAS_BAS_V6TAP_COEF_0_v6tap_coef_0_START  (0)
#define SOC_ISP_BAS_BAS_V6TAP_COEF_0_v6tap_coef_0_END    (19)


/*****************************************************************************
 结构名    : SOC_ISP_BAS_BAS_V6TAP_COEF_1_UNION
 结构说明  : BAS_V6TAP_COEF_1 寄存器结构定义。地址偏移量:0x0600+0x4*(TAP6)，初值:0x00000000，宽度:32
 寄存器说明: vertical 6tap coefficient table
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  v6tap_coef_1 : 20; /* bit[0-19] :  */
        unsigned int  reserved     : 12; /* bit[20-31]:  */
    } reg;
} SOC_ISP_BAS_BAS_V6TAP_COEF_1_UNION;
#endif
#define SOC_ISP_BAS_BAS_V6TAP_COEF_1_v6tap_coef_1_START  (0)
#define SOC_ISP_BAS_BAS_V6TAP_COEF_1_v6tap_coef_1_END    (19)






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

#endif /* end of soc_isp_bas_interface.h */
