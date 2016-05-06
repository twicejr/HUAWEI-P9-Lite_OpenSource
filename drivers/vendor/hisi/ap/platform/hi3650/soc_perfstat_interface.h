/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_perfstat_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:22:26
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_PERFSTAT.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_PERFSTAT_INTERFACE_H__
#define __SOC_PERFSTAT_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) register_PERF_STAT
 ****************************************************************************/
/* 寄存器说明：时钟gate寄存器
   位域定义UNION结构:  SOC_PERFSTAT_CLK_GATE_UNION */
#define SOC_PERFSTAT_CLK_GATE_ADDR(base)              ((base) + (0x00))

/* 寄存器说明：启动寄存器。
   位域定义UNION结构:  SOC_PERFSTAT_CMD_START_UNION */
#define SOC_PERFSTAT_CMD_START_ADDR(base)             ((base) + (0x04))

/* 寄存器说明：采样统计周期寄存器。
   位域定义UNION结构:  SOC_PERFSTAT_SAMPLE_CNT_REG_UNION */
#define SOC_PERFSTAT_SAMPLE_CNT_REG_ADDR(base)        ((base) + (0x08))

/* 寄存器说明：采样次数寄存器。
   位域定义UNION结构:  SOC_PERFSTAT_SAMPLE_NUM_REG_UNION */
#define SOC_PERFSTAT_SAMPLE_NUM_REG_ADDR(base)        ((base) + (0x0C))

/* 寄存器说明：采样停止寄存器
   位域定义UNION结构:  SOC_PERFSTAT_SAMPLE_STOP_UNION */
#define SOC_PERFSTAT_SAMPLE_STOP_ADDR(base)           ((base) + (0x10))

/* 寄存器说明：监控端口个数寄存器。
   位域定义UNION结构:  SOC_PERFSTAT_REAL_PORT_NUM_UNION */
#define SOC_PERFSTAT_REAL_PORT_NUM_ADDR(base)         ((base) + (0x14))

/* 寄存器说明：地址模式寄存器
   位域定义UNION结构:  SOC_PERFSTAT_AXI_ADDR_MODE_UNION */
#define SOC_PERFSTAT_AXI_ADDR_MODE_ADDR(base)         ((base) + (0x18))

/* 寄存器说明：连续模式写地址寄存器。
   位域定义UNION结构:  SOC_PERFSTAT_SEQ_ADDR_UNION */
#define SOC_PERFSTAT_SEQ_ADDR_ADDR(base)              ((base) + (0x1C))

/* 寄存器说明：连续模式写地址区间寄存器。
   位域定义UNION结构:  SOC_PERFSTAT_SEQ_ADDR_LEN_UNION */
#define SOC_PERFSTAT_SEQ_ADDR_LEN_ADDR(base)          ((base) + (0x20))

/* 寄存器说明：链表地址
   位域定义UNION结构:  SOC_PERFSTAT_DESCRIPTOR_ADDR_UNION */
#define SOC_PERFSTAT_DESCRIPTOR_ADDR_ADDR(base)       ((base) + (0x24))

/* 寄存器说明：当前链表地址寄存器
   位域定义UNION结构:  SOC_PERFSTAT_LAST_DESC_ADDR_UNION */
#define SOC_PERFSTAT_LAST_DESC_ADDR_ADDR(base)        ((base) + (0x28))

/* 寄存器说明：复位后计数寄存器
   位域定义UNION结构:  SOC_PERFSTAT_STAT_RST_CNT_UNION */
#define SOC_PERFSTAT_STAT_RST_CNT_ADDR(base)          ((base) + (0x2C))

/* 寄存器说明：ST中断屏蔽控制寄存器
   位域定义UNION结构:  SOC_PERFSTAT_INT_EN_UNION */
#define SOC_PERFSTAT_INT_EN_ADDR(base)                ((base) + (0x30))

/* 寄存器说明：ST中断清除寄存器
   位域定义UNION结构:  SOC_PERFSTAT_INT_CLR_UNION */
#define SOC_PERFSTAT_INT_CLR_ADDR(base)               ((base) + (0x34))

