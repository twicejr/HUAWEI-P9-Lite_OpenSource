/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_cs_ap_etf_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-11-20 13:57:03
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年11月20日
    作    者   : l00352922
    修改内容   : 从《Hi3660V100 SOC寄存器手册_CS_AP_ETF.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_CS_AP_ETF_INTERFACE_H__
#define __SOC_CS_AP_ETF_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) AP_ETF
 ****************************************************************************/
/* 寄存器说明：ETF RAM size寄存器。
   位域定义UNION结构:  SOC_CS_AP_ETF_ETF_RSZ_UNION */
#define SOC_CS_AP_ETF_ETF_RSZ_ADDR(base)              ((base) + (0x004))

/* 寄存器说明：ETF状态寄存器。
   位域定义UNION结构:  SOC_CS_AP_ETF_ETF_STS_UNION */
#define SOC_CS_AP_ETF_ETF_STS_ADDR(base)              ((base) + (0x00C))

/* 寄存器说明：ETF RAM读数据寄存器。
   位域定义UNION结构:  SOC_CS_AP_ETF_ETF_RRD_UNION */
#define SOC_CS_AP_ETF_ETF_RRD_ADDR(base)              ((base) + (0x010))

/* 寄存器说明：ETF RAM读指针寄存器。
   位域定义UNION结构:  SOC_CS_AP_ETF_ETF_RRP_UNION */
#define SOC_CS_AP_ETF_ETF_RRP_ADDR(base)              ((base) + (0x014))

/* 寄存器说明：ETF RAM写指针寄存器。
   位域定义UNION结构:  SOC_CS_AP_ETF_ETF_RWP_UNION */
#define SOC_CS_AP_ETF_ETF_RWP_ADDR(base)              ((base) + (0x018))

/* 寄存器说明：ETF trigger计数器寄存器。
   位域定义UNION结构:  SOC_CS_AP_ETF_ETF_TRG_UNION */
#define SOC_CS_AP_ETF_ETF_TRG_ADDR(base)              ((base) + (0x01C))

/* 寄存器说明：ETF控制寄存器。
   位域定义UNION结构:  SOC_CS_AP_ETF_ETF_CTL_UNION */
#define SOC_CS_AP_ETF_ETF_CTL_ADDR(base)              ((base) + (0x020))

/* 寄存器说明：ETF RAM写数据寄存器。
   位域定义UNION结构:  SOC_CS_AP_ETF_ETF_RWD_UNION */
#define SOC_CS_AP_ETF_ETF_RWD_ADDR(base)              ((base) + (0x024))

/* 寄存器说明：ETF 工作模式配置寄存器。
   位域定义UNION结构:  SOC_CS_AP_ETF_ETF_MODE_UNION */
#define SOC_CS_AP_ETF_ETF_MODE_ADDR(base)             ((base) + (0x028))

/* 寄存器说明：ETF buffer最大锁存水线寄存器。
   位域定义UNION结构:  SOC_CS_AP_ETF_ETF_LBUFLEVEL_UNION */
#define SOC_CS_AP_ETF_ETF_LBUFLEVEL_ADDR(base)        ((base) + (0x02C))

/* 寄存器说明：ETF buffer当前水线寄存器。
   位域定义UNION结构:  SOC_CS_AP_ETF_ETF_CBUFLEVEL_UNION */
#define SOC_CS_AP_ETF_ETF_CBUFLEVEL_ADDR(base)        ((base) + (0x030))

/* 寄存器说明：ETF buffer水线配置寄存器。
   位域定义UNION结构:  SOC_CS_AP_ETF_ETF_BUFWM_UNION */
#define SOC_CS_AP_ETF_ETF_BUFWM_ADDR(base)            ((base) + (0x034))

/* 寄存器说明：ETF formatter and flush状态寄存器。
   位域定义UNION结构:  SOC_CS_AP_ETF_ETF_FFSR_UNION */
#define SOC_CS_AP_ETF_ETF_FFSR_ADDR(base)             ((base) + (0x300))

/* 寄存器说明：ETF formatter and flush控制寄存器。
   位域定义UNION结构:  SOC_CS_AP_ETF_ETF_FFCR_UNION */
#define SOC_CS_AP_ETF_ETF_FFCR_ADDR(base)             ((base) + (0x304))

