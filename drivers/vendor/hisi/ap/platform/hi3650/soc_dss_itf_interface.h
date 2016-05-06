/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_dss_itf_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:20:09
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_DSS_ITF.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_DSS_ITF_INTERFACE_H__
#define __SOC_DSS_ITF_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) reg_ITF
 ****************************************************************************/
/* 寄存器说明：LDI-DPI0水平扫描控制寄存器0
   位域定义UNION结构:  SOC_DSS_ITF_LDI_DPI0_HRZ_CTRL0_UNION */
#define SOC_DSS_ITF_LDI_DPI0_HRZ_CTRL0_ADDR(base)     ((base) + (0x0000))

/* 寄存器说明：LDI-DPI0水平扫描寄存器1
   位域定义UNION结构:  SOC_DSS_ITF_LDI_DPI0_HRZ_CTRL1_UNION */
#define SOC_DSS_ITF_LDI_DPI0_HRZ_CTRL1_ADDR(base)     ((base) + (0x0004))

/* 寄存器说明：LDI-DPI0水平扫描寄存器2
   位域定义UNION结构:  SOC_DSS_ITF_LDI_DPI0_HRZ_CTRL2_UNION */
#define SOC_DSS_ITF_LDI_DPI0_HRZ_CTRL2_ADDR(base)     ((base) + (0x0008))

/* 寄存器说明：LDI垂直扫描控制寄存器0
   位域定义UNION结构:  SOC_DSS_ITF_LDI_VRT_CTRL0_UNION */
#define SOC_DSS_ITF_LDI_VRT_CTRL0_ADDR(base)          ((base) + (0x000C))

/* 寄存器说明：LDI垂直扫描控制寄存器1
   位域定义UNION结构:  SOC_DSS_ITF_LDI_VRT_CTRL1_UNION */
#define SOC_DSS_ITF_LDI_VRT_CTRL1_ADDR(base)          ((base) + (0x0010))

/* 寄存器说明：LDI垂直扫描控制寄存器2
   位域定义UNION结构:  SOC_DSS_ITF_LDI_VRT_CTRL2_UNION */
#define SOC_DSS_ITF_LDI_VRT_CTRL2_ADDR(base)          ((base) + (0x0014))

/* 寄存器说明：LDI信号极性控制寄存器
   位域定义UNION结构:  SOC_DSS_ITF_LDI_PLR_CTRL_UNION */
#define SOC_DSS_ITF_LDI_PLR_CTRL_ADDR(base)           ((base) + (0x0018))

/* 寄存器说明：LDI信号极性控制寄存器
   位域定义UNION结构:  SOC_DSS_ITF_DSS_SH_MASK_INT_UNION */
#define SOC_DSS_ITF_DSS_SH_MASK_INT_ADDR(base)        ((base) + (0x001C))

/* 寄存器说明：LDI 3D显示控制寄存器
   位域定义UNION结构:  SOC_DSS_ITF_LDI_3D_CTRL_UNION */
#define SOC_DSS_ITF_LDI_3D_CTRL_ADDR(base)            ((base) + (0x0020))

/* 寄存器说明：LDI控制寄存器
            (部分PDP专用)
   位域定义UNION结构:  SOC_DSS_ITF_LDI_CTRL_UNION */
#define SOC_DSS_ITF_LDI_CTRL_ADDR(base)               ((base) + (0x0024))

/* 寄存器说明：LDI工作模式控制寄存器
   位域定义UNION结构:  SOC_DSS_ITF_LDI_WORK_MODE_UNION */
#define SOC_DSS_ITF_LDI_WORK_MODE_ADDR(base)          ((base) + (0x0028))

/* 寄存器说明：3D frame by frame格式下active space阶段DE信号有效控制寄存器
   位域定义UNION结构:  SOC_DSS_ITF_LDI_DE_SPACE_LOW_UNION */
#define SOC_DSS_ITF_LDI_DE_SPACE_LOW_ADDR(base)       ((base) + (0x002C))

/* 寄存器说明：DSI Command(CMD)模式控制寄存器
   位域定义UNION结构:  SOC_DSS_ITF_DSI_CMD_MOD_CTRL_UNION */
#define SOC_DSS_ITF_DSI_CMD_MOD_CTRL_ADDR(base)       ((base) + (0x0030))

/* 寄存器说明：DSI Command(CMD)模式TE控制寄存器
   位域定义UNION结构:  SOC_DSS_ITF_DSI_TE_CTRL_UNION */
#define SOC_DSS_ITF_DSI_TE_CTRL_ADDR(base)            ((base) + (0x0034))

/* 寄存器说明：DSI响应行配置寄存器控制寄存器
   位域定义UNION结构:  SOC_DSS_ITF_DSI_TE_HS_NUM_UNION */
#define SOC_DSS_ITF_DSI_TE_HS_NUM_ADDR(base)          ((base) + (0x0038))

/* 寄存器说明：DSI TE PIN模式检测Hsync宽度控制寄存器
   位域定义UNION结构:  SOC_DSS_ITF_DSI_TE_HS_WD_UNION */
#define SOC_DSS_ITF_DSI_TE_HS_WD_ADDR(base)           ((base) + (0x003C))

/* 寄存器说明：DSI TE PIN模式检测Vsync宽度控制寄存器
   位域定义UNION结构:  SOC_DSS_ITF_DSI_TE_VS_WD_UNION */
#define SOC_DSS_ITF_DSI_TE_VS_WD_ADDR(base)           ((base) + (0x0040))

/* 寄存器说明：LDI帧屏蔽控制寄存器
   位域定义UNION结构:  SOC_DSS_ITF_LDI_FRM_MSK_UNION */
#define SOC_DSS_ITF_LDI_FRM_MSK_ADDR(base)            ((base) + (0x0044))

/* 寄存器说明：LDI帧刷新控制寄存器
   位域定义UNION结构:  SOC_DSS_ITF_LDI_FRM_MSK_UP_UNION */
#define SOC_DSS_ITF_LDI_FRM_MSK_UP_ADDR(base)         ((base) + (0x0048))

/* 寄存器说明：v_inactive屏蔽寄存器
   位域定义UNION结构:  SOC_DSS_ITF_LDI_VINACT_MSK_LEN_UNION */
#define SOC_DSS_ITF_LDI_VINACT_MSK_LEN_ADDR(base)     ((base) + (0x0050))

/* 寄存器说明：LDI选择给CMD输出的中断寄存器
   位域定义UNION结构:  SOC_DSS_ITF_LDI_CMD_EVENT_SEL_UNION */
#define SOC_DSS_ITF_LDI_CMD_EVENT_SEL_ADDR(base)      ((base) + (0x0060))

/* 寄存器说明：SRAM低功耗控制寄存器
   位域定义UNION结构:  SOC_DSS_ITF_SRAM_LP_CTRL_UNION */
#define SOC_DSS_ITF_SRAM_LP_CTRL_ADDR(base)           ((base) + (0x0064))

/* 寄存器说明：读影子寄存器选择信号
   位域定义UNION结构:  SOC_DSS_ITF_ITF_RD_SHADOW_UNION */
#define SOC_DSS_ITF_ITF_RD_SHADOW_ADDR(base)          ((base) + (0x006C))

/* 寄存器说明：LDI-DPI1水平扫描控制寄存器0
   位域定义UNION结构:  SOC_DSS_ITF_LDI_DPI1_HRZ_CTRL0_UNION */
#define SOC_DSS_ITF_LDI_DPI1_HRZ_CTRL0_ADDR(base)     ((base) + (0x00F0))

