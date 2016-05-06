/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_pmui2c_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:22:34
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_PMUI2C.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_PMUI2C_INTERFACE_H__
#define __SOC_PMUI2C_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) register_pmui2c
 ****************************************************************************/
/* 寄存器说明：I2C设备的控制寄存器。
            在I2C设备未使能时（IC_ENABLE bit[0]为0），才可配置此寄存器。
   位域定义UNION结构:  SOC_PMUI2C_IC_CON_UNION */
#define SOC_PMUI2C_IC_CON_ADDR(base)                  ((base) + (0x000))

/* 寄存器说明：I2C设备的目标地址寄存器。
            在I2C设备未使能时（IC_ENABLE bit[0]为0），才可配置此寄存器。
   位域定义UNION结构:  SOC_PMUI2C_IC_TAR_UNION */
#define SOC_PMUI2C_IC_TAR_ADDR(base)                  ((base) + (0x004))

/* 寄存器说明：I2C高速模式代码地址寄存器。
            在I2C设备未使能时（I2C_ENABLE bit[0]为0），才可配置此寄存器。
   位域定义UNION结构:  SOC_PMUI2C_IC_HS_MADDR_UNION */
#define SOC_PMUI2C_IC_HS_MADDR_ADDR(base)             ((base) + (0x00C))

/* 寄存器说明：I2C设备的数据、控制寄存器。
   位域定义UNION结构:  SOC_PMUI2C_IC_DATA_CMD_UNION */
#define SOC_PMUI2C_IC_DATA_CMD_ADDR(base)             ((base) + (0x010))

/* 寄存器说明：I2C设备的分频数值寄存器。
            配置I2C设备工作在标准速度时高电平时间由多少时钟周期组成。在I2C设备未使能时（I2C_ENABLE bit[0]为0），才可配置此寄存器。
   位域定义UNION结构:  SOC_PMUI2C_IC_SS_SCL_HCNT_UNION */
#define SOC_PMUI2C_IC_SS_SCL_HCNT_ADDR(base)          ((base) + (0x014))

/* 寄存器说明：I2C设备的分频数值寄存器。
            配置I2C设备工作在标准速度时低电平时间由多少时钟周期组成。在I2C设备未使能时（I2C_ENABLE bit[0]为0），才可配置此寄存器。
   位域定义UNION结构:  SOC_PMUI2C_IC_SS_SCL_LCNT_UNION */
#define SOC_PMUI2C_IC_SS_SCL_LCNT_ADDR(base)          ((base) + (0x018))

/* 寄存器说明：I2C设备的分频数值寄存器。
            配置I2C设备工作在快速速度时高电平时间由多少时钟周期组成。在I2C设备未使能时（I2C_ENABLE bit[0]为0），才可配置此寄存器。
   位域定义UNION结构:  SOC_PMUI2C_IC_FS_SCL_HCNT_UNION */
#define SOC_PMUI2C_IC_FS_SCL_HCNT_ADDR(base)          ((base) + (0x01C))

/* 寄存器说明：I2C设备的分频数值寄存器。
            配置I2C设备工作在快速速度时低电平时间由多少时钟周期组成。在I2C设备未使能时（I2C_ENABLE bit[0]为0），才可配置此寄存器。
   位域定义UNION结构:  SOC_PMUI2C_IC_FS_SCL_LCNT_UNION */
#define SOC_PMUI2C_IC_FS_SCL_LCNT_ADDR(base)          ((base) + (0x020))

/* 寄存器说明：I2C设备的分频数值寄存器。
            配置I2C设备工作在高速速度时高电平时间由多少时钟周期组成。在I2C设备未使能时（I2C_ENABLE bit[0]为0），才可配置此寄存器。
   位域定义UNION结构:  SOC_PMUI2C_IC_HS_SCL_HCNT_UNION */
#define SOC_PMUI2C_IC_HS_SCL_HCNT_ADDR(base)          ((base) + (0x024))

/* 寄存器说明：I2C设备的分频数值寄存器。
            配置I2C设备工作在高速速度时低电平时间由多少时钟周期组成。在I2C设备未使能时（I2C_ENABLE bit[0]为0），才可配置此寄存器。
   位域定义UNION结构:  SOC_PMUI2C_IC_HS_SCL_LCNT_UNION */
#define SOC_PMUI2C_IC_HS_SCL_LCNT_ADDR(base)          ((base) + (0x028))

/* 寄存器说明：中断状态寄存器。
   位域定义UNION结构:  SOC_PMUI2C_IC_INTR_STAT_UNION */
#define SOC_PMUI2C_IC_INTR_STAT_ADDR(base)            ((base) + (0x02C))

/* 寄存器说明：中断屏蔽寄存器。
            值“0”表示屏蔽中断，值“1”表示允许中断。
   位域定义UNION结构:  SOC_PMUI2C_IC_INTR_MASK_UNION */
#define SOC_PMUI2C_IC_INTR_MASK_ADDR(base)            ((base) + (0x030))

/* 寄存器说明：原始中断状态寄存器。
            值“0”表示未发生中断，值“1”表示发生中断。
   位域定义UNION结构:  SOC_PMUI2C_IC_RAW_INTR_STAT_UNION */
#define SOC_PMUI2C_IC_RAW_INTR_STAT_ADDR(base)        ((base) + (0x034))

/* 寄存器说明：接收FIFO阈值寄存器。
   位域定义UNION结构:  SOC_PMUI2C_IC_RX_TL_UNION */
#define SOC_PMUI2C_IC_RX_TL_ADDR(base)                ((base) + (0x038))

/* 寄存器说明：发送FIFO阈值寄存器。
   位域定义UNION结构:  SOC_PMUI2C_IC_TX_TL_UNION */
#define SOC_PMUI2C_IC_TX_TL_ADDR(base)                ((base) + (0x03C))

/* 寄存器说明：组合及独立中断清除寄存器。
   位域定义UNION结构:  SOC_PMUI2C_IC_CLR_INTR_UNION */
#define SOC_PMUI2C_IC_CLR_INTR_ADDR(base)             ((base) + (0x040))

/* 寄存器说明：RX_UNDER中断清除寄存器。
   位域定义UNION结构:  SOC_PMUI2C_IC_CLR_RX_UNDER_UNION */
#define SOC_PMUI2C_IC_CLR_RX_UNDER_ADDR(base)         ((base) + (0x044))

/* 寄存器说明：RX_OVER中断清除寄存器。
   位域定义UNION结构:  SOC_PMUI2C_IC_CLR_RX_OVER_UNION */
#define SOC_PMUI2C_IC_CLR_RX_OVER_ADDR(base)          ((base) + (0x048))

/* 寄存器说明：TX_OVER中断清除寄存器。
   位域定义UNION结构:  SOC_PMUI2C_IC_CLR_TX_OVER_UNION */
#define SOC_PMUI2C_IC_CLR_TX_OVER_ADDR(base)          ((base) + (0x04C))

/* 寄存器说明：TX_ABRT中断清除寄存器。
   位域定义UNION结构:  SOC_PMUI2C_IC_CLR_TX_ABRT_UNION */
#define SOC_PMUI2C_IC_CLR_TX_ABRT_ADDR(base)          ((base) + (0x054))

/* 寄存器说明：ACTIVITY中断清除寄存器。
   位域定义UNION结构:  SOC_PMUI2C_IC_CLR_ACTIVITY_UNION */
#define SOC_PMUI2C_IC_CLR_ACTIVITY_ADDR(base)         ((base) + (0x5C))

/* 寄存器说明：STOP_DET中断清除寄存器。
   位域定义UNION结构:  SOC_PMUI2C_IC_CLR_STOP_DET_UNION */
#define SOC_PMUI2C_IC_CLR_STOP_DET_ADDR(base)         ((base) + (0x060))

/* 寄存器说明：START_DET中断清除寄存器。
   位域定义UNION结构:  SOC_PMUI2C_IC_CLR_SART_DET_UNION */
#define SOC_PMUI2C_IC_CLR_SART_DET_ADDR(base)         ((base) + (0x064))

/* 寄存器说明：GEN_CALL中断清除寄存器。
   位域定义UNION结构:  SOC_PMUI2C_IC_CLR_GEN_CALL_UNION */
#define SOC_PMUI2C_IC_CLR_GEN_CALL_ADDR(base)         ((base) + (0x068))

/* 寄存器说明：I2C设备的使能寄存器。
   位域定义UNION结构:  SOC_PMUI2C_IC_ENABLE_UNION */
#define SOC_PMUI2C_IC_ENABLE_ADDR(base)               ((base) + (0x06C))

/* 寄存器说明：I2C设备的状态寄存器。
            指示当前传输状态和FIFO状态。
   位域定义UNION结构:  SOC_PMUI2C_IC_STATUS_UNION */
#define SOC_PMUI2C_IC_STATUS_ADDR(base)               ((base) + (0x070))

/* 寄存器说明：发送FIFO中的数据个数寄存器。
   位域定义UNION结构:  SOC_PMUI2C_IC_TXFLR_UNION */
#define SOC_PMUI2C_IC_TXFLR_ADDR(base)                ((base) + (0x074))

/* 寄存器说明：接收FIFO中的数据个数寄存器。
   位域定义UNION结构:  SOC_PMUI2C_IC_RXFLR_UNION */
#define SOC_PMUI2C_IC_RXFLR_ADDR(base)                ((base) + (0x078))

/* 寄存器说明：I2C SDA HOLD时间长度寄存器。
   位域定义UNION结构:  SOC_PMUI2C_IC_SDA_HOLD_UNION */
#define SOC_PMUI2C_IC_SDA_HOLD_ADDR(base)             ((base) + (0x07C))

/* 寄存器说明：TX_ABRT中断的中断源寄存器。
            bit[11]～bit[0]的值“0”表示复位值。
   位域定义UNION结构:  SOC_PMUI2C_IC_TX_ABRT_SOURCE_UNION */
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_ADDR(base)       ((base) + (0x080))

/* 寄存器说明：DMA接口控制寄存器。
   位域定义UNION结构:  SOC_PMUI2C_IC_DMA_CR_UNION */
#define SOC_PMUI2C_IC_DMA_CR_ADDR(base)               ((base) + (0x088))

/* 寄存器说明：发送FIFO进行DMA操作时的阈值寄存器。
   位域定义UNION结构:  SOC_PMUI2C_IC_DMA_TDLR_UNION */
#define SOC_PMUI2C_IC_DMA_TDLR_ADDR(base)             ((base) + (0x08C))

/* 寄存器说明：接收FIFO进行DMA操作时的阈值寄存器。
   位域定义UNION结构:  SOC_PMUI2C_IC_DMA_RDLR_UNION */
#define SOC_PMUI2C_IC_DMA_RDLR_ADDR(base)             ((base) + (0x090))

/* 寄存器说明：I2C SDA SETUP时间长度寄存器。
   位域定义UNION结构:  SOC_PMUI2C_IC_SDA_SETUP_UNION */
#define SOC_PMUI2C_IC_SDA_SETUP_ADDR(base)            ((base) + (0x094))

/* 寄存器说明：I2C在接收GENERAL CALL时响应ACK或NACK寄存器
   位域定义UNION结构:  SOC_PMUI2C_IC_ACK_GENERAL_CALL_UNION */
#define SOC_PMUI2C_IC_ACK_GENERAL_CALL_ADDR(base)     ((base) + (0x098))

