/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_m3_scs_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-23 11:27:30
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月23日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_M3_SCS.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_M3_SCS_INTERFACE_H__
#define __SOC_M3_SCS_INTERFACE_H__

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
/* 寄存器说明：Intrrupt Controller Type Register
   位域定义UNION结构:  SOC_M3_SCS_ICTR_UNION */
#define SOC_M3_SCS_ICTR_ADDR(base)                    ((base) + (0x004))

/* 寄存器说明：Auxiliary Control Register
   位域定义UNION结构:  SOC_M3_SCS_ACTLR_UNION */
#define SOC_M3_SCS_ACTLR_ADDR(base)                   ((base) + (0x008))

/* 寄存器说明：SysTick Control and Status Register
   位域定义UNION结构:  SOC_M3_SCS_STCSR_UNION */
#define SOC_M3_SCS_STCSR_ADDR(base)                   ((base) + (0x010))

/* 寄存器说明：SysTick Reload Value Register
   位域定义UNION结构:  SOC_M3_SCS_STRVR_UNION */
#define SOC_M3_SCS_STRVR_ADDR(base)                   ((base) + (0x014))

/* 寄存器说明：SysTick Current Value Register
   位域定义UNION结构:  SOC_M3_SCS_STCVR_UNION */
#define SOC_M3_SCS_STCVR_ADDR(base)                   ((base) + (0x018))

/* 寄存器说明：SysTick Calibration Value Register
   位域定义UNION结构:  SOC_M3_SCS_STCR_UNION */
#define SOC_M3_SCS_STCR_ADDR(base)                    ((base) + (0x01C))

/* 寄存器说明：Interrupt Set-Enable Register n
   位域定义UNION结构:  SOC_M3_SCS_NVIC_ISERn_UNION */
#define SOC_M3_SCS_NVIC_ISERn_ADDR(base, n)           ((base) + (0x100+(n)*4))

/* 寄存器说明：Interrupt Clear-Enable Register n
   位域定义UNION结构:  SOC_M3_SCS_NVIC_ICERn_UNION */
#define SOC_M3_SCS_NVIC_ICERn_ADDR(base, n)           ((base) + (0x180+(n)*4))

/* 寄存器说明：Interrupt Set-Pending Register n
   位域定义UNION结构:  SOC_M3_SCS_NVIC_ISPRn_UNION */
#define SOC_M3_SCS_NVIC_ISPRn_ADDR(base, n)           ((base) + (0x200+(n)*4))

/* 寄存器说明：Interrupt Clear-Pending Register n
   位域定义UNION结构:  SOC_M3_SCS_NVIC_ICPRn_UNION */
#define SOC_M3_SCS_NVIC_ICPRn_ADDR(base, n)           ((base) + (0x280+(n)*4))

/* 寄存器说明：Interrupt Active Bit Register n
   位域定义UNION结构:  SOC_M3_SCS_NVIC_IABRn_UNION */
#define SOC_M3_SCS_NVIC_IABRn_ADDR(base, n)           ((base) + (0x300+(n)*4))

/* 寄存器说明：Interrupt Priority Register m
   位域定义UNION结构:  SOC_M3_SCS_NVIC_IPRm_UNION */
#define SOC_M3_SCS_NVIC_IPRm_ADDR(base, m)            ((base) + (0x400+(m)*4))

/* 寄存器说明：CPUID Base Register
   位域定义UNION结构:  SOC_M3_SCS_CPUID_UNION */
#define SOC_M3_SCS_CPUID_ADDR(base)                   ((base) + (0xD00))

/* 寄存器说明：Interrupt Control and State Register
   位域定义UNION结构:  SOC_M3_SCS_ICSR_UNION */
#define SOC_M3_SCS_ICSR_ADDR(base)                    ((base) + (0xD04))

/* 寄存器说明：Vector Table Offset Register
   位域定义UNION结构:  SOC_M3_SCS_VTOR_UNION */
#define SOC_M3_SCS_VTOR_ADDR(base)                    ((base) + (0xD08))

/* 寄存器说明：Application Interrupt and Reset Control Register
   位域定义UNION结构:  SOC_M3_SCS_AIRCR_UNION */
#define SOC_M3_SCS_AIRCR_ADDR(base)                   ((base) + (0xD0C))

/* 寄存器说明：System Control Register
   位域定义UNION结构:  SOC_M3_SCS_SCR_UNION */
#define SOC_M3_SCS_SCR_ADDR(base)                     ((base) + (0xD10))

/* 寄存器说明：Configuration and Control Register
   位域定义UNION结构:  SOC_M3_SCS_CCR_UNION */
#define SOC_M3_SCS_CCR_ADDR(base)                     ((base) + (0xD14))

/* 寄存器说明：System Handler Priorty Register 1
   位域定义UNION结构:  SOC_M3_SCS_SHPR1_UNION */
#define SOC_M3_SCS_SHPR1_ADDR(base)                   ((base) + (0xD18))

/* 寄存器说明：System Handler Priorty Register 2
   位域定义UNION结构:  SOC_M3_SCS_SHPR2_UNION */
#define SOC_M3_SCS_SHPR2_ADDR(base)                   ((base) + (0xD1C))

/* 寄存器说明：System Handler Priorty Register 3
   位域定义UNION结构:  SOC_M3_SCS_SHPR3_UNION */
#define SOC_M3_SCS_SHPR3_ADDR(base)                   ((base) + (0xD20))

/* 寄存器说明：System Handler Control and State Register
   位域定义UNION结构:  SOC_M3_SCS_SHCSR_UNION */
#define SOC_M3_SCS_SHCSR_ADDR(base)                   ((base) + (0xD24))

/* 寄存器说明：Configurable Fault Status Registers
   位域定义UNION结构:  SOC_M3_SCS_CFSR_UNION */
#define SOC_M3_SCS_CFSR_ADDR(base)                    ((base) + (0xD28))

/* 寄存器说明：HardFault Status Register
   位域定义UNION结构:  SOC_M3_SCS_HFSR_UNION */
#define SOC_M3_SCS_HFSR_ADDR(base)                    ((base) + (0xD2C))

/* 寄存器说明：Debug Fault Status Register
   位域定义UNION结构:  SOC_M3_SCS_DFSR_UNION */
#define SOC_M3_SCS_DFSR_ADDR(base)                    ((base) + (0xD30))

/* 寄存器说明：MemManage Fault Address Register
   位域定义UNION结构:  SOC_M3_SCS_MMFAR_UNION */
#define SOC_M3_SCS_MMFAR_ADDR(base)                   ((base) + (0xD34))

/* 寄存器说明：BusFault Address Register
   位域定义UNION结构:  SOC_M3_SCS_BFAR_UNION */
#define SOC_M3_SCS_BFAR_ADDR(base)                    ((base) + (0xD38))

/* 寄存器说明：Auxiliary Fault Status Register
   位域定义UNION结构:  SOC_M3_SCS_AFSR_UNION */
#define SOC_M3_SCS_AFSR_ADDR(base)                    ((base) + (0xD3C))

/* 寄存器说明：Processor Feature Register 0
   位域定义UNION结构:  SOC_M3_SCS_ID_PFR0_UNION */
#define SOC_M3_SCS_ID_PFR0_ADDR(base)                 ((base) + (0xD40))

/* 寄存器说明：Processor Feature Register 1
   位域定义UNION结构:  SOC_M3_SCS_ID_PFR1_UNION */
#define SOC_M3_SCS_ID_PFR1_ADDR(base)                 ((base) + (0xD44))

/* 寄存器说明：Debug Features Register 0
   位域定义UNION结构:  SOC_M3_SCS_ID_DFR0_UNION */
#define SOC_M3_SCS_ID_DFR0_ADDR(base)                 ((base) + (0xD48))

/* 寄存器说明：Auxiliary Features Register 0
   位域定义UNION结构:  SOC_M3_SCS_ID_AFR0_UNION */
#define SOC_M3_SCS_ID_AFR0_ADDR(base)                 ((base) + (0xD4C))

/* 寄存器说明：Memory Model Feature Register 0
   位域定义UNION结构:  SOC_M3_SCS_ID_MMFR0_UNION */
#define SOC_M3_SCS_ID_MMFR0_ADDR(base)                ((base) + (0xD50))

/* 寄存器说明：Memory Model Feature Register 1
   位域定义UNION结构:  SOC_M3_SCS_ID_MMFR1_UNION */
#define SOC_M3_SCS_ID_MMFR1_ADDR(base)                ((base) + (0xD54))

