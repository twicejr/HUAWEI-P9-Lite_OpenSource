/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_blpwm_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:18:50
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_BLPWM.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_BLPWM_INTERFACE_H__
#define __SOC_BLPWM_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) register_blpwm
 ****************************************************************************/
/* 寄存器说明：输入控制寄存器。
   位域定义UNION结构:  SOC_BLPWM_IN_CTRL_UNION */
#define SOC_BLPWM_IN_CTRL_ADDR(base)                  ((base) + (0x000))

/* 寄存器说明：输入采样时钟分频寄存器。
   位域定义UNION结构:  SOC_BLPWM_IN_DIV_UNION */
#define SOC_BLPWM_IN_DIV_ADDR(base)                   ((base) + (0x004))

/* 寄存器说明：输入计数寄存器。
   位域定义UNION结构:  SOC_BLPWM_IN_NUM_UNION */
#define SOC_BLPWM_IN_NUM_ADDR(base)                   ((base) + (0x008))

/* 寄存器说明：计数debug寄存器。
   位域定义UNION结构:  SOC_BLPWM_IN_NUM_BAK_UNION */
#define SOC_BLPWM_IN_NUM_BAK_ADDR(base)               ((base) + (0x00C))

/* 寄存器说明：输入最大计数值寄存器。
   位域定义UNION结构:  SOC_BLPWM_CNT_MAX_UNION */
#define SOC_BLPWM_CNT_MAX_ADDR(base)                  ((base) + (0x010))

/* 寄存器说明：输入差值报警阈值寄存器。
   位域定义UNION结构:  SOC_BLPWM_INTR_DIFF_UNION */
#define SOC_BLPWM_INTR_DIFF_ADDR(base)                ((base) + (0x014))

/* 寄存器说明：中断屏蔽寄存器。
   位域定义UNION结构:  SOC_BLPWM_INTR_CTRL_UNION */
#define SOC_BLPWM_INTR_CTRL_ADDR(base)                ((base) + (0x018))

/* 寄存器说明：中断状态寄存器。
   位域定义UNION结构:  SOC_BLPWM_IN_INTR_UNION */
#define SOC_BLPWM_IN_INTR_ADDR(base)                  ((base) + (0x01C))

/* 寄存器说明：中断清除寄存器
   位域定义UNION结构:  SOC_BLPWM_INTR_CLEAR_UNION */
#define SOC_BLPWM_INTR_CLEAR_ADDR(base)               ((base) + (0x020))

/* 寄存器说明：输出模式寄存器。
   位域定义UNION结构:  SOC_BLPWM_OUT_CTRL_UNION */
#define SOC_BLPWM_OUT_CTRL_ADDR(base)                 ((base) + (0x100))

/* 寄存器说明：输出生成时钟分频比寄存器。
   位域定义UNION结构:  SOC_BLPWM_OUT_DIV_UNION */
#define SOC_BLPWM_OUT_DIV_ADDR(base)                  ((base) + (0x104))

/* 寄存器说明：输出PWM信号配置寄存器。
   位域定义UNION结构:  SOC_BLPWM_OUT_CFG_UNION */
#define SOC_BLPWM_OUT_CFG_ADDR(base)                  ((base) + (0x108))

/* 寄存器说明：输出PWM信号分组0配置寄存器。
   位域定义UNION结构:  SOC_BLPWM_GROUP0_CFG_UNION */
#define SOC_BLPWM_GROUP0_CFG_ADDR(base)               ((base) + (0x10C))

/* 寄存器说明：输出PWM信号分组1配置寄存器。
   位域定义UNION结构:  SOC_BLPWM_GROUP1_CFG_UNION */
#define SOC_BLPWM_GROUP1_CFG_ADDR(base)               ((base) + (0x110))

/* 寄存器说明：输出PWM信号分组2配置寄存器。
   位域定义UNION结构:  SOC_BLPWM_GROUP2_CFG_UNION */
#define SOC_BLPWM_GROUP2_CFG_ADDR(base)               ((base) + (0x114))

