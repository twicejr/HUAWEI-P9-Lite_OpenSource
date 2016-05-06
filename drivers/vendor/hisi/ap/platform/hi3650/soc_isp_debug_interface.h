/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_isp_debug_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:21:31
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_ISP_DEBUG.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_ISP_DEBUG_INTERFACE_H__
#define __SOC_ISP_DEBUG_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) DEBUG
 ****************************************************************************/
/* 寄存器说明：Processing debug configuration register
   位域定义UNION结构:  SOC_ISP_DEBUG_DBG_TOP_PROC_CFG_UNION */
#define SOC_ISP_DEBUG_DBG_TOP_PROC_CFG_ADDR(base)     ((base) + (0x0))

/* 寄存器说明：configuration of the time out
   位域定义UNION结构:  SOC_ISP_DEBUG_DBG_TOP_PROC_TIMEOUT_UNION */
#define SOC_ISP_DEBUG_DBG_TOP_PROC_TIMEOUT_ADDR(base) ((base) + (0x04))

/* 寄存器说明：Buffer Start address of the DBG
   位域定义UNION结构:  SOC_ISP_DEBUG_DBG_TOP_BUF_ADDR_UNION */
#define SOC_ISP_DEBUG_DBG_TOP_BUF_ADDR_ADDR(base)     ((base) + (0x10))

/* 寄存器说明：Configuration  of the number of subframe in a log frame
   位域定义UNION结构:  SOC_ISP_DEBUG_DBG_TOP_SUBFRAME_NUM_UNION */
#define SOC_ISP_DEBUG_DBG_TOP_SUBFRAME_NUM_ADDR(base) ((base) + (0x14))

/* 寄存器说明：AXI line wrap and line stride
   位域定义UNION结构:  SOC_ISP_DEBUG_DBG_TOP_BUF_LINE_UNION */
#define SOC_ISP_DEBUG_DBG_TOP_BUF_LINE_ADDR(base)     ((base) + (0x18))

/* 寄存器说明：DBG interrupt SW to refresh the write pointer
   位域定义UNION结构:  SOC_ISP_DEBUG_DBG_TOP_REFRESH_WPTR_UNION */
#define SOC_ISP_DEBUG_DBG_TOP_REFRESH_WPTR_ADDR(base) ((base) + (0x1C))

/* 寄存器说明：the write pointer deliver to SW
   位域定义UNION结构:  SOC_ISP_DEBUG_DBG_TOP_WPTR_UNION */
#define SOC_ISP_DEBUG_DBG_TOP_WPTR_ADDR(base)         ((base) + (0x20))

/* 寄存器说明：Interrupt global debug configur register
   位域定义UNION结构:  SOC_ISP_DEBUG_DBG_IRQ_STOP_TIMER_UNION */
#define SOC_ISP_DEBUG_DBG_IRQ_STOP_TIMER_ADDR(base)   ((base) + (0x40))

/* 寄存器说明：configur of the debugger stop mode
   位域定义UNION结构:  SOC_ISP_DEBUG_DBG_IRQ_CFG_UNION */
#define SOC_ISP_DEBUG_DBG_IRQ_CFG_ADDR(base)          ((base) + (0x44))

/* 寄存器说明：Interrupt Enable debug configuration register 0
   位域定义UNION结构:  SOC_ISP_DEBUG_DBG_IRQ_MASK_0_UNION */
#define SOC_ISP_DEBUG_DBG_IRQ_MASK_0_ADDR(base)       ((base) + (0x4C))

/* 寄存器说明：Interrupt Enable debug configuration register 1
   位域定义UNION结构:  SOC_ISP_DEBUG_DBG_IRQ_MASK_1_UNION */
#define SOC_ISP_DEBUG_DBG_IRQ_MASK_1_ADDR(base)       ((base) + (0x50))

/* 寄存器说明：configur of the debugger stop mode
   位域定义UNION结构:  SOC_ISP_DEBUG_DBG_BUS_CFG_UNION */