/* 寄存器说明：Memory Model Feature Register 2
   位域定义UNION结构:  SOC_M3_SCS_ID_MMFR2_UNION */
#define SOC_M3_SCS_ID_MMFR2_ADDR(base)                ((base) + (0xD58))

/* 寄存器说明：Memory Model Feature Register 3
   位域定义UNION结构:  SOC_M3_SCS_ID_MMFR3_UNION */
#define SOC_M3_SCS_ID_MMFR3_ADDR(base)                ((base) + (0xD5C))

/* 寄存器说明：Instruction Set Attributes Register 0
   位域定义UNION结构:  SOC_M3_SCS_ID_ISAR0_UNION */
#define SOC_M3_SCS_ID_ISAR0_ADDR(base)                ((base) + (0xD60))

/* 寄存器说明：Instruction Set Attributes Register 1
   位域定义UNION结构:  SOC_M3_SCS_ID_ISAR1_UNION */
#define SOC_M3_SCS_ID_ISAR1_ADDR(base)                ((base) + (0xD64))

/* 寄存器说明：Instruction Set Attributes Register 2
   位域定义UNION结构:  SOC_M3_SCS_ID_ISAR2_UNION */
#define SOC_M3_SCS_ID_ISAR2_ADDR(base)                ((base) + (0xD68))

/* 寄存器说明：Instruction Set Attributes Register 3
   位域定义UNION结构:  SOC_M3_SCS_ID_ISAR3_UNION */
#define SOC_M3_SCS_ID_ISAR3_ADDR(base)                ((base) + (0xD6C))

/* 寄存器说明：Instruction Set Attributes Register 4
   位域定义UNION结构:  SOC_M3_SCS_ID_ISAR4_UNION */
#define SOC_M3_SCS_ID_ISAR4_ADDR(base)                ((base) + (0xD70))

/* 寄存器说明：Coprocessor Access Control Register
   位域定义UNION结构:  SOC_M3_SCS_CPACR_UNION */
#define SOC_M3_SCS_CPACR_ADDR(base)                   ((base) + (0xD88))

/* 寄存器说明：Software Triggered Interrupt Register
   位域定义UNION结构:  SOC_M3_SCS_STIR_UNION */
#define SOC_M3_SCS_STIR_ADDR(base)                    ((base) + (0xF00))





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
 结构名    : SOC_M3_SCS_ICTR_UNION
 结构说明  : ICTR 寄存器结构定义。地址偏移量:0x004，初值:0x00000003，宽度:32
 寄存器说明: Intrrupt Controller Type Register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  intlinesnum : 4;  /* bit[0-3] : NVIC最多支持240个中断 */
        unsigned int  reserved    : 28; /* bit[4-31]: Reserved */
    } reg;
} SOC_M3_SCS_ICTR_UNION;
#endif
#define SOC_M3_SCS_ICTR_intlinesnum_START  (0)
#define SOC_M3_SCS_ICTR_intlinesnum_END    (3)


/*****************************************************************************
 结构名    : SOC_M3_SCS_ACTLR_UNION
 结构说明  : ACTLR 寄存器结构定义。地址偏移量:0x008，初值:0x00000000，宽度:32
 寄存器说明: Auxiliary Control Register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dismcycint : 1;  /* bit[0]   : 禁止多周期指令的中断。这会增加中断响应延迟。 */
        unsigned int  disdefwbuf : 1;  /* bit[1]   : 禁止在默认的地址空间访问时使用write buffer。
                                                     所有的bus fault都成为precise bus fault
                                                     但是会降低处理器性能 */
        unsigned int  disfold    : 1;  /* bit[2]   : 禁止IT floding功能。 */
        unsigned int  reserved   : 29; /* bit[3-31]: Reserved */
    } reg;
} SOC_M3_SCS_ACTLR_UNION;
#endif
#define SOC_M3_SCS_ACTLR_dismcycint_START  (0)
#define SOC_M3_SCS_ACTLR_dismcycint_END    (0)
#define SOC_M3_SCS_ACTLR_disdefwbuf_START  (1)
#define SOC_M3_SCS_ACTLR_disdefwbuf_END    (1)
#define SOC_M3_SCS_ACTLR_disfold_START     (2)
#define SOC_M3_SCS_ACTLR_disfold_END       (2)


/*****************************************************************************
 结构名    : SOC_M3_SCS_STCSR_UNION
 结构说明  : STCSR 寄存器结构定义。地址偏移量:0x010，初值:0x00000000，宽度:32
 寄存器说明: SysTick Control and Status Register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  enable    : 1;  /* bit[0]    : 0：禁止计数器
                                                     1：使能计数器。计数器从ST_RVR寄存器获取reload值开始倒计数，当归零后将COUNTFLAG置为1，并选择是否配置TICKINT。然后再获取reload值重新开始计数。 */
        unsigned int  tickint   : 1;  /* bit[1]    : 0：计数归零后不挂起SysTick handler，软件可以通过COUNTFLAG来判断是否计到零
                                                     1：计数归零后挂起SysTick handler */
        unsigned int  clksource : 1;  /* bit[2]    : 0：外部参考时钟(STCLK)
                                                     1：core时钟(FCLK)
                                                     如果没有外部参考时钟，则必须接为1。Core时钟频率必须是外部参考时钟的2.5倍以上，否则计数值不可预计 */
        unsigned int  reserved_0: 13; /* bit[3-15] : Reserved */
        unsigned int  countflag : 1;  /* bit[16]   : 从上一次被读开始，计数器为0时返回1
                                                     读这个寄存器的任何部分，都将该值清零；
                                                     如果调试器通过DAP访问，只有当MasterType设置为0的情况下，该值才能被清零，否则不会改变 */
        unsigned int  reserved_1: 15; /* bit[17-31]: Reserved */
    } reg;
} SOC_M3_SCS_STCSR_UNION;
#endif
#define SOC_M3_SCS_STCSR_enable_START     (0)
#define SOC_M3_SCS_STCSR_enable_END       (0)
#define SOC_M3_SCS_STCSR_tickint_START    (1)
#define SOC_M3_SCS_STCSR_tickint_END      (1)
#define SOC_M3_SCS_STCSR_clksource_START  (2)
#define SOC_M3_SCS_STCSR_clksource_END    (2)
#define SOC_M3_SCS_STCSR_countflag_START  (16)
#define SOC_M3_SCS_STCSR_countflag_END    (16)


/*****************************************************************************
 结构名    : SOC_M3_SCS_STRVR_UNION
 结构说明  : STRVR 寄存器结构定义。地址偏移量:0x014，初值:0x00000000，宽度:32
 寄存器说明: SysTick Reload Value Register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reload   : 24; /* bit[0-23] : 计数器重新装载的值，范围为1～0x00FFFFFF，配置为0无效
                                                    配置为N，则倒计数N+1个时钟周期后产生请求，并且不断循环。如果在每个tick中断中配置新的reload值M，则倒计数M个时钟周期产生请求。 */
        unsigned int  reserved : 8;  /* bit[24-31]: Reserved */
    } reg;
} SOC_M3_SCS_STRVR_UNION;
#endif
#define SOC_M3_SCS_STRVR_reload_START    (0)
#define SOC_M3_SCS_STRVR_reload_END      (23)


/*****************************************************************************
 结构名    : SOC_M3_SCS_STCVR_UNION
 结构说明  : STCVR 寄存器结构定义。地址偏移量:0x018，初值:0x00000000，宽度:32
 寄存器说明: SysTick Current Value Register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  current  : 24; /* bit[0-23] : 读：获取当前计数器的值
                                                    写：写清，当写该寄存器，则将寄存器清零，并且清除ST_CSR寄存器的COUNTFLAG位 */
        unsigned int  reserved : 8;  /* bit[24-31]: Reserved */
    } reg;
} SOC_M3_SCS_STCVR_UNION;
#endif
#define SOC_M3_SCS_STCVR_current_START   (0)
#define SOC_M3_SCS_STCVR_current_END     (23)


/*****************************************************************************
 结构名    : SOC_M3_SCS_STCR_UNION
 结构说明  : STCR 寄存器结构定义。地址偏移量:0x01C，初值:0x00000000，宽度:32
 寄存器说明: SysTick Calibration Value Register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tenms    : 24; /* bit[0-23] : 用于计算准确的10ms的校准值。SKEW位必须为1 */
        unsigned int  reserved : 6;  /* bit[24-29]: Reserved */
        unsigned int  skew     : 1;  /* bit[30]   : 0：校准值是准确的10ms
                                                    1：校准值不是准确的10ms */
        unsigned int  noref    : 1;  /* bit[31]   : 0：有参考时钟
                                                    1：无参考时钟 */
    } reg;
} SOC_M3_SCS_STCR_UNION;
#endif
#define SOC_M3_SCS_STCR_tenms_START     (0)
#define SOC_M3_SCS_STCR_tenms_END       (23)
#define SOC_M3_SCS_STCR_skew_START      (30)
#define SOC_M3_SCS_STCR_skew_END        (30)
#define SOC_M3_SCS_STCR_noref_START     (31)
#define SOC_M3_SCS_STCR_noref_END       (31)


