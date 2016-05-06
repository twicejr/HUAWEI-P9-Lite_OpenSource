/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_dss_dsc_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:20:03
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_DSS_DSC.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_DSS_DSC_INTERFACE_H__
#define __SOC_DSS_DSC_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) reg_DSC
 ****************************************************************************/
/* 寄存器说明：版本寄存器
   位域定义UNION结构:  SOC_DSS_DSC_VERSION_UNION */
#define SOC_DSS_DSC_VERSION_ADDR(base)                ((base) + (0x0000))

/* 寄存器说明：PPS标志寄存器
   位域定义UNION结构:  SOC_DSS_DSC_PPS_IDENTIFIER_UNION */
#define SOC_DSS_DSC_PPS_IDENTIFIER_ADDR(base)         ((base) + (0x0004))

/* 寄存器说明：使能寄存器
   位域定义UNION结构:  SOC_DSS_DSC_DSC_EN_UNION */
#define SOC_DSS_DSC_DSC_EN_ADDR(base)                 ((base) + (0x0008))

/* 寄存器说明：控制寄存器
   位域定义UNION结构:  SOC_DSS_DSC_DSC_CTRL_UNION */
#define SOC_DSS_DSC_DSC_CTRL_ADDR(base)               ((base) + (0x000C))

/* 寄存器说明：输入图像尺寸寄存器
   位域定义UNION结构:  SOC_DSS_DSC_PIC_SIZE_UNION */
#define SOC_DSS_DSC_PIC_SIZE_ADDR(base)               ((base) + (0x0010))

/* 寄存器说明：SLICE尺寸寄存器
   位域定义UNION结构:  SOC_DSS_DSC_SLICE_SIZE_UNION */
#define SOC_DSS_DSC_SLICE_SIZE_ADDR(base)             ((base) + (0x0014))

/* 寄存器说明：chunk尺寸寄存器
   位域定义UNION结构:  SOC_DSS_DSC_CHUNK_SIZE_UNION */
#define SOC_DSS_DSC_CHUNK_SIZE_ADDR(base)             ((base) + (0x0018))

/* 寄存器说明：RC model延时寄存器
   位域定义UNION结构:  SOC_DSS_DSC_INITIAL_DELAY_UNION */
#define SOC_DSS_DSC_INITIAL_DELAY_ADDR(base)          ((base) + (0x001C))

/* 寄存器说明：RC参数寄存器0
   位域定义UNION结构:  SOC_DSS_DSC_RC_PARAM0_UNION */
#define SOC_DSS_DSC_RC_PARAM0_ADDR(base)              ((base) + (0x0020))

/* 寄存器说明：RC参数寄存器1
   位域定义UNION结构:  SOC_DSS_DSC_RC_PARAM1_UNION */
#define SOC_DSS_DSC_RC_PARAM1_ADDR(base)              ((base) + (0x0024))

/* 寄存器说明：RC参数寄存器2
   位域定义UNION结构:  SOC_DSS_DSC_RC_PARAM2_UNION */
#define SOC_DSS_DSC_RC_PARAM2_ADDR(base)              ((base) + (0x0028))

/* 寄存器说明：RC参数寄存器3
   位域定义UNION结构:  SOC_DSS_DSC_RC_PARAM3_UNION */
#define SOC_DSS_DSC_RC_PARAM3_ADDR(base)              ((base) + (0x002C))

/* 寄存器说明：flatness QP阈值寄存器
   位域定义UNION结构:  SOC_DSS_DSC_FLATNESS_QP_TH_UNION */
#define SOC_DSS_DSC_FLATNESS_QP_TH_ADDR(base)         ((base) + (0x0030))

/* 寄存器说明：RC参数寄存器4
   位域定义UNION结构:  SOC_DSS_DSC_RC_PARAM4_UNION */
#define SOC_DSS_DSC_RC_PARAM4_ADDR(base)              ((base) + (0x0034))

/* 寄存器说明：RC参数寄存器5
   位域定义UNION结构:  SOC_DSS_DSC_RC_PARAM5_UNION */
#define SOC_DSS_DSC_RC_PARAM5_ADDR(base)              ((base) + (0x0038))

/* 寄存器说明：fullness阈值寄存器0
   位域定义UNION结构:  SOC_DSS_DSC_RC_BUF_THRESH0_UNION */
#define SOC_DSS_DSC_RC_BUF_THRESH0_ADDR(base)         ((base) + (0x003C))

/* 寄存器说明：fullness阈值寄存器1
   位域定义UNION结构:  SOC_DSS_DSC_RC_BUF_THRESH1_UNION */
#define SOC_DSS_DSC_RC_BUF_THRESH1_ADDR(base)         ((base) + (0x0040))

/* 寄存器说明：fullness阈值寄存器2
   位域定义UNION结构:  SOC_DSS_DSC_RC_BUF_THRESH2_UNION */
#define SOC_DSS_DSC_RC_BUF_THRESH2_ADDR(base)         ((base) + (0x0044))

/* 寄存器说明：fullness阈值寄存器3
   位域定义UNION结构:  SOC_DSS_DSC_RC_BUF_THRESH3_UNION */
#define SOC_DSS_DSC_RC_BUF_THRESH3_ADDR(base)         ((base) + (0x0048))

/* 寄存器说明：RC_RANGE参数寄存器0
   位域定义UNION结构:  SOC_DSS_DSC_RC_RANGE_PARAM0_UNION */
#define SOC_DSS_DSC_RC_RANGE_PARAM0_ADDR(base)        ((base) + (0x004C))

/* 寄存器说明：RC_RANGE参数寄存器1
   位域定义UNION结构:  SOC_DSS_DSC_RC_RANGE_PARAM1_UNION */
#define SOC_DSS_DSC_RC_RANGE_PARAM1_ADDR(base)        ((base) + (0x0050))

/* 寄存器说明：RC_RANGE参数寄存器2
   位域定义UNION结构:  SOC_DSS_DSC_RC_RANGE_PARAM2_UNION */
#define SOC_DSS_DSC_RC_RANGE_PARAM2_ADDR(base)        ((base) + (0x0054))

/* 寄存器说明：RC_RANGE参数寄存器3
   位域定义UNION结构:  SOC_DSS_DSC_RC_RANGE_PARAM3_UNION */
#define SOC_DSS_DSC_RC_RANGE_PARAM3_ADDR(base)        ((base) + (0x0058))

/* 寄存器说明：RC_RANGE参数寄存器4
   位域定义UNION结构:  SOC_DSS_DSC_RC_RANGE_PARAM4_UNION */
#define SOC_DSS_DSC_RC_RANGE_PARAM4_ADDR(base)        ((base) + (0x005C))

/* 寄存器说明：RC_RANGE参数寄存器5
   位域定义UNION结构:  SOC_DSS_DSC_RC_RANGE_PARAM5_UNION */
#define SOC_DSS_DSC_RC_RANGE_PARAM5_ADDR(base)        ((base) + (0x0060))

/* 寄存器说明：RC_RANGE参数寄存器6
   位域定义UNION结构:  SOC_DSS_DSC_RC_RANGE_PARAM6_UNION */
#define SOC_DSS_DSC_RC_RANGE_PARAM6_ADDR(base)        ((base) + (0x0064))

/* 寄存器说明：RC_RANGE参数寄存器7
   位域定义UNION结构:  SOC_DSS_DSC_RC_RANGE_PARAM7_UNION */
#define SOC_DSS_DSC_RC_RANGE_PARAM7_ADDR(base)        ((base) + (0x0068))

/* 寄存器说明：ADJUSTMENT_BITS寄存器
   位域定义UNION结构:  SOC_DSS_DSC_ADJUSTMENT_BITS_UNION */
#define SOC_DSS_DSC_ADJUSTMENT_BITS_ADDR(base)        ((base) + (0x006C))

/* 寄存器说明：group编码尺寸寄存器
   位域定义UNION结构:  SOC_DSS_DSC_BITS_PER_GRP_UNION */
#define SOC_DSS_DSC_BITS_PER_GRP_ADDR(base)           ((base) + (0x0070))

/* 寄存器说明：multi_slice控制寄存器
   位域定义UNION结构:  SOC_DSS_DSC_MULTI_SLICE_CTL_UNION */
#define SOC_DSS_DSC_MULTI_SLICE_CTL_ADDR(base)        ((base) + (0x0074))

/* 寄存器说明：DSC输出控制寄存器
   位域定义UNION结构:  SOC_DSS_DSC_DSC_OUT_CTRL_UNION */
#define SOC_DSS_DSC_DSC_OUT_CTRL_ADDR(base)           ((base) + (0x0078))

/* 寄存器说明：一级模块时钟选择信号
   位域定义UNION结构:  SOC_DSS_DSC_DSC_CLK_SEL_UNION */
#define SOC_DSS_DSC_DSC_CLK_SEL_ADDR(base)            ((base) + (0x007C))

/* 寄存器说明：一级模块时钟使能信号
   位域定义UNION结构:  SOC_DSS_DSC_DSC_CLK_EN_UNION */
#define SOC_DSS_DSC_DSC_CLK_EN_ADDR(base)             ((base) + (0x0080))

/* 寄存器说明：DSC memory低功耗控制寄存器
   位域定义UNION结构:  SOC_DSS_DSC_DSC_MEM_CTRL_UNION */
#define SOC_DSS_DSC_DSC_MEM_CTRL_ADDR(base)           ((base) + (0x0084))

/* 寄存器说明：输入状态寄存器
   位域定义UNION结构:  SOC_DSS_DSC_DSC_ST_DATAIN_UNION */
#define SOC_DSS_DSC_DSC_ST_DATAIN_ADDR(base)          ((base) + (0x0088))

/* 寄存器说明：输出状态寄存器
   位域定义UNION结构:  SOC_DSS_DSC_DSC_ST_DATAOUT_UNION */
#define SOC_DSS_DSC_DSC_ST_DATAOUT_ADDR(base)         ((base) + (0x008C))

/* 寄存器说明：SLICE位置状态寄存器
   位域定义UNION结构:  SOC_DSS_DSC_DSC0_ST_SLC_POS_UNION */
#define SOC_DSS_DSC_DSC0_ST_SLC_POS_ADDR(base)        ((base) + (0x0090))

/* 寄存器说明：SLICE位置状态寄存器
   位域定义UNION结构:  SOC_DSS_DSC_DSC1_ST_SLC_POS_UNION */
#define SOC_DSS_DSC_DSC1_ST_SLC_POS_ADDR(base)        ((base) + (0x0094))

/* 寄存器说明：PICTURE位置状态寄存器
   位域定义UNION结构:  SOC_DSS_DSC_DSC0_ST_PIC_POS_UNION */
#define SOC_DSS_DSC_DSC0_ST_PIC_POS_ADDR(base)        ((base) + (0x0098))

/* 寄存器说明：PICTURE位置状态寄存器
   位域定义UNION结构:  SOC_DSS_DSC_DSC1_ST_PIC_POS_UNION */
#define SOC_DSS_DSC_DSC1_ST_PIC_POS_ADDR(base)        ((base) + (0x009C))

/* 寄存器说明：FIFO空满状态寄存器
   位域定义UNION结构:  SOC_DSS_DSC_DSC0_ST_FIFO_UNION */
#define SOC_DSS_DSC_DSC0_ST_FIFO_ADDR(base)           ((base) + (0x00A0))

/* 寄存器说明：FIFO空满状态寄存器
   位域定义UNION结构:  SOC_DSS_DSC_DSC1_ST_FIFO_UNION */
#define SOC_DSS_DSC_DSC1_ST_FIFO_ADDR(base)           ((base) + (0x00A4))

/* 寄存器说明：LINEBUF状态寄存器
   位域定义UNION结构:  SOC_DSS_DSC_DSC0_ST_LINEBUF_UNION */
#define SOC_DSS_DSC_DSC0_ST_LINEBUF_ADDR(base)        ((base) + (0x00A8))

/* 寄存器说明：LINEBUF状态寄存器
   位域定义UNION结构:  SOC_DSS_DSC_DSC1_ST_LINEBUF_UNION */