/* 寄存器说明：I2C硬件状态寄存器，反映i2c当IC_ENABLE[0]从1到0跳变时的状态。当IC_ENABLE[0]为1时，IC_ENABLE_STATUS[2:1]为0，IC_ENABLE_STATUS[0]为1。.
            IC_ENABLE[0]为0时，IC_ENABLE_STATUS[2:1]当IC_ENABLE_STATUS[0]为0时有效。
   位域定义UNION结构:  SOC_PMUI2C_IC_ENABLE_STATUS_UNION */
#define SOC_PMUI2C_IC_ENABLE_STATUS_ADDR(base)        ((base) + (0x09C))

/* 寄存器说明：在Fast Speed模式下，可过滤毛刺长度配置寄存器，在I2C设备未使能时（IC_ENABLE bit[0]为0），才可配置此寄存器。
   位域定义UNION结构:  SOC_PMUI2C_IC_FS_SPKLEN_UNION */
#define SOC_PMUI2C_IC_FS_SPKLEN_ADDR(base)            ((base) + (0x00A0))

/* 寄存器说明：在High Speed模式下，可过滤毛刺长度配置寄存器，在I2C设备未使能时（IC_ENABLE bit[0]为0），才可配置此寄存器。
   位域定义UNION结构:  SOC_PMUI2C_IC_HS_SPKLEN_UNION */
#define SOC_PMUI2C_IC_HS_SPKLEN_ADDR(base)            ((base) + (0x00A4))

/* 寄存器说明：器件参数寄存器
   位域定义UNION结构:  SOC_PMUI2C_IC_COMP_PARAM_1_UNION */
#define SOC_PMUI2C_IC_COMP_PARAM_1_ADDR(base)         ((base) + (0x00F4))

/* 寄存器说明：器件版本寄存器
   位域定义UNION结构:  SOC_PMUI2C_IC_COMP_VERSION_UNION */
#define SOC_PMUI2C_IC_COMP_VERSION_ADDR(base)         ((base) + (0x00F8))

/* 寄存器说明：器件编号寄存器
   位域定义UNION结构:  SOC_PMUI2C_IC_COMP_TYPE_UNION */
#define SOC_PMUI2C_IC_COMP_TYPE_ADDR(base)            ((base) + (0x00FC))

/* 寄存器说明：CPU的调相地址寄存器.
   位域定义UNION结构:  SOC_PMUI2C_CPU_PHS_ADDR_UNION */
#define SOC_PMUI2C_CPU_PHS_ADDR_ADDR(base)            ((base) + (0x0100))

/* 寄存器说明：CPU的调压地址寄存器
   位域定义UNION结构:  SOC_PMUI2C_CPU_VOL_ADDR_UNION */
#define SOC_PMUI2C_CPU_VOL_ADDR_ADDR(base)            ((base) + (0x0104))

/* 寄存器说明：CPU调压/调相数据
   位域定义UNION结构:  SOC_PMUI2C_CPU_IDX_UNION */
#define SOC_PMUI2C_CPU_IDX_ADDR(base)                 ((base) + (0x0108))

/* 寄存器说明：GPU的调相地址寄存器
   位域定义UNION结构:  SOC_PMUI2C_GPU_PHS_ADDR_UNION */
#define SOC_PMUI2C_GPU_PHS_ADDR_ADDR(base)            ((base) + (0x010C))

/* 寄存器说明：GPU的调压地址寄存器
   位域定义UNION结构:  SOC_PMUI2C_GPU_VOL_ADDR_UNION */
#define SOC_PMUI2C_GPU_VOL_ADDR_ADDR(base)            ((base) + (0x0110))

/* 寄存器说明：GPU调压/调相数据
   位域定义UNION结构:  SOC_PMUI2C_GPU_IDX_UNION */
#define SOC_PMUI2C_GPU_IDX_ADDR(base)                 ((base) + (0x0114))

/* 寄存器说明：对应CPU——PMU的地址
   位域定义UNION结构:  SOC_PMUI2C_CPU_SLAVE_ADDR_UNION */
#define SOC_PMUI2C_CPU_SLAVE_ADDR_ADDR(base)          ((base) + (0x0118))

/* 寄存器说明：对应GPU——PMU的地址
   位域定义UNION结构:  SOC_PMUI2C_GPU_SLAVE_ADDR_UNION */
#define SOC_PMUI2C_GPU_SLAVE_ADDR_ADDR(base)          ((base) + (0x011C))

/* 寄存器说明：STOP信号超时计数器与PMU选择寄存器
   位域定义UNION结构:  SOC_PMUI2C_STOPTIMEOUT_UNION */
#define SOC_PMUI2C_STOPTIMEOUT_ADDR(base)             ((base) + (0x0120))

/* 寄存器说明：原始中断状态寄存器
   位域定义UNION结构:  SOC_PMUI2C_INTER_STAT_UNION */
#define SOC_PMUI2C_INTER_STAT_ADDR(base)              ((base) + (0x0124))

/* 寄存器说明：中断屏蔽寄存器
   位域定义UNION结构:  SOC_PMUI2C_INTER_MASK_UNION */
#define SOC_PMUI2C_INTER_MASK_ADDR(base)              ((base) + (0x0128))

/* 寄存器说明：中断状态寄存器
   位域定义UNION结构:  SOC_PMUI2C_INTER_UNION */
#define SOC_PMUI2C_INTER_ADDR(base)                   ((base) + (0x012C))

/* 寄存器说明：清除中断1寄存器
   位域定义UNION结构:  SOC_PMUI2C_CLR_OVERTIME_UNION */
#define SOC_PMUI2C_CLR_OVERTIME_ADDR(base)            ((base) + (0x0130))

/* 寄存器说明：清除中断0寄存器
   位域定义UNION结构:  SOC_PMUI2C_CLR_IMPACT_UNION */
#define SOC_PMUI2C_CLR_IMPACT_ADDR(base)              ((base) + (0x0134))

/* 寄存器说明：DEBUG标志寄存器
   位域定义UNION结构:  SOC_PMUI2C_DEBUG_UNION */
#define SOC_PMUI2C_DEBUG_ADDR(base)                   ((base) + (0x0138))

/* 寄存器说明：PMUI2C状态寄存器
   位域定义UNION结构:  SOC_PMUI2C_PMUI2CSTATE_UNION */
#define SOC_PMUI2C_PMUI2CSTATE_ADDR(base)             ((base) + (0x013C))

/* 寄存器说明：PMUI2C hold/idle模式选择寄存器
   位域定义UNION结构:  SOC_PMUI2C_HOLD_IDLE_UNION */
#define SOC_PMUI2C_HOLD_IDLE_ADDR(base)               ((base) + (0x0140))

/* 寄存器说明：PMUI2C 单/双Slave选择寄存器
   位域定义UNION结构:  SOC_PMUI2C_SLAVE_CHOSE_UNION */
#define SOC_PMUI2C_SLAVE_CHOSE_ADDR(base)             ((base) + (0x0144))





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
                     (1/1) register_pmui2c
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_PMUI2C_IC_CON_UNION
 结构说明  : IC_CON 寄存器结构定义。地址偏移量:0x000，初值:0x007F，宽度:16
 寄存器说明: I2C设备的控制寄存器。
            在I2C设备未使能时（IC_ENABLE bit[0]为0），才可配置此寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  ic_master_mode      : 1;  /* bit[0]   : 主设备功能使能。如果该bit为1，则bit 6 也需要为1。
                                                                0：不使能；
                                                                1：使能。 */
        unsigned short  ic_max_speed_mode   : 2;  /* bit[1-2] : I2C设备的操作速度。
                                                                00：非法，写“00”被认为是配置为快速模式；
                                                                01：标准速度；
                                                                10：快速速度；
                                                                11：高速速度。 */
        unsigned short  reserved_0          : 1;  /* bit[3]   : 保留。 */
        unsigned short  ic_10bitaddr_master : 1;  /* bit[4]   : 作为主设备时发出的地址位数。
                                                                0：7位地址；
                                                                1：10位地址。 */
        unsigned short  ic_restart_en       : 1;  /* bit[5]   : 是否允许主设备产生“重新开始”条件。
                                                                0：不允许；
                                                                1：允许。 */
        unsigned short  ic_slave_disable    : 1;  /* bit[6]   : 此位只能置为“1”。 */
        unsigned short  reserved_1          : 9;  /* bit[7-15]: 保留。 */
    } reg;
} SOC_PMUI2C_IC_CON_UNION;
#endif
#define SOC_PMUI2C_IC_CON_ic_master_mode_START       (0)
#define SOC_PMUI2C_IC_CON_ic_master_mode_END         (0)
#define SOC_PMUI2C_IC_CON_ic_max_speed_mode_START    (1)
#define SOC_PMUI2C_IC_CON_ic_max_speed_mode_END      (2)
#define SOC_PMUI2C_IC_CON_ic_10bitaddr_master_START  (4)
#define SOC_PMUI2C_IC_CON_ic_10bitaddr_master_END    (4)
#define SOC_PMUI2C_IC_CON_ic_restart_en_START        (5)
#define SOC_PMUI2C_IC_CON_ic_restart_en_END          (5)
#define SOC_PMUI2C_IC_CON_ic_slave_disable_START     (6)
#define SOC_PMUI2C_IC_CON_ic_slave_disable_END       (6)


/*****************************************************************************
 结构名    : SOC_PMUI2C_IC_TAR_UNION
 结构说明  : IC_TAR 寄存器结构定义。地址偏移量:0x004，初值:0x0055，宽度:16
 寄存器说明: I2C设备的目标地址寄存器。
            在I2C设备未使能时（IC_ENABLE bit[0]为0），才可配置此寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  i2c_tar     : 10; /* bit[0-9]  : 作为主设备时要访问的从设备地址。 */
        unsigned short  gc_or_start : 1;  /* bit[10]   : 当[special]为1时执行的功能。
                                                         0：General call；
                                                         1：Start byte。 */
        unsigned short  special     : 1;  /* bit[11]   : 是否执行general call和start byte功能。
                                                         0：不执行；
                                                         1：执行。 */
        unsigned short  reserved    : 4;  /* bit[12-15]: 保留。 */
    } reg;
} SOC_PMUI2C_IC_TAR_UNION;
#endif
#define SOC_PMUI2C_IC_TAR_i2c_tar_START      (0)
#define SOC_PMUI2C_IC_TAR_i2c_tar_END        (9)
#define SOC_PMUI2C_IC_TAR_gc_or_start_START  (10)
#define SOC_PMUI2C_IC_TAR_gc_or_start_END    (10)
#define SOC_PMUI2C_IC_TAR_special_START      (11)
#define SOC_PMUI2C_IC_TAR_special_END        (11)


/*****************************************************************************
 结构名    : SOC_PMUI2C_IC_HS_MADDR_UNION
 结构说明  : IC_HS_MADDR 寄存器结构定义。地址偏移量:0x00C，初值:0x0001，宽度:16
 寄存器说明: I2C高速模式代码地址寄存器。
            在I2C设备未使能时（I2C_ENABLE bit[0]为0），才可配置此寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  i2_hs_mar : 3;  /* bit[0-2] : i2c HS Mater Mode Code Address。 */
        unsigned short  reserved  : 13; /* bit[3-15]: 保留。 */
    } reg;
} SOC_PMUI2C_IC_HS_MADDR_UNION;
#endif
#define SOC_PMUI2C_IC_HS_MADDR_i2_hs_mar_START  (0)
#define SOC_PMUI2C_IC_HS_MADDR_i2_hs_mar_END    (2)


