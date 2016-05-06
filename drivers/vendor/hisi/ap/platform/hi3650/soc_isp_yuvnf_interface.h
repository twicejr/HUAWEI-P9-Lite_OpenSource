/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_isp_yuvnf_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:22:12
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_ISP_YUVNF.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_ISP_YUVNF_INTERFACE_H__
#define __SOC_ISP_YUVNF_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) YUVNF
 ****************************************************************************/
/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_YUVNF_YUVNF_CONFIG_UNION */
#define SOC_ISP_YUVNF_YUVNF_CONFIG_ADDR(base)         ((base) + (0x0000))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_YUVNF_SAD_INFO_UNION */
#define SOC_ISP_YUVNF_SAD_INFO_ADDR(base)             ((base) + (0x0004))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_YUVNF_NOISE_REDUC_STRENGH_UNION */
#define SOC_ISP_YUVNF_NOISE_REDUC_STRENGH_ADDR(base)  ((base) + (0x0008))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_YUVNF_SHIFT_TEXTRUE_UNION */
#define SOC_ISP_YUVNF_SHIFT_TEXTRUE_ADDR(base)        ((base) + (0x000C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_YUVNF_M_UV_TH_UNION */
#define SOC_ISP_YUVNF_M_UV_TH_ADDR(base)              ((base) + (0x0014))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_YUVNF_UV_DESATURATION_TH_UNION */
#define SOC_ISP_YUVNF_UV_DESATURATION_TH_ADDR(base)   ((base) + (0x0018))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_YUVNF_RECOVER_STRENGH_PARAM_UNION */
#define SOC_ISP_YUVNF_RECOVER_STRENGH_PARAM_ADDR(base) ((base) + (0x0020))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_YUVNF_XY_CENTER_UNION */
#define SOC_ISP_YUVNF_XY_CENTER_ADDR(base)            ((base) + (0x0024))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_YUVNF_IMAGE_SIZE_UNION */
#define SOC_ISP_YUVNF_IMAGE_SIZE_ADDR(base)           ((base) + (0x0028))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_YUVNF_PGAIN_TABLE_ACTIVE_UNION */
#define SOC_ISP_YUVNF_PGAIN_TABLE_ACTIVE_ADDR(base)   ((base) + (0x0030))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_YUVNF_PGAUSSIANLUT_UNION */
#define SOC_ISP_YUVNF_PGAUSSIANLUT_ADDR(base)         ((base) + (0x034))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_YUVNF_SHIFTN_UNION */
#define SOC_ISP_YUVNF_SHIFTN_ADDR(base)               ((base) + (0x0038))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_YUVNF_WEIGHT_LOW_UNION */
#define SOC_ISP_YUVNF_WEIGHT_LOW_ADDR(base)           ((base) + (0x003c))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_YUVNF_WEIGHT_HIGH_UNION */
#define SOC_ISP_YUVNF_WEIGHT_HIGH_ADDR(base)          ((base) + (0x0040))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_YUVNF_BLEND_X_UNION */
#define SOC_ISP_YUVNF_BLEND_X_ADDR(base)              ((base) + (0x0044))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_YUVNF_BLEND_Y_UNION */
#define SOC_ISP_YUVNF_BLEND_Y_ADDR(base)              ((base) + (0x0048))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_YUVNF_PGAUSSLUT_3_UNION */
#define SOC_ISP_YUVNF_PGAUSSLUT_3_ADDR(base)          ((base) + (0x004c))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_YUVNF_PGAUSSLUT_7_UNION */
#define SOC_ISP_YUVNF_PGAUSSLUT_7_ADDR(base)          ((base) + (0x0050))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_YUVNF_PGAUSSLUT_9_UNION */
#define SOC_ISP_YUVNF_PGAUSSLUT_9_ADDR(base)          ((base) + (0x0054))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_YUVNF_BLENDLOW_UNION */
#define SOC_ISP_YUVNF_BLENDLOW_ADDR(base)             ((base) + (0x0058))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_YUVNF_PGAINLSC_0_UNION */
#define SOC_ISP_YUVNF_PGAINLSC_0_ADDR(base, Range53)  ((base) + (0x0100+0x4*(Range53)))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_YUVNF_PGAINLSC_1_UNION */
#define SOC_ISP_YUVNF_PGAINLSC_1_ADDR(base, Range53)  ((base) + (0x0300+0x4*(Range53)))





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
                     (1/1) YUVNF
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_ISP_YUVNF_YUVNF_CONFIG_UNION
 结构说明  : YUVNF_CONFIG 寄存器结构定义。地址偏移量:0x0000，初值:0x00000001，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  full_bypass      : 1;  /* bit[0-0] : Bypass:
                                                           0: the module is active
                                                           1: the module is bypassed
                                                           Note that the bypass preserves the synchronization between Luma and chroma */
        unsigned int  y_bypass         : 1;  /* bit[1-1] : Bypass:
                                                           0: Luma processing is active
                                                           1: Luma processing is bypassed
                                                           Note that the bypass preserves the synchronization between Luma and chroma */
        unsigned int  mult_gauss_en    : 1;  /* bit[2]   : multiple gauss enable
                                                           0:only use 5x5 gauss
                                                           1:use 3x3,7x7,9x9 gauss */
        unsigned int  bypass_symfilter : 1;  /* bit[3]   : 0:sym filter active
                                                           1:bypass sym filter */
        unsigned int  reserved         : 28; /* bit[4-31]:  */
    } reg;
} SOC_ISP_YUVNF_YUVNF_CONFIG_UNION;
#endif
#define SOC_ISP_YUVNF_YUVNF_CONFIG_full_bypass_START       (0)
#define SOC_ISP_YUVNF_YUVNF_CONFIG_full_bypass_END         (0)
#define SOC_ISP_YUVNF_YUVNF_CONFIG_y_bypass_START          (1)
#define SOC_ISP_YUVNF_YUVNF_CONFIG_y_bypass_END            (1)
#define SOC_ISP_YUVNF_YUVNF_CONFIG_mult_gauss_en_START     (2)
#define SOC_ISP_YUVNF_YUVNF_CONFIG_mult_gauss_en_END       (2)
#define SOC_ISP_YUVNF_YUVNF_CONFIG_bypass_symfilter_START  (3)
#define SOC_ISP_YUVNF_YUVNF_CONFIG_bypass_symfilter_END    (3)