/*****************************************************************************
 结构名    : SOC_M3_SCS_NVIC_ISERn_UNION
 结构说明  : NVIC_ISERn 寄存器结构定义。地址偏移量:0x100+(n)*4，初值:0x00000000，宽度:32
 寄存器说明: Interrupt Set-Enable Register n
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  setena : 32; /* bit[0-31]: 中断使能控制，每bit对应一个中断
                                                 On reads 0 = Interrupt disabled.
                                                  1 = Interrupt enabled.
                                                 On writes 0 = No effect.
                                                  1 = Enable interrupt. */
    } reg;
} SOC_M3_SCS_NVIC_ISERn_UNION;
#endif
#define SOC_M3_SCS_NVIC_ISERn_setena_START  (0)
#define SOC_M3_SCS_NVIC_ISERn_setena_END    (31)


/*****************************************************************************
 结构名    : SOC_M3_SCS_NVIC_ICERn_UNION
 结构说明  : NVIC_ICERn 寄存器结构定义。地址偏移量:0x180+(n)*4，初值:0x00000000，宽度:32
 寄存器说明: Interrupt Clear-Enable Register n
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  clrena : 32; /* bit[0-31]: 中断去使能控制，每bit对应一个中断
                                                 On reads 0 = Interrupt disabled.
                                                  1 = Interrupt enabled.
                                                 On writes 0 = No effect.
                                                  1 = Disable interrupt. */
    } reg;
} SOC_M3_SCS_NVIC_ICERn_UNION;
#endif
#define SOC_M3_SCS_NVIC_ICERn_clrena_START  (0)
#define SOC_M3_SCS_NVIC_ICERn_clrena_END    (31)


/*****************************************************************************
 结构名    : SOC_M3_SCS_NVIC_ISPRn_UNION
 结构说明  : NVIC_ISPRn 寄存器结构定义。地址偏移量:0x200+(n)*4，初值:0x00000000，宽度:32
 寄存器说明: Interrupt Set-Pending Register n
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  setpend : 32; /* bit[0-31]: 中断pending状态控制，每bit对应一个中断
                                                  On reads 0 = Interrupt is not pending.
                                                   1 = Interrupt is pending.
                                                  On writes 0 = No effect.
                                                   1 = Changes state of interrupt to pending. */
    } reg;
} SOC_M3_SCS_NVIC_ISPRn_UNION;
#endif
#define SOC_M3_SCS_NVIC_ISPRn_setpend_START  (0)
#define SOC_M3_SCS_NVIC_ISPRn_setpend_END    (31)


/*****************************************************************************
 结构名    : SOC_M3_SCS_NVIC_ICPRn_UNION
 结构说明  : NVIC_ICPRn 寄存器结构定义。地址偏移量:0x280+(n)*4，初值:0x00000000，宽度:32
 寄存器说明: Interrupt Clear-Pending Register n
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  clrpend : 32; /* bit[0-31]: 中断pending状态清除，每bit对应一个中断
                                                  On reads 0 = Interrupt is not pending.
                                                   1 = Interrupt is pending.
                                                  On writes 0 = No effect.
                                                   1 = Clears the pending state of the interrupt. */
    } reg;
} SOC_M3_SCS_NVIC_ICPRn_UNION;
#endif
#define SOC_M3_SCS_NVIC_ICPRn_clrpend_START  (0)
#define SOC_M3_SCS_NVIC_ICPRn_clrpend_END    (31)


/*****************************************************************************
 结构名    : SOC_M3_SCS_NVIC_IABRn_UNION
 结构说明  : NVIC_IABRn 寄存器结构定义。地址偏移量:0x300+(n)*4，初值:0x00000000，宽度:32
 寄存器说明: Interrupt Active Bit Register n
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  active : 32; /* bit[0-31]: 中断active状态，每bit对应一个中断
                                                 0 = Interrupt not active.
                                                 1 = Interrupt active. */
    } reg;
} SOC_M3_SCS_NVIC_IABRn_UNION;
#endif
#define SOC_M3_SCS_NVIC_IABRn_active_START  (0)
#define SOC_M3_SCS_NVIC_IABRn_active_END    (31)


/*****************************************************************************
 结构名    : SOC_M3_SCS_NVIC_IPRm_UNION
 结构说明  : NVIC_IPRm 寄存器结构定义。地址偏移量:0x400+(m)*4，初值:0x00000000，宽度:32
 寄存器说明: Interrupt Priority Register m
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pri_n0 : 8;  /* bit[0-7]  : For register NVIC_IPRm, priority of interrupt number 4m */
        unsigned int  pri_n1 : 8;  /* bit[8-15] : For register NVIC_IPRm, priority of interrupt number 4m+1. */
        unsigned int  pri_n2 : 8;  /* bit[16-23]: For register NVIC_IPRm, priority of interrupt number 4m+2. */
        unsigned int  pri_n3 : 8;  /* bit[24-31]: For register NVIC_IPRm, priority of interrupt number 4m+3. */
    } reg;
} SOC_M3_SCS_NVIC_IPRm_UNION;
#endif
#define SOC_M3_SCS_NVIC_IPRm_pri_n0_START  (0)
#define SOC_M3_SCS_NVIC_IPRm_pri_n0_END    (7)
#define SOC_M3_SCS_NVIC_IPRm_pri_n1_START  (8)
#define SOC_M3_SCS_NVIC_IPRm_pri_n1_END    (15)
#define SOC_M3_SCS_NVIC_IPRm_pri_n2_START  (16)
#define SOC_M3_SCS_NVIC_IPRm_pri_n2_END    (23)
#define SOC_M3_SCS_NVIC_IPRm_pri_n3_START  (24)
#define SOC_M3_SCS_NVIC_IPRm_pri_n3_END    (31)


/*****************************************************************************
 结构名    : SOC_M3_SCS_CPUID_UNION
 结构说明  : CPUID 寄存器结构定义。地址偏移量:0xD00，初值:0x412FC231，宽度:32
 寄存器说明: CPUID Base Register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  revision    : 4;  /* bit[0-3]  : Revision */
        unsigned int  partno      : 12; /* bit[4-15] : [11:10] b11 = Cortex family
                                                       [9:8] b00 = version
                                                       [7:6] b00 = reserved
                                                       [5:4] b10 = M (v7-M)
                                                       [3:0] X = family member. Cortex-M3 family is b0011. */
        unsigned int  constant    : 4;  /* bit[16-19]: 固定为0xF */
        unsigned int  variant     : 4;  /* bit[20-23]: 由集成决定variant值 */
        unsigned int  implementer : 8;  /* bit[24-31]: ARM为0x41 */
    } reg;
} SOC_M3_SCS_CPUID_UNION;
#endif
#define SOC_M3_SCS_CPUID_revision_START     (0)
#define SOC_M3_SCS_CPUID_revision_END       (3)
#define SOC_M3_SCS_CPUID_partno_START       (4)
#define SOC_M3_SCS_CPUID_partno_END         (15)
#define SOC_M3_SCS_CPUID_constant_START     (16)
#define SOC_M3_SCS_CPUID_constant_END       (19)
#define SOC_M3_SCS_CPUID_variant_START      (20)
#define SOC_M3_SCS_CPUID_variant_END        (23)
#define SOC_M3_SCS_CPUID_implementer_START  (24)
#define SOC_M3_SCS_CPUID_implementer_END    (31)


