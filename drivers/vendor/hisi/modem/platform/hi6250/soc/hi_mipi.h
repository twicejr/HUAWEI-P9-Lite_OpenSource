/******************************************************************************/
/*  Copyright (C), 2007-2013, Hisilicon Technologies Co., Ltd. */
/******************************************************************************/
/* File name     : hi_mipi.h */
/* Version       : 2.0 */
/* Created       : 2013-03-19*/
/* Last Modified : */
/* Description   :  The C union definition file for the module mipi*/
/* Function List : */
/* History       : */
/* 1 Date        : */
/* Modification  : Create file */
/******************************************************************************/

#ifndef __HI_MIPI_H__
#define __HI_MIPI_H__

/*
 * Project: hi
 * Module : mipi
 */

#ifndef HI_SET_GET_MIPI
#define HI_SET_GET_MIPI(a0,a1,a2,a3,a4)
#endif

/********************************************************************************/
/*    mipi 寄存器偏移定义（项目名_模块名_寄存器名_OFFSET)        */
/********************************************************************************/
#define    MIPI_MIPI0_RD_DATA_LOW_SOFT_OFFSET            (0x780) /* 寄存器 */
#define    MIPI_MIPI0_RD_DATA_HIGH_SOFT_OFFSET           (0x784) /* 寄存器 */
#define    MIPI_RD_END_FLAG_MIPI0_SOFT_OFFSET            (0x788) /* 寄存器 */
#define    MIPI_MIPI0_GRANT_DSP_OFFSET                   (0x78c) /* 寄存器 */
#define    MIPI_DSP_MIPI0_WDATA_LOW_OFFSET               (0x790) /* 寄存器 */
#define    MIPI_DSP_MIPI0_WDATA_HIGH_OFFSET              (0x794) /* 寄存器 */
#define    MIPI_DSP_MIPI0_EN_IMI_OFFSET                  (0x798) /* 寄存器 */
#define    MIPI_DSP_MIPI0_CFG_IND_IMI_OFFSET             (0x79c) /* 寄存器 */
#define    MIPI_DSP_MIPI0_RD_CLR_OFFSET                  (0x7a0) /* 寄存器 */

/********************************************************************************/
/*    mipi 寄存器定义（项目名_模块名_寄存器名_T)        */
/********************************************************************************/
typedef union
{
    struct
    {
        unsigned int    mipi0_rd_data_low_soft     : 32; /* [31..0] 由软件直接控制MIPI0 master,不借助xbbp发送回读指令时,回读指令存放低32bit. */
    } bits;
    unsigned int    u32;
}MIPI_MIPI0_RD_DATA_LOW_SOFT_T;    /* 寄存器 */

typedef union
{
    struct
    {
        unsigned int    mipi0_rd_data_high_soft    : 32; /* [31..0] 由软件直接控制MIPI0 master,不借助xbbp发送回读指令时,回读指令存放高32bit. */
    } bits;
    unsigned int    u32;
}MIPI_MIPI0_RD_DATA_HIGH_SOFT_T;    /* 寄存器 */

typedef union
{
    struct
    {
        unsigned int    rd_end_flag_mipi0_soft     : 1; /* [0..0] 由软件直接控制MIPI0 master,不借助xbbp发送回读指令时,回读数据有效指示 */
        unsigned int    Reserved                   : 31; /* [31..1]  */
    } bits;
    unsigned int    u32;
}MIPI_RD_END_FLAG_MIPI0_SOFT_T;    /* 寄存器 */

typedef union
{
    struct
    {
        unsigned int    mipi0_grant_dsp            : 1; /* [0..0] 由软件直接控制MIPI0 master1:软件可以发送CFG_IND启动mipi00:软件等待mipi0授权使用 */
        unsigned int    Reserved                   : 31; /* [31..1]  */
    } bits;
    unsigned int    u32;
}MIPI_MIPI0_GRANT_DSP_T;    /* 寄存器 */

typedef union
{
    struct
    {
        unsigned int    dsp_mipi0_wdata_low        : 32; /* [31..0] 由软件直接控制MIPI0 master,不借助xbbp发送写指令时,写指令低32bit */
    } bits;
    unsigned int    u32;
}MIPI_DSP_MIPI0_WDATA_LOW_T;    /* 寄存器 */

typedef union
{
    struct
    {
        unsigned int    dsp_mipi0_wdata_high       : 32; /* [31..0] 由软件直接控制MIPI0 master,不借助xbbp发送写指令时,写指令高32bit */
    } bits;
    unsigned int    u32;
}MIPI_DSP_MIPI0_WDATA_HIGH_T;    /* 寄存器 */

typedef union
{
    struct
    {
        unsigned int    dsp_mipi0_en_imi           : 1; /* [0..0] 由软件直接控制MIPI0 master,需首先拉高此指示,屏蔽xbbp对MIPI0的控制 */
        unsigned int    Reserved                   : 31; /* [31..1]  */
    } bits;
    unsigned int    u32;
}MIPI_DSP_MIPI0_EN_IMI_T;    /* 寄存器 */