/*****************************************************************************
 结构名    : SOC_ISP_YUVNF_SAD_INFO_UNION
 结构说明  : SAD_INFO 寄存器结构定义。地址偏移量:0x0004，初值:0x01000164，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  off_sad   : 8;  /* bit[0-7]  : [0,128] */
        unsigned int  shift_sad : 2;  /* bit[8-9]  : [0,3] */
        unsigned int  reserved_0: 6;  /* bit[10-15]:  */
        unsigned int  inv_sad   : 11; /* bit[16-26]: [0,1024] inv_sad>>shift_sad=128 */
        unsigned int  reserved_1: 5;  /* bit[27-31]:  */
    } reg;
} SOC_ISP_YUVNF_SAD_INFO_UNION;
#endif
#define SOC_ISP_YUVNF_SAD_INFO_off_sad_START    (0)
#define SOC_ISP_YUVNF_SAD_INFO_off_sad_END      (7)
#define SOC_ISP_YUVNF_SAD_INFO_shift_sad_START  (8)
#define SOC_ISP_YUVNF_SAD_INFO_shift_sad_END    (9)
#define SOC_ISP_YUVNF_SAD_INFO_inv_sad_START    (16)
#define SOC_ISP_YUVNF_SAD_INFO_inv_sad_END      (26)


/*****************************************************************************
 结构名    : SOC_ISP_YUVNF_NOISE_REDUC_STRENGH_UNION
 结构说明  : NOISE_REDUC_STRENGH 寄存器结构定义。地址偏移量:0x0008，初值:0x000A0040，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  edgeth     : 8;  /* bit[0-7]  : [0,128] */
        unsigned int  edgemaxoff : 6;  /* bit[8-13] : [0,32] */
        unsigned int  reserved_0 : 2;  /* bit[14-15]:  */
        unsigned int  gainmaxoff : 8;  /* bit[16-23]: [0,160] */
        unsigned int  reserved_1 : 8;  /* bit[24-31]:  */
    } reg;
} SOC_ISP_YUVNF_NOISE_REDUC_STRENGH_UNION;
#endif
#define SOC_ISP_YUVNF_NOISE_REDUC_STRENGH_edgeth_START      (0)
#define SOC_ISP_YUVNF_NOISE_REDUC_STRENGH_edgeth_END        (7)
#define SOC_ISP_YUVNF_NOISE_REDUC_STRENGH_edgemaxoff_START  (8)
#define SOC_ISP_YUVNF_NOISE_REDUC_STRENGH_edgemaxoff_END    (13)
#define SOC_ISP_YUVNF_NOISE_REDUC_STRENGH_gainmaxoff_START  (16)
#define SOC_ISP_YUVNF_NOISE_REDUC_STRENGH_gainmaxoff_END    (23)


