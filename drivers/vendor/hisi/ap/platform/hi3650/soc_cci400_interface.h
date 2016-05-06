/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_cci400_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:18:52
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_CCI400.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_CCI400_INTERFACE_H__
#define __SOC_CCI400_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) CCI400
 ****************************************************************************/
/* 寄存器说明：CCI控制寄存器。
   位域定义UNION结构:  SOC_CCI400_CCI_CR_UNION */
#define SOC_CCI400_CCI_CR_ADDR(base)                  ((base) + (0x90000))

/* 寄存器说明：Speculation控制寄存器
   位域定义UNION结构:  SOC_CCI400_CCI_SPECCTRL_UNION */
#define SOC_CCI400_CCI_SPECCTRL_ADDR(base)            ((base) + (0x90004))

/* 寄存器说明：安全访问寄存器
   位域定义UNION结构:  SOC_CCI400_CCI_SAR_UNION */
#define SOC_CCI400_CCI_SAR_ADDR(base)                 ((base) + (0x90008))

/* 寄存器说明：状态寄存器
   位域定义UNION结构:  SOC_CCI400_CCI_SR_UNION */
#define SOC_CCI400_CCI_SR_ADDR(base)                  ((base) + (0x9000C))

/* 寄存器说明：不确定错误寄存器
   位域定义UNION结构:  SOC_CCI400_CCI_IMPR_UNION */
#define SOC_CCI400_CCI_IMPR_ADDR(base)                ((base) + (0x90010))

/* 寄存器说明：性能监控寄存器
   位域定义UNION结构:  SOC_CCI400_CCI_PMCR_UNION */
#define SOC_CCI400_CCI_PMCR_ADDR(base)                ((base) + (0x90100))

/* 寄存器说明：组件和外设ID寄存器
   位域定义UNION结构:  SOC_CCI400_CCI_PERI4_UNION */
#define SOC_CCI400_CCI_PERI4_ADDR(base)               ((base) + (0x90FD0))

/* 寄存器说明：组件和外设ID寄存器
   位域定义UNION结构:  SOC_CCI400_CCI_PERI5_UNION */
#define SOC_CCI400_CCI_PERI5_ADDR(base)               ((base) + (0x90FD4))

/* 寄存器说明：组件和外设ID寄存器
   位域定义UNION结构:  SOC_CCI400_CCI_PERI6_UNION */
#define SOC_CCI400_CCI_PERI6_ADDR(base)               ((base) + (0x90FD8))

/* 寄存器说明：组件和外设ID寄存器
   位域定义UNION结构:  SOC_CCI400_CCI_PERI7_UNION */
#define SOC_CCI400_CCI_PERI7_ADDR(base)               ((base) + (0x90FDC))

/* 寄存器说明：组件和外设ID寄存器
   位域定义UNION结构:  SOC_CCI400_CCI_PERI0_UNION */
#define SOC_CCI400_CCI_PERI0_ADDR(base)               ((base) + (0x90FE0))

/* 寄存器说明：组件和外设ID寄存器
   位域定义UNION结构:  SOC_CCI400_CCI_PERI1_UNION */
#define SOC_CCI400_CCI_PERI1_ADDR(base)               ((base) + (0x90FE4))

/* 寄存器说明：组件和外设ID寄存器
   位域定义UNION结构:  SOC_CCI400_CCI_PERI2_UNION */
#define SOC_CCI400_CCI_PERI2_ADDR(base)               ((base) + (0x90FE8))

/* 寄存器说明：组件和外设ID寄存器
   位域定义UNION结构:  SOC_CCI400_CCI_PERI3_UNION */
#define SOC_CCI400_CCI_PERI3_ADDR(base)               ((base) + (0x90FEC))

/* 寄存器说明：组件和外设ID寄存器
   位域定义UNION结构:  SOC_CCI400_CCI_COMP0_UNION */
#define SOC_CCI400_CCI_COMP0_ADDR(base)               ((base) + (0x90FF0))

/* 寄存器说明：组件和外设ID寄存器
   位域定义UNION结构:  SOC_CCI400_CCI_COMP1_UNION */
#define SOC_CCI400_CCI_COMP1_ADDR(base)               ((base) + (0x90FF4))

/* 寄存器说明：组件和外设ID寄存器
   位域定义UNION结构:  SOC_CCI400_CCI_COMP2_UNION */
#define SOC_CCI400_CCI_COMP2_ADDR(base)               ((base) + (0x90FF8))

/* 寄存器说明：组件和外设ID寄存器
   位域定义UNION结构:  SOC_CCI400_CCI_COMP3_UNION */
#define SOC_CCI400_CCI_COMP3_ADDR(base)               ((base) + (0x90FFC))

/* 寄存器说明：snoop控制寄存器
   位域定义UNION结构:  SOC_CCI400_CCI_SCR_S0_UNION */
#define SOC_CCI400_CCI_SCR_S0_ADDR(base)              ((base) + (0x91000))

/* 寄存器说明：过载通过s0的操作的shareability属性
   位域定义UNION结构:  SOC_CCI400_CCI_SOR_S0_UNION */
#define SOC_CCI400_CCI_SOR_S0_ADDR(base)              ((base) + (0x91004))

/* 寄存器说明：过载通过s0读通道的操作的QoS值
   位域定义UNION结构:  SOC_CCI400_CCI_RCQVOR_S0_UNION */
#define SOC_CCI400_CCI_RCQVOR_S0_ADDR(base)           ((base) + (0x91100))

/* 寄存器说明：过载通过s0写通道的操作的QoS值
   位域定义UNION结构:  SOC_CCI400_CCI_WCQVOR_S0_UNION */
#define SOC_CCI400_CCI_WCQVOR_S0_ADDR(base)           ((base) + (0x91104))

/* 寄存器说明：QOS控制寄存器
   位域定义UNION结构:  SOC_CCI400_CCI_QCR_S0_UNION */
#define SOC_CCI400_CCI_QCR_S0_ADDR(base)              ((base) + (0x9110C))

/* 寄存器说明：最大OT寄存器
   位域定义UNION结构:  SOC_CCI400_CCI_MOTR_S0_UNION */
#define SOC_CCI400_CCI_MOTR_S0_ADDR(base)             ((base) + (0x91110))

/* 寄存器说明：目标带宽调节器
   位域定义UNION结构:  SOC_CCI400_CCI_RTR_S0_UNION */
#define SOC_CCI400_CCI_RTR_S0_ADDR(base)              ((base) + (0x91130))

/* 寄存器说明：QoS Regulator比例因子寄存器
   位域定义UNION结构:  SOC_CCI400_CCI_QRSFR_S0_UNION */
#define SOC_CCI400_CCI_QRSFR_S0_ADDR(base)            ((base) + (0x91134))

/* 寄存器说明：QoS 范围寄存器
   位域定义UNION结构:  SOC_CCI400_CCI_QRR_S0_UNION */
#define SOC_CCI400_CCI_QRR_S0_ADDR(base)              ((base) + (0x91138))

/* 寄存器说明：snoop控制寄存器
   位域定义UNION结构:  SOC_CCI400_CCI_SCR_S1_UNION */
#define SOC_CCI400_CCI_SCR_S1_ADDR(base)              ((base) + (0x92000))

/* 寄存器说明：过载通过s0的操作的shareability属性
   位域定义UNION结构:  SOC_CCI400_CCI_SOR_S1_UNION */
#define SOC_CCI400_CCI_SOR_S1_ADDR(base)              ((base) + (0x92004))

/* 寄存器说明：过载通过s0读通道的操作的QoS值
   位域定义UNION结构:  SOC_CCI400_CCI_RCQVOR_S1_UNION */
#define SOC_CCI400_CCI_RCQVOR_S1_ADDR(base)           ((base) + (0x92100))

/* 寄存器说明：过载通过s0写通道的操作的QoS值
   位域定义UNION结构:  SOC_CCI400_CCI_WCQVOR_S1_UNION */
#define SOC_CCI400_CCI_WCQVOR_S1_ADDR(base)           ((base) + (0x92104))

/* 寄存器说明：QOS控制寄存器
   位域定义UNION结构:  SOC_CCI400_CCI_QCR_S1_UNION */
#define SOC_CCI400_CCI_QCR_S1_ADDR(base)              ((base) + (0x9210C))

/* 寄存器说明：最大OT寄存器
   位域定义UNION结构:  SOC_CCI400_CCI_MOTR_S1_UNION */
#define SOC_CCI400_CCI_MOTR_S1_ADDR(base)             ((base) + (0x92110))

/* 寄存器说明：目标带宽调节器
   位域定义UNION结构:  SOC_CCI400_CCI_RTR_S1_UNION */
#define SOC_CCI400_CCI_RTR_S1_ADDR(base)              ((base) + (0x92130))

/* 寄存器说明：QoS Regulator比例因子寄存器
   位域定义UNION结构:  SOC_CCI400_CCI_QRSFR_S1_UNION */
#define SOC_CCI400_CCI_QRSFR_S1_ADDR(base)            ((base) + (0x92134))

/* 寄存器说明：QoS 范围寄存器
   位域定义UNION结构:  SOC_CCI400_CCI_QRR_S1_UNION */
#define SOC_CCI400_CCI_QRR_S1_ADDR(base)              ((base) + (0x92138))

/* 寄存器说明：snoop控制寄存器
   位域定义UNION结构:  SOC_CCI400_CCI_SCR_S2_UNION */
#define SOC_CCI400_CCI_SCR_S2_ADDR(base)              ((base) + (0x93000))

/* 寄存器说明：过载通过s0的操作的shareability属性
   位域定义UNION结构:  SOC_CCI400_CCI_SOR_S2_UNION */
#define SOC_CCI400_CCI_SOR_S2_ADDR(base)              ((base) + (0x93004))

/* 寄存器说明：过载通过s0读通道的操作的QoS值
   位域定义UNION结构:  SOC_CCI400_CCI_RCQVOR_S2_UNION */
#define SOC_CCI400_CCI_RCQVOR_S2_ADDR(base)           ((base) + (0x93100))

/* 寄存器说明：过载通过s0写通道的操作的QoS值
   位域定义UNION结构:  SOC_CCI400_CCI_WCQVOR_S2_UNION */
#define SOC_CCI400_CCI_WCQVOR_S2_ADDR(base)           ((base) + (0x93104))

/* 寄存器说明：QOS控制寄存器
   位域定义UNION结构:  SOC_CCI400_CCI_QCR_S2_UNION */
#define SOC_CCI400_CCI_QCR_S2_ADDR(base)              ((base) + (0x9310C))

/* 寄存器说明：最大OT寄存器
   位域定义UNION结构:  SOC_CCI400_CCI_MOTR_S2_UNION */
#define SOC_CCI400_CCI_MOTR_S2_ADDR(base)             ((base) + (0x93110))

/* 寄存器说明：目标带宽调节器
   位域定义UNION结构:  SOC_CCI400_CCI_RTR_S2_UNION */
#define SOC_CCI400_CCI_RTR_S2_ADDR(base)              ((base) + (0x93130))

/* 寄存器说明：QoS Regulator比例因子寄存器
   位域定义UNION结构:  SOC_CCI400_CCI_QRSFR_S2_UNION */
#define SOC_CCI400_CCI_QRSFR_S2_ADDR(base)            ((base) + (0x93134))

/* 寄存器说明：QoS 范围寄存器
   位域定义UNION结构:  SOC_CCI400_CCI_QRR_S2_UNION */
#define SOC_CCI400_CCI_QRR_S2_ADDR(base)              ((base) + (0x93138))

/* 寄存器说明：snoop控制寄存器
   位域定义UNION结构:  SOC_CCI400_CCI_SCR_S3_UNION */
#define SOC_CCI400_CCI_SCR_S3_ADDR(base)              ((base) + (0x94000))

/* 寄存器说明：过载通过s0读通道的操作的QoS值
   位域定义UNION结构:  SOC_CCI400_CCI_RCQVOR_S3_UNION */
#define SOC_CCI400_CCI_RCQVOR_S3_ADDR(base)           ((base) + (0x94100))

/* 寄存器说明：过载通过s0写通道的操作的QoS值
   位域定义UNION结构:  SOC_CCI400_CCI_WCQVOR_S3_UNION */
#define SOC_CCI400_CCI_WCQVOR_S3_ADDR(base)           ((base) + (0x94104))

/* 寄存器说明：QOS控制寄存器
   位域定义UNION结构:  SOC_CCI400_CCI_QCR_S3_UNION */
#define SOC_CCI400_CCI_QCR_S3_ADDR(base)              ((base) + (0x9410C))

/* 寄存器说明：目标带宽调节器
   位域定义UNION结构:  SOC_CCI400_CCI_RTR_S3_UNION */
#define SOC_CCI400_CCI_RTR_S3_ADDR(base)              ((base) + (0x94130))

/* 寄存器说明：QoS Regulator比例因子寄存器
   位域定义UNION结构:  SOC_CCI400_CCI_QRSFR_S3_UNION */
#define SOC_CCI400_CCI_QRSFR_S3_ADDR(base)            ((base) + (0x94134))

/* 寄存器说明：QoS 范围寄存器
   位域定义UNION结构:  SOC_CCI400_CCI_QRR_S3_UNION */
#define SOC_CCI400_CCI_QRR_S3_ADDR(base)              ((base) + (0x94138))

/* 寄存器说明：snoop控制寄存器
   位域定义UNION结构:  SOC_CCI400_CCI_SCR_S4_UNION */
#define SOC_CCI400_CCI_SCR_S4_ADDR(base)              ((base) + (0x95000))

/* 寄存器说明：过载通过s0读通道的操作的QoS值
   位域定义UNION结构:  SOC_CCI400_CCI_RCQVOR_S4_UNION */
#define SOC_CCI400_CCI_RCQVOR_S4_ADDR(base)           ((base) + (0x95100))

/* 寄存器说明：过载通过s0写通道的操作的QoS值
   位域定义UNION结构:  SOC_CCI400_CCI_WCQVOR_S4_UNION */
#define SOC_CCI400_CCI_WCQVOR_S4_ADDR(base)           ((base) + (0x95104))

/* 寄存器说明：QOS控制寄存器
   位域定义UNION结构:  SOC_CCI400_CCI_QCR_S4_UNION */
#define SOC_CCI400_CCI_QCR_S4_ADDR(base)              ((base) + (0x9510C))

/* 寄存器说明：目标带宽调节器
   位域定义UNION结构:  SOC_CCI400_CCI_RTR_S4_UNION */
#define SOC_CCI400_CCI_RTR_S4_ADDR(base)              ((base) + (0x95130))

/* 寄存器说明：QoS Regulator比例因子寄存器
   位域定义UNION结构:  SOC_CCI400_CCI_QRSFR_S4_UNION */
