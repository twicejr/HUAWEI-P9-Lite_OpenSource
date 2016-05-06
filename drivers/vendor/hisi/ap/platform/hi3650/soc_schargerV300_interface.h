/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_scharger_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-06-05 14:22:23
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年6月5日
    作    者   : l00279044
    修改内容   : 从《nManager_SCHARGER.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_SCHARGER_INTERFACE_H__
#define __SOC_SCHARGER_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) reg_define
 ****************************************************************************/
/* 寄存器说明：芯片版本寄存器0。
   位域定义UNION结构:  SOC_SCHARGER_CHIP_VERSION_0_UNION */
#define SOC_SCHARGER_CHIP_VERSION_0_ADDR(base)        ((base) + (0x00))

/* 寄存器说明：芯片版本寄存器1。
   位域定义UNION结构:  SOC_SCHARGER_CHIP_VERSION_1_UNION */
#define SOC_SCHARGER_CHIP_VERSION_1_ADDR(base)        ((base) + (0x01))

/* 寄存器说明：芯片版本寄存器2。
   位域定义UNION结构:  SOC_SCHARGER_CHIP_VERSION_2_UNION */
#define SOC_SCHARGER_CHIP_VERSION_2_ADDR(base)        ((base) + (0x02))

/* 寄存器说明：芯片版本寄存器3。
   位域定义UNION结构:  SOC_SCHARGER_CHIP_VERSION_3_UNION */
#define SOC_SCHARGER_CHIP_VERSION_3_ADDR(base)        ((base) + (0x03))

/* 寄存器说明：芯片版本寄存器4。
   位域定义UNION结构:  SOC_SCHARGER_CHIP_VERSION_4_UNION */
#define SOC_SCHARGER_CHIP_VERSION_4_ADDR(base)        ((base) + (0x04))

/* 寄存器说明：芯片版本寄存器5。
   位域定义UNION结构:  SOC_SCHARGER_CHIP_VERSION_5_UNION */
#define SOC_SCHARGER_CHIP_VERSION_5_ADDR(base)        ((base) + (0x05))

/* 寄存器说明：状态标志0寄存器。
   位域定义UNION结构:  SOC_SCHARGER_STATUS0_UNION */
#define SOC_SCHARGER_STATUS0_ADDR(base)               ((base) + (0x06))

/* 寄存器说明：状态标志1寄存器。
   位域定义UNION结构:  SOC_SCHARGER_STATUS1_UNION */
#define SOC_SCHARGER_STATUS1_ADDR(base)               ((base) + (0x07))

/* 寄存器说明：状态标志2寄存器。
   位域定义UNION结构:  SOC_SCHARGER_STATUS2_UNION */
#define SOC_SCHARGER_STATUS2_ADDR(base)               ((base) + (0x08))

/* 寄存器说明：中断状态标志0寄存器。
   位域定义UNION结构:  SOC_SCHARGER_IRQ_STATUS0_UNION */
#define SOC_SCHARGER_IRQ_STATUS0_ADDR(base)           ((base) + (0x09))

/* 寄存器说明：中断状态标志1寄存器。
   位域定义UNION结构:  SOC_SCHARGER_IRQ_STATUS1_UNION */
#define SOC_SCHARGER_IRQ_STATUS1_ADDR(base)           ((base) + (0x0A))

/* 寄存器说明：中断状态标志1寄存器。
   位域定义UNION结构:  SOC_SCHARGER_IRQ_STATUS2_UNION */
#define SOC_SCHARGER_IRQ_STATUS2_ADDR(base)           ((base) + (0x0B))

/* 寄存器说明：中断0寄存器。
   位域定义UNION结构:  SOC_SCHARGER_IRQ0_UNION */
#define SOC_SCHARGER_IRQ0_ADDR(base)                  ((base) + (0x0C))

/* 寄存器说明：中断1寄存器。
   位域定义UNION结构:  SOC_SCHARGER_IRQ1_UNION */
#define SOC_SCHARGER_IRQ1_ADDR(base)                  ((base) + (0x0D))

/* 寄存器说明：中断2寄存器。
   位域定义UNION结构:  SOC_SCHARGER_IRQ2_UNION */
#define SOC_SCHARGER_IRQ2_ADDR(base)                  ((base) + (0x0E))

/* 寄存器说明：看门狗中断寄存器。
   位域定义UNION结构:  SOC_SCHARGER_WATCHDOG_IRQ_UNION */
#define SOC_SCHARGER_WATCHDOG_IRQ_ADDR(base)          ((base) + (0x0F))

/* 寄存器说明：中断屏蔽0寄存器。
   位域定义UNION结构:  SOC_SCHARGER_IRQ0_MASK_UNION */
#define SOC_SCHARGER_IRQ0_MASK_ADDR(base)             ((base) + (0x10))

/* 寄存器说明：中断屏蔽1寄存器。
   位域定义UNION结构:  SOC_SCHARGER_IRQ1_MASK_UNION */
#define SOC_SCHARGER_IRQ1_MASK_ADDR(base)             ((base) + (0x11))

/* 寄存器说明：中断屏蔽2寄存器。
   位域定义UNION结构:  SOC_SCHARGER_IRQ2_MASK_UNION */
#define SOC_SCHARGER_IRQ2_MASK_ADDR(base)             ((base) + (0x12))

/* 寄存器说明：看门狗中断屏蔽寄存器。
   位域定义UNION结构:  SOC_SCHARGER_WATCHDOG_IRQ_MASK_UNION */
#define SOC_SCHARGER_WATCHDOG_IRQ_MASK_ADDR(base)     ((base) + (0x13))

/* 寄存器说明：fcp slave 连接状态寄存器。
   位域定义UNION结构:  SOC_SCHARGER_STATUIS_UNION */
#define SOC_SCHARGER_STATUIS_ADDR(base)               ((base) + (0x20))

/* 寄存器说明：XXXX。
   位域定义UNION结构:  SOC_SCHARGER_CNTL_UNION */
#define SOC_SCHARGER_CNTL_ADDR(base)                  ((base) + (0x21))

/* 寄存器说明：fcp 读写命令配置寄存器。
   位域定义UNION结构:  SOC_SCHARGER_CMD_UNION */
#define SOC_SCHARGER_CMD_ADDR(base)                   ((base) + (0x24))

/* 寄存器说明：fcp 读写地址配置寄存器。
   位域定义UNION结构:  SOC_SCHARGER_ADDR_UNION */
#define SOC_SCHARGER_ADDR_ADDR(base)                  ((base) + (0x27))

/* 寄存器说明：fcp 写数据寄存器。
   位域定义UNION结构:  SOC_SCHARGER_DATA0_UNION */
#define SOC_SCHARGER_DATA0_ADDR(base)                 ((base) + (0x28))

/* 寄存器说明：FCP 中断1寄存器。
   位域定义UNION结构:  SOC_SCHARGER_ISR1_UNION */
#define SOC_SCHARGER_ISR1_ADDR(base)                  ((base) + (0x39))

/* 寄存器说明：FCP 中断2寄存器。
   位域定义UNION结构:  SOC_SCHARGER_ISR2_UNION */
#define SOC_SCHARGER_ISR2_ADDR(base)                  ((base) + (0x3A))

/* 寄存器说明：FCP 中断屏蔽1寄存器。
   位域定义UNION结构:  SOC_SCHARGER_IMR1_UNION */
#define SOC_SCHARGER_IMR1_ADDR(base)                  ((base) + (0x3B))

/* 寄存器说明：FCP 中断屏蔽2寄存器。
   位域定义UNION结构:  SOC_SCHARGER_IMR2_UNION */
#define SOC_SCHARGER_IMR2_ADDR(base)                  ((base) + (0x3C))

/* 寄存器说明：FCP中断3寄存器。
   位域定义UNION结构:  SOC_SCHARGER_FCP_IRQ3_UNION */
#define SOC_SCHARGER_FCP_IRQ3_ADDR(base)              ((base) + (0x3D))

/* 寄存器说明：FCP中断4寄存器。
   位域定义UNION结构:  SOC_SCHARGER_FCP_IRQ4_UNION */
#define SOC_SCHARGER_FCP_IRQ4_ADDR(base)              ((base) + (0x3E))

/* 寄存器说明：FCP中断5寄存器。
   位域定义UNION结构:  SOC_SCHARGER_FCP_IRQ5_UNION */
#define SOC_SCHARGER_FCP_IRQ5_ADDR(base)              ((base) + (0x3F))

/* 寄存器说明：FCP中断屏蔽3寄存器。
   位域定义UNION结构:  SOC_SCHARGER_FCP_IRQ3_MASK_UNION */
#define SOC_SCHARGER_FCP_IRQ3_MASK_ADDR(base)         ((base) + (0x40))

/* 寄存器说明：FCP中断屏蔽4寄存器。
   位域定义UNION结构:  SOC_SCHARGER_FCP_IRQ4_MASK_UNION */
#define SOC_SCHARGER_FCP_IRQ4_MASK_ADDR(base)         ((base) + (0x41))

/* 寄存器说明：FCP中断屏蔽5寄存器。
   位域定义UNION结构:  SOC_SCHARGER_FCP_IRQ5_MASK_UNION */
#define SOC_SCHARGER_FCP_IRQ5_MASK_ADDR(base)         ((base) + (0x42))

/* 寄存器说明：高压块充控制寄存器。
   位域定义UNION结构:  SOC_SCHARGER_FCP_CTRL_UNION */
#define SOC_SCHARGER_FCP_CTRL_ADDR(base)              ((base) + (0x43))

/* 寄存器说明：高压快充协议模式2档位控制寄存器。
   位域定义UNION结构:  SOC_SCHARGER_FCP_MODE2_SET_UNION */
#define SOC_SCHARGER_FCP_MODE2_SET_ADDR(base)         ((base) + (0x44))

/* 寄存器说明：高压块充Adapter控制寄存器。
   位域定义UNION结构:  SOC_SCHARGER_FCP_ADAP_CTRL_UNION */
#define SOC_SCHARGER_FCP_ADAP_CTRL_ADDR(base)         ((base) + (0x45))

/* 寄存器说明：状态机状态寄存器。
   位域定义UNION结构:  SOC_SCHARGER_MSTATE_UNION */
#define SOC_SCHARGER_MSTATE_ADDR(base)                ((base) + (0x46))

/* 寄存器说明：slave返回的数据。
   位域定义UNION结构:  SOC_SCHARGER_FCP_RDATA_UNION */
#define SOC_SCHARGER_FCP_RDATA_ADDR(base)             ((base) + (0x47))

/* 寄存器说明：slave返回数据采集好指示信号。
   位域定义UNION结构:  SOC_SCHARGER_RDATA_READY_UNION */
#define SOC_SCHARGER_RDATA_READY_ADDR(base)           ((base) + (0x48))

/* 寄存器说明：crc 使能控制寄存器。
   位域定义UNION结构:  SOC_SCHARGER_CRC_ENABLE_UNION */
#define SOC_SCHARGER_CRC_ENABLE_ADDR(base)            ((base) + (0x49))

/* 寄存器说明：crc 初始值。
   位域定义UNION结构:  SOC_SCHARGER_CRC_START_VALUE_UNION */
#define SOC_SCHARGER_CRC_START_VALUE_ADDR(base)       ((base) + (0x4A))

/* 寄存器说明：采样点调整寄存器。
   位域定义UNION结构:  SOC_SCHARGER_SAMPLE_CNT_ADJ_UNION */
#define SOC_SCHARGER_SAMPLE_CNT_ADJ_ADDR(base)        ((base) + (0x4B))

/* 寄存器说明：RX ping 最小长度高位。
   位域定义UNION结构:  SOC_SCHARGER_RX_PING_WIDTH_MIN_H_UNION */
#define SOC_SCHARGER_RX_PING_WIDTH_MIN_H_ADDR(base)   ((base) + (0x4C))

/* 寄存器说明：RX ping 最小长度低8位
   位域定义UNION结构:  SOC_SCHARGER_RX_PING_WIDTH_MIN_L_UNION */
#define SOC_SCHARGER_RX_PING_WIDTH_MIN_L_ADDR(base)   ((base) + (0x4D))

/* 寄存器说明：RX ping 最大长度高位
   位域定义UNION结构:  SOC_SCHARGER_RX_PING_WIDTH_MAX_H_UNION */
#define SOC_SCHARGER_RX_PING_WIDTH_MAX_H_ADDR(base)   ((base) + (0x4E))

/* 寄存器说明：RX ping 最大长度低8位。
   位域定义UNION结构:  SOC_SCHARGER_RX_PING_WIDTH_MAX_L_UNION */
#define SOC_SCHARGER_RX_PING_WIDTH_MAX_L_ADDR(base)   ((base) + (0x4F))

/* 寄存器说明：数据等待时间寄存器。
   位域定义UNION结构:  SOC_SCHARGER_DATA_WAIT_TIME_UNION */
#define SOC_SCHARGER_DATA_WAIT_TIME_ADDR(base)        ((base) + (0x50))

/* 寄存器说明：数据重新发送次数。
   位域定义UNION结构:  SOC_SCHARGER_RETRY_CNT_UNION */
#define SOC_SCHARGER_RETRY_CNT_ADDR(base)             ((base) + (0x51))

/* 寄存器说明：FCP软复位控制寄存器。
   位域定义UNION结构:  SOC_SCHARGER_FCP_SOFT_RST_CTRL_UNION */
#define SOC_SCHARGER_FCP_SOFT_RST_CTRL_ADDR(base)     ((base) + (0x52))

/* 寄存器说明：fcp只读预留寄存器。
   位域定义UNION结构:  SOC_SCHARGER_FCP_RO_RESERVE_UNION */
#define SOC_SCHARGER_FCP_RO_RESERVE_ADDR(base)        ((base) + (0x53))

/* 寄存器说明：FCP debug寄存器0。
   位域定义UNION结构:  SOC_SCHARGER_FCP_DEBUG_REG0_UNION */
#define SOC_SCHARGER_FCP_DEBUG_REG0_ADDR(base)        ((base) + (0x54))

/* 寄存器说明：FCP debug寄存器1。
   位域定义UNION结构:  SOC_SCHARGER_FCP_DEBUG_REG1_UNION */
#define SOC_SCHARGER_FCP_DEBUG_REG1_ADDR(base)        ((base) + (0x55))

/* 寄存器说明：FCP debug寄存器2。
   位域定义UNION结构:  SOC_SCHARGER_FCP_DEBUG_REG2_UNION */
#define SOC_SCHARGER_FCP_DEBUG_REG2_ADDR(base)        ((base) + (0x56))

/* 寄存器说明：BUCK_REG0调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_BUCK_REG0_UNION */
#define SOC_SCHARGER_BUCK_REG0_ADDR(base)             ((base) + (0x60))

/* 寄存器说明：BUCK_REG1调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_BUCK_REG1_UNION */
#define SOC_SCHARGER_BUCK_REG1_ADDR(base)             ((base) + (0x61))

/* 寄存器说明：BUCK_REG2调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_BUCK_REG2_UNION */
#define SOC_SCHARGER_BUCK_REG2_ADDR(base)             ((base) + (0x62))

/* 寄存器说明：BUCK_REG3调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_BUCK_REG3_UNION */
#define SOC_SCHARGER_BUCK_REG3_ADDR(base)             ((base) + (0x63))

/* 寄存器说明：BUCK_REG4调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_BUCK_REG4_UNION */
#define SOC_SCHARGER_BUCK_REG4_ADDR(base)             ((base) + (0x64))

/* 寄存器说明：BUCK_REG5调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_BUCK_REG5_UNION */
#define SOC_SCHARGER_BUCK_REG5_ADDR(base)             ((base) + (0x65))

/* 寄存器说明：BUCK_REG6调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_BUCK_REG6_UNION */
#define SOC_SCHARGER_BUCK_REG6_ADDR(base)             ((base) + (0x66))

/* 寄存器说明：BUCK_REG7调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_BUCK_REG7_UNION */
#define SOC_SCHARGER_BUCK_REG7_ADDR(base)             ((base) + (0x67))

/* 寄存器说明：BUCK_REG8调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_BUCK_REG8_UNION */
#define SOC_SCHARGER_BUCK_REG8_ADDR(base)             ((base) + (0x68))

/* 寄存器说明：BUCK_REG9调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_BUCK_REG9_UNION */
#define SOC_SCHARGER_BUCK_REG9_ADDR(base)             ((base) + (0x69))

/* 寄存器说明：BUCK_REG10调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_BUCK_REG10_UNION */
#define SOC_SCHARGER_BUCK_REG10_ADDR(base)            ((base) + (0x6A))

/* 寄存器说明：BUCK_REG11调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_BUCK_REG11_UNION */
#define SOC_SCHARGER_BUCK_REG11_ADDR(base)            ((base) + (0x6B))

/* 寄存器说明：BUCK_REG12调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_BUCK_REG12_UNION */
#define SOC_SCHARGER_BUCK_REG12_ADDR(base)            ((base) + (0x6C))

/* 寄存器说明：BUCK_REG13调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_BUCK_REG13_UNION */
#define SOC_SCHARGER_BUCK_REG13_ADDR(base)            ((base) + (0x6D))

/* 寄存器说明：BUCK_REG14调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_BUCK_REG14_UNION */
#define SOC_SCHARGER_BUCK_REG14_ADDR(base)            ((base) + (0x6E))

/* 寄存器说明：BUCK_REG15调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_BUCK_REG15_UNION */
#define SOC_SCHARGER_BUCK_REG15_ADDR(base)            ((base) + (0x6F))

/* 寄存器说明：BUCK两相均流调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_BUCK_REG16_UNION */
#define SOC_SCHARGER_BUCK_REG16_ADDR(base)            ((base) + (0x70))

/* 寄存器说明：BUCK电阻调节0寄存器。
   位域定义UNION结构:  SOC_SCHARGER_BUCK_RES_SEL0_UNION */
#define SOC_SCHARGER_BUCK_RES_SEL0_ADDR(base)         ((base) + (0x71))

/* 寄存器说明：BUCK电阻调节1寄存器。
   位域定义UNION结构:  SOC_SCHARGER_BUCK_RES_SEL1_UNION */
#define SOC_SCHARGER_BUCK_RES_SEL1_ADDR(base)         ((base) + (0x72))

/* 寄存器说明：BUCK电阻调节2寄存器。
   位域定义UNION结构:  SOC_SCHARGER_BUCK_RES_SEL2_UNION */
#define SOC_SCHARGER_BUCK_RES_SEL2_ADDR(base)         ((base) + (0x73))

/* 寄存器说明：BUCK电阻调节3寄存器。
   位域定义UNION结构:  SOC_SCHARGER_BUCK_RES_SEL3_UNION */
#define SOC_SCHARGER_BUCK_RES_SEL3_ADDR(base)         ((base) + (0x74))

/* 寄存器说明：BUCK电容调节0寄存器。
   位域定义UNION结构:  SOC_SCHARGER_BUCK_CAP_SEL0_UNION */
#define SOC_SCHARGER_BUCK_CAP_SEL0_ADDR(base)         ((base) + (0x75))

/* 寄存器说明：BUCK电容调节1寄存器。
   位域定义UNION结构:  SOC_SCHARGER_BUCK_CAP_SEL1_UNION */
#define SOC_SCHARGER_BUCK_CAP_SEL1_ADDR(base)         ((base) + (0x76))

/* 寄存器说明：BUCK预留0寄存器。
   位域定义UNION结构:  SOC_SCHARGER_BUCK_RESERVE0_UNION */
#define SOC_SCHARGER_BUCK_RESERVE0_ADDR(base)         ((base) + (0x77))

/* 寄存器说明：BUCK预留1寄存器。
   位域定义UNION结构:  SOC_SCHARGER_BUCK_RESERVE1_UNION */
#define SOC_SCHARGER_BUCK_RESERVE1_ADDR(base)         ((base) + (0x78))

/* 寄存器说明：BUCK预留2寄存器。
   位域定义UNION结构:  SOC_SCHARGER_BUCK_RESERVE2_UNION */
#define SOC_SCHARGER_BUCK_RESERVE2_ADDR(base)         ((base) + (0x79))

/* 寄存器说明：BUCK预留3寄存器。
   位域定义UNION结构:  SOC_SCHARGER_BUCK_RESERVE3_UNION */
#define SOC_SCHARGER_BUCK_RESERVE3_ADDR(base)         ((base) + (0x7A))

/* 寄存器说明：BUCK预留0状态寄存器。
   位域定义UNION结构:  SOC_SCHARGER_BUCK_RESERVE0_STATE_UNION */
#define SOC_SCHARGER_BUCK_RESERVE0_STATE_ADDR(base)   ((base) + (0x7B))

/* 寄存器说明：BUCK预留1状态寄存器。
   位域定义UNION结构:  SOC_SCHARGER_BUCK_RESERVE1_STATE_UNION */
#define SOC_SCHARGER_BUCK_RESERVE1_STATE_ADDR(base)   ((base) + (0x7C))

/* 寄存器说明：OTG_REG0调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_OTG_REG0_UNION */
#define SOC_SCHARGER_OTG_REG0_ADDR(base)              ((base) + (0x80))

/* 寄存器说明：OTG_REG1调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_OTG_REG1_UNION */
#define SOC_SCHARGER_OTG_REG1_ADDR(base)              ((base) + (0x81))

/* 寄存器说明：OTG_REG2调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_OTG_REG2_UNION */
#define SOC_SCHARGER_OTG_REG2_ADDR(base)              ((base) + (0x82))

/* 寄存器说明：OTG_REG3调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_OTG_REG3_UNION */
#define SOC_SCHARGER_OTG_REG3_ADDR(base)              ((base) + (0x83))

/* 寄存器说明：OTG_REG4调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_OTG_REG4_UNION */
#define SOC_SCHARGER_OTG_REG4_ADDR(base)              ((base) + (0x84))

/* 寄存器说明：OTG_REG5调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_OTG_REG5_UNION */
#define SOC_SCHARGER_OTG_REG5_ADDR(base)              ((base) + (0x85))

/* 寄存器说明：OTG_REG6调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_OTG_REG6_UNION */
#define SOC_SCHARGER_OTG_REG6_ADDR(base)              ((base) + (0x86))

/* 寄存器说明：OTG_REG7调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_OTG_REG7_UNION */
#define SOC_SCHARGER_OTG_REG7_ADDR(base)              ((base) + (0x87))

/* 寄存器说明：OTG_REG8调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_OTG_REG8_UNION */
#define SOC_SCHARGER_OTG_REG8_ADDR(base)              ((base) + (0x88))

/* 寄存器说明：OTG内部延时调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_OTG_REG9_UNION */
#define SOC_SCHARGER_OTG_REG9_ADDR(base)              ((base) + (0x89))

/* 寄存器说明：OTG_TRIM调整1寄存器。
   位域定义UNION结构:  SOC_SCHARGER_OTG_TRIM1_UNION */
#define SOC_SCHARGER_OTG_TRIM1_ADDR(base)             ((base) + (0x8A))

/* 寄存器说明：OTG_TRIM调整2寄存器。
   位域定义UNION结构:  SOC_SCHARGER_OTG_TRIM2_UNION */
#define SOC_SCHARGER_OTG_TRIM2_ADDR(base)             ((base) + (0x8B))

/* 寄存器说明：OTG预留0寄存器。
   位域定义UNION结构:  SOC_SCHARGER_OTG_RESERVE_UNION */
#define SOC_SCHARGER_OTG_RESERVE_ADDR(base)           ((base) + (0x8C))

/* 寄存器说明：OTG预留1寄存器。
   位域定义UNION结构:  SOC_SCHARGER_OTG_RESERVE1_UNION */
#define SOC_SCHARGER_OTG_RESERVE1_ADDR(base)          ((base) + (0x8D))

/* 寄存器说明：OTG预留2寄存器。
   位域定义UNION结构:  SOC_SCHARGER_OTG_RESERVE2_UNION */
#define SOC_SCHARGER_OTG_RESERVE2_ADDR(base)          ((base) + (0x8E))

/* 寄存器说明：CHG_REG0调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_CHG_REG0_UNION */
#define SOC_SCHARGER_CHG_REG0_ADDR(base)              ((base) + (0x90))

/* 寄存器说明：CHG_REG1调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_CHG_REG1_UNION */
#define SOC_SCHARGER_CHG_REG1_ADDR(base)              ((base) + (0x91))

/* 寄存器说明：CHG_REG2调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_CHG_REG2_UNION */
#define SOC_SCHARGER_CHG_REG2_ADDR(base)              ((base) + (0x92))

/* 寄存器说明：CHG_REG3调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_CHG_REG3_UNION */
#define SOC_SCHARGER_CHG_REG3_ADDR(base)              ((base) + (0x93))

/* 寄存器说明：CHG_REG4调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_CHG_REG4_UNION */
#define SOC_SCHARGER_CHG_REG4_ADDR(base)              ((base) + (0x94))

/* 寄存器说明：CHG_REG5调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_CHG_REG5_UNION */
#define SOC_SCHARGER_CHG_REG5_ADDR(base)              ((base) + (0x95))

/* 寄存器说明：CHARGER环路补偿mos电阻调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_CHG_VRES_SEL_UNION */
#define SOC_SCHARGER_CHG_VRES_SEL_ADDR(base)          ((base) + (0x96))

/* 寄存器说明：CHARGER环路补偿电容调节。
   位域定义UNION结构:  SOC_SCHARGER_CHG_CAP_SEL_UNION */
#define SOC_SCHARGER_CHG_CAP_SEL_ADDR(base)           ((base) + (0x97))

/* 寄存器说明：CHG_REG6调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_CHG_REG6_UNION */
#define SOC_SCHARGER_CHG_REG6_ADDR(base)              ((base) + (0x98))

/* 寄存器说明：CHG_REG7调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_CHG_REG7_UNION */
#define SOC_SCHARGER_CHG_REG7_ADDR(base)              ((base) + (0x99))

/* 寄存器说明：CHG_REG8调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_CHG_REG8_UNION */
#define SOC_SCHARGER_CHG_REG8_ADDR(base)              ((base) + (0x9A))

/* 寄存器说明：CHG_REG9调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_CHG_REG9_UNION */
#define SOC_SCHARGER_CHG_REG9_ADDR(base)              ((base) + (0x9B))

/* 寄存器说明：CHG_RESVI1预留寄存器。
   位域定义UNION结构:  SOC_SCHARGER_CHG_RESVI1_UNION */
#define SOC_SCHARGER_CHG_RESVI1_ADDR(base)            ((base) + (0x9C))

/* 寄存器说明：CHG_RESVI2预留寄存器。
   位域定义UNION结构:  SOC_SCHARGER_CHG_RESVI2_UNION */
#define SOC_SCHARGER_CHG_RESVI2_ADDR(base)            ((base) + (0x9D))

/* 寄存器说明：CHG_RESVO1预留寄存器。
   位域定义UNION结构:  SOC_SCHARGER_CHG_RESVO1_UNION */
#define SOC_SCHARGER_CHG_RESVO1_ADDR(base)            ((base) + (0x9E))

/* 寄存器说明：CHG_RESVO2预留寄存器。
   位域定义UNION结构:  SOC_SCHARGER_CHG_RESVO2_UNION */
#define SOC_SCHARGER_CHG_RESVO2_ADDR(base)            ((base) + (0x9F))

/* 寄存器说明：DET_TOP_REG0调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_DET_TOP_REG0_UNION */
#define SOC_SCHARGER_DET_TOP_REG0_ADDR(base)          ((base) + (0xA0))

/* 寄存器说明：DET_TOP_REG1调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_DET_TOP_REG1_UNION */
#define SOC_SCHARGER_DET_TOP_REG1_ADDR(base)          ((base) + (0xA1))

/* 寄存器说明：THSD调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_THSD_ADJ_UNION */
#define SOC_SCHARGER_THSD_ADJ_ADDR(base)              ((base) + (0xA2))

/* 寄存器说明：SCHG_LOGIC控制寄存器。
   位域定义UNION结构:  SOC_SCHARGER_SCHG_LOGIC_CTRL_UNION */
#define SOC_SCHARGER_SCHG_LOGIC_CTRL_ADDR(base)       ((base) + (0xA3))

/* 寄存器说明：BLOCK调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_BLOCK_CTRL_UNION */
#define SOC_SCHARGER_BLOCK_CTRL_ADDR(base)            ((base) + (0xA4))

/* 寄存器说明：REF_TOP调节寄存器。
   位域定义UNION结构:  SOC_SCHARGER_REF_TOP_CTRL_UNION */
#define SOC_SCHARGER_REF_TOP_CTRL_ADDR(base)          ((base) + (0xA5))

/* 寄存器说明：ADC控制寄存器
   位域定义UNION结构:  SOC_SCHARGER_ADC_CTRL_UNION */
#define SOC_SCHARGER_ADC_CTRL_ADDR(base)              ((base) + (0xB0))

/* 寄存器说明：ADC转换开始寄存器
   位域定义UNION结构:  SOC_SCHARGER_ADC_START_UNION */
#define SOC_SCHARGER_ADC_START_ADDR(base)             ((base) + (0xB1))

/* 寄存器说明：ADC转换状态指示寄存器
   位域定义UNION结构:  SOC_SCHARGER_ADC_CONV_STATUS_UNION */
#define SOC_SCHARGER_ADC_CONV_STATUS_ADDR(base)       ((base) + (0xB2))

/* 寄存器说明：ADC转换结果高位寄存器
   位域定义UNION结构:  SOC_SCHARGER_ADC_DATA1_UNION */
#define SOC_SCHARGER_ADC_DATA1_ADDR(base)             ((base) + (0xB3))

/* 寄存器说明：ADC转换结果低位寄存器
   位域定义UNION结构:  SOC_SCHARGER_ADC_DATA0_UNION */
#define SOC_SCHARGER_ADC_DATA0_ADDR(base)             ((base) + (0xB4))

/* 寄存器说明：HKADC工作IBIAS电流配置寄存器。
   位域定义UNION结构:  SOC_SCHARGER_ADC_IBIAS_SEL_UNION */
