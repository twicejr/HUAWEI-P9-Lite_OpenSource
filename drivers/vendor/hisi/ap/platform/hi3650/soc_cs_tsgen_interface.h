/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_cs_tsgen_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-11-20 11:31:19
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年11月20日
    作    者   : l00352922
    修改内容   : 从《Hi3660V100 SOC寄存器手册_CS_TSGEN.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_CS_TSGEN_INTERFACE_H__
#define __SOC_CS_TSGEN_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) TSGEN
 ****************************************************************************/
/* 寄存器说明：timestamp计数控制寄存器。
   位域定义UNION结构:  SOC_CS_TSGEN_TS_CNTCR_UNION */
#define SOC_CS_TSGEN_TS_CNTCR_ADDR(base)              ((base) + (0x0000))

/* 寄存器说明：timestamp计数状态寄存器。
   位域定义UNION结构:  SOC_CS_TSGEN_TS_CNTSR_UNION */
#define SOC_CS_TSGEN_TS_CNTSR_ADDR(base)              ((base) + (0x0004))

/* 寄存器说明：timestamp当前计数值低位寄存器。
   位域定义UNION结构:  SOC_CS_TSGEN_TS_CNTCVLW_UNION */
#define SOC_CS_TSGEN_TS_CNTCVLW_ADDR(base)            ((base) + (0x0008))

/* 寄存器说明：timestamp当前计数值高位寄存器。
   位域定义UNION结构:  SOC_CS_TSGEN_TS_CNTCVUP_UNION */
#define SOC_CS_TSGEN_TS_CNTCVUP_ADDR(base)            ((base) + (0x000C))

/* 寄存器说明：timestamp计数频率寄存器。
   位域定义UNION结构:  SOC_CS_TSGEN_TS_CNTFID0_UNION */
#define SOC_CS_TSGEN_TS_CNTFID0_ADDR(base)            ((base) + (0x0020))

/* 寄存器说明：timestamp当前计数值低位寄存器。
   位域定义UNION结构:  SOC_CS_TSGEN_TSCNTCVLW_RO_UNION */
#define SOC_CS_TSGEN_TSCNTCVLW_RO_ADDR(base)          ((base) + (0x1000))

/* 寄存器说明：timestamp当前计数值高位寄存器。
   位域定义UNION结构:  SOC_CS_TSGEN_TSCNTCVUP_RO_UNION */
#define SOC_CS_TSGEN_TSCNTCVUP_RO_ADDR(base)          ((base) + (0x1004))





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
                     (1/1) TSGEN
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_CS_TSGEN_TS_CNTCR_UNION
 结构说明  : TS_CNTCR 寄存器结构定义。地址偏移量:0x0000，初值:0x00000000，宽度:32
 寄存器说明: timestamp计数控制寄存器。
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
} SOC_CS_TSGEN_TS_CNTCR_UNION;
#endif
#define SOC_CS_TSGEN_TS_CNTCR_en_START        (0)
#define SOC_CS_TSGEN_TS_CNTCR_en_END          (0)
#define SOC_CS_TSGEN_TS_CNTCR_hdbg_START      (1)
#define SOC_CS_TSGEN_TS_CNTCR_hdbg_END        (1)


/*****************************************************************************
 结构名    : SOC_CS_TSGEN_TS_CNTSR_UNION
 结构说明  : TS_CNTSR 寄存器结构定义。地址偏移量:0x0004，初值:0x00000000，宽度:32
 寄存器说明: timestamp计数状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 1;  /* bit[0]   : Reserved */
        unsigned int  dbgh     : 1;  /* bit[1]   : Debug Halted. */
        unsigned int  reserved_1: 30; /* bit[2-31]: Reserved */
    } reg;
} SOC_CS_TSGEN_TS_CNTSR_UNION;
#endif
#define SOC_CS_TSGEN_TS_CNTSR_dbgh_START      (1)
#define SOC_CS_TSGEN_TS_CNTSR_dbgh_END        (1)


/*****************************************************************************
 结构名    : SOC_CS_TSGEN_TS_CNTCVLW_UNION
 结构说明  : TS_CNTCVLW 寄存器结构定义。地址偏移量:0x0008，初值:0x00000000，宽度:32
 寄存器说明: timestamp当前计数值低位寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cntcvlw : 32; /* bit[0-31]: 当前计数值的bit[31:0] */
    } reg;
} SOC_CS_TSGEN_TS_CNTCVLW_UNION;
#endif
#define SOC_CS_TSGEN_TS_CNTCVLW_cntcvlw_START  (0)
#define SOC_CS_TSGEN_TS_CNTCVLW_cntcvlw_END    (31)


/*****************************************************************************
 结构名    : SOC_CS_TSGEN_TS_CNTCVUP_UNION
 结构说明  : TS_CNTCVUP 寄存器结构定义。地址偏移量:0x000C，初值:0x00000000，宽度:32
 寄存器说明: timestamp当前计数值高位寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cntcvup : 32; /* bit[0-31]: 当前计数值的bit[63:32] */
    } reg;
} SOC_CS_TSGEN_TS_CNTCVUP_UNION;
#endif
#define SOC_CS_TSGEN_TS_CNTCVUP_cntcvup_START  (0)
#define SOC_CS_TSGEN_TS_CNTCVUP_cntcvup_END    (31)


/*****************************************************************************
 结构名    : SOC_CS_TSGEN_TS_CNTFID0_UNION
 结构说明  : TS_CNTFID0 寄存器结构定义。地址偏移量:0x0020，初值:0x00000000，宽度:32
 寄存器说明: timestamp计数频率寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  freq : 32; /* bit[0-31]: Frequency in number of ticks per second. For example, for a 50 MHz 
                                               clock, program 0x02FAF080. */
    } reg;
} SOC_CS_TSGEN_TS_CNTFID0_UNION;
#endif
#define SOC_CS_TSGEN_TS_CNTFID0_freq_START  (0)
#define SOC_CS_TSGEN_TS_CNTFID0_freq_END    (31)


/*****************************************************************************
 结构名    : SOC_CS_TSGEN_TSCNTCVLW_RO_UNION
 结构说明  : TSCNTCVLW_RO 寄存器结构定义。地址偏移量:0x1000，初值:0x00000000，宽度:32
 寄存器说明: timestamp当前计数值低位寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cntcvlw_ro : 32; /* bit[0-31]: 当前计数值的bit[31:0]，只读属性 */
    } reg;
} SOC_CS_TSGEN_TSCNTCVLW_RO_UNION;
#endif
#define SOC_CS_TSGEN_TSCNTCVLW_RO_cntcvlw_ro_START  (0)
#define SOC_CS_TSGEN_TSCNTCVLW_RO_cntcvlw_ro_END    (31)


/*****************************************************************************
 结构名    : SOC_CS_TSGEN_TSCNTCVUP_RO_UNION
 结构说明  : TSCNTCVUP_RO 寄存器结构定义。地址偏移量:0x1004，初值:0x00000000，宽度:32
 寄存器说明: timestamp当前计数值高位寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cntcvup_ro : 32; /* bit[0-31]: 当前计数值的bit[63:32]，只读属性 */
    } reg;
} SOC_CS_TSGEN_TSCNTCVUP_RO_UNION;
#endif
#define SOC_CS_TSGEN_TSCNTCVUP_RO_cntcvup_ro_START  (0)
#define SOC_CS_TSGEN_TSCNTCVUP_RO_cntcvup_ro_END    (31)






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

#endif /* end of soc_cs_tsgen_interface.h */