/* 寄存器说明：ETF Formatter同步计数器寄存器。
   位域定义UNION结构:  SOC_CS_AP_ETF_ETF_FSCR_UNION */
#define SOC_CS_AP_ETF_ETF_FSCR_ADDR(base)             ((base) + (0x308))

/* 寄存器说明：ETF锁定访问寄存器。
   位域定义UNION结构:  SOC_CS_AP_ETF_ETF_LAR_UNION */
#define SOC_CS_AP_ETF_ETF_LAR_ADDR(base)              ((base) + (0xFB0))

/* 寄存器说明：ETF锁定状态寄存器。
   位域定义UNION结构:  SOC_CS_AP_ETF_ETF_LSR_UNION */
#define SOC_CS_AP_ETF_ETF_LSR_ADDR(base)              ((base) + (0xFB4))





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
                     (1/1) AP_ETF
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_CS_AP_ETF_ETF_RSZ_UNION
 结构说明  : ETF_RSZ 寄存器结构定义。地址偏移量:0x004，初值:0x00001000，宽度:32
 寄存器说明: ETF RAM size寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rsz      : 31; /* bit[0-30]: 指示TOP ETF trace buffer的大小为16KB。 */
        unsigned int  reserved : 1;  /* bit[31]  : Reserved */
    } reg;
} SOC_CS_AP_ETF_ETF_RSZ_UNION;
#endif
#define SOC_CS_AP_ETF_ETF_RSZ_rsz_START       (0)
#define SOC_CS_AP_ETF_ETF_RSZ_rsz_END         (30)


/*****************************************************************************
 结构名    : SOC_CS_AP_ETF_ETF_STS_UNION
 结构说明  : ETF_STS 寄存器结构定义。地址偏移量:0x00C，初值:0x0000000C，宽度:32
 寄存器说明: ETF状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  full      : 1;  /* bit[0]   : This bit can help to determine how much of the trace buffer contains valid data.
                                                    
                                                    Circular Buffer mode:
                                                    This flag is set when the RAM write pointer wraps around the top of the buffer, and remains set until the TraceCaptEn bit is cleared and set.
                                                    
                                                    Software FIFO mode and Hardware FIFO mode:
                                                    This flag indicates that the current space in the trace memory is less than or equal to the value programmed in the BUFWM Register, that is, Fill level >= MEM_SIZE - BUFWM.  */
        unsigned int  triggered : 1;  /* bit[1]   : The Triggered bit is set when trace capture is in progress and the TMC has detected a Trigger Event.  */
        unsigned int  tmcready  : 1;  /* bit[2]   : Trace capture has stopped and all internal pipelines and buffers have drained and AXI interface is not busy */
        unsigned int  ftempty   : 1;  /* bit[3]   : This bit is set when trace capture has stopped, and all internal pipelines and buffers have drained.  */
        unsigned int  empty     : 1;  /* bit[4]   : This bit indicates that the TMC does not contain any valid trace data in the trace memory.
                                                    This bit is valid only when TraceCaptEn is HIGH. This bit reads as zero when TraceCaptEn is LOW. */
        unsigned int  reserved  : 27; /* bit[5-31]: Reserved */
    } reg;
} SOC_CS_AP_ETF_ETF_STS_UNION;
#endif
#define SOC_CS_AP_ETF_ETF_STS_full_START       (0)
#define SOC_CS_AP_ETF_ETF_STS_full_END         (0)
#define SOC_CS_AP_ETF_ETF_STS_triggered_START  (1)
#define SOC_CS_AP_ETF_ETF_STS_triggered_END    (1)
#define SOC_CS_AP_ETF_ETF_STS_tmcready_START   (2)
#define SOC_CS_AP_ETF_ETF_STS_tmcready_END     (2)
#define SOC_CS_AP_ETF_ETF_STS_ftempty_START    (3)
#define SOC_CS_AP_ETF_ETF_STS_ftempty_END      (3)
#define SOC_CS_AP_ETF_ETF_STS_empty_START      (4)
#define SOC_CS_AP_ETF_ETF_STS_empty_END        (4)


