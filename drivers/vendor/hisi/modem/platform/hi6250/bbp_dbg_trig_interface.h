

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#ifndef __BBP_DBG_TRIG_INTERFACE_H__
#define __BBP_DBG_TRIG_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/***======================================================================***
                     (1/2) register_define_dbg_trig
 ***======================================================================***/
/* 寄存器说明：
 bit[31:20]  保留
 bit[19:8]   W1高地址段地址
 bit[7:5]    保留
 bit[4]      W1上下点使能（OAM根据W1模上下电情况配置）
 bit[3:1]    保留
 bit[0]      W1地址段有效使能（根据测试目的工具勾选使能）
   UNION结构:  DBG_TRIG_W1_CONFIG1_UNION */
#define DBG_TRIG_W1_CONFIG1_ADDR                      (SOC_BBP_DBG_TRIG_BASE_ADDR + 0xFC8000)

/* 寄存器说明：
 bit[31:21]  保留
 bit[20:12]  W1 TRACE ADDR RAM长度
 bit[11:9]   保留
 bit[8:0]    W1 TRACE ADDR RAM起始地址
   UNION结构:  DBG_TRIG_W1_CONFIG2_UNION */
#define DBG_TRIG_W1_CONFIG2_ADDR                      (SOC_BBP_DBG_TRIG_BASE_ADDR + 0xFC8004)

/* 寄存器说明：
 bit[31:16]  保留
 bit[15:0]   W1 TRACE定时起始位置，单位chip。
             bit[7:0]：symbol内chip计数，计数范围0~255chip；
             bit[11:8]：slot内symbol计数，计数范围0~9symbol；
             bit[15:12]：帧内slot计数，计数范围0~14slot
   UNION结构:  DBG_TRIG_W1_START_POS_UNION */
#define DBG_TRIG_W1_START_POS_ADDR                    (SOC_BBP_DBG_TRIG_BASE_ADDR + 0xFC8008)

/* 寄存器说明：
 bit[31:20]  保留
 bit[19:8]   W2高地址段地址
 bit[7:5]    保留
 bit[4]      W2上下点使能（OAM根据W1模上下电情况配置）
 bit[3:1]    保留
 bit[0]      W2地址段有效使能（根据测试目的工具勾选使能）
   UNION结构:  DBG_TRIG_W2_CONFIG1_UNION */
#define DBG_TRIG_W2_CONFIG1_ADDR                      (SOC_BBP_DBG_TRIG_BASE_ADDR + 0xFC800C)

/* 寄存器说明：
 bit[31:21]  保留
 bit[20:12]  W2 TRACE ADDR RAM长度
 bit[11:9]   保留
 bit[8:0]    W2 TRACE ADDR RAM起始地址
   UNION结构:  DBG_TRIG_W2_CONFIG2_UNION */
#define DBG_TRIG_W2_CONFIG2_ADDR                      (SOC_BBP_DBG_TRIG_BASE_ADDR + 0xFC8010)

/* 寄存器说明：
 bit[31:16]  保留
 bit[15:0]   W2 TRACE定时起始位置，单位chip。
             bit[7:0]：symbol内chip计数，计数范围0~255chip；
             bit[11:8]：slot内symbol计数，计数范围0~9symbol；
             bit[15:12]：帧内slot计数，计数范围0~14slot
   UNION结构:  DBG_TRIG_W2_START_POS_UNION */
#define DBG_TRIG_W2_START_POS_ADDR                    (SOC_BBP_DBG_TRIG_BASE_ADDR + 0xFC8014)

/* 寄存器说明：
 bit[31:20]  保留
 bit[19:8]   C1高地址段地址
 bit[7:5]    保留
 bit[4]      C1上下点使能（OAM根据W1模上下电情况配置）
 bit[3:1]    保留
 bit[0]      C1地址段有效使能（根据测试目的工具勾选使能）
   UNION结构:  DBG_TRIG_C1_CONFIG1_UNION */
#define DBG_TRIG_C1_CONFIG1_ADDR                      (SOC_BBP_DBG_TRIG_BASE_ADDR + 0xFC8018)

/* 寄存器说明：
 bit[31:21]  保留
 bit[20:12]  C1 TRACE ADDR RAM长度
 bit[11:9]   保留
 bit[8:0]    C1 TRACE ADDR RAM起始地址
   UNION结构:  DBG_TRIG_C1_CONFIG2_UNION */
#define DBG_TRIG_C1_CONFIG2_ADDR                      (SOC_BBP_DBG_TRIG_BASE_ADDR + 0xFC801C)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   C1 TRACE定时起始位置，单位chip。
             EVDO：
             bit[14:0]：帧内chip计数，计数范围0~32767chip，时间长度80/3ms；
             1X：
             bit[10:0]：PCG内chip计数，计数范围0~1535chip，时间长度80/64；
             bit[14:11]：PCG计数，计数范围0~15，时间长度20ms。
   UNION结构:  DBG_TRIG_C1_START_POS_UNION */
#define DBG_TRIG_C1_START_POS_ADDR                    (SOC_BBP_DBG_TRIG_BASE_ADDR + 0xFC8020)

/* 寄存器说明：
 bit[31:20]  保留
 bit[19:8]   C2高地址段地址
 bit[7:5]    保留
 bit[4]      C2上下点使能（OAM根据W1模上下电情况配置）
 bit[3:1]    保留
 bit[0]      C2地址段有效使能（根据测试目的工具勾选使能）
   UNION结构:  DBG_TRIG_C2_CONFIG1_UNION */
#define DBG_TRIG_C2_CONFIG1_ADDR                      (SOC_BBP_DBG_TRIG_BASE_ADDR + 0xFC8024)

/* 寄存器说明：
 bit[31:21]  保留
 bit[20:12]  C2 TRACE ADDR RAM长度
 bit[11:9]   保留
 bit[8:0]    C2 TRACE ADDR RAM起始地址
   UNION结构:  DBG_TRIG_C2_CONFIG2_UNION */
