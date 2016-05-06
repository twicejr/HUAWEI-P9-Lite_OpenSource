/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_dss_dpp_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:20:02
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_DSS_DPP.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_DSS_DPP_INTERFACE_H__
#define __SOC_DSS_DPP_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) reg_DPP
 ****************************************************************************/
/* 寄存器说明：读寄存器选择信号
   位域定义UNION结构:  SOC_DSS_DPP_DPP_RD_SHADOW_SEL_UNION */
#define SOC_DSS_DPP_DPP_RD_SHADOW_SEL_ADDR(base)      ((base) + (0x000))

/* 寄存器说明：DPP版本信息
   位域定义UNION结构:  SOC_DSS_DPP_DPP_ID_UNION */
#define SOC_DSS_DPP_DPP_ID_ADDR(base)                 ((base) + (0x004))

/* 寄存器说明：DPP图像宽度
   位域定义UNION结构:  SOC_DSS_DPP_DPP_IMG_HRZ_UNION */
#define SOC_DSS_DPP_DPP_IMG_HRZ_ADDR(base)            ((base) + (0x008))

/* 寄存器说明：DPP图像高度
   位域定义UNION结构:  SOC_DSS_DPP_DPP_IMG_VRT_UNION */
#define SOC_DSS_DPP_DPP_IMG_VRT_ADDR(base)            ((base) + (0x00C))

/* 寄存器说明：COLORBAR控制寄存器
   位域定义UNION结构:  SOC_DSS_DPP_CLRBAR_CTRL_UNION */
#define SOC_DSS_DPP_CLRBAR_CTRL_ADDR(base)            ((base) + (0x010))

/* 寄存器说明：DITHER控制寄存器
   位域定义UNION结构:  SOC_DSS_DPP_DITHER_UNION */
#define SOC_DSS_DPP_DITHER_ADDR(base)                 ((base) + (0x014))

/* 寄存器说明：SBL控制寄存器
   位域定义UNION结构:  SOC_DSS_DPP_SBL_UNION */
#define SOC_DSS_DPP_SBL_ADDR(base)                    ((base) + (0x018))

/* 寄存器说明：一级模块时钟选择信号
   位域定义UNION结构:  SOC_DSS_DPP_DPP_CLK_SEL_UNION */
#define SOC_DSS_DPP_DPP_CLK_SEL_ADDR(base)            ((base) + (0x01C))

/* 寄存器说明：一级模块时钟使能信号
   位域定义UNION结构:  SOC_DSS_DPP_DPP_CLK_EN_UNION */
#define SOC_DSS_DPP_DPP_CLK_EN_ADDR(base)             ((base) + (0x020))

/* 寄存器说明：DPP 像素输入计数器，用于debug
   位域定义UNION结构:  SOC_DSS_DPP_DPP_DBG_CNT_UNION */
#define SOC_DSS_DPP_DPP_DBG_CNT_ADDR(base)            ((base) + (0x024))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DPP_LCP_XCC_COEF_00_UNION */
#define SOC_DSS_DPP_LCP_XCC_COEF_00_ADDR(base)        ((base) + (0x100))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DPP_LCP_XCC_COEF_01_UNION */
#define SOC_DSS_DPP_LCP_XCC_COEF_01_ADDR(base)        ((base) + (0x104))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DPP_LCP_XCC_COEF_02_UNION */
#define SOC_DSS_DPP_LCP_XCC_COEF_02_ADDR(base)        ((base) + (0x108))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DPP_LCP_XCC_COEF_03_UNION */
#define SOC_DSS_DPP_LCP_XCC_COEF_03_ADDR(base)        ((base) + (0x10C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DPP_LCP_XCC_COEF_10_UNION */
#define SOC_DSS_DPP_LCP_XCC_COEF_10_ADDR(base)        ((base) + (0x110))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DPP_LCP_XCC_COEF_11_UNION */
#define SOC_DSS_DPP_LCP_XCC_COEF_11_ADDR(base)        ((base) + (0x114))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DPP_LCP_XCC_COEF_12_UNION */
#define SOC_DSS_DPP_LCP_XCC_COEF_12_ADDR(base)        ((base) + (0x118))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DPP_LCP_XCC_COEF_13_UNION */
#define SOC_DSS_DPP_LCP_XCC_COEF_13_ADDR(base)        ((base) + (0x11C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DPP_LCP_XCC_COEF_20_UNION */
#define SOC_DSS_DPP_LCP_XCC_COEF_20_ADDR(base)        ((base) + (0x120))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DPP_LCP_XCC_COEF_21_UNION */
#define SOC_DSS_DPP_LCP_XCC_COEF_21_ADDR(base)        ((base) + (0x124))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DPP_LCP_XCC_COEF_22_UNION */
#define SOC_DSS_DPP_LCP_XCC_COEF_22_ADDR(base)        ((base) + (0x128))

/* 寄存器说明：
   位域定义UNION结构:  SOC_DSS_DPP_LCP_XCC_COEF_23_UNION */
#define SOC_DSS_DPP_LCP_XCC_COEF_23_ADDR(base)        ((base) + (0x12C))

/* 寄存器说明：输入数据有效位选择
   位域定义UNION结构:  SOC_DSS_DPP_GMP_BYPASS_EN_UNION */
#define SOC_DSS_DPP_GMP_BYPASS_EN_ADDR(base)          ((base) + (0x130))

/* 寄存器说明：旁路GAMA模块
   位域定义UNION结构:  SOC_DSS_DPP_XCC_BYPASS_EN_UNION */
#define SOC_DSS_DPP_XCC_BYPASS_EN_ADDR(base)          ((base) + (0x134))

/* 寄存器说明：MEM低功耗控制寄存器
   位域定义UNION结构:  SOC_DSS_DPP_IGM_MEM_CTRL_UNION */
#define SOC_DSS_DPP_IGM_MEM_CTRL_ADDR(base)           ((base) + (0x138))

/* 寄存器说明：MEM低功耗控制寄存器
   位域定义UNION结构:  SOC_DSS_DPP_GMP_MEM_CTRL_UNION */
#define SOC_DSS_DPP_GMP_MEM_CTRL_ADDR(base)           ((base) + (0x13C))

/* 寄存器说明：区域0色调的上下限值
   位域定义UNION结构:  SOC_DSS_DPP_R0_H_UNION */
#define SOC_DSS_DPP_R0_H_ADDR(base)                   ((base) + (0x200))

/* 寄存器说明：区域1色调的上下限值
   位域定义UNION结构:  SOC_DSS_DPP_R1_H_UNION */
#define SOC_DSS_DPP_R1_H_ADDR(base)                   ((base) + (0x204))

/* 寄存器说明：区域2色调的上下限值
   位域定义UNION结构:  SOC_DSS_DPP_R2_H_UNION */
#define SOC_DSS_DPP_R2_H_ADDR(base)                   ((base) + (0x208))

/* 寄存器说明：区域3色调的上下限值
   位域定义UNION结构:  SOC_DSS_DPP_R3_H_UNION */
#define SOC_DSS_DPP_R3_H_ADDR(base)                   ((base) + (0x20C))

/* 寄存器说明：区域4色调的上下限值
   位域定义UNION结构:  SOC_DSS_DPP_R4_H_UNION */
#define SOC_DSS_DPP_R4_H_ADDR(base)                   ((base) + (0x210))

/* 寄存器说明：区域5色调的上下限值
   位域定义UNION结构:  SOC_DSS_DPP_R5_H_UNION */
#define SOC_DSS_DPP_R5_H_ADDR(base)                   ((base) + (0x214))

/* 寄存器说明：区域6色调的上下限值
   位域定义UNION结构:  SOC_DSS_DPP_R6_H_UNION */
#define SOC_DSS_DPP_R6_H_ADDR(base)                   ((base) + (0x218))

/* 寄存器说明：区域使能
   位域定义UNION结构:  SOC_DSS_DPP_ACM_EN_UNION */
#define SOC_DSS_DPP_ACM_EN_ADDR(base)                 ((base) + (0x21C))

/* 寄存器说明：MEM低功耗控制寄存器
   位域定义UNION结构:  SOC_DSS_DPP_ACM_MEM_CTRL_UNION */
#define SOC_DSS_DPP_ACM_MEM_CTRL_ADDR(base)           ((base) + (0x220))

/* 寄存器说明：直方图统计清零
   位域定义UNION结构:  SOC_DSS_DPP_CE_HIST_RESET_UNION */
#define SOC_DSS_DPP_CE_HIST_RESET_ADDR(base)          ((base) + (0x230))

/* 寄存器说明：直方图统计控制
   位域定义UNION结构:  SOC_DSS_DPP_CE_HIST_CTL_UNION */
#define SOC_DSS_DPP_CE_HIST_CTL_ADDR(base)            ((base) + (0x234))

/* 寄存器说明：直方图统计的帧个数
   位域定义UNION结构:  SOC_DSS_DPP_CE_HIST_FRAME_CNT_UNION */
#define SOC_DSS_DPP_CE_HIST_FRAME_CNT_ADDR(base)      ((base) + (0x238))

/* 寄存器说明：图像的宽和高
   位域定义UNION结构:  SOC_DSS_DPP_CE_SIZE_UNION */
#define SOC_DSS_DPP_CE_SIZE_ADDR(base)                ((base) + (0x23C))

/* 寄存器说明：最后一帧的最后几行不进行直方图统计
   位域定义UNION结构:  SOC_DSS_DPP_CE_NO_STAT_LINES_UNION */
#define SOC_DSS_DPP_CE_NO_STAT_LINES_ADDR(base)       ((base) + (0x240))

/* 寄存器说明：暗点阈值
   位域定义UNION结构:  SOC_DSS_DPP_CE_BLACK_REGION_THRE_UNION */
#define SOC_DSS_DPP_CE_BLACK_REGION_THRE_ADDR(base)   ((base) + (0x244))

