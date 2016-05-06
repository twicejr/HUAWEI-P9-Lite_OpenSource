/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_cs_stm_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-11-20 11:31:03
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年11月20日
    作    者   : l00352922
    修改内容   : 从《Hi3660V100 SOC寄存器手册_CS_STM.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_CS_STM_INTERFACE_H__
#define __SOC_CS_STM_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) STM
 ****************************************************************************/
/* 寄存器说明：STM DMA传输起始寄存器。
   位域定义UNION结构:  SOC_CS_STM_STM_DMASTARTR_UNION */
#define SOC_CS_STM_STM_DMASTARTR_ADDR(base)           ((base) + (0xC04))

/* 寄存器说明：STM DMA传输结束寄存器。
   位域定义UNION结构:  SOC_CS_STM_STM_DMASTOPR_UNION */
#define SOC_CS_STM_STM_DMASTOPR_ADDR(base)            ((base) + (0xC08))

/* 寄存器说明：STM DMA传输状态寄存器。
   位域定义UNION结构:  SOC_CS_STM_STM_DMASTATR_UNION */
#define SOC_CS_STM_STM_DMASTATR_ADDR(base)            ((base) + (0xC0C))

/* 寄存器说明：STM DMA控制寄存器。
   位域定义UNION结构:  SOC_CS_STM_STM_DMACTLR_UNION */
#define SOC_CS_STM_STM_DMACTLR_ADDR(base)             ((base) + (0xC10))

/* 寄存器说明：STM硬件事件使能寄存器。
   位域定义UNION结构:  SOC_CS_STM_STM_HEER_UNION */
#define SOC_CS_STM_STM_HEER_ADDR(base)                ((base) + (0xD00))

/* 寄存器说明：STM硬件事件trigger使能寄存器。
   位域定义UNION结构:  SOC_CS_STM_STM_HETER_UNION */
#define SOC_CS_STM_STM_HETER_ADDR(base)               ((base) + (0xD20))

/* 寄存器说明：STM硬件事件bank选择寄存器。
   位域定义UNION结构:  SOC_CS_STM_STM_HEBSR_UNION */
#define SOC_CS_STM_STM_HEBSR_ADDR(base)               ((base) + (0xD60))

/* 寄存器说明：STM硬件事件控制寄存器。
   位域定义UNION结构:  SOC_CS_STM_STM_HEMCR_UNION */
#define SOC_CS_STM_STM_HEMCR_ADDR(base)               ((base) + (0xD64))

/* 寄存器说明：STM硬件事件外部复用控制寄存器。
   位域定义UNION结构:  SOC_CS_STM_STM_HEEXTMUXR_UNION */
#define SOC_CS_STM_STM_HEEXTMUXR_ADDR(base)           ((base) + (0xD68))

/* 寄存器说明：STM硬件事件master个数指示寄存器。
   位域定义UNION结构:  SOC_CS_STM_STM_HEMASTR_UNION */
#define SOC_CS_STM_STM_HEMASTR_ADDR(base)             ((base) + (0xDF4))

/* 寄存器说明：STM硬件事件规格指示寄存器。
   位域定义UNION结构:  SOC_CS_STM_STM_HEFEAT1R_UNION */
#define SOC_CS_STM_STM_HEFEAT1R_ADDR(base)            ((base) + (0xDF8))

/* 寄存器说明：STM硬件事件ID指示寄存器。
   位域定义UNION结构:  SOC_CS_STM_STM_HEIDR_UNION */
#define SOC_CS_STM_STM_HEIDR_ADDR(base)               ((base) + (0xDFC))

/* 寄存器说明：STM激励端口使能寄存器。
   位域定义UNION结构:  SOC_CS_STM_STM_SPER_UNION */
#define SOC_CS_STM_STM_SPER_ADDR(base)                ((base) + (0xE00))

/* 寄存器说明：STM激励端口trigger使能寄存器。
   位域定义UNION结构:  SOC_CS_STM_STM_SPTER_UNION */
#define SOC_CS_STM_STM_SPTER_ADDR(base)               ((base) + (0xE20))

/* 寄存器说明：STM激励端口选择寄存器。
   位域定义UNION结构:  SOC_CS_STM_STM_SPSCR_UNION */
#define SOC_CS_STM_STM_SPSCR_ADDR(base)               ((base) + (0xE60))

/* 寄存器说明：STM激励端口master选择寄存器。
   位域定义UNION结构:  SOC_CS_STM_STM_SPMSCR_UNION */
#define SOC_CS_STM_STM_SPMSCR_ADDR(base)              ((base) + (0xE64))

/* 寄存器说明：STM激励端口override寄存器。
   位域定义UNION结构:  SOC_CS_STM_STM_SPOVERRIDER_UNION */
#define SOC_CS_STM_STM_SPOVERRIDER_ADDR(base)         ((base) + (0xE68))

/* 寄存器说明：STM激励端口master override寄存器。
   位域定义UNION结构:  SOC_CS_STM_STM_SPMOVERRIDER_UNION */
