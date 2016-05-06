/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_isp_sharpen_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:22:04
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_ISP_SHARPEN.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_ISP_SHARPEN_INTERFACE_H__
#define __SOC_ISP_SHARPEN_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) SHARPEN
 ****************************************************************************/
/* 寄存器说明：Mid band filter coefficients 0
   位域定义UNION结构:  SOC_ISP_SHARPEN_G33_0_UNION */
#define SOC_ISP_SHARPEN_G33_0_ADDR(base)              ((base) + (0x000))

/* 寄存器说明：Mid band filter coefficients 1
   位域定义UNION结构:  SOC_ISP_SHARPEN_G33_1_UNION */
#define SOC_ISP_SHARPEN_G33_1_ADDR(base)              ((base) + (0x004))

/* 寄存器说明：Mid band filter coefficients 2
   位域定义UNION结构:  SOC_ISP_SHARPEN_G33_2_UNION */
#define SOC_ISP_SHARPEN_G33_2_ADDR(base)              ((base) + (0x008))

/* 寄存器说明：Line Detection configuration
   位域定义UNION结构:  SOC_ISP_SHARPEN_LINEDET_UNION */
#define SOC_ISP_SHARPEN_LINEDET_ADDR(base)            ((base) + (0x00C))

/* 寄存器说明：sharp configuration (mid-band)
   位域定义UNION结构:  SOC_ISP_SHARPEN_SHARPCFG_UNION */
#define SOC_ISP_SHARPEN_SHARPCFG_ADDR(base)           ((base) + (0x010))

/* 寄存器说明：edge configuration (high-band)
   位域定义UNION结构:  SOC_ISP_SHARPEN_EDGECFG_UNION */
#define SOC_ISP_SHARPEN_EDGECFG_ADDR(base)            ((base) + (0x014))

/* 寄存器说明：undershoot/overshoot configuration
   位域定义UNION结构:  SOC_ISP_SHARPEN_SHOOTCFG_UNION */
#define SOC_ISP_SHARPEN_SHOOTCFG_ADDR(base)           ((base) + (0x018))

/* 寄存器说明：Filter select configuration
   位域定义UNION结构:  SOC_ISP_SHARPEN_SELCFG_UNION */
#define SOC_ISP_SHARPEN_SELCFG_ADDR(base)             ((base) + (0x01C))

/* 寄存器说明：horizontal cropping configuration
   位域定义UNION结构:  SOC_ISP_SHARPEN_HCROP_UNION */
#define SOC_ISP_SHARPEN_HCROP_ADDR(base)              ((base) + (0x020))

/* 寄存器说明：vertical croppring configuration
   位域定义UNION结构:  SOC_ISP_SHARPEN_VCROP_UNION */
#define SOC_ISP_SHARPEN_VCROP_ADDR(base)              ((base) + (0x024))





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
                     (1/1) SHARPEN
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_ISP_SHARPEN_G33_0_UNION
 结构说明  : G33_0 寄存器结构定义。地址偏移量:0x000，初值:0x00000000，宽度:32
 寄存器说明: Mid band filter coefficients 0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g0_0     : 8;  /* bit[0-7]  : Mid Band filter coefficient Qs8.0
                                                    G0_0 = G3[0][0] */
        unsigned int  g0_1     : 8;  /* bit[8-15] : Mid Band filter coefficient Qs8.0
                                                    G0_1 = G3[0][1] */
        unsigned int  g0_2     : 8;  /* bit[16-23]: Mid Band filter coefficient Qs8.0
                                                    G0_2 = G3[0][2] */
        unsigned int  reserved : 8;  /* bit[24-31]:  */
    } reg;
} SOC_ISP_SHARPEN_G33_0_UNION;
#endif
#define SOC_ISP_SHARPEN_G33_0_g0_0_START      (0)
#define SOC_ISP_SHARPEN_G33_0_g0_0_END        (7)
#define SOC_ISP_SHARPEN_G33_0_g0_1_START      (8)
#define SOC_ISP_SHARPEN_G33_0_g0_1_END        (15)
#define SOC_ISP_SHARPEN_G33_0_g0_2_START      (16)
#define SOC_ISP_SHARPEN_G33_0_g0_2_END        (23)


/*****************************************************************************
 结构名    : SOC_ISP_SHARPEN_G33_1_UNION
 结构说明  : G33_1 寄存器结构定义。地址偏移量:0x004，初值:0x00000000，宽度:32
 寄存器说明: Mid band filter coefficients 1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g1_0     : 8;  /* bit[0-7]  : Mid Band filter coefficient Qs8.0
                                                    G1_0 = G3[1][0] */
        unsigned int  g1_1     : 8;  /* bit[8-15] : Mid Band filter coefficient Qs8.0
                                                    G1_1 = G3[1][1] */
        unsigned int  g1_2     : 8;  /* bit[16-23]: Mid Band filter coefficient Qs8.0
                                                    G1_2 = G3[1][2] */
        unsigned int  reserved : 8;  /* bit[24-31]:  */
    } reg;
} SOC_ISP_SHARPEN_G33_1_UNION;
#endif
#define SOC_ISP_SHARPEN_G33_1_g1_0_START      (0)
#define SOC_ISP_SHARPEN_G33_1_g1_0_END        (7)
#define SOC_ISP_SHARPEN_G33_1_g1_1_START      (8)
#define SOC_ISP_SHARPEN_G33_1_g1_1_END        (15)
#define SOC_ISP_SHARPEN_G33_1_g1_2_START      (16)
#define SOC_ISP_SHARPEN_G33_1_g1_2_END        (23)