/* 寄存器说明：亮点阈值
   位域定义UNION结构:  SOC_DSS_DPP_CE_WHITE_REGION_THRE_UNION */
#define SOC_DSS_DPP_CE_WHITE_REGION_THRE_ADDR(base)   ((base) + (0x248))

/* 寄存器说明：LUT表单乒乓选择
   位域定义UNION结构:  SOC_DSS_DPP_CE_LUT_SEL_UNION */
#define SOC_DSS_DPP_CE_LUT_SEL_ADDR(base)             ((base) + (0x24C))

/* 寄存器说明：CE旁路选择
   位域定义UNION结构:  SOC_DSS_DPP_CE_LUT_ENABLE_UNION */
#define SOC_DSS_DPP_CE_LUT_ENABLE_ADDR(base)          ((base) + (0x250))

/* 寄存器说明：LUT读写权限分配指示
   位域定义UNION结构:  SOC_DSS_DPP_CE_LUT_USING_IND_UNION */
#define SOC_DSS_DPP_CE_LUT_USING_IND_ADDR(base)       ((base) + (0x254))

/* 寄存器说明：CE工作指示
   位域定义UNION结构:  SOC_DSS_DPP_CE_STATE_IND_UNION */
#define SOC_DSS_DPP_CE_STATE_IND_ADDR(base)           ((base) + (0x258))

/* 寄存器说明：CE MEM低功耗控制寄存器
   位域定义UNION结构:  SOC_DSS_DPP_CE_MEM_CTRL_UNION */
#define SOC_DSS_DPP_CE_MEM_CTRL_ADDR(base)            ((base) + (0x25C))

/* 寄存器说明：所有灰度总和
   位域定义UNION结构:  SOC_DSS_DPP_CE_TOTALGRAY_UNION */
#define SOC_DSS_DPP_CE_TOTALGRAY_ADDR(base)           ((base) + (0x264))

/* 寄存器说明：所有像素的个数
   位域定义UNION结构:  SOC_DSS_DPP_CE_TOTALPIXL_UNION */
#define SOC_DSS_DPP_CE_TOTALPIXL_ADDR(base)           ((base) + (0x268))

/* 寄存器说明：直方图最大值对应的灰度值
   位域定义UNION结构:  SOC_DSS_DPP_CE_MEAN_UNION */
#define SOC_DSS_DPP_CE_MEAN_ADDR(base)                ((base) + (0x26C))

/* 寄存器说明：分位数0~3
   位域定义UNION结构:  SOC_DSS_DPP_CE_PEC0_3_UNION */
#define SOC_DSS_DPP_CE_PEC0_3_ADDR(base)              ((base) + (0x270))

/* 寄存器说明：分位数4~7
   位域定义UNION结构:  SOC_DSS_DPP_CE_PEC4_7_UNION */
#define SOC_DSS_DPP_CE_PEC4_7_ADDR(base)              ((base) + (0x274))

/* 寄存器说明：分位数8
   位域定义UNION结构:  SOC_DSS_DPP_CE_PEC8_UNION */
#define SOC_DSS_DPP_CE_PEC8_ADDR(base)                ((base) + (0x278))

/* 寄存器说明：暗点个数
   位域定义UNION结构:  SOC_DSS_DPP_CE_BLACK_NUM_UNION */
#define SOC_DSS_DPP_CE_BLACK_NUM_ADDR(base)           ((base) + (0x27C))

/* 寄存器说明：亮点个数
   位域定义UNION结构:  SOC_DSS_DPP_CE_WHITE_NUM_UNION */
#define SOC_DSS_DPP_CE_WHITE_NUM_ADDR(base)           ((base) + (0x280))

/* 寄存器说明：上报直方图指示
   位域定义UNION结构:  SOC_DSS_DPP_CE_HIST_RPT_IND_UNION */
#define SOC_DSS_DPP_CE_HIST_RPT_IND_ADDR(base)        ((base) + (0x284))

/* 寄存器说明：输入数据有效位选择
   位域定义UNION结构:  SOC_DSS_DPP_GAMA_SHORTBIT_EN_UNION */
#define SOC_DSS_DPP_GAMA_SHORTBIT_EN_ADDR(base)       ((base) + (0x300))

/* 寄存器说明：旁路GAMA模块
   位域定义UNION结构:  SOC_DSS_DPP_GAMA_BYPASS_EN_UNION */
#define SOC_DSS_DPP_GAMA_BYPASS_EN_ADDR(base)         ((base) + (0x304))

/* 寄存器说明：MEM低功耗控制寄存器
   位域定义UNION结构:  SOC_DSS_DPP_GAMA_MEM_CTRL_UNION */
#define SOC_DSS_DPP_GAMA_MEM_CTRL_ADDR(base)          ((base) + (0x308))

/* 寄存器说明：模块影子寄存器恢复到默认值
   位域定义UNION结构:  SOC_DSS_DPP_REG_DEFAULT_UNION */
#define SOC_DSS_DPP_REG_DEFAULT_ADDR(base)            ((base) + (0x030C))

/* 寄存器说明：MEM低功耗控制寄存器
   位域定义UNION结构:  SOC_DSS_DPP_SBL_MEM_CTRL_UNION */
#define SOC_DSS_DPP_SBL_MEM_CTRL_ADDR(base)           ((base) + (0x310))

/* 寄存器说明：DPP调试用寄存器
   位域定义UNION结构:  SOC_DSS_DPP_DPP_DBG_UNION */
#define SOC_DSS_DPP_DPP_DBG_ADDR(base)                ((base) + (0x314))

/* 寄存器说明：GAMA系数查找表
   位域定义UNION结构:  SOC_DSS_DPP_U_GAMA_COEF_UNION */
#define SOC_DSS_DPP_U_GAMA_COEF_ADDR(base)            ((base) + (0x0400))

/* 寄存器说明：ACM H分量查找表
   位域定义UNION结构:  SOC_DSS_DPP_U_H_COEF_UNION */
#define SOC_DSS_DPP_U_H_COEF_ADDR(base)               ((base) + (0x1000))

/* 寄存器说明：ACM SATA分量查找表
   位域定义UNION结构:  SOC_DSS_DPP_U_SATA_COEF_UNION */
#define SOC_DSS_DPP_U_SATA_COEF_ADDR(base)            ((base) + (0x1A00))

/* 寄存器说明：ACM SATR分量查找表
   位域定义UNION结构:  SOC_DSS_DPP_U_SATR_COEF_UNION */
#define SOC_DSS_DPP_U_SATR_COEF_ADDR(base)            ((base) + (0x1C00))

/* 寄存器说明：上报直方图memory0
   位域定义UNION结构:  SOC_DSS_DPP_CE_HIST_RPT0_UNION */
#define SOC_DSS_DPP_CE_HIST_RPT0_ADDR(base)           ((base) + (0x2000～0x23FF))

/* 寄存器说明：上报直方图memory1
   位域定义UNION结构:  SOC_DSS_DPP_CE_HIST_RPT1_UNION */
#define SOC_DSS_DPP_CE_HIST_RPT1_ADDR(base)           ((base) + (0x2400～0x27FF))

/* 寄存器说明：LUT 表单 memory0
   位域定义UNION结构:  SOC_DSS_DPP_CE_LUT0_UNION */
#define SOC_DSS_DPP_CE_LUT0_ADDR(base)                ((base) + (0x2800))

/* 寄存器说明：LUT 表单 memory1
   位域定义UNION结构:  SOC_DSS_DPP_CE_LUT1_UNION */
#define SOC_DSS_DPP_CE_LUT1_ADDR(base)                ((base) + (0x2C00))

/* 寄存器说明：GMP查找表
   位域定义UNION结构:  SOC_DSS_DPP_U_GMP_COEF_UNION */
#define SOC_DSS_DPP_U_GMP_COEF_ADDR(base)             ((base) + (0x3000～0x7CCF))

/* 寄存器说明：IGM R分量查找表
   位域定义UNION结构:  SOC_DSS_DPP_U_IGM_R_COEF_UNION */
#define SOC_DSS_DPP_U_IGM_R_COEF_ADDR(base)           ((base) + (0xB000))

/* 寄存器说明：IGM G分量查找表
   位域定义UNION结构:  SOC_DSS_DPP_U_IGM_G_COEF_UNION */
#define SOC_DSS_DPP_U_IGM_G_COEF_ADDR(base)           ((base) + (0xB400))

/* 寄存器说明：IGM B分量查找表
   位域定义UNION结构:  SOC_DSS_DPP_U_IGM_B_COEF_UNION */
#define SOC_DSS_DPP_U_IGM_B_COEF_ADDR(base)           ((base) + (0xB800))





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
                     (1/1) reg_DPP
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_DSS_DPP_DPP_RD_SHADOW_SEL_UNION
 结构说明  : DPP_RD_SHADOW_SEL 寄存器结构定义。地址偏移量:0x000，初值:0x00000000，宽度:32
 寄存器说明: 读寄存器选择信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dpp_rd_shadow : 1;  /* bit[0]   : 1'b0 :读工作寄存器
                                                        1'b1 :读影子寄存器 */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_DPP_DPP_RD_SHADOW_SEL_UNION;
