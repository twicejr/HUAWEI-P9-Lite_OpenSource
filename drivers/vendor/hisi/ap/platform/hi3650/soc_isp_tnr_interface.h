/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_isp_tnr_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:22:10
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_ISP_TNR.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_ISP_TNR_INTERFACE_H__
#define __SOC_ISP_TNR_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) TNR
 ****************************************************************************/
/* 寄存器说明：TNR bypass register
   位域定义UNION结构:  SOC_ISP_TNR_CONFIG_UNION */
#define SOC_ISP_TNR_CONFIG_ADDR(base)                 ((base) + (0x000))

/* 寄存器说明：Threshold configuration
   位域定义UNION结构:  SOC_ISP_TNR_THD_CFG_UNION */
#define SOC_ISP_TNR_THD_CFG_ADDR(base)                ((base) + (0x004))

/* 寄存器说明：Slope and max local offset configuration
   位域定义UNION结构:  SOC_ISP_TNR_SLP_OFST_CFG_UNION */
#define SOC_ISP_TNR_SLP_OFST_CFG_ADDR(base)           ((base) + (0x008))

/* 寄存器说明：Input size configuration
   位域定义UNION结构:  SOC_ISP_TNR_CROP_UNION */
#define SOC_ISP_TNR_CROP_ADDR(base)                   ((base) + (0x00C))

/* 寄存器说明：Luma table coeff
   位域定义UNION结构:  SOC_ISP_TNR_LUMAA_UNION */
#define SOC_ISP_TNR_LUMAA_ADDR(base)                  ((base) + (0x010))

/* 寄存器说明：Luma table coeff
   位域定义UNION结构:  SOC_ISP_TNR_LUMAB_UNION */
#define SOC_ISP_TNR_LUMAB_ADDR(base)                  ((base) + (0x014))

/* 寄存器说明：Luma table coeff
   位域定义UNION结构:  SOC_ISP_TNR_LUMAC_UNION */
#define SOC_ISP_TNR_LUMAC_ADDR(base)                  ((base) + (0x018))

/* 寄存器说明：Luma table coeff
   位域定义UNION结构:  SOC_ISP_TNR_LUMAD_UNION */
#define SOC_ISP_TNR_LUMAD_ADDR(base)                  ((base) + (0x01C))

/* 寄存器说明：Luma table coeff
   位域定义UNION结构:  SOC_ISP_TNR_LUMAE_UNION */
#define SOC_ISP_TNR_LUMAE_ADDR(base)                  ((base) + (0x020))

/* 寄存器说明：Motion table UV coeff
   位域定义UNION结构:  SOC_ISP_TNR_MOTIONUVA_UNION */
#define SOC_ISP_TNR_MOTIONUVA_ADDR(base)              ((base) + (0x024))

/* 寄存器说明：Motion table UV coeff
   位域定义UNION结构:  SOC_ISP_TNR_MOTIONUVB_UNION */
#define SOC_ISP_TNR_MOTIONUVB_ADDR(base)              ((base) + (0x028))

/* 寄存器说明：Motion table UV coeff
   位域定义UNION结构:  SOC_ISP_TNR_MOTIONUVC_UNION */
#define SOC_ISP_TNR_MOTIONUVC_ADDR(base)              ((base) + (0x02C))

/* 寄存器说明：Motion table UV coeff
   位域定义UNION结构:  SOC_ISP_TNR_MOTIONUVD_UNION */
#define SOC_ISP_TNR_MOTIONUVD_ADDR(base)              ((base) + (0x030))

/* 寄存器说明：Motion table UV coeff
   位域定义UNION结构:  SOC_ISP_TNR_MOTIONUVE_UNION */
#define SOC_ISP_TNR_MOTIONUVE_ADDR(base)              ((base) + (0x034))

/* 寄存器说明：Motion table UV coeff
   位域定义UNION结构:  SOC_ISP_TNR_MOTIONUVF_UNION */
#define SOC_ISP_TNR_MOTIONUVF_ADDR(base)              ((base) + (0x038))

/* 寄存器说明：Motion table UV coeff
   位域定义UNION结构:  SOC_ISP_TNR_MOTIONUVG_UNION */
#define SOC_ISP_TNR_MOTIONUVG_ADDR(base)              ((base) + (0x03C))

/* 寄存器说明：Motion table UV coeff
   位域定义UNION结构:  SOC_ISP_TNR_MOTIONUVH_UNION */
#define SOC_ISP_TNR_MOTIONUVH_ADDR(base)              ((base) + (0x040))

/* 寄存器说明：Motion table Y coeff
   位域定义UNION结构:  SOC_ISP_TNR_MOTIONA_UNION */
#define SOC_ISP_TNR_MOTIONA_ADDR(base)                ((base) + (0x044))

/* 寄存器说明：Motion table Y coeff
   位域定义UNION结构:  SOC_ISP_TNR_MOTIONB_UNION */
#define SOC_ISP_TNR_MOTIONB_ADDR(base)                ((base) + (0x048))

/* 寄存器说明：Motion table Y coeff
   位域定义UNION结构:  SOC_ISP_TNR_MOTIONC_UNION */
#define SOC_ISP_TNR_MOTIONC_ADDR(base)                ((base) + (0x04C))

/* 寄存器说明：Motion table Y coeff
   位域定义UNION结构:  SOC_ISP_TNR_MOTIOND_UNION */
