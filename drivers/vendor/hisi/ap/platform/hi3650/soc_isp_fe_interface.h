/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_isp_fe_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:21:41
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_ISP_FE.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_ISP_FE_INTERFACE_H__
#define __SOC_ISP_FE_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) ISP_FE
 ****************************************************************************/
/* 寄存器说明：Functional clock enable for FE
   位域定义UNION结构:  SOC_ISP_FE_FCLK_EN_FE_UNION */
#define SOC_ISP_FE_FCLK_EN_FE_ADDR(base)              ((base) + (0x0))

/* 寄存器说明：Pipe configuration control
   位域定义UNION结构:  SOC_ISP_FE_CONTROL_UNION */
#define SOC_ISP_FE_CONTROL_ADDR(base)                 ((base) + (0x0010))

/* 寄存器说明：Crop horizontal offsets
   位域定义UNION结构:  SOC_ISP_FE_CROP_H_1_UNION */
#define SOC_ISP_FE_CROP_H_1_ADDR(base)                ((base) + (0x0020))

/* 寄存器说明：Crop vertical offsets
   位域定义UNION结构:  SOC_ISP_FE_CROP_V_1_UNION */
#define SOC_ISP_FE_CROP_V_1_ADDR(base)                ((base) + (0x0024))

/* 寄存器说明：Crop horizontal offset
   位域定义UNION结构:  SOC_ISP_FE_ACQ_H_OFFSET_UNION */
#define SOC_ISP_FE_ACQ_H_OFFSET_ADDR(base)            ((base) + (0x0030))

/* 寄存器说明：Crop horizontal offset
   位域定义UNION结构:  SOC_ISP_FE_ACQ_V_OFFSET_UNION */
#define SOC_ISP_FE_ACQ_V_OFFSET_ADDR(base)            ((base) + (0x0034))

/* 寄存器说明：Crop horizontal size
   位域定义UNION结构:  SOC_ISP_FE_ACQ_H_SIZE_UNION */
#define SOC_ISP_FE_ACQ_H_SIZE_ADDR(base)              ((base) + (0x0038))

/* 寄存器说明：Crop horizontal  size
   位域定义UNION结构:  SOC_ISP_FE_ACQ_V_SIZE_UNION */
#define SOC_ISP_FE_ACQ_V_SIZE_ADDR(base)              ((base) + (0x003C))

/* 寄存器说明：Crop horizontal offset
   位域定义UNION结构:  SOC_ISP_FE_OUT_H_OFFSET_UNION */
#define SOC_ISP_FE_OUT_H_OFFSET_ADDR(base)            ((base) + (0x0040))

/* 寄存器说明：Crop horizontal offset
   位域定义UNION结构:  SOC_ISP_FE_OUT_V_OFFSET_UNION */
#define SOC_ISP_FE_OUT_V_OFFSET_ADDR(base)            ((base) + (0x0044))

/* 寄存器说明：Crop horizontal size
   位域定义UNION结构:  SOC_ISP_FE_OUT_H_SIZE_UNION */
#define SOC_ISP_FE_OUT_H_SIZE_ADDR(base)              ((base) + (0x0048))

/* 寄存器说明：Crop horizontal  size
   位域定义UNION结构:  SOC_ISP_FE_OUT_V_SIZE_UNION */
#define SOC_ISP_FE_OUT_V_SIZE_ADDR(base)              ((base) + (0x004C))

/* 寄存器说明：used to force the clock which is generally controlled by HW
   位域定义UNION结构:  SOC_ISP_FE_FORCE_CLK_ON_CFG_UNION */