#endif
#define SOC_DSS_DPP_DPP_RD_SHADOW_SEL_dpp_rd_shadow_START  (0)
#define SOC_DSS_DPP_DPP_RD_SHADOW_SEL_dpp_rd_shadow_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_DPP_ID_UNION
 结构说明  : DPP_ID 寄存器结构定义。地址偏移量:0x004，初值:0x00003650，宽度:32
 寄存器说明: DPP版本信息
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dpp0_id : 32; /* bit[0-31]: 保留 */
    } reg;
} SOC_DSS_DPP_DPP_ID_UNION;
#endif
#define SOC_DSS_DPP_DPP_ID_dpp0_id_START  (0)
#define SOC_DSS_DPP_DPP_ID_dpp0_id_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_DPP_IMG_HRZ_UNION
 结构说明  : DPP_IMG_HRZ 寄存器结构定义。地址偏移量:0x008，初值:0x00000000，宽度:32
 寄存器说明: DPP图像宽度
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dpp0_size_hrz : 13; /* bit[0-12] : DPP图像宽度-1 */
        unsigned int  reserved      : 19; /* bit[13-31]: 保留 */
    } reg;
} SOC_DSS_DPP_DPP_IMG_HRZ_UNION;
#endif
#define SOC_DSS_DPP_DPP_IMG_HRZ_dpp0_size_hrz_START  (0)
#define SOC_DSS_DPP_DPP_IMG_HRZ_dpp0_size_hrz_END    (12)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_DPP_IMG_VRT_UNION
 结构说明  : DPP_IMG_VRT 寄存器结构定义。地址偏移量:0x00C，初值:0x00000000，宽度:32
 寄存器说明: DPP图像高度
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dpp0_size_vrz : 13; /* bit[0-12] : DPP图像高度-1 */
        unsigned int  reserved      : 19; /* bit[13-31]: 保留 */
    } reg;
} SOC_DSS_DPP_DPP_IMG_VRT_UNION;
#endif
#define SOC_DSS_DPP_DPP_IMG_VRT_dpp0_size_vrz_START  (0)
#define SOC_DSS_DPP_DPP_IMG_VRT_dpp0_size_vrz_END    (12)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_CLRBAR_CTRL_UNION
 结构说明  : CLRBAR_CTRL 寄存器结构定义。地址偏移量:0x010，初值:0x00000000，宽度:32
 寄存器说明: COLORBAR控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  clrbar_en    : 1;  /* bit[0-0]  : colorbar使能：
                                                        0： colorbar 关闭；
                                                        1： colorbar 开启； */
        unsigned int  clrbar_mode  : 1;  /* bit[1-1]  : colorbar模式选择：
                                                        00：竖条；
                                                        01：横条；
                                                        其它：保留； */
        unsigned int  reserved     : 22; /* bit[2-23] : 保留 */
        unsigned int  clrbar_width : 8;  /* bit[24-31]: corlorbar RGB彩条宽度，写入值为实际值减1，取值范围为1~256 */
    } reg;
} SOC_DSS_DPP_CLRBAR_CTRL_UNION;
#endif
#define SOC_DSS_DPP_CLRBAR_CTRL_clrbar_en_START     (0)
#define SOC_DSS_DPP_CLRBAR_CTRL_clrbar_en_END       (0)
#define SOC_DSS_DPP_CLRBAR_CTRL_clrbar_mode_START   (1)
#define SOC_DSS_DPP_CLRBAR_CTRL_clrbar_mode_END     (1)
#define SOC_DSS_DPP_CLRBAR_CTRL_clrbar_width_START  (24)
#define SOC_DSS_DPP_CLRBAR_CTRL_clrbar_width_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_DITHER_UNION
 结构说明  : DITHER 寄存器结构定义。地址偏移量:0x014，初值:0x00000000，宽度:32
 寄存器说明: DITHER控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dither_en  : 1;  /* bit[0]   : Dithering使能：
                                                     0：Dithering不使能
                                                     1：Dithering使能 */
        unsigned int  dither_fmt : 1;  /* bit[1]   : dither输出的像素位宽：
                                                     0: 16bpp；
                                                     1: 18bpp； */
        unsigned int  dither_sel : 1;  /* bit[2]   : 丢点算法选择：
                                                     0：采用四舍五入法将输出像素统一到输出格式
                                                     1：采用Dithering算法将输出像素统一到输出格式； */
        unsigned int  reserved   : 29; /* bit[3-31]: 保留 */
    } reg;
} SOC_DSS_DPP_DITHER_UNION;
#endif
#define SOC_DSS_DPP_DITHER_dither_en_START   (0)
#define SOC_DSS_DPP_DITHER_dither_en_END     (0)
#define SOC_DSS_DPP_DITHER_dither_fmt_START  (1)
#define SOC_DSS_DPP_DITHER_dither_fmt_END    (1)
#define SOC_DSS_DPP_DITHER_dither_sel_START  (2)
#define SOC_DSS_DPP_DITHER_dither_sel_END    (2)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_SBL_UNION
 结构说明  : SBL 寄存器结构定义。地址偏移量:0x018，初值:0x00000000，宽度:32
 寄存器说明: SBL控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sbl_en   : 1;  /* bit[0]   : SBL使能寄存器
                                                   0：sbl bypass 
                                                   1：sbl使能 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_DPP_SBL_UNION;
#endif
#define SOC_DSS_DPP_SBL_sbl_en_START    (0)
#define SOC_DSS_DPP_SBL_sbl_en_END      (0)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_DPP_CLK_SEL_UNION
 结构说明  : DPP_CLK_SEL 寄存器结构定义。地址偏移量:0x01C，初值:0xFFFFFFFF，宽度:32
 寄存器说明: 一级模块时钟选择信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dpp_clk_sel : 32; /* bit[0-31]: 各一级模块的时钟选择信号，
                                                      1：表示强制打开时钟。
                                                      0：表示需要根据软件和硬件的时钟使能来开启或关闭时钟
                                                      bit0：用于apb；
                                                      bit1：用于reg；
                                                      bit2：用于sbl；
                                                      bit3：用于cb；
                                                      bit4：用于acm；
                                                      bit5：用于lcp；
                                                      bit6：用于gama；
                                                      bit7：用于dith； */
    } reg;
} SOC_DSS_DPP_DPP_CLK_SEL_UNION;
#endif
#define SOC_DSS_DPP_DPP_CLK_SEL_dpp_clk_sel_START  (0)
#define SOC_DSS_DPP_DPP_CLK_SEL_dpp_clk_sel_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_DPP_CLK_EN_UNION
 结构说明  : DPP_CLK_EN 寄存器结构定义。地址偏移量:0x020，初值:0xFFFFFFFF，宽度:32
 寄存器说明: 一级模块时钟使能信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dpp_clk_en : 32; /* bit[0-31]: 各一级模块的软件时钟使能信号
                                                     1：表示软件时钟使能有效，允许硬件开钟
                                                     0：表示软件时钟使能无效，禁止硬件开钟
                                                     bit0：用于apb；
                                                     bit1：用于reg；
                                                     bit2：用于sbl；
                                                     bit3：用于cb；
                                                     bit4：用于acm；
                                                     bit5：用于lcp；
                                                     bit6：用于gama；
                                                     bit7：用于dith； */
    } reg;
} SOC_DSS_DPP_DPP_CLK_EN_UNION;
#endif
#define SOC_DSS_DPP_DPP_CLK_EN_dpp_clk_en_START  (0)
#define SOC_DSS_DPP_DPP_CLK_EN_dpp_clk_en_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_DPP_DBG_CNT_UNION
 结构说明  : DPP_DBG_CNT 寄存器结构定义。地址偏移量:0x024，初值:0x00000000，宽度:32
 寄存器说明: DPP 像素输入计数器，用于debug
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dpp_h_cnt : 13; /* bit[0-12] : 水平宽度计数器 */
        unsigned int  reserved_0: 3;  /* bit[13-15]: 保留 */
        unsigned int  dpp_v_cnt : 13; /* bit[16-28]: 垂直行数计数器 */
        unsigned int  reserved_1: 3;  /* bit[29-31]: 保留 */
    } reg;
} SOC_DSS_DPP_DPP_DBG_CNT_UNION;
#endif
#define SOC_DSS_DPP_DPP_DBG_CNT_dpp_h_cnt_START  (0)
#define SOC_DSS_DPP_DPP_DBG_CNT_dpp_h_cnt_END    (12)
#define SOC_DSS_DPP_DPP_DBG_CNT_dpp_v_cnt_START  (16)
#define SOC_DSS_DPP_DPP_DBG_CNT_dpp_v_cnt_END    (28)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_LCP_XCC_COEF_00_UNION
 结构说明  : LCP_XCC_COEF_00 寄存器结构定义。地址偏移量:0x100，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coef_00  : 16; /* bit[0-15] : XCC系数00 */
        unsigned int  reserved : 16; /* bit[16-31]: 保留 */
    } reg;
} SOC_DSS_DPP_LCP_XCC_COEF_00_UNION;
#endif
#define SOC_DSS_DPP_LCP_XCC_COEF_00_coef_00_START   (0)
#define SOC_DSS_DPP_LCP_XCC_COEF_00_coef_00_END     (15)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_LCP_XCC_COEF_01_UNION
 结构说明  : LCP_XCC_COEF_01 寄存器结构定义。地址偏移量:0x104，初值:0x00008000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coef_01  : 17; /* bit[0-16] : XCC系数01 */
        unsigned int  reserved : 15; /* bit[17-31]: 保留 */
    } reg;
} SOC_DSS_DPP_LCP_XCC_COEF_01_UNION;
#endif
#define SOC_DSS_DPP_LCP_XCC_COEF_01_coef_01_START   (0)
#define SOC_DSS_DPP_LCP_XCC_COEF_01_coef_01_END     (16)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_LCP_XCC_COEF_02_UNION
 结构说明  : LCP_XCC_COEF_02 寄存器结构定义。地址偏移量:0x108，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coef_02  : 17; /* bit[0-16] : XCC系数02 */
        unsigned int  reserved : 15; /* bit[17-31]: 保留 */
    } reg;
} SOC_DSS_DPP_LCP_XCC_COEF_02_UNION;
#endif
#define SOC_DSS_DPP_LCP_XCC_COEF_02_coef_02_START   (0)
#define SOC_DSS_DPP_LCP_XCC_COEF_02_coef_02_END     (16)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_LCP_XCC_COEF_03_UNION
 结构说明  : LCP_XCC_COEF_03 寄存器结构定义。地址偏移量:0x10C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coef_03  : 17; /* bit[0-16] : XCC系数03 */
        unsigned int  reserved : 15; /* bit[17-31]: 保留 */
    } reg;
} SOC_DSS_DPP_LCP_XCC_COEF_03_UNION;
#endif
#define SOC_DSS_DPP_LCP_XCC_COEF_03_coef_03_START   (0)
#define SOC_DSS_DPP_LCP_XCC_COEF_03_coef_03_END     (16)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_LCP_XCC_COEF_10_UNION
 结构说明  : LCP_XCC_COEF_10 寄存器结构定义。地址偏移量:0x110，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coef_10  : 16; /* bit[0-15] : XCC系数10 */
        unsigned int  reserved : 16; /* bit[16-31]: 保留 */
    } reg;
} SOC_DSS_DPP_LCP_XCC_COEF_10_UNION;
#endif
#define SOC_DSS_DPP_LCP_XCC_COEF_10_coef_10_START   (0)
#define SOC_DSS_DPP_LCP_XCC_COEF_10_coef_10_END     (15)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_LCP_XCC_COEF_11_UNION
 结构说明  : LCP_XCC_COEF_11 寄存器结构定义。地址偏移量:0x114，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coef_11  : 17; /* bit[0-16] : XCC系数11 */
        unsigned int  reserved : 15; /* bit[17-31]: 保留 */
    } reg;
} SOC_DSS_DPP_LCP_XCC_COEF_11_UNION;
#endif
#define SOC_DSS_DPP_LCP_XCC_COEF_11_coef_11_START   (0)
#define SOC_DSS_DPP_LCP_XCC_COEF_11_coef_11_END     (16)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_LCP_XCC_COEF_12_UNION
 结构说明  : LCP_XCC_COEF_12 寄存器结构定义。地址偏移量:0x118，初值:0x00008000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coef_12  : 17; /* bit[0-16] : XCC系数12 */
        unsigned int  reserved : 15; /* bit[17-31]: 保留 */
    } reg;
} SOC_DSS_DPP_LCP_XCC_COEF_12_UNION;
#endif
#define SOC_DSS_DPP_LCP_XCC_COEF_12_coef_12_START   (0)
#define SOC_DSS_DPP_LCP_XCC_COEF_12_coef_12_END     (16)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_LCP_XCC_COEF_13_UNION
 结构说明  : LCP_XCC_COEF_13 寄存器结构定义。地址偏移量:0x11C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coef_13  : 17; /* bit[0-16] : XCC系数13 */
        unsigned int  reserved : 15; /* bit[17-31]: 保留 */
    } reg;
} SOC_DSS_DPP_LCP_XCC_COEF_13_UNION;
#endif
#define SOC_DSS_DPP_LCP_XCC_COEF_13_coef_13_START   (0)
#define SOC_DSS_DPP_LCP_XCC_COEF_13_coef_13_END     (16)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_LCP_XCC_COEF_20_UNION
 结构说明  : LCP_XCC_COEF_20 寄存器结构定义。地址偏移量:0x120，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coef_20  : 16; /* bit[0-15] : XCC系数20 */
        unsigned int  reserved : 16; /* bit[16-31]: 保留 */
    } reg;
} SOC_DSS_DPP_LCP_XCC_COEF_20_UNION;
#endif
#define SOC_DSS_DPP_LCP_XCC_COEF_20_coef_20_START   (0)
#define SOC_DSS_DPP_LCP_XCC_COEF_20_coef_20_END     (15)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_LCP_XCC_COEF_21_UNION
 结构说明  : LCP_XCC_COEF_21 寄存器结构定义。地址偏移量:0x124，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coef_21  : 17; /* bit[0-16] : XCC系数21 */
        unsigned int  reserved : 15; /* bit[17-31]: 保留 */
    } reg;
} SOC_DSS_DPP_LCP_XCC_COEF_21_UNION;
#endif
#define SOC_DSS_DPP_LCP_XCC_COEF_21_coef_21_START   (0)
#define SOC_DSS_DPP_LCP_XCC_COEF_21_coef_21_END     (16)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_LCP_XCC_COEF_22_UNION
 结构说明  : LCP_XCC_COEF_22 寄存器结构定义。地址偏移量:0x128，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coef_22  : 17; /* bit[0-16] : XCC系数22 */
        unsigned int  reserved : 15; /* bit[17-31]: 保留 */
    } reg;
} SOC_DSS_DPP_LCP_XCC_COEF_22_UNION;
#endif
#define SOC_DSS_DPP_LCP_XCC_COEF_22_coef_22_START   (0)
#define SOC_DSS_DPP_LCP_XCC_COEF_22_coef_22_END     (16)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_LCP_XCC_COEF_23_UNION
 结构说明  : LCP_XCC_COEF_23 寄存器结构定义。地址偏移量:0x12C，初值:0x00008000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coef_23  : 17; /* bit[0-16] : XCC系数23 */
        unsigned int  reserved : 15; /* bit[17-31]: 保留 */
    } reg;
} SOC_DSS_DPP_LCP_XCC_COEF_23_UNION;
#endif
#define SOC_DSS_DPP_LCP_XCC_COEF_23_coef_23_START   (0)
#define SOC_DSS_DPP_LCP_XCC_COEF_23_coef_23_END     (16)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_GMP_BYPASS_EN_UNION
 结构说明  : GMP_BYPASS_EN 寄存器结构定义。地址偏移量:0x130，初值:0x00000001，宽度:32
 寄存器说明: 输入数据有效位选择
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gmp_bypass_en : 1;  /* bit[0]   : 1：GMP旁路 */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_DPP_GMP_BYPASS_EN_UNION;
#endif
#define SOC_DSS_DPP_GMP_BYPASS_EN_gmp_bypass_en_START  (0)
#define SOC_DSS_DPP_GMP_BYPASS_EN_gmp_bypass_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_XCC_BYPASS_EN_UNION
 结构说明  : XCC_BYPASS_EN 寄存器结构定义。地址偏移量:0x134，初值:0x00000001，宽度:32
 寄存器说明: 旁路GAMA模块
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  xcc_bypass_en : 1;  /* bit[0]   : 1：XCC旁路 */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_DPP_XCC_BYPASS_EN_UNION;
#endif
#define SOC_DSS_DPP_XCC_BYPASS_EN_xcc_bypass_en_START  (0)
#define SOC_DSS_DPP_XCC_BYPASS_EN_xcc_bypass_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_IGM_MEM_CTRL_UNION
 结构说明  : IGM_MEM_CTRL 寄存器结构定义。地址偏移量:0x138，初值:0x00000000，宽度:32
 寄存器说明: MEM低功耗控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  igm_mem_ctrl : 4;  /* bit[0-3] : 调试寄存器，igm模块内memory低功耗配置：
                                                       [3]: reseverd; 
                                                       [2]: 软件配置模式下有效，为1表示进入Shut Down模式
                                                       [1]: 软件配置模式下有效，为1表示进入Deep Sleep模式
                                                       [0]: 软件配置模式下有效，为1表示进入Sleep模式 */
        unsigned int  reserved     : 28; /* bit[4-31]: 保留 */
    } reg;
} SOC_DSS_DPP_IGM_MEM_CTRL_UNION;
#endif
#define SOC_DSS_DPP_IGM_MEM_CTRL_igm_mem_ctrl_START  (0)
#define SOC_DSS_DPP_IGM_MEM_CTRL_igm_mem_ctrl_END    (3)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_GMP_MEM_CTRL_UNION
 结构说明  : GMP_MEM_CTRL 寄存器结构定义。地址偏移量:0x13C，初值:0x00000000，宽度:32
 寄存器说明: MEM低功耗控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gmp_mem_ctrl : 4;  /* bit[0-3] : 调试寄存器，gmp模块内memory低功耗配置：
                                                       [3]: reseverd; 
                                                       [2]: 软件配置模式下有效，为1表示进入Shut Down模式
                                                       [1]: 软件配置模式下有效，为1表示进入Deep Sleep模式
                                                       [0]: 软件配置模式下有效，为1表示进入Sleep模式 */
        unsigned int  reserved     : 28; /* bit[4-31]: 保留 */
    } reg;
} SOC_DSS_DPP_GMP_MEM_CTRL_UNION;
#endif
#define SOC_DSS_DPP_GMP_MEM_CTRL_gmp_mem_ctrl_START  (0)
#define SOC_DSS_DPP_GMP_MEM_CTRL_gmp_mem_ctrl_END    (3)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_R0_H_UNION
 结构说明  : R0_H 寄存器结构定义。地址偏移量:0x200，初值:0x00000000，宽度:32
 寄存器说明: 区域0色调的上下限值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  r0_lh    : 10; /* bit[0-9]  : 区域0的色调下限值 */
        unsigned int  reserved_0: 6;  /* bit[10-15]: 保留 */
        unsigned int  r0_hh    : 10; /* bit[16-25]: 区域0的色调上限值 */
        unsigned int  reserved_1: 6;  /* bit[26-31]: 保留 */
    } reg;
} SOC_DSS_DPP_R0_H_UNION;
#endif
#define SOC_DSS_DPP_R0_H_r0_lh_START     (0)
#define SOC_DSS_DPP_R0_H_r0_lh_END       (9)
#define SOC_DSS_DPP_R0_H_r0_hh_START     (16)
#define SOC_DSS_DPP_R0_H_r0_hh_END       (25)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_R1_H_UNION
 结构说明  : R1_H 寄存器结构定义。地址偏移量:0x204，初值:0x00000000，宽度:32
 寄存器说明: 区域1色调的上下限值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  r1_lh    : 10; /* bit[0-9]  : 区域1的色调下限值 */
        unsigned int  reserved_0: 6;  /* bit[10-15]: 保留 */
        unsigned int  r1_hh    : 10; /* bit[16-25]: 区域1的色调上限值 */
        unsigned int  reserved_1: 6;  /* bit[26-31]: 保留 */
    } reg;
} SOC_DSS_DPP_R1_H_UNION;
#endif
#define SOC_DSS_DPP_R1_H_r1_lh_START     (0)
#define SOC_DSS_DPP_R1_H_r1_lh_END       (9)
#define SOC_DSS_DPP_R1_H_r1_hh_START     (16)
#define SOC_DSS_DPP_R1_H_r1_hh_END       (25)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_R2_H_UNION
 结构说明  : R2_H 寄存器结构定义。地址偏移量:0x208，初值:0x00000000，宽度:32
 寄存器说明: 区域2色调的上下限值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  r2_lh    : 10; /* bit[0-9]  : 区域2的色调下限值 */
        unsigned int  reserved_0: 6;  /* bit[10-15]: 保留 */
        unsigned int  r2_hh    : 10; /* bit[16-25]: 区域2的色调上限值 */
        unsigned int  reserved_1: 6;  /* bit[26-31]: 保留 */
    } reg;
} SOC_DSS_DPP_R2_H_UNION;
#endif
#define SOC_DSS_DPP_R2_H_r2_lh_START     (0)
#define SOC_DSS_DPP_R2_H_r2_lh_END       (9)
#define SOC_DSS_DPP_R2_H_r2_hh_START     (16)
#define SOC_DSS_DPP_R2_H_r2_hh_END       (25)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_R3_H_UNION
 结构说明  : R3_H 寄存器结构定义。地址偏移量:0x20C，初值:0x00000000，宽度:32
 寄存器说明: 区域3色调的上下限值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  r3_lh    : 10; /* bit[0-9]  : 区域3的色调下限值 */
        unsigned int  reserved_0: 6;  /* bit[10-15]: 保留 */
        unsigned int  r3_hh    : 10; /* bit[16-25]: 区域3的色调上限值 */
        unsigned int  reserved_1: 6;  /* bit[26-31]: 保留 */
    } reg;
} SOC_DSS_DPP_R3_H_UNION;
#endif
#define SOC_DSS_DPP_R3_H_r3_lh_START     (0)
#define SOC_DSS_DPP_R3_H_r3_lh_END       (9)
#define SOC_DSS_DPP_R3_H_r3_hh_START     (16)
#define SOC_DSS_DPP_R3_H_r3_hh_END       (25)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_R4_H_UNION
 结构说明  : R4_H 寄存器结构定义。地址偏移量:0x210，初值:0x00000000，宽度:32
 寄存器说明: 区域4色调的上下限值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  r4_lh    : 10; /* bit[0-9]  : 区域4的色调下限值 */
        unsigned int  reserved_0: 6;  /* bit[10-15]: 保留 */
        unsigned int  r4_hh    : 10; /* bit[16-25]: 区域4的色调上限值 */
        unsigned int  reserved_1: 6;  /* bit[26-31]: 保留 */
    } reg;
} SOC_DSS_DPP_R4_H_UNION;
#endif
#define SOC_DSS_DPP_R4_H_r4_lh_START     (0)
#define SOC_DSS_DPP_R4_H_r4_lh_END       (9)
#define SOC_DSS_DPP_R4_H_r4_hh_START     (16)
#define SOC_DSS_DPP_R4_H_r4_hh_END       (25)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_R5_H_UNION
 结构说明  : R5_H 寄存器结构定义。地址偏移量:0x214，初值:0x00000000，宽度:32
 寄存器说明: 区域5色调的上下限值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  r5_lh    : 10; /* bit[0-9]  : 区域5的色调下限值 */
        unsigned int  reserved_0: 6;  /* bit[10-15]: 保留 */
        unsigned int  r5_hh    : 10; /* bit[16-25]: 区域5的色调上限值 */
        unsigned int  reserved_1: 6;  /* bit[26-31]: 保留 */
    } reg;
} SOC_DSS_DPP_R5_H_UNION;
#endif
#define SOC_DSS_DPP_R5_H_r5_lh_START     (0)
#define SOC_DSS_DPP_R5_H_r5_lh_END       (9)
#define SOC_DSS_DPP_R5_H_r5_hh_START     (16)
#define SOC_DSS_DPP_R5_H_r5_hh_END       (25)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_R6_H_UNION
 结构说明  : R6_H 寄存器结构定义。地址偏移量:0x218，初值:0x00000000，宽度:32
 寄存器说明: 区域6色调的上下限值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  r6_lh    : 10; /* bit[0-9]  : 区域6的色调下限值 */
        unsigned int  reserved_0: 6;  /* bit[10-15]: 保留 */
        unsigned int  r6_hh    : 10; /* bit[16-25]: 区域6的色调上限值 */
        unsigned int  reserved_1: 6;  /* bit[26-31]: 保留 */
    } reg;
} SOC_DSS_DPP_R6_H_UNION;
#endif
#define SOC_DSS_DPP_R6_H_r6_lh_START     (0)
#define SOC_DSS_DPP_R6_H_r6_lh_END       (9)
#define SOC_DSS_DPP_R6_H_r6_hh_START     (16)
#define SOC_DSS_DPP_R6_H_r6_hh_END       (25)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_ACM_EN_UNION
 结构说明  : ACM_EN 寄存器结构定义。地址偏移量:0x21C，初值:0x00000000，宽度:32
 寄存器说明: 区域使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  acm_en        : 1;  /* bit[0]   : ACM使能寄存器 */
        unsigned int  reserved_0    : 3;  /* bit[1-3] : 保留 */
        unsigned int  acm_valid_num : 3;  /* bit[4-6] : 区域选择寄存器，色度调整区域选择 */
        unsigned int  reserved_1    : 25; /* bit[7-31]: 保留 */
    } reg;
} SOC_DSS_DPP_ACM_EN_UNION;
#endif
#define SOC_DSS_DPP_ACM_EN_acm_en_START         (0)
#define SOC_DSS_DPP_ACM_EN_acm_en_END           (0)
#define SOC_DSS_DPP_ACM_EN_acm_valid_num_START  (4)
#define SOC_DSS_DPP_ACM_EN_acm_valid_num_END    (6)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_ACM_MEM_CTRL_UNION
 结构说明  : ACM_MEM_CTRL 寄存器结构定义。地址偏移量:0x220，初值:0x00000000，宽度:32
 寄存器说明: MEM低功耗控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  acm_mem_ctrl : 4;  /* bit[0-3] : 调试寄存器，acm模块内memory低功耗配置：
                                                       [3]: reseverd; 
                                                       [2]: 软件配置模式下有效，为1表示进入Shut Down模式
                                                       [1]: 软件配置模式下有效，为1表示进入Deep Sleep模式
                                                       [0]: 软件配置模式下有效，为1表示进入Sleep模式 */
        unsigned int  reserved     : 28; /* bit[4-31]: 保留 */
    } reg;
} SOC_DSS_DPP_ACM_MEM_CTRL_UNION;
#endif
#define SOC_DSS_DPP_ACM_MEM_CTRL_acm_mem_ctrl_START  (0)
#define SOC_DSS_DPP_ACM_MEM_CTRL_acm_mem_ctrl_END    (3)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_CE_HIST_RESET_UNION
 结构说明  : CE_HIST_RESET 寄存器结构定义。地址偏移量:0x230，初值:0x00000000，宽度:32
 寄存器说明: 直方图统计清零
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ce_hist_reset : 1;  /* bit[0]   : 1’b1：将统计量清零。
                                                        1’b0：继续统计
                                                        对软件来说是写清寄存器，对硬件来说先将写1的动作记下来，等到帧同步到达后将直方图统计的信息清零。 */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_DPP_CE_HIST_RESET_UNION;