/*****************************************************************************
 结构名    : SOC_PMUI2C_IC_DATA_CMD_UNION
 结构说明  : IC_DATA_CMD 寄存器结构定义。地址偏移量:0x010，初值:0x0000，宽度:16
 寄存器说明: I2C设备的数据、控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  dat      : 8;  /* bit[0-7]  : 将要在I2C总线上发送/接收的数据。
                                                      读时读出在I2C总线上接收的数据。
                                                      写时把写入的数据发送到I2C总线上去。 */
        unsigned short  cmd      : 1;  /* bit[8]    : 读/写控制位。
                                                      0：写，表示I2C设备将要向I2C总线发送数据。此时低8bit是I2C设备要向I2C总线发送的数据；
                                                      1：读，表示I2C设备将要从I2C总线读回数据。 */
        unsigned short  stop     : 1;  /* bit[9]    : 该bit控制在1 byte数据被发送或接收后是否产生stop。
                                                      0：在该byte之后不发送stop；
                                                      1：在该byte之后发送stop； */
        unsigned short  restart  : 1;  /* bit[10]   : 该bit控制在1 byte数据被发送或接收前是否发送restart。
                                                      0：如果ic_restart_en为1，则只有在前面命令的传输方向发生改变的时候才发送restart信号；如果如果ic_restart_en为0，在start之后发送stop。
                                                      1：如果ic_restart_en为1，则无论前面命令的传输方向是否发生改变，都在数据被发送或接收之后发送restart信号；如果如果ic_restart_en为0，在在start之后发送stop。 */
        unsigned short  reserved : 5;  /* bit[11-15]: 保留。 */
    } reg;
} SOC_PMUI2C_IC_DATA_CMD_UNION;
#endif
#define SOC_PMUI2C_IC_DATA_CMD_dat_START       (0)
#define SOC_PMUI2C_IC_DATA_CMD_dat_END         (7)
#define SOC_PMUI2C_IC_DATA_CMD_cmd_START       (8)
#define SOC_PMUI2C_IC_DATA_CMD_cmd_END         (8)
#define SOC_PMUI2C_IC_DATA_CMD_stop_START      (9)
#define SOC_PMUI2C_IC_DATA_CMD_stop_END        (9)
#define SOC_PMUI2C_IC_DATA_CMD_restart_START   (10)
#define SOC_PMUI2C_IC_DATA_CMD_restart_END     (10)


/*****************************************************************************
 结构名    : SOC_PMUI2C_IC_SS_SCL_HCNT_UNION
 结构说明  : IC_SS_SCL_HCNT 寄存器结构定义。地址偏移量:0x014，初值:0x0190，宽度:16
 寄存器说明: I2C设备的分频数值寄存器。
            配置I2C设备工作在标准速度时高电平时间由多少时钟周期组成。在I2C设备未使能时（I2C_ENABLE bit[0]为0），才可配置此寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  ic_ss_scl_hcnt : 16; /* bit[0-15]: 标准速度下的SCL信号高电平的时钟周期数（ic_clk周期）。
                                                           此寄存器的最小值为6，写入小于6的值时会被认为是6。 */
    } reg;
} SOC_PMUI2C_IC_SS_SCL_HCNT_UNION;
#endif
#define SOC_PMUI2C_IC_SS_SCL_HCNT_ic_ss_scl_hcnt_START  (0)
#define SOC_PMUI2C_IC_SS_SCL_HCNT_ic_ss_scl_hcnt_END    (15)


/*****************************************************************************
 结构名    : SOC_PMUI2C_IC_SS_SCL_LCNT_UNION
 结构说明  : IC_SS_SCL_LCNT 寄存器结构定义。地址偏移量:0x018，初值:0x01D6，宽度:16
 寄存器说明: I2C设备的分频数值寄存器。
            配置I2C设备工作在标准速度时低电平时间由多少时钟周期组成。在I2C设备未使能时（I2C_ENABLE bit[0]为0），才可配置此寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  ic_ss_scl_lcnt : 16; /* bit[0-15]: 标准速度下的SCL信号低电平的时钟周期数（ic_clk周期）。
                                                           此寄存器的最小值为8，写入小于8的值时会被认为是8。 */
    } reg;
} SOC_PMUI2C_IC_SS_SCL_LCNT_UNION;
#endif
#define SOC_PMUI2C_IC_SS_SCL_LCNT_ic_ss_scl_lcnt_START  (0)
#define SOC_PMUI2C_IC_SS_SCL_LCNT_ic_ss_scl_lcnt_END    (15)


/*****************************************************************************
 结构名    : SOC_PMUI2C_IC_FS_SCL_HCNT_UNION
 结构说明  : IC_FS_SCL_HCNT 寄存器结构定义。地址偏移量:0x01C，初值:0x003C，宽度:16
 寄存器说明: I2C设备的分频数值寄存器。
            配置I2C设备工作在快速速度时高电平时间由多少时钟周期组成。在I2C设备未使能时（I2C_ENABLE bit[0]为0），才可配置此寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  ic_fs_scl_hcnt : 16; /* bit[0-15]: 快速速度下的SCL信号高电平的时钟周期数（ic_clk周期）。
                                                           此寄存器的最小值为6，写入小于6的值时会被认为是6。 */
    } reg;
} SOC_PMUI2C_IC_FS_SCL_HCNT_UNION;
#endif
#define SOC_PMUI2C_IC_FS_SCL_HCNT_ic_fs_scl_hcnt_START  (0)
#define SOC_PMUI2C_IC_FS_SCL_HCNT_ic_fs_scl_hcnt_END    (15)


/*****************************************************************************
 结构名    : SOC_PMUI2C_IC_FS_SCL_LCNT_UNION
 结构说明  : IC_FS_SCL_LCNT 寄存器结构定义。地址偏移量:0x020，初值:0x0082，宽度:16
 寄存器说明: I2C设备的分频数值寄存器。
            配置I2C设备工作在快速速度时低电平时间由多少时钟周期组成。在I2C设备未使能时（I2C_ENABLE bit[0]为0），才可配置此寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  ic_fs_scl_lcnt : 16; /* bit[0-15]: 快速速度下的SCL信号低电平的时钟周期数（ic_clk周期）。
                                                           此寄存器的最小值为8，写入小于8的值时会被认为是8。 */
    } reg;
} SOC_PMUI2C_IC_FS_SCL_LCNT_UNION;
#endif
#define SOC_PMUI2C_IC_FS_SCL_LCNT_ic_fs_scl_lcnt_START  (0)
#define SOC_PMUI2C_IC_FS_SCL_LCNT_ic_fs_scl_lcnt_END    (15)


/*****************************************************************************
 结构名    : SOC_PMUI2C_IC_HS_SCL_HCNT_UNION
 结构说明  : IC_HS_SCL_HCNT 寄存器结构定义。地址偏移量:0x024，初值:0x0006，宽度:16
 寄存器说明: I2C设备的分频数值寄存器。
            配置I2C设备工作在高速速度时高电平时间由多少时钟周期组成。在I2C设备未使能时（I2C_ENABLE bit[0]为0），才可配置此寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  ic_hs_scl_hcnt : 16; /* bit[0-15]: 高速速度下的SCL信号高电平的时钟周期数（ic_clk周期）。
                                                           此寄存器的最小值为6，写入小于6的值时会被认为是6。 */
    } reg;
} SOC_PMUI2C_IC_HS_SCL_HCNT_UNION;
#endif
#define SOC_PMUI2C_IC_HS_SCL_HCNT_ic_hs_scl_hcnt_START  (0)
#define SOC_PMUI2C_IC_HS_SCL_HCNT_ic_hs_scl_hcnt_END    (15)


/*****************************************************************************
 结构名    : SOC_PMUI2C_IC_HS_SCL_LCNT_UNION
 结构说明  : IC_HS_SCL_LCNT 寄存器结构定义。地址偏移量:0x028，初值:0x0010，宽度:16
 寄存器说明: I2C设备的分频数值寄存器。
            配置I2C设备工作在高速速度时低电平时间由多少时钟周期组成。在I2C设备未使能时（I2C_ENABLE bit[0]为0），才可配置此寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  ic_hs_scl_lcnt : 16; /* bit[0-15]: 高速速度下的SCL信号低电平的时钟周期数（ic_clk周期）。
                                                           此寄存器的最小值为8，写入小于8的值时会被认为是8。 */
    } reg;
} SOC_PMUI2C_IC_HS_SCL_LCNT_UNION;
#endif
#define SOC_PMUI2C_IC_HS_SCL_LCNT_ic_hs_scl_lcnt_START  (0)
#define SOC_PMUI2C_IC_HS_SCL_LCNT_ic_hs_scl_lcnt_END    (15)


/*****************************************************************************
 结构名    : SOC_PMUI2C_IC_INTR_STAT_UNION
 结构说明  : IC_INTR_STAT 寄存器结构定义。地址偏移量:0x02C，初值:0x0000，宽度:16
 寄存器说明: 中断状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  r_rx_under  : 1;  /* bit[0]    : 当CPU读空的RX_FIFO时，此位被设置为1。
                                                         0：CPU读RX_FIFO时RX_FIFO未空；
                                                         1：CPU读RX_FIFO时RX_FIFO已空； */
        unsigned short  r_rx_over   : 1;  /* bit[1]    : 接收FIFO溢出标志。
                                                         0：未溢出；
                                                         1：溢出。 */
        unsigned short  r_rx_full   : 1;  /* bit[2]    : 接收FIFO中数据是否到达或大于阈值。
                                                         0：小于阈值；
                                                         1：等于或大于阈值。 */
        unsigned short  r_tx_over   : 1;  /* bit[3]    : 发送FIFO溢出标志。
                                                         0：未溢出；
                                                         1：溢出。 */
        unsigned short  r_tx_empty  : 1;  /* bit[4]    : 发送FIFO中数据是否到达或低于阈值。
                                                         0：大于阈值；
                                                         1：等于或低于阈值。 */
        unsigned short  reserved_0  : 1;  /* bit[5]    : 保留。 */
        unsigned short  r_tx_abrt   : 1;  /* bit[6]    : TX_ABRT中断。
                                                         中断源请参见寄存器I2C_TX_ABRT_SOURCE。 */
        unsigned short  reserved_1  : 1;  /* bit[7]    : 保留。 */
        unsigned short  r_activity  : 1;  /* bit[8]    : I2C的activity状态。
                                                         0：空闲；
                                                         1：忙。 */
        unsigned short  r_stop_det  : 1;  /* bit[9]    : 在I2C总线上是否发生了停止条件。
                                                         0：未发生；
                                                         1：已发生。 */
        unsigned short  r_start_det : 1;  /* bit[10]   : 在I2C总线上是否发生了start或restart条件。
                                                         0：未发生；
                                                         1：已发生。 */
        unsigned short  r_gen_call  : 1;  /* bit[11]   : 一次GENERAL CALL请求被接收状态。
                                                         0：未接收；
                                                         1：已接收。
                                                         I2C将接收到的数据放在接收端缓冲区中。 */
        unsigned short  reserved_2  : 4;  /* bit[12-15]: 保留。 */
    } reg;
} SOC_PMUI2C_IC_INTR_STAT_UNION;
#endif
#define SOC_PMUI2C_IC_INTR_STAT_r_rx_under_START   (0)
#define SOC_PMUI2C_IC_INTR_STAT_r_rx_under_END     (0)
#define SOC_PMUI2C_IC_INTR_STAT_r_rx_over_START    (1)
#define SOC_PMUI2C_IC_INTR_STAT_r_rx_over_END      (1)
#define SOC_PMUI2C_IC_INTR_STAT_r_rx_full_START    (2)
#define SOC_PMUI2C_IC_INTR_STAT_r_rx_full_END      (2)
#define SOC_PMUI2C_IC_INTR_STAT_r_tx_over_START    (3)
#define SOC_PMUI2C_IC_INTR_STAT_r_tx_over_END      (3)
#define SOC_PMUI2C_IC_INTR_STAT_r_tx_empty_START   (4)
#define SOC_PMUI2C_IC_INTR_STAT_r_tx_empty_END     (4)
#define SOC_PMUI2C_IC_INTR_STAT_r_tx_abrt_START    (6)
#define SOC_PMUI2C_IC_INTR_STAT_r_tx_abrt_END      (6)
#define SOC_PMUI2C_IC_INTR_STAT_r_activity_START   (8)
#define SOC_PMUI2C_IC_INTR_STAT_r_activity_END     (8)
#define SOC_PMUI2C_IC_INTR_STAT_r_stop_det_START   (9)
#define SOC_PMUI2C_IC_INTR_STAT_r_stop_det_END     (9)
#define SOC_PMUI2C_IC_INTR_STAT_r_start_det_START  (10)
#define SOC_PMUI2C_IC_INTR_STAT_r_start_det_END    (10)
#define SOC_PMUI2C_IC_INTR_STAT_r_gen_call_START   (11)
#define SOC_PMUI2C_IC_INTR_STAT_r_gen_call_END     (11)


