/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_isp_be_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:21:26
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_ISP_BE.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_ISP_BE_INTERFACE_H__
#define __SOC_ISP_BE_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) ISP_BE
 ****************************************************************************/
/* 寄存器说明：Functional clock enable for FE
   位域定义UNION结构:  SOC_ISP_BE_FCLK_EN_BE_UNION */
#define SOC_ISP_BE_FCLK_EN_BE_ADDR(base)              ((base) + (0x0))

/* 寄存器说明：Pipe configuration control
   位域定义UNION结构:  SOC_ISP_BE_CONTROL_UNION */
#define SOC_ISP_BE_CONTROL_ADDR(base)                 ((base) + (0x0010))

/* 寄存器说明：Crop horizontal offsets
   位域定义UNION结构:  SOC_ISP_BE_CROP_H_2_UNION */
#define SOC_ISP_BE_CROP_H_2_ADDR(base)                ((base) + (0x0020))

/* 寄存器说明：Crop vertical offsets
   位域定义UNION结构:  SOC_ISP_BE_CROP_V_2_UNION */
#define SOC_ISP_BE_CROP_V_2_ADDR(base)                ((base) + (0x0024))

/* 寄存器说明：Color conversion matrix coefficient
   位域定义UNION结构:  SOC_ISP_BE_RGB2YUV_COEFF_0_UNION */
#define SOC_ISP_BE_RGB2YUV_COEFF_0_ADDR(base)         ((base) + (0x0030))

/* 寄存器说明：Color conversion matrix coefficient
   位域定义UNION结构:  SOC_ISP_BE_RGB2YUV_COEFF_1_UNION */
#define SOC_ISP_BE_RGB2YUV_COEFF_1_ADDR(base)         ((base) + (0x0034))

/* 寄存器说明：Color conversion matrix coefficient
   位域定义UNION结构:  SOC_ISP_BE_RGB2YUV_COEFF_2_UNION */
#define SOC_ISP_BE_RGB2YUV_COEFF_2_ADDR(base)         ((base) + (0x0038))

/* 寄存器说明：Color conversion matrix coefficient
   位域定义UNION结构:  SOC_ISP_BE_RGB2YUV_COEFF_3_UNION */
#define SOC_ISP_BE_RGB2YUV_COEFF_3_ADDR(base)         ((base) + (0x003C))

/* 寄存器说明：Color conversion matrix coefficient
   位域定义UNION结构:  SOC_ISP_BE_RGB2YUV_COEFF_4_UNION */
#define SOC_ISP_BE_RGB2YUV_COEFF_4_ADDR(base)         ((base) + (0x0040))

/* 寄存器说明：Color conversion matrix coefficient
   位域定义UNION结构:  SOC_ISP_BE_RGB2YUV_COEFF_5_UNION */
#define SOC_ISP_BE_RGB2YUV_COEFF_5_ADDR(base)         ((base) + (0x0044))

/* 寄存器说明：Color conversion matrix coefficient
   位域定义UNION结构:  SOC_ISP_BE_RGB2YUV_COEFF_6_UNION */
#define SOC_ISP_BE_RGB2YUV_COEFF_6_ADDR(base)         ((base) + (0x0048))

/* 寄存器说明：Color conversion matrix coefficient
   位域定义UNION结构:  SOC_ISP_BE_RGB2YUV_COEFF_7_UNION */
#define SOC_ISP_BE_RGB2YUV_COEFF_7_ADDR(base)         ((base) + (0x004C))

/* 寄存器说明：Color conversion matrix coefficient
   位域定义UNION结构:  SOC_ISP_BE_RGB2YUV_COEFF_8_UNION */
#define SOC_ISP_BE_RGB2YUV_COEFF_8_ADDR(base)         ((base) + (0x0050))

/* 寄存器说明：Color conversion matrix coefficient
   位域定义UNION结构:  SOC_ISP_BE_YUV2RGB_COEFF_0_UNION */
#define SOC_ISP_BE_YUV2RGB_COEFF_0_ADDR(base)         ((base) + (0x0060))

/* 寄存器说明：Color conversion matrix coefficient
   位域定义UNION结构:  SOC_ISP_BE_YUV2RGB_COEFF_1_UNION */
#define SOC_ISP_BE_YUV2RGB_COEFF_1_ADDR(base)         ((base) + (0x0064))

/* 寄存器说明：Color conversion matrix coefficient
   位域定义UNION结构:  SOC_ISP_BE_YUV2RGB_COEFF_2_UNION */
