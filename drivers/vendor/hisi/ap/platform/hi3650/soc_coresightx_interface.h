/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_coresightx_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:19:10
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_coresightx.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_CORESIGHTX_INTERFACE_H__
#define __SOC_CORESIGHTX_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) CORESIGHT
 ****************************************************************************/
/* 寄存器说明：Funnel控制寄存器
   位域定义UNION结构:  SOC_coresightx_CTRL_REG_UNION */
#define SOC_coresightx_CTRL_REG_ADDR(base)            ((base) + (0x1000))

/* 寄存器说明：Funnel优先级控制寄存器
   位域定义UNION结构:  SOC_coresightx_PRIORITY_CTRL_REG_UNION */
#define SOC_coresightx_PRIORITY_CTRL_REG_ADDR(base)   ((base) + (0x1004))

/* 寄存器说明：Funnel锁定访问寄存器
   位域定义UNION结构:  SOC_coresightx_LOCKACCESS_UNION */
#define SOC_coresightx_LOCKACCESS_ADDR(base)          ((base) + (0x1FB0))

/* 寄存器说明：Funnel锁定状态寄存器
   位域定义UNION结构:  SOC_coresightx_LOCKSTATUS_UNION */
#define SOC_coresightx_LOCKSTATUS_ADDR(base)          ((base) + (0x1FB4))

/* 寄存器说明：TPIU trigger计数器值寄存器
   位域定义UNION结构:  SOC_coresightx_TRIGGER_COUNTER_VALUE_UNION */
#define SOC_coresightx_TRIGGER_COUNTER_VALUE_ADDR(base) ((base) + (0x2104))

/* 寄存器说明：TPIU Formatter同步计数器寄存器
   位域定义UNION结构:  SOC_coresightx_FSCR_UNION */
#define SOC_coresightx_FSCR_ADDR(base)                ((base) + (0x2308))

/* 寄存器说明：TPIU集成测试模式控制寄存器
   位域定义UNION结构:  SOC_coresightx_ITCTRL_UNION */
#define SOC_coresightx_ITCTRL_ADDR(base)              ((base) + (0x2F00))

/* 寄存器说明：ETR RAM size寄存器
   位域定义UNION结构:  SOC_coresightx_RSZ_UNION */
#define SOC_coresightx_RSZ_ADDR(base)                 ((base) + (0x3004))

/* 寄存器说明：ETR控制寄存器
   位域定义UNION结构:  SOC_coresightx_CTL_UNION */
#define SOC_coresightx_CTL_ADDR(base)                 ((base) + (0x3020))

/* 寄存器说明：ETR数据buffer地址寄存器
   位域定义UNION结构:  SOC_coresightx_DBALO_UNION */
#define SOC_coresightx_DBALO_ADDR(base)               ((base) + (0x3118))

/* 寄存器说明：CTI控制寄存器
   位域定义UNION结构:  SOC_coresightx_CTICONTROL_UNION */
#define SOC_coresightx_CTICONTROL_ADDR(base)          ((base) + (0x4000))

/* 寄存器说明：CTItrigger0至channel使能寄存器
   位域定义UNION结构:  SOC_coresightx_CTIINEN0_UNION */
#define SOC_coresightx_CTIINEN0_ADDR(base)            ((base) + (0x4020))

/* 寄存器说明：CTI channel使能寄存器
   位域定义UNION结构:  SOC_coresightx_CTIGATE_UNION */
#define SOC_coresightx_CTIGATE_ADDR(base)             ((base) + (0x4140))

/* 寄存器说明：STM硬件事件使能寄存器
   位域定义UNION结构:  SOC_coresightx_STMHEER_UNION */
#define SOC_coresightx_STMHEER_ADDR(base)             ((base) + (0x5D00))

/* 寄存器说明：STM激励端口使能信号
   位域定义UNION结构:  SOC_coresightx_STMSPER_UNION */
#define SOC_coresightx_STMSPER_ADDR(base)             ((base) + (0x5E00))

