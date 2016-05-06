/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_cs_top_etr_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-11-20 11:31:10
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年11月20日
    作    者   : l00352922
    修改内容   : 从《Hi3660V100 SOC寄存器手册_CS_TOP_ETR.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_CS_TOP_ETR_INTERFACE_H__
#define __SOC_CS_TOP_ETR_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) TOP_ETR
 ****************************************************************************/
/* 寄存器说明：ETR RAM size寄存器。
   位域定义UNION结构:  SOC_CS_TOP_ETR_ETR_RSZ_UNION */
#define SOC_CS_TOP_ETR_ETR_RSZ_ADDR(base)             ((base) + (0x004))

/* 寄存器说明：ETR状态寄存器。
   位域定义UNION结构:  SOC_CS_TOP_ETR_ETR_STS_UNION */
#define SOC_CS_TOP_ETR_ETR_STS_ADDR(base)             ((base) + (0x00C))

/* 寄存器说明：ETR RAM读数据寄存器。
   位域定义UNION结构:  SOC_CS_TOP_ETR_ETR_RRD_UNION */
#define SOC_CS_TOP_ETR_ETR_RRD_ADDR(base)             ((base) + (0x010))

/* 寄存器说明：ETR RAM读指针寄存器。
   位域定义UNION结构:  SOC_CS_TOP_ETR_ETR_RRP_UNION */
#define SOC_CS_TOP_ETR_ETR_RRP_ADDR(base)             ((base) + (0x014))

/* 寄存器说明：ETR RAM写指针寄存器。
   位域定义UNION结构:  SOC_CS_TOP_ETR_ETR_RWP_UNION */
#define SOC_CS_TOP_ETR_ETR_RWP_ADDR(base)             ((base) + (0x018))

/* 寄存器说明：ETR trigger计数器寄存器。
   位域定义UNION结构:  SOC_CS_TOP_ETR_ETR_TRG_UNION */
#define SOC_CS_TOP_ETR_ETR_TRG_ADDR(base)             ((base) + (0x01C))

/* 寄存器说明：ETR控制寄存器。
   位域定义UNION结构:  SOC_CS_TOP_ETR_ETR_CTL_UNION */
#define SOC_CS_TOP_ETR_ETR_CTL_ADDR(base)             ((base) + (0x020))

/* 寄存器说明：ETR RAM写数据寄存器。
   位域定义UNION结构:  SOC_CS_TOP_ETR_ETR_RWD_UNION */
#define SOC_CS_TOP_ETR_ETR_RWD_ADDR(base)             ((base) + (0x024))

/* 寄存器说明：ETR 工作模式配置寄存器。
   位域定义UNION结构:  SOC_CS_TOP_ETR_ETR_MODE_UNION */
#define SOC_CS_TOP_ETR_ETR_MODE_ADDR(base)            ((base) + (0x028))

/* 寄存器说明：ETR buffer最大锁存水线寄存器。
   位域定义UNION结构:  SOC_CS_TOP_ETR_ETR_LBUFLEVEL_UNION */
#define SOC_CS_TOP_ETR_ETR_LBUFLEVEL_ADDR(base)       ((base) + (0x02C))

/* 寄存器说明：ETR buffer当前水线寄存器。
   位域定义UNION结构:  SOC_CS_TOP_ETR_ETR_CBUFLEVEL_UNION */
#define SOC_CS_TOP_ETR_ETR_CBUFLEVEL_ADDR(base)       ((base) + (0x030))

/* 寄存器说明：ETR buffer水线配置寄存器。
   位域定义UNION结构:  SOC_CS_TOP_ETR_ETR_BUFWM_UNION */
#define SOC_CS_TOP_ETR_ETR_BUFWM_ADDR(base)           ((base) + (0x034))

/* 寄存器说明：ETR RAM读指针高位寄存器。
   位域定义UNION结构:  SOC_CS_TOP_ETR_ETR_RRPHI_UNION */
#define SOC_CS_TOP_ETR_ETR_RRPHI_ADDR(base)           ((base) + (0x038))

/* 寄存器说明：ETR RAM写指针高位寄存器。
   位域定义UNION结构:  SOC_CS_TOP_ETR_ETR_RWPHI_UNION */