/*****************************************************************************
 结构名    : SOC_ISP_YUVNF_SHIFT_TEXTRUE_UNION
 结构说明  : SHIFT_TEXTRUE 寄存器结构定义。地址偏移量:0x000C，初值:0x00000006，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  shift_textrue : 4;  /* bit[0-3] : Edge intensity scaling factor
                                                        [0,10] */
        unsigned int  reserved      : 28; /* bit[4-31]:  */
    } reg;
} SOC_ISP_YUVNF_SHIFT_TEXTRUE_UNION;
#endif
#define SOC_ISP_YUVNF_SHIFT_TEXTRUE_shift_textrue_START  (0)
#define SOC_ISP_YUVNF_SHIFT_TEXTRUE_shift_textrue_END    (3)


/*****************************************************************************
 结构名    : SOC_ISP_YUVNF_M_UV_TH_UNION
 结构说明  : M_UV_TH 寄存器结构定义。地址偏移量:0x0014，初值:0x00000050，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  uv_impulsive_th : 8;  /* bit[0-7] : [0,255] */
        unsigned int  reserved        : 24; /* bit[8-31]:  */
    } reg;
} SOC_ISP_YUVNF_M_UV_TH_UNION;
#endif
#define SOC_ISP_YUVNF_M_UV_TH_uv_impulsive_th_START  (0)
#define SOC_ISP_YUVNF_M_UV_TH_uv_impulsive_th_END    (7)


/*****************************************************************************
 结构名    : SOC_ISP_YUVNF_UV_DESATURATION_TH_UNION
 结构说明  : UV_DESATURATION_TH 寄存器结构定义。地址偏移量:0x0018，初值:0x00000021，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  v_desaturation_th : 4;  /* bit[0-3] : [0,15] */
        unsigned int  u_desaturation_th : 4;  /* bit[4-7] : [0,15] */
        unsigned int  reserved          : 24; /* bit[8-31]:  */
    } reg;
} SOC_ISP_YUVNF_UV_DESATURATION_TH_UNION;
#endif
#define SOC_ISP_YUVNF_UV_DESATURATION_TH_v_desaturation_th_START  (0)
#define SOC_ISP_YUVNF_UV_DESATURATION_TH_v_desaturation_th_END    (3)
#define SOC_ISP_YUVNF_UV_DESATURATION_TH_u_desaturation_th_START  (4)
#define SOC_ISP_YUVNF_UV_DESATURATION_TH_u_desaturation_th_END    (7)


/*****************************************************************************
 结构名    : SOC_ISP_YUVNF_RECOVER_STRENGH_PARAM_UNION
 结构说明  : RECOVER_STRENGH_PARAM 寄存器结构定义。地址偏移量:0x0020，初值:0x0040805F，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  noeblendlow  : 8;  /* bit[0-7]  : detail recover strength
                                                        [0,128] */
        unsigned int  edgeblendlow : 8;  /* bit[8-15] : detail recover strength
                                                        [0,128] */
        unsigned int  noisescale   : 7;  /* bit[16-22]: small detail or radom noise recover strength
                                                        [0,64] */
        unsigned int  reserved_0   : 1;  /* bit[23-23]:  */
        unsigned int  reserved_1   : 8;  /* bit[24-31]:  */
    } reg;
} SOC_ISP_YUVNF_RECOVER_STRENGH_PARAM_UNION;
#endif
#define SOC_ISP_YUVNF_RECOVER_STRENGH_PARAM_noeblendlow_START   (0)
#define SOC_ISP_YUVNF_RECOVER_STRENGH_PARAM_noeblendlow_END     (7)
#define SOC_ISP_YUVNF_RECOVER_STRENGH_PARAM_edgeblendlow_START  (8)
#define SOC_ISP_YUVNF_RECOVER_STRENGH_PARAM_edgeblendlow_END    (15)
#define SOC_ISP_YUVNF_RECOVER_STRENGH_PARAM_noisescale_START    (16)
#define SOC_ISP_YUVNF_RECOVER_STRENGH_PARAM_noisescale_END      (22)