#define SOC_ISP_DEBUG_DBG_BUS_CFG_ADDR(base)          ((base) + (0x60))

/* 寄存器说明：Interrupt global debug configur register
   位域定义UNION结构:  SOC_ISP_DEBUG_DBG_BUS_STOP_TIMER_UNION */
#define SOC_ISP_DEBUG_DBG_BUS_STOP_TIMER_ADDR(base)   ((base) + (0x64))

/* 寄存器说明：To Mask the given address
   位域定义UNION结构:  SOC_ISP_DEBUG_DBG_BUS_32K_MASK_UNION */
#define SOC_ISP_DEBUG_DBG_BUS_32K_MASK_ADDR(base)     ((base) + (0x68))

/* 寄存器说明：To Mask a indicated address
   位域定义UNION结构:  SOC_ISP_DEBUG_DBG_BUS_SINGLE_MASK_UNION */
#define SOC_ISP_DEBUG_DBG_BUS_SINGLE_MASK_ADDR(base)  ((base) + (0x6C))

/* 寄存器说明：configur of the processing debug map
   位域定义UNION结构:  SOC_ISP_DEBUG_DBG_STATIS_MAP_CFG_UNION */
#define SOC_ISP_DEBUG_DBG_STATIS_MAP_CFG_ADDR(base)   ((base) + (0x70))

/* 寄存器说明：enable
   位域定义UNION结构:  SOC_ISP_DEBUG_DBG_STATIS_CFG_UNION */
#define SOC_ISP_DEBUG_DBG_STATIS_CFG_ADDR(base)       ((base) + (0x74))





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
                     (1/1) DEBUG
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_ISP_DEBUG_DBG_TOP_PROC_CFG_UNION
 结构说明  : DBG_TOP_PROC_CFG 寄存器结构定义。地址偏移量:0x0，初值:0x00000000，宽度:32
 寄存器说明: Processing debug configuration register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_top_proc_enable : 1;  /* bit[0]   :  */
        unsigned int  reserved_0          : 3;  /* bit[1-3] :  */
        unsigned int  dbg_top_stop_mod    : 1;  /* bit[4]   : 0： manual；1：timer */
        unsigned int  reserved_1          : 3;  /* bit[5-7] :  */
        unsigned int  reserved_2          : 24; /* bit[8-31]: enable or not the processing debug logic.
                                                              Once enabled, the statistics will be generated on every end of line, starting from a start of frame.
                                                              This register is working as a shadow register (but shadowing is performed into an FSM).
                                                              If disabled, the video port in is directly sent to the video port out (feedthrough) */
    } reg;
} SOC_ISP_DEBUG_DBG_TOP_PROC_CFG_UNION;
#endif
#define SOC_ISP_DEBUG_DBG_TOP_PROC_CFG_dbg_top_proc_enable_START  (0)
#define SOC_ISP_DEBUG_DBG_TOP_PROC_CFG_dbg_top_proc_enable_END    (0)
#define SOC_ISP_DEBUG_DBG_TOP_PROC_CFG_dbg_top_stop_mod_START     (4)
#define SOC_ISP_DEBUG_DBG_TOP_PROC_CFG_dbg_top_stop_mod_END       (4)


