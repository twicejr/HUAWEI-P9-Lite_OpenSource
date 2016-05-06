/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_dss_sbl_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:20:23
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_DSS_SBL.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_DSS_SBL_INTERFACE_H__
#define __SOC_DSS_SBL_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) reg_SBL
 ****************************************************************************/
/* 寄存器说明：数据格式
   位域定义UNION结构:  SOC_DSS_SBL_DATA_FORMAT_UNION */
#define SOC_DSS_SBL_DATA_FORMAT_ADDR(base)            ((base) + (0x0000))

/* 寄存器说明：控制寄存器
   位域定义UNION结构:  SOC_DSS_SBL_CONTROL_REG1_UNION */
#define SOC_DSS_SBL_CONTROL_REG1_ADDR(base)           ((base) + (0x0004))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_HS_POS_L_UNION */
#define SOC_DSS_SBL_HS_POS_L_ADDR(base)               ((base) + (0x0008))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_HS_POS_H_UNION */
#define SOC_DSS_SBL_HS_POS_H_ADDR(base)               ((base) + (0x000C))

/* 寄存器说明：帧宽度
   位域定义UNION结构:  SOC_DSS_SBL_FRAME_WIDTH_L_UNION */
#define SOC_DSS_SBL_FRAME_WIDTH_L_ADDR(base)          ((base) + (0x0010))

/* 寄存器说明：帧宽度
   位域定义UNION结构:  SOC_DSS_SBL_FRAME_WIDTH_H_UNION */
#define SOC_DSS_SBL_FRAME_WIDTH_H_ADDR(base)          ((base) + (0x00000014))

/* 寄存器说明：帧高度
   位域定义UNION结构:  SOC_DSS_SBL_FRAME_HEIGHT_L_UNION */
#define SOC_DSS_SBL_FRAME_HEIGHT_L_ADDR(base)         ((base) + (0x0018))

/* 寄存器说明：帧高度
   位域定义UNION结构:  SOC_DSS_SBL_FRAME_HEIGHT_H_UNION */
