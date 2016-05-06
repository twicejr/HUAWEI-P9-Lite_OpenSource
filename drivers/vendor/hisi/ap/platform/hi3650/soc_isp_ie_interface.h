/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_isp_ie_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:21:46
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_ISP_IE.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_ISP_IE_INTERFACE_H__
#define __SOC_ISP_IE_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) IE
 ****************************************************************************/
/* 寄存器说明：Image effect control
   位域定义UNION结构:  SOC_ISP_IE_IE_CRTL_UNION */
#define SOC_ISP_IE_IE_CRTL_ADDR(base)                 ((base) + (0x0000))

/* 寄存器说明：Color selection
   位域定义UNION结构:  SOC_ISP_IE_IE_COLOR_SEL_UNION */
#define SOC_ISP_IE_IE_COLOR_SEL_ADDR(base)            ((base) + (0x0004))

/* 寄存器说明：3x3 matrix coefficient for emboss effect- 1
   位域定义UNION结构:  SOC_ISP_IE_IE_MAT_1_UNION */
#define SOC_ISP_IE_IE_MAT_1_ADDR(base)                ((base) + (0x0008))

/* 寄存器说明：3x3 matrix coefficient for emboss effect - 2
   位域定义UNION结构:  SOC_ISP_IE_IE_MAT_2_UNION */
#define SOC_ISP_IE_IE_MAT_2_ADDR(base)                ((base) + (0x000C))

/* 寄存器说明：3x3 matrix coefficient for emboss effect - 3 / sketch/sharpen - 1
   位域定义UNION结构:  SOC_ISP_IE_IE_MAT_3_UNION */
#define SOC_ISP_IE_IE_MAT_3_ADDR(base)                ((base) + (0x0010))

/* 寄存器说明：3x3 matrix coefficient for sketch/sharpen - 2
   位域定义UNION结构:  SOC_ISP_IE_IE_MAT_4_UNION */
#define SOC_ISP_IE_IE_MAT_4_ADDR(base)                ((base) + (0x0014))

/* 寄存器说明：3x3 matrix coefficient for sketch/sharpen - 3
   位域定义UNION结构:  SOC_ISP_IE_IE_MAT_5_UNION */
#define SOC_ISP_IE_IE_MAT_5_ADDR(base)                ((base) + (0x0018))

/* 寄存器说明：Chrominance increment value of a tint(used for sepia effect
   位域定义UNION结构:  SOC_ISP_IE_IE_TINT_UNION */
#define SOC_ISP_IE_IE_TINT_ADDR(base)                 ((base) + (0x001C))

/* 寄存器说明：shadow register for control register
   位域定义UNION结构:  SOC_ISP_IE_IE_CTRL_SHD_UNION */
#define SOC_ISP_IE_IE_CTRL_SHD_ADDR(base)             ((base) + (0x0020))

/* 寄存器说明：Factor and threshold for sharpen effect
   位域定义UNION结构:  SOC_ISP_IE_IE_SHARPEN_UNION */
#define SOC_ISP_IE_IE_SHARPEN_ADDR(base)              ((base) + (0x0024))





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
                     (1/1) IE
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_ISP_IE_IE_CRTL_UNION
 结构说明  : IE_CRTL 寄存器结构定义。地址偏移量:0x0000，初值:0x00000000，宽度:32
 寄存器说明: Image effect control
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bypass_mode : 1;  /* bit[0]   : bypass mode 
                                                      1: processing is activated 
                                                      0: processing is deactivated, bypass mode is selected */
        unsigned int  effect_mode : 3;  /* bit[1-3] : effect mode 
                                                      000: black & white effect (grayscale) 
                                                      001: negative 
                                                      010: sepia effect 
                                                      011: color selection effect 
                                                      100: emboss effect 
                                                      101: sketch effect 
                                                      110: sharpen effect 
                                                      111: reserved */
        unsigned int  reserved    : 28; /* bit[4-31]: Reserved */
    } reg;
} SOC_ISP_IE_IE_CRTL_UNION;
#endif
#define SOC_ISP_IE_IE_CRTL_bypass_mode_START  (0)
#define SOC_ISP_IE_IE_CRTL_bypass_mode_END    (0)
#define SOC_ISP_IE_IE_CRTL_effect_mode_START  (1)
#define SOC_ISP_IE_IE_CRTL_effect_mode_END    (3)