#define SOC_DSS_DSC_DSC1_ST_LINEBUF_ADDR(base)        ((base) + (0x00AC))

/* 寄存器说明：接口状态寄存器
   位域定义UNION结构:  SOC_DSS_DSC_DSC_ST_ITFC_UNION */
#define SOC_DSS_DSC_DSC_ST_ITFC_ADDR(base)            ((base) + (0x00B0))

/* 寄存器说明：读寄存器选择信号
   位域定义UNION结构:  SOC_DSS_DSC_DSC_RD_SHADOW_SEL_UNION */
#define SOC_DSS_DSC_DSC_RD_SHADOW_SEL_ADDR(base)      ((base) + (0x00B4))

/* 寄存器说明：模块影子寄存器恢复到默认值
   位域定义UNION结构:  SOC_DSS_DSC_DSC_REG_DEFAULT_UNION */
#define SOC_DSS_DSC_DSC_REG_DEFAULT_ADDR(base)        ((base) + (0x00B8))





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
                     (1/1) reg_DSC
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_DSS_DSC_VERSION_UNION
 结构说明  : VERSION 寄存器结构定义。地址偏移量:0x0000，初值:0x00000011，宽度:32
 寄存器说明: 版本寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsc_version_minor : 4;  /* bit[0-3] : 小版本号 */
        unsigned int  dsc_version_major : 4;  /* bit[4-7] : 大版本号 */
        unsigned int  reserved          : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_DSS_DSC_VERSION_UNION;
#endif
#define SOC_DSS_DSC_VERSION_dsc_version_minor_START  (0)
#define SOC_DSS_DSC_VERSION_dsc_version_minor_END    (3)
#define SOC_DSS_DSC_VERSION_dsc_version_major_START  (4)
#define SOC_DSS_DSC_VERSION_dsc_version_major_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_DSC_PPS_IDENTIFIER_UNION
 结构说明  : PPS_IDENTIFIER 寄存器结构定义。地址偏移量:0x0004，初值:0x00000000，宽度:32
 寄存器说明: PPS标志寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pps_identifier : 8;  /* bit[0-7] : PPS识别号 */
        unsigned int  reserved       : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_DSC_PPS_IDENTIFIER_UNION;
#endif
#define SOC_DSS_DSC_PPS_IDENTIFIER_pps_identifier_START  (0)
#define SOC_DSS_DSC_PPS_IDENTIFIER_pps_identifier_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_DSC_DSC_EN_UNION
 结构说明  : DSC_EN 寄存器结构定义。地址偏移量:0x0008，初值:0x00000004，宽度:32
 寄存器说明: 使能寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsc_en             : 1;  /* bit[0]   : DSC使能寄存器
                                                             0: DSC不使能
                                                             1: DSC使能 */
        unsigned int  dual_dsc_en        : 1;  /* bit[1]   : 双通道DSC使能寄存器
                                                             0: 使用单通道DSC
                                                             1: 使用双通道DSC
                                                             双通道DSC在大分辨率（1080P以上）时使用，并且需要LCD支持用2颗DSC decoder解压 */
        unsigned int  dsc_if_bypass      : 1;  /* bit[2]   : dsc_if bypass控制寄存器
                                                             0: dsc_if使能
                                                             1: dsc_if不使能
                                                             软件约束：
                                                             当dual_dsc_en=1时，dsc_if_bypass必须为0；
                                                             当dual_dsc_en=0时，dsc_if_bypass为0或1均可，建议为1 */
        unsigned int  reset_ich_per_line : 1;  /* bit[3]   : ich每行复位使能寄存器
                                                             0: 不使能每行复位ich功能
                                                             1: 每行起始时复位ich
                                                             
                                                             符合协议的做法是，当dual_dsc_en = 1时，reset_ich_per_line必须为1；
                                                             但如果DriverIC不支持每行复位ich，此bit需要配置为0。 */
        unsigned int  reserved           : 28; /* bit[4-31]: 保留。 */
    } reg;
} SOC_DSS_DSC_DSC_EN_UNION;
#endif
#define SOC_DSS_DSC_DSC_EN_dsc_en_START              (0)
#define SOC_DSS_DSC_DSC_EN_dsc_en_END                (0)
#define SOC_DSS_DSC_DSC_EN_dual_dsc_en_START         (1)
#define SOC_DSS_DSC_DSC_EN_dual_dsc_en_END           (1)
#define SOC_DSS_DSC_DSC_EN_dsc_if_bypass_START       (2)
#define SOC_DSS_DSC_DSC_EN_dsc_if_bypass_END         (2)
#define SOC_DSS_DSC_DSC_EN_reset_ich_per_line_START  (3)
#define SOC_DSS_DSC_DSC_EN_reset_ich_per_line_END    (3)


/*****************************************************************************
 结构名    : SOC_DSS_DSC_DSC_CTRL_UNION
 结构说明  : DSC_CTRL 寄存器结构定义。地址偏移量:0x000C，初值:0x00080C98，宽度:32
 寄存器说明: 控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bits_per_component : 4;  /* bit[0-3]  : 输入像素每个分量的比特数，无符号整数
                                                              4'b1000: 8 bpc
                                                              其他: 保留 */
        unsigned int  linebuf_depth      : 4;  /* bit[4-7]  : line buffer数据位宽寄存器，无符号整数
                                                              4'b1000: 8 bits
                                                              4'b1001: 9 bits
                                                              其他：保留 */
        unsigned int  reserved_0         : 2;  /* bit[8-9]  : 保留 */
        unsigned int  block_pred_enable  : 1;  /* bit[10]   : block prediction使能寄存器
                                                              1'b0: 不使能block prediction
                                                              1'b1: 使能block prediction */
        unsigned int  convert_rgb        : 1;  /* bit[11]   : RGB->YCoCg转换使能寄存器
                                                              1'b0: 原始的输入是YCbCr
                                                              1'b1: 编码器将输入的RGB转换成YCoCg */
        unsigned int  enable_422         : 1;  /* bit[12]   : YCbCr采样模式寄存器
                                                              1'b0: 使用4:4:4采样
                                                              1'b1: 使用4:2:2采样 */
        unsigned int  vbr_enable         : 1;  /* bit[13]   : VBR使能寄存器
                                                              1'b0: 不使能VBR
                                                              1'b1: 使能VBR */
        unsigned int  reserved_1         : 2;  /* bit[14-15]: 保留 */
        unsigned int  bits_per_pixel     : 10; /* bit[16-25]: 目标压缩数据比特寄存器，无符号整数
                                                              软件约束：
                                                              1. 仅支持大于等于6bpp的数值
                                                              2. 当vbr_enable=0时，此寄存器需小于始终使用MPP预测时压缩像素的比特数 */
        unsigned int  reserved_2         : 6;  /* bit[26-31]: 保留。 */
    } reg;
} SOC_DSS_DSC_DSC_CTRL_UNION;
#endif
#define SOC_DSS_DSC_DSC_CTRL_bits_per_component_START  (0)
#define SOC_DSS_DSC_DSC_CTRL_bits_per_component_END    (3)
#define SOC_DSS_DSC_DSC_CTRL_linebuf_depth_START       (4)
#define SOC_DSS_DSC_DSC_CTRL_linebuf_depth_END         (7)
#define SOC_DSS_DSC_DSC_CTRL_block_pred_enable_START   (10)
#define SOC_DSS_DSC_DSC_CTRL_block_pred_enable_END     (10)
#define SOC_DSS_DSC_DSC_CTRL_convert_rgb_START         (11)
#define SOC_DSS_DSC_DSC_CTRL_convert_rgb_END           (11)
#define SOC_DSS_DSC_DSC_CTRL_enable_422_START          (12)
#define SOC_DSS_DSC_DSC_CTRL_enable_422_END            (12)
#define SOC_DSS_DSC_DSC_CTRL_vbr_enable_START          (13)
#define SOC_DSS_DSC_DSC_CTRL_vbr_enable_END            (13)
#define SOC_DSS_DSC_DSC_CTRL_bits_per_pixel_START      (16)
#define SOC_DSS_DSC_DSC_CTRL_bits_per_pixel_END        (25)


/*****************************************************************************
 结构名    : SOC_DSS_DSC_PIC_SIZE_UNION
 结构说明  : PIC_SIZE 寄存器结构定义。地址偏移量:0x0010，初值:0x00000000，宽度:32
 寄存器说明: 输入图像尺寸寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pic_height : 16; /* bit[0-15] : 原始输入图像高度寄存器，单位是行。配置值为实际值减1 */
        unsigned int  pic_width  : 16; /* bit[16-31]: 原始输入图像宽度寄存器，单位是像素。配置值为实际值减1 */
    } reg;
} SOC_DSS_DSC_PIC_SIZE_UNION;
#endif
#define SOC_DSS_DSC_PIC_SIZE_pic_height_START  (0)
#define SOC_DSS_DSC_PIC_SIZE_pic_height_END    (15)
#define SOC_DSS_DSC_PIC_SIZE_pic_width_START   (16)
#define SOC_DSS_DSC_PIC_SIZE_pic_width_END     (31)


/*****************************************************************************
 结构名    : SOC_DSS_DSC_SLICE_SIZE_UNION
 结构说明  : SLICE_SIZE 寄存器结构定义。地址偏移量:0x0014，初值:0x00000000，宽度:32
 寄存器说明: SLICE尺寸寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  slice_height : 16; /* bit[0-15] : slice高度寄存器，单位是行。配置值为实际值减1 */
        unsigned int  slice_width  : 16; /* bit[16-31]: slice宽度寄存器，单位是像素。配置值为实际值减1 */
    } reg;
} SOC_DSS_DSC_SLICE_SIZE_UNION;
#endif
#define SOC_DSS_DSC_SLICE_SIZE_slice_height_START  (0)
#define SOC_DSS_DSC_SLICE_SIZE_slice_height_END    (15)
#define SOC_DSS_DSC_SLICE_SIZE_slice_width_START   (16)
#define SOC_DSS_DSC_SLICE_SIZE_slice_width_END     (31)


/*****************************************************************************
 结构名    : SOC_DSS_DSC_CHUNK_SIZE_UNION
 结构说明  : CHUNK_SIZE 寄存器结构定义。地址偏移量:0x0018，初值:0x00000000，宽度:32
 寄存器说明: chunk尺寸寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  chunk_size : 16; /* bit[0-15] : chunk尺寸寄存器，，无符号整数
                                                      配置值为ceil(bits_per_pixel*slice_width/8) bytes */
        unsigned int  reserved   : 16; /* bit[16-31]: 保留 */
    } reg;
} SOC_DSS_DSC_CHUNK_SIZE_UNION;
#endif
#define SOC_DSS_DSC_CHUNK_SIZE_chunk_size_START  (0)
#define SOC_DSS_DSC_CHUNK_SIZE_chunk_size_END    (15)


/*****************************************************************************
 结构名    : SOC_DSS_DSC_INITIAL_DELAY_UNION
 结构说明  : INITIAL_DELAY 寄存器结构定义。地址偏移量:0x001C，初值:0x00000200，宽度:32
 寄存器说明: RC model延时寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  initial_xmit_delay : 10; /* bit[0-9]  : Initial decoding delay. Specifies the number
                                                              of pixel times that the decoder accumulates
                                                              data in its rate buffer before starting
                                                              to decode and output pixels. */
        unsigned int  reserved           : 6;  /* bit[10-15]: 保留 */
        unsigned int  initial_dec_delay  : 16; /* bit[16-31]: Initial transmission delay. Specifies the
                                                              number of pixel times that the encoder waits
                                                              before transmitting data from its rate buffer. */
    } reg;
} SOC_DSS_DSC_INITIAL_DELAY_UNION;
#endif
#define SOC_DSS_DSC_INITIAL_DELAY_initial_xmit_delay_START  (0)
#define SOC_DSS_DSC_INITIAL_DELAY_initial_xmit_delay_END    (9)
#define SOC_DSS_DSC_INITIAL_DELAY_initial_dec_delay_START   (16)
#define SOC_DSS_DSC_INITIAL_DELAY_initial_dec_delay_END     (31)


