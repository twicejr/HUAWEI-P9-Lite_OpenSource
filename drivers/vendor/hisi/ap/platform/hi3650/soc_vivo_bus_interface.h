/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_vivo_bus_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:23:25
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_VIVO_BUS.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_VIVO_BUS_INTERFACE_H__
#define __SOC_VIVO_BUS_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/2) NOC_DSS
 ****************************************************************************/
/* 寄存器说明：
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_RD_QOS_ID_COREID_UNION */
#define SOC_VIVO_BUS_DSS0_RD_QOS_ID_COREID_ADDR(base) ((base) + (0x0000))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_RD_QOS_ID_REVISIONID_UNION */
#define SOC_VIVO_BUS_DSS0_RD_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0004))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_RD_QOS_PRIORITY_UNION */
#define SOC_VIVO_BUS_DSS0_RD_QOS_PRIORITY_ADDR(base)  ((base) + (0x0008))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_RD_QOS_MODE_UNION */
#define SOC_VIVO_BUS_DSS0_RD_QOS_MODE_ADDR(base)      ((base) + (0x000C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_RD_QOS_BANDWIDTH_UNION */
#define SOC_VIVO_BUS_DSS0_RD_QOS_BANDWIDTH_ADDR(base) ((base) + (0x0010))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_RD_QOS_SATURATION_UNION */
#define SOC_VIVO_BUS_DSS0_RD_QOS_SATURATION_ADDR(base) ((base) + (0x0014))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_RD_QOS_EXTCONTROL_UNION */
#define SOC_VIVO_BUS_DSS0_RD_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0018))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_QOS_ID_COREID_UNION */
#define SOC_VIVO_BUS_DSS0_WR_QOS_ID_COREID_ADDR(base) ((base) + (0x0080))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_QOS_ID_REVISIONID_UNION */
#define SOC_VIVO_BUS_DSS0_WR_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0084))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_QOS_PRIORITY_UNION */
#define SOC_VIVO_BUS_DSS0_WR_QOS_PRIORITY_ADDR(base)  ((base) + (0x0088))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_QOS_MODE_UNION */
#define SOC_VIVO_BUS_DSS0_WR_QOS_MODE_ADDR(base)      ((base) + (0x008C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_QOS_BANDWIDTH_UNION */
#define SOC_VIVO_BUS_DSS0_WR_QOS_BANDWIDTH_ADDR(base) ((base) + (0x0090))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_QOS_SATURATION_UNION */
#define SOC_VIVO_BUS_DSS0_WR_QOS_SATURATION_ADDR(base) ((base) + (0x0094))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_QOS_EXTCONTROL_UNION */
#define SOC_VIVO_BUS_DSS0_WR_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0098))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_RD_QOS_ID_COREID_UNION */
#define SOC_VIVO_BUS_DSS1_RD_QOS_ID_COREID_ADDR(base) ((base) + (0x0100))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_RD_QOS_ID_REVISIONID_UNION */
#define SOC_VIVO_BUS_DSS1_RD_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0104))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_RD_QOS_PRIORITY_UNION */
#define SOC_VIVO_BUS_DSS1_RD_QOS_PRIORITY_ADDR(base)  ((base) + (0x0108))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_RD_QOS_MODE_UNION */
#define SOC_VIVO_BUS_DSS1_RD_QOS_MODE_ADDR(base)      ((base) + (0x010C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_RD_QOS_BANDWIDTH_UNION */
#define SOC_VIVO_BUS_DSS1_RD_QOS_BANDWIDTH_ADDR(base) ((base) + (0x0110))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_RD_QOS_SATURATION_UNION */
#define SOC_VIVO_BUS_DSS1_RD_QOS_SATURATION_ADDR(base) ((base) + (0x0114))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_RD_QOS_EXTCONTROL_UNION */
#define SOC_VIVO_BUS_DSS1_RD_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0118))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_QOS_ID_COREID_UNION */
#define SOC_VIVO_BUS_DSS1_WR_QOS_ID_COREID_ADDR(base) ((base) + (0x0180))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_QOS_ID_REVISIONID_UNION */
#define SOC_VIVO_BUS_DSS1_WR_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0184))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_QOS_PRIORITY_UNION */
#define SOC_VIVO_BUS_DSS1_WR_QOS_PRIORITY_ADDR(base)  ((base) + (0x0188))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_QOS_MODE_UNION */
#define SOC_VIVO_BUS_DSS1_WR_QOS_MODE_ADDR(base)      ((base) + (0x018C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_QOS_BANDWIDTH_UNION */
#define SOC_VIVO_BUS_DSS1_WR_QOS_BANDWIDTH_ADDR(base) ((base) + (0x0190))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_QOS_SATURATION_UNION */
#define SOC_VIVO_BUS_DSS1_WR_QOS_SATURATION_ADDR(base) ((base) + (0x0194))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_QOS_EXTCONTROL_UNION */
#define SOC_VIVO_BUS_DSS1_WR_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0198))

/* 寄存器说明：VIVOBUS Err probe域ID
   位域定义UNION结构:  SOC_VIVO_BUS_VIVOBUS_ERR_ID_COREID_UNION */
#define SOC_VIVO_BUS_VIVOBUS_ERR_ID_COREID_ADDR(base) ((base) + (0x1C00))

/* 寄存器说明：总线代码版本寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_VIVOBUS_ERR_ID_REVISIONID_UNION */
#define SOC_VIVO_BUS_VIVOBUS_ERR_ID_REVISIONID_ADDR(base) ((base) + (0x1C04))

/* 寄存器说明：VIVOBUS Err probe使能
   位域定义UNION结构:  SOC_VIVO_BUS_VIVOBUS_FAULTEN_UNION */
#define SOC_VIVO_BUS_VIVOBUS_FAULTEN_ADDR(base)       ((base) + (0x1C08))

/* 寄存器说明：Error log有效指示寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_VIVOBUS_ERRVLD_UNION */
#define SOC_VIVO_BUS_VIVOBUS_ERRVLD_ADDR(base)        ((base) + (0x1C0C))

/* 寄存器说明：中断清除寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_VIVOBUS_ERRCLR_UNION */
#define SOC_VIVO_BUS_VIVOBUS_ERRCLR_ADDR(base)        ((base) + (0x1C10))

/* 寄存器说明：Error log0
   位域定义UNION结构:  SOC_VIVO_BUS_VIVOBUS_ERRLOG0_UNION */
#define SOC_VIVO_BUS_VIVOBUS_ERRLOG0_ADDR(base)       ((base) + (0x1C14))

/* 寄存器说明：Error log1
   位域定义UNION结构:  SOC_VIVO_BUS_VIVOBUS_ERRLOG1_UNION */
#define SOC_VIVO_BUS_VIVOBUS_ERRLOG1_ADDR(base)       ((base) + (0x1C18))

/* 寄存器说明：Error log3
   位域定义UNION结构:  SOC_VIVO_BUS_VIVOBUS_ERRLOG3_UNION */
#define SOC_VIVO_BUS_VIVOBUS_ERRLOG3_ADDR(base)       ((base) + (0x1C20))

/* 寄存器说明：Error log5
   位域定义UNION结构:  SOC_VIVO_BUS_VIVOBUS_ERRLOG5_UNION */
#define SOC_VIVO_BUS_VIVOBUS_ERRLOG5_ADDR(base)       ((base) + (0x1C28))

/* 寄存器说明：Error log7
   位域定义UNION结构:  SOC_VIVO_BUS_VIVOBUS_ERRLOG7_UNION */
#define SOC_VIVO_BUS_VIVOBUS_ERRLOG7_ADDR(base)       ((base) + (0x1C30))

/* 寄存器说明：DSS0_RD TransactionStatFilter域ID
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_RD_TRANS_F_ID_COREID_UNION */
#define SOC_VIVO_BUS_DSS0_RD_TRANS_F_ID_COREID_ADDR(base) ((base) + (0x8000))

/* 寄存器说明：代码版本
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_RD_TRANS_F_ID_REVISIONID_UNION */
#define SOC_VIVO_BUS_DSS0_RD_TRANS_F_ID_REVISIONID_ADDR(base) ((base) + (0x8004))

/* 寄存器说明：DSS0_RD Transaction Probe的Filter工作模式配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_RD_TRANS_F_MODE_UNION */
#define SOC_VIVO_BUS_DSS0_RD_TRANS_F_MODE_ADDR(base)  ((base) + (0x8008))

/* 寄存器说明：地址过滤基地址
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_RD_TRANS_F_ADDRBASE_LOW_UNION */
#define SOC_VIVO_BUS_DSS0_RD_TRANS_F_ADDRBASE_LOW_ADDR(base) ((base) + (0x800C))

/* 寄存器说明：地址过滤窗口
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_RD_TRANS_F_ADDRWINDOWSIZE_UNION */
#define SOC_VIVO_BUS_DSS0_RD_TRANS_F_ADDRWINDOWSIZE_ADDR(base) ((base) + (0x8014))

/* 寄存器说明：DSS0_RD的Transaction Probe的Opcode过滤条件
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_RD_TRANS_F_OPCODE_UNION */
#define SOC_VIVO_BUS_DSS0_RD_TRANS_F_OPCODE_ADDR(base) ((base) + (0x8020))

/* 寄存器说明：DSS0_RD的Transaction Probe的User过滤条件
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_RD_TRANS_F_USERBASE_UNION */
#define SOC_VIVO_BUS_DSS0_RD_TRANS_F_USERBASE_ADDR(base) ((base) + (0x8024))

/* 寄存器说明：DSS0_RD的Transaction Probe的User过滤条件Mask
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_RD_TRANS_F_USERMASK_UNION */
#define SOC_VIVO_BUS_DSS0_RD_TRANS_F_USERMASK_ADDR(base) ((base) + (0x8028))

/* 寄存器说明：DSS0_RD的Transaction Probe的安全过滤条件
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_RD_TRANS_F_SECURITYBASE_UNION */
#define SOC_VIVO_BUS_DSS0_RD_TRANS_F_SECURITYBASE_ADDR(base) ((base) + (0x802C))

/* 寄存器说明：DSS0_RD的Transaction Probe的安全过滤条件Mask
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_RD_TRANS_F_SECURITYMASK_UNION */
#define SOC_VIVO_BUS_DSS0_RD_TRANS_F_SECURITYMASK_ADDR(base) ((base) + (0x8030))

/* 寄存器说明：DSS0_RD TransactionStatProfilter域ID
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_RD_TRANS_P_ID_COREID_UNION */
#define SOC_VIVO_BUS_DSS0_RD_TRANS_P_ID_COREID_ADDR(base) ((base) + (0x8080))

/* 寄存器说明：代码版本
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_RD_TRANS_P_ID_REVISIONID_UNION */
#define SOC_VIVO_BUS_DSS0_RD_TRANS_P_ID_REVISIONID_ADDR(base) ((base) + (0x8084))

/* 寄存器说明：transaction Probe的counter使能配置
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_RD_TRANS_P_EN_UNION */
#define SOC_VIVO_BUS_DSS0_RD_TRANS_P_EN_ADDR(base)    ((base) + (0x8088))

/* 寄存器说明：DSS0_RD Transaction Probe的工作模式配置
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_RD_TRANS_P_MODE_UNION */
#define SOC_VIVO_BUS_DSS0_RD_TRANS_P_MODE_ADDR(base)  ((base) + (0x808C))

/* 寄存器说明：统计计数器溢出状态
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_RD_TRANS_P_OVERFLOWSTATUS_UNION */
#define SOC_VIVO_BUS_DSS0_RD_TRANS_P_OVERFLOWSTATUS_ADDR(base) ((base) + (0x80EC))

/* 寄存器说明：统计计数器溢出状态清零
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_RD_TRANS_P_OVERFLOWRESET_UNION */
#define SOC_VIVO_BUS_DSS0_RD_TRANS_P_OVERFLOWRESET_ADDR(base) ((base) + (0x80F0))

/* 寄存器说明：outstanding统计技术工作模式配置
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_RD_TRANS_P_PENDINGEVENTMODE_UNION */
#define SOC_VIVO_BUS_DSS0_RD_TRANS_P_PENDINGEVENTMODE_ADDR(base) ((base) + (0x80F4))

/* 寄存器说明：latency统计系数配置
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_RD_TRANS_P_PRESCALER_UNION */
#define SOC_VIVO_BUS_DSS0_RD_TRANS_P_PRESCALER_ADDR(base) ((base) + (0x80F8))

/* 寄存器说明：DSS0_RD Transaction probe域ID
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_RD_TRANS_M_ID_COREID_UNION */
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_ID_COREID_ADDR(base) ((base) + (0x8400))

/* 寄存器说明：总线代码版本寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_RD_TRANS_M_ID_REVISIONID_UNION */
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_ID_REVISIONID_ADDR(base) ((base) + (0x8404))

/* 寄存器说明：Transaction Probe全局控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_RD_TRANS_M_MAINCTL_UNION */
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_MAINCTL_ADDR(base) ((base) + (0x8408))

/* 寄存器说明：Packet Probe使能寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_RD_TRANS_M_CFGCTL_UNION */
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_CFGCTL_ADDR(base) ((base) + (0x840C))

/* 寄存器说明：统计周期配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_RD_TRANS_M_STATPERIOD_UNION */
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_STATPERIOD_ADDR(base) ((base) + (0x8424))

/* 寄存器说明：手动带宽统计计时开始使能
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_RD_TRANS_M_STATGO_UNION */
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_STATGO_ADDR(base) ((base) + (0x8428))

/* 寄存器说明：统计计数最小告警阈值
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_RD_TRANS_M_STATALARMMIN_UNION */
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_STATALARMMIN_ADDR(base) ((base) + (0x842C))

/* 寄存器说明：统计计数器最大告警阈值
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_RD_TRANS_M_STATALARMMAX_UNION */
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_STATALARMMAX_ADDR(base) ((base) + (0x8430))

/* 寄存器说明：告警状态寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_RD_TRANS_M_STATALARMSTATUS_UNION */
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_STATALARMSTATUS_ADDR(base) ((base) + (0x8434))

/* 寄存器说明：告警状态清除寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_RD_TRANS_M_STATALARMCLR_UNION */
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_STATALARMCLR_ADDR(base) ((base) + (0x8438))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_0_SRC_UNION */
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_0_SRC_ADDR(base) ((base) + (0x8538))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_0_ALARMMODE_UNION */
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_0_ALARMMODE_ADDR(base) ((base) + (0x853C))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_0_VAL_UNION */
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_0_VAL_ADDR(base) ((base) + (0x8540))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_1_SRC_UNION */
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_1_SRC_ADDR(base) ((base) + (0x854C))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_1_ALARMMODE_UNION */
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_1_ALARMMODE_ADDR(base) ((base) + (0x8550))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_1_VAL_UNION */
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_1_VAL_ADDR(base) ((base) + (0x8554))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_2_SRC_UNION */
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_2_SRC_ADDR(base) ((base) + (0x8560))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_2_ALARMMODE_UNION */
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_2_ALARMMODE_ADDR(base) ((base) + (0x8564))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_2_VAL_UNION */
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_2_VAL_ADDR(base) ((base) + (0x8568))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_3_SRC_UNION */
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_3_SRC_ADDR(base) ((base) + (0x8574))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_3_ALARMMODE_UNION */
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_3_ALARMMODE_ADDR(base) ((base) + (0x8578))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_3_VAL_UNION */
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_3_VAL_ADDR(base) ((base) + (0x857C))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_4_SRC_UNION */
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_4_SRC_ADDR(base) ((base) + (0x8588))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_4_ALARMMODE_UNION */
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_4_ALARMMODE_ADDR(base) ((base) + (0x858C))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_4_VAL_UNION */
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_4_VAL_ADDR(base) ((base) + (0x8590))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_5_SRC_UNION */
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_5_SRC_ADDR(base) ((base) + (0x859C))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_5_ALARMMODE_UNION */
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_5_ALARMMODE_ADDR(base) ((base) + (0x85A0))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_5_VAL_UNION */
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_5_VAL_ADDR(base) ((base) + (0x85A4))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_6_SRC_UNION */
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_6_SRC_ADDR(base) ((base) + (0x85B0))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_6_ALARMMODE_UNION */
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_6_ALARMMODE_ADDR(base) ((base) + (0x85B4))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_6_VAL_UNION */
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_6_VAL_ADDR(base) ((base) + (0x85B8))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_7_SRC_UNION */
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_7_SRC_ADDR(base) ((base) + (0x85C4))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_7_ALARMMODE_UNION */
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_7_ALARMMODE_ADDR(base) ((base) + (0x85C8))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_7_VAL_UNION */
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_7_VAL_ADDR(base) ((base) + (0x85CC))

/* 寄存器说明：DSS0_WR TransactionStatFilter域ID
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_TRANS_F_ID_COREID_UNION */
#define SOC_VIVO_BUS_DSS0_WR_TRANS_F_ID_COREID_ADDR(base) ((base) + (0x9000))

/* 寄存器说明：代码版本
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_TRANS_F_ID_REVISIONID_UNION */
#define SOC_VIVO_BUS_DSS0_WR_TRANS_F_ID_REVISIONID_ADDR(base) ((base) + (0x9004))

/* 寄存器说明：DSS0_WR Transaction Probe的Filter工作模式配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_TRANS_F_MODE_UNION */
#define SOC_VIVO_BUS_DSS0_WR_TRANS_F_MODE_ADDR(base)  ((base) + (0x9008))

/* 寄存器说明：地址过滤基地址
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_TRANS_F_ADDRBASE_LOW_UNION */
#define SOC_VIVO_BUS_DSS0_WR_TRANS_F_ADDRBASE_LOW_ADDR(base) ((base) + (0x900C))

/* 寄存器说明：地址过滤基地址
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_TRANS_F_ADDRBASE_HIGH_UNION */
#define SOC_VIVO_BUS_DSS0_WR_TRANS_F_ADDRBASE_HIGH_ADDR(base) ((base) + (0x9010))

/* 寄存器说明：地址过滤窗口
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_TRANS_F_ADDRWINDOWSIZE_UNION */
#define SOC_VIVO_BUS_DSS0_WR_TRANS_F_ADDRWINDOWSIZE_ADDR(base) ((base) + (0x9014))

/* 寄存器说明：DSS0_WR的Transaction Probe的Opcode过滤条件
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_TRANS_F_OPCODE_UNION */
#define SOC_VIVO_BUS_DSS0_WR_TRANS_F_OPCODE_ADDR(base) ((base) + (0x9020))

/* 寄存器说明：DSS0_WR的Transaction Probe的User过滤条件
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_TRANS_F_USERBASE_UNION */
#define SOC_VIVO_BUS_DSS0_WR_TRANS_F_USERBASE_ADDR(base) ((base) + (0x9024))

/* 寄存器说明：DSS0_WR的Transaction Probe的User过滤条件Mask
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_TRANS_F_USERMASK_UNION */
#define SOC_VIVO_BUS_DSS0_WR_TRANS_F_USERMASK_ADDR(base) ((base) + (0x9028))

/* 寄存器说明：DSS0_WR的Transaction Probe的安全过滤条件
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_TRANS_F_SECURITYBASE_UNION */
#define SOC_VIVO_BUS_DSS0_WR_TRANS_F_SECURITYBASE_ADDR(base) ((base) + (0x902C))

/* 寄存器说明：DSS0_WR的Transaction Probe的安全过滤条件Mask
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_TRANS_F_SECURITYMASK_UNION */
#define SOC_VIVO_BUS_DSS0_WR_TRANS_F_SECURITYMASK_ADDR(base) ((base) + (0x9030))

/* 寄存器说明：DSS0_WR TransactionStatProfilter域ID
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_TRANS_P_ID_COREID_UNION */
#define SOC_VIVO_BUS_DSS0_WR_TRANS_P_ID_COREID_ADDR(base) ((base) + (0x9080))

/* 寄存器说明：代码版本
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_TRANS_P_ID_REVISIONID_UNION */
#define SOC_VIVO_BUS_DSS0_WR_TRANS_P_ID_REVISIONID_ADDR(base) ((base) + (0x9084))

/* 寄存器说明：transaction Probe的counter使能配置
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_TRANS_P_EN_UNION */
#define SOC_VIVO_BUS_DSS0_WR_TRANS_P_EN_ADDR(base)    ((base) + (0x9088))

/* 寄存器说明：DSS0_WR Transaction Probe的工作模式配置
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_TRANS_P_MODE_UNION */
#define SOC_VIVO_BUS_DSS0_WR_TRANS_P_MODE_ADDR(base)  ((base) + (0x908C))

/* 寄存器说明：DSS0_WR Transaction Probe的bin_0配置
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_TRANS_P_THRESHOLDS_0_0_UNION */
#define SOC_VIVO_BUS_DSS0_WR_TRANS_P_THRESHOLDS_0_0_ADDR(base) ((base) + (0x90AC))

/* 寄存器说明：DSS0_WR Transaction Probe的bin_0配置
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_TRANS_P_THRESHOLDS_0_1_UNION */
#define SOC_VIVO_BUS_DSS0_WR_TRANS_P_THRESHOLDS_0_1_ADDR(base) ((base) + (0x90B0))

/* 寄存器说明：DSS0_WR Transaction Probe的bin_0配置
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_TRANS_P_THRESHOLDS_0_2_UNION */
#define SOC_VIVO_BUS_DSS0_WR_TRANS_P_THRESHOLDS_0_2_ADDR(base) ((base) + (0x90B4))

/* 寄存器说明：DSS0_WR Transaction Probe的bin_0配置
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_TRANS_P_THRESHOLDS_0_3_UNION */
#define SOC_VIVO_BUS_DSS0_WR_TRANS_P_THRESHOLDS_0_3_ADDR(base) ((base) + (0x90B8))

/* 寄存器说明：统计计数器溢出状态
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_TRANS_P_OVERFLOWSTATUS_UNION */
#define SOC_VIVO_BUS_DSS0_WR_TRANS_P_OVERFLOWSTATUS_ADDR(base) ((base) + (0x90EC))

/* 寄存器说明：统计计数器溢出状态清零
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_TRANS_P_OVERFLOWRESET_UNION */
#define SOC_VIVO_BUS_DSS0_WR_TRANS_P_OVERFLOWRESET_ADDR(base) ((base) + (0x90F0))

/* 寄存器说明：outstanding统计技术工作模式配置
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_TRANS_P_PENDINGEVENTMODE_UNION */
#define SOC_VIVO_BUS_DSS0_WR_TRANS_P_PENDINGEVENTMODE_ADDR(base) ((base) + (0x90F4))

/* 寄存器说明：latency统计系数配置
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_TRANS_P_PRESCALER_UNION */
#define SOC_VIVO_BUS_DSS0_WR_TRANS_P_PRESCALER_ADDR(base) ((base) + (0x90F8))

/* 寄存器说明：DSS0_WR Transaction probe域ID
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_TRANS_M_ID_COREID_UNION */
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_ID_COREID_ADDR(base) ((base) + (0x9400))

/* 寄存器说明：总线代码版本寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_TRANS_M_ID_REVISIONID_UNION */
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_ID_REVISIONID_ADDR(base) ((base) + (0x9404))

/* 寄存器说明：Transaction Probe全局控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_TRANS_M_MAINCTL_UNION */
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_MAINCTL_ADDR(base) ((base) + (0x9408))

/* 寄存器说明：Packet Probe使能寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_TRANS_M_CFGCTL_UNION */
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_CFGCTL_ADDR(base) ((base) + (0x940C))

/* 寄存器说明：统计周期配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_TRANS_M_STATPERIOD_UNION */
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_STATPERIOD_ADDR(base) ((base) + (0x9424))

/* 寄存器说明：手动带宽统计计时开始使能
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_TRANS_M_STATGO_UNION */
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_STATGO_ADDR(base) ((base) + (0x9428))

/* 寄存器说明：统计计数最小告警阈值
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_TRANS_M_STATALARMMIN_UNION */
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_STATALARMMIN_ADDR(base) ((base) + (0x942C))

/* 寄存器说明：统计计数器最大告警阈值
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_TRANS_M_STATALARMMAX_UNION */
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_STATALARMMAX_ADDR(base) ((base) + (0x9430))

/* 寄存器说明：告警状态寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_TRANS_M_STATALARMSTATUS_UNION */
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_STATALARMSTATUS_ADDR(base) ((base) + (0x9434))

/* 寄存器说明：告警状态清除寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_TRANS_M_STATALARMCLR_UNION */
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_STATALARMCLR_ADDR(base) ((base) + (0x9438))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_0_SRC_UNION */
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_0_SRC_ADDR(base) ((base) + (0x9538))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_0_ALARMMODE_UNION */
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_0_ALARMMODE_ADDR(base) ((base) + (0x953C))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_0_VAL_UNION */
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_0_VAL_ADDR(base) ((base) + (0x9540))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_1_SRC_UNION */
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_1_SRC_ADDR(base) ((base) + (0x954C))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_1_ALARMMODE_UNION */
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_1_ALARMMODE_ADDR(base) ((base) + (0x9550))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_1_VAL_UNION */
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_1_VAL_ADDR(base) ((base) + (0x9554))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_2_SRC_UNION */
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_2_SRC_ADDR(base) ((base) + (0x9560))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_2_ALARMMODE_UNION */
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_2_ALARMMODE_ADDR(base) ((base) + (0x9564))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_2_VAL_UNION */
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_2_VAL_ADDR(base) ((base) + (0x9568))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_3_SRC_UNION */
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_3_SRC_ADDR(base) ((base) + (0x9574))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_3_ALARMMODE_UNION */
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_3_ALARMMODE_ADDR(base) ((base) + (0x9578))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_3_VAL_UNION */
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_3_VAL_ADDR(base) ((base) + (0x957C))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_4_SRC_UNION */
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_4_SRC_ADDR(base) ((base) + (0x9588))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_4_ALARMMODE_UNION */
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_4_ALARMMODE_ADDR(base) ((base) + (0x958C))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_4_VAL_UNION */
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_4_VAL_ADDR(base) ((base) + (0x9590))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_5_SRC_UNION */
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_5_SRC_ADDR(base) ((base) + (0x959C))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_5_ALARMMODE_UNION */
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_5_ALARMMODE_ADDR(base) ((base) + (0x95A0))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_5_VAL_UNION */
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_5_VAL_ADDR(base) ((base) + (0x95A4))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_6_SRC_UNION */
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_6_SRC_ADDR(base) ((base) + (0x95B0))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_6_ALARMMODE_UNION */
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_6_ALARMMODE_ADDR(base) ((base) + (0x95B4))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_6_VAL_UNION */
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_6_VAL_ADDR(base) ((base) + (0x95B8))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_7_SRC_UNION */
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_7_SRC_ADDR(base) ((base) + (0x95C4))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_7_ALARMMODE_UNION */
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_7_ALARMMODE_ADDR(base) ((base) + (0x95C8))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_7_VAL_UNION */
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_7_VAL_ADDR(base) ((base) + (0x95CC))

/* 寄存器说明：DSS1_RD TransactionStatFilter域ID
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_RD_TRANS_F_ID_COREID_UNION */
#define SOC_VIVO_BUS_DSS1_RD_TRANS_F_ID_COREID_ADDR(base) ((base) + (0xA000))

/* 寄存器说明：代码版本
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_RD_TRANS_F_ID_REVISIONID_UNION */
#define SOC_VIVO_BUS_DSS1_RD_TRANS_F_ID_REVISIONID_ADDR(base) ((base) + (0xA004))

/* 寄存器说明：DSS1_RD Transaction Probe的Filter工作模式配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_RD_TRANS_F_MODE_UNION */
#define SOC_VIVO_BUS_DSS1_RD_TRANS_F_MODE_ADDR(base)  ((base) + (0xA008))

/* 寄存器说明：地址过滤基地址
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_RD_TRANS_F_ADDRBASE_LOW_UNION */
#define SOC_VIVO_BUS_DSS1_RD_TRANS_F_ADDRBASE_LOW_ADDR(base) ((base) + (0xA00C))

/* 寄存器说明：地址过滤窗口
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_RD_TRANS_F_ADDRWINDOWSIZE_UNION */
#define SOC_VIVO_BUS_DSS1_RD_TRANS_F_ADDRWINDOWSIZE_ADDR(base) ((base) + (0xA014))

/* 寄存器说明：DSS1_RD的Transaction Probe的Opcode过滤条件
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_RD_TRANS_F_OPCODE_UNION */
#define SOC_VIVO_BUS_DSS1_RD_TRANS_F_OPCODE_ADDR(base) ((base) + (0xA020))

/* 寄存器说明：DSS1_RD的Transaction Probe的User过滤条件
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_RD_TRANS_F_USERBASE_UNION */
#define SOC_VIVO_BUS_DSS1_RD_TRANS_F_USERBASE_ADDR(base) ((base) + (0xA024))

/* 寄存器说明：DSS1_RD的Transaction Probe的User过滤条件Mask
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_RD_TRANS_F_USERMASK_UNION */
#define SOC_VIVO_BUS_DSS1_RD_TRANS_F_USERMASK_ADDR(base) ((base) + (0xA028))

/* 寄存器说明：DSS1_RD的Transaction Probe的安全过滤条件
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_RD_TRANS_F_SECURITYBASE_UNION */
#define SOC_VIVO_BUS_DSS1_RD_TRANS_F_SECURITYBASE_ADDR(base) ((base) + (0xA02C))

/* 寄存器说明：DSS1_RD的Transaction Probe的安全过滤条件Mask
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_RD_TRANS_F_SECURITYMASK_UNION */
#define SOC_VIVO_BUS_DSS1_RD_TRANS_F_SECURITYMASK_ADDR(base) ((base) + (0xA030))

/* 寄存器说明：DSS1_RD TransactionStatProfilter域ID
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_RD_TRANS_P_ID_COREID_UNION */
#define SOC_VIVO_BUS_DSS1_RD_TRANS_P_ID_COREID_ADDR(base) ((base) + (0xA080))

/* 寄存器说明：代码版本
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_RD_TRANS_P_ID_REVISIONID_UNION */
#define SOC_VIVO_BUS_DSS1_RD_TRANS_P_ID_REVISIONID_ADDR(base) ((base) + (0xA084))

/* 寄存器说明：transaction Probe的counter使能配置
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_RD_TRANS_P_EN_UNION */
#define SOC_VIVO_BUS_DSS1_RD_TRANS_P_EN_ADDR(base)    ((base) + (0xA088))

/* 寄存器说明：DSS1_RD Transaction Probe的工作模式配置
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_RD_TRANS_P_MODE_UNION */
#define SOC_VIVO_BUS_DSS1_RD_TRANS_P_MODE_ADDR(base)  ((base) + (0xA08C))

/* 寄存器说明：统计计数器溢出状态
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_RD_TRANS_P_OVERFLOWSTATUS_UNION */
#define SOC_VIVO_BUS_DSS1_RD_TRANS_P_OVERFLOWSTATUS_ADDR(base) ((base) + (0xA0EC))

/* 寄存器说明：统计计数器溢出状态清零
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_RD_TRANS_P_OVERFLOWRESET_UNION */
#define SOC_VIVO_BUS_DSS1_RD_TRANS_P_OVERFLOWRESET_ADDR(base) ((base) + (0xA0F0))

/* 寄存器说明：outstanding统计技术工作模式配置
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_RD_TRANS_P_PENDINGEVENTMODE_UNION */
#define SOC_VIVO_BUS_DSS1_RD_TRANS_P_PENDINGEVENTMODE_ADDR(base) ((base) + (0xA0F4))

/* 寄存器说明：latency统计系数配置
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_RD_TRANS_P_PRESCALER_UNION */
#define SOC_VIVO_BUS_DSS1_RD_TRANS_P_PRESCALER_ADDR(base) ((base) + (0xA0F8))

/* 寄存器说明：DSS1_RD Transaction probe域ID
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_RD_TRANS_M_ID_COREID_UNION */
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_ID_COREID_ADDR(base) ((base) + (0xA400))

/* 寄存器说明：总线代码版本寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_RD_TRANS_M_ID_REVISIONID_UNION */
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_ID_REVISIONID_ADDR(base) ((base) + (0xA404))

/* 寄存器说明：Transaction Probe全局控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_RD_TRANS_M_MAINCTL_UNION */
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_MAINCTL_ADDR(base) ((base) + (0xA408))

/* 寄存器说明：Packet Probe使能寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_RD_TRANS_M_CFGCTL_UNION */
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_CFGCTL_ADDR(base) ((base) + (0xA40C))

/* 寄存器说明：统计周期配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_RD_TRANS_M_STATPERIOD_UNION */
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_STATPERIOD_ADDR(base) ((base) + (0xA424))

/* 寄存器说明：手动带宽统计计时开始使能
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_RD_TRANS_M_STATGO_UNION */
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_STATGO_ADDR(base) ((base) + (0xA428))

/* 寄存器说明：统计计数最小告警阈值
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_RD_TRANS_M_STATALARMMIN_UNION */
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_STATALARMMIN_ADDR(base) ((base) + (0xA42C))

/* 寄存器说明：统计计数器最大告警阈值
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_RD_TRANS_M_STATALARMMAX_UNION */
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_STATALARMMAX_ADDR(base) ((base) + (0xA430))

/* 寄存器说明：告警状态寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_RD_TRANS_M_STATALARMSTATUS_UNION */
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_STATALARMSTATUS_ADDR(base) ((base) + (0xA434))

/* 寄存器说明：告警状态清除寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_RD_TRANS_M_STATALARMCLR_UNION */
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_STATALARMCLR_ADDR(base) ((base) + (0xA438))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_0_SRC_UNION */
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_0_SRC_ADDR(base) ((base) + (0xA538))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_0_ALARMMODE_UNION */
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_0_ALARMMODE_ADDR(base) ((base) + (0xA53C))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_0_VAL_UNION */
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_0_VAL_ADDR(base) ((base) + (0xA540))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_1_SRC_UNION */
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_1_SRC_ADDR(base) ((base) + (0xA54C))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_1_ALARMMODE_UNION */
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_1_ALARMMODE_ADDR(base) ((base) + (0xA550))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_1_VAL_UNION */
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_1_VAL_ADDR(base) ((base) + (0xA554))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_2_SRC_UNION */
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_2_SRC_ADDR(base) ((base) + (0xA560))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_2_ALARMMODE_UNION */
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_2_ALARMMODE_ADDR(base) ((base) + (0xA564))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_2_VAL_UNION */
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_2_VAL_ADDR(base) ((base) + (0xA568))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_3_SRC_UNION */
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_3_SRC_ADDR(base) ((base) + (0xA574))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_3_ALARMMODE_UNION */
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_3_ALARMMODE_ADDR(base) ((base) + (0xA578))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_3_VAL_UNION */
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_3_VAL_ADDR(base) ((base) + (0xA57C))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_4_SRC_UNION */
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_4_SRC_ADDR(base) ((base) + (0xA588))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_4_ALARMMODE_UNION */
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_4_ALARMMODE_ADDR(base) ((base) + (0xA58C))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_4_VAL_UNION */
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_4_VAL_ADDR(base) ((base) + (0xA590))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_5_SRC_UNION */
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_5_SRC_ADDR(base) ((base) + (0xA59C))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_5_ALARMMODE_UNION */
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_5_ALARMMODE_ADDR(base) ((base) + (0xA5A0))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_5_VAL_UNION */
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_5_VAL_ADDR(base) ((base) + (0xA5A4))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_6_SRC_UNION */
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_6_SRC_ADDR(base) ((base) + (0xA5B0))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_6_ALARMMODE_UNION */
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_6_ALARMMODE_ADDR(base) ((base) + (0xA5B4))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_6_VAL_UNION */
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_6_VAL_ADDR(base) ((base) + (0xA5B8))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_7_SRC_UNION */
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_7_SRC_ADDR(base) ((base) + (0xA5C4))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_7_ALARMMODE_UNION */
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_7_ALARMMODE_ADDR(base) ((base) + (0xA5C8))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_7_VAL_UNION */
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_7_VAL_ADDR(base) ((base) + (0xA5CC))

/* 寄存器说明：DSS1_WR TransactionStatFilter域ID
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_TRANS_F_ID_COREID_UNION */
#define SOC_VIVO_BUS_DSS1_WR_TRANS_F_ID_COREID_ADDR(base) ((base) + (0xB000))

/* 寄存器说明：代码版本
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_TRANS_F_ID_REVISIONID_UNION */
#define SOC_VIVO_BUS_DSS1_WR_TRANS_F_ID_REVISIONID_ADDR(base) ((base) + (0xB004))

/* 寄存器说明：DSS1_WR Transaction Probe的Filter工作模式配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_TRANS_F_MODE_UNION */
#define SOC_VIVO_BUS_DSS1_WR_TRANS_F_MODE_ADDR(base)  ((base) + (0xB008))

/* 寄存器说明：地址过滤基地址
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_TRANS_F_ADDRBASE_LOW_UNION */
#define SOC_VIVO_BUS_DSS1_WR_TRANS_F_ADDRBASE_LOW_ADDR(base) ((base) + (0xB00C))

/* 寄存器说明：地址过滤基地址
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_TRANS_F_ADDRBASE_HIGH_UNION */
#define SOC_VIVO_BUS_DSS1_WR_TRANS_F_ADDRBASE_HIGH_ADDR(base) ((base) + (0xB010))

/* 寄存器说明：地址过滤窗口
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_TRANS_F_ADDRWINDOWSIZE_UNION */
#define SOC_VIVO_BUS_DSS1_WR_TRANS_F_ADDRWINDOWSIZE_ADDR(base) ((base) + (0xB014))

/* 寄存器说明：DSS1_WR的Transaction Probe的Opcode过滤条件
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_TRANS_F_OPCODE_UNION */
#define SOC_VIVO_BUS_DSS1_WR_TRANS_F_OPCODE_ADDR(base) ((base) + (0xB020))

/* 寄存器说明：DSS1_WR的Transaction Probe的User过滤条件
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_TRANS_F_USERBASE_UNION */
#define SOC_VIVO_BUS_DSS1_WR_TRANS_F_USERBASE_ADDR(base) ((base) + (0xB024))

/* 寄存器说明：DSS1_WR的Transaction Probe的User过滤条件Mask
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_TRANS_F_USERMASK_UNION */
#define SOC_VIVO_BUS_DSS1_WR_TRANS_F_USERMASK_ADDR(base) ((base) + (0xB028))

/* 寄存器说明：DSS1_WR的Transaction Probe的安全过滤条件
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_TRANS_F_SECURITYBASE_UNION */
#define SOC_VIVO_BUS_DSS1_WR_TRANS_F_SECURITYBASE_ADDR(base) ((base) + (0xB02C))

/* 寄存器说明：DSS1_WR的Transaction Probe的安全过滤条件Mask
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_TRANS_F_SECURITYMASK_UNION */
#define SOC_VIVO_BUS_DSS1_WR_TRANS_F_SECURITYMASK_ADDR(base) ((base) + (0xB030))

/* 寄存器说明：代码版本
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_TRANS_P_ID_REVISIONID_UNION */
#define SOC_VIVO_BUS_DSS1_WR_TRANS_P_ID_REVISIONID_ADDR(base) ((base) + (0xB084))

/* 寄存器说明：transaction Probe的counter使能配置
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_TRANS_P_EN_UNION */
#define SOC_VIVO_BUS_DSS1_WR_TRANS_P_EN_ADDR(base)    ((base) + (0xB088))

/* 寄存器说明：DSS1_WR Transaction Probe的工作模式配置
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_TRANS_P_MODE_UNION */
#define SOC_VIVO_BUS_DSS1_WR_TRANS_P_MODE_ADDR(base)  ((base) + (0xB08C))

/* 寄存器说明：DSS1_WR Transaction Probe的bin_0配置
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_TRANS_P_THRESHOLDS_0_0_UNION */
#define SOC_VIVO_BUS_DSS1_WR_TRANS_P_THRESHOLDS_0_0_ADDR(base) ((base) + (0xB0AC))

/* 寄存器说明：DSS1_WR Transaction Probe的bin_0配置
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_TRANS_P_THRESHOLDS_0_1_UNION */
#define SOC_VIVO_BUS_DSS1_WR_TRANS_P_THRESHOLDS_0_1_ADDR(base) ((base) + (0xB0B0))

/* 寄存器说明：DSS1_WR Transaction Probe的bin_0配置
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_TRANS_P_THRESHOLDS_0_2_UNION */
#define SOC_VIVO_BUS_DSS1_WR_TRANS_P_THRESHOLDS_0_2_ADDR(base) ((base) + (0xB0B4))

/* 寄存器说明：DSS1_WR Transaction Probe的bin_0配置
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_TRANS_P_THRESHOLDS_0_3_UNION */
#define SOC_VIVO_BUS_DSS1_WR_TRANS_P_THRESHOLDS_0_3_ADDR(base) ((base) + (0xB0B8))

/* 寄存器说明：统计计数器溢出状态
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_TRANS_P_OVERFLOWSTATUS_UNION */
#define SOC_VIVO_BUS_DSS1_WR_TRANS_P_OVERFLOWSTATUS_ADDR(base) ((base) + (0xB0EC))

/* 寄存器说明：统计计数器溢出状态清零
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_TRANS_P_OVERFLOWRESET_UNION */
#define SOC_VIVO_BUS_DSS1_WR_TRANS_P_OVERFLOWRESET_ADDR(base) ((base) + (0xB0F0))

/* 寄存器说明：outstanding统计技术工作模式配置
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_TRANS_P_PENDINGEVENTMODE_UNION */
#define SOC_VIVO_BUS_DSS1_WR_TRANS_P_PENDINGEVENTMODE_ADDR(base) ((base) + (0xB0F4))

/* 寄存器说明：latency统计系数配置
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_TRANS_P_PRESCALER_UNION */
#define SOC_VIVO_BUS_DSS1_WR_TRANS_P_PRESCALER_ADDR(base) ((base) + (0xB0F8))

/* 寄存器说明：DSS1_WR Transaction probe域ID
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_TRANS_M_ID_COREID_UNION */
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_ID_COREID_ADDR(base) ((base) + (0xB400))

/* 寄存器说明：总线代码版本寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_TRANS_M_ID_REVISIONID_UNION */
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_ID_REVISIONID_ADDR(base) ((base) + (0xB404))

/* 寄存器说明：Transaction Probe全局控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_TRANS_M_MAINCTL_UNION */
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_MAINCTL_ADDR(base) ((base) + (0xB408))

/* 寄存器说明：Packet Probe使能寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_TRANS_M_CFGCTL_UNION */
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_CFGCTL_ADDR(base) ((base) + (0xB40C))

/* 寄存器说明：统计周期配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_TRANS_M_STATPERIOD_UNION */
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_STATPERIOD_ADDR(base) ((base) + (0xB424))

/* 寄存器说明：手动带宽统计计时开始使能
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_TRANS_M_STATGO_UNION */
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_STATGO_ADDR(base) ((base) + (0xB428))

/* 寄存器说明：统计计数最小告警阈值
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_TRANS_M_STATALARMMIN_UNION */
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_STATALARMMIN_ADDR(base) ((base) + (0xB42C))

/* 寄存器说明：统计计数器最大告警阈值
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_TRANS_M_STATALARMMAX_UNION */
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_STATALARMMAX_ADDR(base) ((base) + (0xB430))

/* 寄存器说明：告警状态寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_TRANS_M_STATALARMSTATUS_UNION */
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_STATALARMSTATUS_ADDR(base) ((base) + (0xB434))

/* 寄存器说明：告警状态清除寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_TRANS_M_STATALARMCLR_UNION */
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_STATALARMCLR_ADDR(base) ((base) + (0xB438))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_0_SRC_UNION */
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_0_SRC_ADDR(base) ((base) + (0xB538))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_0_ALARMMODE_UNION */
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_0_ALARMMODE_ADDR(base) ((base) + (0xB53C))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_0_VAL_UNION */
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_0_VAL_ADDR(base) ((base) + (0xB540))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_1_SRC_UNION */
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_1_SRC_ADDR(base) ((base) + (0xB54C))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_1_ALARMMODE_UNION */
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_1_ALARMMODE_ADDR(base) ((base) + (0xB550))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_1_VAL_UNION */
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_1_VAL_ADDR(base) ((base) + (0xB554))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_2_SRC_UNION */
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_2_SRC_ADDR(base) ((base) + (0xB560))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_2_ALARMMODE_UNION */
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_2_ALARMMODE_ADDR(base) ((base) + (0xB564))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_2_VAL_UNION */
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_2_VAL_ADDR(base) ((base) + (0xB568))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_3_SRC_UNION */
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_3_SRC_ADDR(base) ((base) + (0xB574))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_3_ALARMMODE_UNION */
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_3_ALARMMODE_ADDR(base) ((base) + (0xB578))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_3_VAL_UNION */
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_3_VAL_ADDR(base) ((base) + (0xB57C))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_4_SRC_UNION */
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_4_SRC_ADDR(base) ((base) + (0xB588))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_4_ALARMMODE_UNION */
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_4_ALARMMODE_ADDR(base) ((base) + (0xB58C))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_4_VAL_UNION */
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_4_VAL_ADDR(base) ((base) + (0xB590))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_5_SRC_UNION */
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_5_SRC_ADDR(base) ((base) + (0xB59C))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_5_ALARMMODE_UNION */
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_5_ALARMMODE_ADDR(base) ((base) + (0xB5A0))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_5_VAL_UNION */
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_5_VAL_ADDR(base) ((base) + (0xB5A4))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_6_SRC_UNION */
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_6_SRC_ADDR(base) ((base) + (0xB5B0))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_6_ALARMMODE_UNION */
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_6_ALARMMODE_ADDR(base) ((base) + (0xB5B4))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_6_VAL_UNION */
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_6_VAL_ADDR(base) ((base) + (0xB5B8))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_7_SRC_UNION */
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_7_SRC_ADDR(base) ((base) + (0xB5C4))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_7_ALARMMODE_UNION */
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_7_ALARMMODE_ADDR(base) ((base) + (0xB5C8))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_7_VAL_UNION */
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_7_VAL_ADDR(base) ((base) + (0xB5CC))



/****************************************************************************
                     (2/2) NOC_ISP
 ****************************************************************************/
/* 寄存器说明：
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_QOS_ID_COREID_UNION */
#define SOC_VIVO_BUS_ISP_RD_QOS_ID_COREID_ADDR(base)  ((base) + (0x0000))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_QOS_ID_REVISIONID_UNION */
#define SOC_VIVO_BUS_ISP_RD_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0004))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_QOS_PRIORITY_UNION */
#define SOC_VIVO_BUS_ISP_RD_QOS_PRIORITY_ADDR(base)   ((base) + (0x0008))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_QOS_MODE_UNION */
#define SOC_VIVO_BUS_ISP_RD_QOS_MODE_ADDR(base)       ((base) + (0x000C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_QOS_BANDWIDTH_UNION */
#define SOC_VIVO_BUS_ISP_RD_QOS_BANDWIDTH_ADDR(base)  ((base) + (0x0010))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_QOS_SATURATION_UNION */
#define SOC_VIVO_BUS_ISP_RD_QOS_SATURATION_ADDR(base) ((base) + (0x0014))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_QOS_EXTCONTROL_UNION */
#define SOC_VIVO_BUS_ISP_RD_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0018))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_QOS_ID_COREID_UNION */
#define SOC_VIVO_BUS_ISP_WR_QOS_ID_COREID_ADDR(base)  ((base) + (0x0080))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_QOS_ID_REVISIONID_UNION */
#define SOC_VIVO_BUS_ISP_WR_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0084))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_QOS_PRIORITY_UNION */
#define SOC_VIVO_BUS_ISP_WR_QOS_PRIORITY_ADDR(base)   ((base) + (0x0088))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_QOS_MODE_UNION */
#define SOC_VIVO_BUS_ISP_WR_QOS_MODE_ADDR(base)       ((base) + (0x008C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_QOS_BANDWIDTH_UNION */
#define SOC_VIVO_BUS_ISP_WR_QOS_BANDWIDTH_ADDR(base)  ((base) + (0x0090))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_QOS_SATURATION_UNION */
#define SOC_VIVO_BUS_ISP_WR_QOS_SATURATION_ADDR(base) ((base) + (0x0094))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_QOS_EXTCONTROL_UNION */
#define SOC_VIVO_BUS_ISP_WR_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0098))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VIVO_BUS_A7T0VIVOBUS_RD_QOS_ID_COREID_UNION */
#define SOC_VIVO_BUS_A7T0VIVOBUS_RD_QOS_ID_COREID_ADDR(base) ((base) + (0x0100))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VIVO_BUS_A7T0VIVOBUS_RD_QOS_ID_REVISIONID_UNION */
#define SOC_VIVO_BUS_A7T0VIVOBUS_RD_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0104))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VIVO_BUS_A7T0VIVOBUS_RD_QOS_PRIORITY_UNION */
#define SOC_VIVO_BUS_A7T0VIVOBUS_RD_QOS_PRIORITY_ADDR(base) ((base) + (0x0108))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VIVO_BUS_A7T0VIVOBUS_RD_QOS_MODE_UNION */
#define SOC_VIVO_BUS_A7T0VIVOBUS_RD_QOS_MODE_ADDR(base) ((base) + (0x010C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VIVO_BUS_A7T0VIVOBUS_RD_QOS_BANDWIDTH_UNION */
#define SOC_VIVO_BUS_A7T0VIVOBUS_RD_QOS_BANDWIDTH_ADDR(base) ((base) + (0x0110))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VIVO_BUS_A7T0VIVOBUS_RD_QOS_SATURATION_UNION */
#define SOC_VIVO_BUS_A7T0VIVOBUS_RD_QOS_SATURATION_ADDR(base) ((base) + (0x0114))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VIVO_BUS_A7T0VIVOBUS_RD_QOS_EXTCONTROL_UNION */
#define SOC_VIVO_BUS_A7T0VIVOBUS_RD_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0118))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VIVO_BUS_A7T0VIVOBUS_WR_QOS_ID_COREID_UNION */
#define SOC_VIVO_BUS_A7T0VIVOBUS_WR_QOS_ID_COREID_ADDR(base) ((base) + (0x0180))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VIVO_BUS_A7T0VIVOBUS_WR_QOS_ID_REVISIONID_UNION */
#define SOC_VIVO_BUS_A7T0VIVOBUS_WR_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0184))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VIVO_BUS_A7T0VIVOBUS_WR_QOS_PRIORITY_UNION */
#define SOC_VIVO_BUS_A7T0VIVOBUS_WR_QOS_PRIORITY_ADDR(base) ((base) + (0x0188))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VIVO_BUS_A7T0VIVOBUS_WR_QOS_MODE_UNION */
#define SOC_VIVO_BUS_A7T0VIVOBUS_WR_QOS_MODE_ADDR(base) ((base) + (0x018C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VIVO_BUS_A7T0VIVOBUS_WR_QOS_BANDWIDTH_UNION */
#define SOC_VIVO_BUS_A7T0VIVOBUS_WR_QOS_BANDWIDTH_ADDR(base) ((base) + (0x0190))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VIVO_BUS_A7T0VIVOBUS_WR_QOS_SATURATION_UNION */
#define SOC_VIVO_BUS_A7T0VIVOBUS_WR_QOS_SATURATION_ADDR(base) ((base) + (0x0194))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VIVO_BUS_A7T0VIVOBUS_WR_QOS_EXTCONTROL_UNION */
#define SOC_VIVO_BUS_A7T0VIVOBUS_WR_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0198))

/* 寄存器说明：ISP_RD TransactionStatFilter域ID
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_TRANS_F_ID_COREID_UNION */
#define SOC_VIVO_BUS_ISP_RD_TRANS_F_ID_COREID_ADDR(base) ((base) + (0x8000))

/* 寄存器说明：代码版本
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_TRANS_F_ID_REVISIONID_UNION */
#define SOC_VIVO_BUS_ISP_RD_TRANS_F_ID_REVISIONID_ADDR(base) ((base) + (0x8004))

/* 寄存器说明：ISP_RD Transaction Probe的Filter工作模式配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_TRANS_F_MODE_UNION */
#define SOC_VIVO_BUS_ISP_RD_TRANS_F_MODE_ADDR(base)   ((base) + (0x8008))

/* 寄存器说明：地址过滤基地址
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_TRANS_F_ADDRBASE_LOW_UNION */
#define SOC_VIVO_BUS_ISP_RD_TRANS_F_ADDRBASE_LOW_ADDR(base) ((base) + (0x800C))

/* 寄存器说明：地址过滤基地址
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_TRANS_F_ADDRBASE_HIGH_UNION */
#define SOC_VIVO_BUS_ISP_RD_TRANS_F_ADDRBASE_HIGH_ADDR(base) ((base) + (0x8010))

/* 寄存器说明：地址过滤窗口
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_TRANS_F_ADDRWINDOWSIZE_UNION */
#define SOC_VIVO_BUS_ISP_RD_TRANS_F_ADDRWINDOWSIZE_ADDR(base) ((base) + (0x8014))

/* 寄存器说明：ISP_RD的Transaction Probe的Opcode过滤条件
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_TRANS_F_OPCODE_UNION */
#define SOC_VIVO_BUS_ISP_RD_TRANS_F_OPCODE_ADDR(base) ((base) + (0x8020))

/* 寄存器说明：ISP_RD的Transaction Probe的User过滤条件
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_TRANS_F_USERBASE_UNION */
#define SOC_VIVO_BUS_ISP_RD_TRANS_F_USERBASE_ADDR(base) ((base) + (0x8024))

/* 寄存器说明：ISP_RD的Transaction Probe的User过滤条件Mask
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_TRANS_F_USERMASK_UNION */
#define SOC_VIVO_BUS_ISP_RD_TRANS_F_USERMASK_ADDR(base) ((base) + (0x8028))

/* 寄存器说明：ISP_RD的Transaction Probe的安全过滤条件
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_TRANS_F_SECURITYBASE_UNION */
#define SOC_VIVO_BUS_ISP_RD_TRANS_F_SECURITYBASE_ADDR(base) ((base) + (0x802C))

/* 寄存器说明：ISP_RD的Transaction Probe的安全过滤条件Mask
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_TRANS_F_SECURITYMASK_UNION */
#define SOC_VIVO_BUS_ISP_RD_TRANS_F_SECURITYMASK_ADDR(base) ((base) + (0x8030))

/* 寄存器说明：ISP_RD TransactionStatProfilter域ID
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_TRANS_P_ID_COREID_UNION */
#define SOC_VIVO_BUS_ISP_RD_TRANS_P_ID_COREID_ADDR(base) ((base) + (0x8080))

/* 寄存器说明：代码版本
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_TRANS_P_ID_REVISIONID_UNION */
#define SOC_VIVO_BUS_ISP_RD_TRANS_P_ID_REVISIONID_ADDR(base) ((base) + (0x8084))

/* 寄存器说明：transaction Probe的counter使能配置
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_TRANS_P_EN_UNION */
#define SOC_VIVO_BUS_ISP_RD_TRANS_P_EN_ADDR(base)     ((base) + (0x8088))

/* 寄存器说明：ISP_RD Transaction Probe的工作模式配置
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_TRANS_P_MODE_UNION */
#define SOC_VIVO_BUS_ISP_RD_TRANS_P_MODE_ADDR(base)   ((base) + (0x808C))

/* 寄存器说明：ISP_RD Transaction Probe的bin_0配置
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_TRANS_P_THRESHOLDS_0_0_UNION */
#define SOC_VIVO_BUS_ISP_RD_TRANS_P_THRESHOLDS_0_0_ADDR(base) ((base) + (0x80AC))

/* 寄存器说明：ISP_RD Transaction Probe的bin_0配置
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_TRANS_P_THRESHOLDS_0_1_UNION */
#define SOC_VIVO_BUS_ISP_RD_TRANS_P_THRESHOLDS_0_1_ADDR(base) ((base) + (0x80B0))

/* 寄存器说明：统计计数器溢出状态
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_TRANS_P_OVERFLOWSTATUS_UNION */
#define SOC_VIVO_BUS_ISP_RD_TRANS_P_OVERFLOWSTATUS_ADDR(base) ((base) + (0x80EC))

/* 寄存器说明：统计计数器溢出状态清零
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_TRANS_P_OVERFLOWRESET_UNION */
#define SOC_VIVO_BUS_ISP_RD_TRANS_P_OVERFLOWRESET_ADDR(base) ((base) + (0x80F0))

/* 寄存器说明：outstanding统计技术工作模式配置
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_TRANS_P_PENDINGEVENTMODE_UNION */
#define SOC_VIVO_BUS_ISP_RD_TRANS_P_PENDINGEVENTMODE_ADDR(base) ((base) + (0x80F4))

/* 寄存器说明：latency统计系数配置
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_TRANS_P_PRESCALER_UNION */
#define SOC_VIVO_BUS_ISP_RD_TRANS_P_PRESCALER_ADDR(base) ((base) + (0x80F8))

/* 寄存器说明：ISP_RD Transaction probe域ID
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_TRANS_M_ID_COREID_UNION */
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_ID_COREID_ADDR(base) ((base) + (0x8400))

/* 寄存器说明：总线代码版本寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_TRANS_M_ID_REVISIONID_UNION */
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_ID_REVISIONID_ADDR(base) ((base) + (0x8404))

/* 寄存器说明：Transaction Probe全局控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_TRANS_M_MAINCTL_UNION */
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_MAINCTL_ADDR(base) ((base) + (0x8408))

/* 寄存器说明：Packet Probe使能寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_TRANS_M_CFGCTL_UNION */
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_CFGCTL_ADDR(base) ((base) + (0x840C))

/* 寄存器说明：统计周期配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_TRANS_M_STATPERIOD_UNION */
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_STATPERIOD_ADDR(base) ((base) + (0x8424))

/* 寄存器说明：手动带宽统计计时开始使能
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_TRANS_M_STATGO_UNION */
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_STATGO_ADDR(base) ((base) + (0x8428))

/* 寄存器说明：统计计数最小告警阈值
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_TRANS_M_STATALARMMIN_UNION */
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_STATALARMMIN_ADDR(base) ((base) + (0x842C))

/* 寄存器说明：统计计数器最大告警阈值
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_TRANS_M_STATALARMMAX_UNION */
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_STATALARMMAX_ADDR(base) ((base) + (0x8430))

/* 寄存器说明：告警状态寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_TRANS_M_STATALARMSTATUS_UNION */
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_STATALARMSTATUS_ADDR(base) ((base) + (0x8434))

/* 寄存器说明：告警状态清除寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_TRANS_M_STATALARMCLR_UNION */
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_STATALARMCLR_ADDR(base) ((base) + (0x8438))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_0_SRC_UNION */
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_0_SRC_ADDR(base) ((base) + (0x8538))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_0_ALARMMODE_UNION */
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_0_ALARMMODE_ADDR(base) ((base) + (0x853C))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_0_VAL_UNION */
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_0_VAL_ADDR(base) ((base) + (0x8540))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_1_SRC_UNION */
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_1_SRC_ADDR(base) ((base) + (0x854C))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_1_ALARMMODE_UNION */
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_1_ALARMMODE_ADDR(base) ((base) + (0x8550))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_1_VAL_UNION */
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_1_VAL_ADDR(base) ((base) + (0x8554))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_2_SRC_UNION */
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_2_SRC_ADDR(base) ((base) + (0x8560))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_2_ALARMMODE_UNION */
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_2_ALARMMODE_ADDR(base) ((base) + (0x8564))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_2_VAL_UNION */
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_2_VAL_ADDR(base) ((base) + (0x8568))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_3_SRC_UNION */
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_3_SRC_ADDR(base) ((base) + (0x8574))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_3_ALARMMODE_UNION */
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_3_ALARMMODE_ADDR(base) ((base) + (0x8578))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_3_VAL_UNION */
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_3_VAL_ADDR(base) ((base) + (0x857C))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_4_SRC_UNION */
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_4_SRC_ADDR(base) ((base) + (0x8588))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_4_ALARMMODE_UNION */
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_4_ALARMMODE_ADDR(base) ((base) + (0x858C))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_4_VAL_UNION */
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_4_VAL_ADDR(base) ((base) + (0x8590))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_5_SRC_UNION */
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_5_SRC_ADDR(base) ((base) + (0x859C))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_5_ALARMMODE_UNION */
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_5_ALARMMODE_ADDR(base) ((base) + (0x85A0))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_5_VAL_UNION */
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_5_VAL_ADDR(base) ((base) + (0x85A4))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_6_SRC_UNION */
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_6_SRC_ADDR(base) ((base) + (0x85B0))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_6_ALARMMODE_UNION */
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_6_ALARMMODE_ADDR(base) ((base) + (0x85B4))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_6_VAL_UNION */
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_6_VAL_ADDR(base) ((base) + (0x85B8))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_7_SRC_UNION */
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_7_SRC_ADDR(base) ((base) + (0x85C4))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_7_ALARMMODE_UNION */
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_7_ALARMMODE_ADDR(base) ((base) + (0x85C8))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_7_VAL_UNION */
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_7_VAL_ADDR(base) ((base) + (0x85CC))

/* 寄存器说明：ISP_WR TransactionStatFilter域ID
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_TRANS_F_ID_COREID_UNION */
#define SOC_VIVO_BUS_ISP_WR_TRANS_F_ID_COREID_ADDR(base) ((base) + (0x9000))

/* 寄存器说明：代码版本
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_TRANS_F_ID_REVISIONID_UNION */
#define SOC_VIVO_BUS_ISP_WR_TRANS_F_ID_REVISIONID_ADDR(base) ((base) + (0x9004))

/* 寄存器说明：ISP_WR Transaction Probe的Filter工作模式配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_TRANS_F_MODE_UNION */
#define SOC_VIVO_BUS_ISP_WR_TRANS_F_MODE_ADDR(base)   ((base) + (0x9008))

/* 寄存器说明：地址过滤基地址
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_TRANS_F_ADDRBASE_LOW_UNION */
#define SOC_VIVO_BUS_ISP_WR_TRANS_F_ADDRBASE_LOW_ADDR(base) ((base) + (0x900C))

/* 寄存器说明：地址过滤基地址
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_TRANS_F_ADDRBASE_HIGH_UNION */
#define SOC_VIVO_BUS_ISP_WR_TRANS_F_ADDRBASE_HIGH_ADDR(base) ((base) + (0x9010))

/* 寄存器说明：地址过滤窗口
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_TRANS_F_ADDRWINDOWSIZE_UNION */
#define SOC_VIVO_BUS_ISP_WR_TRANS_F_ADDRWINDOWSIZE_ADDR(base) ((base) + (0x9014))

/* 寄存器说明：ISP_WR的Transaction Probe的Opcode过滤条件
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_TRANS_F_OPCODE_UNION */
#define SOC_VIVO_BUS_ISP_WR_TRANS_F_OPCODE_ADDR(base) ((base) + (0x9020))

/* 寄存器说明：ISP_WR的Transaction Probe的User过滤条件
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_TRANS_F_USERBASE_UNION */
#define SOC_VIVO_BUS_ISP_WR_TRANS_F_USERBASE_ADDR(base) ((base) + (0x9024))

/* 寄存器说明：ISP_WR的Transaction Probe的User过滤条件Mask
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_TRANS_F_USERMASK_UNION */
#define SOC_VIVO_BUS_ISP_WR_TRANS_F_USERMASK_ADDR(base) ((base) + (0x9028))

/* 寄存器说明：ISP_WR的Transaction Probe的安全过滤条件
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_TRANS_F_SECURITYBASE_UNION */
#define SOC_VIVO_BUS_ISP_WR_TRANS_F_SECURITYBASE_ADDR(base) ((base) + (0x902C))

/* 寄存器说明：ISP_WR的Transaction Probe的安全过滤条件Mask
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_TRANS_F_SECURITYMASK_UNION */
#define SOC_VIVO_BUS_ISP_WR_TRANS_F_SECURITYMASK_ADDR(base) ((base) + (0x9030))

/* 寄存器说明：ISP_RD TransactionStatProfilter域ID
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_TRANS_P_ID_COREID_UNION */
#define SOC_VIVO_BUS_ISP_WR_TRANS_P_ID_COREID_ADDR(base) ((base) + (0x9080))

/* 寄存器说明：代码版本
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_TRANS_P_ID_REVISIONID_UNION */
#define SOC_VIVO_BUS_ISP_WR_TRANS_P_ID_REVISIONID_ADDR(base) ((base) + (0x9084))

/* 寄存器说明：transaction Probe的counter使能配置
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_TRANS_P_EN_UNION */
#define SOC_VIVO_BUS_ISP_WR_TRANS_P_EN_ADDR(base)     ((base) + (0x9088))

/* 寄存器说明：ISP_WR Transaction Probe的工作模式配置
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_TRANS_P_MODE_UNION */
#define SOC_VIVO_BUS_ISP_WR_TRANS_P_MODE_ADDR(base)   ((base) + (0x908C))

/* 寄存器说明：ISP_WR Transaction Probe的bin_0配置
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_TRANS_P_THRESHOLDS_0_0_UNION */
#define SOC_VIVO_BUS_ISP_WR_TRANS_P_THRESHOLDS_0_0_ADDR(base) ((base) + (0x90AC))

/* 寄存器说明：ISP_WR Transaction Probe的bin_0配置
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_TRANS_P_THRESHOLDS_0_1_UNION */
#define SOC_VIVO_BUS_ISP_WR_TRANS_P_THRESHOLDS_0_1_ADDR(base) ((base) + (0x90B0))

/* 寄存器说明：统计计数器溢出状态
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_TRANS_P_OVERFLOWSTATUS_UNION */
#define SOC_VIVO_BUS_ISP_WR_TRANS_P_OVERFLOWSTATUS_ADDR(base) ((base) + (0x90EC))

/* 寄存器说明：统计计数器溢出状态清零
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_TRANS_P_OVERFLOWRESET_UNION */
#define SOC_VIVO_BUS_ISP_WR_TRANS_P_OVERFLOWRESET_ADDR(base) ((base) + (0x90F0))

/* 寄存器说明：outstanding统计技术工作模式配置
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_TRANS_P_PENDINGEVENTMODE_UNION */
#define SOC_VIVO_BUS_ISP_WR_TRANS_P_PENDINGEVENTMODE_ADDR(base) ((base) + (0x90F4))

/* 寄存器说明：latency统计系数配置
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_TRANS_P_PRESCALER_UNION */
#define SOC_VIVO_BUS_ISP_WR_TRANS_P_PRESCALER_ADDR(base) ((base) + (0x90F8))

/* 寄存器说明：ISP_WR Transaction probe域ID
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_TRANS_M_ID_COREID_UNION */
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_ID_COREID_ADDR(base) ((base) + (0x9400))

/* 寄存器说明：总线代码版本寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_TRANS_M_ID_REVISIONID_UNION */
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_ID_REVISIONID_ADDR(base) ((base) + (0x9404))

/* 寄存器说明：Transaction Probe全局控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_TRANS_M_MAINCTL_UNION */
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_MAINCTL_ADDR(base) ((base) + (0x9408))

/* 寄存器说明：Packet Probe使能寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_TRANS_M_CFGCTL_UNION */
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_CFGCTL_ADDR(base) ((base) + (0x940C))

/* 寄存器说明：统计周期配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_TRANS_M_STATPERIOD_UNION */
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_STATPERIOD_ADDR(base) ((base) + (0x9424))

/* 寄存器说明：手动带宽统计计时开始使能
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_TRANS_M_STATGO_UNION */
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_STATGO_ADDR(base) ((base) + (0x9428))

/* 寄存器说明：统计计数最小告警阈值
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_TRANS_M_STATALARMMIN_UNION */
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_STATALARMMIN_ADDR(base) ((base) + (0x942C))

/* 寄存器说明：统计计数器最大告警阈值
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_TRANS_M_STATALARMMAX_UNION */
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_STATALARMMAX_ADDR(base) ((base) + (0x9430))

/* 寄存器说明：告警状态寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_TRANS_M_STATALARMSTATUS_UNION */
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_STATALARMSTATUS_ADDR(base) ((base) + (0x9434))

/* 寄存器说明：告警状态清除寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_TRANS_M_STATALARMCLR_UNION */
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_STATALARMCLR_ADDR(base) ((base) + (0x9438))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_0_SRC_UNION */
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_0_SRC_ADDR(base) ((base) + (0x9538))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_0_ALARMMODE_UNION */
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_0_ALARMMODE_ADDR(base) ((base) + (0x953C))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_0_VAL_UNION */
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_0_VAL_ADDR(base) ((base) + (0x9540))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_1_SRC_UNION */
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_1_SRC_ADDR(base) ((base) + (0x954C))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_1_ALARMMODE_UNION */
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_1_ALARMMODE_ADDR(base) ((base) + (0x9550))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_1_VAL_UNION */
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_1_VAL_ADDR(base) ((base) + (0x9554))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_2_SRC_UNION */
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_2_SRC_ADDR(base) ((base) + (0x9560))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_2_ALARMMODE_UNION */
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_2_ALARMMODE_ADDR(base) ((base) + (0x9564))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_2_VAL_UNION */
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_2_VAL_ADDR(base) ((base) + (0x9568))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_3_SRC_UNION */
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_3_SRC_ADDR(base) ((base) + (0x9574))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_3_ALARMMODE_UNION */
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_3_ALARMMODE_ADDR(base) ((base) + (0x9578))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_3_VAL_UNION */
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_3_VAL_ADDR(base) ((base) + (0x957C))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_4_SRC_UNION */
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_4_SRC_ADDR(base) ((base) + (0x9588))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_4_ALARMMODE_UNION */
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_4_ALARMMODE_ADDR(base) ((base) + (0x958C))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_4_VAL_UNION */
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_4_VAL_ADDR(base) ((base) + (0x9590))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_5_SRC_UNION */
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_5_SRC_ADDR(base) ((base) + (0x959C))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_5_ALARMMODE_UNION */
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_5_ALARMMODE_ADDR(base) ((base) + (0x95A0))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_5_VAL_UNION */
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_5_VAL_ADDR(base) ((base) + (0x95A4))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_6_SRC_UNION */
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_6_SRC_ADDR(base) ((base) + (0x95B0))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_6_ALARMMODE_UNION */
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_6_ALARMMODE_ADDR(base) ((base) + (0x95B4))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_6_VAL_UNION */
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_6_VAL_ADDR(base) ((base) + (0x95B8))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_7_SRC_UNION */
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_7_SRC_ADDR(base) ((base) + (0x95C4))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_7_ALARMMODE_UNION */
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_7_ALARMMODE_ADDR(base) ((base) + (0x95C8))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_7_VAL_UNION */
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_7_VAL_ADDR(base) ((base) + (0x95CC))

/* 寄存器说明：A7TOVIVOBUS_RD TransactionStatFilter域ID
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_ID_COREID_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_ID_COREID_ADDR(base) ((base) + (0xA000))

/* 寄存器说明：代码版本
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_ID_REVISIONID_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_ID_REVISIONID_ADDR(base) ((base) + (0xA004))

/* 寄存器说明：A7TOVIVOBUS_RD Transaction Probe的Filter工作模式配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_MODE_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_MODE_ADDR(base) ((base) + (0xA008))

/* 寄存器说明：地址过滤基地址
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_ADDRBASE_LOW_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_ADDRBASE_LOW_ADDR(base) ((base) + (0xA00C))

/* 寄存器说明：地址过滤基地址
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_ADDRBASE_HIGH_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_ADDRBASE_HIGH_ADDR(base) ((base) + (0xA010))

/* 寄存器说明：地址过滤窗口
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_ADDRWINDOWSIZE_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_ADDRWINDOWSIZE_ADDR(base) ((base) + (0xA014))

/* 寄存器说明：A7TOVIVOBUS_RD的Transaction Probe的Opcode过滤条件
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_OPCODE_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_OPCODE_ADDR(base) ((base) + (0xA020))

/* 寄存器说明：A7TOVIVOBUS_RD的Transaction Probe的User过滤条件
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_USERBASE_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_USERBASE_ADDR(base) ((base) + (0xA024))

/* 寄存器说明：A7TOVIVOBUS_RD的Transaction Probe的User过滤条件Mask
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_USERMASK_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_USERMASK_ADDR(base) ((base) + (0xA028))

/* 寄存器说明：A7TOVIVOBUS_RD的Transaction Probe的安全过滤条件
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_SECURITYBASE_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_SECURITYBASE_ADDR(base) ((base) + (0xA02C))

/* 寄存器说明：A7TOVIVOBUS_RD的Transaction Probe的安全过滤条件Mask
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_SECURITYMASK_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_SECURITYMASK_ADDR(base) ((base) + (0xA030))

/* 寄存器说明：A7TOVIVOBUS_RD TransactionStatProfilter域ID
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_ID_COREID_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_ID_COREID_ADDR(base) ((base) + (0xA080))

/* 寄存器说明：代码版本
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_ID_REVISIONID_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_ID_REVISIONID_ADDR(base) ((base) + (0xA084))

/* 寄存器说明：transaction Probe的counter使能配置
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_EN_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_EN_ADDR(base) ((base) + (0xA088))

/* 寄存器说明：A7TOVIVOBUS_RD Transaction Probe的工作模式配置
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_MODE_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_MODE_ADDR(base) ((base) + (0xA08C))

/* 寄存器说明：A7TOVIVOBUS_RD Transaction Probe的bin_0配置
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_THRESHOLDS_0_0_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_THRESHOLDS_0_0_ADDR(base) ((base) + (0xA0AC))

/* 寄存器说明：A7TOVIVOBUS_RD Transaction Probe的bin_0配置
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_THRESHOLDS_0_1_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_THRESHOLDS_0_1_ADDR(base) ((base) + (0xA0B0))

/* 寄存器说明：统计计数器溢出状态
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_OVERFLOWSTATUS_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_OVERFLOWSTATUS_ADDR(base) ((base) + (0xA0EC))

/* 寄存器说明：统计计数器溢出状态清零
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_OVERFLOWRESET_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_OVERFLOWRESET_ADDR(base) ((base) + (0xA0F0))

/* 寄存器说明：outstanding统计技术工作模式配置
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_PENDINGEVENTMODE_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_PENDINGEVENTMODE_ADDR(base) ((base) + (0xA0F4))

/* 寄存器说明：latency统计系数配置
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_PRESCALER_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_PRESCALER_ADDR(base) ((base) + (0xA0F8))

/* 寄存器说明：A7TOVIVOBUS_RD Transaction probe域ID
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_ID_COREID_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_ID_COREID_ADDR(base) ((base) + (0xA400))

/* 寄存器说明：总线代码版本寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_ID_REVISIONID_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_ID_REVISIONID_ADDR(base) ((base) + (0xA404))

/* 寄存器说明：Transaction Probe全局控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_MAINCTL_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_MAINCTL_ADDR(base) ((base) + (0xA408))

/* 寄存器说明：Packet Probe使能寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_CFGCTL_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_CFGCTL_ADDR(base) ((base) + (0xA40C))

/* 寄存器说明：统计周期配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_STATPERIOD_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_STATPERIOD_ADDR(base) ((base) + (0xA424))

/* 寄存器说明：手动带宽统计计时开始使能
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_STATGO_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_STATGO_ADDR(base) ((base) + (0xA428))

/* 寄存器说明：统计计数最小告警阈值
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_STATALARMMIN_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_STATALARMMIN_ADDR(base) ((base) + (0xA42C))

/* 寄存器说明：统计计数器最大告警阈值
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_STATALARMMAX_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_STATALARMMAX_ADDR(base) ((base) + (0xA430))

/* 寄存器说明：告警状态寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_STATALARMSTATUS_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_STATALARMSTATUS_ADDR(base) ((base) + (0xA434))

/* 寄存器说明：告警状态清除寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_STATALARMCLR_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_STATALARMCLR_ADDR(base) ((base) + (0xA438))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_0_SRC_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_0_SRC_ADDR(base) ((base) + (0xA538))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_0_ALARMMODE_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_0_ALARMMODE_ADDR(base) ((base) + (0xA53C))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_0_VAL_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_0_VAL_ADDR(base) ((base) + (0xA540))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_1_SRC_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_1_SRC_ADDR(base) ((base) + (0xA54C))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_1_ALARMMODE_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_1_ALARMMODE_ADDR(base) ((base) + (0xA550))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_1_VAL_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_1_VAL_ADDR(base) ((base) + (0xA554))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_2_SRC_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_2_SRC_ADDR(base) ((base) + (0xA560))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_2_ALARMMODE_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_2_ALARMMODE_ADDR(base) ((base) + (0xA564))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_2_VAL_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_2_VAL_ADDR(base) ((base) + (0xA568))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_3_SRC_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_3_SRC_ADDR(base) ((base) + (0xA574))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_3_ALARMMODE_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_3_ALARMMODE_ADDR(base) ((base) + (0xA578))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_3_VAL_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_3_VAL_ADDR(base) ((base) + (0xA57C))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_4_SRC_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_4_SRC_ADDR(base) ((base) + (0xA588))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_4_ALARMMODE_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_4_ALARMMODE_ADDR(base) ((base) + (0xA58C))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_4_VAL_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_4_VAL_ADDR(base) ((base) + (0xA590))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_5_SRC_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_5_SRC_ADDR(base) ((base) + (0xA59C))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_5_ALARMMODE_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_5_ALARMMODE_ADDR(base) ((base) + (0xA5A0))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_5_VAL_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_5_VAL_ADDR(base) ((base) + (0xA5A4))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_6_SRC_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_6_SRC_ADDR(base) ((base) + (0xA5B0))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_6_ALARMMODE_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_6_ALARMMODE_ADDR(base) ((base) + (0xA5B4))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_6_VAL_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_6_VAL_ADDR(base) ((base) + (0xA5B8))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_7_SRC_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_7_SRC_ADDR(base) ((base) + (0xA5C4))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_7_ALARMMODE_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_7_ALARMMODE_ADDR(base) ((base) + (0xA5C8))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_7_VAL_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_7_VAL_ADDR(base) ((base) + (0xA5CC))

/* 寄存器说明：ISP_WR TransactionStatFilter域ID
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_ID_COREID_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_ID_COREID_ADDR(base) ((base) + (0xB000))

/* 寄存器说明：代码版本
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_ID_REVISIONID_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_ID_REVISIONID_ADDR(base) ((base) + (0xB004))

/* 寄存器说明：ISP_WR Transaction Probe的Filter工作模式配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_MODE_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_MODE_ADDR(base) ((base) + (0xB008))

/* 寄存器说明：地址过滤基地址
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_ADDRBASE_LOW_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_ADDRBASE_LOW_ADDR(base) ((base) + (0xB00C))

/* 寄存器说明：地址过滤基地址
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_ADDRBASE_HIGH_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_ADDRBASE_HIGH_ADDR(base) ((base) + (0xB010))

/* 寄存器说明：地址过滤窗口
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_ADDRWINDOWSIZE_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_ADDRWINDOWSIZE_ADDR(base) ((base) + (0xB014))

/* 寄存器说明：ISP_WR的Transaction Probe的Opcode过滤条件
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_OPCODE_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_OPCODE_ADDR(base) ((base) + (0xB020))

/* 寄存器说明：ISP_WR的Transaction Probe的User过滤条件
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_USERBASE_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_USERBASE_ADDR(base) ((base) + (0xB024))

/* 寄存器说明：ISP_WR的Transaction Probe的User过滤条件Mask
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_USERMASK_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_USERMASK_ADDR(base) ((base) + (0xB028))

/* 寄存器说明：ISP_WR的Transaction Probe的安全过滤条件
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_SECURITYBASE_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_SECURITYBASE_ADDR(base) ((base) + (0xB02C))

/* 寄存器说明：ISP_WR的Transaction Probe的安全过滤条件Mask
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_SECURITYMASK_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_SECURITYMASK_ADDR(base) ((base) + (0xB030))

/* 寄存器说明：A7TOVIVOBUS_RD TransactionStatProfilter域ID
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_ID_COREID_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_ID_COREID_ADDR(base) ((base) + (0xB080))

/* 寄存器说明：代码版本
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_ID_REVISIONID_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_ID_REVISIONID_ADDR(base) ((base) + (0xB084))

/* 寄存器说明：transaction Probe的counter使能配置
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_EN_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_EN_ADDR(base) ((base) + (0xB088))

/* 寄存器说明：A7TOVIVOBUS_WR Transaction Probe的工作模式配置
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_MODE_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_MODE_ADDR(base) ((base) + (0xB08C))

/* 寄存器说明：A7TOVIVOBUS_WR Transaction Probe的bin_0配置
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_THRESHOLDS_0_0_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_THRESHOLDS_0_0_ADDR(base) ((base) + (0xB0AC))

/* 寄存器说明：A7TOVIVOBUS_WR Transaction Probe的bin_0配置
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_THRESHOLDS_0_1_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_THRESHOLDS_0_1_ADDR(base) ((base) + (0xB0B0))

/* 寄存器说明：统计计数器溢出状态
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_OVERFLOWSTATUS_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_OVERFLOWSTATUS_ADDR(base) ((base) + (0xB0EC))

/* 寄存器说明：统计计数器溢出状态清零
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_OVERFLOWRESET_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_OVERFLOWRESET_ADDR(base) ((base) + (0xB0F0))

/* 寄存器说明：outstanding统计技术工作模式配置
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_PENDINGEVENTMODE_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_PENDINGEVENTMODE_ADDR(base) ((base) + (0xB0F4))

/* 寄存器说明：latency统计系数配置
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_PRESCALER_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_PRESCALER_ADDR(base) ((base) + (0xB0F8))

/* 寄存器说明：A7TOVIVOBUS_WR Transaction probe域ID
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_ID_COREID_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_ID_COREID_ADDR(base) ((base) + (0xB400))

/* 寄存器说明：总线代码版本寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_ID_REVISIONID_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_ID_REVISIONID_ADDR(base) ((base) + (0xB404))

/* 寄存器说明：Transaction Probe全局控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_MAINCTL_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_MAINCTL_ADDR(base) ((base) + (0xB408))

/* 寄存器说明：Packet Probe使能寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_CFGCTL_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_CFGCTL_ADDR(base) ((base) + (0xB40C))

/* 寄存器说明：统计周期配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_STATPERIOD_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_STATPERIOD_ADDR(base) ((base) + (0xB424))

/* 寄存器说明：手动带宽统计计时开始使能
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_STATGO_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_STATGO_ADDR(base) ((base) + (0xB428))

/* 寄存器说明：统计计数最小告警阈值
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_STATALARMMIN_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_STATALARMMIN_ADDR(base) ((base) + (0xB42C))

/* 寄存器说明：统计计数器最大告警阈值
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_STATALARMMAX_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_STATALARMMAX_ADDR(base) ((base) + (0xB430))

/* 寄存器说明：告警状态寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_STATALARMSTATUS_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_STATALARMSTATUS_ADDR(base) ((base) + (0xB434))

/* 寄存器说明：告警状态清除寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_STATALARMCLR_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_STATALARMCLR_ADDR(base) ((base) + (0xB438))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_0_SRC_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_0_SRC_ADDR(base) ((base) + (0xB538))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_0_ALARMMODE_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_0_ALARMMODE_ADDR(base) ((base) + (0xB53C))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_0_VAL_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_0_VAL_ADDR(base) ((base) + (0xB540))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_1_SRC_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_1_SRC_ADDR(base) ((base) + (0xB54C))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_1_ALARMMODE_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_1_ALARMMODE_ADDR(base) ((base) + (0xB550))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_1_VAL_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_1_VAL_ADDR(base) ((base) + (0xB554))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_2_SRC_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_2_SRC_ADDR(base) ((base) + (0xB560))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_2_ALARMMODE_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_2_ALARMMODE_ADDR(base) ((base) + (0xB564))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_2_VAL_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_2_VAL_ADDR(base) ((base) + (0xB568))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_3_SRC_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_3_SRC_ADDR(base) ((base) + (0xB574))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_3_ALARMMODE_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_3_ALARMMODE_ADDR(base) ((base) + (0xB578))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_3_VAL_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_3_VAL_ADDR(base) ((base) + (0xB57C))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_4_SRC_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_4_SRC_ADDR(base) ((base) + (0xB588))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_4_ALARMMODE_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_4_ALARMMODE_ADDR(base) ((base) + (0xB58C))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_4_VAL_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_4_VAL_ADDR(base) ((base) + (0xB590))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_5_SRC_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_5_SRC_ADDR(base) ((base) + (0xB59C))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_5_ALARMMODE_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_5_ALARMMODE_ADDR(base) ((base) + (0xB5A0))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_5_VAL_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_5_VAL_ADDR(base) ((base) + (0xB5A4))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_6_SRC_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_6_SRC_ADDR(base) ((base) + (0xB5B0))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_6_ALARMMODE_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_6_ALARMMODE_ADDR(base) ((base) + (0xB5B4))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_6_VAL_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_6_VAL_ADDR(base) ((base) + (0xB5B8))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_7_SRC_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_7_SRC_ADDR(base) ((base) + (0xB5C4))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_7_ALARMMODE_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_7_ALARMMODE_ADDR(base) ((base) + (0xB5C8))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_7_VAL_UNION */
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_7_VAL_ADDR(base) ((base) + (0xB5CC))





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
                     (1/2) NOC_DSS
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_RD_QOS_ID_COREID_UNION
 结构说明  : DSS0_RD_QOS_ID_COREID 寄存器结构定义。地址偏移量:0x0000，初值:0x7FE13B04，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coretypeid   : 8;  /* bit[0-7] : Field containing a checksum of the parameters of the IP. */
        unsigned int  corechecksum : 24; /* bit[8-31]: Field identifying the type of IP. */
    } reg;
} SOC_VIVO_BUS_DSS0_RD_QOS_ID_COREID_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_RD_QOS_ID_COREID_coretypeid_START    (0)
#define SOC_VIVO_BUS_DSS0_RD_QOS_ID_COREID_coretypeid_END      (7)
#define SOC_VIVO_BUS_DSS0_RD_QOS_ID_COREID_corechecksum_START  (8)
#define SOC_VIVO_BUS_DSS0_RD_QOS_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_RD_QOS_ID_REVISIONID_UNION
 结构说明  : DSS0_RD_QOS_ID_REVISIONID 寄存器结构定义。地址偏移量:0x0004，初值:0x012D5300，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  userid    : 8;  /* bit[0-7] : Field containing a user defined value, not used anywhere inside the IP itself. */
        unsigned int  flexnocid : 24; /* bit[8-31]: Field containing the build revision of the software used to generate the IP HDL code. */
    } reg;
} SOC_VIVO_BUS_DSS0_RD_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_RD_QOS_ID_REVISIONID_userid_START     (0)
#define SOC_VIVO_BUS_DSS0_RD_QOS_ID_REVISIONID_userid_END       (7)
#define SOC_VIVO_BUS_DSS0_RD_QOS_ID_REVISIONID_flexnocid_START  (8)
#define SOC_VIVO_BUS_DSS0_RD_QOS_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_RD_QOS_PRIORITY_UNION
 结构说明  : DSS0_RD_QOS_PRIORITY 寄存器结构定义。地址偏移量:0x0008，初值:0x80000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p0       : 2;  /* bit[0-1]  : In Regulator mode, defines the LOW hurry level. In Fixed/Limiter mode, defines the Urgency level for WRITE transactions. */
        unsigned int  reserved_0: 6;  /* bit[2-7]  : 保留 */
        unsigned int  p1       : 2;  /* bit[8-9]  : In Regulator mode, defines the HIGH hurry level. In Fixed/Limiter mode, defines the Urgency level for READ transactions. */
        unsigned int  reserved_1: 22; /* bit[10-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_RD_QOS_PRIORITY_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_RD_QOS_PRIORITY_p0_START        (0)
#define SOC_VIVO_BUS_DSS0_RD_QOS_PRIORITY_p0_END          (1)
#define SOC_VIVO_BUS_DSS0_RD_QOS_PRIORITY_p1_START        (8)
#define SOC_VIVO_BUS_DSS0_RD_QOS_PRIORITY_p1_END          (9)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_RD_QOS_MODE_UNION
 结构说明  : DSS0_RD_QOS_MODE 寄存器结构定义。地址偏移量:0x000C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode     : 2;  /* bit[0-1] : Functional Mode: 0=Fixed, 1=Limiter, 2=Bypass, 3=Regulator. */
        unsigned int  reserved : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_RD_QOS_MODE_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_RD_QOS_MODE_mode_START      (0)
#define SOC_VIVO_BUS_DSS0_RD_QOS_MODE_mode_END        (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_RD_QOS_BANDWIDTH_UNION
 结构说明  : DSS0_RD_QOS_BANDWIDTH 寄存器结构定义。地址偏移量:0x0010，初值:0x000007E0，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bandwidth : 13; /* bit[0-12] : Defines the bandwidth threshold in 1/256th-byte-per-cycle units. In other words, the desired rate in MBps is divided by frequency in MHz of the NIU, and then multiplied by 256. */
        unsigned int  reserved  : 19; /* bit[13-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_RD_QOS_BANDWIDTH_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_RD_QOS_BANDWIDTH_bandwidth_START  (0)
#define SOC_VIVO_BUS_DSS0_RD_QOS_BANDWIDTH_bandwidth_END    (12)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_RD_QOS_SATURATION_UNION
 结构说明  : DSS0_RD_QOS_SATURATION 寄存器结构定义。地址偏移量:0x0014，初值:0x000003E8，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  saturation : 10; /* bit[0-9]  : Defines the size of the bandwidth counter, that is, the measurement window, in 16-byte units. In other words, the desired number of bytes divided by 16. */
        unsigned int  reserved   : 22; /* bit[10-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_RD_QOS_SATURATION_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_RD_QOS_SATURATION_saturation_START  (0)
#define SOC_VIVO_BUS_DSS0_RD_QOS_SATURATION_saturation_END    (9)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_RD_QOS_EXTCONTROL_UNION
 结构说明  : DSS0_RD_QOS_EXTCONTROL 寄存器结构定义。地址偏移量:0x0018，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  socketqosen : 1;  /* bit[0-0] : Combines the Socket QoS with Regulator QoS. */
        unsigned int  extthren    : 1;  /* bit[1-1] : ExtThr input controls Low/High priority instead of bandwidth threshold. */
        unsigned int  intclken    : 1;  /* bit[2-2] : Replace the External reference by the local clock. */
        unsigned int  reserved    : 29; /* bit[3-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_RD_QOS_EXTCONTROL_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_RD_QOS_EXTCONTROL_socketqosen_START  (0)
#define SOC_VIVO_BUS_DSS0_RD_QOS_EXTCONTROL_socketqosen_END    (0)
#define SOC_VIVO_BUS_DSS0_RD_QOS_EXTCONTROL_extthren_START     (1)
#define SOC_VIVO_BUS_DSS0_RD_QOS_EXTCONTROL_extthren_END       (1)
#define SOC_VIVO_BUS_DSS0_RD_QOS_EXTCONTROL_intclken_START     (2)
#define SOC_VIVO_BUS_DSS0_RD_QOS_EXTCONTROL_intclken_END       (2)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_QOS_ID_COREID_UNION
 结构说明  : DSS0_WR_QOS_ID_COREID 寄存器结构定义。地址偏移量:0x0080，初值:0xD8BCCE04，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coretypeid   : 8;  /* bit[0-7] : Field containing a checksum of the parameters of the IP. */
        unsigned int  corechecksum : 24; /* bit[8-31]: Field identifying the type of IP. */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_QOS_ID_COREID_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_QOS_ID_COREID_coretypeid_START    (0)
#define SOC_VIVO_BUS_DSS0_WR_QOS_ID_COREID_coretypeid_END      (7)
#define SOC_VIVO_BUS_DSS0_WR_QOS_ID_COREID_corechecksum_START  (8)
#define SOC_VIVO_BUS_DSS0_WR_QOS_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_QOS_ID_REVISIONID_UNION
 结构说明  : DSS0_WR_QOS_ID_REVISIONID 寄存器结构定义。地址偏移量:0x0084，初值:0x012D5300，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  userid    : 8;  /* bit[0-7] : Field containing a user defined value, not used anywhere inside the IP itself. */
        unsigned int  flexnocid : 24; /* bit[8-31]: Field containing the build revision of the software used to generate the IP HDL code. */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_QOS_ID_REVISIONID_userid_START     (0)
#define SOC_VIVO_BUS_DSS0_WR_QOS_ID_REVISIONID_userid_END       (7)
#define SOC_VIVO_BUS_DSS0_WR_QOS_ID_REVISIONID_flexnocid_START  (8)
#define SOC_VIVO_BUS_DSS0_WR_QOS_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_QOS_PRIORITY_UNION
 结构说明  : DSS0_WR_QOS_PRIORITY 寄存器结构定义。地址偏移量:0x0088，初值:0x80000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p0       : 2;  /* bit[0-1]  : In Regulator mode, defines the LOW hurry level. In Fixed/Limiter mode, defines the Urgency level for WRITE transactions. */
        unsigned int  reserved_0: 6;  /* bit[2-7]  : 保留 */
        unsigned int  p1       : 2;  /* bit[8-9]  : In Regulator mode, defines the HIGH hurry level. In Fixed/Limiter mode, defines the Urgency level for READ transactions. */
        unsigned int  reserved_1: 22; /* bit[10-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_QOS_PRIORITY_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_QOS_PRIORITY_p0_START        (0)
#define SOC_VIVO_BUS_DSS0_WR_QOS_PRIORITY_p0_END          (1)
#define SOC_VIVO_BUS_DSS0_WR_QOS_PRIORITY_p1_START        (8)
#define SOC_VIVO_BUS_DSS0_WR_QOS_PRIORITY_p1_END          (9)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_QOS_MODE_UNION
 结构说明  : DSS0_WR_QOS_MODE 寄存器结构定义。地址偏移量:0x008C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode     : 2;  /* bit[0-1] : Functional Mode: 0=Fixed, 1=Limiter, 2=Bypass, 3=Regulator. */
        unsigned int  reserved : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_QOS_MODE_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_QOS_MODE_mode_START      (0)
#define SOC_VIVO_BUS_DSS0_WR_QOS_MODE_mode_END        (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_QOS_BANDWIDTH_UNION
 结构说明  : DSS0_WR_QOS_BANDWIDTH 寄存器结构定义。地址偏移量:0x0090，初值:0x000004B0，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bandwidth : 13; /* bit[0-12] : Defines the bandwidth threshold in 1/256th-byte-per-cycle units. In other words, the desired rate in MBps is divided by frequency in MHz of the NIU, and then multiplied by 256. */
        unsigned int  reserved  : 19; /* bit[13-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_QOS_BANDWIDTH_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_QOS_BANDWIDTH_bandwidth_START  (0)
#define SOC_VIVO_BUS_DSS0_WR_QOS_BANDWIDTH_bandwidth_END    (12)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_QOS_SATURATION_UNION
 结构说明  : DSS0_WR_QOS_SATURATION 寄存器结构定义。地址偏移量:0x0094，初值:0x000003E8，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  saturation : 10; /* bit[0-9]  : Defines the size of the bandwidth counter, that is, the measurement window, in 16-byte units. In other words, the desired number of bytes divided by 16. */
        unsigned int  reserved   : 22; /* bit[10-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_QOS_SATURATION_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_QOS_SATURATION_saturation_START  (0)
#define SOC_VIVO_BUS_DSS0_WR_QOS_SATURATION_saturation_END    (9)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_QOS_EXTCONTROL_UNION
 结构说明  : DSS0_WR_QOS_EXTCONTROL 寄存器结构定义。地址偏移量:0x0098，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  socketqosen : 1;  /* bit[0-0] : Combines the Socket QoS with Regulator QoS. */
        unsigned int  extthren    : 1;  /* bit[1-1] : ExtThr input controls Low/High priority instead of bandwidth threshold. */
        unsigned int  intclken    : 1;  /* bit[2-2] : Replace the External reference by the local clock. */
        unsigned int  reserved    : 29; /* bit[3-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_QOS_EXTCONTROL_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_QOS_EXTCONTROL_socketqosen_START  (0)
#define SOC_VIVO_BUS_DSS0_WR_QOS_EXTCONTROL_socketqosen_END    (0)
#define SOC_VIVO_BUS_DSS0_WR_QOS_EXTCONTROL_extthren_START     (1)
#define SOC_VIVO_BUS_DSS0_WR_QOS_EXTCONTROL_extthren_END       (1)
#define SOC_VIVO_BUS_DSS0_WR_QOS_EXTCONTROL_intclken_START     (2)
#define SOC_VIVO_BUS_DSS0_WR_QOS_EXTCONTROL_intclken_END       (2)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_RD_QOS_ID_COREID_UNION
 结构说明  : DSS1_RD_QOS_ID_COREID 寄存器结构定义。地址偏移量:0x0100，初值:0x7A512504，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coretypeid   : 8;  /* bit[0-7] : Field containing a checksum of the parameters of the IP. */
        unsigned int  corechecksum : 24; /* bit[8-31]: Field identifying the type of IP. */
    } reg;
} SOC_VIVO_BUS_DSS1_RD_QOS_ID_COREID_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_RD_QOS_ID_COREID_coretypeid_START    (0)
#define SOC_VIVO_BUS_DSS1_RD_QOS_ID_COREID_coretypeid_END      (7)
#define SOC_VIVO_BUS_DSS1_RD_QOS_ID_COREID_corechecksum_START  (8)
#define SOC_VIVO_BUS_DSS1_RD_QOS_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_RD_QOS_ID_REVISIONID_UNION
 结构说明  : DSS1_RD_QOS_ID_REVISIONID 寄存器结构定义。地址偏移量:0x0104，初值:0x012D5300，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  userid    : 8;  /* bit[0-7] : Field containing a user defined value, not used anywhere inside the IP itself. */
        unsigned int  flexnocid : 24; /* bit[8-31]: Field containing the build revision of the software used to generate the IP HDL code. */
    } reg;
} SOC_VIVO_BUS_DSS1_RD_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_RD_QOS_ID_REVISIONID_userid_START     (0)
#define SOC_VIVO_BUS_DSS1_RD_QOS_ID_REVISIONID_userid_END       (7)
#define SOC_VIVO_BUS_DSS1_RD_QOS_ID_REVISIONID_flexnocid_START  (8)
#define SOC_VIVO_BUS_DSS1_RD_QOS_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_RD_QOS_PRIORITY_UNION
 结构说明  : DSS1_RD_QOS_PRIORITY 寄存器结构定义。地址偏移量:0x0108，初值:0x80000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p0       : 2;  /* bit[0-1]  : In Regulator mode, defines the LOW hurry level. In Fixed/Limiter mode, defines the Urgency level for WRITE transactions. */
        unsigned int  reserved_0: 6;  /* bit[2-7]  : 保留 */
        unsigned int  p1       : 2;  /* bit[8-9]  : In Regulator mode, defines the HIGH hurry level. In Fixed/Limiter mode, defines the Urgency level for READ transactions. */
        unsigned int  reserved_1: 22; /* bit[10-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_RD_QOS_PRIORITY_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_RD_QOS_PRIORITY_p0_START        (0)
#define SOC_VIVO_BUS_DSS1_RD_QOS_PRIORITY_p0_END          (1)
#define SOC_VIVO_BUS_DSS1_RD_QOS_PRIORITY_p1_START        (8)
#define SOC_VIVO_BUS_DSS1_RD_QOS_PRIORITY_p1_END          (9)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_RD_QOS_MODE_UNION
 结构说明  : DSS1_RD_QOS_MODE 寄存器结构定义。地址偏移量:0x010C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode     : 2;  /* bit[0-1] : Functional Mode: 0=Fixed, 1=Limiter, 2=Bypass, 3=Regulator. */
        unsigned int  reserved : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_RD_QOS_MODE_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_RD_QOS_MODE_mode_START      (0)
#define SOC_VIVO_BUS_DSS1_RD_QOS_MODE_mode_END        (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_RD_QOS_BANDWIDTH_UNION
 结构说明  : DSS1_RD_QOS_BANDWIDTH 寄存器结构定义。地址偏移量:0x0110，初值:0x000007E0，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bandwidth : 13; /* bit[0-12] : Defines the bandwidth threshold in 1/256th-byte-per-cycle units. In other words, the desired rate in MBps is divided by frequency in MHz of the NIU, and then multiplied by 256. */
        unsigned int  reserved  : 19; /* bit[13-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_RD_QOS_BANDWIDTH_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_RD_QOS_BANDWIDTH_bandwidth_START  (0)
#define SOC_VIVO_BUS_DSS1_RD_QOS_BANDWIDTH_bandwidth_END    (12)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_RD_QOS_SATURATION_UNION
 结构说明  : DSS1_RD_QOS_SATURATION 寄存器结构定义。地址偏移量:0x0114，初值:0x000003E8，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  saturation : 10; /* bit[0-9]  : Defines the size of the bandwidth counter, that is, the measurement window, in 16-byte units. In other words, the desired number of bytes divided by 16. */
        unsigned int  reserved   : 22; /* bit[10-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_RD_QOS_SATURATION_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_RD_QOS_SATURATION_saturation_START  (0)
#define SOC_VIVO_BUS_DSS1_RD_QOS_SATURATION_saturation_END    (9)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_RD_QOS_EXTCONTROL_UNION
 结构说明  : DSS1_RD_QOS_EXTCONTROL 寄存器结构定义。地址偏移量:0x0118，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  socketqosen : 1;  /* bit[0-0] : Combines the Socket QoS with Regulator QoS. */
        unsigned int  extthren    : 1;  /* bit[1-1] : ExtThr input controls Low/High priority instead of bandwidth threshold. */
        unsigned int  intclken    : 1;  /* bit[2-2] : Replace the External reference by the local clock. */
        unsigned int  reserved    : 29; /* bit[3-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_RD_QOS_EXTCONTROL_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_RD_QOS_EXTCONTROL_socketqosen_START  (0)
#define SOC_VIVO_BUS_DSS1_RD_QOS_EXTCONTROL_socketqosen_END    (0)
#define SOC_VIVO_BUS_DSS1_RD_QOS_EXTCONTROL_extthren_START     (1)
#define SOC_VIVO_BUS_DSS1_RD_QOS_EXTCONTROL_extthren_END       (1)
#define SOC_VIVO_BUS_DSS1_RD_QOS_EXTCONTROL_intclken_START     (2)
#define SOC_VIVO_BUS_DSS1_RD_QOS_EXTCONTROL_intclken_END       (2)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_QOS_ID_COREID_UNION
 结构说明  : DSS1_WR_QOS_ID_COREID 寄存器结构定义。地址偏移量:0x0180，初值:0x9F7F5F04，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coretypeid   : 8;  /* bit[0-7] : Field containing a checksum of the parameters of the IP. */
        unsigned int  corechecksum : 24; /* bit[8-31]: Field identifying the type of IP. */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_QOS_ID_COREID_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_QOS_ID_COREID_coretypeid_START    (0)
#define SOC_VIVO_BUS_DSS1_WR_QOS_ID_COREID_coretypeid_END      (7)
#define SOC_VIVO_BUS_DSS1_WR_QOS_ID_COREID_corechecksum_START  (8)
#define SOC_VIVO_BUS_DSS1_WR_QOS_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_QOS_ID_REVISIONID_UNION
 结构说明  : DSS1_WR_QOS_ID_REVISIONID 寄存器结构定义。地址偏移量:0x0184，初值:0x012D5300，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  userid    : 8;  /* bit[0-7] : Field containing a user defined value, not used anywhere inside the IP itself. */
        unsigned int  flexnocid : 24; /* bit[8-31]: Field containing the build revision of the software used to generate the IP HDL code. */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_QOS_ID_REVISIONID_userid_START     (0)
#define SOC_VIVO_BUS_DSS1_WR_QOS_ID_REVISIONID_userid_END       (7)
#define SOC_VIVO_BUS_DSS1_WR_QOS_ID_REVISIONID_flexnocid_START  (8)
#define SOC_VIVO_BUS_DSS1_WR_QOS_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_QOS_PRIORITY_UNION
 结构说明  : DSS1_WR_QOS_PRIORITY 寄存器结构定义。地址偏移量:0x0188，初值:0x80000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p0       : 2;  /* bit[0-1]  : In Regulator mode, defines the LOW hurry level. In Fixed/Limiter mode, defines the Urgency level for WRITE transactions. */
        unsigned int  reserved_0: 6;  /* bit[2-7]  : 保留 */
        unsigned int  p1       : 2;  /* bit[8-9]  : In Regulator mode, defines the HIGH hurry level. In Fixed/Limiter mode, defines the Urgency level for READ transactions. */
        unsigned int  reserved_1: 22; /* bit[10-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_QOS_PRIORITY_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_QOS_PRIORITY_p0_START        (0)
#define SOC_VIVO_BUS_DSS1_WR_QOS_PRIORITY_p0_END          (1)
#define SOC_VIVO_BUS_DSS1_WR_QOS_PRIORITY_p1_START        (8)
#define SOC_VIVO_BUS_DSS1_WR_QOS_PRIORITY_p1_END          (9)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_QOS_MODE_UNION
 结构说明  : DSS1_WR_QOS_MODE 寄存器结构定义。地址偏移量:0x018C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode     : 2;  /* bit[0-1] : Functional Mode: 0=Fixed, 1=Limiter, 2=Bypass, 3=Regulator. */
        unsigned int  reserved : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_QOS_MODE_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_QOS_MODE_mode_START      (0)
#define SOC_VIVO_BUS_DSS1_WR_QOS_MODE_mode_END        (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_QOS_BANDWIDTH_UNION
 结构说明  : DSS1_WR_QOS_BANDWIDTH 寄存器结构定义。地址偏移量:0x0190，初值:0x000004B0，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bandwidth : 13; /* bit[0-12] : Defines the bandwidth threshold in 1/256th-byte-per-cycle units. In other words, the desired rate in MBps is divided by frequency in MHz of the NIU, and then multiplied by 256. */
        unsigned int  reserved  : 19; /* bit[13-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_QOS_BANDWIDTH_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_QOS_BANDWIDTH_bandwidth_START  (0)
#define SOC_VIVO_BUS_DSS1_WR_QOS_BANDWIDTH_bandwidth_END    (12)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_QOS_SATURATION_UNION
 结构说明  : DSS1_WR_QOS_SATURATION 寄存器结构定义。地址偏移量:0x0194，初值:0x000003E8，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  saturation : 10; /* bit[0-9]  : Defines the size of the bandwidth counter, that is, the measurement window, in 16-byte units. In other words, the desired number of bytes divided by 16. */
        unsigned int  reserved   : 22; /* bit[10-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_QOS_SATURATION_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_QOS_SATURATION_saturation_START  (0)
#define SOC_VIVO_BUS_DSS1_WR_QOS_SATURATION_saturation_END    (9)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_QOS_EXTCONTROL_UNION
 结构说明  : DSS1_WR_QOS_EXTCONTROL 寄存器结构定义。地址偏移量:0x0198，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  socketqosen : 1;  /* bit[0-0] : Combines the Socket QoS with Regulator QoS. */
        unsigned int  extthren    : 1;  /* bit[1-1] : ExtThr input controls Low/High priority instead of bandwidth threshold. */
        unsigned int  intclken    : 1;  /* bit[2-2] : Replace the External reference by the local clock. */
        unsigned int  reserved    : 29; /* bit[3-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_QOS_EXTCONTROL_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_QOS_EXTCONTROL_socketqosen_START  (0)
#define SOC_VIVO_BUS_DSS1_WR_QOS_EXTCONTROL_socketqosen_END    (0)
#define SOC_VIVO_BUS_DSS1_WR_QOS_EXTCONTROL_extthren_START     (1)
#define SOC_VIVO_BUS_DSS1_WR_QOS_EXTCONTROL_extthren_END       (1)
#define SOC_VIVO_BUS_DSS1_WR_QOS_EXTCONTROL_intclken_START     (2)
#define SOC_VIVO_BUS_DSS1_WR_QOS_EXTCONTROL_intclken_END       (2)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_VIVOBUS_ERR_ID_COREID_UNION
 结构说明  : VIVOBUS_ERR_ID_COREID 寄存器结构定义。地址偏移量:0x1C00，初值:0x220BFC0D，宽度:32
 寄存器说明: VIVOBUS Err probe域ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_coreid : 32; /* bit[0-31]: VIVO_BUS的error probe的域ID。 */
    } reg;
} SOC_VIVO_BUS_VIVOBUS_ERR_ID_COREID_UNION;
#endif
#define SOC_VIVO_BUS_VIVOBUS_ERR_ID_COREID_id_coreid_START  (0)
#define SOC_VIVO_BUS_VIVOBUS_ERR_ID_COREID_id_coreid_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_VIVOBUS_ERR_ID_REVISIONID_UNION
 结构说明  : VIVOBUS_ERR_ID_REVISIONID 寄存器结构定义。地址偏移量:0x1C04，初值:0x012D5300，宽度:32
 寄存器说明: 总线代码版本寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_revisionid : 32; /* bit[0-31]: 低8bit自定义，高24bit是NOC的配置HUSH值。 */
    } reg;
} SOC_VIVO_BUS_VIVOBUS_ERR_ID_REVISIONID_UNION;
#endif
#define SOC_VIVO_BUS_VIVOBUS_ERR_ID_REVISIONID_id_revisionid_START  (0)
#define SOC_VIVO_BUS_VIVOBUS_ERR_ID_REVISIONID_id_revisionid_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_VIVOBUS_FAULTEN_UNION
 结构说明  : VIVOBUS_FAULTEN 寄存器结构定义。地址偏移量:0x1C08，初值:0x00000000，宽度:32
 寄存器说明: VIVOBUS Err probe使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  faulten  : 1;  /* bit[0]   : 使能输出中断，高有效。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_VIVOBUS_FAULTEN_UNION;
#endif
#define SOC_VIVO_BUS_VIVOBUS_FAULTEN_faulten_START   (0)
#define SOC_VIVO_BUS_VIVOBUS_FAULTEN_faulten_END     (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_VIVOBUS_ERRVLD_UNION
 结构说明  : VIVOBUS_ERRVLD 寄存器结构定义。地址偏移量:0x1C0C，初值:0x00000000，宽度:32
 寄存器说明: Error log有效指示寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errvld   : 1;  /* bit[0]   : Error log有效指示状态寄存器，高有效。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_VIVOBUS_ERRVLD_UNION;
#endif
#define SOC_VIVO_BUS_VIVOBUS_ERRVLD_errvld_START    (0)
#define SOC_VIVO_BUS_VIVOBUS_ERRVLD_errvld_END      (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_VIVOBUS_ERRCLR_UNION
 结构说明  : VIVOBUS_ERRCLR 寄存器结构定义。地址偏移量:0x1C10，初值:0x00000000，宽度:32
 寄存器说明: 中断清除寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errclr   : 1;  /* bit[0-0] : 1.写1'b1清零ErrVld寄存器（如果中断使能，同时也清除中断）；
                                                   2.写1'b1并不能存储在ErrClr寄存器中，读该寄存器，返回总是1'b0。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_VIVOBUS_ERRCLR_UNION;
#endif
#define SOC_VIVO_BUS_VIVOBUS_ERRCLR_errclr_START    (0)
#define SOC_VIVO_BUS_VIVOBUS_ERRCLR_errclr_END      (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_VIVOBUS_ERRLOG0_UNION
 结构说明  : VIVOBUS_ERRLOG0 寄存器结构定义。地址偏移量:0x1C14，初值:0x80000000，宽度:32
 寄存器说明: Error log0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lock     : 1;  /* bit[0]    : 只是Transaction是否为Lock操作，高有效； */
        unsigned int  opc      : 4;  /* bit[1-4]  : Transaction操作类型：
                                                    0-->RD：INCR的读操作；
                                                    1-->RDW：WRAP的读操作；
                                                    2-->RDL：Exclusive 读操作；
                                                    3-->RDX：Lock read；
                                                    4-->WR：INCR写操作；
                                                    5-->WRW：WRAP写操作；
                                                    6-->WRC：Exclusive写操作；
                                                    8-->PRE：FIXED BURST；
                                                    9-->URG：urgency packet，Error Probe不会检测到此类packet；
                                                    其它-->Reserveed：非法操作； */
        unsigned int  reserved_0: 3;  /* bit[5-7]  : 保留 */
        unsigned int  errcode  : 3;  /* bit[8-10] : 错误类型：
                                                    0-->被访问slave返回Error Response；
                                                    1-->master访问了总线的Reserve地址空间；
                                                    2-->master发送了slave不支持的Burst类型（当前总线不会出现这种场景）；
                                                    3-->master访问了掉电区域；
                                                    4-->访问权限报错；
                                                    5-->master访问时，收到Firewall的Hide Error Response；
                                                    6-->被访问slave TimeOut，并返回Error Response；
                                                    7-->none。 */
        unsigned int  reserved_1: 5;  /* bit[11-15]: 保留 */
        unsigned int  len1     : 8;  /* bit[16-23]: 表示出错Transaction的包长，单位为Byte */
        unsigned int  reserved_2: 7;  /* bit[24-30]: 保留 */
        unsigned int  format   : 1;  /* bit[31]   : 用于表示Error log0的格式，FlexNoC2.7以后版本固定为1'b1； */
    } reg;
} SOC_VIVO_BUS_VIVOBUS_ERRLOG0_UNION;
#endif
#define SOC_VIVO_BUS_VIVOBUS_ERRLOG0_lock_START      (0)
#define SOC_VIVO_BUS_VIVOBUS_ERRLOG0_lock_END        (0)
#define SOC_VIVO_BUS_VIVOBUS_ERRLOG0_opc_START       (1)
#define SOC_VIVO_BUS_VIVOBUS_ERRLOG0_opc_END         (4)
#define SOC_VIVO_BUS_VIVOBUS_ERRLOG0_errcode_START   (8)
#define SOC_VIVO_BUS_VIVOBUS_ERRLOG0_errcode_END     (10)
#define SOC_VIVO_BUS_VIVOBUS_ERRLOG0_len1_START      (16)
#define SOC_VIVO_BUS_VIVOBUS_ERRLOG0_len1_END        (23)
#define SOC_VIVO_BUS_VIVOBUS_ERRLOG0_format_START    (31)
#define SOC_VIVO_BUS_VIVOBUS_ERRLOG0_format_END      (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_VIVOBUS_ERRLOG1_UNION
 结构说明  : VIVOBUS_ERRLOG1 寄存器结构定义。地址偏移量:0x1C18，初值:0x00000000，宽度:32
 寄存器说明: Error log1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errlog1  : 14; /* bit[0-13] : RouteId：路由信息，各bit含义如下
                                                    [13:10]-->Initiator Flow ID，用于表示发起访问的master；
                                                    [9:7]-->target Flow ID，用于表示被访问的slave；
                                                    [6:0]-->Seq ID，Transaction标记； */
        unsigned int  reserved : 18; /* bit[14-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_VIVOBUS_ERRLOG1_UNION;
#endif
#define SOC_VIVO_BUS_VIVOBUS_ERRLOG1_errlog1_START   (0)
#define SOC_VIVO_BUS_VIVOBUS_ERRLOG1_errlog1_END     (13)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_VIVOBUS_ERRLOG3_UNION
 结构说明  : VIVOBUS_ERRLOG3 寄存器结构定义。地址偏移量:0x1C20，初值:0x00000000，宽度:32
 寄存器说明: Error log3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errlog3 : 32; /* bit[0-31]: 访问地址值 */
    } reg;
} SOC_VIVO_BUS_VIVOBUS_ERRLOG3_UNION;
#endif
#define SOC_VIVO_BUS_VIVOBUS_ERRLOG3_errlog3_START  (0)
#define SOC_VIVO_BUS_VIVOBUS_ERRLOG3_errlog3_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_VIVOBUS_ERRLOG5_UNION
 结构说明  : VIVOBUS_ERRLOG5 寄存器结构定义。地址偏移量:0x1C28，初值:0x00000000，宽度:32
 寄存器说明: Error log5
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errlog5  : 5;  /* bit[0-4] : User信号值 */
        unsigned int  reserved : 27; /* bit[5-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_VIVOBUS_ERRLOG5_UNION;
#endif
#define SOC_VIVO_BUS_VIVOBUS_ERRLOG5_errlog5_START   (0)
#define SOC_VIVO_BUS_VIVOBUS_ERRLOG5_errlog5_END     (4)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_VIVOBUS_ERRLOG7_UNION
 结构说明  : VIVOBUS_ERRLOG7 寄存器结构定义。地址偏移量:0x1C30，初值:0x00000000，宽度:32
 寄存器说明: Error log7
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errlog7  : 1;  /* bit[0]   : 安全信号值 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_VIVOBUS_ERRLOG7_UNION;
#endif
#define SOC_VIVO_BUS_VIVOBUS_ERRLOG7_errlog7_START   (0)
#define SOC_VIVO_BUS_VIVOBUS_ERRLOG7_errlog7_END     (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_RD_TRANS_F_ID_COREID_UNION
 结构说明  : DSS0_RD_TRANS_F_ID_COREID 寄存器结构定义。地址偏移量:0x8000，初值:0x69B39209，宽度:32
 寄存器说明: DSS0_RD TransactionStatFilter域ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coretypeid   : 8;  /* bit[0-7] : 类型ID */
        unsigned int  corechecksum : 24; /* bit[8-31]: 配置参数的校验和 */
    } reg;
} SOC_VIVO_BUS_DSS0_RD_TRANS_F_ID_COREID_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_RD_TRANS_F_ID_COREID_coretypeid_START    (0)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_F_ID_COREID_coretypeid_END      (7)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_F_ID_COREID_corechecksum_START  (8)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_F_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_RD_TRANS_F_ID_REVISIONID_UNION
 结构说明  : DSS0_RD_TRANS_F_ID_REVISIONID 寄存器结构定义。地址偏移量:0x8004，初值:0x012D5300，宽度:32
 寄存器说明: 代码版本
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  userid    : 8;  /* bit[0-7] : 用户自定义ID */
        unsigned int  flexnocid : 24; /* bit[8-31]: FlexNoC生成代码的软件版本 */
    } reg;
} SOC_VIVO_BUS_DSS0_RD_TRANS_F_ID_REVISIONID_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_RD_TRANS_F_ID_REVISIONID_userid_START     (0)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_F_ID_REVISIONID_userid_END       (7)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_F_ID_REVISIONID_flexnocid_START  (8)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_F_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_RD_TRANS_F_MODE_UNION
 结构说明  : DSS0_RD_TRANS_F_MODE 寄存器结构定义。地址偏移量:0x8008，初值:0x00000000，宽度:32
 寄存器说明: DSS0_RD Transaction Probe的Filter工作模式配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode     : 1;  /* bit[0-0] : 0-->handshake的模式，start event=begin request，end event=accept request；
                                                   1-->latency模式，start event=begin request + context ID，end event=begin response + context ID。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_RD_TRANS_F_MODE_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_RD_TRANS_F_MODE_mode_START      (0)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_F_MODE_mode_END        (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_RD_TRANS_F_ADDRBASE_LOW_UNION
 结构说明  : DSS0_RD_TRANS_F_ADDRBASE_LOW 寄存器结构定义。地址偏移量:0x800C，初值:0x00000000，宽度:32
 寄存器说明: 地址过滤基地址
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addrbase_low : 32; /* bit[0-31]: 地址过滤条件的基地址。 */
    } reg;
} SOC_VIVO_BUS_DSS0_RD_TRANS_F_ADDRBASE_LOW_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_RD_TRANS_F_ADDRBASE_LOW_addrbase_low_START  (0)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_F_ADDRBASE_LOW_addrbase_low_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_RD_TRANS_F_ADDRWINDOWSIZE_UNION
 结构说明  : DSS0_RD_TRANS_F_ADDRWINDOWSIZE 寄存器结构定义。地址偏移量:0x8014，初值:0x00000000，宽度:32
 寄存器说明: 地址过滤窗口
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addrwindowsize : 6;  /* bit[0-5] : 地址过滤的Mask窗口大小。
                                                         例如：地址过滤的Mask窗口大小为64MB，WidowSize=log2(64MB)=26，此时，就配置filter_0_windowsize=0x1A；
                                                         Address Mask=~（2^max(WindowSize,packet.len)-1）=0xFC000000（packet.len为NOC内部表示一个packet包长变量的位宽，其值为6~7）；
                                                         过滤条件为：PacketAddress & AddressMask = AddressBase & AddressMask。 */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_RD_TRANS_F_ADDRWINDOWSIZE_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_RD_TRANS_F_ADDRWINDOWSIZE_addrwindowsize_START  (0)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_F_ADDRWINDOWSIZE_addrwindowsize_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_RD_TRANS_F_OPCODE_UNION
 结构说明  : DSS0_RD_TRANS_F_OPCODE 寄存器结构定义。地址偏移量:0x8020，初值:0x00000000，宽度:32
 寄存器说明: DSS0_RD的Transaction Probe的Opcode过滤条件
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rden     : 1;  /* bit[0-0] : 配置为1时，过滤写数据包； */
        unsigned int  wren     : 1;  /* bit[1-1] : 配置为1时，过滤读数据包； */
        unsigned int  reserved : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_RD_TRANS_F_OPCODE_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_RD_TRANS_F_OPCODE_rden_START      (0)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_F_OPCODE_rden_END        (0)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_F_OPCODE_wren_START      (1)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_F_OPCODE_wren_END        (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_RD_TRANS_F_USERBASE_UNION
 结构说明  : DSS0_RD_TRANS_F_USERBASE 寄存器结构定义。地址偏移量:0x8024，初值:0x00000000，宽度:32
 寄存器说明: DSS0_RD的Transaction Probe的User过滤条件
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  userbase : 5;  /* bit[0-4] : User信号过滤条件 */
        unsigned int  reserved : 27; /* bit[5-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_RD_TRANS_F_USERBASE_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_RD_TRANS_F_USERBASE_userbase_START  (0)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_F_USERBASE_userbase_END    (4)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_RD_TRANS_F_USERMASK_UNION
 结构说明  : DSS0_RD_TRANS_F_USERMASK 寄存器结构定义。地址偏移量:0x8028，初值:0x00000000，宽度:32
 寄存器说明: DSS0_RD的Transaction Probe的User过滤条件Mask
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  usermask : 5;  /* bit[0-4] : 对UserBase进行Mask，选择UserBase中的任意几bit User信号作为过滤条件。
                                                   过滤条件：packet.User & UserMask = UserBase & UserMask。 */
        unsigned int  reserved : 27; /* bit[5-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_RD_TRANS_F_USERMASK_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_RD_TRANS_F_USERMASK_usermask_START  (0)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_F_USERMASK_usermask_END    (4)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_RD_TRANS_F_SECURITYBASE_UNION
 结构说明  : DSS0_RD_TRANS_F_SECURITYBASE 寄存器结构定义。地址偏移量:0x802C，初值:0x00000000，宽度:32
 寄存器说明: DSS0_RD的Transaction Probe的安全过滤条件
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  securitybase : 1;  /* bit[0-0] : 0-->表示安全过滤条件；
                                                       1-->表示非安全过滤条件。 */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_RD_TRANS_F_SECURITYBASE_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_RD_TRANS_F_SECURITYBASE_securitybase_START  (0)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_F_SECURITYBASE_securitybase_END    (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_RD_TRANS_F_SECURITYMASK_UNION
 结构说明  : DSS0_RD_TRANS_F_SECURITYMASK 寄存器结构定义。地址偏移量:0x8030，初值:0x00000000，宽度:32
 寄存器说明: DSS0_RD的Transaction Probe的安全过滤条件Mask
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  securitymask : 1;  /* bit[0-0] : 安全过滤条件：packet.Security & SecurityMask = SecurityBase & SecurityMasks；
                                                       也就是说当Filters_1_SecurityMask=1时安全过滤条件Filters_1_SecurityBase有效，可以过滤安全或非安全packet；否则，不起过滤作用； */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_RD_TRANS_F_SECURITYMASK_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_RD_TRANS_F_SECURITYMASK_securitymask_START  (0)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_F_SECURITYMASK_securitymask_END    (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_RD_TRANS_P_ID_COREID_UNION
 结构说明  : DSS0_RD_TRANS_P_ID_COREID 寄存器结构定义。地址偏移量:0x8080，初值:0xD13C080A，宽度:32
 寄存器说明: DSS0_RD TransactionStatProfilter域ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coretypeid   : 8;  /* bit[0-7] : 类型ID */
        unsigned int  corechecksum : 24; /* bit[8-31]: 配置参数的校验和 */
    } reg;
} SOC_VIVO_BUS_DSS0_RD_TRANS_P_ID_COREID_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_RD_TRANS_P_ID_COREID_coretypeid_START    (0)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_P_ID_COREID_coretypeid_END      (7)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_P_ID_COREID_corechecksum_START  (8)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_P_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_RD_TRANS_P_ID_REVISIONID_UNION
 结构说明  : DSS0_RD_TRANS_P_ID_REVISIONID 寄存器结构定义。地址偏移量:0x8084，初值:0x012D5300，宽度:32
 寄存器说明: 代码版本
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  userid    : 8;  /* bit[0-7] : 用户自定义ID */
        unsigned int  flexnocid : 24; /* bit[8-31]: FlexNoC生成代码的软件版本 */
    } reg;
} SOC_VIVO_BUS_DSS0_RD_TRANS_P_ID_REVISIONID_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_RD_TRANS_P_ID_REVISIONID_userid_START     (0)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_P_ID_REVISIONID_userid_END       (7)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_P_ID_REVISIONID_flexnocid_START  (8)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_P_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_RD_TRANS_P_EN_UNION
 结构说明  : DSS0_RD_TRANS_P_EN 寄存器结构定义。地址偏移量:0x8088，初值:0x00000000，宽度:32
 寄存器说明: transaction Probe的counter使能配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  en       : 1;  /* bit[0-0] : 当配置为1时，使能Transaction Probe的统计计数器 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_RD_TRANS_P_EN_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_RD_TRANS_P_EN_en_START        (0)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_P_EN_en_END          (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_RD_TRANS_P_MODE_UNION
 结构说明  : DSS0_RD_TRANS_P_MODE 寄存器结构定义。地址偏移量:0x808C，初值:0x00000000，宽度:32
 寄存器说明: DSS0_RD Transaction Probe的工作模式配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode     : 1;  /* bit[0]   : 0-->统计latency；
                                                   1-->统计outstanding； */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_RD_TRANS_P_MODE_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_RD_TRANS_P_MODE_mode_START      (0)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_P_MODE_mode_END        (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_RD_TRANS_P_OVERFLOWSTATUS_UNION
 结构说明  : DSS0_RD_TRANS_P_OVERFLOWSTATUS 寄存器结构定义。地址偏移量:0x80EC，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器溢出状态
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  overflowstatus : 1;  /* bit[0-0] : 1表示统计计数器溢出 */
        unsigned int  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_RD_TRANS_P_OVERFLOWSTATUS_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_RD_TRANS_P_OVERFLOWSTATUS_overflowstatus_START  (0)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_P_OVERFLOWSTATUS_overflowstatus_END    (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_RD_TRANS_P_OVERFLOWRESET_UNION
 结构说明  : DSS0_RD_TRANS_P_OVERFLOWRESET 寄存器结构定义。地址偏移量:0x80F0，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器溢出状态清零
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  overflowreset : 1;  /* bit[0-0] : 写1时，OverflowStatus寄存器清零，读该寄存器时钟返回0 */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_RD_TRANS_P_OVERFLOWRESET_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_RD_TRANS_P_OVERFLOWRESET_overflowreset_START  (0)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_P_OVERFLOWRESET_overflowreset_END    (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_RD_TRANS_P_PENDINGEVENTMODE_UNION
 结构说明  : DSS0_RD_TRANS_P_PENDINGEVENTMODE 寄存器结构定义。地址偏移量:0x80F4，初值:0x00000000，宽度:32
 寄存器说明: outstanding统计技术工作模式配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pendingeventmode : 1;  /* bit[0-0] : 0x0-->当outstanding数量 > 0时，每个cycle都去触发计数器收集outstanding个数；
                                                           0x1-->当返回1个response时，就触发计数器收集outstanding个数。 */
        unsigned int  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_RD_TRANS_P_PENDINGEVENTMODE_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_RD_TRANS_P_PENDINGEVENTMODE_pendingeventmode_START  (0)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_P_PENDINGEVENTMODE_pendingeventmode_END    (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_RD_TRANS_P_PRESCALER_UNION
 结构说明  : DSS0_RD_TRANS_P_PRESCALER 寄存器结构定义。地址偏移量:0x80F8，初值:0x00000000，宽度:32
 寄存器说明: latency统计系数配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  prescaler : 8;  /* bit[0-7] : 0-->handshake的模式，start event=begin request，end event=accept request；
                                                    1-->latency模式，start event=begin request + context ID，end event=begin response + context ID。 */
        unsigned int  reserved  : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_RD_TRANS_P_PRESCALER_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_RD_TRANS_P_PRESCALER_prescaler_START  (0)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_P_PRESCALER_prescaler_END    (7)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_RD_TRANS_M_ID_COREID_UNION
 结构说明  : DSS0_RD_TRANS_M_ID_COREID 寄存器结构定义。地址偏移量:0x8400，初值:0xB4235806，宽度:32
 寄存器说明: DSS0_RD Transaction probe域ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_coreid : 32; /* bit[0-31]: VcodecBus的Packet Probe的域ID。 */
    } reg;
} SOC_VIVO_BUS_DSS0_RD_TRANS_M_ID_COREID_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_ID_COREID_id_coreid_START  (0)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_ID_COREID_id_coreid_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_RD_TRANS_M_ID_REVISIONID_UNION
 结构说明  : DSS0_RD_TRANS_M_ID_REVISIONID 寄存器结构定义。地址偏移量:0x8404，初值:0x012D5300，宽度:32
 寄存器说明: 总线代码版本寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_revisionid : 32; /* bit[0-31]: 低8bit自定义，高24bit是NOC的配置HUSH值。 */
    } reg;
} SOC_VIVO_BUS_DSS0_RD_TRANS_M_ID_REVISIONID_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_ID_REVISIONID_id_revisionid_START  (0)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_ID_REVISIONID_id_revisionid_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_RD_TRANS_M_MAINCTL_UNION
 结构说明  : DSS0_RD_TRANS_M_MAINCTL 寄存器结构定义。地址偏移量:0x8408，初值:0x00000000，宽度:32
 寄存器说明: Transaction Probe全局控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  erren                     : 1;  /* bit[0]   : ErrEn：使能Packet Probe将检测到的任何错误状态的Packet上报给Observer。由于本总线的Packet Probe不支持trace功能，故此位无意义。 */
        unsigned int  traceen                   : 1;  /* bit[1]   : TraceEn：该总线不支持Trace功能，故此位无意义。 */
        unsigned int  payloaden                 : 1;  /* bit[2]   : PayloadEn：该总线不支持Trace功能，故此位无意义。 */
        unsigned int  staten                    : 1;  /* bit[3]   : StatEn：统计模型使能寄存器，当StatEn由0配置为1时，统计计数器被清零；当StatEn配置为0时，统计计数器被disabled。 */
        unsigned int  alarmen                   : 1;  /* bit[4]   : AlarmEn：中断使能配置。
                                                                    0-->屏蔽中断；
                                                                    1-->使能中断输出。 */
        unsigned int  statconddump              : 1;  /* bit[5]   : 0-->表示无条件dump统计数据，寄存器counters_m_val的值，实时反映统计计数器的值；
                                                                    1-->表示有条件dump数据，在给定的统计周期内发生out of bounds 事件，才会将统计计数器的值dump至寄存器counters_m_val中。 */
        unsigned int  intrusivemode             : 1;  /* bit[6]   : IntrusiveMode： 该总线不支持Trace功能，故此位无意义。 */
        unsigned int  filtbytealwayschainableen : 1;  /* bit[7]   : FiltByteAlwaysChainableEn：奇数和偶数计数器串行使能的全局配置：
                                                                    0-->不使能，此时，所有侧statistic counters都可以被Map；
                                                                    1-->使能，只有偶数statistic counters才可以被Map。 */
        unsigned int  reserved                  : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_RD_TRANS_M_MAINCTL_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_MAINCTL_erren_START                      (0)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_MAINCTL_erren_END                        (0)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_MAINCTL_traceen_START                    (1)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_MAINCTL_traceen_END                      (1)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_MAINCTL_payloaden_START                  (2)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_MAINCTL_payloaden_END                    (2)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_MAINCTL_staten_START                     (3)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_MAINCTL_staten_END                       (3)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_MAINCTL_alarmen_START                    (4)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_MAINCTL_alarmen_END                      (4)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_MAINCTL_statconddump_START               (5)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_MAINCTL_statconddump_END                 (5)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_MAINCTL_intrusivemode_START              (6)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_MAINCTL_intrusivemode_END                (6)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_MAINCTL_filtbytealwayschainableen_START  (7)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_MAINCTL_filtbytealwayschainableen_END    (7)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_RD_TRANS_M_CFGCTL_UNION
 结构说明  : DSS0_RD_TRANS_M_CFGCTL 寄存器结构定义。地址偏移量:0x840C，初值:0x00000000，宽度:32
 寄存器说明: Packet Probe使能寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  globalen : 1;  /* bit[0]   : GlobalEn：Packet Probe使能信号，高有效。 */
        unsigned int  active   : 1;  /* bit[1]   : Active：Packet Probe的工作状态指示信号。
                                                   0-->当GlobalEn配置为0的几个cycle后，Active被拉低；
                                                   1-->当GlobalEn配置为1时，Active被拉高，此时不允许对Packet Probe进行配置。 */
        unsigned int  reserved : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_RD_TRANS_M_CFGCTL_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_CFGCTL_globalen_START  (0)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_CFGCTL_globalen_END    (0)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_CFGCTL_active_START    (1)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_CFGCTL_active_END      (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_RD_TRANS_M_STATPERIOD_UNION
 结构说明  : DSS0_RD_TRANS_M_STATPERIOD 寄存器结构定义。地址偏移量:0x8424，初值:0x00000000，宽度:32
 寄存器说明: 统计周期配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statperiod : 5;  /* bit[0-4] : 自动统计模式下的统计周期，统计周期= N_Cycle = 2^min(23,StatPeriod)，最大为8 mega cycles，最小为2 cycles。当配置为0时，自动统计模式被关闭，需要采用手动模式，也就是配置StatGo寄存器来实现带宽统计。 */
        unsigned int  reserved   : 27; /* bit[5-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_RD_TRANS_M_STATPERIOD_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_STATPERIOD_statperiod_START  (0)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_STATPERIOD_statperiod_END    (4)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_RD_TRANS_M_STATGO_UNION
 结构说明  : DSS0_RD_TRANS_M_STATGO 寄存器结构定义。地址偏移量:0x8428，初值:0x00000000，宽度:32
 寄存器说明: 手动带宽统计计时开始使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statgo   : 1;  /* bit[0]   : 当StatPeriod=0时，当globalen为1，向寄存器StatGo写1，则会将counter_m_val的值与statalarmmax或statalarmmin的值进行比较；读该寄存器始终返回0。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_RD_TRANS_M_STATGO_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_STATGO_statgo_START    (0)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_STATGO_statgo_END      (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_RD_TRANS_M_STATALARMMIN_UNION
 结构说明  : DSS0_RD_TRANS_M_STATALARMMIN 寄存器结构定义。地址偏移量:0x842C，初值:0x00000000，宽度:32
 寄存器说明: 统计计数最小告警阈值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statalarmmin : 32; /* bit[0-31]: 当任意一个统计计数器的值小于StatAlarmMin的值，就触发告警寄存器。 */
    } reg;
} SOC_VIVO_BUS_DSS0_RD_TRANS_M_STATALARMMIN_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_STATALARMMIN_statalarmmin_START  (0)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_STATALARMMIN_statalarmmin_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_RD_TRANS_M_STATALARMMAX_UNION
 结构说明  : DSS0_RD_TRANS_M_STATALARMMAX 寄存器结构定义。地址偏移量:0x8430，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器最大告警阈值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statalarmmax : 32; /* bit[0-31]: 当任意一个统计计数器的值大于StatAlarmMax的值，就触发告警寄存器。 */
    } reg;
} SOC_VIVO_BUS_DSS0_RD_TRANS_M_STATALARMMAX_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_STATALARMMAX_statalarmmax_START  (0)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_STATALARMMAX_statalarmmax_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_RD_TRANS_M_STATALARMSTATUS_UNION
 结构说明  : DSS0_RD_TRANS_M_STATALARMSTATUS 寄存器结构定义。地址偏移量:0x8434，初值:0x00000000，宽度:32
 寄存器说明: 告警状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statalarmstatus : 1;  /* bit[0]   : 当任意一个统计计数器的值大于StatAlarmMax或小于StatAlarmMin，则该寄存器置位为1； */
        unsigned int  reserved        : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_RD_TRANS_M_STATALARMSTATUS_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_STATALARMSTATUS_statalarmstatus_START  (0)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_STATALARMSTATUS_statalarmstatus_END    (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_RD_TRANS_M_STATALARMCLR_UNION
 结构说明  : DSS0_RD_TRANS_M_STATALARMCLR 寄存器结构定义。地址偏移量:0x8438，初值:0x00000000，宽度:32
 寄存器说明: 告警状态清除寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statalarmclr : 1;  /* bit[0]   : 写1会清零StatAlarmStatus寄存器，读此寄存器返回总是0； */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_RD_TRANS_M_STATALARMCLR_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_STATALARMCLR_statalarmclr_START  (0)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_STATALARMCLR_statalarmclr_END    (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_0_SRC_UNION
 结构说明  : DSS0_RD_TRANS_M_COUNTERS_0_SRC 寄存器结构定义。地址偏移量:0x8538，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_0_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~7）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：8~15）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：16~31）；
                                                         0x23-->Bin 3（delay：128~255；outstanding：32~60）；
                                                         0x24-->Bin 4（delay：>= 256；outstanding：>= 61）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_0_SRC_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_0_SRC_counters_0_src_START  (0)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_0_SRC_counters_0_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_0_ALARMMODE_UNION
 结构说明  : DSS0_RD_TRANS_M_COUNTERS_0_ALARMMODE 寄存器结构定义。地址偏移量:0x853C，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_0_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_0_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_0_ALARMMODE_counters_0_alarmmode_START  (0)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_0_ALARMMODE_counters_0_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_0_VAL_UNION
 结构说明  : DSS0_RD_TRANS_M_COUNTERS_0_VAL 寄存器结构定义。地址偏移量:0x8540，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_0_val : 11; /* bit[0-10] : 当Counters_0_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_0_VAL_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_0_VAL_counters_0_val_START  (0)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_0_VAL_counters_0_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_1_SRC_UNION
 结构说明  : DSS0_RD_TRANS_M_COUNTERS_1_SRC 寄存器结构定义。地址偏移量:0x854C，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_1_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~7）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：8~15）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：16~31）；
                                                         0x23-->Bin 3（delay：128~255；outstanding：32~60）；
                                                         0x24-->Bin 4（delay：>= 256；outstanding：>= 61）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_1_SRC_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_1_SRC_counters_1_src_START  (0)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_1_SRC_counters_1_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_1_ALARMMODE_UNION
 结构说明  : DSS0_RD_TRANS_M_COUNTERS_1_ALARMMODE 寄存器结构定义。地址偏移量:0x8550，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_1_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_1_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_1_ALARMMODE_counters_1_alarmmode_START  (0)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_1_ALARMMODE_counters_1_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_1_VAL_UNION
 结构说明  : DSS0_RD_TRANS_M_COUNTERS_1_VAL 寄存器结构定义。地址偏移量:0x8554，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_1_val : 11; /* bit[0-10] : 当Counters_1_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_1_VAL_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_1_VAL_counters_1_val_START  (0)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_1_VAL_counters_1_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_2_SRC_UNION
 结构说明  : DSS0_RD_TRANS_M_COUNTERS_2_SRC 寄存器结构定义。地址偏移量:0x8560，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_2_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~7）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：8~15）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：16~31）；
                                                         0x23-->Bin 3（delay：128~255；outstanding：32~60）；
                                                         0x24-->Bin 4（delay：>= 256；outstanding：>= 61）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_2_SRC_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_2_SRC_counters_2_src_START  (0)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_2_SRC_counters_2_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_2_ALARMMODE_UNION
 结构说明  : DSS0_RD_TRANS_M_COUNTERS_2_ALARMMODE 寄存器结构定义。地址偏移量:0x8564，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_2_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_2_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_2_ALARMMODE_counters_2_alarmmode_START  (0)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_2_ALARMMODE_counters_2_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_2_VAL_UNION
 结构说明  : DSS0_RD_TRANS_M_COUNTERS_2_VAL 寄存器结构定义。地址偏移量:0x8568，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_2_val : 11; /* bit[0-10] : 当Counters_2_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_2_VAL_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_2_VAL_counters_2_val_START  (0)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_2_VAL_counters_2_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_3_SRC_UNION
 结构说明  : DSS0_RD_TRANS_M_COUNTERS_3_SRC 寄存器结构定义。地址偏移量:0x8574，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_3_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~7）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：8~15）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：16~31）；
                                                         0x23-->Bin 3（delay：128~255；outstanding：32~60）；
                                                         0x24-->Bin 4（delay：>= 256；outstanding：>= 61）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_3_SRC_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_3_SRC_counters_3_src_START  (0)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_3_SRC_counters_3_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_3_ALARMMODE_UNION
 结构说明  : DSS0_RD_TRANS_M_COUNTERS_3_ALARMMODE 寄存器结构定义。地址偏移量:0x8578，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_3_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_3_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_3_ALARMMODE_counters_3_alarmmode_START  (0)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_3_ALARMMODE_counters_3_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_3_VAL_UNION
 结构说明  : DSS0_RD_TRANS_M_COUNTERS_3_VAL 寄存器结构定义。地址偏移量:0x857C，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_3_val : 11; /* bit[0-10] : 当Counters_3_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_3_VAL_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_3_VAL_counters_3_val_START  (0)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_3_VAL_counters_3_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_4_SRC_UNION
 结构说明  : DSS0_RD_TRANS_M_COUNTERS_4_SRC 寄存器结构定义。地址偏移量:0x8588，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_4_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~7）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：8~15）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：16~31）；
                                                         0x23-->Bin 3（delay：128~255；outstanding：32~60）；
                                                         0x24-->Bin 4（delay：>= 256；outstanding：>= 61）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_4_SRC_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_4_SRC_counters_4_src_START  (0)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_4_SRC_counters_4_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_4_ALARMMODE_UNION
 结构说明  : DSS0_RD_TRANS_M_COUNTERS_4_ALARMMODE 寄存器结构定义。地址偏移量:0x858C，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_4_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_4_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_4_ALARMMODE_counters_4_alarmmode_START  (0)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_4_ALARMMODE_counters_4_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_4_VAL_UNION
 结构说明  : DSS0_RD_TRANS_M_COUNTERS_4_VAL 寄存器结构定义。地址偏移量:0x8590，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_4_val : 11; /* bit[0-10] : 当Counters_4_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_4_VAL_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_4_VAL_counters_4_val_START  (0)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_4_VAL_counters_4_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_5_SRC_UNION
 结构说明  : DSS0_RD_TRANS_M_COUNTERS_5_SRC 寄存器结构定义。地址偏移量:0x859C，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_5_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~7）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：8~15）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：16~31）；
                                                         0x23-->Bin 3（delay：128~255；outstanding：32~60）；
                                                         0x24-->Bin 4（delay：>= 256；outstanding：>= 61）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_5_SRC_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_5_SRC_counters_5_src_START  (0)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_5_SRC_counters_5_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_5_ALARMMODE_UNION
 结构说明  : DSS0_RD_TRANS_M_COUNTERS_5_ALARMMODE 寄存器结构定义。地址偏移量:0x85A0，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_5_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_5_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_5_ALARMMODE_counters_5_alarmmode_START  (0)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_5_ALARMMODE_counters_5_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_5_VAL_UNION
 结构说明  : DSS0_RD_TRANS_M_COUNTERS_5_VAL 寄存器结构定义。地址偏移量:0x85A4，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_5_val : 11; /* bit[0-10] : 当Counters_5_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_5_VAL_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_5_VAL_counters_5_val_START  (0)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_5_VAL_counters_5_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_6_SRC_UNION
 结构说明  : DSS0_RD_TRANS_M_COUNTERS_6_SRC 寄存器结构定义。地址偏移量:0x85B0，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_6_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~7）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：8~15）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：16~31）；
                                                         0x23-->Bin 3（delay：128~255；outstanding：32~60）；
                                                         0x24-->Bin 4（delay：>= 256；outstanding：>= 61）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_6_SRC_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_6_SRC_counters_6_src_START  (0)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_6_SRC_counters_6_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_6_ALARMMODE_UNION
 结构说明  : DSS0_RD_TRANS_M_COUNTERS_6_ALARMMODE 寄存器结构定义。地址偏移量:0x85B4，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_6_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_6_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_6_ALARMMODE_counters_6_alarmmode_START  (0)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_6_ALARMMODE_counters_6_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_6_VAL_UNION
 结构说明  : DSS0_RD_TRANS_M_COUNTERS_6_VAL 寄存器结构定义。地址偏移量:0x85B8，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_6_val : 11; /* bit[0-10] : 当Counters_6_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_6_VAL_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_6_VAL_counters_6_val_START  (0)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_6_VAL_counters_6_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_7_SRC_UNION
 结构说明  : DSS0_RD_TRANS_M_COUNTERS_7_SRC 寄存器结构定义。地址偏移量:0x85C4，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_7_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~7）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：8~15）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：16~31）；
                                                         0x23-->Bin 3（delay：128~255；outstanding：32~60）；
                                                         0x24-->Bin 4（delay：>= 256；outstanding：>= 61）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_7_SRC_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_7_SRC_counters_7_src_START  (0)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_7_SRC_counters_7_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_7_ALARMMODE_UNION
 结构说明  : DSS0_RD_TRANS_M_COUNTERS_7_ALARMMODE 寄存器结构定义。地址偏移量:0x85C8，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_7_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_7_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_7_ALARMMODE_counters_7_alarmmode_START  (0)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_7_ALARMMODE_counters_7_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_7_VAL_UNION
 结构说明  : DSS0_RD_TRANS_M_COUNTERS_7_VAL 寄存器结构定义。地址偏移量:0x85CC，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_7_val : 11; /* bit[0-10] : 当Counters_7_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_7_VAL_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_7_VAL_counters_7_val_START  (0)
#define SOC_VIVO_BUS_DSS0_RD_TRANS_M_COUNTERS_7_VAL_counters_7_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_TRANS_F_ID_COREID_UNION
 结构说明  : DSS0_WR_TRANS_F_ID_COREID 寄存器结构定义。地址偏移量:0x9000，初值:0xD750AA09，宽度:32
 寄存器说明: DSS0_WR TransactionStatFilter域ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coretypeid   : 8;  /* bit[0-7] : 类型ID */
        unsigned int  corechecksum : 24; /* bit[8-31]: 配置参数的校验和 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_TRANS_F_ID_COREID_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_TRANS_F_ID_COREID_coretypeid_START    (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_F_ID_COREID_coretypeid_END      (7)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_F_ID_COREID_corechecksum_START  (8)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_F_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_TRANS_F_ID_REVISIONID_UNION
 结构说明  : DSS0_WR_TRANS_F_ID_REVISIONID 寄存器结构定义。地址偏移量:0x9004，初值:0x012D5300，宽度:32
 寄存器说明: 代码版本
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  userid    : 8;  /* bit[0-7] : 用户自定义ID */
        unsigned int  flexnocid : 24; /* bit[8-31]: FlexNoC生成代码的软件版本 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_TRANS_F_ID_REVISIONID_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_TRANS_F_ID_REVISIONID_userid_START     (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_F_ID_REVISIONID_userid_END       (7)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_F_ID_REVISIONID_flexnocid_START  (8)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_F_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_TRANS_F_MODE_UNION
 结构说明  : DSS0_WR_TRANS_F_MODE 寄存器结构定义。地址偏移量:0x9008，初值:0x00000000，宽度:32
 寄存器说明: DSS0_WR Transaction Probe的Filter工作模式配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode     : 1;  /* bit[0-0] : 0-->handshake的模式，start event=begin request，end event=accept request；
                                                   1-->latency模式，start event=begin request + context ID，end event=begin response + context ID。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_TRANS_F_MODE_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_TRANS_F_MODE_mode_START      (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_F_MODE_mode_END        (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_TRANS_F_ADDRBASE_LOW_UNION
 结构说明  : DSS0_WR_TRANS_F_ADDRBASE_LOW 寄存器结构定义。地址偏移量:0x900C，初值:0x00000000，宽度:32
 寄存器说明: 地址过滤基地址
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addrbase_low : 32; /* bit[0-31]: 地址过滤条件的基地址。 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_TRANS_F_ADDRBASE_LOW_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_TRANS_F_ADDRBASE_LOW_addrbase_low_START  (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_F_ADDRBASE_LOW_addrbase_low_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_TRANS_F_ADDRBASE_HIGH_UNION
 结构说明  : DSS0_WR_TRANS_F_ADDRBASE_HIGH 寄存器结构定义。地址偏移量:0x9010，初值:0x00000000，宽度:32
 寄存器说明: 地址过滤基地址
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addrbase_high : 2;  /* bit[0-1] : 地址过滤条件的基地址。 */
        unsigned int  reserved      : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_TRANS_F_ADDRBASE_HIGH_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_TRANS_F_ADDRBASE_HIGH_addrbase_high_START  (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_F_ADDRBASE_HIGH_addrbase_high_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_TRANS_F_ADDRWINDOWSIZE_UNION
 结构说明  : DSS0_WR_TRANS_F_ADDRWINDOWSIZE 寄存器结构定义。地址偏移量:0x9014，初值:0x00000000，宽度:32
 寄存器说明: 地址过滤窗口
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addrwindowsize : 6;  /* bit[0-5] : 地址过滤的Mask窗口大小。
                                                         例如：地址过滤的Mask窗口大小为64MB，WidowSize=log2(64MB)=26，此时，就配置filter_0_windowsize=0x1A；
                                                         Address Mask=~（2^max(WindowSize,packet.len)-1）=0xFC000000（packet.len为NOC内部表示一个packet包长变量的位宽，其值为6~7）；
                                                         过滤条件为：PacketAddress & AddressMask = AddressBase & AddressMask。 */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_TRANS_F_ADDRWINDOWSIZE_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_TRANS_F_ADDRWINDOWSIZE_addrwindowsize_START  (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_F_ADDRWINDOWSIZE_addrwindowsize_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_TRANS_F_OPCODE_UNION
 结构说明  : DSS0_WR_TRANS_F_OPCODE 寄存器结构定义。地址偏移量:0x9020，初值:0x00000000，宽度:32
 寄存器说明: DSS0_WR的Transaction Probe的Opcode过滤条件
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rden     : 1;  /* bit[0-0] : 配置为1时，过滤写数据包； */
        unsigned int  wren     : 1;  /* bit[1-1] : 配置为1时，过滤读数据包； */
        unsigned int  reserved : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_TRANS_F_OPCODE_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_TRANS_F_OPCODE_rden_START      (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_F_OPCODE_rden_END        (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_F_OPCODE_wren_START      (1)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_F_OPCODE_wren_END        (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_TRANS_F_USERBASE_UNION
 结构说明  : DSS0_WR_TRANS_F_USERBASE 寄存器结构定义。地址偏移量:0x9024，初值:0x00000000，宽度:32
 寄存器说明: DSS0_WR的Transaction Probe的User过滤条件
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  userbase : 5;  /* bit[0-4] : User信号过滤条件 */
        unsigned int  reserved : 27; /* bit[5-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_TRANS_F_USERBASE_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_TRANS_F_USERBASE_userbase_START  (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_F_USERBASE_userbase_END    (4)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_TRANS_F_USERMASK_UNION
 结构说明  : DSS0_WR_TRANS_F_USERMASK 寄存器结构定义。地址偏移量:0x9028，初值:0x00000000，宽度:32
 寄存器说明: DSS0_WR的Transaction Probe的User过滤条件Mask
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  usermask : 5;  /* bit[0-4] : 对UserBase进行Mask，选择UserBase中的任意几bit User信号作为过滤条件。
                                                   过滤条件：packet.User & UserMask = UserBase & UserMask。 */
        unsigned int  reserved : 27; /* bit[5-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_TRANS_F_USERMASK_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_TRANS_F_USERMASK_usermask_START  (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_F_USERMASK_usermask_END    (4)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_TRANS_F_SECURITYBASE_UNION
 结构说明  : DSS0_WR_TRANS_F_SECURITYBASE 寄存器结构定义。地址偏移量:0x902C，初值:0x00000000，宽度:32
 寄存器说明: DSS0_WR的Transaction Probe的安全过滤条件
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  securitybase : 1;  /* bit[0-0] : 0-->表示安全过滤条件；
                                                       1-->表示非安全过滤条件。 */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_TRANS_F_SECURITYBASE_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_TRANS_F_SECURITYBASE_securitybase_START  (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_F_SECURITYBASE_securitybase_END    (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_TRANS_F_SECURITYMASK_UNION
 结构说明  : DSS0_WR_TRANS_F_SECURITYMASK 寄存器结构定义。地址偏移量:0x9030，初值:0x00000000，宽度:32
 寄存器说明: DSS0_WR的Transaction Probe的安全过滤条件Mask
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  securitymask : 1;  /* bit[0-0] : 安全过滤条件：packet.Security & SecurityMask = SecurityBase & SecurityMasks；
                                                       也就是说当Filters_1_SecurityMask=1时安全过滤条件Filters_1_SecurityBase有效，可以过滤安全或非安全packet；否则，不起过滤作用； */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_TRANS_F_SECURITYMASK_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_TRANS_F_SECURITYMASK_securitymask_START  (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_F_SECURITYMASK_securitymask_END    (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_TRANS_P_ID_COREID_UNION
 结构说明  : DSS0_WR_TRANS_P_ID_COREID 寄存器结构定义。地址偏移量:0x9080，初值:0x35478E0A，宽度:32
 寄存器说明: DSS0_WR TransactionStatProfilter域ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coretypeid   : 8;  /* bit[0-7] : 类型ID */
        unsigned int  corechecksum : 24; /* bit[8-31]: 配置参数的校验和 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_TRANS_P_ID_COREID_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_TRANS_P_ID_COREID_coretypeid_START    (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_P_ID_COREID_coretypeid_END      (7)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_P_ID_COREID_corechecksum_START  (8)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_P_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_TRANS_P_ID_REVISIONID_UNION
 结构说明  : DSS0_WR_TRANS_P_ID_REVISIONID 寄存器结构定义。地址偏移量:0x9084，初值:0x012D5300，宽度:32
 寄存器说明: 代码版本
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  userid    : 8;  /* bit[0-7] : 用户自定义ID */
        unsigned int  flexnocid : 24; /* bit[8-31]: FlexNoC生成代码的软件版本 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_TRANS_P_ID_REVISIONID_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_TRANS_P_ID_REVISIONID_userid_START     (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_P_ID_REVISIONID_userid_END       (7)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_P_ID_REVISIONID_flexnocid_START  (8)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_P_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_TRANS_P_EN_UNION
 结构说明  : DSS0_WR_TRANS_P_EN 寄存器结构定义。地址偏移量:0x9088，初值:0x00000000，宽度:32
 寄存器说明: transaction Probe的counter使能配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  en       : 1;  /* bit[0-0] : 当配置为1时，使能Transaction Probe的统计计数器 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_TRANS_P_EN_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_TRANS_P_EN_en_START        (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_P_EN_en_END          (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_TRANS_P_MODE_UNION
 结构说明  : DSS0_WR_TRANS_P_MODE 寄存器结构定义。地址偏移量:0x908C，初值:0x00000000，宽度:32
 寄存器说明: DSS0_WR Transaction Probe的工作模式配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode     : 1;  /* bit[0]   : 0-->统计latency；
                                                   1-->统计outstanding； */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_TRANS_P_MODE_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_TRANS_P_MODE_mode_START      (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_P_MODE_mode_END        (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_TRANS_P_THRESHOLDS_0_0_UNION
 结构说明  : DSS0_WR_TRANS_P_THRESHOLDS_0_0 寄存器结构定义。地址偏移量:0x90AC，初值:0x00000000，宽度:32
 寄存器说明: DSS0_WR Transaction Probe的bin_0配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  thresholds_0_0 : 2;  /* bit[0-1] : 0x0-->选择threshold_0（delay：40；outstanding：2）；
                                                         0x1-->选择threshold_1（delay：96；outstanding：4）；
                                                         0x2-->选择threshold_2（delay：128；outstanding：8）；
                                                         0x3-->选择threshold_3（delay：256；outstanding：16）； */
        unsigned int  reserved       : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_TRANS_P_THRESHOLDS_0_0_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_TRANS_P_THRESHOLDS_0_0_thresholds_0_0_START  (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_P_THRESHOLDS_0_0_thresholds_0_0_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_TRANS_P_THRESHOLDS_0_1_UNION
 结构说明  : DSS0_WR_TRANS_P_THRESHOLDS_0_1 寄存器结构定义。地址偏移量:0x90B0，初值:0x00000000，宽度:32
 寄存器说明: DSS0_WR Transaction Probe的bin_0配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  thresholds_0_1 : 2;  /* bit[0-1] : 0x0-->选择threshold_0（delay：40；outstanding：2）；
                                                         0x1-->选择threshold_1（delay：96；outstanding：4）；
                                                         0x2-->选择threshold_2（delay：128；outstanding：8）；
                                                         0x3-->选择threshold_3（delay：256；outstanding：16）； */
        unsigned int  reserved       : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_TRANS_P_THRESHOLDS_0_1_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_TRANS_P_THRESHOLDS_0_1_thresholds_0_1_START  (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_P_THRESHOLDS_0_1_thresholds_0_1_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_TRANS_P_THRESHOLDS_0_2_UNION
 结构说明  : DSS0_WR_TRANS_P_THRESHOLDS_0_2 寄存器结构定义。地址偏移量:0x90B4，初值:0x00000000，宽度:32
 寄存器说明: DSS0_WR Transaction Probe的bin_0配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  thresholds_0_2 : 2;  /* bit[0-1] : 0x0-->选择threshold_0（delay：40；outstanding：2）；
                                                         0x1-->选择threshold_1（delay：96；outstanding：4）；
                                                         0x2-->选择threshold_2（delay：128；outstanding：8）；
                                                         0x3-->选择threshold_3（delay：256；outstanding：16）； */
        unsigned int  reserved       : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_TRANS_P_THRESHOLDS_0_2_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_TRANS_P_THRESHOLDS_0_2_thresholds_0_2_START  (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_P_THRESHOLDS_0_2_thresholds_0_2_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_TRANS_P_THRESHOLDS_0_3_UNION
 结构说明  : DSS0_WR_TRANS_P_THRESHOLDS_0_3 寄存器结构定义。地址偏移量:0x90B8，初值:0x00000000，宽度:32
 寄存器说明: DSS0_WR Transaction Probe的bin_0配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  thresholds_0_3 : 2;  /* bit[0-1] : 0x0-->选择threshold_0（delay：40；outstanding：2）；
                                                         0x1-->选择threshold_1（delay：96；outstanding：4）；
                                                         0x2-->选择threshold_2（delay：128；outstanding：8）；
                                                         0x3-->选择threshold_3（delay：256；outstanding：16）； */
        unsigned int  reserved       : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_TRANS_P_THRESHOLDS_0_3_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_TRANS_P_THRESHOLDS_0_3_thresholds_0_3_START  (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_P_THRESHOLDS_0_3_thresholds_0_3_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_TRANS_P_OVERFLOWSTATUS_UNION
 结构说明  : DSS0_WR_TRANS_P_OVERFLOWSTATUS 寄存器结构定义。地址偏移量:0x90EC，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器溢出状态
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  overflowstatus : 1;  /* bit[0-0] : 1表示统计计数器溢出 */
        unsigned int  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_TRANS_P_OVERFLOWSTATUS_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_TRANS_P_OVERFLOWSTATUS_overflowstatus_START  (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_P_OVERFLOWSTATUS_overflowstatus_END    (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_TRANS_P_OVERFLOWRESET_UNION
 结构说明  : DSS0_WR_TRANS_P_OVERFLOWRESET 寄存器结构定义。地址偏移量:0x90F0，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器溢出状态清零
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  overflowreset : 1;  /* bit[0-0] : 写1时，OverflowStatus寄存器清零，读该寄存器时钟返回0 */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_TRANS_P_OVERFLOWRESET_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_TRANS_P_OVERFLOWRESET_overflowreset_START  (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_P_OVERFLOWRESET_overflowreset_END    (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_TRANS_P_PENDINGEVENTMODE_UNION
 结构说明  : DSS0_WR_TRANS_P_PENDINGEVENTMODE 寄存器结构定义。地址偏移量:0x90F4，初值:0x00000000，宽度:32
 寄存器说明: outstanding统计技术工作模式配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pendingeventmode : 1;  /* bit[0-0] : 0x0-->当outstanding数量 > 0时，每个cycle都去触发计数器收集outstanding个数；
                                                           0x1-->当返回1个response时，就触发计数器收集outstanding个数。 */
        unsigned int  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_TRANS_P_PENDINGEVENTMODE_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_TRANS_P_PENDINGEVENTMODE_pendingeventmode_START  (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_P_PENDINGEVENTMODE_pendingeventmode_END    (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_TRANS_P_PRESCALER_UNION
 结构说明  : DSS0_WR_TRANS_P_PRESCALER 寄存器结构定义。地址偏移量:0x90F8，初值:0x00000000，宽度:32
 寄存器说明: latency统计系数配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  prescaler : 8;  /* bit[0-7] : 在统计latency时，将统计值除以PreScaler的值，PreScaler取值范围1~255，当配置为0时，表示disable该功能；
                                                    在配置PreScaler的值时，需要先配置En寄存器为0，即disable Transaction Probe； */
        unsigned int  reserved  : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_TRANS_P_PRESCALER_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_TRANS_P_PRESCALER_prescaler_START  (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_P_PRESCALER_prescaler_END    (7)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_TRANS_M_ID_COREID_UNION
 结构说明  : DSS0_WR_TRANS_M_ID_COREID 寄存器结构定义。地址偏移量:0x9400，初值:0x0037A206，宽度:32
 寄存器说明: DSS0_WR Transaction probe域ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_coreid : 32; /* bit[0-31]: VcodecBus的Packet Probe的域ID。 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_TRANS_M_ID_COREID_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_ID_COREID_id_coreid_START  (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_ID_COREID_id_coreid_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_TRANS_M_ID_REVISIONID_UNION
 结构说明  : DSS0_WR_TRANS_M_ID_REVISIONID 寄存器结构定义。地址偏移量:0x9404，初值:0x012D5300，宽度:32
 寄存器说明: 总线代码版本寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_revisionid : 32; /* bit[0-31]: 低8bit自定义，高24bit是NOC的配置HUSH值。 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_TRANS_M_ID_REVISIONID_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_ID_REVISIONID_id_revisionid_START  (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_ID_REVISIONID_id_revisionid_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_TRANS_M_MAINCTL_UNION
 结构说明  : DSS0_WR_TRANS_M_MAINCTL 寄存器结构定义。地址偏移量:0x9408，初值:0x00000000，宽度:32
 寄存器说明: Transaction Probe全局控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  erren                     : 1;  /* bit[0]   : ErrEn：使能Packet Probe将检测到的任何错误状态的Packet上报给Observer。由于本总线的Packet Probe不支持trace功能，故此位无意义。 */
        unsigned int  traceen                   : 1;  /* bit[1]   : TraceEn：该总线不支持Trace功能，故此位无意义。 */
        unsigned int  payloaden                 : 1;  /* bit[2]   : PayloadEn：该总线不支持Trace功能，故此位无意义。 */
        unsigned int  staten                    : 1;  /* bit[3]   : StatEn：统计模型使能寄存器，当StatEn由0配置为1时，统计计数器被清零；当StatEn配置为0时，统计计数器被disabled。 */
        unsigned int  alarmen                   : 1;  /* bit[4]   : AlarmEn：中断使能配置。
                                                                    0-->屏蔽中断；
                                                                    1-->使能中断输出。 */
        unsigned int  statconddump              : 1;  /* bit[5]   : 0-->表示无条件dump统计数据，寄存器counters_m_val的值，实时反映统计计数器的值；
                                                                    1-->表示有条件dump数据，在给定的统计周期内发生out of bounds 事件，才会将统计计数器的值dump至寄存器counters_m_val中。 */
        unsigned int  intrusivemode             : 1;  /* bit[6]   : IntrusiveMode： 该总线不支持Trace功能，故此位无意义。 */
        unsigned int  filtbytealwayschainableen : 1;  /* bit[7]   : FiltByteAlwaysChainableEn：奇数和偶数计数器串行使能的全局配置：
                                                                    0-->不使能，此时，所有侧statistic counters都可以被Map；
                                                                    1-->使能，只有偶数statistic counters才可以被Map。 */
        unsigned int  reserved                  : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_TRANS_M_MAINCTL_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_MAINCTL_erren_START                      (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_MAINCTL_erren_END                        (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_MAINCTL_traceen_START                    (1)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_MAINCTL_traceen_END                      (1)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_MAINCTL_payloaden_START                  (2)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_MAINCTL_payloaden_END                    (2)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_MAINCTL_staten_START                     (3)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_MAINCTL_staten_END                       (3)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_MAINCTL_alarmen_START                    (4)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_MAINCTL_alarmen_END                      (4)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_MAINCTL_statconddump_START               (5)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_MAINCTL_statconddump_END                 (5)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_MAINCTL_intrusivemode_START              (6)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_MAINCTL_intrusivemode_END                (6)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_MAINCTL_filtbytealwayschainableen_START  (7)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_MAINCTL_filtbytealwayschainableen_END    (7)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_TRANS_M_CFGCTL_UNION
 结构说明  : DSS0_WR_TRANS_M_CFGCTL 寄存器结构定义。地址偏移量:0x940C，初值:0x00000000，宽度:32
 寄存器说明: Packet Probe使能寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  globalen : 1;  /* bit[0]   : GlobalEn：Packet Probe使能信号，高有效。 */
        unsigned int  active   : 1;  /* bit[1]   : Active：Packet Probe的工作状态指示信号。
                                                   0-->当GlobalEn配置为0的几个cycle后，Active被拉低；
                                                   1-->当GlobalEn配置为1时，Active被拉高，此时不允许对Packet Probe进行配置。 */
        unsigned int  reserved : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_TRANS_M_CFGCTL_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_CFGCTL_globalen_START  (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_CFGCTL_globalen_END    (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_CFGCTL_active_START    (1)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_CFGCTL_active_END      (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_TRANS_M_STATPERIOD_UNION
 结构说明  : DSS0_WR_TRANS_M_STATPERIOD 寄存器结构定义。地址偏移量:0x9424，初值:0x00000000，宽度:32
 寄存器说明: 统计周期配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statperiod : 5;  /* bit[0-4] : 自动统计模式下的统计周期，统计周期= N_Cycle = 2^min(23,StatPeriod)，最大为8 mega cycles，最小为2 cycles。当配置为0时，自动统计模式被关闭，需要采用手动模式，也就是配置StatGo寄存器来实现带宽统计。 */
        unsigned int  reserved   : 27; /* bit[5-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_TRANS_M_STATPERIOD_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_STATPERIOD_statperiod_START  (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_STATPERIOD_statperiod_END    (4)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_TRANS_M_STATGO_UNION
 结构说明  : DSS0_WR_TRANS_M_STATGO 寄存器结构定义。地址偏移量:0x9428，初值:0x00000000，宽度:32
 寄存器说明: 手动带宽统计计时开始使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statgo   : 1;  /* bit[0]   : 当StatPeriod=0时，当globalen为1，向寄存器StatGo写1，则会将counter_m_val的值与statalarmmax或statalarmmin的值进行比较；读该寄存器始终返回0。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_TRANS_M_STATGO_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_STATGO_statgo_START    (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_STATGO_statgo_END      (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_TRANS_M_STATALARMMIN_UNION
 结构说明  : DSS0_WR_TRANS_M_STATALARMMIN 寄存器结构定义。地址偏移量:0x942C，初值:0x00000000，宽度:32
 寄存器说明: 统计计数最小告警阈值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statalarmmin : 32; /* bit[0-31]: 当任意一个统计计数器的值小于StatAlarmMin的值，就触发告警寄存器。 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_TRANS_M_STATALARMMIN_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_STATALARMMIN_statalarmmin_START  (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_STATALARMMIN_statalarmmin_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_TRANS_M_STATALARMMAX_UNION
 结构说明  : DSS0_WR_TRANS_M_STATALARMMAX 寄存器结构定义。地址偏移量:0x9430，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器最大告警阈值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statalarmmax : 32; /* bit[0-31]: 当任意一个统计计数器的值大于StatAlarmMax的值，就触发告警寄存器。 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_TRANS_M_STATALARMMAX_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_STATALARMMAX_statalarmmax_START  (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_STATALARMMAX_statalarmmax_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_TRANS_M_STATALARMSTATUS_UNION
 结构说明  : DSS0_WR_TRANS_M_STATALARMSTATUS 寄存器结构定义。地址偏移量:0x9434，初值:0x00000000，宽度:32
 寄存器说明: 告警状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statalarmstatus : 1;  /* bit[0]   : 当任意一个统计计数器的值大于StatAlarmMax或小于StatAlarmMin，则该寄存器置位为1； */
        unsigned int  reserved        : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_TRANS_M_STATALARMSTATUS_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_STATALARMSTATUS_statalarmstatus_START  (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_STATALARMSTATUS_statalarmstatus_END    (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_TRANS_M_STATALARMCLR_UNION
 结构说明  : DSS0_WR_TRANS_M_STATALARMCLR 寄存器结构定义。地址偏移量:0x9438，初值:0x00000000，宽度:32
 寄存器说明: 告警状态清除寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statalarmclr : 1;  /* bit[0]   : 写1会清零StatAlarmStatus寄存器，读此寄存器返回总是0； */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_TRANS_M_STATALARMCLR_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_STATALARMCLR_statalarmclr_START  (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_STATALARMCLR_statalarmclr_END    (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_0_SRC_UNION
 结构说明  : DSS0_WR_TRANS_M_COUNTERS_0_SRC 寄存器结构定义。地址偏移量:0x9538，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_0_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：2~3）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：4~7）；
                                                         0x23-->Bin 3（delay：128~255；outstanding：8~15）；
                                                         0x24-->Bin 4（delay：>= 256；outstanding：>= 16）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_0_SRC_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_0_SRC_counters_0_src_START  (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_0_SRC_counters_0_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_0_ALARMMODE_UNION
 结构说明  : DSS0_WR_TRANS_M_COUNTERS_0_ALARMMODE 寄存器结构定义。地址偏移量:0x953C，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_0_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_0_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_0_ALARMMODE_counters_0_alarmmode_START  (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_0_ALARMMODE_counters_0_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_0_VAL_UNION
 结构说明  : DSS0_WR_TRANS_M_COUNTERS_0_VAL 寄存器结构定义。地址偏移量:0x9540，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_0_val : 11; /* bit[0-10] : 当Counters_0_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_0_VAL_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_0_VAL_counters_0_val_START  (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_0_VAL_counters_0_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_1_SRC_UNION
 结构说明  : DSS0_WR_TRANS_M_COUNTERS_1_SRC 寄存器结构定义。地址偏移量:0x954C，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_1_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：2~3）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：4~7）；
                                                         0x23-->Bin 3（delay：128~255；outstanding：8~15）；
                                                         0x24-->Bin 4（delay：>= 256；outstanding：>= 16）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_1_SRC_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_1_SRC_counters_1_src_START  (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_1_SRC_counters_1_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_1_ALARMMODE_UNION
 结构说明  : DSS0_WR_TRANS_M_COUNTERS_1_ALARMMODE 寄存器结构定义。地址偏移量:0x9550，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_1_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_1_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_1_ALARMMODE_counters_1_alarmmode_START  (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_1_ALARMMODE_counters_1_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_1_VAL_UNION
 结构说明  : DSS0_WR_TRANS_M_COUNTERS_1_VAL 寄存器结构定义。地址偏移量:0x9554，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_1_val : 11; /* bit[0-10] : 当Counters_1_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_1_VAL_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_1_VAL_counters_1_val_START  (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_1_VAL_counters_1_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_2_SRC_UNION
 结构说明  : DSS0_WR_TRANS_M_COUNTERS_2_SRC 寄存器结构定义。地址偏移量:0x9560，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_2_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：2~3）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：4~7）；
                                                         0x23-->Bin 3（delay：128~255；outstanding：8~15）；
                                                         0x24-->Bin 4（delay：>= 256；outstanding：>= 16）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_2_SRC_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_2_SRC_counters_2_src_START  (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_2_SRC_counters_2_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_2_ALARMMODE_UNION
 结构说明  : DSS0_WR_TRANS_M_COUNTERS_2_ALARMMODE 寄存器结构定义。地址偏移量:0x9564，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_2_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_2_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_2_ALARMMODE_counters_2_alarmmode_START  (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_2_ALARMMODE_counters_2_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_2_VAL_UNION
 结构说明  : DSS0_WR_TRANS_M_COUNTERS_2_VAL 寄存器结构定义。地址偏移量:0x9568，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_2_val : 11; /* bit[0-10] : 当Counters_2_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_2_VAL_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_2_VAL_counters_2_val_START  (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_2_VAL_counters_2_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_3_SRC_UNION
 结构说明  : DSS0_WR_TRANS_M_COUNTERS_3_SRC 寄存器结构定义。地址偏移量:0x9574，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_3_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：2~3）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：4~7）；
                                                         0x23-->Bin 3（delay：128~255；outstanding：8~15）；
                                                         0x24-->Bin 4（delay：>= 256；outstanding：>= 16）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_3_SRC_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_3_SRC_counters_3_src_START  (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_3_SRC_counters_3_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_3_ALARMMODE_UNION
 结构说明  : DSS0_WR_TRANS_M_COUNTERS_3_ALARMMODE 寄存器结构定义。地址偏移量:0x9578，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_3_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_3_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_3_ALARMMODE_counters_3_alarmmode_START  (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_3_ALARMMODE_counters_3_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_3_VAL_UNION
 结构说明  : DSS0_WR_TRANS_M_COUNTERS_3_VAL 寄存器结构定义。地址偏移量:0x957C，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_3_val : 11; /* bit[0-10] : 当Counters_3_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_3_VAL_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_3_VAL_counters_3_val_START  (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_3_VAL_counters_3_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_4_SRC_UNION
 结构说明  : DSS0_WR_TRANS_M_COUNTERS_4_SRC 寄存器结构定义。地址偏移量:0x9588，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_4_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：2~3）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：4~7）；
                                                         0x23-->Bin 3（delay：128~255；outstanding：8~15）；
                                                         0x24-->Bin 4（delay：>= 256；outstanding：>= 16）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_4_SRC_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_4_SRC_counters_4_src_START  (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_4_SRC_counters_4_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_4_ALARMMODE_UNION
 结构说明  : DSS0_WR_TRANS_M_COUNTERS_4_ALARMMODE 寄存器结构定义。地址偏移量:0x958C，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_4_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_4_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_4_ALARMMODE_counters_4_alarmmode_START  (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_4_ALARMMODE_counters_4_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_4_VAL_UNION
 结构说明  : DSS0_WR_TRANS_M_COUNTERS_4_VAL 寄存器结构定义。地址偏移量:0x9590，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_4_val : 11; /* bit[0-10] : 当Counters_4_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_4_VAL_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_4_VAL_counters_4_val_START  (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_4_VAL_counters_4_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_5_SRC_UNION
 结构说明  : DSS0_WR_TRANS_M_COUNTERS_5_SRC 寄存器结构定义。地址偏移量:0x959C，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_5_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：2~3）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：4~7）；
                                                         0x23-->Bin 3（delay：128~255；outstanding：8~15）；
                                                         0x24-->Bin 4（delay：>= 256；outstanding：>= 16）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_5_SRC_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_5_SRC_counters_5_src_START  (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_5_SRC_counters_5_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_5_ALARMMODE_UNION
 结构说明  : DSS0_WR_TRANS_M_COUNTERS_5_ALARMMODE 寄存器结构定义。地址偏移量:0x95A0，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_5_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_5_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_5_ALARMMODE_counters_5_alarmmode_START  (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_5_ALARMMODE_counters_5_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_5_VAL_UNION
 结构说明  : DSS0_WR_TRANS_M_COUNTERS_5_VAL 寄存器结构定义。地址偏移量:0x95A4，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_5_val : 11; /* bit[0-10] : 当Counters_5_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_5_VAL_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_5_VAL_counters_5_val_START  (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_5_VAL_counters_5_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_6_SRC_UNION
 结构说明  : DSS0_WR_TRANS_M_COUNTERS_6_SRC 寄存器结构定义。地址偏移量:0x95B0，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_6_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：2~3）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：4~7）；
                                                         0x23-->Bin 3（delay：128~255；outstanding：8~15）；
                                                         0x24-->Bin 4（delay：>= 256；outstanding：>= 16）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_6_SRC_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_6_SRC_counters_6_src_START  (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_6_SRC_counters_6_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_6_ALARMMODE_UNION
 结构说明  : DSS0_WR_TRANS_M_COUNTERS_6_ALARMMODE 寄存器结构定义。地址偏移量:0x95B4，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_6_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_6_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_6_ALARMMODE_counters_6_alarmmode_START  (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_6_ALARMMODE_counters_6_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_6_VAL_UNION
 结构说明  : DSS0_WR_TRANS_M_COUNTERS_6_VAL 寄存器结构定义。地址偏移量:0x95B8，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_6_val : 11; /* bit[0-10] : 当Counters_6_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_6_VAL_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_6_VAL_counters_6_val_START  (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_6_VAL_counters_6_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_7_SRC_UNION
 结构说明  : DSS0_WR_TRANS_M_COUNTERS_7_SRC 寄存器结构定义。地址偏移量:0x95C4，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_7_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：2~3）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：4~7）；
                                                         0x23-->Bin 3（delay：128~255；outstanding：8~15）；
                                                         0x24-->Bin 4（delay：>= 256；outstanding：>= 16）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_7_SRC_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_7_SRC_counters_7_src_START  (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_7_SRC_counters_7_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_7_ALARMMODE_UNION
 结构说明  : DSS0_WR_TRANS_M_COUNTERS_7_ALARMMODE 寄存器结构定义。地址偏移量:0x95C8，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_7_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_7_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_7_ALARMMODE_counters_7_alarmmode_START  (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_7_ALARMMODE_counters_7_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_7_VAL_UNION
 结构说明  : DSS0_WR_TRANS_M_COUNTERS_7_VAL 寄存器结构定义。地址偏移量:0x95CC，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_7_val : 11; /* bit[0-10] : 当Counters_7_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_7_VAL_UNION;
#endif
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_7_VAL_counters_7_val_START  (0)
#define SOC_VIVO_BUS_DSS0_WR_TRANS_M_COUNTERS_7_VAL_counters_7_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_RD_TRANS_F_ID_COREID_UNION
 结构说明  : DSS1_RD_TRANS_F_ID_COREID 寄存器结构定义。地址偏移量:0xA000，初值:0xA5BB4209，宽度:32
 寄存器说明: DSS1_RD TransactionStatFilter域ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coretypeid   : 8;  /* bit[0-7] : 类型ID */
        unsigned int  corechecksum : 24; /* bit[8-31]: 配置参数的校验和 */
    } reg;
} SOC_VIVO_BUS_DSS1_RD_TRANS_F_ID_COREID_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_RD_TRANS_F_ID_COREID_coretypeid_START    (0)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_F_ID_COREID_coretypeid_END      (7)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_F_ID_COREID_corechecksum_START  (8)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_F_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_RD_TRANS_F_ID_REVISIONID_UNION
 结构说明  : DSS1_RD_TRANS_F_ID_REVISIONID 寄存器结构定义。地址偏移量:0xA004，初值:0x012D5300，宽度:32
 寄存器说明: 代码版本
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  userid    : 8;  /* bit[0-7] : 用户自定义ID */
        unsigned int  flexnocid : 24; /* bit[8-31]: FlexNoC生成代码的软件版本 */
    } reg;
} SOC_VIVO_BUS_DSS1_RD_TRANS_F_ID_REVISIONID_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_RD_TRANS_F_ID_REVISIONID_userid_START     (0)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_F_ID_REVISIONID_userid_END       (7)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_F_ID_REVISIONID_flexnocid_START  (8)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_F_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_RD_TRANS_F_MODE_UNION
 结构说明  : DSS1_RD_TRANS_F_MODE 寄存器结构定义。地址偏移量:0xA008，初值:0x00000000，宽度:32
 寄存器说明: DSS1_RD Transaction Probe的Filter工作模式配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode     : 1;  /* bit[0-0] : 0-->handshake的模式，start event=begin request，end event=accept request；
                                                   1-->latency模式，start event=begin request + context ID，end event=begin response + context ID。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_RD_TRANS_F_MODE_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_RD_TRANS_F_MODE_mode_START      (0)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_F_MODE_mode_END        (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_RD_TRANS_F_ADDRBASE_LOW_UNION
 结构说明  : DSS1_RD_TRANS_F_ADDRBASE_LOW 寄存器结构定义。地址偏移量:0xA00C，初值:0x00000000，宽度:32
 寄存器说明: 地址过滤基地址
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addrbase_low : 32; /* bit[0-31]: 地址过滤条件的基地址。 */
    } reg;
} SOC_VIVO_BUS_DSS1_RD_TRANS_F_ADDRBASE_LOW_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_RD_TRANS_F_ADDRBASE_LOW_addrbase_low_START  (0)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_F_ADDRBASE_LOW_addrbase_low_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_RD_TRANS_F_ADDRWINDOWSIZE_UNION
 结构说明  : DSS1_RD_TRANS_F_ADDRWINDOWSIZE 寄存器结构定义。地址偏移量:0xA014，初值:0x00000000，宽度:32
 寄存器说明: 地址过滤窗口
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addrwindowsize : 6;  /* bit[0-5] : 地址过滤的Mask窗口大小。
                                                         例如：地址过滤的Mask窗口大小为64MB，WidowSize=log2(64MB)=26，此时，就配置filter_0_windowsize=0x1A；
                                                         Address Mask=~（2^max(WindowSize,packet.len)-1）=0xFC000000（packet.len为NOC内部表示一个packet包长变量的位宽，其值为6~7）；
                                                         过滤条件为：PacketAddress & AddressMask = AddressBase & AddressMask。 */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_RD_TRANS_F_ADDRWINDOWSIZE_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_RD_TRANS_F_ADDRWINDOWSIZE_addrwindowsize_START  (0)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_F_ADDRWINDOWSIZE_addrwindowsize_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_RD_TRANS_F_OPCODE_UNION
 结构说明  : DSS1_RD_TRANS_F_OPCODE 寄存器结构定义。地址偏移量:0xA020，初值:0x00000000，宽度:32
 寄存器说明: DSS1_RD的Transaction Probe的Opcode过滤条件
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rden     : 1;  /* bit[0-0] : 配置为1时，过滤写数据包； */
        unsigned int  wren     : 1;  /* bit[1-1] : 配置为1时，过滤读数据包； */
        unsigned int  reserved : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_RD_TRANS_F_OPCODE_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_RD_TRANS_F_OPCODE_rden_START      (0)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_F_OPCODE_rden_END        (0)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_F_OPCODE_wren_START      (1)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_F_OPCODE_wren_END        (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_RD_TRANS_F_USERBASE_UNION
 结构说明  : DSS1_RD_TRANS_F_USERBASE 寄存器结构定义。地址偏移量:0xA024，初值:0x00000000，宽度:32
 寄存器说明: DSS1_RD的Transaction Probe的User过滤条件
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  userbase : 5;  /* bit[0-4] : User信号过滤条件 */
        unsigned int  reserved : 27; /* bit[5-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_RD_TRANS_F_USERBASE_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_RD_TRANS_F_USERBASE_userbase_START  (0)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_F_USERBASE_userbase_END    (4)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_RD_TRANS_F_USERMASK_UNION
 结构说明  : DSS1_RD_TRANS_F_USERMASK 寄存器结构定义。地址偏移量:0xA028，初值:0x00000000，宽度:32
 寄存器说明: DSS1_RD的Transaction Probe的User过滤条件Mask
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  usermask : 5;  /* bit[0-4] : 对UserBase进行Mask，选择UserBase中的任意几bit User信号作为过滤条件。
                                                   过滤条件：packet.User & UserMask = UserBase & UserMask。 */
        unsigned int  reserved : 27; /* bit[5-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_RD_TRANS_F_USERMASK_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_RD_TRANS_F_USERMASK_usermask_START  (0)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_F_USERMASK_usermask_END    (4)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_RD_TRANS_F_SECURITYBASE_UNION
 结构说明  : DSS1_RD_TRANS_F_SECURITYBASE 寄存器结构定义。地址偏移量:0xA02C，初值:0x00000000，宽度:32
 寄存器说明: DSS1_RD的Transaction Probe的安全过滤条件
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  securitybase : 1;  /* bit[0-0] : 0-->表示安全过滤条件；
                                                       1-->表示非安全过滤条件。 */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_RD_TRANS_F_SECURITYBASE_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_RD_TRANS_F_SECURITYBASE_securitybase_START  (0)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_F_SECURITYBASE_securitybase_END    (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_RD_TRANS_F_SECURITYMASK_UNION
 结构说明  : DSS1_RD_TRANS_F_SECURITYMASK 寄存器结构定义。地址偏移量:0xA030，初值:0x00000000，宽度:32
 寄存器说明: DSS1_RD的Transaction Probe的安全过滤条件Mask
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  securitymask : 1;  /* bit[0-0] : 安全过滤条件：packet.Security & SecurityMask = SecurityBase & SecurityMasks；
                                                       也就是说当Filters_1_SecurityMask=1时安全过滤条件Filters_1_SecurityBase有效，可以过滤安全或非安全packet；否则，不起过滤作用； */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_RD_TRANS_F_SECURITYMASK_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_RD_TRANS_F_SECURITYMASK_securitymask_START  (0)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_F_SECURITYMASK_securitymask_END    (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_RD_TRANS_P_ID_COREID_UNION
 结构说明  : DSS1_RD_TRANS_P_ID_COREID 寄存器结构定义。地址偏移量:0xA080，初值:0xA1387E0A，宽度:32
 寄存器说明: DSS1_RD TransactionStatProfilter域ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coretypeid   : 8;  /* bit[0-7] : 类型ID */
        unsigned int  corechecksum : 24; /* bit[8-31]: 配置参数的校验和 */
    } reg;
} SOC_VIVO_BUS_DSS1_RD_TRANS_P_ID_COREID_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_RD_TRANS_P_ID_COREID_coretypeid_START    (0)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_P_ID_COREID_coretypeid_END      (7)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_P_ID_COREID_corechecksum_START  (8)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_P_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_RD_TRANS_P_ID_REVISIONID_UNION
 结构说明  : DSS1_RD_TRANS_P_ID_REVISIONID 寄存器结构定义。地址偏移量:0xA084，初值:0x012D5300，宽度:32
 寄存器说明: 代码版本
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  userid    : 8;  /* bit[0-7] : 用户自定义ID */
        unsigned int  flexnocid : 24; /* bit[8-31]: FlexNoC生成代码的软件版本 */
    } reg;
} SOC_VIVO_BUS_DSS1_RD_TRANS_P_ID_REVISIONID_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_RD_TRANS_P_ID_REVISIONID_userid_START     (0)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_P_ID_REVISIONID_userid_END       (7)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_P_ID_REVISIONID_flexnocid_START  (8)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_P_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_RD_TRANS_P_EN_UNION
 结构说明  : DSS1_RD_TRANS_P_EN 寄存器结构定义。地址偏移量:0xA088，初值:0x00000000，宽度:32
 寄存器说明: transaction Probe的counter使能配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  en       : 1;  /* bit[0-0] : 当配置为1时，使能Transaction Probe的统计计数器 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_RD_TRANS_P_EN_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_RD_TRANS_P_EN_en_START        (0)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_P_EN_en_END          (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_RD_TRANS_P_MODE_UNION
 结构说明  : DSS1_RD_TRANS_P_MODE 寄存器结构定义。地址偏移量:0xA08C，初值:0x00000000，宽度:32
 寄存器说明: DSS1_RD Transaction Probe的工作模式配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode     : 1;  /* bit[0]   : 0-->统计latency；
                                                   1-->统计outstanding； */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_RD_TRANS_P_MODE_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_RD_TRANS_P_MODE_mode_START      (0)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_P_MODE_mode_END        (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_RD_TRANS_P_OVERFLOWSTATUS_UNION
 结构说明  : DSS1_RD_TRANS_P_OVERFLOWSTATUS 寄存器结构定义。地址偏移量:0xA0EC，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器溢出状态
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  overflowstatus : 1;  /* bit[0-0] : 1表示统计计数器溢出 */
        unsigned int  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_RD_TRANS_P_OVERFLOWSTATUS_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_RD_TRANS_P_OVERFLOWSTATUS_overflowstatus_START  (0)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_P_OVERFLOWSTATUS_overflowstatus_END    (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_RD_TRANS_P_OVERFLOWRESET_UNION
 结构说明  : DSS1_RD_TRANS_P_OVERFLOWRESET 寄存器结构定义。地址偏移量:0xA0F0，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器溢出状态清零
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  overflowreset : 1;  /* bit[0-0] : 写1时，OverflowStatus寄存器清零，读该寄存器时钟返回0 */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_RD_TRANS_P_OVERFLOWRESET_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_RD_TRANS_P_OVERFLOWRESET_overflowreset_START  (0)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_P_OVERFLOWRESET_overflowreset_END    (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_RD_TRANS_P_PENDINGEVENTMODE_UNION
 结构说明  : DSS1_RD_TRANS_P_PENDINGEVENTMODE 寄存器结构定义。地址偏移量:0xA0F4，初值:0x00000000，宽度:32
 寄存器说明: outstanding统计技术工作模式配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pendingeventmode : 1;  /* bit[0-0] : 0x0-->当outstanding数量 > 0时，每个cycle都去触发计数器收集outstanding个数；
                                                           0x1-->当返回1个response时，就触发计数器收集outstanding个数。 */
        unsigned int  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_RD_TRANS_P_PENDINGEVENTMODE_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_RD_TRANS_P_PENDINGEVENTMODE_pendingeventmode_START  (0)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_P_PENDINGEVENTMODE_pendingeventmode_END    (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_RD_TRANS_P_PRESCALER_UNION
 结构说明  : DSS1_RD_TRANS_P_PRESCALER 寄存器结构定义。地址偏移量:0xA0F8，初值:0x00000000，宽度:32
 寄存器说明: latency统计系数配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  prescaler : 8;  /* bit[0-7] : 0-->handshake的模式，start event=begin request，end event=accept request；
                                                    1-->latency模式，start event=begin request + context ID，end event=begin response + context ID。 */
        unsigned int  reserved  : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_RD_TRANS_P_PRESCALER_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_RD_TRANS_P_PRESCALER_prescaler_START  (0)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_P_PRESCALER_prescaler_END    (7)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_RD_TRANS_M_ID_COREID_UNION
 结构说明  : DSS1_RD_TRANS_M_ID_COREID 寄存器结构定义。地址偏移量:0xA400，初值:0xE14B9706，宽度:32
 寄存器说明: DSS1_RD Transaction probe域ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_coreid : 32; /* bit[0-31]: VcodecBus的Packet Probe的域ID。 */
    } reg;
} SOC_VIVO_BUS_DSS1_RD_TRANS_M_ID_COREID_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_ID_COREID_id_coreid_START  (0)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_ID_COREID_id_coreid_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_RD_TRANS_M_ID_REVISIONID_UNION
 结构说明  : DSS1_RD_TRANS_M_ID_REVISIONID 寄存器结构定义。地址偏移量:0xA404，初值:0x012D5300，宽度:32
 寄存器说明: 总线代码版本寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_revisionid : 32; /* bit[0-31]: 低8bit自定义，高24bit是NOC的配置HUSH值。 */
    } reg;
} SOC_VIVO_BUS_DSS1_RD_TRANS_M_ID_REVISIONID_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_ID_REVISIONID_id_revisionid_START  (0)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_ID_REVISIONID_id_revisionid_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_RD_TRANS_M_MAINCTL_UNION
 结构说明  : DSS1_RD_TRANS_M_MAINCTL 寄存器结构定义。地址偏移量:0xA408，初值:0x00000000，宽度:32
 寄存器说明: Transaction Probe全局控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  erren                     : 1;  /* bit[0]   : ErrEn：使能Packet Probe将检测到的任何错误状态的Packet上报给Observer。由于本总线的Packet Probe不支持trace功能，故此位无意义。 */
        unsigned int  traceen                   : 1;  /* bit[1]   : TraceEn：该总线不支持Trace功能，故此位无意义。 */
        unsigned int  payloaden                 : 1;  /* bit[2]   : PayloadEn：该总线不支持Trace功能，故此位无意义。 */
        unsigned int  staten                    : 1;  /* bit[3]   : StatEn：统计模型使能寄存器，当StatEn由0配置为1时，统计计数器被清零；当StatEn配置为0时，统计计数器被disabled。 */
        unsigned int  alarmen                   : 1;  /* bit[4]   : AlarmEn：中断使能配置。
                                                                    0-->屏蔽中断；
                                                                    1-->使能中断输出。 */
        unsigned int  statconddump              : 1;  /* bit[5]   : 0-->表示无条件dump统计数据，寄存器counters_m_val的值，实时反映统计计数器的值；
                                                                    1-->表示有条件dump数据，在给定的统计周期内发生out of bounds 事件，才会将统计计数器的值dump至寄存器counters_m_val中。 */
        unsigned int  intrusivemode             : 1;  /* bit[6]   : IntrusiveMode： 该总线不支持Trace功能，故此位无意义。 */
        unsigned int  filtbytealwayschainableen : 1;  /* bit[7]   : FiltByteAlwaysChainableEn：奇数和偶数计数器串行使能的全局配置：
                                                                    0-->不使能，此时，所有侧statistic counters都可以被Map；
                                                                    1-->使能，只有偶数statistic counters才可以被Map。 */
        unsigned int  reserved                  : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_RD_TRANS_M_MAINCTL_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_MAINCTL_erren_START                      (0)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_MAINCTL_erren_END                        (0)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_MAINCTL_traceen_START                    (1)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_MAINCTL_traceen_END                      (1)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_MAINCTL_payloaden_START                  (2)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_MAINCTL_payloaden_END                    (2)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_MAINCTL_staten_START                     (3)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_MAINCTL_staten_END                       (3)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_MAINCTL_alarmen_START                    (4)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_MAINCTL_alarmen_END                      (4)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_MAINCTL_statconddump_START               (5)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_MAINCTL_statconddump_END                 (5)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_MAINCTL_intrusivemode_START              (6)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_MAINCTL_intrusivemode_END                (6)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_MAINCTL_filtbytealwayschainableen_START  (7)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_MAINCTL_filtbytealwayschainableen_END    (7)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_RD_TRANS_M_CFGCTL_UNION
 结构说明  : DSS1_RD_TRANS_M_CFGCTL 寄存器结构定义。地址偏移量:0xA40C，初值:0x00000000，宽度:32
 寄存器说明: Packet Probe使能寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  globalen : 1;  /* bit[0]   : GlobalEn：Packet Probe使能信号，高有效。 */
        unsigned int  active   : 1;  /* bit[1]   : Active：Packet Probe的工作状态指示信号。
                                                   0-->当GlobalEn配置为0的几个cycle后，Active被拉低；
                                                   1-->当GlobalEn配置为1时，Active被拉高，此时不允许对Packet Probe进行配置。 */
        unsigned int  reserved : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_RD_TRANS_M_CFGCTL_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_CFGCTL_globalen_START  (0)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_CFGCTL_globalen_END    (0)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_CFGCTL_active_START    (1)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_CFGCTL_active_END      (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_RD_TRANS_M_STATPERIOD_UNION
 结构说明  : DSS1_RD_TRANS_M_STATPERIOD 寄存器结构定义。地址偏移量:0xA424，初值:0x00000000，宽度:32
 寄存器说明: 统计周期配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statperiod : 5;  /* bit[0-4] : 自动统计模式下的统计周期，统计周期= N_Cycle = 2^min(23,StatPeriod)，最大为8 mega cycles，最小为2 cycles。当配置为0时，自动统计模式被关闭，需要采用手动模式，也就是配置StatGo寄存器来实现带宽统计。 */
        unsigned int  reserved   : 27; /* bit[5-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_RD_TRANS_M_STATPERIOD_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_STATPERIOD_statperiod_START  (0)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_STATPERIOD_statperiod_END    (4)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_RD_TRANS_M_STATGO_UNION
 结构说明  : DSS1_RD_TRANS_M_STATGO 寄存器结构定义。地址偏移量:0xA428，初值:0x00000000，宽度:32
 寄存器说明: 手动带宽统计计时开始使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statgo   : 1;  /* bit[0]   : 当StatPeriod=0时，当globalen为1，向寄存器StatGo写1，则会将counter_m_val的值与statalarmmax或statalarmmin的值进行比较；读该寄存器始终返回0。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_RD_TRANS_M_STATGO_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_STATGO_statgo_START    (0)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_STATGO_statgo_END      (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_RD_TRANS_M_STATALARMMIN_UNION
 结构说明  : DSS1_RD_TRANS_M_STATALARMMIN 寄存器结构定义。地址偏移量:0xA42C，初值:0x00000000，宽度:32
 寄存器说明: 统计计数最小告警阈值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statalarmmin : 32; /* bit[0-31]: 当任意一个统计计数器的值小于StatAlarmMin的值，就触发告警寄存器。 */
    } reg;
} SOC_VIVO_BUS_DSS1_RD_TRANS_M_STATALARMMIN_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_STATALARMMIN_statalarmmin_START  (0)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_STATALARMMIN_statalarmmin_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_RD_TRANS_M_STATALARMMAX_UNION
 结构说明  : DSS1_RD_TRANS_M_STATALARMMAX 寄存器结构定义。地址偏移量:0xA430，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器最大告警阈值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statalarmmax : 32; /* bit[0-31]: 当任意一个统计计数器的值大于StatAlarmMax的值，就触发告警寄存器。 */
    } reg;
} SOC_VIVO_BUS_DSS1_RD_TRANS_M_STATALARMMAX_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_STATALARMMAX_statalarmmax_START  (0)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_STATALARMMAX_statalarmmax_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_RD_TRANS_M_STATALARMSTATUS_UNION
 结构说明  : DSS1_RD_TRANS_M_STATALARMSTATUS 寄存器结构定义。地址偏移量:0xA434，初值:0x00000000，宽度:32
 寄存器说明: 告警状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statalarmstatus : 1;  /* bit[0]   : 当任意一个统计计数器的值大于StatAlarmMax或小于StatAlarmMin，则该寄存器置位为1； */
        unsigned int  reserved        : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_RD_TRANS_M_STATALARMSTATUS_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_STATALARMSTATUS_statalarmstatus_START  (0)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_STATALARMSTATUS_statalarmstatus_END    (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_RD_TRANS_M_STATALARMCLR_UNION
 结构说明  : DSS1_RD_TRANS_M_STATALARMCLR 寄存器结构定义。地址偏移量:0xA438，初值:0x00000000，宽度:32
 寄存器说明: 告警状态清除寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statalarmclr : 1;  /* bit[0]   : 写1会清零StatAlarmStatus寄存器，读此寄存器返回总是0； */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_RD_TRANS_M_STATALARMCLR_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_STATALARMCLR_statalarmclr_START  (0)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_STATALARMCLR_statalarmclr_END    (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_0_SRC_UNION
 结构说明  : DSS1_RD_TRANS_M_COUNTERS_0_SRC 寄存器结构定义。地址偏移量:0xA538，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_0_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~7）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：8~15）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：16~31）；
                                                         0x23-->Bin 3（delay：128~255；outstanding：32~60）；
                                                         0x24-->Bin 4（delay：>= 256；outstanding：>= 61）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_0_SRC_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_0_SRC_counters_0_src_START  (0)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_0_SRC_counters_0_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_0_ALARMMODE_UNION
 结构说明  : DSS1_RD_TRANS_M_COUNTERS_0_ALARMMODE 寄存器结构定义。地址偏移量:0xA53C，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_0_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_0_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_0_ALARMMODE_counters_0_alarmmode_START  (0)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_0_ALARMMODE_counters_0_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_0_VAL_UNION
 结构说明  : DSS1_RD_TRANS_M_COUNTERS_0_VAL 寄存器结构定义。地址偏移量:0xA540，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_0_val : 11; /* bit[0-10] : 当Counters_0_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_0_VAL_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_0_VAL_counters_0_val_START  (0)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_0_VAL_counters_0_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_1_SRC_UNION
 结构说明  : DSS1_RD_TRANS_M_COUNTERS_1_SRC 寄存器结构定义。地址偏移量:0xA54C，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_1_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~7）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：8~15）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：16~31）；
                                                         0x23-->Bin 3（delay：128~255；outstanding：32~60）；
                                                         0x24-->Bin 4（delay：>= 256；outstanding：>= 61）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_1_SRC_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_1_SRC_counters_1_src_START  (0)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_1_SRC_counters_1_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_1_ALARMMODE_UNION
 结构说明  : DSS1_RD_TRANS_M_COUNTERS_1_ALARMMODE 寄存器结构定义。地址偏移量:0xA550，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_1_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_1_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_1_ALARMMODE_counters_1_alarmmode_START  (0)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_1_ALARMMODE_counters_1_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_1_VAL_UNION
 结构说明  : DSS1_RD_TRANS_M_COUNTERS_1_VAL 寄存器结构定义。地址偏移量:0xA554，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_1_val : 11; /* bit[0-10] : 当Counters_1_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_1_VAL_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_1_VAL_counters_1_val_START  (0)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_1_VAL_counters_1_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_2_SRC_UNION
 结构说明  : DSS1_RD_TRANS_M_COUNTERS_2_SRC 寄存器结构定义。地址偏移量:0xA560，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_2_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~7）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：8~15）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：16~31）；
                                                         0x23-->Bin 3（delay：128~255；outstanding：32~60）；
                                                         0x24-->Bin 4（delay：>= 256；outstanding：>= 61）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_2_SRC_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_2_SRC_counters_2_src_START  (0)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_2_SRC_counters_2_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_2_ALARMMODE_UNION
 结构说明  : DSS1_RD_TRANS_M_COUNTERS_2_ALARMMODE 寄存器结构定义。地址偏移量:0xA564，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_2_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_2_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_2_ALARMMODE_counters_2_alarmmode_START  (0)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_2_ALARMMODE_counters_2_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_2_VAL_UNION
 结构说明  : DSS1_RD_TRANS_M_COUNTERS_2_VAL 寄存器结构定义。地址偏移量:0xA568，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_2_val : 11; /* bit[0-10] : 当Counters_2_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_2_VAL_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_2_VAL_counters_2_val_START  (0)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_2_VAL_counters_2_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_3_SRC_UNION
 结构说明  : DSS1_RD_TRANS_M_COUNTERS_3_SRC 寄存器结构定义。地址偏移量:0xA574，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_3_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~7）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：8~15）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：16~31）；
                                                         0x23-->Bin 3（delay：128~255；outstanding：32~60）；
                                                         0x24-->Bin 4（delay：>= 256；outstanding：>= 61）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_3_SRC_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_3_SRC_counters_3_src_START  (0)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_3_SRC_counters_3_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_3_ALARMMODE_UNION
 结构说明  : DSS1_RD_TRANS_M_COUNTERS_3_ALARMMODE 寄存器结构定义。地址偏移量:0xA578，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_3_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_3_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_3_ALARMMODE_counters_3_alarmmode_START  (0)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_3_ALARMMODE_counters_3_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_3_VAL_UNION
 结构说明  : DSS1_RD_TRANS_M_COUNTERS_3_VAL 寄存器结构定义。地址偏移量:0xA57C，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_3_val : 11; /* bit[0-10] : 当Counters_3_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_3_VAL_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_3_VAL_counters_3_val_START  (0)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_3_VAL_counters_3_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_4_SRC_UNION
 结构说明  : DSS1_RD_TRANS_M_COUNTERS_4_SRC 寄存器结构定义。地址偏移量:0xA588，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_4_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~7）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：8~15）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：16~31）；
                                                         0x23-->Bin 3（delay：128~255；outstanding：32~60）；
                                                         0x24-->Bin 4（delay：>= 256；outstanding：>= 61）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_4_SRC_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_4_SRC_counters_4_src_START  (0)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_4_SRC_counters_4_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_4_ALARMMODE_UNION
 结构说明  : DSS1_RD_TRANS_M_COUNTERS_4_ALARMMODE 寄存器结构定义。地址偏移量:0xA58C，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_4_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_4_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_4_ALARMMODE_counters_4_alarmmode_START  (0)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_4_ALARMMODE_counters_4_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_4_VAL_UNION
 结构说明  : DSS1_RD_TRANS_M_COUNTERS_4_VAL 寄存器结构定义。地址偏移量:0xA590，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_4_val : 11; /* bit[0-10] : 当Counters_4_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_4_VAL_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_4_VAL_counters_4_val_START  (0)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_4_VAL_counters_4_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_5_SRC_UNION
 结构说明  : DSS1_RD_TRANS_M_COUNTERS_5_SRC 寄存器结构定义。地址偏移量:0xA59C，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_5_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~7）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：8~15）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：16~31）；
                                                         0x23-->Bin 3（delay：128~255；outstanding：32~60）；
                                                         0x24-->Bin 4（delay：>= 256；outstanding：>= 61）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_5_SRC_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_5_SRC_counters_5_src_START  (0)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_5_SRC_counters_5_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_5_ALARMMODE_UNION
 结构说明  : DSS1_RD_TRANS_M_COUNTERS_5_ALARMMODE 寄存器结构定义。地址偏移量:0xA5A0，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_5_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_5_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_5_ALARMMODE_counters_5_alarmmode_START  (0)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_5_ALARMMODE_counters_5_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_5_VAL_UNION
 结构说明  : DSS1_RD_TRANS_M_COUNTERS_5_VAL 寄存器结构定义。地址偏移量:0xA5A4，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_5_val : 11; /* bit[0-10] : 当Counters_5_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_5_VAL_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_5_VAL_counters_5_val_START  (0)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_5_VAL_counters_5_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_6_SRC_UNION
 结构说明  : DSS1_RD_TRANS_M_COUNTERS_6_SRC 寄存器结构定义。地址偏移量:0xA5B0，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_6_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~7）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：8~15）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：16~31）；
                                                         0x23-->Bin 3（delay：128~255；outstanding：32~60）；
                                                         0x24-->Bin 4（delay：>= 256；outstanding：>= 61）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_6_SRC_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_6_SRC_counters_6_src_START  (0)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_6_SRC_counters_6_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_6_ALARMMODE_UNION
 结构说明  : DSS1_RD_TRANS_M_COUNTERS_6_ALARMMODE 寄存器结构定义。地址偏移量:0xA5B4，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_6_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_6_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_6_ALARMMODE_counters_6_alarmmode_START  (0)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_6_ALARMMODE_counters_6_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_6_VAL_UNION
 结构说明  : DSS1_RD_TRANS_M_COUNTERS_6_VAL 寄存器结构定义。地址偏移量:0xA5B8，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_6_val : 11; /* bit[0-10] : 当Counters_6_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_6_VAL_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_6_VAL_counters_6_val_START  (0)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_6_VAL_counters_6_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_7_SRC_UNION
 结构说明  : DSS1_RD_TRANS_M_COUNTERS_7_SRC 寄存器结构定义。地址偏移量:0xA5C4，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_7_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~7）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：8~15）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：16~31）；
                                                         0x23-->Bin 3（delay：128~255；outstanding：32~60）；
                                                         0x24-->Bin 4（delay：>= 256；outstanding：>= 61）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_7_SRC_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_7_SRC_counters_7_src_START  (0)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_7_SRC_counters_7_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_7_ALARMMODE_UNION
 结构说明  : DSS1_RD_TRANS_M_COUNTERS_7_ALARMMODE 寄存器结构定义。地址偏移量:0xA5C8，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_7_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_7_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_7_ALARMMODE_counters_7_alarmmode_START  (0)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_7_ALARMMODE_counters_7_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_7_VAL_UNION
 结构说明  : DSS1_RD_TRANS_M_COUNTERS_7_VAL 寄存器结构定义。地址偏移量:0xA5CC，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_7_val : 11; /* bit[0-10] : 当Counters_7_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_7_VAL_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_7_VAL_counters_7_val_START  (0)
#define SOC_VIVO_BUS_DSS1_RD_TRANS_M_COUNTERS_7_VAL_counters_7_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_TRANS_F_ID_COREID_UNION
 结构说明  : DSS1_WR_TRANS_F_ID_COREID 寄存器结构定义。地址偏移量:0xB000，初值:0xAC2EE309，宽度:32
 寄存器说明: DSS1_WR TransactionStatFilter域ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coretypeid   : 8;  /* bit[0-7] : 类型ID */
        unsigned int  corechecksum : 24; /* bit[8-31]: 配置参数的校验和 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_TRANS_F_ID_COREID_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_TRANS_F_ID_COREID_coretypeid_START    (0)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_F_ID_COREID_coretypeid_END      (7)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_F_ID_COREID_corechecksum_START  (8)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_F_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_TRANS_F_ID_REVISIONID_UNION
 结构说明  : DSS1_WR_TRANS_F_ID_REVISIONID 寄存器结构定义。地址偏移量:0xB004，初值:0x012D5300，宽度:32
 寄存器说明: 代码版本
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  userid    : 8;  /* bit[0-7] : 用户自定义ID */
        unsigned int  flexnocid : 24; /* bit[8-31]: FlexNoC生成代码的软件版本 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_TRANS_F_ID_REVISIONID_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_TRANS_F_ID_REVISIONID_userid_START     (0)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_F_ID_REVISIONID_userid_END       (7)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_F_ID_REVISIONID_flexnocid_START  (8)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_F_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_TRANS_F_MODE_UNION
 结构说明  : DSS1_WR_TRANS_F_MODE 寄存器结构定义。地址偏移量:0xB008，初值:0x00000000，宽度:32
 寄存器说明: DSS1_WR Transaction Probe的Filter工作模式配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode     : 1;  /* bit[0-0] : 0-->handshake的模式，start event=begin request，end event=accept request；
                                                   1-->latency模式，start event=begin request + context ID，end event=begin response + context ID。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_TRANS_F_MODE_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_TRANS_F_MODE_mode_START      (0)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_F_MODE_mode_END        (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_TRANS_F_ADDRBASE_LOW_UNION
 结构说明  : DSS1_WR_TRANS_F_ADDRBASE_LOW 寄存器结构定义。地址偏移量:0xB00C，初值:0x00000000，宽度:32
 寄存器说明: 地址过滤基地址
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addrbase_low : 32; /* bit[0-31]: 地址过滤条件的基地址。 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_TRANS_F_ADDRBASE_LOW_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_TRANS_F_ADDRBASE_LOW_addrbase_low_START  (0)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_F_ADDRBASE_LOW_addrbase_low_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_TRANS_F_ADDRBASE_HIGH_UNION
 结构说明  : DSS1_WR_TRANS_F_ADDRBASE_HIGH 寄存器结构定义。地址偏移量:0xB010，初值:0x00000000，宽度:32
 寄存器说明: 地址过滤基地址
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addrbase_high : 2;  /* bit[0-1] : 地址过滤条件的基地址。 */
        unsigned int  reserved      : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_TRANS_F_ADDRBASE_HIGH_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_TRANS_F_ADDRBASE_HIGH_addrbase_high_START  (0)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_F_ADDRBASE_HIGH_addrbase_high_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_TRANS_F_ADDRWINDOWSIZE_UNION
 结构说明  : DSS1_WR_TRANS_F_ADDRWINDOWSIZE 寄存器结构定义。地址偏移量:0xB014，初值:0x00000000，宽度:32
 寄存器说明: 地址过滤窗口
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addrwindowsize : 6;  /* bit[0-5] : 地址过滤的Mask窗口大小。
                                                         例如：地址过滤的Mask窗口大小为64MB，WidowSize=log2(64MB)=26，此时，就配置filter_0_windowsize=0x1A；
                                                         Address Mask=~（2^max(WindowSize,packet.len)-1）=0xFC000000（packet.len为NOC内部表示一个packet包长变量的位宽，其值为6~7）；
                                                         过滤条件为：PacketAddress & AddressMask = AddressBase & AddressMask。 */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_TRANS_F_ADDRWINDOWSIZE_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_TRANS_F_ADDRWINDOWSIZE_addrwindowsize_START  (0)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_F_ADDRWINDOWSIZE_addrwindowsize_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_TRANS_F_OPCODE_UNION
 结构说明  : DSS1_WR_TRANS_F_OPCODE 寄存器结构定义。地址偏移量:0xB020，初值:0x00000000，宽度:32
 寄存器说明: DSS1_WR的Transaction Probe的Opcode过滤条件
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rden     : 1;  /* bit[0-0] : 配置为1时，过滤写数据包； */
        unsigned int  wren     : 1;  /* bit[1-1] : 配置为1时，过滤读数据包； */
        unsigned int  reserved : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_TRANS_F_OPCODE_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_TRANS_F_OPCODE_rden_START      (0)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_F_OPCODE_rden_END        (0)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_F_OPCODE_wren_START      (1)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_F_OPCODE_wren_END        (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_TRANS_F_USERBASE_UNION
 结构说明  : DSS1_WR_TRANS_F_USERBASE 寄存器结构定义。地址偏移量:0xB024，初值:0x00000000，宽度:32
 寄存器说明: DSS1_WR的Transaction Probe的User过滤条件
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  userbase : 5;  /* bit[0-4] : User信号过滤条件 */
        unsigned int  reserved : 27; /* bit[5-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_TRANS_F_USERBASE_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_TRANS_F_USERBASE_userbase_START  (0)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_F_USERBASE_userbase_END    (4)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_TRANS_F_USERMASK_UNION
 结构说明  : DSS1_WR_TRANS_F_USERMASK 寄存器结构定义。地址偏移量:0xB028，初值:0x00000000，宽度:32
 寄存器说明: DSS1_WR的Transaction Probe的User过滤条件Mask
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  usermask : 5;  /* bit[0-4] : 对UserBase进行Mask，选择UserBase中的任意几bit User信号作为过滤条件。
                                                   过滤条件：packet.User & UserMask = UserBase & UserMask。 */
        unsigned int  reserved : 27; /* bit[5-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_TRANS_F_USERMASK_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_TRANS_F_USERMASK_usermask_START  (0)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_F_USERMASK_usermask_END    (4)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_TRANS_F_SECURITYBASE_UNION
 结构说明  : DSS1_WR_TRANS_F_SECURITYBASE 寄存器结构定义。地址偏移量:0xB02C，初值:0x00000000，宽度:32
 寄存器说明: DSS1_WR的Transaction Probe的安全过滤条件
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  securitybase : 1;  /* bit[0-0] : 0-->表示安全过滤条件；
                                                       1-->表示非安全过滤条件。 */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_TRANS_F_SECURITYBASE_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_TRANS_F_SECURITYBASE_securitybase_START  (0)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_F_SECURITYBASE_securitybase_END    (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_TRANS_F_SECURITYMASK_UNION
 结构说明  : DSS1_WR_TRANS_F_SECURITYMASK 寄存器结构定义。地址偏移量:0xB030，初值:0x00000000，宽度:32
 寄存器说明: DSS1_WR的Transaction Probe的安全过滤条件Mask
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  securitymask : 1;  /* bit[0-0] : 安全过滤条件：packet.Security & SecurityMask = SecurityBase & SecurityMasks；
                                                       也就是说当Filters_1_SecurityMask=1时安全过滤条件Filters_1_SecurityBase有效，可以过滤安全或非安全packet；否则，不起过滤作用； */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_TRANS_F_SECURITYMASK_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_TRANS_F_SECURITYMASK_securitymask_START  (0)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_F_SECURITYMASK_securitymask_END    (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_TRANS_P_ID_REVISIONID_UNION
 结构说明  : DSS1_WR_TRANS_P_ID_REVISIONID 寄存器结构定义。地址偏移量:0xB084，初值:0x012D5300，宽度:32
 寄存器说明: 代码版本
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  userid    : 8;  /* bit[0-7] : 用户自定义ID */
        unsigned int  flexnocid : 24; /* bit[8-31]: FlexNoC生成代码的软件版本 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_TRANS_P_ID_REVISIONID_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_TRANS_P_ID_REVISIONID_userid_START     (0)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_P_ID_REVISIONID_userid_END       (7)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_P_ID_REVISIONID_flexnocid_START  (8)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_P_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_TRANS_P_EN_UNION
 结构说明  : DSS1_WR_TRANS_P_EN 寄存器结构定义。地址偏移量:0xB088，初值:0x00000000，宽度:32
 寄存器说明: transaction Probe的counter使能配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  en       : 1;  /* bit[0-0] : 当配置为1时，使能Transaction Probe的统计计数器 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_TRANS_P_EN_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_TRANS_P_EN_en_START        (0)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_P_EN_en_END          (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_TRANS_P_MODE_UNION
 结构说明  : DSS1_WR_TRANS_P_MODE 寄存器结构定义。地址偏移量:0xB08C，初值:0x00000000，宽度:32
 寄存器说明: DSS1_WR Transaction Probe的工作模式配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode     : 1;  /* bit[0]   : 0-->统计latency；
                                                   1-->统计outstanding； */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_TRANS_P_MODE_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_TRANS_P_MODE_mode_START      (0)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_P_MODE_mode_END        (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_TRANS_P_THRESHOLDS_0_0_UNION
 结构说明  : DSS1_WR_TRANS_P_THRESHOLDS_0_0 寄存器结构定义。地址偏移量:0xB0AC，初值:0x00000000，宽度:32
 寄存器说明: DSS1_WR Transaction Probe的bin_0配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  thresholds_0_0 : 2;  /* bit[0-1] : 0x0-->选择threshold_0（delay：40；outstanding：2）；
                                                         0x1-->选择threshold_1（delay：96；outstanding：4）；
                                                         0x2-->选择threshold_2（delay：128；outstanding：8）；
                                                         0x3-->选择threshold_3（delay：256；outstanding：16）； */
        unsigned int  reserved       : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_TRANS_P_THRESHOLDS_0_0_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_TRANS_P_THRESHOLDS_0_0_thresholds_0_0_START  (0)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_P_THRESHOLDS_0_0_thresholds_0_0_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_TRANS_P_THRESHOLDS_0_1_UNION
 结构说明  : DSS1_WR_TRANS_P_THRESHOLDS_0_1 寄存器结构定义。地址偏移量:0xB0B0，初值:0x00000000，宽度:32
 寄存器说明: DSS1_WR Transaction Probe的bin_0配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  thresholds_0_1 : 2;  /* bit[0-1] : 0x0-->选择threshold_0（delay：40；outstanding：2）；
                                                         0x1-->选择threshold_1（delay：96；outstanding：4）；
                                                         0x2-->选择threshold_2（delay：128；outstanding：8）；
                                                         0x3-->选择threshold_3（delay：256；outstanding：16）； */
        unsigned int  reserved       : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_TRANS_P_THRESHOLDS_0_1_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_TRANS_P_THRESHOLDS_0_1_thresholds_0_1_START  (0)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_P_THRESHOLDS_0_1_thresholds_0_1_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_TRANS_P_THRESHOLDS_0_2_UNION
 结构说明  : DSS1_WR_TRANS_P_THRESHOLDS_0_2 寄存器结构定义。地址偏移量:0xB0B4，初值:0x00000000，宽度:32
 寄存器说明: DSS1_WR Transaction Probe的bin_0配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  thresholds_0_2 : 2;  /* bit[0-1] : 0x0-->选择threshold_0（delay：40；outstanding：2）；
                                                         0x1-->选择threshold_1（delay：96；outstanding：4）；
                                                         0x2-->选择threshold_2（delay：128；outstanding：8）；
                                                         0x3-->选择threshold_3（delay：256；outstanding：16）； */
        unsigned int  reserved       : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_TRANS_P_THRESHOLDS_0_2_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_TRANS_P_THRESHOLDS_0_2_thresholds_0_2_START  (0)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_P_THRESHOLDS_0_2_thresholds_0_2_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_TRANS_P_THRESHOLDS_0_3_UNION
 结构说明  : DSS1_WR_TRANS_P_THRESHOLDS_0_3 寄存器结构定义。地址偏移量:0xB0B8，初值:0x00000000，宽度:32
 寄存器说明: DSS1_WR Transaction Probe的bin_0配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  thresholds_0_3 : 2;  /* bit[0-1] : 0x0-->选择threshold_0（delay：40；outstanding：2）；
                                                         0x1-->选择threshold_1（delay：96；outstanding：4）；
                                                         0x2-->选择threshold_2（delay：128；outstanding：8）；
                                                         0x3-->选择threshold_3（delay：256；outstanding：16）； */
        unsigned int  reserved       : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_TRANS_P_THRESHOLDS_0_3_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_TRANS_P_THRESHOLDS_0_3_thresholds_0_3_START  (0)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_P_THRESHOLDS_0_3_thresholds_0_3_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_TRANS_P_OVERFLOWSTATUS_UNION
 结构说明  : DSS1_WR_TRANS_P_OVERFLOWSTATUS 寄存器结构定义。地址偏移量:0xB0EC，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器溢出状态
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  overflowstatus : 1;  /* bit[0-0] : 1表示统计计数器溢出 */
        unsigned int  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_TRANS_P_OVERFLOWSTATUS_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_TRANS_P_OVERFLOWSTATUS_overflowstatus_START  (0)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_P_OVERFLOWSTATUS_overflowstatus_END    (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_TRANS_P_OVERFLOWRESET_UNION
 结构说明  : DSS1_WR_TRANS_P_OVERFLOWRESET 寄存器结构定义。地址偏移量:0xB0F0，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器溢出状态清零
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  overflowreset : 1;  /* bit[0-0] : 写1时，OverflowStatus寄存器清零，读该寄存器时钟返回0 */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_TRANS_P_OVERFLOWRESET_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_TRANS_P_OVERFLOWRESET_overflowreset_START  (0)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_P_OVERFLOWRESET_overflowreset_END    (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_TRANS_P_PENDINGEVENTMODE_UNION
 结构说明  : DSS1_WR_TRANS_P_PENDINGEVENTMODE 寄存器结构定义。地址偏移量:0xB0F4，初值:0x00000000，宽度:32
 寄存器说明: outstanding统计技术工作模式配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pendingeventmode : 1;  /* bit[0-0] : 0x0-->当outstanding数量 > 0时，每个cycle都去触发计数器收集outstanding个数；
                                                           0x1-->当返回1个response时，就触发计数器收集outstanding个数。 */
        unsigned int  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_TRANS_P_PENDINGEVENTMODE_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_TRANS_P_PENDINGEVENTMODE_pendingeventmode_START  (0)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_P_PENDINGEVENTMODE_pendingeventmode_END    (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_TRANS_P_PRESCALER_UNION
 结构说明  : DSS1_WR_TRANS_P_PRESCALER 寄存器结构定义。地址偏移量:0xB0F8，初值:0x00000000，宽度:32
 寄存器说明: latency统计系数配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  prescaler : 8;  /* bit[0-7] : 在统计latency时，将统计值除以PreScaler的值，PreScaler取值范围1~255，当配置为0时，表示disable该功能；
                                                    在配置PreScaler的值时，需要先配置En寄存器为0，即disable Transaction Probe； */
        unsigned int  reserved  : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_TRANS_P_PRESCALER_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_TRANS_P_PRESCALER_prescaler_START  (0)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_P_PRESCALER_prescaler_END    (7)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_TRANS_M_ID_COREID_UNION
 结构说明  : DSS1_WR_TRANS_M_ID_COREID 寄存器结构定义。地址偏移量:0xB400，初值:0x301EF106，宽度:32
 寄存器说明: DSS1_WR Transaction probe域ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_coreid : 32; /* bit[0-31]: VcodecBus的Packet Probe的域ID。 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_TRANS_M_ID_COREID_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_ID_COREID_id_coreid_START  (0)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_ID_COREID_id_coreid_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_TRANS_M_ID_REVISIONID_UNION
 结构说明  : DSS1_WR_TRANS_M_ID_REVISIONID 寄存器结构定义。地址偏移量:0xB404，初值:0x012D5300，宽度:32
 寄存器说明: 总线代码版本寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_revisionid : 32; /* bit[0-31]: 低8bit自定义，高24bit是NOC的配置HUSH值。 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_TRANS_M_ID_REVISIONID_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_ID_REVISIONID_id_revisionid_START  (0)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_ID_REVISIONID_id_revisionid_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_TRANS_M_MAINCTL_UNION
 结构说明  : DSS1_WR_TRANS_M_MAINCTL 寄存器结构定义。地址偏移量:0xB408，初值:0x00000000，宽度:32
 寄存器说明: Transaction Probe全局控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  erren                     : 1;  /* bit[0]   : ErrEn：使能Packet Probe将检测到的任何错误状态的Packet上报给Observer。由于本总线的Packet Probe不支持trace功能，故此位无意义。 */
        unsigned int  traceen                   : 1;  /* bit[1]   : TraceEn：该总线不支持Trace功能，故此位无意义。 */
        unsigned int  payloaden                 : 1;  /* bit[2]   : PayloadEn：该总线不支持Trace功能，故此位无意义。 */
        unsigned int  staten                    : 1;  /* bit[3]   : StatEn：统计模型使能寄存器，当StatEn由0配置为1时，统计计数器被清零；当StatEn配置为0时，统计计数器被disabled。 */
        unsigned int  alarmen                   : 1;  /* bit[4]   : AlarmEn：中断使能配置。
                                                                    0-->屏蔽中断；
                                                                    1-->使能中断输出。 */
        unsigned int  statconddump              : 1;  /* bit[5]   : 0-->表示无条件dump统计数据，寄存器counters_m_val的值，实时反映统计计数器的值；
                                                                    1-->表示有条件dump数据，在给定的统计周期内发生out of bounds 事件，才会将统计计数器的值dump至寄存器counters_m_val中。 */
        unsigned int  intrusivemode             : 1;  /* bit[6]   : IntrusiveMode： 该总线不支持Trace功能，故此位无意义。 */
        unsigned int  filtbytealwayschainableen : 1;  /* bit[7]   : FiltByteAlwaysChainableEn：奇数和偶数计数器串行使能的全局配置：
                                                                    0-->不使能，此时，所有侧statistic counters都可以被Map；
                                                                    1-->使能，只有偶数statistic counters才可以被Map。 */
        unsigned int  reserved                  : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_TRANS_M_MAINCTL_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_MAINCTL_erren_START                      (0)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_MAINCTL_erren_END                        (0)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_MAINCTL_traceen_START                    (1)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_MAINCTL_traceen_END                      (1)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_MAINCTL_payloaden_START                  (2)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_MAINCTL_payloaden_END                    (2)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_MAINCTL_staten_START                     (3)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_MAINCTL_staten_END                       (3)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_MAINCTL_alarmen_START                    (4)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_MAINCTL_alarmen_END                      (4)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_MAINCTL_statconddump_START               (5)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_MAINCTL_statconddump_END                 (5)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_MAINCTL_intrusivemode_START              (6)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_MAINCTL_intrusivemode_END                (6)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_MAINCTL_filtbytealwayschainableen_START  (7)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_MAINCTL_filtbytealwayschainableen_END    (7)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_TRANS_M_CFGCTL_UNION
 结构说明  : DSS1_WR_TRANS_M_CFGCTL 寄存器结构定义。地址偏移量:0xB40C，初值:0x00000000，宽度:32
 寄存器说明: Packet Probe使能寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  globalen : 1;  /* bit[0]   : GlobalEn：Packet Probe使能信号，高有效。 */
        unsigned int  active   : 1;  /* bit[1]   : Active：Packet Probe的工作状态指示信号。
                                                   0-->当GlobalEn配置为0的几个cycle后，Active被拉低；
                                                   1-->当GlobalEn配置为1时，Active被拉高，此时不允许对Packet Probe进行配置。 */
        unsigned int  reserved : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_TRANS_M_CFGCTL_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_CFGCTL_globalen_START  (0)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_CFGCTL_globalen_END    (0)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_CFGCTL_active_START    (1)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_CFGCTL_active_END      (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_TRANS_M_STATPERIOD_UNION
 结构说明  : DSS1_WR_TRANS_M_STATPERIOD 寄存器结构定义。地址偏移量:0xB424，初值:0x00000000，宽度:32
 寄存器说明: 统计周期配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statperiod : 5;  /* bit[0-4] : 自动统计模式下的统计周期，统计周期= N_Cycle = 2^min(23,StatPeriod)，最大为8 mega cycles，最小为2 cycles。当配置为0时，自动统计模式被关闭，需要采用手动模式，也就是配置StatGo寄存器来实现带宽统计。 */
        unsigned int  reserved   : 27; /* bit[5-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_TRANS_M_STATPERIOD_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_STATPERIOD_statperiod_START  (0)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_STATPERIOD_statperiod_END    (4)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_TRANS_M_STATGO_UNION
 结构说明  : DSS1_WR_TRANS_M_STATGO 寄存器结构定义。地址偏移量:0xB428，初值:0x00000000，宽度:32
 寄存器说明: 手动带宽统计计时开始使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statgo   : 1;  /* bit[0]   : 当StatPeriod=0时，当globalen为1，向寄存器StatGo写1，则会将counter_m_val的值与statalarmmax或statalarmmin的值进行比较；读该寄存器始终返回0。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_TRANS_M_STATGO_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_STATGO_statgo_START    (0)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_STATGO_statgo_END      (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_TRANS_M_STATALARMMIN_UNION
 结构说明  : DSS1_WR_TRANS_M_STATALARMMIN 寄存器结构定义。地址偏移量:0xB42C，初值:0x00000000，宽度:32
 寄存器说明: 统计计数最小告警阈值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statalarmmin : 32; /* bit[0-31]: 当任意一个统计计数器的值小于StatAlarmMin的值，就触发告警寄存器。 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_TRANS_M_STATALARMMIN_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_STATALARMMIN_statalarmmin_START  (0)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_STATALARMMIN_statalarmmin_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_TRANS_M_STATALARMMAX_UNION
 结构说明  : DSS1_WR_TRANS_M_STATALARMMAX 寄存器结构定义。地址偏移量:0xB430，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器最大告警阈值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statalarmmax : 32; /* bit[0-31]: 当任意一个统计计数器的值大于StatAlarmMax的值，就触发告警寄存器。 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_TRANS_M_STATALARMMAX_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_STATALARMMAX_statalarmmax_START  (0)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_STATALARMMAX_statalarmmax_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_TRANS_M_STATALARMSTATUS_UNION
 结构说明  : DSS1_WR_TRANS_M_STATALARMSTATUS 寄存器结构定义。地址偏移量:0xB434，初值:0x00000000，宽度:32
 寄存器说明: 告警状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statalarmstatus : 1;  /* bit[0]   : 当任意一个统计计数器的值大于StatAlarmMax或小于StatAlarmMin，则该寄存器置位为1； */
        unsigned int  reserved        : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_TRANS_M_STATALARMSTATUS_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_STATALARMSTATUS_statalarmstatus_START  (0)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_STATALARMSTATUS_statalarmstatus_END    (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_TRANS_M_STATALARMCLR_UNION
 结构说明  : DSS1_WR_TRANS_M_STATALARMCLR 寄存器结构定义。地址偏移量:0xB438，初值:0x00000000，宽度:32
 寄存器说明: 告警状态清除寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statalarmclr : 1;  /* bit[0]   : 写1会清零StatAlarmStatus寄存器，读此寄存器返回总是0； */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_TRANS_M_STATALARMCLR_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_STATALARMCLR_statalarmclr_START  (0)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_STATALARMCLR_statalarmclr_END    (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_0_SRC_UNION
 结构说明  : DSS1_WR_TRANS_M_COUNTERS_0_SRC 寄存器结构定义。地址偏移量:0xB538，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_0_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：2~3）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：4~7）；
                                                         0x23-->Bin 3（delay：128~255；outstanding：8~15）；
                                                         0x24-->Bin 4（delay：>= 256；outstanding：>= 16）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_0_SRC_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_0_SRC_counters_0_src_START  (0)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_0_SRC_counters_0_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_0_ALARMMODE_UNION
 结构说明  : DSS1_WR_TRANS_M_COUNTERS_0_ALARMMODE 寄存器结构定义。地址偏移量:0xB53C，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_0_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_0_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_0_ALARMMODE_counters_0_alarmmode_START  (0)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_0_ALARMMODE_counters_0_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_0_VAL_UNION
 结构说明  : DSS1_WR_TRANS_M_COUNTERS_0_VAL 寄存器结构定义。地址偏移量:0xB540，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_0_val : 11; /* bit[0-10] : 当Counters_0_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_0_VAL_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_0_VAL_counters_0_val_START  (0)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_0_VAL_counters_0_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_1_SRC_UNION
 结构说明  : DSS1_WR_TRANS_M_COUNTERS_1_SRC 寄存器结构定义。地址偏移量:0xB54C，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_1_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：2~3）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：4~7）；
                                                         0x23-->Bin 3（delay：128~255；outstanding：8~15）；
                                                         0x24-->Bin 4（delay：>= 256；outstanding：>= 16）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_1_SRC_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_1_SRC_counters_1_src_START  (0)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_1_SRC_counters_1_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_1_ALARMMODE_UNION
 结构说明  : DSS1_WR_TRANS_M_COUNTERS_1_ALARMMODE 寄存器结构定义。地址偏移量:0xB550，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_1_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_1_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_1_ALARMMODE_counters_1_alarmmode_START  (0)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_1_ALARMMODE_counters_1_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_1_VAL_UNION
 结构说明  : DSS1_WR_TRANS_M_COUNTERS_1_VAL 寄存器结构定义。地址偏移量:0xB554，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_1_val : 11; /* bit[0-10] : 当Counters_1_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_1_VAL_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_1_VAL_counters_1_val_START  (0)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_1_VAL_counters_1_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_2_SRC_UNION
 结构说明  : DSS1_WR_TRANS_M_COUNTERS_2_SRC 寄存器结构定义。地址偏移量:0xB560，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_2_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：2~3）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：4~7）；
                                                         0x23-->Bin 3（delay：128~255；outstanding：8~15）；
                                                         0x24-->Bin 4（delay：>= 256；outstanding：>= 16）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_2_SRC_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_2_SRC_counters_2_src_START  (0)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_2_SRC_counters_2_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_2_ALARMMODE_UNION
 结构说明  : DSS1_WR_TRANS_M_COUNTERS_2_ALARMMODE 寄存器结构定义。地址偏移量:0xB564，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_2_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_2_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_2_ALARMMODE_counters_2_alarmmode_START  (0)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_2_ALARMMODE_counters_2_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_2_VAL_UNION
 结构说明  : DSS1_WR_TRANS_M_COUNTERS_2_VAL 寄存器结构定义。地址偏移量:0xB568，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_2_val : 11; /* bit[0-10] : 当Counters_2_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_2_VAL_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_2_VAL_counters_2_val_START  (0)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_2_VAL_counters_2_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_3_SRC_UNION
 结构说明  : DSS1_WR_TRANS_M_COUNTERS_3_SRC 寄存器结构定义。地址偏移量:0xB574，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_3_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：2~3）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：4~7）；
                                                         0x23-->Bin 3（delay：128~255；outstanding：8~15）；
                                                         0x24-->Bin 4（delay：>= 256；outstanding：>= 16）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_3_SRC_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_3_SRC_counters_3_src_START  (0)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_3_SRC_counters_3_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_3_ALARMMODE_UNION
 结构说明  : DSS1_WR_TRANS_M_COUNTERS_3_ALARMMODE 寄存器结构定义。地址偏移量:0xB578，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_3_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_3_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_3_ALARMMODE_counters_3_alarmmode_START  (0)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_3_ALARMMODE_counters_3_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_3_VAL_UNION
 结构说明  : DSS1_WR_TRANS_M_COUNTERS_3_VAL 寄存器结构定义。地址偏移量:0xB57C，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_3_val : 11; /* bit[0-10] : 当Counters_3_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_3_VAL_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_3_VAL_counters_3_val_START  (0)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_3_VAL_counters_3_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_4_SRC_UNION
 结构说明  : DSS1_WR_TRANS_M_COUNTERS_4_SRC 寄存器结构定义。地址偏移量:0xB588，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_4_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：2~3）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：4~7）；
                                                         0x23-->Bin 3（delay：128~255；outstanding：8~15）；
                                                         0x24-->Bin 4（delay：>= 256；outstanding：>= 16）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_4_SRC_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_4_SRC_counters_4_src_START  (0)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_4_SRC_counters_4_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_4_ALARMMODE_UNION
 结构说明  : DSS1_WR_TRANS_M_COUNTERS_4_ALARMMODE 寄存器结构定义。地址偏移量:0xB58C，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_4_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_4_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_4_ALARMMODE_counters_4_alarmmode_START  (0)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_4_ALARMMODE_counters_4_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_4_VAL_UNION
 结构说明  : DSS1_WR_TRANS_M_COUNTERS_4_VAL 寄存器结构定义。地址偏移量:0xB590，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_4_val : 11; /* bit[0-10] : 当Counters_4_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_4_VAL_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_4_VAL_counters_4_val_START  (0)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_4_VAL_counters_4_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_5_SRC_UNION
 结构说明  : DSS1_WR_TRANS_M_COUNTERS_5_SRC 寄存器结构定义。地址偏移量:0xB59C，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_5_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：2~3）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：4~7）；
                                                         0x23-->Bin 3（delay：128~255；outstanding：8~15）；
                                                         0x24-->Bin 4（delay：>= 256；outstanding：>= 16）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_5_SRC_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_5_SRC_counters_5_src_START  (0)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_5_SRC_counters_5_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_5_ALARMMODE_UNION
 结构说明  : DSS1_WR_TRANS_M_COUNTERS_5_ALARMMODE 寄存器结构定义。地址偏移量:0xB5A0，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_5_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_5_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_5_ALARMMODE_counters_5_alarmmode_START  (0)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_5_ALARMMODE_counters_5_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_5_VAL_UNION
 结构说明  : DSS1_WR_TRANS_M_COUNTERS_5_VAL 寄存器结构定义。地址偏移量:0xB5A4，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_5_val : 11; /* bit[0-10] : 当Counters_5_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_5_VAL_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_5_VAL_counters_5_val_START  (0)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_5_VAL_counters_5_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_6_SRC_UNION
 结构说明  : DSS1_WR_TRANS_M_COUNTERS_6_SRC 寄存器结构定义。地址偏移量:0xB5B0，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_6_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：2~3）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：4~7）；
                                                         0x23-->Bin 3（delay：128~255；outstanding：8~15）；
                                                         0x24-->Bin 4（delay：>= 256；outstanding：>= 16）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_6_SRC_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_6_SRC_counters_6_src_START  (0)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_6_SRC_counters_6_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_6_ALARMMODE_UNION
 结构说明  : DSS1_WR_TRANS_M_COUNTERS_6_ALARMMODE 寄存器结构定义。地址偏移量:0xB5B4，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_6_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_6_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_6_ALARMMODE_counters_6_alarmmode_START  (0)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_6_ALARMMODE_counters_6_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_6_VAL_UNION
 结构说明  : DSS1_WR_TRANS_M_COUNTERS_6_VAL 寄存器结构定义。地址偏移量:0xB5B8，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_6_val : 11; /* bit[0-10] : 当Counters_6_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_6_VAL_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_6_VAL_counters_6_val_START  (0)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_6_VAL_counters_6_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_7_SRC_UNION
 结构说明  : DSS1_WR_TRANS_M_COUNTERS_7_SRC 寄存器结构定义。地址偏移量:0xB5C4，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_7_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：2~3）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：4~7）；
                                                         0x23-->Bin 3（delay：128~255；outstanding：8~15）；
                                                         0x24-->Bin 4（delay：>= 256；outstanding：>= 16）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_7_SRC_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_7_SRC_counters_7_src_START  (0)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_7_SRC_counters_7_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_7_ALARMMODE_UNION
 结构说明  : DSS1_WR_TRANS_M_COUNTERS_7_ALARMMODE 寄存器结构定义。地址偏移量:0xB5C8，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_7_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_7_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_7_ALARMMODE_counters_7_alarmmode_START  (0)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_7_ALARMMODE_counters_7_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_7_VAL_UNION
 结构说明  : DSS1_WR_TRANS_M_COUNTERS_7_VAL 寄存器结构定义。地址偏移量:0xB5CC，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_7_val : 11; /* bit[0-10] : 当Counters_7_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_7_VAL_UNION;
#endif
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_7_VAL_counters_7_val_START  (0)
#define SOC_VIVO_BUS_DSS1_WR_TRANS_M_COUNTERS_7_VAL_counters_7_val_END    (10)




/****************************************************************************
                     (2/2) NOC_ISP
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_QOS_ID_COREID_UNION
 结构说明  : ISP_RD_QOS_ID_COREID 寄存器结构定义。地址偏移量:0x0000，初值:0xCE59F604，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coretypeid   : 8;  /* bit[0-7] : Field containing a checksum of the parameters of the IP. */
        unsigned int  corechecksum : 24; /* bit[8-31]: Field identifying the type of IP. */
    } reg;
} SOC_VIVO_BUS_ISP_RD_QOS_ID_COREID_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_QOS_ID_COREID_coretypeid_START    (0)
#define SOC_VIVO_BUS_ISP_RD_QOS_ID_COREID_coretypeid_END      (7)
#define SOC_VIVO_BUS_ISP_RD_QOS_ID_COREID_corechecksum_START  (8)
#define SOC_VIVO_BUS_ISP_RD_QOS_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_QOS_ID_REVISIONID_UNION
 结构说明  : ISP_RD_QOS_ID_REVISIONID 寄存器结构定义。地址偏移量:0x0004，初值:0x012D5300，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  userid    : 8;  /* bit[0-7] : Field containing a user defined value, not used anywhere inside the IP itself. */
        unsigned int  flexnocid : 24; /* bit[8-31]: Field containing the build revision of the software used to generate the IP HDL code. */
    } reg;
} SOC_VIVO_BUS_ISP_RD_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_QOS_ID_REVISIONID_userid_START     (0)
#define SOC_VIVO_BUS_ISP_RD_QOS_ID_REVISIONID_userid_END       (7)
#define SOC_VIVO_BUS_ISP_RD_QOS_ID_REVISIONID_flexnocid_START  (8)
#define SOC_VIVO_BUS_ISP_RD_QOS_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_QOS_PRIORITY_UNION
 结构说明  : ISP_RD_QOS_PRIORITY 寄存器结构定义。地址偏移量:0x0008，初值:0x80000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p0       : 2;  /* bit[0-1]  : In Regulator mode, defines the LOW hurry level. In Fixed/Limiter mode, defines the Urgency level for WRITE transactions. */
        unsigned int  reserved_0: 6;  /* bit[2-7]  : 保留 */
        unsigned int  p1       : 2;  /* bit[8-9]  : In Regulator mode, defines the HIGH hurry level. In Fixed/Limiter mode, defines the Urgency level for READ transactions. */
        unsigned int  reserved_1: 22; /* bit[10-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_QOS_PRIORITY_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_QOS_PRIORITY_p0_START        (0)
#define SOC_VIVO_BUS_ISP_RD_QOS_PRIORITY_p0_END          (1)
#define SOC_VIVO_BUS_ISP_RD_QOS_PRIORITY_p1_START        (8)
#define SOC_VIVO_BUS_ISP_RD_QOS_PRIORITY_p1_END          (9)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_QOS_MODE_UNION
 结构说明  : ISP_RD_QOS_MODE 寄存器结构定义。地址偏移量:0x000C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode     : 2;  /* bit[0-1] : Functional Mode: 0=Fixed, 1=Limiter, 2=Bypass, 3=Regulator. */
        unsigned int  reserved : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_QOS_MODE_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_QOS_MODE_mode_START      (0)
#define SOC_VIVO_BUS_ISP_RD_QOS_MODE_mode_END        (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_QOS_BANDWIDTH_UNION
 结构说明  : ISP_RD_QOS_BANDWIDTH 寄存器结构定义。地址偏移量:0x0010，初值:0x000002D0，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bandwidth : 13; /* bit[0-12] : Defines the bandwidth threshold in 1/256th-byte-per-cycle units. In other words, the desired rate in MBps is divided by frequency in MHz of the NIU, and then multiplied by 256. */
        unsigned int  reserved  : 19; /* bit[13-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_QOS_BANDWIDTH_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_QOS_BANDWIDTH_bandwidth_START  (0)
#define SOC_VIVO_BUS_ISP_RD_QOS_BANDWIDTH_bandwidth_END    (12)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_QOS_SATURATION_UNION
 结构说明  : ISP_RD_QOS_SATURATION 寄存器结构定义。地址偏移量:0x0014，初值:0x000003E8，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  saturation : 10; /* bit[0-9]  : Defines the size of the bandwidth counter, that is, the measurement window, in 16-byte units. In other words, the desired number of bytes divided by 16. */
        unsigned int  reserved   : 22; /* bit[10-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_QOS_SATURATION_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_QOS_SATURATION_saturation_START  (0)
#define SOC_VIVO_BUS_ISP_RD_QOS_SATURATION_saturation_END    (9)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_QOS_EXTCONTROL_UNION
 结构说明  : ISP_RD_QOS_EXTCONTROL 寄存器结构定义。地址偏移量:0x0018，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  socketqosen : 1;  /* bit[0-0] : Combines the Socket QoS with Regulator QoS. */
        unsigned int  extthren    : 1;  /* bit[1-1] : ExtThr input controls Low/High priority instead of bandwidth threshold. */
        unsigned int  intclken    : 1;  /* bit[2-2] : Replace the External reference by the local clock. */
        unsigned int  reserved    : 29; /* bit[3-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_QOS_EXTCONTROL_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_QOS_EXTCONTROL_socketqosen_START  (0)
#define SOC_VIVO_BUS_ISP_RD_QOS_EXTCONTROL_socketqosen_END    (0)
#define SOC_VIVO_BUS_ISP_RD_QOS_EXTCONTROL_extthren_START     (1)
#define SOC_VIVO_BUS_ISP_RD_QOS_EXTCONTROL_extthren_END       (1)
#define SOC_VIVO_BUS_ISP_RD_QOS_EXTCONTROL_intclken_START     (2)
#define SOC_VIVO_BUS_ISP_RD_QOS_EXTCONTROL_intclken_END       (2)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_QOS_ID_COREID_UNION
 结构说明  : ISP_WR_QOS_ID_COREID 寄存器结构定义。地址偏移量:0x0080，初值:0xA776D604，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coretypeid   : 8;  /* bit[0-7] : Field containing a checksum of the parameters of the IP. */
        unsigned int  corechecksum : 24; /* bit[8-31]: Field identifying the type of IP. */
    } reg;
} SOC_VIVO_BUS_ISP_WR_QOS_ID_COREID_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_QOS_ID_COREID_coretypeid_START    (0)
#define SOC_VIVO_BUS_ISP_WR_QOS_ID_COREID_coretypeid_END      (7)
#define SOC_VIVO_BUS_ISP_WR_QOS_ID_COREID_corechecksum_START  (8)
#define SOC_VIVO_BUS_ISP_WR_QOS_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_QOS_ID_REVISIONID_UNION
 结构说明  : ISP_WR_QOS_ID_REVISIONID 寄存器结构定义。地址偏移量:0x0084，初值:0x012D5300，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  userid    : 8;  /* bit[0-7] : Field containing a user defined value, not used anywhere inside the IP itself. */
        unsigned int  flexnocid : 24; /* bit[8-31]: Field containing the build revision of the software used to generate the IP HDL code. */
    } reg;
} SOC_VIVO_BUS_ISP_WR_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_QOS_ID_REVISIONID_userid_START     (0)
#define SOC_VIVO_BUS_ISP_WR_QOS_ID_REVISIONID_userid_END       (7)
#define SOC_VIVO_BUS_ISP_WR_QOS_ID_REVISIONID_flexnocid_START  (8)
#define SOC_VIVO_BUS_ISP_WR_QOS_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_QOS_PRIORITY_UNION
 结构说明  : ISP_WR_QOS_PRIORITY 寄存器结构定义。地址偏移量:0x0088，初值:0x80000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p0       : 2;  /* bit[0-1]  : In Regulator mode, defines the LOW hurry level. In Fixed/Limiter mode, defines the Urgency level for WRITE transactions. */
        unsigned int  reserved_0: 6;  /* bit[2-7]  : 保留 */
        unsigned int  p1       : 2;  /* bit[8-9]  : In Regulator mode, defines the HIGH hurry level. In Fixed/Limiter mode, defines the Urgency level for READ transactions. */
        unsigned int  reserved_1: 22; /* bit[10-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_QOS_PRIORITY_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_QOS_PRIORITY_p0_START        (0)
#define SOC_VIVO_BUS_ISP_WR_QOS_PRIORITY_p0_END          (1)
#define SOC_VIVO_BUS_ISP_WR_QOS_PRIORITY_p1_START        (8)
#define SOC_VIVO_BUS_ISP_WR_QOS_PRIORITY_p1_END          (9)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_QOS_MODE_UNION
 结构说明  : ISP_WR_QOS_MODE 寄存器结构定义。地址偏移量:0x008C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode     : 2;  /* bit[0-1] : Functional Mode: 0=Fixed, 1=Limiter, 2=Bypass, 3=Regulator. */
        unsigned int  reserved : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_QOS_MODE_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_QOS_MODE_mode_START      (0)
#define SOC_VIVO_BUS_ISP_WR_QOS_MODE_mode_END        (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_QOS_BANDWIDTH_UNION
 结构说明  : ISP_WR_QOS_BANDWIDTH 寄存器结构定义。地址偏移量:0x0090，初值:0x000009CC，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bandwidth : 13; /* bit[0-12] : Defines the bandwidth threshold in 1/256th-byte-per-cycle units. In other words, the desired rate in MBps is divided by frequency in MHz of the NIU, and then multiplied by 256. */
        unsigned int  reserved  : 19; /* bit[13-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_QOS_BANDWIDTH_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_QOS_BANDWIDTH_bandwidth_START  (0)
#define SOC_VIVO_BUS_ISP_WR_QOS_BANDWIDTH_bandwidth_END    (12)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_QOS_SATURATION_UNION
 结构说明  : ISP_WR_QOS_SATURATION 寄存器结构定义。地址偏移量:0x0094，初值:0x000003E8，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  saturation : 10; /* bit[0-9]  : Defines the size of the bandwidth counter, that is, the measurement window, in 16-byte units. In other words, the desired number of bytes divided by 16. */
        unsigned int  reserved   : 22; /* bit[10-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_QOS_SATURATION_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_QOS_SATURATION_saturation_START  (0)
#define SOC_VIVO_BUS_ISP_WR_QOS_SATURATION_saturation_END    (9)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_QOS_EXTCONTROL_UNION
 结构说明  : ISP_WR_QOS_EXTCONTROL 寄存器结构定义。地址偏移量:0x0098，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  socketqosen : 1;  /* bit[0-0] : Combines the Socket QoS with Regulator QoS. */
        unsigned int  extthren    : 1;  /* bit[1-1] : ExtThr input controls Low/High priority instead of bandwidth threshold. */
        unsigned int  intclken    : 1;  /* bit[2-2] : Replace the External reference by the local clock. */
        unsigned int  reserved    : 29; /* bit[3-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_QOS_EXTCONTROL_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_QOS_EXTCONTROL_socketqosen_START  (0)
#define SOC_VIVO_BUS_ISP_WR_QOS_EXTCONTROL_socketqosen_END    (0)
#define SOC_VIVO_BUS_ISP_WR_QOS_EXTCONTROL_extthren_START     (1)
#define SOC_VIVO_BUS_ISP_WR_QOS_EXTCONTROL_extthren_END       (1)
#define SOC_VIVO_BUS_ISP_WR_QOS_EXTCONTROL_intclken_START     (2)
#define SOC_VIVO_BUS_ISP_WR_QOS_EXTCONTROL_intclken_END       (2)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7T0VIVOBUS_RD_QOS_ID_COREID_UNION
 结构说明  : A7T0VIVOBUS_RD_QOS_ID_COREID 寄存器结构定义。地址偏移量:0x0100，初值:0xCB6A5D04，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coretypeid   : 8;  /* bit[0-7] : Field containing a checksum of the parameters of the IP. */
        unsigned int  corechecksum : 24; /* bit[8-31]: Field identifying the type of IP. */
    } reg;
} SOC_VIVO_BUS_A7T0VIVOBUS_RD_QOS_ID_COREID_UNION;
#endif
#define SOC_VIVO_BUS_A7T0VIVOBUS_RD_QOS_ID_COREID_coretypeid_START    (0)
#define SOC_VIVO_BUS_A7T0VIVOBUS_RD_QOS_ID_COREID_coretypeid_END      (7)
#define SOC_VIVO_BUS_A7T0VIVOBUS_RD_QOS_ID_COREID_corechecksum_START  (8)
#define SOC_VIVO_BUS_A7T0VIVOBUS_RD_QOS_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7T0VIVOBUS_RD_QOS_ID_REVISIONID_UNION
 结构说明  : A7T0VIVOBUS_RD_QOS_ID_REVISIONID 寄存器结构定义。地址偏移量:0x0104，初值:0x012D5300，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  userid    : 8;  /* bit[0-7] : Field containing a user defined value, not used anywhere inside the IP itself. */
        unsigned int  flexnocid : 24; /* bit[8-31]: Field containing the build revision of the software used to generate the IP HDL code. */
    } reg;
} SOC_VIVO_BUS_A7T0VIVOBUS_RD_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_VIVO_BUS_A7T0VIVOBUS_RD_QOS_ID_REVISIONID_userid_START     (0)
#define SOC_VIVO_BUS_A7T0VIVOBUS_RD_QOS_ID_REVISIONID_userid_END       (7)
#define SOC_VIVO_BUS_A7T0VIVOBUS_RD_QOS_ID_REVISIONID_flexnocid_START  (8)
#define SOC_VIVO_BUS_A7T0VIVOBUS_RD_QOS_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7T0VIVOBUS_RD_QOS_PRIORITY_UNION
 结构说明  : A7T0VIVOBUS_RD_QOS_PRIORITY 寄存器结构定义。地址偏移量:0x0108，初值:0x80000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p0       : 2;  /* bit[0-1]  : In Regulator mode, defines the LOW hurry level. In Fixed/Limiter mode, defines the Urgency level for WRITE transactions. */
        unsigned int  reserved_0: 6;  /* bit[2-7]  : 保留 */
        unsigned int  p1       : 2;  /* bit[8-9]  : In Regulator mode, defines the HIGH hurry level. In Fixed/Limiter mode, defines the Urgency level for READ transactions. */
        unsigned int  reserved_1: 22; /* bit[10-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7T0VIVOBUS_RD_QOS_PRIORITY_UNION;
#endif
#define SOC_VIVO_BUS_A7T0VIVOBUS_RD_QOS_PRIORITY_p0_START        (0)
#define SOC_VIVO_BUS_A7T0VIVOBUS_RD_QOS_PRIORITY_p0_END          (1)
#define SOC_VIVO_BUS_A7T0VIVOBUS_RD_QOS_PRIORITY_p1_START        (8)
#define SOC_VIVO_BUS_A7T0VIVOBUS_RD_QOS_PRIORITY_p1_END          (9)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7T0VIVOBUS_RD_QOS_MODE_UNION
 结构说明  : A7T0VIVOBUS_RD_QOS_MODE 寄存器结构定义。地址偏移量:0x010C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode     : 2;  /* bit[0-1] : Functional Mode: 0=Fixed, 1=Limiter, 2=Bypass, 3=Regulator. */
        unsigned int  reserved : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7T0VIVOBUS_RD_QOS_MODE_UNION;
#endif
#define SOC_VIVO_BUS_A7T0VIVOBUS_RD_QOS_MODE_mode_START      (0)
#define SOC_VIVO_BUS_A7T0VIVOBUS_RD_QOS_MODE_mode_END        (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7T0VIVOBUS_RD_QOS_BANDWIDTH_UNION
 结构说明  : A7T0VIVOBUS_RD_QOS_BANDWIDTH 寄存器结构定义。地址偏移量:0x0110，初值:0x00000180，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bandwidth : 13; /* bit[0-12] : Defines the bandwidth threshold in 1/256th-byte-per-cycle units. In other words, the desired rate in MBps is divided by frequency in MHz of the NIU, and then multiplied by 256. */
        unsigned int  reserved  : 19; /* bit[13-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7T0VIVOBUS_RD_QOS_BANDWIDTH_UNION;
#endif
#define SOC_VIVO_BUS_A7T0VIVOBUS_RD_QOS_BANDWIDTH_bandwidth_START  (0)
#define SOC_VIVO_BUS_A7T0VIVOBUS_RD_QOS_BANDWIDTH_bandwidth_END    (12)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7T0VIVOBUS_RD_QOS_SATURATION_UNION
 结构说明  : A7T0VIVOBUS_RD_QOS_SATURATION 寄存器结构定义。地址偏移量:0x0114，初值:0x000003E8，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  saturation : 10; /* bit[0-9]  : Defines the size of the bandwidth counter, that is, the measurement window, in 16-byte units. In other words, the desired number of bytes divided by 16. */
        unsigned int  reserved   : 22; /* bit[10-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7T0VIVOBUS_RD_QOS_SATURATION_UNION;
#endif
#define SOC_VIVO_BUS_A7T0VIVOBUS_RD_QOS_SATURATION_saturation_START  (0)
#define SOC_VIVO_BUS_A7T0VIVOBUS_RD_QOS_SATURATION_saturation_END    (9)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7T0VIVOBUS_RD_QOS_EXTCONTROL_UNION
 结构说明  : A7T0VIVOBUS_RD_QOS_EXTCONTROL 寄存器结构定义。地址偏移量:0x0118，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  socketqosen : 1;  /* bit[0-0] : Combines the Socket QoS with Regulator QoS. */
        unsigned int  extthren    : 1;  /* bit[1-1] : ExtThr input controls Low/High priority instead of bandwidth threshold. */
        unsigned int  intclken    : 1;  /* bit[2-2] : Replace the External reference by the local clock. */
        unsigned int  reserved    : 29; /* bit[3-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7T0VIVOBUS_RD_QOS_EXTCONTROL_UNION;
#endif
#define SOC_VIVO_BUS_A7T0VIVOBUS_RD_QOS_EXTCONTROL_socketqosen_START  (0)
#define SOC_VIVO_BUS_A7T0VIVOBUS_RD_QOS_EXTCONTROL_socketqosen_END    (0)
#define SOC_VIVO_BUS_A7T0VIVOBUS_RD_QOS_EXTCONTROL_extthren_START     (1)
#define SOC_VIVO_BUS_A7T0VIVOBUS_RD_QOS_EXTCONTROL_extthren_END       (1)
#define SOC_VIVO_BUS_A7T0VIVOBUS_RD_QOS_EXTCONTROL_intclken_START     (2)
#define SOC_VIVO_BUS_A7T0VIVOBUS_RD_QOS_EXTCONTROL_intclken_END       (2)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7T0VIVOBUS_WR_QOS_ID_COREID_UNION
 结构说明  : A7T0VIVOBUS_WR_QOS_ID_COREID 寄存器结构定义。地址偏移量:0x0180，初值:0x10873804，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coretypeid   : 8;  /* bit[0-7] : Field containing a checksum of the parameters of the IP. */
        unsigned int  corechecksum : 24; /* bit[8-31]: Field identifying the type of IP. */
    } reg;
} SOC_VIVO_BUS_A7T0VIVOBUS_WR_QOS_ID_COREID_UNION;
#endif
#define SOC_VIVO_BUS_A7T0VIVOBUS_WR_QOS_ID_COREID_coretypeid_START    (0)
#define SOC_VIVO_BUS_A7T0VIVOBUS_WR_QOS_ID_COREID_coretypeid_END      (7)
#define SOC_VIVO_BUS_A7T0VIVOBUS_WR_QOS_ID_COREID_corechecksum_START  (8)
#define SOC_VIVO_BUS_A7T0VIVOBUS_WR_QOS_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7T0VIVOBUS_WR_QOS_ID_REVISIONID_UNION
 结构说明  : A7T0VIVOBUS_WR_QOS_ID_REVISIONID 寄存器结构定义。地址偏移量:0x0184，初值:0x012D5300，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  userid    : 8;  /* bit[0-7] : Field containing a user defined value, not used anywhere inside the IP itself. */
        unsigned int  flexnocid : 24; /* bit[8-31]: Field containing the build revision of the software used to generate the IP HDL code. */
    } reg;
} SOC_VIVO_BUS_A7T0VIVOBUS_WR_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_VIVO_BUS_A7T0VIVOBUS_WR_QOS_ID_REVISIONID_userid_START     (0)
#define SOC_VIVO_BUS_A7T0VIVOBUS_WR_QOS_ID_REVISIONID_userid_END       (7)
#define SOC_VIVO_BUS_A7T0VIVOBUS_WR_QOS_ID_REVISIONID_flexnocid_START  (8)
#define SOC_VIVO_BUS_A7T0VIVOBUS_WR_QOS_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7T0VIVOBUS_WR_QOS_PRIORITY_UNION
 结构说明  : A7T0VIVOBUS_WR_QOS_PRIORITY 寄存器结构定义。地址偏移量:0x0188，初值:0x80000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  p0       : 2;  /* bit[0-1]  : In Regulator mode, defines the LOW hurry level. In Fixed/Limiter mode, defines the Urgency level for WRITE transactions. */
        unsigned int  reserved_0: 6;  /* bit[2-7]  : 保留 */
        unsigned int  p1       : 2;  /* bit[8-9]  : In Regulator mode, defines the HIGH hurry level. In Fixed/Limiter mode, defines the Urgency level for READ transactions. */
        unsigned int  reserved_1: 22; /* bit[10-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7T0VIVOBUS_WR_QOS_PRIORITY_UNION;
#endif
#define SOC_VIVO_BUS_A7T0VIVOBUS_WR_QOS_PRIORITY_p0_START        (0)
#define SOC_VIVO_BUS_A7T0VIVOBUS_WR_QOS_PRIORITY_p0_END          (1)
#define SOC_VIVO_BUS_A7T0VIVOBUS_WR_QOS_PRIORITY_p1_START        (8)
#define SOC_VIVO_BUS_A7T0VIVOBUS_WR_QOS_PRIORITY_p1_END          (9)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7T0VIVOBUS_WR_QOS_MODE_UNION
 结构说明  : A7T0VIVOBUS_WR_QOS_MODE 寄存器结构定义。地址偏移量:0x018C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode     : 2;  /* bit[0-1] : Functional Mode: 0=Fixed, 1=Limiter, 2=Bypass, 3=Regulator. */
        unsigned int  reserved : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7T0VIVOBUS_WR_QOS_MODE_UNION;
#endif
#define SOC_VIVO_BUS_A7T0VIVOBUS_WR_QOS_MODE_mode_START      (0)
#define SOC_VIVO_BUS_A7T0VIVOBUS_WR_QOS_MODE_mode_END        (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7T0VIVOBUS_WR_QOS_BANDWIDTH_UNION
 结构说明  : A7T0VIVOBUS_WR_QOS_BANDWIDTH 寄存器结构定义。地址偏移量:0x0190，初值:0x00000780，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bandwidth : 13; /* bit[0-12] : Defines the bandwidth threshold in 1/256th-byte-per-cycle units. In other words, the desired rate in MBps is divided by frequency in MHz of the NIU, and then multiplied by 256. */
        unsigned int  reserved  : 19; /* bit[13-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7T0VIVOBUS_WR_QOS_BANDWIDTH_UNION;
#endif
#define SOC_VIVO_BUS_A7T0VIVOBUS_WR_QOS_BANDWIDTH_bandwidth_START  (0)
#define SOC_VIVO_BUS_A7T0VIVOBUS_WR_QOS_BANDWIDTH_bandwidth_END    (12)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7T0VIVOBUS_WR_QOS_SATURATION_UNION
 结构说明  : A7T0VIVOBUS_WR_QOS_SATURATION 寄存器结构定义。地址偏移量:0x0194，初值:0x000003E8，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  saturation : 10; /* bit[0-9]  : Defines the size of the bandwidth counter, that is, the measurement window, in 16-byte units. In other words, the desired number of bytes divided by 16. */
        unsigned int  reserved   : 22; /* bit[10-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7T0VIVOBUS_WR_QOS_SATURATION_UNION;
#endif
#define SOC_VIVO_BUS_A7T0VIVOBUS_WR_QOS_SATURATION_saturation_START  (0)
#define SOC_VIVO_BUS_A7T0VIVOBUS_WR_QOS_SATURATION_saturation_END    (9)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7T0VIVOBUS_WR_QOS_EXTCONTROL_UNION
 结构说明  : A7T0VIVOBUS_WR_QOS_EXTCONTROL 寄存器结构定义。地址偏移量:0x0198，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  socketqosen : 1;  /* bit[0-0] : Combines the Socket QoS with Regulator QoS. */
        unsigned int  extthren    : 1;  /* bit[1-1] : ExtThr input controls Low/High priority instead of bandwidth threshold. */
        unsigned int  intclken    : 1;  /* bit[2-2] : Replace the External reference by the local clock. */
        unsigned int  reserved    : 29; /* bit[3-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7T0VIVOBUS_WR_QOS_EXTCONTROL_UNION;
#endif
#define SOC_VIVO_BUS_A7T0VIVOBUS_WR_QOS_EXTCONTROL_socketqosen_START  (0)
#define SOC_VIVO_BUS_A7T0VIVOBUS_WR_QOS_EXTCONTROL_socketqosen_END    (0)
#define SOC_VIVO_BUS_A7T0VIVOBUS_WR_QOS_EXTCONTROL_extthren_START     (1)
#define SOC_VIVO_BUS_A7T0VIVOBUS_WR_QOS_EXTCONTROL_extthren_END       (1)
#define SOC_VIVO_BUS_A7T0VIVOBUS_WR_QOS_EXTCONTROL_intclken_START     (2)
#define SOC_VIVO_BUS_A7T0VIVOBUS_WR_QOS_EXTCONTROL_intclken_END       (2)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_TRANS_F_ID_COREID_UNION
 结构说明  : ISP_RD_TRANS_F_ID_COREID 寄存器结构定义。地址偏移量:0x8000，初值:0x5F41C909，宽度:32
 寄存器说明: ISP_RD TransactionStatFilter域ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coretypeid   : 8;  /* bit[0-7] : 类型ID */
        unsigned int  corechecksum : 24; /* bit[8-31]: 配置参数的校验和 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_TRANS_F_ID_COREID_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_TRANS_F_ID_COREID_coretypeid_START    (0)
#define SOC_VIVO_BUS_ISP_RD_TRANS_F_ID_COREID_coretypeid_END      (7)
#define SOC_VIVO_BUS_ISP_RD_TRANS_F_ID_COREID_corechecksum_START  (8)
#define SOC_VIVO_BUS_ISP_RD_TRANS_F_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_TRANS_F_ID_REVISIONID_UNION
 结构说明  : ISP_RD_TRANS_F_ID_REVISIONID 寄存器结构定义。地址偏移量:0x8004，初值:0x012D5300，宽度:32
 寄存器说明: 代码版本
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  userid    : 8;  /* bit[0-7] : 用户自定义ID */
        unsigned int  flexnocid : 24; /* bit[8-31]: FlexNoC生成代码的软件版本 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_TRANS_F_ID_REVISIONID_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_TRANS_F_ID_REVISIONID_userid_START     (0)
#define SOC_VIVO_BUS_ISP_RD_TRANS_F_ID_REVISIONID_userid_END       (7)
#define SOC_VIVO_BUS_ISP_RD_TRANS_F_ID_REVISIONID_flexnocid_START  (8)
#define SOC_VIVO_BUS_ISP_RD_TRANS_F_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_TRANS_F_MODE_UNION
 结构说明  : ISP_RD_TRANS_F_MODE 寄存器结构定义。地址偏移量:0x8008，初值:0x00000000，宽度:32
 寄存器说明: ISP_RD Transaction Probe的Filter工作模式配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode     : 1;  /* bit[0-0] : 0-->handshake的模式，start event=begin request，end event=accept request；
                                                   1-->latency模式，start event=begin request + context ID，end event=begin response + context ID。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_TRANS_F_MODE_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_TRANS_F_MODE_mode_START      (0)
#define SOC_VIVO_BUS_ISP_RD_TRANS_F_MODE_mode_END        (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_TRANS_F_ADDRBASE_LOW_UNION
 结构说明  : ISP_RD_TRANS_F_ADDRBASE_LOW 寄存器结构定义。地址偏移量:0x800C，初值:0x00000000，宽度:32
 寄存器说明: 地址过滤基地址
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addrbase_low : 32; /* bit[0-31]: 地址过滤条件的基地址。 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_TRANS_F_ADDRBASE_LOW_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_TRANS_F_ADDRBASE_LOW_addrbase_low_START  (0)
#define SOC_VIVO_BUS_ISP_RD_TRANS_F_ADDRBASE_LOW_addrbase_low_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_TRANS_F_ADDRBASE_HIGH_UNION
 结构说明  : ISP_RD_TRANS_F_ADDRBASE_HIGH 寄存器结构定义。地址偏移量:0x8010，初值:0x00000000，宽度:32
 寄存器说明: 地址过滤基地址
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addrbase_high : 2;  /* bit[0-1] : 地址过滤条件的基地址。 */
        unsigned int  reserved      : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_TRANS_F_ADDRBASE_HIGH_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_TRANS_F_ADDRBASE_HIGH_addrbase_high_START  (0)
#define SOC_VIVO_BUS_ISP_RD_TRANS_F_ADDRBASE_HIGH_addrbase_high_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_TRANS_F_ADDRWINDOWSIZE_UNION
 结构说明  : ISP_RD_TRANS_F_ADDRWINDOWSIZE 寄存器结构定义。地址偏移量:0x8014，初值:0x00000000，宽度:32
 寄存器说明: 地址过滤窗口
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addrwindowsize : 6;  /* bit[0-5] : 地址过滤的Mask窗口大小。
                                                         例如：地址过滤的Mask窗口大小为64MB，WidowSize=log2(64MB)=26，此时，就配置filter_0_windowsize=0x1A；
                                                         Address Mask=~（2^max(WindowSize,packet.len)-1）=0xFC000000（packet.len为NOC内部表示一个packet包长变量的位宽，其值为6~7）；
                                                         过滤条件为：PacketAddress & AddressMask = AddressBase & AddressMask。 */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_TRANS_F_ADDRWINDOWSIZE_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_TRANS_F_ADDRWINDOWSIZE_addrwindowsize_START  (0)
#define SOC_VIVO_BUS_ISP_RD_TRANS_F_ADDRWINDOWSIZE_addrwindowsize_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_TRANS_F_OPCODE_UNION
 结构说明  : ISP_RD_TRANS_F_OPCODE 寄存器结构定义。地址偏移量:0x8020，初值:0x00000000，宽度:32
 寄存器说明: ISP_RD的Transaction Probe的Opcode过滤条件
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rden     : 1;  /* bit[0-0] : 配置为1时，过滤写数据包； */
        unsigned int  wren     : 1;  /* bit[1-1] : 配置为1时，过滤读数据包； */
        unsigned int  reserved : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_TRANS_F_OPCODE_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_TRANS_F_OPCODE_rden_START      (0)
#define SOC_VIVO_BUS_ISP_RD_TRANS_F_OPCODE_rden_END        (0)
#define SOC_VIVO_BUS_ISP_RD_TRANS_F_OPCODE_wren_START      (1)
#define SOC_VIVO_BUS_ISP_RD_TRANS_F_OPCODE_wren_END        (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_TRANS_F_USERBASE_UNION
 结构说明  : ISP_RD_TRANS_F_USERBASE 寄存器结构定义。地址偏移量:0x8024，初值:0x00000000，宽度:32
 寄存器说明: ISP_RD的Transaction Probe的User过滤条件
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  userbase : 5;  /* bit[0-4] : User信号过滤条件 */
        unsigned int  reserved : 27; /* bit[5-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_TRANS_F_USERBASE_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_TRANS_F_USERBASE_userbase_START  (0)
#define SOC_VIVO_BUS_ISP_RD_TRANS_F_USERBASE_userbase_END    (4)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_TRANS_F_USERMASK_UNION
 结构说明  : ISP_RD_TRANS_F_USERMASK 寄存器结构定义。地址偏移量:0x8028，初值:0x00000000，宽度:32
 寄存器说明: ISP_RD的Transaction Probe的User过滤条件Mask
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  usermask : 5;  /* bit[0-4] : 对UserBase进行Mask，选择UserBase中的任意几bit User信号作为过滤条件。
                                                   过滤条件：packet.User & UserMask = UserBase & UserMask。 */
        unsigned int  reserved : 27; /* bit[5-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_TRANS_F_USERMASK_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_TRANS_F_USERMASK_usermask_START  (0)
#define SOC_VIVO_BUS_ISP_RD_TRANS_F_USERMASK_usermask_END    (4)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_TRANS_F_SECURITYBASE_UNION
 结构说明  : ISP_RD_TRANS_F_SECURITYBASE 寄存器结构定义。地址偏移量:0x802C，初值:0x00000000，宽度:32
 寄存器说明: ISP_RD的Transaction Probe的安全过滤条件
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  securitybase : 1;  /* bit[0-0] : 0-->表示安全过滤条件；
                                                       1-->表示非安全过滤条件。 */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_TRANS_F_SECURITYBASE_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_TRANS_F_SECURITYBASE_securitybase_START  (0)
#define SOC_VIVO_BUS_ISP_RD_TRANS_F_SECURITYBASE_securitybase_END    (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_TRANS_F_SECURITYMASK_UNION
 结构说明  : ISP_RD_TRANS_F_SECURITYMASK 寄存器结构定义。地址偏移量:0x8030，初值:0x00000000，宽度:32
 寄存器说明: ISP_RD的Transaction Probe的安全过滤条件Mask
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  securitymask : 1;  /* bit[0-0] : 安全过滤条件：packet.Security & SecurityMask = SecurityBase & SecurityMasks；
                                                       也就是说当Filters_1_SecurityMask=1时安全过滤条件Filters_1_SecurityBase有效，可以过滤安全或非安全packet；否则，不起过滤作用； */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_TRANS_F_SECURITYMASK_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_TRANS_F_SECURITYMASK_securitymask_START  (0)
#define SOC_VIVO_BUS_ISP_RD_TRANS_F_SECURITYMASK_securitymask_END    (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_TRANS_P_ID_COREID_UNION
 结构说明  : ISP_RD_TRANS_P_ID_COREID 寄存器结构定义。地址偏移量:0x8080，初值:0xC92AA20A，宽度:32
 寄存器说明: ISP_RD TransactionStatProfilter域ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coretypeid   : 8;  /* bit[0-7] : 类型ID */
        unsigned int  corechecksum : 24; /* bit[8-31]: 配置参数的校验和 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_TRANS_P_ID_COREID_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_TRANS_P_ID_COREID_coretypeid_START    (0)
#define SOC_VIVO_BUS_ISP_RD_TRANS_P_ID_COREID_coretypeid_END      (7)
#define SOC_VIVO_BUS_ISP_RD_TRANS_P_ID_COREID_corechecksum_START  (8)
#define SOC_VIVO_BUS_ISP_RD_TRANS_P_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_TRANS_P_ID_REVISIONID_UNION
 结构说明  : ISP_RD_TRANS_P_ID_REVISIONID 寄存器结构定义。地址偏移量:0x8084，初值:0x012D5300，宽度:32
 寄存器说明: 代码版本
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  userid    : 8;  /* bit[0-7] : 用户自定义ID */
        unsigned int  flexnocid : 24; /* bit[8-31]: FlexNoC生成代码的软件版本 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_TRANS_P_ID_REVISIONID_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_TRANS_P_ID_REVISIONID_userid_START     (0)
#define SOC_VIVO_BUS_ISP_RD_TRANS_P_ID_REVISIONID_userid_END       (7)
#define SOC_VIVO_BUS_ISP_RD_TRANS_P_ID_REVISIONID_flexnocid_START  (8)
#define SOC_VIVO_BUS_ISP_RD_TRANS_P_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_TRANS_P_EN_UNION
 结构说明  : ISP_RD_TRANS_P_EN 寄存器结构定义。地址偏移量:0x8088，初值:0x00000000，宽度:32
 寄存器说明: transaction Probe的counter使能配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  en       : 1;  /* bit[0-0] : 当配置为1时，使能Transaction Probe的统计计数器 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_TRANS_P_EN_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_TRANS_P_EN_en_START        (0)
#define SOC_VIVO_BUS_ISP_RD_TRANS_P_EN_en_END          (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_TRANS_P_MODE_UNION
 结构说明  : ISP_RD_TRANS_P_MODE 寄存器结构定义。地址偏移量:0x808C，初值:0x00000000，宽度:32
 寄存器说明: ISP_RD Transaction Probe的工作模式配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode     : 1;  /* bit[0]   : 0-->统计latency；
                                                   1-->统计outstanding； */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_TRANS_P_MODE_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_TRANS_P_MODE_mode_START      (0)
#define SOC_VIVO_BUS_ISP_RD_TRANS_P_MODE_mode_END        (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_TRANS_P_THRESHOLDS_0_0_UNION
 结构说明  : ISP_RD_TRANS_P_THRESHOLDS_0_0 寄存器结构定义。地址偏移量:0x80AC，初值:0x00000000，宽度:32
 寄存器说明: ISP_RD Transaction Probe的bin_0配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  thresholds_0_0 : 2;  /* bit[0-1] : 0x0-->选择threshold_0（delay：40；outstanding：2）；
                                                         0x1-->选择threshold_1（delay：96；outstanding：5）；
                                                         0x2-->选择threshold_2（delay：128；-----------------）；
                                                         0x3-->选择threshold_3（delay：256；-----------------）； */
        unsigned int  reserved       : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_TRANS_P_THRESHOLDS_0_0_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_TRANS_P_THRESHOLDS_0_0_thresholds_0_0_START  (0)
#define SOC_VIVO_BUS_ISP_RD_TRANS_P_THRESHOLDS_0_0_thresholds_0_0_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_TRANS_P_THRESHOLDS_0_1_UNION
 结构说明  : ISP_RD_TRANS_P_THRESHOLDS_0_1 寄存器结构定义。地址偏移量:0x80B0，初值:0x00000000，宽度:32
 寄存器说明: ISP_RD Transaction Probe的bin_0配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  thresholds_0_1 : 2;  /* bit[0-1] : 0x0-->选择threshold_0（delay：1~40；outstanding：1~2）；
                                                         0x1-->选择threshold_1（delay：41~96；outstanding：3~5）；
                                                         0x2-->选择threshold_2（delay：97~128；-----------------）；
                                                         0x3-->选择threshold_3（delay：129~256；-----------------）； */
        unsigned int  reserved       : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_TRANS_P_THRESHOLDS_0_1_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_TRANS_P_THRESHOLDS_0_1_thresholds_0_1_START  (0)
#define SOC_VIVO_BUS_ISP_RD_TRANS_P_THRESHOLDS_0_1_thresholds_0_1_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_TRANS_P_OVERFLOWSTATUS_UNION
 结构说明  : ISP_RD_TRANS_P_OVERFLOWSTATUS 寄存器结构定义。地址偏移量:0x80EC，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器溢出状态
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  overflowstatus : 1;  /* bit[0-0] : 1表示统计计数器溢出 */
        unsigned int  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_TRANS_P_OVERFLOWSTATUS_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_TRANS_P_OVERFLOWSTATUS_overflowstatus_START  (0)
#define SOC_VIVO_BUS_ISP_RD_TRANS_P_OVERFLOWSTATUS_overflowstatus_END    (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_TRANS_P_OVERFLOWRESET_UNION
 结构说明  : ISP_RD_TRANS_P_OVERFLOWRESET 寄存器结构定义。地址偏移量:0x80F0，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器溢出状态清零
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  overflowreset : 1;  /* bit[0-0] : 写1时，OverflowStatus寄存器清零，读该寄存器时钟返回0 */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_TRANS_P_OVERFLOWRESET_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_TRANS_P_OVERFLOWRESET_overflowreset_START  (0)
#define SOC_VIVO_BUS_ISP_RD_TRANS_P_OVERFLOWRESET_overflowreset_END    (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_TRANS_P_PENDINGEVENTMODE_UNION
 结构说明  : ISP_RD_TRANS_P_PENDINGEVENTMODE 寄存器结构定义。地址偏移量:0x80F4，初值:0x00000000，宽度:32
 寄存器说明: outstanding统计技术工作模式配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pendingeventmode : 1;  /* bit[0-0] : 0x0-->当outstanding数量 > 0时，每个cycle都去触发计数器收集outstanding个数；
                                                           0x1-->当返回1个response时，就触发计数器收集outstanding个数。 */
        unsigned int  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_TRANS_P_PENDINGEVENTMODE_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_TRANS_P_PENDINGEVENTMODE_pendingeventmode_START  (0)
#define SOC_VIVO_BUS_ISP_RD_TRANS_P_PENDINGEVENTMODE_pendingeventmode_END    (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_TRANS_P_PRESCALER_UNION
 结构说明  : ISP_RD_TRANS_P_PRESCALER 寄存器结构定义。地址偏移量:0x80F8，初值:0x00000000，宽度:32
 寄存器说明: latency统计系数配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  prescaler : 8;  /* bit[0-7] : 0-->handshake的模式，start event=begin request，end event=accept request；
                                                    1-->latency模式，start event=begin request + context ID，end event=begin response + context ID。 */
        unsigned int  reserved  : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_TRANS_P_PRESCALER_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_TRANS_P_PRESCALER_prescaler_START  (0)
#define SOC_VIVO_BUS_ISP_RD_TRANS_P_PRESCALER_prescaler_END    (7)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_TRANS_M_ID_COREID_UNION
 结构说明  : ISP_RD_TRANS_M_ID_COREID 寄存器结构定义。地址偏移量:0x8400，初值:0x00D47706，宽度:32
 寄存器说明: ISP_RD Transaction probe域ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_coreid : 32; /* bit[0-31]: VcodecBus的Packet Probe的域ID。 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_TRANS_M_ID_COREID_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_ID_COREID_id_coreid_START  (0)
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_ID_COREID_id_coreid_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_TRANS_M_ID_REVISIONID_UNION
 结构说明  : ISP_RD_TRANS_M_ID_REVISIONID 寄存器结构定义。地址偏移量:0x8404，初值:0x012D5300，宽度:32
 寄存器说明: 总线代码版本寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_revisionid : 32; /* bit[0-31]: 低8bit自定义，高24bit是NOC的配置HUSH值。 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_TRANS_M_ID_REVISIONID_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_ID_REVISIONID_id_revisionid_START  (0)
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_ID_REVISIONID_id_revisionid_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_TRANS_M_MAINCTL_UNION
 结构说明  : ISP_RD_TRANS_M_MAINCTL 寄存器结构定义。地址偏移量:0x8408，初值:0x00000000，宽度:32
 寄存器说明: Transaction Probe全局控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  erren                     : 1;  /* bit[0]   : ErrEn：使能Packet Probe将检测到的任何错误状态的Packet上报给Observer。由于本总线的Packet Probe不支持trace功能，故此位无意义。 */
        unsigned int  traceen                   : 1;  /* bit[1]   : TraceEn：该总线不支持Trace功能，故此位无意义。 */
        unsigned int  payloaden                 : 1;  /* bit[2]   : PayloadEn：该总线不支持Trace功能，故此位无意义。 */
        unsigned int  staten                    : 1;  /* bit[3]   : StatEn：统计模型使能寄存器，当StatEn由0配置为1时，统计计数器被清零；当StatEn配置为0时，统计计数器被disabled。 */
        unsigned int  alarmen                   : 1;  /* bit[4]   : AlarmEn：中断使能配置。
                                                                    0-->屏蔽中断；
                                                                    1-->使能中断输出。 */
        unsigned int  statconddump              : 1;  /* bit[5]   : 0-->表示无条件dump统计数据，寄存器counters_m_val的值，实时反映统计计数器的值；
                                                                    1-->表示有条件dump数据，在给定的统计周期内发生out of bounds 事件，才会将统计计数器的值dump至寄存器counters_m_val中。 */
        unsigned int  intrusivemode             : 1;  /* bit[6]   : IntrusiveMode： 该总线不支持Trace功能，故此位无意义。 */
        unsigned int  filtbytealwayschainableen : 1;  /* bit[7]   : FiltByteAlwaysChainableEn：奇数和偶数计数器串行使能的全局配置：
                                                                    0-->不使能，此时，所有侧statistic counters都可以被Map；
                                                                    1-->使能，只有偶数statistic counters才可以被Map。 */
        unsigned int  reserved                  : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_TRANS_M_MAINCTL_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_MAINCTL_erren_START                      (0)
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_MAINCTL_erren_END                        (0)
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_MAINCTL_traceen_START                    (1)
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_MAINCTL_traceen_END                      (1)
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_MAINCTL_payloaden_START                  (2)
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_MAINCTL_payloaden_END                    (2)
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_MAINCTL_staten_START                     (3)
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_MAINCTL_staten_END                       (3)
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_MAINCTL_alarmen_START                    (4)
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_MAINCTL_alarmen_END                      (4)
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_MAINCTL_statconddump_START               (5)
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_MAINCTL_statconddump_END                 (5)
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_MAINCTL_intrusivemode_START              (6)
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_MAINCTL_intrusivemode_END                (6)
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_MAINCTL_filtbytealwayschainableen_START  (7)
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_MAINCTL_filtbytealwayschainableen_END    (7)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_TRANS_M_CFGCTL_UNION
 结构说明  : ISP_RD_TRANS_M_CFGCTL 寄存器结构定义。地址偏移量:0x840C，初值:0x00000000，宽度:32
 寄存器说明: Packet Probe使能寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  globalen : 1;  /* bit[0]   : GlobalEn：Packet Probe使能信号，高有效。 */
        unsigned int  active   : 1;  /* bit[1]   : Active：Packet Probe的工作状态指示信号。
                                                   0-->当GlobalEn配置为0的几个cycle后，Active被拉低；
                                                   1-->当GlobalEn配置为1时，Active被拉高，此时不允许对Packet Probe进行配置。 */
        unsigned int  reserved : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_TRANS_M_CFGCTL_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_CFGCTL_globalen_START  (0)
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_CFGCTL_globalen_END    (0)
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_CFGCTL_active_START    (1)
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_CFGCTL_active_END      (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_TRANS_M_STATPERIOD_UNION
 结构说明  : ISP_RD_TRANS_M_STATPERIOD 寄存器结构定义。地址偏移量:0x8424，初值:0x00000000，宽度:32
 寄存器说明: 统计周期配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statperiod : 5;  /* bit[0-4] : 自动统计模式下的统计周期，统计周期= N_Cycle = 2^min(23,StatPeriod)，最大为8 mega cycles，最小为2 cycles。当配置为0时，自动统计模式被关闭，需要采用手动模式，也就是配置StatGo寄存器来实现带宽统计。 */
        unsigned int  reserved   : 27; /* bit[5-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_TRANS_M_STATPERIOD_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_STATPERIOD_statperiod_START  (0)
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_STATPERIOD_statperiod_END    (4)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_TRANS_M_STATGO_UNION
 结构说明  : ISP_RD_TRANS_M_STATGO 寄存器结构定义。地址偏移量:0x8428，初值:0x00000000，宽度:32
 寄存器说明: 手动带宽统计计时开始使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statgo   : 1;  /* bit[0]   : 当StatPeriod=0时，当globalen为1，向寄存器StatGo写1，则会将counter_m_val的值与statalarmmax或statalarmmin的值进行比较；读该寄存器始终返回0。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_TRANS_M_STATGO_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_STATGO_statgo_START    (0)
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_STATGO_statgo_END      (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_TRANS_M_STATALARMMIN_UNION
 结构说明  : ISP_RD_TRANS_M_STATALARMMIN 寄存器结构定义。地址偏移量:0x842C，初值:0x00000000，宽度:32
 寄存器说明: 统计计数最小告警阈值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statalarmmin : 32; /* bit[0-31]: 当任意一个统计计数器的值小于StatAlarmMin的值，就触发告警寄存器。 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_TRANS_M_STATALARMMIN_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_STATALARMMIN_statalarmmin_START  (0)
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_STATALARMMIN_statalarmmin_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_TRANS_M_STATALARMMAX_UNION
 结构说明  : ISP_RD_TRANS_M_STATALARMMAX 寄存器结构定义。地址偏移量:0x8430，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器最大告警阈值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statalarmmax : 32; /* bit[0-31]: 当任意一个统计计数器的值大于StatAlarmMax的值，就触发告警寄存器。 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_TRANS_M_STATALARMMAX_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_STATALARMMAX_statalarmmax_START  (0)
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_STATALARMMAX_statalarmmax_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_TRANS_M_STATALARMSTATUS_UNION
 结构说明  : ISP_RD_TRANS_M_STATALARMSTATUS 寄存器结构定义。地址偏移量:0x8434，初值:0x00000000，宽度:32
 寄存器说明: 告警状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statalarmstatus : 1;  /* bit[0]   : 当任意一个统计计数器的值大于StatAlarmMax或小于StatAlarmMin，则该寄存器置位为1； */
        unsigned int  reserved        : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_TRANS_M_STATALARMSTATUS_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_STATALARMSTATUS_statalarmstatus_START  (0)
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_STATALARMSTATUS_statalarmstatus_END    (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_TRANS_M_STATALARMCLR_UNION
 结构说明  : ISP_RD_TRANS_M_STATALARMCLR 寄存器结构定义。地址偏移量:0x8438，初值:0x00000000，宽度:32
 寄存器说明: 告警状态清除寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statalarmclr : 1;  /* bit[0]   : 写1会清零StatAlarmStatus寄存器，读此寄存器返回总是0； */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_TRANS_M_STATALARMCLR_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_STATALARMCLR_statalarmclr_START  (0)
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_STATALARMCLR_statalarmclr_END    (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_0_SRC_UNION
 结构说明  : ISP_RD_TRANS_M_COUNTERS_0_SRC 寄存器结构定义。地址偏移量:0x8538，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_0_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：2~4）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：>= 5）；
                                                         0x23-->Bin 3（delay：128~255；----------------）；
                                                         0x24-->Bin 4（delay：>= 256；----------------）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_0_SRC_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_0_SRC_counters_0_src_START  (0)
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_0_SRC_counters_0_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_0_ALARMMODE_UNION
 结构说明  : ISP_RD_TRANS_M_COUNTERS_0_ALARMMODE 寄存器结构定义。地址偏移量:0x853C，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_0_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_0_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_0_ALARMMODE_counters_0_alarmmode_START  (0)
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_0_ALARMMODE_counters_0_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_0_VAL_UNION
 结构说明  : ISP_RD_TRANS_M_COUNTERS_0_VAL 寄存器结构定义。地址偏移量:0x8540，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_0_val : 11; /* bit[0-10] : 当Counters_0_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_0_VAL_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_0_VAL_counters_0_val_START  (0)
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_0_VAL_counters_0_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_1_SRC_UNION
 结构说明  : ISP_RD_TRANS_M_COUNTERS_1_SRC 寄存器结构定义。地址偏移量:0x854C，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_1_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：2~4）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：>= 5）；
                                                         0x23-->Bin 3（delay：128~255；----------------）；
                                                         0x24-->Bin 4（delay：>= 256；----------------）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_1_SRC_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_1_SRC_counters_1_src_START  (0)
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_1_SRC_counters_1_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_1_ALARMMODE_UNION
 结构说明  : ISP_RD_TRANS_M_COUNTERS_1_ALARMMODE 寄存器结构定义。地址偏移量:0x8550，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_1_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_1_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_1_ALARMMODE_counters_1_alarmmode_START  (0)
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_1_ALARMMODE_counters_1_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_1_VAL_UNION
 结构说明  : ISP_RD_TRANS_M_COUNTERS_1_VAL 寄存器结构定义。地址偏移量:0x8554，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_1_val : 11; /* bit[0-10] : 当Counters_1_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_1_VAL_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_1_VAL_counters_1_val_START  (0)
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_1_VAL_counters_1_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_2_SRC_UNION
 结构说明  : ISP_RD_TRANS_M_COUNTERS_2_SRC 寄存器结构定义。地址偏移量:0x8560，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_2_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：2~4）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：>= 5）；
                                                         0x23-->Bin 3（delay：128~255；----------------）；
                                                         0x24-->Bin 4（delay：>= 256；----------------）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_2_SRC_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_2_SRC_counters_2_src_START  (0)
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_2_SRC_counters_2_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_2_ALARMMODE_UNION
 结构说明  : ISP_RD_TRANS_M_COUNTERS_2_ALARMMODE 寄存器结构定义。地址偏移量:0x8564，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_2_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_2_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_2_ALARMMODE_counters_2_alarmmode_START  (0)
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_2_ALARMMODE_counters_2_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_2_VAL_UNION
 结构说明  : ISP_RD_TRANS_M_COUNTERS_2_VAL 寄存器结构定义。地址偏移量:0x8568，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_2_val : 11; /* bit[0-10] : 当Counters_2_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_2_VAL_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_2_VAL_counters_2_val_START  (0)
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_2_VAL_counters_2_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_3_SRC_UNION
 结构说明  : ISP_RD_TRANS_M_COUNTERS_3_SRC 寄存器结构定义。地址偏移量:0x8574，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_3_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：2~4）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：>= 5）；
                                                         0x23-->Bin 3（delay：128~255；----------------）；
                                                         0x24-->Bin 4（delay：>= 256；----------------）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_3_SRC_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_3_SRC_counters_3_src_START  (0)
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_3_SRC_counters_3_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_3_ALARMMODE_UNION
 结构说明  : ISP_RD_TRANS_M_COUNTERS_3_ALARMMODE 寄存器结构定义。地址偏移量:0x8578，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_3_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_3_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_3_ALARMMODE_counters_3_alarmmode_START  (0)
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_3_ALARMMODE_counters_3_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_3_VAL_UNION
 结构说明  : ISP_RD_TRANS_M_COUNTERS_3_VAL 寄存器结构定义。地址偏移量:0x857C，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_3_val : 11; /* bit[0-10] : 当Counters_3_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_3_VAL_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_3_VAL_counters_3_val_START  (0)
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_3_VAL_counters_3_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_4_SRC_UNION
 结构说明  : ISP_RD_TRANS_M_COUNTERS_4_SRC 寄存器结构定义。地址偏移量:0x8588，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_4_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：2~4）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：>= 5）；
                                                         0x23-->Bin 3（delay：128~255；----------------）；
                                                         0x24-->Bin 4（delay：>= 256；----------------）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_4_SRC_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_4_SRC_counters_4_src_START  (0)
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_4_SRC_counters_4_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_4_ALARMMODE_UNION
 结构说明  : ISP_RD_TRANS_M_COUNTERS_4_ALARMMODE 寄存器结构定义。地址偏移量:0x858C，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_4_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_4_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_4_ALARMMODE_counters_4_alarmmode_START  (0)
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_4_ALARMMODE_counters_4_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_4_VAL_UNION
 结构说明  : ISP_RD_TRANS_M_COUNTERS_4_VAL 寄存器结构定义。地址偏移量:0x8590，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_4_val : 11; /* bit[0-10] : 当Counters_4_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_4_VAL_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_4_VAL_counters_4_val_START  (0)
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_4_VAL_counters_4_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_5_SRC_UNION
 结构说明  : ISP_RD_TRANS_M_COUNTERS_5_SRC 寄存器结构定义。地址偏移量:0x859C，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_5_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：2~4）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：>= 5）；
                                                         0x23-->Bin 3（delay：128~255；----------------）；
                                                         0x24-->Bin 4（delay：>= 256；----------------）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_5_SRC_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_5_SRC_counters_5_src_START  (0)
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_5_SRC_counters_5_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_5_ALARMMODE_UNION
 结构说明  : ISP_RD_TRANS_M_COUNTERS_5_ALARMMODE 寄存器结构定义。地址偏移量:0x85A0，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_5_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_5_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_5_ALARMMODE_counters_5_alarmmode_START  (0)
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_5_ALARMMODE_counters_5_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_5_VAL_UNION
 结构说明  : ISP_RD_TRANS_M_COUNTERS_5_VAL 寄存器结构定义。地址偏移量:0x85A4，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_5_val : 11; /* bit[0-10] : 当Counters_5_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_5_VAL_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_5_VAL_counters_5_val_START  (0)
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_5_VAL_counters_5_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_6_SRC_UNION
 结构说明  : ISP_RD_TRANS_M_COUNTERS_6_SRC 寄存器结构定义。地址偏移量:0x85B0，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_6_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：2~4）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：>= 5）；
                                                         0x23-->Bin 3（delay：128~255；----------------）；
                                                         0x24-->Bin 4（delay：>= 256；----------------）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_6_SRC_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_6_SRC_counters_6_src_START  (0)
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_6_SRC_counters_6_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_6_ALARMMODE_UNION
 结构说明  : ISP_RD_TRANS_M_COUNTERS_6_ALARMMODE 寄存器结构定义。地址偏移量:0x85B4，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_6_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_6_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_6_ALARMMODE_counters_6_alarmmode_START  (0)
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_6_ALARMMODE_counters_6_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_6_VAL_UNION
 结构说明  : ISP_RD_TRANS_M_COUNTERS_6_VAL 寄存器结构定义。地址偏移量:0x85B8，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_6_val : 11; /* bit[0-10] : 当Counters_6_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_6_VAL_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_6_VAL_counters_6_val_START  (0)
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_6_VAL_counters_6_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_7_SRC_UNION
 结构说明  : ISP_RD_TRANS_M_COUNTERS_7_SRC 寄存器结构定义。地址偏移量:0x85C4，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_7_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：2~4）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：>= 5）；
                                                         0x23-->Bin 3（delay：128~255；----------------）；
                                                         0x24-->Bin 4（delay：>= 256；----------------）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_7_SRC_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_7_SRC_counters_7_src_START  (0)
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_7_SRC_counters_7_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_7_ALARMMODE_UNION
 结构说明  : ISP_RD_TRANS_M_COUNTERS_7_ALARMMODE 寄存器结构定义。地址偏移量:0x85C8，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_7_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_7_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_7_ALARMMODE_counters_7_alarmmode_START  (0)
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_7_ALARMMODE_counters_7_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_7_VAL_UNION
 结构说明  : ISP_RD_TRANS_M_COUNTERS_7_VAL 寄存器结构定义。地址偏移量:0x85CC，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_7_val : 11; /* bit[0-10] : 当Counters_7_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_7_VAL_UNION;
#endif
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_7_VAL_counters_7_val_START  (0)
#define SOC_VIVO_BUS_ISP_RD_TRANS_M_COUNTERS_7_VAL_counters_7_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_TRANS_F_ID_COREID_UNION
 结构说明  : ISP_WR_TRANS_F_ID_COREID 寄存器结构定义。地址偏移量:0x9000，初值:0xCAF00D09，宽度:32
 寄存器说明: ISP_WR TransactionStatFilter域ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coretypeid   : 8;  /* bit[0-7] : 类型ID */
        unsigned int  corechecksum : 24; /* bit[8-31]: 配置参数的校验和 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_TRANS_F_ID_COREID_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_TRANS_F_ID_COREID_coretypeid_START    (0)
#define SOC_VIVO_BUS_ISP_WR_TRANS_F_ID_COREID_coretypeid_END      (7)
#define SOC_VIVO_BUS_ISP_WR_TRANS_F_ID_COREID_corechecksum_START  (8)
#define SOC_VIVO_BUS_ISP_WR_TRANS_F_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_TRANS_F_ID_REVISIONID_UNION
 结构说明  : ISP_WR_TRANS_F_ID_REVISIONID 寄存器结构定义。地址偏移量:0x9004，初值:0x012D5300，宽度:32
 寄存器说明: 代码版本
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  userid    : 8;  /* bit[0-7] : 用户自定义ID */
        unsigned int  flexnocid : 24; /* bit[8-31]: FlexNoC生成代码的软件版本 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_TRANS_F_ID_REVISIONID_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_TRANS_F_ID_REVISIONID_userid_START     (0)
#define SOC_VIVO_BUS_ISP_WR_TRANS_F_ID_REVISIONID_userid_END       (7)
#define SOC_VIVO_BUS_ISP_WR_TRANS_F_ID_REVISIONID_flexnocid_START  (8)
#define SOC_VIVO_BUS_ISP_WR_TRANS_F_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_TRANS_F_MODE_UNION
 结构说明  : ISP_WR_TRANS_F_MODE 寄存器结构定义。地址偏移量:0x9008，初值:0x00000000，宽度:32
 寄存器说明: ISP_WR Transaction Probe的Filter工作模式配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode     : 1;  /* bit[0-0] : 0-->handshake的模式，start event=begin request，end event=accept request；
                                                   1-->latency模式，start event=begin request + context ID，end event=begin response + context ID。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_TRANS_F_MODE_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_TRANS_F_MODE_mode_START      (0)
#define SOC_VIVO_BUS_ISP_WR_TRANS_F_MODE_mode_END        (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_TRANS_F_ADDRBASE_LOW_UNION
 结构说明  : ISP_WR_TRANS_F_ADDRBASE_LOW 寄存器结构定义。地址偏移量:0x900C，初值:0x00000000，宽度:32
 寄存器说明: 地址过滤基地址
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addrbase_low : 32; /* bit[0-31]: 地址过滤条件的基地址。 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_TRANS_F_ADDRBASE_LOW_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_TRANS_F_ADDRBASE_LOW_addrbase_low_START  (0)
#define SOC_VIVO_BUS_ISP_WR_TRANS_F_ADDRBASE_LOW_addrbase_low_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_TRANS_F_ADDRBASE_HIGH_UNION
 结构说明  : ISP_WR_TRANS_F_ADDRBASE_HIGH 寄存器结构定义。地址偏移量:0x9010，初值:0x00000000，宽度:32
 寄存器说明: 地址过滤基地址
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addrbase_high : 2;  /* bit[0-1] : 地址过滤条件的基地址。 */
        unsigned int  reserved      : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_TRANS_F_ADDRBASE_HIGH_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_TRANS_F_ADDRBASE_HIGH_addrbase_high_START  (0)
#define SOC_VIVO_BUS_ISP_WR_TRANS_F_ADDRBASE_HIGH_addrbase_high_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_TRANS_F_ADDRWINDOWSIZE_UNION
 结构说明  : ISP_WR_TRANS_F_ADDRWINDOWSIZE 寄存器结构定义。地址偏移量:0x9014，初值:0x00000000，宽度:32
 寄存器说明: 地址过滤窗口
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addrwindowsize : 6;  /* bit[0-5] : 地址过滤的Mask窗口大小。
                                                         例如：地址过滤的Mask窗口大小为64MB，WidowSize=log2(64MB)=26，此时，就配置filter_0_windowsize=0x1A；
                                                         Address Mask=~（2^max(WindowSize,packet.len)-1）=0xFC000000（packet.len为NOC内部表示一个packet包长变量的位宽，其值为6~7）；
                                                         过滤条件为：PacketAddress & AddressMask = AddressBase & AddressMask。 */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_TRANS_F_ADDRWINDOWSIZE_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_TRANS_F_ADDRWINDOWSIZE_addrwindowsize_START  (0)
#define SOC_VIVO_BUS_ISP_WR_TRANS_F_ADDRWINDOWSIZE_addrwindowsize_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_TRANS_F_OPCODE_UNION
 结构说明  : ISP_WR_TRANS_F_OPCODE 寄存器结构定义。地址偏移量:0x9020，初值:0x00000000，宽度:32
 寄存器说明: ISP_WR的Transaction Probe的Opcode过滤条件
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rden     : 1;  /* bit[0-0] : 配置为1时，过滤写数据包； */
        unsigned int  wren     : 1;  /* bit[1-1] : 配置为1时，过滤读数据包； */
        unsigned int  reserved : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_TRANS_F_OPCODE_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_TRANS_F_OPCODE_rden_START      (0)
#define SOC_VIVO_BUS_ISP_WR_TRANS_F_OPCODE_rden_END        (0)
#define SOC_VIVO_BUS_ISP_WR_TRANS_F_OPCODE_wren_START      (1)
#define SOC_VIVO_BUS_ISP_WR_TRANS_F_OPCODE_wren_END        (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_TRANS_F_USERBASE_UNION
 结构说明  : ISP_WR_TRANS_F_USERBASE 寄存器结构定义。地址偏移量:0x9024，初值:0x00000000，宽度:32
 寄存器说明: ISP_WR的Transaction Probe的User过滤条件
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  userbase : 5;  /* bit[0-4] : User信号过滤条件 */
        unsigned int  reserved : 27; /* bit[5-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_TRANS_F_USERBASE_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_TRANS_F_USERBASE_userbase_START  (0)
#define SOC_VIVO_BUS_ISP_WR_TRANS_F_USERBASE_userbase_END    (4)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_TRANS_F_USERMASK_UNION
 结构说明  : ISP_WR_TRANS_F_USERMASK 寄存器结构定义。地址偏移量:0x9028，初值:0x00000000，宽度:32
 寄存器说明: ISP_WR的Transaction Probe的User过滤条件Mask
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  usermask : 5;  /* bit[0-4] : 对UserBase进行Mask，选择UserBase中的任意几bit User信号作为过滤条件。
                                                   过滤条件：packet.User & UserMask = UserBase & UserMask。 */
        unsigned int  reserved : 27; /* bit[5-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_TRANS_F_USERMASK_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_TRANS_F_USERMASK_usermask_START  (0)
#define SOC_VIVO_BUS_ISP_WR_TRANS_F_USERMASK_usermask_END    (4)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_TRANS_F_SECURITYBASE_UNION
 结构说明  : ISP_WR_TRANS_F_SECURITYBASE 寄存器结构定义。地址偏移量:0x902C，初值:0x00000000，宽度:32
 寄存器说明: ISP_WR的Transaction Probe的安全过滤条件
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  securitybase : 1;  /* bit[0-0] : 0-->表示安全过滤条件；
                                                       1-->表示非安全过滤条件。 */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_TRANS_F_SECURITYBASE_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_TRANS_F_SECURITYBASE_securitybase_START  (0)
#define SOC_VIVO_BUS_ISP_WR_TRANS_F_SECURITYBASE_securitybase_END    (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_TRANS_F_SECURITYMASK_UNION
 结构说明  : ISP_WR_TRANS_F_SECURITYMASK 寄存器结构定义。地址偏移量:0x9030，初值:0x00000000，宽度:32
 寄存器说明: ISP_WR的Transaction Probe的安全过滤条件Mask
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  securitymask : 1;  /* bit[0-0] : 安全过滤条件：packet.Security & SecurityMask = SecurityBase & SecurityMasks；
                                                       也就是说当Filters_1_SecurityMask=1时安全过滤条件Filters_1_SecurityBase有效，可以过滤安全或非安全packet；否则，不起过滤作用； */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_TRANS_F_SECURITYMASK_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_TRANS_F_SECURITYMASK_securitymask_START  (0)
#define SOC_VIVO_BUS_ISP_WR_TRANS_F_SECURITYMASK_securitymask_END    (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_TRANS_P_ID_COREID_UNION
 结构说明  : ISP_WR_TRANS_P_ID_COREID 寄存器结构定义。地址偏移量:0x9080，初值:0x154ABB0A，宽度:32
 寄存器说明: ISP_RD TransactionStatProfilter域ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coretypeid   : 8;  /* bit[0-7] : 类型ID */
        unsigned int  corechecksum : 24; /* bit[8-31]: 配置参数的校验和 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_TRANS_P_ID_COREID_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_TRANS_P_ID_COREID_coretypeid_START    (0)
#define SOC_VIVO_BUS_ISP_WR_TRANS_P_ID_COREID_coretypeid_END      (7)
#define SOC_VIVO_BUS_ISP_WR_TRANS_P_ID_COREID_corechecksum_START  (8)
#define SOC_VIVO_BUS_ISP_WR_TRANS_P_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_TRANS_P_ID_REVISIONID_UNION
 结构说明  : ISP_WR_TRANS_P_ID_REVISIONID 寄存器结构定义。地址偏移量:0x9084，初值:0x012D5300，宽度:32
 寄存器说明: 代码版本
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  userid    : 8;  /* bit[0-7] : 用户自定义ID */
        unsigned int  flexnocid : 24; /* bit[8-31]: FlexNoC生成代码的软件版本 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_TRANS_P_ID_REVISIONID_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_TRANS_P_ID_REVISIONID_userid_START     (0)
#define SOC_VIVO_BUS_ISP_WR_TRANS_P_ID_REVISIONID_userid_END       (7)
#define SOC_VIVO_BUS_ISP_WR_TRANS_P_ID_REVISIONID_flexnocid_START  (8)
#define SOC_VIVO_BUS_ISP_WR_TRANS_P_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_TRANS_P_EN_UNION
 结构说明  : ISP_WR_TRANS_P_EN 寄存器结构定义。地址偏移量:0x9088，初值:0x00000000，宽度:32
 寄存器说明: transaction Probe的counter使能配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  en       : 1;  /* bit[0-0] : 当配置为1时，使能Transaction Probe的统计计数器 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_TRANS_P_EN_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_TRANS_P_EN_en_START        (0)
#define SOC_VIVO_BUS_ISP_WR_TRANS_P_EN_en_END          (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_TRANS_P_MODE_UNION
 结构说明  : ISP_WR_TRANS_P_MODE 寄存器结构定义。地址偏移量:0x908C，初值:0x00000000，宽度:32
 寄存器说明: ISP_WR Transaction Probe的工作模式配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode     : 1;  /* bit[0]   : 0-->统计latency；
                                                   1-->统计outstanding； */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_TRANS_P_MODE_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_TRANS_P_MODE_mode_START      (0)
#define SOC_VIVO_BUS_ISP_WR_TRANS_P_MODE_mode_END        (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_TRANS_P_THRESHOLDS_0_0_UNION
 结构说明  : ISP_WR_TRANS_P_THRESHOLDS_0_0 寄存器结构定义。地址偏移量:0x90AC，初值:0x00000000，宽度:32
 寄存器说明: ISP_WR Transaction Probe的bin_0配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  thresholds_0_0 : 2;  /* bit[0-1] : 0x0-->选择threshold_0（delay：40；outstanding：2）；
                                                         0x1-->选择threshold_1（delay：96；outstanding：5）；
                                                         0x2-->选择threshold_2（delay：128；-----------------）；
                                                         0x3-->选择threshold_3（delay：256；-----------------）； */
        unsigned int  reserved       : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_TRANS_P_THRESHOLDS_0_0_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_TRANS_P_THRESHOLDS_0_0_thresholds_0_0_START  (0)
#define SOC_VIVO_BUS_ISP_WR_TRANS_P_THRESHOLDS_0_0_thresholds_0_0_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_TRANS_P_THRESHOLDS_0_1_UNION
 结构说明  : ISP_WR_TRANS_P_THRESHOLDS_0_1 寄存器结构定义。地址偏移量:0x90B0，初值:0x00000000，宽度:32
 寄存器说明: ISP_WR Transaction Probe的bin_0配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  thresholds_0_1 : 2;  /* bit[0-1] : 0x0-->选择threshold_0（delay：1~40；outstanding：1~2）；
                                                         0x1-->选择threshold_1（delay：41~96；outstanding：3~5）；
                                                         0x2-->选择threshold_2（delay：97~128；-----------------）；
                                                         0x3-->选择threshold_3（delay：129~256；-----------------）； */
        unsigned int  reserved       : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_TRANS_P_THRESHOLDS_0_1_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_TRANS_P_THRESHOLDS_0_1_thresholds_0_1_START  (0)
#define SOC_VIVO_BUS_ISP_WR_TRANS_P_THRESHOLDS_0_1_thresholds_0_1_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_TRANS_P_OVERFLOWSTATUS_UNION
 结构说明  : ISP_WR_TRANS_P_OVERFLOWSTATUS 寄存器结构定义。地址偏移量:0x90EC，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器溢出状态
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  overflowstatus : 1;  /* bit[0-0] : 1表示统计计数器溢出 */
        unsigned int  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_TRANS_P_OVERFLOWSTATUS_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_TRANS_P_OVERFLOWSTATUS_overflowstatus_START  (0)
#define SOC_VIVO_BUS_ISP_WR_TRANS_P_OVERFLOWSTATUS_overflowstatus_END    (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_TRANS_P_OVERFLOWRESET_UNION
 结构说明  : ISP_WR_TRANS_P_OVERFLOWRESET 寄存器结构定义。地址偏移量:0x90F0，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器溢出状态清零
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  overflowreset : 1;  /* bit[0-0] : 写1时，OverflowStatus寄存器清零，读该寄存器时钟返回0 */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_TRANS_P_OVERFLOWRESET_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_TRANS_P_OVERFLOWRESET_overflowreset_START  (0)
#define SOC_VIVO_BUS_ISP_WR_TRANS_P_OVERFLOWRESET_overflowreset_END    (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_TRANS_P_PENDINGEVENTMODE_UNION
 结构说明  : ISP_WR_TRANS_P_PENDINGEVENTMODE 寄存器结构定义。地址偏移量:0x90F4，初值:0x00000000，宽度:32
 寄存器说明: outstanding统计技术工作模式配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pendingeventmode : 1;  /* bit[0-0] : 0x0-->当outstanding数量 > 0时，每个cycle都去触发计数器收集outstanding个数；
                                                           0x1-->当返回1个response时，就触发计数器收集outstanding个数。 */
        unsigned int  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_TRANS_P_PENDINGEVENTMODE_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_TRANS_P_PENDINGEVENTMODE_pendingeventmode_START  (0)
#define SOC_VIVO_BUS_ISP_WR_TRANS_P_PENDINGEVENTMODE_pendingeventmode_END    (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_TRANS_P_PRESCALER_UNION
 结构说明  : ISP_WR_TRANS_P_PRESCALER 寄存器结构定义。地址偏移量:0x90F8，初值:0x00000000，宽度:32
 寄存器说明: latency统计系数配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  prescaler : 8;  /* bit[0-7] : 0-->handshake的模式，start event=begin request，end event=accept request；
                                                    1-->latency模式，start event=begin request + context ID，end event=begin response + context ID。 */
        unsigned int  reserved  : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_TRANS_P_PRESCALER_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_TRANS_P_PRESCALER_prescaler_START  (0)
#define SOC_VIVO_BUS_ISP_WR_TRANS_P_PRESCALER_prescaler_END    (7)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_TRANS_M_ID_COREID_UNION
 结构说明  : ISP_WR_TRANS_M_ID_COREID 寄存器结构定义。地址偏移量:0x9400，初值:0x4BEB6806，宽度:32
 寄存器说明: ISP_WR Transaction probe域ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_coreid : 32; /* bit[0-31]: VcodecBus的Packet Probe的域ID。 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_TRANS_M_ID_COREID_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_ID_COREID_id_coreid_START  (0)
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_ID_COREID_id_coreid_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_TRANS_M_ID_REVISIONID_UNION
 结构说明  : ISP_WR_TRANS_M_ID_REVISIONID 寄存器结构定义。地址偏移量:0x9404，初值:0x012D5300，宽度:32
 寄存器说明: 总线代码版本寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_revisionid : 32; /* bit[0-31]: 低8bit自定义，高24bit是NOC的配置HUSH值。 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_TRANS_M_ID_REVISIONID_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_ID_REVISIONID_id_revisionid_START  (0)
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_ID_REVISIONID_id_revisionid_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_TRANS_M_MAINCTL_UNION
 结构说明  : ISP_WR_TRANS_M_MAINCTL 寄存器结构定义。地址偏移量:0x9408，初值:0x00000000，宽度:32
 寄存器说明: Transaction Probe全局控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  erren                     : 1;  /* bit[0]   : ErrEn：使能Packet Probe将检测到的任何错误状态的Packet上报给Observer。由于本总线的Packet Probe不支持trace功能，故此位无意义。 */
        unsigned int  traceen                   : 1;  /* bit[1]   : TraceEn：该总线不支持Trace功能，故此位无意义。 */
        unsigned int  payloaden                 : 1;  /* bit[2]   : PayloadEn：该总线不支持Trace功能，故此位无意义。 */
        unsigned int  staten                    : 1;  /* bit[3]   : StatEn：统计模型使能寄存器，当StatEn由0配置为1时，统计计数器被清零；当StatEn配置为0时，统计计数器被disabled。 */
        unsigned int  alarmen                   : 1;  /* bit[4]   : AlarmEn：中断使能配置。
                                                                    0-->屏蔽中断；
                                                                    1-->使能中断输出。 */
        unsigned int  statconddump              : 1;  /* bit[5]   : 0-->表示无条件dump统计数据，寄存器counters_m_val的值，实时反映统计计数器的值；
                                                                    1-->表示有条件dump数据，在给定的统计周期内发生out of bounds 事件，才会将统计计数器的值dump至寄存器counters_m_val中。 */
        unsigned int  intrusivemode             : 1;  /* bit[6]   : IntrusiveMode： 该总线不支持Trace功能，故此位无意义。 */
        unsigned int  filtbytealwayschainableen : 1;  /* bit[7]   : FiltByteAlwaysChainableEn：奇数和偶数计数器串行使能的全局配置：
                                                                    0-->不使能，此时，所有侧statistic counters都可以被Map；
                                                                    1-->使能，只有偶数statistic counters才可以被Map。 */
        unsigned int  reserved                  : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_TRANS_M_MAINCTL_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_MAINCTL_erren_START                      (0)
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_MAINCTL_erren_END                        (0)
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_MAINCTL_traceen_START                    (1)
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_MAINCTL_traceen_END                      (1)
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_MAINCTL_payloaden_START                  (2)
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_MAINCTL_payloaden_END                    (2)
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_MAINCTL_staten_START                     (3)
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_MAINCTL_staten_END                       (3)
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_MAINCTL_alarmen_START                    (4)
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_MAINCTL_alarmen_END                      (4)
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_MAINCTL_statconddump_START               (5)
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_MAINCTL_statconddump_END                 (5)
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_MAINCTL_intrusivemode_START              (6)
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_MAINCTL_intrusivemode_END                (6)
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_MAINCTL_filtbytealwayschainableen_START  (7)
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_MAINCTL_filtbytealwayschainableen_END    (7)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_TRANS_M_CFGCTL_UNION
 结构说明  : ISP_WR_TRANS_M_CFGCTL 寄存器结构定义。地址偏移量:0x940C，初值:0x00000000，宽度:32
 寄存器说明: Packet Probe使能寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  globalen : 1;  /* bit[0]   : GlobalEn：Packet Probe使能信号，高有效。 */
        unsigned int  active   : 1;  /* bit[1]   : Active：Packet Probe的工作状态指示信号。
                                                   0-->当GlobalEn配置为0的几个cycle后，Active被拉低；
                                                   1-->当GlobalEn配置为1时，Active被拉高，此时不允许对Packet Probe进行配置。 */
        unsigned int  reserved : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_TRANS_M_CFGCTL_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_CFGCTL_globalen_START  (0)
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_CFGCTL_globalen_END    (0)
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_CFGCTL_active_START    (1)
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_CFGCTL_active_END      (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_TRANS_M_STATPERIOD_UNION
 结构说明  : ISP_WR_TRANS_M_STATPERIOD 寄存器结构定义。地址偏移量:0x9424，初值:0x00000000，宽度:32
 寄存器说明: 统计周期配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statperiod : 5;  /* bit[0-4] : 自动统计模式下的统计周期，统计周期= N_Cycle = 2^min(23,StatPeriod)，最大为8 mega cycles，最小为2 cycles。当配置为0时，自动统计模式被关闭，需要采用手动模式，也就是配置StatGo寄存器来实现带宽统计。 */
        unsigned int  reserved   : 27; /* bit[5-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_TRANS_M_STATPERIOD_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_STATPERIOD_statperiod_START  (0)
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_STATPERIOD_statperiod_END    (4)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_TRANS_M_STATGO_UNION
 结构说明  : ISP_WR_TRANS_M_STATGO 寄存器结构定义。地址偏移量:0x9428，初值:0x00000000，宽度:32
 寄存器说明: 手动带宽统计计时开始使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statgo   : 1;  /* bit[0]   : 当StatPeriod=0时，当globalen为1，向寄存器StatGo写1，则会将counter_m_val的值与statalarmmax或statalarmmin的值进行比较；读该寄存器始终返回0。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_TRANS_M_STATGO_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_STATGO_statgo_START    (0)
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_STATGO_statgo_END      (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_TRANS_M_STATALARMMIN_UNION
 结构说明  : ISP_WR_TRANS_M_STATALARMMIN 寄存器结构定义。地址偏移量:0x942C，初值:0x00000000，宽度:32
 寄存器说明: 统计计数最小告警阈值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statalarmmin : 32; /* bit[0-31]: 当任意一个统计计数器的值小于StatAlarmMin的值，就触发告警寄存器。 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_TRANS_M_STATALARMMIN_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_STATALARMMIN_statalarmmin_START  (0)
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_STATALARMMIN_statalarmmin_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_TRANS_M_STATALARMMAX_UNION
 结构说明  : ISP_WR_TRANS_M_STATALARMMAX 寄存器结构定义。地址偏移量:0x9430，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器最大告警阈值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statalarmmax : 32; /* bit[0-31]: 当任意一个统计计数器的值大于StatAlarmMax的值，就触发告警寄存器。 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_TRANS_M_STATALARMMAX_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_STATALARMMAX_statalarmmax_START  (0)
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_STATALARMMAX_statalarmmax_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_TRANS_M_STATALARMSTATUS_UNION
 结构说明  : ISP_WR_TRANS_M_STATALARMSTATUS 寄存器结构定义。地址偏移量:0x9434，初值:0x00000000，宽度:32
 寄存器说明: 告警状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statalarmstatus : 1;  /* bit[0]   : 当任意一个统计计数器的值大于StatAlarmMax或小于StatAlarmMin，则该寄存器置位为1； */
        unsigned int  reserved        : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_TRANS_M_STATALARMSTATUS_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_STATALARMSTATUS_statalarmstatus_START  (0)
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_STATALARMSTATUS_statalarmstatus_END    (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_TRANS_M_STATALARMCLR_UNION
 结构说明  : ISP_WR_TRANS_M_STATALARMCLR 寄存器结构定义。地址偏移量:0x9438，初值:0x00000000，宽度:32
 寄存器说明: 告警状态清除寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statalarmclr : 1;  /* bit[0]   : 写1会清零StatAlarmStatus寄存器，读此寄存器返回总是0； */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_TRANS_M_STATALARMCLR_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_STATALARMCLR_statalarmclr_START  (0)
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_STATALARMCLR_statalarmclr_END    (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_0_SRC_UNION
 结构说明  : ISP_WR_TRANS_M_COUNTERS_0_SRC 寄存器结构定义。地址偏移量:0x9538，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_0_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：2~4）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：>= 5）；
                                                         0x23-->Bin 3（delay：128~255；----------------）；
                                                         0x24-->Bin 4（delay：>= 256；----------------）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_0_SRC_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_0_SRC_counters_0_src_START  (0)
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_0_SRC_counters_0_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_0_ALARMMODE_UNION
 结构说明  : ISP_WR_TRANS_M_COUNTERS_0_ALARMMODE 寄存器结构定义。地址偏移量:0x953C，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_0_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_0_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_0_ALARMMODE_counters_0_alarmmode_START  (0)
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_0_ALARMMODE_counters_0_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_0_VAL_UNION
 结构说明  : ISP_WR_TRANS_M_COUNTERS_0_VAL 寄存器结构定义。地址偏移量:0x9540，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_0_val : 11; /* bit[0-10] : 当Counters_0_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_0_VAL_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_0_VAL_counters_0_val_START  (0)
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_0_VAL_counters_0_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_1_SRC_UNION
 结构说明  : ISP_WR_TRANS_M_COUNTERS_1_SRC 寄存器结构定义。地址偏移量:0x954C，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_1_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：2~4）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：>= 5）；
                                                         0x23-->Bin 3（delay：128~255；----------------）；
                                                         0x24-->Bin 4（delay：>= 256；----------------）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_1_SRC_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_1_SRC_counters_1_src_START  (0)
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_1_SRC_counters_1_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_1_ALARMMODE_UNION
 结构说明  : ISP_WR_TRANS_M_COUNTERS_1_ALARMMODE 寄存器结构定义。地址偏移量:0x9550，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_1_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_1_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_1_ALARMMODE_counters_1_alarmmode_START  (0)
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_1_ALARMMODE_counters_1_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_1_VAL_UNION
 结构说明  : ISP_WR_TRANS_M_COUNTERS_1_VAL 寄存器结构定义。地址偏移量:0x9554，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_1_val : 11; /* bit[0-10] : 当Counters_1_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_1_VAL_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_1_VAL_counters_1_val_START  (0)
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_1_VAL_counters_1_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_2_SRC_UNION
 结构说明  : ISP_WR_TRANS_M_COUNTERS_2_SRC 寄存器结构定义。地址偏移量:0x9560，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_2_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：2~4）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：>= 5）；
                                                         0x23-->Bin 3（delay：128~255；----------------）；
                                                         0x24-->Bin 4（delay：>= 256；----------------）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_2_SRC_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_2_SRC_counters_2_src_START  (0)
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_2_SRC_counters_2_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_2_ALARMMODE_UNION
 结构说明  : ISP_WR_TRANS_M_COUNTERS_2_ALARMMODE 寄存器结构定义。地址偏移量:0x9564，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_2_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_2_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_2_ALARMMODE_counters_2_alarmmode_START  (0)
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_2_ALARMMODE_counters_2_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_2_VAL_UNION
 结构说明  : ISP_WR_TRANS_M_COUNTERS_2_VAL 寄存器结构定义。地址偏移量:0x9568，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_2_val : 11; /* bit[0-10] : 当Counters_2_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_2_VAL_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_2_VAL_counters_2_val_START  (0)
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_2_VAL_counters_2_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_3_SRC_UNION
 结构说明  : ISP_WR_TRANS_M_COUNTERS_3_SRC 寄存器结构定义。地址偏移量:0x9574，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_3_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：2~4）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：>= 5）；
                                                         0x23-->Bin 3（delay：128~255；----------------）；
                                                         0x24-->Bin 4（delay：>= 256；----------------）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_3_SRC_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_3_SRC_counters_3_src_START  (0)
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_3_SRC_counters_3_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_3_ALARMMODE_UNION
 结构说明  : ISP_WR_TRANS_M_COUNTERS_3_ALARMMODE 寄存器结构定义。地址偏移量:0x9578，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_3_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_3_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_3_ALARMMODE_counters_3_alarmmode_START  (0)
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_3_ALARMMODE_counters_3_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_3_VAL_UNION
 结构说明  : ISP_WR_TRANS_M_COUNTERS_3_VAL 寄存器结构定义。地址偏移量:0x957C，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_3_val : 11; /* bit[0-10] : 当Counters_3_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_3_VAL_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_3_VAL_counters_3_val_START  (0)
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_3_VAL_counters_3_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_4_SRC_UNION
 结构说明  : ISP_WR_TRANS_M_COUNTERS_4_SRC 寄存器结构定义。地址偏移量:0x9588，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_4_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：2~4）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：>= 5）；
                                                         0x23-->Bin 3（delay：128~255；----------------）；
                                                         0x24-->Bin 4（delay：>= 256；----------------）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_4_SRC_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_4_SRC_counters_4_src_START  (0)
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_4_SRC_counters_4_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_4_ALARMMODE_UNION
 结构说明  : ISP_WR_TRANS_M_COUNTERS_4_ALARMMODE 寄存器结构定义。地址偏移量:0x958C，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_4_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_4_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_4_ALARMMODE_counters_4_alarmmode_START  (0)
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_4_ALARMMODE_counters_4_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_4_VAL_UNION
 结构说明  : ISP_WR_TRANS_M_COUNTERS_4_VAL 寄存器结构定义。地址偏移量:0x9590，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_4_val : 11; /* bit[0-10] : 当Counters_4_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_4_VAL_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_4_VAL_counters_4_val_START  (0)
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_4_VAL_counters_4_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_5_SRC_UNION
 结构说明  : ISP_WR_TRANS_M_COUNTERS_5_SRC 寄存器结构定义。地址偏移量:0x959C，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_5_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：2~4）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：>= 5）；
                                                         0x23-->Bin 3（delay：128~255；----------------）；
                                                         0x24-->Bin 4（delay：>= 256；----------------）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_5_SRC_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_5_SRC_counters_5_src_START  (0)
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_5_SRC_counters_5_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_5_ALARMMODE_UNION
 结构说明  : ISP_WR_TRANS_M_COUNTERS_5_ALARMMODE 寄存器结构定义。地址偏移量:0x95A0，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_5_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_5_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_5_ALARMMODE_counters_5_alarmmode_START  (0)
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_5_ALARMMODE_counters_5_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_5_VAL_UNION
 结构说明  : ISP_WR_TRANS_M_COUNTERS_5_VAL 寄存器结构定义。地址偏移量:0x95A4，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_5_val : 11; /* bit[0-10] : 当Counters_5_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_5_VAL_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_5_VAL_counters_5_val_START  (0)
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_5_VAL_counters_5_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_6_SRC_UNION
 结构说明  : ISP_WR_TRANS_M_COUNTERS_6_SRC 寄存器结构定义。地址偏移量:0x95B0，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_6_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：2~4）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：>= 5）；
                                                         0x23-->Bin 3（delay：128~255；----------------）；
                                                         0x24-->Bin 4（delay：>= 256；----------------）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_6_SRC_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_6_SRC_counters_6_src_START  (0)
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_6_SRC_counters_6_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_6_ALARMMODE_UNION
 结构说明  : ISP_WR_TRANS_M_COUNTERS_6_ALARMMODE 寄存器结构定义。地址偏移量:0x95B4，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_6_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_6_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_6_ALARMMODE_counters_6_alarmmode_START  (0)
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_6_ALARMMODE_counters_6_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_6_VAL_UNION
 结构说明  : ISP_WR_TRANS_M_COUNTERS_6_VAL 寄存器结构定义。地址偏移量:0x95B8，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_6_val : 11; /* bit[0-10] : 当Counters_6_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_6_VAL_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_6_VAL_counters_6_val_START  (0)
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_6_VAL_counters_6_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_7_SRC_UNION
 结构说明  : ISP_WR_TRANS_M_COUNTERS_7_SRC 寄存器结构定义。地址偏移量:0x95C4，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_7_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：2~4）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：>= 5）；
                                                         0x23-->Bin 3（delay：128~255；----------------）；
                                                         0x24-->Bin 4（delay：>= 256；----------------）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_7_SRC_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_7_SRC_counters_7_src_START  (0)
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_7_SRC_counters_7_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_7_ALARMMODE_UNION
 结构说明  : ISP_WR_TRANS_M_COUNTERS_7_ALARMMODE 寄存器结构定义。地址偏移量:0x95C8，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_7_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_7_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_7_ALARMMODE_counters_7_alarmmode_START  (0)
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_7_ALARMMODE_counters_7_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_7_VAL_UNION
 结构说明  : ISP_WR_TRANS_M_COUNTERS_7_VAL 寄存器结构定义。地址偏移量:0x95CC，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_7_val : 11; /* bit[0-10] : 当Counters_7_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_7_VAL_UNION;
#endif
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_7_VAL_counters_7_val_START  (0)
#define SOC_VIVO_BUS_ISP_WR_TRANS_M_COUNTERS_7_VAL_counters_7_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_ID_COREID_UNION
 结构说明  : A7TOVIVOBUS_RD_TRANS_F_ID_COREID 寄存器结构定义。地址偏移量:0xA000，初值:0x689BAF09，宽度:32
 寄存器说明: A7TOVIVOBUS_RD TransactionStatFilter域ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coretypeid   : 8;  /* bit[0-7] : 类型ID */
        unsigned int  corechecksum : 24; /* bit[8-31]: 配置参数的校验和 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_ID_COREID_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_ID_COREID_coretypeid_START    (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_ID_COREID_coretypeid_END      (7)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_ID_COREID_corechecksum_START  (8)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_ID_REVISIONID_UNION
 结构说明  : A7TOVIVOBUS_RD_TRANS_F_ID_REVISIONID 寄存器结构定义。地址偏移量:0xA004，初值:0x012D5300，宽度:32
 寄存器说明: 代码版本
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  userid    : 8;  /* bit[0-7] : 用户自定义ID */
        unsigned int  flexnocid : 24; /* bit[8-31]: FlexNoC生成代码的软件版本 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_ID_REVISIONID_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_ID_REVISIONID_userid_START     (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_ID_REVISIONID_userid_END       (7)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_ID_REVISIONID_flexnocid_START  (8)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_MODE_UNION
 结构说明  : A7TOVIVOBUS_RD_TRANS_F_MODE 寄存器结构定义。地址偏移量:0xA008，初值:0x00000000，宽度:32
 寄存器说明: A7TOVIVOBUS_RD Transaction Probe的Filter工作模式配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode     : 1;  /* bit[0-0] : 0-->handshake的模式，start event=begin request，end event=accept request；
                                                   1-->latency模式，start event=begin request + context ID，end event=begin response + context ID。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_MODE_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_MODE_mode_START      (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_MODE_mode_END        (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_ADDRBASE_LOW_UNION
 结构说明  : A7TOVIVOBUS_RD_TRANS_F_ADDRBASE_LOW 寄存器结构定义。地址偏移量:0xA00C，初值:0x00000000，宽度:32
 寄存器说明: 地址过滤基地址
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addrbase_low : 32; /* bit[0-31]: 地址过滤条件的基地址。 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_ADDRBASE_LOW_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_ADDRBASE_LOW_addrbase_low_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_ADDRBASE_LOW_addrbase_low_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_ADDRBASE_HIGH_UNION
 结构说明  : A7TOVIVOBUS_RD_TRANS_F_ADDRBASE_HIGH 寄存器结构定义。地址偏移量:0xA010，初值:0x00000000，宽度:32
 寄存器说明: 地址过滤基地址
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addrbase_high : 2;  /* bit[0-1] : 地址过滤条件的基地址。 */
        unsigned int  reserved      : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_ADDRBASE_HIGH_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_ADDRBASE_HIGH_addrbase_high_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_ADDRBASE_HIGH_addrbase_high_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_ADDRWINDOWSIZE_UNION
 结构说明  : A7TOVIVOBUS_RD_TRANS_F_ADDRWINDOWSIZE 寄存器结构定义。地址偏移量:0xA014，初值:0x00000000，宽度:32
 寄存器说明: 地址过滤窗口
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addrwindowsize : 6;  /* bit[0-5] : 地址过滤的Mask窗口大小。
                                                         例如：地址过滤的Mask窗口大小为64MB，WidowSize=log2(64MB)=26，此时，就配置filter_0_windowsize=0x1A；
                                                         Address Mask=~（2^max(WindowSize,packet.len)-1）=0xFC000000（packet.len为NOC内部表示一个packet包长变量的位宽，其值为6~7）；
                                                         过滤条件为：PacketAddress & AddressMask = AddressBase & AddressMask。 */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_ADDRWINDOWSIZE_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_ADDRWINDOWSIZE_addrwindowsize_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_ADDRWINDOWSIZE_addrwindowsize_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_OPCODE_UNION
 结构说明  : A7TOVIVOBUS_RD_TRANS_F_OPCODE 寄存器结构定义。地址偏移量:0xA020，初值:0x00000000，宽度:32
 寄存器说明: A7TOVIVOBUS_RD的Transaction Probe的Opcode过滤条件
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rden     : 1;  /* bit[0-0] : 配置为1时，过滤写数据包； */
        unsigned int  wren     : 1;  /* bit[1-1] : 配置为1时，过滤读数据包； */
        unsigned int  reserved : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_OPCODE_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_OPCODE_rden_START      (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_OPCODE_rden_END        (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_OPCODE_wren_START      (1)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_OPCODE_wren_END        (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_USERBASE_UNION
 结构说明  : A7TOVIVOBUS_RD_TRANS_F_USERBASE 寄存器结构定义。地址偏移量:0xA024，初值:0x00000000，宽度:32
 寄存器说明: A7TOVIVOBUS_RD的Transaction Probe的User过滤条件
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  userbase : 5;  /* bit[0-4] : User信号过滤条件 */
        unsigned int  reserved : 27; /* bit[5-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_USERBASE_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_USERBASE_userbase_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_USERBASE_userbase_END    (4)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_USERMASK_UNION
 结构说明  : A7TOVIVOBUS_RD_TRANS_F_USERMASK 寄存器结构定义。地址偏移量:0xA028，初值:0x00000000，宽度:32
 寄存器说明: A7TOVIVOBUS_RD的Transaction Probe的User过滤条件Mask
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  usermask : 5;  /* bit[0-4] : 对UserBase进行Mask，选择UserBase中的任意几bit User信号作为过滤条件。
                                                   过滤条件：packet.User & UserMask = UserBase & UserMask。 */
        unsigned int  reserved : 27; /* bit[5-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_USERMASK_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_USERMASK_usermask_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_USERMASK_usermask_END    (4)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_SECURITYBASE_UNION
 结构说明  : A7TOVIVOBUS_RD_TRANS_F_SECURITYBASE 寄存器结构定义。地址偏移量:0xA02C，初值:0x00000000，宽度:32
 寄存器说明: A7TOVIVOBUS_RD的Transaction Probe的安全过滤条件
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  securitybase : 1;  /* bit[0-0] : 0-->表示安全过滤条件；
                                                       1-->表示非安全过滤条件。 */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_SECURITYBASE_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_SECURITYBASE_securitybase_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_SECURITYBASE_securitybase_END    (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_SECURITYMASK_UNION
 结构说明  : A7TOVIVOBUS_RD_TRANS_F_SECURITYMASK 寄存器结构定义。地址偏移量:0xA030，初值:0x00000000，宽度:32
 寄存器说明: A7TOVIVOBUS_RD的Transaction Probe的安全过滤条件Mask
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  securitymask : 1;  /* bit[0-0] : 安全过滤条件：packet.Security & SecurityMask = SecurityBase & SecurityMasks；
                                                       也就是说当Filters_1_SecurityMask=1时安全过滤条件Filters_1_SecurityBase有效，可以过滤安全或非安全packet；否则，不起过滤作用； */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_SECURITYMASK_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_SECURITYMASK_securitymask_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_F_SECURITYMASK_securitymask_END    (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_ID_COREID_UNION
 结构说明  : A7TOVIVOBUS_RD_TRANS_P_ID_COREID 寄存器结构定义。地址偏移量:0xA080，初值:0xAEFFDB0A，宽度:32
 寄存器说明: A7TOVIVOBUS_RD TransactionStatProfilter域ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coretypeid   : 8;  /* bit[0-7] : 类型ID */
        unsigned int  corechecksum : 24; /* bit[8-31]: 配置参数的校验和 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_ID_COREID_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_ID_COREID_coretypeid_START    (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_ID_COREID_coretypeid_END      (7)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_ID_COREID_corechecksum_START  (8)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_ID_REVISIONID_UNION
 结构说明  : A7TOVIVOBUS_RD_TRANS_P_ID_REVISIONID 寄存器结构定义。地址偏移量:0xA084，初值:0x012D5300，宽度:32
 寄存器说明: 代码版本
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  userid    : 8;  /* bit[0-7] : 用户自定义ID */
        unsigned int  flexnocid : 24; /* bit[8-31]: FlexNoC生成代码的软件版本 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_ID_REVISIONID_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_ID_REVISIONID_userid_START     (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_ID_REVISIONID_userid_END       (7)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_ID_REVISIONID_flexnocid_START  (8)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_EN_UNION
 结构说明  : A7TOVIVOBUS_RD_TRANS_P_EN 寄存器结构定义。地址偏移量:0xA088，初值:0x00000000，宽度:32
 寄存器说明: transaction Probe的counter使能配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  en       : 1;  /* bit[0-0] : 当配置为1时，使能Transaction Probe的统计计数器 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_EN_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_EN_en_START        (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_EN_en_END          (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_MODE_UNION
 结构说明  : A7TOVIVOBUS_RD_TRANS_P_MODE 寄存器结构定义。地址偏移量:0xA08C，初值:0x00000000，宽度:32
 寄存器说明: A7TOVIVOBUS_RD Transaction Probe的工作模式配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode     : 1;  /* bit[0]   : 0-->统计latency；
                                                   1-->统计outstanding； */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_MODE_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_MODE_mode_START      (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_MODE_mode_END        (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_THRESHOLDS_0_0_UNION
 结构说明  : A7TOVIVOBUS_RD_TRANS_P_THRESHOLDS_0_0 寄存器结构定义。地址偏移量:0xA0AC，初值:0x00000000，宽度:32
 寄存器说明: A7TOVIVOBUS_RD Transaction Probe的bin_0配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  thresholds_0_0 : 2;  /* bit[0-1] : 0x0-->选择threshold_0（delay：40；outstanding：2）；
                                                         0x1-->选择threshold_1（delay：96；outstanding：5）；
                                                         0x2-->选择threshold_2（delay：128；-----------------）；
                                                         0x3-->选择threshold_3（delay：256；-----------------）； */
        unsigned int  reserved       : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_THRESHOLDS_0_0_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_THRESHOLDS_0_0_thresholds_0_0_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_THRESHOLDS_0_0_thresholds_0_0_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_THRESHOLDS_0_1_UNION
 结构说明  : A7TOVIVOBUS_RD_TRANS_P_THRESHOLDS_0_1 寄存器结构定义。地址偏移量:0xA0B0，初值:0x00000000，宽度:32
 寄存器说明: A7TOVIVOBUS_RD Transaction Probe的bin_0配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  thresholds_0_1 : 2;  /* bit[0-1] : 0x0-->选择threshold_0（delay：1~40；outstanding：1~2）；
                                                         0x1-->选择threshold_1（delay：41~96；outstanding：3~5）；
                                                         0x2-->选择threshold_2（delay：97~128；-----------------）；
                                                         0x3-->选择threshold_3（delay：129~256；-----------------）； */
        unsigned int  reserved       : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_THRESHOLDS_0_1_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_THRESHOLDS_0_1_thresholds_0_1_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_THRESHOLDS_0_1_thresholds_0_1_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_OVERFLOWSTATUS_UNION
 结构说明  : A7TOVIVOBUS_RD_TRANS_P_OVERFLOWSTATUS 寄存器结构定义。地址偏移量:0xA0EC，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器溢出状态
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  overflowstatus : 1;  /* bit[0-0] : 1表示统计计数器溢出 */
        unsigned int  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_OVERFLOWSTATUS_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_OVERFLOWSTATUS_overflowstatus_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_OVERFLOWSTATUS_overflowstatus_END    (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_OVERFLOWRESET_UNION
 结构说明  : A7TOVIVOBUS_RD_TRANS_P_OVERFLOWRESET 寄存器结构定义。地址偏移量:0xA0F0，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器溢出状态清零
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  overflowreset : 1;  /* bit[0-0] : 写1时，OverflowStatus寄存器清零，读该寄存器时钟返回0 */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_OVERFLOWRESET_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_OVERFLOWRESET_overflowreset_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_OVERFLOWRESET_overflowreset_END    (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_PENDINGEVENTMODE_UNION
 结构说明  : A7TOVIVOBUS_RD_TRANS_P_PENDINGEVENTMODE 寄存器结构定义。地址偏移量:0xA0F4，初值:0x00000000，宽度:32
 寄存器说明: outstanding统计技术工作模式配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pendingeventmode : 1;  /* bit[0-0] : 0x0-->当outstanding数量 > 0时，每个cycle都去触发计数器收集outstanding个数；
                                                           0x1-->当返回1个response时，就触发计数器收集outstanding个数。 */
        unsigned int  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_PENDINGEVENTMODE_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_PENDINGEVENTMODE_pendingeventmode_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_PENDINGEVENTMODE_pendingeventmode_END    (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_PRESCALER_UNION
 结构说明  : A7TOVIVOBUS_RD_TRANS_P_PRESCALER 寄存器结构定义。地址偏移量:0xA0F8，初值:0x00000000，宽度:32
 寄存器说明: latency统计系数配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  prescaler : 8;  /* bit[0-7] : 0-->handshake的模式，start event=begin request，end event=accept request；
                                                    1-->latency模式，start event=begin request + context ID，end event=begin response + context ID。 */
        unsigned int  reserved  : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_PRESCALER_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_PRESCALER_prescaler_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_P_PRESCALER_prescaler_END    (7)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_ID_COREID_UNION
 结构说明  : A7TOVIVOBUS_RD_TRANS_M_ID_COREID 寄存器结构定义。地址偏移量:0xA400，初值:0x1466D206，宽度:32
 寄存器说明: A7TOVIVOBUS_RD Transaction probe域ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_coreid : 32; /* bit[0-31]: VcodecBus的Packet Probe的域ID。 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_ID_COREID_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_ID_COREID_id_coreid_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_ID_COREID_id_coreid_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_ID_REVISIONID_UNION
 结构说明  : A7TOVIVOBUS_RD_TRANS_M_ID_REVISIONID 寄存器结构定义。地址偏移量:0xA404，初值:0x012D5300，宽度:32
 寄存器说明: 总线代码版本寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_revisionid : 32; /* bit[0-31]: 低8bit自定义，高24bit是NOC的配置HUSH值。 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_ID_REVISIONID_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_ID_REVISIONID_id_revisionid_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_ID_REVISIONID_id_revisionid_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_MAINCTL_UNION
 结构说明  : A7TOVIVOBUS_RD_TRANS_M_MAINCTL 寄存器结构定义。地址偏移量:0xA408，初值:0x00000000，宽度:32
 寄存器说明: Transaction Probe全局控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  erren                     : 1;  /* bit[0]   : ErrEn：使能Packet Probe将检测到的任何错误状态的Packet上报给Observer。由于本总线的Packet Probe不支持trace功能，故此位无意义。 */
        unsigned int  traceen                   : 1;  /* bit[1]   : TraceEn：该总线不支持Trace功能，故此位无意义。 */
        unsigned int  payloaden                 : 1;  /* bit[2]   : PayloadEn：该总线不支持Trace功能，故此位无意义。 */
        unsigned int  staten                    : 1;  /* bit[3]   : StatEn：统计模型使能寄存器，当StatEn由0配置为1时，统计计数器被清零；当StatEn配置为0时，统计计数器被disabled。 */
        unsigned int  alarmen                   : 1;  /* bit[4]   : AlarmEn：中断使能配置。
                                                                    0-->屏蔽中断；
                                                                    1-->使能中断输出。 */
        unsigned int  statconddump              : 1;  /* bit[5]   : 0-->表示无条件dump统计数据，寄存器counters_m_val的值，实时反映统计计数器的值；
                                                                    1-->表示有条件dump数据，在给定的统计周期内发生out of bounds 事件，才会将统计计数器的值dump至寄存器counters_m_val中。 */
        unsigned int  intrusivemode             : 1;  /* bit[6]   : IntrusiveMode： 该总线不支持Trace功能，故此位无意义。 */
        unsigned int  filtbytealwayschainableen : 1;  /* bit[7]   : FiltByteAlwaysChainableEn：奇数和偶数计数器串行使能的全局配置：
                                                                    0-->不使能，此时，所有侧statistic counters都可以被Map；
                                                                    1-->使能，只有偶数statistic counters才可以被Map。 */
        unsigned int  reserved                  : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_MAINCTL_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_MAINCTL_erren_START                      (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_MAINCTL_erren_END                        (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_MAINCTL_traceen_START                    (1)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_MAINCTL_traceen_END                      (1)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_MAINCTL_payloaden_START                  (2)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_MAINCTL_payloaden_END                    (2)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_MAINCTL_staten_START                     (3)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_MAINCTL_staten_END                       (3)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_MAINCTL_alarmen_START                    (4)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_MAINCTL_alarmen_END                      (4)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_MAINCTL_statconddump_START               (5)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_MAINCTL_statconddump_END                 (5)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_MAINCTL_intrusivemode_START              (6)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_MAINCTL_intrusivemode_END                (6)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_MAINCTL_filtbytealwayschainableen_START  (7)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_MAINCTL_filtbytealwayschainableen_END    (7)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_CFGCTL_UNION
 结构说明  : A7TOVIVOBUS_RD_TRANS_M_CFGCTL 寄存器结构定义。地址偏移量:0xA40C，初值:0x00000000，宽度:32
 寄存器说明: Packet Probe使能寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  globalen : 1;  /* bit[0]   : GlobalEn：Packet Probe使能信号，高有效。 */
        unsigned int  active   : 1;  /* bit[1]   : Active：Packet Probe的工作状态指示信号。
                                                   0-->当GlobalEn配置为0的几个cycle后，Active被拉低；
                                                   1-->当GlobalEn配置为1时，Active被拉高，此时不允许对Packet Probe进行配置。 */
        unsigned int  reserved : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_CFGCTL_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_CFGCTL_globalen_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_CFGCTL_globalen_END    (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_CFGCTL_active_START    (1)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_CFGCTL_active_END      (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_STATPERIOD_UNION
 结构说明  : A7TOVIVOBUS_RD_TRANS_M_STATPERIOD 寄存器结构定义。地址偏移量:0xA424，初值:0x00000000，宽度:32
 寄存器说明: 统计周期配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statperiod : 5;  /* bit[0-4] : 自动统计模式下的统计周期，统计周期= N_Cycle = 2^min(23,StatPeriod)，最大为8 mega cycles，最小为2 cycles。当配置为0时，自动统计模式被关闭，需要采用手动模式，也就是配置StatGo寄存器来实现带宽统计。 */
        unsigned int  reserved   : 27; /* bit[5-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_STATPERIOD_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_STATPERIOD_statperiod_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_STATPERIOD_statperiod_END    (4)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_STATGO_UNION
 结构说明  : A7TOVIVOBUS_RD_TRANS_M_STATGO 寄存器结构定义。地址偏移量:0xA428，初值:0x00000000，宽度:32
 寄存器说明: 手动带宽统计计时开始使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statgo   : 1;  /* bit[0]   : 当StatPeriod=0时，当globalen为1，向寄存器StatGo写1，则会将counter_m_val的值与statalarmmax或statalarmmin的值进行比较；读该寄存器始终返回0。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_STATGO_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_STATGO_statgo_START    (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_STATGO_statgo_END      (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_STATALARMMIN_UNION
 结构说明  : A7TOVIVOBUS_RD_TRANS_M_STATALARMMIN 寄存器结构定义。地址偏移量:0xA42C，初值:0x00000000，宽度:32
 寄存器说明: 统计计数最小告警阈值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statalarmmin : 32; /* bit[0-31]: 当任意一个统计计数器的值小于StatAlarmMin的值，就触发告警寄存器。 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_STATALARMMIN_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_STATALARMMIN_statalarmmin_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_STATALARMMIN_statalarmmin_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_STATALARMMAX_UNION
 结构说明  : A7TOVIVOBUS_RD_TRANS_M_STATALARMMAX 寄存器结构定义。地址偏移量:0xA430，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器最大告警阈值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statalarmmax : 32; /* bit[0-31]: 当任意一个统计计数器的值大于StatAlarmMax的值，就触发告警寄存器。 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_STATALARMMAX_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_STATALARMMAX_statalarmmax_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_STATALARMMAX_statalarmmax_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_STATALARMSTATUS_UNION
 结构说明  : A7TOVIVOBUS_RD_TRANS_M_STATALARMSTATUS 寄存器结构定义。地址偏移量:0xA434，初值:0x00000000，宽度:32
 寄存器说明: 告警状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statalarmstatus : 1;  /* bit[0]   : 当任意一个统计计数器的值大于StatAlarmMax或小于StatAlarmMin，则该寄存器置位为1； */
        unsigned int  reserved        : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_STATALARMSTATUS_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_STATALARMSTATUS_statalarmstatus_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_STATALARMSTATUS_statalarmstatus_END    (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_STATALARMCLR_UNION
 结构说明  : A7TOVIVOBUS_RD_TRANS_M_STATALARMCLR 寄存器结构定义。地址偏移量:0xA438，初值:0x00000000，宽度:32
 寄存器说明: 告警状态清除寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statalarmclr : 1;  /* bit[0]   : 写1会清零StatAlarmStatus寄存器，读此寄存器返回总是0； */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_STATALARMCLR_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_STATALARMCLR_statalarmclr_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_STATALARMCLR_statalarmclr_END    (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_0_SRC_UNION
 结构说明  : A7TOVIVOBUS_RD_TRANS_M_COUNTERS_0_SRC 寄存器结构定义。地址偏移量:0xA538，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_0_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：2~4）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：>= 5）；
                                                         0x23-->Bin 3（delay：128~255；----------------）；
                                                         0x24-->Bin 4（delay：>= 256；----------------）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_0_SRC_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_0_SRC_counters_0_src_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_0_SRC_counters_0_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_0_ALARMMODE_UNION
 结构说明  : A7TOVIVOBUS_RD_TRANS_M_COUNTERS_0_ALARMMODE 寄存器结构定义。地址偏移量:0xA53C，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_0_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_0_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_0_ALARMMODE_counters_0_alarmmode_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_0_ALARMMODE_counters_0_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_0_VAL_UNION
 结构说明  : A7TOVIVOBUS_RD_TRANS_M_COUNTERS_0_VAL 寄存器结构定义。地址偏移量:0xA540，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_0_val : 11; /* bit[0-10] : 当Counters_0_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_0_VAL_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_0_VAL_counters_0_val_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_0_VAL_counters_0_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_1_SRC_UNION
 结构说明  : A7TOVIVOBUS_RD_TRANS_M_COUNTERS_1_SRC 寄存器结构定义。地址偏移量:0xA54C，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_1_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：2~4）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：>= 5）；
                                                         0x23-->Bin 3（delay：128~255；----------------）；
                                                         0x24-->Bin 4（delay：>= 256；----------------）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_1_SRC_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_1_SRC_counters_1_src_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_1_SRC_counters_1_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_1_ALARMMODE_UNION
 结构说明  : A7TOVIVOBUS_RD_TRANS_M_COUNTERS_1_ALARMMODE 寄存器结构定义。地址偏移量:0xA550，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_1_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_1_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_1_ALARMMODE_counters_1_alarmmode_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_1_ALARMMODE_counters_1_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_1_VAL_UNION
 结构说明  : A7TOVIVOBUS_RD_TRANS_M_COUNTERS_1_VAL 寄存器结构定义。地址偏移量:0xA554，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_1_val : 11; /* bit[0-10] : 当Counters_1_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_1_VAL_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_1_VAL_counters_1_val_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_1_VAL_counters_1_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_2_SRC_UNION
 结构说明  : A7TOVIVOBUS_RD_TRANS_M_COUNTERS_2_SRC 寄存器结构定义。地址偏移量:0xA560，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_2_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：2~4）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：>= 5）；
                                                         0x23-->Bin 3（delay：128~255；----------------）；
                                                         0x24-->Bin 4（delay：>= 256；----------------）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_2_SRC_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_2_SRC_counters_2_src_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_2_SRC_counters_2_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_2_ALARMMODE_UNION
 结构说明  : A7TOVIVOBUS_RD_TRANS_M_COUNTERS_2_ALARMMODE 寄存器结构定义。地址偏移量:0xA564，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_2_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_2_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_2_ALARMMODE_counters_2_alarmmode_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_2_ALARMMODE_counters_2_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_2_VAL_UNION
 结构说明  : A7TOVIVOBUS_RD_TRANS_M_COUNTERS_2_VAL 寄存器结构定义。地址偏移量:0xA568，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_2_val : 11; /* bit[0-10] : 当Counters_2_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_2_VAL_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_2_VAL_counters_2_val_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_2_VAL_counters_2_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_3_SRC_UNION
 结构说明  : A7TOVIVOBUS_RD_TRANS_M_COUNTERS_3_SRC 寄存器结构定义。地址偏移量:0xA574，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_3_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：2~4）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：>= 5）；
                                                         0x23-->Bin 3（delay：128~255；----------------）；
                                                         0x24-->Bin 4（delay：>= 256；----------------）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_3_SRC_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_3_SRC_counters_3_src_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_3_SRC_counters_3_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_3_ALARMMODE_UNION
 结构说明  : A7TOVIVOBUS_RD_TRANS_M_COUNTERS_3_ALARMMODE 寄存器结构定义。地址偏移量:0xA578，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_3_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_3_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_3_ALARMMODE_counters_3_alarmmode_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_3_ALARMMODE_counters_3_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_3_VAL_UNION
 结构说明  : A7TOVIVOBUS_RD_TRANS_M_COUNTERS_3_VAL 寄存器结构定义。地址偏移量:0xA57C，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_3_val : 11; /* bit[0-10] : 当Counters_3_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_3_VAL_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_3_VAL_counters_3_val_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_3_VAL_counters_3_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_4_SRC_UNION
 结构说明  : A7TOVIVOBUS_RD_TRANS_M_COUNTERS_4_SRC 寄存器结构定义。地址偏移量:0xA588，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_4_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：2~4）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：>= 5）；
                                                         0x23-->Bin 3（delay：128~255；----------------）；
                                                         0x24-->Bin 4（delay：>= 256；----------------）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_4_SRC_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_4_SRC_counters_4_src_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_4_SRC_counters_4_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_4_ALARMMODE_UNION
 结构说明  : A7TOVIVOBUS_RD_TRANS_M_COUNTERS_4_ALARMMODE 寄存器结构定义。地址偏移量:0xA58C，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_4_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_4_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_4_ALARMMODE_counters_4_alarmmode_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_4_ALARMMODE_counters_4_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_4_VAL_UNION
 结构说明  : A7TOVIVOBUS_RD_TRANS_M_COUNTERS_4_VAL 寄存器结构定义。地址偏移量:0xA590，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_4_val : 11; /* bit[0-10] : 当Counters_4_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_4_VAL_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_4_VAL_counters_4_val_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_4_VAL_counters_4_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_5_SRC_UNION
 结构说明  : A7TOVIVOBUS_RD_TRANS_M_COUNTERS_5_SRC 寄存器结构定义。地址偏移量:0xA59C，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_5_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：2~4）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：>= 5）；
                                                         0x23-->Bin 3（delay：128~255；----------------）；
                                                         0x24-->Bin 4（delay：>= 256；----------------）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_5_SRC_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_5_SRC_counters_5_src_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_5_SRC_counters_5_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_5_ALARMMODE_UNION
 结构说明  : A7TOVIVOBUS_RD_TRANS_M_COUNTERS_5_ALARMMODE 寄存器结构定义。地址偏移量:0xA5A0，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_5_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_5_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_5_ALARMMODE_counters_5_alarmmode_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_5_ALARMMODE_counters_5_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_5_VAL_UNION
 结构说明  : A7TOVIVOBUS_RD_TRANS_M_COUNTERS_5_VAL 寄存器结构定义。地址偏移量:0xA5A4，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_5_val : 11; /* bit[0-10] : 当Counters_5_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_5_VAL_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_5_VAL_counters_5_val_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_5_VAL_counters_5_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_6_SRC_UNION
 结构说明  : A7TOVIVOBUS_RD_TRANS_M_COUNTERS_6_SRC 寄存器结构定义。地址偏移量:0xA5B0，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_6_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：2~4）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：>= 5）；
                                                         0x23-->Bin 3（delay：128~255；----------------）；
                                                         0x24-->Bin 4（delay：>= 256；----------------）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_6_SRC_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_6_SRC_counters_6_src_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_6_SRC_counters_6_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_6_ALARMMODE_UNION
 结构说明  : A7TOVIVOBUS_RD_TRANS_M_COUNTERS_6_ALARMMODE 寄存器结构定义。地址偏移量:0xA5B4，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_6_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_6_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_6_ALARMMODE_counters_6_alarmmode_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_6_ALARMMODE_counters_6_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_6_VAL_UNION
 结构说明  : A7TOVIVOBUS_RD_TRANS_M_COUNTERS_6_VAL 寄存器结构定义。地址偏移量:0xA5B8，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_6_val : 11; /* bit[0-10] : 当Counters_6_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_6_VAL_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_6_VAL_counters_6_val_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_6_VAL_counters_6_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_7_SRC_UNION
 结构说明  : A7TOVIVOBUS_RD_TRANS_M_COUNTERS_7_SRC 寄存器结构定义。地址偏移量:0xA5C4，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_7_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：2~4）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：>= 5）；
                                                         0x23-->Bin 3（delay：128~255；----------------）；
                                                         0x24-->Bin 4（delay：>= 256；----------------）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_7_SRC_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_7_SRC_counters_7_src_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_7_SRC_counters_7_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_7_ALARMMODE_UNION
 结构说明  : A7TOVIVOBUS_RD_TRANS_M_COUNTERS_7_ALARMMODE 寄存器结构定义。地址偏移量:0xA5C8，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_7_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_7_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_7_ALARMMODE_counters_7_alarmmode_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_7_ALARMMODE_counters_7_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_7_VAL_UNION
 结构说明  : A7TOVIVOBUS_RD_TRANS_M_COUNTERS_7_VAL 寄存器结构定义。地址偏移量:0xA5CC，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_7_val : 11; /* bit[0-10] : 当Counters_7_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_7_VAL_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_7_VAL_counters_7_val_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_RD_TRANS_M_COUNTERS_7_VAL_counters_7_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_ID_COREID_UNION
 结构说明  : A7TOVIVOBUS_WR_TRANS_F_ID_COREID 寄存器结构定义。地址偏移量:0xB000，初值:0x82A83109，宽度:32
 寄存器说明: ISP_WR TransactionStatFilter域ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coretypeid   : 8;  /* bit[0-7] : 类型ID */
        unsigned int  corechecksum : 24; /* bit[8-31]: 配置参数的校验和 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_ID_COREID_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_ID_COREID_coretypeid_START    (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_ID_COREID_coretypeid_END      (7)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_ID_COREID_corechecksum_START  (8)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_ID_REVISIONID_UNION
 结构说明  : A7TOVIVOBUS_WR_TRANS_F_ID_REVISIONID 寄存器结构定义。地址偏移量:0xB004，初值:0x012D5300，宽度:32
 寄存器说明: 代码版本
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  userid    : 8;  /* bit[0-7] : 用户自定义ID */
        unsigned int  flexnocid : 24; /* bit[8-31]: FlexNoC生成代码的软件版本 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_ID_REVISIONID_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_ID_REVISIONID_userid_START     (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_ID_REVISIONID_userid_END       (7)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_ID_REVISIONID_flexnocid_START  (8)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_MODE_UNION
 结构说明  : A7TOVIVOBUS_WR_TRANS_F_MODE 寄存器结构定义。地址偏移量:0xB008，初值:0x00000000，宽度:32
 寄存器说明: ISP_WR Transaction Probe的Filter工作模式配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode     : 1;  /* bit[0-0] : 0-->handshake的模式，start event=begin request，end event=accept request；
                                                   1-->latency模式，start event=begin request + context ID，end event=begin response + context ID。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_MODE_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_MODE_mode_START      (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_MODE_mode_END        (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_ADDRBASE_LOW_UNION
 结构说明  : A7TOVIVOBUS_WR_TRANS_F_ADDRBASE_LOW 寄存器结构定义。地址偏移量:0xB00C，初值:0x00000000，宽度:32
 寄存器说明: 地址过滤基地址
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addrbase_low : 32; /* bit[0-31]: 地址过滤条件的基地址。 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_ADDRBASE_LOW_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_ADDRBASE_LOW_addrbase_low_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_ADDRBASE_LOW_addrbase_low_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_ADDRBASE_HIGH_UNION
 结构说明  : A7TOVIVOBUS_WR_TRANS_F_ADDRBASE_HIGH 寄存器结构定义。地址偏移量:0xB010，初值:0x00000000，宽度:32
 寄存器说明: 地址过滤基地址
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addrbase_high : 2;  /* bit[0-1] : 地址过滤条件的基地址。 */
        unsigned int  reserved      : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_ADDRBASE_HIGH_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_ADDRBASE_HIGH_addrbase_high_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_ADDRBASE_HIGH_addrbase_high_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_ADDRWINDOWSIZE_UNION
 结构说明  : A7TOVIVOBUS_WR_TRANS_F_ADDRWINDOWSIZE 寄存器结构定义。地址偏移量:0xB014，初值:0x00000000，宽度:32
 寄存器说明: 地址过滤窗口
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addrwindowsize : 6;  /* bit[0-5] : 地址过滤的Mask窗口大小。
                                                         例如：地址过滤的Mask窗口大小为64MB，WidowSize=log2(64MB)=26，此时，就配置filter_0_windowsize=0x1A；
                                                         Address Mask=~（2^max(WindowSize,packet.len)-1）=0xFC000000（packet.len为NOC内部表示一个packet包长变量的位宽，其值为6~7）；
                                                         过滤条件为：PacketAddress & AddressMask = AddressBase & AddressMask。 */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_ADDRWINDOWSIZE_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_ADDRWINDOWSIZE_addrwindowsize_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_ADDRWINDOWSIZE_addrwindowsize_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_OPCODE_UNION
 结构说明  : A7TOVIVOBUS_WR_TRANS_F_OPCODE 寄存器结构定义。地址偏移量:0xB020，初值:0x00000000，宽度:32
 寄存器说明: ISP_WR的Transaction Probe的Opcode过滤条件
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rden     : 1;  /* bit[0-0] : 配置为1时，过滤写数据包； */
        unsigned int  wren     : 1;  /* bit[1-1] : 配置为1时，过滤读数据包； */
        unsigned int  reserved : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_OPCODE_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_OPCODE_rden_START      (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_OPCODE_rden_END        (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_OPCODE_wren_START      (1)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_OPCODE_wren_END        (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_USERBASE_UNION
 结构说明  : A7TOVIVOBUS_WR_TRANS_F_USERBASE 寄存器结构定义。地址偏移量:0xB024，初值:0x00000000，宽度:32
 寄存器说明: ISP_WR的Transaction Probe的User过滤条件
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  userbase : 5;  /* bit[0-4] : User信号过滤条件 */
        unsigned int  reserved : 27; /* bit[5-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_USERBASE_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_USERBASE_userbase_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_USERBASE_userbase_END    (4)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_USERMASK_UNION
 结构说明  : A7TOVIVOBUS_WR_TRANS_F_USERMASK 寄存器结构定义。地址偏移量:0xB028，初值:0x00000000，宽度:32
 寄存器说明: ISP_WR的Transaction Probe的User过滤条件Mask
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  usermask : 5;  /* bit[0-4] : 对UserBase进行Mask，选择UserBase中的任意几bit User信号作为过滤条件。
                                                   过滤条件：packet.User & UserMask = UserBase & UserMask。 */
        unsigned int  reserved : 27; /* bit[5-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_USERMASK_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_USERMASK_usermask_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_USERMASK_usermask_END    (4)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_SECURITYBASE_UNION
 结构说明  : A7TOVIVOBUS_WR_TRANS_F_SECURITYBASE 寄存器结构定义。地址偏移量:0xB02C，初值:0x00000000，宽度:32
 寄存器说明: ISP_WR的Transaction Probe的安全过滤条件
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  securitybase : 1;  /* bit[0-0] : 0-->表示安全过滤条件；
                                                       1-->表示非安全过滤条件。 */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_SECURITYBASE_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_SECURITYBASE_securitybase_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_SECURITYBASE_securitybase_END    (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_SECURITYMASK_UNION
 结构说明  : A7TOVIVOBUS_WR_TRANS_F_SECURITYMASK 寄存器结构定义。地址偏移量:0xB030，初值:0x00000000，宽度:32
 寄存器说明: ISP_WR的Transaction Probe的安全过滤条件Mask
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  securitymask : 1;  /* bit[0-0] : 安全过滤条件：packet.Security & SecurityMask = SecurityBase & SecurityMasks；
                                                       也就是说当Filters_1_SecurityMask=1时安全过滤条件Filters_1_SecurityBase有效，可以过滤安全或非安全packet；否则，不起过滤作用； */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_SECURITYMASK_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_SECURITYMASK_securitymask_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_F_SECURITYMASK_securitymask_END    (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_ID_COREID_UNION
 结构说明  : A7TOVIVOBUS_WR_TRANS_P_ID_COREID 寄存器结构定义。地址偏移量:0xB080，初值:0xD535950A，宽度:32
 寄存器说明: A7TOVIVOBUS_RD TransactionStatProfilter域ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  coretypeid   : 8;  /* bit[0-7] : 类型ID */
        unsigned int  corechecksum : 24; /* bit[8-31]: 配置参数的校验和 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_ID_COREID_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_ID_COREID_coretypeid_START    (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_ID_COREID_coretypeid_END      (7)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_ID_COREID_corechecksum_START  (8)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_ID_REVISIONID_UNION
 结构说明  : A7TOVIVOBUS_WR_TRANS_P_ID_REVISIONID 寄存器结构定义。地址偏移量:0xB084，初值:0x012D5300，宽度:32
 寄存器说明: 代码版本
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  userid    : 8;  /* bit[0-7] : 用户自定义ID */
        unsigned int  flexnocid : 24; /* bit[8-31]: FlexNoC生成代码的软件版本 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_ID_REVISIONID_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_ID_REVISIONID_userid_START     (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_ID_REVISIONID_userid_END       (7)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_ID_REVISIONID_flexnocid_START  (8)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_EN_UNION
 结构说明  : A7TOVIVOBUS_WR_TRANS_P_EN 寄存器结构定义。地址偏移量:0xB088，初值:0x00000000，宽度:32
 寄存器说明: transaction Probe的counter使能配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  en       : 1;  /* bit[0-0] : 当配置为1时，使能Transaction Probe的统计计数器 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_EN_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_EN_en_START        (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_EN_en_END          (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_MODE_UNION
 结构说明  : A7TOVIVOBUS_WR_TRANS_P_MODE 寄存器结构定义。地址偏移量:0xB08C，初值:0x00000000，宽度:32
 寄存器说明: A7TOVIVOBUS_WR Transaction Probe的工作模式配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode     : 1;  /* bit[0]   : 0-->统计latency；
                                                   1-->统计outstanding； */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_MODE_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_MODE_mode_START      (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_MODE_mode_END        (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_THRESHOLDS_0_0_UNION
 结构说明  : A7TOVIVOBUS_WR_TRANS_P_THRESHOLDS_0_0 寄存器结构定义。地址偏移量:0xB0AC，初值:0x00000000，宽度:32
 寄存器说明: A7TOVIVOBUS_WR Transaction Probe的bin_0配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  thresholds_0_0 : 2;  /* bit[0-1] : 0x0-->选择threshold_0（delay：40；outstanding：2）；
                                                         0x1-->选择threshold_1（delay：96；outstanding：5）；
                                                         0x2-->选择threshold_2（delay：128；-----------------）；
                                                         0x3-->选择threshold_3（delay：256；-----------------）； */
        unsigned int  reserved       : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_THRESHOLDS_0_0_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_THRESHOLDS_0_0_thresholds_0_0_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_THRESHOLDS_0_0_thresholds_0_0_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_THRESHOLDS_0_1_UNION
 结构说明  : A7TOVIVOBUS_WR_TRANS_P_THRESHOLDS_0_1 寄存器结构定义。地址偏移量:0xB0B0，初值:0x00000000，宽度:32
 寄存器说明: A7TOVIVOBUS_WR Transaction Probe的bin_0配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  thresholds_0_1 : 2;  /* bit[0-1] : 0x0-->选择threshold_0（delay：1~40；outstanding：1~2）；
                                                         0x1-->选择threshold_1（delay：41~96；outstanding：3~5）；
                                                         0x2-->选择threshold_2（delay：97~128；-----------------）；
                                                         0x3-->选择threshold_3（delay：129~256；-----------------）； */
        unsigned int  reserved       : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_THRESHOLDS_0_1_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_THRESHOLDS_0_1_thresholds_0_1_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_THRESHOLDS_0_1_thresholds_0_1_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_OVERFLOWSTATUS_UNION
 结构说明  : A7TOVIVOBUS_WR_TRANS_P_OVERFLOWSTATUS 寄存器结构定义。地址偏移量:0xB0EC，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器溢出状态
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  overflowstatus : 1;  /* bit[0-0] : 1表示统计计数器溢出 */
        unsigned int  reserved       : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_OVERFLOWSTATUS_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_OVERFLOWSTATUS_overflowstatus_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_OVERFLOWSTATUS_overflowstatus_END    (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_OVERFLOWRESET_UNION
 结构说明  : A7TOVIVOBUS_WR_TRANS_P_OVERFLOWRESET 寄存器结构定义。地址偏移量:0xB0F0，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器溢出状态清零
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  overflowreset : 1;  /* bit[0-0] : 写1时，OverflowStatus寄存器清零，读该寄存器时钟返回0 */
        unsigned int  reserved      : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_OVERFLOWRESET_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_OVERFLOWRESET_overflowreset_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_OVERFLOWRESET_overflowreset_END    (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_PENDINGEVENTMODE_UNION
 结构说明  : A7TOVIVOBUS_WR_TRANS_P_PENDINGEVENTMODE 寄存器结构定义。地址偏移量:0xB0F4，初值:0x00000000，宽度:32
 寄存器说明: outstanding统计技术工作模式配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pendingeventmode : 1;  /* bit[0-0] : 0x0-->当outstanding数量 > 0时，每个cycle都去触发计数器收集outstanding个数；
                                                           0x1-->当返回1个response时，就触发计数器收集outstanding个数。 */
        unsigned int  reserved         : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_PENDINGEVENTMODE_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_PENDINGEVENTMODE_pendingeventmode_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_PENDINGEVENTMODE_pendingeventmode_END    (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_PRESCALER_UNION
 结构说明  : A7TOVIVOBUS_WR_TRANS_P_PRESCALER 寄存器结构定义。地址偏移量:0xB0F8，初值:0x00000000，宽度:32
 寄存器说明: latency统计系数配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  prescaler : 8;  /* bit[0-7] : 0-->handshake的模式，start event=begin request，end event=accept request；
                                                    1-->latency模式，start event=begin request + context ID，end event=begin response + context ID。 */
        unsigned int  reserved  : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_PRESCALER_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_PRESCALER_prescaler_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_P_PRESCALER_prescaler_END    (7)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_ID_COREID_UNION
 结构说明  : A7TOVIVOBUS_WR_TRANS_M_ID_COREID 寄存器结构定义。地址偏移量:0xB400，初值:0x567DD106，宽度:32
 寄存器说明: A7TOVIVOBUS_WR Transaction probe域ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_coreid : 32; /* bit[0-31]: VcodecBus的Packet Probe的域ID。 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_ID_COREID_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_ID_COREID_id_coreid_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_ID_COREID_id_coreid_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_ID_REVISIONID_UNION
 结构说明  : A7TOVIVOBUS_WR_TRANS_M_ID_REVISIONID 寄存器结构定义。地址偏移量:0xB404，初值:0x012D5300，宽度:32
 寄存器说明: 总线代码版本寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_revisionid : 32; /* bit[0-31]: 低8bit自定义，高24bit是NOC的配置HUSH值。 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_ID_REVISIONID_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_ID_REVISIONID_id_revisionid_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_ID_REVISIONID_id_revisionid_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_MAINCTL_UNION
 结构说明  : A7TOVIVOBUS_WR_TRANS_M_MAINCTL 寄存器结构定义。地址偏移量:0xB408，初值:0x00000000，宽度:32
 寄存器说明: Transaction Probe全局控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  erren                     : 1;  /* bit[0]   : ErrEn：使能Packet Probe将检测到的任何错误状态的Packet上报给Observer。由于本总线的Packet Probe不支持trace功能，故此位无意义。 */
        unsigned int  traceen                   : 1;  /* bit[1]   : TraceEn：该总线不支持Trace功能，故此位无意义。 */
        unsigned int  payloaden                 : 1;  /* bit[2]   : PayloadEn：该总线不支持Trace功能，故此位无意义。 */
        unsigned int  staten                    : 1;  /* bit[3]   : StatEn：统计模型使能寄存器，当StatEn由0配置为1时，统计计数器被清零；当StatEn配置为0时，统计计数器被disabled。 */
        unsigned int  alarmen                   : 1;  /* bit[4]   : AlarmEn：中断使能配置。
                                                                    0-->屏蔽中断；
                                                                    1-->使能中断输出。 */
        unsigned int  statconddump              : 1;  /* bit[5]   : 0-->表示无条件dump统计数据，寄存器counters_m_val的值，实时反映统计计数器的值；
                                                                    1-->表示有条件dump数据，在给定的统计周期内发生out of bounds 事件，才会将统计计数器的值dump至寄存器counters_m_val中。 */
        unsigned int  intrusivemode             : 1;  /* bit[6]   : IntrusiveMode： 该总线不支持Trace功能，故此位无意义。 */
        unsigned int  filtbytealwayschainableen : 1;  /* bit[7]   : FiltByteAlwaysChainableEn：奇数和偶数计数器串行使能的全局配置：
                                                                    0-->不使能，此时，所有侧statistic counters都可以被Map；
                                                                    1-->使能，只有偶数statistic counters才可以被Map。 */
        unsigned int  reserved                  : 24; /* bit[8-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_MAINCTL_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_MAINCTL_erren_START                      (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_MAINCTL_erren_END                        (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_MAINCTL_traceen_START                    (1)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_MAINCTL_traceen_END                      (1)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_MAINCTL_payloaden_START                  (2)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_MAINCTL_payloaden_END                    (2)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_MAINCTL_staten_START                     (3)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_MAINCTL_staten_END                       (3)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_MAINCTL_alarmen_START                    (4)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_MAINCTL_alarmen_END                      (4)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_MAINCTL_statconddump_START               (5)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_MAINCTL_statconddump_END                 (5)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_MAINCTL_intrusivemode_START              (6)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_MAINCTL_intrusivemode_END                (6)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_MAINCTL_filtbytealwayschainableen_START  (7)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_MAINCTL_filtbytealwayschainableen_END    (7)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_CFGCTL_UNION
 结构说明  : A7TOVIVOBUS_WR_TRANS_M_CFGCTL 寄存器结构定义。地址偏移量:0xB40C，初值:0x00000000，宽度:32
 寄存器说明: Packet Probe使能寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  globalen : 1;  /* bit[0]   : GlobalEn：Packet Probe使能信号，高有效。 */
        unsigned int  active   : 1;  /* bit[1]   : Active：Packet Probe的工作状态指示信号。
                                                   0-->当GlobalEn配置为0的几个cycle后，Active被拉低；
                                                   1-->当GlobalEn配置为1时，Active被拉高，此时不允许对Packet Probe进行配置。 */
        unsigned int  reserved : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_CFGCTL_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_CFGCTL_globalen_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_CFGCTL_globalen_END    (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_CFGCTL_active_START    (1)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_CFGCTL_active_END      (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_STATPERIOD_UNION
 结构说明  : A7TOVIVOBUS_WR_TRANS_M_STATPERIOD 寄存器结构定义。地址偏移量:0xB424，初值:0x00000000，宽度:32
 寄存器说明: 统计周期配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statperiod : 5;  /* bit[0-4] : 自动统计模式下的统计周期，统计周期= N_Cycle = 2^min(23,StatPeriod)，最大为8 mega cycles，最小为2 cycles。当配置为0时，自动统计模式被关闭，需要采用手动模式，也就是配置StatGo寄存器来实现带宽统计。 */
        unsigned int  reserved   : 27; /* bit[5-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_STATPERIOD_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_STATPERIOD_statperiod_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_STATPERIOD_statperiod_END    (4)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_STATGO_UNION
 结构说明  : A7TOVIVOBUS_WR_TRANS_M_STATGO 寄存器结构定义。地址偏移量:0xB428，初值:0x00000000，宽度:32
 寄存器说明: 手动带宽统计计时开始使能
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statgo   : 1;  /* bit[0]   : 当StatPeriod=0时，当globalen为1，向寄存器StatGo写1，则会将counter_m_val的值与statalarmmax或statalarmmin的值进行比较；读该寄存器始终返回0。 */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_STATGO_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_STATGO_statgo_START    (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_STATGO_statgo_END      (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_STATALARMMIN_UNION
 结构说明  : A7TOVIVOBUS_WR_TRANS_M_STATALARMMIN 寄存器结构定义。地址偏移量:0xB42C，初值:0x00000000，宽度:32
 寄存器说明: 统计计数最小告警阈值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statalarmmin : 32; /* bit[0-31]: 当任意一个统计计数器的值小于StatAlarmMin的值，就触发告警寄存器。 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_STATALARMMIN_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_STATALARMMIN_statalarmmin_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_STATALARMMIN_statalarmmin_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_STATALARMMAX_UNION
 结构说明  : A7TOVIVOBUS_WR_TRANS_M_STATALARMMAX 寄存器结构定义。地址偏移量:0xB430，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器最大告警阈值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statalarmmax : 32; /* bit[0-31]: 当任意一个统计计数器的值大于StatAlarmMax的值，就触发告警寄存器。 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_STATALARMMAX_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_STATALARMMAX_statalarmmax_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_STATALARMMAX_statalarmmax_END    (31)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_STATALARMSTATUS_UNION
 结构说明  : A7TOVIVOBUS_WR_TRANS_M_STATALARMSTATUS 寄存器结构定义。地址偏移量:0xB434，初值:0x00000000，宽度:32
 寄存器说明: 告警状态寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statalarmstatus : 1;  /* bit[0]   : 当任意一个统计计数器的值大于StatAlarmMax或小于StatAlarmMin，则该寄存器置位为1； */
        unsigned int  reserved        : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_STATALARMSTATUS_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_STATALARMSTATUS_statalarmstatus_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_STATALARMSTATUS_statalarmstatus_END    (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_STATALARMCLR_UNION
 结构说明  : A7TOVIVOBUS_WR_TRANS_M_STATALARMCLR 寄存器结构定义。地址偏移量:0xB438，初值:0x00000000，宽度:32
 寄存器说明: 告警状态清除寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  statalarmclr : 1;  /* bit[0]   : 写1会清零StatAlarmStatus寄存器，读此寄存器返回总是0； */
        unsigned int  reserved     : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_STATALARMCLR_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_STATALARMCLR_statalarmclr_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_STATALARMCLR_statalarmclr_END    (0)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_0_SRC_UNION
 结构说明  : A7TOVIVOBUS_WR_TRANS_M_COUNTERS_0_SRC 寄存器结构定义。地址偏移量:0xB538，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_0_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：2~4）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：>= 5）；
                                                         0x23-->Bin 3（delay：128~255；----------------）；
                                                         0x24-->Bin 4（delay：>= 256；----------------）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_0_SRC_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_0_SRC_counters_0_src_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_0_SRC_counters_0_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_0_ALARMMODE_UNION
 结构说明  : A7TOVIVOBUS_WR_TRANS_M_COUNTERS_0_ALARMMODE 寄存器结构定义。地址偏移量:0xB53C，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_0_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_0_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_0_ALARMMODE_counters_0_alarmmode_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_0_ALARMMODE_counters_0_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_0_VAL_UNION
 结构说明  : A7TOVIVOBUS_WR_TRANS_M_COUNTERS_0_VAL 寄存器结构定义。地址偏移量:0xB540，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_0_val : 11; /* bit[0-10] : 当Counters_0_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_0_VAL_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_0_VAL_counters_0_val_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_0_VAL_counters_0_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_1_SRC_UNION
 结构说明  : A7TOVIVOBUS_WR_TRANS_M_COUNTERS_1_SRC 寄存器结构定义。地址偏移量:0xB54C，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_1_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：2~4）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：>= 5）；
                                                         0x23-->Bin 3（delay：128~255；----------------）；
                                                         0x24-->Bin 4（delay：>= 256；----------------）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_1_SRC_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_1_SRC_counters_1_src_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_1_SRC_counters_1_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_1_ALARMMODE_UNION
 结构说明  : A7TOVIVOBUS_WR_TRANS_M_COUNTERS_1_ALARMMODE 寄存器结构定义。地址偏移量:0xB550，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_1_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_1_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_1_ALARMMODE_counters_1_alarmmode_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_1_ALARMMODE_counters_1_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_1_VAL_UNION
 结构说明  : A7TOVIVOBUS_WR_TRANS_M_COUNTERS_1_VAL 寄存器结构定义。地址偏移量:0xB554，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_1_val : 11; /* bit[0-10] : 当Counters_1_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_1_VAL_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_1_VAL_counters_1_val_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_1_VAL_counters_1_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_2_SRC_UNION
 结构说明  : A7TOVIVOBUS_WR_TRANS_M_COUNTERS_2_SRC 寄存器结构定义。地址偏移量:0xB560，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_2_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：2~4）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：>= 5）；
                                                         0x23-->Bin 3（delay：128~255；----------------）；
                                                         0x24-->Bin 4（delay：>= 256；----------------）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_2_SRC_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_2_SRC_counters_2_src_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_2_SRC_counters_2_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_2_ALARMMODE_UNION
 结构说明  : A7TOVIVOBUS_WR_TRANS_M_COUNTERS_2_ALARMMODE 寄存器结构定义。地址偏移量:0xB564，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_2_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_2_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_2_ALARMMODE_counters_2_alarmmode_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_2_ALARMMODE_counters_2_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_2_VAL_UNION
 结构说明  : A7TOVIVOBUS_WR_TRANS_M_COUNTERS_2_VAL 寄存器结构定义。地址偏移量:0xB568，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_2_val : 11; /* bit[0-10] : 当Counters_2_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_2_VAL_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_2_VAL_counters_2_val_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_2_VAL_counters_2_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_3_SRC_UNION
 结构说明  : A7TOVIVOBUS_WR_TRANS_M_COUNTERS_3_SRC 寄存器结构定义。地址偏移量:0xB574，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_3_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：2~4）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：>= 5）；
                                                         0x23-->Bin 3（delay：128~255；----------------）；
                                                         0x24-->Bin 4（delay：>= 256；----------------）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_3_SRC_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_3_SRC_counters_3_src_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_3_SRC_counters_3_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_3_ALARMMODE_UNION
 结构说明  : A7TOVIVOBUS_WR_TRANS_M_COUNTERS_3_ALARMMODE 寄存器结构定义。地址偏移量:0xB578，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_3_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_3_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_3_ALARMMODE_counters_3_alarmmode_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_3_ALARMMODE_counters_3_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_3_VAL_UNION
 结构说明  : A7TOVIVOBUS_WR_TRANS_M_COUNTERS_3_VAL 寄存器结构定义。地址偏移量:0xB57C，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_3_val : 11; /* bit[0-10] : 当Counters_3_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_3_VAL_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_3_VAL_counters_3_val_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_3_VAL_counters_3_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_4_SRC_UNION
 结构说明  : A7TOVIVOBUS_WR_TRANS_M_COUNTERS_4_SRC 寄存器结构定义。地址偏移量:0xB588，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_4_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：2~4）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：>= 5）；
                                                         0x23-->Bin 3（delay：128~255；----------------）；
                                                         0x24-->Bin 4（delay：>= 256；----------------）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_4_SRC_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_4_SRC_counters_4_src_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_4_SRC_counters_4_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_4_ALARMMODE_UNION
 结构说明  : A7TOVIVOBUS_WR_TRANS_M_COUNTERS_4_ALARMMODE 寄存器结构定义。地址偏移量:0xB58C，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_4_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_4_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_4_ALARMMODE_counters_4_alarmmode_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_4_ALARMMODE_counters_4_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_4_VAL_UNION
 结构说明  : A7TOVIVOBUS_WR_TRANS_M_COUNTERS_4_VAL 寄存器结构定义。地址偏移量:0xB590，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_4_val : 11; /* bit[0-10] : 当Counters_4_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_4_VAL_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_4_VAL_counters_4_val_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_4_VAL_counters_4_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_5_SRC_UNION
 结构说明  : A7TOVIVOBUS_WR_TRANS_M_COUNTERS_5_SRC 寄存器结构定义。地址偏移量:0xB59C，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_5_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：2~4）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：>= 5）；
                                                         0x23-->Bin 3（delay：128~255；----------------）；
                                                         0x24-->Bin 4（delay：>= 256；----------------）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_5_SRC_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_5_SRC_counters_5_src_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_5_SRC_counters_5_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_5_ALARMMODE_UNION
 结构说明  : A7TOVIVOBUS_WR_TRANS_M_COUNTERS_5_ALARMMODE 寄存器结构定义。地址偏移量:0xB5A0，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_5_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_5_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_5_ALARMMODE_counters_5_alarmmode_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_5_ALARMMODE_counters_5_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_5_VAL_UNION
 结构说明  : A7TOVIVOBUS_WR_TRANS_M_COUNTERS_5_VAL 寄存器结构定义。地址偏移量:0xB5A4，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_5_val : 11; /* bit[0-10] : 当Counters_5_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_5_VAL_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_5_VAL_counters_5_val_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_5_VAL_counters_5_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_6_SRC_UNION
 结构说明  : A7TOVIVOBUS_WR_TRANS_M_COUNTERS_6_SRC 寄存器结构定义。地址偏移量:0xB5B0，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_6_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：2~4）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：>= 5）；
                                                         0x23-->Bin 3（delay：128~255；----------------）；
                                                         0x24-->Bin 4（delay：>= 256；----------------）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_6_SRC_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_6_SRC_counters_6_src_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_6_SRC_counters_6_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_6_ALARMMODE_UNION
 结构说明  : A7TOVIVOBUS_WR_TRANS_M_COUNTERS_6_ALARMMODE 寄存器结构定义。地址偏移量:0xB5B4，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_6_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_6_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_6_ALARMMODE_counters_6_alarmmode_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_6_ALARMMODE_counters_6_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_6_VAL_UNION
 结构说明  : A7TOVIVOBUS_WR_TRANS_M_COUNTERS_6_VAL 寄存器结构定义。地址偏移量:0xB5B8，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_6_val : 11; /* bit[0-10] : 当Counters_6_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_6_VAL_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_6_VAL_counters_6_val_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_6_VAL_counters_6_val_END    (10)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_7_SRC_UNION
 结构说明  : A7TOVIVOBUS_WR_TRANS_M_COUNTERS_7_SRC 寄存器结构定义。地址偏移量:0xB5C4，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_7_src : 6;  /* bit[0-5] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x20-->Bin 0（delay：0~39；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：40~95；outstanding：2~4）；
                                                         0x22-->Bin 2（delay：96~127；outstanding：>= 5）；
                                                         0x23-->Bin 3（delay：128~255；----------------）；
                                                         0x24-->Bin 4（delay：>= 256；----------------）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_7_SRC_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_7_SRC_counters_7_src_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_7_SRC_counters_7_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_7_ALARMMODE_UNION
 结构说明  : A7TOVIVOBUS_WR_TRANS_M_COUNTERS_7_ALARMMODE 寄存器结构定义。地址偏移量:0xB5C8，初值:0x00000000，宽度:32
 寄存器说明: 告警中断产生配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_7_alarmmode : 2;  /* bit[0-1] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                               0x0-->OFF，告警模式配置disabled；
                                                               0x1-->MIN，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值，则StatAlarmStatus为1；
                                                               0x2-->MAX，在statperiod配置的统计周期结束后，counter的值大于StatAlarmMax寄存器的值，则StatAlarmStatus为1；
                                                               0x3-->MIN_MAX，在statperiod配置的统计周期结束后，counter的值小于StatAlarmMin寄存器的值或大于StatAlarmMax寄存器的值，则StatAlarmStatus为1； */
        unsigned int  reserved             : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_7_ALARMMODE_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_7_ALARMMODE_counters_7_alarmmode_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_7_ALARMMODE_counters_7_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_7_VAL_UNION
 结构说明  : A7TOVIVOBUS_WR_TRANS_M_COUNTERS_7_VAL 寄存器结构定义。地址偏移量:0xB5CC，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_7_val : 11; /* bit[0-10] : 当Counters_7_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 21; /* bit[11-31]: 保留 */
    } reg;
} SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_7_VAL_UNION;
#endif
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_7_VAL_counters_7_val_START  (0)
#define SOC_VIVO_BUS_A7TOVIVOBUS_WR_TRANS_M_COUNTERS_7_VAL_counters_7_val_END    (10)






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

#endif /* end of soc_vivo_bus_interface.h */
