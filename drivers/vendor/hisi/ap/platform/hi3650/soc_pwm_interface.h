/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_pwm_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-04-08 11:47:42
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年4月8日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_PWM.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_PWM_INTERFACE_H__
#define __SOC_PWM_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) register_define
 ****************************************************************************/
/* 寄存器说明：pwm_lock寄存器。
   位域定义UNION结构:  SOC_PWM__LOCK_UNION */
#define SOC_PWM__LOCK_ADDR(base)                      ((base) + (0x000))

/* 寄存器说明：pwm控制寄存器。
   位域定义UNION结构:  SOC_PWM_CTL_UNION */
#define SOC_PWM_CTL_ADDR(base)                        ((base) + (0x004))

/* 寄存器说明：PWM配置寄存器。
   位域定义UNION结构:  SOC_PWM_CFG_UNION */
#define SOC_PWM_CFG_ADDR(base)                        ((base) + (0x0008))

/* 寄存器说明：PWM预分频0寄存器。
   位域定义UNION结构:  SOC_PWM_PR0_UNION */
#define SOC_PWM_PR0_ADDR(base)                        ((base) + (0x0100))

/* 寄存器说明：PWM预分频1寄存器。
   位域定义UNION结构:  SOC_PWM_PR1_UNION */
#define SOC_PWM_PR1_ADDR(base)                        ((base) + (0x0104))

/* 寄存器说明：PWM预分频0计数寄存器。
   位域定义UNION结构:  SOC_PWM_PCNT0_UNION */
#define SOC_PWM_PCNT0_ADDR(base)                      ((base) + (0x0108))

/* 寄存器说明：PWM预分频1计数寄存器。
   位域定义UNION结构:  SOC_PWM_PCNT1_UNION */
#define SOC_PWM_PCNT1_ADDR(base)                      ((base) + (0x010C))

/* 寄存器说明：PWM周期匹配寄存器。
   位域定义UNION结构:  SOC_PWM_C0_MR_UNION */
#define SOC_PWM_C0_MR_ADDR(base)                      ((base) + (0x0300))

/* 寄存器说明：PWM周期匹配寄存器。
   位域定义UNION结构:  SOC_PWM_C1_MR_UNION */
#define SOC_PWM_C1_MR_ADDR(base)                      ((base) + (0x0400))

/* 寄存器说明：PWM周期匹配寄存器。
   位域定义UNION结构:  SOC_PWM_C0_MR0_UNION */
#define SOC_PWM_C0_MR0_ADDR(base)                     ((base) + (0x0304))

/* 寄存器说明：PWM周期匹配寄存器。
   位域定义UNION结构:  SOC_PWM_C1_MR0_UNION */
#define SOC_PWM_C1_MR0_ADDR(base)                     ((base) + (0x0404))

/* 寄存器说明：PWM周期匹配寄存器。
   位域定义UNION结构:  SOC_PWM_C0_MR1_UNION */
#define SOC_PWM_C0_MR1_ADDR(base)                     ((base) + (0x0308))

/* 寄存器说明：PWM周期匹配寄存器。
   位域定义UNION结构:  SOC_PWM_C1_MR1_UNION */
#define SOC_PWM_C1_MR1_ADDR(base)                     ((base) + (0x0408))

/* 寄存器说明：PWM通道0的定时器寄存器。
   位域定义UNION结构:  SOC_PWM_C0_TCNT_UNION */
#define SOC_PWM_C0_TCNT_ADDR(base)                    ((base) + (0x030C))

/* 寄存器说明：PWM通道1的定时器寄存器。
   位域定义UNION结构:  SOC_PWM_C1_TCNT_UNION */
#define SOC_PWM_C1_TCNT_ADDR(base)                    ((base) + (0x040C))

/* 寄存器说明：PWM脉冲相位设置寄存器。
   位域定义UNION结构:  SOC_PWM_C0_PHA_UNION */
#define SOC_PWM_C0_PHA_ADDR(base)                     ((base) + (0x0310))