#define SOC_DSS_SBL_FRAME_HEIGHT_H_ADDR(base)         ((base) + (0x001C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_VS_POS_L_UNION */
#define SOC_DSS_SBL_VS_POS_L_ADDR(base)               ((base) + (0x0020))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_VS_POS_H_UNION */
#define SOC_DSS_SBL_VS_POS_H_ADDR(base)               ((base) + (0x0024))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_ENABLE_UNION */
#define SOC_DSS_SBL_ENABLE_ADDR(base)                 ((base) + (0x0400))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_STRENGTH_UNION */
#define SOC_DSS_SBL_STRENGTH_ADDR(base)               ((base) + (0x0408))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_VARIANCE_INTENSITY_SPACE_UNION */
#define SOC_DSS_SBL_VARIANCE_INTENSITY_SPACE_ADDR(base) ((base) + (0x040C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_SLOPE_MAX_UNION */
#define SOC_DSS_SBL_SLOPE_MAX_ADDR(base)              ((base) + (0x0410))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_SLOPE_MIN_UNION */
#define SOC_DSS_SBL_SLOPE_MIN_ADDR(base)              ((base) + (0x0414))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_BLACK_LEVEL_L_UNION */
#define SOC_DSS_SBL_BLACK_LEVEL_L_ADDR(base)          ((base) + (0x0418))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_BLACK_LEVEL_H_UNION */
#define SOC_DSS_SBL_BLACK_LEVEL_H_ADDR(base)          ((base) + (0x041C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_WHITE_LEVEL_L_UNION */
#define SOC_DSS_SBL_WHITE_LEVEL_L_ADDR(base)          ((base) + (0x0420))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_WHITE_LEVEL_H_UNION */
#define SOC_DSS_SBL_WHITE_LEVEL_H_ADDR(base)          ((base) + (0x0424))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_BRIGHT_DARK_AMP_LIMIT_UNION */
#define SOC_DSS_SBL_BRIGHT_DARK_AMP_LIMIT_ADDR(base)  ((base) + (0x0428))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_DITHER_MODE_UNION */
#define SOC_DSS_SBL_DITHER_MODE_ADDR(base)            ((base) + (0x042C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_CONFIG_BUFFER_MODE_UNION */
#define SOC_DSS_SBL_CONFIG_BUFFER_MODE_ADDR(base)     ((base) + (0x0430))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_CONFIG_BUFFER_GLOBAL_UNION */
#define SOC_DSS_SBL_CONFIG_BUFFER_GLOBAL_ADDR(base)   ((base) + (0x0434))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_ASYMMETRY_LUT_ADDR_UNION */
#define SOC_DSS_SBL_ASYMMETRY_LUT_ADDR_ADDR(base)     ((base) + (0x0480))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_ASYMMETRY_LUT_WRITE_DATA_L_UNION */
#define SOC_DSS_SBL_ASYMMETRY_LUT_WRITE_DATA_L_ADDR(base) ((base) + (0x0484))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_ASYMMETRY_LUT_WRITE_DATA_H_UNION */
#define SOC_DSS_SBL_ASYMMETRY_LUT_WRITE_DATA_H_ADDR(base) ((base) + (0x0488))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_COLOR_CORRECTION_LUT_ADDR_UNION */
#define SOC_DSS_SBL_COLOR_CORRECTION_LUT_ADDR_ADDR(base) ((base) + (0x04C0))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_COLOR_CORRECTION_LUT_WRITE_DATA_L_UNION */
#define SOC_DSS_SBL_COLOR_CORRECTION_LUT_WRITE_DATA_L_ADDR(base) ((base) + (0x04C4))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_COLOR_CORRECTION_LUT_WRITE_DATA_H_UNION */
#define SOC_DSS_SBL_COLOR_CORRECTION_LUT_WRITE_DATA_H_ADDR(base) ((base) + (0x04C8))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_LOGO_LEFT_UNION */
#define SOC_DSS_SBL_LOGO_LEFT_ADDR(base)              ((base) + (0x0800))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_LOGO_TOP_UNION */
#define SOC_DSS_SBL_LOGO_TOP_ADDR(base)               ((base) + (0x0804))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_APICAL_DITHER_UNION */
#define SOC_DSS_SBL_APICAL_DITHER_ADDR(base)          ((base) + (0x0840))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_AUTOMATIC_START_CALC_STRENGTH_DRC_BACKLIGHT_SEL_UNION */
#define SOC_DSS_SBL_AUTOMATIC_START_CALC_STRENGTH_DRC_BACKLIGHT_SEL_ADDR(base) ((base) + (0x0C00))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_STRENGTH_MANUAL_UNION */
#define SOC_DSS_SBL_STRENGTH_MANUAL_ADDR(base)        ((base) + (0x0C04))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_DRC_IN_L_UNION */
#define SOC_DSS_SBL_DRC_IN_L_ADDR(base)               ((base) + (0x0C08))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_DRC_IN_H_UNION */
#define SOC_DSS_SBL_DRC_IN_H_ADDR(base)               ((base) + (0x0C0C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_BACKLIGHT_L_UNION */
#define SOC_DSS_SBL_BACKLIGHT_L_ADDR(base)            ((base) + (0x0C10))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_BACKLIGHT_H_UNION */
#define SOC_DSS_SBL_BACKLIGHT_H_ADDR(base)            ((base) + (0x0C14))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_AMBIENT_LIGHT_L_UNION */
#define SOC_DSS_SBL_AMBIENT_LIGHT_L_ADDR(base)        ((base) + (0x0C18))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_AMBIENT_LIGHT_H_UNION */
#define SOC_DSS_SBL_AMBIENT_LIGHT_H_ADDR(base)        ((base) + (0x0C1C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_START_CALC_UNION */
#define SOC_DSS_SBL_START_CALC_ADDR(base)             ((base) + (0x0C20))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_STRENGTH_LIMIT_UNION */
#define SOC_DSS_SBL_STRENGTH_LIMIT_ADDR(base)         ((base) + (0x0C24))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_CALIBRATION_A_L_UNION */
#define SOC_DSS_SBL_CALIBRATION_A_L_ADDR(base)        ((base) + (0x0C28))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_CALIBRATION_A_H_UNION */
#define SOC_DSS_SBL_CALIBRATION_A_H_ADDR(base)        ((base) + (0x0C2C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_CALIBRATION_B_L_UNION */
#define SOC_DSS_SBL_CALIBRATION_B_L_ADDR(base)        ((base) + (0x0C30))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_CALIBRATION_B_H_UNION */
#define SOC_DSS_SBL_CALIBRATION_B_H_ADDR(base)        ((base) + (0x0C34))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_CALIBRATION_C_L_UNION */
#define SOC_DSS_SBL_CALIBRATION_C_L_ADDR(base)        ((base) + (0x0C38))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_CALIBRATION_C_H_UNION */
#define SOC_DSS_SBL_CALIBRATION_C_H_ADDR(base)        ((base) + (0x0C3C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_CALIBRATION_D_L_UNION */
#define SOC_DSS_SBL_CALIBRATION_D_L_ADDR(base)        ((base) + (0x0C40))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_CALIBRATION_D_H_UNION */
#define SOC_DSS_SBL_CALIBRATION_D_H_ADDR(base)        ((base) + (0x0C44))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_T_FILTER_CONTROL_UNION */
#define SOC_DSS_SBL_T_FILTER_CONTROL_ADDR(base)       ((base) + (0x0C48))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_BACKLIGHT_MIN_L_UNION */
#define SOC_DSS_SBL_BACKLIGHT_MIN_L_ADDR(base)        ((base) + (0x0C4C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_BACKLIGHT_MIN_H_UNION */
#define SOC_DSS_SBL_BACKLIGHT_MIN_H_ADDR(base)        ((base) + (0x0C50))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_BACKLIGHT_MAX_L_UNION */
#define SOC_DSS_SBL_BACKLIGHT_MAX_L_ADDR(base)        ((base) + (0x0C54))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_BACKLIGHT_MAX_H_UNION */
#define SOC_DSS_SBL_BACKLIGHT_MAX_H_ADDR(base)        ((base) + (0x0C58))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_BACKLIGHT_SCALE_L_UNION */
#define SOC_DSS_SBL_BACKLIGHT_SCALE_L_ADDR(base)      ((base) + (0x0C5C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_BACKLIGHT_SCALE_H_UNION */
#define SOC_DSS_SBL_BACKLIGHT_SCALE_H_ADDR(base)      ((base) + (0x0C60))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_AMBIENT_LIGHT_MIN_L_UNION */
#define SOC_DSS_SBL_AMBIENT_LIGHT_MIN_L_ADDR(base)    ((base) + (0x0C64))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_AMBIENT_LIGHT_MIN_H_UNION */
#define SOC_DSS_SBL_AMBIENT_LIGHT_MIN_H_ADDR(base)    ((base) + (0x0C68))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_FILTER_A_L_UNION */
#define SOC_DSS_SBL_FILTER_A_L_ADDR(base)             ((base) + (0x0C6C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_FILTER_A_H_UNION */
#define SOC_DSS_SBL_FILTER_A_H_ADDR(base)             ((base) + (0x0C70))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_FILTER_B_UNION */
#define SOC_DSS_SBL_FILTER_B_ADDR(base)               ((base) + (0x0C74))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_STRENGTH_OUT_UNION */
#define SOC_DSS_SBL_STRENGTH_OUT_ADDR(base)           ((base) + (0x0C80))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_DRC_OUT_L_UNION */
#define SOC_DSS_SBL_DRC_OUT_L_ADDR(base)              ((base) + (0x0C84))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_DRC_OUT_H_UNION */
#define SOC_DSS_SBL_DRC_OUT_H_ADDR(base)              ((base) + (0x0C88))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_BACKLIGHT_OUT_L_UNION */
#define SOC_DSS_SBL_BACKLIGHT_OUT_L_ADDR(base)        ((base) + (0x0C8C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_BACKLIGHT_OUT_H_UNION */
#define SOC_DSS_SBL_BACKLIGHT_OUT_H_ADDR(base)        ((base) + (0x0C90))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_CALC_DONE_UNION */
#define SOC_DSS_SBL_CALC_DONE_ADDR(base)              ((base) + (0x0C94))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_AL_CALIB_LUT_LUT_ADDR_UNION */
#define SOC_DSS_SBL_AL_CALIB_LUT_LUT_ADDR_ADDR(base)  ((base) + (0x0F00))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_AL_CALIB_LUT_LUT_WRITE_DATA_L_UNION */
#define SOC_DSS_SBL_AL_CALIB_LUT_LUT_WRITE_DATA_L_ADDR(base) ((base) + (0x0F10))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_SBL_AL_CALIB_LUT_LUT_WRITE_DATA_H_UNION */
#define SOC_DSS_SBL_AL_CALIB_LUT_LUT_WRITE_DATA_H_ADDR(base) ((base) + (0x0F14))





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
                     (1/1) reg_SBL
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_DSS_SBL_DATA_FORMAT_UNION
 结构说明  : DATA_FORMAT 寄存器结构定义。地址偏移量:0x0000，初值:0x00000003，宽度:32
 寄存器说明: 数据格式
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  data_format : 2;  /* bit[0-1] :  */
        unsigned int  reserved    : 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_DSS_SBL_DATA_FORMAT_UNION;
#endif
#define SOC_DSS_SBL_DATA_FORMAT_data_format_START  (0)
#define SOC_DSS_SBL_DATA_FORMAT_data_format_END    (1)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_CONTROL_REG1_UNION
 结构说明  : CONTROL_REG1 寄存器结构定义。地址偏移量:0x0004，初值:0x00000000，宽度:32
 寄存器说明: 控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  contrlo_reg1 : 8;  /* bit[0-7] :  */
        unsigned int  reserved     : 24; /* bit[8-31]: Control Reg1（sync_format）.Should be Zero */
    } reg;
} SOC_DSS_SBL_CONTROL_REG1_UNION;
#endif
#define SOC_DSS_SBL_CONTROL_REG1_contrlo_reg1_START  (0)
#define SOC_DSS_SBL_CONTROL_REG1_contrlo_reg1_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_HS_POS_L_UNION
 结构说明  : HS_POS_L 寄存器结构定义。地址偏移量:0x0008，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hs_pos_l : 8;  /* bit[0-7] :  */
        unsigned int  reserved : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_HS_POS_L_UNION;