/*****************************************************************************
 结构名    : SOC_PMUI2C_IC_INTR_MASK_UNION
 结构说明  : IC_INTR_MASK 寄存器结构定义。地址偏移量:0x030，初值:0x08FF，宽度:16
 寄存器说明: 中断屏蔽寄存器。
            值“0”表示屏蔽中断，值“1”表示允许中断。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  m_rx_under  : 1;  /* bit[0]    : rx_under中断屏蔽 */
        unsigned short  m_rx_over   : 1;  /* bit[1]    : rx_over中断屏蔽 */
        unsigned short  m_rx_full   : 1;  /* bit[2]    : rx_full中断屏蔽 */
        unsigned short  m_tx_over   : 1;  /* bit[3]    : tx_over中断屏蔽 */
        unsigned short  m_tx_empty  : 1;  /* bit[4]    : tx_empty中断屏蔽 */
        unsigned short  reserved_0  : 1;  /* bit[5]    : 保留。 */
        unsigned short  m_tx_abrt   : 1;  /* bit[6]    : tx_abrt中断屏蔽 */
        unsigned short  reserved_1  : 1;  /* bit[7]    : 保留。 */
        unsigned short  m_activity  : 1;  /* bit[8]    : activity中断屏蔽 */
        unsigned short  m_stop_det  : 1;  /* bit[9]    : stop_det中断屏蔽 */
        unsigned short  m_start_det : 1;  /* bit[10]   : start_det中断屏蔽 */
        unsigned short  m_gen_call  : 1;  /* bit[11]   : gen_call中断屏蔽 */
        unsigned short  reserved_2  : 4;  /* bit[12-15]: 保留。 */
    } reg;
} SOC_PMUI2C_IC_INTR_MASK_UNION;
#endif
#define SOC_PMUI2C_IC_INTR_MASK_m_rx_under_START   (0)
#define SOC_PMUI2C_IC_INTR_MASK_m_rx_under_END     (0)
#define SOC_PMUI2C_IC_INTR_MASK_m_rx_over_START    (1)
#define SOC_PMUI2C_IC_INTR_MASK_m_rx_over_END      (1)
#define SOC_PMUI2C_IC_INTR_MASK_m_rx_full_START    (2)
#define SOC_PMUI2C_IC_INTR_MASK_m_rx_full_END      (2)
#define SOC_PMUI2C_IC_INTR_MASK_m_tx_over_START    (3)
#define SOC_PMUI2C_IC_INTR_MASK_m_tx_over_END      (3)
#define SOC_PMUI2C_IC_INTR_MASK_m_tx_empty_START   (4)
#define SOC_PMUI2C_IC_INTR_MASK_m_tx_empty_END     (4)
#define SOC_PMUI2C_IC_INTR_MASK_m_tx_abrt_START    (6)
#define SOC_PMUI2C_IC_INTR_MASK_m_tx_abrt_END      (6)
#define SOC_PMUI2C_IC_INTR_MASK_m_activity_START   (8)
#define SOC_PMUI2C_IC_INTR_MASK_m_activity_END     (8)
#define SOC_PMUI2C_IC_INTR_MASK_m_stop_det_START   (9)
#define SOC_PMUI2C_IC_INTR_MASK_m_stop_det_END     (9)
#define SOC_PMUI2C_IC_INTR_MASK_m_start_det_START  (10)
#define SOC_PMUI2C_IC_INTR_MASK_m_start_det_END    (10)
#define SOC_PMUI2C_IC_INTR_MASK_m_gen_call_START   (11)
#define SOC_PMUI2C_IC_INTR_MASK_m_gen_call_END     (11)


/*****************************************************************************
 结构名    : SOC_PMUI2C_IC_RAW_INTR_STAT_UNION
 结构说明  : IC_RAW_INTR_STAT 寄存器结构定义。地址偏移量:0x034，初值:0x0000，宽度:16
 寄存器说明: 原始中断状态寄存器。
            值“0”表示未发生中断，值“1”表示发生中断。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  r_rx_under  : 1;  /* bit[0]    : rx_under原始中断状态 */
        unsigned short  r_rx_over   : 1;  /* bit[1]    : rx_over原始中断状态 */
        unsigned short  r_rx_full   : 1;  /* bit[2]    : rx_full原始中断状态 */
        unsigned short  r_tx_over   : 1;  /* bit[3]    : tx_over原始中断状态 */
        unsigned short  r_tx_empty  : 1;  /* bit[4]    : tx_empty原始中断状态 */
        unsigned short  reserved_0  : 1;  /* bit[5]    : 保留。 */
        unsigned short  r_tx_abrt   : 1;  /* bit[6]    : tx_abrt原始中断状态 */
        unsigned short  reserved_1  : 1;  /* bit[7]    : 保留。 */
        unsigned short  r_activity  : 1;  /* bit[8]    : activity原始中断状态 */
        unsigned short  r_stop_det  : 1;  /* bit[9]    : stop_det原始中断状态 */
        unsigned short  r_start_det : 1;  /* bit[10]   : start_det原始中断状态 */
        unsigned short  r_gen_call  : 1;  /* bit[11]   : gen_call原始中断状态 */
        unsigned short  reserved_2  : 4;  /* bit[12-15]: 保留。 */
    } reg;
} SOC_PMUI2C_IC_RAW_INTR_STAT_UNION;
#endif
#define SOC_PMUI2C_IC_RAW_INTR_STAT_r_rx_under_START   (0)
#define SOC_PMUI2C_IC_RAW_INTR_STAT_r_rx_under_END     (0)
#define SOC_PMUI2C_IC_RAW_INTR_STAT_r_rx_over_START    (1)
#define SOC_PMUI2C_IC_RAW_INTR_STAT_r_rx_over_END      (1)
#define SOC_PMUI2C_IC_RAW_INTR_STAT_r_rx_full_START    (2)
#define SOC_PMUI2C_IC_RAW_INTR_STAT_r_rx_full_END      (2)
#define SOC_PMUI2C_IC_RAW_INTR_STAT_r_tx_over_START    (3)
#define SOC_PMUI2C_IC_RAW_INTR_STAT_r_tx_over_END      (3)
#define SOC_PMUI2C_IC_RAW_INTR_STAT_r_tx_empty_START   (4)
#define SOC_PMUI2C_IC_RAW_INTR_STAT_r_tx_empty_END     (4)
#define SOC_PMUI2C_IC_RAW_INTR_STAT_r_tx_abrt_START    (6)
#define SOC_PMUI2C_IC_RAW_INTR_STAT_r_tx_abrt_END      (6)
#define SOC_PMUI2C_IC_RAW_INTR_STAT_r_activity_START   (8)
#define SOC_PMUI2C_IC_RAW_INTR_STAT_r_activity_END     (8)
#define SOC_PMUI2C_IC_RAW_INTR_STAT_r_stop_det_START   (9)
#define SOC_PMUI2C_IC_RAW_INTR_STAT_r_stop_det_END     (9)
#define SOC_PMUI2C_IC_RAW_INTR_STAT_r_start_det_START  (10)
#define SOC_PMUI2C_IC_RAW_INTR_STAT_r_start_det_END    (10)
#define SOC_PMUI2C_IC_RAW_INTR_STAT_r_gen_call_START   (11)
#define SOC_PMUI2C_IC_RAW_INTR_STAT_r_gen_call_END     (11)


/*****************************************************************************
 结构名    : SOC_PMUI2C_IC_RX_TL_UNION
 结构说明  : IC_RX_TL 寄存器结构定义。地址偏移量:0x038，初值:0x0003，宽度:16
 寄存器说明: 接收FIFO阈值寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  rx_tl    : 8;  /* bit[0-7] : 接收FIFO阈值，实际值等于配置值加1。当配置值超过FIFO深度（64）时实际值被认为是64。 */
        unsigned short  reserved : 8;  /* bit[8-15]: 保留。 */
    } reg;
} SOC_PMUI2C_IC_RX_TL_UNION;
#endif
#define SOC_PMUI2C_IC_RX_TL_rx_tl_START     (0)
#define SOC_PMUI2C_IC_RX_TL_rx_tl_END       (7)


/*****************************************************************************
 结构名    : SOC_PMUI2C_IC_TX_TL_UNION
 结构说明  : IC_TX_TL 寄存器结构定义。地址偏移量:0x03C，初值:0x0003，宽度:16
 寄存器说明: 发送FIFO阈值寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  tx_tl    : 8;  /* bit[0-7] : 发送FIFO阈值，实际值等于配置值加1。当配置值超过FIFO深度（64）时实际值被认为是64。 */
        unsigned short  reserved : 8;  /* bit[8-15]: 保留。 */
    } reg;
} SOC_PMUI2C_IC_TX_TL_UNION;
#endif
#define SOC_PMUI2C_IC_TX_TL_tx_tl_START     (0)
#define SOC_PMUI2C_IC_TX_TL_tx_tl_END       (7)


/*****************************************************************************
 结构名    : SOC_PMUI2C_IC_CLR_INTR_UNION
 结构说明  : IC_CLR_INTR 寄存器结构定义。地址偏移量:0x040，初值:0x0000，宽度:16
 寄存器说明: 组合及独立中断清除寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  clr_intr : 1;  /* bit[0]   : 读此寄存器，清所有组合中断和独立中断，以及寄存器I2C_TX_ABRT_SOURCE。
                                                     注意：寄存器I2C_TX_ABRT_SOURCE bit[9]及其引发的组合中断无法被清除。 */
        unsigned short  reserved : 15; /* bit[1-15]: 保留。 */
    } reg;
} SOC_PMUI2C_IC_CLR_INTR_UNION;
#endif
#define SOC_PMUI2C_IC_CLR_INTR_clr_intr_START  (0)
#define SOC_PMUI2C_IC_CLR_INTR_clr_intr_END    (0)


/*****************************************************************************
 结构名    : SOC_PMUI2C_IC_CLR_RX_UNDER_UNION
 结构说明  : IC_CLR_RX_UNDER 寄存器结构定义。地址偏移量:0x044，初值:0x0000，宽度:16
 寄存器说明: RX_UNDER中断清除寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  clr_intr : 1;  /* bit[0]   : 读此寄存器，清RX_UNDER中断。 */
        unsigned short  reserved : 15; /* bit[1-15]: 保留。 */
    } reg;
} SOC_PMUI2C_IC_CLR_RX_UNDER_UNION;
#endif
#define SOC_PMUI2C_IC_CLR_RX_UNDER_clr_intr_START  (0)
#define SOC_PMUI2C_IC_CLR_RX_UNDER_clr_intr_END    (0)


