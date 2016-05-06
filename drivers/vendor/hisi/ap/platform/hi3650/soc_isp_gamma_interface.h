/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_isp_gamma_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:21:43
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_ISP_GAMMA.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_ISP_GAMMA_INTERFACE_H__
#define __SOC_ISP_GAMMA_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) GAMMA
 ****************************************************************************/
/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_GAMMA_GAMMA_CONFIG_UNION */
#define SOC_ISP_GAMMA_GAMMA_CONFIG_ADDR(base)         ((base) + (0x0000))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_GAMMA_GAMMA_OUT_ACTIVE_UNION */
#define SOC_ISP_GAMMA_GAMMA_OUT_ACTIVE_ADDR(base)     ((base) + (0x0004))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_GAMMA_GAMMA_OUT_R_0_UNION */
#define SOC_ISP_GAMMA_GAMMA_OUT_R_0_ADDR(base, Range33)  ((base) + (0x0100+0x4*(Range33)))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_GAMMA_GAMMA_OUT_G_0_UNION */
#define SOC_ISP_GAMMA_GAMMA_OUT_G_0_ADDR(base, Range33, Num33)  ((base) + (0x0100+0x4*(Num33)+0x4*(Range33)))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_GAMMA_GAMMA_OUT_B_0_UNION */
#define SOC_ISP_GAMMA_GAMMA_OUT_B_0_ADDR(base, Range33, Num33)  ((base) + (0x0100+0x4*2*(Num33)+0x4*(Range33)))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_GAMMA_GAMMA_OUT_R_1_UNION */
#define SOC_ISP_GAMMA_GAMMA_OUT_R_1_ADDR(base, Range33)  ((base) + (0x0300+0x4*(Range33)))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_GAMMA_GAMMA_OUT_G_1_UNION */
#define SOC_ISP_GAMMA_GAMMA_OUT_G_1_ADDR(base, Range33, Num33)  ((base) + (0x0300+0x4*(Num33)+0x4*(Range33)))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_GAMMA_GAMMA_OUT_B_1_UNION */
#define SOC_ISP_GAMMA_GAMMA_OUT_B_1_ADDR(base, Range33, Num33)  ((base) + (0x0300+0x4*2*(Num33)+0x4*(Range33)))





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
                     (1/1) GAMMA
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_ISP_GAMMA_GAMMA_CONFIG_UNION
 结构说明  : GAMMA_CONFIG 寄存器结构定义。地址偏移量:0x0000，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bypass   : 1;  /* bit[0-0] : Bypass:
                                                   0: the module is active
                                                   1: the module is bypassed */
        unsigned int  reserved : 31; /* bit[1-31]:  */
    } reg;
} SOC_ISP_GAMMA_GAMMA_CONFIG_UNION;
#endif
#define SOC_ISP_GAMMA_GAMMA_CONFIG_bypass_START    (0)
#define SOC_ISP_GAMMA_GAMMA_CONFIG_bypass_END      (0)


/*****************************************************************************
 结构名    : SOC_ISP_GAMMA_GAMMA_OUT_ACTIVE_UNION
 结构说明  : GAMMA_OUT_ACTIVE 寄存器结构定义。地址偏移量:0x0004，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gamma_out_active : 1;  /* bit[0-0] : GAMMA_OUT_active:
                                                           0:GAMMA_OUT_*_0 is used by the HW
                                                           1:GAMMA_OUT_*_1 is used by the HW */
        unsigned int  reserved         : 31; /* bit[1-31]:  */
    } reg;
} SOC_ISP_GAMMA_GAMMA_OUT_ACTIVE_UNION;
#endif
#define SOC_ISP_GAMMA_GAMMA_OUT_ACTIVE_gamma_out_active_START  (0)
#define SOC_ISP_GAMMA_GAMMA_OUT_ACTIVE_gamma_out_active_END    (0)


/*****************************************************************************
 结构名    : SOC_ISP_GAMMA_GAMMA_OUT_R_0_UNION
 结构说明  : GAMMA_OUT_R_0 寄存器结构定义。地址偏移量:0x0100+0x4*(Range33)，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gamma_out_r : 10; /* bit[0-9]  : 10 bits for Gamma_Out values for Red pixels */
        unsigned int  reserved    : 22; /* bit[10-31]:  */
    } reg;
} SOC_ISP_GAMMA_GAMMA_OUT_R_0_UNION;
#endif
#define SOC_ISP_GAMMA_GAMMA_OUT_R_0_gamma_out_r_START  (0)
#define SOC_ISP_GAMMA_GAMMA_OUT_R_0_gamma_out_r_END    (9)