#endif
#define SOC_DSS_DPP_CE_HIST_RESET_ce_hist_reset_START  (0)
#define SOC_DSS_DPP_CE_HIST_RESET_ce_hist_reset_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_CE_HIST_CTL_UNION
 结构说明  : CE_HIST_CTL 寄存器结构定义。地址偏移量:0x234，初值:0x00000000，宽度:32
 寄存器说明: 直方图统计控制
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ce_hist_ctl : 3;  /* bit[0-2] : bit0: start 写1在帧同步达到后开始统计
                                                      bit1: cancle 写1后立即停止统计
                                                      bit2: stop 写1后等待帧同步到达后停止统计。 */
        unsigned int  reserved    : 29; /* bit[3-31]: 保留 */
    } reg;
} SOC_DSS_DPP_CE_HIST_CTL_UNION;
#endif
#define SOC_DSS_DPP_CE_HIST_CTL_ce_hist_ctl_START  (0)
#define SOC_DSS_DPP_CE_HIST_CTL_ce_hist_ctl_END    (2)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_CE_HIST_FRAME_CNT_UNION
 结构说明  : CE_HIST_FRAME_CNT 寄存器结构定义。地址偏移量:0x238，初值:0x00000000，宽度:32
 寄存器说明: 直方图统计的帧个数
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ce_hist_frame_cnt : 6;  /* bit[0-5] : 2560x1600 – 4
                                                            XGA (1024 x 768) - 21 
                                                            WSVGA (1024 x 600) - 27 
                                                            WVGA (800 x 480) - 43 
                                                            VGA (640 x 480) - 54 
                                                            Reset State: 0x0 */
        unsigned int  reserved          : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_DSS_DPP_CE_HIST_FRAME_CNT_UNION;