/* 寄存器说明：输出PWM信号分组3配置寄存器。
   位域定义UNION结构:  SOC_BLPWM_GROUP3_CFG_UNION */
#define SOC_BLPWM_GROUP3_CFG_ADDR(base)               ((base) + (0x118))

/* 寄存器说明：输出PWM信号分组4配置寄存器。
   位域定义UNION结构:  SOC_BLPWM_GROUP4_CFG_UNION */
#define SOC_BLPWM_GROUP4_CFG_ADDR(base)               ((base) + (0x11C))

/* 寄存器说明：输出PWM信号分组5配置寄存器。
   位域定义UNION结构:  SOC_BLPWM_GROUP5_CFG_UNION */
#define SOC_BLPWM_GROUP5_CFG_ADDR(base)               ((base) + (0x120))

/* 寄存器说明：输出PWM信号分组6配置寄存器。
   位域定义UNION结构:  SOC_BLPWM_GROUP6_CFG_UNION */
#define SOC_BLPWM_GROUP6_CFG_ADDR(base)               ((base) + (0x124))

/* 寄存器说明：输出PWM信号分组7配置寄存器。
   位域定义UNION结构:  SOC_BLPWM_GROUP7_CFG_UNION */
#define SOC_BLPWM_GROUP7_CFG_ADDR(base)               ((base) + (0x128))

/* 寄存器说明：输出工作状态寄存器。
   位域定义UNION结构:  SOC_BLPWM_OUT_STATUS_UNION */
#define SOC_BLPWM_OUT_STATUS_ADDR(base)               ((base) + (0x130))

/* 寄存器说明：分组状态寄存器。
   位域定义UNION结构:  SOC_BLPWM_GROUP_STATUS_UNION */
#define SOC_BLPWM_GROUP_STATUS_ADDR(base)             ((base) + (0x134))





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
                     (1/1) register_blpwm
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_BLPWM_IN_CTRL_UNION
 结构说明  : IN_CTRL 寄存器结构定义。地址偏移量:0x000，初值:0x00000000，宽度:32
 寄存器说明: 输入控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cnt_enable    : 1;  /* bit[0]    : 计数使能，1使能计数，0停止计数。 */
        unsigned int  reserved_0    : 15; /* bit[1-15] : 保留。 */
        unsigned int  input_reverse : 1;  /* bit[16]   : 输入反向使能，即输入的cabc_pwm信号为低有效。 */
        unsigned int  reserved_1    : 15; /* bit[17-31]: 保留。 */
    } reg;
} SOC_BLPWM_IN_CTRL_UNION;
#endif
#define SOC_BLPWM_IN_CTRL_cnt_enable_START     (0)
#define SOC_BLPWM_IN_CTRL_cnt_enable_END       (0)
#define SOC_BLPWM_IN_CTRL_input_reverse_START  (16)
#define SOC_BLPWM_IN_CTRL_input_reverse_END    (16)


/*****************************************************************************
 结构名    : SOC_BLPWM_IN_DIV_UNION
 结构说明  : IN_DIV 寄存器结构定义。地址偏移量:0x004，初值:0x00000000，宽度:32
 寄存器说明: 输入采样时钟分频寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cnt_div  : 8;  /* bit[0-7] : 采样时钟分频比，0为1分频，1为2分频，以此类推。 */
        unsigned int  reserved : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_BLPWM_IN_DIV_UNION;
#endif
#define SOC_BLPWM_IN_DIV_cnt_div_START   (0)
#define SOC_BLPWM_IN_DIV_cnt_div_END     (7)


