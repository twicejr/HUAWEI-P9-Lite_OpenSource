/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_cs_tpiu_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-11-20 11:31:16
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年11月20日
    作    者   : l00352922
    修改内容   : 从《Hi3660V100 SOC寄存器手册_CS_TPIU.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_CS_TPIU_INTERFACE_H__
#define __SOC_CS_TPIU_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) TPIU
 ****************************************************************************/
/* 寄存器说明：TPIU 接口位宽指示寄存器。
   位域定义UNION结构:  SOC_CS_TPIU_TPIU_SUPPORTED_PORT_SIZES_UNION */
#define SOC_CS_TPIU_TPIU_SUPPORTED_PORT_SIZES_ADDR(base) ((base) + (0x000))

/* 寄存器说明：TPIU 当前接口位宽指示寄存器。
   位域定义UNION结构:  SOC_CS_TPIU_TPIU_CURRENT_PORT_SIZES_UNION */
#define SOC_CS_TPIU_TPIU_CURRENT_PORT_SIZES_ADDR(base) ((base) + (0x004))

/* 寄存器说明：TPIU trigger模式指示寄存器。
   位域定义UNION结构:  SOC_CS_TPIU_TPIU_SUPPORTED_TRIGGER_MODES_UNION */
#define SOC_CS_TPIU_TPIU_SUPPORTED_TRIGGER_MODES_ADDR(base) ((base) + (0x100))

/* 寄存器说明：TPIU trigger计数器值寄存器。
   位域定义UNION结构:  SOC_CS_TPIU_TPIU_TRIGGER_COUNTER_VALUE_UNION */
#define SOC_CS_TPIU_TPIU_TRIGGER_COUNTER_VALUE_ADDR(base) ((base) + (0x104))

/* 寄存器说明：TPIU trigger乘数设置寄存器。
   位域定义UNION结构:  SOC_CS_TPIU_TPIU_TRIGGER_MULTIPLIER_UNION */
#define SOC_CS_TPIU_TPIU_TRIGGER_MULTIPLIER_ADDR(base) ((base) + (0x108))

/* 寄存器说明：TPIU test pattern模式指示寄存器。
   位域定义UNION结构:  SOC_CS_TPIU_TPIU_SUPPORTED_TEST_PATTERN_MODE_UNION */
#define SOC_CS_TPIU_TPIU_SUPPORTED_TEST_PATTERN_MODE_ADDR(base) ((base) + (0x200))

/* 寄存器说明：TPIU test pattern模式设置寄存器。
   位域定义UNION结构:  SOC_CS_TPIU_TPIU_CURRENT_TEST_PATTERN_MODE_UNION */
#define SOC_CS_TPIU_TPIU_CURRENT_TEST_PATTERN_MODE_ADDR(base) ((base) + (0x204))

/* 寄存器说明：TPIU test pattern计数器寄存器。
   位域定义UNION结构:  SOC_CS_TPIU_TPIU_TPRCR_UNION */
#define SOC_CS_TPIU_TPIU_TPRCR_ADDR(base)             ((base) + (0x208))

/* 寄存器说明：TPIU formatter and flush状态寄存器。
   位域定义UNION结构:  SOC_CS_TPIU_TPIU_FFSR_UNION */
#define SOC_CS_TPIU_TPIU_FFSR_ADDR(base)              ((base) + (0x300))

/* 寄存器说明：TPIU formatter and flush控制寄存器。
   位域定义UNION结构:  SOC_CS_TPIU_TPIU_FFCR_UNION */
#define SOC_CS_TPIU_TPIU_FFCR_ADDR(base)              ((base) + (0x304))

/* 寄存器说明：TPIU Formatter同步计数器寄存器。
   位域定义UNION结构:  SOC_CS_TPIU_TPIU_FSCR_UNION */
#define SOC_CS_TPIU_TPIU_FSCR_ADDR(base)              ((base) + (0x308))

/* 寄存器说明：TPIU EXCTL In Port寄存器。
   位域定义UNION结构:  SOC_CS_TPIU_TPIU_EXTCTL_IN_PORT_UNION */