#define DBG_TRIG_C2_CONFIG2_ADDR                      (SOC_BBP_DBG_TRIG_BASE_ADDR + 0xFC8028)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:0]   C2 TRACE定时起始位置，单位chip。
             EVDO：
             bit[14:0]：帧内chip计数，计数范围0~32767chip，时间长度80/3ms；
             1X：
             bit[10:0]：PCG内chip计数，计数范围0~1535chip，时间长度80/64；
             bit[14:11]：PCG计数，计数范围0~15，时间长度20ms。
   UNION结构:  DBG_TRIG_C2_START_POS_UNION */
#define DBG_TRIG_C2_START_POS_ADDR                    (SOC_BBP_DBG_TRIG_BASE_ADDR + 0xFC802C)

/* 寄存器说明：
 bit[31:20]  保留
 bit[19:8]   G1高地址段地址
 bit[7:5]    保留
 bit[4]      G1上下点使能（OAM根据W1模上下电情况配置）
 bit[3:1]    保留
 bit[0]      G1地址段有效使能（根据测试目的工具勾选使能）
   UNION结构:  DBG_TRIG_G1_CONFIG1_UNION */
#define DBG_TRIG_G1_CONFIG1_ADDR                      (SOC_BBP_DBG_TRIG_BASE_ADDR + 0xFC8030)

/* 寄存器说明：
 bit[31:21]  保留
 bit[20:12]  G1 TRACE ADDR RAM长度
 bit[11:9]   保留
 bit[8:0]    G1 TRACE ADDR RAM起始地址
   UNION结构:  DBG_TRIG_G1_CONFIG2_UNION */
#define DBG_TRIG_G1_CONFIG2_ADDR                      (SOC_BBP_DBG_TRIG_BASE_ADDR + 0xFC8034)

/* 寄存器说明：
 bit[31:13]  保留
 bit[12:0]   G1 TRACE定时起始位置，单位Qb。
             bit[12:0]：gtc_tdma_qb上的帧内Qb计数，计数范围0~4999Qb；
             
   UNION结构:  DBG_TRIG_G1_START_POS_UNION */
#define DBG_TRIG_G1_START_POS_ADDR                    (SOC_BBP_DBG_TRIG_BASE_ADDR + 0xFC8038)

/* 寄存器说明：
 bit[31:20]  保留
 bit[19:8]   G2高地址段地址
 bit[7:5]    保留
 bit[4]      G2上下点使能（OAM根据W1模上下电情况配置）
 bit[3:1]    保留
 bit[0]      G2地址段有效使能（根据测试目的工具勾选使能）
   UNION结构:  DBG_TRIG_G2_CONFIG1_UNION */
#define DBG_TRIG_G2_CONFIG1_ADDR                      (SOC_BBP_DBG_TRIG_BASE_ADDR + 0xFC803C)

/* 寄存器说明：
 bit[31:21]  保留
 bit[20:12]  G2 TRACE ADDR RAM长度
 bit[11:9]   保留
 bit[8:0]    G2 TRACE ADDR RAM起始地址
   UNION结构:  DBG_TRIG_G2_CONFIG2_UNION */
#define DBG_TRIG_G2_CONFIG2_ADDR                      (SOC_BBP_DBG_TRIG_BASE_ADDR + 0xFC8040)

/* 寄存器说明：
 bit[31:13]  保留
 bit[12:0]   G2 TRACE定时起始位置，单位Qb。
             bit[12:0]：gtc_tdma_qb上的帧内Qb计数，计数范围0~4999Qb；
             
   UNION结构:  DBG_TRIG_G2_START_POS_UNION */
#define DBG_TRIG_G2_START_POS_ADDR                    (SOC_BBP_DBG_TRIG_BASE_ADDR + 0xFC8044)

/* 寄存器说明：
 bit[31:16]  1w2r双端口ram延时控制。
 bit[15:0]   单端口ram延时控制。
   UNION结构:  DBG_TRIG_MEM_CTRL0_DBG_UNION */
#define DBG_TRIG_MEM_CTRL0_DBG_ADDR                   (SOC_BBP_DBG_TRIG_BASE_ADDR + 0xFC8048)

/* 寄存器说明：
 bit[31:24]  保留
 bit[23:16]  rom延时控制。
 bit[15:0]   1rw2rw双端口ram延时控制。
   UNION结构:  DBG_TRIG_MEM_CTRL1_DBG_UNION */
#define DBG_TRIG_MEM_CTRL1_DBG_ADDR                   (SOC_BBP_DBG_TRIG_BASE_ADDR + 0xFC804C)

/* 寄存器说明：
 bit[31:1]   保留
 bit[0]      超时保护清零脉冲，6模共用。
   UNION结构:  DBG_TRIG_OVERTIME_CLR_UNION */
#define DBG_TRIG_OVERTIME_CLR_ADDR                    (SOC_BBP_DBG_TRIG_BASE_ADDR + 0xFC8050)

/* 寄存器说明：
 bit[31:22]  保留
 bit[21:20]  G2 轮询控制状态机上报
 bit[19:18]  保留
 bit[17:16]  G1 轮询控制状态机上报
 bit[15:14]  保留
 bit[13:12]  C2 轮询控制状态机上报
 bit[11:10]  保留
 bit[9:8]    C1 轮询控制状态机上报
 bit[7:6]    保留
 bit[5:4]    W2 轮询控制状态机上报
 bit[3:2]    保留
 bit[1:0]    W1 轮询控制状态机上报
   UNION结构:  DBG_TRIG_CTRL_CURR_STATE_RPT_UNION */
#define DBG_TRIG_CTRL_CURR_STATE_RPT_ADDR             (SOC_BBP_DBG_TRIG_BASE_ADDR + 0xFC8100)

/* 寄存器说明：
 bit[31:15]  保留
 bit[14:12]  当前轮循占用的通道号上报
 bit[11:8]   与LbusArbiter握手状态机上报
 bit[7:5]    保留
 bit[4]      CMD FIFO空标志上报
 bit[3:1]    保留
 bit[0]      CMD FIFO满标志上报
   UNION结构:  DBG_TRIG_ARBIT_INTF_STATE_RPT_UNION */
#define DBG_TRIG_ARBIT_INTF_STATE_RPT_ADDR            (SOC_BBP_DBG_TRIG_BASE_ADDR + 0xFC8104)