/*****************************************************************************
 结构名    : SOC_CS_AP_ETF_ETF_RRD_UNION
 结构说明  : ETF_RRD 寄存器结构定义。地址偏移量:0x010，初值:0x00000000，宽度:32
 寄存器说明: ETF RAM读数据寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rrd : 32; /* bit[0-31]: Reads return data from Trace buffer */
    } reg;
} SOC_CS_AP_ETF_ETF_RRD_UNION;
#endif
#define SOC_CS_AP_ETF_ETF_RRD_rrd_START  (0)
#define SOC_CS_AP_ETF_ETF_RRD_rrd_END    (31)


/*****************************************************************************
 结构名    : SOC_CS_AP_ETF_ETF_RRP_UNION
 结构说明  : ETF_RRP 寄存器结构定义。地址偏移量:0x014，初值:0x00000000，宽度:32
 寄存器说明: ETF RAM读指针寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rrp      : 12; /* bit[0-11] : This value represents the location in trace memory that is accessed on a subsequent RRD read */
        unsigned int  reserved : 20; /* bit[12-31]: Reserved */
    } reg;
} SOC_CS_AP_ETF_ETF_RRP_UNION;
#endif
#define SOC_CS_AP_ETF_ETF_RRP_rrp_START       (0)
#define SOC_CS_AP_ETF_ETF_RRP_rrp_END         (11)


/*****************************************************************************
 结构名    : SOC_CS_AP_ETF_ETF_RWP_UNION
 结构说明  : ETF_RWP 寄存器结构定义。地址偏移量:0x018，初值:0x00000000，宽度:32
 寄存器说明: ETF RAM写指针寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rwp      : 12; /* bit[0-11] : This value represents the location in trace memory that are accessed on a subsequent write to the 
                                                    trace memory */
        unsigned int  reserved : 20; /* bit[12-31]: Reserved */
    } reg;
} SOC_CS_AP_ETF_ETF_RWP_UNION;
#endif
#define SOC_CS_AP_ETF_ETF_RWP_rwp_START       (0)
#define SOC_CS_AP_ETF_ETF_RWP_rwp_END         (11)


/*****************************************************************************
 结构名    : SOC_CS_AP_ETF_ETF_TRG_UNION
 结构说明  : ETF_TRG 寄存器结构定义。地址偏移量:0x01C，初值:0x00000000，宽度:32
 寄存器说明: ETF trigger计数器寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  trg : 32; /* bit[0-31]: This count represents the number of 32-bit words between a TRIGIN or trigger packet and a Trigger Event.  */
    } reg;
} SOC_CS_AP_ETF_ETF_TRG_UNION;
#endif
#define SOC_CS_AP_ETF_ETF_TRG_trg_START  (0)
#define SOC_CS_AP_ETF_ETF_TRG_trg_END    (31)


/*****************************************************************************
 结构名    : SOC_CS_AP_ETF_ETF_CTL_UNION
 结构说明  : ETF_CTL 寄存器结构定义。地址偏移量:0x020，初值:0x00000000，宽度:32
 寄存器说明: ETF控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tracecapten : 1;  /* bit[0]   : Controls trace capture.  */
        unsigned int  reserved    : 31; /* bit[1-31]: Reserved */
    } reg;
} SOC_CS_AP_ETF_ETF_CTL_UNION;
#endif
#define SOC_CS_AP_ETF_ETF_CTL_tracecapten_START  (0)
#define SOC_CS_AP_ETF_ETF_CTL_tracecapten_END    (0)


/*****************************************************************************
 结构名    : SOC_CS_AP_ETF_ETF_RWD_UNION
 结构说明  : ETF_RWD 寄存器结构定义。地址偏移量:0x024，初值:0x00000000，宽度:32
 寄存器说明: ETF RAM写数据寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rwd : 32; /* bit[0-31]: Data written to this register is placed in the Trace RAM. */
    } reg;
} SOC_CS_AP_ETF_ETF_RWD_UNION;
#endif
#define SOC_CS_AP_ETF_ETF_RWD_rwd_START  (0)
#define SOC_CS_AP_ETF_ETF_RWD_rwd_END    (31)