/* 寄存器说明：STM trace控制与状态寄存器
   位域定义UNION结构:  SOC_coresightx_STMTCSR_UNION */
#define SOC_coresightx_STMTCSR_ADDR(base)             ((base) + (0x5E80))

/* 寄存器说明：ETF控制寄存器
   位域定义UNION结构:  SOC_coresightx_ETFCTL_UNION */
#define SOC_coresightx_ETFCTL_ADDR(base)              ((base) + (0x6020))

/* 寄存器说明：ETF工作模式寄存器
   位域定义UNION结构:  SOC_coresightx_ETFMODE_UNION */
#define SOC_coresightx_ETFMODE_ADDR(base)             ((base) + (0x6028))

/* 寄存器说明：ETF集成模式控制寄存器
   位域定义UNION结构:  SOC_coresightx_ETFITCTRL_UNION */
#define SOC_coresightx_ETFITCTRL_ADDR(base)           ((base) + (0x6F00))

/* 寄存器说明：timestamp计数控制寄存器
   位域定义UNION结构:  SOC_coresightx_TSCNTCR_UNION */
#define SOC_coresightx_TSCNTCR_ADDR(base)             ((base) + (0x7000))

/* 寄存器说明：timestamp当前计数值低位寄存器
   位域定义UNION结构:  SOC_coresightx_TSCNTCVLW_UNION */
#define SOC_coresightx_TSCNTCVLW_ADDR(base)           ((base) + (0x7008))

/* 寄存器说明：timestamp当前计数值高位寄存器
   位域定义UNION结构:  SOC_coresightx_TSCNTCVUP_UNION */
#define SOC_coresightx_TSCNTCVUP_ADDR(base)           ((base) + (0x700C))

/* 寄存器说明：timestamp当前计数值低位寄存器
   位域定义UNION结构:  SOC_coresightx_TSCNTCVLW_RO_UNION */
#define SOC_coresightx_TSCNTCVLW_RO_ADDR(base)        ((base) + (0x8000))

/* 寄存器说明：timestamp当前计数值高位寄存器
   位域定义UNION结构:  SOC_coresightx_TSCNTCVUP_RO_UNION */
#define SOC_coresightx_TSCNTCVUP_RO_ADDR(base)        ((base) + (0x8004))





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
                     (1/1) CORESIGHT
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_coresightx_CTRL_REG_UNION
 结构说明  : CTRL_REG 寄存器结构定义。地址偏移量:0x1000，初值:0x00000300，宽度:32
 寄存器说明: Funnel控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  enable   : 5;  /* bit[0-4]  : bit[0]~bit[3]分别对应port0~port4。
                                                    0：slave port disabled
                                                    1：slave port enabled */
        unsigned int  reserved_0: 3;  /* bit[5-7]  : Reserved */
        unsigned int  holdtime : 4;  /* bit[8-11] : Funnel ATB slave端口一次最少接收的transaction数。设置hold time是为了降低端口频繁切换对trace性能带来的影响。最少接收的transaction数为hold time值加1，取值范围b0000~b1110，b1111保留。 */
        unsigned int  reserved_1: 20; /* bit[12-31]: Reserved */
    } reg;
} SOC_coresightx_CTRL_REG_UNION;
#endif
#define SOC_coresightx_CTRL_REG_enable_START    (0)
#define SOC_coresightx_CTRL_REG_enable_END      (4)
#define SOC_coresightx_CTRL_REG_holdtime_START  (8)
#define SOC_coresightx_CTRL_REG_holdtime_END    (11)