/*****************************************************************************
 结构名    : SOC_M3_SCS_ICSR_UNION
 结构说明  : ICSR 寄存器结构定义。地址偏移量:0xD04，初值:0x00000000，宽度:32
 寄存器说明: Interrupt Control and State Register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vectactive  : 9;  /* bit[0-8]  : 当前正在处理的ISR对应的中断号，包括NMI和Hard Fault
                                                       外部中断从16号开始，即INTISR[0]=16 */
        unsigned int  reserved_0  : 2;  /* bit[9-10] : Reserved */
        unsigned int  rettobase   : 1;  /* bit[11]   : This bit is 1 when the set of all active exceptions minus the IPSR_current_exception yields the empty set. */
        unsigned int  vectpending : 10; /* bit[12-21]: 表示最高优先级挂起的ISR对应的中断号 */
        unsigned int  isrpending  : 1;  /* bit[22]   : 中断挂起标志，不包括NMI和Fault异常
                                                       0：中断没有挂起
                                                       1：中断挂起 */
        unsigned int  isrpreempt  : 1;  /* bit[23]   : 仅在debug模式下使用，表示一个挂起的中断在下个周期将被激活 */
        unsigned int  reserved_1  : 1;  /* bit[24]   : Reserved */
        unsigned int  pendstclr   : 1;  /* bit[25]   : 清除SysTick挂起
                                                       0：不清除SysTick挂起
                                                       1：清除SysTick挂起 */
        unsigned int  pendstset   : 1;  /* bit[26]   : 设置SysTick挂起
                                                       0：不挂起SysTick
                                                       1：挂起SysTick */
        unsigned int  pendsvclr   : 1;  /* bit[27]   : 清除pendSV挂起
                                                       0：不清除pendSV挂起
                                                       1：清除pendSV挂起 */
        unsigned int  pendsvset   : 1;  /* bit[28]   : 设置pendSV挂起
                                                       0：不挂起pendSV
                                                       1：挂起pendSV */
        unsigned int  reserved_2  : 2;  /* bit[29-30]: Reserved */
        unsigned int  nmipendset  : 1;  /* bit[31]   : 设置NMI中断挂起
                                                       0：不挂起NMI
                                                       1：挂起NMI
                                                       一旦挂起NMI，则NMI被激活，因为NMI没有屏蔽位 */
    } reg;
} SOC_M3_SCS_ICSR_UNION;
#endif
#define SOC_M3_SCS_ICSR_vectactive_START   (0)
#define SOC_M3_SCS_ICSR_vectactive_END     (8)
#define SOC_M3_SCS_ICSR_rettobase_START    (11)
#define SOC_M3_SCS_ICSR_rettobase_END      (11)
#define SOC_M3_SCS_ICSR_vectpending_START  (12)
#define SOC_M3_SCS_ICSR_vectpending_END    (21)
#define SOC_M3_SCS_ICSR_isrpending_START   (22)
#define SOC_M3_SCS_ICSR_isrpending_END     (22)
#define SOC_M3_SCS_ICSR_isrpreempt_START   (23)
#define SOC_M3_SCS_ICSR_isrpreempt_END     (23)
#define SOC_M3_SCS_ICSR_pendstclr_START    (25)
#define SOC_M3_SCS_ICSR_pendstclr_END      (25)
#define SOC_M3_SCS_ICSR_pendstset_START    (26)
#define SOC_M3_SCS_ICSR_pendstset_END      (26)
#define SOC_M3_SCS_ICSR_pendsvclr_START    (27)
#define SOC_M3_SCS_ICSR_pendsvclr_END      (27)
#define SOC_M3_SCS_ICSR_pendsvset_START    (28)
#define SOC_M3_SCS_ICSR_pendsvset_END      (28)
#define SOC_M3_SCS_ICSR_nmipendset_START   (31)
#define SOC_M3_SCS_ICSR_nmipendset_END     (31)


/*****************************************************************************
 结构名    : SOC_M3_SCS_VTOR_UNION
 结构说明  : VTOR 寄存器结构定义。地址偏移量:0xD08，初值:0x00000000，宽度:32
 寄存器说明: Vector Table Offset Register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 7;  /* bit[0-6]  : Reserved */
        unsigned int  tbloff   : 22; /* bit[7-28] : 向量表的偏移地址，表示从Code区域或RAM区域的最低地址开始的偏移地址，必须32-bit对齐 */
        unsigned int  tblabse  : 1;  /* bit[29]   : 向量表基址所在内存的区域
                                                    0：Code区域
                                                    1：RAM区域 */
        unsigned int  reserved_1: 2;  /* bit[30-31]: Reserved */
    } reg;
} SOC_M3_SCS_VTOR_UNION;
#endif
#define SOC_M3_SCS_VTOR_tbloff_START    (7)
#define SOC_M3_SCS_VTOR_tbloff_END      (28)
#define SOC_M3_SCS_VTOR_tblabse_START   (29)
#define SOC_M3_SCS_VTOR_tblabse_END     (29)


/*****************************************************************************
 结构名    : SOC_M3_SCS_AIRCR_UNION
 结构说明  : AIRCR 寄存器结构定义。地址偏移量:0xD0C，初值:0xFA050000，宽度:32
 寄存器说明: Application Interrupt and Reset Control Register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vectreset           : 1;  /* bit[0]    : 系统复位bit。用于复位除debug模块外逻辑。该位自清。
                                                               0：不复位系统
                                                               1：复位系统
                                                               在debug模式下，只有当处理器进入halt状态才能配置
                                                               注意：SYSRESETREQ也会被VECTRESET清除，因此建议这两位互斥操作，不要同时配置1 */
        unsigned int  vectclractive       : 1;  /* bit[1]    : 清除激活向量位，自清
                                                               0：不清除
                                                               1：清除所有激活的中断、NMI和Fault的状态信息
                                                               该位用于在debug时返回一个确定的状态。
                                                               IPSR寄存器不受该位影响。 */
        unsigned int  sysresetreq         : 1;  /* bit[2]    : 配置该位触发输出的SYSRESETREQ信号，引起系统复位，用于复位内部除debug模块外的所有逻辑 */
        unsigned int  reserved_0          : 5;  /* bit[3-7]  : Reserved */
        unsigned int  prigroup            : 3;  /* bit[8-10] : 设置抢占优先级与子优先级的分割位
                                                               0： [7.1] 抢占优先级7bit，子优先级1bit
                                                               1： [6.2] 抢占优先级6bit，子优先级2bit
                                                               2： [5.3] 抢占优先级5bit，子优先级3bit
                                                               3： [4.4] 抢占优先级4bit，子优先级4bit
                                                               4： [3.5] 抢占优先级3bit，子优先级5bit
                                                               5： [2.6] 抢占优先级2bit，子优先级6bit
                                                               6： [1.7] 抢占优先级1bit，子优先级7bit
                                                               7： [0.8] 无抢占优先级，子优先级8bit
                                                               抢占优先级用PRI优先级位的8bit的左半部分（高位）表示，子优先级用右半部分（低位）表示 */
        unsigned int  reserved_1          : 4;  /* bit[11-14]: Reserved */
        unsigned int  endianess           : 1;  /* bit[15]   : 0：小端
                                                               1：大端
                                                               在复位时采样输入信号BIGEND，其他时间无法更改 */
        unsigned int  vectkey_vectkeystat : 16; /* bit[16-31]: 对该寄存器写操作，必须在VECTKEY位写0x5FA，否则无法更改寄存器值。该位写其他值无效。读返回始终为0xFA05 */
    } reg;
} SOC_M3_SCS_AIRCR_UNION;
#endif
#define SOC_M3_SCS_AIRCR_vectreset_START            (0)
#define SOC_M3_SCS_AIRCR_vectreset_END              (0)
#define SOC_M3_SCS_AIRCR_vectclractive_START        (1)
#define SOC_M3_SCS_AIRCR_vectclractive_END          (1)
#define SOC_M3_SCS_AIRCR_sysresetreq_START          (2)
#define SOC_M3_SCS_AIRCR_sysresetreq_END            (2)
#define SOC_M3_SCS_AIRCR_prigroup_START             (8)
#define SOC_M3_SCS_AIRCR_prigroup_END               (10)
#define SOC_M3_SCS_AIRCR_endianess_START            (15)
#define SOC_M3_SCS_AIRCR_endianess_END              (15)
#define SOC_M3_SCS_AIRCR_vectkey_vectkeystat_START  (16)
#define SOC_M3_SCS_AIRCR_vectkey_vectkeystat_END    (31)


