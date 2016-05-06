/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_dss_dsi_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:20:05
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_DSS_DSI.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_DSS_DSI_INTERFACE_H__
#define __SOC_DSS_DSI_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) reg_DSI
 ****************************************************************************/
/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_VERSION_UNION */
#define SOC_DSS_DSI_VERSION_ADDR(base)                ((base) + (0x0000))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_PWR_UP_UNION */
#define SOC_DSS_DSI_PWR_UP_ADDR(base)                 ((base) + (0x0004))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_CLKMGR_CFG_UNION */
#define SOC_DSS_DSI_CLKMGR_CFG_ADDR(base)             ((base) + (0x0008))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_DPI_VCID_UNION */
#define SOC_DSS_DSI_DPI_VCID_ADDR(base)               ((base) + (0x000C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_DPI_COLOR_CODING_UNION */
#define SOC_DSS_DSI_DPI_COLOR_CODING_ADDR(base)       ((base) + (0x0010))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_DPI_CFG_POL_UNION */
#define SOC_DSS_DSI_DPI_CFG_POL_ADDR(base)            ((base) + (0x0014))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_DPI_LP_CMD_TIM_UNION */
#define SOC_DSS_DSI_DPI_LP_CMD_TIM_ADDR(base)         ((base) + (0x0018))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_PCKHDL_CFG_UNION */
#define SOC_DSS_DSI_PCKHDL_CFG_ADDR(base)             ((base) + (0x002C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_GEN_VCID_UNION */
#define SOC_DSS_DSI_GEN_VCID_ADDR(base)               ((base) + (0x0030))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_MODE_CFG_UNION */
#define SOC_DSS_DSI_MODE_CFG_ADDR(base)               ((base) + (0x0034))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_VID_MODE_CFG_UNION */
#define SOC_DSS_DSI_VID_MODE_CFG_ADDR(base)           ((base) + (0x0038))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_VID_PKT_SIZE_UNION */
#define SOC_DSS_DSI_VID_PKT_SIZE_ADDR(base)           ((base) + (0x003C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_VID_NUM_CHUNKS_UNION */
#define SOC_DSS_DSI_VID_NUM_CHUNKS_ADDR(base)         ((base) + (0x0040))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_VID_NULL_SIZE_UNION */
#define SOC_DSS_DSI_VID_NULL_SIZE_ADDR(base)          ((base) + (0x0044))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_VID_HSA_TIME_UNION */
#define SOC_DSS_DSI_VID_HSA_TIME_ADDR(base)           ((base) + (0x0048))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_VID_HBP_TIME_UNION */
#define SOC_DSS_DSI_VID_HBP_TIME_ADDR(base)           ((base) + (0x004C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_VID_HLINE_TIME_UNION */
#define SOC_DSS_DSI_VID_HLINE_TIME_ADDR(base)         ((base) + (0x0050))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_VID_VSA_LINES_UNION */
#define SOC_DSS_DSI_VID_VSA_LINES_ADDR(base)          ((base) + (0x0054))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_VID_VBP_LINES_UNION */
#define SOC_DSS_DSI_VID_VBP_LINES_ADDR(base)          ((base) + (0x0058))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_VID_VFP_LINES_UNION */
#define SOC_DSS_DSI_VID_VFP_LINES_ADDR(base)          ((base) + (0x005C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_VID_VACTIVE_LINES_UNION */
#define SOC_DSS_DSI_VID_VACTIVE_LINES_ADDR(base)      ((base) + (0x0060))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_EDPI_CMD_SIZE_UNION */
#define SOC_DSS_DSI_EDPI_CMD_SIZE_ADDR(base)          ((base) + (0x0064))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_CMD_MODE_CFG_UNION */
#define SOC_DSS_DSI_CMD_MODE_CFG_ADDR(base)           ((base) + (0x0068))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_GEN_HDR_UNION */
#define SOC_DSS_DSI_GEN_HDR_ADDR(base)                ((base) + (0x006C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_GEN_PLD_DATA_UNION */
#define SOC_DSS_DSI_GEN_PLD_DATA_ADDR(base)           ((base) + (0x0070))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_CMD_PKT_STATUS_UNION */
#define SOC_DSS_DSI_CMD_PKT_STATUS_ADDR(base)         ((base) + (0x0074))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_TO_CNT_CFG_UNION */
#define SOC_DSS_DSI_TO_CNT_CFG_ADDR(base)             ((base) + (0x0078))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_HS_RD_TO_CNT_UNION */
#define SOC_DSS_DSI_HS_RD_TO_CNT_ADDR(base)           ((base) + (0x007C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_LP_RD_TO_CNT_UNION */
#define SOC_DSS_DSI_LP_RD_TO_CNT_ADDR(base)           ((base) + (0x0080))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_HS_WR_TO_CNT_UNION */
#define SOC_DSS_DSI_HS_WR_TO_CNT_ADDR(base)           ((base) + (0x0084))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_LP_WR_TO_CNT_UNION */
#define SOC_DSS_DSI_LP_WR_TO_CNT_ADDR(base)           ((base) + (0x0088))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_BTA_TO_CNT_UNION */
#define SOC_DSS_DSI_BTA_TO_CNT_ADDR(base)             ((base) + (0x008C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_SDF_3D_UNION */
#define SOC_DSS_DSI_SDF_3D_ADDR(base)                 ((base) + (0x0090))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_LPCLK_CTRL_UNION */
#define SOC_DSS_DSI_LPCLK_CTRL_ADDR(base)             ((base) + (0x0094))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_PHY_TMR_LPCLK_CFG_UNION */
#define SOC_DSS_DSI_PHY_TMR_LPCLK_CFG_ADDR(base)      ((base) + (0x0098))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_PHY_TMR_CFG_UNION */
#define SOC_DSS_DSI_PHY_TMR_CFG_ADDR(base)            ((base) + (0x009C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_PHY_RSTZ_UNION */
#define SOC_DSS_DSI_PHY_RSTZ_ADDR(base)               ((base) + (0x00A0))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_PHY_IF_CFG_UNION */
#define SOC_DSS_DSI_PHY_IF_CFG_ADDR(base)             ((base) + (0x00A4))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_PHY_ULPS_CTRL_UNION */
#define SOC_DSS_DSI_PHY_ULPS_CTRL_ADDR(base)          ((base) + (0x00A8))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_PHY_TX_TRIGGERS_UNION */
#define SOC_DSS_DSI_PHY_TX_TRIGGERS_ADDR(base)        ((base) + (0x00AC))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_PHY_STATUS_UNION */
#define SOC_DSS_DSI_PHY_STATUS_ADDR(base)             ((base) + (0x00B0))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_PHY_TST_CTRL0_UNION */
#define SOC_DSS_DSI_PHY_TST_CTRL0_ADDR(base)          ((base) + (0x00B4))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_PHY_TST_CTRL1_UNION */
#define SOC_DSS_DSI_PHY_TST_CTRL1_ADDR(base)          ((base) + (0x00B8))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_INT_ST0_UNION */
#define SOC_DSS_DSI_INT_ST0_ADDR(base)                ((base) + (0x00BC))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_INT_ST1_UNION */
#define SOC_DSS_DSI_INT_ST1_ADDR(base)                ((base) + (0x00C0))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_INT_MSK0_UNION */
#define SOC_DSS_DSI_INT_MSK0_ADDR(base)               ((base) + (0x00C4))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_INT_MSK1_UNION */
#define SOC_DSS_DSI_INT_MSK1_ADDR(base)               ((base) + (0x00C8))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_INT_FORCE0_UNION */
#define SOC_DSS_DSI_INT_FORCE0_ADDR(base)             ((base) + (0x00D8))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_INT_FORCE1_UNION */
#define SOC_DSS_DSI_INT_FORCE1_ADDR(base)             ((base) + (0x00DC))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_VID_SHADOW_CTRL_UNION */
#define SOC_DSS_DSI_VID_SHADOW_CTRL_ADDR(base)        ((base) + (0x0100))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_DPI_VCID_ACT_UNION */
#define SOC_DSS_DSI_DPI_VCID_ACT_ADDR(base)           ((base) + (0x010C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_DPI_COLOR_CODING_ACT_UNION */
#define SOC_DSS_DSI_DPI_COLOR_CODING_ACT_ADDR(base)   ((base) + (0x0110))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_DPI_LP_CMD_TIM_ACT_UNION */
#define SOC_DSS_DSI_DPI_LP_CMD_TIM_ACT_ADDR(base)     ((base) + (0x0118))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_VID_MODE_CFG_ACT_UNION */
#define SOC_DSS_DSI_VID_MODE_CFG_ACT_ADDR(base)       ((base) + (0x0138))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_VID_PKT_SIZE_ACT_UNION */
#define SOC_DSS_DSI_VID_PKT_SIZE_ACT_ADDR(base)       ((base) + (0x013C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_VID_NUM_CHUNKS_ACT_UNION */
#define SOC_DSS_DSI_VID_NUM_CHUNKS_ACT_ADDR(base)     ((base) + (0x0140))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_VID_NULL_SIZE_ACT_UNION */
#define SOC_DSS_DSI_VID_NULL_SIZE_ACT_ADDR(base)      ((base) + (0x0144))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_VID_HSA_TIME_ACT_UNION */
#define SOC_DSS_DSI_VID_HSA_TIME_ACT_ADDR(base)       ((base) + (0x0148))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_VID_HBP_TIME_ACT_UNION */
#define SOC_DSS_DSI_VID_HBP_TIME_ACT_ADDR(base)       ((base) + (0x014C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_VID_HLINE_TIME_ACT_UNION */
#define SOC_DSS_DSI_VID_HLINE_TIME_ACT_ADDR(base)     ((base) + (0x0150))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_VID_VSA_LINES_ACT_UNION */
#define SOC_DSS_DSI_VID_VSA_LINES_ACT_ADDR(base)      ((base) + (0x0154))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_VID_VBP_LINES_ACT_UNION */
#define SOC_DSS_DSI_VID_VBP_LINES_ACT_ADDR(base)      ((base) + (0x0158))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_VID_VFP_LINES_ACT_UNION */
#define SOC_DSS_DSI_VID_VFP_LINES_ACT_ADDR(base)      ((base) + (0x015C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_VID_VACTIVE_LINES_ACT_UNION */
#define SOC_DSS_DSI_VID_VACTIVE_LINES_ACT_ADDR(base)  ((base) + (0x0160))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DSI_SDF_3D_ACT_UNION */
#define SOC_DSS_DSI_SDF_3D_ACT_ADDR(base)             ((base) + (0x0190))





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
                     (1/1) reg_DSI
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_DSS_DSI_VERSION_UNION
 结构说明  : VERSION 寄存器结构定义。地址偏移量:0x0000，初值:0x3133302A，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  version : 32; /* bit[0-31]:  */
    } reg;
} SOC_DSS_DSI_VERSION_UNION;
#endif
#define SOC_DSS_DSI_VERSION_version_START  (0)
#define SOC_DSS_DSI_VERSION_version_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_PWR_UP_UNION
 结构说明  : PWR_UP 寄存器结构定义。地址偏移量:0x0004，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  shutdownz : 1;  /* bit[0]   : This bit configures the core either to power up or to reset. shutdownz is the soft reset register. Its default value is 0. After the core configuration, to enable the DWC_mipi_dsi_host, set this register to 1. 
                                                    ■ 0: Reset
                                                    ■ 1: Power-up */
        unsigned int  reserved  : 31; /* bit[1-31]:  */
    } reg;
} SOC_DSS_DSI_PWR_UP_UNION;
#endif
#define SOC_DSS_DSI_PWR_UP_shutdownz_START  (0)
#define SOC_DSS_DSI_PWR_UP_shutdownz_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_CLKMGR_CFG_UNION
 结构说明  : CLKMGR_CFG 寄存器结构定义。地址偏移量:0x0008，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tx_esc_clk_division : 8;  /* bit[0-7]  : This field indicates the division factor for the TX Escape clock source (lanebyteclk). The values 0 and 1 stop the TX_ESC clock generation. */
        unsigned int  to_clk_division     : 8;  /* bit[8-15] : This field indicates the division factor for the Time Out clock used as the timing unit in the configuration of HS to LP and LP to HS transition error. */
        unsigned int  reserved            : 16; /* bit[16-31]:  */
    } reg;
} SOC_DSS_DSI_CLKMGR_CFG_UNION;
#endif
#define SOC_DSS_DSI_CLKMGR_CFG_tx_esc_clk_division_START  (0)
#define SOC_DSS_DSI_CLKMGR_CFG_tx_esc_clk_division_END    (7)
#define SOC_DSS_DSI_CLKMGR_CFG_to_clk_division_START      (8)
#define SOC_DSS_DSI_CLKMGR_CFG_to_clk_division_END        (15)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_DPI_VCID_UNION
 结构说明  : DPI_VCID 寄存器结构定义。地址偏移量:0x000C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dpi_vcid : 2;  /* bit[0-1] : This field configures the DPI virtual channel id that is indexed to the Video mode packets. */
        unsigned int  reserved : 30; /* bit[2-31]:  */
    } reg;
} SOC_DSS_DSI_DPI_VCID_UNION;
#endif
#define SOC_DSS_DSI_DPI_VCID_dpi_vcid_START  (0)
#define SOC_DSS_DSI_DPI_VCID_dpi_vcid_END    (1)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_DPI_COLOR_CODING_UNION
 结构说明  : DPI_COLOR_CODING 寄存器结构定义。地址偏移量:0x0010，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dpi_color_coding : 4;  /* bit[0-3] : This field configures the DPI color coding as follows:
                                                           ■ 0000: 16-bit configuration 1
                                                           ■ 0001: 16-bit configuration 2
                                                           ■ 0010: 16-bit configuration 3
                                                           ■ 0011: 18-bit configuration 1
                                                           ■ 0100: 18-bit configuration 2
                                                           ■ 0101: 24-bit
                                                           ■ 0110: 20-bit YCbCr 4:2:2 loosely packed
                                                           ■ 0111: 24-bit YCbCr 4:2:2
                                                           ■ 1000: 16-bit YCbCr 4:2:2
                                                           ■ 1001: 30-bit
                                                           ■ 1010: 36-bit
                                                           ■ 1011-1111: 12-bit YCbCr 4:2:0
                                                           Note: If the eDPI interface is chosen and currently works in the Command mode (cmd_video_mode = 1), then 
                                                           0110-1111: 24-bit  */
        unsigned int  reserved_0       : 4;  /* bit[4-7] :  */
        unsigned int  loosely18_en     : 1;  /* bit[8]   : When set to 1, this bit activates loosely packed variant to 18-bit configurations. */
        unsigned int  reserved_1       : 23; /* bit[9-31]:  */
    } reg;
} SOC_DSS_DSI_DPI_COLOR_CODING_UNION;
#endif
#define SOC_DSS_DSI_DPI_COLOR_CODING_dpi_color_coding_START  (0)
#define SOC_DSS_DSI_DPI_COLOR_CODING_dpi_color_coding_END    (3)
#define SOC_DSS_DSI_DPI_COLOR_CODING_loosely18_en_START      (8)
#define SOC_DSS_DSI_DPI_COLOR_CODING_loosely18_en_END        (8)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_DPI_CFG_POL_UNION
 结构说明  : DPI_CFG_POL 寄存器结构定义。地址偏移量:0x0014，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dataen_active_low : 1;  /* bit[0]   : When set to 1, this bit configures the data enable pin (dpidataen) as active low. */
        unsigned int  vsync_active_low  : 1;  /* bit[1]   : When set to 1, this bit configures the vertical synchronism pin (dpivsync) as active low. */
        unsigned int  hsync_active_low  : 1;  /* bit[2]   : When set to 1, this bit configures the horizontal synchronism pin (dpihsync) as active low. */
        unsigned int  shutd_active_low  : 1;  /* bit[3]   : When set to 1, this bit configures the shutdown pin (dpishutdn) as active low. */
        unsigned int  colorm_active_low : 1;  /* bit[4]   : When set to 1, this bit configures the color mode pin (dpicolorm) as active low. */
        unsigned int  reserved          : 27; /* bit[5-31]:  */
    } reg;
} SOC_DSS_DSI_DPI_CFG_POL_UNION;
#endif
#define SOC_DSS_DSI_DPI_CFG_POL_dataen_active_low_START  (0)
#define SOC_DSS_DSI_DPI_CFG_POL_dataen_active_low_END    (0)
#define SOC_DSS_DSI_DPI_CFG_POL_vsync_active_low_START   (1)
#define SOC_DSS_DSI_DPI_CFG_POL_vsync_active_low_END     (1)
#define SOC_DSS_DSI_DPI_CFG_POL_hsync_active_low_START   (2)
#define SOC_DSS_DSI_DPI_CFG_POL_hsync_active_low_END     (2)
#define SOC_DSS_DSI_DPI_CFG_POL_shutd_active_low_START   (3)
#define SOC_DSS_DSI_DPI_CFG_POL_shutd_active_low_END     (3)
#define SOC_DSS_DSI_DPI_CFG_POL_colorm_active_low_START  (4)
#define SOC_DSS_DSI_DPI_CFG_POL_colorm_active_low_END    (4)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_DPI_LP_CMD_TIM_UNION
 结构说明  : DPI_LP_CMD_TIM 寄存器结构定义。地址偏移量:0x0018，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  invact_lpcmd_time  : 8;  /* bit[0-7]  : This field is used for the transmission of commands in low-power mode. It defines the size, in bytes, of the largest packet that can fit in a line during the VACT region. */
        unsigned int  reserved_0         : 8;  /* bit[8-15] :  */
        unsigned int  outvact_lpcmd_time : 8;  /* bit[16-23]: This field is used for the transmission of commands in low-power mode. It defines the size, in bytes, of the largest packet that can fit in a line during the VSA, VBP, and VFP regions. */
        unsigned int  reserved_1         : 8;  /* bit[24-31]:  */
    } reg;
} SOC_DSS_DSI_DPI_LP_CMD_TIM_UNION;
#endif
#define SOC_DSS_DSI_DPI_LP_CMD_TIM_invact_lpcmd_time_START   (0)
#define SOC_DSS_DSI_DPI_LP_CMD_TIM_invact_lpcmd_time_END     (7)
#define SOC_DSS_DSI_DPI_LP_CMD_TIM_outvact_lpcmd_time_START  (16)
#define SOC_DSS_DSI_DPI_LP_CMD_TIM_outvact_lpcmd_time_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_PCKHDL_CFG_UNION
 结构说明  : PCKHDL_CFG 寄存器结构定义。地址偏移量:0x002C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  eotp_tx_en : 1;  /* bit[0]   : When set to 1, this bit enables the EoTp transmission. */
        unsigned int  eotp_rx_en : 1;  /* bit[1]   : When set to 1, this bit enables the EoTp reception. */
        unsigned int  bta_en     : 1;  /* bit[2]   : When set to 1, this bit enables the Bus Turn-Around (BTA) request. */
        unsigned int  ecc_rx_en  : 1;  /* bit[3]   : When set to 1, this bit enables the ECC reception, error correction, and reporting. */
        unsigned int  crc_rx_en  : 1;  /* bit[4]   : When set to 1, this bit enables the CRC reception and error reporting.
                                                     Dependency: DSI_DATAINTERFACE = 1 or DSI_DATAINTERFACE = 3 or DSI_GENERIC = 1. Otherwise, this bit is reserved. */
        unsigned int  reserved   : 27; /* bit[5-31]:  */
    } reg;
} SOC_DSS_DSI_PCKHDL_CFG_UNION;
#endif
#define SOC_DSS_DSI_PCKHDL_CFG_eotp_tx_en_START  (0)
#define SOC_DSS_DSI_PCKHDL_CFG_eotp_tx_en_END    (0)
#define SOC_DSS_DSI_PCKHDL_CFG_eotp_rx_en_START  (1)
#define SOC_DSS_DSI_PCKHDL_CFG_eotp_rx_en_END    (1)
#define SOC_DSS_DSI_PCKHDL_CFG_bta_en_START      (2)
#define SOC_DSS_DSI_PCKHDL_CFG_bta_en_END        (2)
#define SOC_DSS_DSI_PCKHDL_CFG_ecc_rx_en_START   (3)
#define SOC_DSS_DSI_PCKHDL_CFG_ecc_rx_en_END     (3)
#define SOC_DSS_DSI_PCKHDL_CFG_crc_rx_en_START   (4)
#define SOC_DSS_DSI_PCKHDL_CFG_crc_rx_en_END     (4)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_GEN_VCID_UNION
 结构说明  : GEN_VCID 寄存器结构定义。地址偏移量:0x0030，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gen_vcid_rx : 2;  /* bit[0-1] : This field indicates the Generic interface read-back virtual channel identification. */
        unsigned int  reserved    : 30; /* bit[2-31]:  */
    } reg;
} SOC_DSS_DSI_GEN_VCID_UNION;
#endif
#define SOC_DSS_DSI_GEN_VCID_gen_vcid_rx_START  (0)
#define SOC_DSS_DSI_GEN_VCID_gen_vcid_rx_END    (1)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_MODE_CFG_UNION
 结构说明  : MODE_CFG 寄存器结构定义。地址偏移量:0x0034，初值:0x00000001，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cmd_video_mode : 1;  /* bit[0]   : This bit configures the operation mode:
                                                         ■ 0: Video mode
                                                         ■ 1: Command mode */
        unsigned int  reserved       : 31; /* bit[1-31]:  */
    } reg;
} SOC_DSS_DSI_MODE_CFG_UNION;
#endif
#define SOC_DSS_DSI_MODE_CFG_cmd_video_mode_START  (0)
#define SOC_DSS_DSI_MODE_CFG_cmd_video_mode_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_VID_MODE_CFG_UNION
 结构说明  : VID_MODE_CFG 寄存器结构定义。地址偏移量:0x0038，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vid_mode_type    : 2;  /* bit[0-1]  : This field indicates the video mode transmission type as follows:
                                                            ■ 00: Non-burst with sync pulses
                                                            ■ 01: Non-burst with sync events
                                                            ■ 10 and 11: Burst mode */
        unsigned int  reserved_0       : 6;  /* bit[2-7]  :  */
        unsigned int  lp_vsa_en        : 1;  /* bit[8]    : When set to 1, this bit enables the return to low-power inside the VSA period when timing allows. */
        unsigned int  lp_vbp_en        : 1;  /* bit[9]    : When set to 1, this bit enables the return to low-power inside the VBP period when timing allows. */
        unsigned int  lp_vfp_en        : 1;  /* bit[10]   : When set to 1, this bit enables the return to low-power inside the VFP period when timing allows. */
        unsigned int  lp_vact_en       : 1;  /* bit[11]   : When set to 1, this bit enables the return to low-power inside the VACT period when timing allows. */
        unsigned int  lp_hbp_en        : 1;  /* bit[12]   : When set to 1, this bit enables the return to low-power inside the HBP period when timing allows. */
        unsigned int  lp_hfp_en        : 1;  /* bit[13]   : When set to 1, this bit enables the return to low-power inside the HFP period when timing allows. */
        unsigned int  frame_bta_ack_en : 1;  /* bit[14]   : When set to 1, this bit enables the request for an acknowledge response at the end of a frame. */
        unsigned int  lp_cmd_en        : 1;  /* bit[15]   : When set to 1, this bit enables the command transmission only in low-power mode. */
        unsigned int  vpg_en           : 1;  /* bit[16]   : When set to 1, this bit enables the video mode pattern generator. */
        unsigned int  reserved_1       : 3;  /* bit[17-19]:  */
        unsigned int  vpg_mode         : 1;  /* bit[20]   : This field is to select the pattern:
                                                            0: Color bar (horizontal or vertical
                                                            1: BER pattern (vertical only) */
        unsigned int  reserved_2       : 3;  /* bit[21-23]:  */
        unsigned int  vpg_orientation  : 1;  /* bit[24]   : This field indicates the color bar orientation as follows:
                                                            0: Vertical mode
                                                            1: Horizontal mode */
        unsigned int  reserved_3       : 7;  /* bit[25-31]:  */
    } reg;
} SOC_DSS_DSI_VID_MODE_CFG_UNION;
#endif
#define SOC_DSS_DSI_VID_MODE_CFG_vid_mode_type_START     (0)
#define SOC_DSS_DSI_VID_MODE_CFG_vid_mode_type_END       (1)
#define SOC_DSS_DSI_VID_MODE_CFG_lp_vsa_en_START         (8)
#define SOC_DSS_DSI_VID_MODE_CFG_lp_vsa_en_END           (8)
#define SOC_DSS_DSI_VID_MODE_CFG_lp_vbp_en_START         (9)
#define SOC_DSS_DSI_VID_MODE_CFG_lp_vbp_en_END           (9)
#define SOC_DSS_DSI_VID_MODE_CFG_lp_vfp_en_START         (10)
#define SOC_DSS_DSI_VID_MODE_CFG_lp_vfp_en_END           (10)
#define SOC_DSS_DSI_VID_MODE_CFG_lp_vact_en_START        (11)
#define SOC_DSS_DSI_VID_MODE_CFG_lp_vact_en_END          (11)
#define SOC_DSS_DSI_VID_MODE_CFG_lp_hbp_en_START         (12)
#define SOC_DSS_DSI_VID_MODE_CFG_lp_hbp_en_END           (12)
#define SOC_DSS_DSI_VID_MODE_CFG_lp_hfp_en_START         (13)
#define SOC_DSS_DSI_VID_MODE_CFG_lp_hfp_en_END           (13)
#define SOC_DSS_DSI_VID_MODE_CFG_frame_bta_ack_en_START  (14)
#define SOC_DSS_DSI_VID_MODE_CFG_frame_bta_ack_en_END    (14)
#define SOC_DSS_DSI_VID_MODE_CFG_lp_cmd_en_START         (15)
#define SOC_DSS_DSI_VID_MODE_CFG_lp_cmd_en_END           (15)
#define SOC_DSS_DSI_VID_MODE_CFG_vpg_en_START            (16)
#define SOC_DSS_DSI_VID_MODE_CFG_vpg_en_END              (16)
#define SOC_DSS_DSI_VID_MODE_CFG_vpg_mode_START          (20)
#define SOC_DSS_DSI_VID_MODE_CFG_vpg_mode_END            (20)
#define SOC_DSS_DSI_VID_MODE_CFG_vpg_orientation_START   (24)
#define SOC_DSS_DSI_VID_MODE_CFG_vpg_orientation_END     (24)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_VID_PKT_SIZE_UNION
 结构说明  : VID_PKT_SIZE 寄存器结构定义。地址偏移量:0x003C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vid_pkt_size : 14; /* bit[0-13] : This field configures the number of pixels in a single video packet. For 18-bit not loosely packed data types, this number must be a multiple of 4. For YCbCr data types, it must be a multiple of 2, as described in the DSI specification. */
        unsigned int  reserved     : 18; /* bit[14-31]:  */
    } reg;
} SOC_DSS_DSI_VID_PKT_SIZE_UNION;
#endif
#define SOC_DSS_DSI_VID_PKT_SIZE_vid_pkt_size_START  (0)
#define SOC_DSS_DSI_VID_PKT_SIZE_vid_pkt_size_END    (13)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_VID_NUM_CHUNKS_UNION
 结构说明  : VID_NUM_CHUNKS 寄存器结构定义。地址偏移量:0x0040，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vid_null_chunks : 13; /* bit[0-12] : This register configures the number of chunks to be transmitted during a Line period (a chunk consists of a video packet and a null packet). 
                                                           If set to 0 or 1, the video line is transmitted in a single packet. 
                                                           If set to 1, the packet is part of a chunk, so a null packet follows it if vid_null_size > 0. Otherwise, multiple chunks are used to transmit each video line. */
        unsigned int  reserved        : 19; /* bit[13-31]:  */
    } reg;
} SOC_DSS_DSI_VID_NUM_CHUNKS_UNION;
#endif
#define SOC_DSS_DSI_VID_NUM_CHUNKS_vid_null_chunks_START  (0)
#define SOC_DSS_DSI_VID_NUM_CHUNKS_vid_null_chunks_END    (12)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_VID_NULL_SIZE_UNION
 结构说明  : VID_NULL_SIZE 寄存器结构定义。地址偏移量:0x0044，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vid_null_size : 13; /* bit[0-12] : This register configures the number of bytes inside a null packet. 
                                                         Setting it to 0 disables the null packets. */
        unsigned int  reserved      : 19; /* bit[13-31]:  */
    } reg;
} SOC_DSS_DSI_VID_NULL_SIZE_UNION;
#endif
#define SOC_DSS_DSI_VID_NULL_SIZE_vid_null_size_START  (0)
#define SOC_DSS_DSI_VID_NULL_SIZE_vid_null_size_END    (12)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_VID_HSA_TIME_UNION
 结构说明  : VID_HSA_TIME 寄存器结构定义。地址偏移量:0x0048，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vid_has_time : 12; /* bit[0-11] : This field configures the Horizontal Synchronism Active period in lane 
                                                        byte clock cycles. */
        unsigned int  reserved     : 20; /* bit[12-31]:  */
    } reg;
} SOC_DSS_DSI_VID_HSA_TIME_UNION;
#endif
#define SOC_DSS_DSI_VID_HSA_TIME_vid_has_time_START  (0)
#define SOC_DSS_DSI_VID_HSA_TIME_vid_has_time_END    (11)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_VID_HBP_TIME_UNION
 结构说明  : VID_HBP_TIME 寄存器结构定义。地址偏移量:0x004C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vid_hbp_time : 12; /* bit[0-11] : This field configures the Horizontal Back Porch period in lane byte clock cycles. */
        unsigned int  reserved     : 20; /* bit[12-31]:  */
    } reg;
} SOC_DSS_DSI_VID_HBP_TIME_UNION;
#endif
#define SOC_DSS_DSI_VID_HBP_TIME_vid_hbp_time_START  (0)
#define SOC_DSS_DSI_VID_HBP_TIME_vid_hbp_time_END    (11)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_VID_HLINE_TIME_UNION
 结构说明  : VID_HLINE_TIME 寄存器结构定义。地址偏移量:0x0050，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vid_hline_time : 15; /* bit[0-14] : This field configures the size of the total line time 
                                                          (HSA+HBP+HACT+HFP) counted in lane byte clock cycles. */
        unsigned int  reserved       : 17; /* bit[15-31]:  */
    } reg;
} SOC_DSS_DSI_VID_HLINE_TIME_UNION;
#endif
#define SOC_DSS_DSI_VID_HLINE_TIME_vid_hline_time_START  (0)
#define SOC_DSS_DSI_VID_HLINE_TIME_vid_hline_time_END    (14)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_VID_VSA_LINES_UNION
 结构说明  : VID_VSA_LINES 寄存器结构定义。地址偏移量:0x0054，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vsa_lines : 10; /* bit[0-9]  : This field configures the Vertical Synchronism Active period measured in number of horizontal lines. */
        unsigned int  reserved  : 22; /* bit[10-31]:  */
    } reg;
} SOC_DSS_DSI_VID_VSA_LINES_UNION;
#endif
#define SOC_DSS_DSI_VID_VSA_LINES_vsa_lines_START  (0)
#define SOC_DSS_DSI_VID_VSA_LINES_vsa_lines_END    (9)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_VID_VBP_LINES_UNION
 结构说明  : VID_VBP_LINES 寄存器结构定义。地址偏移量:0x0058，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vbp_lines : 10; /* bit[0-9]  : This field configures the Vertical Back Porch period measured in number of horizontal lines. */
        unsigned int  reserved  : 22; /* bit[10-31]:  */
    } reg;
} SOC_DSS_DSI_VID_VBP_LINES_UNION;
#endif
#define SOC_DSS_DSI_VID_VBP_LINES_vbp_lines_START  (0)
#define SOC_DSS_DSI_VID_VBP_LINES_vbp_lines_END    (9)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_VID_VFP_LINES_UNION
 结构说明  : VID_VFP_LINES 寄存器结构定义。地址偏移量:0x005C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vfp_lines : 10; /* bit[0-9]  : This field configures the Vertical Front Porch period measured in number of horizontal lines. */
        unsigned int  reserved  : 22; /* bit[10-31]:  */
    } reg;
} SOC_DSS_DSI_VID_VFP_LINES_UNION;
#endif
#define SOC_DSS_DSI_VID_VFP_LINES_vfp_lines_START  (0)
#define SOC_DSS_DSI_VID_VFP_LINES_vfp_lines_END    (9)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_VID_VACTIVE_LINES_UNION
 结构说明  : VID_VACTIVE_LINES 寄存器结构定义。地址偏移量:0x0060，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  v_active_lines : 14; /* bit[0-13] : his field configures the Vertical Active period measured in number of horizontal lines. */
        unsigned int  reserved       : 18; /* bit[14-31]:  */
    } reg;
} SOC_DSS_DSI_VID_VACTIVE_LINES_UNION;
#endif
#define SOC_DSS_DSI_VID_VACTIVE_LINES_v_active_lines_START  (0)
#define SOC_DSS_DSI_VID_VACTIVE_LINES_v_active_lines_END    (13)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_EDPI_CMD_SIZE_UNION
 结构说明  : EDPI_CMD_SIZE 寄存器结构定义。地址偏移量:0x0064，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  edpi_allowed_cmd_size : 16; /* bit[0-15] : This field configures the maximum allowed size for an eDPI write memory command, measured in pixels. Automatic partitioning of data obtained from eDPI is permanently enabled. */
        unsigned int  reserved              : 16; /* bit[16-31]:  */
    } reg;
} SOC_DSS_DSI_EDPI_CMD_SIZE_UNION;
#endif
#define SOC_DSS_DSI_EDPI_CMD_SIZE_edpi_allowed_cmd_size_START  (0)
#define SOC_DSS_DSI_EDPI_CMD_SIZE_edpi_allowed_cmd_size_END    (15)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_CMD_MODE_CFG_UNION
 结构说明  : CMD_MODE_CFG 寄存器结构定义。地址偏移量:0x0068，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tear_fx_en      : 1;  /* bit[0]    : When set to 1, this bit enables the tearing effect acknowledge request. */
        unsigned int  ack_rqst_en     : 1;  /* bit[1]    : When set to 1, this bit enables the acknowledge request after each packet transmission. */
        unsigned int  reserved_0      : 6;  /* bit[2-7]  :  */
        unsigned int  gen_sw_0p_tx    : 1;  /* bit[8]    : This bit configures the Generic short write packet with zero parameter 
                                                           command transmission type:
                                                           ■ 0: High-speed
                                                           ■ 1: Low-power */
        unsigned int  gen_sw_1p_tx    : 1;  /* bit[9]    : This bit configures the Generic short write packet with one parameter command transmission type:
                                                           ■ 0: High-speed
                                                           ■ 1: Low-power */
        unsigned int  gen_sw_2p_tx    : 1;  /* bit[10]   : This bit configures the Generic short write packet with two parameters command transmission type:
                                                           ■ 0: High-speed
                                                           ■ 1: Low-power */
        unsigned int  gen_sr_0p_tx    : 1;  /* bit[11]   : This bit configures the Generic short read packet with zero parameter command transmission type:
                                                           ■ 0: High-speed
                                                           ■ 1: Low-power */
        unsigned int  gen_sr_1p_tx    : 1;  /* bit[12]   : This bit configures the Generic short read packet with one parameter command transmission type:
                                                           ■ 0: High-speed
                                                           ■ 1: Low-power */
        unsigned int  gen_sr_2p_tx    : 1;  /* bit[13]   : This bit configures the Generic short read packet with two parameters command transmission type:
                                                           ■ 0: High-speed
                                                           ■ 1: Low-power */
        unsigned int  gen_lw_tx       : 1;  /* bit[14]   : This bit configures the Generic long write packet command 
                                                           transmission type:
                                                           ■ 0: High-speed
                                                           ■ 1: Low-power */
        unsigned int  reserved_1      : 1;  /* bit[15]   :  */
        unsigned int  dcs_sw_0p_tx    : 1;  /* bit[16]   : This bit configures the DCS short write packet with zero parameter command transmission type:
                                                           ■ 0: High-speed
                                                           ■ 1: Low-power */
        unsigned int  dcs_sw_1p_tx    : 1;  /* bit[17]   : This bit configures the DCS short write packet with one parameter command transmission type:
                                                           ■ 0: High-speed
                                                           ■ 1: Low-power */
        unsigned int  dcs_sr_0p_tx    : 1;  /* bit[18]   : This bit configures the DCS short read packet with zero parameter command transmission type:
                                                           ■ 0: High-speed
                                                           ■ 1: Low-power */
        unsigned int  dcs_lw_tx       : 1;  /* bit[19]   : This bit configures the DCS long write packet command transmission type:
                                                           ■ 0: High-speed
                                                           ■ 1: Low-power */
        unsigned int  reserved_2      : 4;  /* bit[20-23]:  */
        unsigned int  max_rd_pkt_size : 1;  /* bit[24]   : This bit configures the maximum read packet size command 
                                                           transmission type:
                                                           ■ 0: High-speed
                                                           ■ 1: Low-power */
        unsigned int  reserved_3      : 7;  /* bit[25-31]:  */
    } reg;
} SOC_DSS_DSI_CMD_MODE_CFG_UNION;
#endif
#define SOC_DSS_DSI_CMD_MODE_CFG_tear_fx_en_START       (0)
#define SOC_DSS_DSI_CMD_MODE_CFG_tear_fx_en_END         (0)
#define SOC_DSS_DSI_CMD_MODE_CFG_ack_rqst_en_START      (1)
#define SOC_DSS_DSI_CMD_MODE_CFG_ack_rqst_en_END        (1)
#define SOC_DSS_DSI_CMD_MODE_CFG_gen_sw_0p_tx_START     (8)
#define SOC_DSS_DSI_CMD_MODE_CFG_gen_sw_0p_tx_END       (8)
#define SOC_DSS_DSI_CMD_MODE_CFG_gen_sw_1p_tx_START     (9)
#define SOC_DSS_DSI_CMD_MODE_CFG_gen_sw_1p_tx_END       (9)
#define SOC_DSS_DSI_CMD_MODE_CFG_gen_sw_2p_tx_START     (10)
#define SOC_DSS_DSI_CMD_MODE_CFG_gen_sw_2p_tx_END       (10)
#define SOC_DSS_DSI_CMD_MODE_CFG_gen_sr_0p_tx_START     (11)
#define SOC_DSS_DSI_CMD_MODE_CFG_gen_sr_0p_tx_END       (11)
#define SOC_DSS_DSI_CMD_MODE_CFG_gen_sr_1p_tx_START     (12)
#define SOC_DSS_DSI_CMD_MODE_CFG_gen_sr_1p_tx_END       (12)
#define SOC_DSS_DSI_CMD_MODE_CFG_gen_sr_2p_tx_START     (13)
#define SOC_DSS_DSI_CMD_MODE_CFG_gen_sr_2p_tx_END       (13)
#define SOC_DSS_DSI_CMD_MODE_CFG_gen_lw_tx_START        (14)
#define SOC_DSS_DSI_CMD_MODE_CFG_gen_lw_tx_END          (14)
#define SOC_DSS_DSI_CMD_MODE_CFG_dcs_sw_0p_tx_START     (16)
#define SOC_DSS_DSI_CMD_MODE_CFG_dcs_sw_0p_tx_END       (16)
#define SOC_DSS_DSI_CMD_MODE_CFG_dcs_sw_1p_tx_START     (17)
#define SOC_DSS_DSI_CMD_MODE_CFG_dcs_sw_1p_tx_END       (17)
#define SOC_DSS_DSI_CMD_MODE_CFG_dcs_sr_0p_tx_START     (18)
#define SOC_DSS_DSI_CMD_MODE_CFG_dcs_sr_0p_tx_END       (18)
#define SOC_DSS_DSI_CMD_MODE_CFG_dcs_lw_tx_START        (19)
#define SOC_DSS_DSI_CMD_MODE_CFG_dcs_lw_tx_END          (19)
#define SOC_DSS_DSI_CMD_MODE_CFG_max_rd_pkt_size_START  (24)
#define SOC_DSS_DSI_CMD_MODE_CFG_max_rd_pkt_size_END    (24)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_GEN_HDR_UNION
 结构说明  : GEN_HDR 寄存器结构定义。地址偏移量:0x006C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gen_dt        : 6;  /* bit[0-5]  : This field configures the packet data type of the header packet. */
        unsigned int  gen_vc        : 2;  /* bit[6-7]  : This field configures the virtual channel id of the header packet. */
        unsigned int  gen_wc_lsbyte : 8;  /* bit[8-15] : This field configures the least significant byte of the header packet's Word count for long packets or data 0 for short packets. */
        unsigned int  gen_wc_msbyte : 8;  /* bit[16-23]: This field configures the most significant byte of the header packet's word count for long packets or data 1 for short packets. */
        unsigned int  reserved      : 8;  /* bit[24-31]:  */
    } reg;
} SOC_DSS_DSI_GEN_HDR_UNION;
#endif
#define SOC_DSS_DSI_GEN_HDR_gen_dt_START         (0)
#define SOC_DSS_DSI_GEN_HDR_gen_dt_END           (5)
#define SOC_DSS_DSI_GEN_HDR_gen_vc_START         (6)
#define SOC_DSS_DSI_GEN_HDR_gen_vc_END           (7)
#define SOC_DSS_DSI_GEN_HDR_gen_wc_lsbyte_START  (8)
#define SOC_DSS_DSI_GEN_HDR_gen_wc_lsbyte_END    (15)
#define SOC_DSS_DSI_GEN_HDR_gen_wc_msbyte_START  (16)
#define SOC_DSS_DSI_GEN_HDR_gen_wc_msbyte_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_GEN_PLD_DATA_UNION
 结构说明  : GEN_PLD_DATA 寄存器结构定义。地址偏移量:0x0070，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gen_pld_b1 : 8;  /* bit[0-7]  : This field indicates byte 1 of the packet payload. */
        unsigned int  gen_pld_b2 : 8;  /* bit[8-15] : This field indicates byte 2 of the packet payload. */
        unsigned int  gen_pld_b3 : 8;  /* bit[16-23]: This field indicates byte 3 of the packet payload. */
        unsigned int  gen_pld_b4 : 8;  /* bit[24-31]: This field indicates byte 4 of the packet payload. */
    } reg;
} SOC_DSS_DSI_GEN_PLD_DATA_UNION;
#endif
#define SOC_DSS_DSI_GEN_PLD_DATA_gen_pld_b1_START  (0)
#define SOC_DSS_DSI_GEN_PLD_DATA_gen_pld_b1_END    (7)
#define SOC_DSS_DSI_GEN_PLD_DATA_gen_pld_b2_START  (8)
#define SOC_DSS_DSI_GEN_PLD_DATA_gen_pld_b2_END    (15)
#define SOC_DSS_DSI_GEN_PLD_DATA_gen_pld_b3_START  (16)
#define SOC_DSS_DSI_GEN_PLD_DATA_gen_pld_b3_END    (23)
#define SOC_DSS_DSI_GEN_PLD_DATA_gen_pld_b4_START  (24)
#define SOC_DSS_DSI_GEN_PLD_DATA_gen_pld_b4_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_CMD_PKT_STATUS_UNION
 结构说明  : CMD_PKT_STATUS 寄存器结构定义。地址偏移量:0x0074，初值:0x00000015，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gen_cmd_empty   : 1;  /* bit[0]    : This bit indicates the empty status of the generic command FIFO.
                                                           Dependency: DSI_GENERIC = 1. Otherwise, this bit is reserved.
                                                           Value after reset: 0x1 */
        unsigned int  gen_cmd_full    : 1;  /* bit[1]    : This bit indicates the full status of the generic command FIFO.
                                                           Dependency: DSI_GENERIC = 1. Otherwise, this bit is reserved.
                                                           Value after reset: 0x0 */
        unsigned int  gen_pld_w_empty : 1;  /* bit[2]    : This bit indicates the empty status of the generic write payload FIFO.
                                                           Dependency: DSI_GENERIC = 1. Otherwise, this bit is reserved.
                                                           Value after reset: 0x1 */
        unsigned int  gen_pld_w_full  : 1;  /* bit[3]    : This bit indicates the full status of the generic write payload FIFO.
                                                           Dependency: DSI_GENERIC = 1. Otherwise, this bit is reserved.
                                                           Value after reset: 0x0 */
        unsigned int  gen_pld_r_empty : 1;  /* bit[4]    : This bit indicates the empty status of the generic read payload FIFO.
                                                           Dependency: DSI_GENERIC = 1. Otherwise, this bit is reserved.
                                                           Value after reset: 0x1 */
        unsigned int  gen_pld_r_full  : 1;  /* bit[5]    : This bit indicates the full status of the generic read payload FIFO.
                                                           Dependency: DSI_GENERIC = 1. Otherwise, this bit is reserved.
                                                           Value after reset: 0x0 */
        unsigned int  gen_rd_cmd_busy : 1;  /* bit[6]    : This bit is set when a read command is issued and cleared when the entire response is stored in the FIFO.
                                                           Dependency: DSI_GENERIC = 1. Otherwise, this bit is reserved.
                                                           Value after reset: 0x0 */
        unsigned int  reserved_0      : 1;  /* bit[7]    : This bit indicates the full status of the DBI command FIFO.
                                                           Dependency: DSI_DATAINTERFACE = 1 or DSI_DATAINTERFACE = 3. 
                                                           Otherwise, this bit is reserved.
                                                           Value after reset: 0x0 */
        unsigned int  dbi_cmd_empty   : 1;  /* bit[8]    : This bit indicates the full status of the DBI command FIFO.
                                                           Dependency: DSI_DATAINTERFACE = 1 or DSI_DATAINTERFACE = 3. 
                                                           Otherwise, this bit is reserved.
                                                           Value after reset: 0x0 */
        unsigned int  dbi_cmd_full    : 1;  /* bit[9]    : This bit indicates the empty status of the DBI write payload FIFO.
                                                           Dependency: DSI_DATAINTERFACE = 1 or DSI_DATAINTERFACE = 3. 
                                                           Otherwise, this bit is reserved.
                                                           Value after reset: 0x1 */
        unsigned int  dbi_pld_w_empty : 1;  /* bit[10]   : This bit indicates the empty status of the DBI write payload FIFO.
                                                           Dependency: DSI_DATAINTERFACE = 1 or DSI_DATAINTERFACE = 3. 
                                                           Otherwise, this bit is reserved.
                                                           Value after reset: 0x1 */
        unsigned int  dbi_pld_w_full  : 1;  /* bit[11]   : This bit indicates the full status of the DBI write payload FIFO.
                                                           Dependency: DSI_DATAINTERFACE = 1 or DSI_DATAINTERFACE = 3. 
                                                           Otherwise, this bit is reserved.
                                                           Value after reset: 0x0 */
        unsigned int  dbi_pld_r_empty : 1;  /* bit[12]   : This bit indicates the empty status of the DBI read payload FIFO.
                                                           Dependency: DSI_DATAINTERFACE = 1 or DSI_DATAINTERFACE = 3. 
                                                           Otherwise, this bit is reserved.
                                                           Value after reset: 0x1 */
        unsigned int  dbi_pld_r_full  : 1;  /* bit[13]   : This bit indicates the full status of the DBI read payload FIFO.
                                                           Dependency: DSI_DATAINTERFACE = 1 or DSI_DATAINTERFACE = 3. 
                                                           Otherwise, this bit is reserved.
                                                           Value after reset: 0x0 */
        unsigned int  dbi_rd_cmd_busy : 1;  /* bit[14]   : This bit is set when a read command is issued and cleared when the entire response is stored in the FIFO.
                                                           Dependency: DSI_DATAINTERFACE = 1 or DSI_DATAINTERFACE = 3. 
                                                           Otherwise, this bit is reserved.
                                                           Value after reset: 0x0 */
        unsigned int  reserved_1      : 17; /* bit[15-31]:  */
    } reg;
} SOC_DSS_DSI_CMD_PKT_STATUS_UNION;
#endif
#define SOC_DSS_DSI_CMD_PKT_STATUS_gen_cmd_empty_START    (0)
#define SOC_DSS_DSI_CMD_PKT_STATUS_gen_cmd_empty_END      (0)
#define SOC_DSS_DSI_CMD_PKT_STATUS_gen_cmd_full_START     (1)
#define SOC_DSS_DSI_CMD_PKT_STATUS_gen_cmd_full_END       (1)
#define SOC_DSS_DSI_CMD_PKT_STATUS_gen_pld_w_empty_START  (2)
#define SOC_DSS_DSI_CMD_PKT_STATUS_gen_pld_w_empty_END    (2)
#define SOC_DSS_DSI_CMD_PKT_STATUS_gen_pld_w_full_START   (3)
#define SOC_DSS_DSI_CMD_PKT_STATUS_gen_pld_w_full_END     (3)
#define SOC_DSS_DSI_CMD_PKT_STATUS_gen_pld_r_empty_START  (4)
#define SOC_DSS_DSI_CMD_PKT_STATUS_gen_pld_r_empty_END    (4)
#define SOC_DSS_DSI_CMD_PKT_STATUS_gen_pld_r_full_START   (5)
#define SOC_DSS_DSI_CMD_PKT_STATUS_gen_pld_r_full_END     (5)
#define SOC_DSS_DSI_CMD_PKT_STATUS_gen_rd_cmd_busy_START  (6)
#define SOC_DSS_DSI_CMD_PKT_STATUS_gen_rd_cmd_busy_END    (6)
#define SOC_DSS_DSI_CMD_PKT_STATUS_dbi_cmd_empty_START    (8)
#define SOC_DSS_DSI_CMD_PKT_STATUS_dbi_cmd_empty_END      (8)
#define SOC_DSS_DSI_CMD_PKT_STATUS_dbi_cmd_full_START     (9)
#define SOC_DSS_DSI_CMD_PKT_STATUS_dbi_cmd_full_END       (9)
#define SOC_DSS_DSI_CMD_PKT_STATUS_dbi_pld_w_empty_START  (10)
#define SOC_DSS_DSI_CMD_PKT_STATUS_dbi_pld_w_empty_END    (10)
#define SOC_DSS_DSI_CMD_PKT_STATUS_dbi_pld_w_full_START   (11)
#define SOC_DSS_DSI_CMD_PKT_STATUS_dbi_pld_w_full_END     (11)
#define SOC_DSS_DSI_CMD_PKT_STATUS_dbi_pld_r_empty_START  (12)
#define SOC_DSS_DSI_CMD_PKT_STATUS_dbi_pld_r_empty_END    (12)
#define SOC_DSS_DSI_CMD_PKT_STATUS_dbi_pld_r_full_START   (13)
#define SOC_DSS_DSI_CMD_PKT_STATUS_dbi_pld_r_full_END     (13)
#define SOC_DSS_DSI_CMD_PKT_STATUS_dbi_rd_cmd_busy_START  (14)
#define SOC_DSS_DSI_CMD_PKT_STATUS_dbi_rd_cmd_busy_END    (14)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_TO_CNT_CFG_UNION
 结构说明  : TO_CNT_CFG 寄存器结构定义。地址偏移量:0x0078，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lprx_to_cnt : 16; /* bit[0-15] : This field configures the timeout counter that triggers a low-power reception timeout contention detection (measured in TO_CLK_DIVISION cycles). */
        unsigned int  hstx_to_cnt : 16; /* bit[16-31]: This field configures the timeout counter that triggers a high-speed transmission timeout contention detection (measured in TO_CLK_DIVISION cycles). */
    } reg;
} SOC_DSS_DSI_TO_CNT_CFG_UNION;
#endif
#define SOC_DSS_DSI_TO_CNT_CFG_lprx_to_cnt_START  (0)
#define SOC_DSS_DSI_TO_CNT_CFG_lprx_to_cnt_END    (15)
#define SOC_DSS_DSI_TO_CNT_CFG_hstx_to_cnt_START  (16)
#define SOC_DSS_DSI_TO_CNT_CFG_hstx_to_cnt_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_HS_RD_TO_CNT_UNION
 结构说明  : HS_RD_TO_CNT 寄存器结构定义。地址偏移量:0x007C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hs_rd_to_cnt : 16; /* bit[0-15] : This field sets a period for which the DWC_mipi_dsi_host keeps the link still, after sending a high-speed read operation. This period is measured in cycles of lanebyteclk. The counting starts when the D-PHY enters the Stop state and causes no interrupts. */
        unsigned int  reserved     : 16; /* bit[16-31]:  */
    } reg;
} SOC_DSS_DSI_HS_RD_TO_CNT_UNION;
#endif
#define SOC_DSS_DSI_HS_RD_TO_CNT_hs_rd_to_cnt_START  (0)
#define SOC_DSS_DSI_HS_RD_TO_CNT_hs_rd_to_cnt_END    (15)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_LP_RD_TO_CNT_UNION
 结构说明  : LP_RD_TO_CNT 寄存器结构定义。地址偏移量:0x0080，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lp_rd_to_cnt : 16; /* bit[0-15] : This field sets a period for which the DWC_mipi_dsi_host keeps the link still, after sending a low-power read operation. This period is measured in cycles of lanebyteclk. The counting starts when the D-PHY enters the Stop state and causes no interrupts. */
        unsigned int  reserved     : 16; /* bit[16-31]:  */
    } reg;
} SOC_DSS_DSI_LP_RD_TO_CNT_UNION;
#endif
#define SOC_DSS_DSI_LP_RD_TO_CNT_lp_rd_to_cnt_START  (0)
#define SOC_DSS_DSI_LP_RD_TO_CNT_lp_rd_to_cnt_END    (15)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_HS_WR_TO_CNT_UNION
 结构说明  : HS_WR_TO_CNT 寄存器结构定义。地址偏移量:0x0084，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hs_wr_to_cnt  : 16; /* bit[0-15] : This field sets a period for which the DWC_mipi_dsi_host keeps the link inactive after sending a high-speed write operation. This period is measured in cycles of lanebyteclk. The counting starts when the D-PHY enters the Stop state and causes no interrupts. */
        unsigned int  reserved_0    : 8;  /* bit[16-23]:  */
        unsigned int  presp_to_mode : 1;  /* bit[24]   : When set to 1, this bit ensures that the peripheral response timeout caused by hs_wr_to_cnt is used only once per eDPI frame, when both the following conditions are met:
                                                         ■ dpivsync_edpiwms has risen and fallen.
                                                         ■ Packets originated from eDPI have been transmitted and its FIFO is empty again.
                                                         In this scenario no non-eDPI requests are sent to the D-PHY, even if there is traffic from generic or DBI ready to be sent, making it return to stop state. When it does so, PRESP_TO counter is activated and only when it finishes does the controller send any other traffic that is ready.
                                                         Dependency: DSI_DATAINTERFACE = 4. Otherwise, this bit is 
                                                         reserved. */
        unsigned int  reserved_1    : 7;  /* bit[25-31]:  */
    } reg;
} SOC_DSS_DSI_HS_WR_TO_CNT_UNION;
#endif
#define SOC_DSS_DSI_HS_WR_TO_CNT_hs_wr_to_cnt_START   (0)
#define SOC_DSS_DSI_HS_WR_TO_CNT_hs_wr_to_cnt_END     (15)
#define SOC_DSS_DSI_HS_WR_TO_CNT_presp_to_mode_START  (24)
#define SOC_DSS_DSI_HS_WR_TO_CNT_presp_to_mode_END    (24)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_LP_WR_TO_CNT_UNION
 结构说明  : LP_WR_TO_CNT 寄存器结构定义。地址偏移量:0x0088，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lp_wr_to_cnt : 16; /* bit[0-15] : This field sets a period for which the DWC_mipi_dsi_host keeps the link still, after sending a low-power write operation. This period is measured in cycles of lanebyteclk. The counting starts when the D-PHY enters the Stop state and causes no interrupts. */
        unsigned int  reserved     : 16; /* bit[16-31]:  */
    } reg;
} SOC_DSS_DSI_LP_WR_TO_CNT_UNION;
#endif
#define SOC_DSS_DSI_LP_WR_TO_CNT_lp_wr_to_cnt_START  (0)
#define SOC_DSS_DSI_LP_WR_TO_CNT_lp_wr_to_cnt_END    (15)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_BTA_TO_CNT_UNION
 结构说明  : BTA_TO_CNT 寄存器结构定义。地址偏移量:0x008C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bta_to_cnt : 16; /* bit[0-15] : This field sets a period for which the DWC_mipi_dsi_host keeps the link still, after completing a Bus Turn-Around. This period is measured in cycles of lanebyteclk. The counting starts when the D-PHY enters the Stop state and causes no interrupts. */
        unsigned int  reserved   : 16; /* bit[16-31]:  */
    } reg;
} SOC_DSS_DSI_BTA_TO_CNT_UNION;
#endif
#define SOC_DSS_DSI_BTA_TO_CNT_bta_to_cnt_START  (0)
#define SOC_DSS_DSI_BTA_TO_CNT_bta_to_cnt_END    (15)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_SDF_3D_UNION
 结构说明  : SDF_3D 寄存器结构定义。地址偏移量:0x0090，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode_3d      : 2;  /* bit[0-1]  : This field defines the 3D mode on/off and display orientation:
                                                        ■ 00: 3D mode off (2D mode on)
                                                        ■ 01: 3D mode on, portrait orientation
                                                        ■ 10: 3D mode on, landscape orientation
                                                        ■ 11: Reserved */
        unsigned int  format_3d    : 2;  /* bit[2-3]  : This field defines the 3D image format:
                                                        ■ 00: Line (alternating lines of left and right data)
                                                        ■ 01: Frame (alternating frames of left and right data)
                                                        ■ 10: Pixel (alternating pixels of left and right data)
                                                        ■ 11: Reserved */
        unsigned int  second_vsync : 1;  /* bit[4]    : This field defines whether there is a second VSYNC pulse between 
                                                        Left and Right Images, when 3D Image Format is Frame-based:
                                                        ■ 0: No sync pulses between left and right data
                                                        ■ 1: Sync pulse (HSYNC, VSYNC, blanking) between left and right data */
        unsigned int  right_first  : 1;  /* bit[5]    : This bit defines the left or right order:
                                                        ■ 0: Left eye data is sent first, and then the right eye data is sent.
                                                        ■ 1: Right eye data is sent first, and then the left eye data is sent. */
        unsigned int  reserved_0   : 10; /* bit[6-15] :  */
        unsigned int  send_3d_cfg  : 1;  /* bit[16]   : When set, causes the next VSS packet to include 3D control payload in every VSS packet. */
        unsigned int  reserved_1   : 15; /* bit[17-31]:  */
    } reg;
} SOC_DSS_DSI_SDF_3D_UNION;
#endif
#define SOC_DSS_DSI_SDF_3D_mode_3d_START       (0)
#define SOC_DSS_DSI_SDF_3D_mode_3d_END         (1)
#define SOC_DSS_DSI_SDF_3D_format_3d_START     (2)
#define SOC_DSS_DSI_SDF_3D_format_3d_END       (3)
#define SOC_DSS_DSI_SDF_3D_second_vsync_START  (4)
#define SOC_DSS_DSI_SDF_3D_second_vsync_END    (4)
#define SOC_DSS_DSI_SDF_3D_right_first_START   (5)
#define SOC_DSS_DSI_SDF_3D_right_first_END     (5)
#define SOC_DSS_DSI_SDF_3D_send_3d_cfg_START   (16)
#define SOC_DSS_DSI_SDF_3D_send_3d_cfg_END     (16)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_LPCLK_CTRL_UNION
 结构说明  : LPCLK_CTRL 寄存器结构定义。地址偏移量:0x0094，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  phy_txrequestclkhs : 1;  /* bit[0]   : This bit controls the D-PHY PPI txrequestclkhs signal. */
        unsigned int  auto_clklane_ctrl  : 1;  /* bit[1]   : This bit enables the automatic mechanism to stop providing clock in 
                                                             the clock lane when time allows. */
        unsigned int  reserved           : 30; /* bit[2-31]:  */
    } reg;
} SOC_DSS_DSI_LPCLK_CTRL_UNION;
#endif
#define SOC_DSS_DSI_LPCLK_CTRL_phy_txrequestclkhs_START  (0)
#define SOC_DSS_DSI_LPCLK_CTRL_phy_txrequestclkhs_END    (0)
#define SOC_DSS_DSI_LPCLK_CTRL_auto_clklane_ctrl_START   (1)
#define SOC_DSS_DSI_LPCLK_CTRL_auto_clklane_ctrl_END     (1)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_PHY_TMR_LPCLK_CFG_UNION
 结构说明  : PHY_TMR_LPCLK_CFG 寄存器结构定义。地址偏移量:0x0098，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  phy_clklp2hs_time : 10; /* bit[0-9]  : This field configures the maximum time that the D-PHY clock lane takes to go from low-power to high-speed transmission measured in lane byte clock cycles. */
        unsigned int  reserved_0        : 6;  /* bit[10-15]:  */
        unsigned int  phy_clkhs2lp_time : 10; /* bit[16-25]: This field configures the maximum time that the D-PHY clock lane takes to go from high-speed to low-power transmission measured in lane byte clock cycles. */
        unsigned int  reserved_1        : 6;  /* bit[26-31]:  */
    } reg;
} SOC_DSS_DSI_PHY_TMR_LPCLK_CFG_UNION;
#endif
#define SOC_DSS_DSI_PHY_TMR_LPCLK_CFG_phy_clklp2hs_time_START  (0)
#define SOC_DSS_DSI_PHY_TMR_LPCLK_CFG_phy_clklp2hs_time_END    (9)
#define SOC_DSS_DSI_PHY_TMR_LPCLK_CFG_phy_clkhs2lp_time_START  (16)
#define SOC_DSS_DSI_PHY_TMR_LPCLK_CFG_phy_clkhs2lp_time_END    (25)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_PHY_TMR_CFG_UNION
 结构说明  : PHY_TMR_CFG 寄存器结构定义。地址偏移量:0x009C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  max_rd_time    : 15; /* bit[0-14] : This field configures the maximum time required to perform a read command in lane byte clock cycles. This register can only be modified when no read command is in progress. */
        unsigned int  reserved       : 1;  /* bit[15]   :  */
        unsigned int  phy_lp2hs_time : 8;  /* bit[16-23]: This field configures the maximum time that the D-PHY data lanes take to go from low-power to high-speed transmission measured in lane byte clock cycles. */
        unsigned int  phy_hs2lp_time : 8;  /* bit[24-31]: This field configures the maximum time that the D-PHY data lanes take to go from high-speed to low-power transmission measured in lane byte clock cycles. */
    } reg;
} SOC_DSS_DSI_PHY_TMR_CFG_UNION;
#endif
#define SOC_DSS_DSI_PHY_TMR_CFG_max_rd_time_START     (0)
#define SOC_DSS_DSI_PHY_TMR_CFG_max_rd_time_END       (14)
#define SOC_DSS_DSI_PHY_TMR_CFG_phy_lp2hs_time_START  (16)
#define SOC_DSS_DSI_PHY_TMR_CFG_phy_lp2hs_time_END    (23)
#define SOC_DSS_DSI_PHY_TMR_CFG_phy_hs2lp_time_START  (24)
#define SOC_DSS_DSI_PHY_TMR_CFG_phy_hs2lp_time_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_PHY_RSTZ_UNION
 结构说明  : PHY_RSTZ 寄存器结构定义。地址偏移量:0x00A0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  phy_shutdownz : 1;  /* bit[0]   : When set to 0, this bit places the D-PHY macro in power-down state. */
        unsigned int  phy_rstz      : 1;  /* bit[1]   : When set to 0, this bit places the digital section of the D-PHY in the reset state. */
        unsigned int  phy_enableclk : 1;  /* bit[2]   : When set to1, this bit enables the D-PHY Clock Lane module. */
        unsigned int  phy_forcepll  : 1;  /* bit[3]   : When the D-PHY is in ULPS, this bit enables the D-PHY PLL.
                                                        Dependency: DSI_HOST_FPGA = 0. Otherwise, this bit is reserved. */
        unsigned int  reserved      : 28; /* bit[4-31]:  */
    } reg;
} SOC_DSS_DSI_PHY_RSTZ_UNION;
#endif
#define SOC_DSS_DSI_PHY_RSTZ_phy_shutdownz_START  (0)
#define SOC_DSS_DSI_PHY_RSTZ_phy_shutdownz_END    (0)
#define SOC_DSS_DSI_PHY_RSTZ_phy_rstz_START       (1)
#define SOC_DSS_DSI_PHY_RSTZ_phy_rstz_END         (1)
#define SOC_DSS_DSI_PHY_RSTZ_phy_enableclk_START  (2)
#define SOC_DSS_DSI_PHY_RSTZ_phy_enableclk_END    (2)
#define SOC_DSS_DSI_PHY_RSTZ_phy_forcepll_START   (3)
#define SOC_DSS_DSI_PHY_RSTZ_phy_forcepll_END     (3)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_PHY_IF_CFG_UNION
 结构说明  : PHY_IF_CFG 寄存器结构定义。地址偏移量:0x00A4，初值:0x00000003，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  n_lanes            : 2;  /* bit[0-1]  : This field configures the number of active data lanes:
                                                              ■ 00: One data lane (lane 0)
                                                              ■ 01: Two data lanes (lanes 0 and 1)
                                                              ■ 10: Three data lanes (lanes 0, 1, and 2)
                                                              ■ 11: Four data lanes (lanes 0, 1, 2, and 3) */
        unsigned int  reserved_0         : 6;  /* bit[2-7]  :  */
        unsigned int  phy_stop_wait_time : 8;  /* bit[8-15] : This field configures the minimum wait period to request a high-speed transmission after the Stop state. */
        unsigned int  reserved_1         : 16; /* bit[16-31]:  */
    } reg;
} SOC_DSS_DSI_PHY_IF_CFG_UNION;
#endif
#define SOC_DSS_DSI_PHY_IF_CFG_n_lanes_START             (0)
#define SOC_DSS_DSI_PHY_IF_CFG_n_lanes_END               (1)
#define SOC_DSS_DSI_PHY_IF_CFG_phy_stop_wait_time_START  (8)
#define SOC_DSS_DSI_PHY_IF_CFG_phy_stop_wait_time_END    (15)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_PHY_ULPS_CTRL_UNION
 结构说明  : PHY_ULPS_CTRL 寄存器结构定义。地址偏移量:0x00A8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  phy_txrequlpsclk  : 1;  /* bit[0]   : ULPS mode Request on clock lane. */
        unsigned int  phy_txexitulpsclk : 1;  /* bit[1]   : ULPS mode Exit on clock lane. */
        unsigned int  phy_txrequlpslan  : 1;  /* bit[2]   : ULPS mode Request on all active data lanes. */
        unsigned int  phy_txexitulpslan : 1;  /* bit[3]   : ULPS mode Exit on all active data lanes. */
        unsigned int  reserved          : 28; /* bit[4-31]:  */
    } reg;
} SOC_DSS_DSI_PHY_ULPS_CTRL_UNION;
#endif
#define SOC_DSS_DSI_PHY_ULPS_CTRL_phy_txrequlpsclk_START   (0)
#define SOC_DSS_DSI_PHY_ULPS_CTRL_phy_txrequlpsclk_END     (0)
#define SOC_DSS_DSI_PHY_ULPS_CTRL_phy_txexitulpsclk_START  (1)
#define SOC_DSS_DSI_PHY_ULPS_CTRL_phy_txexitulpsclk_END    (1)
#define SOC_DSS_DSI_PHY_ULPS_CTRL_phy_txrequlpslan_START   (2)
#define SOC_DSS_DSI_PHY_ULPS_CTRL_phy_txrequlpslan_END     (2)
#define SOC_DSS_DSI_PHY_ULPS_CTRL_phy_txexitulpslan_START  (3)
#define SOC_DSS_DSI_PHY_ULPS_CTRL_phy_txexitulpslan_END    (3)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_PHY_TX_TRIGGERS_UNION
 结构说明  : PHY_TX_TRIGGERS 寄存器结构定义。地址偏移量:0x00AC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  phy_tx_triggers : 4;  /* bit[0-3] : This field controls the trigger transmissions. */
        unsigned int  reserved        : 28; /* bit[4-31]:  */
    } reg;
} SOC_DSS_DSI_PHY_TX_TRIGGERS_UNION;
#endif
#define SOC_DSS_DSI_PHY_TX_TRIGGERS_phy_tx_triggers_START  (0)
#define SOC_DSS_DSI_PHY_TX_TRIGGERS_phy_tx_triggers_END    (3)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_PHY_STATUS_UNION
 结构说明  : PHY_STATUS 寄存器结构定义。地址偏移量:0x00B0，初值:0x00001528，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  phy_lock               : 1;  /* bit[0]    : This bit indicates the status of phylock D-PHY signal. */
        unsigned int  phy_direction          : 1;  /* bit[1]    : This bit indicates the status of phydirection D-PHY signal. */
        unsigned int  phy_stopstateclklane   : 1;  /* bit[2]    : This bit indicates the status of phystopstateclklane D-PHY signal. */
        unsigned int  phy_ulpsactivenotclk   : 1;  /* bit[3]    : This bit indicates the status of phyulpsactivenotclk D-PHY signal. */
        unsigned int  phy_stopstate0lane     : 1;  /* bit[4]    : This bit indicates the status of phystopstate0lane D-PHY signal. */
        unsigned int  phy_ulpsactivenot0lane : 1;  /* bit[5]    : This bit indicates the status of ulpsactivenot0lane D-PHY signal. */
        unsigned int  phy_rxulpsesc0lane     : 1;  /* bit[6]    : This bit indicates the status of rxulpsesc0lane D-PHY signal. */
        unsigned int  phy_stopstate1lane     : 1;  /* bit[7]    : This bit indicates the status of phystopstate1lane D-PHY signal.
                                                                  Dependency: DSI_HOST_NUMBER_OF_LANES > 1
                                                                  If DSI_HOST_NUMBER_OF_LANES <= 1, this bit is reserved. */
        unsigned int  phy_ulpsactivenot1lane : 1;  /* bit[8]    : This bit indicates the status of ulpsactivenot1lane D-PHY signal.
                                                                  Dependency: DSI_HOST_NUMBER_OF_LANES > 1 
                                                                  If DSI_HOST_NUMBER_OF_LANES <= 1, this bit is reserved. */
        unsigned int  phy_stopstate2lane     : 1;  /* bit[9]    : This bit indicates the status of phystopstate2lane D-PHY signal.
                                                                  Dependency: DSI_HOST_NUMBER_OF_LANES > 2
                                                                  If DSI_HOST_NUMBER_OF_LANES <= 2, this bit is reserved. */
        unsigned int  phy_ulpsactivenot2lane : 1;  /* bit[10]   : This bit indicates the status of ulpsactivenot2lane D-PHY signal.
                                                                  Dependency: DSI_HOST_NUMBER_OF_LANES > 2
                                                                  If DSI_HOST_NUMBER_OF_LANES <= 2, this bit is reserved. */
        unsigned int  phy_stopstate3lane     : 1;  /* bit[11]   : This bit indicates the status of phystopstate3lane D-PHY signal.
                                                                  Dependency: DSI_HOST_NUMBER_OF_LANES > 3
                                                                  If DSI_HOST_NUMBER_OF_LANES <= 3, this bit is reserved. */
        unsigned int  phy_ulpsactivenot3lane : 1;  /* bit[12]   : This bit indicates the status of ulpsactivenot3lane D-PHY signal.
                                                                  Dependency: DSI_HOST_NUMBER_OF_LANES > 3 
                                                                  If DSI_HOST_NUMBER_OF_LANES <= 3, this bit is reserved. */
        unsigned int  reserved               : 19; /* bit[13-31]:  */
    } reg;
} SOC_DSS_DSI_PHY_STATUS_UNION;
#endif
#define SOC_DSS_DSI_PHY_STATUS_phy_lock_START                (0)
#define SOC_DSS_DSI_PHY_STATUS_phy_lock_END                  (0)
#define SOC_DSS_DSI_PHY_STATUS_phy_direction_START           (1)
#define SOC_DSS_DSI_PHY_STATUS_phy_direction_END             (1)
#define SOC_DSS_DSI_PHY_STATUS_phy_stopstateclklane_START    (2)
#define SOC_DSS_DSI_PHY_STATUS_phy_stopstateclklane_END      (2)
#define SOC_DSS_DSI_PHY_STATUS_phy_ulpsactivenotclk_START    (3)
#define SOC_DSS_DSI_PHY_STATUS_phy_ulpsactivenotclk_END      (3)
#define SOC_DSS_DSI_PHY_STATUS_phy_stopstate0lane_START      (4)
#define SOC_DSS_DSI_PHY_STATUS_phy_stopstate0lane_END        (4)
#define SOC_DSS_DSI_PHY_STATUS_phy_ulpsactivenot0lane_START  (5)
#define SOC_DSS_DSI_PHY_STATUS_phy_ulpsactivenot0lane_END    (5)
#define SOC_DSS_DSI_PHY_STATUS_phy_rxulpsesc0lane_START      (6)
#define SOC_DSS_DSI_PHY_STATUS_phy_rxulpsesc0lane_END        (6)
#define SOC_DSS_DSI_PHY_STATUS_phy_stopstate1lane_START      (7)
#define SOC_DSS_DSI_PHY_STATUS_phy_stopstate1lane_END        (7)
#define SOC_DSS_DSI_PHY_STATUS_phy_ulpsactivenot1lane_START  (8)
#define SOC_DSS_DSI_PHY_STATUS_phy_ulpsactivenot1lane_END    (8)
#define SOC_DSS_DSI_PHY_STATUS_phy_stopstate2lane_START      (9)
#define SOC_DSS_DSI_PHY_STATUS_phy_stopstate2lane_END        (9)
#define SOC_DSS_DSI_PHY_STATUS_phy_ulpsactivenot2lane_START  (10)
#define SOC_DSS_DSI_PHY_STATUS_phy_ulpsactivenot2lane_END    (10)
#define SOC_DSS_DSI_PHY_STATUS_phy_stopstate3lane_START      (11)
#define SOC_DSS_DSI_PHY_STATUS_phy_stopstate3lane_END        (11)
#define SOC_DSS_DSI_PHY_STATUS_phy_ulpsactivenot3lane_START  (12)
#define SOC_DSS_DSI_PHY_STATUS_phy_ulpsactivenot3lane_END    (12)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_PHY_TST_CTRL0_UNION
 结构说明  : PHY_TST_CTRL0 寄存器结构定义。地址偏移量:0x00B4，初值:0x00000001，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  phy_testclr : 1;  /* bit[0]   : PHY test interface clear (active high). */
        unsigned int  phy_testclk : 1;  /* bit[1]   : This bit is used to clock the TESTDIN bus into the D-PHY. */
        unsigned int  reserved    : 30; /* bit[2-31]:  */
    } reg;
} SOC_DSS_DSI_PHY_TST_CTRL0_UNION;
#endif
#define SOC_DSS_DSI_PHY_TST_CTRL0_phy_testclr_START  (0)
#define SOC_DSS_DSI_PHY_TST_CTRL0_phy_testclr_END    (0)
#define SOC_DSS_DSI_PHY_TST_CTRL0_phy_testclk_START  (1)
#define SOC_DSS_DSI_PHY_TST_CTRL0_phy_testclk_END    (1)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_PHY_TST_CTRL1_UNION
 结构说明  : PHY_TST_CTRL1 寄存器结构定义。地址偏移量:0x00B8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  phy_testdin  : 8;  /* bit[0-7]  : PHY test interface input 8-bit data bus for internal register programming and test functionalities access. */
        unsigned int  phy_testdout : 8;  /* bit[8-15] : PHY output 8-bit data bus for read-back and internal probing functionalities. */
        unsigned int  phy_testen   : 1;  /* bit[16]   : PHY test interface operation selector:
                                                        ■ 1: The address write operation is set on the falling edge of the 
                                                        testclk signal.
                                                        ■ 0: The data write operation is set on the rising edge of the testclk 
                                                        signal. */
        unsigned int  reserved     : 15; /* bit[17-31]:  */
    } reg;
} SOC_DSS_DSI_PHY_TST_CTRL1_UNION;
#endif
#define SOC_DSS_DSI_PHY_TST_CTRL1_phy_testdin_START   (0)
#define SOC_DSS_DSI_PHY_TST_CTRL1_phy_testdin_END     (7)
#define SOC_DSS_DSI_PHY_TST_CTRL1_phy_testdout_START  (8)
#define SOC_DSS_DSI_PHY_TST_CTRL1_phy_testdout_END    (15)
#define SOC_DSS_DSI_PHY_TST_CTRL1_phy_testen_START    (16)
#define SOC_DSS_DSI_PHY_TST_CTRL1_phy_testen_END      (16)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_INT_ST0_UNION
 结构说明  : INT_ST0 寄存器结构定义。地址偏移量:0x00BC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ack_with_err_0  : 1;  /* bit[0]    : This bit retrieves the SoT error from the Acknowledge error report. */
        unsigned int  ack_with_err_1  : 1;  /* bit[1]    : This bit retrieves the SoT Sync error from the Acknowledge error report. */
        unsigned int  ack_with_err_2  : 1;  /* bit[2]    : This bit retrieves the EoT Sync error from the Acknowledge error report. */
        unsigned int  ack_with_err_3  : 1;  /* bit[3]    : This bit retrieves the Escape Mode Entry Command error from the Acknowledge error report. */
        unsigned int  ack_with_err_4  : 1;  /* bit[4]    : This bit retrieves the LP Transmit Sync error from the Acknowledge error report. */
        unsigned int  ack_with_err_5  : 1;  /* bit[5]    : This bit retrieves the Peripheral Timeout error from the Acknowledge Error report. */
        unsigned int  ack_with_err_6  : 1;  /* bit[6]    : This bit retrieves the False Control error from the Acknowledge error report. */
        unsigned int  ack_with_err_7  : 1;  /* bit[7]    : This bit retrieves the reserved (specific to device) from the Acknowledge error report. */
        unsigned int  ack_with_err_8  : 1;  /* bit[8]    : This bit retrieves the ECC error, single-bit (detected and corrected) from the Acknowledge error report. */
        unsigned int  ack_with_err_9  : 1;  /* bit[9]    : This bit retrieves the ECC error, multi-bit (detected, not corrected) from the Acknowledge error report. */
        unsigned int  ack_with_err_10 : 1;  /* bit[10]   : This bit retrieves the checksum error (long packet only) from the Acknowledge error report. */
        unsigned int  ack_with_err_11 : 1;  /* bit[11]   : This bit retrieves the not recognized DSI data type from the Acknowledge error report. */
        unsigned int  ack_with_err_12 : 1;  /* bit[12]   : This bit retrieves the DSI VC ID Invalid from the Acknowledge error report. */
        unsigned int  ack_with_err_13 : 1;  /* bit[13]   : This bit retrieves the invalid transmission length from the Acknowledge error report. */
        unsigned int  ack_with_err_14 : 1;  /* bit[14]   : This bit retrieves the reserved (specific to device) from the Acknowledge error report. */
        unsigned int  ack_with_err_15 : 1;  /* bit[15]   : This bit retrieves the DSI protocol violation from the Acknowledge error report. */
        unsigned int  dphy_errors_0   : 1;  /* bit[16]   : This bit indicates ErrEsc escape entry error from Lane 0. */
        unsigned int  dphy_errors_1   : 1;  /* bit[17]   : This bit indicates ErrSyncEsc low-power data transmission 
                                                           synchronization error from Lane 0. */
        unsigned int  dphy_errors_2   : 1;  /* bit[18]   : This bit indicates the ErrControl error from Lane 0. */
        unsigned int  dphy_errors_3   : 1;  /* bit[19]   : This bit indicates the LP0 contention error ErrContentionLP0 from Lane 0. */
        unsigned int  dphy_errors_4   : 1;  /* bit[20]   : This bit indicates the LP1 contention error ErrContentionLP1 from Lane 0. */
        unsigned int  reserved        : 11; /* bit[21-31]:  */
    } reg;
} SOC_DSS_DSI_INT_ST0_UNION;
#endif
#define SOC_DSS_DSI_INT_ST0_ack_with_err_0_START   (0)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_0_END     (0)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_1_START   (1)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_1_END     (1)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_2_START   (2)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_2_END     (2)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_3_START   (3)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_3_END     (3)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_4_START   (4)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_4_END     (4)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_5_START   (5)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_5_END     (5)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_6_START   (6)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_6_END     (6)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_7_START   (7)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_7_END     (7)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_8_START   (8)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_8_END     (8)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_9_START   (9)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_9_END     (9)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_10_START  (10)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_10_END    (10)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_11_START  (11)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_11_END    (11)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_12_START  (12)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_12_END    (12)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_13_START  (13)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_13_END    (13)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_14_START  (14)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_14_END    (14)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_15_START  (15)
#define SOC_DSS_DSI_INT_ST0_ack_with_err_15_END    (15)
#define SOC_DSS_DSI_INT_ST0_dphy_errors_0_START    (16)
#define SOC_DSS_DSI_INT_ST0_dphy_errors_0_END      (16)
#define SOC_DSS_DSI_INT_ST0_dphy_errors_1_START    (17)
#define SOC_DSS_DSI_INT_ST0_dphy_errors_1_END      (17)
#define SOC_DSS_DSI_INT_ST0_dphy_errors_2_START    (18)
#define SOC_DSS_DSI_INT_ST0_dphy_errors_2_END      (18)
#define SOC_DSS_DSI_INT_ST0_dphy_errors_3_START    (19)
#define SOC_DSS_DSI_INT_ST0_dphy_errors_3_END      (19)
#define SOC_DSS_DSI_INT_ST0_dphy_errors_4_START    (20)
#define SOC_DSS_DSI_INT_ST0_dphy_errors_4_END      (20)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_INT_ST1_UNION
 结构说明  : INT_ST1 寄存器结构定义。地址偏移量:0x00C0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  to_hs_tx             : 1;  /* bit[0]    : This bit indicates that the high-speed transmission timeout counter reached the end and contention is detected. */
        unsigned int  to_lp_rx             : 1;  /* bit[1]    : This bit indicates that the low-power reception timeout counter reached the end and contention is detected. */
        unsigned int  ecc_single_err       : 1;  /* bit[2]    : This bit indicates that the ECC single error is detected and corrected in a received packet. */
        unsigned int  ecc_milti_err        : 1;  /* bit[3]    : This bit indicates that the ECC multiple error is detected in a received packet. */
        unsigned int  crc_err              : 1;  /* bit[4]    : This bit indicates that the CRC error is detected in the received packet payload.
                                                                Dependency: DSI_DATAINTERFACE = 1 or DSI_DATAINTERFACE = 3 or DSI_GENERIC = 1. Otherwise, this bit is reserved. */
        unsigned int  pkt_size_err         : 1;  /* bit[5]    : This bit indicates that the packet size error is detected during the packet reception. */
        unsigned int  eopt_err             : 1;  /* bit[6]    : This bit indicates that the EoTp packet is not received at the end of the incoming peripheral transmission. */
        unsigned int  dpi_pld_wr_err       : 1;  /* bit[7]    : This bit indicates that during a DPI pixel line storage, the payload FIFO 
                                                                becomes full and the data stored is corrupted.
                                                                Dependency: DSI_DATAINTERFACE = 2 or DSI_DATAINTERFACE = 3 or DSI_DATAINTERFACE = 4. Otherwise, this bit is reserved. */
        unsigned int  gen_cmd_wr_err       : 1;  /* bit[8]    : This bit indicates that the system tried to write a command through the Generic interface and the FIFO is full. Therefore, the command is not written.
                                                                Dependency: DSI_GENERIC = 1. Otherwise, this bit is reserved */
        unsigned int  gen_pld_wr_err       : 1;  /* bit[9]    : This bit indicates that the system tried to write a payload data through the Generic interface and the FIFO is full. Therefore, the payload is not written.
                                                                Dependency: DSI_GENERIC = 1. Otherwise, this bit is reserved */
        unsigned int  gen_pld_send_err     : 1;  /* bit[10]   : This bit indicates that during a Generic interface packet build, the payload FIFO becomes empty and corrupt data is sent.
                                                                Dependency: DSI_GENERIC = 1. Otherwise, this bit is reserved */
        unsigned int  gen_pld_rd_err       : 1;  /* bit[11]   : This bit indicates that during a DCS read data, the payload FIFO becomes empty and the data sent to the interface is corrupted.
                                                                Dependency: DSI_GENERIC = 1. Otherwise, this bit is reserved. */
        unsigned int  gen_pld_recv_err     : 1;  /* bit[12]   : This bit indicates that during a generic interface packet read back, the payload FIFO becomes full and the received data is corrupted.
                                                                Dependency: DSI_GENERIC = 1
                                                                If DSI_GENERIC = 0, this bit is reserved. */
        unsigned int  dbi_cmd_wr_err       : 1;  /* bit[13]   : This bit indicates that the system tried to write a command through the DBI but the command FIFO is full. Therefore, the command is not written.
                                                                Dependency: DSI_DATAINTERFACE = 1 or DSI_DATAINTERFACE = 3. Otherwise, this bit is reserved. */
        unsigned int  dbi_pld_wr_err       : 1;  /* bit[14]   : This bit indicates that the system tried to write the payload data through the DBI interface and the FIFO is full. Therefore, the command is not written.
                                                                Dependency: DSI_DATAINTERFACE = 1 or DSI_DATAINTERFACE = 3. Otherwise, this bit is reserved. */
        unsigned int  dbi_pld_rd_err       : 1;  /* bit[15]   : This bit indicates that during a DCS read data, the payload FIFO goes 
                                                                empty and the data sent to the interface is corrupted.
                                                                Dependency: DSI_DATAINTERFACE = 1 or DSI_DATAINTERFACE = 3. Otherwise, this bit is reserved. */
        unsigned int  dbi_pld_recv_err     : 1;  /* bit[16]   : This bit indicates that during a DBI read back packet, the payload FIFO becomes full and the received data is corrupted.
                                                                Dependency: DSI_DATAINTERFACE = 1 or DSI_DATAINTERFACE = 3. Otherwise, this bit is reserved. */
        unsigned int  dbi_illegal_comm_err : 1;  /* bit[17]   : This bit indicates that an attempt to write an illegal command on the DBI interface is made and the core is blocked by transmission.
                                                                Dependency: DSI_DATAINTERFACE = 1 or DSI_DATAINTERFACE = 3. Otherwise, this bit is reserved. */
        unsigned int  reserved             : 14; /* bit[18-31]:  */
    } reg;
} SOC_DSS_DSI_INT_ST1_UNION;
#endif
#define SOC_DSS_DSI_INT_ST1_to_hs_tx_START              (0)
#define SOC_DSS_DSI_INT_ST1_to_hs_tx_END                (0)
#define SOC_DSS_DSI_INT_ST1_to_lp_rx_START              (1)
#define SOC_DSS_DSI_INT_ST1_to_lp_rx_END                (1)
#define SOC_DSS_DSI_INT_ST1_ecc_single_err_START        (2)
#define SOC_DSS_DSI_INT_ST1_ecc_single_err_END          (2)
#define SOC_DSS_DSI_INT_ST1_ecc_milti_err_START         (3)
#define SOC_DSS_DSI_INT_ST1_ecc_milti_err_END           (3)
#define SOC_DSS_DSI_INT_ST1_crc_err_START               (4)
#define SOC_DSS_DSI_INT_ST1_crc_err_END                 (4)
#define SOC_DSS_DSI_INT_ST1_pkt_size_err_START          (5)
#define SOC_DSS_DSI_INT_ST1_pkt_size_err_END            (5)
#define SOC_DSS_DSI_INT_ST1_eopt_err_START              (6)
#define SOC_DSS_DSI_INT_ST1_eopt_err_END                (6)
#define SOC_DSS_DSI_INT_ST1_dpi_pld_wr_err_START        (7)
#define SOC_DSS_DSI_INT_ST1_dpi_pld_wr_err_END          (7)
#define SOC_DSS_DSI_INT_ST1_gen_cmd_wr_err_START        (8)
#define SOC_DSS_DSI_INT_ST1_gen_cmd_wr_err_END          (8)
#define SOC_DSS_DSI_INT_ST1_gen_pld_wr_err_START        (9)
#define SOC_DSS_DSI_INT_ST1_gen_pld_wr_err_END          (9)
#define SOC_DSS_DSI_INT_ST1_gen_pld_send_err_START      (10)
#define SOC_DSS_DSI_INT_ST1_gen_pld_send_err_END        (10)
#define SOC_DSS_DSI_INT_ST1_gen_pld_rd_err_START        (11)
#define SOC_DSS_DSI_INT_ST1_gen_pld_rd_err_END          (11)
#define SOC_DSS_DSI_INT_ST1_gen_pld_recv_err_START      (12)
#define SOC_DSS_DSI_INT_ST1_gen_pld_recv_err_END        (12)
#define SOC_DSS_DSI_INT_ST1_dbi_cmd_wr_err_START        (13)
#define SOC_DSS_DSI_INT_ST1_dbi_cmd_wr_err_END          (13)
#define SOC_DSS_DSI_INT_ST1_dbi_pld_wr_err_START        (14)
#define SOC_DSS_DSI_INT_ST1_dbi_pld_wr_err_END          (14)
#define SOC_DSS_DSI_INT_ST1_dbi_pld_rd_err_START        (15)
#define SOC_DSS_DSI_INT_ST1_dbi_pld_rd_err_END          (15)
#define SOC_DSS_DSI_INT_ST1_dbi_pld_recv_err_START      (16)
#define SOC_DSS_DSI_INT_ST1_dbi_pld_recv_err_END        (16)
#define SOC_DSS_DSI_INT_ST1_dbi_illegal_comm_err_START  (17)
#define SOC_DSS_DSI_INT_ST1_dbi_illegal_comm_err_END    (17)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_INT_MSK0_UNION
 结构说明  : INT_MSK0 寄存器结构定义。地址偏移量:0x00C4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ack_with_err_msk_0  : 1;  /* bit[0]    : This bit retrieves the SoT error from the Acknowledge error report. */
        unsigned int  ack_with_err_msk_1  : 1;  /* bit[1]    : This bit retrieves the SoT Sync error from the Acknowledge error report. */
        unsigned int  ack_with_err_msk_2  : 1;  /* bit[2]    : This bit retrieves the EoT Sync error from the Acknowledge error report. */
        unsigned int  ack_with_err_msk_3  : 1;  /* bit[3]    : This bit retrieves the Escape Mode Entry Command error from the Acknowledge error report. */
        unsigned int  ack_with_err_msk_4  : 1;  /* bit[4]    : This bit retrieves the LP Transmit Sync error from the Acknowledge error report. */
        unsigned int  ack_with_err_msk_5  : 1;  /* bit[5]    : This bit retrieves the Peripheral Timeout error from the Acknowledge error report. */
        unsigned int  ack_with_err_msk_6  : 1;  /* bit[6]    : This bit retrieves the False Control error from the Acknowledge error report. */
        unsigned int  ack_with_err_msk_7  : 1;  /* bit[7]    : This bit retrieves the reserved (specific to device) from the Acknowledge error report. */
        unsigned int  ack_with_err_msk_8  : 1;  /* bit[8]    : This bit retrieves the ECC error, single-bit (detected and corrected) from the Acknowledge error report. */
        unsigned int  ack_with_err_msk_9  : 1;  /* bit[9]    : This bit retrieves the ECC error, multi-bit (detected, not corrected) from the Acknowledge error report. */
        unsigned int  ack_with_err_msk_10 : 1;  /* bit[10]   : This bit retrieves the checksum error (long packet only) from the Acknowledge error report. */
        unsigned int  ack_with_err_msk_11 : 1;  /* bit[11]   : This bit retrieves the not recognized DSI data type from the Acknowledge error report. */
        unsigned int  ack_with_err_msk_12 : 1;  /* bit[12]   : This bit retrieves the DSI VC ID Invalid from the Acknowledge error report. */
        unsigned int  ack_with_err_msk_13 : 1;  /* bit[13]   : This bit retrieves the invalid transmission length from the Acknowledge error report. */
        unsigned int  ack_with_err_msk_14 : 1;  /* bit[14]   : This bit retrieves the reserved (specific to device) from the Acknowledge error report. */
        unsigned int  ack_with_err_msk_15 : 1;  /* bit[15]   : This bit retrieves the DSI protocol violation from the Acknowledge error report. */
        unsigned int  dphy_errors_msk_0   : 1;  /* bit[16]   : This bit indicates ErrEsc escape entry error from Lane 0. */
        unsigned int  dphy_errors_msk_1   : 1;  /* bit[17]   : This bit indicates ErrSyncEsc low-power data transmission 
                                                               synchronization error from Lane 0. */
        unsigned int  dphy_errors_msk_2   : 1;  /* bit[18]   : This bit indicates ErrControl control error from Lane 0. */
        unsigned int  dphy_errors_msk_3   : 1;  /* bit[19]   : This bit indicates the LP0 contention error ErrContentionLP0 from Lane 0. */
        unsigned int  dphy_errors_msk_4   : 1;  /* bit[20]   : This bit indicates the LP1 contention error ErrContentionLP1 from Lane 0. */
        unsigned int  reserved            : 11; /* bit[21-31]:  */
    } reg;
} SOC_DSS_DSI_INT_MSK0_UNION;
#endif
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_0_START   (0)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_0_END     (0)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_1_START   (1)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_1_END     (1)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_2_START   (2)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_2_END     (2)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_3_START   (3)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_3_END     (3)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_4_START   (4)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_4_END     (4)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_5_START   (5)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_5_END     (5)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_6_START   (6)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_6_END     (6)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_7_START   (7)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_7_END     (7)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_8_START   (8)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_8_END     (8)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_9_START   (9)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_9_END     (9)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_10_START  (10)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_10_END    (10)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_11_START  (11)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_11_END    (11)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_12_START  (12)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_12_END    (12)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_13_START  (13)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_13_END    (13)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_14_START  (14)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_14_END    (14)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_15_START  (15)
#define SOC_DSS_DSI_INT_MSK0_ack_with_err_msk_15_END    (15)
#define SOC_DSS_DSI_INT_MSK0_dphy_errors_msk_0_START    (16)
#define SOC_DSS_DSI_INT_MSK0_dphy_errors_msk_0_END      (16)
#define SOC_DSS_DSI_INT_MSK0_dphy_errors_msk_1_START    (17)
#define SOC_DSS_DSI_INT_MSK0_dphy_errors_msk_1_END      (17)
#define SOC_DSS_DSI_INT_MSK0_dphy_errors_msk_2_START    (18)
#define SOC_DSS_DSI_INT_MSK0_dphy_errors_msk_2_END      (18)
#define SOC_DSS_DSI_INT_MSK0_dphy_errors_msk_3_START    (19)
#define SOC_DSS_DSI_INT_MSK0_dphy_errors_msk_3_END      (19)
#define SOC_DSS_DSI_INT_MSK0_dphy_errors_msk_4_START    (20)
#define SOC_DSS_DSI_INT_MSK0_dphy_errors_msk_4_END      (20)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_INT_MSK1_UNION
 结构说明  : INT_MSK1 寄存器结构定义。地址偏移量:0x00C8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  to_hs_tx_msk             : 1;  /* bit[0]    : This bit indicates that the high-speed transmission timeout counter reached the end and contention is detected. */
        unsigned int  to_lp_rx_msk             : 1;  /* bit[1]    : This bit indicates that the low-power reception timeout counter reached the end and contention is detected. */
        unsigned int  ecc_single_err_msk       : 1;  /* bit[2]    : This bit indicates that the ECC single error is detected and corrected in a received packet. */
        unsigned int  ecc_milti_err_msk        : 1;  /* bit[3]    : This bit indicates that the ECC multiple error is detected in a received packet. */
        unsigned int  crc_err_msk              : 1;  /* bit[4]    : This bit indicates that the CRC error is detected in the received packet payload
                                                                    Dependency: DSI_DATAINTERFACE = 1 or DSI_DATAINTERFACE = 3 or DSI_GENERIC = 1. Otherwise, this bit is reserved. */
        unsigned int  pkt_size_err_msk         : 1;  /* bit[5]    : This bit indicates that the packet size error is detected during the packet reception. */
        unsigned int  eopt_err_msk             : 1;  /* bit[6]    : This bit indicates that the EoTp packet is not received at the end of the incoming peripheral transmission. */
        unsigned int  dpi_pld_wr_err_msk       : 1;  /* bit[7]    : This bit indicates that during a DPI pixel line storage, the payload FIFO becomes full and the data stored is corrupted.
                                                                    Dependency: DSI_DATAINTERFACE = 2 or DSI_DATAINTERFACE = 3 or DSI_DATAINTERFACE = 4. Otherwise, this bit is reserved. */
        unsigned int  gen_cmd_wr_err_msk       : 1;  /* bit[8]    : This bit indicates that the system tried to write a command through the Generic interface and the FIFO is full. Therefore, the command is not written.
                                                                    Dependency: DSI_GENERIC = 1. Otherwise, this bit is reserved. */
        unsigned int  gen_pld_wr_err_msk       : 1;  /* bit[9]    : This bit indicates that the system tried to write a payload data through the Generic interface and the FIFO is full. Therefore, the payload is not written.
                                                                    Dependency: DSI_GENERIC = 1. Otherwise, this bit is reserved. */
        unsigned int  gen_pld_send_err_msk     : 1;  /* bit[10]   : This bit indicates that during a Generic interface packet build, the payload FIFO becomes empty and corrupt data is sent.
                                                                    Dependency: DSI_GENERIC = 1. Otherwise, this bit is reserved. */
        unsigned int  gen_pld_rd_err_msk       : 1;  /* bit[11]   : This bit indicates that during a DCS read data, the payload FIFO becomes empty and the data sent to the interface is corrupted.
                                                                    Dependency: DSI_GENERIC = 1. Otherwise, this bit is reserved. */
        unsigned int  gen_pld_recv_err_msk     : 1;  /* bit[12]   : This bit indicates that during a generic interface packet read back, the payload FIFO becomes full and the received data is corrupted.
                                                                    Dependency: DSI_GENERIC = 1. Otherwise, this bit is reserved. */
        unsigned int  dbi_cmd_wr_err_msk       : 1;  /* bit[13]   : This bit indicates that the system tried to write a command through the DBI but the command FIFO is full. Therefore, the command is not written.
                                                                    Dependency: DSI_DATAINTERFACE = 1 or DSI_DATAINTERFACE = 3. 
                                                                    Otherwise, this bit is reserved. */
        unsigned int  dbi_pld_wr_err_msk       : 1;  /* bit[14]   : This bit indicates that the system tried to write the payload data through the DBI interface and the FIFO is full. Therefore, the command is not written.
                                                                    Dependency: DSI_DATAINTERFACE = 1 or DSI_DATAINTERFACE = 3. 
                                                                    Otherwise, this bit is reserved. */
        unsigned int  dbi_pld_rd_err_msk       : 1;  /* bit[15]   : This bit indicates that during a DCS read data, the payload FIFO goes 
                                                                    empty and the data sent to the interface is corrupted.
                                                                    Dependency: DSI_DATAINTERFACE = 1 or DSI_DATAINTERFACE = 3. 
                                                                    Otherwise, this bit is reserved. */
        unsigned int  dbi_pld_recv_err_msk     : 1;  /* bit[16]   : This bit indicates that during a DBI read back packet, the payload FIFO becomes full and the received data is corrupted.
                                                                    Dependency: DSI_DATAINTERFACE = 1 or DSI_DATAINTERFACE = 3. 
                                                                    Otherwise, this bit is reserved. */
        unsigned int  dbi_illegal_comm_err_msk : 1;  /* bit[17]   : This bit indicates that an attempt to write an illegal command on the DBI interface is made and the core is blocked by transmission.
                                                                    Dependency: DSI_DATAINTERFACE = 1 or DSI_DATAINTERFACE = 3. 
                                                                    Otherwise, this bit is reserved. */
        unsigned int  reserved                 : 14; /* bit[18-31]:  */
    } reg;
} SOC_DSS_DSI_INT_MSK1_UNION;
#endif
#define SOC_DSS_DSI_INT_MSK1_to_hs_tx_msk_START              (0)
#define SOC_DSS_DSI_INT_MSK1_to_hs_tx_msk_END                (0)
#define SOC_DSS_DSI_INT_MSK1_to_lp_rx_msk_START              (1)
#define SOC_DSS_DSI_INT_MSK1_to_lp_rx_msk_END                (1)
#define SOC_DSS_DSI_INT_MSK1_ecc_single_err_msk_START        (2)
#define SOC_DSS_DSI_INT_MSK1_ecc_single_err_msk_END          (2)
#define SOC_DSS_DSI_INT_MSK1_ecc_milti_err_msk_START         (3)
#define SOC_DSS_DSI_INT_MSK1_ecc_milti_err_msk_END           (3)
#define SOC_DSS_DSI_INT_MSK1_crc_err_msk_START               (4)
#define SOC_DSS_DSI_INT_MSK1_crc_err_msk_END                 (4)
#define SOC_DSS_DSI_INT_MSK1_pkt_size_err_msk_START          (5)
#define SOC_DSS_DSI_INT_MSK1_pkt_size_err_msk_END            (5)
#define SOC_DSS_DSI_INT_MSK1_eopt_err_msk_START              (6)
#define SOC_DSS_DSI_INT_MSK1_eopt_err_msk_END                (6)
#define SOC_DSS_DSI_INT_MSK1_dpi_pld_wr_err_msk_START        (7)
#define SOC_DSS_DSI_INT_MSK1_dpi_pld_wr_err_msk_END          (7)
#define SOC_DSS_DSI_INT_MSK1_gen_cmd_wr_err_msk_START        (8)
#define SOC_DSS_DSI_INT_MSK1_gen_cmd_wr_err_msk_END          (8)
#define SOC_DSS_DSI_INT_MSK1_gen_pld_wr_err_msk_START        (9)
#define SOC_DSS_DSI_INT_MSK1_gen_pld_wr_err_msk_END          (9)
#define SOC_DSS_DSI_INT_MSK1_gen_pld_send_err_msk_START      (10)
#define SOC_DSS_DSI_INT_MSK1_gen_pld_send_err_msk_END        (10)
#define SOC_DSS_DSI_INT_MSK1_gen_pld_rd_err_msk_START        (11)
#define SOC_DSS_DSI_INT_MSK1_gen_pld_rd_err_msk_END          (11)
#define SOC_DSS_DSI_INT_MSK1_gen_pld_recv_err_msk_START      (12)
#define SOC_DSS_DSI_INT_MSK1_gen_pld_recv_err_msk_END        (12)
#define SOC_DSS_DSI_INT_MSK1_dbi_cmd_wr_err_msk_START        (13)
#define SOC_DSS_DSI_INT_MSK1_dbi_cmd_wr_err_msk_END          (13)
#define SOC_DSS_DSI_INT_MSK1_dbi_pld_wr_err_msk_START        (14)
#define SOC_DSS_DSI_INT_MSK1_dbi_pld_wr_err_msk_END          (14)
#define SOC_DSS_DSI_INT_MSK1_dbi_pld_rd_err_msk_START        (15)
#define SOC_DSS_DSI_INT_MSK1_dbi_pld_rd_err_msk_END          (15)
#define SOC_DSS_DSI_INT_MSK1_dbi_pld_recv_err_msk_START      (16)
#define SOC_DSS_DSI_INT_MSK1_dbi_pld_recv_err_msk_END        (16)
#define SOC_DSS_DSI_INT_MSK1_dbi_illegal_comm_err_msk_START  (17)
#define SOC_DSS_DSI_INT_MSK1_dbi_illegal_comm_err_msk_END    (17)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_INT_FORCE0_UNION
 结构说明  : INT_FORCE0 寄存器结构定义。地址偏移量:0x00D8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ack_with_err_frc_0  : 1;  /* bit[0]    :  */
        unsigned int  ack_with_err_frc_1  : 1;  /* bit[1]    :  */
        unsigned int  ack_with_err_frc_2  : 1;  /* bit[2]    :  */
        unsigned int  ack_with_err_frc_3  : 1;  /* bit[3]    :  */
        unsigned int  ack_with_err_frc_4  : 1;  /* bit[4]    :  */
        unsigned int  ack_with_err_frc_5  : 1;  /* bit[5]    :  */
        unsigned int  ack_with_err_frc_6  : 1;  /* bit[6]    :  */
        unsigned int  ack_with_err_frc_7  : 1;  /* bit[7]    :  */
        unsigned int  ack_with_err_frc_8  : 1;  /* bit[8]    :  */
        unsigned int  ack_with_err_frc_9  : 1;  /* bit[9]    :  */
        unsigned int  ack_with_err_frc_10 : 1;  /* bit[10]   :  */
        unsigned int  ack_with_err_frc_11 : 1;  /* bit[11]   :  */
        unsigned int  ack_with_err_frc_12 : 1;  /* bit[12]   :  */
        unsigned int  ack_with_err_frc_13 : 1;  /* bit[13]   :  */
        unsigned int  ack_with_err_frc_14 : 1;  /* bit[14]   :  */
        unsigned int  ack_with_err_frc_15 : 1;  /* bit[15]   :  */
        unsigned int  dphy_error_frc_0    : 1;  /* bit[16]   :  */
        unsigned int  dphy_error_frc_1    : 1;  /* bit[17]   :  */
        unsigned int  dphy_error_frc_2    : 1;  /* bit[18]   :  */
        unsigned int  dphy_error_frc_3    : 1;  /* bit[19]   :  */
        unsigned int  dphy_error_frc_4    : 1;  /* bit[20]   :  */
        unsigned int  reserved            : 11; /* bit[21-31]:  */
    } reg;
} SOC_DSS_DSI_INT_FORCE0_UNION;
#endif
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_0_START   (0)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_0_END     (0)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_1_START   (1)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_1_END     (1)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_2_START   (2)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_2_END     (2)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_3_START   (3)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_3_END     (3)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_4_START   (4)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_4_END     (4)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_5_START   (5)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_5_END     (5)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_6_START   (6)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_6_END     (6)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_7_START   (7)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_7_END     (7)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_8_START   (8)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_8_END     (8)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_9_START   (9)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_9_END     (9)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_10_START  (10)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_10_END    (10)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_11_START  (11)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_11_END    (11)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_12_START  (12)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_12_END    (12)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_13_START  (13)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_13_END    (13)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_14_START  (14)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_14_END    (14)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_15_START  (15)
#define SOC_DSS_DSI_INT_FORCE0_ack_with_err_frc_15_END    (15)
#define SOC_DSS_DSI_INT_FORCE0_dphy_error_frc_0_START     (16)
#define SOC_DSS_DSI_INT_FORCE0_dphy_error_frc_0_END       (16)
#define SOC_DSS_DSI_INT_FORCE0_dphy_error_frc_1_START     (17)
#define SOC_DSS_DSI_INT_FORCE0_dphy_error_frc_1_END       (17)
#define SOC_DSS_DSI_INT_FORCE0_dphy_error_frc_2_START     (18)
#define SOC_DSS_DSI_INT_FORCE0_dphy_error_frc_2_END       (18)
#define SOC_DSS_DSI_INT_FORCE0_dphy_error_frc_3_START     (19)
#define SOC_DSS_DSI_INT_FORCE0_dphy_error_frc_3_END       (19)
#define SOC_DSS_DSI_INT_FORCE0_dphy_error_frc_4_START     (20)
#define SOC_DSS_DSI_INT_FORCE0_dphy_error_frc_4_END       (20)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_INT_FORCE1_UNION
 结构说明  : INT_FORCE1 寄存器结构定义。地址偏移量:0x00DC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  to_hs_tx_frc          : 1;  /* bit[0]    :  */
        unsigned int  to_lp_rx_frc          : 1;  /* bit[1]    :  */
        unsigned int  ecc_single_err_frc    : 1;  /* bit[2]    :  */
        unsigned int  ecc_milti_err_frc     : 1;  /* bit[3]    :  */
        unsigned int  crc_err_frc           : 1;  /* bit[4]    :  */
        unsigned int  pkt_size_err_frc      : 1;  /* bit[5]    :  */
        unsigned int  eopt_err_frc          : 1;  /* bit[6]    :  */
        unsigned int  dpi_pld_wr_err_frc    : 1;  /* bit[7]    :  */
        unsigned int  gen_cmd_wr_err_frc    : 1;  /* bit[8]    :  */
        unsigned int  gen_pld_wr_err_frc    : 1;  /* bit[9]    :  */
        unsigned int  gen_pld_send_err_frc  : 1;  /* bit[10]   :  */
        unsigned int  gen_pld_rd_err_frc    : 1;  /* bit[11]   :  */
        unsigned int  gen_pld_recev_err_frc : 1;  /* bit[12]   :  */
        unsigned int  reserved_0            : 1;  /* bit[13]   :  */
        unsigned int  reserved_1            : 1;  /* bit[14]   :  */
        unsigned int  reserved_2            : 1;  /* bit[15]   :  */
        unsigned int  reserved_3            : 1;  /* bit[16]   :  */
        unsigned int  reserved_4            : 1;  /* bit[17]   :  */
        unsigned int  reserved_5            : 14; /* bit[18-31]:  */
    } reg;
} SOC_DSS_DSI_INT_FORCE1_UNION;
#endif
#define SOC_DSS_DSI_INT_FORCE1_to_hs_tx_frc_START           (0)
#define SOC_DSS_DSI_INT_FORCE1_to_hs_tx_frc_END             (0)
#define SOC_DSS_DSI_INT_FORCE1_to_lp_rx_frc_START           (1)
#define SOC_DSS_DSI_INT_FORCE1_to_lp_rx_frc_END             (1)
#define SOC_DSS_DSI_INT_FORCE1_ecc_single_err_frc_START     (2)
#define SOC_DSS_DSI_INT_FORCE1_ecc_single_err_frc_END       (2)
#define SOC_DSS_DSI_INT_FORCE1_ecc_milti_err_frc_START      (3)
#define SOC_DSS_DSI_INT_FORCE1_ecc_milti_err_frc_END        (3)
#define SOC_DSS_DSI_INT_FORCE1_crc_err_frc_START            (4)
#define SOC_DSS_DSI_INT_FORCE1_crc_err_frc_END              (4)
#define SOC_DSS_DSI_INT_FORCE1_pkt_size_err_frc_START       (5)
#define SOC_DSS_DSI_INT_FORCE1_pkt_size_err_frc_END         (5)
#define SOC_DSS_DSI_INT_FORCE1_eopt_err_frc_START           (6)
#define SOC_DSS_DSI_INT_FORCE1_eopt_err_frc_END             (6)
#define SOC_DSS_DSI_INT_FORCE1_dpi_pld_wr_err_frc_START     (7)
#define SOC_DSS_DSI_INT_FORCE1_dpi_pld_wr_err_frc_END       (7)
#define SOC_DSS_DSI_INT_FORCE1_gen_cmd_wr_err_frc_START     (8)
#define SOC_DSS_DSI_INT_FORCE1_gen_cmd_wr_err_frc_END       (8)
#define SOC_DSS_DSI_INT_FORCE1_gen_pld_wr_err_frc_START     (9)
#define SOC_DSS_DSI_INT_FORCE1_gen_pld_wr_err_frc_END       (9)
#define SOC_DSS_DSI_INT_FORCE1_gen_pld_send_err_frc_START   (10)
#define SOC_DSS_DSI_INT_FORCE1_gen_pld_send_err_frc_END     (10)
#define SOC_DSS_DSI_INT_FORCE1_gen_pld_rd_err_frc_START     (11)
#define SOC_DSS_DSI_INT_FORCE1_gen_pld_rd_err_frc_END       (11)
#define SOC_DSS_DSI_INT_FORCE1_gen_pld_recev_err_frc_START  (12)
#define SOC_DSS_DSI_INT_FORCE1_gen_pld_recev_err_frc_END    (12)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_VID_SHADOW_CTRL_UNION
 结构说明  : VID_SHADOW_CTRL 寄存器结构定义。地址偏移量:0x0100，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vid_shadow_en      : 1;  /* bit[0]    :  */
        unsigned int  reserved_0         : 7;  /* bit[1-7]  :  */
        unsigned int  vid_shadow_req     : 1;  /* bit[8]    :  */
        unsigned int  reserved_1         : 7;  /* bit[9-15] :  */
        unsigned int  vid_shadow_pin_req : 1;  /* bit[16]   :  */
        unsigned int  reserved_2         : 15; /* bit[17-31]:  */
    } reg;
} SOC_DSS_DSI_VID_SHADOW_CTRL_UNION;
#endif
#define SOC_DSS_DSI_VID_SHADOW_CTRL_vid_shadow_en_START       (0)
#define SOC_DSS_DSI_VID_SHADOW_CTRL_vid_shadow_en_END         (0)
#define SOC_DSS_DSI_VID_SHADOW_CTRL_vid_shadow_req_START      (8)
#define SOC_DSS_DSI_VID_SHADOW_CTRL_vid_shadow_req_END        (8)
#define SOC_DSS_DSI_VID_SHADOW_CTRL_vid_shadow_pin_req_START  (16)
#define SOC_DSS_DSI_VID_SHADOW_CTRL_vid_shadow_pin_req_END    (16)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_DPI_VCID_ACT_UNION
 结构说明  : DPI_VCID_ACT 寄存器结构定义。地址偏移量:0x010C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dpi_vcid_act : 2;  /* bit[0-1] :  */
        unsigned int  reserved     : 30; /* bit[2-31]:  */
    } reg;
} SOC_DSS_DSI_DPI_VCID_ACT_UNION;
#endif
#define SOC_DSS_DSI_DPI_VCID_ACT_dpi_vcid_act_START  (0)
#define SOC_DSS_DSI_DPI_VCID_ACT_dpi_vcid_act_END    (1)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_DPI_COLOR_CODING_ACT_UNION
 结构说明  : DPI_COLOR_CODING_ACT 寄存器结构定义。地址偏移量:0x0110，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dpi_color_coding_act : 4;  /* bit[0-3]  :  */
        unsigned int  reserved_0           : 4;  /* bit[4-7]  :  */
        unsigned int  loosely18_en_act     : 1;  /* bit[8]    :  */
        unsigned int  reserved_1           : 18; /* bit[9-26] :  */
        unsigned int  reserved_2           : 5;  /* bit[27-31]:  */
    } reg;
} SOC_DSS_DSI_DPI_COLOR_CODING_ACT_UNION;
#endif
#define SOC_DSS_DSI_DPI_COLOR_CODING_ACT_dpi_color_coding_act_START  (0)
#define SOC_DSS_DSI_DPI_COLOR_CODING_ACT_dpi_color_coding_act_END    (3)
#define SOC_DSS_DSI_DPI_COLOR_CODING_ACT_loosely18_en_act_START      (8)
#define SOC_DSS_DSI_DPI_COLOR_CODING_ACT_loosely18_en_act_END        (8)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_DPI_LP_CMD_TIM_ACT_UNION
 结构说明  : DPI_LP_CMD_TIM_ACT 寄存器结构定义。地址偏移量:0x0118，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  invact_lpcmd_time_act  : 8;  /* bit[0-7]  :  */
        unsigned int  reserved_0             : 8;  /* bit[8-15] :  */
        unsigned int  outvact_lpcmd_time_act : 8;  /* bit[16-23]:  */
        unsigned int  reserved_1             : 8;  /* bit[24-31]:  */
    } reg;
} SOC_DSS_DSI_DPI_LP_CMD_TIM_ACT_UNION;
#endif
#define SOC_DSS_DSI_DPI_LP_CMD_TIM_ACT_invact_lpcmd_time_act_START   (0)
#define SOC_DSS_DSI_DPI_LP_CMD_TIM_ACT_invact_lpcmd_time_act_END     (7)
#define SOC_DSS_DSI_DPI_LP_CMD_TIM_ACT_outvact_lpcmd_time_act_START  (16)
#define SOC_DSS_DSI_DPI_LP_CMD_TIM_ACT_outvact_lpcmd_time_act_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_VID_MODE_CFG_ACT_UNION
 结构说明  : VID_MODE_CFG_ACT 寄存器结构定义。地址偏移量:0x0138，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vid_mode_type_act    : 2;  /* bit[0-1]  :  */
        unsigned int  reserved_0           : 6;  /* bit[2-7]  :  */
        unsigned int  lp_vsa_en_act        : 1;  /* bit[8]    :  */
        unsigned int  lp_vbp_en_act        : 1;  /* bit[9]    :  */
        unsigned int  lp_vfp_en_act        : 1;  /* bit[10]   :  */
        unsigned int  lp_vact_en_act       : 1;  /* bit[11]   :  */
        unsigned int  lp_hbp_en_act        : 1;  /* bit[12]   :  */
        unsigned int  lp_hfp_en_act        : 1;  /* bit[13]   :  */
        unsigned int  frame_bta_ack_en_act : 1;  /* bit[14]   :  */
        unsigned int  lp_cmd_en_act        : 1;  /* bit[15]   :  */
        unsigned int  reserved_1           : 16; /* bit[16-31]:  */
    } reg;
} SOC_DSS_DSI_VID_MODE_CFG_ACT_UNION;
#endif
#define SOC_DSS_DSI_VID_MODE_CFG_ACT_vid_mode_type_act_START     (0)
#define SOC_DSS_DSI_VID_MODE_CFG_ACT_vid_mode_type_act_END       (1)
#define SOC_DSS_DSI_VID_MODE_CFG_ACT_lp_vsa_en_act_START         (8)
#define SOC_DSS_DSI_VID_MODE_CFG_ACT_lp_vsa_en_act_END           (8)
#define SOC_DSS_DSI_VID_MODE_CFG_ACT_lp_vbp_en_act_START         (9)
#define SOC_DSS_DSI_VID_MODE_CFG_ACT_lp_vbp_en_act_END           (9)
#define SOC_DSS_DSI_VID_MODE_CFG_ACT_lp_vfp_en_act_START         (10)
#define SOC_DSS_DSI_VID_MODE_CFG_ACT_lp_vfp_en_act_END           (10)
#define SOC_DSS_DSI_VID_MODE_CFG_ACT_lp_vact_en_act_START        (11)
#define SOC_DSS_DSI_VID_MODE_CFG_ACT_lp_vact_en_act_END          (11)
#define SOC_DSS_DSI_VID_MODE_CFG_ACT_lp_hbp_en_act_START         (12)
#define SOC_DSS_DSI_VID_MODE_CFG_ACT_lp_hbp_en_act_END           (12)
#define SOC_DSS_DSI_VID_MODE_CFG_ACT_lp_hfp_en_act_START         (13)
#define SOC_DSS_DSI_VID_MODE_CFG_ACT_lp_hfp_en_act_END           (13)
#define SOC_DSS_DSI_VID_MODE_CFG_ACT_frame_bta_ack_en_act_START  (14)
#define SOC_DSS_DSI_VID_MODE_CFG_ACT_frame_bta_ack_en_act_END    (14)
#define SOC_DSS_DSI_VID_MODE_CFG_ACT_lp_cmd_en_act_START         (15)
#define SOC_DSS_DSI_VID_MODE_CFG_ACT_lp_cmd_en_act_END           (15)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_VID_PKT_SIZE_ACT_UNION
 结构说明  : VID_PKT_SIZE_ACT 寄存器结构定义。地址偏移量:0x013C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vid_pkt_size_act : 14; /* bit[0-13] :  */
        unsigned int  reserved         : 18; /* bit[14-31]:  */
    } reg;
} SOC_DSS_DSI_VID_PKT_SIZE_ACT_UNION;
#endif
#define SOC_DSS_DSI_VID_PKT_SIZE_ACT_vid_pkt_size_act_START  (0)
#define SOC_DSS_DSI_VID_PKT_SIZE_ACT_vid_pkt_size_act_END    (13)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_VID_NUM_CHUNKS_ACT_UNION
 结构说明  : VID_NUM_CHUNKS_ACT 寄存器结构定义。地址偏移量:0x0140，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vid_null_chunks_act : 13; /* bit[0-12] :  */
        unsigned int  reserved            : 19; /* bit[13-31]:  */
    } reg;
} SOC_DSS_DSI_VID_NUM_CHUNKS_ACT_UNION;
#endif
#define SOC_DSS_DSI_VID_NUM_CHUNKS_ACT_vid_null_chunks_act_START  (0)
#define SOC_DSS_DSI_VID_NUM_CHUNKS_ACT_vid_null_chunks_act_END    (12)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_VID_NULL_SIZE_ACT_UNION
 结构说明  : VID_NULL_SIZE_ACT 寄存器结构定义。地址偏移量:0x0144，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vid_null_size_act : 13; /* bit[0-12] :  */
        unsigned int  reserved          : 19; /* bit[13-31]:  */
    } reg;
} SOC_DSS_DSI_VID_NULL_SIZE_ACT_UNION;
#endif
#define SOC_DSS_DSI_VID_NULL_SIZE_ACT_vid_null_size_act_START  (0)
#define SOC_DSS_DSI_VID_NULL_SIZE_ACT_vid_null_size_act_END    (12)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_VID_HSA_TIME_ACT_UNION
 结构说明  : VID_HSA_TIME_ACT 寄存器结构定义。地址偏移量:0x0148，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vid_has_time_act : 12; /* bit[0-11] :  */
        unsigned int  reserved         : 20; /* bit[12-31]:  */
    } reg;
} SOC_DSS_DSI_VID_HSA_TIME_ACT_UNION;
#endif
#define SOC_DSS_DSI_VID_HSA_TIME_ACT_vid_has_time_act_START  (0)
#define SOC_DSS_DSI_VID_HSA_TIME_ACT_vid_has_time_act_END    (11)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_VID_HBP_TIME_ACT_UNION
 结构说明  : VID_HBP_TIME_ACT 寄存器结构定义。地址偏移量:0x014C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vid_hbp_time_act : 12; /* bit[0-11] :  */
        unsigned int  reserved         : 20; /* bit[12-31]:  */
    } reg;
} SOC_DSS_DSI_VID_HBP_TIME_ACT_UNION;
#endif
#define SOC_DSS_DSI_VID_HBP_TIME_ACT_vid_hbp_time_act_START  (0)
#define SOC_DSS_DSI_VID_HBP_TIME_ACT_vid_hbp_time_act_END    (11)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_VID_HLINE_TIME_ACT_UNION
 结构说明  : VID_HLINE_TIME_ACT 寄存器结构定义。地址偏移量:0x0150，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vid_hline_time_act : 15; /* bit[0-14] :  */
        unsigned int  reserved           : 17; /* bit[15-31]:  */
    } reg;
} SOC_DSS_DSI_VID_HLINE_TIME_ACT_UNION;
#endif
#define SOC_DSS_DSI_VID_HLINE_TIME_ACT_vid_hline_time_act_START  (0)
#define SOC_DSS_DSI_VID_HLINE_TIME_ACT_vid_hline_time_act_END    (14)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_VID_VSA_LINES_ACT_UNION
 结构说明  : VID_VSA_LINES_ACT 寄存器结构定义。地址偏移量:0x0154，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vsa_lines_act : 10; /* bit[0-9]  :  */
        unsigned int  reserved      : 22; /* bit[10-31]:  */
    } reg;
} SOC_DSS_DSI_VID_VSA_LINES_ACT_UNION;
#endif
#define SOC_DSS_DSI_VID_VSA_LINES_ACT_vsa_lines_act_START  (0)
#define SOC_DSS_DSI_VID_VSA_LINES_ACT_vsa_lines_act_END    (9)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_VID_VBP_LINES_ACT_UNION
 结构说明  : VID_VBP_LINES_ACT 寄存器结构定义。地址偏移量:0x0158，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vbp_lines_act : 10; /* bit[0-9]  :  */
        unsigned int  reserved      : 22; /* bit[10-31]:  */
    } reg;
} SOC_DSS_DSI_VID_VBP_LINES_ACT_UNION;
#endif
#define SOC_DSS_DSI_VID_VBP_LINES_ACT_vbp_lines_act_START  (0)
#define SOC_DSS_DSI_VID_VBP_LINES_ACT_vbp_lines_act_END    (9)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_VID_VFP_LINES_ACT_UNION
 结构说明  : VID_VFP_LINES_ACT 寄存器结构定义。地址偏移量:0x015C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vfp_lines_act : 10; /* bit[0-9]  :  */
        unsigned int  reserved      : 22; /* bit[10-31]:  */
    } reg;
} SOC_DSS_DSI_VID_VFP_LINES_ACT_UNION;
#endif
#define SOC_DSS_DSI_VID_VFP_LINES_ACT_vfp_lines_act_START  (0)
#define SOC_DSS_DSI_VID_VFP_LINES_ACT_vfp_lines_act_END    (9)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_VID_VACTIVE_LINES_ACT_UNION
 结构说明  : VID_VACTIVE_LINES_ACT 寄存器结构定义。地址偏移量:0x0160，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  v_active_lines_act : 14; /* bit[0-13] :  */
        unsigned int  reserved           : 18; /* bit[14-31]:  */
    } reg;
} SOC_DSS_DSI_VID_VACTIVE_LINES_ACT_UNION;
#endif
#define SOC_DSS_DSI_VID_VACTIVE_LINES_ACT_v_active_lines_act_START  (0)
#define SOC_DSS_DSI_VID_VACTIVE_LINES_ACT_v_active_lines_act_END    (13)