#define SOC_ISP_BE_YUV2RGB_COEFF_2_ADDR(base)         ((base) + (0x0068))

/* 寄存器说明：Color conversion matrix coefficient
   位域定义UNION结构:  SOC_ISP_BE_YUV2RGB_COEFF_3_UNION */
#define SOC_ISP_BE_YUV2RGB_COEFF_3_ADDR(base)         ((base) + (0x006C))

/* 寄存器说明：Color conversion matrix coefficient
   位域定义UNION结构:  SOC_ISP_BE_YUV2RGB_COEFF_4_UNION */
#define SOC_ISP_BE_YUV2RGB_COEFF_4_ADDR(base)         ((base) + (0x0070))

/* 寄存器说明：Color conversion matrix coefficient
   位域定义UNION结构:  SOC_ISP_BE_YUV2RGB_COEFF_5_UNION */
#define SOC_ISP_BE_YUV2RGB_COEFF_5_ADDR(base)         ((base) + (0x0074))

/* 寄存器说明：Color conversion matrix coefficient
   位域定义UNION结构:  SOC_ISP_BE_YUV2RGB_COEFF_6_UNION */
#define SOC_ISP_BE_YUV2RGB_COEFF_6_ADDR(base)         ((base) + (0x0078))

/* 寄存器说明：Color conversion matrix coefficient
   位域定义UNION结构:  SOC_ISP_BE_YUV2RGB_COEFF_7_UNION */
#define SOC_ISP_BE_YUV2RGB_COEFF_7_ADDR(base)         ((base) + (0x007C))

/* 寄存器说明：Color conversion matrix coefficient
   位域定义UNION结构:  SOC_ISP_BE_YUV2RGB_COEFF_8_UNION */
#define SOC_ISP_BE_YUV2RGB_COEFF_8_ADDR(base)         ((base) + (0x0080))

/* 寄存器说明：Ratio
   位域定义UNION结构:  SOC_ISP_BE_PTREG_UNION */
#define SOC_ISP_BE_PTREG_ADDR(base)                   ((base) + (0x0090))

/* 寄存器说明：used to force the clock which is generally controlled by HW
   位域定义UNION结构:  SOC_ISP_BE_FORCE_CLK_ON_CFG_UNION */
#define SOC_ISP_BE_FORCE_CLK_ON_CFG_ADDR(base)        ((base) + (0x00A0))





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
                     (1/1) ISP_BE
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_ISP_BE_FCLK_EN_BE_UNION
 结构说明  : FCLK_EN_BE 寄存器结构定义。地址偏移量:0x0，初值:0x0000FFFF，宽度:32
 寄存器说明: Functional clock enable for FE
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fclk_en_be : 16; /* bit[0-15] : The register allow to reduce the functional clock by gating 1 to 16 clock pulse out of 16 clock pulse with a given pattern (shifter register) to allow reducing average throughput, hence power consumption by gating the functional function partially. enable is active high.
                                                      0x0000 Clock is fully gated
                                                      0xFFFF No Clk gating
                                                      Any bit pattern in between is gating corresponding functional clock pulse but refers table in top level specification for specific frequency programming */
        unsigned int  reserved   : 16; /* bit[16-31]: Reserved */
    } reg;
} SOC_ISP_BE_FCLK_EN_BE_UNION;
#endif
#define SOC_ISP_BE_FCLK_EN_BE_fclk_en_be_START  (0)
#define SOC_ISP_BE_FCLK_EN_BE_fclk_en_be_END    (15)


