/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_isp_prescaler_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:22:01
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_ISP_PRESCALER.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_ISP_PRESCALER_INTERFACE_H__
#define __SOC_ISP_PRESCALER_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) PRESCALER
 ****************************************************************************/
/* 寄存器说明：horizontal cropping configuration
   位域定义UNION结构:  SOC_ISP_PRESCALER_HCROP_UNION */
#define SOC_ISP_PRESCALER_HCROP_ADDR(base)            ((base) + (0x0000))

/* 寄存器说明：vertical cropping configuration
   位域定义UNION结构:  SOC_ISP_PRESCALER_VCROP_UNION */
#define SOC_ISP_PRESCALER_VCROP_ADDR(base)            ((base) + (0x0004))

/* 寄存器说明：Prescaler Mode
   位域定义UNION结构:  SOC_ISP_PRESCALER_MODE_UNION */
#define SOC_ISP_PRESCALER_MODE_ADDR(base)             ((base) + (0x0008))





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
                     (1/1) PRESCALER
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_ISP_PRESCALER_HCROP_UNION
 结构说明  : HCROP 寄存器结构定义。地址偏移量:0x0000，初值:0x00000000，宽度:32
 寄存器说明: horizontal cropping configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ihright1 : 13; /* bit[0-12] : Position of last pixel in active area of picture from H-GKM1 (left picture).It should be set according to left picture size (=ihsize1-1).When there is merge 2 extra pixels should be received at input right border. Qu13.0
                                                    0x1FFF means no crop
                                                    otherwise:
                                                    0:first pixel in input stream
                                                    1:second pixel in input stream
                                                    n:(n+1) th pixel in input stream */
        unsigned int  reserved_0: 3;  /* bit[13-15]:  */
        unsigned int  ihright2 : 13; /* bit[16-28]: Position of last pixel in active area of picture from H-GKM2 (right picture).It should be set according to right picture size (=hsize2-1) Qu13.0
                                                    0x1FFF means no crop
                                                    otherwise:
                                                    0:first pixel in input stream
                                                    1:second pixel in input stream
                                                    n:(n+1) th pixel in input stream */
        unsigned int  ihleft2  : 2;  /* bit[29-30]: Position of first pixel in active area of right picture ( from GKM-2) Qu2.0 . 0 means no crop. It should be set to 0 when no merge- It should be set to 1 in merge case ( two extra pixels received at input left border )
                                                    0:first pixel is pixel 0
                                                    1:first pixel is pixel 1
                                                    n:first pixel is pixel #n */
        unsigned int  reserved_1: 1;  /* bit[31-31]:  */
    } reg;
} SOC_ISP_PRESCALER_HCROP_UNION;
#endif
#define SOC_ISP_PRESCALER_HCROP_ihright1_START  (0)
#define SOC_ISP_PRESCALER_HCROP_ihright1_END    (12)
#define SOC_ISP_PRESCALER_HCROP_ihright2_START  (16)
#define SOC_ISP_PRESCALER_HCROP_ihright2_END    (28)
#define SOC_ISP_PRESCALER_HCROP_ihleft2_START   (29)
#define SOC_ISP_PRESCALER_HCROP_ihleft2_END     (30)


/*****************************************************************************
 结构名    : SOC_ISP_PRESCALER_VCROP_UNION
 结构说明  : VCROP 寄存器结构定义。地址偏移量:0x0004，初值:0x00000000，宽度:32
 寄存器说明: vertical cropping configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ivbottom : 13; /* bit[0-12] : Position of last line in active area of picture. Qu13.0
                                                    0x1FFF means no crop
                                                    otherwise:
                                                    0:first line in input stream
                                                    1:second line in input stream
                                                    n:(n+1) th line in input stream */
        unsigned int  reserved : 19; /* bit[13-31]:  */
    } reg;
} SOC_ISP_PRESCALER_VCROP_UNION;
#endif
#define SOC_ISP_PRESCALER_VCROP_ivbottom_START  (0)
#define SOC_ISP_PRESCALER_VCROP_ivbottom_END    (12)


/*****************************************************************************
 结构名    : SOC_ISP_PRESCALER_MODE_UNION
 结构说明  : MODE 寄存器结构定义。地址偏移量:0x0008，初值:0x00000004，宽度:32
 寄存器说明: Prescaler Mode
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  input_sel : 2;  /* bit[0-1] : Selection Frame Merger Input
                                                    00, 01: H-GKM1 is selected, H-GKM2 is not used- 
                                                    10:H-GKM2 is selected and H-GKM1 is not used
                                                    11: both H-GKM1 and H-GKM2 are selected for merge.  */
        unsigned int  bypass    : 1;  /* bit[2-2] : Bypass mode configuration:
                                                    0: No bypass
                                                    1: Bypass mode */
        unsigned int  reserved  : 29; /* bit[3-31]:  */
    } reg;
} SOC_ISP_PRESCALER_MODE_UNION;
#endif
#define SOC_ISP_PRESCALER_MODE_input_sel_START  (0)
#define SOC_ISP_PRESCALER_MODE_input_sel_END    (1)
#define SOC_ISP_PRESCALER_MODE_bypass_START     (2)
#define SOC_ISP_PRESCALER_MODE_bypass_END       (2)






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

#endif /* end of soc_isp_prescaler_interface.h */