#define SOC_ISP_FE_FORCE_CLK_ON_CFG_ADDR(base)        ((base) + (0x0050))





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
                     (1/1) ISP_FE
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_ISP_FE_FCLK_EN_FE_UNION
 结构说明  : FCLK_EN_FE 寄存器结构定义。地址偏移量:0x0，初值:0x0000FFFF，宽度:32
 寄存器说明: Functional clock enable for FE
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fclk_en_fe : 16; /* bit[0-15] : The register allow to reduce the functional clock by gating 1 to 16 clock pulse out of 16 clock pulse with a given pattern (shifter register) to allow reducing average throughput, hence power consumption by gating the functional function partially. enable is active high.
                                                      0x0000 Clock is fully gated
                                                      0xFFFF No Clk gating
                                                      Any bit pattern in between is gating corresponding fucntional clock pulse but refers table in top level specication for specific frequency programming */
        unsigned int  reserved   : 16; /* bit[16-31]: Reserved */
    } reg;
} SOC_ISP_FE_FCLK_EN_FE_UNION;
#endif
#define SOC_ISP_FE_FCLK_EN_FE_fclk_en_fe_START  (0)
#define SOC_ISP_FE_FCLK_EN_FE_fclk_en_fe_END    (15)


/*****************************************************************************
 结构名    : SOC_ISP_FE_CONTROL_UNION
 结构说明  : CONTROL 寄存器结构定义。地址偏移量:0x0010，初值:0x00000000，宽度:32
 寄存器说明: Pipe configuration control
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  isp_fe_memout : 1;  /* bit[0]   : Select if the stream comes from the Bayer Scaler BAS_(x) or from the RAWNF_(x). Used to drive the SELECT input of VPM2TO1_31_(x)
                                                        0 -> From BAS_(x)
                                                        1 -> From RAWNF_(x) */
        unsigned int  reserved_0    : 2;  /* bit[1-2] : Reserved for extra VP mux related to ISP_FE */
        unsigned int  bayer_pat_fe  : 2;  /* bit[3-4] : Color components from sensor, starting with top left position in sampled frame 
                                                         00- first line: RGRG..., second line: GBGB..., etc.
                                                         01- first line: GRGR..., second line: BGBG..., etc. 
                                                         10- first line: GBGB..., second line: RGRG..., etc. 
                                                         11- first line: BGBG..., second line: GRGR..., etc. 
                                                        This configuration applies for the black level area after cropping by the input formatter and all modules up to the BAS.
                                                        SHALL BE SHADOWED INSIDE EACH SUB-MODULES */
        unsigned int  ir_position   : 1;  /* bit[5]   : IR pixel is provided by the sensor in place of the green red GR pixel or green blue pixel GB
                                                        0: IR is in place of the GR
                                                        1: IR is in place of the GB */
        unsigned int  sensor_ir     : 1;  /* bit[6]   : Sensor bayer pattern has a IR channel in place of one of the green GR or GB
                                                        0: No IR channel
                                                        1: One IR channel  */
        unsigned int  reserved_1    : 25; /* bit[7-31]: Reserved */
    } reg;
} SOC_ISP_FE_CONTROL_UNION;
#endif
#define SOC_ISP_FE_CONTROL_isp_fe_memout_START  (0)
#define SOC_ISP_FE_CONTROL_isp_fe_memout_END    (0)
#define SOC_ISP_FE_CONTROL_bayer_pat_fe_START   (3)
#define SOC_ISP_FE_CONTROL_bayer_pat_fe_END     (4)
#define SOC_ISP_FE_CONTROL_ir_position_START    (5)
#define SOC_ISP_FE_CONTROL_ir_position_END      (5)
#define SOC_ISP_FE_CONTROL_sensor_ir_START      (6)
#define SOC_ISP_FE_CONTROL_sensor_ir_END        (6)