/*****************************************************************************
 结构名    : SOC_ISP_DEBUG_DBG_TOP_PROC_TIMEOUT_UNION
 结构说明  : DBG_TOP_PROC_TIMEOUT 寄存器结构定义。地址偏移量:0x04，初值:0x00000000，宽度:32
 寄存器说明: configuration of the time out
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_top_stop_timeout : 32; /* bit[0-31]:  */
    } reg;
} SOC_ISP_DEBUG_DBG_TOP_PROC_TIMEOUT_UNION;
#endif
#define SOC_ISP_DEBUG_DBG_TOP_PROC_TIMEOUT_dbg_top_stop_timeout_START  (0)
#define SOC_ISP_DEBUG_DBG_TOP_PROC_TIMEOUT_dbg_top_stop_timeout_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_DEBUG_DBG_TOP_BUF_ADDR_UNION
 结构说明  : DBG_TOP_BUF_ADDR 寄存器结构定义。地址偏移量:0x10，初值:0x00000000，宽度:32
 寄存器说明: Buffer Start address of the DBG
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved          : 4;  /* bit[0-3] :  */
        unsigned int  dbg_top_buf_baddr : 28; /* bit[4-31]: base address, and 16Byte align */
    } reg;
} SOC_ISP_DEBUG_DBG_TOP_BUF_ADDR_UNION;
#endif
#define SOC_ISP_DEBUG_DBG_TOP_BUF_ADDR_dbg_top_buf_baddr_START  (4)
#define SOC_ISP_DEBUG_DBG_TOP_BUF_ADDR_dbg_top_buf_baddr_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_DEBUG_DBG_TOP_SUBFRAME_NUM_UNION
 结构说明  : DBG_TOP_SUBFRAME_NUM 寄存器结构定义。地址偏移量:0x14，初值:0x00000194，宽度:32
 寄存器说明: Configuration  of the number of subframe in a log frame
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_top_subframe_num : 11; /* bit[0-10] : the number of subframe :default:404；
                                                                we strongly advice to config as the following 4 values:
                                                                For 2KBytes length LogFrame: let dbg_top_buf_line_stride 127 and dbg_top_subframe_num 196
                                                                For 4KBytes length LogFrame: let dbg_top_buf_line_stride 255 and dbg_top_subframe_num 404
                                                                For 8KBytes length LogFrame: let dbg_top_buf_line_stride 511 and dbg_top_subframe_num 812
                                                                For 16KBtyes length LogFrame: let dbg_top_buf_line_stride 1023 and dbg_top_subframe_num 1628
                                                                others： reserved， if needed contact with tanhuang00134249 */
        unsigned int  reserved             : 21; /* bit[11-31]:  */
    } reg;
} SOC_ISP_DEBUG_DBG_TOP_SUBFRAME_NUM_UNION;
#endif
#define SOC_ISP_DEBUG_DBG_TOP_SUBFRAME_NUM_dbg_top_subframe_num_START  (0)
#define SOC_ISP_DEBUG_DBG_TOP_SUBFRAME_NUM_dbg_top_subframe_num_END    (10)


/*****************************************************************************
 结构名    : SOC_ISP_DEBUG_DBG_TOP_BUF_LINE_UNION
 结构说明  : DBG_TOP_BUF_LINE 寄存器结构定义。地址偏移量:0x18，初值:0x00FF00FF，宽度:32
 寄存器说明: AXI line wrap and line stride
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_top_buf_line_stride : 10; /* bit[0-9]  : Stride to use on line starts (aligned to a 16 byte boundary: Max stride of 16 KBytes)
                                                                   0: line stride disabled (continuous mode : next line will start on a 128 bytes boundary)
                                                                   1: 2*16 bytes
                                                                   …
                                                                   1023 : 1024*16 bytes
                                                                   please config CVDR as the same
                                                                   we strongly addvice to config as the following 4 types:
                                                                   For 2KBytes length LogFrame: let dbg_top_buf_line_stride 127 and dbg_top_subframe_num 196
                                                                   For 4KBytes length LogFrame: let dbg_top_buf_line_stride 255 and dbg_top_subframe_num 404
                                                                   For 8KBytes length LogFrame: let dbg_top_buf_line_stride 511 and dbg_top_subframe_num 812
                                                                   For 16KBtyes length LogFrame: let dbg_top_buf_line_stride 1023 and dbg_top_subframe_num 1628
                                                                   others： reserved， if needed contact with tanhuang00134249 */
        unsigned int  reserved_0              : 6;  /* bit[10-15]: reserved */
        unsigned int  dbg_top_buf_line_wrap   : 13; /* bit[16-28]: Line wrap: wrap to frame start location (13 bits)
                                                                   0: wrap every line
                                                                   1: wrap every 2 lines
                                                                   …
                                                                   8191: wrap every 8192 lines
                                                                   determined by the buffer depth assign by the system, it should equal to (buffer depth)/stride -1, of course it should aligned with 16Byte */
        unsigned int  reserved_1              : 3;  /* bit[29-31]: reserved */
    } reg;
} SOC_ISP_DEBUG_DBG_TOP_BUF_LINE_UNION;
#endif
#define SOC_ISP_DEBUG_DBG_TOP_BUF_LINE_dbg_top_buf_line_stride_START  (0)
#define SOC_ISP_DEBUG_DBG_TOP_BUF_LINE_dbg_top_buf_line_stride_END    (9)
#define SOC_ISP_DEBUG_DBG_TOP_BUF_LINE_dbg_top_buf_line_wrap_START    (16)
#define SOC_ISP_DEBUG_DBG_TOP_BUF_LINE_dbg_top_buf_line_wrap_END      (28)