#define SOC_CS_TPIU_TPIU_EXTCTL_IN_PORT_ADDR(base)    ((base) + (0x400))

/* 寄存器说明：TPIU EXCTL Out Port寄存器。
   位域定义UNION结构:  SOC_CS_TPIU_TPIU_EXTCTL_OUT_PORT_UNION */
#define SOC_CS_TPIU_TPIU_EXTCTL_OUT_PORT_ADDR(base)   ((base) + (0x404))

/* 寄存器说明：TPIU锁定访问寄存器。
   位域定义UNION结构:  SOC_CS_TPIU_TPIU_LAR_UNION */
#define SOC_CS_TPIU_TPIU_LAR_ADDR(base)               ((base) + (0xFB0))

/* 寄存器说明：TPIU锁定状态寄存器。
   位域定义UNION结构:  SOC_CS_TPIU_TPIU_LSR_UNION */
#define SOC_CS_TPIU_TPIU_LSR_ADDR(base)               ((base) + (0xFB4))





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
                     (1/1) TPIU
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_CS_TPIU_TPIU_SUPPORTED_PORT_SIZES_UNION
 结构说明  : TPIU_SUPPORTED_PORT_SIZES 寄存器结构定义。地址偏移量:0x000，初值:0x0000FFFF，宽度:32
 寄存器说明: TPIU 接口位宽指示寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  port_size_s : 16; /* bit[0-15] : Indicates the TPIU supports port size of 1-bit~16-bit. */
        unsigned int  reserved    : 16; /* bit[16-31]: Reserved */
    } reg;
} SOC_CS_TPIU_TPIU_SUPPORTED_PORT_SIZES_UNION;
#endif
#define SOC_CS_TPIU_TPIU_SUPPORTED_PORT_SIZES_port_size_s_START  (0)
#define SOC_CS_TPIU_TPIU_SUPPORTED_PORT_SIZES_port_size_s_END    (15)


/*****************************************************************************
 结构名    : SOC_CS_TPIU_TPIU_CURRENT_PORT_SIZES_UNION
 结构说明  : TPIU_CURRENT_PORT_SIZES 寄存器结构定义。地址偏移量:0x004，初值:0x00000001，宽度:32
 寄存器说明: TPIU 当前接口位宽指示寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  port_size_c : 16; /* bit[0-15] : 配置当前需要的port size，第n bit配置为1表示port size为n+1.例如，bit[15]配置为1，则port size设置为16. */
        unsigned int  reserved    : 16; /* bit[16-31]: Reserved */
    } reg;
} SOC_CS_TPIU_TPIU_CURRENT_PORT_SIZES_UNION;
#endif
#define SOC_CS_TPIU_TPIU_CURRENT_PORT_SIZES_port_size_c_START  (0)
#define SOC_CS_TPIU_TPIU_CURRENT_PORT_SIZES_port_size_c_END    (15)