/* 寄存器说明：
 bit[31:21]  保留
 bit[20]     G2 超时状态上报，电平信号，软件查询状态后，需要做清零处理
 bit[19:17]  保留
 bit[16]     G1 超时状态上报，电平信号，软件查询状态后，需要做清零处理
 bit[15:13]  保留
 bit[12]     C2 超时状态上报，电平信号，软件查询状态后，需要做清零处理
 bit[11:9]   保留
 bit[8]      C1 超时状态上报，电平信号，软件查询状态后，需要做清零处理
 bit[7:5]    保留
 bit[4]      W2 超时状态上报，电平信号，软件查询状态后，需要做清零处理
 bit[3:1]    保留
 bit[0]      W1 超时状态上报，电平信号，软件查询状态后，需要做清零处理
   UNION结构:  DBG_TRIG_OVERTIME_RPT_UNION */
#define DBG_TRIG_OVERTIME_RPT_ADDR                    (SOC_BBP_DBG_TRIG_BASE_ADDR + 0xFC8108)



/***======================================================================***
                     (2/2) register_define_dbg_trig_mem
 ***======================================================================***/
/* 寄存器说明：寄存器地址表
 bit[31:28]  保留
 bit[27:8]   连续读寄存器的起始地址，为32bit寄存器地址的低20bit。W1和W2共用TRACE_ADDR_RAM相同地址段，G1和G2共用TRACE_ADDR_RAM相同地址段，C1和C2共用TRACE_ADDR_RAM相同地址段
 bit[7:0]    连续读寄存器的个数，范围0~255，0表示1个寄存器；255，表示256个寄存器
   UNION结构:  DBG_TRIG_TRACE_ADDR_RAM_UNION */
#define DBG_TRIG_TRACE_ADDR_RAM_ADDR                  (SOC_BBP_DBG_TRIG_BASE_ADDR + 0xFC8800)
#define DBG_TRIG_TRACE_ADDR_RAM_MEMDEPTH  (384)





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

/***======================================================================***
                     (1/2) register_define_dbg_trig
 ***======================================================================***/
/*****************************************************************************
 结构名    : DBG_TRIG_W1_CONFIG1_UNION
 结构说明  : W1_CONFIG1 寄存器结构定义。地址偏移量:0x000，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      w1_config1_reg;
    struct
    {
        unsigned int  cpu_w1_dbg_trig_sel   : 1;  /* bit[0]    : W1地址段有效使能（根据测试目的工具勾选使能） */
        unsigned int  reserved_0            : 3;  /* bit[1-3]  : 保留 */
        unsigned int  cpu_w1_dbg_trig_ready : 1;  /* bit[4]    : W1上下点使能（OAM根据W1模上下电情况配置） */
        unsigned int  reserved_1            : 3;  /* bit[5-7]  : 保留 */
        unsigned int  cpu_w1_base_addr      : 12; /* bit[8-19] : W1高地址段地址 */
        unsigned int  reserved_2            : 12; /* bit[20-31]: 保留 */
    } reg;
} DBG_TRIG_W1_CONFIG1_UNION;
#define DBG_TRIG_W1_CONFIG1_cpu_w1_dbg_trig_sel_START    (0)
#define DBG_TRIG_W1_CONFIG1_cpu_w1_dbg_trig_sel_END      (0)
#define DBG_TRIG_W1_CONFIG1_cpu_w1_dbg_trig_ready_START  (4)
#define DBG_TRIG_W1_CONFIG1_cpu_w1_dbg_trig_ready_END    (4)
#define DBG_TRIG_W1_CONFIG1_cpu_w1_base_addr_START       (8)
#define DBG_TRIG_W1_CONFIG1_cpu_w1_base_addr_END         (19)


/*****************************************************************************
 结构名    : DBG_TRIG_W1_CONFIG2_UNION
 结构说明  : W1_CONFIG2 寄存器结构定义。地址偏移量:0x004，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      w1_config2_reg;
    struct
    {
        unsigned int  cpu_w1_start_addr   : 9;  /* bit[0-8]  : W1 TRACE ADDR RAM起始地址 */
        unsigned int  reserved_0          : 3;  /* bit[9-11] : 保留 */
        unsigned int  cpu_w1_dbg_trig_num : 9;  /* bit[12-20]: W1 TRACE ADDR RAM长度 */
        unsigned int  reserved_1          : 11; /* bit[21-31]: 保留 */
    } reg;
} DBG_TRIG_W1_CONFIG2_UNION;
#define DBG_TRIG_W1_CONFIG2_cpu_w1_start_addr_START    (0)
#define DBG_TRIG_W1_CONFIG2_cpu_w1_start_addr_END      (8)
#define DBG_TRIG_W1_CONFIG2_cpu_w1_dbg_trig_num_START  (12)
#define DBG_TRIG_W1_CONFIG2_cpu_w1_dbg_trig_num_END    (20)


/*****************************************************************************
 结构名    : DBG_TRIG_W1_START_POS_UNION
 结构说明  : W1_START_POS 寄存器结构定义。地址偏移量:0x008，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      w1_start_pos_reg;
    struct
    {
        unsigned int  cpu_w1_trig_start_pos : 16; /* bit[0-15] : W1 TRACE定时起始位置，单位chip。
                                                                 bit[7:0]：symbol内chip计数，计数范围0~255chip；
                                                                 bit[11:8]：slot内symbol计数，计数范围0~9symbol；
                                                                 bit[15:12]：帧内slot计数，计数范围0~14slot */
        unsigned int  reserved              : 16; /* bit[16-31]: 保留 */
    } reg;
} DBG_TRIG_W1_START_POS_UNION;
#define DBG_TRIG_W1_START_POS_cpu_w1_trig_start_pos_START  (0)
#define DBG_TRIG_W1_START_POS_cpu_w1_trig_start_pos_END    (15)


