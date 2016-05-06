/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_emmc_arasan_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-04-08 11:45:24
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年4月8日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_EMMC_ARASAN.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_EMMC_ARASAN_INTERFACE_H__
#define __SOC_EMMC_ARASAN_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) register_emmc0
 ****************************************************************************/
/* 寄存器说明：SDMA地址控制寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_SDMA_SYSTEM_ADDRESS_ARGU_MENT2_UNION */
#define SOC_EMMC_ARASAN_SDMA_SYSTEM_ADDRESS_ARGU_MENT2_ADDR(base) ((base) + (0x00))

/* 寄存器说明：BLOCK控制寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_BLOCK_CTRL_UNION */
#define SOC_EMMC_ARASAN_BLOCK_CTRL_ADDR(base)         ((base) + (0x04))

/* 寄存器说明：Argument1寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_ARGUMENT1_UNION */
#define SOC_EMMC_ARASAN_ARGUMENT1_ADDR(base)          ((base) + (0x08))

/* 寄存器说明：传输控制和命令控制寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_TRANS_CMD_CTRL_UNION */
#define SOC_EMMC_ARASAN_TRANS_CMD_CTRL_ADDR(base)     ((base) + (0x0C))

/* 寄存器说明：CMD回复0寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_CMD_RES0_UNION */
#define SOC_EMMC_ARASAN_CMD_RES0_ADDR(base)           ((base) + (0x10))

/* 寄存器说明：CMD回复1寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_CMD_RES1_UNION */
#define SOC_EMMC_ARASAN_CMD_RES1_ADDR(base)           ((base) + (0x14))

/* 寄存器说明：CMD回复2寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_CMD_RES2_UNION */
#define SOC_EMMC_ARASAN_CMD_RES2_ADDR(base)           ((base) + (0x18))

/* 寄存器说明：CMD回复3寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_CMD_RES3_UNION */
#define SOC_EMMC_ARASAN_CMD_RES3_ADDR(base)           ((base) + (0x1C))

/* 寄存器说明：数据寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_BUFFER_DATA_UNION */
#define SOC_EMMC_ARASAN_BUFFER_DATA_ADDR(base)        ((base) + (0x20))

/* 寄存器说明：工作状态寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_PRESENT_STATE_UNION */
#define SOC_EMMC_ARASAN_PRESENT_STATE_ADDR(base)      ((base) + (0x24))

/* 寄存器说明：控制1寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_HOST_CTRL1_UNION */
#define SOC_EMMC_ARASAN_HOST_CTRL1_ADDR(base)         ((base) + (0x28))

/* 寄存器说明：时钟控制和复位寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_CLOCK_RESET_CTRL_UNION */
#define SOC_EMMC_ARASAN_CLOCK_RESET_CTRL_ADDR(base)   ((base) + (0x2C))

/* 寄存器说明：中断和错误状态寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_INTR_ERROR_STATUS_UNION */
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ADDR(base)  ((base) + (0x30))

/* 寄存器说明：中断和错误屏蔽寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_UNION */
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_ADDR(base) ((base) + (0x34))

/* 寄存器说明：中断和错误使能寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_UNION */
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_ADDR(base)  ((base) + (0x38))

/* 寄存器说明：自动tuning错误和控制2寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_UNION */
#define SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_ADDR(base) ((base) + (0x3C))

/* 寄存器说明：控制器能力1寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_UNION */
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_ADDR(base) ((base) + (0x40))

/* 寄存器说明：控制器能力2寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_UNION */
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_ADDR(base) ((base) + (0x44))

/* 寄存器说明：最大电流寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_MAX_CURRENT_UNION */
#define SOC_EMMC_ARASAN_MAX_CURRENT_ADDR(base)        ((base) + (0x48))

/* 寄存器说明：强制触发寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_UNION */
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_ADDR(base) ((base) + (0x50))

/* 寄存器说明：ADMA错误寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_ADMA_ERROR_STATUS_REGISTER_UNION */
#define SOC_EMMC_ARASAN_ADMA_ERROR_STATUS_REGISTER_ADDR(base) ((base) + (0x54))

/* 寄存器说明：ADMA地址1寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_ADMA_SYSTEM_ADDRESS_REG1_UNION */
#define SOC_EMMC_ARASAN_ADMA_SYSTEM_ADDRESS_REG1_ADDR(base) ((base) + (0x58))

/* 寄存器说明：ADMA地址2寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_ADMA_SYSTEM_ADDRESS_REG2_UNION */
#define SOC_EMMC_ARASAN_ADMA_SYSTEM_ADDRESS_REG2_ADDR(base) ((base) + (0x5C))

/* 寄存器说明：初始化模式配置1寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_PRESET_VALUE1_UNION */
#define SOC_EMMC_ARASAN_PRESET_VALUE1_ADDR(base)      ((base) + (0x60))

/* 寄存器说明：初始化模式配置2寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_PRESET_VALUE2_UNION */
#define SOC_EMMC_ARASAN_PRESET_VALUE2_ADDR(base)      ((base) + (0x64))

/* 寄存器说明：初始化模式配置3寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_PRESET_VALUE3_UNION */
#define SOC_EMMC_ARASAN_PRESET_VALUE3_ADDR(base)      ((base) + (0x68))

/* 寄存器说明：初始化模式配置4寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_PRESET_VALUE4_UNION */
#define SOC_EMMC_ARASAN_PRESET_VALUE4_ADDR(base)      ((base) + (0x6C))

/* 寄存器说明：初始化模式配置5寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_PRESET_VALUE5_UNION */
#define SOC_EMMC_ARASAN_PRESET_VALUE5_ADDR(base)      ((base) + (0x74))

/* 寄存器说明：BOOT超时计数寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_BOOT_TIMEOUT_CONTROL_REGISTER_UNION */
#define SOC_EMMC_ARASAN_BOOT_TIMEOUT_CONTROL_REGISTER_ADDR(base) ((base) + (0x70))

/* 寄存器说明：Enhanced Strobe使能寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_ENHANCED_STROBE_ENABLE_UNION */
#define SOC_EMMC_ARASAN_ENHANCED_STROBE_ENABLE_ADDR(base) ((base) + (0x78))

/* 寄存器说明：CQ版本寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_CMD_QUEUEING_VERSION_UNION */
#define SOC_EMMC_ARASAN_CMD_QUEUEING_VERSION_ADDR(base) ((base) + (0x200))

/* 寄存器说明：CQ性能寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_CMD_QUEUEING_CAPABILITIES_UNION */
#define SOC_EMMC_ARASAN_CMD_QUEUEING_CAPABILITIES_ADDR(base) ((base) + (0x204))

/* 寄存器说明：CQ配置寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_CMD_QUEUEING_CFG_UNION */
#define SOC_EMMC_ARASAN_CMD_QUEUEING_CFG_ADDR(base)   ((base) + (0x208))

/* 寄存器说明：CQ控制器寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_CMD_QUEUEING_CTRL_UNION */
#define SOC_EMMC_ARASAN_CMD_QUEUEING_CTRL_ADDR(base)  ((base) + (0x20C))

/* 寄存器说明：CQ中断状态寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_CQ_INTERRUPT_STATUS_UNION */
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_STATUS_ADDR(base) ((base) + (0x210))

/* 寄存器说明：CQ中断状态使能寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_CQ_INTERRUPT_STATUS_ENABLE_UNION */
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_STATUS_ENABLE_ADDR(base) ((base) + (0x214))

/* 寄存器说明：CQ中断信号使能寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_CQ_INTERRUPT_SIGNAL_ENABLE_UNION */
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_SIGNAL_ENABLE_ADDR(base) ((base) + (0x218))

/* 寄存器说明：中断合并寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_INTERRUPT_COALESCING_UNION */
#define SOC_EMMC_ARASAN_INTERRUPT_COALESCING_ADDR(base) ((base) + (0x21C))

/* 寄存器说明：任务链表列表的地址的低位寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_CQ_TASK_DESCLIST_BASEADDRLOWER_UNION */
#define SOC_EMMC_ARASAN_CQ_TASK_DESCLIST_BASEADDRLOWER_ADDR(base) ((base) + (0x220))

/* 寄存器说明：任务链表列表的地址的高位寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_CQ_TASK_DESCLIST_BASEADDRUPEER_UNION */
#define SOC_EMMC_ARASAN_CQ_TASK_DESCLIST_BASEADDRUPEER_ADDR(base) ((base) + (0x224))

/* 寄存器说明：触发CQE处理新任务寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_CQ_TASK_DOORBELL_UNION */
#define SOC_EMMC_ARASAN_CQ_TASK_DOORBELL_ADDR(base)   ((base) + (0x228))

/* 寄存器说明：已完成任务报告寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_CQ_TASK_DOORBELL_NOTIFICATION_UNION */
#define SOC_EMMC_ARASAN_CQ_TASK_DOORBELL_NOTIFICATION_ADDR(base) ((base) + (0x22C))

/* 寄存器说明：CQ设备排队状态寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_CQ_DEVICE_QUEUE_STATUS_UNION */
#define SOC_EMMC_ARASAN_CQ_DEVICE_QUEUE_STATUS_ADDR(base) ((base) + (0x230))

/* 寄存器说明：CQ设备待执行任务寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_CQ_DEVICE_PENDING_TASK_UNION */
#define SOC_EMMC_ARASAN_CQ_DEVICE_PENDING_TASK_ADDR(base) ((base) + (0x234))

/* 寄存器说明：CQ任务清除寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_CQ_TASK_CLEAR_UNION */
#define SOC_EMMC_ARASAN_CQ_TASK_CLEAR_ADDR(base)      ((base) + (0x238))

/* 寄存器说明：发送状态计时器配置寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_SEND_STATUS_TIMER_CFG1_UNION */
#define SOC_EMMC_ARASAN_SEND_STATUS_TIMER_CFG1_ADDR(base) ((base) + (0x240))

/* 寄存器说明：发送状态配置寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_SEND_STATUS_CFG2_UNION */
#define SOC_EMMC_ARASAN_SEND_STATUS_CFG2_ADDR(base)   ((base) + (0x244))

/* 寄存器说明：直接命令任务的回复寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_CMDRESP_FOR_DIRECTCMDTASK_UNION */
#define SOC_EMMC_ARASAN_CMDRESP_FOR_DIRECTCMDTASK_ADDR(base) ((base) + (0x248))

/* 寄存器说明：RED中断产生控制寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_RESP_MODE_ERROR_MASK_UNION */
#define SOC_EMMC_ARASAN_RESP_MODE_ERROR_MASK_ADDR(base) ((base) + (0x250))

/* 寄存器说明：任务错误信息寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_TASK_ERROR_INFO_UNION */
#define SOC_EMMC_ARASAN_TASK_ERROR_INFO_ADDR(base)    ((base) + (0x254))

/* 寄存器说明：CMD回复编号寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_CMD_RESP_INDEX_UNION */
#define SOC_EMMC_ARASAN_CMD_RESP_INDEX_ADDR(base)     ((base) + (0x258))

/* 寄存器说明：CMD回复参数寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_CMD_RESP_ARGUMENT_UNION */
#define SOC_EMMC_ARASAN_CMD_RESP_ARGUMENT_ADDR(base)  ((base) + (0x25C))

/* 寄存器说明：IP配置0寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_CORE_CFG0_UNION */
#define SOC_EMMC_ARASAN_CORE_CFG0_ADDR(base)          ((base) + (0x400))

/* 寄存器说明：IP配置1寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_CORE_CFG1_UNION */
#define SOC_EMMC_ARASAN_CORE_CFG1_ADDR(base)          ((base) + (0x404))

/* 寄存器说明：模式预设0寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE0_UNION */
#define SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE0_ADDR(base) ((base) + (0x408))

/* 寄存器说明：模式预设1寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE1_UNION */
#define SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE1_ADDR(base) ((base) + (0x40C))

/* 寄存器说明：模式预设2寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE2_UNION */
#define SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE2_ADDR(base) ((base) + (0x410))

/* 寄存器说明：模式预设3寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE3_UNION */
#define SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE3_ADDR(base) ((base) + (0x414))

/* 寄存器说明：模式预设4寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE4_UNION */
#define SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE4_ADDR(base) ((base) + (0x418))

/* 寄存器说明：IP配置2寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_CORE_CFG2_UNION */
#define SOC_EMMC_ARASAN_CORE_CFG2_ADDR(base)          ((base) + (0x41C))

/* 寄存器说明：DEBUG0寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_DEBUG_REG0_UNION */
#define SOC_EMMC_ARASAN_DEBUG_REG0_ADDR(base)         ((base) + (0x420))

/* 寄存器说明：DEBUG1寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_DEBUG_REG1_UNION */
#define SOC_EMMC_ARASAN_DEBUG_REG1_ADDR(base)         ((base) + (0x424))

/* 寄存器说明：DEBUG2寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_DEBUG_REG2_UNION */
#define SOC_EMMC_ARASAN_DEBUG_REG2_ADDR(base)         ((base) + (0x428))

/* 寄存器说明：DEBUG3寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_DEBUG_REG3_UNION */
#define SOC_EMMC_ARASAN_DEBUG_REG3_ADDR(base)         ((base) + (0x42C))

/* 寄存器说明：PHY控制寄存器1寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_PHYCTRL1_UNION */
#define SOC_EMMC_ARASAN_PHYCTRL1_ADDR(base)           ((base) + (0x430))

/* 寄存器说明：PHY控制寄存器2寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_PHYCTRL2_UNION */
#define SOC_EMMC_ARASAN_PHYCTRL2_ADDR(base)           ((base) + (0x434))

/* 寄存器说明：PHY控制寄存器3寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_PHYCTRL3_UNION */
#define SOC_EMMC_ARASAN_PHYCTRL3_ADDR(base)           ((base) + (0x438))

/* 寄存器说明：PHY控制寄存器4寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_PHYCTRL4_UNION */
#define SOC_EMMC_ARASAN_PHYCTRL4_ADDR(base)           ((base) + (0x43C))

/* 寄存器说明：PHY状态寄存器寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_PHY_STATUS_UNION */
#define SOC_EMMC_ARASAN_PHY_STATUS_ADDR(base)         ((base) + (0x440))

/* 寄存器说明：测试等控制寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_TEST_CONTROL_UNION */
#define SOC_EMMC_ARASAN_TEST_CONTROL_ADDR(base)       ((base) + (0x444))

/* 寄存器说明：IP配置3寄存器。
   位域定义UNION结构:  SOC_EMMC_ARASAN_CORE_CFG3_UNION */