/*****************************************************************************
 结构名    : SOC_ISP_IE_IE_COLOR_SEL_UNION
 结构说明  : IE_COLOR_SEL 寄存器结构定义。地址偏移量:0x0004，初值:0x00000000，宽度:32
 寄存器说明: Color selection
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  color_selection : 3;  /* bit[0-2]  : Defining the maintained color: 
                                                           000: red green and blue 
                                                           001: blue 
                                                           010: green 
                                                           011: green and blue 
                                                           100: red 
                                                           101: red and blue 
                                                           110: red and green 
                                                           111: red green and blue */
        unsigned int  reserved_0      : 5;  /* bit[3-7]  : reserved */
        unsigned int  color_threshold : 8;  /* bit[8-15] : Threshold value of the RGB colors for the color selection effect. */
        unsigned int  reserved_1      : 16; /* bit[16-31]: Reserved */
    } reg;
} SOC_ISP_IE_IE_COLOR_SEL_UNION;
#endif
#define SOC_ISP_IE_IE_COLOR_SEL_color_selection_START  (0)
#define SOC_ISP_IE_IE_COLOR_SEL_color_selection_END    (2)
#define SOC_ISP_IE_IE_COLOR_SEL_color_threshold_START  (8)
#define SOC_ISP_IE_IE_COLOR_SEL_color_threshold_END    (15)


/*****************************************************************************
 结构名    : SOC_ISP_IE_IE_MAT_1_UNION
 结构说明  : IE_MAT_1 寄存器结构定义。地址偏移量:0x0008，初值:0x00008089，宽度:32
 寄存器说明: 3x3 matrix coefficient for emboss effect- 1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  emb_coef_11    : 3;  /* bit[0-2]  : first line, left entry of 3x3 emboss effect matrix, 2 bit for coefficient, one sign bit.
                                                          possible values for coefficients: 000 (1), 001 (2), 010 (4), 011 (8), 100 (-1), 101 (-2), 110 (-4), 111 (-8) */
        unsigned int  emb_coef_11_en : 1;  /* bit[3]    : 0: entry not used (coefficient is zero) 
                                                          1: entry used */
        unsigned int  emb_coef_12    : 3;  /* bit[4-6]  : first line, middle entry of 3x3 emboss effect matrix, 2 bit for coefficient, one sign bit.
                                                          possible values for coefficients: 000 (1), 001 (2), 010 (4), 011 (8), 100 (-1), 101 (-2), 110 (-4), 111 (-8) */
        unsigned int  emb_coef_12_en : 1;  /* bit[7]    : 0: entry not used (coefficient is zero) 
                                                          1: entry used */
        unsigned int  emb_coef_13    : 3;  /* bit[8-10] : first line, right entry of 3x3 emboss effect matrix, 2 bit for coefficient, one sign bit.
                                                          possible values for coefficients: 000 (1), 001 (2), 010 (4), 011 (8), 100 (-1), 101 (-2), 110 (-4), 111 (-8) */
        unsigned int  emb_coef_13_en : 1;  /* bit[11]   : 0: entry not used (coefficient is zero) 
                                                          1: entry used */
        unsigned int  emb_coef_21    : 3;  /* bit[12-14]: second line, left entry of 3x3 emboss effect matrix, 2 bit for coefficient, one sign bit.
                                                          possible values for coefficients: 000 (1), 001 (2), 010 (4), 011 (8), 100 (-1), 101 (-2), 110 (-4), 111 (-8) */
        unsigned int  emb_coef_21_en : 1;  /* bit[15]   : 0: entry not used (coefficient is zero) 
                                                          1: entry used */
        unsigned int  reserved       : 16; /* bit[16-31]: Reserved */
    } reg;
} SOC_ISP_IE_IE_MAT_1_UNION;
#endif
#define SOC_ISP_IE_IE_MAT_1_emb_coef_11_START     (0)
#define SOC_ISP_IE_IE_MAT_1_emb_coef_11_END       (2)
#define SOC_ISP_IE_IE_MAT_1_emb_coef_11_en_START  (3)
#define SOC_ISP_IE_IE_MAT_1_emb_coef_11_en_END    (3)
#define SOC_ISP_IE_IE_MAT_1_emb_coef_12_START     (4)
#define SOC_ISP_IE_IE_MAT_1_emb_coef_12_END       (6)
#define SOC_ISP_IE_IE_MAT_1_emb_coef_12_en_START  (7)
#define SOC_ISP_IE_IE_MAT_1_emb_coef_12_en_END    (7)
#define SOC_ISP_IE_IE_MAT_1_emb_coef_13_START     (8)
#define SOC_ISP_IE_IE_MAT_1_emb_coef_13_END       (10)
#define SOC_ISP_IE_IE_MAT_1_emb_coef_13_en_START  (11)
#define SOC_ISP_IE_IE_MAT_1_emb_coef_13_en_END    (11)
#define SOC_ISP_IE_IE_MAT_1_emb_coef_21_START     (12)
#define SOC_ISP_IE_IE_MAT_1_emb_coef_21_END       (14)
#define SOC_ISP_IE_IE_MAT_1_emb_coef_21_en_START  (15)
#define SOC_ISP_IE_IE_MAT_1_emb_coef_21_en_END    (15)