#define SOC_CS_TOP_ETR_ETR_RWPHI_ADDR(base)           ((base) + (0x03C))

/* 寄存器说明：ETR AXI接口控制寄存器。
   位域定义UNION结构:  SOC_CS_TOP_ETR_ETR_AXICTL_UNION */
#define SOC_CS_TOP_ETR_ETR_AXICTL_ADDR(base)          ((base) + (0x110))

/* 寄存器说明：ETR数据buffer地址寄存器。
   位域定义UNION结构:  SOC_CS_TOP_ETR_ETR_DBALO_UNION */
#define SOC_CS_TOP_ETR_ETR_DBALO_ADDR(base)           ((base) + (0x118))

/* 寄存器说明：ETR数据buffer地址高位寄存器。
   位域定义UNION结构:  SOC_CS_TOP_ETR_ETR_DBAHO_UNION */
#define SOC_CS_TOP_ETR_ETR_DBAHO_ADDR(base)           ((base) + (0x11C))

/* 寄存器说明：ETR formatter and flush状态寄存器。
   位域定义UNION结构:  SOC_CS_TOP_ETR_ETR_FFSR_UNION */
#define SOC_CS_TOP_ETR_ETR_FFSR_ADDR(base)            ((base) + (0x300))

/* 寄存器说明：ETR formatter and flush控制寄存器。
   位域定义UNION结构:  SOC_CS_TOP_ETR_ETR_FFCR_UNION */
#define SOC_CS_TOP_ETR_ETR_FFCR_ADDR(base)            ((base) + (0x304))

/* 寄存器说明：ETR Formatter同步计数器寄存器。
   位域定义UNION结构:  SOC_CS_TOP_ETR_ETR_FSCR_UNION */
#define SOC_CS_TOP_ETR_ETR_FSCR_ADDR(base)            ((base) + (0x308))

/* 寄存器说明：ETR锁定访问寄存器。
   位域定义UNION结构:  SOC_CS_TOP_ETR_ETR_LAR_UNION */
#define SOC_CS_TOP_ETR_ETR_LAR_ADDR(base)             ((base) + (0xFB0))

/* 寄存器说明：ETR锁定状态寄存器。
   位域定义UNION结构:  SOC_CS_TOP_ETR_ETR_LSR_UNION */
#define SOC_CS_TOP_ETR_ETR_LSR_ADDR(base)             ((base) + (0xFB4))

/* 寄存器说明：ETR授权状态寄存器。
   位域定义UNION结构:  SOC_CS_TOP_ETR_ETR_AUTHSTATUS_UNION */
#define SOC_CS_TOP_ETR_ETR_AUTHSTATUS_ADDR(base)      ((base) + (0xFB8))





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
                     (1/1) TOP_ETR
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_CS_TOP_ETR_ETR_RSZ_UNION
 结构说明  : ETR_RSZ 寄存器结构定义。地址偏移量:0x004，初值:0x00000000，宽度:32
 寄存器说明: ETR RAM size寄存器。
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
} SOC_CS_TOP_ETR_ETR_RSZ_UNION;
#endif
#define SOC_CS_TOP_ETR_ETR_RSZ_rsz_START       (0)
#define SOC_CS_TOP_ETR_ETR_RSZ_rsz_END         (30)


