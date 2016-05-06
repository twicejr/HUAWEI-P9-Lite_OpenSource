/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_rtctimerwdtv100_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:22:37
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_RTCTIMERWDTV100.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_RTCTIMERWDTV100_INTERFACE_H__
#define __SOC_RTCTIMERWDTV100_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/3) register_RTC
 ****************************************************************************/
/* 寄存器说明：计数器当前值寄存器
   位域定义UNION结构:  SOC_RTCTIMERWDTV100_RTC_DR_UNION */
#define SOC_RTCTIMERWDTV100_RTC_DR_ADDR(base)         ((base) + (0x0000))

/* 寄存器说明：RTC比较寄存器
   位域定义UNION结构:  SOC_RTCTIMERWDTV100_RTC_MR_UNION */
#define SOC_RTCTIMERWDTV100_RTC_MR_ADDR(base)         ((base) + (0x0004))

/* 寄存器说明：设置RTC计数初始值
   位域定义UNION结构:  SOC_RTCTIMERWDTV100_RTC_LR_UNION */
#define SOC_RTCTIMERWDTV100_RTC_LR_ADDR(base)         ((base) + (0x0008))

/* 寄存器说明：控制寄存器
   位域定义UNION结构:  SOC_RTCTIMERWDTV100_RTC_CR_UNION */
#define SOC_RTCTIMERWDTV100_RTC_CR_ADDR(base)         ((base) + (0x000C))

/* 寄存器说明：屏蔽控制寄存器
   位域定义UNION结构:  SOC_RTCTIMERWDTV100_RTC_IMSC_UNION */
#define SOC_RTCTIMERWDTV100_RTC_IMSC_ADDR(base)       ((base) + (0x0010))

/* 寄存器说明：原始中断状态寄存器
   位域定义UNION结构:  SOC_RTCTIMERWDTV100_RTCRIS_UNION */
#define SOC_RTCTIMERWDTV100_RTCRIS_ADDR(base)         ((base) + (0x0014))

/* 寄存器说明：中断屏蔽后状态寄存器
   位域定义UNION结构:  SOC_RTCTIMERWDTV100_RTCMIS_UNION */
#define SOC_RTCTIMERWDTV100_RTCMIS_ADDR(base)         ((base) + (0x0018))

/* 寄存器说明：中断清除寄存器
   位域定义UNION结构:  SOC_RTCTIMERWDTV100_RTCICR_UNION */
#define SOC_RTCTIMERWDTV100_RTCICR_ADDR(base)         ((base) + (0x001C))



/****************************************************************************
                     (2/3) register_TIMER
 ****************************************************************************/
/* 寄存器说明：计数初值寄存器
   位域定义UNION结构:  SOC_RTCTIMERWDTV100_TIMER0_LOAD_UNION */
#define SOC_RTCTIMERWDTV100_TIMER0_LOAD_ADDR(base)    ((base) + (0x0000))

/* 寄存器说明：计数初值寄存器
   位域定义UNION结构:  SOC_RTCTIMERWDTV100_TIMER1_LOAD_UNION */
#define SOC_RTCTIMERWDTV100_TIMER1_LOAD_ADDR(base)    ((base) + (0x0020))

/* 寄存器说明：当前计数值寄存器
   位域定义UNION结构:  SOC_RTCTIMERWDTV100_TIMER0_VALUE_UNION */
#define SOC_RTCTIMERWDTV100_TIMER0_VALUE_ADDR(base)   ((base) + (0x0004))

/* 寄存器说明：当前计数值寄存器
   位域定义UNION结构:  SOC_RTCTIMERWDTV100_TIMER1_VALUE_UNION */
#define SOC_RTCTIMERWDTV100_TIMER1_VALUE_ADDR(base)   ((base) + (0x0024))

/* 寄存器说明：控制寄存器
   位域定义UNION结构:  SOC_RTCTIMERWDTV100_TIMER0_CONTROL_UNION */
#define SOC_RTCTIMERWDTV100_TIMER0_CONTROL_ADDR(base) ((base) + (0x0008))

/* 寄存器说明：控制寄存器
   位域定义UNION结构:  SOC_RTCTIMERWDTV100_TIMER1_CONTROL_UNION */
#define SOC_RTCTIMERWDTV100_TIMER1_CONTROL_ADDR(base) ((base) + (0x0028))

/* 寄存器说明：中断清除寄存器
   位域定义UNION结构:  SOC_RTCTIMERWDTV100_TIMER0_INTCLR_UNION */