/*****************************************************************************
 结构名    : SOC_BLPWM_IN_NUM_UNION
 结构说明  : IN_NUM 寄存器结构定义。地址偏移量:0x008，初值:0x00000000，宽度:32
 寄存器说明: 输入计数寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cnt_low  : 16; /* bit[0-15] : 输入计数寄存器, 刚结束的周期的低电平周期数。 */
        unsigned int  cnt_high : 16; /* bit[16-31]: 输入计数寄存器, 刚结束的周期的高电平周期数。 */
    } reg;
} SOC_BLPWM_IN_NUM_UNION;
#endif
#define SOC_BLPWM_IN_NUM_cnt_low_START   (0)
#define SOC_BLPWM_IN_NUM_cnt_low_END     (15)
#define SOC_BLPWM_IN_NUM_cnt_high_START  (16)
#define SOC_BLPWM_IN_NUM_cnt_high_END    (31)


/*****************************************************************************
 结构名    : SOC_BLPWM_IN_NUM_BAK_UNION
 结构说明  : IN_NUM_BAK 寄存器结构定义。地址偏移量:0x00C，初值:0x00000000，宽度:32
 寄存器说明: 计数debug寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cnt_low_debug  : 16; /* bit[0-15] : 输入debug寄存器,上一个pwm周期的低电平周期数。 */
        unsigned int  cnt_high_debug : 16; /* bit[16-31]: 输入debug寄存器,上一个pwm周期的高电平周期数。 */
    } reg;
} SOC_BLPWM_IN_NUM_BAK_UNION;
#endif
#define SOC_BLPWM_IN_NUM_BAK_cnt_low_debug_START   (0)
#define SOC_BLPWM_IN_NUM_BAK_cnt_low_debug_END     (15)
#define SOC_BLPWM_IN_NUM_BAK_cnt_high_debug_START  (16)
#define SOC_BLPWM_IN_NUM_BAK_cnt_high_debug_END    (31)


/*****************************************************************************
 结构名    : SOC_BLPWM_CNT_MAX_UNION
 结构说明  : CNT_MAX 寄存器结构定义。地址偏移量:0x010，初值:0x0000FFFF，宽度:32
 寄存器说明: 输入最大计数值寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cnt_max  : 16; /* bit[0-15] : 最大的计数值，超过此值结束当前计数，切换到下一组。 */
        unsigned int  reserved : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_BLPWM_CNT_MAX_UNION;
#endif
#define SOC_BLPWM_CNT_MAX_cnt_max_START   (0)
#define SOC_BLPWM_CNT_MAX_cnt_max_END     (15)


/*****************************************************************************
 结构名    : SOC_BLPWM_INTR_DIFF_UNION
 结构说明  : INTR_DIFF 寄存器结构定义。地址偏移量:0x014，初值:0x00000000，宽度:32
 寄存器说明: 输入差值报警阈值寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cnt_intr_diff : 16; /* bit[0-15] : 当前后两次计数值的高电平差值达到此阈值时，产生中断。 */
        unsigned int  reserved      : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_BLPWM_INTR_DIFF_UNION;
#endif
#define SOC_BLPWM_INTR_DIFF_cnt_intr_diff_START  (0)
#define SOC_BLPWM_INTR_DIFF_cnt_intr_diff_END    (15)


/*****************************************************************************
 结构名    : SOC_BLPWM_INTR_CTRL_UNION
 结构说明  : INTR_CTRL 寄存器结构定义。地址偏移量:0x018，初值:0x00000000，宽度:32
 寄存器说明: 中断屏蔽寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cnt_intr_mask : 1;  /* bit[0]   : 中断屏蔽，为1时屏蔽该中断。 */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_BLPWM_INTR_CTRL_UNION;
#endif
#define SOC_BLPWM_INTR_CTRL_cnt_intr_mask_START  (0)
#define SOC_BLPWM_INTR_CTRL_cnt_intr_mask_END    (0)