/*****************************************************************************
 结构名    : SOC_ISP_YUVNF_XY_CENTER_UNION
 结构说明  : XY_CENTER 寄存器结构定义。地址偏移量:0x0024，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  x_center : 13; /* bit[0-12] : CenterX-offset, used in dual pipe [-4095,4095] */
        unsigned int  reserved_0: 3;  /* bit[13-15]:  */
        unsigned int  reserved_1: 16; /* bit[16-31]:  */
    } reg;
} SOC_ISP_YUVNF_XY_CENTER_UNION;
#endif
#define SOC_ISP_YUVNF_XY_CENTER_x_center_START  (0)
#define SOC_ISP_YUVNF_XY_CENTER_x_center_END    (12)


/*****************************************************************************
 结构名    : SOC_ISP_YUVNF_IMAGE_SIZE_UNION
 结构说明  : IMAGE_SIZE 寄存器结构定义。地址偏移量:0x0028，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  height   : 13; /* bit[0-12] : Image height -1 [ ,8191] */
        unsigned int  reserved_0: 3;  /* bit[13-15]:  */
        unsigned int  width    : 13; /* bit[16-28]: Image width -1 [ ,4423] */
        unsigned int  reserved_1: 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_YUVNF_IMAGE_SIZE_UNION;
#endif
#define SOC_ISP_YUVNF_IMAGE_SIZE_height_START    (0)
#define SOC_ISP_YUVNF_IMAGE_SIZE_height_END      (12)
#define SOC_ISP_YUVNF_IMAGE_SIZE_width_START     (16)
#define SOC_ISP_YUVNF_IMAGE_SIZE_width_END       (28)


/*****************************************************************************
 结构名    : SOC_ISP_YUVNF_PGAIN_TABLE_ACTIVE_UNION
 结构说明  : PGAIN_TABLE_ACTIVE 寄存器结构定义。地址偏移量:0x0030，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pgain_table_active : 1;  /* bit[0-0] : pgain_table_active:
                                                             0:pGainLSC_0 is used by the HW
                                                             1:pGainLSC_1 is used by the HW */
        unsigned int  reserved           : 31; /* bit[1-31]:  */
    } reg;
} SOC_ISP_YUVNF_PGAIN_TABLE_ACTIVE_UNION;
#endif
#define SOC_ISP_YUVNF_PGAIN_TABLE_ACTIVE_pgain_table_active_START  (0)
#define SOC_ISP_YUVNF_PGAIN_TABLE_ACTIVE_pgain_table_active_END    (0)


/*****************************************************************************
 结构名    : SOC_ISP_YUVNF_PGAUSSIANLUT_UNION
 结构说明  : PGAUSSIANLUT 寄存器结构定义。地址偏移量:0x034，初值:0x00010F20，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pgaussianlut_0 : 7;  /* bit[0-6]  : [0,64] */
        unsigned int  reserved_0     : 1;  /* bit[7]    :  */
        unsigned int  pgaussianlut_1 : 7;  /* bit[8-14] : [0,64] */
        unsigned int  reserved_1     : 1;  /* bit[15]   :  */
        unsigned int  pgaussianlut_2 : 7;  /* bit[16-22]: [0,64],pgaussianlut_0*2+pgaussianlut_1*2+pgaussianlut_2=64 */
        unsigned int  reserved_2     : 9;  /* bit[23-31]:  */
    } reg;
} SOC_ISP_YUVNF_PGAUSSIANLUT_UNION;
#endif
#define SOC_ISP_YUVNF_PGAUSSIANLUT_pgaussianlut_0_START  (0)
#define SOC_ISP_YUVNF_PGAUSSIANLUT_pgaussianlut_0_END    (6)
#define SOC_ISP_YUVNF_PGAUSSIANLUT_pgaussianlut_1_START  (8)
#define SOC_ISP_YUVNF_PGAUSSIANLUT_pgaussianlut_1_END    (14)
#define SOC_ISP_YUVNF_PGAUSSIANLUT_pgaussianlut_2_START  (16)
#define SOC_ISP_YUVNF_PGAUSSIANLUT_pgaussianlut_2_END    (22)