/*****************************************************************************
 结构名    : SOC_coresightx_PRIORITY_CTRL_REG_UNION
 结构说明  : PRIORITY_CTRL_REG 寄存器结构定义。地址偏移量:0x1004，初值:0x00000000，宽度:32
 寄存器说明: Funnel优先级控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  priport0 : 3;  /* bit[0-2]  : 端口0优先级设置 */
        unsigned int  priport1 : 3;  /* bit[3-5]  : 端口1优先级设置 */
        unsigned int  priport2 : 3;  /* bit[6-8]  : 端口2优先级设置 */
        unsigned int  priport3 : 3;  /* bit[9-11] : 端口3优先级设置 */
        unsigned int  priport4 : 3;  /* bit[12-14]: 端口4优先级设置，数值越低，优先级越高；当设置值相同时，编号小的端口优先级较高。可能的取值如下：
                                                    b000：优先级0
                                                    b001：优先级1
                                                    b010：优先级2
                                                    b011：优先级3
                                                    b100：优先级4
                                                    b101：优先级5
                                                    b110：优先级6
                                                    b111：优先级0 */
        unsigned int  reserved : 17; /* bit[15-31]: Reserved */
    } reg;
} SOC_coresightx_PRIORITY_CTRL_REG_UNION;
#endif
#define SOC_coresightx_PRIORITY_CTRL_REG_priport0_START  (0)
#define SOC_coresightx_PRIORITY_CTRL_REG_priport0_END    (2)
#define SOC_coresightx_PRIORITY_CTRL_REG_priport1_START  (3)
#define SOC_coresightx_PRIORITY_CTRL_REG_priport1_END    (5)
#define SOC_coresightx_PRIORITY_CTRL_REG_priport2_START  (6)
#define SOC_coresightx_PRIORITY_CTRL_REG_priport2_END    (8)
#define SOC_coresightx_PRIORITY_CTRL_REG_priport3_START  (9)
#define SOC_coresightx_PRIORITY_CTRL_REG_priport3_END    (11)
#define SOC_coresightx_PRIORITY_CTRL_REG_priport4_START  (12)
#define SOC_coresightx_PRIORITY_CTRL_REG_priport4_END    (14)


/*****************************************************************************
 结构名    : SOC_coresightx_LOCKACCESS_UNION
 结构说明  : LOCKACCESS 寄存器结构定义。地址偏移量:0x1FB0，初值:0x00000000，宽度:32
 寄存器说明: Funnel锁定访问寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  key : 32; /* bit[0-31]: 写入0xC5ACCE55进行解锁，然后才可以正常配置funnel寄存器；写入其他任何值后再次锁定。 */
    } reg;
} SOC_coresightx_LOCKACCESS_UNION;
#endif
#define SOC_coresightx_LOCKACCESS_key_START  (0)
#define SOC_coresightx_LOCKACCESS_key_END    (31)


/*****************************************************************************
 结构名    : SOC_coresightx_LOCKSTATUS_UNION
 结构说明  : LOCKSTATUS 寄存器结构定义。地址偏移量:0x1FB4，初值:0x00000003，宽度:32
 寄存器说明: Funnel锁定状态寄存器
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
} SOC_coresightx_LOCKSTATUS_UNION;
#endif
#define SOC_coresightx_LOCKSTATUS_sli_START       (0)
#define SOC_coresightx_LOCKSTATUS_sli_END         (0)
#define SOC_coresightx_LOCKSTATUS_slk_START       (1)
#define SOC_coresightx_LOCKSTATUS_slk_END         (1)
#define SOC_coresightx_LOCKSTATUS_ntt_START       (2)
#define SOC_coresightx_LOCKSTATUS_ntt_END         (2)


/*****************************************************************************
 结构名    : SOC_coresightx_TRIGGER_COUNTER_VALUE_UNION
 结构说明  : TRIGGER_COUNTER_VALUE 寄存器结构定义。地址偏移量:0x2104，初值:0x00000000，宽度:32
 寄存器说明: TPIU trigger计数器值寄存器
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
} SOC_coresightx_TRIGGER_COUNTER_VALUE_UNION;
#endif
#define SOC_coresightx_TRIGGER_COUNTER_VALUE_trigcount_START  (0)
#define SOC_coresightx_TRIGGER_COUNTER_VALUE_trigcount_END    (7)


/*****************************************************************************
 结构名    : SOC_coresightx_FSCR_UNION
 结构说明  : FSCR 寄存器结构定义。地址偏移量:0x2308，初值:0x00000040，宽度:32
 寄存器说明: TPIU Formatter同步计数器寄存器
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
} SOC_coresightx_FSCR_UNION;
#endif
#define SOC_coresightx_FSCR_cyccount_START  (0)
#define SOC_coresightx_FSCR_cyccount_END    (11)


/*****************************************************************************
 结构名    : SOC_coresightx_ITCTRL_UNION
 结构说明  : ITCTRL 寄存器结构定义。地址偏移量:0x2F00，初值:0x00000000，宽度:32
 寄存器说明: TPIU集成测试模式控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ime      : 1;  /* bit[0]   : 集成测试模式控制位。
                                                   0：正常工作模式
                                                   1：集成测试模式 */
        unsigned int  reserved : 31; /* bit[1-31]: Reserved */
    } reg;
} SOC_coresightx_ITCTRL_UNION;
#endif
#define SOC_coresightx_ITCTRL_ime_START       (0)
#define SOC_coresightx_ITCTRL_ime_END         (0)