/*****************************************************************************
 结构名    : SOC_BLPWM_IN_INTR_UNION
 结构说明  : IN_INTR 寄存器结构定义。地址偏移量:0x01C，初值:0x00000000，宽度:32
 寄存器说明: 中断状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cnt_raw_intr : 1;  /* bit[0]    : 原始中断，高有效。 */
        unsigned int  reserved_0   : 15; /* bit[1-15] : 保留。 */
        unsigned int  cnt_intr     : 1;  /* bit[16]   : 屏蔽后中断，高有效。 */
        unsigned int  reserved_1   : 15; /* bit[17-31]: 保留。 */
    } reg;
} SOC_BLPWM_IN_INTR_UNION;
#endif
#define SOC_BLPWM_IN_INTR_cnt_raw_intr_START  (0)
#define SOC_BLPWM_IN_INTR_cnt_raw_intr_END    (0)
#define SOC_BLPWM_IN_INTR_cnt_intr_START      (16)
#define SOC_BLPWM_IN_INTR_cnt_intr_END        (16)


/*****************************************************************************
 结构名    : SOC_BLPWM_INTR_CLEAR_UNION
 结构说明  : INTR_CLEAR 寄存器结构定义。地址偏移量:0x020，初值:0x0000，宽度:32
 寄存器说明: 中断清除寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cnt_intr_clear : 1;  /* bit[0]   : 中断清除寄存器，清除中断时对该位写1，中断清除后该位自动恢复为零。 */
        unsigned int  reserved       : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_BLPWM_INTR_CLEAR_UNION;
#endif
#define SOC_BLPWM_INTR_CLEAR_cnt_intr_clear_START  (0)
#define SOC_BLPWM_INTR_CLEAR_cnt_intr_clear_END    (0)


/*****************************************************************************
 结构名    : SOC_BLPWM_OUT_CTRL_UNION
 结构说明  : OUT_CTRL 寄存器结构定义。地址偏移量:0x100，初值:0x00000004，宽度:32
 寄存器说明: 输出模式寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gen_en      : 1;  /* bit[0]   : 0：停止产生输出信号，输出bl_pwm为0.
                                                      1：输出使能；  */
        unsigned int  gen_mode    : 1;  /* bit[1]   : 输出模式选择寄存器。
                                                      0：分组配置模式；
                                                      1：直通模式。 */
        unsigned int  bypass_mode : 1;  /* bit[2]   : bypass模式，即可以将输入不通过计数模块直接作为bl_pwm输出。复位值为1。当gen_en=0且bypass_mode=1时进入此模式。 */
        unsigned int  reserved    : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_BLPWM_OUT_CTRL_UNION;
#endif
#define SOC_BLPWM_OUT_CTRL_gen_en_START       (0)
#define SOC_BLPWM_OUT_CTRL_gen_en_END         (0)
#define SOC_BLPWM_OUT_CTRL_gen_mode_START     (1)
#define SOC_BLPWM_OUT_CTRL_gen_mode_END       (1)
#define SOC_BLPWM_OUT_CTRL_bypass_mode_START  (2)
#define SOC_BLPWM_OUT_CTRL_bypass_mode_END    (2)


/*****************************************************************************
 结构名    : SOC_BLPWM_OUT_DIV_UNION
 结构说明  : OUT_DIV 寄存器结构定义。地址偏移量:0x104，初值:0x00000000，宽度:32
 寄存器说明: 输出生成时钟分频比寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gen_cnt_div : 8;  /* bit[0-7] : 输出产生时钟分频比。0为1分频，1为2分频，以此类推。 */
        unsigned int  reserved    : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_BLPWM_OUT_DIV_UNION;
#endif
#define SOC_BLPWM_OUT_DIV_gen_cnt_div_START  (0)
#define SOC_BLPWM_OUT_DIV_gen_cnt_div_END    (7)


/*****************************************************************************
 结构名    : SOC_BLPWM_OUT_CFG_UNION
 结构说明  : OUT_CFG 寄存器结构定义。地址偏移量:0x108，初值:0x00000000，宽度:32
 寄存器说明: 输出PWM信号配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  start_low  : 16; /* bit[0-15] : 配置分组模式的起始低电平周期数。为0时表示一个pwm周期内不产生低电平。 */
        unsigned int  start_high : 16; /* bit[16-31]: 配置分组模式的起始高电平周期数。为0时表示一个pwm周期内不产生高电平。 */
    } reg;
} SOC_BLPWM_OUT_CFG_UNION;
#endif
#define SOC_BLPWM_OUT_CFG_start_low_START   (0)
#define SOC_BLPWM_OUT_CFG_start_low_END     (15)
#define SOC_BLPWM_OUT_CFG_start_high_START  (16)
#define SOC_BLPWM_OUT_CFG_start_high_END    (31)