/*****************************************************************************
 结构名    : SOC_ISP_YUVNF_SHIFTN_UNION
 结构说明  : SHIFTN 寄存器结构定义。地址偏移量:0x0038，初值:0x0000000F，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  shiftn   : 5;  /* bit[0-4] : LSC gain interpolate parameter for multi-stripe processing
                                                   [5,16] */
        unsigned int  reserved : 27; /* bit[5-31]:  */
    } reg;
} SOC_ISP_YUVNF_SHIFTN_UNION;
#endif
#define SOC_ISP_YUVNF_SHIFTN_shiftn_START    (0)
#define SOC_ISP_YUVNF_SHIFTN_shiftn_END      (4)


/*****************************************************************************
 结构名    : SOC_ISP_YUVNF_WEIGHT_LOW_UNION
 结构说明  : WEIGHT_LOW 寄存器结构定义。地址偏移量:0x003c，初值:0x00000101，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  weight_low_v : 8;  /* bit[0-7]  : [0.255] */
        unsigned int  weight_low_u : 8;  /* bit[8-15] : [0,255] */
        unsigned int  reserved     : 16; /* bit[16-31]:  */
    } reg;
} SOC_ISP_YUVNF_WEIGHT_LOW_UNION;
#endif
#define SOC_ISP_YUVNF_WEIGHT_LOW_weight_low_v_START  (0)
#define SOC_ISP_YUVNF_WEIGHT_LOW_weight_low_v_END    (7)
#define SOC_ISP_YUVNF_WEIGHT_LOW_weight_low_u_START  (8)
#define SOC_ISP_YUVNF_WEIGHT_LOW_weight_low_u_END    (15)


/*****************************************************************************
 结构名    : SOC_ISP_YUVNF_WEIGHT_HIGH_UNION
 结构说明  : WEIGHT_HIGH 寄存器结构定义。地址偏移量:0x0040，初值:0x00000101，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  weight_high_v : 8;  /* bit[0-7]  : [0.255] */
        unsigned int  weight_high_u : 8;  /* bit[8-15] : [0,255] */
        unsigned int  reserved      : 16; /* bit[16-31]:  */
    } reg;
} SOC_ISP_YUVNF_WEIGHT_HIGH_UNION;
#endif
#define SOC_ISP_YUVNF_WEIGHT_HIGH_weight_high_v_START  (0)
#define SOC_ISP_YUVNF_WEIGHT_HIGH_weight_high_v_END    (7)
#define SOC_ISP_YUVNF_WEIGHT_HIGH_weight_high_u_START  (8)
#define SOC_ISP_YUVNF_WEIGHT_HIGH_weight_high_u_END    (15)


/*****************************************************************************
 结构名    : SOC_ISP_YUVNF_BLEND_X_UNION
 结构说明  : BLEND_X 寄存器结构定义。地址偏移量:0x0044，初值:0x00003010，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  blend_x0 : 8;  /* bit[0-7]  : [0,255] */
        unsigned int  blend_x1 : 8;  /* bit[8-15] : [0,255]，
                                                    blend_x1-blend_x0=16/32/64 and
                                                    blend_x1>blend_x0 */
        unsigned int  reserved : 16; /* bit[16-31]:  */
    } reg;
} SOC_ISP_YUVNF_BLEND_X_UNION;
#endif
#define SOC_ISP_YUVNF_BLEND_X_blend_x0_START  (0)
#define SOC_ISP_YUVNF_BLEND_X_blend_x0_END    (7)
#define SOC_ISP_YUVNF_BLEND_X_blend_x1_START  (8)
#define SOC_ISP_YUVNF_BLEND_X_blend_x1_END    (15)