/*****************************************************************************
 结构名    : SOC_ISP_DEBUG_DBG_TOP_REFRESH_WPTR_UNION
 结构说明  : DBG_TOP_REFRESH_WPTR 寄存器结构定义。地址偏移量:0x1C，初值:0x00000000，宽度:32
 寄存器说明: DBG interrupt SW to refresh the write pointer
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_top_refresh_ptr : 1;  /* bit[0]   :  */
        unsigned int  reserved            : 31; /* bit[1-31]:  */
    } reg;
} SOC_ISP_DEBUG_DBG_TOP_REFRESH_WPTR_UNION;
#endif
#define SOC_ISP_DEBUG_DBG_TOP_REFRESH_WPTR_dbg_top_refresh_ptr_START  (0)
#define SOC_ISP_DEBUG_DBG_TOP_REFRESH_WPTR_dbg_top_refresh_ptr_END    (0)


/*****************************************************************************
 结构名    : SOC_ISP_DEBUG_DBG_TOP_WPTR_UNION
 结构说明  : DBG_TOP_WPTR 寄存器结构定义。地址偏移量:0x20，初值:0x00000000，宽度:32
 寄存器说明: the write pointer deliver to SW
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_top_wptr : 32; /* bit[0-31]: the write pointer send to SOCP */
    } reg;
} SOC_ISP_DEBUG_DBG_TOP_WPTR_UNION;
#endif
#define SOC_ISP_DEBUG_DBG_TOP_WPTR_dbg_top_wptr_START  (0)
#define SOC_ISP_DEBUG_DBG_TOP_WPTR_dbg_top_wptr_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_DEBUG_DBG_IRQ_STOP_TIMER_UNION
 结构说明  : DBG_IRQ_STOP_TIMER 寄存器结构定义。地址偏移量:0x40，初值:0x00000000，宽度:32
 寄存器说明: Interrupt global debug configur register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_irq_timeout : 32; /* bit[0-31]: number of clock cycles before timeout. The maximum value allows a maximum window of 1 second.(upper bits of the 28 bit counter). Value 0 is not authorized. */
    } reg;
} SOC_ISP_DEBUG_DBG_IRQ_STOP_TIMER_UNION;
#endif
#define SOC_ISP_DEBUG_DBG_IRQ_STOP_TIMER_dbg_irq_timeout_START  (0)
#define SOC_ISP_DEBUG_DBG_IRQ_STOP_TIMER_dbg_irq_timeout_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_DEBUG_DBG_IRQ_CFG_UNION
 结构说明  : DBG_IRQ_CFG 寄存器结构定义。地址偏移量:0x44，初值:0x00000000，宽度:32
 寄存器说明: configur of the debugger stop mode
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_irq_enable         : 1;  /* bit[0]    :  */
        unsigned int  reserved_0             : 3;  /* bit[1-3]  :  */
        unsigned int  dbg_irq_stop_mod       : 1;  /* bit[4]    : 0： manual；1：timer */
        unsigned int  reserved_1             : 3;  /* bit[5-7]  :  */
        unsigned int  dbg_irq_start_mod      : 1;  /* bit[8]    : 0 : enable as enable;1 : trigger as enable */
        unsigned int  reserved_2             : 7;  /* bit[9-15] :  */
        unsigned int  dbg_irq_start_trig_idx : 6;  /* bit[16-21]: 0~63: for irq_group[0~63] */
        unsigned int  reserved_3             : 10; /* bit[22-31]:  */
    } reg;
} SOC_ISP_DEBUG_DBG_IRQ_CFG_UNION;
#endif
#define SOC_ISP_DEBUG_DBG_IRQ_CFG_dbg_irq_enable_START          (0)
#define SOC_ISP_DEBUG_DBG_IRQ_CFG_dbg_irq_enable_END            (0)
#define SOC_ISP_DEBUG_DBG_IRQ_CFG_dbg_irq_stop_mod_START        (4)
#define SOC_ISP_DEBUG_DBG_IRQ_CFG_dbg_irq_stop_mod_END          (4)
#define SOC_ISP_DEBUG_DBG_IRQ_CFG_dbg_irq_start_mod_START       (8)
#define SOC_ISP_DEBUG_DBG_IRQ_CFG_dbg_irq_start_mod_END         (8)
#define SOC_ISP_DEBUG_DBG_IRQ_CFG_dbg_irq_start_trig_idx_START  (16)
#define SOC_ISP_DEBUG_DBG_IRQ_CFG_dbg_irq_start_trig_idx_END    (21)


