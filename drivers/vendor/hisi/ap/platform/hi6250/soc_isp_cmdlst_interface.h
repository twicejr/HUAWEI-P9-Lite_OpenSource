

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_ISP_CMDLST_INTERFACE_H__
#define __SOC_ISP_CMDLST_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) CMDLST
 ****************************************************************************/
/* 寄存器说明：Module Identifier
   位域定义UNION结构:  SOC_ISP_CMDLST_CMDLST_ID_UNION */
#define SOC_ISP_CMDLST_CMDLST_ID_ADDR(base)           ((base) + (0x0))

/* 寄存器说明：Module Version
   位域定义UNION结构:  SOC_ISP_CMDLST_CMDLST_VERSION_UNION */
#define SOC_ISP_CMDLST_CMDLST_VERSION_ADDR(base)      ((base) + (0x4))

/* 寄存器说明：Module configuration
   位域定义UNION结构:  SOC_ISP_CMDLST_CMDLST_CFG_UNION */
#define SOC_ISP_CMDLST_CMDLST_CFG_ADDR(base)          ((base) + (0x20))

/* 寄存器说明：Debug register (available over the debug bus, lower part)
   位域定义UNION结构:  SOC_ISP_CMDLST_CMDLST_DEBUG_0_UNION */
#define SOC_ISP_CMDLST_CMDLST_DEBUG_0_ADDR(base)      ((base) + (0x40))

/* 寄存器说明：Debug register
   位域定义UNION结构:  SOC_ISP_CMDLST_CMDLST_DEBUG_1_UNION */
#define SOC_ISP_CMDLST_CMDLST_DEBUG_1_ADDR(base)      ((base) + (0x44))

/* 寄存器说明：Debug register (available over the debug bus, upper part)
   位域定义UNION结构:  SOC_ISP_CMDLST_CMDLST_DEBUG_2_UNION */
#define SOC_ISP_CMDLST_CMDLST_DEBUG_2_ADDR(base)      ((base) + (0x48))

/* 寄存器说明：Debug register
   位域定义UNION结构:  SOC_ISP_CMDLST_CMDLST_DEBUG_3_UNION */
#define SOC_ISP_CMDLST_CMDLST_DEBUG_3_ADDR(base)      ((base) + (0x4C))

/* 寄存器说明：Debug register
   位域定义UNION结构:  SOC_ISP_CMDLST_CMDLST_DEBUG_4_UNION */
#define SOC_ISP_CMDLST_CMDLST_DEBUG_4_ADDR(base)      ((base) + (0x50))

/* 寄存器说明：CVDR Video port read address to write the configuration data (CMDLST_SW_CVDR_RD_DATA*)
   位域定义UNION结构:  SOC_ISP_CMDLST_CMDLST_SW_CVDR_RD_ADDR_UNION */
#define SOC_ISP_CMDLST_CMDLST_SW_CVDR_RD_ADDR_ADDR(base, CHANNEL_NBR_range)  ((base) + (0x80+0x80*(CHANNEL_NBR_range)))

/* 寄存器说明：1st Data to write (VP_RD_CFG)
   位域定义UNION结构:  SOC_ISP_CMDLST_CMDLST_SW_CVDR_RD_DATA_0_UNION */
#define SOC_ISP_CMDLST_CMDLST_SW_CVDR_RD_DATA_0_ADDR(base, CHANNEL_NBR_range)  ((base) + (0x84+0x80*(CHANNEL_NBR_range)))

/* 寄存器说明：2nd data to write (VP_RD_LWG)
   位域定义UNION结构:  SOC_ISP_CMDLST_CMDLST_SW_CVDR_RD_DATA_1_UNION */
#define SOC_ISP_CMDLST_CMDLST_SW_CVDR_RD_DATA_1_ADDR(base, CHANNEL_NBR_range)  ((base) + (0x88+0x80*(CHANNEL_NBR_range)))

/* 寄存器说明：3rd Data to write (VP_RD_FHG)
   位域定义UNION结构:  SOC_ISP_CMDLST_CMDLST_SW_CVDR_RD_DATA_2_UNION */
#define SOC_ISP_CMDLST_CMDLST_SW_CVDR_RD_DATA_2_ADDR(base, CHANNEL_NBR_range)  ((base) + (0x8C+0x80*(CHANNEL_NBR_range)))

/* 寄存器说明：4th Data to write (VP_RD_AXI_FS)
   位域定义UNION结构:  SOC_ISP_CMDLST_CMDLST_SW_CVDR_RD_DATA_3_UNION */
#define SOC_ISP_CMDLST_CMDLST_SW_CVDR_RD_DATA_3_ADDR(base, CHANNEL_NBR_range)  ((base) + (0x90+0x80*(CHANNEL_NBR_range)))

/* 寄存器说明：Branching request
   位域定义UNION结构:  SOC_ISP_CMDLST_CMDLST_SW_BRANCH_UNION */
#define SOC_ISP_CMDLST_CMDLST_SW_BRANCH_ADDR(base, CHANNEL_NBR_range)  ((base) + (0xA0+0x80*(CHANNEL_NBR_range)))

/* 寄存器说明：last CVDR_RD_DATA_3 information used to configure the CVDR
   位域定义UNION结构:  SOC_ISP_CMDLST_CMDLST_LAST_EXEC_RD_DATA_3_UNION */
#define SOC_ISP_CMDLST_CMDLST_LAST_EXEC_RD_DATA_3_ADDR(base, CHANNEL_NBR_range)  ((base) + (0xA4+0x80*(CHANNEL_NBR_range)))