/*****************************************************************************
 结构名    : SOC_BLPWM_GROUP0_CFG_UNION
 结构说明  : GROUP0_CFG 寄存器结构定义。地址偏移量:0x10C，初值:0x00000000，宽度:32
 寄存器说明: 输出PWM信号分组0配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  group0_refresh_freq : 8;  /* bit[0-7]  : 刷新频率，即每多少个周期使用下一个配置值。为0时表示每个值仅执行一次，为1时两次，以此类推。 */
        unsigned int  group0_step_times   : 8;  /* bit[8-15] : 步长的加/减次数。0时为加一次，1时加两次，以此类推。 */
        unsigned int  group0_step         : 15; /* bit[16-30]: 步长，15位有符号数。 */
        unsigned int  group0_active       : 1;  /* bit[31]   : 表示是否进行本组配置，为0时不进行此组操作和后续的分组操作。在初始时，只有分组0此寄存器有效时，才会进行分组加减的配置。 */
    } reg;
} SOC_BLPWM_GROUP0_CFG_UNION;
#endif
#define SOC_BLPWM_GROUP0_CFG_group0_refresh_freq_START  (0)
#define SOC_BLPWM_GROUP0_CFG_group0_refresh_freq_END    (7)
#define SOC_BLPWM_GROUP0_CFG_group0_step_times_START    (8)
#define SOC_BLPWM_GROUP0_CFG_group0_step_times_END      (15)
#define SOC_BLPWM_GROUP0_CFG_group0_step_START          (16)
#define SOC_BLPWM_GROUP0_CFG_group0_step_END            (30)
#define SOC_BLPWM_GROUP0_CFG_group0_active_START        (31)
#define SOC_BLPWM_GROUP0_CFG_group0_active_END          (31)


/*****************************************************************************
 结构名    : SOC_BLPWM_GROUP1_CFG_UNION
 结构说明  : GROUP1_CFG 寄存器结构定义。地址偏移量:0x110，初值:0x00000000，宽度:32
 寄存器说明: 输出PWM信号分组1配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  group1_refresh_freq : 8;  /* bit[0-7]  : 刷新频率，即每多少个周期使用下一个配置值。 */
        unsigned int  group1_step_times   : 8;  /* bit[8-15] : 步长的加/减次数。0时为加一次，1时加两次，以此类推。 */
        unsigned int  group1_step         : 15; /* bit[16-30]: 步长，15位有符号数。 */
        unsigned int  group1_active       : 1;  /* bit[31]   : 表示是否进行本组配置，为0时不进行此组操作和后续的分组操作，循环使用最后一个高低电平的配置输出bl_pwm。 */
    } reg;
} SOC_BLPWM_GROUP1_CFG_UNION;
#endif
#define SOC_BLPWM_GROUP1_CFG_group1_refresh_freq_START  (0)
#define SOC_BLPWM_GROUP1_CFG_group1_refresh_freq_END    (7)
#define SOC_BLPWM_GROUP1_CFG_group1_step_times_START    (8)
#define SOC_BLPWM_GROUP1_CFG_group1_step_times_END      (15)
#define SOC_BLPWM_GROUP1_CFG_group1_step_START          (16)
#define SOC_BLPWM_GROUP1_CFG_group1_step_END            (30)
#define SOC_BLPWM_GROUP1_CFG_group1_active_START        (31)
#define SOC_BLPWM_GROUP1_CFG_group1_active_END          (31)