/*****************************************************************************
 结构名    : SOC_PMUI2C_IC_CLR_RX_OVER_UNION
 结构说明  : IC_CLR_RX_OVER 寄存器结构定义。地址偏移量:0x048，初值:0x0000，宽度:16
 寄存器说明: RX_OVER中断清除寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  clr_rx_under : 1;  /* bit[0]   : 读此寄存器，清RX_OVER中断。 */
        unsigned short  reserved     : 15; /* bit[1-15]: 保留。 */
    } reg;
} SOC_PMUI2C_IC_CLR_RX_OVER_UNION;
#endif
#define SOC_PMUI2C_IC_CLR_RX_OVER_clr_rx_under_START  (0)
#define SOC_PMUI2C_IC_CLR_RX_OVER_clr_rx_under_END    (0)


/*****************************************************************************
 结构名    : SOC_PMUI2C_IC_CLR_TX_OVER_UNION
 结构说明  : IC_CLR_TX_OVER 寄存器结构定义。地址偏移量:0x04C，初值:0x0000，宽度:16
 寄存器说明: TX_OVER中断清除寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  clr_tx_over : 1;  /* bit[0]   : 读此寄存器，清TX_OVER中断。 */
        unsigned short  reserved    : 15; /* bit[1-15]: 保留。 */
    } reg;
} SOC_PMUI2C_IC_CLR_TX_OVER_UNION;
#endif
#define SOC_PMUI2C_IC_CLR_TX_OVER_clr_tx_over_START  (0)
#define SOC_PMUI2C_IC_CLR_TX_OVER_clr_tx_over_END    (0)


/*****************************************************************************
 结构名    : SOC_PMUI2C_IC_CLR_TX_ABRT_UNION
 结构说明  : IC_CLR_TX_ABRT 寄存器结构定义。地址偏移量:0x054，初值:0x0000，宽度:16
 寄存器说明: TX_ABRT中断清除寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  clr_tx_abrt : 1;  /* bit[0]   : 读此寄存器，清TX_ABRT中断和寄存器IC_TX_ABRT_SOURCE。 */
        unsigned short  reserved    : 15; /* bit[1-15]: 保留。 */
    } reg;
} SOC_PMUI2C_IC_CLR_TX_ABRT_UNION;
#endif
#define SOC_PMUI2C_IC_CLR_TX_ABRT_clr_tx_abrt_START  (0)
#define SOC_PMUI2C_IC_CLR_TX_ABRT_clr_tx_abrt_END    (0)


/*****************************************************************************
 结构名    : SOC_PMUI2C_IC_CLR_ACTIVITY_UNION
 结构说明  : IC_CLR_ACTIVITY 寄存器结构定义。地址偏移量:0x5C，初值:0x0000，宽度:16
 寄存器说明: ACTIVITY中断清除寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  clr_activity : 1;  /* bit[0]   : 读此寄存器可获得ACTIVITY中断状态，硬件自动清零。 */
        unsigned short  reserved     : 15; /* bit[1-15]: 保留。 */
    } reg;
} SOC_PMUI2C_IC_CLR_ACTIVITY_UNION;
#endif
#define SOC_PMUI2C_IC_CLR_ACTIVITY_clr_activity_START  (0)
#define SOC_PMUI2C_IC_CLR_ACTIVITY_clr_activity_END    (0)


/*****************************************************************************
 结构名    : SOC_PMUI2C_IC_CLR_STOP_DET_UNION
 结构说明  : IC_CLR_STOP_DET 寄存器结构定义。地址偏移量:0x060，初值:0x0000，宽度:16
 寄存器说明: STOP_DET中断清除寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  clr_stop_det : 1;  /* bit[0]   : 读此寄存器，清STOP_DET中断。 */
        unsigned short  reserved     : 15; /* bit[1-15]: 保留。 */
    } reg;
} SOC_PMUI2C_IC_CLR_STOP_DET_UNION;
#endif
#define SOC_PMUI2C_IC_CLR_STOP_DET_clr_stop_det_START  (0)
#define SOC_PMUI2C_IC_CLR_STOP_DET_clr_stop_det_END    (0)


/*****************************************************************************
 结构名    : SOC_PMUI2C_IC_CLR_SART_DET_UNION
 结构说明  : IC_CLR_SART_DET 寄存器结构定义。地址偏移量:0x064，初值:0x0000，宽度:16
 寄存器说明: START_DET中断清除寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  clr_start_det : 1;  /* bit[0]   : 读此寄存器，清START_DET中断。 */
        unsigned short  reserved      : 15; /* bit[1-15]: 保留。 */
    } reg;
} SOC_PMUI2C_IC_CLR_SART_DET_UNION;
#endif
#define SOC_PMUI2C_IC_CLR_SART_DET_clr_start_det_START  (0)
#define SOC_PMUI2C_IC_CLR_SART_DET_clr_start_det_END    (0)


/*****************************************************************************
 结构名    : SOC_PMUI2C_IC_CLR_GEN_CALL_UNION
 结构说明  : IC_CLR_GEN_CALL 寄存器结构定义。地址偏移量:0x068，初值:0x0000，宽度:16
 寄存器说明: GEN_CALL中断清除寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  clr_gen_call : 1;  /* bit[0]   : 读此寄存器，清GEN_CALL中断。 */
        unsigned short  reserved     : 15; /* bit[1-15]: 保留。 */
    } reg;
} SOC_PMUI2C_IC_CLR_GEN_CALL_UNION;
#endif
#define SOC_PMUI2C_IC_CLR_GEN_CALL_clr_gen_call_START  (0)
#define SOC_PMUI2C_IC_CLR_GEN_CALL_clr_gen_call_END    (0)


/*****************************************************************************
 结构名    : SOC_PMUI2C_IC_ENABLE_UNION
 结构说明  : IC_ENABLE 寄存器结构定义。地址偏移量:0x06C，初值:0x0000，宽度:16
 寄存器说明: I2C设备的使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short      value;
    struct
    {
        unsigned short  enable   : 1;  /* bit[0]   : 使能I2C设备。
                                                     0：分以下两种情况。
                                                     l 处于发送状态时，在完成当前字节发送后停止，同时删除发送FIFO的数据。
                                                     l 处于接收状态时，在接收完当前字节后不响应这次传输。
                                                     1：使I2C设备进入工作状态，写“0”后可对其进行配置。 */
        unsigned short  abort    : 1;  /* bit[1]   : abort I2C设备。
                                                     0：abort未触发或已结束。
                                                     1：正在abort。 */
        unsigned short  reserved : 14; /* bit[2-15]: 保留。 */
    } reg;
} SOC_PMUI2C_IC_ENABLE_UNION;
#endif
#define SOC_PMUI2C_IC_ENABLE_enable_START    (0)
#define SOC_PMUI2C_IC_ENABLE_enable_END      (0)
#define SOC_PMUI2C_IC_ENABLE_abort_START     (1)
#define SOC_PMUI2C_IC_ENABLE_abort_END       (1)


/*****************************************************************************
 结构名    : SOC_PMUI2C_IC_STATUS_UNION
 结构说明  : IC_STATUS 寄存器结构定义。地址偏移量:0x070，初值:0x00000006，宽度:32
 寄存器说明: I2C设备的状态寄存器。
            指示当前传输状态和FIFO状态。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  activity     : 1;  /* bit[0]   : I2C设备的状态。
                                                       0：空闲；
                                                       1：忙。 */
        unsigned int  tfnf         : 1;  /* bit[1]   : 发送FIFO是否没满。
                                                       0：已满；
                                                       1：没满。 */
        unsigned int  tfe          : 1;  /* bit[2]   : 发送FIFO是否已空。
                                                       0：没空；
                                                       1：已空。 */
        unsigned int  rfne         : 1;  /* bit[3]   : 接收FIFO是否非空。
                                                       0：已空；
                                                       1：非空。 */
        unsigned int  rff          : 1;  /* bit[4]   : 接收FIFO是否已满。
                                                       0：没满；
                                                       1：已满。 */
        unsigned int  mst_activity : 1;  /* bit[5]   : master FSM activity状态。
                                                       0：idle；
                                                       1：非idle状态。 */
        unsigned int  slv_activity : 1;  /* bit[6]   : slave FSM activity状态。
                                                       0：idle；
                                                       1：非idle状态。 */
        unsigned int  reserved     : 25; /* bit[7-31]: 保留。 */
    } reg;
} SOC_PMUI2C_IC_STATUS_UNION;
#endif
#define SOC_PMUI2C_IC_STATUS_activity_START      (0)
#define SOC_PMUI2C_IC_STATUS_activity_END        (0)
#define SOC_PMUI2C_IC_STATUS_tfnf_START          (1)
#define SOC_PMUI2C_IC_STATUS_tfnf_END            (1)
#define SOC_PMUI2C_IC_STATUS_tfe_START           (2)
#define SOC_PMUI2C_IC_STATUS_tfe_END             (2)
#define SOC_PMUI2C_IC_STATUS_rfne_START          (3)
#define SOC_PMUI2C_IC_STATUS_rfne_END            (3)
#define SOC_PMUI2C_IC_STATUS_rff_START           (4)
#define SOC_PMUI2C_IC_STATUS_rff_END             (4)
#define SOC_PMUI2C_IC_STATUS_mst_activity_START  (5)
#define SOC_PMUI2C_IC_STATUS_mst_activity_END    (5)
#define SOC_PMUI2C_IC_STATUS_slv_activity_START  (6)
#define SOC_PMUI2C_IC_STATUS_slv_activity_END    (6)


/*****************************************************************************
 结构名    : SOC_PMUI2C_IC_TXFLR_UNION
 结构说明  : IC_TXFLR 寄存器结构定义。地址偏移量:0x074，初值:0x00000000，宽度:32
 寄存器说明: 发送FIFO中的数据个数寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  txflr    : 7;  /* bit[0-6] : 发送FIFO中的数据个数。 */
        unsigned int  reserved : 25; /* bit[7-31]: 保留。 */
    } reg;
} SOC_PMUI2C_IC_TXFLR_UNION;
#endif
#define SOC_PMUI2C_IC_TXFLR_txflr_START     (0)
#define SOC_PMUI2C_IC_TXFLR_txflr_END       (6)


/*****************************************************************************
 结构名    : SOC_PMUI2C_IC_RXFLR_UNION
 结构说明  : IC_RXFLR 寄存器结构定义。地址偏移量:0x078，初值:0x00000000，宽度:32
 寄存器说明: 接收FIFO中的数据个数寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rxflr    : 7;  /* bit[0-6] : 接收FIFO中的数据个数。 */
        unsigned int  reserved : 25; /* bit[7-31]: 保留。 */
    } reg;
} SOC_PMUI2C_IC_RXFLR_UNION;
#endif
#define SOC_PMUI2C_IC_RXFLR_rxflr_START     (0)
#define SOC_PMUI2C_IC_RXFLR_rxflr_END       (6)


/*****************************************************************************
 结构名    : SOC_PMUI2C_IC_SDA_HOLD_UNION
 结构说明  : IC_SDA_HOLD 寄存器结构定义。地址偏移量:0x07C，初值:0x00000001，宽度:32
 寄存器说明: I2C SDA HOLD时间长度寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ic_sda_hold : 16; /* bit[0-15] : 设置SDA hold 时间，以ic_clk周期为单位。 */
        unsigned int  reserved    : 16; /* bit[16-31]: 保留。 */
    } reg;
} SOC_PMUI2C_IC_SDA_HOLD_UNION;
#endif
#define SOC_PMUI2C_IC_SDA_HOLD_ic_sda_hold_START  (0)
#define SOC_PMUI2C_IC_SDA_HOLD_ic_sda_hold_END    (15)