#define SOC_CCI400_CCI_QRSFR_S4_ADDR(base)            ((base) + (0x91134))

/* 寄存器说明：QoS 范围寄存器
   位域定义UNION结构:  SOC_CCI400_CCI_QRR_S4_UNION */
#define SOC_CCI400_CCI_QRR_S4_ADDR(base)              ((base) + (0x95138))

/* 寄存器说明：事件cycle计数寄存器
   位域定义UNION结构:  SOC_CCI400_CCI_ECCR_UNION */
#define SOC_CCI400_CCI_ECCR_ADDR(base)                ((base) + (0x99004))

/* 寄存器说明：计数控制寄存器
   位域定义UNION结构:  SOC_CCI400_CCI_CCR_UNION */
#define SOC_CCI400_CCI_CCR_ADDR(base)                 ((base) + (0x99008))

/* 寄存器说明：计数溢出寄存器
   位域定义UNION结构:  SOC_CCI400_CCI_OFSR_UNION */
#define SOC_CCI400_CCI_OFSR_ADDR(base)                ((base) + (0x9900C))

/* 寄存器说明：事件选择寄存器
   位域定义UNION结构:  SOC_CCI400_CCI_ESR_0_UNION */
#define SOC_CCI400_CCI_ESR_0_ADDR(base)               ((base) + (0x9A000))

/* 寄存器说明：事件cycle计数寄存器
   位域定义UNION结构:  SOC_CCI400_CCI_ECCR_0_UNION */
#define SOC_CCI400_CCI_ECCR_0_ADDR(base)              ((base) + (0x9A004))

/* 寄存器说明：计数控制寄存器
   位域定义UNION结构:  SOC_CCI400_CCI_CCR_0_UNION */
#define SOC_CCI400_CCI_CCR_0_ADDR(base)               ((base) + (0x9A008))

/* 寄存器说明：计数溢出寄存器
   位域定义UNION结构:  SOC_CCI400_CCI_OFSR_0_UNION */
#define SOC_CCI400_CCI_OFSR_0_ADDR(base)              ((base) + (0x9A00C))

/* 寄存器说明：事件选择寄存器
   位域定义UNION结构:  SOC_CCI400_CCI_ESR_1_UNION */
#define SOC_CCI400_CCI_ESR_1_ADDR(base)               ((base) + (0x9B000))

/* 寄存器说明：事件cycle计数寄存器
   位域定义UNION结构:  SOC_CCI400_CCI_ECCR_1_UNION */
#define SOC_CCI400_CCI_ECCR_1_ADDR(base)              ((base) + (0x9B004))

/* 寄存器说明：计数控制寄存器
   位域定义UNION结构:  SOC_CCI400_CCI_CCR_1_UNION */
#define SOC_CCI400_CCI_CCR_1_ADDR(base)               ((base) + (0x9B008))

/* 寄存器说明：计数溢出寄存器
   位域定义UNION结构:  SOC_CCI400_CCI_OFSR_1_UNION */
#define SOC_CCI400_CCI_OFSR_1_ADDR(base)              ((base) + (0x9B00C))

/* 寄存器说明：事件选择寄存器
   位域定义UNION结构:  SOC_CCI400_CCI_ESR_2_UNION */
#define SOC_CCI400_CCI_ESR_2_ADDR(base)               ((base) + (0x9C000))

/* 寄存器说明：事件cycle计数寄存器
   位域定义UNION结构:  SOC_CCI400_CCI_ECCR_2_UNION */
#define SOC_CCI400_CCI_ECCR_2_ADDR(base)              ((base) + (0x9C004))

/* 寄存器说明：计数控制寄存器
   位域定义UNION结构:  SOC_CCI400_CCI_CCR_2_UNION */
#define SOC_CCI400_CCI_CCR_2_ADDR(base)               ((base) + (0x9C008))

/* 寄存器说明：计数溢出寄存器
   位域定义UNION结构:  SOC_CCI400_CCI_OFSR_2_UNION */
#define SOC_CCI400_CCI_OFSR_2_ADDR(base)              ((base) + (0x9C00C))

/* 寄存器说明：事件选择寄存器
   位域定义UNION结构:  SOC_CCI400_CCI_ESR_3_UNION */
#define SOC_CCI400_CCI_ESR_3_ADDR(base)               ((base) + (0x9D000))

/* 寄存器说明：事件cycle计数寄存器
   位域定义UNION结构:  SOC_CCI400_CCI_ECCR_3_UNION */
#define SOC_CCI400_CCI_ECCR_3_ADDR(base)              ((base) + (0x9D004))

/* 寄存器说明：计数控制寄存器
   位域定义UNION结构:  SOC_CCI400_CCI_CCR_3_UNION */
#define SOC_CCI400_CCI_CCR_3_ADDR(base)               ((base) + (0x9D008))

/* 寄存器说明：计数溢出寄存器
   位域定义UNION结构:  SOC_CCI400_CCI_OFSR_3_UNION */