/*****************************************************************************
 结构名    : SOC_CS_AP_ETF_ETF_MODE_UNION
 结构说明  : ETF_MODE 寄存器结构定义。地址偏移量:0x028，初值:0x00000000，宽度:32
 寄存器说明: ETF 工作模式配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode     : 2;  /* bit[0-1] : Selects the operating mode. 
                                                   3 = Reserved 
                                                   2 = Hardware FIFO mode
                                                   1 = Software FIFO mode
                                                   0 = Circular Buffer mode  */
        unsigned int  reserved : 30; /* bit[2-31]: Reserved */
    } reg;
} SOC_CS_AP_ETF_ETF_MODE_UNION;
#endif
#define SOC_CS_AP_ETF_ETF_MODE_mode_START      (0)
#define SOC_CS_AP_ETF_ETF_MODE_mode_END        (1)


/*****************************************************************************
 结构名    : SOC_CS_AP_ETF_ETF_LBUFLEVEL_UNION
 结构说明  : ETF_LBUFLEVEL 寄存器结构定义。地址偏移量:0x02C，初值:0x00000000，宽度:32
 寄存器说明: ETF buffer最大锁存水线寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lbuflevel : 13; /* bit[0-12] : Indicates the maximum fill level of the trace memory in 32-bit words since this register was last 
                                                     read */
        unsigned int  reserved  : 19; /* bit[13-31]: Reserved */
    } reg;
} SOC_CS_AP_ETF_ETF_LBUFLEVEL_UNION;
#endif
#define SOC_CS_AP_ETF_ETF_LBUFLEVEL_lbuflevel_START  (0)
#define SOC_CS_AP_ETF_ETF_LBUFLEVEL_lbuflevel_END    (12)


/*****************************************************************************
 结构名    : SOC_CS_AP_ETF_ETF_CBUFLEVEL_UNION
 结构说明  : ETF_CBUFLEVEL 寄存器结构定义。地址偏移量:0x030，初值:0x00000000，宽度:32
 寄存器说明: ETF buffer当前水线寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cbuflevel : 13; /* bit[0-12] : Indicates the current fill level of the trace memory in 32-bit words */
        unsigned int  reserved  : 19; /* bit[13-31]: Reserved */
    } reg;
} SOC_CS_AP_ETF_ETF_CBUFLEVEL_UNION;
#endif
#define SOC_CS_AP_ETF_ETF_CBUFLEVEL_cbuflevel_START  (0)
#define SOC_CS_AP_ETF_ETF_CBUFLEVEL_cbuflevel_END    (12)