/*****************************************************************************
 结构名    : DBG_TRIG_W2_CONFIG1_UNION
 结构说明  : W2_CONFIG1 寄存器结构定义。地址偏移量:0x00C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      w2_config1_reg;
    struct
    {
        unsigned int  cpu_w2_dbg_trig_sel   : 1;  /* bit[0]    : W2地址段有效使能（根据测试目的工具勾选使能） */
        unsigned int  reserved_0            : 3;  /* bit[1-3]  : 保留 */
        unsigned int  cpu_w2_dbg_trig_ready : 1;  /* bit[4]    : W2上下点使能（OAM根据W1模上下电情况配置） */
        unsigned int  reserved_1            : 3;  /* bit[5-7]  : 保留 */
        unsigned int  cpu_w2_base_addr      : 12; /* bit[8-19] : W2高地址段地址 */
        unsigned int  reserved_2            : 12; /* bit[20-31]: 保留 */
    } reg;
} DBG_TRIG_W2_CONFIG1_UNION;
#define DBG_TRIG_W2_CONFIG1_cpu_w2_dbg_trig_sel_START    (0)
#define DBG_TRIG_W2_CONFIG1_cpu_w2_dbg_trig_sel_END      (0)
#define DBG_TRIG_W2_CONFIG1_cpu_w2_dbg_trig_ready_START  (4)
#define DBG_TRIG_W2_CONFIG1_cpu_w2_dbg_trig_ready_END    (4)
#define DBG_TRIG_W2_CONFIG1_cpu_w2_base_addr_START       (8)
#define DBG_TRIG_W2_CONFIG1_cpu_w2_base_addr_END         (19)


/*****************************************************************************
 结构名    : DBG_TRIG_W2_CONFIG2_UNION
 结构说明  : W2_CONFIG2 寄存器结构定义。地址偏移量:0x010，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      w2_config2_reg;
    struct
    {
        unsigned int  cpu_w2_start_addr   : 9;  /* bit[0-8]  : W2 TRACE ADDR RAM起始地址 */
        unsigned int  reserved_0          : 3;  /* bit[9-11] : 保留 */
        unsigned int  cpu_w2_dbg_trig_num : 9;  /* bit[12-20]: W2 TRACE ADDR RAM长度 */
        unsigned int  reserved_1          : 11; /* bit[21-31]: 保留 */
    } reg;
} DBG_TRIG_W2_CONFIG2_UNION;
#define DBG_TRIG_W2_CONFIG2_cpu_w2_start_addr_START    (0)
#define DBG_TRIG_W2_CONFIG2_cpu_w2_start_addr_END      (8)
#define DBG_TRIG_W2_CONFIG2_cpu_w2_dbg_trig_num_START  (12)
#define DBG_TRIG_W2_CONFIG2_cpu_w2_dbg_trig_num_END    (20)


/*****************************************************************************
 结构名    : DBG_TRIG_W2_START_POS_UNION
 结构说明  : W2_START_POS 寄存器结构定义。地址偏移量:0x014，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      w2_start_pos_reg;
    struct
    {
        unsigned int  cpu_w2_trig_start_pos : 16; /* bit[0-15] : W2 TRACE定时起始位置，单位chip。
                                                                 bit[7:0]：symbol内chip计数，计数范围0~255chip；
                                                                 bit[11:8]：slot内symbol计数，计数范围0~9symbol；
                                                                 bit[15:12]：帧内slot计数，计数范围0~14slot */
        unsigned int  reserved              : 16; /* bit[16-31]: 保留 */
    } reg;
} DBG_TRIG_W2_START_POS_UNION;
#define DBG_TRIG_W2_START_POS_cpu_w2_trig_start_pos_START  (0)
#define DBG_TRIG_W2_START_POS_cpu_w2_trig_start_pos_END    (15)


/*****************************************************************************
 结构名    : DBG_TRIG_C1_CONFIG1_UNION
 结构说明  : C1_CONFIG1 寄存器结构定义。地址偏移量:0x018，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      c1_config1_reg;
    struct
    {
        unsigned int  cpu_c1_dbg_trig_sel   : 1;  /* bit[0]    : C1地址段有效使能（根据测试目的工具勾选使能） */
        unsigned int  reserved_0            : 3;  /* bit[1-3]  : 保留 */
        unsigned int  cpu_c1_dbg_trig_ready : 1;  /* bit[4]    : C1上下点使能（OAM根据W1模上下电情况配置） */
        unsigned int  reserved_1            : 3;  /* bit[5-7]  : 保留 */
        unsigned int  cpu_c1_base_addr      : 12; /* bit[8-19] : C1高地址段地址 */
        unsigned int  reserved_2            : 12; /* bit[20-31]: 保留 */
    } reg;
} DBG_TRIG_C1_CONFIG1_UNION;
#define DBG_TRIG_C1_CONFIG1_cpu_c1_dbg_trig_sel_START    (0)
#define DBG_TRIG_C1_CONFIG1_cpu_c1_dbg_trig_sel_END      (0)
#define DBG_TRIG_C1_CONFIG1_cpu_c1_dbg_trig_ready_START  (4)
#define DBG_TRIG_C1_CONFIG1_cpu_c1_dbg_trig_ready_END    (4)
#define DBG_TRIG_C1_CONFIG1_cpu_c1_base_addr_START       (8)
#define DBG_TRIG_C1_CONFIG1_cpu_c1_base_addr_END         (19)


/*****************************************************************************
 结构名    : DBG_TRIG_C1_CONFIG2_UNION
 结构说明  : C1_CONFIG2 寄存器结构定义。地址偏移量:0x01C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      c1_config2_reg;
    struct
    {
        unsigned int  cpu_c1_start_addr   : 9;  /* bit[0-8]  : C1 TRACE ADDR RAM起始地址 */
        unsigned int  reserved_0          : 3;  /* bit[9-11] : 保留 */
        unsigned int  cpu_c1_dbg_trig_num : 9;  /* bit[12-20]: C1 TRACE ADDR RAM长度 */
        unsigned int  reserved_1          : 11; /* bit[21-31]: 保留 */
    } reg;
} DBG_TRIG_C1_CONFIG2_UNION;
#define DBG_TRIG_C1_CONFIG2_cpu_c1_start_addr_START    (0)
#define DBG_TRIG_C1_CONFIG2_cpu_c1_start_addr_END      (8)
#define DBG_TRIG_C1_CONFIG2_cpu_c1_dbg_trig_num_START  (12)
#define DBG_TRIG_C1_CONFIG2_cpu_c1_dbg_trig_num_END    (20)