/*****************************************************************************
 结构名    : SOC_CS_TOP_ETR_ETR_STS_UNION
 结构说明  : ETR_STS 寄存器结构定义。地址偏移量:0x00C，初值:0x0000000C，宽度:32
 寄存器说明: ETR状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  full      : 1;  /* bit[0]   : This flag is set when the RAM write pointer wraps around the top of the buffer, and remains set until the TraceCaptEn bit is cleared and set. */
        unsigned int  triggered : 1;  /* bit[1]   : The Triggered bit is set when trace capture is in progress and the TMC has detected a Trigger Event.  */
        unsigned int  tmcready  : 1;  /* bit[2]   : Trace capture has stopped and all internal pipelines and buffers have drained and AXI interface is not busy */
        unsigned int  ftempty   : 1;  /* bit[3]   : This bit is set when trace capture has stopped, and all internal pipelines and buffers have drained.  */
        unsigned int  empty     : 1;  /* bit[4]   : This bit indicates that the TMC does not contain any valid trace data in the trace memory.
                                                    This bit is valid only when TraceCaptEn is HIGH. This bit reads as zero when TraceCaptEn is LOW. */
        unsigned int  memerr    : 1;  /* bit[5]   : This bit indicates that an error has occurred on the AXI master interface. The error could be because of an error 
                                                    response from an AXI slave or because of the status of the Authentication interface inputs */
        unsigned int  reserved  : 26; /* bit[6-31]: Reserved */
    } reg;
} SOC_CS_TOP_ETR_ETR_STS_UNION;
#endif
#define SOC_CS_TOP_ETR_ETR_STS_full_START       (0)
#define SOC_CS_TOP_ETR_ETR_STS_full_END         (0)
#define SOC_CS_TOP_ETR_ETR_STS_triggered_START  (1)
#define SOC_CS_TOP_ETR_ETR_STS_triggered_END    (1)
#define SOC_CS_TOP_ETR_ETR_STS_tmcready_START   (2)
#define SOC_CS_TOP_ETR_ETR_STS_tmcready_END     (2)
#define SOC_CS_TOP_ETR_ETR_STS_ftempty_START    (3)
#define SOC_CS_TOP_ETR_ETR_STS_ftempty_END      (3)
#define SOC_CS_TOP_ETR_ETR_STS_empty_START      (4)
#define SOC_CS_TOP_ETR_ETR_STS_empty_END        (4)
#define SOC_CS_TOP_ETR_ETR_STS_memerr_START     (5)
#define SOC_CS_TOP_ETR_ETR_STS_memerr_END       (5)


/*****************************************************************************
 结构名    : SOC_CS_TOP_ETR_ETR_RRD_UNION
 结构说明  : ETR_RRD 寄存器结构定义。地址偏移量:0x010，初值:0x00000000，宽度:32
 寄存器说明: ETR RAM读数据寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rrd : 32; /* bit[0-31]: Reads return data from Trace buffer */
    } reg;
} SOC_CS_TOP_ETR_ETR_RRD_UNION;
#endif
#define SOC_CS_TOP_ETR_ETR_RRD_rrd_START  (0)
#define SOC_CS_TOP_ETR_ETR_RRD_rrd_END    (31)


/*****************************************************************************
 结构名    : SOC_CS_TOP_ETR_ETR_RRP_UNION
 结构说明  : ETR_RRP 寄存器结构定义。地址偏移量:0x014，初值:0x00000000，宽度:32
 寄存器说明: ETR RAM读指针寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rrp : 32; /* bit[0-31]: The contents of this register represents the lower 32 bits of the 
                                              40-bit AXI address used to access trace memory.  */
    } reg;
} SOC_CS_TOP_ETR_ETR_RRP_UNION;
#endif
#define SOC_CS_TOP_ETR_ETR_RRP_rrp_START  (0)
#define SOC_CS_TOP_ETR_ETR_RRP_rrp_END    (31)


/*****************************************************************************
 结构名    : SOC_CS_TOP_ETR_ETR_RWP_UNION
 结构说明  : ETR_RWP 寄存器结构定义。地址偏移量:0x018，初值:0x00000000，宽度:32
 寄存器说明: ETR RAM写指针寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rwp : 32; /* bit[0-31]: The contents of this register represents the lower 32 bits of the 
                                              40-bit AXI address used to access trace memory.  */
    } reg;
} SOC_CS_TOP_ETR_ETR_RWP_UNION;
#endif
#define SOC_CS_TOP_ETR_ETR_RWP_rwp_START  (0)
#define SOC_CS_TOP_ETR_ETR_RWP_rwp_END    (31)


/*****************************************************************************
 结构名    : SOC_CS_TOP_ETR_ETR_TRG_UNION
 结构说明  : ETR_TRG 寄存器结构定义。地址偏移量:0x01C，初值:0x00000000，宽度:32
 寄存器说明: ETR trigger计数器寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  trg : 32; /* bit[0-31]: This count represents the number of 32-bit words between a TRIGIN or trigger packet and a Trigger Event.  */
    } reg;
} SOC_CS_TOP_ETR_ETR_TRG_UNION;
#endif
#define SOC_CS_TOP_ETR_ETR_TRG_trg_START  (0)
#define SOC_CS_TOP_ETR_ETR_TRG_trg_END    (31)