/*****************************************************************************
 结构名    : SOC_DSS_DSI_SDF_3D_ACT_UNION
 结构说明  : SDF_3D_ACT 寄存器结构定义。地址偏移量:0x0190，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode_3d_act      : 2;  /* bit[0-1]  :  */
        unsigned int  format_3d_act    : 2;  /* bit[2-3]  :  */
        unsigned int  second_vsync_act : 1;  /* bit[4]    :  */
        unsigned int  right_first_act  : 1;  /* bit[5]    :  */
        unsigned int  reserved_0       : 10; /* bit[6-15] :  */
        unsigned int  send_3d_cfg_act  : 1;  /* bit[16]   :  */
        unsigned int  reserved_1       : 15; /* bit[17-31]:  */
    } reg;
} SOC_DSS_DSI_SDF_3D_ACT_UNION;
#endif
#define SOC_DSS_DSI_SDF_3D_ACT_mode_3d_act_START       (0)
#define SOC_DSS_DSI_SDF_3D_ACT_mode_3d_act_END         (1)
#define SOC_DSS_DSI_SDF_3D_ACT_format_3d_act_START     (2)
#define SOC_DSS_DSI_SDF_3D_ACT_format_3d_act_END       (3)
#define SOC_DSS_DSI_SDF_3D_ACT_second_vsync_act_START  (4)
#define SOC_DSS_DSI_SDF_3D_ACT_second_vsync_act_END    (4)
#define SOC_DSS_DSI_SDF_3D_ACT_right_first_act_START   (5)
#define SOC_DSS_DSI_SDF_3D_ACT_right_first_act_END     (5)
#define SOC_DSS_DSI_SDF_3D_ACT_send_3d_cfg_act_START   (16)
#define SOC_DSS_DSI_SDF_3D_ACT_send_3d_cfg_act_END     (16)






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

#endif /* end of soc_dss_dsi_interface.h */