/* 寄存器说明：CVDR Video port read address to write the configuration data (CMDLST_HW_CVDR_RD_DATA*)
   位域定义UNION结构:  SOC_ISP_CMDLST_CMDLST_HW_CVDR_RD_ADDR_UNION */
#define SOC_ISP_CMDLST_CMDLST_HW_CVDR_RD_ADDR_ADDR(base, CHANNEL_NBR_range)  ((base) + (0xC0+0x80*(CHANNEL_NBR_range)))

/* 寄存器说明：1st Data to write (VP_RD_CFG)
   位域定义UNION结构:  SOC_ISP_CMDLST_CMDLST_HW_CVDR_RD_DATA_0_UNION */
#define SOC_ISP_CMDLST_CMDLST_HW_CVDR_RD_DATA_0_ADDR(base, CHANNEL_NBR_range)  ((base) + (0xC4+0x80*(CHANNEL_NBR_range)))

/* 寄存器说明：2nd data to write (VP_RD_LWG)
   位域定义UNION结构:  SOC_ISP_CMDLST_CMDLST_HW_CVDR_RD_DATA_1_UNION */
#define SOC_ISP_CMDLST_CMDLST_HW_CVDR_RD_DATA_1_ADDR(base, CHANNEL_NBR_range)  ((base) + (0xC8+0x80*(CHANNEL_NBR_range)))

/* 寄存器说明：3rd Data to write (VP_RD_FHG)
   位域定义UNION结构:  SOC_ISP_CMDLST_CMDLST_HW_CVDR_RD_DATA_2_UNION */
#define SOC_ISP_CMDLST_CMDLST_HW_CVDR_RD_DATA_2_ADDR(base, CHANNEL_NBR_range)  ((base) + (0xCC+0x80*(CHANNEL_NBR_range)))

/* 寄存器说明：4th Data to write (VP_RD_AXI_FS)
   位域定义UNION结构:  SOC_ISP_CMDLST_CMDLST_HW_CVDR_RD_DATA_3_UNION */
#define SOC_ISP_CMDLST_CMDLST_HW_CVDR_RD_DATA_3_ADDR(base, CHANNEL_NBR_range)  ((base) + (0xD0+0x80*(CHANNEL_NBR_range)))

/* 寄存器说明：Debug register
   位域定义UNION结构:  SOC_ISP_CMDLST_CMDLST_CHANNEL_DEBUG_UNION */
#define SOC_ISP_CMDLST_CMDLST_CHANNEL_DEBUG_ADDR(base, CHANNEL_NBR_range)  ((base) + (0xE0+0x80*(CHANNEL_NBR_range)))





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
                     (1/1) CMDLST
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_ISP_CMDLST_CMDLST_ID_UNION
 结构说明  : CMDLST_ID 寄存器结构定义。地址偏移量:0x0，初值:0x434C5354，宽度:32
 寄存器说明: Module Identifier
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_id : 32; /* bit[0-31]: CLST in ASCII */
    } reg;
} SOC_ISP_CMDLST_CMDLST_ID_UNION;
#endif
#define SOC_ISP_CMDLST_CMDLST_ID_ip_id_START  (0)
#define SOC_ISP_CMDLST_CMDLST_ID_ip_id_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CMDLST_CMDLST_VERSION_UNION
 结构说明  : CMDLST_VERSION 寄存器结构定义。地址偏移量:0x4，初值:0x00000100，宽度:32
 寄存器说明: Module Version
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_version : 32; /* bit[0-31]: Version 1.0 */
    } reg;
} SOC_ISP_CMDLST_CMDLST_VERSION_UNION;
#endif
#define SOC_ISP_CMDLST_CMDLST_VERSION_ip_version_START  (0)
#define SOC_ISP_CMDLST_CMDLST_VERSION_ip_version_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CMDLST_CMDLST_CFG_UNION
 结构说明  : CMDLST_CFG 寄存器结构定义。地址偏移量:0x20，初值:0x00000000，宽度:32
 寄存器说明: Module configuration
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  prefetch : 1;  /* bit[0]   : Enables to define the functional mode:
                                                   - 0: several channels are active - prefetch can not be done in advance. CVDR configuration is sent only once the EOP is received, to allow serial usage of the video port.
                                                   - 1: only one channel active - channel 0: command list content is prefetched and stored into the CVDR. In this mode, the video port is exclusive and the CVDR can provide some DUs. */
        unsigned int  reserved : 31; /* bit[1-31]: - */
    } reg;
} SOC_ISP_CMDLST_CMDLST_CFG_UNION;
#endif
#define SOC_ISP_CMDLST_CMDLST_CFG_prefetch_START  (0)
#define SOC_ISP_CMDLST_CMDLST_CFG_prefetch_END    (0)


