/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_isp_fbcraw_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-04-08 11:46:43
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年4月8日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_ISP_FBCRAW.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_ISP_FBCRAW_INTERFACE_H__
#define __SOC_ISP_FBCRAW_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) FBCRAW
 ****************************************************************************/
/* 寄存器说明：configuration1 of the FBC base function.
   位域定义UNION结构:  SOC_ISP_FBCRAW_FBC_CONFIG1_UNION */
#define SOC_ISP_FBCRAW_FBC_CONFIG1_ADDR(base)         ((base) + (0x0000))

/* 寄存器说明：configuration2 of the FBC base function.
   位域定义UNION结构:  SOC_ISP_FBCRAW_FBC_CONFIG2_UNION */
#define SOC_ISP_FBCRAW_FBC_CONFIG2_ADDR(base)         ((base) + (0x0004))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_FBCRAW_TEEE_UNION */
#define SOC_ISP_FBCRAW_TEEE_ADDR(base)                ((base) + (0x2000))





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
                     (1/1) FBCRAW
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_ISP_FBCRAW_FBC_CONFIG1_UNION
 结构说明  : FBC_CONFIG1 寄存器结构定义。地址偏移量:0x0000，初值:0x00000001，宽度:32
 寄存器说明: configuration1 of the FBC base function.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bypass     : 1;  /* bit[0-0]  : Bypass:
                                                      0: the module is active
                                                      1: the module is bypassed
                                                      the configuration is taken into account on a SOF.
                                                      (Same HW behavior as RW_SHADOW). */
        unsigned int  seg_size   : 1;  /* bit[1-1]  : Segment Size:
                                                      0: 64 pixels
                                                      1: 128 pixels. */
        unsigned int  pix_size   : 2;  /* bit[2-3]  : Pixel Size:
                                                      0: 10 bits
                                                      1: 12 bits
                                                      2,3: 14 bits. */
        unsigned int  dualmode   : 1;  /* bit[4-4]  : 0: single source mode
                                                      1: dual source mode. */
        unsigned int  reserved_0 : 11; /* bit[5-15] :  */
        unsigned int  line_width : 13; /* bit[16-28]: Line width - 1
                                                      [Note]
                                                      line_width <= 4224 - 1
                                                      line_witdh >= 192*(seg_size + 1) - 1
                                                      [end]. */
        unsigned int  reserved_1 : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_FBCRAW_FBC_CONFIG1_UNION;
#endif
#define SOC_ISP_FBCRAW_FBC_CONFIG1_bypass_START      (0)
#define SOC_ISP_FBCRAW_FBC_CONFIG1_bypass_END        (0)
#define SOC_ISP_FBCRAW_FBC_CONFIG1_seg_size_START    (1)
#define SOC_ISP_FBCRAW_FBC_CONFIG1_seg_size_END      (1)
#define SOC_ISP_FBCRAW_FBC_CONFIG1_pix_size_START    (2)
#define SOC_ISP_FBCRAW_FBC_CONFIG1_pix_size_END      (3)
#define SOC_ISP_FBCRAW_FBC_CONFIG1_dualmode_START    (4)
#define SOC_ISP_FBCRAW_FBC_CONFIG1_dualmode_END      (4)
#define SOC_ISP_FBCRAW_FBC_CONFIG1_line_width_START  (16)
#define SOC_ISP_FBCRAW_FBC_CONFIG1_line_width_END    (28)


/*****************************************************************************
 结构名    : SOC_ISP_FBCRAW_FBC_CONFIG2_UNION
 结构说明  : FBC_CONFIG2 寄存器结构定义。地址偏移量:0x0004，初值:0x00460020，宽度:32
 寄存器说明: configuration2 of the FBC base function.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  initqp    : 6;  /* bit[0-5]  : Initial QP. */
        unsigned int  reserved_0: 10; /* bit[6-15] :  */
        unsigned int  bit_thres : 8;  /* bit[16-23]: internal threshold. */
        unsigned int  reserved_1: 8;  /* bit[24-31]:  */
    } reg;
} SOC_ISP_FBCRAW_FBC_CONFIG2_UNION;
#endif
#define SOC_ISP_FBCRAW_FBC_CONFIG2_initqp_START     (0)
#define SOC_ISP_FBCRAW_FBC_CONFIG2_initqp_END       (5)
#define SOC_ISP_FBCRAW_FBC_CONFIG2_bit_thres_START  (16)
#define SOC_ISP_FBCRAW_FBC_CONFIG2_bit_thres_END    (23)


/*****************************************************************************
 结构名    : SOC_ISP_FBCRAW_TEEE_UNION
 结构说明  : TEEE 寄存器结构定义。地址偏移量:0x2000，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cvv : 2;  /* bit[0-1] :  */
        unsigned int  aaa : 30; /* bit[2-31]:  */
    } reg;
} SOC_ISP_FBCRAW_TEEE_UNION;
#endif
#define SOC_ISP_FBCRAW_TEEE_cvv_START  (0)
#define SOC_ISP_FBCRAW_TEEE_cvv_END    (1)
#define SOC_ISP_FBCRAW_TEEE_aaa_START  (2)
#define SOC_ISP_FBCRAW_TEEE_aaa_END    (31)






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

#endif /* end of soc_isp_fbcraw_interface.h */