/*****************************************************************************
 结构名    : SOC_DSS_DSC_RC_PARAM0_UNION
 结构说明  : RC_PARAM0 寄存器结构定义。地址偏移量:0x0020，初值:0x00000020，宽度:32
 寄存器说明: RC参数寄存器0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  initial_scale_value      : 6;  /* bit[0-5]  : 无符号小数，低三比特位小数位
                                                                    Specifies the initial rcXformScale factor value used at the beginning of a slice */
        unsigned int  reserved                 : 10; /* bit[6-15] : 保留 */
        unsigned int  scale_increment_interval : 16; /* bit[16-31]: Specifies the number of group times between
                                                                    incrementing the rcXformScale factor at the end of a slice */
    } reg;
} SOC_DSS_DSC_RC_PARAM0_UNION;
#endif
#define SOC_DSS_DSC_RC_PARAM0_initial_scale_value_START       (0)
#define SOC_DSS_DSC_RC_PARAM0_initial_scale_value_END         (5)
#define SOC_DSS_DSC_RC_PARAM0_scale_increment_interval_START  (16)
#define SOC_DSS_DSC_RC_PARAM0_scale_increment_interval_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_DSC_RC_PARAM1_UNION
 结构说明  : RC_PARAM1 寄存器结构定义。地址偏移量:0x0024，初值:0x000C0000，宽度:32
 寄存器说明: RC参数寄存器1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scale_decrement_interval : 12; /* bit[0-11] : Specifies the number of group times between decrementing the rcXformScale factor at the beginning of a slice */
        unsigned int  reserved_0               : 4;  /* bit[12-15]: 保留 */
        unsigned int  first_line_bpg_offset    : 5;  /* bit[16-20]: 无符号整数
                                                                    Specifies the number of additional bits that are allocated for each group on the first line of a slice. */
        unsigned int  reserved_1               : 11; /* bit[21-31]: 保留 */
    } reg;
} SOC_DSS_DSC_RC_PARAM1_UNION;
#endif
#define SOC_DSS_DSC_RC_PARAM1_scale_decrement_interval_START  (0)
#define SOC_DSS_DSC_RC_PARAM1_scale_decrement_interval_END    (11)
#define SOC_DSS_DSC_RC_PARAM1_first_line_bpg_offset_START     (16)
#define SOC_DSS_DSC_RC_PARAM1_first_line_bpg_offset_END       (20)


/*****************************************************************************
 结构名    : SOC_DSS_DSC_RC_PARAM2_UNION
 结构说明  : RC_PARAM2 寄存器结构定义。地址偏移量:0x0028，初值:0x00000000，宽度:32
 寄存器说明: RC参数寄存器2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  nfl_bpg_offset   : 16; /* bit[0-15] : 无符号小数，低11 bits为小数位
                                                            Specifies the number of bits (including fractional bits) that are de-allocated for each group, for groups after the first line of a slice. */
        unsigned int  slice_bpg_offset : 16; /* bit[16-31]: 无符号小数，低11 bits为小数位 */
    } reg;
} SOC_DSS_DSC_RC_PARAM2_UNION;
#endif
#define SOC_DSS_DSC_RC_PARAM2_nfl_bpg_offset_START    (0)
#define SOC_DSS_DSC_RC_PARAM2_nfl_bpg_offset_END      (15)
#define SOC_DSS_DSC_RC_PARAM2_slice_bpg_offset_START  (16)
#define SOC_DSS_DSC_RC_PARAM2_slice_bpg_offset_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_DSC_RC_PARAM3_UNION
 结构说明  : RC_PARAM3 寄存器结构定义。地址偏移量:0x002C，初值:0x00001800，宽度:32
 寄存器说明: RC参数寄存器3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  initial_offset : 16; /* bit[0-15] : 无符号整数
                                                          Specifies the initial value for rcXformOffset, which is initial_offset - rc_model_size at the start of a slice */
        unsigned int  final_offset   : 16; /* bit[16-31]: 无符号整数
                                                          Specifies the maximum end-of-slice value for rcXformOffset, which is final_offset - rc_model_size */
    } reg;
} SOC_DSS_DSC_RC_PARAM3_UNION;
#endif
#define SOC_DSS_DSC_RC_PARAM3_initial_offset_START  (0)
#define SOC_DSS_DSC_RC_PARAM3_initial_offset_END    (15)
#define SOC_DSS_DSC_RC_PARAM3_final_offset_START    (16)
#define SOC_DSS_DSC_RC_PARAM3_final_offset_END      (31)


/*****************************************************************************
 结构名    : SOC_DSS_DSC_FLATNESS_QP_TH_UNION
 结构说明  : FLATNESS_QP_TH 寄存器结构定义。地址偏移量:0x0030，初值:0x000C0003，宽度:32
 寄存器说明: flatness QP阈值寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flatness_min_qp : 8;  /* bit[0-7]  : 无符号整数
                                                           Specifies the minimum QP at which flatness is signaled and the flatness QP adjustment is made. */
        unsigned int  reserved_0      : 8;  /* bit[8-15] :  */
        unsigned int  flatness_max_qp : 8;  /* bit[16-23]: 无符号整数
                                                           Specifies the maximum QP at which flatness is signaled and the flatness QP adjustment is made. */
        unsigned int  reserved_1      : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_DSC_FLATNESS_QP_TH_UNION;
#endif
#define SOC_DSS_DSC_FLATNESS_QP_TH_flatness_min_qp_START  (0)
#define SOC_DSS_DSC_FLATNESS_QP_TH_flatness_min_qp_END    (7)
#define SOC_DSS_DSC_FLATNESS_QP_TH_flatness_max_qp_START  (16)
#define SOC_DSS_DSC_FLATNESS_QP_TH_flatness_max_qp_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_DSC_RC_PARAM4_UNION
 结构说明  : RC_PARAM4 寄存器结构定义。地址偏移量:0x0034，初值:0x00602000，宽度:32
 寄存器说明: RC参数寄存器4
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rc_model_size  : 16; /* bit[0-15] : 无符号整数
                                                          Specifies the number of bits within the
                                                          “RC model” */
        unsigned int  reserved_0     : 4;  /* bit[16-19]: 保留 */
        unsigned int  rc_edge_factor : 4;  /* bit[20-23]: 无符号小数，低1比特位小数位
                                                          Compared to the ratio of current activity vs. previous activity to determine the presence of an “edge,” which in turn determines whether the QP is incremented in the short-term RC */
        unsigned int  reserved_1     : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_DSC_RC_PARAM4_UNION;
#endif
#define SOC_DSS_DSC_RC_PARAM4_rc_model_size_START   (0)
#define SOC_DSS_DSC_RC_PARAM4_rc_model_size_END     (15)
#define SOC_DSS_DSC_RC_PARAM4_rc_edge_factor_START  (20)
#define SOC_DSS_DSC_RC_PARAM4_rc_edge_factor_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_DSC_RC_PARAM5_UNION
 结构说明  : RC_PARAM5 寄存器结构定义。地址偏移量:0x0038，初值:0x00330B0B，宽度:32
 寄存器说明: RC参数寄存器5
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rc_quant_incr_limit0 : 5;  /* bit[0-4]  : 无符号整数
                                                                QP threshold that is used in the short-term RC */
        unsigned int  reserved_0           : 3;  /* bit[5-7]  : 保留 */
        unsigned int  rc_quant_incr_limit1 : 5;  /* bit[8-12] : 无符号整数
                                                                QP threshold that is used in the short-term RC */
        unsigned int  reserved_1           : 3;  /* bit[13-15]: 保留 */
        unsigned int  rc_tgt_offset_hi     : 4;  /* bit[16-19]: 无符号整数
                                                                Specifies the upper end of the variability range around the target bits per group that is allowed by the short-term RC */
        unsigned int  rc_tgt_offset_lo     : 4;  /* bit[20-23]: 无符号整数
                                                                Specifies the lower end of the variability range around the target bits per group that is allowed by the short-term RC */
        unsigned int  reserved_2           : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_DSC_RC_PARAM5_UNION;
#endif
#define SOC_DSS_DSC_RC_PARAM5_rc_quant_incr_limit0_START  (0)
#define SOC_DSS_DSC_RC_PARAM5_rc_quant_incr_limit0_END    (4)
#define SOC_DSS_DSC_RC_PARAM5_rc_quant_incr_limit1_START  (8)
#define SOC_DSS_DSC_RC_PARAM5_rc_quant_incr_limit1_END    (12)
#define SOC_DSS_DSC_RC_PARAM5_rc_tgt_offset_hi_START      (16)
#define SOC_DSS_DSC_RC_PARAM5_rc_tgt_offset_hi_END        (19)
#define SOC_DSS_DSC_RC_PARAM5_rc_tgt_offset_lo_START      (20)
#define SOC_DSS_DSC_RC_PARAM5_rc_tgt_offset_lo_END        (23)


/*****************************************************************************
 结构名    : SOC_DSS_DSC_RC_BUF_THRESH0_UNION
 结构说明  : RC_BUF_THRESH0 寄存器结构定义。地址偏移量:0x003C，初值:0x0E1C2A38，宽度:32
 寄存器说明: fullness阈值寄存器0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rc_buf_thresh3 : 8;  /* bit[0-7]  : 无符号整数
                                                          此寄存器左移6bit得到实际的阈值，用于long-term RC计算 */
        unsigned int  rc_buf_thresh2 : 8;  /* bit[8-15] : 无符号整数
                                                          此寄存器左移6bit得到实际的阈值，用于long-term RC计算 */
        unsigned int  rc_buf_thresh1 : 8;  /* bit[16-23]: 无符号整数
                                                          此寄存器左移6bit得到实际的阈值，用于long-term RC计算 */
        unsigned int  rc_buf_thresh0 : 8;  /* bit[24-31]: 无符号整数
                                                          此寄存器左移6bit得到实际的阈值，用于long-term RC计算 */
    } reg;
} SOC_DSS_DSC_RC_BUF_THRESH0_UNION;
#endif
#define SOC_DSS_DSC_RC_BUF_THRESH0_rc_buf_thresh3_START  (0)
#define SOC_DSS_DSC_RC_BUF_THRESH0_rc_buf_thresh3_END    (7)
#define SOC_DSS_DSC_RC_BUF_THRESH0_rc_buf_thresh2_START  (8)
#define SOC_DSS_DSC_RC_BUF_THRESH0_rc_buf_thresh2_END    (15)
#define SOC_DSS_DSC_RC_BUF_THRESH0_rc_buf_thresh1_START  (16)
#define SOC_DSS_DSC_RC_BUF_THRESH0_rc_buf_thresh1_END    (23)
#define SOC_DSS_DSC_RC_BUF_THRESH0_rc_buf_thresh0_START  (24)
#define SOC_DSS_DSC_RC_BUF_THRESH0_rc_buf_thresh0_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_DSC_RC_BUF_THRESH1_UNION
 结构说明  : RC_BUF_THRESH1 寄存器结构定义。地址偏移量:0x0040，初值:0x46546269，宽度:32
 寄存器说明: fullness阈值寄存器1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rc_buf_thresh7 : 8;  /* bit[0-7]  : 无符号整数
                                                          此寄存器左移6bit得到实际的阈值，用于long-term RC计算 */
        unsigned int  rc_buf_thresh6 : 8;  /* bit[8-15] : 无符号整数
                                                          此寄存器左移6bit得到实际的阈值，用于long-term RC计算 */
        unsigned int  rc_buf_thresh5 : 8;  /* bit[16-23]: 无符号整数
                                                          此寄存器左移6bit得到实际的阈值，用于long-term RC计算 */
        unsigned int  rc_buf_thresh4 : 8;  /* bit[24-31]: 无符号整数
                                                          此寄存器左移6bit得到实际的阈值，用于long-term RC计算 */
    } reg;
} SOC_DSS_DSC_RC_BUF_THRESH1_UNION;
#endif
#define SOC_DSS_DSC_RC_BUF_THRESH1_rc_buf_thresh7_START  (0)
#define SOC_DSS_DSC_RC_BUF_THRESH1_rc_buf_thresh7_END    (7)
#define SOC_DSS_DSC_RC_BUF_THRESH1_rc_buf_thresh6_START  (8)
#define SOC_DSS_DSC_RC_BUF_THRESH1_rc_buf_thresh6_END    (15)
#define SOC_DSS_DSC_RC_BUF_THRESH1_rc_buf_thresh5_START  (16)
#define SOC_DSS_DSC_RC_BUF_THRESH1_rc_buf_thresh5_END    (23)
#define SOC_DSS_DSC_RC_BUF_THRESH1_rc_buf_thresh4_START  (24)
#define SOC_DSS_DSC_RC_BUF_THRESH1_rc_buf_thresh4_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_DSC_RC_BUF_THRESH2_UNION
 结构说明  : RC_BUF_THRESH2 寄存器结构定义。地址偏移量:0x0044，初值:0x7077797B，宽度:32
 寄存器说明: fullness阈值寄存器2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rc_buf_thresh11 : 8;  /* bit[0-7]  : 无符号整数
                                                           此寄存器左移6bit得到实际的阈值，用于long-term RC计算 */
        unsigned int  rc_buf_thresh10 : 8;  /* bit[8-15] : 无符号整数
                                                           此寄存器左移6bit得到实际的阈值，用于long-term RC计算 */
        unsigned int  rc_buf_thresh9  : 8;  /* bit[16-23]: 无符号整数
                                                           此寄存器左移6bit得到实际的阈值，用于long-term RC计算 */
        unsigned int  rc_buf_thresh8  : 8;  /* bit[24-31]: 无符号整数
                                                           此寄存器左移6bit得到实际的阈值，用于long-term RC计算 */
    } reg;
} SOC_DSS_DSC_RC_BUF_THRESH2_UNION;
#endif
#define SOC_DSS_DSC_RC_BUF_THRESH2_rc_buf_thresh11_START  (0)
#define SOC_DSS_DSC_RC_BUF_THRESH2_rc_buf_thresh11_END    (7)
#define SOC_DSS_DSC_RC_BUF_THRESH2_rc_buf_thresh10_START  (8)
#define SOC_DSS_DSC_RC_BUF_THRESH2_rc_buf_thresh10_END    (15)
#define SOC_DSS_DSC_RC_BUF_THRESH2_rc_buf_thresh9_START   (16)
#define SOC_DSS_DSC_RC_BUF_THRESH2_rc_buf_thresh9_END     (23)
#define SOC_DSS_DSC_RC_BUF_THRESH2_rc_buf_thresh8_START   (24)
#define SOC_DSS_DSC_RC_BUF_THRESH2_rc_buf_thresh8_END     (31)