/*****************************************************************************
 结构名    : SOC_CS_TPIU_TPIU_SUPPORTED_TRIGGER_MODES_UNION
 结构说明  : TPIU_SUPPORTED_TRIGGER_MODES 寄存器结构定义。地址偏移量:0x100，初值:0x0000011F，宽度:32
 寄存器说明: TPIU trigger模式指示寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mult2     : 1;  /* bit[0]    : Indicates multiplying the trigger counter by 2 is supported. */
        unsigned int  mult4     : 1;  /* bit[1]    : Indicates multiplying the trigger counter by 4 is supported. */
        unsigned int  mult16    : 1;  /* bit[2]    : Indicates multiplying the trigger counter by 16 is supported. */
        unsigned int  mult256   : 1;  /* bit[3]    : Indicates multiplying the trigger counter by 256 is supported. */
        unsigned int  mult64k   : 1;  /* bit[4]    : Indicates multiplying the trigger counter by 65536 is supported. */
        unsigned int  reserved_0: 3;  /* bit[5-7]  : Reserved */
        unsigned int  tcount8   : 1;  /* bit[8]    : Indicates an 8-bit wide counter register is implemented. */
        unsigned int  reserved_1: 7;  /* bit[9-15] : Reserved */
        unsigned int  triggered : 1;  /* bit[16]   : A trigger has occurred and the counter has reached 0.
                                                     0 Trigger has not occurred.
                                                     1 Trigger has occurred */
        unsigned int  trgrun    : 1;  /* bit[17]   : A trigger has occurred but the counter is not at 0.
                                                     0 Either a trigger has not occurred or the counter is at 0.
                                                     1 A trigger has occurred but the counter is not at 0. */
        unsigned int  reserved_2: 14; /* bit[18-31]: Reserved */
    } reg;
} SOC_CS_TPIU_TPIU_SUPPORTED_TRIGGER_MODES_UNION;
#endif
#define SOC_CS_TPIU_TPIU_SUPPORTED_TRIGGER_MODES_mult2_START      (0)
#define SOC_CS_TPIU_TPIU_SUPPORTED_TRIGGER_MODES_mult2_END        (0)
#define SOC_CS_TPIU_TPIU_SUPPORTED_TRIGGER_MODES_mult4_START      (1)
#define SOC_CS_TPIU_TPIU_SUPPORTED_TRIGGER_MODES_mult4_END        (1)
#define SOC_CS_TPIU_TPIU_SUPPORTED_TRIGGER_MODES_mult16_START     (2)
#define SOC_CS_TPIU_TPIU_SUPPORTED_TRIGGER_MODES_mult16_END       (2)
#define SOC_CS_TPIU_TPIU_SUPPORTED_TRIGGER_MODES_mult256_START    (3)
#define SOC_CS_TPIU_TPIU_SUPPORTED_TRIGGER_MODES_mult256_END      (3)
#define SOC_CS_TPIU_TPIU_SUPPORTED_TRIGGER_MODES_mult64k_START    (4)
#define SOC_CS_TPIU_TPIU_SUPPORTED_TRIGGER_MODES_mult64k_END      (4)
#define SOC_CS_TPIU_TPIU_SUPPORTED_TRIGGER_MODES_tcount8_START    (8)
#define SOC_CS_TPIU_TPIU_SUPPORTED_TRIGGER_MODES_tcount8_END      (8)
#define SOC_CS_TPIU_TPIU_SUPPORTED_TRIGGER_MODES_triggered_START  (16)
#define SOC_CS_TPIU_TPIU_SUPPORTED_TRIGGER_MODES_triggered_END    (16)
#define SOC_CS_TPIU_TPIU_SUPPORTED_TRIGGER_MODES_trgrun_START     (17)
#define SOC_CS_TPIU_TPIU_SUPPORTED_TRIGGER_MODES_trgrun_END       (17)


/*****************************************************************************
 结构名    : SOC_CS_TPIU_TPIU_TRIGGER_COUNTER_VALUE_UNION
 结构说明  : TPIU_TRIGGER_COUNTER_VALUE 寄存器结构定义。地址偏移量:0x104，初值:0x00000000，宽度:32
 寄存器说明: TPIU trigger计数器值寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  trigcount : 8;  /* bit[0-7] : 8-bit计数值，用于延迟指定数量words后再输出trigger。写操作会导致trigger计数器reload，读操作返回预设值，而不是当前计数值。 */
        unsigned int  reserved  : 24; /* bit[8-31]: Reserved */
    } reg;
} SOC_CS_TPIU_TPIU_TRIGGER_COUNTER_VALUE_UNION;
#endif
#define SOC_CS_TPIU_TPIU_TRIGGER_COUNTER_VALUE_trigcount_START  (0)
#define SOC_CS_TPIU_TPIU_TRIGGER_COUNTER_VALUE_trigcount_END    (7)