#endif
#define SOC_DSS_SBL_HS_POS_L_hs_pos_l_START  (0)
#define SOC_DSS_SBL_HS_POS_L_hs_pos_l_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_HS_POS_H_UNION
 结构说明  : HS_POS_H 寄存器结构定义。地址偏移量:0x000C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hs_pos_h : 8;  /* bit[0-7] :  */
        unsigned int  reserved : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_HS_POS_H_UNION;
#endif
#define SOC_DSS_SBL_HS_POS_H_hs_pos_h_START  (0)
#define SOC_DSS_SBL_HS_POS_H_hs_pos_h_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_FRAME_WIDTH_L_UNION
 结构说明  : FRAME_WIDTH_L 寄存器结构定义。地址偏移量:0x0010，初值:0x00000000，宽度:32
 寄存器说明: 帧宽度
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  frame_width_l : 8;  /* bit[0-7] :  */
        unsigned int  reserved      : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_FRAME_WIDTH_L_UNION;
#endif
#define SOC_DSS_SBL_FRAME_WIDTH_L_frame_width_l_START  (0)
#define SOC_DSS_SBL_FRAME_WIDTH_L_frame_width_l_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_FRAME_WIDTH_H_UNION
 结构说明  : FRAME_WIDTH_H 寄存器结构定义。地址偏移量:0x00000014，初值:0x00000001，宽度:32
 寄存器说明: 帧宽度
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  frame_width_h : 8;  /* bit[0-7] :  */
        unsigned int  reserved      : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_FRAME_WIDTH_H_UNION;
#endif
#define SOC_DSS_SBL_FRAME_WIDTH_H_frame_width_h_START  (0)
#define SOC_DSS_SBL_FRAME_WIDTH_H_frame_width_h_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_FRAME_HEIGHT_L_UNION
 结构说明  : FRAME_HEIGHT_L 寄存器结构定义。地址偏移量:0x0018，初值:0x00000000，宽度:32
 寄存器说明: 帧高度
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  frame_height_l : 8;  /* bit[0-7] :  */
        unsigned int  reserved       : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_FRAME_HEIGHT_L_UNION;
#endif
#define SOC_DSS_SBL_FRAME_HEIGHT_L_frame_height_l_START  (0)
#define SOC_DSS_SBL_FRAME_HEIGHT_L_frame_height_l_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_FRAME_HEIGHT_H_UNION
 结构说明  : FRAME_HEIGHT_H 寄存器结构定义。地址偏移量:0x001C，初值:0x00000001，宽度:32
 寄存器说明: 帧高度
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  frame_height_h : 8;  /* bit[0-7] :  */
        unsigned int  reserved       : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_FRAME_HEIGHT_H_UNION;
#endif
#define SOC_DSS_SBL_FRAME_HEIGHT_H_frame_height_h_START  (0)
#define SOC_DSS_SBL_FRAME_HEIGHT_H_frame_height_h_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_VS_POS_L_UNION
 结构说明  : VS_POS_L 寄存器结构定义。地址偏移量:0x0020，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vs_pos_l : 8;  /* bit[0-7] :  */
        unsigned int  reserved : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_VS_POS_L_UNION;
#endif
#define SOC_DSS_SBL_VS_POS_L_vs_pos_l_START  (0)
#define SOC_DSS_SBL_VS_POS_L_vs_pos_l_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_VS_POS_H_UNION
 结构说明  : VS_POS_H 寄存器结构定义。地址偏移量:0x0024，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vs_pos_h : 8;  /* bit[0-7] :  */
        unsigned int  reserved : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_VS_POS_H_UNION;
#endif
#define SOC_DSS_SBL_VS_POS_H_vs_pos_h_START  (0)
#define SOC_DSS_SBL_VS_POS_H_vs_pos_h_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_ENABLE_UNION
 结构说明  : ENABLE 寄存器结构定义。地址偏移量:0x0400，初值:0x00000007，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  enable           : 1;  /* bit[0]   : 0:off 1:on */
        unsigned int  local_contrast   : 2;  /* bit[1-2] :  */
        unsigned int  reserved_0       : 1;  /* bit[3]   :  */
        unsigned int  color_correction : 1;  /* bit[4]   :  */
        unsigned int  reserved_1       : 27; /* bit[5-31]:  */
    } reg;
} SOC_DSS_SBL_ENABLE_UNION;
#endif
#define SOC_DSS_SBL_ENABLE_enable_START            (0)
#define SOC_DSS_SBL_ENABLE_enable_END              (0)
#define SOC_DSS_SBL_ENABLE_local_contrast_START    (1)
#define SOC_DSS_SBL_ENABLE_local_contrast_END      (2)
#define SOC_DSS_SBL_ENABLE_color_correction_START  (4)
#define SOC_DSS_SBL_ENABLE_color_correction_END    (4)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_STRENGTH_UNION
 结构说明  : STRENGTH 寄存器结构定义。地址偏移量:0x0408，初值:0x00000080，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  strength : 8;  /* bit[0-7] : Note:DO NOT USE (LEGACY BEHAV)-THIS REGISTER IS NOT USED TO CONTROL IRIDIX STRENGTH.USE strength_manual INSTEAD.Strength od dynamic range compression.With other parameters at defaults,increases visibility of shadows. */
        unsigned int  reserved : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_STRENGTH_UNION;
#endif
#define SOC_DSS_SBL_STRENGTH_strength_START  (0)
#define SOC_DSS_SBL_STRENGTH_strength_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_VARIANCE_INTENSITY_SPACE_UNION
 结构说明  : VARIANCE_INTENSITY_SPACE 寄存器结构定义。地址偏移量:0x040C，初值:0x00000041，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  variance_space     : 4;  /* bit[0-3] : Sets the degree of spatial sensitivity of the algorithm */
        unsigned int  variance_intensity : 4;  /* bit[4-7] : Sets the degree of luminance sensitivity of the algorithm */
        unsigned int  reserved           : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_VARIANCE_INTENSITY_SPACE_UNION;
#endif
#define SOC_DSS_SBL_VARIANCE_INTENSITY_SPACE_variance_space_START      (0)
#define SOC_DSS_SBL_VARIANCE_INTENSITY_SPACE_variance_space_END        (3)
#define SOC_DSS_SBL_VARIANCE_INTENSITY_SPACE_variance_intensity_START  (4)
#define SOC_DSS_SBL_VARIANCE_INTENSITY_SPACE_variance_intensity_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_SLOPE_MAX_UNION
 结构说明  : SLOPE_MAX 寄存器结构定义。地址偏移量:0x0410，初值:0x0000003C，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  slope_max : 8;  /* bit[0-7] : Restricts the maximum slope(gain) which can be generated by the adaptive algorithm */
        unsigned int  reserved  : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_SLOPE_MAX_UNION;