/*****************************************************************************
 结构名    : SOC_PMUI2C_IC_TX_ABRT_SOURCE_UNION
 结构说明  : IC_TX_ABRT_SOURCE 寄存器结构定义。地址偏移量:0x080，初值:0x00000000，宽度:32
 寄存器说明: TX_ABRT中断的中断源寄存器。
            bit[11]～bit[0]的值“0”表示复位值。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  abrt_7b_addr_noack   : 1;  /* bit[0]    : 1：作为主设备时发送的7位地址没被响应。 */
        unsigned int  abrt_10addr1_noack   : 1;  /* bit[1]    : 1：作为主设备时发送的10位地址的第1字节没被响应。 */
        unsigned int  abrt_10addr2_noack   : 1;  /* bit[2]    : 1：作为主设备时发送的10位地址的第1字节没被响应。 */
        unsigned int  abrt_txdata_nocack   : 1;  /* bit[3]    : 1：作为主设备时发送的地址被从设备响应，而发送的数据没被响应。 */
        unsigned int  abrt_gcall_noack     : 1;  /* bit[4]    : 1：作为主设备时发出general call，但没被响应。 */
        unsigned int  abrt_gcall_read      : 1;  /* bit[5]    : 1：作为主设备时发出general call，而CPU向I2C发出读命令。 */
        unsigned int  abrt_hs_ack_det      : 1;  /* bit[6]    : 1：作为主设备进行高速传输时，高速主机码被响应。 */
        unsigned int  abrt_sbyte_ackdet    : 1;  /* bit[7]    : 1：作为主设备时发出start byte而被响应。 */
        unsigned int  abrt_hs_norstrt      : 1;  /* bit[8]    : 1：作为主设备不支持restart功能时，进行高速操作。 */
        unsigned int  abrt_sbyte_norstrt   : 1;  /* bit[9]    : 1：作为主设备不支持restart功能时，发送start byte。 */
        unsigned int  abrt_10b_rd_norestrt : 1;  /* bit[10]   : 1：作为主设备不支持restart功能时，对10位地址的从设备发出了读命令。 */
        unsigned int  abrt_master_dis      : 1;  /* bit[11]   : 1：Master功能禁用时，发起Master操作。 */
        unsigned int  arb_lost             : 1;  /* bit[12]   : 1：Master失去总线仲裁，或者由于I2C_TX_ABRT_SOURCE[14]设置为1。 */
        unsigned int  abrt_slvflush_txfifo : 1;  /* bit[13]   : 1:Slave接收到读命令时TX_FIFO还有数据，此时Slave发出一个TX_ABRT中断去flush TX_FIFO中的旧数据。 */
        unsigned int  abrt_slv_arblost     : 1;  /* bit[14]   : 1:Slave在发送数据给远端Master时失去总线仲裁，此时I2C_TX_ABRT_SOURCE[12]同时设置为1。 */
        unsigned int  abrt_slvrd_intx      : 1;  /* bit[15]   : 1：Slave在发送数据给远端Master时在IC_DATA_CMD寄存器bit8写入1。 */
        unsigned int  abrt_user_abrt       : 1;  /* bit[16]   : 1:master transmitter检测到传输abort。 */
        unsigned int  reserved             : 7;  /* bit[17-23]: 保留。 */
        unsigned int  tx_flush_cnt         : 8;  /* bit[24-31]: 该值保护txflr的值优先于最后的tx_abrt事件。当I2C disabled的时候该值被清除。 */
    } reg;
} SOC_PMUI2C_IC_TX_ABRT_SOURCE_UNION;
#endif
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_7b_addr_noack_START    (0)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_7b_addr_noack_END      (0)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_10addr1_noack_START    (1)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_10addr1_noack_END      (1)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_10addr2_noack_START    (2)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_10addr2_noack_END      (2)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_txdata_nocack_START    (3)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_txdata_nocack_END      (3)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_gcall_noack_START      (4)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_gcall_noack_END        (4)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_gcall_read_START       (5)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_gcall_read_END         (5)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_hs_ack_det_START       (6)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_hs_ack_det_END         (6)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_sbyte_ackdet_START     (7)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_sbyte_ackdet_END       (7)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_hs_norstrt_START       (8)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_hs_norstrt_END         (8)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_sbyte_norstrt_START    (9)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_sbyte_norstrt_END      (9)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_10b_rd_norestrt_START  (10)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_10b_rd_norestrt_END    (10)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_master_dis_START       (11)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_master_dis_END         (11)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_arb_lost_START              (12)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_arb_lost_END                (12)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_slvflush_txfifo_START  (13)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_slvflush_txfifo_END    (13)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_slv_arblost_START      (14)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_slv_arblost_END        (14)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_slvrd_intx_START       (15)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_slvrd_intx_END         (15)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_user_abrt_START        (16)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_abrt_user_abrt_END          (16)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_tx_flush_cnt_START          (24)
#define SOC_PMUI2C_IC_TX_ABRT_SOURCE_tx_flush_cnt_END            (31)


/*****************************************************************************
 结构名    : SOC_PMUI2C_IC_DMA_CR_UNION
 结构说明  : IC_DMA_CR 寄存器结构定义。地址偏移量:0x088，初值:0x00000000，宽度:32
 寄存器说明: DMA接口控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rdmae    : 1;  /* bit[0]   : 是否打开接收FIFO的DMA通道。
                                                   0：不打开；
                                                   1：打开。 */
        unsigned int  tdmae    : 1;  /* bit[1]   : 是否打开发送FIFO的DMA通道。
                                                   0：不打开；
                                                   1：打开。 */
        unsigned int  reserved : 30; /* bit[2-31]: 保留。 */
    } reg;
} SOC_PMUI2C_IC_DMA_CR_UNION;
#endif
#define SOC_PMUI2C_IC_DMA_CR_rdmae_START     (0)
#define SOC_PMUI2C_IC_DMA_CR_rdmae_END       (0)
#define SOC_PMUI2C_IC_DMA_CR_tdmae_START     (1)
#define SOC_PMUI2C_IC_DMA_CR_tdmae_END       (1)


/*****************************************************************************
 结构名    : SOC_PMUI2C_IC_DMA_TDLR_UNION
 结构说明  : IC_DMA_TDLR 寄存器结构定义。地址偏移量:0x08C，初值:0x00000000，宽度:32
 寄存器说明: 发送FIFO进行DMA操作时的阈值寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dmatdl   : 6;  /* bit[0-5] : 发送FIFO DMA操作时的阈值。 */
        unsigned int  reserved : 26; /* bit[6-31]: 保留。 */
    } reg;
} SOC_PMUI2C_IC_DMA_TDLR_UNION;
#endif
#define SOC_PMUI2C_IC_DMA_TDLR_dmatdl_START    (0)
#define SOC_PMUI2C_IC_DMA_TDLR_dmatdl_END      (5)


/*****************************************************************************
 结构名    : SOC_PMUI2C_IC_DMA_RDLR_UNION
 结构说明  : IC_DMA_RDLR 寄存器结构定义。地址偏移量:0x090，初值:0x00000000，宽度:32
 寄存器说明: 接收FIFO进行DMA操作时的阈值寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dmardl   : 6;  /* bit[0-5] : 接收FIFO DMA操作时的阈值，实际值等于配置值+1。 */
        unsigned int  reserved : 26; /* bit[6-31]: 保留。 */
    } reg;
} SOC_PMUI2C_IC_DMA_RDLR_UNION;
#endif
#define SOC_PMUI2C_IC_DMA_RDLR_dmardl_START    (0)
#define SOC_PMUI2C_IC_DMA_RDLR_dmardl_END      (5)


/*****************************************************************************
 结构名    : SOC_PMUI2C_IC_SDA_SETUP_UNION
 结构说明  : IC_SDA_SETUP 寄存器结构定义。地址偏移量:0x094，初值:0x00000064，宽度:32
 寄存器说明: I2C SDA SETUP时间长度寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ic_sda_setup : 8;  /* bit[0-7] : 设置SDA setup 时间，以ic_clk周期为单位。 */
        unsigned int  reserved     : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_PMUI2C_IC_SDA_SETUP_UNION;
#endif
#define SOC_PMUI2C_IC_SDA_SETUP_ic_sda_setup_START  (0)
#define SOC_PMUI2C_IC_SDA_SETUP_ic_sda_setup_END    (7)


/*****************************************************************************
 结构名    : SOC_PMUI2C_IC_ACK_GENERAL_CALL_UNION
 结构说明  : IC_ACK_GENERAL_CALL 寄存器结构定义。地址偏移量:0x098，初值:0x00000001，宽度:32
 寄存器说明: I2C在接收GENERAL CALL时响应ACK或NACK寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ack_gen_call : 1;  /* bit[0]   : i2c在接收GENERAL CALL时是否响应ACK或NACK寄存器
                                                       1：响应
                                                       0：不响应，且不产生General Call中断 */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留。 */
    } reg;
} SOC_PMUI2C_IC_ACK_GENERAL_CALL_UNION;
#endif
#define SOC_PMUI2C_IC_ACK_GENERAL_CALL_ack_gen_call_START  (0)
#define SOC_PMUI2C_IC_ACK_GENERAL_CALL_ack_gen_call_END    (0)


/*****************************************************************************
 结构名    : SOC_PMUI2C_IC_ENABLE_STATUS_UNION
 结构说明  : IC_ENABLE_STATUS 寄存器结构定义。地址偏移量:0x09C，初值:0x00000000，宽度:32
 寄存器说明: I2C硬件状态寄存器，反映i2c当IC_ENABLE[0]从1到0跳变时的状态。当IC_ENABLE[0]为1时，IC_ENABLE_STATUS[2:1]为0，IC_ENABLE_STATUS[0]为1。.
            IC_ENABLE[0]为0时，IC_ENABLE_STATUS[2:1]当IC_ENABLE_STATUS[0]为0时有效。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ic_en                   : 1;  /* bit[0]   : 1：i2c在enable状态。
                                                                  0：i2c在inactive状态。 */
        unsigned int  slv_disabled_while_busy : 1;  /* bit[1]   : 1：当IC_ENABLE[0]从1到0跳变时，I2C作为Master数据还在传输地址的过程中。
                                                                  0：当IC_ENABLE[0]从1到0跳变时，I2C作为Master数据没有在传输数据 */
        unsigned int  slv_rx_data_lost        : 1;  /* bit[2]   : 1：当IC_ENABLE[0]从1到0跳变时，I2C作为Master数据仍然在传输（已经传输到了地址、数据甚至NACK）。
                                                                  0：当IC_ENABLE[0]从1到0跳变时，I2C作为Master数据没有在传输数据 */
        unsigned int  reserved                : 29; /* bit[3-31]: 保留。 */
    } reg;
} SOC_PMUI2C_IC_ENABLE_STATUS_UNION;
#endif
#define SOC_PMUI2C_IC_ENABLE_STATUS_ic_en_START                    (0)
#define SOC_PMUI2C_IC_ENABLE_STATUS_ic_en_END                      (0)
#define SOC_PMUI2C_IC_ENABLE_STATUS_slv_disabled_while_busy_START  (1)
#define SOC_PMUI2C_IC_ENABLE_STATUS_slv_disabled_while_busy_END    (1)
#define SOC_PMUI2C_IC_ENABLE_STATUS_slv_rx_data_lost_START         (2)
#define SOC_PMUI2C_IC_ENABLE_STATUS_slv_rx_data_lost_END           (2)