#define SOC_RTCTIMERWDTV100_TIMER0_INTCLR_ADDR(base)  ((base) + (0x000C))

/* 寄存器说明：中断清除寄存器
   位域定义UNION结构:  SOC_RTCTIMERWDTV100_TIMER1_INTCLR_UNION */
#define SOC_RTCTIMERWDTV100_TIMER1_INTCLR_ADDR(base)  ((base) + (0x002C))

/* 寄存器说明：原始中断状态寄存器
   位域定义UNION结构:  SOC_RTCTIMERWDTV100_TIMER0_RIS_UNION */
#define SOC_RTCTIMERWDTV100_TIMER0_RIS_ADDR(base)     ((base) + (0x0010))

/* 寄存器说明：原始中断状态寄存器
   位域定义UNION结构:  SOC_RTCTIMERWDTV100_TIMER1_RIS_UNION */
#define SOC_RTCTIMERWDTV100_TIMER1_RIS_ADDR(base)     ((base) + (0x0030))

/* 寄存器说明：屏蔽后中断状态寄存器
   位域定义UNION结构:  SOC_RTCTIMERWDTV100_TIMER0_MIS_UNION */
#define SOC_RTCTIMERWDTV100_TIMER0_MIS_ADDR(base)     ((base) + (0x0014))

/* 寄存器说明：屏蔽后中断状态寄存器
   位域定义UNION结构:  SOC_RTCTIMERWDTV100_TIMER1_MIS_UNION */
#define SOC_RTCTIMERWDTV100_TIMER1_MIS_ADDR(base)     ((base) + (0x0034))

/* 寄存器说明：Periodic模式计数初值寄存器
   位域定义UNION结构:  SOC_RTCTIMERWDTV100_TIMER0_BGLOAD_UNION */
#define SOC_RTCTIMERWDTV100_TIMER0_BGLOAD_ADDR(base)  ((base) + (0x0018))

/* 寄存器说明：Periodic模式计数初值寄存器
   位域定义UNION结构:  SOC_RTCTIMERWDTV100_TIMER1_BGLOAD_UNION */
#define SOC_RTCTIMERWDTV100_TIMER1_BGLOAD_ADDR(base)  ((base) + (0x0038))



/****************************************************************************
                     (3/3) register_WD
 ****************************************************************************/
/* 寄存器说明：计数器的计数初值寄存器
   位域定义UNION结构:  SOC_RTCTIMERWDTV100_WDLOAD_UNION */
#define SOC_RTCTIMERWDTV100_WDLOAD_ADDR(base)         ((base) + (0x0000))

/* 寄存器说明：计数器当前值寄存器
   位域定义UNION结构:  SOC_RTCTIMERWDTV100_WDVALUE_UNION */
#define SOC_RTCTIMERWDTV100_WDVALUE_ADDR(base)        ((base) + (0x0004))

/* 寄存器说明：控制寄存器
   位域定义UNION结构:  SOC_RTCTIMERWDTV100_WDCONTROL_UNION */
#define SOC_RTCTIMERWDTV100_WDCONTROL_ADDR(base)      ((base) + (0x0008))

/* 寄存器说明：中断控制寄存器
   位域定义UNION结构:  SOC_RTCTIMERWDTV100_WDINTCLR_UNION */
#define SOC_RTCTIMERWDTV100_WDINTCLR_ADDR(base)       ((base) + (0x000C))

/* 寄存器说明：原始中断状态寄存器
   位域定义UNION结构:  SOC_RTCTIMERWDTV100_WDRIS_UNION */
#define SOC_RTCTIMERWDTV100_WDRIS_ADDR(base)          ((base) + (0x0010))

/* 寄存器说明：屏蔽后中断状态寄存器
   位域定义UNION结构:  SOC_RTCTIMERWDTV100_WDMIS_UNION */
#define SOC_RTCTIMERWDTV100_WDMIS_ADDR(base)          ((base) + (0x0014))

/* 寄存器说明：写权限控制寄存器
   位域定义UNION结构:  SOC_RTCTIMERWDTV100_WDLOCK_UNION */