/*****************************************************************************
 结构名    : SOC_ISP_DEBUG_DBG_IRQ_MASK_0_UNION
 结构说明  : DBG_IRQ_MASK_0 寄存器结构定义。地址偏移量:0x4C，初值:0xFFFFFFFF，宽度:32
 寄存器说明: Interrupt Enable debug configuration register 0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_irq_mask0 : 32; /* bit[0-31]: enable bit used to select the interrupts used to trigger a change.(from 31 to 0)
                                                        0: masked
                                                        1: input is taking into account for message triggering */
    } reg;
} SOC_ISP_DEBUG_DBG_IRQ_MASK_0_UNION;
#endif
#define SOC_ISP_DEBUG_DBG_IRQ_MASK_0_dbg_irq_mask0_START  (0)
#define SOC_ISP_DEBUG_DBG_IRQ_MASK_0_dbg_irq_mask0_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_DEBUG_DBG_IRQ_MASK_1_UNION
 结构说明  : DBG_IRQ_MASK_1 寄存器结构定义。地址偏移量:0x50，初值:0xFFFFFFFF，宽度:32
 寄存器说明: Interrupt Enable debug configuration register 1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_irq_mask1 : 32; /* bit[0-31]: enable bit used to select the interrupts used to trigger a change.(from 63 to 32)
                                                        0: masked
                                                        1: input is taking into account for message triggering */
    } reg;
} SOC_ISP_DEBUG_DBG_IRQ_MASK_1_UNION;
#endif
#define SOC_ISP_DEBUG_DBG_IRQ_MASK_1_dbg_irq_mask1_START  (0)
#define SOC_ISP_DEBUG_DBG_IRQ_MASK_1_dbg_irq_mask1_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_DEBUG_DBG_BUS_CFG_UNION
 结构说明  : DBG_BUS_CFG 寄存器结构定义。地址偏移量:0x60，初值:0x00003000，宽度:32
 寄存器说明: configur of the debugger stop mode
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_bus_enable    : 1;  /* bit[0]    :  */
        unsigned int  reserved_0        : 3;  /* bit[1-3]  :  */
        unsigned int  dbg_bus_stop_mod  : 1;  /* bit[4]    : 0： manual；1：timer */
        unsigned int  reserved_1        : 3;  /* bit[5-7]  :  */
        unsigned int  dbg_bus_mask_mod  : 1;  /* bit[8]    : 1:mask by single address,0:mask by 32K */
        unsigned int  reserved_2        : 3;  /* bit[9-11] :  */
        unsigned int  dbg_bus_info_mask : 2;  /* bit[12-13]: bit[0] for write, bit[1] for read */
        unsigned int  reserved_3        : 2;  /* bit[14-15]:  */
        unsigned int  reserved_4        : 16; /* bit[16-31]:  */
    } reg;
} SOC_ISP_DEBUG_DBG_BUS_CFG_UNION;
#endif
#define SOC_ISP_DEBUG_DBG_BUS_CFG_dbg_bus_enable_START     (0)
#define SOC_ISP_DEBUG_DBG_BUS_CFG_dbg_bus_enable_END       (0)
#define SOC_ISP_DEBUG_DBG_BUS_CFG_dbg_bus_stop_mod_START   (4)
#define SOC_ISP_DEBUG_DBG_BUS_CFG_dbg_bus_stop_mod_END     (4)
#define SOC_ISP_DEBUG_DBG_BUS_CFG_dbg_bus_mask_mod_START   (8)
#define SOC_ISP_DEBUG_DBG_BUS_CFG_dbg_bus_mask_mod_END     (8)
#define SOC_ISP_DEBUG_DBG_BUS_CFG_dbg_bus_info_mask_START  (12)
#define SOC_ISP_DEBUG_DBG_BUS_CFG_dbg_bus_info_mask_END    (13)