/*****************************************************************************
 结构名    : SOC_ISP_SHARPEN_G33_2_UNION
 结构说明  : G33_2 寄存器结构定义。地址偏移量:0x008，初值:0x00000000，宽度:32
 寄存器说明: Mid band filter coefficients 2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g2_0     : 8;  /* bit[0-7]  : Mid Band filter coefficient Qs8.0
                                                    G2_0 = G3[2][0] */
        unsigned int  g2_1     : 8;  /* bit[8-15] : Mid Band filter coefficient Qs8.0
                                                    G2_1 = G3[2][1] */
        unsigned int  g2_2     : 8;  /* bit[16-23]: Mid Band filter coefficient Qs8.0
                                                    G2_2 = G3[2][2] */
        unsigned int  reserved : 8;  /* bit[24-31]:  */
    } reg;
} SOC_ISP_SHARPEN_G33_2_UNION;
#endif
#define SOC_ISP_SHARPEN_G33_2_g2_0_START      (0)
#define SOC_ISP_SHARPEN_G33_2_g2_0_END        (7)
#define SOC_ISP_SHARPEN_G33_2_g2_1_START      (8)
#define SOC_ISP_SHARPEN_G33_2_g2_1_END        (15)
#define SOC_ISP_SHARPEN_G33_2_g2_2_START      (16)
#define SOC_ISP_SHARPEN_G33_2_g2_2_END        (23)


/*****************************************************************************
 结构名    : SOC_ISP_SHARPEN_LINEDET_UNION
 结构说明  : LINEDET 寄存器结构定义。地址偏移量:0x00C，初值:0x00000000，宽度:32
 寄存器说明: Line Detection configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  linethd1  : 5;  /* bit[0-4]  : Line Detection threshold Qu5.0 */
        unsigned int  reserved_0: 3;  /* bit[5-7]  :  */
        unsigned int  linethd2  : 5;  /* bit[8-12] : Line Detection threshold Qu5.0 */
        unsigned int  reserved_1: 3;  /* bit[13-15]:  */
        unsigned int  lineamt1  : 12; /* bit[16-27]: high-band sharpen strength when line is detected Qu12.0 */
        unsigned int  reserved_2: 3;  /* bit[28-30]:  */
        unsigned int  linedeten : 1;  /* bit[31-31]: Line Detection enable Qu1
                                                     0: line detection disabled
                                                     1: line detection enabled */
    } reg;
} SOC_ISP_SHARPEN_LINEDET_UNION;
#endif
#define SOC_ISP_SHARPEN_LINEDET_linethd1_START   (0)
#define SOC_ISP_SHARPEN_LINEDET_linethd1_END     (4)
#define SOC_ISP_SHARPEN_LINEDET_linethd2_START   (8)
#define SOC_ISP_SHARPEN_LINEDET_linethd2_END     (12)
#define SOC_ISP_SHARPEN_LINEDET_lineamt1_START   (16)
#define SOC_ISP_SHARPEN_LINEDET_lineamt1_END     (27)
#define SOC_ISP_SHARPEN_LINEDET_linedeten_START  (31)
#define SOC_ISP_SHARPEN_LINEDET_linedeten_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_SHARPEN_SHARPCFG_UNION
 结构说明  : SHARPCFG 寄存器结构定义。地址偏移量:0x010，初值:0x00000000，宽度:32
 寄存器说明: sharp configuration (mid-band)
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sharpamt1    : 12; /* bit[0-11] : mid-band sharpen strength Qu12.0 */
        unsigned int  sharpthd1mul : 12; /* bit[12-23]: Convert 1/SharpThd1 to multiplication Qu12.0 */
        unsigned int  sharpthd1    : 8;  /* bit[24-31]: mid-band sharpen strength threshold Qu8.0 */
    } reg;
} SOC_ISP_SHARPEN_SHARPCFG_UNION;
#endif
#define SOC_ISP_SHARPEN_SHARPCFG_sharpamt1_START     (0)
#define SOC_ISP_SHARPEN_SHARPCFG_sharpamt1_END       (11)
#define SOC_ISP_SHARPEN_SHARPCFG_sharpthd1mul_START  (12)
#define SOC_ISP_SHARPEN_SHARPCFG_sharpthd1mul_END    (23)
#define SOC_ISP_SHARPEN_SHARPCFG_sharpthd1_START     (24)
#define SOC_ISP_SHARPEN_SHARPCFG_sharpthd1_END       (31)