#define SOC_RTCTIMERWDTV100_WDLOCK_ADDR(base)         ((base) + (0x0C00))





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
                     (1/3) register_RTC
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_RTCTIMERWDTV100_RTC_DR_UNION
 结构说明  : RTC_DR 寄存器结构定义。地址偏移量:0x0000，初值:0x00000000，宽度:32
 寄存器说明: 计数器当前值寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rtcdr : 32; /* bit[0-31]: 读取RTC内部计数器的当前值 */
    } reg;
} SOC_RTCTIMERWDTV100_RTC_DR_UNION;
#endif
#define SOC_RTCTIMERWDTV100_RTC_DR_rtcdr_START  (0)
#define SOC_RTCTIMERWDTV100_RTC_DR_rtcdr_END    (31)


/*****************************************************************************
 结构名    : SOC_RTCTIMERWDTV100_RTC_MR_UNION
 结构说明  : RTC_MR 寄存器结构定义。地址偏移量:0x0004，初值:0x00000000，宽度:32
 寄存器说明: RTC比较寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rtcmr : 32; /* bit[0-31]: 设置RTC比较值 */
    } reg;
} SOC_RTCTIMERWDTV100_RTC_MR_UNION;
#endif
#define SOC_RTCTIMERWDTV100_RTC_MR_rtcmr_START  (0)
#define SOC_RTCTIMERWDTV100_RTC_MR_rtcmr_END    (31)


/*****************************************************************************
 结构名    : SOC_RTCTIMERWDTV100_RTC_LR_UNION
 结构说明  : RTC_LR 寄存器结构定义。地址偏移量:0x0008，初值:0x00000000，宽度:32
 寄存器说明: 设置RTC计数初始值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rtclr : 32; /* bit[0-31]: 设置RTC计数初始值 */
    } reg;
} SOC_RTCTIMERWDTV100_RTC_LR_UNION;
#endif
#define SOC_RTCTIMERWDTV100_RTC_LR_rtclr_START  (0)
#define SOC_RTCTIMERWDTV100_RTC_LR_rtclr_END    (31)


/*****************************************************************************
 结构名    : SOC_RTCTIMERWDTV100_RTC_CR_UNION
 结构说明  : RTC_CR 寄存器结构定义。地址偏移量:0x000C，初值:0x00000000，宽度:32
 寄存器说明: 控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rtccr    : 1;  /* bit[0]   : RTC使能：
                                                   0：禁止；
                                                   1：使能。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_RTCTIMERWDTV100_RTC_CR_UNION;
#endif
#define SOC_RTCTIMERWDTV100_RTC_CR_rtccr_START     (0)
#define SOC_RTCTIMERWDTV100_RTC_CR_rtccr_END       (0)


/*****************************************************************************
 结构名    : SOC_RTCTIMERWDTV100_RTC_IMSC_UNION
 结构说明  : RTC_IMSC 寄存器结构定义。地址偏移量:0x0010，初值:0x00000000，宽度:32
 寄存器说明: 屏蔽控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rtcimsc  : 1;  /* bit[0]   : 是否允许中断：
                                                   0：禁止中断；
                                                   1：允许中断。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_RTCTIMERWDTV100_RTC_IMSC_UNION;
#endif
#define SOC_RTCTIMERWDTV100_RTC_IMSC_rtcimsc_START   (0)
#define SOC_RTCTIMERWDTV100_RTC_IMSC_rtcimsc_END     (0)


/*****************************************************************************
 结构名    : SOC_RTCTIMERWDTV100_RTCRIS_UNION
 结构说明  : RTCRIS 寄存器结构定义。地址偏移量:0x0014，初值:0x00000000，宽度:32
 寄存器说明: 原始中断状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rtcris   : 1;  /* bit[0]   : 原始中断状态：
                                                   0：未产生中断；
                                                   1：已产生中断。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_RTCTIMERWDTV100_RTCRIS_UNION;
#endif
#define SOC_RTCTIMERWDTV100_RTCRIS_rtcris_START    (0)
#define SOC_RTCTIMERWDTV100_RTCRIS_rtcris_END      (0)


/*****************************************************************************
 结构名    : SOC_RTCTIMERWDTV100_RTCMIS_UNION
 结构说明  : RTCMIS 寄存器结构定义。地址偏移量:0x0018，初值:0x00000000，宽度:32
 寄存器说明: 中断屏蔽后状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rtcmis   : 1;  /* bit[0]   : 屏蔽后的中断状态：
                                                   0：未产生中断或者中断被屏蔽；
                                                   1：已产生中断。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_RTCTIMERWDTV100_RTCMIS_UNION;
#endif
#define SOC_RTCTIMERWDTV100_RTCMIS_rtcmis_START    (0)
#define SOC_RTCTIMERWDTV100_RTCMIS_rtcmis_END      (0)


/*****************************************************************************
 结构名    : SOC_RTCTIMERWDTV100_RTCICR_UNION
 结构说明  : RTCICR 寄存器结构定义。地址偏移量:0x001C，初值:0x00000000，宽度:32
 寄存器说明: 中断清除寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rtcicr   : 1;  /* bit[0]   : 清除RTC中断：
                                                   0：无影响；
                                                   1：清除中断。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_RTCTIMERWDTV100_RTCICR_UNION;
#endif
#define SOC_RTCTIMERWDTV100_RTCICR_rtcicr_START    (0)
#define SOC_RTCTIMERWDTV100_RTCICR_rtcicr_END      (0)




/****************************************************************************
                     (2/3) register_TIMER
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_RTCTIMERWDTV100_TIMER0_LOAD_UNION
 结构说明  : TIMER0_LOAD 寄存器结构定义。地址偏移量:0x0000，初值:0x00000000，宽度:32
 寄存器说明: 计数初值寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  timerxload : 32; /* bit[0-31]: 保存着定时器的计数初值 */
    } reg;
} SOC_RTCTIMERWDTV100_TIMER0_LOAD_UNION;
#endif
#define SOC_RTCTIMERWDTV100_TIMER0_LOAD_timerxload_START  (0)
#define SOC_RTCTIMERWDTV100_TIMER0_LOAD_timerxload_END    (31)