/*****************************************************************************
 结构名    : SOC_ISP_DEBUG_DBG_BUS_STOP_TIMER_UNION
 结构说明  : DBG_BUS_STOP_TIMER 寄存器结构定义。地址偏移量:0x64，初值:0x00000000，宽度:32
 寄存器说明: Interrupt global debug configur register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_bus_timeout : 32; /* bit[0-31]: number of clock cycles before timeout. The maximum value allows a maximum window of 1 second.(upper bits of the 28 bit counter). Value 0 is not authorized. */
    } reg;
} SOC_ISP_DEBUG_DBG_BUS_STOP_TIMER_UNION;
#endif
#define SOC_ISP_DEBUG_DBG_BUS_STOP_TIMER_dbg_bus_timeout_START  (0)
#define SOC_ISP_DEBUG_DBG_BUS_STOP_TIMER_dbg_bus_timeout_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_DEBUG_DBG_BUS_32K_MASK_UNION
 结构说明  : DBG_BUS_32K_MASK 寄存器结构定义。地址偏移量:0x68，初值:0xFFFFFFFF，宽度:32
 寄存器说明: To Mask the given address
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_bus_addr_32k_mask : 32; /* bit[0-31]:  */
    } reg;
} SOC_ISP_DEBUG_DBG_BUS_32K_MASK_UNION;
#endif
#define SOC_ISP_DEBUG_DBG_BUS_32K_MASK_dbg_bus_addr_32k_mask_START  (0)
#define SOC_ISP_DEBUG_DBG_BUS_32K_MASK_dbg_bus_addr_32k_mask_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_DEBUG_DBG_BUS_SINGLE_MASK_UNION
 结构说明  : DBG_BUS_SINGLE_MASK 寄存器结构定义。地址偏移量:0x6C，初值:0x00000000，宽度:32
 寄存器说明: To Mask a indicated address
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_bus_addr_single_mask : 20; /* bit[0-19] :  */
        unsigned int  reserved                 : 12; /* bit[20-31]:  */
    } reg;
} SOC_ISP_DEBUG_DBG_BUS_SINGLE_MASK_UNION;
#endif
#define SOC_ISP_DEBUG_DBG_BUS_SINGLE_MASK_dbg_bus_addr_single_mask_START  (0)
#define SOC_ISP_DEBUG_DBG_BUS_SINGLE_MASK_dbg_bus_addr_single_mask_END    (19)