/*****************************************************************************
 结构名    : SOC_ISP_BE_CONTROL_UNION
 结构说明  : CONTROL 寄存器结构定义。地址偏移量:0x0010，初值:0x00000040，宽度:32
 寄存器说明: Pipe configuration control
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bayer_pat_be           : 2;  /* bit[0-1]  : Color components from sensor, starting with top left position in sampled frame 
                                                                   00- first line: RGRG..., second line: GBGB..., etc.
                                                                   01- first line: GRGR..., second line: BGBG..., etc. 
                                                                   10- first line: GBGB..., second line: RGRG..., etc. 
                                                                   11- first line: BGBG..., second line: GRGR..., etc. 
                                                                  This configuration applies to all modules processing Raw in the back end. SW set its value based on the BAS setting ( bypass/downsampling) and cropping function.
                                                                  SHALL BE SHADOWED INSIDE EACH SUB-MODULES */
        unsigned int  ccir_seq               : 2;  /* bit[2-3]  : indicates the Y,Cb,Cr sequencing to manage upsampling in the UVDEC module 
                                                                  00- YCbYCr 
                                                                  01- YCrYCb 
                                                                  10- CbYCrY 
                                                                  11- CrYCbY */
        unsigned int  conv_422               : 2;  /* bit[4-5]  : select the upsampling method in the UVDEC module 
                                                                  00- co-sited color subsampling Y0Cb0Cr0 – Y1 
                                                                  01- interleaved color subsampling Y0Cb0 – Y1Cr1 (not recommended) 
                                                                  10- non-cosited color subsampling Y0Cb(0+1)/2 – Y1Cr(0+1)/2 
                                                                  11- reserved */
        unsigned int  awb_enable             : 1;  /* bit[6]    : auto white balance ON/OFF
                                                                  0 OFF
                                                                  1 ON */
        unsigned int  uvup_ccir_seq          : 2;  /* bit[7-8]  : indicates the Y,Cb,Cr sequencing to manage upsampling in the UVUP module 
                                                                  00- YCbYCr 
                                                                  01- YCrYCb 
                                                                  10- CbYCrY 
                                                                  11- CrYCbY */
        unsigned int  uvup_422_cosited       : 1;  /* bit[9]    : YUV422 input is co-sited or non co-sited
                                                                  0 not co-sited
                                                                  1 co_sited */
        unsigned int  uvup_enable            : 1;  /* bit[10]   : uvup ON/OFF. Note that when Disabled the accept is valid on the on input video port
                                                                  0 OFF
                                                                  1 ON */
        unsigned int  select_ispbe_input_src : 1;  /* bit[11]   : input stream on ISP_BE can be selected to come from ISP_FE/STREAM_ROUTER or from DRAM (VPM_33_x)
                                                                  0 : ISP_FE or STREAM_ROUTER is providing the data stream
                                                                  1 : CVDR(DRAM) is providing the data stream */
        unsigned int  reserved               : 20; /* bit[12-31]: Reserved */
    } reg;
} SOC_ISP_BE_CONTROL_UNION;
#endif
#define SOC_ISP_BE_CONTROL_bayer_pat_be_START            (0)
#define SOC_ISP_BE_CONTROL_bayer_pat_be_END              (1)
#define SOC_ISP_BE_CONTROL_ccir_seq_START                (2)
#define SOC_ISP_BE_CONTROL_ccir_seq_END                  (3)
#define SOC_ISP_BE_CONTROL_conv_422_START                (4)
#define SOC_ISP_BE_CONTROL_conv_422_END                  (5)
#define SOC_ISP_BE_CONTROL_awb_enable_START              (6)
#define SOC_ISP_BE_CONTROL_awb_enable_END                (6)
#define SOC_ISP_BE_CONTROL_uvup_ccir_seq_START           (7)
#define SOC_ISP_BE_CONTROL_uvup_ccir_seq_END             (8)
#define SOC_ISP_BE_CONTROL_uvup_422_cosited_START        (9)
#define SOC_ISP_BE_CONTROL_uvup_422_cosited_END          (9)
#define SOC_ISP_BE_CONTROL_uvup_enable_START             (10)
#define SOC_ISP_BE_CONTROL_uvup_enable_END               (10)
#define SOC_ISP_BE_CONTROL_select_ispbe_input_src_START  (11)
#define SOC_ISP_BE_CONTROL_select_ispbe_input_src_END    (11)


/*****************************************************************************
 结构名    : SOC_ISP_BE_CROP_H_2_UNION
 结构说明  : CROP_H_2 寄存器结构定义。地址偏移量:0x0020，初值:0x00000000，宽度:32
 寄存器说明: Crop horizontal offsets
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ihleft   : 13; /* bit[0-12] : Indicate position of first pixel on the left for the cropped window, 0 means no left crop.  */
        unsigned int  reserved_0: 3;  /* bit[13-15]: reserved */
        unsigned int  ihright  : 13; /* bit[16-28]: Indicate position of last pixel on the right for the cropped window.  */
        unsigned int  reserved_1: 3;  /* bit[29-31]: Reserved */
    } reg;
} SOC_ISP_BE_CROP_H_2_UNION;
#endif
#define SOC_ISP_BE_CROP_H_2_ihleft_START    (0)
#define SOC_ISP_BE_CROP_H_2_ihleft_END      (12)
#define SOC_ISP_BE_CROP_H_2_ihright_START   (16)
#define SOC_ISP_BE_CROP_H_2_ihright_END     (28)