#endif
#define SOC_DSS_SBL_SLOPE_MAX_slope_max_START  (0)
#define SOC_DSS_SBL_SLOPE_MAX_slope_max_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_SLOPE_MIN_UNION
 结构说明  : SLOPE_MIN 寄存器结构定义。地址偏移量:0x0414，初值:0x00000080，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  slope_min : 8;  /* bit[0-7] : Restricts the minimum slope(gain) which can be generated by the adaptive algorithm */
        unsigned int  reserved  : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_SLOPE_MIN_UNION;
#endif
#define SOC_DSS_SBL_SLOPE_MIN_slope_min_START  (0)
#define SOC_DSS_SBL_SLOPE_MIN_slope_min_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_BLACK_LEVEL_L_UNION
 结构说明  : BLACK_LEVEL_L 寄存器结构定义。地址偏移量:0x0418，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  black_level_l : 8;  /* bit[0-7] : Sets black level for iridix processing */
        unsigned int  reserved      : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_BLACK_LEVEL_L_UNION;
#endif
#define SOC_DSS_SBL_BLACK_LEVEL_L_black_level_l_START  (0)
#define SOC_DSS_SBL_BLACK_LEVEL_L_black_level_l_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_BLACK_LEVEL_H_UNION
 结构说明  : BLACK_LEVEL_H 寄存器结构定义。地址偏移量:0x041C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  black_level_h : 2;  /* bit[0-1] : Sets black level for iridix processing */
        unsigned int  reserved      : 30; /* bit[2-31]:  */
    } reg;
} SOC_DSS_SBL_BLACK_LEVEL_H_UNION;
#endif
#define SOC_DSS_SBL_BLACK_LEVEL_H_black_level_h_START  (0)
#define SOC_DSS_SBL_BLACK_LEVEL_H_black_level_h_END    (1)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_WHITE_LEVEL_L_UNION
 结构说明  : WHITE_LEVEL_L 寄存器结构定义。地址偏移量:0x0420，初值:0x000000FF，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  white_level_l : 8;  /* bit[0-7] : Sets white level for iridix processing */
        unsigned int  reserved      : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_WHITE_LEVEL_L_UNION;
#endif
#define SOC_DSS_SBL_WHITE_LEVEL_L_white_level_l_START  (0)
#define SOC_DSS_SBL_WHITE_LEVEL_L_white_level_l_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_WHITE_LEVEL_H_UNION
 结构说明  : WHITE_LEVEL_H 寄存器结构定义。地址偏移量:0x0424，初值:0x00000003，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  white_level_h : 2;  /* bit[0-1] : Sets white level for iridix processing */
        unsigned int  reserved      : 30; /* bit[2-31]:  */
    } reg;
} SOC_DSS_SBL_WHITE_LEVEL_H_UNION;
#endif
#define SOC_DSS_SBL_WHITE_LEVEL_H_white_level_h_START  (0)
#define SOC_DSS_SBL_WHITE_LEVEL_H_white_level_h_END    (1)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_BRIGHT_DARK_AMP_LIMIT_UNION
 结构说明  : BRIGHT_DARK_AMP_LIMIT 寄存器结构定义。地址偏移量:0x0428，初值:0x000000F0，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dark_amp_limit   : 4;  /* bit[0-3] :  */
        unsigned int  bright_amp_limit : 4;  /* bit[4-7] :  */
        unsigned int  reserved         : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_BRIGHT_DARK_AMP_LIMIT_UNION;
#endif
#define SOC_DSS_SBL_BRIGHT_DARK_AMP_LIMIT_dark_amp_limit_START    (0)
#define SOC_DSS_SBL_BRIGHT_DARK_AMP_LIMIT_dark_amp_limit_END      (3)
#define SOC_DSS_SBL_BRIGHT_DARK_AMP_LIMIT_bright_amp_limit_START  (4)
#define SOC_DSS_SBL_BRIGHT_DARK_AMP_LIMIT_bright_amp_limit_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_DITHER_MODE_UNION
 结构说明  : DITHER_MODE 寄存器结构定义。地址偏移量:0x042C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dither_mode : 3;  /* bit[0-2] :  */
        unsigned int  reserved    : 29; /* bit[3-31]:  */
    } reg;
} SOC_DSS_SBL_DITHER_MODE_UNION;
#endif
#define SOC_DSS_SBL_DITHER_MODE_dither_mode_START  (0)
#define SOC_DSS_SBL_DITHER_MODE_dither_mode_END    (2)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_CONFIG_BUFFER_MODE_UNION
 结构说明  : CONFIG_BUFFER_MODE 寄存器结构定义。地址偏移量:0x0430，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  config_buffer_mode : 2;  /* bit[0-1] : double buffering control for video pipeline configuration parameters */
        unsigned int  reserved           : 30; /* bit[2-31]:  */
    } reg;
} SOC_DSS_SBL_CONFIG_BUFFER_MODE_UNION;
#endif
#define SOC_DSS_SBL_CONFIG_BUFFER_MODE_config_buffer_mode_START  (0)
#define SOC_DSS_SBL_CONFIG_BUFFER_MODE_config_buffer_mode_END    (1)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_CONFIG_BUFFER_GLOBAL_UNION
 结构说明  : CONFIG_BUFFER_GLOBAL 寄存器结构定义。地址偏移量:0x0434，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  config_buffer_global : 1;  /* bit[0]   : double buffering control for video pipeline configuration parameters */
        unsigned int  reserved             : 31; /* bit[1-31]:  */
    } reg;
} SOC_DSS_SBL_CONFIG_BUFFER_GLOBAL_UNION;
#endif
#define SOC_DSS_SBL_CONFIG_BUFFER_GLOBAL_config_buffer_global_START  (0)
#define SOC_DSS_SBL_CONFIG_BUFFER_GLOBAL_config_buffer_global_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_ASYMMETRY_LUT_ADDR_UNION
 结构说明  : ASYMMETRY_LUT_ADDR 寄存器结构定义。地址偏移量:0x0480，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  asymmetry_lut_addr : 6;  /* bit[0-5] : LUT address register (valid range 0 to 32) */
        unsigned int  reserved           : 26; /* bit[6-31]:  */
    } reg;
} SOC_DSS_SBL_ASYMMETRY_LUT_ADDR_UNION;
#endif
#define SOC_DSS_SBL_ASYMMETRY_LUT_ADDR_asymmetry_lut_addr_START  (0)
#define SOC_DSS_SBL_ASYMMETRY_LUT_ADDR_asymmetry_lut_addr_END    (5)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_ASYMMETRY_LUT_WRITE_DATA_L_UNION
 结构说明  : ASYMMETRY_LUT_WRITE_DATA_L 寄存器结构定义。地址偏移量:0x0484，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  asymmetry_lut_write_data_l : 8;  /* bit[0-7] : LUT write data register */
        unsigned int  reserved                   : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_ASYMMETRY_LUT_WRITE_DATA_L_UNION;