/*****************************************************************************
 结构名    : SOC_ISP_CMDLST_CMDLST_DEBUG_0_UNION
 结构说明  : CMDLST_DEBUG_0 寄存器结构定义。地址偏移量:0x40，初值:0x00000000，宽度:32
 寄存器说明: Debug register (available over the debug bus, lower part)
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_fifo_nb_elem  : 3;  /* bit[0-2]  : FIFO number of element */
        unsigned int  reserved_0        : 1;  /* bit[3]    : - */
        unsigned int  dbg_lb_master_fsm : 3;  /* bit[4-6]  : LB master FSM states:
                                                             0: IDLE => Nothing to do, single write, or NOP
                                                             1: WR_CMD => Write burst accesses is ongoing
                                                             2: RD_CMD => Read accesses is ongoing, request is send
                                                             3: RD_DATA => Read accesses is ongoing, read data is sampled
                                                             4: RD_WAIT => Waiting for acknowledge from upper part (basically VP write port) */
        unsigned int  reserved_1        : 1;  /* bit[7]    : - */
        unsigned int  dbg_vp_wr_fsm     : 2;  /* bit[8-9]  : VP write FSM states:
                                                             0: IDLE => VP write has not been used
                                                             1: ACTIVE => VP write is active, at least one access has been done (basically RD command has been executed)
                                                             3: FLUSH => EOF is sending to VP write */
        unsigned int  reserved_2        : 2;  /* bit[10-11]: - */
        unsigned int  dbg_arb_fsm       : 1;  /* bit[12]   : Channels arbiter FSM states:
                                                             0: ARBITRATION => Arbiter is ready for arbitration
                                                             1: WAIT_REQ_DONE => Arbitration has been done and waiting for LB MASTER release (basically end of CMDLST execution) */
        unsigned int  reserved_3        : 3;  /* bit[13-15]: - */
        unsigned int  dbg_sw_start      : 8;  /* bit[16-23]: SW request (1 bit per channel): for channels from 0 to 7 */
        unsigned int  dbg_hw_start      : 8;  /* bit[24-31]: HW request is pending (1 bit per channel): for channels from 0 to 7 */
    } reg;
} SOC_ISP_CMDLST_CMDLST_DEBUG_0_UNION;
#endif
#define SOC_ISP_CMDLST_CMDLST_DEBUG_0_dbg_fifo_nb_elem_START   (0)
#define SOC_ISP_CMDLST_CMDLST_DEBUG_0_dbg_fifo_nb_elem_END     (2)
#define SOC_ISP_CMDLST_CMDLST_DEBUG_0_dbg_lb_master_fsm_START  (4)
#define SOC_ISP_CMDLST_CMDLST_DEBUG_0_dbg_lb_master_fsm_END    (6)
#define SOC_ISP_CMDLST_CMDLST_DEBUG_0_dbg_vp_wr_fsm_START      (8)
#define SOC_ISP_CMDLST_CMDLST_DEBUG_0_dbg_vp_wr_fsm_END        (9)
#define SOC_ISP_CMDLST_CMDLST_DEBUG_0_dbg_arb_fsm_START        (12)
#define SOC_ISP_CMDLST_CMDLST_DEBUG_0_dbg_arb_fsm_END          (12)
#define SOC_ISP_CMDLST_CMDLST_DEBUG_0_dbg_sw_start_START       (16)
#define SOC_ISP_CMDLST_CMDLST_DEBUG_0_dbg_sw_start_END         (23)
#define SOC_ISP_CMDLST_CMDLST_DEBUG_0_dbg_hw_start_START       (24)
#define SOC_ISP_CMDLST_CMDLST_DEBUG_0_dbg_hw_start_END         (31)


/*****************************************************************************
 结构名    : SOC_ISP_CMDLST_CMDLST_DEBUG_1_UNION
 结构说明  : CMDLST_DEBUG_1 寄存器结构定义。地址偏移量:0x44，初值:0x00000000，宽度:32
 寄存器说明: Debug register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_sw_start : 16; /* bit[0-15] : SW request (1 bit per channel) for channels from 0 to 15 */
        unsigned int  dbg_hw_start : 16; /* bit[16-31]: HW request is pending (1 bit per channel) for channels from 0 to 15 */
    } reg;
} SOC_ISP_CMDLST_CMDLST_DEBUG_1_UNION;
#endif
#define SOC_ISP_CMDLST_CMDLST_DEBUG_1_dbg_sw_start_START  (0)
#define SOC_ISP_CMDLST_CMDLST_DEBUG_1_dbg_sw_start_END    (15)
#define SOC_ISP_CMDLST_CMDLST_DEBUG_1_dbg_hw_start_START  (16)
#define SOC_ISP_CMDLST_CMDLST_DEBUG_1_dbg_hw_start_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CMDLST_CMDLST_DEBUG_2_UNION
 结构说明  : CMDLST_DEBUG_2 寄存器结构定义。地址偏移量:0x48，初值:0x00000000，宽度:32
 寄存器说明: Debug register (available over the debug bus, upper part)
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_fsm_ch_0 : 3;  /* bit[0-2]  : Channel 0 FSM state */
        unsigned int  reserved_0   : 1;  /* bit[3]    : - */
        unsigned int  dbg_fsm_ch_1 : 3;  /* bit[4-6]  : Channel 1 FSM state */
        unsigned int  reserved_1   : 1;  /* bit[7]    : - */
        unsigned int  dbg_fsm_ch_2 : 3;  /* bit[8-10] : Channel 2 FSM state */
        unsigned int  reserved_2   : 1;  /* bit[11]   : - */
        unsigned int  dbg_fsm_ch_3 : 3;  /* bit[12-14]: Channel 3 FSM state */
        unsigned int  reserved_3   : 1;  /* bit[15]   : - */
        unsigned int  dbg_fsm_ch_4 : 3;  /* bit[16-18]: Channel 4 FSM state */
        unsigned int  reserved_4   : 1;  /* bit[19]   : - */
        unsigned int  dbg_fsm_ch_5 : 3;  /* bit[20-22]: Channel 5 FSM state */
        unsigned int  reserved_5   : 1;  /* bit[23]   : - */
        unsigned int  dbg_fsm_ch_6 : 3;  /* bit[24-26]: Channel 6 FSM state */
        unsigned int  reserved_6   : 1;  /* bit[27]   : - */
        unsigned int  dbg_fsm_ch_7 : 3;  /* bit[28-30]: Channel 7 FSM state */
        unsigned int  reserved_7   : 1;  /* bit[31]   :  */
    } reg;
} SOC_ISP_CMDLST_CMDLST_DEBUG_2_UNION;
#endif
#define SOC_ISP_CMDLST_CMDLST_DEBUG_2_dbg_fsm_ch_0_START  (0)
#define SOC_ISP_CMDLST_CMDLST_DEBUG_2_dbg_fsm_ch_0_END    (2)
#define SOC_ISP_CMDLST_CMDLST_DEBUG_2_dbg_fsm_ch_1_START  (4)
#define SOC_ISP_CMDLST_CMDLST_DEBUG_2_dbg_fsm_ch_1_END    (6)
#define SOC_ISP_CMDLST_CMDLST_DEBUG_2_dbg_fsm_ch_2_START  (8)
#define SOC_ISP_CMDLST_CMDLST_DEBUG_2_dbg_fsm_ch_2_END    (10)
#define SOC_ISP_CMDLST_CMDLST_DEBUG_2_dbg_fsm_ch_3_START  (12)
#define SOC_ISP_CMDLST_CMDLST_DEBUG_2_dbg_fsm_ch_3_END    (14)
#define SOC_ISP_CMDLST_CMDLST_DEBUG_2_dbg_fsm_ch_4_START  (16)
#define SOC_ISP_CMDLST_CMDLST_DEBUG_2_dbg_fsm_ch_4_END    (18)
#define SOC_ISP_CMDLST_CMDLST_DEBUG_2_dbg_fsm_ch_5_START  (20)
#define SOC_ISP_CMDLST_CMDLST_DEBUG_2_dbg_fsm_ch_5_END    (22)
#define SOC_ISP_CMDLST_CMDLST_DEBUG_2_dbg_fsm_ch_6_START  (24)
#define SOC_ISP_CMDLST_CMDLST_DEBUG_2_dbg_fsm_ch_6_END    (26)
#define SOC_ISP_CMDLST_CMDLST_DEBUG_2_dbg_fsm_ch_7_START  (28)
#define SOC_ISP_CMDLST_CMDLST_DEBUG_2_dbg_fsm_ch_7_END    (30)