/*****************************************************************************
 结构名    : SOC_ISP_BE_CROP_V_2_UNION
 结构说明  : CROP_V_2 寄存器结构定义。地址偏移量:0x0024，初值:0x00000000，宽度:32
 寄存器说明: Crop vertical offsets
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ivtop    : 13; /* bit[0-12] : indicates position of first line on the top for the cropped window,, 0 means no top crop */
        unsigned int  reserved_0: 3;  /* bit[13-15]: Reserved */
        unsigned int  ivbottom : 13; /* bit[16-28]: indicates position of last line on the bottom for the cropped window */
        unsigned int  reserved_1: 3;  /* bit[29-31]: Reserved */
    } reg;
} SOC_ISP_BE_CROP_V_2_UNION;
#endif
#define SOC_ISP_BE_CROP_V_2_ivtop_START     (0)
#define SOC_ISP_BE_CROP_V_2_ivtop_END       (12)
#define SOC_ISP_BE_CROP_V_2_ivbottom_START  (16)
#define SOC_ISP_BE_CROP_V_2_ivbottom_END    (28)


/*****************************************************************************
 结构名    : SOC_ISP_BE_RGB2YUV_COEFF_0_UNION
 结构说明  : RGB2YUV_COEFF_0 寄存器结构定义。地址偏移量:0x0030，初值:0x00000026，宽度:32
 寄存器说明: Color conversion matrix coefficient
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  y_r      : 9;  /* bit[0-8] : coefficient Y_R */
        unsigned int  reserved : 23; /* bit[9-31]: Reserved */
    } reg;
} SOC_ISP_BE_RGB2YUV_COEFF_0_UNION;
#endif
#define SOC_ISP_BE_RGB2YUV_COEFF_0_y_r_START       (0)
#define SOC_ISP_BE_RGB2YUV_COEFF_0_y_r_END         (8)


/*****************************************************************************
 结构名    : SOC_ISP_BE_RGB2YUV_COEFF_1_UNION
 结构说明  : RGB2YUV_COEFF_1 寄存器结构定义。地址偏移量:0x0034，初值:0x0000004B，宽度:32
 寄存器说明: Color conversion matrix coefficient
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  y_g      : 9;  /* bit[0-8] : coefficient Y_G */
        unsigned int  reserved : 23; /* bit[9-31]: Reserved */
    } reg;
} SOC_ISP_BE_RGB2YUV_COEFF_1_UNION;
#endif
#define SOC_ISP_BE_RGB2YUV_COEFF_1_y_g_START       (0)
#define SOC_ISP_BE_RGB2YUV_COEFF_1_y_g_END         (8)


/*****************************************************************************
 结构名    : SOC_ISP_BE_RGB2YUV_COEFF_2_UNION
 结构说明  : RGB2YUV_COEFF_2 寄存器结构定义。地址偏移量:0x0038，初值:0x0000000F，宽度:32
 寄存器说明: Color conversion matrix coefficient
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  y_b      : 9;  /* bit[0-8] : coefficient Y_B */
        unsigned int  reserved : 23; /* bit[9-31]: Reserved */
    } reg;
} SOC_ISP_BE_RGB2YUV_COEFF_2_UNION;
#endif
#define SOC_ISP_BE_RGB2YUV_COEFF_2_y_b_START       (0)
#define SOC_ISP_BE_RGB2YUV_COEFF_2_y_b_END         (8)


/*****************************************************************************
 结构名    : SOC_ISP_BE_RGB2YUV_COEFF_3_UNION
 结构说明  : RGB2YUV_COEFF_3 寄存器结构定义。地址偏移量:0x003C，初值:0x000001EA，宽度:32
 寄存器说明: Color conversion matrix coefficient
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  u_r      : 9;  /* bit[0-8] : coefficient U_R */
        unsigned int  reserved : 23; /* bit[9-31]: Reserved */
    } reg;
} SOC_ISP_BE_RGB2YUV_COEFF_3_UNION;
#endif
#define SOC_ISP_BE_RGB2YUV_COEFF_3_u_r_START       (0)
#define SOC_ISP_BE_RGB2YUV_COEFF_3_u_r_END         (8)