#endif
#define SOC_DSS_DPP_CE_HIST_FRAME_CNT_ce_hist_frame_cnt_START  (0)
#define SOC_DSS_DPP_CE_HIST_FRAME_CNT_ce_hist_frame_cnt_END    (5)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_CE_SIZE_UNION
 结构说明  : CE_SIZE 寄存器结构定义。地址偏移量:0x23C，初值:0x00000000，宽度:32
 寄存器说明: 图像的宽和高
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ce_height : 13; /* bit[0-12] : 图像的宽-1 */
        unsigned int  reserved_0: 3;  /* bit[13-15]: 保留 */
        unsigned int  ce_width  : 13; /* bit[16-28]: 图像的高-1 */
        unsigned int  reserved_1: 3;  /* bit[29-31]: 保留 */
    } reg;
} SOC_DSS_DPP_CE_SIZE_UNION;
#endif
#define SOC_DSS_DPP_CE_SIZE_ce_height_START  (0)
#define SOC_DSS_DPP_CE_SIZE_ce_height_END    (12)
#define SOC_DSS_DPP_CE_SIZE_ce_width_START   (16)
#define SOC_DSS_DPP_CE_SIZE_ce_width_END     (28)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_CE_NO_STAT_LINES_UNION
 结构说明  : CE_NO_STAT_LINES 寄存器结构定义。地址偏移量:0x240，初值:0x00000000，宽度:32
 寄存器说明: 最后一帧的最后几行不进行直方图统计
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ce_no_stat_lines : 8;  /* bit[0-7] : ce_hist_frame_cnt的值为n，第n帧之前的全部像素统计直方图，第n帧的最后ce_no_stat_lines行不统计。统计结束后就上报中断。 */
        unsigned int  reserved         : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_DSS_DPP_CE_NO_STAT_LINES_UNION;
