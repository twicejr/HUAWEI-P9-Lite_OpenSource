

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

/* 寄存器说明：configur of the processing debug map
   位域定义UNION结构:  SOC_ISP_DEBUG_DBG_STATIS_MAP_CFG_UNION */
#define SOC_ISP_DEBUG_DBG_STATIS_MAP_CFG_ADDR(base)   ((base) + (0x70))

/* 寄存器说明：enable
   位域定义UNION结构:  SOC_ISP_DEBUG_DBG_STATIS_CFG_UNION */
#define SOC_ISP_DEBUG_DBG_STATIS_CFG_ADDR(base)       ((base) + (0x74))

/* 寄存器说明：Generic source configuration
   位域定义UNION结构:  SOC_ISP_DEBUG_DBG_VCD_SRC_CFG_UNION */
#define SOC_ISP_DEBUG_DBG_VCD_SRC_CFG_ADDR(base)      ((base) + (0x78))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_DEBUG_DBG_VCD_SRC_FILTER_UNION */
#define SOC_ISP_DEBUG_DBG_VCD_SRC_FILTER_ADDR(base)   ((base) + (0x7C))

/* 寄存器说明：General Access debugger configuration
   位域定义UNION结构:  SOC_ISP_DEBUG_DBG_BUS_CFG_UNION */
#define SOC_ISP_DEBUG_DBG_BUS_CFG_ADDR(base, Range2)  ((base) + (0x80+0x60*(Range2)))

/* 寄存器说明：configure of the debugger stop mode
   位域定义UNION结构:  SOC_ISP_DEBUG_DBG_BUS_STOP_TIMER_UNION */
#define SOC_ISP_DEBUG_DBG_BUS_STOP_TIMER_ADDR(base, Range2)  ((base) + (0x84+0x60*(Range2)))

/* 寄存器说明：configure data match pattern if applicable
   位域定义UNION结构:  SOC_ISP_DEBUG_DBG_BUS_DATA_MATCH_UNION */
#define SOC_ISP_DEBUG_DBG_BUS_DATA_MATCH_ADDR(base, Range2)  ((base) + (0x88+0x60*(Range2)))

/* 寄存器说明：Configure the start address of the range (if enabled)
   位域定义UNION结构:  SOC_ISP_DEBUG_DBG_BUS_ADDR_START_UNION */
#define SOC_ISP_DEBUG_DBG_BUS_ADDR_START_ADDR(base, Range2, Range8)  ((base) + (0x80+0x10+0x60*(Range2)+0x8*(Range8)))

/* 寄存器说明：Configure the end address of the range (if enabled)
   位域定义UNION结构:  SOC_ISP_DEBUG_DBG_BUS_ADDR_END_UNION */
