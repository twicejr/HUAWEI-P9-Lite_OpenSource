/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_isp_watchdog_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:22:11
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_ISP_WatchDog.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_ISP_WATCHDOG_INTERFACE_H__
#define __SOC_ISP_WATCHDOG_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) WatchDog
 ****************************************************************************/
/* 寄存器说明：计数初值寄存器，配置WatchDog内部计数器的计数初值。
   位域定义UNION结构:  SOC_ISP_WatchDog_WDG_LOAD_UNION */
#define SOC_ISP_WatchDog_WDG_LOAD_ADDR(base)          ((base) + (0x0000))

/* 寄存器说明：计数器当前值寄存器，读出WatchDog内部计数器的当前计数值。
   位域定义UNION结构:  SOC_ISP_WatchDog_WDG_VALUE_UNION */
#define SOC_ISP_WatchDog_WDG_VALUE_ADDR(base)         ((base) + (0x0004))

/* 寄存器说明：控制寄存器，控制WatchDog的打开/关闭、中断和复位功能。
   位域定义UNION结构:  SOC_ISP_WatchDog_WDG_CONTROL_UNION */
#define SOC_ISP_WatchDog_WDG_CONTROL_ADDR(base)       ((base) + (0x0008))

/* 寄存器说明：中断清除寄存器。清除WatchDog中断，使WatchDog重新载入初值进行计数。本寄存器是只写寄存器，写进去任意值，都会引起WatchDog清中断，内部并不记忆写入的值，无复位值。
   位域定义UNION结构:  SOC_ISP_WatchDog_WDG_INTCLR_UNION */
#define SOC_ISP_WatchDog_WDG_INTCLR_ADDR(base)        ((base) + (0x000C))

/* 寄存器说明：原始中断寄存器。
   位域定义UNION结构:  SOC_ISP_WatchDog_WDG_RIS_UNION */
#define SOC_ISP_WatchDog_WDG_RIS_ADDR(base)           ((base) + (0x0010))

/* 寄存器说明：屏蔽后中断寄存器。
   位域定义UNION结构:  SOC_ISP_WatchDog_WDG_MIS_UNION */
#define SOC_ISP_WatchDog_WDG_MIS_ADDR(base)           ((base) + (0x0014))

/* 寄存器说明：LOCK寄存器，控制WatchDog寄存器的读写权限。
   位域定义UNION结构:  SOC_ISP_WatchDog_WDG_LOCK_UNION */
#define SOC_ISP_WatchDog_WDG_LOCK_ADDR(base)          ((base) + (0x0C00))





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
                     (1/1) WatchDog
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_ISP_WatchDog_WDG_LOAD_UNION
 结构说明  : WDG_LOAD 寄存器结构定义。地址偏移量:0x0000，初值:0xFFFFFFFF，宽度:32
 寄存器说明: 计数初值寄存器，配置WatchDog内部计数器的计数初值。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wdg_load : 32; /* bit[0-31]: Watchdog内部递减计数器的初始值。该值一旦被刷新，立即触发计数器计数。 */
    } reg;
} SOC_ISP_WatchDog_WDG_LOAD_UNION;
#endif
#define SOC_ISP_WatchDog_WDG_LOAD_wdg_load_START  (0)
#define SOC_ISP_WatchDog_WDG_LOAD_wdg_load_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_WatchDog_WDG_VALUE_UNION
 结构说明  : WDG_VALUE 寄存器结构定义。地址偏移量:0x0004，初值:0xFFFFFFFF，宽度:32
 寄存器说明: 计数器当前值寄存器，读出WatchDog内部计数器的当前计数值。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wdogvalue : 32; /* bit[0-31]: 正在递减计数的计数器当前值。 */
    } reg;
} SOC_ISP_WatchDog_WDG_VALUE_UNION;
#endif
#define SOC_ISP_WatchDog_WDG_VALUE_wdogvalue_START  (0)
#define SOC_ISP_WatchDog_WDG_VALUE_wdogvalue_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_WatchDog_WDG_CONTROL_UNION
 结构说明  : WDG_CONTROL 寄存器结构定义。地址偏移量:0x0008，初值:0x00000000，宽度:32
 寄存器说明: 控制寄存器，控制WatchDog的打开/关闭、中断和复位功能。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  inten    : 1;  /* bit[0]   : WatchDog中断信号输出使能。
                                                   0：计数器停止计数，计数值保持当前值不变，WatchDog被关闭；
                                                   1：既启动计数器又使能中断，WatchDog被启动。
                                                   若中断先前被禁止，则当中断再次被使能时，计数器从寄存器WdogLoad中载入初值并重新开始计数。 */
        unsigned int  resen    : 1;  /* bit[1]   : WatchDog复位信号输出使能。
                                                   0：禁止；
                                                   1：使能。 */
        unsigned int  reserved : 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_ISP_WatchDog_WDG_CONTROL_UNION;