/*****************************************************************************
 结构名    : SOC_RTCTIMERWDTV100_TIMER1_LOAD_UNION
 结构说明  : TIMER1_LOAD 寄存器结构定义。地址偏移量:0x0020，初值:0x00000000，宽度:32
 寄存器说明: 计数初值寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  timerxload : 32; /* bit[0-31]: 保存着定时器的计数初值 */
    } reg;
} SOC_RTCTIMERWDTV100_TIMER1_LOAD_UNION;
#endif
#define SOC_RTCTIMERWDTV100_TIMER1_LOAD_timerxload_START  (0)
#define SOC_RTCTIMERWDTV100_TIMER1_LOAD_timerxload_END    (31)


/*****************************************************************************
 结构名    : SOC_RTCTIMERWDTV100_TIMER0_VALUE_UNION
 结构说明  : TIMER0_VALUE 寄存器结构定义。地址偏移量:0x0004，初值:0xffffffff，宽度:32
 寄存器说明: 当前计数值寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  timerxvalue : 32; /* bit[0-31]: 显示正在递减的定时计数器的当前值 */
    } reg;
} SOC_RTCTIMERWDTV100_TIMER0_VALUE_UNION;
#endif
#define SOC_RTCTIMERWDTV100_TIMER0_VALUE_timerxvalue_START  (0)
#define SOC_RTCTIMERWDTV100_TIMER0_VALUE_timerxvalue_END    (31)


/*****************************************************************************
 结构名    : SOC_RTCTIMERWDTV100_TIMER1_VALUE_UNION
 结构说明  : TIMER1_VALUE 寄存器结构定义。地址偏移量:0x0024，初值:0xffffffff，宽度:32
 寄存器说明: 当前计数值寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  timerxvalue : 32; /* bit[0-31]: 显示正在递减的定时计数器的当前值 */
    } reg;
} SOC_RTCTIMERWDTV100_TIMER1_VALUE_UNION;
#endif
#define SOC_RTCTIMERWDTV100_TIMER1_VALUE_timerxvalue_START  (0)
#define SOC_RTCTIMERWDTV100_TIMER1_VALUE_timerxvalue_END    (31)