/*****************************************************************************
 结构名    : SOC_CS_AP_ETF_ETF_BUFWM_UNION
 结构说明  : ETF_BUFWM 寄存器结构定义。地址偏移量:0x034，初值:0x00000000，宽度:32
 寄存器说明: ETF buffer水线配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  protctrlbit0      : 1;  /* bit[0]    : This bit controls the value driven on ARPROTM[0] or AWPROTM[0] on the AXI master interface when performing AXI transfers.
                                                             0 Normal access.
                                                             1 Privileged access. */
        unsigned int  protctrlbit1      : 1;  /* bit[1]    : This bit controls the value driven on ARPROTM[1] or AWPROTM[1] on the AXI master interface when performing AXI transfers.
                                                             0 Secure access.
                                                             1 Non-secure access. */
        unsigned int  cachectrlbit0     : 1;  /* bit[2]    : This bit controls the value driven on the ARCACHEM[0] or AWCACHEM[0] signal on the AXI master interface when performing AXI transfers.
                                                             0 Non-bufferable.
                                                             1 Bufferable. */
        unsigned int  cachectrlbit1     : 1;  /* bit[3]    : This bit controls the value driven on the ARCACHEM[1] or AWCACHEM[1] signal on the AXI master interface when performing AXI transfers.
                                                             0 Non-cacheable.
                                                             1 Cacheable. */
        unsigned int  cachectrlbit2     : 1;  /* bit[4]    : This bit controls the value driven on the ARCACHEM[2] or AWCACHEM[2] signal on the AXI master interface when performing AXI transfers. If CacheCtrlBit1 is LOW, this bit must also be LOW to comply with the AXI protocol. Setting this bit to HIGH when the CacheCtrlBit1 is LOW 
                                                             results in Unpredictable behavior.
                                                             0 Do not cache allocate on reads.
                                                             1 Cache allocate on reads. */
        unsigned int  cachectrlbit3     : 1;  /* bit[5]    : This bit controls the value driven on the ARCACHEM[3] or AWCACHEM[3] signal on the AXI master interface when performing AXI transfers. If CacheCtrlBit1 is LOW, this bit must also be LOW to comply with the AXI protocol. Setting this bit to HIGH when the CacheCtrlBit1 is LOW 
                                                             results in Unpredictable behavior.
                                                             0 Do not cache allocate on writes.
                                                             1 Cache allocate on writes. */
        unsigned int  reserved_0        : 1;  /* bit[6]    : Reserved */
        unsigned int  scattergathermode : 1;  /* bit[7]    : This bit indicates whether trace memory is accessed as a single buffer in system memory or as a linked-list based scatter-gather memory. This bit is ignored when in Disabled state.
                                                             0 Trace memory is a single contiguous block of system memory.
                                                             1 Trace memory is spread over multiple blocks of system memory based on a linked-list mechanism.  */
        unsigned int  wrburstlen        : 4;  /* bit[8-11] : This field indicates the maximum number of data transfers that can occur within each burst.
                                                             It is recommended that this value be set to no more than half the write buffer depth. Also, it is recommended that this value be set to enable an AXI burst of at least one frame of trace data.
                                                             0x0 One data transfer per burst. 
                                                             0x1 Maximum of two data transfers per burst.
                                                             ...
                                                             0xF Maximum of 16 data transfers per burst. */
        unsigned int  bufwm             : 1;  /* bit[12]   : Indicates the required threshold vacancy level in 32-bit words in the trace memory */
        unsigned int  reserved_1        : 19; /* bit[13-31]: Reserved */
    } reg;
} SOC_CS_AP_ETF_ETF_BUFWM_UNION;
#endif
#define SOC_CS_AP_ETF_ETF_BUFWM_protctrlbit0_START       (0)
#define SOC_CS_AP_ETF_ETF_BUFWM_protctrlbit0_END         (0)
#define SOC_CS_AP_ETF_ETF_BUFWM_protctrlbit1_START       (1)
#define SOC_CS_AP_ETF_ETF_BUFWM_protctrlbit1_END         (1)
#define SOC_CS_AP_ETF_ETF_BUFWM_cachectrlbit0_START      (2)
#define SOC_CS_AP_ETF_ETF_BUFWM_cachectrlbit0_END        (2)
#define SOC_CS_AP_ETF_ETF_BUFWM_cachectrlbit1_START      (3)
#define SOC_CS_AP_ETF_ETF_BUFWM_cachectrlbit1_END        (3)
#define SOC_CS_AP_ETF_ETF_BUFWM_cachectrlbit2_START      (4)
#define SOC_CS_AP_ETF_ETF_BUFWM_cachectrlbit2_END        (4)
#define SOC_CS_AP_ETF_ETF_BUFWM_cachectrlbit3_START      (5)
#define SOC_CS_AP_ETF_ETF_BUFWM_cachectrlbit3_END        (5)
#define SOC_CS_AP_ETF_ETF_BUFWM_scattergathermode_START  (7)
#define SOC_CS_AP_ETF_ETF_BUFWM_scattergathermode_END    (7)
#define SOC_CS_AP_ETF_ETF_BUFWM_wrburstlen_START         (8)
#define SOC_CS_AP_ETF_ETF_BUFWM_wrburstlen_END           (11)
#define SOC_CS_AP_ETF_ETF_BUFWM_bufwm_START              (12)
#define SOC_CS_AP_ETF_ETF_BUFWM_bufwm_END                (12)


/*****************************************************************************
 结构名    : SOC_CS_AP_ETF_ETF_FFSR_UNION
 结构说明  : ETF_FFSR 寄存器结构定义。地址偏移量:0x300，初值:0x00000000，宽度:32
 寄存器说明: ETF formatter and flush状态寄存器。
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
        unsigned int  ftstopped : 1;  /* bit[1]   : This bit behaves in the same way as the FtEmpty bit in the STS Register, 0x00C */
        unsigned int  reserved  : 30; /* bit[2-31]: Reserved */
    } reg;
} SOC_CS_AP_ETF_ETF_FFSR_UNION;
#endif
#define SOC_CS_AP_ETF_ETF_FFSR_flinprog_START   (0)
#define SOC_CS_AP_ETF_ETF_FFSR_flinprog_END     (0)
#define SOC_CS_AP_ETF_ETF_FFSR_ftstopped_START  (1)
#define SOC_CS_AP_ETF_ETF_FFSR_ftstopped_END    (1)