/*****************************************************************************
 结构名    : SOC_ISP_FE_CROP_H_1_UNION
 结构说明  : CROP_H_1 寄存器结构定义。地址偏移量:0x0020，初值:0x00000000，宽度:32
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
} SOC_ISP_FE_CROP_H_1_UNION;
#endif
#define SOC_ISP_FE_CROP_H_1_ihleft_START    (0)
#define SOC_ISP_FE_CROP_H_1_ihleft_END      (12)
#define SOC_ISP_FE_CROP_H_1_ihright_START   (16)
#define SOC_ISP_FE_CROP_H_1_ihright_END     (28)


/*****************************************************************************
 结构名    : SOC_ISP_FE_CROP_V_1_UNION
 结构说明  : CROP_V_1 寄存器结构定义。地址偏移量:0x0024，初值:0x00000000，宽度:32
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
} SOC_ISP_FE_CROP_V_1_UNION;
#endif
#define SOC_ISP_FE_CROP_V_1_ivtop_START     (0)
#define SOC_ISP_FE_CROP_V_1_ivtop_END       (12)
#define SOC_ISP_FE_CROP_V_1_ivbottom_START  (16)
#define SOC_ISP_FE_CROP_V_1_ivbottom_END    (28)


/*****************************************************************************
 结构名    : SOC_ISP_FE_ACQ_H_OFFSET_UNION
 结构说明  : ACQ_H_OFFSET 寄存器结构定义。地址偏移量:0x0030，初值:0x00000000，宽度:32
 寄存器说明: Crop horizontal offset
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  acq_h_offset : 13; /* bit[0-12] : Indicate position of first pixel on the left for the acquisition window, 0 means no left crop.
                                                        SHALL BE SHADOWED INSIDE THE SUB_MODULE inform.v */
        unsigned int  reserved     : 19; /* bit[13-31]: Reserved */
    } reg;
} SOC_ISP_FE_ACQ_H_OFFSET_UNION;
#endif
#define SOC_ISP_FE_ACQ_H_OFFSET_acq_h_offset_START  (0)
#define SOC_ISP_FE_ACQ_H_OFFSET_acq_h_offset_END    (12)


/*****************************************************************************
 结构名    : SOC_ISP_FE_ACQ_V_OFFSET_UNION
 结构说明  : ACQ_V_OFFSET 寄存器结构定义。地址偏移量:0x0034，初值:0x00000000，宽度:32
 寄存器说明: Crop horizontal offset
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  acq_v_offset : 13; /* bit[0-12] : Indicates position of first line on the top for the acquisition window,, 0 means no top crop
                                                        SHALL BE SHADOWED INSIDE THE SUB_MODULE inform.v */
        unsigned int  reserved     : 19; /* bit[13-31]: Reserved */
    } reg;
} SOC_ISP_FE_ACQ_V_OFFSET_UNION;
#endif
#define SOC_ISP_FE_ACQ_V_OFFSET_acq_v_offset_START  (0)
#define SOC_ISP_FE_ACQ_V_OFFSET_acq_v_offset_END    (12)


/*****************************************************************************
 结构名    : SOC_ISP_FE_ACQ_H_SIZE_UNION
 结构说明  : ACQ_H_SIZE 寄存器结构定义。地址偏移量:0x0038，初值:0x00000000，宽度:32
 寄存器说明: Crop horizontal size
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  acq_h_size : 13; /* bit[0-12] : Indicates the number of horizontal samples minus 1 of the acquisition window (one = 2 samples = 2 raw pixels)
                                                      SHALL BE SHADOWED INSIDE THE SUB_MODULE inform.v */
        unsigned int  reserved   : 19; /* bit[13-31]: Reserved */
    } reg;
} SOC_ISP_FE_ACQ_H_SIZE_UNION;
#endif
#define SOC_ISP_FE_ACQ_H_SIZE_acq_h_size_START  (0)
#define SOC_ISP_FE_ACQ_H_SIZE_acq_h_size_END    (12)


/*****************************************************************************
 结构名    : SOC_ISP_FE_ACQ_V_SIZE_UNION
 结构说明  : ACQ_V_SIZE 寄存器结构定义。地址偏移量:0x003C，初值:0x00000000，宽度:32
 寄存器说明: Crop horizontal  size
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  acq_v_size : 13; /* bit[0-12] : Indicates the number of vertical samples minus 1 of the acquisition window (one = 2 samples = 2 raw pixels)
                                                      SHALL BE SHADOWED INSIDE THE SUB_MODULE inform.v */
        unsigned int  reserved   : 19; /* bit[13-31]: Reserved */
    } reg;
} SOC_ISP_FE_ACQ_V_SIZE_UNION;
#endif
#define SOC_ISP_FE_ACQ_V_SIZE_acq_v_size_START  (0)
#define SOC_ISP_FE_ACQ_V_SIZE_acq_v_size_END    (12)