#endif
#define SOC_DSS_SBL_ASYMMETRY_LUT_WRITE_DATA_L_asymmetry_lut_write_data_l_START  (0)
#define SOC_DSS_SBL_ASYMMETRY_LUT_WRITE_DATA_L_asymmetry_lut_write_data_l_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_ASYMMETRY_LUT_WRITE_DATA_H_UNION
 结构说明  : ASYMMETRY_LUT_WRITE_DATA_H 寄存器结构定义。地址偏移量:0x0488，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  asymmetry_lut_write_data_h : 4;  /* bit[0-3] : LUT write data register 
                                                                       */
        unsigned int  reserved                   : 28; /* bit[4-31]:  */
    } reg;
} SOC_DSS_SBL_ASYMMETRY_LUT_WRITE_DATA_H_UNION;
#endif
#define SOC_DSS_SBL_ASYMMETRY_LUT_WRITE_DATA_H_asymmetry_lut_write_data_h_START  (0)
#define SOC_DSS_SBL_ASYMMETRY_LUT_WRITE_DATA_H_asymmetry_lut_write_data_h_END    (3)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_COLOR_CORRECTION_LUT_ADDR_UNION
 结构说明  : COLOR_CORRECTION_LUT_ADDR 寄存器结构定义。地址偏移量:0x04C0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  color_correction_lut_addr : 6;  /* bit[0-5] : LUT address register(valid range 0 to 32) */
        unsigned int  reserved                  : 26; /* bit[6-31]:  */
    } reg;
} SOC_DSS_SBL_COLOR_CORRECTION_LUT_ADDR_UNION;
#endif
#define SOC_DSS_SBL_COLOR_CORRECTION_LUT_ADDR_color_correction_lut_addr_START  (0)
#define SOC_DSS_SBL_COLOR_CORRECTION_LUT_ADDR_color_correction_lut_addr_END    (5)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_COLOR_CORRECTION_LUT_WRITE_DATA_L_UNION
 结构说明  : COLOR_CORRECTION_LUT_WRITE_DATA_L 寄存器结构定义。地址偏移量:0x04C4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  color_correction_lut_write_data_l : 8;  /* bit[0-7] : LUT write data register */
        unsigned int  reserved                          : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_COLOR_CORRECTION_LUT_WRITE_DATA_L_UNION;
#endif
#define SOC_DSS_SBL_COLOR_CORRECTION_LUT_WRITE_DATA_L_color_correction_lut_write_data_l_START  (0)
#define SOC_DSS_SBL_COLOR_CORRECTION_LUT_WRITE_DATA_L_color_correction_lut_write_data_l_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_COLOR_CORRECTION_LUT_WRITE_DATA_H_UNION
 结构说明  : COLOR_CORRECTION_LUT_WRITE_DATA_H 寄存器结构定义。地址偏移量:0x04C8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  color_correction_lut_write_data_h : 4;  /* bit[0-3] : LUT write data register 
                                                                             
                                                                              */
        unsigned int  reserved                          : 28; /* bit[4-31]:  */
    } reg;
} SOC_DSS_SBL_COLOR_CORRECTION_LUT_WRITE_DATA_H_UNION;
#endif
#define SOC_DSS_SBL_COLOR_CORRECTION_LUT_WRITE_DATA_H_color_correction_lut_write_data_h_START  (0)
#define SOC_DSS_SBL_COLOR_CORRECTION_LUT_WRITE_DATA_H_color_correction_lut_write_data_h_END    (3)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_LOGO_LEFT_UNION
 结构说明  : LOGO_LEFT 寄存器结构定义。地址偏移量:0x0800，初值:0x00000002，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  logo_left : 8;  /* bit[0-7] : Sets x ordinate of logo(in 16-pixel steps) */
        unsigned int  reserved  : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_LOGO_LEFT_UNION;
#endif
#define SOC_DSS_SBL_LOGO_LEFT_logo_left_START  (0)
#define SOC_DSS_SBL_LOGO_LEFT_logo_left_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_LOGO_TOP_UNION
 结构说明  : LOGO_TOP 寄存器结构定义。地址偏移量:0x0804，初值:0x00000002，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  logo_top : 8;  /* bit[0-7] : Sets y ordinate of logo(in 16-pixel steps) */
        unsigned int  reserved : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_LOGO_TOP_UNION;
#endif
#define SOC_DSS_SBL_LOGO_TOP_logo_top_START  (0)
#define SOC_DSS_SBL_LOGO_TOP_logo_top_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_APICAL_DITHER_UNION
 结构说明  : APICAL_DITHER 寄存器结构定义。地址偏移量:0x0840，初值:0x00000003，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  enable_dither : 1;  /* bit[0]   : Enable/Disable external dither module */
        unsigned int  shift_mode    : 1;  /* bit[1]   : 0=out is MSB aligned 1=out is LSB aligned */
        unsigned int  dither_amount : 2;  /* bit[2-3] : 0=dither 1 bit 1=dither 2 bits */
        unsigned int  reserved_0    : 3;  /* bit[4-6] :  */
        unsigned int  dither_bypass : 1;  /* bit[7]   : bypass dither module */
        unsigned int  reserved_1    : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_APICAL_DITHER_UNION;
#endif
#define SOC_DSS_SBL_APICAL_DITHER_enable_dither_START  (0)
#define SOC_DSS_SBL_APICAL_DITHER_enable_dither_END    (0)
#define SOC_DSS_SBL_APICAL_DITHER_shift_mode_START     (1)
#define SOC_DSS_SBL_APICAL_DITHER_shift_mode_END       (1)
#define SOC_DSS_SBL_APICAL_DITHER_dither_amount_START  (2)
#define SOC_DSS_SBL_APICAL_DITHER_dither_amount_END    (3)
#define SOC_DSS_SBL_APICAL_DITHER_dither_bypass_START  (7)
#define SOC_DSS_SBL_APICAL_DITHER_dither_bypass_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_AUTOMATIC_START_CALC_STRENGTH_DRC_BACKLIGHT_SEL_UNION
 结构说明  : AUTOMATIC_START_CALC_STRENGTH_DRC_BACKLIGHT_SEL 寄存器结构定义。地址偏移量:0x0C00，初值:0x00000080，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  backlight_sel        : 1;  /* bit[0]   : Enable/Disable Manual Backlight */
        unsigned int  drc_sel              : 1;  /* bit[1]   : Enable/Disable Manual drc */
        unsigned int  strength_sel         : 1;  /* bit[2]   : Enable/Disable Manual strength */
        unsigned int  reserved_0           : 4;  /* bit[3-6] :  */
        unsigned int  automatic_start_calc : 1;  /* bit[7]   : Enable/Disable auto trigger of start calc */
        unsigned int  reserved_1           : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_AUTOMATIC_START_CALC_STRENGTH_DRC_BACKLIGHT_SEL_UNION;