/* 寄存器说明：ST原始中断状态寄存器
   位域定义UNION结构:  SOC_PERFSTAT_RAW_INT_STAT_UNION */
#define SOC_PERFSTAT_RAW_INT_STAT_ADDR(base)          ((base) + (0x38))

/* 寄存器说明：ST屏蔽后中断状态寄存器
   位域定义UNION结构:  SOC_PERFSTAT_MASK_INT_STAT_UNION */
#define SOC_PERFSTAT_MASK_INT_STAT_ADDR(base)         ((base) + (0x3C))

/* 寄存器说明：总采样次数寄存器
   位域定义UNION结构:  SOC_PERFSTAT_ALL_SAMPLE_NUM_UNION */
#define SOC_PERFSTAT_ALL_SAMPLE_NUM_ADDR(base)        ((base) + (0x40))

/* 寄存器说明：采样地址寄存器
   位域定义UNION结构:  SOC_PERFSTAT_LAST_SAMPLE_AXI_ADDR_UNION */
#define SOC_PERFSTAT_LAST_SAMPLE_AXI_ADDR_ADDR(base)  ((base) + (0x44))

/* 寄存器说明：超时计数器
   位域定义UNION结构:  SOC_PERFSTAT_OVERTIME_CFG_CNT_UNION */
#define SOC_PERFSTAT_OVERTIME_CFG_CNT_ADDR(base)      ((base) + (0x48))

/* 寄存器说明：查询fifo满状态寄存器
   位域定义UNION结构:  SOC_PERFSTAT_DEBUG_FIFO_FULL_UNION */
#define SOC_PERFSTAT_DEBUG_FIFO_FULL_ADDR(base)       ((base) + (0x4C))

/* 寄存器说明：查询monitor阻塞寄存器
   位域定义UNION结构:  SOC_PERFSTAT_DEBUG_MONITOR_UNION */
#define SOC_PERFSTAT_DEBUG_MONITOR_ADDR(base)         ((base) + (0x50))

/* 寄存器说明：monitor复位寄存器
   位域定义UNION结构:  SOC_PERFSTAT_MONITOR_RESET_UNION */
#define SOC_PERFSTAT_MONITOR_RESET_ADDR(base)         ((base) + (0x54))





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
                     (1/1) register_PERF_STAT
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_PERFSTAT_CLK_GATE_UNION
 结构说明  : CLK_GATE 寄存器结构定义。地址偏移量:0x00，初值:0x0000，宽度:32
 寄存器说明: 时钟gate寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  apb_clk_gate : 1;  /* bit[0]   : 时钟gate，需配置real_port_num为0xffff。在采样未启动时使用，gating生效后，不可恢复。
                                                       gating的是远程monitor总线axi时钟。
                                                       0：时钟gate无效；
                                                       1：时钟gate有效。 */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_PERFSTAT_CLK_GATE_UNION;
#endif
#define SOC_PERFSTAT_CLK_GATE_apb_clk_gate_START  (0)
#define SOC_PERFSTAT_CLK_GATE_apb_clk_gate_END    (0)


/*****************************************************************************
 结构名    : SOC_PERFSTAT_CMD_START_UNION
 结构说明  : CMD_START 寄存器结构定义。地址偏移量:0x04，初值:0x00000000，宽度:32
 寄存器说明: 启动寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cmd_start : 1;  /* bit[0]   : 采样启动标志。
                                                    0：启动配置未生效；
                                                    1：启动配置生效。 */
        unsigned int  reserved  : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_PERFSTAT_CMD_START_UNION;
#endif
#define SOC_PERFSTAT_CMD_START_cmd_start_START  (0)
#define SOC_PERFSTAT_CMD_START_cmd_start_END    (0)