/*****************************************************************************
 结构名    : SOC_RTCTIMERWDTV100_TIMER0_CONTROL_UNION
 结构说明  : TIMER0_CONTROL 寄存器结构定义。地址偏移量:0x0008，初值:0x00000020，宽度:32
 寄存器说明: 控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  oneshot    : 1;  /* bit[0]   : 计数模式：
                                                     0：回卷计数（缺省值）；
                                                     1：一次性计数。 */
        unsigned int  timersize  : 1;  /* bit[1]   : 计数器位数：
                                                     0：16bit（缺省值）；
                                                     1：32bit。 */
        unsigned int  timerpre   : 2;  /* bit[2-3] : 预分频因子：
                                                     00：不经过预分频，时钟频率除以1（缺省值）；
                                                     01：4级预分频，将定时器时钟频率除以16：
                                                     10：8级预分频，将定时器时钟频率除以256；
                                                     11：未定义，若设为该值，相当于预分频因子为8级预分频 */
        unsigned int  reserved_0 : 1;  /* bit[4]   : 保留。写无效，读时返回0。 */
        unsigned int  internable : 1;  /* bit[5]   : 中断使能位（写入时）：
                                                     0：禁止中断；
                                                     1：使能中断(缺省值)。 */
        unsigned int  timermode  : 1;  /* bit[6]   : 计数模式：
                                                     0：定时器处于Free-running模式（缺省值）；
                                                     1：定时器处于Periodic模式。 */
        unsigned int  timeren    : 1;  /* bit[7]   : 定时器使能位：
                                                     0：禁止（缺省值）；
                                                     1：使能。定时器使能位： */
        unsigned int  reserved_1 : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_RTCTIMERWDTV100_TIMER0_CONTROL_UNION;
#endif
#define SOC_RTCTIMERWDTV100_TIMER0_CONTROL_oneshot_START     (0)
#define SOC_RTCTIMERWDTV100_TIMER0_CONTROL_oneshot_END       (0)
#define SOC_RTCTIMERWDTV100_TIMER0_CONTROL_timersize_START   (1)
#define SOC_RTCTIMERWDTV100_TIMER0_CONTROL_timersize_END     (1)
#define SOC_RTCTIMERWDTV100_TIMER0_CONTROL_timerpre_START    (2)
#define SOC_RTCTIMERWDTV100_TIMER0_CONTROL_timerpre_END      (3)
#define SOC_RTCTIMERWDTV100_TIMER0_CONTROL_internable_START  (5)
#define SOC_RTCTIMERWDTV100_TIMER0_CONTROL_internable_END    (5)
#define SOC_RTCTIMERWDTV100_TIMER0_CONTROL_timermode_START   (6)
#define SOC_RTCTIMERWDTV100_TIMER0_CONTROL_timermode_END     (6)
#define SOC_RTCTIMERWDTV100_TIMER0_CONTROL_timeren_START     (7)
#define SOC_RTCTIMERWDTV100_TIMER0_CONTROL_timeren_END       (7)


/*****************************************************************************
 结构名    : SOC_RTCTIMERWDTV100_TIMER1_CONTROL_UNION
 结构说明  : TIMER1_CONTROL 寄存器结构定义。地址偏移量:0x0028，初值:0x00000020，宽度:32
 寄存器说明: 控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  oneshot    : 1;  /* bit[0]   : 计数模式：
                                                     0：回卷计数（缺省值）；
                                                     1：一次性计数。 */
        unsigned int  timersize  : 1;  /* bit[1]   : 计数器位数：
                                                     0：16bit（缺省值）；
                                                     1：32bit。 */
        unsigned int  timerpre   : 2;  /* bit[2-3] : 预分频因子：
                                                     00：不经过预分频，时钟频率除以1（缺省值）；
                                                     01：4级预分频，将定时器时钟频率除以16：
                                                     10：8级预分频，将定时器时钟频率除以256；
                                                     11：未定义，若设为该值，相当于预分频因子为8级预分频 */
        unsigned int  reserved_0 : 1;  /* bit[4]   : 保留。写无效，读时返回0。 */
        unsigned int  internable : 1;  /* bit[5]   : 中断使能位（写入时）：
                                                     0：禁止中断；
                                                     1：使能中断(缺省值)。 */
        unsigned int  timermode  : 1;  /* bit[6]   : 计数模式：
                                                     0：定时器处于Free-running模式（缺省值）；
                                                     1：定时器处于Periodic模式。 */
        unsigned int  timeren    : 1;  /* bit[7]   : 定时器使能位：
                                                     0：禁止（缺省值）；
                                                     1：使能。定时器使能位： */
        unsigned int  reserved_1 : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_RTCTIMERWDTV100_TIMER1_CONTROL_UNION;