#define SOC_SCHARGER_ADC_IBIAS_SEL_ADDR(base)         ((base) + (0xB5))

/* 寄存器说明：EFUSE调节0寄存器。
   位域定义UNION结构:  SOC_SCHARGER_EFUSE_REG0_UNION */
#define SOC_SCHARGER_EFUSE_REG0_ADDR(base)            ((base) + (0xC0))

/* 寄存器说明：EFUSE调节1寄存器。
   位域定义UNION结构:  SOC_SCHARGER_EFUSE_REG1_UNION */
#define SOC_SCHARGER_EFUSE_REG1_ADDR(base)            ((base) + (0xC1))

/* 寄存器说明：EFUSE地址寄存器对应地址[7:0]。
   位域定义UNION结构:  SOC_SCHARGER_EFUSE_WE0_UNION */
#define SOC_SCHARGER_EFUSE_WE0_ADDR(base)             ((base) + (0xC2))

/* 寄存器说明：EFUSE地址寄存器对应地址[15:8]。
   位域定义UNION结构:  SOC_SCHARGER_EFUSE_WE1_UNION */
#define SOC_SCHARGER_EFUSE_WE1_ADDR(base)             ((base) + (0xC3))

/* 寄存器说明：EFUSE地址寄存器对应地址[23:16]。
   位域定义UNION结构:  SOC_SCHARGER_EFUSE_WE2_UNION */
#define SOC_SCHARGER_EFUSE_WE2_ADDR(base)             ((base) + (0xC4))

/* 寄存器说明：EFUSE地址寄存器对应地址[31:24]。
   位域定义UNION结构:  SOC_SCHARGER_EFUSE_WE3_UNION */
#define SOC_SCHARGER_EFUSE_WE3_ADDR(base)             ((base) + (0xC5))

/* 寄存器说明：EFUSE地址寄存器对应地址[39:32]。
   位域定义UNION结构:  SOC_SCHARGER_EFUSE_WE4_UNION */
#define SOC_SCHARGER_EFUSE_WE4_ADDR(base)             ((base) + (0xC6))

/* 寄存器说明：EFUSE地址寄存器对应地址[47:40]。
   位域定义UNION结构:  SOC_SCHARGER_EFUSE_WE5_UNION */
#define SOC_SCHARGER_EFUSE_WE5_ADDR(base)             ((base) + (0xC7))

/* 寄存器说明：EFUSE地址寄存器对应地址[55:48]。
   位域定义UNION结构:  SOC_SCHARGER_EFUSE_WE6_UNION */
#define SOC_SCHARGER_EFUSE_WE6_ADDR(base)             ((base) + (0xC8))

/* 寄存器说明：EFUSE地址寄存器对应地址[63:56]。
   位域定义UNION结构:  SOC_SCHARGER_EFUSE_WE7_UNION */
#define SOC_SCHARGER_EFUSE_WE7_ADDR(base)             ((base) + (0xC9))

/* 寄存器说明：EFUSE数据输出对应地址[7:0]。
   位域定义UNION结构:  SOC_SCHARGER_EFUSE_PDOB0_UNION */
#define SOC_SCHARGER_EFUSE_PDOB0_ADDR(base)           ((base) + (0xCA))

/* 寄存器说明：EFUSE数据输出对应地址[15:8]。
   位域定义UNION结构:  SOC_SCHARGER_EFUSE_PDOB1_UNION */
#define SOC_SCHARGER_EFUSE_PDOB1_ADDR(base)           ((base) + (0xCB))

/* 寄存器说明：EFUSE数据输出对应地址[23:16]。
   位域定义UNION结构:  SOC_SCHARGER_EFUSE_PDOB2_UNION */
#define SOC_SCHARGER_EFUSE_PDOB2_ADDR(base)           ((base) + (0xCC))

/* 寄存器说明：EFUSE数据输出对应地址[31:24]。
   位域定义UNION结构:  SOC_SCHARGER_EFUSE_PDOB3_UNION */
#define SOC_SCHARGER_EFUSE_PDOB3_ADDR(base)           ((base) + (0xCD))

/* 寄存器说明：EFUSE数据输出对应地址[39:32]。
   位域定义UNION结构:  SOC_SCHARGER_EFUSE_PDOB4_UNION */
#define SOC_SCHARGER_EFUSE_PDOB4_ADDR(base)           ((base) + (0xCE))

/* 寄存器说明：EFUSE数据输出对应地址[47:40]。
   位域定义UNION结构:  SOC_SCHARGER_EFUSE_PDOB5_UNION */
#define SOC_SCHARGER_EFUSE_PDOB5_ADDR(base)           ((base) + (0xCF))

/* 寄存器说明：EFUSE数据输出对应地址[55:48]。
   位域定义UNION结构:  SOC_SCHARGER_EFUSE_PDOB6_UNION */
#define SOC_SCHARGER_EFUSE_PDOB6_ADDR(base)           ((base) + (0xD0))

/* 寄存器说明：EFUSE数据输出对应地址[63:56]。
   位域定义UNION结构:  SOC_SCHARGER_EFUSE_PDOB7_UNION */
#define SOC_SCHARGER_EFUSE_PDOB7_ADDR(base)           ((base) + (0xD1))

/* 寄存器说明：EFUSE软复位控制寄存器。
   位域定义UNION结构:  SOC_SCHARGER_EFUSE_SOFT_RST_CTRL_UNION */
#define SOC_SCHARGER_EFUSE_SOFT_RST_CTRL_ADDR(base)   ((base) + (0xD2))

/* 寄存器说明：SYS调节1寄存器。
   位域定义UNION结构:  SOC_SCHARGER_SYS_RESVO1_UNION */
#define SOC_SCHARGER_SYS_RESVO1_ADDR(base)            ((base) + (0xE0))

/* 寄存器说明：SYS_RESVO2预留寄存器。
   位域定义UNION结构:  SOC_SCHARGER_SYS_RESVO2_UNION */
#define SOC_SCHARGER_SYS_RESVO2_ADDR(base)            ((base) + (0xE1))

/* 寄存器说明：SYS_RESVO3预留寄存器。
   位域定义UNION结构:  SOC_SCHARGER_SYS_RESVO3_UNION */
#define SOC_SCHARGER_SYS_RESVO3_ADDR(base)            ((base) + (0xE2))

/* 寄存器说明：SYS_RESVO4预留寄存器。
   位域定义UNION结构:  SOC_SCHARGER_SYS_RESVO4_UNION */
#define SOC_SCHARGER_SYS_RESVO4_ADDR(base)            ((base) + (0xE3))

/* 寄存器说明：SYS_RESVI1预留寄存器。
   位域定义UNION结构:  SOC_SCHARGER_SYS_RESVI1_UNION */
#define SOC_SCHARGER_SYS_RESVI1_ADDR(base)            ((base) + (0xE4))

/* 寄存器说明：SYS_RESVI2预留寄存器。
   位域定义UNION结构:  SOC_SCHARGER_SYS_RESVI2_UNION */
#define SOC_SCHARGER_SYS_RESVI2_ADDR(base)            ((base) + (0xE5))

/* 寄存器说明：2MHz高精度时钟频率修调寄存器。
   位域定义UNION结构:  SOC_SCHARGER_OSC_FCP_UNION */
#define SOC_SCHARGER_OSC_FCP_ADDR(base)               ((base) + (0xE6))

/* 寄存器说明：全局软复位控制寄存器。
   位域定义UNION结构:  SOC_SCHARGER_GLB_SOFT_RST_CTRL_UNION */
#define SOC_SCHARGER_GLB_SOFT_RST_CTRL_ADDR(base)     ((base) + (0xE7))

/* 寄存器说明：看门狗软复位控制寄存器。
   位域定义UNION结构:  SOC_SCHARGER_WATCHDOG_SOFT_RST_UNION */
#define SOC_SCHARGER_WATCHDOG_SOFT_RST_ADDR(base)     ((base) + (0xE8))

/* 寄存器说明：喂狗时间控制寄存器。
   位域定义UNION结构:  SOC_SCHARGER_WATCHDOG_CTRL_UNION */
#define SOC_SCHARGER_WATCHDOG_CTRL_ADDR(base)         ((base) + (0xE9))

/* 寄存器说明：clk gating控制寄存器。
   位域定义UNION结构:  SOC_SCHARGER_CLK_GATE_UNION */
#define SOC_SCHARGER_CLK_GATE_ADDR(base)              ((base) + (0xEA))





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
                     (1/1) reg_define
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_SCHARGER_CHIP_VERSION_0_UNION
 结构说明  : CHIP_VERSION_0 寄存器结构定义。地址偏移量:0x00，初值:0x36，宽度:8
 寄存器说明: 芯片版本寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chip_id2 : 8;  /* bit[0-7]: ASIC码表示项目编号6。 */
    } reg;
} SOC_SCHARGER_CHIP_VERSION_0_UNION;
#endif
#define SOC_SCHARGER_CHIP_VERSION_0_chip_id2_START  (0)
#define SOC_SCHARGER_CHIP_VERSION_0_chip_id2_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_CHIP_VERSION_1_UNION
 结构说明  : CHIP_VERSION_1 寄存器结构定义。地址偏移量:0x01，初值:0x35，宽度:8
 寄存器说明: 芯片版本寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chip_id3 : 8;  /* bit[0-7]: ASIC码表示项目编号5。 */
    } reg;
} SOC_SCHARGER_CHIP_VERSION_1_UNION;
#endif
#define SOC_SCHARGER_CHIP_VERSION_1_chip_id3_START  (0)
#define SOC_SCHARGER_CHIP_VERSION_1_chip_id3_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_CHIP_VERSION_2_UNION
 结构说明  : CHIP_VERSION_2 寄存器结构定义。地址偏移量:0x02，初值:0x32，宽度:8
 寄存器说明: 芯片版本寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chip_id4 : 8;  /* bit[0-7]: ASIC码表示项目编号2。 */
    } reg;
} SOC_SCHARGER_CHIP_VERSION_2_UNION;
#endif
#define SOC_SCHARGER_CHIP_VERSION_2_chip_id4_START  (0)
#define SOC_SCHARGER_CHIP_VERSION_2_chip_id4_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_CHIP_VERSION_3_UNION
 结构说明  : CHIP_VERSION_3 寄存器结构定义。地址偏移量:0x03，初值:0x33，宽度:8
 寄存器说明: 芯片版本寄存器3。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chip_id5 : 8;  /* bit[0-7]: ASIC码表示项目编号3。 */
    } reg;
} SOC_SCHARGER_CHIP_VERSION_3_UNION;
#endif
#define SOC_SCHARGER_CHIP_VERSION_3_chip_id5_START  (0)
#define SOC_SCHARGER_CHIP_VERSION_3_chip_id5_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_CHIP_VERSION_4_UNION
 结构说明  : CHIP_VERSION_4 寄存器结构定义。地址偏移量:0x04，初值:0x03，宽度:8
 寄存器说明: 芯片版本寄存器4。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chip_id0 : 8;  /* bit[0-7]: 版本寄存器，表示V300的3。 */
    } reg;
} SOC_SCHARGER_CHIP_VERSION_4_UNION;
#endif
#define SOC_SCHARGER_CHIP_VERSION_4_chip_id0_START  (0)
#define SOC_SCHARGER_CHIP_VERSION_4_chip_id0_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_CHIP_VERSION_5_UNION
 结构说明  : CHIP_VERSION_5 寄存器结构定义。地址偏移量:0x05，初值:0x00，宽度:8
 寄存器说明: 芯片版本寄存器5。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chip_id1 : 8;  /* bit[0-7]: 版本寄存器，表示V300的00。 */
    } reg;
} SOC_SCHARGER_CHIP_VERSION_5_UNION;
#endif
#define SOC_SCHARGER_CHIP_VERSION_5_chip_id1_START  (0)
#define SOC_SCHARGER_CHIP_VERSION_5_chip_id1_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_STATUS0_UNION
 结构说明  : STATUS0 寄存器结构定义。地址偏移量:0x06，初值:0x00，宽度:8
 寄存器说明: 状态标志0寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_rechg_state : 1;  /* bit[0]  : 系统复充电状态记录寄存器：
                                                          0：not in recharging state；
                                                          1：In recharging state。 */
        unsigned char  chg_therm_state : 1;  /* bit[1]  : 系统热调整状态记录寄存器：
                                                          0：Normal；
                                                          1：In Thermal Regulation。 */
        unsigned char  chg_dpm_state   : 1;  /* bit[2]  : 系统dpm状态记录寄存器：
                                                          0：Normal； 
                                                          1：In dpm Regulation。 */
        unsigned char  chg_acl_state   : 1;  /* bit[3]  : 系统acl状态记录寄存器：
                                                          0：Normal；
                                                          1：In acl Regulation； */
        unsigned char  chg_chgstate    : 2;  /* bit[4-5]: 充电状态记录寄存器：
                                                          00：Not Charging；
                                                          01：Pre-charge；
                                                          10：Fast-charg；
                                                          11：Charge Termination Done。 */
        unsigned char  otg_on          : 1;  /* bit[6]  : boost状态指示：
                                                          0：OTG关闭；
                                                          1：OTG开启。 */
        unsigned char  buck_ok         : 1;  /* bit[7]  : buck工作状态指示：
                                                          0：buck没有工作；
                                                          1：buck在工作。 */
    } reg;
} SOC_SCHARGER_STATUS0_UNION;
#endif
#define SOC_SCHARGER_STATUS0_chg_rechg_state_START  (0)
#define SOC_SCHARGER_STATUS0_chg_rechg_state_END    (0)
#define SOC_SCHARGER_STATUS0_chg_therm_state_START  (1)
#define SOC_SCHARGER_STATUS0_chg_therm_state_END    (1)
#define SOC_SCHARGER_STATUS0_chg_dpm_state_START    (2)
#define SOC_SCHARGER_STATUS0_chg_dpm_state_END      (2)
#define SOC_SCHARGER_STATUS0_chg_acl_state_START    (3)
#define SOC_SCHARGER_STATUS0_chg_acl_state_END      (3)
#define SOC_SCHARGER_STATUS0_chg_chgstate_START     (4)
#define SOC_SCHARGER_STATUS0_chg_chgstate_END       (5)
#define SOC_SCHARGER_STATUS0_otg_on_START           (6)
#define SOC_SCHARGER_STATUS0_otg_on_END             (6)
#define SOC_SCHARGER_STATUS0_buck_ok_START          (7)
#define SOC_SCHARGER_STATUS0_buck_ok_END            (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_STATUS1_UNION
 结构说明  : STATUS1 寄存器结构定义。地址偏移量:0x07，初值:0x03，宽度:8
 寄存器说明: 状态标志1寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  batfet_ctrl    : 1;  /* bit[0]  : 充电管控制状态寄存器：
                                                         0：关闭batfet；
                                                         1：打开batfet。 */
        unsigned char  wdt_time_out_n : 1;  /* bit[1]  : 0: watchdog timer 溢出，SOC在规定时间内没有清watchdog timer寄存器，即在规定时间内没有对wd_rst_n（0xE8）寄存器写1；
                                                         1: watchdog timer 功能没有触发 或watchdog timer正常； */
        unsigned char  otg_en_in      : 1;  /* bit[2]  : OTG使能的指示信号：
                                                         0：OTG没有使能；
                                                         1：OTG已经使能； */
        unsigned char  chg_batfet_ocp : 1;  /* bit[3]  : batfet 12A 过流保护状态指示寄存器：
                                                         0：没有过流；
                                                         1：过流保护。 */
        unsigned char  reserved       : 4;  /* bit[4-7]: 保留。 */
    } reg;
} SOC_SCHARGER_STATUS1_UNION;
#endif
#define SOC_SCHARGER_STATUS1_batfet_ctrl_START     (0)
#define SOC_SCHARGER_STATUS1_batfet_ctrl_END       (0)
#define SOC_SCHARGER_STATUS1_wdt_time_out_n_START  (1)
#define SOC_SCHARGER_STATUS1_wdt_time_out_n_END    (1)
#define SOC_SCHARGER_STATUS1_otg_en_in_START       (2)
#define SOC_SCHARGER_STATUS1_otg_en_in_END         (2)
#define SOC_SCHARGER_STATUS1_chg_batfet_ocp_START  (3)
#define SOC_SCHARGER_STATUS1_chg_batfet_ocp_END    (3)


/*****************************************************************************
 结构名    : SOC_SCHARGER_STATUS2_UNION
 结构说明  : STATUS2 寄存器结构定义。地址偏移量:0x08，初值:0x00，宽度:8
 寄存器说明: 状态标志2寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otg_state : 8;  /* bit[0-7]: OTG状态指示。
                                                    注：内部调试用。 */
    } reg;
} SOC_SCHARGER_STATUS2_UNION;
#endif
#define SOC_SCHARGER_STATUS2_otg_state_START  (0)
#define SOC_SCHARGER_STATUS2_otg_state_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_IRQ_STATUS0_UNION
 结构说明  : IRQ_STATUS0 寄存器结构定义。地址偏移量:0x09，初值:0x00，宽度:8
 寄存器说明: 中断状态标志0寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otmp_140_r  : 1;  /* bit[0]: 温度状态记录寄存器：
                                                    0：温度没超过设置温度(140℃)；
                                                    1：温度超过设置温度(140℃)。 */
        unsigned char  otg_ovp_r   : 1;  /* bit[1]: OTG输出过压状态记录寄存器：
                                                    0：otg boost 没有发生过压；
                                                    1：otg boost 发生过压。 */
        unsigned char  otg_uvp_r   : 1;  /* bit[2]: OTG输出欠压状态记录寄存器：
                                                    0：otg boost 没有发生欠压；
                                                    1：otg boost 发生欠压。 */
        unsigned char  otg_ocp_r   : 1;  /* bit[3]: OTG输出过流状态记录寄存器：
                                                    0：otg 没有发生过流；
                                                    1：otg 发生过流。 */
        unsigned char  otg_scp_r   : 1;  /* bit[4]: OTG输出短路状态记录寄存器：
                                                    0：otg 没有发生短路；
                                                    1：otg 发生短路。 */
        unsigned char  otmp_jreg_r : 1;  /* bit[5]: 温度超过热调制温度状态记录寄存器：
                                                    0：温度没超过热调整设置温度；
                                                    1：温度超过热调整设置温度。 */
        unsigned char  buck_ocp_r  : 1;  /* bit[6]: BUCK输出过流状态记录寄存器：
                                                    0：buck没有发生过流；
                                                    1：buck发生过流。 */
        unsigned char  buck_scp_r  : 1;  /* bit[7]: BUCK输出短路状态记录寄存器：
                                                    0：buck没有发生短路；
                                                    1：buck发生短路。 */
    } reg;
} SOC_SCHARGER_IRQ_STATUS0_UNION;
#endif
#define SOC_SCHARGER_IRQ_STATUS0_otmp_140_r_START   (0)
#define SOC_SCHARGER_IRQ_STATUS0_otmp_140_r_END     (0)
#define SOC_SCHARGER_IRQ_STATUS0_otg_ovp_r_START    (1)
#define SOC_SCHARGER_IRQ_STATUS0_otg_ovp_r_END      (1)
#define SOC_SCHARGER_IRQ_STATUS0_otg_uvp_r_START    (2)
#define SOC_SCHARGER_IRQ_STATUS0_otg_uvp_r_END      (2)
#define SOC_SCHARGER_IRQ_STATUS0_otg_ocp_r_START    (3)
#define SOC_SCHARGER_IRQ_STATUS0_otg_ocp_r_END      (3)
#define SOC_SCHARGER_IRQ_STATUS0_otg_scp_r_START    (4)
#define SOC_SCHARGER_IRQ_STATUS0_otg_scp_r_END      (4)
#define SOC_SCHARGER_IRQ_STATUS0_otmp_jreg_r_START  (5)
#define SOC_SCHARGER_IRQ_STATUS0_otmp_jreg_r_END    (5)
#define SOC_SCHARGER_IRQ_STATUS0_buck_ocp_r_START   (6)
#define SOC_SCHARGER_IRQ_STATUS0_buck_ocp_r_END     (6)
#define SOC_SCHARGER_IRQ_STATUS0_buck_scp_r_START   (7)
#define SOC_SCHARGER_IRQ_STATUS0_buck_scp_r_END     (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_IRQ_STATUS1_UNION
 结构说明  : IRQ_STATUS1 寄存器结构定义。地址偏移量:0x0A，初值:0x00，宽度:8
 寄存器说明: 中断状态标志1寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  regn_ocp_r       : 1;  /* bit[0]: ldo5过流状态记录寄存器：
                                                         0：ldo5没有过流；
                                                         1：ldo5发生过流。 */
        unsigned char  vbat_ovp_r       : 1;  /* bit[1]: vbat(charger IC电池)过压状态记录寄存器：
                                                         0：没有过压（正常，vbat<102% ）；
                                                         1：过压发生（vbat>104%）。 */
        unsigned char  vbus_uvp_r       : 1;  /* bit[2]: vbus欠压状态记录寄存器：
                                                         0：vbus 没有发生欠压；
                                                         1：vbus 发生欠压。 */
        unsigned char  vbus_ovp_r       : 1;  /* bit[3]: vbus过压状态记录寄存器：
                                                         0：vbus 没有发生过压；
                                                         1：vbus 发生过压。 */
        unsigned char  sys_ocp_r        : 1;  /* bit[4]: 电池反向放电过流状态记录寄存器：
                                                         0：Normal；
                                                         1：反向放电过流。 */
        unsigned char  chg_fast_fault_r : 1;  /* bit[5]: 快充电fault状态记录寄存器：
                                                         0：Normal； 
                                                         1：In fast charging fault。 */
        unsigned char  chg_pre_fault_r  : 1;  /* bit[6]: 预充电fault状态记录寄存器：
                                                         0：Normal；
                                                         1：In pre charging fault。 */
        unsigned char  chg_tri_fault_r  : 1;  /* bit[7]: 涓流充电fault状态记录寄存器：
                                                         0：Normal；
                                                         1：In tricle charging fault。 */
    } reg;
} SOC_SCHARGER_IRQ_STATUS1_UNION;
#endif
#define SOC_SCHARGER_IRQ_STATUS1_regn_ocp_r_START        (0)
#define SOC_SCHARGER_IRQ_STATUS1_regn_ocp_r_END          (0)
#define SOC_SCHARGER_IRQ_STATUS1_vbat_ovp_r_START        (1)
#define SOC_SCHARGER_IRQ_STATUS1_vbat_ovp_r_END          (1)
#define SOC_SCHARGER_IRQ_STATUS1_vbus_uvp_r_START        (2)
#define SOC_SCHARGER_IRQ_STATUS1_vbus_uvp_r_END          (2)
#define SOC_SCHARGER_IRQ_STATUS1_vbus_ovp_r_START        (3)
#define SOC_SCHARGER_IRQ_STATUS1_vbus_ovp_r_END          (3)
#define SOC_SCHARGER_IRQ_STATUS1_sys_ocp_r_START         (4)
#define SOC_SCHARGER_IRQ_STATUS1_sys_ocp_r_END           (4)
#define SOC_SCHARGER_IRQ_STATUS1_chg_fast_fault_r_START  (5)
#define SOC_SCHARGER_IRQ_STATUS1_chg_fast_fault_r_END    (5)
#define SOC_SCHARGER_IRQ_STATUS1_chg_pre_fault_r_START   (6)
#define SOC_SCHARGER_IRQ_STATUS1_chg_pre_fault_r_END     (6)
#define SOC_SCHARGER_IRQ_STATUS1_chg_tri_fault_r_START   (7)
#define SOC_SCHARGER_IRQ_STATUS1_chg_tri_fault_r_END     (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_IRQ_STATUS2_UNION
 结构说明  : IRQ_STATUS2 寄存器结构定义。地址偏移量:0x0B，初值:0x00，宽度:8
 寄存器说明: 中断状态标志1寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  bat_ltmp_r : 1;  /* bit[0]  : 电池温度检测状态记录寄存器：
                                                     0：电池没有发生低温过温（正常）；
                                                     1：电池低温过温。 */
        unsigned char  bat_htmp_r : 1;  /* bit[1]  : 电池温度检测状态记录寄存器：
                                                     0：电池没有发生高温过温（正常）；
                                                     1：电池高温过温。 */
        unsigned char  reserved   : 6;  /* bit[2-7]: 保留。 */
    } reg;
} SOC_SCHARGER_IRQ_STATUS2_UNION;
#endif
#define SOC_SCHARGER_IRQ_STATUS2_bat_ltmp_r_START  (0)
#define SOC_SCHARGER_IRQ_STATUS2_bat_ltmp_r_END    (0)
#define SOC_SCHARGER_IRQ_STATUS2_bat_htmp_r_START  (1)
#define SOC_SCHARGER_IRQ_STATUS2_bat_htmp_r_END    (1)


/*****************************************************************************
 结构名    : SOC_SCHARGER_IRQ0_UNION
 结构说明  : IRQ0 寄存器结构定义。地址偏移量:0x0C，初值:0x00，宽度:8
 寄存器说明: 中断0寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otmp_140_r  : 1;  /* bit[0]: 0：无此中断；
                                                    1：温度超过设置温度(140℃)中断。 */
        unsigned char  otg_ovp_r   : 1;  /* bit[1]: 0：无此中断；
                                                    1：otg boost 输出过压中断。 */
        unsigned char  otg_uvp_r   : 1;  /* bit[2]: 0：无此中断；
                                                    1：otg boost 输出欠压中断。 */
        unsigned char  otg_ocp_r   : 1;  /* bit[3]: 0：无此中断；
                                                    1：otg 输出过流中断。 */
        unsigned char  otg_scp_r   : 1;  /* bit[4]: 0：无此中断；
                                                    1：otg 输出短路中断。 */
        unsigned char  otmp_jreg_r : 1;  /* bit[5]: 0：无此中断；
                                                    1：温度超过热调整设置温度中断。 */
        unsigned char  buck_ocp_r  : 1;  /* bit[6]: 0：无此中断；
                                                    1：BUCK输出过流中断。 */
        unsigned char  buck_scp_r  : 1;  /* bit[7]: 0：无此中断；
                                                    1：BUCK输出短路中断。 */
    } reg;
} SOC_SCHARGER_IRQ0_UNION;
#endif
#define SOC_SCHARGER_IRQ0_otmp_140_r_START   (0)
#define SOC_SCHARGER_IRQ0_otmp_140_r_END     (0)
#define SOC_SCHARGER_IRQ0_otg_ovp_r_START    (1)
#define SOC_SCHARGER_IRQ0_otg_ovp_r_END      (1)
#define SOC_SCHARGER_IRQ0_otg_uvp_r_START    (2)
#define SOC_SCHARGER_IRQ0_otg_uvp_r_END      (2)
#define SOC_SCHARGER_IRQ0_otg_ocp_r_START    (3)
#define SOC_SCHARGER_IRQ0_otg_ocp_r_END      (3)
#define SOC_SCHARGER_IRQ0_otg_scp_r_START    (4)
#define SOC_SCHARGER_IRQ0_otg_scp_r_END      (4)
#define SOC_SCHARGER_IRQ0_otmp_jreg_r_START  (5)
#define SOC_SCHARGER_IRQ0_otmp_jreg_r_END    (5)
#define SOC_SCHARGER_IRQ0_buck_ocp_r_START   (6)
#define SOC_SCHARGER_IRQ0_buck_ocp_r_END     (6)
#define SOC_SCHARGER_IRQ0_buck_scp_r_START   (7)
#define SOC_SCHARGER_IRQ0_buck_scp_r_END     (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_IRQ1_UNION
 结构说明  : IRQ1 寄存器结构定义。地址偏移量:0x0D，初值:0x00，宽度:8
 寄存器说明: 中断1寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  regn_ocp_r       : 1;  /* bit[0]: 0：无此中断；
                                                         1：ldo5输出过流中断。 */
        unsigned char  vbat_ovp_r       : 1;  /* bit[1]: 0：无此中断；
                                                         1：vbat(charger IC电池)输出过压中断。 */
        unsigned char  vbus_uvp_r       : 1;  /* bit[2]: 0：无此中断；
                                                         1：vbus输出欠压中断。 */
        unsigned char  vbus_ovp_r       : 1;  /* bit[3]: 0：无此中断；
                                                         1：vbus输出过压中断。 */
        unsigned char  sys_ocp_r        : 1;  /* bit[4]: 0：无此中断；
                                                         1：电池反向放电过流中断。 */
        unsigned char  chg_fast_fault_r : 1;  /* bit[5]: 0：无此中断；
                                                         1：快充电fault中断。 */
        unsigned char  chg_pre_fault_r  : 1;  /* bit[6]: 0：无此中断；
                                                         1：预充电fault中断。 */
        unsigned char  chg_tri_fault_r  : 1;  /* bit[7]: 0：无此中断；
                                                         1：涓流充电fault中断。 */
    } reg;
} SOC_SCHARGER_IRQ1_UNION;
#endif
#define SOC_SCHARGER_IRQ1_regn_ocp_r_START        (0)
#define SOC_SCHARGER_IRQ1_regn_ocp_r_END          (0)
#define SOC_SCHARGER_IRQ1_vbat_ovp_r_START        (1)
#define SOC_SCHARGER_IRQ1_vbat_ovp_r_END          (1)
#define SOC_SCHARGER_IRQ1_vbus_uvp_r_START        (2)
#define SOC_SCHARGER_IRQ1_vbus_uvp_r_END          (2)
#define SOC_SCHARGER_IRQ1_vbus_ovp_r_START        (3)
#define SOC_SCHARGER_IRQ1_vbus_ovp_r_END          (3)
#define SOC_SCHARGER_IRQ1_sys_ocp_r_START         (4)
#define SOC_SCHARGER_IRQ1_sys_ocp_r_END           (4)
#define SOC_SCHARGER_IRQ1_chg_fast_fault_r_START  (5)
#define SOC_SCHARGER_IRQ1_chg_fast_fault_r_END    (5)
#define SOC_SCHARGER_IRQ1_chg_pre_fault_r_START   (6)
#define SOC_SCHARGER_IRQ1_chg_pre_fault_r_END     (6)
#define SOC_SCHARGER_IRQ1_chg_tri_fault_r_START   (7)
#define SOC_SCHARGER_IRQ1_chg_tri_fault_r_END     (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_IRQ2_UNION
 结构说明  : IRQ2 寄存器结构定义。地址偏移量:0x0E，初值:0x00，宽度:8
 寄存器说明: 中断2寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  bat_ltmp_r : 1;  /* bit[0]  : 0：无此中断；
                                                     1：电池低温过温中断。 */
        unsigned char  bat_htmp_r : 1;  /* bit[1]  : 0：无此中断；
                                                     1：电池高温过温中断。 */
        unsigned char  reserved   : 6;  /* bit[2-7]: 保留。 */
    } reg;
} SOC_SCHARGER_IRQ2_UNION;
#endif
#define SOC_SCHARGER_IRQ2_bat_ltmp_r_START  (0)
#define SOC_SCHARGER_IRQ2_bat_ltmp_r_END    (0)
#define SOC_SCHARGER_IRQ2_bat_htmp_r_START  (1)
#define SOC_SCHARGER_IRQ2_bat_htmp_r_END    (1)