#define SOC_CS_STM_STM_SPMOVERRIDER_ADDR(base)        ((base) + (0xE6C))

/* 寄存器说明：STM激励端口trigger控制及状态寄存器。
   位域定义UNION结构:  SOC_CS_STM_STM_SPTRIGCSR_UNION */
#define SOC_CS_STM_STM_SPTRIGCSR_ADDR(base)           ((base) + (0xE70))

/* 寄存器说明：STM trace控制与状态寄存器。
   位域定义UNION结构:  SOC_CS_STM_STM_TCSR_UNION */
#define SOC_CS_STM_STM_TCSR_ADDR(base)                ((base) + (0xE80))

/* 寄存器说明：STM timestamp激励寄存器。
   位域定义UNION结构:  SOC_CS_STM_STM_TSSTIMR_UNION */
#define SOC_CS_STM_STM_TSSTIMR_ADDR(base)             ((base) + (0xE84))

/* 寄存器说明：STM timestamp频率寄存器。
   位域定义UNION结构:  SOC_CS_STM_STM_TSFREQR_UNION */
#define SOC_CS_STM_STM_TSFREQR_ADDR(base)             ((base) + (0xE8C))

/* 寄存器说明：STM同步控制寄存器。
   位域定义UNION结构:  SOC_CS_STM_STM_SYNCR_UNION */
#define SOC_CS_STM_STM_SYNCR_ADDR(base)               ((base) + (0xE90))

/* 寄存器说明：STM辅助控制寄存器。
   位域定义UNION结构:  SOC_CS_STM_STM_AUXCR_UNION */
#define SOC_CS_STM_STM_AUXCR_ADDR(base)               ((base) + (0xE94))

/* 寄存器说明：STM锁定访问寄存器。
   位域定义UNION结构:  SOC_CS_STM_STM_LAR_UNION */
#define SOC_CS_STM_STM_LAR_ADDR(base)                 ((base) + (0xFB0))

/* 寄存器说明：STM锁定状态寄存器。
   位域定义UNION结构:  SOC_CS_STM_STM_LSR_UNION */
#define SOC_CS_STM_STM_LSR_ADDR(base)                 ((base) + (0xFB4))

/* 寄存器说明：STM授权状态寄存器。
   位域定义UNION结构:  SOC_CS_STM_STM_AUTHSTATUS_UNION */
#define SOC_CS_STM_STM_AUTHSTATUS_ADDR(base)          ((base) + (0xFB8))





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
                     (1/1) STM
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_CS_STM_STM_DMASTARTR_UNION
 结构说明  : STM_DMASTARTR 寄存器结构定义。地址偏移量:0xC04，初值:0x00000000，宽度:32
 寄存器说明: STM DMA传输起始寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  start    : 1;  /* bit[0]   : Start a DMA transfer */
        unsigned int  reserved : 31; /* bit[1-31]:  */
    } reg;
} SOC_CS_STM_STM_DMASTARTR_UNION;
#endif
#define SOC_CS_STM_STM_DMASTARTR_start_START     (0)
#define SOC_CS_STM_STM_DMASTARTR_start_END       (0)


/*****************************************************************************
 结构名    : SOC_CS_STM_STM_DMASTOPR_UNION
 结构说明  : STM_DMASTOPR 寄存器结构定义。地址偏移量:0xC08，初值:0x00000000，宽度:32
 寄存器说明: STM DMA传输结束寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stop     : 1;  /* bit[0]   : Stop a DMA transfer */
        unsigned int  reserved : 31; /* bit[1-31]:  */
    } reg;
} SOC_CS_STM_STM_DMASTOPR_UNION;
#endif
#define SOC_CS_STM_STM_DMASTOPR_stop_START      (0)
#define SOC_CS_STM_STM_DMASTOPR_stop_END        (0)


/*****************************************************************************
 结构名    : SOC_CS_STM_STM_DMASTATR_UNION
 结构说明  : STM_DMASTATR 寄存器结构定义。地址偏移量:0xC0C，初值:0x00000000，宽度:32
 寄存器说明: STM DMA传输状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  status   : 1;  /* bit[0]   : Status of the DMA peripheral request interface:
                                                   0b0 Interface is idle.
                                                   0b1 Interface is active. */
        unsigned int  reserved : 31; /* bit[1-31]:  */
    } reg;
} SOC_CS_STM_STM_DMASTATR_UNION;
#endif
#define SOC_CS_STM_STM_DMASTATR_status_START    (0)
#define SOC_CS_STM_STM_DMASTATR_status_END      (0)


/*****************************************************************************
 结构名    : SOC_CS_STM_STM_DMACTLR_UNION
 结构说明  : STM_DMACTLR 寄存器结构定义。地址偏移量:0xC10，初值:0x00000000，宽度:32
 寄存器说明: STM DMA控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 2;  /* bit[0-1] : Reserved */
        unsigned int  sens     : 2;  /* bit[2-3] : Determines the sensitivity of the DMA request to the current buffer level in the STM:
                                                   0b00 Buffer is <25% full.
                                                   0b01 Buffer is <50% full.
                                                   0b10 Buffer is <75% full.
                                                   0b11 Buffer is <100% full. */
        unsigned int  reserved_1: 28; /* bit[4-31]: Reserved */
    } reg;
} SOC_CS_STM_STM_DMACTLR_UNION;
#endif
#define SOC_CS_STM_STM_DMACTLR_sens_START      (2)
#define SOC_CS_STM_STM_DMACTLR_sens_END        (3)


