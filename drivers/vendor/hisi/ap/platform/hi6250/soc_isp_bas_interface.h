

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
                                                       11:diable, always accept data, but not output */
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
                                                 [Note]
                                                 binning phase correction mode doesn't support crop, so this field must be 0x0..
                                                 If binning during preview, ZSL is not supported because sensor need to be reprogrammed for capture. Hence, specific crop module can be used for DZOOM instead
                                                 [end] */
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
                                                  [Note]
                                                  0xFFFF_FFFF means no crop
                                                  Otherwise, for correct rescaling, after calculating hinc, we should have ihright = ihleft+hinc*(ohsize-1), here ohsize mean output horizontal size
                                                  [end]
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
                                                [Note]
                                                binning phase correction mode doesn't support crop, so this field must be 0x0.
                                                If binning during preview, ZSL is not supported because sensor need to be reprogrammed for capture. Hence, specific crop module can be used for DZOOM instead
                                                [end] */
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
                                                   0xFFFF_FFFF means no crop 
                                                   Otherwise, for correct rescaling we should have ivbottom=ivtop+vinc(ovsize-1),here ovize mean output vertical size
                                                   [end]
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
                                                    ratio= ihsize/ohsize.
                                                    IHINC = 2^18 * ratio
                                                    0x40000 means ratio 1
                                                    0x80000 means downscaling by 2 and ratio=2
                                                    [Note]
                                                    upscaling not support, this fieild must >=0x40000
                                                    in binning phase correction mode, this field must be 0x40000
                                                    [end] */
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
                                                    ratio= ivsize/ovsize
                                                    IVINC = 2^18 * ratio
                                                    0x40000 means ratio 1
                                                    0x80000 means downscaling by 2 and ratio=2
                                                    [Note]
                                                    upscaling not support, this field must >=0x40000
                                                    in binning phase correction mode, this field must be 0x40000
                                                    Binning Phase Correction and downscale are exclusive
                                                    [end] */
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
        unsigned int  h6tap_coef0_0_5 : 7;  /* bit[0-6]  :  */
        unsigned int  reserved_0      : 1;  /* bit[7]    :  */
        unsigned int  h6tap_coef0_1_4 : 8;  /* bit[8-15] :  */
        unsigned int  h6tap_coef0_2_3 : 10; /* bit[16-25]:  */
        unsigned int  reserved_1      : 6;  /* bit[26-31]:  */
    } reg;
} SOC_ISP_BAS_BAS_H_COEF_0_UNION;
#endif
#define SOC_ISP_BAS_BAS_H_COEF_0_h6tap_coef0_0_5_START  (0)
#define SOC_ISP_BAS_BAS_H_COEF_0_h6tap_coef0_0_5_END    (6)
#define SOC_ISP_BAS_BAS_H_COEF_0_h6tap_coef0_1_4_START  (8)
#define SOC_ISP_BAS_BAS_H_COEF_0_h6tap_coef0_1_4_END    (15)
#define SOC_ISP_BAS_BAS_H_COEF_0_h6tap_coef0_2_3_START  (16)
#define SOC_ISP_BAS_BAS_H_COEF_0_h6tap_coef0_2_3_END    (25)


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
        unsigned int  h6tap_coef1_0_5 : 7;  /* bit[0-6]  :  */
        unsigned int  reserved_0      : 1;  /* bit[7]    :  */
        unsigned int  h6tap_coef1_1_4 : 8;  /* bit[8-15] :  */
        unsigned int  h6tap_coef1_2_3 : 10; /* bit[16-25]:  */
        unsigned int  reserved_1      : 6;  /* bit[26-31]:  */
    } reg;
} SOC_ISP_BAS_BAS_H_COEF_1_UNION;
#endif
#define SOC_ISP_BAS_BAS_H_COEF_1_h6tap_coef1_0_5_START  (0)
#define SOC_ISP_BAS_BAS_H_COEF_1_h6tap_coef1_0_5_END    (6)
#define SOC_ISP_BAS_BAS_H_COEF_1_h6tap_coef1_1_4_START  (8)
#define SOC_ISP_BAS_BAS_H_COEF_1_h6tap_coef1_1_4_END    (15)
#define SOC_ISP_BAS_BAS_H_COEF_1_h6tap_coef1_2_3_START  (16)
#define SOC_ISP_BAS_BAS_H_COEF_1_h6tap_coef1_2_3_END    (25)


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
        unsigned int  reserved_0      : 8;  /* bit[0-7]  :  */
        unsigned int  v4tap_coef0_0_3 : 8;  /* bit[8-15] : 32 phases table has symatricity, only 17 entries are needed.
                                                           the example coefficient table is as following, coefficient order from left to right is C3,C2,C1,C0
                                                           even address write C0
                                                           odd address write C3
                                                           eg. for the following table
                                                           0x0 v4tap_coef_0_3=0
                                                            v4tap_coef_1_2=55
                                                           0x4 v4tap_coef_0_3=55
                                                            v4tap_coef_1_2=146
                                                           
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
                                                           12,116,116,12,
                                                           
                                                           another example table with neative coefficients as following
                                                            -7,272, -7, -2,
                                                           -11,269, 0, -2,
                                                           -15,268, 6, -3,
                                                           -19,266, 13, -4,
                                                           -22,261, 21, -4,
                                                           -24,256, 29, -5,
                                                           -26,251, 38, -7,
                                                           -28,244, 48, -8,
                                                           -29,236, 58, -9,
                                                           -29,227, 69,-11,
                                                           -29,218, 80,-13,
                                                           -29,208, 91,-14,
                                                           -28,197,103,-16,
                                                           -27,186,115,-18,
                                                           -26,175,127,-20,
                                                           -25,163,139,-21,
                                                           -23,151,151,-23, */
        unsigned int  v4tap_coef0_1_2 : 10; /* bit[16-25]: even address write C1
                                                           odd address write C2 */
        unsigned int  reserved_1      : 6;  /* bit[26-31]:  */
    } reg;
} SOC_ISP_BAS_BAS_V4TAP_COEF_0_UNION;
#endif
#define SOC_ISP_BAS_BAS_V4TAP_COEF_0_v4tap_coef0_0_3_START  (8)
#define SOC_ISP_BAS_BAS_V4TAP_COEF_0_v4tap_coef0_0_3_END    (15)
#define SOC_ISP_BAS_BAS_V4TAP_COEF_0_v4tap_coef0_1_2_START  (16)
#define SOC_ISP_BAS_BAS_V4TAP_COEF_0_v4tap_coef0_1_2_END    (25)


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
        unsigned int  reserved_0      : 8;  /* bit[0-7]  :  */
        unsigned int  v4tap_coef1_0_3 : 8;  /* bit[8-15] :  */
        unsigned int  v4tap_coef1_1_2 : 10; /* bit[16-25]:  */
        unsigned int  reserved_1      : 6;  /* bit[26-31]:  */
    } reg;
} SOC_ISP_BAS_BAS_V4TAP_COEF_1_UNION;
#endif
#define SOC_ISP_BAS_BAS_V4TAP_COEF_1_v4tap_coef1_0_3_START  (8)
#define SOC_ISP_BAS_BAS_V4TAP_COEF_1_v4tap_coef1_0_3_END    (15)
#define SOC_ISP_BAS_BAS_V4TAP_COEF_1_v4tap_coef1_1_2_START  (16)
#define SOC_ISP_BAS_BAS_V4TAP_COEF_1_v4tap_coef1_1_2_END    (25)


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
        unsigned int  v6tap_coef0_0_5 : 7;  /* bit[0-6]  : 32 phases table has symatricity, only 17 entries are needed.
                                                           the example coefficient table is as following
                                                           coefficient order from left to right is C5,C4,C3,C2,C1,C0
                                                           even address write C0
                                                           odd address write C5
                                                           eg. for the following table
                                                           0x0 v6tap_coef_0_5=0
                                                            v6tap_coef_1_4=16
                                                            v6tap_coef_2_3=64
                                                           0x4 v6tap_coef_0_5=16
                                                            v6tap_coef_1_4=64
                                                            v6tap_coef_2_3=96
                                                           
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
                                                           4,37,87,87,37,4,
                                                           
                                                           another example table with negative coefficients as following
                                                            8,-19,279,-19, 8,-1,
                                                            8,-23,277,-11, 6,-1,
                                                            9,-28,275, -4, 5,-1,
                                                           10,-32,271, 4, 4,-1,
                                                           10,-35,267, 13, 2,-1,
                                                           10,-37,262, 22, 0,-1,
                                                           10,-39,256, 32, -2,-1,
                                                           10,-40,249, 42, -5, 0,
                                                           10,-41,241, 53, -7, 0,
                                                           10,-41,231, 65,-10, 1,
                                                            9,-41,224, 76,-13, 1,
                                                            9,-40,211, 89,-15, 2,
                                                            8,-38,200,101,-18, 3,
                                                            7,-37,190,114,-21, 3,
                                                            7,-35,177,127,-24, 4,
                                                            6,-32,165,140,-27, 4,
                                                            5,-29,152,152,-29, 5, */
        unsigned int  reserved_0      : 1;  /* bit[7]    :  */
        unsigned int  v6tap_coef0_1_4 : 8;  /* bit[8-15] : even address write C1
                                                           odd address write C2 */
        unsigned int  v6tap_coef0_2_3 : 10; /* bit[16-25]: even address write C2
                                                           odd address write C3 */
        unsigned int  reserved_1      : 6;  /* bit[26-31]:  */
    } reg;
} SOC_ISP_BAS_BAS_V6TAP_COEF_0_UNION;
#endif
#define SOC_ISP_BAS_BAS_V6TAP_COEF_0_v6tap_coef0_0_5_START  (0)
#define SOC_ISP_BAS_BAS_V6TAP_COEF_0_v6tap_coef0_0_5_END    (6)
#define SOC_ISP_BAS_BAS_V6TAP_COEF_0_v6tap_coef0_1_4_START  (8)
#define SOC_ISP_BAS_BAS_V6TAP_COEF_0_v6tap_coef0_1_4_END    (15)
#define SOC_ISP_BAS_BAS_V6TAP_COEF_0_v6tap_coef0_2_3_START  (16)
#define SOC_ISP_BAS_BAS_V6TAP_COEF_0_v6tap_coef0_2_3_END    (25)


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
        unsigned int  v6tap_coef1_0_5 : 7;  /* bit[0-6]  :  */
        unsigned int  reserved_0      : 1;  /* bit[7]    :  */
        unsigned int  v6tap_coef1_1_4 : 8;  /* bit[8-15] :  */
        unsigned int  v6tap_coef1_2_3 : 10; /* bit[16-25]:  */
        unsigned int  reserved_1      : 6;  /* bit[26-31]:  */
    } reg;
} SOC_ISP_BAS_BAS_V6TAP_COEF_1_UNION;
#endif
#define SOC_ISP_BAS_BAS_V6TAP_COEF_1_v6tap_coef1_0_5_START  (0)
#define SOC_ISP_BAS_BAS_V6TAP_COEF_1_v6tap_coef1_0_5_END    (6)
#define SOC_ISP_BAS_BAS_V6TAP_COEF_1_v6tap_coef1_1_4_START  (8)
#define SOC_ISP_BAS_BAS_V6TAP_COEF_1_v6tap_coef1_1_4_END    (15)
#define SOC_ISP_BAS_BAS_V6TAP_COEF_1_v6tap_coef1_2_3_START  (16)
#define SOC_ISP_BAS_BAS_V6TAP_COEF_1_v6tap_coef1_2_3_END    (25)






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