/*****************************************************************************
 结构名    : SOC_ISP_IE_IE_MAT_2_UNION
 结构说明  : IE_MAT_2 寄存器结构定义。地址偏移量:0x000C，初值:0x0000C0C0，宽度:32
 寄存器说明: 3x3 matrix coefficient for emboss effect - 2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  emb_coef_22    : 3;  /* bit[0-2]  : second line, middle entry of 3x3 emboss effect matrix, 2 bit for coefficient, one sign bit.
                                                          possible values for coefficients: 000 (1), 001 (2), 010 (4), 011 (8), 100 (-1), 101 (-2), 110 (-4), 111 (-8) */
        unsigned int  emb_coef_22_en : 1;  /* bit[3]    : 0: entry not used (coefficient is zero) 
                                                          1: entry used */
        unsigned int  emb_coef_23    : 3;  /* bit[4-6]  : second line, right entry of 3x3 emboss effect matrix, 2 bit for coefficient, one sign bit.
                                                          possible values for coefficients: 000 (1), 001 (2), 010 (4), 011 (8), 100 (-1), 101 (-2), 110 (-4), 111 (-8) */
        unsigned int  emb_coef_23_en : 1;  /* bit[7]    : 0: entry not used (coefficient is zero) 
                                                          1: entry used */
        unsigned int  emb_coef_31    : 3;  /* bit[8-10] : Third line, left entry of 3x3 emboss effect matrix, 2 bit for coefficient, one sign bit.
                                                          possible values for coefficients: 000 (1), 001 (2), 010 (4), 011 (8), 100 (-1), 101 (-2), 110 (-4), 111 (-8) */
        unsigned int  emb_coef_31_en : 1;  /* bit[11]   : 0: entry not used (coefficient is zero) 
                                                          1: entry used */
        unsigned int  emb_coef_32    : 3;  /* bit[12-14]: Third line, middle entry of 3x3 emboss effect matrix, 2 bit for coefficient, one sign bit.
                                                          possible values for coefficients: 000 (1), 001 (2), 010 (4), 011 (8), 100 (-1), 101 (-2), 110 (-4), 111 (-8) */
        unsigned int  emb_coef_32_en : 1;  /* bit[15]   : 0: entry not used (coefficient is zero) 
                                                          1: entry used */
        unsigned int  reserved       : 16; /* bit[16-31]: Reserved */
    } reg;
} SOC_ISP_IE_IE_MAT_2_UNION;
#endif
#define SOC_ISP_IE_IE_MAT_2_emb_coef_22_START     (0)
#define SOC_ISP_IE_IE_MAT_2_emb_coef_22_END       (2)
#define SOC_ISP_IE_IE_MAT_2_emb_coef_22_en_START  (3)
#define SOC_ISP_IE_IE_MAT_2_emb_coef_22_en_END    (3)
#define SOC_ISP_IE_IE_MAT_2_emb_coef_23_START     (4)
#define SOC_ISP_IE_IE_MAT_2_emb_coef_23_END       (6)
#define SOC_ISP_IE_IE_MAT_2_emb_coef_23_en_START  (7)
#define SOC_ISP_IE_IE_MAT_2_emb_coef_23_en_END    (7)
#define SOC_ISP_IE_IE_MAT_2_emb_coef_31_START     (8)
#define SOC_ISP_IE_IE_MAT_2_emb_coef_31_END       (10)
#define SOC_ISP_IE_IE_MAT_2_emb_coef_31_en_START  (11)
#define SOC_ISP_IE_IE_MAT_2_emb_coef_31_en_END    (11)
#define SOC_ISP_IE_IE_MAT_2_emb_coef_32_START     (12)
#define SOC_ISP_IE_IE_MAT_2_emb_coef_32_END       (14)
#define SOC_ISP_IE_IE_MAT_2_emb_coef_32_en_START  (15)
#define SOC_ISP_IE_IE_MAT_2_emb_coef_32_en_END    (15)