/*****************************************************************************
 结构名    : SOC_CS_TOP_ETR_ETR_CTL_UNION
 结构说明  : ETR_CTL 寄存器结构定义。地址偏移量:0x020，初值:0x00000000，宽度:32
 寄存器说明: ETR控制寄存器。
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
} SOC_CS_TOP_ETR_ETR_CTL_UNION;
#endif
#define SOC_CS_TOP_ETR_ETR_CTL_tracecapten_START  (0)
#define SOC_CS_TOP_ETR_ETR_CTL_tracecapten_END    (0)


/*****************************************************************************
 结构名    : SOC_CS_TOP_ETR_ETR_RWD_UNION
 结构说明  : ETR_RWD 寄存器结构定义。地址偏移量:0x024，初值:0x00000000，宽度:32
 寄存器说明: ETR RAM写数据寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rwd : 32; /* bit[0-31]: Data written to this register is placed in the Trace RAM. */
    } reg;
} SOC_CS_TOP_ETR_ETR_RWD_UNION;
#endif
#define SOC_CS_TOP_ETR_ETR_RWD_rwd_START  (0)
#define SOC_CS_TOP_ETR_ETR_RWD_rwd_END    (31)


/*****************************************************************************
 结构名    : SOC_CS_TOP_ETR_ETR_MODE_UNION
 结构说明  : ETR_MODE 寄存器结构定义。地址偏移量:0x028，初值:0x00000000，宽度:32
 寄存器说明: ETR 工作模式配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode     : 2;  /* bit[0-1] : Selects the operating mode. 
                                                   2/3 =Reserved 
                                                   1 = Software FIFO mode
                                                   0 = Circular Buffer mode  */
        unsigned int  reserved : 30; /* bit[2-31]: Reserved */
    } reg;
} SOC_CS_TOP_ETR_ETR_MODE_UNION;
#endif
#define SOC_CS_TOP_ETR_ETR_MODE_mode_START      (0)
#define SOC_CS_TOP_ETR_ETR_MODE_mode_END        (1)


/*****************************************************************************
 结构名    : SOC_CS_TOP_ETR_ETR_LBUFLEVEL_UNION
 结构说明  : ETR_LBUFLEVEL 寄存器结构定义。地址偏移量:0x02C，初值:0x00000000，宽度:32
 寄存器说明: ETR buffer最大锁存水线寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lbuflevel : 32; /* bit[0-31]: Indicates the maximum fill level of the trace memory in 32-bit words since this register was last read. */
    } reg;
} SOC_CS_TOP_ETR_ETR_LBUFLEVEL_UNION;
#endif
#define SOC_CS_TOP_ETR_ETR_LBUFLEVEL_lbuflevel_START  (0)
#define SOC_CS_TOP_ETR_ETR_LBUFLEVEL_lbuflevel_END    (31)


/*****************************************************************************
 结构名    : SOC_CS_TOP_ETR_ETR_CBUFLEVEL_UNION
 结构说明  : ETR_CBUFLEVEL 寄存器结构定义。地址偏移量:0x030，初值:0x00000000，宽度:32
 寄存器说明: ETR buffer当前水线寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cbuflevel : 32; /* bit[0-31]: Indicates the current fill level of the trace memory in 32-bit words */
    } reg;
} SOC_CS_TOP_ETR_ETR_CBUFLEVEL_UNION;
#endif
#define SOC_CS_TOP_ETR_ETR_CBUFLEVEL_cbuflevel_START  (0)
#define SOC_CS_TOP_ETR_ETR_CBUFLEVEL_cbuflevel_END    (31)


/*****************************************************************************
 结构名    : SOC_CS_TOP_ETR_ETR_BUFWM_UNION
 结构说明  : ETR_BUFWM 寄存器结构定义。地址偏移量:0x034，初值:0x00000000，宽度:32
 寄存器说明: ETR buffer水线配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bufwm : 32; /* bit[0-31]: Indicates the required threshold vacancy level in 32-bit words in the trace memory */
    } reg;
} SOC_CS_TOP_ETR_ETR_BUFWM_UNION;
#endif
#define SOC_CS_TOP_ETR_ETR_BUFWM_bufwm_START  (0)
#define SOC_CS_TOP_ETR_ETR_BUFWM_bufwm_END    (31)