/*****************************************************************************
 结构名    : SOC_DSS_DSC_RC_BUF_THRESH3_UNION
 结构说明  : RC_BUF_THRESH3 寄存器结构定义。地址偏移量:0x0048，初值:0x7D7E0000，宽度:32
 寄存器说明: fullness阈值寄存器3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved        : 16; /* bit[0-15] : 保留 */
        unsigned int  rc_buf_thresh13 : 8;  /* bit[16-23]: 无符号整数
                                                           此寄存器左移6bit得到实际的阈值，用于long-term RC计算 */
        unsigned int  rc_buf_thresh12 : 8;  /* bit[24-31]: 无符号整数
                                                           此寄存器左移6bit得到实际的阈值，用于long-term RC计算 */
    } reg;
} SOC_DSS_DSC_RC_BUF_THRESH3_UNION;
#endif
#define SOC_DSS_DSC_RC_BUF_THRESH3_rc_buf_thresh13_START  (16)
#define SOC_DSS_DSC_RC_BUF_THRESH3_rc_buf_thresh13_END    (23)
#define SOC_DSS_DSC_RC_BUF_THRESH3_rc_buf_thresh12_START  (24)
#define SOC_DSS_DSC_RC_BUF_THRESH3_rc_buf_thresh12_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_DSC_RC_RANGE_PARAM0_UNION
 结构说明  : RC_RANGE_PARAM0 寄存器结构定义。地址偏移量:0x004C，初值:0x01020100，宽度:32
 寄存器说明: RC_RANGE参数寄存器0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  range_bpg_offset1 : 6;  /* bit[0-5]  : long-rc range为1时的range参数
                                                             有符号数 */
        unsigned int  range_max_qp1     : 5;  /* bit[6-10] : long-rc range为1时的range参数
                                                             无符号数 */
        unsigned int  range_min_qp1     : 5;  /* bit[11-15]: long-rc range为1时的range参数
                                                             无符号数 */
        unsigned int  range_bpg_offset0 : 6;  /* bit[16-21]: long-rc range为0时的range参数
                                                             有符号数 */
        unsigned int  range_max_qp0     : 5;  /* bit[22-26]: long-rc range为0时的range参数
                                                             无符号数 */
        unsigned int  range_min_qp0     : 5;  /* bit[27-31]: long-rc range为0时的range参数
                                                             无符号数 */
    } reg;
} SOC_DSS_DSC_RC_RANGE_PARAM0_UNION;
#endif
#define SOC_DSS_DSC_RC_RANGE_PARAM0_range_bpg_offset1_START  (0)
#define SOC_DSS_DSC_RC_RANGE_PARAM0_range_bpg_offset1_END    (5)
#define SOC_DSS_DSC_RC_RANGE_PARAM0_range_max_qp1_START      (6)
#define SOC_DSS_DSC_RC_RANGE_PARAM0_range_max_qp1_END        (10)
#define SOC_DSS_DSC_RC_RANGE_PARAM0_range_min_qp1_START      (11)
#define SOC_DSS_DSC_RC_RANGE_PARAM0_range_min_qp1_END        (15)
#define SOC_DSS_DSC_RC_RANGE_PARAM0_range_bpg_offset0_START  (16)
#define SOC_DSS_DSC_RC_RANGE_PARAM0_range_bpg_offset0_END    (21)
#define SOC_DSS_DSC_RC_RANGE_PARAM0_range_max_qp0_START      (22)
#define SOC_DSS_DSC_RC_RANGE_PARAM0_range_max_qp0_END        (26)
#define SOC_DSS_DSC_RC_RANGE_PARAM0_range_min_qp0_START      (27)
#define SOC_DSS_DSC_RC_RANGE_PARAM0_range_min_qp0_END        (31)


/*****************************************************************************
 结构名    : SOC_DSS_DSC_RC_RANGE_PARAM1_UNION
 结构说明  : RC_RANGE_PARAM1 寄存器结构定义。地址偏移量:0x0050，初值:0x094009BE，宽度:32
 寄存器说明: RC_RANGE参数寄存器1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  range_bpg_offset3 : 6;  /* bit[0-5]  : long-rc range为3时的range参数
                                                             有符号数 */
        unsigned int  range_max_qp3     : 5;  /* bit[6-10] : long-rc range为3时的range参数
                                                             无符号数 */
        unsigned int  range_min_qp3     : 5;  /* bit[11-15]: long-rc range为3时的range参数
                                                             无符号数 */
        unsigned int  range_bpg_offset2 : 6;  /* bit[16-21]: long-rc range为2时的range参数
                                                             有符号数 */
        unsigned int  range_max_qp2     : 5;  /* bit[22-26]: long-rc range为2时的range参数
                                                             无符号数 */
        unsigned int  range_min_qp2     : 5;  /* bit[27-31]: long-rc range为2时的range参数
                                                             无符号数 */
    } reg;
} SOC_DSS_DSC_RC_RANGE_PARAM1_UNION;
#endif
#define SOC_DSS_DSC_RC_RANGE_PARAM1_range_bpg_offset3_START  (0)
#define SOC_DSS_DSC_RC_RANGE_PARAM1_range_bpg_offset3_END    (5)
#define SOC_DSS_DSC_RC_RANGE_PARAM1_range_max_qp3_START      (6)
#define SOC_DSS_DSC_RC_RANGE_PARAM1_range_max_qp3_END        (10)
#define SOC_DSS_DSC_RC_RANGE_PARAM1_range_min_qp3_START      (11)
#define SOC_DSS_DSC_RC_RANGE_PARAM1_range_min_qp3_END        (15)
#define SOC_DSS_DSC_RC_RANGE_PARAM1_range_bpg_offset2_START  (16)
#define SOC_DSS_DSC_RC_RANGE_PARAM1_range_bpg_offset2_END    (21)
#define SOC_DSS_DSC_RC_RANGE_PARAM1_range_max_qp2_START      (22)
#define SOC_DSS_DSC_RC_RANGE_PARAM1_range_max_qp2_END        (26)
#define SOC_DSS_DSC_RC_RANGE_PARAM1_range_min_qp2_START      (27)
#define SOC_DSS_DSC_RC_RANGE_PARAM1_range_min_qp2_END        (31)


/*****************************************************************************
 结构名    : SOC_DSS_DSC_RC_RANGE_PARAM2_UNION
 结构说明  : RC_RANGE_PARAM2 寄存器结构定义。地址偏移量:0x0054，初值:0x19FC19FA，宽度:32
 寄存器说明: RC_RANGE参数寄存器2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  range_bpg_offset5 : 6;  /* bit[0-5]  : long-rc range为5时的range参数
                                                             有符号数 */
        unsigned int  range_max_qp5     : 5;  /* bit[6-10] : long-rc range为5时的range参数
                                                             无符号数 */
        unsigned int  range_min_qp5     : 5;  /* bit[11-15]: long-rc range为5时的range参数
                                                             无符号数 */
        unsigned int  range_bpg_offset4 : 6;  /* bit[16-21]: long-rc range为4时的range参数
                                                             有符号数 */
        unsigned int  range_max_qp4     : 5;  /* bit[22-26]: long-rc range为4时的range参数
                                                             无符号数 */
        unsigned int  range_min_qp4     : 5;  /* bit[27-31]: long-rc range为4时的range参数
                                                             无符号数 */
    } reg;
} SOC_DSS_DSC_RC_RANGE_PARAM2_UNION;
#endif
#define SOC_DSS_DSC_RC_RANGE_PARAM2_range_bpg_offset5_START  (0)
#define SOC_DSS_DSC_RC_RANGE_PARAM2_range_bpg_offset5_END    (5)
#define SOC_DSS_DSC_RC_RANGE_PARAM2_range_max_qp5_START      (6)
#define SOC_DSS_DSC_RC_RANGE_PARAM2_range_max_qp5_END        (10)
#define SOC_DSS_DSC_RC_RANGE_PARAM2_range_min_qp5_START      (11)
#define SOC_DSS_DSC_RC_RANGE_PARAM2_range_min_qp5_END        (15)
#define SOC_DSS_DSC_RC_RANGE_PARAM2_range_bpg_offset4_START  (16)
#define SOC_DSS_DSC_RC_RANGE_PARAM2_range_bpg_offset4_END    (21)
#define SOC_DSS_DSC_RC_RANGE_PARAM2_range_max_qp4_START      (22)
#define SOC_DSS_DSC_RC_RANGE_PARAM2_range_max_qp4_END        (26)
#define SOC_DSS_DSC_RC_RANGE_PARAM2_range_min_qp4_START      (27)
#define SOC_DSS_DSC_RC_RANGE_PARAM2_range_min_qp4_END        (31)