/*****************************************************************************
 结构名    : SOC_ISP_FE_OUT_H_OFFSET_UNION
 结构说明  : OUT_H_OFFSET 寄存器结构定义。地址偏移量:0x0040，初值:0x00000000，宽度:32
 寄存器说明: Crop horizontal offset
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  out_h_offset : 13; /* bit[0-12] : Indicate position of first pixel on the left for the acquisition window, 0 means no left crop. 
                                                        SHALL BE SHADOWED INSIDE THE SUB_MODULE outform.v */
        unsigned int  reserved     : 19; /* bit[13-31]: Reserved */
    } reg;
} SOC_ISP_FE_OUT_H_OFFSET_UNION;
#endif
#define SOC_ISP_FE_OUT_H_OFFSET_out_h_offset_START  (0)
#define SOC_ISP_FE_OUT_H_OFFSET_out_h_offset_END    (12)


/*****************************************************************************
 结构名    : SOC_ISP_FE_OUT_V_OFFSET_UNION
 结构说明  : OUT_V_OFFSET 寄存器结构定义。地址偏移量:0x0044，初值:0x00000000，宽度:32
 寄存器说明: Crop horizontal offset
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  out_v_offset : 13; /* bit[0-12] : Indicates position of first line on the top for the acquisition window,, 0 means no top crop
                                                        SHALL BE SHADOWED INSIDE THE SUB_MODULE outform.v */
        unsigned int  reserved     : 19; /* bit[13-31]: Reserved */
    } reg;
} SOC_ISP_FE_OUT_V_OFFSET_UNION;
#endif
#define SOC_ISP_FE_OUT_V_OFFSET_out_v_offset_START  (0)
#define SOC_ISP_FE_OUT_V_OFFSET_out_v_offset_END    (12)


/*****************************************************************************
 结构名    : SOC_ISP_FE_OUT_H_SIZE_UNION
 结构说明  : OUT_H_SIZE 寄存器结构定义。地址偏移量:0x0048，初值:0x00000000，宽度:32
 寄存器说明: Crop horizontal size
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  out_h_size : 13; /* bit[0-12] : Indicates the number of horizontal minus 1 samples of the acquisition window (one = 2 samples = 2 raw pixels)
                                                      SHALL BE SHADOWED INSIDE THE SUB_MODULE outform.v */
        unsigned int  reserved   : 19; /* bit[13-31]: Reserved */
    } reg;
} SOC_ISP_FE_OUT_H_SIZE_UNION;
#endif
#define SOC_ISP_FE_OUT_H_SIZE_out_h_size_START  (0)
#define SOC_ISP_FE_OUT_H_SIZE_out_h_size_END    (12)


/*****************************************************************************
 结构名    : SOC_ISP_FE_OUT_V_SIZE_UNION
 结构说明  : OUT_V_SIZE 寄存器结构定义。地址偏移量:0x004C，初值:0x00000000，宽度:32
 寄存器说明: Crop horizontal  size
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  out_v_size : 13; /* bit[0-12] : Indicates the number of vertical samples minus 1 of the acquisition window (one = 2 sample = 2 raw pixels)
                                                      SHALL BE SHADOWED INSIDE THE SUB_MODULE outform.v */
        unsigned int  reserved   : 19; /* bit[13-31]: Reserved */
    } reg;
} SOC_ISP_FE_OUT_V_SIZE_UNION;
#endif
#define SOC_ISP_FE_OUT_V_SIZE_out_v_size_START  (0)
#define SOC_ISP_FE_OUT_V_SIZE_out_v_size_END    (12)


