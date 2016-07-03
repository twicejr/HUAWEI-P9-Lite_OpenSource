/******************************************************************************/
/*  Copyright (C), 2007-2013, Hisilicon Technologies Co., Ltd. */
/******************************************************************************/
/* File name     : hi_wdt.h */
/* Version       : 2.0 */
/* Created       : 2013-02-01*/
/* Last Modified : */
/* Description   :  The C union definition file for the module wdt*/
/* Function List : */
/* History       : */
/* 1 Date        : */
/* Modification  : Create file */
/******************************************************************************/

#ifndef __HI_WDT_H__
#define __HI_WDT_H__

/*
 * Project: hi
 * Module : wdt
 */

#ifndef HI_SET_GET
#define HI_SET_GET(a0,a1,a2,a3,a4)
#endif

/********************************************************************************/
/*    wdt 寄存器偏移定义（项目名_模块名_寄存器名_OFFSET)        */
/********************************************************************************/
#define    HI_WDG_LOAD_OFFSET                                (0x0) /* 计数初值寄存器，配置WatchDog内部计数器的计数初值。 */
#define    HI_WDG_VALUE_OFFSET                               (0x4) /* 计数器当前值寄存器，读出WatchDog内部计数器的当前计数值。 */
#define    HI_WDG_CONTROL_OFFSET                             (0x8) /* 控制寄存器，控制WatchDog的打开/关闭、中断和复位功能。 */
#define    HI_WDG_INTCLR_OFFSET                              (0xC) /* 中断清除寄存器。清除WatchDog中断，使WatchDog重新载入初值进行计数。本寄存器是只写寄存器，写进去任意值，都会引起WatchDog清中断，内部并不记忆写入的值，无复位值。 */
#define    HI_WDG_RIS_OFFSET                                 (0x10) /* 原始中断寄存器。 */
#define    HI_WDG_MIS_OFFSET                                 (0x14) /* 屏蔽后中断寄存器。 */
#define    HI_WDG_LOCK_OFFSET                                (0xC00) /* LOCK寄存器，控制WatchDog寄存器的读写权限。 */
#define		HI_WDG_SYSCTRL_ENABLE_OFFSET				(0x33C)/*读取系统控制寄存器33c bit[0] ,0打开看门狗，1关闭看门狗*/
/********************************************************************************/
/*    wdt 寄存器定义（项目名_模块名_寄存器名_T)        */
/********************************************************************************/
typedef union
{
    struct
    {
        unsigned int    wdg_load                   : 32; /* [31..0] Watchdog内部递减计数器的初始值。该值一旦被刷新，立即触发计数器计数。 */
    } bits;
    unsigned int    u32;
}HI_WDG_LOAD_T;    /* 计数初值寄存器，配置WatchDog内部计数器的计数初值。 */

typedef union
{
    struct
    {
        unsigned int    wdogvalue                  : 32; /* [31..0] 正在递减计数的计数器当前值。 */
    } bits;
    unsigned int    u32;
}HI_WDG_VALUE_T;    /* 计数器当前值寄存器，读出WatchDog内部计数器的当前计数值。 */

typedef union
{
    struct
    {
        unsigned int    inten                      : 1; /* [0..0] WatchDog中断信号输出使能。0：计数器停止计数，计数值保持当前值不变，WatchDog被关闭；1：既启动计数器又使能中断，WatchDog被启动。若中断先前被禁止，则当中断再次被使能时，计数器从寄存器WdogLoad中载入初值并重新开始计数。 */
        unsigned int    resen                      : 1; /* [1..1] WatchDog复位信号输出使能。0：禁止；1：使能。 */
        unsigned int    reserved                   : 30; /* [31..2] 保留。 */
    } bits;
    unsigned int    u32;
}HI_WDG_CONTROL_T;    /* 控制寄存器，控制WatchDog的打开/关闭、中断和复位功能。 */