/*****************************************************************************
 结构名    : DBG_TRIG_C1_START_POS_UNION
 结构说明  : C1_START_POS 寄存器结构定义。地址偏移量:0x020，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      c1_start_pos_reg;
    struct
    {
        unsigned int  cpu_c1_trig_start_pos : 15; /* bit[0-14] : C1 TRACE定时起始位置，单位chip。
                                                                 EVDO：
                                                                 bit[14:0]：帧内chip计数，计数范围0~32767chip，时间长度80/3ms；
                                                                 1X：
                                                                 bit[10:0]：PCG内chip计数，计数范围0~1535chip，时间长度80/64；
                                                                 bit[14:11]：PCG计数，计数范围0~15，时间长度20ms。 */
        unsigned int  reserved              : 17; /* bit[15-31]: 保留 */
    } reg;
} DBG_TRIG_C1_START_POS_UNION;
#define DBG_TRIG_C1_START_POS_cpu_c1_trig_start_pos_START  (0)
#define DBG_TRIG_C1_START_POS_cpu_c1_trig_start_pos_END    (14)


/*****************************************************************************
 结构名    : DBG_TRIG_C2_CONFIG1_UNION
 结构说明  : C2_CONFIG1 寄存器结构定义。地址偏移量:0x024，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      c2_config1_reg;
    struct
    {
        unsigned int  cpu_c2_dbg_trig_sel   : 1;  /* bit[0]    : C2地址段有效使能（根据测试目的工具勾选使能） */
        unsigned int  reserved_0            : 3;  /* bit[1-3]  : 保留 */
        unsigned int  cpu_c2_dbg_trig_ready : 1;  /* bit[4]    : C2上下点使能（OAM根据W1模上下电情况配置） */
        unsigned int  reserved_1            : 3;  /* bit[5-7]  : 保留 */
        unsigned int  cpu_c2_base_addr      : 12; /* bit[8-19] : C2高地址段地址 */
        unsigned int  reserved_2            : 12; /* bit[20-31]: 保留 */
    } reg;
} DBG_TRIG_C2_CONFIG1_UNION;
#define DBG_TRIG_C2_CONFIG1_cpu_c2_dbg_trig_sel_START    (0)
#define DBG_TRIG_C2_CONFIG1_cpu_c2_dbg_trig_sel_END      (0)
#define DBG_TRIG_C2_CONFIG1_cpu_c2_dbg_trig_ready_START  (4)
#define DBG_TRIG_C2_CONFIG1_cpu_c2_dbg_trig_ready_END    (4)
#define DBG_TRIG_C2_CONFIG1_cpu_c2_base_addr_START       (8)
#define DBG_TRIG_C2_CONFIG1_cpu_c2_base_addr_END         (19)


/*****************************************************************************
 结构名    : DBG_TRIG_C2_CONFIG2_UNION
 结构说明  : C2_CONFIG2 寄存器结构定义。地址偏移量:0x028，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      c2_config2_reg;
    struct
    {
        unsigned int  cpu_c2_start_addr   : 9;  /* bit[0-8]  : C2 TRACE ADDR RAM起始地址 */
        unsigned int  reserved_0          : 3;  /* bit[9-11] : 保留 */
        unsigned int  cpu_c2_dbg_trig_num : 9;  /* bit[12-20]: C2 TRACE ADDR RAM长度 */
        unsigned int  reserved_1          : 11; /* bit[21-31]: 保留 */
    } reg;
} DBG_TRIG_C2_CONFIG2_UNION;
#define DBG_TRIG_C2_CONFIG2_cpu_c2_start_addr_START    (0)
#define DBG_TRIG_C2_CONFIG2_cpu_c2_start_addr_END      (8)
#define DBG_TRIG_C2_CONFIG2_cpu_c2_dbg_trig_num_START  (12)
#define DBG_TRIG_C2_CONFIG2_cpu_c2_dbg_trig_num_END    (20)


/*****************************************************************************
 结构名    : DBG_TRIG_C2_START_POS_UNION
 结构说明  : C2_START_POS 寄存器结构定义。地址偏移量:0x02C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      c2_start_pos_reg;
    struct
    {
        unsigned int  cpu_c2_trig_start_pos : 15; /* bit[0-14] : C2 TRACE定时起始位置，单位chip。
                                                                 EVDO：
                                                                 bit[14:0]：帧内chip计数，计数范围0~32767chip，时间长度80/3ms；
                                                                 1X：
                                                                 bit[10:0]：PCG内chip计数，计数范围0~1535chip，时间长度80/64；
                                                                 bit[14:11]：PCG计数，计数范围0~15，时间长度20ms。 */
        unsigned int  reserved              : 17; /* bit[15-31]: 保留 */
    } reg;
} DBG_TRIG_C2_START_POS_UNION;
#define DBG_TRIG_C2_START_POS_cpu_c2_trig_start_pos_START  (0)
#define DBG_TRIG_C2_START_POS_cpu_c2_trig_start_pos_END    (14)


/*****************************************************************************
 结构名    : DBG_TRIG_G1_CONFIG1_UNION
 结构说明  : G1_CONFIG1 寄存器结构定义。地址偏移量:0x030，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      g1_config1_reg;
    struct
    {
        unsigned int  cpu_g1_dbg_trig_sel   : 1;  /* bit[0]    : G1地址段有效使能（根据测试目的工具勾选使能） */
        unsigned int  reserved_0            : 3;  /* bit[1-3]  : 保留 */
        unsigned int  cpu_g1_dbg_trig_ready : 1;  /* bit[4]    : G1上下点使能（OAM根据W1模上下电情况配置） */
        unsigned int  reserved_1            : 3;  /* bit[5-7]  : 保留 */
        unsigned int  cpu_g1_base_addr      : 12; /* bit[8-19] : G1高地址段地址 */
        unsigned int  reserved_2            : 12; /* bit[20-31]: 保留 */
    } reg;
} DBG_TRIG_G1_CONFIG1_UNION;
#define DBG_TRIG_G1_CONFIG1_cpu_g1_dbg_trig_sel_START    (0)
#define DBG_TRIG_G1_CONFIG1_cpu_g1_dbg_trig_sel_END      (0)
#define DBG_TRIG_G1_CONFIG1_cpu_g1_dbg_trig_ready_START  (4)
#define DBG_TRIG_G1_CONFIG1_cpu_g1_dbg_trig_ready_END    (4)
#define DBG_TRIG_G1_CONFIG1_cpu_g1_base_addr_START       (8)
#define DBG_TRIG_G1_CONFIG1_cpu_g1_base_addr_END         (19)