/*****************************************************************************
 结构名    : SOC_PERFSTAT_SAMPLE_CNT_REG_UNION
 结构说明  : SAMPLE_CNT_REG 寄存器结构定义。地址偏移量:0x08，初值:0x00000000，宽度:32
 寄存器说明: 采样统计周期寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: 采样统计周期数，时钟频率为60MHz。 */
    } reg;
} SOC_PERFSTAT_SAMPLE_CNT_REG_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_PERFSTAT_SAMPLE_NUM_REG_UNION
 结构说明  : SAMPLE_NUM_REG 寄存器结构定义。地址偏移量:0x0C，初值:0x00000000，宽度:32
 寄存器说明: 采样次数寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: 采样次数。其中0表示循环采样，其他值为实际采样次数。 */
    } reg;
} SOC_PERFSTAT_SAMPLE_NUM_REG_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_PERFSTAT_SAMPLE_STOP_UNION
 结构说明  : SAMPLE_STOP 寄存器结构定义。地址偏移量:0x10，初值:0x0000，宽度:32
 寄存器说明: 采样停止寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sample_stop : 1;  /* bit[0]   : 采样停止。
                                                      0：无效；
                                                      1：配置采样停止。 */
        unsigned int  reserved    : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_PERFSTAT_SAMPLE_STOP_UNION;
#endif
#define SOC_PERFSTAT_SAMPLE_STOP_sample_stop_START  (0)
#define SOC_PERFSTAT_SAMPLE_STOP_sample_stop_END    (0)


/*****************************************************************************
 结构名    : SOC_PERFSTAT_REAL_PORT_NUM_UNION
 结构说明  : REAL_PORT_NUM 寄存器结构定义。地址偏移量:0x14，初值:0x00000000，宽度:32
 寄存器说明: 监控端口个数寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  real_port_num : 16; /* bit[0-15] : 配置待监控端口个数（每bit代表1个端口，如设置监控每个端口，配置为0xffff）。
                                                         其中端口映射如下：【0】：dss_m0；【1】：dss_m1；【2】：cci_m1；【3】：cci_m2；【4】：gpu；【5】：modem_m0；【6】：modem_m1；【7】：isp_dram；【8】：isp_a7；【9】：vdec；【10】：venc；【11】：ivp；【12】：sysnoc；【13】：audio；【14】：emmc；【15】：usb。 */
        unsigned int  reserved      : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_PERFSTAT_REAL_PORT_NUM_UNION;
#endif
#define SOC_PERFSTAT_REAL_PORT_NUM_real_port_num_START  (0)
#define SOC_PERFSTAT_REAL_PORT_NUM_real_port_num_END    (15)


/*****************************************************************************
 结构名    : SOC_PERFSTAT_AXI_ADDR_MODE_UNION
 结构说明  : AXI_ADDR_MODE 寄存器结构定义。地址偏移量:0x18，初值:0x0000，宽度:32
 寄存器说明: 地址模式寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  axi_addr_mode : 1;  /* bit[0]   : 地址模式。
                                                        0：连续地址模式；
                                                        1：链表地址模式。 */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_PERFSTAT_AXI_ADDR_MODE_UNION;
#endif
#define SOC_PERFSTAT_AXI_ADDR_MODE_axi_addr_mode_START  (0)
#define SOC_PERFSTAT_AXI_ADDR_MODE_axi_addr_mode_END    (0)


/*****************************************************************************
 结构名    : SOC_PERFSTAT_SEQ_ADDR_UNION
 结构说明  : SEQ_ADDR 寄存器结构定义。地址偏移量:0x1C，初值:0x0000，宽度:32
 寄存器说明: 连续模式写地址寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: 连续模式，配置AXI写操作首地址（32Byte对齐）。 */
    } reg;
} SOC_PERFSTAT_SEQ_ADDR_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_PERFSTAT_SEQ_ADDR_LEN_UNION
 结构说明  : SEQ_ADDR_LEN 寄存器结构定义。地址偏移量:0x20，初值:0x0000，宽度:32
 寄存器说明: 连续模式写地址区间寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: 连续模式，配置AXI写操作地址区间（32Byte整数倍） */
    } reg;
} SOC_PERFSTAT_SEQ_ADDR_LEN_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_PERFSTAT_DESCRIPTOR_ADDR_UNION
 结构说明  : DESCRIPTOR_ADDR 寄存器结构定义。地址偏移量:0x24，初值:0x0000，宽度:32
 寄存器说明: 链表地址
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: 链表地址，用于AXI读操作的首地址。 */
    } reg;
} SOC_PERFSTAT_DESCRIPTOR_ADDR_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_PERFSTAT_LAST_DESC_ADDR_UNION
 结构说明  : LAST_DESC_ADDR 寄存器结构定义。地址偏移量:0x28，初值:0x0000，宽度:32
 寄存器说明: 当前链表地址寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: 用于异常处理。查询当前链表地址，用于链表出错时的debug */
    } reg;
} SOC_PERFSTAT_LAST_DESC_ADDR_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_PERFSTAT_STAT_RST_CNT_UNION
 结构说明  : STAT_RST_CNT 寄存器结构定义。地址偏移量:0x2C，初值:0x0000，宽度:32
 寄存器说明: 复位后计数寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stat_rst_cnt : 9;  /* bit[0-8] : 用于异常处理。查询软复位后计数器状态，当计数器值为0时，表示远程monitor模块处于非shift状态。 */
        unsigned int  reserved     : 23; /* bit[9-31]: 保留。 */
    } reg;
} SOC_PERFSTAT_STAT_RST_CNT_UNION;
#endif
#define SOC_PERFSTAT_STAT_RST_CNT_stat_rst_cnt_START  (0)
#define SOC_PERFSTAT_STAT_RST_CNT_stat_rst_cnt_END    (8)