/*****************************************************************************
 结构名    : SOC_ISP_BE_RGB2YUV_COEFF_4_UNION
 结构说明  : RGB2YUV_COEFF_4 寄存器结构定义。地址偏移量:0x0040，初值:0x000001D6，宽度:32
 寄存器说明: Color conversion matrix coefficient
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  u_g      : 9;  /* bit[0-8] : coefficient U_G */
        unsigned int  reserved : 23; /* bit[9-31]: Reserved */
    } reg;
} SOC_ISP_BE_RGB2YUV_COEFF_4_UNION;
#endif
#define SOC_ISP_BE_RGB2YUV_COEFF_4_u_g_START       (0)
#define SOC_ISP_BE_RGB2YUV_COEFF_4_u_g_END         (8)


/*****************************************************************************
 结构名    : SOC_ISP_BE_RGB2YUV_COEFF_5_UNION
 结构说明  : RGB2YUV_COEFF_5 寄存器结构定义。地址偏移量:0x0044，初值:0x00000040，宽度:32
 寄存器说明: Color conversion matrix coefficient
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  u_b      : 9;  /* bit[0-8] : coefficient U_B */
        unsigned int  reserved : 23; /* bit[9-31]: Reserved */
    } reg;
} SOC_ISP_BE_RGB2YUV_COEFF_5_UNION;
#endif
#define SOC_ISP_BE_RGB2YUV_COEFF_5_u_b_START       (0)
#define SOC_ISP_BE_RGB2YUV_COEFF_5_u_b_END         (8)


/*****************************************************************************
 结构名    : SOC_ISP_BE_RGB2YUV_COEFF_6_UNION
 结构说明  : RGB2YUV_COEFF_6 寄存器结构定义。地址偏移量:0x0048，初值:0x00000040，宽度:32
 寄存器说明: Color conversion matrix coefficient
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  v_r      : 9;  /* bit[0-8] : coefficient V_R */
        unsigned int  reserved : 23; /* bit[9-31]: Reserved */
    } reg;
} SOC_ISP_BE_RGB2YUV_COEFF_6_UNION;
#endif
#define SOC_ISP_BE_RGB2YUV_COEFF_6_v_r_START       (0)
#define SOC_ISP_BE_RGB2YUV_COEFF_6_v_r_END         (8)


/*****************************************************************************
 结构名    : SOC_ISP_BE_RGB2YUV_COEFF_7_UNION
 结构说明  : RGB2YUV_COEFF_7 寄存器结构定义。地址偏移量:0x004C，初值:0x000001CA，宽度:32
 寄存器说明: Color conversion matrix coefficient
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  v_g      : 9;  /* bit[0-8] : coefficient V_G */
        unsigned int  reserved : 23; /* bit[9-31]: Reserved */
    } reg;
} SOC_ISP_BE_RGB2YUV_COEFF_7_UNION;
#endif
#define SOC_ISP_BE_RGB2YUV_COEFF_7_v_g_START       (0)
#define SOC_ISP_BE_RGB2YUV_COEFF_7_v_g_END         (8)


/*****************************************************************************
 结构名    : SOC_ISP_BE_RGB2YUV_COEFF_8_UNION
 结构说明  : RGB2YUV_COEFF_8 寄存器结构定义。地址偏移量:0x0050，初值:0x000001F6，宽度:32
 寄存器说明: Color conversion matrix coefficient
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  v_b      : 9;  /* bit[0-8] : coefficient V_B */
        unsigned int  reserved : 23; /* bit[9-31]: Reserved */
    } reg;
} SOC_ISP_BE_RGB2YUV_COEFF_8_UNION;
#endif
#define SOC_ISP_BE_RGB2YUV_COEFF_8_v_b_START       (0)
#define SOC_ISP_BE_RGB2YUV_COEFF_8_v_b_END         (8)


/*****************************************************************************
 结构名    : SOC_ISP_BE_YUV2RGB_COEFF_0_UNION
 结构说明  : YUV2RGB_COEFF_0 寄存器结构定义。地址偏移量:0x0060，初值:0x00000080，宽度:32
 寄存器说明: Color conversion matrix coefficient
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  r_y      : 9;  /* bit[0-8] : coefficient R_Y */
        unsigned int  reserved : 23; /* bit[9-31]: Reserved */
    } reg;
} SOC_ISP_BE_YUV2RGB_COEFF_0_UNION;
#endif
#define SOC_ISP_BE_YUV2RGB_COEFF_0_r_y_START       (0)
#define SOC_ISP_BE_YUV2RGB_COEFF_0_r_y_END         (8)