/*****************************************************************************
 结构名    : SOC_CS_TOP_ETR_ETR_RRPHI_UNION
 结构说明  : ETR_RRPHI 寄存器结构定义。地址偏移量:0x038，初值:0x00000000，宽度:32
 寄存器说明: ETR RAM读指针高位寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rrphi    : 8;  /* bit[0-7] : Bits [39:32] of the read pointer */
        unsigned int  reserved : 24; /* bit[8-31]: Reserved */
    } reg;
} SOC_CS_TOP_ETR_ETR_RRPHI_UNION;
#endif
#define SOC_CS_TOP_ETR_ETR_RRPHI_rrphi_START     (0)
#define SOC_CS_TOP_ETR_ETR_RRPHI_rrphi_END       (7)


/*****************************************************************************
 结构名    : SOC_CS_TOP_ETR_ETR_RWPHI_UNION
 结构说明  : ETR_RWPHI 寄存器结构定义。地址偏移量:0x03C，初值:0x00000000，宽度:32
 寄存器说明: ETR RAM写指针高位寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rwphi    : 8;  /* bit[0-7] : Bits [39:32] of the write pointer */
        unsigned int  reserved : 24; /* bit[8-31]: Reserved */
    } reg;
} SOC_CS_TOP_ETR_ETR_RWPHI_UNION;
#endif
#define SOC_CS_TOP_ETR_ETR_RWPHI_rwphi_START     (0)
#define SOC_CS_TOP_ETR_ETR_RWPHI_rwphi_END       (7)


/*****************************************************************************
 结构名    : SOC_CS_TOP_ETR_ETR_AXICTL_UNION
 结构说明  : ETR_AXICTL 寄存器结构定义。地址偏移量:0x110，初值:0x00000000，宽度:32
 寄存器说明: ETR AXI接口控制寄存器。
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
        unsigned int  reserved_1        : 20; /* bit[12-31]: Reserved */
    } reg;
} SOC_CS_TOP_ETR_ETR_AXICTL_UNION;
#endif
#define SOC_CS_TOP_ETR_ETR_AXICTL_protctrlbit0_START       (0)
#define SOC_CS_TOP_ETR_ETR_AXICTL_protctrlbit0_END         (0)
#define SOC_CS_TOP_ETR_ETR_AXICTL_protctrlbit1_START       (1)
#define SOC_CS_TOP_ETR_ETR_AXICTL_protctrlbit1_END         (1)
#define SOC_CS_TOP_ETR_ETR_AXICTL_cachectrlbit0_START      (2)
#define SOC_CS_TOP_ETR_ETR_AXICTL_cachectrlbit0_END        (2)
#define SOC_CS_TOP_ETR_ETR_AXICTL_cachectrlbit1_START      (3)
#define SOC_CS_TOP_ETR_ETR_AXICTL_cachectrlbit1_END        (3)
#define SOC_CS_TOP_ETR_ETR_AXICTL_cachectrlbit2_START      (4)
#define SOC_CS_TOP_ETR_ETR_AXICTL_cachectrlbit2_END        (4)
#define SOC_CS_TOP_ETR_ETR_AXICTL_cachectrlbit3_START      (5)
#define SOC_CS_TOP_ETR_ETR_AXICTL_cachectrlbit3_END        (5)
#define SOC_CS_TOP_ETR_ETR_AXICTL_scattergathermode_START  (7)
#define SOC_CS_TOP_ETR_ETR_AXICTL_scattergathermode_END    (7)
#define SOC_CS_TOP_ETR_ETR_AXICTL_wrburstlen_START         (8)
#define SOC_CS_TOP_ETR_ETR_AXICTL_wrburstlen_END           (11)


/*****************************************************************************
 结构名    : SOC_CS_TOP_ETR_ETR_DBALO_UNION
 结构说明  : ETR_DBALO 寄存器结构定义。地址偏移量:0x118，初值:0x00000000，宽度:32
 寄存器说明: ETR数据buffer地址寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bufaddrlo : 32; /* bit[0-31]: 作为trace buffer的系统内存的低32-bit地址 */
    } reg;
} SOC_CS_TOP_ETR_ETR_DBALO_UNION;
#endif
#define SOC_CS_TOP_ETR_ETR_DBALO_bufaddrlo_START  (0)
#define SOC_CS_TOP_ETR_ETR_DBALO_bufaddrlo_END    (31)