typedef union
{
    struct
    {
        unsigned int    dsp_mipi0_cfg_ind_imi      : 1; /* [0..0] 由软件直接控制MIPI0 master,拉高此dsp_mipi0_en后,产生软件启动脉冲 */
        unsigned int    Reserved                   : 31; /* [31..1]  */
    } bits;
    unsigned int    u32;
}MIPI_DSP_MIPI0_CFG_IND_IMI_T;    /* 寄存器 */

typedef union
{
    struct
    {
        unsigned int    dsp_mipi0_rd_clr           : 1; /* [0..0] 由软件直接控制MIPI0 master,取走回读数据后,清标志位脉冲 */
        unsigned int    Reserved                   : 31; /* [31..1]  */
    } bits;
    unsigned int    u32;
}MIPI_DSP_MIPI0_RD_CLR_T;    /* 寄存器 */


/********************************************************************************/
/*    mipi 函数（项目名_模块名_寄存器名_成员名_set)        */
/********************************************************************************/
HI_SET_GET_MIPI(mipi_mipi0_rd_data_low_soft_mipi0_rd_data_low_soft,mipi0_rd_data_low_soft,MIPI_MIPI0_RD_DATA_LOW_SOFT_T,MIPI_BASE_ADDR, MIPI_MIPI0_RD_DATA_LOW_SOFT_OFFSET)
HI_SET_GET_MIPI(mipi_mipi0_rd_data_high_soft_mipi0_rd_data_high_soft,mipi0_rd_data_high_soft,MIPI_MIPI0_RD_DATA_HIGH_SOFT_T,MIPI_BASE_ADDR, MIPI_MIPI0_RD_DATA_HIGH_SOFT_OFFSET)
HI_SET_GET_MIPI(mipi_rd_end_flag_mipi0_soft_rd_end_flag_mipi0_soft,rd_end_flag_mipi0_soft,MIPI_RD_END_FLAG_MIPI0_SOFT_T,MIPI_BASE_ADDR, MIPI_RD_END_FLAG_MIPI0_SOFT_OFFSET)
HI_SET_GET_MIPI(mipi_rd_end_flag_mipi0_soft_reserved,Reserved,MIPI_RD_END_FLAG_MIPI0_SOFT_T,MIPI_BASE_ADDR, MIPI_RD_END_FLAG_MIPI0_SOFT_OFFSET)
HI_SET_GET_MIPI(mipi_mipi0_grant_dsp_mipi0_grant_dsp,mipi0_grant_dsp,MIPI_MIPI0_GRANT_DSP_T,MIPI_BASE_ADDR, MIPI_MIPI0_GRANT_DSP_OFFSET)
HI_SET_GET_MIPI(mipi_mipi0_grant_dsp_reserved,Reserved,MIPI_MIPI0_GRANT_DSP_T,MIPI_BASE_ADDR, MIPI_MIPI0_GRANT_DSP_OFFSET)
HI_SET_GET_MIPI(mipi_dsp_mipi0_wdata_low_dsp_mipi0_wdata_low,dsp_mipi0_wdata_low,MIPI_DSP_MIPI0_WDATA_LOW_T,MIPI_BASE_ADDR, MIPI_DSP_MIPI0_WDATA_LOW_OFFSET)
HI_SET_GET_MIPI(mipi_dsp_mipi0_wdata_high_dsp_mipi0_wdata_high,dsp_mipi0_wdata_high,MIPI_DSP_MIPI0_WDATA_HIGH_T,MIPI_BASE_ADDR, MIPI_DSP_MIPI0_WDATA_HIGH_OFFSET)
HI_SET_GET_MIPI(mipi_dsp_mipi0_en_imi_dsp_mipi0_en_imi,dsp_mipi0_en_imi,MIPI_DSP_MIPI0_EN_IMI_T,MIPI_BASE_ADDR, MIPI_DSP_MIPI0_EN_IMI_OFFSET)
HI_SET_GET_MIPI(mipi_dsp_mipi0_en_imi_reserved,Reserved,MIPI_DSP_MIPI0_EN_IMI_T,MIPI_BASE_ADDR, MIPI_DSP_MIPI0_EN_IMI_OFFSET)
HI_SET_GET_MIPI(mipi_dsp_mipi0_cfg_ind_imi_dsp_mipi0_cfg_ind_imi,dsp_mipi0_cfg_ind_imi,MIPI_DSP_MIPI0_CFG_IND_IMI_T,MIPI_BASE_ADDR, MIPI_DSP_MIPI0_CFG_IND_IMI_OFFSET)
HI_SET_GET_MIPI(mipi_dsp_mipi0_cfg_ind_imi_reserved,Reserved,MIPI_DSP_MIPI0_CFG_IND_IMI_T,MIPI_BASE_ADDR, MIPI_DSP_MIPI0_CFG_IND_IMI_OFFSET)
HI_SET_GET_MIPI(mipi_dsp_mipi0_rd_clr_dsp_mipi0_rd_clr,dsp_mipi0_rd_clr,MIPI_DSP_MIPI0_RD_CLR_T,MIPI_BASE_ADDR, MIPI_DSP_MIPI0_RD_CLR_OFFSET)
HI_SET_GET_MIPI(mipi_dsp_mipi0_rd_clr_reserved,Reserved,MIPI_DSP_MIPI0_RD_CLR_T,MIPI_BASE_ADDR, MIPI_DSP_MIPI0_RD_CLR_OFFSET)

#endif // __HI_MIPI_H__