/*****************************************************************************
 结构名    : SOC_PMUI2C_IC_FS_SPKLEN_UNION
 结构说明  : IC_FS_SPKLEN 寄存器结构定义。地址偏移量:0x00A0，初值:0x00000005，宽度:32
 寄存器说明: 在Fast Speed模式下，可过滤毛刺长度配置寄存器，在I2C设备未使能时（IC_ENABLE bit[0]为0），才可配置此寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ic_fs_spklen : 8;  /* bit[0-7] : 以ic_clk的cycle为准，Fast Speed模式下设置SCL和SDA中可被过滤毛刺的最长长度，最小值为1，若小于1，按1处理 */
        unsigned int  reserved     : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_PMUI2C_IC_FS_SPKLEN_UNION;
#endif
#define SOC_PMUI2C_IC_FS_SPKLEN_ic_fs_spklen_START  (0)
#define SOC_PMUI2C_IC_FS_SPKLEN_ic_fs_spklen_END    (7)


/*****************************************************************************
 结构名    : SOC_PMUI2C_IC_HS_SPKLEN_UNION
 结构说明  : IC_HS_SPKLEN 寄存器结构定义。地址偏移量:0x00A4，初值:0x00000101，宽度:32
 寄存器说明: 在High Speed模式下，可过滤毛刺长度配置寄存器，在I2C设备未使能时（IC_ENABLE bit[0]为0），才可配置此寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ic_hs_spklen : 8;  /* bit[0-7] : 以ic_clk的cycle为准，High Speed模式下设置SCL和SDA中可被过滤毛刺的最长长度，最小值为1，若小于1，按1处理 */
        unsigned int  reserved     : 24; /* bit[8-31]: 保留。 */
    } reg;
} SOC_PMUI2C_IC_HS_SPKLEN_UNION;
#endif
#define SOC_PMUI2C_IC_HS_SPKLEN_ic_hs_spklen_START  (0)
#define SOC_PMUI2C_IC_HS_SPKLEN_ic_hs_spklen_END    (7)


/*****************************************************************************
 结构名    : SOC_PMUI2C_IC_COMP_PARAM_1_UNION
 结构说明  : IC_COMP_PARAM_1 寄存器结构定义。地址偏移量:0x00F4，初值:0x003F3FEE，宽度:32
 寄存器说明: 器件参数寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  apb_data_width     : 2;  /* bit[0-1]  : APB的数据宽度配置
                                                              可选0x00=8,
                                                              0x01=16,
                                                              0x02=32,
                                                              0x03=reserved */
        unsigned int  max_speed_mode     : 2;  /* bit[2-3]  : 配置I2C的速度模式
                                                              0x00：reserved
                                                              0x01：Standard
                                                              0x02：Fast
                                                              0x03：High */
        unsigned int  hc_count_values    : 1;  /* bit[4]    : 所有的*CNT寄存器是否可读写
                                                              1：只读
                                                              0：可读写 */
        unsigned int  intr_io            : 1;  /* bit[5]    : 每个中断是否有独立的输出
                                                              1：所有中断源公用一个输出
                                                              0：每个中断源有各自独立的输出 */
        unsigned int  has_dma            : 1;  /* bit[6]    : 是否在顶层添加DMA握手接口信号
                                                              1：添加
                                                              0：不添加 */
        unsigned int  add_encoded_params : 1;  /* bit[7]    : 是否通过软件添加encoded参数
                                                              1：添加
                                                              0：不添加 */
        unsigned int  rx_buffer_depth    : 8;  /* bit[8-15] : 描述RX_BUFFER的深度 */
        unsigned int  tx_buffer_depth    : 8;  /* bit[16-23]: 描述TX_BUFFER的深度 */
        unsigned int  reserved           : 8;  /* bit[24-31]: 保留 */
    } reg;
} SOC_PMUI2C_IC_COMP_PARAM_1_UNION;
#endif
#define SOC_PMUI2C_IC_COMP_PARAM_1_apb_data_width_START      (0)
#define SOC_PMUI2C_IC_COMP_PARAM_1_apb_data_width_END        (1)
#define SOC_PMUI2C_IC_COMP_PARAM_1_max_speed_mode_START      (2)
#define SOC_PMUI2C_IC_COMP_PARAM_1_max_speed_mode_END        (3)
#define SOC_PMUI2C_IC_COMP_PARAM_1_hc_count_values_START     (4)
#define SOC_PMUI2C_IC_COMP_PARAM_1_hc_count_values_END       (4)
#define SOC_PMUI2C_IC_COMP_PARAM_1_intr_io_START             (5)
#define SOC_PMUI2C_IC_COMP_PARAM_1_intr_io_END               (5)
#define SOC_PMUI2C_IC_COMP_PARAM_1_has_dma_START             (6)
#define SOC_PMUI2C_IC_COMP_PARAM_1_has_dma_END               (6)
#define SOC_PMUI2C_IC_COMP_PARAM_1_add_encoded_params_START  (7)
#define SOC_PMUI2C_IC_COMP_PARAM_1_add_encoded_params_END    (7)
#define SOC_PMUI2C_IC_COMP_PARAM_1_rx_buffer_depth_START     (8)
#define SOC_PMUI2C_IC_COMP_PARAM_1_rx_buffer_depth_END       (15)
#define SOC_PMUI2C_IC_COMP_PARAM_1_tx_buffer_depth_START     (16)
#define SOC_PMUI2C_IC_COMP_PARAM_1_tx_buffer_depth_END       (23)


/*****************************************************************************
 结构名    : SOC_PMUI2C_IC_COMP_VERSION_UNION
 结构说明  : IC_COMP_VERSION 寄存器结构定义。地址偏移量:0x00F8，初值:0x3132302A，宽度:32
 寄存器说明: 器件版本寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: 描述I2C器件的版本信息 */
    } reg;
} SOC_PMUI2C_IC_COMP_VERSION_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_PMUI2C_IC_COMP_TYPE_UNION
 结构说明  : IC_COMP_TYPE 寄存器结构定义。地址偏移量:0x00FC，初值:0x44570140，宽度:32
 寄存器说明: 器件编号寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: 描述I2C元件的TYPE NUMBER */
    } reg;
} SOC_PMUI2C_IC_COMP_TYPE_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_PMUI2C_CPU_PHS_ADDR_UNION
 结构说明  : CPU_PHS_ADDR 寄存器结构定义。地址偏移量:0x0100，初值:0xD2，宽度:8
 寄存器说明: CPU的调相地址寄存器.
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cpu_phs_addr : 8;  /* bit[0-7]: PMU调相寄存器地址（对应CPU） */
    } reg;
} SOC_PMUI2C_CPU_PHS_ADDR_UNION;
#endif
#define SOC_PMUI2C_CPU_PHS_ADDR_cpu_phs_addr_START  (0)
#define SOC_PMUI2C_CPU_PHS_ADDR_cpu_phs_addr_END    (7)


/*****************************************************************************
 结构名    : SOC_PMUI2C_CPU_VOL_ADDR_UNION
 结构说明  : CPU_VOL_ADDR 寄存器结构定义。地址偏移量:0x0104，初值:0xD8，宽度:8
 寄存器说明: CPU的调压地址寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cpu_vol_addr : 8;  /* bit[0-7]: PMU调压寄存器地址（对应CPU） */
    } reg;
} SOC_PMUI2C_CPU_VOL_ADDR_UNION;
#endif
#define SOC_PMUI2C_CPU_VOL_ADDR_cpu_vol_addr_START  (0)
#define SOC_PMUI2C_CPU_VOL_ADDR_cpu_vol_addr_END    (7)


/*****************************************************************************
 结构名    : SOC_PMUI2C_CPU_IDX_UNION
 结构说明  : CPU_IDX 寄存器结构定义。地址偏移量:0x0108，初值:0x00，宽度:8
 寄存器说明: CPU调压/调相数据
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cpu_idx : 8;  /* bit[0-7]: CPU调压调相寄存器数据 */
    } reg;
} SOC_PMUI2C_CPU_IDX_UNION;
#endif
#define SOC_PMUI2C_CPU_IDX_cpu_idx_START  (0)
#define SOC_PMUI2C_CPU_IDX_cpu_idx_END    (7)


/*****************************************************************************
 结构名    : SOC_PMUI2C_GPU_PHS_ADDR_UNION
 结构说明  : GPU_PHS_ADDR 寄存器结构定义。地址偏移量:0x010C，初值:0xD2，宽度:8
 寄存器说明: GPU的调相地址寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  gpu_phs_addr : 8;  /* bit[0-7]: PMU调相寄存器地址（对应GPU） */
    } reg;
} SOC_PMUI2C_GPU_PHS_ADDR_UNION;
#endif
#define SOC_PMUI2C_GPU_PHS_ADDR_gpu_phs_addr_START  (0)
#define SOC_PMUI2C_GPU_PHS_ADDR_gpu_phs_addr_END    (7)


/*****************************************************************************
 结构名    : SOC_PMUI2C_GPU_VOL_ADDR_UNION
 结构说明  : GPU_VOL_ADDR 寄存器结构定义。地址偏移量:0x0110，初值:0xD8，宽度:8
 寄存器说明: GPU的调压地址寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  gpu_vol_addr : 8;  /* bit[0-7]: PMU调压寄存器地址（对应GPU） */
    } reg;
} SOC_PMUI2C_GPU_VOL_ADDR_UNION;
#endif
#define SOC_PMUI2C_GPU_VOL_ADDR_gpu_vol_addr_START  (0)
#define SOC_PMUI2C_GPU_VOL_ADDR_gpu_vol_addr_END    (7)


/*****************************************************************************
 结构名    : SOC_PMUI2C_GPU_IDX_UNION
 结构说明  : GPU_IDX 寄存器结构定义。地址偏移量:0x0114，初值:0x00，宽度:8
 寄存器说明: GPU调压/调相数据
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  gpu_idx : 8;  /* bit[0-7]: GPU调压调相寄存器数据 */
    } reg;
} SOC_PMUI2C_GPU_IDX_UNION;
#endif
#define SOC_PMUI2C_GPU_IDX_gpu_idx_START  (0)
#define SOC_PMUI2C_GPU_IDX_gpu_idx_END    (7)


/*****************************************************************************
 结构名    : SOC_PMUI2C_CPU_SLAVE_ADDR_UNION
 结构说明  : CPU_SLAVE_ADDR 寄存器结构定义。地址偏移量:0x0118，初值:0x68，宽度:8
 寄存器说明: 对应CPU——PMU的地址
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cpu_slave_addr : 8;  /* bit[0-7]: PMU的地址（对应CPU） */
    } reg;
} SOC_PMUI2C_CPU_SLAVE_ADDR_UNION;
#endif
#define SOC_PMUI2C_CPU_SLAVE_ADDR_cpu_slave_addr_START  (0)
#define SOC_PMUI2C_CPU_SLAVE_ADDR_cpu_slave_addr_END    (7)


/*****************************************************************************
 结构名    : SOC_PMUI2C_GPU_SLAVE_ADDR_UNION
 结构说明  : GPU_SLAVE_ADDR 寄存器结构定义。地址偏移量:0x011C，初值:0x58，宽度:8
 寄存器说明: 对应GPU——PMU的地址
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  gpu_slave_addr : 8;  /* bit[0-7]: PMU的地址（对应GPU） */
    } reg;
} SOC_PMUI2C_GPU_SLAVE_ADDR_UNION;
#endif
#define SOC_PMUI2C_GPU_SLAVE_ADDR_gpu_slave_addr_START  (0)
#define SOC_PMUI2C_GPU_SLAVE_ADDR_gpu_slave_addr_END    (7)