/*****************************************************************************
 结构名    : SOC_SCHARGER_WATCHDOG_IRQ_UNION
 结构说明  : WATCHDOG_IRQ 寄存器结构定义。地址偏移量:0x0F，初值:0x00，宽度:8
 寄存器说明: 看门狗中断寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  wdt_irq  : 1;  /* bit[0]  : 看门狗中断事件：
                                                   0：未发生看门中断事件；
                                                   1：发生看门狗中断。 */
        unsigned char  reserved : 7;  /* bit[1-7]: 保留。 */
    } reg;
} SOC_SCHARGER_WATCHDOG_IRQ_UNION;
#endif
#define SOC_SCHARGER_WATCHDOG_IRQ_wdt_irq_START   (0)
#define SOC_SCHARGER_WATCHDOG_IRQ_wdt_irq_END     (0)


/*****************************************************************************
 结构名    : SOC_SCHARGER_IRQ0_MASK_UNION
 结构说明  : IRQ0_MASK 寄存器结构定义。地址偏移量:0x10，初值:0x48，宽度:8
 寄存器说明: 中断屏蔽0寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otmp_140_mk  : 1;  /* bit[0]: 0：使能该中断；(默认不屏蔽)
                                                     1：屏蔽该中断。 */
        unsigned char  otg_ovp_mk   : 1;  /* bit[1]: 0：使能该中断；(默认不屏蔽)
                                                     1：屏蔽该中断。 */
        unsigned char  otg_uvp_mk   : 1;  /* bit[2]: 0：使能该中断；(默认不屏蔽)
                                                     1：屏蔽该中断。 */
        unsigned char  otg_ocp_mk   : 1;  /* bit[3]: 0：使能该中断；
                                                     1：屏蔽该中断。(默认屏蔽) */
        unsigned char  otg_scp_mk   : 1;  /* bit[4]: 0：使能该中断；(默认不屏蔽)
                                                     1：屏蔽该中断。 */
        unsigned char  otmp_jreg_mk : 1;  /* bit[5]: 0：使能该中断；(默认不屏蔽)
                                                     1：屏蔽该中断。 */
        unsigned char  buck_ocp_mk  : 1;  /* bit[6]: 0：使能该中断；
                                                     1：屏蔽该中断。（默认屏蔽） */
        unsigned char  buck_scp_mk  : 1;  /* bit[7]: 0：使能该中断；(默认不屏蔽)
                                                     1：屏蔽该中断。 */
    } reg;
} SOC_SCHARGER_IRQ0_MASK_UNION;
#endif
#define SOC_SCHARGER_IRQ0_MASK_otmp_140_mk_START   (0)
#define SOC_SCHARGER_IRQ0_MASK_otmp_140_mk_END     (0)
#define SOC_SCHARGER_IRQ0_MASK_otg_ovp_mk_START    (1)
#define SOC_SCHARGER_IRQ0_MASK_otg_ovp_mk_END      (1)
#define SOC_SCHARGER_IRQ0_MASK_otg_uvp_mk_START    (2)
#define SOC_SCHARGER_IRQ0_MASK_otg_uvp_mk_END      (2)
#define SOC_SCHARGER_IRQ0_MASK_otg_ocp_mk_START    (3)
#define SOC_SCHARGER_IRQ0_MASK_otg_ocp_mk_END      (3)
#define SOC_SCHARGER_IRQ0_MASK_otg_scp_mk_START    (4)
#define SOC_SCHARGER_IRQ0_MASK_otg_scp_mk_END      (4)
#define SOC_SCHARGER_IRQ0_MASK_otmp_jreg_mk_START  (5)
#define SOC_SCHARGER_IRQ0_MASK_otmp_jreg_mk_END    (5)
#define SOC_SCHARGER_IRQ0_MASK_buck_ocp_mk_START   (6)
#define SOC_SCHARGER_IRQ0_MASK_buck_ocp_mk_END     (6)
#define SOC_SCHARGER_IRQ0_MASK_buck_scp_mk_START   (7)
#define SOC_SCHARGER_IRQ0_MASK_buck_scp_mk_END     (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_IRQ1_MASK_UNION
 结构说明  : IRQ1_MASK 寄存器结构定义。地址偏移量:0x11，初值:0x10，宽度:8
 寄存器说明: 中断屏蔽1寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  regn_ocp_mk       : 1;  /* bit[0]: 0：使能该中断；(默认不屏蔽)
                                                          1：屏蔽该中断。 */
        unsigned char  vbat_ovp_mk       : 1;  /* bit[1]: 0：使能该中断；(默认不屏蔽)
                                                          1：屏蔽该中断。 */
        unsigned char  vbus_uvp_mk       : 1;  /* bit[2]: 0：使能该中断；(默认不屏蔽)
                                                          1：屏蔽该中断。 */
        unsigned char  vbus_ovp_mk       : 1;  /* bit[3]: 0：使能该中断；(默认不屏蔽)
                                                          1：屏蔽该中断。 */
        unsigned char  sys_ocp_mk        : 1;  /* bit[4]: 0：使能该中断；
                                                          1：屏蔽该中断。(默认屏蔽) */
        unsigned char  chg_fast_fault_mk : 1;  /* bit[5]: 0：使能该中断；(默认不屏蔽)
                                                          1：屏蔽该中断。 */
        unsigned char  chg_pre_fault_mk  : 1;  /* bit[6]: 0：使能该中断；(默认不屏蔽)
                                                          1：屏蔽该中断。 */
        unsigned char  chg_tri_fault_mk  : 1;  /* bit[7]: 0：使能该中断；(默认不屏蔽)
                                                          1：屏蔽该中断。 */
    } reg;
} SOC_SCHARGER_IRQ1_MASK_UNION;
#endif
#define SOC_SCHARGER_IRQ1_MASK_regn_ocp_mk_START        (0)
#define SOC_SCHARGER_IRQ1_MASK_regn_ocp_mk_END          (0)
#define SOC_SCHARGER_IRQ1_MASK_vbat_ovp_mk_START        (1)
#define SOC_SCHARGER_IRQ1_MASK_vbat_ovp_mk_END          (1)
#define SOC_SCHARGER_IRQ1_MASK_vbus_uvp_mk_START        (2)
#define SOC_SCHARGER_IRQ1_MASK_vbus_uvp_mk_END          (2)
#define SOC_SCHARGER_IRQ1_MASK_vbus_ovp_mk_START        (3)
#define SOC_SCHARGER_IRQ1_MASK_vbus_ovp_mk_END          (3)
#define SOC_SCHARGER_IRQ1_MASK_sys_ocp_mk_START         (4)
#define SOC_SCHARGER_IRQ1_MASK_sys_ocp_mk_END           (4)
#define SOC_SCHARGER_IRQ1_MASK_chg_fast_fault_mk_START  (5)
#define SOC_SCHARGER_IRQ1_MASK_chg_fast_fault_mk_END    (5)
#define SOC_SCHARGER_IRQ1_MASK_chg_pre_fault_mk_START   (6)
#define SOC_SCHARGER_IRQ1_MASK_chg_pre_fault_mk_END     (6)
#define SOC_SCHARGER_IRQ1_MASK_chg_tri_fault_mk_START   (7)
#define SOC_SCHARGER_IRQ1_MASK_chg_tri_fault_mk_END     (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_IRQ2_MASK_UNION
 结构说明  : IRQ2_MASK 寄存器结构定义。地址偏移量:0x12，初值:0x00，宽度:8
 寄存器说明: 中断屏蔽2寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  bat_ltmp_mk : 1;  /* bit[0]  : 0：使能该中断；(默认不屏蔽)
                                                      1：屏蔽该中断。 */
        unsigned char  bat_htmp_mk : 1;  /* bit[1]  : 0：使能该中断；(默认不屏蔽)
                                                      1：屏蔽该中断。 */
        unsigned char  reserved    : 6;  /* bit[2-7]: 保留。 */
    } reg;
} SOC_SCHARGER_IRQ2_MASK_UNION;
#endif
#define SOC_SCHARGER_IRQ2_MASK_bat_ltmp_mk_START  (0)
#define SOC_SCHARGER_IRQ2_MASK_bat_ltmp_mk_END    (0)
#define SOC_SCHARGER_IRQ2_MASK_bat_htmp_mk_START  (1)
#define SOC_SCHARGER_IRQ2_MASK_bat_htmp_mk_END    (1)


/*****************************************************************************
 结构名    : SOC_SCHARGER_WATCHDOG_IRQ_MASK_UNION
 结构说明  : WATCHDOG_IRQ_MASK 寄存器结构定义。地址偏移量:0x13，初值:0x00，宽度:8
 寄存器说明: 看门狗中断屏蔽寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  wdt_irq_mk : 1;  /* bit[0]  : 0：使能该中断；
                                                     1：屏蔽该中断。 */
        unsigned char  reserved   : 7;  /* bit[1-7]: 保留。 */
    } reg;
} SOC_SCHARGER_WATCHDOG_IRQ_MASK_UNION;
#endif
#define SOC_SCHARGER_WATCHDOG_IRQ_MASK_wdt_irq_mk_START  (0)
#define SOC_SCHARGER_WATCHDOG_IRQ_MASK_wdt_irq_mk_END    (0)


/*****************************************************************************
 结构名    : SOC_SCHARGER_STATUIS_UNION
 结构说明  : STATUIS 寄存器结构定义。地址偏移量:0x20，初值:0x00，宽度:8
 寄存器说明: fcp slave 连接状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  attach   : 1;  /* bit[0]  : 0：检测到装置未插入；
                                                   1：检测到装置插入 */
        unsigned char  reserved : 5;  /* bit[1-5]: 保留。 */
        unsigned char  dvc      : 2;  /* bit[6-7]: 00：检测没有开始或者正在检测状态；
                                                   01：检测到无效FCP slave；
                                                   10：保留；
                                                   11：检测到FCP slave。 */
    } reg;
} SOC_SCHARGER_STATUIS_UNION;
#endif
#define SOC_SCHARGER_STATUIS_attach_START    (0)
#define SOC_SCHARGER_STATUIS_attach_END      (0)
#define SOC_SCHARGER_STATUIS_dvc_START       (6)
#define SOC_SCHARGER_STATUIS_dvc_END         (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_CNTL_UNION
 结构说明  : CNTL 寄存器结构定义。地址偏移量:0x21，初值:0x00，宽度:8
 寄存器说明: XXXX。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  sndcmd   : 1;  /* bit[0]  : fcp master transaction 开始控制寄存器。 */
        unsigned char  reserved_0: 1;  /* bit[1]  : 保留。 */
        unsigned char  mstr_rst : 1;  /* bit[2]  : fcp master 控制slave复位寄存器。 */
        unsigned char  enable   : 1;  /* bit[3]  : fcp 使能控制寄存器。 */
        unsigned char  reserved_1: 4;  /* bit[4-7]: 保留。 */
    } reg;
} SOC_SCHARGER_CNTL_UNION;
#endif
#define SOC_SCHARGER_CNTL_sndcmd_START    (0)
#define SOC_SCHARGER_CNTL_sndcmd_END      (0)
#define SOC_SCHARGER_CNTL_mstr_rst_START  (2)
#define SOC_SCHARGER_CNTL_mstr_rst_END    (2)
#define SOC_SCHARGER_CNTL_enable_START    (3)
#define SOC_SCHARGER_CNTL_enable_END      (3)


/*****************************************************************************
 结构名    : SOC_SCHARGER_CMD_UNION
 结构说明  : CMD 寄存器结构定义。地址偏移量:0x24，初值:0x00，宽度:8
 寄存器说明: fcp 读写命令配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cmd : 8;  /* bit[0-7]: fcp 读写命令配置寄存器。 */
    } reg;
} SOC_SCHARGER_CMD_UNION;
#endif
#define SOC_SCHARGER_CMD_cmd_START  (0)
#define SOC_SCHARGER_CMD_cmd_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_ADDR_UNION
 结构说明  : ADDR 寄存器结构定义。地址偏移量:0x27，初值:0x00，宽度:8
 寄存器说明: fcp 读写地址配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  addr : 8;  /* bit[0-7]: fcp 读写地址配置寄存器。 */
    } reg;
} SOC_SCHARGER_ADDR_UNION;
#endif
#define SOC_SCHARGER_ADDR_addr_START  (0)
#define SOC_SCHARGER_ADDR_addr_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_DATA0_UNION
 结构说明  : DATA0 寄存器结构定义。地址偏移量:0x28，初值:0x00，宽度:8
 寄存器说明: fcp 写数据寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  data0 : 8;  /* bit[0-7]: fcp 写数据寄存器。 */
    } reg;
} SOC_SCHARGER_DATA0_UNION;
#endif
#define SOC_SCHARGER_DATA0_data0_START  (0)
#define SOC_SCHARGER_DATA0_data0_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_ISR1_UNION
 结构说明  : ISR1 寄存器结构定义。地址偏移量:0x39，初值:0x00，宽度:8
 寄存器说明: FCP 中断1寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reserved_0: 3;  /* bit[0-2]: 保留。 */
        unsigned char  crcpar   : 1;  /* bit[3]  : Slaver没有数据包返回中断；
                                                   0：无此中断；
                                                   1：有中断。 */
        unsigned char  nack     : 1;  /* bit[4]  : Slaver 返回NACK中断：
                                                   0：无此中断；
                                                   1：有中断。 */
        unsigned char  reserved_1: 1;  /* bit[5]  : 保留。 */
        unsigned char  ack      : 1;  /* bit[6]  : Slaver 返回ACK中断：
                                                   0：无此中断；
                                                   1：有中断。 */
        unsigned char  cmdcpl   : 1;  /* bit[7]  : FCP命令成功完成中断：
                                                   0：无此中断；
                                                   1：有中断。 */
    } reg;
} SOC_SCHARGER_ISR1_UNION;
#endif
#define SOC_SCHARGER_ISR1_crcpar_START    (3)
#define SOC_SCHARGER_ISR1_crcpar_END      (3)
#define SOC_SCHARGER_ISR1_nack_START      (4)
#define SOC_SCHARGER_ISR1_nack_END        (4)
#define SOC_SCHARGER_ISR1_ack_START       (6)
#define SOC_SCHARGER_ISR1_ack_END         (6)
#define SOC_SCHARGER_ISR1_cmdcpl_START    (7)
#define SOC_SCHARGER_ISR1_cmdcpl_END      (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_ISR2_UNION
 结构说明  : ISR2 寄存器结构定义。地址偏移量:0x3A，初值:0x00，宽度:8
 寄存器说明: FCP 中断2寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reserved_0: 1;  /* bit[0]  : 保留。 */
        unsigned char  protstat : 1;  /* bit[1]  : Slaver检测状态变化中断：
                                                   0：无此中断；
                                                   1：有中断。 */
        unsigned char  reserved_1: 1;  /* bit[2]  : 保留。 */
        unsigned char  parrx    : 1;  /* bit[3]  : Slaver返回数据parity校验错误中断：
                                                   0：无此中断；
                                                   1：有中断。 */
        unsigned char  crcrx    : 1;  /* bit[4]  : Slaver返回数据crc校验错误中断；
                                                   0：无此中断；
                                                   1：有中断。 */
        unsigned char  reserved_2: 3;  /* bit[5-7]: 保留。 */
    } reg;
} SOC_SCHARGER_ISR2_UNION;
#endif
#define SOC_SCHARGER_ISR2_protstat_START  (1)
#define SOC_SCHARGER_ISR2_protstat_END    (1)
#define SOC_SCHARGER_ISR2_parrx_START     (3)
#define SOC_SCHARGER_ISR2_parrx_END       (3)
#define SOC_SCHARGER_ISR2_crcrx_START     (4)
#define SOC_SCHARGER_ISR2_crcrx_END       (4)


/*****************************************************************************
 结构名    : SOC_SCHARGER_IMR1_UNION
 结构说明  : IMR1 寄存器结构定义。地址偏移量:0x3B，初值:0x00，宽度:8
 寄存器说明: FCP 中断屏蔽1寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reserved_0: 3;  /* bit[0-2]: 保留。 */
        unsigned char  crcpar_mk : 1;  /* bit[3]  : crcpar中断屏蔽寄存器：
                                                    0：不屏蔽；
                                                    1：屏蔽。 */
        unsigned char  nack_mk   : 1;  /* bit[4]  : nack中断屏蔽寄存器：
                                                    0：不屏蔽；
                                                    1：屏蔽。 */
        unsigned char  reserved_1: 1;  /* bit[5]  : 保留。 */
        unsigned char  ack_mk    : 1;  /* bit[6]  : ack中断屏蔽寄存器：
                                                    0：不屏蔽；
                                                    1：屏蔽。 */
        unsigned char  cmdcpl_mk : 1;  /* bit[7]  : cmdcpl中断屏蔽寄存器：
                                                    0：不屏蔽；
                                                    1：屏蔽。 */
    } reg;
} SOC_SCHARGER_IMR1_UNION;
#endif
#define SOC_SCHARGER_IMR1_crcpar_mk_START  (3)
#define SOC_SCHARGER_IMR1_crcpar_mk_END    (3)
#define SOC_SCHARGER_IMR1_nack_mk_START    (4)
#define SOC_SCHARGER_IMR1_nack_mk_END      (4)
#define SOC_SCHARGER_IMR1_ack_mk_START     (6)
#define SOC_SCHARGER_IMR1_ack_mk_END       (6)
#define SOC_SCHARGER_IMR1_cmdcpl_mk_START  (7)
#define SOC_SCHARGER_IMR1_cmdcpl_mk_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_IMR2_UNION
 结构说明  : IMR2 寄存器结构定义。地址偏移量:0x3C，初值:0x00，宽度:8
 寄存器说明: FCP 中断屏蔽2寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  reserved_0  : 1;  /* bit[0]  : 保留。 */
        unsigned char  protstat_mk : 1;  /* bit[1]  : protstat中断屏蔽寄存器：
                                                      0：不屏蔽；
                                                      1：屏蔽。 */
        unsigned char  reserved_1  : 1;  /* bit[2]  : 保留。 */
        unsigned char  parrx_mk    : 1;  /* bit[3]  : parrx中断屏蔽寄存器：
                                                      0：不屏蔽；
                                                      1：屏蔽。 */
        unsigned char  crcrx_mk    : 1;  /* bit[4]  : crcrx中断屏蔽寄存器：
                                                      0：不屏蔽；
                                                      1：屏蔽。 */
        unsigned char  reserved_2  : 3;  /* bit[5-7]: 保留。 */
    } reg;
} SOC_SCHARGER_IMR2_UNION;
#endif
#define SOC_SCHARGER_IMR2_protstat_mk_START  (1)
#define SOC_SCHARGER_IMR2_protstat_mk_END    (1)
#define SOC_SCHARGER_IMR2_parrx_mk_START     (3)
#define SOC_SCHARGER_IMR2_parrx_mk_END       (3)
#define SOC_SCHARGER_IMR2_crcrx_mk_START     (4)
#define SOC_SCHARGER_IMR2_crcrx_mk_END       (4)


/*****************************************************************************
 结构名    : SOC_SCHARGER_FCP_IRQ3_UNION
 结构说明  : FCP_IRQ3 寄存器结构定义。地址偏移量:0x3D，初值:0x00，宽度:8
 寄存器说明: FCP中断3寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  last_hand_fail_irq  : 1;  /* bit[0]: 数据包发送完后握手失败中断：
                                                            0：无此中断；
                                                            1：有中断。 */
        unsigned char  tail_hand_fail_irq  : 1;  /* bit[1]: Slaver 返回数据后第一次返回ping握手失败中断：
                                                            0：无此中断；
                                                            1：有中断。 */
        unsigned char  trans_hand_fail_irq : 1;  /* bit[2]: Master发送数据后握手失败中断：
                                                            0：无此中断；
                                                            1：有中断。 */
        unsigned char  init_hand_fail_irq  : 1;  /* bit[3]: 初始化握手失败中断：
                                                            0：无此中断；
                                                            1：有中断。 */
        unsigned char  rx_data_det_irq     : 1;  /* bit[4]: 等不到slaver返回的数据中断：
                                                            0：无此中断；
                                                            1：有中断。 */
        unsigned char  rx_head_det_irq     : 1;  /* bit[5]: 等不到slaver返回的数据包头中断：
                                                            0：无此中断；
                                                            1：有中断。 */
        unsigned char  cmd_err_irq         : 1;  /* bit[6]: SNDCMD不为读或者写中断：
                                                            0：无此中断；
                                                            1：有中断。 */
        unsigned char  reserved            : 1;  /* bit[7]:  */
    } reg;
} SOC_SCHARGER_FCP_IRQ3_UNION;
#endif
#define SOC_SCHARGER_FCP_IRQ3_last_hand_fail_irq_START   (0)
#define SOC_SCHARGER_FCP_IRQ3_last_hand_fail_irq_END     (0)
#define SOC_SCHARGER_FCP_IRQ3_tail_hand_fail_irq_START   (1)
#define SOC_SCHARGER_FCP_IRQ3_tail_hand_fail_irq_END     (1)
#define SOC_SCHARGER_FCP_IRQ3_trans_hand_fail_irq_START  (2)
#define SOC_SCHARGER_FCP_IRQ3_trans_hand_fail_irq_END    (2)
#define SOC_SCHARGER_FCP_IRQ3_init_hand_fail_irq_START   (3)
#define SOC_SCHARGER_FCP_IRQ3_init_hand_fail_irq_END     (3)
#define SOC_SCHARGER_FCP_IRQ3_rx_data_det_irq_START      (4)
#define SOC_SCHARGER_FCP_IRQ3_rx_data_det_irq_END        (4)
#define SOC_SCHARGER_FCP_IRQ3_rx_head_det_irq_START      (5)
#define SOC_SCHARGER_FCP_IRQ3_rx_head_det_irq_END        (5)
#define SOC_SCHARGER_FCP_IRQ3_cmd_err_irq_START          (6)
#define SOC_SCHARGER_FCP_IRQ3_cmd_err_irq_END            (6)


/*****************************************************************************
 结构名    : SOC_SCHARGER_FCP_IRQ4_UNION
 结构说明  : FCP_IRQ4 寄存器结构定义。地址偏移量:0x3E，初值:0x00，宽度:8
 寄存器说明: FCP中断4寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  last_hand_no_respond_irq   : 1;  /* bit[0]  : 数据包发送完后等不到slaver ping中断：
                                                                     0：无此中断；
                                                                     1：有中断。 */
        unsigned char  tail_hand_no_respond_irq   : 1;  /* bit[1]  : Slaver 返回数据后第一次返回ping握手等不到slaver ping中断：
                                                                     0：无此中断；
                                                                     1：有中断。 */
        unsigned char  trans_hand_no_respond_irq  : 1;  /* bit[2]  : Master发送数据后握手等不到slaver ping中断：
                                                                     0：无此中断；
                                                                     1：有中断。 */
        unsigned char  init_hand_no_respond_irq   : 1;  /* bit[3]  : 初始化slaver没有ping返回中断：
                                                                     0：无此中断；
                                                                     1：有中断。 */
        unsigned char  enable_hand_fail_irq       : 1;  /* bit[4]  : 通过enable发送master ping后，握手失败（握手失败会自动重复握手15次）：
                                                                     0：无此中断；
                                                                     1：有中断。 */
        unsigned char  enable_hand_no_respond_irq : 1;  /* bit[5]  : 通过enable发送master ping后，slaver没有响应中断（握手失败会自动重复握手15次）：
                                                                     0：无此中断；
                                                                     1：有中断。 */
        unsigned char  reserved                   : 2;  /* bit[6-7]: 保留。 */
    } reg;
} SOC_SCHARGER_FCP_IRQ4_UNION;
#endif
#define SOC_SCHARGER_FCP_IRQ4_last_hand_no_respond_irq_START    (0)
#define SOC_SCHARGER_FCP_IRQ4_last_hand_no_respond_irq_END      (0)
#define SOC_SCHARGER_FCP_IRQ4_tail_hand_no_respond_irq_START    (1)
#define SOC_SCHARGER_FCP_IRQ4_tail_hand_no_respond_irq_END      (1)
#define SOC_SCHARGER_FCP_IRQ4_trans_hand_no_respond_irq_START   (2)
#define SOC_SCHARGER_FCP_IRQ4_trans_hand_no_respond_irq_END     (2)
#define SOC_SCHARGER_FCP_IRQ4_init_hand_no_respond_irq_START    (3)
#define SOC_SCHARGER_FCP_IRQ4_init_hand_no_respond_irq_END      (3)
#define SOC_SCHARGER_FCP_IRQ4_enable_hand_fail_irq_START        (4)
#define SOC_SCHARGER_FCP_IRQ4_enable_hand_fail_irq_END          (4)
#define SOC_SCHARGER_FCP_IRQ4_enable_hand_no_respond_irq_START  (5)
#define SOC_SCHARGER_FCP_IRQ4_enable_hand_no_respond_irq_END    (5)


/*****************************************************************************
 结构名    : SOC_SCHARGER_FCP_IRQ5_UNION
 结构说明  : FCP_IRQ5 寄存器结构定义。地址偏移量:0x3F，初值:0x00，宽度:8
 寄存器说明: FCP中断5寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  fcp_set_d60m_r : 1;  /* bit[0]  : 支持高压快充的Adapter中断（fcp_set滤波60ms，检测上升沿，上报中断）：
                                                         0：无此中断；
                                                         1：有中断。
                                                         注：在fcp_cmp_en=0时，模拟送出的fcp_set信号是0的。 */
        unsigned char  fcp_en_det_int : 1;  /* bit[1]  : fcp_det_en&amp;fcp_cmp_en信号为高电平后2s内，没有收到fcp_set上升沿中断：
                                                         0：无此中断；
                                                         1：有中断。 */
        unsigned char  reserved       : 6;  /* bit[2-7]: 保留。 */
    } reg;
} SOC_SCHARGER_FCP_IRQ5_UNION;
#endif
#define SOC_SCHARGER_FCP_IRQ5_fcp_set_d60m_r_START  (0)
#define SOC_SCHARGER_FCP_IRQ5_fcp_set_d60m_r_END    (0)
#define SOC_SCHARGER_FCP_IRQ5_fcp_en_det_int_START  (1)
#define SOC_SCHARGER_FCP_IRQ5_fcp_en_det_int_END    (1)


/*****************************************************************************
 结构名    : SOC_SCHARGER_FCP_IRQ3_MASK_UNION
 结构说明  : FCP_IRQ3_MASK 寄存器结构定义。地址偏移量:0x40，初值:0x00，宽度:8
 寄存器说明: FCP中断屏蔽3寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  last_hand_fail_irq_mk  : 1;  /* bit[0]: 0：使能该中断；
                                                               1：屏蔽该中断。 */
        unsigned char  tail_hand_fail_irq_mk  : 1;  /* bit[1]: 0：使能该中断；
                                                               1：屏蔽该中断。 */
        unsigned char  trans_hand_fail_irq_mk : 1;  /* bit[2]: 0：使能该中断；
                                                               1：屏蔽该中断。 */
        unsigned char  init_hand_fail_irq_mk  : 1;  /* bit[3]: 0：使能该中断；
                                                               1：屏蔽该中断。 */
        unsigned char  rx_data_det_irq_mk     : 1;  /* bit[4]: 0：使能该中断；
                                                               1：屏蔽该中断。 */
        unsigned char  rx_head_det_irq_mk     : 1;  /* bit[5]: 0：使能该中断；
                                                               1：屏蔽该中断。 */
        unsigned char  cmd_err_irq_mk         : 1;  /* bit[6]: 0：使能该中断；
                                                               1：屏蔽该中断。 */
        unsigned char  reserved               : 1;  /* bit[7]: 保留。 */
    } reg;
} SOC_SCHARGER_FCP_IRQ3_MASK_UNION;
#endif
#define SOC_SCHARGER_FCP_IRQ3_MASK_last_hand_fail_irq_mk_START   (0)
#define SOC_SCHARGER_FCP_IRQ3_MASK_last_hand_fail_irq_mk_END     (0)
#define SOC_SCHARGER_FCP_IRQ3_MASK_tail_hand_fail_irq_mk_START   (1)
#define SOC_SCHARGER_FCP_IRQ3_MASK_tail_hand_fail_irq_mk_END     (1)
#define SOC_SCHARGER_FCP_IRQ3_MASK_trans_hand_fail_irq_mk_START  (2)
#define SOC_SCHARGER_FCP_IRQ3_MASK_trans_hand_fail_irq_mk_END    (2)
#define SOC_SCHARGER_FCP_IRQ3_MASK_init_hand_fail_irq_mk_START   (3)
#define SOC_SCHARGER_FCP_IRQ3_MASK_init_hand_fail_irq_mk_END     (3)
#define SOC_SCHARGER_FCP_IRQ3_MASK_rx_data_det_irq_mk_START      (4)
#define SOC_SCHARGER_FCP_IRQ3_MASK_rx_data_det_irq_mk_END        (4)
#define SOC_SCHARGER_FCP_IRQ3_MASK_rx_head_det_irq_mk_START      (5)
#define SOC_SCHARGER_FCP_IRQ3_MASK_rx_head_det_irq_mk_END        (5)
#define SOC_SCHARGER_FCP_IRQ3_MASK_cmd_err_irq_mk_START          (6)
#define SOC_SCHARGER_FCP_IRQ3_MASK_cmd_err_irq_mk_END            (6)