#endif
#define SOC_DSS_DPP_CE_NO_STAT_LINES_ce_no_stat_lines_START  (0)
#define SOC_DSS_DPP_CE_NO_STAT_LINES_ce_no_stat_lines_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_CE_BLACK_REGION_THRE_UNION
 结构说明  : CE_BLACK_REGION_THRE 寄存器结构定义。地址偏移量:0x244，初值:0x00000000，宽度:32
 寄存器说明: 暗点阈值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ce_black_region_thre : 8;  /* bit[0-7] : 暗点阈值，灰度小于这个值暗点值加1 */
        unsigned int  reserved             : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_DSS_DPP_CE_BLACK_REGION_THRE_UNION;
#endif
#define SOC_DSS_DPP_CE_BLACK_REGION_THRE_ce_black_region_thre_START  (0)
#define SOC_DSS_DPP_CE_BLACK_REGION_THRE_ce_black_region_thre_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_CE_WHITE_REGION_THRE_UNION
 结构说明  : CE_WHITE_REGION_THRE 寄存器结构定义。地址偏移量:0x248，初值:0x00000000，宽度:32
 寄存器说明: 亮点阈值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ce_white_region_thre : 8;  /* bit[0-7] : 亮点阈值，灰度大于这个值亮点值加1 */
        unsigned int  reserved             : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_DSS_DPP_CE_WHITE_REGION_THRE_UNION;
#endif
#define SOC_DSS_DPP_CE_WHITE_REGION_THRE_ce_white_region_thre_START  (0)
#define SOC_DSS_DPP_CE_WHITE_REGION_THRE_ce_white_region_thre_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_CE_LUT_SEL_UNION
 结构说明  : CE_LUT_SEL 寄存器结构定义。地址偏移量:0x24C，初值:0x00000000，宽度:32
 寄存器说明: LUT表单乒乓选择
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ce_lut_sel : 1;  /* bit[0]   : 配置乒乓LUT的读写权限分配。
                                                     0：表示软件对LUT0具有写权限，芯片对LUT1具有读权限。
                                                     1：表示软件对LUT1具有写权限，芯片对LUT0具有读权限。 */
        unsigned int  reserved   : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_DPP_CE_LUT_SEL_UNION;
#endif
#define SOC_DSS_DPP_CE_LUT_SEL_ce_lut_sel_START  (0)
#define SOC_DSS_DPP_CE_LUT_SEL_ce_lut_sel_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_CE_LUT_ENABLE_UNION
 结构说明  : CE_LUT_ENABLE 寄存器结构定义。地址偏移量:0x250，初值:0x00000000，宽度:32
 寄存器说明: CE旁路选择
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ce_lut_enable  : 1;  /* bit[0]   : 1：Y分量的值作为LUT表的地址，得出新的Y分量。
                                                         0：CE旁路，Y分量不用查LUT表单直接送给后级。 */
        unsigned int  ce_hist_enable : 1;  /* bit[1]   : 1：ce直方图统计功能使能
                                                         0：ce直方图统计功能不使能 */
        unsigned int  reserved       : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_DSS_DPP_CE_LUT_ENABLE_UNION;
#endif
#define SOC_DSS_DPP_CE_LUT_ENABLE_ce_lut_enable_START   (0)
#define SOC_DSS_DPP_CE_LUT_ENABLE_ce_lut_enable_END     (0)
#define SOC_DSS_DPP_CE_LUT_ENABLE_ce_hist_enable_START  (1)
#define SOC_DSS_DPP_CE_LUT_ENABLE_ce_hist_enable_END    (1)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_CE_LUT_USING_IND_UNION
 结构说明  : CE_LUT_USING_IND 寄存器结构定义。地址偏移量:0x254，初值:0x00000000，宽度:32
 寄存器说明: LUT读写权限分配指示
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ce_lut_using_ind : 1;  /* bit[0]   : 指示目前乒乓LUT的读写权限的分配情况
                                                           0：表示软件对LUT0具有读写权限，芯对LUT1具有读写权限。
                                                           1：表示软件对LUT1具有读写权限，芯片LUT0具有读写权限。 */
        unsigned int  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_DPP_CE_LUT_USING_IND_UNION;
#endif
#define SOC_DSS_DPP_CE_LUT_USING_IND_ce_lut_using_ind_START  (0)
#define SOC_DSS_DPP_CE_LUT_USING_IND_ce_lut_using_ind_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_CE_STATE_IND_UNION
 结构说明  : CE_STATE_IND 寄存器结构定义。地址偏移量:0x258，初值:0x00000000，宽度:32
 寄存器说明: CE工作指示
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ce_state_ind : 1;  /* bit[0]   : 调试观测使用
                                                       1:CE模块处于工作状态
                                                       0：CE模块处于空闲状态 */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_DPP_CE_STATE_IND_UNION;
#endif
#define SOC_DSS_DPP_CE_STATE_IND_ce_state_ind_START  (0)
#define SOC_DSS_DPP_CE_STATE_IND_ce_state_ind_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_CE_MEM_CTRL_UNION
 结构说明  : CE_MEM_CTRL 寄存器结构定义。地址偏移量:0x25C，初值:0x00000000，宽度:32
 寄存器说明: CE MEM低功耗控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ce_lut_mem_ctrl : 4;  /* bit[0-3] : 调试寄存器，ce lut模块内memory低功耗配置： 
                                                          [3]: reseverd; 
                                                          [2]: 软件配置模式下有效，为1表示进入Shut Down模式
                                                          [1]: 软件配置模式下有效，为1表示进入Deep Sleep模式
                                                          [0]: 软件配置模式下有效，为1表示进入Sleep模式 */
        unsigned int  ce_his_mem_ctrl : 4;  /* bit[4-7] : 调试寄存器，ce his模块内memory低功耗配置：
                                                          [3]: reseverd; 
                                                          [2]: 软件配置模式下有效，为1表示进入Shut Down模式
                                                          [1]: 软件配置模式下有效，为1表示进入Deep Sleep模式
                                                          [0]: 软件配置模式下有效，为1表示进入Sleep模式 */
        unsigned int  reserved        : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_DSS_DPP_CE_MEM_CTRL_UNION;
#endif
#define SOC_DSS_DPP_CE_MEM_CTRL_ce_lut_mem_ctrl_START  (0)
#define SOC_DSS_DPP_CE_MEM_CTRL_ce_lut_mem_ctrl_END    (3)
#define SOC_DSS_DPP_CE_MEM_CTRL_ce_his_mem_ctrl_START  (4)
#define SOC_DSS_DPP_CE_MEM_CTRL_ce_his_mem_ctrl_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_CE_TOTALGRAY_UNION
 结构说明  : CE_TOTALGRAY 寄存器结构定义。地址偏移量:0x264，初值:0x00000000，宽度:32
 寄存器说明: 所有灰度总和
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ce_totalgray : 32; /* bit[0-31]: 总灰度 */
    } reg;
} SOC_DSS_DPP_CE_TOTALGRAY_UNION;
#endif
#define SOC_DSS_DPP_CE_TOTALGRAY_ce_totalgray_START  (0)
#define SOC_DSS_DPP_CE_TOTALGRAY_ce_totalgray_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_CE_TOTALPIXL_UNION
 结构说明  : CE_TOTALPIXL 寄存器结构定义。地址偏移量:0x268，初值:0x00000000，宽度:32
 寄存器说明: 所有像素的个数
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ce_totalpixl : 24; /* bit[0-23] : 统计的总像素个数。 */
        unsigned int  reserved     : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_DPP_CE_TOTALPIXL_UNION;
#endif
#define SOC_DSS_DPP_CE_TOTALPIXL_ce_totalpixl_START  (0)
#define SOC_DSS_DPP_CE_TOTALPIXL_ce_totalpixl_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_CE_MEAN_UNION
 结构说明  : CE_MEAN 寄存器结构定义。地址偏移量:0x26C，初值:0x00000000，宽度:32
 寄存器说明: 直方图最大值对应的灰度值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ce_mean  : 8;  /* bit[0-7] : 一个灰度值，这个灰度值对应的像素最多. */
        unsigned int  reserved : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_DSS_DPP_CE_MEAN_UNION;