/*****************************************************************************
 结构名    : SOC_coresightx_RSZ_UNION
 结构说明  : RSZ 寄存器结构定义。地址偏移量:0x3004，初值:0x00000400，宽度:32
 寄存器说明: ETR RAM size寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rsz      : 31; /* bit[0-30]: trace buffer的大小，以32-bit word为单位。如1KB时，寄存器值为0x00000100 */
        unsigned int  reserved : 1;  /* bit[31]  : Reserved */
    } reg;
} SOC_coresightx_RSZ_UNION;
#endif
#define SOC_coresightx_RSZ_rsz_START       (0)
#define SOC_coresightx_RSZ_rsz_END         (30)


/*****************************************************************************
 结构名    : SOC_coresightx_CTL_UNION
 结构说明  : CTL 寄存器结构定义。地址偏移量:0x3020，初值:0x00000000，宽度:32
 寄存器说明: ETR控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tracecapten : 1;  /* bit[0]   : 控制trace数据的捕捉 */
        unsigned int  reserved    : 31; /* bit[1-31]: Reserved */
    } reg;
} SOC_coresightx_CTL_UNION;
#endif
#define SOC_coresightx_CTL_tracecapten_START  (0)
#define SOC_coresightx_CTL_tracecapten_END    (0)


/*****************************************************************************
 结构名    : SOC_coresightx_DBALO_UNION
 结构说明  : DBALO 寄存器结构定义。地址偏移量:0x3118，初值:0x00000000，宽度:32
 寄存器说明: ETR数据buffer地址寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bufaddrlo : 32; /* bit[0-31]: 作为trace buffer的系统内存的低32-bit地址 */
    } reg;
} SOC_coresightx_DBALO_UNION;
#endif
#define SOC_coresightx_DBALO_bufaddrlo_START  (0)
#define SOC_coresightx_DBALO_bufaddrlo_END    (31)


/*****************************************************************************
 结构名    : SOC_coresightx_CTICONTROL_UNION
 结构说明  : CTICONTROL 寄存器结构定义。地址偏移量:0x4000，初值:0x00000000，宽度:32
 寄存器说明: CTI控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  glben    : 1;  /* bit[0]   : CTI整体使能控制位
                                                   0：disabled
                                                   1：enabled */
        unsigned int  reserved : 31; /* bit[1-31]: Reserved */
    } reg;
} SOC_coresightx_CTICONTROL_UNION;
#endif
#define SOC_coresightx_CTICONTROL_glben_START     (0)
#define SOC_coresightx_CTICONTROL_glben_END       (0)