/* 寄存器说明：PWM脉冲相位设置寄存器。
   位域定义UNION结构:  SOC_PWM_C1_PHA_UNION */
#define SOC_PWM_C1_PHA_ADDR(base)                     ((base) + (0x0410))





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
                     (1/1) register_define
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_PWM__LOCK_UNION
 结构说明  : _LOCK 寄存器结构定义。地址偏移量:0x000，初值:0x00000001，宽度:32
 寄存器说明: pwm_lock寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pwm_lock : 32; /* bit[0-31]: pwm_lock寄存器，当向该地址写入0x1ACC_E551(该值宏定义可配，配置范围为32'h00000000~32'hffffffff)时，pwm_lock为1'b0,解锁可以配置所有寄存器；当向该寄存器写入其他值时，pwm_lock为1'b1，只能配置lock寄存器。 */
    } reg;
} SOC_PWM__LOCK_UNION;
#endif
#define SOC_PWM__LOCK_pwm_lock_START  (0)
#define SOC_PWM__LOCK_pwm_lock_END    (31)


/*****************************************************************************
 结构名    : SOC_PWM_CTL_UNION
 结构说明  : CTL 寄存器结构定义。地址偏移量:0x004，初值:0x00000000，宽度:32
 寄存器说明: pwm控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pwm_en   : 1;  /* bit[0]   : 模块使能信号，高有效，使能和模块计数功能有关，输出pwm_out保持为关闭时状态。
                                                   0：PWM未使能；
                                                   1：PWM使能；
                                                   注：pwm_en配置为0关闭，pwm_out也会立即关闭无效。 */
        unsigned int  pwm_rst  : 1;  /* bit[1]   : 软复位，高有效
                                                   0：软复位无效；
                                                   1：软复位有效；
                                                   注：配置1次的有效时间为1个cycle，然后自动清零。 */
        unsigned int  reserved : 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_PWM_CTL_UNION;
#endif
#define SOC_PWM_CTL_pwm_en_START    (0)
#define SOC_PWM_CTL_pwm_en_END      (0)
#define SOC_PWM_CTL_pwm_rst_START   (1)
#define SOC_PWM_CTL_pwm_rst_END     (1)


/*****************************************************************************
 结构名    : SOC_PWM_CFG_UNION
 结构说明  : CFG 寄存器结构定义。地址偏移量:0x0008，初值:0x00000000，宽度:32
 寄存器说明: PWM配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pwm_mode_0 : 1;  /* bit[0]   : 通道0的边沿方式选择信号
                                                     0：单边沿方式；
                                                     1：双边沿方式； */
        unsigned int  pwm_oen_0  : 1;  /* bit[1]   : 通道0的PWM波形输出控制信号（备注：在我们芯片应用中不会用到三态模式，复位后初始化寄存器列表时候将该比特拉高，之后不能再做改变，即永远处于输出PWM模式）
                                                     0：输出三态；
                                                     1：输出PWM波形； */
        unsigned int  pwm_mode_1 : 1;  /* bit[2]   : 通道1的边沿方式选择信号
                                                     0：单边沿方式；
                                                     1：双边沿方式； */
        unsigned int  pwm_oen_1  : 1;  /* bit[3]   : 通道1的PWM波形输出控制信号（备注：在我们芯片应用中不会用到三态模式，复位后初始化寄存器列表时候将该比特拉高，之后不能再做改变，即永远处于输出PWM模式）
                                                     0：输出三态；
                                                     1：输出PWM波形； */
        unsigned int  reserved   : 28; /* bit[4-31]: 保留。 */
    } reg;
} SOC_PWM_CFG_UNION;
#endif
#define SOC_PWM_CFG_pwm_mode_0_START  (0)
#define SOC_PWM_CFG_pwm_mode_0_END    (0)
#define SOC_PWM_CFG_pwm_oen_0_START   (1)
#define SOC_PWM_CFG_pwm_oen_0_END     (1)
#define SOC_PWM_CFG_pwm_mode_1_START  (2)
#define SOC_PWM_CFG_pwm_mode_1_END    (2)
#define SOC_PWM_CFG_pwm_oen_1_START   (3)
#define SOC_PWM_CFG_pwm_oen_1_END     (3)