/*****************************************************************************
 结构名    : SOC_PERFSTAT_INT_EN_UNION
 结构说明  : INT_EN 寄存器结构定义。地址偏移量:0x30，初值:0x0000，宽度:32
 寄存器说明: ST中断屏蔽控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sample_int_en   : 1;  /* bit[0]   : 是否允许采样结束中断：
                                                          0：禁止中断；
                                                          1：允许中断。 */
        unsigned int  overtime_int_en : 1;  /* bit[1]   : 是否允许超时中断：
                                                          0：禁止中断；
                                                          1：允许中断。 */
        unsigned int  desc_int_en     : 1;  /* bit[2]   : 是否允许链表中断：
                                                          0：禁止中断；
                                                          1：允许中断。 */
        unsigned int  desc_error_en   : 1;  /* bit[3]   : 是否允许链表错误中断：
                                                          0：禁止中断；
                                                          1：允许中断。 */
        unsigned int  reserved        : 28; /* bit[4-31]: 保留。 */
    } reg;
} SOC_PERFSTAT_INT_EN_UNION;
#endif
#define SOC_PERFSTAT_INT_EN_sample_int_en_START    (0)
#define SOC_PERFSTAT_INT_EN_sample_int_en_END      (0)
#define SOC_PERFSTAT_INT_EN_overtime_int_en_START  (1)
#define SOC_PERFSTAT_INT_EN_overtime_int_en_END    (1)
#define SOC_PERFSTAT_INT_EN_desc_int_en_START      (2)
#define SOC_PERFSTAT_INT_EN_desc_int_en_END        (2)
#define SOC_PERFSTAT_INT_EN_desc_error_en_START    (3)
#define SOC_PERFSTAT_INT_EN_desc_error_en_END      (3)


/*****************************************************************************
 结构名    : SOC_PERFSTAT_INT_CLR_UNION
 结构说明  : INT_CLR 寄存器结构定义。地址偏移量:0x34，初值:0x0000，宽度:32
 寄存器说明: ST中断清除寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sample_int_clr   : 1;  /* bit[0]   : 完成采样结束中断清除。
                                                           0：无效；
                                                           1：清除中断。 */
        unsigned int  overtime_int_clr : 1;  /* bit[1]   : 完成超时中断清除。
                                                           0：无效；
                                                           1：清除中断。 */
        unsigned int  desc_int_clr     : 1;  /* bit[2]   : 完成链表中断清除。
                                                           0：无效；
                                                           1：清除中断。 */
        unsigned int  desc_error_clr   : 1;  /* bit[3]   : 完成链表错误中断清除。
                                                           0：无效；
                                                           1：清除中断。 */
        unsigned int  reserved         : 28; /* bit[4-31]: 保留。 */
    } reg;
} SOC_PERFSTAT_INT_CLR_UNION;
#endif
#define SOC_PERFSTAT_INT_CLR_sample_int_clr_START    (0)
#define SOC_PERFSTAT_INT_CLR_sample_int_clr_END      (0)
#define SOC_PERFSTAT_INT_CLR_overtime_int_clr_START  (1)
#define SOC_PERFSTAT_INT_CLR_overtime_int_clr_END    (1)
#define SOC_PERFSTAT_INT_CLR_desc_int_clr_START      (2)
#define SOC_PERFSTAT_INT_CLR_desc_int_clr_END        (2)
#define SOC_PERFSTAT_INT_CLR_desc_error_clr_START    (3)
#define SOC_PERFSTAT_INT_CLR_desc_error_clr_END      (3)


