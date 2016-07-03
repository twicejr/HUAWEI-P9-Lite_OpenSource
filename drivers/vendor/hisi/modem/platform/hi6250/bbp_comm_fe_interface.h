

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __BBP_COMM_FE_INTERFACE_H__
#define __BBP_COMM_FE_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/***======================================================================***
                     (1/3) register_define_ctu
 ***======================================================================***/
/* 寄存器说明：接收通道0对应主模（主模0）的模式指示寄存器
 bit[31:3]   保留
 bit[2:0]    接收通道0对应的主模（定义为主模0）的模式配置指示：
             000：LTE 主模。
             001：W主模。
             010：TDS主模。
             011：Gm主模；
             100：Gs主模；
             101:C2主模；
             110~111：无效。
             配置时刻：各模根据通信场景配置
   UNION结构:  BBPCOMM_C0_PRIMARY_MODE_IND_RX_UNION */
#define BBPCOMM_C0_PRIMARY_MODE_IND_RX_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0x0)

/* 寄存器说明：主模0对应的从模（从模0）的模式指示寄存器
 bit[31:3]   保留
 bit[2:0]    接收主模0对应的从模（定义为从模0）的模式配置指示：
             000：LTE从模。
             001：W 从模。
             010：TDS从模。
             011：Gm从模；
             100：Gs从模；
             101:C2从模；
             110~111：无效。
             配置时刻：各模根据通信场景配置
   UNION结构:  BBPCOMM_C0_SECOND_MODE_IND_UNION */
#define BBPCOMM_C0_SECOND_MODE_IND_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x4)

/* 寄存器说明：发送通道0对应的模式指示寄存器
 bit[31:3]   保留
 bit[2:0]    发送通道0对应的模式配置指示：
             000：LTE 主模。
             001：W主模。
             010：TDS主模。
             011：Gm主模；
             100：Gs主模；
             101:C2主模；
             110~111：无效。
             配置时刻：各模根据通信场景配置
   UNION结构:  BBPCOMM_C0_PRIMARY_MODE_IND_TX_UNION */
#define BBPCOMM_C0_PRIMARY_MODE_IND_TX_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0x8)

/* 寄存器说明：寄存器
   详      述：AFC0值传递
               [15:0]:AFC积分器值
               [16]:AFC锁定指示
               
               配置时刻：DSP从主模切换为从模时配置；DSP从从模切换为主模时读取并清除锁定指示
               生效时刻：立即生效
   UNION结构 ：无 */
#define BBPCOMM_AFC0_VALUE_INTER_RAT_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0xC)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      0:通道0从模使用通道0主模afc控制字
             1:通道0从模使用通道0从模afc控制字
   UNION结构:  BBPCOMM_C0_SECOND_AFC_MODE_UNION */
#define BBPCOMM_C0_SECOND_AFC_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x10)

/* 寄存器说明：接收通道1对应主模（主模1）的模式指示寄存器
 bit[31:3]   保留
 bit[2:0]    接收通道1对应的主模（定义为主模1）的模式配置指示：
             000：LTE 主模。
             001：W主模。
             010：TDS主模。
             011：Gm主模；
             100：Gs主模；
             101:C2主模；
             110~111：无效。
             配置时刻：各模根据通信场景配置
   UNION结构:  BBPCOMM_C1_PRIMARY_MODE_IND_RX_UNION */
#define BBPCOMM_C1_PRIMARY_MODE_IND_RX_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0x20)

/* 寄存器说明：主模1对应的从模（从模1）的模式指示寄存器
 bit[31:3]   保留
 bit[2:0]    接收主模1对应的从模（定义为从模1）的模式配置指示：
             000：LTE从模。
             001：W 从模。
             010：TDS从模。
             011：Gm从模；
             100：Gs从模；
             101:C2从模；
             110~111：无效。
             配置时刻：各模根据通信场景配置
   UNION结构:  BBPCOMM_C1_SECOND_MODE_IND_UNION */
#define BBPCOMM_C1_SECOND_MODE_IND_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x24)

/* 寄存器说明：发送通道1对应的模式指示寄存器
 bit[31:3]   保留
 bit[2:0]    发送通道1对应的模式配置指示：
             000：LTE 主模。
             001：W主模。
             010：TDS主模。
             011：Gm主模；
             100：Gs主模；
             101:C2主模；
             110~111：无效。
             配置时刻：各模根据通信场景配置
   UNION结构:  BBPCOMM_C1_PRIMARY_MODE_IND_TX_UNION */
#define BBPCOMM_C1_PRIMARY_MODE_IND_TX_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0x28)

/* 寄存器说明：寄存器
   详      述：AFC1值传递
               [15:0]:AFC积分器值
               [16]:AFC锁定指示
               
               配置时刻：DSP从主模切换为从模时配置；DSP从从模切换为主模时读取并清除锁定指示
               生效时刻：立即生效
   UNION结构 ：无 */
#define BBPCOMM_AFC1_VALUE_INTER_RAT_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x2C)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      0:通道1从模使用通道1主模afc控制字
             1:通道1从模使用通道1从模afc控制字
   UNION结构:  BBPCOMM_C1_SECOND_AFC_MODE_UNION */
#define BBPCOMM_C1_SECOND_AFC_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x30)

/* 寄存器说明：接收通道2对应主模（主模2）的模式指示寄存器
 bit[31:3]   保留
 bit[2:0]    接收通道2对应的主模（定义为主模2）的模式配置指示：
             000：LTE 主模。
             001：W主模。
             010：TDS主模。
             011：Gm主模；
             100：Gs主模；
             101:C2主模；
             110~111：无效。
             配置时刻：各模根据通信场景配置
   UNION结构:  BBPCOMM_C2_PRIMARY_MODE_IND_RX_UNION */
#define BBPCOMM_C2_PRIMARY_MODE_IND_RX_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0x40)

/* 寄存器说明：主模2对应的从模（从模2）的模式指示寄存器
 bit[31:3]   保留
 bit[2:0]    接收主模2对应的从模（定义为从模2）的模式配置指示：
             000：LTE从模。
             001：W 从模。
             010：TDS从模。
             011：Gm从模；
             100：Gs从模；
             101:C2从模；
             110~111：无效。
             配置时刻：各模根据通信场景配置
   UNION结构:  BBPCOMM_C2_SECOND_MODE_IND_UNION */
#define BBPCOMM_C2_SECOND_MODE_IND_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x44)

/* 寄存器说明：发送通道2对应的模式指示寄存器
 bit[31:3]   保留
 bit[2:0]    发送通道2对应的模式配置指示：
             000：LTE 主模。
             001：W主模。
             010：TDS主模。
             011：Gm主模；
             100：Gs主模；
             101:C2主模；
             110~111：无效。
             配置时刻：各模根据通信场景配置
   UNION结构:  BBPCOMM_C2_PRIMARY_MODE_IND_TX_UNION */
#define BBPCOMM_C2_PRIMARY_MODE_IND_TX_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0x48)

/* 寄存器说明：寄存器
   详      述：AFC2值传递
               [15:0]:AFC积分器值
               [16]:AFC锁定指示
               
               配置时刻：DSP从主模切换为从模时配置；DSP从从模切换为主模时读取并清除锁定指示
               生效时刻：立即生效
   UNION结构 ：无 */
#define BBPCOMM_AFC2_VALUE_INTER_RAT_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x4C)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      0:通道2从模使用通道2主模afc控制字
             1:通道2从模使用通道2从模afc控制字
   UNION结构:  BBPCOMM_C2_SECOND_AFC_MODE_UNION */
#define BBPCOMM_C2_SECOND_AFC_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x50)

/* 寄存器说明：接收通道3对应主模（主模3）的模式指示寄存器
 bit[31:3]   保留
 bit[2:0]    接收通道3对应的主模（定义为主模3）的模式配置指示：
             000：LTE 主模。
             001：W主模。
             010：TDS主模。
             011：Gm主模；
             100：Gs主模；
             101:C2主模；
             110~111：无效。
             配置时刻：各模根据通信场景配置
   UNION结构:  BBPCOMM_C3_PRIMARY_MODE_IND_RX_UNION */
#define BBPCOMM_C3_PRIMARY_MODE_IND_RX_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0x60)

/* 寄存器说明：主模3对应的从模（从模3）的模式指示寄存器
 bit[31:3]   保留
 bit[2:0]    接收主模3对应的从模（定义为从模3）的模式配置指示：
             000：LTE从模。
             001：W 从模。
             010：TDS从模。
             011：Gm从模；
             100：Gs从模；
             101:C2从模；
             110~111：无效。
             配置时刻：各模根据通信场景配置
   UNION结构:  BBPCOMM_C3_SECOND_MODE_IND_UNION */
#define BBPCOMM_C3_SECOND_MODE_IND_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x64)

/* 寄存器说明：发送通道3对应的模式指示寄存器
 bit[31:3]   保留
 bit[2:0]    发送通道3对应的模式配置指示：
             000：LTE 主模。
             001：W主模。
             010：TDS主模。
             011：Gm主模；
             100：Gs主模；
             101:C2主模；
             110~111：无效。
             配置时刻：各模根据通信场景配置
   UNION结构:  BBPCOMM_C3_PRIMARY_MODE_IND_TX_UNION */
#define BBPCOMM_C3_PRIMARY_MODE_IND_TX_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0x68)

/* 寄存器说明：寄存器
   详      述：AFC3值传递
               [15:0]:AFC积分器值
               [16]:AFC锁定指示
               
               配置时刻：DSP从主模切换为从模时配置；DSP从从模切换为主模时读取并清除锁定指示
               生效时刻：立即生效
   UNION结构 ：无 */
#define BBPCOMM_AFC3_VALUE_INTER_RAT_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x6C)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      0:通道3从模使用通道3主模afc控制字
             1:通道3从模使用通道3从模afc控制字
   UNION结构:  BBPCOMM_C3_SECOND_AFC_MODE_UNION */
#define BBPCOMM_C3_SECOND_AFC_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x70)

/* 寄存器说明：寄存器
 bit[31:10]  保留
 bit[9:9]    1'b1：LTE的CH0 TX通路I路数据取反
             1'b0：LTE的CH0 TX通路I路数据不取反
 bit[8:8]    1'b1：LTE的CH0 TX通路Q路数据取反
             1'b0：LTE的CH0 TX通路Q路数据不取反
 bit[7:7]    1'b1：LTE的CH0 TX通路IQ路数据交换
             1'b0：LTE的CH0 TX通路IQ路数据不交换
 bit[6:6]    1'b1：LTE的CH0 RXA通路I路数据取反
             1'b0：LTE的CH0 RXA通路I路数据不取反
 bit[5:5]    1'b1：LTE的CH0 RXA通路Q路数据取反
             1'b0：LTE的CH0 RXA通路Q路数据不取反
 bit[4:4]    1'b1：LTE的CH0 RXA通路IQ路数据交换
             1'b0：LTE的CH0 RXA通路IQ路数据不交换
 bit[3:3]    1'b1：LTE的CH0 RXB通路I路数据取反
             1'b0：LTE的CH0 RXB通路I路数据不取反
 bit[2:2]    1'b1：LTE的CH0 RXB通路Q路数据取反
             1'b0：LTE的CH0 RXB通路Q路数据不取反
 bit[1:1]    1'b1：LTE的CH0 RXB通路IQ路数据交换
             1'b0：LTE的CH0 RXB通路IQ路数据不交换
 bit[0:0]    保留
   UNION结构:  BBPCOMM_LTE_CH0_ABBIF_FMT_UNION */
#define BBPCOMM_LTE_CH0_ABBIF_FMT_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x100)

/* 寄存器说明：寄存器
 bit[31:10]  保留
 bit[9:9]    1'b1：LTE的CH1 TX通路I路数据取反
             1'b0：LTE的CH1 TX通路I路数据不取反
 bit[8:8]    1'b1：LTE的CH1 TX通路Q路数据取反
             1'b0：LTE的CH1 TX通路Q路数据不取反
 bit[7:7]    1'b1：LTE的CH1 TX通路IQ路数据交换
             1'b0：LTE的CH1 TX通路IQ路数据不交换
 bit[6:6]    1'b1：LTE的CH1 RXA通路I路数据取反
             1'b0：LTE的CH1 RXA通路I路数据不取反
 bit[5:5]    1'b1：LTE的CH1 RXA通路Q路数据取反
             1'b0：LTE的CH1 RXA通路Q路数据不取反
 bit[4:4]    1'b1：LTE的CH1 RXA通路IQ路数据交换
             1'b0：LTE的CH1 RXA通路IQ路数据不交换
 bit[3:3]    1'b1：LTE的CH1 RXB通路I路数据取反
             1'b0：LTE的CH1 RXB通路I路数据不取反
 bit[2:2]    1'b1：LTE的CH1 RXB通路Q路数据取反
             1'b0：LTE的CH1 RXB通路Q路数据不取反
 bit[1:1]    1'b1：LTE的CH1 RXB通路IQ路数据交换
             1'b0：LTE的CH1 RXB通路IQ路数据不交换
 bit[0:0]    保留
   UNION结构:  BBPCOMM_LTE_CH1_ABBIF_FMT_UNION */
#define BBPCOMM_LTE_CH1_ABBIF_FMT_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x104)

/* 寄存器说明：寄存器
 bit[31:10]  保留
 bit[9:9]    1'b1：LTE的CH2 TX通路I路数据取反
             1'b0：LTE的CH2 TX通路I路数据不取反
 bit[8:8]    1'b1：LTE的CH2 TX通路Q路数据取反
             1'b0：LTE的CH2 TX通路Q路数据不取反
 bit[7:7]    1'b1：LTE的CH2 TX通路IQ路数据交换
             1'b0：LTE的CH2 TX通路IQ路数据不交换
 bit[6:6]    1'b1：LTE的CH2 RXA通路I路数据取反
             1'b0：LTE的CH2 RXA通路I路数据不取反
 bit[5:5]    1'b1：LTE的CH2 RXA通路Q路数据取反
             1'b0：LTE的CH2 RXA通路Q路数据不取反
 bit[4:4]    1'b1：LTE的CH2 RXA通路IQ路数据交换
             1'b0：LTE的CH2 RXA通路IQ路数据不交换
 bit[3:3]    1'b1：LTE的CH2 RXB通路I路数据取反
             1'b0：LTE的CH2 RXB通路I路数据不取反
 bit[2:2]    1'b1：LTE的CH2 RXB通路Q路数据取反
             1'b0：LTE的CH2 RXB通路Q路数据不取反
 bit[1:1]    1'b1：LTE的CH2 RXB通路IQ路数据交换
             1'b0：LTE的CH2 RXB通路IQ路数据不交换
 bit[0:0]    保留
   UNION结构:  BBPCOMM_LTE_CH2_ABBIF_FMT_UNION */
#define BBPCOMM_LTE_CH2_ABBIF_FMT_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x108)

/* 寄存器说明：寄存器
 bit[31:10]  保留
 bit[9:9]    1'b1：LTE的CH3 TX通路I路数据取反
             1'b0：LTE的CH3 TX通路I路数据不取反
 bit[8:8]    1'b1：LTE的CH3 TX通路Q路数据取反
             1'b0：LTE的CH3 TX通路Q路数据不取反
 bit[7:7]    1'b1：LTE的CH3 TX通路IQ路数据交换
             1'b0：LTE的CH3 TX通路IQ路数据不交换
 bit[6:6]    1'b1：LTE的CH3 RXA通路I路数据取反
             1'b0：LTE的CH3 RXA通路I路数据不取反
 bit[5:5]    1'b1：LTE的CH3 RXA通路Q路数据取反
             1'b0：LTE的CH3 RXA通路Q路数据不取反
 bit[4:4]    1'b1：LTE的CH3 RXA通路IQ路数据交换
             1'b0：LTE的CH3 RXA通路IQ路数据不交换
 bit[3:3]    1'b1：LTE的CH3 RXB通路I路数据取反
             1'b0：LTE的CH3 RXB通路I路数据不取反
 bit[2:2]    1'b1：LTE的CH3 RXB通路Q路数据取反
             1'b0：LTE的CH3 RXB通路Q路数据不取反
 bit[1:1]    1'b1：LTE的CH3 RXB通路IQ路数据交换
             1'b0：LTE的CH3 RXB通路IQ路数据不交换
 bit[0:0]    保留
   UNION结构:  BBPCOMM_LTE_CH3_ABBIF_FMT_UNION */
#define BBPCOMM_LTE_CH3_ABBIF_FMT_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x10C)

/* 寄存器说明：寄存器
 bit[31:10]  保留
 bit[9:9]    1'b1：W的TX通路I路数据取反
             1'b0：W的TX通路I路数据不取反。
 bit[8:8]    1'b1：W的TX通路Q路数据取反
             1'b0：W的TX通路Q路数据不取反
 bit[7:7]    1'b1：W的TX通路IQ路数据交换
             1'b0：W的TX通路IQ路数据不交换
             V3R3不支持IQ交换功能。
 bit[6:6]    1'b1：W的RXA通路I路数据取反
             1'b0：W的RXA通路I路数据不取反
 bit[5:5]    1'b1：W的RXA通路Q路数据取反
             1'b0：W的RXA通路Q路数据不取反
 bit[4:4]    1'b1：W的RXA通路IQ路数据交换
             1'b0：W的RXA通路IQ路数据不交换
             V3R3不支持IQ交换功能。
 bit[3:3]    1'b1：W的RXB通路I路数据取反
             1'b0：W的RXB通路I路数据不取反
 bit[2:2]    1'b1：W的RXB通路Q路数据取反
             1'b0：W的RXB通路Q路数据不取反
 bit[1:1]    1'b1：W的RXB通路IQ路数据交换
             1'b0：W的RXB通路IQ路数据不交换
             V3R3不支持IQ交换功能。
 bit[0:0]    保留
   UNION结构:  BBPCOMM_W_ABBIF_FMT_UNION */
#define BBPCOMM_W_ABBIF_FMT_ADDR                      (SOC_BBP_COMM_BASE_ADDR + 0x110)

/* 寄存器说明：寄存器
 bit[31:10]  保留
 bit[9:9]    1'b1：TDS的TX通路I路数据取反
             1'b0：TDS的TX通路I路数据不取反
 bit[8:8]    1'b1：TDS的TX通路Q路数据取反
             1'b0：TDS的TX通路Q路数据不取反
 bit[7:7]    1'b1：TDS的TX通路IQ路数据交换
             1'b0：TDS的TX通路IQ路数据不交换
             V3R3不支持IQ交换功能。
 bit[6:6]    1'b1：TDS的RXA通路I路数据取反
             1'b0：TDS的RXA通路I路数据不取反
 bit[5:5]    1'b1：TDS的RXA通路Q路数据取反
             1'b0：TDS的RXA通路Q路数据不取反
 bit[4:4]    1'b1：TDS的RXA通路IQ路数据交换
             1'b0：TDS的RXA通路IQ路数据不交换
             V3R3不支持IQ交换功能。
 bit[3:3]    1'b1：TDS的RXB通路I路数据取反
             1'b0：TDS的RXB通路I路数据不取反
 bit[2:2]    1'b1：TDS的RXB通路Q路数据取反
             1'b0：TDS的RXB通路Q路数据不取反
 bit[1:1]    1'b1：TDS的RXB通路IQ路数据交换
             1'b0：TDS的RXB通路IQ路数据不交换
             V3R3不支持IQ交换功能。
 bit[0:0]    保留
   UNION结构:  BBPCOMM_TDS_ABBIF_FMT_UNION */
#define BBPCOMM_TDS_ABBIF_FMT_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x114)

/* 寄存器说明：寄存器
 bit[31:10]  保留
 bit[9:9]    1'b1：GM的TX通路I路数据取反
             1'b0：GM的TX通路I路数据不取反
 bit[8:8]    1'b1：GM的TX通路Q路数据取反
             1'b0：GM的TX通路Q路数据不取反
 bit[7:7]    1'b1：GM的TX通路IQ路数据交换
             1'b0：GM的TX通路IQ路数据不交换
             V3R3不支持IQ交换功能。
 bit[6:6]    1'b1：GM的RXA通路I路数据取反
             1'b0：GM的RXA通路I路数据不取反
 bit[5:5]    1'b1：GM的RXA通路Q路数据取反
             1'b0：GM的RXA通路Q路数据不取反
 bit[4:4]    1'b1：GM的RXA通路IQ路数据交换
             1'b0：GM的RXA通路IQ路数据不交换
             V3R3不支持IQ交换功能。
 bit[3:3]    1'b1：GM的RXB通路I路数据取反
             1'b0：GM的RXB通路I路数据不取反
 bit[2:2]    1'b1：GM的RXB通路Q路数据取反
             1'b0：GM的RXB通路Q路数据不取反
 bit[1:1]    1'b1：GM的RXB通路IQ路数据交换
             1'b0：GM的RXB通路IQ路数据不交换
             V3R3不支持IQ交换功能。
 bit[0:0]    保留
   UNION结构:  BBPCOMM_GM_ABBIF_FMT_UNION */
#define BBPCOMM_GM_ABBIF_FMT_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x118)

/* 寄存器说明：寄存器
 bit[31:10]  保留
 bit[9:9]    1'b1：GS的TX通路I路数据取反
             1'b0：GS的TX通路I路数据不取反
 bit[8:8]    1'b1：GS的TX通路Q路数据取反
             1'b0：GS的TX通路Q路数据不取反
 bit[7:7]    1'b1：GS的TX通路IQ路数据交换
             1'b0：GS的TX通路IQ路数据不交换
             V3R3不支持IQ交换功能。
 bit[6:6]    1'b1：GS的RXA通路I路数据取反
             1'b0：GS的RXA通路I路数据不取反
 bit[5:5]    1'b1：GS的RXA通路Q路数据取反
             1'b0：GS的RXA通路Q路数据不取反
 bit[4:4]    1'b1：GS的RXA通路IQ路数据交换
             1'b0：GS的RXA通路IQ路数据不交换
             V3R3不支持IQ交换功能。
 bit[3:3]    1'b1：GS的RXB通路I路数据取反
             1'b0：GS的RXB通路I路数据不取反
 bit[2:2]    1'b1：GS的RXB通路Q路数据取反
             1'b0：GS的RXB通路Q路数据不取反
 bit[1:1]    1'b1：GS的RXB通路IQ路数据交换
             1'b0：GS的RXB通路IQ路数据不交换
             V3R3不支持IQ交换功能。
 bit[0:0]    保留
   UNION结构:  BBPCOMM_GS_ABBIF_FMT_UNION */
#define BBPCOMM_GS_ABBIF_FMT_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x11C)

/* 寄存器说明：寄存器
 bit[31:10]  保留
 bit[9:9]    1'b1：C2的TX通路I路数据取反
             1'b0：C2的TX通路I路数据不取反
 bit[8:8]    1'b1：C2的TX通路Q路数据取反
             1'b0：C2的TX通路Q路数据不取反
 bit[7:7]    1'b1：C2的TX通路IQ路数据交换
             1'b0：C2的TX通路IQ路数据不交换
             V3R3不支持IQ交换功能。
 bit[6:6]    1'b1：C2的RXA通路I路数据取反
             1'b0：C2的RXA通路I路数据不取反
 bit[5:5]    1'b1：C2的RXA通路Q路数据取反
             1'b0：C2的RXA通路Q路数据不取反
 bit[4:4]    1'b1：C2的RXA通路IQ路数据交换
             1'b0：C2的RXA通路IQ路数据不交换
             V3R3不支持IQ交换功能。
 bit[3:3]    1'b1：C2的RXB通路I路数据取反
             1'b0：C2的RXB通路I路数据不取反
 bit[2:2]    1'b1：C2的RXB通路Q路数据取反
             1'b0：C2的RXB通路Q路数据不取反
 bit[1:1]    1'b1：C2的RXB通路IQ路数据交换
             1'b0：C2的RXB通路IQ路数据不交换
             V3R3不支持IQ交换功能。
 bit[0:0]    保留
   UNION结构:  BBPCOMM_C_ABBIF_FMT_UNION */
#define BBPCOMM_C_ABBIF_FMT_ADDR                      (SOC_BBP_COMM_BASE_ADDR + 0x120)

/* 寄存器说明：寄存器
 bit[31:12]  保留
 bit[11:9]   SSI3master等待时间
 bit[8:6]    SSI2master等待时间
 bit[5:3]    SSI1master等待时间
 bit[2:0]    SSI0master等待时间
   UNION结构:  BBPCOMM_RFIC_CK_CFG_UNION */
#define BBPCOMM_RFIC_CK_CFG_ADDR                      (SOC_BBP_COMM_BASE_ADDR + 0x124)

/* 寄存器说明：寄存器
 bit[31:3]   保留
 bit[2:0]    apt_pdm0信号来源：
             2'd0：来自于通道0
             2'd1：来自于通道1
             2'd2：来自于通道2
             2'd3：来自于通道3
             其它：强制拉低电平输出
   UNION结构:  BBPCOMM_APT_CH_SEL0_UNION */
#define BBPCOMM_APT_CH_SEL0_ADDR                      (SOC_BBP_COMM_BASE_ADDR + 0x130)

/* 寄存器说明：寄存器
 bit[31:3]   保留
 bit[2:0]    apt_pdm1信号来源：
             2'd0：来自于通道0
             2'd1：来自于通道1
             2'd2：来自于通道2
             2'd3：来自于通道3
             其它：强制拉低电平输出
   UNION结构:  BBPCOMM_APT_CH_SEL1_UNION */
#define BBPCOMM_APT_CH_SEL1_ADDR                      (SOC_BBP_COMM_BASE_ADDR + 0x134)

/* 寄存器说明：寄存器
 bit[31:3]   保留
 bit[2:0]    apt_pdm2信号来源：
             2'd0：来自于通道0
             2'd1：来自于通道1
             2'd2：来自于通道2
             2'd3：来自于通道3
             其它：强制拉低电平输出
   UNION结构:  BBPCOMM_APT_CH_SEL2_UNION */
#define BBPCOMM_APT_CH_SEL2_ADDR                      (SOC_BBP_COMM_BASE_ADDR + 0x138)

/* 寄存器说明：寄存器
 bit[31:3]   保留
 bit[2:0]    apt_pdm3信号来源：
             2'd0：来自于通道0
             2'd1：来自于通道1
             2'd2：来自于通道2
             2'd3：来自于通道3
             其它：强制拉低电平输出
   UNION结构:  BBPCOMM_APT_CH_SEL3_UNION */
#define BBPCOMM_APT_CH_SEL3_ADDR                      (SOC_BBP_COMM_BASE_ADDR + 0x13C)

/* 寄存器说明：寄存器
 bit[31:3]   保留
 bit[2:0]    afc pdm0信号来源：
             2'd0：来自于通道0
             2'd1：来自于通道1
             2'd2：来自于通道2
             2'd3：来自于通道3
             其它：强制拉低电平输出
   UNION结构:  BBPCOMM_AFC_CH_SEL0_UNION */
#define BBPCOMM_AFC_CH_SEL0_ADDR                      (SOC_BBP_COMM_BASE_ADDR + 0x140)

/* 寄存器说明：寄存器
 bit[31:3]   保留
 bit[2:0]    afc pdm1信号来源：
             2'd0：来自于通道0
             2'd1：来自于通道1
             2'd2：来自于通道2
             2'd3：来自于通道3
             其它：强制拉低电平输出
   UNION结构:  BBPCOMM_AFC_CH_SEL1_UNION */
#define BBPCOMM_AFC_CH_SEL1_ADDR                      (SOC_BBP_COMM_BASE_ADDR + 0x144)

/* 寄存器说明：寄存器
 bit[31:3]   保留
 bit[2:0]    afc pdm2信号来源：
             1'b0：来自于通道0
             1'b1：来自于通道1
             2'b2：来自于通道2
             2'b3：来自于通道3
   UNION结构:  BBPCOMM_AFC_CH_SEL2_UNION */
#define BBPCOMM_AFC_CH_SEL2_ADDR                      (SOC_BBP_COMM_BASE_ADDR + 0x148)

/* 寄存器说明：寄存器
 bit[31:3]   保留
 bit[2:0]    afc pdm3信号来源：
             1'b0：来自于通道0
             1'b1：来自于通道1
             2'b2：来自于通道2
             2'b3：来自于通道3
   UNION结构:  BBPCOMM_AFC_CH_SEL3_UNION */
#define BBPCOMM_AFC_CH_SEL3_ADDR                      (SOC_BBP_COMM_BASE_ADDR + 0x14C)

/* 寄存器说明：寄存器
 bit[31:3]   保留
 bit[2:0]    auxdac0信号来源：
             2'b0：来自于通道0
             2'b1：来自于通道1
             2'b2：来自于通道2
             2'b3：来自于通道3
   UNION结构:  BBPCOMM_PMU_CH_SEL0_UNION */
#define BBPCOMM_PMU_CH_SEL0_ADDR                      (SOC_BBP_COMM_BASE_ADDR + 0x150)

/* 寄存器说明：寄存器
 bit[31:3]   保留
 bit[2:0]    auxdac1信号来源：
             2'd0：来自于通道0
             2'd1：来自于通道1
             2'd2：来自于通道2
             2'd3：来自于通道3
             其它：强制拉低电平输出
   UNION结构:  BBPCOMM_PMU_CH_SEL1_UNION */
#define BBPCOMM_PMU_CH_SEL1_ADDR                      (SOC_BBP_COMM_BASE_ADDR + 0x154)

/* 寄存器说明：寄存器
 bit[31:3]   保留
 bit[2:0]    auxdac2信号来源：
             2'd0：来自于通道0
             2'd1：来自于通道1
             2'd2：来自于通道2
             2'd3：来自于通道3
             其它：强制拉低电平输出
   UNION结构:  BBPCOMM_PMU_CH_SEL2_UNION */
#define BBPCOMM_PMU_CH_SEL2_ADDR                      (SOC_BBP_COMM_BASE_ADDR + 0x158)

/* 寄存器说明：寄存器
 bit[31:3]   保留
 bit[2:0]    auxdac3信号来源：
             2'd0：来自于通道0
             2'd1：来自于通道1
             2'd2：来自于通道2
             2'd3：来自于通道3
             其它：强制拉低电平输出
   UNION结构:  BBPCOMM_PMU_CH_SEL3_UNION */
#define BBPCOMM_PMU_CH_SEL3_ADDR                      (SOC_BBP_COMM_BASE_ADDR + 0x15C)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      lte 通道0的tcvr_on配置：
             1'b0：配置为低电平
             1'b1：配置为高电平
   UNION结构:  BBPCOMM_L_TCVR_ON_CH0_UNION */
#define BBPCOMM_L_TCVR_ON_CH0_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x180)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      lte 通道1的tcvr_on配置：
             1'b0：配置为低电平
             1'b1：配置为高电平
   UNION结构:  BBPCOMM_L_TCVR_ON_CH1_UNION */
#define BBPCOMM_L_TCVR_ON_CH1_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x184)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      lte 通道2的tcvr_on配置：
             1'b0：配置为低电平
             1'b1：配置为高电平
   UNION结构:  BBPCOMM_L_TCVR_ON_CH2_UNION */
#define BBPCOMM_L_TCVR_ON_CH2_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x188)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      lte 通道3的tcvr_on配置：
             1'b0：配置为低电平
             1'b1：配置为高电平
   UNION结构:  BBPCOMM_L_TCVR_ON_CH3_UNION */
#define BBPCOMM_L_TCVR_ON_CH3_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x18C)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      tds 的tcvr_on配置：
             1'b0：配置为低电平
             1'b1：配置为高电平
   UNION结构:  BBPCOMM_T_TCVR_ON_UNION */
#define BBPCOMM_T_TCVR_ON_ADDR                        (SOC_BBP_COMM_BASE_ADDR + 0x190)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      w 的tcvr_on配置：
             1'b0：配置为低电平
             1'b1：配置为高电平
   UNION结构:  BBPCOMM_W_TCVR_ON_UNION */
#define BBPCOMM_W_TCVR_ON_ADDR                        (SOC_BBP_COMM_BASE_ADDR + 0x194)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      gm 的tcvr_on配置：
             1'b0：配置为低电平
             1'b1：配置为高电平
   UNION结构:  BBPCOMM_GM_TCVR_ON_UNION */
#define BBPCOMM_GM_TCVR_ON_ADDR                       (SOC_BBP_COMM_BASE_ADDR + 0x198)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      gs 的tcvr_on配置：
             1'b0：配置为低电平
             1'b1：配置为高电平
   UNION结构:  BBPCOMM_GS_TCVR_ON_UNION */
#define BBPCOMM_GS_TCVR_ON_ADDR                       (SOC_BBP_COMM_BASE_ADDR + 0x19C)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      c2 的tcvr_on配置：
             1'b0：配置为低电平
             1'b1：配置为高电平
   UNION结构:  BBPCOMM_C_TCVR_ON_UNION */
#define BBPCOMM_C_TCVR_ON_ADDR                        (SOC_BBP_COMM_BASE_ADDR + 0x1A0)

/* 寄存器说明：寄存器
 bit[31:5]   保留
 bit[4]      ch0 DSP强制的tcvr_on_rx 配置：
             1'b0：配置为低电平
             1'b1：配置为高电平
 bit[3:1]    保留
 bit[0]      CH0 的tcvr_on_rx来源选择：
             1'b0：来自于逻辑选通
             1'b1：来自于DSP配置，ch0_tcvr_on_rx_dsp
   UNION结构:  BBPCOMM_CH0_TCVR_ON_RX_SEL_UNION */
#define BBPCOMM_CH0_TCVR_ON_RX_SEL_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x1A4)

/* 寄存器说明：寄存器
 bit[31:5]   保留
 bit[4]      ch1 DSP的tcvr_on_rx 配置：
             1'b0：配置为低电平
             1'b1：配置为高电平
 bit[3:1]    保留
 bit[0]      CH1 的tcvr_on_rx来源选择：
             1'b0：来自于逻辑选通
             1'b1：来自于DSP配置，ch1_tcvr_on_rx_dsp
   UNION结构:  BBPCOMM_CH1_TCVR_ON_RX_SEL_UNION */
#define BBPCOMM_CH1_TCVR_ON_RX_SEL_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x1A8)

/* 寄存器说明：寄存器
 bit[31:5]   保留
 bit[4]      ch2 DSP的tcvr_on_rx 配置：
             1'b0：配置为低电平
             1'b1：配置为高电平
 bit[3:1]    保留
 bit[0]      CH2 的tcvr_on_rx来源选择：
             1'b0：来自于逻辑选通
             1'b1：来自于DSP配置，ch2_tcvr_on_rx_dsp
   UNION结构:  BBPCOMM_CH2_TCVR_ON_RX_SEL_UNION */
#define BBPCOMM_CH2_TCVR_ON_RX_SEL_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x1AC)

/* 寄存器说明：寄存器
 bit[31:5]   保留
 bit[4]      ch3 DSP的tcvr_on_rx 配置：
             1'b0：配置为低电平
             1'b1：配置为高电平
 bit[3:1]    保留
 bit[0]      CH3 的tcvr_on_rx来源选择：
             1'b0：来自于逻辑选通
             1'b1：来自于DSP配置，ch3_tcvr_on_rx_dsp
   UNION结构:  BBPCOMM_CH3_TCVR_ON_RX_SEL_UNION */
#define BBPCOMM_CH3_TCVR_ON_RX_SEL_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x1B0)

/* 寄存器说明：寄存器
 bit[31:5]   保留
 bit[4]      ch0 DSP强制的tcvr_on_tx 配置：
             1'b0：配置为低电平
             1'b1：配置为高电平
 bit[3:1]    保留
 bit[0]      CH0 的tcvr_on_tx来源选择：
             1'b0：来自于逻辑选通
             1'b1：来自于DSP配置，ch0_tcvr_on_tx_dsp
   UNION结构:  BBPCOMM_CH0_TCVR_ON_TX_SEL_UNION */
#define BBPCOMM_CH0_TCVR_ON_TX_SEL_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x1B4)

/* 寄存器说明：寄存器
 bit[31:5]   保留
 bit[4]      ch1 DSP的tcvr_on_tx 配置：
             1'b0：配置为低电平
             1'b1：配置为高电平
 bit[3:1]    保留
 bit[0]      CH1 的tcvr_on_tx来源选择：
             1'b0：来自于逻辑选通
             1'b1：来自于DSP配置，ch1_tcvr_on_tx_dsp
   UNION结构:  BBPCOMM_CH1_TCVR_ON_TX_SEL_UNION */
#define BBPCOMM_CH1_TCVR_ON_TX_SEL_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x1B8)

/* 寄存器说明：寄存器
 bit[31:5]   保留
 bit[4]      ch2 DSP的tcvr_on_tx 配置：
             1'b0：配置为低电平
             1'b1：配置为高电平
 bit[3:1]    保留
 bit[0]      CH2 的tcvr_on_tx来源选择：
             1'b0：来自于逻辑选通
             1'b1：来自于DSP配置，ch2_tcvr_on_tx_dsp
   UNION结构:  BBPCOMM_CH2_TCVR_ON_TX_SEL_UNION */
#define BBPCOMM_CH2_TCVR_ON_TX_SEL_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x1BC)

/* 寄存器说明：寄存器
 bit[31:5]   保留
 bit[4]      ch3 DSP的tcvr_on_tx 配置：
             1'b0：配置为低电平
             1'b1：配置为高电平
 bit[3:1]    保留
 bit[0]      CH3 的tcvr_on_tx来源选择：
             1'b0：来自于逻辑选通
             1'b1：来自于DSP配置，ch3_tcvr_on_tx_dsp
   UNION结构:  BBPCOMM_CH3_TCVR_ON_TX_SEL_UNION */
#define BBPCOMM_CH3_TCVR_ON_TX_SEL_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x1C0)

/* 寄存器说明：寄存器
 bit[31:8]   保留
 bit[7:4]    输出管脚ch0_tcvr_on_out映射配置：
             bit3：
             1：ch3_tcvr_on_tx拉高即拉高
             0：不来自于ch3_tcvr_on_tx
             bit2：
             1：ch2_tcvr_on_tx拉高即拉高
             0：不来自于ch2_tcvr_on_tx
             bit1：
             1：ch1_tcvr_on_tx拉高即拉高
             0：不来自于ch1_tcvr_on_tx
             bit0：
             1：ch0_tcvr_on_tx拉高即拉高
             0：不来自于ch0_tcvr_on_tx
 bit[3:0]    输出管脚ch0_tcvr_on_out映射配置：
             bit3：
             1：ch3_tcvr_on_rx拉高即拉高
             0：不来自于ch3_tcvr_on_rx
             bit2：
             1：ch2_tcvr_on_rx拉高即拉高
             0：不来自于ch2_tcvr_on_rx
             bit1：
             1：ch1_tcvr_on_rx拉高即拉高
             0：不来自于ch1_tcvr_on_rx
             bit0：
             1：ch0_tcvr_on_rx拉高即拉高
             0：不来自于ch0_tcvr_on_rx
   UNION结构:  BBPCOMM_CH0_TCVR_ON_OUT_CFG_UNION */
#define BBPCOMM_CH0_TCVR_ON_OUT_CFG_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x1C4)

/* 寄存器说明：寄存器
 bit[31:8]   保留
 bit[7:4]    输出管脚ch1_tcvr_on_out映射配置：
             bit3：
             1：ch3_tcvr_on_tx拉高即拉高
             0：不来自于ch3_tcvr_on_tx
             bit2：
             1：ch2_tcvr_on_tx拉高即拉高
             0：不来自于ch2_tcvr_on_tx
             bit1：
             1：ch1_tcvr_on_tx拉高即拉高
             0：不来自于ch1_tcvr_on_tx
             bit0：
             1：ch0_tcvr_on_tx拉高即拉高
             0：不来自于ch0_tcvr_on_tx
 bit[3:0]    输出管脚ch1_tcvr_on_out映射配置：
             bit3：
             1：ch3_tcvr_on_rx拉高即拉高
             0：不来自于ch3_tcvr_on_rx
             bit2：
             1：ch2_tcvr_on_rx拉高即拉高
             0：不来自于ch2_tcvr_on_rx
             bit1：
             1：ch1_tcvr_on_rx拉高即拉高
             0：不来自于ch1_tcvr_on_rx
             bit0：
             1：ch0_tcvr_on_rx拉高即拉高
             0：不来自于ch0_tcvr_on_rx
   UNION结构:  BBPCOMM_CH1_TCVR_ON_OUT_CFG_UNION */
#define BBPCOMM_CH1_TCVR_ON_OUT_CFG_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x1C8)

/* 寄存器说明：寄存器
 bit[31:8]   保留
 bit[7:4]    输出管脚ch2_tcvr_on_out映射配置：
             bit3：
             1：ch3_tcvr_on_tx拉高即拉高
             0：不来自于ch3_tcvr_on_tx
             bit2：
             1：ch2_tcvr_on_tx拉高即拉高
             0：不来自于ch2_tcvr_on_tx
             bit1：
             1：ch1_tcvr_on_tx拉高即拉高
             0：不来自于ch1_tcvr_on_tx
             bit0：
             1：ch0_tcvr_on_tx拉高即拉高
             0：不来自于ch0_tcvr_on_tx
 bit[3:0]    输出管脚ch2_tcvr_on_out映射配置：
             bit3：
             1：ch3_tcvr_on_rx拉高即拉高
             0：不来自于ch3_tcvr_on_rx
             bit2：
             1：ch2_tcvr_on_rx拉高即拉高
             0：不来自于ch2_tcvr_on_rx
             bit1：
             1：ch1_tcvr_on_rx拉高即拉高
             0：不来自于ch1_tcvr_on_rx
             bit0：
             1：ch0_tcvr_on_rx拉高即拉高
             0：不来自于ch0_tcvr_on_rx
   UNION结构:  BBPCOMM_CH2_TCVR_ON_OUT_CFG_UNION */
#define BBPCOMM_CH2_TCVR_ON_OUT_CFG_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x1CC)

/* 寄存器说明：寄存器
 bit[31:8]   保留
 bit[7:4]    输出管脚ch3_tcvr_on_out映射配置：
             bit3：
             1：ch3_tcvr_on_tx拉高即拉高
             0：不来自于ch3_tcvr_on_tx
             bit2：
             1：ch2_tcvr_on_tx拉高即拉高
             0：不来自于ch2_tcvr_on_tx
             bit1：
             1：ch1_tcvr_on_tx拉高即拉高
             0：不来自于ch1_tcvr_on_tx
             bit0：
             1：ch0_tcvr_on_tx拉高即拉高
             0：不来自于ch0_tcvr_on_tx
 bit[3:0]    输出管脚ch3_tcvr_on_out映射配置：
             bit3：
             1：ch3_tcvr_on_rx拉高即拉高
             0：不来自于ch3_tcvr_on_rx
             bit2：
             1：ch2_tcvr_on_rx拉高即拉高
             0：不来自于ch2_tcvr_on_rx
             bit1：
             1：ch1_tcvr_on_rx拉高即拉高
             0：不来自于ch1_tcvr_on_rx
             bit0：
             1：ch0_tcvr_on_rx拉高即拉高
             0：不来自于ch0_tcvr_on_rx
   UNION结构:  BBPCOMM_CH3_TCVR_ON_OUT_CFG_UNION */
#define BBPCOMM_CH3_TCVR_ON_OUT_CFG_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x1D0)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      comm控制sc_pll使能，1：通过comm控制sc_pll，0：不通过comm控制sc_pll
   UNION结构:  BBPCOMM_CPU_CFG_SC_EN_UNION */
#define BBPCOMM_CPU_CFG_SC_EN_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x1E0)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      comm向sc_pll发送中断1使能，1：有效，0无效
   UNION结构:  BBPCOMM_CPU_INT1_CFG_SC_EN_UNION */
#define BBPCOMM_CPU_INT1_CFG_SC_EN_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x1E4)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      comm向sc_pll发送中断2使能，1：有效，0无效
   UNION结构:  BBPCOMM_CPU_INT2_CFG_SC_EN_UNION */
#define BBPCOMM_CPU_INT2_CFG_SC_EN_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x1E8)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      软件向sc_pll配置的主模的ind信号
   UNION结构:  BBPCOMM_CPU_PRO_SOFT_CFG_SC_IND_UNION */
#define BBPCOMM_CPU_PRO_SOFT_CFG_SC_IND_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0x1EC)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      软件向sc_pll配置的从模的ind信号
   UNION结构:  BBPCOMM_CPU_SEC_SOFT_CFG_SC_IND_UNION */
#define BBPCOMM_CPU_SEC_SOFT_CFG_SC_IND_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0x1F0)

/* 寄存器说明：寄存器
 bit[31:2]   保留
 bit[1:0]    0：根据通道0主从模产生配置sc_pll信号
             1：根据通道1主从模产生配置sc_pll信号
             2：根据通道2主从模产生配置sc_pll信号
             3：根据通道3主从模产生配置sc_pll信号
   UNION结构:  BBPCOMM_CPU_SC_CH_SEL_UNION */
#define BBPCOMM_CPU_SC_CH_SEL_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x1F4)

/* 寄存器说明：寄存器
   详      述：保留
   UNION结构 ：无 */
#define BBPCOMM_TIMING_REV0_ADDR                      (SOC_BBP_COMM_BASE_ADDR + 0x200)

/* 寄存器说明：定时锁存使能指示寄存器
 bit[31:6]   保留
 bit[5:4]    L/T模BBE16 DSP读取C2模bbp计数器结果1x、evdo还是base_cnt。   00：1x定时，01：evdo定时，10： base_cnt ，11：无效。
             
 bit[3:1]    保留
 bit[0]      逻辑自清零。
             L/T模BBE16 DSP需要获取定时关系时配置生效，CTU逻辑根据此信号锁存LTE/W/Gm/Gs/TDS/C的系统定时，CTU的内部定时供DSP查询。
             
   UNION结构:  BBPCOMM_TIMING_GET_IND_UNION */
#define BBPCOMM_TIMING_GET_IND_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0x204)

/* 寄存器说明：定时标志清除寄存器
   详      述：保留
   UNION结构 ：无 */
#define BBPCOMM_TIMING_REV1_ADDR                      (SOC_BBP_COMM_BASE_ADDR + 0x208)

/* 寄存器说明：定时锁存延迟寄存器
   详      述：保留
   UNION结构 ：无 */
#define BBPCOMM_TIMING_REV2_ADDR                      (SOC_BBP_COMM_BASE_ADDR + 0x20C)

/* 寄存器说明：中断延迟寄存器
 bit[31:16]  保留
 bit[15:0]   CTU中断上报等待时间，单位为一个CLK周期。
             DSP清除中断标志寄存器的某种类型bit后，CTU上报中断电平需要拉低，如果此时中断标志寄存器还有其它中断类型有效，则需等待int_wait_cnt个时钟周期后再拉高CTU上报中断。
             配置时刻：上电初始化
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_WAIT_CNT_UNION */
#define BBPCOMM_INT_WAIT_CNT_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x210)

/* 寄存器说明：寄存器
   详      述：用于提供w的复帧号，由wDSP更新。
               配置时刻：
               生效时刻：触发后检测o_timing_valid为1有效。
   UNION结构 ：无 */
#define BBPCOMM_W_MUX_FRAME_NUM_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0x214)

/* 寄存器说明：寄存器
 bit[31:6]   保留
 bit[5:4]    上报c2模的计数器给L/T模BBE16 DSP的是1x、evdo还是base_cnt
             00：1x定时
             01： evdo定时
             10： basecent
 bit[3:1]    保留
 bit[0]      定时上报有效标志，高有效。
             L/T模BBE16 DSP配置timing_get_ind后，查询此标志，如果为高，则可以获取LTE，W，Gm，Gs, TDS的系统定时。
             DSP读取定时，在DSP下次启动新的timing_get_ind时拉低此信号。
             
             
   UNION结构:  BBPCOMM_TIMING_VALID_UNION */
#define BBPCOMM_TIMING_VALID_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x218)

/* 寄存器说明：寄存器
 bit[31:20]  L/T模BBE16 DSP读取W的系统定时信息，由DSP 配置timing_get_ind触发上报。
             上报时刻：触发后检测o_timing_valid为1有效。
             [31:20]表示W的SFN计数（源自w_timing_b[11:0]），范围0~4095。
 bit[19:16]  [19:16]为时隙计数，范围0~14
 bit[15:4]   [15:4]为时隙内chip计数，范围0~2559
 bit[3:0]    [3:0]为chip内时钟计数，范围0~15
   UNION结构:  BBPCOMM_W_TIMING_DSP_UNION */
#define BBPCOMM_W_TIMING_DSP_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x21C)

/* 寄存器说明：寄存器
   详      述：用于提供w的复帧号，由L/T模BBE16 DSP 配置timing_get_ind触发上报。上报时刻：触发后检测o_timing_valid为1有效。
   UNION结构 ：无 */
#define BBPCOMM_W_MUX_FRAME_NUM_BBP_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x220)

/* 寄存器说明：寄存器
 bit[31:22]  保留
 bit[21:0]   GM的FN计数（源自gm_timing_a[21:0]），由L/T模BBE16 DSP配置timing_get_ind触发上报。其中[10:0]表示fn_low,范围0~1325；[21:11]表示fn_hign,范围0~2047。
             上报时刻：触发后立即生效
   UNION结构:  BBPCOMM_GM_FN_DSP_UNION */
#define BBPCOMM_GM_FN_DSP_ADDR                        (SOC_BBP_COMM_BASE_ADDR + 0x224)

/* 寄存器说明：寄存器
 bit[31:13]  保留
 bit[12:0]   GM的系统定时Qb信息，由L/T模BBE16 DSP配置timing_get_ind触发上报。
              [12:0]表示 G系统定时帧内Qb计数（源自gm_timing_b[12:0]），范围0~4999。
             上报时刻：触发后立即生效
   UNION结构:  BBPCOMM_GM_QB_DSP_UNION */
#define BBPCOMM_GM_QB_DSP_ADDR                        (SOC_BBP_COMM_BASE_ADDR + 0x228)

/* 寄存器说明：寄存器
   详      述：用于提供gm的复帧号，由gmDSP更新。
               配置时刻：
               生效时刻：触发后检测o_timing_valid为1有效。
   UNION结构 ：无 */
#define BBPCOMM_GM_MUX_FRAME_NUM_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x22C)

/* 寄存器说明：寄存器
 bit[31:22]  保留
 bit[21:0]   GS的FN计数（源自gs_timing_a[21:0]），由L/T模BBE16 DSP配置timing_get_ind触发上报。其中[10:0]表示fn_low,范围0~1325；[21:11]表示fn_hign,范围0~2047。
             上报时刻：触发后立即生效
   UNION结构:  BBPCOMM_GS_FN_DSP_UNION */
#define BBPCOMM_GS_FN_DSP_ADDR                        (SOC_BBP_COMM_BASE_ADDR + 0x230)

/* 寄存器说明：寄存器
 bit[31:13]  保留
 bit[12:0]   GS的系统定时Qb信息，由L/T模BBE16 DSP配置timing_get_ind触发上报。
              [12:0]表示 GS系统定时帧内Qb计数（源自gs_timing_b[12:0]），范围0~4999。
             上报时刻：触发后立即生效
   UNION结构:  BBPCOMM_GS_QB_DSP_UNION */
#define BBPCOMM_GS_QB_DSP_ADDR                        (SOC_BBP_COMM_BASE_ADDR + 0x234)

/* 寄存器说明：寄存器
   详      述：用于提供gs的复帧号，由gsDSP更新。
               配置时刻：
               生效时刻：触发后检测o_timing_valid为1有效。
   UNION结构 ：无 */
#define BBPCOMM_GS_MUX_FRAME_NUM_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x238)

/* 寄存器说明：寄存器
 bit[31:30]  保留
 bit[29:20]  LTE的系统定时。由L/T模BBE16 DSP配置timing_get_ind触发上报。
             上报时刻：触发后立即生效
             其中:
             [29:20]表示SFN计数，范围0~1023
 bit[19:16]  [19:16]是子帧计数
 bit[15:15]  保留
 bit[14:0]   [14:0]是子帧内计数。 
   UNION结构:  BBPCOMM_LTE_TIMING_DSP_UNION */
#define BBPCOMM_LTE_TIMING_DSP_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0x23C)

/* 寄存器说明：寄存器
   详      述：用于提供LTE的复帧号。由L/T模BBE16 DSP配置timing_get_ind触发上报。
               上报时刻：触发后检测o_timing_valid为1有效。
   UNION结构 ：无 */
#define BBPCOMM_LTE_MUX_FRAME_NUM_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x240)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   TDS的系统定时。由L/T模BBE16 DSP配置timing_get_ind触发上报。本寄存器上报的是TDS的tcfsr系统子帧号0~65535循环计数，TDS实际有效子帧范围为0~8191
             上报时刻：触发后立即生效
   UNION结构:  BBPCOMM_TDS_TIMING1_DSP_UNION */
#define BBPCOMM_TDS_TIMING1_DSP_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0x244)

/* 寄存器说明：寄存器
 bit[31:20]  保留
 bit[19:0]   TDS的系统定时。由L/T模BBE16 DSP 配置timing_get_ind触发上报。本寄存器上报的是是TDS的framc帧计数
             上报时刻：触发后立即生效
   UNION结构:  BBPCOMM_TDS_TIMING2_DSP_UNION */
#define BBPCOMM_TDS_TIMING2_DSP_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0x248)

/* 寄存器说明：寄存器
   详      述：用于提供LTE的复帧号。由L/T模BBE16 DSP配置timing_get_ind触发上报。
               上报时刻：触发后检测o_timing_valid为1有效。
   UNION结构 ：无 */
#define BBPCOMM_TDS_MUX_FRAME_NUM_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x24C)

/* 寄存器说明：寄存器
 bit[31:30]  保留
 bit[29:0]   C2模定时信息上报。 
             1X模式：
             Bit[4:0]   1/4chip     计数范围0~24  
             Bit[6:5]   chip        计数范围0~3
             Bit[17:7]  chip number 计数范围0~1535
             Bit[23:18] 80ms        计数范围0~63
             Bit[29:24] 2s/5.12s超帧计数范围0~24/0~63
             EVDO：
             Bit[4:0]   1/4chip     计数范围0~24  Bit[6:5]   chip        计数范围0~3
             Bit[21:7]  chip number 计数范围0~32767
             Bit[23:22] 80ms        计数范围0~63
             Bit[29:24] 2s/5.12s超帧计数范围0~24/0~63
             BASE_CNT：
             Bit[4:0]   1/4chip     计数范围0~24  
             Bit[6:5]   chip        计数范围0~3
             Bit[21:7]  chip number 计数范围0~32767
             Bit[23:22]  80ms       计数范围0~63
             Bit[28:24]  2s超帧     计数范围0~24
   UNION结构:  BBPCOMM_C_TIMING_DSP_UNION */
#define BBPCOMM_C_TIMING_DSP_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x250)

/* 寄存器说明：寄存器
   详      述：CTU内部定时，由L/T模BBE16 DSP配置timing_get_ind触发上报。计数器使用clk_19m_bbp_soc时钟,32比特计满再从头开始计数
               上报时刻：触发后检测o_timing_valid为1有效。
   UNION结构 ：无 */
#define BBPCOMM_CTU_TIMING_DSP_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0x254)

/* 寄存器说明：寄存器
   详      述：32K公共定时器的定时信息，由L/T模BBE16 DSP配置timing_get_ind1触发上报。32比特计数计满后再从头开始计数。
               上报时刻：触发后检测o_timing_valid1为1有效。
   UNION结构 ：无 */
#define BBPCOMM_COMM_32K_TIMING_RPT1_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x258)

/* 寄存器说明：寄存器
   详      述：CTU内部定时。使用clk_19m_bbp_soc时钟计数。
               各主模在int0、int1、int2的时刻触发上报。
   UNION结构 ：无 */
#define BBPCOMM_CTU_BASECNT2_DSP_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x25C)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:8]   通过xbbp向SSI master发出回读类指令时,DSP等待回读结果长度配置
 bit[7:0]    通过xbbp向MIPI master发出回读类指令时,DSP等待回读结果长度配置
   UNION结构:  BBPCOMM_DSP_WAITTIME_UNION */
#define BBPCOMM_DSP_WAITTIME_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x260)

/* 寄存器说明：寄存器
   详      述：CTU内部定时计数器，有时钟就计数，计满从头开始。计数器使用clk_19m_bbp_soc时钟
               上报时刻：随时读取。
   UNION结构 ：无 */
#define BBPCOMM_CTU_BASECNT1_DSP_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x264)

/* 寄存器说明：寄存器
   详      述：保留
   UNION结构 ：无 */
#define BBPCOMM_TIMING_REV3_ADDR                      (SOC_BBP_COMM_BASE_ADDR + 0x268)

/* 寄存器说明：寄存器
   详      述：保留
   UNION结构 ：无 */
#define BBPCOMM_TIMING_REV4_ADDR                      (SOC_BBP_COMM_BASE_ADDR + 0x26C)

/* 寄存器说明：定时锁存使能指示寄存器
 bit[31:6]   保留
 bit[5:4]    arm读取C2模bbp计数器结果1x、evdo还是base_cnt。   00：1x定时，01：evdo定时，10： base_cnt ，11：无效。
             
 bit[3:1]    保留
 bit[0]      逻辑自清零。
             arm需要获取定时关系时配置生效，CTU逻辑根据此信号锁存LTE/W/Gm/Gs/TDS/C的系统定时，CTU的内部定时供DSP查询。
             
   UNION结构:  BBPCOMM_TIMING_GET_IND1_UNION */
#define BBPCOMM_TIMING_GET_IND1_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0x270)

/* 寄存器说明：寄存器
   详      述：保留
   UNION结构 ：无 */
#define BBPCOMM_TIMING_REV5_ADDR                      (SOC_BBP_COMM_BASE_ADDR + 0x274)

/* 寄存器说明：寄存器
 bit[31:2]   保留
 bit[1:0]    L/T模BBE16 DSP读取W模bbp计数器结果sys_cnt还是base_cnt。00（二进制）：sys_cnt，01：base_cnt 10：无效 11：无效
             timing_get_mode无效时，不需配置，无意义
   UNION结构:  BBPCOMM_TIMING_GET_W_SEL_UNION */
#define BBPCOMM_TIMING_GET_W_SEL_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x278)

/* 寄存器说明：寄存器
 bit[31:2]   保留
 bit[1:0]    上报w模的计数器给L/T模BBE16 DSP的是sys_cnt还是base_cnt
             00（二进制）： sys_cnt
             01： basecent 10：无效  11：无效 
   UNION结构:  BBPCOMM_TIMING_VALID_W_SEL_UNION */
#define BBPCOMM_TIMING_VALID_W_SEL_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x27C)

/* 寄存器说明：寄存器
 bit[31:2]   保留
 bit[1:0]    ARM读取W模bbp计数器结果sys_cnt还是base_cnt。00（二进制）：sys_cnt，01：base_cnt 10：无效 11：无效
             timing_get_mode无效时，不需配置，无意义
   UNION结构:  BBPCOMM_TIMING_GET_W_SEL1_UNION */
#define BBPCOMM_TIMING_GET_W_SEL1_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x280)

/* 寄存器说明：寄存器
 bit[31:2]   保留
 bit[1:0]    上报的计数器给arm的是w模bbp的sys_cnt还是base_cnt
             00：sys_cnt定时
             01：base_cnt定时 
             10：无效
             11：无效
   UNION结构:  BBPCOMM_TIMING_VALID_W_SEL1_UNION */
#define BBPCOMM_TIMING_VALID_W_SEL1_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x284)

/* 寄存器说明：寄存器
   详      述：保留
   UNION结构 ：无 */
#define BBPCOMM_TIMING_REV6_ADDR                      (SOC_BBP_COMM_BASE_ADDR + 0x288)

/* 寄存器说明：寄存器
   详      述：CTU内部19.2M钟驱动定时计数器上报结果
   UNION结构 ：无 */
#define BBPCOMM_CTU_BASECNT_DSP_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0x28C)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      CTU内部19.2M钟驱动定时计数器结果读取使能
   UNION结构:  BBPCOMM_DSP_CTU_TIMING_GET_IND_UNION */
#define BBPCOMM_DSP_CTU_TIMING_GET_IND_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0x290)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      CTU内部19.2M钟驱动定时计数器结果读取有效指示
   UNION结构:  BBPCOMM_CTU_TIMING_VALID_DSP_UNION */
#define BBPCOMM_CTU_TIMING_VALID_DSP_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x294)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      CTU内部19.2M钟驱动定时计数器结果读取后清零使能
   UNION结构:  BBPCOMM_DSP_CTU_TIMING_CLR_UNION */
#define BBPCOMM_DSP_CTU_TIMING_CLR_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x298)

/* 寄存器说明：寄存器
   详      述：W/TD/GM/GS/C为主模时写此寄存器，L为从模时读取此寄存器。此寄存器由DSP之间进行读写，BBP仅提供接口。
   UNION结构 ：无 */
#define BBPCOMM_MEAS_FLAG_L_RD_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0x29C)

/* 寄存器说明：寄存器
   详      述：L/TD/GM/GS/C为主模时写此寄存器，W为从模时读取此寄存器。此寄存器由DSP之间进行读写，BBP仅提供接口。
   UNION结构 ：无 */
#define BBPCOMM_MEAS_FLAG_W_RD_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0x2A0)

/* 寄存器说明：寄存器
   详      述：W/L/GM/GS为/C主模时写此寄存器，TD为从模时读取此寄存器。此寄存器由DSP之间进行读写，BBP仅提供接口。
   UNION结构 ：无 */
#define BBPCOMM_MEAS_FLAG_T_RD_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0x2A4)

/* 寄存器说明：寄存器
   详      述：W/TD/L/GS/C为主模时写此寄存器，GM为从模时读取此寄存器。此寄存器由DSP之间进行读写，BBP仅提供接口。
   UNION结构 ：无 */
#define BBPCOMM_MEAS_FLAG_GM_RD_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0x2A8)

/* 寄存器说明：寄存器
   详      述：W/TD/GM/L/C为主模时写此寄存器，GS为从模时读取此寄存器。此寄存器由DSP之间进行读写，BBP仅提供接口。
   UNION结构 ：无 */
#define BBPCOMM_MEAS_FLAG_GS_RD_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0x2AC)

/* 寄存器说明：寄存器
   详      述：L为从模时写此寄存器，W/TD/GM/GS/C主模读取此寄存器。此寄存器由DSP之间进行读写，BBP仅提供接口。
   UNION结构 ：无 */
#define BBPCOMM_WAKE_FLAG_L_WR_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0x2B0)

/* 寄存器说明：寄存器
   详      述：W为从模时写此寄存器，L/TD/GM/GS/C主模读取此寄存器。此寄存器由DSP之间进行读写，BBP仅提供接口。
   UNION结构 ：无 */
#define BBPCOMM_WAKE_FLAG_W_WR_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0x2B4)

/* 寄存器说明：寄存器
   详      述：TD为从模时写此寄存器，W/L/GM/GS/C主模读取此寄存器。此寄存器由DSP之间进行读写，BBP仅提供接口。
   UNION结构 ：无 */
#define BBPCOMM_WAKE_FLAG_T_WR_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0x2B8)

/* 寄存器说明：寄存器
   详      述：GM为从模时写此寄存器，W/TD/L/GS/C主模读取此寄存器。此寄存器由DSP之间进行读写，BBP仅提供接口。
   UNION结构 ：无 */
#define BBPCOMM_WAKE_FLAG_GM_WR_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0x2BC)

/* 寄存器说明：寄存器
   详      述：GS为从模时写此寄存器，W/TD/GM/L/C主模读取此寄存器。此寄存器由DSP之间进行读写，BBP仅提供接口。
   UNION结构 ：无 */
#define BBPCOMM_WAKE_FLAG_GS_WR_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0x2C0)

/* 寄存器说明：寄存器
 bit[31:2]   保留
 bit[1:0]    C模BBE16 DSP读取W模bbp计数器结果sys_cnt还是base_cnt。00（二进制）：sys_cnt，01：base_cnt 10：无效 11：无效
             timing_get_mode无效时，不需配置，无意义
   UNION结构:  BBPCOMM_TIMING_GET_W_SEL2_UNION */
#define BBPCOMM_TIMING_GET_W_SEL2_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x2C4)

/* 寄存器说明：寄存器
 bit[31:2]   保留
 bit[1:0]    上报的计数器给C模BBE16 DSP的是w模bbp的sys_cnt还是base_cnt
             00：sys_cnt定时
             01：base_cnt定时 
             10：无效
             11：无效
   UNION结构:  BBPCOMM_TIMING_VALID_W_SEL2_UNION */
#define BBPCOMM_TIMING_VALID_W_SEL2_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x2C8)

/* 寄存器说明：定时锁存使能指示寄存器
 bit[31:6]   保留
 bit[5:4]    C2模BBE16 DSP读取C模bbp计数器结果1x、evdo还是base_cnt。   00：1x定时，01：evdo定时，10： base_cnt ，11：无效。
             
 bit[3:1]    保留
 bit[0]      逻辑自清零。
             arm需要获取定时关系时配置生效，CTU逻辑根据此信号锁存LTE/W/Gm/Gs/TDS/C的系统定时，CTU的内部定时供DSP查询。
             
   UNION结构:  BBPCOMM_TIMING_GET_IND2_UNION */
#define BBPCOMM_TIMING_GET_IND2_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0x2CC)

/* 寄存器说明：寄存器
 bit[31:8]   保留
 bit[7:0]    定时锁存各类定时等待时间，19.2M时钟域
   UNION结构:  BBPCOMM_TIMING_WAIT_CNT_UNION */
#define BBPCOMM_TIMING_WAIT_CNT_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0x2D0)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0:0]    线控tas_ind输出控制信号
             0：tas_ind直接输出
             1：tas_ind取反输出
   UNION结构:  BBPCOMM_TAS_IND_CTRL_UNION */
#define BBPCOMM_TAS_IND_CTRL_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x2D4)

/* 寄存器说明：寄存器
 bit[31:17]  保留
 bit[16:0]   tuner gpio输出信号屏蔽控制寄存器，bit0~bit16对应的屏蔽信号如下：
             bit0: m1_active_p；
             bit1: m1_active_s；
             bit2: m0_active；
             bit3：m0_line_p[0]；
             bit4：m0_line_p[1]；
             bit5：m0_line_p[2]；
             bit6：m0_line_p[3]；
             bit7：m0_line_s[0]；
             bit8：m0_line_s[1]；
             bit9：m0_line_s[2]；
             bit10：m0_line_s[3]；
             bit11：m1_line[0]；
             bit12：m1_line[1]；
             bit13：m1_line[2]；
             bit14：m1_line[3]；
             bit15：m1_line[4]；
             bit16：m1_line[5]；
             其中对应比特为1表示输出CTU的值，为0则使用tuner输出的GPIO值
   UNION结构:  BBPCOMM_TUNER_GPIO_LINE_MASK_UNION */
#define BBPCOMM_TUNER_GPIO_LINE_MASK_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x2D8)

/* 寄存器说明：寄存器
 bit[31:30]  保留
 bit[29:16]  软件配置的输出给abb0的上行数据，cpu_abb_ch0_tx_data_sel为0时选择输出
 bit[15:2]   保留
 bit[1]      ABB上行通道0 tx_en线控控制寄存器
             0：由软件控制输出，输出值由
             1：CTU逻辑选通输出
 bit[0]      ABB上行通道0 tx_en线控控制寄存器
             0：由ant_sel29控制输出
             1：CTU逻辑选通输出
   UNION结构:  BBPCOMM_CPU_ABB_CH0_TX_SEL_UNION */
#define BBPCOMM_CPU_ABB_CH0_TX_SEL_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x2DC)

/* 寄存器说明：寄存器
 bit[31:30]  保留
 bit[29:16]  软件配置的输出给abb1的上行数据，cpu_abb_ch1_tx_data_sel为0时选择输出
 bit[15:2]   保留
 bit[1]      ABB上行通道1 tx_en线控控制寄存器
             0：由软件控制输出，输出值由
             1：CTU逻辑选通输出
 bit[0]      ABB上行通道1 tx_en线控控制寄存器
             0：由ant_sel30控制输出
             1：CTU逻辑选通输出
   UNION结构:  BBPCOMM_CPU_ABB_CH1_TX_SEL_UNION */
#define BBPCOMM_CPU_ABB_CH1_TX_SEL_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x2E0)

/* 寄存器说明：寄存器
   详      述：软中断int1产生的绝对时标，19.2M时钟单位
   UNION结构 ：无 */
#define BBPCOMM_SOFT_INT1_TIMER_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0x2E4)

/* 寄存器说明：寄存器
   详      述：软中断int0相对于int1绝对时标提前量，19.2M时钟单位
   UNION结构 ：无 */
#define BBPCOMM_SOFT_INT0_INT1_TIMER_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x2E8)

/* 寄存器说明：寄存器
   详      述：软中断int2相对于int1绝对时标延后量，19.2M时钟单位
   UNION结构 ：无 */
#define BBPCOMM_SOFT_INT1_INT2_TIMER_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x2EC)

/* 寄存器说明：寄存器
 bit[31:3]   保留
 bit[2:0]    软中断软件配置的软件主模指示：
             000：LTE 主模。
             001：W主模。
             010：TDS主模。
             011：Gm主模；
             100：Gs主模；
             101:C2主模；
             110~111：无效。
             
   UNION结构:  BBPCOMM_SOFT_PRI_IND_RX_UNION */
#define BBPCOMM_SOFT_PRI_IND_RX_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0x2F0)

/* 寄存器说明：寄存器
 bit[31:3]   保留
 bit[2:0]    软中断软件配置的软件从模指示：
             000：LTE 从模。
             001：W从模。
             010：TDS从模。
             011：Gm从模；
             100：Gs从模；
             101:C2从模；
             110~111：无效。
             
   UNION结构:  BBPCOMM_SOFT_SEC_IND_UNION */
#define BBPCOMM_SOFT_SEC_IND_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x2F4)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      软中使能
             配置时刻：在定时及软件主从模配置完毕后打开使能。
             
             
   UNION结构:  BBPCOMM_SOFT_INT_EN_UNION */
#define BBPCOMM_SOFT_INT_EN_ADDR                      (SOC_BBP_COMM_BASE_ADDR + 0x2F8)

/* 寄存器说明：W为从模时对应通道的指示寄存器
 bit[31:5]   保留
 bit[4:4]    W为从模时对应的通道选择信号生效方式。
             0：在int1生效；
             1：立即生效。
 bit[3:2]    保留
 bit[1:0]    W为从模时对应的通道选择信号。
             0：选择通道0；
             1：选择通道1；
             2：选择通道2；
             3：选择通道3。
             配置时刻：各模根据通信场景配置
   UNION结构:  BBPCOMM_S_W_CH_NUM_IND_UNION */
#define BBPCOMM_S_W_CH_NUM_IND_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0x300)

/* 寄存器说明：寄存器
 bit[31:4]   保留
 bit[3:0]    异系统测量类型。
             4’b0：测量3G。
             4’b1: 3G背景搜；
             4’d2: 3G ANR。
             其它预留。
             生效时刻：立即生效
   UNION结构:  BBPCOMM_W_INTERSYS_MEASURE_TYPE_UNION */
#define BBPCOMM_W_INTERSYS_MEASURE_TYPE_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0x304)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0:0]    单频点测量周期到指示，L或者TDS/Gm/Gs作为主模，通知W DSP W测量的单频点周期到达。
             只在连接态下需要配置。
             电平信号，高有效。
             生效时刻：立即生效
   UNION结构:  BBPCOMM_W_MEASURE_REPORT_VALID_UNION */
#define BBPCOMM_W_MEASURE_REPORT_VALID_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0x308)

/* 寄存器说明：寄存器
   详      述：预处理中断int0到int1之间的offset信息，单位us（向下取整）。。
               配置时刻：主模启动W从模异系统测量时配置
               生效时刻：立即生效
   UNION结构 ：无 */
#define BBPCOMM_W_PREINT_OFFSET_TIME_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x30C)

/* 寄存器说明：寄存器
   详      述：W作为从模时，主模分配给W用于异系统测量时间长度，告知WDSP。单位us，向下取整到us。
               配置时刻：主模启动W从模异系统测量时配置
               生效时刻：立即生效
   UNION结构 ：无 */
#define BBPCOMM_W_INTERSYS_MEASURE_TIME_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0x310)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   逻辑自清零。
             中断标志清除指示，高有效。用于清除INT_TYPE_W_RCV_LTE[15:0]对应bit位
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_CLEAR_W_RCV_LTE_UNION */
#define BBPCOMM_INT_CLEAR_W_RCV_LTE_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x314)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   逻辑自清零。
             中断标志清除指示，高有效。用于清除INT_TYPE_W_RCV_TDS[15:0]对应bit位
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_CLEAR_W_RCV_TDS_UNION */
#define BBPCOMM_INT_CLEAR_W_RCV_TDS_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x318)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   逻辑自清零。
             中断标志清除指示，高有效。用于清除INT_TYPE_W_RCV_GM[15:0]对应bit位
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_CLEAR_W_RCV_GM_UNION */
#define BBPCOMM_INT_CLEAR_W_RCV_GM_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x31C)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   逻辑自清零。
             中断标志清除指示，高有效。用于清除INT_TYPE_W_RCV_GS[15:0]对应bit位
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_CLEAR_W_RCV_GS_UNION */
#define BBPCOMM_INT_CLEAR_W_RCV_GS_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x320)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   逻辑自清零。
             中断标志清除指示，高有效。用于清除INT_TYPE_W_RCV_W[15:0]对应bit位
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_CLEAR_W_RCV_W_UNION */
#define BBPCOMM_INT_CLEAR_W_RCV_W_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x324)

/* 寄存器说明：寄存器
 bit[31:3]   保留
 bit[2:0]    逻辑自清零。
             中断标志清除指示，高有效。用于清除INT_TYPE_W_INT012[2:0]对应bit位
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_CLEAR_W_INT012_UNION */
#define BBPCOMM_INT_CLEAR_W_INT012_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x328)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   中断屏蔽标志。用于屏蔽INT_TYPE_W_RCV_LTE[15:0]对应bit中断。
             0：屏蔽中断上报；
             1：使能中断上报。
             配置时刻：初始化
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_MASK_W_RCV_LTE_UNION */
#define BBPCOMM_INT_MASK_W_RCV_LTE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x32C)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   中断屏蔽标志。用于屏蔽INT_TYPE_W_RCV_TDS[15:0]对应bit中断。
             0：屏蔽中断上报；
             1：使能中断上报。
             配置时刻：初始化
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_MASK_W_RCV_TDS_UNION */
#define BBPCOMM_INT_MASK_W_RCV_TDS_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x330)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   中断屏蔽标志。用于屏蔽INT_TYPE_W_RCV_GM[15:0]对应bit中断。
             0：屏蔽中断上报；
             1：使能中断上报。
             配置时刻：初始化
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_MASK_W_RCV_GM_UNION */
#define BBPCOMM_INT_MASK_W_RCV_GM_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x334)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   中断屏蔽标志。用于屏蔽INT_TYPE_W_RCV_GS[15:0]对应bit中断。
             0：屏蔽中断上报；
             1：使能中断上报。
             配置时刻：初始化
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_MASK_W_RCV_GS_UNION */
#define BBPCOMM_INT_MASK_W_RCV_GS_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x338)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   中断屏蔽标志。用于屏蔽INT_TYPE_W_RCV_W[15:0]对应bit中断。
             0：屏蔽中断上报；
             1：使能中断上报。
             配置时刻：初始化
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_MASK_W_RCV_W_UNION */
#define BBPCOMM_INT_MASK_W_RCV_W_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x33C)

/* 寄存器说明：寄存器
 bit[31:3]   保留
 bit[2:0]    中断屏蔽标志。用于屏蔽INT_TYPE_W_INT012[2:0]对应bit中断。
             0：屏蔽中断上报；
             1：使能中断上报。
             配置时刻：初始化
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_MASK_W_INT012_UNION */
#define BBPCOMM_INT_MASK_W_INT012_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x340)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   中断状态标志。各bit单独对应一种中断类型，高有效。
             [0]: 中断类型0。 LTE（主模）提前通知W异系统测量启动中断。
             [1]: 中断类型1。 LTE（主模）进GAP中断，通知W进行异系统测量射频通道配置，天线切换等操作。
             [2]: 中断类型2。 LTE（主模）出GAP中断。
             [3]: 中断类型3。LTE（从模）测量结束中断。
             [4]: 中断类型4。LTE（主模）强制W退出异系统测量中断。
             [5]: 中断类型5。LTE（主模）通知W上报本次测量结果。
             [6]: 保留。
             [15:7]: 对应中断类型[15:7]，预留。
             软件读取该中断状态上报寄存器后，需要和0x06F0的int_mask_w_rcv_lte相与，再判断是否需要处理。
   UNION结构:  BBPCOMM_INT_TYPE_W_RCV_LTE_UNION */
#define BBPCOMM_INT_TYPE_W_RCV_LTE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x344)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   中断状态标志0，1，2只有当TDS处于主模时才能产生。
             
             [0]: 中断类型0。 TDS（主模）提前通知W异系统测量启动中断。
             [1]: 中断类型1。 TDS（主模）进GAP中断，通知W进行异系统测量射频通道配置，天线切换等操作。
             [2]: 中断类型2。 TDS（主模）出GAP中断。
             [3]: 中断类型3。TDS（从模）测量结束中断。
             [4]: 中断类型4。TDS（主模）强制W退出异系统测量中断。
             [5]: 中断类型5。TDS（主模）通知W上报本次测量结果。
             [6]: 中断类型6。保留。
             [15:7]: 对应中断类型[15:7]，预留。
             软件读取该中断状态上报寄存器后，需要和0x06F4的int_mask_w_rcv_tds相与，再判断是否需要处理。
   UNION结构:  BBPCOMM_INT_TYPE_W_RCV_TDS_UNION */
#define BBPCOMM_INT_TYPE_W_RCV_TDS_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x348)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   中断状态标志。各bit单独对应一种中断类型，高有效。
             [0]: 中断类型0。GM（主模）提前通知W异系统测量启动中断。
             [1]: 中断类型1。GM（主模）进GAP中断，通知W进行异系统测量射频通道配置，天线切换等操作。
             [2]: 中断类型2。GM（主模）出GAP中断。
             [3]: 中断类型3。GM（从模）测量结束中断。
             [4]: 中断类型4。GM（主模）强制W退出异系统测量中断。
             [5]: 中断类型5。GM（主模）通知W上报本次测量结果。
             [6]: 中断类型6。保留。
             [15:7]: 对应中断类型[15:7]，预留。
             中断状态标志0，1，2只有当GM处于主模时才能产生。
             软件读取该中断状态上报寄存器后，需要和0x06F8的int_mask_w_rcv_gm相与，再判断是否需要处理。
   UNION结构:  BBPCOMM_INT_TYPE_W_RCV_GM_UNION */
#define BBPCOMM_INT_TYPE_W_RCV_GM_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x34C)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   [0]: 中断类型0。GS（主模）提前通知W异系统测量启动中断。
             [1]: 中断类型1。GS（主模）进GAP中断，通知W进行异系统测量射频通道配置，天线切换等操作。
             [2]: 中断类型2。GS（主模）出GAP中断。
             [3]: 中断类型3。GS（从模）测量结束中断。
             [4]: 中断类型4。GS（主模）强制W退出异系统测量中断。
             [5]: 中断类型5。GS（主模）通知W上报本次测量结果。
             [6]: 中断类型6。保留。
             [15:7]: 对应中断类型[15:7]，预留。
             中断状态标志0，1，2只有当TDS处于主模时才能产生。
             软件读取该中断状态上报寄存器后，需要和0x06FC的int_mask_w_rcv_gs相与，再判断是否需要处理。
   UNION结构:  BBPCOMM_INT_TYPE_W_RCV_GS_UNION */
#define BBPCOMM_INT_TYPE_W_RCV_GS_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x350)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   中断状态标志。各bit单独对应一种中断类型，高有效。
             [0]: 中断类型0。W（主模）提前通知W异频测量启动中断。
             [1]: 中断类型1。W（主模）进GAP中断，通知W进行异频测量射频通道配置，天线切换等操作。
             [2]: 中断类型2。W（主模）出GAP中断。
             [3]: 中断类型3。W（从模，即异频）测量结束中断。
             [4]: 中断类型4。W（主模）强制W退出异频测量中断。
             [5]: 中断类型5。W（主模）通知W上报本次测量结果。
             [6]: 中断类型6。保留。
             [15:7]: 对应中断类型[15:7]，预留。
             中断状态标志0，1，2只有当W处于主模时才能产生。
             软件读取该中断状态上报寄存器后，需要和0x0700的int_mask_w_rcv_w相与，再判断是否需要处理。
   UNION结构:  BBPCOMM_INT_TYPE_W_RCV_W_UNION */
#define BBPCOMM_INT_TYPE_W_RCV_W_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x354)

/* 寄存器说明：寄存器
 bit[31:3]   保留
 bit[2:0]    增加主模产生int0、1、2的上报（(包括异频、异系统场景)），高有效。
             [0]: W主模时，CTU告诉通知WDSP产生int0中断。
             [1]: W主模时，CTU告诉通知WDSP产生int1中断。
             [2]: W主模时，CTU告诉通知WDSP产生int2中断。
             软件读取该中断状态上报寄存器后，需要和0x0704的int_mask_w_int012相与，再判断是否需要处理。
   UNION结构:  BBPCOMM_INT_TYPE_W_INT012_UNION */
#define BBPCOMM_INT_TYPE_W_INT012_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x358)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:3]   逻辑自清零。高有效。
             
             bit15~7：对应w_snd_lte_int_15 ~ 7。
             W DSP通过此寄存器触发类型15~7中断（int_type_lte_rcv_w[15:7]）给LDSP。
             生效时刻：立即生效
             
             bit6：对应w_snd_lte_int_6。
             WDSP通过此寄存器触发类型6中断（int_type_lte_rcv_w[6]）给LDSP。
             生效时刻：立即生效
             
             bit5：对应w_snd_lte_int_5。
             W主模时通知LDSP L测量周期到达，高有效。
             W DSP通过此寄存器触发类型5中断（int_type_lte_rcv_w[5]）给LDSP。
             生效时刻：立即生效
             
             bit4：对应w_snd_lte_int_4。
             W主模时强制退出异系统测量指示。高有效。
             W DSP通过此寄存器触发类型4中断（int_type_lte_rcv_w[4]）给LDSP。
             生效时刻：立即生效
             
             bit3：对应w_snd_lte_int_3。W测量结束指示，高有效。
             用于触发中断类型3 （int_type_lte_rcv_w[3]）给LDSP。L主模下对W进行异系统测量时，如果W测量结束，W DSP配置此标志为1。 
             生效时刻：立即生效
 bit[2:0]    保留
   UNION结构:  BBPCOMM_W_SND_LTE_INT_13_UNION */
#define BBPCOMM_W_SND_LTE_INT_13_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x35C)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:3]   逻辑自清零。高有效。
             
             bit15~7：对应w_snd_tds_int_15 ~ 7。
             W DSP通过此寄存器触发类型15~7中断（int_type_tds_rcv_w[15:7]）给TDSP。
             生效时刻：立即生效
             
             bit6：对应w_snd_tds_int_6。
             WDSP通过此寄存器触发类型6中断（int_type_tds_rcv_w[6]）给TDSP。
             生效时刻：立即生效
             
             bit5：对应w_snd_tds_int_5。
             W主模时通知TDSP T测量周期到达，高有效。
             W DSP通过此寄存器触发类型5中断（int_type_tds_rcv_w[5]）给TDSP。
             生效时刻：立即生效
             
             bit4：对应w_snd_tds_int_4。
             W主模时强制退出异系统测量指示。高有效。
             W DSP通过此寄存器触发类型4中断（int_type_tds_rcv_w[4]）给TDSP。
             生效时刻：立即生效
             
             bit3：对应w_snd_tds_int_3。W测量结束指示，高有效。
             用于触发中断类型3 （int_type_tds_rcv_w[3]）给TDSP。T主模下对W进行异系统测量时，如果W测量结束，W DSP配置此标志为1。 
             生效时刻：立即生效
 bit[2:0]    保留
   UNION结构:  BBPCOMM_W_SND_TDS_INT_13_UNION */
#define BBPCOMM_W_SND_TDS_INT_13_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x360)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:3]   逻辑自清零。高有效。
             
             bit15~7：对应w_snd_gm_int_15 ~ 7。
             W DSP通过此寄存器触发类型15~7中断（int_type_gm_rcv_w[15:7]）给GMDSP。
             生效时刻：立即生效
             
             bit6：对应w_snd_gm_int_6。
             WDSP通过此寄存器触发类型6中断（int_type_gm_rcv_w[6]）给GMDSP。
             生效时刻：立即生效
             
             bit5：对应w_snd_gm_int_5。
             W主模时通知GMDSP GM测量周期到达，高有效。
             W DSP通过此寄存器触发类型5中断（int_type_gm_rcv_w[5]）给GMDSP。
             生效时刻：立即生效
             
             bit4：对应w_snd_gm_int_4。
             W主模时强制退出异系统测量指示。高有效。
             W DSP通过此寄存器触发类型4中断（int_type_gm_rcv_w[4]）给GMDSP。
             生效时刻：立即生效
             
             bit3：对应w_snd_gm_int_3。W测量结束指示，高有效。
             用于触发中断类型3 （int_type_gm_rcv_w[3]）给GMDSP。GM主模下对W进行异系统测量时，如果W测量结束，W DSP配置此标志为1。 
             生效时刻：立即生效
 bit[2:0]    保留
   UNION结构:  BBPCOMM_W_SND_GM_INT_13_UNION */
#define BBPCOMM_W_SND_GM_INT_13_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0x364)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:3]   逻辑自清零。高有效。
             
             bit15~7：对应w_snd_gs_int_15 ~ 7。
             W DSP通过此寄存器触发类型15~7中断（int_type_gs_rcv_w[15:7]）给GSDSP。
             生效时刻：立即生效
             
             bit6：对应w_snd_gs_int_6。
             WDSP通过此寄存器触发类型6中断（int_type_gs_rcv_w[6]）给GSDSP。
             生效时刻：立即生效
             
             bit5：对应w_snd_gs_int_5。
             W主模时通知GSDSP GS测量周期到达，高有效。
             W DSP通过此寄存器触发类型5中断（int_type_gs_rcv_w[5]）给GSDSP。
             生效时刻：立即生效
             
             bit4：对应w_snd_gs_int_4。
             W主模时强制退出异系统测量指示。高有效。
             W DSP通过此寄存器触发类型4中断（int_type_gs_rcv_w[4]）给GSDSP。
             生效时刻：立即生效
             
             bit3：对应w_snd_gs_int_3。W测量结束指示，高有效。
             用于触发中断类型3 （int_type_gs_rcv_w[3]）给GSDSP。GS主模下对W进行异系统测量时，如果W测量结束，W DSP配置此标志为1。 
             生效时刻：立即生效
 bit[2:0]    保留
   UNION结构:  BBPCOMM_W_SND_GS_INT_13_UNION */
#define BBPCOMM_W_SND_GS_INT_13_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0x368)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:3]   逻辑自清零。高有效。
             
             bit15~7：对应w_snd_w_int_15 ~ 7。
             W DSP通过此寄存器触发类型15~7中断（int_type_w_rcv_w[15:7]）给WDSP。
             生效时刻：立即生效
             
             bit6：对应w_snd_w_int_6。
             WDSP通过此寄存器触发类型6中断（int_type_w_rcv_w[6]）给WDSP。
             生效时刻：立即生效
             
             bit5：对应w_snd_w_int_5。
             W主模时通知WDSP W测量周期到达，高有效。
             W DSP通过此寄存器触发类型5中断（int_type_w_rcv_w[5]）给WDSP。
             生效时刻：立即生效
             
             bit4：对应w_snd_w_int_4。
             W主模时强制退出异系统测量指示。高有效。
             W DSP通过此寄存器触发类型4中断（int_type_w_rcv_w[4]）给WDSP。
             生效时刻：立即生效
             
             bit3：对应w_snd_w_int_3。W测量结束指示，高有效。
             用于触发中断类型3 （int_type_w_rcv_w[3]）给WDSP。W主模下对W进行异系统测量时，如果W测量结束，W DSP配置此标志为1。 
             生效时刻：立即生效
 bit[2:0]    保留
   UNION结构:  BBPCOMM_W_SND_W_INT_13_UNION */
#define BBPCOMM_W_SND_W_INT_13_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0x36C)

/* 寄存器说明：LTE为从模时对应通道的指示寄存器
 bit[31:5]   保留
 bit[4]      LTE为从模时对应的通道选择信号生效方式。
             0：在int1生效；
             1：立即生效。
 bit[3]      LTE在从模时配置
             1'b1：LTE的CH3通路在occasion中有效
             1'b0：LTE的CH3通路在occasion中无效
 bit[2]      LTE在从模时配置
             1'b1：LTE的CH2通路在occasion中有效
             1'b0：LTE的CH2通路在occasion中无效
 bit[1]      LTE在从模时配置
             1'b1：LTE的CH1通路在occasion中有效
             1'b0：LTE的CH1通路在occasion中无效
 bit[0]      LTE在从模时配置
             1'b1：LTE的CH0通路在occasion中有效
             1'b0：LTE的CH0通路在occasion中无效
   UNION结构:  BBPCOMM_S_LTE_CH_NUM_IND_UNION */
#define BBPCOMM_S_LTE_CH_NUM_IND_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x380)

/* 寄存器说明：寄存器
 bit[31:4]   保留
 bit[3:0]    异系统测量类型。
             4’b0：测量LTE。
             4’b1：背景搜LTE。
             其它预留
             生效时刻：立即生效
   UNION结构:  BBPCOMM_LTE_INTERSYS_MEASURE_TYPE_UNION */
#define BBPCOMM_LTE_INTERSYS_MEASURE_TYPE_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0x384)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      单频点测量周期到指示，W/Gm/Gs或者TDS作为主模，通知L DSP 测量的单频点周期到达。
             只在连接态下需要配置，且Gm测L时不需要配置；
             电平信号，高有效。
             
             生效时刻：立即生效
   UNION结构:  BBPCOMM_LTE_MEASURE_REPORT_VALID_UNION */
#define BBPCOMM_LTE_MEASURE_REPORT_VALID_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x388)

/* 寄存器说明：寄存器
   详      述：预处理中断int0到int1之间的offset信息，单位us（向下取整）。
               配置时刻：每次启动LTE从模异系统测量时配置
               生效时刻：立即生效
   UNION结构 ：无 */
#define BBPCOMM_LTE_PREINT_OFFSET_TIME_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0x38C)

/* 寄存器说明：寄存器
   详      述：LTE作为从模时，主模主模分配给LTE用于异系统测量时间长度,告知LTE DSP。单位us，向下取整
               配置时刻：每次启动LTE从模异系统测量时配置
               生效时刻：立即生效
   UNION结构 ：无 */
#define BBPCOMM_LTE_INTERSYS_MEASURE_TIME_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0x390)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   逻辑自清零。
             中断标志清除指示，高有效。用于清除INT_TYPE_LTE_RCV_LTE[15:0]对应bit位
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_CLEAR_LTE_RCV_LTE_UNION */
#define BBPCOMM_INT_CLEAR_LTE_RCV_LTE_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0x394)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   逻辑自清零。
             中断标志清除指示，高有效。用于清除INT_TYPE_LTE_RCV_TDS[15:0]对应bit位
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_CLEAR_LTE_RCV_TDS_UNION */
#define BBPCOMM_INT_CLEAR_LTE_RCV_TDS_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0x398)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   逻辑自清零。
             中断标志清除指示，高有效。用于清除INT_TYPE_LTE_RCV_GM[15:0]对应bit位
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_CLEAR_LTE_RCV_GM_UNION */
#define BBPCOMM_INT_CLEAR_LTE_RCV_GM_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x39C)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   逻辑自清零。
             中断标志清除指示，高有效。用于清除INT_TYPE_LTE_RCV_GS[15:0]对应bit位
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_CLEAR_LTE_RCV_GS_UNION */
#define BBPCOMM_INT_CLEAR_LTE_RCV_GS_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x3A0)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   逻辑自清零。
             中断标志清除指示，高有效。用于清除INT_TYPE_LTE_RCV_W[15:0]对应bit位
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_CLEAR_LTE_RCV_W_UNION */
#define BBPCOMM_INT_CLEAR_LTE_RCV_W_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x3A4)

/* 寄存器说明：寄存器
 bit[31:3]   保留
 bit[2:0]    逻辑自清零。
             中断标志清除指示，高有效。用于清除INT_TYPE_LTE_INT012[2:0]对应bit位
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_CLEAR_LTE_INT012_UNION */
#define BBPCOMM_INT_CLEAR_LTE_INT012_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x3A8)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   中断屏蔽标志。用于屏蔽INT_TYPE_LTE_RCV_LTE[15:0]对应bit中断。
             0：屏蔽中断上报；
             1：使能中断上报。
             配置时刻：初始化
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_MASK_LTE_RCV_LTE_UNION */
#define BBPCOMM_INT_MASK_LTE_RCV_LTE_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x3AC)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   中断屏蔽标志。用于屏蔽INT_TYPE_LTE_RCV_TDS[15:0]对应bit中断。
             0：屏蔽中断上报；
             1：使能中断上报。
             配置时刻：初始化
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_MASK_LTE_RCV_TDS_UNION */
#define BBPCOMM_INT_MASK_LTE_RCV_TDS_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x3B0)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   中断屏蔽标志。用于屏蔽INT_TYPE_LTE_RCV_GM[15:0]对应bit中断。
             0：屏蔽中断上报；
             1：使能中断上报。
             配置时刻：初始化
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_MASK_LTE_RCV_GM_UNION */
#define BBPCOMM_INT_MASK_LTE_RCV_GM_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x3B4)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   中断屏蔽标志。用于屏蔽INT_TYPE_LTE_RCV_GS[15:0]对应bit中断。
             0：屏蔽中断上报；
             1：使能中断上报。
             配置时刻：初始化
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_MASK_LTE_RCV_GS_UNION */
#define BBPCOMM_INT_MASK_LTE_RCV_GS_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x3B8)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   中断屏蔽标志。用于屏蔽INT_TYPE_LTE_RCV_W[15:0]对应bit中断。
             0：屏蔽中断上报；
             1：使能中断上报。
             配置时刻：初始化
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_MASK_LTE_RCV_W_UNION */
#define BBPCOMM_INT_MASK_LTE_RCV_W_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x3BC)

/* 寄存器说明：寄存器
 bit[31:3]   保留
 bit[2:0]    中断屏蔽标志。用于屏蔽INT_TYPE_LTE_INT012[2:0]对应bit中断。
             0：屏蔽中断上报；
             1：使能中断上报。
             配置时刻：初始化
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_MASK_LTE_INT012_UNION */
#define BBPCOMM_INT_MASK_LTE_INT012_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x3C0)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   中断状态标志。各bit单独对应一种中断类型，高有效。
             [0]: 中断类型0。 W（主模）提前通知LTE异系统测量启动中断。
             [1]: 中断类型1。 W（主模）进GAP中断，通知LTE进行异系统测量射频通道配置，天线切换等操作。
             [2]: 中断类型2。 W（主模）出GAP中断。
             [3]: 中断类型3。W（从模）测量结束中断。
             [4]: 中断类型4。W（主模）强制LTE退出异系统测量中断。
             [5]: 中断类型5。W（主模）通知LTE上报本次测量结果。
             [6]: 保留。
             [15:7]: 对应中断类型[15:7]，预留。
             软件读取该中断状态上报寄存器后，需要和0x076C的int_mask_lte_rcv_w相与，再判断是否需要处理。
   UNION结构:  BBPCOMM_INT_TYPE_LTE_RCV_W_UNION */
#define BBPCOMM_INT_TYPE_LTE_RCV_W_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x3C4)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   中断状态标志0，1，2只有当TDS处于主模时才能产生。
             [0]: 中断类型0。 TDS（主模）提前通知LTE异系统测量启动中断。
             [1]: 中断类型1。 TDS（主模）进GAP中断，通知LTE进行异系统测量射频通道配置，天线切换等操作。
             [2]: 中断类型2。 TDS（主模）出GAP中断。
             [3]: 中断类型3。TDS（从模）测量结束中断。
             [4]: 中断类型4。TDS（主模）强制LTE退出异系统测量中断。
             [5]: 中断类型5。TDS（主模）通知LTE上报本次测量结果。
             [6]: 中断类型6。保留。
             [15:7]: 对应中断类型[15:7]，预留。
             软件读取该中断状态上报寄存器后，需要和0x0760的int_mask_lte_rcv_tds相与，再判断是否需要处理。
   UNION结构:  BBPCOMM_INT_TYPE_LTE_RCV_TDS_UNION */
#define BBPCOMM_INT_TYPE_LTE_RCV_TDS_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x3C8)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   中断状态标志。各bit单独对应一种中断类型，高有效。
             [0]: 中断类型0。GM（主模）提前通知LTE异系统测量启动中断。
             [1]: 中断类型1。GM（主模）进GAP中断，通知LTE进行异系统测量射频通道配置，天线切换等操作。
             [2]: 中断类型2。GM（主模）出GAP中断。
             [3]: 中断类型3。GM（从模）测量结束中断。
             [4]: 中断类型4。GM（主模）强制LTE退出异系统测量中断。
             [5]: 中断类型5。GM（主模）通知LTE上报本次测量结果。
             [6]: 中断类型6。保留。
             [15:7]: 对应中断类型[15:7]，预留。
             中断状态标志0，1，2只有当GM处于主模时才能产生。
             软件读取该中断状态上报寄存器后，需要和0x0764的int_mask_lte_rcv_gm相与，再判断是否需要处理。
   UNION结构:  BBPCOMM_INT_TYPE_LTE_RCV_GM_UNION */
#define BBPCOMM_INT_TYPE_LTE_RCV_GM_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x3CC)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   [0]: 中断类型0。GS（主模）提前通知LTE异系统测量启动中断。
             [1]: 中断类型1。GS（主模）进GAP中断，通知LTE进行异系统测量射频通道配置，天线切换等操作。
             [2]: 中断类型2。GS（主模）出GAP中断。
             [3]: 中断类型3。GS（从模）测量结束中断。
             [4]: 中断类型4。GS（主模）强制LTE退出异系统测量中断。
             [5]: 中断类型5。GS（主模）通知LTE上报本次测量结果。
             [6]: 中断类型6。保留。
             [15:7]: 对应中断类型[15:7]，预留。
             中断状态标志0，1，2只有当TDS处于主模时才能产生。
             软件读取该中断状态上报寄存器后，需要和0x0768的int_mask_lte_rcv_gs相与，再判断是否需要处理。
   UNION结构:  BBPCOMM_INT_TYPE_LTE_RCV_GS_UNION */
#define BBPCOMM_INT_TYPE_LTE_RCV_GS_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x3D0)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   中断状态标志。各bit单独对应一种中断类型，高有效。
             [0]: 中断类型0。LTE（主模）提前通知LTE异频测量启动中断。
             [1]: 中断类型1。LTE（主模）进GAP中断，通知LTE进行异频测量射频通道配置，天线切换等操作。
             [2]: 中断类型2。LTE（主模）出GAP中断。
             [3]: 中断类型3。LTE（从模，即异频）测量结束中断。
             [4]: 中断类型4。LTE（主模）强制LTE退出异频测量中断。
             [5]: 中断类型5。LTE（主模）通知LTE上报本次测量结果。
             [6]: 中断类型6。保留。
             [15:7]: 对应中断类型[15:7]，预留。
             中断状态标志0，1，2只有当LTE处于主模时才能产生。
             软件读取该中断状态上报寄存器后，需要和0x075C的int_mask_lte_rcv_lte相与，再判断是否需要处理。
   UNION结构:  BBPCOMM_INT_TYPE_LTE_RCV_LTE_UNION */
#define BBPCOMM_INT_TYPE_LTE_RCV_LTE_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x3D4)

/* 寄存器说明：寄存器
 bit[31:3]   保留
 bit[2:0]    增加主模产生int0、1、2的上报（(包括异频、异系统场景)），高有效。
             [0]: L主模时，CTU告诉通知LDSP产生int0中断。
             [1]: L主模时，CTU告诉通知LDSP产生int1中断。
             [2]: L主模时，CTU告诉通知LDSP产生int2中断。
             软件读取该中断状态上报寄存器后，需要和0x0770的int_mask_lte_int012相与，再判断是否需要处理。
   UNION结构:  BBPCOMM_INT_TYPE_LTE_INT012_UNION */
#define BBPCOMM_INT_TYPE_LTE_INT012_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x3D8)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:3]   逻辑自清零。高有效。
             
             bit15~7：对应lte_snd_lte_int_15 ~ 7。
             L DSP通过此寄存器触发类型15~7中断（int_type_lte_rcv_lte[15:7]）给LDSP。
             生效时刻：立即生效
             
             bit6：对应lte_snd_lte_int_6。
             LDSP通过此寄存器触发类型6中断（int_type_lte_rcv_lte[6]）给LDSP。
             生效时刻：立即生效
             
             bit5：对应lte_snd_lte_int_5。
             L主模时通知LDSP L测量周期到达，高有效。
             L DSP通过此寄存器触发类型5中断（int_type_lte_rcv_lte[5]）给LDSP。
             生效时刻：立即生效
             
             bit4：对应lte_snd_lte_int_4。
             L主模时强制退出异系统测量指示。高有效。
             L DSP通过此寄存器触发类型4中断（int_type_lte_rcv_lte[4]）给LDSP。
             生效时刻：立即生效
             
             bit3：对应lte_snd_lte_int_3。L测量结束指示，高有效。
             用于触发中断类型3 （int_type_lte_rcv_lte[3]）给LDSP。L主模下对L进行异系统测量时，如果L测量结束，L DSP配置此标志为1。 
             生效时刻：立即生效
 bit[2:0]    保留
   UNION结构:  BBPCOMM_LTE_SND_LTE_INT_13_UNION */
#define BBPCOMM_LTE_SND_LTE_INT_13_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x3DC)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:3]   逻辑自清零。高有效。
             
             bit15~7：对应lte_snd_tds_int_15 ~ 7。
             L DSP通过此寄存器触发类型15~7中断（int_type_tds_rcv_lte[15:7]）给TDSDSP。
             生效时刻：立即生效
             
             bit6：对应lte_snd_tds_int_6。
             LDSP通过此寄存器触发类型6中断（int_type_tds_rcv_lte[6]）给TDSDSP。
             生效时刻：立即生效
             
             bit5：对应lte_snd_tds_int_5。
             L主模时通知TDSDSP TDS测量周期到达，高有效。
             L DSP通过此寄存器触发类型5中断（int_type_tds_rcv_lte[5]）给TDSDSP。
             生效时刻：立即生效
             
             bit4：对应lte_snd_tds_int_4。
             L主模时强制退出异系统测量指示。高有效。
             L DSP通过此寄存器触发类型4中断（int_type_tds_rcv_lte[4]）给TDSDSP。
             生效时刻：立即生效
             
             bit3：对应lte_snd_tds_int_3。L测量结束指示，高有效。
             用于触发中断类型3 （int_type_tds_rcv_lte[3]）给TDSDSP。TDS主模下对L进行异系统测量时，如果L测量结束，L DSP配置此标志为1。 
             生效时刻：立即生效
 bit[2:0]    保留
   UNION结构:  BBPCOMM_LTE_SND_TDS_INT_13_UNION */
#define BBPCOMM_LTE_SND_TDS_INT_13_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x3E0)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:3]   逻辑自清零。高有效。
             
             bit15~7：对应lte_snd_gm_int_15 ~ 7。
             L DSP通过此寄存器触发类型15~7中断（int_type_gm_rcv_lte[15:7]）给GMDSP。
             生效时刻：立即生效
             
             bit6：对应lte_snd_gm_int_6。
             LDSP通过此寄存器触发类型6中断（iint_type_gm_rcv_lte[6]）给GMDSP。
             生效时刻：立即生效
             
             bit5：对应lte_snd_gm_int_5。
             L主模时通知GMDSP GM测量周期到达，高有效。
             L DSP通过此寄存器触发类型5中断（int_type_gm_rcv_lte[5]）给GMDSP。
             生效时刻：立即生效
             
             bit4：对应lte_snd_gm_int_4。
             L主模时强制退出异系统测量指示。高有效。
             L DSP通过此寄存器触发类型4中断（int_type_gm_rcv_lte[4]）给GMDSP。
             生效时刻：立即生效
             
             bit3：对应lte_snd_gm_int_3。L测量结束指示，高有效。
             用于触发中断类型3 （int_type_gm_rcv_lte[3]）给GMDSP。GM主模下对L进行异系统测量时，如果L测量结束，L DSP配置此标志为1。 
             生效时刻：立即生效
 bit[2:0]    保留
   UNION结构:  BBPCOMM_LTE_SND_GM_INT_13_UNION */
#define BBPCOMM_LTE_SND_GM_INT_13_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x3E4)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:3]   逻辑自清零。高有效。
             
             bit15~7：对应lte_snd_gs_int_15 ~ 7。
             L DSP通过此寄存器触发类型15~7中断（int_type_gs_rcv_lte[15:7]）给GSDSP。
             生效时刻：立即生效
             
             bit6：对应lte_snd_gs_int_6。
             LDSP通过此寄存器触发类型6中断（int_type_gs_rcv_lte[6]）给GSDSP。
             生效时刻：立即生效
             
             bit5：对应lte_snd_gs_int_5。
             L主模时通知GSDSP GS测量周期到达，高有效。
             L DSP通过此寄存器触发类型5中断（int_type_gs_rcv_lte[5]）给GSDSP。
             生效时刻：立即生效
             
             bit4：对应lte_snd_gs_int_4。
             L主模时强制退出异系统测量指示。高有效。
             L DSP通过此寄存器触发类型4中断（int_type_gs_rcv_lte[4]）给GSDSP。
             生效时刻：立即生效
             
             bit3：对应lte_snd_gs_int_3。L测量结束指示，高有效。
             用于触发中断类型3 （int_type_gs_rcv_lte[3]）给GSDSP。GS主模下对L进行异系统测量时，如果L测量结束，L DSP配置此标志为1。 
             生效时刻：立即生效
 bit[2:0]    保留
   UNION结构:  BBPCOMM_LTE_SND_GS_INT_13_UNION */
#define BBPCOMM_LTE_SND_GS_INT_13_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x3E8)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:3]   逻辑自清零。高有效。
             
             bit15~7：对应lte_snd_w_int_15 ~ 7。
             L DSP通过此寄存器触发类型15~7中断（int_type_w_rcv_lte[15:7]）给WDSP。
             生效时刻：立即生效
             
             bit6：对应lte_snd_w_int_6。
             LDSP通过此寄存器触发类型6中断（int_type_w_rcv_lte[6]）给WDSP。
             生效时刻：立即生效
             
             bit5：对应lte_snd_w_int_5。
             L主模时通知WDSP W测量周期到达，高有效。
             L DSP通过此寄存器触发类型5中断（int_type_w_rcv_lte[5]）给WDSP。
             生效时刻：立即生效
             
             bit4：对应lte_snd_w_int_4。
             L主模时强制退出异系统测量指示。高有效。
             L DSP通过此寄存器触发类型4中断（int_type_w_rcv_lte[4]）给WDSP。
             生效时刻：立即生效
             
             bit3：对应lte_snd_w_int_3。L测量结束指示，高有效。
             用于触发中断类型3 （int_type_w_rcv_lte[3]）给WDSP。W主模下对L进行异系统测量时，如果L测量结束，L DSP配置此标志为1。 
             生效时刻：立即生效
 bit[2:0]    保留
   UNION结构:  BBPCOMM_LTE_SND_W_INT_13_UNION */
#define BBPCOMM_LTE_SND_W_INT_13_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x3EC)

/* 寄存器说明：TDS为从模时对应通道的指示寄存器
 bit[31:5]   保留
 bit[4:4]    TDS为从模时对应的通道选择信号生效方式。
             0：在int1生效；
             1：立即生效。
 bit[3:2]    保留
 bit[1:0]    TDS为从模时对应的通道选择信号。
             0：选择通道0；
             1：选择通道1；
             2：选择通道2；
             3：选择通道3。
             配置时刻：各模根据通信场景配置
   UNION结构:  BBPCOMM_S_TDS_CH_NUM_IND_UNION */
#define BBPCOMM_S_TDS_CH_NUM_IND_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x400)

/* 寄存器说明：寄存器
 bit[31:4]   保留
 bit[3:0]    异系统测量类型 。
             4’b0： 测量TDS
             4’b1： 背景搜TDS
             其它预留
             
             生效时刻：立即生效
   UNION结构:  BBPCOMM_TDS_INTERSYS_MEASURE_TYPE_UNION */
#define BBPCOMM_TDS_INTERSYS_MEASURE_TYPE_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0x404)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      单频点测量周期到指示，U/Gm/Gs或者L作为主模，通知T DSP W测量的单频点周期到达。
             只在连接态下需要配置，且G测TDS时不需要配置；
             电平信号，高有效。
             
             生效时刻：立即生效
   UNION结构:  BBPCOMM_TDS_MEASURE_REPORT_VALID_UNION */
#define BBPCOMM_TDS_MEASURE_REPORT_VALID_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x408)

/* 寄存器说明：寄存器
   详      述：预处理中断int0到int1之间的offset信息，单位us（向下取整）。
               配置时刻：主模启动TDS从模异系统测量时配置
               生效时刻：立即生效
   UNION结构 ：无 */
#define BBPCOMM_TDS_PREINT_OFFSET_TIME_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0x40C)

/* 寄存器说明：寄存器
   详      述：测量时间长度，告知TDS DSP。单位us，向下取整到us。
               配置时刻：主模启动TDS从模异系统测量时配置
               生效时刻：立即生效
   UNION结构 ：无 */
#define BBPCOMM_TDS_INTERSYS_MEASURE_TIME_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0x410)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   逻辑自清零。
             中断标志清除指示，高有效。用于清除INT_TYPE_TDS_RCV_LTE[15:0]对应bit位
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_CLEAR_TDS_RCV_LTE_UNION */
#define BBPCOMM_INT_CLEAR_TDS_RCV_LTE_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0x414)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   逻辑自清零。
             中断标志清除指示，高有效。用于清除INT_TYPE_TDS_RCV_TDS[15:0]对应bit位
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_CLEAR_TDS_RCV_TDS_UNION */
#define BBPCOMM_INT_CLEAR_TDS_RCV_TDS_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0x418)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   逻辑自清零。
             中断标志清除指示，高有效。用于清除INT_TYPE_TDS_RCV_GM[15:0]对应bit位
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_CLEAR_TDS_RCV_GM_UNION */
#define BBPCOMM_INT_CLEAR_TDS_RCV_GM_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x41C)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   逻辑自清零。
             中断标志清除指示，高有效。用于清除INT_TYPE_TDS_RCV_GS[15:0]对应bit位
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_CLEAR_TDS_RCV_GS_UNION */
#define BBPCOMM_INT_CLEAR_TDS_RCV_GS_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x420)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   逻辑自清零。
             中断标志清除指示，高有效。用于清除INT_TYPE_TDS_RCV_W[15:0]对应bit位
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_CLEAR_TDS_RCV_W_UNION */
#define BBPCOMM_INT_CLEAR_TDS_RCV_W_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x424)

/* 寄存器说明：寄存器
 bit[31:3]   保留
 bit[2:0]    逻辑自清零。
             中断标志清除指示，高有效。用于清除INT_TYPE_TDS_INT012[2:0]对应bit位
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_CLEAR_TDS_INT012_UNION */
#define BBPCOMM_INT_CLEAR_TDS_INT012_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x428)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   中断屏蔽标志。用于屏蔽INT_TYPE_TDS_RCV_LTE[15:0]对应bit中断。
             0：屏蔽中断上报；
             1：使能中断上报。
             配置时刻：初始化
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_MASK_TDS_RCV_LTE_UNION */
#define BBPCOMM_INT_MASK_TDS_RCV_LTE_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x42C)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   中断屏蔽标志。用于屏蔽INT_TYPE_TDS_RCV_TDS[15:0]对应bit中断。
             0：屏蔽中断上报；
             1：使能中断上报。
             配置时刻：初始化
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_MASK_TDS_RCV_TDS_UNION */
#define BBPCOMM_INT_MASK_TDS_RCV_TDS_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x430)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   中断屏蔽标志。用于屏蔽INT_TYPE_TDS_RCV_GM[15:0]对应bit中断。
             0：屏蔽中断上报；
             1：使能中断上报。
             配置时刻：初始化
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_MASK_TDS_RCV_GM_UNION */
#define BBPCOMM_INT_MASK_TDS_RCV_GM_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x434)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   中断屏蔽标志。用于屏蔽INT_TYPE_TDS_RCV_GS[15:0]对应bit中断。
             0：屏蔽中断上报；
             1：使能中断上报。
             配置时刻：初始化
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_MASK_TDS_RCV_GS_UNION */
#define BBPCOMM_INT_MASK_TDS_RCV_GS_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x438)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   中断屏蔽标志。用于屏蔽INT_TYPE_TDS_RCV_W[15:0]对应bit中断。
             0：屏蔽中断上报；
             1：使能中断上报。
             配置时刻：初始化
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_MASK_TDS_RCV_W_UNION */
#define BBPCOMM_INT_MASK_TDS_RCV_W_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x43C)

/* 寄存器说明：寄存器
 bit[31:3]   保留
 bit[2:0]    中断屏蔽标志。用于屏蔽INT_TYPE_TDS_INT012[2:0]对应bit中断。
             0：屏蔽中断上报；
             1：使能中断上报。
             配置时刻：初始化
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_MASK_TDS_INT012_UNION */
#define BBPCOMM_INT_MASK_TDS_INT012_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x440)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   中断状态标志。各bit单独对应一种中断类型，高有效。
             [0]: 中断类型0。 LTE（主模）提前通知TDS异系统测量启动中断。
             [1]: 中断类型1。 LTE（主模）进GAP中断，通知TDS进行异系统测量射频通道配置，天线切换等操作。
             [2]: 中断类型2。 LTE（主模）出GAP中断。
             [3]: 中断类型3。LTE（从模）测量结束中断。
             [4]: 中断类型4。LTE（主模）强制TDS退出异系统测量中断。
             [5]: 中断类型5。LTE（主模）通知TDS上报本次测量结果。
             [6]: 保留。
             [15:7]: 对应中断类型[15:7]，预留。
             软件读取该中断状态上报寄存器后，需要和0x07C8的int_mask_tds_rcv_lte相与，再判断是否需要处理。
   UNION结构:  BBPCOMM_INT_TYPE_TDS_RCV_LTE_UNION */
#define BBPCOMM_INT_TYPE_TDS_RCV_LTE_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x444)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   中断状态标志0，1，2只有当TDS处于主模时才能产生。
             
             [0]: 中断类型0。 TDS（主模）提前通知TDS异系统测量启动中断。
             [1]: 中断类型1。 TDS（主模）进GAP中断，通知TDS进行异系统测量射频通道配置，天线切换等操作。
             [2]: 中断类型2。 TDS（主模）出GAP中断。
             [3]: 中断类型3。TDS（从模）测量结束中断。
             [4]: 中断类型4。TDS（主模）强制TDS退出异系统测量中断。
             [5]: 中断类型5。TDS（主模）通知TDS上报本次测量结果。
             [6]: 中断类型6。保留。
             [15:7]: 对应中断类型[15:7]，预留。
             软件读取该中断状态上报寄存器后，需要和0x07D8的int_mask_tds_rcv_w相与，再判断是否需要处理。
   UNION结构:  BBPCOMM_INT_TYPE_TDS_RCV_W_UNION */
#define BBPCOMM_INT_TYPE_TDS_RCV_W_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x448)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   中断状态标志。各bit单独对应一种中断类型，高有效。
             [0]: 中断类型0。GM（主模）提前通知TDS异系统测量启动中断。
             [1]: 中断类型1。GM（主模）进GAP中断，通知TDS进行异系统测量射频通道配置，天线切换等操作。
             [2]: 中断类型2。GM（主模）出GAP中断。
             [3]: 中断类型3。GM（从模）测量结束中断。
             [4]: 中断类型4。GM（主模）强制TDS退出异系统测量中断。
             [5]: 中断类型5。GM（主模）通知TDS上报本次测量结果。
             [6]: 中断类型6。保留。
             [15:7]: 对应中断类型[15:7]，预留。
             中断状态标志0，1，2只有当GM处于主模时才能产生。
             软件读取该中断状态上报寄存器后，需要和0x07D0的int_mask_tds_rcv_gm相与，再判断是否需要处理。
   UNION结构:  BBPCOMM_INT_TYPE_TDS_RCV_GM_UNION */
#define BBPCOMM_INT_TYPE_TDS_RCV_GM_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x44C)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   [0]: 中断类型0。GS（主模）提前通知TDS异系统测量启动中断。
             [1]: 中断类型1。GS（主模）进GAP中断，通知TDS进行异系统测量射频通道配置，天线切换等操作。
             [2]: 中断类型2。GS（主模）出GAP中断。
             [3]: 中断类型3。GS（从模）测量结束中断。
             [4]: 中断类型4。GS（主模）强制TDS退出异系统测量中断。
             [5]: 中断类型5。GS（主模）通知TDS上报本次测量结果。
             [6]: 中断类型6。保留。
             [15:7]: 对应中断类型[15:7]，预留。
             中断状态标志0，1，2只有当TDS处于主模时才能产生。
             软件读取该中断状态上报寄存器后，需要和0x07D4的int_mask_tds_rcv_gs相与，再判断是否需要处理。
   UNION结构:  BBPCOMM_INT_TYPE_TDS_RCV_GS_UNION */
#define BBPCOMM_INT_TYPE_TDS_RCV_GS_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x450)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   中断状态标志。各bit单独对应一种中断类型，高有效。
             [0]: 中断类型0。TDS（主模）提前通知TDS异频测量启动中断。
             [1]: 中断类型1。TDS（主模）进GAP中断，通知TDS进行异频测量射频通道配置，天线切换等操作。
             [2]: 中断类型2。TDS（主模）出GAP中断。
             [3]: 中断类型3。TDS（从模，即异频）测量结束中断。
             [4]: 中断类型4。TDS（主模）强制TDS退出异频测量中断。
             [5]: 中断类型5。TDS（主模）通知TDS上报本次测量结果。
             [6]: 中断类型6。保留。
             [15:7]: 对应中断类型[15:7]，预留。
             中断状态标志0，1，2只有当TDS处于主模时才能产生。
             软件读取该中断状态上报寄存器后，需要和0x07CC的int_mask_tds_rcv_tds相与，再判断是否需要处理。
   UNION结构:  BBPCOMM_INT_TYPE_TDS_RCV_TDS_UNION */
#define BBPCOMM_INT_TYPE_TDS_RCV_TDS_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x454)

/* 寄存器说明：寄存器
 bit[31:3]   保留
 bit[2:0]    增加主模产生int0、1、2的上报（(包括异频、异系统场景)），高有效。
             [0]: T主模时，CTU告诉通知TDSP产生int0中断。
             [1]: T主模时，CTU告诉通知TDSP产生int1中断。
             [2]: T主模时，CTU告诉通知TDSP产生int2中断。
             软件读取该中断状态上报寄存器后，需要和0x07DC的int_mask_tds_int012相与，再判断是否需要处理。
   UNION结构:  BBPCOMM_INT_TYPE_TDS_INT012_UNION */
#define BBPCOMM_INT_TYPE_TDS_INT012_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x458)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:3]   逻辑自清零。高有效。
             
             bit15~7：对应tds_snd_lte_int_15 ~ 7。
             TDS DSP通过此寄存器触发类型15~7中断（int_type_lte_rcv_tds[15:7]）给LDSP。
             生效时刻：立即生效
             
             bit6：对应tds_snd_lte_int_6。
             TDSDSP通过此寄存器触发类型6中断（int_type_lte_rcv_tds[6]）给LDSP。
             生效时刻：立即生效
             
             bit5：对应tds_snd_lte_int_5。
             TDS主模时通知LDSP L测量周期到达，高有效。
             TDS DSP通过此寄存器触发类型5中断（int_type_lte_rcv_tds[5]）给LDSP。
             生效时刻：立即生效
             
             bit4：对应tds_snd_lte_int_4。
             TDS主模时强制退出异系统测量指示。高有效。
             TDS DSP通过此寄存器触发类型4中断（int_type_lte_rcv_tds[4]）给LDSP。
             生效时刻：立即生效
             
             bit3：对应tds_snd_lte_int_3。TDS测量结束指示，高有效。
             用于触发中断类型3 （int_type_lte_rcv_tds[3]）给LDSP。L主模下对TDS进行异系统测量时，如果TDS测量结束，TDS DSP配置此标志为1。 
             生效时刻：立即生效
 bit[2:0]    保留
   UNION结构:  BBPCOMM_TDS_SND_LTE_INT_13_UNION */
#define BBPCOMM_TDS_SND_LTE_INT_13_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x45C)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:3]   逻辑自清零。高有效。
             
             bit15~7：对应tds_snd_tds_int_15 ~ 7。
             TDS DSP通过此寄存器触发类型15~7中断（int_type_tds_rcv_tds[15:7]）给TDSP。
             生效时刻：立即生效
             
             bit6：对应tds_snd_tds_int_6。
             TDSDSP通过此寄存器触发类型6中断（int_type_tds_rcv_tds[6]）给TDSP。
             生效时刻：立即生效
             
             bit5：对应tds_snd_tds_int_5。
             TDS主模时通知TDSP T测量周期到达，高有效。
             TDS DSP通过此寄存器触发类型5中断（int_type_tds_rcv_tds[5]）给TDSP。
             生效时刻：立即生效
             
             bit4：对应tds_snd_tds_int_4。
             TDS主模时强制退出异系统测量指示。高有效。
             TDS DSP通过此寄存器触发类型4中断（int_type_tds_rcv_tds[4]）给TDSP。
             生效时刻：立即生效
             
             bit3：对应tds_snd_tds_int_3。TDS测量结束指示，高有效。
             用于触发中断类型3 （int_type_tds_rcv_tds[3]）给TDSP。T主模下对TDS进行异系统测量时，如果TDS测量结束，TDS DSP配置此标志为1。 
             生效时刻：立即生效
 bit[2:0]    保留
   UNION结构:  BBPCOMM_TDS_SND_TDS_INT_13_UNION */
#define BBPCOMM_TDS_SND_TDS_INT_13_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x460)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:3]   逻辑自清零。高有效。
             
             bit15~7：对应tds_snd_gm_int_15 ~ 7。
             TDS DSP通过此寄存器触发类型15~7中断（int_type_gm_rcv_tds[15:7]）给GMDSP。
             生效时刻：立即生效
             
             bit6：对应tds_snd_gm_int_6。
             TDSDSP通过此寄存器触发类型6中断（int_type_gm_rcv_tds[6]）给GMDSP。
             生效时刻：立即生效
             
             bit5：对应tds_snd_gm_int_5。
             TDS主模时通知GMDSP GM测量周期到达，高有效。
             TDS DSP通过此寄存器触发类型5中断（int_type_gm_rcv_tds[5]）给GMDSP。
             生效时刻：立即生效
             
             bit4：对应tds_snd_gm_int_4。
             TDS主模时强制退出异系统测量指示。高有效。
             TDS DSP通过此寄存器触发类型4中断（int_type_gm_rcv_tds[4]）给GMDSP。
             生效时刻：立即生效
             
             bit3：对应tds_snd_gm_int_3。TDS测量结束指示，高有效。
             用于触发中断类型3 （int_type_gm_rcv_tds[3]）给GMDSP。GM主模下对TDS进行异系统测量时，如果TDS测量结束，TDS DSP配置此标志为1。 
             生效时刻：立即生效
 bit[2:0]    保留
   UNION结构:  BBPCOMM_TDS_SND_GM_INT_13_UNION */
#define BBPCOMM_TDS_SND_GM_INT_13_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x464)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:3]   逻辑自清零。高有效。
             
             bit15~7：对应tds_snd_gs_int_15 ~ 7。
             TDS DSP通过此寄存器触发类型15~7中断（int_type_gs_rcv_tds[15:7]）给GSDSP。
             生效时刻：立即生效
             
             bit6：对应tds_snd_gs_int_6。
             TDSDSP通过此寄存器触发类型6中断（int_type_gs_rcv_tds[6]）给GSDSP。
             生效时刻：立即生效
             
             bit5：对应tds_snd_gs_int_5。
             TDS主模时通知GSDSP GS测量周期到达，高有效。
             TDS DSP通过此寄存器触发类型5中断（int_type_gs_rcv_tds[5]）给GSDSP。
             生效时刻：立即生效
             
             bit4：对应tds_snd_gs_int_4。
             TDS主模时强制退出异系统测量指示。高有效。
             TDS DSP通过此寄存器触发类型4中断（int_type_gs_rcv_tds[4]）给GSDSP。
             生效时刻：立即生效
             
             bit3：对应tds_snd_gs_int_3。TDS测量结束指示，高有效。
             用于触发中断类型3 （int_type_gs_rcv_tds[3]）给GSDSP。GS主模下对TDS进行异系统测量时，如果TDS测量结束，TDS DSP配置此标志为1。 
             生效时刻：立即生效
 bit[2:0]    保留
   UNION结构:  BBPCOMM_TDS_SND_GS_INT_13_UNION */
#define BBPCOMM_TDS_SND_GS_INT_13_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x468)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:3]   逻辑自清零。高有效。
             
             bit15~7：对应tds_snd_w_int_15 ~ 7。
             TDS DSP通过此寄存器触发类型15~7中断（int_type_w_rcv_tds[15:7]）给WDSP。
             生效时刻：立即生效
             
             bit6：对应tds_snd_w_int_6。
             TDSDSP通过此寄存器触发类型6中断（int_type_w_rcv_tds[6]）给WDSP。
             生效时刻：立即生效
             
             bit5：对应tds_snd_w_int_5。
             TDS主模时通知WDSP W测量周期到达，高有效。
             TDS DSP通过此寄存器触发类型5中断（int_type_w_rcv_tds[5]）给WDSP。
             生效时刻：立即生效
             
             bit4：对应tds_snd_w_int_4。
             TDS主模时强制退出异系统测量指示。高有效。
             TDS DSP通过此寄存器触发类型4中断（int_type_w_rcv_tds[4]）给WDSP。
             生效时刻：立即生效
             
             bit3：对应tds_snd_w_int_3。TDS测量结束指示，高有效。
             用于触发中断类型3 （int_type_w_rcv_tds[3]）给WDSP。W主模下对TDS进行异系统测量时，如果TDS测量结束，TDS DSP配置此标志为1。 
             生效时刻：立即生效
 bit[2:0]    保留
   UNION结构:  BBPCOMM_TDS_SND_W_INT_13_UNION */
#define BBPCOMM_TDS_SND_W_INT_13_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x46C)

/* 寄存器说明：GM为从模时对应通道的指示寄存器
 bit[31:5]   保留
 bit[4:4]    GM为从模时对应的通道选择信号生效方式。
             0：在int1生效；
             1：立即生效。
 bit[3:2]    保留
 bit[1:0]    GM为从模时对应的通道选择信号。
             0：选择通道0；
             1：选择通道1；
             2：选择通道2；
             3：选择通道3。
             配置时刻：各模根据通信场景配置
   UNION结构:  BBPCOMM_S_GM_CH_NUM_IND_UNION */
#define BBPCOMM_S_GM_CH_NUM_IND_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0x480)

/* 寄存器说明：寄存器
 bit[31:4]   保留
 bit[3:0]    异系统测量类型。
             4’d0：测量GM RSSI。
             4’d1: 测量GM bsic verification。
             4’d2: 测量GM bsic confirm。
             4’d3: 背景搜GM；
             4’d4: 2G ANR。
             其它预留
             生效时刻：立即生效
   UNION结构:  BBPCOMM_GM_INTERSYS_MEASURE_TYPE_UNION */
#define BBPCOMM_GM_INTERSYS_MEASURE_TYPE_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x484)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      单频点测量周期到指示，L或者TDS/W/Gs作为主模，通知GM DSP GM测量的单频点周期到达。
             只在连接态下需要配置。
             电平信号，高有效。
             生效时刻：立即生效
   UNION结构:  BBPCOMM_GM_MEASURE_REPORT_VALID_UNION */
#define BBPCOMM_GM_MEASURE_REPORT_VALID_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0x488)

/* 寄存器说明：寄存器
   详      述：预处理中断int0到int1之间的offset信息，单位us（向下取整）。。
               配置时刻：主模启动GM从模异系统测量时配置
               生效时刻：立即生效
   UNION结构 ：无 */
#define BBPCOMM_GM_PREINT_OFFSET_TIME_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0x48C)

/* 寄存器说明：寄存器
   详      述：GM作为从模时，主模分配给GM用于异系统测量时间长度，告知GMDSP。单位us，向下取整到us。
               配置时刻：主模启动GM从模异系统测量时配置
               生效时刻：立即生效
   UNION结构 ：无 */
#define BBPCOMM_GM_INTERSYS_MEASURE_TIME_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x490)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   逻辑自清零。
             中断标志清除指示，高有效。用于清除INT_TYPE_GM_RCV_LTE[15:0]对应bit位
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_CLEAR_GM_RCV_LTE_UNION */
#define BBPCOMM_INT_CLEAR_GM_RCV_LTE_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x494)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   逻辑自清零。
             中断标志清除指示，高有效。用于清除INT_TYPE_GM_RCV_TDS[15:0]对应bit位
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_CLEAR_GM_RCV_TDS_UNION */
#define BBPCOMM_INT_CLEAR_GM_RCV_TDS_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x498)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   逻辑自清零。
             中断标志清除指示，高有效。用于清除INT_TYPE_GM_RCV_GM[15:0]对应bit位
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_CLEAR_GM_RCV_GM_UNION */
#define BBPCOMM_INT_CLEAR_GM_RCV_GM_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x49C)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   逻辑自清零。
             中断标志清除指示，高有效。用于清除INT_TYPE_GM_RCV_GS[15:0]对应bit位
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_CLEAR_GM_RCV_GS_UNION */
#define BBPCOMM_INT_CLEAR_GM_RCV_GS_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x4A0)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   逻辑自清零。
             中断标志清除指示，高有效。用于清除INT_TYPE_GM_RCV_W[15:0]对应bit位
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_CLEAR_GM_RCV_W_UNION */
#define BBPCOMM_INT_CLEAR_GM_RCV_W_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x4A4)

/* 寄存器说明：寄存器
 bit[31:3]   保留
 bit[2:0]    逻辑自清零。
             中断标志清除指示，高有效。用于清除INT_TYPE_GM_INT012[2:0]对应bit位
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_CLEAR_GM_INT012_UNION */
#define BBPCOMM_INT_CLEAR_GM_INT012_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x4A8)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   中断屏蔽标志。用于屏蔽INT_TYPE_GM_RCV_LTE[15:0]对应bit中断。
             0：屏蔽中断上报；
             1：使能中断上报。
             配置时刻：初始化
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_MASK_GM_RCV_LTE_UNION */
#define BBPCOMM_INT_MASK_GM_RCV_LTE_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x4AC)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   中断屏蔽标志。用于屏蔽INT_TYPE_GM_RCV_TDS[15:0]对应bit中断。
             0：屏蔽中断上报；
             1：使能中断上报。
             配置时刻：初始化
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_MASK_GM_RCV_TDS_UNION */
#define BBPCOMM_INT_MASK_GM_RCV_TDS_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x4B0)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   中断屏蔽标志。用于屏蔽INT_TYPE_GM_RCV_GM[15:0]对应bit中断。
             0：屏蔽中断上报；
             1：使能中断上报。
             配置时刻：初始化
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_MASK_GM_RCV_GM_UNION */
#define BBPCOMM_INT_MASK_GM_RCV_GM_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x4B4)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   中断屏蔽标志。用于屏蔽INT_TYPE_GM_RCV_GS[15:0]对应bit中断。
             0：屏蔽中断上报；
             1：使能中断上报。
             配置时刻：初始化
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_MASK_GM_RCV_GS_UNION */
#define BBPCOMM_INT_MASK_GM_RCV_GS_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x4B8)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   中断屏蔽标志。用于屏蔽INT_TYPE_GM_RCV_W[15:0]对应bit中断。
             0：屏蔽中断上报；
             1：使能中断上报。
             配置时刻：初始化
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_MASK_GM_RCV_W_UNION */
#define BBPCOMM_INT_MASK_GM_RCV_W_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x4BC)

/* 寄存器说明：寄存器
 bit[31:3]   保留
 bit[2:0]    中断屏蔽标志。用于屏蔽INT_TYPE_GM_INT012[2:0]对应bit中断。
             0：屏蔽中断上报；
             1：使能中断上报。
             配置时刻：初始化
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_MASK_GM_INT012_UNION */
#define BBPCOMM_INT_MASK_GM_INT012_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x4C0)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   中断状态标志。各bit单独对应一种中断类型，高有效。
             [0]: 中断类型0。 LTE（主模）提前通知GM异系统测量启动中断。
             [1]: 中断类型1。 LTE（主模）进GAP中断，通知GM进行异系统测量射频通道配置，天线切换等操作。
             [2]: 中断类型2。 LTE（主模）出GAP中断。
             [3]: 中断类型3。LTE（从模）测量结束中断。
             [4]: 中断类型4。LTE（主模）强制GM退出异系统测量中断。
             [5]: 中断类型5。LTE（主模）通知GM上报本次测量结果。
             [6]: 保留。
             [15:7]: 对应中断类型[15:7]，预留。
             软件读取该中断状态上报寄存器后，需要和0x0834的int_mask_gm_rcv_lte相与，再判断是否需要处理。
   UNION结构:  BBPCOMM_INT_TYPE_GM_RCV_LTE_UNION */
#define BBPCOMM_INT_TYPE_GM_RCV_LTE_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x4C4)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   中断状态标志0，1，2只有当TDS处于主模时才能产生。
             
             [0]: 中断类型0。 TDS（主模）提前通知GM异系统测量启动中断。
             [1]: 中断类型1。 TDS（主模）进GAP中断，通知GM进行异系统测量射频通道配置，天线切换等操作。
             [2]: 中断类型2。 TDS（主模）出GAP中断。
             [3]: 中断类型3。TDS（从模）测量结束中断。
             [4]: 中断类型4。TDS（主模）强制GM退出异系统测量中断。
             [5]: 中断类型5。TDS（主模）通知GM上报本次测量结果。
             [6]: 中断类型6。保留。
             [15:7]: 对应中断类型[15:7]，预留。
             软件读取该中断状态上报寄存器后，需要和0x0838的int_mask_gm_rcv_tds相与，再判断是否需要处理。
   UNION结构:  BBPCOMM_INT_TYPE_GM_RCV_TDS_UNION */
#define BBPCOMM_INT_TYPE_GM_RCV_TDS_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x4C8)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   中断状态标志。各bit单独对应一种中断类型，高有效。
             [0]: 中断类型0。W（主模）提前通知GM异系统测量启动中断。
             [1]: 中断类型1。W（主模）进GAP中断，通知GM进行异系统测量射频通道配置，天线切换等操作。
             [2]: 中断类型2。W（主模）出GAP中断。
             [3]: 中断类型3。W（从模）测量结束中断。
             [4]: 中断类型4。W（主模）强制GM退出异系统测量中断。
             [5]: 中断类型5。W（主模）通知GM上报本次测量结果。
             [6]: 中断类型6。保留。
             [15:7]: 对应中断类型[15:7]，预留。
             中断状态标志0，1，2只有当W处于主模时才能产生。
             软件读取该中断状态上报寄存器后，需要和0x0844的int_mask_gm_rcv_w相与，再判断是否需要处理。
   UNION结构:  BBPCOMM_INT_TYPE_GM_RCV_W_UNION */
#define BBPCOMM_INT_TYPE_GM_RCV_W_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x4CC)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   [0]: 中断类型0。GS（主模）提前通知GM异系统测量启动中断。
             [1]: 中断类型1。GS（主模）进GAP中断，通知GM进行异系统测量射频通道配置，天线切换等操作。
             [2]: 中断类型2。GS（主模）出GAP中断。
             [3]: 中断类型3。GS（从模）测量结束中断。
             [4]: 中断类型4。GS（主模）强制GM退出异系统测量中断。
             [5]: 中断类型5。GS（主模）通知GM上报本次测量结果。
             [6]: 中断类型6。保留。
             [15:7]: 对应中断类型[15:7]，预留。
             中断状态标志0，1，2只有当TDS处于主模时才能产生。
             软件读取该中断状态上报寄存器后，需要和0x0840的int_mask_gm_rcv_gs相与，再判断是否需要处理。
   UNION结构:  BBPCOMM_INT_TYPE_GM_RCV_GS_UNION */
#define BBPCOMM_INT_TYPE_GM_RCV_GS_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x4D0)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   中断状态标志。各bit单独对应一种中断类型，高有效。
             [0]: 中断类型0。GM（主模）提前通知GM异频测量启动中断。
             [1]: 中断类型1。GM（主模）进GAP中断，通知GM进行异频测量射频通道配置，天线切换等操作。
             [2]: 中断类型2。GM（主模）出GAP中断。
             [3]: 中断类型3。GM（从模，即异频）测量结束中断。
             [4]: 中断类型4。GM（主模）强制GM退出异频测量中断。
             [5]: 中断类型5。GM（主模）通知GM上报本次测量结果。
             [6]: 中断类型6。保留。
             [15:7]: 对应中断类型[15:7]，预留。
             中断状态标志0，1，2只有当GM处于主模时才能产生。
             软件读取该中断状态上报寄存器后，需要和0x083C的int_mask_gm_rcv_gm相与，再判断是否需要处理。
   UNION结构:  BBPCOMM_INT_TYPE_GM_RCV_GM_UNION */
#define BBPCOMM_INT_TYPE_GM_RCV_GM_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x4D4)

/* 寄存器说明：寄存器
 bit[31:3]   保留
 bit[2:0]    增加主模产生int0、1、2的上报（(包括异频、异系统场景)），高有效。
             [0]: GM主模时，CTU告诉通知GMDSP产生int0中断。
             [1]: GM主模时，CTU告诉通知GMDSP产生int1中断。
             [2]: GM主模时，CTU告诉通知GMDSP产生int2中断。
             软件读取该中断状态上报寄存器后，需要和0x0848的int_mask_gm_int012相与，再判断是否需要处理。
   UNION结构:  BBPCOMM_INT_TYPE_GM_INT012_UNION */
#define BBPCOMM_INT_TYPE_GM_INT012_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x4D8)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:3]   逻辑自清零。高有效。
             
             bit15~7：对应gm_snd_lte_int_15 ~ 7。
             GM DSP通过此寄存器触发类型15~7中断（int_type_lte_rcv_gm[15:7]）给LTEDSP。
             生效时刻：立即生效
             
             bit6：对应gm_snd_lte_int_6。
             GMDSP通过此寄存器触发类型6中断（int_type_lte_rcv_gm[6]）给LTEDSP。
             生效时刻：立即生效
             
             bit5：对应gm_snd_lte_int_5。
             GM主模时通知LTEDSP LTE测量周期到达，高有效。
             GM DSP通过此寄存器触发类型5中断（int_type_lte_rcv_gm[5]）给LTEDSP。
             生效时刻：立即生效
             
             bit4：对应gm_snd_lte_int_4。
             GM主模时强制退出异系统测量指示。高有效。
             GM DSP通过此寄存器触发类型4中断（int_type_lte_rcv_gm[4]）给LTEDSP。
             生效时刻：立即生效
             
             bit3：对应gm_snd_lte_int_3。GM测量结束指示，高有效。
             用于触发中断类型3 （int_type_lte_rcv_gm[3]）给LTEDSP。LTE主模下对GM进行异系统测量时，如果GM测量结束，GM DSP配置此标志为1。 
             生效时刻：立即生效
 bit[2:0]    保留
   UNION结构:  BBPCOMM_GM_SND_LTE_INT_13_UNION */
#define BBPCOMM_GM_SND_LTE_INT_13_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x4DC)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:3]   逻辑自清零。高有效。
             
             bit15~7：对应gm_snd_tds_int_15 ~ 7。
             GM DSP通过此寄存器触发类型15~7中断（int_type_tds_rcv_gm[15:7]）给TDSDSP。
             生效时刻：立即生效
             
             bit6：对应gm_snd_tds_int_6。
             GMDSP通过此寄存器触发类型6中断（int_type_tds_rcv_gm[6]）给TDSDSP。
             生效时刻：立即生效
             
             bit5：对应gm_snd_tds_int_5。
             GM主模时通知TDSDSP tds测量周期到达，高有效。
             GM DSP通过此寄存器触发类型5中断（int_type_tds_rcv_gm[5]）给TDSDSP。
             生效时刻：立即生效
             
             bit4：对应gm_snd_tds_int_4。
             GM主模时强制退出异系统测量指示。高有效。
             GM DSP通过此寄存器触发类型4中断（int_type_tds_rcv_gm[4]）给TDSDSP。
             生效时刻：立即生效
             
             bit3：对应gm_snd_tds_int_3。GM测量结束指示，高有效。
             用于触发中断类型3 （int_type_tds_rcv_gm[3]）给TDSDSP。tds主模下对GM进行异系统测量时，如果GM测量结束，GM DSP配置此标志为1。 
             生效时刻：立即生效
 bit[2:0]    保留
   UNION结构:  BBPCOMM_GM_SND_TDS_INT_13_UNION */
#define BBPCOMM_GM_SND_TDS_INT_13_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x4E0)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:3]   逻辑自清零。高有效。
             
             bit15~7：对应gm_snd_gm_int_15 ~ 7。
             GM DSP通过此寄存器触发类型15~7中断（int_type_gm_rcv_gm[15:7]）给GMDSP。
             生效时刻：立即生效
             
             bit6：对应gm_snd_gm_int_6。
             GMDSP通过此寄存器触发类型6中断（int_type_gm_rcv_gm[6]）给GMDSP。
             生效时刻：立即生效
             
             bit5：对应gm_snd_gm_int_5。
             GM主模时通知GMDSP GM测量周期到达，高有效。
             GM DSP通过此寄存器触发类型5中断（int_type_gm_rcv_gm[5]）给GMDSP。
             生效时刻：立即生效
             
             bit4：对应gm_snd_gm_int_4。
             GM主模时强制退出异系统测量指示。高有效。
             GM DSP通过此寄存器触发类型4中断（int_type_gm_rcv_gm[4]）给GMDSP。
             生效时刻：立即生效
             
             bit3：对应gm_snd_gm_int_3。GM测量结束指示，高有效。
             用于触发中断类型3 （int_type_gm_rcv_gm[3]）给GMDSP。GM主模下对GM进行异系统测量时，如果GM测量结束，GM DSP配置此标志为1。 
             生效时刻：立即生效
 bit[2:0]    保留
   UNION结构:  BBPCOMM_GM_SND_GM_INT_13_UNION */
#define BBPCOMM_GM_SND_GM_INT_13_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x4E4)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:3]   逻辑自清零。高有效。
             
             bit15~7：对应gm_snd_gs_int_15 ~ 7。
             GM DSP通过此寄存器触发类型15~7中断（int_type_gs_rcv_gm[15:7]）给GSDSP。
             生效时刻：立即生效
             
             bit6：对应gm_snd_gs_int_6。
             GMDSP通过此寄存器触发类型6中断（int_type_gs_rcv_gm[6]）给GSDSP。
             生效时刻：立即生效
             
             bit5：对应gm_snd_gs_int_5。
             GM主模时通知GSDSP GS测量周期到达，高有效。
             GM DSP通过此寄存器触发类型5中断（int_type_gs_rcv_gm[5]）给GSDSP。
             生效时刻：立即生效
             
             bit4：对应gm_snd_gs_int_4。
             GM主模时强制退出异系统测量指示。高有效。
             GM DSP通过此寄存器触发类型4中断（int_type_gs_rcv_gm[4]）给GSDSP。
             生效时刻：立即生效
             
             bit3：对应gm_snd_gs_int_3。GM测量结束指示，高有效。
             用于触发中断类型3 （int_type_gs_rcv_gm[3]）给GSDSP。GS主模下对GM进行异系统测量时，如果GM测量结束，GM DSP配置此标志为1。 
             生效时刻：立即生效
 bit[2:0]    保留
   UNION结构:  BBPCOMM_GM_SND_GS_INT_13_UNION */
#define BBPCOMM_GM_SND_GS_INT_13_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x4E8)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:3]   逻辑自清零。高有效。
             
             bit15~7：对应gm_snd_lte_int_15 ~ 7。
             GM DSP通过此寄存器触发类型15~7中断（int_type_lte_rcv_gm[15:7]）给LTEDSP。
             生效时刻：立即生效
             
             bit6：对应gm_snd_lte_int_6。
             GMDSP通过此寄存器触发类型6中断（int_type_lte_rcv_gm[6]）给LTEDSP。
             生效时刻：立即生效
             
             bit5：对应gm_snd_lte_int_5。
             GM主模时通知LTEDSP LTE测量周期到达，高有效。
             GM DSP通过此寄存器触发类型5中断（int_type_lte_rcv_gm[5]）给LTEDSP。
             生效时刻：立即生效
             
             bit4：对应gm_snd_lte_int_4。
             GM主模时强制退出异系统测量指示。高有效。
             GM DSP通过此寄存器触发类型4中断（int_type_lte_rcv_gm[4]）给LTEDSP。
             生效时刻：立即生效
             
             bit3：对应gm_snd_lte_int_3。GM测量结束指示，高有效。
             用于触发中断类型3 （int_type_lte_rcv_gm[3]）给LTEDSP。LTE主模下对GM进行异系统测量时，如果GM测量结束，GM DSP配置此标志为1。 
             生效时刻：立即生效
 bit[2:0]    保留
   UNION结构:  BBPCOMM_GM_SND_W_INT_13_UNION */
#define BBPCOMM_GM_SND_W_INT_13_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0x4EC)

/* 寄存器说明：GS为从模时对应通道的指示寄存器
 bit[31:5]   保留
 bit[4:4]    GS为从模时对应的通道选择信号生效方式。
             0：在int1生效；
             1：立即生效。
 bit[3:2]    保留
 bit[1:0]    GS为从模时对应的通道选择信号。
             0：选择通道0；
             1：选择通道1；
             2：选择通道2；
             3：选择通道3。
             配置时刻：各模根据通信场景配置
   UNION结构:  BBPCOMM_S_GS_CH_NUM_IND_UNION */
#define BBPCOMM_S_GS_CH_NUM_IND_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0x500)

/* 寄存器说明：寄存器
 bit[31:4]   保留
 bit[3:0]    异系统测量类型。
             4’d0：测量GS RSSI。
             4’d1: 测量GS bsic verification。
             4’d2: 测量GS bsic confirm。
             4’d3: 背景搜GS
             4’d4: 2G ANR。
             其它预留
             生效时刻：立即生效
   UNION结构:  BBPCOMM_GS_INTERSYS_MEASURE_TYPE_UNION */
#define BBPCOMM_GS_INTERSYS_MEASURE_TYPE_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x504)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      单频点测量周期到指示，L或者TDS/W/Gm作为主模，通知GS DSP GS测量的单频点周期到达。
             只在连接态下需要配置。
             电平信号，高有效。
             生效时刻：立即生效
   UNION结构:  BBPCOMM_GS_MEASURE_REPORT_VALID_UNION */
#define BBPCOMM_GS_MEASURE_REPORT_VALID_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0x508)

/* 寄存器说明：寄存器
   详      述：预处理中断int0到int1之间的offset信息，单位us（向下取整）。。
               配置时刻：主模启动GS从模异系统测量时配置
               生效时刻：立即生效
   UNION结构 ：无 */
#define BBPCOMM_GS_PREINT_OFFSET_TIME_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0x50C)

/* 寄存器说明：寄存器
   详      述：GS作为从模时，主模分配给GS用于异系统测量时间长度，告知GSDSP。单位us，向下取整到us。
               配置时刻：主模启动GS从模异系统测量时配置
               生效时刻：立即生效
   UNION结构 ：无 */
#define BBPCOMM_GS_INTERSYS_MEASURE_TIME_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x510)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   逻辑自清零。
             中断标志清除指示，高有效。用于清除INT_TYPE_GS_RCV_LTE[15:0]对应bit位
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_CLEAR_GS_RCV_LTE_UNION */
#define BBPCOMM_INT_CLEAR_GS_RCV_LTE_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x514)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   逻辑自清零。
             中断标志清除指示，高有效。用于清除INT_TYPE_GS_RCV_TDS[15:0]对应bit位
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_CLEAR_GS_RCV_TDS_UNION */
#define BBPCOMM_INT_CLEAR_GS_RCV_TDS_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x518)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   逻辑自清零。
             中断标志清除指示，高有效。用于清除INT_TYPE_GS_RCV_GM[15:0]对应bit位
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_CLEAR_GS_RCV_GM_UNION */
#define BBPCOMM_INT_CLEAR_GS_RCV_GM_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x51C)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   逻辑自清零。
             中断标志清除指示，高有效。用于清除INT_TYPE_GS_RCV_GS[15:0]对应bit位
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_CLEAR_GS_RCV_GS_UNION */
#define BBPCOMM_INT_CLEAR_GS_RCV_GS_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x520)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   逻辑自清零。
             中断标志清除指示，高有效。用于清除INT_TYPE_GS_RCV_W[15:0]对应bit位
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_CLEAR_GS_RCV_W_UNION */
#define BBPCOMM_INT_CLEAR_GS_RCV_W_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x524)

/* 寄存器说明：寄存器
 bit[31:3]   保留
 bit[2:0]    逻辑自清零。
             中断标志清除指示，高有效。用于清除INT_TYPE_GS_INT012[2:0]对应bit位
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_CLEAR_GS_INT012_UNION */
#define BBPCOMM_INT_CLEAR_GS_INT012_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x528)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   中断屏蔽标志。用于屏蔽INT_TYPE_GS_RCV_LTE[15:0]对应bit中断。
             0：屏蔽中断上报；
             1：使能中断上报。
             配置时刻：初始化
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_MASK_GS_RCV_LTE_UNION */
#define BBPCOMM_INT_MASK_GS_RCV_LTE_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x52C)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   中断屏蔽标志。用于屏蔽INT_TYPE_GS_RCV_TDS[15:0]对应bit中断。
             0：屏蔽中断上报；
             1：使能中断上报。
             配置时刻：初始化
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_MASK_GS_RCV_TDS_UNION */
#define BBPCOMM_INT_MASK_GS_RCV_TDS_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x530)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   中断屏蔽标志。用于屏蔽INT_TYPE_GS_RCV_GM[15:0]对应bit中断。
             0：屏蔽中断上报；
             1：使能中断上报。
             配置时刻：初始化
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_MASK_GS_RCV_GM_UNION */
#define BBPCOMM_INT_MASK_GS_RCV_GM_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x534)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   中断屏蔽标志。用于屏蔽INT_TYPE_GS_RCV_GS[15:0]对应bit中断。
             0：屏蔽中断上报；
             1：使能中断上报。
             配置时刻：初始化
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_MASK_GS_RCV_GS_UNION */
#define BBPCOMM_INT_MASK_GS_RCV_GS_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x538)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   中断屏蔽标志。用于屏蔽INT_TYPE_GS_RCV_W[15:0]对应bit中断。
             0：屏蔽中断上报；
             1：使能中断上报。
             配置时刻：初始化
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_MASK_GS_RCV_W_UNION */
#define BBPCOMM_INT_MASK_GS_RCV_W_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x53C)

/* 寄存器说明：寄存器
 bit[31:3]   保留
 bit[2:0]    中断屏蔽标志。用于屏蔽INT_TYPE_GS_INT012[2:0]对应bit中断。
             0：屏蔽中断上报；
             1：使能中断上报。
             配置时刻：初始化
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_MASK_GS_INT012_UNION */
#define BBPCOMM_INT_MASK_GS_INT012_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x540)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   中断状态标志。各bit单独对应一种中断类型，高有效。
             [0]: 中断类型0。 LTE（主模）提前通知GS异系统测量启动中断。
             [1]: 中断类型1。 LTE（主模）进GAP中断，通知GS进行异系统测量射频通道配置，天线切换等操作。
             [2]: 中断类型2。 LTE（主模）出GAP中断。
             [3]: 中断类型3。LTE（从模）测量结束中断。
             [4]: 中断类型4。LTE（主模）强制GS退出异系统测量中断。
             [5]: 中断类型5。LTE（主模）通知GS上报本次测量结果。
             [6]: 保留。
             [15:7]: 对应中断类型[15:7]，预留。
             软件读取该中断状态上报寄存器后，需要和0x08A0的int_mask_gs_rcv_lte相与，再判断是否需要处理。
   UNION结构:  BBPCOMM_INT_TYPE_GS_RCV_LTE_UNION */
#define BBPCOMM_INT_TYPE_GS_RCV_LTE_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x544)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   中断状态标志0，1，2只有当TDS处于主模时才能产生。
             
             [0]: 中断类型0。 TDS（主模）提前通知GS异系统测量启动中断。
             [1]: 中断类型1。 TDS（主模）进GAP中断，通知GS进行异系统测量射频通道配置，天线切换等操作。
             [2]: 中断类型2。 TDS（主模）出GAP中断。
             [3]: 中断类型3。TDS（从模）测量结束中断。
             [4]: 中断类型4。TDS（主模）强制GS退出异系统测量中断。
             [5]: 中断类型5。TDS（主模）通知GS上报本次测量结果。
             [6]: 中断类型6。保留。
             [15:7]: 对应中断类型[15:7]，预留。
             软件读取该中断状态上报寄存器后，需要和0x08A4的int_mask_gs_rcv_tds相与，再判断是否需要处理。
   UNION结构:  BBPCOMM_INT_TYPE_GS_RCV_TDS_UNION */
#define BBPCOMM_INT_TYPE_GS_RCV_TDS_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x548)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   中断状态标志。各bit单独对应一种中断类型，高有效。
             [0]: 中断类型0。GM（主模）提前通知GS异系统测量启动中断。
             [1]: 中断类型1。GM（主模）进GAP中断，通知GS进行异系统测量射频通道配置，天线切换等操作。
             [2]: 中断类型2。GM（主模）出GAP中断。
             [3]: 中断类型3。GM（从模）测量结束中断。
             [4]: 中断类型4。GM（主模）强制GS退出异系统测量中断。
             [5]: 中断类型5。GM（主模）通知GS上报本次测量结果。
             [6]: 中断类型6。保留。
             [15:7]: 对应中断类型[15:7]，预留。
             中断状态标志0，1，2只有当GM处于主模时才能产生。
             软件读取该中断状态上报寄存器后，需要和0x08A8的int_mask_gs_rcv_gm相与，再判断是否需要处理。
   UNION结构:  BBPCOMM_INT_TYPE_GS_RCV_GM_UNION */
#define BBPCOMM_INT_TYPE_GS_RCV_GM_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x54C)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   [0]: 中断类型0。GS（主模）提前通知GS异系统测量启动中断。
             [1]: 中断类型1。GS（主模）进GAP中断，通知GS进行异系统测量射频通道配置，天线切换等操作。
             [2]: 中断类型2。GS（主模）出GAP中断。
             [3]: 中断类型3。GS（从模）测量结束中断。
             [4]: 中断类型4。GS（主模）强制GS退出异系统测量中断。
             [5]: 中断类型5。GS（主模）通知GS上报本次测量结果。
             [6]: 中断类型6。保留。
             [15:7]: 对应中断类型[15:7]，预留。
             中断状态标志0，1，2只有当TDS处于主模时才能产生。
             软件读取该中断状态上报寄存器后，需要和0x08AC的int_mask_gs_rcv_gs相与，再判断是否需要处理。
   UNION结构:  BBPCOMM_INT_TYPE_GS_RCV_GS_UNION */
#define BBPCOMM_INT_TYPE_GS_RCV_GS_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x550)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   中断状态标志。各bit单独对应一种中断类型，高有效。
             [0]: 中断类型0。W（主模）提前通知GS异频测量启动中断。
             [1]: 中断类型1。W（主模）进GAP中断，通知GS进行异频测量射频通道配置，天线切换等操作。
             [2]: 中断类型2。W（主模）出GAP中断。
             [3]: 中断类型3。W（从模，即异频）测量结束中断。
             [4]: 中断类型4。W（主模）强制GS退出异频测量中断。
             [5]: 中断类型5。W（主模）通知GS上报本次测量结果。
             [6]: 中断类型6。保留。
             [15:7]: 对应中断类型[15:7]，预留。
             中断状态标志0，1，2只有当W处于主模时才能产生。
             软件读取该中断状态上报寄存器后，需要和0x08B0的int_mask_gs_rcv_w相与，再判断是否需要处理。
   UNION结构:  BBPCOMM_INT_TYPE_GS_RCV_W_UNION */
#define BBPCOMM_INT_TYPE_GS_RCV_W_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x554)

/* 寄存器说明：寄存器
 bit[31:3]   保留
 bit[2:0]    主模产生int0、1、2的上报（(包括异频、异系统场景)），高有效。
             [0]: GS主模时，CTU告诉通知GSDSP产生int0中断。
             [1]: GS主模时，CTU告诉通知GSDSP产生int1中断。
             [2]: GS主模时，CTU告诉通知GSDSP产生int2中断。
             软件读取该中断状态上报寄存器后，需要和0x08B4的int_mask_gs_int012相与，再判断是否需要处理。
   UNION结构:  BBPCOMM_INT_TYPE_GS_INT012_UNION */
#define BBPCOMM_INT_TYPE_GS_INT012_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x558)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:3]   逻辑自清零。高有效。
             
             bit15~7：对应gs_snd_lte_int_15 ~ 7。
             GS DSP通过此寄存器触发类型15~7中断（int_type_lte_rcv_gs[15:7]）给LTEDSP。
             生效时刻：立即生效
             
             bit6：对应gs_snd_lte_int_6。
             GSDSP通过此寄存器触发类型6中断（int_type_lte_rcv_gs[6]）给LTEDSP。
             生效时刻：立即生效
             
             bit5：对应gs_snd_lte_int_5。
             GS主模时通知LTEDSP LTE测量周期到达，高有效。
             GS DSP通过此寄存器触发类型5中断（int_type_lte_rcv_gs[5]）给LTEDSP。
             生效时刻：立即生效
             
             bit4：对应gs_snd_lte_int_4。
             GS主模时强制退出异系统测量指示。高有效。
             GS DSP通过此寄存器触发类型4中断（int_type_lte_rcv_gs[4]）给LTEDSP。
             生效时刻：立即生效
             
             bit3：对应gs_snd_lte_int_3。GS测量结束指示，高有效。
             用于触发中断类型3 （int_type_lte_rcv_gs[3]）给LTEDSP。LTE主模下对GS进行异系统测量时，如果GS测量结束，GS DSP配置此标志为1。 
             生效时刻：立即生效
 bit[2:0]    保留
   UNION结构:  BBPCOMM_GS_SND_LTE_INT_13_UNION */
#define BBPCOMM_GS_SND_LTE_INT_13_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x55C)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:3]   逻辑自清零。高有效。
             
             bit15~7：对应gs_snd_tds_int_15 ~ 7。
             GS DSP通过此寄存器触发类型15~7中断（int_type_tds_rcv_gs[15:7]）给TDSDSP。
             生效时刻：立即生效
             
             bit6：对应gs_snd_tds_int_6。
             GSDSP通过此寄存器触发类型6中断（int_type_tds_rcv_gs[6]）给TDSDSP。
             生效时刻：立即生效
             
             bit5：对应gs_snd_tds_int_5。
             GS主模时通知TDSDSP TDS测量周期到达，高有效。
             GS DSP通过此寄存器触发类型5中断（int_type_tds_rcv_gs[5]）给TDSDSP。
             生效时刻：立即生效
             
             bit4：对应gs_snd_tds_int_4。
             GS主模时强制退出异系统测量指示。高有效。
             GS DSP通过此寄存器触发类型4中断（int_type_tds_rcv_gs[4]）给TDSDSP。
             生效时刻：立即生效
             
             bit3：对应gs_snd_tds_int_3。GS测量结束指示，高有效。
             用于触发中断类型3 （int_type_tds_rcv_gs[3]）给TDSDSP。TDS主模下对GS进行异系统测量时，如果GS测量结束，GS DSP配置此标志为1。 
             生效时刻：立即生效
 bit[2:0]    保留
   UNION结构:  BBPCOMM_GS_SND_TDS_INT_13_UNION */
#define BBPCOMM_GS_SND_TDS_INT_13_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x560)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:3]   逻辑自清零。高有效。
             
             bit15~7：对应gs_snd_gm_int_15 ~ 7。
             GS DSP通过此寄存器触发类型15~7中断（int_type_gm_rcv_gs[15:7]）给GMDSP。
             生效时刻：立即生效
             
             bit6：对应gs_snd_gm_int_6。
             GSDSP通过此寄存器触发类型6中断（int_type_gm_rcv_gs[6]）给GMDSP。
             生效时刻：立即生效
             
             bit5：对应gs_snd_gm_int_5。
             GS主模时通知GMDSP GM测量周期到达，高有效。
             GS DSP通过此寄存器触发类型5中断（int_type_gm_rcv_gs[5]）给GMDSP。
             生效时刻：立即生效
             
             bit4：对应gs_snd_gm_int_4。
             GS主模时强制退出异系统测量指示。高有效。
             GS DSP通过此寄存器触发类型4中断（int_type_gm_rcv_gs[4]）给GMDSP。
             生效时刻：立即生效
             
             bit3：对应gs_snd_gm_int_3。GS测量结束指示，高有效。
             用于触发中断类型3 （int_type_gm_rcv_gs[3]）给GMDSP。GM主模下对GS进行异系统测量时，如果GS测量结束，GS DSP配置此标志为1。 
             生效时刻：立即生效
 bit[2:0]    保留
   UNION结构:  BBPCOMM_GS_SND_GM_INT_13_UNION */
#define BBPCOMM_GS_SND_GM_INT_13_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x564)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:3]   逻辑自清零。高有效。
             
             bit15~7：对应gs_snd_gs_int_15 ~ 7。
             GS DSP通过此寄存器触发类型15~7中断（int_type_gs_rcv_gs[15:7]）给GSDSP。
             生效时刻：立即生效
             
             bit6：对应gs_snd_gs_int_6。
             GSDSP通过此寄存器触发类型6中断（int_type_gs_rcv_gs[6]）给GSDSP。
             生效时刻：立即生效
             
             bit5：对应gs_snd_gs_int_5。
             GS主模时通知GSDSP GS测量周期到达，高有效。
             GS DSP通过此寄存器触发类型5中断（int_type_gs_rcv_gs[5]）给GSDSP。
             生效时刻：立即生效
             
             bit4：对应gs_snd_gs_int_4。
             GS主模时强制退出异系统测量指示。高有效。
             GS DSP通过此寄存器触发类型4中断（int_type_gs_rcv_gs[4]）给GSDSP。
             生效时刻：立即生效
             
             bit3：对应gs_snd_gs_int_3。GS测量结束指示，高有效。
             用于触发中断类型3 （int_type_gs_rcv_gs[3]）给GSDSP。GS主模下对GS进行异系统测量时，如果GS测量结束，GS DSP配置此标志为1。 
             生效时刻：立即生效
 bit[2:0]    保留
   UNION结构:  BBPCOMM_GS_SND_GS_INT_13_UNION */
#define BBPCOMM_GS_SND_GS_INT_13_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x568)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:3]   逻辑自清零。高有效。
             
             bit15~7：对应gs_snd_w_int_15 ~ 7。
             GS DSP通过此寄存器触发类型15~7中断（int_type_w_rcv_gs[15:7]）给WDSP。
             生效时刻：立即生效
             
             bit6：对应gs_snd_w_int_6。
             GSDSP通过此寄存器触发类型6中断（int_type_w_rcv_gs[6]）给WDSP。
             生效时刻：立即生效
             
             bit5：对应gs_snd_w_int_5。
             GS主模时通知WDSP W测量周期到达，高有效。
             GS DSP通过此寄存器触发类型5中断（int_type_w_rcv_gs[5]）给WDSP。
             生效时刻：立即生效
             
             bit4：对应gs_snd_w_int_4。
             GS主模时强制退出异系统测量指示。高有效。
             GS DSP通过此寄存器触发类型4中断（int_type_w_rcv_gs[4]）给WDSP。
             生效时刻：立即生效
             
             bit3：对应gs_snd_w_int_3。GS测量结束指示，高有效。
             用于触发中断类型3 （int_type_w_rcv_gs[3]）给WDSP。W主模下对GS进行异系统测量时，如果GS测量结束，GS DSP配置此标志为1。 
             生效时刻：立即生效
 bit[2:0]    保留
   UNION结构:  BBPCOMM_GS_SND_W_INT_13_UNION */
#define BBPCOMM_GS_SND_W_INT_13_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0x56C)

/* 寄存器说明：GS为从模时对应通道的指示寄存器
 bit[31:5]   保留
 bit[4:4]    C2为从模时对应的通道选择信号生效方式。
             0：在int1生效；
             1：立即生效。
 bit[3:2]    保留
 bit[1:0]    C2为从模时对应的通道选择信号。
             0：选择通道0；
             1：选择通道1；
             2：选择通道2；
             3：选择通道3。
             配置时刻：各模根据通信场景配置
   UNION结构:  BBPCOMM_S_C_CH_NUM_IND_UNION */
#define BBPCOMM_S_C_CH_NUM_IND_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0x580)

/* 寄存器说明：寄存器
 bit[31:4]   保留
 bit[3:0]    异系统测量类型。
             4’b0：测量C2。
             4’b1: C2背景搜；
             其它预留。
             生效时刻：立即生效
   UNION结构:  BBPCOMM_C_INTERSYS_MEASURE_TYPE_UNION */
#define BBPCOMM_C_INTERSYS_MEASURE_TYPE_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0x584)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0:0]    单频点测量周期到指示，L或者TDS/Gm/Gs/U作为主模，通知C2PHY W测量的单频点周期到达。
             只在连接态下需要配置。
             电平信号，高有效。
             生效时刻：立即生效
   UNION结构:  BBPCOMM_C_MEASURE_REPORT_VALID_UNION */
#define BBPCOMM_C_MEASURE_REPORT_VALID_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0x588)

/* 寄存器说明：寄存器
   详      述：预处理中断int0到int1之间的offset信息，单位us（向下取整）。。
               配置时刻：主模启动C2从模异系统测量时配置
               生效时刻：立即生效
   UNION结构 ：无 */
#define BBPCOMM_C_PREINT_OFFSET_TIME_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x58C)

/* 寄存器说明：寄存器
   详      述：C2作为从模时，主模分配给C2用于异系统测量时间长度，告知C2PHY。单位us，向下取整到us。
               配置时刻：主模启动C2从模异系统测量时配置
               生效时刻：立即生效
   UNION结构 ：无 */
#define BBPCOMM_C_INTERSYS_MEASURE_TIME_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0x590)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   逻辑自清零。
             中断标志清除指示，高有效。用于清除INT_TYPE_LTE_RCV_C[15:0]对应bit位
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_CLEAR_LTE_RCV_C_UNION */
#define BBPCOMM_INT_CLEAR_LTE_RCV_C_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x594)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   中断屏蔽标志。用于屏蔽INT_TYPE_LTE_RCV_C[15:0]对应bit中断。
             0：屏蔽中断上报；
             1：使能中断上报。
             配置时刻：初始化
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_MASK_LTE_RCV_C_UNION */
#define BBPCOMM_INT_MASK_LTE_RCV_C_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x598)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   中断状态标志。各bit单独对应一种中断类型，高有效。
             [0]: 中断类型0。 C2（主模）提前通知LTE异系统测量启动中断。
             [1]: 中断类型1。 C2（主模）进GAP中断，通知LTE进行异系统测量射频通道配置，天线切换等操作。
             [2]: 中断类型2。C2（主模）出GAP中断。
             [3]: 中断类型3。C2（从模）测量结束中断。
             [4]: 中断类型4。C2（主模）强制C2退出异系统测量中断。
             [5]: 中断类型5。C2（主模）通知C2上报本次测量结果。
             [6]: 保留。
             [15:7]: 对应中断类型[15:7]，预留。
             软件读取该中断状态上报寄存器后，需要和0x0A84的int_mask_lte_rcv_c相与，再判断是否需要处理。
   UNION结构:  BBPCOMM_INT_TYPE_LTE_RCV_C_UNION */
#define BBPCOMM_INT_TYPE_LTE_RCV_C_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x59C)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:3]   逻辑自清零。高有效。
             
             bit15~7：对应lte_snd_c_int_15 ~ 7。
             LPHY通过此寄存器触发类型15~7中断（int_type_c_rcv_lte[15:7]）给C2PHY。
             生效时刻：立即生效
             
             bit6：对应lte_snd_c_int_6。
             LPHY通过此寄存器触发类型6中断（int_type_lte_rcv_c[6]）给LPHY。
             生效时刻：立即生效
             
             bit5：对应c_snd_lte_int_5。
             L主模时通知LPHY L测量周期到达，高有效。
             LPHY通过此寄存器触发类型5中断（int_type_c_rcv_lte[5]）给LPHY。
             生效时刻：立即生效
             
             bit4：对应lte_snd_c_int_4。
             L主模时强制退出异系统测量指示。高有效。
             LPHY通过此寄存器触发类型4中断（int_type_c_rcv_lte[4]）给C2PHY。
             生效时刻：立即生效
             
             bit3：对应lte_snd_c_int_3。L测量结束指示，高有效。
             用于触发中断类型3 （int_type_c_rcv_lte[3]）给C2PHY。C2主模下对L进行异系统测量时，如果L测量结束，LPHY配置此标志为1。 
             生效时刻：立即生效
 bit[2:0]    保留
   UNION结构:  BBPCOMM_LTE_SND_C_INT_13_UNION */
#define BBPCOMM_LTE_SND_C_INT_13_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x5A0)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:3]   逻辑自清零。高有效。
             
             bit15~7：对应c_snd_c_int_15 ~ 7。
             C2 DSP通过此寄存器触发类型15~7中断（int_type_c_rcv_c[15:7]）给C2 DSP。
             生效时刻：立即生效
             
             bit6：对应c_snd_c_int_6。
             C2DSP通过此寄存器触发类型6中断（int_type_c_rcv_c[6]）给C2DSP。
             生效时刻：立即生效
             
             bit5：对应c_snd_c_int_5。
             C2主模时通知C2DSP C2测量周期到达，高有效。
             C2 DSP通过此寄存器触发类型5中断（int_type_c_rcv_c[5]）给C2DSP。
             生效时刻：立即生效
             
             bit4：对应c_snd_c_int_4。
             C2主模时强制退出异系统测量指示。高有效。
             C2 DSP通过此寄存器触发类型4中断（int_type_c_rcv_c[4]）给C2DSP。
             生效时刻：立即生效
             
             bit3：对应c_snd_c_int_3。C2测量结束指示，高有效。
             用于触发中断类型3 （int_type_c_rcv_c[3]）给C2DSP。C2主模下对C2进行异系统测量时，如果C2测量结束，C2 DSP配置此标志为1。 
             生效时刻：立即生效
 bit[2:0]    保留
   UNION结构:  BBPCOMM_C_SND_C_INT_13_UNION */
#define BBPCOMM_C_SND_C_INT_13_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0x5A4)

/* 寄存器说明：寄存器
   详      述：W/TD/GM/L/GS为主模时写此寄存器，GS为从模时读取此寄存器。此寄存器由DSP之间进行读写，BBP仅提供接口。
   UNION结构 ：无 */
#define BBPCOMM_MEAS_FLAG_C_RD_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0x5A8)

/* 寄存器说明：寄存器
   详      述：C2为从模时写此寄存器，W/TD/GM/L/GS主模读取此寄存器。此寄存器由DSP之间进行读写，BBP仅提供接口。
   UNION结构 ：无 */
#define BBPCOMM_WAKE_FLAG_C_WR_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0x5AC)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   逻辑自清零。
             中断标志清除指示，高有效。用于清除INT_TYPE_C_RCV_LTE[15:0]对应bit位
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_CLEAR_C_RCV_LTE_UNION */
#define BBPCOMM_INT_CLEAR_C_RCV_LTE_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x5B0)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   逻辑自清零。
             中断标志清除指示，高有效。用于清除INT_TYPE_C_RCV_C[15:0]对应bit位
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_CLEAR_C_RCV_C_UNION */
#define BBPCOMM_INT_CLEAR_C_RCV_C_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x5B4)

/* 寄存器说明：寄存器
 bit[31:3]   保留
 bit[2:0]    逻辑自清零。
             中断标志清除指示，高有效。用于清除INT_TYPE_C_INT012[2:0]对应bit位
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_CLEAR_C_INT012_UNION */
#define BBPCOMM_INT_CLEAR_C_INT012_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x5B8)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   中断屏蔽标志。用于屏蔽INT_TYPE_C_RCV_LTE[15:0]对应bit中断。
             0：屏蔽中断上报；
             1：使能中断上报。
             配置时刻：初始化
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_MASK_C_RCV_LTE_UNION */
#define BBPCOMM_INT_MASK_C_RCV_LTE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x5BC)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   中断屏蔽标志。用于屏蔽INT_TYPE_C_RCV_C[15:0]对应bit中断。
             0：屏蔽中断上报；
             1：使能中断上报。
             配置时刻：初始化
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_MASK_C_RCV_C_UNION */
#define BBPCOMM_INT_MASK_C_RCV_C_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x5C0)

/* 寄存器说明：寄存器
 bit[31:3]   保留
 bit[2:0]    中断屏蔽标志。用于屏蔽INT_TYPE_C_INT012[2:0]对应bit中断。
             0：屏蔽中断上报；
             1：使能中断上报。
             配置时刻：初始化
             生效时刻：立即生效
   UNION结构:  BBPCOMM_INT_MASK_C_INT012_UNION */
#define BBPCOMM_INT_MASK_C_INT012_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x5C4)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   中断状态标志。各bit单独对应一种中断类型，高有效。
             [0]: 中断类型0。 LTE（主模）提前通知C2异系统测量启动中断。
             [1]: 中断类型1。 LTE（主模）进GAP中断，通知C2进行异系统测量射频通道配置，天线切换等操作。
             [2]: 中断类型2。 LTE（主模）出GAP中断。
             [3]: 中断类型3。LTE（从模）测量结束中断。
             [4]: 中断类型4。LTE（主模）强制C2退出异系统测量中断。
             [5]: 中断类型5。LTE（主模）通知C2上报本次测量结果。
             [6]: 保留。
             [15:7]: 对应中断类型[15:7]，预留。
             软件读取该中断状态上报寄存器后，需要和0x0B34的int_mask_c_rcv_lte相与，再判断是否需要处理。
   UNION结构:  BBPCOMM_INT_TYPE_C_RCV_LTE_UNION */
#define BBPCOMM_INT_TYPE_C_RCV_LTE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x5C8)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   中断状态标志。各bit单独对应一种中断类型，高有效。
             [0]: 中断类型0。C2（主模）提前通知LTE异频测量启动中断。
             [1]: 中断类型1。C2（主模）进GAP中断，通知C2进行异频测量射频通道配置，天线切换等操作。
             [2]: 中断类型2。C2（主模）出GAP中断。
             [3]: 中断类型3。C2（从模，即异频）测量结束中断。
             [4]: 中断类型4。C2（主模）强制C2退出异频测量中断。
             [5]: 中断类型5。C2（主模）通知C2上报本次测量结果。
             [6]: 中断类型6。保留。
             [15:7]: 对应中断类型[15:7]，预留。
             中断状态标志0，1，2只有当LTE处于主模时才能产生。
             软件读取该中断状态上报寄存器后，需要和0x0B38的int_mask_c_rcv_c相与，再判断是否需要处理。
   UNION结构:  BBPCOMM_INT_TYPE_C_RCV_C_UNION */
#define BBPCOMM_INT_TYPE_C_RCV_C_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x5CC)

/* 寄存器说明：寄存器
 bit[31:3]   保留
 bit[2:0]    增加主模产生int0、1、2的上报（(包括异频、异系统场景)），高有效。
             [0]: C2主模时，C2TU告诉通知C2PHY产生int0中断。
             [1]: C2主模时，C2TU告诉通知C2PHY产生int1中断。
             [2]:C2W主模时，C2TU告诉通知C2PHY产生int2中断。
             软件读取该中断状态上报寄存器后，需要和0x0704的int_mask_c_int012相与，再判断是否需要处理。
   UNION结构:  BBPCOMM_INT_TYPE_C_INT012_UNION */
#define BBPCOMM_INT_TYPE_C_INT012_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x5D0)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:3]   逻辑自清零。高有效。
             
             bit15~7：对应c_snd_lte_int_15 ~ 7。
             C2PHY通过此寄存器触发类型15~7中断（int_type_lte_rcv_c[15:7]）给LPHY。
             生效时刻：立即生效
             
             bit6：对应c_snd_lte_int_6。
             C2PHY通过此寄存器触发类型6中断（int_type_lte_rcv_c[6]）给LPHY。
             生效时刻：立即生效
             
             bit5：对应c_snd_lte_int_5。
             C2主模时通知C2PHY L测量周期到达，高有效。
             C2PHY通过此寄存器触发类型5中断（int_type_lte_rcv_c[5]）给C2PHY。
             生效时刻：立即生效
             
             bit4：对应c_snd_lte_int_4。
             C2主模时强制退出异系统测量指示。高有效。
             C2PHY通过此寄存器触发类型4中断（int_type_lte_rcv_c[4]）给LPHY。
             生效时刻：立即生效
             
             bit3：对应c_snd_lte_int_3。C2测量结束指示，高有效。
             用于触发中断类型3 （int_type_lte_rcv_c[3]）给LPHY。L主模下对C2进行异系统测量时，如果C2测量结束，C2PHY配置此标志为1。 
             生效时刻：立即生效
 bit[2:0]    保留
   UNION结构:  BBPCOMM_C_SND_LTE_INT_13_UNION */
#define BBPCOMM_C_SND_LTE_INT_13_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x5D4)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      1'b0：TDS CTU中断输出至物理层；
             1'b1：C CTU中断输出至物理层。
   UNION结构:  BBPCOMM_TDS_C_CTU_INT_SEL_UNION */
#define BBPCOMM_TDS_C_CTU_INT_SEL_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x5D8)

/* 寄存器说明：寄存器
   详      述：寄存器0，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG0_FOR_USE_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x600)

/* 寄存器说明：寄存器
   详      述：寄存器1，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG1_FOR_USE_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x604)

/* 寄存器说明：寄存器
   详      述：寄存器2，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG2_FOR_USE_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x608)

/* 寄存器说明：寄存器
   详      述：寄存器3，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG3_FOR_USE_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x60C)

/* 寄存器说明：寄存器
   详      述：寄存器4，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG4_FOR_USE_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x610)

/* 寄存器说明：寄存器
   详      述：寄存器5，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG5_FOR_USE_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x614)

/* 寄存器说明：寄存器
   详      述：寄存器6，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG6_FOR_USE_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x618)

/* 寄存器说明：寄存器
   详      述：寄存器7，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG7_FOR_USE_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x61C)

/* 寄存器说明：寄存器
   详      述：寄存器8，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG8_FOR_USE_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x620)

/* 寄存器说明：寄存器
   详      述：寄存器9，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG9_FOR_USE_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x624)

/* 寄存器说明：寄存器
   详      述：寄存器10，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG10_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x628)

/* 寄存器说明：寄存器
   详      述：寄存器11，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG11_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x62C)

/* 寄存器说明：寄存器
   详      述：寄存器12，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG12_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x630)

/* 寄存器说明：寄存器
   详      述：寄存器13，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG13_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x634)

/* 寄存器说明：寄存器
   详      述：寄存器14，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG14_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x638)

/* 寄存器说明：寄存器
   详      述：寄存器15，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG15_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x63C)

/* 寄存器说明：寄存器
   详      述：寄存器16，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG16_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x640)

/* 寄存器说明：寄存器
   详      述：寄存器17，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG17_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x644)

/* 寄存器说明：寄存器
   详      述：寄存器18，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG18_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x648)

/* 寄存器说明：寄存器
   详      述：寄存器19，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG19_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x64C)

/* 寄存器说明：寄存器
   详      述：寄存器20，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG20_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x650)

/* 寄存器说明：寄存器
   详      述：寄存器21，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG21_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x654)

/* 寄存器说明：寄存器
   详      述：寄存器22，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG22_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x658)

/* 寄存器说明：寄存器
   详      述：寄存器23，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG23_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x65C)

/* 寄存器说明：寄存器
   详      述：寄存器24，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG24_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x660)

/* 寄存器说明：寄存器
   详      述：寄存器25，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG25_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x664)

/* 寄存器说明：寄存器
   详      述：寄存器26，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG26_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x668)

/* 寄存器说明：寄存器
   详      述：寄存器27，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG27_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x66C)

/* 寄存器说明：寄存器
   详      述：寄存器28，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG28_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x670)

/* 寄存器说明：寄存器
   详      述：寄存器29，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG29_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x674)

/* 寄存器说明：寄存器
   详      述：寄存器30，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG30_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x678)

/* 寄存器说明：寄存器
   详      述：寄存器31，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG31_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x67C)

/* 寄存器说明：寄存器
   详      述：寄存器32，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG32_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x680)

/* 寄存器说明：寄存器
   详      述：寄存器33，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG33_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x684)

/* 寄存器说明：寄存器
   详      述：寄存器34，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG34_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x688)

/* 寄存器说明：寄存器
   详      述：寄存器35，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG35_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x68C)

/* 寄存器说明：寄存器
   详      述：寄存器36，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG36_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x690)

/* 寄存器说明：寄存器
   详      述：寄存器37，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG37_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x694)

/* 寄存器说明：寄存器
   详      述：寄存器38，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG38_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x698)

/* 寄存器说明：寄存器
   详      述：寄存器39，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG39_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x69C)

/* 寄存器说明：寄存器
   详      述：寄存器40，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG40_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x6A0)

/* 寄存器说明：寄存器
   详      述：寄存器41，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG41_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x6A4)

/* 寄存器说明：寄存器
   详      述：寄存器42，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG42_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x6A8)

/* 寄存器说明：寄存器
   详      述：寄存器43，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG43_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x6AC)

/* 寄存器说明：寄存器
   详      述：寄存器44，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG44_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x6B0)

/* 寄存器说明：寄存器
   详      述：寄存器45，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG45_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x6B4)

/* 寄存器说明：寄存器
   详      述：寄存器46，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG46_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x6B8)

/* 寄存器说明：寄存器
   详      述：寄存器47，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG47_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x6BC)

/* 寄存器说明：寄存器
   详      述：寄存器48，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG48_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x1600)

/* 寄存器说明：寄存器
   详      述：寄存器49，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG49_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x1604)

/* 寄存器说明：寄存器
   详      述：寄存器50，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG50_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x1608)

/* 寄存器说明：寄存器
   详      述：寄存器51，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG51_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x160C)

/* 寄存器说明：寄存器
   详      述：寄存器52，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG52_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x1610)

/* 寄存器说明：寄存器
   详      述：寄存器53，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG53_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x1614)

/* 寄存器说明：寄存器
   详      述：寄存器54，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG54_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x1618)

/* 寄存器说明：寄存器
   详      述：寄存器55，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG55_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x161C)

/* 寄存器说明：寄存器
   详      述：寄存器56，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG56_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x1620)

/* 寄存器说明：寄存器
   详      述：寄存器57，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG57_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x1624)

/* 寄存器说明：寄存器
   详      述：寄存器58，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG58_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x1628)

/* 寄存器说明：寄存器
   详      述：寄存器59，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG59_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x162C)

/* 寄存器说明：寄存器
   详      述：寄存器60，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG60_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x1630)

/* 寄存器说明：寄存器
   详      述：寄存器61，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG61_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x1634)

/* 寄存器说明：寄存器
   详      述：寄存器62，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG62_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x1638)

/* 寄存器说明：寄存器
   详      述：寄存器63，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG63_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x163C)

/* 寄存器说明：寄存器
   详      述：寄存器64，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG64_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x1640)

/* 寄存器说明：寄存器
   详      述：寄存器65，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG65_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x1644)

/* 寄存器说明：寄存器
   详      述：寄存器66，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG66_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x1648)

/* 寄存器说明：寄存器
   详      述：寄存器67，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG67_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x164C)

/* 寄存器说明：寄存器
   详      述：寄存器68，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG68_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x1650)

/* 寄存器说明：寄存器
   详      述：寄存器69，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG69_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x1654)

/* 寄存器说明：寄存器
   详      述：寄存器70，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG70_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x1658)

/* 寄存器说明：寄存器
   详      述：寄存器71，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG71_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x165C)

/* 寄存器说明：寄存器
   详      述：寄存器72，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG72_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x1660)

/* 寄存器说明：寄存器
   详      述：寄存器73，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG73_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x1664)

/* 寄存器说明：寄存器
   详      述：寄存器74，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG74_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x1668)

/* 寄存器说明：寄存器
   详      述：寄存器75，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG75_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x166C)

/* 寄存器说明：寄存器
   详      述：寄存器76，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG76_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x1670)

/* 寄存器说明：寄存器
   详      述：寄存器77，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG77_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x1674)

/* 寄存器说明：寄存器
   详      述：寄存器78，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG78_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x1678)

/* 寄存器说明：寄存器
   详      述：寄存器79，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG79_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x167C)

/* 寄存器说明：寄存器
   详      述：寄存器80，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG80_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x1680)

/* 寄存器说明：寄存器
   详      述：寄存器81，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG81_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x1684)

/* 寄存器说明：寄存器
   详      述：寄存器82，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG82_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x1688)

/* 寄存器说明：寄存器
   详      述：寄存器83，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG83_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x168C)

/* 寄存器说明：寄存器
   详      述：寄存器84，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG84_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x1690)

/* 寄存器说明：寄存器
   详      述：寄存器85，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG85_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x1694)

/* 寄存器说明：寄存器
   详      述：寄存器86，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG86_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x1698)

/* 寄存器说明：寄存器
   详      述：寄存器87，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG87_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x169C)

/* 寄存器说明：寄存器
   详      述：寄存器88，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG88_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x16A0)

/* 寄存器说明：寄存器
   详      述：寄存器89，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG89_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x16A4)

/* 寄存器说明：寄存器
   详      述：寄存器90，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG90_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x16A8)

/* 寄存器说明：寄存器
   详      述：寄存器91，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG91_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x16AC)

/* 寄存器说明：寄存器
   详      述：寄存器92，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG92_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x16B0)

/* 寄存器说明：寄存器
   详      述：寄存器93，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG93_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x16B4)

/* 寄存器说明：寄存器
   详      述：寄存器94，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG94_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x16B8)

/* 寄存器说明：寄存器
   详      述：寄存器95，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG95_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x16BC)

/* 寄存器说明：寄存器
   详      述：寄存器96，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG96_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x16C0)

/* 寄存器说明：寄存器
   详      述：寄存器97，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG97_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x16C4)

/* 寄存器说明：寄存器
   详      述：寄存器98，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG98_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x16C8)

/* 寄存器说明：寄存器
   详      述：寄存器99，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG99_FOR_USE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x16CC)

/* 寄存器说明：寄存器
   详      述：寄存器100，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG100_FOR_USE_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0x16D0)

/* 寄存器说明：寄存器
   详      述：寄存器101，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG101_FOR_USE_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0x16D4)

/* 寄存器说明：寄存器
   详      述：寄存器102，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG102_FOR_USE_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0x16D8)

/* 寄存器说明：寄存器
   详      述：寄存器103，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG103_FOR_USE_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0x16DC)

/* 寄存器说明：寄存器
   详      述：寄存器104，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG104_FOR_USE_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0x16E0)

/* 寄存器说明：寄存器
   详      述：寄存器105，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG105_FOR_USE_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0x16E4)

/* 寄存器说明：寄存器
   详      述：寄存器106，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG106_FOR_USE_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0x16E8)

/* 寄存器说明：寄存器
   详      述：寄存器107，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG107_FOR_USE_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0x16EC)

/* 寄存器说明：寄存器
   详      述：寄存器108，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG108_FOR_USE_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0x16F0)

/* 寄存器说明：寄存器
   详      述：寄存器109，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG109_FOR_USE_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0x16F4)

/* 寄存器说明：寄存器
   详      述：寄存器110，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG110_FOR_USE_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0x16F8)

/* 寄存器说明：寄存器
   详      述：寄存器111，预留。供DSP之间传递信息。
   UNION结构 ：无 */
#define BBPCOMM_REG111_FOR_USE_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0x16FC)

/* 寄存器说明：门控时钟配置寄存器
 bit[31:2]   保留
 bit[1:1]    bbp_comm_dbg模块时钟bypass配置信号：
             1：直接使用输入时钟，不进行门控处理，此时dsp_dbg_clk_gate_en配置无效；
             0：表示根据dsp_dbg_clk_gate_en进行门控处理。
 bit[0:0]    bbp_comm_dbg模块门控时钟使能信号：
             1：直接使用输入时钟，未进行门控；
             0：输入时钟无效，此时进行低功耗状态。
   UNION结构:  BBPCOMM_DBG_CLK_GATE_EN_UNION */
#define BBPCOMM_DBG_CLK_GATE_EN_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0x700)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0:0]    bbp_comm_dbg使能信号：
             1：使能；
             0：不使能。
   UNION结构:  BBPCOMM_DBG_COMM_EN_UNION */
#define BBPCOMM_DBG_COMM_EN_ADDR                      (SOC_BBP_COMM_BASE_ADDR + 0x704)

/* 寄存器说明：寄存器
 bit[31:16]  可维可测的包个数
 bit[15:2]   保留
 bit[1]      可维可测数据上报模式：
             'b0：触发后继续采样dbg_pkg_num个数据包后自动结束；
             'b1：只要dbg_en为1就上报，没有上报个数限制。
 bit[0]      可维可测使能信号，当dbg_rpt_mode为0时逻辑自清，否则需要写清。
             1'b0：可维可测功能不使能                             1'b1：可维可测功能使能
   UNION结构:  BBPCOMM_DBG_EN_UNION */
#define BBPCOMM_DBG_EN_ADDR                           (SOC_BBP_COMM_BASE_ADDR + 0x708)

/* 寄存器说明：寄存器
   详      述：可维可测上报数据包ID号基址
   UNION结构 ：无 */
#define BBPCOMM_DBG_ID_ADDR                           (SOC_BBP_COMM_BASE_ADDR + 0x70C)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   可维可测内部分组指示：
             1：上报mipi数据
             2：上报ssi数据
             3：其它dbg上报数据
             其它：保留
   UNION结构:  BBPCOMM_DBG_FLT_UNION */
#define BBPCOMM_DBG_FLT_ADDR                          (SOC_BBP_COMM_BASE_ADDR + 0x710)

/* 寄存器说明：寄存器
 bit[31:4]   保留
 bit[3:0]    可维可测mipi采集数据通道屏蔽指示：
             dbg_mipi_ch_mask[X],X=0~3,则：
             0：通道X的mipi数据不采集
             1：采集通道X的mipi数据
   UNION结构:  BBPCOMM_DBG_MIPI_CH_MASK_UNION */
#define BBPCOMM_DBG_MIPI_CH_MASK_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x714)

/* 寄存器说明：寄存器
 bit[31:4]   保留
 bit[3:0]    可维可测ssi采集数据通道屏蔽指示：
             dbg_ssi_ch_mask[X],X=0~3,则：
             0：通道X的ssi数据不采集
             1：采集通道X的ssi数据
   UNION结构:  BBPCOMM_DBG_SSI_CH_MASK_UNION */
#define BBPCOMM_DBG_SSI_CH_MASK_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0x718)

/* 寄存器说明：寄存器
   详      述：由软件直接控制MIPI0 master,不借助xbbp发送回读指令时,回读指令存放低32bit.
   UNION结构 ：无 */
#define BBPCOMM_MIPI0_RD_DATA_LOW_SOFT_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0x780)

/* 寄存器说明：寄存器
   详      述：由软件直接控制MIPI0 master,不借助xbbp发送回读指令时,回读指令存放高32bit.
   UNION结构 ：无 */
#define BBPCOMM_MIPI0_RD_DATA_HIGH_SOFT_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0x784)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      由软件直接控制MIPI0 master,不借助xbbp发送回读指令时,回读数据有效指示
   UNION结构:  BBPCOMM_RD_END_FLAG_MIPI0_SOFT_UNION */
#define BBPCOMM_RD_END_FLAG_MIPI0_SOFT_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0x788)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      由软件直接控制MIPI0 master
             1:软件可以发送CFG_IND启动mipi0
             0:软件等待mipi0授权使用
   UNION结构:  BBPCOMM_MIPI0_GRANT_DSP_UNION */
#define BBPCOMM_MIPI0_GRANT_DSP_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0x78C)

/* 寄存器说明：寄存器
   详      述：由软件直接控制MIPI0 master,不借助xbbp发送写指令时,写指令低32bit。
               在MIPI动态使能mipi_dyn_exchg_en有效时，MIPI扩展指令时，dsp_mipi0_wdata_low[1:0]应配置为0
   UNION结构 ：无 */
#define BBPCOMM_DSP_MIPI0_WDATA_LOW_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x790)

/* 寄存器说明：寄存器
   详      述：由软件直接控制MIPI0 master,不借助xbbp发送写指令时,写指令高32bit。
               在MIPI动态使能mipi_dyn_exchg_en有效，MIPI非扩展指令时，dsp_mipi0_wdata_high[1:0]应配置为0
   UNION结构 ：无 */
#define BBPCOMM_DSP_MIPI0_WDATA_HIGH_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x794)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      由软件直接控制MIPI0 master,需首先拉高此指示,屏蔽xbbp对MIPI0的控制
   UNION结构:  BBPCOMM_DSP_MIPI0_EN_IMI_UNION */
#define BBPCOMM_DSP_MIPI0_EN_IMI_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x798)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      由软件直接控制MIPI0 master,拉高此dsp_mipi0_en后,产生软件启动脉冲
   UNION结构:  BBPCOMM_DSP_MIPI0_CFG_IND_IMI_UNION */
#define BBPCOMM_DSP_MIPI0_CFG_IND_IMI_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0x79C)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      由软件直接控制MIPI0 master,取走回读数据后,清标志位脉冲
   UNION结构:  BBPCOMM_DSP_MIPI0_RD_CLR_UNION */
#define BBPCOMM_DSP_MIPI0_RD_CLR_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x7A0)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      cpu配置mipi功能,配置为1才能正常工作, 测试时配置为0
   UNION结构:  BBPCOMM_CPU_MIPI0_FUNC_SEL_UNION */
#define BBPCOMM_CPU_MIPI0_FUNC_SEL_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x7A4)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      cpu配置mipi功能,测试用
   UNION结构:  BBPCOMM_CPU_MIPI0_TEST_FUNC_UNION */
#define BBPCOMM_CPU_MIPI0_TEST_FUNC_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x7A8)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      cpu配置mipi功能, 测试用
   UNION结构:  BBPCOMM_CPU_MIPI0_SCLK_TEST_UNION */
#define BBPCOMM_CPU_MIPI0_SCLK_TEST_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x7AC)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      cpu配置mipi功能, 测试用
   UNION结构:  BBPCOMM_CPU_MIPI0_SDATA_TEST_UNION */
#define BBPCOMM_CPU_MIPI0_SDATA_TEST_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x7B0)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      cpu配置mipi功能,mipi0master清异常信号
   UNION结构:  BBPCOMM_CPU_MIPI0_CLR_IND_IMI_UNION */
#define BBPCOMM_CPU_MIPI0_CLR_IND_IMI_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0x7B4)

/* 寄存器说明：寄存器
   详      述：由软件直接控制MIPI1 master,不借助xbbp发送回读指令时,回读指令存放低32bit.
   UNION结构 ：无 */
#define BBPCOMM_MIPI1_RD_DATA_LOW_SOFT_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0x7C0)

/* 寄存器说明：寄存器
   详      述：由软件直接控制MIPI1 master,不借助xbbp发送回读指令时,回读指令存放高32bit.
   UNION结构 ：无 */
#define BBPCOMM_MIPI1_RD_DATA_HIGH_SOFT_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0x7C4)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      由软件直接控制MIPI1 master,不借助xbbp发送回读指令时,回读数据有效指示
   UNION结构:  BBPCOMM_RD_END_FLAG_MIPI1_SOFT_UNION */
#define BBPCOMM_RD_END_FLAG_MIPI1_SOFT_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0x7C8)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      由软件直接控制MIPI1 master
             1:软件可以发送CFG_IND启动mipi1
             0:软件等待mipi1授权使用
   UNION结构:  BBPCOMM_MIPI1_GRANT_DSP_UNION */
#define BBPCOMM_MIPI1_GRANT_DSP_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0x7CC)

/* 寄存器说明：寄存器
   详      述：由软件直接控制MIPI1 master,不借助xbbp发送写指令时,写指令高32bit。
               在MIPI动态使能mipi_dyn_exchg_en有效，在MIPI扩展指令时
               dsp_mipi1_wdata_low[1:0]应配置为0
   UNION结构 ：无 */
#define BBPCOMM_DSP_MIPI1_WDATA_LOW_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x7D0)

/* 寄存器说明：寄存器
   详      述：由软件直接控制MIPI1 master,不借助xbbp发送写指令时,写指令高32bit。
               在MIPI动态使能mipi_dyn_exchg_en有效，在MIPI非扩展指令时
               dsp_mipi1_wdata_high[1:0]应配置为0
   UNION结构 ：无 */
#define BBPCOMM_DSP_MIPI1_WDATA_HIGH_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x7D4)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      由软件直接控制MIPI1 master,需首先拉高此指示,屏蔽xbbp对MIPI1的控制
   UNION结构:  BBPCOMM_DSP_MIPI1_EN_IMI_UNION */
#define BBPCOMM_DSP_MIPI1_EN_IMI_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x7D8)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      由软件直接控制MIPI1 master,拉高此dsp_mipi1_en后,产生软件启动脉冲
   UNION结构:  BBPCOMM_DSP_MIPI1_CFG_IND_IMI_UNION */
#define BBPCOMM_DSP_MIPI1_CFG_IND_IMI_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0x7DC)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      由软件直接控制MIPI1 master,取走回读数据后,清标志位脉冲
   UNION结构:  BBPCOMM_DSP_MIPI1_RD_CLR_UNION */
#define BBPCOMM_DSP_MIPI1_RD_CLR_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x7E0)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      cpu配置mipi功能,配置为1才能正常工作, 测试时配置为0
   UNION结构:  BBPCOMM_CPU_MIPI1_FUNC_SEL_UNION */
#define BBPCOMM_CPU_MIPI1_FUNC_SEL_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x7E4)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      cpu配置mipi功能,测试用
   UNION结构:  BBPCOMM_CPU_MIPI1_TEST_FUNC_UNION */
#define BBPCOMM_CPU_MIPI1_TEST_FUNC_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x7E8)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      cpu配置mipi功能,测试用
   UNION结构:  BBPCOMM_CPU_MIPI1_SCLK_TEST_UNION */
#define BBPCOMM_CPU_MIPI1_SCLK_TEST_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x7EC)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      cpu配置mipi功能,测试用
   UNION结构:  BBPCOMM_CPU_MIPI1_SDATA_TEST_UNION */
#define BBPCOMM_CPU_MIPI1_SDATA_TEST_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x7F0)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      cpu配置mipi功能,mipi1master清异常信号
   UNION结构:  BBPCOMM_CPU_MIPI1_CLR_IND_IMI_UNION */
#define BBPCOMM_CPU_MIPI1_CLR_IND_IMI_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0x7F4)

/* 寄存器说明：寄存器
   详      述：由软件直接控制MIPI2 master,不借助xbbp发送回读指令时,回读指令存放低32bit.
   UNION结构 ：无 */
#define BBPCOMM_MIPI2_RD_DATA_LOW_SOFT_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0x800)

/* 寄存器说明：寄存器
   详      述：由软件直接控制MIPI2 master,不借助xbbp发送回读指令时,回读指令存放高32bit.
   UNION结构 ：无 */
#define BBPCOMM_MIPI2_RD_DATA_HIGH_SOFT_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0x804)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      由软件直接控制MIPI2 master,不借助xbbp发送回读指令时,回读数据有效指示
   UNION结构:  BBPCOMM_RD_END_FLAG_MIPI2_SOFT_UNION */
#define BBPCOMM_RD_END_FLAG_MIPI2_SOFT_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0x808)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      由软件直接控制MIPI2 master
             1:软件可以发送CFG_IND启动mipi0
             0:软件等待mipi2授权使用
   UNION结构:  BBPCOMM_MIPI2_GRANT_DSP_UNION */
#define BBPCOMM_MIPI2_GRANT_DSP_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0x80C)

/* 寄存器说明：寄存器
   详      述：由软件直接控制MIPI2 master,不借助xbbp发送写指令时,写指令低32bit。
               在MIPI动态使能mipi_dyn_exchg_en有效时，MIPI扩展指令时，dsp_mipi2_wdata_low[1：0]应配置为0x2
   UNION结构 ：无 */
#define BBPCOMM_DSP_MIPI2_WDATA_LOW_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x810)

/* 寄存器说明：寄存器
   详      述：由软件直接控制MIPI2 master,不借助xbbp发送写指令时,写指令高32bit。
               在MIPI动态使能mipi_dyn_exchg_en有效，MIPI非扩展指令时，dsp_mipi2_wdata_high[1：0]应配置为:0x2
   UNION结构 ：无 */
#define BBPCOMM_DSP_MIPI2_WDATA_HIGH_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x814)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      由软件直接控制MIPI2 master,需首先拉高此指示,屏蔽xbbp对MIPI0的控制
   UNION结构:  BBPCOMM_DSP_MIPI2_EN_IMI_UNION */
#define BBPCOMM_DSP_MIPI2_EN_IMI_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x818)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      由软件直接控制MIPI2 master,拉高此dsp_mipi0_en后,产生软件启动脉冲
   UNION结构:  BBPCOMM_DSP_MIPI2_CFG_IND_IMI_UNION */
#define BBPCOMM_DSP_MIPI2_CFG_IND_IMI_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0x81C)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      由软件直接控制MIPI2 master,取走回读数据后,清标志位脉冲
   UNION结构:  BBPCOMM_DSP_MIPI2_RD_CLR_UNION */
#define BBPCOMM_DSP_MIPI2_RD_CLR_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x820)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      cpu配置mipi功能,配置为1才能正常工作, 测试时配置为0
   UNION结构:  BBPCOMM_CPU_MIPI2_FUNC_SEL_UNION */
#define BBPCOMM_CPU_MIPI2_FUNC_SEL_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x824)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      cpu配置mipi功能,测试用
   UNION结构:  BBPCOMM_CPU_MIPI2_TEST_FUNC_UNION */
#define BBPCOMM_CPU_MIPI2_TEST_FUNC_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x828)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      cpu配置mipi功能, 测试用
   UNION结构:  BBPCOMM_CPU_MIPI2_SCLK_TEST_UNION */
#define BBPCOMM_CPU_MIPI2_SCLK_TEST_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x82C)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      cpu配置mipi功能, 测试用
   UNION结构:  BBPCOMM_CPU_MIPI2_SDATA_TEST_UNION */
#define BBPCOMM_CPU_MIPI2_SDATA_TEST_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x830)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      cpu配置mipi功能,mipi2master清异常信号
   UNION结构:  BBPCOMM_CPU_MIPI2_CLR_IND_IMI_UNION */
#define BBPCOMM_CPU_MIPI2_CLR_IND_IMI_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0x834)

/* 寄存器说明：寄存器
   详      述：由软件直接控制MIPI3 master,不借助xbbp发送回读指令时,回读指令存放低32bit.
   UNION结构 ：无 */
#define BBPCOMM_MIPI3_RD_DATA_LOW_SOFT_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0x840)

/* 寄存器说明：寄存器
   详      述：由软件直接控制MIPI3 master,不借助xbbp发送回读指令时,回读指令存放高32bit.
   UNION结构 ：无 */
#define BBPCOMM_MIPI3_RD_DATA_HIGH_SOFT_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0x844)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      由软件直接控制MIPI3 master,不借助xbbp发送回读指令时,回读数据有效指示
   UNION结构:  BBPCOMM_RD_END_FLAG_MIPI3_SOFT_UNION */
#define BBPCOMM_RD_END_FLAG_MIPI3_SOFT_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0x848)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      由软件直接控制MIPI3 master
             1:软件可以发送CFG_IND启动mipi3
             0:软件等待mipi3授权使用
   UNION结构:  BBPCOMM_MIPI3_GRANT_DSP_UNION */
#define BBPCOMM_MIPI3_GRANT_DSP_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0x84C)

/* 寄存器说明：寄存器
   详      述：由软件直接控制MIPI3 master,不借助xbbp发送写指令时,写指令低32bit。
               在MIPI动态使能mipi_dyn_exchg_en有效时，MIPI扩展指令时，dsp_mipi0_wdata_low[1:0]应配置为3
   UNION结构 ：无 */
#define BBPCOMM_DSP_MIPI3_WDATA_LOW_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x850)

/* 寄存器说明：寄存器
   详      述：由软件直接控制MIPI0 master,不借助xbbp发送写指令时,写指令高32bit。
               在MIPI动态使能mipi_dyn_exchg_en有效，MIPI非扩展指令时，dsp_mipi0_wdata_high[1:0]应配置为3
   UNION结构 ：无 */
#define BBPCOMM_DSP_MIPI3_WDATA_HIGH_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x854)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      由软件直接控制MIPI3 master,需首先拉高此指示,屏蔽xbbp对MIPI3的控制
   UNION结构:  BBPCOMM_DSP_MIPI3_EN_IMI_UNION */
#define BBPCOMM_DSP_MIPI3_EN_IMI_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x858)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      由软件直接控制MIPI3 master,拉高此dsp_mipi3_en后,产生软件启动脉冲
   UNION结构:  BBPCOMM_DSP_MIPI3_CFG_IND_IMI_UNION */
#define BBPCOMM_DSP_MIPI3_CFG_IND_IMI_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0x85C)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      由软件直接控制MIPI3 master,取走回读数据后,清标志位脉冲
   UNION结构:  BBPCOMM_DSP_MIPI3_RD_CLR_UNION */
#define BBPCOMM_DSP_MIPI3_RD_CLR_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x860)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      cpu配置mipi功能,配置为1才能正常工作, 测试时配置为0
   UNION结构:  BBPCOMM_CPU_MIPI3_FUNC_SEL_UNION */
#define BBPCOMM_CPU_MIPI3_FUNC_SEL_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x864)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      cpu配置mipi功能,测试用
   UNION结构:  BBPCOMM_CPU_MIPI3_TEST_FUNC_UNION */
#define BBPCOMM_CPU_MIPI3_TEST_FUNC_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x868)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      cpu配置mipi功能, 测试用
   UNION结构:  BBPCOMM_CPU_MIPI3_SCLK_TEST_UNION */
#define BBPCOMM_CPU_MIPI3_SCLK_TEST_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x86C)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      cpu配置mipi功能, 测试用
   UNION结构:  BBPCOMM_CPU_MIPI3_SDATA_TEST_UNION */
#define BBPCOMM_CPU_MIPI3_SDATA_TEST_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x870)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      cpu配置mipi功能,mipi3master清异常信号
   UNION结构:  BBPCOMM_CPU_MIPI3_CLR_IND_IMI_UNION */
#define BBPCOMM_CPU_MIPI3_CLR_IND_IMI_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0x874)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      DSP等待回读结果超时标志位
             1:超时  
   UNION结构:  BBPCOMM_GM_MIPI_RD_OVERTIME_FLAG_DSP_UNION */
#define BBPCOMM_GM_MIPI_RD_OVERTIME_FLAG_DSP_ADDR     (SOC_BBP_COMM_BASE_ADDR + 0x900)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      DSP等待回读结果超时标志位
             1:超时  
   UNION结构:  BBPCOMM_GM_SSI_RD_OVERTIME_FLAG_DSP_UNION */
#define BBPCOMM_GM_SSI_RD_OVERTIME_FLAG_DSP_ADDR      (SOC_BBP_COMM_BASE_ADDR + 0x904)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      DSP等待回读结果超时后,清抄时标志位脉冲
   UNION结构:  BBPCOMM_GM_MIPI_RD_OVERTIME_CLR_UNION */
#define BBPCOMM_GM_MIPI_RD_OVERTIME_CLR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0x908)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      DSP等待回读结果超时后,清抄时标志位脉冲
   UNION结构:  BBPCOMM_GM_SSI_RD_OVERTIME_CLR_UNION */
#define BBPCOMM_GM_SSI_RD_OVERTIME_CLR_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0x90C)

/* 寄存器说明：寄存器
   详      述：xbbp向SSI0 master发出回读类指令时,DSP读取SSI回读结果,回读结果放置在此16寄存器位置由dsp配置,回读数据是否有效参考标志位
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GM_RFIC_1_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x910)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GM_RFIC_2_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x914)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GM_RFIC_3_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x918)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GM_RFIC_4_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x91C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GM_RFIC_5_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x920)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GM_RFIC_6_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x924)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GM_RFIC_7_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x928)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GM_RFIC_8_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x92C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GM_RFIC_9_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x930)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GM_RFIC_10_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x934)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GM_RFIC_11_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x938)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GM_RFIC_12_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x93C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GM_RFIC_13_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x940)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GM_RFIC_14_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x944)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GM_RFIC_15_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x948)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GM_RFIC_16_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x94C)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      所有回读指令执行完毕,可以取走回读数据
             1:所有回读指令发送完毕,DSP可以按位置读取SSI回读结果
   UNION结构:  BBPCOMM_RD_RESULT_FLAG_GM_RFIC_UNION */
#define BBPCOMM_RD_RESULT_FLAG_GM_RFIC_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0x950)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      1:DSP取走所有回读数据后,写入clr信号清标志位
   UNION结构:  BBPCOMM_RD_RESULT_FLAG_GM_RFIC_CLR_UNION */
#define BBPCOMM_RD_RESULT_FLAG_GM_RFIC_CLR_ADDR       (SOC_BBP_COMM_BASE_ADDR + 0x954)

/* 寄存器说明：寄存器
   详      述：xbbp向MIPI0 master发出回读类指令时,DSP读取MIPI回读结果,回读结果放置在此16寄存器位置由dsp配置,回读数据是否有效参考标志位
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GM_MIPI_1_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x958)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GM_MIPI_2_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x95C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GM_MIPI_3_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x960)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GM_MIPI_4_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x964)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GM_MIPI_5_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x968)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GM_MIPI_6_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x96C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GM_MIPI_7_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x970)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GM_MIPI_8_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x974)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GM_MIPI_9_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x978)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GM_MIPI_10_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x97C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GM_MIPI_11_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x980)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GM_MIPI_12_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x984)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GM_MIPI_13_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x988)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GM_MIPI_14_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x98C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GM_MIPI_15_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x990)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GM_MIPI_16_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x994)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      所有回读指令执行完毕,可以取走回读数据
             1:所有回读指令发送完毕,DSP可以按位置读取MIPI回读结果,与下述的软件直接控制MIPI标志位不同
   UNION结构:  BBPCOMM_RD_RESULT_FLAG_GM_MIPI_UNION */
#define BBPCOMM_RD_RESULT_FLAG_GM_MIPI_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0x998)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      1:DSP取走所有回读数据后,写入clr信号清标志位,与下述的软件直接控制MIPI标志位不同
   UNION结构:  BBPCOMM_RD_RESULT_FLAG_GM_MIPI_CLR_UNION */
#define BBPCOMM_RD_RESULT_FLAG_GM_MIPI_CLR_ADDR       (SOC_BBP_COMM_BASE_ADDR + 0x99C)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      DSP等待回读结果超时标志位
             1:超时  
   UNION结构:  BBPCOMM_GS_MIPI_RD_OVERTIME_FLAG_DSP_UNION */
#define BBPCOMM_GS_MIPI_RD_OVERTIME_FLAG_DSP_ADDR     (SOC_BBP_COMM_BASE_ADDR + 0xA00)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      DSP等待回读结果超时标志位
             1:超时  
   UNION结构:  BBPCOMM_GS_SSI_RD_OVERTIME_FLAG_DSP_UNION */
#define BBPCOMM_GS_SSI_RD_OVERTIME_FLAG_DSP_ADDR      (SOC_BBP_COMM_BASE_ADDR + 0xA04)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      DSP等待回读结果超时后,清抄时标志位脉冲
   UNION结构:  BBPCOMM_GS_MIPI_RD_OVERTIME_CLR_UNION */
#define BBPCOMM_GS_MIPI_RD_OVERTIME_CLR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xA08)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      DSP等待回读结果超时后,清抄时标志位脉冲
   UNION结构:  BBPCOMM_GS_SSI_RD_OVERTIME_CLR_UNION */
#define BBPCOMM_GS_SSI_RD_OVERTIME_CLR_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xA0C)

/* 寄存器说明：寄存器
   详      述：xbbp向SSI1 master发出回读类指令时,DSP读取SSI回读结果,回读结果放置在此16寄存器位置由dsp配置,回读数据是否有效参考标志位
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GS_RFIC_1_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xA10)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GS_RFIC_2_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xA14)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GS_RFIC_3_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xA18)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GS_RFIC_4_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xA1C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GS_RFIC_5_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xA20)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GS_RFIC_6_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xA24)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GS_RFIC_7_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xA28)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GS_RFIC_8_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xA2C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GS_RFIC_9_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xA30)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GS_RFIC_10_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0xA34)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GS_RFIC_11_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0xA38)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GS_RFIC_12_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0xA3C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GS_RFIC_13_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0xA40)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GS_RFIC_14_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0xA44)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GS_RFIC_15_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0xA48)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GS_RFIC_16_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0xA4C)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      所有回读指令执行完毕,可以取走回读数据
             1:所有回读指令发送完毕,DSP可以按位置读取SSI回读结果
   UNION结构:  BBPCOMM_RD_RESULT_FLAG_GS_RFIC_UNION */
#define BBPCOMM_RD_RESULT_FLAG_GS_RFIC_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xA50)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      1:DSP取走所有回读数据后,写入clr信号清标志位
   UNION结构:  BBPCOMM_RD_RESULT_FLAG_GS_RFIC_CLR_UNION */
#define BBPCOMM_RD_RESULT_FLAG_GS_RFIC_CLR_ADDR       (SOC_BBP_COMM_BASE_ADDR + 0xA54)

/* 寄存器说明：寄存器
   详      述：xbbp向MIPI1 master发出回读类指令时,DSP读取MIPI回读结果,回读结果放置在此16寄存器位置由dsp配置
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GS_MIPI_1_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xA58)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GS_MIPI_2_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xA5C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GS_MIPI_3_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xA60)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GS_MIPI_4_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xA64)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GS_MIPI_5_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xA68)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GS_MIPI_6_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xA6C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GS_MIPI_7_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xA70)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GS_MIPI_8_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xA74)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GS_MIPI_9_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xA78)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GS_MIPI_10_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0xA7C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GS_MIPI_11_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0xA80)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GS_MIPI_12_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0xA84)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GS_MIPI_13_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0xA88)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GS_MIPI_14_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0xA8C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GS_MIPI_15_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0xA90)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_GS_MIPI_16_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0xA94)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      所有回读指令执行完毕,可以取走回读数据
             1:所有回读指令发送完毕,DSP可以按位置读取MIPI回读结果,与下述的软件直接控制MIPI标志位不同
   UNION结构:  BBPCOMM_RD_RESULT_FLAG_GS_MIPI_UNION */
#define BBPCOMM_RD_RESULT_FLAG_GS_MIPI_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xA98)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      1:DSP取走所有回读数据后,写入clr信号清标志位,与下述的软件直接控制MIPI标志位不同
   UNION结构:  BBPCOMM_RD_RESULT_FLAG_GS_MIPI_CLR_UNION */
#define BBPCOMM_RD_RESULT_FLAG_GS_MIPI_CLR_ADDR       (SOC_BBP_COMM_BASE_ADDR + 0xA9C)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      DSP等待回读结果超时标志位
             1:超时  
   UNION结构:  BBPCOMM_W_MIPI_RD_OVERTIME_FLAG_DSP_UNION */
#define BBPCOMM_W_MIPI_RD_OVERTIME_FLAG_DSP_ADDR      (SOC_BBP_COMM_BASE_ADDR + 0xB00)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      DSP等待回读结果超时标志位
             1:超时  
   UNION结构:  BBPCOMM_W_SSI_RD_OVERTIME_FLAG_DSP_UNION */
#define BBPCOMM_W_SSI_RD_OVERTIME_FLAG_DSP_ADDR       (SOC_BBP_COMM_BASE_ADDR + 0xB04)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      DSP等待回读结果超时后,清抄时标志位脉冲
   UNION结构:  BBPCOMM_W_MIPI_RD_OVERTIME_CLR_UNION */
#define BBPCOMM_W_MIPI_RD_OVERTIME_CLR_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xB08)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      DSP等待回读结果超时后,清抄时标志位脉冲
   UNION结构:  BBPCOMM_W_SSI_RD_OVERTIME_CLR_UNION */
#define BBPCOMM_W_SSI_RD_OVERTIME_CLR_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xB0C)

/* 寄存器说明：寄存器
   详      述：xbbp向SSI2 master发出回读类指令时,DSP读取SSI回读结果,回读结果放置在此16寄存器位置由dsp配置,回读数据是否有效参考标志位
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_W_RFIC_1_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xB10)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_W_RFIC_2_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xB14)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_W_RFIC_3_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xB18)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_W_RFIC_4_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xB1C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_W_RFIC_5_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xB20)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_W_RFIC_6_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xB24)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_W_RFIC_7_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xB28)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_W_RFIC_8_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xB2C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_W_RFIC_9_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xB30)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_W_RFIC_10_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xB34)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_W_RFIC_11_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xB38)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_W_RFIC_12_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xB3C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_W_RFIC_13_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xB40)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_W_RFIC_14_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xB44)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_W_RFIC_15_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xB48)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_W_RFIC_16_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xB4C)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      所有回读指令执行完毕,可以取走回读数据
             1:所有回读指令发送完毕,DSP可以按位置读取SSI回读结果
   UNION结构:  BBPCOMM_RD_RESULT_FLAG_W_RFIC_UNION */
#define BBPCOMM_RD_RESULT_FLAG_W_RFIC_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xB50)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      1:DSP取走所有回读数据后,写入clr信号清标志位
   UNION结构:  BBPCOMM_RD_RESULT_FLAG_W_RFIC_CLR_UNION */
#define BBPCOMM_RD_RESULT_FLAG_W_RFIC_CLR_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0xB54)

/* 寄存器说明：寄存器
   详      述：xbbp向MIPI2 master发出回读类指令时,DSP读取MIPI回读结果,回读结果放置在此16寄存器位置由dsp配置,回读数据是否有效参考标志位
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_W_MIPI_1_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xB58)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_W_MIPI_2_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xB5C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_W_MIPI_3_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xB60)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_W_MIPI_4_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xB64)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_W_MIPI_5_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xB68)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_W_MIPI_6_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xB6C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_W_MIPI_7_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xB70)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_W_MIPI_8_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xB74)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_W_MIPI_9_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xB78)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_W_MIPI_10_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xB7C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_W_MIPI_11_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xB80)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_W_MIPI_12_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xB84)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_W_MIPI_13_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xB88)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_W_MIPI_14_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xB8C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_W_MIPI_15_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xB90)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_W_MIPI_16_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xB94)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      所有回读指令执行完毕,可以取走回读数据
             1:所有回读指令发送完毕,DSP可以按位置读取MIPI回读结果,与下述的软件直接控制MIPI标志位不同
   UNION结构:  BBPCOMM_RD_RESULT_FLAG_W_MIPI_UNION */
#define BBPCOMM_RD_RESULT_FLAG_W_MIPI_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xB98)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      1:DSP取走所有回读数据后,写入clr信号清标志位,与下述的软件直接控制MIPI标志位不同
   UNION结构:  BBPCOMM_RD_RESULT_FLAG_W_MIPI_CLR_UNION */
#define BBPCOMM_RD_RESULT_FLAG_W_MIPI_CLR_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0xB9C)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      DSP等待回读结果超时标志位
             1:超时  
   UNION结构:  BBPCOMM_T_MIPI_RD_OVERTIME_FLAG_DSP_UNION */
#define BBPCOMM_T_MIPI_RD_OVERTIME_FLAG_DSP_ADDR      (SOC_BBP_COMM_BASE_ADDR + 0xC00)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      DSP等待回读结果超时标志位
             1:超时  
   UNION结构:  BBPCOMM_T_SSI_RD_OVERTIME_FLAG_DSP_UNION */
#define BBPCOMM_T_SSI_RD_OVERTIME_FLAG_DSP_ADDR       (SOC_BBP_COMM_BASE_ADDR + 0xC04)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      DSP等待回读结果超时后,清抄时标志位脉冲
   UNION结构:  BBPCOMM_T_MIPI_RD_OVERTIME_CLR_UNION */
#define BBPCOMM_T_MIPI_RD_OVERTIME_CLR_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xC08)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      DSP等待回读结果超时后,清抄时标志位脉冲
   UNION结构:  BBPCOMM_T_SSI_RD_OVERTIME_CLR_UNION */
#define BBPCOMM_T_SSI_RD_OVERTIME_CLR_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC0C)

/* 寄存器说明：寄存器
   详      述：xbbp向SSI3 master发出回读类指令时,DSP读取SSI回读结果,回读结果放置在此16寄存器位置由dsp配置,回读数据是否有效参考标志位
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_T_RFIC_1_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC10)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_T_RFIC_2_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC14)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_T_RFIC_3_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC18)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_T_RFIC_4_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC1C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_T_RFIC_5_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC20)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_T_RFIC_6_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC24)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_T_RFIC_7_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC28)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_T_RFIC_8_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC2C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_T_RFIC_9_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC30)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_T_RFIC_10_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xC34)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_T_RFIC_11_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xC38)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_T_RFIC_12_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xC3C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_T_RFIC_13_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xC40)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_T_RFIC_14_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xC44)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_T_RFIC_15_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xC48)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_T_RFIC_16_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xC4C)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      所有回读指令执行完毕,可以取走回读数据
             1:所有回读指令发送完毕,DSP可以按位置读取SSI回读结果
   UNION结构:  BBPCOMM_RD_RESULT_FLAG_T_RFIC_UNION */
#define BBPCOMM_RD_RESULT_FLAG_T_RFIC_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC50)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      1:DSP取走所有回读数据后,写入clr信号清标志位
   UNION结构:  BBPCOMM_RD_RESULT_FLAG_T_RFIC_CLR_UNION */
#define BBPCOMM_RD_RESULT_FLAG_T_RFIC_CLR_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0xC54)

/* 寄存器说明：寄存器
   详      述：xbbp向MIPI3 master发出回读类指令时,DSP读取MIPI回读结果,回读结果放置在此16寄存器位置由dsp配置,回读数据是否有效参考标志位
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_T_MIPI_1_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC58)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_T_MIPI_2_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC5C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_T_MIPI_3_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC60)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_T_MIPI_4_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC64)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_T_MIPI_5_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC68)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_T_MIPI_6_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC6C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_T_MIPI_7_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC70)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_T_MIPI_8_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC74)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_T_MIPI_9_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC78)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_T_MIPI_10_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xC7C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_T_MIPI_11_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xC80)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_T_MIPI_12_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xC84)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_T_MIPI_13_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xC88)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_T_MIPI_14_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xC8C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_T_MIPI_15_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xC90)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_T_MIPI_16_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xC94)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      所有回读指令执行完毕,可以取走回读数据
             1:所有回读指令发送完毕,DSP可以按位置读取MIPI回读结果,与下述的软件直接控制MIPI标志位不同
   UNION结构:  BBPCOMM_RD_RESULT_FLAG_T_MIPI_UNION */
#define BBPCOMM_RD_RESULT_FLAG_T_MIPI_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC98)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      1:DSP取走所有回读数据后,写入clr信号清标志位,与下述的软件直接控制MIPI标志位不同
   UNION结构:  BBPCOMM_RD_RESULT_FLAG_T_MIPI_CLR_UNION */
#define BBPCOMM_RD_RESULT_FLAG_T_MIPI_CLR_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0xC9C)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      DSP等待回读结果超时标志位
             1:超时  
   UNION结构:  BBPCOMM_C_MIPI_RD_OVERTIME_FLAG_DSP_UNION */
#define BBPCOMM_C_MIPI_RD_OVERTIME_FLAG_DSP_ADDR      (SOC_BBP_COMM_BASE_ADDR + 0xD00)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      DSP等待回读结果超时标志位
             1:超时  
   UNION结构:  BBPCOMM_C_SSI_RD_OVERTIME_FLAG_DSP_UNION */
#define BBPCOMM_C_SSI_RD_OVERTIME_FLAG_DSP_ADDR       (SOC_BBP_COMM_BASE_ADDR + 0xD04)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      DSP等待回读结果超时后,清抄时标志位脉冲
   UNION结构:  BBPCOMM_C_MIPI_RD_OVERTIME_CLR_UNION */
#define BBPCOMM_C_MIPI_RD_OVERTIME_CLR_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xD08)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      DSP等待回读结果超时后,清抄时标志位脉冲
   UNION结构:  BBPCOMM_C_SSI_RD_OVERTIME_CLR_UNION */
#define BBPCOMM_C_SSI_RD_OVERTIME_CLR_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xD0C)

/* 寄存器说明：寄存器
   详      述：xbbp向SSI3 master发出回读类指令时,DSP读取SSI回读结果,回读结果放置在此16寄存器位置由dsp配置,回读数据是否有效参考标志位
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_C_RFIC_1_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xD10)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_C_RFIC_2_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xD14)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_C_RFIC_3_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xD18)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_C_RFIC_4_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xD1C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_C_RFIC_5_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xD20)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_C_RFIC_6_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xD24)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_C_RFIC_7_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xD28)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_C_RFIC_8_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xD2C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_C_RFIC_9_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xD30)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_C_RFIC_10_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xD34)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_C_RFIC_11_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xD38)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_C_RFIC_12_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xD3C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_C_RFIC_13_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xD40)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_C_RFIC_14_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xD44)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_C_RFIC_15_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xD48)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_C_RFIC_16_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xD4C)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      所有回读指令执行完毕,可以取走回读数据
             1:所有回读指令发送完毕,DSP可以按位置读取SSI回读结果
   UNION结构:  BBPCOMM_RD_RESULT_FLAG_C_RFIC_UNION */
#define BBPCOMM_RD_RESULT_FLAG_C_RFIC_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xD50)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      1:DSP取走所有回读数据后,写入clr信号清标志位
   UNION结构:  BBPCOMM_RD_RESULT_FLAG_C_RFIC_CLR_UNION */
#define BBPCOMM_RD_RESULT_FLAG_C_RFIC_CLR_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0xD54)

/* 寄存器说明：寄存器
   详      述：xbbp向MIPI3 master发出回读类指令时,DSP读取MIPI回读结果,回读结果放置在此16寄存器位置由dsp配置,回读数据是否有效参考标志位
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_C_MIPI_1_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xD58)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_C_MIPI_2_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xD5C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_C_MIPI_3_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xD60)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_C_MIPI_4_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xD64)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_C_MIPI_5_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xD68)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_C_MIPI_6_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xD6C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_C_MIPI_7_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xD70)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_C_MIPI_8_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xD74)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_C_MIPI_9_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xD78)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_C_MIPI_10_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xD7C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_C_MIPI_11_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xD80)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_C_MIPI_12_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xD84)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_C_MIPI_13_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xD88)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_C_MIPI_14_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xD8C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_C_MIPI_15_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xD90)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_C_MIPI_16_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xD94)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      所有回读指令执行完毕,可以取走回读数据
             1:所有回读指令发送完毕,DSP可以按位置读取MIPI回读结果,与下述的软件直接控制MIPI标志位不同
   UNION结构:  BBPCOMM_RD_RESULT_FLAG_C_MIPI_UNION */
#define BBPCOMM_RD_RESULT_FLAG_C_MIPI_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xD98)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      1:DSP取走所有回读数据后,写入clr信号清标志位,与下述的软件直接控制MIPI标志位不同
   UNION结构:  BBPCOMM_RD_RESULT_FLAG_C_MIPI_CLR_UNION */
#define BBPCOMM_RD_RESULT_FLAG_C_MIPI_CLR_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0xD9C)

/* 寄存器说明：寄存器
   详      述：用于提供w的复帧号，由wDSP更新。
               配置时刻：
               生效时刻：触发后检测o_timing_valid1为1有效。
   UNION结构 ：无 */
#define BBPCOMM_W_MUX_FRAME_NUM1_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0xCA0)

/* 寄存器说明：寄存器
 bit[31:6]   保留
 bit[5:4]    上报c2模的计数器给ARM的是1x、evdo还是base_cnt
             00：1x定时
             01： evdo定时
             10： basecent
 bit[3:1]    保留
 bit[0]      定时上报有效标志，高有效。
             ARM配置timing_get_ind后，查询此标志，如果为高，则可以获取LTE，W，Gm，Gs, TDS的系统定时。
             DSP读取定时，在DSP下次启动新的timing_get_ind时拉低此信号。
             
             
   UNION结构:  BBPCOMM_TIMING_VALID1_UNION */
#define BBPCOMM_TIMING_VALID1_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0xCA4)

/* 寄存器说明：寄存器
 bit[31:20]  ARM读取W的系统定时信息，由DSP 配置timing_get_ind触发上报。
             上报时刻：触发后检测o_timing_valid1为1有效。
             [31:20]表示W的SFN计数（源自w_timing_b[11:0]），范围0~4095。
 bit[19:16]  [19:16]为时隙计数，范围0~14
 bit[15:4]   [15:4]为时隙内chip计数，范围0~2559
 bit[3:0]    [3:0]为chip内时钟计数，范围0~15
   UNION结构:  BBPCOMM_W_TIMING_DSP1_UNION */
#define BBPCOMM_W_TIMING_DSP1_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0xCAC)

/* 寄存器说明：寄存器
   详      述：用于提供w的复帧号，由ARM配置timing_get_ind触发上报。上报时刻：触发后检测o_timing_valid1为1有效。
   UNION结构 ：无 */
#define BBPCOMM_W_MUX_FRAME_NUM_BBP1_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0xCB0)

/* 寄存器说明：寄存器
 bit[31:22]  保留
 bit[21:0]   GM的FN计数（源自gm_timing_a[21:0]），由ARM配置timing_get_ind触发上报。其中[10:0]表示fn_low,范围0~1325；[21:11]表示fn_hign,范围0~2047。
             上报时刻：触发后立即生效
   UNION结构:  BBPCOMM_GM_FN_DSP1_UNION */
#define BBPCOMM_GM_FN_DSP1_ADDR                       (SOC_BBP_COMM_BASE_ADDR + 0xCB4)

/* 寄存器说明：寄存器
 bit[31:13]  保留
 bit[12:0]   GM的系统定时Qb信息，由ARM配置timing_get_ind触发上报。
              [12:0]表示 G系统定时帧内Qb计数（源自gm_timing_b[12:0]），范围0~4999。
             上报时刻：触发后立即生效
   UNION结构:  BBPCOMM_GM_QB_DSP1_UNION */
#define BBPCOMM_GM_QB_DSP1_ADDR                       (SOC_BBP_COMM_BASE_ADDR + 0xCB8)

/* 寄存器说明：寄存器
   详      述：用于提供gm的复帧号，由gmDSP更新。
               配置时刻：
               生效时刻：触发后检测o_timing_valid1为1有效。
   UNION结构 ：无 */
#define BBPCOMM_GM_MUX_FRAME_NUM1_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xCBC)

/* 寄存器说明：寄存器
 bit[31:22]  保留
 bit[21:0]   GS的FN计数（源自gs_timing_a[21:0]），由ARM配置timing_get_ind触发上报。其中[10:0]表示fn_low,范围0~1325；[21:11]表示fn_hign,范围0~2047。
             上报时刻：触发后立即生效
   UNION结构:  BBPCOMM_GS_FN_DSP1_UNION */
#define BBPCOMM_GS_FN_DSP1_ADDR                       (SOC_BBP_COMM_BASE_ADDR + 0xCD0)

/* 寄存器说明：寄存器
 bit[31:13]  保留
 bit[12:0]   GS的系统定时Qb信息，由ARM配置timing_get_ind触发上报。
              [12:0]表示 GS系统定时帧内Qb计数（源自gs_timing_b[12:0]），范围0~4999。
             上报时刻：触发后立即生效
   UNION结构:  BBPCOMM_GS_QB_DSP1_UNION */
#define BBPCOMM_GS_QB_DSP1_ADDR                       (SOC_BBP_COMM_BASE_ADDR + 0xCD4)

/* 寄存器说明：寄存器
   详      述：用于提供gs的复帧号，由gsDSP更新。
               配置时刻：
               生效时刻：触发后检测o_timing_valid1为1有效。
   UNION结构 ：无 */
#define BBPCOMM_GS_MUX_FRAME_NUM1_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xCD8)

/* 寄存器说明：寄存器
 bit[31:30]  保留
 bit[29:20]  LTE的系统定时。由ARM配置timing_get_ind触发上报。
             上报时刻：触发后立即生效
             其中:
             [29:20]表示SFN计数，范围0~1023
 bit[19:16]  [19:16]是子帧计数
 bit[15:15]  保留
 bit[14:0]   [14:0]是子帧内计数。 
   UNION结构:  BBPCOMM_LTE_TIMING_DSP1_UNION */
#define BBPCOMM_LTE_TIMING_DSP1_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0xCDC)

/* 寄存器说明：寄存器
   详      述：用于提供LTE的复帧号。由ARM配置timing_get_ind触发上报。
               上报时刻：触发后检测o_timing_valid1为1有效。
   UNION结构 ：无 */
#define BBPCOMM_LTE_MUX_FRAME_NUM1_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xCE0)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   TDS的系统定时。由ARM配置timing_get_ind触发上报。本寄存器上报的是TDS的tcfsr系统子帧号0~65535循环计数，TDS实际有效子帧范围为0~8191
             上报时刻：触发后立即生效
   UNION结构:  BBPCOMM_TDS_TIMING1_DSP1_UNION */
#define BBPCOMM_TDS_TIMING1_DSP1_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0xCE4)

/* 寄存器说明：寄存器
 bit[31:20]  保留
 bit[19:0]   TDS的系统定时。由ARM配置timing_get_ind触发上报。本寄存器上报的是是TDS的framc帧计数
             上报时刻：触发后立即生效
   UNION结构:  BBPCOMM_TDS_TIMING2_DSP1_UNION */
#define BBPCOMM_TDS_TIMING2_DSP1_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0xCE8)

/* 寄存器说明：寄存器
   详      述：用于提供LTE的复帧号。由ARM配置timing_get_ind触发上报。
               上报时刻：触发后检测o_timing_valid1为1有效。
   UNION结构 ：无 */
#define BBPCOMM_TDS_MUX_FRAME_NUM1_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xCEC)

/* 寄存器说明：寄存器
 bit[31:30]  保留
 bit[29:0]   C2模定时信息上报。 
             C2模定时信息上报。 
             1X模式：
             Bit[4:0]   1/4chip     计数范围0~24  
             Bit[6:5]   chip        计数范围0~3
             Bit[17:7]  chip number 计数范围0~1535
             Bit[23:18] 80ms        计数范围0~63
             Bit[29:24] 2s/5.12s超帧计数范围0~24/0~63
             EVDO：
             Bit[4:0]   1/4chip     计数范围0~24  Bit[6:5]   chip        计数范围0~3
             Bit[21:7]  chip number 计数范围0~32767
             Bit[23:22] 80ms        计数范围0~63
             Bit[29:24] 2s/5.12s超帧计数范围0~24/0~63
             BASE_CNT：
             Bit[4:0]   1/4chip     计数范围0~24  
             Bit[6:5]   chip        计数范围0~3
             Bit[21:7]  chip number 计数范围0~32767
             Bit[23:22]  80ms       计数范围0~63
             Bit[28:24]  2s超帧     计数范围0~24
   UNION结构:  BBPCOMM_C_TIMING_DSP1_UNION */
#define BBPCOMM_C_TIMING_DSP1_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0xCF0)

/* 寄存器说明：寄存器
   详      述：CTU内部定时，由ARM配置timing_get_ind1触发上报。计数器使用clk_19m_bbp_soc时钟,32比特计满再从头开始计数
               上报时刻：触发后检测o_timing_valid1为1有效。
   UNION结构 ：无 */
#define BBPCOMM_CTU_TIMING_DSP1_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0xCF4)

/* 寄存器说明：寄存器
   详      述：32K公共定时器的定时信息，由ARM配置timing_get_ind1触发上报。32比特计数计满后再从头开始计数。
               上报时刻：触发后检测o_timing_valid1为1有效。
   UNION结构 ：无 */
#define BBPCOMM_COMM_32K_TIMING_RPT2_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0xCF8)

/* 寄存器说明：寄存器
   详      述：用于提供w的复帧号，由wDSP更新。
               配置时刻：
               生效时刻：触发后检测o_timing_valid2为1有效。
   UNION结构 ：无 */
#define BBPCOMM_W_MUX_FRAME_NUM2_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0xEA0)

/* 寄存器说明：寄存器
 bit[31:6]   保留
 bit[5:4]    上报c2模的计数器给C模BBE16 DSP的是1x、evdo还是base_cnt
             00：1x定时
             01： evdo定时
             10： basecent
 bit[3:1]    保留
 bit[0]      定时上报有效标志，高有效。
             C模BBE16 DSP配置timing_get_ind后，查询此标志，如果为高，则可以获取LTE，W，Gm，Gs, TDS的系统定时。
             DSP读取定时，在DSP下次启动新的timing_get_ind时拉低此信号。
             
             
   UNION结构:  BBPCOMM_TIMING_VALID2_UNION */
#define BBPCOMM_TIMING_VALID2_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0xEA4)

/* 寄存器说明：寄存器
 bit[31:20]  C模BBE16 DSP读取W的系统定时信息，由DSP 配置timing_get_ind触发上报。
             上报时刻：触发后检测o_timing_valid2为1有效。
             [31:20]表示W的SFN计数（源自w_timing_b[11:0]），范围0~4095。
 bit[19:16]  [19:16]为时隙计数，范围0~14
 bit[15:4]   [15:4]为时隙内chip计数，范围0~2559
 bit[3:0]    [3:0]为chip内时钟计数，范围0~15
   UNION结构:  BBPCOMM_W_TIMING_DSP2_UNION */
#define BBPCOMM_W_TIMING_DSP2_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0xEA8)

/* 寄存器说明：寄存器
   详      述：用于提供w的复帧号，由C模BBE16 DSP配置timing_get_ind触发上报。上报时刻：触发后检测o_timing_valid2为1有效。
   UNION结构 ：无 */
#define BBPCOMM_W_MUX_FRAME_NUM_BBP2_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0xEAC)

/* 寄存器说明：寄存器
 bit[31:22]  保留
 bit[21:0]   GM的FN计数（源自gm_timing_a[21:0]），由C模BBE16 DSP配置timing_get_ind触发上报。其中[10:0]表示fn_low,范围0~1325；[21:11]表示fn_hign,范围0~2047。
             上报时刻：触发后立即生效
   UNION结构:  BBPCOMM_GM_FN_DSP2_UNION */
#define BBPCOMM_GM_FN_DSP2_ADDR                       (SOC_BBP_COMM_BASE_ADDR + 0xEB0)

/* 寄存器说明：寄存器
 bit[31:13]  保留
 bit[12:0]   GM的系统定时Qb信息，由C模BBE16 DSP配置timing_get_ind触发上报。
              [12:0]表示 G系统定时帧内Qb计数（源自gm_timing_b[12:0]），范围0~4999。
             上报时刻：触发后立即生效
   UNION结构:  BBPCOMM_GM_QB_DSP2_UNION */
#define BBPCOMM_GM_QB_DSP2_ADDR                       (SOC_BBP_COMM_BASE_ADDR + 0xEB4)

/* 寄存器说明：寄存器
   详      述：用于提供gm的复帧号，由gmDSP更新。
               配置时刻：
               生效时刻：触发后检测o_timing_valid2为1有效。
   UNION结构 ：无 */
#define BBPCOMM_GM_MUX_FRAME_NUM2_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xEB8)

/* 寄存器说明：寄存器
 bit[31:22]  保留
 bit[21:0]   GS的FN计数（源自gs_timing_a[21:0]），由C模BBE16 DSP配置timing_get_ind触发上报。其中[10:0]表示fn_low,范围0~1325；[21:11]表示fn_hign,范围0~2047。
             上报时刻：触发后立即生效
   UNION结构:  BBPCOMM_GS_FN_DSP2_UNION */
#define BBPCOMM_GS_FN_DSP2_ADDR                       (SOC_BBP_COMM_BASE_ADDR + 0xEBC)

/* 寄存器说明：寄存器
 bit[31:13]  保留
 bit[12:0]   GS的系统定时Qb信息，由C模BBE16 DSP配置timing_get_ind触发上报。
              [12:0]表示 GS系统定时帧内Qb计数（源自gs_timing_b[12:0]），范围0~4999。
             上报时刻：触发后立即生效
   UNION结构:  BBPCOMM_GS_QB_DSP2_UNION */
#define BBPCOMM_GS_QB_DSP2_ADDR                       (SOC_BBP_COMM_BASE_ADDR + 0xEC0)

/* 寄存器说明：寄存器
   详      述：用于提供gs的复帧号，由gsDSP更新。
               配置时刻：
               生效时刻：触发后检测o_timing_valid2为1有效。
   UNION结构 ：无 */
#define BBPCOMM_GS_MUX_FRAME_NUM2_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xEC4)

/* 寄存器说明：寄存器
 bit[31:30]  保留
 bit[29:20]  LTE的系统定时。由C模BBE16 DSP配置timing_get_ind触发上报。
             上报时刻：触发后立即生效
             其中:
             [29:20]表示SFN计数，范围0~1023
 bit[19:16]  [19:16]是子帧计数
 bit[15:15]  保留
 bit[14:0]   [14:0]是子帧内计数。 
   UNION结构:  BBPCOMM_LTE_TIMING_DSP2_UNION */
#define BBPCOMM_LTE_TIMING_DSP2_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0xEC8)

/* 寄存器说明：寄存器
   详      述：用于提供LTE的复帧号。由C模BBE16 DSP配置timing_get_ind触发上报。
               上报时刻：触发后检测o_timing_valid2为1有效。
   UNION结构 ：无 */
#define BBPCOMM_LTE_MUX_FRAME_NUM2_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xECC)

/* 寄存器说明：寄存器
 bit[31:16]  保留
 bit[15:0]   TDS的系统定时。由C模BBE16 DSP配置timing_get_ind触发上报。本寄存器上报的是TDS的tcfsr系统子帧号0~65535循环计数，TDS实际有效子帧范围为0~8191
             上报时刻：触发后立即生效
   UNION结构:  BBPCOMM_TDS_TIMING1_DSP2_UNION */
#define BBPCOMM_TDS_TIMING1_DSP2_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0xED0)

/* 寄存器说明：寄存器
 bit[31:20]  保留
 bit[19:0]   TDS的系统定时。由C模BBE16 DSP配置timing_get_ind触发上报。本寄存器上报的是是TDS的framc帧计数
             上报时刻：触发后立即生效
   UNION结构:  BBPCOMM_TDS_TIMING2_DSP2_UNION */
#define BBPCOMM_TDS_TIMING2_DSP2_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0xED4)

/* 寄存器说明：寄存器
   详      述：用于提供LTE的复帧号。由C模BBE16 DSP配置timing_get_ind触发上报。
               上报时刻：触发后检测o_timing_valid2为1有效。
   UNION结构 ：无 */
#define BBPCOMM_TDS_MUX_FRAME_NUM2_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xED8)

/* 寄存器说明：寄存器
 bit[31:30]  保留
 bit[29:0]   C2模定时信息上报。 
             C2模定时信息上报。 
             1X模式：
             Bit[4:0]   1/4chip     计数范围0~24  
             Bit[6:5]   chip        计数范围0~3
             Bit[17:7]  chip number 计数范围0~1535
             Bit[23:18] 80ms        计数范围0~63
             Bit[29:24] 2s/5.12s超帧计数范围0~24/0~63
             EVDO：
             Bit[4:0]   1/4chip     计数范围0~24  Bit[6:5]   chip        计数范围0~3
             Bit[21:7]  chip number 计数范围0~32767
             Bit[23:22] 80ms        计数范围0~63
             Bit[29:24] 2s/5.12s超帧计数范围0~24/0~63
             BASE_CNT：
             Bit[4:0]   1/4chip     计数范围0~24  
             Bit[6:5]   chip        计数范围0~3
             Bit[21:7]  chip number 计数范围0~32767
             Bit[23:22]  80ms       计数范围0~63
             Bit[28:24]  2s超帧     计数范围0~24
   UNION结构:  BBPCOMM_C_TIMING_DSP2_UNION */
#define BBPCOMM_C_TIMING_DSP2_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0xEDC)

/* 寄存器说明：寄存器
   详      述：CTU内部定时，由C模BBE16 DSP配置timing_get_ind2触发上报。计数器使用clk_19m_bbp_soc时钟,32比特计满再从头开始计数
               上报时刻：触发后检测o_timing_valid2为1有效。
   UNION结构 ：无 */
#define BBPCOMM_CTU_TIMING_DSP2_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0xEE0)

/* 寄存器说明：寄存器
   详      述：32K公共定时器的定时信息，由C模BBE16 DSP配置timing_get_ind2触发上报。32比特计数计满后再从头开始计数。
               上报时刻：触发后检测o_timing_valid2为1有效。
   UNION结构 ：无 */
#define BBPCOMM_COMM_32K_TIMING_RPT3_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0xEE4)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      DSP等待回读结果超时标志位
             1:超时  
   UNION结构:  BBPCOMM_LTE_CH0_MIPI_RD_OVERTIME_FLAG_DSP_UNION */
#define BBPCOMM_LTE_CH0_MIPI_RD_OVERTIME_FLAG_DSP_ADDR (SOC_BBP_COMM_BASE_ADDR + 0xE00)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      DSP等待回读结果超时标志位
             1:超时  
   UNION结构:  BBPCOMM_LTE_CH0_SSI_RD_OVERTIME_FLAG_DSP_UNION */
#define BBPCOMM_LTE_CH0_SSI_RD_OVERTIME_FLAG_DSP_ADDR (SOC_BBP_COMM_BASE_ADDR + 0xE04)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      DSP等待回读结果超时后,清抄时标志位脉冲
   UNION结构:  BBPCOMM_LTE_CH0_MIPI_RD_OVERTIME_CLR_UNION */
#define BBPCOMM_LTE_CH0_MIPI_RD_OVERTIME_CLR_ADDR     (SOC_BBP_COMM_BASE_ADDR + 0xE08)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      DSP等待回读结果超时后,清抄时标志位脉冲
   UNION结构:  BBPCOMM_LTE_CH0_SSI_RD_OVERTIME_CLR_UNION */
#define BBPCOMM_LTE_CH0_SSI_RD_OVERTIME_CLR_ADDR      (SOC_BBP_COMM_BASE_ADDR + 0xE0C)

/* 寄存器说明：寄存器
   详      述：xbbp向SSI3 master发出回读类指令时,DSP读取SSI回读结果,回读结果放置在此16寄存器位置由dsp配置,回读数据是否有效参考标志位
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH0_RFIC_1_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xE10)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH0_RFIC_2_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xE14)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH0_RFIC_3_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xE18)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH0_RFIC_4_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xE1C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH0_RFIC_5_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xE20)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH0_RFIC_6_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xE24)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH0_RFIC_7_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xE28)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH0_RFIC_8_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xE2C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH0_RFIC_9_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xE30)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH0_RFIC_10_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0xE34)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH0_RFIC_11_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0xE38)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH0_RFIC_12_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0xE3C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH0_RFIC_13_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0xE40)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH0_RFIC_14_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0xE44)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH0_RFIC_15_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0xE48)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH0_RFIC_16_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0xE4C)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      所有回读指令执行完毕,可以取走回读数据
             1:所有回读指令发送完毕,DSP可以按位置读取SSI回读结果
   UNION结构:  BBPCOMM_RD_RESULT_FLAG_LTE_CH0_RFIC_UNION */
#define BBPCOMM_RD_RESULT_FLAG_LTE_CH0_RFIC_ADDR      (SOC_BBP_COMM_BASE_ADDR + 0xE50)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      1:DSP取走所有回读数据后,写入clr信号清标志位
   UNION结构:  BBPCOMM_RD_RESULT_FLAG_LTE_CH0_RFIC_CLR_UNION */
#define BBPCOMM_RD_RESULT_FLAG_LTE_CH0_RFIC_CLR_ADDR  (SOC_BBP_COMM_BASE_ADDR + 0xE54)

/* 寄存器说明：寄存器
   详      述：xbbp向MIPI3 master发出回读类指令时,DSP读取MIPI回读结果,回读结果放置在此16寄存器位置由dsp配置,回读数据是否有效参考标志位
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH0_MIPI_1_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xE58)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH0_MIPI_2_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xE5C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH0_MIPI_3_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xE60)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH0_MIPI_4_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xE64)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH0_MIPI_5_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xE68)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH0_MIPI_6_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xE6C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH0_MIPI_7_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xE70)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH0_MIPI_8_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xE74)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH0_MIPI_9_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xE78)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH0_MIPI_10_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0xE7C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH0_MIPI_11_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0xE80)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH0_MIPI_12_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0xE84)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH0_MIPI_13_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0xE88)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH0_MIPI_14_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0xE8C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH0_MIPI_15_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0xE90)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH0_MIPI_16_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0xE94)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      所有回读指令执行完毕,可以取走回读数据
             1:所有回读指令发送完毕,DSP可以按位置读取MIPI回读结果,与下述的软件直接控制MIPI标志位不同
   UNION结构:  BBPCOMM_RD_RESULT_FLAG_LTE_CH0_MIPI_UNION */
#define BBPCOMM_RD_RESULT_FLAG_LTE_CH0_MIPI_ADDR      (SOC_BBP_COMM_BASE_ADDR + 0xE98)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      1:DSP取走所有回读数据后,写入clr信号清标志位,与下述的软件直接控制MIPI标志位不同
   UNION结构:  BBPCOMM_RD_RESULT_FLAG_LTE_CH0_MIPI_CLR_UNION */
#define BBPCOMM_RD_RESULT_FLAG_LTE_CH0_MIPI_CLR_ADDR  (SOC_BBP_COMM_BASE_ADDR + 0xE9C)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      DSP等待回读结果超时标志位
             1:超时  
   UNION结构:  BBPCOMM_LTE_CH1_MIPI_RD_OVERTIME_FLAG_DSP_UNION */
#define BBPCOMM_LTE_CH1_MIPI_RD_OVERTIME_FLAG_DSP_ADDR (SOC_BBP_COMM_BASE_ADDR + 0xF00)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      DSP等待回读结果超时标志位
             1:超时  
   UNION结构:  BBPCOMM_LTE_CH1_SSI_RD_OVERTIME_FLAG_DSP_UNION */
#define BBPCOMM_LTE_CH1_SSI_RD_OVERTIME_FLAG_DSP_ADDR (SOC_BBP_COMM_BASE_ADDR + 0xF04)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      DSP等待回读结果超时后,清抄时标志位脉冲
   UNION结构:  BBPCOMM_LTE_CH1_MIPI_RD_OVERTIME_CLR_UNION */
#define BBPCOMM_LTE_CH1_MIPI_RD_OVERTIME_CLR_ADDR     (SOC_BBP_COMM_BASE_ADDR + 0xF08)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      DSP等待回读结果超时后,清抄时标志位脉冲
   UNION结构:  BBPCOMM_LTE_CH1_SSI_RD_OVERTIME_CLR_UNION */
#define BBPCOMM_LTE_CH1_SSI_RD_OVERTIME_CLR_ADDR      (SOC_BBP_COMM_BASE_ADDR + 0xF0C)

/* 寄存器说明：寄存器
   详      述：xbbp向SSI3 master发出回读类指令时,DSP读取SSI回读结果,回读结果放置在此16寄存器位置由dsp配置,回读数据是否有效参考标志位
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH1_RFIC_1_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xF10)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH1_RFIC_2_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xF14)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH1_RFIC_3_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xF18)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH1_RFIC_4_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xF1C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH1_RFIC_5_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xF20)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH1_RFIC_6_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xF24)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH1_RFIC_7_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xF28)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH1_RFIC_8_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xF2C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH1_RFIC_9_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xF30)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH1_RFIC_10_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0xF34)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH1_RFIC_11_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0xF38)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH1_RFIC_12_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0xF3C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH1_RFIC_13_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0xF40)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH1_RFIC_14_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0xF44)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH1_RFIC_15_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0xF48)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH1_RFIC_16_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0xF4C)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      所有回读指令执行完毕,可以取走回读数据
             1:所有回读指令发送完毕,DSP可以按位置读取SSI回读结果
   UNION结构:  BBPCOMM_RD_RESULT_FLAG_LTE_CH1_RFIC_UNION */
#define BBPCOMM_RD_RESULT_FLAG_LTE_CH1_RFIC_ADDR      (SOC_BBP_COMM_BASE_ADDR + 0xF50)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      1:DSP取走所有回读数据后,写入clr信号清标志位
   UNION结构:  BBPCOMM_RD_RESULT_FLAG_LTE_CH1_RFIC_CLR_UNION */
#define BBPCOMM_RD_RESULT_FLAG_LTE_CH1_RFIC_CLR_ADDR  (SOC_BBP_COMM_BASE_ADDR + 0xF54)

/* 寄存器说明：寄存器
   详      述：xbbp向MIPI3 master发出回读类指令时,DSP读取MIPI回读结果,回读结果放置在此16寄存器位置由dsp配置,回读数据是否有效参考标志位
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH1_MIPI_1_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xF58)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH1_MIPI_2_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xF5C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH1_MIPI_3_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xF60)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH1_MIPI_4_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xF64)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH1_MIPI_5_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xF68)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH1_MIPI_6_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xF6C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH1_MIPI_7_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xF70)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH1_MIPI_8_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xF74)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH1_MIPI_9_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xF78)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH1_MIPI_10_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0xF7C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH1_MIPI_11_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0xF80)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH1_MIPI_12_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0xF84)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH1_MIPI_13_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0xF88)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH1_MIPI_14_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0xF8C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH1_MIPI_15_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0xF90)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH1_MIPI_16_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0xF94)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      所有回读指令执行完毕,可以取走回读数据
             1:所有回读指令发送完毕,DSP可以按位置读取MIPI回读结果,与下述的软件直接控制MIPI标志位不同
   UNION结构:  BBPCOMM_RD_RESULT_FLAG_LTE_CH1_MIPI_UNION */
#define BBPCOMM_RD_RESULT_FLAG_LTE_CH1_MIPI_ADDR      (SOC_BBP_COMM_BASE_ADDR + 0xF98)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      1:DSP取走所有回读数据后,写入clr信号清标志位,与下述的软件直接控制MIPI标志位不同
   UNION结构:  BBPCOMM_RD_RESULT_FLAG_LTE_CH1_MIPI_CLR_UNION */
#define BBPCOMM_RD_RESULT_FLAG_LTE_CH1_MIPI_CLR_ADDR  (SOC_BBP_COMM_BASE_ADDR + 0xF9C)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      DSP等待回读结果超时标志位
             1:超时  
   UNION结构:  BBPCOMM_LTE_CH2_MIPI_RD_OVERTIME_FLAG_DSP_UNION */
#define BBPCOMM_LTE_CH2_MIPI_RD_OVERTIME_FLAG_DSP_ADDR (SOC_BBP_COMM_BASE_ADDR + 0x1000)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      DSP等待回读结果超时标志位
             1:超时  
   UNION结构:  BBPCOMM_LTE_CH2_SSI_RD_OVERTIME_FLAG_DSP_UNION */
#define BBPCOMM_LTE_CH2_SSI_RD_OVERTIME_FLAG_DSP_ADDR (SOC_BBP_COMM_BASE_ADDR + 0x1004)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      DSP等待回读结果超时后,清抄时标志位脉冲
   UNION结构:  BBPCOMM_LTE_CH2_MIPI_RD_OVERTIME_CLR_UNION */
#define BBPCOMM_LTE_CH2_MIPI_RD_OVERTIME_CLR_ADDR     (SOC_BBP_COMM_BASE_ADDR + 0x1008)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      DSP等待回读结果超时后,清抄时标志位脉冲
   UNION结构:  BBPCOMM_LTE_CH2_SSI_RD_OVERTIME_CLR_UNION */
#define BBPCOMM_LTE_CH2_SSI_RD_OVERTIME_CLR_ADDR      (SOC_BBP_COMM_BASE_ADDR + 0x100C)

/* 寄存器说明：寄存器
   详      述：xbbp向SSI3 master发出回读类指令时,DSP读取SSI回读结果,回读结果放置在此16寄存器位置由dsp配置,回读数据是否有效参考标志位
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH2_RFIC_1_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x1010)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH2_RFIC_2_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x1014)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH2_RFIC_3_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x1018)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH2_RFIC_4_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x101C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH2_RFIC_5_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x1020)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH2_RFIC_6_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x1024)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH2_RFIC_7_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x1028)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH2_RFIC_8_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x102C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH2_RFIC_9_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x1030)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH2_RFIC_10_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0x1034)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH2_RFIC_11_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0x1038)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH2_RFIC_12_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0x103C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH2_RFIC_13_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0x1040)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH2_RFIC_14_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0x1044)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH2_RFIC_15_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0x1048)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH2_RFIC_16_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0x104C)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      所有回读指令执行完毕,可以取走回读数据
             1:所有回读指令发送完毕,DSP可以按位置读取SSI回读结果
   UNION结构:  BBPCOMM_RD_RESULT_FLAG_LTE_CH2_RFIC_UNION */
#define BBPCOMM_RD_RESULT_FLAG_LTE_CH2_RFIC_ADDR      (SOC_BBP_COMM_BASE_ADDR + 0x1050)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      1:DSP取走所有回读数据后,写入clr信号清标志位
   UNION结构:  BBPCOMM_RD_RESULT_FLAG_LTE_CH2_RFIC_CLR_UNION */
#define BBPCOMM_RD_RESULT_FLAG_LTE_CH2_RFIC_CLR_ADDR  (SOC_BBP_COMM_BASE_ADDR + 0x1054)

/* 寄存器说明：寄存器
   详      述：xbbp向MIPI3 master发出回读类指令时,DSP读取MIPI回读结果,回读结果放置在此16寄存器位置由dsp配置,回读数据是否有效参考标志位
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH2_MIPI_1_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x1058)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH2_MIPI_2_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x105C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH2_MIPI_3_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x1060)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH2_MIPI_4_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x1064)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH2_MIPI_5_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x1068)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH2_MIPI_6_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x106C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH2_MIPI_7_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x1070)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH2_MIPI_8_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x1074)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH2_MIPI_9_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x1078)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH2_MIPI_10_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0x107C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH2_MIPI_11_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0x1080)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH2_MIPI_12_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0x1084)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH2_MIPI_13_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0x1088)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH2_MIPI_14_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0x108C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH2_MIPI_15_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0x1090)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH2_MIPI_16_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0x1094)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      所有回读指令执行完毕,可以取走回读数据
             1:所有回读指令发送完毕,DSP可以按位置读取MIPI回读结果,与下述的软件直接控制MIPI标志位不同
   UNION结构:  BBPCOMM_RD_RESULT_FLAG_LTE_CH2_MIPI_UNION */
#define BBPCOMM_RD_RESULT_FLAG_LTE_CH2_MIPI_ADDR      (SOC_BBP_COMM_BASE_ADDR + 0x1098)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      1:DSP取走所有回读数据后,写入clr信号清标志位,与下述的软件直接控制MIPI标志位不同
   UNION结构:  BBPCOMM_RD_RESULT_FLAG_LTE_CH2_MIPI_CLR_UNION */
#define BBPCOMM_RD_RESULT_FLAG_LTE_CH2_MIPI_CLR_ADDR  (SOC_BBP_COMM_BASE_ADDR + 0x109C)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      DSP等待回读结果超时标志位
             1:超时  
   UNION结构:  BBPCOMM_LTE_CH3_MIPI_RD_OVERTIME_FLAG_DSP_UNION */
#define BBPCOMM_LTE_CH3_MIPI_RD_OVERTIME_FLAG_DSP_ADDR (SOC_BBP_COMM_BASE_ADDR + 0x1100)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      DSP等待回读结果超时标志位
             1:超时  
   UNION结构:  BBPCOMM_LTE_CH3_SSI_RD_OVERTIME_FLAG_DSP_UNION */
#define BBPCOMM_LTE_CH3_SSI_RD_OVERTIME_FLAG_DSP_ADDR (SOC_BBP_COMM_BASE_ADDR + 0x1104)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      DSP等待回读结果超时后,清抄时标志位脉冲
   UNION结构:  BBPCOMM_LTE_CH3_MIPI_RD_OVERTIME_CLR_UNION */
#define BBPCOMM_LTE_CH3_MIPI_RD_OVERTIME_CLR_ADDR     (SOC_BBP_COMM_BASE_ADDR + 0x1108)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      DSP等待回读结果超时后,清抄时标志位脉冲
   UNION结构:  BBPCOMM_LTE_CH3_SSI_RD_OVERTIME_CLR_UNION */
#define BBPCOMM_LTE_CH3_SSI_RD_OVERTIME_CLR_ADDR      (SOC_BBP_COMM_BASE_ADDR + 0x110C)

/* 寄存器说明：寄存器
   详      述：xbbp向SSI3 master发出回读类指令时,DSP读取SSI回读结果,回读结果放置在此16寄存器位置由dsp配置,回读数据是否有效参考标志位
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH3_RFIC_1_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x1110)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH3_RFIC_2_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x1114)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH3_RFIC_3_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x1118)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH3_RFIC_4_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x111C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH3_RFIC_5_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x1120)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH3_RFIC_6_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x1124)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH3_RFIC_7_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x1128)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH3_RFIC_8_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x112C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH3_RFIC_9_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x1130)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH3_RFIC_10_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0x1134)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH3_RFIC_11_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0x1138)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH3_RFIC_12_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0x113C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH3_RFIC_13_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0x1140)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH3_RFIC_14_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0x1144)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH3_RFIC_15_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0x1148)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH3_RFIC_16_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0x114C)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      所有回读指令执行完毕,可以取走回读数据
             1:所有回读指令发送完毕,DSP可以按位置读取SSI回读结果
   UNION结构:  BBPCOMM_RD_RESULT_FLAG_LTE_CH3_RFIC_UNION */
#define BBPCOMM_RD_RESULT_FLAG_LTE_CH3_RFIC_ADDR      (SOC_BBP_COMM_BASE_ADDR + 0x1150)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      1:DSP取走所有回读数据后,写入clr信号清标志位
   UNION结构:  BBPCOMM_RD_RESULT_FLAG_LTE_CH3_RFIC_CLR_UNION */
#define BBPCOMM_RD_RESULT_FLAG_LTE_CH3_RFIC_CLR_ADDR  (SOC_BBP_COMM_BASE_ADDR + 0x1154)

/* 寄存器说明：寄存器
   详      述：xbbp向MIPI3 master发出回读类指令时,DSP读取MIPI回读结果,回读结果放置在此16寄存器位置由dsp配置,回读数据是否有效参考标志位
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH3_MIPI_1_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x1158)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH3_MIPI_2_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x115C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH3_MIPI_3_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x1160)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH3_MIPI_4_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x1164)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH3_MIPI_5_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x1168)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH3_MIPI_6_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x116C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH3_MIPI_7_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x1170)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH3_MIPI_8_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x1174)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH3_MIPI_9_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x1178)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH3_MIPI_10_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0x117C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH3_MIPI_11_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0x1180)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH3_MIPI_12_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0x1184)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH3_MIPI_13_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0x1188)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH3_MIPI_14_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0x118C)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH3_MIPI_15_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0x1190)

/* 寄存器说明：寄存器
   详      述：同上
   UNION结构 ：无 */
#define BBPCOMM_RD_RESULT_LTE_CH3_MIPI_16_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0x1194)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      所有回读指令执行完毕,可以取走回读数据
             1:所有回读指令发送完毕,DSP可以按位置读取MIPI回读结果,与下述的软件直接控制MIPI标志位不同
   UNION结构:  BBPCOMM_RD_RESULT_FLAG_LTE_CH3_MIPI_UNION */
#define BBPCOMM_RD_RESULT_FLAG_LTE_CH3_MIPI_ADDR      (SOC_BBP_COMM_BASE_ADDR + 0x1198)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      1:DSP取走所有回读数据后,写入clr信号清标志位,与下述的软件直接控制MIPI标志位不同
   UNION结构:  BBPCOMM_RD_RESULT_FLAG_LTE_CH3_MIPI_CLR_UNION */
#define BBPCOMM_RD_RESULT_FLAG_LTE_CH3_MIPI_CLR_ADDR  (SOC_BBP_COMM_BASE_ADDR + 0x119C)

/* 寄存器说明：寄存器
 bit[31:4]   保留
 bit[3:0]    通道0 AFC控制信号来源。
             4'b0000，受主模控制；
             4'b0010，强制受W模控制；
             4'b0011，强制受TDS模控制；
             4'b0100，强制受Gm模控制；
             4'b0101，强制受Gs模控制；
             4'b0110，强制受C模控制；
             4'b1000，强制受L模控制；
             其它，无效。
             调试用。
   UNION结构:  BBPCOMM_C0_AFC_PDM_SELECT_MASK_UNION */
#define BBPCOMM_C0_AFC_PDM_SELECT_MASK_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0x1200)

/* 寄存器说明：寄存器
 bit[31:4]   保留
 bit[3:0]    通道0 天线开关和PA控制信号来源。
             4'b0000，受主模控制；
             4'b0010，强制受W模控制；
             4'b0011，强制受TDS模控制；
             4'b0100，强制受Gm模控制；
             4'b0101，强制受Gs模控制；
             4'b0110，强制受C模控制；
             4'b1000，强制受L模控制；
             其它，无效。
             调试用。
   UNION结构:  BBPCOMM_C0_ANT_SWITCH_PA_SELECT_MASK_UNION */
#define BBPCOMM_C0_ANT_SWITCH_PA_SELECT_MASK_ADDR     (SOC_BBP_COMM_BASE_ADDR + 0x1204)

/* 寄存器说明：寄存器
 bit[31:4]   保留
 bit[3:0]    通道0 RFIC控制信号来源（包括线控和SSI）。
             4'b0000，受主模控制；
             4'b0010，强制受W模控制；
             4'b0011，强制受TDS模控制；
             4'b0100，强制受Gm模控制；
             4'b0101，强制受Gs模控制；
             4'b0110，强制受C模控制；
             4'b1000，强制受L模CC0控制；
             4'b1001，强制受L模CC1控制；
             4'b1010，强制受L模CC2控制；
             4'b1011，强制受L模CC3控制；
             其它，无效。
             调试用。
   UNION结构:  BBPCOMM_C0_RFIC_SELECT_MASK_UNION */
#define BBPCOMM_C0_RFIC_SELECT_MASK_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x1208)

/* 寄存器说明：寄存器
 bit[31:4]   保留
 bit[3:0]    通道0 MIPI控制信号来源。
             4'b0000，受主模控制；
             4'b0010，强制受W模控制；
             4'b0011，强制受TDS模控制；
             4'b0100，强制受Gm模控制；
             4'b0101，强制受Gs模控制；
             4'b0110，强制受C模控制；
             4'b1000，强制受L模CC0控制；
             4'b1001，强制受L模CC1控制；
             4'b1010，强制受L模CC2控制；
             4'b1011，强制受L模CC3控制；
             其它，无效。
             调试用。
   UNION结构:  BBPCOMM_C0_MIPI_SELECT_MASK_UNION */
#define BBPCOMM_C0_MIPI_SELECT_MASK_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x120C)

/* 寄存器说明：寄存器
 bit[31:4]   保留
 bit[3:0]    通道0 ABB接收控制信号来源。
             4'b0000，受主模控制；
             4'b0010，强制受W模控制；
             4'b0011，强制受TDS模控制；
             4'b0100，强制受Gm模控制；
             4'b0101，强制受Gs模控制；
             4'b0110，强制受C模控制；
             4'b1000，强制受L模CC0控制；
             4'b1001，强制受L模CC1控制；
             4'b1010，强制受L模CC2控制；
             4'b1011，强制受L模CC3控制；
             其它，无效。
             调试用。
   UNION结构:  BBPCOMM_C0_ABB_RX_SELECT_MASK_UNION */
#define BBPCOMM_C0_ABB_RX_SELECT_MASK_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0x1210)

/* 寄存器说明：寄存器
 bit[31:8]   保留
 bit[7:7]    软件强配模式abb0_rxb_blk_en.
 bit[6:6]    软件强配模式abb0_rxa_blk_en.
 bit[5:5]    软件强配模式abb0_rxb_en.
 bit[4:4]    软件强配模式abb0_rxa_en.
 bit[3:1]    软件强配模式abb0_mode_sel_rx.
 bit[0:0]    ABB0线控强配模式：
             1：表示软件强配，此时上述各个强配才生效；
             0：表示由CTU根据各BBP产生。
             默认值为0。
             测试用。
   UNION结构:  BBPCOMM_ABB0_LINE_CONTROL_CMD_RX_UNION */
#define BBPCOMM_ABB0_LINE_CONTROL_CMD_RX_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x1214)

/* 寄存器说明：寄存器
 bit[31:5]   保留
 bit[4:2]    软件强配模式abb0_mode_sel_tx.
 bit[1:1]    软件强配模式abb0_tx_en.
 bit[0:0]    ABB0线控强配模式：
             1：表示软件强配，此时上述各个强配才生效；
             0：表示由CTU根据各BBP产生。
             默认值为0。
             测试用。
   UNION结构:  BBPCOMM_ABB0_LINE_CONTROL_CMD_TX_UNION */
#define BBPCOMM_ABB0_LINE_CONTROL_CMD_TX_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x1218)

/* 寄存器说明：寄存器
 bit[31:12]  保留
 bit[11]     C2模通道0 TX ABB随路时钟门控旁路信号
 bit[10]     C2模通道0 RX ABB随路时钟门控旁路信号
 bit[9]      G2通道0 TX ABB随路时钟门控旁路信号
 bit[8]      G1通道0 TX ABB随路时钟门控旁路信号
 bit[7]      W模通道0 TX ABB随路时钟门控旁路信号
 bit[6]      TDS通道0 TX ABB随路时钟门控旁路信号
 bit[5]      L模cc0通道0 TX ABB随路时钟门控旁路信号
 bit[4]      G2通道0 RX ABB随路时钟门控旁路信号
 bit[3]      G1通道0 RX ABB随路时钟门控旁路信号
 bit[2]      W模通道0 RX ABB随路时钟门控旁路信号
 bit[1]      TDS通道0 RX ABB随路时钟门控旁路信号
 bit[0]      L模cc0通道0 RX ABB随路时钟门控旁路信号
   UNION结构:  BBPCOMM_CPU_RX0_TX0_CKG_BYPASS_UNION */
#define BBPCOMM_CPU_RX0_TX0_CKG_BYPASS_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0x1220)

/* 寄存器说明：主模0对应的从模（从模0）的模式指示寄存器
 bit[31:1]   保留
 bit[0]      接收主模0对应从模生效时刻
             0：在int0生效
             1：立即生效
             调试用
   UNION结构:  BBPCOMM_C0_SECOND_MODE_IND_SEL_UNION */
#define BBPCOMM_C0_SECOND_MODE_IND_SEL_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0x1224)

/* 寄存器说明：寄存器
 bit[31:4]   保留
 bit[3:0]    通道1 AFC控制信号来源。
             4'b0000，受主模控制；
             4'b0010，强制受W模控制；
             4'b0011，强制受TDS模控制；
             4'b0100，强制受Gm模控制；
             4'b0101，强制受Gs模控制；
             4'b0110，强制受C模控制；
             4'b1000，强制受L模控制；
             其它，无效。
             调试用。
   UNION结构:  BBPCOMM_C1_AFC_PDM_SELECT_MASK_UNION */
#define BBPCOMM_C1_AFC_PDM_SELECT_MASK_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0x1230)

/* 寄存器说明：寄存器
 bit[31:4]   保留
 bit[3:0]    通道1 天线开关和PA控制信号来源。
             4'b0000，受主模控制；
             4'b0010，强制受W模控制；
             4'b0011，强制受TDS模控制；
             4'b0100，强制受Gm模控制；
             4'b0101，强制受Gs模控制；
             4'b0110，强制受C模控制；
             4'b1000，强制受L模控制；
             其它，无效。
             调试用。
   UNION结构:  BBPCOMM_C1_ANT_SWITCH_PA_SELECT_MASK_UNION */
#define BBPCOMM_C1_ANT_SWITCH_PA_SELECT_MASK_ADDR     (SOC_BBP_COMM_BASE_ADDR + 0x1234)

/* 寄存器说明：寄存器
 bit[31:4]   保留
 bit[3:0]    通道1 RFIC控制信号来源（包括线控和SSI）。
             4'b0000，受主模控制；
             4'b0010，强制受W模控制；
             4'b0011，强制受TDS模控制；
             4'b0100，强制受Gm模控制；
             4'b0101，强制受Gs模控制；
             4'b0110，强制受C模控制；
             4'b1000，强制受L模1CC控制；
             4'b1001，强制受L模2CC控制；
             4'b1010，强制受L模3CC控制；
             4'b1011，强制受L模4CC控制；
             其它，无效。
             调试用。
   UNION结构:  BBPCOMM_C1_RFIC_SELECT_MASK_UNION */
#define BBPCOMM_C1_RFIC_SELECT_MASK_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x1238)

/* 寄存器说明：寄存器
 bit[31:4]   保留
 bit[3:0]    通道1 MIPI控制信号来源。
             4'b0000，受主模控制；
             4'b0010，强制受W模控制；
             4'b0011，强制受TDS模控制；
             4'b0100，强制受Gm模控制；
             4'b0101，强制受Gs模控制；
             4'b0110，强制受C模控制；
             4'b1000，强制受L模CC0控制；
             4'b1001，强制受L模CC1控制；
             4'b1010，强制受L模CC2控制；
             4'b1011，强制受L模CC3控制；
             其它，无效。
             调试用。
   UNION结构:  BBPCOMM_C1_MIPI_SELECT_MASK_UNION */
#define BBPCOMM_C1_MIPI_SELECT_MASK_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x123C)

/* 寄存器说明：寄存器
 bit[31:4]   保留
 bit[3:0]    通道1 ABB控制信号来源。
             4'b0000，受主模控制；
             4'b0010，强制受W模控制；
             4'b0011，强制受TDS模控制；
             4'b0100，强制受Gm模控制；
             4'b0101，强制受Gs模控制；
             4'b0110，强制受C模控制；
             4'b1000，强制受L模CC0控制；
             4'b1001，强制受L模CC1控制；
             4'b1010，强制受L模CC2控制；
             4'b1011，强制受L模CC3控制；
             其它，无效。
             调试用。
   UNION结构:  BBPCOMM_C1_ABB_RX_SELECT_MASK_UNION */
#define BBPCOMM_C1_ABB_RX_SELECT_MASK_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0x1240)

/* 寄存器说明：寄存器
 bit[31:8]   保留
 bit[7:7]    软件强配模式abb1_rxb_blk_en.
 bit[6:6]    软件强配模式abb1_rxa_blk_en.
 bit[5:5]    软件强配模式abb1_rxb_en.
 bit[4:4]    软件强配模式abb1_rxa_en.
 bit[3:1]    软件强配模式abb1_mode_sel_rx.
 bit[0:0]    ABB1线控强配模式：
             1：表示软件强配，此时上述各个强配才生效；
             0：表示由CTU根据各BBP产生。
             默认值为0。
             测试用。
   UNION结构:  BBPCOMM_ABB1_LINE_CONTROL_CMD_RX_UNION */
#define BBPCOMM_ABB1_LINE_CONTROL_CMD_RX_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x1244)

/* 寄存器说明：寄存器
 bit[31:5]   保留
 bit[4:2]    软件强配模式abb1_mode_sel_tx.
 bit[1:1]    软件强配模式abb1_tx_en.
 bit[0:0]    ABB1线控强配模式：
             1：表示软件强配，此时上述各个强配才生效；
             0：表示由CTU根据各BBP产生。
             默认值为0。
             测试用。
   UNION结构:  BBPCOMM_ABB1_LINE_CONTROL_CMD_TX_UNION */
#define BBPCOMM_ABB1_LINE_CONTROL_CMD_TX_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x1248)

/* 寄存器说明：寄存器
 bit[31:12]  保留
 bit[11]     C2模通道1 TX ABB随路时钟门控旁路信号
 bit[10]     C2模通道1 RX ABB随路时钟门控旁路信号
 bit[9]      G2通道1 TX ABB随路时钟门控旁路信号
 bit[8]      G1通道1 TX ABB随路时钟门控旁路信号
 bit[7]      W模通道1 TX ABB随路时钟门控旁路信号
 bit[6]      TDS通道1 TX ABB随路时钟门控旁路信号
 bit[5]      L模cc1通道1 TX ABB随路时钟门控旁路信号
 bit[4]      G2通道1 RX ABB随路时钟门控旁路信号
 bit[3]      G1通道1 RX ABB随路时钟门控旁路信号
 bit[2]      W模通道1 RX ABB随路时钟门控旁路信号
 bit[1]      TDS通道1 RX ABB随路时钟门控旁路信号
 bit[0]      L模cc1通道1 RX ABB随路时钟门控旁路信号
   UNION结构:  BBPCOMM_CPU_RX1_TX1_CKG_BYPASS_UNION */
#define BBPCOMM_CPU_RX1_TX1_CKG_BYPASS_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0x1250)

/* 寄存器说明：主模1对应的从模（从模1）的模式指示寄存器
 bit[31:1]   保留
 bit[0]      接收主模1对应从模生效时刻
             0：在int0生效
             1：立即生效
             调试用
   UNION结构:  BBPCOMM_C1_SECOND_MODE_IND_SEL_UNION */
#define BBPCOMM_C1_SECOND_MODE_IND_SEL_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0x1254)

/* 寄存器说明：寄存器
 bit[31:4]   保留
 bit[3:0]    通道2 AFC控制信号来源。
             4'b0000，受主模控制；
             4'b0010，强制受W模控制；
             4'b0011，强制受TDS模控制；
             4'b0100，强制受Gm模控制；
             4'b0101，强制受Gs模控制；
             4'b0110，强制受C模控制；
             4'b1000，强制受L模控制；
             其它，无效。
             调试用。
   UNION结构:  BBPCOMM_C2_AFC_PDM_SELECT_MASK_UNION */
#define BBPCOMM_C2_AFC_PDM_SELECT_MASK_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0x1260)

/* 寄存器说明：寄存器
 bit[31:4]   保留
 bit[3:0]    通道2 天线开关和PA控制信号来源。
             4'b0000，受主模控制；
             4'b0010，强制受W模控制；
             4'b0011，强制受TDS模控制；
             4'b0100，强制受Gm模控制；
             4'b0101，强制受Gs模控制；
             4'b0110，强制受C模控制；
             4'b1000，强制受L模控制；
             其它，无效。
             调试用。
   UNION结构:  BBPCOMM_C2_ANT_SWITCH_PA_SELECT_MASK_UNION */
#define BBPCOMM_C2_ANT_SWITCH_PA_SELECT_MASK_ADDR     (SOC_BBP_COMM_BASE_ADDR + 0x1264)

/* 寄存器说明：寄存器
 bit[31:4]   保留
 bit[3:0]    通道2 RFIC控制信号来源（包括线控和SSI）。
             4'b0000，受主模控制；
             4'b0010，强制受W模控制；
             4'b0011，强制受TDS模控制；
             4'b0100，强制受Gm模控制；
             4'b0101，强制受Gs模控制；
             4'b0110，强制受C模控制；
             4'b1000，强制受L模1CC控制；
             4'b1001，强制受L模2CC控制；
             4'b1010，强制受L模3CC控制；
             4'b1011，强制受L模4CC控制；
             其它，无效。
             调试用。
   UNION结构:  BBPCOMM_C2_RFIC_SELECT_MASK_UNION */
#define BBPCOMM_C2_RFIC_SELECT_MASK_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x1268)

/* 寄存器说明：寄存器
 bit[31:4]   保留
 bit[3:0]    通道2 MIPI控制信号来源。
             4'b0000，受主模控制；
             4'b0010，强制受W模控制；
             4'b0011，强制受TDS模控制；
             4'b0100，强制受Gm模控制；
             4'b0101，强制受Gs模控制；
             4'b0110，强制受C模控制；
             4'b1000，强制受L模1CC控制；
             4'b1001，强制受L模2CC控制；
             4'b1010，强制受L模3CC控制；
             4'b1011，强制受L模4CC控制；
             其它，无效。
             调试用。
   UNION结构:  BBPCOMM_C2_MIPI_SELECT_MASK_UNION */
#define BBPCOMM_C2_MIPI_SELECT_MASK_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x126C)

/* 寄存器说明：寄存器
 bit[31:4]   保留
 bit[3:0]    通道2 ABB接收控制信号来源。
             4'b0000，受主模控制；
             4'b0010，强制受W模控制；
             4'b0011，强制受TDS模控制；
             4'b0100，强制受Gm模控制；
             4'b0101，强制受Gs模控制；
             4'b0110，强制受C模控制；
             4'b1000，强制受L模1CC控制；
             4'b1001，强制受L模2CC控制；
             4'b1010，强制受L模3CC控制；
             4'b1011，强制受L模4CC控制；
             其它，无效。
             调试用。
   UNION结构:  BBPCOMM_C2_ABB_RX_SELECT_MASK_UNION */
#define BBPCOMM_C2_ABB_RX_SELECT_MASK_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0x1270)

/* 寄存器说明：寄存器
 bit[31:8]   保留
 bit[7:7]    软件强配模式abb2_rxb_blk_en.
 bit[6:6]    软件强配模式abb2_rxa_blk_en.
 bit[5:5]    软件强配模式abb2_rxb_en.
 bit[4:4]    软件强配模式abb2_rxa_en.
 bit[3:1]    软件强配模式abb2_mode_sel_rx.
 bit[0:0]    ABB2线控强配模式：
             1：表示软件强配，此时上述各个强配才生效；
             0：表示由CTU根据各BBP产生。
             默认值为0。
             测试用。
   UNION结构:  BBPCOMM_ABB2_LINE_CONTROL_CMD_RX_UNION */
#define BBPCOMM_ABB2_LINE_CONTROL_CMD_RX_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x1274)

/* 寄存器说明：寄存器
 bit[31:5]   保留
 bit[4:2]    软件强配模式abb2_mode_sel_tx.
 bit[1:1]    软件强配模式abb2_tx_en.
 bit[0:0]    ABB2线控强配模式：
             1：表示软件强配，此时上述各个强配才生效；
             0：表示由CTU根据各BBP产生。
             默认值为0。
             测试用。
   UNION结构:  BBPCOMM_ABB2_LINE_CONTROL_CMD_TX_UNION */
#define BBPCOMM_ABB2_LINE_CONTROL_CMD_TX_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x1278)

/* 寄存器说明：寄存器
 bit[31:12]  保留
 bit[11]     C2模通道2 TX ABB随路时钟门控旁路信号
 bit[10]     C2模通道2 RX ABB随路时钟门控旁路信号
 bit[9]      G2通道2 TX ABB随路时钟门控旁路信号
 bit[8]      G1通道2 TX ABB随路时钟门控旁路信号
 bit[7]      W模通道2 TX ABB随路时钟门控旁路信号
 bit[6]      TDS通道2 TX ABB随路时钟门控旁路信号
 bit[5]      L模cc2通道2 TX ABB随路时钟门控旁路信号
 bit[4]      G2通道2 RX ABB随路时钟门控旁路信号
 bit[3]      G1通道2 RX ABB随路时钟门控旁路信号
 bit[2]      W模通道2 RX ABB随路时钟门控旁路信号
 bit[1]      TDS通道2 RX ABB随路时钟门控旁路信号
 bit[0]      L模cc2通道2 RX ABB随路时钟门控旁路信号
   UNION结构:  BBPCOMM_CPU_RX2_TX0_CKG_BYPASS_UNION */
#define BBPCOMM_CPU_RX2_TX0_CKG_BYPASS_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0x1280)

/* 寄存器说明：主模2对应的从模（从模2）的模式指示寄存器
 bit[31:1]   保留
 bit[0]      接收主模2对应从模生效时刻
             0：在int0生效
             1：立即生效
             调试用
   UNION结构:  BBPCOMM_C2_SECOND_MODE_IND_SEL_UNION */
#define BBPCOMM_C2_SECOND_MODE_IND_SEL_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0x1284)

/* 寄存器说明：寄存器
 bit[31:4]   保留
 bit[3:0]    通道3 AFC控制信号来源。
             4'b0000，受主模控制；
             4'b0010，强制受W模控制；
             4'b0011，强制受TDS模控制；
             4'b0100，强制受Gm模控制；
             4'b0101，强制受Gs模控制；
             4'b0110，强制受C模控制；
             4'b1000，强制受L模控制；
             其它，无效。
             调试用。
   UNION结构:  BBPCOMM_C3_AFC_PDM_SELECT_MASK_UNION */
#define BBPCOMM_C3_AFC_PDM_SELECT_MASK_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0x1290)

/* 寄存器说明：寄存器
 bit[31:4]   保留
 bit[3:0]    通道3 天线开关和PA控制信号来源。
             4'b0000，受主模控制；
             4'b0010，强制受W模控制；
             4'b0011，强制受TDS模控制；
             4'b0100，强制受Gm模控制；
             4'b0101，强制受Gs模控制；
             4'b0110，强制受C模控制；
             4'b1000，强制受L模控制；
             其它，无效。
             调试用。
   UNION结构:  BBPCOMM_C3_ANT_SWITCH_PA_SELECT_MASK_UNION */
#define BBPCOMM_C3_ANT_SWITCH_PA_SELECT_MASK_ADDR     (SOC_BBP_COMM_BASE_ADDR + 0x1294)

/* 寄存器说明：寄存器
 bit[31:4]   保留
 bit[3:0]    通道3 RFIC控制信号来源（包括线控和SSI）。
             4'b0000，受主模控制；
             4'b0010，强制受W模控制；
             4'b0011，强制受TDS模控制；
             4'b0100，强制受Gm模控制；
             4'b0101，强制受Gs模控制；
             4'b0110，强制受C模控制；
             4'b1000，强制受L模1CC控制；
             4'b1001，强制受L模2CC控制；
             4'b1010，强制受L模3CC控制；
             4'b1011，强制受L模4CC控制；
             其它，无效。
             调试用。
   UNION结构:  BBPCOMM_C3_RFIC_SELECT_MASK_UNION */
#define BBPCOMM_C3_RFIC_SELECT_MASK_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x1298)

/* 寄存器说明：寄存器
 bit[31:4]   保留
 bit[3:0]    通道3 MIPI控制信号来源。
             4'b0000，受主模控制；
             4'b0010，强制受W模控制；
             4'b0011，强制受TDS模控制；
             4'b0100，强制受Gm模控制；
             4'b0101，强制受Gs模控制；
             4'b0110，强制受C模控制；
             4'b1000，强制受L模CC0控制；
             4'b1001，强制受L模CC1控制；
             4'b1010，强制受L模CC2控制；
             4'b1011，强制受L模CC3控制；
             其它，无效。
             调试用。
   UNION结构:  BBPCOMM_C3_MIPI_SELECT_MASK_UNION */
#define BBPCOMM_C3_MIPI_SELECT_MASK_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x129C)

/* 寄存器说明：寄存器
 bit[31:4]   保留
 bit[3:0]    通道3 ABB接收控制信号来源。
             4'b0000，受主模控制；
             4'b0010，强制受W模控制；
             4'b0011，强制受TDS模控制；
             4'b0100，强制受Gm模控制；
             4'b0101，强制受Gs模控制；
             4'b0110，强制受C模控制；
             4'b1000，强制受L模CC0控制；
             4'b1001，强制受L模CC1控制；
             4'b1010，强制受L模CC2控制；
             4'b1011，强制受L模CC3控制；
             其它，无效。
             调试用。
   UNION结构:  BBPCOMM_C3_ABB_RX_SELECT_MASK_UNION */
#define BBPCOMM_C3_ABB_RX_SELECT_MASK_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0x12A0)

/* 寄存器说明：寄存器
 bit[31:8]   保留
 bit[7:7]    软件强配模式abb3_rxb_blk_en.
 bit[6:6]    软件强配模式abb3_rxa_blk_en.
 bit[5:5]    软件强配模式abb3_rxb_en.
 bit[4:4]    软件强配模式abb3_rxa_en.
 bit[3:1]    软件强配模式abb3_mode_sel_rx.
 bit[0:0]    ABB3线控强配模式：
             1：表示软件强配，此时上述各个强配才生效；
             0：表示由CTU根据各BBP产生。
             默认值为0。
             测试用。
   UNION结构:  BBPCOMM_ABB3_LINE_CONTROL_CMD_RX_UNION */
#define BBPCOMM_ABB3_LINE_CONTROL_CMD_RX_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x12A4)

/* 寄存器说明：寄存器
 bit[31:5]   保留
 bit[4:2]    软件强配模式abb3_mode_sel_tx.
 bit[1:1]    软件强配模式abb3_tx_en.
 bit[0:0]    ABB3线控强配模式：
             1：表示软件强配，此时上述各个强配才生效；
             0：表示由CTU根据各BBP产生。
             默认值为0。
             测试用。
   UNION结构:  BBPCOMM_ABB3_LINE_CONTROL_CMD_TX_UNION */
#define BBPCOMM_ABB3_LINE_CONTROL_CMD_TX_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x12A8)

/* 寄存器说明：寄存器
 bit[31:12]  保留
 bit[11]     C2模通道3 TX ABB随路时钟门控旁路信号
 bit[10]     C2模通道3 RX ABB随路时钟门控旁路信号
 bit[9]      G2通道3 TX ABB随路时钟门控旁路信号
 bit[8]      G1通道3 TX ABB随路时钟门控旁路信号
 bit[7]      W模通道3 TX ABB随路时钟门控旁路信号
 bit[6]      TDS通道3 TX ABB随路时钟门控旁路信号
 bit[5]      L模cc3通道3 TX ABB随路时钟门控旁路信号
 bit[4]      G2通道3 RX ABB随路时钟门控旁路信号
 bit[3]      G1通道3 RX ABB随路时钟门控旁路信号
 bit[2]      W模通道3 RX ABB随路时钟门控旁路信号
 bit[1]      TDS通道3 RX ABB随路时钟门控旁路信号
 bit[0]      L模cc3通道3 RX ABB随路时钟门控旁路信号
   UNION结构:  BBPCOMM_CPU_RX3_TX3_CKG_BYPASS_UNION */
#define BBPCOMM_CPU_RX3_TX3_CKG_BYPASS_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0x12B0)

/* 寄存器说明：主模3对应的从模（从模3）的模式指示寄存器
 bit[31:1]   保留
 bit[0]      接收主模3对应从模生效时刻
             0：在int0生效
             1：立即生效
             调试用
   UNION结构:  BBPCOMM_C3_SECOND_MODE_IND_SEL_UNION */
#define BBPCOMM_C3_SECOND_MODE_IND_SEL_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0x12B4)

/* 寄存器说明：寄存器
 bit[31:2]   保留
 bit[1:0]    电平信号，低有效。
             当LTE主模需要做异系统测量时需配置本寄存器为3，异系统测量结束后配置本寄存器为0。
             bit1:1’b0: lte_intrasys_valid输入无效，被强制为1。
             bit0:1’b0:
             lte_intersys_ingap_pre_ind输入无效，被强制为0。
             bit[1:0] = 11b: 让lte_intrasys_valid和lte_intersys_ingap_pre_ind输入有效。
             
             配置时刻：LTE主模需要做异系统测量时需配置本寄存器为3，异系统测量结束后配置本寄存器为0。
             生效时刻：立即生效
   UNION结构:  BBPCOMM_LTEBBP_INPUT_MASK_UNION */
#define BBPCOMM_LTEBBP_INPUT_MASK_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x1300)

/* 寄存器说明：寄存器
 bit[31:2]   保留
 bit[1:0]    电平信号，低有效。
             当W主模需要做异系统测量时需配置本寄存器为3，异系统测量结束后配置本寄存器为0。
             bit1:1’b0:
              让w_intrasys_valid输入无效，被强制为1。
             bit0:1’b0:
             w_intersys_ingap_pre_ind输入无效，被强制为0。
             bit[1:0] = 11b: 让w_intrasys_valid和w_intersys_ingap_pre_ind输入有效。
             
             配置时刻：W主模需要做异系统测量时需配置本寄存器为3，异系统测量结束后配置本寄存器为0。
             生效时刻：立即生效
   UNION结构:  BBPCOMM_WBBP_INPUT_MASK_UNION */
#define BBPCOMM_WBBP_INPUT_MASK_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0x1304)

/* 寄存器说明：寄存器
 bit[31:2]   保留
 bit[1:0]    电平信号，低有效。
             当Gm主模需要做异系统测量时需配置本寄存器为3，异系统测量结束后配置本寄存器为0。
             bit1:1’b0:
              让gm_intrasys_valid输入无效，被强制为1。
             bit0:1’b0:
             gm_intersys_ingap_pre_ind输入无效，被强制为0。
             bit[1:0] = 11b: 让gm_intrasys_valid和gm_intersys_ingap_pre_ind输入有效。
             
             配置时刻：Gm主模需要做异系统测量时需配置本寄存器为3，异系统测量结束后配置本寄存器为0。
             生效时刻：立即生效
   UNION结构:  BBPCOMM_GMBBP_INPUT_MASK_UNION */
#define BBPCOMM_GMBBP_INPUT_MASK_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x1308)

/* 寄存器说明：寄存器
 bit[31:2]   保留
 bit[1:0]    电平信号，低有效。
             当Gs主模需要做异系统测量时需配置本寄存器为3，异系统测量结束后配置本寄存器为0。
             bit1:1’b0:
              让gs_intrasys_valid输入无效，被强制为1。
             bit0:1’b0:
             gs_intersys_ingap_pre_ind输入无效，被强制为0。
             bit[1:0] = 11b: 让gs_intrasys_valid和gs_intersys_ingap_pre_ind输入有效。
             
             配置时刻：Gs主模需要做异系统测量时需配置本寄存器为3，异系统测量结束后配置本寄存器为0。
             生效时刻：立即生效
   UNION结构:  BBPCOMM_GSBBP_INPUT_MASK_UNION */
#define BBPCOMM_GSBBP_INPUT_MASK_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x130C)

/* 寄存器说明：寄存器
 bit[31:2]   保留
 bit[1:0]    电平信号，低有效。
             当TDS主模需要做异系统测量时需配置本寄存器为3，异系统测量结束后配置本寄存器为0。
             bit1:1’b0:
              让tds_intrasys_valid输入无效，被强制为1。
             bit0:1’b0:
             tds_intersys_ingap_pre_ind输入无效，被强制为0。
             bit[1:0] = 11b: 让tds_intrasys_valid和tds_intersys_ingap_pre_ind输入有效。
             
             配置时刻：TDS主模需要做异系统测量时需配置本寄存器为3，异系统测量结束后配置本寄存器为0。
             生效时刻：立即生效
   UNION结构:  BBPCOMM_TDSBBP_INPUT_MASK_UNION */
#define BBPCOMM_TDSBBP_INPUT_MASK_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x1310)

/* 寄存器说明：寄存器
 bit[31:2]   保留
 bit[1:0]    电平信号，低有效。
             当C主模需要做异系统测量时需配置本寄存器为3，异系统测量结束后配置本寄存器为0。
             bit1:1’b0:
              让c_intrasys_valid输入无效，被强制为1。
             bit0:1’b0:
             c_intersys_ingap_pre_ind输入无效，被强制为0。
             bit[1:0] = 11b: 让c_intrasys_valid和c_intersys_ingap_pre_ind输入有效。
             配置时刻：TDS主模需要做异系统测量时需配置本寄存器为3，异系统测量结束后配置本寄存器为0。
             生效时刻：立即生效
   UNION结构:  BBPCOMM_CBBP_INPUT_MASK_UNION */
#define BBPCOMM_CBBP_INPUT_MASK_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0x1314)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      MIPI轮询请求清零信号，1：清除清零信号，0：无效
   UNION结构:  BBPCOMM_MIPI_ROBIN_CLR_IND_IMI_UNION */
#define BBPCOMM_MIPI_ROBIN_CLR_IND_IMI_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0x1318)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      SSI轮询请求清零信号，1：清除清零信号，0：无效
   UNION结构:  BBPCOMM_SSI_ROBIN_CLR_IND_IMI_UNION */
#define BBPCOMM_SSI_ROBIN_CLR_IND_IMI_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0x131C)

/* 寄存器说明：寄存器
 bit[31:2]   保留
 bit[1]      w主模下实际控制RF指示，电平信号。为1代表W控制RF配置通道，为0代表从模可以控制RF通道。用于单RFIC时射频控制相关信号的选通。
             w_intrasys_valid_delay的上升沿比w_intrasys_valid上升沿滞后，下降沿一致。
 bit[0]      w主模下控制RF指示，电平信号。
             1’b0: W放弃RF控制权。
             1’b1: W享有控制RF权（但实际配置RF需w_intrasys_valid_delay信号为1）。
   UNION结构:  BBPCOMM_W_INTRASYS_VALID_UNION */
#define BBPCOMM_W_INTRASYS_VALID_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x1320)

/* 寄存器说明：寄存器
 bit[31:2]   保留
 bit[1]      gm主模下实际控制RF指示，电平信号。为1代表gm控制RF配置通道，为0代表从模可以控制RF通道。用于单RFIC时射频控制相关信号的选通。
             gm_intrasys_valid_delay的上升沿比gm_intrasys_valid上升沿滞后，下降沿一致。
 bit[0]      gm主模下控制RF指示，电平信号。
             1’b0: gm放弃RF控制权。
             1’b1: gm享有控制RF权（但实际配置RF需gm_intrasys_valid_delay信号为1）。
   UNION结构:  BBPCOMM_GM_INTRASYS_VALID_UNION */
#define BBPCOMM_GM_INTRASYS_VALID_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x1324)

/* 寄存器说明：寄存器
 bit[31:2]   保留
 bit[1]      gs主模下实际控制RF指示，电平信号。为1代表gs控制RF配置通道，为0代表从模可以控制RF通道。用于单RFIC时射频控制相关信号的选通。
             gs_intrasys_valid_delay的上升沿比gs_intrasys_valid上升沿滞后，下降沿一致。
 bit[0]      gs主模下控制RF指示，电平信号。
             1’b0: gs放弃RF控制权。
             1’b1: gs享有控制RF权（但实际配置RF需gs_intrasys_valid_delay信号为1）。
   UNION结构:  BBPCOMM_GS_INTRASYS_VALID_UNION */
#define BBPCOMM_GS_INTRASYS_VALID_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x1328)

/* 寄存器说明：寄存器
 bit[31:2]   保留
 bit[1]      LTE主模下实际控制RF指示，电平信号。为1代表LTE控制RF配置通道，为0代表从模可以控制RF通道。用于单RFIC时射频控制相关信号的选通。
             lte_intrasys_valid_delay的上升沿比lte_intrasys_valid上升沿滞后，下降沿一致。
 bit[0]      Lte主模下控制RF指示，电平信号。
             1’b0: LTE放弃RF控制权。
             1’b1: LTE享有控制RF权（但实际配置RF需lte_intrasys_valid_delay信号为1）。
   UNION结构:  BBPCOMM_LTE_INTRASYS_VALID_UNION */
#define BBPCOMM_LTE_INTRASYS_VALID_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x132C)

/* 寄存器说明：寄存器
 bit[31:2]   保留
 bit[1]      TDS主模下实际控制RF指示，电平信号。为1代表TDS控制RF配置通道，为0代表从模可以控制RF通道。用于单RFIC时射频控制相关信号的选通。
             tds_intrasys_valid_delay的上升沿比tds_intrasys_valid上升沿滞后，下降沿一致。
 bit[0]      TDS主模下控制RF指示，电平信号。
             1’b0: TDS放弃RF控制权。
             1’b1: TDS享有控制RF权（但实际配置RF需tds_intrasys_valid_delay信号为1）。
   UNION结构:  BBPCOMM_TDS_INTRASYS_VALID_UNION */
#define BBPCOMM_TDS_INTRASYS_VALID_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x1330)

/* 寄存器说明：寄存器
 bit[31:2]   保留
 bit[1]      c2主模下实际控制RF指示，电平信号。为1代表C控制RF配置通道，为0代表从模可以控制RF通道。用于单RFIC时射频控制相关信号的选通。
             c_intrasys_valid_delay的上升沿比c_intrasys_valid上升沿滞后，下降沿一致。
 bit[0]      w主模下控制RF指示，电平信号。
             1’b0: W放弃RF控制权。
             1’b1: W享有控制RF权（但实际配置RF需w_intrasys_valid_delay信号为1）。
   UNION结构:  BBPCOMM_C_INTRASYS_VALID_UNION */
#define BBPCOMM_C_INTRASYS_VALID_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x1334)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      软中断int0生效时刻转圈指示
   UNION结构:  BBPCOMM_INT0_TIME_CIRCLE_UNION */
#define BBPCOMM_INT0_TIME_CIRCLE_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x1338)

/* 寄存器说明：寄存器
   详      述：软中断配置时刻19.2M钟计数器计数值
   UNION结构 ：无 */
#define BBPCOMM_SOFT_TIME_START_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0x133C)

/* 寄存器说明：寄存器
 bit[31:12]  保留
 bit[11:0]   ch0的com2abb_line_ctrl_mode切换时，com2abb_rxa/b_en强制拉低的时间。
             单位：工作时钟
   UNION结构:  BBPCOMM_CH0_RX_EN_FORCE_LOW_CNT_UNION */
#define BBPCOMM_CH0_RX_EN_FORCE_LOW_CNT_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0x1370)

/* 寄存器说明：寄存器
 bit[31:12]  保留
 bit[11:0]   ch1的com2abb_line_ctrl_mode切换时，com2abb_rxa/b_en强制拉低的时间。
             单位：工作时钟
   UNION结构:  BBPCOMM_CH1_RX_EN_FORCE_LOW_CNT_UNION */
#define BBPCOMM_CH1_RX_EN_FORCE_LOW_CNT_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0x1374)

/* 寄存器说明：寄存器
 bit[31:12]  保留
 bit[11:0]   ch2的com2abb_line_ctrl_mode切换时，com2abb_rxa/b_en强制拉低的时间。
             单位：工作时钟
   UNION结构:  BBPCOMM_CH2_RX_EN_FORCE_LOW_CNT_UNION */
#define BBPCOMM_CH2_RX_EN_FORCE_LOW_CNT_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0x1378)

/* 寄存器说明：寄存器
 bit[31:12]  保留
 bit[11:0]   ch3的com2abb_line_ctrl_mode切换时，com2abb_rxa/b_en强制拉低的时间。
             单位：工作时钟
   UNION结构:  BBPCOMM_CH3_RX_EN_FORCE_LOW_CNT_UNION */
#define BBPCOMM_CH3_RX_EN_FORCE_LOW_CNT_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0x137C)

/* 寄存器说明：寄存器
 bit[31:16]  通道0下行模式切换时下行时钟强制为0的时钟数
             单位：工作时钟。
 bit[15:0]   通道0上行模式切换时上行时钟强制为0的时钟数
             单位：工作时钟。
   UNION结构:  BBPCOMM_CH0_CLK_MUX_CNT_UNION */
#define BBPCOMM_CH0_CLK_MUX_CNT_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0x1380)

/* 寄存器说明：寄存器
 bit[31:16]  通道1下行模式切换时下行时钟强制为0的时钟数
             单位：工作时钟。
 bit[15:0]   通道1上行模式切换时上行时钟强制为0的时钟数
             单位：工作时钟。
   UNION结构:  BBPCOMM_CH1_CLK_MUX_CNT_UNION */
#define BBPCOMM_CH1_CLK_MUX_CNT_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0x1384)

/* 寄存器说明：寄存器
 bit[31:16]  通道2下行模式切换时下行时钟强制为0的时钟数
             单位：工作时钟。
 bit[15:0]   通道2上行模式切换时上行时钟强制为0的时钟数
             单位：工作时钟。
   UNION结构:  BBPCOMM_CH2_CLK_MUX_CNT_UNION */
#define BBPCOMM_CH2_CLK_MUX_CNT_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0x1388)

/* 寄存器说明：寄存器
 bit[31:16]  通道3下行模式切换时下行时钟强制为0的时钟数
             单位：工作时钟。
 bit[15:0]   通道3上行模式切换时上行时钟强制为0的时钟数
             单位：工作时钟。
   UNION结构:  BBPCOMM_CH3_CLK_MUX_CNT_UNION */
#define BBPCOMM_CH3_CLK_MUX_CNT_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0x138C)

/* 寄存器说明：寄存器
 bit[31:12]  保留
 bit[11:0]   W模下行随路时钟门控使能强制拉高时钟数，
             单位：工作时钟。
   UNION结构:  BBPCOMM_W_CLK_EN_FORCE_HIGH_CNT_UNION */
#define BBPCOMM_W_CLK_EN_FORCE_HIGH_CNT_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0x1390)

/* 寄存器说明：寄存器
 bit[31:12]  保留
 bit[11:0]   TDS模下行随路时钟门控使能强制拉高时钟数，
             单位：工作时钟。
   UNION结构:  BBPCOMM_TDS_CLK_EN_FORCE_HIGH_CNT_UNION */
#define BBPCOMM_TDS_CLK_EN_FORCE_HIGH_CNT_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0x1394)

/* 寄存器说明：寄存器
 bit[31:12]  保留
 bit[11:0]   GM模下行随路时钟门控使能强制拉高时钟数，
             单位：工作时钟。
   UNION结构:  BBPCOMM_GM_CLK_EN_FORCE_HIGH_CNT_UNION */
#define BBPCOMM_GM_CLK_EN_FORCE_HIGH_CNT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x1398)

/* 寄存器说明：寄存器
 bit[31:12]  保留
 bit[11:0]   GS模下行随路时钟门控使能强制拉高时钟数，
             单位：工作时钟。
   UNION结构:  BBPCOMM_GS_CLK_EN_FORCE_HIGH_CNT_UNION */
#define BBPCOMM_GS_CLK_EN_FORCE_HIGH_CNT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x139C)

/* 寄存器说明：寄存器
 bit[31:12]  保留
 bit[11:0]   C2模下行随路时钟门控使能强制拉高时钟数，
             单位：工作时钟。
   UNION结构:  BBPCOMM_C_CLK_EN_FORCE_HIGH_CNT_UNION */
#define BBPCOMM_C_CLK_EN_FORCE_HIGH_CNT_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0x13A0)

/* 寄存器说明：寄存器
 bit[31:12]  保留
 bit[11:0]   LTE通道0模式下行随路时钟门控使能强制拉高时钟数，
             单位：工作时钟。
   UNION结构:  BBPCOMM_LTE_CH0_CLK_EN_FORCE_HIGH_CNT_UNION */
#define BBPCOMM_LTE_CH0_CLK_EN_FORCE_HIGH_CNT_ADDR    (SOC_BBP_COMM_BASE_ADDR + 0x13A4)

/* 寄存器说明：寄存器
 bit[31:12]  保留
 bit[11:0]   LTE通道1模式下行随路时钟门控使能强制拉高时钟数，
             单位：工作时钟。
   UNION结构:  BBPCOMM_LTE_CH1_CLK_EN_FORCE_HIGH_CNT_UNION */
#define BBPCOMM_LTE_CH1_CLK_EN_FORCE_HIGH_CNT_ADDR    (SOC_BBP_COMM_BASE_ADDR + 0x13A8)

/* 寄存器说明：寄存器
 bit[31:12]  保留
 bit[11:0]   LTE通道2模式下行随路时钟门控使能强制拉高时钟数，
             单位：工作时钟。
   UNION结构:  BBPCOMM_LTE_CH2_CLK_EN_FORCE_HIGH_CNT_UNION */
#define BBPCOMM_LTE_CH2_CLK_EN_FORCE_HIGH_CNT_ADDR    (SOC_BBP_COMM_BASE_ADDR + 0x13AC)

/* 寄存器说明：寄存器
 bit[31:12]  保留
 bit[11:0]   LTE通道3模式下行随路时钟门控使能强制拉高时钟数，
             单位：工作时钟。
   UNION结构:  BBPCOMM_LTE_CH3_CLK_EN_FORCE_HIGH_CNT_UNION */
#define BBPCOMM_LTE_CH3_CLK_EN_FORCE_HIGH_CNT_ADDR    (SOC_BBP_COMM_BASE_ADDR + 0x13B0)

/* 寄存器说明：寄存器
   详      述：保留
   UNION结构 ：无 */
#define BBPCOMM_BBC_REV0_ADDR                         (SOC_BBP_COMM_BASE_ADDR + 0x1400)

/* 寄存器说明：寄存器
   详      述：保留
   UNION结构 ：无 */
#define BBPCOMM_BBC_REV1_ADDR                         (SOC_BBP_COMM_BASE_ADDR + 0x1404)

/* 寄存器说明：寄存器
   详      述：保留
   UNION结构 ：无 */
#define BBPCOMM_BBC_REV2_ADDR                         (SOC_BBP_COMM_BASE_ADDR + 0x1408)

/* 寄存器说明：寄存器
   详      述：保留
   UNION结构 ：无 */
#define BBPCOMM_BBC_REV3_ADDR                         (SOC_BBP_COMM_BASE_ADDR + 0x140C)

/* 寄存器说明：寄存器
   详      述：保留
   UNION结构 ：无 */
#define BBPCOMM_BBC_REV4_ADDR                         (SOC_BBP_COMM_BASE_ADDR + 0x1410)

/* 寄存器说明：寄存器
   详      述：由软件直接控制SSI0 master,不借助xbbp发送回读指令时,回读指令存放地址.
   UNION结构 ：无 */
#define BBPCOMM_SSI0_RD_DATA_SOFT_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x1420)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      由软件直接控制SSI0 master,不借助xbbp发送回读指令时,回读数据有效指示
   UNION结构:  BBPCOMM_RD_END_FLAG_SSI0_SOFT_UNION */
#define BBPCOMM_RD_END_FLAG_SSI0_SOFT_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0x1424)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      由软件直接控制ssi0 master
             1:软件可以发送CFG_IND启动ssi0
             0:软件等待授权使用ssi0
   UNION结构:  BBPCOMM_SSI0_GRANT_DSP_UNION */
#define BBPCOMM_SSI0_GRANT_DSP_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0x1428)

/* 寄存器说明：寄存器
   详      述：由软件直接控制SSI0 master,不借助xbbp发送写指令时,软件配置的SSI指令值。
   UNION结构 ：无 */
#define BBPCOMM_DSP_SSI0_WDATA_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0x142C)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      由软件直接控制SSI0 master,需首先拉高此指示,屏蔽xbbp对SSI0的控制
   UNION结构:  BBPCOMM_DSP_SSI0_EN_IMI_UNION */
#define BBPCOMM_DSP_SSI0_EN_IMI_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0x1430)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      由软件直接控制SSI0 master，在ssi0_grant_dsp为1时,配置次信号产生软件启动脉冲。
   UNION结构:  BBPCOMM_DSP_SSI0_CFG_IND_IMI_UNION */
#define BBPCOMM_DSP_SSI0_CFG_IND_IMI_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x1434)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0]      由软件直接控制SSI0 master,取走回读数据后,清rd_end_flag_ssi0_soft标志位脉冲
   UNION结构:  BBPCOMM_DSP_SSI0_RD_CLR_UNION */
#define BBPCOMM_DSP_SSI0_RD_CLR_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0x1438)

/* 寄存器说明：寄存器
 bit[31:31]  保留
 bit[30:0]   LTE模天线开关软件配置值，lte_soft_antpa_en信号有效时生效
   UNION结构:  BBPCOMM_LTE_SOFT_ANTPA_SEL_UNION */
#define BBPCOMM_LTE_SOFT_ANTPA_SEL_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x1450)

/* 寄存器说明：寄存器
 bit[31:31]  保留
 bit[30:0]   W模天线开关软件配置值，w_soft_antpa_en信号有效时生效
   UNION结构:  BBPCOMM_W_SOFT_ANTPA_SEL_UNION */
#define BBPCOMM_W_SOFT_ANTPA_SEL_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x1454)

/* 寄存器说明：寄存器
 bit[31:31]  保留
 bit[30:0]   TDS模天线开关软件配置值，tds_soft_antpa_en信号有效时生效
   UNION结构:  BBPCOMM_TDS_SOFT_ANTPA_SEL_UNION */
#define BBPCOMM_TDS_SOFT_ANTPA_SEL_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x1458)

/* 寄存器说明：寄存器
 bit[31:31]  保留
 bit[30:0]   GM模天线开关软件配置值，gm_soft_antpa_en信号有效时生效
   UNION结构:  BBPCOMM_GM_SOFT_ANTPA_SEL_UNION */
#define BBPCOMM_GM_SOFT_ANTPA_SEL_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x145C)

/* 寄存器说明：寄存器
 bit[31:31]  保留
 bit[30:0]   GS模天线开关软件配置值，gs_soft_antpa_en信号有效时生效
   UNION结构:  BBPCOMM_GS_SOFT_ANTPA_SEL_UNION */
#define BBPCOMM_GS_SOFT_ANTPA_SEL_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x1460)

/* 寄存器说明：寄存器
 bit[31:31]  保留
 bit[30:0]   C2模天线开关软件配置值，c_soft_antpa_en信号有效时生效
   UNION结构:  BBPCOMM_C_SOFT_ANTPA_SEL_UNION */
#define BBPCOMM_C_SOFT_ANTPA_SEL_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x1464)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0:0]    LTE模天线开关软件配置使能,
             0:使用逻辑输入值
             1：使用软件配置值lte_soft_antpa_sel
   UNION结构:  BBPCOMM_LTE_SOFT_ANTPA_EN_UNION */
#define BBPCOMM_LTE_SOFT_ANTPA_EN_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x1468)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0:0]    W模天线开关软件配置使能,
             0:使用逻辑输入值
             1：使用软件配置值w_soft_antpa_sel
   UNION结构:  BBPCOMM_W_SOFT_ANTPA_EN_UNION */
#define BBPCOMM_W_SOFT_ANTPA_EN_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0x146C)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0:0]    TDS模天线开关软件配置使能,
             0:使用逻辑输入值
             1：使用软件配置值tds_soft_antpa_sel
   UNION结构:  BBPCOMM_TDS_SOFT_ANTPA_EN_UNION */
#define BBPCOMM_TDS_SOFT_ANTPA_EN_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x1470)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0:0]    GM模天线开关软件配置使能,
             0:使用逻辑输入值
             1：使用软件配置值gm_soft_antpa_sel
   UNION结构:  BBPCOMM_GM_SOFT_ANTPA_EN_UNION */
#define BBPCOMM_GM_SOFT_ANTPA_EN_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x1474)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0:0]    GS模天线开关软件配置使能,
             0:使用逻辑输入值
             1：使用软件配置值gs_soft_antpa_sel
   UNION结构:  BBPCOMM_GS_SOFT_ANTPA_EN_UNION */
#define BBPCOMM_GS_SOFT_ANTPA_EN_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x1478)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0:0]    C2模天线开关软件配置使能,
             0:使用逻辑输入值
             1：使用软件配置值c_soft_antpa_sel
   UNION结构:  BBPCOMM_C_SOFT_ANTPA_EN_UNION */
#define BBPCOMM_C_SOFT_ANTPA_EN_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0x147C)

/* 寄存器说明：寄存器
 bit[31:31]  通道0模式无效时软件配置的天线开关配置值是否参与通道的bit与或运算
             0：参与
             1：不参与
 bit[30:0]   通道0模式无效时软件配置的天线开关配置值
   UNION结构:  BBPCOMM_CH0_SOFT_ANTPA_SEL_UNION */
#define BBPCOMM_CH0_SOFT_ANTPA_SEL_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x1480)

/* 寄存器说明：寄存器
 bit[31:31]  通道1模式无效时软件配置的天线开关配置值是否参与通道的bit与或运算
             0：参与
             1：不参与
 bit[30:0]   通道1模式无效时软件配置的天线开关配置值
   UNION结构:  BBPCOMM_CH1_SOFT_ANTPA_SEL_UNION */
#define BBPCOMM_CH1_SOFT_ANTPA_SEL_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x1484)

/* 寄存器说明：寄存器
 bit[31:31]  通道2模式无效时软件配置的天线开关配置值是否参与通道的bit与或运算
             0：参与
             1：不参与
 bit[30:0]   通道2模式无效时软件配置的天线开关配置值
   UNION结构:  BBPCOMM_CH2_SOFT_ANTPA_SEL_UNION */
#define BBPCOMM_CH2_SOFT_ANTPA_SEL_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x1488)

/* 寄存器说明：寄存器
 bit[31:31]  通道3模式无效时软件配置的天线开关配置值是否参与通道的bit与或运算
             0：参与
             1：不参与
 bit[30:0]   通道3模式无效时软件配置的天线开关配置值
   UNION结构:  BBPCOMM_CH3_SOFT_ANTPA_SEL_UNION */
#define BBPCOMM_CH3_SOFT_ANTPA_SEL_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x148C)

/* 寄存器说明：寄存器
 bit[31:31]  保留
 bit[30:0]   4路通道输出的31比特线控对应线控相与和相或选择开关：
             1：相与
             0：相或
   UNION结构:  BBPCOMM_CH_ANTPA_BIT_AND_OR_EN_UNION */
#define BBPCOMM_CH_ANTPA_BIT_AND_OR_EN_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0x1490)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0:0]    软件检测mipi指令地址使能：
             1：打开检测功能
             0：关闭检测功能
   UNION结构:  BBPCOMM_MIPI_DET_EN_UNION */
#define BBPCOMM_MIPI_DET_EN_ADDR                      (SOC_BBP_COMM_BASE_ADDR + 0x14A0)

/* 寄存器说明：寄存器
 bit[31:12]  保留
 bit[11:8]   软件检测mipi指令slave id，4比特
 bit[7:0]    软件检测mipi写指令地址，最大8比特
   UNION结构:  BBPCOMM_MIPI_DET_ADDR_UNION */
#define BBPCOMM_MIPI_DET_ADDR_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x14A4)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0:0]    通道0软件检测mipi地址结果：
             1：检测到mipi指令发送软件配置的地址
             0：没有检测到mipi指令发送软件配置的地址
   UNION结构:  BBPCOMM_CH0_MIPI_DET_RESULT_FLAG_UNION */
#define BBPCOMM_CH0_MIPI_DET_RESULT_FLAG_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x14A8)

/* 寄存器说明：寄存器
 bit[31:23]  保留
 bit[22:22]  通道0逻辑检测到软件配置的地址后上报指令指令是否由软件配置标志
 bit[21:19]  通道0逻辑检测到软件配置的地址后上报指令指令通道id号
 bit[18:16]  通道0逻辑检测到软件配置的地址后上报指令指令类型
 bit[15:12]  通道0逻辑检测到软件配置的地址后上报指令的slave_id
 bit[11:8]   通道0逻辑检测到软件配置的地址后上报指令源来自于哪个BBP的配置
 bit[7:0]    通道0逻辑检测到软件配置的地址后上报指令的配置数据（扩展写指令只上报起始地址配置的数据）
   UNION结构:  BBPCOMM_CH0_MIPI_DET_RESULT_INFO_UNION */
#define BBPCOMM_CH0_MIPI_DET_RESULT_INFO_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x14AC)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0:0]    通道0软件检测mipi地址结果清除脉冲，写1清
   UNION结构:  BBPCOMM_CH0_MIPI_DET_RESULT_FLAG_CLR_UNION */
#define BBPCOMM_CH0_MIPI_DET_RESULT_FLAG_CLR_ADDR     (SOC_BBP_COMM_BASE_ADDR + 0x14B0)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0:0]    通道1软件检测mipi地址结果：
             1：检测到mipi指令发送软件配置的地址
             0：没有检测到mipi指令发送软件配置的地址
   UNION结构:  BBPCOMM_CH1_MIPI_DET_RESULT_FLAG_UNION */
#define BBPCOMM_CH1_MIPI_DET_RESULT_FLAG_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x14B4)

/* 寄存器说明：寄存器
 bit[31:23]  保留
 bit[22:22]  通道1逻辑检测到软件配置的地址后上报指令指令是否由软件配置标志
 bit[21:19]  通道1逻辑检测到软件配置的地址后上报指令指令通道id号
 bit[18:16]  通道1逻辑检测到软件配置的地址后上报指令指令类型
 bit[15:12]  通道1逻辑检测到软件配置的地址后上报指令的slave_id
 bit[11:8]   通道1逻辑检测到软件配置的地址后上报指令源来自于哪个BBP的配置
 bit[7:0]    通道1逻辑检测到软件配置的地址后上报指令的配置数据（扩展写指令只上报起始地址配置的数据）
   UNION结构:  BBPCOMM_CH1_MIPI_DET_RESULT_INFO_UNION */
#define BBPCOMM_CH1_MIPI_DET_RESULT_INFO_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x14B8)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0:0]    通道1软件检测mipi地址结果清除脉冲，写1清
   UNION结构:  BBPCOMM_CH1_MIPI_DET_RESULT_FLAG_CLR_UNION */
#define BBPCOMM_CH1_MIPI_DET_RESULT_FLAG_CLR_ADDR     (SOC_BBP_COMM_BASE_ADDR + 0x14BC)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0:0]    通道2软件检测mipi地址结果：
             1：检测到mipi指令发送软件配置的地址
             0：没有检测到mipi指令发送软件配置的地址
   UNION结构:  BBPCOMM_CH2_MIPI_DET_RESULT_FLAG_UNION */
#define BBPCOMM_CH2_MIPI_DET_RESULT_FLAG_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x14C0)

/* 寄存器说明：寄存器
 bit[31:23]  保留
 bit[22:22]  通道2逻辑检测到软件配置的地址后上报指令指令是否由软件配置标志
 bit[21:19]  通道2逻辑检测到软件配置的地址后上报指令指令通道id号
 bit[18:16]  通道2逻辑检测到软件配置的地址后上报指令指令类型
 bit[15:12]  通道2逻辑检测到软件配置的地址后上报指令的slave_id
 bit[11:8]   通道2逻辑检测到软件配置的地址后上报指令源来自于哪个BBP的配置
 bit[7:0]    通道2逻辑检测到软件配置的地址后上报指令的配置数据（扩展写指令只上报起始地址配置的数据）
   UNION结构:  BBPCOMM_CH2_MIPI_DET_RESULT_INFO_UNION */
#define BBPCOMM_CH2_MIPI_DET_RESULT_INFO_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x14C4)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0:0]    通道2软件检测mipi地址结果清除脉冲，写1清
   UNION结构:  BBPCOMM_CH2_MIPI_DET_RESULT_FLAG_CLR_UNION */
#define BBPCOMM_CH2_MIPI_DET_RESULT_FLAG_CLR_ADDR     (SOC_BBP_COMM_BASE_ADDR + 0x14C8)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0:0]    通道3软件检测mipi地址结果：
             1：检测到mipi指令发送软件配置的地址
             0：没有检测到mipi指令发送软件配置的地址
   UNION结构:  BBPCOMM_CH3_MIPI_DET_RESULT_FLAG_UNION */
#define BBPCOMM_CH3_MIPI_DET_RESULT_FLAG_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x14CC)

/* 寄存器说明：寄存器
 bit[31:23]  保留
 bit[22:22]  通道3逻辑检测到软件配置的地址后上报指令指令是否由软件配置标志
 bit[21:19]  通道3逻辑检测到软件配置的地址后上报指令指令通道id号
 bit[18:16]  通道3逻辑检测到软件配置的地址后上报指令指令类型
 bit[15:12]  通道3逻辑检测到软件配置的地址后上报指令的slave_id
 bit[11:8]   通道3逻辑检测到软件配置的地址后上报指令源来自于哪个BBP的配置
 bit[7:0]    通道3逻辑检测到软件配置的地址后上报指令的配置数据（扩展写指令只上报起始地址配置的数据）
   UNION结构:  BBPCOMM_CH3_MIPI_DET_RESULT_INFO_UNION */
#define BBPCOMM_CH3_MIPI_DET_RESULT_INFO_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0x14D4)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0:0]    通道3软件检测mipi地址结果清除脉冲，写1清
   UNION结构:  BBPCOMM_CH3_MIPI_DET_RESULT_FLAG_CLR_UNION */
#define BBPCOMM_CH3_MIPI_DET_RESULT_FLAG_CLR_ADDR     (SOC_BBP_COMM_BASE_ADDR + 0x14D8)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0:0]    软件检测ssi指令地址使能：
             1：打开检测功能
             0：关闭检测功能
   UNION结构:  BBPCOMM_SSI_DET_EN_UNION */
#define BBPCOMM_SSI_DET_EN_ADDR                       (SOC_BBP_COMM_BASE_ADDR + 0x14DC)

/* 寄存器说明：寄存器
 bit[31:8]   保留
 bit[7:0]    软件检测ssi写指令地址，最大8比特
   UNION结构:  BBPCOMM_SSI_DET_ADDR_UNION */
#define BBPCOMM_SSI_DET_ADDR_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x14E4)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0:0]    通道0软件检测ssi地址结果：
             1：检测到ssi指令发送软件配置的地址
             0：没有检测到ssi指令发送软件配置的地址
   UNION结构:  BBPCOMM_CH0_SSI_DET_RESULT_FLAG_UNION */
#define BBPCOMM_CH0_SSI_DET_RESULT_FLAG_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0x14E8)

/* 寄存器说明：寄存器
 bit[31:23]  保留
 bit[22:22]  通道0逻辑检测到软件配置的地址后上报指令指令是否由软件配置标志
 bit[21:20]  通道0逻辑检测到软件配置的地址后上报指令指令通道id号
 bit[19:16]  通道0逻辑检测到软件配置的地址后上报指令源来自于哪个BBP的配置
 bit[15:0]   通道0逻辑检测到软件配置的地址后上报指令的配置数据（扩展写指令只上报起始地址配置的数据）
   UNION结构:  BBPCOMM_CH0_SSI_DET_RESULT_INFO_UNION */
#define BBPCOMM_CH0_SSI_DET_RESULT_INFO_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0x14EC)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0:0]    通道0软件检测ssi地址结果清除脉冲，写1清
   UNION结构:  BBPCOMM_CH0_SSI_DET_RESULT_FLAG_CLR_UNION */
#define BBPCOMM_CH0_SSI_DET_RESULT_FLAG_CLR_ADDR      (SOC_BBP_COMM_BASE_ADDR + 0x14F0)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0:0]    通道1软件检测ssi地址结果：
             1：检测到ssi指令发送软件配置的地址
             0：没有检测到ssi指令发送软件配置的地址
   UNION结构:  BBPCOMM_CH1_SSI_DET_RESULT_FLAG_UNION */
#define BBPCOMM_CH1_SSI_DET_RESULT_FLAG_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0x14F4)

/* 寄存器说明：寄存器
 bit[31:23]  保留
 bit[22:22]  通道1逻辑检测到软件配置的地址后上报指令指令是否由软件配置标志
 bit[21:20]  通道1逻辑检测到软件配置的地址后上报指令指令通道id号
 bit[19:16]  通道1逻辑检测到软件配置的地址后上报指令源来自于哪个BBP的配置
 bit[15:0]   通道1逻辑检测到软件配置的地址后上报指令的配置数据（扩展写指令只上报起始地址配置的数据）
   UNION结构:  BBPCOMM_CH1_SSI_DET_RESULT_INFO_UNION */
#define BBPCOMM_CH1_SSI_DET_RESULT_INFO_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0x14F8)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0:0]    通道1软件检测ssi地址结果清除脉冲，写1清
   UNION结构:  BBPCOMM_CH1_SSI_DET_RESULT_FLAG_CLR_UNION */
#define BBPCOMM_CH1_SSI_DET_RESULT_FLAG_CLR_ADDR      (SOC_BBP_COMM_BASE_ADDR + 0x14FC)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0:0]    通道2软件检测ssi地址结果：
             1：检测到ssi指令发送软件配置的地址
             0：没有检测到ssi指令发送软件配置的地址
   UNION结构:  BBPCOMM_CH2_SSI_DET_RESULT_FLAG_UNION */
#define BBPCOMM_CH2_SSI_DET_RESULT_FLAG_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0x1500)

/* 寄存器说明：寄存器
 bit[31:23]  保留
 bit[22:22]  通道2逻辑检测到软件配置的地址后上报指令指令是否由软件配置标志
 bit[21:20]  通道2逻辑检测到软件配置的地址后上报指令指令通道id号
 bit[19:16]  通道2逻辑检测到软件配置的地址后上报指令源来自于哪个BBP的配置
 bit[15:0]   通道2逻辑检测到软件配置的地址后上报指令的配置数据（扩展写指令只上报起始地址配置的数据）
   UNION结构:  BBPCOMM_CH2_SSI_DET_RESULT_INFO_UNION */
#define BBPCOMM_CH2_SSI_DET_RESULT_INFO_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0x1504)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0:0]    通道2软件检测ssi地址结果清除脉冲，写1清
   UNION结构:  BBPCOMM_CH2_SSI_DET_RESULT_FLAG_CLR_UNION */
#define BBPCOMM_CH2_SSI_DET_RESULT_FLAG_CLR_ADDR      (SOC_BBP_COMM_BASE_ADDR + 0x1508)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0:0]    通道3软件检测ssi地址结果：
             1：检测到ssi指令发送软件配置的地址
             0：没有检测到ssi指令发送软件配置的地址
   UNION结构:  BBPCOMM_CH3_SSI_DET_RESULT_FLAG_UNION */
#define BBPCOMM_CH3_SSI_DET_RESULT_FLAG_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0x150C)

/* 寄存器说明：寄存器
 bit[31:23]  保留
 bit[22:22]  通道3逻辑检测到软件配置的地址后上报指令指令是否由软件配置标志
 bit[21:20]  通道3逻辑检测到软件配置的地址后上报指令指令通道id号
 bit[19:16]  通道3逻辑检测到软件配置的地址后上报指令源来自于哪个BBP的配置
 bit[15:0]   通道3逻辑检测到软件配置的地址后上报指令的配置数据（扩展写指令只上报起始地址配置的数据）
   UNION结构:  BBPCOMM_CH3_SSI_DET_RESULT_INFO_UNION */
#define BBPCOMM_CH3_SSI_DET_RESULT_INFO_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0x1510)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0:0]    通道3软件检测ssi地址结果清除脉冲，写1清
   UNION结构:  BBPCOMM_CH3_SSI_DET_RESULT_FLAG_CLR_UNION */
#define BBPCOMM_CH3_SSI_DET_RESULT_FLAG_CLR_ADDR      (SOC_BBP_COMM_BASE_ADDR + 0x1514)

/* 寄存器说明：寄存器
 bit[31:26]  保留
 bit[25:0]   可维可测轮询请求上报信号使能，dbg_req_en[25:0]对应reg[25:0],如dbg_req_en[X]为1，reg[X]请求有效，dbg_req_en[X]为0，reg[X]请求无效,
             X=0~25
   UNION结构:  BBPCOMM_DBG_REQ_EN_UNION */
#define BBPCOMM_DBG_REQ_EN_ADDR                       (SOC_BBP_COMM_BASE_ADDR + 0x1518)

/* 寄存器说明：寄存器
   详      述：
   UNION结构 ：无 */
#define BBPCOMM_DBG_REG0_CPU_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x151C)

/* 寄存器说明：寄存器
   详      述：
   UNION结构 ：无 */
#define BBPCOMM_DBG_REG1_CPU_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x1520)

/* 寄存器说明：寄存器
   详      述：
   UNION结构 ：无 */
#define BBPCOMM_DBG_REG2_CPU_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x1524)

/* 寄存器说明：寄存器
   详      述：
   UNION结构 ：无 */
#define BBPCOMM_DBG_REG3_CPU_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x1528)

/* 寄存器说明：寄存器
   详      述：
   UNION结构 ：无 */
#define BBPCOMM_DBG_REG4_CPU_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x152C)

/* 寄存器说明：寄存器
   详      述：
   UNION结构 ：无 */
#define BBPCOMM_DBG_REG5_CPU_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x1530)

/* 寄存器说明：寄存器
   详      述：
   UNION结构 ：无 */
#define BBPCOMM_DBG_REG6_CPU_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x1534)

/* 寄存器说明：寄存器
   详      述：
   UNION结构 ：无 */
#define BBPCOMM_DBG_REG7_CPU_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x1538)

/* 寄存器说明：寄存器
   详      述：
   UNION结构 ：无 */
#define BBPCOMM_DBG_REG8_CPU_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x153C)

/* 寄存器说明：寄存器
   详      述：
   UNION结构 ：无 */
#define BBPCOMM_DBG_REG9_CPU_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x1540)

/* 寄存器说明：寄存器
   详      述：
   UNION结构 ：无 */
#define BBPCOMM_DBG_REG10_CPU_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x1548)

/* 寄存器说明：寄存器
   详      述：
   UNION结构 ：无 */
#define BBPCOMM_DBG_REG11_CPU_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x154C)

/* 寄存器说明：寄存器
   详      述：
   UNION结构 ：无 */
#define BBPCOMM_DBG_REG12_CPU_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x1550)

/* 寄存器说明：寄存器
   详      述：
   UNION结构 ：无 */
#define BBPCOMM_DBG_REG13_CPU_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x1554)

/* 寄存器说明：寄存器
   详      述：
   UNION结构 ：无 */
#define BBPCOMM_DBG_REG14_CPU_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x1558)

/* 寄存器说明：寄存器
   详      述：
   UNION结构 ：无 */
#define BBPCOMM_DBG_REG15_CPU_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x155C)

/* 寄存器说明：寄存器
   详      述：
   UNION结构 ：无 */
#define BBPCOMM_DBG_REG16_CPU_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x1560)

/* 寄存器说明：寄存器
   详      述：
   UNION结构 ：无 */
#define BBPCOMM_DBG_REG17_CPU_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x1564)

/* 寄存器说明：寄存器
   详      述：
   UNION结构 ：无 */
#define BBPCOMM_DBG_REG18_CPU_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x1568)

/* 寄存器说明：寄存器
   详      述：
   UNION结构 ：无 */
#define BBPCOMM_DBG_REG19_CPU_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x156C)

/* 寄存器说明：寄存器
   详      述：
   UNION结构 ：无 */
#define BBPCOMM_DBG_REG20_CPU_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x1570)

/* 寄存器说明：寄存器
   详      述：
   UNION结构 ：无 */
#define BBPCOMM_DBG_REG21_CPU_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x1574)

/* 寄存器说明：寄存器
   详      述：
   UNION结构 ：无 */
#define BBPCOMM_DBG_REG22_CPU_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x1578)

/* 寄存器说明：寄存器
   详      述：
   UNION结构 ：无 */
#define BBPCOMM_DBG_REG23_CPU_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x157C)

/* 寄存器说明：寄存器
   详      述：
   UNION结构 ：无 */
#define BBPCOMM_DBG_REG24_CPU_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x1580)

/* 寄存器说明：寄存器
   详      述：
   UNION结构 ：无 */
#define BBPCOMM_DBG_REG25_CPU_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x1584)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0:0]    19.2M钟自由计数软初始值设置使能。
             
   UNION结构:  BBPCOMM_FREE_COUNT_EN_UNION */
#define BBPCOMM_FREE_COUNT_EN_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x1588)

/* 寄存器说明：寄存器
   详      述：19.2M钟自由计数软初始配置值，free_count_en为1时生效。
   UNION结构 ：无 */
#define BBPCOMM_FREE_COUNT_INIT_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0x158C)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0:0]    BBP_COMMON输出给LTE模反压busy信号的软复位信号
             1：软复位反压busy信号
             0：不软复位反压busy信号
   UNION结构:  BBPCOMM_LTE_SOFT_RST_UNION */
#define BBPCOMM_LTE_SOFT_RST_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x1590)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0:0]    BBP_COMMON输出给W模反压busy信号的软复位信号
             1：软复位反压busy信号
             0：不软复位反压busy信号
   UNION结构:  BBPCOMM_W_SOFT_RST_UNION */
#define BBPCOMM_W_SOFT_RST_ADDR                       (SOC_BBP_COMM_BASE_ADDR + 0x1594)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0:0]    BBP_COMMON输出给TDS模反压busy信号的软复位信号
             1：软复位反压busy信号
             0：不软复位反压busy信号
   UNION结构:  BBPCOMM_TDS_SOFT_RST_UNION */
#define BBPCOMM_TDS_SOFT_RST_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x1598)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0:0]    BBP_COMMON输出给GM模反压busy信号的软复位信号
             1：软复位反压busy信号
             0：不软复位反压busy信号
   UNION结构:  BBPCOMM_GM_SOFT_RST_UNION */
#define BBPCOMM_GM_SOFT_RST_ADDR                      (SOC_BBP_COMM_BASE_ADDR + 0x159C)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0:0]    BBP_COMMON输出给GS模反压busy信号的软复位信号
             1：软复位反压busy信号
             0：不软复位反压busy信号
   UNION结构:  BBPCOMM_GS_SOFT_RST_UNION */
#define BBPCOMM_GS_SOFT_RST_ADDR                      (SOC_BBP_COMM_BASE_ADDR + 0x15A0)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0:0]    BBP_COMMON输出给C2模反压busy信号的软复位信号
             1：软复位反压busy信号
             0：不软复位反压busy信号
   UNION结构:  BBPCOMM_C_SOFT_RST_UNION */
#define BBPCOMM_C_SOFT_RST_ADDR                       (SOC_BBP_COMM_BASE_ADDR + 0x15A4)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0:0]    tcvr_on输出pin脚0信号源选择开关：
             0：来自于通道0的逻辑选择输出；
             1：来自于软件配置输出；
   UNION结构:  BBPCOMM_TCVR_ON_CFG_OUT0_UNION */
#define BBPCOMM_TCVR_ON_CFG_OUT0_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x15A8)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0:0]    tcvr_on输出pin脚1信号源选择开关：
             0：来自于通道0的逻辑选择输出；
             1：来自于软件配置输出；
   UNION结构:  BBPCOMM_TCVR_ON_CFG_OUT1_UNION */
#define BBPCOMM_TCVR_ON_CFG_OUT1_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x15AC)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0:0]    软件配置LTE模tcvr_on信号控制外围
             pin脚0的tcvr_on信号输出
             配置1为拉高，0为拉低
   UNION结构:  BBPCOMM_LTE_TCVR_ON_CFG_PIN0_UNION */
#define BBPCOMM_LTE_TCVR_ON_CFG_PIN0_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x15B0)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0:0]    软件配置W模tcvr_on信号控制外围
             pin脚0的tcvr_on信号输出
             配置1为拉高，0为拉低
   UNION结构:  BBPCOMM_W_TCVR_ON_CFG_PIN0_UNION */
#define BBPCOMM_W_TCVR_ON_CFG_PIN0_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x15B4)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0:0]    软件配置TDS模tcvr_on信号控制外围
             pin脚0的tcvr_on信号输出
             配置1为拉高，0为拉低
   UNION结构:  BBPCOMM_TDS_TCVR_ON_CFG_PIN0_UNION */
#define BBPCOMM_TDS_TCVR_ON_CFG_PIN0_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x15B8)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0:0]    软件配置GM模tcvr_on信号控制外围
             pin脚0的tcvr_on信号输出
             配置1为拉高，0为拉低
   UNION结构:  BBPCOMM_GM_TCVR_ON_CFG_PIN0_UNION */
#define BBPCOMM_GM_TCVR_ON_CFG_PIN0_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x15BC)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0:0]    软件配置GS模tcvr_on信号控制外围
             pin脚0的tcvr_on信号输出
             配置1为拉高，0为拉低
   UNION结构:  BBPCOMM_GS_TCVR_ON_CFG_PIN0_UNION */
#define BBPCOMM_GS_TCVR_ON_CFG_PIN0_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x15C0)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0:0]    软件配置C2模tcvr_on信号控制外围
             pin脚0的tcvr_on信号输出
             配置1为拉高，0为拉低
   UNION结构:  BBPCOMM_C_TCVR_ON_CFG_PIN0_UNION */
#define BBPCOMM_C_TCVR_ON_CFG_PIN0_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x15C4)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0:0]    软件配置LTE模tcvr_on信号控制外围
             pin脚1的tcvr_on信号输出
             配置1为拉高，0为拉低
   UNION结构:  BBPCOMM_LTE_TCVR_ON_CFG_PIN1_UNION */
#define BBPCOMM_LTE_TCVR_ON_CFG_PIN1_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x15C8)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0:0]    软件配置W模tcvr_on信号控制外围
             pin脚1的tcvr_on信号输出
             配置1为拉高，0为拉低
   UNION结构:  BBPCOMM_W_TCVR_ON_CFG_PIN1_UNION */
#define BBPCOMM_W_TCVR_ON_CFG_PIN1_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x15CC)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0:0]    软件配置TDS模tcvr_on信号控制外围
             pin脚1的tcvr_on信号输出
             配置1为拉高，0为拉低
   UNION结构:  BBPCOMM_TDS_TCVR_ON_CFG_PIN1_UNION */
#define BBPCOMM_TDS_TCVR_ON_CFG_PIN1_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0x15D0)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0:0]    软件配置GM模tcvr_on信号控制外围
             pin脚1的tcvr_on信号输出
             配置1为拉高，0为拉低
   UNION结构:  BBPCOMM_GM_TCVR_ON_CFG_PIN1_UNION */
#define BBPCOMM_GM_TCVR_ON_CFG_PIN1_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x15D4)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0:0]    软件配置GS模tcvr_on信号控制外围
             pin脚1的tcvr_on信号输出
             配置1为拉高，0为拉低
   UNION结构:  BBPCOMM_GS_TCVR_ON_CFG_PIN1_UNION */
#define BBPCOMM_GS_TCVR_ON_CFG_PIN1_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0x15D8)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0:0]    软件配置C2模tcvr_on信号控制外围
             pin脚1的tcvr_on信号输出
             配置1为拉高，0为拉低
   UNION结构:  BBPCOMM_C_TCVR_ON_CFG_PIN1_UNION */
#define BBPCOMM_C_TCVR_ON_CFG_PIN1_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x15DC)

/* 寄存器说明：寄存器
 bit[31:6]   保留
 bit[5:0]    各通道实际输出tcvr_on延迟的配置值，
             最大支持64个cycle，单位为19.2M钟
   UNION结构:  BBPCOMM_TCVR_ON_DLY_CYCLE_UNION */
#define BBPCOMM_TCVR_ON_DLY_CYCLE_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x15E0)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0:0]    寄存器模块时钟门控选择：
             0：时钟门控
             1：时钟常开
   UNION结构:  BBPCOMM_REG_CLK_SEL_UNION */
#define BBPCOMM_REG_CLK_SEL_ADDR                      (SOC_BBP_COMM_BASE_ADDR + 0x15E4)

/* 寄存器说明：寄存器
 bit[31:4]   保留
 bit[3:3]    通道3的tuner mipi自动交换功能屏蔽寄存器
             0：使用tuner输出结果
             1：bypass tuner输出结果，tuner mipi指令不能从CTU通道3输出
 bit[2:2]    通道2的tuner mipi自动交换功能屏蔽寄存器
             0：使用tuner输出结果
             1：bypass tuner输出结果，tuner mipi指令不能从CTU通道2输出
 bit[1:1]    通道1的tuner mipi自动交换功能屏蔽寄存器
             0：使用tuner输出结果
             1：bypass tuner输出结果，tuner mipi指令不能从CTU通道1输出
 bit[0:0]    通道0的tuner mipi自动交换功能屏蔽寄存器
             0：使用tuner输出结果
             1：bypass tuner输出结果，tuner mipi指令不能从CTU通道0输出
   UNION结构:  BBPCOMM_TUNER_MIPI_MASK_UNION */
#define BBPCOMM_TUNER_MIPI_MASK_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0x15E8)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0:0]    tuner gpio m0_line_p线控屏蔽寄存器
             0：使用tuner输出值
             1：bypass tuner输出值，使用CTU输出值
   UNION结构:  BBPCOMM_TNNER_GPIO_M0_LINE_P_MASK_UNION */
#define BBPCOMM_TNNER_GPIO_M0_LINE_P_MASK_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0x15EC)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0:0]    tuner gpio m0_line_s线控屏蔽寄存器
             0：使用tuner输出值
             1：bypass tuner输出值，使用CTU输出值
   UNION结构:  BBPCOMM_TNNER_GPIO_M0_LINE_S_MASK_UNION */
#define BBPCOMM_TNNER_GPIO_M0_LINE_S_MASK_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0x15F0)

/* 寄存器说明：寄存器
 bit[31:1]   保留
 bit[0:0]    tuner gpio m1_line线控屏蔽寄存器
             0：使用tuner输出值
             1：bypass tuner输出值，使用CTU输出值
   UNION结构:  BBPCOMM_TNNER_GPIO_M1_LINE_MASK_UNION */
#define BBPCOMM_TNNER_GPIO_M1_LINE_MASK_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0x15F4)

/* 寄存器说明：寄存器
 bit[31:27]  保留
 bit[26:0]   BBC上行行时钟工作状态指示：
             bit0:abb接收通道0随路时钟工作状态指示；
             bit1:abb接收通道1随路时钟工作状态指示；
             bit2:abb接收通道2随路时钟工作状态指示；
             bit3:abb接收通道3随路时钟工作状态指示；
             bit4:lte_ch0下行接收时钟工作状态指示；
             bit5:lte_ch1下行接收时钟工作状态指示；
             bit6:lte_ch2下行接收时钟工作状态指示；
             bit7:lte_ch3下行接收时钟工作状态指示；
             bit8:W下行接收时钟工作状态指示；
             bit9:TDS下行接收时钟工作状态指示；
             bit10:GM下行接收时钟工作状态指示；
             bit11:GS下行接收时钟工作状态指示；
             bit12:C下行接收时钟工作状态指示；
             bit13~bit15：reserved；
             bit16:abb发送通道0随路时钟工作状态指示；
             bit17:abb发送通道1随路时钟工作状态指示；
             bit18~bit19：reserved；
             bit20:lte_ch0上行发送时钟工作状态指示；
             bit21:lte_ch1上行发送时钟工作状态指示；
             bit22:W上行发送时钟工作状态指示；
             bit23:TDS上行发送时钟工作状态指示；
             bit24:GM上行发送时钟工作状态指示；
             bit25:GS上行发送时钟工作状态指示；
             bit26:C上行发送时钟工作状态指示；
             bit27~bit31：reserved；
   UNION结构:  BBPCOMM_BBC_TX_RX_CLK_FLAG_UNION */
#define BBPCOMM_BBC_TX_RX_CLK_FLAG_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0x15F8)

/* 寄存器说明：寄存器
 bit[31:18]  保留
 bit[17]     C2 MIPI 忙标志
 bit[16]     GS MIPI 忙标志
 bit[15]     GM MIPI 忙标志
 bit[14]     TDS MIPI 忙标志
 bit[13]     W MIPI 忙标志
 bit[12]     LTE CH3 MIPI 忙标志
 bit[11]     LTE CH2 MIPI 忙标志
 bit[10]     LTE CH1 MIPI 忙标志
 bit[9]      LTE CH0 MIPI 忙标志
 bit[8]      C2 SSI 忙标志
 bit[7]      GS SSI 忙标志
 bit[6]      GM  SSI 忙标志
 bit[5]      TDS  SSI 忙标志
 bit[4]      W SSI 忙标志
 bit[3]      LTE CH3 SSI 忙标志
 bit[2]      LTE CH2 SSI 忙标志
 bit[1]      LTE CH1 SSI 忙标志
 bit[0]      LTE CH0 SSI 忙标志
   UNION结构:  BBPCOMM_MIPI_SSI_STATE_UNION */
#define BBPCOMM_MIPI_SSI_STATE_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0x15FC)



/***======================================================================***
                     (2/3) register_define_mipi_tuner
 ***======================================================================***/
/* 寄存器说明：
 bit[31:5]   
 bit[4]      MIPI_tuner模块
 bit[3:1]    
 bit[0]      MIPI_TUNER模块使能开关，0表示关闭，1表示打开。
   UNION结构:  BBPCOMM_MIPI_TUNER_EN_UNION */
#define BBPCOMM_MIPI_TUNER_EN_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x6600)

/* 寄存器说明：
 bit[31:9]   
 bit[8]      副卡线控使能开关，0表示关闭，1表示打开。
 bit[7]      副卡主卡使能开关，0表示关闭，1表示打开。
 bit[6]      副卡TAS切换使能开关，0表示关闭，1表示打开。
 bit[5]      主卡辅载波线控切换使能开关，0表示关闭，1表示打开。
 bit[4]      主卡辅载波副卡有效使能开关，0表示关闭，1表示打开。
 bit[3]      主卡辅载波TAS切换使能开关，0表示关闭，1表示打开。
 bit[2]      主卡主载波线控切换使能开关，0表示关闭，1表示打开。
 bit[1]      主卡主载波副卡有效使能开关，0表示关闭，1表示打开。
 bit[0]      主卡主载波TAS切换使能开关，0表示关闭，1表示打开。
   UNION结构:  BBPCOMM_MIPI_TUNER_REQ_EN_UNION */
#define BBPCOMM_MIPI_TUNER_REQ_EN_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0x6604)

/* 寄存器说明：
   详      述：GPIO最近轮询序列上报
   UNION结构 ：无 */
#define BBPCOMM_REQ_NUM_RPT_GPIO_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x6608)

/* 寄存器说明：
 bit[31:16]  
 bit[15:0]   状态机超时计时器
   UNION结构:  BBPCOMM_MIPI_OT_CNT_UNION */
#define BBPCOMM_MIPI_OT_CNT_ADDR                      (SOC_BBP_COMM_BASE_ADDR + 0x6610)

/* 寄存器说明：
 bit[31:3]   
 bit[2]      轮询状态上报
 bit[1]      轮询状态上报
 bit[0]      轮询状态上报
   UNION结构:  BBPCOMM_QUEUE_BUSY_IND_UNION */
#define BBPCOMM_QUEUE_BUSY_IND_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0x6614)

/* 寄存器说明：
 bit[31:26]  
 bit[25]     m1 fifo状态上报
 bit[24]     m1 fifo状态上报
 bit[23:16]  m1当前状态值
 bit[15]     m0_s fifo状态上报
 bit[14]     m0_s fifo状态上报
 bit[13:8]   m0_s当前状态值
 bit[7]      m0_p fifo状态上报
 bit[6]      m0_p fifo状态上报
 bit[5:0]    m0_p当前状态值
   UNION结构:  BBPCOMM_M_GEN_RPT_UNION */
#define BBPCOMM_M_GEN_RPT_ADDR                        (SOC_BBP_COMM_BASE_ADDR + 0x6618)

/* 寄存器说明：
   详      述：最近轮询序列上报
   UNION结构 ：无 */
#define BBPCOMM_REQ_NUM_RPT_MIPI_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0x661C)

/* 寄存器说明：
 bit[31:2]   
 bit[1:0]    查表状态机上报
   UNION结构:  BBPCOMM_LUT_FSM_RPT_UNION */
#define BBPCOMM_LUT_FSM_RPT_ADDR                      (SOC_BBP_COMM_BASE_ADDR + 0x6620)

/* 寄存器说明：
 bit[31:16]  DFT MEM cpu接口配置
 bit[15:0]   DFT MEM cpu接口配置
   UNION结构:  BBPCOMM_DFT_MEM_CTRL1_UNION */
#define BBPCOMM_DFT_MEM_CTRL1_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x6624)

/* 寄存器说明：
 bit[31:24]  
 bit[23:16]  DFT MEM cpu接口配置
 bit[15:0]   DFT MEM cpu接口配置
   UNION结构:  BBPCOMM_DFT_MEM_CTRL2_UNION */
#define BBPCOMM_DFT_MEM_CTRL2_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0x6628)

/* 寄存器说明：
 bit[31:5]   
 bit[4]      在cpu配置GPIO cross开关为1的情况下，该位域配置为0，则GPIO不做CROSS直通输出，当前只支持该信号配置为0
 bit[3:1]    
 bit[0]      cpu配置GPIO cross开关，1：CPU配置，当前CPU配置下用于默认场景下的GPIO直通情况。
             0：TAS_IND 自动控制GPIO CROSS
   UNION结构:  BBPCOMM_GPIO_M0_LINE_CROSS_EN_UNION */
#define BBPCOMM_GPIO_M0_LINE_CROSS_EN_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0x662C)

/* 寄存器说明：
 bit[31:1]   
 bit[0]      状态机超时计时器
   UNION结构:  BBPCOMM_FSM_OT_PRRT_EN_UNION */
#define BBPCOMM_FSM_OT_PRRT_EN_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0x6630)



/***======================================================================***
                     (3/3) register_define_mipi_tuner_mem
 ***======================================================================***/
/* 寄存器说明：mipi 查表RAM
   详      述：MIPI表单，地址为0xE1F84000 - 0xE1F863FC
               为MIPI数据表，MIPI查表遇到表单内容全0退出，所以软件配置的时候，该表所有空间都需要配置，不想使用的地址写0
   UNION结构 ：无 */
#define BBPCOMM_MIPI_LUT_RAM_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x4000)
#define BBPCOMM_MIPI_LUT_RAM_MEMDEPTH  (2304)

/* 寄存器说明：gpio 查表RAM
   详      述：GPIO表单，地址为0xE1F86400-0xE1F8657C
   UNION结构 ：无 */
#define BBPCOMM_GPIO_LUT_RAM_ADDR                     (SOC_BBP_COMM_BASE_ADDR + 0x6400)
#define BBPCOMM_GPIO_LUT_RAM_MEMDEPTH  (96)





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
                     (1/3) register_define_ctu
 ***======================================================================***/
/*****************************************************************************
 结构名    : BBPCOMM_C0_PRIMARY_MODE_IND_RX_UNION
 结构说明  : C0_PRIMARY_MODE_IND_RX 寄存器结构定义。地址偏移量:0x0000，初值:0x00000007，宽度:32
 寄存器说明: 接收通道0对应主模（主模0）的模式指示寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c0_primary_mode_ind_rx_reg;
    struct
    {
        unsigned int  c0_primary_mode_ind_rx : 3;  /* bit[0-2] : 接收通道0对应的主模（定义为主模0）的模式配置指示：
                                                                 000：LTE 主模。
                                                                 001：W主模。
                                                                 010：TDS主模。
                                                                 011：Gm主模；
                                                                 100：Gs主模；
                                                                 101:C2主模；
                                                                 110~111：无效。
                                                                 配置时刻：各模根据通信场景配置 */
        unsigned int  reserved               : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_C0_PRIMARY_MODE_IND_RX_UNION;
#define BBPCOMM_C0_PRIMARY_MODE_IND_RX_c0_primary_mode_ind_rx_START  (0)
#define BBPCOMM_C0_PRIMARY_MODE_IND_RX_c0_primary_mode_ind_rx_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_C0_SECOND_MODE_IND_UNION
 结构说明  : C0_SECOND_MODE_IND 寄存器结构定义。地址偏移量:0x0004，初值:0x00000007，宽度:32
 寄存器说明: 主模0对应的从模（从模0）的模式指示寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c0_second_mode_ind_reg;
    struct
    {
        unsigned int  c0_second_mode_ind : 3;  /* bit[0-2] : 接收主模0对应的从模（定义为从模0）的模式配置指示：
                                                             000：LTE从模。
                                                             001：W 从模。
                                                             010：TDS从模。
                                                             011：Gm从模；
                                                             100：Gs从模；
                                                             101:C2从模；
                                                             110~111：无效。
                                                             配置时刻：各模根据通信场景配置 */
        unsigned int  reserved           : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_C0_SECOND_MODE_IND_UNION;
#define BBPCOMM_C0_SECOND_MODE_IND_c0_second_mode_ind_START  (0)
#define BBPCOMM_C0_SECOND_MODE_IND_c0_second_mode_ind_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_C0_PRIMARY_MODE_IND_TX_UNION
 结构说明  : C0_PRIMARY_MODE_IND_TX 寄存器结构定义。地址偏移量:0x0008，初值:0x00000007，宽度:32
 寄存器说明: 发送通道0对应的模式指示寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c0_primary_mode_ind_tx_reg;
    struct
    {
        unsigned int  c0_primary_mode_ind_tx : 3;  /* bit[0-2] : 发送通道0对应的模式配置指示：
                                                                 000：LTE 主模。
                                                                 001：W主模。
                                                                 010：TDS主模。
                                                                 011：Gm主模；
                                                                 100：Gs主模；
                                                                 101:C2主模；
                                                                 110~111：无效。
                                                                 配置时刻：各模根据通信场景配置 */
        unsigned int  reserved               : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_C0_PRIMARY_MODE_IND_TX_UNION;
#define BBPCOMM_C0_PRIMARY_MODE_IND_TX_c0_primary_mode_ind_tx_START  (0)
#define BBPCOMM_C0_PRIMARY_MODE_IND_TX_c0_primary_mode_ind_tx_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_C0_SECOND_AFC_MODE_UNION
 结构说明  : C0_SECOND_AFC_MODE 寄存器结构定义。地址偏移量:0x0010，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c0_second_afc_mode_reg;
    struct
    {
        unsigned int  c0_second_afc_mode : 1;  /* bit[0]   : 0:通道0从模使用通道0主模afc控制字
                                                             1:通道0从模使用通道0从模afc控制字 */
        unsigned int  reserved           : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_C0_SECOND_AFC_MODE_UNION;
#define BBPCOMM_C0_SECOND_AFC_MODE_c0_second_afc_mode_START  (0)
#define BBPCOMM_C0_SECOND_AFC_MODE_c0_second_afc_mode_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_C1_PRIMARY_MODE_IND_RX_UNION
 结构说明  : C1_PRIMARY_MODE_IND_RX 寄存器结构定义。地址偏移量:0x020，初值:0x00000007，宽度:32
 寄存器说明: 接收通道1对应主模（主模1）的模式指示寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c1_primary_mode_ind_rx_reg;
    struct
    {
        unsigned int  c1_primary_mode_ind_rx : 3;  /* bit[0-2] : 接收通道1对应的主模（定义为主模1）的模式配置指示：
                                                                 000：LTE 主模。
                                                                 001：W主模。
                                                                 010：TDS主模。
                                                                 011：Gm主模；
                                                                 100：Gs主模；
                                                                 101:C2主模；
                                                                 110~111：无效。
                                                                 配置时刻：各模根据通信场景配置 */
        unsigned int  reserved               : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_C1_PRIMARY_MODE_IND_RX_UNION;
#define BBPCOMM_C1_PRIMARY_MODE_IND_RX_c1_primary_mode_ind_rx_START  (0)
#define BBPCOMM_C1_PRIMARY_MODE_IND_RX_c1_primary_mode_ind_rx_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_C1_SECOND_MODE_IND_UNION
 结构说明  : C1_SECOND_MODE_IND 寄存器结构定义。地址偏移量:0x024，初值:0x00000007，宽度:32
 寄存器说明: 主模1对应的从模（从模1）的模式指示寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c1_second_mode_ind_reg;
    struct
    {
        unsigned int  c1_second_mode_ind : 3;  /* bit[0-2] : 接收主模1对应的从模（定义为从模1）的模式配置指示：
                                                             000：LTE从模。
                                                             001：W 从模。
                                                             010：TDS从模。
                                                             011：Gm从模；
                                                             100：Gs从模；
                                                             101:C2从模；
                                                             110~111：无效。
                                                             配置时刻：各模根据通信场景配置 */
        unsigned int  reserved           : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_C1_SECOND_MODE_IND_UNION;
#define BBPCOMM_C1_SECOND_MODE_IND_c1_second_mode_ind_START  (0)
#define BBPCOMM_C1_SECOND_MODE_IND_c1_second_mode_ind_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_C1_PRIMARY_MODE_IND_TX_UNION
 结构说明  : C1_PRIMARY_MODE_IND_TX 寄存器结构定义。地址偏移量:0x028，初值:0x00000007，宽度:32
 寄存器说明: 发送通道1对应的模式指示寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c1_primary_mode_ind_tx_reg;
    struct
    {
        unsigned int  c1_primary_mode_ind_tx : 3;  /* bit[0-2] : 发送通道1对应的模式配置指示：
                                                                 000：LTE 主模。
                                                                 001：W主模。
                                                                 010：TDS主模。
                                                                 011：Gm主模；
                                                                 100：Gs主模；
                                                                 101:C2主模；
                                                                 110~111：无效。
                                                                 配置时刻：各模根据通信场景配置 */
        unsigned int  reserved               : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_C1_PRIMARY_MODE_IND_TX_UNION;
#define BBPCOMM_C1_PRIMARY_MODE_IND_TX_c1_primary_mode_ind_tx_START  (0)
#define BBPCOMM_C1_PRIMARY_MODE_IND_TX_c1_primary_mode_ind_tx_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_C1_SECOND_AFC_MODE_UNION
 结构说明  : C1_SECOND_AFC_MODE 寄存器结构定义。地址偏移量:0x0030，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c1_second_afc_mode_reg;
    struct
    {
        unsigned int  c1_second_afc_mode : 1;  /* bit[0]   : 0:通道1从模使用通道1主模afc控制字
                                                             1:通道1从模使用通道1从模afc控制字 */
        unsigned int  reserved           : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_C1_SECOND_AFC_MODE_UNION;
#define BBPCOMM_C1_SECOND_AFC_MODE_c1_second_afc_mode_START  (0)
#define BBPCOMM_C1_SECOND_AFC_MODE_c1_second_afc_mode_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_C2_PRIMARY_MODE_IND_RX_UNION
 结构说明  : C2_PRIMARY_MODE_IND_RX 寄存器结构定义。地址偏移量:0x0040，初值:0x00000007，宽度:32
 寄存器说明: 接收通道2对应主模（主模2）的模式指示寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c2_primary_mode_ind_rx_reg;
    struct
    {
        unsigned int  c2_primary_mode_ind_rx : 3;  /* bit[0-2] : 接收通道2对应的主模（定义为主模2）的模式配置指示：
                                                                 000：LTE 主模。
                                                                 001：W主模。
                                                                 010：TDS主模。
                                                                 011：Gm主模；
                                                                 100：Gs主模；
                                                                 101:C2主模；
                                                                 110~111：无效。
                                                                 配置时刻：各模根据通信场景配置 */
        unsigned int  reserved               : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_C2_PRIMARY_MODE_IND_RX_UNION;
#define BBPCOMM_C2_PRIMARY_MODE_IND_RX_c2_primary_mode_ind_rx_START  (0)
#define BBPCOMM_C2_PRIMARY_MODE_IND_RX_c2_primary_mode_ind_rx_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_C2_SECOND_MODE_IND_UNION
 结构说明  : C2_SECOND_MODE_IND 寄存器结构定义。地址偏移量:0x0044，初值:0x00000007，宽度:32
 寄存器说明: 主模2对应的从模（从模2）的模式指示寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c2_second_mode_ind_reg;
    struct
    {
        unsigned int  c2_second_mode_ind : 3;  /* bit[0-2] : 接收主模2对应的从模（定义为从模2）的模式配置指示：
                                                             000：LTE从模。
                                                             001：W 从模。
                                                             010：TDS从模。
                                                             011：Gm从模；
                                                             100：Gs从模；
                                                             101:C2从模；
                                                             110~111：无效。
                                                             配置时刻：各模根据通信场景配置 */
        unsigned int  reserved           : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_C2_SECOND_MODE_IND_UNION;
#define BBPCOMM_C2_SECOND_MODE_IND_c2_second_mode_ind_START  (0)
#define BBPCOMM_C2_SECOND_MODE_IND_c2_second_mode_ind_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_C2_PRIMARY_MODE_IND_TX_UNION
 结构说明  : C2_PRIMARY_MODE_IND_TX 寄存器结构定义。地址偏移量:0x0048，初值:0x00000007，宽度:32
 寄存器说明: 发送通道2对应的模式指示寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c2_primary_mode_ind_tx_reg;
    struct
    {
        unsigned int  c2_primary_mode_ind_tx : 3;  /* bit[0-2] : 发送通道2对应的模式配置指示：
                                                                 000：LTE 主模。
                                                                 001：W主模。
                                                                 010：TDS主模。
                                                                 011：Gm主模；
                                                                 100：Gs主模；
                                                                 101:C2主模；
                                                                 110~111：无效。
                                                                 配置时刻：各模根据通信场景配置 */
        unsigned int  reserved               : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_C2_PRIMARY_MODE_IND_TX_UNION;
#define BBPCOMM_C2_PRIMARY_MODE_IND_TX_c2_primary_mode_ind_tx_START  (0)
#define BBPCOMM_C2_PRIMARY_MODE_IND_TX_c2_primary_mode_ind_tx_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_C2_SECOND_AFC_MODE_UNION
 结构说明  : C2_SECOND_AFC_MODE 寄存器结构定义。地址偏移量:0x0050，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c2_second_afc_mode_reg;
    struct
    {
        unsigned int  c2_second_afc_mode : 1;  /* bit[0]   : 0:通道2从模使用通道2主模afc控制字
                                                             1:通道2从模使用通道2从模afc控制字 */
        unsigned int  reserved           : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_C2_SECOND_AFC_MODE_UNION;
#define BBPCOMM_C2_SECOND_AFC_MODE_c2_second_afc_mode_START  (0)
#define BBPCOMM_C2_SECOND_AFC_MODE_c2_second_afc_mode_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_C3_PRIMARY_MODE_IND_RX_UNION
 结构说明  : C3_PRIMARY_MODE_IND_RX 寄存器结构定义。地址偏移量:0x0060，初值:0x00000007，宽度:32
 寄存器说明: 接收通道3对应主模（主模3）的模式指示寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c3_primary_mode_ind_rx_reg;
    struct
    {
        unsigned int  c3_primary_mode_ind_rx : 3;  /* bit[0-2] : 接收通道3对应的主模（定义为主模3）的模式配置指示：
                                                                 000：LTE 主模。
                                                                 001：W主模。
                                                                 010：TDS主模。
                                                                 011：Gm主模；
                                                                 100：Gs主模；
                                                                 101:C2主模；
                                                                 110~111：无效。
                                                                 配置时刻：各模根据通信场景配置 */
        unsigned int  reserved               : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_C3_PRIMARY_MODE_IND_RX_UNION;
#define BBPCOMM_C3_PRIMARY_MODE_IND_RX_c3_primary_mode_ind_rx_START  (0)
#define BBPCOMM_C3_PRIMARY_MODE_IND_RX_c3_primary_mode_ind_rx_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_C3_SECOND_MODE_IND_UNION
 结构说明  : C3_SECOND_MODE_IND 寄存器结构定义。地址偏移量:0x0064，初值:0x00000007，宽度:32
 寄存器说明: 主模3对应的从模（从模3）的模式指示寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c3_second_mode_ind_reg;
    struct
    {
        unsigned int  c3_second_mode_ind : 3;  /* bit[0-2] : 接收主模3对应的从模（定义为从模3）的模式配置指示：
                                                             000：LTE从模。
                                                             001：W 从模。
                                                             010：TDS从模。
                                                             011：Gm从模；
                                                             100：Gs从模；
                                                             101:C2从模；
                                                             110~111：无效。
                                                             配置时刻：各模根据通信场景配置 */
        unsigned int  reserved           : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_C3_SECOND_MODE_IND_UNION;
#define BBPCOMM_C3_SECOND_MODE_IND_c3_second_mode_ind_START  (0)
#define BBPCOMM_C3_SECOND_MODE_IND_c3_second_mode_ind_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_C3_PRIMARY_MODE_IND_TX_UNION
 结构说明  : C3_PRIMARY_MODE_IND_TX 寄存器结构定义。地址偏移量:0x0068，初值:0x00000007，宽度:32
 寄存器说明: 发送通道3对应的模式指示寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c3_primary_mode_ind_tx_reg;
    struct
    {
        unsigned int  c3_primary_mode_ind_tx : 3;  /* bit[0-2] : 发送通道3对应的模式配置指示：
                                                                 000：LTE 主模。
                                                                 001：W主模。
                                                                 010：TDS主模。
                                                                 011：Gm主模；
                                                                 100：Gs主模；
                                                                 101:C2主模；
                                                                 110~111：无效。
                                                                 配置时刻：各模根据通信场景配置 */
        unsigned int  reserved               : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_C3_PRIMARY_MODE_IND_TX_UNION;
#define BBPCOMM_C3_PRIMARY_MODE_IND_TX_c3_primary_mode_ind_tx_START  (0)
#define BBPCOMM_C3_PRIMARY_MODE_IND_TX_c3_primary_mode_ind_tx_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_C3_SECOND_AFC_MODE_UNION
 结构说明  : C3_SECOND_AFC_MODE 寄存器结构定义。地址偏移量:0x0070，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c3_second_afc_mode_reg;
    struct
    {
        unsigned int  c3_second_afc_mode : 1;  /* bit[0]   : 0:通道3从模使用通道3主模afc控制字
                                                             1:通道3从模使用通道3从模afc控制字 */
        unsigned int  reserved           : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_C3_SECOND_AFC_MODE_UNION;
#define BBPCOMM_C3_SECOND_AFC_MODE_c3_second_afc_mode_START  (0)
#define BBPCOMM_C3_SECOND_AFC_MODE_c3_second_afc_mode_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_LTE_CH0_ABBIF_FMT_UNION
 结构说明  : LTE_CH0_ABBIF_FMT 寄存器结构定义。地址偏移量:0x0100，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      lte_ch0_abbif_fmt_reg;
    struct
    {
        unsigned int  reserved_0              : 1;  /* bit[0-0]  : 保留 */
        unsigned int  lte_ch0_rxb_iq_exchange : 1;  /* bit[1-1]  : 1'b1：LTE的CH0 RXB通路IQ路数据交换
                                                                   1'b0：LTE的CH0 RXB通路IQ路数据不交换 */
        unsigned int  lte_ch0_rxb_q_inv       : 1;  /* bit[2-2]  : 1'b1：LTE的CH0 RXB通路Q路数据取反
                                                                   1'b0：LTE的CH0 RXB通路Q路数据不取反 */
        unsigned int  lte_ch0_rxb_i_inv       : 1;  /* bit[3-3]  : 1'b1：LTE的CH0 RXB通路I路数据取反
                                                                   1'b0：LTE的CH0 RXB通路I路数据不取反 */
        unsigned int  lte_ch0_rxa_iq_exchange : 1;  /* bit[4-4]  : 1'b1：LTE的CH0 RXA通路IQ路数据交换
                                                                   1'b0：LTE的CH0 RXA通路IQ路数据不交换 */
        unsigned int  lte_ch0_rxa_q_inv       : 1;  /* bit[5-5]  : 1'b1：LTE的CH0 RXA通路Q路数据取反
                                                                   1'b0：LTE的CH0 RXA通路Q路数据不取反 */
        unsigned int  lte_ch0_rxa_i_inv       : 1;  /* bit[6-6]  : 1'b1：LTE的CH0 RXA通路I路数据取反
                                                                   1'b0：LTE的CH0 RXA通路I路数据不取反 */
        unsigned int  lte_ch0_tx_iq_exchange  : 1;  /* bit[7-7]  : 1'b1：LTE的CH0 TX通路IQ路数据交换
                                                                   1'b0：LTE的CH0 TX通路IQ路数据不交换 */
        unsigned int  lte_ch0_tx_q_inv        : 1;  /* bit[8-8]  : 1'b1：LTE的CH0 TX通路Q路数据取反
                                                                   1'b0：LTE的CH0 TX通路Q路数据不取反 */
        unsigned int  lte_ch0_tx_i_inv        : 1;  /* bit[9-9]  : 1'b1：LTE的CH0 TX通路I路数据取反
                                                                   1'b0：LTE的CH0 TX通路I路数据不取反 */
        unsigned int  reserved_1              : 22; /* bit[10-31]: 保留 */
    } reg;
} BBPCOMM_LTE_CH0_ABBIF_FMT_UNION;
#define BBPCOMM_LTE_CH0_ABBIF_FMT_lte_ch0_rxb_iq_exchange_START  (1)
#define BBPCOMM_LTE_CH0_ABBIF_FMT_lte_ch0_rxb_iq_exchange_END    (1)
#define BBPCOMM_LTE_CH0_ABBIF_FMT_lte_ch0_rxb_q_inv_START        (2)
#define BBPCOMM_LTE_CH0_ABBIF_FMT_lte_ch0_rxb_q_inv_END          (2)
#define BBPCOMM_LTE_CH0_ABBIF_FMT_lte_ch0_rxb_i_inv_START        (3)
#define BBPCOMM_LTE_CH0_ABBIF_FMT_lte_ch0_rxb_i_inv_END          (3)
#define BBPCOMM_LTE_CH0_ABBIF_FMT_lte_ch0_rxa_iq_exchange_START  (4)
#define BBPCOMM_LTE_CH0_ABBIF_FMT_lte_ch0_rxa_iq_exchange_END    (4)
#define BBPCOMM_LTE_CH0_ABBIF_FMT_lte_ch0_rxa_q_inv_START        (5)
#define BBPCOMM_LTE_CH0_ABBIF_FMT_lte_ch0_rxa_q_inv_END          (5)
#define BBPCOMM_LTE_CH0_ABBIF_FMT_lte_ch0_rxa_i_inv_START        (6)
#define BBPCOMM_LTE_CH0_ABBIF_FMT_lte_ch0_rxa_i_inv_END          (6)
#define BBPCOMM_LTE_CH0_ABBIF_FMT_lte_ch0_tx_iq_exchange_START   (7)
#define BBPCOMM_LTE_CH0_ABBIF_FMT_lte_ch0_tx_iq_exchange_END     (7)
#define BBPCOMM_LTE_CH0_ABBIF_FMT_lte_ch0_tx_q_inv_START         (8)
#define BBPCOMM_LTE_CH0_ABBIF_FMT_lte_ch0_tx_q_inv_END           (8)
#define BBPCOMM_LTE_CH0_ABBIF_FMT_lte_ch0_tx_i_inv_START         (9)
#define BBPCOMM_LTE_CH0_ABBIF_FMT_lte_ch0_tx_i_inv_END           (9)


/*****************************************************************************
 结构名    : BBPCOMM_LTE_CH1_ABBIF_FMT_UNION
 结构说明  : LTE_CH1_ABBIF_FMT 寄存器结构定义。地址偏移量:0x0104，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      lte_ch1_abbif_fmt_reg;
    struct
    {
        unsigned int  reserved_0              : 1;  /* bit[0-0]  : 保留 */
        unsigned int  lte_ch1_rxb_iq_exchange : 1;  /* bit[1-1]  : 1'b1：LTE的CH1 RXB通路IQ路数据交换
                                                                   1'b0：LTE的CH1 RXB通路IQ路数据不交换 */
        unsigned int  lte_ch1_rxb_q_inv       : 1;  /* bit[2-2]  : 1'b1：LTE的CH1 RXB通路Q路数据取反
                                                                   1'b0：LTE的CH1 RXB通路Q路数据不取反 */
        unsigned int  lte_ch1_rxb_i_inv       : 1;  /* bit[3-3]  : 1'b1：LTE的CH1 RXB通路I路数据取反
                                                                   1'b0：LTE的CH1 RXB通路I路数据不取反 */
        unsigned int  lte_ch1_rxa_iq_exchange : 1;  /* bit[4-4]  : 1'b1：LTE的CH1 RXA通路IQ路数据交换
                                                                   1'b0：LTE的CH1 RXA通路IQ路数据不交换 */
        unsigned int  lte_ch1_rxa_q_inv       : 1;  /* bit[5-5]  : 1'b1：LTE的CH1 RXA通路Q路数据取反
                                                                   1'b0：LTE的CH1 RXA通路Q路数据不取反 */
        unsigned int  lte_ch1_rxa_i_inv       : 1;  /* bit[6-6]  : 1'b1：LTE的CH1 RXA通路I路数据取反
                                                                   1'b0：LTE的CH1 RXA通路I路数据不取反 */
        unsigned int  lte_ch1_tx_iq_exchange  : 1;  /* bit[7-7]  : 1'b1：LTE的CH1 TX通路IQ路数据交换
                                                                   1'b0：LTE的CH1 TX通路IQ路数据不交换 */
        unsigned int  lte_ch1_tx_q_inv        : 1;  /* bit[8-8]  : 1'b1：LTE的CH1 TX通路Q路数据取反
                                                                   1'b0：LTE的CH1 TX通路Q路数据不取反 */
        unsigned int  lte_ch1_tx_i_inv        : 1;  /* bit[9-9]  : 1'b1：LTE的CH1 TX通路I路数据取反
                                                                   1'b0：LTE的CH1 TX通路I路数据不取反 */
        unsigned int  reserved_1              : 22; /* bit[10-31]: 保留 */
    } reg;
} BBPCOMM_LTE_CH1_ABBIF_FMT_UNION;
#define BBPCOMM_LTE_CH1_ABBIF_FMT_lte_ch1_rxb_iq_exchange_START  (1)
#define BBPCOMM_LTE_CH1_ABBIF_FMT_lte_ch1_rxb_iq_exchange_END    (1)
#define BBPCOMM_LTE_CH1_ABBIF_FMT_lte_ch1_rxb_q_inv_START        (2)
#define BBPCOMM_LTE_CH1_ABBIF_FMT_lte_ch1_rxb_q_inv_END          (2)
#define BBPCOMM_LTE_CH1_ABBIF_FMT_lte_ch1_rxb_i_inv_START        (3)
#define BBPCOMM_LTE_CH1_ABBIF_FMT_lte_ch1_rxb_i_inv_END          (3)
#define BBPCOMM_LTE_CH1_ABBIF_FMT_lte_ch1_rxa_iq_exchange_START  (4)
#define BBPCOMM_LTE_CH1_ABBIF_FMT_lte_ch1_rxa_iq_exchange_END    (4)
#define BBPCOMM_LTE_CH1_ABBIF_FMT_lte_ch1_rxa_q_inv_START        (5)
#define BBPCOMM_LTE_CH1_ABBIF_FMT_lte_ch1_rxa_q_inv_END          (5)
#define BBPCOMM_LTE_CH1_ABBIF_FMT_lte_ch1_rxa_i_inv_START        (6)
#define BBPCOMM_LTE_CH1_ABBIF_FMT_lte_ch1_rxa_i_inv_END          (6)
#define BBPCOMM_LTE_CH1_ABBIF_FMT_lte_ch1_tx_iq_exchange_START   (7)
#define BBPCOMM_LTE_CH1_ABBIF_FMT_lte_ch1_tx_iq_exchange_END     (7)
#define BBPCOMM_LTE_CH1_ABBIF_FMT_lte_ch1_tx_q_inv_START         (8)
#define BBPCOMM_LTE_CH1_ABBIF_FMT_lte_ch1_tx_q_inv_END           (8)
#define BBPCOMM_LTE_CH1_ABBIF_FMT_lte_ch1_tx_i_inv_START         (9)
#define BBPCOMM_LTE_CH1_ABBIF_FMT_lte_ch1_tx_i_inv_END           (9)


/*****************************************************************************
 结构名    : BBPCOMM_LTE_CH2_ABBIF_FMT_UNION
 结构说明  : LTE_CH2_ABBIF_FMT 寄存器结构定义。地址偏移量:0x0108，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      lte_ch2_abbif_fmt_reg;
    struct
    {
        unsigned int  reserved_0              : 1;  /* bit[0-0]  : 保留 */
        unsigned int  lte_ch2_rxb_iq_exchange : 1;  /* bit[1-1]  : 1'b1：LTE的CH2 RXB通路IQ路数据交换
                                                                   1'b0：LTE的CH2 RXB通路IQ路数据不交换 */
        unsigned int  lte_ch2_rxb_q_inv       : 1;  /* bit[2-2]  : 1'b1：LTE的CH2 RXB通路Q路数据取反
                                                                   1'b0：LTE的CH2 RXB通路Q路数据不取反 */
        unsigned int  lte_ch2_rxb_i_inv       : 1;  /* bit[3-3]  : 1'b1：LTE的CH2 RXB通路I路数据取反
                                                                   1'b0：LTE的CH2 RXB通路I路数据不取反 */
        unsigned int  lte_ch2_rxa_iq_exchange : 1;  /* bit[4-4]  : 1'b1：LTE的CH2 RXA通路IQ路数据交换
                                                                   1'b0：LTE的CH2 RXA通路IQ路数据不交换 */
        unsigned int  lte_ch2_rxa_q_inv       : 1;  /* bit[5-5]  : 1'b1：LTE的CH2 RXA通路Q路数据取反
                                                                   1'b0：LTE的CH2 RXA通路Q路数据不取反 */
        unsigned int  lte_ch2_rxa_i_inv       : 1;  /* bit[6-6]  : 1'b1：LTE的CH2 RXA通路I路数据取反
                                                                   1'b0：LTE的CH2 RXA通路I路数据不取反 */
        unsigned int  lte_ch2_tx_iq_exchange  : 1;  /* bit[7-7]  : 1'b1：LTE的CH2 TX通路IQ路数据交换
                                                                   1'b0：LTE的CH2 TX通路IQ路数据不交换 */
        unsigned int  lte_ch2_tx_q_inv        : 1;  /* bit[8-8]  : 1'b1：LTE的CH2 TX通路Q路数据取反
                                                                   1'b0：LTE的CH2 TX通路Q路数据不取反 */
        unsigned int  lte_ch2_tx_i_inv        : 1;  /* bit[9-9]  : 1'b1：LTE的CH2 TX通路I路数据取反
                                                                   1'b0：LTE的CH2 TX通路I路数据不取反 */
        unsigned int  reserved_1              : 22; /* bit[10-31]: 保留 */
    } reg;
} BBPCOMM_LTE_CH2_ABBIF_FMT_UNION;
#define BBPCOMM_LTE_CH2_ABBIF_FMT_lte_ch2_rxb_iq_exchange_START  (1)
#define BBPCOMM_LTE_CH2_ABBIF_FMT_lte_ch2_rxb_iq_exchange_END    (1)
#define BBPCOMM_LTE_CH2_ABBIF_FMT_lte_ch2_rxb_q_inv_START        (2)
#define BBPCOMM_LTE_CH2_ABBIF_FMT_lte_ch2_rxb_q_inv_END          (2)
#define BBPCOMM_LTE_CH2_ABBIF_FMT_lte_ch2_rxb_i_inv_START        (3)
#define BBPCOMM_LTE_CH2_ABBIF_FMT_lte_ch2_rxb_i_inv_END          (3)
#define BBPCOMM_LTE_CH2_ABBIF_FMT_lte_ch2_rxa_iq_exchange_START  (4)
#define BBPCOMM_LTE_CH2_ABBIF_FMT_lte_ch2_rxa_iq_exchange_END    (4)
#define BBPCOMM_LTE_CH2_ABBIF_FMT_lte_ch2_rxa_q_inv_START        (5)
#define BBPCOMM_LTE_CH2_ABBIF_FMT_lte_ch2_rxa_q_inv_END          (5)
#define BBPCOMM_LTE_CH2_ABBIF_FMT_lte_ch2_rxa_i_inv_START        (6)
#define BBPCOMM_LTE_CH2_ABBIF_FMT_lte_ch2_rxa_i_inv_END          (6)
#define BBPCOMM_LTE_CH2_ABBIF_FMT_lte_ch2_tx_iq_exchange_START   (7)
#define BBPCOMM_LTE_CH2_ABBIF_FMT_lte_ch2_tx_iq_exchange_END     (7)
#define BBPCOMM_LTE_CH2_ABBIF_FMT_lte_ch2_tx_q_inv_START         (8)
#define BBPCOMM_LTE_CH2_ABBIF_FMT_lte_ch2_tx_q_inv_END           (8)
#define BBPCOMM_LTE_CH2_ABBIF_FMT_lte_ch2_tx_i_inv_START         (9)
#define BBPCOMM_LTE_CH2_ABBIF_FMT_lte_ch2_tx_i_inv_END           (9)


/*****************************************************************************
 结构名    : BBPCOMM_LTE_CH3_ABBIF_FMT_UNION
 结构说明  : LTE_CH3_ABBIF_FMT 寄存器结构定义。地址偏移量:0x010C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      lte_ch3_abbif_fmt_reg;
    struct
    {
        unsigned int  reserved_0              : 1;  /* bit[0-0]  : 保留 */
        unsigned int  lte_ch3_rxb_iq_exchange : 1;  /* bit[1-1]  : 1'b1：LTE的CH3 RXB通路IQ路数据交换
                                                                   1'b0：LTE的CH3 RXB通路IQ路数据不交换 */
        unsigned int  lte_ch3_rxb_q_inv       : 1;  /* bit[2-2]  : 1'b1：LTE的CH3 RXB通路Q路数据取反
                                                                   1'b0：LTE的CH3 RXB通路Q路数据不取反 */
        unsigned int  lte_ch3_rxb_i_inv       : 1;  /* bit[3-3]  : 1'b1：LTE的CH3 RXB通路I路数据取反
                                                                   1'b0：LTE的CH3 RXB通路I路数据不取反 */
        unsigned int  lte_ch3_rxa_iq_exchange : 1;  /* bit[4-4]  : 1'b1：LTE的CH3 RXA通路IQ路数据交换
                                                                   1'b0：LTE的CH3 RXA通路IQ路数据不交换 */
        unsigned int  lte_ch3_rxa_q_inv       : 1;  /* bit[5-5]  : 1'b1：LTE的CH3 RXA通路Q路数据取反
                                                                   1'b0：LTE的CH3 RXA通路Q路数据不取反 */
        unsigned int  lte_ch3_rxa_i_inv       : 1;  /* bit[6-6]  : 1'b1：LTE的CH3 RXA通路I路数据取反
                                                                   1'b0：LTE的CH3 RXA通路I路数据不取反 */
        unsigned int  lte_ch3_tx_iq_exchange  : 1;  /* bit[7-7]  : 1'b1：LTE的CH3 TX通路IQ路数据交换
                                                                   1'b0：LTE的CH3 TX通路IQ路数据不交换 */
        unsigned int  lte_ch3_tx_q_inv        : 1;  /* bit[8-8]  : 1'b1：LTE的CH3 TX通路Q路数据取反
                                                                   1'b0：LTE的CH3 TX通路Q路数据不取反 */
        unsigned int  lte_ch3_tx_i_inv        : 1;  /* bit[9-9]  : 1'b1：LTE的CH3 TX通路I路数据取反
                                                                   1'b0：LTE的CH3 TX通路I路数据不取反 */
        unsigned int  reserved_1              : 22; /* bit[10-31]: 保留 */
    } reg;
} BBPCOMM_LTE_CH3_ABBIF_FMT_UNION;
#define BBPCOMM_LTE_CH3_ABBIF_FMT_lte_ch3_rxb_iq_exchange_START  (1)
#define BBPCOMM_LTE_CH3_ABBIF_FMT_lte_ch3_rxb_iq_exchange_END    (1)
#define BBPCOMM_LTE_CH3_ABBIF_FMT_lte_ch3_rxb_q_inv_START        (2)
#define BBPCOMM_LTE_CH3_ABBIF_FMT_lte_ch3_rxb_q_inv_END          (2)
#define BBPCOMM_LTE_CH3_ABBIF_FMT_lte_ch3_rxb_i_inv_START        (3)
#define BBPCOMM_LTE_CH3_ABBIF_FMT_lte_ch3_rxb_i_inv_END          (3)
#define BBPCOMM_LTE_CH3_ABBIF_FMT_lte_ch3_rxa_iq_exchange_START  (4)
#define BBPCOMM_LTE_CH3_ABBIF_FMT_lte_ch3_rxa_iq_exchange_END    (4)
#define BBPCOMM_LTE_CH3_ABBIF_FMT_lte_ch3_rxa_q_inv_START        (5)
#define BBPCOMM_LTE_CH3_ABBIF_FMT_lte_ch3_rxa_q_inv_END          (5)
#define BBPCOMM_LTE_CH3_ABBIF_FMT_lte_ch3_rxa_i_inv_START        (6)
#define BBPCOMM_LTE_CH3_ABBIF_FMT_lte_ch3_rxa_i_inv_END          (6)
#define BBPCOMM_LTE_CH3_ABBIF_FMT_lte_ch3_tx_iq_exchange_START   (7)
#define BBPCOMM_LTE_CH3_ABBIF_FMT_lte_ch3_tx_iq_exchange_END     (7)
#define BBPCOMM_LTE_CH3_ABBIF_FMT_lte_ch3_tx_q_inv_START         (8)
#define BBPCOMM_LTE_CH3_ABBIF_FMT_lte_ch3_tx_q_inv_END           (8)
#define BBPCOMM_LTE_CH3_ABBIF_FMT_lte_ch3_tx_i_inv_START         (9)
#define BBPCOMM_LTE_CH3_ABBIF_FMT_lte_ch3_tx_i_inv_END           (9)


/*****************************************************************************
 结构名    : BBPCOMM_W_ABBIF_FMT_UNION
 结构说明  : W_ABBIF_FMT 寄存器结构定义。地址偏移量:0x0110，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      w_abbif_fmt_reg;
    struct
    {
        unsigned int  reserved_0        : 1;  /* bit[0-0]  : 保留 */
        unsigned int  w_rxb_iq_exchange : 1;  /* bit[1-1]  : 1'b1：W的RXB通路IQ路数据交换
                                                             1'b0：W的RXB通路IQ路数据不交换
                                                             V3R3不支持IQ交换功能。 */
        unsigned int  w_rxb_q_inv       : 1;  /* bit[2-2]  : 1'b1：W的RXB通路Q路数据取反
                                                             1'b0：W的RXB通路Q路数据不取反 */
        unsigned int  w_rxb_i_inv       : 1;  /* bit[3-3]  : 1'b1：W的RXB通路I路数据取反
                                                             1'b0：W的RXB通路I路数据不取反 */
        unsigned int  w_rxa_iq_exchange : 1;  /* bit[4-4]  : 1'b1：W的RXA通路IQ路数据交换
                                                             1'b0：W的RXA通路IQ路数据不交换
                                                             V3R3不支持IQ交换功能。 */
        unsigned int  w_rxa_q_inv       : 1;  /* bit[5-5]  : 1'b1：W的RXA通路Q路数据取反
                                                             1'b0：W的RXA通路Q路数据不取反 */
        unsigned int  w_rxa_i_inv       : 1;  /* bit[6-6]  : 1'b1：W的RXA通路I路数据取反
                                                             1'b0：W的RXA通路I路数据不取反 */
        unsigned int  w_tx_iq_exchange  : 1;  /* bit[7-7]  : 1'b1：W的TX通路IQ路数据交换
                                                             1'b0：W的TX通路IQ路数据不交换
                                                             V3R3不支持IQ交换功能。 */
        unsigned int  w_tx_q_inv        : 1;  /* bit[8-8]  : 1'b1：W的TX通路Q路数据取反
                                                             1'b0：W的TX通路Q路数据不取反 */
        unsigned int  w_tx_i_inv        : 1;  /* bit[9-9]  : 1'b1：W的TX通路I路数据取反
                                                             1'b0：W的TX通路I路数据不取反。 */
        unsigned int  reserved_1        : 22; /* bit[10-31]: 保留 */
    } reg;
} BBPCOMM_W_ABBIF_FMT_UNION;
#define BBPCOMM_W_ABBIF_FMT_w_rxb_iq_exchange_START  (1)
#define BBPCOMM_W_ABBIF_FMT_w_rxb_iq_exchange_END    (1)
#define BBPCOMM_W_ABBIF_FMT_w_rxb_q_inv_START        (2)
#define BBPCOMM_W_ABBIF_FMT_w_rxb_q_inv_END          (2)
#define BBPCOMM_W_ABBIF_FMT_w_rxb_i_inv_START        (3)
#define BBPCOMM_W_ABBIF_FMT_w_rxb_i_inv_END          (3)
#define BBPCOMM_W_ABBIF_FMT_w_rxa_iq_exchange_START  (4)
#define BBPCOMM_W_ABBIF_FMT_w_rxa_iq_exchange_END    (4)
#define BBPCOMM_W_ABBIF_FMT_w_rxa_q_inv_START        (5)
#define BBPCOMM_W_ABBIF_FMT_w_rxa_q_inv_END          (5)
#define BBPCOMM_W_ABBIF_FMT_w_rxa_i_inv_START        (6)
#define BBPCOMM_W_ABBIF_FMT_w_rxa_i_inv_END          (6)
#define BBPCOMM_W_ABBIF_FMT_w_tx_iq_exchange_START   (7)
#define BBPCOMM_W_ABBIF_FMT_w_tx_iq_exchange_END     (7)
#define BBPCOMM_W_ABBIF_FMT_w_tx_q_inv_START         (8)
#define BBPCOMM_W_ABBIF_FMT_w_tx_q_inv_END           (8)
#define BBPCOMM_W_ABBIF_FMT_w_tx_i_inv_START         (9)
#define BBPCOMM_W_ABBIF_FMT_w_tx_i_inv_END           (9)


/*****************************************************************************
 结构名    : BBPCOMM_TDS_ABBIF_FMT_UNION
 结构说明  : TDS_ABBIF_FMT 寄存器结构定义。地址偏移量:0x0114，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      tds_abbif_fmt_reg;
    struct
    {
        unsigned int  reserved_0          : 1;  /* bit[0-0]  : 保留 */
        unsigned int  tds_rxb_iq_exchange : 1;  /* bit[1-1]  : 1'b1：TDS的RXB通路IQ路数据交换
                                                               1'b0：TDS的RXB通路IQ路数据不交换
                                                               V3R3不支持IQ交换功能。 */
        unsigned int  tds_rxb_q_inv       : 1;  /* bit[2-2]  : 1'b1：TDS的RXB通路Q路数据取反
                                                               1'b0：TDS的RXB通路Q路数据不取反 */
        unsigned int  tds_rxb_i_inv       : 1;  /* bit[3-3]  : 1'b1：TDS的RXB通路I路数据取反
                                                               1'b0：TDS的RXB通路I路数据不取反 */
        unsigned int  tds_rxa_iq_exchange : 1;  /* bit[4-4]  : 1'b1：TDS的RXA通路IQ路数据交换
                                                               1'b0：TDS的RXA通路IQ路数据不交换
                                                               V3R3不支持IQ交换功能。 */
        unsigned int  tds_rxa_q_inv       : 1;  /* bit[5-5]  : 1'b1：TDS的RXA通路Q路数据取反
                                                               1'b0：TDS的RXA通路Q路数据不取反 */
        unsigned int  tds_rxa_i_inv       : 1;  /* bit[6-6]  : 1'b1：TDS的RXA通路I路数据取反
                                                               1'b0：TDS的RXA通路I路数据不取反 */
        unsigned int  tds_tx_iq_exchange  : 1;  /* bit[7-7]  : 1'b1：TDS的TX通路IQ路数据交换
                                                               1'b0：TDS的TX通路IQ路数据不交换
                                                               V3R3不支持IQ交换功能。 */
        unsigned int  tds_tx_q_inv        : 1;  /* bit[8-8]  : 1'b1：TDS的TX通路Q路数据取反
                                                               1'b0：TDS的TX通路Q路数据不取反 */
        unsigned int  tds_tx_i_inv        : 1;  /* bit[9-9]  : 1'b1：TDS的TX通路I路数据取反
                                                               1'b0：TDS的TX通路I路数据不取反 */
        unsigned int  reserved_1          : 22; /* bit[10-31]: 保留 */
    } reg;
} BBPCOMM_TDS_ABBIF_FMT_UNION;
#define BBPCOMM_TDS_ABBIF_FMT_tds_rxb_iq_exchange_START  (1)
#define BBPCOMM_TDS_ABBIF_FMT_tds_rxb_iq_exchange_END    (1)
#define BBPCOMM_TDS_ABBIF_FMT_tds_rxb_q_inv_START        (2)
#define BBPCOMM_TDS_ABBIF_FMT_tds_rxb_q_inv_END          (2)
#define BBPCOMM_TDS_ABBIF_FMT_tds_rxb_i_inv_START        (3)
#define BBPCOMM_TDS_ABBIF_FMT_tds_rxb_i_inv_END          (3)
#define BBPCOMM_TDS_ABBIF_FMT_tds_rxa_iq_exchange_START  (4)
#define BBPCOMM_TDS_ABBIF_FMT_tds_rxa_iq_exchange_END    (4)
#define BBPCOMM_TDS_ABBIF_FMT_tds_rxa_q_inv_START        (5)
#define BBPCOMM_TDS_ABBIF_FMT_tds_rxa_q_inv_END          (5)
#define BBPCOMM_TDS_ABBIF_FMT_tds_rxa_i_inv_START        (6)
#define BBPCOMM_TDS_ABBIF_FMT_tds_rxa_i_inv_END          (6)
#define BBPCOMM_TDS_ABBIF_FMT_tds_tx_iq_exchange_START   (7)
#define BBPCOMM_TDS_ABBIF_FMT_tds_tx_iq_exchange_END     (7)
#define BBPCOMM_TDS_ABBIF_FMT_tds_tx_q_inv_START         (8)
#define BBPCOMM_TDS_ABBIF_FMT_tds_tx_q_inv_END           (8)
#define BBPCOMM_TDS_ABBIF_FMT_tds_tx_i_inv_START         (9)
#define BBPCOMM_TDS_ABBIF_FMT_tds_tx_i_inv_END           (9)


/*****************************************************************************
 结构名    : BBPCOMM_GM_ABBIF_FMT_UNION
 结构说明  : GM_ABBIF_FMT 寄存器结构定义。地址偏移量:0x0118，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      gm_abbif_fmt_reg;
    struct
    {
        unsigned int  reserved_0         : 1;  /* bit[0-0]  : 保留 */
        unsigned int  gm_rxb_iq_exchange : 1;  /* bit[1-1]  : 1'b1：GM的RXB通路IQ路数据交换
                                                              1'b0：GM的RXB通路IQ路数据不交换
                                                              V3R3不支持IQ交换功能。 */
        unsigned int  gm_rxb_q_inv       : 1;  /* bit[2-2]  : 1'b1：GM的RXB通路Q路数据取反
                                                              1'b0：GM的RXB通路Q路数据不取反 */
        unsigned int  gm_rxb_i_inv       : 1;  /* bit[3-3]  : 1'b1：GM的RXB通路I路数据取反
                                                              1'b0：GM的RXB通路I路数据不取反 */
        unsigned int  gm_rxa_iq_exchange : 1;  /* bit[4-4]  : 1'b1：GM的RXA通路IQ路数据交换
                                                              1'b0：GM的RXA通路IQ路数据不交换
                                                              V3R3不支持IQ交换功能。 */
        unsigned int  gm_rxa_q_inv       : 1;  /* bit[5-5]  : 1'b1：GM的RXA通路Q路数据取反
                                                              1'b0：GM的RXA通路Q路数据不取反 */
        unsigned int  gm_rxa_i_inv       : 1;  /* bit[6-6]  : 1'b1：GM的RXA通路I路数据取反
                                                              1'b0：GM的RXA通路I路数据不取反 */
        unsigned int  gm_tx_iq_exchange  : 1;  /* bit[7-7]  : 1'b1：GM的TX通路IQ路数据交换
                                                              1'b0：GM的TX通路IQ路数据不交换
                                                              V3R3不支持IQ交换功能。 */
        unsigned int  gm_tx_q_inv        : 1;  /* bit[8-8]  : 1'b1：GM的TX通路Q路数据取反
                                                              1'b0：GM的TX通路Q路数据不取反 */
        unsigned int  gm_tx_i_inv        : 1;  /* bit[9-9]  : 1'b1：GM的TX通路I路数据取反
                                                              1'b0：GM的TX通路I路数据不取反 */
        unsigned int  reserved_1         : 22; /* bit[10-31]: 保留 */
    } reg;
} BBPCOMM_GM_ABBIF_FMT_UNION;
#define BBPCOMM_GM_ABBIF_FMT_gm_rxb_iq_exchange_START  (1)
#define BBPCOMM_GM_ABBIF_FMT_gm_rxb_iq_exchange_END    (1)
#define BBPCOMM_GM_ABBIF_FMT_gm_rxb_q_inv_START        (2)
#define BBPCOMM_GM_ABBIF_FMT_gm_rxb_q_inv_END          (2)
#define BBPCOMM_GM_ABBIF_FMT_gm_rxb_i_inv_START        (3)
#define BBPCOMM_GM_ABBIF_FMT_gm_rxb_i_inv_END          (3)
#define BBPCOMM_GM_ABBIF_FMT_gm_rxa_iq_exchange_START  (4)
#define BBPCOMM_GM_ABBIF_FMT_gm_rxa_iq_exchange_END    (4)
#define BBPCOMM_GM_ABBIF_FMT_gm_rxa_q_inv_START        (5)
#define BBPCOMM_GM_ABBIF_FMT_gm_rxa_q_inv_END          (5)
#define BBPCOMM_GM_ABBIF_FMT_gm_rxa_i_inv_START        (6)
#define BBPCOMM_GM_ABBIF_FMT_gm_rxa_i_inv_END          (6)
#define BBPCOMM_GM_ABBIF_FMT_gm_tx_iq_exchange_START   (7)
#define BBPCOMM_GM_ABBIF_FMT_gm_tx_iq_exchange_END     (7)
#define BBPCOMM_GM_ABBIF_FMT_gm_tx_q_inv_START         (8)
#define BBPCOMM_GM_ABBIF_FMT_gm_tx_q_inv_END           (8)
#define BBPCOMM_GM_ABBIF_FMT_gm_tx_i_inv_START         (9)
#define BBPCOMM_GM_ABBIF_FMT_gm_tx_i_inv_END           (9)


/*****************************************************************************
 结构名    : BBPCOMM_GS_ABBIF_FMT_UNION
 结构说明  : GS_ABBIF_FMT 寄存器结构定义。地址偏移量:0x011C，初值:0x00000001，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      gs_abbif_fmt_reg;
    struct
    {
        unsigned int  reserved_0         : 1;  /* bit[0-0]  : 保留 */
        unsigned int  gs_rxb_iq_exchange : 1;  /* bit[1-1]  : 1'b1：GS的RXB通路IQ路数据交换
                                                              1'b0：GS的RXB通路IQ路数据不交换
                                                              V3R3不支持IQ交换功能。 */
        unsigned int  gs_rxb_q_inv       : 1;  /* bit[2-2]  : 1'b1：GS的RXB通路Q路数据取反
                                                              1'b0：GS的RXB通路Q路数据不取反 */
        unsigned int  gs_rxb_i_inv       : 1;  /* bit[3-3]  : 1'b1：GS的RXB通路I路数据取反
                                                              1'b0：GS的RXB通路I路数据不取反 */
        unsigned int  gs_rxa_iq_exchange : 1;  /* bit[4-4]  : 1'b1：GS的RXA通路IQ路数据交换
                                                              1'b0：GS的RXA通路IQ路数据不交换
                                                              V3R3不支持IQ交换功能。 */
        unsigned int  gs_rxa_q_inv       : 1;  /* bit[5-5]  : 1'b1：GS的RXA通路Q路数据取反
                                                              1'b0：GS的RXA通路Q路数据不取反 */
        unsigned int  gs_rxa_i_inv       : 1;  /* bit[6-6]  : 1'b1：GS的RXA通路I路数据取反
                                                              1'b0：GS的RXA通路I路数据不取反 */
        unsigned int  gs_tx_iq_exchange  : 1;  /* bit[7-7]  : 1'b1：GS的TX通路IQ路数据交换
                                                              1'b0：GS的TX通路IQ路数据不交换
                                                              V3R3不支持IQ交换功能。 */
        unsigned int  gs_tx_q_inv        : 1;  /* bit[8-8]  : 1'b1：GS的TX通路Q路数据取反
                                                              1'b0：GS的TX通路Q路数据不取反 */
        unsigned int  gs_tx_i_inv        : 1;  /* bit[9-9]  : 1'b1：GS的TX通路I路数据取反
                                                              1'b0：GS的TX通路I路数据不取反 */
        unsigned int  reserved_1         : 22; /* bit[10-31]: 保留 */
    } reg;
} BBPCOMM_GS_ABBIF_FMT_UNION;
#define BBPCOMM_GS_ABBIF_FMT_gs_rxb_iq_exchange_START  (1)
#define BBPCOMM_GS_ABBIF_FMT_gs_rxb_iq_exchange_END    (1)
#define BBPCOMM_GS_ABBIF_FMT_gs_rxb_q_inv_START        (2)
#define BBPCOMM_GS_ABBIF_FMT_gs_rxb_q_inv_END          (2)
#define BBPCOMM_GS_ABBIF_FMT_gs_rxb_i_inv_START        (3)
#define BBPCOMM_GS_ABBIF_FMT_gs_rxb_i_inv_END          (3)
#define BBPCOMM_GS_ABBIF_FMT_gs_rxa_iq_exchange_START  (4)
#define BBPCOMM_GS_ABBIF_FMT_gs_rxa_iq_exchange_END    (4)
#define BBPCOMM_GS_ABBIF_FMT_gs_rxa_q_inv_START        (5)
#define BBPCOMM_GS_ABBIF_FMT_gs_rxa_q_inv_END          (5)
#define BBPCOMM_GS_ABBIF_FMT_gs_rxa_i_inv_START        (6)
#define BBPCOMM_GS_ABBIF_FMT_gs_rxa_i_inv_END          (6)
#define BBPCOMM_GS_ABBIF_FMT_gs_tx_iq_exchange_START   (7)
#define BBPCOMM_GS_ABBIF_FMT_gs_tx_iq_exchange_END     (7)
#define BBPCOMM_GS_ABBIF_FMT_gs_tx_q_inv_START         (8)
#define BBPCOMM_GS_ABBIF_FMT_gs_tx_q_inv_END           (8)
#define BBPCOMM_GS_ABBIF_FMT_gs_tx_i_inv_START         (9)
#define BBPCOMM_GS_ABBIF_FMT_gs_tx_i_inv_END           (9)


/*****************************************************************************
 结构名    : BBPCOMM_C_ABBIF_FMT_UNION
 结构说明  : C_ABBIF_FMT 寄存器结构定义。地址偏移量:0x0120，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c_abbif_fmt_reg;
    struct
    {
        unsigned int  reserved_0        : 1;  /* bit[0-0]  : 保留 */
        unsigned int  c_rxb_iq_exchange : 1;  /* bit[1-1]  : 1'b1：C2的RXB通路IQ路数据交换
                                                             1'b0：C2的RXB通路IQ路数据不交换
                                                             V3R3不支持IQ交换功能。 */
        unsigned int  c_rxb_q_inv       : 1;  /* bit[2-2]  : 1'b1：C2的RXB通路Q路数据取反
                                                             1'b0：C2的RXB通路Q路数据不取反 */
        unsigned int  c_rxb_i_inv       : 1;  /* bit[3-3]  : 1'b1：C2的RXB通路I路数据取反
                                                             1'b0：C2的RXB通路I路数据不取反 */
        unsigned int  c_rxa_iq_exchange : 1;  /* bit[4-4]  : 1'b1：C2的RXA通路IQ路数据交换
                                                             1'b0：C2的RXA通路IQ路数据不交换
                                                             V3R3不支持IQ交换功能。 */
        unsigned int  c_rxa_q_inv       : 1;  /* bit[5-5]  : 1'b1：C2的RXA通路Q路数据取反
                                                             1'b0：C2的RXA通路Q路数据不取反 */
        unsigned int  c_rxa_i_inv       : 1;  /* bit[6-6]  : 1'b1：C2的RXA通路I路数据取反
                                                             1'b0：C2的RXA通路I路数据不取反 */
        unsigned int  c_tx_iq_exchange  : 1;  /* bit[7-7]  : 1'b1：C2的TX通路IQ路数据交换
                                                             1'b0：C2的TX通路IQ路数据不交换
                                                             V3R3不支持IQ交换功能。 */
        unsigned int  c_tx_q_inv        : 1;  /* bit[8-8]  : 1'b1：C2的TX通路Q路数据取反
                                                             1'b0：C2的TX通路Q路数据不取反 */
        unsigned int  c_tx_i_inv        : 1;  /* bit[9-9]  : 1'b1：C2的TX通路I路数据取反
                                                             1'b0：C2的TX通路I路数据不取反 */
        unsigned int  reserved_1        : 22; /* bit[10-31]: 保留 */
    } reg;
} BBPCOMM_C_ABBIF_FMT_UNION;
#define BBPCOMM_C_ABBIF_FMT_c_rxb_iq_exchange_START  (1)
#define BBPCOMM_C_ABBIF_FMT_c_rxb_iq_exchange_END    (1)
#define BBPCOMM_C_ABBIF_FMT_c_rxb_q_inv_START        (2)
#define BBPCOMM_C_ABBIF_FMT_c_rxb_q_inv_END          (2)
#define BBPCOMM_C_ABBIF_FMT_c_rxb_i_inv_START        (3)
#define BBPCOMM_C_ABBIF_FMT_c_rxb_i_inv_END          (3)
#define BBPCOMM_C_ABBIF_FMT_c_rxa_iq_exchange_START  (4)
#define BBPCOMM_C_ABBIF_FMT_c_rxa_iq_exchange_END    (4)
#define BBPCOMM_C_ABBIF_FMT_c_rxa_q_inv_START        (5)
#define BBPCOMM_C_ABBIF_FMT_c_rxa_q_inv_END          (5)
#define BBPCOMM_C_ABBIF_FMT_c_rxa_i_inv_START        (6)
#define BBPCOMM_C_ABBIF_FMT_c_rxa_i_inv_END          (6)
#define BBPCOMM_C_ABBIF_FMT_c_tx_iq_exchange_START   (7)
#define BBPCOMM_C_ABBIF_FMT_c_tx_iq_exchange_END     (7)
#define BBPCOMM_C_ABBIF_FMT_c_tx_q_inv_START         (8)
#define BBPCOMM_C_ABBIF_FMT_c_tx_q_inv_END           (8)
#define BBPCOMM_C_ABBIF_FMT_c_tx_i_inv_START         (9)
#define BBPCOMM_C_ABBIF_FMT_c_tx_i_inv_END           (9)


/*****************************************************************************
 结构名    : BBPCOMM_RFIC_CK_CFG_UNION
 结构说明  : RFIC_CK_CFG 寄存器结构定义。地址偏移量:0x0124，初值:0x00000249，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      rfic_ck_cfg_reg;
    struct
    {
        unsigned int  cpu_rfic0_ck_cfg : 3;  /* bit[0-2]  : SSI0master等待时间 */
        unsigned int  cpu_rfic1_ck_cfg : 3;  /* bit[3-5]  : SSI1master等待时间 */
        unsigned int  cpu_rfic2_ck_cfg : 3;  /* bit[6-8]  : SSI2master等待时间 */
        unsigned int  cpu_rfic3_ck_cfg : 3;  /* bit[9-11] : SSI3master等待时间 */
        unsigned int  reserved         : 20; /* bit[12-31]: 保留 */
    } reg;
} BBPCOMM_RFIC_CK_CFG_UNION;
#define BBPCOMM_RFIC_CK_CFG_cpu_rfic0_ck_cfg_START  (0)
#define BBPCOMM_RFIC_CK_CFG_cpu_rfic0_ck_cfg_END    (2)
#define BBPCOMM_RFIC_CK_CFG_cpu_rfic1_ck_cfg_START  (3)
#define BBPCOMM_RFIC_CK_CFG_cpu_rfic1_ck_cfg_END    (5)
#define BBPCOMM_RFIC_CK_CFG_cpu_rfic2_ck_cfg_START  (6)
#define BBPCOMM_RFIC_CK_CFG_cpu_rfic2_ck_cfg_END    (8)
#define BBPCOMM_RFIC_CK_CFG_cpu_rfic3_ck_cfg_START  (9)
#define BBPCOMM_RFIC_CK_CFG_cpu_rfic3_ck_cfg_END    (11)


/*****************************************************************************
 结构名    : BBPCOMM_APT_CH_SEL0_UNION
 结构说明  : APT_CH_SEL0 寄存器结构定义。地址偏移量:0x0130，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      apt_ch_sel0_reg;
    struct
    {
        unsigned int  apt_ch_sel0 : 3;  /* bit[0-2] : apt_pdm0信号来源：
                                                      2'd0：来自于通道0
                                                      2'd1：来自于通道1
                                                      2'd2：来自于通道2
                                                      2'd3：来自于通道3
                                                      其它：强制拉低电平输出 */
        unsigned int  reserved    : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_APT_CH_SEL0_UNION;
#define BBPCOMM_APT_CH_SEL0_apt_ch_sel0_START  (0)
#define BBPCOMM_APT_CH_SEL0_apt_ch_sel0_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_APT_CH_SEL1_UNION
 结构说明  : APT_CH_SEL1 寄存器结构定义。地址偏移量:0x0134，初值:0x00000001，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      apt_ch_sel1_reg;
    struct
    {
        unsigned int  apt_ch_sel1 : 3;  /* bit[0-2] : apt_pdm1信号来源：
                                                      2'd0：来自于通道0
                                                      2'd1：来自于通道1
                                                      2'd2：来自于通道2
                                                      2'd3：来自于通道3
                                                      其它：强制拉低电平输出 */
        unsigned int  reserved    : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_APT_CH_SEL1_UNION;
#define BBPCOMM_APT_CH_SEL1_apt_ch_sel1_START  (0)
#define BBPCOMM_APT_CH_SEL1_apt_ch_sel1_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_APT_CH_SEL2_UNION
 结构说明  : APT_CH_SEL2 寄存器结构定义。地址偏移量:0x0138，初值:0x00000002，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      apt_ch_sel2_reg;
    struct
    {
        unsigned int  apt_ch_sel2 : 3;  /* bit[0-2] : apt_pdm2信号来源：
                                                      2'd0：来自于通道0
                                                      2'd1：来自于通道1
                                                      2'd2：来自于通道2
                                                      2'd3：来自于通道3
                                                      其它：强制拉低电平输出 */
        unsigned int  reserved    : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_APT_CH_SEL2_UNION;
#define BBPCOMM_APT_CH_SEL2_apt_ch_sel2_START  (0)
#define BBPCOMM_APT_CH_SEL2_apt_ch_sel2_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_APT_CH_SEL3_UNION
 结构说明  : APT_CH_SEL3 寄存器结构定义。地址偏移量:0x013C，初值:0x00000003，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      apt_ch_sel3_reg;
    struct
    {
        unsigned int  apt_ch_sel3 : 3;  /* bit[0-2] : apt_pdm3信号来源：
                                                      2'd0：来自于通道0
                                                      2'd1：来自于通道1
                                                      2'd2：来自于通道2
                                                      2'd3：来自于通道3
                                                      其它：强制拉低电平输出 */
        unsigned int  reserved    : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_APT_CH_SEL3_UNION;
#define BBPCOMM_APT_CH_SEL3_apt_ch_sel3_START  (0)
#define BBPCOMM_APT_CH_SEL3_apt_ch_sel3_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_AFC_CH_SEL0_UNION
 结构说明  : AFC_CH_SEL0 寄存器结构定义。地址偏移量:0x0140，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      afc_ch_sel0_reg;
    struct
    {
        unsigned int  afc_ch_sel0 : 3;  /* bit[0-2] : afc pdm0信号来源：
                                                      2'd0：来自于通道0
                                                      2'd1：来自于通道1
                                                      2'd2：来自于通道2
                                                      2'd3：来自于通道3
                                                      其它：强制拉低电平输出 */
        unsigned int  reserved    : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_AFC_CH_SEL0_UNION;
#define BBPCOMM_AFC_CH_SEL0_afc_ch_sel0_START  (0)
#define BBPCOMM_AFC_CH_SEL0_afc_ch_sel0_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_AFC_CH_SEL1_UNION
 结构说明  : AFC_CH_SEL1 寄存器结构定义。地址偏移量:0x0144，初值:0x00000001，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      afc_ch_sel1_reg;
    struct
    {
        unsigned int  afc_ch_sel1 : 3;  /* bit[0-2] : afc pdm1信号来源：
                                                      2'd0：来自于通道0
                                                      2'd1：来自于通道1
                                                      2'd2：来自于通道2
                                                      2'd3：来自于通道3
                                                      其它：强制拉低电平输出 */
        unsigned int  reserved    : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_AFC_CH_SEL1_UNION;
#define BBPCOMM_AFC_CH_SEL1_afc_ch_sel1_START  (0)
#define BBPCOMM_AFC_CH_SEL1_afc_ch_sel1_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_AFC_CH_SEL2_UNION
 结构说明  : AFC_CH_SEL2 寄存器结构定义。地址偏移量:0x0148，初值:0x00000002，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      afc_ch_sel2_reg;
    struct
    {
        unsigned int  afc_ch_sel2 : 3;  /* bit[0-2] : afc pdm2信号来源：
                                                      1'b0：来自于通道0
                                                      1'b1：来自于通道1
                                                      2'b2：来自于通道2
                                                      2'b3：来自于通道3 */
        unsigned int  reserved    : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_AFC_CH_SEL2_UNION;
#define BBPCOMM_AFC_CH_SEL2_afc_ch_sel2_START  (0)
#define BBPCOMM_AFC_CH_SEL2_afc_ch_sel2_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_AFC_CH_SEL3_UNION
 结构说明  : AFC_CH_SEL3 寄存器结构定义。地址偏移量:0x014C，初值:0x00000003，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      afc_ch_sel3_reg;
    struct
    {
        unsigned int  afc_ch_sel3 : 3;  /* bit[0-2] : afc pdm3信号来源：
                                                      1'b0：来自于通道0
                                                      1'b1：来自于通道1
                                                      2'b2：来自于通道2
                                                      2'b3：来自于通道3 */
        unsigned int  reserved    : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_AFC_CH_SEL3_UNION;
#define BBPCOMM_AFC_CH_SEL3_afc_ch_sel3_START  (0)
#define BBPCOMM_AFC_CH_SEL3_afc_ch_sel3_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_PMU_CH_SEL0_UNION
 结构说明  : PMU_CH_SEL0 寄存器结构定义。地址偏移量:0x0150，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      pmu_ch_sel0_reg;
    struct
    {
        unsigned int  pmu_ch_sel0 : 3;  /* bit[0-2] : auxdac0信号来源：
                                                      2'b0：来自于通道0
                                                      2'b1：来自于通道1
                                                      2'b2：来自于通道2
                                                      2'b3：来自于通道3 */
        unsigned int  reserved    : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_PMU_CH_SEL0_UNION;
#define BBPCOMM_PMU_CH_SEL0_pmu_ch_sel0_START  (0)
#define BBPCOMM_PMU_CH_SEL0_pmu_ch_sel0_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_PMU_CH_SEL1_UNION
 结构说明  : PMU_CH_SEL1 寄存器结构定义。地址偏移量:0x0154，初值:0x00000001，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      pmu_ch_sel1_reg;
    struct
    {
        unsigned int  pmu_ch_sel1 : 3;  /* bit[0-2] : auxdac1信号来源：
                                                      2'd0：来自于通道0
                                                      2'd1：来自于通道1
                                                      2'd2：来自于通道2
                                                      2'd3：来自于通道3
                                                      其它：强制拉低电平输出 */
        unsigned int  reserved    : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_PMU_CH_SEL1_UNION;
#define BBPCOMM_PMU_CH_SEL1_pmu_ch_sel1_START  (0)
#define BBPCOMM_PMU_CH_SEL1_pmu_ch_sel1_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_PMU_CH_SEL2_UNION
 结构说明  : PMU_CH_SEL2 寄存器结构定义。地址偏移量:0x0158，初值:0x00000002，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      pmu_ch_sel2_reg;
    struct
    {
        unsigned int  pmu_ch_sel2 : 3;  /* bit[0-2] : auxdac2信号来源：
                                                      2'd0：来自于通道0
                                                      2'd1：来自于通道1
                                                      2'd2：来自于通道2
                                                      2'd3：来自于通道3
                                                      其它：强制拉低电平输出 */
        unsigned int  reserved    : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_PMU_CH_SEL2_UNION;
#define BBPCOMM_PMU_CH_SEL2_pmu_ch_sel2_START  (0)
#define BBPCOMM_PMU_CH_SEL2_pmu_ch_sel2_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_PMU_CH_SEL3_UNION
 结构说明  : PMU_CH_SEL3 寄存器结构定义。地址偏移量:0x015C，初值:0x00000003，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      pmu_ch_sel3_reg;
    struct
    {
        unsigned int  pmu_ch_sel3 : 3;  /* bit[0-2] : auxdac3信号来源：
                                                      2'd0：来自于通道0
                                                      2'd1：来自于通道1
                                                      2'd2：来自于通道2
                                                      2'd3：来自于通道3
                                                      其它：强制拉低电平输出 */
        unsigned int  reserved    : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_PMU_CH_SEL3_UNION;
#define BBPCOMM_PMU_CH_SEL3_pmu_ch_sel3_START  (0)
#define BBPCOMM_PMU_CH_SEL3_pmu_ch_sel3_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_L_TCVR_ON_CH0_UNION
 结构说明  : L_TCVR_ON_CH0 寄存器结构定义。地址偏移量:0x0180，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      l_tcvr_on_ch0_reg;
    struct
    {
        unsigned int  lte_tcvr_on_ch0 : 1;  /* bit[0]   : lte 通道0的tcvr_on配置：
                                                          1'b0：配置为低电平
                                                          1'b1：配置为高电平 */
        unsigned int  reserved        : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_L_TCVR_ON_CH0_UNION;
#define BBPCOMM_L_TCVR_ON_CH0_lte_tcvr_on_ch0_START  (0)
#define BBPCOMM_L_TCVR_ON_CH0_lte_tcvr_on_ch0_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_L_TCVR_ON_CH1_UNION
 结构说明  : L_TCVR_ON_CH1 寄存器结构定义。地址偏移量:0x0184，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      l_tcvr_on_ch1_reg;
    struct
    {
        unsigned int  lte_tcvr_on_ch1 : 1;  /* bit[0]   : lte 通道1的tcvr_on配置：
                                                          1'b0：配置为低电平
                                                          1'b1：配置为高电平 */
        unsigned int  reserved        : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_L_TCVR_ON_CH1_UNION;
#define BBPCOMM_L_TCVR_ON_CH1_lte_tcvr_on_ch1_START  (0)
#define BBPCOMM_L_TCVR_ON_CH1_lte_tcvr_on_ch1_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_L_TCVR_ON_CH2_UNION
 结构说明  : L_TCVR_ON_CH2 寄存器结构定义。地址偏移量:0x0188，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      l_tcvr_on_ch2_reg;
    struct
    {
        unsigned int  lte_tcvr_on_ch2 : 1;  /* bit[0]   : lte 通道2的tcvr_on配置：
                                                          1'b0：配置为低电平
                                                          1'b1：配置为高电平 */
        unsigned int  reserved        : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_L_TCVR_ON_CH2_UNION;
#define BBPCOMM_L_TCVR_ON_CH2_lte_tcvr_on_ch2_START  (0)
#define BBPCOMM_L_TCVR_ON_CH2_lte_tcvr_on_ch2_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_L_TCVR_ON_CH3_UNION
 结构说明  : L_TCVR_ON_CH3 寄存器结构定义。地址偏移量:0x018C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      l_tcvr_on_ch3_reg;
    struct
    {
        unsigned int  lte_tcvr_on_ch3 : 1;  /* bit[0]   : lte 通道3的tcvr_on配置：
                                                          1'b0：配置为低电平
                                                          1'b1：配置为高电平 */
        unsigned int  reserved        : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_L_TCVR_ON_CH3_UNION;
#define BBPCOMM_L_TCVR_ON_CH3_lte_tcvr_on_ch3_START  (0)
#define BBPCOMM_L_TCVR_ON_CH3_lte_tcvr_on_ch3_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_T_TCVR_ON_UNION
 结构说明  : T_TCVR_ON 寄存器结构定义。地址偏移量:0x0190，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      t_tcvr_on_reg;
    struct
    {
        unsigned int  tds_tcvr_on : 1;  /* bit[0]   : tds 的tcvr_on配置：
                                                      1'b0：配置为低电平
                                                      1'b1：配置为高电平 */
        unsigned int  reserved    : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_T_TCVR_ON_UNION;
#define BBPCOMM_T_TCVR_ON_tds_tcvr_on_START  (0)
#define BBPCOMM_T_TCVR_ON_tds_tcvr_on_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_W_TCVR_ON_UNION
 结构说明  : W_TCVR_ON 寄存器结构定义。地址偏移量:0x0194，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      w_tcvr_on_reg;
    struct
    {
        unsigned int  w_tcvr_on : 1;  /* bit[0]   : w 的tcvr_on配置：
                                                    1'b0：配置为低电平
                                                    1'b1：配置为高电平 */
        unsigned int  reserved  : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_W_TCVR_ON_UNION;
#define BBPCOMM_W_TCVR_ON_w_tcvr_on_START  (0)
#define BBPCOMM_W_TCVR_ON_w_tcvr_on_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_GM_TCVR_ON_UNION
 结构说明  : GM_TCVR_ON 寄存器结构定义。地址偏移量:0x0198，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      gm_tcvr_on_reg;
    struct
    {
        unsigned int  gm_tcvr_on : 1;  /* bit[0]   : gm 的tcvr_on配置：
                                                     1'b0：配置为低电平
                                                     1'b1：配置为高电平 */
        unsigned int  reserved   : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_GM_TCVR_ON_UNION;
#define BBPCOMM_GM_TCVR_ON_gm_tcvr_on_START  (0)
#define BBPCOMM_GM_TCVR_ON_gm_tcvr_on_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_GS_TCVR_ON_UNION
 结构说明  : GS_TCVR_ON 寄存器结构定义。地址偏移量:0x019C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      gs_tcvr_on_reg;
    struct
    {
        unsigned int  gs_tcvr_on : 1;  /* bit[0]   : gs 的tcvr_on配置：
                                                     1'b0：配置为低电平
                                                     1'b1：配置为高电平 */
        unsigned int  reserved   : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_GS_TCVR_ON_UNION;
#define BBPCOMM_GS_TCVR_ON_gs_tcvr_on_START  (0)
#define BBPCOMM_GS_TCVR_ON_gs_tcvr_on_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_C_TCVR_ON_UNION
 结构说明  : C_TCVR_ON 寄存器结构定义。地址偏移量:0x01A0，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c_tcvr_on_reg;
    struct
    {
        unsigned int  c_tcvr_on : 1;  /* bit[0]   : c2 的tcvr_on配置：
                                                    1'b0：配置为低电平
                                                    1'b1：配置为高电平 */
        unsigned int  reserved  : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_C_TCVR_ON_UNION;
#define BBPCOMM_C_TCVR_ON_c_tcvr_on_START  (0)
#define BBPCOMM_C_TCVR_ON_c_tcvr_on_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_CH0_TCVR_ON_RX_SEL_UNION
 结构说明  : CH0_TCVR_ON_RX_SEL 寄存器结构定义。地址偏移量:0x01A4，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      ch0_tcvr_on_rx_sel_reg;
    struct
    {
        unsigned int  ch0_tcvr_on_rx_sel : 1;  /* bit[0]   : CH0 的tcvr_on_rx来源选择：
                                                             1'b0：来自于逻辑选通
                                                             1'b1：来自于DSP配置，ch0_tcvr_on_rx_dsp */
        unsigned int  reserved_0         : 3;  /* bit[1-3] : 保留 */
        unsigned int  ch0_tcvr_on_rx_dsp : 1;  /* bit[4]   : ch0 DSP强制的tcvr_on_rx 配置：
                                                             1'b0：配置为低电平
                                                             1'b1：配置为高电平 */
        unsigned int  reserved_1         : 27; /* bit[5-31]: 保留 */
    } reg;
} BBPCOMM_CH0_TCVR_ON_RX_SEL_UNION;
#define BBPCOMM_CH0_TCVR_ON_RX_SEL_ch0_tcvr_on_rx_sel_START  (0)
#define BBPCOMM_CH0_TCVR_ON_RX_SEL_ch0_tcvr_on_rx_sel_END    (0)
#define BBPCOMM_CH0_TCVR_ON_RX_SEL_ch0_tcvr_on_rx_dsp_START  (4)
#define BBPCOMM_CH0_TCVR_ON_RX_SEL_ch0_tcvr_on_rx_dsp_END    (4)


/*****************************************************************************
 结构名    : BBPCOMM_CH1_TCVR_ON_RX_SEL_UNION
 结构说明  : CH1_TCVR_ON_RX_SEL 寄存器结构定义。地址偏移量:0x01A8，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      ch1_tcvr_on_rx_sel_reg;
    struct
    {
        unsigned int  ch1_tcvr_on_rx_sel : 1;  /* bit[0]   : CH1 的tcvr_on_rx来源选择：
                                                             1'b0：来自于逻辑选通
                                                             1'b1：来自于DSP配置，ch1_tcvr_on_rx_dsp */
        unsigned int  reserved_0         : 3;  /* bit[1-3] : 保留 */
        unsigned int  ch1_tcvr_on_rx_dsp : 1;  /* bit[4]   : ch1 DSP的tcvr_on_rx 配置：
                                                             1'b0：配置为低电平
                                                             1'b1：配置为高电平 */
        unsigned int  reserved_1         : 27; /* bit[5-31]: 保留 */
    } reg;
} BBPCOMM_CH1_TCVR_ON_RX_SEL_UNION;
#define BBPCOMM_CH1_TCVR_ON_RX_SEL_ch1_tcvr_on_rx_sel_START  (0)
#define BBPCOMM_CH1_TCVR_ON_RX_SEL_ch1_tcvr_on_rx_sel_END    (0)
#define BBPCOMM_CH1_TCVR_ON_RX_SEL_ch1_tcvr_on_rx_dsp_START  (4)
#define BBPCOMM_CH1_TCVR_ON_RX_SEL_ch1_tcvr_on_rx_dsp_END    (4)


/*****************************************************************************
 结构名    : BBPCOMM_CH2_TCVR_ON_RX_SEL_UNION
 结构说明  : CH2_TCVR_ON_RX_SEL 寄存器结构定义。地址偏移量:0x01AC，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      ch2_tcvr_on_rx_sel_reg;
    struct
    {
        unsigned int  ch2_tcvr_on_rx_sel : 1;  /* bit[0]   : CH2 的tcvr_on_rx来源选择：
                                                             1'b0：来自于逻辑选通
                                                             1'b1：来自于DSP配置，ch2_tcvr_on_rx_dsp */
        unsigned int  reserved_0         : 3;  /* bit[1-3] : 保留 */
        unsigned int  ch2_tcvr_on_rx_dsp : 1;  /* bit[4]   : ch2 DSP的tcvr_on_rx 配置：
                                                             1'b0：配置为低电平
                                                             1'b1：配置为高电平 */
        unsigned int  reserved_1         : 27; /* bit[5-31]: 保留 */
    } reg;
} BBPCOMM_CH2_TCVR_ON_RX_SEL_UNION;
#define BBPCOMM_CH2_TCVR_ON_RX_SEL_ch2_tcvr_on_rx_sel_START  (0)
#define BBPCOMM_CH2_TCVR_ON_RX_SEL_ch2_tcvr_on_rx_sel_END    (0)
#define BBPCOMM_CH2_TCVR_ON_RX_SEL_ch2_tcvr_on_rx_dsp_START  (4)
#define BBPCOMM_CH2_TCVR_ON_RX_SEL_ch2_tcvr_on_rx_dsp_END    (4)


/*****************************************************************************
 结构名    : BBPCOMM_CH3_TCVR_ON_RX_SEL_UNION
 结构说明  : CH3_TCVR_ON_RX_SEL 寄存器结构定义。地址偏移量:0x01B0，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      ch3_tcvr_on_rx_sel_reg;
    struct
    {
        unsigned int  ch3_tcvr_on_rx_sel : 1;  /* bit[0]   : CH3 的tcvr_on_rx来源选择：
                                                             1'b0：来自于逻辑选通
                                                             1'b1：来自于DSP配置，ch3_tcvr_on_rx_dsp */
        unsigned int  reserved_0         : 3;  /* bit[1-3] : 保留 */
        unsigned int  ch3_tcvr_on_rx_dsp : 1;  /* bit[4]   : ch3 DSP的tcvr_on_rx 配置：
                                                             1'b0：配置为低电平
                                                             1'b1：配置为高电平 */
        unsigned int  reserved_1         : 27; /* bit[5-31]: 保留 */
    } reg;
} BBPCOMM_CH3_TCVR_ON_RX_SEL_UNION;
#define BBPCOMM_CH3_TCVR_ON_RX_SEL_ch3_tcvr_on_rx_sel_START  (0)
#define BBPCOMM_CH3_TCVR_ON_RX_SEL_ch3_tcvr_on_rx_sel_END    (0)
#define BBPCOMM_CH3_TCVR_ON_RX_SEL_ch3_tcvr_on_rx_dsp_START  (4)
#define BBPCOMM_CH3_TCVR_ON_RX_SEL_ch3_tcvr_on_rx_dsp_END    (4)


/*****************************************************************************
 结构名    : BBPCOMM_CH0_TCVR_ON_TX_SEL_UNION
 结构说明  : CH0_TCVR_ON_TX_SEL 寄存器结构定义。地址偏移量:0x01B4，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      ch0_tcvr_on_tx_sel_reg;
    struct
    {
        unsigned int  ch0_tcvr_on_tx_sel : 1;  /* bit[0]   : CH0 的tcvr_on_tx来源选择：
                                                             1'b0：来自于逻辑选通
                                                             1'b1：来自于DSP配置，ch0_tcvr_on_tx_dsp */
        unsigned int  reserved_0         : 3;  /* bit[1-3] : 保留 */
        unsigned int  ch0_tcvr_on_tx_dsp : 1;  /* bit[4]   : ch0 DSP强制的tcvr_on_tx 配置：
                                                             1'b0：配置为低电平
                                                             1'b1：配置为高电平 */
        unsigned int  reserved_1         : 27; /* bit[5-31]: 保留 */
    } reg;
} BBPCOMM_CH0_TCVR_ON_TX_SEL_UNION;
#define BBPCOMM_CH0_TCVR_ON_TX_SEL_ch0_tcvr_on_tx_sel_START  (0)
#define BBPCOMM_CH0_TCVR_ON_TX_SEL_ch0_tcvr_on_tx_sel_END    (0)
#define BBPCOMM_CH0_TCVR_ON_TX_SEL_ch0_tcvr_on_tx_dsp_START  (4)
#define BBPCOMM_CH0_TCVR_ON_TX_SEL_ch0_tcvr_on_tx_dsp_END    (4)


/*****************************************************************************
 结构名    : BBPCOMM_CH1_TCVR_ON_TX_SEL_UNION
 结构说明  : CH1_TCVR_ON_TX_SEL 寄存器结构定义。地址偏移量:0x01B8，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      ch1_tcvr_on_tx_sel_reg;
    struct
    {
        unsigned int  ch1_tcvr_on_tx_sel : 1;  /* bit[0]   : CH1 的tcvr_on_tx来源选择：
                                                             1'b0：来自于逻辑选通
                                                             1'b1：来自于DSP配置，ch1_tcvr_on_tx_dsp */
        unsigned int  reserved_0         : 3;  /* bit[1-3] : 保留 */
        unsigned int  ch1_tcvr_on_tx_dsp : 1;  /* bit[4]   : ch1 DSP的tcvr_on_tx 配置：
                                                             1'b0：配置为低电平
                                                             1'b1：配置为高电平 */
        unsigned int  reserved_1         : 27; /* bit[5-31]: 保留 */
    } reg;
} BBPCOMM_CH1_TCVR_ON_TX_SEL_UNION;
#define BBPCOMM_CH1_TCVR_ON_TX_SEL_ch1_tcvr_on_tx_sel_START  (0)
#define BBPCOMM_CH1_TCVR_ON_TX_SEL_ch1_tcvr_on_tx_sel_END    (0)
#define BBPCOMM_CH1_TCVR_ON_TX_SEL_ch1_tcvr_on_tx_dsp_START  (4)
#define BBPCOMM_CH1_TCVR_ON_TX_SEL_ch1_tcvr_on_tx_dsp_END    (4)


/*****************************************************************************
 结构名    : BBPCOMM_CH2_TCVR_ON_TX_SEL_UNION
 结构说明  : CH2_TCVR_ON_TX_SEL 寄存器结构定义。地址偏移量:0x01BC，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      ch2_tcvr_on_tx_sel_reg;
    struct
    {
        unsigned int  ch2_tcvr_on_tx_sel : 1;  /* bit[0]   : CH2 的tcvr_on_tx来源选择：
                                                             1'b0：来自于逻辑选通
                                                             1'b1：来自于DSP配置，ch2_tcvr_on_tx_dsp */
        unsigned int  reserved_0         : 3;  /* bit[1-3] : 保留 */
        unsigned int  ch2_tcvr_on_tx_dsp : 1;  /* bit[4]   : ch2 DSP的tcvr_on_tx 配置：
                                                             1'b0：配置为低电平
                                                             1'b1：配置为高电平 */
        unsigned int  reserved_1         : 27; /* bit[5-31]: 保留 */
    } reg;
} BBPCOMM_CH2_TCVR_ON_TX_SEL_UNION;
#define BBPCOMM_CH2_TCVR_ON_TX_SEL_ch2_tcvr_on_tx_sel_START  (0)
#define BBPCOMM_CH2_TCVR_ON_TX_SEL_ch2_tcvr_on_tx_sel_END    (0)
#define BBPCOMM_CH2_TCVR_ON_TX_SEL_ch2_tcvr_on_tx_dsp_START  (4)
#define BBPCOMM_CH2_TCVR_ON_TX_SEL_ch2_tcvr_on_tx_dsp_END    (4)


/*****************************************************************************
 结构名    : BBPCOMM_CH3_TCVR_ON_TX_SEL_UNION
 结构说明  : CH3_TCVR_ON_TX_SEL 寄存器结构定义。地址偏移量:0x01C0，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      ch3_tcvr_on_tx_sel_reg;
    struct
    {
        unsigned int  ch3_tcvr_on_tx_sel : 1;  /* bit[0]   : CH3 的tcvr_on_tx来源选择：
                                                             1'b0：来自于逻辑选通
                                                             1'b1：来自于DSP配置，ch3_tcvr_on_tx_dsp */
        unsigned int  reserved_0         : 3;  /* bit[1-3] : 保留 */
        unsigned int  ch3_tcvr_on_tx_dsp : 1;  /* bit[4]   : ch3 DSP的tcvr_on_tx 配置：
                                                             1'b0：配置为低电平
                                                             1'b1：配置为高电平 */
        unsigned int  reserved_1         : 27; /* bit[5-31]: 保留 */
    } reg;
} BBPCOMM_CH3_TCVR_ON_TX_SEL_UNION;
#define BBPCOMM_CH3_TCVR_ON_TX_SEL_ch3_tcvr_on_tx_sel_START  (0)
#define BBPCOMM_CH3_TCVR_ON_TX_SEL_ch3_tcvr_on_tx_sel_END    (0)
#define BBPCOMM_CH3_TCVR_ON_TX_SEL_ch3_tcvr_on_tx_dsp_START  (4)
#define BBPCOMM_CH3_TCVR_ON_TX_SEL_ch3_tcvr_on_tx_dsp_END    (4)


/*****************************************************************************
 结构名    : BBPCOMM_CH0_TCVR_ON_OUT_CFG_UNION
 结构说明  : CH0_TCVR_ON_OUT_CFG 寄存器结构定义。地址偏移量:0x01C4，初值:0x00000013，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      ch0_tcvr_on_out_cfg_reg;
    struct
    {
        unsigned int  ch0_tcvr_on_rx_out_cfg : 4;  /* bit[0-3] : 输出管脚ch0_tcvr_on_out映射配置：
                                                                 bit3：
                                                                 1：ch3_tcvr_on_rx拉高即拉高
                                                                 0：不来自于ch3_tcvr_on_rx
                                                                 bit2：
                                                                 1：ch2_tcvr_on_rx拉高即拉高
                                                                 0：不来自于ch2_tcvr_on_rx
                                                                 bit1：
                                                                 1：ch1_tcvr_on_rx拉高即拉高
                                                                 0：不来自于ch1_tcvr_on_rx
                                                                 bit0：
                                                                 1：ch0_tcvr_on_rx拉高即拉高
                                                                 0：不来自于ch0_tcvr_on_rx */
        unsigned int  ch0_tcvr_on_tx_out_cfg : 4;  /* bit[4-7] : 输出管脚ch0_tcvr_on_out映射配置：
                                                                 bit3：
                                                                 1：ch3_tcvr_on_tx拉高即拉高
                                                                 0：不来自于ch3_tcvr_on_tx
                                                                 bit2：
                                                                 1：ch2_tcvr_on_tx拉高即拉高
                                                                 0：不来自于ch2_tcvr_on_tx
                                                                 bit1：
                                                                 1：ch1_tcvr_on_tx拉高即拉高
                                                                 0：不来自于ch1_tcvr_on_tx
                                                                 bit0：
                                                                 1：ch0_tcvr_on_tx拉高即拉高
                                                                 0：不来自于ch0_tcvr_on_tx */
        unsigned int  reserved               : 24; /* bit[8-31]: 保留 */
    } reg;
} BBPCOMM_CH0_TCVR_ON_OUT_CFG_UNION;
#define BBPCOMM_CH0_TCVR_ON_OUT_CFG_ch0_tcvr_on_rx_out_cfg_START  (0)
#define BBPCOMM_CH0_TCVR_ON_OUT_CFG_ch0_tcvr_on_rx_out_cfg_END    (3)
#define BBPCOMM_CH0_TCVR_ON_OUT_CFG_ch0_tcvr_on_tx_out_cfg_START  (4)
#define BBPCOMM_CH0_TCVR_ON_OUT_CFG_ch0_tcvr_on_tx_out_cfg_END    (7)


/*****************************************************************************
 结构名    : BBPCOMM_CH1_TCVR_ON_OUT_CFG_UNION
 结构说明  : CH1_TCVR_ON_OUT_CFG 寄存器结构定义。地址偏移量:0x01C8，初值:0x0000002C，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      ch1_tcvr_on_out_cfg_reg;
    struct
    {
        unsigned int  ch1_tcvr_on_rx_out_cfg : 4;  /* bit[0-3] : 输出管脚ch1_tcvr_on_out映射配置：
                                                                 bit3：
                                                                 1：ch3_tcvr_on_rx拉高即拉高
                                                                 0：不来自于ch3_tcvr_on_rx
                                                                 bit2：
                                                                 1：ch2_tcvr_on_rx拉高即拉高
                                                                 0：不来自于ch2_tcvr_on_rx
                                                                 bit1：
                                                                 1：ch1_tcvr_on_rx拉高即拉高
                                                                 0：不来自于ch1_tcvr_on_rx
                                                                 bit0：
                                                                 1：ch0_tcvr_on_rx拉高即拉高
                                                                 0：不来自于ch0_tcvr_on_rx */
        unsigned int  ch1_tcvr_on_tx_out_cfg : 4;  /* bit[4-7] : 输出管脚ch1_tcvr_on_out映射配置：
                                                                 bit3：
                                                                 1：ch3_tcvr_on_tx拉高即拉高
                                                                 0：不来自于ch3_tcvr_on_tx
                                                                 bit2：
                                                                 1：ch2_tcvr_on_tx拉高即拉高
                                                                 0：不来自于ch2_tcvr_on_tx
                                                                 bit1：
                                                                 1：ch1_tcvr_on_tx拉高即拉高
                                                                 0：不来自于ch1_tcvr_on_tx
                                                                 bit0：
                                                                 1：ch0_tcvr_on_tx拉高即拉高
                                                                 0：不来自于ch0_tcvr_on_tx */
        unsigned int  reserved               : 24; /* bit[8-31]: 保留 */
    } reg;
} BBPCOMM_CH1_TCVR_ON_OUT_CFG_UNION;
#define BBPCOMM_CH1_TCVR_ON_OUT_CFG_ch1_tcvr_on_rx_out_cfg_START  (0)
#define BBPCOMM_CH1_TCVR_ON_OUT_CFG_ch1_tcvr_on_rx_out_cfg_END    (3)
#define BBPCOMM_CH1_TCVR_ON_OUT_CFG_ch1_tcvr_on_tx_out_cfg_START  (4)
#define BBPCOMM_CH1_TCVR_ON_OUT_CFG_ch1_tcvr_on_tx_out_cfg_END    (7)


/*****************************************************************************
 结构名    : BBPCOMM_CH2_TCVR_ON_OUT_CFG_UNION
 结构说明  : CH2_TCVR_ON_OUT_CFG 寄存器结构定义。地址偏移量:0x01CC，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      ch2_tcvr_on_out_cfg_reg;
    struct
    {
        unsigned int  ch2_tcvr_on_rx_out_cfg : 4;  /* bit[0-3] : 输出管脚ch2_tcvr_on_out映射配置：
                                                                 bit3：
                                                                 1：ch3_tcvr_on_rx拉高即拉高
                                                                 0：不来自于ch3_tcvr_on_rx
                                                                 bit2：
                                                                 1：ch2_tcvr_on_rx拉高即拉高
                                                                 0：不来自于ch2_tcvr_on_rx
                                                                 bit1：
                                                                 1：ch1_tcvr_on_rx拉高即拉高
                                                                 0：不来自于ch1_tcvr_on_rx
                                                                 bit0：
                                                                 1：ch0_tcvr_on_rx拉高即拉高
                                                                 0：不来自于ch0_tcvr_on_rx */
        unsigned int  ch2_tcvr_on_tx_out_cfg : 4;  /* bit[4-7] : 输出管脚ch2_tcvr_on_out映射配置：
                                                                 bit3：
                                                                 1：ch3_tcvr_on_tx拉高即拉高
                                                                 0：不来自于ch3_tcvr_on_tx
                                                                 bit2：
                                                                 1：ch2_tcvr_on_tx拉高即拉高
                                                                 0：不来自于ch2_tcvr_on_tx
                                                                 bit1：
                                                                 1：ch1_tcvr_on_tx拉高即拉高
                                                                 0：不来自于ch1_tcvr_on_tx
                                                                 bit0：
                                                                 1：ch0_tcvr_on_tx拉高即拉高
                                                                 0：不来自于ch0_tcvr_on_tx */
        unsigned int  reserved               : 24; /* bit[8-31]: 保留 */
    } reg;
} BBPCOMM_CH2_TCVR_ON_OUT_CFG_UNION;
#define BBPCOMM_CH2_TCVR_ON_OUT_CFG_ch2_tcvr_on_rx_out_cfg_START  (0)
#define BBPCOMM_CH2_TCVR_ON_OUT_CFG_ch2_tcvr_on_rx_out_cfg_END    (3)
#define BBPCOMM_CH2_TCVR_ON_OUT_CFG_ch2_tcvr_on_tx_out_cfg_START  (4)
#define BBPCOMM_CH2_TCVR_ON_OUT_CFG_ch2_tcvr_on_tx_out_cfg_END    (7)


/*****************************************************************************
 结构名    : BBPCOMM_CH3_TCVR_ON_OUT_CFG_UNION
 结构说明  : CH3_TCVR_ON_OUT_CFG 寄存器结构定义。地址偏移量:0x01D0，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      ch3_tcvr_on_out_cfg_reg;
    struct
    {
        unsigned int  ch3_tcvr_on_rx_out_cfg : 4;  /* bit[0-3] : 输出管脚ch3_tcvr_on_out映射配置：
                                                                 bit3：
                                                                 1：ch3_tcvr_on_rx拉高即拉高
                                                                 0：不来自于ch3_tcvr_on_rx
                                                                 bit2：
                                                                 1：ch2_tcvr_on_rx拉高即拉高
                                                                 0：不来自于ch2_tcvr_on_rx
                                                                 bit1：
                                                                 1：ch1_tcvr_on_rx拉高即拉高
                                                                 0：不来自于ch1_tcvr_on_rx
                                                                 bit0：
                                                                 1：ch0_tcvr_on_rx拉高即拉高
                                                                 0：不来自于ch0_tcvr_on_rx */
        unsigned int  ch3_tcvr_on_tx_out_cfg : 4;  /* bit[4-7] : 输出管脚ch3_tcvr_on_out映射配置：
                                                                 bit3：
                                                                 1：ch3_tcvr_on_tx拉高即拉高
                                                                 0：不来自于ch3_tcvr_on_tx
                                                                 bit2：
                                                                 1：ch2_tcvr_on_tx拉高即拉高
                                                                 0：不来自于ch2_tcvr_on_tx
                                                                 bit1：
                                                                 1：ch1_tcvr_on_tx拉高即拉高
                                                                 0：不来自于ch1_tcvr_on_tx
                                                                 bit0：
                                                                 1：ch0_tcvr_on_tx拉高即拉高
                                                                 0：不来自于ch0_tcvr_on_tx */
        unsigned int  reserved               : 24; /* bit[8-31]: 保留 */
    } reg;
} BBPCOMM_CH3_TCVR_ON_OUT_CFG_UNION;
#define BBPCOMM_CH3_TCVR_ON_OUT_CFG_ch3_tcvr_on_rx_out_cfg_START  (0)
#define BBPCOMM_CH3_TCVR_ON_OUT_CFG_ch3_tcvr_on_rx_out_cfg_END    (3)
#define BBPCOMM_CH3_TCVR_ON_OUT_CFG_ch3_tcvr_on_tx_out_cfg_START  (4)
#define BBPCOMM_CH3_TCVR_ON_OUT_CFG_ch3_tcvr_on_tx_out_cfg_END    (7)


/*****************************************************************************
 结构名    : BBPCOMM_CPU_CFG_SC_EN_UNION
 结构说明  : CPU_CFG_SC_EN 寄存器结构定义。地址偏移量:0x01E0，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      cpu_cfg_sc_en_reg;
    struct
    {
        unsigned int  cpu_cfg_sc_en : 1;  /* bit[0]   : comm控制sc_pll使能，1：通过comm控制sc_pll，0：不通过comm控制sc_pll */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_CPU_CFG_SC_EN_UNION;
#define BBPCOMM_CPU_CFG_SC_EN_cpu_cfg_sc_en_START  (0)
#define BBPCOMM_CPU_CFG_SC_EN_cpu_cfg_sc_en_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_CPU_INT1_CFG_SC_EN_UNION
 结构说明  : CPU_INT1_CFG_SC_EN 寄存器结构定义。地址偏移量:0x01E4，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      cpu_int1_cfg_sc_en_reg;
    struct
    {
        unsigned int  cpu_int1_cfg_sc_en : 1;  /* bit[0]   : comm向sc_pll发送中断1使能，1：有效，0无效 */
        unsigned int  reserved           : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_CPU_INT1_CFG_SC_EN_UNION;
#define BBPCOMM_CPU_INT1_CFG_SC_EN_cpu_int1_cfg_sc_en_START  (0)
#define BBPCOMM_CPU_INT1_CFG_SC_EN_cpu_int1_cfg_sc_en_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_CPU_INT2_CFG_SC_EN_UNION
 结构说明  : CPU_INT2_CFG_SC_EN 寄存器结构定义。地址偏移量:0x01E8，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      cpu_int2_cfg_sc_en_reg;
    struct
    {
        unsigned int  cpu_int2_cfg_sc_en : 1;  /* bit[0]   : comm向sc_pll发送中断2使能，1：有效，0无效 */
        unsigned int  reserved           : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_CPU_INT2_CFG_SC_EN_UNION;
#define BBPCOMM_CPU_INT2_CFG_SC_EN_cpu_int2_cfg_sc_en_START  (0)
#define BBPCOMM_CPU_INT2_CFG_SC_EN_cpu_int2_cfg_sc_en_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_CPU_PRO_SOFT_CFG_SC_IND_UNION
 结构说明  : CPU_PRO_SOFT_CFG_SC_IND 寄存器结构定义。地址偏移量:0x01EC，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      cpu_pro_soft_cfg_sc_ind_reg;
    struct
    {
        unsigned int  cpu_pro_soft_cfg_sc_ind : 1;  /* bit[0]   : 软件向sc_pll配置的主模的ind信号 */
        unsigned int  reserved                : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_CPU_PRO_SOFT_CFG_SC_IND_UNION;
#define BBPCOMM_CPU_PRO_SOFT_CFG_SC_IND_cpu_pro_soft_cfg_sc_ind_START  (0)
#define BBPCOMM_CPU_PRO_SOFT_CFG_SC_IND_cpu_pro_soft_cfg_sc_ind_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_CPU_SEC_SOFT_CFG_SC_IND_UNION
 结构说明  : CPU_SEC_SOFT_CFG_SC_IND 寄存器结构定义。地址偏移量:0x01F0，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      cpu_sec_soft_cfg_sc_ind_reg;
    struct
    {
        unsigned int  cpu_sec_soft_cfg_sc_ind : 1;  /* bit[0]   : 软件向sc_pll配置的从模的ind信号 */
        unsigned int  reserved                : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_CPU_SEC_SOFT_CFG_SC_IND_UNION;
#define BBPCOMM_CPU_SEC_SOFT_CFG_SC_IND_cpu_sec_soft_cfg_sc_ind_START  (0)
#define BBPCOMM_CPU_SEC_SOFT_CFG_SC_IND_cpu_sec_soft_cfg_sc_ind_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_CPU_SC_CH_SEL_UNION
 结构说明  : CPU_SC_CH_SEL 寄存器结构定义。地址偏移量:0x01F4，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      cpu_sc_ch_sel_reg;
    struct
    {
        unsigned int  cpu_sc_ch_sel : 2;  /* bit[0-1] : 0：根据通道0主从模产生配置sc_pll信号
                                                        1：根据通道1主从模产生配置sc_pll信号
                                                        2：根据通道2主从模产生配置sc_pll信号
                                                        3：根据通道3主从模产生配置sc_pll信号 */
        unsigned int  reserved      : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_CPU_SC_CH_SEL_UNION;
#define BBPCOMM_CPU_SC_CH_SEL_cpu_sc_ch_sel_START  (0)
#define BBPCOMM_CPU_SC_CH_SEL_cpu_sc_ch_sel_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_TIMING_GET_IND_UNION
 结构说明  : TIMING_GET_IND 寄存器结构定义。地址偏移量:0x0204，初值:0x00000030，宽度:32
 寄存器说明: 定时锁存使能指示寄存器
*****************************************************************************/
typedef union
{
    unsigned int      timing_get_ind_reg;
    struct
    {
        unsigned int  timing_get_ind   : 1;  /* bit[0]   : 逻辑自清零。
                                                           L/T模BBE16 DSP需要获取定时关系时配置生效，CTU逻辑根据此信号锁存LTE/W/Gm/Gs/TDS/C的系统定时，CTU的内部定时供DSP查询。 */
        unsigned int  reserved_0       : 3;  /* bit[1-3] : 保留 */
        unsigned int  timing_get_c_sel : 2;  /* bit[4-5] : L/T模BBE16 DSP读取C2模bbp计数器结果1x、evdo还是base_cnt。   00：1x定时，01：evdo定时，10： base_cnt ，11：无效。 */
        unsigned int  reserved_1       : 26; /* bit[6-31]: 保留 */
    } reg;
} BBPCOMM_TIMING_GET_IND_UNION;
#define BBPCOMM_TIMING_GET_IND_timing_get_ind_START    (0)
#define BBPCOMM_TIMING_GET_IND_timing_get_ind_END      (0)
#define BBPCOMM_TIMING_GET_IND_timing_get_c_sel_START  (4)
#define BBPCOMM_TIMING_GET_IND_timing_get_c_sel_END    (5)


/*****************************************************************************
 结构名    : BBPCOMM_INT_WAIT_CNT_UNION
 结构说明  : INT_WAIT_CNT 寄存器结构定义。地址偏移量:0x0210，初值:0x0000001E，宽度:32
 寄存器说明: 中断延迟寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_wait_cnt_reg;
    struct
    {
        unsigned int  int_wait_cnt : 16; /* bit[0-15] : CTU中断上报等待时间，单位为一个CLK周期。
                                                        DSP清除中断标志寄存器的某种类型bit后，CTU上报中断电平需要拉低，如果此时中断标志寄存器还有其它中断类型有效，则需等待int_wait_cnt个时钟周期后再拉高CTU上报中断。
                                                        配置时刻：上电初始化
                                                        生效时刻：立即生效 */
        unsigned int  reserved     : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_WAIT_CNT_UNION;
#define BBPCOMM_INT_WAIT_CNT_int_wait_cnt_START  (0)
#define BBPCOMM_INT_WAIT_CNT_int_wait_cnt_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_TIMING_VALID_UNION
 结构说明  : TIMING_VALID 寄存器结构定义。地址偏移量:0x0218，初值:0x00000030，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      timing_valid_reg;
    struct
    {
        unsigned int  o_timing_valid     : 1;  /* bit[0]   : 定时上报有效标志，高有效。
                                                             L/T模BBE16 DSP配置timing_get_ind后，查询此标志，如果为高，则可以获取LTE，W，Gm，Gs, TDS的系统定时。
                                                             DSP读取定时，在DSP下次启动新的timing_get_ind时拉低此信号。 */
        unsigned int  reserved_0         : 3;  /* bit[1-3] : 保留 */
        unsigned int  timing_valid_c_sel : 2;  /* bit[4-5] : 上报c2模的计数器给L/T模BBE16 DSP的是1x、evdo还是base_cnt
                                                             00：1x定时
                                                             01： evdo定时
                                                             10： basecent */
        unsigned int  reserved_1         : 26; /* bit[6-31]: 保留 */
    } reg;
} BBPCOMM_TIMING_VALID_UNION;
#define BBPCOMM_TIMING_VALID_o_timing_valid_START      (0)
#define BBPCOMM_TIMING_VALID_o_timing_valid_END        (0)
#define BBPCOMM_TIMING_VALID_timing_valid_c_sel_START  (4)
#define BBPCOMM_TIMING_VALID_timing_valid_c_sel_END    (5)


/*****************************************************************************
 结构名    : BBPCOMM_W_TIMING_DSP_UNION
 结构说明  : W_TIMING_DSP 寄存器结构定义。地址偏移量:0x021C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      w_timing_dsp_reg;
    struct
    {
        unsigned int  w_clk_cnt_dsp  : 4;  /* bit[0-3]  : [3:0]为chip内时钟计数，范围0~15 */
        unsigned int  w_chip_cnt_dsp : 12; /* bit[4-15] : [15:4]为时隙内chip计数，范围0~2559 */
        unsigned int  w_slot_cnt_dsp : 4;  /* bit[16-19]: [19:16]为时隙计数，范围0~14 */
        unsigned int  w_sfn_dsp      : 12; /* bit[20-31]: L/T模BBE16 DSP读取W的系统定时信息，由DSP 配置timing_get_ind触发上报。
                                                          上报时刻：触发后检测o_timing_valid为1有效。
                                                          [31:20]表示W的SFN计数（源自w_timing_b[11:0]），范围0~4095。 */
    } reg;
} BBPCOMM_W_TIMING_DSP_UNION;
#define BBPCOMM_W_TIMING_DSP_w_clk_cnt_dsp_START   (0)
#define BBPCOMM_W_TIMING_DSP_w_clk_cnt_dsp_END     (3)
#define BBPCOMM_W_TIMING_DSP_w_chip_cnt_dsp_START  (4)
#define BBPCOMM_W_TIMING_DSP_w_chip_cnt_dsp_END    (15)
#define BBPCOMM_W_TIMING_DSP_w_slot_cnt_dsp_START  (16)
#define BBPCOMM_W_TIMING_DSP_w_slot_cnt_dsp_END    (19)
#define BBPCOMM_W_TIMING_DSP_w_sfn_dsp_START       (20)
#define BBPCOMM_W_TIMING_DSP_w_sfn_dsp_END         (31)


/*****************************************************************************
 结构名    : BBPCOMM_GM_FN_DSP_UNION
 结构说明  : GM_FN_DSP 寄存器结构定义。地址偏移量:0x0224，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      gm_fn_dsp_reg;
    struct
    {
        unsigned int  o_gm_fn_dsp : 22; /* bit[0-21] : GM的FN计数（源自gm_timing_a[21:0]），由L/T模BBE16 DSP配置timing_get_ind触发上报。其中[10:0]表示fn_low,范围0~1325；[21:11]表示fn_hign,范围0~2047。
                                                       上报时刻：触发后立即生效 */
        unsigned int  reserved    : 10; /* bit[22-31]: 保留 */
    } reg;
} BBPCOMM_GM_FN_DSP_UNION;
#define BBPCOMM_GM_FN_DSP_o_gm_fn_dsp_START  (0)
#define BBPCOMM_GM_FN_DSP_o_gm_fn_dsp_END    (21)


/*****************************************************************************
 结构名    : BBPCOMM_GM_QB_DSP_UNION
 结构说明  : GM_QB_DSP 寄存器结构定义。地址偏移量:0x0228，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      gm_qb_dsp_reg;
    struct
    {
        unsigned int  o_gm_qb_dsp : 13; /* bit[0-12] : GM的系统定时Qb信息，由L/T模BBE16 DSP配置timing_get_ind触发上报。
                                                        [12:0]表示 G系统定时帧内Qb计数（源自gm_timing_b[12:0]），范围0~4999。
                                                       上报时刻：触发后立即生效 */
        unsigned int  reserved    : 19; /* bit[13-31]: 保留 */
    } reg;
} BBPCOMM_GM_QB_DSP_UNION;
#define BBPCOMM_GM_QB_DSP_o_gm_qb_dsp_START  (0)
#define BBPCOMM_GM_QB_DSP_o_gm_qb_dsp_END    (12)


/*****************************************************************************
 结构名    : BBPCOMM_GS_FN_DSP_UNION
 结构说明  : GS_FN_DSP 寄存器结构定义。地址偏移量:0x0230，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      gs_fn_dsp_reg;
    struct
    {
        unsigned int  gs_fn_dsp : 22; /* bit[0-21] : GS的FN计数（源自gs_timing_a[21:0]），由L/T模BBE16 DSP配置timing_get_ind触发上报。其中[10:0]表示fn_low,范围0~1325；[21:11]表示fn_hign,范围0~2047。
                                                     上报时刻：触发后立即生效 */
        unsigned int  reserved  : 10; /* bit[22-31]: 保留 */
    } reg;
} BBPCOMM_GS_FN_DSP_UNION;
#define BBPCOMM_GS_FN_DSP_gs_fn_dsp_START  (0)
#define BBPCOMM_GS_FN_DSP_gs_fn_dsp_END    (21)


/*****************************************************************************
 结构名    : BBPCOMM_GS_QB_DSP_UNION
 结构说明  : GS_QB_DSP 寄存器结构定义。地址偏移量:0x0234，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      gs_qb_dsp_reg;
    struct
    {
        unsigned int  o_gs_qb_dsp : 13; /* bit[0-12] : GS的系统定时Qb信息，由L/T模BBE16 DSP配置timing_get_ind触发上报。
                                                        [12:0]表示 GS系统定时帧内Qb计数（源自gs_timing_b[12:0]），范围0~4999。
                                                       上报时刻：触发后立即生效 */
        unsigned int  reserved    : 19; /* bit[13-31]: 保留 */
    } reg;
} BBPCOMM_GS_QB_DSP_UNION;
#define BBPCOMM_GS_QB_DSP_o_gs_qb_dsp_START  (0)
#define BBPCOMM_GS_QB_DSP_o_gs_qb_dsp_END    (12)


/*****************************************************************************
 结构名    : BBPCOMM_LTE_TIMING_DSP_UNION
 结构说明  : LTE_TIMING_DSP 寄存器结构定义。地址偏移量:0x023C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      lte_timing_dsp_reg;
    struct
    {
        unsigned int  o_lte_sys_ts_cnt_dsp     : 15; /* bit[0-14] : [14:0]是子帧内计数。  */
        unsigned int  reserved_0               : 1;  /* bit[15-15]: 保留 */
        unsigned int  o_lte_sys_subfrm_cnt_dsp : 4;  /* bit[16-19]: [19:16]是子帧计数 */
        unsigned int  o_lte_sfn_dsp            : 10; /* bit[20-29]: LTE的系统定时。由L/T模BBE16 DSP配置timing_get_ind触发上报。
                                                                    上报时刻：触发后立即生效
                                                                    其中:
                                                                    [29:20]表示SFN计数，范围0~1023 */
        unsigned int  reserved_1               : 2;  /* bit[30-31]: 保留 */
    } reg;
} BBPCOMM_LTE_TIMING_DSP_UNION;
#define BBPCOMM_LTE_TIMING_DSP_o_lte_sys_ts_cnt_dsp_START      (0)
#define BBPCOMM_LTE_TIMING_DSP_o_lte_sys_ts_cnt_dsp_END        (14)
#define BBPCOMM_LTE_TIMING_DSP_o_lte_sys_subfrm_cnt_dsp_START  (16)
#define BBPCOMM_LTE_TIMING_DSP_o_lte_sys_subfrm_cnt_dsp_END    (19)
#define BBPCOMM_LTE_TIMING_DSP_o_lte_sfn_dsp_START             (20)
#define BBPCOMM_LTE_TIMING_DSP_o_lte_sfn_dsp_END               (29)


/*****************************************************************************
 结构名    : BBPCOMM_TDS_TIMING1_DSP_UNION
 结构说明  : TDS_TIMING1_DSP 寄存器结构定义。地址偏移量:0x0244，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      tds_timing1_dsp_reg;
    struct
    {
        unsigned int  o_tds_timing1_dsp : 16; /* bit[0-15] : TDS的系统定时。由L/T模BBE16 DSP配置timing_get_ind触发上报。本寄存器上报的是TDS的tcfsr系统子帧号0~65535循环计数，TDS实际有效子帧范围为0~8191
                                                             上报时刻：触发后立即生效 */
        unsigned int  reserved          : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_TDS_TIMING1_DSP_UNION;
#define BBPCOMM_TDS_TIMING1_DSP_o_tds_timing1_dsp_START  (0)
#define BBPCOMM_TDS_TIMING1_DSP_o_tds_timing1_dsp_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_TDS_TIMING2_DSP_UNION
 结构说明  : TDS_TIMING2_DSP 寄存器结构定义。地址偏移量:0x0248，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      tds_timing2_dsp_reg;
    struct
    {
        unsigned int  o_tds_timing2_dsp : 20; /* bit[0-19] : TDS的系统定时。由L/T模BBE16 DSP 配置timing_get_ind触发上报。本寄存器上报的是是TDS的framc帧计数
                                                             上报时刻：触发后立即生效 */
        unsigned int  reserved          : 12; /* bit[20-31]: 保留 */
    } reg;
} BBPCOMM_TDS_TIMING2_DSP_UNION;
#define BBPCOMM_TDS_TIMING2_DSP_o_tds_timing2_dsp_START  (0)
#define BBPCOMM_TDS_TIMING2_DSP_o_tds_timing2_dsp_END    (19)


/*****************************************************************************
 结构名    : BBPCOMM_C_TIMING_DSP_UNION
 结构说明  : C_TIMING_DSP 寄存器结构定义。地址偏移量:0x0250，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c_timing_dsp_reg;
    struct
    {
        unsigned int  o_c_timing1_dsp : 30; /* bit[0-29] : C2模定时信息上报。 
                                                           1X模式：
                                                           Bit[4:0]   1/4chip     计数范围0~24  
                                                           Bit[6:5]   chip        计数范围0~3
                                                           Bit[17:7]  chip number 计数范围0~1535
                                                           Bit[23:18] 80ms        计数范围0~63
                                                           Bit[29:24] 2s/5.12s超帧计数范围0~24/0~63
                                                           EVDO：
                                                           Bit[4:0]   1/4chip     计数范围0~24  Bit[6:5]   chip        计数范围0~3
                                                           Bit[21:7]  chip number 计数范围0~32767
                                                           Bit[23:22] 80ms        计数范围0~63
                                                           Bit[29:24] 2s/5.12s超帧计数范围0~24/0~63
                                                           BASE_CNT：
                                                           Bit[4:0]   1/4chip     计数范围0~24  
                                                           Bit[6:5]   chip        计数范围0~3
                                                           Bit[21:7]  chip number 计数范围0~32767
                                                           Bit[23:22]  80ms       计数范围0~63
                                                           Bit[28:24]  2s超帧     计数范围0~24 */
        unsigned int  reserved        : 2;  /* bit[30-31]: 保留 */
    } reg;
} BBPCOMM_C_TIMING_DSP_UNION;
#define BBPCOMM_C_TIMING_DSP_o_c_timing1_dsp_START  (0)
#define BBPCOMM_C_TIMING_DSP_o_c_timing1_dsp_END    (29)


/*****************************************************************************
 结构名    : BBPCOMM_DSP_WAITTIME_UNION
 结构说明  : DSP_WAITTIME 寄存器结构定义。地址偏移量:0x0260，初值:0x0000FFFF，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dsp_waittime_reg;
    struct
    {
        unsigned int  dsp_mipi_wait_time : 8;  /* bit[0-7]  : 通过xbbp向MIPI master发出回读类指令时,DSP等待回读结果长度配置 */
        unsigned int  dsp_ssi_wait_time  : 8;  /* bit[8-15] : 通过xbbp向SSI master发出回读类指令时,DSP等待回读结果长度配置 */
        unsigned int  reserved           : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_DSP_WAITTIME_UNION;
#define BBPCOMM_DSP_WAITTIME_dsp_mipi_wait_time_START  (0)
#define BBPCOMM_DSP_WAITTIME_dsp_mipi_wait_time_END    (7)
#define BBPCOMM_DSP_WAITTIME_dsp_ssi_wait_time_START   (8)
#define BBPCOMM_DSP_WAITTIME_dsp_ssi_wait_time_END     (15)


/*****************************************************************************
 结构名    : BBPCOMM_TIMING_GET_IND1_UNION
 结构说明  : TIMING_GET_IND1 寄存器结构定义。地址偏移量:0x0270，初值:0x00000030，宽度:32
 寄存器说明: 定时锁存使能指示寄存器
*****************************************************************************/
typedef union
{
    unsigned int      timing_get_ind1_reg;
    struct
    {
        unsigned int  timing_get_ind1   : 1;  /* bit[0]   : 逻辑自清零。
                                                            arm需要获取定时关系时配置生效，CTU逻辑根据此信号锁存LTE/W/Gm/Gs/TDS/C的系统定时，CTU的内部定时供DSP查询。 */
        unsigned int  reserved_0        : 3;  /* bit[1-3] : 保留 */
        unsigned int  timing_get_c_sel1 : 2;  /* bit[4-5] : arm读取C2模bbp计数器结果1x、evdo还是base_cnt。   00：1x定时，01：evdo定时，10： base_cnt ，11：无效。 */
        unsigned int  reserved_1        : 26; /* bit[6-31]: 保留 */
    } reg;
} BBPCOMM_TIMING_GET_IND1_UNION;
#define BBPCOMM_TIMING_GET_IND1_timing_get_ind1_START    (0)
#define BBPCOMM_TIMING_GET_IND1_timing_get_ind1_END      (0)
#define BBPCOMM_TIMING_GET_IND1_timing_get_c_sel1_START  (4)
#define BBPCOMM_TIMING_GET_IND1_timing_get_c_sel1_END    (5)


/*****************************************************************************
 结构名    : BBPCOMM_TIMING_GET_W_SEL_UNION
 结构说明  : TIMING_GET_W_SEL 寄存器结构定义。地址偏移量:0x0278，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      timing_get_w_sel_reg;
    struct
    {
        unsigned int  timing_get_w_sel : 2;  /* bit[0-1] : L/T模BBE16 DSP读取W模bbp计数器结果sys_cnt还是base_cnt。00（二进制）：sys_cnt，01：base_cnt 10：无效 11：无效
                                                           timing_get_mode无效时，不需配置，无意义 */
        unsigned int  reserved         : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_TIMING_GET_W_SEL_UNION;
#define BBPCOMM_TIMING_GET_W_SEL_timing_get_w_sel_START  (0)
#define BBPCOMM_TIMING_GET_W_SEL_timing_get_w_sel_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_TIMING_VALID_W_SEL_UNION
 结构说明  : TIMING_VALID_W_SEL 寄存器结构定义。地址偏移量:0x027C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      timing_valid_w_sel_reg;
    struct
    {
        unsigned int  timing_valid_w_sel : 2;  /* bit[0-1] : 上报w模的计数器给L/T模BBE16 DSP的是sys_cnt还是base_cnt
                                                             00（二进制）： sys_cnt
                                                             01： basecent 10：无效  11：无效  */
        unsigned int  reserved           : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_TIMING_VALID_W_SEL_UNION;
#define BBPCOMM_TIMING_VALID_W_SEL_timing_valid_w_sel_START  (0)
#define BBPCOMM_TIMING_VALID_W_SEL_timing_valid_w_sel_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_TIMING_GET_W_SEL1_UNION
 结构说明  : TIMING_GET_W_SEL1 寄存器结构定义。地址偏移量:0x0280，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      timing_get_w_sel1_reg;
    struct
    {
        unsigned int  timing_get_w_sel1 : 2;  /* bit[0-1] : ARM读取W模bbp计数器结果sys_cnt还是base_cnt。00（二进制）：sys_cnt，01：base_cnt 10：无效 11：无效
                                                            timing_get_mode无效时，不需配置，无意义 */
        unsigned int  reserved          : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_TIMING_GET_W_SEL1_UNION;
#define BBPCOMM_TIMING_GET_W_SEL1_timing_get_w_sel1_START  (0)
#define BBPCOMM_TIMING_GET_W_SEL1_timing_get_w_sel1_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_TIMING_VALID_W_SEL1_UNION
 结构说明  : TIMING_VALID_W_SEL1 寄存器结构定义。地址偏移量:0x0284，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      timing_valid_w_sel1_reg;
    struct
    {
        unsigned int  timing_valid_w_sel1 : 2;  /* bit[0-1] : 上报的计数器给arm的是w模bbp的sys_cnt还是base_cnt
                                                              00：sys_cnt定时
                                                              01：base_cnt定时 
                                                              10：无效
                                                              11：无效 */
        unsigned int  reserved            : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_TIMING_VALID_W_SEL1_UNION;
#define BBPCOMM_TIMING_VALID_W_SEL1_timing_valid_w_sel1_START  (0)
#define BBPCOMM_TIMING_VALID_W_SEL1_timing_valid_w_sel1_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_DSP_CTU_TIMING_GET_IND_UNION
 结构说明  : DSP_CTU_TIMING_GET_IND 寄存器结构定义。地址偏移量:0x0290，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dsp_ctu_timing_get_ind_reg;
    struct
    {
        unsigned int  dsp_ctu_timing_get_ind : 1;  /* bit[0]   : CTU内部19.2M钟驱动定时计数器结果读取使能 */
        unsigned int  reserved               : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_DSP_CTU_TIMING_GET_IND_UNION;
#define BBPCOMM_DSP_CTU_TIMING_GET_IND_dsp_ctu_timing_get_ind_START  (0)
#define BBPCOMM_DSP_CTU_TIMING_GET_IND_dsp_ctu_timing_get_ind_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_CTU_TIMING_VALID_DSP_UNION
 结构说明  : CTU_TIMING_VALID_DSP 寄存器结构定义。地址偏移量:0x0294，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      ctu_timing_valid_dsp_reg;
    struct
    {
        unsigned int  ctu_timing_valid_dsp : 1;  /* bit[0]   : CTU内部19.2M钟驱动定时计数器结果读取有效指示 */
        unsigned int  reserved             : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_CTU_TIMING_VALID_DSP_UNION;
#define BBPCOMM_CTU_TIMING_VALID_DSP_ctu_timing_valid_dsp_START  (0)
#define BBPCOMM_CTU_TIMING_VALID_DSP_ctu_timing_valid_dsp_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_DSP_CTU_TIMING_CLR_UNION
 结构说明  : DSP_CTU_TIMING_CLR 寄存器结构定义。地址偏移量:0x0298，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dsp_ctu_timing_clr_reg;
    struct
    {
        unsigned int  dsp_ctu_timing_clr : 1;  /* bit[0]   : CTU内部19.2M钟驱动定时计数器结果读取后清零使能 */
        unsigned int  reserved           : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_DSP_CTU_TIMING_CLR_UNION;
#define BBPCOMM_DSP_CTU_TIMING_CLR_dsp_ctu_timing_clr_START  (0)
#define BBPCOMM_DSP_CTU_TIMING_CLR_dsp_ctu_timing_clr_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_TIMING_GET_W_SEL2_UNION
 结构说明  : TIMING_GET_W_SEL2 寄存器结构定义。地址偏移量:0x02C4，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      timing_get_w_sel2_reg;
    struct
    {
        unsigned int  timing_get_w_sel2 : 2;  /* bit[0-1] : C模BBE16 DSP读取W模bbp计数器结果sys_cnt还是base_cnt。00（二进制）：sys_cnt，01：base_cnt 10：无效 11：无效
                                                            timing_get_mode无效时，不需配置，无意义 */
        unsigned int  reserved          : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_TIMING_GET_W_SEL2_UNION;
#define BBPCOMM_TIMING_GET_W_SEL2_timing_get_w_sel2_START  (0)
#define BBPCOMM_TIMING_GET_W_SEL2_timing_get_w_sel2_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_TIMING_VALID_W_SEL2_UNION
 结构说明  : TIMING_VALID_W_SEL2 寄存器结构定义。地址偏移量:0x02C8，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      timing_valid_w_sel2_reg;
    struct
    {
        unsigned int  timing_valid_w_sel2 : 2;  /* bit[0-1] : 上报的计数器给C模BBE16 DSP的是w模bbp的sys_cnt还是base_cnt
                                                              00：sys_cnt定时
                                                              01：base_cnt定时 
                                                              10：无效
                                                              11：无效 */
        unsigned int  reserved            : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_TIMING_VALID_W_SEL2_UNION;
#define BBPCOMM_TIMING_VALID_W_SEL2_timing_valid_w_sel2_START  (0)
#define BBPCOMM_TIMING_VALID_W_SEL2_timing_valid_w_sel2_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_TIMING_GET_IND2_UNION
 结构说明  : TIMING_GET_IND2 寄存器结构定义。地址偏移量:0x02CC，初值:0x00000030，宽度:32
 寄存器说明: 定时锁存使能指示寄存器
*****************************************************************************/
typedef union
{
    unsigned int      timing_get_ind2_reg;
    struct
    {
        unsigned int  timing_get_ind2   : 1;  /* bit[0]   : 逻辑自清零。
                                                            arm需要获取定时关系时配置生效，CTU逻辑根据此信号锁存LTE/W/Gm/Gs/TDS/C的系统定时，CTU的内部定时供DSP查询。 */
        unsigned int  reserved_0        : 3;  /* bit[1-3] : 保留 */
        unsigned int  timing_get_c_sel2 : 2;  /* bit[4-5] : C2模BBE16 DSP读取C模bbp计数器结果1x、evdo还是base_cnt。   00：1x定时，01：evdo定时，10： base_cnt ，11：无效。 */
        unsigned int  reserved_1        : 26; /* bit[6-31]: 保留 */
    } reg;
} BBPCOMM_TIMING_GET_IND2_UNION;
#define BBPCOMM_TIMING_GET_IND2_timing_get_ind2_START    (0)
#define BBPCOMM_TIMING_GET_IND2_timing_get_ind2_END      (0)
#define BBPCOMM_TIMING_GET_IND2_timing_get_c_sel2_START  (4)
#define BBPCOMM_TIMING_GET_IND2_timing_get_c_sel2_END    (5)


/*****************************************************************************
 结构名    : BBPCOMM_TIMING_WAIT_CNT_UNION
 结构说明  : TIMING_WAIT_CNT 寄存器结构定义。地址偏移量:0x02D0，初值:0x00000007，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      timing_wait_cnt_reg;
    struct
    {
        unsigned int  timing_wait_cnt : 8;  /* bit[0-7] : 定时锁存各类定时等待时间，19.2M时钟域 */
        unsigned int  reserved        : 24; /* bit[8-31]: 保留 */
    } reg;
} BBPCOMM_TIMING_WAIT_CNT_UNION;
#define BBPCOMM_TIMING_WAIT_CNT_timing_wait_cnt_START  (0)
#define BBPCOMM_TIMING_WAIT_CNT_timing_wait_cnt_END    (7)


/*****************************************************************************
 结构名    : BBPCOMM_TAS_IND_CTRL_UNION
 结构说明  : TAS_IND_CTRL 寄存器结构定义。地址偏移量:0x02D4，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      tas_ind_ctrl_reg;
    struct
    {
        unsigned int  tas_ind_ctrl : 1;  /* bit[0-0] : 线控tas_ind输出控制信号
                                                       0：tas_ind直接输出
                                                       1：tas_ind取反输出 */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_TAS_IND_CTRL_UNION;
#define BBPCOMM_TAS_IND_CTRL_tas_ind_ctrl_START  (0)
#define BBPCOMM_TAS_IND_CTRL_tas_ind_ctrl_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_TUNER_GPIO_LINE_MASK_UNION
 结构说明  : TUNER_GPIO_LINE_MASK 寄存器结构定义。地址偏移量:0x02D8，初值:0x0001FFFF，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      tuner_gpio_line_mask_reg;
    struct
    {
        unsigned int  tuner_gpio_line_mask : 17; /* bit[0-16] : tuner gpio输出信号屏蔽控制寄存器，bit0~bit16对应的屏蔽信号如下：
                                                                bit0: m1_active_p；
                                                                bit1: m1_active_s；
                                                                bit2: m0_active；
                                                                bit3：m0_line_p[0]；
                                                                bit4：m0_line_p[1]；
                                                                bit5：m0_line_p[2]；
                                                                bit6：m0_line_p[3]；
                                                                bit7：m0_line_s[0]；
                                                                bit8：m0_line_s[1]；
                                                                bit9：m0_line_s[2]；
                                                                bit10：m0_line_s[3]；
                                                                bit11：m1_line[0]；
                                                                bit12：m1_line[1]；
                                                                bit13：m1_line[2]；
                                                                bit14：m1_line[3]；
                                                                bit15：m1_line[4]；
                                                                bit16：m1_line[5]；
                                                                其中对应比特为1表示输出CTU的值，为0则使用tuner输出的GPIO值 */
        unsigned int  reserved             : 15; /* bit[17-31]: 保留 */
    } reg;
} BBPCOMM_TUNER_GPIO_LINE_MASK_UNION;
#define BBPCOMM_TUNER_GPIO_LINE_MASK_tuner_gpio_line_mask_START  (0)
#define BBPCOMM_TUNER_GPIO_LINE_MASK_tuner_gpio_line_mask_END    (16)


/*****************************************************************************
 结构名    : BBPCOMM_CPU_ABB_CH0_TX_SEL_UNION
 结构说明  : CPU_ABB_CH0_TX_SEL 寄存器结构定义。地址偏移量:0x02DC，初值:0x00000003，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      cpu_abb_ch0_tx_sel_reg;
    struct
    {
        unsigned int  cpu_abb_ch0_tx_en_sel   : 1;  /* bit[0]    : ABB上行通道0 tx_en线控控制寄存器
                                                                   0：由ant_sel29控制输出
                                                                   1：CTU逻辑选通输出 */
        unsigned int  cpu_abb_ch0_tx_data_sel : 1;  /* bit[1]    : ABB上行通道0 tx_en线控控制寄存器
                                                                   0：由软件控制输出，输出值由
                                                                   1：CTU逻辑选通输出 */
        unsigned int  reserved_0              : 14; /* bit[2-15] : 保留 */
        unsigned int  cpu_abb0_data_value     : 14; /* bit[16-29]: 软件配置的输出给abb0的上行数据，cpu_abb_ch0_tx_data_sel为0时选择输出 */
        unsigned int  reserved_1              : 2;  /* bit[30-31]: 保留 */
    } reg;
} BBPCOMM_CPU_ABB_CH0_TX_SEL_UNION;
#define BBPCOMM_CPU_ABB_CH0_TX_SEL_cpu_abb_ch0_tx_en_sel_START    (0)
#define BBPCOMM_CPU_ABB_CH0_TX_SEL_cpu_abb_ch0_tx_en_sel_END      (0)
#define BBPCOMM_CPU_ABB_CH0_TX_SEL_cpu_abb_ch0_tx_data_sel_START  (1)
#define BBPCOMM_CPU_ABB_CH0_TX_SEL_cpu_abb_ch0_tx_data_sel_END    (1)
#define BBPCOMM_CPU_ABB_CH0_TX_SEL_cpu_abb0_data_value_START      (16)
#define BBPCOMM_CPU_ABB_CH0_TX_SEL_cpu_abb0_data_value_END        (29)


/*****************************************************************************
 结构名    : BBPCOMM_CPU_ABB_CH1_TX_SEL_UNION
 结构说明  : CPU_ABB_CH1_TX_SEL 寄存器结构定义。地址偏移量:0x02E0，初值:0x00000003，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      cpu_abb_ch1_tx_sel_reg;
    struct
    {
        unsigned int  cpu_abb_ch1_tx_en_sel   : 1;  /* bit[0]    : ABB上行通道1 tx_en线控控制寄存器
                                                                   0：由ant_sel30控制输出
                                                                   1：CTU逻辑选通输出 */
        unsigned int  cpu_abb_ch1_tx_data_sel : 1;  /* bit[1]    : ABB上行通道1 tx_en线控控制寄存器
                                                                   0：由软件控制输出，输出值由
                                                                   1：CTU逻辑选通输出 */
        unsigned int  reserved_0              : 14; /* bit[2-15] : 保留 */
        unsigned int  cpu_abb1_data_value     : 14; /* bit[16-29]: 软件配置的输出给abb1的上行数据，cpu_abb_ch1_tx_data_sel为0时选择输出 */
        unsigned int  reserved_1              : 2;  /* bit[30-31]: 保留 */
    } reg;
} BBPCOMM_CPU_ABB_CH1_TX_SEL_UNION;
#define BBPCOMM_CPU_ABB_CH1_TX_SEL_cpu_abb_ch1_tx_en_sel_START    (0)
#define BBPCOMM_CPU_ABB_CH1_TX_SEL_cpu_abb_ch1_tx_en_sel_END      (0)
#define BBPCOMM_CPU_ABB_CH1_TX_SEL_cpu_abb_ch1_tx_data_sel_START  (1)
#define BBPCOMM_CPU_ABB_CH1_TX_SEL_cpu_abb_ch1_tx_data_sel_END    (1)
#define BBPCOMM_CPU_ABB_CH1_TX_SEL_cpu_abb1_data_value_START      (16)
#define BBPCOMM_CPU_ABB_CH1_TX_SEL_cpu_abb1_data_value_END        (29)


/*****************************************************************************
 结构名    : BBPCOMM_SOFT_PRI_IND_RX_UNION
 结构说明  : SOFT_PRI_IND_RX 寄存器结构定义。地址偏移量:0x02F0，初值:0x00000007，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      soft_pri_ind_rx_reg;
    struct
    {
        unsigned int  soft_pri_ind_rx : 3;  /* bit[0-2] : 软中断软件配置的软件主模指示：
                                                          000：LTE 主模。
                                                          001：W主模。
                                                          010：TDS主模。
                                                          011：Gm主模；
                                                          100：Gs主模；
                                                          101:C2主模；
                                                          110~111：无效。 */
        unsigned int  reserved        : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_SOFT_PRI_IND_RX_UNION;
#define BBPCOMM_SOFT_PRI_IND_RX_soft_pri_ind_rx_START  (0)
#define BBPCOMM_SOFT_PRI_IND_RX_soft_pri_ind_rx_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_SOFT_SEC_IND_UNION
 结构说明  : SOFT_SEC_IND 寄存器结构定义。地址偏移量:0x02F4，初值:0x00000007，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      soft_sec_ind_reg;
    struct
    {
        unsigned int  soft_sec_ind : 3;  /* bit[0-2] : 软中断软件配置的软件从模指示：
                                                       000：LTE 从模。
                                                       001：W从模。
                                                       010：TDS从模。
                                                       011：Gm从模；
                                                       100：Gs从模；
                                                       101:C2从模；
                                                       110~111：无效。 */
        unsigned int  reserved     : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_SOFT_SEC_IND_UNION;
#define BBPCOMM_SOFT_SEC_IND_soft_sec_ind_START  (0)
#define BBPCOMM_SOFT_SEC_IND_soft_sec_ind_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_SOFT_INT_EN_UNION
 结构说明  : SOFT_INT_EN 寄存器结构定义。地址偏移量:0x02F8，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      soft_int_en_reg;
    struct
    {
        unsigned int  soft_int_en : 1;  /* bit[0]   : 软中使能
                                                      配置时刻：在定时及软件主从模配置完毕后打开使能。 */
        unsigned int  reserved    : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_SOFT_INT_EN_UNION;
#define BBPCOMM_SOFT_INT_EN_soft_int_en_START  (0)
#define BBPCOMM_SOFT_INT_EN_soft_int_en_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_S_W_CH_NUM_IND_UNION
 结构说明  : S_W_CH_NUM_IND 寄存器结构定义。地址偏移量:0x0300，初值:0x00000000，宽度:32
 寄存器说明: W为从模时对应通道的指示寄存器
*****************************************************************************/
typedef union
{
    unsigned int      s_w_ch_num_ind_reg;
    struct
    {
        unsigned int  s_w_ch_num_ind     : 2;  /* bit[0-1] : W为从模时对应的通道选择信号。
                                                             0：选择通道0；
                                                             1：选择通道1；
                                                             2：选择通道2；
                                                             3：选择通道3。
                                                             配置时刻：各模根据通信场景配置 */
        unsigned int  reserved_0         : 2;  /* bit[2-3] : 保留 */
        unsigned int  s_w_ch_num_ind_sel : 1;  /* bit[4-4] : W为从模时对应的通道选择信号生效方式。
                                                             0：在int1生效；
                                                             1：立即生效。 */
        unsigned int  reserved_1         : 27; /* bit[5-31]: 保留 */
    } reg;
} BBPCOMM_S_W_CH_NUM_IND_UNION;
#define BBPCOMM_S_W_CH_NUM_IND_s_w_ch_num_ind_START      (0)
#define BBPCOMM_S_W_CH_NUM_IND_s_w_ch_num_ind_END        (1)
#define BBPCOMM_S_W_CH_NUM_IND_s_w_ch_num_ind_sel_START  (4)
#define BBPCOMM_S_W_CH_NUM_IND_s_w_ch_num_ind_sel_END    (4)


/*****************************************************************************
 结构名    : BBPCOMM_W_INTERSYS_MEASURE_TYPE_UNION
 结构说明  : W_INTERSYS_MEASURE_TYPE 寄存器结构定义。地址偏移量:0x0304，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      w_intersys_measure_type_reg;
    struct
    {
        unsigned int  w_intersys_measure_type : 4;  /* bit[0-3] : 异系统测量类型。
                                                                  4’b0：测量3G。
                                                                  4’b1: 3G背景搜；
                                                                  4’d2: 3G ANR。
                                                                  其它预留。
                                                                  生效时刻：立即生效 */
        unsigned int  reserved                : 28; /* bit[4-31]: 保留 */
    } reg;
} BBPCOMM_W_INTERSYS_MEASURE_TYPE_UNION;
#define BBPCOMM_W_INTERSYS_MEASURE_TYPE_w_intersys_measure_type_START  (0)
#define BBPCOMM_W_INTERSYS_MEASURE_TYPE_w_intersys_measure_type_END    (3)


/*****************************************************************************
 结构名    : BBPCOMM_W_MEASURE_REPORT_VALID_UNION
 结构说明  : W_MEASURE_REPORT_VALID 寄存器结构定义。地址偏移量:0x0308，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      w_measure_report_valid_reg;
    struct
    {
        unsigned int  w_measure_report_valid : 1;  /* bit[0-0] : 单频点测量周期到指示，L或者TDS/Gm/Gs作为主模，通知W DSP W测量的单频点周期到达。
                                                                 只在连接态下需要配置。
                                                                 电平信号，高有效。
                                                                 生效时刻：立即生效 */
        unsigned int  reserved               : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_W_MEASURE_REPORT_VALID_UNION;
#define BBPCOMM_W_MEASURE_REPORT_VALID_w_measure_report_valid_START  (0)
#define BBPCOMM_W_MEASURE_REPORT_VALID_w_measure_report_valid_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_INT_CLEAR_W_RCV_LTE_UNION
 结构说明  : INT_CLEAR_W_RCV_LTE 寄存器结构定义。地址偏移量:0x0314，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_w_rcv_lte_reg;
    struct
    {
        unsigned int  int_clear_w_rcv_lte : 16; /* bit[0-15] : 逻辑自清零。
                                                               中断标志清除指示，高有效。用于清除INT_TYPE_W_RCV_LTE[15:0]对应bit位
                                                               生效时刻：立即生效 */
        unsigned int  reserved            : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_CLEAR_W_RCV_LTE_UNION;
#define BBPCOMM_INT_CLEAR_W_RCV_LTE_int_clear_w_rcv_lte_START  (0)
#define BBPCOMM_INT_CLEAR_W_RCV_LTE_int_clear_w_rcv_lte_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_CLEAR_W_RCV_TDS_UNION
 结构说明  : INT_CLEAR_W_RCV_TDS 寄存器结构定义。地址偏移量:0x0318，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_w_rcv_tds_reg;
    struct
    {
        unsigned int  int_clear_w_rcv_tds : 16; /* bit[0-15] : 逻辑自清零。
                                                               中断标志清除指示，高有效。用于清除INT_TYPE_W_RCV_TDS[15:0]对应bit位
                                                               生效时刻：立即生效 */
        unsigned int  reserved            : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_CLEAR_W_RCV_TDS_UNION;
#define BBPCOMM_INT_CLEAR_W_RCV_TDS_int_clear_w_rcv_tds_START  (0)
#define BBPCOMM_INT_CLEAR_W_RCV_TDS_int_clear_w_rcv_tds_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_CLEAR_W_RCV_GM_UNION
 结构说明  : INT_CLEAR_W_RCV_GM 寄存器结构定义。地址偏移量:0x031C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_w_rcv_gm_reg;
    struct
    {
        unsigned int  int_clear_w_rcv_gm : 16; /* bit[0-15] : 逻辑自清零。
                                                              中断标志清除指示，高有效。用于清除INT_TYPE_W_RCV_GM[15:0]对应bit位
                                                              生效时刻：立即生效 */
        unsigned int  reserved           : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_CLEAR_W_RCV_GM_UNION;
#define BBPCOMM_INT_CLEAR_W_RCV_GM_int_clear_w_rcv_gm_START  (0)
#define BBPCOMM_INT_CLEAR_W_RCV_GM_int_clear_w_rcv_gm_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_CLEAR_W_RCV_GS_UNION
 结构说明  : INT_CLEAR_W_RCV_GS 寄存器结构定义。地址偏移量:0x0320，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_w_rcv_gs_reg;
    struct
    {
        unsigned int  int_clear_w_rcv_gs : 16; /* bit[0-15] : 逻辑自清零。
                                                              中断标志清除指示，高有效。用于清除INT_TYPE_W_RCV_GS[15:0]对应bit位
                                                              生效时刻：立即生效 */
        unsigned int  reserved           : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_CLEAR_W_RCV_GS_UNION;
#define BBPCOMM_INT_CLEAR_W_RCV_GS_int_clear_w_rcv_gs_START  (0)
#define BBPCOMM_INT_CLEAR_W_RCV_GS_int_clear_w_rcv_gs_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_CLEAR_W_RCV_W_UNION
 结构说明  : INT_CLEAR_W_RCV_W 寄存器结构定义。地址偏移量:0x0324，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_w_rcv_w_reg;
    struct
    {
        unsigned int  int_clear_w_rcv_w : 16; /* bit[0-15] : 逻辑自清零。
                                                             中断标志清除指示，高有效。用于清除INT_TYPE_W_RCV_W[15:0]对应bit位
                                                             生效时刻：立即生效 */
        unsigned int  reserved          : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_CLEAR_W_RCV_W_UNION;
#define BBPCOMM_INT_CLEAR_W_RCV_W_int_clear_w_rcv_w_START  (0)
#define BBPCOMM_INT_CLEAR_W_RCV_W_int_clear_w_rcv_w_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_CLEAR_W_INT012_UNION
 结构说明  : INT_CLEAR_W_INT012 寄存器结构定义。地址偏移量:0x0328，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_w_int012_reg;
    struct
    {
        unsigned int  int_clear_w_int012 : 3;  /* bit[0-2] : 逻辑自清零。
                                                             中断标志清除指示，高有效。用于清除INT_TYPE_W_INT012[2:0]对应bit位
                                                             生效时刻：立即生效 */
        unsigned int  reserved           : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_INT_CLEAR_W_INT012_UNION;
#define BBPCOMM_INT_CLEAR_W_INT012_int_clear_w_int012_START  (0)
#define BBPCOMM_INT_CLEAR_W_INT012_int_clear_w_int012_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_INT_MASK_W_RCV_LTE_UNION
 结构说明  : INT_MASK_W_RCV_LTE 寄存器结构定义。地址偏移量:0x032C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_w_rcv_lte_reg;
    struct
    {
        unsigned int  int_mask_w_rcv_lte : 16; /* bit[0-15] : 中断屏蔽标志。用于屏蔽INT_TYPE_W_RCV_LTE[15:0]对应bit中断。
                                                              0：屏蔽中断上报；
                                                              1：使能中断上报。
                                                              配置时刻：初始化
                                                              生效时刻：立即生效 */
        unsigned int  reserved           : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_MASK_W_RCV_LTE_UNION;
#define BBPCOMM_INT_MASK_W_RCV_LTE_int_mask_w_rcv_lte_START  (0)
#define BBPCOMM_INT_MASK_W_RCV_LTE_int_mask_w_rcv_lte_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_MASK_W_RCV_TDS_UNION
 结构说明  : INT_MASK_W_RCV_TDS 寄存器结构定义。地址偏移量:0x0330，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_w_rcv_tds_reg;
    struct
    {
        unsigned int  int_mask_w_rcv_tds : 16; /* bit[0-15] : 中断屏蔽标志。用于屏蔽INT_TYPE_W_RCV_TDS[15:0]对应bit中断。
                                                              0：屏蔽中断上报；
                                                              1：使能中断上报。
                                                              配置时刻：初始化
                                                              生效时刻：立即生效 */
        unsigned int  reserved           : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_MASK_W_RCV_TDS_UNION;
#define BBPCOMM_INT_MASK_W_RCV_TDS_int_mask_w_rcv_tds_START  (0)
#define BBPCOMM_INT_MASK_W_RCV_TDS_int_mask_w_rcv_tds_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_MASK_W_RCV_GM_UNION
 结构说明  : INT_MASK_W_RCV_GM 寄存器结构定义。地址偏移量:0x0334，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_w_rcv_gm_reg;
    struct
    {
        unsigned int  int_mask_w_rcv_gm : 16; /* bit[0-15] : 中断屏蔽标志。用于屏蔽INT_TYPE_W_RCV_GM[15:0]对应bit中断。
                                                             0：屏蔽中断上报；
                                                             1：使能中断上报。
                                                             配置时刻：初始化
                                                             生效时刻：立即生效 */
        unsigned int  reserved          : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_MASK_W_RCV_GM_UNION;
#define BBPCOMM_INT_MASK_W_RCV_GM_int_mask_w_rcv_gm_START  (0)
#define BBPCOMM_INT_MASK_W_RCV_GM_int_mask_w_rcv_gm_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_MASK_W_RCV_GS_UNION
 结构说明  : INT_MASK_W_RCV_GS 寄存器结构定义。地址偏移量:0x0338，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_w_rcv_gs_reg;
    struct
    {
        unsigned int  int_mask_w_rcv_gs : 16; /* bit[0-15] : 中断屏蔽标志。用于屏蔽INT_TYPE_W_RCV_GS[15:0]对应bit中断。
                                                             0：屏蔽中断上报；
                                                             1：使能中断上报。
                                                             配置时刻：初始化
                                                             生效时刻：立即生效 */
        unsigned int  reserved          : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_MASK_W_RCV_GS_UNION;
#define BBPCOMM_INT_MASK_W_RCV_GS_int_mask_w_rcv_gs_START  (0)
#define BBPCOMM_INT_MASK_W_RCV_GS_int_mask_w_rcv_gs_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_MASK_W_RCV_W_UNION
 结构说明  : INT_MASK_W_RCV_W 寄存器结构定义。地址偏移量:0x033C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_w_rcv_w_reg;
    struct
    {
        unsigned int  int_mask_w_rcv_w : 16; /* bit[0-15] : 中断屏蔽标志。用于屏蔽INT_TYPE_W_RCV_W[15:0]对应bit中断。
                                                            0：屏蔽中断上报；
                                                            1：使能中断上报。
                                                            配置时刻：初始化
                                                            生效时刻：立即生效 */
        unsigned int  reserved         : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_MASK_W_RCV_W_UNION;
#define BBPCOMM_INT_MASK_W_RCV_W_int_mask_w_rcv_w_START  (0)
#define BBPCOMM_INT_MASK_W_RCV_W_int_mask_w_rcv_w_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_MASK_W_INT012_UNION
 结构说明  : INT_MASK_W_INT012 寄存器结构定义。地址偏移量:0x0340，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_w_int012_reg;
    struct
    {
        unsigned int  int_mask_w_int012 : 3;  /* bit[0-2] : 中断屏蔽标志。用于屏蔽INT_TYPE_W_INT012[2:0]对应bit中断。
                                                            0：屏蔽中断上报；
                                                            1：使能中断上报。
                                                            配置时刻：初始化
                                                            生效时刻：立即生效 */
        unsigned int  reserved          : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_INT_MASK_W_INT012_UNION;
#define BBPCOMM_INT_MASK_W_INT012_int_mask_w_int012_START  (0)
#define BBPCOMM_INT_MASK_W_INT012_int_mask_w_int012_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_INT_TYPE_W_RCV_LTE_UNION
 结构说明  : INT_TYPE_W_RCV_LTE 寄存器结构定义。地址偏移量:0x0344，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_type_w_rcv_lte_reg;
    struct
    {
        unsigned int  o_int_type_w_rcv_lte : 16; /* bit[0-15] : 中断状态标志。各bit单独对应一种中断类型，高有效。
                                                                [0]: 中断类型0。 LTE（主模）提前通知W异系统测量启动中断。
                                                                [1]: 中断类型1。 LTE（主模）进GAP中断，通知W进行异系统测量射频通道配置，天线切换等操作。
                                                                [2]: 中断类型2。 LTE（主模）出GAP中断。
                                                                [3]: 中断类型3。LTE（从模）测量结束中断。
                                                                [4]: 中断类型4。LTE（主模）强制W退出异系统测量中断。
                                                                [5]: 中断类型5。LTE（主模）通知W上报本次测量结果。
                                                                [6]: 保留。
                                                                [15:7]: 对应中断类型[15:7]，预留。
                                                                软件读取该中断状态上报寄存器后，需要和0x06F0的int_mask_w_rcv_lte相与，再判断是否需要处理。 */
        unsigned int  reserved             : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_TYPE_W_RCV_LTE_UNION;
#define BBPCOMM_INT_TYPE_W_RCV_LTE_o_int_type_w_rcv_lte_START  (0)
#define BBPCOMM_INT_TYPE_W_RCV_LTE_o_int_type_w_rcv_lte_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_TYPE_W_RCV_TDS_UNION
 结构说明  : INT_TYPE_W_RCV_TDS 寄存器结构定义。地址偏移量:0x0348，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_type_w_rcv_tds_reg;
    struct
    {
        unsigned int  o_int_type_w_rcv_tds : 16; /* bit[0-15] : 中断状态标志0，1，2只有当TDS处于主模时才能产生。
                                                                
                                                                [0]: 中断类型0。 TDS（主模）提前通知W异系统测量启动中断。
                                                                [1]: 中断类型1。 TDS（主模）进GAP中断，通知W进行异系统测量射频通道配置，天线切换等操作。
                                                                [2]: 中断类型2。 TDS（主模）出GAP中断。
                                                                [3]: 中断类型3。TDS（从模）测量结束中断。
                                                                [4]: 中断类型4。TDS（主模）强制W退出异系统测量中断。
                                                                [5]: 中断类型5。TDS（主模）通知W上报本次测量结果。
                                                                [6]: 中断类型6。保留。
                                                                [15:7]: 对应中断类型[15:7]，预留。
                                                                软件读取该中断状态上报寄存器后，需要和0x06F4的int_mask_w_rcv_tds相与，再判断是否需要处理。 */
        unsigned int  reserved             : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_TYPE_W_RCV_TDS_UNION;
#define BBPCOMM_INT_TYPE_W_RCV_TDS_o_int_type_w_rcv_tds_START  (0)
#define BBPCOMM_INT_TYPE_W_RCV_TDS_o_int_type_w_rcv_tds_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_TYPE_W_RCV_GM_UNION
 结构说明  : INT_TYPE_W_RCV_GM 寄存器结构定义。地址偏移量:0x034C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_type_w_rcv_gm_reg;
    struct
    {
        unsigned int  o_int_type_w_rcv_gm : 16; /* bit[0-15] : 中断状态标志。各bit单独对应一种中断类型，高有效。
                                                               [0]: 中断类型0。GM（主模）提前通知W异系统测量启动中断。
                                                               [1]: 中断类型1。GM（主模）进GAP中断，通知W进行异系统测量射频通道配置，天线切换等操作。
                                                               [2]: 中断类型2。GM（主模）出GAP中断。
                                                               [3]: 中断类型3。GM（从模）测量结束中断。
                                                               [4]: 中断类型4。GM（主模）强制W退出异系统测量中断。
                                                               [5]: 中断类型5。GM（主模）通知W上报本次测量结果。
                                                               [6]: 中断类型6。保留。
                                                               [15:7]: 对应中断类型[15:7]，预留。
                                                               中断状态标志0，1，2只有当GM处于主模时才能产生。
                                                               软件读取该中断状态上报寄存器后，需要和0x06F8的int_mask_w_rcv_gm相与，再判断是否需要处理。 */
        unsigned int  reserved            : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_TYPE_W_RCV_GM_UNION;
#define BBPCOMM_INT_TYPE_W_RCV_GM_o_int_type_w_rcv_gm_START  (0)
#define BBPCOMM_INT_TYPE_W_RCV_GM_o_int_type_w_rcv_gm_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_TYPE_W_RCV_GS_UNION
 结构说明  : INT_TYPE_W_RCV_GS 寄存器结构定义。地址偏移量:0x0350，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_type_w_rcv_gs_reg;
    struct
    {
        unsigned int  o_int_type_w_rcv_gs : 16; /* bit[0-15] : [0]: 中断类型0。GS（主模）提前通知W异系统测量启动中断。
                                                               [1]: 中断类型1。GS（主模）进GAP中断，通知W进行异系统测量射频通道配置，天线切换等操作。
                                                               [2]: 中断类型2。GS（主模）出GAP中断。
                                                               [3]: 中断类型3。GS（从模）测量结束中断。
                                                               [4]: 中断类型4。GS（主模）强制W退出异系统测量中断。
                                                               [5]: 中断类型5。GS（主模）通知W上报本次测量结果。
                                                               [6]: 中断类型6。保留。
                                                               [15:7]: 对应中断类型[15:7]，预留。
                                                               中断状态标志0，1，2只有当TDS处于主模时才能产生。
                                                               软件读取该中断状态上报寄存器后，需要和0x06FC的int_mask_w_rcv_gs相与，再判断是否需要处理。 */
        unsigned int  reserved            : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_TYPE_W_RCV_GS_UNION;
#define BBPCOMM_INT_TYPE_W_RCV_GS_o_int_type_w_rcv_gs_START  (0)
#define BBPCOMM_INT_TYPE_W_RCV_GS_o_int_type_w_rcv_gs_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_TYPE_W_RCV_W_UNION
 结构说明  : INT_TYPE_W_RCV_W 寄存器结构定义。地址偏移量:0x0354，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_type_w_rcv_w_reg;
    struct
    {
        unsigned int  o_int_type_w_rcv_w : 16; /* bit[0-15] : 中断状态标志。各bit单独对应一种中断类型，高有效。
                                                              [0]: 中断类型0。W（主模）提前通知W异频测量启动中断。
                                                              [1]: 中断类型1。W（主模）进GAP中断，通知W进行异频测量射频通道配置，天线切换等操作。
                                                              [2]: 中断类型2。W（主模）出GAP中断。
                                                              [3]: 中断类型3。W（从模，即异频）测量结束中断。
                                                              [4]: 中断类型4。W（主模）强制W退出异频测量中断。
                                                              [5]: 中断类型5。W（主模）通知W上报本次测量结果。
                                                              [6]: 中断类型6。保留。
                                                              [15:7]: 对应中断类型[15:7]，预留。
                                                              中断状态标志0，1，2只有当W处于主模时才能产生。
                                                              软件读取该中断状态上报寄存器后，需要和0x0700的int_mask_w_rcv_w相与，再判断是否需要处理。 */
        unsigned int  reserved           : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_TYPE_W_RCV_W_UNION;
#define BBPCOMM_INT_TYPE_W_RCV_W_o_int_type_w_rcv_w_START  (0)
#define BBPCOMM_INT_TYPE_W_RCV_W_o_int_type_w_rcv_w_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_TYPE_W_INT012_UNION
 结构说明  : INT_TYPE_W_INT012 寄存器结构定义。地址偏移量:0x0358，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_type_w_int012_reg;
    struct
    {
        unsigned int  o_int_type_w_int012 : 3;  /* bit[0-2] : 增加主模产生int0、1、2的上报（(包括异频、异系统场景)），高有效。
                                                              [0]: W主模时，CTU告诉通知WDSP产生int0中断。
                                                              [1]: W主模时，CTU告诉通知WDSP产生int1中断。
                                                              [2]: W主模时，CTU告诉通知WDSP产生int2中断。
                                                              软件读取该中断状态上报寄存器后，需要和0x0704的int_mask_w_int012相与，再判断是否需要处理。 */
        unsigned int  reserved            : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_INT_TYPE_W_INT012_UNION;
#define BBPCOMM_INT_TYPE_W_INT012_o_int_type_w_int012_START  (0)
#define BBPCOMM_INT_TYPE_W_INT012_o_int_type_w_int012_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_W_SND_LTE_INT_13_UNION
 结构说明  : W_SND_LTE_INT_13 寄存器结构定义。地址偏移量:0x035C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      w_snd_lte_int_13_reg;
    struct
    {
        unsigned int  reserved_0       : 3;  /* bit[0-2]  : 保留 */
        unsigned int  w_snd_lte_int_13 : 13; /* bit[3-15] : 逻辑自清零。高有效。
                                                            
                                                            bit15~7：对应w_snd_lte_int_15 ~ 7。
                                                            W DSP通过此寄存器触发类型15~7中断（int_type_lte_rcv_w[15:7]）给LDSP。
                                                            生效时刻：立即生效
                                                            
                                                            bit6：对应w_snd_lte_int_6。
                                                            WDSP通过此寄存器触发类型6中断（int_type_lte_rcv_w[6]）给LDSP。
                                                            生效时刻：立即生效
                                                            
                                                            bit5：对应w_snd_lte_int_5。
                                                            W主模时通知LDSP L测量周期到达，高有效。
                                                            W DSP通过此寄存器触发类型5中断（int_type_lte_rcv_w[5]）给LDSP。
                                                            生效时刻：立即生效
                                                            
                                                            bit4：对应w_snd_lte_int_4。
                                                            W主模时强制退出异系统测量指示。高有效。
                                                            W DSP通过此寄存器触发类型4中断（int_type_lte_rcv_w[4]）给LDSP。
                                                            生效时刻：立即生效
                                                            
                                                            bit3：对应w_snd_lte_int_3。W测量结束指示，高有效。
                                                            用于触发中断类型3 （int_type_lte_rcv_w[3]）给LDSP。L主模下对W进行异系统测量时，如果W测量结束，W DSP配置此标志为1。 
                                                            生效时刻：立即生效 */
        unsigned int  reserved_1       : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_W_SND_LTE_INT_13_UNION;
#define BBPCOMM_W_SND_LTE_INT_13_w_snd_lte_int_13_START  (3)
#define BBPCOMM_W_SND_LTE_INT_13_w_snd_lte_int_13_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_W_SND_TDS_INT_13_UNION
 结构说明  : W_SND_TDS_INT_13 寄存器结构定义。地址偏移量:0x0360，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      w_snd_tds_int_13_reg;
    struct
    {
        unsigned int  reserved_0       : 3;  /* bit[0-2]  : 保留 */
        unsigned int  w_snd_tds_int_13 : 13; /* bit[3-15] : 逻辑自清零。高有效。
                                                            
                                                            bit15~7：对应w_snd_tds_int_15 ~ 7。
                                                            W DSP通过此寄存器触发类型15~7中断（int_type_tds_rcv_w[15:7]）给TDSP。
                                                            生效时刻：立即生效
                                                            
                                                            bit6：对应w_snd_tds_int_6。
                                                            WDSP通过此寄存器触发类型6中断（int_type_tds_rcv_w[6]）给TDSP。
                                                            生效时刻：立即生效
                                                            
                                                            bit5：对应w_snd_tds_int_5。
                                                            W主模时通知TDSP T测量周期到达，高有效。
                                                            W DSP通过此寄存器触发类型5中断（int_type_tds_rcv_w[5]）给TDSP。
                                                            生效时刻：立即生效
                                                            
                                                            bit4：对应w_snd_tds_int_4。
                                                            W主模时强制退出异系统测量指示。高有效。
                                                            W DSP通过此寄存器触发类型4中断（int_type_tds_rcv_w[4]）给TDSP。
                                                            生效时刻：立即生效
                                                            
                                                            bit3：对应w_snd_tds_int_3。W测量结束指示，高有效。
                                                            用于触发中断类型3 （int_type_tds_rcv_w[3]）给TDSP。T主模下对W进行异系统测量时，如果W测量结束，W DSP配置此标志为1。 
                                                            生效时刻：立即生效 */
        unsigned int  reserved_1       : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_W_SND_TDS_INT_13_UNION;
#define BBPCOMM_W_SND_TDS_INT_13_w_snd_tds_int_13_START  (3)
#define BBPCOMM_W_SND_TDS_INT_13_w_snd_tds_int_13_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_W_SND_GM_INT_13_UNION
 结构说明  : W_SND_GM_INT_13 寄存器结构定义。地址偏移量:0x0364，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      w_snd_gm_int_13_reg;
    struct
    {
        unsigned int  reserved_0      : 3;  /* bit[0-2]  : 保留 */
        unsigned int  w_snd_gm_int_13 : 13; /* bit[3-15] : 逻辑自清零。高有效。
                                                           
                                                           bit15~7：对应w_snd_gm_int_15 ~ 7。
                                                           W DSP通过此寄存器触发类型15~7中断（int_type_gm_rcv_w[15:7]）给GMDSP。
                                                           生效时刻：立即生效
                                                           
                                                           bit6：对应w_snd_gm_int_6。
                                                           WDSP通过此寄存器触发类型6中断（int_type_gm_rcv_w[6]）给GMDSP。
                                                           生效时刻：立即生效
                                                           
                                                           bit5：对应w_snd_gm_int_5。
                                                           W主模时通知GMDSP GM测量周期到达，高有效。
                                                           W DSP通过此寄存器触发类型5中断（int_type_gm_rcv_w[5]）给GMDSP。
                                                           生效时刻：立即生效
                                                           
                                                           bit4：对应w_snd_gm_int_4。
                                                           W主模时强制退出异系统测量指示。高有效。
                                                           W DSP通过此寄存器触发类型4中断（int_type_gm_rcv_w[4]）给GMDSP。
                                                           生效时刻：立即生效
                                                           
                                                           bit3：对应w_snd_gm_int_3。W测量结束指示，高有效。
                                                           用于触发中断类型3 （int_type_gm_rcv_w[3]）给GMDSP。GM主模下对W进行异系统测量时，如果W测量结束，W DSP配置此标志为1。 
                                                           生效时刻：立即生效 */
        unsigned int  reserved_1      : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_W_SND_GM_INT_13_UNION;
#define BBPCOMM_W_SND_GM_INT_13_w_snd_gm_int_13_START  (3)
#define BBPCOMM_W_SND_GM_INT_13_w_snd_gm_int_13_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_W_SND_GS_INT_13_UNION
 结构说明  : W_SND_GS_INT_13 寄存器结构定义。地址偏移量:0x0368，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      w_snd_gs_int_13_reg;
    struct
    {
        unsigned int  reserved_0      : 3;  /* bit[0-2]  : 保留 */
        unsigned int  w_snd_gs_int_13 : 13; /* bit[3-15] : 逻辑自清零。高有效。
                                                           
                                                           bit15~7：对应w_snd_gs_int_15 ~ 7。
                                                           W DSP通过此寄存器触发类型15~7中断（int_type_gs_rcv_w[15:7]）给GSDSP。
                                                           生效时刻：立即生效
                                                           
                                                           bit6：对应w_snd_gs_int_6。
                                                           WDSP通过此寄存器触发类型6中断（int_type_gs_rcv_w[6]）给GSDSP。
                                                           生效时刻：立即生效
                                                           
                                                           bit5：对应w_snd_gs_int_5。
                                                           W主模时通知GSDSP GS测量周期到达，高有效。
                                                           W DSP通过此寄存器触发类型5中断（int_type_gs_rcv_w[5]）给GSDSP。
                                                           生效时刻：立即生效
                                                           
                                                           bit4：对应w_snd_gs_int_4。
                                                           W主模时强制退出异系统测量指示。高有效。
                                                           W DSP通过此寄存器触发类型4中断（int_type_gs_rcv_w[4]）给GSDSP。
                                                           生效时刻：立即生效
                                                           
                                                           bit3：对应w_snd_gs_int_3。W测量结束指示，高有效。
                                                           用于触发中断类型3 （int_type_gs_rcv_w[3]）给GSDSP。GS主模下对W进行异系统测量时，如果W测量结束，W DSP配置此标志为1。 
                                                           生效时刻：立即生效 */
        unsigned int  reserved_1      : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_W_SND_GS_INT_13_UNION;
#define BBPCOMM_W_SND_GS_INT_13_w_snd_gs_int_13_START  (3)
#define BBPCOMM_W_SND_GS_INT_13_w_snd_gs_int_13_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_W_SND_W_INT_13_UNION
 结构说明  : W_SND_W_INT_13 寄存器结构定义。地址偏移量:0x036C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      w_snd_w_int_13_reg;
    struct
    {
        unsigned int  reserved_0     : 3;  /* bit[0-2]  : 保留 */
        unsigned int  w_snd_w_int_13 : 13; /* bit[3-15] : 逻辑自清零。高有效。
                                                          
                                                          bit15~7：对应w_snd_w_int_15 ~ 7。
                                                          W DSP通过此寄存器触发类型15~7中断（int_type_w_rcv_w[15:7]）给WDSP。
                                                          生效时刻：立即生效
                                                          
                                                          bit6：对应w_snd_w_int_6。
                                                          WDSP通过此寄存器触发类型6中断（int_type_w_rcv_w[6]）给WDSP。
                                                          生效时刻：立即生效
                                                          
                                                          bit5：对应w_snd_w_int_5。
                                                          W主模时通知WDSP W测量周期到达，高有效。
                                                          W DSP通过此寄存器触发类型5中断（int_type_w_rcv_w[5]）给WDSP。
                                                          生效时刻：立即生效
                                                          
                                                          bit4：对应w_snd_w_int_4。
                                                          W主模时强制退出异系统测量指示。高有效。
                                                          W DSP通过此寄存器触发类型4中断（int_type_w_rcv_w[4]）给WDSP。
                                                          生效时刻：立即生效
                                                          
                                                          bit3：对应w_snd_w_int_3。W测量结束指示，高有效。
                                                          用于触发中断类型3 （int_type_w_rcv_w[3]）给WDSP。W主模下对W进行异系统测量时，如果W测量结束，W DSP配置此标志为1。 
                                                          生效时刻：立即生效 */
        unsigned int  reserved_1     : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_W_SND_W_INT_13_UNION;
#define BBPCOMM_W_SND_W_INT_13_w_snd_w_int_13_START  (3)
#define BBPCOMM_W_SND_W_INT_13_w_snd_w_int_13_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_S_LTE_CH_NUM_IND_UNION
 结构说明  : S_LTE_CH_NUM_IND 寄存器结构定义。地址偏移量:0x0380，初值:0x00000000，宽度:32
 寄存器说明: LTE为从模时对应通道的指示寄存器
*****************************************************************************/
typedef union
{
    unsigned int      s_lte_ch_num_ind_reg;
    struct
    {
        unsigned int  lte_ch0_slave_active_en : 1;  /* bit[0]   : LTE在从模时配置
                                                                  1'b1：LTE的CH0通路在occasion中有效
                                                                  1'b0：LTE的CH0通路在occasion中无效 */
        unsigned int  lte_ch1_slave_active_en : 1;  /* bit[1]   : LTE在从模时配置
                                                                  1'b1：LTE的CH1通路在occasion中有效
                                                                  1'b0：LTE的CH1通路在occasion中无效 */
        unsigned int  lte_ch2_slave_active_en : 1;  /* bit[2]   : LTE在从模时配置
                                                                  1'b1：LTE的CH2通路在occasion中有效
                                                                  1'b0：LTE的CH2通路在occasion中无效 */
        unsigned int  lte_ch3_slave_active_en : 1;  /* bit[3]   : LTE在从模时配置
                                                                  1'b1：LTE的CH3通路在occasion中有效
                                                                  1'b0：LTE的CH3通路在occasion中无效 */
        unsigned int  s_lte_ch_num_ind_sel    : 1;  /* bit[4]   : LTE为从模时对应的通道选择信号生效方式。
                                                                  0：在int1生效；
                                                                  1：立即生效。 */
        unsigned int  reserved                : 27; /* bit[5-31]: 保留 */
    } reg;
} BBPCOMM_S_LTE_CH_NUM_IND_UNION;
#define BBPCOMM_S_LTE_CH_NUM_IND_lte_ch0_slave_active_en_START  (0)
#define BBPCOMM_S_LTE_CH_NUM_IND_lte_ch0_slave_active_en_END    (0)
#define BBPCOMM_S_LTE_CH_NUM_IND_lte_ch1_slave_active_en_START  (1)
#define BBPCOMM_S_LTE_CH_NUM_IND_lte_ch1_slave_active_en_END    (1)
#define BBPCOMM_S_LTE_CH_NUM_IND_lte_ch2_slave_active_en_START  (2)
#define BBPCOMM_S_LTE_CH_NUM_IND_lte_ch2_slave_active_en_END    (2)
#define BBPCOMM_S_LTE_CH_NUM_IND_lte_ch3_slave_active_en_START  (3)
#define BBPCOMM_S_LTE_CH_NUM_IND_lte_ch3_slave_active_en_END    (3)
#define BBPCOMM_S_LTE_CH_NUM_IND_s_lte_ch_num_ind_sel_START     (4)
#define BBPCOMM_S_LTE_CH_NUM_IND_s_lte_ch_num_ind_sel_END       (4)


/*****************************************************************************
 结构名    : BBPCOMM_LTE_INTERSYS_MEASURE_TYPE_UNION
 结构说明  : LTE_INTERSYS_MEASURE_TYPE 寄存器结构定义。地址偏移量:0x0384，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      lte_intersys_measure_type_reg;
    struct
    {
        unsigned int  lte_intersys_measure_type : 4;  /* bit[0-3] : 异系统测量类型。
                                                                    4’b0：测量LTE。
                                                                    4’b1：背景搜LTE。
                                                                    其它预留
                                                                    生效时刻：立即生效 */
        unsigned int  reserved                  : 28; /* bit[4-31]: 保留 */
    } reg;
} BBPCOMM_LTE_INTERSYS_MEASURE_TYPE_UNION;
#define BBPCOMM_LTE_INTERSYS_MEASURE_TYPE_lte_intersys_measure_type_START  (0)
#define BBPCOMM_LTE_INTERSYS_MEASURE_TYPE_lte_intersys_measure_type_END    (3)


/*****************************************************************************
 结构名    : BBPCOMM_LTE_MEASURE_REPORT_VALID_UNION
 结构说明  : LTE_MEASURE_REPORT_VALID 寄存器结构定义。地址偏移量:0x0388，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      lte_measure_report_valid_reg;
    struct
    {
        unsigned int  lte_measure_report_valid : 1;  /* bit[0]   : 单频点测量周期到指示，W/Gm/Gs或者TDS作为主模，通知L DSP 测量的单频点周期到达。
                                                                   只在连接态下需要配置，且Gm测L时不需要配置；
                                                                   电平信号，高有效。
                                                                   
                                                                   生效时刻：立即生效 */
        unsigned int  reserved                 : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_LTE_MEASURE_REPORT_VALID_UNION;
#define BBPCOMM_LTE_MEASURE_REPORT_VALID_lte_measure_report_valid_START  (0)
#define BBPCOMM_LTE_MEASURE_REPORT_VALID_lte_measure_report_valid_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_INT_CLEAR_LTE_RCV_LTE_UNION
 结构说明  : INT_CLEAR_LTE_RCV_LTE 寄存器结构定义。地址偏移量:0x0394，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_lte_rcv_lte_reg;
    struct
    {
        unsigned int  int_clear_lte_rcv_lte : 16; /* bit[0-15] : 逻辑自清零。
                                                                 中断标志清除指示，高有效。用于清除INT_TYPE_LTE_RCV_LTE[15:0]对应bit位
                                                                 生效时刻：立即生效 */
        unsigned int  reserved              : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_CLEAR_LTE_RCV_LTE_UNION;
#define BBPCOMM_INT_CLEAR_LTE_RCV_LTE_int_clear_lte_rcv_lte_START  (0)
#define BBPCOMM_INT_CLEAR_LTE_RCV_LTE_int_clear_lte_rcv_lte_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_CLEAR_LTE_RCV_TDS_UNION
 结构说明  : INT_CLEAR_LTE_RCV_TDS 寄存器结构定义。地址偏移量:0x0398，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_lte_rcv_tds_reg;
    struct
    {
        unsigned int  int_clear_lte_rcv_tds : 16; /* bit[0-15] : 逻辑自清零。
                                                                 中断标志清除指示，高有效。用于清除INT_TYPE_LTE_RCV_TDS[15:0]对应bit位
                                                                 生效时刻：立即生效 */
        unsigned int  reserved              : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_CLEAR_LTE_RCV_TDS_UNION;
#define BBPCOMM_INT_CLEAR_LTE_RCV_TDS_int_clear_lte_rcv_tds_START  (0)
#define BBPCOMM_INT_CLEAR_LTE_RCV_TDS_int_clear_lte_rcv_tds_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_CLEAR_LTE_RCV_GM_UNION
 结构说明  : INT_CLEAR_LTE_RCV_GM 寄存器结构定义。地址偏移量:0x039C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_lte_rcv_gm_reg;
    struct
    {
        unsigned int  int_clear_lte_rcv_gm : 16; /* bit[0-15] : 逻辑自清零。
                                                                中断标志清除指示，高有效。用于清除INT_TYPE_LTE_RCV_GM[15:0]对应bit位
                                                                生效时刻：立即生效 */
        unsigned int  reserved             : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_CLEAR_LTE_RCV_GM_UNION;
#define BBPCOMM_INT_CLEAR_LTE_RCV_GM_int_clear_lte_rcv_gm_START  (0)
#define BBPCOMM_INT_CLEAR_LTE_RCV_GM_int_clear_lte_rcv_gm_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_CLEAR_LTE_RCV_GS_UNION
 结构说明  : INT_CLEAR_LTE_RCV_GS 寄存器结构定义。地址偏移量:0x03A0，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_lte_rcv_gs_reg;
    struct
    {
        unsigned int  int_clear_lte_rcv_gs : 16; /* bit[0-15] : 逻辑自清零。
                                                                中断标志清除指示，高有效。用于清除INT_TYPE_LTE_RCV_GS[15:0]对应bit位
                                                                生效时刻：立即生效 */
        unsigned int  reserved             : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_CLEAR_LTE_RCV_GS_UNION;
#define BBPCOMM_INT_CLEAR_LTE_RCV_GS_int_clear_lte_rcv_gs_START  (0)
#define BBPCOMM_INT_CLEAR_LTE_RCV_GS_int_clear_lte_rcv_gs_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_CLEAR_LTE_RCV_W_UNION
 结构说明  : INT_CLEAR_LTE_RCV_W 寄存器结构定义。地址偏移量:0x03A4，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_lte_rcv_w_reg;
    struct
    {
        unsigned int  int_clear_lte_rcv_w : 16; /* bit[0-15] : 逻辑自清零。
                                                               中断标志清除指示，高有效。用于清除INT_TYPE_LTE_RCV_W[15:0]对应bit位
                                                               生效时刻：立即生效 */
        unsigned int  reserved            : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_CLEAR_LTE_RCV_W_UNION;
#define BBPCOMM_INT_CLEAR_LTE_RCV_W_int_clear_lte_rcv_w_START  (0)
#define BBPCOMM_INT_CLEAR_LTE_RCV_W_int_clear_lte_rcv_w_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_CLEAR_LTE_INT012_UNION
 结构说明  : INT_CLEAR_LTE_INT012 寄存器结构定义。地址偏移量:0x03A8，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_lte_int012_reg;
    struct
    {
        unsigned int  int_clear_lte_int012 : 3;  /* bit[0-2] : 逻辑自清零。
                                                               中断标志清除指示，高有效。用于清除INT_TYPE_LTE_INT012[2:0]对应bit位
                                                               生效时刻：立即生效 */
        unsigned int  reserved             : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_INT_CLEAR_LTE_INT012_UNION;
#define BBPCOMM_INT_CLEAR_LTE_INT012_int_clear_lte_int012_START  (0)
#define BBPCOMM_INT_CLEAR_LTE_INT012_int_clear_lte_int012_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_INT_MASK_LTE_RCV_LTE_UNION
 结构说明  : INT_MASK_LTE_RCV_LTE 寄存器结构定义。地址偏移量:0x03AC，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_lte_rcv_lte_reg;
    struct
    {
        unsigned int  int_mask_lte_rcv_lte : 16; /* bit[0-15] : 中断屏蔽标志。用于屏蔽INT_TYPE_LTE_RCV_LTE[15:0]对应bit中断。
                                                                0：屏蔽中断上报；
                                                                1：使能中断上报。
                                                                配置时刻：初始化
                                                                生效时刻：立即生效 */
        unsigned int  reserved             : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_MASK_LTE_RCV_LTE_UNION;
#define BBPCOMM_INT_MASK_LTE_RCV_LTE_int_mask_lte_rcv_lte_START  (0)
#define BBPCOMM_INT_MASK_LTE_RCV_LTE_int_mask_lte_rcv_lte_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_MASK_LTE_RCV_TDS_UNION
 结构说明  : INT_MASK_LTE_RCV_TDS 寄存器结构定义。地址偏移量:0x03B0，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_lte_rcv_tds_reg;
    struct
    {
        unsigned int  int_mask_lte_rcv_tds : 16; /* bit[0-15] : 中断屏蔽标志。用于屏蔽INT_TYPE_LTE_RCV_TDS[15:0]对应bit中断。
                                                                0：屏蔽中断上报；
                                                                1：使能中断上报。
                                                                配置时刻：初始化
                                                                生效时刻：立即生效 */
        unsigned int  reserved             : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_MASK_LTE_RCV_TDS_UNION;
#define BBPCOMM_INT_MASK_LTE_RCV_TDS_int_mask_lte_rcv_tds_START  (0)
#define BBPCOMM_INT_MASK_LTE_RCV_TDS_int_mask_lte_rcv_tds_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_MASK_LTE_RCV_GM_UNION
 结构说明  : INT_MASK_LTE_RCV_GM 寄存器结构定义。地址偏移量:0x03B4，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_lte_rcv_gm_reg;
    struct
    {
        unsigned int  int_mask_lte_rcv_gm : 16; /* bit[0-15] : 中断屏蔽标志。用于屏蔽INT_TYPE_LTE_RCV_GM[15:0]对应bit中断。
                                                               0：屏蔽中断上报；
                                                               1：使能中断上报。
                                                               配置时刻：初始化
                                                               生效时刻：立即生效 */
        unsigned int  reserved            : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_MASK_LTE_RCV_GM_UNION;
#define BBPCOMM_INT_MASK_LTE_RCV_GM_int_mask_lte_rcv_gm_START  (0)
#define BBPCOMM_INT_MASK_LTE_RCV_GM_int_mask_lte_rcv_gm_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_MASK_LTE_RCV_GS_UNION
 结构说明  : INT_MASK_LTE_RCV_GS 寄存器结构定义。地址偏移量:0x03B8，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_lte_rcv_gs_reg;
    struct
    {
        unsigned int  int_mask_lte_rcv_gs : 16; /* bit[0-15] : 中断屏蔽标志。用于屏蔽INT_TYPE_LTE_RCV_GS[15:0]对应bit中断。
                                                               0：屏蔽中断上报；
                                                               1：使能中断上报。
                                                               配置时刻：初始化
                                                               生效时刻：立即生效 */
        unsigned int  reserved            : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_MASK_LTE_RCV_GS_UNION;
#define BBPCOMM_INT_MASK_LTE_RCV_GS_int_mask_lte_rcv_gs_START  (0)
#define BBPCOMM_INT_MASK_LTE_RCV_GS_int_mask_lte_rcv_gs_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_MASK_LTE_RCV_W_UNION
 结构说明  : INT_MASK_LTE_RCV_W 寄存器结构定义。地址偏移量:0x03BC，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_lte_rcv_w_reg;
    struct
    {
        unsigned int  int_mask_lte_rcv_w : 16; /* bit[0-15] : 中断屏蔽标志。用于屏蔽INT_TYPE_LTE_RCV_W[15:0]对应bit中断。
                                                              0：屏蔽中断上报；
                                                              1：使能中断上报。
                                                              配置时刻：初始化
                                                              生效时刻：立即生效 */
        unsigned int  reserved           : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_MASK_LTE_RCV_W_UNION;
#define BBPCOMM_INT_MASK_LTE_RCV_W_int_mask_lte_rcv_w_START  (0)
#define BBPCOMM_INT_MASK_LTE_RCV_W_int_mask_lte_rcv_w_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_MASK_LTE_INT012_UNION
 结构说明  : INT_MASK_LTE_INT012 寄存器结构定义。地址偏移量:0x03C0，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_lte_int012_reg;
    struct
    {
        unsigned int  int_mask_lte_int012 : 3;  /* bit[0-2] : 中断屏蔽标志。用于屏蔽INT_TYPE_LTE_INT012[2:0]对应bit中断。
                                                              0：屏蔽中断上报；
                                                              1：使能中断上报。
                                                              配置时刻：初始化
                                                              生效时刻：立即生效 */
        unsigned int  reserved            : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_INT_MASK_LTE_INT012_UNION;
#define BBPCOMM_INT_MASK_LTE_INT012_int_mask_lte_int012_START  (0)
#define BBPCOMM_INT_MASK_LTE_INT012_int_mask_lte_int012_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_INT_TYPE_LTE_RCV_W_UNION
 结构说明  : INT_TYPE_LTE_RCV_W 寄存器结构定义。地址偏移量:0x03C4，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_type_lte_rcv_w_reg;
    struct
    {
        unsigned int  o_int_type_lte_rcv_w : 16; /* bit[0-15] : 中断状态标志。各bit单独对应一种中断类型，高有效。
                                                                [0]: 中断类型0。 W（主模）提前通知LTE异系统测量启动中断。
                                                                [1]: 中断类型1。 W（主模）进GAP中断，通知LTE进行异系统测量射频通道配置，天线切换等操作。
                                                                [2]: 中断类型2。 W（主模）出GAP中断。
                                                                [3]: 中断类型3。W（从模）测量结束中断。
                                                                [4]: 中断类型4。W（主模）强制LTE退出异系统测量中断。
                                                                [5]: 中断类型5。W（主模）通知LTE上报本次测量结果。
                                                                [6]: 保留。
                                                                [15:7]: 对应中断类型[15:7]，预留。
                                                                软件读取该中断状态上报寄存器后，需要和0x076C的int_mask_lte_rcv_w相与，再判断是否需要处理。 */
        unsigned int  reserved             : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_TYPE_LTE_RCV_W_UNION;
#define BBPCOMM_INT_TYPE_LTE_RCV_W_o_int_type_lte_rcv_w_START  (0)
#define BBPCOMM_INT_TYPE_LTE_RCV_W_o_int_type_lte_rcv_w_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_TYPE_LTE_RCV_TDS_UNION
 结构说明  : INT_TYPE_LTE_RCV_TDS 寄存器结构定义。地址偏移量:0x03C8，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_type_lte_rcv_tds_reg;
    struct
    {
        unsigned int  o_int_type_lte_rcv_tds : 16; /* bit[0-15] : 中断状态标志0，1，2只有当TDS处于主模时才能产生。
                                                                  [0]: 中断类型0。 TDS（主模）提前通知LTE异系统测量启动中断。
                                                                  [1]: 中断类型1。 TDS（主模）进GAP中断，通知LTE进行异系统测量射频通道配置，天线切换等操作。
                                                                  [2]: 中断类型2。 TDS（主模）出GAP中断。
                                                                  [3]: 中断类型3。TDS（从模）测量结束中断。
                                                                  [4]: 中断类型4。TDS（主模）强制LTE退出异系统测量中断。
                                                                  [5]: 中断类型5。TDS（主模）通知LTE上报本次测量结果。
                                                                  [6]: 中断类型6。保留。
                                                                  [15:7]: 对应中断类型[15:7]，预留。
                                                                  软件读取该中断状态上报寄存器后，需要和0x0760的int_mask_lte_rcv_tds相与，再判断是否需要处理。 */
        unsigned int  reserved               : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_TYPE_LTE_RCV_TDS_UNION;
#define BBPCOMM_INT_TYPE_LTE_RCV_TDS_o_int_type_lte_rcv_tds_START  (0)
#define BBPCOMM_INT_TYPE_LTE_RCV_TDS_o_int_type_lte_rcv_tds_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_TYPE_LTE_RCV_GM_UNION
 结构说明  : INT_TYPE_LTE_RCV_GM 寄存器结构定义。地址偏移量:0x03CC，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_type_lte_rcv_gm_reg;
    struct
    {
        unsigned int  o_int_type_lte_rcv_gm : 16; /* bit[0-15] : 中断状态标志。各bit单独对应一种中断类型，高有效。
                                                                 [0]: 中断类型0。GM（主模）提前通知LTE异系统测量启动中断。
                                                                 [1]: 中断类型1。GM（主模）进GAP中断，通知LTE进行异系统测量射频通道配置，天线切换等操作。
                                                                 [2]: 中断类型2。GM（主模）出GAP中断。
                                                                 [3]: 中断类型3。GM（从模）测量结束中断。
                                                                 [4]: 中断类型4。GM（主模）强制LTE退出异系统测量中断。
                                                                 [5]: 中断类型5。GM（主模）通知LTE上报本次测量结果。
                                                                 [6]: 中断类型6。保留。
                                                                 [15:7]: 对应中断类型[15:7]，预留。
                                                                 中断状态标志0，1，2只有当GM处于主模时才能产生。
                                                                 软件读取该中断状态上报寄存器后，需要和0x0764的int_mask_lte_rcv_gm相与，再判断是否需要处理。 */
        unsigned int  reserved              : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_TYPE_LTE_RCV_GM_UNION;
#define BBPCOMM_INT_TYPE_LTE_RCV_GM_o_int_type_lte_rcv_gm_START  (0)
#define BBPCOMM_INT_TYPE_LTE_RCV_GM_o_int_type_lte_rcv_gm_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_TYPE_LTE_RCV_GS_UNION
 结构说明  : INT_TYPE_LTE_RCV_GS 寄存器结构定义。地址偏移量:0x03D0，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_type_lte_rcv_gs_reg;
    struct
    {
        unsigned int  o_int_type_lte_rcv_gs : 16; /* bit[0-15] : [0]: 中断类型0。GS（主模）提前通知LTE异系统测量启动中断。
                                                                 [1]: 中断类型1。GS（主模）进GAP中断，通知LTE进行异系统测量射频通道配置，天线切换等操作。
                                                                 [2]: 中断类型2。GS（主模）出GAP中断。
                                                                 [3]: 中断类型3。GS（从模）测量结束中断。
                                                                 [4]: 中断类型4。GS（主模）强制LTE退出异系统测量中断。
                                                                 [5]: 中断类型5。GS（主模）通知LTE上报本次测量结果。
                                                                 [6]: 中断类型6。保留。
                                                                 [15:7]: 对应中断类型[15:7]，预留。
                                                                 中断状态标志0，1，2只有当TDS处于主模时才能产生。
                                                                 软件读取该中断状态上报寄存器后，需要和0x0768的int_mask_lte_rcv_gs相与，再判断是否需要处理。 */
        unsigned int  reserved              : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_TYPE_LTE_RCV_GS_UNION;
#define BBPCOMM_INT_TYPE_LTE_RCV_GS_o_int_type_lte_rcv_gs_START  (0)
#define BBPCOMM_INT_TYPE_LTE_RCV_GS_o_int_type_lte_rcv_gs_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_TYPE_LTE_RCV_LTE_UNION
 结构说明  : INT_TYPE_LTE_RCV_LTE 寄存器结构定义。地址偏移量:0x03D4，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_type_lte_rcv_lte_reg;
    struct
    {
        unsigned int  o_int_type_lte_rcv_lte : 16; /* bit[0-15] : 中断状态标志。各bit单独对应一种中断类型，高有效。
                                                                  [0]: 中断类型0。LTE（主模）提前通知LTE异频测量启动中断。
                                                                  [1]: 中断类型1。LTE（主模）进GAP中断，通知LTE进行异频测量射频通道配置，天线切换等操作。
                                                                  [2]: 中断类型2。LTE（主模）出GAP中断。
                                                                  [3]: 中断类型3。LTE（从模，即异频）测量结束中断。
                                                                  [4]: 中断类型4。LTE（主模）强制LTE退出异频测量中断。
                                                                  [5]: 中断类型5。LTE（主模）通知LTE上报本次测量结果。
                                                                  [6]: 中断类型6。保留。
                                                                  [15:7]: 对应中断类型[15:7]，预留。
                                                                  中断状态标志0，1，2只有当LTE处于主模时才能产生。
                                                                  软件读取该中断状态上报寄存器后，需要和0x075C的int_mask_lte_rcv_lte相与，再判断是否需要处理。 */
        unsigned int  reserved               : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_TYPE_LTE_RCV_LTE_UNION;
#define BBPCOMM_INT_TYPE_LTE_RCV_LTE_o_int_type_lte_rcv_lte_START  (0)
#define BBPCOMM_INT_TYPE_LTE_RCV_LTE_o_int_type_lte_rcv_lte_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_TYPE_LTE_INT012_UNION
 结构说明  : INT_TYPE_LTE_INT012 寄存器结构定义。地址偏移量:0x03D8，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_type_lte_int012_reg;
    struct
    {
        unsigned int  o_int_type_lte_int012 : 3;  /* bit[0-2] : 增加主模产生int0、1、2的上报（(包括异频、异系统场景)），高有效。
                                                                [0]: L主模时，CTU告诉通知LDSP产生int0中断。
                                                                [1]: L主模时，CTU告诉通知LDSP产生int1中断。
                                                                [2]: L主模时，CTU告诉通知LDSP产生int2中断。
                                                                软件读取该中断状态上报寄存器后，需要和0x0770的int_mask_lte_int012相与，再判断是否需要处理。 */
        unsigned int  reserved              : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_INT_TYPE_LTE_INT012_UNION;
#define BBPCOMM_INT_TYPE_LTE_INT012_o_int_type_lte_int012_START  (0)
#define BBPCOMM_INT_TYPE_LTE_INT012_o_int_type_lte_int012_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_LTE_SND_LTE_INT_13_UNION
 结构说明  : LTE_SND_LTE_INT_13 寄存器结构定义。地址偏移量:0x03DC，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      lte_snd_lte_int_13_reg;
    struct
    {
        unsigned int  reserved_0         : 3;  /* bit[0-2]  : 保留 */
        unsigned int  lte_snd_lte_int_13 : 13; /* bit[3-15] : 逻辑自清零。高有效。
                                                              
                                                              bit15~7：对应lte_snd_lte_int_15 ~ 7。
                                                              L DSP通过此寄存器触发类型15~7中断（int_type_lte_rcv_lte[15:7]）给LDSP。
                                                              生效时刻：立即生效
                                                              
                                                              bit6：对应lte_snd_lte_int_6。
                                                              LDSP通过此寄存器触发类型6中断（int_type_lte_rcv_lte[6]）给LDSP。
                                                              生效时刻：立即生效
                                                              
                                                              bit5：对应lte_snd_lte_int_5。
                                                              L主模时通知LDSP L测量周期到达，高有效。
                                                              L DSP通过此寄存器触发类型5中断（int_type_lte_rcv_lte[5]）给LDSP。
                                                              生效时刻：立即生效
                                                              
                                                              bit4：对应lte_snd_lte_int_4。
                                                              L主模时强制退出异系统测量指示。高有效。
                                                              L DSP通过此寄存器触发类型4中断（int_type_lte_rcv_lte[4]）给LDSP。
                                                              生效时刻：立即生效
                                                              
                                                              bit3：对应lte_snd_lte_int_3。L测量结束指示，高有效。
                                                              用于触发中断类型3 （int_type_lte_rcv_lte[3]）给LDSP。L主模下对L进行异系统测量时，如果L测量结束，L DSP配置此标志为1。 
                                                              生效时刻：立即生效 */
        unsigned int  reserved_1         : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_LTE_SND_LTE_INT_13_UNION;
#define BBPCOMM_LTE_SND_LTE_INT_13_lte_snd_lte_int_13_START  (3)
#define BBPCOMM_LTE_SND_LTE_INT_13_lte_snd_lte_int_13_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_LTE_SND_TDS_INT_13_UNION
 结构说明  : LTE_SND_TDS_INT_13 寄存器结构定义。地址偏移量:0x03E0，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      lte_snd_tds_int_13_reg;
    struct
    {
        unsigned int  reserved_0         : 3;  /* bit[0-2]  : 保留 */
        unsigned int  lte_snd_tds_int_13 : 13; /* bit[3-15] : 逻辑自清零。高有效。
                                                              
                                                              bit15~7：对应lte_snd_tds_int_15 ~ 7。
                                                              L DSP通过此寄存器触发类型15~7中断（int_type_tds_rcv_lte[15:7]）给TDSDSP。
                                                              生效时刻：立即生效
                                                              
                                                              bit6：对应lte_snd_tds_int_6。
                                                              LDSP通过此寄存器触发类型6中断（int_type_tds_rcv_lte[6]）给TDSDSP。
                                                              生效时刻：立即生效
                                                              
                                                              bit5：对应lte_snd_tds_int_5。
                                                              L主模时通知TDSDSP TDS测量周期到达，高有效。
                                                              L DSP通过此寄存器触发类型5中断（int_type_tds_rcv_lte[5]）给TDSDSP。
                                                              生效时刻：立即生效
                                                              
                                                              bit4：对应lte_snd_tds_int_4。
                                                              L主模时强制退出异系统测量指示。高有效。
                                                              L DSP通过此寄存器触发类型4中断（int_type_tds_rcv_lte[4]）给TDSDSP。
                                                              生效时刻：立即生效
                                                              
                                                              bit3：对应lte_snd_tds_int_3。L测量结束指示，高有效。
                                                              用于触发中断类型3 （int_type_tds_rcv_lte[3]）给TDSDSP。TDS主模下对L进行异系统测量时，如果L测量结束，L DSP配置此标志为1。 
                                                              生效时刻：立即生效 */
        unsigned int  reserved_1         : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_LTE_SND_TDS_INT_13_UNION;
#define BBPCOMM_LTE_SND_TDS_INT_13_lte_snd_tds_int_13_START  (3)
#define BBPCOMM_LTE_SND_TDS_INT_13_lte_snd_tds_int_13_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_LTE_SND_GM_INT_13_UNION
 结构说明  : LTE_SND_GM_INT_13 寄存器结构定义。地址偏移量:0x03E4，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      lte_snd_gm_int_13_reg;
    struct
    {
        unsigned int  reserved_0        : 3;  /* bit[0-2]  : 保留 */
        unsigned int  lte_snd_gm_int_13 : 13; /* bit[3-15] : 逻辑自清零。高有效。
                                                             
                                                             bit15~7：对应lte_snd_gm_int_15 ~ 7。
                                                             L DSP通过此寄存器触发类型15~7中断（int_type_gm_rcv_lte[15:7]）给GMDSP。
                                                             生效时刻：立即生效
                                                             
                                                             bit6：对应lte_snd_gm_int_6。
                                                             LDSP通过此寄存器触发类型6中断（iint_type_gm_rcv_lte[6]）给GMDSP。
                                                             生效时刻：立即生效
                                                             
                                                             bit5：对应lte_snd_gm_int_5。
                                                             L主模时通知GMDSP GM测量周期到达，高有效。
                                                             L DSP通过此寄存器触发类型5中断（int_type_gm_rcv_lte[5]）给GMDSP。
                                                             生效时刻：立即生效
                                                             
                                                             bit4：对应lte_snd_gm_int_4。
                                                             L主模时强制退出异系统测量指示。高有效。
                                                             L DSP通过此寄存器触发类型4中断（int_type_gm_rcv_lte[4]）给GMDSP。
                                                             生效时刻：立即生效
                                                             
                                                             bit3：对应lte_snd_gm_int_3。L测量结束指示，高有效。
                                                             用于触发中断类型3 （int_type_gm_rcv_lte[3]）给GMDSP。GM主模下对L进行异系统测量时，如果L测量结束，L DSP配置此标志为1。 
                                                             生效时刻：立即生效 */
        unsigned int  reserved_1        : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_LTE_SND_GM_INT_13_UNION;
#define BBPCOMM_LTE_SND_GM_INT_13_lte_snd_gm_int_13_START  (3)
#define BBPCOMM_LTE_SND_GM_INT_13_lte_snd_gm_int_13_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_LTE_SND_GS_INT_13_UNION
 结构说明  : LTE_SND_GS_INT_13 寄存器结构定义。地址偏移量:0x03E8，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      lte_snd_gs_int_13_reg;
    struct
    {
        unsigned int  reserved_0        : 3;  /* bit[0-2]  : 保留 */
        unsigned int  lte_snd_gs_int_13 : 13; /* bit[3-15] : 逻辑自清零。高有效。
                                                             
                                                             bit15~7：对应lte_snd_gs_int_15 ~ 7。
                                                             L DSP通过此寄存器触发类型15~7中断（int_type_gs_rcv_lte[15:7]）给GSDSP。
                                                             生效时刻：立即生效
                                                             
                                                             bit6：对应lte_snd_gs_int_6。
                                                             LDSP通过此寄存器触发类型6中断（int_type_gs_rcv_lte[6]）给GSDSP。
                                                             生效时刻：立即生效
                                                             
                                                             bit5：对应lte_snd_gs_int_5。
                                                             L主模时通知GSDSP GS测量周期到达，高有效。
                                                             L DSP通过此寄存器触发类型5中断（int_type_gs_rcv_lte[5]）给GSDSP。
                                                             生效时刻：立即生效
                                                             
                                                             bit4：对应lte_snd_gs_int_4。
                                                             L主模时强制退出异系统测量指示。高有效。
                                                             L DSP通过此寄存器触发类型4中断（int_type_gs_rcv_lte[4]）给GSDSP。
                                                             生效时刻：立即生效
                                                             
                                                             bit3：对应lte_snd_gs_int_3。L测量结束指示，高有效。
                                                             用于触发中断类型3 （int_type_gs_rcv_lte[3]）给GSDSP。GS主模下对L进行异系统测量时，如果L测量结束，L DSP配置此标志为1。 
                                                             生效时刻：立即生效 */
        unsigned int  reserved_1        : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_LTE_SND_GS_INT_13_UNION;
#define BBPCOMM_LTE_SND_GS_INT_13_lte_snd_gs_int_13_START  (3)
#define BBPCOMM_LTE_SND_GS_INT_13_lte_snd_gs_int_13_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_LTE_SND_W_INT_13_UNION
 结构说明  : LTE_SND_W_INT_13 寄存器结构定义。地址偏移量:0x03EC，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      lte_snd_w_int_13_reg;
    struct
    {
        unsigned int  reserved_0       : 3;  /* bit[0-2]  : 保留 */
        unsigned int  lte_snd_w_int_13 : 13; /* bit[3-15] : 逻辑自清零。高有效。
                                                            
                                                            bit15~7：对应lte_snd_w_int_15 ~ 7。
                                                            L DSP通过此寄存器触发类型15~7中断（int_type_w_rcv_lte[15:7]）给WDSP。
                                                            生效时刻：立即生效
                                                            
                                                            bit6：对应lte_snd_w_int_6。
                                                            LDSP通过此寄存器触发类型6中断（int_type_w_rcv_lte[6]）给WDSP。
                                                            生效时刻：立即生效
                                                            
                                                            bit5：对应lte_snd_w_int_5。
                                                            L主模时通知WDSP W测量周期到达，高有效。
                                                            L DSP通过此寄存器触发类型5中断（int_type_w_rcv_lte[5]）给WDSP。
                                                            生效时刻：立即生效
                                                            
                                                            bit4：对应lte_snd_w_int_4。
                                                            L主模时强制退出异系统测量指示。高有效。
                                                            L DSP通过此寄存器触发类型4中断（int_type_w_rcv_lte[4]）给WDSP。
                                                            生效时刻：立即生效
                                                            
                                                            bit3：对应lte_snd_w_int_3。L测量结束指示，高有效。
                                                            用于触发中断类型3 （int_type_w_rcv_lte[3]）给WDSP。W主模下对L进行异系统测量时，如果L测量结束，L DSP配置此标志为1。 
                                                            生效时刻：立即生效 */
        unsigned int  reserved_1       : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_LTE_SND_W_INT_13_UNION;
#define BBPCOMM_LTE_SND_W_INT_13_lte_snd_w_int_13_START  (3)
#define BBPCOMM_LTE_SND_W_INT_13_lte_snd_w_int_13_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_S_TDS_CH_NUM_IND_UNION
 结构说明  : S_TDS_CH_NUM_IND 寄存器结构定义。地址偏移量:0x0400，初值:0x00000000，宽度:32
 寄存器说明: TDS为从模时对应通道的指示寄存器
*****************************************************************************/
typedef union
{
    unsigned int      s_tds_ch_num_ind_reg;
    struct
    {
        unsigned int  s_tds_ch_num_ind     : 2;  /* bit[0-1] : TDS为从模时对应的通道选择信号。
                                                               0：选择通道0；
                                                               1：选择通道1；
                                                               2：选择通道2；
                                                               3：选择通道3。
                                                               配置时刻：各模根据通信场景配置 */
        unsigned int  reserved_0           : 2;  /* bit[2-3] : 保留 */
        unsigned int  s_tds_ch_num_ind_sel : 1;  /* bit[4-4] : TDS为从模时对应的通道选择信号生效方式。
                                                               0：在int1生效；
                                                               1：立即生效。 */
        unsigned int  reserved_1           : 27; /* bit[5-31]: 保留 */
    } reg;
} BBPCOMM_S_TDS_CH_NUM_IND_UNION;
#define BBPCOMM_S_TDS_CH_NUM_IND_s_tds_ch_num_ind_START      (0)
#define BBPCOMM_S_TDS_CH_NUM_IND_s_tds_ch_num_ind_END        (1)
#define BBPCOMM_S_TDS_CH_NUM_IND_s_tds_ch_num_ind_sel_START  (4)
#define BBPCOMM_S_TDS_CH_NUM_IND_s_tds_ch_num_ind_sel_END    (4)


/*****************************************************************************
 结构名    : BBPCOMM_TDS_INTERSYS_MEASURE_TYPE_UNION
 结构说明  : TDS_INTERSYS_MEASURE_TYPE 寄存器结构定义。地址偏移量:0x0404，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      tds_intersys_measure_type_reg;
    struct
    {
        unsigned int  tds_intersys_measure_type : 4;  /* bit[0-3] : 异系统测量类型 。
                                                                    4’b0： 测量TDS
                                                                    4’b1： 背景搜TDS
                                                                    其它预留
                                                                    
                                                                    生效时刻：立即生效 */
        unsigned int  reserved                  : 28; /* bit[4-31]: 保留 */
    } reg;
} BBPCOMM_TDS_INTERSYS_MEASURE_TYPE_UNION;
#define BBPCOMM_TDS_INTERSYS_MEASURE_TYPE_tds_intersys_measure_type_START  (0)
#define BBPCOMM_TDS_INTERSYS_MEASURE_TYPE_tds_intersys_measure_type_END    (3)


/*****************************************************************************
 结构名    : BBPCOMM_TDS_MEASURE_REPORT_VALID_UNION
 结构说明  : TDS_MEASURE_REPORT_VALID 寄存器结构定义。地址偏移量:0x0408，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      tds_measure_report_valid_reg;
    struct
    {
        unsigned int  tds_measure_report_valid : 1;  /* bit[0]   : 单频点测量周期到指示，U/Gm/Gs或者L作为主模，通知T DSP W测量的单频点周期到达。
                                                                   只在连接态下需要配置，且G测TDS时不需要配置；
                                                                   电平信号，高有效。
                                                                   
                                                                   生效时刻：立即生效 */
        unsigned int  reserved                 : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_TDS_MEASURE_REPORT_VALID_UNION;
#define BBPCOMM_TDS_MEASURE_REPORT_VALID_tds_measure_report_valid_START  (0)
#define BBPCOMM_TDS_MEASURE_REPORT_VALID_tds_measure_report_valid_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_INT_CLEAR_TDS_RCV_LTE_UNION
 结构说明  : INT_CLEAR_TDS_RCV_LTE 寄存器结构定义。地址偏移量:0x0414，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_tds_rcv_lte_reg;
    struct
    {
        unsigned int  int_clear_tds_rcv_lte : 16; /* bit[0-15] : 逻辑自清零。
                                                                 中断标志清除指示，高有效。用于清除INT_TYPE_TDS_RCV_LTE[15:0]对应bit位
                                                                 生效时刻：立即生效 */
        unsigned int  reserved              : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_CLEAR_TDS_RCV_LTE_UNION;
#define BBPCOMM_INT_CLEAR_TDS_RCV_LTE_int_clear_tds_rcv_lte_START  (0)
#define BBPCOMM_INT_CLEAR_TDS_RCV_LTE_int_clear_tds_rcv_lte_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_CLEAR_TDS_RCV_TDS_UNION
 结构说明  : INT_CLEAR_TDS_RCV_TDS 寄存器结构定义。地址偏移量:0x0418，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_tds_rcv_tds_reg;
    struct
    {
        unsigned int  int_clear_tds_rcv_tds : 16; /* bit[0-15] : 逻辑自清零。
                                                                 中断标志清除指示，高有效。用于清除INT_TYPE_TDS_RCV_TDS[15:0]对应bit位
                                                                 生效时刻：立即生效 */
        unsigned int  reserved              : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_CLEAR_TDS_RCV_TDS_UNION;
#define BBPCOMM_INT_CLEAR_TDS_RCV_TDS_int_clear_tds_rcv_tds_START  (0)
#define BBPCOMM_INT_CLEAR_TDS_RCV_TDS_int_clear_tds_rcv_tds_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_CLEAR_TDS_RCV_GM_UNION
 结构说明  : INT_CLEAR_TDS_RCV_GM 寄存器结构定义。地址偏移量:0x041C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_tds_rcv_gm_reg;
    struct
    {
        unsigned int  int_clear_tds_rcv_gm : 16; /* bit[0-15] : 逻辑自清零。
                                                                中断标志清除指示，高有效。用于清除INT_TYPE_TDS_RCV_GM[15:0]对应bit位
                                                                生效时刻：立即生效 */
        unsigned int  reserved             : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_CLEAR_TDS_RCV_GM_UNION;
#define BBPCOMM_INT_CLEAR_TDS_RCV_GM_int_clear_tds_rcv_gm_START  (0)
#define BBPCOMM_INT_CLEAR_TDS_RCV_GM_int_clear_tds_rcv_gm_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_CLEAR_TDS_RCV_GS_UNION
 结构说明  : INT_CLEAR_TDS_RCV_GS 寄存器结构定义。地址偏移量:0x0420，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_tds_rcv_gs_reg;
    struct
    {
        unsigned int  int_clear_tds_rcv_gs : 16; /* bit[0-15] : 逻辑自清零。
                                                                中断标志清除指示，高有效。用于清除INT_TYPE_TDS_RCV_GS[15:0]对应bit位
                                                                生效时刻：立即生效 */
        unsigned int  reserved             : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_CLEAR_TDS_RCV_GS_UNION;
#define BBPCOMM_INT_CLEAR_TDS_RCV_GS_int_clear_tds_rcv_gs_START  (0)
#define BBPCOMM_INT_CLEAR_TDS_RCV_GS_int_clear_tds_rcv_gs_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_CLEAR_TDS_RCV_W_UNION
 结构说明  : INT_CLEAR_TDS_RCV_W 寄存器结构定义。地址偏移量:0x0424，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_tds_rcv_w_reg;
    struct
    {
        unsigned int  int_clear_tds_rcv_w : 16; /* bit[0-15] : 逻辑自清零。
                                                               中断标志清除指示，高有效。用于清除INT_TYPE_TDS_RCV_W[15:0]对应bit位
                                                               生效时刻：立即生效 */
        unsigned int  reserved            : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_CLEAR_TDS_RCV_W_UNION;
#define BBPCOMM_INT_CLEAR_TDS_RCV_W_int_clear_tds_rcv_w_START  (0)
#define BBPCOMM_INT_CLEAR_TDS_RCV_W_int_clear_tds_rcv_w_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_CLEAR_TDS_INT012_UNION
 结构说明  : INT_CLEAR_TDS_INT012 寄存器结构定义。地址偏移量:0x0428，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_tds_int012_reg;
    struct
    {
        unsigned int  int_clear_tds_int012 : 3;  /* bit[0-2] : 逻辑自清零。
                                                               中断标志清除指示，高有效。用于清除INT_TYPE_TDS_INT012[2:0]对应bit位
                                                               生效时刻：立即生效 */
        unsigned int  reserved             : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_INT_CLEAR_TDS_INT012_UNION;
#define BBPCOMM_INT_CLEAR_TDS_INT012_int_clear_tds_int012_START  (0)
#define BBPCOMM_INT_CLEAR_TDS_INT012_int_clear_tds_int012_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_INT_MASK_TDS_RCV_LTE_UNION
 结构说明  : INT_MASK_TDS_RCV_LTE 寄存器结构定义。地址偏移量:0x042C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_tds_rcv_lte_reg;
    struct
    {
        unsigned int  int_mask_tds_rcv_lte : 16; /* bit[0-15] : 中断屏蔽标志。用于屏蔽INT_TYPE_TDS_RCV_LTE[15:0]对应bit中断。
                                                                0：屏蔽中断上报；
                                                                1：使能中断上报。
                                                                配置时刻：初始化
                                                                生效时刻：立即生效 */
        unsigned int  reserved             : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_MASK_TDS_RCV_LTE_UNION;
#define BBPCOMM_INT_MASK_TDS_RCV_LTE_int_mask_tds_rcv_lte_START  (0)
#define BBPCOMM_INT_MASK_TDS_RCV_LTE_int_mask_tds_rcv_lte_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_MASK_TDS_RCV_TDS_UNION
 结构说明  : INT_MASK_TDS_RCV_TDS 寄存器结构定义。地址偏移量:0x0430，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_tds_rcv_tds_reg;
    struct
    {
        unsigned int  int_mask_tds_rcv_tds : 16; /* bit[0-15] : 中断屏蔽标志。用于屏蔽INT_TYPE_TDS_RCV_TDS[15:0]对应bit中断。
                                                                0：屏蔽中断上报；
                                                                1：使能中断上报。
                                                                配置时刻：初始化
                                                                生效时刻：立即生效 */
        unsigned int  reserved             : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_MASK_TDS_RCV_TDS_UNION;
#define BBPCOMM_INT_MASK_TDS_RCV_TDS_int_mask_tds_rcv_tds_START  (0)
#define BBPCOMM_INT_MASK_TDS_RCV_TDS_int_mask_tds_rcv_tds_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_MASK_TDS_RCV_GM_UNION
 结构说明  : INT_MASK_TDS_RCV_GM 寄存器结构定义。地址偏移量:0x0434，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_tds_rcv_gm_reg;
    struct
    {
        unsigned int  int_mask_tds_rcv_gm : 16; /* bit[0-15] : 中断屏蔽标志。用于屏蔽INT_TYPE_TDS_RCV_GM[15:0]对应bit中断。
                                                               0：屏蔽中断上报；
                                                               1：使能中断上报。
                                                               配置时刻：初始化
                                                               生效时刻：立即生效 */
        unsigned int  reserved            : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_MASK_TDS_RCV_GM_UNION;
#define BBPCOMM_INT_MASK_TDS_RCV_GM_int_mask_tds_rcv_gm_START  (0)
#define BBPCOMM_INT_MASK_TDS_RCV_GM_int_mask_tds_rcv_gm_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_MASK_TDS_RCV_GS_UNION
 结构说明  : INT_MASK_TDS_RCV_GS 寄存器结构定义。地址偏移量:0x0438，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_tds_rcv_gs_reg;
    struct
    {
        unsigned int  int_mask_tds_rcv_gs : 16; /* bit[0-15] : 中断屏蔽标志。用于屏蔽INT_TYPE_TDS_RCV_GS[15:0]对应bit中断。
                                                               0：屏蔽中断上报；
                                                               1：使能中断上报。
                                                               配置时刻：初始化
                                                               生效时刻：立即生效 */
        unsigned int  reserved            : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_MASK_TDS_RCV_GS_UNION;
#define BBPCOMM_INT_MASK_TDS_RCV_GS_int_mask_tds_rcv_gs_START  (0)
#define BBPCOMM_INT_MASK_TDS_RCV_GS_int_mask_tds_rcv_gs_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_MASK_TDS_RCV_W_UNION
 结构说明  : INT_MASK_TDS_RCV_W 寄存器结构定义。地址偏移量:0x043C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_tds_rcv_w_reg;
    struct
    {
        unsigned int  int_mask_tds_rcv_w : 16; /* bit[0-15] : 中断屏蔽标志。用于屏蔽INT_TYPE_TDS_RCV_W[15:0]对应bit中断。
                                                              0：屏蔽中断上报；
                                                              1：使能中断上报。
                                                              配置时刻：初始化
                                                              生效时刻：立即生效 */
        unsigned int  reserved           : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_MASK_TDS_RCV_W_UNION;
#define BBPCOMM_INT_MASK_TDS_RCV_W_int_mask_tds_rcv_w_START  (0)
#define BBPCOMM_INT_MASK_TDS_RCV_W_int_mask_tds_rcv_w_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_MASK_TDS_INT012_UNION
 结构说明  : INT_MASK_TDS_INT012 寄存器结构定义。地址偏移量:0x0440，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_tds_int012_reg;
    struct
    {
        unsigned int  int_mask_tds_int012 : 3;  /* bit[0-2] : 中断屏蔽标志。用于屏蔽INT_TYPE_TDS_INT012[2:0]对应bit中断。
                                                              0：屏蔽中断上报；
                                                              1：使能中断上报。
                                                              配置时刻：初始化
                                                              生效时刻：立即生效 */
        unsigned int  reserved            : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_INT_MASK_TDS_INT012_UNION;
#define BBPCOMM_INT_MASK_TDS_INT012_int_mask_tds_int012_START  (0)
#define BBPCOMM_INT_MASK_TDS_INT012_int_mask_tds_int012_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_INT_TYPE_TDS_RCV_LTE_UNION
 结构说明  : INT_TYPE_TDS_RCV_LTE 寄存器结构定义。地址偏移量:0x0444，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_type_tds_rcv_lte_reg;
    struct
    {
        unsigned int  o_int_type_tds_rcv_lte : 16; /* bit[0-15] : 中断状态标志。各bit单独对应一种中断类型，高有效。
                                                                  [0]: 中断类型0。 LTE（主模）提前通知TDS异系统测量启动中断。
                                                                  [1]: 中断类型1。 LTE（主模）进GAP中断，通知TDS进行异系统测量射频通道配置，天线切换等操作。
                                                                  [2]: 中断类型2。 LTE（主模）出GAP中断。
                                                                  [3]: 中断类型3。LTE（从模）测量结束中断。
                                                                  [4]: 中断类型4。LTE（主模）强制TDS退出异系统测量中断。
                                                                  [5]: 中断类型5。LTE（主模）通知TDS上报本次测量结果。
                                                                  [6]: 保留。
                                                                  [15:7]: 对应中断类型[15:7]，预留。
                                                                  软件读取该中断状态上报寄存器后，需要和0x07C8的int_mask_tds_rcv_lte相与，再判断是否需要处理。 */
        unsigned int  reserved               : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_TYPE_TDS_RCV_LTE_UNION;
#define BBPCOMM_INT_TYPE_TDS_RCV_LTE_o_int_type_tds_rcv_lte_START  (0)
#define BBPCOMM_INT_TYPE_TDS_RCV_LTE_o_int_type_tds_rcv_lte_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_TYPE_TDS_RCV_W_UNION
 结构说明  : INT_TYPE_TDS_RCV_W 寄存器结构定义。地址偏移量:0x0448，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_type_tds_rcv_w_reg;
    struct
    {
        unsigned int  o_int_type_tds_rcv_w : 16; /* bit[0-15] : 中断状态标志0，1，2只有当TDS处于主模时才能产生。
                                                                
                                                                [0]: 中断类型0。 TDS（主模）提前通知TDS异系统测量启动中断。
                                                                [1]: 中断类型1。 TDS（主模）进GAP中断，通知TDS进行异系统测量射频通道配置，天线切换等操作。
                                                                [2]: 中断类型2。 TDS（主模）出GAP中断。
                                                                [3]: 中断类型3。TDS（从模）测量结束中断。
                                                                [4]: 中断类型4。TDS（主模）强制TDS退出异系统测量中断。
                                                                [5]: 中断类型5。TDS（主模）通知TDS上报本次测量结果。
                                                                [6]: 中断类型6。保留。
                                                                [15:7]: 对应中断类型[15:7]，预留。
                                                                软件读取该中断状态上报寄存器后，需要和0x07D8的int_mask_tds_rcv_w相与，再判断是否需要处理。 */
        unsigned int  reserved             : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_TYPE_TDS_RCV_W_UNION;
#define BBPCOMM_INT_TYPE_TDS_RCV_W_o_int_type_tds_rcv_w_START  (0)
#define BBPCOMM_INT_TYPE_TDS_RCV_W_o_int_type_tds_rcv_w_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_TYPE_TDS_RCV_GM_UNION
 结构说明  : INT_TYPE_TDS_RCV_GM 寄存器结构定义。地址偏移量:0x044C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_type_tds_rcv_gm_reg;
    struct
    {
        unsigned int  o_int_type_tds_rcv_gm : 16; /* bit[0-15] : 中断状态标志。各bit单独对应一种中断类型，高有效。
                                                                 [0]: 中断类型0。GM（主模）提前通知TDS异系统测量启动中断。
                                                                 [1]: 中断类型1。GM（主模）进GAP中断，通知TDS进行异系统测量射频通道配置，天线切换等操作。
                                                                 [2]: 中断类型2。GM（主模）出GAP中断。
                                                                 [3]: 中断类型3。GM（从模）测量结束中断。
                                                                 [4]: 中断类型4。GM（主模）强制TDS退出异系统测量中断。
                                                                 [5]: 中断类型5。GM（主模）通知TDS上报本次测量结果。
                                                                 [6]: 中断类型6。保留。
                                                                 [15:7]: 对应中断类型[15:7]，预留。
                                                                 中断状态标志0，1，2只有当GM处于主模时才能产生。
                                                                 软件读取该中断状态上报寄存器后，需要和0x07D0的int_mask_tds_rcv_gm相与，再判断是否需要处理。 */
        unsigned int  reserved              : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_TYPE_TDS_RCV_GM_UNION;
#define BBPCOMM_INT_TYPE_TDS_RCV_GM_o_int_type_tds_rcv_gm_START  (0)
#define BBPCOMM_INT_TYPE_TDS_RCV_GM_o_int_type_tds_rcv_gm_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_TYPE_TDS_RCV_GS_UNION
 结构说明  : INT_TYPE_TDS_RCV_GS 寄存器结构定义。地址偏移量:0x0450，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_type_tds_rcv_gs_reg;
    struct
    {
        unsigned int  o_int_type_tds_rcv_gs : 16; /* bit[0-15] : [0]: 中断类型0。GS（主模）提前通知TDS异系统测量启动中断。
                                                                 [1]: 中断类型1。GS（主模）进GAP中断，通知TDS进行异系统测量射频通道配置，天线切换等操作。
                                                                 [2]: 中断类型2。GS（主模）出GAP中断。
                                                                 [3]: 中断类型3。GS（从模）测量结束中断。
                                                                 [4]: 中断类型4。GS（主模）强制TDS退出异系统测量中断。
                                                                 [5]: 中断类型5。GS（主模）通知TDS上报本次测量结果。
                                                                 [6]: 中断类型6。保留。
                                                                 [15:7]: 对应中断类型[15:7]，预留。
                                                                 中断状态标志0，1，2只有当TDS处于主模时才能产生。
                                                                 软件读取该中断状态上报寄存器后，需要和0x07D4的int_mask_tds_rcv_gs相与，再判断是否需要处理。 */
        unsigned int  reserved              : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_TYPE_TDS_RCV_GS_UNION;
#define BBPCOMM_INT_TYPE_TDS_RCV_GS_o_int_type_tds_rcv_gs_START  (0)
#define BBPCOMM_INT_TYPE_TDS_RCV_GS_o_int_type_tds_rcv_gs_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_TYPE_TDS_RCV_TDS_UNION
 结构说明  : INT_TYPE_TDS_RCV_TDS 寄存器结构定义。地址偏移量:0x0454，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_type_tds_rcv_tds_reg;
    struct
    {
        unsigned int  o_int_type_tds_rcv_tds : 16; /* bit[0-15] : 中断状态标志。各bit单独对应一种中断类型，高有效。
                                                                  [0]: 中断类型0。TDS（主模）提前通知TDS异频测量启动中断。
                                                                  [1]: 中断类型1。TDS（主模）进GAP中断，通知TDS进行异频测量射频通道配置，天线切换等操作。
                                                                  [2]: 中断类型2。TDS（主模）出GAP中断。
                                                                  [3]: 中断类型3。TDS（从模，即异频）测量结束中断。
                                                                  [4]: 中断类型4。TDS（主模）强制TDS退出异频测量中断。
                                                                  [5]: 中断类型5。TDS（主模）通知TDS上报本次测量结果。
                                                                  [6]: 中断类型6。保留。
                                                                  [15:7]: 对应中断类型[15:7]，预留。
                                                                  中断状态标志0，1，2只有当TDS处于主模时才能产生。
                                                                  软件读取该中断状态上报寄存器后，需要和0x07CC的int_mask_tds_rcv_tds相与，再判断是否需要处理。 */
        unsigned int  reserved               : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_TYPE_TDS_RCV_TDS_UNION;
#define BBPCOMM_INT_TYPE_TDS_RCV_TDS_o_int_type_tds_rcv_tds_START  (0)
#define BBPCOMM_INT_TYPE_TDS_RCV_TDS_o_int_type_tds_rcv_tds_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_TYPE_TDS_INT012_UNION
 结构说明  : INT_TYPE_TDS_INT012 寄存器结构定义。地址偏移量:0x0458，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_type_tds_int012_reg;
    struct
    {
        unsigned int  o_int_type_tds_int012 : 3;  /* bit[0-2] : 增加主模产生int0、1、2的上报（(包括异频、异系统场景)），高有效。
                                                                [0]: T主模时，CTU告诉通知TDSP产生int0中断。
                                                                [1]: T主模时，CTU告诉通知TDSP产生int1中断。
                                                                [2]: T主模时，CTU告诉通知TDSP产生int2中断。
                                                                软件读取该中断状态上报寄存器后，需要和0x07DC的int_mask_tds_int012相与，再判断是否需要处理。 */
        unsigned int  reserved              : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_INT_TYPE_TDS_INT012_UNION;
#define BBPCOMM_INT_TYPE_TDS_INT012_o_int_type_tds_int012_START  (0)
#define BBPCOMM_INT_TYPE_TDS_INT012_o_int_type_tds_int012_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_TDS_SND_LTE_INT_13_UNION
 结构说明  : TDS_SND_LTE_INT_13 寄存器结构定义。地址偏移量:0x045C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      tds_snd_lte_int_13_reg;
    struct
    {
        unsigned int  reserved_0         : 3;  /* bit[0-2]  : 保留 */
        unsigned int  tds_snd_lte_int_13 : 13; /* bit[3-15] : 逻辑自清零。高有效。
                                                              
                                                              bit15~7：对应tds_snd_lte_int_15 ~ 7。
                                                              TDS DSP通过此寄存器触发类型15~7中断（int_type_lte_rcv_tds[15:7]）给LDSP。
                                                              生效时刻：立即生效
                                                              
                                                              bit6：对应tds_snd_lte_int_6。
                                                              TDSDSP通过此寄存器触发类型6中断（int_type_lte_rcv_tds[6]）给LDSP。
                                                              生效时刻：立即生效
                                                              
                                                              bit5：对应tds_snd_lte_int_5。
                                                              TDS主模时通知LDSP L测量周期到达，高有效。
                                                              TDS DSP通过此寄存器触发类型5中断（int_type_lte_rcv_tds[5]）给LDSP。
                                                              生效时刻：立即生效
                                                              
                                                              bit4：对应tds_snd_lte_int_4。
                                                              TDS主模时强制退出异系统测量指示。高有效。
                                                              TDS DSP通过此寄存器触发类型4中断（int_type_lte_rcv_tds[4]）给LDSP。
                                                              生效时刻：立即生效
                                                              
                                                              bit3：对应tds_snd_lte_int_3。TDS测量结束指示，高有效。
                                                              用于触发中断类型3 （int_type_lte_rcv_tds[3]）给LDSP。L主模下对TDS进行异系统测量时，如果TDS测量结束，TDS DSP配置此标志为1。 
                                                              生效时刻：立即生效 */
        unsigned int  reserved_1         : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_TDS_SND_LTE_INT_13_UNION;
#define BBPCOMM_TDS_SND_LTE_INT_13_tds_snd_lte_int_13_START  (3)
#define BBPCOMM_TDS_SND_LTE_INT_13_tds_snd_lte_int_13_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_TDS_SND_TDS_INT_13_UNION
 结构说明  : TDS_SND_TDS_INT_13 寄存器结构定义。地址偏移量:0x0460，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      tds_snd_tds_int_13_reg;
    struct
    {
        unsigned int  reserved_0         : 3;  /* bit[0-2]  : 保留 */
        unsigned int  tds_snd_tds_int_13 : 13; /* bit[3-15] : 逻辑自清零。高有效。
                                                              
                                                              bit15~7：对应tds_snd_tds_int_15 ~ 7。
                                                              TDS DSP通过此寄存器触发类型15~7中断（int_type_tds_rcv_tds[15:7]）给TDSP。
                                                              生效时刻：立即生效
                                                              
                                                              bit6：对应tds_snd_tds_int_6。
                                                              TDSDSP通过此寄存器触发类型6中断（int_type_tds_rcv_tds[6]）给TDSP。
                                                              生效时刻：立即生效
                                                              
                                                              bit5：对应tds_snd_tds_int_5。
                                                              TDS主模时通知TDSP T测量周期到达，高有效。
                                                              TDS DSP通过此寄存器触发类型5中断（int_type_tds_rcv_tds[5]）给TDSP。
                                                              生效时刻：立即生效
                                                              
                                                              bit4：对应tds_snd_tds_int_4。
                                                              TDS主模时强制退出异系统测量指示。高有效。
                                                              TDS DSP通过此寄存器触发类型4中断（int_type_tds_rcv_tds[4]）给TDSP。
                                                              生效时刻：立即生效
                                                              
                                                              bit3：对应tds_snd_tds_int_3。TDS测量结束指示，高有效。
                                                              用于触发中断类型3 （int_type_tds_rcv_tds[3]）给TDSP。T主模下对TDS进行异系统测量时，如果TDS测量结束，TDS DSP配置此标志为1。 
                                                              生效时刻：立即生效 */
        unsigned int  reserved_1         : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_TDS_SND_TDS_INT_13_UNION;
#define BBPCOMM_TDS_SND_TDS_INT_13_tds_snd_tds_int_13_START  (3)
#define BBPCOMM_TDS_SND_TDS_INT_13_tds_snd_tds_int_13_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_TDS_SND_GM_INT_13_UNION
 结构说明  : TDS_SND_GM_INT_13 寄存器结构定义。地址偏移量:0x0464，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      tds_snd_gm_int_13_reg;
    struct
    {
        unsigned int  reserved_0        : 3;  /* bit[0-2]  : 保留 */
        unsigned int  tds_snd_gm_int_13 : 13; /* bit[3-15] : 逻辑自清零。高有效。
                                                             
                                                             bit15~7：对应tds_snd_gm_int_15 ~ 7。
                                                             TDS DSP通过此寄存器触发类型15~7中断（int_type_gm_rcv_tds[15:7]）给GMDSP。
                                                             生效时刻：立即生效
                                                             
                                                             bit6：对应tds_snd_gm_int_6。
                                                             TDSDSP通过此寄存器触发类型6中断（int_type_gm_rcv_tds[6]）给GMDSP。
                                                             生效时刻：立即生效
                                                             
                                                             bit5：对应tds_snd_gm_int_5。
                                                             TDS主模时通知GMDSP GM测量周期到达，高有效。
                                                             TDS DSP通过此寄存器触发类型5中断（int_type_gm_rcv_tds[5]）给GMDSP。
                                                             生效时刻：立即生效
                                                             
                                                             bit4：对应tds_snd_gm_int_4。
                                                             TDS主模时强制退出异系统测量指示。高有效。
                                                             TDS DSP通过此寄存器触发类型4中断（int_type_gm_rcv_tds[4]）给GMDSP。
                                                             生效时刻：立即生效
                                                             
                                                             bit3：对应tds_snd_gm_int_3。TDS测量结束指示，高有效。
                                                             用于触发中断类型3 （int_type_gm_rcv_tds[3]）给GMDSP。GM主模下对TDS进行异系统测量时，如果TDS测量结束，TDS DSP配置此标志为1。 
                                                             生效时刻：立即生效 */
        unsigned int  reserved_1        : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_TDS_SND_GM_INT_13_UNION;
#define BBPCOMM_TDS_SND_GM_INT_13_tds_snd_gm_int_13_START  (3)
#define BBPCOMM_TDS_SND_GM_INT_13_tds_snd_gm_int_13_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_TDS_SND_GS_INT_13_UNION
 结构说明  : TDS_SND_GS_INT_13 寄存器结构定义。地址偏移量:0x0468，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      tds_snd_gs_int_13_reg;
    struct
    {
        unsigned int  reserved_0        : 3;  /* bit[0-2]  : 保留 */
        unsigned int  tds_snd_gs_int_13 : 13; /* bit[3-15] : 逻辑自清零。高有效。
                                                             
                                                             bit15~7：对应tds_snd_gs_int_15 ~ 7。
                                                             TDS DSP通过此寄存器触发类型15~7中断（int_type_gs_rcv_tds[15:7]）给GSDSP。
                                                             生效时刻：立即生效
                                                             
                                                             bit6：对应tds_snd_gs_int_6。
                                                             TDSDSP通过此寄存器触发类型6中断（int_type_gs_rcv_tds[6]）给GSDSP。
                                                             生效时刻：立即生效
                                                             
                                                             bit5：对应tds_snd_gs_int_5。
                                                             TDS主模时通知GSDSP GS测量周期到达，高有效。
                                                             TDS DSP通过此寄存器触发类型5中断（int_type_gs_rcv_tds[5]）给GSDSP。
                                                             生效时刻：立即生效
                                                             
                                                             bit4：对应tds_snd_gs_int_4。
                                                             TDS主模时强制退出异系统测量指示。高有效。
                                                             TDS DSP通过此寄存器触发类型4中断（int_type_gs_rcv_tds[4]）给GSDSP。
                                                             生效时刻：立即生效
                                                             
                                                             bit3：对应tds_snd_gs_int_3。TDS测量结束指示，高有效。
                                                             用于触发中断类型3 （int_type_gs_rcv_tds[3]）给GSDSP。GS主模下对TDS进行异系统测量时，如果TDS测量结束，TDS DSP配置此标志为1。 
                                                             生效时刻：立即生效 */
        unsigned int  reserved_1        : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_TDS_SND_GS_INT_13_UNION;
#define BBPCOMM_TDS_SND_GS_INT_13_tds_snd_gs_int_13_START  (3)
#define BBPCOMM_TDS_SND_GS_INT_13_tds_snd_gs_int_13_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_TDS_SND_W_INT_13_UNION
 结构说明  : TDS_SND_W_INT_13 寄存器结构定义。地址偏移量:0x046C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      tds_snd_w_int_13_reg;
    struct
    {
        unsigned int  reserved_0       : 3;  /* bit[0-2]  : 保留 */
        unsigned int  tds_snd_w_int_13 : 13; /* bit[3-15] : 逻辑自清零。高有效。
                                                            
                                                            bit15~7：对应tds_snd_w_int_15 ~ 7。
                                                            TDS DSP通过此寄存器触发类型15~7中断（int_type_w_rcv_tds[15:7]）给WDSP。
                                                            生效时刻：立即生效
                                                            
                                                            bit6：对应tds_snd_w_int_6。
                                                            TDSDSP通过此寄存器触发类型6中断（int_type_w_rcv_tds[6]）给WDSP。
                                                            生效时刻：立即生效
                                                            
                                                            bit5：对应tds_snd_w_int_5。
                                                            TDS主模时通知WDSP W测量周期到达，高有效。
                                                            TDS DSP通过此寄存器触发类型5中断（int_type_w_rcv_tds[5]）给WDSP。
                                                            生效时刻：立即生效
                                                            
                                                            bit4：对应tds_snd_w_int_4。
                                                            TDS主模时强制退出异系统测量指示。高有效。
                                                            TDS DSP通过此寄存器触发类型4中断（int_type_w_rcv_tds[4]）给WDSP。
                                                            生效时刻：立即生效
                                                            
                                                            bit3：对应tds_snd_w_int_3。TDS测量结束指示，高有效。
                                                            用于触发中断类型3 （int_type_w_rcv_tds[3]）给WDSP。W主模下对TDS进行异系统测量时，如果TDS测量结束，TDS DSP配置此标志为1。 
                                                            生效时刻：立即生效 */
        unsigned int  reserved_1       : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_TDS_SND_W_INT_13_UNION;
#define BBPCOMM_TDS_SND_W_INT_13_tds_snd_w_int_13_START  (3)
#define BBPCOMM_TDS_SND_W_INT_13_tds_snd_w_int_13_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_S_GM_CH_NUM_IND_UNION
 结构说明  : S_GM_CH_NUM_IND 寄存器结构定义。地址偏移量:0x0480，初值:0x00000000，宽度:32
 寄存器说明: GM为从模时对应通道的指示寄存器
*****************************************************************************/
typedef union
{
    unsigned int      s_gm_ch_num_ind_reg;
    struct
    {
        unsigned int  s_gm_ch_num_ind     : 2;  /* bit[0-1] : GM为从模时对应的通道选择信号。
                                                              0：选择通道0；
                                                              1：选择通道1；
                                                              2：选择通道2；
                                                              3：选择通道3。
                                                              配置时刻：各模根据通信场景配置 */
        unsigned int  reserved_0          : 2;  /* bit[2-3] : 保留 */
        unsigned int  s_gm_ch_num_ind_sel : 1;  /* bit[4-4] : GM为从模时对应的通道选择信号生效方式。
                                                              0：在int1生效；
                                                              1：立即生效。 */
        unsigned int  reserved_1          : 27; /* bit[5-31]: 保留 */
    } reg;
} BBPCOMM_S_GM_CH_NUM_IND_UNION;
#define BBPCOMM_S_GM_CH_NUM_IND_s_gm_ch_num_ind_START      (0)
#define BBPCOMM_S_GM_CH_NUM_IND_s_gm_ch_num_ind_END        (1)
#define BBPCOMM_S_GM_CH_NUM_IND_s_gm_ch_num_ind_sel_START  (4)
#define BBPCOMM_S_GM_CH_NUM_IND_s_gm_ch_num_ind_sel_END    (4)


/*****************************************************************************
 结构名    : BBPCOMM_GM_INTERSYS_MEASURE_TYPE_UNION
 结构说明  : GM_INTERSYS_MEASURE_TYPE 寄存器结构定义。地址偏移量:0x0484，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      gm_intersys_measure_type_reg;
    struct
    {
        unsigned int  gm_intersys_measure_type : 4;  /* bit[0-3] : 异系统测量类型。
                                                                   4’d0：测量GM RSSI。
                                                                   4’d1: 测量GM bsic verification。
                                                                   4’d2: 测量GM bsic confirm。
                                                                   4’d3: 背景搜GM；
                                                                   4’d4: 2G ANR。
                                                                   其它预留
                                                                   生效时刻：立即生效 */
        unsigned int  reserved                 : 28; /* bit[4-31]: 保留 */
    } reg;
} BBPCOMM_GM_INTERSYS_MEASURE_TYPE_UNION;
#define BBPCOMM_GM_INTERSYS_MEASURE_TYPE_gm_intersys_measure_type_START  (0)
#define BBPCOMM_GM_INTERSYS_MEASURE_TYPE_gm_intersys_measure_type_END    (3)


/*****************************************************************************
 结构名    : BBPCOMM_GM_MEASURE_REPORT_VALID_UNION
 结构说明  : GM_MEASURE_REPORT_VALID 寄存器结构定义。地址偏移量:0x0488，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      gm_measure_report_valid_reg;
    struct
    {
        unsigned int  gm_measure_report_valid : 1;  /* bit[0]   : 单频点测量周期到指示，L或者TDS/W/Gs作为主模，通知GM DSP GM测量的单频点周期到达。
                                                                  只在连接态下需要配置。
                                                                  电平信号，高有效。
                                                                  生效时刻：立即生效 */
        unsigned int  reserved                : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_GM_MEASURE_REPORT_VALID_UNION;
#define BBPCOMM_GM_MEASURE_REPORT_VALID_gm_measure_report_valid_START  (0)
#define BBPCOMM_GM_MEASURE_REPORT_VALID_gm_measure_report_valid_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_INT_CLEAR_GM_RCV_LTE_UNION
 结构说明  : INT_CLEAR_GM_RCV_LTE 寄存器结构定义。地址偏移量:0x0494，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_gm_rcv_lte_reg;
    struct
    {
        unsigned int  int_clear_gm_rcv_lte : 16; /* bit[0-15] : 逻辑自清零。
                                                                中断标志清除指示，高有效。用于清除INT_TYPE_GM_RCV_LTE[15:0]对应bit位
                                                                生效时刻：立即生效 */
        unsigned int  reserved             : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_CLEAR_GM_RCV_LTE_UNION;
#define BBPCOMM_INT_CLEAR_GM_RCV_LTE_int_clear_gm_rcv_lte_START  (0)
#define BBPCOMM_INT_CLEAR_GM_RCV_LTE_int_clear_gm_rcv_lte_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_CLEAR_GM_RCV_TDS_UNION
 结构说明  : INT_CLEAR_GM_RCV_TDS 寄存器结构定义。地址偏移量:0x0498，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_gm_rcv_tds_reg;
    struct
    {
        unsigned int  int_clear_gm_rcv_tds : 16; /* bit[0-15] : 逻辑自清零。
                                                                中断标志清除指示，高有效。用于清除INT_TYPE_GM_RCV_TDS[15:0]对应bit位
                                                                生效时刻：立即生效 */
        unsigned int  reserved             : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_CLEAR_GM_RCV_TDS_UNION;
#define BBPCOMM_INT_CLEAR_GM_RCV_TDS_int_clear_gm_rcv_tds_START  (0)
#define BBPCOMM_INT_CLEAR_GM_RCV_TDS_int_clear_gm_rcv_tds_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_CLEAR_GM_RCV_GM_UNION
 结构说明  : INT_CLEAR_GM_RCV_GM 寄存器结构定义。地址偏移量:0x049C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_gm_rcv_gm_reg;
    struct
    {
        unsigned int  int_clear_gm_rcv_gm : 16; /* bit[0-15] : 逻辑自清零。
                                                               中断标志清除指示，高有效。用于清除INT_TYPE_GM_RCV_GM[15:0]对应bit位
                                                               生效时刻：立即生效 */
        unsigned int  reserved            : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_CLEAR_GM_RCV_GM_UNION;
#define BBPCOMM_INT_CLEAR_GM_RCV_GM_int_clear_gm_rcv_gm_START  (0)
#define BBPCOMM_INT_CLEAR_GM_RCV_GM_int_clear_gm_rcv_gm_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_CLEAR_GM_RCV_GS_UNION
 结构说明  : INT_CLEAR_GM_RCV_GS 寄存器结构定义。地址偏移量:0x04A0，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_gm_rcv_gs_reg;
    struct
    {
        unsigned int  int_clear_gm_rcv_gs : 16; /* bit[0-15] : 逻辑自清零。
                                                               中断标志清除指示，高有效。用于清除INT_TYPE_GM_RCV_GS[15:0]对应bit位
                                                               生效时刻：立即生效 */
        unsigned int  reserved            : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_CLEAR_GM_RCV_GS_UNION;
#define BBPCOMM_INT_CLEAR_GM_RCV_GS_int_clear_gm_rcv_gs_START  (0)
#define BBPCOMM_INT_CLEAR_GM_RCV_GS_int_clear_gm_rcv_gs_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_CLEAR_GM_RCV_W_UNION
 结构说明  : INT_CLEAR_GM_RCV_W 寄存器结构定义。地址偏移量:0x04A4，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_gm_rcv_w_reg;
    struct
    {
        unsigned int  int_clear_gm_rcv_w : 16; /* bit[0-15] : 逻辑自清零。
                                                              中断标志清除指示，高有效。用于清除INT_TYPE_GM_RCV_W[15:0]对应bit位
                                                              生效时刻：立即生效 */
        unsigned int  reserved           : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_CLEAR_GM_RCV_W_UNION;
#define BBPCOMM_INT_CLEAR_GM_RCV_W_int_clear_gm_rcv_w_START  (0)
#define BBPCOMM_INT_CLEAR_GM_RCV_W_int_clear_gm_rcv_w_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_CLEAR_GM_INT012_UNION
 结构说明  : INT_CLEAR_GM_INT012 寄存器结构定义。地址偏移量:0x04A8，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_gm_int012_reg;
    struct
    {
        unsigned int  int_clear_gm_int012 : 3;  /* bit[0-2] : 逻辑自清零。
                                                              中断标志清除指示，高有效。用于清除INT_TYPE_GM_INT012[2:0]对应bit位
                                                              生效时刻：立即生效 */
        unsigned int  reserved            : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_INT_CLEAR_GM_INT012_UNION;
#define BBPCOMM_INT_CLEAR_GM_INT012_int_clear_gm_int012_START  (0)
#define BBPCOMM_INT_CLEAR_GM_INT012_int_clear_gm_int012_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_INT_MASK_GM_RCV_LTE_UNION
 结构说明  : INT_MASK_GM_RCV_LTE 寄存器结构定义。地址偏移量:0x04AC，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_gm_rcv_lte_reg;
    struct
    {
        unsigned int  int_mask_gm_rcv_lte : 16; /* bit[0-15] : 中断屏蔽标志。用于屏蔽INT_TYPE_GM_RCV_LTE[15:0]对应bit中断。
                                                               0：屏蔽中断上报；
                                                               1：使能中断上报。
                                                               配置时刻：初始化
                                                               生效时刻：立即生效 */
        unsigned int  reserved            : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_MASK_GM_RCV_LTE_UNION;
#define BBPCOMM_INT_MASK_GM_RCV_LTE_int_mask_gm_rcv_lte_START  (0)
#define BBPCOMM_INT_MASK_GM_RCV_LTE_int_mask_gm_rcv_lte_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_MASK_GM_RCV_TDS_UNION
 结构说明  : INT_MASK_GM_RCV_TDS 寄存器结构定义。地址偏移量:0x04B0，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_gm_rcv_tds_reg;
    struct
    {
        unsigned int  int_mask_gm_rcv_tds : 16; /* bit[0-15] : 中断屏蔽标志。用于屏蔽INT_TYPE_GM_RCV_TDS[15:0]对应bit中断。
                                                               0：屏蔽中断上报；
                                                               1：使能中断上报。
                                                               配置时刻：初始化
                                                               生效时刻：立即生效 */
        unsigned int  reserved            : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_MASK_GM_RCV_TDS_UNION;
#define BBPCOMM_INT_MASK_GM_RCV_TDS_int_mask_gm_rcv_tds_START  (0)
#define BBPCOMM_INT_MASK_GM_RCV_TDS_int_mask_gm_rcv_tds_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_MASK_GM_RCV_GM_UNION
 结构说明  : INT_MASK_GM_RCV_GM 寄存器结构定义。地址偏移量:0x04B4，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_gm_rcv_gm_reg;
    struct
    {
        unsigned int  int_mask_gm_rcv_gm : 16; /* bit[0-15] : 中断屏蔽标志。用于屏蔽INT_TYPE_GM_RCV_GM[15:0]对应bit中断。
                                                              0：屏蔽中断上报；
                                                              1：使能中断上报。
                                                              配置时刻：初始化
                                                              生效时刻：立即生效 */
        unsigned int  reserved           : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_MASK_GM_RCV_GM_UNION;
#define BBPCOMM_INT_MASK_GM_RCV_GM_int_mask_gm_rcv_gm_START  (0)
#define BBPCOMM_INT_MASK_GM_RCV_GM_int_mask_gm_rcv_gm_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_MASK_GM_RCV_GS_UNION
 结构说明  : INT_MASK_GM_RCV_GS 寄存器结构定义。地址偏移量:0x04B8，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_gm_rcv_gs_reg;
    struct
    {
        unsigned int  int_mask_gm_rcv_gs : 16; /* bit[0-15] : 中断屏蔽标志。用于屏蔽INT_TYPE_GM_RCV_GS[15:0]对应bit中断。
                                                              0：屏蔽中断上报；
                                                              1：使能中断上报。
                                                              配置时刻：初始化
                                                              生效时刻：立即生效 */
        unsigned int  reserved           : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_MASK_GM_RCV_GS_UNION;
#define BBPCOMM_INT_MASK_GM_RCV_GS_int_mask_gm_rcv_gs_START  (0)
#define BBPCOMM_INT_MASK_GM_RCV_GS_int_mask_gm_rcv_gs_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_MASK_GM_RCV_W_UNION
 结构说明  : INT_MASK_GM_RCV_W 寄存器结构定义。地址偏移量:0x04BC，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_gm_rcv_w_reg;
    struct
    {
        unsigned int  int_mask_gm_rcv_w : 16; /* bit[0-15] : 中断屏蔽标志。用于屏蔽INT_TYPE_GM_RCV_W[15:0]对应bit中断。
                                                             0：屏蔽中断上报；
                                                             1：使能中断上报。
                                                             配置时刻：初始化
                                                             生效时刻：立即生效 */
        unsigned int  reserved          : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_MASK_GM_RCV_W_UNION;
#define BBPCOMM_INT_MASK_GM_RCV_W_int_mask_gm_rcv_w_START  (0)
#define BBPCOMM_INT_MASK_GM_RCV_W_int_mask_gm_rcv_w_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_MASK_GM_INT012_UNION
 结构说明  : INT_MASK_GM_INT012 寄存器结构定义。地址偏移量:0x04C0，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_gm_int012_reg;
    struct
    {
        unsigned int  int_mask_gm_int012 : 3;  /* bit[0-2] : 中断屏蔽标志。用于屏蔽INT_TYPE_GM_INT012[2:0]对应bit中断。
                                                             0：屏蔽中断上报；
                                                             1：使能中断上报。
                                                             配置时刻：初始化
                                                             生效时刻：立即生效 */
        unsigned int  reserved           : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_INT_MASK_GM_INT012_UNION;
#define BBPCOMM_INT_MASK_GM_INT012_int_mask_gm_int012_START  (0)
#define BBPCOMM_INT_MASK_GM_INT012_int_mask_gm_int012_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_INT_TYPE_GM_RCV_LTE_UNION
 结构说明  : INT_TYPE_GM_RCV_LTE 寄存器结构定义。地址偏移量:0x04C4，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_type_gm_rcv_lte_reg;
    struct
    {
        unsigned int  o_int_type_gm_rcv_lte : 16; /* bit[0-15] : 中断状态标志。各bit单独对应一种中断类型，高有效。
                                                                 [0]: 中断类型0。 LTE（主模）提前通知GM异系统测量启动中断。
                                                                 [1]: 中断类型1。 LTE（主模）进GAP中断，通知GM进行异系统测量射频通道配置，天线切换等操作。
                                                                 [2]: 中断类型2。 LTE（主模）出GAP中断。
                                                                 [3]: 中断类型3。LTE（从模）测量结束中断。
                                                                 [4]: 中断类型4。LTE（主模）强制GM退出异系统测量中断。
                                                                 [5]: 中断类型5。LTE（主模）通知GM上报本次测量结果。
                                                                 [6]: 保留。
                                                                 [15:7]: 对应中断类型[15:7]，预留。
                                                                 软件读取该中断状态上报寄存器后，需要和0x0834的int_mask_gm_rcv_lte相与，再判断是否需要处理。 */
        unsigned int  reserved              : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_TYPE_GM_RCV_LTE_UNION;
#define BBPCOMM_INT_TYPE_GM_RCV_LTE_o_int_type_gm_rcv_lte_START  (0)
#define BBPCOMM_INT_TYPE_GM_RCV_LTE_o_int_type_gm_rcv_lte_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_TYPE_GM_RCV_TDS_UNION
 结构说明  : INT_TYPE_GM_RCV_TDS 寄存器结构定义。地址偏移量:0x04C8，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_type_gm_rcv_tds_reg;
    struct
    {
        unsigned int  o_int_type_gm_rcv_tds : 16; /* bit[0-15] : 中断状态标志0，1，2只有当TDS处于主模时才能产生。
                                                                 
                                                                 [0]: 中断类型0。 TDS（主模）提前通知GM异系统测量启动中断。
                                                                 [1]: 中断类型1。 TDS（主模）进GAP中断，通知GM进行异系统测量射频通道配置，天线切换等操作。
                                                                 [2]: 中断类型2。 TDS（主模）出GAP中断。
                                                                 [3]: 中断类型3。TDS（从模）测量结束中断。
                                                                 [4]: 中断类型4。TDS（主模）强制GM退出异系统测量中断。
                                                                 [5]: 中断类型5。TDS（主模）通知GM上报本次测量结果。
                                                                 [6]: 中断类型6。保留。
                                                                 [15:7]: 对应中断类型[15:7]，预留。
                                                                 软件读取该中断状态上报寄存器后，需要和0x0838的int_mask_gm_rcv_tds相与，再判断是否需要处理。 */
        unsigned int  reserved              : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_TYPE_GM_RCV_TDS_UNION;
#define BBPCOMM_INT_TYPE_GM_RCV_TDS_o_int_type_gm_rcv_tds_START  (0)
#define BBPCOMM_INT_TYPE_GM_RCV_TDS_o_int_type_gm_rcv_tds_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_TYPE_GM_RCV_W_UNION
 结构说明  : INT_TYPE_GM_RCV_W 寄存器结构定义。地址偏移量:0x04CC，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_type_gm_rcv_w_reg;
    struct
    {
        unsigned int  o_int_type_gm_rcv_w : 16; /* bit[0-15] : 中断状态标志。各bit单独对应一种中断类型，高有效。
                                                               [0]: 中断类型0。W（主模）提前通知GM异系统测量启动中断。
                                                               [1]: 中断类型1。W（主模）进GAP中断，通知GM进行异系统测量射频通道配置，天线切换等操作。
                                                               [2]: 中断类型2。W（主模）出GAP中断。
                                                               [3]: 中断类型3。W（从模）测量结束中断。
                                                               [4]: 中断类型4。W（主模）强制GM退出异系统测量中断。
                                                               [5]: 中断类型5。W（主模）通知GM上报本次测量结果。
                                                               [6]: 中断类型6。保留。
                                                               [15:7]: 对应中断类型[15:7]，预留。
                                                               中断状态标志0，1，2只有当W处于主模时才能产生。
                                                               软件读取该中断状态上报寄存器后，需要和0x0844的int_mask_gm_rcv_w相与，再判断是否需要处理。 */
        unsigned int  reserved            : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_TYPE_GM_RCV_W_UNION;
#define BBPCOMM_INT_TYPE_GM_RCV_W_o_int_type_gm_rcv_w_START  (0)
#define BBPCOMM_INT_TYPE_GM_RCV_W_o_int_type_gm_rcv_w_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_TYPE_GM_RCV_GS_UNION
 结构说明  : INT_TYPE_GM_RCV_GS 寄存器结构定义。地址偏移量:0x04D0，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_type_gm_rcv_gs_reg;
    struct
    {
        unsigned int  o_int_type_gm_rcv_gs : 16; /* bit[0-15] : [0]: 中断类型0。GS（主模）提前通知GM异系统测量启动中断。
                                                                [1]: 中断类型1。GS（主模）进GAP中断，通知GM进行异系统测量射频通道配置，天线切换等操作。
                                                                [2]: 中断类型2。GS（主模）出GAP中断。
                                                                [3]: 中断类型3。GS（从模）测量结束中断。
                                                                [4]: 中断类型4。GS（主模）强制GM退出异系统测量中断。
                                                                [5]: 中断类型5。GS（主模）通知GM上报本次测量结果。
                                                                [6]: 中断类型6。保留。
                                                                [15:7]: 对应中断类型[15:7]，预留。
                                                                中断状态标志0，1，2只有当TDS处于主模时才能产生。
                                                                软件读取该中断状态上报寄存器后，需要和0x0840的int_mask_gm_rcv_gs相与，再判断是否需要处理。 */
        unsigned int  reserved             : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_TYPE_GM_RCV_GS_UNION;
#define BBPCOMM_INT_TYPE_GM_RCV_GS_o_int_type_gm_rcv_gs_START  (0)
#define BBPCOMM_INT_TYPE_GM_RCV_GS_o_int_type_gm_rcv_gs_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_TYPE_GM_RCV_GM_UNION
 结构说明  : INT_TYPE_GM_RCV_GM 寄存器结构定义。地址偏移量:0x04D4，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_type_gm_rcv_gm_reg;
    struct
    {
        unsigned int  o_int_type_gm_rcv_gm : 16; /* bit[0-15] : 中断状态标志。各bit单独对应一种中断类型，高有效。
                                                                [0]: 中断类型0。GM（主模）提前通知GM异频测量启动中断。
                                                                [1]: 中断类型1。GM（主模）进GAP中断，通知GM进行异频测量射频通道配置，天线切换等操作。
                                                                [2]: 中断类型2。GM（主模）出GAP中断。
                                                                [3]: 中断类型3。GM（从模，即异频）测量结束中断。
                                                                [4]: 中断类型4。GM（主模）强制GM退出异频测量中断。
                                                                [5]: 中断类型5。GM（主模）通知GM上报本次测量结果。
                                                                [6]: 中断类型6。保留。
                                                                [15:7]: 对应中断类型[15:7]，预留。
                                                                中断状态标志0，1，2只有当GM处于主模时才能产生。
                                                                软件读取该中断状态上报寄存器后，需要和0x083C的int_mask_gm_rcv_gm相与，再判断是否需要处理。 */
        unsigned int  reserved             : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_TYPE_GM_RCV_GM_UNION;
#define BBPCOMM_INT_TYPE_GM_RCV_GM_o_int_type_gm_rcv_gm_START  (0)
#define BBPCOMM_INT_TYPE_GM_RCV_GM_o_int_type_gm_rcv_gm_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_TYPE_GM_INT012_UNION
 结构说明  : INT_TYPE_GM_INT012 寄存器结构定义。地址偏移量:0x04D8，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_type_gm_int012_reg;
    struct
    {
        unsigned int  o_int_type_gm_int012 : 3;  /* bit[0-2] : 增加主模产生int0、1、2的上报（(包括异频、异系统场景)），高有效。
                                                               [0]: GM主模时，CTU告诉通知GMDSP产生int0中断。
                                                               [1]: GM主模时，CTU告诉通知GMDSP产生int1中断。
                                                               [2]: GM主模时，CTU告诉通知GMDSP产生int2中断。
                                                               软件读取该中断状态上报寄存器后，需要和0x0848的int_mask_gm_int012相与，再判断是否需要处理。 */
        unsigned int  reserved             : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_INT_TYPE_GM_INT012_UNION;
#define BBPCOMM_INT_TYPE_GM_INT012_o_int_type_gm_int012_START  (0)
#define BBPCOMM_INT_TYPE_GM_INT012_o_int_type_gm_int012_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_GM_SND_LTE_INT_13_UNION
 结构说明  : GM_SND_LTE_INT_13 寄存器结构定义。地址偏移量:0x04DC，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      gm_snd_lte_int_13_reg;
    struct
    {
        unsigned int  reserved_0        : 3;  /* bit[0-2]  : 保留 */
        unsigned int  gm_snd_lte_int_13 : 13; /* bit[3-15] : 逻辑自清零。高有效。
                                                             
                                                             bit15~7：对应gm_snd_lte_int_15 ~ 7。
                                                             GM DSP通过此寄存器触发类型15~7中断（int_type_lte_rcv_gm[15:7]）给LTEDSP。
                                                             生效时刻：立即生效
                                                             
                                                             bit6：对应gm_snd_lte_int_6。
                                                             GMDSP通过此寄存器触发类型6中断（int_type_lte_rcv_gm[6]）给LTEDSP。
                                                             生效时刻：立即生效
                                                             
                                                             bit5：对应gm_snd_lte_int_5。
                                                             GM主模时通知LTEDSP LTE测量周期到达，高有效。
                                                             GM DSP通过此寄存器触发类型5中断（int_type_lte_rcv_gm[5]）给LTEDSP。
                                                             生效时刻：立即生效
                                                             
                                                             bit4：对应gm_snd_lte_int_4。
                                                             GM主模时强制退出异系统测量指示。高有效。
                                                             GM DSP通过此寄存器触发类型4中断（int_type_lte_rcv_gm[4]）给LTEDSP。
                                                             生效时刻：立即生效
                                                             
                                                             bit3：对应gm_snd_lte_int_3。GM测量结束指示，高有效。
                                                             用于触发中断类型3 （int_type_lte_rcv_gm[3]）给LTEDSP。LTE主模下对GM进行异系统测量时，如果GM测量结束，GM DSP配置此标志为1。 
                                                             生效时刻：立即生效 */
        unsigned int  reserved_1        : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_GM_SND_LTE_INT_13_UNION;
#define BBPCOMM_GM_SND_LTE_INT_13_gm_snd_lte_int_13_START  (3)
#define BBPCOMM_GM_SND_LTE_INT_13_gm_snd_lte_int_13_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_GM_SND_TDS_INT_13_UNION
 结构说明  : GM_SND_TDS_INT_13 寄存器结构定义。地址偏移量:0x04E0，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      gm_snd_tds_int_13_reg;
    struct
    {
        unsigned int  reserved_0        : 3;  /* bit[0-2]  : 保留 */
        unsigned int  gm_snd_tds_int_13 : 13; /* bit[3-15] : 逻辑自清零。高有效。
                                                             
                                                             bit15~7：对应gm_snd_tds_int_15 ~ 7。
                                                             GM DSP通过此寄存器触发类型15~7中断（int_type_tds_rcv_gm[15:7]）给TDSDSP。
                                                             生效时刻：立即生效
                                                             
                                                             bit6：对应gm_snd_tds_int_6。
                                                             GMDSP通过此寄存器触发类型6中断（int_type_tds_rcv_gm[6]）给TDSDSP。
                                                             生效时刻：立即生效
                                                             
                                                             bit5：对应gm_snd_tds_int_5。
                                                             GM主模时通知TDSDSP tds测量周期到达，高有效。
                                                             GM DSP通过此寄存器触发类型5中断（int_type_tds_rcv_gm[5]）给TDSDSP。
                                                             生效时刻：立即生效
                                                             
                                                             bit4：对应gm_snd_tds_int_4。
                                                             GM主模时强制退出异系统测量指示。高有效。
                                                             GM DSP通过此寄存器触发类型4中断（int_type_tds_rcv_gm[4]）给TDSDSP。
                                                             生效时刻：立即生效
                                                             
                                                             bit3：对应gm_snd_tds_int_3。GM测量结束指示，高有效。
                                                             用于触发中断类型3 （int_type_tds_rcv_gm[3]）给TDSDSP。tds主模下对GM进行异系统测量时，如果GM测量结束，GM DSP配置此标志为1。 
                                                             生效时刻：立即生效 */
        unsigned int  reserved_1        : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_GM_SND_TDS_INT_13_UNION;
#define BBPCOMM_GM_SND_TDS_INT_13_gm_snd_tds_int_13_START  (3)
#define BBPCOMM_GM_SND_TDS_INT_13_gm_snd_tds_int_13_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_GM_SND_GM_INT_13_UNION
 结构说明  : GM_SND_GM_INT_13 寄存器结构定义。地址偏移量:0x04E4，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      gm_snd_gm_int_13_reg;
    struct
    {
        unsigned int  reserved_0       : 3;  /* bit[0-2]  : 保留 */
        unsigned int  gm_snd_gm_int_13 : 13; /* bit[3-15] : 逻辑自清零。高有效。
                                                            
                                                            bit15~7：对应gm_snd_gm_int_15 ~ 7。
                                                            GM DSP通过此寄存器触发类型15~7中断（int_type_gm_rcv_gm[15:7]）给GMDSP。
                                                            生效时刻：立即生效
                                                            
                                                            bit6：对应gm_snd_gm_int_6。
                                                            GMDSP通过此寄存器触发类型6中断（int_type_gm_rcv_gm[6]）给GMDSP。
                                                            生效时刻：立即生效
                                                            
                                                            bit5：对应gm_snd_gm_int_5。
                                                            GM主模时通知GMDSP GM测量周期到达，高有效。
                                                            GM DSP通过此寄存器触发类型5中断（int_type_gm_rcv_gm[5]）给GMDSP。
                                                            生效时刻：立即生效
                                                            
                                                            bit4：对应gm_snd_gm_int_4。
                                                            GM主模时强制退出异系统测量指示。高有效。
                                                            GM DSP通过此寄存器触发类型4中断（int_type_gm_rcv_gm[4]）给GMDSP。
                                                            生效时刻：立即生效
                                                            
                                                            bit3：对应gm_snd_gm_int_3。GM测量结束指示，高有效。
                                                            用于触发中断类型3 （int_type_gm_rcv_gm[3]）给GMDSP。GM主模下对GM进行异系统测量时，如果GM测量结束，GM DSP配置此标志为1。 
                                                            生效时刻：立即生效 */
        unsigned int  reserved_1       : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_GM_SND_GM_INT_13_UNION;
#define BBPCOMM_GM_SND_GM_INT_13_gm_snd_gm_int_13_START  (3)
#define BBPCOMM_GM_SND_GM_INT_13_gm_snd_gm_int_13_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_GM_SND_GS_INT_13_UNION
 结构说明  : GM_SND_GS_INT_13 寄存器结构定义。地址偏移量:0x04E8，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      gm_snd_gs_int_13_reg;
    struct
    {
        unsigned int  reserved_0       : 3;  /* bit[0-2]  : 保留 */
        unsigned int  gm_snd_gs_int_13 : 13; /* bit[3-15] : 逻辑自清零。高有效。
                                                            
                                                            bit15~7：对应gm_snd_gs_int_15 ~ 7。
                                                            GM DSP通过此寄存器触发类型15~7中断（int_type_gs_rcv_gm[15:7]）给GSDSP。
                                                            生效时刻：立即生效
                                                            
                                                            bit6：对应gm_snd_gs_int_6。
                                                            GMDSP通过此寄存器触发类型6中断（int_type_gs_rcv_gm[6]）给GSDSP。
                                                            生效时刻：立即生效
                                                            
                                                            bit5：对应gm_snd_gs_int_5。
                                                            GM主模时通知GSDSP GS测量周期到达，高有效。
                                                            GM DSP通过此寄存器触发类型5中断（int_type_gs_rcv_gm[5]）给GSDSP。
                                                            生效时刻：立即生效
                                                            
                                                            bit4：对应gm_snd_gs_int_4。
                                                            GM主模时强制退出异系统测量指示。高有效。
                                                            GM DSP通过此寄存器触发类型4中断（int_type_gs_rcv_gm[4]）给GSDSP。
                                                            生效时刻：立即生效
                                                            
                                                            bit3：对应gm_snd_gs_int_3。GM测量结束指示，高有效。
                                                            用于触发中断类型3 （int_type_gs_rcv_gm[3]）给GSDSP。GS主模下对GM进行异系统测量时，如果GM测量结束，GM DSP配置此标志为1。 
                                                            生效时刻：立即生效 */
        unsigned int  reserved_1       : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_GM_SND_GS_INT_13_UNION;
#define BBPCOMM_GM_SND_GS_INT_13_gm_snd_gs_int_13_START  (3)
#define BBPCOMM_GM_SND_GS_INT_13_gm_snd_gs_int_13_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_GM_SND_W_INT_13_UNION
 结构说明  : GM_SND_W_INT_13 寄存器结构定义。地址偏移量:0x04EC，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      gm_snd_w_int_13_reg;
    struct
    {
        unsigned int  reserved_0      : 3;  /* bit[0-2]  : 保留 */
        unsigned int  gm_snd_w_int_13 : 13; /* bit[3-15] : 逻辑自清零。高有效。
                                                           
                                                           bit15~7：对应gm_snd_lte_int_15 ~ 7。
                                                           GM DSP通过此寄存器触发类型15~7中断（int_type_lte_rcv_gm[15:7]）给LTEDSP。
                                                           生效时刻：立即生效
                                                           
                                                           bit6：对应gm_snd_lte_int_6。
                                                           GMDSP通过此寄存器触发类型6中断（int_type_lte_rcv_gm[6]）给LTEDSP。
                                                           生效时刻：立即生效
                                                           
                                                           bit5：对应gm_snd_lte_int_5。
                                                           GM主模时通知LTEDSP LTE测量周期到达，高有效。
                                                           GM DSP通过此寄存器触发类型5中断（int_type_lte_rcv_gm[5]）给LTEDSP。
                                                           生效时刻：立即生效
                                                           
                                                           bit4：对应gm_snd_lte_int_4。
                                                           GM主模时强制退出异系统测量指示。高有效。
                                                           GM DSP通过此寄存器触发类型4中断（int_type_lte_rcv_gm[4]）给LTEDSP。
                                                           生效时刻：立即生效
                                                           
                                                           bit3：对应gm_snd_lte_int_3。GM测量结束指示，高有效。
                                                           用于触发中断类型3 （int_type_lte_rcv_gm[3]）给LTEDSP。LTE主模下对GM进行异系统测量时，如果GM测量结束，GM DSP配置此标志为1。 
                                                           生效时刻：立即生效 */
        unsigned int  reserved_1      : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_GM_SND_W_INT_13_UNION;
#define BBPCOMM_GM_SND_W_INT_13_gm_snd_w_int_13_START  (3)
#define BBPCOMM_GM_SND_W_INT_13_gm_snd_w_int_13_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_S_GS_CH_NUM_IND_UNION
 结构说明  : S_GS_CH_NUM_IND 寄存器结构定义。地址偏移量:0x0500，初值:0x00000000，宽度:32
 寄存器说明: GS为从模时对应通道的指示寄存器
*****************************************************************************/
typedef union
{
    unsigned int      s_gs_ch_num_ind_reg;
    struct
    {
        unsigned int  s_gs_ch_num_ind     : 2;  /* bit[0-1] : GS为从模时对应的通道选择信号。
                                                              0：选择通道0；
                                                              1：选择通道1；
                                                              2：选择通道2；
                                                              3：选择通道3。
                                                              配置时刻：各模根据通信场景配置 */
        unsigned int  reserved_0          : 2;  /* bit[2-3] : 保留 */
        unsigned int  s_gs_ch_num_ind_sel : 1;  /* bit[4-4] : GS为从模时对应的通道选择信号生效方式。
                                                              0：在int1生效；
                                                              1：立即生效。 */
        unsigned int  reserved_1          : 27; /* bit[5-31]: 保留 */
    } reg;
} BBPCOMM_S_GS_CH_NUM_IND_UNION;
#define BBPCOMM_S_GS_CH_NUM_IND_s_gs_ch_num_ind_START      (0)
#define BBPCOMM_S_GS_CH_NUM_IND_s_gs_ch_num_ind_END        (1)
#define BBPCOMM_S_GS_CH_NUM_IND_s_gs_ch_num_ind_sel_START  (4)
#define BBPCOMM_S_GS_CH_NUM_IND_s_gs_ch_num_ind_sel_END    (4)


/*****************************************************************************
 结构名    : BBPCOMM_GS_INTERSYS_MEASURE_TYPE_UNION
 结构说明  : GS_INTERSYS_MEASURE_TYPE 寄存器结构定义。地址偏移量:0x0504，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      gs_intersys_measure_type_reg;
    struct
    {
        unsigned int  gs_intersys_measure_type : 4;  /* bit[0-3] : 异系统测量类型。
                                                                   4’d0：测量GS RSSI。
                                                                   4’d1: 测量GS bsic verification。
                                                                   4’d2: 测量GS bsic confirm。
                                                                   4’d3: 背景搜GS
                                                                   4’d4: 2G ANR。
                                                                   其它预留
                                                                   生效时刻：立即生效 */
        unsigned int  reserved                 : 28; /* bit[4-31]: 保留 */
    } reg;
} BBPCOMM_GS_INTERSYS_MEASURE_TYPE_UNION;
#define BBPCOMM_GS_INTERSYS_MEASURE_TYPE_gs_intersys_measure_type_START  (0)
#define BBPCOMM_GS_INTERSYS_MEASURE_TYPE_gs_intersys_measure_type_END    (3)


/*****************************************************************************
 结构名    : BBPCOMM_GS_MEASURE_REPORT_VALID_UNION
 结构说明  : GS_MEASURE_REPORT_VALID 寄存器结构定义。地址偏移量:0x0508，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      gs_measure_report_valid_reg;
    struct
    {
        unsigned int  gs_measure_report_valid : 1;  /* bit[0]   : 单频点测量周期到指示，L或者TDS/W/Gm作为主模，通知GS DSP GS测量的单频点周期到达。
                                                                  只在连接态下需要配置。
                                                                  电平信号，高有效。
                                                                  生效时刻：立即生效 */
        unsigned int  reserved                : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_GS_MEASURE_REPORT_VALID_UNION;
#define BBPCOMM_GS_MEASURE_REPORT_VALID_gs_measure_report_valid_START  (0)
#define BBPCOMM_GS_MEASURE_REPORT_VALID_gs_measure_report_valid_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_INT_CLEAR_GS_RCV_LTE_UNION
 结构说明  : INT_CLEAR_GS_RCV_LTE 寄存器结构定义。地址偏移量:0x0514，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_gs_rcv_lte_reg;
    struct
    {
        unsigned int  int_clear_gs_rcv_lte : 16; /* bit[0-15] : 逻辑自清零。
                                                                中断标志清除指示，高有效。用于清除INT_TYPE_GS_RCV_LTE[15:0]对应bit位
                                                                生效时刻：立即生效 */
        unsigned int  reserved             : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_CLEAR_GS_RCV_LTE_UNION;
#define BBPCOMM_INT_CLEAR_GS_RCV_LTE_int_clear_gs_rcv_lte_START  (0)
#define BBPCOMM_INT_CLEAR_GS_RCV_LTE_int_clear_gs_rcv_lte_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_CLEAR_GS_RCV_TDS_UNION
 结构说明  : INT_CLEAR_GS_RCV_TDS 寄存器结构定义。地址偏移量:0x0518，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_gs_rcv_tds_reg;
    struct
    {
        unsigned int  int_clear_gs_rcv_tds : 16; /* bit[0-15] : 逻辑自清零。
                                                                中断标志清除指示，高有效。用于清除INT_TYPE_GS_RCV_TDS[15:0]对应bit位
                                                                生效时刻：立即生效 */
        unsigned int  reserved             : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_CLEAR_GS_RCV_TDS_UNION;
#define BBPCOMM_INT_CLEAR_GS_RCV_TDS_int_clear_gs_rcv_tds_START  (0)
#define BBPCOMM_INT_CLEAR_GS_RCV_TDS_int_clear_gs_rcv_tds_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_CLEAR_GS_RCV_GM_UNION
 结构说明  : INT_CLEAR_GS_RCV_GM 寄存器结构定义。地址偏移量:0x051C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_gs_rcv_gm_reg;
    struct
    {
        unsigned int  int_clear_gs_rcv_gm : 16; /* bit[0-15] : 逻辑自清零。
                                                               中断标志清除指示，高有效。用于清除INT_TYPE_GS_RCV_GM[15:0]对应bit位
                                                               生效时刻：立即生效 */
        unsigned int  reserved            : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_CLEAR_GS_RCV_GM_UNION;
#define BBPCOMM_INT_CLEAR_GS_RCV_GM_int_clear_gs_rcv_gm_START  (0)
#define BBPCOMM_INT_CLEAR_GS_RCV_GM_int_clear_gs_rcv_gm_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_CLEAR_GS_RCV_GS_UNION
 结构说明  : INT_CLEAR_GS_RCV_GS 寄存器结构定义。地址偏移量:0x0520，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_gs_rcv_gs_reg;
    struct
    {
        unsigned int  int_clear_gs_rcv_gs : 16; /* bit[0-15] : 逻辑自清零。
                                                               中断标志清除指示，高有效。用于清除INT_TYPE_GS_RCV_GS[15:0]对应bit位
                                                               生效时刻：立即生效 */
        unsigned int  reserved            : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_CLEAR_GS_RCV_GS_UNION;
#define BBPCOMM_INT_CLEAR_GS_RCV_GS_int_clear_gs_rcv_gs_START  (0)
#define BBPCOMM_INT_CLEAR_GS_RCV_GS_int_clear_gs_rcv_gs_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_CLEAR_GS_RCV_W_UNION
 结构说明  : INT_CLEAR_GS_RCV_W 寄存器结构定义。地址偏移量:0x0524，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_gs_rcv_w_reg;
    struct
    {
        unsigned int  int_clear_gs_rcv_w : 16; /* bit[0-15] : 逻辑自清零。
                                                              中断标志清除指示，高有效。用于清除INT_TYPE_GS_RCV_W[15:0]对应bit位
                                                              生效时刻：立即生效 */
        unsigned int  reserved           : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_CLEAR_GS_RCV_W_UNION;
#define BBPCOMM_INT_CLEAR_GS_RCV_W_int_clear_gs_rcv_w_START  (0)
#define BBPCOMM_INT_CLEAR_GS_RCV_W_int_clear_gs_rcv_w_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_CLEAR_GS_INT012_UNION
 结构说明  : INT_CLEAR_GS_INT012 寄存器结构定义。地址偏移量:0x0528，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_gs_int012_reg;
    struct
    {
        unsigned int  int_clear_gs_int012 : 3;  /* bit[0-2] : 逻辑自清零。
                                                              中断标志清除指示，高有效。用于清除INT_TYPE_GS_INT012[2:0]对应bit位
                                                              生效时刻：立即生效 */
        unsigned int  reserved            : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_INT_CLEAR_GS_INT012_UNION;
#define BBPCOMM_INT_CLEAR_GS_INT012_int_clear_gs_int012_START  (0)
#define BBPCOMM_INT_CLEAR_GS_INT012_int_clear_gs_int012_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_INT_MASK_GS_RCV_LTE_UNION
 结构说明  : INT_MASK_GS_RCV_LTE 寄存器结构定义。地址偏移量:0x052C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_gs_rcv_lte_reg;
    struct
    {
        unsigned int  int_mask_gs_rcv_lte : 16; /* bit[0-15] : 中断屏蔽标志。用于屏蔽INT_TYPE_GS_RCV_LTE[15:0]对应bit中断。
                                                               0：屏蔽中断上报；
                                                               1：使能中断上报。
                                                               配置时刻：初始化
                                                               生效时刻：立即生效 */
        unsigned int  reserved            : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_MASK_GS_RCV_LTE_UNION;
#define BBPCOMM_INT_MASK_GS_RCV_LTE_int_mask_gs_rcv_lte_START  (0)
#define BBPCOMM_INT_MASK_GS_RCV_LTE_int_mask_gs_rcv_lte_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_MASK_GS_RCV_TDS_UNION
 结构说明  : INT_MASK_GS_RCV_TDS 寄存器结构定义。地址偏移量:0x0530，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_gs_rcv_tds_reg;
    struct
    {
        unsigned int  int_mask_gs_rcv_tds : 16; /* bit[0-15] : 中断屏蔽标志。用于屏蔽INT_TYPE_GS_RCV_TDS[15:0]对应bit中断。
                                                               0：屏蔽中断上报；
                                                               1：使能中断上报。
                                                               配置时刻：初始化
                                                               生效时刻：立即生效 */
        unsigned int  reserved            : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_MASK_GS_RCV_TDS_UNION;
#define BBPCOMM_INT_MASK_GS_RCV_TDS_int_mask_gs_rcv_tds_START  (0)
#define BBPCOMM_INT_MASK_GS_RCV_TDS_int_mask_gs_rcv_tds_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_MASK_GS_RCV_GM_UNION
 结构说明  : INT_MASK_GS_RCV_GM 寄存器结构定义。地址偏移量:0x0534，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_gs_rcv_gm_reg;
    struct
    {
        unsigned int  int_mask_gs_rcv_gm : 16; /* bit[0-15] : 中断屏蔽标志。用于屏蔽INT_TYPE_GS_RCV_GM[15:0]对应bit中断。
                                                              0：屏蔽中断上报；
                                                              1：使能中断上报。
                                                              配置时刻：初始化
                                                              生效时刻：立即生效 */
        unsigned int  reserved           : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_MASK_GS_RCV_GM_UNION;
#define BBPCOMM_INT_MASK_GS_RCV_GM_int_mask_gs_rcv_gm_START  (0)
#define BBPCOMM_INT_MASK_GS_RCV_GM_int_mask_gs_rcv_gm_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_MASK_GS_RCV_GS_UNION
 结构说明  : INT_MASK_GS_RCV_GS 寄存器结构定义。地址偏移量:0x0538，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_gs_rcv_gs_reg;
    struct
    {
        unsigned int  int_mask_gs_rcv_gs : 16; /* bit[0-15] : 中断屏蔽标志。用于屏蔽INT_TYPE_GS_RCV_GS[15:0]对应bit中断。
                                                              0：屏蔽中断上报；
                                                              1：使能中断上报。
                                                              配置时刻：初始化
                                                              生效时刻：立即生效 */
        unsigned int  reserved           : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_MASK_GS_RCV_GS_UNION;
#define BBPCOMM_INT_MASK_GS_RCV_GS_int_mask_gs_rcv_gs_START  (0)
#define BBPCOMM_INT_MASK_GS_RCV_GS_int_mask_gs_rcv_gs_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_MASK_GS_RCV_W_UNION
 结构说明  : INT_MASK_GS_RCV_W 寄存器结构定义。地址偏移量:0x053C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_gs_rcv_w_reg;
    struct
    {
        unsigned int  int_mask_gs_rcv_w : 16; /* bit[0-15] : 中断屏蔽标志。用于屏蔽INT_TYPE_GS_RCV_W[15:0]对应bit中断。
                                                             0：屏蔽中断上报；
                                                             1：使能中断上报。
                                                             配置时刻：初始化
                                                             生效时刻：立即生效 */
        unsigned int  reserved          : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_MASK_GS_RCV_W_UNION;
#define BBPCOMM_INT_MASK_GS_RCV_W_int_mask_gs_rcv_w_START  (0)
#define BBPCOMM_INT_MASK_GS_RCV_W_int_mask_gs_rcv_w_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_MASK_GS_INT012_UNION
 结构说明  : INT_MASK_GS_INT012 寄存器结构定义。地址偏移量:0x0540，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_gs_int012_reg;
    struct
    {
        unsigned int  int_mask_gs_int012 : 3;  /* bit[0-2] : 中断屏蔽标志。用于屏蔽INT_TYPE_GS_INT012[2:0]对应bit中断。
                                                             0：屏蔽中断上报；
                                                             1：使能中断上报。
                                                             配置时刻：初始化
                                                             生效时刻：立即生效 */
        unsigned int  reserved           : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_INT_MASK_GS_INT012_UNION;
#define BBPCOMM_INT_MASK_GS_INT012_int_mask_gs_int012_START  (0)
#define BBPCOMM_INT_MASK_GS_INT012_int_mask_gs_int012_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_INT_TYPE_GS_RCV_LTE_UNION
 结构说明  : INT_TYPE_GS_RCV_LTE 寄存器结构定义。地址偏移量:0x0544，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_type_gs_rcv_lte_reg;
    struct
    {
        unsigned int  o_int_type_gs_rcv_lte : 16; /* bit[0-15] : 中断状态标志。各bit单独对应一种中断类型，高有效。
                                                                 [0]: 中断类型0。 LTE（主模）提前通知GS异系统测量启动中断。
                                                                 [1]: 中断类型1。 LTE（主模）进GAP中断，通知GS进行异系统测量射频通道配置，天线切换等操作。
                                                                 [2]: 中断类型2。 LTE（主模）出GAP中断。
                                                                 [3]: 中断类型3。LTE（从模）测量结束中断。
                                                                 [4]: 中断类型4。LTE（主模）强制GS退出异系统测量中断。
                                                                 [5]: 中断类型5。LTE（主模）通知GS上报本次测量结果。
                                                                 [6]: 保留。
                                                                 [15:7]: 对应中断类型[15:7]，预留。
                                                                 软件读取该中断状态上报寄存器后，需要和0x08A0的int_mask_gs_rcv_lte相与，再判断是否需要处理。 */
        unsigned int  reserved              : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_TYPE_GS_RCV_LTE_UNION;
#define BBPCOMM_INT_TYPE_GS_RCV_LTE_o_int_type_gs_rcv_lte_START  (0)
#define BBPCOMM_INT_TYPE_GS_RCV_LTE_o_int_type_gs_rcv_lte_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_TYPE_GS_RCV_TDS_UNION
 结构说明  : INT_TYPE_GS_RCV_TDS 寄存器结构定义。地址偏移量:0x0548，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_type_gs_rcv_tds_reg;
    struct
    {
        unsigned int  o_int_type_gs_rcv_tds : 16; /* bit[0-15] : 中断状态标志0，1，2只有当TDS处于主模时才能产生。
                                                                 
                                                                 [0]: 中断类型0。 TDS（主模）提前通知GS异系统测量启动中断。
                                                                 [1]: 中断类型1。 TDS（主模）进GAP中断，通知GS进行异系统测量射频通道配置，天线切换等操作。
                                                                 [2]: 中断类型2。 TDS（主模）出GAP中断。
                                                                 [3]: 中断类型3。TDS（从模）测量结束中断。
                                                                 [4]: 中断类型4。TDS（主模）强制GS退出异系统测量中断。
                                                                 [5]: 中断类型5。TDS（主模）通知GS上报本次测量结果。
                                                                 [6]: 中断类型6。保留。
                                                                 [15:7]: 对应中断类型[15:7]，预留。
                                                                 软件读取该中断状态上报寄存器后，需要和0x08A4的int_mask_gs_rcv_tds相与，再判断是否需要处理。 */
        unsigned int  reserved              : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_TYPE_GS_RCV_TDS_UNION;
#define BBPCOMM_INT_TYPE_GS_RCV_TDS_o_int_type_gs_rcv_tds_START  (0)
#define BBPCOMM_INT_TYPE_GS_RCV_TDS_o_int_type_gs_rcv_tds_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_TYPE_GS_RCV_GM_UNION
 结构说明  : INT_TYPE_GS_RCV_GM 寄存器结构定义。地址偏移量:0x054C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_type_gs_rcv_gm_reg;
    struct
    {
        unsigned int  o_int_type_gs_rcv_gm : 16; /* bit[0-15] : 中断状态标志。各bit单独对应一种中断类型，高有效。
                                                                [0]: 中断类型0。GM（主模）提前通知GS异系统测量启动中断。
                                                                [1]: 中断类型1。GM（主模）进GAP中断，通知GS进行异系统测量射频通道配置，天线切换等操作。
                                                                [2]: 中断类型2。GM（主模）出GAP中断。
                                                                [3]: 中断类型3。GM（从模）测量结束中断。
                                                                [4]: 中断类型4。GM（主模）强制GS退出异系统测量中断。
                                                                [5]: 中断类型5。GM（主模）通知GS上报本次测量结果。
                                                                [6]: 中断类型6。保留。
                                                                [15:7]: 对应中断类型[15:7]，预留。
                                                                中断状态标志0，1，2只有当GM处于主模时才能产生。
                                                                软件读取该中断状态上报寄存器后，需要和0x08A8的int_mask_gs_rcv_gm相与，再判断是否需要处理。 */
        unsigned int  reserved             : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_TYPE_GS_RCV_GM_UNION;
#define BBPCOMM_INT_TYPE_GS_RCV_GM_o_int_type_gs_rcv_gm_START  (0)
#define BBPCOMM_INT_TYPE_GS_RCV_GM_o_int_type_gs_rcv_gm_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_TYPE_GS_RCV_GS_UNION
 结构说明  : INT_TYPE_GS_RCV_GS 寄存器结构定义。地址偏移量:0x0550，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_type_gs_rcv_gs_reg;
    struct
    {
        unsigned int  o_int_type_gs_rcv_gs : 16; /* bit[0-15] : [0]: 中断类型0。GS（主模）提前通知GS异系统测量启动中断。
                                                                [1]: 中断类型1。GS（主模）进GAP中断，通知GS进行异系统测量射频通道配置，天线切换等操作。
                                                                [2]: 中断类型2。GS（主模）出GAP中断。
                                                                [3]: 中断类型3。GS（从模）测量结束中断。
                                                                [4]: 中断类型4。GS（主模）强制GS退出异系统测量中断。
                                                                [5]: 中断类型5。GS（主模）通知GS上报本次测量结果。
                                                                [6]: 中断类型6。保留。
                                                                [15:7]: 对应中断类型[15:7]，预留。
                                                                中断状态标志0，1，2只有当TDS处于主模时才能产生。
                                                                软件读取该中断状态上报寄存器后，需要和0x08AC的int_mask_gs_rcv_gs相与，再判断是否需要处理。 */
        unsigned int  reserved             : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_TYPE_GS_RCV_GS_UNION;
#define BBPCOMM_INT_TYPE_GS_RCV_GS_o_int_type_gs_rcv_gs_START  (0)
#define BBPCOMM_INT_TYPE_GS_RCV_GS_o_int_type_gs_rcv_gs_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_TYPE_GS_RCV_W_UNION
 结构说明  : INT_TYPE_GS_RCV_W 寄存器结构定义。地址偏移量:0x0554，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_type_gs_rcv_w_reg;
    struct
    {
        unsigned int  o_int_type_gs_rcv_w : 16; /* bit[0-15] : 中断状态标志。各bit单独对应一种中断类型，高有效。
                                                               [0]: 中断类型0。W（主模）提前通知GS异频测量启动中断。
                                                               [1]: 中断类型1。W（主模）进GAP中断，通知GS进行异频测量射频通道配置，天线切换等操作。
                                                               [2]: 中断类型2。W（主模）出GAP中断。
                                                               [3]: 中断类型3。W（从模，即异频）测量结束中断。
                                                               [4]: 中断类型4。W（主模）强制GS退出异频测量中断。
                                                               [5]: 中断类型5。W（主模）通知GS上报本次测量结果。
                                                               [6]: 中断类型6。保留。
                                                               [15:7]: 对应中断类型[15:7]，预留。
                                                               中断状态标志0，1，2只有当W处于主模时才能产生。
                                                               软件读取该中断状态上报寄存器后，需要和0x08B0的int_mask_gs_rcv_w相与，再判断是否需要处理。 */
        unsigned int  reserved            : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_TYPE_GS_RCV_W_UNION;
#define BBPCOMM_INT_TYPE_GS_RCV_W_o_int_type_gs_rcv_w_START  (0)
#define BBPCOMM_INT_TYPE_GS_RCV_W_o_int_type_gs_rcv_w_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_TYPE_GS_INT012_UNION
 结构说明  : INT_TYPE_GS_INT012 寄存器结构定义。地址偏移量:0x0558，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_type_gs_int012_reg;
    struct
    {
        unsigned int  o_int_type_gs_int012 : 3;  /* bit[0-2] : 主模产生int0、1、2的上报（(包括异频、异系统场景)），高有效。
                                                               [0]: GS主模时，CTU告诉通知GSDSP产生int0中断。
                                                               [1]: GS主模时，CTU告诉通知GSDSP产生int1中断。
                                                               [2]: GS主模时，CTU告诉通知GSDSP产生int2中断。
                                                               软件读取该中断状态上报寄存器后，需要和0x08B4的int_mask_gs_int012相与，再判断是否需要处理。 */
        unsigned int  reserved             : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_INT_TYPE_GS_INT012_UNION;
#define BBPCOMM_INT_TYPE_GS_INT012_o_int_type_gs_int012_START  (0)
#define BBPCOMM_INT_TYPE_GS_INT012_o_int_type_gs_int012_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_GS_SND_LTE_INT_13_UNION
 结构说明  : GS_SND_LTE_INT_13 寄存器结构定义。地址偏移量:0x055C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      gs_snd_lte_int_13_reg;
    struct
    {
        unsigned int  reserved_0        : 3;  /* bit[0-2]  : 保留 */
        unsigned int  gs_snd_lte_int_13 : 13; /* bit[3-15] : 逻辑自清零。高有效。
                                                             
                                                             bit15~7：对应gs_snd_lte_int_15 ~ 7。
                                                             GS DSP通过此寄存器触发类型15~7中断（int_type_lte_rcv_gs[15:7]）给LTEDSP。
                                                             生效时刻：立即生效
                                                             
                                                             bit6：对应gs_snd_lte_int_6。
                                                             GSDSP通过此寄存器触发类型6中断（int_type_lte_rcv_gs[6]）给LTEDSP。
                                                             生效时刻：立即生效
                                                             
                                                             bit5：对应gs_snd_lte_int_5。
                                                             GS主模时通知LTEDSP LTE测量周期到达，高有效。
                                                             GS DSP通过此寄存器触发类型5中断（int_type_lte_rcv_gs[5]）给LTEDSP。
                                                             生效时刻：立即生效
                                                             
                                                             bit4：对应gs_snd_lte_int_4。
                                                             GS主模时强制退出异系统测量指示。高有效。
                                                             GS DSP通过此寄存器触发类型4中断（int_type_lte_rcv_gs[4]）给LTEDSP。
                                                             生效时刻：立即生效
                                                             
                                                             bit3：对应gs_snd_lte_int_3。GS测量结束指示，高有效。
                                                             用于触发中断类型3 （int_type_lte_rcv_gs[3]）给LTEDSP。LTE主模下对GS进行异系统测量时，如果GS测量结束，GS DSP配置此标志为1。 
                                                             生效时刻：立即生效 */
        unsigned int  reserved_1        : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_GS_SND_LTE_INT_13_UNION;
#define BBPCOMM_GS_SND_LTE_INT_13_gs_snd_lte_int_13_START  (3)
#define BBPCOMM_GS_SND_LTE_INT_13_gs_snd_lte_int_13_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_GS_SND_TDS_INT_13_UNION
 结构说明  : GS_SND_TDS_INT_13 寄存器结构定义。地址偏移量:0x0560，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      gs_snd_tds_int_13_reg;
    struct
    {
        unsigned int  reserved_0        : 3;  /* bit[0-2]  : 保留 */
        unsigned int  gs_snd_tds_int_13 : 13; /* bit[3-15] : 逻辑自清零。高有效。
                                                             
                                                             bit15~7：对应gs_snd_tds_int_15 ~ 7。
                                                             GS DSP通过此寄存器触发类型15~7中断（int_type_tds_rcv_gs[15:7]）给TDSDSP。
                                                             生效时刻：立即生效
                                                             
                                                             bit6：对应gs_snd_tds_int_6。
                                                             GSDSP通过此寄存器触发类型6中断（int_type_tds_rcv_gs[6]）给TDSDSP。
                                                             生效时刻：立即生效
                                                             
                                                             bit5：对应gs_snd_tds_int_5。
                                                             GS主模时通知TDSDSP TDS测量周期到达，高有效。
                                                             GS DSP通过此寄存器触发类型5中断（int_type_tds_rcv_gs[5]）给TDSDSP。
                                                             生效时刻：立即生效
                                                             
                                                             bit4：对应gs_snd_tds_int_4。
                                                             GS主模时强制退出异系统测量指示。高有效。
                                                             GS DSP通过此寄存器触发类型4中断（int_type_tds_rcv_gs[4]）给TDSDSP。
                                                             生效时刻：立即生效
                                                             
                                                             bit3：对应gs_snd_tds_int_3。GS测量结束指示，高有效。
                                                             用于触发中断类型3 （int_type_tds_rcv_gs[3]）给TDSDSP。TDS主模下对GS进行异系统测量时，如果GS测量结束，GS DSP配置此标志为1。 
                                                             生效时刻：立即生效 */
        unsigned int  reserved_1        : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_GS_SND_TDS_INT_13_UNION;
#define BBPCOMM_GS_SND_TDS_INT_13_gs_snd_tds_int_13_START  (3)
#define BBPCOMM_GS_SND_TDS_INT_13_gs_snd_tds_int_13_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_GS_SND_GM_INT_13_UNION
 结构说明  : GS_SND_GM_INT_13 寄存器结构定义。地址偏移量:0x0564，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      gs_snd_gm_int_13_reg;
    struct
    {
        unsigned int  reserved_0       : 3;  /* bit[0-2]  : 保留 */
        unsigned int  gs_snd_gm_int_13 : 13; /* bit[3-15] : 逻辑自清零。高有效。
                                                            
                                                            bit15~7：对应gs_snd_gm_int_15 ~ 7。
                                                            GS DSP通过此寄存器触发类型15~7中断（int_type_gm_rcv_gs[15:7]）给GMDSP。
                                                            生效时刻：立即生效
                                                            
                                                            bit6：对应gs_snd_gm_int_6。
                                                            GSDSP通过此寄存器触发类型6中断（int_type_gm_rcv_gs[6]）给GMDSP。
                                                            生效时刻：立即生效
                                                            
                                                            bit5：对应gs_snd_gm_int_5。
                                                            GS主模时通知GMDSP GM测量周期到达，高有效。
                                                            GS DSP通过此寄存器触发类型5中断（int_type_gm_rcv_gs[5]）给GMDSP。
                                                            生效时刻：立即生效
                                                            
                                                            bit4：对应gs_snd_gm_int_4。
                                                            GS主模时强制退出异系统测量指示。高有效。
                                                            GS DSP通过此寄存器触发类型4中断（int_type_gm_rcv_gs[4]）给GMDSP。
                                                            生效时刻：立即生效
                                                            
                                                            bit3：对应gs_snd_gm_int_3。GS测量结束指示，高有效。
                                                            用于触发中断类型3 （int_type_gm_rcv_gs[3]）给GMDSP。GM主模下对GS进行异系统测量时，如果GS测量结束，GS DSP配置此标志为1。 
                                                            生效时刻：立即生效 */
        unsigned int  reserved_1       : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_GS_SND_GM_INT_13_UNION;
#define BBPCOMM_GS_SND_GM_INT_13_gs_snd_gm_int_13_START  (3)
#define BBPCOMM_GS_SND_GM_INT_13_gs_snd_gm_int_13_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_GS_SND_GS_INT_13_UNION
 结构说明  : GS_SND_GS_INT_13 寄存器结构定义。地址偏移量:0x0568，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      gs_snd_gs_int_13_reg;
    struct
    {
        unsigned int  reserved_0       : 3;  /* bit[0-2]  : 保留 */
        unsigned int  gs_snd_gs_int_13 : 13; /* bit[3-15] : 逻辑自清零。高有效。
                                                            
                                                            bit15~7：对应gs_snd_gs_int_15 ~ 7。
                                                            GS DSP通过此寄存器触发类型15~7中断（int_type_gs_rcv_gs[15:7]）给GSDSP。
                                                            生效时刻：立即生效
                                                            
                                                            bit6：对应gs_snd_gs_int_6。
                                                            GSDSP通过此寄存器触发类型6中断（int_type_gs_rcv_gs[6]）给GSDSP。
                                                            生效时刻：立即生效
                                                            
                                                            bit5：对应gs_snd_gs_int_5。
                                                            GS主模时通知GSDSP GS测量周期到达，高有效。
                                                            GS DSP通过此寄存器触发类型5中断（int_type_gs_rcv_gs[5]）给GSDSP。
                                                            生效时刻：立即生效
                                                            
                                                            bit4：对应gs_snd_gs_int_4。
                                                            GS主模时强制退出异系统测量指示。高有效。
                                                            GS DSP通过此寄存器触发类型4中断（int_type_gs_rcv_gs[4]）给GSDSP。
                                                            生效时刻：立即生效
                                                            
                                                            bit3：对应gs_snd_gs_int_3。GS测量结束指示，高有效。
                                                            用于触发中断类型3 （int_type_gs_rcv_gs[3]）给GSDSP。GS主模下对GS进行异系统测量时，如果GS测量结束，GS DSP配置此标志为1。 
                                                            生效时刻：立即生效 */
        unsigned int  reserved_1       : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_GS_SND_GS_INT_13_UNION;
#define BBPCOMM_GS_SND_GS_INT_13_gs_snd_gs_int_13_START  (3)
#define BBPCOMM_GS_SND_GS_INT_13_gs_snd_gs_int_13_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_GS_SND_W_INT_13_UNION
 结构说明  : GS_SND_W_INT_13 寄存器结构定义。地址偏移量:0x056C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      gs_snd_w_int_13_reg;
    struct
    {
        unsigned int  reserved_0      : 3;  /* bit[0-2]  : 保留 */
        unsigned int  gs_snd_w_int_13 : 13; /* bit[3-15] : 逻辑自清零。高有效。
                                                           
                                                           bit15~7：对应gs_snd_w_int_15 ~ 7。
                                                           GS DSP通过此寄存器触发类型15~7中断（int_type_w_rcv_gs[15:7]）给WDSP。
                                                           生效时刻：立即生效
                                                           
                                                           bit6：对应gs_snd_w_int_6。
                                                           GSDSP通过此寄存器触发类型6中断（int_type_w_rcv_gs[6]）给WDSP。
                                                           生效时刻：立即生效
                                                           
                                                           bit5：对应gs_snd_w_int_5。
                                                           GS主模时通知WDSP W测量周期到达，高有效。
                                                           GS DSP通过此寄存器触发类型5中断（int_type_w_rcv_gs[5]）给WDSP。
                                                           生效时刻：立即生效
                                                           
                                                           bit4：对应gs_snd_w_int_4。
                                                           GS主模时强制退出异系统测量指示。高有效。
                                                           GS DSP通过此寄存器触发类型4中断（int_type_w_rcv_gs[4]）给WDSP。
                                                           生效时刻：立即生效
                                                           
                                                           bit3：对应gs_snd_w_int_3。GS测量结束指示，高有效。
                                                           用于触发中断类型3 （int_type_w_rcv_gs[3]）给WDSP。W主模下对GS进行异系统测量时，如果GS测量结束，GS DSP配置此标志为1。 
                                                           生效时刻：立即生效 */
        unsigned int  reserved_1      : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_GS_SND_W_INT_13_UNION;
#define BBPCOMM_GS_SND_W_INT_13_gs_snd_w_int_13_START  (3)
#define BBPCOMM_GS_SND_W_INT_13_gs_snd_w_int_13_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_S_C_CH_NUM_IND_UNION
 结构说明  : S_C_CH_NUM_IND 寄存器结构定义。地址偏移量:0x0580，初值:0x00000000，宽度:32
 寄存器说明: GS为从模时对应通道的指示寄存器
*****************************************************************************/
typedef union
{
    unsigned int      s_c_ch_num_ind_reg;
    struct
    {
        unsigned int  s_c_ch_num_ind     : 2;  /* bit[0-1] : C2为从模时对应的通道选择信号。
                                                             0：选择通道0；
                                                             1：选择通道1；
                                                             2：选择通道2；
                                                             3：选择通道3。
                                                             配置时刻：各模根据通信场景配置 */
        unsigned int  reserved_0         : 2;  /* bit[2-3] : 保留 */
        unsigned int  s_c_ch_num_ind_sel : 1;  /* bit[4-4] : C2为从模时对应的通道选择信号生效方式。
                                                             0：在int1生效；
                                                             1：立即生效。 */
        unsigned int  reserved_1         : 27; /* bit[5-31]: 保留 */
    } reg;
} BBPCOMM_S_C_CH_NUM_IND_UNION;
#define BBPCOMM_S_C_CH_NUM_IND_s_c_ch_num_ind_START      (0)
#define BBPCOMM_S_C_CH_NUM_IND_s_c_ch_num_ind_END        (1)
#define BBPCOMM_S_C_CH_NUM_IND_s_c_ch_num_ind_sel_START  (4)
#define BBPCOMM_S_C_CH_NUM_IND_s_c_ch_num_ind_sel_END    (4)


/*****************************************************************************
 结构名    : BBPCOMM_C_INTERSYS_MEASURE_TYPE_UNION
 结构说明  : C_INTERSYS_MEASURE_TYPE 寄存器结构定义。地址偏移量:0x0584，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c_intersys_measure_type_reg;
    struct
    {
        unsigned int  c_intersys_measure_type : 4;  /* bit[0-3] : 异系统测量类型。
                                                                  4’b0：测量C2。
                                                                  4’b1: C2背景搜；
                                                                  其它预留。
                                                                  生效时刻：立即生效 */
        unsigned int  reserved                : 28; /* bit[4-31]: 保留 */
    } reg;
} BBPCOMM_C_INTERSYS_MEASURE_TYPE_UNION;
#define BBPCOMM_C_INTERSYS_MEASURE_TYPE_c_intersys_measure_type_START  (0)
#define BBPCOMM_C_INTERSYS_MEASURE_TYPE_c_intersys_measure_type_END    (3)


/*****************************************************************************
 结构名    : BBPCOMM_C_MEASURE_REPORT_VALID_UNION
 结构说明  : C_MEASURE_REPORT_VALID 寄存器结构定义。地址偏移量:0x0588，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c_measure_report_valid_reg;
    struct
    {
        unsigned int  c_measure_report_valid : 1;  /* bit[0-0] : 单频点测量周期到指示，L或者TDS/Gm/Gs/U作为主模，通知C2PHY W测量的单频点周期到达。
                                                                 只在连接态下需要配置。
                                                                 电平信号，高有效。
                                                                 生效时刻：立即生效 */
        unsigned int  reserved               : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_C_MEASURE_REPORT_VALID_UNION;
#define BBPCOMM_C_MEASURE_REPORT_VALID_c_measure_report_valid_START  (0)
#define BBPCOMM_C_MEASURE_REPORT_VALID_c_measure_report_valid_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_INT_CLEAR_LTE_RCV_C_UNION
 结构说明  : INT_CLEAR_LTE_RCV_C 寄存器结构定义。地址偏移量:0x0594，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_lte_rcv_c_reg;
    struct
    {
        unsigned int  int_clear_lte_rcv_c : 16; /* bit[0-15] : 逻辑自清零。
                                                               中断标志清除指示，高有效。用于清除INT_TYPE_LTE_RCV_C[15:0]对应bit位
                                                               生效时刻：立即生效 */
        unsigned int  reserved            : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_CLEAR_LTE_RCV_C_UNION;
#define BBPCOMM_INT_CLEAR_LTE_RCV_C_int_clear_lte_rcv_c_START  (0)
#define BBPCOMM_INT_CLEAR_LTE_RCV_C_int_clear_lte_rcv_c_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_MASK_LTE_RCV_C_UNION
 结构说明  : INT_MASK_LTE_RCV_C 寄存器结构定义。地址偏移量:0x0598，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_lte_rcv_c_reg;
    struct
    {
        unsigned int  int_mask_lte_rcv_c : 16; /* bit[0-15] : 中断屏蔽标志。用于屏蔽INT_TYPE_LTE_RCV_C[15:0]对应bit中断。
                                                              0：屏蔽中断上报；
                                                              1：使能中断上报。
                                                              配置时刻：初始化
                                                              生效时刻：立即生效 */
        unsigned int  reserved           : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_MASK_LTE_RCV_C_UNION;
#define BBPCOMM_INT_MASK_LTE_RCV_C_int_mask_lte_rcv_c_START  (0)
#define BBPCOMM_INT_MASK_LTE_RCV_C_int_mask_lte_rcv_c_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_TYPE_LTE_RCV_C_UNION
 结构说明  : INT_TYPE_LTE_RCV_C 寄存器结构定义。地址偏移量:0x059C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_type_lte_rcv_c_reg;
    struct
    {
        unsigned int  o_int_type_lte_rcv_c : 16; /* bit[0-15] : 中断状态标志。各bit单独对应一种中断类型，高有效。
                                                                [0]: 中断类型0。 C2（主模）提前通知LTE异系统测量启动中断。
                                                                [1]: 中断类型1。 C2（主模）进GAP中断，通知LTE进行异系统测量射频通道配置，天线切换等操作。
                                                                [2]: 中断类型2。C2（主模）出GAP中断。
                                                                [3]: 中断类型3。C2（从模）测量结束中断。
                                                                [4]: 中断类型4。C2（主模）强制C2退出异系统测量中断。
                                                                [5]: 中断类型5。C2（主模）通知C2上报本次测量结果。
                                                                [6]: 保留。
                                                                [15:7]: 对应中断类型[15:7]，预留。
                                                                软件读取该中断状态上报寄存器后，需要和0x0A84的int_mask_lte_rcv_c相与，再判断是否需要处理。 */
        unsigned int  reserved             : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_TYPE_LTE_RCV_C_UNION;
#define BBPCOMM_INT_TYPE_LTE_RCV_C_o_int_type_lte_rcv_c_START  (0)
#define BBPCOMM_INT_TYPE_LTE_RCV_C_o_int_type_lte_rcv_c_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_LTE_SND_C_INT_13_UNION
 结构说明  : LTE_SND_C_INT_13 寄存器结构定义。地址偏移量:0x05A0，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      lte_snd_c_int_13_reg;
    struct
    {
        unsigned int  reserved_0       : 3;  /* bit[0-2]  : 保留 */
        unsigned int  lte_snd_c_int_13 : 13; /* bit[3-15] : 逻辑自清零。高有效。
                                                            
                                                            bit15~7：对应lte_snd_c_int_15 ~ 7。
                                                            LPHY通过此寄存器触发类型15~7中断（int_type_c_rcv_lte[15:7]）给C2PHY。
                                                            生效时刻：立即生效
                                                            
                                                            bit6：对应lte_snd_c_int_6。
                                                            LPHY通过此寄存器触发类型6中断（int_type_lte_rcv_c[6]）给LPHY。
                                                            生效时刻：立即生效
                                                            
                                                            bit5：对应c_snd_lte_int_5。
                                                            L主模时通知LPHY L测量周期到达，高有效。
                                                            LPHY通过此寄存器触发类型5中断（int_type_c_rcv_lte[5]）给LPHY。
                                                            生效时刻：立即生效
                                                            
                                                            bit4：对应lte_snd_c_int_4。
                                                            L主模时强制退出异系统测量指示。高有效。
                                                            LPHY通过此寄存器触发类型4中断（int_type_c_rcv_lte[4]）给C2PHY。
                                                            生效时刻：立即生效
                                                            
                                                            bit3：对应lte_snd_c_int_3。L测量结束指示，高有效。
                                                            用于触发中断类型3 （int_type_c_rcv_lte[3]）给C2PHY。C2主模下对L进行异系统测量时，如果L测量结束，LPHY配置此标志为1。 
                                                            生效时刻：立即生效 */
        unsigned int  reserved_1       : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_LTE_SND_C_INT_13_UNION;
#define BBPCOMM_LTE_SND_C_INT_13_lte_snd_c_int_13_START  (3)
#define BBPCOMM_LTE_SND_C_INT_13_lte_snd_c_int_13_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_C_SND_C_INT_13_UNION
 结构说明  : C_SND_C_INT_13 寄存器结构定义。地址偏移量:0x05A4，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c_snd_c_int_13_reg;
    struct
    {
        unsigned int  reserved_0     : 3;  /* bit[0-2]  : 保留 */
        unsigned int  c_snd_c_int_13 : 13; /* bit[3-15] : 逻辑自清零。高有效。
                                                          
                                                          bit15~7：对应c_snd_c_int_15 ~ 7。
                                                          C2 DSP通过此寄存器触发类型15~7中断（int_type_c_rcv_c[15:7]）给C2 DSP。
                                                          生效时刻：立即生效
                                                          
                                                          bit6：对应c_snd_c_int_6。
                                                          C2DSP通过此寄存器触发类型6中断（int_type_c_rcv_c[6]）给C2DSP。
                                                          生效时刻：立即生效
                                                          
                                                          bit5：对应c_snd_c_int_5。
                                                          C2主模时通知C2DSP C2测量周期到达，高有效。
                                                          C2 DSP通过此寄存器触发类型5中断（int_type_c_rcv_c[5]）给C2DSP。
                                                          生效时刻：立即生效
                                                          
                                                          bit4：对应c_snd_c_int_4。
                                                          C2主模时强制退出异系统测量指示。高有效。
                                                          C2 DSP通过此寄存器触发类型4中断（int_type_c_rcv_c[4]）给C2DSP。
                                                          生效时刻：立即生效
                                                          
                                                          bit3：对应c_snd_c_int_3。C2测量结束指示，高有效。
                                                          用于触发中断类型3 （int_type_c_rcv_c[3]）给C2DSP。C2主模下对C2进行异系统测量时，如果C2测量结束，C2 DSP配置此标志为1。 
                                                          生效时刻：立即生效 */
        unsigned int  reserved_1     : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_C_SND_C_INT_13_UNION;
#define BBPCOMM_C_SND_C_INT_13_c_snd_c_int_13_START  (3)
#define BBPCOMM_C_SND_C_INT_13_c_snd_c_int_13_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_CLEAR_C_RCV_LTE_UNION
 结构说明  : INT_CLEAR_C_RCV_LTE 寄存器结构定义。地址偏移量:0x05B0，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_c_rcv_lte_reg;
    struct
    {
        unsigned int  int_clear_c_rcv_lte : 16; /* bit[0-15] : 逻辑自清零。
                                                               中断标志清除指示，高有效。用于清除INT_TYPE_C_RCV_LTE[15:0]对应bit位
                                                               生效时刻：立即生效 */
        unsigned int  reserved            : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_CLEAR_C_RCV_LTE_UNION;
#define BBPCOMM_INT_CLEAR_C_RCV_LTE_int_clear_c_rcv_lte_START  (0)
#define BBPCOMM_INT_CLEAR_C_RCV_LTE_int_clear_c_rcv_lte_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_CLEAR_C_RCV_C_UNION
 结构说明  : INT_CLEAR_C_RCV_C 寄存器结构定义。地址偏移量:0x05B4，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_c_rcv_c_reg;
    struct
    {
        unsigned int  int_clear_c_rcv_c : 16; /* bit[0-15] : 逻辑自清零。
                                                             中断标志清除指示，高有效。用于清除INT_TYPE_C_RCV_C[15:0]对应bit位
                                                             生效时刻：立即生效 */
        unsigned int  reserved          : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_CLEAR_C_RCV_C_UNION;
#define BBPCOMM_INT_CLEAR_C_RCV_C_int_clear_c_rcv_c_START  (0)
#define BBPCOMM_INT_CLEAR_C_RCV_C_int_clear_c_rcv_c_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_CLEAR_C_INT012_UNION
 结构说明  : INT_CLEAR_C_INT012 寄存器结构定义。地址偏移量:0x05B8，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_clear_c_int012_reg;
    struct
    {
        unsigned int  int_clear_c_int012 : 3;  /* bit[0-2] : 逻辑自清零。
                                                             中断标志清除指示，高有效。用于清除INT_TYPE_C_INT012[2:0]对应bit位
                                                             生效时刻：立即生效 */
        unsigned int  reserved           : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_INT_CLEAR_C_INT012_UNION;
#define BBPCOMM_INT_CLEAR_C_INT012_int_clear_c_int012_START  (0)
#define BBPCOMM_INT_CLEAR_C_INT012_int_clear_c_int012_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_INT_MASK_C_RCV_LTE_UNION
 结构说明  : INT_MASK_C_RCV_LTE 寄存器结构定义。地址偏移量:0x05BC，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_c_rcv_lte_reg;
    struct
    {
        unsigned int  int_mask_c_rcv_lte : 16; /* bit[0-15] : 中断屏蔽标志。用于屏蔽INT_TYPE_C_RCV_LTE[15:0]对应bit中断。
                                                              0：屏蔽中断上报；
                                                              1：使能中断上报。
                                                              配置时刻：初始化
                                                              生效时刻：立即生效 */
        unsigned int  reserved           : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_MASK_C_RCV_LTE_UNION;
#define BBPCOMM_INT_MASK_C_RCV_LTE_int_mask_c_rcv_lte_START  (0)
#define BBPCOMM_INT_MASK_C_RCV_LTE_int_mask_c_rcv_lte_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_MASK_C_RCV_C_UNION
 结构说明  : INT_MASK_C_RCV_C 寄存器结构定义。地址偏移量:0x05C0，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_c_rcv_c_reg;
    struct
    {
        unsigned int  int_mask_c_rcv_c : 16; /* bit[0-15] : 中断屏蔽标志。用于屏蔽INT_TYPE_C_RCV_C[15:0]对应bit中断。
                                                            0：屏蔽中断上报；
                                                            1：使能中断上报。
                                                            配置时刻：初始化
                                                            生效时刻：立即生效 */
        unsigned int  reserved         : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_MASK_C_RCV_C_UNION;
#define BBPCOMM_INT_MASK_C_RCV_C_int_mask_c_rcv_c_START  (0)
#define BBPCOMM_INT_MASK_C_RCV_C_int_mask_c_rcv_c_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_MASK_C_INT012_UNION
 结构说明  : INT_MASK_C_INT012 寄存器结构定义。地址偏移量:0x05C4，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_mask_c_int012_reg;
    struct
    {
        unsigned int  int_mask_c_int012 : 3;  /* bit[0-2] : 中断屏蔽标志。用于屏蔽INT_TYPE_C_INT012[2:0]对应bit中断。
                                                            0：屏蔽中断上报；
                                                            1：使能中断上报。
                                                            配置时刻：初始化
                                                            生效时刻：立即生效 */
        unsigned int  reserved          : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_INT_MASK_C_INT012_UNION;
#define BBPCOMM_INT_MASK_C_INT012_int_mask_c_int012_START  (0)
#define BBPCOMM_INT_MASK_C_INT012_int_mask_c_int012_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_INT_TYPE_C_RCV_LTE_UNION
 结构说明  : INT_TYPE_C_RCV_LTE 寄存器结构定义。地址偏移量:0x05C8，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_type_c_rcv_lte_reg;
    struct
    {
        unsigned int  o_int_type_c_rcv_lte : 16; /* bit[0-15] : 中断状态标志。各bit单独对应一种中断类型，高有效。
                                                                [0]: 中断类型0。 LTE（主模）提前通知C2异系统测量启动中断。
                                                                [1]: 中断类型1。 LTE（主模）进GAP中断，通知C2进行异系统测量射频通道配置，天线切换等操作。
                                                                [2]: 中断类型2。 LTE（主模）出GAP中断。
                                                                [3]: 中断类型3。LTE（从模）测量结束中断。
                                                                [4]: 中断类型4。LTE（主模）强制C2退出异系统测量中断。
                                                                [5]: 中断类型5。LTE（主模）通知C2上报本次测量结果。
                                                                [6]: 保留。
                                                                [15:7]: 对应中断类型[15:7]，预留。
                                                                软件读取该中断状态上报寄存器后，需要和0x0B34的int_mask_c_rcv_lte相与，再判断是否需要处理。 */
        unsigned int  reserved             : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_TYPE_C_RCV_LTE_UNION;
#define BBPCOMM_INT_TYPE_C_RCV_LTE_o_int_type_c_rcv_lte_START  (0)
#define BBPCOMM_INT_TYPE_C_RCV_LTE_o_int_type_c_rcv_lte_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_TYPE_C_RCV_C_UNION
 结构说明  : INT_TYPE_C_RCV_C 寄存器结构定义。地址偏移量:0x05CC，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_type_c_rcv_c_reg;
    struct
    {
        unsigned int  o_int_type_c_rcv_c : 16; /* bit[0-15] : 中断状态标志。各bit单独对应一种中断类型，高有效。
                                                              [0]: 中断类型0。C2（主模）提前通知LTE异频测量启动中断。
                                                              [1]: 中断类型1。C2（主模）进GAP中断，通知C2进行异频测量射频通道配置，天线切换等操作。
                                                              [2]: 中断类型2。C2（主模）出GAP中断。
                                                              [3]: 中断类型3。C2（从模，即异频）测量结束中断。
                                                              [4]: 中断类型4。C2（主模）强制C2退出异频测量中断。
                                                              [5]: 中断类型5。C2（主模）通知C2上报本次测量结果。
                                                              [6]: 中断类型6。保留。
                                                              [15:7]: 对应中断类型[15:7]，预留。
                                                              中断状态标志0，1，2只有当LTE处于主模时才能产生。
                                                              软件读取该中断状态上报寄存器后，需要和0x0B38的int_mask_c_rcv_c相与，再判断是否需要处理。 */
        unsigned int  reserved           : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_INT_TYPE_C_RCV_C_UNION;
#define BBPCOMM_INT_TYPE_C_RCV_C_o_int_type_c_rcv_c_START  (0)
#define BBPCOMM_INT_TYPE_C_RCV_C_o_int_type_c_rcv_c_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_INT_TYPE_C_INT012_UNION
 结构说明  : INT_TYPE_C_INT012 寄存器结构定义。地址偏移量:0x05D0，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int_type_c_int012_reg;
    struct
    {
        unsigned int  o_int_type_c_int012 : 3;  /* bit[0-2] : 增加主模产生int0、1、2的上报（(包括异频、异系统场景)），高有效。
                                                              [0]: C2主模时，C2TU告诉通知C2PHY产生int0中断。
                                                              [1]: C2主模时，C2TU告诉通知C2PHY产生int1中断。
                                                              [2]:C2W主模时，C2TU告诉通知C2PHY产生int2中断。
                                                              软件读取该中断状态上报寄存器后，需要和0x0704的int_mask_c_int012相与，再判断是否需要处理。 */
        unsigned int  reserved            : 29; /* bit[3-31]: 保留 */
    } reg;
} BBPCOMM_INT_TYPE_C_INT012_UNION;
#define BBPCOMM_INT_TYPE_C_INT012_o_int_type_c_int012_START  (0)
#define BBPCOMM_INT_TYPE_C_INT012_o_int_type_c_int012_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_C_SND_LTE_INT_13_UNION
 结构说明  : C_SND_LTE_INT_13 寄存器结构定义。地址偏移量:0x05D4，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c_snd_lte_int_13_reg;
    struct
    {
        unsigned int  reserved_0       : 3;  /* bit[0-2]  : 保留 */
        unsigned int  c_snd_lte_int_13 : 13; /* bit[3-15] : 逻辑自清零。高有效。
                                                            
                                                            bit15~7：对应c_snd_lte_int_15 ~ 7。
                                                            C2PHY通过此寄存器触发类型15~7中断（int_type_lte_rcv_c[15:7]）给LPHY。
                                                            生效时刻：立即生效
                                                            
                                                            bit6：对应c_snd_lte_int_6。
                                                            C2PHY通过此寄存器触发类型6中断（int_type_lte_rcv_c[6]）给LPHY。
                                                            生效时刻：立即生效
                                                            
                                                            bit5：对应c_snd_lte_int_5。
                                                            C2主模时通知C2PHY L测量周期到达，高有效。
                                                            C2PHY通过此寄存器触发类型5中断（int_type_lte_rcv_c[5]）给C2PHY。
                                                            生效时刻：立即生效
                                                            
                                                            bit4：对应c_snd_lte_int_4。
                                                            C2主模时强制退出异系统测量指示。高有效。
                                                            C2PHY通过此寄存器触发类型4中断（int_type_lte_rcv_c[4]）给LPHY。
                                                            生效时刻：立即生效
                                                            
                                                            bit3：对应c_snd_lte_int_3。C2测量结束指示，高有效。
                                                            用于触发中断类型3 （int_type_lte_rcv_c[3]）给LPHY。L主模下对C2进行异系统测量时，如果C2测量结束，C2PHY配置此标志为1。 
                                                            生效时刻：立即生效 */
        unsigned int  reserved_1       : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_C_SND_LTE_INT_13_UNION;
#define BBPCOMM_C_SND_LTE_INT_13_c_snd_lte_int_13_START  (3)
#define BBPCOMM_C_SND_LTE_INT_13_c_snd_lte_int_13_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_TDS_C_CTU_INT_SEL_UNION
 结构说明  : TDS_C_CTU_INT_SEL 寄存器结构定义。地址偏移量:0x05D8，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      tds_c_ctu_int_sel_reg;
    struct
    {
        unsigned int  tds_c_ctu_int_sel : 1;  /* bit[0]   : 1'b0：TDS CTU中断输出至物理层；
                                                            1'b1：C CTU中断输出至物理层。 */
        unsigned int  reserved          : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_TDS_C_CTU_INT_SEL_UNION;
#define BBPCOMM_TDS_C_CTU_INT_SEL_tds_c_ctu_int_sel_START  (0)
#define BBPCOMM_TDS_C_CTU_INT_SEL_tds_c_ctu_int_sel_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_DBG_CLK_GATE_EN_UNION
 结构说明  : DBG_CLK_GATE_EN 寄存器结构定义。地址偏移量:0x0700，初值:0x00000000，宽度:32
 寄存器说明: 门控时钟配置寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dbg_clk_gate_en_reg;
    struct
    {
        unsigned int  dsp_dbg_clk_gate_en : 1;  /* bit[0-0] : bbp_comm_dbg模块门控时钟使能信号：
                                                              1：直接使用输入时钟，未进行门控；
                                                              0：输入时钟无效，此时进行低功耗状态。 */
        unsigned int  dsp_dbg_clk_bypass  : 1;  /* bit[1-1] : bbp_comm_dbg模块时钟bypass配置信号：
                                                              1：直接使用输入时钟，不进行门控处理，此时dsp_dbg_clk_gate_en配置无效；
                                                              0：表示根据dsp_dbg_clk_gate_en进行门控处理。 */
        unsigned int  reserved            : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_DBG_CLK_GATE_EN_UNION;
#define BBPCOMM_DBG_CLK_GATE_EN_dsp_dbg_clk_gate_en_START  (0)
#define BBPCOMM_DBG_CLK_GATE_EN_dsp_dbg_clk_gate_en_END    (0)
#define BBPCOMM_DBG_CLK_GATE_EN_dsp_dbg_clk_bypass_START   (1)
#define BBPCOMM_DBG_CLK_GATE_EN_dsp_dbg_clk_bypass_END     (1)


/*****************************************************************************
 结构名    : BBPCOMM_DBG_COMM_EN_UNION
 结构说明  : DBG_COMM_EN 寄存器结构定义。地址偏移量:0x0704，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dbg_comm_en_reg;
    struct
    {
        unsigned int  dbg_comm_en : 1;  /* bit[0-0] : bbp_comm_dbg使能信号：
                                                      1：使能；
                                                      0：不使能。 */
        unsigned int  reserved    : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_DBG_COMM_EN_UNION;
#define BBPCOMM_DBG_COMM_EN_dbg_comm_en_START  (0)
#define BBPCOMM_DBG_COMM_EN_dbg_comm_en_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_DBG_EN_UNION
 结构说明  : DBG_EN 寄存器结构定义。地址偏移量:0x0708，初值:0x00000002，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dbg_en_reg;
    struct
    {
        unsigned int  dbg_en       : 1;  /* bit[0]    : 可维可测使能信号，当dbg_rpt_mode为0时逻辑自清，否则需要写清。
                                                        1'b0：可维可测功能不使能                             1'b1：可维可测功能使能 */
        unsigned int  dbg_rpt_mode : 1;  /* bit[1]    : 可维可测数据上报模式：
                                                        'b0：触发后继续采样dbg_pkg_num个数据包后自动结束；
                                                        'b1：只要dbg_en为1就上报，没有上报个数限制。 */
        unsigned int  reserved     : 14; /* bit[2-15] : 保留 */
        unsigned int  dbg_pkg_num  : 16; /* bit[16-31]: 可维可测的包个数 */
    } reg;
} BBPCOMM_DBG_EN_UNION;
#define BBPCOMM_DBG_EN_dbg_en_START        (0)
#define BBPCOMM_DBG_EN_dbg_en_END          (0)
#define BBPCOMM_DBG_EN_dbg_rpt_mode_START  (1)
#define BBPCOMM_DBG_EN_dbg_rpt_mode_END    (1)
#define BBPCOMM_DBG_EN_dbg_pkg_num_START   (16)
#define BBPCOMM_DBG_EN_dbg_pkg_num_END     (31)


/*****************************************************************************
 结构名    : BBPCOMM_DBG_FLT_UNION
 结构说明  : DBG_FLT 寄存器结构定义。地址偏移量:0x0710，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dbg_flt_reg;
    struct
    {
        unsigned int  dbg_flt  : 16; /* bit[0-15] : 可维可测内部分组指示：
                                                    1：上报mipi数据
                                                    2：上报ssi数据
                                                    3：其它dbg上报数据
                                                    其它：保留 */
        unsigned int  reserved : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_DBG_FLT_UNION;
#define BBPCOMM_DBG_FLT_dbg_flt_START   (0)
#define BBPCOMM_DBG_FLT_dbg_flt_END     (15)


/*****************************************************************************
 结构名    : BBPCOMM_DBG_MIPI_CH_MASK_UNION
 结构说明  : DBG_MIPI_CH_MASK 寄存器结构定义。地址偏移量:0x0714，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dbg_mipi_ch_mask_reg;
    struct
    {
        unsigned int  dbg_mipi_ch_mask : 4;  /* bit[0-3] : 可维可测mipi采集数据通道屏蔽指示：
                                                           dbg_mipi_ch_mask[X],X=0~3,则：
                                                           0：通道X的mipi数据不采集
                                                           1：采集通道X的mipi数据 */
        unsigned int  reserved         : 28; /* bit[4-31]: 保留 */
    } reg;
} BBPCOMM_DBG_MIPI_CH_MASK_UNION;
#define BBPCOMM_DBG_MIPI_CH_MASK_dbg_mipi_ch_mask_START  (0)
#define BBPCOMM_DBG_MIPI_CH_MASK_dbg_mipi_ch_mask_END    (3)


/*****************************************************************************
 结构名    : BBPCOMM_DBG_SSI_CH_MASK_UNION
 结构说明  : DBG_SSI_CH_MASK 寄存器结构定义。地址偏移量:0x0718，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dbg_ssi_ch_mask_reg;
    struct
    {
        unsigned int  dbg_ssi_ch_mask : 4;  /* bit[0-3] : 可维可测ssi采集数据通道屏蔽指示：
                                                          dbg_ssi_ch_mask[X],X=0~3,则：
                                                          0：通道X的ssi数据不采集
                                                          1：采集通道X的ssi数据 */
        unsigned int  reserved        : 28; /* bit[4-31]: 保留 */
    } reg;
} BBPCOMM_DBG_SSI_CH_MASK_UNION;
#define BBPCOMM_DBG_SSI_CH_MASK_dbg_ssi_ch_mask_START  (0)
#define BBPCOMM_DBG_SSI_CH_MASK_dbg_ssi_ch_mask_END    (3)


/*****************************************************************************
 结构名    : BBPCOMM_RD_END_FLAG_MIPI0_SOFT_UNION
 结构说明  : RD_END_FLAG_MIPI0_SOFT 寄存器结构定义。地址偏移量:0x0788，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      rd_end_flag_mipi0_soft_reg;
    struct
    {
        unsigned int  rd_end_flag_mipi0_soft : 1;  /* bit[0]   : 由软件直接控制MIPI0 master,不借助xbbp发送回读指令时,回读数据有效指示 */
        unsigned int  reserved               : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_RD_END_FLAG_MIPI0_SOFT_UNION;
#define BBPCOMM_RD_END_FLAG_MIPI0_SOFT_rd_end_flag_mipi0_soft_START  (0)
#define BBPCOMM_RD_END_FLAG_MIPI0_SOFT_rd_end_flag_mipi0_soft_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_MIPI0_GRANT_DSP_UNION
 结构说明  : MIPI0_GRANT_DSP 寄存器结构定义。地址偏移量:0x078C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      mipi0_grant_dsp_reg;
    struct
    {
        unsigned int  mipi0_grant_dsp : 1;  /* bit[0]   : 由软件直接控制MIPI0 master
                                                          1:软件可以发送CFG_IND启动mipi0
                                                          0:软件等待mipi0授权使用 */
        unsigned int  reserved        : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_MIPI0_GRANT_DSP_UNION;
#define BBPCOMM_MIPI0_GRANT_DSP_mipi0_grant_dsp_START  (0)
#define BBPCOMM_MIPI0_GRANT_DSP_mipi0_grant_dsp_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_DSP_MIPI0_EN_IMI_UNION
 结构说明  : DSP_MIPI0_EN_IMI 寄存器结构定义。地址偏移量:0x0798，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dsp_mipi0_en_imi_reg;
    struct
    {
        unsigned int  dsp_mipi0_en_imi : 1;  /* bit[0]   : 由软件直接控制MIPI0 master,需首先拉高此指示,屏蔽xbbp对MIPI0的控制 */
        unsigned int  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_DSP_MIPI0_EN_IMI_UNION;
#define BBPCOMM_DSP_MIPI0_EN_IMI_dsp_mipi0_en_imi_START  (0)
#define BBPCOMM_DSP_MIPI0_EN_IMI_dsp_mipi0_en_imi_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_DSP_MIPI0_CFG_IND_IMI_UNION
 结构说明  : DSP_MIPI0_CFG_IND_IMI 寄存器结构定义。地址偏移量:0x079C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dsp_mipi0_cfg_ind_imi_reg;
    struct
    {
        unsigned int  dsp_mipi0_cfg_ind_imi : 1;  /* bit[0]   : 由软件直接控制MIPI0 master,拉高此dsp_mipi0_en后,产生软件启动脉冲 */
        unsigned int  reserved              : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_DSP_MIPI0_CFG_IND_IMI_UNION;
#define BBPCOMM_DSP_MIPI0_CFG_IND_IMI_dsp_mipi0_cfg_ind_imi_START  (0)
#define BBPCOMM_DSP_MIPI0_CFG_IND_IMI_dsp_mipi0_cfg_ind_imi_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_DSP_MIPI0_RD_CLR_UNION
 结构说明  : DSP_MIPI0_RD_CLR 寄存器结构定义。地址偏移量:0x07A0，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dsp_mipi0_rd_clr_reg;
    struct
    {
        unsigned int  dsp_mipi0_rd_clr : 1;  /* bit[0]   : 由软件直接控制MIPI0 master,取走回读数据后,清标志位脉冲 */
        unsigned int  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_DSP_MIPI0_RD_CLR_UNION;
#define BBPCOMM_DSP_MIPI0_RD_CLR_dsp_mipi0_rd_clr_START  (0)
#define BBPCOMM_DSP_MIPI0_RD_CLR_dsp_mipi0_rd_clr_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_CPU_MIPI0_FUNC_SEL_UNION
 结构说明  : CPU_MIPI0_FUNC_SEL 寄存器结构定义。地址偏移量:0x07A4，初值:0x00000001，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      cpu_mipi0_func_sel_reg;
    struct
    {
        unsigned int  cpu_mipi0_func_sel : 1;  /* bit[0]   : cpu配置mipi功能,配置为1才能正常工作, 测试时配置为0 */
        unsigned int  reserved           : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_CPU_MIPI0_FUNC_SEL_UNION;
#define BBPCOMM_CPU_MIPI0_FUNC_SEL_cpu_mipi0_func_sel_START  (0)
#define BBPCOMM_CPU_MIPI0_FUNC_SEL_cpu_mipi0_func_sel_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_CPU_MIPI0_TEST_FUNC_UNION
 结构说明  : CPU_MIPI0_TEST_FUNC 寄存器结构定义。地址偏移量:0x07A8，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      cpu_mipi0_test_func_reg;
    struct
    {
        unsigned int  cpu_mipi0_test_func : 1;  /* bit[0]   : cpu配置mipi功能,测试用 */
        unsigned int  reserved            : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_CPU_MIPI0_TEST_FUNC_UNION;
#define BBPCOMM_CPU_MIPI0_TEST_FUNC_cpu_mipi0_test_func_START  (0)
#define BBPCOMM_CPU_MIPI0_TEST_FUNC_cpu_mipi0_test_func_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_CPU_MIPI0_SCLK_TEST_UNION
 结构说明  : CPU_MIPI0_SCLK_TEST 寄存器结构定义。地址偏移量:0x07AC，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      cpu_mipi0_sclk_test_reg;
    struct
    {
        unsigned int  cpu_mipi0_sclk_test : 1;  /* bit[0]   : cpu配置mipi功能, 测试用 */
        unsigned int  reserved            : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_CPU_MIPI0_SCLK_TEST_UNION;
#define BBPCOMM_CPU_MIPI0_SCLK_TEST_cpu_mipi0_sclk_test_START  (0)
#define BBPCOMM_CPU_MIPI0_SCLK_TEST_cpu_mipi0_sclk_test_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_CPU_MIPI0_SDATA_TEST_UNION
 结构说明  : CPU_MIPI0_SDATA_TEST 寄存器结构定义。地址偏移量:0x07B0，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      cpu_mipi0_sdata_test_reg;
    struct
    {
        unsigned int  cpu_mipi0_sdata_test : 1;  /* bit[0]   : cpu配置mipi功能, 测试用 */
        unsigned int  reserved             : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_CPU_MIPI0_SDATA_TEST_UNION;
#define BBPCOMM_CPU_MIPI0_SDATA_TEST_cpu_mipi0_sdata_test_START  (0)
#define BBPCOMM_CPU_MIPI0_SDATA_TEST_cpu_mipi0_sdata_test_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_CPU_MIPI0_CLR_IND_IMI_UNION
 结构说明  : CPU_MIPI0_CLR_IND_IMI 寄存器结构定义。地址偏移量:0x07B4，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      cpu_mipi0_clr_ind_imi_reg;
    struct
    {
        unsigned int  cpu_mipi0_clr_ind_imi : 1;  /* bit[0]   : cpu配置mipi功能,mipi0master清异常信号 */
        unsigned int  reserved              : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_CPU_MIPI0_CLR_IND_IMI_UNION;
#define BBPCOMM_CPU_MIPI0_CLR_IND_IMI_cpu_mipi0_clr_ind_imi_START  (0)
#define BBPCOMM_CPU_MIPI0_CLR_IND_IMI_cpu_mipi0_clr_ind_imi_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_RD_END_FLAG_MIPI1_SOFT_UNION
 结构说明  : RD_END_FLAG_MIPI1_SOFT 寄存器结构定义。地址偏移量:0x07C8，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      rd_end_flag_mipi1_soft_reg;
    struct
    {
        unsigned int  rd_end_flag_mipi1_soft : 1;  /* bit[0]   : 由软件直接控制MIPI1 master,不借助xbbp发送回读指令时,回读数据有效指示 */
        unsigned int  reserved               : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_RD_END_FLAG_MIPI1_SOFT_UNION;
#define BBPCOMM_RD_END_FLAG_MIPI1_SOFT_rd_end_flag_mipi1_soft_START  (0)
#define BBPCOMM_RD_END_FLAG_MIPI1_SOFT_rd_end_flag_mipi1_soft_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_MIPI1_GRANT_DSP_UNION
 结构说明  : MIPI1_GRANT_DSP 寄存器结构定义。地址偏移量:0x07CC，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      mipi1_grant_dsp_reg;
    struct
    {
        unsigned int  mipi1_grant_dsp : 1;  /* bit[0]   : 由软件直接控制MIPI1 master
                                                          1:软件可以发送CFG_IND启动mipi1
                                                          0:软件等待mipi1授权使用 */
        unsigned int  reserved        : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_MIPI1_GRANT_DSP_UNION;
#define BBPCOMM_MIPI1_GRANT_DSP_mipi1_grant_dsp_START  (0)
#define BBPCOMM_MIPI1_GRANT_DSP_mipi1_grant_dsp_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_DSP_MIPI1_EN_IMI_UNION
 结构说明  : DSP_MIPI1_EN_IMI 寄存器结构定义。地址偏移量:0x07D8，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dsp_mipi1_en_imi_reg;
    struct
    {
        unsigned int  dsp_mipi1_en_imi : 1;  /* bit[0]   : 由软件直接控制MIPI1 master,需首先拉高此指示,屏蔽xbbp对MIPI1的控制 */
        unsigned int  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_DSP_MIPI1_EN_IMI_UNION;
#define BBPCOMM_DSP_MIPI1_EN_IMI_dsp_mipi1_en_imi_START  (0)
#define BBPCOMM_DSP_MIPI1_EN_IMI_dsp_mipi1_en_imi_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_DSP_MIPI1_CFG_IND_IMI_UNION
 结构说明  : DSP_MIPI1_CFG_IND_IMI 寄存器结构定义。地址偏移量:0x07DC，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dsp_mipi1_cfg_ind_imi_reg;
    struct
    {
        unsigned int  dsp_mipi1_cfg_ind_imi : 1;  /* bit[0]   : 由软件直接控制MIPI1 master,拉高此dsp_mipi1_en后,产生软件启动脉冲 */
        unsigned int  reserved              : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_DSP_MIPI1_CFG_IND_IMI_UNION;
#define BBPCOMM_DSP_MIPI1_CFG_IND_IMI_dsp_mipi1_cfg_ind_imi_START  (0)
#define BBPCOMM_DSP_MIPI1_CFG_IND_IMI_dsp_mipi1_cfg_ind_imi_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_DSP_MIPI1_RD_CLR_UNION
 结构说明  : DSP_MIPI1_RD_CLR 寄存器结构定义。地址偏移量:0x07E0，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dsp_mipi1_rd_clr_reg;
    struct
    {
        unsigned int  dsp_mipi1_rd_clr : 1;  /* bit[0]   : 由软件直接控制MIPI1 master,取走回读数据后,清标志位脉冲 */
        unsigned int  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_DSP_MIPI1_RD_CLR_UNION;
#define BBPCOMM_DSP_MIPI1_RD_CLR_dsp_mipi1_rd_clr_START  (0)
#define BBPCOMM_DSP_MIPI1_RD_CLR_dsp_mipi1_rd_clr_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_CPU_MIPI1_FUNC_SEL_UNION
 结构说明  : CPU_MIPI1_FUNC_SEL 寄存器结构定义。地址偏移量:0x07E4，初值:0x00000001，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      cpu_mipi1_func_sel_reg;
    struct
    {
        unsigned int  cpu_mipi1_func_sel : 1;  /* bit[0]   : cpu配置mipi功能,配置为1才能正常工作, 测试时配置为0 */
        unsigned int  reserved           : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_CPU_MIPI1_FUNC_SEL_UNION;
#define BBPCOMM_CPU_MIPI1_FUNC_SEL_cpu_mipi1_func_sel_START  (0)
#define BBPCOMM_CPU_MIPI1_FUNC_SEL_cpu_mipi1_func_sel_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_CPU_MIPI1_TEST_FUNC_UNION
 结构说明  : CPU_MIPI1_TEST_FUNC 寄存器结构定义。地址偏移量:0x07E8，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      cpu_mipi1_test_func_reg;
    struct
    {
        unsigned int  cpu_mipi1_test_func : 1;  /* bit[0]   : cpu配置mipi功能,测试用 */
        unsigned int  reserved            : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_CPU_MIPI1_TEST_FUNC_UNION;
#define BBPCOMM_CPU_MIPI1_TEST_FUNC_cpu_mipi1_test_func_START  (0)
#define BBPCOMM_CPU_MIPI1_TEST_FUNC_cpu_mipi1_test_func_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_CPU_MIPI1_SCLK_TEST_UNION
 结构说明  : CPU_MIPI1_SCLK_TEST 寄存器结构定义。地址偏移量:0x07EC，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      cpu_mipi1_sclk_test_reg;
    struct
    {
        unsigned int  cpu_mipi1_sclk_test : 1;  /* bit[0]   : cpu配置mipi功能,测试用 */
        unsigned int  reserved            : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_CPU_MIPI1_SCLK_TEST_UNION;
#define BBPCOMM_CPU_MIPI1_SCLK_TEST_cpu_mipi1_sclk_test_START  (0)
#define BBPCOMM_CPU_MIPI1_SCLK_TEST_cpu_mipi1_sclk_test_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_CPU_MIPI1_SDATA_TEST_UNION
 结构说明  : CPU_MIPI1_SDATA_TEST 寄存器结构定义。地址偏移量:0x07F0，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      cpu_mipi1_sdata_test_reg;
    struct
    {
        unsigned int  cpu_mipi1_sdata_test : 1;  /* bit[0]   : cpu配置mipi功能,测试用 */
        unsigned int  reserved             : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_CPU_MIPI1_SDATA_TEST_UNION;
#define BBPCOMM_CPU_MIPI1_SDATA_TEST_cpu_mipi1_sdata_test_START  (0)
#define BBPCOMM_CPU_MIPI1_SDATA_TEST_cpu_mipi1_sdata_test_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_CPU_MIPI1_CLR_IND_IMI_UNION
 结构说明  : CPU_MIPI1_CLR_IND_IMI 寄存器结构定义。地址偏移量:0x07F4，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      cpu_mipi1_clr_ind_imi_reg;
    struct
    {
        unsigned int  cpu_mipi1_clr_ind_imi : 1;  /* bit[0]   : cpu配置mipi功能,mipi1master清异常信号 */
        unsigned int  reserved              : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_CPU_MIPI1_CLR_IND_IMI_UNION;
#define BBPCOMM_CPU_MIPI1_CLR_IND_IMI_cpu_mipi1_clr_ind_imi_START  (0)
#define BBPCOMM_CPU_MIPI1_CLR_IND_IMI_cpu_mipi1_clr_ind_imi_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_RD_END_FLAG_MIPI2_SOFT_UNION
 结构说明  : RD_END_FLAG_MIPI2_SOFT 寄存器结构定义。地址偏移量:0x0808，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      rd_end_flag_mipi2_soft_reg;
    struct
    {
        unsigned int  rd_end_flag_mipi2_soft : 1;  /* bit[0]   : 由软件直接控制MIPI2 master,不借助xbbp发送回读指令时,回读数据有效指示 */
        unsigned int  reserved               : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_RD_END_FLAG_MIPI2_SOFT_UNION;
#define BBPCOMM_RD_END_FLAG_MIPI2_SOFT_rd_end_flag_mipi2_soft_START  (0)
#define BBPCOMM_RD_END_FLAG_MIPI2_SOFT_rd_end_flag_mipi2_soft_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_MIPI2_GRANT_DSP_UNION
 结构说明  : MIPI2_GRANT_DSP 寄存器结构定义。地址偏移量:0x080C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      mipi2_grant_dsp_reg;
    struct
    {
        unsigned int  mipi2_grant_dsp : 1;  /* bit[0]   : 由软件直接控制MIPI2 master
                                                          1:软件可以发送CFG_IND启动mipi0
                                                          0:软件等待mipi2授权使用 */
        unsigned int  reserved        : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_MIPI2_GRANT_DSP_UNION;
#define BBPCOMM_MIPI2_GRANT_DSP_mipi2_grant_dsp_START  (0)
#define BBPCOMM_MIPI2_GRANT_DSP_mipi2_grant_dsp_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_DSP_MIPI2_EN_IMI_UNION
 结构说明  : DSP_MIPI2_EN_IMI 寄存器结构定义。地址偏移量:0x0818，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dsp_mipi2_en_imi_reg;
    struct
    {
        unsigned int  dsp_mipi2_en_imi : 1;  /* bit[0]   : 由软件直接控制MIPI2 master,需首先拉高此指示,屏蔽xbbp对MIPI0的控制 */
        unsigned int  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_DSP_MIPI2_EN_IMI_UNION;
#define BBPCOMM_DSP_MIPI2_EN_IMI_dsp_mipi2_en_imi_START  (0)
#define BBPCOMM_DSP_MIPI2_EN_IMI_dsp_mipi2_en_imi_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_DSP_MIPI2_CFG_IND_IMI_UNION
 结构说明  : DSP_MIPI2_CFG_IND_IMI 寄存器结构定义。地址偏移量:0x081C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dsp_mipi2_cfg_ind_imi_reg;
    struct
    {
        unsigned int  dsp_mipi2_cfg_ind_imi : 1;  /* bit[0]   : 由软件直接控制MIPI2 master,拉高此dsp_mipi0_en后,产生软件启动脉冲 */
        unsigned int  reserved              : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_DSP_MIPI2_CFG_IND_IMI_UNION;
#define BBPCOMM_DSP_MIPI2_CFG_IND_IMI_dsp_mipi2_cfg_ind_imi_START  (0)
#define BBPCOMM_DSP_MIPI2_CFG_IND_IMI_dsp_mipi2_cfg_ind_imi_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_DSP_MIPI2_RD_CLR_UNION
 结构说明  : DSP_MIPI2_RD_CLR 寄存器结构定义。地址偏移量:0x0820，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dsp_mipi2_rd_clr_reg;
    struct
    {
        unsigned int  dsp_mipi2_rd_clr : 1;  /* bit[0]   : 由软件直接控制MIPI2 master,取走回读数据后,清标志位脉冲 */
        unsigned int  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_DSP_MIPI2_RD_CLR_UNION;
#define BBPCOMM_DSP_MIPI2_RD_CLR_dsp_mipi2_rd_clr_START  (0)
#define BBPCOMM_DSP_MIPI2_RD_CLR_dsp_mipi2_rd_clr_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_CPU_MIPI2_FUNC_SEL_UNION
 结构说明  : CPU_MIPI2_FUNC_SEL 寄存器结构定义。地址偏移量:0x0824，初值:0x00000001，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      cpu_mipi2_func_sel_reg;
    struct
    {
        unsigned int  cpu_mipi2_func_sel : 1;  /* bit[0]   : cpu配置mipi功能,配置为1才能正常工作, 测试时配置为0 */
        unsigned int  reserved           : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_CPU_MIPI2_FUNC_SEL_UNION;
#define BBPCOMM_CPU_MIPI2_FUNC_SEL_cpu_mipi2_func_sel_START  (0)
#define BBPCOMM_CPU_MIPI2_FUNC_SEL_cpu_mipi2_func_sel_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_CPU_MIPI2_TEST_FUNC_UNION
 结构说明  : CPU_MIPI2_TEST_FUNC 寄存器结构定义。地址偏移量:0x0828，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      cpu_mipi2_test_func_reg;
    struct
    {
        unsigned int  cpu_mipi2_test_func : 1;  /* bit[0]   : cpu配置mipi功能,测试用 */
        unsigned int  reserved            : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_CPU_MIPI2_TEST_FUNC_UNION;
#define BBPCOMM_CPU_MIPI2_TEST_FUNC_cpu_mipi2_test_func_START  (0)
#define BBPCOMM_CPU_MIPI2_TEST_FUNC_cpu_mipi2_test_func_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_CPU_MIPI2_SCLK_TEST_UNION
 结构说明  : CPU_MIPI2_SCLK_TEST 寄存器结构定义。地址偏移量:0x082C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      cpu_mipi2_sclk_test_reg;
    struct
    {
        unsigned int  cpu_mipi2_sclk_test : 1;  /* bit[0]   : cpu配置mipi功能, 测试用 */
        unsigned int  reserved            : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_CPU_MIPI2_SCLK_TEST_UNION;
#define BBPCOMM_CPU_MIPI2_SCLK_TEST_cpu_mipi2_sclk_test_START  (0)
#define BBPCOMM_CPU_MIPI2_SCLK_TEST_cpu_mipi2_sclk_test_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_CPU_MIPI2_SDATA_TEST_UNION
 结构说明  : CPU_MIPI2_SDATA_TEST 寄存器结构定义。地址偏移量:0x0830，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      cpu_mipi2_sdata_test_reg;
    struct
    {
        unsigned int  cpu_mipi2_sdata_test : 1;  /* bit[0]   : cpu配置mipi功能, 测试用 */
        unsigned int  reserved             : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_CPU_MIPI2_SDATA_TEST_UNION;
#define BBPCOMM_CPU_MIPI2_SDATA_TEST_cpu_mipi2_sdata_test_START  (0)
#define BBPCOMM_CPU_MIPI2_SDATA_TEST_cpu_mipi2_sdata_test_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_CPU_MIPI2_CLR_IND_IMI_UNION
 结构说明  : CPU_MIPI2_CLR_IND_IMI 寄存器结构定义。地址偏移量:0x0834，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      cpu_mipi2_clr_ind_imi_reg;
    struct
    {
        unsigned int  cpu_mipi2_clr_ind_imi : 1;  /* bit[0]   : cpu配置mipi功能,mipi2master清异常信号 */
        unsigned int  reserved              : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_CPU_MIPI2_CLR_IND_IMI_UNION;
#define BBPCOMM_CPU_MIPI2_CLR_IND_IMI_cpu_mipi2_clr_ind_imi_START  (0)
#define BBPCOMM_CPU_MIPI2_CLR_IND_IMI_cpu_mipi2_clr_ind_imi_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_RD_END_FLAG_MIPI3_SOFT_UNION
 结构说明  : RD_END_FLAG_MIPI3_SOFT 寄存器结构定义。地址偏移量:0x0848，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      rd_end_flag_mipi3_soft_reg;
    struct
    {
        unsigned int  rd_end_flag_mipi3_soft : 1;  /* bit[0]   : 由软件直接控制MIPI3 master,不借助xbbp发送回读指令时,回读数据有效指示 */
        unsigned int  reserved               : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_RD_END_FLAG_MIPI3_SOFT_UNION;
#define BBPCOMM_RD_END_FLAG_MIPI3_SOFT_rd_end_flag_mipi3_soft_START  (0)
#define BBPCOMM_RD_END_FLAG_MIPI3_SOFT_rd_end_flag_mipi3_soft_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_MIPI3_GRANT_DSP_UNION
 结构说明  : MIPI3_GRANT_DSP 寄存器结构定义。地址偏移量:0x084C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      mipi3_grant_dsp_reg;
    struct
    {
        unsigned int  mipi3_grant_dsp : 1;  /* bit[0]   : 由软件直接控制MIPI3 master
                                                          1:软件可以发送CFG_IND启动mipi3
                                                          0:软件等待mipi3授权使用 */
        unsigned int  reserved        : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_MIPI3_GRANT_DSP_UNION;
#define BBPCOMM_MIPI3_GRANT_DSP_mipi3_grant_dsp_START  (0)
#define BBPCOMM_MIPI3_GRANT_DSP_mipi3_grant_dsp_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_DSP_MIPI3_EN_IMI_UNION
 结构说明  : DSP_MIPI3_EN_IMI 寄存器结构定义。地址偏移量:0x0858，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dsp_mipi3_en_imi_reg;
    struct
    {
        unsigned int  dsp_mipi3_en_imi : 1;  /* bit[0]   : 由软件直接控制MIPI3 master,需首先拉高此指示,屏蔽xbbp对MIPI3的控制 */
        unsigned int  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_DSP_MIPI3_EN_IMI_UNION;
#define BBPCOMM_DSP_MIPI3_EN_IMI_dsp_mipi3_en_imi_START  (0)
#define BBPCOMM_DSP_MIPI3_EN_IMI_dsp_mipi3_en_imi_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_DSP_MIPI3_CFG_IND_IMI_UNION
 结构说明  : DSP_MIPI3_CFG_IND_IMI 寄存器结构定义。地址偏移量:0x085C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dsp_mipi3_cfg_ind_imi_reg;
    struct
    {
        unsigned int  dsp_mipi3_cfg_ind_imi : 1;  /* bit[0]   : 由软件直接控制MIPI3 master,拉高此dsp_mipi3_en后,产生软件启动脉冲 */
        unsigned int  reserved              : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_DSP_MIPI3_CFG_IND_IMI_UNION;
#define BBPCOMM_DSP_MIPI3_CFG_IND_IMI_dsp_mipi3_cfg_ind_imi_START  (0)
#define BBPCOMM_DSP_MIPI3_CFG_IND_IMI_dsp_mipi3_cfg_ind_imi_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_DSP_MIPI3_RD_CLR_UNION
 结构说明  : DSP_MIPI3_RD_CLR 寄存器结构定义。地址偏移量:0x0860，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dsp_mipi3_rd_clr_reg;
    struct
    {
        unsigned int  dsp_mipi3_rd_clr : 1;  /* bit[0]   : 由软件直接控制MIPI3 master,取走回读数据后,清标志位脉冲 */
        unsigned int  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_DSP_MIPI3_RD_CLR_UNION;
#define BBPCOMM_DSP_MIPI3_RD_CLR_dsp_mipi3_rd_clr_START  (0)
#define BBPCOMM_DSP_MIPI3_RD_CLR_dsp_mipi3_rd_clr_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_CPU_MIPI3_FUNC_SEL_UNION
 结构说明  : CPU_MIPI3_FUNC_SEL 寄存器结构定义。地址偏移量:0x0864，初值:0x00000001，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      cpu_mipi3_func_sel_reg;
    struct
    {
        unsigned int  cpu_mipi3_func_sel : 1;  /* bit[0]   : cpu配置mipi功能,配置为1才能正常工作, 测试时配置为0 */
        unsigned int  reserved           : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_CPU_MIPI3_FUNC_SEL_UNION;
#define BBPCOMM_CPU_MIPI3_FUNC_SEL_cpu_mipi3_func_sel_START  (0)
#define BBPCOMM_CPU_MIPI3_FUNC_SEL_cpu_mipi3_func_sel_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_CPU_MIPI3_TEST_FUNC_UNION
 结构说明  : CPU_MIPI3_TEST_FUNC 寄存器结构定义。地址偏移量:0x0868，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      cpu_mipi3_test_func_reg;
    struct
    {
        unsigned int  cpu_mipi3_test_func : 1;  /* bit[0]   : cpu配置mipi功能,测试用 */
        unsigned int  reserved            : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_CPU_MIPI3_TEST_FUNC_UNION;
#define BBPCOMM_CPU_MIPI3_TEST_FUNC_cpu_mipi3_test_func_START  (0)
#define BBPCOMM_CPU_MIPI3_TEST_FUNC_cpu_mipi3_test_func_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_CPU_MIPI3_SCLK_TEST_UNION
 结构说明  : CPU_MIPI3_SCLK_TEST 寄存器结构定义。地址偏移量:0x086C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      cpu_mipi3_sclk_test_reg;
    struct
    {
        unsigned int  cpu_mipi3_sclk_test : 1;  /* bit[0]   : cpu配置mipi功能, 测试用 */
        unsigned int  reserved            : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_CPU_MIPI3_SCLK_TEST_UNION;
#define BBPCOMM_CPU_MIPI3_SCLK_TEST_cpu_mipi3_sclk_test_START  (0)
#define BBPCOMM_CPU_MIPI3_SCLK_TEST_cpu_mipi3_sclk_test_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_CPU_MIPI3_SDATA_TEST_UNION
 结构说明  : CPU_MIPI3_SDATA_TEST 寄存器结构定义。地址偏移量:0x0870，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      cpu_mipi3_sdata_test_reg;
    struct
    {
        unsigned int  cpu_mipi3_sdata_test : 1;  /* bit[0]   : cpu配置mipi功能, 测试用 */
        unsigned int  reserved             : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_CPU_MIPI3_SDATA_TEST_UNION;
#define BBPCOMM_CPU_MIPI3_SDATA_TEST_cpu_mipi3_sdata_test_START  (0)
#define BBPCOMM_CPU_MIPI3_SDATA_TEST_cpu_mipi3_sdata_test_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_CPU_MIPI3_CLR_IND_IMI_UNION
 结构说明  : CPU_MIPI3_CLR_IND_IMI 寄存器结构定义。地址偏移量:0x0874，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      cpu_mipi3_clr_ind_imi_reg;
    struct
    {
        unsigned int  cpu_mipi3_clr_ind_imi : 1;  /* bit[0]   : cpu配置mipi功能,mipi3master清异常信号 */
        unsigned int  reserved              : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_CPU_MIPI3_CLR_IND_IMI_UNION;
#define BBPCOMM_CPU_MIPI3_CLR_IND_IMI_cpu_mipi3_clr_ind_imi_START  (0)
#define BBPCOMM_CPU_MIPI3_CLR_IND_IMI_cpu_mipi3_clr_ind_imi_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_GM_MIPI_RD_OVERTIME_FLAG_DSP_UNION
 结构说明  : GM_MIPI_RD_OVERTIME_FLAG_DSP 寄存器结构定义。地址偏移量:0x0900，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      gm_mipi_rd_overtime_flag_dsp_reg;
    struct
    {
        unsigned int  gm_mipi_rd_overtime_flag_dsp : 1;  /* bit[0]   : DSP等待回读结果超时标志位
                                                                       1:超时   */
        unsigned int  reserved                     : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_GM_MIPI_RD_OVERTIME_FLAG_DSP_UNION;
#define BBPCOMM_GM_MIPI_RD_OVERTIME_FLAG_DSP_gm_mipi_rd_overtime_flag_dsp_START  (0)
#define BBPCOMM_GM_MIPI_RD_OVERTIME_FLAG_DSP_gm_mipi_rd_overtime_flag_dsp_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_GM_SSI_RD_OVERTIME_FLAG_DSP_UNION
 结构说明  : GM_SSI_RD_OVERTIME_FLAG_DSP 寄存器结构定义。地址偏移量:0x0904，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      gm_ssi_rd_overtime_flag_dsp_reg;
    struct
    {
        unsigned int  gm_rfic_rd_overtime_flag_dsp : 1;  /* bit[0]   : DSP等待回读结果超时标志位
                                                                       1:超时   */
        unsigned int  reserved                     : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_GM_SSI_RD_OVERTIME_FLAG_DSP_UNION;
#define BBPCOMM_GM_SSI_RD_OVERTIME_FLAG_DSP_gm_rfic_rd_overtime_flag_dsp_START  (0)
#define BBPCOMM_GM_SSI_RD_OVERTIME_FLAG_DSP_gm_rfic_rd_overtime_flag_dsp_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_GM_MIPI_RD_OVERTIME_CLR_UNION
 结构说明  : GM_MIPI_RD_OVERTIME_CLR 寄存器结构定义。地址偏移量:0x0908，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      gm_mipi_rd_overtime_clr_reg;
    struct
    {
        unsigned int  gm_mipi_rd_overtime_clr_imi : 1;  /* bit[0]   : DSP等待回读结果超时后,清抄时标志位脉冲 */
        unsigned int  reserved                    : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_GM_MIPI_RD_OVERTIME_CLR_UNION;
#define BBPCOMM_GM_MIPI_RD_OVERTIME_CLR_gm_mipi_rd_overtime_clr_imi_START  (0)
#define BBPCOMM_GM_MIPI_RD_OVERTIME_CLR_gm_mipi_rd_overtime_clr_imi_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_GM_SSI_RD_OVERTIME_CLR_UNION
 结构说明  : GM_SSI_RD_OVERTIME_CLR 寄存器结构定义。地址偏移量:0x090C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      gm_ssi_rd_overtime_clr_reg;
    struct
    {
        unsigned int  gm_rfic_rd_overtime_clr_imi : 1;  /* bit[0]   : DSP等待回读结果超时后,清抄时标志位脉冲 */
        unsigned int  reserved                    : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_GM_SSI_RD_OVERTIME_CLR_UNION;
#define BBPCOMM_GM_SSI_RD_OVERTIME_CLR_gm_rfic_rd_overtime_clr_imi_START  (0)
#define BBPCOMM_GM_SSI_RD_OVERTIME_CLR_gm_rfic_rd_overtime_clr_imi_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_RD_RESULT_FLAG_GM_RFIC_UNION
 结构说明  : RD_RESULT_FLAG_GM_RFIC 寄存器结构定义。地址偏移量:0x0950，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      rd_result_flag_gm_rfic_reg;
    struct
    {
        unsigned int  rd_result_flag_gm_rfic : 1;  /* bit[0]   : 所有回读指令执行完毕,可以取走回读数据
                                                                 1:所有回读指令发送完毕,DSP可以按位置读取SSI回读结果 */
        unsigned int  reserved               : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_RD_RESULT_FLAG_GM_RFIC_UNION;
#define BBPCOMM_RD_RESULT_FLAG_GM_RFIC_rd_result_flag_gm_rfic_START  (0)
#define BBPCOMM_RD_RESULT_FLAG_GM_RFIC_rd_result_flag_gm_rfic_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_RD_RESULT_FLAG_GM_RFIC_CLR_UNION
 结构说明  : RD_RESULT_FLAG_GM_RFIC_CLR 寄存器结构定义。地址偏移量:0x0954，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      rd_result_flag_gm_rfic_clr_reg;
    struct
    {
        unsigned int  rd_result_flag_gm_rfic_clr : 1;  /* bit[0]   : 1:DSP取走所有回读数据后,写入clr信号清标志位 */
        unsigned int  reserved                   : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_RD_RESULT_FLAG_GM_RFIC_CLR_UNION;
#define BBPCOMM_RD_RESULT_FLAG_GM_RFIC_CLR_rd_result_flag_gm_rfic_clr_START  (0)
#define BBPCOMM_RD_RESULT_FLAG_GM_RFIC_CLR_rd_result_flag_gm_rfic_clr_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_RD_RESULT_FLAG_GM_MIPI_UNION
 结构说明  : RD_RESULT_FLAG_GM_MIPI 寄存器结构定义。地址偏移量:0x0998，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      rd_result_flag_gm_mipi_reg;
    struct
    {
        unsigned int  rd_result_flag_gm_mipi : 1;  /* bit[0]   : 所有回读指令执行完毕,可以取走回读数据
                                                                 1:所有回读指令发送完毕,DSP可以按位置读取MIPI回读结果,与下述的软件直接控制MIPI标志位不同 */
        unsigned int  reserved               : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_RD_RESULT_FLAG_GM_MIPI_UNION;
#define BBPCOMM_RD_RESULT_FLAG_GM_MIPI_rd_result_flag_gm_mipi_START  (0)
#define BBPCOMM_RD_RESULT_FLAG_GM_MIPI_rd_result_flag_gm_mipi_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_RD_RESULT_FLAG_GM_MIPI_CLR_UNION
 结构说明  : RD_RESULT_FLAG_GM_MIPI_CLR 寄存器结构定义。地址偏移量:0x099C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      rd_result_flag_gm_mipi_clr_reg;
    struct
    {
        unsigned int  rd_result_flag_gm_mipi_clr : 1;  /* bit[0]   : 1:DSP取走所有回读数据后,写入clr信号清标志位,与下述的软件直接控制MIPI标志位不同 */
        unsigned int  reserved                   : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_RD_RESULT_FLAG_GM_MIPI_CLR_UNION;
#define BBPCOMM_RD_RESULT_FLAG_GM_MIPI_CLR_rd_result_flag_gm_mipi_clr_START  (0)
#define BBPCOMM_RD_RESULT_FLAG_GM_MIPI_CLR_rd_result_flag_gm_mipi_clr_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_GS_MIPI_RD_OVERTIME_FLAG_DSP_UNION
 结构说明  : GS_MIPI_RD_OVERTIME_FLAG_DSP 寄存器结构定义。地址偏移量:0x0A00，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      gs_mipi_rd_overtime_flag_dsp_reg;
    struct
    {
        unsigned int  gs_mipi_rd_overtime_flag_dsp : 1;  /* bit[0]   : DSP等待回读结果超时标志位
                                                                       1:超时   */
        unsigned int  reserved                     : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_GS_MIPI_RD_OVERTIME_FLAG_DSP_UNION;
#define BBPCOMM_GS_MIPI_RD_OVERTIME_FLAG_DSP_gs_mipi_rd_overtime_flag_dsp_START  (0)
#define BBPCOMM_GS_MIPI_RD_OVERTIME_FLAG_DSP_gs_mipi_rd_overtime_flag_dsp_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_GS_SSI_RD_OVERTIME_FLAG_DSP_UNION
 结构说明  : GS_SSI_RD_OVERTIME_FLAG_DSP 寄存器结构定义。地址偏移量:0x0A04，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      gs_ssi_rd_overtime_flag_dsp_reg;
    struct
    {
        unsigned int  gs_rfic_rd_overtime_flag_dsp : 1;  /* bit[0]   : DSP等待回读结果超时标志位
                                                                       1:超时   */
        unsigned int  reserved                     : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_GS_SSI_RD_OVERTIME_FLAG_DSP_UNION;
#define BBPCOMM_GS_SSI_RD_OVERTIME_FLAG_DSP_gs_rfic_rd_overtime_flag_dsp_START  (0)
#define BBPCOMM_GS_SSI_RD_OVERTIME_FLAG_DSP_gs_rfic_rd_overtime_flag_dsp_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_GS_MIPI_RD_OVERTIME_CLR_UNION
 结构说明  : GS_MIPI_RD_OVERTIME_CLR 寄存器结构定义。地址偏移量:0x0A08，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      gs_mipi_rd_overtime_clr_reg;
    struct
    {
        unsigned int  gs_mipi_rd_overtime_clr_imi : 1;  /* bit[0]   : DSP等待回读结果超时后,清抄时标志位脉冲 */
        unsigned int  reserved                    : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_GS_MIPI_RD_OVERTIME_CLR_UNION;
#define BBPCOMM_GS_MIPI_RD_OVERTIME_CLR_gs_mipi_rd_overtime_clr_imi_START  (0)
#define BBPCOMM_GS_MIPI_RD_OVERTIME_CLR_gs_mipi_rd_overtime_clr_imi_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_GS_SSI_RD_OVERTIME_CLR_UNION
 结构说明  : GS_SSI_RD_OVERTIME_CLR 寄存器结构定义。地址偏移量:0x0A0C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      gs_ssi_rd_overtime_clr_reg;
    struct
    {
        unsigned int  gs_rfic_rd_overtime_clr_imi : 1;  /* bit[0]   : DSP等待回读结果超时后,清抄时标志位脉冲 */
        unsigned int  reserved                    : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_GS_SSI_RD_OVERTIME_CLR_UNION;
#define BBPCOMM_GS_SSI_RD_OVERTIME_CLR_gs_rfic_rd_overtime_clr_imi_START  (0)
#define BBPCOMM_GS_SSI_RD_OVERTIME_CLR_gs_rfic_rd_overtime_clr_imi_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_RD_RESULT_FLAG_GS_RFIC_UNION
 结构说明  : RD_RESULT_FLAG_GS_RFIC 寄存器结构定义。地址偏移量:0x0A50，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      rd_result_flag_gs_rfic_reg;
    struct
    {
        unsigned int  rd_result_flag_gs_rfic : 1;  /* bit[0]   : 所有回读指令执行完毕,可以取走回读数据
                                                                 1:所有回读指令发送完毕,DSP可以按位置读取SSI回读结果 */
        unsigned int  reserved               : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_RD_RESULT_FLAG_GS_RFIC_UNION;
#define BBPCOMM_RD_RESULT_FLAG_GS_RFIC_rd_result_flag_gs_rfic_START  (0)
#define BBPCOMM_RD_RESULT_FLAG_GS_RFIC_rd_result_flag_gs_rfic_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_RD_RESULT_FLAG_GS_RFIC_CLR_UNION
 结构说明  : RD_RESULT_FLAG_GS_RFIC_CLR 寄存器结构定义。地址偏移量:0x0A54，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      rd_result_flag_gs_rfic_clr_reg;
    struct
    {
        unsigned int  rd_result_flag_gs_rfic_clr : 1;  /* bit[0]   : 1:DSP取走所有回读数据后,写入clr信号清标志位 */
        unsigned int  reserved                   : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_RD_RESULT_FLAG_GS_RFIC_CLR_UNION;
#define BBPCOMM_RD_RESULT_FLAG_GS_RFIC_CLR_rd_result_flag_gs_rfic_clr_START  (0)
#define BBPCOMM_RD_RESULT_FLAG_GS_RFIC_CLR_rd_result_flag_gs_rfic_clr_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_RD_RESULT_FLAG_GS_MIPI_UNION
 结构说明  : RD_RESULT_FLAG_GS_MIPI 寄存器结构定义。地址偏移量:0x0A98，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      rd_result_flag_gs_mipi_reg;
    struct
    {
        unsigned int  rd_result_flag_gs_mipi : 1;  /* bit[0]   : 所有回读指令执行完毕,可以取走回读数据
                                                                 1:所有回读指令发送完毕,DSP可以按位置读取MIPI回读结果,与下述的软件直接控制MIPI标志位不同 */
        unsigned int  reserved               : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_RD_RESULT_FLAG_GS_MIPI_UNION;
#define BBPCOMM_RD_RESULT_FLAG_GS_MIPI_rd_result_flag_gs_mipi_START  (0)
#define BBPCOMM_RD_RESULT_FLAG_GS_MIPI_rd_result_flag_gs_mipi_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_RD_RESULT_FLAG_GS_MIPI_CLR_UNION
 结构说明  : RD_RESULT_FLAG_GS_MIPI_CLR 寄存器结构定义。地址偏移量:0x0A9C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      rd_result_flag_gs_mipi_clr_reg;
    struct
    {
        unsigned int  rd_result_flag_gs_mipi_clr : 1;  /* bit[0]   : 1:DSP取走所有回读数据后,写入clr信号清标志位,与下述的软件直接控制MIPI标志位不同 */
        unsigned int  reserved                   : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_RD_RESULT_FLAG_GS_MIPI_CLR_UNION;
#define BBPCOMM_RD_RESULT_FLAG_GS_MIPI_CLR_rd_result_flag_gs_mipi_clr_START  (0)
#define BBPCOMM_RD_RESULT_FLAG_GS_MIPI_CLR_rd_result_flag_gs_mipi_clr_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_W_MIPI_RD_OVERTIME_FLAG_DSP_UNION
 结构说明  : W_MIPI_RD_OVERTIME_FLAG_DSP 寄存器结构定义。地址偏移量:0x0B00，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      w_mipi_rd_overtime_flag_dsp_reg;
    struct
    {
        unsigned int  w_mipi_rd_overtime_flag_dsp : 1;  /* bit[0]   : DSP等待回读结果超时标志位
                                                                      1:超时   */
        unsigned int  reserved                    : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_W_MIPI_RD_OVERTIME_FLAG_DSP_UNION;
#define BBPCOMM_W_MIPI_RD_OVERTIME_FLAG_DSP_w_mipi_rd_overtime_flag_dsp_START  (0)
#define BBPCOMM_W_MIPI_RD_OVERTIME_FLAG_DSP_w_mipi_rd_overtime_flag_dsp_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_W_SSI_RD_OVERTIME_FLAG_DSP_UNION
 结构说明  : W_SSI_RD_OVERTIME_FLAG_DSP 寄存器结构定义。地址偏移量:0x0B04，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      w_ssi_rd_overtime_flag_dsp_reg;
    struct
    {
        unsigned int  w_rfic_rd_overtime_flag_dsp : 1;  /* bit[0]   : DSP等待回读结果超时标志位
                                                                      1:超时   */
        unsigned int  reserved                    : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_W_SSI_RD_OVERTIME_FLAG_DSP_UNION;
#define BBPCOMM_W_SSI_RD_OVERTIME_FLAG_DSP_w_rfic_rd_overtime_flag_dsp_START  (0)
#define BBPCOMM_W_SSI_RD_OVERTIME_FLAG_DSP_w_rfic_rd_overtime_flag_dsp_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_W_MIPI_RD_OVERTIME_CLR_UNION
 结构说明  : W_MIPI_RD_OVERTIME_CLR 寄存器结构定义。地址偏移量:0x0B08，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      w_mipi_rd_overtime_clr_reg;
    struct
    {
        unsigned int  w_mipi_rd_overtime_clr_imi : 1;  /* bit[0]   : DSP等待回读结果超时后,清抄时标志位脉冲 */
        unsigned int  reserved                   : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_W_MIPI_RD_OVERTIME_CLR_UNION;
#define BBPCOMM_W_MIPI_RD_OVERTIME_CLR_w_mipi_rd_overtime_clr_imi_START  (0)
#define BBPCOMM_W_MIPI_RD_OVERTIME_CLR_w_mipi_rd_overtime_clr_imi_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_W_SSI_RD_OVERTIME_CLR_UNION
 结构说明  : W_SSI_RD_OVERTIME_CLR 寄存器结构定义。地址偏移量:0x0B0C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      w_ssi_rd_overtime_clr_reg;
    struct
    {
        unsigned int  w_rfic_rd_overtime_clr_imi : 1;  /* bit[0]   : DSP等待回读结果超时后,清抄时标志位脉冲 */
        unsigned int  reserved                   : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_W_SSI_RD_OVERTIME_CLR_UNION;
#define BBPCOMM_W_SSI_RD_OVERTIME_CLR_w_rfic_rd_overtime_clr_imi_START  (0)
#define BBPCOMM_W_SSI_RD_OVERTIME_CLR_w_rfic_rd_overtime_clr_imi_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_RD_RESULT_FLAG_W_RFIC_UNION
 结构说明  : RD_RESULT_FLAG_W_RFIC 寄存器结构定义。地址偏移量:0x0B50，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      rd_result_flag_w_rfic_reg;
    struct
    {
        unsigned int  rd_result_flag_w_rfic : 1;  /* bit[0]   : 所有回读指令执行完毕,可以取走回读数据
                                                                1:所有回读指令发送完毕,DSP可以按位置读取SSI回读结果 */
        unsigned int  reserved              : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_RD_RESULT_FLAG_W_RFIC_UNION;
#define BBPCOMM_RD_RESULT_FLAG_W_RFIC_rd_result_flag_w_rfic_START  (0)
#define BBPCOMM_RD_RESULT_FLAG_W_RFIC_rd_result_flag_w_rfic_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_RD_RESULT_FLAG_W_RFIC_CLR_UNION
 结构说明  : RD_RESULT_FLAG_W_RFIC_CLR 寄存器结构定义。地址偏移量:0x0B54，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      rd_result_flag_w_rfic_clr_reg;
    struct
    {
        unsigned int  rd_result_flag_w_rfic_clr : 1;  /* bit[0]   : 1:DSP取走所有回读数据后,写入clr信号清标志位 */
        unsigned int  reserved                  : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_RD_RESULT_FLAG_W_RFIC_CLR_UNION;
#define BBPCOMM_RD_RESULT_FLAG_W_RFIC_CLR_rd_result_flag_w_rfic_clr_START  (0)
#define BBPCOMM_RD_RESULT_FLAG_W_RFIC_CLR_rd_result_flag_w_rfic_clr_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_RD_RESULT_FLAG_W_MIPI_UNION
 结构说明  : RD_RESULT_FLAG_W_MIPI 寄存器结构定义。地址偏移量:0x0B98，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      rd_result_flag_w_mipi_reg;
    struct
    {
        unsigned int  rd_result_flag_w_mipi : 1;  /* bit[0]   : 所有回读指令执行完毕,可以取走回读数据
                                                                1:所有回读指令发送完毕,DSP可以按位置读取MIPI回读结果,与下述的软件直接控制MIPI标志位不同 */
        unsigned int  reserved              : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_RD_RESULT_FLAG_W_MIPI_UNION;
#define BBPCOMM_RD_RESULT_FLAG_W_MIPI_rd_result_flag_w_mipi_START  (0)
#define BBPCOMM_RD_RESULT_FLAG_W_MIPI_rd_result_flag_w_mipi_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_RD_RESULT_FLAG_W_MIPI_CLR_UNION
 结构说明  : RD_RESULT_FLAG_W_MIPI_CLR 寄存器结构定义。地址偏移量:0x0B9C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      rd_result_flag_w_mipi_clr_reg;
    struct
    {
        unsigned int  rd_result_flag_w_mipi_clr : 1;  /* bit[0]   : 1:DSP取走所有回读数据后,写入clr信号清标志位,与下述的软件直接控制MIPI标志位不同 */
        unsigned int  reserved                  : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_RD_RESULT_FLAG_W_MIPI_CLR_UNION;
#define BBPCOMM_RD_RESULT_FLAG_W_MIPI_CLR_rd_result_flag_w_mipi_clr_START  (0)
#define BBPCOMM_RD_RESULT_FLAG_W_MIPI_CLR_rd_result_flag_w_mipi_clr_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_T_MIPI_RD_OVERTIME_FLAG_DSP_UNION
 结构说明  : T_MIPI_RD_OVERTIME_FLAG_DSP 寄存器结构定义。地址偏移量:0x0C00，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      t_mipi_rd_overtime_flag_dsp_reg;
    struct
    {
        unsigned int  tds_mipi_rd_overtime_flag_dsp : 1;  /* bit[0]   : DSP等待回读结果超时标志位
                                                                        1:超时   */
        unsigned int  reserved                      : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_T_MIPI_RD_OVERTIME_FLAG_DSP_UNION;
#define BBPCOMM_T_MIPI_RD_OVERTIME_FLAG_DSP_tds_mipi_rd_overtime_flag_dsp_START  (0)
#define BBPCOMM_T_MIPI_RD_OVERTIME_FLAG_DSP_tds_mipi_rd_overtime_flag_dsp_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_T_SSI_RD_OVERTIME_FLAG_DSP_UNION
 结构说明  : T_SSI_RD_OVERTIME_FLAG_DSP 寄存器结构定义。地址偏移量:0x0C04，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      t_ssi_rd_overtime_flag_dsp_reg;
    struct
    {
        unsigned int  tds_rfic_rd_overtime_flag_dsp : 1;  /* bit[0]   : DSP等待回读结果超时标志位
                                                                        1:超时   */
        unsigned int  reserved                      : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_T_SSI_RD_OVERTIME_FLAG_DSP_UNION;
#define BBPCOMM_T_SSI_RD_OVERTIME_FLAG_DSP_tds_rfic_rd_overtime_flag_dsp_START  (0)
#define BBPCOMM_T_SSI_RD_OVERTIME_FLAG_DSP_tds_rfic_rd_overtime_flag_dsp_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_T_MIPI_RD_OVERTIME_CLR_UNION
 结构说明  : T_MIPI_RD_OVERTIME_CLR 寄存器结构定义。地址偏移量:0x0C08，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      t_mipi_rd_overtime_clr_reg;
    struct
    {
        unsigned int  tds_mipi_rd_overtime_clr_imi : 1;  /* bit[0]   : DSP等待回读结果超时后,清抄时标志位脉冲 */
        unsigned int  reserved                     : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_T_MIPI_RD_OVERTIME_CLR_UNION;
#define BBPCOMM_T_MIPI_RD_OVERTIME_CLR_tds_mipi_rd_overtime_clr_imi_START  (0)
#define BBPCOMM_T_MIPI_RD_OVERTIME_CLR_tds_mipi_rd_overtime_clr_imi_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_T_SSI_RD_OVERTIME_CLR_UNION
 结构说明  : T_SSI_RD_OVERTIME_CLR 寄存器结构定义。地址偏移量:0x0C0C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      t_ssi_rd_overtime_clr_reg;
    struct
    {
        unsigned int  tds_rfic_rd_overtime_clr_imi : 1;  /* bit[0]   : DSP等待回读结果超时后,清抄时标志位脉冲 */
        unsigned int  reserved                     : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_T_SSI_RD_OVERTIME_CLR_UNION;
#define BBPCOMM_T_SSI_RD_OVERTIME_CLR_tds_rfic_rd_overtime_clr_imi_START  (0)
#define BBPCOMM_T_SSI_RD_OVERTIME_CLR_tds_rfic_rd_overtime_clr_imi_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_RD_RESULT_FLAG_T_RFIC_UNION
 结构说明  : RD_RESULT_FLAG_T_RFIC 寄存器结构定义。地址偏移量:0x0C50，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      rd_result_flag_t_rfic_reg;
    struct
    {
        unsigned int  rd_result_flag_tds_rfic : 1;  /* bit[0]   : 所有回读指令执行完毕,可以取走回读数据
                                                                  1:所有回读指令发送完毕,DSP可以按位置读取SSI回读结果 */
        unsigned int  reserved                : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_RD_RESULT_FLAG_T_RFIC_UNION;
#define BBPCOMM_RD_RESULT_FLAG_T_RFIC_rd_result_flag_tds_rfic_START  (0)
#define BBPCOMM_RD_RESULT_FLAG_T_RFIC_rd_result_flag_tds_rfic_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_RD_RESULT_FLAG_T_RFIC_CLR_UNION
 结构说明  : RD_RESULT_FLAG_T_RFIC_CLR 寄存器结构定义。地址偏移量:0x0C54，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      rd_result_flag_t_rfic_clr_reg;
    struct
    {
        unsigned int  rd_result_flag_tds_rfic_clr : 1;  /* bit[0]   : 1:DSP取走所有回读数据后,写入clr信号清标志位 */
        unsigned int  reserved                    : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_RD_RESULT_FLAG_T_RFIC_CLR_UNION;
#define BBPCOMM_RD_RESULT_FLAG_T_RFIC_CLR_rd_result_flag_tds_rfic_clr_START  (0)
#define BBPCOMM_RD_RESULT_FLAG_T_RFIC_CLR_rd_result_flag_tds_rfic_clr_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_RD_RESULT_FLAG_T_MIPI_UNION
 结构说明  : RD_RESULT_FLAG_T_MIPI 寄存器结构定义。地址偏移量:0x0C98，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      rd_result_flag_t_mipi_reg;
    struct
    {
        unsigned int  rd_result_flag_tds_mipi : 1;  /* bit[0]   : 所有回读指令执行完毕,可以取走回读数据
                                                                  1:所有回读指令发送完毕,DSP可以按位置读取MIPI回读结果,与下述的软件直接控制MIPI标志位不同 */
        unsigned int  reserved                : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_RD_RESULT_FLAG_T_MIPI_UNION;
#define BBPCOMM_RD_RESULT_FLAG_T_MIPI_rd_result_flag_tds_mipi_START  (0)
#define BBPCOMM_RD_RESULT_FLAG_T_MIPI_rd_result_flag_tds_mipi_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_RD_RESULT_FLAG_T_MIPI_CLR_UNION
 结构说明  : RD_RESULT_FLAG_T_MIPI_CLR 寄存器结构定义。地址偏移量:0x0C9C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      rd_result_flag_t_mipi_clr_reg;
    struct
    {
        unsigned int  rd_result_flag_tds_mipi_clr : 1;  /* bit[0]   : 1:DSP取走所有回读数据后,写入clr信号清标志位,与下述的软件直接控制MIPI标志位不同 */
        unsigned int  reserved                    : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_RD_RESULT_FLAG_T_MIPI_CLR_UNION;
#define BBPCOMM_RD_RESULT_FLAG_T_MIPI_CLR_rd_result_flag_tds_mipi_clr_START  (0)
#define BBPCOMM_RD_RESULT_FLAG_T_MIPI_CLR_rd_result_flag_tds_mipi_clr_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_C_MIPI_RD_OVERTIME_FLAG_DSP_UNION
 结构说明  : C_MIPI_RD_OVERTIME_FLAG_DSP 寄存器结构定义。地址偏移量:0x0D00，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c_mipi_rd_overtime_flag_dsp_reg;
    struct
    {
        unsigned int  c_mipi_rd_overtime_flag_dsp : 1;  /* bit[0]   : DSP等待回读结果超时标志位
                                                                      1:超时   */
        unsigned int  reserved                    : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_C_MIPI_RD_OVERTIME_FLAG_DSP_UNION;
#define BBPCOMM_C_MIPI_RD_OVERTIME_FLAG_DSP_c_mipi_rd_overtime_flag_dsp_START  (0)
#define BBPCOMM_C_MIPI_RD_OVERTIME_FLAG_DSP_c_mipi_rd_overtime_flag_dsp_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_C_SSI_RD_OVERTIME_FLAG_DSP_UNION
 结构说明  : C_SSI_RD_OVERTIME_FLAG_DSP 寄存器结构定义。地址偏移量:0x0D04，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c_ssi_rd_overtime_flag_dsp_reg;
    struct
    {
        unsigned int  c_rfic_rd_overtime_flag_dsp : 1;  /* bit[0]   : DSP等待回读结果超时标志位
                                                                      1:超时   */
        unsigned int  reserved                    : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_C_SSI_RD_OVERTIME_FLAG_DSP_UNION;
#define BBPCOMM_C_SSI_RD_OVERTIME_FLAG_DSP_c_rfic_rd_overtime_flag_dsp_START  (0)
#define BBPCOMM_C_SSI_RD_OVERTIME_FLAG_DSP_c_rfic_rd_overtime_flag_dsp_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_C_MIPI_RD_OVERTIME_CLR_UNION
 结构说明  : C_MIPI_RD_OVERTIME_CLR 寄存器结构定义。地址偏移量:0x0D08，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c_mipi_rd_overtime_clr_reg;
    struct
    {
        unsigned int  c_mipi_rd_overtime_clr_imi : 1;  /* bit[0]   : DSP等待回读结果超时后,清抄时标志位脉冲 */
        unsigned int  reserved                   : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_C_MIPI_RD_OVERTIME_CLR_UNION;
#define BBPCOMM_C_MIPI_RD_OVERTIME_CLR_c_mipi_rd_overtime_clr_imi_START  (0)
#define BBPCOMM_C_MIPI_RD_OVERTIME_CLR_c_mipi_rd_overtime_clr_imi_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_C_SSI_RD_OVERTIME_CLR_UNION
 结构说明  : C_SSI_RD_OVERTIME_CLR 寄存器结构定义。地址偏移量:0x0D0C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c_ssi_rd_overtime_clr_reg;
    struct
    {
        unsigned int  c_rfic_rd_overtime_clr_imi : 1;  /* bit[0]   : DSP等待回读结果超时后,清抄时标志位脉冲 */
        unsigned int  reserved                   : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_C_SSI_RD_OVERTIME_CLR_UNION;
#define BBPCOMM_C_SSI_RD_OVERTIME_CLR_c_rfic_rd_overtime_clr_imi_START  (0)
#define BBPCOMM_C_SSI_RD_OVERTIME_CLR_c_rfic_rd_overtime_clr_imi_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_RD_RESULT_FLAG_C_RFIC_UNION
 结构说明  : RD_RESULT_FLAG_C_RFIC 寄存器结构定义。地址偏移量:0x0D50，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      rd_result_flag_c_rfic_reg;
    struct
    {
        unsigned int  rd_result_flag_c_rfic : 1;  /* bit[0]   : 所有回读指令执行完毕,可以取走回读数据
                                                                1:所有回读指令发送完毕,DSP可以按位置读取SSI回读结果 */
        unsigned int  reserved              : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_RD_RESULT_FLAG_C_RFIC_UNION;
#define BBPCOMM_RD_RESULT_FLAG_C_RFIC_rd_result_flag_c_rfic_START  (0)
#define BBPCOMM_RD_RESULT_FLAG_C_RFIC_rd_result_flag_c_rfic_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_RD_RESULT_FLAG_C_RFIC_CLR_UNION
 结构说明  : RD_RESULT_FLAG_C_RFIC_CLR 寄存器结构定义。地址偏移量:0x0D54，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      rd_result_flag_c_rfic_clr_reg;
    struct
    {
        unsigned int  rd_result_flag_c_rfic_clr : 1;  /* bit[0]   : 1:DSP取走所有回读数据后,写入clr信号清标志位 */
        unsigned int  reserved                  : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_RD_RESULT_FLAG_C_RFIC_CLR_UNION;
#define BBPCOMM_RD_RESULT_FLAG_C_RFIC_CLR_rd_result_flag_c_rfic_clr_START  (0)
#define BBPCOMM_RD_RESULT_FLAG_C_RFIC_CLR_rd_result_flag_c_rfic_clr_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_RD_RESULT_FLAG_C_MIPI_UNION
 结构说明  : RD_RESULT_FLAG_C_MIPI 寄存器结构定义。地址偏移量:0x0D98，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      rd_result_flag_c_mipi_reg;
    struct
    {
        unsigned int  rd_result_flag_c_mipi : 1;  /* bit[0]   : 所有回读指令执行完毕,可以取走回读数据
                                                                1:所有回读指令发送完毕,DSP可以按位置读取MIPI回读结果,与下述的软件直接控制MIPI标志位不同 */
        unsigned int  reserved              : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_RD_RESULT_FLAG_C_MIPI_UNION;
#define BBPCOMM_RD_RESULT_FLAG_C_MIPI_rd_result_flag_c_mipi_START  (0)
#define BBPCOMM_RD_RESULT_FLAG_C_MIPI_rd_result_flag_c_mipi_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_RD_RESULT_FLAG_C_MIPI_CLR_UNION
 结构说明  : RD_RESULT_FLAG_C_MIPI_CLR 寄存器结构定义。地址偏移量:0x0D9C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      rd_result_flag_c_mipi_clr_reg;
    struct
    {
        unsigned int  rd_result_flag_c_mipi_clr : 1;  /* bit[0]   : 1:DSP取走所有回读数据后,写入clr信号清标志位,与下述的软件直接控制MIPI标志位不同 */
        unsigned int  reserved                  : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_RD_RESULT_FLAG_C_MIPI_CLR_UNION;
#define BBPCOMM_RD_RESULT_FLAG_C_MIPI_CLR_rd_result_flag_c_mipi_clr_START  (0)
#define BBPCOMM_RD_RESULT_FLAG_C_MIPI_CLR_rd_result_flag_c_mipi_clr_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_TIMING_VALID1_UNION
 结构说明  : TIMING_VALID1 寄存器结构定义。地址偏移量:0x0CA4，初值:0x00000030，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      timing_valid1_reg;
    struct
    {
        unsigned int  o_timing_valid1     : 1;  /* bit[0]   : 定时上报有效标志，高有效。
                                                              ARM配置timing_get_ind后，查询此标志，如果为高，则可以获取LTE，W，Gm，Gs, TDS的系统定时。
                                                              DSP读取定时，在DSP下次启动新的timing_get_ind时拉低此信号。 */
        unsigned int  reserved_0          : 3;  /* bit[1-3] : 保留 */
        unsigned int  timing_valid_c_sel1 : 2;  /* bit[4-5] : 上报c2模的计数器给ARM的是1x、evdo还是base_cnt
                                                              00：1x定时
                                                              01： evdo定时
                                                              10： basecent */
        unsigned int  reserved_1          : 26; /* bit[6-31]: 保留 */
    } reg;
} BBPCOMM_TIMING_VALID1_UNION;
#define BBPCOMM_TIMING_VALID1_o_timing_valid1_START      (0)
#define BBPCOMM_TIMING_VALID1_o_timing_valid1_END        (0)
#define BBPCOMM_TIMING_VALID1_timing_valid_c_sel1_START  (4)
#define BBPCOMM_TIMING_VALID1_timing_valid_c_sel1_END    (5)


/*****************************************************************************
 结构名    : BBPCOMM_W_TIMING_DSP1_UNION
 结构说明  : W_TIMING_DSP1 寄存器结构定义。地址偏移量:0x0CAC，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      w_timing_dsp1_reg;
    struct
    {
        unsigned int  w_clk_cnt_dsp1  : 4;  /* bit[0-3]  : [3:0]为chip内时钟计数，范围0~15 */
        unsigned int  w_chip_cnt_dsp1 : 12; /* bit[4-15] : [15:4]为时隙内chip计数，范围0~2559 */
        unsigned int  w_slot_cnt_dsp1 : 4;  /* bit[16-19]: [19:16]为时隙计数，范围0~14 */
        unsigned int  w_sfn_dsp1      : 12; /* bit[20-31]: ARM读取W的系统定时信息，由DSP 配置timing_get_ind触发上报。
                                                           上报时刻：触发后检测o_timing_valid1为1有效。
                                                           [31:20]表示W的SFN计数（源自w_timing_b[11:0]），范围0~4095。 */
    } reg;
} BBPCOMM_W_TIMING_DSP1_UNION;
#define BBPCOMM_W_TIMING_DSP1_w_clk_cnt_dsp1_START   (0)
#define BBPCOMM_W_TIMING_DSP1_w_clk_cnt_dsp1_END     (3)
#define BBPCOMM_W_TIMING_DSP1_w_chip_cnt_dsp1_START  (4)
#define BBPCOMM_W_TIMING_DSP1_w_chip_cnt_dsp1_END    (15)
#define BBPCOMM_W_TIMING_DSP1_w_slot_cnt_dsp1_START  (16)
#define BBPCOMM_W_TIMING_DSP1_w_slot_cnt_dsp1_END    (19)
#define BBPCOMM_W_TIMING_DSP1_w_sfn_dsp1_START       (20)
#define BBPCOMM_W_TIMING_DSP1_w_sfn_dsp1_END         (31)


/*****************************************************************************
 结构名    : BBPCOMM_GM_FN_DSP1_UNION
 结构说明  : GM_FN_DSP1 寄存器结构定义。地址偏移量:0x0CB4，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      gm_fn_dsp1_reg;
    struct
    {
        unsigned int  o_gm_fn_dsp1 : 22; /* bit[0-21] : GM的FN计数（源自gm_timing_a[21:0]），由ARM配置timing_get_ind触发上报。其中[10:0]表示fn_low,范围0~1325；[21:11]表示fn_hign,范围0~2047。
                                                        上报时刻：触发后立即生效 */
        unsigned int  reserved     : 10; /* bit[22-31]: 保留 */
    } reg;
} BBPCOMM_GM_FN_DSP1_UNION;
#define BBPCOMM_GM_FN_DSP1_o_gm_fn_dsp1_START  (0)
#define BBPCOMM_GM_FN_DSP1_o_gm_fn_dsp1_END    (21)


/*****************************************************************************
 结构名    : BBPCOMM_GM_QB_DSP1_UNION
 结构说明  : GM_QB_DSP1 寄存器结构定义。地址偏移量:0x0CB8，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      gm_qb_dsp1_reg;
    struct
    {
        unsigned int  o_gm_qb_dsp1 : 13; /* bit[0-12] : GM的系统定时Qb信息，由ARM配置timing_get_ind触发上报。
                                                         [12:0]表示 G系统定时帧内Qb计数（源自gm_timing_b[12:0]），范围0~4999。
                                                        上报时刻：触发后立即生效 */
        unsigned int  reserved     : 19; /* bit[13-31]: 保留 */
    } reg;
} BBPCOMM_GM_QB_DSP1_UNION;
#define BBPCOMM_GM_QB_DSP1_o_gm_qb_dsp1_START  (0)
#define BBPCOMM_GM_QB_DSP1_o_gm_qb_dsp1_END    (12)


/*****************************************************************************
 结构名    : BBPCOMM_GS_FN_DSP1_UNION
 结构说明  : GS_FN_DSP1 寄存器结构定义。地址偏移量:0x0CD0，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      gs_fn_dsp1_reg;
    struct
    {
        unsigned int  gs_fn_dsp1 : 22; /* bit[0-21] : GS的FN计数（源自gs_timing_a[21:0]），由ARM配置timing_get_ind触发上报。其中[10:0]表示fn_low,范围0~1325；[21:11]表示fn_hign,范围0~2047。
                                                      上报时刻：触发后立即生效 */
        unsigned int  reserved   : 10; /* bit[22-31]: 保留 */
    } reg;
} BBPCOMM_GS_FN_DSP1_UNION;
#define BBPCOMM_GS_FN_DSP1_gs_fn_dsp1_START  (0)
#define BBPCOMM_GS_FN_DSP1_gs_fn_dsp1_END    (21)


/*****************************************************************************
 结构名    : BBPCOMM_GS_QB_DSP1_UNION
 结构说明  : GS_QB_DSP1 寄存器结构定义。地址偏移量:0x0CD4，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      gs_qb_dsp1_reg;
    struct
    {
        unsigned int  o_gs_qb_dsp1 : 13; /* bit[0-12] : GS的系统定时Qb信息，由ARM配置timing_get_ind触发上报。
                                                         [12:0]表示 GS系统定时帧内Qb计数（源自gs_timing_b[12:0]），范围0~4999。
                                                        上报时刻：触发后立即生效 */
        unsigned int  reserved     : 19; /* bit[13-31]: 保留 */
    } reg;
} BBPCOMM_GS_QB_DSP1_UNION;
#define BBPCOMM_GS_QB_DSP1_o_gs_qb_dsp1_START  (0)
#define BBPCOMM_GS_QB_DSP1_o_gs_qb_dsp1_END    (12)


/*****************************************************************************
 结构名    : BBPCOMM_LTE_TIMING_DSP1_UNION
 结构说明  : LTE_TIMING_DSP1 寄存器结构定义。地址偏移量:0x0CDC，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      lte_timing_dsp1_reg;
    struct
    {
        unsigned int  o_lte_sys_ts_cnt_dsp1     : 15; /* bit[0-14] : [14:0]是子帧内计数。  */
        unsigned int  reserved_0                : 1;  /* bit[15-15]: 保留 */
        unsigned int  o_lte_sys_subfrm_cnt_dsp1 : 4;  /* bit[16-19]: [19:16]是子帧计数 */
        unsigned int  o_lte_sfn_dsp1            : 10; /* bit[20-29]: LTE的系统定时。由ARM配置timing_get_ind触发上报。
                                                                     上报时刻：触发后立即生效
                                                                     其中:
                                                                     [29:20]表示SFN计数，范围0~1023 */
        unsigned int  reserved_1                : 2;  /* bit[30-31]: 保留 */
    } reg;
} BBPCOMM_LTE_TIMING_DSP1_UNION;
#define BBPCOMM_LTE_TIMING_DSP1_o_lte_sys_ts_cnt_dsp1_START      (0)
#define BBPCOMM_LTE_TIMING_DSP1_o_lte_sys_ts_cnt_dsp1_END        (14)
#define BBPCOMM_LTE_TIMING_DSP1_o_lte_sys_subfrm_cnt_dsp1_START  (16)
#define BBPCOMM_LTE_TIMING_DSP1_o_lte_sys_subfrm_cnt_dsp1_END    (19)
#define BBPCOMM_LTE_TIMING_DSP1_o_lte_sfn_dsp1_START             (20)
#define BBPCOMM_LTE_TIMING_DSP1_o_lte_sfn_dsp1_END               (29)


/*****************************************************************************
 结构名    : BBPCOMM_TDS_TIMING1_DSP1_UNION
 结构说明  : TDS_TIMING1_DSP1 寄存器结构定义。地址偏移量:0x0CE4，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      tds_timing1_dsp1_reg;
    struct
    {
        unsigned int  o_tds_timing1_dsp1 : 16; /* bit[0-15] : TDS的系统定时。由ARM配置timing_get_ind触发上报。本寄存器上报的是TDS的tcfsr系统子帧号0~65535循环计数，TDS实际有效子帧范围为0~8191
                                                              上报时刻：触发后立即生效 */
        unsigned int  reserved           : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_TDS_TIMING1_DSP1_UNION;
#define BBPCOMM_TDS_TIMING1_DSP1_o_tds_timing1_dsp1_START  (0)
#define BBPCOMM_TDS_TIMING1_DSP1_o_tds_timing1_dsp1_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_TDS_TIMING2_DSP1_UNION
 结构说明  : TDS_TIMING2_DSP1 寄存器结构定义。地址偏移量:0x0CE8，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      tds_timing2_dsp1_reg;
    struct
    {
        unsigned int  o_tds_timing2_dsp1 : 20; /* bit[0-19] : TDS的系统定时。由ARM配置timing_get_ind触发上报。本寄存器上报的是是TDS的framc帧计数
                                                              上报时刻：触发后立即生效 */
        unsigned int  reserved           : 12; /* bit[20-31]: 保留 */
    } reg;
} BBPCOMM_TDS_TIMING2_DSP1_UNION;
#define BBPCOMM_TDS_TIMING2_DSP1_o_tds_timing2_dsp1_START  (0)
#define BBPCOMM_TDS_TIMING2_DSP1_o_tds_timing2_dsp1_END    (19)


/*****************************************************************************
 结构名    : BBPCOMM_C_TIMING_DSP1_UNION
 结构说明  : C_TIMING_DSP1 寄存器结构定义。地址偏移量:0x0CF0，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c_timing_dsp1_reg;
    struct
    {
        unsigned int  o_c_timing1_dsp1 : 30; /* bit[0-29] : C2模定时信息上报。 
                                                            C2模定时信息上报。 
                                                            1X模式：
                                                            Bit[4:0]   1/4chip     计数范围0~24  
                                                            Bit[6:5]   chip        计数范围0~3
                                                            Bit[17:7]  chip number 计数范围0~1535
                                                            Bit[23:18] 80ms        计数范围0~63
                                                            Bit[29:24] 2s/5.12s超帧计数范围0~24/0~63
                                                            EVDO：
                                                            Bit[4:0]   1/4chip     计数范围0~24  Bit[6:5]   chip        计数范围0~3
                                                            Bit[21:7]  chip number 计数范围0~32767
                                                            Bit[23:22] 80ms        计数范围0~63
                                                            Bit[29:24] 2s/5.12s超帧计数范围0~24/0~63
                                                            BASE_CNT：
                                                            Bit[4:0]   1/4chip     计数范围0~24  
                                                            Bit[6:5]   chip        计数范围0~3
                                                            Bit[21:7]  chip number 计数范围0~32767
                                                            Bit[23:22]  80ms       计数范围0~63
                                                            Bit[28:24]  2s超帧     计数范围0~24 */
        unsigned int  reserved         : 2;  /* bit[30-31]: 保留 */
    } reg;
} BBPCOMM_C_TIMING_DSP1_UNION;
#define BBPCOMM_C_TIMING_DSP1_o_c_timing1_dsp1_START  (0)
#define BBPCOMM_C_TIMING_DSP1_o_c_timing1_dsp1_END    (29)


/*****************************************************************************
 结构名    : BBPCOMM_TIMING_VALID2_UNION
 结构说明  : TIMING_VALID2 寄存器结构定义。地址偏移量:0x0EA4，初值:0x00000030，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      timing_valid2_reg;
    struct
    {
        unsigned int  o_timing_valid2     : 1;  /* bit[0]   : 定时上报有效标志，高有效。
                                                              C模BBE16 DSP配置timing_get_ind后，查询此标志，如果为高，则可以获取LTE，W，Gm，Gs, TDS的系统定时。
                                                              DSP读取定时，在DSP下次启动新的timing_get_ind时拉低此信号。 */
        unsigned int  reserved_0          : 3;  /* bit[1-3] : 保留 */
        unsigned int  timing_valid_c_sel2 : 2;  /* bit[4-5] : 上报c2模的计数器给C模BBE16 DSP的是1x、evdo还是base_cnt
                                                              00：1x定时
                                                              01： evdo定时
                                                              10： basecent */
        unsigned int  reserved_1          : 26; /* bit[6-31]: 保留 */
    } reg;
} BBPCOMM_TIMING_VALID2_UNION;
#define BBPCOMM_TIMING_VALID2_o_timing_valid2_START      (0)
#define BBPCOMM_TIMING_VALID2_o_timing_valid2_END        (0)
#define BBPCOMM_TIMING_VALID2_timing_valid_c_sel2_START  (4)
#define BBPCOMM_TIMING_VALID2_timing_valid_c_sel2_END    (5)


/*****************************************************************************
 结构名    : BBPCOMM_W_TIMING_DSP2_UNION
 结构说明  : W_TIMING_DSP2 寄存器结构定义。地址偏移量:0x0EA8，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      w_timing_dsp2_reg;
    struct
    {
        unsigned int  w_clk_cnt_dsp2  : 4;  /* bit[0-3]  : [3:0]为chip内时钟计数，范围0~15 */
        unsigned int  w_chip_cnt_dsp2 : 12; /* bit[4-15] : [15:4]为时隙内chip计数，范围0~2559 */
        unsigned int  w_slot_cnt_dsp2 : 4;  /* bit[16-19]: [19:16]为时隙计数，范围0~14 */
        unsigned int  w_sfn_dsp2      : 12; /* bit[20-31]: C模BBE16 DSP读取W的系统定时信息，由DSP 配置timing_get_ind触发上报。
                                                           上报时刻：触发后检测o_timing_valid2为1有效。
                                                           [31:20]表示W的SFN计数（源自w_timing_b[11:0]），范围0~4095。 */
    } reg;
} BBPCOMM_W_TIMING_DSP2_UNION;
#define BBPCOMM_W_TIMING_DSP2_w_clk_cnt_dsp2_START   (0)
#define BBPCOMM_W_TIMING_DSP2_w_clk_cnt_dsp2_END     (3)
#define BBPCOMM_W_TIMING_DSP2_w_chip_cnt_dsp2_START  (4)
#define BBPCOMM_W_TIMING_DSP2_w_chip_cnt_dsp2_END    (15)
#define BBPCOMM_W_TIMING_DSP2_w_slot_cnt_dsp2_START  (16)
#define BBPCOMM_W_TIMING_DSP2_w_slot_cnt_dsp2_END    (19)
#define BBPCOMM_W_TIMING_DSP2_w_sfn_dsp2_START       (20)
#define BBPCOMM_W_TIMING_DSP2_w_sfn_dsp2_END         (31)


/*****************************************************************************
 结构名    : BBPCOMM_GM_FN_DSP2_UNION
 结构说明  : GM_FN_DSP2 寄存器结构定义。地址偏移量:0x0EB0，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      gm_fn_dsp2_reg;
    struct
    {
        unsigned int  o_gm_fn_dsp2 : 22; /* bit[0-21] : GM的FN计数（源自gm_timing_a[21:0]），由C模BBE16 DSP配置timing_get_ind触发上报。其中[10:0]表示fn_low,范围0~1325；[21:11]表示fn_hign,范围0~2047。
                                                        上报时刻：触发后立即生效 */
        unsigned int  reserved     : 10; /* bit[22-31]: 保留 */
    } reg;
} BBPCOMM_GM_FN_DSP2_UNION;
#define BBPCOMM_GM_FN_DSP2_o_gm_fn_dsp2_START  (0)
#define BBPCOMM_GM_FN_DSP2_o_gm_fn_dsp2_END    (21)


/*****************************************************************************
 结构名    : BBPCOMM_GM_QB_DSP2_UNION
 结构说明  : GM_QB_DSP2 寄存器结构定义。地址偏移量:0x0EB4，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      gm_qb_dsp2_reg;
    struct
    {
        unsigned int  o_gm_qb_dsp2 : 13; /* bit[0-12] : GM的系统定时Qb信息，由C模BBE16 DSP配置timing_get_ind触发上报。
                                                         [12:0]表示 G系统定时帧内Qb计数（源自gm_timing_b[12:0]），范围0~4999。
                                                        上报时刻：触发后立即生效 */
        unsigned int  reserved     : 19; /* bit[13-31]: 保留 */
    } reg;
} BBPCOMM_GM_QB_DSP2_UNION;
#define BBPCOMM_GM_QB_DSP2_o_gm_qb_dsp2_START  (0)
#define BBPCOMM_GM_QB_DSP2_o_gm_qb_dsp2_END    (12)


/*****************************************************************************
 结构名    : BBPCOMM_GS_FN_DSP2_UNION
 结构说明  : GS_FN_DSP2 寄存器结构定义。地址偏移量:0x0EBC，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      gs_fn_dsp2_reg;
    struct
    {
        unsigned int  gs_fn_dsp2 : 22; /* bit[0-21] : GS的FN计数（源自gs_timing_a[21:0]），由C模BBE16 DSP配置timing_get_ind触发上报。其中[10:0]表示fn_low,范围0~1325；[21:11]表示fn_hign,范围0~2047。
                                                      上报时刻：触发后立即生效 */
        unsigned int  reserved   : 10; /* bit[22-31]: 保留 */
    } reg;
} BBPCOMM_GS_FN_DSP2_UNION;
#define BBPCOMM_GS_FN_DSP2_gs_fn_dsp2_START  (0)
#define BBPCOMM_GS_FN_DSP2_gs_fn_dsp2_END    (21)


/*****************************************************************************
 结构名    : BBPCOMM_GS_QB_DSP2_UNION
 结构说明  : GS_QB_DSP2 寄存器结构定义。地址偏移量:0x0EC0，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      gs_qb_dsp2_reg;
    struct
    {
        unsigned int  o_gs_qb_dsp2 : 13; /* bit[0-12] : GS的系统定时Qb信息，由C模BBE16 DSP配置timing_get_ind触发上报。
                                                         [12:0]表示 GS系统定时帧内Qb计数（源自gs_timing_b[12:0]），范围0~4999。
                                                        上报时刻：触发后立即生效 */
        unsigned int  reserved     : 19; /* bit[13-31]: 保留 */
    } reg;
} BBPCOMM_GS_QB_DSP2_UNION;
#define BBPCOMM_GS_QB_DSP2_o_gs_qb_dsp2_START  (0)
#define BBPCOMM_GS_QB_DSP2_o_gs_qb_dsp2_END    (12)


/*****************************************************************************
 结构名    : BBPCOMM_LTE_TIMING_DSP2_UNION
 结构说明  : LTE_TIMING_DSP2 寄存器结构定义。地址偏移量:0x0EC8，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      lte_timing_dsp2_reg;
    struct
    {
        unsigned int  o_lte_sys_ts_cnt_dsp2     : 15; /* bit[0-14] : [14:0]是子帧内计数。  */
        unsigned int  reserved_0                : 1;  /* bit[15-15]: 保留 */
        unsigned int  o_lte_sys_subfrm_cnt_dsp2 : 4;  /* bit[16-19]: [19:16]是子帧计数 */
        unsigned int  o_lte_sfn_dsp2            : 10; /* bit[20-29]: LTE的系统定时。由C模BBE16 DSP配置timing_get_ind触发上报。
                                                                     上报时刻：触发后立即生效
                                                                     其中:
                                                                     [29:20]表示SFN计数，范围0~1023 */
        unsigned int  reserved_1                : 2;  /* bit[30-31]: 保留 */
    } reg;
} BBPCOMM_LTE_TIMING_DSP2_UNION;
#define BBPCOMM_LTE_TIMING_DSP2_o_lte_sys_ts_cnt_dsp2_START      (0)
#define BBPCOMM_LTE_TIMING_DSP2_o_lte_sys_ts_cnt_dsp2_END        (14)
#define BBPCOMM_LTE_TIMING_DSP2_o_lte_sys_subfrm_cnt_dsp2_START  (16)
#define BBPCOMM_LTE_TIMING_DSP2_o_lte_sys_subfrm_cnt_dsp2_END    (19)
#define BBPCOMM_LTE_TIMING_DSP2_o_lte_sfn_dsp2_START             (20)
#define BBPCOMM_LTE_TIMING_DSP2_o_lte_sfn_dsp2_END               (29)


/*****************************************************************************
 结构名    : BBPCOMM_TDS_TIMING1_DSP2_UNION
 结构说明  : TDS_TIMING1_DSP2 寄存器结构定义。地址偏移量:0x0ED0，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      tds_timing1_dsp2_reg;
    struct
    {
        unsigned int  o_tds_timing1_dsp2 : 16; /* bit[0-15] : TDS的系统定时。由C模BBE16 DSP配置timing_get_ind触发上报。本寄存器上报的是TDS的tcfsr系统子帧号0~65535循环计数，TDS实际有效子帧范围为0~8191
                                                              上报时刻：触发后立即生效 */
        unsigned int  reserved           : 16; /* bit[16-31]: 保留 */
    } reg;
} BBPCOMM_TDS_TIMING1_DSP2_UNION;
#define BBPCOMM_TDS_TIMING1_DSP2_o_tds_timing1_dsp2_START  (0)
#define BBPCOMM_TDS_TIMING1_DSP2_o_tds_timing1_dsp2_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_TDS_TIMING2_DSP2_UNION
 结构说明  : TDS_TIMING2_DSP2 寄存器结构定义。地址偏移量:0x0ED4，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      tds_timing2_dsp2_reg;
    struct
    {
        unsigned int  o_tds_timing2_dsp2 : 20; /* bit[0-19] : TDS的系统定时。由C模BBE16 DSP配置timing_get_ind触发上报。本寄存器上报的是是TDS的framc帧计数
                                                              上报时刻：触发后立即生效 */
        unsigned int  reserved           : 12; /* bit[20-31]: 保留 */
    } reg;
} BBPCOMM_TDS_TIMING2_DSP2_UNION;
#define BBPCOMM_TDS_TIMING2_DSP2_o_tds_timing2_dsp2_START  (0)
#define BBPCOMM_TDS_TIMING2_DSP2_o_tds_timing2_dsp2_END    (19)


/*****************************************************************************
 结构名    : BBPCOMM_C_TIMING_DSP2_UNION
 结构说明  : C_TIMING_DSP2 寄存器结构定义。地址偏移量:0x0EDC，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c_timing_dsp2_reg;
    struct
    {
        unsigned int  o_c_timing1_dsp2 : 30; /* bit[0-29] : C2模定时信息上报。 
                                                            C2模定时信息上报。 
                                                            1X模式：
                                                            Bit[4:0]   1/4chip     计数范围0~24  
                                                            Bit[6:5]   chip        计数范围0~3
                                                            Bit[17:7]  chip number 计数范围0~1535
                                                            Bit[23:18] 80ms        计数范围0~63
                                                            Bit[29:24] 2s/5.12s超帧计数范围0~24/0~63
                                                            EVDO：
                                                            Bit[4:0]   1/4chip     计数范围0~24  Bit[6:5]   chip        计数范围0~3
                                                            Bit[21:7]  chip number 计数范围0~32767
                                                            Bit[23:22] 80ms        计数范围0~63
                                                            Bit[29:24] 2s/5.12s超帧计数范围0~24/0~63
                                                            BASE_CNT：
                                                            Bit[4:0]   1/4chip     计数范围0~24  
                                                            Bit[6:5]   chip        计数范围0~3
                                                            Bit[21:7]  chip number 计数范围0~32767
                                                            Bit[23:22]  80ms       计数范围0~63
                                                            Bit[28:24]  2s超帧     计数范围0~24 */
        unsigned int  reserved         : 2;  /* bit[30-31]: 保留 */
    } reg;
} BBPCOMM_C_TIMING_DSP2_UNION;
#define BBPCOMM_C_TIMING_DSP2_o_c_timing1_dsp2_START  (0)
#define BBPCOMM_C_TIMING_DSP2_o_c_timing1_dsp2_END    (29)


/*****************************************************************************
 结构名    : BBPCOMM_LTE_CH0_MIPI_RD_OVERTIME_FLAG_DSP_UNION
 结构说明  : LTE_CH0_MIPI_RD_OVERTIME_FLAG_DSP 寄存器结构定义。地址偏移量:0x0E00，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      lte_ch0_mipi_rd_overtime_flag_dsp_reg;
    struct
    {
        unsigned int  lte_ch0_mipi_rd_overtime_flag_dsp : 1;  /* bit[0]   : DSP等待回读结果超时标志位
                                                                            1:超时   */
        unsigned int  reserved                          : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_LTE_CH0_MIPI_RD_OVERTIME_FLAG_DSP_UNION;
#define BBPCOMM_LTE_CH0_MIPI_RD_OVERTIME_FLAG_DSP_lte_ch0_mipi_rd_overtime_flag_dsp_START  (0)
#define BBPCOMM_LTE_CH0_MIPI_RD_OVERTIME_FLAG_DSP_lte_ch0_mipi_rd_overtime_flag_dsp_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_LTE_CH0_SSI_RD_OVERTIME_FLAG_DSP_UNION
 结构说明  : LTE_CH0_SSI_RD_OVERTIME_FLAG_DSP 寄存器结构定义。地址偏移量:0x0E04，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      lte_ch0_ssi_rd_overtime_flag_dsp_reg;
    struct
    {
        unsigned int  lte_ch0_rfic_rd_overtime_flag_dsp : 1;  /* bit[0]   : DSP等待回读结果超时标志位
                                                                            1:超时   */
        unsigned int  reserved                          : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_LTE_CH0_SSI_RD_OVERTIME_FLAG_DSP_UNION;
#define BBPCOMM_LTE_CH0_SSI_RD_OVERTIME_FLAG_DSP_lte_ch0_rfic_rd_overtime_flag_dsp_START  (0)
#define BBPCOMM_LTE_CH0_SSI_RD_OVERTIME_FLAG_DSP_lte_ch0_rfic_rd_overtime_flag_dsp_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_LTE_CH0_MIPI_RD_OVERTIME_CLR_UNION
 结构说明  : LTE_CH0_MIPI_RD_OVERTIME_CLR 寄存器结构定义。地址偏移量:0x0E08，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      lte_ch0_mipi_rd_overtime_clr_reg;
    struct
    {
        unsigned int  lte_ch0_mipi_rd_overtime_clr_imi : 1;  /* bit[0]   : DSP等待回读结果超时后,清抄时标志位脉冲 */
        unsigned int  reserved                         : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_LTE_CH0_MIPI_RD_OVERTIME_CLR_UNION;
#define BBPCOMM_LTE_CH0_MIPI_RD_OVERTIME_CLR_lte_ch0_mipi_rd_overtime_clr_imi_START  (0)
#define BBPCOMM_LTE_CH0_MIPI_RD_OVERTIME_CLR_lte_ch0_mipi_rd_overtime_clr_imi_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_LTE_CH0_SSI_RD_OVERTIME_CLR_UNION
 结构说明  : LTE_CH0_SSI_RD_OVERTIME_CLR 寄存器结构定义。地址偏移量:0x0E0C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      lte_ch0_ssi_rd_overtime_clr_reg;
    struct
    {
        unsigned int  lte_ch0_rfic_rd_overtime_clr_imi : 1;  /* bit[0]   : DSP等待回读结果超时后,清抄时标志位脉冲 */
        unsigned int  reserved                         : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_LTE_CH0_SSI_RD_OVERTIME_CLR_UNION;
#define BBPCOMM_LTE_CH0_SSI_RD_OVERTIME_CLR_lte_ch0_rfic_rd_overtime_clr_imi_START  (0)
#define BBPCOMM_LTE_CH0_SSI_RD_OVERTIME_CLR_lte_ch0_rfic_rd_overtime_clr_imi_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_RD_RESULT_FLAG_LTE_CH0_RFIC_UNION
 结构说明  : RD_RESULT_FLAG_LTE_CH0_RFIC 寄存器结构定义。地址偏移量:0x0E50，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      rd_result_flag_lte_ch0_rfic_reg;
    struct
    {
        unsigned int  rd_result_flag_lte_ch0_rfic : 1;  /* bit[0]   : 所有回读指令执行完毕,可以取走回读数据
                                                                      1:所有回读指令发送完毕,DSP可以按位置读取SSI回读结果 */
        unsigned int  reserved                    : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_RD_RESULT_FLAG_LTE_CH0_RFIC_UNION;
#define BBPCOMM_RD_RESULT_FLAG_LTE_CH0_RFIC_rd_result_flag_lte_ch0_rfic_START  (0)
#define BBPCOMM_RD_RESULT_FLAG_LTE_CH0_RFIC_rd_result_flag_lte_ch0_rfic_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_RD_RESULT_FLAG_LTE_CH0_RFIC_CLR_UNION
 结构说明  : RD_RESULT_FLAG_LTE_CH0_RFIC_CLR 寄存器结构定义。地址偏移量:0x0E54，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      rd_result_flag_lte_ch0_rfic_clr_reg;
    struct
    {
        unsigned int  rd_result_flag_lte_ch0_rfic_clr : 1;  /* bit[0]   : 1:DSP取走所有回读数据后,写入clr信号清标志位 */
        unsigned int  reserved                        : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_RD_RESULT_FLAG_LTE_CH0_RFIC_CLR_UNION;
#define BBPCOMM_RD_RESULT_FLAG_LTE_CH0_RFIC_CLR_rd_result_flag_lte_ch0_rfic_clr_START  (0)
#define BBPCOMM_RD_RESULT_FLAG_LTE_CH0_RFIC_CLR_rd_result_flag_lte_ch0_rfic_clr_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_RD_RESULT_FLAG_LTE_CH0_MIPI_UNION
 结构说明  : RD_RESULT_FLAG_LTE_CH0_MIPI 寄存器结构定义。地址偏移量:0x0E98，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      rd_result_flag_lte_ch0_mipi_reg;
    struct
    {
        unsigned int  rd_result_flag_lte_ch0_mipi : 1;  /* bit[0]   : 所有回读指令执行完毕,可以取走回读数据
                                                                      1:所有回读指令发送完毕,DSP可以按位置读取MIPI回读结果,与下述的软件直接控制MIPI标志位不同 */
        unsigned int  reserved                    : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_RD_RESULT_FLAG_LTE_CH0_MIPI_UNION;
#define BBPCOMM_RD_RESULT_FLAG_LTE_CH0_MIPI_rd_result_flag_lte_ch0_mipi_START  (0)
#define BBPCOMM_RD_RESULT_FLAG_LTE_CH0_MIPI_rd_result_flag_lte_ch0_mipi_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_RD_RESULT_FLAG_LTE_CH0_MIPI_CLR_UNION
 结构说明  : RD_RESULT_FLAG_LTE_CH0_MIPI_CLR 寄存器结构定义。地址偏移量:0x0E9C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      rd_result_flag_lte_ch0_mipi_clr_reg;
    struct
    {
        unsigned int  rd_result_flag_lte_ch0_mipi_clr : 1;  /* bit[0]   : 1:DSP取走所有回读数据后,写入clr信号清标志位,与下述的软件直接控制MIPI标志位不同 */
        unsigned int  reserved                        : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_RD_RESULT_FLAG_LTE_CH0_MIPI_CLR_UNION;
#define BBPCOMM_RD_RESULT_FLAG_LTE_CH0_MIPI_CLR_rd_result_flag_lte_ch0_mipi_clr_START  (0)
#define BBPCOMM_RD_RESULT_FLAG_LTE_CH0_MIPI_CLR_rd_result_flag_lte_ch0_mipi_clr_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_LTE_CH1_MIPI_RD_OVERTIME_FLAG_DSP_UNION
 结构说明  : LTE_CH1_MIPI_RD_OVERTIME_FLAG_DSP 寄存器结构定义。地址偏移量:0x0F00，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      lte_ch1_mipi_rd_overtime_flag_dsp_reg;
    struct
    {
        unsigned int  lte_ch1_mipi_rd_overtime_flag_dsp : 1;  /* bit[0]   : DSP等待回读结果超时标志位
                                                                            1:超时   */
        unsigned int  reserved                          : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_LTE_CH1_MIPI_RD_OVERTIME_FLAG_DSP_UNION;
#define BBPCOMM_LTE_CH1_MIPI_RD_OVERTIME_FLAG_DSP_lte_ch1_mipi_rd_overtime_flag_dsp_START  (0)
#define BBPCOMM_LTE_CH1_MIPI_RD_OVERTIME_FLAG_DSP_lte_ch1_mipi_rd_overtime_flag_dsp_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_LTE_CH1_SSI_RD_OVERTIME_FLAG_DSP_UNION
 结构说明  : LTE_CH1_SSI_RD_OVERTIME_FLAG_DSP 寄存器结构定义。地址偏移量:0x0F04，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      lte_ch1_ssi_rd_overtime_flag_dsp_reg;
    struct
    {
        unsigned int  lte_ch1_rfic_rd_overtime_flag_dsp : 1;  /* bit[0]   : DSP等待回读结果超时标志位
                                                                            1:超时   */
        unsigned int  reserved                          : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_LTE_CH1_SSI_RD_OVERTIME_FLAG_DSP_UNION;
#define BBPCOMM_LTE_CH1_SSI_RD_OVERTIME_FLAG_DSP_lte_ch1_rfic_rd_overtime_flag_dsp_START  (0)
#define BBPCOMM_LTE_CH1_SSI_RD_OVERTIME_FLAG_DSP_lte_ch1_rfic_rd_overtime_flag_dsp_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_LTE_CH1_MIPI_RD_OVERTIME_CLR_UNION
 结构说明  : LTE_CH1_MIPI_RD_OVERTIME_CLR 寄存器结构定义。地址偏移量:0x0F08，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      lte_ch1_mipi_rd_overtime_clr_reg;
    struct
    {
        unsigned int  lte_ch1_mipi_rd_overtime_clr_imi : 1;  /* bit[0]   : DSP等待回读结果超时后,清抄时标志位脉冲 */
        unsigned int  reserved                         : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_LTE_CH1_MIPI_RD_OVERTIME_CLR_UNION;
#define BBPCOMM_LTE_CH1_MIPI_RD_OVERTIME_CLR_lte_ch1_mipi_rd_overtime_clr_imi_START  (0)
#define BBPCOMM_LTE_CH1_MIPI_RD_OVERTIME_CLR_lte_ch1_mipi_rd_overtime_clr_imi_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_LTE_CH1_SSI_RD_OVERTIME_CLR_UNION
 结构说明  : LTE_CH1_SSI_RD_OVERTIME_CLR 寄存器结构定义。地址偏移量:0x0F0C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      lte_ch1_ssi_rd_overtime_clr_reg;
    struct
    {
        unsigned int  lte_ch1_rfic_rd_overtime_clr_imi : 1;  /* bit[0]   : DSP等待回读结果超时后,清抄时标志位脉冲 */
        unsigned int  reserved                         : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_LTE_CH1_SSI_RD_OVERTIME_CLR_UNION;
#define BBPCOMM_LTE_CH1_SSI_RD_OVERTIME_CLR_lte_ch1_rfic_rd_overtime_clr_imi_START  (0)
#define BBPCOMM_LTE_CH1_SSI_RD_OVERTIME_CLR_lte_ch1_rfic_rd_overtime_clr_imi_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_RD_RESULT_FLAG_LTE_CH1_RFIC_UNION
 结构说明  : RD_RESULT_FLAG_LTE_CH1_RFIC 寄存器结构定义。地址偏移量:0x0F50，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      rd_result_flag_lte_ch1_rfic_reg;
    struct
    {
        unsigned int  rd_result_flag_lte_ch1_rfic : 1;  /* bit[0]   : 所有回读指令执行完毕,可以取走回读数据
                                                                      1:所有回读指令发送完毕,DSP可以按位置读取SSI回读结果 */
        unsigned int  reserved                    : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_RD_RESULT_FLAG_LTE_CH1_RFIC_UNION;
#define BBPCOMM_RD_RESULT_FLAG_LTE_CH1_RFIC_rd_result_flag_lte_ch1_rfic_START  (0)
#define BBPCOMM_RD_RESULT_FLAG_LTE_CH1_RFIC_rd_result_flag_lte_ch1_rfic_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_RD_RESULT_FLAG_LTE_CH1_RFIC_CLR_UNION
 结构说明  : RD_RESULT_FLAG_LTE_CH1_RFIC_CLR 寄存器结构定义。地址偏移量:0x0F54，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      rd_result_flag_lte_ch1_rfic_clr_reg;
    struct
    {
        unsigned int  rd_result_flag_lte_ch1_rfic_clr : 1;  /* bit[0]   : 1:DSP取走所有回读数据后,写入clr信号清标志位 */
        unsigned int  reserved                        : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_RD_RESULT_FLAG_LTE_CH1_RFIC_CLR_UNION;
#define BBPCOMM_RD_RESULT_FLAG_LTE_CH1_RFIC_CLR_rd_result_flag_lte_ch1_rfic_clr_START  (0)
#define BBPCOMM_RD_RESULT_FLAG_LTE_CH1_RFIC_CLR_rd_result_flag_lte_ch1_rfic_clr_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_RD_RESULT_FLAG_LTE_CH1_MIPI_UNION
 结构说明  : RD_RESULT_FLAG_LTE_CH1_MIPI 寄存器结构定义。地址偏移量:0x0F98，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      rd_result_flag_lte_ch1_mipi_reg;
    struct
    {
        unsigned int  rd_result_flag_lte_ch1_mipi : 1;  /* bit[0]   : 所有回读指令执行完毕,可以取走回读数据
                                                                      1:所有回读指令发送完毕,DSP可以按位置读取MIPI回读结果,与下述的软件直接控制MIPI标志位不同 */
        unsigned int  reserved                    : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_RD_RESULT_FLAG_LTE_CH1_MIPI_UNION;
#define BBPCOMM_RD_RESULT_FLAG_LTE_CH1_MIPI_rd_result_flag_lte_ch1_mipi_START  (0)
#define BBPCOMM_RD_RESULT_FLAG_LTE_CH1_MIPI_rd_result_flag_lte_ch1_mipi_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_RD_RESULT_FLAG_LTE_CH1_MIPI_CLR_UNION
 结构说明  : RD_RESULT_FLAG_LTE_CH1_MIPI_CLR 寄存器结构定义。地址偏移量:0x0F9C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      rd_result_flag_lte_ch1_mipi_clr_reg;
    struct
    {
        unsigned int  rd_result_flag_lte_ch1_mipi_clr : 1;  /* bit[0]   : 1:DSP取走所有回读数据后,写入clr信号清标志位,与下述的软件直接控制MIPI标志位不同 */
        unsigned int  reserved                        : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_RD_RESULT_FLAG_LTE_CH1_MIPI_CLR_UNION;
#define BBPCOMM_RD_RESULT_FLAG_LTE_CH1_MIPI_CLR_rd_result_flag_lte_ch1_mipi_clr_START  (0)
#define BBPCOMM_RD_RESULT_FLAG_LTE_CH1_MIPI_CLR_rd_result_flag_lte_ch1_mipi_clr_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_LTE_CH2_MIPI_RD_OVERTIME_FLAG_DSP_UNION
 结构说明  : LTE_CH2_MIPI_RD_OVERTIME_FLAG_DSP 寄存器结构定义。地址偏移量:0x1000，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      lte_ch2_mipi_rd_overtime_flag_dsp_reg;
    struct
    {
        unsigned int  lte_ch2_mipi_rd_overtime_flag_dsp : 1;  /* bit[0]   : DSP等待回读结果超时标志位
                                                                            1:超时   */
        unsigned int  reserved                          : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_LTE_CH2_MIPI_RD_OVERTIME_FLAG_DSP_UNION;
#define BBPCOMM_LTE_CH2_MIPI_RD_OVERTIME_FLAG_DSP_lte_ch2_mipi_rd_overtime_flag_dsp_START  (0)
#define BBPCOMM_LTE_CH2_MIPI_RD_OVERTIME_FLAG_DSP_lte_ch2_mipi_rd_overtime_flag_dsp_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_LTE_CH2_SSI_RD_OVERTIME_FLAG_DSP_UNION
 结构说明  : LTE_CH2_SSI_RD_OVERTIME_FLAG_DSP 寄存器结构定义。地址偏移量:0x1004，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      lte_ch2_ssi_rd_overtime_flag_dsp_reg;
    struct
    {
        unsigned int  lte_ch2_rfic_rd_overtime_flag_dsp : 1;  /* bit[0]   : DSP等待回读结果超时标志位
                                                                            1:超时   */
        unsigned int  reserved                          : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_LTE_CH2_SSI_RD_OVERTIME_FLAG_DSP_UNION;
#define BBPCOMM_LTE_CH2_SSI_RD_OVERTIME_FLAG_DSP_lte_ch2_rfic_rd_overtime_flag_dsp_START  (0)
#define BBPCOMM_LTE_CH2_SSI_RD_OVERTIME_FLAG_DSP_lte_ch2_rfic_rd_overtime_flag_dsp_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_LTE_CH2_MIPI_RD_OVERTIME_CLR_UNION
 结构说明  : LTE_CH2_MIPI_RD_OVERTIME_CLR 寄存器结构定义。地址偏移量:0x1008，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      lte_ch2_mipi_rd_overtime_clr_reg;
    struct
    {
        unsigned int  lte_ch2_mipi_rd_overtime_clr_imi : 1;  /* bit[0]   : DSP等待回读结果超时后,清抄时标志位脉冲 */
        unsigned int  reserved                         : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_LTE_CH2_MIPI_RD_OVERTIME_CLR_UNION;
#define BBPCOMM_LTE_CH2_MIPI_RD_OVERTIME_CLR_lte_ch2_mipi_rd_overtime_clr_imi_START  (0)
#define BBPCOMM_LTE_CH2_MIPI_RD_OVERTIME_CLR_lte_ch2_mipi_rd_overtime_clr_imi_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_LTE_CH2_SSI_RD_OVERTIME_CLR_UNION
 结构说明  : LTE_CH2_SSI_RD_OVERTIME_CLR 寄存器结构定义。地址偏移量:0x100C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      lte_ch2_ssi_rd_overtime_clr_reg;
    struct
    {
        unsigned int  lte_ch2_rfic_rd_overtime_clr_imi : 1;  /* bit[0]   : DSP等待回读结果超时后,清抄时标志位脉冲 */
        unsigned int  reserved                         : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_LTE_CH2_SSI_RD_OVERTIME_CLR_UNION;
#define BBPCOMM_LTE_CH2_SSI_RD_OVERTIME_CLR_lte_ch2_rfic_rd_overtime_clr_imi_START  (0)
#define BBPCOMM_LTE_CH2_SSI_RD_OVERTIME_CLR_lte_ch2_rfic_rd_overtime_clr_imi_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_RD_RESULT_FLAG_LTE_CH2_RFIC_UNION
 结构说明  : RD_RESULT_FLAG_LTE_CH2_RFIC 寄存器结构定义。地址偏移量:0x1050，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      rd_result_flag_lte_ch2_rfic_reg;
    struct
    {
        unsigned int  rd_result_flag_lte_ch2_rfic : 1;  /* bit[0]   : 所有回读指令执行完毕,可以取走回读数据
                                                                      1:所有回读指令发送完毕,DSP可以按位置读取SSI回读结果 */
        unsigned int  reserved                    : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_RD_RESULT_FLAG_LTE_CH2_RFIC_UNION;
#define BBPCOMM_RD_RESULT_FLAG_LTE_CH2_RFIC_rd_result_flag_lte_ch2_rfic_START  (0)
#define BBPCOMM_RD_RESULT_FLAG_LTE_CH2_RFIC_rd_result_flag_lte_ch2_rfic_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_RD_RESULT_FLAG_LTE_CH2_RFIC_CLR_UNION
 结构说明  : RD_RESULT_FLAG_LTE_CH2_RFIC_CLR 寄存器结构定义。地址偏移量:0x1054，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      rd_result_flag_lte_ch2_rfic_clr_reg;
    struct
    {
        unsigned int  rd_result_flag_lte_ch2_rfic_clr : 1;  /* bit[0]   : 1:DSP取走所有回读数据后,写入clr信号清标志位 */
        unsigned int  reserved                        : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_RD_RESULT_FLAG_LTE_CH2_RFIC_CLR_UNION;
#define BBPCOMM_RD_RESULT_FLAG_LTE_CH2_RFIC_CLR_rd_result_flag_lte_ch2_rfic_clr_START  (0)
#define BBPCOMM_RD_RESULT_FLAG_LTE_CH2_RFIC_CLR_rd_result_flag_lte_ch2_rfic_clr_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_RD_RESULT_FLAG_LTE_CH2_MIPI_UNION
 结构说明  : RD_RESULT_FLAG_LTE_CH2_MIPI 寄存器结构定义。地址偏移量:0x1098，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      rd_result_flag_lte_ch2_mipi_reg;
    struct
    {
        unsigned int  rd_result_flag_lte_ch2_mipi : 1;  /* bit[0]   : 所有回读指令执行完毕,可以取走回读数据
                                                                      1:所有回读指令发送完毕,DSP可以按位置读取MIPI回读结果,与下述的软件直接控制MIPI标志位不同 */
        unsigned int  reserved                    : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_RD_RESULT_FLAG_LTE_CH2_MIPI_UNION;
#define BBPCOMM_RD_RESULT_FLAG_LTE_CH2_MIPI_rd_result_flag_lte_ch2_mipi_START  (0)
#define BBPCOMM_RD_RESULT_FLAG_LTE_CH2_MIPI_rd_result_flag_lte_ch2_mipi_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_RD_RESULT_FLAG_LTE_CH2_MIPI_CLR_UNION
 结构说明  : RD_RESULT_FLAG_LTE_CH2_MIPI_CLR 寄存器结构定义。地址偏移量:0x109C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      rd_result_flag_lte_ch2_mipi_clr_reg;
    struct
    {
        unsigned int  rd_result_flag_lte_ch2_mipi_clr : 1;  /* bit[0]   : 1:DSP取走所有回读数据后,写入clr信号清标志位,与下述的软件直接控制MIPI标志位不同 */
        unsigned int  reserved                        : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_RD_RESULT_FLAG_LTE_CH2_MIPI_CLR_UNION;
#define BBPCOMM_RD_RESULT_FLAG_LTE_CH2_MIPI_CLR_rd_result_flag_lte_ch2_mipi_clr_START  (0)
#define BBPCOMM_RD_RESULT_FLAG_LTE_CH2_MIPI_CLR_rd_result_flag_lte_ch2_mipi_clr_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_LTE_CH3_MIPI_RD_OVERTIME_FLAG_DSP_UNION
 结构说明  : LTE_CH3_MIPI_RD_OVERTIME_FLAG_DSP 寄存器结构定义。地址偏移量:0x1100，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      lte_ch3_mipi_rd_overtime_flag_dsp_reg;
    struct
    {
        unsigned int  lte_ch3_mipi_rd_overtime_flag_dsp : 1;  /* bit[0]   : DSP等待回读结果超时标志位
                                                                            1:超时   */
        unsigned int  reserved                          : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_LTE_CH3_MIPI_RD_OVERTIME_FLAG_DSP_UNION;
#define BBPCOMM_LTE_CH3_MIPI_RD_OVERTIME_FLAG_DSP_lte_ch3_mipi_rd_overtime_flag_dsp_START  (0)
#define BBPCOMM_LTE_CH3_MIPI_RD_OVERTIME_FLAG_DSP_lte_ch3_mipi_rd_overtime_flag_dsp_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_LTE_CH3_SSI_RD_OVERTIME_FLAG_DSP_UNION
 结构说明  : LTE_CH3_SSI_RD_OVERTIME_FLAG_DSP 寄存器结构定义。地址偏移量:0x1104，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      lte_ch3_ssi_rd_overtime_flag_dsp_reg;
    struct
    {
        unsigned int  lte_ch3_rfic_rd_overtime_flag_dsp : 1;  /* bit[0]   : DSP等待回读结果超时标志位
                                                                            1:超时   */
        unsigned int  reserved                          : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_LTE_CH3_SSI_RD_OVERTIME_FLAG_DSP_UNION;
#define BBPCOMM_LTE_CH3_SSI_RD_OVERTIME_FLAG_DSP_lte_ch3_rfic_rd_overtime_flag_dsp_START  (0)
#define BBPCOMM_LTE_CH3_SSI_RD_OVERTIME_FLAG_DSP_lte_ch3_rfic_rd_overtime_flag_dsp_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_LTE_CH3_MIPI_RD_OVERTIME_CLR_UNION
 结构说明  : LTE_CH3_MIPI_RD_OVERTIME_CLR 寄存器结构定义。地址偏移量:0x1108，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      lte_ch3_mipi_rd_overtime_clr_reg;
    struct
    {
        unsigned int  lte_ch3_mipi_rd_overtime_clr_imi : 1;  /* bit[0]   : DSP等待回读结果超时后,清抄时标志位脉冲 */
        unsigned int  reserved                         : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_LTE_CH3_MIPI_RD_OVERTIME_CLR_UNION;
#define BBPCOMM_LTE_CH3_MIPI_RD_OVERTIME_CLR_lte_ch3_mipi_rd_overtime_clr_imi_START  (0)
#define BBPCOMM_LTE_CH3_MIPI_RD_OVERTIME_CLR_lte_ch3_mipi_rd_overtime_clr_imi_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_LTE_CH3_SSI_RD_OVERTIME_CLR_UNION
 结构说明  : LTE_CH3_SSI_RD_OVERTIME_CLR 寄存器结构定义。地址偏移量:0x110C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      lte_ch3_ssi_rd_overtime_clr_reg;
    struct
    {
        unsigned int  lte_ch3_rfic_rd_overtime_clr_imi : 1;  /* bit[0]   : DSP等待回读结果超时后,清抄时标志位脉冲 */
        unsigned int  reserved                         : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_LTE_CH3_SSI_RD_OVERTIME_CLR_UNION;
#define BBPCOMM_LTE_CH3_SSI_RD_OVERTIME_CLR_lte_ch3_rfic_rd_overtime_clr_imi_START  (0)
#define BBPCOMM_LTE_CH3_SSI_RD_OVERTIME_CLR_lte_ch3_rfic_rd_overtime_clr_imi_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_RD_RESULT_FLAG_LTE_CH3_RFIC_UNION
 结构说明  : RD_RESULT_FLAG_LTE_CH3_RFIC 寄存器结构定义。地址偏移量:0x1150，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      rd_result_flag_lte_ch3_rfic_reg;
    struct
    {
        unsigned int  rd_result_flag_lte_ch3_rfic : 1;  /* bit[0]   : 所有回读指令执行完毕,可以取走回读数据
                                                                      1:所有回读指令发送完毕,DSP可以按位置读取SSI回读结果 */
        unsigned int  reserved                    : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_RD_RESULT_FLAG_LTE_CH3_RFIC_UNION;
#define BBPCOMM_RD_RESULT_FLAG_LTE_CH3_RFIC_rd_result_flag_lte_ch3_rfic_START  (0)
#define BBPCOMM_RD_RESULT_FLAG_LTE_CH3_RFIC_rd_result_flag_lte_ch3_rfic_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_RD_RESULT_FLAG_LTE_CH3_RFIC_CLR_UNION
 结构说明  : RD_RESULT_FLAG_LTE_CH3_RFIC_CLR 寄存器结构定义。地址偏移量:0x1154，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      rd_result_flag_lte_ch3_rfic_clr_reg;
    struct
    {
        unsigned int  rd_result_flag_lte_ch3_rfic_clr : 1;  /* bit[0]   : 1:DSP取走所有回读数据后,写入clr信号清标志位 */
        unsigned int  reserved                        : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_RD_RESULT_FLAG_LTE_CH3_RFIC_CLR_UNION;
#define BBPCOMM_RD_RESULT_FLAG_LTE_CH3_RFIC_CLR_rd_result_flag_lte_ch3_rfic_clr_START  (0)
#define BBPCOMM_RD_RESULT_FLAG_LTE_CH3_RFIC_CLR_rd_result_flag_lte_ch3_rfic_clr_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_RD_RESULT_FLAG_LTE_CH3_MIPI_UNION
 结构说明  : RD_RESULT_FLAG_LTE_CH3_MIPI 寄存器结构定义。地址偏移量:0x1198，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      rd_result_flag_lte_ch3_mipi_reg;
    struct
    {
        unsigned int  rd_result_flag_lte_ch3_mipi : 1;  /* bit[0]   : 所有回读指令执行完毕,可以取走回读数据
                                                                      1:所有回读指令发送完毕,DSP可以按位置读取MIPI回读结果,与下述的软件直接控制MIPI标志位不同 */
        unsigned int  reserved                    : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_RD_RESULT_FLAG_LTE_CH3_MIPI_UNION;
#define BBPCOMM_RD_RESULT_FLAG_LTE_CH3_MIPI_rd_result_flag_lte_ch3_mipi_START  (0)
#define BBPCOMM_RD_RESULT_FLAG_LTE_CH3_MIPI_rd_result_flag_lte_ch3_mipi_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_RD_RESULT_FLAG_LTE_CH3_MIPI_CLR_UNION
 结构说明  : RD_RESULT_FLAG_LTE_CH3_MIPI_CLR 寄存器结构定义。地址偏移量:0x119C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      rd_result_flag_lte_ch3_mipi_clr_reg;
    struct
    {
        unsigned int  rd_result_flag_lte_ch3_mipi_clr : 1;  /* bit[0]   : 1:DSP取走所有回读数据后,写入clr信号清标志位,与下述的软件直接控制MIPI标志位不同 */
        unsigned int  reserved                        : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_RD_RESULT_FLAG_LTE_CH3_MIPI_CLR_UNION;
#define BBPCOMM_RD_RESULT_FLAG_LTE_CH3_MIPI_CLR_rd_result_flag_lte_ch3_mipi_clr_START  (0)
#define BBPCOMM_RD_RESULT_FLAG_LTE_CH3_MIPI_CLR_rd_result_flag_lte_ch3_mipi_clr_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_C0_AFC_PDM_SELECT_MASK_UNION
 结构说明  : C0_AFC_PDM_SELECT_MASK 寄存器结构定义。地址偏移量:0x1200，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c0_afc_pdm_select_mask_reg;
    struct
    {
        unsigned int  c0_afc_pdm_select_mask : 4;  /* bit[0-3] : 通道0 AFC控制信号来源。
                                                                 4'b0000，受主模控制；
                                                                 4'b0010，强制受W模控制；
                                                                 4'b0011，强制受TDS模控制；
                                                                 4'b0100，强制受Gm模控制；
                                                                 4'b0101，强制受Gs模控制；
                                                                 4'b0110，强制受C模控制；
                                                                 4'b1000，强制受L模控制；
                                                                 其它，无效。
                                                                 调试用。 */
        unsigned int  reserved               : 28; /* bit[4-31]: 保留 */
    } reg;
} BBPCOMM_C0_AFC_PDM_SELECT_MASK_UNION;
#define BBPCOMM_C0_AFC_PDM_SELECT_MASK_c0_afc_pdm_select_mask_START  (0)
#define BBPCOMM_C0_AFC_PDM_SELECT_MASK_c0_afc_pdm_select_mask_END    (3)


/*****************************************************************************
 结构名    : BBPCOMM_C0_ANT_SWITCH_PA_SELECT_MASK_UNION
 结构说明  : C0_ANT_SWITCH_PA_SELECT_MASK 寄存器结构定义。地址偏移量:0x1204，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c0_ant_switch_pa_select_mask_reg;
    struct
    {
        unsigned int  c0_ant_switch_pa_select_mask : 4;  /* bit[0-3] : 通道0 天线开关和PA控制信号来源。
                                                                       4'b0000，受主模控制；
                                                                       4'b0010，强制受W模控制；
                                                                       4'b0011，强制受TDS模控制；
                                                                       4'b0100，强制受Gm模控制；
                                                                       4'b0101，强制受Gs模控制；
                                                                       4'b0110，强制受C模控制；
                                                                       4'b1000，强制受L模控制；
                                                                       其它，无效。
                                                                       调试用。 */
        unsigned int  reserved                     : 28; /* bit[4-31]: 保留 */
    } reg;
} BBPCOMM_C0_ANT_SWITCH_PA_SELECT_MASK_UNION;
#define BBPCOMM_C0_ANT_SWITCH_PA_SELECT_MASK_c0_ant_switch_pa_select_mask_START  (0)
#define BBPCOMM_C0_ANT_SWITCH_PA_SELECT_MASK_c0_ant_switch_pa_select_mask_END    (3)


/*****************************************************************************
 结构名    : BBPCOMM_C0_RFIC_SELECT_MASK_UNION
 结构说明  : C0_RFIC_SELECT_MASK 寄存器结构定义。地址偏移量:0x1208，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c0_rfic_select_mask_reg;
    struct
    {
        unsigned int  c0_rfic_select_mask : 4;  /* bit[0-3] : 通道0 RFIC控制信号来源（包括线控和SSI）。
                                                              4'b0000，受主模控制；
                                                              4'b0010，强制受W模控制；
                                                              4'b0011，强制受TDS模控制；
                                                              4'b0100，强制受Gm模控制；
                                                              4'b0101，强制受Gs模控制；
                                                              4'b0110，强制受C模控制；
                                                              4'b1000，强制受L模CC0控制；
                                                              4'b1001，强制受L模CC1控制；
                                                              4'b1010，强制受L模CC2控制；
                                                              4'b1011，强制受L模CC3控制；
                                                              其它，无效。
                                                              调试用。 */
        unsigned int  reserved            : 28; /* bit[4-31]: 保留 */
    } reg;
} BBPCOMM_C0_RFIC_SELECT_MASK_UNION;
#define BBPCOMM_C0_RFIC_SELECT_MASK_c0_rfic_select_mask_START  (0)
#define BBPCOMM_C0_RFIC_SELECT_MASK_c0_rfic_select_mask_END    (3)


/*****************************************************************************
 结构名    : BBPCOMM_C0_MIPI_SELECT_MASK_UNION
 结构说明  : C0_MIPI_SELECT_MASK 寄存器结构定义。地址偏移量:0x120C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c0_mipi_select_mask_reg;
    struct
    {
        unsigned int  c0_mipi_select_mask : 4;  /* bit[0-3] : 通道0 MIPI控制信号来源。
                                                              4'b0000，受主模控制；
                                                              4'b0010，强制受W模控制；
                                                              4'b0011，强制受TDS模控制；
                                                              4'b0100，强制受Gm模控制；
                                                              4'b0101，强制受Gs模控制；
                                                              4'b0110，强制受C模控制；
                                                              4'b1000，强制受L模CC0控制；
                                                              4'b1001，强制受L模CC1控制；
                                                              4'b1010，强制受L模CC2控制；
                                                              4'b1011，强制受L模CC3控制；
                                                              其它，无效。
                                                              调试用。 */
        unsigned int  reserved            : 28; /* bit[4-31]: 保留 */
    } reg;
} BBPCOMM_C0_MIPI_SELECT_MASK_UNION;
#define BBPCOMM_C0_MIPI_SELECT_MASK_c0_mipi_select_mask_START  (0)
#define BBPCOMM_C0_MIPI_SELECT_MASK_c0_mipi_select_mask_END    (3)


/*****************************************************************************
 结构名    : BBPCOMM_C0_ABB_RX_SELECT_MASK_UNION
 结构说明  : C0_ABB_RX_SELECT_MASK 寄存器结构定义。地址偏移量:0x1210，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c0_abb_rx_select_mask_reg;
    struct
    {
        unsigned int  c0_abb_rx_select_mask : 4;  /* bit[0-3] : 通道0 ABB接收控制信号来源。
                                                                4'b0000，受主模控制；
                                                                4'b0010，强制受W模控制；
                                                                4'b0011，强制受TDS模控制；
                                                                4'b0100，强制受Gm模控制；
                                                                4'b0101，强制受Gs模控制；
                                                                4'b0110，强制受C模控制；
                                                                4'b1000，强制受L模CC0控制；
                                                                4'b1001，强制受L模CC1控制；
                                                                4'b1010，强制受L模CC2控制；
                                                                4'b1011，强制受L模CC3控制；
                                                                其它，无效。
                                                                调试用。 */
        unsigned int  reserved              : 28; /* bit[4-31]: 保留 */
    } reg;
} BBPCOMM_C0_ABB_RX_SELECT_MASK_UNION;
#define BBPCOMM_C0_ABB_RX_SELECT_MASK_c0_abb_rx_select_mask_START  (0)
#define BBPCOMM_C0_ABB_RX_SELECT_MASK_c0_abb_rx_select_mask_END    (3)


/*****************************************************************************
 结构名    : BBPCOMM_ABB0_LINE_CONTROL_CMD_RX_UNION
 结构说明  : ABB0_LINE_CONTROL_CMD_RX 寄存器结构定义。地址偏移量:0x1214，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      abb0_line_control_cmd_rx_reg;
    struct
    {
        unsigned int  abb0_line_control_cmd_sel_rx : 1;  /* bit[0-0] : ABB0线控强配模式：
                                                                       1：表示软件强配，此时上述各个强配才生效；
                                                                       0：表示由CTU根据各BBP产生。
                                                                       默认值为0。
                                                                       测试用。 */
        unsigned int  abb0_mode_sel_rx_cmd         : 3;  /* bit[1-3] : 软件强配模式abb0_mode_sel_rx. */
        unsigned int  abb0_rxa_en_cmd              : 1;  /* bit[4-4] : 软件强配模式abb0_rxa_en. */
        unsigned int  abb0_rxb_en_cmd              : 1;  /* bit[5-5] : 软件强配模式abb0_rxb_en. */
        unsigned int  abb0_blka_en_cmd             : 1;  /* bit[6-6] : 软件强配模式abb0_rxa_blk_en. */
        unsigned int  abb0_blkb_en_cmd             : 1;  /* bit[7-7] : 软件强配模式abb0_rxb_blk_en. */
        unsigned int  reserved                     : 24; /* bit[8-31]: 保留 */
    } reg;
} BBPCOMM_ABB0_LINE_CONTROL_CMD_RX_UNION;
#define BBPCOMM_ABB0_LINE_CONTROL_CMD_RX_abb0_line_control_cmd_sel_rx_START  (0)
#define BBPCOMM_ABB0_LINE_CONTROL_CMD_RX_abb0_line_control_cmd_sel_rx_END    (0)
#define BBPCOMM_ABB0_LINE_CONTROL_CMD_RX_abb0_mode_sel_rx_cmd_START          (1)
#define BBPCOMM_ABB0_LINE_CONTROL_CMD_RX_abb0_mode_sel_rx_cmd_END            (3)
#define BBPCOMM_ABB0_LINE_CONTROL_CMD_RX_abb0_rxa_en_cmd_START               (4)
#define BBPCOMM_ABB0_LINE_CONTROL_CMD_RX_abb0_rxa_en_cmd_END                 (4)
#define BBPCOMM_ABB0_LINE_CONTROL_CMD_RX_abb0_rxb_en_cmd_START               (5)
#define BBPCOMM_ABB0_LINE_CONTROL_CMD_RX_abb0_rxb_en_cmd_END                 (5)
#define BBPCOMM_ABB0_LINE_CONTROL_CMD_RX_abb0_blka_en_cmd_START              (6)
#define BBPCOMM_ABB0_LINE_CONTROL_CMD_RX_abb0_blka_en_cmd_END                (6)
#define BBPCOMM_ABB0_LINE_CONTROL_CMD_RX_abb0_blkb_en_cmd_START              (7)
#define BBPCOMM_ABB0_LINE_CONTROL_CMD_RX_abb0_blkb_en_cmd_END                (7)


/*****************************************************************************
 结构名    : BBPCOMM_ABB0_LINE_CONTROL_CMD_TX_UNION
 结构说明  : ABB0_LINE_CONTROL_CMD_TX 寄存器结构定义。地址偏移量:0x1218，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      abb0_line_control_cmd_tx_reg;
    struct
    {
        unsigned int  abb0_line_control_cmd_sel_tx : 1;  /* bit[0-0] : ABB0线控强配模式：
                                                                       1：表示软件强配，此时上述各个强配才生效；
                                                                       0：表示由CTU根据各BBP产生。
                                                                       默认值为0。
                                                                       测试用。 */
        unsigned int  abb0_tx_en_cmd               : 1;  /* bit[1-1] : 软件强配模式abb0_tx_en. */
        unsigned int  abb0_mode_sel_tx_cmd         : 3;  /* bit[2-4] : 软件强配模式abb0_mode_sel_tx. */
        unsigned int  reserved                     : 27; /* bit[5-31]: 保留 */
    } reg;
} BBPCOMM_ABB0_LINE_CONTROL_CMD_TX_UNION;
#define BBPCOMM_ABB0_LINE_CONTROL_CMD_TX_abb0_line_control_cmd_sel_tx_START  (0)
#define BBPCOMM_ABB0_LINE_CONTROL_CMD_TX_abb0_line_control_cmd_sel_tx_END    (0)
#define BBPCOMM_ABB0_LINE_CONTROL_CMD_TX_abb0_tx_en_cmd_START                (1)
#define BBPCOMM_ABB0_LINE_CONTROL_CMD_TX_abb0_tx_en_cmd_END                  (1)
#define BBPCOMM_ABB0_LINE_CONTROL_CMD_TX_abb0_mode_sel_tx_cmd_START          (2)
#define BBPCOMM_ABB0_LINE_CONTROL_CMD_TX_abb0_mode_sel_tx_cmd_END            (4)


/*****************************************************************************
 结构名    : BBPCOMM_CPU_RX0_TX0_CKG_BYPASS_UNION
 结构说明  : CPU_RX0_TX0_CKG_BYPASS 寄存器结构定义。地址偏移量:0x1220，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      cpu_rx0_tx0_ckg_bypass_reg;
    struct
    {
        unsigned int  cpu_rx0_lte_ch0_ckg_bypass : 1;  /* bit[0]    : L模cc0通道0 RX ABB随路时钟门控旁路信号 */
        unsigned int  cpu_rx0_tds_ckg_bypass     : 1;  /* bit[1]    : TDS通道0 RX ABB随路时钟门控旁路信号 */
        unsigned int  cpu_rx0_w_ckg_bypass       : 1;  /* bit[2]    : W模通道0 RX ABB随路时钟门控旁路信号 */
        unsigned int  cpu_rx0_g1_ckg_bypass      : 1;  /* bit[3]    : G1通道0 RX ABB随路时钟门控旁路信号 */
        unsigned int  cpu_rx0_g2_ckg_bypass      : 1;  /* bit[4]    : G2通道0 RX ABB随路时钟门控旁路信号 */
        unsigned int  cpu_tx0_lte_ch0_ckg_bypass : 1;  /* bit[5]    : L模cc0通道0 TX ABB随路时钟门控旁路信号 */
        unsigned int  cpu_tx0_tds_ckg_bypass     : 1;  /* bit[6]    : TDS通道0 TX ABB随路时钟门控旁路信号 */
        unsigned int  cpu_tx0_w_ckg_bypass       : 1;  /* bit[7]    : W模通道0 TX ABB随路时钟门控旁路信号 */
        unsigned int  cpu_tx0_g1_ckg_bypass      : 1;  /* bit[8]    : G1通道0 TX ABB随路时钟门控旁路信号 */
        unsigned int  cpu_tx0_g2_ckg_bypass      : 1;  /* bit[9]    : G2通道0 TX ABB随路时钟门控旁路信号 */
        unsigned int  cpu_rx0_c_ckg_bypass       : 1;  /* bit[10]   : C2模通道0 RX ABB随路时钟门控旁路信号 */
        unsigned int  cpu_tx0_c_ckg_bypass       : 1;  /* bit[11]   : C2模通道0 TX ABB随路时钟门控旁路信号 */
        unsigned int  reserved                   : 20; /* bit[12-31]: 保留 */
    } reg;
} BBPCOMM_CPU_RX0_TX0_CKG_BYPASS_UNION;
#define BBPCOMM_CPU_RX0_TX0_CKG_BYPASS_cpu_rx0_lte_ch0_ckg_bypass_START  (0)
#define BBPCOMM_CPU_RX0_TX0_CKG_BYPASS_cpu_rx0_lte_ch0_ckg_bypass_END    (0)
#define BBPCOMM_CPU_RX0_TX0_CKG_BYPASS_cpu_rx0_tds_ckg_bypass_START      (1)
#define BBPCOMM_CPU_RX0_TX0_CKG_BYPASS_cpu_rx0_tds_ckg_bypass_END        (1)
#define BBPCOMM_CPU_RX0_TX0_CKG_BYPASS_cpu_rx0_w_ckg_bypass_START        (2)
#define BBPCOMM_CPU_RX0_TX0_CKG_BYPASS_cpu_rx0_w_ckg_bypass_END          (2)
#define BBPCOMM_CPU_RX0_TX0_CKG_BYPASS_cpu_rx0_g1_ckg_bypass_START       (3)
#define BBPCOMM_CPU_RX0_TX0_CKG_BYPASS_cpu_rx0_g1_ckg_bypass_END         (3)
#define BBPCOMM_CPU_RX0_TX0_CKG_BYPASS_cpu_rx0_g2_ckg_bypass_START       (4)
#define BBPCOMM_CPU_RX0_TX0_CKG_BYPASS_cpu_rx0_g2_ckg_bypass_END         (4)
#define BBPCOMM_CPU_RX0_TX0_CKG_BYPASS_cpu_tx0_lte_ch0_ckg_bypass_START  (5)
#define BBPCOMM_CPU_RX0_TX0_CKG_BYPASS_cpu_tx0_lte_ch0_ckg_bypass_END    (5)
#define BBPCOMM_CPU_RX0_TX0_CKG_BYPASS_cpu_tx0_tds_ckg_bypass_START      (6)
#define BBPCOMM_CPU_RX0_TX0_CKG_BYPASS_cpu_tx0_tds_ckg_bypass_END        (6)
#define BBPCOMM_CPU_RX0_TX0_CKG_BYPASS_cpu_tx0_w_ckg_bypass_START        (7)
#define BBPCOMM_CPU_RX0_TX0_CKG_BYPASS_cpu_tx0_w_ckg_bypass_END          (7)
#define BBPCOMM_CPU_RX0_TX0_CKG_BYPASS_cpu_tx0_g1_ckg_bypass_START       (8)
#define BBPCOMM_CPU_RX0_TX0_CKG_BYPASS_cpu_tx0_g1_ckg_bypass_END         (8)
#define BBPCOMM_CPU_RX0_TX0_CKG_BYPASS_cpu_tx0_g2_ckg_bypass_START       (9)
#define BBPCOMM_CPU_RX0_TX0_CKG_BYPASS_cpu_tx0_g2_ckg_bypass_END         (9)
#define BBPCOMM_CPU_RX0_TX0_CKG_BYPASS_cpu_rx0_c_ckg_bypass_START        (10)
#define BBPCOMM_CPU_RX0_TX0_CKG_BYPASS_cpu_rx0_c_ckg_bypass_END          (10)
#define BBPCOMM_CPU_RX0_TX0_CKG_BYPASS_cpu_tx0_c_ckg_bypass_START        (11)
#define BBPCOMM_CPU_RX0_TX0_CKG_BYPASS_cpu_tx0_c_ckg_bypass_END          (11)


/*****************************************************************************
 结构名    : BBPCOMM_C0_SECOND_MODE_IND_SEL_UNION
 结构说明  : C0_SECOND_MODE_IND_SEL 寄存器结构定义。地址偏移量:0x1224，初值:0x00000000，宽度:32
 寄存器说明: 主模0对应的从模（从模0）的模式指示寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c0_second_mode_ind_sel_reg;
    struct
    {
        unsigned int  c0_second_mode_ind_sel : 1;  /* bit[0]   : 接收主模0对应从模生效时刻
                                                                 0：在int0生效
                                                                 1：立即生效
                                                                 调试用 */
        unsigned int  reserved               : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_C0_SECOND_MODE_IND_SEL_UNION;
#define BBPCOMM_C0_SECOND_MODE_IND_SEL_c0_second_mode_ind_sel_START  (0)
#define BBPCOMM_C0_SECOND_MODE_IND_SEL_c0_second_mode_ind_sel_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_C1_AFC_PDM_SELECT_MASK_UNION
 结构说明  : C1_AFC_PDM_SELECT_MASK 寄存器结构定义。地址偏移量:0x1230，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c1_afc_pdm_select_mask_reg;
    struct
    {
        unsigned int  c1_afc_pdm_select_mask : 4;  /* bit[0-3] : 通道1 AFC控制信号来源。
                                                                 4'b0000，受主模控制；
                                                                 4'b0010，强制受W模控制；
                                                                 4'b0011，强制受TDS模控制；
                                                                 4'b0100，强制受Gm模控制；
                                                                 4'b0101，强制受Gs模控制；
                                                                 4'b0110，强制受C模控制；
                                                                 4'b1000，强制受L模控制；
                                                                 其它，无效。
                                                                 调试用。 */
        unsigned int  reserved               : 28; /* bit[4-31]: 保留 */
    } reg;
} BBPCOMM_C1_AFC_PDM_SELECT_MASK_UNION;
#define BBPCOMM_C1_AFC_PDM_SELECT_MASK_c1_afc_pdm_select_mask_START  (0)
#define BBPCOMM_C1_AFC_PDM_SELECT_MASK_c1_afc_pdm_select_mask_END    (3)


/*****************************************************************************
 结构名    : BBPCOMM_C1_ANT_SWITCH_PA_SELECT_MASK_UNION
 结构说明  : C1_ANT_SWITCH_PA_SELECT_MASK 寄存器结构定义。地址偏移量:0x1234，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c1_ant_switch_pa_select_mask_reg;
    struct
    {
        unsigned int  c1_ant_switch_pa_select_mask : 4;  /* bit[0-3] : 通道1 天线开关和PA控制信号来源。
                                                                       4'b0000，受主模控制；
                                                                       4'b0010，强制受W模控制；
                                                                       4'b0011，强制受TDS模控制；
                                                                       4'b0100，强制受Gm模控制；
                                                                       4'b0101，强制受Gs模控制；
                                                                       4'b0110，强制受C模控制；
                                                                       4'b1000，强制受L模控制；
                                                                       其它，无效。
                                                                       调试用。 */
        unsigned int  reserved                     : 28; /* bit[4-31]: 保留 */
    } reg;
} BBPCOMM_C1_ANT_SWITCH_PA_SELECT_MASK_UNION;
#define BBPCOMM_C1_ANT_SWITCH_PA_SELECT_MASK_c1_ant_switch_pa_select_mask_START  (0)
#define BBPCOMM_C1_ANT_SWITCH_PA_SELECT_MASK_c1_ant_switch_pa_select_mask_END    (3)


/*****************************************************************************
 结构名    : BBPCOMM_C1_RFIC_SELECT_MASK_UNION
 结构说明  : C1_RFIC_SELECT_MASK 寄存器结构定义。地址偏移量:0x1238，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c1_rfic_select_mask_reg;
    struct
    {
        unsigned int  c1_rfic_select_mask : 4;  /* bit[0-3] : 通道1 RFIC控制信号来源（包括线控和SSI）。
                                                              4'b0000，受主模控制；
                                                              4'b0010，强制受W模控制；
                                                              4'b0011，强制受TDS模控制；
                                                              4'b0100，强制受Gm模控制；
                                                              4'b0101，强制受Gs模控制；
                                                              4'b0110，强制受C模控制；
                                                              4'b1000，强制受L模1CC控制；
                                                              4'b1001，强制受L模2CC控制；
                                                              4'b1010，强制受L模3CC控制；
                                                              4'b1011，强制受L模4CC控制；
                                                              其它，无效。
                                                              调试用。 */
        unsigned int  reserved            : 28; /* bit[4-31]: 保留 */
    } reg;
} BBPCOMM_C1_RFIC_SELECT_MASK_UNION;
#define BBPCOMM_C1_RFIC_SELECT_MASK_c1_rfic_select_mask_START  (0)
#define BBPCOMM_C1_RFIC_SELECT_MASK_c1_rfic_select_mask_END    (3)


/*****************************************************************************
 结构名    : BBPCOMM_C1_MIPI_SELECT_MASK_UNION
 结构说明  : C1_MIPI_SELECT_MASK 寄存器结构定义。地址偏移量:0x123C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c1_mipi_select_mask_reg;
    struct
    {
        unsigned int  c1_mipi_select_mask : 4;  /* bit[0-3] : 通道1 MIPI控制信号来源。
                                                              4'b0000，受主模控制；
                                                              4'b0010，强制受W模控制；
                                                              4'b0011，强制受TDS模控制；
                                                              4'b0100，强制受Gm模控制；
                                                              4'b0101，强制受Gs模控制；
                                                              4'b0110，强制受C模控制；
                                                              4'b1000，强制受L模CC0控制；
                                                              4'b1001，强制受L模CC1控制；
                                                              4'b1010，强制受L模CC2控制；
                                                              4'b1011，强制受L模CC3控制；
                                                              其它，无效。
                                                              调试用。 */
        unsigned int  reserved            : 28; /* bit[4-31]: 保留 */
    } reg;
} BBPCOMM_C1_MIPI_SELECT_MASK_UNION;
#define BBPCOMM_C1_MIPI_SELECT_MASK_c1_mipi_select_mask_START  (0)
#define BBPCOMM_C1_MIPI_SELECT_MASK_c1_mipi_select_mask_END    (3)


/*****************************************************************************
 结构名    : BBPCOMM_C1_ABB_RX_SELECT_MASK_UNION
 结构说明  : C1_ABB_RX_SELECT_MASK 寄存器结构定义。地址偏移量:0x1240，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c1_abb_rx_select_mask_reg;
    struct
    {
        unsigned int  c1_abb_rx_select_mask : 4;  /* bit[0-3] : 通道1 ABB控制信号来源。
                                                                4'b0000，受主模控制；
                                                                4'b0010，强制受W模控制；
                                                                4'b0011，强制受TDS模控制；
                                                                4'b0100，强制受Gm模控制；
                                                                4'b0101，强制受Gs模控制；
                                                                4'b0110，强制受C模控制；
                                                                4'b1000，强制受L模CC0控制；
                                                                4'b1001，强制受L模CC1控制；
                                                                4'b1010，强制受L模CC2控制；
                                                                4'b1011，强制受L模CC3控制；
                                                                其它，无效。
                                                                调试用。 */
        unsigned int  reserved              : 28; /* bit[4-31]: 保留 */
    } reg;
} BBPCOMM_C1_ABB_RX_SELECT_MASK_UNION;
#define BBPCOMM_C1_ABB_RX_SELECT_MASK_c1_abb_rx_select_mask_START  (0)
#define BBPCOMM_C1_ABB_RX_SELECT_MASK_c1_abb_rx_select_mask_END    (3)


/*****************************************************************************
 结构名    : BBPCOMM_ABB1_LINE_CONTROL_CMD_RX_UNION
 结构说明  : ABB1_LINE_CONTROL_CMD_RX 寄存器结构定义。地址偏移量:0x1244，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      abb1_line_control_cmd_rx_reg;
    struct
    {
        unsigned int  abb1_line_control_cmd_sel_rx : 1;  /* bit[0-0] : ABB1线控强配模式：
                                                                       1：表示软件强配，此时上述各个强配才生效；
                                                                       0：表示由CTU根据各BBP产生。
                                                                       默认值为0。
                                                                       测试用。 */
        unsigned int  abb1_mode_sel_rx_cmd         : 3;  /* bit[1-3] : 软件强配模式abb1_mode_sel_rx. */
        unsigned int  abb1_rxa_en_cmd              : 1;  /* bit[4-4] : 软件强配模式abb1_rxa_en. */
        unsigned int  abb1_rxb_en_cmd              : 1;  /* bit[5-5] : 软件强配模式abb1_rxb_en. */
        unsigned int  abb1_blka_en_cmd             : 1;  /* bit[6-6] : 软件强配模式abb1_rxa_blk_en. */
        unsigned int  abb1_blkb_en_cmd             : 1;  /* bit[7-7] : 软件强配模式abb1_rxb_blk_en. */
        unsigned int  reserved                     : 24; /* bit[8-31]: 保留 */
    } reg;
} BBPCOMM_ABB1_LINE_CONTROL_CMD_RX_UNION;
#define BBPCOMM_ABB1_LINE_CONTROL_CMD_RX_abb1_line_control_cmd_sel_rx_START  (0)
#define BBPCOMM_ABB1_LINE_CONTROL_CMD_RX_abb1_line_control_cmd_sel_rx_END    (0)
#define BBPCOMM_ABB1_LINE_CONTROL_CMD_RX_abb1_mode_sel_rx_cmd_START          (1)
#define BBPCOMM_ABB1_LINE_CONTROL_CMD_RX_abb1_mode_sel_rx_cmd_END            (3)
#define BBPCOMM_ABB1_LINE_CONTROL_CMD_RX_abb1_rxa_en_cmd_START               (4)
#define BBPCOMM_ABB1_LINE_CONTROL_CMD_RX_abb1_rxa_en_cmd_END                 (4)
#define BBPCOMM_ABB1_LINE_CONTROL_CMD_RX_abb1_rxb_en_cmd_START               (5)
#define BBPCOMM_ABB1_LINE_CONTROL_CMD_RX_abb1_rxb_en_cmd_END                 (5)
#define BBPCOMM_ABB1_LINE_CONTROL_CMD_RX_abb1_blka_en_cmd_START              (6)
#define BBPCOMM_ABB1_LINE_CONTROL_CMD_RX_abb1_blka_en_cmd_END                (6)
#define BBPCOMM_ABB1_LINE_CONTROL_CMD_RX_abb1_blkb_en_cmd_START              (7)
#define BBPCOMM_ABB1_LINE_CONTROL_CMD_RX_abb1_blkb_en_cmd_END                (7)


/*****************************************************************************
 结构名    : BBPCOMM_ABB1_LINE_CONTROL_CMD_TX_UNION
 结构说明  : ABB1_LINE_CONTROL_CMD_TX 寄存器结构定义。地址偏移量:0x1248，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      abb1_line_control_cmd_tx_reg;
    struct
    {
        unsigned int  abb1_line_control_cmd_sel_tx : 1;  /* bit[0-0] : ABB1线控强配模式：
                                                                       1：表示软件强配，此时上述各个强配才生效；
                                                                       0：表示由CTU根据各BBP产生。
                                                                       默认值为0。
                                                                       测试用。 */
        unsigned int  abb1_tx_en_cmd               : 1;  /* bit[1-1] : 软件强配模式abb1_tx_en. */
        unsigned int  abb1_mode_sel_tx_cmd         : 3;  /* bit[2-4] : 软件强配模式abb1_mode_sel_tx. */
        unsigned int  reserved                     : 27; /* bit[5-31]: 保留 */
    } reg;
} BBPCOMM_ABB1_LINE_CONTROL_CMD_TX_UNION;
#define BBPCOMM_ABB1_LINE_CONTROL_CMD_TX_abb1_line_control_cmd_sel_tx_START  (0)
#define BBPCOMM_ABB1_LINE_CONTROL_CMD_TX_abb1_line_control_cmd_sel_tx_END    (0)
#define BBPCOMM_ABB1_LINE_CONTROL_CMD_TX_abb1_tx_en_cmd_START                (1)
#define BBPCOMM_ABB1_LINE_CONTROL_CMD_TX_abb1_tx_en_cmd_END                  (1)
#define BBPCOMM_ABB1_LINE_CONTROL_CMD_TX_abb1_mode_sel_tx_cmd_START          (2)
#define BBPCOMM_ABB1_LINE_CONTROL_CMD_TX_abb1_mode_sel_tx_cmd_END            (4)


/*****************************************************************************
 结构名    : BBPCOMM_CPU_RX1_TX1_CKG_BYPASS_UNION
 结构说明  : CPU_RX1_TX1_CKG_BYPASS 寄存器结构定义。地址偏移量:0x1250，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      cpu_rx1_tx1_ckg_bypass_reg;
    struct
    {
        unsigned int  cpu_rx1_lte_ch1_ckg_bypass : 1;  /* bit[0]    : L模cc1通道1 RX ABB随路时钟门控旁路信号 */
        unsigned int  cpu_rx1_tds_ckg_bypass     : 1;  /* bit[1]    : TDS通道1 RX ABB随路时钟门控旁路信号 */
        unsigned int  cpu_rx1_w_ckg_bypass       : 1;  /* bit[2]    : W模通道1 RX ABB随路时钟门控旁路信号 */
        unsigned int  cpu_rx1_g1_ckg_bypass      : 1;  /* bit[3]    : G1通道1 RX ABB随路时钟门控旁路信号 */
        unsigned int  cpu_rx1_g2_ckg_bypass      : 1;  /* bit[4]    : G2通道1 RX ABB随路时钟门控旁路信号 */
        unsigned int  cpu_tx1_lte_ch1_ckg_bypass : 1;  /* bit[5]    : L模cc1通道1 TX ABB随路时钟门控旁路信号 */
        unsigned int  cpu_tx1_tds_ckg_bypass     : 1;  /* bit[6]    : TDS通道1 TX ABB随路时钟门控旁路信号 */
        unsigned int  cpu_tx1_w_ckg_bypass       : 1;  /* bit[7]    : W模通道1 TX ABB随路时钟门控旁路信号 */
        unsigned int  cpu_tx1_g1_ckg_bypass      : 1;  /* bit[8]    : G1通道1 TX ABB随路时钟门控旁路信号 */
        unsigned int  cpu_tx1_g2_ckg_bypass      : 1;  /* bit[9]    : G2通道1 TX ABB随路时钟门控旁路信号 */
        unsigned int  cpu_rx1_c_ckg_bypass       : 1;  /* bit[10]   : C2模通道1 RX ABB随路时钟门控旁路信号 */
        unsigned int  cpu_tx1_c_ckg_bypass       : 1;  /* bit[11]   : C2模通道1 TX ABB随路时钟门控旁路信号 */
        unsigned int  reserved                   : 20; /* bit[12-31]: 保留 */
    } reg;
} BBPCOMM_CPU_RX1_TX1_CKG_BYPASS_UNION;
#define BBPCOMM_CPU_RX1_TX1_CKG_BYPASS_cpu_rx1_lte_ch1_ckg_bypass_START  (0)
#define BBPCOMM_CPU_RX1_TX1_CKG_BYPASS_cpu_rx1_lte_ch1_ckg_bypass_END    (0)
#define BBPCOMM_CPU_RX1_TX1_CKG_BYPASS_cpu_rx1_tds_ckg_bypass_START      (1)
#define BBPCOMM_CPU_RX1_TX1_CKG_BYPASS_cpu_rx1_tds_ckg_bypass_END        (1)
#define BBPCOMM_CPU_RX1_TX1_CKG_BYPASS_cpu_rx1_w_ckg_bypass_START        (2)
#define BBPCOMM_CPU_RX1_TX1_CKG_BYPASS_cpu_rx1_w_ckg_bypass_END          (2)
#define BBPCOMM_CPU_RX1_TX1_CKG_BYPASS_cpu_rx1_g1_ckg_bypass_START       (3)
#define BBPCOMM_CPU_RX1_TX1_CKG_BYPASS_cpu_rx1_g1_ckg_bypass_END         (3)
#define BBPCOMM_CPU_RX1_TX1_CKG_BYPASS_cpu_rx1_g2_ckg_bypass_START       (4)
#define BBPCOMM_CPU_RX1_TX1_CKG_BYPASS_cpu_rx1_g2_ckg_bypass_END         (4)
#define BBPCOMM_CPU_RX1_TX1_CKG_BYPASS_cpu_tx1_lte_ch1_ckg_bypass_START  (5)
#define BBPCOMM_CPU_RX1_TX1_CKG_BYPASS_cpu_tx1_lte_ch1_ckg_bypass_END    (5)
#define BBPCOMM_CPU_RX1_TX1_CKG_BYPASS_cpu_tx1_tds_ckg_bypass_START      (6)
#define BBPCOMM_CPU_RX1_TX1_CKG_BYPASS_cpu_tx1_tds_ckg_bypass_END        (6)
#define BBPCOMM_CPU_RX1_TX1_CKG_BYPASS_cpu_tx1_w_ckg_bypass_START        (7)
#define BBPCOMM_CPU_RX1_TX1_CKG_BYPASS_cpu_tx1_w_ckg_bypass_END          (7)
#define BBPCOMM_CPU_RX1_TX1_CKG_BYPASS_cpu_tx1_g1_ckg_bypass_START       (8)
#define BBPCOMM_CPU_RX1_TX1_CKG_BYPASS_cpu_tx1_g1_ckg_bypass_END         (8)
#define BBPCOMM_CPU_RX1_TX1_CKG_BYPASS_cpu_tx1_g2_ckg_bypass_START       (9)
#define BBPCOMM_CPU_RX1_TX1_CKG_BYPASS_cpu_tx1_g2_ckg_bypass_END         (9)
#define BBPCOMM_CPU_RX1_TX1_CKG_BYPASS_cpu_rx1_c_ckg_bypass_START        (10)
#define BBPCOMM_CPU_RX1_TX1_CKG_BYPASS_cpu_rx1_c_ckg_bypass_END          (10)
#define BBPCOMM_CPU_RX1_TX1_CKG_BYPASS_cpu_tx1_c_ckg_bypass_START        (11)
#define BBPCOMM_CPU_RX1_TX1_CKG_BYPASS_cpu_tx1_c_ckg_bypass_END          (11)


/*****************************************************************************
 结构名    : BBPCOMM_C1_SECOND_MODE_IND_SEL_UNION
 结构说明  : C1_SECOND_MODE_IND_SEL 寄存器结构定义。地址偏移量:0x1254，初值:0x00000000，宽度:32
 寄存器说明: 主模1对应的从模（从模1）的模式指示寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c1_second_mode_ind_sel_reg;
    struct
    {
        unsigned int  c1_second_mode_ind_sel : 1;  /* bit[0]   : 接收主模1对应从模生效时刻
                                                                 0：在int0生效
                                                                 1：立即生效
                                                                 调试用 */
        unsigned int  reserved               : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_C1_SECOND_MODE_IND_SEL_UNION;
#define BBPCOMM_C1_SECOND_MODE_IND_SEL_c1_second_mode_ind_sel_START  (0)
#define BBPCOMM_C1_SECOND_MODE_IND_SEL_c1_second_mode_ind_sel_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_C2_AFC_PDM_SELECT_MASK_UNION
 结构说明  : C2_AFC_PDM_SELECT_MASK 寄存器结构定义。地址偏移量:0x1260，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c2_afc_pdm_select_mask_reg;
    struct
    {
        unsigned int  c2_afc_pdm_select_mask : 4;  /* bit[0-3] : 通道2 AFC控制信号来源。
                                                                 4'b0000，受主模控制；
                                                                 4'b0010，强制受W模控制；
                                                                 4'b0011，强制受TDS模控制；
                                                                 4'b0100，强制受Gm模控制；
                                                                 4'b0101，强制受Gs模控制；
                                                                 4'b0110，强制受C模控制；
                                                                 4'b1000，强制受L模控制；
                                                                 其它，无效。
                                                                 调试用。 */
        unsigned int  reserved               : 28; /* bit[4-31]: 保留 */
    } reg;
} BBPCOMM_C2_AFC_PDM_SELECT_MASK_UNION;
#define BBPCOMM_C2_AFC_PDM_SELECT_MASK_c2_afc_pdm_select_mask_START  (0)
#define BBPCOMM_C2_AFC_PDM_SELECT_MASK_c2_afc_pdm_select_mask_END    (3)


/*****************************************************************************
 结构名    : BBPCOMM_C2_ANT_SWITCH_PA_SELECT_MASK_UNION
 结构说明  : C2_ANT_SWITCH_PA_SELECT_MASK 寄存器结构定义。地址偏移量:0x1264，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c2_ant_switch_pa_select_mask_reg;
    struct
    {
        unsigned int  c2_ant_switch_pa_select_mask : 4;  /* bit[0-3] : 通道2 天线开关和PA控制信号来源。
                                                                       4'b0000，受主模控制；
                                                                       4'b0010，强制受W模控制；
                                                                       4'b0011，强制受TDS模控制；
                                                                       4'b0100，强制受Gm模控制；
                                                                       4'b0101，强制受Gs模控制；
                                                                       4'b0110，强制受C模控制；
                                                                       4'b1000，强制受L模控制；
                                                                       其它，无效。
                                                                       调试用。 */
        unsigned int  reserved                     : 28; /* bit[4-31]: 保留 */
    } reg;
} BBPCOMM_C2_ANT_SWITCH_PA_SELECT_MASK_UNION;
#define BBPCOMM_C2_ANT_SWITCH_PA_SELECT_MASK_c2_ant_switch_pa_select_mask_START  (0)
#define BBPCOMM_C2_ANT_SWITCH_PA_SELECT_MASK_c2_ant_switch_pa_select_mask_END    (3)


/*****************************************************************************
 结构名    : BBPCOMM_C2_RFIC_SELECT_MASK_UNION
 结构说明  : C2_RFIC_SELECT_MASK 寄存器结构定义。地址偏移量:0x1268，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c2_rfic_select_mask_reg;
    struct
    {
        unsigned int  c2_rfic_select_mask : 4;  /* bit[0-3] : 通道2 RFIC控制信号来源（包括线控和SSI）。
                                                              4'b0000，受主模控制；
                                                              4'b0010，强制受W模控制；
                                                              4'b0011，强制受TDS模控制；
                                                              4'b0100，强制受Gm模控制；
                                                              4'b0101，强制受Gs模控制；
                                                              4'b0110，强制受C模控制；
                                                              4'b1000，强制受L模1CC控制；
                                                              4'b1001，强制受L模2CC控制；
                                                              4'b1010，强制受L模3CC控制；
                                                              4'b1011，强制受L模4CC控制；
                                                              其它，无效。
                                                              调试用。 */
        unsigned int  reserved            : 28; /* bit[4-31]: 保留 */
    } reg;
} BBPCOMM_C2_RFIC_SELECT_MASK_UNION;
#define BBPCOMM_C2_RFIC_SELECT_MASK_c2_rfic_select_mask_START  (0)
#define BBPCOMM_C2_RFIC_SELECT_MASK_c2_rfic_select_mask_END    (3)


/*****************************************************************************
 结构名    : BBPCOMM_C2_MIPI_SELECT_MASK_UNION
 结构说明  : C2_MIPI_SELECT_MASK 寄存器结构定义。地址偏移量:0x126C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c2_mipi_select_mask_reg;
    struct
    {
        unsigned int  c2_mipi_select_mask : 4;  /* bit[0-3] : 通道2 MIPI控制信号来源。
                                                              4'b0000，受主模控制；
                                                              4'b0010，强制受W模控制；
                                                              4'b0011，强制受TDS模控制；
                                                              4'b0100，强制受Gm模控制；
                                                              4'b0101，强制受Gs模控制；
                                                              4'b0110，强制受C模控制；
                                                              4'b1000，强制受L模1CC控制；
                                                              4'b1001，强制受L模2CC控制；
                                                              4'b1010，强制受L模3CC控制；
                                                              4'b1011，强制受L模4CC控制；
                                                              其它，无效。
                                                              调试用。 */
        unsigned int  reserved            : 28; /* bit[4-31]: 保留 */
    } reg;
} BBPCOMM_C2_MIPI_SELECT_MASK_UNION;
#define BBPCOMM_C2_MIPI_SELECT_MASK_c2_mipi_select_mask_START  (0)
#define BBPCOMM_C2_MIPI_SELECT_MASK_c2_mipi_select_mask_END    (3)


/*****************************************************************************
 结构名    : BBPCOMM_C2_ABB_RX_SELECT_MASK_UNION
 结构说明  : C2_ABB_RX_SELECT_MASK 寄存器结构定义。地址偏移量:0x1270，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c2_abb_rx_select_mask_reg;
    struct
    {
        unsigned int  c2_abb_rx_select_mask : 4;  /* bit[0-3] : 通道2 ABB接收控制信号来源。
                                                                4'b0000，受主模控制；
                                                                4'b0010，强制受W模控制；
                                                                4'b0011，强制受TDS模控制；
                                                                4'b0100，强制受Gm模控制；
                                                                4'b0101，强制受Gs模控制；
                                                                4'b0110，强制受C模控制；
                                                                4'b1000，强制受L模1CC控制；
                                                                4'b1001，强制受L模2CC控制；
                                                                4'b1010，强制受L模3CC控制；
                                                                4'b1011，强制受L模4CC控制；
                                                                其它，无效。
                                                                调试用。 */
        unsigned int  reserved              : 28; /* bit[4-31]: 保留 */
    } reg;
} BBPCOMM_C2_ABB_RX_SELECT_MASK_UNION;
#define BBPCOMM_C2_ABB_RX_SELECT_MASK_c2_abb_rx_select_mask_START  (0)
#define BBPCOMM_C2_ABB_RX_SELECT_MASK_c2_abb_rx_select_mask_END    (3)


/*****************************************************************************
 结构名    : BBPCOMM_ABB2_LINE_CONTROL_CMD_RX_UNION
 结构说明  : ABB2_LINE_CONTROL_CMD_RX 寄存器结构定义。地址偏移量:0x1274，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      abb2_line_control_cmd_rx_reg;
    struct
    {
        unsigned int  abb2_line_control_cmd_sel_rx : 1;  /* bit[0-0] : ABB2线控强配模式：
                                                                       1：表示软件强配，此时上述各个强配才生效；
                                                                       0：表示由CTU根据各BBP产生。
                                                                       默认值为0。
                                                                       测试用。 */
        unsigned int  abb2_mode_sel_rx_cmd         : 3;  /* bit[1-3] : 软件强配模式abb2_mode_sel_rx. */
        unsigned int  abb2_rxa_en_cmd              : 1;  /* bit[4-4] : 软件强配模式abb2_rxa_en. */
        unsigned int  abb2_rxb_en_cmd              : 1;  /* bit[5-5] : 软件强配模式abb2_rxb_en. */
        unsigned int  abb2_blka_en_cmd             : 1;  /* bit[6-6] : 软件强配模式abb2_rxa_blk_en. */
        unsigned int  abb2_blkb_en_cmd             : 1;  /* bit[7-7] : 软件强配模式abb2_rxb_blk_en. */
        unsigned int  reserved                     : 24; /* bit[8-31]: 保留 */
    } reg;
} BBPCOMM_ABB2_LINE_CONTROL_CMD_RX_UNION;
#define BBPCOMM_ABB2_LINE_CONTROL_CMD_RX_abb2_line_control_cmd_sel_rx_START  (0)
#define BBPCOMM_ABB2_LINE_CONTROL_CMD_RX_abb2_line_control_cmd_sel_rx_END    (0)
#define BBPCOMM_ABB2_LINE_CONTROL_CMD_RX_abb2_mode_sel_rx_cmd_START          (1)
#define BBPCOMM_ABB2_LINE_CONTROL_CMD_RX_abb2_mode_sel_rx_cmd_END            (3)
#define BBPCOMM_ABB2_LINE_CONTROL_CMD_RX_abb2_rxa_en_cmd_START               (4)
#define BBPCOMM_ABB2_LINE_CONTROL_CMD_RX_abb2_rxa_en_cmd_END                 (4)
#define BBPCOMM_ABB2_LINE_CONTROL_CMD_RX_abb2_rxb_en_cmd_START               (5)
#define BBPCOMM_ABB2_LINE_CONTROL_CMD_RX_abb2_rxb_en_cmd_END                 (5)
#define BBPCOMM_ABB2_LINE_CONTROL_CMD_RX_abb2_blka_en_cmd_START              (6)
#define BBPCOMM_ABB2_LINE_CONTROL_CMD_RX_abb2_blka_en_cmd_END                (6)
#define BBPCOMM_ABB2_LINE_CONTROL_CMD_RX_abb2_blkb_en_cmd_START              (7)
#define BBPCOMM_ABB2_LINE_CONTROL_CMD_RX_abb2_blkb_en_cmd_END                (7)


/*****************************************************************************
 结构名    : BBPCOMM_ABB2_LINE_CONTROL_CMD_TX_UNION
 结构说明  : ABB2_LINE_CONTROL_CMD_TX 寄存器结构定义。地址偏移量:0x1278，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      abb2_line_control_cmd_tx_reg;
    struct
    {
        unsigned int  abb2_line_control_cmd_sel_tx : 1;  /* bit[0-0] : ABB2线控强配模式：
                                                                       1：表示软件强配，此时上述各个强配才生效；
                                                                       0：表示由CTU根据各BBP产生。
                                                                       默认值为0。
                                                                       测试用。 */
        unsigned int  abb2_tx_en_cmd               : 1;  /* bit[1-1] : 软件强配模式abb2_tx_en. */
        unsigned int  abb2_mode_sel_tx_cmd         : 3;  /* bit[2-4] : 软件强配模式abb2_mode_sel_tx. */
        unsigned int  reserved                     : 27; /* bit[5-31]: 保留 */
    } reg;
} BBPCOMM_ABB2_LINE_CONTROL_CMD_TX_UNION;
#define BBPCOMM_ABB2_LINE_CONTROL_CMD_TX_abb2_line_control_cmd_sel_tx_START  (0)
#define BBPCOMM_ABB2_LINE_CONTROL_CMD_TX_abb2_line_control_cmd_sel_tx_END    (0)
#define BBPCOMM_ABB2_LINE_CONTROL_CMD_TX_abb2_tx_en_cmd_START                (1)
#define BBPCOMM_ABB2_LINE_CONTROL_CMD_TX_abb2_tx_en_cmd_END                  (1)
#define BBPCOMM_ABB2_LINE_CONTROL_CMD_TX_abb2_mode_sel_tx_cmd_START          (2)
#define BBPCOMM_ABB2_LINE_CONTROL_CMD_TX_abb2_mode_sel_tx_cmd_END            (4)


/*****************************************************************************
 结构名    : BBPCOMM_CPU_RX2_TX0_CKG_BYPASS_UNION
 结构说明  : CPU_RX2_TX0_CKG_BYPASS 寄存器结构定义。地址偏移量:0x1280，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      cpu_rx2_tx0_ckg_bypass_reg;
    struct
    {
        unsigned int  cpu_rx2_lte_ch2_ckg_bypass : 1;  /* bit[0]    : L模cc2通道2 RX ABB随路时钟门控旁路信号 */
        unsigned int  cpu_rx2_tds_ckg_bypass     : 1;  /* bit[1]    : TDS通道2 RX ABB随路时钟门控旁路信号 */
        unsigned int  cpu_rx2_w_ckg_bypass       : 1;  /* bit[2]    : W模通道2 RX ABB随路时钟门控旁路信号 */
        unsigned int  cpu_rx2_g1_ckg_bypass      : 1;  /* bit[3]    : G1通道2 RX ABB随路时钟门控旁路信号 */
        unsigned int  cpu_rx2_g2_ckg_bypass      : 1;  /* bit[4]    : G2通道2 RX ABB随路时钟门控旁路信号 */
        unsigned int  cpu_tx2_lte_ch2_ckg_bypass : 1;  /* bit[5]    : L模cc2通道2 TX ABB随路时钟门控旁路信号 */
        unsigned int  cpu_tx2_tds_ckg_bypass     : 1;  /* bit[6]    : TDS通道2 TX ABB随路时钟门控旁路信号 */
        unsigned int  cpu_tx2_w_ckg_bypass       : 1;  /* bit[7]    : W模通道2 TX ABB随路时钟门控旁路信号 */
        unsigned int  cpu_tx2_g1_ckg_bypass      : 1;  /* bit[8]    : G1通道2 TX ABB随路时钟门控旁路信号 */
        unsigned int  cpu_tx2_g2_ckg_bypass      : 1;  /* bit[9]    : G2通道2 TX ABB随路时钟门控旁路信号 */
        unsigned int  cpu_rx2_c_ckg_bypass       : 1;  /* bit[10]   : C2模通道2 RX ABB随路时钟门控旁路信号 */
        unsigned int  cpu_tx2_c_ckg_bypass       : 1;  /* bit[11]   : C2模通道2 TX ABB随路时钟门控旁路信号 */
        unsigned int  reserved                   : 20; /* bit[12-31]: 保留 */
    } reg;
} BBPCOMM_CPU_RX2_TX0_CKG_BYPASS_UNION;
#define BBPCOMM_CPU_RX2_TX0_CKG_BYPASS_cpu_rx2_lte_ch2_ckg_bypass_START  (0)
#define BBPCOMM_CPU_RX2_TX0_CKG_BYPASS_cpu_rx2_lte_ch2_ckg_bypass_END    (0)
#define BBPCOMM_CPU_RX2_TX0_CKG_BYPASS_cpu_rx2_tds_ckg_bypass_START      (1)
#define BBPCOMM_CPU_RX2_TX0_CKG_BYPASS_cpu_rx2_tds_ckg_bypass_END        (1)
#define BBPCOMM_CPU_RX2_TX0_CKG_BYPASS_cpu_rx2_w_ckg_bypass_START        (2)
#define BBPCOMM_CPU_RX2_TX0_CKG_BYPASS_cpu_rx2_w_ckg_bypass_END          (2)
#define BBPCOMM_CPU_RX2_TX0_CKG_BYPASS_cpu_rx2_g1_ckg_bypass_START       (3)
#define BBPCOMM_CPU_RX2_TX0_CKG_BYPASS_cpu_rx2_g1_ckg_bypass_END         (3)
#define BBPCOMM_CPU_RX2_TX0_CKG_BYPASS_cpu_rx2_g2_ckg_bypass_START       (4)
#define BBPCOMM_CPU_RX2_TX0_CKG_BYPASS_cpu_rx2_g2_ckg_bypass_END         (4)
#define BBPCOMM_CPU_RX2_TX0_CKG_BYPASS_cpu_tx2_lte_ch2_ckg_bypass_START  (5)
#define BBPCOMM_CPU_RX2_TX0_CKG_BYPASS_cpu_tx2_lte_ch2_ckg_bypass_END    (5)
#define BBPCOMM_CPU_RX2_TX0_CKG_BYPASS_cpu_tx2_tds_ckg_bypass_START      (6)
#define BBPCOMM_CPU_RX2_TX0_CKG_BYPASS_cpu_tx2_tds_ckg_bypass_END        (6)
#define BBPCOMM_CPU_RX2_TX0_CKG_BYPASS_cpu_tx2_w_ckg_bypass_START        (7)
#define BBPCOMM_CPU_RX2_TX0_CKG_BYPASS_cpu_tx2_w_ckg_bypass_END          (7)
#define BBPCOMM_CPU_RX2_TX0_CKG_BYPASS_cpu_tx2_g1_ckg_bypass_START       (8)
#define BBPCOMM_CPU_RX2_TX0_CKG_BYPASS_cpu_tx2_g1_ckg_bypass_END         (8)
#define BBPCOMM_CPU_RX2_TX0_CKG_BYPASS_cpu_tx2_g2_ckg_bypass_START       (9)
#define BBPCOMM_CPU_RX2_TX0_CKG_BYPASS_cpu_tx2_g2_ckg_bypass_END         (9)
#define BBPCOMM_CPU_RX2_TX0_CKG_BYPASS_cpu_rx2_c_ckg_bypass_START        (10)
#define BBPCOMM_CPU_RX2_TX0_CKG_BYPASS_cpu_rx2_c_ckg_bypass_END          (10)
#define BBPCOMM_CPU_RX2_TX0_CKG_BYPASS_cpu_tx2_c_ckg_bypass_START        (11)
#define BBPCOMM_CPU_RX2_TX0_CKG_BYPASS_cpu_tx2_c_ckg_bypass_END          (11)


/*****************************************************************************
 结构名    : BBPCOMM_C2_SECOND_MODE_IND_SEL_UNION
 结构说明  : C2_SECOND_MODE_IND_SEL 寄存器结构定义。地址偏移量:0x1284，初值:0x00000000，宽度:32
 寄存器说明: 主模2对应的从模（从模2）的模式指示寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c2_second_mode_ind_sel_reg;
    struct
    {
        unsigned int  c2_second_mode_ind_sel : 1;  /* bit[0]   : 接收主模2对应从模生效时刻
                                                                 0：在int0生效
                                                                 1：立即生效
                                                                 调试用 */
        unsigned int  reserved               : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_C2_SECOND_MODE_IND_SEL_UNION;
#define BBPCOMM_C2_SECOND_MODE_IND_SEL_c2_second_mode_ind_sel_START  (0)
#define BBPCOMM_C2_SECOND_MODE_IND_SEL_c2_second_mode_ind_sel_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_C3_AFC_PDM_SELECT_MASK_UNION
 结构说明  : C3_AFC_PDM_SELECT_MASK 寄存器结构定义。地址偏移量:0x1290，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c3_afc_pdm_select_mask_reg;
    struct
    {
        unsigned int  c3_afc_pdm_select_mask : 4;  /* bit[0-3] : 通道3 AFC控制信号来源。
                                                                 4'b0000，受主模控制；
                                                                 4'b0010，强制受W模控制；
                                                                 4'b0011，强制受TDS模控制；
                                                                 4'b0100，强制受Gm模控制；
                                                                 4'b0101，强制受Gs模控制；
                                                                 4'b0110，强制受C模控制；
                                                                 4'b1000，强制受L模控制；
                                                                 其它，无效。
                                                                 调试用。 */
        unsigned int  reserved               : 28; /* bit[4-31]: 保留 */
    } reg;
} BBPCOMM_C3_AFC_PDM_SELECT_MASK_UNION;
#define BBPCOMM_C3_AFC_PDM_SELECT_MASK_c3_afc_pdm_select_mask_START  (0)
#define BBPCOMM_C3_AFC_PDM_SELECT_MASK_c3_afc_pdm_select_mask_END    (3)


/*****************************************************************************
 结构名    : BBPCOMM_C3_ANT_SWITCH_PA_SELECT_MASK_UNION
 结构说明  : C3_ANT_SWITCH_PA_SELECT_MASK 寄存器结构定义。地址偏移量:0x1294，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c3_ant_switch_pa_select_mask_reg;
    struct
    {
        unsigned int  c3_ant_switch_pa_select_mask : 4;  /* bit[0-3] : 通道3 天线开关和PA控制信号来源。
                                                                       4'b0000，受主模控制；
                                                                       4'b0010，强制受W模控制；
                                                                       4'b0011，强制受TDS模控制；
                                                                       4'b0100，强制受Gm模控制；
                                                                       4'b0101，强制受Gs模控制；
                                                                       4'b0110，强制受C模控制；
                                                                       4'b1000，强制受L模控制；
                                                                       其它，无效。
                                                                       调试用。 */
        unsigned int  reserved                     : 28; /* bit[4-31]: 保留 */
    } reg;
} BBPCOMM_C3_ANT_SWITCH_PA_SELECT_MASK_UNION;
#define BBPCOMM_C3_ANT_SWITCH_PA_SELECT_MASK_c3_ant_switch_pa_select_mask_START  (0)
#define BBPCOMM_C3_ANT_SWITCH_PA_SELECT_MASK_c3_ant_switch_pa_select_mask_END    (3)


/*****************************************************************************
 结构名    : BBPCOMM_C3_RFIC_SELECT_MASK_UNION
 结构说明  : C3_RFIC_SELECT_MASK 寄存器结构定义。地址偏移量:0x1298，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c3_rfic_select_mask_reg;
    struct
    {
        unsigned int  c3_rfic_select_mask : 4;  /* bit[0-3] : 通道3 RFIC控制信号来源（包括线控和SSI）。
                                                              4'b0000，受主模控制；
                                                              4'b0010，强制受W模控制；
                                                              4'b0011，强制受TDS模控制；
                                                              4'b0100，强制受Gm模控制；
                                                              4'b0101，强制受Gs模控制；
                                                              4'b0110，强制受C模控制；
                                                              4'b1000，强制受L模1CC控制；
                                                              4'b1001，强制受L模2CC控制；
                                                              4'b1010，强制受L模3CC控制；
                                                              4'b1011，强制受L模4CC控制；
                                                              其它，无效。
                                                              调试用。 */
        unsigned int  reserved            : 28; /* bit[4-31]: 保留 */
    } reg;
} BBPCOMM_C3_RFIC_SELECT_MASK_UNION;
#define BBPCOMM_C3_RFIC_SELECT_MASK_c3_rfic_select_mask_START  (0)
#define BBPCOMM_C3_RFIC_SELECT_MASK_c3_rfic_select_mask_END    (3)


/*****************************************************************************
 结构名    : BBPCOMM_C3_MIPI_SELECT_MASK_UNION
 结构说明  : C3_MIPI_SELECT_MASK 寄存器结构定义。地址偏移量:0x129C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c3_mipi_select_mask_reg;
    struct
    {
        unsigned int  c3_mipi_select_mask : 4;  /* bit[0-3] : 通道3 MIPI控制信号来源。
                                                              4'b0000，受主模控制；
                                                              4'b0010，强制受W模控制；
                                                              4'b0011，强制受TDS模控制；
                                                              4'b0100，强制受Gm模控制；
                                                              4'b0101，强制受Gs模控制；
                                                              4'b0110，强制受C模控制；
                                                              4'b1000，强制受L模CC0控制；
                                                              4'b1001，强制受L模CC1控制；
                                                              4'b1010，强制受L模CC2控制；
                                                              4'b1011，强制受L模CC3控制；
                                                              其它，无效。
                                                              调试用。 */
        unsigned int  reserved            : 28; /* bit[4-31]: 保留 */
    } reg;
} BBPCOMM_C3_MIPI_SELECT_MASK_UNION;
#define BBPCOMM_C3_MIPI_SELECT_MASK_c3_mipi_select_mask_START  (0)
#define BBPCOMM_C3_MIPI_SELECT_MASK_c3_mipi_select_mask_END    (3)


/*****************************************************************************
 结构名    : BBPCOMM_C3_ABB_RX_SELECT_MASK_UNION
 结构说明  : C3_ABB_RX_SELECT_MASK 寄存器结构定义。地址偏移量:0x12A0，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c3_abb_rx_select_mask_reg;
    struct
    {
        unsigned int  c3_abb_rx_select_mask : 4;  /* bit[0-3] : 通道3 ABB接收控制信号来源。
                                                                4'b0000，受主模控制；
                                                                4'b0010，强制受W模控制；
                                                                4'b0011，强制受TDS模控制；
                                                                4'b0100，强制受Gm模控制；
                                                                4'b0101，强制受Gs模控制；
                                                                4'b0110，强制受C模控制；
                                                                4'b1000，强制受L模CC0控制；
                                                                4'b1001，强制受L模CC1控制；
                                                                4'b1010，强制受L模CC2控制；
                                                                4'b1011，强制受L模CC3控制；
                                                                其它，无效。
                                                                调试用。 */
        unsigned int  reserved              : 28; /* bit[4-31]: 保留 */
    } reg;
} BBPCOMM_C3_ABB_RX_SELECT_MASK_UNION;
#define BBPCOMM_C3_ABB_RX_SELECT_MASK_c3_abb_rx_select_mask_START  (0)
#define BBPCOMM_C3_ABB_RX_SELECT_MASK_c3_abb_rx_select_mask_END    (3)


/*****************************************************************************
 结构名    : BBPCOMM_ABB3_LINE_CONTROL_CMD_RX_UNION
 结构说明  : ABB3_LINE_CONTROL_CMD_RX 寄存器结构定义。地址偏移量:0x12A4，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      abb3_line_control_cmd_rx_reg;
    struct
    {
        unsigned int  abb3_line_control_cmd_sel_rx : 1;  /* bit[0-0] : ABB3线控强配模式：
                                                                       1：表示软件强配，此时上述各个强配才生效；
                                                                       0：表示由CTU根据各BBP产生。
                                                                       默认值为0。
                                                                       测试用。 */
        unsigned int  abb3_mode_sel_rx_cmd         : 3;  /* bit[1-3] : 软件强配模式abb3_mode_sel_rx. */
        unsigned int  abb3_rxa_en_cmd              : 1;  /* bit[4-4] : 软件强配模式abb3_rxa_en. */
        unsigned int  abb3_rxb_en_cmd              : 1;  /* bit[5-5] : 软件强配模式abb3_rxb_en. */
        unsigned int  abb3_blka_en_cmd             : 1;  /* bit[6-6] : 软件强配模式abb3_rxa_blk_en. */
        unsigned int  abb3_blkb_en_cmd             : 1;  /* bit[7-7] : 软件强配模式abb3_rxb_blk_en. */
        unsigned int  reserved                     : 24; /* bit[8-31]: 保留 */
    } reg;
} BBPCOMM_ABB3_LINE_CONTROL_CMD_RX_UNION;
#define BBPCOMM_ABB3_LINE_CONTROL_CMD_RX_abb3_line_control_cmd_sel_rx_START  (0)
#define BBPCOMM_ABB3_LINE_CONTROL_CMD_RX_abb3_line_control_cmd_sel_rx_END    (0)
#define BBPCOMM_ABB3_LINE_CONTROL_CMD_RX_abb3_mode_sel_rx_cmd_START          (1)
#define BBPCOMM_ABB3_LINE_CONTROL_CMD_RX_abb3_mode_sel_rx_cmd_END            (3)
#define BBPCOMM_ABB3_LINE_CONTROL_CMD_RX_abb3_rxa_en_cmd_START               (4)
#define BBPCOMM_ABB3_LINE_CONTROL_CMD_RX_abb3_rxa_en_cmd_END                 (4)
#define BBPCOMM_ABB3_LINE_CONTROL_CMD_RX_abb3_rxb_en_cmd_START               (5)
#define BBPCOMM_ABB3_LINE_CONTROL_CMD_RX_abb3_rxb_en_cmd_END                 (5)
#define BBPCOMM_ABB3_LINE_CONTROL_CMD_RX_abb3_blka_en_cmd_START              (6)
#define BBPCOMM_ABB3_LINE_CONTROL_CMD_RX_abb3_blka_en_cmd_END                (6)
#define BBPCOMM_ABB3_LINE_CONTROL_CMD_RX_abb3_blkb_en_cmd_START              (7)
#define BBPCOMM_ABB3_LINE_CONTROL_CMD_RX_abb3_blkb_en_cmd_END                (7)


/*****************************************************************************
 结构名    : BBPCOMM_ABB3_LINE_CONTROL_CMD_TX_UNION
 结构说明  : ABB3_LINE_CONTROL_CMD_TX 寄存器结构定义。地址偏移量:0x12A8，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      abb3_line_control_cmd_tx_reg;
    struct
    {
        unsigned int  abb3_line_control_cmd_sel_tx : 1;  /* bit[0-0] : ABB3线控强配模式：
                                                                       1：表示软件强配，此时上述各个强配才生效；
                                                                       0：表示由CTU根据各BBP产生。
                                                                       默认值为0。
                                                                       测试用。 */
        unsigned int  abb3_tx_en_cmd               : 1;  /* bit[1-1] : 软件强配模式abb3_tx_en. */
        unsigned int  abb3_mode_sel_tx_cmd         : 3;  /* bit[2-4] : 软件强配模式abb3_mode_sel_tx. */
        unsigned int  reserved                     : 27; /* bit[5-31]: 保留 */
    } reg;
} BBPCOMM_ABB3_LINE_CONTROL_CMD_TX_UNION;
#define BBPCOMM_ABB3_LINE_CONTROL_CMD_TX_abb3_line_control_cmd_sel_tx_START  (0)
#define BBPCOMM_ABB3_LINE_CONTROL_CMD_TX_abb3_line_control_cmd_sel_tx_END    (0)
#define BBPCOMM_ABB3_LINE_CONTROL_CMD_TX_abb3_tx_en_cmd_START                (1)
#define BBPCOMM_ABB3_LINE_CONTROL_CMD_TX_abb3_tx_en_cmd_END                  (1)
#define BBPCOMM_ABB3_LINE_CONTROL_CMD_TX_abb3_mode_sel_tx_cmd_START          (2)
#define BBPCOMM_ABB3_LINE_CONTROL_CMD_TX_abb3_mode_sel_tx_cmd_END            (4)


/*****************************************************************************
 结构名    : BBPCOMM_CPU_RX3_TX3_CKG_BYPASS_UNION
 结构说明  : CPU_RX3_TX3_CKG_BYPASS 寄存器结构定义。地址偏移量:0x12B0，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      cpu_rx3_tx3_ckg_bypass_reg;
    struct
    {
        unsigned int  cpu_rx3_lte_ch3_ckg_bypass : 1;  /* bit[0]    : L模cc3通道3 RX ABB随路时钟门控旁路信号 */
        unsigned int  cpu_rx3_tds_ckg_bypass     : 1;  /* bit[1]    : TDS通道3 RX ABB随路时钟门控旁路信号 */
        unsigned int  cpu_rx3_w_ckg_bypass       : 1;  /* bit[2]    : W模通道3 RX ABB随路时钟门控旁路信号 */
        unsigned int  cpu_rx3_g1_ckg_bypass      : 1;  /* bit[3]    : G1通道3 RX ABB随路时钟门控旁路信号 */
        unsigned int  cpu_rx3_g2_ckg_bypass      : 1;  /* bit[4]    : G2通道3 RX ABB随路时钟门控旁路信号 */
        unsigned int  cpu_tx3_lte_ch3_ckg_bypass : 1;  /* bit[5]    : L模cc3通道3 TX ABB随路时钟门控旁路信号 */
        unsigned int  cpu_tx3_tds_ckg_bypass     : 1;  /* bit[6]    : TDS通道3 TX ABB随路时钟门控旁路信号 */
        unsigned int  cpu_tx3_w_ckg_bypass       : 1;  /* bit[7]    : W模通道3 TX ABB随路时钟门控旁路信号 */
        unsigned int  cpu_tx3_g1_ckg_bypass      : 1;  /* bit[8]    : G1通道3 TX ABB随路时钟门控旁路信号 */
        unsigned int  cpu_tx3_g2_ckg_bypass      : 1;  /* bit[9]    : G2通道3 TX ABB随路时钟门控旁路信号 */
        unsigned int  cpu_rx3_c_ckg_bypass       : 1;  /* bit[10]   : C2模通道3 RX ABB随路时钟门控旁路信号 */
        unsigned int  cpu_tx3_c_ckg_bypass       : 1;  /* bit[11]   : C2模通道3 TX ABB随路时钟门控旁路信号 */
        unsigned int  reserved                   : 20; /* bit[12-31]: 保留 */
    } reg;
} BBPCOMM_CPU_RX3_TX3_CKG_BYPASS_UNION;
#define BBPCOMM_CPU_RX3_TX3_CKG_BYPASS_cpu_rx3_lte_ch3_ckg_bypass_START  (0)
#define BBPCOMM_CPU_RX3_TX3_CKG_BYPASS_cpu_rx3_lte_ch3_ckg_bypass_END    (0)
#define BBPCOMM_CPU_RX3_TX3_CKG_BYPASS_cpu_rx3_tds_ckg_bypass_START      (1)
#define BBPCOMM_CPU_RX3_TX3_CKG_BYPASS_cpu_rx3_tds_ckg_bypass_END        (1)
#define BBPCOMM_CPU_RX3_TX3_CKG_BYPASS_cpu_rx3_w_ckg_bypass_START        (2)
#define BBPCOMM_CPU_RX3_TX3_CKG_BYPASS_cpu_rx3_w_ckg_bypass_END          (2)
#define BBPCOMM_CPU_RX3_TX3_CKG_BYPASS_cpu_rx3_g1_ckg_bypass_START       (3)
#define BBPCOMM_CPU_RX3_TX3_CKG_BYPASS_cpu_rx3_g1_ckg_bypass_END         (3)
#define BBPCOMM_CPU_RX3_TX3_CKG_BYPASS_cpu_rx3_g2_ckg_bypass_START       (4)
#define BBPCOMM_CPU_RX3_TX3_CKG_BYPASS_cpu_rx3_g2_ckg_bypass_END         (4)
#define BBPCOMM_CPU_RX3_TX3_CKG_BYPASS_cpu_tx3_lte_ch3_ckg_bypass_START  (5)
#define BBPCOMM_CPU_RX3_TX3_CKG_BYPASS_cpu_tx3_lte_ch3_ckg_bypass_END    (5)
#define BBPCOMM_CPU_RX3_TX3_CKG_BYPASS_cpu_tx3_tds_ckg_bypass_START      (6)
#define BBPCOMM_CPU_RX3_TX3_CKG_BYPASS_cpu_tx3_tds_ckg_bypass_END        (6)
#define BBPCOMM_CPU_RX3_TX3_CKG_BYPASS_cpu_tx3_w_ckg_bypass_START        (7)
#define BBPCOMM_CPU_RX3_TX3_CKG_BYPASS_cpu_tx3_w_ckg_bypass_END          (7)
#define BBPCOMM_CPU_RX3_TX3_CKG_BYPASS_cpu_tx3_g1_ckg_bypass_START       (8)
#define BBPCOMM_CPU_RX3_TX3_CKG_BYPASS_cpu_tx3_g1_ckg_bypass_END         (8)
#define BBPCOMM_CPU_RX3_TX3_CKG_BYPASS_cpu_tx3_g2_ckg_bypass_START       (9)
#define BBPCOMM_CPU_RX3_TX3_CKG_BYPASS_cpu_tx3_g2_ckg_bypass_END         (9)
#define BBPCOMM_CPU_RX3_TX3_CKG_BYPASS_cpu_rx3_c_ckg_bypass_START        (10)
#define BBPCOMM_CPU_RX3_TX3_CKG_BYPASS_cpu_rx3_c_ckg_bypass_END          (10)
#define BBPCOMM_CPU_RX3_TX3_CKG_BYPASS_cpu_tx3_c_ckg_bypass_START        (11)
#define BBPCOMM_CPU_RX3_TX3_CKG_BYPASS_cpu_tx3_c_ckg_bypass_END          (11)


/*****************************************************************************
 结构名    : BBPCOMM_C3_SECOND_MODE_IND_SEL_UNION
 结构说明  : C3_SECOND_MODE_IND_SEL 寄存器结构定义。地址偏移量:0x12B4，初值:0x00000000，宽度:32
 寄存器说明: 主模3对应的从模（从模3）的模式指示寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c3_second_mode_ind_sel_reg;
    struct
    {
        unsigned int  c3_second_mode_ind_sel : 1;  /* bit[0]   : 接收主模3对应从模生效时刻
                                                                 0：在int0生效
                                                                 1：立即生效
                                                                 调试用 */
        unsigned int  reserved               : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_C3_SECOND_MODE_IND_SEL_UNION;
#define BBPCOMM_C3_SECOND_MODE_IND_SEL_c3_second_mode_ind_sel_START  (0)
#define BBPCOMM_C3_SECOND_MODE_IND_SEL_c3_second_mode_ind_sel_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_LTEBBP_INPUT_MASK_UNION
 结构说明  : LTEBBP_INPUT_MASK 寄存器结构定义。地址偏移量:0x1300，初值:0x00000003，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      ltebbp_input_mask_reg;
    struct
    {
        unsigned int  ltebbp_input_mask : 2;  /* bit[0-1] : 电平信号，低有效。
                                                            当LTE主模需要做异系统测量时需配置本寄存器为3，异系统测量结束后配置本寄存器为0。
                                                            bit1:1’b0: lte_intrasys_valid输入无效，被强制为1。
                                                            bit0:1’b0:
                                                            lte_intersys_ingap_pre_ind输入无效，被强制为0。
                                                            bit[1:0] = 11b: 让lte_intrasys_valid和lte_intersys_ingap_pre_ind输入有效。
                                                            
                                                            配置时刻：LTE主模需要做异系统测量时需配置本寄存器为3，异系统测量结束后配置本寄存器为0。
                                                            生效时刻：立即生效 */
        unsigned int  reserved          : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_LTEBBP_INPUT_MASK_UNION;
#define BBPCOMM_LTEBBP_INPUT_MASK_ltebbp_input_mask_START  (0)
#define BBPCOMM_LTEBBP_INPUT_MASK_ltebbp_input_mask_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_WBBP_INPUT_MASK_UNION
 结构说明  : WBBP_INPUT_MASK 寄存器结构定义。地址偏移量:0x1304，初值:0x00000003，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      wbbp_input_mask_reg;
    struct
    {
        unsigned int  wbbp_input_mask : 2;  /* bit[0-1] : 电平信号，低有效。
                                                          当W主模需要做异系统测量时需配置本寄存器为3，异系统测量结束后配置本寄存器为0。
                                                          bit1:1’b0:
                                                           让w_intrasys_valid输入无效，被强制为1。
                                                          bit0:1’b0:
                                                          w_intersys_ingap_pre_ind输入无效，被强制为0。
                                                          bit[1:0] = 11b: 让w_intrasys_valid和w_intersys_ingap_pre_ind输入有效。
                                                          
                                                          配置时刻：W主模需要做异系统测量时需配置本寄存器为3，异系统测量结束后配置本寄存器为0。
                                                          生效时刻：立即生效 */
        unsigned int  reserved        : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_WBBP_INPUT_MASK_UNION;
#define BBPCOMM_WBBP_INPUT_MASK_wbbp_input_mask_START  (0)
#define BBPCOMM_WBBP_INPUT_MASK_wbbp_input_mask_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_GMBBP_INPUT_MASK_UNION
 结构说明  : GMBBP_INPUT_MASK 寄存器结构定义。地址偏移量:0x1308，初值:0x00000003，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      gmbbp_input_mask_reg;
    struct
    {
        unsigned int  gmbbp_input_mask : 2;  /* bit[0-1] : 电平信号，低有效。
                                                           当Gm主模需要做异系统测量时需配置本寄存器为3，异系统测量结束后配置本寄存器为0。
                                                           bit1:1’b0:
                                                            让gm_intrasys_valid输入无效，被强制为1。
                                                           bit0:1’b0:
                                                           gm_intersys_ingap_pre_ind输入无效，被强制为0。
                                                           bit[1:0] = 11b: 让gm_intrasys_valid和gm_intersys_ingap_pre_ind输入有效。
                                                           
                                                           配置时刻：Gm主模需要做异系统测量时需配置本寄存器为3，异系统测量结束后配置本寄存器为0。
                                                           生效时刻：立即生效 */
        unsigned int  reserved         : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_GMBBP_INPUT_MASK_UNION;
#define BBPCOMM_GMBBP_INPUT_MASK_gmbbp_input_mask_START  (0)
#define BBPCOMM_GMBBP_INPUT_MASK_gmbbp_input_mask_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_GSBBP_INPUT_MASK_UNION
 结构说明  : GSBBP_INPUT_MASK 寄存器结构定义。地址偏移量:0x130C，初值:0x00000003，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      gsbbp_input_mask_reg;
    struct
    {
        unsigned int  gsbbp_input_mask : 2;  /* bit[0-1] : 电平信号，低有效。
                                                           当Gs主模需要做异系统测量时需配置本寄存器为3，异系统测量结束后配置本寄存器为0。
                                                           bit1:1’b0:
                                                            让gs_intrasys_valid输入无效，被强制为1。
                                                           bit0:1’b0:
                                                           gs_intersys_ingap_pre_ind输入无效，被强制为0。
                                                           bit[1:0] = 11b: 让gs_intrasys_valid和gs_intersys_ingap_pre_ind输入有效。
                                                           
                                                           配置时刻：Gs主模需要做异系统测量时需配置本寄存器为3，异系统测量结束后配置本寄存器为0。
                                                           生效时刻：立即生效 */
        unsigned int  reserved         : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_GSBBP_INPUT_MASK_UNION;
#define BBPCOMM_GSBBP_INPUT_MASK_gsbbp_input_mask_START  (0)
#define BBPCOMM_GSBBP_INPUT_MASK_gsbbp_input_mask_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_TDSBBP_INPUT_MASK_UNION
 结构说明  : TDSBBP_INPUT_MASK 寄存器结构定义。地址偏移量:0x1310，初值:0x00000003，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      tdsbbp_input_mask_reg;
    struct
    {
        unsigned int  tdsbbp_input_mask : 2;  /* bit[0-1] : 电平信号，低有效。
                                                            当TDS主模需要做异系统测量时需配置本寄存器为3，异系统测量结束后配置本寄存器为0。
                                                            bit1:1’b0:
                                                             让tds_intrasys_valid输入无效，被强制为1。
                                                            bit0:1’b0:
                                                            tds_intersys_ingap_pre_ind输入无效，被强制为0。
                                                            bit[1:0] = 11b: 让tds_intrasys_valid和tds_intersys_ingap_pre_ind输入有效。
                                                            
                                                            配置时刻：TDS主模需要做异系统测量时需配置本寄存器为3，异系统测量结束后配置本寄存器为0。
                                                            生效时刻：立即生效 */
        unsigned int  reserved          : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_TDSBBP_INPUT_MASK_UNION;
#define BBPCOMM_TDSBBP_INPUT_MASK_tdsbbp_input_mask_START  (0)
#define BBPCOMM_TDSBBP_INPUT_MASK_tdsbbp_input_mask_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_CBBP_INPUT_MASK_UNION
 结构说明  : CBBP_INPUT_MASK 寄存器结构定义。地址偏移量:0x1314，初值:0x00000003，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      cbbp_input_mask_reg;
    struct
    {
        unsigned int  cbbp_input_mask : 2;  /* bit[0-1] : 电平信号，低有效。
                                                          当C主模需要做异系统测量时需配置本寄存器为3，异系统测量结束后配置本寄存器为0。
                                                          bit1:1’b0:
                                                           让c_intrasys_valid输入无效，被强制为1。
                                                          bit0:1’b0:
                                                          c_intersys_ingap_pre_ind输入无效，被强制为0。
                                                          bit[1:0] = 11b: 让c_intrasys_valid和c_intersys_ingap_pre_ind输入有效。
                                                          配置时刻：TDS主模需要做异系统测量时需配置本寄存器为3，异系统测量结束后配置本寄存器为0。
                                                          生效时刻：立即生效 */
        unsigned int  reserved        : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_CBBP_INPUT_MASK_UNION;
#define BBPCOMM_CBBP_INPUT_MASK_cbbp_input_mask_START  (0)
#define BBPCOMM_CBBP_INPUT_MASK_cbbp_input_mask_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_MIPI_ROBIN_CLR_IND_IMI_UNION
 结构说明  : MIPI_ROBIN_CLR_IND_IMI 寄存器结构定义。地址偏移量:0x1318，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      mipi_robin_clr_ind_imi_reg;
    struct
    {
        unsigned int  mipi_robin_clr_ind_imi : 1;  /* bit[0]   : MIPI轮询请求清零信号，1：清除清零信号，0：无效 */
        unsigned int  reserved               : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_MIPI_ROBIN_CLR_IND_IMI_UNION;
#define BBPCOMM_MIPI_ROBIN_CLR_IND_IMI_mipi_robin_clr_ind_imi_START  (0)
#define BBPCOMM_MIPI_ROBIN_CLR_IND_IMI_mipi_robin_clr_ind_imi_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_SSI_ROBIN_CLR_IND_IMI_UNION
 结构说明  : SSI_ROBIN_CLR_IND_IMI 寄存器结构定义。地址偏移量:0x131C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      ssi_robin_clr_ind_imi_reg;
    struct
    {
        unsigned int  ssi_robin_clr_ind_imi : 1;  /* bit[0]   : SSI轮询请求清零信号，1：清除清零信号，0：无效 */
        unsigned int  reserved              : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_SSI_ROBIN_CLR_IND_IMI_UNION;
#define BBPCOMM_SSI_ROBIN_CLR_IND_IMI_ssi_robin_clr_ind_imi_START  (0)
#define BBPCOMM_SSI_ROBIN_CLR_IND_IMI_ssi_robin_clr_ind_imi_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_W_INTRASYS_VALID_UNION
 结构说明  : W_INTRASYS_VALID 寄存器结构定义。地址偏移量:0x1320，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      w_intrasys_valid_reg;
    struct
    {
        unsigned int  o_w_intrasys_valid       : 1;  /* bit[0]   : w主模下控制RF指示，电平信号。
                                                                   1’b0: W放弃RF控制权。
                                                                   1’b1: W享有控制RF权（但实际配置RF需w_intrasys_valid_delay信号为1）。 */
        unsigned int  o_w_intrasys_valid_delay : 1;  /* bit[1]   : w主模下实际控制RF指示，电平信号。为1代表W控制RF配置通道，为0代表从模可以控制RF通道。用于单RFIC时射频控制相关信号的选通。
                                                                   w_intrasys_valid_delay的上升沿比w_intrasys_valid上升沿滞后，下降沿一致。 */
        unsigned int  reserved                 : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_W_INTRASYS_VALID_UNION;
#define BBPCOMM_W_INTRASYS_VALID_o_w_intrasys_valid_START        (0)
#define BBPCOMM_W_INTRASYS_VALID_o_w_intrasys_valid_END          (0)
#define BBPCOMM_W_INTRASYS_VALID_o_w_intrasys_valid_delay_START  (1)
#define BBPCOMM_W_INTRASYS_VALID_o_w_intrasys_valid_delay_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_GM_INTRASYS_VALID_UNION
 结构说明  : GM_INTRASYS_VALID 寄存器结构定义。地址偏移量:0x1324，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      gm_intrasys_valid_reg;
    struct
    {
        unsigned int  o_gm_intrasys_valid       : 1;  /* bit[0]   : gm主模下控制RF指示，电平信号。
                                                                    1’b0: gm放弃RF控制权。
                                                                    1’b1: gm享有控制RF权（但实际配置RF需gm_intrasys_valid_delay信号为1）。 */
        unsigned int  o_gm_intrasys_valid_delay : 1;  /* bit[1]   : gm主模下实际控制RF指示，电平信号。为1代表gm控制RF配置通道，为0代表从模可以控制RF通道。用于单RFIC时射频控制相关信号的选通。
                                                                    gm_intrasys_valid_delay的上升沿比gm_intrasys_valid上升沿滞后，下降沿一致。 */
        unsigned int  reserved                  : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_GM_INTRASYS_VALID_UNION;
#define BBPCOMM_GM_INTRASYS_VALID_o_gm_intrasys_valid_START        (0)
#define BBPCOMM_GM_INTRASYS_VALID_o_gm_intrasys_valid_END          (0)
#define BBPCOMM_GM_INTRASYS_VALID_o_gm_intrasys_valid_delay_START  (1)
#define BBPCOMM_GM_INTRASYS_VALID_o_gm_intrasys_valid_delay_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_GS_INTRASYS_VALID_UNION
 结构说明  : GS_INTRASYS_VALID 寄存器结构定义。地址偏移量:0x1328，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      gs_intrasys_valid_reg;
    struct
    {
        unsigned int  o_gs_intrasys_valid       : 1;  /* bit[0]   : gs主模下控制RF指示，电平信号。
                                                                    1’b0: gs放弃RF控制权。
                                                                    1’b1: gs享有控制RF权（但实际配置RF需gs_intrasys_valid_delay信号为1）。 */
        unsigned int  o_gs_intrasys_valid_delay : 1;  /* bit[1]   : gs主模下实际控制RF指示，电平信号。为1代表gs控制RF配置通道，为0代表从模可以控制RF通道。用于单RFIC时射频控制相关信号的选通。
                                                                    gs_intrasys_valid_delay的上升沿比gs_intrasys_valid上升沿滞后，下降沿一致。 */
        unsigned int  reserved                  : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_GS_INTRASYS_VALID_UNION;
#define BBPCOMM_GS_INTRASYS_VALID_o_gs_intrasys_valid_START        (0)
#define BBPCOMM_GS_INTRASYS_VALID_o_gs_intrasys_valid_END          (0)
#define BBPCOMM_GS_INTRASYS_VALID_o_gs_intrasys_valid_delay_START  (1)
#define BBPCOMM_GS_INTRASYS_VALID_o_gs_intrasys_valid_delay_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_LTE_INTRASYS_VALID_UNION
 结构说明  : LTE_INTRASYS_VALID 寄存器结构定义。地址偏移量:0x132C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      lte_intrasys_valid_reg;
    struct
    {
        unsigned int  o_lte_intrasys_valid       : 1;  /* bit[0]   : Lte主模下控制RF指示，电平信号。
                                                                     1’b0: LTE放弃RF控制权。
                                                                     1’b1: LTE享有控制RF权（但实际配置RF需lte_intrasys_valid_delay信号为1）。 */
        unsigned int  o_lte_intrasys_valid_delay : 1;  /* bit[1]   : LTE主模下实际控制RF指示，电平信号。为1代表LTE控制RF配置通道，为0代表从模可以控制RF通道。用于单RFIC时射频控制相关信号的选通。
                                                                     lte_intrasys_valid_delay的上升沿比lte_intrasys_valid上升沿滞后，下降沿一致。 */
        unsigned int  reserved                   : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_LTE_INTRASYS_VALID_UNION;
#define BBPCOMM_LTE_INTRASYS_VALID_o_lte_intrasys_valid_START        (0)
#define BBPCOMM_LTE_INTRASYS_VALID_o_lte_intrasys_valid_END          (0)
#define BBPCOMM_LTE_INTRASYS_VALID_o_lte_intrasys_valid_delay_START  (1)
#define BBPCOMM_LTE_INTRASYS_VALID_o_lte_intrasys_valid_delay_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_TDS_INTRASYS_VALID_UNION
 结构说明  : TDS_INTRASYS_VALID 寄存器结构定义。地址偏移量:0x1330，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      tds_intrasys_valid_reg;
    struct
    {
        unsigned int  o_tds_intrasys_valid       : 1;  /* bit[0]   : TDS主模下控制RF指示，电平信号。
                                                                     1’b0: TDS放弃RF控制权。
                                                                     1’b1: TDS享有控制RF权（但实际配置RF需tds_intrasys_valid_delay信号为1）。 */
        unsigned int  o_tds_intrasys_valid_delay : 1;  /* bit[1]   : TDS主模下实际控制RF指示，电平信号。为1代表TDS控制RF配置通道，为0代表从模可以控制RF通道。用于单RFIC时射频控制相关信号的选通。
                                                                     tds_intrasys_valid_delay的上升沿比tds_intrasys_valid上升沿滞后，下降沿一致。 */
        unsigned int  reserved                   : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_TDS_INTRASYS_VALID_UNION;
#define BBPCOMM_TDS_INTRASYS_VALID_o_tds_intrasys_valid_START        (0)
#define BBPCOMM_TDS_INTRASYS_VALID_o_tds_intrasys_valid_END          (0)
#define BBPCOMM_TDS_INTRASYS_VALID_o_tds_intrasys_valid_delay_START  (1)
#define BBPCOMM_TDS_INTRASYS_VALID_o_tds_intrasys_valid_delay_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_C_INTRASYS_VALID_UNION
 结构说明  : C_INTRASYS_VALID 寄存器结构定义。地址偏移量:0x1334，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c_intrasys_valid_reg;
    struct
    {
        unsigned int  o_c_intrasys_valid       : 1;  /* bit[0]   : w主模下控制RF指示，电平信号。
                                                                   1’b0: W放弃RF控制权。
                                                                   1’b1: W享有控制RF权（但实际配置RF需w_intrasys_valid_delay信号为1）。 */
        unsigned int  o_c_intrasys_valid_delay : 1;  /* bit[1]   : c2主模下实际控制RF指示，电平信号。为1代表C控制RF配置通道，为0代表从模可以控制RF通道。用于单RFIC时射频控制相关信号的选通。
                                                                   c_intrasys_valid_delay的上升沿比c_intrasys_valid上升沿滞后，下降沿一致。 */
        unsigned int  reserved                 : 30; /* bit[2-31]: 保留 */
    } reg;
} BBPCOMM_C_INTRASYS_VALID_UNION;
#define BBPCOMM_C_INTRASYS_VALID_o_c_intrasys_valid_START        (0)
#define BBPCOMM_C_INTRASYS_VALID_o_c_intrasys_valid_END          (0)
#define BBPCOMM_C_INTRASYS_VALID_o_c_intrasys_valid_delay_START  (1)
#define BBPCOMM_C_INTRASYS_VALID_o_c_intrasys_valid_delay_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_INT0_TIME_CIRCLE_UNION
 结构说明  : INT0_TIME_CIRCLE 寄存器结构定义。地址偏移量:0x1338，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      int0_time_circle_reg;
    struct
    {
        unsigned int  int0_time_circle : 1;  /* bit[0]   : 软中断int0生效时刻转圈指示 */
        unsigned int  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_INT0_TIME_CIRCLE_UNION;
#define BBPCOMM_INT0_TIME_CIRCLE_int0_time_circle_START  (0)
#define BBPCOMM_INT0_TIME_CIRCLE_int0_time_circle_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_CH0_RX_EN_FORCE_LOW_CNT_UNION
 结构说明  : CH0_RX_EN_FORCE_LOW_CNT 寄存器结构定义。地址偏移量:0x1370，初值:0x00000100，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      ch0_rx_en_force_low_cnt_reg;
    struct
    {
        unsigned int  ch0_rx_en_force_low_cnt : 12; /* bit[0-11] : ch0的com2abb_line_ctrl_mode切换时，com2abb_rxa/b_en强制拉低的时间。
                                                                   单位：工作时钟 */
        unsigned int  reserved                : 20; /* bit[12-31]: 保留 */
    } reg;
} BBPCOMM_CH0_RX_EN_FORCE_LOW_CNT_UNION;
#define BBPCOMM_CH0_RX_EN_FORCE_LOW_CNT_ch0_rx_en_force_low_cnt_START  (0)
#define BBPCOMM_CH0_RX_EN_FORCE_LOW_CNT_ch0_rx_en_force_low_cnt_END    (11)


/*****************************************************************************
 结构名    : BBPCOMM_CH1_RX_EN_FORCE_LOW_CNT_UNION
 结构说明  : CH1_RX_EN_FORCE_LOW_CNT 寄存器结构定义。地址偏移量:0x1374，初值:0x00000100，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      ch1_rx_en_force_low_cnt_reg;
    struct
    {
        unsigned int  ch1_rx_en_force_low_cnt : 12; /* bit[0-11] : ch1的com2abb_line_ctrl_mode切换时，com2abb_rxa/b_en强制拉低的时间。
                                                                   单位：工作时钟 */
        unsigned int  reserved                : 20; /* bit[12-31]: 保留 */
    } reg;
} BBPCOMM_CH1_RX_EN_FORCE_LOW_CNT_UNION;
#define BBPCOMM_CH1_RX_EN_FORCE_LOW_CNT_ch1_rx_en_force_low_cnt_START  (0)
#define BBPCOMM_CH1_RX_EN_FORCE_LOW_CNT_ch1_rx_en_force_low_cnt_END    (11)


/*****************************************************************************
 结构名    : BBPCOMM_CH2_RX_EN_FORCE_LOW_CNT_UNION
 结构说明  : CH2_RX_EN_FORCE_LOW_CNT 寄存器结构定义。地址偏移量:0x1378，初值:0x00000100，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      ch2_rx_en_force_low_cnt_reg;
    struct
    {
        unsigned int  ch2_rx_en_force_low_cnt : 12; /* bit[0-11] : ch2的com2abb_line_ctrl_mode切换时，com2abb_rxa/b_en强制拉低的时间。
                                                                   单位：工作时钟 */
        unsigned int  reserved                : 20; /* bit[12-31]: 保留 */
    } reg;
} BBPCOMM_CH2_RX_EN_FORCE_LOW_CNT_UNION;
#define BBPCOMM_CH2_RX_EN_FORCE_LOW_CNT_ch2_rx_en_force_low_cnt_START  (0)
#define BBPCOMM_CH2_RX_EN_FORCE_LOW_CNT_ch2_rx_en_force_low_cnt_END    (11)


/*****************************************************************************
 结构名    : BBPCOMM_CH3_RX_EN_FORCE_LOW_CNT_UNION
 结构说明  : CH3_RX_EN_FORCE_LOW_CNT 寄存器结构定义。地址偏移量:0x137C，初值:0x00000100，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      ch3_rx_en_force_low_cnt_reg;
    struct
    {
        unsigned int  ch3_rx_en_force_low_cnt : 12; /* bit[0-11] : ch3的com2abb_line_ctrl_mode切换时，com2abb_rxa/b_en强制拉低的时间。
                                                                   单位：工作时钟 */
        unsigned int  reserved                : 20; /* bit[12-31]: 保留 */
    } reg;
} BBPCOMM_CH3_RX_EN_FORCE_LOW_CNT_UNION;
#define BBPCOMM_CH3_RX_EN_FORCE_LOW_CNT_ch3_rx_en_force_low_cnt_START  (0)
#define BBPCOMM_CH3_RX_EN_FORCE_LOW_CNT_ch3_rx_en_force_low_cnt_END    (11)


/*****************************************************************************
 结构名    : BBPCOMM_CH0_CLK_MUX_CNT_UNION
 结构说明  : CH0_CLK_MUX_CNT 寄存器结构定义。地址偏移量:0x1380，初值:0x00960096，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      ch0_clk_mux_cnt_reg;
    struct
    {
        unsigned int  ch0_tx_mux_cnt : 16; /* bit[0-15] : 通道0上行模式切换时上行时钟强制为0的时钟数
                                                          单位：工作时钟。 */
        unsigned int  ch0_rx_mux_cnt : 16; /* bit[16-31]: 通道0下行模式切换时下行时钟强制为0的时钟数
                                                          单位：工作时钟。 */
    } reg;
} BBPCOMM_CH0_CLK_MUX_CNT_UNION;
#define BBPCOMM_CH0_CLK_MUX_CNT_ch0_tx_mux_cnt_START  (0)
#define BBPCOMM_CH0_CLK_MUX_CNT_ch0_tx_mux_cnt_END    (15)
#define BBPCOMM_CH0_CLK_MUX_CNT_ch0_rx_mux_cnt_START  (16)
#define BBPCOMM_CH0_CLK_MUX_CNT_ch0_rx_mux_cnt_END    (31)


/*****************************************************************************
 结构名    : BBPCOMM_CH1_CLK_MUX_CNT_UNION
 结构说明  : CH1_CLK_MUX_CNT 寄存器结构定义。地址偏移量:0x1384，初值:0x00960096，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      ch1_clk_mux_cnt_reg;
    struct
    {
        unsigned int  ch1_tx_mux_cnt : 16; /* bit[0-15] : 通道1上行模式切换时上行时钟强制为0的时钟数
                                                          单位：工作时钟。 */
        unsigned int  ch1_rx_mux_cnt : 16; /* bit[16-31]: 通道1下行模式切换时下行时钟强制为0的时钟数
                                                          单位：工作时钟。 */
    } reg;
} BBPCOMM_CH1_CLK_MUX_CNT_UNION;
#define BBPCOMM_CH1_CLK_MUX_CNT_ch1_tx_mux_cnt_START  (0)
#define BBPCOMM_CH1_CLK_MUX_CNT_ch1_tx_mux_cnt_END    (15)
#define BBPCOMM_CH1_CLK_MUX_CNT_ch1_rx_mux_cnt_START  (16)
#define BBPCOMM_CH1_CLK_MUX_CNT_ch1_rx_mux_cnt_END    (31)


/*****************************************************************************
 结构名    : BBPCOMM_CH2_CLK_MUX_CNT_UNION
 结构说明  : CH2_CLK_MUX_CNT 寄存器结构定义。地址偏移量:0x1388，初值:0x00960096，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      ch2_clk_mux_cnt_reg;
    struct
    {
        unsigned int  ch2_tx_mux_cnt : 16; /* bit[0-15] : 通道2上行模式切换时上行时钟强制为0的时钟数
                                                          单位：工作时钟。 */
        unsigned int  ch2_rx_mux_cnt : 16; /* bit[16-31]: 通道2下行模式切换时下行时钟强制为0的时钟数
                                                          单位：工作时钟。 */
    } reg;
} BBPCOMM_CH2_CLK_MUX_CNT_UNION;
#define BBPCOMM_CH2_CLK_MUX_CNT_ch2_tx_mux_cnt_START  (0)
#define BBPCOMM_CH2_CLK_MUX_CNT_ch2_tx_mux_cnt_END    (15)
#define BBPCOMM_CH2_CLK_MUX_CNT_ch2_rx_mux_cnt_START  (16)
#define BBPCOMM_CH2_CLK_MUX_CNT_ch2_rx_mux_cnt_END    (31)


/*****************************************************************************
 结构名    : BBPCOMM_CH3_CLK_MUX_CNT_UNION
 结构说明  : CH3_CLK_MUX_CNT 寄存器结构定义。地址偏移量:0x138C，初值:0x00960096，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      ch3_clk_mux_cnt_reg;
    struct
    {
        unsigned int  ch3_tx_mux_cnt : 16; /* bit[0-15] : 通道3上行模式切换时上行时钟强制为0的时钟数
                                                          单位：工作时钟。 */
        unsigned int  ch3_rx_mux_cnt : 16; /* bit[16-31]: 通道3下行模式切换时下行时钟强制为0的时钟数
                                                          单位：工作时钟。 */
    } reg;
} BBPCOMM_CH3_CLK_MUX_CNT_UNION;
#define BBPCOMM_CH3_CLK_MUX_CNT_ch3_tx_mux_cnt_START  (0)
#define BBPCOMM_CH3_CLK_MUX_CNT_ch3_tx_mux_cnt_END    (15)
#define BBPCOMM_CH3_CLK_MUX_CNT_ch3_rx_mux_cnt_START  (16)
#define BBPCOMM_CH3_CLK_MUX_CNT_ch3_rx_mux_cnt_END    (31)


/*****************************************************************************
 结构名    : BBPCOMM_W_CLK_EN_FORCE_HIGH_CNT_UNION
 结构说明  : W_CLK_EN_FORCE_HIGH_CNT 寄存器结构定义。地址偏移量:0x1390，初值:0x00000010，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      w_clk_en_force_high_cnt_reg;
    struct
    {
        unsigned int  w_clk_en_force_high_cnt : 12; /* bit[0-11] : W模下行随路时钟门控使能强制拉高时钟数，
                                                                   单位：工作时钟。 */
        unsigned int  reserved                : 20; /* bit[12-31]: 保留 */
    } reg;
} BBPCOMM_W_CLK_EN_FORCE_HIGH_CNT_UNION;
#define BBPCOMM_W_CLK_EN_FORCE_HIGH_CNT_w_clk_en_force_high_cnt_START  (0)
#define BBPCOMM_W_CLK_EN_FORCE_HIGH_CNT_w_clk_en_force_high_cnt_END    (11)


/*****************************************************************************
 结构名    : BBPCOMM_TDS_CLK_EN_FORCE_HIGH_CNT_UNION
 结构说明  : TDS_CLK_EN_FORCE_HIGH_CNT 寄存器结构定义。地址偏移量:0x1394，初值:0x00000010，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      tds_clk_en_force_high_cnt_reg;
    struct
    {
        unsigned int  tds_clk_en_force_high_cnt : 12; /* bit[0-11] : TDS模下行随路时钟门控使能强制拉高时钟数，
                                                                     单位：工作时钟。 */
        unsigned int  reserved                  : 20; /* bit[12-31]: 保留 */
    } reg;
} BBPCOMM_TDS_CLK_EN_FORCE_HIGH_CNT_UNION;
#define BBPCOMM_TDS_CLK_EN_FORCE_HIGH_CNT_tds_clk_en_force_high_cnt_START  (0)
#define BBPCOMM_TDS_CLK_EN_FORCE_HIGH_CNT_tds_clk_en_force_high_cnt_END    (11)


/*****************************************************************************
 结构名    : BBPCOMM_GM_CLK_EN_FORCE_HIGH_CNT_UNION
 结构说明  : GM_CLK_EN_FORCE_HIGH_CNT 寄存器结构定义。地址偏移量:0x1398，初值:0x00000080，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      gm_clk_en_force_high_cnt_reg;
    struct
    {
        unsigned int  gm_clk_en_force_high_cnt : 12; /* bit[0-11] : GM模下行随路时钟门控使能强制拉高时钟数，
                                                                    单位：工作时钟。 */
        unsigned int  reserved                 : 20; /* bit[12-31]: 保留 */
    } reg;
} BBPCOMM_GM_CLK_EN_FORCE_HIGH_CNT_UNION;
#define BBPCOMM_GM_CLK_EN_FORCE_HIGH_CNT_gm_clk_en_force_high_cnt_START  (0)
#define BBPCOMM_GM_CLK_EN_FORCE_HIGH_CNT_gm_clk_en_force_high_cnt_END    (11)


/*****************************************************************************
 结构名    : BBPCOMM_GS_CLK_EN_FORCE_HIGH_CNT_UNION
 结构说明  : GS_CLK_EN_FORCE_HIGH_CNT 寄存器结构定义。地址偏移量:0x139C，初值:0x00000080，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      gs_clk_en_force_high_cnt_reg;
    struct
    {
        unsigned int  gs_clk_en_force_high_cnt : 12; /* bit[0-11] : GS模下行随路时钟门控使能强制拉高时钟数，
                                                                    单位：工作时钟。 */
        unsigned int  reserved                 : 20; /* bit[12-31]: 保留 */
    } reg;
} BBPCOMM_GS_CLK_EN_FORCE_HIGH_CNT_UNION;
#define BBPCOMM_GS_CLK_EN_FORCE_HIGH_CNT_gs_clk_en_force_high_cnt_START  (0)
#define BBPCOMM_GS_CLK_EN_FORCE_HIGH_CNT_gs_clk_en_force_high_cnt_END    (11)


/*****************************************************************************
 结构名    : BBPCOMM_C_CLK_EN_FORCE_HIGH_CNT_UNION
 结构说明  : C_CLK_EN_FORCE_HIGH_CNT 寄存器结构定义。地址偏移量:0x13A0，初值:0x00000008，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c_clk_en_force_high_cnt_reg;
    struct
    {
        unsigned int  c_clk_en_force_high_cnt : 12; /* bit[0-11] : C2模下行随路时钟门控使能强制拉高时钟数，
                                                                   单位：工作时钟。 */
        unsigned int  reserved                : 20; /* bit[12-31]: 保留 */
    } reg;
} BBPCOMM_C_CLK_EN_FORCE_HIGH_CNT_UNION;
#define BBPCOMM_C_CLK_EN_FORCE_HIGH_CNT_c_clk_en_force_high_cnt_START  (0)
#define BBPCOMM_C_CLK_EN_FORCE_HIGH_CNT_c_clk_en_force_high_cnt_END    (11)


/*****************************************************************************
 结构名    : BBPCOMM_LTE_CH0_CLK_EN_FORCE_HIGH_CNT_UNION
 结构说明  : LTE_CH0_CLK_EN_FORCE_HIGH_CNT 寄存器结构定义。地址偏移量:0x13A4，初值:0x00000008，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      lte_ch0_clk_en_force_high_cnt_reg;
    struct
    {
        unsigned int  lte_ch0_clk_en_force_high_cnt : 12; /* bit[0-11] : LTE通道0模式下行随路时钟门控使能强制拉高时钟数，
                                                                         单位：工作时钟。 */
        unsigned int  reserved                      : 20; /* bit[12-31]: 保留 */
    } reg;
} BBPCOMM_LTE_CH0_CLK_EN_FORCE_HIGH_CNT_UNION;
#define BBPCOMM_LTE_CH0_CLK_EN_FORCE_HIGH_CNT_lte_ch0_clk_en_force_high_cnt_START  (0)
#define BBPCOMM_LTE_CH0_CLK_EN_FORCE_HIGH_CNT_lte_ch0_clk_en_force_high_cnt_END    (11)


/*****************************************************************************
 结构名    : BBPCOMM_LTE_CH1_CLK_EN_FORCE_HIGH_CNT_UNION
 结构说明  : LTE_CH1_CLK_EN_FORCE_HIGH_CNT 寄存器结构定义。地址偏移量:0x13A8，初值:0x00000008，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      lte_ch1_clk_en_force_high_cnt_reg;
    struct
    {
        unsigned int  lte_ch1_clk_en_force_high_cnt : 12; /* bit[0-11] : LTE通道1模式下行随路时钟门控使能强制拉高时钟数，
                                                                         单位：工作时钟。 */
        unsigned int  reserved                      : 20; /* bit[12-31]: 保留 */
    } reg;
} BBPCOMM_LTE_CH1_CLK_EN_FORCE_HIGH_CNT_UNION;
#define BBPCOMM_LTE_CH1_CLK_EN_FORCE_HIGH_CNT_lte_ch1_clk_en_force_high_cnt_START  (0)
#define BBPCOMM_LTE_CH1_CLK_EN_FORCE_HIGH_CNT_lte_ch1_clk_en_force_high_cnt_END    (11)


/*****************************************************************************
 结构名    : BBPCOMM_LTE_CH2_CLK_EN_FORCE_HIGH_CNT_UNION
 结构说明  : LTE_CH2_CLK_EN_FORCE_HIGH_CNT 寄存器结构定义。地址偏移量:0x13AC，初值:0x00000008，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      lte_ch2_clk_en_force_high_cnt_reg;
    struct
    {
        unsigned int  lte_ch2_clk_en_force_high_cnt : 12; /* bit[0-11] : LTE通道2模式下行随路时钟门控使能强制拉高时钟数，
                                                                         单位：工作时钟。 */
        unsigned int  reserved                      : 20; /* bit[12-31]: 保留 */
    } reg;
} BBPCOMM_LTE_CH2_CLK_EN_FORCE_HIGH_CNT_UNION;
#define BBPCOMM_LTE_CH2_CLK_EN_FORCE_HIGH_CNT_lte_ch2_clk_en_force_high_cnt_START  (0)
#define BBPCOMM_LTE_CH2_CLK_EN_FORCE_HIGH_CNT_lte_ch2_clk_en_force_high_cnt_END    (11)


/*****************************************************************************
 结构名    : BBPCOMM_LTE_CH3_CLK_EN_FORCE_HIGH_CNT_UNION
 结构说明  : LTE_CH3_CLK_EN_FORCE_HIGH_CNT 寄存器结构定义。地址偏移量:0x13B0，初值:0x00000008，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      lte_ch3_clk_en_force_high_cnt_reg;
    struct
    {
        unsigned int  lte_ch3_clk_en_force_high_cnt : 12; /* bit[0-11] : LTE通道3模式下行随路时钟门控使能强制拉高时钟数，
                                                                         单位：工作时钟。 */
        unsigned int  reserved                      : 20; /* bit[12-31]: 保留 */
    } reg;
} BBPCOMM_LTE_CH3_CLK_EN_FORCE_HIGH_CNT_UNION;
#define BBPCOMM_LTE_CH3_CLK_EN_FORCE_HIGH_CNT_lte_ch3_clk_en_force_high_cnt_START  (0)
#define BBPCOMM_LTE_CH3_CLK_EN_FORCE_HIGH_CNT_lte_ch3_clk_en_force_high_cnt_END    (11)


/*****************************************************************************
 结构名    : BBPCOMM_RD_END_FLAG_SSI0_SOFT_UNION
 结构说明  : RD_END_FLAG_SSI0_SOFT 寄存器结构定义。地址偏移量:0x1424，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      rd_end_flag_ssi0_soft_reg;
    struct
    {
        unsigned int  rd_end_flag_ssi0_soft : 1;  /* bit[0]   : 由软件直接控制SSI0 master,不借助xbbp发送回读指令时,回读数据有效指示 */
        unsigned int  reserved              : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_RD_END_FLAG_SSI0_SOFT_UNION;
#define BBPCOMM_RD_END_FLAG_SSI0_SOFT_rd_end_flag_ssi0_soft_START  (0)
#define BBPCOMM_RD_END_FLAG_SSI0_SOFT_rd_end_flag_ssi0_soft_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_SSI0_GRANT_DSP_UNION
 结构说明  : SSI0_GRANT_DSP 寄存器结构定义。地址偏移量:0x1428，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      ssi0_grant_dsp_reg;
    struct
    {
        unsigned int  ssi0_grant_dsp : 1;  /* bit[0]   : 由软件直接控制ssi0 master
                                                         1:软件可以发送CFG_IND启动ssi0
                                                         0:软件等待授权使用ssi0 */
        unsigned int  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_SSI0_GRANT_DSP_UNION;
#define BBPCOMM_SSI0_GRANT_DSP_ssi0_grant_dsp_START  (0)
#define BBPCOMM_SSI0_GRANT_DSP_ssi0_grant_dsp_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_DSP_SSI0_EN_IMI_UNION
 结构说明  : DSP_SSI0_EN_IMI 寄存器结构定义。地址偏移量:0x1430，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dsp_ssi0_en_imi_reg;
    struct
    {
        unsigned int  dsp_ssi0_en_imi : 1;  /* bit[0]   : 由软件直接控制SSI0 master,需首先拉高此指示,屏蔽xbbp对SSI0的控制 */
        unsigned int  reserved        : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_DSP_SSI0_EN_IMI_UNION;
#define BBPCOMM_DSP_SSI0_EN_IMI_dsp_ssi0_en_imi_START  (0)
#define BBPCOMM_DSP_SSI0_EN_IMI_dsp_ssi0_en_imi_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_DSP_SSI0_CFG_IND_IMI_UNION
 结构说明  : DSP_SSI0_CFG_IND_IMI 寄存器结构定义。地址偏移量:0x1434，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dsp_ssi0_cfg_ind_imi_reg;
    struct
    {
        unsigned int  dsp_ssi0_cfg_ind_imi : 1;  /* bit[0]   : 由软件直接控制SSI0 master，在ssi0_grant_dsp为1时,配置次信号产生软件启动脉冲。 */
        unsigned int  reserved             : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_DSP_SSI0_CFG_IND_IMI_UNION;
#define BBPCOMM_DSP_SSI0_CFG_IND_IMI_dsp_ssi0_cfg_ind_imi_START  (0)
#define BBPCOMM_DSP_SSI0_CFG_IND_IMI_dsp_ssi0_cfg_ind_imi_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_DSP_SSI0_RD_CLR_UNION
 结构说明  : DSP_SSI0_RD_CLR 寄存器结构定义。地址偏移量:0x1438，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dsp_ssi0_rd_clr_reg;
    struct
    {
        unsigned int  dsp_ssi0_rd_clr : 1;  /* bit[0]   : 由软件直接控制SSI0 master,取走回读数据后,清rd_end_flag_ssi0_soft标志位脉冲 */
        unsigned int  reserved        : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_DSP_SSI0_RD_CLR_UNION;
#define BBPCOMM_DSP_SSI0_RD_CLR_dsp_ssi0_rd_clr_START  (0)
#define BBPCOMM_DSP_SSI0_RD_CLR_dsp_ssi0_rd_clr_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_LTE_SOFT_ANTPA_SEL_UNION
 结构说明  : LTE_SOFT_ANTPA_SEL 寄存器结构定义。地址偏移量:0x1450，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      lte_soft_antpa_sel_reg;
    struct
    {
        unsigned int  lte_soft_antpa_sel : 31; /* bit[0-30] : LTE模天线开关软件配置值，lte_soft_antpa_en信号有效时生效 */
        unsigned int  reserved           : 1;  /* bit[31-31]: 保留 */
    } reg;
} BBPCOMM_LTE_SOFT_ANTPA_SEL_UNION;
#define BBPCOMM_LTE_SOFT_ANTPA_SEL_lte_soft_antpa_sel_START  (0)
#define BBPCOMM_LTE_SOFT_ANTPA_SEL_lte_soft_antpa_sel_END    (30)


/*****************************************************************************
 结构名    : BBPCOMM_W_SOFT_ANTPA_SEL_UNION
 结构说明  : W_SOFT_ANTPA_SEL 寄存器结构定义。地址偏移量:0x1454，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      w_soft_antpa_sel_reg;
    struct
    {
        unsigned int  w_soft_antpa_sel : 31; /* bit[0-30] : W模天线开关软件配置值，w_soft_antpa_en信号有效时生效 */
        unsigned int  reserved         : 1;  /* bit[31-31]: 保留 */
    } reg;
} BBPCOMM_W_SOFT_ANTPA_SEL_UNION;
#define BBPCOMM_W_SOFT_ANTPA_SEL_w_soft_antpa_sel_START  (0)
#define BBPCOMM_W_SOFT_ANTPA_SEL_w_soft_antpa_sel_END    (30)


/*****************************************************************************
 结构名    : BBPCOMM_TDS_SOFT_ANTPA_SEL_UNION
 结构说明  : TDS_SOFT_ANTPA_SEL 寄存器结构定义。地址偏移量:0x1458，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      tds_soft_antpa_sel_reg;
    struct
    {
        unsigned int  tds_soft_antpa_sel : 31; /* bit[0-30] : TDS模天线开关软件配置值，tds_soft_antpa_en信号有效时生效 */
        unsigned int  reserved           : 1;  /* bit[31-31]: 保留 */
    } reg;
} BBPCOMM_TDS_SOFT_ANTPA_SEL_UNION;
#define BBPCOMM_TDS_SOFT_ANTPA_SEL_tds_soft_antpa_sel_START  (0)
#define BBPCOMM_TDS_SOFT_ANTPA_SEL_tds_soft_antpa_sel_END    (30)


/*****************************************************************************
 结构名    : BBPCOMM_GM_SOFT_ANTPA_SEL_UNION
 结构说明  : GM_SOFT_ANTPA_SEL 寄存器结构定义。地址偏移量:0x145C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      gm_soft_antpa_sel_reg;
    struct
    {
        unsigned int  gm_soft_antpa_sel : 31; /* bit[0-30] : GM模天线开关软件配置值，gm_soft_antpa_en信号有效时生效 */
        unsigned int  reserved          : 1;  /* bit[31-31]: 保留 */
    } reg;
} BBPCOMM_GM_SOFT_ANTPA_SEL_UNION;
#define BBPCOMM_GM_SOFT_ANTPA_SEL_gm_soft_antpa_sel_START  (0)
#define BBPCOMM_GM_SOFT_ANTPA_SEL_gm_soft_antpa_sel_END    (30)


/*****************************************************************************
 结构名    : BBPCOMM_GS_SOFT_ANTPA_SEL_UNION
 结构说明  : GS_SOFT_ANTPA_SEL 寄存器结构定义。地址偏移量:0x1460，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      gs_soft_antpa_sel_reg;
    struct
    {
        unsigned int  gs_soft_antpa_sel : 31; /* bit[0-30] : GS模天线开关软件配置值，gs_soft_antpa_en信号有效时生效 */
        unsigned int  reserved          : 1;  /* bit[31-31]: 保留 */
    } reg;
} BBPCOMM_GS_SOFT_ANTPA_SEL_UNION;
#define BBPCOMM_GS_SOFT_ANTPA_SEL_gs_soft_antpa_sel_START  (0)
#define BBPCOMM_GS_SOFT_ANTPA_SEL_gs_soft_antpa_sel_END    (30)


/*****************************************************************************
 结构名    : BBPCOMM_C_SOFT_ANTPA_SEL_UNION
 结构说明  : C_SOFT_ANTPA_SEL 寄存器结构定义。地址偏移量:0x1464，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c_soft_antpa_sel_reg;
    struct
    {
        unsigned int  c_soft_antpa_sel : 31; /* bit[0-30] : C2模天线开关软件配置值，c_soft_antpa_en信号有效时生效 */
        unsigned int  reserved         : 1;  /* bit[31-31]: 保留 */
    } reg;
} BBPCOMM_C_SOFT_ANTPA_SEL_UNION;
#define BBPCOMM_C_SOFT_ANTPA_SEL_c_soft_antpa_sel_START  (0)
#define BBPCOMM_C_SOFT_ANTPA_SEL_c_soft_antpa_sel_END    (30)


/*****************************************************************************
 结构名    : BBPCOMM_LTE_SOFT_ANTPA_EN_UNION
 结构说明  : LTE_SOFT_ANTPA_EN 寄存器结构定义。地址偏移量:0x1468，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      lte_soft_antpa_en_reg;
    struct
    {
        unsigned int  lte_soft_antpa_en : 1;  /* bit[0-0] : LTE模天线开关软件配置使能,
                                                            0:使用逻辑输入值
                                                            1：使用软件配置值lte_soft_antpa_sel */
        unsigned int  reserved          : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_LTE_SOFT_ANTPA_EN_UNION;
#define BBPCOMM_LTE_SOFT_ANTPA_EN_lte_soft_antpa_en_START  (0)
#define BBPCOMM_LTE_SOFT_ANTPA_EN_lte_soft_antpa_en_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_W_SOFT_ANTPA_EN_UNION
 结构说明  : W_SOFT_ANTPA_EN 寄存器结构定义。地址偏移量:0x146C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      w_soft_antpa_en_reg;
    struct
    {
        unsigned int  w_soft_antpa_en : 1;  /* bit[0-0] : W模天线开关软件配置使能,
                                                          0:使用逻辑输入值
                                                          1：使用软件配置值w_soft_antpa_sel */
        unsigned int  reserved        : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_W_SOFT_ANTPA_EN_UNION;
#define BBPCOMM_W_SOFT_ANTPA_EN_w_soft_antpa_en_START  (0)
#define BBPCOMM_W_SOFT_ANTPA_EN_w_soft_antpa_en_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_TDS_SOFT_ANTPA_EN_UNION
 结构说明  : TDS_SOFT_ANTPA_EN 寄存器结构定义。地址偏移量:0x1470，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      tds_soft_antpa_en_reg;
    struct
    {
        unsigned int  tds_soft_antpa_en : 1;  /* bit[0-0] : TDS模天线开关软件配置使能,
                                                            0:使用逻辑输入值
                                                            1：使用软件配置值tds_soft_antpa_sel */
        unsigned int  reserved          : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_TDS_SOFT_ANTPA_EN_UNION;
#define BBPCOMM_TDS_SOFT_ANTPA_EN_tds_soft_antpa_en_START  (0)
#define BBPCOMM_TDS_SOFT_ANTPA_EN_tds_soft_antpa_en_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_GM_SOFT_ANTPA_EN_UNION
 结构说明  : GM_SOFT_ANTPA_EN 寄存器结构定义。地址偏移量:0x1474，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      gm_soft_antpa_en_reg;
    struct
    {
        unsigned int  gm_soft_antpa_en : 1;  /* bit[0-0] : GM模天线开关软件配置使能,
                                                           0:使用逻辑输入值
                                                           1：使用软件配置值gm_soft_antpa_sel */
        unsigned int  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_GM_SOFT_ANTPA_EN_UNION;
#define BBPCOMM_GM_SOFT_ANTPA_EN_gm_soft_antpa_en_START  (0)
#define BBPCOMM_GM_SOFT_ANTPA_EN_gm_soft_antpa_en_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_GS_SOFT_ANTPA_EN_UNION
 结构说明  : GS_SOFT_ANTPA_EN 寄存器结构定义。地址偏移量:0x1478，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      gs_soft_antpa_en_reg;
    struct
    {
        unsigned int  gs_soft_antpa_en : 1;  /* bit[0-0] : GS模天线开关软件配置使能,
                                                           0:使用逻辑输入值
                                                           1：使用软件配置值gs_soft_antpa_sel */
        unsigned int  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_GS_SOFT_ANTPA_EN_UNION;
#define BBPCOMM_GS_SOFT_ANTPA_EN_gs_soft_antpa_en_START  (0)
#define BBPCOMM_GS_SOFT_ANTPA_EN_gs_soft_antpa_en_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_C_SOFT_ANTPA_EN_UNION
 结构说明  : C_SOFT_ANTPA_EN 寄存器结构定义。地址偏移量:0x147C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c_soft_antpa_en_reg;
    struct
    {
        unsigned int  c_soft_antpa_en : 1;  /* bit[0-0] : C2模天线开关软件配置使能,
                                                          0:使用逻辑输入值
                                                          1：使用软件配置值c_soft_antpa_sel */
        unsigned int  reserved        : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_C_SOFT_ANTPA_EN_UNION;
#define BBPCOMM_C_SOFT_ANTPA_EN_c_soft_antpa_en_START  (0)
#define BBPCOMM_C_SOFT_ANTPA_EN_c_soft_antpa_en_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_CH0_SOFT_ANTPA_SEL_UNION
 结构说明  : CH0_SOFT_ANTPA_SEL 寄存器结构定义。地址偏移量:0x1480，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      ch0_soft_antpa_sel_reg;
    struct
    {
        unsigned int  ch0_soft_antpa_sel : 31; /* bit[0-30] : 通道0模式无效时软件配置的天线开关配置值 */
        unsigned int  ch0_and_or_sel     : 1;  /* bit[31-31]: 通道0模式无效时软件配置的天线开关配置值是否参与通道的bit与或运算
                                                              0：参与
                                                              1：不参与 */
    } reg;
} BBPCOMM_CH0_SOFT_ANTPA_SEL_UNION;
#define BBPCOMM_CH0_SOFT_ANTPA_SEL_ch0_soft_antpa_sel_START  (0)
#define BBPCOMM_CH0_SOFT_ANTPA_SEL_ch0_soft_antpa_sel_END    (30)
#define BBPCOMM_CH0_SOFT_ANTPA_SEL_ch0_and_or_sel_START      (31)
#define BBPCOMM_CH0_SOFT_ANTPA_SEL_ch0_and_or_sel_END        (31)


/*****************************************************************************
 结构名    : BBPCOMM_CH1_SOFT_ANTPA_SEL_UNION
 结构说明  : CH1_SOFT_ANTPA_SEL 寄存器结构定义。地址偏移量:0x1484，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      ch1_soft_antpa_sel_reg;
    struct
    {
        unsigned int  ch1_soft_antpa_sel : 31; /* bit[0-30] : 通道1模式无效时软件配置的天线开关配置值 */
        unsigned int  ch1_and_or_sel     : 1;  /* bit[31-31]: 通道1模式无效时软件配置的天线开关配置值是否参与通道的bit与或运算
                                                              0：参与
                                                              1：不参与 */
    } reg;
} BBPCOMM_CH1_SOFT_ANTPA_SEL_UNION;
#define BBPCOMM_CH1_SOFT_ANTPA_SEL_ch1_soft_antpa_sel_START  (0)
#define BBPCOMM_CH1_SOFT_ANTPA_SEL_ch1_soft_antpa_sel_END    (30)
#define BBPCOMM_CH1_SOFT_ANTPA_SEL_ch1_and_or_sel_START      (31)
#define BBPCOMM_CH1_SOFT_ANTPA_SEL_ch1_and_or_sel_END        (31)


/*****************************************************************************
 结构名    : BBPCOMM_CH2_SOFT_ANTPA_SEL_UNION
 结构说明  : CH2_SOFT_ANTPA_SEL 寄存器结构定义。地址偏移量:0x1488，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      ch2_soft_antpa_sel_reg;
    struct
    {
        unsigned int  ch2_soft_antpa_sel : 31; /* bit[0-30] : 通道2模式无效时软件配置的天线开关配置值 */
        unsigned int  ch2_and_or_sel     : 1;  /* bit[31-31]: 通道2模式无效时软件配置的天线开关配置值是否参与通道的bit与或运算
                                                              0：参与
                                                              1：不参与 */
    } reg;
} BBPCOMM_CH2_SOFT_ANTPA_SEL_UNION;
#define BBPCOMM_CH2_SOFT_ANTPA_SEL_ch2_soft_antpa_sel_START  (0)
#define BBPCOMM_CH2_SOFT_ANTPA_SEL_ch2_soft_antpa_sel_END    (30)
#define BBPCOMM_CH2_SOFT_ANTPA_SEL_ch2_and_or_sel_START      (31)
#define BBPCOMM_CH2_SOFT_ANTPA_SEL_ch2_and_or_sel_END        (31)


/*****************************************************************************
 结构名    : BBPCOMM_CH3_SOFT_ANTPA_SEL_UNION
 结构说明  : CH3_SOFT_ANTPA_SEL 寄存器结构定义。地址偏移量:0x148C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      ch3_soft_antpa_sel_reg;
    struct
    {
        unsigned int  ch3_soft_antpa_sel : 31; /* bit[0-30] : 通道3模式无效时软件配置的天线开关配置值 */
        unsigned int  ch3_and_or_sel     : 1;  /* bit[31-31]: 通道3模式无效时软件配置的天线开关配置值是否参与通道的bit与或运算
                                                              0：参与
                                                              1：不参与 */
    } reg;
} BBPCOMM_CH3_SOFT_ANTPA_SEL_UNION;
#define BBPCOMM_CH3_SOFT_ANTPA_SEL_ch3_soft_antpa_sel_START  (0)
#define BBPCOMM_CH3_SOFT_ANTPA_SEL_ch3_soft_antpa_sel_END    (30)
#define BBPCOMM_CH3_SOFT_ANTPA_SEL_ch3_and_or_sel_START      (31)
#define BBPCOMM_CH3_SOFT_ANTPA_SEL_ch3_and_or_sel_END        (31)


/*****************************************************************************
 结构名    : BBPCOMM_CH_ANTPA_BIT_AND_OR_EN_UNION
 结构说明  : CH_ANTPA_BIT_AND_OR_EN 寄存器结构定义。地址偏移量:0x1490，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      ch_antpa_bit_and_or_en_reg;
    struct
    {
        unsigned int  ch_antpa_bit_and_or_en : 31; /* bit[0-30] : 4路通道输出的31比特线控对应线控相与和相或选择开关：
                                                                  1：相与
                                                                  0：相或 */
        unsigned int  reserved               : 1;  /* bit[31-31]: 保留 */
    } reg;
} BBPCOMM_CH_ANTPA_BIT_AND_OR_EN_UNION;
#define BBPCOMM_CH_ANTPA_BIT_AND_OR_EN_ch_antpa_bit_and_or_en_START  (0)
#define BBPCOMM_CH_ANTPA_BIT_AND_OR_EN_ch_antpa_bit_and_or_en_END    (30)


/*****************************************************************************
 结构名    : BBPCOMM_MIPI_DET_EN_UNION
 结构说明  : MIPI_DET_EN 寄存器结构定义。地址偏移量:0x14A0，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      mipi_det_en_reg;
    struct
    {
        unsigned int  mipi_det_en : 1;  /* bit[0-0] : 软件检测mipi指令地址使能：
                                                      1：打开检测功能
                                                      0：关闭检测功能 */
        unsigned int  reserved    : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_MIPI_DET_EN_UNION;
#define BBPCOMM_MIPI_DET_EN_mipi_det_en_START  (0)
#define BBPCOMM_MIPI_DET_EN_mipi_det_en_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_MIPI_DET_ADDR_UNION
 结构说明  : MIPI_DET_ADDR 寄存器结构定义。地址偏移量:0x14A4，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      mipi_det_addr_reg;
    struct
    {
        unsigned int  mipi_det_addr   : 8;  /* bit[0-7]  : 软件检测mipi写指令地址，最大8比特 */
        unsigned int  mipi_det_slv_id : 4;  /* bit[8-11] : 软件检测mipi指令slave id，4比特 */
        unsigned int  reserved        : 20; /* bit[12-31]: 保留 */
    } reg;
} BBPCOMM_MIPI_DET_ADDR_UNION;
#define BBPCOMM_MIPI_DET_ADDR_mipi_det_addr_START    (0)
#define BBPCOMM_MIPI_DET_ADDR_mipi_det_addr_END      (7)
#define BBPCOMM_MIPI_DET_ADDR_mipi_det_slv_id_START  (8)
#define BBPCOMM_MIPI_DET_ADDR_mipi_det_slv_id_END    (11)


/*****************************************************************************
 结构名    : BBPCOMM_CH0_MIPI_DET_RESULT_FLAG_UNION
 结构说明  : CH0_MIPI_DET_RESULT_FLAG 寄存器结构定义。地址偏移量:0x14A8，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      ch0_mipi_det_result_flag_reg;
    struct
    {
        unsigned int  ch0_mipi_det_result_flag : 1;  /* bit[0-0] : 通道0软件检测mipi地址结果：
                                                                   1：检测到mipi指令发送软件配置的地址
                                                                   0：没有检测到mipi指令发送软件配置的地址 */
        unsigned int  reserved                 : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_CH0_MIPI_DET_RESULT_FLAG_UNION;
#define BBPCOMM_CH0_MIPI_DET_RESULT_FLAG_ch0_mipi_det_result_flag_START  (0)
#define BBPCOMM_CH0_MIPI_DET_RESULT_FLAG_ch0_mipi_det_result_flag_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_CH0_MIPI_DET_RESULT_INFO_UNION
 结构说明  : CH0_MIPI_DET_RESULT_INFO 寄存器结构定义。地址偏移量:0x14AC，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      ch0_mipi_det_result_info_reg;
    struct
    {
        unsigned int  ch0_mipi_det_result_data          : 8;  /* bit[0-7]  : 通道0逻辑检测到软件配置的地址后上报指令的配置数据（扩展写指令只上报起始地址配置的数据） */
        unsigned int  ch0_mipi_det_result_ch_mode       : 4;  /* bit[8-11] : 通道0逻辑检测到软件配置的地址后上报指令源来自于哪个BBP的配置 */
        unsigned int  ch0_mipi_det_result_slv_id        : 4;  /* bit[12-15]: 通道0逻辑检测到软件配置的地址后上报指令的slave_id */
        unsigned int  ch0_mipi_det_result_cmd_type      : 3;  /* bit[16-18]: 通道0逻辑检测到软件配置的地址后上报指令指令类型 */
        unsigned int  ch0_mipi_det_result_ch_id         : 3;  /* bit[19-21]: 通道0逻辑检测到软件配置的地址后上报指令指令通道id号 */
        unsigned int  ch0_mipi_det_result_soft_cfg_flag : 1;  /* bit[22-22]: 通道0逻辑检测到软件配置的地址后上报指令指令是否由软件配置标志 */
        unsigned int  reserved                          : 9;  /* bit[23-31]: 保留 */
    } reg;
} BBPCOMM_CH0_MIPI_DET_RESULT_INFO_UNION;
#define BBPCOMM_CH0_MIPI_DET_RESULT_INFO_ch0_mipi_det_result_data_START           (0)
#define BBPCOMM_CH0_MIPI_DET_RESULT_INFO_ch0_mipi_det_result_data_END             (7)
#define BBPCOMM_CH0_MIPI_DET_RESULT_INFO_ch0_mipi_det_result_ch_mode_START        (8)
#define BBPCOMM_CH0_MIPI_DET_RESULT_INFO_ch0_mipi_det_result_ch_mode_END          (11)
#define BBPCOMM_CH0_MIPI_DET_RESULT_INFO_ch0_mipi_det_result_slv_id_START         (12)
#define BBPCOMM_CH0_MIPI_DET_RESULT_INFO_ch0_mipi_det_result_slv_id_END           (15)
#define BBPCOMM_CH0_MIPI_DET_RESULT_INFO_ch0_mipi_det_result_cmd_type_START       (16)
#define BBPCOMM_CH0_MIPI_DET_RESULT_INFO_ch0_mipi_det_result_cmd_type_END         (18)
#define BBPCOMM_CH0_MIPI_DET_RESULT_INFO_ch0_mipi_det_result_ch_id_START          (19)
#define BBPCOMM_CH0_MIPI_DET_RESULT_INFO_ch0_mipi_det_result_ch_id_END            (21)
#define BBPCOMM_CH0_MIPI_DET_RESULT_INFO_ch0_mipi_det_result_soft_cfg_flag_START  (22)
#define BBPCOMM_CH0_MIPI_DET_RESULT_INFO_ch0_mipi_det_result_soft_cfg_flag_END    (22)


/*****************************************************************************
 结构名    : BBPCOMM_CH0_MIPI_DET_RESULT_FLAG_CLR_UNION
 结构说明  : CH0_MIPI_DET_RESULT_FLAG_CLR 寄存器结构定义。地址偏移量:0x14B0，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      ch0_mipi_det_result_flag_clr_reg;
    struct
    {
        unsigned int  ch0_mipi_det_result_flag_clr : 1;  /* bit[0-0] : 通道0软件检测mipi地址结果清除脉冲，写1清 */
        unsigned int  reserved                     : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_CH0_MIPI_DET_RESULT_FLAG_CLR_UNION;
#define BBPCOMM_CH0_MIPI_DET_RESULT_FLAG_CLR_ch0_mipi_det_result_flag_clr_START  (0)
#define BBPCOMM_CH0_MIPI_DET_RESULT_FLAG_CLR_ch0_mipi_det_result_flag_clr_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_CH1_MIPI_DET_RESULT_FLAG_UNION
 结构说明  : CH1_MIPI_DET_RESULT_FLAG 寄存器结构定义。地址偏移量:0x14B4，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      ch1_mipi_det_result_flag_reg;
    struct
    {
        unsigned int  ch1_mipi_det_result_flag : 1;  /* bit[0-0] : 通道1软件检测mipi地址结果：
                                                                   1：检测到mipi指令发送软件配置的地址
                                                                   0：没有检测到mipi指令发送软件配置的地址 */
        unsigned int  reserved                 : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_CH1_MIPI_DET_RESULT_FLAG_UNION;
#define BBPCOMM_CH1_MIPI_DET_RESULT_FLAG_ch1_mipi_det_result_flag_START  (0)
#define BBPCOMM_CH1_MIPI_DET_RESULT_FLAG_ch1_mipi_det_result_flag_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_CH1_MIPI_DET_RESULT_INFO_UNION
 结构说明  : CH1_MIPI_DET_RESULT_INFO 寄存器结构定义。地址偏移量:0x14B8，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      ch1_mipi_det_result_info_reg;
    struct
    {
        unsigned int  ch1_mipi_det_result_data          : 8;  /* bit[0-7]  : 通道1逻辑检测到软件配置的地址后上报指令的配置数据（扩展写指令只上报起始地址配置的数据） */
        unsigned int  ch1_mipi_det_result_ch_mode       : 4;  /* bit[8-11] : 通道1逻辑检测到软件配置的地址后上报指令源来自于哪个BBP的配置 */
        unsigned int  ch1_mipi_det_result_slv_id        : 4;  /* bit[12-15]: 通道1逻辑检测到软件配置的地址后上报指令的slave_id */
        unsigned int  ch1_mipi_det_result_cmd_type      : 3;  /* bit[16-18]: 通道1逻辑检测到软件配置的地址后上报指令指令类型 */
        unsigned int  ch1_mipi_det_result_ch_id         : 3;  /* bit[19-21]: 通道1逻辑检测到软件配置的地址后上报指令指令通道id号 */
        unsigned int  ch1_mipi_det_result_soft_cfg_flag : 1;  /* bit[22-22]: 通道1逻辑检测到软件配置的地址后上报指令指令是否由软件配置标志 */
        unsigned int  reserved                          : 9;  /* bit[23-31]: 保留 */
    } reg;
} BBPCOMM_CH1_MIPI_DET_RESULT_INFO_UNION;
#define BBPCOMM_CH1_MIPI_DET_RESULT_INFO_ch1_mipi_det_result_data_START           (0)
#define BBPCOMM_CH1_MIPI_DET_RESULT_INFO_ch1_mipi_det_result_data_END             (7)
#define BBPCOMM_CH1_MIPI_DET_RESULT_INFO_ch1_mipi_det_result_ch_mode_START        (8)
#define BBPCOMM_CH1_MIPI_DET_RESULT_INFO_ch1_mipi_det_result_ch_mode_END          (11)
#define BBPCOMM_CH1_MIPI_DET_RESULT_INFO_ch1_mipi_det_result_slv_id_START         (12)
#define BBPCOMM_CH1_MIPI_DET_RESULT_INFO_ch1_mipi_det_result_slv_id_END           (15)
#define BBPCOMM_CH1_MIPI_DET_RESULT_INFO_ch1_mipi_det_result_cmd_type_START       (16)
#define BBPCOMM_CH1_MIPI_DET_RESULT_INFO_ch1_mipi_det_result_cmd_type_END         (18)
#define BBPCOMM_CH1_MIPI_DET_RESULT_INFO_ch1_mipi_det_result_ch_id_START          (19)
#define BBPCOMM_CH1_MIPI_DET_RESULT_INFO_ch1_mipi_det_result_ch_id_END            (21)
#define BBPCOMM_CH1_MIPI_DET_RESULT_INFO_ch1_mipi_det_result_soft_cfg_flag_START  (22)
#define BBPCOMM_CH1_MIPI_DET_RESULT_INFO_ch1_mipi_det_result_soft_cfg_flag_END    (22)


/*****************************************************************************
 结构名    : BBPCOMM_CH1_MIPI_DET_RESULT_FLAG_CLR_UNION
 结构说明  : CH1_MIPI_DET_RESULT_FLAG_CLR 寄存器结构定义。地址偏移量:0x14BC，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      ch1_mipi_det_result_flag_clr_reg;
    struct
    {
        unsigned int  ch1_mipi_det_result_flag_clr : 1;  /* bit[0-0] : 通道1软件检测mipi地址结果清除脉冲，写1清 */
        unsigned int  reserved                     : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_CH1_MIPI_DET_RESULT_FLAG_CLR_UNION;
#define BBPCOMM_CH1_MIPI_DET_RESULT_FLAG_CLR_ch1_mipi_det_result_flag_clr_START  (0)
#define BBPCOMM_CH1_MIPI_DET_RESULT_FLAG_CLR_ch1_mipi_det_result_flag_clr_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_CH2_MIPI_DET_RESULT_FLAG_UNION
 结构说明  : CH2_MIPI_DET_RESULT_FLAG 寄存器结构定义。地址偏移量:0x14C0，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      ch2_mipi_det_result_flag_reg;
    struct
    {
        unsigned int  ch2_mipi_det_result_flag : 1;  /* bit[0-0] : 通道2软件检测mipi地址结果：
                                                                   1：检测到mipi指令发送软件配置的地址
                                                                   0：没有检测到mipi指令发送软件配置的地址 */
        unsigned int  reserved                 : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_CH2_MIPI_DET_RESULT_FLAG_UNION;
#define BBPCOMM_CH2_MIPI_DET_RESULT_FLAG_ch2_mipi_det_result_flag_START  (0)
#define BBPCOMM_CH2_MIPI_DET_RESULT_FLAG_ch2_mipi_det_result_flag_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_CH2_MIPI_DET_RESULT_INFO_UNION
 结构说明  : CH2_MIPI_DET_RESULT_INFO 寄存器结构定义。地址偏移量:0x14C4，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      ch2_mipi_det_result_info_reg;
    struct
    {
        unsigned int  ch2_mipi_det_result_data          : 8;  /* bit[0-7]  : 通道2逻辑检测到软件配置的地址后上报指令的配置数据（扩展写指令只上报起始地址配置的数据） */
        unsigned int  ch2_mipi_det_result_ch_mode       : 4;  /* bit[8-11] : 通道2逻辑检测到软件配置的地址后上报指令源来自于哪个BBP的配置 */
        unsigned int  ch2_mipi_det_result_slv_id        : 4;  /* bit[12-15]: 通道2逻辑检测到软件配置的地址后上报指令的slave_id */
        unsigned int  ch2_mipi_det_result_cmd_type      : 3;  /* bit[16-18]: 通道2逻辑检测到软件配置的地址后上报指令指令类型 */
        unsigned int  ch2_mipi_det_result_ch_id         : 3;  /* bit[19-21]: 通道2逻辑检测到软件配置的地址后上报指令指令通道id号 */
        unsigned int  ch2_mipi_det_result_soft_cfg_flag : 1;  /* bit[22-22]: 通道2逻辑检测到软件配置的地址后上报指令指令是否由软件配置标志 */
        unsigned int  reserved                          : 9;  /* bit[23-31]: 保留 */
    } reg;
} BBPCOMM_CH2_MIPI_DET_RESULT_INFO_UNION;
#define BBPCOMM_CH2_MIPI_DET_RESULT_INFO_ch2_mipi_det_result_data_START           (0)
#define BBPCOMM_CH2_MIPI_DET_RESULT_INFO_ch2_mipi_det_result_data_END             (7)
#define BBPCOMM_CH2_MIPI_DET_RESULT_INFO_ch2_mipi_det_result_ch_mode_START        (8)
#define BBPCOMM_CH2_MIPI_DET_RESULT_INFO_ch2_mipi_det_result_ch_mode_END          (11)
#define BBPCOMM_CH2_MIPI_DET_RESULT_INFO_ch2_mipi_det_result_slv_id_START         (12)
#define BBPCOMM_CH2_MIPI_DET_RESULT_INFO_ch2_mipi_det_result_slv_id_END           (15)
#define BBPCOMM_CH2_MIPI_DET_RESULT_INFO_ch2_mipi_det_result_cmd_type_START       (16)
#define BBPCOMM_CH2_MIPI_DET_RESULT_INFO_ch2_mipi_det_result_cmd_type_END         (18)
#define BBPCOMM_CH2_MIPI_DET_RESULT_INFO_ch2_mipi_det_result_ch_id_START          (19)
#define BBPCOMM_CH2_MIPI_DET_RESULT_INFO_ch2_mipi_det_result_ch_id_END            (21)
#define BBPCOMM_CH2_MIPI_DET_RESULT_INFO_ch2_mipi_det_result_soft_cfg_flag_START  (22)
#define BBPCOMM_CH2_MIPI_DET_RESULT_INFO_ch2_mipi_det_result_soft_cfg_flag_END    (22)


/*****************************************************************************
 结构名    : BBPCOMM_CH2_MIPI_DET_RESULT_FLAG_CLR_UNION
 结构说明  : CH2_MIPI_DET_RESULT_FLAG_CLR 寄存器结构定义。地址偏移量:0x14C8，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      ch2_mipi_det_result_flag_clr_reg;
    struct
    {
        unsigned int  ch2_mipi_det_result_flag_clr : 1;  /* bit[0-0] : 通道2软件检测mipi地址结果清除脉冲，写1清 */
        unsigned int  reserved                     : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_CH2_MIPI_DET_RESULT_FLAG_CLR_UNION;
#define BBPCOMM_CH2_MIPI_DET_RESULT_FLAG_CLR_ch2_mipi_det_result_flag_clr_START  (0)
#define BBPCOMM_CH2_MIPI_DET_RESULT_FLAG_CLR_ch2_mipi_det_result_flag_clr_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_CH3_MIPI_DET_RESULT_FLAG_UNION
 结构说明  : CH3_MIPI_DET_RESULT_FLAG 寄存器结构定义。地址偏移量:0x14CC，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      ch3_mipi_det_result_flag_reg;
    struct
    {
        unsigned int  ch3_mipi_det_result_flag : 1;  /* bit[0-0] : 通道3软件检测mipi地址结果：
                                                                   1：检测到mipi指令发送软件配置的地址
                                                                   0：没有检测到mipi指令发送软件配置的地址 */
        unsigned int  reserved                 : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_CH3_MIPI_DET_RESULT_FLAG_UNION;
#define BBPCOMM_CH3_MIPI_DET_RESULT_FLAG_ch3_mipi_det_result_flag_START  (0)
#define BBPCOMM_CH3_MIPI_DET_RESULT_FLAG_ch3_mipi_det_result_flag_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_CH3_MIPI_DET_RESULT_INFO_UNION
 结构说明  : CH3_MIPI_DET_RESULT_INFO 寄存器结构定义。地址偏移量:0x14D4，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      ch3_mipi_det_result_info_reg;
    struct
    {
        unsigned int  ch3_mipi_det_result_data          : 8;  /* bit[0-7]  : 通道3逻辑检测到软件配置的地址后上报指令的配置数据（扩展写指令只上报起始地址配置的数据） */
        unsigned int  ch3_mipi_det_result_ch_mode       : 4;  /* bit[8-11] : 通道3逻辑检测到软件配置的地址后上报指令源来自于哪个BBP的配置 */
        unsigned int  ch3_mipi_det_result_slv_id        : 4;  /* bit[12-15]: 通道3逻辑检测到软件配置的地址后上报指令的slave_id */
        unsigned int  ch3_mipi_det_result_cmd_type      : 3;  /* bit[16-18]: 通道3逻辑检测到软件配置的地址后上报指令指令类型 */
        unsigned int  ch3_mipi_det_result_ch_id         : 3;  /* bit[19-21]: 通道3逻辑检测到软件配置的地址后上报指令指令通道id号 */
        unsigned int  ch3_mipi_det_result_soft_cfg_flag : 1;  /* bit[22-22]: 通道3逻辑检测到软件配置的地址后上报指令指令是否由软件配置标志 */
        unsigned int  reserved                          : 9;  /* bit[23-31]: 保留 */
    } reg;
} BBPCOMM_CH3_MIPI_DET_RESULT_INFO_UNION;
#define BBPCOMM_CH3_MIPI_DET_RESULT_INFO_ch3_mipi_det_result_data_START           (0)
#define BBPCOMM_CH3_MIPI_DET_RESULT_INFO_ch3_mipi_det_result_data_END             (7)
#define BBPCOMM_CH3_MIPI_DET_RESULT_INFO_ch3_mipi_det_result_ch_mode_START        (8)
#define BBPCOMM_CH3_MIPI_DET_RESULT_INFO_ch3_mipi_det_result_ch_mode_END          (11)
#define BBPCOMM_CH3_MIPI_DET_RESULT_INFO_ch3_mipi_det_result_slv_id_START         (12)
#define BBPCOMM_CH3_MIPI_DET_RESULT_INFO_ch3_mipi_det_result_slv_id_END           (15)
#define BBPCOMM_CH3_MIPI_DET_RESULT_INFO_ch3_mipi_det_result_cmd_type_START       (16)
#define BBPCOMM_CH3_MIPI_DET_RESULT_INFO_ch3_mipi_det_result_cmd_type_END         (18)
#define BBPCOMM_CH3_MIPI_DET_RESULT_INFO_ch3_mipi_det_result_ch_id_START          (19)
#define BBPCOMM_CH3_MIPI_DET_RESULT_INFO_ch3_mipi_det_result_ch_id_END            (21)
#define BBPCOMM_CH3_MIPI_DET_RESULT_INFO_ch3_mipi_det_result_soft_cfg_flag_START  (22)
#define BBPCOMM_CH3_MIPI_DET_RESULT_INFO_ch3_mipi_det_result_soft_cfg_flag_END    (22)


/*****************************************************************************
 结构名    : BBPCOMM_CH3_MIPI_DET_RESULT_FLAG_CLR_UNION
 结构说明  : CH3_MIPI_DET_RESULT_FLAG_CLR 寄存器结构定义。地址偏移量:0x14D8，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      ch3_mipi_det_result_flag_clr_reg;
    struct
    {
        unsigned int  ch3_mipi_det_result_flag_clr : 1;  /* bit[0-0] : 通道3软件检测mipi地址结果清除脉冲，写1清 */
        unsigned int  reserved                     : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_CH3_MIPI_DET_RESULT_FLAG_CLR_UNION;
#define BBPCOMM_CH3_MIPI_DET_RESULT_FLAG_CLR_ch3_mipi_det_result_flag_clr_START  (0)
#define BBPCOMM_CH3_MIPI_DET_RESULT_FLAG_CLR_ch3_mipi_det_result_flag_clr_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_SSI_DET_EN_UNION
 结构说明  : SSI_DET_EN 寄存器结构定义。地址偏移量:0x14DC，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      ssi_det_en_reg;
    struct
    {
        unsigned int  ssi_det_en : 1;  /* bit[0-0] : 软件检测ssi指令地址使能：
                                                     1：打开检测功能
                                                     0：关闭检测功能 */
        unsigned int  reserved   : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_SSI_DET_EN_UNION;
#define BBPCOMM_SSI_DET_EN_ssi_det_en_START  (0)
#define BBPCOMM_SSI_DET_EN_ssi_det_en_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_SSI_DET_ADDR_UNION
 结构说明  : SSI_DET_ADDR 寄存器结构定义。地址偏移量:0x14E4，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      ssi_det_addr_reg;
    struct
    {
        unsigned int  ssi_det_addr : 8;  /* bit[0-7] : 软件检测ssi写指令地址，最大8比特 */
        unsigned int  reserved     : 24; /* bit[8-31]: 保留 */
    } reg;
} BBPCOMM_SSI_DET_ADDR_UNION;
#define BBPCOMM_SSI_DET_ADDR_ssi_det_addr_START  (0)
#define BBPCOMM_SSI_DET_ADDR_ssi_det_addr_END    (7)


/*****************************************************************************
 结构名    : BBPCOMM_CH0_SSI_DET_RESULT_FLAG_UNION
 结构说明  : CH0_SSI_DET_RESULT_FLAG 寄存器结构定义。地址偏移量:0x14E8，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      ch0_ssi_det_result_flag_reg;
    struct
    {
        unsigned int  ch0_ssi_det_result_flag : 1;  /* bit[0-0] : 通道0软件检测ssi地址结果：
                                                                  1：检测到ssi指令发送软件配置的地址
                                                                  0：没有检测到ssi指令发送软件配置的地址 */
        unsigned int  reserved                : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_CH0_SSI_DET_RESULT_FLAG_UNION;
#define BBPCOMM_CH0_SSI_DET_RESULT_FLAG_ch0_ssi_det_result_flag_START  (0)
#define BBPCOMM_CH0_SSI_DET_RESULT_FLAG_ch0_ssi_det_result_flag_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_CH0_SSI_DET_RESULT_INFO_UNION
 结构说明  : CH0_SSI_DET_RESULT_INFO 寄存器结构定义。地址偏移量:0x14EC，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      ch0_ssi_det_result_info_reg;
    struct
    {
        unsigned int  ch0_ssi_det_result_data          : 16; /* bit[0-15] : 通道0逻辑检测到软件配置的地址后上报指令的配置数据（扩展写指令只上报起始地址配置的数据） */
        unsigned int  ch0_ssi_det_result_ch_mode       : 4;  /* bit[16-19]: 通道0逻辑检测到软件配置的地址后上报指令源来自于哪个BBP的配置 */
        unsigned int  ch0_ssi_det_result_ch_id         : 2;  /* bit[20-21]: 通道0逻辑检测到软件配置的地址后上报指令指令通道id号 */
        unsigned int  ch0_ssi_det_result_soft_cfg_flag : 1;  /* bit[22-22]: 通道0逻辑检测到软件配置的地址后上报指令指令是否由软件配置标志 */
        unsigned int  reserved                         : 9;  /* bit[23-31]: 保留 */
    } reg;
} BBPCOMM_CH0_SSI_DET_RESULT_INFO_UNION;
#define BBPCOMM_CH0_SSI_DET_RESULT_INFO_ch0_ssi_det_result_data_START           (0)
#define BBPCOMM_CH0_SSI_DET_RESULT_INFO_ch0_ssi_det_result_data_END             (15)
#define BBPCOMM_CH0_SSI_DET_RESULT_INFO_ch0_ssi_det_result_ch_mode_START        (16)
#define BBPCOMM_CH0_SSI_DET_RESULT_INFO_ch0_ssi_det_result_ch_mode_END          (19)
#define BBPCOMM_CH0_SSI_DET_RESULT_INFO_ch0_ssi_det_result_ch_id_START          (20)
#define BBPCOMM_CH0_SSI_DET_RESULT_INFO_ch0_ssi_det_result_ch_id_END            (21)
#define BBPCOMM_CH0_SSI_DET_RESULT_INFO_ch0_ssi_det_result_soft_cfg_flag_START  (22)
#define BBPCOMM_CH0_SSI_DET_RESULT_INFO_ch0_ssi_det_result_soft_cfg_flag_END    (22)


/*****************************************************************************
 结构名    : BBPCOMM_CH0_SSI_DET_RESULT_FLAG_CLR_UNION
 结构说明  : CH0_SSI_DET_RESULT_FLAG_CLR 寄存器结构定义。地址偏移量:0x14F0，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      ch0_ssi_det_result_flag_clr_reg;
    struct
    {
        unsigned int  ch0_ssi_det_result_flag_clr : 1;  /* bit[0-0] : 通道0软件检测ssi地址结果清除脉冲，写1清 */
        unsigned int  reserved                    : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_CH0_SSI_DET_RESULT_FLAG_CLR_UNION;
#define BBPCOMM_CH0_SSI_DET_RESULT_FLAG_CLR_ch0_ssi_det_result_flag_clr_START  (0)
#define BBPCOMM_CH0_SSI_DET_RESULT_FLAG_CLR_ch0_ssi_det_result_flag_clr_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_CH1_SSI_DET_RESULT_FLAG_UNION
 结构说明  : CH1_SSI_DET_RESULT_FLAG 寄存器结构定义。地址偏移量:0x14F4，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      ch1_ssi_det_result_flag_reg;
    struct
    {
        unsigned int  ch1_ssi_det_result_flag : 1;  /* bit[0-0] : 通道1软件检测ssi地址结果：
                                                                  1：检测到ssi指令发送软件配置的地址
                                                                  0：没有检测到ssi指令发送软件配置的地址 */
        unsigned int  reserved                : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_CH1_SSI_DET_RESULT_FLAG_UNION;
#define BBPCOMM_CH1_SSI_DET_RESULT_FLAG_ch1_ssi_det_result_flag_START  (0)
#define BBPCOMM_CH1_SSI_DET_RESULT_FLAG_ch1_ssi_det_result_flag_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_CH1_SSI_DET_RESULT_INFO_UNION
 结构说明  : CH1_SSI_DET_RESULT_INFO 寄存器结构定义。地址偏移量:0x14F8，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      ch1_ssi_det_result_info_reg;
    struct
    {
        unsigned int  ch1_ssi_det_result_data          : 16; /* bit[0-15] : 通道1逻辑检测到软件配置的地址后上报指令的配置数据（扩展写指令只上报起始地址配置的数据） */
        unsigned int  ch1_ssi_det_result_ch_mode       : 4;  /* bit[16-19]: 通道1逻辑检测到软件配置的地址后上报指令源来自于哪个BBP的配置 */
        unsigned int  ch1_ssi_det_result_ch_id         : 2;  /* bit[20-21]: 通道1逻辑检测到软件配置的地址后上报指令指令通道id号 */
        unsigned int  ch1_ssi_det_result_soft_cfg_flag : 1;  /* bit[22-22]: 通道1逻辑检测到软件配置的地址后上报指令指令是否由软件配置标志 */
        unsigned int  reserved                         : 9;  /* bit[23-31]: 保留 */
    } reg;
} BBPCOMM_CH1_SSI_DET_RESULT_INFO_UNION;
#define BBPCOMM_CH1_SSI_DET_RESULT_INFO_ch1_ssi_det_result_data_START           (0)
#define BBPCOMM_CH1_SSI_DET_RESULT_INFO_ch1_ssi_det_result_data_END             (15)
#define BBPCOMM_CH1_SSI_DET_RESULT_INFO_ch1_ssi_det_result_ch_mode_START        (16)
#define BBPCOMM_CH1_SSI_DET_RESULT_INFO_ch1_ssi_det_result_ch_mode_END          (19)
#define BBPCOMM_CH1_SSI_DET_RESULT_INFO_ch1_ssi_det_result_ch_id_START          (20)
#define BBPCOMM_CH1_SSI_DET_RESULT_INFO_ch1_ssi_det_result_ch_id_END            (21)
#define BBPCOMM_CH1_SSI_DET_RESULT_INFO_ch1_ssi_det_result_soft_cfg_flag_START  (22)
#define BBPCOMM_CH1_SSI_DET_RESULT_INFO_ch1_ssi_det_result_soft_cfg_flag_END    (22)


/*****************************************************************************
 结构名    : BBPCOMM_CH1_SSI_DET_RESULT_FLAG_CLR_UNION
 结构说明  : CH1_SSI_DET_RESULT_FLAG_CLR 寄存器结构定义。地址偏移量:0x14FC，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      ch1_ssi_det_result_flag_clr_reg;
    struct
    {
        unsigned int  ch1_ssi_det_result_flag_clr : 1;  /* bit[0-0] : 通道1软件检测ssi地址结果清除脉冲，写1清 */
        unsigned int  reserved                    : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_CH1_SSI_DET_RESULT_FLAG_CLR_UNION;
#define BBPCOMM_CH1_SSI_DET_RESULT_FLAG_CLR_ch1_ssi_det_result_flag_clr_START  (0)
#define BBPCOMM_CH1_SSI_DET_RESULT_FLAG_CLR_ch1_ssi_det_result_flag_clr_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_CH2_SSI_DET_RESULT_FLAG_UNION
 结构说明  : CH2_SSI_DET_RESULT_FLAG 寄存器结构定义。地址偏移量:0x1500，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      ch2_ssi_det_result_flag_reg;
    struct
    {
        unsigned int  ch2_ssi_det_result_flag : 1;  /* bit[0-0] : 通道2软件检测ssi地址结果：
                                                                  1：检测到ssi指令发送软件配置的地址
                                                                  0：没有检测到ssi指令发送软件配置的地址 */
        unsigned int  reserved                : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_CH2_SSI_DET_RESULT_FLAG_UNION;
#define BBPCOMM_CH2_SSI_DET_RESULT_FLAG_ch2_ssi_det_result_flag_START  (0)
#define BBPCOMM_CH2_SSI_DET_RESULT_FLAG_ch2_ssi_det_result_flag_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_CH2_SSI_DET_RESULT_INFO_UNION
 结构说明  : CH2_SSI_DET_RESULT_INFO 寄存器结构定义。地址偏移量:0x1504，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      ch2_ssi_det_result_info_reg;
    struct
    {
        unsigned int  ch2_ssi_det_result_data          : 16; /* bit[0-15] : 通道2逻辑检测到软件配置的地址后上报指令的配置数据（扩展写指令只上报起始地址配置的数据） */
        unsigned int  ch2_ssi_det_result_ch_mode       : 4;  /* bit[16-19]: 通道2逻辑检测到软件配置的地址后上报指令源来自于哪个BBP的配置 */
        unsigned int  ch2_ssi_det_result_ch_id         : 2;  /* bit[20-21]: 通道2逻辑检测到软件配置的地址后上报指令指令通道id号 */
        unsigned int  ch2_ssi_det_result_soft_cfg_flag : 1;  /* bit[22-22]: 通道2逻辑检测到软件配置的地址后上报指令指令是否由软件配置标志 */
        unsigned int  reserved                         : 9;  /* bit[23-31]: 保留 */
    } reg;
} BBPCOMM_CH2_SSI_DET_RESULT_INFO_UNION;
#define BBPCOMM_CH2_SSI_DET_RESULT_INFO_ch2_ssi_det_result_data_START           (0)
#define BBPCOMM_CH2_SSI_DET_RESULT_INFO_ch2_ssi_det_result_data_END             (15)
#define BBPCOMM_CH2_SSI_DET_RESULT_INFO_ch2_ssi_det_result_ch_mode_START        (16)
#define BBPCOMM_CH2_SSI_DET_RESULT_INFO_ch2_ssi_det_result_ch_mode_END          (19)
#define BBPCOMM_CH2_SSI_DET_RESULT_INFO_ch2_ssi_det_result_ch_id_START          (20)
#define BBPCOMM_CH2_SSI_DET_RESULT_INFO_ch2_ssi_det_result_ch_id_END            (21)
#define BBPCOMM_CH2_SSI_DET_RESULT_INFO_ch2_ssi_det_result_soft_cfg_flag_START  (22)
#define BBPCOMM_CH2_SSI_DET_RESULT_INFO_ch2_ssi_det_result_soft_cfg_flag_END    (22)


/*****************************************************************************
 结构名    : BBPCOMM_CH2_SSI_DET_RESULT_FLAG_CLR_UNION
 结构说明  : CH2_SSI_DET_RESULT_FLAG_CLR 寄存器结构定义。地址偏移量:0x1508，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      ch2_ssi_det_result_flag_clr_reg;
    struct
    {
        unsigned int  ch2_ssi_det_result_flag_clr : 1;  /* bit[0-0] : 通道2软件检测ssi地址结果清除脉冲，写1清 */
        unsigned int  reserved                    : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_CH2_SSI_DET_RESULT_FLAG_CLR_UNION;
#define BBPCOMM_CH2_SSI_DET_RESULT_FLAG_CLR_ch2_ssi_det_result_flag_clr_START  (0)
#define BBPCOMM_CH2_SSI_DET_RESULT_FLAG_CLR_ch2_ssi_det_result_flag_clr_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_CH3_SSI_DET_RESULT_FLAG_UNION
 结构说明  : CH3_SSI_DET_RESULT_FLAG 寄存器结构定义。地址偏移量:0x150C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      ch3_ssi_det_result_flag_reg;
    struct
    {
        unsigned int  ch3_ssi_det_result_flag : 1;  /* bit[0-0] : 通道3软件检测ssi地址结果：
                                                                  1：检测到ssi指令发送软件配置的地址
                                                                  0：没有检测到ssi指令发送软件配置的地址 */
        unsigned int  reserved                : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_CH3_SSI_DET_RESULT_FLAG_UNION;
#define BBPCOMM_CH3_SSI_DET_RESULT_FLAG_ch3_ssi_det_result_flag_START  (0)
#define BBPCOMM_CH3_SSI_DET_RESULT_FLAG_ch3_ssi_det_result_flag_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_CH3_SSI_DET_RESULT_INFO_UNION
 结构说明  : CH3_SSI_DET_RESULT_INFO 寄存器结构定义。地址偏移量:0x1510，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      ch3_ssi_det_result_info_reg;
    struct
    {
        unsigned int  ch3_ssi_det_result_data          : 16; /* bit[0-15] : 通道3逻辑检测到软件配置的地址后上报指令的配置数据（扩展写指令只上报起始地址配置的数据） */
        unsigned int  ch3_ssi_det_result_ch_mode       : 4;  /* bit[16-19]: 通道3逻辑检测到软件配置的地址后上报指令源来自于哪个BBP的配置 */
        unsigned int  ch3_ssi_det_result_ch_id         : 2;  /* bit[20-21]: 通道3逻辑检测到软件配置的地址后上报指令指令通道id号 */
        unsigned int  ch3_ssi_det_result_soft_cfg_flag : 1;  /* bit[22-22]: 通道3逻辑检测到软件配置的地址后上报指令指令是否由软件配置标志 */
        unsigned int  reserved                         : 9;  /* bit[23-31]: 保留 */
    } reg;
} BBPCOMM_CH3_SSI_DET_RESULT_INFO_UNION;
#define BBPCOMM_CH3_SSI_DET_RESULT_INFO_ch3_ssi_det_result_data_START           (0)
#define BBPCOMM_CH3_SSI_DET_RESULT_INFO_ch3_ssi_det_result_data_END             (15)
#define BBPCOMM_CH3_SSI_DET_RESULT_INFO_ch3_ssi_det_result_ch_mode_START        (16)
#define BBPCOMM_CH3_SSI_DET_RESULT_INFO_ch3_ssi_det_result_ch_mode_END          (19)
#define BBPCOMM_CH3_SSI_DET_RESULT_INFO_ch3_ssi_det_result_ch_id_START          (20)
#define BBPCOMM_CH3_SSI_DET_RESULT_INFO_ch3_ssi_det_result_ch_id_END            (21)
#define BBPCOMM_CH3_SSI_DET_RESULT_INFO_ch3_ssi_det_result_soft_cfg_flag_START  (22)
#define BBPCOMM_CH3_SSI_DET_RESULT_INFO_ch3_ssi_det_result_soft_cfg_flag_END    (22)


/*****************************************************************************
 结构名    : BBPCOMM_CH3_SSI_DET_RESULT_FLAG_CLR_UNION
 结构说明  : CH3_SSI_DET_RESULT_FLAG_CLR 寄存器结构定义。地址偏移量:0x1514，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      ch3_ssi_det_result_flag_clr_reg;
    struct
    {
        unsigned int  ch3_ssi_det_result_flag_clr : 1;  /* bit[0-0] : 通道3软件检测ssi地址结果清除脉冲，写1清 */
        unsigned int  reserved                    : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_CH3_SSI_DET_RESULT_FLAG_CLR_UNION;
#define BBPCOMM_CH3_SSI_DET_RESULT_FLAG_CLR_ch3_ssi_det_result_flag_clr_START  (0)
#define BBPCOMM_CH3_SSI_DET_RESULT_FLAG_CLR_ch3_ssi_det_result_flag_clr_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_DBG_REQ_EN_UNION
 结构说明  : DBG_REQ_EN 寄存器结构定义。地址偏移量:0x1518，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      dbg_req_en_reg;
    struct
    {
        unsigned int  dbg_req_en : 26; /* bit[0-25] : 可维可测轮询请求上报信号使能，dbg_req_en[25:0]对应reg[25:0],如dbg_req_en[X]为1，reg[X]请求有效，dbg_req_en[X]为0，reg[X]请求无效,
                                                      X=0~25 */
        unsigned int  reserved   : 6;  /* bit[26-31]: 保留 */
    } reg;
} BBPCOMM_DBG_REQ_EN_UNION;
#define BBPCOMM_DBG_REQ_EN_dbg_req_en_START  (0)
#define BBPCOMM_DBG_REQ_EN_dbg_req_en_END    (25)


/*****************************************************************************
 结构名    : BBPCOMM_FREE_COUNT_EN_UNION
 结构说明  : FREE_COUNT_EN 寄存器结构定义。地址偏移量:0x1588，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      free_count_en_reg;
    struct
    {
        unsigned int  free_count_en : 1;  /* bit[0-0] : 19.2M钟自由计数软初始值设置使能。 */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_FREE_COUNT_EN_UNION;
#define BBPCOMM_FREE_COUNT_EN_free_count_en_START  (0)
#define BBPCOMM_FREE_COUNT_EN_free_count_en_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_LTE_SOFT_RST_UNION
 结构说明  : LTE_SOFT_RST 寄存器结构定义。地址偏移量:0x1590，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      lte_soft_rst_reg;
    struct
    {
        unsigned int  lte_soft_rst : 1;  /* bit[0-0] : BBP_COMMON输出给LTE模反压busy信号的软复位信号
                                                       1：软复位反压busy信号
                                                       0：不软复位反压busy信号 */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_LTE_SOFT_RST_UNION;
#define BBPCOMM_LTE_SOFT_RST_lte_soft_rst_START  (0)
#define BBPCOMM_LTE_SOFT_RST_lte_soft_rst_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_W_SOFT_RST_UNION
 结构说明  : W_SOFT_RST 寄存器结构定义。地址偏移量:0x1594，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      w_soft_rst_reg;
    struct
    {
        unsigned int  w_soft_rst : 1;  /* bit[0-0] : BBP_COMMON输出给W模反压busy信号的软复位信号
                                                     1：软复位反压busy信号
                                                     0：不软复位反压busy信号 */
        unsigned int  reserved   : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_W_SOFT_RST_UNION;
#define BBPCOMM_W_SOFT_RST_w_soft_rst_START  (0)
#define BBPCOMM_W_SOFT_RST_w_soft_rst_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_TDS_SOFT_RST_UNION
 结构说明  : TDS_SOFT_RST 寄存器结构定义。地址偏移量:0x1598，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      tds_soft_rst_reg;
    struct
    {
        unsigned int  tds_soft_rst : 1;  /* bit[0-0] : BBP_COMMON输出给TDS模反压busy信号的软复位信号
                                                       1：软复位反压busy信号
                                                       0：不软复位反压busy信号 */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_TDS_SOFT_RST_UNION;
#define BBPCOMM_TDS_SOFT_RST_tds_soft_rst_START  (0)
#define BBPCOMM_TDS_SOFT_RST_tds_soft_rst_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_GM_SOFT_RST_UNION
 结构说明  : GM_SOFT_RST 寄存器结构定义。地址偏移量:0x159C，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      gm_soft_rst_reg;
    struct
    {
        unsigned int  gm_soft_rst : 1;  /* bit[0-0] : BBP_COMMON输出给GM模反压busy信号的软复位信号
                                                      1：软复位反压busy信号
                                                      0：不软复位反压busy信号 */
        unsigned int  reserved    : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_GM_SOFT_RST_UNION;
#define BBPCOMM_GM_SOFT_RST_gm_soft_rst_START  (0)
#define BBPCOMM_GM_SOFT_RST_gm_soft_rst_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_GS_SOFT_RST_UNION
 结构说明  : GS_SOFT_RST 寄存器结构定义。地址偏移量:0x15A0，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      gs_soft_rst_reg;
    struct
    {
        unsigned int  gs_soft_rst : 1;  /* bit[0-0] : BBP_COMMON输出给GS模反压busy信号的软复位信号
                                                      1：软复位反压busy信号
                                                      0：不软复位反压busy信号 */
        unsigned int  reserved    : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_GS_SOFT_RST_UNION;
#define BBPCOMM_GS_SOFT_RST_gs_soft_rst_START  (0)
#define BBPCOMM_GS_SOFT_RST_gs_soft_rst_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_C_SOFT_RST_UNION
 结构说明  : C_SOFT_RST 寄存器结构定义。地址偏移量:0x15A4，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c_soft_rst_reg;
    struct
    {
        unsigned int  c_soft_rst : 1;  /* bit[0-0] : BBP_COMMON输出给C2模反压busy信号的软复位信号
                                                     1：软复位反压busy信号
                                                     0：不软复位反压busy信号 */
        unsigned int  reserved   : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_C_SOFT_RST_UNION;
#define BBPCOMM_C_SOFT_RST_c_soft_rst_START  (0)
#define BBPCOMM_C_SOFT_RST_c_soft_rst_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_TCVR_ON_CFG_OUT0_UNION
 结构说明  : TCVR_ON_CFG_OUT0 寄存器结构定义。地址偏移量:0x15A8，初值:0x00000001，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      tcvr_on_cfg_out0_reg;
    struct
    {
        unsigned int  tcvr_on_cfg_out0 : 1;  /* bit[0-0] : tcvr_on输出pin脚0信号源选择开关：
                                                           0：来自于通道0的逻辑选择输出；
                                                           1：来自于软件配置输出； */
        unsigned int  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_TCVR_ON_CFG_OUT0_UNION;
#define BBPCOMM_TCVR_ON_CFG_OUT0_tcvr_on_cfg_out0_START  (0)
#define BBPCOMM_TCVR_ON_CFG_OUT0_tcvr_on_cfg_out0_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_TCVR_ON_CFG_OUT1_UNION
 结构说明  : TCVR_ON_CFG_OUT1 寄存器结构定义。地址偏移量:0x15AC，初值:0x00000001，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      tcvr_on_cfg_out1_reg;
    struct
    {
        unsigned int  tcvr_on_cfg_out1 : 1;  /* bit[0-0] : tcvr_on输出pin脚1信号源选择开关：
                                                           0：来自于通道0的逻辑选择输出；
                                                           1：来自于软件配置输出； */
        unsigned int  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_TCVR_ON_CFG_OUT1_UNION;
#define BBPCOMM_TCVR_ON_CFG_OUT1_tcvr_on_cfg_out1_START  (0)
#define BBPCOMM_TCVR_ON_CFG_OUT1_tcvr_on_cfg_out1_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_LTE_TCVR_ON_CFG_PIN0_UNION
 结构说明  : LTE_TCVR_ON_CFG_PIN0 寄存器结构定义。地址偏移量:0x15B0，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      lte_tcvr_on_cfg_pin0_reg;
    struct
    {
        unsigned int  lte_tcvr_on_cfg_pin0 : 1;  /* bit[0-0] : 软件配置LTE模tcvr_on信号控制外围
                                                               pin脚0的tcvr_on信号输出
                                                               配置1为拉高，0为拉低 */
        unsigned int  reserved             : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_LTE_TCVR_ON_CFG_PIN0_UNION;
#define BBPCOMM_LTE_TCVR_ON_CFG_PIN0_lte_tcvr_on_cfg_pin0_START  (0)
#define BBPCOMM_LTE_TCVR_ON_CFG_PIN0_lte_tcvr_on_cfg_pin0_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_W_TCVR_ON_CFG_PIN0_UNION
 结构说明  : W_TCVR_ON_CFG_PIN0 寄存器结构定义。地址偏移量:0x15B4，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      w_tcvr_on_cfg_pin0_reg;
    struct
    {
        unsigned int  w_tcvr_on_cfg_pin0 : 1;  /* bit[0-0] : 软件配置W模tcvr_on信号控制外围
                                                             pin脚0的tcvr_on信号输出
                                                             配置1为拉高，0为拉低 */
        unsigned int  reserved           : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_W_TCVR_ON_CFG_PIN0_UNION;
#define BBPCOMM_W_TCVR_ON_CFG_PIN0_w_tcvr_on_cfg_pin0_START  (0)
#define BBPCOMM_W_TCVR_ON_CFG_PIN0_w_tcvr_on_cfg_pin0_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_TDS_TCVR_ON_CFG_PIN0_UNION
 结构说明  : TDS_TCVR_ON_CFG_PIN0 寄存器结构定义。地址偏移量:0x15B8，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      tds_tcvr_on_cfg_pin0_reg;
    struct
    {
        unsigned int  tds_tcvr_on_cfg_pin0 : 1;  /* bit[0-0] : 软件配置TDS模tcvr_on信号控制外围
                                                               pin脚0的tcvr_on信号输出
                                                               配置1为拉高，0为拉低 */
        unsigned int  reserved             : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_TDS_TCVR_ON_CFG_PIN0_UNION;
#define BBPCOMM_TDS_TCVR_ON_CFG_PIN0_tds_tcvr_on_cfg_pin0_START  (0)
#define BBPCOMM_TDS_TCVR_ON_CFG_PIN0_tds_tcvr_on_cfg_pin0_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_GM_TCVR_ON_CFG_PIN0_UNION
 结构说明  : GM_TCVR_ON_CFG_PIN0 寄存器结构定义。地址偏移量:0x15BC，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      gm_tcvr_on_cfg_pin0_reg;
    struct
    {
        unsigned int  gm_tcvr_on_cfg_pin0 : 1;  /* bit[0-0] : 软件配置GM模tcvr_on信号控制外围
                                                              pin脚0的tcvr_on信号输出
                                                              配置1为拉高，0为拉低 */
        unsigned int  reserved            : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_GM_TCVR_ON_CFG_PIN0_UNION;
#define BBPCOMM_GM_TCVR_ON_CFG_PIN0_gm_tcvr_on_cfg_pin0_START  (0)
#define BBPCOMM_GM_TCVR_ON_CFG_PIN0_gm_tcvr_on_cfg_pin0_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_GS_TCVR_ON_CFG_PIN0_UNION
 结构说明  : GS_TCVR_ON_CFG_PIN0 寄存器结构定义。地址偏移量:0x15C0，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      gs_tcvr_on_cfg_pin0_reg;
    struct
    {
        unsigned int  gs_tcvr_on_cfg_pin0 : 1;  /* bit[0-0] : 软件配置GS模tcvr_on信号控制外围
                                                              pin脚0的tcvr_on信号输出
                                                              配置1为拉高，0为拉低 */
        unsigned int  reserved            : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_GS_TCVR_ON_CFG_PIN0_UNION;
#define BBPCOMM_GS_TCVR_ON_CFG_PIN0_gs_tcvr_on_cfg_pin0_START  (0)
#define BBPCOMM_GS_TCVR_ON_CFG_PIN0_gs_tcvr_on_cfg_pin0_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_C_TCVR_ON_CFG_PIN0_UNION
 结构说明  : C_TCVR_ON_CFG_PIN0 寄存器结构定义。地址偏移量:0x15C4，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c_tcvr_on_cfg_pin0_reg;
    struct
    {
        unsigned int  c_tcvr_on_cfg_pin0 : 1;  /* bit[0-0] : 软件配置C2模tcvr_on信号控制外围
                                                             pin脚0的tcvr_on信号输出
                                                             配置1为拉高，0为拉低 */
        unsigned int  reserved           : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_C_TCVR_ON_CFG_PIN0_UNION;
#define BBPCOMM_C_TCVR_ON_CFG_PIN0_c_tcvr_on_cfg_pin0_START  (0)
#define BBPCOMM_C_TCVR_ON_CFG_PIN0_c_tcvr_on_cfg_pin0_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_LTE_TCVR_ON_CFG_PIN1_UNION
 结构说明  : LTE_TCVR_ON_CFG_PIN1 寄存器结构定义。地址偏移量:0x15C8，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      lte_tcvr_on_cfg_pin1_reg;
    struct
    {
        unsigned int  lte_tcvr_on_cfg_pin1 : 1;  /* bit[0-0] : 软件配置LTE模tcvr_on信号控制外围
                                                               pin脚1的tcvr_on信号输出
                                                               配置1为拉高，0为拉低 */
        unsigned int  reserved             : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_LTE_TCVR_ON_CFG_PIN1_UNION;
#define BBPCOMM_LTE_TCVR_ON_CFG_PIN1_lte_tcvr_on_cfg_pin1_START  (0)
#define BBPCOMM_LTE_TCVR_ON_CFG_PIN1_lte_tcvr_on_cfg_pin1_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_W_TCVR_ON_CFG_PIN1_UNION
 结构说明  : W_TCVR_ON_CFG_PIN1 寄存器结构定义。地址偏移量:0x15CC，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      w_tcvr_on_cfg_pin1_reg;
    struct
    {
        unsigned int  w_tcvr_on_cfg_pin1 : 1;  /* bit[0-0] : 软件配置W模tcvr_on信号控制外围
                                                             pin脚1的tcvr_on信号输出
                                                             配置1为拉高，0为拉低 */
        unsigned int  reserved           : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_W_TCVR_ON_CFG_PIN1_UNION;
#define BBPCOMM_W_TCVR_ON_CFG_PIN1_w_tcvr_on_cfg_pin1_START  (0)
#define BBPCOMM_W_TCVR_ON_CFG_PIN1_w_tcvr_on_cfg_pin1_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_TDS_TCVR_ON_CFG_PIN1_UNION
 结构说明  : TDS_TCVR_ON_CFG_PIN1 寄存器结构定义。地址偏移量:0x15D0，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      tds_tcvr_on_cfg_pin1_reg;
    struct
    {
        unsigned int  tds_tcvr_on_cfg_pin1 : 1;  /* bit[0-0] : 软件配置TDS模tcvr_on信号控制外围
                                                               pin脚1的tcvr_on信号输出
                                                               配置1为拉高，0为拉低 */
        unsigned int  reserved             : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_TDS_TCVR_ON_CFG_PIN1_UNION;
#define BBPCOMM_TDS_TCVR_ON_CFG_PIN1_tds_tcvr_on_cfg_pin1_START  (0)
#define BBPCOMM_TDS_TCVR_ON_CFG_PIN1_tds_tcvr_on_cfg_pin1_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_GM_TCVR_ON_CFG_PIN1_UNION
 结构说明  : GM_TCVR_ON_CFG_PIN1 寄存器结构定义。地址偏移量:0x15D4，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      gm_tcvr_on_cfg_pin1_reg;
    struct
    {
        unsigned int  gm_tcvr_on_cfg_pin1 : 1;  /* bit[0-0] : 软件配置GM模tcvr_on信号控制外围
                                                              pin脚1的tcvr_on信号输出
                                                              配置1为拉高，0为拉低 */
        unsigned int  reserved            : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_GM_TCVR_ON_CFG_PIN1_UNION;
#define BBPCOMM_GM_TCVR_ON_CFG_PIN1_gm_tcvr_on_cfg_pin1_START  (0)
#define BBPCOMM_GM_TCVR_ON_CFG_PIN1_gm_tcvr_on_cfg_pin1_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_GS_TCVR_ON_CFG_PIN1_UNION
 结构说明  : GS_TCVR_ON_CFG_PIN1 寄存器结构定义。地址偏移量:0x15D8，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      gs_tcvr_on_cfg_pin1_reg;
    struct
    {
        unsigned int  gs_tcvr_on_cfg_pin1 : 1;  /* bit[0-0] : 软件配置GS模tcvr_on信号控制外围
                                                              pin脚1的tcvr_on信号输出
                                                              配置1为拉高，0为拉低 */
        unsigned int  reserved            : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_GS_TCVR_ON_CFG_PIN1_UNION;
#define BBPCOMM_GS_TCVR_ON_CFG_PIN1_gs_tcvr_on_cfg_pin1_START  (0)
#define BBPCOMM_GS_TCVR_ON_CFG_PIN1_gs_tcvr_on_cfg_pin1_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_C_TCVR_ON_CFG_PIN1_UNION
 结构说明  : C_TCVR_ON_CFG_PIN1 寄存器结构定义。地址偏移量:0x15DC，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      c_tcvr_on_cfg_pin1_reg;
    struct
    {
        unsigned int  c_tcvr_on_cfg_pin1 : 1;  /* bit[0-0] : 软件配置C2模tcvr_on信号控制外围
                                                             pin脚1的tcvr_on信号输出
                                                             配置1为拉高，0为拉低 */
        unsigned int  reserved           : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_C_TCVR_ON_CFG_PIN1_UNION;
#define BBPCOMM_C_TCVR_ON_CFG_PIN1_c_tcvr_on_cfg_pin1_START  (0)
#define BBPCOMM_C_TCVR_ON_CFG_PIN1_c_tcvr_on_cfg_pin1_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_TCVR_ON_DLY_CYCLE_UNION
 结构说明  : TCVR_ON_DLY_CYCLE 寄存器结构定义。地址偏移量:0x15E0，初值:0x0000001A，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      tcvr_on_dly_cycle_reg;
    struct
    {
        unsigned int  tcvr_on_dly_cycle : 6;  /* bit[0-5] : 各通道实际输出tcvr_on延迟的配置值，
                                                            最大支持64个cycle，单位为19.2M钟 */
        unsigned int  reserved          : 26; /* bit[6-31]: 保留 */
    } reg;
} BBPCOMM_TCVR_ON_DLY_CYCLE_UNION;
#define BBPCOMM_TCVR_ON_DLY_CYCLE_tcvr_on_dly_cycle_START  (0)
#define BBPCOMM_TCVR_ON_DLY_CYCLE_tcvr_on_dly_cycle_END    (5)


/*****************************************************************************
 结构名    : BBPCOMM_REG_CLK_SEL_UNION
 结构说明  : REG_CLK_SEL 寄存器结构定义。地址偏移量:0x15E4，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      reg_clk_sel_reg;
    struct
    {
        unsigned int  reg_clk_sel : 1;  /* bit[0-0] : 寄存器模块时钟门控选择：
                                                      0：时钟门控
                                                      1：时钟常开 */
        unsigned int  reserved    : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_REG_CLK_SEL_UNION;
#define BBPCOMM_REG_CLK_SEL_reg_clk_sel_START  (0)
#define BBPCOMM_REG_CLK_SEL_reg_clk_sel_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_TUNER_MIPI_MASK_UNION
 结构说明  : TUNER_MIPI_MASK 寄存器结构定义。地址偏移量:0x15E8，初值:0x0000000F，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      tuner_mipi_mask_reg;
    struct
    {
        unsigned int  tuner_mipi_mask_ch0 : 1;  /* bit[0-0] : 通道0的tuner mipi自动交换功能屏蔽寄存器
                                                              0：使用tuner输出结果
                                                              1：bypass tuner输出结果，tuner mipi指令不能从CTU通道0输出 */
        unsigned int  tuner_mipi_mask_ch1 : 1;  /* bit[1-1] : 通道1的tuner mipi自动交换功能屏蔽寄存器
                                                              0：使用tuner输出结果
                                                              1：bypass tuner输出结果，tuner mipi指令不能从CTU通道1输出 */
        unsigned int  tuner_mipi_mask_ch2 : 1;  /* bit[2-2] : 通道2的tuner mipi自动交换功能屏蔽寄存器
                                                              0：使用tuner输出结果
                                                              1：bypass tuner输出结果，tuner mipi指令不能从CTU通道2输出 */
        unsigned int  tuner_mipi_mask_ch3 : 1;  /* bit[3-3] : 通道3的tuner mipi自动交换功能屏蔽寄存器
                                                              0：使用tuner输出结果
                                                              1：bypass tuner输出结果，tuner mipi指令不能从CTU通道3输出 */
        unsigned int  reserved            : 28; /* bit[4-31]: 保留 */
    } reg;
} BBPCOMM_TUNER_MIPI_MASK_UNION;
#define BBPCOMM_TUNER_MIPI_MASK_tuner_mipi_mask_ch0_START  (0)
#define BBPCOMM_TUNER_MIPI_MASK_tuner_mipi_mask_ch0_END    (0)
#define BBPCOMM_TUNER_MIPI_MASK_tuner_mipi_mask_ch1_START  (1)
#define BBPCOMM_TUNER_MIPI_MASK_tuner_mipi_mask_ch1_END    (1)
#define BBPCOMM_TUNER_MIPI_MASK_tuner_mipi_mask_ch2_START  (2)
#define BBPCOMM_TUNER_MIPI_MASK_tuner_mipi_mask_ch2_END    (2)
#define BBPCOMM_TUNER_MIPI_MASK_tuner_mipi_mask_ch3_START  (3)
#define BBPCOMM_TUNER_MIPI_MASK_tuner_mipi_mask_ch3_END    (3)


/*****************************************************************************
 结构名    : BBPCOMM_TNNER_GPIO_M0_LINE_P_MASK_UNION
 结构说明  : TNNER_GPIO_M0_LINE_P_MASK 寄存器结构定义。地址偏移量:0x15EC，初值:0x00000001，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      tnner_gpio_m0_line_p_mask_reg;
    struct
    {
        unsigned int  tuner_gpio_m0_line_p_mask : 1;  /* bit[0-0] : tuner gpio m0_line_p线控屏蔽寄存器
                                                                    0：使用tuner输出值
                                                                    1：bypass tuner输出值，使用CTU输出值 */
        unsigned int  reserved                  : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_TNNER_GPIO_M0_LINE_P_MASK_UNION;
#define BBPCOMM_TNNER_GPIO_M0_LINE_P_MASK_tuner_gpio_m0_line_p_mask_START  (0)
#define BBPCOMM_TNNER_GPIO_M0_LINE_P_MASK_tuner_gpio_m0_line_p_mask_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_TNNER_GPIO_M0_LINE_S_MASK_UNION
 结构说明  : TNNER_GPIO_M0_LINE_S_MASK 寄存器结构定义。地址偏移量:0x15F0，初值:0x00000001，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      tnner_gpio_m0_line_s_mask_reg;
    struct
    {
        unsigned int  tuner_gpio_m0_line_s_mask : 1;  /* bit[0-0] : tuner gpio m0_line_s线控屏蔽寄存器
                                                                    0：使用tuner输出值
                                                                    1：bypass tuner输出值，使用CTU输出值 */
        unsigned int  reserved                  : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_TNNER_GPIO_M0_LINE_S_MASK_UNION;
#define BBPCOMM_TNNER_GPIO_M0_LINE_S_MASK_tuner_gpio_m0_line_s_mask_START  (0)
#define BBPCOMM_TNNER_GPIO_M0_LINE_S_MASK_tuner_gpio_m0_line_s_mask_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_TNNER_GPIO_M1_LINE_MASK_UNION
 结构说明  : TNNER_GPIO_M1_LINE_MASK 寄存器结构定义。地址偏移量:0x15F4，初值:0x00000001，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      tnner_gpio_m1_line_mask_reg;
    struct
    {
        unsigned int  tuner_gpio_m1_line_mask : 1;  /* bit[0-0] : tuner gpio m1_line线控屏蔽寄存器
                                                                  0：使用tuner输出值
                                                                  1：bypass tuner输出值，使用CTU输出值 */
        unsigned int  reserved                : 31; /* bit[1-31]: 保留 */
    } reg;
} BBPCOMM_TNNER_GPIO_M1_LINE_MASK_UNION;
#define BBPCOMM_TNNER_GPIO_M1_LINE_MASK_tuner_gpio_m1_line_mask_START  (0)
#define BBPCOMM_TNNER_GPIO_M1_LINE_MASK_tuner_gpio_m1_line_mask_END    (0)


/*****************************************************************************
 结构名    : BBPCOMM_BBC_TX_RX_CLK_FLAG_UNION
 结构说明  : BBC_TX_RX_CLK_FLAG 寄存器结构定义。地址偏移量:0x15F8，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      bbc_tx_rx_clk_flag_reg;
    struct
    {
        unsigned int  bbc_tx_rx_clk_flag : 27; /* bit[0-26] : BBC上行行时钟工作状态指示：
                                                              bit0:abb接收通道0随路时钟工作状态指示；
                                                              bit1:abb接收通道1随路时钟工作状态指示；
                                                              bit2:abb接收通道2随路时钟工作状态指示；
                                                              bit3:abb接收通道3随路时钟工作状态指示；
                                                              bit4:lte_ch0下行接收时钟工作状态指示；
                                                              bit5:lte_ch1下行接收时钟工作状态指示；
                                                              bit6:lte_ch2下行接收时钟工作状态指示；
                                                              bit7:lte_ch3下行接收时钟工作状态指示；
                                                              bit8:W下行接收时钟工作状态指示；
                                                              bit9:TDS下行接收时钟工作状态指示；
                                                              bit10:GM下行接收时钟工作状态指示；
                                                              bit11:GS下行接收时钟工作状态指示；
                                                              bit12:C下行接收时钟工作状态指示；
                                                              bit13~bit15：reserved；
                                                              bit16:abb发送通道0随路时钟工作状态指示；
                                                              bit17:abb发送通道1随路时钟工作状态指示；
                                                              bit18~bit19：reserved；
                                                              bit20:lte_ch0上行发送时钟工作状态指示；
                                                              bit21:lte_ch1上行发送时钟工作状态指示；
                                                              bit22:W上行发送时钟工作状态指示；
                                                              bit23:TDS上行发送时钟工作状态指示；
                                                              bit24:GM上行发送时钟工作状态指示；
                                                              bit25:GS上行发送时钟工作状态指示；
                                                              bit26:C上行发送时钟工作状态指示；
                                                              bit27~bit31：reserved； */
        unsigned int  reserved           : 5;  /* bit[27-31]: 保留 */
    } reg;
} BBPCOMM_BBC_TX_RX_CLK_FLAG_UNION;
#define BBPCOMM_BBC_TX_RX_CLK_FLAG_bbc_tx_rx_clk_flag_START  (0)
#define BBPCOMM_BBC_TX_RX_CLK_FLAG_bbc_tx_rx_clk_flag_END    (26)


/*****************************************************************************
 结构名    : BBPCOMM_MIPI_SSI_STATE_UNION
 结构说明  : MIPI_SSI_STATE 寄存器结构定义。地址偏移量:0x15FC，初值:0x00000000，宽度:32
 寄存器说明: 寄存器
*****************************************************************************/
typedef union
{
    unsigned int      mipi_ssi_state_reg;
    struct
    {
        unsigned int  com2lte_ch0_busy_ssi  : 1;  /* bit[0]    : LTE CH0 SSI 忙标志 */
        unsigned int  com2lte_ch1_busy_ssi  : 1;  /* bit[1]    : LTE CH1 SSI 忙标志 */
        unsigned int  com2lte_ch2_busy_ssi  : 1;  /* bit[2]    : LTE CH2 SSI 忙标志 */
        unsigned int  com2lte_ch3_busy_ssi  : 1;  /* bit[3]    : LTE CH3 SSI 忙标志 */
        unsigned int  com2w_busy_ssi        : 1;  /* bit[4]    : W SSI 忙标志 */
        unsigned int  com2tds_busy_ssi      : 1;  /* bit[5]    : TDS  SSI 忙标志 */
        unsigned int  com2gm_busy_ssi       : 1;  /* bit[6]    : GM  SSI 忙标志 */
        unsigned int  com2gs_busy_ssi       : 1;  /* bit[7]    : GS SSI 忙标志 */
        unsigned int  com2c_busy_ssi        : 1;  /* bit[8]    : C2 SSI 忙标志 */
        unsigned int  com2lte_ch0_busy_mipi : 1;  /* bit[9]    : LTE CH0 MIPI 忙标志 */
        unsigned int  com2lte_ch1_busy_mipi : 1;  /* bit[10]   : LTE CH1 MIPI 忙标志 */
        unsigned int  com2lte_ch2_busy_mipi : 1;  /* bit[11]   : LTE CH2 MIPI 忙标志 */
        unsigned int  com2lte_ch3_busy_mipi : 1;  /* bit[12]   : LTE CH3 MIPI 忙标志 */
        unsigned int  com2w_busy_mipi       : 1;  /* bit[13]   : W MIPI 忙标志 */
        unsigned int  com2tds_busy_mipi     : 1;  /* bit[14]   : TDS MIPI 忙标志 */
        unsigned int  com2gm_busy_mipi      : 1;  /* bit[15]   : GM MIPI 忙标志 */
        unsigned int  com2gs_busy_mipi      : 1;  /* bit[16]   : GS MIPI 忙标志 */
        unsigned int  com2c_busy_mipi       : 1;  /* bit[17]   : C2 MIPI 忙标志 */
        unsigned int  reserved              : 14; /* bit[18-31]: 保留 */
    } reg;
} BBPCOMM_MIPI_SSI_STATE_UNION;
#define BBPCOMM_MIPI_SSI_STATE_com2lte_ch0_busy_ssi_START   (0)
#define BBPCOMM_MIPI_SSI_STATE_com2lte_ch0_busy_ssi_END     (0)
#define BBPCOMM_MIPI_SSI_STATE_com2lte_ch1_busy_ssi_START   (1)
#define BBPCOMM_MIPI_SSI_STATE_com2lte_ch1_busy_ssi_END     (1)
#define BBPCOMM_MIPI_SSI_STATE_com2lte_ch2_busy_ssi_START   (2)
#define BBPCOMM_MIPI_SSI_STATE_com2lte_ch2_busy_ssi_END     (2)
#define BBPCOMM_MIPI_SSI_STATE_com2lte_ch3_busy_ssi_START   (3)
#define BBPCOMM_MIPI_SSI_STATE_com2lte_ch3_busy_ssi_END     (3)
#define BBPCOMM_MIPI_SSI_STATE_com2w_busy_ssi_START         (4)
#define BBPCOMM_MIPI_SSI_STATE_com2w_busy_ssi_END           (4)
#define BBPCOMM_MIPI_SSI_STATE_com2tds_busy_ssi_START       (5)
#define BBPCOMM_MIPI_SSI_STATE_com2tds_busy_ssi_END         (5)
#define BBPCOMM_MIPI_SSI_STATE_com2gm_busy_ssi_START        (6)
#define BBPCOMM_MIPI_SSI_STATE_com2gm_busy_ssi_END          (6)
#define BBPCOMM_MIPI_SSI_STATE_com2gs_busy_ssi_START        (7)
#define BBPCOMM_MIPI_SSI_STATE_com2gs_busy_ssi_END          (7)
#define BBPCOMM_MIPI_SSI_STATE_com2c_busy_ssi_START         (8)
#define BBPCOMM_MIPI_SSI_STATE_com2c_busy_ssi_END           (8)
#define BBPCOMM_MIPI_SSI_STATE_com2lte_ch0_busy_mipi_START  (9)
#define BBPCOMM_MIPI_SSI_STATE_com2lte_ch0_busy_mipi_END    (9)
#define BBPCOMM_MIPI_SSI_STATE_com2lte_ch1_busy_mipi_START  (10)
#define BBPCOMM_MIPI_SSI_STATE_com2lte_ch1_busy_mipi_END    (10)
#define BBPCOMM_MIPI_SSI_STATE_com2lte_ch2_busy_mipi_START  (11)
#define BBPCOMM_MIPI_SSI_STATE_com2lte_ch2_busy_mipi_END    (11)
#define BBPCOMM_MIPI_SSI_STATE_com2lte_ch3_busy_mipi_START  (12)
#define BBPCOMM_MIPI_SSI_STATE_com2lte_ch3_busy_mipi_END    (12)
#define BBPCOMM_MIPI_SSI_STATE_com2w_busy_mipi_START        (13)
#define BBPCOMM_MIPI_SSI_STATE_com2w_busy_mipi_END          (13)
#define BBPCOMM_MIPI_SSI_STATE_com2tds_busy_mipi_START      (14)
#define BBPCOMM_MIPI_SSI_STATE_com2tds_busy_mipi_END        (14)
#define BBPCOMM_MIPI_SSI_STATE_com2gm_busy_mipi_START       (15)
#define BBPCOMM_MIPI_SSI_STATE_com2gm_busy_mipi_END         (15)
#define BBPCOMM_MIPI_SSI_STATE_com2gs_busy_mipi_START       (16)
#define BBPCOMM_MIPI_SSI_STATE_com2gs_busy_mipi_END         (16)
#define BBPCOMM_MIPI_SSI_STATE_com2c_busy_mipi_START        (17)
#define BBPCOMM_MIPI_SSI_STATE_com2c_busy_mipi_END          (17)


/***======================================================================***
                     (2/3) register_define_mipi_tuner
 ***======================================================================***/
/*****************************************************************************
 结构名    : BBPCOMM_MIPI_TUNER_EN_UNION
 结构说明  : MIPI_TUNER_EN 寄存器结构定义。地址偏移量:0x0，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      mipi_tuner_en_reg;
    struct
    {
        unsigned int  cpu_mipi_tuner_en_imi        : 1;  /* bit[0]   : MIPI_TUNER模块使能开关，0表示关闭，1表示打开。 */
        unsigned int  reserved_0                   : 3;  /* bit[1-3] :  */
        unsigned int  cpu_mipi_tuner_queue_clr_imi : 1;  /* bit[4]   : MIPI_tuner模块 */
        unsigned int  reserved_1                   : 27; /* bit[5-31]:  */
    } reg;
} BBPCOMM_MIPI_TUNER_EN_UNION;
#define BBPCOMM_MIPI_TUNER_EN_cpu_mipi_tuner_en_imi_START         (0)
#define BBPCOMM_MIPI_TUNER_EN_cpu_mipi_tuner_en_imi_END           (0)
#define BBPCOMM_MIPI_TUNER_EN_cpu_mipi_tuner_queue_clr_imi_START  (4)
#define BBPCOMM_MIPI_TUNER_EN_cpu_mipi_tuner_queue_clr_imi_END    (4)


/*****************************************************************************
 结构名    : BBPCOMM_MIPI_TUNER_REQ_EN_UNION
 结构说明  : MIPI_TUNER_REQ_EN 寄存器结构定义。地址偏移量:0x4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      mipi_tuner_req_en_reg;
    struct
    {
        unsigned int  m0_tas_ind_p_req_en_imi : 1;  /* bit[0]   : 主卡主载波TAS切换使能开关，0表示关闭，1表示打开。 */
        unsigned int  m1_active_p_req_en_imi  : 1;  /* bit[1]   : 主卡主载波副卡有效使能开关，0表示关闭，1表示打开。 */
        unsigned int  m0_line_p_req_en_imi    : 1;  /* bit[2]   : 主卡主载波线控切换使能开关，0表示关闭，1表示打开。 */
        unsigned int  m0_tas_ind_s_req_en_imi : 1;  /* bit[3]   : 主卡辅载波TAS切换使能开关，0表示关闭，1表示打开。 */
        unsigned int  m1_active_s_req_en_imi  : 1;  /* bit[4]   : 主卡辅载波副卡有效使能开关，0表示关闭，1表示打开。 */
        unsigned int  m0_line_s_req_ind_imi   : 1;  /* bit[5]   : 主卡辅载波线控切换使能开关，0表示关闭，1表示打开。 */
        unsigned int  m1_tas_ind_req_en_imi   : 1;  /* bit[6]   : 副卡TAS切换使能开关，0表示关闭，1表示打开。 */
        unsigned int  m0_active_req_en_imi    : 1;  /* bit[7]   : 副卡主卡使能开关，0表示关闭，1表示打开。 */
        unsigned int  m1_line_req_en_imi      : 1;  /* bit[8]   : 副卡线控使能开关，0表示关闭，1表示打开。 */
        unsigned int  reserved                : 23; /* bit[9-31]:  */
    } reg;
} BBPCOMM_MIPI_TUNER_REQ_EN_UNION;
#define BBPCOMM_MIPI_TUNER_REQ_EN_m0_tas_ind_p_req_en_imi_START  (0)
#define BBPCOMM_MIPI_TUNER_REQ_EN_m0_tas_ind_p_req_en_imi_END    (0)
#define BBPCOMM_MIPI_TUNER_REQ_EN_m1_active_p_req_en_imi_START   (1)
#define BBPCOMM_MIPI_TUNER_REQ_EN_m1_active_p_req_en_imi_END     (1)
#define BBPCOMM_MIPI_TUNER_REQ_EN_m0_line_p_req_en_imi_START     (2)
#define BBPCOMM_MIPI_TUNER_REQ_EN_m0_line_p_req_en_imi_END       (2)
#define BBPCOMM_MIPI_TUNER_REQ_EN_m0_tas_ind_s_req_en_imi_START  (3)
#define BBPCOMM_MIPI_TUNER_REQ_EN_m0_tas_ind_s_req_en_imi_END    (3)
#define BBPCOMM_MIPI_TUNER_REQ_EN_m1_active_s_req_en_imi_START   (4)
#define BBPCOMM_MIPI_TUNER_REQ_EN_m1_active_s_req_en_imi_END     (4)
#define BBPCOMM_MIPI_TUNER_REQ_EN_m0_line_s_req_ind_imi_START    (5)
#define BBPCOMM_MIPI_TUNER_REQ_EN_m0_line_s_req_ind_imi_END      (5)
#define BBPCOMM_MIPI_TUNER_REQ_EN_m1_tas_ind_req_en_imi_START    (6)
#define BBPCOMM_MIPI_TUNER_REQ_EN_m1_tas_ind_req_en_imi_END      (6)
#define BBPCOMM_MIPI_TUNER_REQ_EN_m0_active_req_en_imi_START     (7)
#define BBPCOMM_MIPI_TUNER_REQ_EN_m0_active_req_en_imi_END       (7)
#define BBPCOMM_MIPI_TUNER_REQ_EN_m1_line_req_en_imi_START       (8)
#define BBPCOMM_MIPI_TUNER_REQ_EN_m1_line_req_en_imi_END         (8)


/*****************************************************************************
 结构名    : BBPCOMM_MIPI_OT_CNT_UNION
 结构说明  : MIPI_OT_CNT 寄存器结构定义。地址偏移量:0x10，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      mipi_ot_cnt_reg;
    struct
    {
        unsigned int  mipi_ot_cnt : 16; /* bit[0-15] : 状态机超时计时器 */
        unsigned int  reserved    : 16; /* bit[16-31]:  */
    } reg;
} BBPCOMM_MIPI_OT_CNT_UNION;
#define BBPCOMM_MIPI_OT_CNT_mipi_ot_cnt_START  (0)
#define BBPCOMM_MIPI_OT_CNT_mipi_ot_cnt_END    (15)


/*****************************************************************************
 结构名    : BBPCOMM_QUEUE_BUSY_IND_UNION
 结构说明  : QUEUE_BUSY_IND 寄存器结构定义。地址偏移量:0x14，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      queue_busy_ind_reg;
    struct
    {
        unsigned int  req0_busy : 1;  /* bit[0]   : 轮询状态上报 */
        unsigned int  req1_busy : 1;  /* bit[1]   : 轮询状态上报 */
        unsigned int  req2_busy : 1;  /* bit[2]   : 轮询状态上报 */
        unsigned int  reserved  : 29; /* bit[3-31]:  */
    } reg;
} BBPCOMM_QUEUE_BUSY_IND_UNION;
#define BBPCOMM_QUEUE_BUSY_IND_req0_busy_START  (0)
#define BBPCOMM_QUEUE_BUSY_IND_req0_busy_END    (0)
#define BBPCOMM_QUEUE_BUSY_IND_req1_busy_START  (1)
#define BBPCOMM_QUEUE_BUSY_IND_req1_busy_END    (1)
#define BBPCOMM_QUEUE_BUSY_IND_req2_busy_START  (2)
#define BBPCOMM_QUEUE_BUSY_IND_req2_busy_END    (2)


/*****************************************************************************
 结构名    : BBPCOMM_M_GEN_RPT_UNION
 结构说明  : M_GEN_RPT 寄存器结构定义。地址偏移量:0x18，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      m_gen_rpt_reg;
    struct
    {
        unsigned int  m0_sync_status_p : 6;  /* bit[0-5]  : m0_p当前状态值 */
        unsigned int  m0_p_fifo_empty  : 1;  /* bit[6]    : m0_p fifo状态上报 */
        unsigned int  m0_p_fifo_full   : 1;  /* bit[7]    : m0_p fifo状态上报 */
        unsigned int  m0_sync_status_s : 6;  /* bit[8-13] : m0_s当前状态值 */
        unsigned int  m0_s_fifo_empty  : 1;  /* bit[14]   : m0_s fifo状态上报 */
        unsigned int  m0_s_fifo_full   : 1;  /* bit[15]   : m0_s fifo状态上报 */
        unsigned int  m1_sync_status   : 8;  /* bit[16-23]: m1当前状态值 */
        unsigned int  m1_fifo_empty    : 1;  /* bit[24]   : m1 fifo状态上报 */
        unsigned int  m1_fifo_full     : 1;  /* bit[25]   : m1 fifo状态上报 */
        unsigned int  reserved         : 6;  /* bit[26-31]:  */
    } reg;
} BBPCOMM_M_GEN_RPT_UNION;
#define BBPCOMM_M_GEN_RPT_m0_sync_status_p_START  (0)
#define BBPCOMM_M_GEN_RPT_m0_sync_status_p_END    (5)
#define BBPCOMM_M_GEN_RPT_m0_p_fifo_empty_START   (6)
#define BBPCOMM_M_GEN_RPT_m0_p_fifo_empty_END     (6)
#define BBPCOMM_M_GEN_RPT_m0_p_fifo_full_START    (7)
#define BBPCOMM_M_GEN_RPT_m0_p_fifo_full_END      (7)
#define BBPCOMM_M_GEN_RPT_m0_sync_status_s_START  (8)
#define BBPCOMM_M_GEN_RPT_m0_sync_status_s_END    (13)
#define BBPCOMM_M_GEN_RPT_m0_s_fifo_empty_START   (14)
#define BBPCOMM_M_GEN_RPT_m0_s_fifo_empty_END     (14)
#define BBPCOMM_M_GEN_RPT_m0_s_fifo_full_START    (15)
#define BBPCOMM_M_GEN_RPT_m0_s_fifo_full_END      (15)
#define BBPCOMM_M_GEN_RPT_m1_sync_status_START    (16)
#define BBPCOMM_M_GEN_RPT_m1_sync_status_END      (23)
#define BBPCOMM_M_GEN_RPT_m1_fifo_empty_START     (24)
#define BBPCOMM_M_GEN_RPT_m1_fifo_empty_END       (24)
#define BBPCOMM_M_GEN_RPT_m1_fifo_full_START      (25)
#define BBPCOMM_M_GEN_RPT_m1_fifo_full_END        (25)


/*****************************************************************************
 结构名    : BBPCOMM_LUT_FSM_RPT_UNION
 结构说明  : LUT_FSM_RPT 寄存器结构定义。地址偏移量:0x20，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      lut_fsm_rpt_reg;
    struct
    {
        unsigned int  curr_state : 2;  /* bit[0-1] : 查表状态机上报 */
        unsigned int  reserved   : 30; /* bit[2-31]:  */
    } reg;
} BBPCOMM_LUT_FSM_RPT_UNION;
#define BBPCOMM_LUT_FSM_RPT_curr_state_START  (0)
#define BBPCOMM_LUT_FSM_RPT_curr_state_END    (1)


/*****************************************************************************
 结构名    : BBPCOMM_DFT_MEM_CTRL1_UNION
 结构说明  : DFT_MEM_CTRL1 寄存器结构定义。地址偏移量:0x24，初值:0x03501050，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      dft_mem_ctrl1_reg;
    struct
    {
        unsigned int  mem_ctrl_s_w1      : 16; /* bit[0-15] : DFT MEM cpu接口配置 */
        unsigned int  mem_ctrl_d_1w2r_w1 : 16; /* bit[16-31]: DFT MEM cpu接口配置 */
    } reg;
} BBPCOMM_DFT_MEM_CTRL1_UNION;
#define BBPCOMM_DFT_MEM_CTRL1_mem_ctrl_s_w1_START       (0)
#define BBPCOMM_DFT_MEM_CTRL1_mem_ctrl_s_w1_END         (15)
#define BBPCOMM_DFT_MEM_CTRL1_mem_ctrl_d_1w2r_w1_START  (16)
#define BBPCOMM_DFT_MEM_CTRL1_mem_ctrl_d_1w2r_w1_END    (31)


/*****************************************************************************
 结构名    : BBPCOMM_DFT_MEM_CTRL2_UNION
 结构说明  : DFT_MEM_CTRL2 寄存器结构定义。地址偏移量:0x28，初值:0x00700057，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      dft_mem_ctrl2_reg;
    struct
    {
        unsigned int  mem_ctrl_d_1rw2rw_w1 : 16; /* bit[0-15] : DFT MEM cpu接口配置 */
        unsigned int  rom_ctrl_pre         : 8;  /* bit[16-23]: DFT MEM cpu接口配置 */
        unsigned int  reserved             : 8;  /* bit[24-31]:  */
    } reg;
} BBPCOMM_DFT_MEM_CTRL2_UNION;
#define BBPCOMM_DFT_MEM_CTRL2_mem_ctrl_d_1rw2rw_w1_START  (0)
#define BBPCOMM_DFT_MEM_CTRL2_mem_ctrl_d_1rw2rw_w1_END    (15)
#define BBPCOMM_DFT_MEM_CTRL2_rom_ctrl_pre_START          (16)
#define BBPCOMM_DFT_MEM_CTRL2_rom_ctrl_pre_END            (23)


/*****************************************************************************
 结构名    : BBPCOMM_GPIO_M0_LINE_CROSS_EN_UNION
 结构说明  : GPIO_M0_LINE_CROSS_EN 寄存器结构定义。地址偏移量:0x2C，初值:0x00000001，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      gpio_m0_line_cross_en_reg;
    struct
    {
        unsigned int  cpu_m0_line_cross_cfg_imi : 1;  /* bit[0]   : cpu配置GPIO cross开关，1：CPU配置，当前CPU配置下用于默认场景下的GPIO直通情况。
                                                                    0：TAS_IND 自动控制GPIO CROSS */
        unsigned int  reserved_0                : 3;  /* bit[1-3] :  */
        unsigned int  gpio_m0_line_cross_en_imi : 1;  /* bit[4]   : 在cpu配置GPIO cross开关为1的情况下，该位域配置为0，则GPIO不做CROSS直通输出，当前只支持该信号配置为0 */
        unsigned int  reserved_1                : 27; /* bit[5-31]:  */
    } reg;
} BBPCOMM_GPIO_M0_LINE_CROSS_EN_UNION;
#define BBPCOMM_GPIO_M0_LINE_CROSS_EN_cpu_m0_line_cross_cfg_imi_START  (0)
#define BBPCOMM_GPIO_M0_LINE_CROSS_EN_cpu_m0_line_cross_cfg_imi_END    (0)
#define BBPCOMM_GPIO_M0_LINE_CROSS_EN_gpio_m0_line_cross_en_imi_START  (4)
#define BBPCOMM_GPIO_M0_LINE_CROSS_EN_gpio_m0_line_cross_en_imi_END    (4)


/*****************************************************************************
 结构名    : BBPCOMM_FSM_OT_PRRT_EN_UNION
 结构说明  : FSM_OT_PRRT_EN 寄存器结构定义。地址偏移量:0x30，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
typedef union
{
    unsigned int      fsm_ot_prrt_en_reg;
    struct
    {
        unsigned int  fsm_ot_prt_en_imi : 1;  /* bit[0]   : 状态机超时计时器 */
        unsigned int  reserved          : 31; /* bit[1-31]:  */
    } reg;
} BBPCOMM_FSM_OT_PRRT_EN_UNION;
#define BBPCOMM_FSM_OT_PRRT_EN_fsm_ot_prt_en_imi_START  (0)
#define BBPCOMM_FSM_OT_PRRT_EN_fsm_ot_prt_en_imi_END    (0)


/***======================================================================***
                     (3/3) register_define_mipi_tuner_mem
 ***======================================================================***/


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

#endif /* end of bbp_comm_fe_interface.h */