#define SOC_ISP_DEBUG_DBG_BUS_ADDR_END_ADDR(base, Range2, Range8)  ((base) + (0x80+0x14+0x60*(Range2)+0x8*(Range8)))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ISP_DEBUG_ILA_CTRL_UNION */
#define SOC_ISP_DEBUG_ILA_CTRL_ADDR(base)             ((base) + (0x180))





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
        unsigned int  dbg_top_proc_enable : 1;  /* bit[0]   : enable or not the processing debug logic.
                                                              Once enabled, the statistics will be generated on every end of line, starting from a start of frame.
                                                              This register is working as a shadow register (but shadowing is performed into an FSM).
                                                              If disabled, the video port in is directly sent to the video port out (feedthrough) */
        unsigned int  reserved_0          : 3;  /* bit[1-3] :  */
        unsigned int  dbg_top_stop_mod    : 1;  /* bit[4]   : 0： manual；1：timer */
        unsigned int  reserved_1          : 27; /* bit[5-31]:  */
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
        unsigned int  dbg_top_subframe_num : 11; 
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
        unsigned int  dbg_top_buf_line_stride : 10; 
        unsigned int  reserved_0              : 6;  /* bit[10-15]: reserved */
        unsigned int  dbg_top_buf_line_wrap   : 13; /* bit[16-28]: Line wrap: wrap to frame start location (13 bits)
                                                                   0: wrap every line
                                                                   1: wrap every 2 lines
                                                                   …
                                                                   8191: wrap every 8192 lines
                                                                   determined by the buffer depth assign by the system, it should equal to (buffer depth)/stride -1, of course it should aligned with 16Byte. */
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
        unsigned int  dbg_irq_enable         : 1;  /* bit[0]    : enables the event debugger */
        unsigned int  reserved_0             : 3;  /* bit[1-3]  :  */
        unsigned int  dbg_irq_stop_mod       : 1;  /* bit[4]    : 0： manual；1：timer */
        unsigned int  reserved_1             : 3;  /* bit[5-7]  :  */
        unsigned int  dbg_irq_start_mod      : 1;  /* bit[8]    : 0 : enable as enable;1 : trigger as enable */
        unsigned int  reserved_2             : 7;  /* bit[9-15] :  */
        unsigned int  dbg_irq_start_trig_idx : 6;  /* bit[16-21]: 0~63: for irq_group[0~63]
                                                                  0 SOF OTAP_1_1 W 0
                                                                  1 EOF OTAP_1_1 W 0
                                                                  2 SOF OTAP_2_1 W 14
                                                                  3 EOF OTAP_2_1 W 14
                                                                  4 SOF SCLAER_1_1 Y W 8
                                                                  5 EOF SCLAER_1_1 Y W 8
                                                                  6 SOF SCALER_1_1 UV W 9
                                                                  7 EOF SCALER_1_1 UV W 9
                                                                  8 SOF FBCRAW_1_1 W 16
                                                                  9 EOF FBCRAW_1_1 W 16
                                                                  10 SOF FBCRAW_1_2 W 17
                                                                  11 EOF FBCRAW_1_2 W 17
                                                                  12 SOF FBCRAW_2_1 W 18
                                                                  13 EOF FBCRAW_2_1 W 18
                                                                  14 SOF FBCRAW_2_2 W 19
                                                                  15 EOF FBCRAW_2_2 W 19
                                                                  16 SOF STAT3A_1 W 20
                                                                  17 EOF STAT3A_1 W 20
                                                                  18 SOF STAT3A_2 W 21
                                                                  19 EOF STAT3A_2 W 21
                                                                  20 SOF STREAMROUTER W 22
                                                                  21 EOF STREAMROUTER W 22
                                                                  22 SOF STREAMROUTER W 23
                                                                  23 EOF STREAMROUTER W 23
                                                                  24 SOF STREAMROUTER W 24
                                                                  25 EOF STREAMROUTER W 24
                                                                  26 SOF JPEG W 25
                                                                  27 EOF JPEG W 25
                                                                  28 SOF CMDLST W 26
                                                                  29 EOF CMDLST W 26
                                                                  30 SOF STREAMROUTER W 27
                                                                  31 EOF STREAMROUTER W27
                                                                  32 SOF SCALER_1 R0
                                                                  33 EOF SCALER_1 R0
                                                                  34 SOF ITAP_1_1 R4
                                                                  35 EOF ITAP_1_1 R4
                                                                  36 SOF ITAP_2_1 R5
                                                                  37 EOF ITAP_2_1 R5
                                                                  38 SOF ISP_FE_1 R8
                                                                  39 EOF ISP_FE_1 R8
                                                                  40 SOF ISP_FE_1 R9
                                                                  41 EOF ISP_FE_1 R9
                                                                  42 Cvdr_axi_wr_full CVDR 
                                                                  43 reserved 
                                                                  44 reserved 
                                                                  45 Scaler_1_1_start_of_frame_evt SCALER_1_1 
                                                                  46 Scaler_1_1_end_of_rescale_evt SCALER_1_1 
                                                                  47 reserved 
                                                                  48 reserved 
                                                                  49 Scaler_2_1_start_of_frame_evt SCALER_2_1 
                                                                  50 Scaler_2_1_end_of_rescale_evt SCALER_2_1 
                                                                  51 reserved 
                                                                  52 reserved 
                                                                  53 Stream_router_cam_a_ovf_evt STREAMROUTER 
                                                                  54 Stream_router_reformater_err_0_evt STREAMROUTER 
                                                                  55 Stream_router_reformater_sof_0_evt STREAMROUTER 
                                                                  56 Stream_router_reformater_frame_dropped_0_evt STREAMROUTER 
                                                                  57 reserved 
                                                                  58 Flash_capture FLSH_CTRL 
                                                                  59 Dram_intp_cvdr_axi_wr_resp_err CVDR 
                                                                  60 Dram_intp_cvdr_axi_rd_resp_err CVDR 
                                                                  61 Isp_pressure posedge STREAMROUTER 
                                                                  62 Isp_pressure negedge STREAMROUTER 
                                                                  63 Vsync posedge CSI  */
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
                                                        1: input is taking into account for message triggering
                                                        [Note]:please keep bit[31] 1 since there may be some confusion report since some asynchronous
                                                        [End] */
    } reg;
} SOC_ISP_DEBUG_DBG_IRQ_MASK_1_UNION;
#endif
#define SOC_ISP_DEBUG_DBG_IRQ_MASK_1_dbg_irq_mask1_START  (0)
#define SOC_ISP_DEBUG_DBG_IRQ_MASK_1_dbg_irq_mask1_END    (31)


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
        unsigned int  dbg_statis_ch0 : 6;  /* bit[0-5]  : VP of DEBUG VP of CVDR Source Description
                                                          0 R3.1 SCALER_1_1 0
                                                          1 R11.1 ITAP_1_1 4
                                                          2 R12.1 ITAP_2_1 5
                                                          3 R11.2 ITAP_1_2 6
                                                          4 F12.2 ITAP_2_2 7
                                                          5 R10.1 ISP_FE_1 8
                                                          6 R10.2 ISP_FE_2 9
                                                          7 R2.1 CMDLST 10
                                                          8 Reserved Reserved Reserved
                                                          9 Reserved Reserved Reserved
                                                          10 W12.1 OTAP_1_1 0
                                                          11 W12.2 OTAP_1_2 1
                                                          12 W5.1.1 SCLAER_2_1 Y 4
                                                          13 W5.1.2 SCLAER_2_1UV 5
                                                          14 W4.1.1 SCLAER_1_1Y 8
                                                          15 W4.1.2 SCLAER_1_1UV 9
                                                          16 W13.1 OTAP_2_1 14
                                                          17 W13.2 OTAP_2_2 15
                                                          18 W1.1 FBCRAW_1_1 16
                                                          19 W1.2 FBCRAW_2_1 17
                                                          20 W14.1 FBCRAW_1_2 18
                                                          21 W14.2 FBCRAW_2_2 19
                                                          22 W11.1 STAT3A_1 20
                                                          23 W11.2 STAT3A_2 21
                                                          24 W2.3 STREAMROUTER 22
                                                          25 W2.4 STREAMROUTER 23
                                                          26 W2.5 STREAMROUTER 24
                                                          27 Reserved Reserved Reserved
                                                          28 W8.1 JEPG 25
                                                          29 W3.1 CMDLST 26
                                                          30 W2.2 STREAMROUTER 27
                                                          31 Reserved Reserved Reserved
                                                          32 Reserved Reserved Reserved
                                                          33 SR2FE0 STREAMROUTER FE0 input
                                                          34 SR2FE1 STREAMROUTER FE1 input
                                                          35 FE0_OUT1 FE0 FE0 output 14bit
                                                          36 FE0_OUT2 FE0 FE0 output 28bit(2PF)
                                                          37 FE0_OUT1 FE1 FE1 output 14bit 
                                                          38 FE0_OUT2 FE1 FE1 output 28bit(2PF)
                                                          39 BE_IN FBDRAW BE input
                                                          40 BE_OUT BE BE output to sclaer
                                                          41 reserved reserved reserved
                                                          42 reserved reserved reserved
                                                          43 Ptreg_out PTREG BE
                                                          44 Lsc_out LSC BE
                                                          45 Rawnf_in RAWNF BE
                                                          46 Rawnf_out RAWNF BE
                                                          47 Gcd_in GCD BE
                                                          48 Gcd_out GCD BE
                                                          49 Uvup_out UVUP BE
                                                          50 Cc_out CC BE
                                                          51 Drc_out DRC BE
                                                          52 Gamma_out GAMMA BE
                                                          53 Rgd2yuv_out RGB2YUV BE
                                                          54 Uvdec_out UVDEC BE
                                                          55 Ce_out CE BE
                                                          56 Yuvnf_out_y YUVNF BE Y
                                                          57 Yuvnf_out_uv YUVNF U BE V
                                                          58 BLS2DGAM BLS_1 FE0
                                                          59 DGAM2VPB DEGAMMA_1 FE0
                                                          60 PDAF_OUT PDAF_1 FE0
                                                          61 STAT3A STAT3A_1 FE0
                                                          62 BLS2DGAM BLS_2 FE1
                                                          63 DGAM2VPB DEGAMMA_2 FE1
                                                           PDAF_OUT PDAF_2 FE1: not connected
                                                           STAT3A STAT3A_2 FE1: not connected */
        unsigned int  reserved_0     : 2;  /* bit[6-7]  :  */
        unsigned int  dbg_statis_ch1 : 6;  /* bit[8-13] : Ref. dgb_statis_ch0 */
        unsigned int  reserved_1     : 2;  /* bit[14-15]:  */
        unsigned int  dbg_statis_ch2 : 6;  /* bit[16-21]: Ref. dgb_statis_ch0 */
        unsigned int  reserved_2     : 2;  /* bit[22-23]:  */
        unsigned int  dbg_statis_ch3 : 6;  /* bit[24-29]: Ref. dgb_statis_ch0 */
        unsigned int  reserved_3     : 2;  /* bit[30-31]:  */
    } reg;
} SOC_ISP_DEBUG_DBG_STATIS_MAP_CFG_UNION;
#endif
#define SOC_ISP_DEBUG_DBG_STATIS_MAP_CFG_dbg_statis_ch0_START  (0)
#define SOC_ISP_DEBUG_DBG_STATIS_MAP_CFG_dbg_statis_ch0_END    (5)
#define SOC_ISP_DEBUG_DBG_STATIS_MAP_CFG_dbg_statis_ch1_START  (8)
#define SOC_ISP_DEBUG_DBG_STATIS_MAP_CFG_dbg_statis_ch1_END    (13)
#define SOC_ISP_DEBUG_DBG_STATIS_MAP_CFG_dbg_statis_ch2_START  (16)
#define SOC_ISP_DEBUG_DBG_STATIS_MAP_CFG_dbg_statis_ch2_END    (21)
#define SOC_ISP_DEBUG_DBG_STATIS_MAP_CFG_dbg_statis_ch3_START  (24)
#define SOC_ISP_DEBUG_DBG_STATIS_MAP_CFG_dbg_statis_ch3_END    (29)


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
 结构名    : SOC_ISP_DEBUG_DBG_VCD_SRC_CFG_UNION
 结构说明  : DBG_VCD_SRC_CFG 寄存器结构定义。地址偏移量:0x78，初值:0x00000000，宽度:32
 寄存器说明: Generic source configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_vcd_src_0 : 5;  /* bit[0-4]  : used to select the 16-bits source of the first 16-bits of the 64 vcd bus */
        unsigned int  reserved_0    : 3;  /* bit[5-7]  :  */
        unsigned int  dbg_vcd_src_1 : 5;  /* bit[8-12] : used to select the 16-bits source of the second 16-bits of the 64 vcd bus */
        unsigned int  reserved_1    : 3;  /* bit[13-15]:  */
        unsigned int  dbg_vcd_src_2 : 5;  /* bit[16-20]: used to select the 16-bits source of the third 16-bits of the 64 vcd bus */
        unsigned int  reserved_2    : 3;  /* bit[21-23]:  */
        unsigned int  dbg_vcd_src_3 : 5;  /* bit[24-28]: used to select the 16-bits source of the fourth 16-bits of the 64 vcd bus */
        unsigned int  reserved_3    : 3;  /* bit[29-31]:  */
    } reg;
} SOC_ISP_DEBUG_DBG_VCD_SRC_CFG_UNION;
#endif
#define SOC_ISP_DEBUG_DBG_VCD_SRC_CFG_dbg_vcd_src_0_START  (0)
#define SOC_ISP_DEBUG_DBG_VCD_SRC_CFG_dbg_vcd_src_0_END    (4)
#define SOC_ISP_DEBUG_DBG_VCD_SRC_CFG_dbg_vcd_src_1_START  (8)
#define SOC_ISP_DEBUG_DBG_VCD_SRC_CFG_dbg_vcd_src_1_END    (12)
#define SOC_ISP_DEBUG_DBG_VCD_SRC_CFG_dbg_vcd_src_2_START  (16)
#define SOC_ISP_DEBUG_DBG_VCD_SRC_CFG_dbg_vcd_src_2_END    (20)
#define SOC_ISP_DEBUG_DBG_VCD_SRC_CFG_dbg_vcd_src_3_START  (24)
#define SOC_ISP_DEBUG_DBG_VCD_SRC_CFG_dbg_vcd_src_3_END    (28)