/* 寄存器说明：LDI-DPI1水平扫描寄存器1
            (双mipi专用)
   位域定义UNION结构:  SOC_DSS_ITF_LDI_DPI1_HRZ_CTRL1_UNION */
#define SOC_DSS_ITF_LDI_DPI1_HRZ_CTRL1_ADDR(base)     ((base) + (0x00F4))

/* 寄存器说明：LDI-DPI1水平扫描寄存器1
            (双mipi专用)
   位域定义UNION结构:  SOC_DSS_ITF_LDI_DPI1_HRZ_CTRL2_UNION */
#define SOC_DSS_ITF_LDI_DPI1_HRZ_CTRL2_ADDR(base)     ((base) + (0x00F8))

/* 寄存器说明：LDI双dpi模式overlap尺寸寄存器
            (双mipi专用)
   位域定义UNION结构:  SOC_DSS_ITF_LDI_OVERLAP_SIZE_UNION */
#define SOC_DSS_ITF_LDI_OVERLAP_SIZE_ADDR(base)       ((base) + (0x00FC))

/* 寄存器说明：MEM低功耗控制寄存器
   位域定义UNION结构:  SOC_DSS_ITF_LDI_MEM_CTRL_UNION */
#define SOC_DSS_ITF_LDI_MEM_CTRL_ADDR(base)           ((base) + (0x0100))

/* 寄存器说明：一级模块时钟选择信号
   位域定义UNION结构:  SOC_DSS_ITF_LDI_CLK_SEL_UNION */
#define SOC_DSS_ITF_LDI_CLK_SEL_ADDR(base)            ((base) + (0x0108))

/* 寄存器说明：一级模块时钟使能信号
   位域定义UNION结构:  SOC_DSS_ITF_LDI_CLK_EN_UNION */
#define SOC_DSS_ITF_LDI_CLK_EN_ADDR(base)             ((base) + (0x010C))

/* 寄存器说明：sram bypass选择信号
   位域定义UNION结构:  SOC_DSS_ITF_LDI_IF_BYPASS_UNION */
#define SOC_DSS_ITF_LDI_IF_BYPASS_ADDR(base)          ((base) + (0x0110))

/* 寄存器说明：模块影子寄存器恢复到默认值
   位域定义UNION结构:  SOC_DSS_ITF_REG_DEFAULT_UNION */
#define SOC_DSS_ITF_REG_DEFAULT_ADDR(base)            ((base) + (0x0114))

/* 寄存器说明：模块影子寄存器恢复到默认值
   位域定义UNION结构:  SOC_DSS_ITF_FRM_VALID_DBG_UNION */
#define SOC_DSS_ITF_FRM_VALID_DBG_ADDR(base)          ((base) + (0x0118))

/* 寄存器说明：LDI的crc校验结果
   位域定义UNION结构:  SOC_DSS_ITF_CRC_DBG_ITF_UNION */
#define SOC_DSS_ITF_CRC_DBG_ITF_ADDR(base)            ((base) + (0x0200))

/* 寄存器说明：LDI的CRC启动使能信号
   位域定义UNION结构:  SOC_DSS_ITF_CRC_ITF_EN_UNION */
#define SOC_DSS_ITF_CRC_ITF_EN_ADDR(base)             ((base) + (0x0204))

/* 寄存器说明：LDI上报的CRC校验的帧数
   位域定义UNION结构:  SOC_DSS_ITF_CRC_ITF_FRM_UNION */
#define SOC_DSS_ITF_CRC_ITF_FRM_ADDR(base)            ((base) + (0x0208))





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
                     (1/1) reg_ITF
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_DSS_ITF_LDI_DPI0_HRZ_CTRL0_UNION
 结构说明  : LDI_DPI0_HRZ_CTRL0 寄存器结构定义。地址偏移量:0x0000，初值:0x00000000，宽度:32
 寄存器说明: LDI-DPI0水平扫描控制寄存器0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dpi0_hfp : 13; /* bit[0-12] : 行前消隐时间配置，写入的是实际值。行后消隐取值范围0~4095;
                                                    行后消隐为一行有效数据结束到水平同步信号ldi_hsync有效这段时间内的像素时钟个数 */
        unsigned int  reserved_0: 3;  /* bit[13-15]:  */
        unsigned int  dpi0_hbp : 13; /* bit[16-28]: 行后消隐时间配置，写入的是实际值。行后消隐的取值范围为0~4095 */
        unsigned int  reserved_1: 3;  /* bit[29-31]:  */
    } reg;
} SOC_DSS_ITF_LDI_DPI0_HRZ_CTRL0_UNION;
#endif
#define SOC_DSS_ITF_LDI_DPI0_HRZ_CTRL0_dpi0_hfp_START  (0)
#define SOC_DSS_ITF_LDI_DPI0_HRZ_CTRL0_dpi0_hfp_END    (12)
#define SOC_DSS_ITF_LDI_DPI0_HRZ_CTRL0_dpi0_hbp_START  (16)
#define SOC_DSS_ITF_LDI_DPI0_HRZ_CTRL0_dpi0_hbp_END    (28)


/*****************************************************************************
 结构名    : SOC_DSS_ITF_LDI_DPI0_HRZ_CTRL1_UNION
 结构说明  : LDI_DPI0_HRZ_CTRL1 寄存器结构定义。地址偏移量:0x0004，初值:0x00000000，宽度:32
 寄存器说明: LDI-DPI0水平扫描寄存器1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dpi0_hsw : 13; /* bit[0-12] : 水平同步脉宽配置，写入的值为实际值减1后的结果。水平同步脉冲的宽度以像素时钟为单位，取值范围为1~4096 */
        unsigned int  reserved : 19; /* bit[13-31]:  */
    } reg;
} SOC_DSS_ITF_LDI_DPI0_HRZ_CTRL1_UNION;
#endif
#define SOC_DSS_ITF_LDI_DPI0_HRZ_CTRL1_dpi0_hsw_START  (0)
#define SOC_DSS_ITF_LDI_DPI0_HRZ_CTRL1_dpi0_hsw_END    (12)


/*****************************************************************************
 结构名    : SOC_DSS_ITF_LDI_DPI0_HRZ_CTRL2_UNION
 结构说明  : LDI_DPI0_HRZ_CTRL2 寄存器结构定义。地址偏移量:0x0008，初值:0x00000000，宽度:32
 寄存器说明: LDI-DPI0水平扫描寄存器2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dpi0_hsize : 13; /* bit[0-12] : 水平尺寸寄存器，写入的值为实际值减1后的结果 */
        unsigned int  reserved   : 19; /* bit[13-31]: 保留 */
    } reg;
} SOC_DSS_ITF_LDI_DPI0_HRZ_CTRL2_UNION;
#endif
#define SOC_DSS_ITF_LDI_DPI0_HRZ_CTRL2_dpi0_hsize_START  (0)
#define SOC_DSS_ITF_LDI_DPI0_HRZ_CTRL2_dpi0_hsize_END    (12)