/*****************************************************************************
 结构名    : SOC_ISP_GAMMA_GAMMA_OUT_G_0_UNION
 结构说明  : GAMMA_OUT_G_0 寄存器结构定义。地址偏移量:0x0100+0x4*(Num33)+0x4*(Range33)，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gamma_out_g : 10; /* bit[0-9]  : 10 bits for Gamma_Out values for green pixels */
        unsigned int  reserved    : 22; /* bit[10-31]:  */
    } reg;
} SOC_ISP_GAMMA_GAMMA_OUT_G_0_UNION;
#endif
#define SOC_ISP_GAMMA_GAMMA_OUT_G_0_gamma_out_g_START  (0)
#define SOC_ISP_GAMMA_GAMMA_OUT_G_0_gamma_out_g_END    (9)


/*****************************************************************************
 结构名    : SOC_ISP_GAMMA_GAMMA_OUT_B_0_UNION
 结构说明  : GAMMA_OUT_B_0 寄存器结构定义。地址偏移量:0x0100+0x4*2*(Num33)+0x4*(Range33)，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gamma_out_b : 10; /* bit[0-9]  : 10 bits for Gamma_Out values for blue pixels */
        unsigned int  reserved    : 22; /* bit[10-31]:  */
    } reg;
} SOC_ISP_GAMMA_GAMMA_OUT_B_0_UNION;
#endif
#define SOC_ISP_GAMMA_GAMMA_OUT_B_0_gamma_out_b_START  (0)
#define SOC_ISP_GAMMA_GAMMA_OUT_B_0_gamma_out_b_END    (9)


/*****************************************************************************
 结构名    : SOC_ISP_GAMMA_GAMMA_OUT_R_1_UNION
 结构说明  : GAMMA_OUT_R_1 寄存器结构定义。地址偏移量:0x0300+0x4*(Range33)，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gamma_out_r : 10; /* bit[0-9]  : 10 bits for Gamma_Out values for Red pixels */
        unsigned int  reserved    : 22; /* bit[10-31]:  */
    } reg;
} SOC_ISP_GAMMA_GAMMA_OUT_R_1_UNION;
#endif
#define SOC_ISP_GAMMA_GAMMA_OUT_R_1_gamma_out_r_START  (0)
#define SOC_ISP_GAMMA_GAMMA_OUT_R_1_gamma_out_r_END    (9)


/*****************************************************************************
 结构名    : SOC_ISP_GAMMA_GAMMA_OUT_G_1_UNION
 结构说明  : GAMMA_OUT_G_1 寄存器结构定义。地址偏移量:0x0300+0x4*(Num33)+0x4*(Range33)，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gamma_out_g : 10; /* bit[0-9]  : 10 bits for Gamma_Out values for green pixels */
        unsigned int  reserved    : 22; /* bit[10-31]:  */
    } reg;
} SOC_ISP_GAMMA_GAMMA_OUT_G_1_UNION;
#endif
#define SOC_ISP_GAMMA_GAMMA_OUT_G_1_gamma_out_g_START  (0)
#define SOC_ISP_GAMMA_GAMMA_OUT_G_1_gamma_out_g_END    (9)


/*****************************************************************************
 结构名    : SOC_ISP_GAMMA_GAMMA_OUT_B_1_UNION
 结构说明  : GAMMA_OUT_B_1 寄存器结构定义。地址偏移量:0x0300+0x4*2*(Num33)+0x4*(Range33)，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gamma_out_b : 10; /* bit[0-9]  : 10 bits for Gamma_Out values for blue pixels */
        unsigned int  reserved    : 22; /* bit[10-31]:  */
    } reg;
} SOC_ISP_GAMMA_GAMMA_OUT_B_1_UNION;
#endif
#define SOC_ISP_GAMMA_GAMMA_OUT_B_1_gamma_out_b_START  (0)
#define SOC_ISP_GAMMA_GAMMA_OUT_B_1_gamma_out_b_END    (9)






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

#endif /* end of soc_isp_gamma_interface.h */