/*****************************************************************************
 结构名    : SOC_ISP_CMDLST_CMDLST_DEBUG_3_UNION
 结构说明  : CMDLST_DEBUG_3 寄存器结构定义。地址偏移量:0x4C，初值:0x00000000，宽度:32
 寄存器说明: Debug register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_fsm_ch_8  : 3;  /* bit[0-2]  : Channel 8 FSM state */
        unsigned int  reserved_0    : 1;  /* bit[3]    : - */
        unsigned int  dbg_fsm_ch_9  : 3;  /* bit[4-6]  : Channel 9 FSM state */
        unsigned int  reserved_1    : 1;  /* bit[7]    : - */
        unsigned int  dbg_fsm_ch_10 : 3;  /* bit[8-10] : Channel 10 FSM state */
        unsigned int  reserved_2    : 1;  /* bit[11]   : - */
        unsigned int  dbg_fsm_ch_11 : 3;  /* bit[12-14]: Channel 11 FSM state */
        unsigned int  reserved_3    : 1;  /* bit[15]   : - */
        unsigned int  dbg_fsm_ch_12 : 3;  /* bit[16-18]: Channel 12 FSM state */
        unsigned int  reserved_4    : 1;  /* bit[19]   : - */
        unsigned int  dbg_fsm_ch_13 : 3;  /* bit[20-22]: Channel 13 FSM state */
        unsigned int  reserved_5    : 1;  /* bit[23]   : - */
        unsigned int  dbg_fsm_ch_14 : 3;  /* bit[24-26]: Channel 14 FSM state */
        unsigned int  reserved_6    : 1;  /* bit[27]   : - */
        unsigned int  dbg_fsm_ch_15 : 3;  /* bit[28-30]: Channel 15 FSM state */
        unsigned int  reserved_7    : 1;  /* bit[31]   : - */
    } reg;
} SOC_ISP_CMDLST_CMDLST_DEBUG_3_UNION;
#endif
#define SOC_ISP_CMDLST_CMDLST_DEBUG_3_dbg_fsm_ch_8_START   (0)
#define SOC_ISP_CMDLST_CMDLST_DEBUG_3_dbg_fsm_ch_8_END     (2)
#define SOC_ISP_CMDLST_CMDLST_DEBUG_3_dbg_fsm_ch_9_START   (4)
#define SOC_ISP_CMDLST_CMDLST_DEBUG_3_dbg_fsm_ch_9_END     (6)
#define SOC_ISP_CMDLST_CMDLST_DEBUG_3_dbg_fsm_ch_10_START  (8)
#define SOC_ISP_CMDLST_CMDLST_DEBUG_3_dbg_fsm_ch_10_END    (10)
#define SOC_ISP_CMDLST_CMDLST_DEBUG_3_dbg_fsm_ch_11_START  (12)
#define SOC_ISP_CMDLST_CMDLST_DEBUG_3_dbg_fsm_ch_11_END    (14)
#define SOC_ISP_CMDLST_CMDLST_DEBUG_3_dbg_fsm_ch_12_START  (16)
#define SOC_ISP_CMDLST_CMDLST_DEBUG_3_dbg_fsm_ch_12_END    (18)
#define SOC_ISP_CMDLST_CMDLST_DEBUG_3_dbg_fsm_ch_13_START  (20)
#define SOC_ISP_CMDLST_CMDLST_DEBUG_3_dbg_fsm_ch_13_END    (22)
#define SOC_ISP_CMDLST_CMDLST_DEBUG_3_dbg_fsm_ch_14_START  (24)
#define SOC_ISP_CMDLST_CMDLST_DEBUG_3_dbg_fsm_ch_14_END    (26)
#define SOC_ISP_CMDLST_CMDLST_DEBUG_3_dbg_fsm_ch_15_START  (28)
#define SOC_ISP_CMDLST_CMDLST_DEBUG_3_dbg_fsm_ch_15_END    (30)