/*****************************************************************************
 结构名    : SOC_CS_TOP_ETR_ETR_DBAHO_UNION
 结构说明  : ETR_DBAHO 寄存器结构定义。地址偏移量:0x11C，初值:0x00000000，宽度:32
 寄存器说明: ETR数据buffer地址高位寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bufaddrhi : 8;  /* bit[0-7] : Holds the upper eight bits of the 40-bit address used to locate the trace buffer in system memory */
        unsigned int  reserved  : 24; /* bit[8-31]: Reserved */
    } reg;
} SOC_CS_TOP_ETR_ETR_DBAHO_UNION;
#endif
#define SOC_CS_TOP_ETR_ETR_DBAHO_bufaddrhi_START  (0)
#define SOC_CS_TOP_ETR_ETR_DBAHO_bufaddrhi_END    (7)


/*****************************************************************************
 结构名    : SOC_CS_TOP_ETR_ETR_FFSR_UNION
 结构说明  : ETR_FFSR 寄存器结构定义。地址偏移量:0x300，初值:0x00000000，宽度:32
 寄存器说明: ETR formatter and flush状态寄存器。
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
} SOC_CS_TOP_ETR_ETR_FFSR_UNION;
#endif
#define SOC_CS_TOP_ETR_ETR_FFSR_flinprog_START   (0)
#define SOC_CS_TOP_ETR_ETR_FFSR_flinprog_END     (0)
#define SOC_CS_TOP_ETR_ETR_FFSR_ftstopped_START  (1)
#define SOC_CS_TOP_ETR_ETR_FFSR_ftstopped_END    (1)


/*****************************************************************************
 结构名    : SOC_CS_TOP_ETR_ETR_FFCR_UNION
 结构说明  : ETR_FFCR 寄存器结构定义。地址偏移量:0x304，初值:0x00000000，宽度:32
 寄存器说明: ETR formatter and flush控制寄存器。
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
        unsigned int  reserved_3    : 18; /* bit[14-31]: Reserved */
    } reg;
} SOC_CS_TOP_ETR_ETR_FFCR_UNION;
#endif
#define SOC_CS_TOP_ETR_ETR_FFCR_enft_START           (0)
#define SOC_CS_TOP_ETR_ETR_FFCR_enft_END             (0)
#define SOC_CS_TOP_ETR_ETR_FFCR_enti_START           (1)
#define SOC_CS_TOP_ETR_ETR_FFCR_enti_END             (1)
#define SOC_CS_TOP_ETR_ETR_FFCR_fonflin_START        (4)
#define SOC_CS_TOP_ETR_ETR_FFCR_fonflin_END          (4)
#define SOC_CS_TOP_ETR_ETR_FFCR_fontrig_START        (5)
#define SOC_CS_TOP_ETR_ETR_FFCR_fontrig_END          (5)
#define SOC_CS_TOP_ETR_ETR_FFCR_flushman_START       (6)
#define SOC_CS_TOP_ETR_ETR_FFCR_flushman_END         (6)
#define SOC_CS_TOP_ETR_ETR_FFCR_trigontrigin_START   (8)
#define SOC_CS_TOP_ETR_ETR_FFCR_trigontrigin_END     (8)
#define SOC_CS_TOP_ETR_ETR_FFCR_trigontrigevt_START  (9)
#define SOC_CS_TOP_ETR_ETR_FFCR_trigontrigevt_END    (9)
#define SOC_CS_TOP_ETR_ETR_FFCR_trigonfl_START       (10)
#define SOC_CS_TOP_ETR_ETR_FFCR_trigonfl_END         (10)
#define SOC_CS_TOP_ETR_ETR_FFCR_stoponfl_START       (12)
#define SOC_CS_TOP_ETR_ETR_FFCR_stoponfl_END         (12)
#define SOC_CS_TOP_ETR_ETR_FFCR_stopontrigevt_START  (13)
#define SOC_CS_TOP_ETR_ETR_FFCR_stopontrigevt_END    (13)