/*****************************************************************************
 结构名    : SOC_M3_SCS_SCR_UNION
 结构说明  : SCR 寄存器结构定义。地址偏移量:0xD10，初值:0x00000000，宽度:32
 寄存器说明: System Control Register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0  : 1;  /* bit[0]   : Reserved */
        unsigned int  sleeponexit : 1;  /* bit[1]   : 当从handler模式到thread模式推出时进入睡眠
                                                      0：当返回thread模式时不睡眠
                                                      1：推出ISR时进入睡眠 */
        unsigned int  sleepdeep   : 1;  /* bit[2]   : 0：不能关闭core时钟
                                                      1：使输出信号SLEEPDEEP有效，指示可以关闭core时钟 */
        unsigned int  reserved_1  : 1;  /* bit[3]   : Reserved */
        unsigned int  sevonpend   : 1;  /* bit[4]   : 设置该位，是的当中断从未激活到挂起状态则WFE唤醒 */
        unsigned int  reserved_2  : 27; /* bit[5-31]: Reserved */
    } reg;
} SOC_M3_SCS_SCR_UNION;
#endif
#define SOC_M3_SCS_SCR_sleeponexit_START  (1)
#define SOC_M3_SCS_SCR_sleeponexit_END    (1)
#define SOC_M3_SCS_SCR_sleepdeep_START    (2)
#define SOC_M3_SCS_SCR_sleepdeep_END      (2)
#define SOC_M3_SCS_SCR_sevonpend_START    (4)
#define SOC_M3_SCS_SCR_sevonpend_END      (4)


/*****************************************************************************
 结构名    : SOC_M3_SCS_CCR_UNION
 结构说明  : CCR 寄存器结构定义。地址偏移量:0xD14，初值:0x00000000，宽度:32
 寄存器说明: Configuration and Control Register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  nonebasethrdena : 1;  /* bit[0]    : 0：当从最后一个异常返回时只能进入thread模式
                                                           1：handler模式任何情况下都能够通过控制返回值进入thread模式 */
        unsigned int  usersetmpend    : 1;  /* bit[1]    : 配置1，则使得用户代码能够通过配置STIR寄存器来触发Main异常 */
        unsigned int  reserved_0      : 1;  /* bit[2]    : Reserved */
        unsigned int  unalign_trp     : 1;  /* bit[3]    : Trap for unaligned access. This enables faulting/halting on any unaligned half or full word access. Unaligned load-store multiples always fault. The relevant Usage Fault Status Register bit is UNALIGNED, see Usage Fault Status Register */
        unsigned int  div_0_trp       : 1;  /* bit[4]    : Trap on Divide by 0. This enables faulting/halting when an attempt is made to divide by 0. The relevant Usage Fault Status Register bit is DIVBYZERO, see Usage Fault Status Register */
        unsigned int  reserved_1      : 3;  /* bit[5-7]  : Reserved */
        unsigned int  bfhfnmign       : 1;  /* bit[8]    : 使能该位，则服务程序运行在-1和-2优先级，而忽视由load和store操作引发的数据总线fault */
        unsigned int  stkalign        : 1;  /* bit[9]    : 0：保证SP在进入异常之前只用4-byte对齐
                                                           1：在异常入口，SP在进入异常之前调整为8-byte对齐 */
        unsigned int  reserved_2      : 22; /* bit[10-31]: Reserved */
    } reg;
} SOC_M3_SCS_CCR_UNION;
#endif
#define SOC_M3_SCS_CCR_nonebasethrdena_START  (0)
#define SOC_M3_SCS_CCR_nonebasethrdena_END    (0)
#define SOC_M3_SCS_CCR_usersetmpend_START     (1)
#define SOC_M3_SCS_CCR_usersetmpend_END       (1)
#define SOC_M3_SCS_CCR_unalign_trp_START      (3)
#define SOC_M3_SCS_CCR_unalign_trp_END        (3)
#define SOC_M3_SCS_CCR_div_0_trp_START        (4)
#define SOC_M3_SCS_CCR_div_0_trp_END          (4)
#define SOC_M3_SCS_CCR_bfhfnmign_START        (8)
#define SOC_M3_SCS_CCR_bfhfnmign_END          (8)
#define SOC_M3_SCS_CCR_stkalign_START         (9)
#define SOC_M3_SCS_CCR_stkalign_END           (9)


/*****************************************************************************
 结构名    : SOC_M3_SCS_SHPR1_UNION
 结构说明  : SHPR1 寄存器结构定义。地址偏移量:0xD18，初值:0x00000000，宽度:32
 寄存器说明: System Handler Priorty Register 1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pri_4    : 8;  /* bit[0-7]  : Priority of system handler 4, MemManage */
        unsigned int  pri_5    : 8;  /* bit[8-15] : Priority of system handler 5, BusFault */
        unsigned int  pri_6    : 8;  /* bit[16-23]: Priority of system handler 6, UsageFault */
        unsigned int  reserved : 8;  /* bit[24-31]: Reserved for priority of system handler 7 */
    } reg;
} SOC_M3_SCS_SHPR1_UNION;
#endif
#define SOC_M3_SCS_SHPR1_pri_4_START     (0)
#define SOC_M3_SCS_SHPR1_pri_4_END       (7)
#define SOC_M3_SCS_SHPR1_pri_5_START     (8)
#define SOC_M3_SCS_SHPR1_pri_5_END       (15)
#define SOC_M3_SCS_SHPR1_pri_6_START     (16)
#define SOC_M3_SCS_SHPR1_pri_6_END       (23)


/*****************************************************************************
 结构名    : SOC_M3_SCS_SHPR2_UNION
 结构说明  : SHPR2 寄存器结构定义。地址偏移量:0xD1C，初值:0x00000000，宽度:32
 寄存器说明: System Handler Priorty Register 2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 8;  /* bit[0-7]  : Reserved for priority of system handler 8 */
        unsigned int  reserved_1: 8;  /* bit[8-15] : Reserved for priority of system handler 9 */
        unsigned int  reserved_2: 8;  /* bit[16-23]: Reserved for priority of system handler 10 */
        unsigned int  pri_11   : 8;  /* bit[24-31]: Priority of system handler 11, SVCall */
    } reg;
} SOC_M3_SCS_SHPR2_UNION;
#endif
#define SOC_M3_SCS_SHPR2_pri_11_START    (24)
#define SOC_M3_SCS_SHPR2_pri_11_END      (31)


/*****************************************************************************
 结构名    : SOC_M3_SCS_SHPR3_UNION
 结构说明  : SHPR3 寄存器结构定义。地址偏移量:0xD20，初值:0x00000000，宽度:32
 寄存器说明: System Handler Priorty Register 3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pri_12   : 8;  /* bit[0-7]  : Priority of system handler 12, DebugMonitor */
        unsigned int  reserved : 8;  /* bit[8-15] : Reserved for priority of system handler 13 */
        unsigned int  pri_14   : 8;  /* bit[16-23]: Priority of system handler 14, PendSV */
        unsigned int  pri_15   : 8;  /* bit[24-31]: Priority of system handler 15, SysTick */
    } reg;
} SOC_M3_SCS_SHPR3_UNION;
#endif
#define SOC_M3_SCS_SHPR3_pri_12_START    (0)
#define SOC_M3_SCS_SHPR3_pri_12_END      (7)
#define SOC_M3_SCS_SHPR3_pri_14_START    (16)
#define SOC_M3_SCS_SHPR3_pri_14_END      (23)
#define SOC_M3_SCS_SHPR3_pri_15_START    (24)
#define SOC_M3_SCS_SHPR3_pri_15_END      (31)