#endif
#define SOC_RTCTIMERWDTV100_TIMER1_CONTROL_oneshot_START     (0)
#define SOC_RTCTIMERWDTV100_TIMER1_CONTROL_oneshot_END       (0)
#define SOC_RTCTIMERWDTV100_TIMER1_CONTROL_timersize_START   (1)
#define SOC_RTCTIMERWDTV100_TIMER1_CONTROL_timersize_END     (1)
#define SOC_RTCTIMERWDTV100_TIMER1_CONTROL_timerpre_START    (2)
#define SOC_RTCTIMERWDTV100_TIMER1_CONTROL_timerpre_END      (3)
#define SOC_RTCTIMERWDTV100_TIMER1_CONTROL_internable_START  (5)
#define SOC_RTCTIMERWDTV100_TIMER1_CONTROL_internable_END    (5)
#define SOC_RTCTIMERWDTV100_TIMER1_CONTROL_timermode_START   (6)
#define SOC_RTCTIMERWDTV100_TIMER1_CONTROL_timermode_END     (6)
#define SOC_RTCTIMERWDTV100_TIMER1_CONTROL_timeren_START     (7)
#define SOC_RTCTIMERWDTV100_TIMER1_CONTROL_timeren_END       (7)


/*****************************************************************************
 结构名    : SOC_RTCTIMERWDTV100_TIMER0_INTCLR_UNION
 结构说明  : TIMER0_INTCLR 寄存器结构定义。地址偏移量:0x000C，初值:0x00000000，宽度:32
 寄存器说明: 中断清除寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  timerxintclr : 32; /* bit[0-31]: 任何写操作都会清除Timer定时器的中断 */
    } reg;
} SOC_RTCTIMERWDTV100_TIMER0_INTCLR_UNION;
#endif
#define SOC_RTCTIMERWDTV100_TIMER0_INTCLR_timerxintclr_START  (0)
#define SOC_RTCTIMERWDTV100_TIMER0_INTCLR_timerxintclr_END    (31)


/*****************************************************************************
 结构名    : SOC_RTCTIMERWDTV100_TIMER1_INTCLR_UNION
 结构说明  : TIMER1_INTCLR 寄存器结构定义。地址偏移量:0x002C，初值:0x00000000，宽度:32
 寄存器说明: 中断清除寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  timerxintclr : 32; /* bit[0-31]: 任何写操作都会清除Timer定时器的中断 */
    } reg;
} SOC_RTCTIMERWDTV100_TIMER1_INTCLR_UNION;
#endif
#define SOC_RTCTIMERWDTV100_TIMER1_INTCLR_timerxintclr_START  (0)
#define SOC_RTCTIMERWDTV100_TIMER1_INTCLR_timerxintclr_END    (31)


/*****************************************************************************
 结构名    : SOC_RTCTIMERWDTV100_TIMER0_RIS_UNION
 结构说明  : TIMER0_RIS 寄存器结构定义。地址偏移量:0x0010，初值:0x00000000，宽度:32
 寄存器说明: 原始中断状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  timerxris : 1;  /* bit[0]   : 读时返回计数器的原始中断状态：
                                                    0：无原始中断；
                                                    1：有原始中断。 */
        unsigned int  reserved  : 31; /* bit[1-31]: 保留。写无效，读时返回0。 */
    } reg;
} SOC_RTCTIMERWDTV100_TIMER0_RIS_UNION;
#endif
#define SOC_RTCTIMERWDTV100_TIMER0_RIS_timerxris_START  (0)
#define SOC_RTCTIMERWDTV100_TIMER0_RIS_timerxris_END    (0)


/*****************************************************************************
 结构名    : SOC_RTCTIMERWDTV100_TIMER1_RIS_UNION
 结构说明  : TIMER1_RIS 寄存器结构定义。地址偏移量:0x0030，初值:0x00000000，宽度:32
 寄存器说明: 原始中断状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  timerxris : 1;  /* bit[0]   : 读时返回计数器的原始中断状态：
                                                    0：无原始中断；
                                                    1：有原始中断。 */
        unsigned int  reserved  : 31; /* bit[1-31]: 保留。写无效，读时返回0。 */
    } reg;
} SOC_RTCTIMERWDTV100_TIMER1_RIS_UNION;
#endif
#define SOC_RTCTIMERWDTV100_TIMER1_RIS_timerxris_START  (0)
#define SOC_RTCTIMERWDTV100_TIMER1_RIS_timerxris_END    (0)