/*****************************************************************************
 结构名    : SOC_ISP_IE_IE_MAT_3_UNION
 结构说明  : IE_MAT_3 寄存器结构定义。地址偏移量:0x0010，初值:0x0000CCCD，宽度:32
 寄存器说明: 3x3 matrix coefficient for emboss effect - 3 / sketch/sharpen - 1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  emb_coef_33     : 3;  /* bit[0-2]  : third line, middle entry of 3x3 emboss effect matrix, 2 bit for coefficient, one sign bit.
                                                           possible values for coefficients: 000 (1), 001 (2), 010 (4), 011 (8), 100 (-1), 101 (-2), 110 (-4), 111 (-8) */
        unsigned int  emb_coef_33_en  : 1;  /* bit[3]    : 0: entry not used (coefficient is zero) 
                                                           1: entry used */
        unsigned int  sket_coef_11    : 3;  /* bit[4-6]  : first line, left entry of 3x3 sketch effect matrix, 2 bit for coefficient, one sign bit. */
        unsigned int  sket_coef_11_en : 1;  /* bit[7]    : 0: entry not used (coefficient is zero) 
                                                           1: entry used */
        unsigned int  sket_coef_12    : 3;  /* bit[8-10] : first line, middle entry of 3x3 sketch effect matrix, 2 bit for coefficient, one sign bit. */
        unsigned int  sket_coef_12_en : 1;  /* bit[11]   : 0: entry not used (coefficient is zero) 
                                                           1: entry used */
        unsigned int  sket_coef_13    : 3;  /* bit[12-14]: first line, right entry of 3x3 sketch effect matrix, 2 bit for coefficient, one sign bit. */
        unsigned int  sket_coef_13_en : 1;  /* bit[15]   : 0: entry not used (coefficient is zero) 
                                                           1: entry used */
        unsigned int  reserved        : 16; /* bit[16-31]: Reserved */
    } reg;
} SOC_ISP_IE_IE_MAT_3_UNION;
#endif
#define SOC_ISP_IE_IE_MAT_3_emb_coef_33_START      (0)
#define SOC_ISP_IE_IE_MAT_3_emb_coef_33_END        (2)
#define SOC_ISP_IE_IE_MAT_3_emb_coef_33_en_START   (3)
#define SOC_ISP_IE_IE_MAT_3_emb_coef_33_en_END     (3)
#define SOC_ISP_IE_IE_MAT_3_sket_coef_11_START     (4)
#define SOC_ISP_IE_IE_MAT_3_sket_coef_11_END       (6)
#define SOC_ISP_IE_IE_MAT_3_sket_coef_11_en_START  (7)
#define SOC_ISP_IE_IE_MAT_3_sket_coef_11_en_END    (7)
#define SOC_ISP_IE_IE_MAT_3_sket_coef_12_START     (8)
#define SOC_ISP_IE_IE_MAT_3_sket_coef_12_END       (10)
#define SOC_ISP_IE_IE_MAT_3_sket_coef_12_en_START  (11)
#define SOC_ISP_IE_IE_MAT_3_sket_coef_12_en_END    (11)
#define SOC_ISP_IE_IE_MAT_3_sket_coef_13_START     (12)
#define SOC_ISP_IE_IE_MAT_3_sket_coef_13_END       (14)
#define SOC_ISP_IE_IE_MAT_3_sket_coef_13_en_START  (15)
#define SOC_ISP_IE_IE_MAT_3_sket_coef_13_en_END    (15)