#define SOC_ISP_TNR_MOTIOND_ADDR(base)                ((base) + (0x050))

/* 寄存器说明：Motion table Y coeff
   位域定义UNION结构:  SOC_ISP_TNR_MOTIONE_UNION */
#define SOC_ISP_TNR_MOTIONE_ADDR(base)                ((base) + (0x054))

/* 寄存器说明：Motion table Y coeff
   位域定义UNION结构:  SOC_ISP_TNR_MOTIONF_UNION */
#define SOC_ISP_TNR_MOTIONF_ADDR(base)                ((base) + (0x058))

/* 寄存器说明：Motion table Y coeff
   位域定义UNION结构:  SOC_ISP_TNR_MOTIONG_UNION */
#define SOC_ISP_TNR_MOTIONG_ADDR(base)                ((base) + (0x05C))

/* 寄存器说明：Motion table Y coeff
   位域定义UNION结构:  SOC_ISP_TNR_MOTIONH_UNION */
#define SOC_ISP_TNR_MOTIONH_ADDR(base)                ((base) + (0x060))

/* 寄存器说明：used to force the clock which is generally controlled by HW
   位域定义UNION结构:  SOC_ISP_TNR_FORCE_CLK_ON_CFG_UNION */
#define SOC_ISP_TNR_FORCE_CLK_ON_CFG_ADDR(base)       ((base) + (0x070))





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
                     (1/1) TNR
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_ISP_TNR_CONFIG_UNION
 结构说明  : CONFIG 寄存器结构定义。地址偏移量:0x000，初值:0x00000001，宽度:32
 寄存器说明: TNR bypass register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bypass   : 1;  /* bit[0-0] : Configure TNR bypass.This register is actually shadowed using state machine.
                                                   0 : TNR is not bypassed
                                                   1: TNR is bypassed */
        unsigned int  reserved : 31; /* bit[1-31]:  */
    } reg;
} SOC_ISP_TNR_CONFIG_UNION;
#endif
#define SOC_ISP_TNR_CONFIG_bypass_START    (0)
#define SOC_ISP_TNR_CONFIG_bypass_END      (0)


/*****************************************************************************
 结构名    : SOC_ISP_TNR_THD_CFG_UNION
 结构说明  : THD_CFG 寄存器结构定义。地址偏移量:0x004，初值:0x00000000，宽度:32
 寄存器说明: Threshold configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  alpha_thd  : 8;  /* bit[0-7]  : alpha threshold as defined in algo spec Qu8.0 */
        unsigned int  motion_thd : 8;  /* bit[8-15] : Motion threshold as defined in algo spec Qu8.0 */
        unsigned int  global_thd : 11; /* bit[16-26]: Global threshold as defined in algo spec Qu11.0 */
        unsigned int  reserved   : 5;  /* bit[27-31]:  */
    } reg;
} SOC_ISP_TNR_THD_CFG_UNION;
#endif
#define SOC_ISP_TNR_THD_CFG_alpha_thd_START   (0)
#define SOC_ISP_TNR_THD_CFG_alpha_thd_END     (7)
#define SOC_ISP_TNR_THD_CFG_motion_thd_START  (8)
#define SOC_ISP_TNR_THD_CFG_motion_thd_END    (15)
#define SOC_ISP_TNR_THD_CFG_global_thd_START  (16)
#define SOC_ISP_TNR_THD_CFG_global_thd_END    (26)


/*****************************************************************************
 结构名    : SOC_ISP_TNR_SLP_OFST_CFG_UNION
 结构说明  : SLP_OFST_CFG 寄存器结构定义。地址偏移量:0x008，初值:0x00000000，宽度:32
 寄存器说明: Slope and max local offset configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  weight_slope     : 2;  /* bit[0-1]  : weight slope as defined in algo spec Qu2.0  */
        unsigned int  motion_slope     : 6;  /* bit[2-7]  : Motion slope as defined in algo spec Qs6.0 */
        unsigned int  reserved_0       : 8;  /* bit[8-15] :  */
        unsigned int  local_offset_max : 8;  /* bit[16-23]: max local offset as defined in algo spec- Qu8.0 */
        unsigned int  reserved_1       : 8;  /* bit[24-31]:  */
    } reg;
} SOC_ISP_TNR_SLP_OFST_CFG_UNION;
#endif
#define SOC_ISP_TNR_SLP_OFST_CFG_weight_slope_START      (0)
#define SOC_ISP_TNR_SLP_OFST_CFG_weight_slope_END        (1)
#define SOC_ISP_TNR_SLP_OFST_CFG_motion_slope_START      (2)
#define SOC_ISP_TNR_SLP_OFST_CFG_motion_slope_END        (7)
#define SOC_ISP_TNR_SLP_OFST_CFG_local_offset_max_START  (16)
#define SOC_ISP_TNR_SLP_OFST_CFG_local_offset_max_END    (23)


/*****************************************************************************
 结构名    : SOC_ISP_TNR_CROP_UNION
 结构说明  : CROP 寄存器结构定义。地址偏移量:0x00C，初值:0x00000000，宽度:32
 寄存器说明: Input size configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ihright  : 13; /* bit[0-12] : Input picture horizontal size-1.There must be an even number of pixels in input so ihright must be an odd number.Qu13.0
                                                    
                                                    1:2 pixels in input stream
                                                    n:(n+1) pixels in input stream */
        unsigned int  reserved_0: 3;  /* bit[13-15]:  */
        unsigned int  ivbottom : 13; /* bit[16-28]: Input picture vertical size-1. Qu13.0
                                                    
                                                    0:1 line in input stream
                                                    1:2 lines in input stream
                                                    n:(n+1) lines in input stream */
        unsigned int  reserved_1: 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_TNR_CROP_UNION;