/*****************************************************************************
 结构名    : SOC_M3_SCS_SHCSR_UNION
 结构说明  : SHCSR 寄存器结构定义。地址偏移量:0xD24，初值:0x00000000，宽度:32
 寄存器说明: System Handler Control and State Register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  memfaultact    : 1;  /* bit[0]    : 0 = MemManage is not active.
                                                          1 = MemManage is active. */
        unsigned int  busfaultact    : 1;  /* bit[1]    : 0 = BusFault is not active.
                                                          1 = BusFault is active. */
        unsigned int  reserved_0     : 1;  /* bit[2]    : Reserved */
        unsigned int  usgfaultact    : 1;  /* bit[3]    : 0 = UsageFault is not active.
                                                          1 = UsageFault is active. */
        unsigned int  reserved_1     : 3;  /* bit[4-6]  : Reserved */
        unsigned int  svcallact      : 1;  /* bit[7]    : 0 = SVCall is not active.
                                                          1 = SVCall is active.  */
        unsigned int  monitoract     : 1;  /* bit[8]    : 0 = Monitor is not active.
                                                          1 = Monitor is active.  */
        unsigned int  reserved_2     : 1;  /* bit[9]    : Reserved */
        unsigned int  pendsvact      : 1;  /* bit[10]   : 0 = PendSV is not active.
                                                          1 = PendSV is active.  */
        unsigned int  systickact     : 1;  /* bit[11]   : 0 = SysTick is not active.
                                                          1 = SysTick is active. */
        unsigned int  usgfaultpended : 1;  /* bit[12]   : 0 = UsageFault is not pending.
                                                          1 = UsageFault is pending. */
        unsigned int  memfaultpended : 1;  /* bit[13]   : 0 = MemManage is not pending.
                                                          1 = MemManage is pending. */
        unsigned int  busfaultpended : 1;  /* bit[14]   : 0 = BusFault is not pending.
                                                          1 = BusFault is pending. */
        unsigned int  svcallpended   : 1;  /* bit[15]   : 0 = SVCall is not pending.
                                                          1 = SVCall is pending. */
        unsigned int  memfaultena    : 1;  /* bit[16]   : 0 = Disable MemManage fault.
                                                          1 = Enable MemManage fault.  */
        unsigned int  busfaultena    : 1;  /* bit[17]   : 0 = Disable BusFault.
                                                          1 = Enable BusFault.  */
        unsigned int  usgfaultena    : 1;  /* bit[18]   : 0 = Disable UsageFault.
                                                          1 = Enable UsageFault.  */
        unsigned int  reserved_3     : 13; /* bit[19-31]: Reserved */
    } reg;
} SOC_M3_SCS_SHCSR_UNION;
#endif
#define SOC_M3_SCS_SHCSR_memfaultact_START     (0)
#define SOC_M3_SCS_SHCSR_memfaultact_END       (0)
#define SOC_M3_SCS_SHCSR_busfaultact_START     (1)
#define SOC_M3_SCS_SHCSR_busfaultact_END       (1)
#define SOC_M3_SCS_SHCSR_usgfaultact_START     (3)
#define SOC_M3_SCS_SHCSR_usgfaultact_END       (3)
#define SOC_M3_SCS_SHCSR_svcallact_START       (7)
#define SOC_M3_SCS_SHCSR_svcallact_END         (7)
#define SOC_M3_SCS_SHCSR_monitoract_START      (8)
#define SOC_M3_SCS_SHCSR_monitoract_END        (8)
#define SOC_M3_SCS_SHCSR_pendsvact_START       (10)
#define SOC_M3_SCS_SHCSR_pendsvact_END         (10)
#define SOC_M3_SCS_SHCSR_systickact_START      (11)
#define SOC_M3_SCS_SHCSR_systickact_END        (11)
#define SOC_M3_SCS_SHCSR_usgfaultpended_START  (12)
#define SOC_M3_SCS_SHCSR_usgfaultpended_END    (12)
#define SOC_M3_SCS_SHCSR_memfaultpended_START  (13)
#define SOC_M3_SCS_SHCSR_memfaultpended_END    (13)
#define SOC_M3_SCS_SHCSR_busfaultpended_START  (14)
#define SOC_M3_SCS_SHCSR_busfaultpended_END    (14)
#define SOC_M3_SCS_SHCSR_svcallpended_START    (15)
#define SOC_M3_SCS_SHCSR_svcallpended_END      (15)
#define SOC_M3_SCS_SHCSR_memfaultena_START     (16)
#define SOC_M3_SCS_SHCSR_memfaultena_END       (16)
#define SOC_M3_SCS_SHCSR_busfaultena_START     (17)
#define SOC_M3_SCS_SHCSR_busfaultena_END       (17)
#define SOC_M3_SCS_SHCSR_usgfaultena_START     (18)
#define SOC_M3_SCS_SHCSR_usgfaultena_END       (18)


/*****************************************************************************
 结构名    : SOC_M3_SCS_CFSR_UNION
 结构说明  : CFSR 寄存器结构定义。地址偏移量:0xD28，初值:0x00000000，宽度:32
 寄存器说明: Configurable Fault Status Registers
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iaccviol    : 1;  /* bit[0]    : 0 = No MPU or Execute Never (XN) default memory map access violation has occurred.
                                                       1 = MPU or Execute Never (XN) default memory map access violation on an instruction fetch has occurred. The fault is signalled only if the instruction is issued. */
        unsigned int  daccviol    : 1;  /* bit[1]    : 0 = No data access violation has occurred. 
                                                       1 = Data access violation. The MMAR shows the data address that the load or store tried 
                                                       to access. */
        unsigned int  reserved_0  : 1;  /* bit[2]    : Reserved */
        unsigned int  munstkerr   : 1;  /* bit[3]    : 0 = No derived MemManage fault has occurred. 
                                                       1 = A derived MemManage fault occurred on exception return.  */
        unsigned int  mstkerr     : 1;  /* bit[4]    : 0 = No derived MemManage fault has occurred.
                                                       1 = A derived MemManage fault occurred on exception entry. */
        unsigned int  mlsperr     : 1;  /* bit[5]    : 0 = No derived MemManage fault has occurred.
                                                       1 = A derived MemManage fault occurred on exception entry. */
        unsigned int  reserved_1  : 1;  /* bit[6]    : Reserved */
        unsigned int  mmarvalid   : 1;  /* bit[7]    : 0 = MMAR does not have valid contents.
                                                       1 = MMAR has valid contents. */
        unsigned int  ibuserr     : 1;  /* bit[8]    : 0 = No bus fault on an instruction prefetch has occurred.
                                                       1 = A bus fault on an instruction prefetch has occurred. The fault is signalled only if the instruction is issued */
        unsigned int  preciserr   : 1;  /* bit[9]    : 0 = No precise data access error has occurred.
                                                       1 = A precise data access error has occurred, and the processor has written the faulting address to the BFAR */
        unsigned int  impreciserr : 1;  /* bit[10]   : 0 = No imprecise data access error has occurred.
                                                       1 = Imprecise data access error has occurred */
        unsigned int  unstkerr    : 1;  /* bit[11]   : 0 = No derived bus fault has occurred.
                                                       1 = A derived bus fault has occurred on exception return. */
        unsigned int  stkerr      : 1;  /* bit[12]   : 0 = No derived bus fault has occurred.
                                                       1 = A derived bus fault has occurred on exception entry. */
        unsigned int  lsperr      : 1;  /* bit[13]   : 0 = No bus fault occurred during FP lazy state preservation.
                                                       1 = A bus fault occurred during FP lazy state preservation. */
        unsigned int  reserved_2  : 1;  /* bit[14]   : Reserved */
        unsigned int  bfarvalid   : 1;  /* bit[15]   : 0 = BFAR does not have valid contents.
                                                       1 = BFAR has valid contents. */
        unsigned int  undefinstr  : 1;  /* bit[16]   : 0 = No Undefined Instruction Usage fault has occurred.
                                                       1 = The processor has attempted to execute an undefined instruction. This might be an undefined instruction associated with an enabled coprocessor */
        unsigned int  invstate    : 1;  /* bit[17]   : 0 = EPSR.T bit and EPSR.IT bits are valid for instruction execution.
                                                       1 = Instruction executed with invalid EPSR.T or EPSR.IT field. */
        unsigned int  invpc       : 1;  /* bit[18]   : 0 = No integrity check error has occurred.
                                                       1 = An integrity check error has occurred on EXC_RETURN.  */
        unsigned int  nocp        : 1;  /* bit[19]   : 0 = No coprocessor access error has occurred.
                                                       1 = A coprocessor access error has occurred. This shows that the coprocessor is disabled or not present */
        unsigned int  reserved_3  : 4;  /* bit[20-23]: Reserved */
        unsigned int  unaligned   : 1;  /* bit[24]   : 0 = No unaligned access error has occurred.
                                                       1 = Unaligned access error has occurred.
                                                       Multi-word accesses always fault if not word aligned. Software can configure 
                                                       unaligned word and halfword accesses to fault, by enabling UNALIGN_TRP in the 
                                                       CCR */
        unsigned int  divbyzero   : 1;  /* bit[25]   : 0 = No divide by zero error has occurred.
                                                       1 = Divide by zero error has occurred.
                                                       When SDIV or UDIV instruction is used with a divisor of 0, this fault occurs if DIV_0_TRP is enabled in the CCR */
        unsigned int  reserved_4  : 6;  /* bit[26-31]: Reserved */
    } reg;
} SOC_M3_SCS_CFSR_UNION;
#endif
#define SOC_M3_SCS_CFSR_iaccviol_START     (0)
#define SOC_M3_SCS_CFSR_iaccviol_END       (0)
#define SOC_M3_SCS_CFSR_daccviol_START     (1)
#define SOC_M3_SCS_CFSR_daccviol_END       (1)
#define SOC_M3_SCS_CFSR_munstkerr_START    (3)
#define SOC_M3_SCS_CFSR_munstkerr_END      (3)
#define SOC_M3_SCS_CFSR_mstkerr_START      (4)
#define SOC_M3_SCS_CFSR_mstkerr_END        (4)
#define SOC_M3_SCS_CFSR_mlsperr_START      (5)
#define SOC_M3_SCS_CFSR_mlsperr_END        (5)
#define SOC_M3_SCS_CFSR_mmarvalid_START    (7)
#define SOC_M3_SCS_CFSR_mmarvalid_END      (7)
#define SOC_M3_SCS_CFSR_ibuserr_START      (8)
#define SOC_M3_SCS_CFSR_ibuserr_END        (8)
#define SOC_M3_SCS_CFSR_preciserr_START    (9)
#define SOC_M3_SCS_CFSR_preciserr_END      (9)
#define SOC_M3_SCS_CFSR_impreciserr_START  (10)
#define SOC_M3_SCS_CFSR_impreciserr_END    (10)
#define SOC_M3_SCS_CFSR_unstkerr_START     (11)
#define SOC_M3_SCS_CFSR_unstkerr_END       (11)
#define SOC_M3_SCS_CFSR_stkerr_START       (12)
#define SOC_M3_SCS_CFSR_stkerr_END         (12)
#define SOC_M3_SCS_CFSR_lsperr_START       (13)
#define SOC_M3_SCS_CFSR_lsperr_END         (13)
#define SOC_M3_SCS_CFSR_bfarvalid_START    (15)
#define SOC_M3_SCS_CFSR_bfarvalid_END      (15)
#define SOC_M3_SCS_CFSR_undefinstr_START   (16)
#define SOC_M3_SCS_CFSR_undefinstr_END     (16)
#define SOC_M3_SCS_CFSR_invstate_START     (17)
#define SOC_M3_SCS_CFSR_invstate_END       (17)
#define SOC_M3_SCS_CFSR_invpc_START        (18)
#define SOC_M3_SCS_CFSR_invpc_END          (18)
#define SOC_M3_SCS_CFSR_nocp_START         (19)
#define SOC_M3_SCS_CFSR_nocp_END           (19)
#define SOC_M3_SCS_CFSR_unaligned_START    (24)
#define SOC_M3_SCS_CFSR_unaligned_END      (24)
#define SOC_M3_SCS_CFSR_divbyzero_START    (25)
#define SOC_M3_SCS_CFSR_divbyzero_END      (25)