/*****************************************************************************
 结构名    : SOC_PWM_PR0_UNION
 结构说明  : PR0 寄存器结构定义。地址偏移量:0x0100，初值:0x00000000，宽度:32
 寄存器说明: PWM预分频0寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pwm_pr0  : 16; /* bit[0-15] : 用来记录脉冲调制的预分频0值得大小。
                                                    注：该寄存器配置的值，只有在pwm_en有从0到1的过程，该配置值才会实际生效，否则实际使用的为原值进行分频。 */
        unsigned int  reserved : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_PWM_PR0_UNION;
#endif
#define SOC_PWM_PR0_pwm_pr0_START   (0)
#define SOC_PWM_PR0_pwm_pr0_END     (15)


/*****************************************************************************
 结构名    : SOC_PWM_PR1_UNION
 结构说明  : PR1 寄存器结构定义。地址偏移量:0x0104，初值:0x00000000，宽度:32
 寄存器说明: PWM预分频1寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pwm_pr1  : 16; /* bit[0-15] : 用来记录脉冲调制的预分频1值得大小。
                                                    注：见PWM_PR0 */
        unsigned int  reserved : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_PWM_PR1_UNION;
#endif
#define SOC_PWM_PR1_pwm_pr1_START   (0)
#define SOC_PWM_PR1_pwm_pr1_END     (15)


/*****************************************************************************
 结构名    : SOC_PWM_PCNT0_UNION
 结构说明  : PCNT0 寄存器结构定义。地址偏移量:0x0108，初值:0x00000000，宽度:32
 寄存器说明: PWM预分频0计数寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pwm_pcnt1 : 16; /* bit[0-15] : 全局复位或者软复位时，寄存器初始化；当PWM模块使能信号有效时，计数器自加1；当计数器匹配预分频0值时，赋值0，此寄存器位宽1~32宏定义`PWM_PR_WIDTH可配，可通过宏定义`PWM_INCLUDE_DE进行关闭。
                                                     注：当pwm_en从关闭再到重新开启，需要进行全局复位或者软复位操作。否则该寄存器残留的计数值(前次pwm_en有效时)，会影响当前pwm_en有效时pwm_out的输出。 */
        unsigned int  reserved  : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_PWM_PCNT0_UNION;
#endif
#define SOC_PWM_PCNT0_pwm_pcnt1_START  (0)
#define SOC_PWM_PCNT0_pwm_pcnt1_END    (15)


/*****************************************************************************
 结构名    : SOC_PWM_PCNT1_UNION
 结构说明  : PCNT1 寄存器结构定义。地址偏移量:0x010C，初值:0x00000000，宽度:32
 寄存器说明: PWM预分频1计数寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pwm_pcnt1 : 16; /* bit[0-15] : 全局复位或者软复位时，寄存器初始化；当PWM模块使能信号有效时，计数器自加1；当计数器匹配预分频0值时，赋值0，此寄存器位宽1~32宏定义`PWM_PR_WIDTH可配，可通过宏定义`PWM_INCLUDE_DE进行关闭。
                                                     注：见PWM_PCNT0 */
        unsigned int  reserved  : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_PWM_PCNT1_UNION;
#endif
#define SOC_PWM_PCNT1_pwm_pcnt1_START  (0)
#define SOC_PWM_PCNT1_pwm_pcnt1_END    (15)