/*****************************************************************************
 结构名    : SOC_SCHARGER_FCP_IRQ4_MASK_UNION
 结构说明  : FCP_IRQ4_MASK 寄存器结构定义。地址偏移量:0x41，初值:0x00，宽度:8
 寄存器说明: FCP中断屏蔽4寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  last_hand_no_respond_irq_mk   : 1;  /* bit[0]  : 0：使能该中断；
                                                                        1：屏蔽该中断。 */
        unsigned char  tail_hand_no_respond_irq_mk   : 1;  /* bit[1]  : 0：使能该中断；
                                                                        1：屏蔽该中断。 */
        unsigned char  trans_hand_no_respond_irq_mk  : 1;  /* bit[2]  : 0：使能该中断；
                                                                        1：屏蔽该中断。 */
        unsigned char  init_hand_no_respond_irq_mk   : 1;  /* bit[3]  : 0：使能该中断；
                                                                        1：屏蔽该中断。 */
        unsigned char  enable_hand_fail_irq_mk       : 1;  /* bit[4]  : 0：使能该中断；
                                                                        1：屏蔽该中断。 */
        unsigned char  enable_hand_no_respond_irq_mk : 1;  /* bit[5]  : 0：使能该中断；
                                                                        1：屏蔽该中断。 */
        unsigned char  reserved                      : 2;  /* bit[6-7]: 保留。 */
    } reg;
} SOC_SCHARGER_FCP_IRQ4_MASK_UNION;
#endif
#define SOC_SCHARGER_FCP_IRQ4_MASK_last_hand_no_respond_irq_mk_START    (0)
#define SOC_SCHARGER_FCP_IRQ4_MASK_last_hand_no_respond_irq_mk_END      (0)
#define SOC_SCHARGER_FCP_IRQ4_MASK_tail_hand_no_respond_irq_mk_START    (1)
#define SOC_SCHARGER_FCP_IRQ4_MASK_tail_hand_no_respond_irq_mk_END      (1)
#define SOC_SCHARGER_FCP_IRQ4_MASK_trans_hand_no_respond_irq_mk_START   (2)
#define SOC_SCHARGER_FCP_IRQ4_MASK_trans_hand_no_respond_irq_mk_END     (2)
#define SOC_SCHARGER_FCP_IRQ4_MASK_init_hand_no_respond_irq_mk_START    (3)
#define SOC_SCHARGER_FCP_IRQ4_MASK_init_hand_no_respond_irq_mk_END      (3)
#define SOC_SCHARGER_FCP_IRQ4_MASK_enable_hand_fail_irq_mk_START        (4)
#define SOC_SCHARGER_FCP_IRQ4_MASK_enable_hand_fail_irq_mk_END          (4)
#define SOC_SCHARGER_FCP_IRQ4_MASK_enable_hand_no_respond_irq_mk_START  (5)
#define SOC_SCHARGER_FCP_IRQ4_MASK_enable_hand_no_respond_irq_mk_END    (5)


/*****************************************************************************
 结构名    : SOC_SCHARGER_FCP_IRQ5_MASK_UNION
 结构说明  : FCP_IRQ5_MASK 寄存器结构定义。地址偏移量:0x42，初值:0x00，宽度:8
 寄存器说明: FCP中断屏蔽5寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  fcp_set_d60m_r_mk : 1;  /* bit[0]  : 0：使能该中断；
                                                            1：屏蔽该中断。 */
        unsigned char  fcp_en_det_int_mk : 1;  /* bit[1]  : 0：使能该中断；
                                                            1：屏蔽该中断。 */
        unsigned char  reserved          : 6;  /* bit[2-7]: 保留。 */
    } reg;
} SOC_SCHARGER_FCP_IRQ5_MASK_UNION;
#endif
#define SOC_SCHARGER_FCP_IRQ5_MASK_fcp_set_d60m_r_mk_START  (0)
#define SOC_SCHARGER_FCP_IRQ5_MASK_fcp_set_d60m_r_mk_END    (0)
#define SOC_SCHARGER_FCP_IRQ5_MASK_fcp_en_det_int_mk_START  (1)
#define SOC_SCHARGER_FCP_IRQ5_MASK_fcp_en_det_int_mk_END    (1)


/*****************************************************************************
 结构名    : SOC_SCHARGER_FCP_CTRL_UNION
 结构说明  : FCP_CTRL 寄存器结构定义。地址偏移量:0x43，初值:0x00，宽度:8
 寄存器说明: 高压块充控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  fcp_clk_test : 1;  /* bit[0]  : 高压快充的测试模式选择：
                                                       0：正常工作模式；
                                                       1：测试模式。 */
        unsigned char  fcp_mode     : 1;  /* bit[1]  : 高压快充模式选择：
                                                       0：模式1；
                                                       1：模式2； */
        unsigned char  fcp_cmp_en   : 1;  /* bit[2]  : 高压快充协议检测比较器使能：
                                                       0：关闭检测比较器；
                                                       1：检测比较器。
                                                       （注：看门狗发生异常后该寄存器会被置0。） */
        unsigned char  fcp_det_en   : 1;  /* bit[3]  : 高压快充协议检测使能：
                                                       0：关闭快充协议检测功能；
                                                       1：开启快充协议检测功能。
                                                       （注：看门狗发生异常后该寄存器会被置0。） */
        unsigned char  reserved     : 4;  /* bit[4-7]: 保留。 */
    } reg;
} SOC_SCHARGER_FCP_CTRL_UNION;
#endif
#define SOC_SCHARGER_FCP_CTRL_fcp_clk_test_START  (0)
#define SOC_SCHARGER_FCP_CTRL_fcp_clk_test_END    (0)
#define SOC_SCHARGER_FCP_CTRL_fcp_mode_START      (1)
#define SOC_SCHARGER_FCP_CTRL_fcp_mode_END        (1)
#define SOC_SCHARGER_FCP_CTRL_fcp_cmp_en_START    (2)
#define SOC_SCHARGER_FCP_CTRL_fcp_cmp_en_END      (2)
#define SOC_SCHARGER_FCP_CTRL_fcp_det_en_START    (3)
#define SOC_SCHARGER_FCP_CTRL_fcp_det_en_END      (3)


/*****************************************************************************
 结构名    : SOC_SCHARGER_FCP_MODE2_SET_UNION
 结构说明  : FCP_MODE2_SET 寄存器结构定义。地址偏移量:0x44，初值:0x00，宽度:8
 寄存器说明: 高压快充协议模式2档位控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  fcp_mod2_set : 2;  /* bit[0-1]: 高压快充协议模式2档位控制：
                                                       00：（0.6V,0V)
                                                       01: (3.3V,0.6V)
                                                       10: (0.6V,0.6V)
                                                       11: (3.3V,3.3V) */
        unsigned char  reserved     : 6;  /* bit[2-7]: 保留。 */
    } reg;
} SOC_SCHARGER_FCP_MODE2_SET_UNION;
#endif
#define SOC_SCHARGER_FCP_MODE2_SET_fcp_mod2_set_START  (0)
#define SOC_SCHARGER_FCP_MODE2_SET_fcp_mod2_set_END    (1)


/*****************************************************************************
 结构名    : SOC_SCHARGER_FCP_ADAP_CTRL_UNION
 结构说明  : FCP_ADAP_CTRL 寄存器结构定义。地址偏移量:0x45，初值:0x00，宽度:8
 寄存器说明: 高压块充Adapter控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  fcp_set_d60m_r : 1;  /* bit[0]  : 高压快充的Adapter判断（fcp_set_d60m_r中断状态寄存器）：
                                                         0：不支持高压快充的Adapter；
                                                         1：支持高压快充的Adapter。 */
        unsigned char  reserved       : 7;  /* bit[1-7]: 保留。 */
    } reg;
} SOC_SCHARGER_FCP_ADAP_CTRL_UNION;
#endif
#define SOC_SCHARGER_FCP_ADAP_CTRL_fcp_set_d60m_r_START  (0)
#define SOC_SCHARGER_FCP_ADAP_CTRL_fcp_set_d60m_r_END    (0)


/*****************************************************************************
 结构名    : SOC_SCHARGER_MSTATE_UNION
 结构说明  : MSTATE 寄存器结构定义。地址偏移量:0x46，初值:0x00，宽度:8
 寄存器说明: 状态机状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  mstate   : 4;  /* bit[0-3]: FCP状态机状态寄存器。 */
        unsigned char  reserved : 4;  /* bit[4-7]: 保留。 */
    } reg;
} SOC_SCHARGER_MSTATE_UNION;
#endif
#define SOC_SCHARGER_MSTATE_mstate_START    (0)
#define SOC_SCHARGER_MSTATE_mstate_END      (3)


/*****************************************************************************
 结构名    : SOC_SCHARGER_FCP_RDATA_UNION
 结构说明  : FCP_RDATA 寄存器结构定义。地址偏移量:0x47，初值:0x00，宽度:8
 寄存器说明: slave返回的数据。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  fcp_rdata : 8;  /* bit[0-7]: I2C通过master读回的slaver的寄存器值。 */
    } reg;
} SOC_SCHARGER_FCP_RDATA_UNION;
#endif
#define SOC_SCHARGER_FCP_RDATA_fcp_rdata_START  (0)
#define SOC_SCHARGER_FCP_RDATA_fcp_rdata_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_RDATA_READY_UNION
 结构说明  : RDATA_READY 寄存器结构定义。地址偏移量:0x48，初值:0x00，宽度:8
 寄存器说明: slave返回数据采集好指示信号。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  fcp_rdata_ready : 1;  /* bit[0]  : I2C通过master读回的slaver的寄存器值准备好指示信号。 */
        unsigned char  reserved        : 7;  /* bit[1-7]: 保留。 */
    } reg;
} SOC_SCHARGER_RDATA_READY_UNION;
#endif
#define SOC_SCHARGER_RDATA_READY_fcp_rdata_ready_START  (0)
#define SOC_SCHARGER_RDATA_READY_fcp_rdata_ready_END    (0)


/*****************************************************************************
 结构名    : SOC_SCHARGER_CRC_ENABLE_UNION
 结构说明  : CRC_ENABLE 寄存器结构定义。地址偏移量:0x49，初值:0x01，宽度:8
 寄存器说明: crc 使能控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  crc_en   : 1;  /* bit[0]  : crc 使能控制寄存器：
                                                   0：不使能；
                                                   1：使能。 */
        unsigned char  reserved : 7;  /* bit[1-7]: 保留。 */
    } reg;
} SOC_SCHARGER_CRC_ENABLE_UNION;
#endif
#define SOC_SCHARGER_CRC_ENABLE_crc_en_START    (0)
#define SOC_SCHARGER_CRC_ENABLE_crc_en_END      (0)


/*****************************************************************************
 结构名    : SOC_SCHARGER_CRC_START_VALUE_UNION
 结构说明  : CRC_START_VALUE 寄存器结构定义。地址偏移量:0x4A，初值:0x00，宽度:8
 寄存器说明: crc 初始值。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  crc_start_val : 8;  /* bit[0-7]: crc 初始值。 */
    } reg;
} SOC_SCHARGER_CRC_START_VALUE_UNION;
#endif
#define SOC_SCHARGER_CRC_START_VALUE_crc_start_val_START  (0)
#define SOC_SCHARGER_CRC_START_VALUE_crc_start_val_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_SAMPLE_CNT_ADJ_UNION
 结构说明  : SAMPLE_CNT_ADJ 寄存器结构定义。地址偏移量:0x4B，初值:0x00，宽度:8
 寄存器说明: 采样点调整寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  sample_cnt_adjust : 5;  /* bit[0-4]: 采样slaver数据周期手动调节寄存器，为0时采样周期为计算slaver ping长度得出，当配置其他值时，采样周期就为配置值。
                                                            注：可配置的最大值为28（5'b11100） */
        unsigned char  reserved          : 3;  /* bit[5-7]: 保留。 */
    } reg;
} SOC_SCHARGER_SAMPLE_CNT_ADJ_UNION;
#endif
#define SOC_SCHARGER_SAMPLE_CNT_ADJ_sample_cnt_adjust_START  (0)
#define SOC_SCHARGER_SAMPLE_CNT_ADJ_sample_cnt_adjust_END    (4)


/*****************************************************************************
 结构名    : SOC_SCHARGER_RX_PING_WIDTH_MIN_H_UNION
 结构说明  : RX_PING_WIDTH_MIN_H 寄存器结构定义。地址偏移量:0x4C，初值:0x01，宽度:8
 寄存器说明: RX ping 最小长度高位。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rx_ping_width_min_h : 1;  /* bit[0]  : Slaver ping最短有效长度高位。 */
        unsigned char  reserved            : 7;  /* bit[1-7]: 保留。 */
    } reg;
} SOC_SCHARGER_RX_PING_WIDTH_MIN_H_UNION;
#endif
#define SOC_SCHARGER_RX_PING_WIDTH_MIN_H_rx_ping_width_min_h_START  (0)
#define SOC_SCHARGER_RX_PING_WIDTH_MIN_H_rx_ping_width_min_h_END    (0)


/*****************************************************************************
 结构名    : SOC_SCHARGER_RX_PING_WIDTH_MIN_L_UNION
 结构说明  : RX_PING_WIDTH_MIN_L 寄存器结构定义。地址偏移量:0x4D，初值:0x04，宽度:8
 寄存器说明: RX ping 最小长度低8位
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rx_ping_width_min_l : 8;  /* bit[0-7]: Slaver ping最短有效长度低8位。 */
    } reg;
} SOC_SCHARGER_RX_PING_WIDTH_MIN_L_UNION;
#endif
#define SOC_SCHARGER_RX_PING_WIDTH_MIN_L_rx_ping_width_min_l_START  (0)
#define SOC_SCHARGER_RX_PING_WIDTH_MIN_L_rx_ping_width_min_l_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_RX_PING_WIDTH_MAX_H_UNION
 结构说明  : RX_PING_WIDTH_MAX_H 寄存器结构定义。地址偏移量:0x4E，初值:0x01，宽度:8
 寄存器说明: RX ping 最大长度高位
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rx_ping_width_max_h : 1;  /* bit[0]  : Slaver ping最长有效长度高位。 */
        unsigned char  reserved            : 7;  /* bit[1-7]: 保留。 */
    } reg;
} SOC_SCHARGER_RX_PING_WIDTH_MAX_H_UNION;
#endif
#define SOC_SCHARGER_RX_PING_WIDTH_MAX_H_rx_ping_width_max_h_START  (0)
#define SOC_SCHARGER_RX_PING_WIDTH_MAX_H_rx_ping_width_max_h_END    (0)


/*****************************************************************************
 结构名    : SOC_SCHARGER_RX_PING_WIDTH_MAX_L_UNION
 结构说明  : RX_PING_WIDTH_MAX_L 寄存器结构定义。地址偏移量:0x4F，初值:0x8B，宽度:8
 寄存器说明: RX ping 最大长度低8位。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  rx_ping_width_max_l : 8;  /* bit[0-7]: Slaver ping最长有效长度低8位。 */
    } reg;
} SOC_SCHARGER_RX_PING_WIDTH_MAX_L_UNION;
#endif
#define SOC_SCHARGER_RX_PING_WIDTH_MAX_L_rx_ping_width_max_l_START  (0)
#define SOC_SCHARGER_RX_PING_WIDTH_MAX_L_rx_ping_width_max_l_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_DATA_WAIT_TIME_UNION
 结构说明  : DATA_WAIT_TIME 寄存器结构定义。地址偏移量:0x50，初值:0x64，宽度:8
 寄存器说明: 数据等待时间寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  data_wait_time : 7;  /* bit[0-6]: 数据包等待配置时间寄存器，实际周期为配置值*4 cycle。 */
        unsigned char  reserved       : 1;  /* bit[7]  : 保留。 */
    } reg;
} SOC_SCHARGER_DATA_WAIT_TIME_UNION;
#endif
#define SOC_SCHARGER_DATA_WAIT_TIME_data_wait_time_START  (0)
#define SOC_SCHARGER_DATA_WAIT_TIME_data_wait_time_END    (6)


/*****************************************************************************
 结构名    : SOC_SCHARGER_RETRY_CNT_UNION
 结构说明  : RETRY_CNT 寄存器结构定义。地址偏移量:0x51，初值:0x03，宽度:8
 寄存器说明: 数据重新发送次数。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  cmd_retry_config : 4;  /* bit[0-3]: 数据包出错，master retry次数。 */
        unsigned char  reserved         : 4;  /* bit[4-7]: 保留。 */
    } reg;
} SOC_SCHARGER_RETRY_CNT_UNION;
#endif
#define SOC_SCHARGER_RETRY_CNT_cmd_retry_config_START  (0)
#define SOC_SCHARGER_RETRY_CNT_cmd_retry_config_END    (3)


/*****************************************************************************
 结构名    : SOC_SCHARGER_FCP_SOFT_RST_CTRL_UNION
 结构说明  : FCP_SOFT_RST_CTRL 寄存器结构定义。地址偏移量:0x52，初值:0x00，宽度:8
 寄存器说明: FCP软复位控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  fcp_soft_rst_cfg : 8;  /* bit[0-7]: FCP模块软复位信号，写入0x04进行复位，自动清零。 */
    } reg;
} SOC_SCHARGER_FCP_SOFT_RST_CTRL_UNION;
#endif
#define SOC_SCHARGER_FCP_SOFT_RST_CTRL_fcp_soft_rst_cfg_START  (0)
#define SOC_SCHARGER_FCP_SOFT_RST_CTRL_fcp_soft_rst_cfg_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_FCP_RO_RESERVE_UNION
 结构说明  : FCP_RO_RESERVE 寄存器结构定义。地址偏移量:0x53，初值:0x00，宽度:8
 寄存器说明: fcp只读预留寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  fcp_ro_reserve : 8;  /* bit[0-7]: fcp只读预留寄存器。 */
    } reg;
} SOC_SCHARGER_FCP_RO_RESERVE_UNION;
#endif
#define SOC_SCHARGER_FCP_RO_RESERVE_fcp_ro_reserve_START  (0)
#define SOC_SCHARGER_FCP_RO_RESERVE_fcp_ro_reserve_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_FCP_DEBUG_REG0_UNION
 结构说明  : FCP_DEBUG_REG0 寄存器结构定义。地址偏移量:0x54，初值:0x00，宽度:8
 寄存器说明: FCP debug寄存器0。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  slv_crc_err         : 1;  /* bit[0]  : Slaver数据crc校验状态。 */
        unsigned char  resp_ack_parity_err : 1;  /* bit[1]  : Slaver返回的ACK/NACK数据的partity校验。 */
        unsigned char  rdata_parity_err    : 1;  /* bit[2]  : Slaver返回的读数据的parity校验。 */
        unsigned char  slv_crc_parity_err  : 1;  /* bit[3]  : Slaver返回的CRC数据的parity校验。 */
        unsigned char  reserved            : 4;  /* bit[4-7]: 保留。 */
    } reg;
} SOC_SCHARGER_FCP_DEBUG_REG0_UNION;
#endif
#define SOC_SCHARGER_FCP_DEBUG_REG0_slv_crc_err_START          (0)
#define SOC_SCHARGER_FCP_DEBUG_REG0_slv_crc_err_END            (0)
#define SOC_SCHARGER_FCP_DEBUG_REG0_resp_ack_parity_err_START  (1)
#define SOC_SCHARGER_FCP_DEBUG_REG0_resp_ack_parity_err_END    (1)
#define SOC_SCHARGER_FCP_DEBUG_REG0_rdata_parity_err_START     (2)
#define SOC_SCHARGER_FCP_DEBUG_REG0_rdata_parity_err_END       (2)
#define SOC_SCHARGER_FCP_DEBUG_REG0_slv_crc_parity_err_START   (3)
#define SOC_SCHARGER_FCP_DEBUG_REG0_slv_crc_parity_err_END     (3)


/*****************************************************************************
 结构名    : SOC_SCHARGER_FCP_DEBUG_REG1_UNION
 结构说明  : FCP_DEBUG_REG1 寄存器结构定义。地址偏移量:0x55，初值:0x00，宽度:8
 寄存器说明: FCP debug寄存器1。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  resp_ack : 8;  /* bit[0-7]: FCP debug寄存器1，Slaver返回的ACK/NAC数据。 */
    } reg;
} SOC_SCHARGER_FCP_DEBUG_REG1_UNION;
#endif
#define SOC_SCHARGER_FCP_DEBUG_REG1_resp_ack_START  (0)
#define SOC_SCHARGER_FCP_DEBUG_REG1_resp_ack_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_FCP_DEBUG_REG2_UNION
 结构说明  : FCP_DEBUG_REG2 寄存器结构定义。地址偏移量:0x56，初值:0x00，宽度:8
 寄存器说明: FCP debug寄存器2。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  slv_crc : 8;  /* bit[0-7]: FCP debug寄存器2，Slaver返回的CRC数据。 */
    } reg;
} SOC_SCHARGER_FCP_DEBUG_REG2_UNION;
#endif
#define SOC_SCHARGER_FCP_DEBUG_REG2_slv_crc_START  (0)
#define SOC_SCHARGER_FCP_DEBUG_REG2_slv_crc_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_BUCK_REG0_UNION
 结构说明  : BUCK_REG0 寄存器结构定义。地址偏移量:0x60，初值:0x0A，宽度:8
 寄存器说明: BUCK_REG0调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_scp_vset : 2;  /* bit[0-1]: buck scp档位设置：
                                                        00：1V；
                                                        01：1.4V；
                                                        10：1.8V；
                                                        11：2.2V。 */
        unsigned char  buck_ilimit   : 5;  /* bit[2-6]: buck平均限流环设定电流：
                                                        00000：100mA；
                                                        00001：150mA；
                                                        00010：500mA；
                                                        00011：900mA；
                                                        00100：1A；
                                                        00101：1.2A；
                                                        00110：1.3A；
                                                        00111：1.4A；
                                                        01000：1.5A；
                                                        01001：1.6A；
                                                        01010：1.7A；
                                                        01011：1.8A；
                                                        01100：1.9A；
                                                        01101：2A；
                                                        01110：2.1A；
                                                        01111：2.2A；
                                                        10000：2.4A；
                                                        10001：2.6A；
                                                        10010：2.8A；
                                                        10011：3A；
                                                        10100：3.2A；
                                                        10101~11111:3.2A。 */
        unsigned char  reserved      : 1;  /* bit[7]  : 保留。 */
    } reg;
} SOC_SCHARGER_BUCK_REG0_UNION;
#endif
#define SOC_SCHARGER_BUCK_REG0_buck_scp_vset_START  (0)
#define SOC_SCHARGER_BUCK_REG0_buck_scp_vset_END    (1)
#define SOC_SCHARGER_BUCK_REG0_buck_ilimit_START    (2)
#define SOC_SCHARGER_BUCK_REG0_buck_ilimit_END      (6)


/*****************************************************************************
 结构名    : SOC_SCHARGER_BUCK_REG1_UNION
 结构说明  : BUCK_REG1 寄存器结构定义。地址偏移量:0x61，初值:0x00，宽度:8
 寄存器说明: BUCK_REG1调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_ocp_en_n : 1;  /* bit[0]  : 9/12V关闭OCP功能：
                                                        0: 不关闭；
                                                        1: 关闭。 */
        unsigned char  buck_pfm_en   : 1;  /* bit[1]  : pfm模式使能控制：
                                                        0：不使能；
                                                        1：使能。 */
        unsigned char  buck_scp_dis  : 1;  /* bit[2]  : buck scp使能与屏蔽：
                                                        0：不屏蔽；
                                                        1：屏蔽。 */
        unsigned char  reserved      : 5;  /* bit[3-7]: 保留。 */
    } reg;
} SOC_SCHARGER_BUCK_REG1_UNION;
#endif
#define SOC_SCHARGER_BUCK_REG1_buck_ocp_en_n_START  (0)
#define SOC_SCHARGER_BUCK_REG1_buck_ocp_en_n_END    (0)
#define SOC_SCHARGER_BUCK_REG1_buck_pfm_en_START    (1)
#define SOC_SCHARGER_BUCK_REG1_buck_pfm_en_END      (1)
#define SOC_SCHARGER_BUCK_REG1_buck_scp_dis_START   (2)
#define SOC_SCHARGER_BUCK_REG1_buck_scp_dis_END     (2)


/*****************************************************************************
 结构名    : SOC_SCHARGER_BUCK_REG2_UNION
 结构说明  : BUCK_REG2 寄存器结构定义。地址偏移量:0x62，初值:0x2C，宽度:8
 寄存器说明: BUCK_REG2调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_ocp_sel    : 2;  /* bit[0-1]: 12V输入时OCP点是否需在9V基础上加500mA，默认为0增加500mA，1表示不增加。 */
        unsigned char  buck_dpm_sel    : 3;  /* bit[2-4]: DPM输入电压设定：
                                                          000：82.5%；
                                                          001：85%；
                                                          010：87.5%；
                                                          011：90%；
                                                          100：92.5%；
                                                          101：95%。 */
        unsigned char  buck_sysmin_sel : 2;  /* bit[5-6]: Vsys最小输出电压选择：
                                                          00：3.4V；
                                                          01：3.5V；
                                                          10：3.6V；
                                                          11：3.7V。 */
        unsigned char  reserved        : 1;  /* bit[7]  : 保留。 */
    } reg;
} SOC_SCHARGER_BUCK_REG2_UNION;
#endif
#define SOC_SCHARGER_BUCK_REG2_buck_ocp_sel_START     (0)
#define SOC_SCHARGER_BUCK_REG2_buck_ocp_sel_END       (1)
#define SOC_SCHARGER_BUCK_REG2_buck_dpm_sel_START     (2)
#define SOC_SCHARGER_BUCK_REG2_buck_dpm_sel_END       (4)
#define SOC_SCHARGER_BUCK_REG2_buck_sysmin_sel_START  (5)
#define SOC_SCHARGER_BUCK_REG2_buck_sysmin_sel_END    (6)


/*****************************************************************************
 结构名    : SOC_SCHARGER_BUCK_REG3_UNION
 结构说明  : BUCK_REG3 寄存器结构定义。地址偏移量:0x63，初值:0x00，宽度:8
 寄存器说明: BUCK_REG3调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_gap      : 3;  /* bit[0-2]: buck gap电压修调寄存器调节：
                                                        000：0；
                                                        001：-30mV；
                                                        010：-60mV；
                                                        011：-90mV；
                                                        100：0mV；
                                                        101：+30mV；
                                                        110：+60mV；
                                                        111：+90mV。 */
        unsigned char  buck_ilimit_k : 5;  /* bit[3-7]: buck限流比例调节：
                                                        00000：0；
                                                        00001：+2.5%；
                                                        00010：+5%；
                                                        00011：+7.5%；
                                                        00100：+10%；
                                                        00101：+12.5%；
                                                        00110：+15%；
                                                        00111：+17.5%；
                                                        01000：+20%；
                                                        01001：+22.5%；
                                                        01010：+25%；
                                                        01011：+27.5%；
                                                        01100：+30%；
                                                        01101：+32.5%；
                                                        01110：+35%；
                                                        01111：+37.5%；
                                                        10000：0；
                                                        10001：-2.5%；
                                                        10010：-5%；
                                                        10011：-7.5%；
                                                        10100：-10%；
                                                        10101：-12.5%；
                                                        10110：-15%；
                                                        10111：-17.5%；
                                                        11000：-20%；
                                                        11001：-22.5%；
                                                        11010：-25%；
                                                        11011：-27.5%；
                                                        11100：-30%；
                                                        11101：-32.5%；
                                                        11110：-35%；
                                                        11111：-37.5%。 */
    } reg;
} SOC_SCHARGER_BUCK_REG3_UNION;
#endif
#define SOC_SCHARGER_BUCK_REG3_buck_gap_START       (0)
#define SOC_SCHARGER_BUCK_REG3_buck_gap_END         (2)
#define SOC_SCHARGER_BUCK_REG3_buck_ilimit_k_START  (3)
#define SOC_SCHARGER_BUCK_REG3_buck_ilimit_k_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_BUCK_REG4_UNION
 结构说明  : BUCK_REG4 寄存器结构定义。地址偏移量:0x64，初值:0x40，宽度:8
 寄存器说明: BUCK_REG4调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_osc_otp_reg : 3;  /* bit[0-2]: buck osc trim的等效寄存器。 */
        unsigned char  buck_osc_frq     : 4;  /* bit[3-6]: osc振荡器频率调节：
                                                           0000：0.7M；
                                                           1111：3M。 */
        unsigned char  reserved         : 1;  /* bit[7]  : 保留。 */
    } reg;
} SOC_SCHARGER_BUCK_REG4_UNION;
#endif
#define SOC_SCHARGER_BUCK_REG4_buck_osc_otp_reg_START  (0)
#define SOC_SCHARGER_BUCK_REG4_buck_osc_otp_reg_END    (2)
#define SOC_SCHARGER_BUCK_REG4_buck_osc_frq_START      (3)
#define SOC_SCHARGER_BUCK_REG4_buck_osc_frq_END        (6)