/*****************************************************************************
 结构名    : SOC_DSS_ITF_LDI_VRT_CTRL0_UNION
 结构说明  : LDI_VRT_CTRL0 寄存器结构定义。地址偏移量:0x000C，初值:0x00000000，宽度:32
 寄存器说明: LDI垂直扫描控制寄存器0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vfp      : 13; /* bit[0-12] : 帧前消隐时间配置，写入的是实际值，取值范围为0~4095;
                                                    帧前消隐为有效数据结束到帧同步信号ldi_vsync有效这段时间内的消隐扫描行数 */
        unsigned int  reserved_0: 3;  /* bit[13-15]:  */
        unsigned int  vbp      : 13; /* bit[16-28]: 帧后消隐时间配置，写入的是实际值，取值范围为0~4095.
                                                    帧后消隐为帧同步信号ldi_vsync无效到一帧有效数据开始这段时间内的消隐扫描行数. */
        unsigned int  reserved_1: 3;  /* bit[29-31]:  */
    } reg;
} SOC_DSS_ITF_LDI_VRT_CTRL0_UNION;
#endif
#define SOC_DSS_ITF_LDI_VRT_CTRL0_vfp_START       (0)
#define SOC_DSS_ITF_LDI_VRT_CTRL0_vfp_END         (12)
#define SOC_DSS_ITF_LDI_VRT_CTRL0_vbp_START       (16)
#define SOC_DSS_ITF_LDI_VRT_CTRL0_vbp_END         (28)


/*****************************************************************************
 结构名    : SOC_DSS_ITF_LDI_VRT_CTRL1_UNION
 结构说明  : LDI_VRT_CTRL1 寄存器结构定义。地址偏移量:0x0010，初值:0x00000000，宽度:32
 寄存器说明: LDI垂直扫描控制寄存器1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vsw      : 13; /* bit[0-12] : 帧同步脉冲宽度配置，写入的值为实际值减1的结果。帧同步脉冲宽度是以扫描行数为单位,取值范围为1~4096 */
        unsigned int  reserved : 19; /* bit[13-31]:  */
    } reg;
} SOC_DSS_ITF_LDI_VRT_CTRL1_UNION;
#endif
#define SOC_DSS_ITF_LDI_VRT_CTRL1_vsw_START       (0)
#define SOC_DSS_ITF_LDI_VRT_CTRL1_vsw_END         (12)


/*****************************************************************************
 结构名    : SOC_DSS_ITF_LDI_VRT_CTRL2_UNION
 结构说明  : LDI_VRT_CTRL2 寄存器结构定义。地址偏移量:0x0014，初值:0x00000000，宽度:32
 寄存器说明: LDI垂直扫描控制寄存器2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vsize    : 13; /* bit[0-12] : 垂直尺寸寄存器，写入的值为实际值减1后的结果 */
        unsigned int  reserved : 19; /* bit[13-31]: 保留 */
    } reg;
} SOC_DSS_ITF_LDI_VRT_CTRL2_UNION;
#endif
#define SOC_DSS_ITF_LDI_VRT_CTRL2_vsize_START     (0)
#define SOC_DSS_ITF_LDI_VRT_CTRL2_vsize_END       (12)


/*****************************************************************************
 结构名    : SOC_DSS_ITF_LDI_PLR_CTRL_UNION
 结构说明  : LDI_PLR_CTRL 寄存器结构定义。地址偏移量:0x0018，初值:0x00000000，宽度:32
 寄存器说明: LDI信号极性控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vsync_plr     : 1;  /* bit[0]   : 帧同步信号ldi_vsync_o有效极性：
                                                        0：ldi_vsync_o高有效；
                                                        1：ldi_hsync_o低有效 */
        unsigned int  hsync_plr     : 1;  /* bit[1]   : 行同步信号ldi_hsync_o有效极性：
                                                        0：ldi_hsync_o高有效；
                                                        1：ldi_hsync_o低有效 */
        unsigned int  pixel_clk_plr : 1;  /* bit[2]   : 像素时钟ldi_pixel_clk有效极性：
                                                        0：ldi_pixel_clk上升沿有效；
                                                        1：ldi_pixel_clk下降沿有效 */
        unsigned int  data_en_plr   : 1;  /* bit[3]   : 数据有效信号ldi_data_en_o有效极性:
                                                        0：ldi_data_en_o高有效；
                                                        1：ldi_data_en_o低有效 */
        unsigned int  reserved      : 28; /* bit[4-31]:  */
    } reg;
} SOC_DSS_ITF_LDI_PLR_CTRL_UNION;
#endif
#define SOC_DSS_ITF_LDI_PLR_CTRL_vsync_plr_START      (0)
#define SOC_DSS_ITF_LDI_PLR_CTRL_vsync_plr_END        (0)
#define SOC_DSS_ITF_LDI_PLR_CTRL_hsync_plr_START      (1)
#define SOC_DSS_ITF_LDI_PLR_CTRL_hsync_plr_END        (1)
#define SOC_DSS_ITF_LDI_PLR_CTRL_pixel_clk_plr_START  (2)
#define SOC_DSS_ITF_LDI_PLR_CTRL_pixel_clk_plr_END    (2)
#define SOC_DSS_ITF_LDI_PLR_CTRL_data_en_plr_START    (3)
#define SOC_DSS_ITF_LDI_PLR_CTRL_data_en_plr_END      (3)


/*****************************************************************************
 结构名    : SOC_DSS_ITF_DSS_SH_MASK_INT_UNION
 结构说明  : DSS_SH_MASK_INT 寄存器结构定义。地址偏移量:0x001C，初值:0x00000000，宽度:32
 寄存器说明: LDI信号极性控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dss_sh_mask_int : 14; /* bit[0-13] : sensor hub的中断屏蔽寄存器，对应itf上报的14个中断信号
                                                           0：表示屏蔽
                                                           1：表示不屏蔽 */
        unsigned int  reserved        : 18; /* bit[14-31]:  */
    } reg;
} SOC_DSS_ITF_DSS_SH_MASK_INT_UNION;
#endif
#define SOC_DSS_ITF_DSS_SH_MASK_INT_dss_sh_mask_int_START  (0)
#define SOC_DSS_ITF_DSS_SH_MASK_INT_dss_sh_mask_int_END    (13)


/*****************************************************************************
 结构名    : SOC_DSS_ITF_LDI_3D_CTRL_UNION
 结构说明  : LDI_3D_CTRL 寄存器结构定义。地址偏移量:0x0020，初值:0x00000000，宽度:32
 寄存器说明: LDI 3D显示控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  active_space : 13; /* bit[0-12] : 帧与帧之间的active space时间配置，写入为实际值，取值范围为0~4095。（只用于3D 显示frame by frame格式）;Active space是以扫描行数为单位 */
        unsigned int  reserved     : 19; /* bit[13-31]:  */
    } reg;
} SOC_DSS_ITF_LDI_3D_CTRL_UNION;
#endif
#define SOC_DSS_ITF_LDI_3D_CTRL_active_space_START  (0)
#define SOC_DSS_ITF_LDI_3D_CTRL_active_space_END    (12)