/*****************************************************************************
 结构名    : SOC_CS_AP_ETF_ETF_FFCR_UNION
 结构说明  : ETF_FFCR 寄存器结构定义。地址偏移量:0x304，初值:0x00000000，宽度:32
 寄存器说明: ETF formatter and flush控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  enft          : 1;  /* bit[0]    : If this bit is set, formatting is enabled.
                                                         0 Formatting disabled.
                                                         1 Formatting enabled. */
        unsigned int  enti          : 1;  /* bit[1]    : Setting this bit enables the insertion of triggers in the formatted trace stream.
                                                         0 Triggers are not embedded into the formatted trace stream.
                                                         1 Embed triggers into formatted trace stream. */
        unsigned int  reserved_0    : 2;  /* bit[2-3]  : Reserved */
        unsigned int  fonflin       : 1;  /* bit[4]    : Setting this bit enables the detection of transitions on the FLUSHIN input by the TMC. If this bit is set and the Formatter has not already stopped, a rising edge on FLUSHIN initiates a flush request.
                                                         0 Flush-on-FLUSHIN feature is disabled.
                                                         1 Flush-on-FLUSHIN feature is enabled. */
        unsigned int  fontrig       : 1;  /* bit[5]    : Setting this bit generates a flush when a Trigger Event occurs. If StopOnTrigEvt is set, this bit is ignored. 
                                                         0 Flush-on-trigger-event disabled.
                                                         1 Flush-on-trigger-event enabled. */
        unsigned int  flushman      : 1;  /* bit[6]    : Manually generate a flush of the system. Setting this bit causes a flush to be generated.
                                                         0 Manual flush is not initiated.
                                                         1 Manual flush is initiated. */
        unsigned int  reserved_1    : 1;  /* bit[7]    : Reserved */
        unsigned int  trigontrigin  : 1;  /* bit[8]    : Indicates a trigger when trigin is asserted.
                                                         0 Disable trigger indication when trigin is asserted.
                                                         1 Enable trigger indication when trigin is asserted. */
        unsigned int  trigontrigevt : 1;  /* bit[9]    : If this bit is set, a trigger is indicated on the output trace stream when a Trigger Event occurs. 
                                                         0 A trigger is not indicated on the trace stream when a Trigger Event occurs.
                                                         1 A trigger is indicated on the trace stream when a Trigger Event occurs. */
        unsigned int  trigonfl      : 1;  /* bit[10]   : If this bit is set, a trigger is indicated on the trace stream when a flush completes. 
                                                         0 A trigger is not indicated on the trace stream when a flush completes.
                                                         1 A trigger is indicated on the trace stream when a flush completes. */
        unsigned int  reserved_2    : 1;  /* bit[11]   : Reserved */
        unsigned int  stoponfl      : 1;  /* bit[12]   : If this bit is set, the formatter is stopped on completion of a flush operation.
                                                         0 Trace capture is not stopped when FLUSH is completed.
                                                         1 Trace capture is stopped when FLUSH is completed.  */
        unsigned int  stopontrigevt : 1;  /* bit[13]   : Stops the formatter after a trigger event is observed. Reset to disabled or 0.
                                                         0 Trace capture is not stopped when a Trigger Event is observed.
                                                         1 Trace capture is stopped when a Trigger Event is observed. */
        unsigned int  drainbuffer   : 1;  /* bit[14]   : This bit is used to enable draining of the trace data through the ATB master interface after the formatter has stopped.
                                                         0 Trace data is not drained through ATB master interface.
                                                         1 Trace data is drained through ATB master interface. */
        unsigned int  reserved_3    : 17; /* bit[15-31]: Reserved */
    } reg;
} SOC_CS_AP_ETF_ETF_FFCR_UNION;
#endif
#define SOC_CS_AP_ETF_ETF_FFCR_enft_START           (0)
#define SOC_CS_AP_ETF_ETF_FFCR_enft_END             (0)
#define SOC_CS_AP_ETF_ETF_FFCR_enti_START           (1)
#define SOC_CS_AP_ETF_ETF_FFCR_enti_END             (1)
#define SOC_CS_AP_ETF_ETF_FFCR_fonflin_START        (4)
#define SOC_CS_AP_ETF_ETF_FFCR_fonflin_END          (4)
#define SOC_CS_AP_ETF_ETF_FFCR_fontrig_START        (5)
#define SOC_CS_AP_ETF_ETF_FFCR_fontrig_END          (5)
#define SOC_CS_AP_ETF_ETF_FFCR_flushman_START       (6)
#define SOC_CS_AP_ETF_ETF_FFCR_flushman_END         (6)
#define SOC_CS_AP_ETF_ETF_FFCR_trigontrigin_START   (8)
#define SOC_CS_AP_ETF_ETF_FFCR_trigontrigin_END     (8)
#define SOC_CS_AP_ETF_ETF_FFCR_trigontrigevt_START  (9)
#define SOC_CS_AP_ETF_ETF_FFCR_trigontrigevt_END    (9)
#define SOC_CS_AP_ETF_ETF_FFCR_trigonfl_START       (10)
#define SOC_CS_AP_ETF_ETF_FFCR_trigonfl_END         (10)
#define SOC_CS_AP_ETF_ETF_FFCR_stoponfl_START       (12)
#define SOC_CS_AP_ETF_ETF_FFCR_stoponfl_END         (12)
#define SOC_CS_AP_ETF_ETF_FFCR_stopontrigevt_START  (13)
#define SOC_CS_AP_ETF_ETF_FFCR_stopontrigevt_END    (13)
#define SOC_CS_AP_ETF_ETF_FFCR_drainbuffer_START    (14)
#define SOC_CS_AP_ETF_ETF_FFCR_drainbuffer_END      (14)