typedef union
{
    struct
    {
        unsigned int    wdg_intclr                 : 32; /* [31..0] 对该寄存器写入任意值可清除WatchDog的中断，并使WatchDog从寄存器WDG_LOAD中重新载入初值重新计数。 */
    } bits;
    unsigned int    u32;
}HI_WDG_INTCLR_T;    /* 中断清除寄存器。清除WatchDog中断，使WatchDog重新载入初值进行计数。本寄存器是只写寄存器，写进去任意值，都会引起WatchDog清中断，内部并不记忆写入的值，无复位值。 */

typedef union
{
    struct
    {
        unsigned int    wdogris                    : 1; /* [0..0] WatchDog原始中断状态，当计数器的计数值递减到0时，该位置1。0：未产生中断；1：已产生中断。 */
        unsigned int    reserved                   : 31; /* [31..1] 保留。 */
    } bits;
    unsigned int    u32;
}HI_WDG_RIS_T;    /* 原始中断寄存器。 */

typedef union
{
    struct
    {
        unsigned int    wdogmis                    : 1; /* [0..0] WatchDog的屏蔽后中断状态。0：未产生中断或者中断被屏蔽；1：已产生中断。 */
        unsigned int    reserved                   : 31; /* [31..1] 保留。 */
    } bits;
    unsigned int    u32;
}HI_WDG_MIS_T;    /* 屏蔽后中断寄存器。 */

typedef union
{
    struct
    {
        unsigned int    wdg_lock                   : 32; /* [31..0] 向该寄存器写入0x1ACC_E551，可打开所有寄存器的写权限；向该寄存器写入其他值则关闭写权限。读该寄存器返回加锁的状态而不是写入该寄存器的值：0x0000_0000：允许写访问（未加锁）；0x0000_0001：禁止写访问（已加锁）。 */
    } bits;
    unsigned int    u32;
}HI_WDG_LOCK_T;    /* LOCK寄存器，控制WatchDog寄存器的读写权限。 */


/********************************************************************************/
/*    wdt 函数（项目名_模块名_寄存器名_成员名_set)        */
/********************************************************************************/
HI_SET_GET(hi_wdg_load_wdg_load,wdg_load,HI_WDG_LOAD_T,HI_WDT_BASE_ADDR, HI_WDG_LOAD_OFFSET)
HI_SET_GET(hi_wdg_value_wdogvalue,wdogvalue,HI_WDG_VALUE_T,HI_WDT_BASE_ADDR, HI_WDG_VALUE_OFFSET)
HI_SET_GET(hi_wdg_control_inten,inten,HI_WDG_CONTROL_T,HI_WDT_BASE_ADDR, HI_WDG_CONTROL_OFFSET)
HI_SET_GET(hi_wdg_control_resen,resen,HI_WDG_CONTROL_T,HI_WDT_BASE_ADDR, HI_WDG_CONTROL_OFFSET)
HI_SET_GET(hi_wdg_control_reserved,reserved,HI_WDG_CONTROL_T,HI_WDT_BASE_ADDR, HI_WDG_CONTROL_OFFSET)
HI_SET_GET(hi_wdg_intclr_wdg_intclr,wdg_intclr,HI_WDG_INTCLR_T,HI_WDT_BASE_ADDR, HI_WDG_INTCLR_OFFSET)
HI_SET_GET(hi_wdg_ris_wdogris,wdogris,HI_WDG_RIS_T,HI_WDT_BASE_ADDR, HI_WDG_RIS_OFFSET)
HI_SET_GET(hi_wdg_ris_reserved,reserved,HI_WDG_RIS_T,HI_WDT_BASE_ADDR, HI_WDG_RIS_OFFSET)
HI_SET_GET(hi_wdg_mis_wdogmis,wdogmis,HI_WDG_MIS_T,HI_WDT_BASE_ADDR, HI_WDG_MIS_OFFSET)
HI_SET_GET(hi_wdg_mis_reserved,reserved,HI_WDG_MIS_T,HI_WDT_BASE_ADDR, HI_WDG_MIS_OFFSET)
HI_SET_GET(hi_wdg_lock_wdg_lock,wdg_lock,HI_WDG_LOCK_T,HI_WDT_BASE_ADDR, HI_WDG_LOCK_OFFSET)

#endif // __HI_WDT_H__