/*****************************************************************************
 结构名    : SOC_CS_STM_STM_HEER_UNION
 结构说明  : STM_HEER 寄存器结构定义。地址偏移量:0xD00，初值:0x00000000，宽度:32
 寄存器说明: STM硬件事件使能寄存器。
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
} SOC_CS_STM_STM_HEER_UNION;
#endif
#define SOC_CS_STM_STM_HEER_heen_START  (0)
#define SOC_CS_STM_STM_HEER_heen_END    (31)


/*****************************************************************************
 结构名    : SOC_CS_STM_STM_HETER_UNION
 结构说明  : STM_HETER 寄存器结构定义。地址偏移量:0xD20，初值:0x00000000，宽度:32
 寄存器说明: STM硬件事件trigger使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hete : 32; /* bit[0-31]: Bit mask to enable trigger generation from the hardware events, with one bit per hardware event:
                                               0b0 Disabled.
                                               0b1 Enabled. */
    } reg;
} SOC_CS_STM_STM_HETER_UNION;
#endif
#define SOC_CS_STM_STM_HETER_hete_START  (0)
#define SOC_CS_STM_STM_HETER_hete_END    (31)


/*****************************************************************************
 结构名    : SOC_CS_STM_STM_HEBSR_UNION
 结构说明  : STM_HEBSR 寄存器结构定义。地址偏移量:0xD60，初值:0x00000000，宽度:32
 寄存器说明: STM硬件事件bank选择寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hebs     : 1;  /* bit[0]   : Select a bank of 32 hardware events to control.
                                                   0x0, reads from and writes to the STMHEER and STMHETER correspond to hardware event 0-31.
                                                   0x1, reads from and writes to the STMHEER and STMHETER correspond to hardware event 32-63. */
        unsigned int  reserved : 31; /* bit[1-31]: Reserved */
    } reg;
} SOC_CS_STM_STM_HEBSR_UNION;
#endif
#define SOC_CS_STM_STM_HEBSR_hebs_START      (0)
#define SOC_CS_STM_STM_HEBSR_hebs_END        (0)


/*****************************************************************************
 结构名    : SOC_CS_STM_STM_HEMCR_UNION
 结构说明  : STM_HEMCR 寄存器结构定义。地址偏移量:0xD64，初值:0x00000000，宽度:32
 寄存器说明: STM硬件事件控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  en         : 1;  /* bit[0]   : Enable Hardware Event Tracing:
                                                     0b0 Disabled.
                                                     0b1 Enabled. */
        unsigned int  compen     : 1;  /* bit[1]   : Enable leading zero suppression of hardware event data values in the trace stream:
                                                     0b0 Disabled.
                                                     0b1 Enabled. */
        unsigned int  errdetect  : 1;  /* bit[2]   : Enable error detection on the hardware event tracing:
                                                     0b0 Disabled.
                                                     0b1 Enabled. */
        unsigned int  reserved_0 : 1;  /* bit[3]   : Reserved */
        unsigned int  trigctl    : 1;  /* bit[4]   : Trigger Control:
                                                     0b0 Triggers are multi-shot.
                                                     0b1 Triggers are single-shot */
        unsigned int  trigstatus : 1;  /* bit[5]   : When TRIGCTL indicates single-shot mode, this indicates whether the single trigger has occurred:
                                                     0b0 Trigger has not occurred.
                                                     0b1 Trigger has occurred. */
        unsigned int  trigclear  : 1;  /* bit[6]   : When TRIGCTL indicates single-shot mode, this bit is used to clear TRIGSTATUS:
                                                     0b0 No effect.
                                                     0b1 Clears TRIGSTATUS if TRIGSTATUS is 0b1. */
        unsigned int  atbtrigen  : 1;  /* bit[7]   : ATB trigger enable on events being monitored using the STMHETER. When set, this bit enables the STM to use the ATID value of 0x7D.  */
        unsigned int  reserved_1 : 24; /* bit[8-31]: Reserved */
    } reg;
} SOC_CS_STM_STM_HEMCR_UNION;
#endif
#define SOC_CS_STM_STM_HEMCR_en_START          (0)
#define SOC_CS_STM_STM_HEMCR_en_END            (0)
#define SOC_CS_STM_STM_HEMCR_compen_START      (1)
#define SOC_CS_STM_STM_HEMCR_compen_END        (1)
#define SOC_CS_STM_STM_HEMCR_errdetect_START   (2)
#define SOC_CS_STM_STM_HEMCR_errdetect_END     (2)
#define SOC_CS_STM_STM_HEMCR_trigctl_START     (4)
#define SOC_CS_STM_STM_HEMCR_trigctl_END       (4)
#define SOC_CS_STM_STM_HEMCR_trigstatus_START  (5)
#define SOC_CS_STM_STM_HEMCR_trigstatus_END    (5)
#define SOC_CS_STM_STM_HEMCR_trigclear_START   (6)
#define SOC_CS_STM_STM_HEMCR_trigclear_END     (6)
#define SOC_CS_STM_STM_HEMCR_atbtrigen_START   (7)
#define SOC_CS_STM_STM_HEMCR_atbtrigen_END     (7)