/*****************************************************************************
 结构名    : SOC_RTCTIMERWDTV100_TIMER0_MIS_UNION
 结构说明  : TIMER0_MIS 寄存器结构定义。地址偏移量:0x0014，初值:0x00000000，宽度:32
 寄存器说明: 屏蔽后中断状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  timerxmis : 1;  /* bit[0]   : 读时返回屏蔽后的计数器中断状态：
                                                    0：无中断；
                                                    1：有中断。 */
        unsigned int  reserved  : 31; /* bit[1-31]: 保留。写无效，读时返回0。 */
    } reg;
} SOC_RTCTIMERWDTV100_TIMER0_MIS_UNION;
#endif
#define SOC_RTCTIMERWDTV100_TIMER0_MIS_timerxmis_START  (0)
#define SOC_RTCTIMERWDTV100_TIMER0_MIS_timerxmis_END    (0)


/*****************************************************************************
 结构名    : SOC_RTCTIMERWDTV100_TIMER1_MIS_UNION
 结构说明  : TIMER1_MIS 寄存器结构定义。地址偏移量:0x0034，初值:0x00000000，宽度:32
 寄存器说明: 屏蔽后中断状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  timerxmis : 1;  /* bit[0]   : 读时返回屏蔽后的计数器中断状态：
                                                    0：无中断；
                                                    1：有中断。 */
        unsigned int  reserved  : 31; /* bit[1-31]: 保留。写无效，读时返回0。 */
    } reg;
} SOC_RTCTIMERWDTV100_TIMER1_MIS_UNION;
#endif
#define SOC_RTCTIMERWDTV100_TIMER1_MIS_timerxmis_START  (0)
#define SOC_RTCTIMERWDTV100_TIMER1_MIS_timerxmis_END    (0)


/*****************************************************************************
 结构名    : SOC_RTCTIMERWDTV100_TIMER0_BGLOAD_UNION
 结构说明  : TIMER0_BGLOAD 寄存器结构定义。地址偏移量:0x0018，初值:0x00000000，宽度:32
 寄存器说明: Periodic模式计数初值寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  timerxbgload : 32; /* bit[0-31]: 存储定时器的计数初值 */
    } reg;
} SOC_RTCTIMERWDTV100_TIMER0_BGLOAD_UNION;
#endif
#define SOC_RTCTIMERWDTV100_TIMER0_BGLOAD_timerxbgload_START  (0)
#define SOC_RTCTIMERWDTV100_TIMER0_BGLOAD_timerxbgload_END    (31)


/*****************************************************************************
 结构名    : SOC_RTCTIMERWDTV100_TIMER1_BGLOAD_UNION
 结构说明  : TIMER1_BGLOAD 寄存器结构定义。地址偏移量:0x0038，初值:0x00000000，宽度:32
 寄存器说明: Periodic模式计数初值寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  timerxbgload : 32; /* bit[0-31]: 存储定时器的计数初值 */
    } reg;
} SOC_RTCTIMERWDTV100_TIMER1_BGLOAD_UNION;
#endif
#define SOC_RTCTIMERWDTV100_TIMER1_BGLOAD_timerxbgload_START  (0)
#define SOC_RTCTIMERWDTV100_TIMER1_BGLOAD_timerxbgload_END    (31)




/****************************************************************************
                     (3/3) register_WD
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_RTCTIMERWDTV100_WDLOAD_UNION
 结构说明  : WDLOAD 寄存器结构定义。地址偏移量:0x0000，初值:0xFFFFFFFF，宽度:32
 寄存器说明: 计数器的计数初值寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wdogload : 32; /* bit[0-31]: watchdog递减计数器的初始值。一旦该计数器的值被更新，则计数器立即从新值开始递减计数 */
    } reg;
} SOC_RTCTIMERWDTV100_WDLOAD_UNION;
#endif
#define SOC_RTCTIMERWDTV100_WDLOAD_wdogload_START  (0)
#define SOC_RTCTIMERWDTV100_WDLOAD_wdogload_END    (31)


/*****************************************************************************
 结构名    : SOC_RTCTIMERWDTV100_WDVALUE_UNION
 结构说明  : WDVALUE 寄存器结构定义。地址偏移量:0x0004，初值:0xFFFFFFFF，宽度:32
 寄存器说明: 计数器当前值寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wdogvalue : 32; /* bit[0-31]: 正在递减计数的计数器当前值 */
    } reg;
} SOC_RTCTIMERWDTV100_WDVALUE_UNION;
#endif
#define SOC_RTCTIMERWDTV100_WDVALUE_wdogvalue_START  (0)
#define SOC_RTCTIMERWDTV100_WDVALUE_wdogvalue_END    (31)