/*****************************************************************************
 结构名    : SOC_PWM_C0_MR_UNION
 结构说明  : C0_MR 寄存器结构定义。地址偏移量:0x0300，初值:0x00000000，宽度:32
 寄存器说明: PWM周期匹配寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pwm_c0_mr : 32; /* bit[0-31]: 用来记录通道0的匹配寄存器的值。
                                                    匹配通道0的周期cycle数，该cycle指经过预分频，周期为该数值+1.
                                                    注：该寄存器配置的值，只有在pwm_en有从0到1的过程，该配置值才会实际生效，否则实际使用的为原值。 */
    } reg;
} SOC_PWM_C0_MR_UNION;
#endif
#define SOC_PWM_C0_MR_pwm_c0_mr_START  (0)
#define SOC_PWM_C0_MR_pwm_c0_mr_END    (31)


/*****************************************************************************
 结构名    : SOC_PWM_C1_MR_UNION
 结构说明  : C1_MR 寄存器结构定义。地址偏移量:0x0400，初值:0x00000000，宽度:32
 寄存器说明: PWM周期匹配寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pwm_c1_mr : 32; /* bit[0-31]: 用来记录通道1的匹配寄存器的值。
                                                    匹配通道1的周期cycle数，该cycle指经过预分频，周期为该数值+1.
                                                    注：见PWM_C0_MR */
    } reg;
} SOC_PWM_C1_MR_UNION;
#endif
#define SOC_PWM_C1_MR_pwm_c1_mr_START  (0)
#define SOC_PWM_C1_MR_pwm_c1_mr_END    (31)


/*****************************************************************************
 结构名    : SOC_PWM_C0_MR0_UNION
 结构说明  : C0_MR0 寄存器结构定义。地址偏移量:0x0304，初值:0x00000000，宽度:32
 寄存器说明: PWM周期匹配寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pwm_c0_mr0 : 32; /* bit[0-31]: 用来记录通道0的匹配寄存器0的值。
                                                     单边沿和双边沿都会使用。
                                                     在单边沿模式记录pwm_out的高电平cycle数，该cycle指经过预分频。且在单边模式下，该寄存器不能配置为0(内部RTL代码限制)，如果想输出占空比为0的pwm波形，直接关闭pwm信号输出即可。
                                                     在双边沿模式记录pwm_out的低电平cycle数，该cycle指经过预分频，持续时间为该数值+1.
                                                     注：支持动态配置，即pwm_en一直有效的情况下，配置新值以达到动态调整占空比的目的。且动态调整的新值不会影响当前正在输出的pwm_out的占空比，即新值在下个pwm_out生效。 */
    } reg;
} SOC_PWM_C0_MR0_UNION;
#endif
#define SOC_PWM_C0_MR0_pwm_c0_mr0_START  (0)
#define SOC_PWM_C0_MR0_pwm_c0_mr0_END    (31)


/*****************************************************************************
 结构名    : SOC_PWM_C1_MR0_UNION
 结构说明  : C1_MR0 寄存器结构定义。地址偏移量:0x0404，初值:0x00000000，宽度:32
 寄存器说明: PWM周期匹配寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pwm_c1_mr0 : 32; /* bit[0-31]: 用来记录通道1的匹配寄存器0的值。
                                                     注：见PWM_C0_MR0 */
    } reg;
} SOC_PWM_C1_MR0_UNION;
#endif
#define SOC_PWM_C1_MR0_pwm_c1_mr0_START  (0)
#define SOC_PWM_C1_MR0_pwm_c1_mr0_END    (31)


/*****************************************************************************
 结构名    : SOC_PWM_C0_MR1_UNION
 结构说明  : C0_MR1 寄存器结构定义。地址偏移量:0x0308，初值:0x00000000，宽度:32
 寄存器说明: PWM周期匹配寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pwm_c0_mr1 : 32; /* bit[0-31]: 用来记录通道0的匹配寄存器1的值。
                                                     只在双边沿模式下使用。
                                                     注：支持动态配置，即pwm_en一直有效的情况下，配置新值以达到动态调整占空比的目的。且动态调整的新值不会影响当前正在输出的pwm_out的占空比，即新值在下个pwm_out生效。 */
    } reg;
} SOC_PWM_C0_MR1_UNION;
#endif
#define SOC_PWM_C0_MR1_pwm_c0_mr1_START  (0)
#define SOC_PWM_C0_MR1_pwm_c0_mr1_END    (31)