#endif
#define SOC_ISP_TNR_CROP_ihright_START   (0)
#define SOC_ISP_TNR_CROP_ihright_END     (12)
#define SOC_ISP_TNR_CROP_ivbottom_START  (16)
#define SOC_ISP_TNR_CROP_ivbottom_END    (28)


/*****************************************************************************
 结构名    : SOC_ISP_TNR_LUMAA_UNION
 结构说明  : LUMAA 寄存器结构定义。地址偏移量:0x010，初值:0x00000000，宽度:32
 寄存器说明: Luma table coeff
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  luma0 : 8;  /* bit[0-7]  : Luma coefficient-Qu8.0
                                                 Luma0=ltb[0] */
        unsigned int  luma1 : 8;  /* bit[8-15] : Luma coefficient-Qu8.0
                                                 Luma1=ltb[1] */
        unsigned int  luma2 : 8;  /* bit[16-23]: Luma coefficient-Qu8.0
                                                 Luma2=ltb[2] */
        unsigned int  luma3 : 8;  /* bit[24-31]: Luma coefficient-Qu8.0
                                                 Luma3=ltb[3] */
    } reg;
} SOC_ISP_TNR_LUMAA_UNION;
#endif
#define SOC_ISP_TNR_LUMAA_luma0_START  (0)
#define SOC_ISP_TNR_LUMAA_luma0_END    (7)
#define SOC_ISP_TNR_LUMAA_luma1_START  (8)
#define SOC_ISP_TNR_LUMAA_luma1_END    (15)
#define SOC_ISP_TNR_LUMAA_luma2_START  (16)
#define SOC_ISP_TNR_LUMAA_luma2_END    (23)
#define SOC_ISP_TNR_LUMAA_luma3_START  (24)
#define SOC_ISP_TNR_LUMAA_luma3_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_TNR_LUMAB_UNION
 结构说明  : LUMAB 寄存器结构定义。地址偏移量:0x014，初值:0x00000000，宽度:32
 寄存器说明: Luma table coeff
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  luma4 : 8;  /* bit[0-7]  : Luma coefficient-Qu8.0
                                                 Luma4=ltb[4] */
        unsigned int  luma5 : 8;  /* bit[8-15] : Luma coefficient-Qu8.0
                                                 Luma5=ltb[5] */
        unsigned int  luma6 : 8;  /* bit[16-23]: Luma coefficient-Qu8.0
                                                 Luma6=ltb[6] */
        unsigned int  luma7 : 8;  /* bit[24-31]: Luma coefficient-Qu8.0
                                                 Luma7=ltb[7] */
    } reg;
} SOC_ISP_TNR_LUMAB_UNION;
#endif
#define SOC_ISP_TNR_LUMAB_luma4_START  (0)
#define SOC_ISP_TNR_LUMAB_luma4_END    (7)
#define SOC_ISP_TNR_LUMAB_luma5_START  (8)
#define SOC_ISP_TNR_LUMAB_luma5_END    (15)
#define SOC_ISP_TNR_LUMAB_luma6_START  (16)
#define SOC_ISP_TNR_LUMAB_luma6_END    (23)
#define SOC_ISP_TNR_LUMAB_luma7_START  (24)
#define SOC_ISP_TNR_LUMAB_luma7_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_TNR_LUMAC_UNION
 结构说明  : LUMAC 寄存器结构定义。地址偏移量:0x018，初值:0x00000000，宽度:32
 寄存器说明: Luma table coeff
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  luma8  : 8;  /* bit[0-7]  : Luma coefficient-Qu8.0
                                                  Luma8=ltb[8] */
        unsigned int  luma9  : 8;  /* bit[8-15] : Luma coefficient-Qu8.0
                                                  Luma9=ltb[9] */
        unsigned int  luma10 : 8;  /* bit[16-23]: Luma coefficient-Qu8.0
                                                  Luma10=ltb[10] */
        unsigned int  luma11 : 8;  /* bit[24-31]: Luma coefficient-Qu8.0
                                                  Luma11=ltb[11] */
    } reg;
} SOC_ISP_TNR_LUMAC_UNION;
#endif
#define SOC_ISP_TNR_LUMAC_luma8_START   (0)
#define SOC_ISP_TNR_LUMAC_luma8_END     (7)
#define SOC_ISP_TNR_LUMAC_luma9_START   (8)
#define SOC_ISP_TNR_LUMAC_luma9_END     (15)
#define SOC_ISP_TNR_LUMAC_luma10_START  (16)
#define SOC_ISP_TNR_LUMAC_luma10_END    (23)
#define SOC_ISP_TNR_LUMAC_luma11_START  (24)
#define SOC_ISP_TNR_LUMAC_luma11_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_TNR_LUMAD_UNION
 结构说明  : LUMAD 寄存器结构定义。地址偏移量:0x01C，初值:0x00000000，宽度:32
 寄存器说明: Luma table coeff
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  luma12 : 8;  /* bit[0-7]  : Luma coefficient-Qu8.0
                                                  Luma12=ltb[12] */
        unsigned int  luma13 : 8;  /* bit[8-15] : Luma coefficient-Qu8.0
                                                  Luma13=ltb[13] */
        unsigned int  luma14 : 8;  /* bit[16-23]: Luma coefficient-Qu8.0
                                                  Luma14=ltb[14] */
        unsigned int  luma15 : 8;  /* bit[24-31]: Luma coefficient-Qu8.0
                                                  Luma15=ltb[15] */
    } reg;
} SOC_ISP_TNR_LUMAD_UNION;
#endif
#define SOC_ISP_TNR_LUMAD_luma12_START  (0)
#define SOC_ISP_TNR_LUMAD_luma12_END    (7)
#define SOC_ISP_TNR_LUMAD_luma13_START  (8)
#define SOC_ISP_TNR_LUMAD_luma13_END    (15)
#define SOC_ISP_TNR_LUMAD_luma14_START  (16)
#define SOC_ISP_TNR_LUMAD_luma14_END    (23)
#define SOC_ISP_TNR_LUMAD_luma15_START  (24)
#define SOC_ISP_TNR_LUMAD_luma15_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_TNR_LUMAE_UNION
 结构说明  : LUMAE 寄存器结构定义。地址偏移量:0x020，初值:0x00000000，宽度:32
 寄存器说明: Luma table coeff
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  luma16   : 8;  /* bit[0-7] : Luma coefficient-Qu8.0
                                                   Luma16=ltb[16] */
        unsigned int  reserved : 24; /* bit[8-31]:  */
    } reg;
} SOC_ISP_TNR_LUMAE_UNION;
#endif
#define SOC_ISP_TNR_LUMAE_luma16_START    (0)
#define SOC_ISP_TNR_LUMAE_luma16_END      (7)