#define SOC_EMMC_ARASAN_CORE_CFG3_ADDR(base)          ((base) + (0x448))





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
                     (1/1) register_emmc0
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_SDMA_SYSTEM_ADDRESS_ARGU_MENT2_UNION
 结构说明  : SDMA_SYSTEM_ADDRESS_ARGU_MENT2 寄存器结构定义。地址偏移量:0x00，初值:0x00000000，宽度:32
 寄存器说明: SDMA地址控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: This register contains the physical system memory address used for DMA transfers or the second argument for the Auto CMD23.
                                                   (1) SDMA System Address
                                                   (2) Argument 2 */
    } reg;
} SOC_EMMC_ARASAN_SDMA_SYSTEM_ADDRESS_ARGU_MENT2_UNION;
#endif


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_BLOCK_CTRL_UNION
 结构说明  : BLOCK_CTRL 寄存器结构定义。地址偏移量:0x04，初值:0x00000000，宽度:32
 寄存器说明: BLOCK控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  trans_block_size : 12; /* bit[0-11] : This register specifies the block size for block data transfers for CMD17, CMD18, CMD24, CMD25, and CMD53. It can be accessed only if no transaction is executing (i.e after a transaction has stopped). Read operations during transfer return an invalid value and write operations shall be ignored.
                                                            0000h - No Data Transfer
                                                            0001h - 1 Byte
                                                            0002h - 2 Bytes
                                                            0003h - 3 Bytes
                                                            0004h - 4 Bytes
                                                            --- ---
                                                            01FFh - 511 Bytes
                                                            0200h - 512 Bytes */
        unsigned int  sdma_buffer_size : 3;  /* bit[12-14]: To perform long DMA transfer, System Address register shall be updated at every system boundary during DMA transfer. These bits specify the size of contiguous buffer in the system memory. The DMA transfer shall wait at the every boundary specified by these fields and the HC generates the DMA Interrupt to request the HD to update the System Address register.
                                                            000b - 4KB(Detects A11 Carry out)
                                                            001b - 8KB(Detects A12 Carry out)
                                                            010b - 16KB(Detects A13 Carry out)
                                                            011b - 32KB(Detects A14 Carry out)
                                                            100b - 64KB(Detects A15 Carry out)
                                                            101b -128KB(Detects A16 Carry out)
                                                            110b - 256KB(Detects A17 Carry out)
                                                            111b - 512KB(Detects A18 Carry out) */
        unsigned int  reserved         : 1;  /* bit[15]   : reserved. */
        unsigned int  block_count      : 16; /* bit[16-31]: This register is enabled when Block Count Enable in the Transfer Mode register is set to 1 and is valid only for multiple block transfers. The HC decrements the block count after each block transfer and stops when the count reaches zero. It can be accessed only if no transaction is executing (i.e. after a transaction has stopped). Read operations during transfer return an invalid value and write operations shall be ignored.
                                                            When saving transfer context as a result of Suspend command, the number of blocks yet to be transferred can be determined by reading this register. When restoring transfer context prior to issuing a Resume command, the HD shall restore the previously save block count.
                                                            0000h: Stop Count
                                                            0001h: 1 block
                                                            0002h: 2 blocks
                                                            ...
                                                            FFFFh: 65535 blocks */
    } reg;
} SOC_EMMC_ARASAN_BLOCK_CTRL_UNION;
#endif
#define SOC_EMMC_ARASAN_BLOCK_CTRL_trans_block_size_START  (0)
#define SOC_EMMC_ARASAN_BLOCK_CTRL_trans_block_size_END    (11)
#define SOC_EMMC_ARASAN_BLOCK_CTRL_sdma_buffer_size_START  (12)
#define SOC_EMMC_ARASAN_BLOCK_CTRL_sdma_buffer_size_END    (14)
#define SOC_EMMC_ARASAN_BLOCK_CTRL_block_count_START       (16)
#define SOC_EMMC_ARASAN_BLOCK_CTRL_block_count_END         (31)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_ARGUMENT1_UNION
 结构说明  : ARGUMENT1 寄存器结构定义。地址偏移量:0x08，初值:0x00000000，宽度:32
 寄存器说明: Argument1寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cmd_argument : 32; /* bit[0-31]: The SD Command Argument is specified as bit39-8 of Command-Format. */
    } reg;
} SOC_EMMC_ARASAN_ARGUMENT1_UNION;
#endif
#define SOC_EMMC_ARASAN_ARGUMENT1_cmd_argument_START  (0)
#define SOC_EMMC_ARASAN_ARGUMENT1_cmd_argument_END    (31)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_TRANS_CMD_CTRL_UNION
 结构说明  : TRANS_CMD_CTRL 寄存器结构定义。地址偏移量:0x0C，初值:0x00000000，宽度:32
 寄存器说明: 传输控制和命令控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_enable           : 1;  /* bit[0]    : DMA enable:
                                                                0 - Disable
                                                                1 - Enable */
        unsigned int  block_count_enable   : 1;  /* bit[1]    : This bit is used to enable the Block count register, which is only relevant for multiple block transfers. When this bit is 0, the Block Count register is disabled, which is useful in executing an infinite transfer.
                                                                0 - Disable
                                                                1 - Enable */
        unsigned int  auto_cmd_enable      : 2;  /* bit[2-3]  : This field determines use of auto command functions
                                                                00b - Auto Command Disabled
                                                                01b - Auto CMD12 Enable
                                                                10b - Auto CMD23 Enable
                                                                11b - Reserved
                                                                There are two methods to stop Multiple-block read and write operation.
                                                                (1) Auto CMD12 Enable
                                                                Multiple-block read and write commands for memory require CMD12 to stop the operation. When this field is set to 01b, the Host Controller issues CMD12 automatically when last block transfer is completed. Auto CMD12 error is indicated to the Auto CMD Error Status register. The Host Driver shall not set this bit if the command does not require CMD12. 
                                                                (2) Auto CMD23 Enable
                                                                When this bit field is set to 10b, the Host Controller issues a CMD23 automatically before issuing a command specified in the Command Register The following conditions are required to use the Auto CMD23.
                                                                ? Auto CMD23 Supported (Host Controller Version is 3.00 or later)
                                                                ? A memory card that supports CMD23 (SCR[33]=1)
                                                                ? If DMA is used, it shall be ADMA.
                                                                ? Only when CMD18 or CMD25 is issued
                                                                By writing the Command register, the Host Controller issues a CMD23 first and then issues a command specified by the Command Index in Command register 32-bit block count value for CMD23 is set to SDMA System Address / Argument 2 register. */
        unsigned int  data_trans_direction : 1;  /* bit[4]    : This bit defines the direction of data transfers.
                                                                0 - Write (Host to Card)
                                                                1 - Read (Card to Host) */
        unsigned int  multi_block_select   : 1;  /* bit[5]    : This bit enables multiple block data transfers.
                                                                0 - Single Block
                                                                1 - Multiple Block */
        unsigned int  reserved_0           : 10; /* bit[6-15] : reserved. */
        unsigned int  response_type        : 2;  /* bit[16-17]: Response Type Select
                                                                00 - No Response
                                                                01 - Response length 136
                                                                10 - Response length 48
                                                                11 - Response length 48 check Busy after response */
        unsigned int  reserved_1           : 1;  /* bit[18]   : reserved. */
        unsigned int  cmd_crc_check        : 1;  /* bit[19]   : If this bit is set to 1, the HC shall check the CRC field in the response. If an error is detected, it is reported as a Command CRC Error. If this bit is set to 0, the CRC field is not checked.
                                                                0 - Disable
                                                                1 - Enable */
        unsigned int  cmd_index_check      : 1;  /* bit[20]   : If this bit is set to 1, the HC shall check the index field in the response to see if it has the same value as the command index. If it is not, it is reported as a Command Index Error. If this bit is set to 0, the Index field is not checked.
                                                                0 - Disable
                                                                1 - Enable */
        unsigned int  data_present_select  : 1;  /* bit[21]   : This bit is set to 1 to indicate that data is present and shall be transferred using the DAT line. If is set to 0 for the following:
                                                                1. Commands using only CMD line (ex. CMD52)
                                                                2. Commands with no data transfer but using busy signal on DAT[0] line (R1b or R5b ex. CMD38)
                                                                3. Resume Command
                                                                0 - No Data Present
                                                                1 - Data Present */
        unsigned int  cmd_type             : 2;  /* bit[22-23]: 00b - Normal
                                                                01b - Suspend
                                                                10b - Resume
                                                                11b - Abort */
        unsigned int  cmd_index            : 6;  /* bit[24-29]: This bit shall be set to the command number (CMD0-63, ACMD0-63). */
        unsigned int  reserved_2           : 2;  /* bit[30-31]: reserved. */
    } reg;
} SOC_EMMC_ARASAN_TRANS_CMD_CTRL_UNION;
#endif
#define SOC_EMMC_ARASAN_TRANS_CMD_CTRL_dma_enable_START            (0)
#define SOC_EMMC_ARASAN_TRANS_CMD_CTRL_dma_enable_END              (0)
#define SOC_EMMC_ARASAN_TRANS_CMD_CTRL_block_count_enable_START    (1)
#define SOC_EMMC_ARASAN_TRANS_CMD_CTRL_block_count_enable_END      (1)
#define SOC_EMMC_ARASAN_TRANS_CMD_CTRL_auto_cmd_enable_START       (2)
#define SOC_EMMC_ARASAN_TRANS_CMD_CTRL_auto_cmd_enable_END         (3)
#define SOC_EMMC_ARASAN_TRANS_CMD_CTRL_data_trans_direction_START  (4)
#define SOC_EMMC_ARASAN_TRANS_CMD_CTRL_data_trans_direction_END    (4)
#define SOC_EMMC_ARASAN_TRANS_CMD_CTRL_multi_block_select_START    (5)
#define SOC_EMMC_ARASAN_TRANS_CMD_CTRL_multi_block_select_END      (5)
#define SOC_EMMC_ARASAN_TRANS_CMD_CTRL_response_type_START         (16)
#define SOC_EMMC_ARASAN_TRANS_CMD_CTRL_response_type_END           (17)
#define SOC_EMMC_ARASAN_TRANS_CMD_CTRL_cmd_crc_check_START         (19)
#define SOC_EMMC_ARASAN_TRANS_CMD_CTRL_cmd_crc_check_END           (19)
#define SOC_EMMC_ARASAN_TRANS_CMD_CTRL_cmd_index_check_START       (20)
#define SOC_EMMC_ARASAN_TRANS_CMD_CTRL_cmd_index_check_END         (20)
#define SOC_EMMC_ARASAN_TRANS_CMD_CTRL_data_present_select_START   (21)
#define SOC_EMMC_ARASAN_TRANS_CMD_CTRL_data_present_select_END     (21)
#define SOC_EMMC_ARASAN_TRANS_CMD_CTRL_cmd_type_START              (22)
#define SOC_EMMC_ARASAN_TRANS_CMD_CTRL_cmd_type_END                (23)
#define SOC_EMMC_ARASAN_TRANS_CMD_CTRL_cmd_index_START             (24)
#define SOC_EMMC_ARASAN_TRANS_CMD_CTRL_cmd_index_END               (29)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_CMD_RES0_UNION
 结构说明  : CMD_RES0 寄存器结构定义。地址偏移量:0x10，初值:0x00000000，宽度:32
 寄存器说明: CMD回复0寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cmd_response0 : 32; /* bit[0-31]: Command Response 0~31bit */
    } reg;
} SOC_EMMC_ARASAN_CMD_RES0_UNION;
#endif
#define SOC_EMMC_ARASAN_CMD_RES0_cmd_response0_START  (0)
#define SOC_EMMC_ARASAN_CMD_RES0_cmd_response0_END    (31)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_CMD_RES1_UNION
 结构说明  : CMD_RES1 寄存器结构定义。地址偏移量:0x14，初值:0x00000000，宽度:32
 寄存器说明: CMD回复1寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cmd_response1 : 32; /* bit[0-31]: Command Response 32~63bit */
    } reg;
} SOC_EMMC_ARASAN_CMD_RES1_UNION;
#endif
#define SOC_EMMC_ARASAN_CMD_RES1_cmd_response1_START  (0)
#define SOC_EMMC_ARASAN_CMD_RES1_cmd_response1_END    (31)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_CMD_RES2_UNION
 结构说明  : CMD_RES2 寄存器结构定义。地址偏移量:0x18，初值:0x00000000，宽度:32
 寄存器说明: CMD回复2寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cmd_response2 : 32; /* bit[0-31]: Command Response 64~95bit */
    } reg;
} SOC_EMMC_ARASAN_CMD_RES2_UNION;
#endif
#define SOC_EMMC_ARASAN_CMD_RES2_cmd_response2_START  (0)
#define SOC_EMMC_ARASAN_CMD_RES2_cmd_response2_END    (31)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_CMD_RES3_UNION
 结构说明  : CMD_RES3 寄存器结构定义。地址偏移量:0x1C，初值:0x00000000，宽度:32
 寄存器说明: CMD回复3寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cmd_response3 : 32; /* bit[0-31]: Command Response 96~127bit */
    } reg;
} SOC_EMMC_ARASAN_CMD_RES3_UNION;
#endif
#define SOC_EMMC_ARASAN_CMD_RES3_cmd_response3_START  (0)
#define SOC_EMMC_ARASAN_CMD_RES3_cmd_response3_END    (31)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_BUFFER_DATA_UNION
 结构说明  : BUFFER_DATA 寄存器结构定义。地址偏移量:0x20，初值:0x00000000，宽度:32
 寄存器说明: 数据寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  buffer_data : 32; /* bit[0-31]: The Host Controller Buffer can be accessed through this 32-bit Data Port Register. */
    } reg;
} SOC_EMMC_ARASAN_BUFFER_DATA_UNION;
#endif
#define SOC_EMMC_ARASAN_BUFFER_DATA_buffer_data_START  (0)
#define SOC_EMMC_ARASAN_BUFFER_DATA_buffer_data_END    (31)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_PRESENT_STATE_UNION
 结构说明  : PRESENT_STATE 寄存器结构定义。地址偏移量:0x24，初值:0x1FF00000，宽度:32
 寄存器说明: 工作状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cmd_inhibit_cmd       : 1;  /* bit[0]    : If this bit is 0, it indicates the CMD line is not in use 
                                                                 and the HC can issue a SD command using the 
                                                                 CMD line.
                                                                 This bit is set immediately after the 
                                                                 Command register (00Fh) is written. This bit is 
                                                                 cleared when the command response is received.  */
        unsigned int  cmd_inhibit_data      : 1;  /* bit[1]    : This status bit is generated if either the DAT Line Active or the Read transfer Active is set to 1. If this 
                                                                 bit is 0, it indicates the HC can issue the next SD command. Commands with busy signal belong to Command Inhibit (DAT) (ex. R1b, R5b type). 
                                                                 Changing from 1 to 0 generates a Transfer Complete interrupt in the Normal interrupt status register.
                                                                 
                                                                 Note: The SD Host Driver can save registers in 
                                                                 the range of 000-00Dh for a suspend transaction 
                                                                 after this bit has changed from 1 to 0.
                                                                 1 - cannot issue command which uses the DAT line
                                                                 0 - Can issue command which uses the DAT line */
        unsigned int  data_line_active      : 1;  /* bit[2]    : This bit indicates whether one of the DAT line on SD bus is in use.
                                                                 1 - DAT line active
                                                                 0 - DAT line inactive */
        unsigned int  retuning_request      : 1;  /* bit[3]    : 1 Sampling clock needs re-tuning
                                                                 0 Fixed or well tuned sampling clock */
        unsigned int  reserved_0            : 4;  /* bit[4-7]  : reserved. */
        unsigned int  write_transfer_active : 1;  /* bit[8]    : This status indicates a write transfer is active.
                                                                 1 - transferring data
                                                                 0 - No valid data */
        unsigned int  read_transfer_active  : 1;  /* bit[9]    : This status is used for detecting completion of a 
                                                                 read transfer.
                                                                 1 - Transferring data
                                                                 0 - No valid data */
        unsigned int  buffer_write_enable   : 1;  /* bit[10]   : This status is used for non-DMA write transfers. 
                                                                 0 - Write Disable
                                                                 1 - Write Enable. */
        unsigned int  buffer_read_enable    : 1;  /* bit[11]   : This status is used for non-DMA read transfers. 
                                                                 0 - Read Disable
                                                                 1 - Read Enable. */
        unsigned int  reserved_1            : 4;  /* bit[12-15]: reserved. */
        unsigned int  card_inserted         : 1;  /* bit[16]   : 0 - Reset or Debouncing or No Card
                                                                 1 - Card Inserted */
        unsigned int  card_state_stable     : 1;  /* bit[17]   : 0 - Reset of Debouncing
                                                                 1 - No Card or Inserted */
        unsigned int  card_detect_level     : 1;  /* bit[18]   : This bit reflects the inverse value of the SDCD# pin.
                                                                 0 - No Card present (SDCD# = 1)
                                                                 1 - Card present (SDCD# = 0) */
        unsigned int  write_protect_level   : 1;  /* bit[19]   : write_protect_level */
        unsigned int  data3_0_line_level    : 4;  /* bit[20-23]: This status is used to check DAT line level to recover from errors, and for debugging. This is especially useful in detecting the busy signal level from DAT[0].
                                                                 D23 - DAT[3]
                                                                 D22 - DAT[2]
                                                                 D21 - DAT[1]
                                                                 D20 - DAT[0] */
        unsigned int  cmd_line_level        : 1;  /* bit[24]   : This status is used to check CMD line level to recover from errors, and for debugging. */
        unsigned int  data7_4_line_level    : 4;  /* bit[25-28]: This status is used to check DAT line level to recover from errors, and for debugging.
                                                                 D28 - DAT[7]
                                                                 D27 - DAT[6]
                                                                 D26 - DAT[5]
                                                                 D25 - DAT[4] */
        unsigned int  reserved_2            : 3;  /* bit[29-31]: reserved. */
    } reg;
} SOC_EMMC_ARASAN_PRESENT_STATE_UNION;
#endif
#define SOC_EMMC_ARASAN_PRESENT_STATE_cmd_inhibit_cmd_START        (0)
#define SOC_EMMC_ARASAN_PRESENT_STATE_cmd_inhibit_cmd_END          (0)
#define SOC_EMMC_ARASAN_PRESENT_STATE_cmd_inhibit_data_START       (1)
#define SOC_EMMC_ARASAN_PRESENT_STATE_cmd_inhibit_data_END         (1)
#define SOC_EMMC_ARASAN_PRESENT_STATE_data_line_active_START       (2)
#define SOC_EMMC_ARASAN_PRESENT_STATE_data_line_active_END         (2)
#define SOC_EMMC_ARASAN_PRESENT_STATE_retuning_request_START       (3)
#define SOC_EMMC_ARASAN_PRESENT_STATE_retuning_request_END         (3)
#define SOC_EMMC_ARASAN_PRESENT_STATE_write_transfer_active_START  (8)
#define SOC_EMMC_ARASAN_PRESENT_STATE_write_transfer_active_END    (8)
#define SOC_EMMC_ARASAN_PRESENT_STATE_read_transfer_active_START   (9)
#define SOC_EMMC_ARASAN_PRESENT_STATE_read_transfer_active_END     (9)
#define SOC_EMMC_ARASAN_PRESENT_STATE_buffer_write_enable_START    (10)
#define SOC_EMMC_ARASAN_PRESENT_STATE_buffer_write_enable_END      (10)
#define SOC_EMMC_ARASAN_PRESENT_STATE_buffer_read_enable_START     (11)
#define SOC_EMMC_ARASAN_PRESENT_STATE_buffer_read_enable_END       (11)
#define SOC_EMMC_ARASAN_PRESENT_STATE_card_inserted_START          (16)
#define SOC_EMMC_ARASAN_PRESENT_STATE_card_inserted_END            (16)
#define SOC_EMMC_ARASAN_PRESENT_STATE_card_state_stable_START      (17)
#define SOC_EMMC_ARASAN_PRESENT_STATE_card_state_stable_END        (17)
#define SOC_EMMC_ARASAN_PRESENT_STATE_card_detect_level_START      (18)
#define SOC_EMMC_ARASAN_PRESENT_STATE_card_detect_level_END        (18)
#define SOC_EMMC_ARASAN_PRESENT_STATE_write_protect_level_START    (19)
#define SOC_EMMC_ARASAN_PRESENT_STATE_write_protect_level_END      (19)
#define SOC_EMMC_ARASAN_PRESENT_STATE_data3_0_line_level_START     (20)
#define SOC_EMMC_ARASAN_PRESENT_STATE_data3_0_line_level_END       (23)
#define SOC_EMMC_ARASAN_PRESENT_STATE_cmd_line_level_START         (24)
#define SOC_EMMC_ARASAN_PRESENT_STATE_cmd_line_level_END           (24)
#define SOC_EMMC_ARASAN_PRESENT_STATE_data7_4_line_level_START     (25)
#define SOC_EMMC_ARASAN_PRESENT_STATE_data7_4_line_level_END       (28)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_HOST_CTRL1_UNION
 结构说明  : HOST_CTRL1 寄存器结构定义。地址偏移量:0x28，初值:0x00000000，宽度:32
 寄存器说明: 控制1寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  led_control                  : 1;  /* bit[0]    : 无用。 */
        unsigned int  data_transfer_width          : 1;  /* bit[1]    : This bit selects the data width of the HC. The HD shall select it to match the data width of the SD card.
                                                                        1 - 4 bit mode
                                                                        0 - 1 bit mode */
        unsigned int  high_speed_enable            : 1;  /* bit[2]    : This bit is optional. Before setting this bit, the HD shall check the High Speed Support in the capabilities register. If this bit is set to 0 (default), the HC out-
                                                                        puts CMD line and DAT lines at the falling edge of the SD clock (up to 25 MHz/20MHz for MMC). If this bit is set to 1, the HC outputs CMD line and DAT lines at the rising edge of the SD clock (up to 50 MHz for SD/52MHz for MMC) / 208Mhz (for SD3.0)
                                                                        切换时先关时钟,切换完成打开时钟。
                                                                        If Preset Value Enable in the Host Control 2 register is set to 1, Host Driver needs to reset SD Clock Enable before changing this field to avoid generating clock glitches. After setting this field, the Host Driver sets SD Clock Enable again
                                                                        1 - High Speed Mode
                                                                        0 - Normal Speed Mode */
        unsigned int  dma_select                   : 2;  /* bit[3-4]  : One of supported DMA modes can be selected. The host driver shall check support of DMA modes by referring the Capabilities register.
                                                                        00 - SDMA is selected
                                                                        01 - 32-bit Address ADMA1 is selected
                                                                        10 -32-bit Address ADMA2 is selected
                                                                        11 - 64-bit Address ADMA2 is selected */
        unsigned int  extended_data_transfer_width : 1;  /* bit[5]    : If a device supports 8-bit bus mode, this bit may be set to 1. If this bit is 0, bus width is controlled by Data 
                                                                        Transfer Width in the Host Control 1 register. */
        unsigned int  card_detect_test_level       : 1;  /* bit[6]    : This bit is enabled while the Card Detect Signal Selection is set to 1 and it indicates card inserted or not.
                                                                        Generates (card ins or card removal)interrupt when the normal int sts enable bit is set.
                                                                        1 - Card Inserted
                                                                        0 - No Card */
        unsigned int  card_detect_sig_dect         : 1;  /* bit[7]    : This bit selects source for card detec-
                                                                        tion.
                                                                        1- The card detect test level is selected
                                                                        0 -SDCD# is selected (for normal use) */
        unsigned int  sd_bus_power                 : 1;  /* bit[8]    : 无用。 */
        unsigned int  sd_bus_voltage_sel           : 3;  /* bit[9-11] : 无用。 */
        unsigned int  emmc_devive_hw_rst_n         : 1;  /* bit[12]   : 器件的硬件复位。
                                                                        0： 给器件的复位信号为1，不复位；
                                                                        1： 给器件的复位信号为0，复位器件。 
                                                                        注：按协议器件应检测复位信号的下降沿来复位器件。 */
        unsigned int  reserved_0                   : 3;  /* bit[13-15]: reserved. */
        unsigned int  stop_at_block_gap            : 1;  /* bit[16]   : This bit is used to stop executing a transaction at the next block gap for non- DMA,SDMA and ADMA transfers. Until the transfer complete is set to 1, indicating a transfer completion the HD shall leave this bit set to 1. Clearing both the Stop At Block Gap Request and Continue Request shall not cause the transaction to restart. Read Wait is used to stop the read transaction at the block gap. The HC shall honour Stop At Block Gap Request for write transfers, but for read transfers it requires that the SD card support Read Wait. 
                                                                        Therefore the HD shall not set this bit during read transfers unless the SD card supports Read Wait and has set Read Wait Control to 1. In case of write transfers in which the HD writes data to the Buffer Data Port register, the HD shall set this bit after all block data is written. If this bit is set to 1, the HD shall not write data to Buffer data port register. This bit affects Read Transfer Active, Write Transfer Active, DAT line 
                                                                        active and Command Inhibit (DAT) in the Present State register.
                                                                        1 - Stop
                                                                        0 - Transfer */
        unsigned int  continue_request             : 1;  /* bit[17]   : read & write, auto cleared when operation is done.
                                                                        This bit is used to restart a transaction which was stopped using the Stop At Block Gap Request. To cancel stop at the block gap, set Stop At block Gap Request to 0 and set this bit to restart the transfer.
                                                                        The HC automatically clears this bit in either of the following cases:
                                                                        1) In the case of a read transaction, the DAT Line Active changes from 0 to 1 as a read transaction restarts.
                                                                        2) In the case of a write transaction, the Write transfer active changes from 0 to 1 as the write transaction restarts.
                                                                        Therefore it is not necessary for Host driver to set this bit to 0. If Stop At Block Gap Request is set to 1, any write to this bit is ignored.
                                                                        1 - Restart
                                                                        0 - Ignored */
        unsigned int  read_wait_control            : 1;  /* bit[18]   : The read wait function is optional for SDIO cards.  */
        unsigned int  intrrup_at_block_gap         : 1;  /* bit[19]   : This bit is valid only in 4-bit mode of the SDIO card and selects a sample point in the interrupt cycle. */
        unsigned int  spi_mode                     : 1;  /* bit[20]   : SPI mode enable bit.
                                                                        1- SPI mode
                                                                        0 - SD mode */
        unsigned int  boot_en                      : 1;  /* bit[21]   : To start boot code access
                                                                        1- To start boot code access
                                                                        0 - To stop boot code access */
        unsigned int  alt_boot_en                  : 1;  /* bit[22]   : To start boot code access in alternative mode.
                                                                        1- To start alternate boot mode access
                                                                        0 - To stop alternate boot mode access */
        unsigned int  boot_ack_chk                 : 1;  /* bit[23]   : To check for the boot acknowledge in boot operation.
                                                                        1 - wait for boot ack from eMMC card
                                                                        0 - Will not wait for boot ack from eMMC card */
        unsigned int  wakeup_en_sd_intrrupt        : 1;  /* bit[24]   : This bit enables wakeup event via Card Interrupt assertion in the Normal Interrupt Status register. 
                                                                        This bit can be set to 1 if FN_WUS (Wake Up Support) in CIS is set to 1.
                                                                        1 - Enable
                                                                        0 - Disable */
        unsigned int  wakeup_en_sd_instert         : 1;  /* bit[25]   : This bit enables wakeup event via Card Insertion assertion in the Normal Interrupt Status register. 
                                                                        FN_WUS (Wake up Support) in CIS does not affect this bit.
                                                                        1 - Enable
                                                                        0 - Disable */
        unsigned int  wakeup_en_sd_removal         : 1;  /* bit[26]   : This bit enables wakeup event via Card Removal assertion in the Normal Interrupt Status register. 
                                                                        FN_WUS (Wake up Support) in CIS does not affect this bit.
                                                                        1 - Enable
                                                                        0 - Disable */
        unsigned int  reserved_1                   : 5;  /* bit[27-31]: reserved. */
    } reg;
} SOC_EMMC_ARASAN_HOST_CTRL1_UNION;
#endif
#define SOC_EMMC_ARASAN_HOST_CTRL1_led_control_START                   (0)
#define SOC_EMMC_ARASAN_HOST_CTRL1_led_control_END                     (0)
#define SOC_EMMC_ARASAN_HOST_CTRL1_data_transfer_width_START           (1)
#define SOC_EMMC_ARASAN_HOST_CTRL1_data_transfer_width_END             (1)
#define SOC_EMMC_ARASAN_HOST_CTRL1_high_speed_enable_START             (2)
#define SOC_EMMC_ARASAN_HOST_CTRL1_high_speed_enable_END               (2)
#define SOC_EMMC_ARASAN_HOST_CTRL1_dma_select_START                    (3)
#define SOC_EMMC_ARASAN_HOST_CTRL1_dma_select_END                      (4)
#define SOC_EMMC_ARASAN_HOST_CTRL1_extended_data_transfer_width_START  (5)
#define SOC_EMMC_ARASAN_HOST_CTRL1_extended_data_transfer_width_END    (5)
#define SOC_EMMC_ARASAN_HOST_CTRL1_card_detect_test_level_START        (6)
#define SOC_EMMC_ARASAN_HOST_CTRL1_card_detect_test_level_END          (6)
#define SOC_EMMC_ARASAN_HOST_CTRL1_card_detect_sig_dect_START          (7)
#define SOC_EMMC_ARASAN_HOST_CTRL1_card_detect_sig_dect_END            (7)
#define SOC_EMMC_ARASAN_HOST_CTRL1_sd_bus_power_START                  (8)
#define SOC_EMMC_ARASAN_HOST_CTRL1_sd_bus_power_END                    (8)
#define SOC_EMMC_ARASAN_HOST_CTRL1_sd_bus_voltage_sel_START            (9)
#define SOC_EMMC_ARASAN_HOST_CTRL1_sd_bus_voltage_sel_END              (11)
#define SOC_EMMC_ARASAN_HOST_CTRL1_emmc_devive_hw_rst_n_START          (12)
#define SOC_EMMC_ARASAN_HOST_CTRL1_emmc_devive_hw_rst_n_END            (12)
#define SOC_EMMC_ARASAN_HOST_CTRL1_stop_at_block_gap_START             (16)
#define SOC_EMMC_ARASAN_HOST_CTRL1_stop_at_block_gap_END               (16)
#define SOC_EMMC_ARASAN_HOST_CTRL1_continue_request_START              (17)
#define SOC_EMMC_ARASAN_HOST_CTRL1_continue_request_END                (17)
#define SOC_EMMC_ARASAN_HOST_CTRL1_read_wait_control_START             (18)
#define SOC_EMMC_ARASAN_HOST_CTRL1_read_wait_control_END               (18)
#define SOC_EMMC_ARASAN_HOST_CTRL1_intrrup_at_block_gap_START          (19)
#define SOC_EMMC_ARASAN_HOST_CTRL1_intrrup_at_block_gap_END            (19)
#define SOC_EMMC_ARASAN_HOST_CTRL1_spi_mode_START                      (20)
#define SOC_EMMC_ARASAN_HOST_CTRL1_spi_mode_END                        (20)
#define SOC_EMMC_ARASAN_HOST_CTRL1_boot_en_START                       (21)
#define SOC_EMMC_ARASAN_HOST_CTRL1_boot_en_END                         (21)
#define SOC_EMMC_ARASAN_HOST_CTRL1_alt_boot_en_START                   (22)
#define SOC_EMMC_ARASAN_HOST_CTRL1_alt_boot_en_END                     (22)
#define SOC_EMMC_ARASAN_HOST_CTRL1_boot_ack_chk_START                  (23)
#define SOC_EMMC_ARASAN_HOST_CTRL1_boot_ack_chk_END                    (23)
#define SOC_EMMC_ARASAN_HOST_CTRL1_wakeup_en_sd_intrrupt_START         (24)
#define SOC_EMMC_ARASAN_HOST_CTRL1_wakeup_en_sd_intrrupt_END           (24)
#define SOC_EMMC_ARASAN_HOST_CTRL1_wakeup_en_sd_instert_START          (25)
#define SOC_EMMC_ARASAN_HOST_CTRL1_wakeup_en_sd_instert_END            (25)
#define SOC_EMMC_ARASAN_HOST_CTRL1_wakeup_en_sd_removal_START          (26)
#define SOC_EMMC_ARASAN_HOST_CTRL1_wakeup_en_sd_removal_END            (26)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_CLOCK_RESET_CTRL_UNION
 结构说明  : CLOCK_RESET_CTRL 寄存器结构定义。地址偏移量:0x2C，初值:0x00000000，宽度:32
 寄存器说明: 时钟控制和复位寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  internal_clk_enable      : 1;  /* bit[0]    : This bit is set to 0 when the HD is not using the HC or the HC awaits a wakeup event. The HC should stop its internal clock to go very low power state. Still, registers shall be able to be read and written. Clock starts to oscillate when this bit is set to 1. When clock oscillation is stable, the HC shall set Internal Clock Stable in this register to 1. This bit shall not affect card detection. 
                                                                    1 - Oscillate
                                                                    0 - Stop */
        unsigned int  internal_clk_stable      : 1;  /* bit[1]    : This bit is set to 1 when SD clock is stable after writing to Internal Clock Enable in this register to 1. The SD Host Driver shall wait to set SD Clock Enable until this bit is set to 1. 
                                                                    Note: This is useful when using PLL for a clock oscillator that requires setup time.
                                                                    1 - Ready
                                                                    0 - Not Ready */
        unsigned int  sd_clk_en                : 1;  /* bit[2]    : The HC shall stop SDCLK when writing this bit to 0. SDCLK frequency Select can be changed when this bit is 0. Then, the HC shall maintain the same clock frequency until SDCLK is stopped (Stop at SDCLK = 0). If the HC detects the No Card state, this bit shall be cleared.
                                                                    1 - Enable
                                                                    0 - Disable */
        unsigned int  reserved_0               : 2;  /* bit[3-4]  : reserved. */
        unsigned int  clock_gen_sel            : 1;  /* bit[5]    : This bit is used to select the clock generator mode in SDCLK Frequency Select.
                                                                    If the Programmable Clock Mode is supported (non-zero value is set to Clock Multiplier in the Capabilities register), this bit attribute is RW, and if not supported, this bit attribute is RO and zero is read.
                                                                    This bit depends on the setting of Preset Value Enable in the Host Control 2 register.
                                                                    If the Preset Value Enable = 0, this bit is set by Host Driver.
                                                                    If the Preset Value Enable = 1, this bit is utomatically set to a value specified in one of Preset Value registers.
                                                                    1 Programmable Clock Mode
                                                                    0 Divided Clock Mode */
        unsigned int  upper_bits_sdclk_frq_sel : 2;  /* bit[6-7]  : (2) 10-bit Divided Clock Mode
                                                                    Host Controller Version 3.00 supports this mandatory mode instead of the 8-bit Divided Clock Mode. The length of divider is extended to10 bits and all divider values shall be supported.
                                                                    3FFh --1/2046 Divided Clock
                                                                    N -------1/2N Divided Clock (Duty 50%)
                                                                    002h -- 1/4 Divided Clock
                                                                    001h ---1/2 Divided Clock
                                                                    000h --- Base Clock (10MHz-254MHz)
                                                                    Bit 07-06 is assigned to bit 09-08 of clock divider in SDCLK Frequency Select */
        unsigned int  clock_freq_sel           : 8;  /* bit[8-15] : This register is used to select the frequency of the SDCLK pin. The frequency is not programmed directly; rather this register holds the divisor of the Base Clock Frequency For SD clock in the capabilities register. Only the following settings are allowed.
                                                                    (1) 8-bit Divided Clock Mode
                                                                    80h - base clock divided by 256
                                                                    ...
                                                                    04h - base clock divided by 8
                                                                    02h - base clock divided by 4
                                                                    01h - base clock divided by 2
                                                                    00h - base clock(10MHz-63MHz)
                                                                    Setting 00h specifies the highest frequency of the SD Clock. When setting multiple bits, the most significant bit is used as the divisor. But multiple bits should not be set. The two default divider values can be calculated by the frequency that is defined by the Base Clock Frequency For SD Clock in the Capabilities register.
                                                                    1) 25 MHz divider value
                                                                    2) 400 KHz divider value
                                                                    The frequency of the SDCLK is set by the following formula:Clock Frequency = (Baseclock) / divisor.
                                                                    Thus choose the smallest possible divisor which results in a clock frequency that is less than or equal to the target frequency.
                                                                    Maximum Frequency for SD = 50Mhz (base clock)
                                                                    Maximum Frequency for MMC = 52Mhz (base clock)
                                                                    Minimum Frequency = 195.3125Khz (50Mhz / 256), same calculation for MMC also */
        unsigned int  data_timeout_cnt_value   : 3;  /* bit[16-18]: This value determines the interval by which DAT line time-outs are detected. Refer to the Data Time-out Error in the Error Interrupt Status register for information on factors that dictate time-out generation. Time-out clock frequency will be generated by dividing the sdclockTMCLK by this value. When setting this register, prevent inadvertent time-out events by clearing the Data Time-out Error Status Enable (in the 
                                                                    Error Interrupt Status Enable register).
                                                                    1111 - Reserved
                                                                    1110 - TMCLK * 2^27
                                                                    ------------------------------
                                                                    ------------------------------
                                                                    0001 - TMCLK * 2^14
                                                                    0000 - TMCLK * 2^13 */
        unsigned int  reserved_1               : 5;  /* bit[19-23]: reserved. */
        unsigned int  soft_reset_all           : 1;  /* bit[24]   : This reset affects the entire HC except for the card detection circuit. Register bits of type ROC, RW, RW1C, RWAC are cleared to 0. During its initialization, the 
                                                                    HD shall set this bit to 1 to reset the HC. 
                                                                    The HC shall reset this bit to 0 when capabilities registers are valid and the HD can read them. Additional use of Software Reset For All may not affect the value of the Capabilities registers. If this bit is set to 1, the SD card shall reset itself and must be re initialized by the HD.
                                                                    1 - Reset
                                                                    0 - Work */
        unsigned int  soft_reset_cmdline       : 1;  /* bit[25]   : Only part of command circuit is reset.
                                                                    The following registers and bits are 
                                                                    cleared by this bit:
                                                                    Present State register
                                                                     -Command Inhibit (CMD)
                                                                    Normal Interrupt Status register
                                                                     -Command Complete
                                                                    1 - Reset
                                                                    0 - Work */
        unsigned int  soft_reset_dataline      : 1;  /* bit[26]   : Only part of data circuit is reset. The following registers and bits are cleared by this bit:
                                                                    Buffer Data Port Register
                                                                     -Buffer is cleared and Initialized.
                                                                    Present State register
                                                                     -Buffer read Enable
                                                                     -Buffer write Enable
                                                                     -Read Transfer Active
                                                                     -Write Transfer Active
                                                                     -DAT Line Active
                                                                     -Command Inhibit (DAT)
                                                                    Block Gap Control register
                                                                     -Continue Request
                                                                     -Stop At Block Gap Request
                                                                    Normal Interrupt Status register
                                                                    1 - Reset
                                                                    0 - Work */
        unsigned int  reserved_2               : 5;  /* bit[27-31]: reserved. */
    } reg;
} SOC_EMMC_ARASAN_CLOCK_RESET_CTRL_UNION;
#endif
#define SOC_EMMC_ARASAN_CLOCK_RESET_CTRL_internal_clk_enable_START       (0)
#define SOC_EMMC_ARASAN_CLOCK_RESET_CTRL_internal_clk_enable_END         (0)
#define SOC_EMMC_ARASAN_CLOCK_RESET_CTRL_internal_clk_stable_START       (1)
#define SOC_EMMC_ARASAN_CLOCK_RESET_CTRL_internal_clk_stable_END         (1)
#define SOC_EMMC_ARASAN_CLOCK_RESET_CTRL_sd_clk_en_START                 (2)
#define SOC_EMMC_ARASAN_CLOCK_RESET_CTRL_sd_clk_en_END                   (2)
#define SOC_EMMC_ARASAN_CLOCK_RESET_CTRL_clock_gen_sel_START             (5)
#define SOC_EMMC_ARASAN_CLOCK_RESET_CTRL_clock_gen_sel_END               (5)
#define SOC_EMMC_ARASAN_CLOCK_RESET_CTRL_upper_bits_sdclk_frq_sel_START  (6)
#define SOC_EMMC_ARASAN_CLOCK_RESET_CTRL_upper_bits_sdclk_frq_sel_END    (7)
#define SOC_EMMC_ARASAN_CLOCK_RESET_CTRL_clock_freq_sel_START            (8)
#define SOC_EMMC_ARASAN_CLOCK_RESET_CTRL_clock_freq_sel_END              (15)
#define SOC_EMMC_ARASAN_CLOCK_RESET_CTRL_data_timeout_cnt_value_START    (16)
#define SOC_EMMC_ARASAN_CLOCK_RESET_CTRL_data_timeout_cnt_value_END      (18)
#define SOC_EMMC_ARASAN_CLOCK_RESET_CTRL_soft_reset_all_START            (24)
#define SOC_EMMC_ARASAN_CLOCK_RESET_CTRL_soft_reset_all_END              (24)
#define SOC_EMMC_ARASAN_CLOCK_RESET_CTRL_soft_reset_cmdline_START        (25)
#define SOC_EMMC_ARASAN_CLOCK_RESET_CTRL_soft_reset_cmdline_END          (25)
#define SOC_EMMC_ARASAN_CLOCK_RESET_CTRL_soft_reset_dataline_START       (26)
#define SOC_EMMC_ARASAN_CLOCK_RESET_CTRL_soft_reset_dataline_END         (26)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_INTR_ERROR_STATUS_UNION
 结构说明  : INTR_ERROR_STATUS 寄存器结构定义。地址偏移量:0x30，初值:0x00000000，宽度:32
 寄存器说明: 中断和错误状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cmd_complete            : 1;  /* bit[0]    : This bit is set when we get the end bit of the 
                                                                   command response (Except Auto CMD12 and Auto CMD23)
                                                                   Note: Command Time-out Error has higher priority than Command Complete. If both are set to 1, it can be considered that the response was not received correctly.
                                                                   0 - No Command Complete
                                                                   1 - Command Complete */
        unsigned int  transfer_complete       : 1;  /* bit[1]    : 1.This bit is set when a read / write transaction is completed.
                                                                   1) Read Transaction:
                                                                   This bit is set at the falling edge of Read Transfer Active Status.
                                                                   There are two cases in which the Interrupt is generated. The first is when a data transfer is completed as specified by data length (After the last data has been read to the Host System). The second is when data has stopped at the block gap and completed the data transfer by setting the Stop At Block Gap Request in the Block Gap Control Register (After valid data has been read to the Host System).
                                                                   2) Write Transaction:
                                                                   This bit is set at the falling edge of the DAT Line Active Status.
                                                                   There are two cases in which the Interrupt is generated. The first is when the last data is written to the card as specified by data length and Busy signal is released. The second is when data transfers are stopped at the block gap by setting Stop At Block Gap Request in the Block Gap Control Register and data transfers completed. (After valid data is written to the SD card and the busy signal is 
                                                                   released).
                                                                   3) In case of command with busy:
                                                                   This bit is set when busy is deasserted.
                                                                   Note: Transfer Complete has higher priority than Data Time-out Error. If both bits are set to 1, the data transfer can be considered complete.
                                                                   Note: While performing tuning procedure (Execute Tuning is set to 1), Transfer complete is not set to 1
                                                                   0 - No Data Transfer Complete
                                                                   1 - Data Transfer Complete */
        unsigned int  bloack_gap_event        : 1;  /* bit[2]    : If the Stop At Block Gap Request in the Block Gap Control Register is set, this bit is set. 
                                                                   Read Transaction:
                                                                   This bit is set at the falling edge of the DAT Line Active Status (When the ransaction is stopped at SD Bus timing. The Read Wait must be supported inorder to use this function).
                                                                   Write Transaction:
                                                                   This bit is set at the falling edge of Write Transfer Active Status (After getting CRC status at SD Bus timing).
                                                                   0 - No Block Gap Event
                                                                   1 - Transaction stopped at Block Gap */
        unsigned int  dma_imterrupt           : 1;  /* bit[3]    : This status is set if the HC detects the Host DMA Buffer Boundary in the Block Size 
                                                                   regiser.
                                                                   0 - No DMA Interrupt
                                                                   1 - DMA Interrupt is Generated  */
        unsigned int  buffer_write_ready      : 1;  /* bit[4]    : This status is set if the Buffer Write Enable changes from 0 to 1.
                                                                   0 - Not Ready to Write Buffer.
                                                                   1 - Ready to Write Buffer. */
        unsigned int  buffer_read_ready       : 1;  /* bit[5]    : This status is set if the Buffer Read Enable changes from 0 to 1.
                                                                   Buffer Read Ready is set to 1 for every CMD19 execution in tuning procedure.
                                                                   0 - Not Ready to read Buffer.
                                                                   1 - Ready to read Buffer. */
        unsigned int  card_insertion          : 1;  /* bit[6]    : This status is set if the Card Inserted in the Present State register changes from 0 to 1. When the HD writes this bit to 1 to clear this status the status of the Card Inserted in the Present State register should be confirmed. Because the card detect may possibly be changed when the HD clear this bit an Interrupt event may not be generated.
                                                                   0 - Card State Stable or Debouncing
                                                                   1 - Card Inserted */
        unsigned int  card_removal            : 1;  /* bit[7]    : This status is set if the Card Inserted in the Present State register changes from 0 to 1. When the HD writes this bit to 1 to clear this status the status of the Card Inserted in the Present State register should be confirmed. Because the card detect may possibly be changed when the HD clear this bit an Interrupt event may not be generated.
                                                                   0 - Card State Stable or Debouncing
                                                                   1 - Card Inserted */
        unsigned int  card_interrupt          : 1;  /* bit[8]    : Writing this bit to 1 does not clear this bit. It is cleared by resetting the SD card interrupt factor. In 1-bit mode, the HC shall detect the Card Interrupt without SD Clock to support wakeup.In 4-bit mode, the card interrupt signal is sampled during the interrupt cycle, so there are some sample delays between the interrupt signal from the card and the interrupt to the Host system.when this status has been set and the HD needs to start this interrupt service, Card Interupt Status Enable in the Normal Interrupt Status register shall be set to 0 in order to clear the card interrupt statuses latched in the HC and stop driving the Host System. After completion of the card interrupt service (the reset factor in the SD card and the interrupt signal may not be asserted), set Card Interrupt Status Enable to 1 and start sampling the interrupt signal again.
                                                                   Interrupt detected by DAT[1] is supported when there is a card per slot. In case of 
                                                                   shared bus, interrupt pins are used to detect interrupts. If 000b is set to interrupt Pin Select in the Shared Bus Control register, this status is effective. Non-zero value is set to Interrupt Pin Select, INT_A, INT_B or INT_C is then used to device interrupts.
                                                                   0 - No Card Interrupt 
                                                                   1 - Generate Card Interrupt */
        unsigned int  int_a                   : 1;  /* bit[9]    : This status is set if INT_A is enabled and INT_A# pin is in low level. Writing this bit to 1 does not clear this bit. It is cleared by resetting the INT_A interrupt factor
                                                                   NOTE : INT_A, INT_B, and INT_C are to be implemented based on the Application Requirements. By default these are not implemented as there is no specific requirement from Customers. */
        unsigned int  int_b                   : 1;  /* bit[10]   : This status is set if INT_B is enabled and INT_B# pin is in low level. Writing this bit to 1 does not clear this bit. It is cleared by resetting the INT_B interrupt factor */
        unsigned int  int_c                   : 1;  /* bit[11]   : This status is set if INT_C is enabled and INT_C# pin is in low level. Writing this bit to 1 does not clear this bit. It is cleared by resetting the INT_C interrupt factor. */
        unsigned int  retuning_event          : 1;  /* bit[12]   : This status is set if Re-Tuning Request in the Present State register changes from 0 to 1.
                                                                   Host Controller requests Host Driver to perform re-tuning for next data transfer. Current data transfer (not large block count) can be completed without re-tuning.
                                                                   1 Re-Tuning should be performed
                                                                   0 Re-Tuning is not required */
        unsigned int  boot_ack_rev            : 1;  /* bit[13]   : This status is set if the boot acknowledge is received from device.
                                                                   0 - Boot ack is not received.
                                                                   1 - Boot ack is received. */
        unsigned int  boot_terminate_intrrupt : 1;  /* bit[14]   : This status is set if the boot operation get terminated
                                                                   0 - Boot operation is not terminated.
                                                                   1 - Boot operation is terminated */
        unsigned int  error_interrupt         : 1;  /* bit[15]   : If any of the bits in the Error Interrupt Status Register are set, then this bit is set. Therefore the HD can test for an error by checking this bit first.
                                                                   0 - No Error.
                                                                   1 - Error. */
        unsigned int  cmd_timeout_error       : 1;  /* bit[16]   : Occurs only if the no response is returned within 64 SDCLK cycles from the end bit of the command. If the HC detects a CMD line conflict, in which case Command CRC Error shall also be set. This bit shall be set without waiting for 64 SDCLK cycles
                                                                   because the command will be aborted by the HC.
                                                                   0 - No Error
                                                                   1 - Timeout */
        unsigned int  cmd_crc_error           : 1;  /* bit[17]   : Command CRC Error is generated in two cases.
                                                                   1. If a response is returned and the Command Time-out Error is set to 0, this bit is set to 1 when detecting a CRT error in the command response
                                                                   2. The HC detects a CMD line conflict by monitoring the CMD line when a command is issued. If the HC drives the CMD line to 1 level, but detects 0 level on the CMD line at the next SDCLK edge, then the HC shall abort the command (Stop driving CMD line) and set this bit to 1. The Command Timeout Error shall also be set to 1 to distinguish CMD line conflict.
                                                                   0 - No Error
                                                                   1 - CRC Error Generated */
        unsigned int  cmd_end_bit_error       : 1;  /* bit[18]   : Occurs when detecting that the end bit of a command response is 0.
                                                                   0 - No Error
                                                                   1 - End Bit Error Generated */
        unsigned int  cmd_index_err           : 1;  /* bit[19]   : Occurs when detecting that the end bit of a command response is 0.
                                                                   0 - No Error
                                                                   1 - End Bit Error Generated */
        unsigned int  data_timeout_error      : 1;  /* bit[20]   : Occurs when detecting one of following timeout conditions.
                                                                   1. Busy Timeout for R1b, R5b type.
                                                                   2. Busy Timeout after Write CRC status
                                                                   3. Write CRC status Timeout
                                                                   4. Read Data Timeout
                                                                   
                                                                   0 - No Error
                                                                   1 - Timeout */
        unsigned int  data_crc_error          : 1;  /* bit[21]   : Occurs when detecting CRC error when transferring read data which uses the DAT line or when detecting the Write CRC Status having a value of other than “010”.
                                                                   0 - No Error
                                                                   1 - Error */
        unsigned int  data_endbit_error       : 1;  /* bit[22]   : Occurs when detecting 0 at the end bit position of read data which uses the DAT line or the end bit position of the CRC status.
                                                                   0 - No Error
                                                                   1 - Error */
        unsigned int  current_limit_error     : 1;  /* bit[23]   : By default it is not implemented as there is no specific requirement from Customers. */
        unsigned int  auto_cmd_error          : 1;  /* bit[24]   : Auto CMD12 and Auto CMD23 use this error status. This bit is set when detecting that one of the bits D00-D04 in Auto CMD Error Status register has changed from 0 to 1. In case of Auto CMD12, this bit is set to 1, not only when the errors in Auto CMD12 occur but also when Auto CMD12 is not executed due to the previous command error.
                                                                   0 - No Error
                                                                   1 - Error */
        unsigned int  adma_error              : 1;  /* bit[25]   : This bit is set when the Host Controller detects errors during ADMA based data transfer. The state of the ADMA at an error occurrence is saved in the ADMA Error Status Register.
                                                                   1- Error
                                                                   0 -No error */
        unsigned int  reserved_0              : 2;  /* bit[26-27]: reserved. */
        unsigned int  target_resp_error       : 1;  /* bit[28]   : Occurs when detecting ERROR in m_hresp(dma transaction)
                                                                   0 - no error
                                                                   1 - error */
        unsigned int  reserved_1              : 3;  /* bit[29-31]: reserved. */
    } reg;
} SOC_EMMC_ARASAN_INTR_ERROR_STATUS_UNION;
#endif
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_cmd_complete_START             (0)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_cmd_complete_END               (0)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_transfer_complete_START        (1)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_transfer_complete_END          (1)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_bloack_gap_event_START         (2)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_bloack_gap_event_END           (2)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_dma_imterrupt_START            (3)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_dma_imterrupt_END              (3)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_buffer_write_ready_START       (4)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_buffer_write_ready_END         (4)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_buffer_read_ready_START        (5)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_buffer_read_ready_END          (5)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_card_insertion_START           (6)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_card_insertion_END             (6)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_card_removal_START             (7)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_card_removal_END               (7)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_card_interrupt_START           (8)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_card_interrupt_END             (8)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_int_a_START                    (9)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_int_a_END                      (9)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_int_b_START                    (10)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_int_b_END                      (10)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_int_c_START                    (11)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_int_c_END                      (11)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_retuning_event_START           (12)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_retuning_event_END             (12)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_boot_ack_rev_START             (13)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_boot_ack_rev_END               (13)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_boot_terminate_intrrupt_START  (14)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_boot_terminate_intrrupt_END    (14)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_error_interrupt_START          (15)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_error_interrupt_END            (15)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_cmd_timeout_error_START        (16)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_cmd_timeout_error_END          (16)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_cmd_crc_error_START            (17)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_cmd_crc_error_END              (17)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_cmd_end_bit_error_START        (18)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_cmd_end_bit_error_END          (18)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_cmd_index_err_START            (19)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_cmd_index_err_END              (19)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_data_timeout_error_START       (20)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_data_timeout_error_END         (20)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_data_crc_error_START           (21)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_data_crc_error_END             (21)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_data_endbit_error_START        (22)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_data_endbit_error_END          (22)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_current_limit_error_START      (23)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_current_limit_error_END        (23)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_auto_cmd_error_START           (24)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_auto_cmd_error_END             (24)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_adma_error_START               (25)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_adma_error_END                 (25)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_target_resp_error_START        (28)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_target_resp_error_END          (28)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_UNION
 结构说明  : INTR_ERROR_STATUS_ENABLE 寄存器结构定义。地址偏移量:0x34，初值:0x00000000，宽度:32
 寄存器说明: 中断和错误屏蔽寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cmd_complete_mask            : 1;  /* bit[0]    : 0 - Masked
                                                                        1 - Enabled */
        unsigned int  transfer_complete_mask       : 1;  /* bit[1]    : 0 - Masked
                                                                        1 - Enabled */
        unsigned int  bloack_gap_event_mask        : 1;  /* bit[2]    : 0 - Masked
                                                                        1 - Enabled */
        unsigned int  dma_imterrupt_mask           : 1;  /* bit[3]    : 0 - Masked
                                                                        1 - Enabled */
        unsigned int  buffer_write_ready_mask      : 1;  /* bit[4]    : 0 - Masked
                                                                        1 - Enabled */
        unsigned int  buffer_read_ready_mask       : 1;  /* bit[5]    : 0 - Masked
                                                                        1 - Enabled */
        unsigned int  card_insertion_mask          : 1;  /* bit[6]    : 0 - Masked
                                                                        1 - Enabled */
        unsigned int  card_removal_mask            : 1;  /* bit[7]    : 0 - Masked
                                                                        1 - Enabled */
        unsigned int  card_interrupt_mask          : 1;  /* bit[8]    : If this bit is set to 0, the HC shall clear Interrupt request to the System. The Card Interrupt detection is stopped when this bit is cleared and restarted when this bit is set to 1. The HD may clear the Card Interrupt Status Enable before servicing the Card Interrupt and may set this bit again after all Interrupt requests from the card are cleared to prevent inadvertent Interrupts.
                                                                        0 - Masked
                                                                        1 - Enabled */
        unsigned int  int_a_mask                   : 1;  /* bit[9]    : 0 - Masked
                                                                        1 - Enabled */
        unsigned int  int_b_mask                   : 1;  /* bit[10]   : 0 - Masked
                                                                        1 - Enabled */
        unsigned int  int_c_mask                   : 1;  /* bit[11]   : If this bit is set to 0, the Host Controller shall clear the interrupt request to the System. The Host Driver may clear this bit before servicing the INT_C and may set this bit again after all interrupt requests to INT_C pin are cleared to prevent inadvertent interrupts.
                                                                        0 - Masked
                                                                        1 - Enabled */
        unsigned int  retuning_event_mask          : 1;  /* bit[12]   : 0 - Masked
                                                                        1 - Enabled */
        unsigned int  boot_ack_rev_mask            : 1;  /* bit[13]   : 0 - Masked
                                                                        1 - Enabled */
        unsigned int  boot_terminate_intrrupt_mask : 1;  /* bit[14]   : 0 - Masked
                                                                        1 - Enabled */
        unsigned int  fixed_zero                   : 1;  /* bit[15]   : The HC shall control error Interrupts using the Error Interrupt Status Enable register. */
        unsigned int  cmd_timeout_err_mask         : 1;  /* bit[16]   : Command Time-out Error Status Enable
                                                                        0 - Masked
                                                                        1 - Enabled */
        unsigned int  cmd_crc_err_mask             : 1;  /* bit[17]   : Command CRC Error Status Enable
                                                                        0 - Masked
                                                                        1 - Enabled */
        unsigned int  cmd_end_bit_err_mask         : 1;  /* bit[18]   : Command End Bit Error Status Enable
                                                                        0 - Masked
                                                                        1 - Enabled */
        unsigned int  cmd_index_err_mask           : 1;  /* bit[19]   : Command Index Error Status Enable
                                                                        0 - Masked
                                                                        1 - Enabled */
        unsigned int  data_timeout_err_mask        : 1;  /* bit[20]   : Data Timeout Error Status Enable
                                                                        0 - Masked
                                                                        1 - Enabled */
        unsigned int  data_crc_err_mask            : 1;  /* bit[21]   : Data CRC Error Status Enable
                                                                        0 - Masked
                                                                        1 - Enabled */
        unsigned int  data_endbit_err_mask         : 1;  /* bit[22]   : Data End Bit Error Status Enable
                                                                        0 - Masked
                                                                        1 - Enabled */
        unsigned int  current_limit_err_mask       : 1;  /* bit[23]   : Current Limit Error Status Enable
                                                                        0 - Masked
                                                                        1 - Enabled */
        unsigned int  auto_cmd12_err_mask          : 1;  /* bit[24]   : Auto CMD12 Error Status Enable
                                                                        0 - Masked
                                                                        1 - Enabled */
        unsigned int  adma_err_mask                : 1;  /* bit[25]   : ADMA Error Status Enable
                                                                        0 - Masked
                                                                        1 - Enabled */
        unsigned int  tuning_err_mask              : 1;  /* bit[26]   : Tuning error status enable
                                                                        0 - Masked
                                                                        1 - Enabled */
        unsigned int  reserved_0                   : 1;  /* bit[27]   : reserved. */
        unsigned int  target_resp_err_mask         : 1;  /* bit[28]   : Target Response Error /Host Error Status Enable
                                                                        0 - Masked
                                                                        1 - Enabled */
        unsigned int  reserved_1                   : 3;  /* bit[29-31]: reserved. */
    } reg;
} SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_UNION;
#endif
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_cmd_complete_mask_START             (0)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_cmd_complete_mask_END               (0)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_transfer_complete_mask_START        (1)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_transfer_complete_mask_END          (1)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_bloack_gap_event_mask_START         (2)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_bloack_gap_event_mask_END           (2)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_dma_imterrupt_mask_START            (3)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_dma_imterrupt_mask_END              (3)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_buffer_write_ready_mask_START       (4)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_buffer_write_ready_mask_END         (4)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_buffer_read_ready_mask_START        (5)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_buffer_read_ready_mask_END          (5)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_card_insertion_mask_START           (6)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_card_insertion_mask_END             (6)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_card_removal_mask_START             (7)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_card_removal_mask_END               (7)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_card_interrupt_mask_START           (8)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_card_interrupt_mask_END             (8)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_int_a_mask_START                    (9)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_int_a_mask_END                      (9)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_int_b_mask_START                    (10)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_int_b_mask_END                      (10)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_int_c_mask_START                    (11)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_int_c_mask_END                      (11)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_retuning_event_mask_START           (12)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_retuning_event_mask_END             (12)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_boot_ack_rev_mask_START             (13)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_boot_ack_rev_mask_END               (13)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_boot_terminate_intrrupt_mask_START  (14)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_boot_terminate_intrrupt_mask_END    (14)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_fixed_zero_START                    (15)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_fixed_zero_END                      (15)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_cmd_timeout_err_mask_START          (16)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_cmd_timeout_err_mask_END            (16)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_cmd_crc_err_mask_START              (17)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_cmd_crc_err_mask_END                (17)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_cmd_end_bit_err_mask_START          (18)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_cmd_end_bit_err_mask_END            (18)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_cmd_index_err_mask_START            (19)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_cmd_index_err_mask_END              (19)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_data_timeout_err_mask_START         (20)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_data_timeout_err_mask_END           (20)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_data_crc_err_mask_START             (21)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_data_crc_err_mask_END               (21)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_data_endbit_err_mask_START          (22)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_data_endbit_err_mask_END            (22)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_current_limit_err_mask_START        (23)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_current_limit_err_mask_END          (23)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_auto_cmd12_err_mask_START           (24)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_auto_cmd12_err_mask_END             (24)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_adma_err_mask_START                 (25)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_adma_err_mask_END                   (25)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_tuning_err_mask_START               (26)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_tuning_err_mask_END                 (26)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_target_resp_err_mask_START          (28)
#define SOC_EMMC_ARASAN_INTR_ERROR_STATUS_ENABLE_target_resp_err_mask_END            (28)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_UNION
 结构说明  : INTR_ERROR_ENABLE 寄存器结构定义。地址偏移量:0x38，初值:0x00000000，宽度:32
 寄存器说明: 中断和错误使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cmd_complete_enable            : 1;  /* bit[0]    : 0 - Masked
                                                                          1 - Enabled */
        unsigned int  transfer_complete_enable       : 1;  /* bit[1]    : 0 - Masked
                                                                          1 - Enabled */
        unsigned int  bloack_gap_event_enable        : 1;  /* bit[2]    : 0 - Masked
                                                                          1 - Enabled */
        unsigned int  dma_imterrupt_enable           : 1;  /* bit[3]    : 0 - Masked
                                                                          1 - Enabled */
        unsigned int  buffer_write_ready_enable      : 1;  /* bit[4]    : 0 - Masked
                                                                          1 - Enabled */
        unsigned int  buffer_read_ready_enable       : 1;  /* bit[5]    : 0 - Masked
                                                                          1 - Enabled */
        unsigned int  card_insertion_enable          : 1;  /* bit[6]    : 0 - Masked
                                                                          1 - Enabled */
        unsigned int  card_removal_enable            : 1;  /* bit[7]    : 0 - Masked
                                                                          1 - Enabled */
        unsigned int  card_interrupt_enable          : 1;  /* bit[8]    : 0 - Masked
                                                                          1 - Enabled */
        unsigned int  int_a_enable                   : 1;  /* bit[9]    : 0 - Masked
                                                                          1 - Enabled */
        unsigned int  int_b_enable                   : 1;  /* bit[10]   : 0 - Masked
                                                                          1 - Enabled */
        unsigned int  int_c_enable                   : 1;  /* bit[11]   : 0 - Masked
                                                                          1 - Enabled */
        unsigned int  retuning_event_enable          : 1;  /* bit[12]   : 0 - Masked
                                                                          1 - Enabled */
        unsigned int  boot_ack_rev_enable            : 1;  /* bit[13]   : 0 - Masked
                                                                          1 - Enabled */
        unsigned int  boot_terminate_intrrupt_enable : 1;  /* bit[14]   : 0 - Masked
                                                                          1 - Enabled */
        unsigned int  fixed_zero                     : 1;  /* bit[15]   : 0 - Masked
                                                                          1 - Enabled */
        unsigned int  cmd_timeout_err_enable         : 1;  /* bit[16]   : 0 - Masked
                                                                          1 - Enabled */
        unsigned int  cmd_crc_err_enable             : 1;  /* bit[17]   : 0 - Masked
                                                                          1 - Enabled */
        unsigned int  cmd_end_bit_err_enable         : 1;  /* bit[18]   : 0 - Masked
                                                                          1 - Enabled */
        unsigned int  cmd_index_err_enable           : 1;  /* bit[19]   : 0 - Masked
                                                                          1 - Enabled */
        unsigned int  data_timeout_err_enable        : 1;  /* bit[20]   : 0 - Masked
                                                                          1 - Enabled */
        unsigned int  data_crc_err_enable            : 1;  /* bit[21]   : 0 - Masked
                                                                          1 - Enabled */
        unsigned int  data_endbit_err_enable         : 1;  /* bit[22]   : 0 - Masked
                                                                          1 - Enabled */
        unsigned int  current_limit_err_enable       : 1;  /* bit[23]   : 0 - Masked
                                                                          1 - Enabled */
        unsigned int  auto_cmd12_err_enable          : 1;  /* bit[24]   : 0 - Masked
                                                                          1 - Enabled */
        unsigned int  adma_err_enable                : 1;  /* bit[25]   : 0 - Masked
                                                                          1 - Enabled */
        unsigned int  tuning_err_enable              : 1;  /* bit[26]   : 0 - Masked
                                                                          1 - Enabled */
        unsigned int  reserved_0                     : 1;  /* bit[27]   : reserved. */
        unsigned int  target_resp_err_enable         : 1;  /* bit[28]   : 0 - Masked
                                                                          1 - Enabled */
        unsigned int  reserved_1                     : 3;  /* bit[29-31]: reserved. */
    } reg;
} SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_UNION;
#endif
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_cmd_complete_enable_START             (0)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_cmd_complete_enable_END               (0)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_transfer_complete_enable_START        (1)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_transfer_complete_enable_END          (1)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_bloack_gap_event_enable_START         (2)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_bloack_gap_event_enable_END           (2)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_dma_imterrupt_enable_START            (3)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_dma_imterrupt_enable_END              (3)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_buffer_write_ready_enable_START       (4)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_buffer_write_ready_enable_END         (4)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_buffer_read_ready_enable_START        (5)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_buffer_read_ready_enable_END          (5)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_card_insertion_enable_START           (6)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_card_insertion_enable_END             (6)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_card_removal_enable_START             (7)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_card_removal_enable_END               (7)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_card_interrupt_enable_START           (8)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_card_interrupt_enable_END             (8)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_int_a_enable_START                    (9)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_int_a_enable_END                      (9)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_int_b_enable_START                    (10)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_int_b_enable_END                      (10)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_int_c_enable_START                    (11)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_int_c_enable_END                      (11)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_retuning_event_enable_START           (12)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_retuning_event_enable_END             (12)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_boot_ack_rev_enable_START             (13)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_boot_ack_rev_enable_END               (13)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_boot_terminate_intrrupt_enable_START  (14)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_boot_terminate_intrrupt_enable_END    (14)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_fixed_zero_START                      (15)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_fixed_zero_END                        (15)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_cmd_timeout_err_enable_START          (16)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_cmd_timeout_err_enable_END            (16)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_cmd_crc_err_enable_START              (17)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_cmd_crc_err_enable_END                (17)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_cmd_end_bit_err_enable_START          (18)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_cmd_end_bit_err_enable_END            (18)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_cmd_index_err_enable_START            (19)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_cmd_index_err_enable_END              (19)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_data_timeout_err_enable_START         (20)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_data_timeout_err_enable_END           (20)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_data_crc_err_enable_START             (21)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_data_crc_err_enable_END               (21)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_data_endbit_err_enable_START          (22)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_data_endbit_err_enable_END            (22)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_current_limit_err_enable_START        (23)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_current_limit_err_enable_END          (23)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_auto_cmd12_err_enable_START           (24)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_auto_cmd12_err_enable_END             (24)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_adma_err_enable_START                 (25)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_adma_err_enable_END                   (25)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_tuning_err_enable_START               (26)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_tuning_err_enable_END                 (26)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_target_resp_err_enable_START          (28)
#define SOC_EMMC_ARASAN_INTR_ERROR_ENABLE_target_resp_err_enable_END            (28)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_UNION
 结构说明  : AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2 寄存器结构定义。地址偏移量:0x3C，初值:0x00000000，宽度:32
 寄存器说明: 自动tuning错误和控制2寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  auto_cmd12_not_executed                : 1;  /* bit[0]    : If memory multiple block data transfer is not started due to command error, this bit is not set because it is not necessary to issue Auto CMD12. Setting this bit 
                                                                                  to 1 means the HC cannot issue Auto CMD12 to stop memory multiple block transfer due to some error. If this bit is set to 1, other error status bits (D04 - D01) are meaningless.
                                                                                  This bit is set to 0 when Auto CMD Error is generated by Auto CMD23
                                                                                  0 - Executed
                                                                                  1 - Not Executed */
        unsigned int  auto_cmd_timeout_error                 : 1;  /* bit[1]    : Occurs if the no response is returned within 64 SDCLK cycles from the end bit of the command.If this bit is set to 1, the other error status bits (D04 - D02) are meaningless.
                                                                                  0 - No Error
                                                                                  1 - Timeout */
        unsigned int  auto_cmd_crc_error                     : 1;  /* bit[2]    : Occurs when detecting a CRC error in the command response.
                                                                                  0 - No Error
                                                                                  1 - CRC Error Generated */
        unsigned int  auto_cmd_end_bit_error                 : 1;  /* bit[3]    : Occurs when detecting that the end bit of command response is 0.
                                                                                  0 - No Error
                                                                                  1 - End Bit Error Generated */
        unsigned int  auto_cmd_index_error                   : 1;  /* bit[4]    : Occurs if the Command Index error occurs in response to a command.
                                                                                  0 - No Error
                                                                                  1 - Error */
        unsigned int  reserved_0                             : 2;  /* bit[5-6]  : reserved. */
        unsigned int  command_not_issued_by_auto_cmd12_error : 1;  /* bit[7]    : Setting this bit to 1 means CMD_wo_DAT is not executed due to an Auto CMD12 error (D04 - D01) in this register.This bit is set to 0 when Auto CMD Error is generated by Auto CMD23
                                                                                  0 - No Error
                                                                                  1 - Not Issued */
        unsigned int  reserved_1                             : 8;  /* bit[8-15] : reserved. */
        unsigned int  uhs_mode_select                        : 3;  /* bit[16-18]: This field is used to select one of UHS-I modes and effective when 1.8V Signaling Enable is set to 1.If Preset Value Enable in the Host Control 2 register is set to 1, Host Controller sets SDCLK Frequency Select, Clock Generator Select in the Clock Control register and Driver Strength Select according to Preset Value registers. In this case, one of preset value registers is selected by this field. Host Driver needs to reset SD Clock Enable before changing this field to avoid generating clock glitch. After setting this field, Host Driver sets SD Clock Enable again.
                                                                                  000b - SDR12
                                                                                  001b - SDR25
                                                                                  010b - SDR50
                                                                                  011b - SDR104
                                                                                  100b - DDR50
                                                                                  101b - HS400 
                                                                                  110b - 111 Reserved
                                                                                  When SDR50, SDR104 or DDR50 is selected for SDIO card, interrupt detection at the block gap shall not be used. Read Wait timing is changed for these modes. Refer to the SDIO Specification Version 3.00 for more detail. */
        unsigned int  v1p8_signaling_enable                  : 1;  /* bit[19]   : This bit controls voltage regulator for I/O cell. 3.3V is supplied to the card regardless of signaling voltage.Setting this bit from 0 to 1 starts changing signal voltage from 3.3V to 1.8V.1.8V regulator output shall be stable within 5ms. Host Controller clears this bit if switching to 1.8V signaling fails.
                                                                                  Clearing this bit from 1 to 0 starts changing signal voltage from 1.8V to 3.3V.
                                                                                  3.3V regulator output shall be stable within 5ms.
                                                                                  Host Driver can set this bit to 1 when Host Controller supports 1.8V signaling (One of support bits is set to 1: SDR50, SDR104 or DDR50 in the Capabilities register) and the card or device supports UHS-I 
                                                                                  1 - 1.8V Signaling
                                                                                  0 - 3.3V Signaling */
        unsigned int  driver_strength_select                 : 2;  /* bit[20-21]: Host Controller output driver in 1.8V signaling is selected by this bit. In 3.3V signaling, this field is not effective. This field can be set depends on Driver Type A, C and D support bits in the Capabilities register. This bit depends on setting of Preset Value Enable. 
                                                                                  If Preset Value Enable = 0, this field is set by Host Driver. 
                                                                                  If Preset Value Enable = 1, this field is automatically set by a value specified in the one of Preset Value registers.
                                                                                  00b Driver Type B is Selected (Default)
                                                                                  01b Driver Type A is Selected
                                                                                  10b Driver Type C is Selected
                                                                                  11b Driver Type D is Selected */
        unsigned int  executetuning                          : 1;  /* bit[22]   : This bit is set to 1 to start tuning procedure and automatically cleared when tuning procedure is completed. The result of tuning is indicated to Sampling Clock Select. Tuning procedure is aborted by writing 0 for more detail about tuning procedure.
                                                                                  1- Execute Tuning, 0 Not Tuned or Tuning Completed. */
        unsigned int  sampling_clock_select                  : 1;  /* bit[23]   : This bit is set by tuning procedure when Execute Tuning is cleared. Writing 1 to this bit is meaningless and ignored. Setting 1 means that tuning is completed successfully and setting 0 means that tuning is failed. Host Controller uses this bit to select sampling clock to receive CMD and DAT. This bit is cleared by writing 0. Change of this bit is not allowed while the Host Controller is receiving response or a read data block.
                                                                                  1 Tuned clock is used to sample data
                                                                                  0 Fixed clock is used to sample data */
        unsigned int  reserved_2                             : 1;  /* bit[24]   : reserved. */
        unsigned int  driverstrength                         : 1;  /* bit[25]   : This is the programmed Drive STrength output and Bit[2] of the sdhccore_drivestrength value. */
        unsigned int  reserved_3                             : 4;  /* bit[26-29]: reserved. */
        unsigned int  asynchronous_interrupt_enable          : 1;  /* bit[30]   : This bit can be set to 1 if a card support asynchronous interrupt and Asynchronous Interrupt Support is set to 1 in the Capabilities register. Asynchronous interrupt is effective when DAT[1] interrupt is used in 4-bit SD mode (and zero is set to Interrupt Pin Select in the Shared Bus Control register). If this bit is set to 1, the Host Driver can stop the SDCLK during asynchronous interrupt period to save power. During this period, the Host Controller continues to deliver Card Interrupt to the host when it is asserted by the Card.
                                                                                  1 - Enabled, 
                                                                                  0 - Disabled */
        unsigned int  preset_value_enable                    : 1;  /* bit[31]   : Host Controller Version 3.00 supports this bit. As the operating SDCLK frequency and I/O driver strength depend on the Host System implementation, it is difficult to determine these parameters in the Standard Host Driver. When Preset Value Enable is set to automatic. This bit enables the functions defined in the Preset Value registers.
                                                                                  1 Automatic Selection by Preset Value are Enabled
                                                                                  0 SDCLK and Driver Strength are controlled by Host Driver
                                                                                  If this bit is set to 0, SDCLK Frequency Select, Clock Generator Select in the Clock Control register and Driver Strength Select in Host Control 2 register are set by Host Driver. If this bit is set to 1, SDCLK Frequency Select, Clock Generator Select in the Clock Control register and Driver Strength Select in Host Control 2 register are set by Host Controller as specified in the Preset Value registers. */
    } reg;
} SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_UNION;
#endif
#define SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_auto_cmd12_not_executed_START                 (0)
#define SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_auto_cmd12_not_executed_END                   (0)
#define SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_auto_cmd_timeout_error_START                  (1)
#define SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_auto_cmd_timeout_error_END                    (1)
#define SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_auto_cmd_crc_error_START                      (2)
#define SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_auto_cmd_crc_error_END                        (2)
#define SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_auto_cmd_end_bit_error_START                  (3)
#define SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_auto_cmd_end_bit_error_END                    (3)
#define SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_auto_cmd_index_error_START                    (4)
#define SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_auto_cmd_index_error_END                      (4)
#define SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_command_not_issued_by_auto_cmd12_error_START  (7)
#define SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_command_not_issued_by_auto_cmd12_error_END    (7)
#define SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_uhs_mode_select_START                         (16)
#define SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_uhs_mode_select_END                           (18)
#define SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_v1p8_signaling_enable_START                   (19)
#define SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_v1p8_signaling_enable_END                     (19)
#define SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_driver_strength_select_START                  (20)
#define SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_driver_strength_select_END                    (21)
#define SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_executetuning_START                           (22)
#define SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_executetuning_END                             (22)
#define SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_sampling_clock_select_START                   (23)
#define SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_sampling_clock_select_END                     (23)
#define SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_driverstrength_START                          (25)
#define SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_driverstrength_END                            (25)
#define SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_asynchronous_interrupt_enable_START           (30)
#define SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_asynchronous_interrupt_enable_END             (30)
#define SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_preset_value_enable_START                     (31)
#define SOC_EMMC_ARASAN_AUTO_CMD_ERR_STATUS_AND_HOST_CONTRL_2_preset_value_enable_END                       (31)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_UNION
 结构说明  : CAPABILITIES_REGISTER1 寄存器结构定义。地址偏移量:0x40，初值:0x44ECC881，宽度:32
 寄存器说明: 控制器能力1寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  timeoutclockfrequency          : 6;  /* bit[0-5]  : This bit shows the base clock frequency used to detect Data Timeout Error.
                                                                          Not 0 - 1Khz to 63Khz or 1Mhz to 63Mhz
                                                                          000000b - Get Information via another method. */
        unsigned int  reserved_0                     : 1;  /* bit[6]    : reserved. */
        unsigned int  timeoutclockunit               : 1;  /* bit[7]    : This bit shows the unit of base clock frequency used to detect Data Timeout Error.
                                                                          0 - Khz
                                                                          1 - Mhz */
        unsigned int  baseclockfrequencyforsdclock   : 8;  /* bit[8-15] : 200M */
        unsigned int  max_block_length               : 2;  /* bit[16-17]: This value indicates the maximum block size that the HD can read and write to the buffer in the HC. The buffer shall transfer this block size without wait cycles. Three sizes can be defined as indicated below.
                                                                          00 - 512 byte
                                                                          01 - 1024 byte
                                                                          10 - 2048 byte
                                                                          11 - 4096 byte */
        unsigned int  extendedmediabussupport        : 1;  /* bit[18]   : This bit indicates whether the Host Controller is capable of using 8-bit bus width mode. This bit is not effective when Slot Type is set to 10b. In this case, refer to Bus Width Preset in the Shared Bus resister.
                                                                          1 - Extended Media Bus Supported
                                                                          0 - Extended Media Bus not Supported */
        unsigned int  adma2support                   : 1;  /* bit[19]   : 1 - ADMA2 support.
                                                                          0 - ADMA2 not suppo */
        unsigned int  reserved_1                     : 1;  /* bit[20]   : reserved. */
        unsigned int  highspeedsupport               : 1;  /* bit[21]   : This bit indicates whether the HC and the Host System support High Speed mode and they can supply SD Clock frequency from 25Mhz to 50 Mhz (for SD)/ 20MHz to 52MHz (for MMC).
                                                                          0 - High Speed Not Supported
                                                                          1 - High Speed Supported */
        unsigned int  sdma_support                   : 1;  /* bit[22]   : This bit indicates whether the HC is capable of using DMA to transfer data between system memory and the HC directly.
                                                                          0 - SDMA Not Supported
                                                                          1 - SDMA Supported. */
        unsigned int  suspend_resumesupport          : 1;  /* bit[23]   : This bit indicates whether the HC supports Suspend / Resume functionality. If this bit is 0, the Suspend and Resume mechanism are not supported and the HD shall not issue either Suspend / Resume commands.
                                                                          0 - Not Supported
                                                                          1 - Supported */
        unsigned int  voltagesupport3_3v             : 1;  /* bit[24]   : 0 - 3.3 V Not Supported
                                                                          1 - 3.3 V Supported */
        unsigned int  voltagesupport3_0v             : 1;  /* bit[25]   : 0 - 3.0 V Not Supported
                                                                          1 - 3.0 V Supported */
        unsigned int  voltagesupport1_8v             : 1;  /* bit[26]   : 0 - 1.8 V Not Supported
                                                                          1 - 1.8 V Supported */
        unsigned int  reserved_2                     : 1;  /* bit[27]   : reserved. */
        unsigned int  bus64_bitsystembussupport      : 1;  /* bit[28]   : 1 - supports 64 bit system address
                                                                          0 - Does not support 64 bit system address */
        unsigned int  asynchronous_interrupt_support : 1;  /* bit[29]   : Refer to SDIO Specification Version 3.00 about asynchronous interrupt.
                                                                          1 Asynchronous Interrupt Supported
                                                                          0 Asynchronous Interrupt Not Supported */
        unsigned int  slottype                       : 2;  /* bit[30-31]: 00b Removable Card Slot
                                                                          01b Embedded Slot for One Device
                                                                          10b Shared Bus Slot
                                                                          11b Reserved */
    } reg;
} SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_UNION;
#endif
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_timeoutclockfrequency_START           (0)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_timeoutclockfrequency_END             (5)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_timeoutclockunit_START                (7)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_timeoutclockunit_END                  (7)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_baseclockfrequencyforsdclock_START    (8)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_baseclockfrequencyforsdclock_END      (15)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_max_block_length_START                (16)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_max_block_length_END                  (17)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_extendedmediabussupport_START         (18)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_extendedmediabussupport_END           (18)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_adma2support_START                    (19)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_adma2support_END                      (19)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_highspeedsupport_START                (21)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_highspeedsupport_END                  (21)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_sdma_support_START                    (22)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_sdma_support_END                      (22)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_suspend_resumesupport_START           (23)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_suspend_resumesupport_END             (23)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_voltagesupport3_3v_START              (24)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_voltagesupport3_3v_END                (24)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_voltagesupport3_0v_START              (25)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_voltagesupport3_0v_END                (25)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_voltagesupport1_8v_START              (26)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_voltagesupport1_8v_END                (26)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_bus64_bitsystembussupport_START       (28)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_bus64_bitsystembussupport_END         (28)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_asynchronous_interrupt_support_START  (29)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_asynchronous_interrupt_support_END    (29)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_slottype_START                        (30)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER1_slottype_END                          (31)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_UNION
 结构说明  : CAPABILITIES_REGISTER2 寄存器结构定义。地址偏移量:0x44，初值:0x800020F7，宽度:32
 寄存器说明: 控制器能力2寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sdr50_support            : 1;  /* bit[0]    : If SDR104 is supported, this bit shall be set to 1. Bit 40 indicates whether SDR50 requires tuning or not.
                                                                    1 SDR50 is Supported
                                                                    0 SDR50 is Not Supported */
        unsigned int  sdr104_support           : 1;  /* bit[1]    : SDR104 requires tuning.
                                                                    1 SDR104 is Supported
                                                                    0 SDR104 is Not Supported */
        unsigned int  ddr50_support            : 1;  /* bit[2]    : 1 DDR50 is Supported
                                                                    0 DDR50 is Not Supported */
        unsigned int  reserved_0               : 1;  /* bit[3]    : reserved. */
        unsigned int  driver_typea_support     : 1;  /* bit[4]    : Driver_TypeA_Support */
        unsigned int  driver_typec_support     : 1;  /* bit[5]    : Driver_TypeC_Support */
        unsigned int  driver_typed_support     : 1;  /* bit[6]    : Driver_TypeD_Support */
        unsigned int  driver_type4_support     : 1;  /* bit[7]    : Driver_Type4_Support */
        unsigned int  timer_count_for_retuning : 4;  /* bit[8-11] : This field indicates an initial value of the Re-Tuning Timer for Re-Tuning Mode 1 to 3.
                                                                    0h - Get information via other 
                                                                    source
                                                                    1h = 1 seconds
                                                                    2h = 2 seconds
                                                                    3h = 4 seconds
                                                                    4h = 8 seconds
                                                                    --
                                                                    n = 2(n-1) seconds
                                                                    --
                                                                    Bh = 1024 seconds
                                                                    Fh - Ch = Reserved */
        unsigned int  reserved_1               : 1;  /* bit[12]   : reserved. */
        unsigned int  use_tuning_for_sdr50     : 1;  /* bit[13]   : If this bit is set to 1, this Host Controller requires tuning to operate SDR50. (Tuning is always required to operate SDR104.)
                                                                    1 SDR50 requires tuning
                                                                    0 SDR50 does not require tuning */
        unsigned int  re_tuning_modes          : 2;  /* bit[14-15]: This field defines the re-tuning capability of a Host Controller and how to manage the data transfer length and a Re-Tuning Timer by the Host Driver
                                                                    00 - Mode1
                                                                    01 - Mode2
                                                                    10 - Mode3
                                                                    11 - Reserved
                                                                    There are two re-tuning timings: Re-Tuning Request and expiration of a Re-Tuning Timer. By receiving either timing, the Host Driver executes the re-tuning procedure just before a next command issue */
        unsigned int  clock_multiplier         : 8;  /* bit[16-23]: This field indicates clock multiplier value of programmable clock generator. Refer to Clock Control register. Setting 00h means that Host Controller does not support programmable clock generator.
                                                                    FFh Clock Multiplier M = 256
                                                                    ....
                                                                    02h Clock Multiplier M = 3
                                                                    01h Clock Multiplier M = 2
                                                                    00h Clock Multiplier is Not Supported */
        unsigned int  spi_mode                 : 1;  /* bit[24]   : Spi mode
                                                                    0 - Not Supported
                                                                    1 - Supported */
        unsigned int  spi_block_mode           : 1;  /* bit[25]   : Spi block mode
                                                                    0 - Not Supported
                                                                    1 - Supported */
        unsigned int  reserved_2               : 5;  /* bit[26-30]: reserved. */
        unsigned int  hs400_support            : 1;  /* bit[31]   : 1 HS400 is Supported
                                                                    0 HS400 is Not Supported */
    } reg;
} SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_UNION;
#endif
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_sdr50_support_START             (0)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_sdr50_support_END               (0)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_sdr104_support_START            (1)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_sdr104_support_END              (1)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_ddr50_support_START             (2)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_ddr50_support_END               (2)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_driver_typea_support_START      (4)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_driver_typea_support_END        (4)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_driver_typec_support_START      (5)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_driver_typec_support_END        (5)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_driver_typed_support_START      (6)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_driver_typed_support_END        (6)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_driver_type4_support_START      (7)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_driver_type4_support_END        (7)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_timer_count_for_retuning_START  (8)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_timer_count_for_retuning_END    (11)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_use_tuning_for_sdr50_START      (13)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_use_tuning_for_sdr50_END        (13)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_re_tuning_modes_START           (14)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_re_tuning_modes_END             (15)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_clock_multiplier_START          (16)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_clock_multiplier_END            (23)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_spi_mode_START                  (24)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_spi_mode_END                    (24)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_spi_block_mode_START            (25)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_spi_block_mode_END              (25)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_hs400_support_START             (31)
#define SOC_EMMC_ARASAN_CAPABILITIES_REGISTER2_hs400_support_END               (31)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_MAX_CURRENT_UNION
 结构说明  : MAX_CURRENT 寄存器结构定义。地址偏移量:0x48，初值:0x00000000，宽度:32
 寄存器说明: 最大电流寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  max_current : 24; /* bit[0-23] : max_current */
        unsigned int  reserved    : 8;  /* bit[24-31]: reserved. */
    } reg;
} SOC_EMMC_ARASAN_MAX_CURRENT_UNION;
#endif
#define SOC_EMMC_ARASAN_MAX_CURRENT_max_current_START  (0)
#define SOC_EMMC_ARASAN_MAX_CURRENT_max_current_END    (23)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_UNION
 结构说明  : FORCE_EVENT_REGISTER 寄存器结构定义。地址偏移量:0x50，初值:0x00000000，宽度:32
 寄存器说明: 强制触发寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  forceeventforautocmd12notexecuted_            : 1;  /* bit[0]    : 1 - Interrupt is generated
                                                                                         0 - no interrupt */
        unsigned int  forceeventforautocmdtimeouterror_             : 1;  /* bit[1]    : 1 - Interrupt is generated
                                                                                         0 - no interrupt */
        unsigned int  forceeventforautocmdcrcerror                  : 1;  /* bit[2]    : 1 - Interrupt is generated
                                                                                         0 - no interrupt */
        unsigned int  forceeventforautocmdendbiterror               : 1;  /* bit[3]    : 1 - Interrupt is generated
                                                                                         0 - no interrupt */
        unsigned int  forceeventforautocmdindexerror                : 1;  /* bit[4]    : 1 - Interrupt is generated
                                                                                         0 - no interrupt */
        unsigned int  reserved_0                                    : 2;  /* bit[5-6]  : reserved. */
        unsigned int  forceeventforcommandnotissuedbyautocmd12error : 1;  /* bit[7]    : 1 - Interrupt is generated
                                                                                         0 - no interrupt */
        unsigned int  reserved_1                                    : 8;  /* bit[8-15] : reserved. */
        unsigned int  forceeventforcommandtime_outerror             : 1;  /* bit[16]   : Force Event for Command Timeout 
                                                                                         Error
                                                                                         1 - Interrupt is generated
                                                                                         0 - No interrupt */
        unsigned int  forceeventforcommandcrcerror                  : 1;  /* bit[17]   : force Event for Command CRC Error
                                                                                         1 - Interrupt is generated
                                                                                         0 - No interrupt */
        unsigned int  forceeventforcommandendbiterror               : 1;  /* bit[18]   : Force Event for Command End Bit Error
                                                                                         1 - Interrupt is generated
                                                                                         0 - No interrupt. */
        unsigned int  forceeventforcommandindexerror                : 1;  /* bit[19]   : Force Event for Command Index Error
                                                                                         1 - Interrupt is generated
                                                                                         0 - No interrupt */
        unsigned int  forceeventfordatatimeouterror                 : 1;  /* bit[20]   : Force Event for Data Timeout Error
                                                                                         1 - Interrupt is generated
                                                                                         0 - No interrupt */
        unsigned int  forceeventfordatacrcerror                     : 1;  /* bit[21]   : Force Event for Data CRC Error
                                                                                         1 - Interrupt is generated
                                                                                         0 - No interrupt */
        unsigned int  forceeventfordataendbiterror                  : 1;  /* bit[22]   : Force Event for Data End Bit Error
                                                                                         1 - Interrupt is generated
                                                                                         0 - No interrupt */
        unsigned int  forceeventforcurrentlimiterror                : 1;  /* bit[23]   : Force Event for Current Limit Error
                                                                                         1 - Interrupt is generated
                                                                                         0 - No interrupt */
        unsigned int  forceeventforautocmderror                     : 1;  /* bit[24]   : Force Event for Auto CMD Error
                                                                                         1 - Interrupt is generated
                                                                                         0 - No interrupt */
        unsigned int  forceeventforadmaerror                        : 1;  /* bit[25]   : Force Event for ADMA Error
                                                                                         1 - Interrupt is generated
                                                                                         0 - No interrupt */
        unsigned int  reserved_2                                    : 6;  /* bit[26-31]: reserved. */
    } reg;
} SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_UNION;
#endif
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventforautocmd12notexecuted__START             (0)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventforautocmd12notexecuted__END               (0)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventforautocmdtimeouterror__START              (1)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventforautocmdtimeouterror__END                (1)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventforautocmdcrcerror_START                   (2)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventforautocmdcrcerror_END                     (2)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventforautocmdendbiterror_START                (3)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventforautocmdendbiterror_END                  (3)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventforautocmdindexerror_START                 (4)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventforautocmdindexerror_END                   (4)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventforcommandnotissuedbyautocmd12error_START  (7)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventforcommandnotissuedbyautocmd12error_END    (7)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventforcommandtime_outerror_START              (16)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventforcommandtime_outerror_END                (16)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventforcommandcrcerror_START                   (17)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventforcommandcrcerror_END                     (17)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventforcommandendbiterror_START                (18)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventforcommandendbiterror_END                  (18)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventforcommandindexerror_START                 (19)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventforcommandindexerror_END                   (19)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventfordatatimeouterror_START                  (20)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventfordatatimeouterror_END                    (20)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventfordatacrcerror_START                      (21)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventfordatacrcerror_END                        (21)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventfordataendbiterror_START                   (22)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventfordataendbiterror_END                     (22)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventforcurrentlimiterror_START                 (23)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventforcurrentlimiterror_END                   (23)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventforautocmderror_START                      (24)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventforautocmderror_END                        (24)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventforadmaerror_START                         (25)
#define SOC_EMMC_ARASAN_FORCE_EVENT_REGISTER_forceeventforadmaerror_END                           (25)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_ADMA_ERROR_STATUS_REGISTER_UNION
 结构说明  : ADMA_ERROR_STATUS_REGISTER 寄存器结构定义。地址偏移量:0x54，初值:0x00000000，宽度:32
 寄存器说明: ADMA错误寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  admaerrorstate          : 2;  /* bit[0-1] : his field indicates the state of ADMA when error is occurred during ADMA data transfer. This field never indicates "10" because ADMA never stops in this state. 
                                                                  D01 – D00 : ADMA Error State when error occurred Contents of SYS_SDR register
                                                                  00 - ST_STOP (Stop DMA) Points to next of the error descriptor
                                                                  01 - ST_FDS (Fetch Descriptor) Points to the error descriptor
                                                                  10 - Never set this state (Not used)
                                                                  11 - ST_TFR (Transfer Data) Points to the next of the error descriptor */
        unsigned int  admalengthmismatcherror : 1;  /* bit[2]   : This error occurs in the following 2 cases.
                                                                  While Block Count Enable being set, the total data length specified by the Descriptor table is different from that specified by the Block Count and Block 
                                                                  Length. Total data length can not be divided by the block length.
                                                                   1 - Error
                                                                   0 - No error */
        unsigned int  reserved                : 29; /* bit[3-31]: reserved. */
    } reg;
} SOC_EMMC_ARASAN_ADMA_ERROR_STATUS_REGISTER_UNION;
#endif
#define SOC_EMMC_ARASAN_ADMA_ERROR_STATUS_REGISTER_admaerrorstate_START           (0)
#define SOC_EMMC_ARASAN_ADMA_ERROR_STATUS_REGISTER_admaerrorstate_END             (1)
#define SOC_EMMC_ARASAN_ADMA_ERROR_STATUS_REGISTER_admalengthmismatcherror_START  (2)
#define SOC_EMMC_ARASAN_ADMA_ERROR_STATUS_REGISTER_admalengthmismatcherror_END    (2)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_ADMA_SYSTEM_ADDRESS_REG1_UNION
 结构说明  : ADMA_SYSTEM_ADDRESS_REG1 寄存器结构定义。地址偏移量:0x58，初值:0x00000000，宽度:32
 寄存器说明: ADMA地址1寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  admasystemaddress2 : 32; /* bit[0-31]: This register holds byte address of executing command of the Descriptor table. 
                                                             32-bit Address Descriptor uses lower 32bit of this register. At the start of ADMA, the Host Driver shall set start address of the Descriptor table. The ADMA increments this register address, which points to next line, when every fetching a Descriptor line. When the ADMA Error Interrupt is generated, this register shall hold valid Descriptor address depending on the ADMA state. The Host Driver shall program Descriptor Table on 32-bit boundary and set 32-bit boundary address to this register. ADMA2 ignores lower 2-bit of this register and assumes it to be 00b.
                                                             32-bit Address ADMA Register Value 32-bit System Address
                                                             xxxxxxxx 00000000h 00000000h
                                                             xxxxxxxx 00000004h 00000004h
                                                             …… ……
                                                             xxxxxxxx FFFFFFFCh FFFFFFFCh */
    } reg;
} SOC_EMMC_ARASAN_ADMA_SYSTEM_ADDRESS_REG1_UNION;
#endif
#define SOC_EMMC_ARASAN_ADMA_SYSTEM_ADDRESS_REG1_admasystemaddress2_START  (0)
#define SOC_EMMC_ARASAN_ADMA_SYSTEM_ADDRESS_REG1_admasystemaddress2_END    (31)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_ADMA_SYSTEM_ADDRESS_REG2_UNION
 结构说明  : ADMA_SYSTEM_ADDRESS_REG2 寄存器结构定义。地址偏移量:0x5C，初值:0x00000000，宽度:32
 寄存器说明: ADMA地址2寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  adma_system_address1 : 32; /* bit[0-31]: This register holds byte address of executing command of the Descriptor table.
                                                               64-bit Address Descriptor uses Upper 32-bit of this register. At the start of ADMA, the Host Driver shall set start address of the Descriptor table. This field is valid only when "64-bit System Bus Support" of Capabilities register 
                                                               is set to 1 */
    } reg;
} SOC_EMMC_ARASAN_ADMA_SYSTEM_ADDRESS_REG2_UNION;
#endif
#define SOC_EMMC_ARASAN_ADMA_SYSTEM_ADDRESS_REG2_adma_system_address1_START  (0)
#define SOC_EMMC_ARASAN_ADMA_SYSTEM_ADDRESS_REG2_adma_system_address1_END    (31)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_PRESET_VALUE1_UNION
 结构说明  : PRESET_VALUE1 寄存器结构定义。地址偏移量:0x60，初值:0x00000000，宽度:32
 寄存器说明: 初始化模式配置1寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  presetvalueforinitialization : 17; /* bit[0-16] : Preset Value for Initialization */
        unsigned int  presetvaluefordefaultspeed   : 15; /* bit[17-31]: Preset Value for Default Speed */
    } reg;
} SOC_EMMC_ARASAN_PRESET_VALUE1_UNION;
#endif
#define SOC_EMMC_ARASAN_PRESET_VALUE1_presetvalueforinitialization_START  (0)
#define SOC_EMMC_ARASAN_PRESET_VALUE1_presetvalueforinitialization_END    (16)
#define SOC_EMMC_ARASAN_PRESET_VALUE1_presetvaluefordefaultspeed_START    (17)
#define SOC_EMMC_ARASAN_PRESET_VALUE1_presetvaluefordefaultspeed_END      (31)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_PRESET_VALUE2_UNION
 结构说明  : PRESET_VALUE2 寄存器结构定义。地址偏移量:0x64，初值:0x00000000，宽度:32
 寄存器说明: 初始化模式配置2寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  presetvalueforsdr12     : 16; /* bit[0-15] : Preset Value for SDR12 */
        unsigned int  presetvalueforhighspeed : 16; /* bit[16-31]: Preset Value for High Speed */
    } reg;
} SOC_EMMC_ARASAN_PRESET_VALUE2_UNION;
#endif
#define SOC_EMMC_ARASAN_PRESET_VALUE2_presetvalueforsdr12_START      (0)
#define SOC_EMMC_ARASAN_PRESET_VALUE2_presetvalueforsdr12_END        (15)
#define SOC_EMMC_ARASAN_PRESET_VALUE2_presetvalueforhighspeed_START  (16)
#define SOC_EMMC_ARASAN_PRESET_VALUE2_presetvalueforhighspeed_END    (31)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_PRESET_VALUE3_UNION
 结构说明  : PRESET_VALUE3 寄存器结构定义。地址偏移量:0x68，初值:0x00000000，宽度:32
 寄存器说明: 初始化模式配置3寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  presetvalueforsdr25 : 16; /* bit[0-15] : Preset Value for SDR25 */
        unsigned int  presetvalueforsdr50 : 16; /* bit[16-31]: PresetValueforSDR50 */
    } reg;
} SOC_EMMC_ARASAN_PRESET_VALUE3_UNION;
#endif
#define SOC_EMMC_ARASAN_PRESET_VALUE3_presetvalueforsdr25_START  (0)
#define SOC_EMMC_ARASAN_PRESET_VALUE3_presetvalueforsdr25_END    (15)
#define SOC_EMMC_ARASAN_PRESET_VALUE3_presetvalueforsdr50_START  (16)
#define SOC_EMMC_ARASAN_PRESET_VALUE3_presetvalueforsdr50_END    (31)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_PRESET_VALUE4_UNION
 结构说明  : PRESET_VALUE4 寄存器结构定义。地址偏移量:0x6C，初值:0x00000000，宽度:32
 寄存器说明: 初始化模式配置4寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  presetvalueforsdr104 : 16; /* bit[0-15] : Preset Value for SDR104  */
        unsigned int  presetvalueforddr50  : 16; /* bit[16-31]: Preset Value for DDR50 */
    } reg;
} SOC_EMMC_ARASAN_PRESET_VALUE4_UNION;
#endif
#define SOC_EMMC_ARASAN_PRESET_VALUE4_presetvalueforsdr104_START  (0)
#define SOC_EMMC_ARASAN_PRESET_VALUE4_presetvalueforsdr104_END    (15)
#define SOC_EMMC_ARASAN_PRESET_VALUE4_presetvalueforddr50_START   (16)
#define SOC_EMMC_ARASAN_PRESET_VALUE4_presetvalueforddr50_END     (31)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_PRESET_VALUE5_UNION
 结构说明  : PRESET_VALUE5 寄存器结构定义。地址偏移量:0x74，初值:0x00000000，宽度:32
 寄存器说明: 初始化模式配置5寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  presetvalueforhs400 : 16; /* bit[0-15] : Preset Value for HS400 */
        unsigned int  reserved            : 16; /* bit[16-31]: reserved. */
    } reg;
} SOC_EMMC_ARASAN_PRESET_VALUE5_UNION;
#endif
#define SOC_EMMC_ARASAN_PRESET_VALUE5_presetvalueforhs400_START  (0)
#define SOC_EMMC_ARASAN_PRESET_VALUE5_presetvalueforhs400_END    (15)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_BOOT_TIMEOUT_CONTROL_REGISTER_UNION
 结构说明  : BOOT_TIMEOUT_CONTROL_REGISTER 寄存器结构定义。地址偏移量:0x70，初值:0x00000000，宽度:32
 寄存器说明: BOOT超时计数寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bootdatatimeoutcountervalue : 32; /* bit[0-31]: This value determines the interval by which DAT line time-outs are detected during boot operation for eMMC card.
                                                                      The value is in number of sd clock. */
    } reg;
} SOC_EMMC_ARASAN_BOOT_TIMEOUT_CONTROL_REGISTER_UNION;
#endif
#define SOC_EMMC_ARASAN_BOOT_TIMEOUT_CONTROL_REGISTER_bootdatatimeoutcountervalue_START  (0)
#define SOC_EMMC_ARASAN_BOOT_TIMEOUT_CONTROL_REGISTER_bootdatatimeoutcountervalue_END    (31)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_ENHANCED_STROBE_ENABLE_UNION
 结构说明  : ENHANCED_STROBE_ENABLE 寄存器结构定义。地址偏移量:0x78，初值:0x00000000，宽度:32
 寄存器说明: Enhanced Strobe使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  enhancedstrobe : 1;  /* bit[0]   : This bit enables the enhanced strobe logic of the Host Controller */
        unsigned int  reserved       : 31; /* bit[1-31]: reserved. */
    } reg;
} SOC_EMMC_ARASAN_ENHANCED_STROBE_ENABLE_UNION;
#endif
#define SOC_EMMC_ARASAN_ENHANCED_STROBE_ENABLE_enhancedstrobe_START  (0)
#define SOC_EMMC_ARASAN_ENHANCED_STROBE_ENABLE_enhancedstrobe_END    (0)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_CMD_QUEUEING_VERSION_UNION
 结构说明  : CMD_QUEUEING_VERSION 寄存器结构定义。地址偏移量:0x200，初值:0x00000510，宽度:32
 寄存器说明: CQ版本寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  emmcversionsuffix   : 4;  /* bit[0-3]  : eMMC Version Suffix (2nd digit right of decimal point), in BCD format */
        unsigned int  emmcminorversionnum : 4;  /* bit[4-7]  : eMMC Minor Version Number(digit right of decimal point), in BCD format */
        unsigned int  emmcmajorversionnum : 4;  /* bit[8-11] : eMMC Major Version Number (digit left of decimal point), in BCD format */
        unsigned int  reserved            : 20; /* bit[12-31]: reserved. */
    } reg;
} SOC_EMMC_ARASAN_CMD_QUEUEING_VERSION_UNION;
#endif
#define SOC_EMMC_ARASAN_CMD_QUEUEING_VERSION_emmcversionsuffix_START    (0)
#define SOC_EMMC_ARASAN_CMD_QUEUEING_VERSION_emmcversionsuffix_END      (3)
#define SOC_EMMC_ARASAN_CMD_QUEUEING_VERSION_emmcminorversionnum_START  (4)
#define SOC_EMMC_ARASAN_CMD_QUEUEING_VERSION_emmcminorversionnum_END    (7)
#define SOC_EMMC_ARASAN_CMD_QUEUEING_VERSION_emmcmajorversionnum_START  (8)
#define SOC_EMMC_ARASAN_CMD_QUEUEING_VERSION_emmcmajorversionnum_END    (11)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_CMD_QUEUEING_CAPABILITIES_UNION
 结构说明  : CMD_QUEUEING_CAPABILITIES 寄存器结构定义。地址偏移量:0x204，初值:0x00003001，宽度:32
 寄存器说明: CQ性能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  intertimerclkfreqval : 10; /* bit[0-9]  : Internal Timer Clock Frequency Value (ITCFVAL) 
                                                                TCFMUL and ITCFVAL indicate the frequency of the clock used for interrupt coalescing timer and for determining the polling period when using periodic SEND_QUEUE_ STATUS (CMD13) polling.
                                                                The clock frequency is calculated as ITCFVAL* ITCFMUL.
                                                                For example, to encode 19.2 MHz
                                                                ITCFVAL shall be C0h (= 192 decimal) and ITCFMUL 
                                                                shall be 2h (0.1 MHz) 192 * 0.1 MHz = 19.2 MHz */
        unsigned int  reserved_0           : 2;  /* bit[10-11]: reserved. */
        unsigned int  intertimerclkfreqmul : 4;  /* bit[12-15]: Internal Timer Clock Frequency Multiplier (ITCFMUL)
                                                                ITCFMUL and ITCFVAL indicate the frequency of the clock used for interrupt coalescing timer and for determining the SQS polling period. See ITCFVAL definition for details.
                                                                Field Value Description:
                                                                0h = 0.001 MHz
                                                                1h = 0.01 MHz
                                                                2h = 0.1 MHz
                                                                3h = 1 MHz
                                                                4h = 10 MHz
                                                                Other values are reserved */
        unsigned int  reserved_1           : 16; /* bit[16-31]: reserved. */
    } reg;
} SOC_EMMC_ARASAN_CMD_QUEUEING_CAPABILITIES_UNION;
#endif
#define SOC_EMMC_ARASAN_CMD_QUEUEING_CAPABILITIES_intertimerclkfreqval_START  (0)
#define SOC_EMMC_ARASAN_CMD_QUEUEING_CAPABILITIES_intertimerclkfreqval_END    (9)
#define SOC_EMMC_ARASAN_CMD_QUEUEING_CAPABILITIES_intertimerclkfreqmul_START  (12)
#define SOC_EMMC_ARASAN_CMD_QUEUEING_CAPABILITIES_intertimerclkfreqmul_END    (15)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_CMD_QUEUEING_CFG_UNION
 结构说明  : CMD_QUEUEING_CFG 寄存器结构定义。地址偏移量:0x208，初值:0x00000000，宽度:32
 寄存器说明: CQ配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cmdqueueing_en : 1;  /* bit[0]    : Software shall write ‘1’ this bit when in order to enable command queueing mode (i.e. enable CQE).
                                                          When this bit is 0, CQE is disabled and software controls the eMMC bus using the legacy eMMC host controller.
                                                          Before software writes ‘1’ to this bit, software shall verify that the eMMC host controller is in idle state and there are no commands or data transfers ongoing.
                                                          When software wants to exit command queueing mode, it shall clear all previous tasks if such exist before setting this bit to 0. */
        unsigned int  reserved_0     : 7;  /* bit[1-7]  : reserved. */
        unsigned int  taskdescsize   : 1;  /* bit[8]    : This bit indicates whether the task descriptor size is 128 bits or 64 bits as detailed in Data Structures section. This bit can only be configured when Command Queueing Enable bit is ‘0’
                                                          1 = Task descriptor size is 128 bits
                                                          0 = Task descriptor size is 64 bits */
        unsigned int  reserved_1     : 3;  /* bit[9-11] : reserved. */
        unsigned int  directcmd_en   : 1;  /* bit[12]   : Direct Command (DCMD) Enable
                                                          This bit indicates to the hardware whether the Task Descriptor in slot #31 of the TDL is a Data Transfer Task Descriptor, or a Direct Command Task Descriptor.
                                                          CQE uses this bit when a task is issued in slot #31, to determine how to decode the Task Descriptor.
                                                          Bit Value Description
                                                          1 = Task descriptor in slot #31 is a DCMD Task Descriptor
                                                          0 = Task descriptor in slot #31 is a Data Transfer Task Descriptor */
        unsigned int  reserved_2     : 19; /* bit[13-31]: reserved. */
    } reg;
} SOC_EMMC_ARASAN_CMD_QUEUEING_CFG_UNION;
#endif
#define SOC_EMMC_ARASAN_CMD_QUEUEING_CFG_cmdqueueing_en_START  (0)
#define SOC_EMMC_ARASAN_CMD_QUEUEING_CFG_cmdqueueing_en_END    (0)
#define SOC_EMMC_ARASAN_CMD_QUEUEING_CFG_taskdescsize_START    (8)
#define SOC_EMMC_ARASAN_CMD_QUEUEING_CFG_taskdescsize_END      (8)
#define SOC_EMMC_ARASAN_CMD_QUEUEING_CFG_directcmd_en_START    (12)
#define SOC_EMMC_ARASAN_CMD_QUEUEING_CFG_directcmd_en_END      (12)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_CMD_QUEUEING_CTRL_UNION
 结构说明  : CMD_QUEUEING_CTRL 寄存器结构定义。地址偏移量:0x20C，初值:0x00000000，宽度:32
 寄存器说明: CQ控制器寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  halt          : 1;  /* bit[0]   : Host software shall write ‘1’ to the bit when it wants to acquire software control over the eMMC bus and disable CQE from issuing commands on the bus.
                                                        For example, issuing a Discard Task command (CMDQ_TASK_MGMT)
                                                        When software writes ‘1’, CQE shall complete the ongoing task if such a task is in progress.
                                                        Once the task is completed and CQE is in idle state, CQE shall not issue new commands and shall indicate so to software by setting this bit to 1.
                                                        Software may poll on this bit until it is set to 1, and may only then send commands on the eMMC bus.
                                                        In order to exit halt state (i.e. resume CQE activity), software shall clear this bit (write ‘0’). Writing ‘0’ when the value is already ‘0’ shall have no effect. */
        unsigned int  reserved_0    : 7;  /* bit[1-7] : reserved. */
        unsigned int  clearalltasks : 1;  /* bit[8]   : Software shall write ‘1’ this bit when it wants to clear all the tasks sent to the device.
                                                        This bit can only be written when CQE is in halt state (i.e. Halt bit is 1).
                                                        When software writes 1, the value of the register is updated to ‘1’, and CQE shall reset CQTDBR register and all other context information for all unfinished tasks. 
                                                        Then CQE will clear this bit.
                                                        Software should poll on this bit until it is set to back 0 and may then resume normal operation, by clearing the Halt bit.
                                                        CQE does not communicate to the device that the tasks were cleared. It is software’s responsibility to order the device to discard the tasks in its queue using CMDQ_TASK_MGMT command.
                                                        Writing ‘0’ to this register shall have no effect */
        unsigned int  reserved_1    : 23; /* bit[9-31]: reserved. */
    } reg;
} SOC_EMMC_ARASAN_CMD_QUEUEING_CTRL_UNION;
#endif
#define SOC_EMMC_ARASAN_CMD_QUEUEING_CTRL_halt_START           (0)
#define SOC_EMMC_ARASAN_CMD_QUEUEING_CTRL_halt_END             (0)
#define SOC_EMMC_ARASAN_CMD_QUEUEING_CTRL_clearalltasks_START  (8)
#define SOC_EMMC_ARASAN_CMD_QUEUEING_CTRL_clearalltasks_END    (8)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_CQ_INTERRUPT_STATUS_UNION
 结构说明  : CQ_INTERRUPT_STATUS 寄存器结构定义。地址偏移量:0x210，初值:0x00000000，宽度:32
 寄存器说明: CQ中断状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  haltcompleteintr    : 1;  /* bit[0]   : This status bit is asserted (if CQISTE.HAC=1) when halt bit in CQCTL register transitions from 0 to 1 indicating that host controller has completed its current ongoing task and has entered halt state. */
        unsigned int  taskcompleteintr    : 1;  /* bit[1]   : This status bit is asserted(if CQISTE.TCC=1) when at least one of the following two conditions are met:
                                                              (1) A task is completed and the INT bit is set in its Task Descriptor(2) Interrupt caused by Interrupt Coalescing logic 
                                                              (2) Interrupt caused by Interrupt Coalescing logic (see Section C.4.9) */
        unsigned int  resperrdetectedintr : 1;  /* bit[2]   : This status bit is asserted (if CQISTE.RED=1) when a response is received with an error bit set in the device status field.The contents of the device status field are listed in Section 6.13.
                                                              Software uses CQRMEM register to configure which device status bit fields may trigger an interrupt, and which are masked. */
        unsigned int  taskcleared         : 1;  /* bit[3]   : This status bit is asserted (if CQISTE.TCL=1) when a task clear operation is completed by CQE. The com-pleted task clear operation is either an individual task clear (CQTCLR) or clearing of all tasks (CQCTL). */
        unsigned int  taskerrorintr       : 1;  /* bit[4]   : This bit is asserted when task error is detected due to invalid task descriptor. */
        unsigned int  reserved            : 27; /* bit[5-31]: reserved. */
    } reg;
} SOC_EMMC_ARASAN_CQ_INTERRUPT_STATUS_UNION;
#endif
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_STATUS_haltcompleteintr_START     (0)
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_STATUS_haltcompleteintr_END       (0)
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_STATUS_taskcompleteintr_START     (1)
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_STATUS_taskcompleteintr_END       (1)
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_STATUS_resperrdetectedintr_START  (2)
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_STATUS_resperrdetectedintr_END    (2)
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_STATUS_taskcleared_START          (3)
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_STATUS_taskcleared_END            (3)
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_STATUS_taskerrorintr_START        (4)
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_STATUS_taskerrorintr_END          (4)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_CQ_INTERRUPT_STATUS_ENABLE_UNION
 结构说明  : CQ_INTERRUPT_STATUS_ENABLE 寄存器结构定义。地址偏移量:0x214，初值:0x00000000，宽度:32
 寄存器说明: CQ中断状态使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  haltcompletestatus_en : 1;  /* bit[0]   : 1 = CQIS.HAC will be set when its interrupt condition is active
                                                                0 = CQIS.HAC is disabled */
        unsigned int  taskcompletestatus_en : 1;  /* bit[1]   : 1 = CQIS.TCC will be set when its interrupt condition is active
                                                                0 = CQIS.TCC is disabled */
        unsigned int  resperrdetecstatus_en : 1;  /* bit[2]   : 1 = CQIS.RED will be set when its interrupt condition is active
                                                                0 = CQIS.RED is disabled */
        unsigned int  taskclearedstatus_en  : 1;  /* bit[3]   : 1 = CQIS.TCL will be set when its interrupt condition is active
                                                                0 = CQIS.TCL is disabled */
        unsigned int  taskerrintrstatus_en  : 1;  /* bit[4]   : 1 = CQIS.TERR will be set when its interrupt condition is active
                                                                0 = CQIS.TERR is disabled */
        unsigned int  reserved              : 27; /* bit[5-31]: Reserved */
    } reg;
} SOC_EMMC_ARASAN_CQ_INTERRUPT_STATUS_ENABLE_UNION;
#endif
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_STATUS_ENABLE_haltcompletestatus_en_START  (0)
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_STATUS_ENABLE_haltcompletestatus_en_END    (0)
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_STATUS_ENABLE_taskcompletestatus_en_START  (1)
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_STATUS_ENABLE_taskcompletestatus_en_END    (1)
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_STATUS_ENABLE_resperrdetecstatus_en_START  (2)
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_STATUS_ENABLE_resperrdetecstatus_en_END    (2)
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_STATUS_ENABLE_taskclearedstatus_en_START   (3)
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_STATUS_ENABLE_taskclearedstatus_en_END     (3)
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_STATUS_ENABLE_taskerrintrstatus_en_START   (4)
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_STATUS_ENABLE_taskerrintrstatus_en_END     (4)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_CQ_INTERRUPT_SIGNAL_ENABLE_UNION
 结构说明  : CQ_INTERRUPT_SIGNAL_ENABLE 寄存器结构定义。地址偏移量:0x218，初值:0x00000000，宽度:32
 寄存器说明: CQ中断信号使能寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  haltcompletesig_en : 1;  /* bit[0]   : When set and CQIS.HAC is asserted, the CQE shall generate an interrupt */
        unsigned int  taskcompletesig_en : 1;  /* bit[1]   : When set and CQIS.TCC is asserted, the CQE shall generate an interrupt */
        unsigned int  resperrdetecsig_en : 1;  /* bit[2]   : When set and CQIS.RED is asserted, the CQE shall generate an interrupt */
        unsigned int  taskclearedsig_en  : 1;  /* bit[3]   : When set and CQIS.TCL is asserted, the CQE shall gen-erate an interrupt */
        unsigned int  taskerrintrsig_en  : 1;  /* bit[4]   : When set and CQIS.TERR is asserted, the CQE shall generate an interrupt */
        unsigned int  reserved           : 27; /* bit[5-31]: Reserved */
    } reg;
} SOC_EMMC_ARASAN_CQ_INTERRUPT_SIGNAL_ENABLE_UNION;
#endif
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_SIGNAL_ENABLE_haltcompletesig_en_START  (0)
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_SIGNAL_ENABLE_haltcompletesig_en_END    (0)
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_SIGNAL_ENABLE_taskcompletesig_en_START  (1)
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_SIGNAL_ENABLE_taskcompletesig_en_END    (1)
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_SIGNAL_ENABLE_resperrdetecsig_en_START  (2)
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_SIGNAL_ENABLE_resperrdetecsig_en_END    (2)
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_SIGNAL_ENABLE_taskclearedsig_en_START   (3)
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_SIGNAL_ENABLE_taskclearedsig_en_END     (3)
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_SIGNAL_ENABLE_taskerrintrsig_en_START   (4)
#define SOC_EMMC_ARASAN_CQ_INTERRUPT_SIGNAL_ENABLE_taskerrintrsig_en_END     (4)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_INTERRUPT_COALESCING_UNION
 结构说明  : INTERRUPT_COALESCING 寄存器结构定义。地址偏移量:0x21C，初值:0x00000000，宽度:32
 寄存器说明: 中断合并寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  intrcoaltimeoutval     : 7;  /* bit[0-6]  : Software uses this field to configure the maximum time allowed between the completion of a task on the bus and the generation of an interrupt.
                                                                  Timer Operation: The timer is reset by software during the interrupt service routine.
                                                                  It starts running when a data transfer task with INT=0 is completed, after the timer was reset. When the timer reaches the value configured in ICTOVAL field it generates an interrupt and stops.
                                                                  The timer’s unit is equal to 1024 clock periods of the clock whose frequency is specified in the nternal Timer Clock Frequency field CQCAP register.
                                                                  The minimum value is 01h (1024 clock periods) and the maximum value is 7Fh (127*1024 clock periods).
                                                                  For example, a CQCAP field value of 0 indicates a 19.2 MHz clock frequency (period = 52.08 ns). If the setting in ICTOVAL is 10h, the calculated polling period is 16*1024*52.08 ns= 853.33 us
                                                                  NOTE: When ICTOVAL is 0, the timer is not running, and timer-based interrupts are not generated.
                                                                  In order to write to this field, the ICTOVALWEN bit must be set at the same write operation. */
        unsigned int  intrcoaltimeoutval_wen : 1;  /* bit[7]    : When software writes ‘1’, the value ICTOVAL is updated with the contents written at the same cycle.
                                                                  When software writes ‘0’, the value in ICTOVAL is not updated.
                                                                  NOTE: Write operations to ICTOVAL are only allowed when the task queue is empty. */
        unsigned int  intrcoalcntthres       : 5;  /* bit[8-12] : Software uses this field to configure the number of task completions (only tasks withINT=0 in the Task Descrip-tor) which are required in order to generate an interrupt.
                                                                  Counter Operation: As data transfer tasks with INT=0 complete, they are counted by CQE. The counter is reset by software during the interrupt service routine.
                                                                  The counter stops counting when it reaches the value configured in ICCTH.
                                                                  The maximum allowed value is 31
                                                                  NOTE : When ICCTH is 0, task completions are not counted, and counting-based interrupts are not generated.
                                                                  In order to write to this field, the ICCTHWEN bit must be set at the same write operation. */
        unsigned int  reserved_0             : 2;  /* bit[13-14]: Reserved */
        unsigned int  intrcoalcntthres_wen   : 1;  /* bit[15]   : When software writes ‘1’, the value ICCTH is updated with the contents written at the same cycle.
                                                                  When software writes ‘0’, the value in ICCTH is not updated.
                                                                  NOTE: Write operations to ICCTH are only allowed when the task queue is empty. */
        unsigned int  cnttimerrst            : 1;  /* bit[16]   : When host driver writes ‘1’, the interrupt coalescing timer and counter are reset */
        unsigned int  reserved_1             : 3;  /* bit[17-19]: Reserved */
        unsigned int  intrcoalescingstatus   : 1;  /* bit[20]   : This bit indicates to software whether any tasks (with INT=0) have completed and counted towards interrupt coalescing(i.e., ICSB is set if and only if IC counter > 0).
                                                                  1 = At least one task completion has been counted (IC counter >0)
                                                                  0 = No task completions have occurred since last counter reset (IC counter =0) */
        unsigned int  reserved_2             : 10; /* bit[21-30]: Reserved */
        unsigned int  intrcoalescing_en      : 1;  /* bit[31]   : When set to ‘0’ by software, command responses are neither counted nor timed. Interrupts are still triggered by completion of tasks with INT=1 in the Task Descriptor.
                                                                  When set to ‘1’, the interrupt coalescing mechanism is enabled and coalesced interrupts are generated. */
    } reg;
} SOC_EMMC_ARASAN_INTERRUPT_COALESCING_UNION;
#endif
#define SOC_EMMC_ARASAN_INTERRUPT_COALESCING_intrcoaltimeoutval_START      (0)
#define SOC_EMMC_ARASAN_INTERRUPT_COALESCING_intrcoaltimeoutval_END        (6)
#define SOC_EMMC_ARASAN_INTERRUPT_COALESCING_intrcoaltimeoutval_wen_START  (7)
#define SOC_EMMC_ARASAN_INTERRUPT_COALESCING_intrcoaltimeoutval_wen_END    (7)
#define SOC_EMMC_ARASAN_INTERRUPT_COALESCING_intrcoalcntthres_START        (8)
#define SOC_EMMC_ARASAN_INTERRUPT_COALESCING_intrcoalcntthres_END          (12)
#define SOC_EMMC_ARASAN_INTERRUPT_COALESCING_intrcoalcntthres_wen_START    (15)
#define SOC_EMMC_ARASAN_INTERRUPT_COALESCING_intrcoalcntthres_wen_END      (15)
#define SOC_EMMC_ARASAN_INTERRUPT_COALESCING_cnttimerrst_START             (16)
#define SOC_EMMC_ARASAN_INTERRUPT_COALESCING_cnttimerrst_END               (16)
#define SOC_EMMC_ARASAN_INTERRUPT_COALESCING_intrcoalescingstatus_START    (20)
#define SOC_EMMC_ARASAN_INTERRUPT_COALESCING_intrcoalescingstatus_END      (20)
#define SOC_EMMC_ARASAN_INTERRUPT_COALESCING_intrcoalescing_en_START       (31)
#define SOC_EMMC_ARASAN_INTERRUPT_COALESCING_intrcoalescing_en_END         (31)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_CQ_TASK_DESCLIST_BASEADDRLOWER_UNION
 结构说明  : CQ_TASK_DESCLIST_BASEADDRLOWER 寄存器结构定义。地址偏移量:0x220，初值:0x00000000，宽度:32
 寄存器说明: 任务链表列表的地址的低位寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  taskdesclistbaseaddr_lower : 32; /* bit[0-31]: Task Descriptor List Base Address (TDLBA)
                                                                     This register stores the LSB bits (bits 31:0) of the byte address of the head of the Task Descriptor List in system memory.The size of the task descriptor list is 32 * (Task Descriptor size + Transfer Descriptor size) as configured by Host driver.This address shall be set on Byte1 KByte boundary.: The lower 10 bits of this register shall be set to 0 by software and shall be ignored by CQE. */
    } reg;
} SOC_EMMC_ARASAN_CQ_TASK_DESCLIST_BASEADDRLOWER_UNION;
#endif
#define SOC_EMMC_ARASAN_CQ_TASK_DESCLIST_BASEADDRLOWER_taskdesclistbaseaddr_lower_START  (0)
#define SOC_EMMC_ARASAN_CQ_TASK_DESCLIST_BASEADDRLOWER_taskdesclistbaseaddr_lower_END    (31)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_CQ_TASK_DESCLIST_BASEADDRUPEER_UNION
 结构说明  : CQ_TASK_DESCLIST_BASEADDRUPEER 寄存器结构定义。地址偏移量:0x224，初值:0x00000000，宽度:32
 寄存器说明: 任务链表列表的地址的高位寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  taskdesclistbaseaddr_upper : 32; /* bit[0-31]: Task Descriptor List Base Address (TDLBA)
                                                                     This register stores the MSB bits (bits 63:32) of the byte address of the head of the Task Descriptor List in system memory.The size of the task descriptor list is 32 * (Task Descriptor size + Transfer Descriptor size) as configured by Host driver.This register is reserved when using 32-bit addressing mode. */
    } reg;
} SOC_EMMC_ARASAN_CQ_TASK_DESCLIST_BASEADDRUPEER_UNION;
#endif
#define SOC_EMMC_ARASAN_CQ_TASK_DESCLIST_BASEADDRUPEER_taskdesclistbaseaddr_upper_START  (0)
#define SOC_EMMC_ARASAN_CQ_TASK_DESCLIST_BASEADDRUPEER_taskdesclistbaseaddr_upper_END    (31)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_CQ_TASK_DOORBELL_UNION
 结构说明  : CQ_TASK_DOORBELL 寄存器结构定义。地址偏移量:0x228，初值:0x00000000，宽度:32
 寄存器说明: 触发CQE处理新任务寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cmdqueuetaskdoorbell : 32; /* bit[0-31]: Command Queueing Task Doorbell
                                                               Software shall configure TDLBA and TDLBAU, and enable CQE in CQCFG before using this register.
                                                               Writing 1 to bit n of this register triggers CQE to start processing the task encoded in slot n of the TDL.
                                                               CQE always processes tasks in-order according to the order submitted to the list by CQTDBR write transactions.
                                                               CQE processes Data Transfer tasks by reading the Task Descriptor and sending QUEUED_TASK_PARAMS (CMD44) and QUEUED_TASK_ADDRESS (CMD45) commands to the device.
                                                               CQE processes DCMD tasks (in slot #31, when enabled) by reading the Task Descriptor, and generating the command encoded by its index and argument.
                                                               The corresponding bit is cleared to ‘0’ by CQE in one of the following events:
                                                               (a) When a task execution is completed (with success or error)
                                                               (b) The task is cleared using CQTCLR register
                                                               (c) All tasks are cleared using CQCTL register
                                                               (d) CQE is disabled using CQCFG register 
                                                               Software may initiate multiple tasks at the same time (batch submission) by writing 1 to multiple bits of this register in the same transaction.
                                                               In the case of batch submission:
                                                               CQE shall process the tasks in order of the task index, starting with the lowest index.
                                                               If one or more tasks in the batch are marked with QBR, the ordering of execution will be based on said processing order.
                                                               Writing 0 by software shall have no impact on the hardware, and will not change the value of the register bit. */
    } reg;
} SOC_EMMC_ARASAN_CQ_TASK_DOORBELL_UNION;
#endif
#define SOC_EMMC_ARASAN_CQ_TASK_DOORBELL_cmdqueuetaskdoorbell_START  (0)
#define SOC_EMMC_ARASAN_CQ_TASK_DOORBELL_cmdqueuetaskdoorbell_END    (31)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_CQ_TASK_DOORBELL_NOTIFICATION_UNION
 结构说明  : CQ_TASK_DOORBELL_NOTIFICATION 寄存器结构定义。地址偏移量:0x22C，初值:0x00000000，宽度:32
 寄存器说明: 已完成任务报告寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  taskcomplnotification : 32; /* bit[0-31]: CQE shall set bit n of this register (at the same time it clears bit n of CQTDBR) when a task execution is com-pleted (with success or error).
                                                                When receiving interrupt for task completion, software may read this register to know which tasks have finished.
                                                                After reading this register, software may clear the relevant bit fields by writing 1 to the corresponding bits. */
    } reg;
} SOC_EMMC_ARASAN_CQ_TASK_DOORBELL_NOTIFICATION_UNION;
#endif
#define SOC_EMMC_ARASAN_CQ_TASK_DOORBELL_NOTIFICATION_taskcomplnotification_START  (0)
#define SOC_EMMC_ARASAN_CQ_TASK_DOORBELL_NOTIFICATION_taskcomplnotification_END    (31)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_CQ_DEVICE_QUEUE_STATUS_UNION
 结构说明  : CQ_DEVICE_QUEUE_STATUS 寄存器结构定义。地址偏移量:0x230，初值:0x00000000，宽度:32
 寄存器说明: CQ设备排队状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  devqueuestatus : 32; /* bit[0-31]: Device Queue Status
                                                         Every time the Host controller receives a queue status register (QSR) from the device, it updates this register with the response of status command, i.e. the device’s queue status. */
    } reg;
} SOC_EMMC_ARASAN_CQ_DEVICE_QUEUE_STATUS_UNION;
#endif
#define SOC_EMMC_ARASAN_CQ_DEVICE_QUEUE_STATUS_devqueuestatus_START  (0)
#define SOC_EMMC_ARASAN_CQ_DEVICE_QUEUE_STATUS_devqueuestatus_END    (31)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_CQ_DEVICE_PENDING_TASK_UNION
 结构说明  : CQ_DEVICE_PENDING_TASK 寄存器结构定义。地址偏移量:0x234，初值:0x00000000，宽度:32
 寄存器说明: CQ设备待执行任务寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  devpendtask : 32; /* bit[0-31]: Bit n of this register is set if and only if 
                                                      QUEUED_TASK_PARAMS (CMD44) and QUEUED_TASK_ADDRESS (CMD45) were sent for this specific task and if this task hasn’t been executed yet.
                                                      CQE shall set this bit after receiving a successful response for CMD45. CQE shall clear this bit after the task has completed execution.
                                                      Software needs to read this register in the task-discard procedure, when the controller is halted, to determine if the task is queued in the device. If the task is queued, the driver sends a CMDQ_TASK_MGMT (CMD48) to the device ordering it to discard the task. Then software clears the task in the CQE. Only then the software orders CQE to resume its operation using CQCTL register. */
    } reg;
} SOC_EMMC_ARASAN_CQ_DEVICE_PENDING_TASK_UNION;
#endif
#define SOC_EMMC_ARASAN_CQ_DEVICE_PENDING_TASK_devpendtask_START  (0)
#define SOC_EMMC_ARASAN_CQ_DEVICE_PENDING_TASK_devpendtask_END    (31)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_CQ_TASK_CLEAR_UNION
 结构说明  : CQ_TASK_CLEAR 寄存器结构定义。地址偏移量:0x238，初值:0x00000000，宽度:32
 寄存器说明: CQ任务清除寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cmdqueueingtaskclr : 32; /* bit[0-31]: Command Queueing Task Clear
                                                             Writing 1 to bit n of this register orders CQE to clear a task which software has previously issued.
                                                             This bit can only be written when CQE is in Halt state as indicated in CQCFG register Halt bit.
                                                             When software writes ‘1’ to a bit in this register, CQE updates the value to ‘1’, and starts clearing the data structures related to the task. CQE clears the bit fields (sets a value of 0) in CQTCLR and in CQTDBR once clear operation is complete.
                                                             Software should poll on the CQTCLR until it is cleared to verify clear operation was complete.
                                                             Writing to this register only clears the task in the CQE and does not have impact on the device. In order to discard the task in the device, host software shall send CMDQ_TASK _MGMT while CQE is still in Halt state.
                                                             Host driver is not allowed to use this register to clear multiple tasks at the same time. Clearing multiple tasks can be done using CQCTL register.
                                                             Writing 0 to a register bit shall have no impact. */
    } reg;
} SOC_EMMC_ARASAN_CQ_TASK_CLEAR_UNION;
#endif
#define SOC_EMMC_ARASAN_CQ_TASK_CLEAR_cmdqueueingtaskclr_START  (0)
#define SOC_EMMC_ARASAN_CQ_TASK_CLEAR_cmdqueueingtaskclr_END    (31)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_SEND_STATUS_TIMER_CFG1_UNION
 结构说明  : SEND_STATUS_TIMER_CFG1 寄存器结构定义。地址偏移量:0x240，初值:0x00000000，宽度:32
 寄存器说明: 发送状态计时器配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sendstatuscmdidletimer : 16; /* bit[0-15] : Send Status Command Idle Timer
                                                                  This field indicates to CQE the polling period to use when using periodic SEND_QUEUE_STATUS (CMD13) 
                                                                  polling.
                                                                  Periodic polling is used when tasks are pending in the device, but no data transfer is in progress. When a SEND_QUEUE_STATUS response indicating that no task is ready for execution, CQE counts the configured time until it issues the next SEND_QUEUE_STATUS.
                                                                  Timer units are clock periods of the clock whose frequency is specified in the Internal Timer Clock Frequency field CQCAP register.
                                                                  The minimum value is 0001h (1 clock period) and the maximum value is FFFFh (65535 clock periods). Default interval is: 4096 clock periods.
                                                                  For example, a CQCAP field value of 0 indicates a 19.2 MHz clock frequency (period = 52.08 ns). If the setting in CQSST is 1000h, the calcu.lated polling period is 4096*52.08 ns= 213.33 us. */
        unsigned int  sendstatuscmdblockcnt  : 4;  /* bit[16-19]: Send Status Command Block Counter
                                                                  This field indicates to CQE when to send SEND_QUEUE_STATUS (CMD13) command to inquire the status of the device’s task queue.
                                                                  A value of n means CQE shall send status command on the CMD line, during the transfer of data block 
                                                                  BLOCK_CNT-n, on the data lines, where BLOCK_CNT is the number of blocks in the current transaction.
                                                                  A value of 0 means that SEND_QUEUE_STATUS (CMD13) command shall not be sent during the transaction. Instead it will be sent only when the data lines are idle.
                                                                  A value of 1 means that STATUS command is to be sent during the last block of the transaction. */
        unsigned int  reserved               : 12; /* bit[20-31]: reserved. */
    } reg;
} SOC_EMMC_ARASAN_SEND_STATUS_TIMER_CFG1_UNION;
#endif
#define SOC_EMMC_ARASAN_SEND_STATUS_TIMER_CFG1_sendstatuscmdidletimer_START  (0)
#define SOC_EMMC_ARASAN_SEND_STATUS_TIMER_CFG1_sendstatuscmdidletimer_END    (15)
#define SOC_EMMC_ARASAN_SEND_STATUS_TIMER_CFG1_sendstatuscmdblockcnt_START   (16)
#define SOC_EMMC_ARASAN_SEND_STATUS_TIMER_CFG1_sendstatuscmdblockcnt_END     (19)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_SEND_STATUS_CFG2_UNION
 结构说明  : SEND_STATUS_CFG2 寄存器结构定义。地址偏移量:0x244，初值:0x00000000，宽度:32
 寄存器说明: 发送状态配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sendqueuerca : 16; /* bit[0-15] : This field provides CQE with the contents of the 16-bit RCA field in SEND_QUEUE_ STATUS (CMD13) com-mand. argument. 
                                                        CQE shall copy this field to bits 31:16 of the argument when transmitting SEND_ QUEUE_STATUS (CMD13) command. */
        unsigned int  reserved     : 16; /* bit[16-31]: reserved. */
    } reg;
} SOC_EMMC_ARASAN_SEND_STATUS_CFG2_UNION;
#endif
#define SOC_EMMC_ARASAN_SEND_STATUS_CFG2_sendqueuerca_START  (0)
#define SOC_EMMC_ARASAN_SEND_STATUS_CFG2_sendqueuerca_END    (15)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_CMDRESP_FOR_DIRECTCMDTASK_UNION
 结构说明  : CMDRESP_FOR_DIRECTCMDTASK 寄存器结构定义。地址偏移量:0x248，初值:0x00000000，宽度:32
 寄存器说明: 直接命令任务的回复寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  direcmdlastresp : 32; /* bit[0-31]: Direct Command Last Response
                                                          This register contains the response of the command generated by the last direct-command (DCMD) task which was sent.
                                                          CQE shall update this register when it receives the response for a DCMD task.
                                                          This register is considered valid only after bit 31 of CQTDBR register is cleared by CQE. */
    } reg;
} SOC_EMMC_ARASAN_CMDRESP_FOR_DIRECTCMDTASK_UNION;
#endif
#define SOC_EMMC_ARASAN_CMDRESP_FOR_DIRECTCMDTASK_direcmdlastresp_START  (0)
#define SOC_EMMC_ARASAN_CMDRESP_FOR_DIRECTCMDTASK_direcmdlastresp_END    (31)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_RESP_MODE_ERROR_MASK_UNION
 结构说明  : RESP_MODE_ERROR_MASK 寄存器结构定义。地址偏移量:0x250，初值:0xFDF9A080，宽度:32
 寄存器说明: RED中断产生控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  respmodeerrmask : 32; /* bit[0-31]: This bit is used as in interrupt mask on the device status filed which is received in R1/R1b responses.
                                                          1 = When a R1/R1b response is received, with bit i in the device status set, a RED interrupt is generated
                                                          0 = When a R1/R1b response is received, bit i in the device status is ignored
                                                          The reset value of this register is set to trigger an interrupt on all “Error” type bits in the device status, as defined in Section 6.13.
                                                          NOTE: Responses to CMD13 (SQS) encode the QSR, so they are ignored by this logic. */
    } reg;
} SOC_EMMC_ARASAN_RESP_MODE_ERROR_MASK_UNION;
#endif
#define SOC_EMMC_ARASAN_RESP_MODE_ERROR_MASK_respmodeerrmask_START  (0)
#define SOC_EMMC_ARASAN_RESP_MODE_ERROR_MASK_respmodeerrmask_END    (31)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_TASK_ERROR_INFO_UNION
 结构说明  : TASK_ERROR_INFO 寄存器结构定义。地址偏移量:0x254，初值:0x00000000，宽度:32
 寄存器说明: 任务错误信息寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  respmodeerrcmdindex     : 6;  /* bit[0-5]  : This field indicates the index of the command which was executed on the command line when an error occurred.
                                                                   The field is updated if a command transaction is in progress when an error is detected by CQE, or indicated by eMMC controller. */
        unsigned int  reserved_0              : 2;  /* bit[6-7]  : reserved. */
        unsigned int  respmode0errtaskid      : 5;  /* bit[8-12] : This field indicates the ID of the task which was executed on the command line when an error occurred.
                                                                   The field is updated if a command transaction is in progress when an error is detected by CQE, or indicated 
                                                                   by eMMC controller. */
        unsigned int  reserved_1              : 2;  /* bit[13-14]: reserved. */
        unsigned int  respmodeerrfieldsvalid  : 1;  /* bit[15]   : This bit is updated when an error is detected by CQE, or indicated by eMMC controller.
                                                                   If a command transaction is in progress when the error is detected/indicated, the bit is set to 1.
                                                                   If a no command transaction is in progress when the error is detected/indicated, the bit is cleared to 0. */
        unsigned int  datatranserrcmdindex    : 6;  /* bit[16-21]: This field indicates the index of the command which was executed on the data lines when an error occurred. */
        unsigned int  reserved_2              : 2;  /* bit[22-23]: reserved. */
        unsigned int  datatranserrtaskid      : 5;  /* bit[24-28]: This field indicates the ID of the task which was executed on the data lines when an error occurred.
                                                                   The field is updated if a data transfer is in progress when an error is detected by CQE, or indicated by eMMC con-troller */
        unsigned int  reserved_3              : 2;  /* bit[29-30]: reserved. */
        unsigned int  datatranserrfieldsvalid : 1;  /* bit[31]   : This bit is updated when an error is detected by CQE, or indicated by eMMC controller.
                                                                   If a data transfer is in progress when the error is detected/indicated, the bit is set to 1.
                                                                   If a no data transfer is in progress when the error is detected/indicated, the bit is cleared to 0. */
    } reg;
} SOC_EMMC_ARASAN_TASK_ERROR_INFO_UNION;
#endif
#define SOC_EMMC_ARASAN_TASK_ERROR_INFO_respmodeerrcmdindex_START      (0)
#define SOC_EMMC_ARASAN_TASK_ERROR_INFO_respmodeerrcmdindex_END        (5)
#define SOC_EMMC_ARASAN_TASK_ERROR_INFO_respmode0errtaskid_START       (8)
#define SOC_EMMC_ARASAN_TASK_ERROR_INFO_respmode0errtaskid_END         (12)
#define SOC_EMMC_ARASAN_TASK_ERROR_INFO_respmodeerrfieldsvalid_START   (15)
#define SOC_EMMC_ARASAN_TASK_ERROR_INFO_respmodeerrfieldsvalid_END     (15)
#define SOC_EMMC_ARASAN_TASK_ERROR_INFO_datatranserrcmdindex_START     (16)
#define SOC_EMMC_ARASAN_TASK_ERROR_INFO_datatranserrcmdindex_END       (21)
#define SOC_EMMC_ARASAN_TASK_ERROR_INFO_datatranserrtaskid_START       (24)
#define SOC_EMMC_ARASAN_TASK_ERROR_INFO_datatranserrtaskid_END         (28)
#define SOC_EMMC_ARASAN_TASK_ERROR_INFO_datatranserrfieldsvalid_START  (31)
#define SOC_EMMC_ARASAN_TASK_ERROR_INFO_datatranserrfieldsvalid_END    (31)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_CMD_RESP_INDEX_UNION
 结构说明  : CMD_RESP_INDEX 寄存器结构定义。地址偏移量:0x258，初值:0x00000000，宽度:32
 寄存器说明: CMD回复编号寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lastcmdrespindex : 6;  /* bit[0-5] : This field stores the index of the last received command response. CQE shall update the value every time a command response is received. */
        unsigned int  reserved         : 26; /* bit[6-31]: reserved. */
    } reg;
} SOC_EMMC_ARASAN_CMD_RESP_INDEX_UNION;
#endif
#define SOC_EMMC_ARASAN_CMD_RESP_INDEX_lastcmdrespindex_START  (0)
#define SOC_EMMC_ARASAN_CMD_RESP_INDEX_lastcmdrespindex_END    (5)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_CMD_RESP_ARGUMENT_UNION
 结构说明  : CMD_RESP_ARGUMENT 寄存器结构定义。地址偏移量:0x25C，初值:0x00000000，宽度:32
 寄存器说明: CMD回复参数寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lastcmdrespargumemt : 32; /* bit[0-31]: This field stores the argument of the last received command. CQE shall update the value every time a command response is received. */
    } reg;
} SOC_EMMC_ARASAN_CMD_RESP_ARGUMENT_UNION;
#endif
#define SOC_EMMC_ARASAN_CMD_RESP_ARGUMENT_lastcmdrespargumemt_START  (0)
#define SOC_EMMC_ARASAN_CMD_RESP_ARGUMENT_lastcmdrespargumemt_END    (31)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_CORE_CFG0_UNION
 结构说明  : CORE_CFG0 寄存器结构定义。地址偏移量:0x400，初值:0x400F20F9，宽度:32
 寄存器说明: IP配置0寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  corecfg_1p8voltsupport   : 1;  /* bit[0]    : 0 - 1.8 V Not Supported
                                                                    1 - 1.8 V Supported */
        unsigned int  corecfg_3p0voltsupport   : 1;  /* bit[1]    : 0 - 3.0 V Not Supported
                                                                    1 - 3.0 V Supported */
        unsigned int  corecfg_3p3voltsupport   : 1;  /* bit[2]    : 0 - 3.3 V Not Supported
                                                                    1 - 3.3 V Supported */
        unsigned int  corecfg_suspressupport   : 1;  /* bit[3]    : This bit indicates whether the HC supports Suspend / Resume functionality. If this bit is 0, the Suspend and Resume mechanism are not supported and the HD shall not issue either Suspend / Resume commands.
                                                                    0 - Not Supported
                                                                    1 - Supported */
        unsigned int  corecfg_sdmasupport      : 1;  /* bit[4]    : This bit indicates whether the HC is capable of using DMA to transfer data between system memory and the HC directly.
                                                                    0 - SDMA Not Supported
                                                                    1 - SDMA Supported. */
        unsigned int  corecfg_highspeedsupport : 1;  /* bit[5]    : This bit indicates whether the HC and the Host System support High Speed mode and they can supply SD Clock frequency from 25Mhz to 50 Mhz (for SD)/ 20MHz to 52MHz (for MMC).
                                                                    0 - High Speed Not Supported
                                                                    1 - High Speed Supported */
        unsigned int  corecfg_adma2support     : 1;  /* bit[6]    : 1 - ADMA2 support.
                                                                    0 - ADMA2 not support */
        unsigned int  corecfg_8bitsupport      : 1;  /* bit[7]    : This bit indicates whether the Host Controller is capable of using 8-bit bus width mode. This bit is not effective when Slot Type is set to 10b. In this case, refer to Bus Width Preset in the Shared Bus resister.
                                                                    1 - Extended Media Bus Supported
                                                                    0 - Extended Media Bus not Supported */
        unsigned int  corecfg_maxblklength     : 2;  /* bit[8-9]  : This value indicates the maximum block size that the HD can read and write to the buffer in the HC. The buffer shall transfer this block size without wait cycles. Three sizes can be defined as indicated below.
                                                                    00 - 512 byte
                                                                    01 - 1024 byte
                                                                    10 - 2048 byte
                                                                    11 - 4096 byte */
        unsigned int  corecfg_baseclkfreq      : 8;  /* bit[10-17]: (1) 6-bit Base Clock Frequency
                                                                    This mode is supported by the Host Controller Version 1.00 and 2.00. Upper 2-bit is not effective and always 0. Unit values are 1MHz. The supported clock range is 10MHz to 63MHz. */
        unsigned int  corecfg_timeoutclkunit   : 1;  /* bit[18]   : This bit shows the base clock frequency used to detect Data Time-out Error.
                                                                    Not 0 - 1Khz to 63Khz or 1Mhz to 63Mhz
                                                                    000000b - Get Information via another method. */
        unsigned int  corecfg_timeoutclkfreq   : 6;  /* bit[19-24]: This bit shows the unit of base clock frequency used to detect Data Timeout Error.
                                                                    0 - Khz
                                                                    1 - Mhz */
        unsigned int  corecfg_tuningcount      : 6;  /* bit[25-30]: tuning_count */
        unsigned int  corecfg_asyncwkupena     : 1;  /* bit[31]   : async wake up enable */
    } reg;
} SOC_EMMC_ARASAN_CORE_CFG0_UNION;
#endif
#define SOC_EMMC_ARASAN_CORE_CFG0_corecfg_1p8voltsupport_START    (0)
#define SOC_EMMC_ARASAN_CORE_CFG0_corecfg_1p8voltsupport_END      (0)
#define SOC_EMMC_ARASAN_CORE_CFG0_corecfg_3p0voltsupport_START    (1)
#define SOC_EMMC_ARASAN_CORE_CFG0_corecfg_3p0voltsupport_END      (1)
#define SOC_EMMC_ARASAN_CORE_CFG0_corecfg_3p3voltsupport_START    (2)
#define SOC_EMMC_ARASAN_CORE_CFG0_corecfg_3p3voltsupport_END      (2)
#define SOC_EMMC_ARASAN_CORE_CFG0_corecfg_suspressupport_START    (3)
#define SOC_EMMC_ARASAN_CORE_CFG0_corecfg_suspressupport_END      (3)
#define SOC_EMMC_ARASAN_CORE_CFG0_corecfg_sdmasupport_START       (4)
#define SOC_EMMC_ARASAN_CORE_CFG0_corecfg_sdmasupport_END         (4)
#define SOC_EMMC_ARASAN_CORE_CFG0_corecfg_highspeedsupport_START  (5)
#define SOC_EMMC_ARASAN_CORE_CFG0_corecfg_highspeedsupport_END    (5)
#define SOC_EMMC_ARASAN_CORE_CFG0_corecfg_adma2support_START      (6)
#define SOC_EMMC_ARASAN_CORE_CFG0_corecfg_adma2support_END        (6)
#define SOC_EMMC_ARASAN_CORE_CFG0_corecfg_8bitsupport_START       (7)
#define SOC_EMMC_ARASAN_CORE_CFG0_corecfg_8bitsupport_END         (7)
#define SOC_EMMC_ARASAN_CORE_CFG0_corecfg_maxblklength_START      (8)
#define SOC_EMMC_ARASAN_CORE_CFG0_corecfg_maxblklength_END        (9)
#define SOC_EMMC_ARASAN_CORE_CFG0_corecfg_baseclkfreq_START       (10)
#define SOC_EMMC_ARASAN_CORE_CFG0_corecfg_baseclkfreq_END         (17)
#define SOC_EMMC_ARASAN_CORE_CFG0_corecfg_timeoutclkunit_START    (18)
#define SOC_EMMC_ARASAN_CORE_CFG0_corecfg_timeoutclkunit_END      (18)
#define SOC_EMMC_ARASAN_CORE_CFG0_corecfg_timeoutclkfreq_START    (19)
#define SOC_EMMC_ARASAN_CORE_CFG0_corecfg_timeoutclkfreq_END      (24)
#define SOC_EMMC_ARASAN_CORE_CFG0_corecfg_tuningcount_START       (25)
#define SOC_EMMC_ARASAN_CORE_CFG0_corecfg_tuningcount_END         (30)
#define SOC_EMMC_ARASAN_CORE_CFG0_corecfg_asyncwkupena_START      (31)
#define SOC_EMMC_ARASAN_CORE_CFG0_corecfg_asyncwkupena_END        (31)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_CORE_CFG1_UNION
 结构说明  : CORE_CFG1 寄存器结构定义。地址偏移量:0x404，初值:0x1FF08000，宽度:32
 寄存器说明: IP配置1寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved                  : 3;  /* bit[0-2]  : reserved. */
        unsigned int  corecfg_spiblkmode        : 1;  /* bit[3]    : Spi block mode
                                                                     0 - Not Supported
                                                                     1 - Supported */
        unsigned int  corecfg_spisupport        : 1;  /* bit[4]    : Spi mode
                                                                     0 - Not Supported
                                                                     1 - Supported */
        unsigned int  corecfg_clockmultiplier   : 8;  /* bit[5-12] : This field indicates clock multiplier value of programmable clock generator. Refer to Clock Control register. Setting 00h means that Host Controller does not support programmable clock generator.
                                                                     FFh Clock Multiplier M = 256
                                                                     ....
                                                                     02h Clock Multiplier M = 3
                                                                     01h Clock Multiplier M = 2
                                                                     00h Clock Multiplier is Not Supported */
        unsigned int  corecfg_retuningmodes     : 2;  /* bit[13-14]: This field defines the re-tuning capability of a Host Controller and how to manage the data transfer length and a Re-Tuning Timer by the Host Driver
                                                                     00 - Mode1
                                                                     01 - Mode2
                                                                     10 - Mode3
                                                                     11 - Reserved
                                                                     There are two re-tuning timings: 
                                                                     Re-Tuning Request and expiration of a Re-Tuning Timer. By receiving either timing, the Host Driver executes the re-tuning procedure just before a next command issue */
        unsigned int  corecfg_tuningforsdr50    : 1;  /* bit[15]   : If this bit is set to 1, this Host Controller requires tuning to operate SDR50. (Tuning is always required to operate SDR104.)
                                                                     1 SDR50 requires tuning
                                                                     0 SDR50 does not require tuning */
        unsigned int  corecfg_retuningtimercnt  : 4;  /* bit[16-19]: This field indicates an initial value of the Re-Tuning Timer for Re-Tuning Mode 1 to 3.
                                                                     0h - Get information via other source
                                                                     1h = 1 seconds
                                                                     2h = 2 seconds
                                                                     3h = 4 seconds
                                                                     --
                                                                     Bh = 1024 seconds
                                                                     Fh - Ch = Reserved */
        unsigned int  corecfg_type4support      : 1;  /* bit[20]   : Driver Type 4 Support
                                                                     1 Driver Type 4 is Supported
                                                                     0 Driver Type 4 is Not Supported */
        unsigned int  corecfg_ddriversupport    : 1;  /* bit[21]   : This bit indicates support of Driver
                                                                     Type D for 1.8 Signaling.
                                                                     1 Driver Type D is Supported
                                                                     0 Driver Type D is Not Supported */
        unsigned int  corecfg_cdriversupport    : 1;  /* bit[22]   : This bit indicates support of Driver
                                                                     Type D for 1.8 Signaling.
                                                                     1 Driver Type C is Supported
                                                                     0 Driver Type C is Not Supported */
        unsigned int  corecfg_adriversupport    : 1;  /* bit[23]   : This bit indicates support of Driver
                                                                     Type D for 1.8 Signaling.
                                                                     1 Driver Type A is Supported
                                                                     0 Driver Type A is Not Supported */
        unsigned int  corecfg_hs400support      : 1;  /* bit[24]   : 1 HS400 is Supported
                                                                     0 HS400 is Not Supported */
        unsigned int  corecfg_ddr50support      : 1;  /* bit[25]   : 1 DDR50 is Supported
                                                                     0 DDR50 is Not Supported */
        unsigned int  corecfg_sdr104support     : 1;  /* bit[26]   : SDR104 requires tuning.
                                                                     1 SDR104 is Supported
                                                                     0 SDR104 is Not Supported */
        unsigned int  corecfg_sdr50support      : 1;  /* bit[27]   : If SDR104 is supported, this bit shall be set to 1. Bit 40 indicates whether SDR50 requires tuning or not.
                                                                     1 SDR50 is Supported
                                                                     0 SDR50 is Not Supported */
        unsigned int  corecfg_slottype          : 2;  /* bit[28-29]: This field indicates usage of a slot by a specific Host System.
                                                                     10b Shared Bus Slot
                                                                     11b Reserved */
        unsigned int  corecfg_asynchintrsupport : 1;  /* bit[30]   : Refer to SDIO Specification Version 3.00 about asynchronous interrupt.
                                                                     1 Asynchronous Interrupt Supported
                                                                     0 Asynchronous Interrupt Not Supported */
        unsigned int  corecfg_64bitsupport      : 1;  /* bit[31]   : 1 - supports 64 bit system address
                                                                     0 - Does not support 64 bit system address */
    } reg;
} SOC_EMMC_ARASAN_CORE_CFG1_UNION;
#endif
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_spiblkmode_START         (3)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_spiblkmode_END           (3)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_spisupport_START         (4)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_spisupport_END           (4)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_clockmultiplier_START    (5)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_clockmultiplier_END      (12)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_retuningmodes_START      (13)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_retuningmodes_END        (14)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_tuningforsdr50_START     (15)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_tuningforsdr50_END       (15)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_retuningtimercnt_START   (16)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_retuningtimercnt_END     (19)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_type4support_START       (20)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_type4support_END         (20)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_ddriversupport_START     (21)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_ddriversupport_END       (21)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_cdriversupport_START     (22)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_cdriversupport_END       (22)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_adriversupport_START     (23)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_adriversupport_END       (23)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_hs400support_START       (24)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_hs400support_END         (24)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_ddr50support_START       (25)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_ddr50support_END         (25)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_sdr104support_START      (26)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_sdr104support_END        (26)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_sdr50support_START       (27)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_sdr50support_END         (27)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_slottype_START           (28)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_slottype_END             (29)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_asynchintrsupport_START  (30)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_asynchintrsupport_END    (30)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_64bitsupport_START       (31)
#define SOC_EMMC_ARASAN_CORE_CFG1_corecfg_64bitsupport_END         (31)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE0_UNION
 结构说明  : CORECFG_PRESET_VALUE0 寄存器结构定义。地址偏移量:0x408，初值:0x00000000，宽度:32
 寄存器说明: 模式预设0寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  corecfg_dspdpresetval : 13; /* bit[0-12] : Preset Value for Default Speed */
        unsigned int  reserved_0            : 3;  /* bit[13-15]: reserved. */
        unsigned int  corecfg_initpresetval : 13; /* bit[16-28]: Preset Value for Initialization.
                                                                 presetval[12:11]: Driver Strength Select Value[1:0]
                                                                 presetval[10]: Clock Generator Select Value
                                                                 presetval[9:0]: SDCLK Frequency Select Value [9:0]  */
        unsigned int  reserved_1            : 3;  /* bit[29-31]: reserved. */
    } reg;
} SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE0_UNION;
#endif
#define SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE0_corecfg_dspdpresetval_START  (0)
#define SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE0_corecfg_dspdpresetval_END    (12)
#define SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE0_corecfg_initpresetval_START  (16)
#define SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE0_corecfg_initpresetval_END    (28)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE1_UNION
 结构说明  : CORECFG_PRESET_VALUE1 寄存器结构定义。地址偏移量:0x40C，初值:0x00000000，宽度:32
 寄存器说明: 模式预设1寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  corecfg_sdr12presetval : 13; /* bit[0-12] : Preset Value for SDR12 */
        unsigned int  reserved_0             : 3;  /* bit[13-15]: reserved. */
        unsigned int  corecfg_hspdpresetval  : 13; /* bit[16-28]: Preset Value for High Speed */
        unsigned int  reserved_1             : 3;  /* bit[29-31]: reserved. */
    } reg;
} SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE1_UNION;
#endif
#define SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE1_corecfg_sdr12presetval_START  (0)
#define SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE1_corecfg_sdr12presetval_END    (12)
#define SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE1_corecfg_hspdpresetval_START   (16)
#define SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE1_corecfg_hspdpresetval_END     (28)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE2_UNION
 结构说明  : CORECFG_PRESET_VALUE2 寄存器结构定义。地址偏移量:0x410，初值:0x00000000，宽度:32
 寄存器说明: 模式预设2寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  corecfg_sdr50presetval : 13; /* bit[0-12] : Preset Value for SDR50 */
        unsigned int  reserved_0             : 3;  /* bit[13-15]: reserved. */
        unsigned int  corecfg_sdr25presetval : 13; /* bit[16-28]: Preset Value for SDR25 */
        unsigned int  reserved_1             : 3;  /* bit[29-31]: reserved. */
    } reg;
} SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE2_UNION;
#endif
#define SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE2_corecfg_sdr50presetval_START  (0)
#define SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE2_corecfg_sdr50presetval_END    (12)
#define SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE2_corecfg_sdr25presetval_START  (16)
#define SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE2_corecfg_sdr25presetval_END    (28)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE3_UNION
 结构说明  : CORECFG_PRESET_VALUE3 寄存器结构定义。地址偏移量:0x414，初值:0x00000000，宽度:32
 寄存器说明: 模式预设3寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  corecfg_ddr50presetval  : 13; /* bit[0-12] : Preset Value for DDR50 */
        unsigned int  reserved_0              : 3;  /* bit[13-15]: reserved */
        unsigned int  corecfg_sdr104presetval : 13; /* bit[16-28]: Preset Value for SDR104 */
        unsigned int  reserved_1              : 3;  /* bit[29-31]: reserved. */
    } reg;
} SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE3_UNION;
#endif
#define SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE3_corecfg_ddr50presetval_START   (0)
#define SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE3_corecfg_ddr50presetval_END     (12)
#define SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE3_corecfg_sdr104presetval_START  (16)
#define SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE3_corecfg_sdr104presetval_END    (28)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE4_UNION
 结构说明  : CORECFG_PRESET_VALUE4 寄存器结构定义。地址偏移量:0x418，初值:0x00000000，宽度:32
 寄存器说明: 模式预设4寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  corecfg_hs400presetval : 13; /* bit[0-12] : Preset Value for HS400 */
        unsigned int  reserved               : 19; /* bit[13-31]: reserved. */
    } reg;
} SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE4_UNION;
#endif
#define SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE4_corecfg_hs400presetval_START  (0)
#define SOC_EMMC_ARASAN_CORECFG_PRESET_VALUE4_corecfg_hs400presetval_END    (12)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_CORE_CFG2_UNION
 结构说明  : CORE_CFG2 寄存器结构定义。地址偏移量:0x41C，初值:0x00000000，宽度:32
 寄存器说明: IP配置2寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  corecfg_maxcurrent3p3v : 8;  /* bit[0-7]  : Maximum Current for 3.3V */
        unsigned int  corecfg_maxcurrent3p0v : 8;  /* bit[8-15] : Maximum Current for 3.0V */
        unsigned int  corecfg_maxcurrent1p8v : 8;  /* bit[16-23]: Maximum Current for 1.8V */
        unsigned int  reserved               : 8;  /* bit[24-31]: reserved. */
    } reg;
} SOC_EMMC_ARASAN_CORE_CFG2_UNION;
#endif
#define SOC_EMMC_ARASAN_CORE_CFG2_corecfg_maxcurrent3p3v_START  (0)
#define SOC_EMMC_ARASAN_CORE_CFG2_corecfg_maxcurrent3p3v_END    (7)
#define SOC_EMMC_ARASAN_CORE_CFG2_corecfg_maxcurrent3p0v_START  (8)
#define SOC_EMMC_ARASAN_CORE_CFG2_corecfg_maxcurrent3p0v_END    (15)
#define SOC_EMMC_ARASAN_CORE_CFG2_corecfg_maxcurrent1p8v_START  (16)
#define SOC_EMMC_ARASAN_CORE_CFG2_corecfg_maxcurrent1p8v_END    (23)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_DEBUG_REG0_UNION
 结构说明  : DEBUG_REG0 寄存器结构定义。地址偏移量:0x420，初值:0x00000000，宽度:32
 寄存器说明: DEBUG0寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cmd_cmdfsm_state            : 4;  /* bit[0-3]  : cmdfsm_state[3:0] - Command State Machine
                                                                       4'h0：CMDFSM_IDLE;
                                                                       4'h1：CMDFSM_WAITCLK;
                                                                       4'h2：CMDFSM_SENDSEQ;
                                                                       4'h3：CMDFSM_SENDCRC;
                                                                       4'h4：CMDFSM_SENDEND;
                                                                       4'h5：CMDFSM_WTFERESP;
                                                                       4'h6：CMDFSM_BUSYWAIT;
                                                                       4'h7：CMDFSM_CMDBOOT;
                                                                       4'h8：CMDFSM_. */
        unsigned int  cmd_cmdfsm_cmdout           : 1;  /* bit[4]    : CMD Output */
        unsigned int  cmd_cmdfsm_cmdena           : 1;  /* bit[5]    : CMD Output Enable */
        unsigned int  cmd_cmdfsm_cmdcomplete      : 1;  /* bit[6]    : Command complete bit. */
        unsigned int  cmd_cmdfsm_cmdissued        : 1;  /* bit[7]    : CMD Issued Signal. */
        unsigned int  cmd_cmdfsm_autocmd12        : 1;  /* bit[8]    : Auto CMD12 Indication. */
        unsigned int  cmd_cmdfsm_autocmd23        : 1;  /* bit[9]    : It is set when AutoCMD 23 Qualified with CMD_Data Present */
        unsigned int  cmd_regset_cmdexecute_sdclk : 1;  /* bit[10]   : Double Synchronization of sdhcregset_cmdexecute Signal. */
        unsigned int  cmd_regset_bootena_sdclk    : 1;  /* bit[11]   : Double Synchronization of sdhcregset_bootena Signal. */
        unsigned int  cmd_cmdfsm_cmdrespstatus    : 4;  /* bit[12-15]: Command Response Status. */
        unsigned int  dma_piosdma_state           : 3;  /* bit[16-18]: PIO/SDMA State Machine.
                                                                       3'h0：PIOSDMA_IDLE;
                                                                       3'h1：PIOSDMA_CMDRESP;
                                                                       3'h2：PIOSDMA_DATXFER0;
                                                                       3'h3：PIOSDMA_DATXFER1;
                                                                       3'h4：PIOSDMA_BLOCKGAP;
                                                                       3'h5：PIOSDMA_SDMAINTR;
                                                                       3'h6：PIOSDMA_COMPLETE;
                                                                       3'h7：PIOSDMA_NEXTBOOT; */
        unsigned int  dma_adma2_state             : 4;  /* bit[19-22]: ADMA2 State Machine.
                                                                       4'h0：ADMA2_IDLE;
                                                                       4'h1：ADMA2_CMDRESP;
                                                                       4'h2：ADMA2_DESCRD0;
                                                                       4'h3：ADMA2_DESCRD1;
                                                                       4'h4：ADMA2_DATXFER0;
                                                                       4'h5：ADMA2_DATXFER1;
                                                                       4'h6：ADMA2_BLOCKGAP;
                                                                       4'h7：ADMA2_COMPLETE;
                                                                       4'h8：ADMA2_NEXTBOOT. */
        unsigned int  dma_hosttrans_state         : 2;  /* bit[23-24]: Host Transfer State Machine.
                                                                       0: HOSTTRANS_IDL;
                                                                       1: HOSTTRANS_PRE;
                                                                       0: HOSTTRANS_REQ;
                                                                       1: HOSTTRANS_EOF. */
        unsigned int  dma_hostrddat_state         : 1;  /* bit[25]   : The ReadData State machine receives the Data from Host Interface.
                                                                       0: HOSTRDDAT_IDL;
                                                                       1: HOSTRDDAT_FRM. */
        unsigned int  dma_hostwrdat_state         : 1;  /* bit[26]   : The WriteData State machine Transfers the Data to Host Interface.
                                                                       0: HOSTWRDAT_IDL/HOSTWRDAT_END
                                                                       1: HOSTWRDAT_FRM */
        unsigned int  dma_hostintf_stopatblkgap   : 1;  /* bit[27]   : For write transfer,It is set from the PIO/SDMA and ADMA2 State Machines.
                                                                       For read transfer,RegSet is used to generate Stop at BlkGap */
        unsigned int  dma_hostintf_enddataxfer    : 1;  /* bit[28]   : It is set when the end Data Transfer Complete Indications from the PIO/SDMA and ADMA2 State Machines. */
        unsigned int  dma_hostintf_rdxferactive   : 1;  /* bit[29]   : This is set from the time the Command Last Bit is issued or Block Gap Continue to the time the last block of data is sent to Host. */
        unsigned int  dma_hostintf_abortcmdmode   : 1;  /* bit[30]   : When the Abort command is issued, the flag is set. */
        unsigned int  dma_hostintf_blocknextcmd   : 1;  /* bit[31]   : CommandComplete indication from SDHC_CMDCTRL is set, the next Command Indication should be blocked. */
    } reg;
} SOC_EMMC_ARASAN_DEBUG_REG0_UNION;
#endif
#define SOC_EMMC_ARASAN_DEBUG_REG0_cmd_cmdfsm_state_START             (0)
#define SOC_EMMC_ARASAN_DEBUG_REG0_cmd_cmdfsm_state_END               (3)
#define SOC_EMMC_ARASAN_DEBUG_REG0_cmd_cmdfsm_cmdout_START            (4)
#define SOC_EMMC_ARASAN_DEBUG_REG0_cmd_cmdfsm_cmdout_END              (4)
#define SOC_EMMC_ARASAN_DEBUG_REG0_cmd_cmdfsm_cmdena_START            (5)
#define SOC_EMMC_ARASAN_DEBUG_REG0_cmd_cmdfsm_cmdena_END              (5)
#define SOC_EMMC_ARASAN_DEBUG_REG0_cmd_cmdfsm_cmdcomplete_START       (6)
#define SOC_EMMC_ARASAN_DEBUG_REG0_cmd_cmdfsm_cmdcomplete_END         (6)
#define SOC_EMMC_ARASAN_DEBUG_REG0_cmd_cmdfsm_cmdissued_START         (7)
#define SOC_EMMC_ARASAN_DEBUG_REG0_cmd_cmdfsm_cmdissued_END           (7)
#define SOC_EMMC_ARASAN_DEBUG_REG0_cmd_cmdfsm_autocmd12_START         (8)
#define SOC_EMMC_ARASAN_DEBUG_REG0_cmd_cmdfsm_autocmd12_END           (8)
#define SOC_EMMC_ARASAN_DEBUG_REG0_cmd_cmdfsm_autocmd23_START         (9)
#define SOC_EMMC_ARASAN_DEBUG_REG0_cmd_cmdfsm_autocmd23_END           (9)
#define SOC_EMMC_ARASAN_DEBUG_REG0_cmd_regset_cmdexecute_sdclk_START  (10)
#define SOC_EMMC_ARASAN_DEBUG_REG0_cmd_regset_cmdexecute_sdclk_END    (10)
#define SOC_EMMC_ARASAN_DEBUG_REG0_cmd_regset_bootena_sdclk_START     (11)
#define SOC_EMMC_ARASAN_DEBUG_REG0_cmd_regset_bootena_sdclk_END       (11)
#define SOC_EMMC_ARASAN_DEBUG_REG0_cmd_cmdfsm_cmdrespstatus_START     (12)
#define SOC_EMMC_ARASAN_DEBUG_REG0_cmd_cmdfsm_cmdrespstatus_END       (15)
#define SOC_EMMC_ARASAN_DEBUG_REG0_dma_piosdma_state_START            (16)
#define SOC_EMMC_ARASAN_DEBUG_REG0_dma_piosdma_state_END              (18)
#define SOC_EMMC_ARASAN_DEBUG_REG0_dma_adma2_state_START              (19)
#define SOC_EMMC_ARASAN_DEBUG_REG0_dma_adma2_state_END                (22)
#define SOC_EMMC_ARASAN_DEBUG_REG0_dma_hosttrans_state_START          (23)
#define SOC_EMMC_ARASAN_DEBUG_REG0_dma_hosttrans_state_END            (24)
#define SOC_EMMC_ARASAN_DEBUG_REG0_dma_hostrddat_state_START          (25)
#define SOC_EMMC_ARASAN_DEBUG_REG0_dma_hostrddat_state_END            (25)
#define SOC_EMMC_ARASAN_DEBUG_REG0_dma_hostwrdat_state_START          (26)
#define SOC_EMMC_ARASAN_DEBUG_REG0_dma_hostwrdat_state_END            (26)
#define SOC_EMMC_ARASAN_DEBUG_REG0_dma_hostintf_stopatblkgap_START    (27)
#define SOC_EMMC_ARASAN_DEBUG_REG0_dma_hostintf_stopatblkgap_END      (27)
#define SOC_EMMC_ARASAN_DEBUG_REG0_dma_hostintf_enddataxfer_START     (28)
#define SOC_EMMC_ARASAN_DEBUG_REG0_dma_hostintf_enddataxfer_END       (28)
#define SOC_EMMC_ARASAN_DEBUG_REG0_dma_hostintf_rdxferactive_START    (29)
#define SOC_EMMC_ARASAN_DEBUG_REG0_dma_hostintf_rdxferactive_END      (29)
#define SOC_EMMC_ARASAN_DEBUG_REG0_dma_hostintf_abortcmdmode_START    (30)
#define SOC_EMMC_ARASAN_DEBUG_REG0_dma_hostintf_abortcmdmode_END      (30)
#define SOC_EMMC_ARASAN_DEBUG_REG0_dma_hostintf_blocknextcmd_START    (31)
#define SOC_EMMC_ARASAN_DEBUG_REG0_dma_hostintf_blocknextcmd_END      (31)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_DEBUG_REG1_UNION
 结构说明  : DEBUG_REG1 寄存器结构定义。地址偏移量:0x424，初值:0x00000000，宽度:32
 寄存器说明: DEBUG1寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rxctrl_rcvdata        : 1;  /* bit[0]    : Receive Data Indication. */
        unsigned int  rxctrl_stopsdcardclk1 : 1;  /* bit[1]    : Stop SD Clock Indication (Normal Operation, Buffer Full). */
        unsigned int  rxctrl_stopsdcardclk2 : 1;  /* bit[2]    : Stop SD Clock Indication (Stop at Block Gap). */
        unsigned int  rxctrl_stopafterblk   : 1;  /* bit[3]    : Stop Receiving After this Block (Stop at Blk Gap). */
        unsigned int  rxctrl_rcvstsvld      : 1;  /* bit[4]    : Receive Status Valid. */
        unsigned int  rxctrl_rcvstatus      : 3;  /* bit[5-7]  : Receive Status {EndBit Err, CRC Err, TimeoutErr}. */
        unsigned int  reserved              : 8;  /* bit[8-15] : reserved. */
        unsigned int  txdfsm_state          : 4;  /* bit[16-19]: Transmit Data State Machine.
                                                                 4'h0:IDLE;
                                                                 4'h1:BLKWAIT;
                                                                 4'h2:BLKSTART;
                                                                 4'h3:SENDBLK;
                                                                 4'h4:SENDCRC; 
                                                                 4'h5:SENDEND;
                                                                 4'h6:WAITCRC;
                                                                 4'h7:WAITBSY;
                                                                 4'h8:STOPBLKGAP;
                                                                 4'h9:CRCERROR. */
        unsigned int  txdfsm_datalineactive : 1;  /* bit[20]   : Data Line Active Indicaiton */
        unsigned int  txdfsm_wrxferactive   : 1;  /* bit[21]   : Wr Transfer Active Indication. */
        unsigned int  txdfsm_sddataena      : 1;  /* bit[22]   : SD Data Enable. */
        unsigned int  txdfsm_readbuffer     : 1;  /* bit[23]   : Read Buffer. */
        unsigned int  txdfsm_readeob        : 1;  /* bit[24]   : Read EOB. */
        unsigned int  txdfsm_rcvcrcsts      : 1;  /* bit[25]   : Receive CRC Status Indication to RXCRC State Machine. */
        unsigned int  txdfsm_xmitstsvld     : 1;  /* bit[26]   : Transmit Status Valid Indication. */
        unsigned int  txdfsm_xmitstatus     : 3;  /* bit[27-29]: Transmit Status {ENDBIT Err, CRC Error, Timeout Error} */
        unsigned int  txdfsm_stopsdcardclk  : 1;  /* bit[30]   : Stop SDCard Clock */
        unsigned int  txdfsm_enatimeoutchk  : 1;  /* bit[31]   : Enable Data Timeout Check. */
    } reg;
} SOC_EMMC_ARASAN_DEBUG_REG1_UNION;
#endif
#define SOC_EMMC_ARASAN_DEBUG_REG1_rxctrl_rcvdata_START         (0)
#define SOC_EMMC_ARASAN_DEBUG_REG1_rxctrl_rcvdata_END           (0)
#define SOC_EMMC_ARASAN_DEBUG_REG1_rxctrl_stopsdcardclk1_START  (1)
#define SOC_EMMC_ARASAN_DEBUG_REG1_rxctrl_stopsdcardclk1_END    (1)
#define SOC_EMMC_ARASAN_DEBUG_REG1_rxctrl_stopsdcardclk2_START  (2)
#define SOC_EMMC_ARASAN_DEBUG_REG1_rxctrl_stopsdcardclk2_END    (2)
#define SOC_EMMC_ARASAN_DEBUG_REG1_rxctrl_stopafterblk_START    (3)
#define SOC_EMMC_ARASAN_DEBUG_REG1_rxctrl_stopafterblk_END      (3)
#define SOC_EMMC_ARASAN_DEBUG_REG1_rxctrl_rcvstsvld_START       (4)
#define SOC_EMMC_ARASAN_DEBUG_REG1_rxctrl_rcvstsvld_END         (4)
#define SOC_EMMC_ARASAN_DEBUG_REG1_rxctrl_rcvstatus_START       (5)
#define SOC_EMMC_ARASAN_DEBUG_REG1_rxctrl_rcvstatus_END         (7)
#define SOC_EMMC_ARASAN_DEBUG_REG1_txdfsm_state_START           (16)
#define SOC_EMMC_ARASAN_DEBUG_REG1_txdfsm_state_END             (19)
#define SOC_EMMC_ARASAN_DEBUG_REG1_txdfsm_datalineactive_START  (20)
#define SOC_EMMC_ARASAN_DEBUG_REG1_txdfsm_datalineactive_END    (20)
#define SOC_EMMC_ARASAN_DEBUG_REG1_txdfsm_wrxferactive_START    (21)
#define SOC_EMMC_ARASAN_DEBUG_REG1_txdfsm_wrxferactive_END      (21)
#define SOC_EMMC_ARASAN_DEBUG_REG1_txdfsm_sddataena_START       (22)
#define SOC_EMMC_ARASAN_DEBUG_REG1_txdfsm_sddataena_END         (22)
#define SOC_EMMC_ARASAN_DEBUG_REG1_txdfsm_readbuffer_START      (23)
#define SOC_EMMC_ARASAN_DEBUG_REG1_txdfsm_readbuffer_END        (23)
#define SOC_EMMC_ARASAN_DEBUG_REG1_txdfsm_readeob_START         (24)
#define SOC_EMMC_ARASAN_DEBUG_REG1_txdfsm_readeob_END           (24)
#define SOC_EMMC_ARASAN_DEBUG_REG1_txdfsm_rcvcrcsts_START       (25)
#define SOC_EMMC_ARASAN_DEBUG_REG1_txdfsm_rcvcrcsts_END         (25)
#define SOC_EMMC_ARASAN_DEBUG_REG1_txdfsm_xmitstsvld_START      (26)
#define SOC_EMMC_ARASAN_DEBUG_REG1_txdfsm_xmitstsvld_END        (26)
#define SOC_EMMC_ARASAN_DEBUG_REG1_txdfsm_xmitstatus_START      (27)
#define SOC_EMMC_ARASAN_DEBUG_REG1_txdfsm_xmitstatus_END        (29)
#define SOC_EMMC_ARASAN_DEBUG_REG1_txdfsm_stopsdcardclk_START   (30)
#define SOC_EMMC_ARASAN_DEBUG_REG1_txdfsm_stopsdcardclk_END     (30)
#define SOC_EMMC_ARASAN_DEBUG_REG1_txdfsm_enatimeoutchk_START   (31)
#define SOC_EMMC_ARASAN_DEBUG_REG1_txdfsm_enatimeoutchk_END     (31)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_DEBUG_REG2_UNION
 结构说明  : DEBUG_REG2 寄存器结构定义。地址偏移量:0x428，初值:0x00000000，宽度:32
 寄存器说明: DEBUG2寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tuningfsm_state       : 3;  /* bit[0-2]  : The Tuning FSM waits for Execute_Tuning Request from Software and starts the Tuning Procedure.
                                                                 3'h0: IDLE;
                                                                 3'h1: WTFORCMD;
                                                                 3'h2: WTFORDAT;
                                                                 3'h3: WTFORCRC;
                                                                 3'h4: NEXTITER;
                                                                 3'h5: SELCLOCK0;
                                                                 3'h6: SELCLOCK1; */
        unsigned int  tuningfsm_count       : 6;  /* bit[3-8]  : Tuning Count. */
        unsigned int  tuningfsm_numseqmatch : 6;  /* bit[9-14] : Number of Sequential Matches. */
        unsigned int  tuningfsm_done        : 1;  /* bit[15]   : Tuning Done Indication. */
        unsigned int  rxdfsm_state          : 3;  /* bit[16-18]: Receive Data State Machine:
                                                                 3'h0: RCVSTATE;
                                                                 3'h1: RCVDATA;
                                                                 3'h2: RCVEND;
                                                                 3'h3: STOPBLKGAP;
                                                                 3'h4: RDWAIT;
                                                                 3'h5: RCVBOOTACK;
                                                                 3'h6: RCVSPISTATE; */
        unsigned int  rxdfsm_wtforblk       : 1;  /* bit[19]   : Wait for Block Indication. */
        unsigned int  rxdfsm_datawrite      : 1;  /* bit[20]   : Data Byte/Word Write. */
        unsigned int  rxdfsm_dataeob        : 1;  /* bit[21]   : Data Byte/Word is End Of Block Indication. */
        unsigned int  rxdfsm_okstopclk      : 1;  /* bit[22]   : OK to Stop the Clock (End of Block Flow Control) */
        unsigned int  rxdfsm_reachingeob    : 1;  /* bit[23]   : Reaching End of Block Indication */
        unsigned int  sdhc_rxddebugbus1     : 8;  /* bit[24-31]: reserved. */
    } reg;
} SOC_EMMC_ARASAN_DEBUG_REG2_UNION;
#endif
#define SOC_EMMC_ARASAN_DEBUG_REG2_tuningfsm_state_START        (0)
#define SOC_EMMC_ARASAN_DEBUG_REG2_tuningfsm_state_END          (2)
#define SOC_EMMC_ARASAN_DEBUG_REG2_tuningfsm_count_START        (3)
#define SOC_EMMC_ARASAN_DEBUG_REG2_tuningfsm_count_END          (8)
#define SOC_EMMC_ARASAN_DEBUG_REG2_tuningfsm_numseqmatch_START  (9)
#define SOC_EMMC_ARASAN_DEBUG_REG2_tuningfsm_numseqmatch_END    (14)
#define SOC_EMMC_ARASAN_DEBUG_REG2_tuningfsm_done_START         (15)
#define SOC_EMMC_ARASAN_DEBUG_REG2_tuningfsm_done_END           (15)
#define SOC_EMMC_ARASAN_DEBUG_REG2_rxdfsm_state_START           (16)
#define SOC_EMMC_ARASAN_DEBUG_REG2_rxdfsm_state_END             (18)
#define SOC_EMMC_ARASAN_DEBUG_REG2_rxdfsm_wtforblk_START        (19)
#define SOC_EMMC_ARASAN_DEBUG_REG2_rxdfsm_wtforblk_END          (19)
#define SOC_EMMC_ARASAN_DEBUG_REG2_rxdfsm_datawrite_START       (20)
#define SOC_EMMC_ARASAN_DEBUG_REG2_rxdfsm_datawrite_END         (20)
#define SOC_EMMC_ARASAN_DEBUG_REG2_rxdfsm_dataeob_START         (21)
#define SOC_EMMC_ARASAN_DEBUG_REG2_rxdfsm_dataeob_END           (21)
#define SOC_EMMC_ARASAN_DEBUG_REG2_rxdfsm_okstopclk_START       (22)
#define SOC_EMMC_ARASAN_DEBUG_REG2_rxdfsm_okstopclk_END         (22)
#define SOC_EMMC_ARASAN_DEBUG_REG2_rxdfsm_reachingeob_START     (23)
#define SOC_EMMC_ARASAN_DEBUG_REG2_rxdfsm_reachingeob_END       (23)
#define SOC_EMMC_ARASAN_DEBUG_REG2_sdhc_rxddebugbus1_START      (24)
#define SOC_EMMC_ARASAN_DEBUG_REG2_sdhc_rxddebugbus1_END        (31)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_DEBUG_REG3_UNION
 结构说明  : DEBUG_REG3 寄存器结构定义。地址偏移量:0x42C，初值:0x00000200，宽度:32
 寄存器说明: DEBUG3寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sdhc_ledcontrol     : 1;  /* bit[0]    : LED ON: To Caution the user not to remove the card 
                                                               while the SD card is being accessed. */
        unsigned int  sdhc_sdbuspower     : 1;  /* bit[1]    : Control SD Card Power Supply. */
        unsigned int  sdhc_sdbusvoltage   : 3;  /* bit[2-4]  : SD Bus voltage select. */
        unsigned int  sdhc_driverstrength : 3;  /* bit[5-7]  : Driver Strength Select */
        unsigned int  sdhc_1p8vsigenable  : 1;  /* bit[8]    : 1.8V Signaling Enable */
        unsigned int  sdhc_emmchwrst_n    : 1;  /* bit[9]    : Device reset status. */
        unsigned int  sdhc_cmddir         : 1;  /* bit[10]   : To indicate the command Direction
                                                               0 - Write (Host to Card)
                                                               1 - Read (Card to Host) */
        unsigned int  reserved            : 21; /* bit[11-31]: reserved. */
    } reg;
} SOC_EMMC_ARASAN_DEBUG_REG3_UNION;
#endif
#define SOC_EMMC_ARASAN_DEBUG_REG3_sdhc_ledcontrol_START      (0)
#define SOC_EMMC_ARASAN_DEBUG_REG3_sdhc_ledcontrol_END        (0)
#define SOC_EMMC_ARASAN_DEBUG_REG3_sdhc_sdbuspower_START      (1)
#define SOC_EMMC_ARASAN_DEBUG_REG3_sdhc_sdbuspower_END        (1)
#define SOC_EMMC_ARASAN_DEBUG_REG3_sdhc_sdbusvoltage_START    (2)
#define SOC_EMMC_ARASAN_DEBUG_REG3_sdhc_sdbusvoltage_END      (4)
#define SOC_EMMC_ARASAN_DEBUG_REG3_sdhc_driverstrength_START  (5)
#define SOC_EMMC_ARASAN_DEBUG_REG3_sdhc_driverstrength_END    (7)
#define SOC_EMMC_ARASAN_DEBUG_REG3_sdhc_1p8vsigenable_START   (8)
#define SOC_EMMC_ARASAN_DEBUG_REG3_sdhc_1p8vsigenable_END     (8)
#define SOC_EMMC_ARASAN_DEBUG_REG3_sdhc_emmchwrst_n_START     (9)
#define SOC_EMMC_ARASAN_DEBUG_REG3_sdhc_emmchwrst_n_END       (9)
#define SOC_EMMC_ARASAN_DEBUG_REG3_sdhc_cmddir_START          (10)
#define SOC_EMMC_ARASAN_DEBUG_REG3_sdhc_cmddir_END            (10)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_PHYCTRL1_UNION
 结构说明  : PHYCTRL1 寄存器结构定义。地址偏移量:0x430，初值:0x00000000，宽度:32
 寄存器说明: PHY控制寄存器1寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  phyctrl_oden_cmd    : 1;  /* bit[0]    : Open Drain Enable on CMD line. Power on Default 1b’0  */
        unsigned int  phyctrl_oden_strb   : 1;  /* bit[1]    : Open Drain Enable on STRB line. Power on Default 1b’0  */
        unsigned int  phyctrl_retenb      : 1;  /* bit[2]    : Useless here. IO retention function is contrlled by sys_ctrl. */
        unsigned int  phyctrl_reten       : 1;  /* bit[3]    : Useless here. IO retention function is contrlled by sys_ctrl. */
        unsigned int  phyctrl_dlliff      : 3;  /* bit[4-6]  : useless. */
        unsigned int  phyctrl_endll       : 1;  /* bit[7]    : Enable DLL. Enables the analog DLL circuits. 
                                                               Power on Default 1b’0  */
        unsigned int  phyctrl_dll_trm_icp : 8;  /* bit[8-15] : 仅低4bit有效,上电初始化应配置为4‘b1000。
                                                               Analog DLL’s Charge Pump Current Trim. Programs the analog DLL loop gain. Power on Default 4b’0000. */
        unsigned int  phyctrl_en_rtrim    : 1;  /* bit[16]   : CALIO enable. Enables CALIO, If enabled CALIO will start calibration cycle at phyctrl_pdb positive edge. 
                                                               Power on Default 1b’1  */
        unsigned int  reserved_0          : 4;  /* bit[17-20]: reserved */
        unsigned int  phyctrl_retrim      : 1;  /* bit[21]   : Start CALIO calibration cycle. At positive edge initiates CALIO calibration cycle. Power on Default 1b’0 */
        unsigned int  phyctrl_dr_ty       : 3;  /* bit[22-24]: Drive Source/Sink impedance programming 
                                                               3b000: 50 ohms 
                                                               3b001: 33 Ohms 
                                                               3b010: 66 Ohms 
                                                               3b011: 100 Ohms 
                                                               3b100: 40 Ohms 
                                                               Power on Default 3b’000  */
        unsigned int  phyctrl_pdb         : 1;  /* bit[25]   : CALIO S/M power down bar. SOC asserts after power up sequence 
                                                               is completed. Power on Default 1b’0.  */
        unsigned int  reserved_1          : 6;  /* bit[26-31]: reserved. */
    } reg;
} SOC_EMMC_ARASAN_PHYCTRL1_UNION;
#endif
#define SOC_EMMC_ARASAN_PHYCTRL1_phyctrl_oden_cmd_START     (0)
#define SOC_EMMC_ARASAN_PHYCTRL1_phyctrl_oden_cmd_END       (0)
#define SOC_EMMC_ARASAN_PHYCTRL1_phyctrl_oden_strb_START    (1)
#define SOC_EMMC_ARASAN_PHYCTRL1_phyctrl_oden_strb_END      (1)
#define SOC_EMMC_ARASAN_PHYCTRL1_phyctrl_retenb_START       (2)
#define SOC_EMMC_ARASAN_PHYCTRL1_phyctrl_retenb_END         (2)
#define SOC_EMMC_ARASAN_PHYCTRL1_phyctrl_reten_START        (3)
#define SOC_EMMC_ARASAN_PHYCTRL1_phyctrl_reten_END          (3)
#define SOC_EMMC_ARASAN_PHYCTRL1_phyctrl_dlliff_START       (4)
#define SOC_EMMC_ARASAN_PHYCTRL1_phyctrl_dlliff_END         (6)
#define SOC_EMMC_ARASAN_PHYCTRL1_phyctrl_endll_START        (7)
#define SOC_EMMC_ARASAN_PHYCTRL1_phyctrl_endll_END          (7)
#define SOC_EMMC_ARASAN_PHYCTRL1_phyctrl_dll_trm_icp_START  (8)
#define SOC_EMMC_ARASAN_PHYCTRL1_phyctrl_dll_trm_icp_END    (15)
#define SOC_EMMC_ARASAN_PHYCTRL1_phyctrl_en_rtrim_START     (16)
#define SOC_EMMC_ARASAN_PHYCTRL1_phyctrl_en_rtrim_END       (16)
#define SOC_EMMC_ARASAN_PHYCTRL1_phyctrl_retrim_START       (21)
#define SOC_EMMC_ARASAN_PHYCTRL1_phyctrl_retrim_END         (21)
#define SOC_EMMC_ARASAN_PHYCTRL1_phyctrl_dr_ty_START        (22)
#define SOC_EMMC_ARASAN_PHYCTRL1_phyctrl_dr_ty_END          (24)
#define SOC_EMMC_ARASAN_PHYCTRL1_phyctrl_pdb_START          (25)
#define SOC_EMMC_ARASAN_PHYCTRL1_phyctrl_pdb_END            (25)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_PHYCTRL2_UNION
 结构说明  : PHYCTRL2 寄存器结构定义。地址偏移量:0x434，初值:0x003FF7FC，宽度:32
 寄存器说明: PHY控制寄存器2寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  phyctrl_od_release_cmd  : 1;  /* bit[0]    : Disable an internal 4.7K pull up resistor on CMD line in open drain mode. */
        unsigned int  phyctrl_od_release_strb : 1;  /* bit[1]    : Disable an internal 4.7K pull up resistor on STRB line in open drain mode.  */
        unsigned int  phyctrl_pu_dat          : 8;  /* bit[2-9]  : Enable pull up on DAT lines. If phyctrl_ren_dat[7:0] is high week pull up is enabled on DATA lines. 
                                                                   Power on Default 8b’11111111  */
        unsigned int  phyctrl_pu_cmd          : 1;  /* bit[10]   : Enable pull up on CMD line. If phyctrl_ren_cmd is high week pull up is enabled on CMD line. 
                                                                   Power on Default 1b’01. */
        unsigned int  phyctrl_pu_strb         : 1;  /* bit[11]   : Enable pull up on STRB line. If phyctrl_ren_strb is high week pull up is enabled on STRB line. 
                                                                   Power on Default 1b’0  */
        unsigned int  phyctrl_ren_dat         : 8;  /* bit[12-19]: Enable pull up/down on DAT Lines. If phyctrl_pup_dat[7:0] is high week pull up is enabled on DATA lines, if low week pull down is enabled on DATA lines. 
                                                                   Power on Default 8b’11111111  */
        unsigned int  phyctrl_ren_cmd         : 1;  /* bit[20]   : Enable pull up/down on CMD line. If phyctrl_pup_cmd is high week pull up is enabled on CMD line, if low week pull down is enabled on CMD line. 
                                                                   Power on Default 1b’1 */
        unsigned int  phyctrl_ren_strb        : 1;  /* bit[21]   : Enable pull up/down on the STRB line. If phyctrl_pup_strb is high a week pull up is enabled on STRB line, if low week pull down is enabled on STRB line. 
                                                                   Power on Default 1b’1 */
        unsigned int  phyctrl_oden_dat        : 8;  /* bit[22-29]: Open Drain Enable on DAT lines. Power on Default 8b’00000000  */
        unsigned int  reserved                : 2;  /* bit[30-31]: reserved. */
    } reg;
} SOC_EMMC_ARASAN_PHYCTRL2_UNION;
#endif
#define SOC_EMMC_ARASAN_PHYCTRL2_phyctrl_od_release_cmd_START   (0)
#define SOC_EMMC_ARASAN_PHYCTRL2_phyctrl_od_release_cmd_END     (0)
#define SOC_EMMC_ARASAN_PHYCTRL2_phyctrl_od_release_strb_START  (1)
#define SOC_EMMC_ARASAN_PHYCTRL2_phyctrl_od_release_strb_END    (1)
#define SOC_EMMC_ARASAN_PHYCTRL2_phyctrl_pu_dat_START           (2)
#define SOC_EMMC_ARASAN_PHYCTRL2_phyctrl_pu_dat_END             (9)
#define SOC_EMMC_ARASAN_PHYCTRL2_phyctrl_pu_cmd_START           (10)
#define SOC_EMMC_ARASAN_PHYCTRL2_phyctrl_pu_cmd_END             (10)
#define SOC_EMMC_ARASAN_PHYCTRL2_phyctrl_pu_strb_START          (11)
#define SOC_EMMC_ARASAN_PHYCTRL2_phyctrl_pu_strb_END            (11)
#define SOC_EMMC_ARASAN_PHYCTRL2_phyctrl_ren_dat_START          (12)
#define SOC_EMMC_ARASAN_PHYCTRL2_phyctrl_ren_dat_END            (19)
#define SOC_EMMC_ARASAN_PHYCTRL2_phyctrl_ren_cmd_START          (20)
#define SOC_EMMC_ARASAN_PHYCTRL2_phyctrl_ren_cmd_END            (20)
#define SOC_EMMC_ARASAN_PHYCTRL2_phyctrl_ren_strb_START         (21)
#define SOC_EMMC_ARASAN_PHYCTRL2_phyctrl_ren_strb_END           (21)
#define SOC_EMMC_ARASAN_PHYCTRL2_phyctrl_oden_dat_START         (22)
#define SOC_EMMC_ARASAN_PHYCTRL2_phyctrl_oden_dat_END           (29)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_PHYCTRL3_UNION
 结构说明  : PHYCTRL3 寄存器结构定义。地址偏移量:0x438，初值:0x00000000，宽度:32
 寄存器说明: PHY控制寄存器3寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  phyctrl_seldlytxclk    : 1;  /* bit[0]    : Select the Delay chain based txclk. Enables the TX clock based delay chain rather than analog DLL based delay chain. 
                                                                  Power on Default 1b’0.  */
        unsigned int  phyctrl_seldlyrxclk    : 1;  /* bit[1]    : Select the Delay chain based rxclk. Enables the RX clock based delay chain rather than analog DLL based delay chain. 
                                                                  Power on Default 1b’0.  */
        unsigned int  phyctrl_strbsel        : 4;  /* bit[2-5]  : Select the Four Taps for each of STRB_90 and STRB_180 Outputs. phyctrl_strbsel[3:2] selects one of the four for STRB_180 and phyctrl_strbsel[1:0] selects the four taps for STRB_90. 
                                                                  Power on default 4b’0000 . */
        unsigned int  reserved_0             : 2;  /* bit[6-7]  : reserved. */
        unsigned int  phyctrl_otapdlyena     : 1;  /* bit[8]    : Output Tap Delay Enable. Enables manual control of the TX clock tap delay, for clocking the final stage flops for maintaining Hold requirements on EMMC Interface. 
                                                                  Power on Default 1b’0.  */
        unsigned int  phyctrl_otapdlysel     : 4;  /* bit[9-12] : Output Tap Delay Select. Manual control of the TX clock tap delay for clocking the final stage flops for maintaining Hold requirements on EMMC Interface. 
                                                                  Power on Default 4’0000  */
        unsigned int  phyctrl_itapchgwin     : 1;  /* bit[13]   : Input Tap Change Window. It gets asserted by the controller while changing the phyctrl_itapdlysel. Used to gate of the RX clock during switching the clock source while tap is changing to avoid clock glitches. 
                                                                  Power on Default 1b’0  */
        unsigned int  phyctrl_itapdlyena     : 1;  /* bit[14]   : Input Tap Delay Enable. This is used for the manual control of the RX clock Tap Delay in non HS200/HS400 modes. 
                                                                  Power on default 1b’0  */
        unsigned int  phyctrl_itapdlysel     : 5;  /* bit[15-19]: Input Tap Delay Select. Manual control of the RX clock Tap Delay in the non HS200/HS400 modes. Power on Default 5b’00000  */
        unsigned int  phyctrl_od_release_dat : 8;  /* bit[20-27]: Disable an internal 4.7K pull up resistor on data lines in open drain mode. 
                                                                  Power on Default 8b’00000000  */
        unsigned int  phyctrl_freqsel        : 3;  /* bit[28-30]: Select the frequency range of DLL operation: 
                                                                  3b'000: 200MHz to 170 MHz range 
                                                                  3b'001: 140MHz to 170 MHz range 
                                                                  3b'011: 110MHz to 140 MHz 
                                                                  3b'100: 80MHz to 110MHz 
                                                                  3b'101: 50MHz to 80 MHz 
                                                                  3b'110: Reserved 
                                                                  3b'111: Reserved 
                                                                  Power on Default 3b’000.  */
        unsigned int  reserved_1             : 1;  /* bit[31]   : reserved. */
    } reg;
} SOC_EMMC_ARASAN_PHYCTRL3_UNION;
#endif
#define SOC_EMMC_ARASAN_PHYCTRL3_phyctrl_seldlytxclk_START     (0)
#define SOC_EMMC_ARASAN_PHYCTRL3_phyctrl_seldlytxclk_END       (0)
#define SOC_EMMC_ARASAN_PHYCTRL3_phyctrl_seldlyrxclk_START     (1)
#define SOC_EMMC_ARASAN_PHYCTRL3_phyctrl_seldlyrxclk_END       (1)
#define SOC_EMMC_ARASAN_PHYCTRL3_phyctrl_strbsel_START         (2)
#define SOC_EMMC_ARASAN_PHYCTRL3_phyctrl_strbsel_END           (5)
#define SOC_EMMC_ARASAN_PHYCTRL3_phyctrl_otapdlyena_START      (8)
#define SOC_EMMC_ARASAN_PHYCTRL3_phyctrl_otapdlyena_END        (8)
#define SOC_EMMC_ARASAN_PHYCTRL3_phyctrl_otapdlysel_START      (9)
#define SOC_EMMC_ARASAN_PHYCTRL3_phyctrl_otapdlysel_END        (12)
#define SOC_EMMC_ARASAN_PHYCTRL3_phyctrl_itapchgwin_START      (13)
#define SOC_EMMC_ARASAN_PHYCTRL3_phyctrl_itapchgwin_END        (13)
#define SOC_EMMC_ARASAN_PHYCTRL3_phyctrl_itapdlyena_START      (14)
#define SOC_EMMC_ARASAN_PHYCTRL3_phyctrl_itapdlyena_END        (14)
#define SOC_EMMC_ARASAN_PHYCTRL3_phyctrl_itapdlysel_START      (15)
#define SOC_EMMC_ARASAN_PHYCTRL3_phyctrl_itapdlysel_END        (19)
#define SOC_EMMC_ARASAN_PHYCTRL3_phyctrl_od_release_dat_START  (20)
#define SOC_EMMC_ARASAN_PHYCTRL3_phyctrl_od_release_dat_END    (27)
#define SOC_EMMC_ARASAN_PHYCTRL3_phyctrl_freqsel_START         (28)
#define SOC_EMMC_ARASAN_PHYCTRL3_phyctrl_freqsel_END           (30)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_PHYCTRL4_UNION
 结构说明  : PHYCTRL4 寄存器结构定义。地址偏移量:0x43C，初值:0x00000000，宽度:32
 寄存器说明: PHY控制寄存器4寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  phyctrl_testctrl : 8;  /* bit[0-7]  : ACS eMMC50_PHY test control. 
                                                            8’b0001_0000 èTest EMMC IOs sink impedance 
                                                            8’b0001_0001 èTest EMMC IOs source impedance 
                                                            8’b0010_0000 èTest RX clock phases on data lines. 
                                                            ph<0> -> EMMC50_DAT<0>, ph<4> -> EMMC50_DAT<1> 
                                                            ph<8> -> EMMC50_DAT<2>, ph<12> -> EMMC50_DAT<3> 
                                                            ph<16> -> EMMC50_DAT<4>, ph<20> -> EMMC50_DAT<5> 
                                                            ph<24> -> EMMC50_DAT<6>, ph<28> -> EMMC50_DAT<7> 
                                                            8’b0011_0000 èTest TX clock phases on data lines. 
                                                            ph<0> -> EMMC50_DAT<0>, ph<4> -> EMMC50_DAT<1> 
                                                            ph<8> -> EMMC50_DAT<2>, ph<12> -> EMMC50_DAT<3> 
                                                            ph<16> -> EMMC50_DAT<4>, ph<20> -> EMMC50_DAT<5> 
                                                            ph<24> -> EMMC50_DAT<6>, ph<28> -> EMMC50_DAT<7> 
                                                            8’b0100_0000 èTest STRB clock phases on data lines. 
                                                            ph<0> -> EMMC50_DAT<0>, ph<4> -> EMMC50_DAT<1> 
                                                            ph<8> -> EMMC50_DAT<2>, ph<12> -> EMMC50_DAT<3> 
                                                            ph<16> -> EMMC50_DAT<4>, ph<20> -> EMMC50_DAT<5> 
                                                            ph<24> -> EMMC50_DAT<6>, ph<28> -> EMMC50_DAT<7> 
                                                            Power on default 8b’00000000  */
        unsigned int  reserved_0       : 2;  /* bit[8-9]  : reserved. */
        unsigned int  reserved_1       : 22; /* bit[10-31]: reserved. */
    } reg;
} SOC_EMMC_ARASAN_PHYCTRL4_UNION;
#endif
#define SOC_EMMC_ARASAN_PHYCTRL4_phyctrl_testctrl_START  (0)
#define SOC_EMMC_ARASAN_PHYCTRL4_phyctrl_testctrl_END    (7)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_PHY_STATUS_UNION
 结构说明  : PHY_STATUS 寄存器结构定义。地址偏移量:0x440，初值:0x00000038，宽度:32
 寄存器说明: PHY状态寄存器寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  phyctrl_exr_ninst : 1;  /* bit[0]   : External Resistor on CALIO absent. Indicates trim cycle started and external resistor is absent. 
                                                            Power on Default 1b’0.  */
        unsigned int  phyctrl_dllrdy    : 1;  /* bit[1]   : DLL ready. Indicates that DLL loop is locked. 
                                                            Power on Default 1b’0  */
        unsigned int  phyctrl_rtrim     : 4;  /* bit[2-5] : CALIO Calibration Result. Holds the content of CALIO Impedance Calibration Result. Power on default 4b’1110.  */
        unsigned int  phyctrl_caldone   : 1;  /* bit[6]   : CALIO STATUS, 
                                                            indicate that CALIO Calibration is completed successfully. Power on default 1b’0.  */
        unsigned int  reserved          : 25; /* bit[7-31]: reserved. */
    } reg;
} SOC_EMMC_ARASAN_PHY_STATUS_UNION;
#endif
#define SOC_EMMC_ARASAN_PHY_STATUS_phyctrl_exr_ninst_START  (0)
#define SOC_EMMC_ARASAN_PHY_STATUS_phyctrl_exr_ninst_END    (0)
#define SOC_EMMC_ARASAN_PHY_STATUS_phyctrl_dllrdy_START     (1)
#define SOC_EMMC_ARASAN_PHY_STATUS_phyctrl_dllrdy_END       (1)
#define SOC_EMMC_ARASAN_PHY_STATUS_phyctrl_rtrim_START      (2)
#define SOC_EMMC_ARASAN_PHY_STATUS_phyctrl_rtrim_END        (5)
#define SOC_EMMC_ARASAN_PHY_STATUS_phyctrl_caldone_START    (6)
#define SOC_EMMC_ARASAN_PHY_STATUS_phyctrl_caldone_END      (6)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_TEST_CONTROL_UNION
 结构说明  : TEST_CONTROL 寄存器结构定义。地址偏移量:0x444，初值:0x000000E0，宽度:32
 寄存器说明: 测试等控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  test_output_en    : 1;  /* bit[0]    : 测试信号（tp_emmc_xx）输出使能。
                                                             0：输出不使能；
                                                             1：输出使能。 */
        unsigned int  phyctrl_clkbufsel : 3;  /* bit[1-3]  : Clock Delay Buffer Select. 
                                                             Selects one of the eight taps in the CLK Delay Buffer based on PVT variation. 
                                                             Power on default 3b’000. */
        unsigned int  sdcard_buf_bypass : 1;  /* bit[4]    : EMMC_CLK输出时钟路径上的buffer delay的bypass使能信号。
                                                             Clock Buffer是为了平衡数据路径上的延时，减小由于corner变化导致DATA/CMD相对于CLK的建立保持时间的变化。
                                                             0：bypass 不使能；
                                                             1：bypass 使能。 */
        unsigned int  test_ctrl_bak     : 11; /* bit[5-15] : backup. 
                                                             Useless. */
        unsigned int  reserved          : 16; /* bit[16-31]: reserved. */
    } reg;
} SOC_EMMC_ARASAN_TEST_CONTROL_UNION;
#endif
#define SOC_EMMC_ARASAN_TEST_CONTROL_test_output_en_START     (0)
#define SOC_EMMC_ARASAN_TEST_CONTROL_test_output_en_END       (0)
#define SOC_EMMC_ARASAN_TEST_CONTROL_phyctrl_clkbufsel_START  (1)
#define SOC_EMMC_ARASAN_TEST_CONTROL_phyctrl_clkbufsel_END    (3)
#define SOC_EMMC_ARASAN_TEST_CONTROL_sdcard_buf_bypass_START  (4)
#define SOC_EMMC_ARASAN_TEST_CONTROL_sdcard_buf_bypass_END    (4)
#define SOC_EMMC_ARASAN_TEST_CONTROL_test_ctrl_bak_START      (5)
#define SOC_EMMC_ARASAN_TEST_CONTROL_test_ctrl_bak_END        (15)