/*****************************************************************************
 结构名    : SOC_ISP_SHARPEN_EDGECFG_UNION
 结构说明  : EDGECFG 寄存器结构定义。地址偏移量:0x014，初值:0x00000000，宽度:32
 寄存器说明: edge configuration (high-band)
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  edgeamt1    : 12; /* bit[0-11] : high-band sharpen strength Qu12.0 */
        unsigned int  edgethd1mul : 12; /* bit[12-23]: Convert 1/EdgeThd1 to multiplication Qu12.0 */
        unsigned int  edgethd1    : 8;  /* bit[24-31]: high-band sharpen strength threhold Qu8.0 */
    } reg;
} SOC_ISP_SHARPEN_EDGECFG_UNION;
#endif
#define SOC_ISP_SHARPEN_EDGECFG_edgeamt1_START     (0)
#define SOC_ISP_SHARPEN_EDGECFG_edgeamt1_END       (11)
#define SOC_ISP_SHARPEN_EDGECFG_edgethd1mul_START  (12)
#define SOC_ISP_SHARPEN_EDGECFG_edgethd1mul_END    (23)
#define SOC_ISP_SHARPEN_EDGECFG_edgethd1_START     (24)
#define SOC_ISP_SHARPEN_EDGECFG_edgethd1_END       (31)


/*****************************************************************************
 结构名    : SOC_ISP_SHARPEN_SHOOTCFG_UNION
 结构说明  : SHOOTCFG 寄存器结构定义。地址偏移量:0x018，初值:0x00000000，宽度:32
 寄存器说明: undershoot/overshoot configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  undershootamt : 8;  /* bit[0-7]  : Undershoot amplitude Qu8.0 */
        unsigned int  overshootamt  : 8;  /* bit[8-15] : Overshoot amplitude Qu8.0 */
        unsigned int  reserved      : 16; /* bit[16-31]:  */
    } reg;
} SOC_ISP_SHARPEN_SHOOTCFG_UNION;
#endif
#define SOC_ISP_SHARPEN_SHOOTCFG_undershootamt_START  (0)
#define SOC_ISP_SHARPEN_SHOOTCFG_undershootamt_END    (7)
#define SOC_ISP_SHARPEN_SHOOTCFG_overshootamt_START   (8)
#define SOC_ISP_SHARPEN_SHOOTCFG_overshootamt_END     (15)


/*****************************************************************************
 结构名    : SOC_ISP_SHARPEN_SELCFG_UNION
 结构说明  : SELCFG 寄存器结构定义。地址偏移量:0x01C，初值:0x00000000，宽度:32
 寄存器说明: Filter select configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hbfsel   : 1;  /* bit[0-0] : High-band filter coefficients selection */
        unsigned int  edgecmp  : 1;  /* bit[1-1] : Used to select Sharp1 or YEdge1 to control the High-band sharpen strength. 
                                                   0: select YEdge1
                                                   1: select Sharp1 */
        unsigned int  reserved : 30; /* bit[2-31]:  */
    } reg;
} SOC_ISP_SHARPEN_SELCFG_UNION;
#endif
#define SOC_ISP_SHARPEN_SELCFG_hbfsel_START    (0)
#define SOC_ISP_SHARPEN_SELCFG_hbfsel_END      (0)
#define SOC_ISP_SHARPEN_SELCFG_edgecmp_START   (1)
#define SOC_ISP_SHARPEN_SELCFG_edgecmp_END     (1)


/*****************************************************************************
 结构名    : SOC_ISP_SHARPEN_HCROP_UNION
 结构说明  : HCROP 寄存器结构定义。地址偏移量:0x020，初值:0x00001FFF，宽度:32
 寄存器说明: horizontal cropping configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ihright  : 13; /* bit[0-12] : Input picture horizontal size.There must be an even number of pixels in input so ihright must be an odd number.Qu13.0
                                                    ihsize= ihright+1.Ihsize is supported in the range 4 to 4224( 4 <= ihsize <= 4224 )
                                                    1:2 pixels in input stream
                                                    n:(n+1) pixels in input stream */
        unsigned int  reserved : 19; /* bit[13-31]:  */
    } reg;
} SOC_ISP_SHARPEN_HCROP_UNION;
#endif
#define SOC_ISP_SHARPEN_HCROP_ihright_START   (0)
#define SOC_ISP_SHARPEN_HCROP_ihright_END     (12)


/*****************************************************************************
 结构名    : SOC_ISP_SHARPEN_VCROP_UNION
 结构说明  : VCROP 寄存器结构定义。地址偏移量:0x024，初值:0x00001FFF，宽度:32
 寄存器说明: vertical croppring configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ivbottom : 13; /* bit[0-12] : Input picture vertical size. Qu13.0
                                                    Ivsize= ivbottom+1. Ivsize is supported in the range 4 to 8192 (4 <= ivsize <= 8192)
                                                    0:1 line in input stream
                                                    1:2 lines in input stream
                                                    n:(n+1) lines in input stream */
        unsigned int  reserved : 19; /* bit[13-31]:  */
    } reg;
} SOC_ISP_SHARPEN_VCROP_UNION;
#endif
#define SOC_ISP_SHARPEN_VCROP_ivbottom_START  (0)
#define SOC_ISP_SHARPEN_VCROP_ivbottom_END    (12)






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

#endif /* end of soc_isp_sharpen_interface.h */