/*****************************************************************************
 结构名    : SOC_ISP_BE_YUV2RGB_COEFF_1_UNION
 结构说明  : YUV2RGB_COEFF_1 寄存器结构定义。地址偏移量:0x0064，初值:0x00000000，宽度:32
 寄存器说明: Color conversion matrix coefficient
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  r_u      : 9;  /* bit[0-8] : coefficient R_U */
        unsigned int  reserved : 23; /* bit[9-31]: Reserved */
    } reg;
} SOC_ISP_BE_YUV2RGB_COEFF_1_UNION;
#endif
#define SOC_ISP_BE_YUV2RGB_COEFF_1_r_u_START       (0)
#define SOC_ISP_BE_YUV2RGB_COEFF_1_r_u_END         (8)


/*****************************************************************************
 结构名    : SOC_ISP_BE_YUV2RGB_COEFF_2_UNION
 结构说明  : YUV2RGB_COEFF_2 寄存器结构定义。地址偏移量:0x0068，初值:0x000000B3，宽度:32
 寄存器说明: Color conversion matrix coefficient
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  r_v      : 9;  /* bit[0-8] : coefficient R_V */
        unsigned int  reserved : 23; /* bit[9-31]: Reserved */
    } reg;
} SOC_ISP_BE_YUV2RGB_COEFF_2_UNION;
#endif
#define SOC_ISP_BE_YUV2RGB_COEFF_2_r_v_START       (0)
#define SOC_ISP_BE_YUV2RGB_COEFF_2_r_v_END         (8)


/*****************************************************************************
 结构名    : SOC_ISP_BE_YUV2RGB_COEFF_3_UNION
 结构说明  : YUV2RGB_COEFF_3 寄存器结构定义。地址偏移量:0x006C，初值:0x00000080，宽度:32
 寄存器说明: Color conversion matrix coefficient
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g_y      : 9;  /* bit[0-8] : coefficient G_Y */
        unsigned int  reserved : 23; /* bit[9-31]: Reserved */
    } reg;
} SOC_ISP_BE_YUV2RGB_COEFF_3_UNION;
#endif
#define SOC_ISP_BE_YUV2RGB_COEFF_3_g_y_START       (0)
#define SOC_ISP_BE_YUV2RGB_COEFF_3_g_y_END         (8)


/*****************************************************************************
 结构名    : SOC_ISP_BE_YUV2RGB_COEFF_4_UNION
 结构说明  : YUV2RGB_COEFF_4 寄存器结构定义。地址偏移量:0x0070，初值:0x000001D5，宽度:32
 寄存器说明: Color conversion matrix coefficient
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g_u      : 9;  /* bit[0-8] : coefficient G_U */
        unsigned int  reserved : 23; /* bit[9-31]: Reserved */
    } reg;
} SOC_ISP_BE_YUV2RGB_COEFF_4_UNION;
#endif
#define SOC_ISP_BE_YUV2RGB_COEFF_4_g_u_START       (0)
#define SOC_ISP_BE_YUV2RGB_COEFF_4_g_u_END         (8)


/*****************************************************************************
 结构名    : SOC_ISP_BE_YUV2RGB_COEFF_5_UNION
 结构说明  : YUV2RGB_COEFF_5 寄存器结构定义。地址偏移量:0x0074，初值:0x000001A5，宽度:32
 寄存器说明: Color conversion matrix coefficient
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g_v      : 9;  /* bit[0-8] : coefficient G_V */
        unsigned int  reserved : 23; /* bit[9-31]: Reserved */
    } reg;
} SOC_ISP_BE_YUV2RGB_COEFF_5_UNION;
#endif
#define SOC_ISP_BE_YUV2RGB_COEFF_5_g_v_START       (0)
#define SOC_ISP_BE_YUV2RGB_COEFF_5_g_v_END         (8)


/*****************************************************************************
 结构名    : SOC_ISP_BE_YUV2RGB_COEFF_6_UNION
 结构说明  : YUV2RGB_COEFF_6 寄存器结构定义。地址偏移量:0x0078，初值:0x00000080，宽度:32
 寄存器说明: Color conversion matrix coefficient
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  b_y      : 9;  /* bit[0-8] : coefficient B_Y */
        unsigned int  reserved : 23; /* bit[9-31]: Reserved */
    } reg;
} SOC_ISP_BE_YUV2RGB_COEFF_6_UNION;
#endif
#define SOC_ISP_BE_YUV2RGB_COEFF_6_b_y_START       (0)
#define SOC_ISP_BE_YUV2RGB_COEFF_6_b_y_END         (8)