/*****************************************************************************
 结构名    : SOC_ISP_YUVNF_BLEND_Y_UNION
 结构说明  : BLEND_Y 寄存器结构定义。地址偏移量:0x0048，初值:0x00008000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  blend_y0 : 8;  /* bit[0-7]  : [0,128] */
        unsigned int  blend_y1 : 8;  /* bit[8-15] : [0,128]，blend_y1>blend_y0 */
        unsigned int  reserved : 16; /* bit[16-31]:  */
    } reg;
} SOC_ISP_YUVNF_BLEND_Y_UNION;
#endif
#define SOC_ISP_YUVNF_BLEND_Y_blend_y0_START  (0)
#define SOC_ISP_YUVNF_BLEND_Y_blend_y0_END    (7)
#define SOC_ISP_YUVNF_BLEND_Y_blend_y1_START  (8)
#define SOC_ISP_YUVNF_BLEND_Y_blend_y1_END    (15)


/*****************************************************************************
 结构名    : SOC_ISP_YUVNF_PGAUSSLUT_3_UNION
 结构说明  : PGAUSSLUT_3 寄存器结构定义。地址偏移量:0x004c，初值:0x00123008，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pg3lut_0 : 7;  /* bit[0-6]  : [0,64] */
        unsigned int  reserved_0: 1;  /* bit[7]    :  */
        unsigned int  pg3lut_1 : 7;  /* bit[8-14] : [0,64]
                                                    pg3lut_0*2+pg3lut_1=64 */
        unsigned int  reserved_1: 1;  /* bit[15]   :  */
        unsigned int  pg9lut_4 : 7;  /* bit[16-22]: [0,64] */
        unsigned int  reserved_2: 9;  /* bit[23-31]:  */
    } reg;
} SOC_ISP_YUVNF_PGAUSSLUT_3_UNION;
#endif
#define SOC_ISP_YUVNF_PGAUSSLUT_3_pg3lut_0_START  (0)
#define SOC_ISP_YUVNF_PGAUSSLUT_3_pg3lut_0_END    (6)
#define SOC_ISP_YUVNF_PGAUSSLUT_3_pg3lut_1_START  (8)
#define SOC_ISP_YUVNF_PGAUSSLUT_3_pg3lut_1_END    (14)
#define SOC_ISP_YUVNF_PGAUSSLUT_3_pg9lut_4_START  (16)
#define SOC_ISP_YUVNF_PGAUSSLUT_3_pg9lut_4_END    (22)


/*****************************************************************************
 结构名    : SOC_ISP_YUVNF_PGAUSSLUT_7_UNION
 结构说明  : PGAUSSLUT_7 寄存器结构定义。地址偏移量:0x0050，初值:0x1815120D，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pg7lut_0 : 7;  /* bit[0-6]  : [0,64] */
        unsigned int  reserved_0: 1;  /* bit[7]    :  */
        unsigned int  pg7lut_1 : 7;  /* bit[8-14] : [0,64] */
        unsigned int  reserved_1: 1;  /* bit[15]   :  */
        unsigned int  pg7lut_2 : 7;  /* bit[16-22]: [0,64] */
        unsigned int  reserved_2: 1;  /* bit[23]   :  */
        unsigned int  pg7lut_3 : 7;  /* bit[24-30]: [0,64]
                                                    pg7lut_0*2+pg7lut_1*2+pg7lut_2*2+pg7lut_3=128 */
        unsigned int  reserved_3: 1;  /* bit[31]   :  */
    } reg;
} SOC_ISP_YUVNF_PGAUSSLUT_7_UNION;
#endif
#define SOC_ISP_YUVNF_PGAUSSLUT_7_pg7lut_0_START  (0)
#define SOC_ISP_YUVNF_PGAUSSLUT_7_pg7lut_0_END    (6)
#define SOC_ISP_YUVNF_PGAUSSLUT_7_pg7lut_1_START  (8)
#define SOC_ISP_YUVNF_PGAUSSLUT_7_pg7lut_1_END    (14)
#define SOC_ISP_YUVNF_PGAUSSLUT_7_pg7lut_2_START  (16)
#define SOC_ISP_YUVNF_PGAUSSLUT_7_pg7lut_2_END    (22)
#define SOC_ISP_YUVNF_PGAUSSLUT_7_pg7lut_3_START  (24)
#define SOC_ISP_YUVNF_PGAUSSLUT_7_pg7lut_3_END    (30)