/*****************************************************************************
 结构名    : SOC_CS_STM_STM_HEEXTMUXR_UNION
 结构说明  : STM_HEEXTMUXR 寄存器结构定义。地址偏移量:0xD68，初值:0x00000000，宽度:32
 寄存器说明: STM硬件事件外部复用控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  extmux   : 8;  /* bit[0-7] : Provides a value to optional multiplexing logic, to control which hardware events are connected to the STM.  */
        unsigned int  reserved : 24; /* bit[8-31]: Reserved */
    } reg;
} SOC_CS_STM_STM_HEEXTMUXR_UNION;
#endif
#define SOC_CS_STM_STM_HEEXTMUXR_extmux_START    (0)
#define SOC_CS_STM_STM_HEEXTMUXR_extmux_END      (7)


/*****************************************************************************
 结构名    : SOC_CS_STM_STM_HEMASTR_UNION
 结构说明  : STM_HEMASTR 寄存器结构定义。地址偏移量:0xDF4，初值:0x00000080，宽度:32
 寄存器说明: STM硬件事件master个数指示寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  master   : 16; /* bit[0-15] : The STPv2 master number for the hardware event trace:
                                                    0x80 Hardware events are associated with master ID 0x80. */
        unsigned int  reserved : 16; /* bit[16-31]: Reserved */
    } reg;
} SOC_CS_STM_STM_HEMASTR_UNION;
#endif
#define SOC_CS_STM_STM_HEMASTR_master_START    (0)
#define SOC_CS_STM_STM_HEMASTR_master_END      (15)


/*****************************************************************************
 结构名    : SOC_CS_STM_STM_HEFEAT1R_UNION
 结构说明  : STM_HEFEAT1R 寄存器结构定义。地址偏移量:0xDF8，初值:0x30400035，宽度:32
 寄存器说明: STM硬件事件规格指示寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  heter        : 1;  /* bit[0]    : Specifies the STMHETER support:
                                                        0b1 Implemented. */
        unsigned int  reserved_0   : 1;  /* bit[1]    : Reserved */
        unsigned int  heerr        : 1;  /* bit[2]    : Hardware event error detection support:
                                                        0b1 Implemented. The STM implements the STMHEMCR.ERRDETECT bit. */
        unsigned int  hemaster     : 1;  /* bit[3]    : Specifies the STMHEMASTR support:
                                                        0b0 The STMHEMASTR is read-only. */
        unsigned int  hecomp       : 2;  /* bit[4-5]  : Data compression on hardware event tracing support:
                                                        0b11 Programmable data compression support. The STM implements the 
                                                        STMHEMCR.COMPEN bit. */
        unsigned int  reserved_1   : 9;  /* bit[6-14] : Reserved */
        unsigned int  numhe        : 9;  /* bit[15-23]: The number of hardware events supported by the STM:
                                                        0b001000000 64 hardware events */
        unsigned int  reserved_2   : 4;  /* bit[24-27]: Reserved */
        unsigned int  heextmuxsize : 3;  /* bit[28-30]: The size of the STMHEEXTMUXR.EXTMUX bit field:
                                                        0b011 8 bits wide. */
        unsigned int  reserved_3   : 1;  /* bit[31]   : Reserved */
    } reg;
} SOC_CS_STM_STM_HEFEAT1R_UNION;
#endif
#define SOC_CS_STM_STM_HEFEAT1R_heter_START         (0)
#define SOC_CS_STM_STM_HEFEAT1R_heter_END           (0)
#define SOC_CS_STM_STM_HEFEAT1R_heerr_START         (2)
#define SOC_CS_STM_STM_HEFEAT1R_heerr_END           (2)
#define SOC_CS_STM_STM_HEFEAT1R_hemaster_START      (3)
#define SOC_CS_STM_STM_HEFEAT1R_hemaster_END        (3)
#define SOC_CS_STM_STM_HEFEAT1R_hecomp_START        (4)
#define SOC_CS_STM_STM_HEFEAT1R_hecomp_END          (5)
#define SOC_CS_STM_STM_HEFEAT1R_numhe_START         (15)
#define SOC_CS_STM_STM_HEFEAT1R_numhe_END           (23)
#define SOC_CS_STM_STM_HEFEAT1R_heextmuxsize_START  (28)
#define SOC_CS_STM_STM_HEFEAT1R_heextmuxsize_END    (30)