/*****************************************************************************
 结构名    : SOC_ISP_BE_YUV2RGB_COEFF_7_UNION
 结构说明  : YUV2RGB_COEFF_7 寄存器结构定义。地址偏移量:0x007C，初值:0x000000E1，宽度:32
 寄存器说明: Color conversion matrix coefficient
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  b_u      : 9;  /* bit[0-8] : coefficient B_U */
        unsigned int  reserved : 23; /* bit[9-31]: Reserved */
    } reg;
} SOC_ISP_BE_YUV2RGB_COEFF_7_UNION;
#endif
#define SOC_ISP_BE_YUV2RGB_COEFF_7_b_u_START       (0)
#define SOC_ISP_BE_YUV2RGB_COEFF_7_b_u_END         (8)


/*****************************************************************************
 结构名    : SOC_ISP_BE_YUV2RGB_COEFF_8_UNION
 结构说明  : YUV2RGB_COEFF_8 寄存器结构定义。地址偏移量:0x0080，初值:0x00000000，宽度:32
 寄存器说明: Color conversion matrix coefficient
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  b_v      : 9;  /* bit[0-8] : coefficient B_V */
        unsigned int  reserved : 23; /* bit[9-31]: Reserved */
    } reg;
} SOC_ISP_BE_YUV2RGB_COEFF_8_UNION;
#endif
#define SOC_ISP_BE_YUV2RGB_COEFF_8_b_v_START       (0)
#define SOC_ISP_BE_YUV2RGB_COEFF_8_b_v_END         (8)


/*****************************************************************************
 结构名    : SOC_ISP_BE_PTREG_UNION
 结构说明  : PTREG 寄存器结构定义。地址偏移量:0x0090，初值:0x00000010，宽度:32
 寄存器说明: Ratio
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ratio    : 5;  /* bit[0-4] : The throughput ratio between the ISP capability of the pipe and the use case requirement is indicated as a decimal value on 4 bit. 1 = 0.h10.the increment as 1/16 granularity
                                                   The register holds the value N/M which is used as a decimal part [O,1[ in the PTREG to simplify the design. 
                                                   0x10 : PTREG behaves as a bypass 
                                                   0x0x : Indicates a bandwidth ratio with 1/16 granularity
                                                   0x1x : with x different from zero is reserved */
        unsigned int  reserved : 27; /* bit[5-31]: Reserved */
    } reg;
} SOC_ISP_BE_PTREG_UNION;
#endif
#define SOC_ISP_BE_PTREG_ratio_START     (0)
#define SOC_ISP_BE_PTREG_ratio_END       (4)