/*****************************************************************************
 结构名    : SOC_ISP_DEBUG_DBG_STATIS_MAP_CFG_UNION
 结构说明  : DBG_STATIS_MAP_CFG 寄存器结构定义。地址偏移量:0x70，初值:0x00000000，宽度:32
 寄存器说明: configur of the processing debug map
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_statis_ch0 : 5;  /* bit[0-4]  :  */
        unsigned int  reserved_0     : 3;  /* bit[5-7]  :  */
        unsigned int  dbg_statis_ch1 : 5;  /* bit[8-12] :  */
        unsigned int  reserved_1     : 3;  /* bit[13-15]:  */
        unsigned int  dbg_statis_ch2 : 5;  /* bit[16-20]:  */
        unsigned int  reserved_2     : 3;  /* bit[21-23]:  */
        unsigned int  dbg_statis_ch3 : 5;  /* bit[24-28]:  */
        unsigned int  reserved_3     : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_DEBUG_DBG_STATIS_MAP_CFG_UNION;
#endif
#define SOC_ISP_DEBUG_DBG_STATIS_MAP_CFG_dbg_statis_ch0_START  (0)
#define SOC_ISP_DEBUG_DBG_STATIS_MAP_CFG_dbg_statis_ch0_END    (4)
#define SOC_ISP_DEBUG_DBG_STATIS_MAP_CFG_dbg_statis_ch1_START  (8)
#define SOC_ISP_DEBUG_DBG_STATIS_MAP_CFG_dbg_statis_ch1_END    (12)
#define SOC_ISP_DEBUG_DBG_STATIS_MAP_CFG_dbg_statis_ch2_START  (16)
#define SOC_ISP_DEBUG_DBG_STATIS_MAP_CFG_dbg_statis_ch2_END    (20)
#define SOC_ISP_DEBUG_DBG_STATIS_MAP_CFG_dbg_statis_ch3_START  (24)
#define SOC_ISP_DEBUG_DBG_STATIS_MAP_CFG_dbg_statis_ch3_END    (28)


/*****************************************************************************
 结构名    : SOC_ISP_DEBUG_DBG_STATIS_CFG_UNION
 结构说明  : DBG_STATIS_CFG 寄存器结构定义。地址偏移量:0x74，初值:0x00000000，宽度:32
 寄存器说明: enable
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_statis_enable_ch0 : 1;  /* bit[0]    :  */
        unsigned int  reserved_0            : 3;  /* bit[1-3]  :  */
        unsigned int  dbg_statis_enable_ch1 : 1;  /* bit[4]    :  */
        unsigned int  reserved_1            : 3;  /* bit[5-7]  :  */
        unsigned int  dbg_statis_enable_ch2 : 1;  /* bit[8]    :  */
        unsigned int  reserved_2            : 3;  /* bit[9-11] :  */
        unsigned int  dbg_statis_enable_ch3 : 1;  /* bit[12]   :  */
        unsigned int  reserved_3            : 3;  /* bit[13-15]:  */
        unsigned int  reserved_4            : 16; /* bit[16-31]:  */
    } reg;
} SOC_ISP_DEBUG_DBG_STATIS_CFG_UNION;
#endif
#define SOC_ISP_DEBUG_DBG_STATIS_CFG_dbg_statis_enable_ch0_START  (0)
#define SOC_ISP_DEBUG_DBG_STATIS_CFG_dbg_statis_enable_ch0_END    (0)
#define SOC_ISP_DEBUG_DBG_STATIS_CFG_dbg_statis_enable_ch1_START  (4)
#define SOC_ISP_DEBUG_DBG_STATIS_CFG_dbg_statis_enable_ch1_END    (4)
#define SOC_ISP_DEBUG_DBG_STATIS_CFG_dbg_statis_enable_ch2_START  (8)
#define SOC_ISP_DEBUG_DBG_STATIS_CFG_dbg_statis_enable_ch2_END    (8)
#define SOC_ISP_DEBUG_DBG_STATIS_CFG_dbg_statis_enable_ch3_START  (12)
#define SOC_ISP_DEBUG_DBG_STATIS_CFG_dbg_statis_enable_ch3_END    (12)






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

#endif /* end of soc_isp_debug_interface.h */