/*****************************************************************************
 结构名    : SOC_BLPWM_GROUP2_CFG_UNION
 结构说明  : GROUP2_CFG 寄存器结构定义。地址偏移量:0x114，初值:0x00000000，宽度:32
 寄存器说明: 输出PWM信号分组2配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  group2_refresh_freq : 8;  /* bit[0-7]  : 刷新频率，即每多少个周期使用下一个配置值。 */
        unsigned int  group2_step_times   : 8;  /* bit[8-15] : 步长的加/减次数。0时为加一次，1时加两次，以此类推。 */
        unsigned int  group2_step         : 15; /* bit[16-30]: 步长，15位有符号数。 */
        unsigned int  group2_active       : 1;  /* bit[31]   : 表示是否进行本组配置，为0时不进行此组操作和后续的分组操作，循环使用最后一个高低电平的配置输出bl_pwm。 */
    } reg;
} SOC_BLPWM_GROUP2_CFG_UNION;
#endif
#define SOC_BLPWM_GROUP2_CFG_group2_refresh_freq_START  (0)
#define SOC_BLPWM_GROUP2_CFG_group2_refresh_freq_END    (7)
#define SOC_BLPWM_GROUP2_CFG_group2_step_times_START    (8)
#define SOC_BLPWM_GROUP2_CFG_group2_step_times_END      (15)
#define SOC_BLPWM_GROUP2_CFG_group2_step_START          (16)
#define SOC_BLPWM_GROUP2_CFG_group2_step_END            (30)
#define SOC_BLPWM_GROUP2_CFG_group2_active_START        (31)
#define SOC_BLPWM_GROUP2_CFG_group2_active_END          (31)


/*****************************************************************************
 结构名    : SOC_BLPWM_GROUP3_CFG_UNION
 结构说明  : GROUP3_CFG 寄存器结构定义。地址偏移量:0x118，初值:0x00000000，宽度:32
 寄存器说明: 输出PWM信号分组3配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  group3_refresh_freq : 8;  /* bit[0-7]  : 刷新频率，即每多少个周期使用下一个配置值。 */
        unsigned int  group3_step_times   : 8;  /* bit[8-15] : 步长的加/减次数。 */
        unsigned int  group3_step         : 15; /* bit[16-30]: 步长，15位有符号数。 */
        unsigned int  group3_active       : 1;  /* bit[31]   : 表示是否进行本组配置，为0时不进行此组操作和后续的分组操作，循环使用最后一个高低电平的配置输出bl_pwm。 */
    } reg;
} SOC_BLPWM_GROUP3_CFG_UNION;
#endif
#define SOC_BLPWM_GROUP3_CFG_group3_refresh_freq_START  (0)
#define SOC_BLPWM_GROUP3_CFG_group3_refresh_freq_END    (7)
#define SOC_BLPWM_GROUP3_CFG_group3_step_times_START    (8)
#define SOC_BLPWM_GROUP3_CFG_group3_step_times_END      (15)
#define SOC_BLPWM_GROUP3_CFG_group3_step_START          (16)
#define SOC_BLPWM_GROUP3_CFG_group3_step_END            (30)
#define SOC_BLPWM_GROUP3_CFG_group3_active_START        (31)
#define SOC_BLPWM_GROUP3_CFG_group3_active_END          (31)


/*****************************************************************************
 结构名    : SOC_BLPWM_GROUP4_CFG_UNION
 结构说明  : GROUP4_CFG 寄存器结构定义。地址偏移量:0x11C，初值:0x00000000，宽度:32
 寄存器说明: 输出PWM信号分组4配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  group4_refresh_freq : 8;  /* bit[0-7]  : 刷新频率，即每多少个周期使用下一个配置值。 */
        unsigned int  group4_step_times   : 8;  /* bit[8-15] : 步长的加/减次数。0时为加一次，1时加两次，以此类推。 */
        unsigned int  group4_step         : 15; /* bit[16-30]: 步长，15位有符号数。 */
        unsigned int  group4_active       : 1;  /* bit[31]   : 表示是否进行本组配置，为0时不进行此组操作和后续的分组操作，循环使用最后一个高低电平的配置输出bl_pwm。 */
    } reg;
} SOC_BLPWM_GROUP4_CFG_UNION;
#endif
#define SOC_BLPWM_GROUP4_CFG_group4_refresh_freq_START  (0)
#define SOC_BLPWM_GROUP4_CFG_group4_refresh_freq_END    (7)
#define SOC_BLPWM_GROUP4_CFG_group4_step_times_START    (8)
#define SOC_BLPWM_GROUP4_CFG_group4_step_times_END      (15)
#define SOC_BLPWM_GROUP4_CFG_group4_step_START          (16)
#define SOC_BLPWM_GROUP4_CFG_group4_step_END            (30)
#define SOC_BLPWM_GROUP4_CFG_group4_active_START        (31)
#define SOC_BLPWM_GROUP4_CFG_group4_active_END          (31)