/*****************************************************************************
 结构名    : SOC_DSS_DSC_RC_RANGE_PARAM3_UNION
 结构说明  : RC_RANGE_PARAM3 寄存器结构定义。地址偏移量:0x0058，初值:0x19F81A38，宽度:32
 寄存器说明: RC_RANGE参数寄存器3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  range_bpg_offset7 : 6;  /* bit[0-5]  : long-rc range为7时的range参数
                                                             有符号数 */
        unsigned int  range_max_qp7     : 5;  /* bit[6-10] : long-rc range为7时的range参数
                                                             无符号数 */
        unsigned int  range_min_qp7     : 5;  /* bit[11-15]: long-rc range为7时的range参数
                                                             无符号数 */
        unsigned int  range_bpg_offset6 : 6;  /* bit[16-21]: long-rc range为6时的range参数
                                                             有符号数 */
        unsigned int  range_max_qp6     : 5;  /* bit[22-26]: long-rc range为6时的range参数
                                                             无符号数 */
        unsigned int  range_min_qp6     : 5;  /* bit[27-31]: long-rc range为6时的range参数
                                                             无符号数 */
    } reg;
} SOC_DSS_DSC_RC_RANGE_PARAM3_UNION;
#endif
#define SOC_DSS_DSC_RC_RANGE_PARAM3_range_bpg_offset7_START  (0)
#define SOC_DSS_DSC_RC_RANGE_PARAM3_range_bpg_offset7_END    (5)
#define SOC_DSS_DSC_RC_RANGE_PARAM3_range_max_qp7_START      (6)
#define SOC_DSS_DSC_RC_RANGE_PARAM3_range_max_qp7_END        (10)
#define SOC_DSS_DSC_RC_RANGE_PARAM3_range_min_qp7_START      (11)
#define SOC_DSS_DSC_RC_RANGE_PARAM3_range_min_qp7_END        (15)
#define SOC_DSS_DSC_RC_RANGE_PARAM3_range_bpg_offset6_START  (16)
#define SOC_DSS_DSC_RC_RANGE_PARAM3_range_bpg_offset6_END    (21)
#define SOC_DSS_DSC_RC_RANGE_PARAM3_range_max_qp6_START      (22)
#define SOC_DSS_DSC_RC_RANGE_PARAM3_range_max_qp6_END        (26)
#define SOC_DSS_DSC_RC_RANGE_PARAM3_range_min_qp6_START      (27)
#define SOC_DSS_DSC_RC_RANGE_PARAM3_range_min_qp6_END        (31)


/*****************************************************************************
 结构名    : SOC_DSS_DSC_RC_RANGE_PARAM4_UNION
 结构说明  : RC_RANGE_PARAM4 寄存器结构定义。地址偏移量:0x005C，初值:0x1A781AB6，宽度:32
 寄存器说明: RC_RANGE参数寄存器4
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  range_bpg_offset9 : 6;  /* bit[0-5]  : long-rc range为9时的range参数
                                                             有符号数 */
        unsigned int  range_max_qp9     : 5;  /* bit[6-10] : long-rc range为9时的range参数
                                                             无符号数 */
        unsigned int  range_min_qp9     : 5;  /* bit[11-15]: long-rc range为9时的range参数
                                                             无符号数 */
        unsigned int  range_bpg_offset8 : 6;  /* bit[16-21]: long-rc range为8时的range参数
                                                             有符号数 */
        unsigned int  range_max_qp8     : 5;  /* bit[22-26]: long-rc range为8时的range参数
                                                             无符号数 */
        unsigned int  range_min_qp8     : 5;  /* bit[27-31]: long-rc range为8时的range参数
                                                             无符号数 */
    } reg;
} SOC_DSS_DSC_RC_RANGE_PARAM4_UNION;
#endif
#define SOC_DSS_DSC_RC_RANGE_PARAM4_range_bpg_offset9_START  (0)
#define SOC_DSS_DSC_RC_RANGE_PARAM4_range_bpg_offset9_END    (5)
#define SOC_DSS_DSC_RC_RANGE_PARAM4_range_max_qp9_START      (6)
#define SOC_DSS_DSC_RC_RANGE_PARAM4_range_max_qp9_END        (10)
#define SOC_DSS_DSC_RC_RANGE_PARAM4_range_min_qp9_START      (11)
#define SOC_DSS_DSC_RC_RANGE_PARAM4_range_min_qp9_END        (15)
#define SOC_DSS_DSC_RC_RANGE_PARAM4_range_bpg_offset8_START  (16)
#define SOC_DSS_DSC_RC_RANGE_PARAM4_range_bpg_offset8_END    (21)
#define SOC_DSS_DSC_RC_RANGE_PARAM4_range_max_qp8_START      (22)
#define SOC_DSS_DSC_RC_RANGE_PARAM4_range_max_qp8_END        (26)
#define SOC_DSS_DSC_RC_RANGE_PARAM4_range_min_qp8_START      (27)
#define SOC_DSS_DSC_RC_RANGE_PARAM4_range_min_qp8_END        (31)


/*****************************************************************************
 结构名    : SOC_DSS_DSC_RC_RANGE_PARAM5_UNION
 结构说明  : RC_RANGE_PARAM5 寄存器结构定义。地址偏移量:0x0060，初值:0x2AF62B34，宽度:32
 寄存器说明: RC_RANGE参数寄存器5
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  range_bpg_offset11 : 6;  /* bit[0-5]  : long-rc range为11时的range参数
                                                              有符号数 */
        unsigned int  range_max_qp11     : 5;  /* bit[6-10] : long-rc range为11时的range参数
                                                              无符号数 */
        unsigned int  range_min_qp11     : 5;  /* bit[11-15]: long-rc range为11时的range参数
                                                              无符号数 */
        unsigned int  range_bpg_offset10 : 6;  /* bit[16-21]: long-rc range为10时的range参数
                                                              有符号数 */
        unsigned int  range_max_qp10     : 5;  /* bit[22-26]: long-rc range为10时的range参数
                                                              无符号数 */
        unsigned int  range_min_qp10     : 5;  /* bit[27-31]: long-rc range为10时的range参数
                                                              无符号数 */
    } reg;
} SOC_DSS_DSC_RC_RANGE_PARAM5_UNION;
#endif
#define SOC_DSS_DSC_RC_RANGE_PARAM5_range_bpg_offset11_START  (0)
#define SOC_DSS_DSC_RC_RANGE_PARAM5_range_bpg_offset11_END    (5)
#define SOC_DSS_DSC_RC_RANGE_PARAM5_range_max_qp11_START      (6)
#define SOC_DSS_DSC_RC_RANGE_PARAM5_range_max_qp11_END        (10)
#define SOC_DSS_DSC_RC_RANGE_PARAM5_range_min_qp11_START      (11)
#define SOC_DSS_DSC_RC_RANGE_PARAM5_range_min_qp11_END        (15)
#define SOC_DSS_DSC_RC_RANGE_PARAM5_range_bpg_offset10_START  (16)
#define SOC_DSS_DSC_RC_RANGE_PARAM5_range_bpg_offset10_END    (21)
#define SOC_DSS_DSC_RC_RANGE_PARAM5_range_max_qp10_START      (22)
#define SOC_DSS_DSC_RC_RANGE_PARAM5_range_max_qp10_END        (26)
#define SOC_DSS_DSC_RC_RANGE_PARAM5_range_min_qp10_START      (27)
#define SOC_DSS_DSC_RC_RANGE_PARAM5_range_min_qp10_END        (31)


/*****************************************************************************
 结构名    : SOC_DSS_DSC_RC_RANGE_PARAM6_UNION
 结构说明  : RC_RANGE_PARAM6 寄存器结构定义。地址偏移量:0x0064，初值:0x2B743B74，宽度:32
 寄存器说明: RC_RANGE参数寄存器6
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  range_bpg_offset13 : 6;  /* bit[0-5]  : long-rc range为13时的range参数
                                                              有符号数 */
        unsigned int  range_max_qp13     : 5;  /* bit[6-10] : long-rc range为13时的range参数
                                                              无符号数 */
        unsigned int  range_min_qp13     : 5;  /* bit[11-15]: long-rc range为13时的range参数
                                                              无符号数 */
        unsigned int  range_bpg_offset12 : 6;  /* bit[16-21]: long-rc range为12时的range参数
                                                              有符号数 */
        unsigned int  range_max_qp12     : 5;  /* bit[22-26]: long-rc range为12时的range参数
                                                              无符号数 */
        unsigned int  range_min_qp12     : 5;  /* bit[27-31]: long-rc range为12时的range参数
                                                              无符号数 */
    } reg;
} SOC_DSS_DSC_RC_RANGE_PARAM6_UNION;
#endif
#define SOC_DSS_DSC_RC_RANGE_PARAM6_range_bpg_offset13_START  (0)
#define SOC_DSS_DSC_RC_RANGE_PARAM6_range_bpg_offset13_END    (5)
#define SOC_DSS_DSC_RC_RANGE_PARAM6_range_max_qp13_START      (6)
#define SOC_DSS_DSC_RC_RANGE_PARAM6_range_max_qp13_END        (10)
#define SOC_DSS_DSC_RC_RANGE_PARAM6_range_min_qp13_START      (11)
#define SOC_DSS_DSC_RC_RANGE_PARAM6_range_min_qp13_END        (15)
#define SOC_DSS_DSC_RC_RANGE_PARAM6_range_bpg_offset12_START  (16)
#define SOC_DSS_DSC_RC_RANGE_PARAM6_range_bpg_offset12_END    (21)
#define SOC_DSS_DSC_RC_RANGE_PARAM6_range_max_qp12_START      (22)
#define SOC_DSS_DSC_RC_RANGE_PARAM6_range_max_qp12_END        (26)
#define SOC_DSS_DSC_RC_RANGE_PARAM6_range_min_qp12_START      (27)
#define SOC_DSS_DSC_RC_RANGE_PARAM6_range_min_qp12_END        (31)


/*****************************************************************************
 结构名    : SOC_DSS_DSC_RC_RANGE_PARAM7_UNION
 结构说明  : RC_RANGE_PARAM7 寄存器结构定义。地址偏移量:0x0068，初值:0x6BF40000，宽度:32
 寄存器说明: RC_RANGE参数寄存器7
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved           : 16; /* bit[0-15] : 保留 */
        unsigned int  range_bpg_offset14 : 6;  /* bit[16-21]: long-rc range为14时的range参数
                                                              有符号数 */
        unsigned int  range_max_qp14     : 5;  /* bit[22-26]: long-rc range为14时的range参数
                                                              无符号数 */
        unsigned int  range_min_qp14     : 5;  /* bit[27-31]: long-rc range为14时的range参数
                                                              无符号数 */
    } reg;
} SOC_DSS_DSC_RC_RANGE_PARAM7_UNION;
#endif
#define SOC_DSS_DSC_RC_RANGE_PARAM7_range_bpg_offset14_START  (16)
#define SOC_DSS_DSC_RC_RANGE_PARAM7_range_bpg_offset14_END    (21)
#define SOC_DSS_DSC_RC_RANGE_PARAM7_range_max_qp14_START      (22)
#define SOC_DSS_DSC_RC_RANGE_PARAM7_range_max_qp14_END        (26)
#define SOC_DSS_DSC_RC_RANGE_PARAM7_range_min_qp14_START      (27)
#define SOC_DSS_DSC_RC_RANGE_PARAM7_range_min_qp14_END        (31)


/*****************************************************************************
 结构名    : SOC_DSS_DSC_ADJUSTMENT_BITS_UNION
 结构说明  : ADJUSTMENT_BITS 寄存器结构定义。地址偏移量:0x006C，初值:0x00000000，宽度:32
 寄存器说明: ADJUSTMENT_BITS寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  adjustment_bits : 4;  /* bit[0-3] : ADJUSTMENT_BITS寄存器
                                                          adjustment_bits使得编码后的一行的bit数为byte的整数倍
                                                          配置值 = 
                                                          （8-(bits_per_pixel * slice_hsize) % 8）% 8
                                                          取值范围为0-7 */
        unsigned int  reserved        : 28; /* bit[4-31]: 保留 */
    } reg;
} SOC_DSS_DSC_ADJUSTMENT_BITS_UNION;
#endif
#define SOC_DSS_DSC_ADJUSTMENT_BITS_adjustment_bits_START  (0)
#define SOC_DSS_DSC_ADJUSTMENT_BITS_adjustment_bits_END    (3)