/*****************************************************************************
 结构名    : SOC_CS_TPIU_TPIU_TRIGGER_MULTIPLIER_UNION
 结构说明  : TPIU_TRIGGER_MULTIPLIER 寄存器结构定义。地址偏移量:0x108，初值:0x00000000，宽度:32
 寄存器说明: TPIU trigger乘数设置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mult2    : 1;  /* bit[0]   : Multiply the Trigger Counter by 2 (2^1).
                                                   0 Multiplier disabled.
                                                   1 Multiplier enabled */
        unsigned int  mult4    : 1;  /* bit[1]   : Multiply the Trigger Counter by 4 (2^2).
                                                   0 Multiplier disabled.
                                                   1 Multiplier enabled. */
        unsigned int  mult16   : 1;  /* bit[2]   : Multiply the Trigger Counter by 16 (2^4).
                                                   0 Multiplier disabled.
                                                   1 Multiplier enabled. */
        unsigned int  mult256  : 1;  /* bit[3]   : Multiply the Trigger Counter by 256 (2^8).
                                                   0 Multiplier disabled.
                                                   1 Multiplier enabled */
        unsigned int  mult64k  : 1;  /* bit[4]   : Multiply the Trigger Counter by 65536 (2^16).
                                                   0 Multiplier disabled.
                                                   1 Multiplier enabled. */
        unsigned int  reserved : 27; /* bit[5-31]: Reserved */
    } reg;
} SOC_CS_TPIU_TPIU_TRIGGER_MULTIPLIER_UNION;
#endif
#define SOC_CS_TPIU_TPIU_TRIGGER_MULTIPLIER_mult2_START     (0)
#define SOC_CS_TPIU_TPIU_TRIGGER_MULTIPLIER_mult2_END       (0)
#define SOC_CS_TPIU_TPIU_TRIGGER_MULTIPLIER_mult4_START     (1)
#define SOC_CS_TPIU_TPIU_TRIGGER_MULTIPLIER_mult4_END       (1)
#define SOC_CS_TPIU_TPIU_TRIGGER_MULTIPLIER_mult16_START    (2)
#define SOC_CS_TPIU_TPIU_TRIGGER_MULTIPLIER_mult16_END      (2)
#define SOC_CS_TPIU_TPIU_TRIGGER_MULTIPLIER_mult256_START   (3)
#define SOC_CS_TPIU_TPIU_TRIGGER_MULTIPLIER_mult256_END     (3)
#define SOC_CS_TPIU_TPIU_TRIGGER_MULTIPLIER_mult64k_START   (4)
#define SOC_CS_TPIU_TPIU_TRIGGER_MULTIPLIER_mult64k_END     (4)


/*****************************************************************************
 结构名    : SOC_CS_TPIU_TPIU_SUPPORTED_TEST_PATTERN_MODE_UNION
 结构说明  : TPIU_SUPPORTED_TEST_PATTERN_MODE 寄存器结构定义。地址偏移量:0x200，初值:0x0003000F，宽度:32
 寄存器说明: TPIU test pattern模式指示寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  patw1    : 1;  /* bit[0]    : Indicates the walking 1s pattern is supported as output over the trace port. */
        unsigned int  patw0    : 1;  /* bit[1]    : Indicates the walking 0s pattern is supported as output over the trace port. */
        unsigned int  pata5    : 1;  /* bit[2]    : Indicates the AA/55 pattern is supported as output over the trace port. */
        unsigned int  patf0    : 1;  /* bit[3]    : Indicates the FF/00 pattern is supported as output over the trace port. */
        unsigned int  reserved_0: 12; /* bit[4-15] : Reserved */
        unsigned int  ptimeen  : 1;  /* bit[16]   : Indicates timed mode is supported. */
        unsigned int  pcouten  : 1;  /* bit[17]   : Indicates continuous mode is supported. */
        unsigned int  reserved_1: 14; /* bit[18-31]: Reserved */
    } reg;
} SOC_CS_TPIU_TPIU_SUPPORTED_TEST_PATTERN_MODE_UNION;
#endif
#define SOC_CS_TPIU_TPIU_SUPPORTED_TEST_PATTERN_MODE_patw1_START     (0)
#define SOC_CS_TPIU_TPIU_SUPPORTED_TEST_PATTERN_MODE_patw1_END       (0)
#define SOC_CS_TPIU_TPIU_SUPPORTED_TEST_PATTERN_MODE_patw0_START     (1)
#define SOC_CS_TPIU_TPIU_SUPPORTED_TEST_PATTERN_MODE_patw0_END       (1)
#define SOC_CS_TPIU_TPIU_SUPPORTED_TEST_PATTERN_MODE_pata5_START     (2)
#define SOC_CS_TPIU_TPIU_SUPPORTED_TEST_PATTERN_MODE_pata5_END       (2)
#define SOC_CS_TPIU_TPIU_SUPPORTED_TEST_PATTERN_MODE_patf0_START     (3)
#define SOC_CS_TPIU_TPIU_SUPPORTED_TEST_PATTERN_MODE_patf0_END       (3)
#define SOC_CS_TPIU_TPIU_SUPPORTED_TEST_PATTERN_MODE_ptimeen_START   (16)
#define SOC_CS_TPIU_TPIU_SUPPORTED_TEST_PATTERN_MODE_ptimeen_END     (16)
#define SOC_CS_TPIU_TPIU_SUPPORTED_TEST_PATTERN_MODE_pcouten_START   (17)
#define SOC_CS_TPIU_TPIU_SUPPORTED_TEST_PATTERN_MODE_pcouten_END     (17)