/*****************************************************************************
 结构名    : SOC_CS_TOP_ETR_ETR_FSCR_UNION
 结构说明  : ETR_FSCR 寄存器结构定义。地址偏移量:0x308，初值:0x00000000，宽度:32
 寄存器说明: ETR Formatter同步计数器寄存器。
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
} SOC_CS_TOP_ETR_ETR_FSCR_UNION;
#endif
#define SOC_CS_TOP_ETR_ETR_FSCR_pscount_START   (0)
#define SOC_CS_TOP_ETR_ETR_FSCR_pscount_END     (4)


/*****************************************************************************
 结构名    : SOC_CS_TOP_ETR_ETR_LAR_UNION
 结构说明  : ETR_LAR 寄存器结构定义。地址偏移量:0xFB0，初值:0x00000000，宽度:32
 寄存器说明: ETR锁定访问寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  key : 32; /* bit[0-31]: 写入0xC5ACCE55进行解锁，然后才可以正常配置其他寄存器；写入其他任何值后再次锁定。 */
    } reg;
} SOC_CS_TOP_ETR_ETR_LAR_UNION;
#endif
#define SOC_CS_TOP_ETR_ETR_LAR_key_START  (0)
#define SOC_CS_TOP_ETR_ETR_LAR_key_END    (31)


/*****************************************************************************
 结构名    : SOC_CS_TOP_ETR_ETR_LSR_UNION
 结构说明  : ETR_LSR 寄存器结构定义。地址偏移量:0xFB4，初值:0x00000003，宽度:32
 寄存器说明: ETR锁定状态寄存器。
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
} SOC_CS_TOP_ETR_ETR_LSR_UNION;
#endif
#define SOC_CS_TOP_ETR_ETR_LSR_sli_START       (0)
#define SOC_CS_TOP_ETR_ETR_LSR_sli_END         (0)
#define SOC_CS_TOP_ETR_ETR_LSR_slk_START       (1)
#define SOC_CS_TOP_ETR_ETR_LSR_slk_END         (1)
#define SOC_CS_TOP_ETR_ETR_LSR_ntt_START       (2)
#define SOC_CS_TOP_ETR_ETR_LSR_ntt_END         (2)


/*****************************************************************************
 结构名    : SOC_CS_TOP_ETR_ETR_AUTHSTATUS_UNION
 结构说明  : ETR_AUTHSTATUS 寄存器结构定义。地址偏移量:0xFB8，初值:0x00000022，宽度:32
 寄存器说明: ETR授权状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  nsid     : 2;  /* bit[0-1] : Indicates the security level for non-secure invasive debug.
                                                   0x2 Functionality disabled. This return value occurs when DBGEN is LOW.
                                                   0x3 Functionality enabled. This return value occurs when DBGEN is HIGH. */
        unsigned int  nsnid    : 2;  /* bit[2-3] : Indicates non-secure non-invasive debug is not implemented. */
        unsigned int  sid      : 2;  /* bit[4-5] : Indicates the security level for secure invasive debug.
                                                   0x2 Functionality disabled. This return value occurs when SPIDEN is LOW or DBGEN is LOW.
                                                   0x3 Functionality enabled. This return value occurs when SPIDEN and DBGEN are HIGH. */
        unsigned int  snid     : 2;  /* bit[6-7] : Indicates secure non-invasive debug is not implemented. */
        unsigned int  reserved : 24; /* bit[8-31]: Reserved */
    } reg;
} SOC_CS_TOP_ETR_ETR_AUTHSTATUS_UNION;
#endif
#define SOC_CS_TOP_ETR_ETR_AUTHSTATUS_nsid_START      (0)
#define SOC_CS_TOP_ETR_ETR_AUTHSTATUS_nsid_END        (1)
#define SOC_CS_TOP_ETR_ETR_AUTHSTATUS_nsnid_START     (2)
#define SOC_CS_TOP_ETR_ETR_AUTHSTATUS_nsnid_END       (3)
#define SOC_CS_TOP_ETR_ETR_AUTHSTATUS_sid_START       (4)
#define SOC_CS_TOP_ETR_ETR_AUTHSTATUS_sid_END         (5)
#define SOC_CS_TOP_ETR_ETR_AUTHSTATUS_snid_START      (6)
#define SOC_CS_TOP_ETR_ETR_AUTHSTATUS_snid_END        (7)






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

#endif /* end of soc_cs_top_etr_interface.h */