/*****************************************************************************
 结构名    : SOC_DSS_DSC_BITS_PER_GRP_UNION
 结构说明  : BITS_PER_GRP 寄存器结构定义。地址偏移量:0x0070，初值:0x00001518，宽度:32
 寄存器说明: group编码尺寸寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bits_per_grp     : 6;  /* bit[0-5]  : 每个group编码后的bit数
                                                            配置值=ceil（bits_per_pixel * 3） */
        unsigned int  reserved_0       : 2;  /* bit[6-7]  : 保留 */
        unsigned int  adj_bits_per_grp : 6;  /* bit[8-13] : 配置值=bits_per_pixel * 3 - 3 */
        unsigned int  reserved_1       : 18; /* bit[14-31]: 保留 */
    } reg;
} SOC_DSS_DSC_BITS_PER_GRP_UNION;
#endif
#define SOC_DSS_DSC_BITS_PER_GRP_bits_per_grp_START      (0)
#define SOC_DSS_DSC_BITS_PER_GRP_bits_per_grp_END        (5)
#define SOC_DSS_DSC_BITS_PER_GRP_adj_bits_per_grp_START  (8)
#define SOC_DSS_DSC_BITS_PER_GRP_adj_bits_per_grp_END    (13)


/*****************************************************************************
 结构名    : SOC_DSS_DSC_MULTI_SLICE_CTL_UNION
 结构说明  : MULTI_SLICE_CTL 寄存器结构定义。地址偏移量:0x0074，初值:0x00000000，宽度:32
 寄存器说明: multi_slice控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  slices_per_line  : 2;  /* bit[0-1]  : 每行的slice数目
                                                            2'b00: 1 slice per line
                                                            2'b01: 2 slices per line
                                                            2'b1x: reserved
                                                            当pic_width > slice_width时，slices_per_line=1；否则slices_per_line=0 */
        unsigned int  reserved         : 14; /* bit[2-15] : 保留 */
        unsigned int  pic_line_grp_num : 16; /* bit[16-31]: pic_line_grp_num = (slice_width+3)/3*slices_per_line-1
                                                            注：此处slice_width为实际值减1 */
    } reg;
} SOC_DSS_DSC_MULTI_SLICE_CTL_UNION;
#endif
#define SOC_DSS_DSC_MULTI_SLICE_CTL_slices_per_line_START   (0)
#define SOC_DSS_DSC_MULTI_SLICE_CTL_slices_per_line_END     (1)
#define SOC_DSS_DSC_MULTI_SLICE_CTL_pic_line_grp_num_START  (16)
#define SOC_DSS_DSC_MULTI_SLICE_CTL_pic_line_grp_num_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_DSC_DSC_OUT_CTRL_UNION
 结构说明  : DSC_OUT_CTRL 寄存器结构定义。地址偏移量:0x0078，初值:0x00000000，宽度:32
 寄存器说明: DSC输出控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsc_out_mode : 1;  /* bit[0]   : 0: 24bit输出模式；
                                                       1: 16bit输出模式。
                                                       24bit输出模式时，DSC输出的24bit全部有效。
                                                       16bit输出模式时，DSC输出的24bit中低16bit有效。
                                                       当chunk_size%3==0时，dsc_out_mode=0；否则dsc_out_mode=1. */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_DSC_DSC_OUT_CTRL_UNION;
#endif
#define SOC_DSS_DSC_DSC_OUT_CTRL_dsc_out_mode_START  (0)
#define SOC_DSS_DSC_DSC_OUT_CTRL_dsc_out_mode_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_DSC_DSC_CLK_SEL_UNION
 结构说明  : DSC_CLK_SEL 寄存器结构定义。地址偏移量:0x007C，初值:0xFFFFFFFF，宽度:32
 寄存器说明: 一级模块时钟选择信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsc_clk_sel : 32; /* bit[0-31]: 各一级模块的时钟选择信号，
                                                      1：表示强制打开时钟。
                                                      0：表示需要根据软件和硬件的时钟使能来开启或关闭时钟
                                                      [31:3]: 保留
                                                      [2]: DSC_IF时钟控制寄存器
                                                      [1]: DSC1时钟控制寄存器；
                                                      [0]: DSC0时钟控制寄存器； */
    } reg;
} SOC_DSS_DSC_DSC_CLK_SEL_UNION;
#endif
#define SOC_DSS_DSC_DSC_CLK_SEL_dsc_clk_sel_START  (0)
#define SOC_DSS_DSC_DSC_CLK_SEL_dsc_clk_sel_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_DSC_DSC_CLK_EN_UNION
 结构说明  : DSC_CLK_EN 寄存器结构定义。地址偏移量:0x0080，初值:0xFFFFFFFF，宽度:32
 寄存器说明: 一级模块时钟使能信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsc_clk_en : 32; /* bit[0-31]: 各一级模块的软件时钟使能信号
                                                     1：表示软件时钟使能有效，允许硬件开钟
                                                     0：表示软件时钟使能无效，禁止硬件开钟
                                                     [31:3]: 保留
                                                     [2]: DSC_IF时钟控制寄存器
                                                     [1]: DSC1时钟控制寄存器；
                                                     [0]: DSC0时钟控制寄存器； */
    } reg;
} SOC_DSS_DSC_DSC_CLK_EN_UNION;
#endif
#define SOC_DSS_DSC_DSC_CLK_EN_dsc_clk_en_START  (0)
#define SOC_DSS_DSC_DSC_CLK_EN_dsc_clk_en_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_DSC_DSC_MEM_CTRL_UNION
 结构说明  : DSC_MEM_CTRL 寄存器结构定义。地址偏移量:0x0084，初值:0x00000000，宽度:32
 寄存器说明: DSC memory低功耗控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsc_mem_ctrl_0 : 4;  /* bit[0-3]  : DSC0 memory低功耗控制寄存器
                                                          [3] mem_ctrl_auto_en , 自动模式、软件配置模式选择,0自动模式，1软件配置模式 
                                                          [2]: 软件配置模式下有效，为1表示进入Shut Down模式
                                                          [1]: 软件配置模式下有效，为1表示进入Deep Sleep模式
                                                          [0]: 软件配置模式下有效，为1表示进入Sleep模式 */
        unsigned int  dsc_mem_ctrl_1 : 4;  /* bit[4-7]  : DSC1 memory低功耗控制寄存器，各比特含义同[3:0] */
        unsigned int  dsc_mem_ctrl_2 : 4;  /* bit[8-11] : DSC_IF line buffer低功耗控制寄存器，各比特含义同[3:0] */
        unsigned int  dsc_mem_ctrl_3 : 4;  /* bit[12-15]: 保留 */
        unsigned int  dsc_mem_ctrl_4 : 4;  /* bit[16-19]: 保留 */
        unsigned int  dsc_mem_ctrl_5 : 4;  /* bit[20-23]: 保留 */
        unsigned int  dsc_mem_ctrl_6 : 4;  /* bit[24-27]: 保留 */
        unsigned int  dsc_mem_ctrl_7 : 4;  /* bit[28-31]: 保留 */
    } reg;
} SOC_DSS_DSC_DSC_MEM_CTRL_UNION;
#endif
#define SOC_DSS_DSC_DSC_MEM_CTRL_dsc_mem_ctrl_0_START  (0)
#define SOC_DSS_DSC_DSC_MEM_CTRL_dsc_mem_ctrl_0_END    (3)
#define SOC_DSS_DSC_DSC_MEM_CTRL_dsc_mem_ctrl_1_START  (4)
#define SOC_DSS_DSC_DSC_MEM_CTRL_dsc_mem_ctrl_1_END    (7)
#define SOC_DSS_DSC_DSC_MEM_CTRL_dsc_mem_ctrl_2_START  (8)
#define SOC_DSS_DSC_DSC_MEM_CTRL_dsc_mem_ctrl_2_END    (11)
#define SOC_DSS_DSC_DSC_MEM_CTRL_dsc_mem_ctrl_3_START  (12)
#define SOC_DSS_DSC_DSC_MEM_CTRL_dsc_mem_ctrl_3_END    (15)
#define SOC_DSS_DSC_DSC_MEM_CTRL_dsc_mem_ctrl_4_START  (16)
#define SOC_DSS_DSC_DSC_MEM_CTRL_dsc_mem_ctrl_4_END    (19)
#define SOC_DSS_DSC_DSC_MEM_CTRL_dsc_mem_ctrl_5_START  (20)
#define SOC_DSS_DSC_DSC_MEM_CTRL_dsc_mem_ctrl_5_END    (23)
#define SOC_DSS_DSC_DSC_MEM_CTRL_dsc_mem_ctrl_6_START  (24)
#define SOC_DSS_DSC_DSC_MEM_CTRL_dsc_mem_ctrl_6_END    (27)
#define SOC_DSS_DSC_DSC_MEM_CTRL_dsc_mem_ctrl_7_START  (28)
#define SOC_DSS_DSC_DSC_MEM_CTRL_dsc_mem_ctrl_7_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_DSC_DSC_ST_DATAIN_UNION
 结构说明  : DSC_ST_DATAIN 寄存器结构定义。地址偏移量:0x0088，初值:0x00000000，宽度:32
 寄存器说明: 输入状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  datain_line_cnt : 12; /* bit[0-11] : 输入像素纵向位置状态寄存器 */
        unsigned int  reserved_0      : 4;  /* bit[12-15]: 保留 */
        unsigned int  datain_pix_cnt  : 12; /* bit[16-27]: 输入像素横向位置状态寄存器 */
        unsigned int  reserved_1      : 4;  /* bit[28-31]: 保留 */
    } reg;
} SOC_DSS_DSC_DSC_ST_DATAIN_UNION;
#endif
#define SOC_DSS_DSC_DSC_ST_DATAIN_datain_line_cnt_START  (0)
#define SOC_DSS_DSC_DSC_ST_DATAIN_datain_line_cnt_END    (11)
#define SOC_DSS_DSC_DSC_ST_DATAIN_datain_pix_cnt_START   (16)
#define SOC_DSS_DSC_DSC_ST_DATAIN_datain_pix_cnt_END     (27)


/*****************************************************************************
 结构名    : SOC_DSS_DSC_DSC_ST_DATAOUT_UNION
 结构说明  : DSC_ST_DATAOUT 寄存器结构定义。地址偏移量:0x008C，初值:0x00000000，宽度:32
 寄存器说明: 输出状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dataout_line_cnt : 12; /* bit[0-11] : 输出数据纵向位置状态寄存器 */
        unsigned int  reserved         : 4;  /* bit[12-15]: 保留 */
        unsigned int  dataout_byte_cnt : 16; /* bit[16-31]: 输出byte数状态寄存器 */
    } reg;
} SOC_DSS_DSC_DSC_ST_DATAOUT_UNION;
#endif
#define SOC_DSS_DSC_DSC_ST_DATAOUT_dataout_line_cnt_START  (0)
#define SOC_DSS_DSC_DSC_ST_DATAOUT_dataout_line_cnt_END    (11)
#define SOC_DSS_DSC_DSC_ST_DATAOUT_dataout_byte_cnt_START  (16)
#define SOC_DSS_DSC_DSC_ST_DATAOUT_dataout_byte_cnt_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_DSC_DSC0_ST_SLC_POS_UNION
 结构说明  : DSC0_ST_SLC_POS 寄存器结构定义。地址偏移量:0x0090，初值:0x00000000，宽度:32
 寄存器说明: SLICE位置状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsc0_slice_line_cnt : 12; /* bit[0-11] : dsc0 slice纵向位置状态寄存器
                                                               即dsc0当前输入的像素位于所在slice的纵向位置 */
        unsigned int  reserved_0          : 4;  /* bit[12-15]: 保留 */
        unsigned int  dsc0_slice_pix_cnt  : 12; /* bit[16-27]: dsc0 slice横向位置状态寄存器
                                                               即dsc0当前输入的像素位于所在slice的横向位置 */
        unsigned int  reserved_1          : 4;  /* bit[28-31]: 保留 */
    } reg;
} SOC_DSS_DSC_DSC0_ST_SLC_POS_UNION;
#endif
#define SOC_DSS_DSC_DSC0_ST_SLC_POS_dsc0_slice_line_cnt_START  (0)
#define SOC_DSS_DSC_DSC0_ST_SLC_POS_dsc0_slice_line_cnt_END    (11)
#define SOC_DSS_DSC_DSC0_ST_SLC_POS_dsc0_slice_pix_cnt_START   (16)
#define SOC_DSS_DSC_DSC0_ST_SLC_POS_dsc0_slice_pix_cnt_END     (27)