/*****************************************************************************
 结构名    : SOC_coresightx_CTIINEN0_UNION
 结构说明  : CTIINEN0 寄存器结构定义。地址偏移量:0x4020，初值:0x00000000，宽度:32
 寄存器说明: CTItrigger0至channel使能寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  triginen : 4;  /* bit[0-3] : 使能trigger事件到相应channel的映射
                                                   0：disable CTITRIGIN到相应channel的映射
                                                   1：enable CTITRIGIN到相应channel的映射 */
        unsigned int  reserved : 28; /* bit[4-31]: Reserved */
    } reg;
} SOC_coresightx_CTIINEN0_UNION;
#endif
#define SOC_coresightx_CTIINEN0_triginen_START  (0)
#define SOC_coresightx_CTIINEN0_triginen_END    (3)


/*****************************************************************************
 结构名    : SOC_coresightx_CTIGATE_UNION
 结构说明  : CTIGATE 寄存器结构定义。地址偏移量:0x4140，初值:0x0000000F，宽度:32
 寄存器说明: CTI channel使能寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctigateen0 : 1;  /* bit[0]   : 使能通道0
                                                     0：disable CTICHOUT0
                                                     1：enable CTICHOUT0 */
        unsigned int  ctigateen1 : 1;  /* bit[1]   : 使能通道1
                                                     0：disable CTICHOUT1
                                                     1：enable CTICHOUT1 */
        unsigned int  ctigateen2 : 1;  /* bit[2]   : 使能通道2
                                                     0：disable CTICHOUT2
                                                     1：enable CTICHOUT2 */
        unsigned int  ctigateen3 : 1;  /* bit[3]   : 使能通道3
                                                     0：disable CTICHOUT3
                                                     1：enable CTICHOUT3 */
        unsigned int  reserved   : 28; /* bit[4-31]: Reserved */
    } reg;
} SOC_coresightx_CTIGATE_UNION;
#endif
#define SOC_coresightx_CTIGATE_ctigateen0_START  (0)
#define SOC_coresightx_CTIGATE_ctigateen0_END    (0)
#define SOC_coresightx_CTIGATE_ctigateen1_START  (1)
#define SOC_coresightx_CTIGATE_ctigateen1_END    (1)
#define SOC_coresightx_CTIGATE_ctigateen2_START  (2)
#define SOC_coresightx_CTIGATE_ctigateen2_END    (2)
#define SOC_coresightx_CTIGATE_ctigateen3_START  (3)
#define SOC_coresightx_CTIGATE_ctigateen3_END    (3)


/*****************************************************************************
 结构名    : SOC_coresightx_STMHEER_UNION
 结构说明  : STMHEER 寄存器结构定义。地址偏移量:0x5D00，初值:0x00000000，宽度:32
 寄存器说明: STM硬件事件使能寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  heen : 32; /* bit[0-31]: 硬件监测事件使能，每bit对应1个事件：
                                               0：硬事件disabled
                                               1：硬事件enabled */
    } reg;
} SOC_coresightx_STMHEER_UNION;
#endif
#define SOC_coresightx_STMHEER_heen_START  (0)
#define SOC_coresightx_STMHEER_heen_END    (31)


/*****************************************************************************
 结构名    : SOC_coresightx_STMSPER_UNION
 结构说明  : STMSPER 寄存器结构定义。地址偏移量:0x5E00，初值:0x00000000，宽度:32
 寄存器说明: STM激励端口使能信号
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  spe : 32; /* bit[0-31]: 激励端口使能控制每bit对应一个端口
                                              0：该端口disable
                                              1：该端口enable */
    } reg;
} SOC_coresightx_STMSPER_UNION;
#endif
#define SOC_coresightx_STMSPER_spe_START  (0)
#define SOC_coresightx_STMSPER_spe_END    (31)