#endif
#define SOC_DSS_DPP_CE_MEAN_ce_mean_START   (0)
#define SOC_DSS_DPP_CE_MEAN_ce_mean_END     (7)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_CE_PEC0_3_UNION
 结构说明  : CE_PEC0_3 寄存器结构定义。地址偏移量:0x270，初值:0x00000000，宽度:32
 寄存器说明: 分位数0~3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ce_pec0 : 8;  /* bit[0-7]  : 分位数0灰度值 */
        unsigned int  ce_pec1 : 8;  /* bit[8-15] : 分位数1灰度值 */
        unsigned int  ce_pec2 : 8;  /* bit[16-23]: 分位数2灰度值 */
        unsigned int  ce_pec3 : 8;  /* bit[24-31]: 分位数3灰度值 */
    } reg;
} SOC_DSS_DPP_CE_PEC0_3_UNION;
#endif
#define SOC_DSS_DPP_CE_PEC0_3_ce_pec0_START  (0)
#define SOC_DSS_DPP_CE_PEC0_3_ce_pec0_END    (7)
#define SOC_DSS_DPP_CE_PEC0_3_ce_pec1_START  (8)
#define SOC_DSS_DPP_CE_PEC0_3_ce_pec1_END    (15)
#define SOC_DSS_DPP_CE_PEC0_3_ce_pec2_START  (16)
#define SOC_DSS_DPP_CE_PEC0_3_ce_pec2_END    (23)
#define SOC_DSS_DPP_CE_PEC0_3_ce_pec3_START  (24)
#define SOC_DSS_DPP_CE_PEC0_3_ce_pec3_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_CE_PEC4_7_UNION
 结构说明  : CE_PEC4_7 寄存器结构定义。地址偏移量:0x274，初值:0x00000000，宽度:32
 寄存器说明: 分位数4~7
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ce_pec4 : 8;  /* bit[0-7]  : 分位数4灰度值 */
        unsigned int  ce_pec5 : 8;  /* bit[8-15] : 分位数5灰度值 */
        unsigned int  ce_pec6 : 8;  /* bit[16-23]: 分位数6灰度值 */
        unsigned int  ce_pec7 : 8;  /* bit[24-31]: 分位数7灰度值 */
    } reg;
} SOC_DSS_DPP_CE_PEC4_7_UNION;
#endif
#define SOC_DSS_DPP_CE_PEC4_7_ce_pec4_START  (0)
#define SOC_DSS_DPP_CE_PEC4_7_ce_pec4_END    (7)
#define SOC_DSS_DPP_CE_PEC4_7_ce_pec5_START  (8)
#define SOC_DSS_DPP_CE_PEC4_7_ce_pec5_END    (15)
#define SOC_DSS_DPP_CE_PEC4_7_ce_pec6_START  (16)
#define SOC_DSS_DPP_CE_PEC4_7_ce_pec6_END    (23)
#define SOC_DSS_DPP_CE_PEC4_7_ce_pec7_START  (24)
#define SOC_DSS_DPP_CE_PEC4_7_ce_pec7_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_CE_PEC8_UNION
 结构说明  : CE_PEC8 寄存器结构定义。地址偏移量:0x278，初值:0x00000000，宽度:32
 寄存器说明: 分位数8
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ce_pec8  : 8;  /* bit[0-7] : 分位数8灰度值 */
        unsigned int  reserved : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_DSS_DPP_CE_PEC8_UNION;
#endif
#define SOC_DSS_DPP_CE_PEC8_ce_pec8_START   (0)
#define SOC_DSS_DPP_CE_PEC8_ce_pec8_END     (7)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_CE_BLACK_NUM_UNION
 结构说明  : CE_BLACK_NUM 寄存器结构定义。地址偏移量:0x27C，初值:0x00000000，宽度:32
 寄存器说明: 暗点个数
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ce_black_num : 24; /* bit[0-23] : 暗点个数 */
        unsigned int  reserved     : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_DPP_CE_BLACK_NUM_UNION;
#endif
#define SOC_DSS_DPP_CE_BLACK_NUM_ce_black_num_START  (0)
#define SOC_DSS_DPP_CE_BLACK_NUM_ce_black_num_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_CE_WHITE_NUM_UNION
 结构说明  : CE_WHITE_NUM 寄存器结构定义。地址偏移量:0x280，初值:0x00000000，宽度:32
 寄存器说明: 亮点个数
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ce_white_num : 24; /* bit[0-23] : 亮点个数 */
        unsigned int  reserved     : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_DPP_CE_WHITE_NUM_UNION;
#endif
#define SOC_DSS_DPP_CE_WHITE_NUM_ce_white_num_START  (0)
#define SOC_DSS_DPP_CE_WHITE_NUM_ce_white_num_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_CE_HIST_RPT_IND_UNION
 结构说明  : CE_HIST_RPT_IND 寄存器结构定义。地址偏移量:0x284，初值:0x00000001，宽度:32
 寄存器说明: 上报直方图指示
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ce_hist_rpt_ind : 1;  /* bit[0]   : 0：表示读取直方图memory0的上报结果
                                                          1：表示读取直方图memory1的上报结果 */
        unsigned int  reserved        : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_DPP_CE_HIST_RPT_IND_UNION;
#endif
#define SOC_DSS_DPP_CE_HIST_RPT_IND_ce_hist_rpt_ind_START  (0)
#define SOC_DSS_DPP_CE_HIST_RPT_IND_ce_hist_rpt_ind_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_GAMA_SHORTBIT_EN_UNION
 结构说明  : GAMA_SHORTBIT_EN 寄存器结构定义。地址偏移量:0x300，初值:0x00000000，宽度:32
 寄存器说明: 输入数据有效位选择
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  shortbit_en : 1;  /* bit[0]   : 1：处理24bit的数据输入；
                                                      0：处理36bit的数据输入 */
        unsigned int  reserved    : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_DPP_GAMA_SHORTBIT_EN_UNION;
#endif
#define SOC_DSS_DPP_GAMA_SHORTBIT_EN_shortbit_en_START  (0)
#define SOC_DSS_DPP_GAMA_SHORTBIT_EN_shortbit_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_GAMA_BYPASS_EN_UNION
 结构说明  : GAMA_BYPASS_EN 寄存器结构定义。地址偏移量:0x304，初值:0x00000001，宽度:32
 寄存器说明: 旁路GAMA模块
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bypass_en : 1;  /* bit[0]   : 1：GAMA被旁路 */
        unsigned int  reserved  : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_DSS_DPP_GAMA_BYPASS_EN_UNION;
#endif
#define SOC_DSS_DPP_GAMA_BYPASS_EN_bypass_en_START  (0)
#define SOC_DSS_DPP_GAMA_BYPASS_EN_bypass_en_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_GAMA_MEM_CTRL_UNION
 结构说明  : GAMA_MEM_CTRL 寄存器结构定义。地址偏移量:0x308，初值:0x00000000，宽度:32
 寄存器说明: MEM低功耗控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gama_mem_ctrl : 4;  /* bit[0-3] : 调试寄存器，gama模块内memory低功耗配置：
                                                        [3]: reseverd; 
                                                        [2]: 软件配置模式下有效，为1表示进入Shut Down模式
                                                        [1]: 软件配置模式下有效，为1表示进入Deep Sleep模式
                                                        [0]: 软件配置模式下有效，为1表示进入Sleep模式 */
        unsigned int  reserved      : 28; /* bit[4-31]: 保留 */
    } reg;
} SOC_DSS_DPP_GAMA_MEM_CTRL_UNION;
#endif
#define SOC_DSS_DPP_GAMA_MEM_CTRL_gama_mem_ctrl_START  (0)
#define SOC_DSS_DPP_GAMA_MEM_CTRL_gama_mem_ctrl_END    (3)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_REG_DEFAULT_UNION
 结构说明  : REG_DEFAULT 寄存器结构定义。地址偏移量:0x030C，初值:0x00000000，宽度:32
 寄存器说明: 模块影子寄存器恢复到默认值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reg_default : 1;  /* bit[0]   :  */
        unsigned int  reserved    : 31; /* bit[1-31]:  */
    } reg;
} SOC_DSS_DPP_REG_DEFAULT_UNION;
#endif
#define SOC_DSS_DPP_REG_DEFAULT_reg_default_START  (0)
#define SOC_DSS_DPP_REG_DEFAULT_reg_default_END    (0)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_SBL_MEM_CTRL_UNION
 结构说明  : SBL_MEM_CTRL 寄存器结构定义。地址偏移量:0x310，初值:0x00000000，宽度:32
 寄存器说明: MEM低功耗控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sbl_mem_ctrl : 4;  /* bit[0-3] : 调试寄存器，sbl模块内memory低功耗配置：
                                                       [3]: reseverd; 
                                                       [2]: 软件配置模式下有效，为1表示进入Shut Down模式
                                                       [1]: 软件配置模式下有效，为1表示进入Deep Sleep模式
                                                       [0]: 软件配置模式下有效，为1表示进入Sleep模式 */
        unsigned int  reserved     : 28; /* bit[4-31]: 保留 */
    } reg;
} SOC_DSS_DPP_SBL_MEM_CTRL_UNION;
#endif
#define SOC_DSS_DPP_SBL_MEM_CTRL_sbl_mem_ctrl_START  (0)
#define SOC_DSS_DPP_SBL_MEM_CTRL_sbl_mem_ctrl_END    (3)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_DPP_DBG_UNION
 结构说明  : DPP_DBG 寄存器结构定义。地址偏移量:0x314，初值:0x00010000，宽度:32
 寄存器说明: DPP调试用寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dpp_dbg : 32; /* bit[0-31]: [31:18]:reserved;
                                                  [17]：sbl软复位使能。
                                                   1'b0：软复位不使能
                                                   1'b1：软复位使能
                                                  [16]：sbl软复位和硬件自清模式选择。
                                                   1'b0：选择sbl在underflow场景下的软复位模式
                                                   1'b1：选择sbl在underflow场景下的硬件自清模式
                                                  [15:4]:reserved;
                                                  [3]：选择ACM LUT软件可配的时间是否软件可控.
                                                   1'b0：软件不可控，软件在ACM不使能或者DPP非工作状态时可以配置ACM LUT；
                                                   1'b1：软件可控，软件可通过bit2来选择ACM LUT是否软件可配；
                                                  [2]：ACM LUT是否软件可配.
                                                   1'b0：此时ACM LUT软件可配，但是如果此时ACM正在工作，ACM从LUT读出的数为0；
                                                   1'b1：如果ACM使能，则软件不可配，如果ACM不使能，软件可配；
                                                  [1]：reserved;
                                                  [0]：选择送给SBL的frm_end来自DPP内部还是ldi_frm_end.
                                                   1'b0：DPP内部frm_end
                                                   1'b1： ldi_frm_end */
    } reg;
} SOC_DSS_DPP_DPP_DBG_UNION;
#endif
#define SOC_DSS_DPP_DPP_DBG_dpp_dbg_START  (0)
#define SOC_DSS_DPP_DPP_DBG_dpp_dbg_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_U_GAMA_COEF_UNION
 结构说明  : U_GAMA_COEF 寄存器结构定义。地址偏移量:0x0400，初值:0x00000000，宽度:32
 寄存器说明: GAMA系数查找表
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  u_gama_coef : 8;  /* bit[0-7] : GAMA系数查找表基地址，软件如需配置支持请联系设计人员 */
        unsigned int  reserved    : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_DPP_U_GAMA_COEF_UNION;