/*****************************************************************************
 结构名    : SOC_DSS_ITF_LDI_CTRL_UNION
 结构说明  : LDI_CTRL 寄存器结构定义。地址偏移量:0x0024，初值:0x00000ED0，宽度:32
 寄存器说明: LDI控制寄存器
            (部分PDP专用)
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ldi_en         : 1;  /* bit[0]    : LDI使能 */
        unsigned int  disp_mode_buf  : 1;  /* bit[1]    : 显示模式。
                                                          0：2D 显示模式或者3D显示时非frame by frame模式，默认配置；
                                                          1：3D frame by frame模式； */
        unsigned int  data_gate_en   : 1;  /* bit[2]    : 数据有效信号门控功能使能。
                                                          0：不使能；
                                                          1：使能； */
        unsigned int  bpp            : 2;  /* bit[3-4]  : 输入像素深度配置。
                                                          00：输入RGB565像素格式；
                                                          01：输入RGB666像素格式；
                                                          10：输入RGB888像素格式；
                                                          11：保留 */
        unsigned int  dual_mode_en   : 1;  /* bit[5]    : 单/双dpi选择信号：
                                                          0：单dpi输出
                                                          1：双dpi输出
                                                          (PDP专用) */
        unsigned int  colorbar_width : 7;  /* bit[6-12] : colorbar RGB彩条宽度，写入值为实际值减1，取值范围为1~128 */
        unsigned int  bgr            : 1;  /* bit[13]   : RGB输出配置:
                                                          0：普通的RGB输出格式；
                                                          1：BGR输出格式（Blue与Red分量对调） */
        unsigned int  color_mode     : 1;  /* bit[14]   : 给DSI DPI接口的Color Mode信号：
                                                          0： Full color Mode;
                                                          1： Reduced Color Mode */
        unsigned int  shutdown       : 1;  /* bit[15]   : 给DSI DPI接口的shutdown信号：
                                                          0： LCD正常显示;
                                                          1： LCD进入Sleep模式 */
        unsigned int  split_mode     : 1;  /* bit[16]   : 双dpi输出模式选择信号：
                                                          0：左右模式
                                                          1：奇偶模式
                                                          (PDP专用) */
        unsigned int  dpi0_rs_clear  : 1;  /* bit[17]   : 输出给DPI0_RS的clear信号，高有效
                                                          (PDP专用) */
        unsigned int  dpi1_rs_clear  : 1;  /* bit[18]   : 输出给DPI1_RS的clear信号，高有效
                                                          (PDP专用) */
        unsigned int  reserved       : 13; /* bit[19-31]:  */
    } reg;
} SOC_DSS_ITF_LDI_CTRL_UNION;
#endif
#define SOC_DSS_ITF_LDI_CTRL_ldi_en_START          (0)
#define SOC_DSS_ITF_LDI_CTRL_ldi_en_END            (0)
#define SOC_DSS_ITF_LDI_CTRL_disp_mode_buf_START   (1)
#define SOC_DSS_ITF_LDI_CTRL_disp_mode_buf_END     (1)
#define SOC_DSS_ITF_LDI_CTRL_data_gate_en_START    (2)
#define SOC_DSS_ITF_LDI_CTRL_data_gate_en_END      (2)
#define SOC_DSS_ITF_LDI_CTRL_bpp_START             (3)
#define SOC_DSS_ITF_LDI_CTRL_bpp_END               (4)
#define SOC_DSS_ITF_LDI_CTRL_dual_mode_en_START    (5)
#define SOC_DSS_ITF_LDI_CTRL_dual_mode_en_END      (5)
#define SOC_DSS_ITF_LDI_CTRL_colorbar_width_START  (6)
#define SOC_DSS_ITF_LDI_CTRL_colorbar_width_END    (12)
#define SOC_DSS_ITF_LDI_CTRL_bgr_START             (13)
#define SOC_DSS_ITF_LDI_CTRL_bgr_END               (13)
#define SOC_DSS_ITF_LDI_CTRL_color_mode_START      (14)
#define SOC_DSS_ITF_LDI_CTRL_color_mode_END        (14)
#define SOC_DSS_ITF_LDI_CTRL_shutdown_START        (15)
#define SOC_DSS_ITF_LDI_CTRL_shutdown_END          (15)
#define SOC_DSS_ITF_LDI_CTRL_split_mode_START      (16)
#define SOC_DSS_ITF_LDI_CTRL_split_mode_END        (16)
#define SOC_DSS_ITF_LDI_CTRL_dpi0_rs_clear_START   (17)
#define SOC_DSS_ITF_LDI_CTRL_dpi0_rs_clear_END     (17)
#define SOC_DSS_ITF_LDI_CTRL_dpi1_rs_clear_START   (18)
#define SOC_DSS_ITF_LDI_CTRL_dpi1_rs_clear_END     (18)


/*****************************************************************************
 结构名    : SOC_DSS_ITF_LDI_WORK_MODE_UNION
 结构说明  : LDI_WORK_MODE 寄存器结构定义。地址偏移量:0x0028，初值:0x00000001，宽度:32
 寄存器说明: LDI工作模式控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  work_mode    : 1;  /* bit[0]   : 工作模式：
                                                       0：COLORBAR模式:LDI内部自动产生红、绿、蓝彩带， 用于LCD屏调试：
                                                       1：正常工作模式 */
        unsigned int  colorbar_ort : 1;  /* bit[1]   : colorbar方向选择信号：
                                                       0： 竖条
                                                       1： 横条 */
        unsigned int  reserved     : 30; /* bit[2-31]:  */
    } reg;
} SOC_DSS_ITF_LDI_WORK_MODE_UNION;
#endif
#define SOC_DSS_ITF_LDI_WORK_MODE_work_mode_START     (0)
#define SOC_DSS_ITF_LDI_WORK_MODE_work_mode_END       (0)
#define SOC_DSS_ITF_LDI_WORK_MODE_colorbar_ort_START  (1)
#define SOC_DSS_ITF_LDI_WORK_MODE_colorbar_ort_END    (1)


/*****************************************************************************
 结构名    : SOC_DSS_ITF_LDI_DE_SPACE_LOW_UNION
 结构说明  : LDI_DE_SPACE_LOW 寄存器结构定义。地址偏移量:0x002C，初值:0x00000000，宽度:32
 寄存器说明: 3D frame by frame格式下active space阶段DE信号有效控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  de_space_low : 1;  /* bit[0]   : DE信号在active space阶段是否有效：
                                                       0：DE信号在active space阶段为高；
                                                       1：DE信号在active space阶段为低；
                                                       该寄存器只在3D frame by frame格式下有效，2D格式下无效 */
        unsigned int  reserved     : 31; /* bit[1-31]:  */
    } reg;
} SOC_DSS_ITF_LDI_DE_SPACE_LOW_UNION;
#endif
#define SOC_DSS_ITF_LDI_DE_SPACE_LOW_de_space_low_START  (0)
#define SOC_DSS_ITF_LDI_DE_SPACE_LOW_de_space_low_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_ITF_DSI_CMD_MOD_CTRL_UNION
 结构说明  : DSI_CMD_MOD_CTRL 寄存器结构定义。地址偏移量:0x0030，初值:0x00000000，宽度:32
 寄存器说明: DSI Command(CMD)模式控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsi_halt_cmd_en   : 1;  /* bit[0]   : 在CMD模式下HALT信号的使能
                                                            0：不使能Halt信号，在内部不看这个信号
                                                            1：使能Halt信号 */
        unsigned int  dsi_halt_video_en : 1;  /* bit[1]   : 在Video模式下HALT信号的使能,用于last line拉长使能
                                                            0：不使能Halt信号，在内部不看这个信号
                                                            1：使能Halt信号 */
        unsigned int  dsi_wms_3d_mode   : 1;  /* bit[2]   : 在3D模式下WMS信号的模式（frame by frame）
                                                            0 分离WMS模式
                                                            1 连续WMS模式 */
        unsigned int  reserved          : 29; /* bit[3-31]:  */
    } reg;
} SOC_DSS_ITF_DSI_CMD_MOD_CTRL_UNION;
#endif
#define SOC_DSS_ITF_DSI_CMD_MOD_CTRL_dsi_halt_cmd_en_START    (0)
#define SOC_DSS_ITF_DSI_CMD_MOD_CTRL_dsi_halt_cmd_en_END      (0)
#define SOC_DSS_ITF_DSI_CMD_MOD_CTRL_dsi_halt_video_en_START  (1)
#define SOC_DSS_ITF_DSI_CMD_MOD_CTRL_dsi_halt_video_en_END    (1)
#define SOC_DSS_ITF_DSI_CMD_MOD_CTRL_dsi_wms_3d_mode_START    (2)
#define SOC_DSS_ITF_DSI_CMD_MOD_CTRL_dsi_wms_3d_mode_END      (2)