/*****************************************************************************
 结构名    : DBG_TRIG_G1_CONFIG2_UNION
 结构说明  : G1_CONFIG2 寄存器结构定义。地址偏移量:0x034，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      g1_config2_reg;
    struct
    {
        unsigned int  cpu_g1_start_addr   : 9;  /* bit[0-8]  : G1 TRACE ADDR RAM起始地址 */
        unsigned int  reserved_0          : 3;  /* bit[9-11] : 保留 */
        unsigned int  cpu_g1_dbg_trig_num : 9;  /* bit[12-20]: G1 TRACE ADDR RAM长度 */
        unsigned int  reserved_1          : 11; /* bit[21-31]: 保留 */
    } reg;
} DBG_TRIG_G1_CONFIG2_UNION;
#define DBG_TRIG_G1_CONFIG2_cpu_g1_start_addr_START    (0)
#define DBG_TRIG_G1_CONFIG2_cpu_g1_start_addr_END      (8)
#define DBG_TRIG_G1_CONFIG2_cpu_g1_dbg_trig_num_START  (12)
#define DBG_TRIG_G1_CONFIG2_cpu_g1_dbg_trig_num_END    (20)


/*****************************************************************************
 结构名    : DBG_TRIG_G1_START_POS_UNION
 结构说明  : G1_START_POS 寄存器结构定义。地址偏移量:0x038，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      g1_start_pos_reg;
    struct
    {
        unsigned int  cpu_g1_trig_start_pos : 13; /* bit[0-12] : G1 TRACE定时起始位置，单位Qb。
                                                                 bit[12:0]：gtc_tdma_qb上的帧内Qb计数，计数范围0~4999Qb； */
        unsigned int  reserved              : 19; /* bit[13-31]: 保留 */
    } reg;
} DBG_TRIG_G1_START_POS_UNION;
#define DBG_TRIG_G1_START_POS_cpu_g1_trig_start_pos_START  (0)
#define DBG_TRIG_G1_START_POS_cpu_g1_trig_start_pos_END    (12)


/*****************************************************************************
 结构名    : DBG_TRIG_G2_CONFIG1_UNION
 结构说明  : G2_CONFIG1 寄存器结构定义。地址偏移量:0x03C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      g2_config1_reg;
    struct
    {
        unsigned int  cpu_g2_dbg_trig_sel   : 1;  /* bit[0]    : G2地址段有效使能（根据测试目的工具勾选使能） */
        unsigned int  reserved_0            : 3;  /* bit[1-3]  : 保留 */
        unsigned int  cpu_g2_dbg_trig_ready : 1;  /* bit[4]    : G2上下点使能（OAM根据W1模上下电情况配置） */
        unsigned int  reserved_1            : 3;  /* bit[5-7]  : 保留 */
        unsigned int  cpu_g2_base_addr      : 12; /* bit[8-19] : G2高地址段地址 */
        unsigned int  reserved_2            : 12; /* bit[20-31]: 保留 */
    } reg;
} DBG_TRIG_G2_CONFIG1_UNION;
#define DBG_TRIG_G2_CONFIG1_cpu_g2_dbg_trig_sel_START    (0)
#define DBG_TRIG_G2_CONFIG1_cpu_g2_dbg_trig_sel_END      (0)
#define DBG_TRIG_G2_CONFIG1_cpu_g2_dbg_trig_ready_START  (4)
#define DBG_TRIG_G2_CONFIG1_cpu_g2_dbg_trig_ready_END    (4)
#define DBG_TRIG_G2_CONFIG1_cpu_g2_base_addr_START       (8)
#define DBG_TRIG_G2_CONFIG1_cpu_g2_base_addr_END         (19)


/*****************************************************************************
 结构名    : DBG_TRIG_G2_CONFIG2_UNION
 结构说明  : G2_CONFIG2 寄存器结构定义。地址偏移量:0x040，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      g2_config2_reg;
    struct
    {
        unsigned int  cpu_g2_start_addr   : 9;  /* bit[0-8]  : G2 TRACE ADDR RAM起始地址 */
        unsigned int  reserved_0          : 3;  /* bit[9-11] : 保留 */
        unsigned int  cpu_g2_dbg_trig_num : 9;  /* bit[12-20]: G2 TRACE ADDR RAM长度 */
        unsigned int  reserved_1          : 11; /* bit[21-31]: 保留 */
    } reg;
} DBG_TRIG_G2_CONFIG2_UNION;
#define DBG_TRIG_G2_CONFIG2_cpu_g2_start_addr_START    (0)
#define DBG_TRIG_G2_CONFIG2_cpu_g2_start_addr_END      (8)
#define DBG_TRIG_G2_CONFIG2_cpu_g2_dbg_trig_num_START  (12)
#define DBG_TRIG_G2_CONFIG2_cpu_g2_dbg_trig_num_END    (20)


/*****************************************************************************
 结构名    : DBG_TRIG_G2_START_POS_UNION
 结构说明  : G2_START_POS 寄存器结构定义。地址偏移量:0x044，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      g2_start_pos_reg;
    struct
    {
        unsigned int  cpu_g2_trig_start_pos : 13; /* bit[0-12] : G2 TRACE定时起始位置，单位Qb。
                                                                 bit[12:0]：gtc_tdma_qb上的帧内Qb计数，计数范围0~4999Qb； */
        unsigned int  reserved              : 19; /* bit[13-31]: 保留 */
    } reg;
} DBG_TRIG_G2_START_POS_UNION;
#define DBG_TRIG_G2_START_POS_cpu_g2_trig_start_pos_START  (0)
#define DBG_TRIG_G2_START_POS_cpu_g2_trig_start_pos_END    (12)


