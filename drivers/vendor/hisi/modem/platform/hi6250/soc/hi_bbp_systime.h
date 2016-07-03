/******************************************************************************/
/*  Copyright (C), 2007-2013, Hisilicon Technologies Co., Ltd. */
/******************************************************************************/
/* File name		: hi_bbp_systime.h */
/* Version		: 2.0 */
/* Autho			: xxx*/
/* Created		: 2013-02-26*/
/* Last Modified	: */
/* Description		:  The C union definition file for the module bbp_systime*/
/* Function List	: */
/* History		: */
/* 1 Date		: */
/* Modification 	: Create file */
/******************************************************************************/

#ifndef __HI_BBP_SYSTIME_H__
#define __HI_BBP_SYSTIME_H__
#include "product_config.h"
/*
 * Project: hi
 * Module : bbp_systime
 */

#ifndef HI_SET_GET
#define HI_SET_GET(a0,a1,a2,a3,a4)
#endif

/********************************************************************************/
/*    bbp_systime 寄存器偏移定义（项目名_模块名_寄存器名_OFFSET)        */
/********************************************************************************/
#ifdef BSP_CONFIG_K3V3_SFT
#define    HI_BBP_SYSTIME_ABS_TIMER_L_OFFSET                 0x1008 /* DRX绝对定时的低32位 */
#define    HI_BBP_SYSTIME_ABS_TIMER_H_OFFSET                 0x100c /* DRX绝对定时的高32位 */
#else
#define    HI_BBP_SYSTIME_ABS_TIMER_L_OFFSET                 0x534 /* DRX绝对定时的低32位 */
#define    HI_BBP_SYSTIME_ABS_TIMER_H_OFFSET                 0x538 /* DRX绝对定时的高32位 */
#endif

#ifndef __ASSEMBLY__

/********************************************************************************/
/*    bbp_systime 寄存器定义（项目名_模块名_寄存器名_T)        */
/********************************************************************************/
typedef union
{
    struct
    {
        unsigned int    fpga_version               : 32; /* [31..0] F1版本号 */
    } bits;
    unsigned int    u32;
}HI_BBP_SYSTIME_FPGA_VERSION_T;    /* F1版本号 */

typedef union
{
    struct
    {
        unsigned int    abs_timer_l                : 32; /* [31..0] DRX绝对定时的低32位 */
    } bits;
    unsigned int    u32;
}HI_BBP_SYSTIME_ABS_TIMER_L_T;    /* DRX绝对定时的低32位 */

typedef union
{
    struct
    {
        unsigned int    abs_timer_h                : 32; /* [31..0] DRX绝对定时的高32位 */
    } bits;
    unsigned int    u32;
}HI_BBP_SYSTIME_ABS_TIMER_H_T;    /* DRX绝对定时的高32位 */

typedef union
{
    struct
    {
        unsigned int    drp_data                   : 32; /* [31..0] DRP数据 */
    } bits;
    unsigned int    u32;
}HI_BBP_SYSTIME_DRP_DATA_T;    /* DRP数据 */

typedef union
{
    struct
    {
        unsigned int    abb_rst                    : 32; /* [31..0] ABB复位控制 */
    } bits;
    unsigned int    u32;
}HI_BBP_SYSTIME_ABB_RST_T;    /* ABB复位控制 */


/********************************************************************************/
/*    bbp_systime 函数（项目名_模块名_寄存器名_成员名_set)        */
/********************************************************************************/
#if 0
HI_SET_GET(hi_bbp_systime_abs_timer_l_abs_timer_l,abs_timer_l,HI_BBP_SYSTIME_ABS_TIMER_L_T,HI_BBP_SYSTIME_BASE_ADDR, HI_BBP_SYSTIME_ABS_TIMER_L_OFFSET)
HI_SET_GET(hi_bbp_systime_abs_timer_h_abs_timer_h,abs_timer_h,HI_BBP_SYSTIME_ABS_TIMER_H_T,HI_BBP_SYSTIME_BASE_ADDR, HI_BBP_SYSTIME_ABS_TIMER_H_OFFSET)
#endif
#endif

#endif // __HI_BBP_SYSTIME_H__