/*****************************************************************************
 结构名    : SOC_ISP_IE_IE_MAT_4_UNION
 结构说明  : IE_MAT_4 寄存器结构定义。地址偏移量:0x0014，初值:0x0000CCBC，宽度:32
 寄存器说明: 3x3 matrix coefficient for sketch/sharpen - 2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sket_coef_21    : 3;  /* bit[0-2]  : second line, left entry of 3x3 sketch effect matrix, 2 bit for coefficient, one sign bit.
                                                           possible values for coefficients: 000 (1), 001 (2), 010 (4), 011 (8), 100 (-1), 101 (-2), 110 (-4), 111 (-8) */
        unsigned int  sket_coef_21_en : 1;  /* bit[3]    : 0: entry not used (coefficient is zero) 
                                                           1: entry used */
        unsigned int  sket_coef_22    : 3;  /* bit[4-6]  : second line, middle entry of 3x3 sketch effect matrix, 2 bit for coefficient, one sign bit. */
        unsigned int  sket_coef_22_en : 1;  /* bit[7]    : 0: entry not used (coefficient is zero) 
                                                           1: entry used */
        unsigned int  sket_coef_23    : 3;  /* bit[8-10] : second line, right entry of 3x3 sketch effect matrix, 2 bit for coefficient, one sign bit. */
        unsigned int  sket_coef_23_en : 1;  /* bit[11]   : 0: entry not used (coefficient is zero) 
                                                           1: entry used */
        unsigned int  sket_coef_31    : 3;  /* bit[12-14]: third line, left entry of 3x3 sketch effect matrix, 2 bit for coefficient, one sign bit. */
        unsigned int  sket_coef_31_en : 1;  /* bit[15]   : 0: entry not used (coefficient is zero) 
                                                           1: entry used */
        unsigned int  reserved        : 16; /* bit[16-31]: Reserved */
    } reg;
} SOC_ISP_IE_IE_MAT_4_UNION;
#endif
#define SOC_ISP_IE_IE_MAT_4_sket_coef_21_START     (0)
#define SOC_ISP_IE_IE_MAT_4_sket_coef_21_END       (2)
#define SOC_ISP_IE_IE_MAT_4_sket_coef_21_en_START  (3)
#define SOC_ISP_IE_IE_MAT_4_sket_coef_21_en_END    (3)
#define SOC_ISP_IE_IE_MAT_4_sket_coef_22_START     (4)
#define SOC_ISP_IE_IE_MAT_4_sket_coef_22_END       (6)
#define SOC_ISP_IE_IE_MAT_4_sket_coef_22_en_START  (7)
#define SOC_ISP_IE_IE_MAT_4_sket_coef_22_en_END    (7)
#define SOC_ISP_IE_IE_MAT_4_sket_coef_23_START     (8)
#define SOC_ISP_IE_IE_MAT_4_sket_coef_23_END       (10)
#define SOC_ISP_IE_IE_MAT_4_sket_coef_23_en_START  (11)
#define SOC_ISP_IE_IE_MAT_4_sket_coef_23_en_END    (11)
#define SOC_ISP_IE_IE_MAT_4_sket_coef_31_START     (12)
#define SOC_ISP_IE_IE_MAT_4_sket_coef_31_END       (14)
#define SOC_ISP_IE_IE_MAT_4_sket_coef_31_en_START  (15)
#define SOC_ISP_IE_IE_MAT_4_sket_coef_31_en_END    (15)