/*****************************************************************************
 结构名    : SOC_CS_STM_STM_HEIDR_UNION
 结构说明  : STM_HEIDR 寄存器结构定义。地址偏移量:0xDFC，初值:0x00000011，宽度:32
 寄存器说明: STM硬件事件ID指示寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  class    : 4;  /* bit[0-3]  : Identifies the programmers model:
                                                    0b0001 Hardware event control. */
        unsigned int  classrev : 4;  /* bit[4-7]  : Identifies the revision of the programmers model:
                                                    0b0001 Revision. */
        unsigned int  vendspec : 4;  /* bit[8-11] : Identifies vendor-specific modifications or mappings:
                                                    0b0000 Vendor-specific information */
        unsigned int  reserved : 20; /* bit[12-31]: Reserved */
    } reg;
} SOC_CS_STM_STM_HEIDR_UNION;
#endif
#define SOC_CS_STM_STM_HEIDR_class_START     (0)
#define SOC_CS_STM_STM_HEIDR_class_END       (3)
#define SOC_CS_STM_STM_HEIDR_classrev_START  (4)
#define SOC_CS_STM_STM_HEIDR_classrev_END    (7)
#define SOC_CS_STM_STM_HEIDR_vendspec_START  (8)
#define SOC_CS_STM_STM_HEIDR_vendspec_END    (11)


/*****************************************************************************
 结构名    : SOC_CS_STM_STM_SPER_UNION
 结构说明  : STM_SPER 寄存器结构定义。地址偏移量:0xE00，初值:0x00000000，宽度:32
 寄存器说明: STM激励端口使能寄存器。
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
} SOC_CS_STM_STM_SPER_UNION;
#endif
#define SOC_CS_STM_STM_SPER_spe_START  (0)
#define SOC_CS_STM_STM_SPER_spe_END    (31)


/*****************************************************************************
 结构名    : SOC_CS_STM_STM_SPTER_UNION
 结构说明  : STM_SPTER 寄存器结构定义。地址偏移量:0xE20，初值:0x00000000，宽度:32
 寄存器说明: STM激励端口trigger使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  spte : 32; /* bit[0-31]: Bit mask to enable trigger generation from the stimulus port registers, with one bit per stimulus port register:
                                               0b0 Disabled.
                                               0b1 Enabled. */
    } reg;
} SOC_CS_STM_STM_SPTER_UNION;
#endif
#define SOC_CS_STM_STM_SPTER_spte_START  (0)
#define SOC_CS_STM_STM_SPTER_spte_END    (31)


/*****************************************************************************
 结构名    : SOC_CS_STM_STM_SPSCR_UNION
 结构说明  : STM_SPSCR 寄存器结构定义。地址偏移量:0xE60，初值:0x00000000，宽度:32
 寄存器说明: STM激励端口选择寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  portctl  : 2;  /* bit[0-1]  : This defines how the port selection is applied:
                                                    0b00 Port selection not used.
                                                    0b01 Port selection applies only to the STMSPTER.
                                                    0b10 Reserved.
                                                    0b11 Port selection applies to both the STMSPER and STMSPTER. */
        unsigned int  reserved : 18; /* bit[2-19] : Reserved */
        unsigned int  portsel  : 12; /* bit[20-31]: Port Selection. This field defines which stimulus ports the STMSPER and/or STMSPTER apply to.  */
    } reg;
} SOC_CS_STM_STM_SPSCR_UNION;
#endif
#define SOC_CS_STM_STM_SPSCR_portctl_START   (0)
#define SOC_CS_STM_STM_SPSCR_portctl_END     (1)
#define SOC_CS_STM_STM_SPSCR_portsel_START   (20)
#define SOC_CS_STM_STM_SPSCR_portsel_END     (31)


/*****************************************************************************
 结构名    : SOC_CS_STM_STM_SPMSCR_UNION
 结构说明  : STM_SPMSCR 寄存器结构定义。地址偏移量:0xE64，初值:0x00000000，宽度:32
 寄存器说明: STM激励端口master选择寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mastctl  : 1;  /* bit[0]    : This bit defines how the master is applied: 
                                                    0b0 Master selection not used.
                                                    0b1 Master selection applies to the STMSPSCR. */
        unsigned int  reserved : 14; /* bit[1-14] : Reserved */
        unsigned int  mastsel  : 17; /* bit[15-31]: Master Selection. This field defines which master the STMSPSCR applies to. */
    } reg;
} SOC_CS_STM_STM_SPMSCR_UNION;
#endif
#define SOC_CS_STM_STM_SPMSCR_mastctl_START   (0)
#define SOC_CS_STM_STM_SPMSCR_mastctl_END     (0)
#define SOC_CS_STM_STM_SPMSCR_mastsel_START   (15)
#define SOC_CS_STM_STM_SPMSCR_mastsel_END     (31)