/*****************************************************************************
 结构名    : SOC_CS_TPIU_TPIU_CURRENT_TEST_PATTERN_MODE_UNION
 结构说明  : TPIU_CURRENT_TEST_PATTERN_MODE 寄存器结构定义。地址偏移量:0x204，初值:0x00000000，宽度:32
 寄存器说明: TPIU test pattern模式设置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  patw1    : 1;  /* bit[0]    : Indicates whether the walking 1s pattern is enabled as output over the Trace Port.
                                                    0 Pattern disabled.
                                                    1 Pattern enabled. */
        unsigned int  patw0    : 1;  /* bit[1]    : Indicates whether the walking 0s pattern is enabled as output over the Trace Port.
                                                    0 Pattern disabled.
                                                    1 Pattern enabled. */
        unsigned int  pata5    : 1;  /* bit[2]    : Indicates whether the AA/55 pattern is enabled as output over the Trace Port.
                                                    0 Pattern disabled.
                                                    1 Pattern enabled. */
        unsigned int  patf0    : 1;  /* bit[3]    : Indicates whether the FF/00 pattern is enabled as output over the Trace Port.
                                                    0 Pattern disabled.
                                                    1 Pattern enabled. */
        unsigned int  reserved_0: 12; /* bit[4-15] : Reserved */
        unsigned int  ptimeen  : 1;  /* bit[16]   : Indicates whether Timed Mode is enabled.
                                                    0 Mode disabled.
                                                    1 Mode enabled. */
        unsigned int  pcouten  : 1;  /* bit[17]   : Indicates whether Continuous Mode is enabled.
                                                    0 Mode disabled.
                                                    1 Mode enabled. */
        unsigned int  reserved_1: 14; /* bit[18-31]: Reserved */
    } reg;
} SOC_CS_TPIU_TPIU_CURRENT_TEST_PATTERN_MODE_UNION;
#endif
#define SOC_CS_TPIU_TPIU_CURRENT_TEST_PATTERN_MODE_patw1_START     (0)
#define SOC_CS_TPIU_TPIU_CURRENT_TEST_PATTERN_MODE_patw1_END       (0)
#define SOC_CS_TPIU_TPIU_CURRENT_TEST_PATTERN_MODE_patw0_START     (1)
#define SOC_CS_TPIU_TPIU_CURRENT_TEST_PATTERN_MODE_patw0_END       (1)
#define SOC_CS_TPIU_TPIU_CURRENT_TEST_PATTERN_MODE_pata5_START     (2)
#define SOC_CS_TPIU_TPIU_CURRENT_TEST_PATTERN_MODE_pata5_END       (2)
#define SOC_CS_TPIU_TPIU_CURRENT_TEST_PATTERN_MODE_patf0_START     (3)
#define SOC_CS_TPIU_TPIU_CURRENT_TEST_PATTERN_MODE_patf0_END       (3)
#define SOC_CS_TPIU_TPIU_CURRENT_TEST_PATTERN_MODE_ptimeen_START   (16)
#define SOC_CS_TPIU_TPIU_CURRENT_TEST_PATTERN_MODE_ptimeen_END     (16)
#define SOC_CS_TPIU_TPIU_CURRENT_TEST_PATTERN_MODE_pcouten_START   (17)
#define SOC_CS_TPIU_TPIU_CURRENT_TEST_PATTERN_MODE_pcouten_END     (17)