#endif
#define SOC_DSS_SBL_AUTOMATIC_START_CALC_STRENGTH_DRC_BACKLIGHT_SEL_backlight_sel_START         (0)
#define SOC_DSS_SBL_AUTOMATIC_START_CALC_STRENGTH_DRC_BACKLIGHT_SEL_backlight_sel_END           (0)
#define SOC_DSS_SBL_AUTOMATIC_START_CALC_STRENGTH_DRC_BACKLIGHT_SEL_drc_sel_START               (1)
#define SOC_DSS_SBL_AUTOMATIC_START_CALC_STRENGTH_DRC_BACKLIGHT_SEL_drc_sel_END                 (1)
#define SOC_DSS_SBL_AUTOMATIC_START_CALC_STRENGTH_DRC_BACKLIGHT_SEL_strength_sel_START          (2)
#define SOC_DSS_SBL_AUTOMATIC_START_CALC_STRENGTH_DRC_BACKLIGHT_SEL_strength_sel_END            (2)
#define SOC_DSS_SBL_AUTOMATIC_START_CALC_STRENGTH_DRC_BACKLIGHT_SEL_automatic_start_calc_START  (7)
#define SOC_DSS_SBL_AUTOMATIC_START_CALC_STRENGTH_DRC_BACKLIGHT_SEL_automatic_start_calc_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_STRENGTH_MANUAL_UNION
 结构说明  : STRENGTH_MANUAL 寄存器结构定义。地址偏移量:0x0C04，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  strength_manual : 8;  /* bit[0-7] : Manual override value of iridix module strength when option_select=9(dec) */
        unsigned int  reserved        : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_STRENGTH_MANUAL_UNION;
#endif
#define SOC_DSS_SBL_STRENGTH_MANUAL_strength_manual_START  (0)
#define SOC_DSS_SBL_STRENGTH_MANUAL_strength_manual_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_DRC_IN_L_UNION
 结构说明  : DRC_IN_L 寄存器结构定义。地址偏移量:0x0C08，初值:0x000000FF，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  drc_in_l : 8;  /* bit[0-7] :  */
        unsigned int  reserved : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_DRC_IN_L_UNION;
#endif
#define SOC_DSS_SBL_DRC_IN_L_drc_in_l_START  (0)
#define SOC_DSS_SBL_DRC_IN_L_drc_in_l_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_DRC_IN_H_UNION
 结构说明  : DRC_IN_H 寄存器结构定义。地址偏移量:0x0C0C，初值:0x000000FF，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  drc_in_h : 8;  /* bit[0-7] : target strength of dynamic range compression */
        unsigned int  reserved : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_DRC_IN_H_UNION;
#endif
#define SOC_DSS_SBL_DRC_IN_H_drc_in_h_START  (0)
#define SOC_DSS_SBL_DRC_IN_H_drc_in_h_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_BACKLIGHT_L_UNION
 结构说明  : BACKLIGHT_L 寄存器结构定义。地址偏移量:0x0C10，初值:0x000000FF，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  backlight_l : 8;  /* bit[0-7] :  */
        unsigned int  reserved    : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_BACKLIGHT_L_UNION;
#endif
#define SOC_DSS_SBL_BACKLIGHT_L_backlight_l_START  (0)
#define SOC_DSS_SBL_BACKLIGHT_L_backlight_l_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_BACKLIGHT_H_UNION
 结构说明  : BACKLIGHT_H 寄存器结构定义。地址偏移量:0x0C14，初值:0x000000FF，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  backlight_h : 8;  /* bit[0-7] : screen brightness on a scale of 0 to backlight_scale */
        unsigned int  reserved    : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_BACKLIGHT_H_UNION;
#endif
#define SOC_DSS_SBL_BACKLIGHT_H_backlight_h_START  (0)
#define SOC_DSS_SBL_BACKLIGHT_H_backlight_h_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_AMBIENT_LIGHT_L_UNION
 结构说明  : AMBIENT_LIGHT_L 寄存器结构定义。地址偏移量:0x0C18，初值:0x000000FF，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ambient_light_l : 8;  /* bit[0-7] :  */
        unsigned int  reserved        : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_AMBIENT_LIGHT_L_UNION;
#endif
#define SOC_DSS_SBL_AMBIENT_LIGHT_L_ambient_light_l_START  (0)
#define SOC_DSS_SBL_AMBIENT_LIGHT_L_ambient_light_l_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_AMBIENT_LIGHT_H_UNION
 结构说明  : AMBIENT_LIGHT_H 寄存器结构定义。地址偏移量:0x0C1C，初值:0x000000FF，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ambient_light_h : 8;  /* bit[0-7] : ambient light level from photosensor */
        unsigned int  reserved        : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_AMBIENT_LIGHT_H_UNION;
#endif
#define SOC_DSS_SBL_AMBIENT_LIGHT_H_ambient_light_h_START  (0)
#define SOC_DSS_SBL_AMBIENT_LIGHT_H_ambient_light_h_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_START_CALC_UNION
 结构说明  : START_CALC 寄存器结构定义。地址偏移量:0x0C20，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  start_calc : 1;  /* bit[0]   : start calculator pulse */
        unsigned int  reserved   : 31; /* bit[1-31]:  */
    } reg;
} SOC_DSS_SBL_START_CALC_UNION;
#endif
#define SOC_DSS_SBL_START_CALC_start_calc_START  (0)
#define SOC_DSS_SBL_START_CALC_start_calc_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_STRENGTH_LIMIT_UNION
 结构说明  : STRENGTH_LIMIT 寄存器结构定义。地址偏移量:0x0C24，初值:0x00000080，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  strength_limit : 8;  /* bit[0-7] : imposes a cap on maximum dynamic range compression strength */
        unsigned int  reserved       : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_STRENGTH_LIMIT_UNION;
#endif
#define SOC_DSS_SBL_STRENGTH_LIMIT_strength_limit_START  (0)
#define SOC_DSS_SBL_STRENGTH_LIMIT_strength_limit_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_CALIBRATION_A_L_UNION
 结构说明  : CALIBRATION_A_L 寄存器结构定义。地址偏移量:0x0C28，初值:0x0000006E，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  calibration_a_l : 8;  /* bit[0-7] :  */
        unsigned int  reserved        : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_CALIBRATION_A_L_UNION;
#endif
#define SOC_DSS_SBL_CALIBRATION_A_L_calibration_a_l_START  (0)
#define SOC_DSS_SBL_CALIBRATION_A_L_calibration_a_l_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_CALIBRATION_A_H_UNION
 结构说明  : CALIBRATION_A_H 寄存器结构定义。地址偏移量:0x0C2C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  calibration_a_h : 8;  /* bit[0-7] : screen calibration parameter */
        unsigned int  reserved        : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_CALIBRATION_A_H_UNION;
#endif
#define SOC_DSS_SBL_CALIBRATION_A_H_calibration_a_h_START  (0)
#define SOC_DSS_SBL_CALIBRATION_A_H_calibration_a_h_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_CALIBRATION_B_L_UNION
 结构说明  : CALIBRATION_B_L 寄存器结构定义。地址偏移量:0x0C30，初值:0x0000005F，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  calibration_b_l : 8;  /* bit[0-7] :  */
        unsigned int  reserved        : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_CALIBRATION_B_L_UNION;
#endif
#define SOC_DSS_SBL_CALIBRATION_B_L_calibration_b_l_START  (0)
#define SOC_DSS_SBL_CALIBRATION_B_L_calibration_b_l_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_CALIBRATION_B_H_UNION
 结构说明  : CALIBRATION_B_H 寄存器结构定义。地址偏移量:0x0C34，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  calibration_b_h : 8;  /* bit[0-7] : screen calibration parameter */
        unsigned int  reserved        : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_CALIBRATION_B_H_UNION;