/*****************************************************************************
 结构名    : SOC_DSS_ITF_DSI_TE_CTRL_UNION
 结构说明  : DSI_TE_CTRL 寄存器结构定义。地址偏移量:0x0034，初值:0x00000100，宽度:32
 寄存器说明: DSI Command(CMD)模式TE控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsi_te_hard_en    : 1;  /* bit[0]    : TE模式使能信号
                                                             0：不使能TE模式
                                                             1：使能TE模式，LDI输出信号时序依赖于TE信号
                                                             每当在TE Mask模式并且是按比例做FRC（帧率切换）的模式开和关时需要先Disable这个寄存器。 */
        unsigned int  dsi_te0_pin_p     : 1;  /* bit[1]    : TE0 极性选择
                                                             0：保持输入极性
                                                             1：输入极性取反 */
        unsigned int  dsi_te1_pin_p     : 1;  /* bit[2]    : TE1 极性选择
                                                             0：保持输入极性
                                                             1：输入极性取反 */
        unsigned int  dsi_te_hard_sel   : 1;  /* bit[3]    : TE硬件模式源选择
                                                             0：从管脚输入的TE PIN源
                                                             1：从MIPI接口上读的TE Trigger源 */
        unsigned int  dsi_te_tri_sel    : 2;  /* bit[4-5]  : TE硬件模式下，DSI TE triger信号选择
                                                             2'b01：DSI0 TE TRIGER
                                                             2'b10：DSI1 TE TRIGER
                                                             2'b11：DSI0 TE TRIGER | DSI1 TE TRIGER */
        unsigned int  dsi_te_pin_hd_sel : 2;  /* bit[6-7]  : TE硬件模式下，TE PIN选择
                                                             2'b01：TE0 PIN
                                                             2'b10：TE1 PIN
                                                             2'b11：TE0 PIN | TE1 PIN */
        unsigned int  dsi_te_mask_en    : 1;  /* bit[8]    : TE屏蔽使能（只用于Hard模式，soft模式只需忽略中断即可，不需此功能）
                                                             0：屏蔽TE信号关闭
                                                             1：屏蔽TE信号功能打开 */
        unsigned int  dsi_te_mask_dis   : 4;  /* bit[9-12] : TE屏蔽时显示的TE个数
                                                             例如等于6时，开始的6个TE信号显示数据到屏， */
        unsigned int  dsi_te_mask_und   : 4;  /* bit[13-16]: TE屏蔽时屏蔽的TE个数
                                                             例如等于6时，接着显示的TE个数后面的6个TE信号被屏蔽 */
        unsigned int  dsi_te_pin_en     : 1;  /* bit[17]   : 在CMD模式下用TE PIN（管脚）检测使能
                                                             0 关闭TE PIN检测逻辑，用于Video模式或CMD模式不用TE PIN场景
                                                             1 启动TE PIN检测逻辑，用于CMD模式并且用TE PIN场景 */
        unsigned int  reserved          : 14; /* bit[18-31]:  */
    } reg;
} SOC_DSS_ITF_DSI_TE_CTRL_UNION;
#endif
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te_hard_en_START     (0)
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te_hard_en_END       (0)
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te0_pin_p_START      (1)
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te0_pin_p_END        (1)
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te1_pin_p_START      (2)
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te1_pin_p_END        (2)
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te_hard_sel_START    (3)
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te_hard_sel_END      (3)
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te_tri_sel_START     (4)
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te_tri_sel_END       (5)
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te_pin_hd_sel_START  (6)
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te_pin_hd_sel_END    (7)
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te_mask_en_START     (8)
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te_mask_en_END       (8)
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te_mask_dis_START    (9)
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te_mask_dis_END      (12)
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te_mask_und_START    (13)
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te_mask_und_END      (16)
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te_pin_en_START      (17)
#define SOC_DSS_ITF_DSI_TE_CTRL_dsi_te_pin_en_END        (17)


/*****************************************************************************
 结构名    : SOC_DSS_ITF_DSI_TE_HS_NUM_UNION
 结构说明  : DSI_TE_HS_NUM 寄存器结构定义。地址偏移量:0x0038，初值:0x00000000，宽度:32
 寄存器说明: DSI响应行配置寄存器控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsi_te0_hs_num : 13; /* bit[0-12] : 用于在TE0信号在Mode2(VS+HS)模式下，设置在哪个HS时开始发送数据。
                                                          设置为0有特殊含义，即此模式用VS发送数据不看HS。
                                                          实际发送值为DSI_TE1_HS_NUM + 1行发送。 */
        unsigned int  dsi_te1_hs_num : 13; /* bit[13-25]: 用于在TE1信号在Mode2(VS+HS)模式下，设置在哪个HS时开始发送数据。
                                                          设置为0有特殊含义，即此模式用VS发送数据不看HS。
                                                          实际发送值为DSI_TE1_HS_NUM + 1行发送。 */
        unsigned int  reserved       : 6;  /* bit[26-31]:  */
    } reg;
} SOC_DSS_ITF_DSI_TE_HS_NUM_UNION;
#endif
#define SOC_DSS_ITF_DSI_TE_HS_NUM_dsi_te0_hs_num_START  (0)
#define SOC_DSS_ITF_DSI_TE_HS_NUM_dsi_te0_hs_num_END    (12)
#define SOC_DSS_ITF_DSI_TE_HS_NUM_dsi_te1_hs_num_START  (13)
#define SOC_DSS_ITF_DSI_TE_HS_NUM_dsi_te1_hs_num_END    (25)