/*****************************************************************************
 结构名    : SOC_ISP_CMDLST_CMDLST_DEBUG_4_UNION
 结构说明  : CMDLST_DEBUG_4 寄存器结构定义。地址偏移量:0x50，初值:0x00000000，宽度:32
 寄存器说明: Debug register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  last_lb_addr : 21; /* bit[0-20] : Last LB MASTER address access */
        unsigned int  reserved     : 11; /* bit[21-31]: - */
    } reg;
} SOC_ISP_CMDLST_CMDLST_DEBUG_4_UNION;
#endif
#define SOC_ISP_CMDLST_CMDLST_DEBUG_4_last_lb_addr_START  (0)
#define SOC_ISP_CMDLST_CMDLST_DEBUG_4_last_lb_addr_END    (20)


/*****************************************************************************
 结构名    : SOC_ISP_CMDLST_CMDLST_SW_CVDR_RD_ADDR_UNION
 结构说明  : CMDLST_SW_CVDR_RD_ADDR 寄存器结构定义。地址偏移量:0x80+0x80*(CHANNEL_NBR_range)，初值:0x03000000，宽度:32
 寄存器说明: CVDR Video port read address to write the configuration data (CMDLST_SW_CVDR_RD_DATA*)
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0         : 2;  /* bit[0-1]  : not used */
        unsigned int  sw_cvdr_rd_address : 19; /* bit[2-20] : Start Address to use to configure the video port read.
                                                              The size of the command is configured into cfg_burst_size and the data to write are defined into CMDLST_CFG_DATA_0/1/2/3 */
        unsigned int  reserved_1         : 3;  /* bit[21-23]: not used */
        unsigned int  sw_cvdr_rd_size    : 2;  /* bit[24-25]: Number of data to write:
                                                              0: CMDLST_CFG_DATA_0
                                                              1: CMDLST_CFG_DATA_0 then CMDLST_CFG_DATA1
                                                              2: CMDLST_CFG_DATA_0 then CMDLST_CFG_DATA1 then CMDLST_CFG_DATA_2
                                                              3: CMDLST_CFG_DATA_0 then CMDLST_CFG_DATA1 then CMDLST_CFG_DATA_2 then CMDLST_CFG_DATA_3 
                                                              [note] value 0x3 is expected [end] */
        unsigned int  reserved_2         : 6;  /* bit[26-31]: not used */
    } reg;
} SOC_ISP_CMDLST_CMDLST_SW_CVDR_RD_ADDR_UNION;
#endif
#define SOC_ISP_CMDLST_CMDLST_SW_CVDR_RD_ADDR_sw_cvdr_rd_address_START  (2)
#define SOC_ISP_CMDLST_CMDLST_SW_CVDR_RD_ADDR_sw_cvdr_rd_address_END    (20)
#define SOC_ISP_CMDLST_CMDLST_SW_CVDR_RD_ADDR_sw_cvdr_rd_size_START     (24)
#define SOC_ISP_CMDLST_CMDLST_SW_CVDR_RD_ADDR_sw_cvdr_rd_size_END       (25)