/*****************************************************************************
 结构名    : DBG_TRIG_MEM_CTRL0_DBG_UNION
 结构说明  : MEM_CTRL0_DBG 寄存器结构定义。地址偏移量:0x048，初值:0x03501050，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      mem_ctrl0_dbg_reg;
    struct
    {
        unsigned int  mem_ctrl_s_dbg      : 16; /* bit[0-15] : 单端口ram延时控制。 */
        unsigned int  mem_ctrl_d_1w2r_dbg : 16; /* bit[16-31]: 1w2r双端口ram延时控制。 */
    } reg;
} DBG_TRIG_MEM_CTRL0_DBG_UNION;
#define DBG_TRIG_MEM_CTRL0_DBG_mem_ctrl_s_dbg_START       (0)
#define DBG_TRIG_MEM_CTRL0_DBG_mem_ctrl_s_dbg_END         (15)
#define DBG_TRIG_MEM_CTRL0_DBG_mem_ctrl_d_1w2r_dbg_START  (16)
#define DBG_TRIG_MEM_CTRL0_DBG_mem_ctrl_d_1w2r_dbg_END    (31)


/*****************************************************************************
 结构名    : DBG_TRIG_MEM_CTRL1_DBG_UNION
 结构说明  : MEM_CTRL1_DBG 寄存器结构定义。地址偏移量:0x04C，初值:0x00700057，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      mem_ctrl1_dbg_reg;
    struct
    {
        unsigned int  mem_ctrl_d_1rw2rw_dbg : 16; /* bit[0-15] : 1rw2rw双端口ram延时控制。 */
        unsigned int  rom_ctrl_dbg          : 8;  /* bit[16-23]: rom延时控制。 */
        unsigned int  reserved              : 8;  /* bit[24-31]: 保留 */
    } reg;
} DBG_TRIG_MEM_CTRL1_DBG_UNION;
#define DBG_TRIG_MEM_CTRL1_DBG_mem_ctrl_d_1rw2rw_dbg_START  (0)
#define DBG_TRIG_MEM_CTRL1_DBG_mem_ctrl_d_1rw2rw_dbg_END    (15)
#define DBG_TRIG_MEM_CTRL1_DBG_rom_ctrl_dbg_START           (16)
#define DBG_TRIG_MEM_CTRL1_DBG_rom_ctrl_dbg_END             (23)


/*****************************************************************************
 结构名    : DBG_TRIG_OVERTIME_CLR_UNION
 结构说明  : OVERTIME_CLR 寄存器结构定义。地址偏移量:0x050，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      overtime_clr_reg;
    struct
    {
        unsigned int  cpu_overtime_clr : 1;  /* bit[0]   : 超时保护清零脉冲，6模共用。 */
        unsigned int  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} DBG_TRIG_OVERTIME_CLR_UNION;
#define DBG_TRIG_OVERTIME_CLR_cpu_overtime_clr_START  (0)
#define DBG_TRIG_OVERTIME_CLR_cpu_overtime_clr_END    (0)


/*****************************************************************************
 结构名    : DBG_TRIG_CTRL_CURR_STATE_RPT_UNION
 结构说明  : CTRL_CURR_STATE_RPT 寄存器结构定义。地址偏移量:0x100，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      ctrl_curr_state_rpt_reg;
    struct
    {
        unsigned int  w1_curr_st : 2;  /* bit[0-1]  : W1 轮询控制状态机上报 */
        unsigned int  reserved_0 : 2;  /* bit[2-3]  : 保留 */
        unsigned int  w2_curr_st : 2;  /* bit[4-5]  : W2 轮询控制状态机上报 */
        unsigned int  reserved_1 : 2;  /* bit[6-7]  : 保留 */
        unsigned int  c1_curr_st : 2;  /* bit[8-9]  : C1 轮询控制状态机上报 */
        unsigned int  reserved_2 : 2;  /* bit[10-11]: 保留 */
        unsigned int  c2_curr_st : 2;  /* bit[12-13]: C2 轮询控制状态机上报 */
        unsigned int  reserved_3 : 2;  /* bit[14-15]: 保留 */
        unsigned int  g1_curr_st : 2;  /* bit[16-17]: G1 轮询控制状态机上报 */
        unsigned int  reserved_4 : 2;  /* bit[18-19]: 保留 */
        unsigned int  g2_curr_st : 2;  /* bit[20-21]: G2 轮询控制状态机上报 */
        unsigned int  reserved_5 : 10; /* bit[22-31]: 保留 */
    } reg;
} DBG_TRIG_CTRL_CURR_STATE_RPT_UNION;
#define DBG_TRIG_CTRL_CURR_STATE_RPT_w1_curr_st_START  (0)
#define DBG_TRIG_CTRL_CURR_STATE_RPT_w1_curr_st_END    (1)
#define DBG_TRIG_CTRL_CURR_STATE_RPT_w2_curr_st_START  (4)
#define DBG_TRIG_CTRL_CURR_STATE_RPT_w2_curr_st_END    (5)
#define DBG_TRIG_CTRL_CURR_STATE_RPT_c1_curr_st_START  (8)
#define DBG_TRIG_CTRL_CURR_STATE_RPT_c1_curr_st_END    (9)
#define DBG_TRIG_CTRL_CURR_STATE_RPT_c2_curr_st_START  (12)
#define DBG_TRIG_CTRL_CURR_STATE_RPT_c2_curr_st_END    (13)
#define DBG_TRIG_CTRL_CURR_STATE_RPT_g1_curr_st_START  (16)
#define DBG_TRIG_CTRL_CURR_STATE_RPT_g1_curr_st_END    (17)
#define DBG_TRIG_CTRL_CURR_STATE_RPT_g2_curr_st_START  (20)
#define DBG_TRIG_CTRL_CURR_STATE_RPT_g2_curr_st_END    (21)