/*****************************************************************************
 结构名    : SOC_M3_SCS_HFSR_UNION
 结构说明  : HFSR 寄存器结构定义。地址偏移量:0xD2C，初值:0x00000000，宽度:32
 寄存器说明: HardFault Status Register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 1;  /* bit[0]   : Reserved */
        unsigned int  vecttbl  : 1;  /* bit[1]   : Indicates when a fault has occurred because of a vector table read error on exception processing:
                                                   0 = No vector table read fault has occurred.
                                                   1 = Vector table read fault has occurred */
        unsigned int  reserved_1: 28; /* bit[2-29]: Reserved */
        unsigned int  forced   : 1;  /* bit[30]  : Indicates that a fault with configurable priority has been escalated to a HardFault exception, because it could not be made active, because of priority or because it was disabled:
                                                   0 = No priority escalation has occurred.
                                                   1 = Processor has escalated a configurable-priority exception to HardFault */
        unsigned int  debugevt : 1;  /* bit[31]  : Indicates when a Debug event has occurred:
                                                   0 = No Debug event has occurred.
                                                   1 = Debug event has occurred. The Debug Fault Status Register has been updated
                                                   The processor sets this bit to 1 only when halting debug is disabled and a Debug event occurs */
    } reg;
} SOC_M3_SCS_HFSR_UNION;
#endif
#define SOC_M3_SCS_HFSR_vecttbl_START   (1)
#define SOC_M3_SCS_HFSR_vecttbl_END     (1)
#define SOC_M3_SCS_HFSR_forced_START    (30)
#define SOC_M3_SCS_HFSR_forced_END      (30)
#define SOC_M3_SCS_HFSR_debugevt_START  (31)
#define SOC_M3_SCS_HFSR_debugevt_END    (31)


/*****************************************************************************
 结构名    : SOC_M3_SCS_DFSR_UNION
 结构说明  : DFSR 寄存器结构定义。地址偏移量:0xD30，初值:0x00000000，宽度:32
 寄存器说明: Debug Fault Status Register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  halted   : 1;  /* bit[0]   : 0 = No active halt request debug event.
                                                   1 = Halt request debug event active. */
        unsigned int  bkpt     : 1;  /* bit[1]   : Indicates a debug event generated by BKPT instruction execution or a breakpoint match in FPB:
                                                   0 = No current breakpoint debug event.
                                                   1 = At least one current breakpoint debug event. */
        unsigned int  dwttrap  : 1;  /* bit[2]   : Indicates a debug event generated by the DWT:
                                                   0 = No current debug events generated by the DWT.
                                                   1 = At least one current debug event generated by the DWT. */
        unsigned int  vcatch   : 1;  /* bit[3]   : Indicates triggering of a Vector catch:
                                                   0 = No Vector catch triggered.
                                                   1 = Vector catch triggered.
                                                   The corresponding FSR shows the primary cause of the exception. */
        unsigned int  external : 1;  /* bit[4]   : Indicates a debug event generated because of the assertion of EDBGRQ:
                                                   0 = No EDBGRQ debug event.
                                                   1 = EDBGRQ debug event. */
        unsigned int  reserved : 27; /* bit[5-31]: Reserved */
    } reg;
} SOC_M3_SCS_DFSR_UNION;
#endif
#define SOC_M3_SCS_DFSR_halted_START    (0)
#define SOC_M3_SCS_DFSR_halted_END      (0)
#define SOC_M3_SCS_DFSR_bkpt_START      (1)
#define SOC_M3_SCS_DFSR_bkpt_END        (1)
#define SOC_M3_SCS_DFSR_dwttrap_START   (2)
#define SOC_M3_SCS_DFSR_dwttrap_END     (2)
#define SOC_M3_SCS_DFSR_vcatch_START    (3)
#define SOC_M3_SCS_DFSR_vcatch_END      (3)
#define SOC_M3_SCS_DFSR_external_START  (4)
#define SOC_M3_SCS_DFSR_external_END    (4)


/*****************************************************************************
 结构名    : SOC_M3_SCS_MMFAR_UNION
 结构说明  : MMFAR 寄存器结构定义。地址偏移量:0xD34，初值:0x00000000，宽度:32
 寄存器说明: MemManage Fault Address Register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  address_mem : 32; /* bit[0-31]: Data address for an MPU fault.  */
    } reg;
} SOC_M3_SCS_MMFAR_UNION;
#endif
#define SOC_M3_SCS_MMFAR_address_mem_START  (0)
#define SOC_M3_SCS_MMFAR_address_mem_END    (31)


/*****************************************************************************
 结构名    : SOC_M3_SCS_BFAR_UNION
 结构说明  : BFAR 寄存器结构定义。地址偏移量:0xD38，初值:0x00000000，宽度:32
 寄存器说明: BusFault Address Register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  address_bus : 32; /* bit[0-31]: Data address for a precise bus fault. */
    } reg;
} SOC_M3_SCS_BFAR_UNION;
#endif
#define SOC_M3_SCS_BFAR_address_bus_START  (0)
#define SOC_M3_SCS_BFAR_address_bus_END    (31)


/*****************************************************************************
 结构名    : SOC_M3_SCS_AFSR_UNION
 结构说明  : AFSR 寄存器结构定义。地址偏移量:0xD3C，初值:0x00000000，宽度:32
 寄存器说明: Auxiliary Fault Status Register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  auxfault : 32; /* bit[0-31]: Latched version of the AUXFAULT inputs */
    } reg;
} SOC_M3_SCS_AFSR_UNION;
#endif
#define SOC_M3_SCS_AFSR_auxfault_START  (0)
#define SOC_M3_SCS_AFSR_auxfault_END    (31)


/*****************************************************************************
 结构名    : SOC_M3_SCS_ID_PFR0_UNION
 结构说明  : ID_PFR0 寄存器结构定义。地址偏移量:0xD40，初值:0x00000030，宽度:32
 寄存器说明: Processor Feature Register 0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ID_PFR0 : 32; /* bit[0-31]:  */
    } reg;
} SOC_M3_SCS_ID_PFR0_UNION;
#endif
#define SOC_M3_SCS_ID_PFR0_ID_PFR0_START  (0)
#define SOC_M3_SCS_ID_PFR0_ID_PFR0_END    (31)