/*****************************************************************************
 结构名    : SOC_ISP_CMDLST_CMDLST_SW_CVDR_RD_DATA_0_UNION
 结构说明  : CMDLST_SW_CVDR_RD_DATA_0 寄存器结构定义。地址偏移量:0x84+0x80*(CHANNEL_NBR_range)，初值:0x00003C00，宽度:32
 寄存器说明: 1st Data to write (VP_RD_CFG)
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_pixel_format    : 4;  /* bit[0-3]  : "Pixel formats supported (see ref. [1])ReturnToLine 0:3->1PF8:1PF14 ReturnToLine 4:7->2PF8:2PF14 ReturnToLine 9:11->3PF8:3PF14 ReturnToLine 12:D32 ReturnToLine 13:D48 ReturnToLine 14: D64" */
        unsigned int  vprd_pixel_expansion : 1;  /* bit[4-4]  : Pixel expansion can be used (see ref. [1]) */
        unsigned int  vprd_allocated_du    : 5;  /* bit[5-9]  : "Number of allocated DUsReturnToLineA maximum of 16 DUs can be allocated per video port" */
        unsigned int  vprd_access_limiter  : 4;  /* bit[10-13]: "CVDR RAM access limiter: maximum number of read 128 bit accesses allowed on a 32 clock cycle windowReturnToLine0: 0 access allowed (unexpected in regular SW)ReturnToLine1: 1 access maximum allowedReturnToLineand so onReturnToLine15: 15 accesses maximum allowed"
                                                                [note] value different from 0 is expected, value 0xF is recommended [end] */
        unsigned int  reserved             : 1;  /* bit[14-14]: not used */
        unsigned int  vprd_last_page       : 17; /* bit[15-31]: "last 32KB page reserved to read the data. This page is not necessarily prefetched but is the last page reserved by the Software.ReturnToLineThe CVDR must prefetch the page used by the frame start (back to initial - in case of continuous mode) once the last page is equal to vprd_last_page. ReturnToLineThis info must be aligned with the frame size (SW info) and the vprd_line_wrap info (SW and HW) to be aligned with buffer size reserved by the SW." */
    } reg;
} SOC_ISP_CMDLST_CMDLST_SW_CVDR_RD_DATA_0_UNION;
#endif
#define SOC_ISP_CMDLST_CMDLST_SW_CVDR_RD_DATA_0_vprd_pixel_format_START     (0)
#define SOC_ISP_CMDLST_CMDLST_SW_CVDR_RD_DATA_0_vprd_pixel_format_END       (3)
#define SOC_ISP_CMDLST_CMDLST_SW_CVDR_RD_DATA_0_vprd_pixel_expansion_START  (4)
#define SOC_ISP_CMDLST_CMDLST_SW_CVDR_RD_DATA_0_vprd_pixel_expansion_END    (4)
#define SOC_ISP_CMDLST_CMDLST_SW_CVDR_RD_DATA_0_vprd_allocated_du_START     (5)
#define SOC_ISP_CMDLST_CMDLST_SW_CVDR_RD_DATA_0_vprd_allocated_du_END       (9)
#define SOC_ISP_CMDLST_CMDLST_SW_CVDR_RD_DATA_0_vprd_access_limiter_START   (10)
#define SOC_ISP_CMDLST_CMDLST_SW_CVDR_RD_DATA_0_vprd_access_limiter_END     (13)
#define SOC_ISP_CMDLST_CMDLST_SW_CVDR_RD_DATA_0_vprd_last_page_START        (15)
#define SOC_ISP_CMDLST_CMDLST_SW_CVDR_RD_DATA_0_vprd_last_page_END          (31)


/*****************************************************************************
 结构名    : SOC_ISP_CMDLST_CMDLST_SW_CVDR_RD_DATA_1_UNION
 结构说明  : CMDLST_SW_CVDR_RD_DATA_1 寄存器结构定义。地址偏移量:0x88+0x80*(CHANNEL_NBR_range)，初值:0x00000000，宽度:32
 寄存器说明: 2nd data to write (VP_RD_LWG)
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_line_size           : 13; /* bit[0-12] : number of pixels per line (up to 8192 pixels) */
        unsigned int  reserved_0               : 3;  /* bit[13-15]: not used */
        unsigned int  vprd_horizontal_blanking : 8;  /* bit[16-23]: "Horizontal blanking (number of clock cycles between 2 lines)ReturnToLineup to 256 clock cycles" */
        unsigned int  reserved_1               : 8;  /* bit[24-31]: not used */
    } reg;
} SOC_ISP_CMDLST_CMDLST_SW_CVDR_RD_DATA_1_UNION;
#endif
#define SOC_ISP_CMDLST_CMDLST_SW_CVDR_RD_DATA_1_vprd_line_size_START            (0)
#define SOC_ISP_CMDLST_CMDLST_SW_CVDR_RD_DATA_1_vprd_line_size_END              (12)
#define SOC_ISP_CMDLST_CMDLST_SW_CVDR_RD_DATA_1_vprd_horizontal_blanking_START  (16)
#define SOC_ISP_CMDLST_CMDLST_SW_CVDR_RD_DATA_1_vprd_horizontal_blanking_END    (23)


/*****************************************************************************
 结构名    : SOC_ISP_CMDLST_CMDLST_SW_CVDR_RD_DATA_2_UNION
 结构说明  : CMDLST_SW_CVDR_RD_DATA_2 寄存器结构定义。地址偏移量:0x8C+0x80*(CHANNEL_NBR_range)，初值:0x00000000，宽度:32
 寄存器说明: 3rd Data to write (VP_RD_FHG)
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vprd_frame_size        : 13; /* bit[0-12] : number of lines per frame (up to 8192 lines) */
        unsigned int  reserved_0             : 3;  /* bit[13-15]: not used */
        unsigned int  vprd_vertical_blanking : 8;  /* bit[16-23]: "Vertical blanking (number of dummy lines between 2 frames)ReturnToLineup to 256 lines" */
        unsigned int  reserved_1             : 8;  /* bit[24-31]: not used */
    } reg;
} SOC_ISP_CMDLST_CMDLST_SW_CVDR_RD_DATA_2_UNION;
#endif
#define SOC_ISP_CMDLST_CMDLST_SW_CVDR_RD_DATA_2_vprd_frame_size_START         (0)
#define SOC_ISP_CMDLST_CMDLST_SW_CVDR_RD_DATA_2_vprd_frame_size_END           (12)
#define SOC_ISP_CMDLST_CMDLST_SW_CVDR_RD_DATA_2_vprd_vertical_blanking_START  (16)
#define SOC_ISP_CMDLST_CMDLST_SW_CVDR_RD_DATA_2_vprd_vertical_blanking_END    (23)