/*****************************************************************************
 结构名    : SOC_ISP_BE_FORCE_CLK_ON_CFG_UNION
 结构说明  : FORCE_CLK_ON_CFG 寄存器结构定义。地址偏移量:0x00A0，初值:0x00003FFF，宽度:32
 寄存器说明: used to force the clock which is generally controlled by HW
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  force_clk_on_0  : 1;  /* bit[0]    : AWBGAIN_(x) clock is controlled by idle_detector by default. If set to '1', this will force the clock ON */
        unsigned int  force_clk_on_1  : 1;  /* bit[1]    : GCD_(x) clock is controlled by idle_detector by default. If set to '1', this will force the clock ON */
        unsigned int  force_clk_on_2  : 1;  /* bit[2]    : UVUP_(x) clock is controlled by idle_detector by default. If set to '1', this will force the clock ON  */
        unsigned int  force_clk_on_3  : 1;  /* bit[3]    : CC_(x) clock is controlled by idle_detector by default. If set to '1', this will force the clock ON */
        unsigned int  force_clk_on_4  : 1;  /* bit[4]    : DRC_(x) clock is controlled by idle_detector by default. If set to '1', this will force the clock ON */
        unsigned int  force_clk_on_5  : 1;  /* bit[5]    : GAMMA_(x) clock is controlled by idle_detector by default. If set to '1', this will force the clock ON */
        unsigned int  force_clk_on_6  : 1;  /* bit[6]    : YUV2RGB_(x) clock is controlled by idle_detector by default. If set to '1', this will force the clock ON */
        unsigned int  force_clk_on_7  : 1;  /* bit[7]    : UVDEC_(x) clock is controlled by idle_detector by default. If set to '1', this will force the clock ON */
        unsigned int  force_clk_on_8  : 1;  /* bit[8]    : CE_(x) clock is controlled by idle_detector by default. If set to '1', this will force the clock ON */
        unsigned int  force_clk_on_9  : 1;  /* bit[9]    : YUVNF_(x) clock is controlled by idle_detector by default. If set to '1', this will force the clock ON */
        unsigned int  force_clk_on_10 : 1;  /* bit[10]   : SHARPEN_(x) clock is controlled by idle_detector by default. If set to '1', this will force the clock ON */
        unsigned int  force_clk_on_11 : 1;  /* bit[11]   : TNR_(x) clock is controlled by idle_detector by default. If set to '1', this will force the clock ON */
        unsigned int  force_clk_on_12 : 1;  /* bit[12]   : IE_(x) clock is controlled by idle_detector by default. If set to '1', this will force the clock ON */
        unsigned int  force_clk_on_13 : 1;  /* bit[13]   : BE top logic clock is controlled by idle_detector by default. If set to '1', this will force the clock ON (clock also used by idle_detector)  */
        unsigned int  reserved        : 18; /* bit[14-31]: Reserved */
    } reg;
} SOC_ISP_BE_FORCE_CLK_ON_CFG_UNION;
#endif
#define SOC_ISP_BE_FORCE_CLK_ON_CFG_force_clk_on_0_START   (0)
#define SOC_ISP_BE_FORCE_CLK_ON_CFG_force_clk_on_0_END     (0)
#define SOC_ISP_BE_FORCE_CLK_ON_CFG_force_clk_on_1_START   (1)
#define SOC_ISP_BE_FORCE_CLK_ON_CFG_force_clk_on_1_END     (1)
#define SOC_ISP_BE_FORCE_CLK_ON_CFG_force_clk_on_2_START   (2)
#define SOC_ISP_BE_FORCE_CLK_ON_CFG_force_clk_on_2_END     (2)
#define SOC_ISP_BE_FORCE_CLK_ON_CFG_force_clk_on_3_START   (3)
#define SOC_ISP_BE_FORCE_CLK_ON_CFG_force_clk_on_3_END     (3)
#define SOC_ISP_BE_FORCE_CLK_ON_CFG_force_clk_on_4_START   (4)
#define SOC_ISP_BE_FORCE_CLK_ON_CFG_force_clk_on_4_END     (4)
#define SOC_ISP_BE_FORCE_CLK_ON_CFG_force_clk_on_5_START   (5)
#define SOC_ISP_BE_FORCE_CLK_ON_CFG_force_clk_on_5_END     (5)
#define SOC_ISP_BE_FORCE_CLK_ON_CFG_force_clk_on_6_START   (6)
#define SOC_ISP_BE_FORCE_CLK_ON_CFG_force_clk_on_6_END     (6)
#define SOC_ISP_BE_FORCE_CLK_ON_CFG_force_clk_on_7_START   (7)
#define SOC_ISP_BE_FORCE_CLK_ON_CFG_force_clk_on_7_END     (7)
#define SOC_ISP_BE_FORCE_CLK_ON_CFG_force_clk_on_8_START   (8)
#define SOC_ISP_BE_FORCE_CLK_ON_CFG_force_clk_on_8_END     (8)
#define SOC_ISP_BE_FORCE_CLK_ON_CFG_force_clk_on_9_START   (9)
#define SOC_ISP_BE_FORCE_CLK_ON_CFG_force_clk_on_9_END     (9)
#define SOC_ISP_BE_FORCE_CLK_ON_CFG_force_clk_on_10_START  (10)
#define SOC_ISP_BE_FORCE_CLK_ON_CFG_force_clk_on_10_END    (10)
#define SOC_ISP_BE_FORCE_CLK_ON_CFG_force_clk_on_11_START  (11)
#define SOC_ISP_BE_FORCE_CLK_ON_CFG_force_clk_on_11_END    (11)
#define SOC_ISP_BE_FORCE_CLK_ON_CFG_force_clk_on_12_START  (12)
#define SOC_ISP_BE_FORCE_CLK_ON_CFG_force_clk_on_12_END    (12)
#define SOC_ISP_BE_FORCE_CLK_ON_CFG_force_clk_on_13_START  (13)
#define SOC_ISP_BE_FORCE_CLK_ON_CFG_force_clk_on_13_END    (13)






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

#endif /* end of soc_isp_be_interface.h */