/*****************************************************************************
 结构名    : SOC_M3_SCS_ID_PFR1_UNION
 结构说明  : ID_PFR1 寄存器结构定义。地址偏移量:0xD44，初值:0x00000200，宽度:32
 寄存器说明: Processor Feature Register 1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ID_PFR1 : 32; /* bit[0-31]:  */
    } reg;
} SOC_M3_SCS_ID_PFR1_UNION;
#endif
#define SOC_M3_SCS_ID_PFR1_ID_PFR1_START  (0)
#define SOC_M3_SCS_ID_PFR1_ID_PFR1_END    (31)


/*****************************************************************************
 结构名    : SOC_M3_SCS_ID_DFR0_UNION
 结构说明  : ID_DFR0 寄存器结构定义。地址偏移量:0xD48，初值:0x00100000，宽度:32
 寄存器说明: Debug Features Register 0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ID_DFR0 : 32; /* bit[0-31]:  */
    } reg;
} SOC_M3_SCS_ID_DFR0_UNION;
#endif
#define SOC_M3_SCS_ID_DFR0_ID_DFR0_START  (0)
#define SOC_M3_SCS_ID_DFR0_ID_DFR0_END    (31)


/*****************************************************************************
 结构名    : SOC_M3_SCS_ID_AFR0_UNION
 结构说明  : ID_AFR0 寄存器结构定义。地址偏移量:0xD4C，初值:0x00000000，宽度:32
 寄存器说明: Auxiliary Features Register 0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ID_AFR0 : 32; /* bit[0-31]:  */
    } reg;
} SOC_M3_SCS_ID_AFR0_UNION;
#endif
#define SOC_M3_SCS_ID_AFR0_ID_AFR0_START  (0)
#define SOC_M3_SCS_ID_AFR0_ID_AFR0_END    (31)


/*****************************************************************************
 结构名    : SOC_M3_SCS_ID_MMFR0_UNION
 结构说明  : ID_MMFR0 寄存器结构定义。地址偏移量:0xD50，初值:0x00100030，宽度:32
 寄存器说明: Memory Model Feature Register 0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ID_MMFR0 : 32; /* bit[0-31]:  */
    } reg;
} SOC_M3_SCS_ID_MMFR0_UNION;
#endif
#define SOC_M3_SCS_ID_MMFR0_ID_MMFR0_START  (0)
#define SOC_M3_SCS_ID_MMFR0_ID_MMFR0_END    (31)


/*****************************************************************************
 结构名    : SOC_M3_SCS_ID_MMFR1_UNION
 结构说明  : ID_MMFR1 寄存器结构定义。地址偏移量:0xD54，初值:0x00000000，宽度:32
 寄存器说明: Memory Model Feature Register 1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ID_MMFR1 : 32; /* bit[0-31]:  */
    } reg;
} SOC_M3_SCS_ID_MMFR1_UNION;
#endif
#define SOC_M3_SCS_ID_MMFR1_ID_MMFR1_START  (0)
#define SOC_M3_SCS_ID_MMFR1_ID_MMFR1_END    (31)


/*****************************************************************************
 结构名    : SOC_M3_SCS_ID_MMFR2_UNION
 结构说明  : ID_MMFR2 寄存器结构定义。地址偏移量:0xD58，初值:0x01000000，宽度:32
 寄存器说明: Memory Model Feature Register 2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ID_MMFR2 : 32; /* bit[0-31]:  */
    } reg;
} SOC_M3_SCS_ID_MMFR2_UNION;
#endif
#define SOC_M3_SCS_ID_MMFR2_ID_MMFR2_START  (0)
#define SOC_M3_SCS_ID_MMFR2_ID_MMFR2_END    (31)


/*****************************************************************************
 结构名    : SOC_M3_SCS_ID_MMFR3_UNION
 结构说明  : ID_MMFR3 寄存器结构定义。地址偏移量:0xD5C，初值:0x00000000，宽度:32
 寄存器说明: Memory Model Feature Register 3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ID_MMFR3 : 32; /* bit[0-31]:  */
    } reg;
} SOC_M3_SCS_ID_MMFR3_UNION;
#endif
#define SOC_M3_SCS_ID_MMFR3_ID_MMFR3_START  (0)
#define SOC_M3_SCS_ID_MMFR3_ID_MMFR3_END    (31)


/*****************************************************************************
 结构名    : SOC_M3_SCS_ID_ISAR0_UNION
 结构说明  : ID_ISAR0 寄存器结构定义。地址偏移量:0xD60，初值:0x01100110，宽度:32
 寄存器说明: Instruction Set Attributes Register 0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ID_ISAR0 : 32; /* bit[0-31]:  */
    } reg;
} SOC_M3_SCS_ID_ISAR0_UNION;
#endif
#define SOC_M3_SCS_ID_ISAR0_ID_ISAR0_START  (0)
#define SOC_M3_SCS_ID_ISAR0_ID_ISAR0_END    (31)


/*****************************************************************************
 结构名    : SOC_M3_SCS_ID_ISAR1_UNION
 结构说明  : ID_ISAR1 寄存器结构定义。地址偏移量:0xD64，初值:0x02111000，宽度:32
 寄存器说明: Instruction Set Attributes Register 1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ID_ISAR1 : 32; /* bit[0-31]:  */
    } reg;
} SOC_M3_SCS_ID_ISAR1_UNION;
#endif
#define SOC_M3_SCS_ID_ISAR1_ID_ISAR1_START  (0)
#define SOC_M3_SCS_ID_ISAR1_ID_ISAR1_END    (31)


/*****************************************************************************
 结构名    : SOC_M3_SCS_ID_ISAR2_UNION
 结构说明  : ID_ISAR2 寄存器结构定义。地址偏移量:0xD68，初值:0x21112231，宽度:32
 寄存器说明: Instruction Set Attributes Register 2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ID_ISAR2 : 32; /* bit[0-31]:  */
    } reg;
} SOC_M3_SCS_ID_ISAR2_UNION;
#endif
#define SOC_M3_SCS_ID_ISAR2_ID_ISAR2_START  (0)
#define SOC_M3_SCS_ID_ISAR2_ID_ISAR2_END    (31)


/*****************************************************************************
 结构名    : SOC_M3_SCS_ID_ISAR3_UNION
 结构说明  : ID_ISAR3 寄存器结构定义。地址偏移量:0xD6C，初值:0x01111110，宽度:32
 寄存器说明: Instruction Set Attributes Register 3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ID_ISAR3 : 32; /* bit[0-31]:  */
    } reg;
} SOC_M3_SCS_ID_ISAR3_UNION;
#endif
#define SOC_M3_SCS_ID_ISAR3_ID_ISAR3_START  (0)
#define SOC_M3_SCS_ID_ISAR3_ID_ISAR3_END    (31)


/*****************************************************************************
 结构名    : SOC_M3_SCS_ID_ISAR4_UNION
 结构说明  : ID_ISAR4 寄存器结构定义。地址偏移量:0xD70，初值:0x01310132，宽度:32
 寄存器说明: Instruction Set Attributes Register 4
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ID_ISAR4 : 32; /* bit[0-31]:  */
    } reg;
} SOC_M3_SCS_ID_ISAR4_UNION;
#endif
#define SOC_M3_SCS_ID_ISAR4_ID_ISAR4_START  (0)
#define SOC_M3_SCS_ID_ISAR4_ID_ISAR4_END    (31)


/*****************************************************************************
 结构名    : SOC_M3_SCS_CPACR_UNION
 结构说明  : CPACR 寄存器结构定义。地址偏移量:0xD88，初值:0x00000000，宽度:32
 寄存器说明: Coprocessor Access Control Register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  CPACR : 32; /* bit[0-31]:  */
    } reg;
} SOC_M3_SCS_CPACR_UNION;
#endif
#define SOC_M3_SCS_CPACR_CPACR_START  (0)
#define SOC_M3_SCS_CPACR_CPACR_END    (31)


/*****************************************************************************
 结构名    : SOC_M3_SCS_STIR_UNION
 结构说明  : STIR 寄存器结构定义。地址偏移量:0xF00，初值:0x00000000，宽度:32
 寄存器说明: Software Triggered Interrupt Register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  intid    : 9;  /* bit[0-8] : Indicates the interrupt to be triggered.The value written is (ExceptionNumber - 16) */
        unsigned int  reserved : 23; /* bit[9-31]: Reserved */
    } reg;
} SOC_M3_SCS_STIR_UNION;
#endif
#define SOC_M3_SCS_STIR_intid_START     (0)
#define SOC_M3_SCS_STIR_intid_END       (8)






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

#endif /* end of soc_m3_scs_interface.h */