/*****************************************************************************
 结构名    : SOC_CS_STM_STM_SPOVERRIDER_UNION
 结构说明  : STM_SPOVERRIDER 寄存器结构定义。地址偏移量:0xE68，初值:0x00000000，宽度:32
 寄存器说明: STM激励端口override寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  overctl  : 2;  /* bit[0-1]  : This defines how the port selection is applied:
                                                    0b00 Override controls disabled.
                                                    0b01 Ports selected by PORTSEL always behave as guaranteed transactions.
                                                    0b10 Ports selected by PORTSEL always behave as invariant timing transactions.
                                                    0b11 Reserved. */
        unsigned int  overts   : 1;  /* bit[2]    : Timestamping override.
                                                    This override requests all stimulus port writes that cause trace to be traced with a timestamp (where 
                                                    possible). As with normal operation, this does not ensure all packets are generated with timestamps.
                                                    0b0 Override not enabled.
                                                    0b1 Override enabled. */
        unsigned int  reserved : 12; /* bit[3-14] : Reserved */
        unsigned int  portsel  : 17; /* bit[15-31]: Port selection. 
                                                    This field defines which stimulus ports the override controls apply to. */
    } reg;
} SOC_CS_STM_STM_SPOVERRIDER_UNION;
#endif
#define SOC_CS_STM_STM_SPOVERRIDER_overctl_START   (0)
#define SOC_CS_STM_STM_SPOVERRIDER_overctl_END     (1)
#define SOC_CS_STM_STM_SPOVERRIDER_overts_START    (2)
#define SOC_CS_STM_STM_SPOVERRIDER_overts_END      (2)
#define SOC_CS_STM_STM_SPOVERRIDER_portsel_START   (15)
#define SOC_CS_STM_STM_SPOVERRIDER_portsel_END     (31)


/*****************************************************************************
 结构名    : SOC_CS_STM_STM_SPMOVERRIDER_UNION
 结构说明  : STM_SPMOVERRIDER 寄存器结构定义。地址偏移量:0xE6C，初值:0x00000000，宽度:32
 寄存器说明: STM激励端口master override寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mastctl  : 1;  /* bit[0]    : This bit defines how the master selection is applied:
                                                    0b0 Master selection not enabled. STMSPOVERRIDER applies equally to all masters.
                                                    0b1 Master selection enabled. STMSPOVERRIDER applies to the masters selected by MASTSEL. */
        unsigned int  reserved : 14; /* bit[1-14] : Reserved */
        unsigned int  mastsel  : 17; /* bit[15-31]: Master selection.
                                                    This field defines which master the override controls apply to. */
    } reg;
} SOC_CS_STM_STM_SPMOVERRIDER_UNION;
#endif
#define SOC_CS_STM_STM_SPMOVERRIDER_mastctl_START   (0)
#define SOC_CS_STM_STM_SPMOVERRIDER_mastctl_END     (0)
#define SOC_CS_STM_STM_SPMOVERRIDER_mastsel_START   (15)
#define SOC_CS_STM_STM_SPMOVERRIDER_mastsel_END     (31)


/*****************************************************************************
 结构名    : SOC_CS_STM_STM_SPTRIGCSR_UNION
 结构说明  : STM_SPTRIGCSR 寄存器结构定义。地址偏移量:0xE70，初值:0x00000000，宽度:32
 寄存器说明: STM激励端口trigger控制及状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  trigctl       : 1;  /* bit[0]   : Trigger control:
                                                        0b0 Triggers are multi-shot.
                                                        0b1 Triggers are single-shot */
        unsigned int  trigstatus    : 1;  /* bit[1]   : When TRIGCTL indicates single-shot mode, this bit indicates whether the single trigger has occurred:
                                                        0b0 Trigger has not occurred.
                                                        0b1 Trigger has occurred */
        unsigned int  trigclear     : 1;  /* bit[2]   : When TRIGCTL indicates single-shot mode, this bit is used to clear TRIGSTATUS:
                                                        0b0 No effect.
                                                        0b1 Clears TRIGSTATUS if TRIGSTATUS is 0b1 */
        unsigned int  atbtrigen_te  : 1;  /* bit[3]   : ATB trigger enable on writes to Stimulus Ports being monitored using the STMSPTER. 
                                                        When set, this bit enables the STM to use the ATID value of 0x7D when software writes to an enabled Stimulus Port.  */
        unsigned int  atbtrigen_dir : 1;  /* bit[4]   : ATB trigger enable on direct writes to TRIG locations in an Extended Stimulus Port. When set, this bit enables the STM to use the ATID value of 0x7D when software writes to the TRIG locations.  */
        unsigned int  reserved      : 27; /* bit[5-31]: Reserved */
    } reg;
} SOC_CS_STM_STM_SPTRIGCSR_UNION;
#endif
#define SOC_CS_STM_STM_SPTRIGCSR_trigctl_START        (0)
#define SOC_CS_STM_STM_SPTRIGCSR_trigctl_END          (0)
#define SOC_CS_STM_STM_SPTRIGCSR_trigstatus_START     (1)
#define SOC_CS_STM_STM_SPTRIGCSR_trigstatus_END       (1)
#define SOC_CS_STM_STM_SPTRIGCSR_trigclear_START      (2)
#define SOC_CS_STM_STM_SPTRIGCSR_trigclear_END        (2)
#define SOC_CS_STM_STM_SPTRIGCSR_atbtrigen_te_START   (3)
#define SOC_CS_STM_STM_SPTRIGCSR_atbtrigen_te_END     (3)
#define SOC_CS_STM_STM_SPTRIGCSR_atbtrigen_dir_START  (4)
#define SOC_CS_STM_STM_SPTRIGCSR_atbtrigen_dir_END    (4)