/*****************************************************************************
 结构名    : SOC_BLPWM_GROUP5_CFG_UNION
 结构说明  : GROUP5_CFG 寄存器结构定义。地址偏移量:0x120，初值:0x00000000，宽度:32
 寄存器说明: 输出PWM信号分组5配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  group5_refresh_freq : 8;  /* bit[0-7]  : 刷新频率，即每多少个周期使用下一个配置值。 */
        unsigned int  group5_step_times   : 8;  /* bit[8-15] : 步长的加/减次数。0时为加一次，1时加两次，以此类推。 */
        unsigned int  group5_step         : 15; /* bit[16-30]: 步长，15位有符号数。 */
        unsigned int  group5_active       : 1;  /* bit[31]   : 表示是否进行本组配置，为0时不进行此组操作，循环使用最后一个配置数。 */
    } reg;
} SOC_BLPWM_GROUP5_CFG_UNION;
#endif
#define SOC_BLPWM_GROUP5_CFG_group5_refresh_freq_START  (0)
#define SOC_BLPWM_GROUP5_CFG_group5_refresh_freq_END    (7)
#define SOC_BLPWM_GROUP5_CFG_group5_step_times_START    (8)
#define SOC_BLPWM_GROUP5_CFG_group5_step_times_END      (15)
#define SOC_BLPWM_GROUP5_CFG_group5_step_START          (16)
#define SOC_BLPWM_GROUP5_CFG_group5_step_END            (30)
#define SOC_BLPWM_GROUP5_CFG_group5_active_START        (31)
#define SOC_BLPWM_GROUP5_CFG_group5_active_END          (31)


/*****************************************************************************
 结构名    : SOC_BLPWM_GROUP6_CFG_UNION
 结构说明  : GROUP6_CFG 寄存器结构定义。地址偏移量:0x124，初值:0x00000000，宽度:32
 寄存器说明: 输出PWM信号分组6配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  group6_refresh_freq : 8;  /* bit[0-7]  : 刷新频率，即每多少个周期使用下一个配置值。 */
        unsigned int  group6_step_times   : 8;  /* bit[8-15] : 步长的加/减次数。0时为加一次，1时加两次，以此类推。 */
        unsigned int  group6_step         : 15; /* bit[16-30]: 步长，15位有符号数。 */
        unsigned int  group6_active       : 1;  /* bit[31]   : 表示是否进行本组配置，为0时不进行此组操作和后续的分组操作，循环使用最后一个高低电平的配置输出bl_pwm。 */
    } reg;
} SOC_BLPWM_GROUP6_CFG_UNION;
#endif
#define SOC_BLPWM_GROUP6_CFG_group6_refresh_freq_START  (0)
#define SOC_BLPWM_GROUP6_CFG_group6_refresh_freq_END    (7)
#define SOC_BLPWM_GROUP6_CFG_group6_step_times_START    (8)
#define SOC_BLPWM_GROUP6_CFG_group6_step_times_END      (15)
#define SOC_BLPWM_GROUP6_CFG_group6_step_START          (16)
#define SOC_BLPWM_GROUP6_CFG_group6_step_END            (30)
#define SOC_BLPWM_GROUP6_CFG_group6_active_START        (31)
#define SOC_BLPWM_GROUP6_CFG_group6_active_END          (31)