#endif
#define SOC_DSS_DPP_U_GAMA_COEF_u_gama_coef_START  (0)
#define SOC_DSS_DPP_U_GAMA_COEF_u_gama_coef_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_U_H_COEF_UNION
 结构说明  : U_H_COEF 寄存器结构定义。地址偏移量:0x1000，初值:0x00000000，宽度:32
 寄存器说明: ACM H分量查找表
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  h_l_out  : 10; /* bit[0-9]  : U_HL_COEF系数查找表基地址，软件如需配置支持请联系设计人员 */
        unsigned int  reserved_0: 6;  /* bit[10-15]: 保留 */
        unsigned int  h_r_out  : 10; /* bit[16-25]: U_HR_COEF系数查找表基地址，软件如需配置支持请联系设计人员 */
        unsigned int  reserved_1: 6;  /* bit[26-31]:  */
    } reg;
} SOC_DSS_DPP_U_H_COEF_UNION;
#endif
#define SOC_DSS_DPP_U_H_COEF_h_l_out_START   (0)
#define SOC_DSS_DPP_U_H_COEF_h_l_out_END     (9)
#define SOC_DSS_DPP_U_H_COEF_h_r_out_START   (16)
#define SOC_DSS_DPP_U_H_COEF_h_r_out_END     (25)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_U_SATA_COEF_UNION
 结构说明  : U_SATA_COEF 寄存器结构定义。地址偏移量:0x1A00，初值:0x00000000，宽度:32
 寄存器说明: ACM SATA分量查找表
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sata_l_out : 8;  /* bit[0-7]  : U_SATAL_COEF系数查找表基地址，软件如需配置支持请联系设计人员 */
        unsigned int  sata_r_out : 8;  /* bit[8-15] : U_SATAR_COEF系数查找表基地址，软件如需配置支持请联系设计人员 */
        unsigned int  reserved   : 16; /* bit[16-31]:  */
    } reg;
} SOC_DSS_DPP_U_SATA_COEF_UNION;
#endif
#define SOC_DSS_DPP_U_SATA_COEF_sata_l_out_START  (0)
#define SOC_DSS_DPP_U_SATA_COEF_sata_l_out_END    (7)
#define SOC_DSS_DPP_U_SATA_COEF_sata_r_out_START  (8)
#define SOC_DSS_DPP_U_SATA_COEF_sata_r_out_END    (15)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_U_SATR_COEF_UNION
 结构说明  : U_SATR_COEF 寄存器结构定义。地址偏移量:0x1C00，初值:0x00000000，宽度:32
 寄存器说明: ACM SATR分量查找表
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  satr_l_out : 8;  /* bit[0-7]  : U_SATRL_COEF系数查找表基地址，软件如需配置支持请联系设计人员 */
        unsigned int  satr_r_out : 8;  /* bit[8-15] : U_SATRR_COEF系数查找表基地址，软件如需配置支持请联系设计人员 */
        unsigned int  reserved   : 16; /* bit[16-31]:  */
    } reg;
} SOC_DSS_DPP_U_SATR_COEF_UNION;
#endif
#define SOC_DSS_DPP_U_SATR_COEF_satr_l_out_START  (0)
#define SOC_DSS_DPP_U_SATR_COEF_satr_l_out_END    (7)
#define SOC_DSS_DPP_U_SATR_COEF_satr_r_out_START  (8)
#define SOC_DSS_DPP_U_SATR_COEF_satr_r_out_END    (15)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_CE_HIST_RPT0_UNION
 结构说明  : CE_HIST_RPT0 寄存器结构定义。地址偏移量:0x2000～0x23FF，初值:0x00000000，宽度:32
 寄存器说明: 上报直方图memory0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ce_hist_rpt0 : 24; /* bit[0-23] : 当前子帧的直方图统计上报 */
        unsigned int  reserved     : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_DPP_CE_HIST_RPT0_UNION;
#endif
#define SOC_DSS_DPP_CE_HIST_RPT0_ce_hist_rpt0_START  (0)
#define SOC_DSS_DPP_CE_HIST_RPT0_ce_hist_rpt0_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_CE_HIST_RPT1_UNION
 结构说明  : CE_HIST_RPT1 寄存器结构定义。地址偏移量:0x2400～0x27FF，初值:0x00000000，宽度:32
 寄存器说明: 上报直方图memory1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ce_hist_rpt1 : 24; /* bit[0-23] : 当前子帧的直方图统计上报 */
        unsigned int  reserved     : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_DSS_DPP_CE_HIST_RPT1_UNION;
#endif
#define SOC_DSS_DPP_CE_HIST_RPT1_ce_hist_rpt1_START  (0)
#define SOC_DSS_DPP_CE_HIST_RPT1_ce_hist_rpt1_END    (23)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_CE_LUT0_UNION
 结构说明  : CE_LUT0 寄存器结构定义。地址偏移量:0x2800，初值:0x00000000，宽度:32
 寄存器说明: LUT 表单 memory0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ce_lut0 : 8;  /* bit[0-7] : 当前子帧使用的LUT查找表基地址，软件如需配置支持请联系设计人员 */
        unsigned int  reserved: 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_DSS_DPP_CE_LUT0_UNION;
#endif
#define SOC_DSS_DPP_CE_LUT0_ce_lut0_START  (0)
#define SOC_DSS_DPP_CE_LUT0_ce_lut0_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_CE_LUT1_UNION
 结构说明  : CE_LUT1 寄存器结构定义。地址偏移量:0x2C00，初值:0x00000000，宽度:32
 寄存器说明: LUT 表单 memory1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ce_lut1 : 8;  /* bit[0-7] : 当前子帧使用的LUT查找表基地址，软件如需配置支持请联系设计人员 */
        unsigned int  reserved: 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_DSS_DPP_CE_LUT1_UNION;
#endif
#define SOC_DSS_DPP_CE_LUT1_ce_lut1_START  (0)
#define SOC_DSS_DPP_CE_LUT1_ce_lut1_END    (7)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_U_GMP_COEF_UNION
 结构说明  : U_GMP_COEF 寄存器结构定义。地址偏移量:0x3000～0x7CCF，初值:0x00000000，宽度:32
 寄存器说明: GMP查找表
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  u_gmp_coef : 32; /* bit[0-31]: GMP查找表 */
    } reg;
} SOC_DSS_DPP_U_GMP_COEF_UNION;
#endif
#define SOC_DSS_DPP_U_GMP_COEF_u_gmp_coef_START  (0)
#define SOC_DSS_DPP_U_GMP_COEF_u_gmp_coef_END    (31)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_U_IGM_R_COEF_UNION
 结构说明  : U_IGM_R_COEF 寄存器结构定义。地址偏移量:0xB000，初值:0x00000000，宽度:32
 寄存器说明: IGM R分量查找表
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  u_igm_r_coef : 12; /* bit[0-11] : IGM R分量查找表基地址，软件如需配置支持请联系设计人员 */
        unsigned int  reserved     : 20; /* bit[12-31]:  */
    } reg;
} SOC_DSS_DPP_U_IGM_R_COEF_UNION;
#endif
#define SOC_DSS_DPP_U_IGM_R_COEF_u_igm_r_coef_START  (0)
#define SOC_DSS_DPP_U_IGM_R_COEF_u_igm_r_coef_END    (11)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_U_IGM_G_COEF_UNION
 结构说明  : U_IGM_G_COEF 寄存器结构定义。地址偏移量:0xB400，初值:0x00000000，宽度:32
 寄存器说明: IGM G分量查找表
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  u_igm_g_coef : 12; /* bit[0-11] : IGM G分量查找表基地址，软件如需配置支持请联系设计人员 */
        unsigned int  reserved     : 20; /* bit[12-31]:  */
    } reg;
} SOC_DSS_DPP_U_IGM_G_COEF_UNION;
#endif
#define SOC_DSS_DPP_U_IGM_G_COEF_u_igm_g_coef_START  (0)
#define SOC_DSS_DPP_U_IGM_G_COEF_u_igm_g_coef_END    (11)


/*****************************************************************************
 结构名    : SOC_DSS_DPP_U_IGM_B_COEF_UNION
 结构说明  : U_IGM_B_COEF 寄存器结构定义。地址偏移量:0xB800，初值:0x00000000，宽度:32
 寄存器说明: IGM B分量查找表
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  u_igm_b_coef : 12; /* bit[0-11] : IGM B分量查找表基地址，软件如需配置支持请联系设计人员 */
        unsigned int  reserved     : 20; /* bit[12-31]:  */
    } reg;
} SOC_DSS_DPP_U_IGM_B_COEF_UNION;
#endif
#define SOC_DSS_DPP_U_IGM_B_COEF_u_igm_b_coef_START  (0)
#define SOC_DSS_DPP_U_IGM_B_COEF_u_igm_b_coef_END    (11)






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

#endif /* end of soc_dss_dpp_interface.h */