/*****************************************************************************
 结构名    : SOC_ISP_DEBUG_DBG_VCD_SRC_FILTER_UNION
 结构说明  : DBG_VCD_SRC_FILTER 寄存器结构定义。地址偏移量:0x7C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_vcd_l16_value : 16; /* bit[0-15] : start trigger condition value */
        unsigned int  dbg_vcd_l16_mask  : 16; /* bit[16-31]: used to set the trigger condition: mask=1,need to match with dbg_vcd_h16_value;mask=0, don't care; only match the data selected by dbg_vcd_src_0  */
    } reg;
} SOC_ISP_DEBUG_DBG_VCD_SRC_FILTER_UNION;
#endif
#define SOC_ISP_DEBUG_DBG_VCD_SRC_FILTER_dbg_vcd_l16_value_START  (0)
#define SOC_ISP_DEBUG_DBG_VCD_SRC_FILTER_dbg_vcd_l16_value_END    (15)
#define SOC_ISP_DEBUG_DBG_VCD_SRC_FILTER_dbg_vcd_l16_mask_START   (16)
#define SOC_ISP_DEBUG_DBG_VCD_SRC_FILTER_dbg_vcd_l16_mask_END     (31)


/*****************************************************************************
 结构名    : SOC_ISP_DEBUG_DBG_BUS_CFG_UNION
 结构说明  : DBG_BUS_CFG 寄存器结构定义。地址偏移量:0x80+0x60*(Range2)，初值:0x10030400，宽度:32
 寄存器说明: General Access debugger configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_bus_enable            : 1;  /* bit[0]    : enable bit for access debugguer */
        unsigned int  reserved_0                : 3;  /* bit[1-3]  :  */
        unsigned int  dbg_bus_stop_mod          : 1;  /* bit[4]    : 0： manual；1：timer */
        unsigned int  reserved_1                : 3;  /* bit[5-7]  :  */
        unsigned int  dbg_bus_src               : 4;  /* bit[8-11] : Input source:
                                                                     0: AXI write Req
                                                                     1: AXI write Resp
                                                                     2: AXI Read Req
                                                                     3: AXI Read Resp
                                                                     4: Config
                                                                     5: AXI prefetch Req
                                                                     6: AXI prefetch Resp
                                                                     7: Generic interface (64 bits of effective data, strongly recommended to use SRC to '1111' for SW debug and need to implemented the miss function outside of the debug module)
                                                                     8: Enables VCD tracing functionality */
        unsigned int  dbg_bus_msg_format        : 2;  /* bit[12-13]: Used to dump different msg formats.
                                                                     0: debug message is address/data 
                                                                     1: debug message is info/address
                                                                     2: debug message is info/data
                                                                     3: same as 0 */
        unsigned int  dbg_bus_stall_limit       : 2;  /* bit[14-15]: Allows to specify the stall bits (16 bits clipped counter) reported by the debug module
                                                                     0: 7:0 stall counter is reported and the counter is clipping at 0xFF
                                                                     1: 11:4 stall counter is reported and the counter is clipping at 0xFFF
                                                                     2: 15:8 stall counter is reported and the counter is clipping at 0xFFFF
                                                                     3: same behavior as 0 */
        unsigned int  dbg_bus_wr_enable         : 1;  /* bit[16]   : Enables write transactions to be reported：1 enable，0： disable */
        unsigned int  dbg_bus_rd_enable         : 1;  /* bit[17]   : Enables read transactions to be reported：1 enable，0： disable */
        unsigned int  reserved_2                : 2;  /* bit[18-19]:  */
        unsigned int  dbg_bus_data_mask_enable  : 1;  /* bit[20]   : Enables data mask check：1 enable，0： disable */
        unsigned int  dbg_bus_data_location     : 2;  /* bit[21-22]: Used to specify the location of the 32-bits data to be sent to DRAM
                                                                     0: 31:0 data bus is used (generally config interface)
                                                                     1: 63:32 data bus is used (can be used on AXI interface)
                                                                     2: 95:64 data bus is used (can be used on AXI interface)
                                                                     3: 127:96 data bus is used (can be used on AXI interface) */
        unsigned int  reserved_3                : 1;  /* bit[23]   :  */
        unsigned int  dbg_bus_addr_range_enable : 4;  /* bit[24-27]: Enable bits for the Address range comparators */
        unsigned int  reserved_4                : 4;  /* bit[28-31]:  */
    } reg;
} SOC_ISP_DEBUG_DBG_BUS_CFG_UNION;
#endif
#define SOC_ISP_DEBUG_DBG_BUS_CFG_dbg_bus_enable_START             (0)
#define SOC_ISP_DEBUG_DBG_BUS_CFG_dbg_bus_enable_END               (0)
#define SOC_ISP_DEBUG_DBG_BUS_CFG_dbg_bus_stop_mod_START           (4)
#define SOC_ISP_DEBUG_DBG_BUS_CFG_dbg_bus_stop_mod_END             (4)
#define SOC_ISP_DEBUG_DBG_BUS_CFG_dbg_bus_src_START                (8)
#define SOC_ISP_DEBUG_DBG_BUS_CFG_dbg_bus_src_END                  (11)
#define SOC_ISP_DEBUG_DBG_BUS_CFG_dbg_bus_msg_format_START         (12)
#define SOC_ISP_DEBUG_DBG_BUS_CFG_dbg_bus_msg_format_END           (13)
#define SOC_ISP_DEBUG_DBG_BUS_CFG_dbg_bus_stall_limit_START        (14)
#define SOC_ISP_DEBUG_DBG_BUS_CFG_dbg_bus_stall_limit_END          (15)
#define SOC_ISP_DEBUG_DBG_BUS_CFG_dbg_bus_wr_enable_START          (16)
#define SOC_ISP_DEBUG_DBG_BUS_CFG_dbg_bus_wr_enable_END            (16)
#define SOC_ISP_DEBUG_DBG_BUS_CFG_dbg_bus_rd_enable_START          (17)
#define SOC_ISP_DEBUG_DBG_BUS_CFG_dbg_bus_rd_enable_END            (17)
#define SOC_ISP_DEBUG_DBG_BUS_CFG_dbg_bus_data_mask_enable_START   (20)
#define SOC_ISP_DEBUG_DBG_BUS_CFG_dbg_bus_data_mask_enable_END     (20)
#define SOC_ISP_DEBUG_DBG_BUS_CFG_dbg_bus_data_location_START      (21)
#define SOC_ISP_DEBUG_DBG_BUS_CFG_dbg_bus_data_location_END        (22)
#define SOC_ISP_DEBUG_DBG_BUS_CFG_dbg_bus_addr_range_enable_START  (24)
#define SOC_ISP_DEBUG_DBG_BUS_CFG_dbg_bus_addr_range_enable_END    (27)