/*****************************************************************************
 结构名    : SOC_BLPWM_GROUP7_CFG_UNION
 结构说明  : GROUP7_CFG 寄存器结构定义。地址偏移量:0x128，初值:0x00000000，宽度:32
 寄存器说明: 输出PWM信号分组7配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  group7_refresh_freq : 8;  /* bit[0-7]  : 刷新频率，即每多少个周期使用下一个配置值。 */
        unsigned int  group7_step_times   : 8;  /* bit[8-15] : 步长的加/减次数。0时为加一次，1时加两次，以此类推。 */
        unsigned int  group7_step         : 15; /* bit[16-30]: 步长，15位有符号数。 */
        unsigned int  group7_active       : 1;  /* bit[31]   : 表示是否进行本组配置，为0时不进行此组操作和后续的分组操作，循环使用最后一个高低电平的配置输出bl_pwm。 */
    } reg;
} SOC_BLPWM_GROUP7_CFG_UNION;
#endif
#define SOC_BLPWM_GROUP7_CFG_group7_refresh_freq_START  (0)
#define SOC_BLPWM_GROUP7_CFG_group7_refresh_freq_END    (7)
#define SOC_BLPWM_GROUP7_CFG_group7_step_times_START    (8)
#define SOC_BLPWM_GROUP7_CFG_group7_step_times_END      (15)
#define SOC_BLPWM_GROUP7_CFG_group7_step_START          (16)
#define SOC_BLPWM_GROUP7_CFG_group7_step_END            (30)
#define SOC_BLPWM_GROUP7_CFG_group7_active_START        (31)
#define SOC_BLPWM_GROUP7_CFG_group7_active_END          (31)


/*****************************************************************************
 结构名    : SOC_BLPWM_OUT_STATUS_UNION
 结构说明  : OUT_STATUS 寄存器结构定义。地址偏移量:0x130，初值:0x00000000，宽度:32
 寄存器说明: 输出工作状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gen_low  : 16; /* bit[0-15] : 分组模式输出时，当前pwm信号的低电平周期数。 */
        unsigned int  gen_high : 16; /* bit[16-31]: 分组模式输出时，当前pwm信号的高电平周期数。 */
    } reg;
} SOC_BLPWM_OUT_STATUS_UNION;
#endif
#define SOC_BLPWM_OUT_STATUS_gen_low_START   (0)
#define SOC_BLPWM_OUT_STATUS_gen_low_END     (15)
#define SOC_BLPWM_OUT_STATUS_gen_high_START  (16)
#define SOC_BLPWM_OUT_STATUS_gen_high_END    (31)


/*****************************************************************************
 结构名    : SOC_BLPWM_GROUP_STATUS_UNION
 结构说明  : GROUP_STATUS 寄存器结构定义。地址偏移量:0x134，初值:0x00000000，宽度:32
 寄存器说明: 分组状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gen_num          : 3;  /* bit[0-2]  : 分组输出时，当前进行配置的组数。 */
        unsigned int  reserved_0       : 13; /* bit[3-15] : 保留 */
        unsigned int  group_over       : 1;  /* bit[16]   : 分组配置完成。 */
        unsigned int  group_inprogress : 1;  /* bit[17]   : 正在进行分组的加减操作。 */
        unsigned int  reserved_1       : 14; /* bit[18-31]: 保留。 */
    } reg;
} SOC_BLPWM_GROUP_STATUS_UNION;
#endif
#define SOC_BLPWM_GROUP_STATUS_gen_num_START           (0)
#define SOC_BLPWM_GROUP_STATUS_gen_num_END             (2)
#define SOC_BLPWM_GROUP_STATUS_group_over_START        (16)
#define SOC_BLPWM_GROUP_STATUS_group_over_END          (16)
#define SOC_BLPWM_GROUP_STATUS_group_inprogress_START  (17)
#define SOC_BLPWM_GROUP_STATUS_group_inprogress_END    (17)






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

#endif /* end of soc_blpwm_interface.h */