/*****************************************************************************
 结构名    : SOC_CS_AP_ETF_ETF_FSCR_UNION
 结构说明  : ETF_FSCR 寄存器结构定义。地址偏移量:0x308，初值:0x00000000，宽度:32
 寄存器说明: ETF Formatter同步计数器寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pscount  : 5;  /* bit[0-4] : Determines the reload value of the Synchronization Counter. The reload value takes effect the next time the 
                                                   counter reaches zero. Reads from this register return the reload value programmed into this register. This register is set to 0xA on reset, corresponding to a synchronization period of 1024 bytes.
                                                   0x0 Synchronization disabled.
                                                   0x1-0x6 Reserved.
                                                   0x7-0x1B Synchronization period is 2PSCount bytes. For example, a value of 0x7 gives a synchronization 
                                                   period of 128 bytes.
                                                   0x1C-0x1F Reserved. */
        unsigned int  reserved : 27; /* bit[5-31]: Reserved */
    } reg;
} SOC_CS_AP_ETF_ETF_FSCR_UNION;
#endif
#define SOC_CS_AP_ETF_ETF_FSCR_pscount_START   (0)
#define SOC_CS_AP_ETF_ETF_FSCR_pscount_END     (4)


/*****************************************************************************
 结构名    : SOC_CS_AP_ETF_ETF_LAR_UNION
 结构说明  : ETF_LAR 寄存器结构定义。地址偏移量:0xFB0，初值:0x00000000，宽度:32
 寄存器说明: ETF锁定访问寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  key : 32; /* bit[0-31]: 写入0xC5ACCE55进行解锁，然后才可以正常配置其他寄存器；写入其他任何值后再次锁定。 */
    } reg;
} SOC_CS_AP_ETF_ETF_LAR_UNION;
#endif
#define SOC_CS_AP_ETF_ETF_LAR_key_START  (0)
#define SOC_CS_AP_ETF_ETF_LAR_key_END    (31)


/*****************************************************************************
 结构名    : SOC_CS_AP_ETF_ETF_LSR_UNION
 结构说明  : ETF_LSR 寄存器结构定义。地址偏移量:0xFB4，初值:0x00000003，宽度:32
 寄存器说明: ETF锁定状态寄存器。
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
} SOC_CS_AP_ETF_ETF_LSR_UNION;
#endif
#define SOC_CS_AP_ETF_ETF_LSR_sli_START       (0)
#define SOC_CS_AP_ETF_ETF_LSR_sli_END         (0)
#define SOC_CS_AP_ETF_ETF_LSR_slk_START       (1)
#define SOC_CS_AP_ETF_ETF_LSR_slk_END         (1)
#define SOC_CS_AP_ETF_ETF_LSR_ntt_START       (2)
#define SOC_CS_AP_ETF_ETF_LSR_ntt_END         (2)






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

#endif /* end of soc_cs_ap_etf_interface.h */