#endif
#define SOC_DSS_SBL_CALIBRATION_B_H_calibration_b_h_START  (0)
#define SOC_DSS_SBL_CALIBRATION_B_H_calibration_b_h_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_CALIBRATION_C_L_UNION
 结构说明  : CALIBRATION_C_L 寄存器结构定义。地址偏移量:0x0C38，初值:0x00000013，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  calibration_c_l : 8;  /* bit[0-7] :  */
        unsigned int  reserved        : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_CALIBRATION_C_L_UNION;
#endif
#define SOC_DSS_SBL_CALIBRATION_C_L_calibration_c_l_START  (0)
#define SOC_DSS_SBL_CALIBRATION_C_L_calibration_c_l_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_CALIBRATION_C_H_UNION
 结构说明  : CALIBRATION_C_H 寄存器结构定义。地址偏移量:0x0C3C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  calibration_c_h : 8;  /* bit[0-7] : screen calibration parameter */
        unsigned int  reserved        : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_CALIBRATION_C_H_UNION;
#endif
#define SOC_DSS_SBL_CALIBRATION_C_H_calibration_c_h_START  (0)
#define SOC_DSS_SBL_CALIBRATION_C_H_calibration_c_h_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_CALIBRATION_D_L_UNION
 结构说明  : CALIBRATION_D_L 寄存器结构定义。地址偏移量:0x0C40，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  calibration_d_l : 8;  /* bit[0-7] :  */
        unsigned int  reserved        : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_CALIBRATION_D_L_UNION;
#endif
#define SOC_DSS_SBL_CALIBRATION_D_L_calibration_d_l_START  (0)
#define SOC_DSS_SBL_CALIBRATION_D_L_calibration_d_l_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_CALIBRATION_D_H_UNION
 结构说明  : CALIBRATION_D_H 寄存器结构定义。地址偏移量:0x0C44，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  calibration_d_h : 8;  /* bit[0-7] : screen calibration parameter */
        unsigned int  reserved        : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_CALIBRATION_D_H_UNION;
#endif
#define SOC_DSS_SBL_CALIBRATION_D_H_calibration_d_h_START  (0)
#define SOC_DSS_SBL_CALIBRATION_D_H_calibration_d_h_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_T_FILTER_CONTROL_UNION
 结构说明  : T_FILTER_CONTROL 寄存器结构定义。地址偏移量:0x0C48，初值:0x00000001，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  t_filter_control : 8;  /* bit[0-7] : Recursion depth of temporal filter */
        unsigned int  reserved         : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_T_FILTER_CONTROL_UNION;
#endif
#define SOC_DSS_SBL_T_FILTER_CONTROL_t_filter_control_START  (0)
#define SOC_DSS_SBL_T_FILTER_CONTROL_t_filter_control_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_BACKLIGHT_MIN_L_UNION
 结构说明  : BACKLIGHT_MIN_L 寄存器结构定义。地址偏移量:0x0C4C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  backlight_min_l : 8;  /* bit[0-7] :  */
        unsigned int  reserved        : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_BACKLIGHT_MIN_L_UNION;
#endif
#define SOC_DSS_SBL_BACKLIGHT_MIN_L_backlight_min_l_START  (0)
#define SOC_DSS_SBL_BACKLIGHT_MIN_L_backlight_min_l_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_BACKLIGHT_MIN_H_UNION
 结构说明  : BACKLIGHT_MIN_H 寄存器结构定义。地址偏移量:0x0C50，初值:0x00000028，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  backlight_min_h : 8;  /* bit[0-7] : minimum output backlight value permitted */
        unsigned int  reserved        : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_BACKLIGHT_MIN_H_UNION;
#endif
#define SOC_DSS_SBL_BACKLIGHT_MIN_H_backlight_min_h_START  (0)
#define SOC_DSS_SBL_BACKLIGHT_MIN_H_backlight_min_h_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_BACKLIGHT_MAX_L_UNION
 结构说明  : BACKLIGHT_MAX_L 寄存器结构定义。地址偏移量:0x0C54，初值:0x000000FF，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  backlight_max_l : 8;  /* bit[0-7] :  */
        unsigned int  reserved        : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_BACKLIGHT_MAX_L_UNION;
#endif
#define SOC_DSS_SBL_BACKLIGHT_MAX_L_backlight_max_l_START  (0)
#define SOC_DSS_SBL_BACKLIGHT_MAX_L_backlight_max_l_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_BACKLIGHT_MAX_H_UNION
 结构说明  : BACKLIGHT_MAX_H 寄存器结构定义。地址偏移量:0x0C58，初值:0x000000FF，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  backlight_max_h : 8;  /* bit[0-7] : maximum output backlight value permitted */
        unsigned int  reserved        : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_BACKLIGHT_MAX_H_UNION;
#endif
#define SOC_DSS_SBL_BACKLIGHT_MAX_H_backlight_max_h_START  (0)
#define SOC_DSS_SBL_BACKLIGHT_MAX_H_backlight_max_h_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_BACKLIGHT_SCALE_L_UNION
 结构说明  : BACKLIGHT_SCALE_L 寄存器结构定义。地址偏移量:0x0C5C，初值:0x000000FF，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  backlight_scale_l : 8;  /* bit[0-7] :  */
        unsigned int  reserved          : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_BACKLIGHT_SCALE_L_UNION;
#endif
#define SOC_DSS_SBL_BACKLIGHT_SCALE_L_backlight_scale_l_START  (0)
#define SOC_DSS_SBL_BACKLIGHT_SCALE_L_backlight_scale_l_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_BACKLIGHT_SCALE_H_UNION
 结构说明  : BACKLIGHT_SCALE_H 寄存器结构定义。地址偏移量:0x0C60，初值:0x000000FF，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  backlight_scale_h : 8;  /* bit[0-7] : digital value corresponding to the maximum possible backlight input level */
        unsigned int  reserved          : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_BACKLIGHT_SCALE_H_UNION;
#endif
#define SOC_DSS_SBL_BACKLIGHT_SCALE_H_backlight_scale_h_START  (0)
#define SOC_DSS_SBL_BACKLIGHT_SCALE_H_backlight_scale_h_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_AMBIENT_LIGHT_MIN_L_UNION
 结构说明  : AMBIENT_LIGHT_MIN_L 寄存器结构定义。地址偏移量:0x0C64，初值:0x0000000E，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ambient_light_min_l : 8;  /* bit[0-7] :  */
        unsigned int  reserved            : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_AMBIENT_LIGHT_MIN_L_UNION;
#endif
#define SOC_DSS_SBL_AMBIENT_LIGHT_MIN_L_ambient_light_min_l_START  (0)
#define SOC_DSS_SBL_AMBIENT_LIGHT_MIN_L_ambient_light_min_l_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_AMBIENT_LIGHT_MIN_H_UNION
 结构说明  : AMBIENT_LIGHT_MIN_H 寄存器结构定义。地址偏移量:0x0C68，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ambient_light_min_h : 8;  /* bit[0-7] : ambient light level below which backlight_out is set to backlight_min */
        unsigned int  reserved            : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_AMBIENT_LIGHT_MIN_H_UNION;