/*****************************************************************************
 结构名    : SOC_SCHARGER_BUCK_REG5_UNION
 结构说明  : BUCK_REG5 寄存器结构定义。地址偏移量:0x65，初值:0x01，宽度:8
 寄存器说明: BUCK_REG5调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_fullduty_en   : 1;  /* bit[0]  : buck发生直通时处理方法：
                                                             0：不处理；
                                                             1：数周期内强制off一次。 */
        unsigned char  buck_block_ctrl    : 3;  /* bit[1-3]: 防倒流管控制 */
        unsigned char  buck_saw_peak_adj  : 2;  /* bit[4-5]: saw峰值调节寄存器 */
        unsigned char  buck_saw_vally_adj : 1;  /* bit[6]  : saw谷值调节寄存器 */
        unsigned char  buck_syn_en        : 1;  /* bit[7]  : 两项buck是否错相：
                                                             0：错相；
                                                             1：不错相。 */
    } reg;
} SOC_SCHARGER_BUCK_REG5_UNION;
#endif
#define SOC_SCHARGER_BUCK_REG5_buck_fullduty_en_START    (0)
#define SOC_SCHARGER_BUCK_REG5_buck_fullduty_en_END      (0)
#define SOC_SCHARGER_BUCK_REG5_buck_block_ctrl_START     (1)
#define SOC_SCHARGER_BUCK_REG5_buck_block_ctrl_END       (3)
#define SOC_SCHARGER_BUCK_REG5_buck_saw_peak_adj_START   (4)
#define SOC_SCHARGER_BUCK_REG5_buck_saw_peak_adj_END     (5)
#define SOC_SCHARGER_BUCK_REG5_buck_saw_vally_adj_START  (6)
#define SOC_SCHARGER_BUCK_REG5_buck_saw_vally_adj_END    (6)
#define SOC_SCHARGER_BUCK_REG5_buck_syn_en_START         (7)
#define SOC_SCHARGER_BUCK_REG5_buck_syn_en_END           (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_BUCK_REG6_UNION
 结构说明  : BUCK_REG6 寄存器结构定义。地址偏移量:0x66，初值:0x51，宽度:8
 寄存器说明: BUCK_REG6调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_fullduty_offtime : 2;  /* bit[0-1]: 直通后强制关闭上管时间调节寄存器：
                                                                00：20nS；
                                                                01：30nS；
                                                                01：40nS；
                                                                11：50n。 */
        unsigned char  buck_min_offtime_sel  : 1;  /* bit[2]  : 最小关断时间屏蔽 */
        unsigned char  buck_min_ontime_sel   : 1;  /* bit[3]  : 最小导通时间屏蔽 */
        unsigned char  buck_min_offtime      : 2;  /* bit[4-5]: 最小关断时间选择 */
        unsigned char  buck_min_ontime       : 2;  /* bit[6-7]: 最小导通时间选择 */
    } reg;
} SOC_SCHARGER_BUCK_REG6_UNION;
#endif
#define SOC_SCHARGER_BUCK_REG6_buck_fullduty_offtime_START  (0)
#define SOC_SCHARGER_BUCK_REG6_buck_fullduty_offtime_END    (1)
#define SOC_SCHARGER_BUCK_REG6_buck_min_offtime_sel_START   (2)
#define SOC_SCHARGER_BUCK_REG6_buck_min_offtime_sel_END     (2)
#define SOC_SCHARGER_BUCK_REG6_buck_min_ontime_sel_START    (3)
#define SOC_SCHARGER_BUCK_REG6_buck_min_ontime_sel_END      (3)
#define SOC_SCHARGER_BUCK_REG6_buck_min_offtime_START       (4)
#define SOC_SCHARGER_BUCK_REG6_buck_min_offtime_END         (5)
#define SOC_SCHARGER_BUCK_REG6_buck_min_ontime_START        (6)
#define SOC_SCHARGER_BUCK_REG6_buck_min_ontime_END          (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_BUCK_REG7_UNION
 结构说明  : BUCK_REG7 寄存器结构定义。地址偏移量:0x67，初值:0x25，宽度:8
 寄存器说明: BUCK_REG7调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_pfm_in             : 2;  /* bit[0-1]: 进入pfm点调节 */
        unsigned char  buck_pfm_ibias_adj      : 2;  /* bit[2-3]: buck pfm模式bias电流调节 */
        unsigned char  buck_fullduty_delaytime : 4;  /* bit[4-7]: 多少时间没有开关动作视为直通：
                                                                  0001：4uS；
                                                                  0010：8uS；
                                                                  0100：16uS；
                                                                  1000：32uS。 */
    } reg;
} SOC_SCHARGER_BUCK_REG7_UNION;
#endif
#define SOC_SCHARGER_BUCK_REG7_buck_pfm_in_START              (0)
#define SOC_SCHARGER_BUCK_REG7_buck_pfm_in_END                (1)
#define SOC_SCHARGER_BUCK_REG7_buck_pfm_ibias_adj_START       (2)
#define SOC_SCHARGER_BUCK_REG7_buck_pfm_ibias_adj_END         (3)
#define SOC_SCHARGER_BUCK_REG7_buck_fullduty_delaytime_START  (4)
#define SOC_SCHARGER_BUCK_REG7_buck_fullduty_delaytime_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_BUCK_REG8_UNION
 结构说明  : BUCK_REG8 寄存器结构定义。地址偏移量:0x68，初值:0x54，宽度:8
 寄存器说明: BUCK_REG8调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_offtime_judge_en    : 1;  /* bit[0]  : buck下管开启时间检测功能的使能信号 默认0不开 */
        unsigned char  buck_offtime_judge_delay : 3;  /* bit[1-3]: 多少时间内判断发生下管开启时间比较短 */
        unsigned char  buck_offtime_judge       : 2;  /* bit[4-5]: buck下管开启时间检测，给均流sense电路准备时间 */
        unsigned char  buck_pfm_out             : 2;  /* bit[6-7]: 退出pfm点调节 */
    } reg;
} SOC_SCHARGER_BUCK_REG8_UNION;
#endif
#define SOC_SCHARGER_BUCK_REG8_buck_offtime_judge_en_START     (0)
#define SOC_SCHARGER_BUCK_REG8_buck_offtime_judge_en_END       (0)
#define SOC_SCHARGER_BUCK_REG8_buck_offtime_judge_delay_START  (1)
#define SOC_SCHARGER_BUCK_REG8_buck_offtime_judge_delay_END    (3)
#define SOC_SCHARGER_BUCK_REG8_buck_offtime_judge_START        (4)
#define SOC_SCHARGER_BUCK_REG8_buck_offtime_judge_END          (5)
#define SOC_SCHARGER_BUCK_REG8_buck_pfm_out_START              (6)
#define SOC_SCHARGER_BUCK_REG8_buck_pfm_out_END                (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_BUCK_REG9_UNION
 结构说明  : BUCK_REG9 寄存器结构定义。地址偏移量:0x69，初值:0xD5，宽度:8
 寄存器说明: BUCK_REG9调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_cmp_ibias_adj   : 1;  /* bit[0]  : buck比较器电流调节寄存器：
                                                               0：0.5uA；
                                                               1：2uA。 */
        unsigned char  buck_sft_maxduty_en  : 1;  /* bit[1]  : 软启动时最大占空比限制使能控制 */
        unsigned char  buck_9v_maxduty_adj  : 2;  /* bit[2-3]: 9V输入时最大占空比调节 */
        unsigned char  buck_12v_maxduty_adj : 2;  /* bit[4-5]: 12V输入时最大占空比调节 */
        unsigned char  buck_9v_maxduty_en   : 1;  /* bit[6]  : 9V输入时最大占空比是否使能 */
        unsigned char  buck_12v_maxduty_en  : 1;  /* bit[7]  : 12V输入时最大占空比是否使能 */
    } reg;
} SOC_SCHARGER_BUCK_REG9_UNION;
#endif
#define SOC_SCHARGER_BUCK_REG9_buck_cmp_ibias_adj_START    (0)
#define SOC_SCHARGER_BUCK_REG9_buck_cmp_ibias_adj_END      (0)
#define SOC_SCHARGER_BUCK_REG9_buck_sft_maxduty_en_START   (1)
#define SOC_SCHARGER_BUCK_REG9_buck_sft_maxduty_en_END     (1)
#define SOC_SCHARGER_BUCK_REG9_buck_9v_maxduty_adj_START   (2)
#define SOC_SCHARGER_BUCK_REG9_buck_9v_maxduty_adj_END     (3)
#define SOC_SCHARGER_BUCK_REG9_buck_12v_maxduty_adj_START  (4)
#define SOC_SCHARGER_BUCK_REG9_buck_12v_maxduty_adj_END    (5)
#define SOC_SCHARGER_BUCK_REG9_buck_9v_maxduty_en_START    (6)
#define SOC_SCHARGER_BUCK_REG9_buck_9v_maxduty_en_END      (6)
#define SOC_SCHARGER_BUCK_REG9_buck_12v_maxduty_en_START   (7)
#define SOC_SCHARGER_BUCK_REG9_buck_12v_maxduty_en_END     (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_BUCK_REG10_UNION
 结构说明  : BUCK_REG10 寄存器结构定义。地址偏移量:0x6A，初值:0x12，宽度:8
 寄存器说明: BUCK_REG10调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_hmos_fall    : 3;  /* bit[0-2]: 上管下降沿驱动能力选择 */
        unsigned char  buck_hmos_rise    : 3;  /* bit[3-5]: 上管上升沿驱动能力选择 */
        unsigned char  buck_sftstart_adj : 2;  /* bit[6-7]: buck软启动时间调节寄存器 */
    } reg;
} SOC_SCHARGER_BUCK_REG10_UNION;
#endif
#define SOC_SCHARGER_BUCK_REG10_buck_hmos_fall_START     (0)
#define SOC_SCHARGER_BUCK_REG10_buck_hmos_fall_END       (2)
#define SOC_SCHARGER_BUCK_REG10_buck_hmos_rise_START     (3)
#define SOC_SCHARGER_BUCK_REG10_buck_hmos_rise_END       (5)
#define SOC_SCHARGER_BUCK_REG10_buck_sftstart_adj_START  (6)
#define SOC_SCHARGER_BUCK_REG10_buck_sftstart_adj_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_BUCK_REG11_UNION
 结构说明  : BUCK_REG11 寄存器结构定义。地址偏移量:0x6B，初值:0x48，宽度:8
 寄存器说明: BUCK_REG11调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_dt_lshs_delay : 2;  /* bit[0-1]: 下管到上管死区额外延迟5ns：
                                                             高位：1 老死区控制加5nS
                                                             低位：1 新死区控制加5nS */
        unsigned char  buck_lmos_fall     : 3;  /* bit[2-4]: 下管下降沿驱动能力选择 */
        unsigned char  buck_lmos_rise     : 3;  /* bit[5-7]: 下管上升沿驱动能力选择 */
    } reg;
} SOC_SCHARGER_BUCK_REG11_UNION;
#endif
#define SOC_SCHARGER_BUCK_REG11_buck_dt_lshs_delay_START  (0)
#define SOC_SCHARGER_BUCK_REG11_buck_dt_lshs_delay_END    (1)
#define SOC_SCHARGER_BUCK_REG11_buck_lmos_fall_START      (2)
#define SOC_SCHARGER_BUCK_REG11_buck_lmos_fall_END        (4)
#define SOC_SCHARGER_BUCK_REG11_buck_lmos_rise_START      (5)
#define SOC_SCHARGER_BUCK_REG11_buck_lmos_rise_END        (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_BUCK_REG12_UNION
 结构说明  : BUCK_REG12 寄存器结构定义。地址偏移量:0x6C，初值:0x01，宽度:8
 寄存器说明: BUCK_REG12调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_dmd_ibias   : 2;  /* bit[0-1]: buck_dmd偏置电流调节 */
        unsigned char  buck_dmd_dis     : 1;  /* bit[2]  : 选择是否屏蔽DMD功能：
                                                           0：不屏蔽；
                                                           1：屏蔽。 */
        unsigned char  buck_dmd_clamp   : 1;  /* bit[3]  : dmd比较器输出嵌位使能：
                                                           0：嵌位；
                                                           1：不嵌位。 */
        unsigned char  buck_ss_init_dis : 1;  /* bit[4]  : buck启动时是否屏蔽init模块：
                                                           0：不屏蔽；
                                                           1：屏蔽 */
        unsigned char  buck_ssmode_en   : 1;  /* bit[5]  : buck启动时是否要等待VC再开启driver：
                                                           0：不等待；
                                                           1：等待。 */
        unsigned char  buck_dt_hsls     : 1;  /* bit[6]  : 上管到下管死区额外延迟5nS：
                                                           0：不加5nS；
                                                           1：加5nS。 */
        unsigned char  buck_dt_lshs     : 1;  /* bit[7]  : 下管到上管的死区产生方式选择：
                                                           0：老死区时间；
                                                           1：新死区时间(PWM)。 */
    } reg;
} SOC_SCHARGER_BUCK_REG12_UNION;
#endif
#define SOC_SCHARGER_BUCK_REG12_buck_dmd_ibias_START    (0)
#define SOC_SCHARGER_BUCK_REG12_buck_dmd_ibias_END      (1)
#define SOC_SCHARGER_BUCK_REG12_buck_dmd_dis_START      (2)
#define SOC_SCHARGER_BUCK_REG12_buck_dmd_dis_END        (2)
#define SOC_SCHARGER_BUCK_REG12_buck_dmd_clamp_START    (3)
#define SOC_SCHARGER_BUCK_REG12_buck_dmd_clamp_END      (3)
#define SOC_SCHARGER_BUCK_REG12_buck_ss_init_dis_START  (4)
#define SOC_SCHARGER_BUCK_REG12_buck_ss_init_dis_END    (4)
#define SOC_SCHARGER_BUCK_REG12_buck_ssmode_en_START    (5)
#define SOC_SCHARGER_BUCK_REG12_buck_ssmode_en_END      (5)
#define SOC_SCHARGER_BUCK_REG12_buck_dt_hsls_START      (6)
#define SOC_SCHARGER_BUCK_REG12_buck_dt_hsls_END        (6)
#define SOC_SCHARGER_BUCK_REG12_buck_dt_lshs_START      (7)
#define SOC_SCHARGER_BUCK_REG12_buck_dt_lshs_END        (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_BUCK_REG13_UNION
 结构说明  : BUCK_REG13 寄存器结构定义。地址偏移量:0x6D，初值:0x39，宽度:8
 寄存器说明: BUCK_REG13调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_q1ocp_adj    : 2;  /* bit[0-1]: bcuk上管ocp检测调节寄存器：
                                                            00：1.8A；
                                                            01：2A；
                                                            10：2.2A；
                                                            11：2.4A。 */
        unsigned char  buck_sft_scp_en_n : 1;  /* bit[2]  : buck 软启动是否开启scp功能：
                                                            0：开启；
                                                            1：屏蔽。 */
        unsigned char  buck_dmd_sel      : 4;  /* bit[3-6]: DMD点选择：
                                                            0111:180mA */
        unsigned char  buck_dmd_delay    : 1;  /* bit[7]  : dmd检测NG延时：
                                                            1：加入15nS */
    } reg;
} SOC_SCHARGER_BUCK_REG13_UNION;
#endif
#define SOC_SCHARGER_BUCK_REG13_buck_q1ocp_adj_START     (0)
#define SOC_SCHARGER_BUCK_REG13_buck_q1ocp_adj_END       (1)
#define SOC_SCHARGER_BUCK_REG13_buck_sft_scp_en_n_START  (2)
#define SOC_SCHARGER_BUCK_REG13_buck_sft_scp_en_n_END    (2)
#define SOC_SCHARGER_BUCK_REG13_buck_dmd_sel_START       (3)
#define SOC_SCHARGER_BUCK_REG13_buck_dmd_sel_END         (6)
#define SOC_SCHARGER_BUCK_REG13_buck_dmd_delay_START     (7)
#define SOC_SCHARGER_BUCK_REG13_buck_dmd_delay_END       (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_BUCK_REG14_UNION
 结构说明  : BUCK_REG14 寄存器结构定义。地址偏移量:0x6E，初值:0x55，宽度:8
 寄存器说明: BUCK_REG14调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_q1ocp_lpf_adj : 2;  /* bit[0-1]: buck上管检测时滤抖时间调节：
                                                             00：50n；
                                                             01：75n；
                                                             10：90n；
                                                             11：100n。 */
        unsigned char  buck_q3ocp_lpf_adj : 2;  /* bit[2-3]: buck下管检测时滤抖时间调节：
                                                             00：50n；
                                                             01：75n；
                                                             10：90n；
                                                             11：100n。 */
        unsigned char  buck_ocp_vally     : 2;  /* bit[4-5]: buck 下管谷值ocp检测调节寄存器：
                                                             00：1.5A；
                                                             01：1.7A；
                                                             10：1.9A；
                                                             11：2.2A */
        unsigned char  buck_ocp_peak      : 2;  /* bit[6-7]: buck 下管峰值ocp检测调节寄存器：
                                                             00：2.5A；
                                                             01：2.8A；
                                                             10：3A；
                                                             11：3.2A */
    } reg;
} SOC_SCHARGER_BUCK_REG14_UNION;
#endif
#define SOC_SCHARGER_BUCK_REG14_buck_q1ocp_lpf_adj_START  (0)
#define SOC_SCHARGER_BUCK_REG14_buck_q1ocp_lpf_adj_END    (1)
#define SOC_SCHARGER_BUCK_REG14_buck_q3ocp_lpf_adj_START  (2)
#define SOC_SCHARGER_BUCK_REG14_buck_q3ocp_lpf_adj_END    (3)
#define SOC_SCHARGER_BUCK_REG14_buck_ocp_vally_START      (4)
#define SOC_SCHARGER_BUCK_REG14_buck_ocp_vally_END        (5)
#define SOC_SCHARGER_BUCK_REG14_buck_ocp_peak_START       (6)
#define SOC_SCHARGER_BUCK_REG14_buck_ocp_peak_END         (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_BUCK_REG15_UNION
 结构说明  : BUCK_REG15 寄存器结构定义。地址偏移量:0x6F，初值:0x04，宽度:8
 寄存器说明: BUCK_REG15调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_ocp_mode_sel      : 1;  /* bit[0]  : buck ocp时处理方法选择：
                                                                 0：谷峰值检测；
                                                                 1：只检测谷值。 */
        unsigned char  buck_ocp_sense_cap_adj : 1;  /* bit[1]  : buck ocp sense电路中滤波电容调节：
                                                                 0：不增加电容；
                                                                 1：增加电容。 */
        unsigned char  buck_ocp_delay         : 2;  /* bit[2-3]: 发生ocp后强制关闭上管时间调节：
                                                                 00：400nS；
                                                                 01：570nS；
                                                                 10：720nS；
                                                                 11：860nS。 */
        unsigned char  buck_sft_ocp_en        : 1;  /* bit[4]  : buck软启动时是否上、下管ocp同时检测: 
                                                                 0：同时检测；
                                                                 1：只检测上管。 */
        unsigned char  reserved               : 3;  /* bit[5-7]: 保留。 */
    } reg;
} SOC_SCHARGER_BUCK_REG15_UNION;
#endif
#define SOC_SCHARGER_BUCK_REG15_buck_ocp_mode_sel_START       (0)
#define SOC_SCHARGER_BUCK_REG15_buck_ocp_mode_sel_END         (0)
#define SOC_SCHARGER_BUCK_REG15_buck_ocp_sense_cap_adj_START  (1)
#define SOC_SCHARGER_BUCK_REG15_buck_ocp_sense_cap_adj_END    (1)
#define SOC_SCHARGER_BUCK_REG15_buck_ocp_delay_START          (2)
#define SOC_SCHARGER_BUCK_REG15_buck_ocp_delay_END            (3)
#define SOC_SCHARGER_BUCK_REG15_buck_sft_ocp_en_START         (4)
#define SOC_SCHARGER_BUCK_REG15_buck_sft_ocp_en_END           (4)


/*****************************************************************************
 结构名    : SOC_SCHARGER_BUCK_REG16_UNION
 结构说明  : BUCK_REG16 寄存器结构定义。地址偏移量:0x70，初值:0x15，宽度:8
 寄存器说明: BUCK两相均流调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_sd_sel      : 2;  /* bit[0-1]: 双相均流采样延迟时间调节位：
                                                           00：25ns；
                                                           01：50ns；
                                                           10：75ns；
                                                           11：100ns。 */
        unsigned char  buck_st_sel      : 2;  /* bit[2-3]: 双相均流采样时间调节位：
                                                           00：15ns；
                                                           01：30ns；
                                                           10：45ns；
                                                           11：60ns。 */
        unsigned char  buck_balance_sel : 1;  /* bit[4]  : 两相均流功能选择：
                                                           0：均流关闭；
                                                           1：均流使能。 */
        unsigned char  reserved         : 3;  /* bit[5-7]: 保留。 */
    } reg;
} SOC_SCHARGER_BUCK_REG16_UNION;
#endif
#define SOC_SCHARGER_BUCK_REG16_buck_sd_sel_START       (0)
#define SOC_SCHARGER_BUCK_REG16_buck_sd_sel_END         (1)
#define SOC_SCHARGER_BUCK_REG16_buck_st_sel_START       (2)
#define SOC_SCHARGER_BUCK_REG16_buck_st_sel_END         (3)
#define SOC_SCHARGER_BUCK_REG16_buck_balance_sel_START  (4)
#define SOC_SCHARGER_BUCK_REG16_buck_balance_sel_END    (4)


/*****************************************************************************
 结构名    : SOC_SCHARGER_BUCK_RES_SEL0_UNION
 结构说明  : BUCK_RES_SEL0 寄存器结构定义。地址偏移量:0x71，初值:0x55，宽度:8
 寄存器说明: BUCK电阻调节0寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_res4_sel : 2;  /* bit[0-1]: dpm环路preamp跨导调节电阻：
                                                        00：3.5K；
                                                        01：5.3K；
                                                        10：7.1K；
                                                        11：8.9K； */
        unsigned char  buck_res3_sel : 2;  /* bit[2-3]: fast cc regulation 环路preamp跨导调节电阻：
                                                        00：35K；
                                                        01：70K；
                                                        10：105K；
                                                        11：140K； */
        unsigned char  buck_res2_sel : 2;  /* bit[4-5]: cv regulation 环路preamp跨导调节电阻：
                                                        00：0.9K；
                                                        01：1.8K；
                                                        10：2.7K；
                                                        11：3.6K； */
        unsigned char  buck_res1_sel : 2;  /* bit[6-7]: sys regulation 环路preamp跨导调节电阻：
                                                        00：1.8K；
                                                        01：2.7K；
                                                        10：3.6K；
                                                        11：4.5K； */
    } reg;
} SOC_SCHARGER_BUCK_RES_SEL0_UNION;
#endif
#define SOC_SCHARGER_BUCK_RES_SEL0_buck_res4_sel_START  (0)
#define SOC_SCHARGER_BUCK_RES_SEL0_buck_res4_sel_END    (1)
#define SOC_SCHARGER_BUCK_RES_SEL0_buck_res3_sel_START  (2)
#define SOC_SCHARGER_BUCK_RES_SEL0_buck_res3_sel_END    (3)
#define SOC_SCHARGER_BUCK_RES_SEL0_buck_res2_sel_START  (4)
#define SOC_SCHARGER_BUCK_RES_SEL0_buck_res2_sel_END    (5)
#define SOC_SCHARGER_BUCK_RES_SEL0_buck_res1_sel_START  (6)
#define SOC_SCHARGER_BUCK_RES_SEL0_buck_res1_sel_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_BUCK_RES_SEL1_UNION
 结构说明  : BUCK_RES_SEL1 寄存器结构定义。地址偏移量:0x72，初值:0x55，宽度:8
 寄存器说明: BUCK电阻调节1寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_res8_sel : 2;  /* bit[0-1]: 三型补偿网络补偿电阻R2：
                                                        00：13K；
                                                        01：26K；
                                                        10：39K；
                                                        11：52K； */
        unsigned char  buck_res7_sel : 2;  /* bit[2-3]: 三型补偿网络补偿电阻R1：
                                                        00：535K；
                                                        01：1070K；
                                                        10：1605K；
                                                        11：2140K； */
        unsigned char  buck_res6_sel : 2;  /* bit[4-5]: themal regulation环路preamp跨导调节电阻：
                                                        00：3.5K；
                                                        01：5.3K；
                                                        10：7.1K；
                                                        11：8.9K； */
        unsigned char  buck_res5_sel : 2;  /* bit[6-7]: acl环路preamp跨导调节电阻：
                                                        00：54K；
                                                        01：108K；
                                                        10：162K；
                                                        11：216K； */
    } reg;
} SOC_SCHARGER_BUCK_RES_SEL1_UNION;
#endif
#define SOC_SCHARGER_BUCK_RES_SEL1_buck_res8_sel_START  (0)
#define SOC_SCHARGER_BUCK_RES_SEL1_buck_res8_sel_END    (1)
#define SOC_SCHARGER_BUCK_RES_SEL1_buck_res7_sel_START  (2)
#define SOC_SCHARGER_BUCK_RES_SEL1_buck_res7_sel_END    (3)
#define SOC_SCHARGER_BUCK_RES_SEL1_buck_res6_sel_START  (4)
#define SOC_SCHARGER_BUCK_RES_SEL1_buck_res6_sel_END    (5)
#define SOC_SCHARGER_BUCK_RES_SEL1_buck_res5_sel_START  (6)
#define SOC_SCHARGER_BUCK_RES_SEL1_buck_res5_sel_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_BUCK_RES_SEL2_UNION
 结构说明  : BUCK_RES_SEL2 寄存器结构定义。地址偏移量:0x73，初值:0x59，宽度:8
 寄存器说明: BUCK电阻调节2寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_res12_sel : 2;  /* bit[0-1]: cc环路补偿电阻：
                                                         00： 
                                                         01： 
                                                         10： 
                                                         11： */
        unsigned char  buck_res11_sel : 2;  /* bit[2-3]: 两相均流电路电流转电压电阻：
                                                         00：10K；
                                                         01：15K；
                                                         10：20K；
                                                         11：25K； */
        unsigned char  buck_res10_sel : 2;  /* bit[4-5]: 两相均流OTA输出电阻：
                                                         00：5K；
                                                         01：10K；
                                                         10：15K；
                                                         11：20K； */
        unsigned char  buck_res9_sel  : 2;  /* bit[6-7]: 三型补偿网络补偿电阻R3：
                                                         00：106K；
                                                         01：212K；
                                                         10：318K；
                                                         11：424K； */
    } reg;
} SOC_SCHARGER_BUCK_RES_SEL2_UNION;
#endif
#define SOC_SCHARGER_BUCK_RES_SEL2_buck_res12_sel_START  (0)
#define SOC_SCHARGER_BUCK_RES_SEL2_buck_res12_sel_END    (1)
#define SOC_SCHARGER_BUCK_RES_SEL2_buck_res11_sel_START  (2)
#define SOC_SCHARGER_BUCK_RES_SEL2_buck_res11_sel_END    (3)
#define SOC_SCHARGER_BUCK_RES_SEL2_buck_res10_sel_START  (4)
#define SOC_SCHARGER_BUCK_RES_SEL2_buck_res10_sel_END    (5)
#define SOC_SCHARGER_BUCK_RES_SEL2_buck_res9_sel_START   (6)
#define SOC_SCHARGER_BUCK_RES_SEL2_buck_res9_sel_END     (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_BUCK_RES_SEL3_UNION
 结构说明  : BUCK_RES_SEL3 寄存器结构定义。地址偏移量:0x74，初值:0x05，宽度:8
 寄存器说明: BUCK电阻调节3寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_res14_sel : 2;  /* bit[0-1]: acl环路补偿电阻：
                                                         00： 
                                                         01：
                                                         10： 
                                                         11：  */
        unsigned char  buck_res13_sel : 2;  /* bit[2-3]: dpm环路补偿电阻：
                                                         00： 
                                                         01：
                                                         10： 
                                                         11：  */
        unsigned char  reserved       : 4;  /* bit[4-7]: 保留。 */
    } reg;
} SOC_SCHARGER_BUCK_RES_SEL3_UNION;
#endif
#define SOC_SCHARGER_BUCK_RES_SEL3_buck_res14_sel_START  (0)
#define SOC_SCHARGER_BUCK_RES_SEL3_buck_res14_sel_END    (1)
#define SOC_SCHARGER_BUCK_RES_SEL3_buck_res13_sel_START  (2)
#define SOC_SCHARGER_BUCK_RES_SEL3_buck_res13_sel_END    (3)