/*****************************************************************************
 结构名    : SOC_ISP_IE_IE_MAT_5_UNION
 结构说明  : IE_MAT_5 寄存器结构定义。地址偏移量:0x0018，初值:0x000000CC，宽度:32
 寄存器说明: 3x3 matrix coefficient for sketch/sharpen - 3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sket_coef_32    : 3;  /* bit[0-2] : Third line, left entry of 3x3 sketch effect matrix, 2 bit for coefficient, one sign bit.
                                                          possible values for coefficients: 000 (1), 001 (2), 010 (4), 011 (8), 100 (-1), 101 (-2), 110 (-4), 111 (-8) */
        unsigned int  sket_coef_32_en : 1;  /* bit[3]   : 0: entry not used (coefficient is zero) 
                                                          1: entry used */
        unsigned int  sket_coef_33    : 3;  /* bit[4-6] : Third line, middle entry of 3x3 sketch effect matrix, 2 bit for coefficient, one sign bit. */
        unsigned int  sket_coef_33_en : 1;  /* bit[7]   : 0: entry not used (coefficient is zero) 
                                                          1: entry used */
        unsigned int  reserved        : 24; /* bit[8-31]: Reserved */
    } reg;
} SOC_ISP_IE_IE_MAT_5_UNION;
#endif
#define SOC_ISP_IE_IE_MAT_5_sket_coef_32_START     (0)
#define SOC_ISP_IE_IE_MAT_5_sket_coef_32_END       (2)
#define SOC_ISP_IE_IE_MAT_5_sket_coef_32_en_START  (3)
#define SOC_ISP_IE_IE_MAT_5_sket_coef_32_en_END    (3)
#define SOC_ISP_IE_IE_MAT_5_sket_coef_33_START     (4)
#define SOC_ISP_IE_IE_MAT_5_sket_coef_33_END       (6)
#define SOC_ISP_IE_IE_MAT_5_sket_coef_33_en_START  (7)
#define SOC_ISP_IE_IE_MAT_5_sket_coef_33_en_END    (7)


/*****************************************************************************
 结构名    : SOC_ISP_IE_IE_TINT_UNION
 结构说明  : IE_TINT 寄存器结构定义。地址偏移量:0x001C，初值:0x0000880C，宽度:32
 寄存器说明: Chrominance increment value of a tint(used for sepia effect
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  inc_cb   : 8;  /* bit[0-7]  : Cb increment value of a tint. 7 bits for value, 1 sign bit. Default tint is R=162 G=138 B=101, which is used for the sepia effect. See below for the calculation of the entries. */
        unsigned int  inc_cr   : 8;  /* bit[8-15] : Cr increment value of a tint. 7 bits for value, 1 sign bit. Default tint is R=162 G=138 B=101, which is used for the sepia effect. See below for the calculation of the entries. */
        unsigned int  reserved : 16; /* bit[16-31]: Reserved */
    } reg;
} SOC_ISP_IE_IE_TINT_UNION;
#endif
#define SOC_ISP_IE_IE_TINT_inc_cb_START    (0)
#define SOC_ISP_IE_IE_TINT_inc_cb_END      (7)
#define SOC_ISP_IE_IE_TINT_inc_cr_START    (8)
#define SOC_ISP_IE_IE_TINT_inc_cr_END      (15)