/*****************************************************************************
 结构名    : SOC_CS_STM_STM_TCSR_UNION
 结构说明  : STM_TCSR 寄存器结构定义。地址偏移量:0xE80，初值:0x00000004，宽度:32
 寄存器说明: STM trace控制与状态寄存器。
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
} SOC_CS_STM_STM_TCSR_UNION;
#endif
#define SOC_CS_STM_STM_TCSR_en_START        (0)
#define SOC_CS_STM_STM_TCSR_en_END          (0)
#define SOC_CS_STM_STM_TCSR_tsen_START      (1)
#define SOC_CS_STM_STM_TCSR_tsen_END        (1)
#define SOC_CS_STM_STM_TCSR_syncen_START    (2)
#define SOC_CS_STM_STM_TCSR_syncen_END      (2)
#define SOC_CS_STM_STM_TCSR_compen_START    (5)
#define SOC_CS_STM_STM_TCSR_compen_END      (5)
#define SOC_CS_STM_STM_TCSR_traceid_START   (16)
#define SOC_CS_STM_STM_TCSR_traceid_END     (22)
#define SOC_CS_STM_STM_TCSR_busy_START      (23)
#define SOC_CS_STM_STM_TCSR_busy_END        (23)


/*****************************************************************************
 结构名    : SOC_CS_STM_STM_TSSTIMR_UNION
 结构说明  : STM_TSSTIMR 寄存器结构定义。地址偏移量:0xE84，初值:0x00000000，宽度:32
 寄存器说明: STM timestamp激励寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  forcets  : 1;  /* bit[0]   : Force timestamp stimulus. A write to this register with this bit as 0b1 requests the next stimulus port write which causes trace to be upgraded to have a timestamp. */
        unsigned int  reserved : 31; /* bit[1-31]: Reserved */
    } reg;
} SOC_CS_STM_STM_TSSTIMR_UNION;
#endif
#define SOC_CS_STM_STM_TSSTIMR_forcets_START   (0)
#define SOC_CS_STM_STM_TSSTIMR_forcets_END     (0)


/*****************************************************************************
 结构名    : SOC_CS_STM_STM_TSFREQR_UNION
 结构说明  : STM_TSFREQR 寄存器结构定义。地址偏移量:0xE8C，初值:0x00000000，宽度:32
 寄存器说明: STM timestamp频率寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  freq : 32; /* bit[0-31]: The timestamp frequency in Hz */
    } reg;
} SOC_CS_STM_STM_TSFREQR_UNION;
#endif
#define SOC_CS_STM_STM_TSFREQR_freq_START  (0)
#define SOC_CS_STM_STM_TSFREQR_freq_END    (31)


/*****************************************************************************
 结构名    : SOC_CS_STM_STM_SYNCR_UNION
 结构说明  : STM_SYNCR 寄存器结构定义。地址偏移量:0xE90，初值:0x00000000，宽度:32
 寄存器说明: STM同步控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  count    : 12; /* bit[0-11] : Counter value for the number of bytes between synchronization packets.  */
        unsigned int  mode     : 1;  /* bit[12]   : Mode control:
                                                    0b0 COUNT[11:0] defines a value N. Synchronization period is N bytes.
                                                    0b1 COUNT[11:7] defines a value N. Synchronization period is 2^N bytes. N must be in the range of 
                                                    12 to 27 inclusive and other values are UNPREDICTABLE.  */
        unsigned int  reserved : 19; /* bit[13-31]: Reserved */
    } reg;
} SOC_CS_STM_STM_SYNCR_UNION;
#endif
#define SOC_CS_STM_STM_SYNCR_count_START     (0)
#define SOC_CS_STM_STM_SYNCR_count_END       (11)
#define SOC_CS_STM_STM_SYNCR_mode_START      (12)
#define SOC_CS_STM_STM_SYNCR_mode_END        (12)