/*****************************************************************************
 结构名    : SOC_ISP_YUVNF_PGAUSSLUT_9_UNION
 结构说明  : PGAUSSLUT_9 寄存器结构定义。地址偏移量:0x0054，初值:0x100F0D0B，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pg9lut_0 : 7;  /* bit[0-6]  : [0,64] */
        unsigned int  reserved_0: 1;  /* bit[7]    :  */
        unsigned int  pg9lut_1 : 7;  /* bit[8-14] : [0,64] */
        unsigned int  reserved_1: 1;  /* bit[15]   :  */
        unsigned int  pg9lut_2 : 7;  /* bit[16-22]: [0,64] */
        unsigned int  reserved_2: 1;  /* bit[23]   :  */
        unsigned int  pg9lut_3 : 7;  /* bit[24-30]: [0,64]
                                                    pg9lut_0*2+pg9lut_1*2+pg9lut_2*2+pg9lut_3*2+pg9lut_4=128 */
        unsigned int  reserved_3: 1;  /* bit[31]   :  */
    } reg;
} SOC_ISP_YUVNF_PGAUSSLUT_9_UNION;
#endif
#define SOC_ISP_YUVNF_PGAUSSLUT_9_pg9lut_0_START  (0)
#define SOC_ISP_YUVNF_PGAUSSLUT_9_pg9lut_0_END    (6)
#define SOC_ISP_YUVNF_PGAUSSLUT_9_pg9lut_1_START  (8)
#define SOC_ISP_YUVNF_PGAUSSLUT_9_pg9lut_1_END    (14)
#define SOC_ISP_YUVNF_PGAUSSLUT_9_pg9lut_2_START  (16)
#define SOC_ISP_YUVNF_PGAUSSLUT_9_pg9lut_2_END    (22)
#define SOC_ISP_YUVNF_PGAUSSLUT_9_pg9lut_3_START  (24)
#define SOC_ISP_YUVNF_PGAUSSLUT_9_pg9lut_3_END    (30)


/*****************************************************************************
 结构名    : SOC_ISP_YUVNF_BLENDLOW_UNION
 结构说明  : BLENDLOW 寄存器结构定义。地址偏移量:0x0058，初值:0x00000099，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  blendlow : 10; /* bit[0-9]  : blend parameter for nlm filter and guassian filter
                                                    mult_gauss_en=0:[0,255]
                                                    mult_gauss_en=1:[0,1023] */
        unsigned int  reserved : 22; /* bit[10-31]:  */
    } reg;
} SOC_ISP_YUVNF_BLENDLOW_UNION;
#endif
#define SOC_ISP_YUVNF_BLENDLOW_blendlow_START  (0)
#define SOC_ISP_YUVNF_BLENDLOW_blendlow_END    (9)


/*****************************************************************************
 结构名    : SOC_ISP_YUVNF_PGAINLSC_0_UNION
 结构说明  : PGAINLSC_0 寄存器结构定义。地址偏移量:0x0100+0x4*(Range53)，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pgainlsc : 13; /* bit[0-12] : Lsc gain table [1024,5120] increment
                                                    1024 1086 1138 1175 1208 1241 1273 1304 1333 1361 1389 1417 1445 1472 1499 1526 1554 1582 1611 1640 1671 1700 1729 1761 1794 1827 1863 1901 1941 1984 2028 2075 2122 2169 2220 2272 2325 2379 2434 2493 2555 2620 2688 2760 2836 2916 3002 3091 3188 3290 3395 3503 3603  */
        unsigned int  reserved : 19; /* bit[13-31]:  */
    } reg;
} SOC_ISP_YUVNF_PGAINLSC_0_UNION;
#endif
#define SOC_ISP_YUVNF_PGAINLSC_0_pgainlsc_START  (0)
#define SOC_ISP_YUVNF_PGAINLSC_0_pgainlsc_END    (12)


/*****************************************************************************
 结构名    : SOC_ISP_YUVNF_PGAINLSC_1_UNION
 结构说明  : PGAINLSC_1 寄存器结构定义。地址偏移量:0x0300+0x4*(Range53)，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pgainlsc : 13; /* bit[0-12] : Lsc gain table */
        unsigned int  reserved : 19; /* bit[13-31]:  */
    } reg;
} SOC_ISP_YUVNF_PGAINLSC_1_UNION;
#endif
#define SOC_ISP_YUVNF_PGAINLSC_1_pgainlsc_START  (0)
#define SOC_ISP_YUVNF_PGAINLSC_1_pgainlsc_END    (12)






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

#endif /* end of soc_isp_yuvnf_interface.h */