/*****************************************************************************
 结构名    : SOC_DSS_ITF_DSI_TE_HS_WD_UNION
 结构说明  : DSI_TE_HS_WD 寄存器结构定义。地址偏移量:0x003C，初值:0x00003003，宽度:32
 寄存器说明: DSI TE PIN模式检测Hsync宽度控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsi_te0_hs_wd : 12; /* bit[0-11] : 用于检测TE0信号在Mode2(VS+HS)模式下，HS信号的判别，当进来的TE信号有效区域大于这个寄存器设置是认为这个HS信号。
                                                         这个寄存器的设置值必须小于DSI_TE0_VS_WD的值。 */
        unsigned int  dsi_te1_hs_wd : 12; /* bit[12-23]: 用于检测TE1信号在Mode2(VS+HS)模式下，HS信号的判别，当进来的TE信号有效区域大于这个寄存器设置是认为这个HS信号。
                                                         这个寄存器的设置值必须小于DSI_TE1_VS_WD的值。 */
        unsigned int  reserved      : 8;  /* bit[24-31]:  */
    } reg;
} SOC_DSS_ITF_DSI_TE_HS_WD_UNION;
#endif
#define SOC_DSS_ITF_DSI_TE_HS_WD_dsi_te0_hs_wd_START  (0)
#define SOC_DSS_ITF_DSI_TE_HS_WD_dsi_te0_hs_wd_END    (11)
#define SOC_DSS_ITF_DSI_TE_HS_WD_dsi_te1_hs_wd_START  (12)
#define SOC_DSS_ITF_DSI_TE_HS_WD_dsi_te1_hs_wd_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_ITF_DSI_TE_VS_WD_UNION
 结构说明  : DSI_TE_VS_WD 寄存器结构定义。地址偏移量:0x0040，初值:0x00080080，宽度:32
 寄存器说明: DSI TE PIN模式检测Vsync宽度控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsi_te0_vs_wd : 12; /* bit[0-11] : 用于检测TE0信号在Mode2(VS+HS)模式下，VS信号的判别，当进来的TE信号有效区域大于这个寄存器设置是认为这个VS信号 */
        unsigned int  dsi_te1_vs_wd : 12; /* bit[12-23]: 用于检测TE1信号在Mode2(VS+HS)模式下，VS信号的判别，当进来的TE信号有效区域大于这个寄存器设置是认为这个VS信号，此寄存器设置必须大于DSI_TE1_HS_WD， */
        unsigned int  reserved      : 8;  /* bit[24-31]:  */
    } reg;
} SOC_DSS_ITF_DSI_TE_VS_WD_UNION;
#endif
#define SOC_DSS_ITF_DSI_TE_VS_WD_dsi_te0_vs_wd_START  (0)
#define SOC_DSS_ITF_DSI_TE_VS_WD_dsi_te0_vs_wd_END    (11)
#define SOC_DSS_ITF_DSI_TE_VS_WD_dsi_te1_vs_wd_START  (12)
#define SOC_DSS_ITF_DSI_TE_VS_WD_dsi_te1_vs_wd_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_ITF_LDI_FRM_MSK_UNION
 结构说明  : LDI_FRM_MSK 寄存器结构定义。地址偏移量:0x0044，初值:0x00000000，宽度:32
 寄存器说明: LDI帧屏蔽控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  frm_msk_en : 1;  /* bit[0]    : 0：帧屏蔽功能关闭
                                                      1：帧屏蔽功能使能 */
        unsigned int  reserved_0 : 7;  /* bit[1-7]  : 保留 */
        unsigned int  frm_msk    : 8;  /* bit[8-15] : 帧屏蔽功能使能时，LDI按照frm_unmsk:frm_msk的比例输出frm_unmsk帧，屏蔽frm_msk帧，依此循环。例如，如果frm_unmsk=1，frm_msk=59，LDI输出一帧后，后59帧的时间处于不输出数据。 */
        unsigned int  frm_unmsk  : 8;  /* bit[16-23]: 帧屏蔽功能使能时，LDI按照frm_unmsk:frm_msk的比例输出frm_unmsk帧，屏蔽frm_msk帧，依此循环。例如，如果frm_unmsk=1，frm_msk=59，LDI输出一帧后，后59帧的时间处于不输出数据。 */
        unsigned int  reserved_1 : 8;  /* bit[24-31]:  */
    } reg;
} SOC_DSS_ITF_LDI_FRM_MSK_UNION;
#endif
#define SOC_DSS_ITF_LDI_FRM_MSK_frm_msk_en_START  (0)
#define SOC_DSS_ITF_LDI_FRM_MSK_frm_msk_en_END    (0)
#define SOC_DSS_ITF_LDI_FRM_MSK_frm_msk_START     (8)
#define SOC_DSS_ITF_LDI_FRM_MSK_frm_msk_END       (15)
#define SOC_DSS_ITF_LDI_FRM_MSK_frm_unmsk_START   (16)
#define SOC_DSS_ITF_LDI_FRM_MSK_frm_unmsk_END     (23)


/*****************************************************************************
 结构名    : SOC_DSS_ITF_LDI_FRM_MSK_UP_UNION
 结构说明  : LDI_FRM_MSK_UP 寄存器结构定义。地址偏移量:0x0048，初值:0x00000000，宽度:32
 寄存器说明: LDI帧刷新控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  single_frm_update : 1;  /* bit[0]   : frm_msk_en为1时，向此寄存器写1刷新下一帧 */
        unsigned int  reserved          : 31; /* bit[1-31]:  */
    } reg;
} SOC_DSS_ITF_LDI_FRM_MSK_UP_UNION;
#endif
#define SOC_DSS_ITF_LDI_FRM_MSK_UP_single_frm_update_START  (0)
#define SOC_DSS_ITF_LDI_FRM_MSK_UP_single_frm_update_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_ITF_LDI_VINACT_MSK_LEN_UNION
 结构说明  : LDI_VINACT_MSK_LEN 寄存器结构定义。地址偏移量:0x0050，初值:0x00000000，宽度:32
 寄存器说明: v_inactive屏蔽寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ldi_vinact_msk_len : 13; /* bit[0-12] : 帧消影区需要被屏蔽的长度，单位为ldi_clk_s周期，在被屏蔽期间DFS不请求rqos */
        unsigned int  reserved           : 19; /* bit[13-31]: 保留 */
    } reg;
} SOC_DSS_ITF_LDI_VINACT_MSK_LEN_UNION;
#endif
#define SOC_DSS_ITF_LDI_VINACT_MSK_LEN_ldi_vinact_msk_len_START  (0)
#define SOC_DSS_ITF_LDI_VINACT_MSK_LEN_ldi_vinact_msk_len_END    (12)


/*****************************************************************************
 结构名    : SOC_DSS_ITF_LDI_CMD_EVENT_SEL_UNION
 结构说明  : LDI_CMD_EVENT_SEL 寄存器结构定义。地址偏移量:0x0060，初值:0x00000000，宽度:32
 寄存器说明: LDI选择给CMD输出的中断寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ldi_cmd_event_sel : 4;  /* bit[0-3] : 0：ldi选择frm_end_int作为cmd_event信号
                                                            1：ldi选择frm_start_int作为cmd_event信号
                                                            2：ldi选择vbackporch_int作为cmd_event信号
                                                            3：ldi选择vfrontporch_int作为cmd_event信号
                                                            4：ldi选择vfrontporch_end_int作为cmd_event信号
                                                            5：ldi选择vactive0_end_int作为cmd_event信号
                                                            6：ldi选择vactive0_start_int作为cmd_event信号
                                                            7：ldi选择vactive1_end_int作为cmd_event信号
                                                            8：ldi选择vactive1_start_int作为cmd_event信号 */
        unsigned int  reserved          : 28; /* bit[4-31]: 保留 */
    } reg;
} SOC_DSS_ITF_LDI_CMD_EVENT_SEL_UNION;
#endif
#define SOC_DSS_ITF_LDI_CMD_EVENT_SEL_ldi_cmd_event_sel_START  (0)
#define SOC_DSS_ITF_LDI_CMD_EVENT_SEL_ldi_cmd_event_sel_END    (3)


/*****************************************************************************
 结构名    : SOC_DSS_ITF_SRAM_LP_CTRL_UNION
 结构说明  : SRAM_LP_CTRL 寄存器结构定义。地址偏移量:0x0064，初值:0x00000001，宽度:32
 寄存器说明: SRAM低功耗控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pd_in_vfp : 1;  /* bit[0]   : 0：SRAM在VFP期间不进入power down模式
                                                    1：SRAM在VFP期间进入power down模式 */
        unsigned int  reserved  : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_ITF_SRAM_LP_CTRL_UNION;
