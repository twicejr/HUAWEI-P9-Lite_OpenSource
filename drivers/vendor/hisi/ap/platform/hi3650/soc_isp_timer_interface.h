/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_isp_timer_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:22:09
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_ISP_TIMER.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_ISP_TIMER_INTERFACE_H__
#define __SOC_ISP_TIMER_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) TIMER
 ****************************************************************************/
/* 寄存器说明：计数初值寄存器
   位域定义UNION结构:  SOC_ISP_TIMER_TIMER0_LOAD_UNION */
#define SOC_ISP_TIMER_TIMER0_LOAD_ADDR(base)          ((base) + (0x0000))

/* 寄存器说明：计数初值寄存器
   位域定义UNION结构:  SOC_ISP_TIMER_TIMER1_LOAD_UNION */
#define SOC_ISP_TIMER_TIMER1_LOAD_ADDR(base)          ((base) + (0x0020))

/* 寄存器说明：当前计数值寄存器
   位域定义UNION结构:  SOC_ISP_TIMER_TIMER0_VALUE_UNION */
#define SOC_ISP_TIMER_TIMER0_VALUE_ADDR(base)         ((base) + (0x0004))

/* 寄存器说明：当前计数值寄存器
   位域定义UNION结构:  SOC_ISP_TIMER_TIMER1_VALUE_UNION */
#define SOC_ISP_TIMER_TIMER1_VALUE_ADDR(base)         ((base) + (0x0024))

/* 寄存器说明：控制寄存器
   位域定义UNION结构:  SOC_ISP_TIMER_TIMER0_CONTROL_UNION */
#define SOC_ISP_TIMER_TIMER0_CONTROL_ADDR(base)       ((base) + (0x0008))

/* 寄存器说明：控制寄存器
   位域定义UNION结构:  SOC_ISP_TIMER_TIMER1_CONTROL_UNION */
#define SOC_ISP_TIMER_TIMER1_CONTROL_ADDR(base)       ((base) + (0x0028))

/* 寄存器说明：中断清除寄存器
   位域定义UNION结构:  SOC_ISP_TIMER_TIMER0_INTCLR_UNION */
#define SOC_ISP_TIMER_TIMER0_INTCLR_ADDR(base)        ((base) + (0x000C))

/* 寄存器说明：中断清除寄存器
   位域定义UNION结构:  SOC_ISP_TIMER_TIMER1_INTCLR_UNION */
#define SOC_ISP_TIMER_TIMER1_INTCLR_ADDR(base)        ((base) + (0x002C))

/* 寄存器说明：原始中断状态寄存器
   位域定义UNION结构:  SOC_ISP_TIMER_TIMER0_RIS_UNION */
#define SOC_ISP_TIMER_TIMER0_RIS_ADDR(base)           ((base) + (0x0010))

/* 寄存器说明：原始中断状态寄存器
   位域定义UNION结构:  SOC_ISP_TIMER_TIMER1_RIS_UNION */
#define SOC_ISP_TIMER_TIMER1_RIS_ADDR(base)           ((base) + (0x0030))

/* 寄存器说明：屏蔽后中断状态寄存器
   位域定义UNION结构:  SOC_ISP_TIMER_TIMER0_MIS_UNION */
#define SOC_ISP_TIMER_TIMER0_MIS_ADDR(base)           ((base) + (0x0014))

/* 寄存器说明：屏蔽后中断状态寄存器
   位域定义UNION结构:  SOC_ISP_TIMER_TIMER1_MIS_UNION */
#define SOC_ISP_TIMER_TIMER1_MIS_ADDR(base)           ((base) + (0x0034))

/* 寄存器说明：Periodic模式计数初值寄存器
   位域定义UNION结构:  SOC_ISP_TIMER_TIMER0_BGLOAD_UNION */
#define SOC_ISP_TIMER_TIMER0_BGLOAD_ADDR(base)        ((base) + (0x0018))

/* 寄存器说明：Periodic模式计数初值寄存器
   位域定义UNION结构:  SOC_ISP_TIMER_TIMER1_BGLOAD_UNION */
#define SOC_ISP_TIMER_TIMER1_BGLOAD_ADDR(base)        ((base) + (0x0038))





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
                     (1/1) TIMER
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_ISP_TIMER_TIMER0_LOAD_UNION
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
} SOC_ISP_TIMER_TIMER0_LOAD_UNION;
#endif
#define SOC_ISP_TIMER_TIMER0_LOAD_timerxload_START  (0)
#define SOC_ISP_TIMER_TIMER0_LOAD_timerxload_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_TIMER_TIMER1_LOAD_UNION
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
} SOC_ISP_TIMER_TIMER1_LOAD_UNION;
#endif
#define SOC_ISP_TIMER_TIMER1_LOAD_timerxload_START  (0)
#define SOC_ISP_TIMER_TIMER1_LOAD_timerxload_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_TIMER_TIMER0_VALUE_UNION
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
} SOC_ISP_TIMER_TIMER0_VALUE_UNION;
#endif
#define SOC_ISP_TIMER_TIMER0_VALUE_timerxvalue_START  (0)
#define SOC_ISP_TIMER_TIMER0_VALUE_timerxvalue_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_TIMER_TIMER1_VALUE_UNION
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
} SOC_ISP_TIMER_TIMER1_VALUE_UNION;
#endif
#define SOC_ISP_TIMER_TIMER1_VALUE_timerxvalue_START  (0)
#define SOC_ISP_TIMER_TIMER1_VALUE_timerxvalue_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_TIMER_TIMER0_CONTROL_UNION
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
} SOC_ISP_TIMER_TIMER0_CONTROL_UNION;
#endif
#define SOC_ISP_TIMER_TIMER0_CONTROL_oneshot_START     (0)
#define SOC_ISP_TIMER_TIMER0_CONTROL_oneshot_END       (0)
#define SOC_ISP_TIMER_TIMER0_CONTROL_timersize_START   (1)
#define SOC_ISP_TIMER_TIMER0_CONTROL_timersize_END     (1)
#define SOC_ISP_TIMER_TIMER0_CONTROL_timerpre_START    (2)
#define SOC_ISP_TIMER_TIMER0_CONTROL_timerpre_END      (3)
#define SOC_ISP_TIMER_TIMER0_CONTROL_internable_START  (5)
#define SOC_ISP_TIMER_TIMER0_CONTROL_internable_END    (5)
#define SOC_ISP_TIMER_TIMER0_CONTROL_timermode_START   (6)
#define SOC_ISP_TIMER_TIMER0_CONTROL_timermode_END     (6)
#define SOC_ISP_TIMER_TIMER0_CONTROL_timeren_START     (7)
#define SOC_ISP_TIMER_TIMER0_CONTROL_timeren_END       (7)