/*****************************************************************************
 结构名    : SOC_PMUI2C_STOPTIMEOUT_UNION
 结构说明  : STOPTIMEOUT 寄存器结构定义。地址偏移量:0x0120，初值:0xFFFFFFFF，宽度:32
 寄存器说明: STOP信号超时计数器与PMU选择寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stop_time_out : 32; /* bit[0-31]: PMUI2C超时计数 */
    } reg;
} SOC_PMUI2C_STOPTIMEOUT_UNION;
#endif
#define SOC_PMUI2C_STOPTIMEOUT_stop_time_out_START  (0)
#define SOC_PMUI2C_STOPTIMEOUT_stop_time_out_END    (31)


/*****************************************************************************
 结构名    : SOC_PMUI2C_INTER_STAT_UNION
 结构说明  : INTER_STAT 寄存器结构定义。地址偏移量:0x0124，初值:0x0，宽度:32
 寄存器说明: 原始中断状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pmui2c_impact_inter_state  : 1;  /* bit[0]   : APB模式下来AVS请求的原始中断 */
        unsigned int  pmui2c_overtime_inter_stat : 1;  /* bit[1-1] : AVS模式下Stop超时原始中断 */
        unsigned int  reserved                   : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_PMUI2C_INTER_STAT_UNION;
#endif
#define SOC_PMUI2C_INTER_STAT_pmui2c_impact_inter_state_START   (0)
#define SOC_PMUI2C_INTER_STAT_pmui2c_impact_inter_state_END     (0)
#define SOC_PMUI2C_INTER_STAT_pmui2c_overtime_inter_stat_START  (1)
#define SOC_PMUI2C_INTER_STAT_pmui2c_overtime_inter_stat_END    (1)


/*****************************************************************************
 结构名    : SOC_PMUI2C_INTER_MASK_UNION
 结构说明  : INTER_MASK 寄存器结构定义。地址偏移量:0x0128，初值:0x3，宽度:32
 寄存器说明: 中断屏蔽寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pmui2c_impact_inter_mask   : 1;  /* bit[0]   : APB模式下来AVS请求的中断屏蔽，0表明屏蔽，1表明不屏蔽。 */
        unsigned int  pmui2c_overtime_inter_mask : 1;  /* bit[1-1] : AVS模式下Stop超时中断屏蔽，0表明屏蔽，1表明不屏蔽。 */
        unsigned int  reserved                   : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_PMUI2C_INTER_MASK_UNION;
#endif
#define SOC_PMUI2C_INTER_MASK_pmui2c_impact_inter_mask_START    (0)
#define SOC_PMUI2C_INTER_MASK_pmui2c_impact_inter_mask_END      (0)
#define SOC_PMUI2C_INTER_MASK_pmui2c_overtime_inter_mask_START  (1)
#define SOC_PMUI2C_INTER_MASK_pmui2c_overtime_inter_mask_END    (1)


/*****************************************************************************
 结构名    : SOC_PMUI2C_INTER_UNION
 结构说明  : INTER 寄存器结构定义。地址偏移量:0x012C，初值:0x0，宽度:32
 寄存器说明: 中断状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pmui2c_impact_inter   : 1;  /* bit[0]   : APB模式下来AVS请求的中断（可屏蔽） */
        unsigned int  pmui2c_overtime_inter : 1;  /* bit[1-1] : AVS模式下Stop超时中断（可屏蔽） */
        unsigned int  reserved              : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_PMUI2C_INTER_UNION;
#endif
#define SOC_PMUI2C_INTER_pmui2c_impact_inter_START    (0)
#define SOC_PMUI2C_INTER_pmui2c_impact_inter_END      (0)
#define SOC_PMUI2C_INTER_pmui2c_overtime_inter_START  (1)
#define SOC_PMUI2C_INTER_pmui2c_overtime_inter_END    (1)


/*****************************************************************************
 结构名    : SOC_PMUI2C_CLR_OVERTIME_UNION
 结构说明  : CLR_OVERTIME 寄存器结构定义。地址偏移量:0x0130，初值:0x0，宽度:32
 寄存器说明: 清除中断1寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 1;  /* bit[0-0] : 读清AVS模式下Stop超时原始中断 */
        unsigned int  reserved_1: 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_PMUI2C_CLR_OVERTIME_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_PMUI2C_CLR_IMPACT_UNION
 结构说明  : CLR_IMPACT 寄存器结构定义。地址偏移量:0x0134，初值:0x0，宽度:32
 寄存器说明: 清除中断0寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 1;  /* bit[0-0] : 读清APB模式下来AVS请求的中断 */
        unsigned int  reserved_1: 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_PMUI2C_CLR_IMPACT_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_PMUI2C_DEBUG_UNION
 结构说明  : DEBUG 寄存器结构定义。地址偏移量:0x0138，初值:0x00000，宽度:32
 寄存器说明: DEBUG标志寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pmui2c_debug_err     : 1;  /* bit[0]    : PMUI2C在AVS正在传输的过程中是否有APB的请求 */
        unsigned int  i2c_debug_slv_cstate : 3;  /* bit[1-3]  : 对应I2C内部的debug信号 */
        unsigned int  i2c_debug_mst_cstate : 5;  /* bit[4-8]  : 对应I2C内部的debug信号 */
        unsigned int  i2c_debug_slave_act  : 1;  /* bit[9]    : 对应I2C内部的debug信号 */
        unsigned int  i2c_debug_master_act : 1;  /* bit[10]   : 对应I2C内部的debug信号 */
        unsigned int  i2c_debug_hs         : 1;  /* bit[11]   : 对应I2C内部的debug信号 */
        unsigned int  i2c_debug_wr         : 1;  /* bit[12]   : 对应I2C内部的debug信号 */
        unsigned int  i2c_debug_rd         : 1;  /* bit[13]   : 对应I2C内部的debug信号 */
        unsigned int  i2c_debug_addr_10bit : 1;  /* bit[14]   : 对应I2C内部的debug信号 */
        unsigned int  i2c_debug_addr       : 1;  /* bit[15]   : 对应I2C内部的debug信号 */
        unsigned int  i2c_debug_data       : 1;  /* bit[16]   : 对应I2C内部的debug信号 */
        unsigned int  i2c_debug_p_gen      : 1;  /* bit[17]   : 对应I2C内部的debug信号 */
        unsigned int  i2c_debug_s_gen      : 1;  /* bit[18]   : 对应I2C内部的debug信号 */
        unsigned int  reserved             : 13; /* bit[19-31]: 保留 */
    } reg;
} SOC_PMUI2C_DEBUG_UNION;
#endif
#define SOC_PMUI2C_DEBUG_pmui2c_debug_err_START      (0)
#define SOC_PMUI2C_DEBUG_pmui2c_debug_err_END        (0)
#define SOC_PMUI2C_DEBUG_i2c_debug_slv_cstate_START  (1)
#define SOC_PMUI2C_DEBUG_i2c_debug_slv_cstate_END    (3)
#define SOC_PMUI2C_DEBUG_i2c_debug_mst_cstate_START  (4)
#define SOC_PMUI2C_DEBUG_i2c_debug_mst_cstate_END    (8)
#define SOC_PMUI2C_DEBUG_i2c_debug_slave_act_START   (9)
#define SOC_PMUI2C_DEBUG_i2c_debug_slave_act_END     (9)
#define SOC_PMUI2C_DEBUG_i2c_debug_master_act_START  (10)
#define SOC_PMUI2C_DEBUG_i2c_debug_master_act_END    (10)
#define SOC_PMUI2C_DEBUG_i2c_debug_hs_START          (11)
#define SOC_PMUI2C_DEBUG_i2c_debug_hs_END            (11)
#define SOC_PMUI2C_DEBUG_i2c_debug_wr_START          (12)
#define SOC_PMUI2C_DEBUG_i2c_debug_wr_END            (12)
#define SOC_PMUI2C_DEBUG_i2c_debug_rd_START          (13)
#define SOC_PMUI2C_DEBUG_i2c_debug_rd_END            (13)
#define SOC_PMUI2C_DEBUG_i2c_debug_addr_10bit_START  (14)
#define SOC_PMUI2C_DEBUG_i2c_debug_addr_10bit_END    (14)
#define SOC_PMUI2C_DEBUG_i2c_debug_addr_START        (15)
#define SOC_PMUI2C_DEBUG_i2c_debug_addr_END          (15)
#define SOC_PMUI2C_DEBUG_i2c_debug_data_START        (16)
#define SOC_PMUI2C_DEBUG_i2c_debug_data_END          (16)
#define SOC_PMUI2C_DEBUG_i2c_debug_p_gen_START       (17)
#define SOC_PMUI2C_DEBUG_i2c_debug_p_gen_END         (17)
#define SOC_PMUI2C_DEBUG_i2c_debug_s_gen_START       (18)
#define SOC_PMUI2C_DEBUG_i2c_debug_s_gen_END         (18)


/*****************************************************************************
 结构名    : SOC_PMUI2C_PMUI2CSTATE_UNION
 结构说明  : PMUI2CSTATE 寄存器结构定义。地址偏移量:0x013C，初值:0x0，宽度:32
 寄存器说明: PMUI2C状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pmui2c_cur_state : 1;  /* bit[0]   : PMUI2C切换完成后的模式 */
        unsigned int  pmui2c_pre_state : 1;  /* bit[1]   : PMUI2C预期要切换的模式 */
        unsigned int  reserved         : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_PMUI2C_PMUI2CSTATE_UNION;
#endif
#define SOC_PMUI2C_PMUI2CSTATE_pmui2c_cur_state_START  (0)
#define SOC_PMUI2C_PMUI2CSTATE_pmui2c_cur_state_END    (0)
#define SOC_PMUI2C_PMUI2CSTATE_pmui2c_pre_state_START  (1)
#define SOC_PMUI2C_PMUI2CSTATE_pmui2c_pre_state_END    (1)


/*****************************************************************************
 结构名    : SOC_PMUI2C_HOLD_IDLE_UNION
 结构说明  : HOLD_IDLE 寄存器结构定义。地址偏移量:0x0140，初值:0x1，宽度:32
 寄存器说明: PMUI2C hold/idle模式选择寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hold_idle : 1;  /* bit[0-0] : 0对应hold模式
                                                    1对应idle模式 */
        unsigned int  reserved  : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_PMUI2C_HOLD_IDLE_UNION;
#endif
#define SOC_PMUI2C_HOLD_IDLE_hold_idle_START  (0)
#define SOC_PMUI2C_HOLD_IDLE_hold_idle_END    (0)


/*****************************************************************************
 结构名    : SOC_PMUI2C_SLAVE_CHOSE_UNION
 结构说明  : SLAVE_CHOSE 寄存器结构定义。地址偏移量:0x0144，初值:0x0，宽度:32
 寄存器说明: PMUI2C 单/双Slave选择寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  slave_chose : 1;  /* bit[0-0] : 0对应一个slave
                                                      1对应两个slave */
        unsigned int  reserved    : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_PMUI2C_SLAVE_CHOSE_UNION;
#endif
#define SOC_PMUI2C_SLAVE_CHOSE_slave_chose_START  (0)
#define SOC_PMUI2C_SLAVE_CHOSE_slave_chose_END    (0)






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

#endif /* end of soc_pmui2c_interface.h */