/*****************************************************************************
 结构名    : SOC_ISP_TNR_MOTIONUVA_UNION
 结构说明  : MOTIONUVA 寄存器结构定义。地址偏移量:0x024，初值:0x00000000，宽度:32
 寄存器说明: Motion table UV coeff
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  motionuv0 : 8;  /* bit[0-7]  : Motion coefficient-Qu8.0
                                                     Motionuv0=mtbuv[0] */
        unsigned int  motionuv1 : 8;  /* bit[8-15] : Motion coefficient-Qu8.0
                                                     Motionuv1=mtbuv[1] */
        unsigned int  motionuv2 : 8;  /* bit[16-23]: Motion coefficient-Qu8.0
                                                     Motionuv2=mtbuv[2] */
        unsigned int  motionuv3 : 8;  /* bit[24-31]: Motion coefficient-Qu8.0
                                                     Motionuv3=mtbuv[3] */
    } reg;
} SOC_ISP_TNR_MOTIONUVA_UNION;
#endif
#define SOC_ISP_TNR_MOTIONUVA_motionuv0_START  (0)
#define SOC_ISP_TNR_MOTIONUVA_motionuv0_END    (7)
#define SOC_ISP_TNR_MOTIONUVA_motionuv1_START  (8)
#define SOC_ISP_TNR_MOTIONUVA_motionuv1_END    (15)
#define SOC_ISP_TNR_MOTIONUVA_motionuv2_START  (16)
#define SOC_ISP_TNR_MOTIONUVA_motionuv2_END    (23)
#define SOC_ISP_TNR_MOTIONUVA_motionuv3_START  (24)
#define SOC_ISP_TNR_MOTIONUVA_motionuv3_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_TNR_MOTIONUVB_UNION
 结构说明  : MOTIONUVB 寄存器结构定义。地址偏移量:0x028，初值:0x00000000，宽度:32
 寄存器说明: Motion table UV coeff
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  motionuv4 : 8;  /* bit[0-7]  : Motion coefficient-Qu8.0
                                                     Motionuv4=mtbuv[4] */
        unsigned int  motionuv5 : 8;  /* bit[8-15] : Motion coefficient-Qu8.0
                                                     Motionuv5=mtbuv[5] */
        unsigned int  motionuv6 : 8;  /* bit[16-23]: Motion coefficient-Qu8.0
                                                     Motionuv6=mtbuv[6] */
        unsigned int  motionuv7 : 8;  /* bit[24-31]: Motion coefficient-Qu8.0
                                                     Motionuv7=mtbuv[7] */
    } reg;
} SOC_ISP_TNR_MOTIONUVB_UNION;
#endif
#define SOC_ISP_TNR_MOTIONUVB_motionuv4_START  (0)
#define SOC_ISP_TNR_MOTIONUVB_motionuv4_END    (7)
#define SOC_ISP_TNR_MOTIONUVB_motionuv5_START  (8)
#define SOC_ISP_TNR_MOTIONUVB_motionuv5_END    (15)
#define SOC_ISP_TNR_MOTIONUVB_motionuv6_START  (16)
#define SOC_ISP_TNR_MOTIONUVB_motionuv6_END    (23)
#define SOC_ISP_TNR_MOTIONUVB_motionuv7_START  (24)
#define SOC_ISP_TNR_MOTIONUVB_motionuv7_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_TNR_MOTIONUVC_UNION
 结构说明  : MOTIONUVC 寄存器结构定义。地址偏移量:0x02C，初值:0x00000000，宽度:32
 寄存器说明: Motion table UV coeff
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  motionuv8  : 8;  /* bit[0-7]  : Motion coefficient-Qu8.0
                                                      Motionuv8=mtbuv[8] */
        unsigned int  motionuv9  : 8;  /* bit[8-15] : Motion coefficient-Qu8.0
                                                      Motionuv9=mtbuv[9] */
        unsigned int  motionuv10 : 8;  /* bit[16-23]: Motion coefficient-Qu8.0
                                                      Motionuv10=mtbuv[10] */
        unsigned int  motionuv11 : 8;  /* bit[24-31]: Motion coefficient-Qu8.0
                                                      Motionuv11=mtbuv[11] */
    } reg;
} SOC_ISP_TNR_MOTIONUVC_UNION;
#endif
#define SOC_ISP_TNR_MOTIONUVC_motionuv8_START   (0)
#define SOC_ISP_TNR_MOTIONUVC_motionuv8_END     (7)
#define SOC_ISP_TNR_MOTIONUVC_motionuv9_START   (8)
#define SOC_ISP_TNR_MOTIONUVC_motionuv9_END     (15)
#define SOC_ISP_TNR_MOTIONUVC_motionuv10_START  (16)
#define SOC_ISP_TNR_MOTIONUVC_motionuv10_END    (23)
#define SOC_ISP_TNR_MOTIONUVC_motionuv11_START  (24)
#define SOC_ISP_TNR_MOTIONUVC_motionuv11_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_TNR_MOTIONUVD_UNION
 结构说明  : MOTIONUVD 寄存器结构定义。地址偏移量:0x030，初值:0x00000000，宽度:32
 寄存器说明: Motion table UV coeff
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  motionuv12 : 8;  /* bit[0-7]  : Motion coefficient-Qu8.0
                                                      Motionuv12=mtbuv[12] */
        unsigned int  motionuv13 : 8;  /* bit[8-15] : Motion coefficient-Qu8.0
                                                      Motionuv13=mtbuv[13] */
        unsigned int  motionuv14 : 8;  /* bit[16-23]: Motion coefficient-Qu8.0
                                                      Motionuv14=mtbuv[14] */
        unsigned int  motionuv15 : 8;  /* bit[24-31]: Motion coefficient-Qu8.0
                                                      Motionuv15=mtbuv[15] */
    } reg;
} SOC_ISP_TNR_MOTIONUVD_UNION;
#endif
#define SOC_ISP_TNR_MOTIONUVD_motionuv12_START  (0)
#define SOC_ISP_TNR_MOTIONUVD_motionuv12_END    (7)
#define SOC_ISP_TNR_MOTIONUVD_motionuv13_START  (8)
#define SOC_ISP_TNR_MOTIONUVD_motionuv13_END    (15)
#define SOC_ISP_TNR_MOTIONUVD_motionuv14_START  (16)
#define SOC_ISP_TNR_MOTIONUVD_motionuv14_END    (23)
#define SOC_ISP_TNR_MOTIONUVD_motionuv15_START  (24)
#define SOC_ISP_TNR_MOTIONUVD_motionuv15_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_TNR_MOTIONUVE_UNION
 结构说明  : MOTIONUVE 寄存器结构定义。地址偏移量:0x034，初值:0x00000000，宽度:32
 寄存器说明: Motion table UV coeff
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  motionuv16 : 8;  /* bit[0-7]  : Motion coefficient-Qu8.0
                                                      Motionuv16=mtbuv[16] */
        unsigned int  motionuv17 : 8;  /* bit[8-15] : Motion coefficient-Qu8.0
                                                      Motionuv17=mtbuv[17] */
        unsigned int  motionuv18 : 8;  /* bit[16-23]: Motion coefficient-Qu8.0
                                                      Motionuv18=mtbuv[18] */
        unsigned int  motionuv19 : 8;  /* bit[24-31]: Motion coefficient-Qu8.0
                                                      Motionuv19=mtbuv[19] */
    } reg;
} SOC_ISP_TNR_MOTIONUVE_UNION;
#endif
#define SOC_ISP_TNR_MOTIONUVE_motionuv16_START  (0)
#define SOC_ISP_TNR_MOTIONUVE_motionuv16_END    (7)
#define SOC_ISP_TNR_MOTIONUVE_motionuv17_START  (8)
#define SOC_ISP_TNR_MOTIONUVE_motionuv17_END    (15)
#define SOC_ISP_TNR_MOTIONUVE_motionuv18_START  (16)
#define SOC_ISP_TNR_MOTIONUVE_motionuv18_END    (23)
#define SOC_ISP_TNR_MOTIONUVE_motionuv19_START  (24)
#define SOC_ISP_TNR_MOTIONUVE_motionuv19_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_TNR_MOTIONUVF_UNION
 结构说明  : MOTIONUVF 寄存器结构定义。地址偏移量:0x038，初值:0x00000000，宽度:32
 寄存器说明: Motion table UV coeff
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  motionuv20 : 8;  /* bit[0-7]  : Motion coefficient-Qu8.0
                                                      Motionuv20=mtbuv[20] */
        unsigned int  motionuv21 : 8;  /* bit[8-15] : Motion coefficient-Qu8.0
                                                      Motionuv21=mtbuv[21] */
        unsigned int  motionuv22 : 8;  /* bit[16-23]: Motion coefficient-Qu8.0
                                                      Motionuv22=mtbuv[22] */
        unsigned int  motionuv23 : 8;  /* bit[24-31]: Motion coefficient-Qu8.0
                                                      Motionuv23=mtbuv[23] */
    } reg;
} SOC_ISP_TNR_MOTIONUVF_UNION;
#endif
#define SOC_ISP_TNR_MOTIONUVF_motionuv20_START  (0)
#define SOC_ISP_TNR_MOTIONUVF_motionuv20_END    (7)
#define SOC_ISP_TNR_MOTIONUVF_motionuv21_START  (8)
#define SOC_ISP_TNR_MOTIONUVF_motionuv21_END    (15)
#define SOC_ISP_TNR_MOTIONUVF_motionuv22_START  (16)
#define SOC_ISP_TNR_MOTIONUVF_motionuv22_END    (23)
#define SOC_ISP_TNR_MOTIONUVF_motionuv23_START  (24)
#define SOC_ISP_TNR_MOTIONUVF_motionuv23_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_TNR_MOTIONUVG_UNION
 结构说明  : MOTIONUVG 寄存器结构定义。地址偏移量:0x03C，初值:0x00000000，宽度:32
 寄存器说明: Motion table UV coeff
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  motionuv24 : 8;  /* bit[0-7]  : Motion coefficient-Qu8.0
                                                      Motionuv24=mtbuv[24] */
        unsigned int  motionuv25 : 8;  /* bit[8-15] : Motion coefficient-Qu8.0
                                                      Motionuv25=mtbuv[25] */
        unsigned int  motionuv26 : 8;  /* bit[16-23]: Motion coefficient-Qu8.0
                                                      Motionuv26=mtbuv[26] */
        unsigned int  motionuv27 : 8;  /* bit[24-31]: Motion coefficient-Qu8.0
                                                      Motionuv27=mtbuv[27] */
    } reg;
} SOC_ISP_TNR_MOTIONUVG_UNION;
#endif
#define SOC_ISP_TNR_MOTIONUVG_motionuv24_START  (0)
#define SOC_ISP_TNR_MOTIONUVG_motionuv24_END    (7)
#define SOC_ISP_TNR_MOTIONUVG_motionuv25_START  (8)
#define SOC_ISP_TNR_MOTIONUVG_motionuv25_END    (15)
#define SOC_ISP_TNR_MOTIONUVG_motionuv26_START  (16)
#define SOC_ISP_TNR_MOTIONUVG_motionuv26_END    (23)
#define SOC_ISP_TNR_MOTIONUVG_motionuv27_START  (24)
#define SOC_ISP_TNR_MOTIONUVG_motionuv27_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_TNR_MOTIONUVH_UNION
 结构说明  : MOTIONUVH 寄存器结构定义。地址偏移量:0x040，初值:0x00000000，宽度:32
 寄存器说明: Motion table UV coeff
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  motionuv28 : 8;  /* bit[0-7]  : Motion coefficient-Qu8.0
                                                      Motionuv28=mtbuv[28] */
        unsigned int  motionuv29 : 8;  /* bit[8-15] : Motion coefficient-Qu8.0
                                                      Motionuv29=mtbuv[29] */
        unsigned int  reserved   : 16; /* bit[16-31]:  */
    } reg;
} SOC_ISP_TNR_MOTIONUVH_UNION;
#endif
#define SOC_ISP_TNR_MOTIONUVH_motionuv28_START  (0)
#define SOC_ISP_TNR_MOTIONUVH_motionuv28_END    (7)
#define SOC_ISP_TNR_MOTIONUVH_motionuv29_START  (8)
#define SOC_ISP_TNR_MOTIONUVH_motionuv29_END    (15)