#endif
#define SOC_DSS_SBL_AMBIENT_LIGHT_MIN_H_ambient_light_min_h_START  (0)
#define SOC_DSS_SBL_AMBIENT_LIGHT_MIN_H_ambient_light_min_h_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_FILTER_A_L_UNION
 结构说明  : FILTER_A_L 寄存器结构定义。地址偏移量:0x0C6C，初值:0x000000CA，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  filter_a_l : 8;  /* bit[0-7] :  */
        unsigned int  reserved   : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_FILTER_A_L_UNION;
#endif
#define SOC_DSS_SBL_FILTER_A_L_filter_a_l_START  (0)
#define SOC_DSS_SBL_FILTER_A_L_filter_a_l_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_FILTER_A_H_UNION
 结构说明  : FILTER_A_H 寄存器结构定义。地址偏移量:0x0C70，初值:0x00000006，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  filter_a_h : 8;  /* bit[0-7] : filter values for the input ambient_light */
        unsigned int  reserved   : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_FILTER_A_H_UNION;
#endif
#define SOC_DSS_SBL_FILTER_A_H_filter_a_h_START  (0)
#define SOC_DSS_SBL_FILTER_A_H_filter_a_h_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_FILTER_B_UNION
 结构说明  : FILTER_B 寄存器结构定义。地址偏移量:0x0C74，初值:0x00000006，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  filter_b : 8;  /* bit[0-7] : filter values for the input ambient_light */
        unsigned int  reserved : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_FILTER_B_UNION;
#endif
#define SOC_DSS_SBL_FILTER_B_filter_b_START  (0)
#define SOC_DSS_SBL_FILTER_B_filter_b_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_STRENGTH_OUT_UNION
 结构说明  : STRENGTH_OUT 寄存器结构定义。地址偏移量:0x0C80，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  strength_out : 8;  /* bit[0-7] : The primary output of the calculator, passed to the internal iridix module strength register. This is included as an output from the core for debug purposes only */
        unsigned int  reserved     : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_STRENGTH_OUT_UNION;
#endif
#define SOC_DSS_SBL_STRENGTH_OUT_strength_out_START  (0)
#define SOC_DSS_SBL_STRENGTH_OUT_strength_out_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_DRC_OUT_L_UNION
 结构说明  : DRC_OUT_L 寄存器结构定义。地址偏移量:0x0C84，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  drc_out_l : 8;  /* bit[0-7] :  */
        unsigned int  reserved  : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_DRC_OUT_L_UNION;
#endif
#define SOC_DSS_SBL_DRC_OUT_L_drc_out_l_START  (0)
#define SOC_DSS_SBL_DRC_OUT_L_drc_out_l_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_DRC_OUT_H_UNION
 结构说明  : DRC_OUT_H 寄存器结构定义。地址偏移量:0x0C88，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  drc_out_h : 8;  /* bit[0-7] : calculated dynamic range compression */
        unsigned int  reserved  : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_DRC_OUT_H_UNION;
#endif
#define SOC_DSS_SBL_DRC_OUT_H_drc_out_h_START  (0)
#define SOC_DSS_SBL_DRC_OUT_H_drc_out_h_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_BACKLIGHT_OUT_L_UNION
 结构说明  : BACKLIGHT_OUT_L 寄存器结构定义。地址偏移量:0x0C8C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  backlight_out_l : 8;  /* bit[0-7] :  */
        unsigned int  reserved        : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_BACKLIGHT_OUT_L_UNION;
#endif
#define SOC_DSS_SBL_BACKLIGHT_OUT_L_backlight_out_l_START  (0)
#define SOC_DSS_SBL_BACKLIGHT_OUT_L_backlight_out_l_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_BACKLIGHT_OUT_H_UNION
 结构说明  : BACKLIGHT_OUT_H 寄存器结构定义。地址偏移量:0x0C90，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  backlight_out_h : 8;  /* bit[0-7] : calculated backlight setting */
        unsigned int  reserved        : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_BACKLIGHT_OUT_H_UNION;
#endif
#define SOC_DSS_SBL_BACKLIGHT_OUT_H_backlight_out_h_START  (0)
#define SOC_DSS_SBL_BACKLIGHT_OUT_H_backlight_out_h_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_CALC_DONE_UNION
 结构说明  : CALC_DONE 寄存器结构定义。地址偏移量:0x0C94，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  calc_done : 1;  /* bit[0]   : calculation done flag */
        unsigned int  reserved  : 31; /* bit[1-31]:  */
    } reg;
} SOC_DSS_SBL_CALC_DONE_UNION;
#endif
#define SOC_DSS_SBL_CALC_DONE_calc_done_START  (0)
#define SOC_DSS_SBL_CALC_DONE_calc_done_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_AL_CALIB_LUT_LUT_ADDR_UNION
 结构说明  : AL_CALIB_LUT_LUT_ADDR 寄存器结构定义。地址偏移量:0x0F00，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  al_calib_lut_lut_addr : 6;  /* bit[0-5] : LUT address register(valid range 0 to 32) */
        unsigned int  reserved              : 26; /* bit[6-31]:  */
    } reg;
} SOC_DSS_SBL_AL_CALIB_LUT_LUT_ADDR_UNION;
#endif
#define SOC_DSS_SBL_AL_CALIB_LUT_LUT_ADDR_al_calib_lut_lut_addr_START  (0)
#define SOC_DSS_SBL_AL_CALIB_LUT_LUT_ADDR_al_calib_lut_lut_addr_END    (5)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_AL_CALIB_LUT_LUT_WRITE_DATA_L_UNION
 结构说明  : AL_CALIB_LUT_LUT_WRITE_DATA_L 寄存器结构定义。地址偏移量:0x0F10，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  al_calib_lut_lut_write_data_l : 8;  /* bit[0-7] :  */
        unsigned int  reserved                      : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_AL_CALIB_LUT_LUT_WRITE_DATA_L_UNION;
#endif
#define SOC_DSS_SBL_AL_CALIB_LUT_LUT_WRITE_DATA_L_al_calib_lut_lut_write_data_l_START  (0)
#define SOC_DSS_SBL_AL_CALIB_LUT_LUT_WRITE_DATA_L_al_calib_lut_lut_write_data_l_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_SBL_AL_CALIB_LUT_LUT_WRITE_DATA_H_UNION
 结构说明  : AL_CALIB_LUT_LUT_WRITE_DATA_H 寄存器结构定义。地址偏移量:0x0F14，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  al_calib_lut_lut_write_data_h : 8;  /* bit[0-7] : LUT write data register */
        unsigned int  reserved                      : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_SBL_AL_CALIB_LUT_LUT_WRITE_DATA_H_UNION;
#endif
#define SOC_DSS_SBL_AL_CALIB_LUT_LUT_WRITE_DATA_H_al_calib_lut_lut_write_data_h_START  (0)
#define SOC_DSS_SBL_AL_CALIB_LUT_LUT_WRITE_DATA_H_al_calib_lut_lut_write_data_h_END    (7)






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

#endif /* end of soc_dss_sbl_interface.h */