/*****************************************************************************
 结构名    : SOC_ISP_CMDLST_CMDLST_SW_CVDR_RD_DATA_3_UNION
 结构说明  : CMDLST_SW_CVDR_RD_DATA_3 寄存器结构定义。地址偏移量:0x90+0x80*(CHANNEL_NBR_range)，初值:0x00000000，宽度:32
 寄存器说明: 4th Data to write (VP_RD_AXI_FS)
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved               : 4;  /* bit[0-3] : not used */
        unsigned int  vprd_axi_frame_start_0 : 28; /* bit[4-31]: "Start address of the frame (in 16 bytes boundary).ReturnToLineSince we are 128-bits */
    } reg;
} SOC_ISP_CMDLST_CMDLST_SW_CVDR_RD_DATA_3_UNION;
#endif
#define SOC_ISP_CMDLST_CMDLST_SW_CVDR_RD_DATA_3_vprd_axi_frame_start_0_START  (4)
#define SOC_ISP_CMDLST_CMDLST_SW_CVDR_RD_DATA_3_vprd_axi_frame_start_0_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CMDLST_CMDLST_SW_BRANCH_UNION
 结构说明  : CMDLST_SW_BRANCH 寄存器结构定义。地址偏移量:0xA0+0x80*(CHANNEL_NBR_range)，初值:0x00000000，宽度:32
 寄存器说明: Branching request
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  branching : 1;  /* bit[0]   : Branching request. 
                                                    The bit is set by SW when the software wants to branch the linked list, the consequence will be that no new command list can start but the current one can finish (if any on going)
                                                    The hardware will automatically clear it once CMDLST_SW_CVDR_RD_DATA_3 is written. */
        unsigned int  reserved  : 31; /* bit[1-31]:  */
    } reg;
} SOC_ISP_CMDLST_CMDLST_SW_BRANCH_UNION;
#endif
#define SOC_ISP_CMDLST_CMDLST_SW_BRANCH_branching_START  (0)
#define SOC_ISP_CMDLST_CMDLST_SW_BRANCH_branching_END    (0)


/*****************************************************************************
 结构名    : SOC_ISP_CMDLST_CMDLST_LAST_EXEC_RD_DATA_3_UNION
 结构说明  : CMDLST_LAST_EXEC_RD_DATA_3 寄存器结构定义。地址偏移量:0xA4+0x80*(CHANNEL_NBR_range)，初值:0x00000000，宽度:32
 寄存器说明: last CVDR_RD_DATA_3 information used to configure the CVDR
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  shadowed_rd_data_3 : 32; /* bit[0-31]: stores the oldest */
    } reg;
} SOC_ISP_CMDLST_CMDLST_LAST_EXEC_RD_DATA_3_UNION;
#endif
#define SOC_ISP_CMDLST_CMDLST_LAST_EXEC_RD_DATA_3_shadowed_rd_data_3_START  (0)
#define SOC_ISP_CMDLST_CMDLST_LAST_EXEC_RD_DATA_3_shadowed_rd_data_3_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CMDLST_CMDLST_HW_CVDR_RD_ADDR_UNION
 结构说明  : CMDLST_HW_CVDR_RD_ADDR 寄存器结构定义。地址偏移量:0xC0+0x80*(CHANNEL_NBR_range)，初值:0x03000000，宽度:32
 寄存器说明: CVDR Video port read address to write the configuration data (CMDLST_HW_CVDR_RD_DATA*)
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0         : 2;  /* bit[0-1]  : not used */
        unsigned int  hw_cvdr_rd_address : 19; /* bit[2-20] : refers to sw_cvdr_rd_address */
        unsigned int  reserved_1         : 3;  /* bit[21-23]: not used */
        unsigned int  hw_cvdr_rd_size    : 2;  /* bit[24-25]: refers to sw_cvdr_rd_size
                                                              [note] value 0x3 is expected [end] */
        unsigned int  reserved_2         : 6;  /* bit[26-31]: not used */
    } reg;
} SOC_ISP_CMDLST_CMDLST_HW_CVDR_RD_ADDR_UNION;
#endif
#define SOC_ISP_CMDLST_CMDLST_HW_CVDR_RD_ADDR_hw_cvdr_rd_address_START  (2)
#define SOC_ISP_CMDLST_CMDLST_HW_CVDR_RD_ADDR_hw_cvdr_rd_address_END    (20)
#define SOC_ISP_CMDLST_CMDLST_HW_CVDR_RD_ADDR_hw_cvdr_rd_size_START     (24)
#define SOC_ISP_CMDLST_CMDLST_HW_CVDR_RD_ADDR_hw_cvdr_rd_size_END       (25)