/*****************************************************************************
 结构名    : SOC_EMMC_ARASAN_CORE_CFG3_UNION
 结构说明  : CORE_CFG3 寄存器结构定义。地址偏移量:0x448，初值:0x00000C01，宽度:32
 寄存器说明: IP配置3寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  corecfg_cqfval : 10; /* bit[0-9]  : Internal Timer Clock Frequency Value (ITCFVAL)
                                                          TCFMUL and ITCFVAL indicate the frequency of the clock used for interrupt coalescing timer and for determining the polling period when using periodic SEND_QUEUE_ STATUS (CMD13) polling.
                                                          The clock frequency is calculated as ITCFVAL* ITCFMUL.
                                                          For example, to encode 19.2 MHz, ITCFVAL shall be C0h (= 192 decimal) and ITCFMUL shall be 2h (192 * 0.1 MHz = 19.2 MHz) */
        unsigned int  corecfg_cqfmul : 4;  /* bit[10-13]: Internal Timer Clock Frequency Multiplier (ITCFMUL)
                                                          ITCFMUL and ITCFVAL indicate the frequency of the clock used for interrupt coalescing timer and for determining the SQS polling period. See ITCFVAL definition for details.
                                                          Field Value Description:
                                                          0h = 0.001 MHz
                                                          1h = 0.01 MHz
                                                          2h = 0.1 MHz
                                                          3h = 1 MHz
                                                          4h = 10 MHz
                                                          Other values are reserved */
        unsigned int  reserved       : 18; /* bit[14-31]: reserved. */
    } reg;
} SOC_EMMC_ARASAN_CORE_CFG3_UNION;
#endif
#define SOC_EMMC_ARASAN_CORE_CFG3_corecfg_cqfval_START  (0)
#define SOC_EMMC_ARASAN_CORE_CFG3_corecfg_cqfval_END    (9)
#define SOC_EMMC_ARASAN_CORE_CFG3_corecfg_cqfmul_START  (10)
#define SOC_EMMC_ARASAN_CORE_CFG3_corecfg_cqfmul_END    (13)






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

#endif /* end of soc_emmc_arasan_interface.h */