/*****************************************************************************
 结构名    : SOC_coresightx_STMTCSR_UNION
 结构说明  : STMTCSR 寄存器结构定义。地址偏移量:0x5E80，初值:0x00000004，宽度:32
 寄存器说明: STM trace控制与状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  en       : 1;  /* bit[0]    : STM全局使能
                                                    0：STM disabled
                                                    1：STM enabled */
        unsigned int  tsen     : 1;  /* bit[1]    : 控制时间戳请求是否被忽略
                                                    0：timestamp disabled，产生时间戳的请求被忽略
                                                    1：timestamp enabled，可由激励端口选择timestamping来产生时间戳 */
        unsigned int  syncen   : 1;  /* bit[2]    : STM同步控制寄存器可用。 */
        unsigned int  reserved_0: 2;  /* bit[3-4]  : Reserved */
        unsigned int  compen   : 1;  /* bit[5]    : 激励端口数据压缩使能
                                                    0：压缩disabled，数据以原始size进行传输
                                                    1：压缩enabled，数据被压缩以节省带宽 */
        unsigned int  reserved_1: 10; /* bit[6-15] : Reserved */
        unsigned int  traceid  : 7;  /* bit[16-22]: ATB trace ID */
        unsigned int  busy     : 1;  /* bit[23]   : 0：STM is not busy
                                                    1：STM is busy */
        unsigned int  reserved_2: 8;  /* bit[24-31]: Reserved */
    } reg;
} SOC_coresightx_STMTCSR_UNION;
#endif
#define SOC_coresightx_STMTCSR_en_START        (0)
#define SOC_coresightx_STMTCSR_en_END          (0)
#define SOC_coresightx_STMTCSR_tsen_START      (1)
#define SOC_coresightx_STMTCSR_tsen_END        (1)
#define SOC_coresightx_STMTCSR_syncen_START    (2)
#define SOC_coresightx_STMTCSR_syncen_END      (2)
#define SOC_coresightx_STMTCSR_compen_START    (5)
#define SOC_coresightx_STMTCSR_compen_END      (5)
#define SOC_coresightx_STMTCSR_traceid_START   (16)
#define SOC_coresightx_STMTCSR_traceid_END     (22)
#define SOC_coresightx_STMTCSR_busy_START      (23)
#define SOC_coresightx_STMTCSR_busy_END        (23)


/*****************************************************************************
 结构名    : SOC_coresightx_ETFCTL_UNION
 结构说明  : ETFCTL 寄存器结构定义。地址偏移量:0x6020，初值:0x00000000，宽度:32
 寄存器说明: ETF控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tracecapten : 1;  /* bit[0]   : 控制trace数据的捕捉 */
        unsigned int  reserved    : 31; /* bit[1-31]: Reserved */
    } reg;
} SOC_coresightx_ETFCTL_UNION;
#endif
#define SOC_coresightx_ETFCTL_tracecapten_START  (0)
#define SOC_coresightx_ETFCTL_tracecapten_END    (0)


/*****************************************************************************
 结构名    : SOC_coresightx_ETFMODE_UNION
 结构说明  : ETFMODE 寄存器结构定义。地址偏移量:0x6028，初值:0x00000000，宽度:32
 寄存器说明: ETF工作模式寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode     : 2;  /* bit[0-1] : 选择ETF的工作模式。
                                                   11：Reserved
                                                   10：Hardware FIFO mode
                                                   01：Software FIFO mode
                                                   00：Circular Buffer mode */
        unsigned int  reserved : 30; /* bit[2-31]: Reserved */
    } reg;
} SOC_coresightx_ETFMODE_UNION;
#endif
#define SOC_coresightx_ETFMODE_mode_START      (0)
#define SOC_coresightx_ETFMODE_mode_END        (1)


/*****************************************************************************
 结构名    : SOC_coresightx_ETFITCTRL_UNION
 结构说明  : ETFITCTRL 寄存器结构定义。地址偏移量:0x6F00，初值:0x00000000，宽度:32
 寄存器说明: ETF集成模式控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  integrationmode : 1;  /* bit[0]   : 控制ETF在工作模式和集成模式之间切换。
                                                          0：disable integration mode
                                                          1：enable integration mode */
        unsigned int  reserved        : 31; /* bit[1-31]: Reserved */
    } reg;
} SOC_coresightx_ETFITCTRL_UNION;
#endif
#define SOC_coresightx_ETFITCTRL_integrationmode_START  (0)
#define SOC_coresightx_ETFITCTRL_integrationmode_END    (0)