/*****************************************************************************
 结构名    : DBG_TRIG_ARBIT_INTF_STATE_RPT_UNION
 结构说明  : ARBIT_INTF_STATE_RPT 寄存器结构定义。地址偏移量:0x104，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      arbit_intf_state_rpt_reg;
    struct
    {
        unsigned int  cfifo_full  : 1;  /* bit[0]    : CMD FIFO满标志上报 */
        unsigned int  reserved_0  : 3;  /* bit[1-3]  : 保留 */
        unsigned int  cfifo_empty : 1;  /* bit[4]    : CMD FIFO空标志上报 */
        unsigned int  reserved_1  : 3;  /* bit[5-7]  : 保留 */
        unsigned int  lbus_st     : 4;  /* bit[8-11] : 与LbusArbiter握手状态机上报 */
        unsigned int  req_num     : 3;  /* bit[12-14]: 当前轮循占用的通道号上报 */
        unsigned int  reserved_2  : 17; /* bit[15-31]: 保留 */
    } reg;
} DBG_TRIG_ARBIT_INTF_STATE_RPT_UNION;
#define DBG_TRIG_ARBIT_INTF_STATE_RPT_cfifo_full_START   (0)
#define DBG_TRIG_ARBIT_INTF_STATE_RPT_cfifo_full_END     (0)
#define DBG_TRIG_ARBIT_INTF_STATE_RPT_cfifo_empty_START  (4)
#define DBG_TRIG_ARBIT_INTF_STATE_RPT_cfifo_empty_END    (4)
#define DBG_TRIG_ARBIT_INTF_STATE_RPT_lbus_st_START      (8)
#define DBG_TRIG_ARBIT_INTF_STATE_RPT_lbus_st_END        (11)
#define DBG_TRIG_ARBIT_INTF_STATE_RPT_req_num_START      (12)
#define DBG_TRIG_ARBIT_INTF_STATE_RPT_req_num_END        (14)


/*****************************************************************************
 结构名    : DBG_TRIG_OVERTIME_RPT_UNION
 结构说明  : OVERTIME_RPT 寄存器结构定义。地址偏移量:0x108，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      overtime_rpt_reg;
    struct
    {
        unsigned int  w1_overtime_rpt : 1;  /* bit[0]    : W1 超时状态上报，电平信号，软件查询状态后，需要做清零处理 */
        unsigned int  reserved_0      : 3;  /* bit[1-3]  : 保留 */
        unsigned int  w2_overtime_rpt : 1;  /* bit[4]    : W2 超时状态上报，电平信号，软件查询状态后，需要做清零处理 */
        unsigned int  reserved_1      : 3;  /* bit[5-7]  : 保留 */
        unsigned int  c1_overtime_rpt : 1;  /* bit[8]    : C1 超时状态上报，电平信号，软件查询状态后，需要做清零处理 */
        unsigned int  reserved_2      : 3;  /* bit[9-11] : 保留 */
        unsigned int  c2_overtime_rpt : 1;  /* bit[12]   : C2 超时状态上报，电平信号，软件查询状态后，需要做清零处理 */
        unsigned int  reserved_3      : 3;  /* bit[13-15]: 保留 */
        unsigned int  g1_overtime_rpt : 1;  /* bit[16]   : G1 超时状态上报，电平信号，软件查询状态后，需要做清零处理 */
        unsigned int  reserved_4      : 3;  /* bit[17-19]: 保留 */
        unsigned int  g2_overtime_rpt : 1;  /* bit[20]   : G2 超时状态上报，电平信号，软件查询状态后，需要做清零处理 */
        unsigned int  reserved_5      : 11; /* bit[21-31]: 保留 */
    } reg;
} DBG_TRIG_OVERTIME_RPT_UNION;
#define DBG_TRIG_OVERTIME_RPT_w1_overtime_rpt_START  (0)
#define DBG_TRIG_OVERTIME_RPT_w1_overtime_rpt_END    (0)
#define DBG_TRIG_OVERTIME_RPT_w2_overtime_rpt_START  (4)
#define DBG_TRIG_OVERTIME_RPT_w2_overtime_rpt_END    (4)
#define DBG_TRIG_OVERTIME_RPT_c1_overtime_rpt_START  (8)
#define DBG_TRIG_OVERTIME_RPT_c1_overtime_rpt_END    (8)
#define DBG_TRIG_OVERTIME_RPT_c2_overtime_rpt_START  (12)
#define DBG_TRIG_OVERTIME_RPT_c2_overtime_rpt_END    (12)
#define DBG_TRIG_OVERTIME_RPT_g1_overtime_rpt_START  (16)
#define DBG_TRIG_OVERTIME_RPT_g1_overtime_rpt_END    (16)
#define DBG_TRIG_OVERTIME_RPT_g2_overtime_rpt_START  (20)
#define DBG_TRIG_OVERTIME_RPT_g2_overtime_rpt_END    (20)


/***======================================================================***
                     (2/2) register_define_dbg_trig_mem
 ***======================================================================***/
/*****************************************************************************
 结构名    : DBG_TRIG_TRACE_ADDR_RAM_UNION
 结构说明  : TRACE_ADDR_RAM 寄存器结构定义。地址偏移量:0x800，初值:0x00000000，宽度:32
 寄存器说明: 寄存器地址表
*****************************************************************************/
typedef union
{
    unsigned int      trace_addr_ram_reg;
    struct
    {
        unsigned int  len        : 8;  /* bit[0-7]  : 连续读寄存器的个数，范围0~255，0表示1个寄存器；255，表示256个寄存器 */
        unsigned int  start_addr : 20; /* bit[8-27] : 连续读寄存器的起始地址，为32bit寄存器地址的低20bit。W1和W2共用TRACE_ADDR_RAM相同地址段，G1和G2共用TRACE_ADDR_RAM相同地址段，C1和C2共用TRACE_ADDR_RAM相同地址段 */
        unsigned int  reserved   : 4;  /* bit[28-31]: 保留 */
    } reg;
} DBG_TRIG_TRACE_ADDR_RAM_UNION;
#define DBG_TRIG_TRACE_ADDR_RAM_len_START         (0)
#define DBG_TRIG_TRACE_ADDR_RAM_len_END           (7)
#define DBG_TRIG_TRACE_ADDR_RAM_start_addr_START  (8)
#define DBG_TRIG_TRACE_ADDR_RAM_start_addr_END    (27)




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

#endif /* end of bbp_dbg_trig_interface.h */