/*****************************************************************************
 结构名    : SOC_CS_TPIU_TPIU_TPRCR_UNION
 结构说明  : TPIU_TPRCR 寄存器结构定义。地址偏移量:0x208，初值:0x00000000，宽度:32
 寄存器说明: TPIU test pattern计数器寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pattcount : 8;  /* bit[0-7] : 8-bit counter value to indicate the number of traceclkin cycles for which a pattern runs before it 
                                                    switches to the next pattern. */
        unsigned int  reserved  : 24; /* bit[8-31]: Reserved */
    } reg;
} SOC_CS_TPIU_TPIU_TPRCR_UNION;
#endif
#define SOC_CS_TPIU_TPIU_TPRCR_pattcount_START  (0)
#define SOC_CS_TPIU_TPIU_TPRCR_pattcount_END    (7)


/*****************************************************************************
 结构名    : SOC_CS_TPIU_TPIU_FFSR_UNION
 结构说明  : TPIU_FFSR 寄存器结构定义。地址偏移量:0x300，初值:0x00000000，宽度:32
 寄存器说明: TPIU formatter and flush状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flinprog  : 1;  /* bit[0]   : Flush in progress.
                                                    0 afvalids is LOW.
                                                    1 afvalids is HIGH */
        unsigned int  ftstopped : 1;  /* bit[1]   : The formatter has received a stop request signal and all trace data and post-amble is sent. Any additional trace data on the ATB interface is ignored and atreadys goes HIGH.
                                                    0 Formatter has not stopped.
                                                    1 Formatter has stopped. */
        unsigned int  tcpresent : 1;  /* bit[2]   : Indicates whether the TRACECTL pin is available for use.
                                                    0 TRACECTL pin not present.
                                                    1 TRACECTL pin present. */
        unsigned int  reserved  : 29; /* bit[3-31]: Reserved */
    } reg;
} SOC_CS_TPIU_TPIU_FFSR_UNION;
#endif
#define SOC_CS_TPIU_TPIU_FFSR_flinprog_START   (0)
#define SOC_CS_TPIU_TPIU_FFSR_flinprog_END     (0)
#define SOC_CS_TPIU_TPIU_FFSR_ftstopped_START  (1)
#define SOC_CS_TPIU_TPIU_FFSR_ftstopped_END    (1)
#define SOC_CS_TPIU_TPIU_FFSR_tcpresent_START  (2)
#define SOC_CS_TPIU_TPIU_FFSR_tcpresent_END    (2)