/*****************************************************************************
 结构名    : SOC_coresightx_TSCNTCR_UNION
 结构说明  : TSCNTCR 寄存器结构定义。地址偏移量:0x7000，初值:0x00000000，宽度:32
 寄存器说明: timestamp计数控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  en       : 1;  /* bit[0]   : 使能控制
                                                   0：计数器disabled
                                                   1：计数器enabled */
        unsigned int  hdbg     : 1;  /* bit[1]   : Halt on debug控制
                                                   0：HLTDBG信号对计数器无影响
                                                   1：HLTDBG信号有效时将暂停计数 */
        unsigned int  reserved : 30; /* bit[2-31]: Reserved */
    } reg;
} SOC_coresightx_TSCNTCR_UNION;
#endif
#define SOC_coresightx_TSCNTCR_en_START        (0)
#define SOC_coresightx_TSCNTCR_en_END          (0)
#define SOC_coresightx_TSCNTCR_hdbg_START      (1)
#define SOC_coresightx_TSCNTCR_hdbg_END        (1)


/*****************************************************************************
 结构名    : SOC_coresightx_TSCNTCVLW_UNION
 结构说明  : TSCNTCVLW 寄存器结构定义。地址偏移量:0x7008，初值:0x00000000，宽度:32
 寄存器说明: timestamp当前计数值低位寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cntcvlw : 32; /* bit[0-31]: 当前计数值的bit[31:0] */
    } reg;
} SOC_coresightx_TSCNTCVLW_UNION;
#endif
#define SOC_coresightx_TSCNTCVLW_cntcvlw_START  (0)
#define SOC_coresightx_TSCNTCVLW_cntcvlw_END    (31)


/*****************************************************************************
 结构名    : SOC_coresightx_TSCNTCVUP_UNION
 结构说明  : TSCNTCVUP 寄存器结构定义。地址偏移量:0x700C，初值:0x00000000，宽度:32
 寄存器说明: timestamp当前计数值高位寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cntcvup : 32; /* bit[0-31]: 当前计数值的bit[63:32] */
    } reg;
} SOC_coresightx_TSCNTCVUP_UNION;
#endif
#define SOC_coresightx_TSCNTCVUP_cntcvup_START  (0)
#define SOC_coresightx_TSCNTCVUP_cntcvup_END    (31)


/*****************************************************************************
 结构名    : SOC_coresightx_TSCNTCVLW_RO_UNION
 结构说明  : TSCNTCVLW_RO 寄存器结构定义。地址偏移量:0x8000，初值:0x00000000，宽度:32
 寄存器说明: timestamp当前计数值低位寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cntcvlw_ro : 32; /* bit[0-31]: 当前计数值的bit[31:0]，只读属性 */
    } reg;
} SOC_coresightx_TSCNTCVLW_RO_UNION;
#endif
#define SOC_coresightx_TSCNTCVLW_RO_cntcvlw_ro_START  (0)
#define SOC_coresightx_TSCNTCVLW_RO_cntcvlw_ro_END    (31)


/*****************************************************************************
 结构名    : SOC_coresightx_TSCNTCVUP_RO_UNION
 结构说明  : TSCNTCVUP_RO 寄存器结构定义。地址偏移量:0x8004，初值:0x00000000，宽度:32
 寄存器说明: timestamp当前计数值高位寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cntcvup_ro : 32; /* bit[0-31]: 当前计数值的bit[63:32]，只读属性 */
    } reg;
} SOC_coresightx_TSCNTCVUP_RO_UNION;
#endif
#define SOC_coresightx_TSCNTCVUP_RO_cntcvup_ro_START  (0)
#define SOC_coresightx_TSCNTCVUP_RO_cntcvup_ro_END    (31)






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

#endif /* end of soc_coresightx_interface.h */