/*****************************************************************************
 结构名    : SOC_RTCTIMERWDTV100_WDCONTROL_UNION
 结构说明  : WDCONTROL 寄存器结构定义。地址偏移量:0x0008，初值:0x00000000，宽度:32
 寄存器说明: 控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  inten    : 1;  /* bit[0]   : 使能中断信号的输出。
                                                   0：计数器停止计数，计数值保持当前值不变；
                                                   1：既启动计数器又使能中断。
                                                   若中断先前被禁止，则当中断再次被使能时，计数器从寄存器WdogLoad中载入初值并重新开始计数。 */
        unsigned int  resen    : 1;  /* bit[1]   : 使能Watchdog模块输出复位信号。
                                                   0：禁止；
                                                   1：使能。 */
        unsigned int  reserved : 30; /* bit[2-31]: 保留。写无效，读时返回0。 */
    } reg;
} SOC_RTCTIMERWDTV100_WDCONTROL_UNION;
#endif
#define SOC_RTCTIMERWDTV100_WDCONTROL_inten_START     (0)
#define SOC_RTCTIMERWDTV100_WDCONTROL_inten_END       (0)
#define SOC_RTCTIMERWDTV100_WDCONTROL_resen_START     (1)
#define SOC_RTCTIMERWDTV100_WDCONTROL_resen_END       (1)


/*****************************************************************************
 结构名    : SOC_RTCTIMERWDTV100_WDINTCLR_UNION
 结构说明  : WDINTCLR 寄存器结构定义。地址偏移量:0x000C，初值:0x00000000，宽度:32
 寄存器说明: 中断控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wdogxintclr : 32; /* bit[0-31]: 对该寄存器写入任意值可清除中断，并使Watchdog从寄存器WatchLoad中重新载入初值。 */
    } reg;
} SOC_RTCTIMERWDTV100_WDINTCLR_UNION;
#endif
#define SOC_RTCTIMERWDTV100_WDINTCLR_wdogxintclr_START  (0)
#define SOC_RTCTIMERWDTV100_WDINTCLR_wdogxintclr_END    (31)


/*****************************************************************************
 结构名    : SOC_RTCTIMERWDTV100_WDRIS_UNION
 结构说明  : WDRIS 寄存器结构定义。地址偏移量:0x0010，初值:0x00000000，宽度:32
 寄存器说明: 原始中断状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wdogris  : 1;  /* bit[0]   : 原始中断装态，当计数器见到零时该位有效。
                                                   0：未产生中断；
                                                   1：已产生中断。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留。写无效，读时返回0。 */
    } reg;
} SOC_RTCTIMERWDTV100_WDRIS_UNION;
#endif
#define SOC_RTCTIMERWDTV100_WDRIS_wdogris_START   (0)
#define SOC_RTCTIMERWDTV100_WDRIS_wdogris_END     (0)


/*****************************************************************************
 结构名    : SOC_RTCTIMERWDTV100_WDMIS_UNION
 结构说明  : WDMIS 寄存器结构定义。地址偏移量:0x0014，初值:0x00000000，宽度:32
 寄存器说明: 屏蔽后中断状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wdogmis  : 1;  /* bit[0]   : 屏蔽后中断装态。
                                                   0：未产生中断或中断被屏蔽；
                                                   1：已产生中断。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留。写无效，读时返回0。 */
    } reg;
} SOC_RTCTIMERWDTV100_WDMIS_UNION;
#endif
#define SOC_RTCTIMERWDTV100_WDMIS_wdogmis_START   (0)
#define SOC_RTCTIMERWDTV100_WDMIS_wdogmis_END     (0)


/*****************************************************************************
 结构名    : SOC_RTCTIMERWDTV100_WDLOCK_UNION
 结构说明  : WDLOCK 寄存器结构定义。地址偏移量:0x0C00，初值:0x00000000，宽度:32
 寄存器说明: 写权限控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wdoglock : 32; /* bit[0-31]: 向该寄存器写入0x1ACC_E551可打开所有寄存器的写权限，写入其他值则关闭写权限。读该寄存器返回加锁的状态而不是写入该寄存器的值.0:允许写访问（未加锁）；1：禁止写访问（已加锁）。 */
    } reg;
} SOC_RTCTIMERWDTV100_WDLOCK_UNION;
#endif
#define SOC_RTCTIMERWDTV100_WDLOCK_wdoglock_START  (0)
#define SOC_RTCTIMERWDTV100_WDLOCK_wdoglock_END    (31)






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

#endif /* end of soc_rtctimerwdtv100_interface.h */