/*****************************************************************************
 结构名    : SOC_PERFSTAT_RAW_INT_STAT_UNION
 结构说明  : RAW_INT_STAT 寄存器结构定义。地址偏移量:0x38，初值:0x0000，宽度:32
 寄存器说明: ST原始中断状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sample_raw_int_stat : 1;  /* bit[0]   : 原始采样结束中断状态。
                                                              0：无效；
                                                              1：有效。 */
        unsigned int  overtime_int_stat   : 1;  /* bit[1]   : 原始超时中断状态。
                                                              0：无效；
                                                              1：有效。 */
        unsigned int  desc_raw_int_stat   : 1;  /* bit[2]   : 原始链表中断状态。
                                                              0：无效；
                                                              1：有效。 */
        unsigned int  desc_raw_error_stat : 1;  /* bit[3]   : 原始链表错误中断状态。
                                                              0：无效；
                                                              1：有效。 */
        unsigned int  reserved            : 28; /* bit[4-31]: 保留。 */
    } reg;
} SOC_PERFSTAT_RAW_INT_STAT_UNION;
#endif
#define SOC_PERFSTAT_RAW_INT_STAT_sample_raw_int_stat_START  (0)
#define SOC_PERFSTAT_RAW_INT_STAT_sample_raw_int_stat_END    (0)
#define SOC_PERFSTAT_RAW_INT_STAT_overtime_int_stat_START    (1)
#define SOC_PERFSTAT_RAW_INT_STAT_overtime_int_stat_END      (1)
#define SOC_PERFSTAT_RAW_INT_STAT_desc_raw_int_stat_START    (2)
#define SOC_PERFSTAT_RAW_INT_STAT_desc_raw_int_stat_END      (2)
#define SOC_PERFSTAT_RAW_INT_STAT_desc_raw_error_stat_START  (3)
#define SOC_PERFSTAT_RAW_INT_STAT_desc_raw_error_stat_END    (3)


/*****************************************************************************
 结构名    : SOC_PERFSTAT_MASK_INT_STAT_UNION
 结构说明  : MASK_INT_STAT 寄存器结构定义。地址偏移量:0x3C，初值:0x0000，宽度:32
 寄存器说明: ST屏蔽后中断状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sample_mask_int_stat : 1;  /* bit[0]   : 屏蔽后采样结束中断状态。
                                                               0：无效；
                                                               1：有效。 */
        unsigned int  overtime_int_stat    : 1;  /* bit[1]   : 屏蔽后超时中断状态。
                                                               0：无效；
                                                               1：有效。 */
        unsigned int  desc_mask_int_stat   : 1;  /* bit[2]   : 屏蔽后链表中断状态。
                                                               0：无效；
                                                               1：有效。 */
        unsigned int  desc_mask_error_stat : 1;  /* bit[3]   : 屏蔽后链表错误中断状态。
                                                               0：无效；
                                                               1：有效。 */
        unsigned int  reserved             : 28; /* bit[4-31]: 保留。 */
    } reg;
} SOC_PERFSTAT_MASK_INT_STAT_UNION;
#endif
#define SOC_PERFSTAT_MASK_INT_STAT_sample_mask_int_stat_START  (0)
#define SOC_PERFSTAT_MASK_INT_STAT_sample_mask_int_stat_END    (0)
#define SOC_PERFSTAT_MASK_INT_STAT_overtime_int_stat_START     (1)
#define SOC_PERFSTAT_MASK_INT_STAT_overtime_int_stat_END       (1)
#define SOC_PERFSTAT_MASK_INT_STAT_desc_mask_int_stat_START    (2)
#define SOC_PERFSTAT_MASK_INT_STAT_desc_mask_int_stat_END      (2)
#define SOC_PERFSTAT_MASK_INT_STAT_desc_mask_error_stat_START  (3)
#define SOC_PERFSTAT_MASK_INT_STAT_desc_mask_error_stat_END    (3)