/*****************************************************************************
 结构名    : SOC_DSS_DSC_DSC1_ST_SLC_POS_UNION
 结构说明  : DSC1_ST_SLC_POS 寄存器结构定义。地址偏移量:0x0094，初值:0x00000000，宽度:32
 寄存器说明: SLICE位置状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsc1_slice_line_cnt : 12; /* bit[0-11] : dsc1 slice纵向位置状态寄存器
                                                               即dsc1当前输入的像素位于所在slice的纵向位置 */
        unsigned int  reserved_0          : 4;  /* bit[12-15]: 保留 */
        unsigned int  dsc1_slice_pix_cnt  : 12; /* bit[16-27]: dsc1 slice横向位置状态寄存器
                                                               即dsc1当前输入的像素位于所在slice的横向位置 */
        unsigned int  reserved_1          : 4;  /* bit[28-31]: 保留 */
    } reg;
} SOC_DSS_DSC_DSC1_ST_SLC_POS_UNION;
#endif
#define SOC_DSS_DSC_DSC1_ST_SLC_POS_dsc1_slice_line_cnt_START  (0)
#define SOC_DSS_DSC_DSC1_ST_SLC_POS_dsc1_slice_line_cnt_END    (11)
#define SOC_DSS_DSC_DSC1_ST_SLC_POS_dsc1_slice_pix_cnt_START   (16)
#define SOC_DSS_DSC_DSC1_ST_SLC_POS_dsc1_slice_pix_cnt_END     (27)


/*****************************************************************************
 结构名    : SOC_DSS_DSC_DSC0_ST_PIC_POS_UNION
 结构说明  : DSC0_ST_PIC_POS 寄存器结构定义。地址偏移量:0x0098，初值:0x00000000，宽度:32
 寄存器说明: PICTURE位置状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsc0_pic_line_cnt : 12; /* bit[0-11] : dsc0 picturee纵向位置状态寄存器
                                                             即dsc0当前输入的像素位于整帧的横向位置 */
        unsigned int  reserved_0        : 4;  /* bit[12-15]: 保留 */
        unsigned int  dsc0_pic_pix_cnt  : 12; /* bit[16-27]: dsc0 picture横向位置状态寄存器
                                                             即dsc0当前输入的像素位于整帧的横向位置 */
        unsigned int  reserved_1        : 4;  /* bit[28-31]: 保留 */
    } reg;
} SOC_DSS_DSC_DSC0_ST_PIC_POS_UNION;
#endif
#define SOC_DSS_DSC_DSC0_ST_PIC_POS_dsc0_pic_line_cnt_START  (0)
#define SOC_DSS_DSC_DSC0_ST_PIC_POS_dsc0_pic_line_cnt_END    (11)
#define SOC_DSS_DSC_DSC0_ST_PIC_POS_dsc0_pic_pix_cnt_START   (16)
#define SOC_DSS_DSC_DSC0_ST_PIC_POS_dsc0_pic_pix_cnt_END     (27)


/*****************************************************************************
 结构名    : SOC_DSS_DSC_DSC1_ST_PIC_POS_UNION
 结构说明  : DSC1_ST_PIC_POS 寄存器结构定义。地址偏移量:0x009C，初值:0x00000000，宽度:32
 寄存器说明: PICTURE位置状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsc1_pic_line_cnt : 12; /* bit[0-11] : dsc1 picturee纵向位置状态寄存器
                                                             即dsc0当前输入的像素位于整帧的横向位置 */
        unsigned int  reserved_0        : 4;  /* bit[12-15]: 保留 */
        unsigned int  dsc1_pic_pix_cnt  : 12; /* bit[16-27]: dsc1 picture横向位置状态寄存器
                                                             即dsc0当前输入的像素位于整帧的横向位置 */
        unsigned int  reserved_1        : 4;  /* bit[28-31]: 保留 */
    } reg;
} SOC_DSS_DSC_DSC1_ST_PIC_POS_UNION;
#endif
#define SOC_DSS_DSC_DSC1_ST_PIC_POS_dsc1_pic_line_cnt_START  (0)
#define SOC_DSS_DSC_DSC1_ST_PIC_POS_dsc1_pic_line_cnt_END    (11)
#define SOC_DSS_DSC_DSC1_ST_PIC_POS_dsc1_pic_pix_cnt_START   (16)
#define SOC_DSS_DSC_DSC1_ST_PIC_POS_dsc1_pic_pix_cnt_END     (27)


/*****************************************************************************
 结构名    : SOC_DSS_DSC_DSC0_ST_FIFO_UNION
 结构说明  : DSC0_ST_FIFO 寄存器结构定义。地址偏移量:0x00A0，初值:0x00002AAA，宽度:32
 寄存器说明: FIFO空满状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsc0_flatff_full     : 1;  /* bit[0]    : dsc0 flat检测fifo满指示状态寄存器 */
        unsigned int  dsc0_flatff_empty    : 1;  /* bit[1]    : dsc0 flat检测fifo空指示状态寄存器 */
        unsigned int  dsc0_blncff0_full    : 1;  /* bit[2]    : dsc0 Y分量balance fifo0满指示寄存器 */
        unsigned int  dsc0_blncff0_empty   : 1;  /* bit[3]    : dsc0 Y分量balance fifo0空指示寄存器 */
        unsigned int  dsc0_blncff1_full    : 1;  /* bit[4]    : dsc0 Y分量balance fifo1满指示寄存器 */
        unsigned int  dsc0_blncff1_empty   : 1;  /* bit[5]    : dsc0 Y分量balance fifo1空指示寄存器 */
        unsigned int  dsc0_sesizeff0_full  : 1;  /* bit[6]    : dsc0 Y分量syntax element size fifo0空指示寄存器 */
        unsigned int  dsc0_sesizeff0_empty : 1;  /* bit[7]    : dsc0 Y分量syntax element size fifo0满指示寄存器 */
        unsigned int  dsc0_sesizeff1_full  : 1;  /* bit[8]    : dsc0 Y分量syntax element size fifo1空指示寄存器 */
        unsigned int  dsc0_sesizeff1_empty : 1;  /* bit[9]    : dsc0 Y分量syntax element size fifo1满指示寄存器 */
        unsigned int  dsc0_rcbuf0_full     : 1;  /* bit[10]   : dsc0 rc buffer0即将满指示寄存器 */
        unsigned int  dsc0_rcbuf0_empty    : 1;  /* bit[11]   : dsc0 rc buffer0空指示寄存器 */
        unsigned int  dsc0_rcbuf1_full     : 1;  /* bit[12]   : dsc0 rc buffer1即将满指示寄存器 */
        unsigned int  dsc0_rcbuf1_empty    : 1;  /* bit[13]   : dsc0 rc buffer1空指示寄存器 */
        unsigned int  reserved             : 18; /* bit[14-31]: 保留 */
    } reg;
} SOC_DSS_DSC_DSC0_ST_FIFO_UNION;
#endif
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_flatff_full_START      (0)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_flatff_full_END        (0)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_flatff_empty_START     (1)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_flatff_empty_END       (1)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_blncff0_full_START     (2)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_blncff0_full_END       (2)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_blncff0_empty_START    (3)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_blncff0_empty_END      (3)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_blncff1_full_START     (4)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_blncff1_full_END       (4)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_blncff1_empty_START    (5)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_blncff1_empty_END      (5)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_sesizeff0_full_START   (6)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_sesizeff0_full_END     (6)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_sesizeff0_empty_START  (7)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_sesizeff0_empty_END    (7)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_sesizeff1_full_START   (8)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_sesizeff1_full_END     (8)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_sesizeff1_empty_START  (9)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_sesizeff1_empty_END    (9)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_rcbuf0_full_START      (10)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_rcbuf0_full_END        (10)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_rcbuf0_empty_START     (11)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_rcbuf0_empty_END       (11)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_rcbuf1_full_START      (12)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_rcbuf1_full_END        (12)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_rcbuf1_empty_START     (13)
#define SOC_DSS_DSC_DSC0_ST_FIFO_dsc0_rcbuf1_empty_END       (13)


/*****************************************************************************
 结构名    : SOC_DSS_DSC_DSC1_ST_FIFO_UNION
 结构说明  : DSC1_ST_FIFO 寄存器结构定义。地址偏移量:0x00A4，初值:0x00002AAA，宽度:32
 寄存器说明: FIFO空满状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsc1_flatff_full     : 1;  /* bit[0]    : dsc1 flat检测fifo满指示状态寄存器 */
        unsigned int  dsc1_flatff_empty    : 1;  /* bit[1]    : dsc1 flat检测fifo空指示状态寄存器 */
        unsigned int  dsc1_blncff0_full    : 1;  /* bit[2]    : dsc1 Y分量balance fifo0满指示寄存器 */
        unsigned int  dsc1_blncff0_empty   : 1;  /* bit[3]    : dsc1 Y分量balance fifo0空指示寄存器 */
        unsigned int  dsc1_blncff1_full    : 1;  /* bit[4]    : dsc1 Y分量balance fifo1满指示寄存器 */
        unsigned int  dsc1_blncff1_empty   : 1;  /* bit[5]    : dsc1 Y分量balance fifo1空指示寄存器 */
        unsigned int  dsc1_sesizeff0_full  : 1;  /* bit[6]    : dsc1 Y分量syntax element size fifo0空指示寄存器 */
        unsigned int  dsc1_sesizeff0_empty : 1;  /* bit[7]    : dsc1 Y分量syntax element size fifo0满指示寄存器 */
        unsigned int  dsc1_sesizeff1_full  : 1;  /* bit[8]    : dsc1 Y分量syntax element size fifo1空指示寄存器 */
        unsigned int  dsc1_sesizeff1_empty : 1;  /* bit[9]    : dsc1 Y分量syntax element size fifo1满指示寄存器 */
        unsigned int  dsc1_rcbuf0_full     : 1;  /* bit[10]   : dsc1 rc buffer0即将满指示寄存器 */
        unsigned int  dsc1_rcbuf0_empty    : 1;  /* bit[11]   : dsc1 rc buffer0空指示寄存器 */
        unsigned int  dsc1_rcbuf1_full     : 1;  /* bit[12]   : dsc1 rc buffer1即将满指示寄存器 */
        unsigned int  dsc1_rcbuf1_empty    : 1;  /* bit[13]   : dsc1 rc buffer1空指示寄存器 */
        unsigned int  reserved             : 18; /* bit[14-31]: 保留 */
    } reg;
} SOC_DSS_DSC_DSC1_ST_FIFO_UNION;
#endif
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_flatff_full_START      (0)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_flatff_full_END        (0)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_flatff_empty_START     (1)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_flatff_empty_END       (1)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_blncff0_full_START     (2)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_blncff0_full_END       (2)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_blncff0_empty_START    (3)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_blncff0_empty_END      (3)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_blncff1_full_START     (4)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_blncff1_full_END       (4)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_blncff1_empty_START    (5)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_blncff1_empty_END      (5)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_sesizeff0_full_START   (6)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_sesizeff0_full_END     (6)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_sesizeff0_empty_START  (7)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_sesizeff0_empty_END    (7)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_sesizeff1_full_START   (8)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_sesizeff1_full_END     (8)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_sesizeff1_empty_START  (9)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_sesizeff1_empty_END    (9)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_rcbuf0_full_START      (10)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_rcbuf0_full_END        (10)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_rcbuf0_empty_START     (11)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_rcbuf0_empty_END       (11)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_rcbuf1_full_START      (12)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_rcbuf1_full_END        (12)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_rcbuf1_empty_START     (13)
#define SOC_DSS_DSC_DSC1_ST_FIFO_dsc1_rcbuf1_empty_END       (13)