/*****************************************************************************
 结构名    : SOC_CS_STM_STM_AUXCR_UNION
 结构说明  : STM_AUXCR 寄存器结构定义。地址偏移量:0xE94，初值:0x00000000，宽度:32
 寄存器说明: STM辅助控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fifoaf        : 1;  /* bit[0]   : Auto-flush:
                                                        0b0 Disabled.
                                                        0b1 Enabled. The STM automatically drains all data even if the ATB interface is not fully utilized. */
        unsigned int  asyncpe       : 1;  /* bit[1]   : ASYNC priority:
                                                        0b0 Always lower than trace.
                                                        0b1 Escalates on second synchronization request. */
        unsigned int  priorinvdis   : 1;  /* bit[2]   : Controls arbitration between the AXI interface and the hardware event observation interface during flush:
                                                        0b0 Priority inversion. When the AXI flush completes, the hardware event observation interface gets priority until the hardware event observation interface flush completes.
                                                        0b1 Priority inversion disabled. The AXI always has priority over the hardware event observation interface. */
        unsigned int  reserved_0    : 4;  /* bit[3-6] : Reserved */
        unsigned int  qhwevoverride : 1;  /* bit[7]   : Low-power interface override when hardware event tracing is enabled:
                                                        0b0 The STM can accept a quiescence request on the STM low-power interface when the STMHEMCR.EN bit is set to 0b1.
                                                        0b1 If the STMHEMCR.EN bit is set to 0b1, all quiescence requests on the STM low-power interface are denied. */
        unsigned int  reserved_1    : 24; /* bit[8-31]: Reserved */
    } reg;
} SOC_CS_STM_STM_AUXCR_UNION;
#endif
#define SOC_CS_STM_STM_AUXCR_fifoaf_START         (0)
#define SOC_CS_STM_STM_AUXCR_fifoaf_END           (0)
#define SOC_CS_STM_STM_AUXCR_asyncpe_START        (1)
#define SOC_CS_STM_STM_AUXCR_asyncpe_END          (1)
#define SOC_CS_STM_STM_AUXCR_priorinvdis_START    (2)
#define SOC_CS_STM_STM_AUXCR_priorinvdis_END      (2)
#define SOC_CS_STM_STM_AUXCR_qhwevoverride_START  (7)
#define SOC_CS_STM_STM_AUXCR_qhwevoverride_END    (7)


/*****************************************************************************
 结构名    : SOC_CS_STM_STM_LAR_UNION
 结构说明  : STM_LAR 寄存器结构定义。地址偏移量:0xFB0，初值:0x00000000，宽度:32
 寄存器说明: STM锁定访问寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  key : 32; /* bit[0-31]: 写入0xC5ACCE55进行解锁，然后才可以正常配置其他寄存器；写入其他任何值后再次锁定。 */
    } reg;
} SOC_CS_STM_STM_LAR_UNION;
#endif
#define SOC_CS_STM_STM_LAR_key_START  (0)
#define SOC_CS_STM_STM_LAR_key_END    (31)


/*****************************************************************************
 结构名    : SOC_CS_STM_STM_LSR_UNION
 结构说明  : STM_LSR 寄存器结构定义。地址偏移量:0xFB4，初值:0x00000003，宽度:32
 寄存器说明: STM锁定状态寄存器。
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
} SOC_CS_STM_STM_LSR_UNION;
#endif
#define SOC_CS_STM_STM_LSR_sli_START       (0)
#define SOC_CS_STM_STM_LSR_sli_END         (0)
#define SOC_CS_STM_STM_LSR_slk_START       (1)
#define SOC_CS_STM_STM_LSR_slk_END         (1)
#define SOC_CS_STM_STM_LSR_ntt_START       (2)
#define SOC_CS_STM_STM_LSR_ntt_END         (2)


/*****************************************************************************
 结构名    : SOC_CS_STM_STM_AUTHSTATUS_UNION
 结构说明  : STM_AUTHSTATUS 寄存器结构定义。地址偏移量:0xFB8，初值:0x000000AA，宽度:32
 寄存器说明: STM授权状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  nsid     : 2;  /* bit[0-1] : Indicates the security level for non-secure invasive debug:
                                                   0b10 Disabled.
                                                   0b11 Enabled. */
        unsigned int  nsnid    : 2;  /* bit[2-3] : Indicates the security level for non-secure non-invasive debug:
                                                   0b10 Disabled.
                                                   0b11 Enabled. */
        unsigned int  sid      : 2;  /* bit[4-5] : Indicates the security level for Secure invasive debug:
                                                   0b10 Disabled.
                                                   0b11 Enabled. */
        unsigned int  snid     : 2;  /* bit[6-7] : Indicates the security level for Secure non-invasive debug:
                                                   0b10 Disabled.
                                                   0b11 Enabled. */
        unsigned int  reserved : 24; /* bit[8-31]: Reserved */
    } reg;
} SOC_CS_STM_STM_AUTHSTATUS_UNION;
#endif
#define SOC_CS_STM_STM_AUTHSTATUS_nsid_START      (0)
#define SOC_CS_STM_STM_AUTHSTATUS_nsid_END        (1)
#define SOC_CS_STM_STM_AUTHSTATUS_nsnid_START     (2)
#define SOC_CS_STM_STM_AUTHSTATUS_nsnid_END       (3)
#define SOC_CS_STM_STM_AUTHSTATUS_sid_START       (4)
#define SOC_CS_STM_STM_AUTHSTATUS_sid_END         (5)
#define SOC_CS_STM_STM_AUTHSTATUS_snid_START      (6)
#define SOC_CS_STM_STM_AUTHSTATUS_snid_END        (7)






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

#endif /* end of soc_cs_stm_interface.h */