#define SOC_CCI400_CCI_OFSR_3_ADDR(base)              ((base) + (0x9D00C))





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
                     (1/1) CCI400
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_CCI400_CCI_CR_UNION
 结构说明  : CCI_CR 寄存器结构定义。地址偏移量:0x90000，初值:0x00000000，宽度:32
 寄存器说明: CCI控制寄存器。
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  Snoop_disable       : 1;  /* bit[0]   : Snoop disable. The options are as follows:
                                                              0b0 Snoop masters according to the Snoop Control Registers.
                                                              0b1 Disable all snoops, but not DVM messages. */
        unsigned int  DVM_message_disable : 1;  /* bit[1]   : DVM message disable. The options are as follows:
                                                              0b0 Send DVM messages according to the Snoop Control Registers.
                                                              0b1 Disable propagation of all DVM messages. */
        unsigned int  spec_fetch_disable  : 1;  /* bit[2]   : Disable speculative fetches. The options are as follows:
                                                              0b0 Send speculative fetches according to the Speculation Control
                                                              Register. 
                                                              0b1 Disable speculative fetches from all master interfaces. */
        unsigned int  barrier_terminate   : 1;  /* bit[3]   : Terminate all barrier transactions. The options are as follows:
                                                              0b0 Master interfaces terminate barriers according to the
                                                              BARRIERTERMINATE inputs.
                                                              0b1 All master interfaces terminate barriers. */
        unsigned int  prop_prom_disable   : 1;  /* bit[4]   : Disable priority promotion. The options are as follows:
                                                              0b0 Use ARQOSARBS inputs to promote the priority of earlier
                                                              requests.
                                                              0b1 Ignore ARQOSARBS inputs. */
        unsigned int  reserved            : 27; /* bit[5-31]: Reserved */
    } reg;
} SOC_CCI400_CCI_CR_UNION;
#endif
#define SOC_CCI400_CCI_CR_Snoop_disable_START        (0)
#define SOC_CCI400_CCI_CR_Snoop_disable_END          (0)
#define SOC_CCI400_CCI_CR_DVM_message_disable_START  (1)
#define SOC_CCI400_CCI_CR_DVM_message_disable_END    (1)
#define SOC_CCI400_CCI_CR_spec_fetch_disable_START   (2)
#define SOC_CCI400_CCI_CR_spec_fetch_disable_END     (2)
#define SOC_CCI400_CCI_CR_barrier_terminate_START    (3)
#define SOC_CCI400_CCI_CR_barrier_terminate_END      (3)
#define SOC_CCI400_CCI_CR_prop_prom_disable_START    (4)
#define SOC_CCI400_CCI_CR_prop_prom_disable_END      (4)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_SPECCTRL_UNION
 结构说明  : CCI_SPECCTRL 寄存器结构定义。地址偏移量:0x90004，初值:0x00000000，宽度:32
 寄存器说明: Speculation控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  spec_fetch_disable_mst : 3;  /* bit[0-2]  : Disable speculative fetches from a master interface.
                                                                  One bit for each master interface: M2, M1, and M0.
                                                                  0b0 Enable speculative fetches.
                                                                  0b1 Disable speculative fetches. */
        unsigned int  reserved_0             : 13; /* bit[3-15] : Reserved */
        unsigned int  spec_fetch_disable_slv : 5;  /* bit[16-20]: Disable speculative fetches for transactions through a slave interface.
                                                                  One bit for each slave interface: S4, S3, S2, S1, and S0.
                                                                  0b0 Enable speculative fetches.
                                                                  0b1 Disable speculative fetches */
        unsigned int  reserved_1             : 11; /* bit[21-31]: Reserved */
    } reg;
} SOC_CCI400_CCI_SPECCTRL_UNION;
#endif
#define SOC_CCI400_CCI_SPECCTRL_spec_fetch_disable_mst_START  (0)
#define SOC_CCI400_CCI_SPECCTRL_spec_fetch_disable_mst_END    (2)
#define SOC_CCI400_CCI_SPECCTRL_spec_fetch_disable_slv_START  (16)
#define SOC_CCI400_CCI_SPECCTRL_spec_fetch_disable_slv_END    (20)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_SAR_UNION
 结构说明  : CCI_SAR 寄存器结构定义。地址偏移量:0x90008，初值:0x00000000，宽度:32
 寄存器说明: 安全访问寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  trans_pending : 1;  /* bit[0]   : Non-secure register access override.
                                                        0b0 Disable non-secure access to CCI-400 registers.
                                                        0b1 Enable non-secure access to CCI-400 registers. */
        unsigned int  reserved      : 31; /* bit[1-31]: Reserved */
    } reg;
} SOC_CCI400_CCI_SAR_UNION;
#endif
#define SOC_CCI400_CCI_SAR_trans_pending_START  (0)
#define SOC_CCI400_CCI_SAR_trans_pending_END    (0)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_SR_UNION
 结构说明  : CCI_SR 寄存器结构定义。地址偏移量:0x9000C，初值:0x00000000，宽度:32
 寄存器说明: 状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dvm_pending : 1;  /* bit[0]   : Indicates whether any changes to the snoop or DVM enables is pending in the
                                                      CCI-400:
                                                      0b0 No change pending.
                                                      0b1 Change pending. */
        unsigned int  reserved    : 31; /* bit[1-31]: Reserved */
    } reg;
} SOC_CCI400_CCI_SR_UNION;
#endif
#define SOC_CCI400_CCI_SR_dvm_pending_START  (0)
#define SOC_CCI400_CCI_SR_dvm_pending_END    (0)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_IMPR_UNION
 结构说明  : CCI_IMPR 寄存器结构定义。地址偏移量:0x90010，初值:0x00000000，宽度:32
 寄存器说明: 不确定错误寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  err_ind0_m0 : 1;  /* bit[0]    : Imprecise error indicator for master interface 0:
                                                       0b0 No error since this bit was last reset.
                                                       0b1 An error response has been received, but not signalled precisely */
        unsigned int  err_ind0_m1 : 1;  /* bit[1]    : Imprecise error indicator for master interface 1. */
        unsigned int  err_ind0_m2 : 1;  /* bit[2]    : Imprecise error indicator for master interface 2. */
        unsigned int  reserved_0  : 13; /* bit[3-15] : Reserved */
        unsigned int  err_ind0_s  : 1;  /* bit[16]   : Imprecise error indicator for slave interface 0. */
        unsigned int  err_ind1_s  : 1;  /* bit[17]   : Imprecise error indicator for slave interface 1. */
        unsigned int  err_ind2_s  : 1;  /* bit[18]   : Imprecise error indicator for slave interface 2. */
        unsigned int  err_ind3_s  : 1;  /* bit[19]   : Imprecise error indicator for slave interface 3. */
        unsigned int  err_ind4_s  : 1;  /* bit[20]   : Imprecise error indicator for slave interface 4. */
        unsigned int  reserved_1  : 11; /* bit[21-31]: Reserved */
    } reg;
} SOC_CCI400_CCI_IMPR_UNION;
#endif
#define SOC_CCI400_CCI_IMPR_err_ind0_m0_START  (0)
#define SOC_CCI400_CCI_IMPR_err_ind0_m0_END    (0)
#define SOC_CCI400_CCI_IMPR_err_ind0_m1_START  (1)
#define SOC_CCI400_CCI_IMPR_err_ind0_m1_END    (1)
#define SOC_CCI400_CCI_IMPR_err_ind0_m2_START  (2)
#define SOC_CCI400_CCI_IMPR_err_ind0_m2_END    (2)
#define SOC_CCI400_CCI_IMPR_err_ind0_s_START   (16)
#define SOC_CCI400_CCI_IMPR_err_ind0_s_END     (16)
#define SOC_CCI400_CCI_IMPR_err_ind1_s_START   (17)
#define SOC_CCI400_CCI_IMPR_err_ind1_s_END     (17)
#define SOC_CCI400_CCI_IMPR_err_ind2_s_START   (18)
#define SOC_CCI400_CCI_IMPR_err_ind2_s_END     (18)
#define SOC_CCI400_CCI_IMPR_err_ind3_s_START   (19)
#define SOC_CCI400_CCI_IMPR_err_ind3_s_END     (19)
#define SOC_CCI400_CCI_IMPR_err_ind4_s_START   (20)
#define SOC_CCI400_CCI_IMPR_err_ind4_s_END     (20)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_PMCR_UNION
 结构说明  : CCI_PMCR 寄存器结构定义。地址偏移量:0x90100，初值:0x00002000，宽度:32
 寄存器说明: 性能监控寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  CEN      : 1;  /* bit[0]    : Enable bit. The options are as follows:
                                                    0b0 Disable all counters, including CCNT.
                                                    0b1 Enable all counters, including CCNT. */
        unsigned int  RST      : 1;  /* bit[1]    : Performance counter reset. The options are as follows:
                                                    0b0 No action.
                                                    0b1 Reset all performance counters to zero, not including CCNT. */
        unsigned int  CCR      : 1;  /* bit[2]    : Cycle counter reset. The options are as follows:
                                                    0b0 No action.
                                                    0b1 Reset cycle counter, CCNT, to zero */
        unsigned int  CCD      : 1;  /* bit[3]    : Cycle count divider. The options are as follows:
                                                    0b0 Count every clock cycle when enabled.
                                                    0b1 Count every 64th clock cycle when enabled. */
        unsigned int  EX       : 1;  /* bit[4]    : Enable export of the events to the event bus, EVNTBUS, for an external monitoring
                                                    block to trace events. The options are as follows:
                                                    0b0 Do not export EVNTBUS.
                                                    0b1 Export EVNTBUS. */
        unsigned int  DP       : 1;  /* bit[5]    : Disables cycle counter, CCNT, if non-invasive debug is prohibited. The options are
                                                    as follows:
                                                    0b0 Count is not disabled when NIDEN input is LOW.
                                                    0b1 Count is disabled when NIDEN input is LOW. */
        unsigned int  reserved_0: 5;  /* bit[6-10] : Reserved. */
        unsigned int  cnt_num  : 5;  /* bit[11-15]: Specifies the number of counters implemented */
        unsigned int  reserved_1: 16; /* bit[16-31]: Reserved */
    } reg;
} SOC_CCI400_CCI_PMCR_UNION;
#endif
#define SOC_CCI400_CCI_PMCR_CEN_START       (0)
#define SOC_CCI400_CCI_PMCR_CEN_END         (0)
#define SOC_CCI400_CCI_PMCR_RST_START       (1)
#define SOC_CCI400_CCI_PMCR_RST_END         (1)
#define SOC_CCI400_CCI_PMCR_CCR_START       (2)
#define SOC_CCI400_CCI_PMCR_CCR_END         (2)
#define SOC_CCI400_CCI_PMCR_CCD_START       (3)
#define SOC_CCI400_CCI_PMCR_CCD_END         (3)
#define SOC_CCI400_CCI_PMCR_EX_START        (4)
#define SOC_CCI400_CCI_PMCR_EX_END          (4)
#define SOC_CCI400_CCI_PMCR_DP_START        (5)
#define SOC_CCI400_CCI_PMCR_DP_END          (5)
#define SOC_CCI400_CCI_PMCR_cnt_num_START   (11)
#define SOC_CCI400_CCI_PMCR_cnt_num_END     (15)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_PERI4_UNION
 结构说明  : CCI_PERI4 寄存器结构定义。地址偏移量:0x90FD0，初值:0x00000044，宽度:32
 寄存器说明: 组件和外设ID寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  jep106_continue : 4;  /* bit[0-3] : JEP106 continuation code for ARM. */
        unsigned int  reg_cnt         : 4;  /* bit[4-7] : 4KB region count. */
        unsigned int  reserved        : 24; /* bit[8-31]:  */
    } reg;
} SOC_CCI400_CCI_PERI4_UNION;
#endif
#define SOC_CCI400_CCI_PERI4_jep106_continue_START  (0)
#define SOC_CCI400_CCI_PERI4_jep106_continue_END    (3)
#define SOC_CCI400_CCI_PERI4_reg_cnt_START          (4)
#define SOC_CCI400_CCI_PERI4_reg_cnt_END            (7)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_PERI5_UNION
 结构说明  : CCI_PERI5 寄存器结构定义。地址偏移量:0x90FD4，初值:0x00000000，宽度:32
 寄存器说明: 组件和外设ID寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  peri_id5 : 8;  /* bit[0-7] : Reserved. */
        unsigned int  reserved : 24; /* bit[8-31]: Reserved */
    } reg;
} SOC_CCI400_CCI_PERI5_UNION;
#endif
#define SOC_CCI400_CCI_PERI5_peri_id5_START  (0)
#define SOC_CCI400_CCI_PERI5_peri_id5_END    (7)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_PERI6_UNION
 结构说明  : CCI_PERI6 寄存器结构定义。地址偏移量:0x90FD8，初值:0x00000000，宽度:32
 寄存器说明: 组件和外设ID寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  peri_id6 : 8;  /* bit[0-7] : Reserved. */
        unsigned int  reserved : 24; /* bit[8-31]: Reserved */
    } reg;
} SOC_CCI400_CCI_PERI6_UNION;
#endif
#define SOC_CCI400_CCI_PERI6_peri_id6_START  (0)
#define SOC_CCI400_CCI_PERI6_peri_id6_END    (7)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_PERI7_UNION
 结构说明  : CCI_PERI7 寄存器结构定义。地址偏移量:0x90FDC，初值:0x00000000，宽度:32
 寄存器说明: 组件和外设ID寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  peri_id7 : 8;  /* bit[0-7] : Reserved. */
        unsigned int  reserved : 24; /* bit[8-31]: Reserved */
    } reg;
} SOC_CCI400_CCI_PERI7_UNION;
#endif
#define SOC_CCI400_CCI_PERI7_peri_id7_START  (0)
#define SOC_CCI400_CCI_PERI7_peri_id7_END    (7)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_PERI0_UNION
 结构说明  : CCI_PERI0 寄存器结构定义。地址偏移量:0x90FE0，初值:0x00000020，宽度:32
 寄存器说明: 组件和外设ID寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  peri_id0 : 8;  /* bit[0-7] : Part number[7:0]. */
        unsigned int  reserved : 24; /* bit[8-31]: Reserved */
    } reg;
} SOC_CCI400_CCI_PERI0_UNION;
#endif
#define SOC_CCI400_CCI_PERI0_peri_id0_START  (0)
#define SOC_CCI400_CCI_PERI0_peri_id0_END    (7)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_PERI1_UNION
 结构说明  : CCI_PERI1 寄存器结构定义。地址偏移量:0x90FE4，初值:0x000000B4，宽度:32
 寄存器说明: 组件和外设ID寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  peri_id1_num : 4;  /* bit[0-3] : Part number[11:8]. */
        unsigned int  jep106_id_l  : 4;  /* bit[4-7] : JEP106 ID code[3:0] for ARM */
        unsigned int  reserved     : 24; /* bit[8-31]: Reserved */
    } reg;
} SOC_CCI400_CCI_PERI1_UNION;
#endif
#define SOC_CCI400_CCI_PERI1_peri_id1_num_START  (0)
#define SOC_CCI400_CCI_PERI1_peri_id1_num_END    (3)
#define SOC_CCI400_CCI_PERI1_jep106_id_l_START   (4)
#define SOC_CCI400_CCI_PERI1_jep106_id_l_END     (7)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_PERI2_UNION
 结构说明  : CCI_PERI2 寄存器结构定义。地址偏移量:0x90FE8，初值:0x0000006B，宽度:32
 寄存器说明: 组件和外设ID寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  jep106_id_h  : 3;  /* bit[0-2] : JEP106 ID code[6:4] for ARM. */
        unsigned int  manu_id_code : 1;  /* bit[3]   : IC uses a manufacturer’s identity code allocated by JEDEC according to the JEP106 */
        unsigned int  ccr_rev      : 4;  /* bit[4-7] : CCI-400 revision, r1p1. */
        unsigned int  reserved     : 24; /* bit[8-31]: Reserved */
    } reg;
} SOC_CCI400_CCI_PERI2_UNION;
#endif
#define SOC_CCI400_CCI_PERI2_jep106_id_h_START   (0)
#define SOC_CCI400_CCI_PERI2_jep106_id_h_END     (2)
#define SOC_CCI400_CCI_PERI2_manu_id_code_START  (3)
#define SOC_CCI400_CCI_PERI2_manu_id_code_END    (3)
#define SOC_CCI400_CCI_PERI2_ccr_rev_START       (4)
#define SOC_CCI400_CCI_PERI2_ccr_rev_END         (7)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_PERI3_UNION
 结构说明  : CCI_PERI3 寄存器结构定义。地址偏移量:0x90FEC，初值:0x00000000，宽度:32
 寄存器说明: 组件和外设ID寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mod_num  : 4;  /* bit[0-3] : Customer modification number */
        unsigned int  eco_num  : 4;  /* bit[4-7] : ARM approved ECO number. Use the ECOREVNUM inputs to modify this value. */
        unsigned int  reserved : 24; /* bit[8-31]: Reserved */
    } reg;
} SOC_CCI400_CCI_PERI3_UNION;
#endif
#define SOC_CCI400_CCI_PERI3_mod_num_START   (0)
#define SOC_CCI400_CCI_PERI3_mod_num_END     (3)
#define SOC_CCI400_CCI_PERI3_eco_num_START   (4)
#define SOC_CCI400_CCI_PERI3_eco_num_END     (7)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_COMP0_UNION
 结构说明  : CCI_COMP0 寄存器结构定义。地址偏移量:0x90FF0，初值:0x0000000D，宽度:32
 寄存器说明: 组件和外设ID寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  component_id0 : 8;  /* bit[0-7] : These values identify the CCI-400 as an ARM component */
        unsigned int  reserved      : 24; /* bit[8-31]: Reserved */
    } reg;
} SOC_CCI400_CCI_COMP0_UNION;
#endif
#define SOC_CCI400_CCI_COMP0_component_id0_START  (0)
#define SOC_CCI400_CCI_COMP0_component_id0_END    (7)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_COMP1_UNION
 结构说明  : CCI_COMP1 寄存器结构定义。地址偏移量:0x90FF4，初值:0x000000F0，宽度:32
 寄存器说明: 组件和外设ID寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  component_id1 : 8;  /* bit[0-7] : These values identify the CCI-400 as an ARM component */
        unsigned int  reserved      : 24; /* bit[8-31]: Reserved */
    } reg;
} SOC_CCI400_CCI_COMP1_UNION;
#endif
#define SOC_CCI400_CCI_COMP1_component_id1_START  (0)
#define SOC_CCI400_CCI_COMP1_component_id1_END    (7)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_COMP2_UNION
 结构说明  : CCI_COMP2 寄存器结构定义。地址偏移量:0x90FF8，初值:0x00000005，宽度:32
 寄存器说明: 组件和外设ID寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  component_id2 : 8;  /* bit[0-7] : These values identify the CCI-400 as an ARM component */
        unsigned int  reserved      : 24; /* bit[8-31]: Reserved */
    } reg;
} SOC_CCI400_CCI_COMP2_UNION;
#endif
#define SOC_CCI400_CCI_COMP2_component_id2_START  (0)
#define SOC_CCI400_CCI_COMP2_component_id2_END    (7)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_COMP3_UNION
 结构说明  : CCI_COMP3 寄存器结构定义。地址偏移量:0x90FFC，初值:0x000000B1，宽度:32
 寄存器说明: 组件和外设ID寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  component_id3 : 8;  /* bit[0-7] : These values identify the CCI-400 as an ARM component */
        unsigned int  reserved      : 24; /* bit[8-31]: Reserved */
    } reg;
} SOC_CCI400_CCI_COMP3_UNION;
#endif
#define SOC_CCI400_CCI_COMP3_component_id3_START  (0)
#define SOC_CCI400_CCI_COMP3_component_id3_END    (7)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_SCR_S0_UNION
 结构说明  : CCI_SCR_S0 寄存器结构定义。地址偏移量:0x91000，初值:0x80000000，宽度:32
 寄存器说明: snoop控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  snoop_en      : 1;  /* bit[0]   : Enable issuing of snoop requests from this slave interface.
                                                        RAZ/WI for interfaces not supporting snoops:
                                                        0b0 Disable snoop requests.
                                                        0b1 Enable snoop requests. */
        unsigned int  dvm_en        : 1;  /* bit[1]   : Enable issuing of DVM message requests from this slave interface.
                                                        RAZ/WI for interfaces not supporting DVM messages:
                                                        0b0 Disable DVM message requests.
                                                        0b1 Enable DVM message requests */
        unsigned int  reserved      : 28; /* bit[2-29]: RESERVED */
        unsigned int  snoop_support : 1;  /* bit[30]  : Slave interface supports snoops.
                                                        This is overridden to 0x0 if you set the Control Override Register [0]. */
        unsigned int  dvm_support   : 1;  /* bit[31]  : Slave interface supports DVM messages.
                                                        This is overridden to 0x0 if you set the Control Override Register [1]. */
    } reg;
} SOC_CCI400_CCI_SCR_S0_UNION;
#endif
#define SOC_CCI400_CCI_SCR_S0_snoop_en_START       (0)
#define SOC_CCI400_CCI_SCR_S0_snoop_en_END         (0)
#define SOC_CCI400_CCI_SCR_S0_dvm_en_START         (1)
#define SOC_CCI400_CCI_SCR_S0_dvm_en_END           (1)
#define SOC_CCI400_CCI_SCR_S0_snoop_support_START  (30)
#define SOC_CCI400_CCI_SCR_S0_snoop_support_END    (30)
#define SOC_CCI400_CCI_SCR_S0_dvm_support_START    (31)
#define SOC_CCI400_CCI_SCR_S0_dvm_support_END      (31)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_SOR_S0_UNION
 结构说明  : CCI_SOR_S0 寄存器结构定义。地址偏移量:0x91004，初值:0x00000000，宽度:32
 寄存器说明: 过载通过s0的操作的shareability属性
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  shareable_override : 2;  /* bit[0-1] : Shareable override for slave interface.
                                                             0x0, 0x1 Do not override AxDOMAIN inputs.
                                                             0x2 Override AxDOMAIN inputs to 0b00, all transactions are treated
                                                             as non-shareable:
                                                             ? ReadOnce becomes ReadNoSnoop.
                                                             ? WriteUnique and WriteLineUnique become WriteNoSnoop.
                                                             0x3 Override AxDOMAIN inputs to 0b01, normal transactions are
                                                             treated as shareable:
                                                             ? ReadNoSnoop becomes ReadOnce.
                                                             ? WriteNoSnoop becomes WriteUnique. */
        unsigned int  reserved           : 30; /* bit[2-31]: Reserved */
    } reg;
} SOC_CCI400_CCI_SOR_S0_UNION;
#endif
#define SOC_CCI400_CCI_SOR_S0_shareable_override_START  (0)
#define SOC_CCI400_CCI_SOR_S0_shareable_override_END    (1)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_RCQVOR_S0_UNION
 结构说明  : CCI_RCQVOR_S0 寄存器结构定义。地址偏移量:0x91100，初值:0x00000000，宽度:32
 寄存器说明: 过载通过s0读通道的操作的QoS值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  arqos_ov    : 4;  /* bit[0-3]  : ARQOS value override for slave interface */
        unsigned int  reserved_0  : 4;  /* bit[4-7]  : Reserved. */
        unsigned int  arqos_value : 4;  /* bit[8-11] : Reads what value is currently applied to transactions with ARQOS=0 if QOSOVERRIDE is HIGH and QoS value regulation is enabled. */
        unsigned int  reserved_1  : 20; /* bit[12-31]: Reserved. */
    } reg;
} SOC_CCI400_CCI_RCQVOR_S0_UNION;
#endif
#define SOC_CCI400_CCI_RCQVOR_S0_arqos_ov_START     (0)
#define SOC_CCI400_CCI_RCQVOR_S0_arqos_ov_END       (3)
#define SOC_CCI400_CCI_RCQVOR_S0_arqos_value_START  (8)
#define SOC_CCI400_CCI_RCQVOR_S0_arqos_value_END    (11)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_WCQVOR_S0_UNION
 结构说明  : CCI_WCQVOR_S0 寄存器结构定义。地址偏移量:0x91104，初值:0x00000000，宽度:32
 寄存器说明: 过载通过s0写通道的操作的QoS值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  awqos_ov    : 4;  /* bit[0-3]  : AWQOS value override for slave interface */
        unsigned int  reserved_0  : 4;  /* bit[4-7]  : RESERVED */
        unsigned int  awqos_value : 4;  /* bit[8-11] : Reads what value is currently applied to transactions with AWQOS=0 if QOSOVERRIDE is HIGH and QoS value regulation is enabled. */
        unsigned int  reserved_1  : 20; /* bit[12-31]: Reserved */
    } reg;
} SOC_CCI400_CCI_WCQVOR_S0_UNION;
#endif
#define SOC_CCI400_CCI_WCQVOR_S0_awqos_ov_START     (0)
#define SOC_CCI400_CCI_WCQVOR_S0_awqos_ov_END       (3)
#define SOC_CCI400_CCI_WCQVOR_S0_awqos_value_START  (8)
#define SOC_CCI400_CCI_WCQVOR_S0_awqos_value_END    (11)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_QCR_S0_UNION
 结构说明  : CCI_QCR_S0 寄存器结构定义。地址偏移量:0x9110C，初值:0x00000000，宽度:32
 寄存器说明: QOS控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  qos_reg_en    : 1;  /* bit[0]    : Enable QoS value regulation on writes for slave interfaces. */
        unsigned int  rd_s_en       : 1;  /* bit[1]    : Enable on reads for slave interfaces */
        unsigned int  osd_wr_en     : 1;  /* bit[2]    : Enable regulation of outstanding write transactions for slave interfaces.
                                                         ? ACE-Lite interfaces only: S0, S1, and S2.
                                                         ? RAZ/WI for ACE interfaces: S3 and S4. */
        unsigned int  osd_rd_en     : 1;  /* bit[3]    : Enable regulation of outstanding read transactions for slave interfaces.
                                                         ? ACE-Lite interfaces only: S0, S1, and S2.
                                                         ? RAZ/WI for ACE interfaces: S3 and S4. */
        unsigned int  reserved_0    : 12; /* bit[4-15] : Reserved. */
        unsigned int  mode_wr       : 1;  /* bit[16]   : Configures the mode of the QoS value regulator for write transactions.
                                                         0b0 Latency mode.
                                                         0b1 Period mode, for bandwidth regulation. */
        unsigned int  reserved_1    : 3;  /* bit[17-19]: Reserved. */
        unsigned int  mode_rd       : 1;  /* bit[20]   : Configures the mode of the QoS value regulator for read transactions.
                                                         0b0 Latency mode.
                                                         0b1 Period mode, for bandwidth regulation. */
        unsigned int  bandwidth_reg : 1;  /* bit[21]   : Sets the mode for bandwidth regulation:
                                                         0b0 Normal mode.
                                                         The QoS value is stable when the master is idle.
                                                         0b1 Quiesce High mode.
                                                         The QoS value tends to the maximum when the master is idle. */
        unsigned int  reserved_2    : 10; /* bit[22-31]: Reserved. */
    } reg;
} SOC_CCI400_CCI_QCR_S0_UNION;
#endif
#define SOC_CCI400_CCI_QCR_S0_qos_reg_en_START     (0)
#define SOC_CCI400_CCI_QCR_S0_qos_reg_en_END       (0)
#define SOC_CCI400_CCI_QCR_S0_rd_s_en_START        (1)
#define SOC_CCI400_CCI_QCR_S0_rd_s_en_END          (1)
#define SOC_CCI400_CCI_QCR_S0_osd_wr_en_START      (2)
#define SOC_CCI400_CCI_QCR_S0_osd_wr_en_END        (2)
#define SOC_CCI400_CCI_QCR_S0_osd_rd_en_START      (3)
#define SOC_CCI400_CCI_QCR_S0_osd_rd_en_END        (3)
#define SOC_CCI400_CCI_QCR_S0_mode_wr_START        (16)
#define SOC_CCI400_CCI_QCR_S0_mode_wr_END          (16)
#define SOC_CCI400_CCI_QCR_S0_mode_rd_START        (20)
#define SOC_CCI400_CCI_QCR_S0_mode_rd_END          (20)
#define SOC_CCI400_CCI_QCR_S0_bandwidth_reg_START  (21)
#define SOC_CCI400_CCI_QCR_S0_bandwidth_reg_END    (21)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_MOTR_S0_UNION
 结构说明  : CCI_MOTR_S0 寄存器结构定义。地址偏移量:0x91110，初值:0x00000000，宽度:32
 寄存器说明: 最大OT寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fra_awaddr : 8;  /* bit[0-7]  : Fractional part of the maximum outstanding AW addresses. */
        unsigned int  int_awaddr : 6;  /* bit[8-13] : Integer part of the maximum outstanding AW addresses. */
        unsigned int  reserved_0 : 2;  /* bit[14-15]: Reserved */
        unsigned int  fra_araddr : 8;  /* bit[16-23]: Fractional part of the maximum outstanding AR addresses */
        unsigned int  int_araddr : 6;  /* bit[24-29]: Integer part of the maximum outstanding AR addresses. */
        unsigned int  reserved_1 : 2;  /* bit[30-31]: Reserved */
    } reg;
} SOC_CCI400_CCI_MOTR_S0_UNION;
#endif
#define SOC_CCI400_CCI_MOTR_S0_fra_awaddr_START  (0)
#define SOC_CCI400_CCI_MOTR_S0_fra_awaddr_END    (7)
#define SOC_CCI400_CCI_MOTR_S0_int_awaddr_START  (8)
#define SOC_CCI400_CCI_MOTR_S0_int_awaddr_END    (13)
#define SOC_CCI400_CCI_MOTR_S0_fra_araddr_START  (16)
#define SOC_CCI400_CCI_MOTR_S0_fra_araddr_END    (23)
#define SOC_CCI400_CCI_MOTR_S0_int_araddr_START  (24)
#define SOC_CCI400_CCI_MOTR_S0_int_araddr_END    (29)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_RTR_S0_UNION
 结构说明  : CCI_RTR_S0 寄存器结构定义。地址偏移量:0x91130，初值:0x00000000，宽度:32
 寄存器说明: 目标带宽调节器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rt_aw    : 12; /* bit[0-11] : AW channel regulator target. */
        unsigned int  reserved_0: 4;  /* bit[12-15]: Reserved. */
        unsigned int  rt_ar    : 12; /* bit[16-27]: AR channel regulator target */
        unsigned int  reserved_1: 4;  /* bit[28-31]: Reserved */
    } reg;
} SOC_CCI400_CCI_RTR_S0_UNION;
#endif
#define SOC_CCI400_CCI_RTR_S0_rt_aw_START     (0)
#define SOC_CCI400_CCI_RTR_S0_rt_aw_END       (11)
#define SOC_CCI400_CCI_RTR_S0_rt_ar_START     (16)
#define SOC_CCI400_CCI_RTR_S0_rt_ar_END       (27)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_QRSFR_S0_UNION
 结构说明  : CCI_QRSFR_S0 寄存器结构定义。地址偏移量:0x91134，初值:0x00000000，宽度:32
 寄存器说明: QoS Regulator比例因子寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  awqos_sf : 3;  /* bit[0-2]  : AWQOS scale factor, power of 2 in the range 2–5-2–12. */
        unsigned int  reserved_0: 5;  /* bit[3-7]  : Reserved. */
        unsigned int  arqos_sf : 3;  /* bit[8-10] : ARQOS scale factor, power of 2 in the range 2–5-2–12. */
        unsigned int  reserved_1: 21; /* bit[11-31]: Reserved */
    } reg;
} SOC_CCI400_CCI_QRSFR_S0_UNION;
#endif
#define SOC_CCI400_CCI_QRSFR_S0_awqos_sf_START  (0)
#define SOC_CCI400_CCI_QRSFR_S0_awqos_sf_END    (2)
#define SOC_CCI400_CCI_QRSFR_S0_arqos_sf_START  (8)
#define SOC_CCI400_CCI_QRSFR_S0_arqos_sf_END    (10)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_QRR_S0_UNION
 结构说明  : CCI_QRR_S0 寄存器结构定义。地址偏移量:0x91138，初值:0x00000000，宽度:32
 寄存器说明: QoS 范围寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  awqos_min : 4;  /* bit[0-3]  : Minimum AWQOS value */
        unsigned int  reserved_0: 4;  /* bit[4-7]  : Reserved. */
        unsigned int  awqos_max : 4;  /* bit[8-11] : Maximum AWQOS value */
        unsigned int  reserved_1: 4;  /* bit[12-15]: Reserved. */
        unsigned int  arqos_min : 4;  /* bit[16-19]: Minimum ARQOS value */
        unsigned int  reserved_2: 4;  /* bit[20-23]: Reserved. */
        unsigned int  arqos_max : 4;  /* bit[24-27]: Maximum ARQOS value */
        unsigned int  reserved_3: 4;  /* bit[28-31]: Reserved */
    } reg;
} SOC_CCI400_CCI_QRR_S0_UNION;
#endif
#define SOC_CCI400_CCI_QRR_S0_awqos_min_START  (0)
#define SOC_CCI400_CCI_QRR_S0_awqos_min_END    (3)
#define SOC_CCI400_CCI_QRR_S0_awqos_max_START  (8)
#define SOC_CCI400_CCI_QRR_S0_awqos_max_END    (11)
#define SOC_CCI400_CCI_QRR_S0_arqos_min_START  (16)
#define SOC_CCI400_CCI_QRR_S0_arqos_min_END    (19)
#define SOC_CCI400_CCI_QRR_S0_arqos_max_START  (24)
#define SOC_CCI400_CCI_QRR_S0_arqos_max_END    (27)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_SCR_S1_UNION
 结构说明  : CCI_SCR_S1 寄存器结构定义。地址偏移量:0x92000，初值:0x00000000，宽度:32
 寄存器说明: snoop控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  snoop_en      : 1;  /* bit[0]   : Enable issuing of snoop requests from this slave interface.
                                                        RAZ/WI for interfaces not supporting snoops:
                                                        0b0 Disable snoop requests.
                                                        0b1 Enable snoop requests. */
        unsigned int  dvm_en        : 1;  /* bit[1]   : Enable issuing of DVM message requests from this slave interface.
                                                        RAZ/WI for interfaces not supporting DVM messages:
                                                        0b0 Disable DVM message requests.
                                                        0b1 Enable DVM message requests */
        unsigned int  reserved      : 28; /* bit[2-29]: RESERVED */
        unsigned int  snoop_support : 1;  /* bit[30]  : Slave interface supports snoops.
                                                        This is overridden to 0x0 if you set the Control Override Register [0]. */
        unsigned int  dvm_support   : 1;  /* bit[31]  : Slave interface supports DVM messages.
                                                        This is overridden to 0x0 if you set the Control Override Register [1]. */
    } reg;
} SOC_CCI400_CCI_SCR_S1_UNION;
#endif
#define SOC_CCI400_CCI_SCR_S1_snoop_en_START       (0)
#define SOC_CCI400_CCI_SCR_S1_snoop_en_END         (0)
#define SOC_CCI400_CCI_SCR_S1_dvm_en_START         (1)
#define SOC_CCI400_CCI_SCR_S1_dvm_en_END           (1)
#define SOC_CCI400_CCI_SCR_S1_snoop_support_START  (30)
#define SOC_CCI400_CCI_SCR_S1_snoop_support_END    (30)
#define SOC_CCI400_CCI_SCR_S1_dvm_support_START    (31)
#define SOC_CCI400_CCI_SCR_S1_dvm_support_END      (31)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_SOR_S1_UNION
 结构说明  : CCI_SOR_S1 寄存器结构定义。地址偏移量:0x92004，初值:0x00000000，宽度:32
 寄存器说明: 过载通过s0的操作的shareability属性
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  shareable_override : 2;  /* bit[0-1] : Shareable override for slave interface.
                                                             0x0, 0x1 Do not override AxDOMAIN inputs.
                                                             0x2 Override AxDOMAIN inputs to 0b00, all transactions are treated
                                                             as non-shareable:
                                                             ? ReadOnce becomes ReadNoSnoop.
                                                             ? WriteUnique and WriteLineUnique become WriteNoSnoop.
                                                             0x3 Override AxDOMAIN inputs to 0b01, normal transactions are
                                                             treated as shareable:
                                                             ? ReadNoSnoop becomes ReadOnce.
                                                             ? WriteNoSnoop becomes WriteUnique. */
        unsigned int  reserved           : 30; /* bit[2-31]: Reserved */
    } reg;
} SOC_CCI400_CCI_SOR_S1_UNION;
#endif
#define SOC_CCI400_CCI_SOR_S1_shareable_override_START  (0)
#define SOC_CCI400_CCI_SOR_S1_shareable_override_END    (1)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_RCQVOR_S1_UNION
 结构说明  : CCI_RCQVOR_S1 寄存器结构定义。地址偏移量:0x92100，初值:0x00000000，宽度:32
 寄存器说明: 过载通过s0读通道的操作的QoS值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  arqos_ov    : 4;  /* bit[0-3]  : ARQOS value override for slave interface */
        unsigned int  reserved_0  : 4;  /* bit[4-7]  : Reserved. */
        unsigned int  arqos_value : 4;  /* bit[8-11] : Reads what value is currently applied to transactions with ARQOS=0 if QOSOVERRIDE is HIGH and QoS value regulation is enabled. */
        unsigned int  reserved_1  : 20; /* bit[12-31]: Reserved. */
    } reg;
} SOC_CCI400_CCI_RCQVOR_S1_UNION;
#endif
#define SOC_CCI400_CCI_RCQVOR_S1_arqos_ov_START     (0)
#define SOC_CCI400_CCI_RCQVOR_S1_arqos_ov_END       (3)
#define SOC_CCI400_CCI_RCQVOR_S1_arqos_value_START  (8)
#define SOC_CCI400_CCI_RCQVOR_S1_arqos_value_END    (11)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_WCQVOR_S1_UNION
 结构说明  : CCI_WCQVOR_S1 寄存器结构定义。地址偏移量:0x92104，初值:0x00000000，宽度:32
 寄存器说明: 过载通过s0写通道的操作的QoS值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  awqos_ov    : 4;  /* bit[0-3]  : AWQOS value override for slave interface */
        unsigned int  reserved_0  : 4;  /* bit[4-7]  : RESERVED */
        unsigned int  awqos_value : 4;  /* bit[8-11] : Reads what value is currently applied to transactions with AWQOS=0 if QOSOVERRIDE is HIGH and QoS value regulation is enabled. */
        unsigned int  reserved_1  : 20; /* bit[12-31]: Reserved */
    } reg;
} SOC_CCI400_CCI_WCQVOR_S1_UNION;
#endif
#define SOC_CCI400_CCI_WCQVOR_S1_awqos_ov_START     (0)
#define SOC_CCI400_CCI_WCQVOR_S1_awqos_ov_END       (3)
#define SOC_CCI400_CCI_WCQVOR_S1_awqos_value_START  (8)
#define SOC_CCI400_CCI_WCQVOR_S1_awqos_value_END    (11)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_QCR_S1_UNION
 结构说明  : CCI_QCR_S1 寄存器结构定义。地址偏移量:0x9210C，初值:0x00000000，宽度:32
 寄存器说明: QOS控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  qos_reg_en    : 1;  /* bit[0]    : Enable QoS value regulation on writes for slave interfaces. */
        unsigned int  rd_s_en       : 1;  /* bit[1]    : Enable on reads for slave interfaces */
        unsigned int  osd_wr_en     : 1;  /* bit[2]    : Enable regulation of outstanding write transactions for slave interfaces.
                                                         ? ACE-Lite interfaces only: S0, S1, and S2.
                                                         ? RAZ/WI for ACE interfaces: S3 and S4. */
        unsigned int  osd_rd_en     : 1;  /* bit[3]    : Enable regulation of outstanding read transactions for slave interfaces.
                                                         ? ACE-Lite interfaces only: S0, S1, and S2.
                                                         ? RAZ/WI for ACE interfaces: S3 and S4. */
        unsigned int  reserved_0    : 12; /* bit[4-15] : Reserved. */
        unsigned int  mode_wr       : 1;  /* bit[16]   : Configures the mode of the QoS value regulator for write transactions.
                                                         0b0 Latency mode.
                                                         0b1 Period mode, for bandwidth regulation. */
        unsigned int  reserved_1    : 3;  /* bit[17-19]: Reserved. */
        unsigned int  mode_rd       : 1;  /* bit[20]   : Configures the mode of the QoS value regulator for read transactions.
                                                         0b0 Latency mode.
                                                         0b1 Period mode, for bandwidth regulation. */
        unsigned int  bandwidth_reg : 1;  /* bit[21]   : Sets the mode for bandwidth regulation:
                                                         0b0 Normal mode.
                                                         The QoS value is stable when the master is idle.
                                                         0b1 Quiesce High mode.
                                                         The QoS value tends to the maximum when the master is idle. */
        unsigned int  reserved_2    : 10; /* bit[22-31]: Reserved. */
    } reg;
} SOC_CCI400_CCI_QCR_S1_UNION;
#endif
#define SOC_CCI400_CCI_QCR_S1_qos_reg_en_START     (0)
#define SOC_CCI400_CCI_QCR_S1_qos_reg_en_END       (0)
#define SOC_CCI400_CCI_QCR_S1_rd_s_en_START        (1)
#define SOC_CCI400_CCI_QCR_S1_rd_s_en_END          (1)
#define SOC_CCI400_CCI_QCR_S1_osd_wr_en_START      (2)
#define SOC_CCI400_CCI_QCR_S1_osd_wr_en_END        (2)
#define SOC_CCI400_CCI_QCR_S1_osd_rd_en_START      (3)
#define SOC_CCI400_CCI_QCR_S1_osd_rd_en_END        (3)
#define SOC_CCI400_CCI_QCR_S1_mode_wr_START        (16)
#define SOC_CCI400_CCI_QCR_S1_mode_wr_END          (16)
#define SOC_CCI400_CCI_QCR_S1_mode_rd_START        (20)
#define SOC_CCI400_CCI_QCR_S1_mode_rd_END          (20)
#define SOC_CCI400_CCI_QCR_S1_bandwidth_reg_START  (21)
#define SOC_CCI400_CCI_QCR_S1_bandwidth_reg_END    (21)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_MOTR_S1_UNION
 结构说明  : CCI_MOTR_S1 寄存器结构定义。地址偏移量:0x92110，初值:0x00000000，宽度:32
 寄存器说明: 最大OT寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fra_awaddr : 8;  /* bit[0-7]  : Fractional part of the maximum outstanding AW addresses. */
        unsigned int  int_awaddr : 6;  /* bit[8-13] : Integer part of the maximum outstanding AW addresses. */
        unsigned int  reserved_0 : 2;  /* bit[14-15]: Reserved */
        unsigned int  fra_araddr : 8;  /* bit[16-23]: Fractional part of the maximum outstanding AR addresses */
        unsigned int  int_araddr : 6;  /* bit[24-29]: Integer part of the maximum outstanding AR addresses. */
        unsigned int  reserved_1 : 2;  /* bit[30-31]: Reserved */
    } reg;
} SOC_CCI400_CCI_MOTR_S1_UNION;
#endif
#define SOC_CCI400_CCI_MOTR_S1_fra_awaddr_START  (0)
#define SOC_CCI400_CCI_MOTR_S1_fra_awaddr_END    (7)
#define SOC_CCI400_CCI_MOTR_S1_int_awaddr_START  (8)
#define SOC_CCI400_CCI_MOTR_S1_int_awaddr_END    (13)
#define SOC_CCI400_CCI_MOTR_S1_fra_araddr_START  (16)
#define SOC_CCI400_CCI_MOTR_S1_fra_araddr_END    (23)
#define SOC_CCI400_CCI_MOTR_S1_int_araddr_START  (24)
#define SOC_CCI400_CCI_MOTR_S1_int_araddr_END    (29)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_RTR_S1_UNION
 结构说明  : CCI_RTR_S1 寄存器结构定义。地址偏移量:0x92130，初值:0x00000000，宽度:32
 寄存器说明: 目标带宽调节器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rt_aw    : 12; /* bit[0-11] : AW channel regulator target. */
        unsigned int  reserved_0: 4;  /* bit[12-15]: Reserved. */
        unsigned int  rt_ar    : 12; /* bit[16-27]: AR channel regulator target */
        unsigned int  reserved_1: 4;  /* bit[28-31]: Reserved */
    } reg;
} SOC_CCI400_CCI_RTR_S1_UNION;
#endif
#define SOC_CCI400_CCI_RTR_S1_rt_aw_START     (0)
#define SOC_CCI400_CCI_RTR_S1_rt_aw_END       (11)
#define SOC_CCI400_CCI_RTR_S1_rt_ar_START     (16)
#define SOC_CCI400_CCI_RTR_S1_rt_ar_END       (27)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_QRSFR_S1_UNION
 结构说明  : CCI_QRSFR_S1 寄存器结构定义。地址偏移量:0x92134，初值:0x00000000，宽度:32
 寄存器说明: QoS Regulator比例因子寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  awqos_sf : 3;  /* bit[0-2]  : AWQOS scale factor, power of 2 in the range 2–5-2–12. */
        unsigned int  reserved_0: 5;  /* bit[3-7]  : Reserved. */
        unsigned int  arqos_sf : 3;  /* bit[8-10] : ARQOS scale factor, power of 2 in the range 2–5-2–12. */
        unsigned int  reserved_1: 21; /* bit[11-31]: Reserved */
    } reg;
} SOC_CCI400_CCI_QRSFR_S1_UNION;
#endif
#define SOC_CCI400_CCI_QRSFR_S1_awqos_sf_START  (0)
#define SOC_CCI400_CCI_QRSFR_S1_awqos_sf_END    (2)
#define SOC_CCI400_CCI_QRSFR_S1_arqos_sf_START  (8)
#define SOC_CCI400_CCI_QRSFR_S1_arqos_sf_END    (10)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_QRR_S1_UNION
 结构说明  : CCI_QRR_S1 寄存器结构定义。地址偏移量:0x92138，初值:0x00000000，宽度:32
 寄存器说明: QoS 范围寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  awqos_min : 4;  /* bit[0-3]  : Minimum AWQOS value */
        unsigned int  reserved_0: 4;  /* bit[4-7]  : Reserved. */
        unsigned int  awqos_max : 4;  /* bit[8-11] : Maximum AWQOS value */
        unsigned int  reserved_1: 4;  /* bit[12-15]: Reserved. */
        unsigned int  arqos_min : 4;  /* bit[16-19]: Minimum ARQOS value */
        unsigned int  reserved_2: 4;  /* bit[20-23]: Reserved. */
        unsigned int  arqos_max : 4;  /* bit[24-27]: Maximum ARQOS value */
        unsigned int  reserved_3: 4;  /* bit[28-31]: Reserved */
    } reg;
} SOC_CCI400_CCI_QRR_S1_UNION;
#endif
#define SOC_CCI400_CCI_QRR_S1_awqos_min_START  (0)
#define SOC_CCI400_CCI_QRR_S1_awqos_min_END    (3)
#define SOC_CCI400_CCI_QRR_S1_awqos_max_START  (8)
#define SOC_CCI400_CCI_QRR_S1_awqos_max_END    (11)
#define SOC_CCI400_CCI_QRR_S1_arqos_min_START  (16)
#define SOC_CCI400_CCI_QRR_S1_arqos_min_END    (19)
#define SOC_CCI400_CCI_QRR_S1_arqos_max_START  (24)
#define SOC_CCI400_CCI_QRR_S1_arqos_max_END    (27)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_SCR_S2_UNION
 结构说明  : CCI_SCR_S2 寄存器结构定义。地址偏移量:0x93000，初值:0x80000000，宽度:32
 寄存器说明: snoop控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  snoop_en      : 1;  /* bit[0]   : Enable issuing of snoop requests from this slave interface.
                                                        RAZ/WI for interfaces not supporting snoops:
                                                        0b0 Disable snoop requests.
                                                        0b1 Enable snoop requests. */
        unsigned int  dvm_en        : 1;  /* bit[1]   : Enable issuing of DVM message requests from this slave interface.
                                                        RAZ/WI for interfaces not supporting DVM messages:
                                                        0b0 Disable DVM message requests.
                                                        0b1 Enable DVM message requests */
        unsigned int  reserved      : 28; /* bit[2-29]: RESERVED */
        unsigned int  snoop_support : 1;  /* bit[30]  : Slave interface supports snoops.
                                                        This is overridden to 0x0 if you set the Control Override Register [0]. */
        unsigned int  dvm_support   : 1;  /* bit[31]  : Slave interface supports DVM messages.
                                                        This is overridden to 0x0 if you set the Control Override Register [1]. */
    } reg;
} SOC_CCI400_CCI_SCR_S2_UNION;
#endif
#define SOC_CCI400_CCI_SCR_S2_snoop_en_START       (0)
#define SOC_CCI400_CCI_SCR_S2_snoop_en_END         (0)
#define SOC_CCI400_CCI_SCR_S2_dvm_en_START         (1)
#define SOC_CCI400_CCI_SCR_S2_dvm_en_END           (1)
#define SOC_CCI400_CCI_SCR_S2_snoop_support_START  (30)
#define SOC_CCI400_CCI_SCR_S2_snoop_support_END    (30)
#define SOC_CCI400_CCI_SCR_S2_dvm_support_START    (31)
#define SOC_CCI400_CCI_SCR_S2_dvm_support_END      (31)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_SOR_S2_UNION
 结构说明  : CCI_SOR_S2 寄存器结构定义。地址偏移量:0x93004，初值:0x00000000，宽度:32
 寄存器说明: 过载通过s0的操作的shareability属性
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  shareable_override : 2;  /* bit[0-1] : Shareable override for slave interface.
                                                             0x0, 0x1 Do not override AxDOMAIN inputs.
                                                             0x2 Override AxDOMAIN inputs to 0b00, all transactions are treated
                                                             as non-shareable:
                                                             ? ReadOnce becomes ReadNoSnoop.
                                                             ? WriteUnique and WriteLineUnique become WriteNoSnoop.
                                                             0x3 Override AxDOMAIN inputs to 0b01, normal transactions are
                                                             treated as shareable:
                                                             ? ReadNoSnoop becomes ReadOnce.
                                                             ? WriteNoSnoop becomes WriteUnique. */
        unsigned int  reserved           : 30; /* bit[2-31]: Reserved */
    } reg;
} SOC_CCI400_CCI_SOR_S2_UNION;
#endif
#define SOC_CCI400_CCI_SOR_S2_shareable_override_START  (0)
#define SOC_CCI400_CCI_SOR_S2_shareable_override_END    (1)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_RCQVOR_S2_UNION
 结构说明  : CCI_RCQVOR_S2 寄存器结构定义。地址偏移量:0x93100，初值:0x00000000，宽度:32
 寄存器说明: 过载通过s0读通道的操作的QoS值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  arqos_ov    : 4;  /* bit[0-3]  : ARQOS value override for slave interface */
        unsigned int  reserved_0  : 4;  /* bit[4-7]  : Reserved. */
        unsigned int  arqos_value : 4;  /* bit[8-11] : Reads what value is currently applied to transactions with ARQOS=0 if QOSOVERRIDE is HIGH and QoS value regulation is enabled. */
        unsigned int  reserved_1  : 20; /* bit[12-31]: Reserved. */
    } reg;
} SOC_CCI400_CCI_RCQVOR_S2_UNION;
#endif
#define SOC_CCI400_CCI_RCQVOR_S2_arqos_ov_START     (0)
#define SOC_CCI400_CCI_RCQVOR_S2_arqos_ov_END       (3)
#define SOC_CCI400_CCI_RCQVOR_S2_arqos_value_START  (8)
#define SOC_CCI400_CCI_RCQVOR_S2_arqos_value_END    (11)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_WCQVOR_S2_UNION
 结构说明  : CCI_WCQVOR_S2 寄存器结构定义。地址偏移量:0x93104，初值:0x00000000，宽度:32
 寄存器说明: 过载通过s0写通道的操作的QoS值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  awqos_ov    : 4;  /* bit[0-3]  : AWQOS value override for slave interface */
        unsigned int  reserved_0  : 4;  /* bit[4-7]  : RESERVED */
        unsigned int  awqos_value : 4;  /* bit[8-11] : Reads what value is currently applied to transactions with AWQOS=0 if QOSOVERRIDE is HIGH and QoS value regulation is enabled. */
        unsigned int  reserved_1  : 20; /* bit[12-31]: 保留 */
    } reg;
} SOC_CCI400_CCI_WCQVOR_S2_UNION;
#endif
#define SOC_CCI400_CCI_WCQVOR_S2_awqos_ov_START     (0)
#define SOC_CCI400_CCI_WCQVOR_S2_awqos_ov_END       (3)
#define SOC_CCI400_CCI_WCQVOR_S2_awqos_value_START  (8)
#define SOC_CCI400_CCI_WCQVOR_S2_awqos_value_END    (11)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_QCR_S2_UNION
 结构说明  : CCI_QCR_S2 寄存器结构定义。地址偏移量:0x9310C，初值:0x00000000，宽度:32
 寄存器说明: QOS控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  qos_reg_en    : 1;  /* bit[0]    : Enable QoS value regulation on writes for slave interfaces. */
        unsigned int  rd_s_en       : 1;  /* bit[1]    : Enable on reads for slave interfaces */
        unsigned int  osd_wr_en     : 1;  /* bit[2]    : Enable regulation of outstanding write transactions for slave interfaces.
                                                         ? ACE-Lite interfaces only: S0, S1, and S2.
                                                         ? RAZ/WI for ACE interfaces: S3 and S4. */
        unsigned int  osd_rd_en     : 1;  /* bit[3]    : Enable regulation of outstanding read transactions for slave interfaces.
                                                         ? ACE-Lite interfaces only: S0, S1, and S2.
                                                         ? RAZ/WI for ACE interfaces: S3 and S4. */
        unsigned int  reserved_0    : 12; /* bit[4-15] : Reserved. */
        unsigned int  mode_wr       : 1;  /* bit[16]   : Configures the mode of the QoS value regulator for write transactions.
                                                         0b0 Latency mode.
                                                         0b1 Period mode, for bandwidth regulation. */
        unsigned int  reserved_1    : 3;  /* bit[17-19]: Reserved. */
        unsigned int  mode_rd       : 1;  /* bit[20]   : Configures the mode of the QoS value regulator for read transactions.
                                                         0b0 Latency mode.
                                                         0b1 Period mode, for bandwidth regulation. */
        unsigned int  bandwidth_reg : 1;  /* bit[21]   : Sets the mode for bandwidth regulation:
                                                         0b0 Normal mode.
                                                         The QoS value is stable when the master is idle.
                                                         0b1 Quiesce High mode.
                                                         The QoS value tends to the maximum when the master is idle. */
        unsigned int  reserved_2    : 10; /* bit[22-31]: Reserved. */
    } reg;
} SOC_CCI400_CCI_QCR_S2_UNION;
#endif
#define SOC_CCI400_CCI_QCR_S2_qos_reg_en_START     (0)
#define SOC_CCI400_CCI_QCR_S2_qos_reg_en_END       (0)
#define SOC_CCI400_CCI_QCR_S2_rd_s_en_START        (1)
#define SOC_CCI400_CCI_QCR_S2_rd_s_en_END          (1)
#define SOC_CCI400_CCI_QCR_S2_osd_wr_en_START      (2)
#define SOC_CCI400_CCI_QCR_S2_osd_wr_en_END        (2)
#define SOC_CCI400_CCI_QCR_S2_osd_rd_en_START      (3)
#define SOC_CCI400_CCI_QCR_S2_osd_rd_en_END        (3)
#define SOC_CCI400_CCI_QCR_S2_mode_wr_START        (16)
#define SOC_CCI400_CCI_QCR_S2_mode_wr_END          (16)
#define SOC_CCI400_CCI_QCR_S2_mode_rd_START        (20)
#define SOC_CCI400_CCI_QCR_S2_mode_rd_END          (20)
#define SOC_CCI400_CCI_QCR_S2_bandwidth_reg_START  (21)
#define SOC_CCI400_CCI_QCR_S2_bandwidth_reg_END    (21)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_MOTR_S2_UNION
 结构说明  : CCI_MOTR_S2 寄存器结构定义。地址偏移量:0x93110，初值:0x00000000，宽度:32
 寄存器说明: 最大OT寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fra_awaddr : 8;  /* bit[0-7]  : Fractional part of the maximum outstanding AW addresses. */
        unsigned int  int_awaddr : 6;  /* bit[8-13] : Integer part of the maximum outstanding AW addresses. */
        unsigned int  reserved_0 : 2;  /* bit[14-15]: Reserved */
        unsigned int  fra_araddr : 8;  /* bit[16-23]: Fractional part of the maximum outstanding AR addresses */
        unsigned int  int_araddr : 6;  /* bit[24-29]: Integer part of the maximum outstanding AR addresses. */
        unsigned int  reserved_1 : 2;  /* bit[30-31]: Reserved */
    } reg;
} SOC_CCI400_CCI_MOTR_S2_UNION;
#endif
#define SOC_CCI400_CCI_MOTR_S2_fra_awaddr_START  (0)
#define SOC_CCI400_CCI_MOTR_S2_fra_awaddr_END    (7)
#define SOC_CCI400_CCI_MOTR_S2_int_awaddr_START  (8)
#define SOC_CCI400_CCI_MOTR_S2_int_awaddr_END    (13)
#define SOC_CCI400_CCI_MOTR_S2_fra_araddr_START  (16)
#define SOC_CCI400_CCI_MOTR_S2_fra_araddr_END    (23)
#define SOC_CCI400_CCI_MOTR_S2_int_araddr_START  (24)
#define SOC_CCI400_CCI_MOTR_S2_int_araddr_END    (29)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_RTR_S2_UNION
 结构说明  : CCI_RTR_S2 寄存器结构定义。地址偏移量:0x93130，初值:0x00000000，宽度:32
 寄存器说明: 目标带宽调节器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rt_aw    : 12; /* bit[0-11] : AW channel regulator target. */
        unsigned int  reserved_0: 4;  /* bit[12-15]: Reserved. */
        unsigned int  rt_ar    : 12; /* bit[16-27]: AR channel regulator target */
        unsigned int  reserved_1: 4;  /* bit[28-31]: Reserved */
    } reg;
} SOC_CCI400_CCI_RTR_S2_UNION;
#endif
#define SOC_CCI400_CCI_RTR_S2_rt_aw_START     (0)
#define SOC_CCI400_CCI_RTR_S2_rt_aw_END       (11)
#define SOC_CCI400_CCI_RTR_S2_rt_ar_START     (16)
#define SOC_CCI400_CCI_RTR_S2_rt_ar_END       (27)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_QRSFR_S2_UNION
 结构说明  : CCI_QRSFR_S2 寄存器结构定义。地址偏移量:0x93134，初值:0x00000000，宽度:32
 寄存器说明: QoS Regulator比例因子寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  awqos_sf : 3;  /* bit[0-2]  : AWQOS scale factor, power of 2 in the range 2–5-2–12. */
        unsigned int  reserved_0: 5;  /* bit[3-7]  : Reserved. */
        unsigned int  arqos_sf : 3;  /* bit[8-10] : ARQOS scale factor, power of 2 in the range 2–5-2–12. */
        unsigned int  reserved_1: 21; /* bit[11-31]: Reserved */
    } reg;
} SOC_CCI400_CCI_QRSFR_S2_UNION;
#endif
#define SOC_CCI400_CCI_QRSFR_S2_awqos_sf_START  (0)
#define SOC_CCI400_CCI_QRSFR_S2_awqos_sf_END    (2)
#define SOC_CCI400_CCI_QRSFR_S2_arqos_sf_START  (8)
#define SOC_CCI400_CCI_QRSFR_S2_arqos_sf_END    (10)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_QRR_S2_UNION
 结构说明  : CCI_QRR_S2 寄存器结构定义。地址偏移量:0x93138，初值:0x00000000，宽度:32
 寄存器说明: QoS 范围寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  awqos_min : 4;  /* bit[0-3]  : Minimum AWQOS value */
        unsigned int  reserved_0: 4;  /* bit[4-7]  : Reserved. */
        unsigned int  awqos_max : 4;  /* bit[8-11] : Maximum AWQOS value */
        unsigned int  reserved_1: 4;  /* bit[12-15]: Reserved. */
        unsigned int  arqos_min : 4;  /* bit[16-19]: Minimum ARQOS value */
        unsigned int  reserved_2: 4;  /* bit[20-23]: Reserved. */
        unsigned int  arqos_max : 4;  /* bit[24-27]: Maximum ARQOS value */
        unsigned int  reserved_3: 4;  /* bit[28-31]: Reserved */
    } reg;
} SOC_CCI400_CCI_QRR_S2_UNION;
#endif
#define SOC_CCI400_CCI_QRR_S2_awqos_min_START  (0)
#define SOC_CCI400_CCI_QRR_S2_awqos_min_END    (3)
#define SOC_CCI400_CCI_QRR_S2_awqos_max_START  (8)
#define SOC_CCI400_CCI_QRR_S2_awqos_max_END    (11)
#define SOC_CCI400_CCI_QRR_S2_arqos_min_START  (16)
#define SOC_CCI400_CCI_QRR_S2_arqos_min_END    (19)
#define SOC_CCI400_CCI_QRR_S2_arqos_max_START  (24)
#define SOC_CCI400_CCI_QRR_S2_arqos_max_END    (27)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_SCR_S3_UNION
 结构说明  : CCI_SCR_S3 寄存器结构定义。地址偏移量:0x94000，初值:0xC0000000，宽度:32
 寄存器说明: snoop控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  snoop_en      : 1;  /* bit[0]   : Enable issuing of snoop requests from this slave interface.
                                                        RAZ/WI for interfaces not supporting snoops:
                                                        0b0 Disable snoop requests.
                                                        0b1 Enable snoop requests. */
        unsigned int  dvm_en        : 1;  /* bit[1]   : Enable issuing of DVM message requests from this slave interface.
                                                        RAZ/WI for interfaces not supporting DVM messages:
                                                        0b0 Disable DVM message requests.
                                                        0b1 Enable DVM message requests */
        unsigned int  reserved      : 28; /* bit[2-29]: RESERVED */
        unsigned int  snoop_support : 1;  /* bit[30]  : Slave interface supports snoops.
                                                        This is overridden to 0x0 if you set the Control Override Register [0]. */
        unsigned int  dvm_support   : 1;  /* bit[31]  : Slave interface supports DVM messages.
                                                        This is overridden to 0x0 if you set the Control Override Register [1]. */
    } reg;
} SOC_CCI400_CCI_SCR_S3_UNION;
#endif
#define SOC_CCI400_CCI_SCR_S3_snoop_en_START       (0)
#define SOC_CCI400_CCI_SCR_S3_snoop_en_END         (0)
#define SOC_CCI400_CCI_SCR_S3_dvm_en_START         (1)
#define SOC_CCI400_CCI_SCR_S3_dvm_en_END           (1)
#define SOC_CCI400_CCI_SCR_S3_snoop_support_START  (30)
#define SOC_CCI400_CCI_SCR_S3_snoop_support_END    (30)
#define SOC_CCI400_CCI_SCR_S3_dvm_support_START    (31)
#define SOC_CCI400_CCI_SCR_S3_dvm_support_END      (31)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_RCQVOR_S3_UNION
 结构说明  : CCI_RCQVOR_S3 寄存器结构定义。地址偏移量:0x94100，初值:0x00000000，宽度:32
 寄存器说明: 过载通过s0读通道的操作的QoS值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  arqos_ov    : 4;  /* bit[0-3]  : ARQOS value override for slave interface */
        unsigned int  reserved_0  : 4;  /* bit[4-7]  : Reserved. */
        unsigned int  arqos_value : 4;  /* bit[8-11] : Reads what value is currently applied to transactions with ARQOS=0 if QOSOVERRIDE is HIGH and QoS value regulation is enabled. */
        unsigned int  reserved_1  : 20; /* bit[12-31]: Reserved. */
    } reg;
} SOC_CCI400_CCI_RCQVOR_S3_UNION;
#endif
#define SOC_CCI400_CCI_RCQVOR_S3_arqos_ov_START     (0)
#define SOC_CCI400_CCI_RCQVOR_S3_arqos_ov_END       (3)
#define SOC_CCI400_CCI_RCQVOR_S3_arqos_value_START  (8)
#define SOC_CCI400_CCI_RCQVOR_S3_arqos_value_END    (11)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_WCQVOR_S3_UNION
 结构说明  : CCI_WCQVOR_S3 寄存器结构定义。地址偏移量:0x94104，初值:0x00000000，宽度:32
 寄存器说明: 过载通过s0写通道的操作的QoS值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  awqos_ov    : 4;  /* bit[0-3]  : AWQOS value override for slave interface */
        unsigned int  reserved_0  : 4;  /* bit[4-7]  : RESERVED */
        unsigned int  awqos_value : 4;  /* bit[8-11] : Reads what value is currently applied to transactions with AWQOS=0 if QOSOVERRIDE is HIGH and QoS value regulation is enabled. */
        unsigned int  reserved_1  : 20; /* bit[12-31]: 保留 */
    } reg;
} SOC_CCI400_CCI_WCQVOR_S3_UNION;
#endif
#define SOC_CCI400_CCI_WCQVOR_S3_awqos_ov_START     (0)
#define SOC_CCI400_CCI_WCQVOR_S3_awqos_ov_END       (3)
#define SOC_CCI400_CCI_WCQVOR_S3_awqos_value_START  (8)
#define SOC_CCI400_CCI_WCQVOR_S3_awqos_value_END    (11)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_QCR_S3_UNION
 结构说明  : CCI_QCR_S3 寄存器结构定义。地址偏移量:0x9410C，初值:0x00000000，宽度:32
 寄存器说明: QOS控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  qos_reg_en    : 1;  /* bit[0]    : Enable QoS value regulation on writes for slave interfaces. */
        unsigned int  rd_s_en       : 1;  /* bit[1]    : Enable on reads for slave interfaces */
        unsigned int  osd_wr_en     : 1;  /* bit[2]    : Enable regulation of outstanding write transactions for slave interfaces.
                                                         ? ACE-Lite interfaces only: S0, S1, and S2.
                                                         ? RAZ/WI for ACE interfaces: S3 and S4. */
        unsigned int  osd_rd_en     : 1;  /* bit[3]    : Enable regulation of outstanding read transactions for slave interfaces.
                                                         ? ACE-Lite interfaces only: S0, S1, and S2.
                                                         ? RAZ/WI for ACE interfaces: S3 and S4. */
        unsigned int  reserved_0    : 12; /* bit[4-15] : Reserved. */
        unsigned int  mode_wr       : 1;  /* bit[16]   : Configures the mode of the QoS value regulator for write transactions.
                                                         0b0 Latency mode.
                                                         0b1 Period mode, for bandwidth regulation. */
        unsigned int  reserved_1    : 3;  /* bit[17-19]: Reserved. */
        unsigned int  mode_rd       : 1;  /* bit[20]   : Configures the mode of the QoS value regulator for read transactions.
                                                         0b0 Latency mode.
                                                         0b1 Period mode, for bandwidth regulation. */
        unsigned int  bandwidth_reg : 1;  /* bit[21]   : Sets the mode for bandwidth regulation:
                                                         0b0 Normal mode.
                                                         The QoS value is stable when the master is idle.
                                                         0b1 Quiesce High mode.
                                                         The QoS value tends to the maximum when the master is idle. */
        unsigned int  reserved_2    : 10; /* bit[22-31]: Reserved. */
    } reg;
} SOC_CCI400_CCI_QCR_S3_UNION;
#endif
#define SOC_CCI400_CCI_QCR_S3_qos_reg_en_START     (0)
#define SOC_CCI400_CCI_QCR_S3_qos_reg_en_END       (0)
#define SOC_CCI400_CCI_QCR_S3_rd_s_en_START        (1)
#define SOC_CCI400_CCI_QCR_S3_rd_s_en_END          (1)
#define SOC_CCI400_CCI_QCR_S3_osd_wr_en_START      (2)
#define SOC_CCI400_CCI_QCR_S3_osd_wr_en_END        (2)
#define SOC_CCI400_CCI_QCR_S3_osd_rd_en_START      (3)
#define SOC_CCI400_CCI_QCR_S3_osd_rd_en_END        (3)
#define SOC_CCI400_CCI_QCR_S3_mode_wr_START        (16)
#define SOC_CCI400_CCI_QCR_S3_mode_wr_END          (16)
#define SOC_CCI400_CCI_QCR_S3_mode_rd_START        (20)
#define SOC_CCI400_CCI_QCR_S3_mode_rd_END          (20)
#define SOC_CCI400_CCI_QCR_S3_bandwidth_reg_START  (21)
#define SOC_CCI400_CCI_QCR_S3_bandwidth_reg_END    (21)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_RTR_S3_UNION
 结构说明  : CCI_RTR_S3 寄存器结构定义。地址偏移量:0x94130，初值:0x00000000，宽度:32
 寄存器说明: 目标带宽调节器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rt_aw    : 12; /* bit[0-11] : AW channel regulator target. */
        unsigned int  reserved_0: 4;  /* bit[12-15]: Reserved. */
        unsigned int  rt_ar    : 12; /* bit[16-27]: AR channel regulator target */
        unsigned int  reserved_1: 4;  /* bit[28-31]: Reserved */
    } reg;
} SOC_CCI400_CCI_RTR_S3_UNION;
#endif
#define SOC_CCI400_CCI_RTR_S3_rt_aw_START     (0)
#define SOC_CCI400_CCI_RTR_S3_rt_aw_END       (11)
#define SOC_CCI400_CCI_RTR_S3_rt_ar_START     (16)
#define SOC_CCI400_CCI_RTR_S3_rt_ar_END       (27)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_QRSFR_S3_UNION
 结构说明  : CCI_QRSFR_S3 寄存器结构定义。地址偏移量:0x94134，初值:0x00000000，宽度:32
 寄存器说明: QoS Regulator比例因子寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  awqos_sf : 3;  /* bit[0-2]  : AWQOS scale factor, power of 2 in the range 2–5-2–12. */
        unsigned int  reserved_0: 5;  /* bit[3-7]  : Reserved. */
        unsigned int  arqos_sf : 3;  /* bit[8-10] : ARQOS scale factor, power of 2 in the range 2–5-2–12. */
        unsigned int  reserved_1: 21; /* bit[11-31]: Reserved */
    } reg;
} SOC_CCI400_CCI_QRSFR_S3_UNION;
#endif
#define SOC_CCI400_CCI_QRSFR_S3_awqos_sf_START  (0)
#define SOC_CCI400_CCI_QRSFR_S3_awqos_sf_END    (2)
#define SOC_CCI400_CCI_QRSFR_S3_arqos_sf_START  (8)
#define SOC_CCI400_CCI_QRSFR_S3_arqos_sf_END    (10)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_QRR_S3_UNION
 结构说明  : CCI_QRR_S3 寄存器结构定义。地址偏移量:0x94138，初值:0x00000000，宽度:32
 寄存器说明: QoS 范围寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  awqos_min : 4;  /* bit[0-3]  : Minimum AWQOS value */
        unsigned int  reserved_0: 4;  /* bit[4-7]  : Reserved. */
        unsigned int  awqos_max : 4;  /* bit[8-11] : Maximum AWQOS value */
        unsigned int  reserved_1: 4;  /* bit[12-15]: Reserved. */
        unsigned int  arqos_min : 4;  /* bit[16-19]: Minimum ARQOS value */
        unsigned int  reserved_2: 4;  /* bit[20-23]: Reserved. */
        unsigned int  arqos_max : 4;  /* bit[24-27]: Maximum ARQOS value */
        unsigned int  reserved_3: 4;  /* bit[28-31]: Reserved */
    } reg;
} SOC_CCI400_CCI_QRR_S3_UNION;
#endif
#define SOC_CCI400_CCI_QRR_S3_awqos_min_START  (0)
#define SOC_CCI400_CCI_QRR_S3_awqos_min_END    (3)
#define SOC_CCI400_CCI_QRR_S3_awqos_max_START  (8)
#define SOC_CCI400_CCI_QRR_S3_awqos_max_END    (11)
#define SOC_CCI400_CCI_QRR_S3_arqos_min_START  (16)
#define SOC_CCI400_CCI_QRR_S3_arqos_min_END    (19)
#define SOC_CCI400_CCI_QRR_S3_arqos_max_START  (24)
#define SOC_CCI400_CCI_QRR_S3_arqos_max_END    (27)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_SCR_S4_UNION
 结构说明  : CCI_SCR_S4 寄存器结构定义。地址偏移量:0x95000，初值:0xC0000000，宽度:32
 寄存器说明: snoop控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  snoop_en      : 1;  /* bit[0]   : Enable issuing of snoop requests from this slave interface.
                                                        RAZ/WI for interfaces not supporting snoops:
                                                        0b0 Disable snoop requests.
                                                        0b1 Enable snoop requests. */
        unsigned int  dvm_en        : 1;  /* bit[1]   : Enable issuing of DVM message requests from this slave interface.
                                                        RAZ/WI for interfaces not supporting DVM messages:
                                                        0b0 Disable DVM message requests.
                                                        0b1 Enable DVM message requests */
        unsigned int  reserved      : 28; /* bit[2-29]: RESERVED */
        unsigned int  snoop_support : 1;  /* bit[30]  : Slave interface supports snoops.
                                                        This is overridden to 0x0 if you set the Control Override Register [0]. */
        unsigned int  dvm_support   : 1;  /* bit[31]  : Slave interface supports DVM messages.
                                                        This is overridden to 0x0 if you set the Control Override Register [1]. */
    } reg;
} SOC_CCI400_CCI_SCR_S4_UNION;
#endif
#define SOC_CCI400_CCI_SCR_S4_snoop_en_START       (0)
#define SOC_CCI400_CCI_SCR_S4_snoop_en_END         (0)
#define SOC_CCI400_CCI_SCR_S4_dvm_en_START         (1)
#define SOC_CCI400_CCI_SCR_S4_dvm_en_END           (1)
#define SOC_CCI400_CCI_SCR_S4_snoop_support_START  (30)
#define SOC_CCI400_CCI_SCR_S4_snoop_support_END    (30)
#define SOC_CCI400_CCI_SCR_S4_dvm_support_START    (31)
#define SOC_CCI400_CCI_SCR_S4_dvm_support_END      (31)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_RCQVOR_S4_UNION
 结构说明  : CCI_RCQVOR_S4 寄存器结构定义。地址偏移量:0x95100，初值:0x00000000，宽度:32
 寄存器说明: 过载通过s0读通道的操作的QoS值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  arqos_ov    : 4;  /* bit[0-3]  : ARQOS value override for slave interface */
        unsigned int  reserved_0  : 4;  /* bit[4-7]  : Reserved. */
        unsigned int  arqos_value : 4;  /* bit[8-11] : Reads what value is currently applied to transactions with ARQOS=0 if QOSOVERRIDE is HIGH and QoS value regulation is enabled. */
        unsigned int  reserved_1  : 20; /* bit[12-31]: Reserved. */
    } reg;
} SOC_CCI400_CCI_RCQVOR_S4_UNION;
#endif
#define SOC_CCI400_CCI_RCQVOR_S4_arqos_ov_START     (0)
#define SOC_CCI400_CCI_RCQVOR_S4_arqos_ov_END       (3)
#define SOC_CCI400_CCI_RCQVOR_S4_arqos_value_START  (8)
#define SOC_CCI400_CCI_RCQVOR_S4_arqos_value_END    (11)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_WCQVOR_S4_UNION
 结构说明  : CCI_WCQVOR_S4 寄存器结构定义。地址偏移量:0x95104，初值:0x00000000，宽度:32
 寄存器说明: 过载通过s0写通道的操作的QoS值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  awqos_ov    : 4;  /* bit[0-3]  : AWQOS value override for slave interface */
        unsigned int  reserved_0  : 4;  /* bit[4-7]  : RESERVED */
        unsigned int  awqos_value : 4;  /* bit[8-11] : Reads what value is currently applied to transactions with AWQOS=0 if QOSOVERRIDE is HIGH and QoS value regulation is enabled. */
        unsigned int  reserved_1  : 20; /* bit[12-31]: 保留 */
    } reg;
} SOC_CCI400_CCI_WCQVOR_S4_UNION;
#endif
#define SOC_CCI400_CCI_WCQVOR_S4_awqos_ov_START     (0)
#define SOC_CCI400_CCI_WCQVOR_S4_awqos_ov_END       (3)
#define SOC_CCI400_CCI_WCQVOR_S4_awqos_value_START  (8)
#define SOC_CCI400_CCI_WCQVOR_S4_awqos_value_END    (11)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_QCR_S4_UNION
 结构说明  : CCI_QCR_S4 寄存器结构定义。地址偏移量:0x9510C，初值:0x00000000，宽度:32
 寄存器说明: QOS控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  qos_reg_en    : 1;  /* bit[0]    : Enable QoS value regulation on writes for slave interfaces. */
        unsigned int  rd_s_en       : 1;  /* bit[1]    : Enable on reads for slave interfaces */
        unsigned int  osd_wr_en     : 1;  /* bit[2]    : Enable regulation of outstanding write transactions for slave interfaces.
                                                         ? ACE-Lite interfaces only: S0, S1, and S2.
                                                         ? RAZ/WI for ACE interfaces: S3 and S4. */
        unsigned int  osd_rd_en     : 1;  /* bit[3]    : Enable regulation of outstanding read transactions for slave interfaces.
                                                         ? ACE-Lite interfaces only: S0, S1, and S2.
                                                         ? RAZ/WI for ACE interfaces: S3 and S4. */
        unsigned int  reserved_0    : 12; /* bit[4-15] : Reserved. */
        unsigned int  mode_wr       : 1;  /* bit[16]   : Configures the mode of the QoS value regulator for write transactions.
                                                         0b0 Latency mode.
                                                         0b1 Period mode, for bandwidth regulation. */
        unsigned int  reserved_1    : 3;  /* bit[17-19]: Reserved. */
        unsigned int  mode_rd       : 1;  /* bit[20]   : Configures the mode of the QoS value regulator for read transactions.
                                                         0b0 Latency mode.
                                                         0b1 Period mode, for bandwidth regulation. */
        unsigned int  bandwidth_reg : 1;  /* bit[21]   : Sets the mode for bandwidth regulation:
                                                         0b0 Normal mode.
                                                         The QoS value is stable when the master is idle.
                                                         0b1 Quiesce High mode.
                                                         The QoS value tends to the maximum when the master is idle. */
        unsigned int  reserved_2    : 10; /* bit[22-31]: Reserved. */
    } reg;
} SOC_CCI400_CCI_QCR_S4_UNION;
#endif
#define SOC_CCI400_CCI_QCR_S4_qos_reg_en_START     (0)
#define SOC_CCI400_CCI_QCR_S4_qos_reg_en_END       (0)
#define SOC_CCI400_CCI_QCR_S4_rd_s_en_START        (1)
#define SOC_CCI400_CCI_QCR_S4_rd_s_en_END          (1)
#define SOC_CCI400_CCI_QCR_S4_osd_wr_en_START      (2)
#define SOC_CCI400_CCI_QCR_S4_osd_wr_en_END        (2)
#define SOC_CCI400_CCI_QCR_S4_osd_rd_en_START      (3)
#define SOC_CCI400_CCI_QCR_S4_osd_rd_en_END        (3)
#define SOC_CCI400_CCI_QCR_S4_mode_wr_START        (16)
#define SOC_CCI400_CCI_QCR_S4_mode_wr_END          (16)
#define SOC_CCI400_CCI_QCR_S4_mode_rd_START        (20)
#define SOC_CCI400_CCI_QCR_S4_mode_rd_END          (20)
#define SOC_CCI400_CCI_QCR_S4_bandwidth_reg_START  (21)
#define SOC_CCI400_CCI_QCR_S4_bandwidth_reg_END    (21)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_RTR_S4_UNION
 结构说明  : CCI_RTR_S4 寄存器结构定义。地址偏移量:0x95130，初值:0x00000000，宽度:32
 寄存器说明: 目标带宽调节器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rt_aw    : 12; /* bit[0-11] : AW channel regulator target. */
        unsigned int  reserved_0: 4;  /* bit[12-15]: Reserved. */
        unsigned int  rt_ar    : 12; /* bit[16-27]: AR channel regulator target */
        unsigned int  reserved_1: 4;  /* bit[28-31]: Reserved */
    } reg;
} SOC_CCI400_CCI_RTR_S4_UNION;
#endif
#define SOC_CCI400_CCI_RTR_S4_rt_aw_START     (0)
#define SOC_CCI400_CCI_RTR_S4_rt_aw_END       (11)
#define SOC_CCI400_CCI_RTR_S4_rt_ar_START     (16)
#define SOC_CCI400_CCI_RTR_S4_rt_ar_END       (27)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_QRSFR_S4_UNION
 结构说明  : CCI_QRSFR_S4 寄存器结构定义。地址偏移量:0x91134，初值:0x00000000，宽度:32
 寄存器说明: QoS Regulator比例因子寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  awqos_sf : 3;  /* bit[0-2]  : AWQOS scale factor, power of 2 in the range 2–5-2–12. */
        unsigned int  reserved_0: 5;  /* bit[3-7]  : Reserved. */
        unsigned int  arqos_sf : 3;  /* bit[8-10] : ARQOS scale factor, power of 2 in the range 2–5-2–12. */
        unsigned int  reserved_1: 21; /* bit[11-31]: Reserved */
    } reg;
} SOC_CCI400_CCI_QRSFR_S4_UNION;
#endif
#define SOC_CCI400_CCI_QRSFR_S4_awqos_sf_START  (0)
#define SOC_CCI400_CCI_QRSFR_S4_awqos_sf_END    (2)
#define SOC_CCI400_CCI_QRSFR_S4_arqos_sf_START  (8)
#define SOC_CCI400_CCI_QRSFR_S4_arqos_sf_END    (10)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_QRR_S4_UNION
 结构说明  : CCI_QRR_S4 寄存器结构定义。地址偏移量:0x95138，初值:0x00000000，宽度:32
 寄存器说明: QoS 范围寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  awqos_min : 4;  /* bit[0-3]  : Minimum AWQOS value */
        unsigned int  reserved_0: 4;  /* bit[4-7]  : Reserved. */
        unsigned int  awqos_max : 4;  /* bit[8-11] : Maximum AWQOS value */
        unsigned int  reserved_1: 4;  /* bit[12-15]: Reserved. */
        unsigned int  arqos_min : 4;  /* bit[16-19]: Minimum ARQOS value */
        unsigned int  reserved_2: 4;  /* bit[20-23]: Reserved. */
        unsigned int  arqos_max : 4;  /* bit[24-27]: Maximum ARQOS value */
        unsigned int  reserved_3: 4;  /* bit[28-31]: Reserved */
    } reg;
} SOC_CCI400_CCI_QRR_S4_UNION;
#endif
#define SOC_CCI400_CCI_QRR_S4_awqos_min_START  (0)
#define SOC_CCI400_CCI_QRR_S4_awqos_min_END    (3)
#define SOC_CCI400_CCI_QRR_S4_awqos_max_START  (8)
#define SOC_CCI400_CCI_QRR_S4_awqos_max_END    (11)
#define SOC_CCI400_CCI_QRR_S4_arqos_min_START  (16)
#define SOC_CCI400_CCI_QRR_S4_arqos_min_END    (19)
#define SOC_CCI400_CCI_QRR_S4_arqos_max_START  (24)
#define SOC_CCI400_CCI_QRR_S4_arqos_max_END    (27)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_ECCR_UNION
 结构说明  : CCI_ECCR 寄存器结构定义。地址偏移量:0x99004，初值:0x00000000，宽度:32
 寄存器说明: 事件cycle计数寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  event_cycle_cnt : 32; /* bit[0-31]: Reserved */
    } reg;
} SOC_CCI400_CCI_ECCR_UNION;
#endif
#define SOC_CCI400_CCI_ECCR_event_cycle_cnt_START  (0)
#define SOC_CCI400_CCI_ECCR_event_cycle_cnt_END    (31)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_CCR_UNION
 结构说明  : CCI_CCR 寄存器结构定义。地址偏移量:0x99008，初值:0x00000000，宽度:32
 寄存器说明: 计数控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cnt_en   : 1;  /* bit[0]   : Counter enable. The options are as follows:
                                                   0b0 Counter disabled.
                                                   0b1 Counter enabled. */
        unsigned int  reserved : 31; /* bit[1-31]: Reserved */
    } reg;
} SOC_CCI400_CCI_CCR_UNION;
#endif
#define SOC_CCI400_CCI_CCR_cnt_en_START    (0)
#define SOC_CCI400_CCI_CCR_cnt_en_END      (0)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_OFSR_UNION
 结构说明  : CCI_OFSR 寄存器结构定义。地址偏移量:0x9900C，初值:0x00000000，宽度:32
 寄存器说明: 计数溢出寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  overflow_flag : 1;  /* bit[0]   : Event counter and cycle counter overflow flag.(w1c) */
        unsigned int  reserved      : 31; /* bit[1-31]: Reserved */
    } reg;
} SOC_CCI400_CCI_OFSR_UNION;
#endif
#define SOC_CCI400_CCI_OFSR_overflow_flag_START  (0)
#define SOC_CCI400_CCI_OFSR_overflow_flag_END    (0)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_ESR_0_UNION
 结构说明  : CCI_ESR_0 寄存器结构定义。地址偏移量:0x9A000，初值:0x00000000，宽度:32
 寄存器说明: 事件选择寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  event_mon : 5;  /* bit[0-4] : Event code to define which event to monitor. See PMU event list on page 2-5. */
        unsigned int  int_mon   : 3;  /* bit[5-7] : Event code to define which interface to monitor. See PMU event list on page 2-5. */
        unsigned int  reserved  : 24; /* bit[8-31]: Reserved */
    } reg;
} SOC_CCI400_CCI_ESR_0_UNION;
#endif
#define SOC_CCI400_CCI_ESR_0_event_mon_START  (0)
#define SOC_CCI400_CCI_ESR_0_event_mon_END    (4)
#define SOC_CCI400_CCI_ESR_0_int_mon_START    (5)
#define SOC_CCI400_CCI_ESR_0_int_mon_END      (7)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_ECCR_0_UNION
 结构说明  : CCI_ECCR_0 寄存器结构定义。地址偏移量:0x9A004，初值:0x00000000，宽度:32
 寄存器说明: 事件cycle计数寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  event_cycle_cnt : 32; /* bit[0-31]: Reserved */
    } reg;
} SOC_CCI400_CCI_ECCR_0_UNION;
#endif
#define SOC_CCI400_CCI_ECCR_0_event_cycle_cnt_START  (0)
#define SOC_CCI400_CCI_ECCR_0_event_cycle_cnt_END    (31)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_CCR_0_UNION
 结构说明  : CCI_CCR_0 寄存器结构定义。地址偏移量:0x9A008，初值:0x00000000，宽度:32
 寄存器说明: 计数控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cnt_en   : 1;  /* bit[0]   : Counter enable. The options are as follows:
                                                   0b0 Counter disabled.
                                                   0b1 Counter enabled. */
        unsigned int  reserved : 31; /* bit[1-31]: Reserved */
    } reg;
} SOC_CCI400_CCI_CCR_0_UNION;
#endif
#define SOC_CCI400_CCI_CCR_0_cnt_en_START    (0)
#define SOC_CCI400_CCI_CCR_0_cnt_en_END      (0)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_OFSR_0_UNION
 结构说明  : CCI_OFSR_0 寄存器结构定义。地址偏移量:0x9A00C，初值:0x00000000，宽度:32
 寄存器说明: 计数溢出寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  overflow_flag : 1;  /* bit[0]   : Event counter and cycle counter overflow flag.(w1c) */
        unsigned int  reserved      : 31; /* bit[1-31]: Reserved */
    } reg;
} SOC_CCI400_CCI_OFSR_0_UNION;
#endif
#define SOC_CCI400_CCI_OFSR_0_overflow_flag_START  (0)
#define SOC_CCI400_CCI_OFSR_0_overflow_flag_END    (0)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_ESR_1_UNION
 结构说明  : CCI_ESR_1 寄存器结构定义。地址偏移量:0x9B000，初值:0x00000000，宽度:32
 寄存器说明: 事件选择寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  event_mon : 5;  /* bit[0-4] : Event code to define which event to monitor. See PMU event list on page 2-5. */
        unsigned int  int_mon   : 3;  /* bit[5-7] : Event code to define which interface to monitor. See PMU event list on page 2-5. */
        unsigned int  reserved  : 24; /* bit[8-31]: Reserved */
    } reg;
} SOC_CCI400_CCI_ESR_1_UNION;
#endif
#define SOC_CCI400_CCI_ESR_1_event_mon_START  (0)
#define SOC_CCI400_CCI_ESR_1_event_mon_END    (4)
#define SOC_CCI400_CCI_ESR_1_int_mon_START    (5)
#define SOC_CCI400_CCI_ESR_1_int_mon_END      (7)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_ECCR_1_UNION
 结构说明  : CCI_ECCR_1 寄存器结构定义。地址偏移量:0x9B004，初值:0x00000000，宽度:32
 寄存器说明: 事件cycle计数寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  event_cycle_cnt : 32; /* bit[0-31]: Reserved */
    } reg;
} SOC_CCI400_CCI_ECCR_1_UNION;
#endif
#define SOC_CCI400_CCI_ECCR_1_event_cycle_cnt_START  (0)
#define SOC_CCI400_CCI_ECCR_1_event_cycle_cnt_END    (31)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_CCR_1_UNION
 结构说明  : CCI_CCR_1 寄存器结构定义。地址偏移量:0x9B008，初值:0x00000000，宽度:32
 寄存器说明: 计数控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cnt_en   : 1;  /* bit[0]   : Counter enable. The options are as follows:
                                                   0b0 Counter disabled.
                                                   0b1 Counter enabled. */
        unsigned int  reserved : 31; /* bit[1-31]: Reserved */
    } reg;
} SOC_CCI400_CCI_CCR_1_UNION;
#endif
#define SOC_CCI400_CCI_CCR_1_cnt_en_START    (0)
#define SOC_CCI400_CCI_CCR_1_cnt_en_END      (0)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_OFSR_1_UNION
 结构说明  : CCI_OFSR_1 寄存器结构定义。地址偏移量:0x9B00C，初值:0x00000000，宽度:32
 寄存器说明: 计数溢出寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  overflow_flag : 1;  /* bit[0]   : Event counter and cycle counter overflow flag.(w1c) */
        unsigned int  reserved      : 31; /* bit[1-31]: Reserved */
    } reg;
} SOC_CCI400_CCI_OFSR_1_UNION;
#endif
#define SOC_CCI400_CCI_OFSR_1_overflow_flag_START  (0)
#define SOC_CCI400_CCI_OFSR_1_overflow_flag_END    (0)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_ESR_2_UNION
 结构说明  : CCI_ESR_2 寄存器结构定义。地址偏移量:0x9C000，初值:0x00000000，宽度:32
 寄存器说明: 事件选择寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  event_mon : 5;  /* bit[0-4] : Event code to define which event to monitor. See PMU event list on page 2-5. */
        unsigned int  int_mon   : 3;  /* bit[5-7] : Event code to define which interface to monitor. See PMU event list on page 2-5. */
        unsigned int  reserved  : 24; /* bit[8-31]: Reserved */
    } reg;
} SOC_CCI400_CCI_ESR_2_UNION;
#endif
#define SOC_CCI400_CCI_ESR_2_event_mon_START  (0)
#define SOC_CCI400_CCI_ESR_2_event_mon_END    (4)
#define SOC_CCI400_CCI_ESR_2_int_mon_START    (5)
#define SOC_CCI400_CCI_ESR_2_int_mon_END      (7)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_ECCR_2_UNION
 结构说明  : CCI_ECCR_2 寄存器结构定义。地址偏移量:0x9C004，初值:0x00000000，宽度:32
 寄存器说明: 事件cycle计数寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  event_cycle_cnt : 32; /* bit[0-31]: Reserved */
    } reg;
} SOC_CCI400_CCI_ECCR_2_UNION;
#endif
#define SOC_CCI400_CCI_ECCR_2_event_cycle_cnt_START  (0)
#define SOC_CCI400_CCI_ECCR_2_event_cycle_cnt_END    (31)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_CCR_2_UNION
 结构说明  : CCI_CCR_2 寄存器结构定义。地址偏移量:0x9C008，初值:0x00000000，宽度:32
 寄存器说明: 计数控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cnt_en   : 1;  /* bit[0]   : Counter enable. The options are as follows:
                                                   0b0 Counter disabled.
                                                   0b1 Counter enabled. */
        unsigned int  reserved : 31; /* bit[1-31]: Reserved */
    } reg;
} SOC_CCI400_CCI_CCR_2_UNION;
#endif
#define SOC_CCI400_CCI_CCR_2_cnt_en_START    (0)
#define SOC_CCI400_CCI_CCR_2_cnt_en_END      (0)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_OFSR_2_UNION
 结构说明  : CCI_OFSR_2 寄存器结构定义。地址偏移量:0x9C00C，初值:0x00000000，宽度:32
 寄存器说明: 计数溢出寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  overflow_flag : 1;  /* bit[0]   : Event counter and cycle counter overflow flag.(w1c) */
        unsigned int  reserved      : 31; /* bit[1-31]: Reserved */
    } reg;
} SOC_CCI400_CCI_OFSR_2_UNION;
#endif
#define SOC_CCI400_CCI_OFSR_2_overflow_flag_START  (0)
#define SOC_CCI400_CCI_OFSR_2_overflow_flag_END    (0)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_ESR_3_UNION
 结构说明  : CCI_ESR_3 寄存器结构定义。地址偏移量:0x9D000，初值:0x00000000，宽度:32
 寄存器说明: 事件选择寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  event_mon : 5;  /* bit[0-4] : Event code to define which event to monitor. See PMU event list on page 2-5. */
        unsigned int  int_mon   : 3;  /* bit[5-7] : Event code to define which interface to monitor. See PMU event list on page 2-5. */
        unsigned int  reserved  : 24; /* bit[8-31]: Reserved */
    } reg;
} SOC_CCI400_CCI_ESR_3_UNION;
#endif
#define SOC_CCI400_CCI_ESR_3_event_mon_START  (0)
#define SOC_CCI400_CCI_ESR_3_event_mon_END    (4)
#define SOC_CCI400_CCI_ESR_3_int_mon_START    (5)
#define SOC_CCI400_CCI_ESR_3_int_mon_END      (7)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_ECCR_3_UNION
 结构说明  : CCI_ECCR_3 寄存器结构定义。地址偏移量:0x9D004，初值:0x00000000，宽度:32
 寄存器说明: 事件cycle计数寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  event_cycle_cnt : 32; /* bit[0-31]: Reserved */
    } reg;
} SOC_CCI400_CCI_ECCR_3_UNION;
#endif
#define SOC_CCI400_CCI_ECCR_3_event_cycle_cnt_START  (0)
#define SOC_CCI400_CCI_ECCR_3_event_cycle_cnt_END    (31)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_CCR_3_UNION
 结构说明  : CCI_CCR_3 寄存器结构定义。地址偏移量:0x9D008，初值:0x00000000，宽度:32
 寄存器说明: 计数控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cnt_en   : 1;  /* bit[0]   : Counter enable. The options are as follows:
                                                   0b0 Counter disabled.
                                                   0b1 Counter enabled. */
        unsigned int  reserved : 31; /* bit[1-31]: Reserved */
    } reg;
} SOC_CCI400_CCI_CCR_3_UNION;
#endif
#define SOC_CCI400_CCI_CCR_3_cnt_en_START    (0)
#define SOC_CCI400_CCI_CCR_3_cnt_en_END      (0)


/*****************************************************************************
 结构名    : SOC_CCI400_CCI_OFSR_3_UNION
 结构说明  : CCI_OFSR_3 寄存器结构定义。地址偏移量:0x9D00C，初值:0x00000000，宽度:32
 寄存器说明: 计数溢出寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  overflow_flag : 1;  /* bit[0]   : Event counter and cycle counter overflow flag.(w1c) */
        unsigned int  reserved      : 31; /* bit[1-31]: Reserved */
    } reg;
} SOC_CCI400_CCI_OFSR_3_UNION;
#endif
#define SOC_CCI400_CCI_OFSR_3_overflow_flag_START  (0)
#define SOC_CCI400_CCI_OFSR_3_overflow_flag_END    (0)






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

#endif /* end of soc_cci400_interface.h */