/*****************************************************************************
 结构名    : SOC_DSS_DSC_DSC0_ST_LINEBUF_UNION
 结构说明  : DSC0_ST_LINEBUF 寄存器结构定义。地址偏移量:0x00A8，初值:0x00220000，宽度:32
 寄存器说明: LINEBUF状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsc0_addr_linebuf  : 10; /* bit[0-9]  : dsc0 line buffer 地址状态寄存器 */
        unsigned int  reserved_0         : 6;  /* bit[10-15]: 保留 */
        unsigned int  dsc0_infifo_full   : 1;  /* bit[16]   : dsc0 重建像素读入缓存fifo 满状态急促亲 */
        unsigned int  dsc0_infifo_empty  : 1;  /* bit[17]   : dsc0 重建像素读入缓存fifo 空状态急促亲 */
        unsigned int  dsc0_infifo_uflow  : 1;  /* bit[18]   : dsc0 重建像素读入缓存fifo underflow状态急促亲 */
        unsigned int  dsc0_infifo_oflow  : 1;  /* bit[19]   : dsc0 重建像素读入缓存fifo overflow状态急促亲 */
        unsigned int  dsc0_outfifo_full  : 1;  /* bit[20]   : dsc0 重建像素写出缓存fifo 满状态急促亲 */
        unsigned int  dsc0_outfifo_empty : 1;  /* bit[21]   : dsc0 重建像素写出缓存fifo 空状态急促亲 */
        unsigned int  dsc0_outfifo_uflow : 1;  /* bit[22]   : dsc0 重建像素写出缓存fifo underflow状态急促亲 */
        unsigned int  dsc0_outfifo_oflow : 1;  /* bit[23]   : dsc0 重建像素写出缓存fifo overflow状态急促亲 */
        unsigned int  reserved_1         : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_DSC_DSC0_ST_LINEBUF_UNION;
#endif
#define SOC_DSS_DSC_DSC0_ST_LINEBUF_dsc0_addr_linebuf_START   (0)
#define SOC_DSS_DSC_DSC0_ST_LINEBUF_dsc0_addr_linebuf_END     (9)
#define SOC_DSS_DSC_DSC0_ST_LINEBUF_dsc0_infifo_full_START    (16)
#define SOC_DSS_DSC_DSC0_ST_LINEBUF_dsc0_infifo_full_END      (16)
#define SOC_DSS_DSC_DSC0_ST_LINEBUF_dsc0_infifo_empty_START   (17)
#define SOC_DSS_DSC_DSC0_ST_LINEBUF_dsc0_infifo_empty_END     (17)
#define SOC_DSS_DSC_DSC0_ST_LINEBUF_dsc0_infifo_uflow_START   (18)
#define SOC_DSS_DSC_DSC0_ST_LINEBUF_dsc0_infifo_uflow_END     (18)
#define SOC_DSS_DSC_DSC0_ST_LINEBUF_dsc0_infifo_oflow_START   (19)
#define SOC_DSS_DSC_DSC0_ST_LINEBUF_dsc0_infifo_oflow_END     (19)
#define SOC_DSS_DSC_DSC0_ST_LINEBUF_dsc0_outfifo_full_START   (20)
#define SOC_DSS_DSC_DSC0_ST_LINEBUF_dsc0_outfifo_full_END     (20)
#define SOC_DSS_DSC_DSC0_ST_LINEBUF_dsc0_outfifo_empty_START  (21)
#define SOC_DSS_DSC_DSC0_ST_LINEBUF_dsc0_outfifo_empty_END    (21)
#define SOC_DSS_DSC_DSC0_ST_LINEBUF_dsc0_outfifo_uflow_START  (22)
#define SOC_DSS_DSC_DSC0_ST_LINEBUF_dsc0_outfifo_uflow_END    (22)
#define SOC_DSS_DSC_DSC0_ST_LINEBUF_dsc0_outfifo_oflow_START  (23)
#define SOC_DSS_DSC_DSC0_ST_LINEBUF_dsc0_outfifo_oflow_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_DSC_DSC1_ST_LINEBUF_UNION
 结构说明  : DSC1_ST_LINEBUF 寄存器结构定义。地址偏移量:0x00AC，初值:0x00220000，宽度:32
 寄存器说明: LINEBUF状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsc1_addr_linebuf  : 10; /* bit[0-9]  : dsc1 line buffer 地址状态寄存器 */
        unsigned int  reserved_0         : 6;  /* bit[10-15]: 保留 */
        unsigned int  dsc1_infifo_full   : 1;  /* bit[16]   : dsc1 重建像素读入缓存fifo 满状态急促亲 */
        unsigned int  dsc1_infifo_empty  : 1;  /* bit[17]   : dsc1 重建像素读入缓存fifo 空状态急促亲 */
        unsigned int  dsc1_infifo_uflow  : 1;  /* bit[18]   : dsc1 重建像素读入缓存fifo underflow状态急促亲 */
        unsigned int  dsc1_infifo_oflow  : 1;  /* bit[19]   : dsc1 重建像素读入缓存fifo overflow状态急促亲 */
        unsigned int  dsc1_outfifo_full  : 1;  /* bit[20]   : dsc1 重建像素写出缓存fifo 满状态急促亲 */
        unsigned int  dsc1_outfifo_empty : 1;  /* bit[21]   : dsc1 重建像素写出缓存fifo 空状态急促亲 */
        unsigned int  dsc1_outfifo_uflow : 1;  /* bit[22]   : dsc1 重建像素写出缓存fifo underflow状态急促亲 */
        unsigned int  dsc1_outfifo_oflow : 1;  /* bit[23]   : dsc1 重建像素写出缓存fifo overflow状态急促亲 */
        unsigned int  reserved_1         : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_DSC_DSC1_ST_LINEBUF_UNION;
#endif
#define SOC_DSS_DSC_DSC1_ST_LINEBUF_dsc1_addr_linebuf_START   (0)
#define SOC_DSS_DSC_DSC1_ST_LINEBUF_dsc1_addr_linebuf_END     (9)
#define SOC_DSS_DSC_DSC1_ST_LINEBUF_dsc1_infifo_full_START    (16)
#define SOC_DSS_DSC_DSC1_ST_LINEBUF_dsc1_infifo_full_END      (16)
#define SOC_DSS_DSC_DSC1_ST_LINEBUF_dsc1_infifo_empty_START   (17)
#define SOC_DSS_DSC_DSC1_ST_LINEBUF_dsc1_infifo_empty_END     (17)
#define SOC_DSS_DSC_DSC1_ST_LINEBUF_dsc1_infifo_uflow_START   (18)
#define SOC_DSS_DSC_DSC1_ST_LINEBUF_dsc1_infifo_uflow_END     (18)
#define SOC_DSS_DSC_DSC1_ST_LINEBUF_dsc1_infifo_oflow_START   (19)
#define SOC_DSS_DSC_DSC1_ST_LINEBUF_dsc1_infifo_oflow_END     (19)
#define SOC_DSS_DSC_DSC1_ST_LINEBUF_dsc1_outfifo_full_START   (20)
#define SOC_DSS_DSC_DSC1_ST_LINEBUF_dsc1_outfifo_full_END     (20)
#define SOC_DSS_DSC_DSC1_ST_LINEBUF_dsc1_outfifo_empty_START  (21)
#define SOC_DSS_DSC_DSC1_ST_LINEBUF_dsc1_outfifo_empty_END    (21)
#define SOC_DSS_DSC_DSC1_ST_LINEBUF_dsc1_outfifo_uflow_START  (22)
#define SOC_DSS_DSC_DSC1_ST_LINEBUF_dsc1_outfifo_uflow_END    (22)
#define SOC_DSS_DSC_DSC1_ST_LINEBUF_dsc1_outfifo_oflow_START  (23)
#define SOC_DSS_DSC_DSC1_ST_LINEBUF_dsc1_outfifo_oflow_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_DSC_DSC_ST_ITFC_UNION
 结构说明  : DSC_ST_ITFC 寄存器结构定义。地址偏移量:0x00B0，初值:0x0000000A，宽度:32
 寄存器说明: 接口状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsc1_pre_drdy  : 1;  /* bit[0]    : dsc1 前级ready-need接口状态寄存器 */
        unsigned int  dsc1_pre_dneed : 1;  /* bit[1]    : dsc1 前级ready-need接口状态寄存器 */
        unsigned int  dsc1_dv2pred   : 1;  /* bit[2]    : dsc1 前级ready-need接口状态寄存器 */
        unsigned int  dsc1_nxt_dneed : 1;  /* bit[3]    : dsc1 后级ready-need接口状态寄存器 */
        unsigned int  dsc1_nxt_drdy  : 1;  /* bit[4]    : dsc1 后级ready-need接口状态寄存器 */
        unsigned int  dsc0_pre_drdy  : 1;  /* bit[5]    : dsc0 前级ready-need接口状态寄存器 */
        unsigned int  dsc0_pre_dneed : 1;  /* bit[6]    : dsc0 前级ready-need接口状态寄存器 */
        unsigned int  dsc0_dv2pred   : 1;  /* bit[7]    : dsc0 前级ready-need接口状态寄存器 */
        unsigned int  dsc0_nxt_dneed : 1;  /* bit[8]    : dsc0 后级ready-need接口状态寄存器 */
        unsigned int  dsc0_nxt_drdy  : 1;  /* bit[9]    : dsc0 后级ready-need接口状态寄存器 */
        unsigned int  reserved       : 22; /* bit[10-31]: 保留 */
    } reg;
} SOC_DSS_DSC_DSC_ST_ITFC_UNION;
#endif
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc1_pre_drdy_START   (0)
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc1_pre_drdy_END     (0)
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc1_pre_dneed_START  (1)
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc1_pre_dneed_END    (1)
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc1_dv2pred_START    (2)
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc1_dv2pred_END      (2)
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc1_nxt_dneed_START  (3)
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc1_nxt_dneed_END    (3)
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc1_nxt_drdy_START   (4)
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc1_nxt_drdy_END     (4)
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc0_pre_drdy_START   (5)
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc0_pre_drdy_END     (5)
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc0_pre_dneed_START  (6)
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc0_pre_dneed_END    (6)
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc0_dv2pred_START    (7)
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc0_dv2pred_END      (7)
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc0_nxt_dneed_START  (8)
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc0_nxt_dneed_END    (8)
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc0_nxt_drdy_START   (9)
#define SOC_DSS_DSC_DSC_ST_ITFC_dsc0_nxt_drdy_END     (9)


/*****************************************************************************
 结构名    : SOC_DSS_DSC_DSC_RD_SHADOW_SEL_UNION
 结构说明  : DSC_RD_SHADOW_SEL 寄存器结构定义。地址偏移量:0x00B4，初值:0x00000000，宽度:32
 寄存器说明: 读寄存器选择信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsc_rd_shadow : 1;  /* bit[0]   : 1'b0 :读工作寄存器
                                                        1'b1 :读影子寄存器 */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_DSC_DSC_RD_SHADOW_SEL_UNION;
#endif
#define SOC_DSS_DSC_DSC_RD_SHADOW_SEL_dsc_rd_shadow_START  (0)
#define SOC_DSS_DSC_DSC_RD_SHADOW_SEL_dsc_rd_shadow_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_DSC_DSC_REG_DEFAULT_UNION
 结构说明  : DSC_REG_DEFAULT 寄存器结构定义。地址偏移量:0x00B8，初值:0x00000000，宽度:32
 寄存器说明: 模块影子寄存器恢复到默认值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsc_reg_default : 1;  /* bit[0]   : 向此寄存器写1，所有影子寄存器恢复到复位值。 */
        unsigned int  reserved        : 31; /* bit[1-31]:  */
    } reg;
} SOC_DSS_DSC_DSC_REG_DEFAULT_UNION;
#endif
#define SOC_DSS_DSC_DSC_REG_DEFAULT_dsc_reg_default_START  (0)
#define SOC_DSS_DSC_DSC_REG_DEFAULT_dsc_reg_default_END    (0)






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

#endif /* end of soc_dss_dsc_interface.h */