/*****************************************************************************
 结构名    : SOC_CS_TPIU_TPIU_FFCR_UNION
 结构说明  : TPIU_FFCR 寄存器结构定义。地址偏移量:0x304，初值:0x00000000，宽度:32
 寄存器说明: TPIU formatter and flush控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  enftc    : 1;  /* bit[0]    : Do not embed triggers into the formatted stream. Trace disable cycles and triggers are indicated 
                                                    by tracectl, where present.
                                                    0 Formatting disabled.
                                                    1 Formatting enabled. */
        unsigned int  encont   : 1;  /* bit[1]    : Is embedded in trigger packets and indicates that no cycle is using sync packets.
                                                    0 Continuous formatting disabled.
                                                    1 Continuous formatting enabled. */
        unsigned int  reserved_0: 2;  /* bit[2-3]  : Reserved */
        unsigned int  fonflin  : 1;  /* bit[4]    : Enables the use of the flushin connection.
                                                    0 Disable generation of flush using the flushin interface.
                                                    1 Enable generation of flush using the flushin interface */
        unsigned int  fontrig  : 1;  /* bit[5]    : Initiates a manual flush of data in the system when a trigger event occurs.
                                                    A trigger event occurs when the trigger counter reaches 0, or, if the trigger counter is 0, when 
                                                    trigin is HIGH.
                                                    0 Disable generation of flush when a Trigger Event occurs.
                                                    1 Enable generation of flush when a Trigger Event occurs. */
        unsigned int  fonman   : 1;  /* bit[6]    : Generates a flush. This bit is set to 0 when this flush is serviced.
                                                    0 Manual flush is not initiated.
                                                    1 Manual flush is initiated. */
        unsigned int  reserved_1: 1;  /* bit[7]    : Reserved */
        unsigned int  trigin   : 1;  /* bit[8]    : Indicates a trigger when trigin is asserted.
                                                    0 Disable trigger indication when trigin is asserted.
                                                    1 Enable trigger indication when trigin is asserted. */
        unsigned int  trigevt  : 1;  /* bit[9]    : Indicates a trigger on a trigger event.
                                                    0 Disable trigger indication on a trigger event.
                                                    1 Enable trigger indication on a trigger event */
        unsigned int  trigfl   : 1;  /* bit[10]   : Indicates a trigger when flush completion on afreadys is returned.
                                                    0 Disable trigger indication on return of afreadys.
                                                    1 Enable trigger indication on return of afreadys. */
        unsigned int  reserved_2: 1;  /* bit[11]   : Reserved */
        unsigned int  stopfl   : 1;  /* bit[12]   : Forces the FIFO to drain off any part-completed packets.
                                                    0 Disable stopping the formatter on return of afreadys.
                                                    1 Enable stopping the formatter on return of afreadys */
        unsigned int  stoptrig : 1;  /* bit[13]   : Stops the formatter after a trigger event is observed. Reset to disabled or 0.
                                                    0 Disable stopping the formatter after a trigger event is observed.
                                                    1 Enable stopping the formatter after a trigger event is observed. */
        unsigned int  reserved_3: 18; /* bit[14-31]: Reserved */
    } reg;
} SOC_CS_TPIU_TPIU_FFCR_UNION;
#endif
#define SOC_CS_TPIU_TPIU_FFCR_enftc_START     (0)
#define SOC_CS_TPIU_TPIU_FFCR_enftc_END       (0)
#define SOC_CS_TPIU_TPIU_FFCR_encont_START    (1)
#define SOC_CS_TPIU_TPIU_FFCR_encont_END      (1)
#define SOC_CS_TPIU_TPIU_FFCR_fonflin_START   (4)
#define SOC_CS_TPIU_TPIU_FFCR_fonflin_END     (4)
#define SOC_CS_TPIU_TPIU_FFCR_fontrig_START   (5)
#define SOC_CS_TPIU_TPIU_FFCR_fontrig_END     (5)
#define SOC_CS_TPIU_TPIU_FFCR_fonman_START    (6)
#define SOC_CS_TPIU_TPIU_FFCR_fonman_END      (6)
#define SOC_CS_TPIU_TPIU_FFCR_trigin_START    (8)
#define SOC_CS_TPIU_TPIU_FFCR_trigin_END      (8)
#define SOC_CS_TPIU_TPIU_FFCR_trigevt_START   (9)
#define SOC_CS_TPIU_TPIU_FFCR_trigevt_END     (9)
#define SOC_CS_TPIU_TPIU_FFCR_trigfl_START    (10)
#define SOC_CS_TPIU_TPIU_FFCR_trigfl_END      (10)
#define SOC_CS_TPIU_TPIU_FFCR_stopfl_START    (12)
#define SOC_CS_TPIU_TPIU_FFCR_stopfl_END      (12)
#define SOC_CS_TPIU_TPIU_FFCR_stoptrig_START  (13)
#define SOC_CS_TPIU_TPIU_FFCR_stoptrig_END    (13)


/*****************************************************************************
 结构名    : SOC_CS_TPIU_TPIU_FSCR_UNION
 结构说明  : TPIU_FSCR 寄存器结构定义。地址偏移量:0x308，初值:0x00000040，宽度:32
 寄存器说明: TPIU Formatter同步计数器寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cyccount : 12; /* bit[0-11] : 12-bit计数值，用于周期性的产生同步包。初始值为0x40，即每64帧数据后产生同步包。 */
        unsigned int  reserved : 20; /* bit[12-31]: Reserved */
    } reg;
} SOC_CS_TPIU_TPIU_FSCR_UNION;
#endif
#define SOC_CS_TPIU_TPIU_FSCR_cyccount_START  (0)
#define SOC_CS_TPIU_TPIU_FSCR_cyccount_END    (11)