#endif
#define SOC_ISP_WatchDog_WDG_CONTROL_inten_START     (0)
#define SOC_ISP_WatchDog_WDG_CONTROL_inten_END       (0)
#define SOC_ISP_WatchDog_WDG_CONTROL_resen_START     (1)
#define SOC_ISP_WatchDog_WDG_CONTROL_resen_END       (1)


/*****************************************************************************
 结构名    : SOC_ISP_WatchDog_WDG_INTCLR_UNION
 结构说明  : WDG_INTCLR 寄存器结构定义。地址偏移量:0x000C，初值:0x00000000，宽度:32
 寄存器说明: 中断清除寄存器。清除WatchDog中断，使WatchDog重新载入初值进行计数。本寄存器是只写寄存器，写进去任意值，都会引起WatchDog清中断，内部并不记忆写入的值，无复位值。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wdg_intclr : 32; /* bit[0-31]: 对该寄存器写入任意值可清除WatchDog的中断，并使WatchDog从寄存器WDG_LOAD中重新载入初值重新计数。 */
    } reg;
} SOC_ISP_WatchDog_WDG_INTCLR_UNION;
#endif
#define SOC_ISP_WatchDog_WDG_INTCLR_wdg_intclr_START  (0)
#define SOC_ISP_WatchDog_WDG_INTCLR_wdg_intclr_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_WatchDog_WDG_RIS_UNION
 结构说明  : WDG_RIS 寄存器结构定义。地址偏移量:0x0010，初值:0x00000000，宽度:32
 寄存器说明: 原始中断寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wdogris  : 1;  /* bit[0]   : WatchDog原始中断状态，当计数器的计数值递减到0时，该位置1。
                                                   0：未产生中断；
                                                   1：已产生中断。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_ISP_WatchDog_WDG_RIS_UNION;
#endif
#define SOC_ISP_WatchDog_WDG_RIS_wdogris_START   (0)
#define SOC_ISP_WatchDog_WDG_RIS_wdogris_END     (0)


/*****************************************************************************
 结构名    : SOC_ISP_WatchDog_WDG_MIS_UNION
 结构说明  : WDG_MIS 寄存器结构定义。地址偏移量:0x0014，初值:0x00000000，宽度:32
 寄存器说明: 屏蔽后中断寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wdogmis  : 1;  /* bit[0]   : WatchDog的屏蔽后中断状态。
                                                   0：未产生中断或者中断被屏蔽；
                                                   1：已产生中断。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_ISP_WatchDog_WDG_MIS_UNION;
#endif
#define SOC_ISP_WatchDog_WDG_MIS_wdogmis_START   (0)
#define SOC_ISP_WatchDog_WDG_MIS_wdogmis_END     (0)


/*****************************************************************************
 结构名    : SOC_ISP_WatchDog_WDG_LOCK_UNION
 结构说明  : WDG_LOCK 寄存器结构定义。地址偏移量:0x0C00，初值:0x00000000，宽度:32
 寄存器说明: LOCK寄存器，控制WatchDog寄存器的读写权限。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wdg_lock : 32; /* bit[0-31]: 向该寄存器写入0x1ACC_E551，可打开所有寄存器的写权限；
                                                   向该寄存器写入其他值则关闭写权限。
                                                   读该寄存器返回加锁的状态而不是写入该寄存器的值：
                                                   0x0000_0000：允许写访问（未加锁）；
                                                   0x0000_0001：禁止写访问（已加锁）。 */
    } reg;
} SOC_ISP_WatchDog_WDG_LOCK_UNION;
#endif
#define SOC_ISP_WatchDog_WDG_LOCK_wdg_lock_START  (0)
#define SOC_ISP_WatchDog_WDG_LOCK_wdg_lock_END    (31)






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

#endif /* end of soc_isp_watchdog_interface.h */