/*****************************************************************************
 结构名    : SOC_SCHARGER_BUCK_CAP_SEL0_UNION
 结构说明  : BUCK_CAP_SEL0 寄存器结构定义。地址偏移量:0x75，初值:0x55，宽度:8
 寄存器说明: BUCK电容调节0寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_cap4_sel : 2;  /* bit[0-1]: 均流环路采样电容：
                                                        00：4pF；
                                                        01：6pF；
                                                        10：8pF；
                                                        11：10pF。 */
        unsigned char  buck_cap3_sel : 2;  /* bit[2-3]: 三型补偿网络补偿电容C3：
                                                        00：50fF；
                                                        01：100fF；
                                                        10：150fF；
                                                        11：200fF。 */
        unsigned char  buck_cap2_sel : 2;  /* bit[4-5]: 三型补偿网络补偿电容C2：
                                                        00：1.2pF；
                                                        01：2.4pF；
                                                        10：3.6pF；
                                                        11：4.8pF。 */
        unsigned char  buck_cap1_sel : 2;  /* bit[6-7]: 三型补偿网络补偿电容C1：
                                                        00：41pF；
                                                        01：50pF；
                                                        10：59pF；
                                                        11：68pF。 */
    } reg;
} SOC_SCHARGER_BUCK_CAP_SEL0_UNION;
#endif
#define SOC_SCHARGER_BUCK_CAP_SEL0_buck_cap4_sel_START  (0)
#define SOC_SCHARGER_BUCK_CAP_SEL0_buck_cap4_sel_END    (1)
#define SOC_SCHARGER_BUCK_CAP_SEL0_buck_cap3_sel_START  (2)
#define SOC_SCHARGER_BUCK_CAP_SEL0_buck_cap3_sel_END    (3)
#define SOC_SCHARGER_BUCK_CAP_SEL0_buck_cap2_sel_START  (4)
#define SOC_SCHARGER_BUCK_CAP_SEL0_buck_cap2_sel_END    (5)
#define SOC_SCHARGER_BUCK_CAP_SEL0_buck_cap1_sel_START  (6)
#define SOC_SCHARGER_BUCK_CAP_SEL0_buck_cap1_sel_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_BUCK_CAP_SEL1_UNION
 结构说明  : BUCK_CAP_SEL1 寄存器结构定义。地址偏移量:0x76，初值:0x15，宽度:8
 寄存器说明: BUCK电容调节1寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_cap7_sel : 2;  /* bit[0-1]: acl环路补偿电容：
                                                        00：3pF；
                                                        01：6pF；
                                                        10：9pF；
                                                        11：12pF。 */
        unsigned char  buck_cap6_sel : 2;  /* bit[2-3]: dpm环路补偿电容：
                                                        00：1.2pF；
                                                        01：2.4pF；
                                                        10：3.6pF；
                                                        11：4.8pF。 */
        unsigned char  buck_cap5_sel : 2;  /* bit[4-5]: cc环路补偿电容：
                                                        00：3pF；
                                                        01：6pF；
                                                        10：9pF；
                                                        11：12pF。 */
        unsigned char  reserved      : 2;  /* bit[6-7]: 保留。 */
    } reg;
} SOC_SCHARGER_BUCK_CAP_SEL1_UNION;
#endif
#define SOC_SCHARGER_BUCK_CAP_SEL1_buck_cap7_sel_START  (0)
#define SOC_SCHARGER_BUCK_CAP_SEL1_buck_cap7_sel_END    (1)
#define SOC_SCHARGER_BUCK_CAP_SEL1_buck_cap6_sel_START  (2)
#define SOC_SCHARGER_BUCK_CAP_SEL1_buck_cap6_sel_END    (3)
#define SOC_SCHARGER_BUCK_CAP_SEL1_buck_cap5_sel_START  (4)
#define SOC_SCHARGER_BUCK_CAP_SEL1_buck_cap5_sel_END    (5)


/*****************************************************************************
 结构名    : SOC_SCHARGER_BUCK_RESERVE0_UNION
 结构说明  : BUCK_RESERVE0 寄存器结构定义。地址偏移量:0x77，初值:0x00，宽度:8
 寄存器说明: BUCK预留0寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_reserve0 : 8;  /* bit[0-7]: <7> 强制buck_osc使能震荡，避免不震荡，默认此功能关闭
                                                        <6> 屏蔽EA高嵌位，默认0不屏蔽；
                                                        <5:0>buck 6个环路使能控制位：
                                                         000000：环路全部使能
                                                         111111：环路全部不使能 */
    } reg;
} SOC_SCHARGER_BUCK_RESERVE0_UNION;
#endif
#define SOC_SCHARGER_BUCK_RESERVE0_buck_reserve0_START  (0)
#define SOC_SCHARGER_BUCK_RESERVE0_buck_reserve0_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_BUCK_RESERVE1_UNION
 结构说明  : BUCK_RESERVE1 寄存器结构定义。地址偏移量:0x78，初值:0x00，宽度:8
 寄存器说明: BUCK预留1寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_reserve1 : 8;  /* bit[0-7]: <3> 5V输入时，是否使能OCP，默认0表示使能
                                                        <5:4> dpm修调备用寄存器，默认00 */
    } reg;
} SOC_SCHARGER_BUCK_RESERVE1_UNION;
#endif
#define SOC_SCHARGER_BUCK_RESERVE1_buck_reserve1_START  (0)
#define SOC_SCHARGER_BUCK_RESERVE1_buck_reserve1_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_BUCK_RESERVE2_UNION
 结构说明  : BUCK_RESERVE2 寄存器结构定义。地址偏移量:0x79，初值:0x00，宽度:8
 寄存器说明: BUCK预留2寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_reserve2 : 8;  /* bit[0-7]: <7> anti-reverbst模块使能
                                                        0：关闭 1：使能
                                                        <6> anti-reverbst去抖时间选择
                                                        0：32ms 1：8ms
                                                        <5:4> anti-reverbst参数调整
                                                        00:50mv
                                                        01:100mv
                                                        10:200mv
                                                        11:0mv
                                                        <3:2>buck_cap8大小调节
                                                        00: 60pF
                                                        01：45pF
                                                        10: 30pF
                                                        11: 15pF
                                                        <1:0>buck均流模式选择：
                                                        00：默认模式
                                                        01：强制连续均流模式
                                                        10：强制采样均流模式
                                                        11：默认模式 */
    } reg;
} SOC_SCHARGER_BUCK_RESERVE2_UNION;
#endif
#define SOC_SCHARGER_BUCK_RESERVE2_buck_reserve2_START  (0)
#define SOC_SCHARGER_BUCK_RESERVE2_buck_reserve2_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_BUCK_RESERVE3_UNION
 结构说明  : BUCK_RESERVE3 寄存器结构定义。地址偏移量:0x7A，初值:0x00，宽度:8
 寄存器说明: BUCK预留3寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_reserve3 : 8;  /* bit[0-7]: 预留寄存器 */
    } reg;
} SOC_SCHARGER_BUCK_RESERVE3_UNION;
#endif
#define SOC_SCHARGER_BUCK_RESERVE3_buck_reserve3_START  (0)
#define SOC_SCHARGER_BUCK_RESERVE3_buck_reserve3_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_BUCK_RESERVE0_STATE_UNION
 结构说明  : BUCK_RESERVE0_STATE 寄存器结构定义。地址偏移量:0x7B，初值:0x00，宽度:8
 寄存器说明: BUCK预留0状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_reserve0_state : 8;  /* bit[0-7]: 预留寄存器 */
    } reg;
} SOC_SCHARGER_BUCK_RESERVE0_STATE_UNION;
#endif
#define SOC_SCHARGER_BUCK_RESERVE0_STATE_buck_reserve0_state_START  (0)
#define SOC_SCHARGER_BUCK_RESERVE0_STATE_buck_reserve0_state_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_BUCK_RESERVE1_STATE_UNION
 结构说明  : BUCK_RESERVE1_STATE 寄存器结构定义。地址偏移量:0x7C，初值:0x00，宽度:8
 寄存器说明: BUCK预留1状态寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_reserve1_state : 8;  /* bit[0-7]: 预留寄存器 */
    } reg;
} SOC_SCHARGER_BUCK_RESERVE1_STATE_UNION;
#endif
#define SOC_SCHARGER_BUCK_RESERVE1_STATE_buck_reserve1_state_START  (0)
#define SOC_SCHARGER_BUCK_RESERVE1_STATE_buck_reserve1_state_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_OTG_REG0_UNION
 结构说明  : OTG_REG0 寄存器结构定义。地址偏移量:0x80，初值:0x2F，宽度:8
 寄存器说明: OTG_REG0调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otg_scp_en  : 1;  /* bit[0]  : boost scp动作选择：
                                                      0：短路后系统不自动关闭（仍上报）；
                                                      1：短路后系统自动关闭； */
        unsigned char  otg_ocp_sys : 1;  /* bit[1]  : boost OCP动作选择：
                                                      0：过流后不上报；
                                                      1：过流后上报。 */
        unsigned char  otg_ocp_en  : 1;  /* bit[2]  : boost OCP动作选择：
                                                      0：过流后不限流；
                                                      1：过流后限流。 */
        unsigned char  otg_lim_set : 2;  /* bit[3-4]: boost平均限流选择：
                                                      00：500mA；
                                                      01：1A；
                                                      10：1.5A；
                                                      11：2A。 */
        unsigned char  otg_lim_en  : 1;  /* bit[5]  : boost 平均限流模块使能：
                                                      0：关闭平均限流模块；
                                                      1：使能平均限流模块。 */
        unsigned char  otg_en_int  : 1;  /* bit[6]  : otg_en使能配置寄存器：
                                                      0：关闭；
                                                      1：使能。 */
        unsigned char  reserved    : 1;  /* bit[7]  : 保留。 */
    } reg;
} SOC_SCHARGER_OTG_REG0_UNION;
#endif
#define SOC_SCHARGER_OTG_REG0_otg_scp_en_START   (0)
#define SOC_SCHARGER_OTG_REG0_otg_scp_en_END     (0)
#define SOC_SCHARGER_OTG_REG0_otg_ocp_sys_START  (1)
#define SOC_SCHARGER_OTG_REG0_otg_ocp_sys_END    (1)
#define SOC_SCHARGER_OTG_REG0_otg_ocp_en_START   (2)
#define SOC_SCHARGER_OTG_REG0_otg_ocp_en_END     (2)
#define SOC_SCHARGER_OTG_REG0_otg_lim_set_START  (3)
#define SOC_SCHARGER_OTG_REG0_otg_lim_set_END    (4)
#define SOC_SCHARGER_OTG_REG0_otg_lim_en_START   (5)
#define SOC_SCHARGER_OTG_REG0_otg_lim_en_END     (5)
#define SOC_SCHARGER_OTG_REG0_otg_en_int_START   (6)
#define SOC_SCHARGER_OTG_REG0_otg_en_int_END     (6)


/*****************************************************************************
 结构名    : SOC_SCHARGER_OTG_REG1_UNION
 结构说明  : OTG_REG1 寄存器结构定义。地址偏移量:0x81，初值:0x5D，宽度:8
 寄存器说明: OTG_REG1调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otg_vo        : 2;  /* bit[0-1]: OTG输出电压微调：
                                                        00： 
                                                        01：
                                                        10： 
                                                        11： */
        unsigned char  otg_pfm_v_en  : 1;  /* bit[2]  : boost pfm_v使能：
                                                        0：关闭pfm；
                                                        1：使能pfm。 */
        unsigned char  otg_ovp_en    : 1;  /* bit[3]  : boost ovp使能：
                                                        0：关闭过压电路（不上报）；
                                                        1：使能过压电路（上报）。 */
        unsigned char  otg_uvp_set_v : 2;  /* bit[4-5]: boost uvp电压点选择：
                                                        00：
                                                        01： 
                                                        10：
                                                        11：  */
        unsigned char  otg_uvp_en    : 1;  /* bit[6]  : boost uvp使能：
                                                        0：关闭欠压电路（不上报）；
                                                        1：使能欠压电路（上报）。 */
        unsigned char  reserved      : 1;  /* bit[7]  : 保留。 */
    } reg;
} SOC_SCHARGER_OTG_REG1_UNION;
#endif
#define SOC_SCHARGER_OTG_REG1_otg_vo_START         (0)
#define SOC_SCHARGER_OTG_REG1_otg_vo_END           (1)
#define SOC_SCHARGER_OTG_REG1_otg_pfm_v_en_START   (2)
#define SOC_SCHARGER_OTG_REG1_otg_pfm_v_en_END     (2)
#define SOC_SCHARGER_OTG_REG1_otg_ovp_en_START     (3)
#define SOC_SCHARGER_OTG_REG1_otg_ovp_en_END       (3)
#define SOC_SCHARGER_OTG_REG1_otg_uvp_set_v_START  (4)
#define SOC_SCHARGER_OTG_REG1_otg_uvp_set_v_END    (5)
#define SOC_SCHARGER_OTG_REG1_otg_uvp_en_START     (6)
#define SOC_SCHARGER_OTG_REG1_otg_uvp_en_END       (6)


/*****************************************************************************
 结构名    : SOC_SCHARGER_OTG_REG2_UNION
 结构说明  : OTG_REG2 寄存器结构定义。地址偏移量:0x82，初值:0x2B，宽度:8
 寄存器说明: OTG_REG2调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otg_slop_en   : 1;  /* bit[0]  : boost 斜坡补偿使能：
                                                        0：关闭斜坡补偿；
                                                        1：使能斜坡补偿。 */
        unsigned char  otg_dmd       : 1;  /* bit[1]  : boost dmd使能：
                                                        0：关闭过零检测；
                                                        1：使能过零检测。 */
        unsigned char  otg_skip_set  : 1;  /* bit[2]  : skip周期内Pmos的开关状态：
                                                        0：PMOS关闭；
                                                        1：PMOS开启。 */
        unsigned char  otg_ovp_set_t : 2;  /* bit[3-4]: boost ovp去抖时间选择：
                                                        00：0ms；
                                                        01：1ms；
                                                        10：2ms；
                                                        11：4ms。 */
        unsigned char  otg_uvp_set_t : 2;  /* bit[5-6]: boost uvp去抖时间选择：
                                                        00：0ms；
                                                        01：1ms；
                                                        10：2ms；
                                                        11：4ms。 */
        unsigned char  otg_scp_time  : 1;  /* bit[7]  : boost scp时间选择：
                                                        0：1ms内VOUT不足0.85BAT，上报短路；
                                                        1：2ms内VOUT不足0.85BAT，上报短路。 */
    } reg;
} SOC_SCHARGER_OTG_REG2_UNION;
#endif
#define SOC_SCHARGER_OTG_REG2_otg_slop_en_START    (0)
#define SOC_SCHARGER_OTG_REG2_otg_slop_en_END      (0)
#define SOC_SCHARGER_OTG_REG2_otg_dmd_START        (1)
#define SOC_SCHARGER_OTG_REG2_otg_dmd_END          (1)
#define SOC_SCHARGER_OTG_REG2_otg_skip_set_START   (2)
#define SOC_SCHARGER_OTG_REG2_otg_skip_set_END     (2)
#define SOC_SCHARGER_OTG_REG2_otg_ovp_set_t_START  (3)
#define SOC_SCHARGER_OTG_REG2_otg_ovp_set_t_END    (4)
#define SOC_SCHARGER_OTG_REG2_otg_uvp_set_t_START  (5)
#define SOC_SCHARGER_OTG_REG2_otg_uvp_set_t_END    (6)
#define SOC_SCHARGER_OTG_REG2_otg_scp_time_START   (7)
#define SOC_SCHARGER_OTG_REG2_otg_scp_time_END     (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_OTG_REG3_UNION
 结构说明  : OTG_REG3 寄存器结构定义。地址偏移量:0x83，初值:0x94，宽度:8
 寄存器说明: OTG_REG3调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otg_clp_l_iav_set : 2;  /* bit[0-1]: boost EA_iav钳位电路（低）电平选择：
                                                            00：
                                                            01：
                                                            10：
                                                            11： */
        unsigned char  otg_clp_l_iav_en  : 1;  /* bit[2]  : boost EA_iav钳位电路（低）使能：
                                                            0：关闭钳位电路；
                                                            1：使能钳位电路。 */
        unsigned char  otg_clp_h_iav_en  : 1;  /* bit[3]  : boost EA_iav钳位电路（高）使能：
                                                            0：关闭钳位电路；
                                                            1：使能钳位电路。 */
        unsigned char  otg_clp_l_en      : 1;  /* bit[4]  : boost EA钳位电路（低）使能：
                                                            0：关闭钳位电路；
                                                            1：使能钳位电路。 */
        unsigned char  otg_clp_h_en      : 1;  /* bit[5]  : boost EA钳位电路（高）使能：
                                                            0：关闭钳位电路；
                                                            1：使能钳位电路。 */
        unsigned char  otg_slop_set      : 2;  /* bit[6-7]: boost 斜坡补偿电容选择：
                                                            00：1.5p；
                                                            01：2p；
                                                            10：2.5p；
                                                            11：3p。 */
    } reg;
} SOC_SCHARGER_OTG_REG3_UNION;
#endif
#define SOC_SCHARGER_OTG_REG3_otg_clp_l_iav_set_START  (0)
#define SOC_SCHARGER_OTG_REG3_otg_clp_l_iav_set_END    (1)
#define SOC_SCHARGER_OTG_REG3_otg_clp_l_iav_en_START   (2)
#define SOC_SCHARGER_OTG_REG3_otg_clp_l_iav_en_END     (2)
#define SOC_SCHARGER_OTG_REG3_otg_clp_h_iav_en_START   (3)
#define SOC_SCHARGER_OTG_REG3_otg_clp_h_iav_en_END     (3)
#define SOC_SCHARGER_OTG_REG3_otg_clp_l_en_START       (4)
#define SOC_SCHARGER_OTG_REG3_otg_clp_l_en_END         (4)
#define SOC_SCHARGER_OTG_REG3_otg_clp_h_en_START       (5)
#define SOC_SCHARGER_OTG_REG3_otg_clp_h_en_END         (5)
#define SOC_SCHARGER_OTG_REG3_otg_slop_set_START       (6)
#define SOC_SCHARGER_OTG_REG3_otg_slop_set_END         (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_OTG_REG4_UNION
 结构说明  : OTG_REG4 寄存器结构定义。地址偏移量:0x84，初值:0x65，宽度:8
 寄存器说明: OTG_REG4调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otg_ccom2_cmp  : 2;  /* bit[0-1]: boost EA输出滤波电容（峰值电流模）：
                                                         00：0.8pF；
                                                         01：1.1pF；
                                                         10：1.4pF；
                                                         11：1.7pF。 */
        unsigned char  otg_ccom1_cmp  : 2;  /* bit[2-3]: boost 主环路补偿电容（峰值电流模）：
                                                         00：35pF；
                                                         01：40pF；
                                                         10：45pF；
                                                         11：50pF。 */
        unsigned char  otg_rcom_cmp   : 2;  /* bit[4-5]: boost 主环路补偿电阻（峰值电流模）：
                                                         00：320kΩ；
                                                         01：280kΩ；
                                                         10：240kΩ；
                                                         11：200kΩ。 */
        unsigned char  otg_clp_l_set  : 1;  /* bit[6]  : boost EA输出钳位值和VRAMP直流电平值的失调：
                                                         0：27mv；
                                                         1：40mv。 */
        unsigned char  otg_pfm_iav_en : 1;  /* bit[7]  : boost iloop_pfm使能：
                                                         0：关闭iloop_pfm；
                                                          1：使能iloop_pfm。 */
    } reg;
} SOC_SCHARGER_OTG_REG4_UNION;
#endif
#define SOC_SCHARGER_OTG_REG4_otg_ccom2_cmp_START   (0)
#define SOC_SCHARGER_OTG_REG4_otg_ccom2_cmp_END     (1)
#define SOC_SCHARGER_OTG_REG4_otg_ccom1_cmp_START   (2)
#define SOC_SCHARGER_OTG_REG4_otg_ccom1_cmp_END     (3)
#define SOC_SCHARGER_OTG_REG4_otg_rcom_cmp_START    (4)
#define SOC_SCHARGER_OTG_REG4_otg_rcom_cmp_END      (5)
#define SOC_SCHARGER_OTG_REG4_otg_clp_l_set_START   (6)
#define SOC_SCHARGER_OTG_REG4_otg_clp_l_set_END     (6)
#define SOC_SCHARGER_OTG_REG4_otg_pfm_iav_en_START  (7)
#define SOC_SCHARGER_OTG_REG4_otg_pfm_iav_en_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_OTG_REG5_UNION
 结构说明  : OTG_REG5 寄存器结构定义。地址偏移量:0x85，初值:0xA5，宽度:8
 寄存器说明: OTG_REG5调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otg_osc_ckmax : 2;  /* bit[0-1]: 振荡器放电电流（uA）：
                                                        00：13；
                                                        01：14；
                                                        10：15； 11：16。 */
        unsigned char  otg_ccom_iav  : 2;  /* bit[2-3]: boost 限流环路电容补偿：
                                                        00：20p；
                                                        01：25p；
                                                        10：30p；
                                                        11：35p。 */
        unsigned char  otg_rcom2_iav : 2;  /* bit[4-5]: boost 限流环路电阻补偿：
                                                        00：620kΩ；
                                                        01：580kΩ；
                                                        10：440kΩ；
                                                        11：300kΩ。 */
        unsigned char  otg_rcom1_iav : 2;  /* bit[6-7]: boost 限流环路电阻补偿：
                                                        00：1.2MΩ；
                                                        01：1.6MΩ；
                                                        10：2.0MΩ；
                                                        11：2.4MΩ。 */
    } reg;
} SOC_SCHARGER_OTG_REG5_UNION;
#endif
#define SOC_SCHARGER_OTG_REG5_otg_osc_ckmax_START  (0)
#define SOC_SCHARGER_OTG_REG5_otg_osc_ckmax_END    (1)
#define SOC_SCHARGER_OTG_REG5_otg_ccom_iav_START   (2)
#define SOC_SCHARGER_OTG_REG5_otg_ccom_iav_END     (3)
#define SOC_SCHARGER_OTG_REG5_otg_rcom2_iav_START  (4)
#define SOC_SCHARGER_OTG_REG5_otg_rcom2_iav_END    (5)
#define SOC_SCHARGER_OTG_REG5_otg_rcom1_iav_START  (6)
#define SOC_SCHARGER_OTG_REG5_otg_rcom1_iav_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_OTG_REG6_UNION
 结构说明  : OTG_REG6 寄存器结构定义。地址偏移量:0x86，初值:0x38，宽度:8
 寄存器说明: OTG_REG6调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otg_osc  : 4;  /* bit[0-3]: 开关频率（MHz）：
                                                   0000：2.01；
                                                   0001：1.98；
                                                   0010：1.94；
                                                   0011：1.90；
                                                   0100：1.86；
                                                   0101：1.81；
                                                   0110：1.74；
                                                   0111：1.65；
                                                   1000：1.54；
                                                   1001：1.41；
                                                   1010：1.27；
                                                   1011：1.11；
                                                   1100：0.92；
                                                   1101：0.73；
                                                   1110：0.50；
                                                   1111：0.31。 */
        unsigned char  otg_gm   : 3;  /* bit[4-6]: boost EA中gm电阻设定(gm=2/R)：
                                                   000：90kΩ；
                                                   001：80kΩ；
                                                   010：70kΩ；
                                                   011：60kΩ；
                                                   100：40kΩ；
                                                   101：30kΩ；
                                                   110：20kΩ；
                                                   111：10kΩ。 */
        unsigned char  reserved : 1;  /* bit[7]  : 保留。 */
    } reg;
} SOC_SCHARGER_OTG_REG6_UNION;
#endif
#define SOC_SCHARGER_OTG_REG6_otg_osc_START   (0)
#define SOC_SCHARGER_OTG_REG6_otg_osc_END     (3)
#define SOC_SCHARGER_OTG_REG6_otg_gm_START    (4)
#define SOC_SCHARGER_OTG_REG6_otg_gm_END      (6)


/*****************************************************************************
 结构名    : SOC_SCHARGER_OTG_REG7_UNION
 结构说明  : OTG_REG7 寄存器结构定义。地址偏移量:0x87，初值:0x69，宽度:8
 寄存器说明: OTG_REG7调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otg_dmd_ofs  : 4;  /* bit[0-3]: boost DMD失调电压调节：
                                                       0000：20mV (300mA)；
                                                       0001：16mV (240mA)；
                                                       0010：14mV (210mA)；
                                                       0011：12mV (180mA)；
                                                       0100：10mV (150mA)；
                                                       0101：8mV (120mA)；
                                                       0110：6mV (90mA)；
                                                       0111：4mV (60mA)；
                                                       1000：2mV (30mA)；
                                                       1001：0；
                                                       1010：-16mV (-180mA)；
                                                       1011：-32mV (-360mA)；
                                                       1100：-48mV (-540mA)；
                                                       1101：-64mV (-720mA)；
                                                       1110：-128mV (-900mA)；
                                                       1111：-256mV (-1080mA)。 */
        unsigned char  otg_ckmin    : 2;  /* bit[4-5]: NMOS最小导通时间：
                                                       00：40ns；
                                                       01：30ns；
                                                       10：20ns；
                                                       11：15ns。 */
        unsigned char  otg_lmos_ocp : 2;  /* bit[6-7]: boost 低端MOS管限流值(A)：
                                                       00：2.8；
                                                       01：3.2；
                                                       10：3.6；
                                                       11：4.0。 */
    } reg;
} SOC_SCHARGER_OTG_REG7_UNION;
#endif
#define SOC_SCHARGER_OTG_REG7_otg_dmd_ofs_START   (0)
#define SOC_SCHARGER_OTG_REG7_otg_dmd_ofs_END     (3)
#define SOC_SCHARGER_OTG_REG7_otg_ckmin_START     (4)
#define SOC_SCHARGER_OTG_REG7_otg_ckmin_END       (5)
#define SOC_SCHARGER_OTG_REG7_otg_lmos_ocp_START  (6)
#define SOC_SCHARGER_OTG_REG7_otg_lmos_ocp_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_OTG_REG8_UNION
 结构说明  : OTG_REG8 寄存器结构定义。地址偏移量:0x88，初值:0x8F，宽度:8
 寄存器说明: OTG_REG8调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otg_down  : 2;  /* bit[0-1]: OTG下电控制：
                                                    00：
                                                    01：
                                                    10： 
                                                    11： */
        unsigned char  otg_hmos  : 1;  /* bit[2]  : OTG 上管控制选择：
                                                    0：强制关闭；
                                                    1：正常开关。 */
        unsigned char  otg_cmp   : 1;  /* bit[3]  : OTG 主比较器电流选择：
                                                    0：0.5uA；
                                                    1：2uA。 */
        unsigned char  otg_phase : 2;  /* bit[4-5]: OTG输出选择：
                                                    00：一路开；
                                                    01：二路开；
                                                    10：一、二路全开；
                                                    10：一、二路全开。 */
        unsigned char  otg_rf    : 2;  /* bit[6-7]: 电感电流转电压阻抗：
                                                    00：0.5Ω（实际100kΩ）；
                                                    01：0.4Ω（实际80kΩ）；
                                                    10：0.3Ω（实际60kΩ）；
                                                    11：0.2Ω（实际40kΩ）。 */
    } reg;
} SOC_SCHARGER_OTG_REG8_UNION;
#endif
#define SOC_SCHARGER_OTG_REG8_otg_down_START   (0)
#define SOC_SCHARGER_OTG_REG8_otg_down_END     (1)
#define SOC_SCHARGER_OTG_REG8_otg_hmos_START   (2)
#define SOC_SCHARGER_OTG_REG8_otg_hmos_END     (2)
#define SOC_SCHARGER_OTG_REG8_otg_cmp_START    (3)
#define SOC_SCHARGER_OTG_REG8_otg_cmp_END      (3)
#define SOC_SCHARGER_OTG_REG8_otg_phase_START  (4)
#define SOC_SCHARGER_OTG_REG8_otg_phase_END    (5)
#define SOC_SCHARGER_OTG_REG8_otg_rf_START     (6)
#define SOC_SCHARGER_OTG_REG8_otg_rf_END       (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_OTG_REG9_UNION
 结构说明  : OTG_REG9 寄存器结构定义。地址偏移量:0x89，初值:0x05，宽度:8
 寄存器说明: OTG内部延时调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otg_delay2 : 2;  /* bit[0-1]: OTG内部延时调整：
                                                     00：
                                                     01：
                                                     10：
                                                     11： */
        unsigned char  otg_delay1 : 2;  /* bit[2-3]: OTG内部延时调整：
                                                     00：
                                                     01：
                                                     10：
                                                     11： */
        unsigned char  reserved   : 4;  /* bit[4-7]: 保留。 */
    } reg;
} SOC_SCHARGER_OTG_REG9_UNION;
#endif
#define SOC_SCHARGER_OTG_REG9_otg_delay2_START  (0)
#define SOC_SCHARGER_OTG_REG9_otg_delay2_END    (1)
#define SOC_SCHARGER_OTG_REG9_otg_delay1_START  (2)
#define SOC_SCHARGER_OTG_REG9_otg_delay1_END    (3)