#endif
#define SOC_DSS_ITF_SRAM_LP_CTRL_pd_in_vfp_START  (0)
#define SOC_DSS_ITF_SRAM_LP_CTRL_pd_in_vfp_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_ITF_ITF_RD_SHADOW_UNION
 结构说明  : ITF_RD_SHADOW 寄存器结构定义。地址偏移量:0x006C，初值:0x00000000，宽度:32
 寄存器说明: 读影子寄存器选择信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  itf_rd_shadow : 1;  /* bit[0]   : 1'b0 :读工作寄存器
                                                        1'b1 :读影子寄存器 */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_ITF_ITF_RD_SHADOW_UNION;
#endif
#define SOC_DSS_ITF_ITF_RD_SHADOW_itf_rd_shadow_START  (0)
#define SOC_DSS_ITF_ITF_RD_SHADOW_itf_rd_shadow_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_ITF_LDI_DPI1_HRZ_CTRL0_UNION
 结构说明  : LDI_DPI1_HRZ_CTRL0 寄存器结构定义。地址偏移量:0x00F0，初值:0x00000000，宽度:32
 寄存器说明: LDI-DPI1水平扫描控制寄存器0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 16; /* bit[0-15] : 保留 */
        unsigned int  dpi1_hbp : 13; /* bit[16-28]: 行后消隐时间配置，写入的是实际值。行后消隐的取值范围为0~4095 */
        unsigned int  reserved_1: 3;  /* bit[29-31]:  */
    } reg;
} SOC_DSS_ITF_LDI_DPI1_HRZ_CTRL0_UNION;
#endif
#define SOC_DSS_ITF_LDI_DPI1_HRZ_CTRL0_dpi1_hbp_START  (16)
#define SOC_DSS_ITF_LDI_DPI1_HRZ_CTRL0_dpi1_hbp_END    (28)


/*****************************************************************************
 结构名    : SOC_DSS_ITF_LDI_DPI1_HRZ_CTRL1_UNION
 结构说明  : LDI_DPI1_HRZ_CTRL1 寄存器结构定义。地址偏移量:0x00F4，初值:0x00000000，宽度:32
 寄存器说明: LDI-DPI1水平扫描寄存器1
            (双mipi专用)
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dpi1_hsw : 13; /* bit[0-12] : 水平同步脉宽配置，写入的值为实际值减1后的结果。水平同步脉冲的宽度以像素时钟为单位，取值范围为1~4096 */
        unsigned int  reserved : 19; /* bit[13-31]:  */
    } reg;
} SOC_DSS_ITF_LDI_DPI1_HRZ_CTRL1_UNION;
#endif
#define SOC_DSS_ITF_LDI_DPI1_HRZ_CTRL1_dpi1_hsw_START  (0)
#define SOC_DSS_ITF_LDI_DPI1_HRZ_CTRL1_dpi1_hsw_END    (12)


/*****************************************************************************
 结构名    : SOC_DSS_ITF_LDI_DPI1_HRZ_CTRL2_UNION
 结构说明  : LDI_DPI1_HRZ_CTRL2 寄存器结构定义。地址偏移量:0x00F8，初值:0x00000000，宽度:32
 寄存器说明: LDI-DPI1水平扫描寄存器1
            (双mipi专用)
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dpi1_hsize : 13; /* bit[0-12] : 水平尺寸寄存器，写入的值为实际值减1后的结果 */
        unsigned int  reserved   : 19; /* bit[13-31]:  */
    } reg;
} SOC_DSS_ITF_LDI_DPI1_HRZ_CTRL2_UNION;
#endif
#define SOC_DSS_ITF_LDI_DPI1_HRZ_CTRL2_dpi1_hsize_START  (0)
#define SOC_DSS_ITF_LDI_DPI1_HRZ_CTRL2_dpi1_hsize_END    (12)


/*****************************************************************************
 结构名    : SOC_DSS_ITF_LDI_OVERLAP_SIZE_UNION
 结构说明  : LDI_OVERLAP_SIZE 寄存器结构定义。地址偏移量:0x00FC，初值:0x00000000，宽度:32
 寄存器说明: LDI双dpi模式overlap尺寸寄存器
            (双mipi专用)
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dpi0_overlap_size : 8;  /* bit[0-7]  : 左半图像与DPI1_HSIZE重叠区域的尺寸，单位为列。此寄存器仅在双DPI左右模式时起作用。 */
        unsigned int  reserved_0        : 8;  /* bit[8-15] : 保留 */
        unsigned int  dpi1_overlap_size : 8;  /* bit[16-23]: 右半图像与DPI0_HSIZE重叠区域的尺寸，单位为列。此寄存器仅在双DPI左右模式时起作用。 */
        unsigned int  reserved_1        : 8;  /* bit[24-31]:  */
    } reg;
} SOC_DSS_ITF_LDI_OVERLAP_SIZE_UNION;
#endif
#define SOC_DSS_ITF_LDI_OVERLAP_SIZE_dpi0_overlap_size_START  (0)
#define SOC_DSS_ITF_LDI_OVERLAP_SIZE_dpi0_overlap_size_END    (7)
#define SOC_DSS_ITF_LDI_OVERLAP_SIZE_dpi1_overlap_size_START  (16)
#define SOC_DSS_ITF_LDI_OVERLAP_SIZE_dpi1_overlap_size_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_ITF_LDI_MEM_CTRL_UNION
 结构说明  : LDI_MEM_CTRL 寄存器结构定义。地址偏移量:0x0100，初值:0x00000000，宽度:32
 寄存器说明: MEM低功耗控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ldi_mem_ctrl : 4;  /* bit[0-3] : 调试用寄存器，对应spram1344x48
                                                       [3] mem_ctrl_auto_en , 自动模式、软件配置模式选择,0自动模式，1软件配置模式 
                                                       [2]: 软件配置模式下有效，为1表示进入Shut Down模式
                                                       [1]: 软件配置模式下有效，为1表示进入Deep Sleep模式
                                                       [0]: 软件配置模式下有效，为1表示进入Sleep模式 */
        unsigned int  reserved     : 28; /* bit[4-31]: 保留 */
    } reg;
} SOC_DSS_ITF_LDI_MEM_CTRL_UNION;
#endif
#define SOC_DSS_ITF_LDI_MEM_CTRL_ldi_mem_ctrl_START  (0)
#define SOC_DSS_ITF_LDI_MEM_CTRL_ldi_mem_ctrl_END    (3)


/*****************************************************************************
 结构名    : SOC_DSS_ITF_LDI_CLK_SEL_UNION
 结构说明  : LDI_CLK_SEL 寄存器结构定义。地址偏移量:0x0108，初值:0xFFFFFFFF，宽度:32
 寄存器说明: 一级模块时钟选择信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ldi_clk_sel : 32; /* bit[0-31]: 各一级模块的时钟选择信号，
                                                      1：表示强制打开时钟。
                                                      0：表示需要根据软件和硬件的时钟使能来开启或关闭时钟
                                                      bit0：用于apb；
                                                      bit1：用于reg；
                                                      bit2：用于dss_ldi； */
    } reg;
} SOC_DSS_ITF_LDI_CLK_SEL_UNION;
#endif
#define SOC_DSS_ITF_LDI_CLK_SEL_ldi_clk_sel_START  (0)
#define SOC_DSS_ITF_LDI_CLK_SEL_ldi_clk_sel_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_ITF_LDI_CLK_EN_UNION
 结构说明  : LDI_CLK_EN 寄存器结构定义。地址偏移量:0x010C，初值:0xFFFFFFFF，宽度:32
 寄存器说明: 一级模块时钟使能信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ldi_clk_en : 32; /* bit[0-31]: 各一级模块的软件时钟使能信号
                                                     1：表示软件时钟使能有效，允许硬件开钟
                                                     0：表示软件时钟使能无效，禁止硬件开钟
                                                     bit0：reserved；
                                                     bit1：用于reg；
                                                     bit2：用于dss_ldi； */
    } reg;
} SOC_DSS_ITF_LDI_CLK_EN_UNION;
#endif
#define SOC_DSS_ITF_LDI_CLK_EN_ldi_clk_en_START  (0)
#define SOC_DSS_ITF_LDI_CLK_EN_ldi_clk_en_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_ITF_LDI_IF_BYPASS_UNION
 结构说明  : LDI_IF_BYPASS 寄存器结构定义。地址偏移量:0x0110，初值:0x00000000，宽度:32
 寄存器说明: sram bypass选择信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ldi_if_bypass : 1;  /* bit[0]   : 保留 */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_ITF_LDI_IF_BYPASS_UNION;