/*****************************************************************************
 结构名    : SOC_ISP_CMDLST_CMDLST_HW_CVDR_RD_DATA_0_UNION
 结构说明  : CMDLST_HW_CVDR_RD_DATA_0 寄存器结构定义。地址偏移量:0xC4+0x80*(CHANNEL_NBR_range)，初值:0x00000000，宽度:32
 寄存器说明: 1st Data to write (VP_RD_CFG)
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hw_cvdr_rd_data_0 : 32; /* bit[0-31]: Data used to configure at address hw_cvdr_rd_address (refers to CMDLST_SW_CVDR_RD_DATA_0) */
    } reg;
} SOC_ISP_CMDLST_CMDLST_HW_CVDR_RD_DATA_0_UNION;
#endif
#define SOC_ISP_CMDLST_CMDLST_HW_CVDR_RD_DATA_0_hw_cvdr_rd_data_0_START  (0)
#define SOC_ISP_CMDLST_CMDLST_HW_CVDR_RD_DATA_0_hw_cvdr_rd_data_0_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CMDLST_CMDLST_HW_CVDR_RD_DATA_1_UNION
 结构说明  : CMDLST_HW_CVDR_RD_DATA_1 寄存器结构定义。地址偏移量:0xC8+0x80*(CHANNEL_NBR_range)，初值:0x00000000，宽度:32
 寄存器说明: 2nd data to write (VP_RD_LWG)
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hw_cvdr_rd_data_1 : 32; /* bit[0-31]: Data used to configure at address hw_cvdr_rd_address + 4 (refers to CMDLST_SW_CVDR_RD_DATA_1) */
    } reg;
} SOC_ISP_CMDLST_CMDLST_HW_CVDR_RD_DATA_1_UNION;
#endif
#define SOC_ISP_CMDLST_CMDLST_HW_CVDR_RD_DATA_1_hw_cvdr_rd_data_1_START  (0)
#define SOC_ISP_CMDLST_CMDLST_HW_CVDR_RD_DATA_1_hw_cvdr_rd_data_1_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CMDLST_CMDLST_HW_CVDR_RD_DATA_2_UNION
 结构说明  : CMDLST_HW_CVDR_RD_DATA_2 寄存器结构定义。地址偏移量:0xCC+0x80*(CHANNEL_NBR_range)，初值:0x00000000，宽度:32
 寄存器说明: 3rd Data to write (VP_RD_FHG)
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hw_cvdr_rd_data_2 : 32; /* bit[0-31]: Data used to configure at address hw_cvdr_rd_address + 8 (refers to CMDLST_SW_CVDR_RD_DATA_2) */
    } reg;
} SOC_ISP_CMDLST_CMDLST_HW_CVDR_RD_DATA_2_UNION;
#endif
#define SOC_ISP_CMDLST_CMDLST_HW_CVDR_RD_DATA_2_hw_cvdr_rd_data_2_START  (0)
#define SOC_ISP_CMDLST_CMDLST_HW_CVDR_RD_DATA_2_hw_cvdr_rd_data_2_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CMDLST_CMDLST_HW_CVDR_RD_DATA_3_UNION
 结构说明  : CMDLST_HW_CVDR_RD_DATA_3 寄存器结构定义。地址偏移量:0xD0+0x80*(CHANNEL_NBR_range)，初值:0x00000000，宽度:32
 寄存器说明: 4th Data to write (VP_RD_AXI_FS)
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hw_cvdr_rd_data_3 : 32; /* bit[0-31]: Data used to configure at address hw_cvdr_rd_address + 12 (refers to CMDLST_SW_CVDR_RD_DATA_3) */
    } reg;
} SOC_ISP_CMDLST_CMDLST_HW_CVDR_RD_DATA_3_UNION;
#endif
#define SOC_ISP_CMDLST_CMDLST_HW_CVDR_RD_DATA_3_hw_cvdr_rd_data_3_START  (0)
#define SOC_ISP_CMDLST_CMDLST_HW_CVDR_RD_DATA_3_hw_cvdr_rd_data_3_END    (31)


/*****************************************************************************
 结构名    : SOC_ISP_CMDLST_CMDLST_CHANNEL_DEBUG_UNION
 结构说明  : CMDLST_CHANNEL_DEBUG 寄存器结构定义。地址偏移量:0xE0+0x80*(CHANNEL_NBR_range)，初值:0x00000000，宽度:32
 寄存器说明: Debug register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_fsm_ch   : 3;  /* bit[0-2] : Channel FSM states:
                                                       0: IDLE => Job has been done, there is no more pending request
                                                       1:BUS_REQ => Channel is requesting LB MASTER access
                                                       2: CFG_CVDR => CVDR configuration is ongoing
                                                       3: EXEC_CMD => CMDLST is executing
                                                       4: WAIT_FLUSH => CMDLST is done and VP write has to be flushed (send EOF)
                                                       5: WAIT_EOP => CMDLST execution is done and EOP event is waiting for
                                                       6: CFG_CVDR2 => Only when prefetch mode is enable, next CVDR configuration is ongoing as previous CMDLST is executing
                                                       7: WAIT_EOF2 => Only when prefetch mode is enable, CMDLST execution is done and EOP event is waiting for */
        unsigned int  reserved_0   : 1;  /* bit[3]   : reserved */
        unsigned int  dbg_sw_start : 1;  /* bit[4]   : SW request is pending */
        unsigned int  reserved_1   : 3;  /* bit[5-7] : reserved */
        unsigned int  dbg_hw_start : 1;  /* bit[8]   : HW request is pending */
        unsigned int  reserved_2   : 23; /* bit[9-31]: reserved */
    } reg;
} SOC_ISP_CMDLST_CMDLST_CHANNEL_DEBUG_UNION;
#endif
#define SOC_ISP_CMDLST_CMDLST_CHANNEL_DEBUG_dbg_fsm_ch_START    (0)
#define SOC_ISP_CMDLST_CMDLST_CHANNEL_DEBUG_dbg_fsm_ch_END      (2)
#define SOC_ISP_CMDLST_CMDLST_CHANNEL_DEBUG_dbg_sw_start_START  (4)
#define SOC_ISP_CMDLST_CMDLST_CHANNEL_DEBUG_dbg_sw_start_END    (4)
#define SOC_ISP_CMDLST_CMDLST_CHANNEL_DEBUG_dbg_hw_start_START  (8)
#define SOC_ISP_CMDLST_CMDLST_CHANNEL_DEBUG_dbg_hw_start_END    (8)






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

#endif /* end of soc_isp_cmdlst_interface.h */