/*****************************************************************************
 结构名    : SOC_SCHARGER_OTG_TRIM1_UNION
 结构说明  : OTG_TRIM1 寄存器结构定义。地址偏移量:0x8A，初值:0x00，宽度:8
 寄存器说明: OTG_TRIM调整1寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otg_trim1 : 8;  /* bit[0-7]: OTG trim调整 */
    } reg;
} SOC_SCHARGER_OTG_TRIM1_UNION;
#endif
#define SOC_SCHARGER_OTG_TRIM1_otg_trim1_START  (0)
#define SOC_SCHARGER_OTG_TRIM1_otg_trim1_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_OTG_TRIM2_UNION
 结构说明  : OTG_TRIM2 寄存器结构定义。地址偏移量:0x8B，初值:0x00，宽度:8
 寄存器说明: OTG_TRIM调整2寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otg_trim2 : 8;  /* bit[0-7]: OTG trim调整 */
    } reg;
} SOC_SCHARGER_OTG_TRIM2_UNION;
#endif
#define SOC_SCHARGER_OTG_TRIM2_otg_trim2_START  (0)
#define SOC_SCHARGER_OTG_TRIM2_otg_trim2_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_OTG_RESERVE_UNION
 结构说明  : OTG_RESERVE 寄存器结构定义。地址偏移量:0x8C，初值:0x00，宽度:8
 寄存器说明: OTG预留0寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otg_resved : 8;  /* bit[0-7]: 预留寄存器 */
    } reg;
} SOC_SCHARGER_OTG_RESERVE_UNION;
#endif
#define SOC_SCHARGER_OTG_RESERVE_otg_resved_START  (0)
#define SOC_SCHARGER_OTG_RESERVE_otg_resved_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_OTG_RESERVE1_UNION
 结构说明  : OTG_RESERVE1 寄存器结构定义。地址偏移量:0x8D，初值:0x00，宽度:8
 寄存器说明: OTG预留1寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otg_resved1 : 8;  /* bit[0-7]: 预留寄存器 */
    } reg;
} SOC_SCHARGER_OTG_RESERVE1_UNION;
#endif
#define SOC_SCHARGER_OTG_RESERVE1_otg_resved1_START  (0)
#define SOC_SCHARGER_OTG_RESERVE1_otg_resved1_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_OTG_RESERVE2_UNION
 结构说明  : OTG_RESERVE2 寄存器结构定义。地址偏移量:0x8E，初值:0x00，宽度:8
 寄存器说明: OTG预留2寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otg_resved2 : 8;  /* bit[0-7]: 预留寄存器 */
    } reg;
} SOC_SCHARGER_OTG_RESERVE2_UNION;
#endif
#define SOC_SCHARGER_OTG_RESERVE2_otg_resved2_START  (0)
#define SOC_SCHARGER_OTG_RESERVE2_otg_resved2_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_CHG_REG0_UNION
 结构说明  : CHG_REG0 寄存器结构定义。地址偏移量:0x90，初值:0x14，宽度:8
 寄存器说明: CHG_REG0调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_pre_vchg    : 2;  /* bit[0-1]: 预充电电压阈值大小调节位：
                                                          00：2.8V；
                                                          01：3.0V；
                                                          10：3.1V；
                                                          11：3.2V。 */
        unsigned char  chg_pre_ichg    : 2;  /* bit[2-3]: 预充电电流大小调节位：
                                                          00：100mA；
                                                          01：200mA；
                                                          10：300mA；
                                                          11：400mA。 */
        unsigned char  batfet_ctrl_cfg : 1;  /* bit[4]  : batfet_ctrl配置寄存器
                                                          该寄存器除了受到pwr_rst_n复位外，还受到模拟送给数字另外一个信号dc_plug_n控制：
                                                          0：关闭batfet；
                                                          1：打开batfet。 */
        unsigned char  chg_en          : 1;  /* bit[5]  : charger使能信号：
                                                          0：关闭；
                                                          1：使能。 */
        unsigned char  reserved        : 2;  /* bit[6-7]: 保留。 */
    } reg;
} SOC_SCHARGER_CHG_REG0_UNION;
#endif
#define SOC_SCHARGER_CHG_REG0_chg_pre_vchg_START     (0)
#define SOC_SCHARGER_CHG_REG0_chg_pre_vchg_END       (1)
#define SOC_SCHARGER_CHG_REG0_chg_pre_ichg_START     (2)
#define SOC_SCHARGER_CHG_REG0_chg_pre_ichg_END       (3)
#define SOC_SCHARGER_CHG_REG0_batfet_ctrl_cfg_START  (4)
#define SOC_SCHARGER_CHG_REG0_batfet_ctrl_cfg_END    (4)
#define SOC_SCHARGER_CHG_REG0_chg_en_START           (5)
#define SOC_SCHARGER_CHG_REG0_chg_en_END             (5)


/*****************************************************************************
 结构名    : SOC_SCHARGER_CHG_REG1_UNION
 结构说明  : CHG_REG1 寄存器结构定义。地址偏移量:0x91，初值:0x0E，宽度:8
 寄存器说明: CHG_REG1调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_fast_ichg : 5;  /* bit[0-4]: 快充电电流大小调节位：
                                                        00000：100mA；
                                                        00001：200mA；
                                                        00010：300mA；
                                                        00011：400mA；
                                                        00100：500mA；
                                                        00101：600mA；
                                                        00110：700mA；
                                                        00111：800mA；
                                                        01000：900mA；
                                                        01001：1000mA；
                                                        01010：1200mA；
                                                        01011：1400mA；
                                                        01100：1600mA；
                                                        01101：1800mA；
                                                        01110：2000mA；
                                                        01111：2100mA；
                                                        10000：2200mA；
                                                        10001：2300mA；
                                                        10010：2400mA；
                                                        10011：2500mA；
                                                        10100：2600mA；
                                                        10101：2700mA；
                                                        10110：2800mA；
                                                        10111：2900mA；
                                                        11000：3000mA；
                                                        11001：3200mA；
                                                        11010：3400mA；
                                                        11011：3600mA；
                                                        11100：3800mA；
                                                        11101：4000mA；
                                                        11110：4200mA；
                                                        11111：4500mA。 */
        unsigned char  reserved      : 3;  /* bit[5-7]: 保留。 */
    } reg;
} SOC_SCHARGER_CHG_REG1_UNION;
#endif
#define SOC_SCHARGER_CHG_REG1_chg_fast_ichg_START  (0)
#define SOC_SCHARGER_CHG_REG1_chg_fast_ichg_END    (4)


/*****************************************************************************
 结构名    : SOC_SCHARGER_CHG_REG2_UNION
 结构说明  : CHG_REG2 寄存器结构定义。地址偏移量:0x92，初值:0x5A，宽度:8
 寄存器说明: CHG_REG2调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_term_ichg : 3;  /* bit[0-2]: 终止充电电流阈值调节位：
                                                        000：50mA；
                                                        001：100mA；
                                                        010：150mA；
                                                        011：200mA；
                                                        100：300mA；
                                                        101：400mA；
                                                        110：500mA；
                                                        111：600mA。 */
        unsigned char  chg_fast_vchg : 4;  /* bit[3-6]: 快充电完成电压阈值大小调节位：
                                                        0000：3.8V；
                                                        0001：3.85V；
                                                        0010：3.9V；
                                                        0011：3.95V；
                                                        0100：4V；
                                                        0101：4.05V；
                                                        0110：4.1V；
                                                        0111：4.15V；
                                                        1000：4.2；
                                                        1001：4.25；
                                                        1010：4.3；
                                                        1011：4.35；
                                                        1100：4.4；
                                                        1101：4.45；
                                                        1110：4.5；
                                                        1111：4.5。 */
        unsigned char  reserved      : 1;  /* bit[7]  : 保留。 */
    } reg;
} SOC_SCHARGER_CHG_REG2_UNION;
#endif
#define SOC_SCHARGER_CHG_REG2_chg_term_ichg_START  (0)
#define SOC_SCHARGER_CHG_REG2_chg_term_ichg_END    (2)
#define SOC_SCHARGER_CHG_REG2_chg_fast_vchg_START  (3)
#define SOC_SCHARGER_CHG_REG2_chg_fast_vchg_END    (6)


/*****************************************************************************
 结构名    : SOC_SCHARGER_CHG_REG3_UNION
 结构说明  : CHG_REG3 寄存器结构定义。地址偏移量:0x93，初值:0x40，宽度:8
 寄存器说明: CHG_REG3调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_gap_set       : 2;  /* bit[0-1]: SYS to BAT backward voltage gap调节位：
                                                            00：30mV；
                                                            01：10mV；
                                                            10：40mV；
                                                            11：50mV。 */
        unsigned char  chg_fastchg_timer : 2;  /* bit[2-3]: 快充安全计时器（小时）：
                                                            00：5 h；
                                                            01：8 h；
                                                            10：12 h；
                                                            11：20 h。 */
        unsigned char  chg_prechg_timer  : 2;  /* bit[4-5]: 预充电计时器（分钟）：
                                                            00：30min；
                                                            01：45min；
                                                            10：60min；
                                                            11：75min。 */
        unsigned char  chg_vrechg_hys    : 2;  /* bit[6-7]: 重新充电回滞电压调节位：
                                                            00：50mV；
                                                            01：100mV；
                                                            10：150mV；
                                                            11：200mV； */
    } reg;
} SOC_SCHARGER_CHG_REG3_UNION;
#endif
#define SOC_SCHARGER_CHG_REG3_chg_gap_set_START        (0)
#define SOC_SCHARGER_CHG_REG3_chg_gap_set_END          (1)
#define SOC_SCHARGER_CHG_REG3_chg_fastchg_timer_START  (2)
#define SOC_SCHARGER_CHG_REG3_chg_fastchg_timer_END    (3)
#define SOC_SCHARGER_CHG_REG3_chg_prechg_timer_START   (4)
#define SOC_SCHARGER_CHG_REG3_chg_prechg_timer_END     (5)
#define SOC_SCHARGER_CHG_REG3_chg_vrechg_hys_START     (6)
#define SOC_SCHARGER_CHG_REG3_chg_vrechg_hys_END       (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_CHG_REG4_UNION
 结构说明  : CHG_REG4 寄存器结构定义。地址偏移量:0x94，初值:0x04，宽度:8
 寄存器说明: CHG_REG4调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_bat_open     : 1;  /* bit[0]  : 电池不在位指示：
                                                           0：电池在位；
                                                           1：电池不在位。 */
        unsigned char  chg_clk_div2_shd : 1;  /* bit[1]  : 快充安全计时器在热调整和DPM过程中放缓2倍计数功能屏蔽位：
                                                           0：2X功能不屏蔽；
                                                           1：2X功能屏蔽。 */
        unsigned char  chg_en_term      : 1;  /* bit[2]  : 终止充电控制位：
                                                           0：Disabled；
                                                           1：Enabled。 */
        unsigned char  reserved         : 5;  /* bit[3-7]: 保留。 */
    } reg;
} SOC_SCHARGER_CHG_REG4_UNION;
#endif
#define SOC_SCHARGER_CHG_REG4_chg_bat_open_START      (0)
#define SOC_SCHARGER_CHG_REG4_chg_bat_open_END        (0)
#define SOC_SCHARGER_CHG_REG4_chg_clk_div2_shd_START  (1)
#define SOC_SCHARGER_CHG_REG4_chg_clk_div2_shd_END    (1)
#define SOC_SCHARGER_CHG_REG4_chg_en_term_START       (2)
#define SOC_SCHARGER_CHG_REG4_chg_en_term_END         (2)


/*****************************************************************************
 结构名    : SOC_SCHARGER_CHG_REG5_UNION
 结构说明  : CHG_REG5 寄存器结构定义。地址偏移量:0x95，初值:0x00，宽度:8
 寄存器说明: CHG_REG5调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_vclamp_set : 3;  /* bit[0-2]: 电池通道电阻补偿钳位电压：
                                                         000：0mV；
                                                         001：50mV；
                                                         010：100mV；
                                                         011：150mV；
                                                         000：200mV；
                                                         101：250mV；
                                                         110：300mV；
                                                         111：350mV。 */
        unsigned char  chg_ir_set     : 3;  /* bit[3-5]: 电池通道电阻补偿：
                                                         000：0mohm；
                                                         001：15mohm；
                                                         010：30mohm；
                                                         011：45mohm；
                                                         100：60mohm；
                                                         101：75mohm；
                                                         110：95mohm；
                                                         111：110mohm。 */
        unsigned char  reserved       : 2;  /* bit[6-7]: 保留。 */
    } reg;
} SOC_SCHARGER_CHG_REG5_UNION;
#endif
#define SOC_SCHARGER_CHG_REG5_chg_vclamp_set_START  (0)
#define SOC_SCHARGER_CHG_REG5_chg_vclamp_set_END    (2)
#define SOC_SCHARGER_CHG_REG5_chg_ir_set_START      (3)
#define SOC_SCHARGER_CHG_REG5_chg_ir_set_END        (5)


/*****************************************************************************
 结构名    : SOC_SCHARGER_CHG_VRES_SEL_UNION
 结构说明  : CHG_VRES_SEL 寄存器结构定义。地址偏移量:0x96，初值:0x05，宽度:8
 寄存器说明: CHARGER环路补偿mos电阻调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_vres2_sel : 2;  /* bit[0-1]: charger环路补偿mos电阻调节 */
        unsigned char  chg_vres1_sel : 2;  /* bit[2-3]: charger环路补偿mos电阻调节 */
        unsigned char  reserved      : 4;  /* bit[4-7]: 保留。 */
    } reg;
} SOC_SCHARGER_CHG_VRES_SEL_UNION;
#endif
#define SOC_SCHARGER_CHG_VRES_SEL_chg_vres2_sel_START  (0)
#define SOC_SCHARGER_CHG_VRES_SEL_chg_vres2_sel_END    (1)
#define SOC_SCHARGER_CHG_VRES_SEL_chg_vres1_sel_START  (2)
#define SOC_SCHARGER_CHG_VRES_SEL_chg_vres1_sel_END    (3)


/*****************************************************************************
 结构名    : SOC_SCHARGER_CHG_CAP_SEL_UNION
 结构说明  : CHG_CAP_SEL 寄存器结构定义。地址偏移量:0x97，初值:0x55，宽度:8
 寄存器说明: CHARGER环路补偿电容调节。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_cap4_sel : 2;  /* bit[0-1]: charger环路补偿电容调节：
                                                       00：3pF；
                                                       01：6pF；
                                                       10：9pF；
                                                       11：12pF。 */
        unsigned char  chg_cap3_sel : 2;  /* bit[2-3]: charger环路补偿电容调节：
                                                       00：4.4pF；
                                                       01：8.8pF；
                                                       10：13.2pF；
                                                       11：15.6pF。 */
        unsigned char  chg_cap2_sel : 2;  /* bit[4-5]: charger环路补偿电容调节：
                                                       00：2.2pF；
                                                       01：4.4pF；
                                                       10：6.6pF；
                                                       11：8.8pF。 */
        unsigned char  chg_cap1_sel : 2;  /* bit[6-7]: charger环路补偿电容调节：
                                                       00：1.1pF；
                                                       01：2.2pF；
                                                       10：3.3pF；
                                                       11：4.4pF。 */
    } reg;
} SOC_SCHARGER_CHG_CAP_SEL_UNION;
#endif
#define SOC_SCHARGER_CHG_CAP_SEL_chg_cap4_sel_START  (0)
#define SOC_SCHARGER_CHG_CAP_SEL_chg_cap4_sel_END    (1)
#define SOC_SCHARGER_CHG_CAP_SEL_chg_cap3_sel_START  (2)
#define SOC_SCHARGER_CHG_CAP_SEL_chg_cap3_sel_END    (3)
#define SOC_SCHARGER_CHG_CAP_SEL_chg_cap2_sel_START  (4)
#define SOC_SCHARGER_CHG_CAP_SEL_chg_cap2_sel_END    (5)
#define SOC_SCHARGER_CHG_CAP_SEL_chg_cap1_sel_START  (6)
#define SOC_SCHARGER_CHG_CAP_SEL_chg_cap1_sel_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_CHG_REG6_UNION
 结构说明  : CHG_REG6 寄存器结构定义。地址偏移量:0x98，初值:0x40，宽度:8
 寄存器说明: CHG_REG6调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_ios_adj_ir : 5;  /* bit[0-4]: 充电电流检测失调校正：
                                                         00000：0mA；
                                                         00001：-25mA；
                                                         00010：-50mA；
                                                         00011：-75mA；
                                                         …
                                                         …
                                                         01111：-375mA；
                                                         10000：+25mA；
                                                         10001：+50mA；
                                                         10010：+75mA；
                                                         10011：+100mA；
                                                         …
                                                         …
                                                         11111：+400mA。 */
        unsigned char  chg_rechg_time : 2;  /* bit[5-6]: 重新充电模式去抖时间设置位：
                                                         00：0.1s；
                                                         01：1s；
                                                         10：2s；
                                                         11：4s； */
        unsigned char  reserved       : 1;  /* bit[7]  : 保留。 */
    } reg;
} SOC_SCHARGER_CHG_REG6_UNION;
#endif
#define SOC_SCHARGER_CHG_REG6_chg_ios_adj_ir_START  (0)
#define SOC_SCHARGER_CHG_REG6_chg_ios_adj_ir_END    (4)
#define SOC_SCHARGER_CHG_REG6_chg_rechg_time_START  (5)
#define SOC_SCHARGER_CHG_REG6_chg_rechg_time_END    (6)


/*****************************************************************************
 结构名    : SOC_SCHARGER_CHG_REG7_UNION
 结构说明  : CHG_REG7 寄存器结构定义。地址偏移量:0x99，初值:0x00，宽度:8
 寄存器说明: CHG_REG7调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_iscale_adj_gap : 3;  /* bit[0-2]: 充电电流检测比例校正：
                                                             000：1X；
                                                             001：1.042X；
                                                             010：1.087X；
                                                             011：1.136X；
                                                             100：0.962X；
                                                             101：0.926X；
                                                             110：0.893X；
                                                             111：0.862X。 */
        unsigned char  chg_iscale_adj_ir  : 4;  /* bit[3-6]: 充电电流检测比例校正：
                                                             0000：1X；
                                                             0001：1.020X；
                                                             0010：1.042X；
                                                             0011：1.064X；
                                                             0100：1.087X；
                                                             0101：1.111X；
                                                             0110：1.136X；
                                                             0111：1.163X；
                                                             1000：0.980X；
                                                             1001：0.962X；
                                                             1010：0.943X；
                                                             1011：0.926X；
                                                             1100：0.909X；
                                                             1101：0.893X；
                                                             1110：0.877X；
                                                             1111：0.862X。 */
        unsigned char  reserved           : 1;  /* bit[7]  : 保留。 */
    } reg;
} SOC_SCHARGER_CHG_REG7_UNION;
#endif
#define SOC_SCHARGER_CHG_REG7_chg_iscale_adj_gap_START  (0)
#define SOC_SCHARGER_CHG_REG7_chg_iscale_adj_gap_END    (2)
#define SOC_SCHARGER_CHG_REG7_chg_iscale_adj_ir_START   (3)
#define SOC_SCHARGER_CHG_REG7_chg_iscale_adj_ir_END     (6)


/*****************************************************************************
 结构名    : SOC_SCHARGER_CHG_REG8_UNION
 结构说明  : CHG_REG8 寄存器结构定义。地址偏移量:0x9A，初值:0x00，宽度:8
 寄存器说明: CHG_REG8调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_ios_adj_gap : 5;  /* bit[0-4]: 充电电流检测失调校正：
                                                          00000：0mA；
                                                          00001：-25mA；
                                                          00010：-50mA；
                                                          00011：-75mA；
                                                          …
                                                          …
                                                          01111：-375mA；
                                                          10000：+25mA；
                                                          10001：+50mA；
                                                          10010：+75mA；
                                                          10011：+100mA；
                                                          …
                                                          …
                                                          11111：+400mA。 */
        unsigned char  reserved        : 3;  /* bit[5-7]: 保留。 */
    } reg;
} SOC_SCHARGER_CHG_REG8_UNION;
#endif
#define SOC_SCHARGER_CHG_REG8_chg_ios_adj_gap_START  (0)
#define SOC_SCHARGER_CHG_REG8_chg_ios_adj_gap_END    (4)


/*****************************************************************************
 结构名    : SOC_SCHARGER_CHG_REG9_UNION
 结构说明  : CHG_REG9 寄存器结构定义。地址偏移量:0x9B，初值:0x02，宽度:8
 寄存器说明: CHG_REG9调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_cp_src_sel : 1;  /* bit[0]  : charge pump输入电源选择：
                                                         0：选择battery；
                                                         1：选择avdd_bas。 */
        unsigned char  chg_iref_clamp : 2;  /* bit[1-2]: 充电电流参考电压钳位：
                                                         00：100mV；
                                                         01：150mV；
                                                         10：200mV；
                                                         11：250mV。 */
        unsigned char  chg_ocp_shd    : 1;  /* bit[3]  : 放电电流ocp保护屏蔽位：
                                                         0：不屏蔽；
                                                         1：屏蔽。 */
        unsigned char  chg_cv_adj     : 4;  /* bit[4-7]: cv寄存器修调位：
                                                         0000：0mV；
                                                         0001：-12.5mV；
                                                         0010：-25mV；
                                                         0011：-37.5mV；
                                                         0100：-50mV；
                                                         0101：-62.5mV；
                                                         0110：-75mV；
                                                         0111：-87.5mV；
                                                         1000：+12.5mV；
                                                         1001：+25mV；
                                                         1010：+37.5mV；
                                                         1011：+50mV；
                                                         1100：+62.5mV；
                                                         1101：+75mV；
                                                         1110：+87.5mV；
                                                         1111：+100mV。 */
    } reg;
} SOC_SCHARGER_CHG_REG9_UNION;
#endif
#define SOC_SCHARGER_CHG_REG9_chg_cp_src_sel_START  (0)
#define SOC_SCHARGER_CHG_REG9_chg_cp_src_sel_END    (0)
#define SOC_SCHARGER_CHG_REG9_chg_iref_clamp_START  (1)
#define SOC_SCHARGER_CHG_REG9_chg_iref_clamp_END    (2)
#define SOC_SCHARGER_CHG_REG9_chg_ocp_shd_START     (3)
#define SOC_SCHARGER_CHG_REG9_chg_ocp_shd_END       (3)
#define SOC_SCHARGER_CHG_REG9_chg_cv_adj_START      (4)
#define SOC_SCHARGER_CHG_REG9_chg_cv_adj_END        (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_CHG_RESVI1_UNION
 结构说明  : CHG_RESVI1 寄存器结构定义。地址偏移量:0x9C，初值:0x00，宽度:8
 寄存器说明: CHG_RESVI1预留寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_resvi1 : 8;  /* bit[0-7]: 预留寄存器 */
    } reg;
} SOC_SCHARGER_CHG_RESVI1_UNION;
#endif
#define SOC_SCHARGER_CHG_RESVI1_chg_resvi1_START  (0)
#define SOC_SCHARGER_CHG_RESVI1_chg_resvi1_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_CHG_RESVI2_UNION
 结构说明  : CHG_RESVI2 寄存器结构定义。地址偏移量:0x9D，初值:0x00，宽度:8
 寄存器说明: CHG_RESVI2预留寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_resvi2 : 8;  /* bit[0-7]: 预留寄存器 */
    } reg;
} SOC_SCHARGER_CHG_RESVI2_UNION;
#endif
#define SOC_SCHARGER_CHG_RESVI2_chg_resvi2_START  (0)
#define SOC_SCHARGER_CHG_RESVI2_chg_resvi2_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_CHG_RESVO1_UNION
 结构说明  : CHG_RESVO1 寄存器结构定义。地址偏移量:0x9E，初值:0x00，宽度:8
 寄存器说明: CHG_RESVO1预留寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_resvo1 : 8;  /* bit[0-7]: <7:1>预留寄存器
                                                     <0>400mA以下快充档位模式选择：
                                                     0:IR模式；
                                                     1：GAP模式。 */
    } reg;
} SOC_SCHARGER_CHG_RESVO1_UNION;
#endif
#define SOC_SCHARGER_CHG_RESVO1_chg_resvo1_START  (0)
#define SOC_SCHARGER_CHG_RESVO1_chg_resvo1_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_CHG_RESVO2_UNION
 结构说明  : CHG_RESVO2 寄存器结构定义。地址偏移量:0x9F，初值:0x00，宽度:8
 寄存器说明: CHG_RESVO2预留寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_resvo2 : 8;  /* bit[0-7]: 预留寄存器 */
    } reg;
} SOC_SCHARGER_CHG_RESVO2_UNION;
#endif
#define SOC_SCHARGER_CHG_RESVO2_chg_resvo2_START  (0)
#define SOC_SCHARGER_CHG_RESVO2_chg_resvo2_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_DET_TOP_REG0_UNION
 结构说明  : DET_TOP_REG0 寄存器结构定义。地址偏移量:0xA0，初值:0x02，宽度:8
 寄存器说明: DET_TOP_REG0调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  bat_gd_shield : 1;  /* bit[0]  : 强制使bat_gd为高：
                                                        0：不强制，由模拟判断bat_gd是否为高电平；
                                                        1：强制使bat_gd为高电平。 */
        unsigned char  bat_gd_sel    : 1;  /* bit[1]  : OTG开启的电池电压判断档位选择：
                                                        0：3V；
                                                        1：2.8V。 */
        unsigned char  slp_vset      : 1;  /* bit[2]  : sleep点退出的档位选择：
                                                        0：sleep点退出为80mV；
                                                        1：sleep点退出为120mV。 */
        unsigned char  vbus_vset     : 2;  /* bit[3-4]: 适配器输入电压档位配置：
                                                        00：5V；
                                                        01：9V；
                                                        10&amp;11：12V。 */
        unsigned char  ts_ctrl       : 1;  /* bit[5]  : 控制电池温度检测模块：
                                                        0：关闭；
                                                        1：开启。 */
        unsigned char  reserved      : 2;  /* bit[6-7]: 保留。 */
    } reg;
} SOC_SCHARGER_DET_TOP_REG0_UNION;
#endif
#define SOC_SCHARGER_DET_TOP_REG0_bat_gd_shield_START  (0)
#define SOC_SCHARGER_DET_TOP_REG0_bat_gd_shield_END    (0)
#define SOC_SCHARGER_DET_TOP_REG0_bat_gd_sel_START     (1)
#define SOC_SCHARGER_DET_TOP_REG0_bat_gd_sel_END       (1)
#define SOC_SCHARGER_DET_TOP_REG0_slp_vset_START       (2)
#define SOC_SCHARGER_DET_TOP_REG0_slp_vset_END         (2)
#define SOC_SCHARGER_DET_TOP_REG0_vbus_vset_START      (3)
#define SOC_SCHARGER_DET_TOP_REG0_vbus_vset_END        (4)
#define SOC_SCHARGER_DET_TOP_REG0_ts_ctrl_START        (5)
#define SOC_SCHARGER_DET_TOP_REG0_ts_ctrl_END          (5)


/*****************************************************************************
 结构名    : SOC_SCHARGER_DET_TOP_REG1_UNION
 结构说明  : DET_TOP_REG1 寄存器结构定义。地址偏移量:0xA1，初值:0x0A，宽度:8
 寄存器说明: DET_TOP_REG1调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  chg_hot_hsys  : 2;  /* bit[0-1]: 电池过热检测的回滞温度调整：
                                                        00：1%；
                                                        01：2%；
                                                        10：3%；
                                                        11：4%。 */
        unsigned char  chg_cold_hsys : 2;  /* bit[2-3]: 电池过冷检测的回滞温度调整：
                                                        00：1%；
                                                        01：2%；
                                                        10：3%；
                                                        11：4%。 */
        unsigned char  reserved      : 4;  /* bit[4-7]: 保留。 */
    } reg;
} SOC_SCHARGER_DET_TOP_REG1_UNION;
#endif
#define SOC_SCHARGER_DET_TOP_REG1_chg_hot_hsys_START   (0)
#define SOC_SCHARGER_DET_TOP_REG1_chg_hot_hsys_END     (1)
#define SOC_SCHARGER_DET_TOP_REG1_chg_cold_hsys_START  (2)
#define SOC_SCHARGER_DET_TOP_REG1_chg_cold_hsys_END    (3)


/*****************************************************************************
 结构名    : SOC_SCHARGER_THSD_ADJ_UNION
 结构说明  : THSD_ADJ 寄存器结构定义。地址偏移量:0xA2，初值:0x02，宽度:8
 寄存器说明: THSD调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  thsd_treg_set : 2;  /* bit[0-1]: 热调整温度档位选择：
                                                        00：60度；
                                                        01：80度；
                                                        10：100度；
                                                        11：120度。 */
        unsigned char  reserved      : 6;  /* bit[2-7]: 保留。 */
    } reg;
} SOC_SCHARGER_THSD_ADJ_UNION;
#endif
#define SOC_SCHARGER_THSD_ADJ_thsd_treg_set_START  (0)
#define SOC_SCHARGER_THSD_ADJ_thsd_treg_set_END    (1)


/*****************************************************************************
 结构名    : SOC_SCHARGER_SCHG_LOGIC_CTRL_UNION
 结构说明  : SCHG_LOGIC_CTRL 寄存器结构定义。地址偏移量:0xA3，初值:0x00，宽度:8
 寄存器说明: SCHG_LOGIC控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  buck_enb        : 1;  /* bit[0]  : buck强制关闭控制：
                                                          0：buck使能由模拟自动控制；
                                                          1：buck强制关闭。 */
        unsigned char  timer_test      : 1;  /* bit[1]  : 计时器测试模式：
                                                          0：芯片正常工作模式；
                                                          1：测试模式，通过该信号选择计时时间短的计时，方便测试。 */
        unsigned char  regn_ocp_shield : 1;  /* bit[2]  : regn ocp信号的屏蔽信号：
                                                          0：不屏蔽regn_ocp；
                                                          1：屏蔽regn_ocp。 */
        unsigned char  reserved        : 5;  /* bit[3-7]: 保留。 */
    } reg;
} SOC_SCHARGER_SCHG_LOGIC_CTRL_UNION;
#endif
#define SOC_SCHARGER_SCHG_LOGIC_CTRL_buck_enb_START         (0)
#define SOC_SCHARGER_SCHG_LOGIC_CTRL_buck_enb_END           (0)
#define SOC_SCHARGER_SCHG_LOGIC_CTRL_timer_test_START       (1)
#define SOC_SCHARGER_SCHG_LOGIC_CTRL_timer_test_END         (1)
#define SOC_SCHARGER_SCHG_LOGIC_CTRL_regn_ocp_shield_START  (2)
#define SOC_SCHARGER_SCHG_LOGIC_CTRL_regn_ocp_shield_END    (2)


/*****************************************************************************
 结构名    : SOC_SCHARGER_BLOCK_CTRL_UNION
 结构说明  : BLOCK_CTRL 寄存器结构定义。地址偏移量:0xA4，初值:0x00，宽度:8
 寄存器说明: BLOCK调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  otg_500ma_mos : 1;  /* bit[0]  : OTG 500mA限流时BLOCK管比例选择：
                                                        0：20m ohm导通阻抗；
                                                        1：100m ohm导通阻抗。 */
        unsigned char  gate_gnd_ctrl : 1;  /* bit[1]  : BLOCK管拉低选择：
                                                        0：block gate拉至vbus；
                                                        1：block gate拉至gnd。 */
        unsigned char  reserved      : 6;  /* bit[2-7]: 保留。 */
    } reg;
} SOC_SCHARGER_BLOCK_CTRL_UNION;
#endif
#define SOC_SCHARGER_BLOCK_CTRL_otg_500ma_mos_START  (0)
#define SOC_SCHARGER_BLOCK_CTRL_otg_500ma_mos_END    (0)
#define SOC_SCHARGER_BLOCK_CTRL_gate_gnd_ctrl_START  (1)
#define SOC_SCHARGER_BLOCK_CTRL_gate_gnd_ctrl_END    (1)