/*****************************************************************************
 结构名    : SOC_ISP_TNR_MOTIONA_UNION
 结构说明  : MOTIONA 寄存器结构定义。地址偏移量:0x044，初值:0x00000000，宽度:32
 寄存器说明: Motion table Y coeff
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  motion0 : 8;  /* bit[0-7]  : Motion coefficient-Qu8.0
                                                   Motion0=mtb[0] */
        unsigned int  motion1 : 8;  /* bit[8-15] : Motion coefficient-Qu8.0
                                                   Motion1=mtb[1] */
        unsigned int  motion2 : 8;  /* bit[16-23]: Motion coefficient-Qu8.0
                                                   Motion2=mtb[2] */
        unsigned int  motion3 : 8;  /* bit[24-31]: Motion coefficient-Qu8.0
                                                   Motion3=mtb[3] */
    } reg;
} SOC_ISP_TNR_MOTIONA_UNION;
#endif
#define SOC_ISP_TNR_MOTIONA_motion0_START  (0)
#define SOC_ISP_TNR_MOTIONA_motion0_END    (7)
#define SOC_ISP_TNR_MOTIONA_motion1_START  (8)
#define SOC_ISP_TNR_MOTIONA_motion1_END    (15)
#define SOC_ISP_TNR_MOTIONA_motion2_START  (16)
#define SOC_ISP_TNR_MOTIONA_motion2_END    (23)
#define SOC_ISP_TNR_MOTIONA_motion3_START  (24)
#define SOC_ISP_TNR_MOTIONA_motion3_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_TNR_MOTIONB_UNION
 结构说明  : MOTIONB 寄存器结构定义。地址偏移量:0x048，初值:0x00000000，宽度:32
 寄存器说明: Motion table Y coeff
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  motion4 : 8;  /* bit[0-7]  : Motion coefficient-Qu8.0
                                                   Motion4=mtb[4] */
        unsigned int  motion5 : 8;  /* bit[8-15] : Motion coefficient-Qu8.0
                                                   Motion5=mtb[5] */
        unsigned int  motion6 : 8;  /* bit[16-23]: Motion coefficient-Qu8.0
                                                   Motion6=mtb[6] */
        unsigned int  motion7 : 8;  /* bit[24-31]: Motion coefficient-Qu8.0
                                                   Motion7=mtb[7] */
    } reg;
} SOC_ISP_TNR_MOTIONB_UNION;
#endif
#define SOC_ISP_TNR_MOTIONB_motion4_START  (0)
#define SOC_ISP_TNR_MOTIONB_motion4_END    (7)
#define SOC_ISP_TNR_MOTIONB_motion5_START  (8)
#define SOC_ISP_TNR_MOTIONB_motion5_END    (15)
#define SOC_ISP_TNR_MOTIONB_motion6_START  (16)
#define SOC_ISP_TNR_MOTIONB_motion6_END    (23)
#define SOC_ISP_TNR_MOTIONB_motion7_START  (24)
#define SOC_ISP_TNR_MOTIONB_motion7_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_TNR_MOTIONC_UNION
 结构说明  : MOTIONC 寄存器结构定义。地址偏移量:0x04C，初值:0x00000000，宽度:32
 寄存器说明: Motion table Y coeff
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  motion8  : 8;  /* bit[0-7]  : Motion coefficient-Qu8.0
                                                    Motion8=mtb[8] */
        unsigned int  motion9  : 8;  /* bit[8-15] : Motion coefficient-Qu8.0
                                                    Motion9=mtb[9] */
        unsigned int  motion10 : 8;  /* bit[16-23]: Motion coefficient-Qu8.0
                                                    Motion10=mtb[10] */
        unsigned int  motion11 : 8;  /* bit[24-31]: Motion coefficient-Qu8.0
                                                    Motion11=mtb[11] */
    } reg;
} SOC_ISP_TNR_MOTIONC_UNION;
#endif
#define SOC_ISP_TNR_MOTIONC_motion8_START   (0)
#define SOC_ISP_TNR_MOTIONC_motion8_END     (7)
#define SOC_ISP_TNR_MOTIONC_motion9_START   (8)
#define SOC_ISP_TNR_MOTIONC_motion9_END     (15)
#define SOC_ISP_TNR_MOTIONC_motion10_START  (16)
#define SOC_ISP_TNR_MOTIONC_motion10_END    (23)
#define SOC_ISP_TNR_MOTIONC_motion11_START  (24)
#define SOC_ISP_TNR_MOTIONC_motion11_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_TNR_MOTIOND_UNION
 结构说明  : MOTIOND 寄存器结构定义。地址偏移量:0x050，初值:0x00000000，宽度:32
 寄存器说明: Motion table Y coeff
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  motion12 : 8;  /* bit[0-7]  : Motion coefficient-Qu8.0
                                                    Motion12=mtb[12] */
        unsigned int  motion13 : 8;  /* bit[8-15] : Motion coefficient-Qu8.0
                                                    Motion13=mtb[13] */
        unsigned int  motion14 : 8;  /* bit[16-23]: Motion coefficient-Qu8.0
                                                    Motion14=mtb[14] */
        unsigned int  motion15 : 8;  /* bit[24-31]: Motion coefficient-Qu8.0
                                                    Motion15=mtb[15] */
    } reg;
} SOC_ISP_TNR_MOTIOND_UNION;
#endif
#define SOC_ISP_TNR_MOTIOND_motion12_START  (0)
#define SOC_ISP_TNR_MOTIOND_motion12_END    (7)
#define SOC_ISP_TNR_MOTIOND_motion13_START  (8)
#define SOC_ISP_TNR_MOTIOND_motion13_END    (15)
#define SOC_ISP_TNR_MOTIOND_motion14_START  (16)
#define SOC_ISP_TNR_MOTIOND_motion14_END    (23)
#define SOC_ISP_TNR_MOTIOND_motion15_START  (24)
#define SOC_ISP_TNR_MOTIOND_motion15_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_TNR_MOTIONE_UNION
 结构说明  : MOTIONE 寄存器结构定义。地址偏移量:0x054，初值:0x00000000，宽度:32
 寄存器说明: Motion table Y coeff
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  motion16 : 8;  /* bit[0-7]  : Motion coefficient-Qu8.0
                                                    Motion16=mtb[16] */
        unsigned int  motion17 : 8;  /* bit[8-15] : Motion coefficient-Qu8.0
                                                    Motion17=mtb[17] */
        unsigned int  motion18 : 8;  /* bit[16-23]: Motion coefficient-Qu8.0
                                                    Motion18=mtb[18] */
        unsigned int  motion19 : 8;  /* bit[24-31]: Motion coefficient-Qu8.0
                                                    Motion19=mtb[19] */
    } reg;
} SOC_ISP_TNR_MOTIONE_UNION;
#endif
#define SOC_ISP_TNR_MOTIONE_motion16_START  (0)
#define SOC_ISP_TNR_MOTIONE_motion16_END    (7)
#define SOC_ISP_TNR_MOTIONE_motion17_START  (8)
#define SOC_ISP_TNR_MOTIONE_motion17_END    (15)
#define SOC_ISP_TNR_MOTIONE_motion18_START  (16)
#define SOC_ISP_TNR_MOTIONE_motion18_END    (23)
#define SOC_ISP_TNR_MOTIONE_motion19_START  (24)
#define SOC_ISP_TNR_MOTIONE_motion19_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_TNR_MOTIONF_UNION
 结构说明  : MOTIONF 寄存器结构定义。地址偏移量:0x058，初值:0x00000000，宽度:32
 寄存器说明: Motion table Y coeff
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  motion20 : 8;  /* bit[0-7]  : Motion coefficient-Qu8.0
                                                    Motion20=mtb[20] */
        unsigned int  motion21 : 8;  /* bit[8-15] : Motion coefficient-Qu8.0
                                                    Motion21=mtb[21] */
        unsigned int  motion22 : 8;  /* bit[16-23]: Motion coefficient-Qu8.0
                                                    Motion22=mtb[22] */
        unsigned int  motion23 : 8;  /* bit[24-31]: Motion coefficient-Qu8.0
                                                    Motion23=mtb[23] */
    } reg;
} SOC_ISP_TNR_MOTIONF_UNION;
#endif
#define SOC_ISP_TNR_MOTIONF_motion20_START  (0)
#define SOC_ISP_TNR_MOTIONF_motion20_END    (7)
#define SOC_ISP_TNR_MOTIONF_motion21_START  (8)
#define SOC_ISP_TNR_MOTIONF_motion21_END    (15)
#define SOC_ISP_TNR_MOTIONF_motion22_START  (16)
#define SOC_ISP_TNR_MOTIONF_motion22_END    (23)
#define SOC_ISP_TNR_MOTIONF_motion23_START  (24)
#define SOC_ISP_TNR_MOTIONF_motion23_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_TNR_MOTIONG_UNION
 结构说明  : MOTIONG 寄存器结构定义。地址偏移量:0x05C，初值:0x00000000，宽度:32
 寄存器说明: Motion table Y coeff
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  motion24 : 8;  /* bit[0-7]  : Motion coefficient-Qu8.0
                                                    Motion24=mtb[24] */
        unsigned int  motion25 : 8;  /* bit[8-15] : Motion coefficient-Qu8.0
                                                    Motion25=mtb[25] */
        unsigned int  motion26 : 8;  /* bit[16-23]: Motion coefficient-Qu8.0
                                                    Motion26=mtb[26] */
        unsigned int  motion27 : 8;  /* bit[24-31]: Motion coefficient-Qu8.0
                                                    Motion27=mtb[27] */
    } reg;
} SOC_ISP_TNR_MOTIONG_UNION;
#endif
#define SOC_ISP_TNR_MOTIONG_motion24_START  (0)
#define SOC_ISP_TNR_MOTIONG_motion24_END    (7)
#define SOC_ISP_TNR_MOTIONG_motion25_START  (8)
#define SOC_ISP_TNR_MOTIONG_motion25_END    (15)
#define SOC_ISP_TNR_MOTIONG_motion26_START  (16)
#define SOC_ISP_TNR_MOTIONG_motion26_END    (23)
#define SOC_ISP_TNR_MOTIONG_motion27_START  (24)
#define SOC_ISP_TNR_MOTIONG_motion27_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_TNR_MOTIONH_UNION
 结构说明  : MOTIONH 寄存器结构定义。地址偏移量:0x060，初值:0x00000000，宽度:32
 寄存器说明: Motion table Y coeff
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  motion28 : 8;  /* bit[0-7]  : Motion coefficient-Qu8.0
                                                    Motion28=mtb[28] */
        unsigned int  motion29 : 8;  /* bit[8-15] : Motion coefficient-Qu8.0
                                                    Motion29=mtb[29] */
        unsigned int  reserved : 16; /* bit[16-31]:  */
    } reg;
} SOC_ISP_TNR_MOTIONH_UNION;
#endif
#define SOC_ISP_TNR_MOTIONH_motion28_START  (0)
#define SOC_ISP_TNR_MOTIONH_motion28_END    (7)
#define SOC_ISP_TNR_MOTIONH_motion29_START  (8)
#define SOC_ISP_TNR_MOTIONH_motion29_END    (15)


/*****************************************************************************
 结构名    : SOC_ISP_TNR_FORCE_CLK_ON_CFG_UNION
 结构说明  : FORCE_CLK_ON_CFG 寄存器结构定义。地址偏移量:0x070，初值:0x00000001，宽度:32
 寄存器说明: used to force the clock which is generally controlled by HW
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  force_clk_on : 1;  /* bit[0]   : 0: local clock gating is controlled by idle_detector
                                                       1: local clock gating is disabled (clock is ON) */
        unsigned int  reserved     : 31; /* bit[1-31]: Reserved */
    } reg;
} SOC_ISP_TNR_FORCE_CLK_ON_CFG_UNION;
#endif
#define SOC_ISP_TNR_FORCE_CLK_ON_CFG_force_clk_on_START  (0)
#define SOC_ISP_TNR_FORCE_CLK_ON_CFG_force_clk_on_END    (0)






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

#endif /* end of soc_isp_tnr_interface.h */