/*****************************************************************************
 结构名    : SOC_PWM_C1_MR1_UNION
 结构说明  : C1_MR1 寄存器结构定义。地址偏移量:0x0408，初值:0x00000000，宽度:32
 寄存器说明: PWM周期匹配寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pwm_c1_mr1 : 32; /* bit[0-31]: 用来记录通道1的匹配寄存器1的值。
                                                     注：见PWM_C0_MR1 */
    } reg;
} SOC_PWM_C1_MR1_UNION;
#endif
#define SOC_PWM_C1_MR1_pwm_c1_mr1_START  (0)
#define SOC_PWM_C1_MR1_pwm_c1_mr1_END    (31)


/*****************************************************************************
 结构名    : SOC_PWM_C0_TCNT_UNION
 结构说明  : C0_TCNT 寄存器结构定义。地址偏移量:0x030C，初值:0x00000000，宽度:32
 寄存器说明: PWM通道0的定时器寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pwm_c0_tcnt : 32; /* bit[0-31]: 全局复位或者软复位时，寄存器初始化；当定时器使能信号有效时，定时器自加1；当计数到周期匹配寄存器值时，清零0.
                                                      注：当pwm_en从关闭再到重新开启，需要进行全局复位或者软复位操作。否则该寄存器残留的计数值(前次pwm_en有效时)，会影响当前pwm_en有效时pwm_out的输出。 */
    } reg;
} SOC_PWM_C0_TCNT_UNION;
#endif
#define SOC_PWM_C0_TCNT_pwm_c0_tcnt_START  (0)
#define SOC_PWM_C0_TCNT_pwm_c0_tcnt_END    (31)


/*****************************************************************************
 结构名    : SOC_PWM_C1_TCNT_UNION
 结构说明  : C1_TCNT 寄存器结构定义。地址偏移量:0x040C，初值:0x00000000，宽度:32
 寄存器说明: PWM通道1的定时器寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pwm_c1_tcnt : 32; /* bit[0-31]: 全局复位或者软复位时，寄存器初始化；当定时器使能信号有效时，定时器自加1；当计数到周期匹配寄存器值时，清零0.
                                                      注：见PWM_C0_TCNT */
    } reg;
} SOC_PWM_C1_TCNT_UNION;
#endif
#define SOC_PWM_C1_TCNT_pwm_c1_tcnt_START  (0)
#define SOC_PWM_C1_TCNT_pwm_c1_tcnt_END    (31)


/*****************************************************************************
 结构名    : SOC_PWM_C0_PHA_UNION
 结构说明  : C0_PHA 寄存器结构定义。地址偏移量:0x0310，初值:0x00000000，宽度:32
 寄存器说明: PWM脉冲相位设置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pwm_ch0_pha : 32; /* bit[0-31]: 用来记录通道0输出脉冲的相位值。
                                                      注：该寄存器配置的值，只有在pwm_en有从0到1的过程，该配置值才会实际生效，否则实际使用的为原值。 */
    } reg;
} SOC_PWM_C0_PHA_UNION;
#endif
#define SOC_PWM_C0_PHA_pwm_ch0_pha_START  (0)
#define SOC_PWM_C0_PHA_pwm_ch0_pha_END    (31)


/*****************************************************************************
 结构名    : SOC_PWM_C1_PHA_UNION
 结构说明  : C1_PHA 寄存器结构定义。地址偏移量:0x0410，初值:0x00000000，宽度:32
 寄存器说明: PWM脉冲相位设置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pwm_ch1_pha : 32; /* bit[0-31]: 用来记录通道1输出脉冲的相位值。
                                                      注：见PWM_CO_PHA */
    } reg;
} SOC_PWM_C1_PHA_UNION;
#endif
#define SOC_PWM_C1_PHA_pwm_ch1_pha_START  (0)
#define SOC_PWM_C1_PHA_pwm_ch1_pha_END    (31)






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

#endif /* end of soc_pwm_interface.h */