/*****************************************************************************
 结构名    : SOC_SCHARGER_REF_TOP_CTRL_UNION
 结构说明  : REF_TOP_CTRL 寄存器结构定义。地址偏移量:0xA5，初值:0x80，宽度:8
 寄存器说明: REF_TOP调节寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  ref_trim        : 7;  /* bit[0-6]: 对未修调的芯片进行编程，以便于在实验室修调基准电压VREF。 */
        unsigned char  ibias_switch_en : 1;  /* bit[7]  : 0：不使能电流切换功能；
                                                          1：使能电流切换功能。 */
    } reg;
} SOC_SCHARGER_REF_TOP_CTRL_UNION;
#endif
#define SOC_SCHARGER_REF_TOP_CTRL_ref_trim_START         (0)
#define SOC_SCHARGER_REF_TOP_CTRL_ref_trim_END           (6)
#define SOC_SCHARGER_REF_TOP_CTRL_ibias_switch_en_START  (7)
#define SOC_SCHARGER_REF_TOP_CTRL_ibias_switch_en_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_ADC_CTRL_UNION
 结构说明  : ADC_CTRL 寄存器结构定义。地址偏移量:0xB0，初值:0x00，宽度:8
 寄存器说明: ADC控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  hkadc_ch_sel   : 2;  /* bit[0-1]: HKADC 工作通道选择寄存器；默认0； */
        unsigned char  hkadc_div_freq : 1;  /* bit[2]  : HKADC工作频率降频，默认0，不降频（支持5K 采样率） */
        unsigned char  hkadc_reset    : 1;  /* bit[3]  : HKADC内部 逻辑复位控制：
                                                         0：不复位；
                                                         1：强制复位。 */
        unsigned char  hkadc_en       : 1;  /* bit[4]  : HKADC使能：（默认0）
                                                         0：不开启；
                                                         1：开启。 */
        unsigned char  reserved       : 3;  /* bit[5-7]: 保留。 */
    } reg;
} SOC_SCHARGER_ADC_CTRL_UNION;
#endif
#define SOC_SCHARGER_ADC_CTRL_hkadc_ch_sel_START    (0)
#define SOC_SCHARGER_ADC_CTRL_hkadc_ch_sel_END      (1)
#define SOC_SCHARGER_ADC_CTRL_hkadc_div_freq_START  (2)
#define SOC_SCHARGER_ADC_CTRL_hkadc_div_freq_END    (2)
#define SOC_SCHARGER_ADC_CTRL_hkadc_reset_START     (3)
#define SOC_SCHARGER_ADC_CTRL_hkadc_reset_END       (3)
#define SOC_SCHARGER_ADC_CTRL_hkadc_en_START        (4)
#define SOC_SCHARGER_ADC_CTRL_hkadc_en_END          (4)


/*****************************************************************************
 结构名    : SOC_SCHARGER_ADC_START_UNION
 结构说明  : ADC_START 寄存器结构定义。地址偏移量:0xB1，初值:0x00，宽度:8
 寄存器说明: ADC转换开始寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  hkadc_start    : 1;  /* bit[0]  : HKADC启动设置寄存器；默认0，写一次地址0xB1（无论0或1），该寄存器发生一次翻转，触发一次数据转换
                                                         （注：禁止在HKADC发起hkadc_start后，转换过程中(hkadc_valid=0)重复发起hkadc_start信号，否则hkadc内部逻辑会发生混乱，需要重新开关hkadc或进行hkadc_reset置‘1’强制逻辑复位）
                                                         注：需要至少持续3个hkadc工作时钟clk周期（不降频为3个125k时钟，降频为3个62.5k时钟）后再清零 */
        unsigned char  hkadc_reserved : 7;  /* bit[1-7]: 保留。 */
    } reg;
} SOC_SCHARGER_ADC_START_UNION;
#endif
#define SOC_SCHARGER_ADC_START_hkadc_start_START     (0)
#define SOC_SCHARGER_ADC_START_hkadc_start_END       (0)
#define SOC_SCHARGER_ADC_START_hkadc_reserved_START  (1)
#define SOC_SCHARGER_ADC_START_hkadc_reserved_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_ADC_CONV_STATUS_UNION
 结构说明  : ADC_CONV_STATUS 寄存器结构定义。地址偏移量:0xB2，初值:0x00，宽度:8
 寄存器说明: ADC转换状态指示寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  hkadc_valid : 1;  /* bit[0]  : HKADC状态输出寄存器：
                                                      0：转换过程中；
                                                      1：转换完毕。
                                                      (注：该bit在转换开始时，被拉低；在转换结束后，变成“1”，并且“1”一直持续到下一次转换开始) */
        unsigned char  reserved    : 7;  /* bit[1-7]: 保留。 */
    } reg;
} SOC_SCHARGER_ADC_CONV_STATUS_UNION;
#endif
#define SOC_SCHARGER_ADC_CONV_STATUS_hkadc_valid_START  (0)
#define SOC_SCHARGER_ADC_CONV_STATUS_hkadc_valid_END    (0)


/*****************************************************************************
 结构名    : SOC_SCHARGER_ADC_DATA1_UNION
 结构说明  : ADC_DATA1 寄存器结构定义。地址偏移量:0xB3，初值:0x00，宽度:8
 寄存器说明: ADC转换结果高位寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  hkadc_data11_8 : 4;  /* bit[0-3]: ADC转换结果高4位bit[11:8]。 */
        unsigned char  reserved       : 4;  /* bit[4-7]: 保留。 */
    } reg;
} SOC_SCHARGER_ADC_DATA1_UNION;
#endif
#define SOC_SCHARGER_ADC_DATA1_hkadc_data11_8_START  (0)
#define SOC_SCHARGER_ADC_DATA1_hkadc_data11_8_END    (3)


/*****************************************************************************
 结构名    : SOC_SCHARGER_ADC_DATA0_UNION
 结构说明  : ADC_DATA0 寄存器结构定义。地址偏移量:0xB4，初值:0x00，宽度:8
 寄存器说明: ADC转换结果低位寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  hkadc_data7_0 : 8;  /* bit[0-7]: ADC转换结果低8位bit[7:0]。 */
    } reg;
} SOC_SCHARGER_ADC_DATA0_UNION;
#endif
#define SOC_SCHARGER_ADC_DATA0_hkadc_data7_0_START  (0)
#define SOC_SCHARGER_ADC_DATA0_hkadc_data7_0_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_ADC_IBIAS_SEL_UNION
 结构说明  : ADC_IBIAS_SEL 寄存器结构定义。地址偏移量:0xB5，初值:0x00，宽度:8
 寄存器说明: HKADC工作IBIAS电流配置寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  hkadc_ibias_sel : 8;  /* bit[0-7]: HKADC工作ibias电流配置寄存器；默认0 */
    } reg;
} SOC_SCHARGER_ADC_IBIAS_SEL_UNION;
#endif
#define SOC_SCHARGER_ADC_IBIAS_SEL_hkadc_ibias_sel_START  (0)
#define SOC_SCHARGER_ADC_IBIAS_SEL_hkadc_ibias_sel_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_EFUSE_REG0_UNION
 结构说明  : EFUSE_REG0 寄存器结构定义。地址偏移量:0xC0，初值:0x00，宽度:8
 寄存器说明: EFUSE调节0寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  efuse_por_int_ro : 1;  /* bit[0]  : efuse_por_int状态寄存器：
                                                           0：eFuse不读；
                                                           1：自动将64bits eFuse值读回到寄存器保存。 */
        unsigned char  efuse_state      : 4;  /* bit[1-4]: EFUSE_CTRL状态机状态寄存器。 */
        unsigned char  reserved         : 3;  /* bit[5-7]: 保留。 */
    } reg;
} SOC_SCHARGER_EFUSE_REG0_UNION;
#endif
#define SOC_SCHARGER_EFUSE_REG0_efuse_por_int_ro_START  (0)
#define SOC_SCHARGER_EFUSE_REG0_efuse_por_int_ro_END    (0)
#define SOC_SCHARGER_EFUSE_REG0_efuse_state_START       (1)
#define SOC_SCHARGER_EFUSE_REG0_efuse_state_END         (4)


/*****************************************************************************
 结构名    : SOC_SCHARGER_EFUSE_REG1_UNION
 结构说明  : EFUSE_REG1 寄存器结构定义。地址偏移量:0xC1，初值:0x02，宽度:8
 寄存器说明: EFUSE调节1寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  efuse_nr_cfg     : 1;  /* bit[0]: efuse_nr信号控制寄存器 */
        unsigned char  efuse_pgenb_cfg  : 1;  /* bit[1]: efuse_pgenb信号控制寄存器 */
        unsigned char  efuse_strobe_cfg : 1;  /* bit[2]: efuse写控制信号的脉宽 */
        unsigned char  efuse_rd_ctrl    : 1;  /* bit[3]: EFUSE读控制寄存器。 */
        unsigned char  efuse_inctrl_sel : 1;  /* bit[4]: 0：EFUSE的编程信号由芯片数字自动生成（内部自动）；
                                                         1：EFUSE的编程时序由寄存器控制生成（内部手动）。 */
        unsigned char  efuse_prog_sel   : 1;  /* bit[5]: 0：EFUSE的编程时序由芯片内部产生；
                                                         1：EFUSE的编程时序由外部D+管脚配合。 */
        unsigned char  efuse_prog_int   : 1;  /* bit[6]: efuse编程控制信号。
                                                         0：eFuse不编程；
                                                         1：eFuse开始编程。 */
        unsigned char  reserved         : 1;  /* bit[7]: 保留。 */
    } reg;
} SOC_SCHARGER_EFUSE_REG1_UNION;
#endif
#define SOC_SCHARGER_EFUSE_REG1_efuse_nr_cfg_START      (0)
#define SOC_SCHARGER_EFUSE_REG1_efuse_nr_cfg_END        (0)
#define SOC_SCHARGER_EFUSE_REG1_efuse_pgenb_cfg_START   (1)
#define SOC_SCHARGER_EFUSE_REG1_efuse_pgenb_cfg_END     (1)
#define SOC_SCHARGER_EFUSE_REG1_efuse_strobe_cfg_START  (2)
#define SOC_SCHARGER_EFUSE_REG1_efuse_strobe_cfg_END    (2)
#define SOC_SCHARGER_EFUSE_REG1_efuse_rd_ctrl_START     (3)
#define SOC_SCHARGER_EFUSE_REG1_efuse_rd_ctrl_END       (3)
#define SOC_SCHARGER_EFUSE_REG1_efuse_inctrl_sel_START  (4)
#define SOC_SCHARGER_EFUSE_REG1_efuse_inctrl_sel_END    (4)
#define SOC_SCHARGER_EFUSE_REG1_efuse_prog_sel_START    (5)
#define SOC_SCHARGER_EFUSE_REG1_efuse_prog_sel_END      (5)
#define SOC_SCHARGER_EFUSE_REG1_efuse_prog_int_START    (6)
#define SOC_SCHARGER_EFUSE_REG1_efuse_prog_int_END      (6)


/*****************************************************************************
 结构名    : SOC_SCHARGER_EFUSE_WE0_UNION
 结构说明  : EFUSE_WE0 寄存器结构定义。地址偏移量:0xC2，初值:0x00，宽度:8
 寄存器说明: EFUSE地址寄存器对应地址[7:0]。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  efuse_we0_cfg : 8;  /* bit[0-7]: efuse地址寄存器对应地址we0[7:0]。 */
    } reg;
} SOC_SCHARGER_EFUSE_WE0_UNION;
#endif
#define SOC_SCHARGER_EFUSE_WE0_efuse_we0_cfg_START  (0)
#define SOC_SCHARGER_EFUSE_WE0_efuse_we0_cfg_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_EFUSE_WE1_UNION
 结构说明  : EFUSE_WE1 寄存器结构定义。地址偏移量:0xC3，初值:0x00，宽度:8
 寄存器说明: EFUSE地址寄存器对应地址[15:8]。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  efuse_we1_cfg : 8;  /* bit[0-7]: efuse地址寄存器对应地址we1[15:8] */
    } reg;
} SOC_SCHARGER_EFUSE_WE1_UNION;
#endif
#define SOC_SCHARGER_EFUSE_WE1_efuse_we1_cfg_START  (0)
#define SOC_SCHARGER_EFUSE_WE1_efuse_we1_cfg_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_EFUSE_WE2_UNION
 结构说明  : EFUSE_WE2 寄存器结构定义。地址偏移量:0xC4，初值:0x00，宽度:8
 寄存器说明: EFUSE地址寄存器对应地址[23:16]。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  efuse_we2_cfg : 8;  /* bit[0-7]: efuse地址寄存器对应地址we2[23:16] */
    } reg;
} SOC_SCHARGER_EFUSE_WE2_UNION;
#endif
#define SOC_SCHARGER_EFUSE_WE2_efuse_we2_cfg_START  (0)
#define SOC_SCHARGER_EFUSE_WE2_efuse_we2_cfg_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_EFUSE_WE3_UNION
 结构说明  : EFUSE_WE3 寄存器结构定义。地址偏移量:0xC5，初值:0x00，宽度:8
 寄存器说明: EFUSE地址寄存器对应地址[31:24]。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  efuse_we3_cfg : 8;  /* bit[0-7]: efuse地址寄存器对应地址we3[31:24] */
    } reg;
} SOC_SCHARGER_EFUSE_WE3_UNION;
#endif
#define SOC_SCHARGER_EFUSE_WE3_efuse_we3_cfg_START  (0)
#define SOC_SCHARGER_EFUSE_WE3_efuse_we3_cfg_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_EFUSE_WE4_UNION
 结构说明  : EFUSE_WE4 寄存器结构定义。地址偏移量:0xC6，初值:0x00，宽度:8
 寄存器说明: EFUSE地址寄存器对应地址[39:32]。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  efuse_we4_cfg : 8;  /* bit[0-7]: efuse地址寄存器对应地址we4[39:32] */
    } reg;
} SOC_SCHARGER_EFUSE_WE4_UNION;
#endif
#define SOC_SCHARGER_EFUSE_WE4_efuse_we4_cfg_START  (0)
#define SOC_SCHARGER_EFUSE_WE4_efuse_we4_cfg_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_EFUSE_WE5_UNION
 结构说明  : EFUSE_WE5 寄存器结构定义。地址偏移量:0xC7，初值:0x00，宽度:8
 寄存器说明: EFUSE地址寄存器对应地址[47:40]。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  efuse_we5_cfg : 8;  /* bit[0-7]: efuse地址寄存器对应地址we5[47:40] */
    } reg;
} SOC_SCHARGER_EFUSE_WE5_UNION;
#endif
#define SOC_SCHARGER_EFUSE_WE5_efuse_we5_cfg_START  (0)
#define SOC_SCHARGER_EFUSE_WE5_efuse_we5_cfg_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_EFUSE_WE6_UNION
 结构说明  : EFUSE_WE6 寄存器结构定义。地址偏移量:0xC8，初值:0x00，宽度:8
 寄存器说明: EFUSE地址寄存器对应地址[55:48]。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  efuse_we6_cfg : 8;  /* bit[0-7]: efuse地址寄存器对应地址we6[55:48] */
    } reg;
} SOC_SCHARGER_EFUSE_WE6_UNION;
#endif
#define SOC_SCHARGER_EFUSE_WE6_efuse_we6_cfg_START  (0)
#define SOC_SCHARGER_EFUSE_WE6_efuse_we6_cfg_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_EFUSE_WE7_UNION
 结构说明  : EFUSE_WE7 寄存器结构定义。地址偏移量:0xC9，初值:0x00，宽度:8
 寄存器说明: EFUSE地址寄存器对应地址[63:56]。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  efuse_we7_cfg : 8;  /* bit[0-7]: efuse地址寄存器对应地址we7[63:56] */
    } reg;
} SOC_SCHARGER_EFUSE_WE7_UNION;
#endif
#define SOC_SCHARGER_EFUSE_WE7_efuse_we7_cfg_START  (0)
#define SOC_SCHARGER_EFUSE_WE7_efuse_we7_cfg_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_EFUSE_PDOB0_UNION
 结构说明  : EFUSE_PDOB0 寄存器结构定义。地址偏移量:0xCA，初值:0x00，宽度:8
 寄存器说明: EFUSE数据输出对应地址[7:0]。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  efuse_pdob0 : 8;  /* bit[0-7]: efuse数据输出对应地址we0[7:0] */
    } reg;
} SOC_SCHARGER_EFUSE_PDOB0_UNION;
#endif
#define SOC_SCHARGER_EFUSE_PDOB0_efuse_pdob0_START  (0)
#define SOC_SCHARGER_EFUSE_PDOB0_efuse_pdob0_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_EFUSE_PDOB1_UNION
 结构说明  : EFUSE_PDOB1 寄存器结构定义。地址偏移量:0xCB，初值:0x00，宽度:8
 寄存器说明: EFUSE数据输出对应地址[15:8]。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  efuse_pdob1 : 8;  /* bit[0-7]: efuse数据输出对应地址we1[15:8] */
    } reg;
} SOC_SCHARGER_EFUSE_PDOB1_UNION;
#endif
#define SOC_SCHARGER_EFUSE_PDOB1_efuse_pdob1_START  (0)
#define SOC_SCHARGER_EFUSE_PDOB1_efuse_pdob1_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_EFUSE_PDOB2_UNION
 结构说明  : EFUSE_PDOB2 寄存器结构定义。地址偏移量:0xCC，初值:0x00，宽度:8
 寄存器说明: EFUSE数据输出对应地址[23:16]。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  efuse_pdob2 : 8;  /* bit[0-7]: efuse数据输出对应地址we2[23:16] */
    } reg;
} SOC_SCHARGER_EFUSE_PDOB2_UNION;
#endif
#define SOC_SCHARGER_EFUSE_PDOB2_efuse_pdob2_START  (0)
#define SOC_SCHARGER_EFUSE_PDOB2_efuse_pdob2_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_EFUSE_PDOB3_UNION
 结构说明  : EFUSE_PDOB3 寄存器结构定义。地址偏移量:0xCD，初值:0x00，宽度:8
 寄存器说明: EFUSE数据输出对应地址[31:24]。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  efuse_pdob3 : 8;  /* bit[0-7]: efuse数据输出对应地址we3[31:24] */
    } reg;
} SOC_SCHARGER_EFUSE_PDOB3_UNION;
#endif
#define SOC_SCHARGER_EFUSE_PDOB3_efuse_pdob3_START  (0)
#define SOC_SCHARGER_EFUSE_PDOB3_efuse_pdob3_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_EFUSE_PDOB4_UNION
 结构说明  : EFUSE_PDOB4 寄存器结构定义。地址偏移量:0xCE，初值:0x00，宽度:8
 寄存器说明: EFUSE数据输出对应地址[39:32]。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  efuse_pdob4 : 8;  /* bit[0-7]: efuse数据输出对应地址we4[39:32] */
    } reg;
} SOC_SCHARGER_EFUSE_PDOB4_UNION;
#endif
#define SOC_SCHARGER_EFUSE_PDOB4_efuse_pdob4_START  (0)
#define SOC_SCHARGER_EFUSE_PDOB4_efuse_pdob4_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_EFUSE_PDOB5_UNION
 结构说明  : EFUSE_PDOB5 寄存器结构定义。地址偏移量:0xCF，初值:0x00，宽度:8
 寄存器说明: EFUSE数据输出对应地址[47:40]。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  efuse_pdob5 : 8;  /* bit[0-7]: efuse数据输出对应地址we5[47:40] */
    } reg;
} SOC_SCHARGER_EFUSE_PDOB5_UNION;
#endif
#define SOC_SCHARGER_EFUSE_PDOB5_efuse_pdob5_START  (0)
#define SOC_SCHARGER_EFUSE_PDOB5_efuse_pdob5_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_EFUSE_PDOB6_UNION
 结构说明  : EFUSE_PDOB6 寄存器结构定义。地址偏移量:0xD0，初值:0x00，宽度:8
 寄存器说明: EFUSE数据输出对应地址[55:48]。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  efuse_pdob6 : 8;  /* bit[0-7]: efuse数据输出对应地址we6[55:48] */
    } reg;
} SOC_SCHARGER_EFUSE_PDOB6_UNION;
#endif
#define SOC_SCHARGER_EFUSE_PDOB6_efuse_pdob6_START  (0)
#define SOC_SCHARGER_EFUSE_PDOB6_efuse_pdob6_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_EFUSE_PDOB7_UNION
 结构说明  : EFUSE_PDOB7 寄存器结构定义。地址偏移量:0xD1，初值:0x00，宽度:8
 寄存器说明: EFUSE数据输出对应地址[63:56]。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  efuse_pdob7 : 8;  /* bit[0-7]: efuse数据输出对应地址we7[63:56] */
    } reg;
} SOC_SCHARGER_EFUSE_PDOB7_UNION;
#endif
#define SOC_SCHARGER_EFUSE_PDOB7_efuse_pdob7_START  (0)
#define SOC_SCHARGER_EFUSE_PDOB7_efuse_pdob7_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_EFUSE_SOFT_RST_CTRL_UNION
 结构说明  : EFUSE_SOFT_RST_CTRL 寄存器结构定义。地址偏移量:0xD2，初值:0x00，宽度:8
 寄存器说明: EFUSE软复位控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  efuse_soft_rst_cfg : 8;  /* bit[0-7]: EFUSE模块软复位信号，写入0x04进行复位，自动清零。 */
    } reg;
} SOC_SCHARGER_EFUSE_SOFT_RST_CTRL_UNION;
#endif
#define SOC_SCHARGER_EFUSE_SOFT_RST_CTRL_efuse_soft_rst_cfg_START  (0)
#define SOC_SCHARGER_EFUSE_SOFT_RST_CTRL_efuse_soft_rst_cfg_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_SYS_RESVO1_UNION
 结构说明  : SYS_RESVO1 寄存器结构定义。地址偏移量:0xE0，初值:0x00，宽度:8
 寄存器说明: SYS调节1寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  sys_resvo1 : 8;  /* bit[0-7]: sys_resvo1<7:5>：寄存器预留；
                                                     sys_resvo1<4:3>：VBUS欠压点的寄存器选择
                                                     00：欠压点为3.8V；
                                                     01：欠压点为7.4V；
                                                     10&amp;11：欠压点9.7V；
                                                     sys_resvo1<2:1>：VBUS过压点的寄存器选择
                                                     00：过压点为6.5V；
                                                     01：过压点为10.5V；
                                                     10&amp;11：过压点13.5V；
                                                     sys_resvo1<0>：OTG启动延时时间的档位选择
                                                     0：延时256ms；
                                                     1：延时128ms。
                                                     注：VBUS的过压、欠压点的选择要注意匹配vbus_vset的输入电压档位选择。 */
    } reg;
} SOC_SCHARGER_SYS_RESVO1_UNION;
#endif
#define SOC_SCHARGER_SYS_RESVO1_sys_resvo1_START  (0)
#define SOC_SCHARGER_SYS_RESVO1_sys_resvo1_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_SYS_RESVO2_UNION
 结构说明  : SYS_RESVO2 寄存器结构定义。地址偏移量:0xE1，初值:0x00，宽度:8
 寄存器说明: SYS_RESVO2预留寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  sys_resvo2 : 8;  /* bit[0-7]: 预留寄存器 */
    } reg;
} SOC_SCHARGER_SYS_RESVO2_UNION;
#endif
#define SOC_SCHARGER_SYS_RESVO2_sys_resvo2_START  (0)
#define SOC_SCHARGER_SYS_RESVO2_sys_resvo2_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_SYS_RESVO3_UNION
 结构说明  : SYS_RESVO3 寄存器结构定义。地址偏移量:0xE2，初值:0x00，宽度:8
 寄存器说明: SYS_RESVO3预留寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  sys_resvo3 : 8;  /* bit[0-7]: 预留寄存器 */
    } reg;
} SOC_SCHARGER_SYS_RESVO3_UNION;
#endif
#define SOC_SCHARGER_SYS_RESVO3_sys_resvo3_START  (0)
#define SOC_SCHARGER_SYS_RESVO3_sys_resvo3_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_SYS_RESVO4_UNION
 结构说明  : SYS_RESVO4 寄存器结构定义。地址偏移量:0xE3，初值:0x00，宽度:8
 寄存器说明: SYS_RESVO4预留寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  sys_resvo4 : 8;  /* bit[0-7]: 预留寄存器 */
    } reg;
} SOC_SCHARGER_SYS_RESVO4_UNION;
#endif
#define SOC_SCHARGER_SYS_RESVO4_sys_resvo4_START  (0)
#define SOC_SCHARGER_SYS_RESVO4_sys_resvo4_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_SYS_RESVI1_UNION
 结构说明  : SYS_RESVI1 寄存器结构定义。地址偏移量:0xE4，初值:0x00，宽度:8
 寄存器说明: SYS_RESVI1预留寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  sys_resvi1 : 8;  /* bit[0-7]: 预留寄存器 */
    } reg;
} SOC_SCHARGER_SYS_RESVI1_UNION;
#endif
#define SOC_SCHARGER_SYS_RESVI1_sys_resvi1_START  (0)
#define SOC_SCHARGER_SYS_RESVI1_sys_resvi1_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_SYS_RESVI2_UNION
 结构说明  : SYS_RESVI2 寄存器结构定义。地址偏移量:0xE5，初值:0x00，宽度:8
 寄存器说明: SYS_RESVI2预留寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  sys_resvi2 : 8;  /* bit[0-7]: 预留寄存器 */
    } reg;
} SOC_SCHARGER_SYS_RESVI2_UNION;
#endif
#define SOC_SCHARGER_SYS_RESVI2_sys_resvi2_START  (0)
#define SOC_SCHARGER_SYS_RESVI2_sys_resvi2_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_OSC_FCP_UNION
 结构说明  : OSC_FCP 寄存器结构定义。地址偏移量:0xE6，初值:0x00，宽度:8
 寄存器说明: 2MHz高精度时钟频率修调寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  osc_trimcode : 6;  /* bit[0-5]: 对2MHz高精度时钟频率进行修调 */
        unsigned char  reserved     : 2;  /* bit[6-7]: 保留。 */
    } reg;
} SOC_SCHARGER_OSC_FCP_UNION;
#endif
#define SOC_SCHARGER_OSC_FCP_osc_trimcode_START  (0)
#define SOC_SCHARGER_OSC_FCP_osc_trimcode_END    (5)


/*****************************************************************************
 结构名    : SOC_SCHARGER_GLB_SOFT_RST_CTRL_UNION
 结构说明  : GLB_SOFT_RST_CTRL 寄存器结构定义。地址偏移量:0xE7，初值:0x00，宽度:8
 寄存器说明: 全局软复位控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  soft_rst_cfg : 8;  /* bit[0-7]: 全局软复位信号，写入0x04进行复位，自动清零，batfet_ctrl寄存器不受软复位控制。 */
    } reg;
} SOC_SCHARGER_GLB_SOFT_RST_CTRL_UNION;
#endif
#define SOC_SCHARGER_GLB_SOFT_RST_CTRL_soft_rst_cfg_START  (0)
#define SOC_SCHARGER_GLB_SOFT_RST_CTRL_soft_rst_cfg_END    (7)


/*****************************************************************************
 结构名    : SOC_SCHARGER_WATCHDOG_SOFT_RST_UNION
 结构说明  : WATCHDOG_SOFT_RST 寄存器结构定义。地址偏移量:0xE8，初值:0x00，宽度:8
 寄存器说明: 看门狗软复位控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  wd_rst_n : 1;  /* bit[0]  : 写1该寄存器，系统watchdog timer计数重新计时(写1后，自动清零)
                                                   如果SoC在设置时间内不对该寄存器写‘1’操作，则复位chg_en和watchdog_timer寄存器。 */
        unsigned char  reserved : 7;  /* bit[1-7]: 保留。 */
    } reg;
} SOC_SCHARGER_WATCHDOG_SOFT_RST_UNION;
#endif
#define SOC_SCHARGER_WATCHDOG_SOFT_RST_wd_rst_n_START  (0)
#define SOC_SCHARGER_WATCHDOG_SOFT_RST_wd_rst_n_END    (0)


/*****************************************************************************
 结构名    : SOC_SCHARGER_WATCHDOG_CTRL_UNION
 结构说明  : WATCHDOG_CTRL 寄存器结构定义。地址偏移量:0xE9，初值:0x00，宽度:8
 寄存器说明: 喂狗时间控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  watchdog_timer : 2;  /* bit[0-1]: SOC每隔一定时间对wd_rst_n(0xE8)进行一次寄存器写操作；如果没有写操作事件发生，则进入Default模式，复位chg_en和watchdog_timer寄存器；否则是正常的Host模式。
                                                         系统watchdog_timer时间设置：
                                                         00：系统watchdog_timer功能屏蔽；
                                                         01：10s；
                                                         10：20s；
                                                         11：40s 。 */
        unsigned char  reserved       : 6;  /* bit[2-7]: 保留。 */
    } reg;
} SOC_SCHARGER_WATCHDOG_CTRL_UNION;
#endif
#define SOC_SCHARGER_WATCHDOG_CTRL_watchdog_timer_START  (0)
#define SOC_SCHARGER_WATCHDOG_CTRL_watchdog_timer_END    (1)


/*****************************************************************************
 结构名    : SOC_SCHARGER_CLK_GATE_UNION
 结构说明  : CLK_GATE 寄存器结构定义。地址偏移量:0xEA，初值:0x00，宽度:8
 寄存器说明: clk gating控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char      value;
    struct
    {
        unsigned char  red_clk_enable : 1;  /* bit[0]  : clk gating寄存器：
                                                         0：gate时钟；
                                                         1：使能时钟。 */
        unsigned char  reserved       : 7;  /* bit[1-7]: 保留。 */
    } reg;
} SOC_SCHARGER_CLK_GATE_UNION;
#endif
#define SOC_SCHARGER_CLK_GATE_red_clk_enable_START  (0)
#define SOC_SCHARGER_CLK_GATE_red_clk_enable_END    (0)






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

#endif /* end of soc_scharger_interface.h */