/*****************************************************************************
 结构名    : SOC_PERFSTAT_ALL_SAMPLE_NUM_UNION
 结构说明  : ALL_SAMPLE_NUM 寄存器结构定义。地址偏移量:0x40，初值:0x0000，宽度:32
 寄存器说明: 总采样次数寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: 总采样次数，表示当前已采样的次数值 */
    } reg;
} SOC_PERFSTAT_ALL_SAMPLE_NUM_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_PERFSTAT_LAST_SAMPLE_AXI_ADDR_UNION
 结构说明  : LAST_SAMPLE_AXI_ADDR 寄存器结构定义。地址偏移量:0x44，初值:0x0000，宽度:32
 寄存器说明: 采样地址寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: 该地址表示最后一笔数据写完成后的写指针地址 */
    } reg;
} SOC_PERFSTAT_LAST_SAMPLE_AXI_ADDR_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_PERFSTAT_OVERTIME_CFG_CNT_UNION
 结构说明  : OVERTIME_CFG_CNT 寄存器结构定义。地址偏移量:0x48，初值:0x0000，宽度:32
 寄存器说明: 超时计数器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: 可维可测寄存器。配置计数器值，监控该计数周期内，monitor模块和axi输出端反压信息。 */
    } reg;
} SOC_PERFSTAT_OVERTIME_CFG_CNT_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_PERFSTAT_DEBUG_FIFO_FULL_UNION
 结构说明  : DEBUG_FIFO_FULL 寄存器结构定义。地址偏移量:0x4C，初值:0x0000，宽度:32
 寄存器说明: 查询fifo满状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  debug_fifo_full : 1;  /* bit[0]   : 可维可测寄存器。配置超时计数器后使用。
                                                          当超时中断有效时，查询fifo状态。
                                                          0：fifo当前为非满状态；
                                                          1：fifo当前为满状态。 */
        unsigned int  reserved        : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_PERFSTAT_DEBUG_FIFO_FULL_UNION;
#endif
#define SOC_PERFSTAT_DEBUG_FIFO_FULL_debug_fifo_full_START  (0)
#define SOC_PERFSTAT_DEBUG_FIFO_FULL_debug_fifo_full_END    (0)


/*****************************************************************************
 结构名    : SOC_PERFSTAT_DEBUG_MONITOR_UNION
 结构说明  : DEBUG_MONITOR 寄存器结构定义。地址偏移量:0x50，初值:0x0000，宽度:32
 寄存器说明: 查询monitor阻塞寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  debug_monitor : 16; /* bit[0-15] : 可维可测寄存器。配置超时计数器后使用。
                                                         当超时中断有效时，查询各monitor是否阻塞。其中，16bit表示16个monitor端口的阻塞状态。
                                                         0：未阻塞；
                                                         1：阻塞。 */
        unsigned int  reserved      : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_PERFSTAT_DEBUG_MONITOR_UNION;
#endif
#define SOC_PERFSTAT_DEBUG_MONITOR_debug_monitor_START  (0)
#define SOC_PERFSTAT_DEBUG_MONITOR_debug_monitor_END    (15)


/*****************************************************************************
 结构名    : SOC_PERFSTAT_MONITOR_RESET_UNION
 结构说明  : MONITOR_RESET 寄存器结构定义。地址偏移量:0x54，初值:0x0000，宽度:32
 寄存器说明: monitor复位寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  monitor_reset : 1;  /* bit[0]   : 用于异常处理。读stat_rst_cnt寄存器为0后，配置minotor状态机回到IDLE状态。可重新启动。 */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_PERFSTAT_MONITOR_RESET_UNION;
#endif
#define SOC_PERFSTAT_MONITOR_RESET_monitor_reset_START  (0)
#define SOC_PERFSTAT_MONITOR_RESET_monitor_reset_END    (0)






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

#endif /* end of soc_perfstat_interface.h */