/*****************************************************************************
 结构名    : SOC_ISP_TIMER_TIMER1_CONTROL_UNION
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
} SOC_ISP_TIMER_TIMER1_CONTROL_UNION;
#endif
#define SOC_ISP_TIMER_TIMER1_CONTROL_oneshot_START     (0)
#define SOC_ISP_TIMER_TIMER1_CONTROL_oneshot_END       (0)
#define SOC_ISP_TIMER_TIMER1_CONTROL_timersize_START   (1)
#define SOC_ISP_TIMER_TIMER1_CONTROL_timersize_END     (1)
#define SOC_ISP_TIMER_TIMER1_CONTROL_timerpre_START    (2)
#define SOC_ISP_TIMER_TIMER1_CONTROL_timerpre_END      (3)
#define SOC_ISP_TIMER_TIMER1_CONTROL_internable_START  (5)
#define SOC_ISP_TIMER_TIMER1_CONTROL_internable_END    (5)
#define SOC_ISP_TIMER_TIMER1_CONTROL_timermode_START   (6)
#define SOC_ISP_TIMER_TIMER1_CONTROL_timermode_END     (6)
#define SOC_ISP_TIMER_TIMER1_CONTROL_timeren_START     (7)
#define SOC_ISP_TIMER_TIMER1_CONTROL_timeren_END       (7)


/*****************************************************************************
 结构名    : SOC_ISP_TIMER_TIMER0_INTCLR_UNION
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
} SOC_ISP_TIMER_TIMER0_INTCLR_UNION;
#endif
#define SOC_ISP_TIMER_TIMER0_INTCLR_timerxintclr_START  (0)
#define SOC_ISP_TIMER_TIMER0_INTCLR_timerxintclr_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_TIMER_TIMER1_INTCLR_UNION
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
} SOC_ISP_TIMER_TIMER1_INTCLR_UNION;
#endif
#define SOC_ISP_TIMER_TIMER1_INTCLR_timerxintclr_START  (0)
#define SOC_ISP_TIMER_TIMER1_INTCLR_timerxintclr_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_TIMER_TIMER0_RIS_UNION
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
} SOC_ISP_TIMER_TIMER0_RIS_UNION;
#endif
#define SOC_ISP_TIMER_TIMER0_RIS_timerxris_START  (0)
#define SOC_ISP_TIMER_TIMER0_RIS_timerxris_END    (0)


/*****************************************************************************
 结构名    : SOC_ISP_TIMER_TIMER1_RIS_UNION
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
} SOC_ISP_TIMER_TIMER1_RIS_UNION;
#endif
#define SOC_ISP_TIMER_TIMER1_RIS_timerxris_START  (0)
#define SOC_ISP_TIMER_TIMER1_RIS_timerxris_END    (0)


/*****************************************************************************
 结构名    : SOC_ISP_TIMER_TIMER0_MIS_UNION
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
} SOC_ISP_TIMER_TIMER0_MIS_UNION;
#endif
#define SOC_ISP_TIMER_TIMER0_MIS_timerxmis_START  (0)
#define SOC_ISP_TIMER_TIMER0_MIS_timerxmis_END    (0)


/*****************************************************************************
 结构名    : SOC_ISP_TIMER_TIMER1_MIS_UNION
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
} SOC_ISP_TIMER_TIMER1_MIS_UNION;
#endif
#define SOC_ISP_TIMER_TIMER1_MIS_timerxmis_START  (0)
#define SOC_ISP_TIMER_TIMER1_MIS_timerxmis_END    (0)


/*****************************************************************************
 结构名    : SOC_ISP_TIMER_TIMER0_BGLOAD_UNION
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
} SOC_ISP_TIMER_TIMER0_BGLOAD_UNION;
#endif
#define SOC_ISP_TIMER_TIMER0_BGLOAD_timerxbgload_START  (0)
#define SOC_ISP_TIMER_TIMER0_BGLOAD_timerxbgload_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_TIMER_TIMER1_BGLOAD_UNION
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
} SOC_ISP_TIMER_TIMER1_BGLOAD_UNION;
#endif
#define SOC_ISP_TIMER_TIMER1_BGLOAD_timerxbgload_START  (0)
#define SOC_ISP_TIMER_TIMER1_BGLOAD_timerxbgload_END    (31)






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

#endif /* end of soc_isp_timer_interface.h */