/*****************************************************************************
 结构名    : SOC_ISP_FE_FORCE_CLK_ON_CFG_UNION
 结构说明  : FORCE_CLK_ON_CFG 寄存器结构定义。地址偏移量:0x0050，初值:0x000001FF，宽度:32
 寄存器说明: used to force the clock which is generally controlled by HW
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  force_clk_on_0 : 1;  /* bit[0]   : BLC_(x) clock is controlled by idle_detector by default. If set to '1', this will force the clock ON */
        unsigned int  force_clk_on_1 : 1;  /* bit[1]   : DGAMMA_(x) clock is controlled by idle_detector by default. If set to '1', this will force the clock ON */
        unsigned int  force_clk_on_2 : 1;  /* bit[2]   : LSC_(x) clock is controlled by idle_detector by default. If set to '1', this will force the clock ON */
        unsigned int  force_clk_on_3 : 1;  /* bit[3]   : DPCC_(x) clock is controlled by idle_detector by default. If set to '1', this will force the clock ON */
        unsigned int  force_clk_on_4 : 1;  /* bit[4]   : STAT3A_(x) clock is controlled by idle_detector by default. If set to '1', this will force the clock ON */
        unsigned int  force_clk_on_5 : 1;  /* bit[5]   : STATDIS_(x) clock is controlled by idle_detector by default. If set to '1', this will force the clock ON */
        unsigned int  force_clk_on_6 : 1;  /* bit[6]   : RAWNF_(x) clock is controlled by idle_detector by default. If set to '1', this will force the clock ON */
        unsigned int  force_clk_on_7 : 1;  /* bit[7]   : BAS_(x) clock is controlled by idle_detector by default. If set to '1', this will force the clock ON */
        unsigned int  force_clk_on_8 : 1;  /* bit[8]   : FE top logic clock is controlled by idle_detector by default. If set to '1', this will force the clock ON (clock also used by idle_detector)  */
        unsigned int  reserved       : 23; /* bit[9-31]: Reserved */
    } reg;
} SOC_ISP_FE_FORCE_CLK_ON_CFG_UNION;
#endif
#define SOC_ISP_FE_FORCE_CLK_ON_CFG_force_clk_on_0_START  (0)
#define SOC_ISP_FE_FORCE_CLK_ON_CFG_force_clk_on_0_END    (0)
#define SOC_ISP_FE_FORCE_CLK_ON_CFG_force_clk_on_1_START  (1)
#define SOC_ISP_FE_FORCE_CLK_ON_CFG_force_clk_on_1_END    (1)
#define SOC_ISP_FE_FORCE_CLK_ON_CFG_force_clk_on_2_START  (2)
#define SOC_ISP_FE_FORCE_CLK_ON_CFG_force_clk_on_2_END    (2)
#define SOC_ISP_FE_FORCE_CLK_ON_CFG_force_clk_on_3_START  (3)
#define SOC_ISP_FE_FORCE_CLK_ON_CFG_force_clk_on_3_END    (3)
#define SOC_ISP_FE_FORCE_CLK_ON_CFG_force_clk_on_4_START  (4)
#define SOC_ISP_FE_FORCE_CLK_ON_CFG_force_clk_on_4_END    (4)
#define SOC_ISP_FE_FORCE_CLK_ON_CFG_force_clk_on_5_START  (5)
#define SOC_ISP_FE_FORCE_CLK_ON_CFG_force_clk_on_5_END    (5)
#define SOC_ISP_FE_FORCE_CLK_ON_CFG_force_clk_on_6_START  (6)
#define SOC_ISP_FE_FORCE_CLK_ON_CFG_force_clk_on_6_END    (6)
#define SOC_ISP_FE_FORCE_CLK_ON_CFG_force_clk_on_7_START  (7)
#define SOC_ISP_FE_FORCE_CLK_ON_CFG_force_clk_on_7_END    (7)
#define SOC_ISP_FE_FORCE_CLK_ON_CFG_force_clk_on_8_START  (8)
#define SOC_ISP_FE_FORCE_CLK_ON_CFG_force_clk_on_8_END    (8)






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

#endif /* end of soc_isp_fe_interface.h */