/*****************************************************************************
 结构名    : SOC_CS_TPIU_TPIU_EXTCTL_IN_PORT_UNION
 结构说明  : TPIU_EXTCTL_IN_PORT 寄存器结构定义。地址偏移量:0x400，初值:0x00000000，宽度:32
 寄存器说明: TPIU EXCTL In Port寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  extctlin : 8;  /* bit[0-7] : EXTCTL inputs. */
        unsigned int  reserved : 24; /* bit[8-31]: Reserved */
    } reg;
} SOC_CS_TPIU_TPIU_EXTCTL_IN_PORT_UNION;
#endif
#define SOC_CS_TPIU_TPIU_EXTCTL_IN_PORT_extctlin_START  (0)
#define SOC_CS_TPIU_TPIU_EXTCTL_IN_PORT_extctlin_END    (7)


/*****************************************************************************
 结构名    : SOC_CS_TPIU_TPIU_EXTCTL_OUT_PORT_UNION
 结构说明  : TPIU_EXTCTL_OUT_PORT 寄存器结构定义。地址偏移量:0x404，初值:0x00000000，宽度:32
 寄存器说明: TPIU EXCTL Out Port寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  extctlout : 8;  /* bit[0-7] : EXTCTL outputs. */
        unsigned int  reserved  : 24; /* bit[8-31]: Reserved */
    } reg;
} SOC_CS_TPIU_TPIU_EXTCTL_OUT_PORT_UNION;
#endif
#define SOC_CS_TPIU_TPIU_EXTCTL_OUT_PORT_extctlout_START  (0)
#define SOC_CS_TPIU_TPIU_EXTCTL_OUT_PORT_extctlout_END    (7)


/*****************************************************************************
 结构名    : SOC_CS_TPIU_TPIU_LAR_UNION
 结构说明  : TPIU_LAR 寄存器结构定义。地址偏移量:0xFB0，初值:0x00000000，宽度:32
 寄存器说明: TPIU锁定访问寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  key : 32; /* bit[0-31]: 写入0xC5ACCE55进行解锁，然后才可以正常配置其他寄存器；写入其他任何值后再次锁定。 */
    } reg;
} SOC_CS_TPIU_TPIU_LAR_UNION;
#endif
#define SOC_CS_TPIU_TPIU_LAR_key_START  (0)
#define SOC_CS_TPIU_TPIU_LAR_key_END    (31)


/*****************************************************************************
 结构名    : SOC_CS_TPIU_TPIU_LSR_UNION
 结构说明  : TPIU_LSR 寄存器结构定义。地址偏移量:0xFB4，初值:0x00000003，宽度:32
 寄存器说明: TPIU锁定状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sli      : 1;  /* bit[0]   : 指示期间是否支持锁定机制：
                                                   0：组件不支持锁定机制
                                                   1：组件支持锁定机制 */
        unsigned int  slk      : 1;  /* bit[1]   : 组件的当前锁定状态：
                                                   0：已解锁，允许写操作
                                                   1：已锁定，不允许写操作，可读 */
        unsigned int  ntt      : 1;  /* bit[2]   : 指示锁定访问寄存器为32-bit */
        unsigned int  reserved : 29; /* bit[3-31]: Reserved */
    } reg;
} SOC_CS_TPIU_TPIU_LSR_UNION;
#endif
#define SOC_CS_TPIU_TPIU_LSR_sli_START       (0)
#define SOC_CS_TPIU_TPIU_LSR_sli_END         (0)
#define SOC_CS_TPIU_TPIU_LSR_slk_START       (1)
#define SOC_CS_TPIU_TPIU_LSR_slk_END         (1)
#define SOC_CS_TPIU_TPIU_LSR_ntt_START       (2)
#define SOC_CS_TPIU_TPIU_LSR_ntt_END         (2)






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

#endif /* end of soc_cs_tpiu_interface.h */