/*****************************************************************************
 结构名    : SOC_ISP_DEBUG_DBG_BUS_STOP_TIMER_UNION
 结构说明  : DBG_BUS_STOP_TIMER 寄存器结构定义。地址偏移量:0x84+0x60*(Range2)，初值:0x00000000，宽度:32
 寄存器说明: configure of the debugger stop mode
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
 结构名    : SOC_ISP_DEBUG_DBG_BUS_DATA_MATCH_UNION
 结构说明  : DBG_BUS_DATA_MATCH 寄存器结构定义。地址偏移量:0x88+0x60*(Range2)，初值:0x00000000，宽度:32
 寄存器说明: configure data match pattern if applicable
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_bus_data_match : 32; /* bit[0-31]: In case data has to be checked, dbg_bus_data_match is used to compare agains the input data */
    } reg;
} SOC_ISP_DEBUG_DBG_BUS_DATA_MATCH_UNION;
#endif
#define SOC_ISP_DEBUG_DBG_BUS_DATA_MATCH_dbg_bus_data_match_START  (0)
#define SOC_ISP_DEBUG_DBG_BUS_DATA_MATCH_dbg_bus_data_match_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_DEBUG_DBG_BUS_ADDR_START_UNION
 结构说明  : DBG_BUS_ADDR_START 寄存器结构定义。地址偏移量:0x80+0x10+0x60*(Range2)+0x8*(Range8)，初值:0x00000000，宽度:32
 寄存器说明: Configure the start address of the range (if enabled)
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved                 : 2;  /* bit[0-1] :  */
        unsigned int  dbg_bus_addr_range_start : 30; /* bit[2-31]: Start address of the range (value included) */
    } reg;
} SOC_ISP_DEBUG_DBG_BUS_ADDR_START_UNION;
#endif
#define SOC_ISP_DEBUG_DBG_BUS_ADDR_START_dbg_bus_addr_range_start_START  (2)
#define SOC_ISP_DEBUG_DBG_BUS_ADDR_START_dbg_bus_addr_range_start_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_DEBUG_DBG_BUS_ADDR_END_UNION
 结构说明  : DBG_BUS_ADDR_END 寄存器结构定义。地址偏移量:0x80+0x14+0x60*(Range2)+0x8*(Range8)，初值:0xFFFFFFFC，宽度:32
 寄存器说明: Configure the end address of the range (if enabled)
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved               : 2;  /* bit[0-1] :  */
        unsigned int  dbg_bus_addr_range_end : 30; /* bit[2-31]: End address of the range (Value included) */
    } reg;
} SOC_ISP_DEBUG_DBG_BUS_ADDR_END_UNION;
#endif
#define SOC_ISP_DEBUG_DBG_BUS_ADDR_END_dbg_bus_addr_range_end_START  (2)
#define SOC_ISP_DEBUG_DBG_BUS_ADDR_END_dbg_bus_addr_range_end_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_DEBUG_ILA_CTRL_UNION
 结构说明  : ILA_CTRL 寄存器结构定义。地址偏移量:0x180，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ila_vpwdata_idx_0 : 5;  /* bit[0-4]  : select the VP data from the 64 VP write */
        unsigned int  ila_vpwdata_idx_1 : 5;  /* bit[5-9]  : select the VP data from the 64 VP write */
        unsigned int  ila_vprdata_idx_0 : 5;  /* bit[10-14]: select the VP data from the 64 VP read */
        unsigned int  ila_vprdata_idx_1 : 5;  /* bit[15-19]: select the VP data from the 64 VP read */
        unsigned int  ila_intf_6_idx    : 4;  /* bit[20-23]: select the ila trace :
                                                             4'd0:csi;
                                                             4'd1:streamrouter
                                                             4'd2:fbcraw1
                                                             4'd3:fbcraw2
                                                             4'd4:fbdraw
                                                             4'd5:jpg
                                                             4'd6:scaler
                                                             4'd7:bus
                                                             4'd8:reserved
                                                             4'd9:reserved
                                                             4'd10:fe1
                                                             4'd11:fe2
                                                             4'd12:be1
                                                             other:reserved */
        unsigned int  ila_intf_7_idx    : 4;  /* bit[24-27]: select the ila trace :
                                                             4'd0:csi;
                                                             4'd1:streamrouter
                                                             4'd2:fbcraw1
                                                             4'd3:fbcraw2
                                                             4'd4:fbdraw
                                                             4'd5:jpg
                                                             4'd6:scaler
                                                             4'd7:bus
                                                             4'd8:reserved
                                                             4'd9:reserved
                                                             4'd10:fe1
                                                             4'd11:fe2
                                                             4'd12:be1
                                                             other:reserved */
        unsigned int  ila_ctrl_reserved : 4;  /* bit[28-31]: reserved for other use */
    } reg;
} SOC_ISP_DEBUG_ILA_CTRL_UNION;
#endif
#define SOC_ISP_DEBUG_ILA_CTRL_ila_vpwdata_idx_0_START  (0)
#define SOC_ISP_DEBUG_ILA_CTRL_ila_vpwdata_idx_0_END    (4)
#define SOC_ISP_DEBUG_ILA_CTRL_ila_vpwdata_idx_1_START  (5)
#define SOC_ISP_DEBUG_ILA_CTRL_ila_vpwdata_idx_1_END    (9)
#define SOC_ISP_DEBUG_ILA_CTRL_ila_vprdata_idx_0_START  (10)
#define SOC_ISP_DEBUG_ILA_CTRL_ila_vprdata_idx_0_END    (14)
#define SOC_ISP_DEBUG_ILA_CTRL_ila_vprdata_idx_1_START  (15)
#define SOC_ISP_DEBUG_ILA_CTRL_ila_vprdata_idx_1_END    (19)
#define SOC_ISP_DEBUG_ILA_CTRL_ila_intf_6_idx_START     (20)
#define SOC_ISP_DEBUG_ILA_CTRL_ila_intf_6_idx_END       (23)
#define SOC_ISP_DEBUG_ILA_CTRL_ila_intf_7_idx_START     (24)
#define SOC_ISP_DEBUG_ILA_CTRL_ila_intf_7_idx_END       (27)
#define SOC_ISP_DEBUG_ILA_CTRL_ila_ctrl_reserved_START  (28)
#define SOC_ISP_DEBUG_ILA_CTRL_ila_ctrl_reserved_END    (31)






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