#endif
#define SOC_DSS_ITF_LDI_IF_BYPASS_ldi_if_bypass_START  (0)
#define SOC_DSS_ITF_LDI_IF_BYPASS_ldi_if_bypass_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_ITF_REG_DEFAULT_UNION
 结构说明  : REG_DEFAULT 寄存器结构定义。地址偏移量:0x0114，初值:0x00000000，宽度:32
 寄存器说明: 模块影子寄存器恢复到默认值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reg_default : 1;  /* bit[0]   : 模块所有影子寄存器恢复到默认值，高有效 */
        unsigned int  reserved    : 31; /* bit[1-31]:  */
    } reg;
} SOC_DSS_ITF_REG_DEFAULT_UNION;
#endif
#define SOC_DSS_ITF_REG_DEFAULT_reg_default_START  (0)
#define SOC_DSS_ITF_REG_DEFAULT_reg_default_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_ITF_FRM_VALID_DBG_UNION
 结构说明  : FRM_VALID_DBG 寄存器结构定义。地址偏移量:0x0118，初值:0x00000000，宽度:32
 寄存器说明: 模块影子寄存器恢复到默认值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  frm_valid_dbg : 32; /* bit[0-31]: [31:25]:reserved;
                                                        [24]: 0表示选择按需输出给cmdlist vactive1_start_int，无效帧不出 ； 1表示每帧输出vactive1_start_int
                                                        [23]: 0表示选择按需输出给cmdlist vactive1_end_int，无效帧不出 ； 1表示每帧输出vactive1_end_int
                                                        [22]: 0表示选择按需输出给cmdlist vactive0_start_int，无效帧不出 ； 1表示每帧输出vactive0_start_int
                                                        [21]: 0表示选择按需输出给cmdlist vactive0_end_int，无效帧不出 ； 1表示每帧输出vactive0_end_int
                                                        [20]: 0表示选择按需输出给cmdlist vfrontporch_end_int，无效帧不出 ； 1表示每帧输出vfrontporch_end_int
                                                        [19]: 0表示选择按需输出给cmdlist vfrontporch_int，无效帧不出 ； 1表示每帧输出vfrontporch_int
                                                        [18]: 0表示选择按需输出给cmdlist vbackporch_int，无效帧不出 ； 1表示每帧输出vbackporch_int
                                                        [17]: 0表示选择按需输出给cmdlist frm_start_int，无效帧不出 ； 1表示每帧输出frm_start_int
                                                        [16]: 0表示选择按需输出给cmdlist frm_end_int，无效帧不出 ； 1表示每帧输出frm_end_int
                                                        [15]: 0表示选择每帧出glb dsi_te_tri_int ； 1表示按需出dsi_te_tri_int ，无效帧不出
                                                        [14]: 0表示选择每帧出glb lcd_te0_pin_int ； 1表示按需出frm_start_int，无效帧不出
                                                        [13]: 0表示选择每帧出glb lcd_te1_pin_int ； 1表示按需出lcd_te1_pin_int ，无效帧不出
                                                        [12]: 0表示选择每帧出glb vactive1_end_int ； 1表示按需出vactive1_end_int ,无效帧不出
                                                        [11]: 0表示选择每帧出glb vactive1_start_int ； 1表示按需出vactive1_start_int ,无效帧不出
                                                        [10]: 0表示选择每帧出glb vactive0_end_int ； 1表示按需出vactive0_end_int ,无效帧不出
                                                        [9]: 1表示选择每帧出glb vactive0_start_int ；0表示按需出vactive0_start_int ,无效帧不出
                                                        [8]: 0表示选择每帧出glb vfrontporch_int ； 1表示按需出vfrontporch_int ,无效帧不出
                                                        [7]: 0表示选择每帧出glb vbackporch_int ； 1表示按需出vbackporch_int ,无效帧不出
                                                        [6]: 0表示选择每帧出glb vsync_int ； 1表示按需出vsync_int ,无效帧不出
                                                        [5]: 0表示选择每帧出glb vfrontporch_end_int ； 1表示按需出vfrontporch_end_int ,无效帧不出
                                                        [4]: 0表示选择每帧出glb frm_end_int ； 1表示按需出frm_end_int ，无效帧不出
                                                        [3]: 0表示选择每帧出glb frm_start_int ； 1表示按需出frm_start_int，无效帧不出
                                                        [2:0]:reserved; */
    } reg;
} SOC_DSS_ITF_FRM_VALID_DBG_UNION;
#endif
#define SOC_DSS_ITF_FRM_VALID_DBG_frm_valid_dbg_START  (0)
#define SOC_DSS_ITF_FRM_VALID_DBG_frm_valid_dbg_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_ITF_CRC_DBG_ITF_UNION
 结构说明  : CRC_DBG_ITF 寄存器结构定义。地址偏移量:0x0200，初值:0x00000000，宽度:32
 寄存器说明: LDI的crc校验结果
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  crc_dbg_itf : 32; /* bit[0-31]: LDI0的crc校验结果 */
    } reg;
} SOC_DSS_ITF_CRC_DBG_ITF_UNION;
#endif
#define SOC_DSS_ITF_CRC_DBG_ITF_crc_dbg_itf_START  (0)
#define SOC_DSS_ITF_CRC_DBG_ITF_crc_dbg_itf_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_ITF_CRC_ITF_EN_UNION
 结构说明  : CRC_ITF_EN 寄存器结构定义。地址偏移量:0x0204，初值:0x00000000，宽度:32
 寄存器说明: LDI的CRC启动使能信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  crc_itf_en : 1;  /* bit[0-0] : LDI0的CRC启动使能信号 */
        unsigned int  reserved   : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_ITF_CRC_ITF_EN_UNION;
#endif
#define SOC_DSS_ITF_CRC_ITF_EN_crc_itf_en_START  (0)
#define SOC_DSS_ITF_CRC_ITF_EN_crc_itf_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_ITF_CRC_ITF_FRM_UNION
 结构说明  : CRC_ITF_FRM 寄存器结构定义。地址偏移量:0x0208，初值:0x00000000，宽度:32
 寄存器说明: LDI上报的CRC校验的帧数
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  crc_itf_frm : 32; /* bit[0-31]: LDI0上报的CRC校验的帧数 */
    } reg;
} SOC_DSS_ITF_CRC_ITF_FRM_UNION;
#endif
#define SOC_DSS_ITF_CRC_ITF_FRM_crc_itf_frm_START  (0)
#define SOC_DSS_ITF_CRC_ITF_FRM_crc_itf_frm_END    (31)






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

#endif /* end of soc_dss_itf_interface.h */