/*****************************************************************************
 结构名    : SOC_ISP_IE_IE_CTRL_SHD_UNION
 结构说明  : IE_CTRL_SHD 寄存器结构定义。地址偏移量:0x0020，初值:0x00000000，宽度:32
 寄存器说明: shadow register for control register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0      : 1;  /* bit[0]   : Cr increment value of a tint. 7 bits for value, 1 sign bit. Default tint is R=162 G=138 B=101, which is used for the sepia effect. See below for the calculation of the entries. */
        unsigned int  effect_mode_shd : 3;  /* bit[1-3] : effect mode 
                                                          000: black & white effect (grayscale) 
                                                          001: negative 
                                                          010: sepia effect 
                                                          011: color selection effect 
                                                          100: emboss effect 
                                                          101: sketch effect 
                                                          110: sharpen effect 
                                                          111: reserved */
        unsigned int  reserved_1      : 28; /* bit[4-31]: Reserved */
    } reg;
} SOC_ISP_IE_IE_CTRL_SHD_UNION;
#endif
#define SOC_ISP_IE_IE_CTRL_SHD_effect_mode_shd_START  (1)
#define SOC_ISP_IE_IE_CTRL_SHD_effect_mode_shd_END    (3)


/*****************************************************************************
 结构名    : SOC_ISP_IE_IE_SHARPEN_UNION
 结构说明  : IE_SHARPEN 寄存器结构定义。地址偏移量:0x0024，初值:0x00000000，宽度:32
 寄存器说明: Factor and threshold for sharpen effect
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coring_thr   : 8;  /* bit[0-7]  : Threshold for coring function. This value is used to avoid amplifying noise too much by suppressing sharpening for small gradients. Higher value means less sharpening for smooth edges. Threshold zero means no coring, so all gradients are treated the same. Threshold 255 means nearly no sharpening. An absolute value for the highpass signal is defined here. The highpass signal is truncated at the defined level. */
        unsigned int  sharp_factor : 6;  /* bit[8-13] : 6Bit Factor for sharpening function. Value range is from 0x0 to 
                                                        0x3F. High value means strong sharpening. The resulting factors are for example: 
                                                        0x00 = 0 (no sharpen effect like bypass) 
                                                        0x01 = 0.25 
                                                        0x02 = 0.5 
                                                        0x03 = 0.75 
                                                        0x04 = 1.0 
                                                        0x05 = 1.25 
                                                        0x06 = 1.5 
                                                        0x08 = 2.0 
                                                        0x0A = 2.5 
                                                        0x0C = 3.0 
                                                        0x10 = 4.0 
                                                        0x18 = 6.0 
                                                        0x20 = 8.0 
                                                        0x30 = 12.0 
                                                        0x3F = 15.75 */
        unsigned int  reserved     : 18; /* bit[14-31]: Reserved */
    } reg;
} SOC_ISP_IE_IE_SHARPEN_UNION;
#endif
#define SOC_ISP_IE_IE_SHARPEN_coring_thr_START    (0)
#define SOC_ISP_IE_IE_SHARPEN_coring_thr_END      (7)
#define SOC_ISP_IE_IE_SHARPEN_sharp_factor_START  (8)
#define SOC_ISP_IE_IE_SHARPEN_sharp_factor_END    (13)






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

#endif /* end of soc_isp_ie_interface.h */
