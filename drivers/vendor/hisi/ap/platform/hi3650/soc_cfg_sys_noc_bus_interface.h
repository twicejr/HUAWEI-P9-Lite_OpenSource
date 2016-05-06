/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_cfg_sys_noc_bus_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:18:56
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_CFG_SYS_NOC_BUS.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_CFG_SYS_NOC_BUS_INTERFACE_H__
#define __SOC_CFG_SYS_NOC_BUS_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/9) MODEMBUS
 ****************************************************************************/
/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM_QOS_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_ID_COREID_ADDR(base) ((base) + (0x0000))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM_QOS_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0004))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM_QOS_PRIORITY_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_PRIORITY_ADDR(base) ((base) + (0x0008))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM_QOS_MODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_MODE_ADDR(base) ((base) + (0x000C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM_QOS_EXTCONTROL_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0018))

/* 寄存器说明：MODEMBUS Err probe域ID
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERR_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERR_ID_COREID_ADDR(base) ((base) + (0x1C00))

/* 寄存器说明：总线代码版本寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERR_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERR_ID_REVISIONID_ADDR(base) ((base) + (0x1C04))

/* 寄存器说明：MODEMBUS Err probe使能
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEMBUS_FAULTEN_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_FAULTEN_ADDR(base) ((base) + (0x1C08))

/* 寄存器说明：Error log有效指示寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRVLD_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRVLD_ADDR(base) ((base) + (0x1C0C))

/* 寄存器说明：中断清除寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRCLR_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRCLR_ADDR(base) ((base) + (0x1C10))

/* 寄存器说明：Error log0
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG0_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG0_ADDR(base) ((base) + (0x1C14))

/* 寄存器说明：Error log1
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG1_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG1_ADDR(base) ((base) + (0x1C18))

/* 寄存器说明：Error log3
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG3_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG3_ADDR(base) ((base) + (0x1C20))

/* 寄存器说明：Error log5
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG5_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG5_ADDR(base) ((base) + (0x1C28))

/* 寄存器说明：Error log7
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG7_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG7_ADDR(base) ((base) + (0x1C30))

/* 寄存器说明：MODEM TransactionStatFilter域ID
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ID_COREID_ADDR(base) ((base) + (0x8000))

/* 寄存器说明：代码版本
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ID_REVISIONID_ADDR(base) ((base) + (0x8004))

/* 寄存器说明：MODEM Transaction Probe的Filter工作模式配置寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_MODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_MODE_ADDR(base) ((base) + (0x8008))

/* 寄存器说明：地址过滤基地址
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ADDRBASE_LOW_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ADDRBASE_LOW_ADDR(base) ((base) + (0x800C))

/* 寄存器说明：地址过滤窗口
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ADDRWINDOWSIZE_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ADDRWINDOWSIZE_ADDR(base) ((base) + (0x8014))

/* 寄存器说明：MODEM的Transaction Probe的Opcode过滤条件
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_OPCODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_OPCODE_ADDR(base) ((base) + (0x8020))

/* 寄存器说明：MODEM的Transaction Probe的User过滤条件
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_USERBASE_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_USERBASE_ADDR(base) ((base) + (0x8024))

/* 寄存器说明：MODEM的Transaction Probe的User过滤条件Mask
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_USERMASK_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_USERMASK_ADDR(base) ((base) + (0x8028))

/* 寄存器说明：MODEM的Transaction Probe的安全过滤条件
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_SECURITYBASE_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_SECURITYBASE_ADDR(base) ((base) + (0x802C))

/* 寄存器说明：MODEM的Transaction Probe的安全过滤条件Mask
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_SECURITYMASK_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_SECURITYMASK_ADDR(base) ((base) + (0x8030))

/* 寄存器说明：MODEM TransactionStatProfilter域ID
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_ID_COREID_ADDR(base) ((base) + (0x8080))

/* 寄存器说明：代码版本
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_ID_REVISIONID_ADDR(base) ((base) + (0x8084))

/* 寄存器说明：transaction Probe的counter使能配置
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_EN_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_EN_ADDR(base) ((base) + (0x8088))

/* 寄存器说明：MODEM Transaction Probe的工作模式配置
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_MODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_MODE_ADDR(base) ((base) + (0x808C))

/* 寄存器说明：MODEM Transaction Probe的bin_0配置
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_THRESHOLDS_0_0_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_THRESHOLDS_0_0_ADDR(base) ((base) + (0x80AC))

/* 寄存器说明：MODEM Transaction Probe的bin_0配置
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_THRESHOLDS_0_1_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_THRESHOLDS_0_1_ADDR(base) ((base) + (0x80B0))

/* 寄存器说明：统计计数器溢出状态
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_OVERFLOWSTATUS_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_OVERFLOWSTATUS_ADDR(base) ((base) + (0x80EC))

/* 寄存器说明：统计计数器溢出状态清零
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_OVERFLOWRESET_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_OVERFLOWRESET_ADDR(base) ((base) + (0x80F0))

/* 寄存器说明：outstanding统计技术工作模式配置
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_PENDINGEVENTMODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_PENDINGEVENTMODE_ADDR(base) ((base) + (0x80F4))

/* 寄存器说明：latency统计系数配置
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_PRESCALER_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_PRESCALER_ADDR(base) ((base) + (0x80F8))

/* 寄存器说明：MODEM Transaction probe域ID
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_ID_COREID_ADDR(base) ((base) + (0x8400))

/* 寄存器说明：总线代码版本寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_ID_REVISIONID_ADDR(base) ((base) + (0x8404))

/* 寄存器说明：Transaction Probe全局控制寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_MAINCTL_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_MAINCTL_ADDR(base) ((base) + (0x8408))

/* 寄存器说明：Packet Probe使能寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_CFGCTL_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_CFGCTL_ADDR(base) ((base) + (0x840C))

/* 寄存器说明：统计周期配置寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATPERIOD_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATPERIOD_ADDR(base) ((base) + (0x8424))

/* 寄存器说明：手动带宽统计计时开始使能
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATGO_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATGO_ADDR(base) ((base) + (0x8428))

/* 寄存器说明：统计计数最小告警阈值
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMMIN_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMMIN_ADDR(base) ((base) + (0x842C))

/* 寄存器说明：统计计数器最大告警阈值
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMMAX_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMMAX_ADDR(base) ((base) + (0x8430))

/* 寄存器说明：告警状态寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMSTATUS_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMSTATUS_ADDR(base) ((base) + (0x8434))

/* 寄存器说明：告警状态清除寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMCLR_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMCLR_ADDR(base) ((base) + (0x8438))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_0_SRC_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_0_SRC_ADDR(base) ((base) + (0x8538))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_0_ALARMMODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_0_ALARMMODE_ADDR(base) ((base) + (0x853C))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_0_VAL_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_0_VAL_ADDR(base) ((base) + (0x8540))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_1_SRC_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_1_SRC_ADDR(base) ((base) + (0x854C))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_1_ALARMMODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_1_ALARMMODE_ADDR(base) ((base) + (0x8550))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_1_VAL_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_1_VAL_ADDR(base) ((base) + (0x8554))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_2_SRC_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_2_SRC_ADDR(base) ((base) + (0x8560))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_2_ALARMMODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_2_ALARMMODE_ADDR(base) ((base) + (0x8564))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_2_VAL_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_2_VAL_ADDR(base) ((base) + (0x8568))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_3_SRC_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_3_SRC_ADDR(base) ((base) + (0x8574))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_3_ALARMMODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_3_ALARMMODE_ADDR(base) ((base) + (0x8578))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_3_VAL_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_3_VAL_ADDR(base) ((base) + (0x857C))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_4_SRC_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_4_SRC_ADDR(base) ((base) + (0x8588))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_4_ALARMMODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_4_ALARMMODE_ADDR(base) ((base) + (0x858C))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_4_VAL_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_4_VAL_ADDR(base) ((base) + (0x8590))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_5_SRC_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_5_SRC_ADDR(base) ((base) + (0x859C))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_5_ALARMMODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_5_ALARMMODE_ADDR(base) ((base) + (0x85A0))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_5_VAL_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_5_VAL_ADDR(base) ((base) + (0x85A4))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_6_SRC_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_6_SRC_ADDR(base) ((base) + (0x85B0))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_6_ALARMMODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_6_ALARMMODE_ADDR(base) ((base) + (0x85B4))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_6_VAL_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_6_VAL_ADDR(base) ((base) + (0x85B8))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_7_SRC_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_7_SRC_ADDR(base) ((base) + (0x85C4))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_7_ALARMMODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_7_ALARMMODE_ADDR(base) ((base) + (0x85C8))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_7_VAL_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_7_VAL_ADDR(base) ((base) + (0x85CC))



/****************************************************************************
                     (2/9) ASPBUS
 ****************************************************************************/
/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_QOS_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_ID_COREID_ADDR(base) ((base) + (0x0000))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_QOS_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0004))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_QOS_PRIORITY_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_PRIORITY_ADDR(base) ((base) + (0x0008))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_QOS_MODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_MODE_ADDR(base)   ((base) + (0x000C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_QOS_BANDWIDTH_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_BANDWIDTH_ADDR(base) ((base) + (0x0010))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_QOS_SATURATION_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_SATURATION_ADDR(base) ((base) + (0x0014))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_QOS_EXTCONTROL_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0018))

/* 寄存器说明：ASP TransactionStatFilter域ID
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ID_COREID_ADDR(base) ((base) + (0x8000))

/* 寄存器说明：代码版本
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ID_REVISIONID_ADDR(base) ((base) + (0x8004))

/* 寄存器说明：ASP Transaction Probe的Filter工作模式配置寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_MODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_MODE_ADDR(base) ((base) + (0x8008))

/* 寄存器说明：地址过滤基地址
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ADDRBASE_LOW_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ADDRBASE_LOW_ADDR(base) ((base) + (0x800C))

/* 寄存器说明：地址过滤窗口
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ADDRWINDOWSIZE_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ADDRWINDOWSIZE_ADDR(base) ((base) + (0x8014))

/* 寄存器说明：ASP的Transaction Probe的Opcode过滤条件
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_OPCODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_OPCODE_ADDR(base) ((base) + (0x8020))

/* 寄存器说明：ASP的Transaction Probe的User过滤条件
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_USERBASE_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_USERBASE_ADDR(base) ((base) + (0x8024))

/* 寄存器说明：ASP的Transaction Probe的User过滤条件Mask
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_USERMASK_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_USERMASK_ADDR(base) ((base) + (0x8028))

/* 寄存器说明：ASP的Transaction Probe的安全过滤条件
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_SECURITYBASE_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_SECURITYBASE_ADDR(base) ((base) + (0x802C))

/* 寄存器说明：ASP的Transaction Probe的安全过滤条件Mask
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_SECURITYMASK_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_SECURITYMASK_ADDR(base) ((base) + (0x8030))

/* 寄存器说明：ASP TransactionStatProfilter域ID
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_ID_COREID_ADDR(base) ((base) + (0x8080))

/* 寄存器说明：代码版本
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_ID_REVISIONID_ADDR(base) ((base) + (0x8084))

/* 寄存器说明：transaction Probe的counter使能配置
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_EN_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_EN_ADDR(base) ((base) + (0x8088))

/* 寄存器说明：ASP Transaction Probe的工作模式配置
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_MODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_MODE_ADDR(base) ((base) + (0x808C))

/* 寄存器说明：ASP Transaction Probe的bin_0配置
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_0_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_0_ADDR(base) ((base) + (0x80AC))

/* 寄存器说明：ASP Transaction Probe的bin_1配置
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_1_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_1_ADDR(base) ((base) + (0x80B0))

/* 寄存器说明：ASP Transaction Probe的bin_1配置
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_2_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_2_ADDR(base) ((base) + (0x80B4))

/* 寄存器说明：ASP Transaction Probe的bin_1配置
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_3_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_3_ADDR(base) ((base) + (0x80B8))

/* 寄存器说明：统计计数器溢出状态
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_OVERFLOWSTATUS_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_OVERFLOWSTATUS_ADDR(base) ((base) + (0x80EC))

/* 寄存器说明：统计计数器溢出状态清零
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_OVERFLOWRESET_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_OVERFLOWRESET_ADDR(base) ((base) + (0x80F0))

/* 寄存器说明：outstanding统计技术工作模式配置
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_PENDINGEVENTMODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_PENDINGEVENTMODE_ADDR(base) ((base) + (0x80F4))

/* 寄存器说明：latency统计系数配置
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_PRESCALER_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_PRESCALER_ADDR(base) ((base) + (0x80F8))

/* 寄存器说明：ASP Transaction probe域ID
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_ID_COREID_ADDR(base) ((base) + (0x8400))

/* 寄存器说明：总线代码版本寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_ID_REVISIONID_ADDR(base) ((base) + (0x8404))

/* 寄存器说明：Transaction Probe全局控制寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_MAINCTL_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_MAINCTL_ADDR(base) ((base) + (0x8408))

/* 寄存器说明：Packet Probe使能寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_CFGCTL_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_CFGCTL_ADDR(base) ((base) + (0x840C))

/* 寄存器说明：统计周期配置寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATPERIOD_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATPERIOD_ADDR(base) ((base) + (0x8424))

/* 寄存器说明：手动带宽统计计时开始使能
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATGO_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATGO_ADDR(base) ((base) + (0x8428))

/* 寄存器说明：统计计数最小告警阈值
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMMIN_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMMIN_ADDR(base) ((base) + (0x842C))

/* 寄存器说明：统计计数器最大告警阈值
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMMAX_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMMAX_ADDR(base) ((base) + (0x8430))

/* 寄存器说明：告警状态寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMSTATUS_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMSTATUS_ADDR(base) ((base) + (0x8434))

/* 寄存器说明：告警状态清除寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMCLR_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMCLR_ADDR(base) ((base) + (0x8438))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_0_SRC_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_0_SRC_ADDR(base) ((base) + (0x8538))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_0_ALARMMODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_0_ALARMMODE_ADDR(base) ((base) + (0x853C))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_0_VAL_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_0_VAL_ADDR(base) ((base) + (0x8540))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_1_SRC_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_1_SRC_ADDR(base) ((base) + (0x854C))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_1_ALARMMODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_1_ALARMMODE_ADDR(base) ((base) + (0x8550))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_1_VAL_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_1_VAL_ADDR(base) ((base) + (0x8554))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_2_SRC_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_2_SRC_ADDR(base) ((base) + (0x8560))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_2_ALARMMODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_2_ALARMMODE_ADDR(base) ((base) + (0x8564))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_2_VAL_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_2_VAL_ADDR(base) ((base) + (0x8568))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_3_SRC_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_3_SRC_ADDR(base) ((base) + (0x8574))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_3_ALARMMODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_3_ALARMMODE_ADDR(base) ((base) + (0x8578))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_3_VAL_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_3_VAL_ADDR(base) ((base) + (0x857C))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_4_SRC_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_4_SRC_ADDR(base) ((base) + (0x8588))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_4_ALARMMODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_4_ALARMMODE_ADDR(base) ((base) + (0x858C))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_4_VAL_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_4_VAL_ADDR(base) ((base) + (0x8590))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_5_SRC_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_5_SRC_ADDR(base) ((base) + (0x859C))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_5_ALARMMODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_5_ALARMMODE_ADDR(base) ((base) + (0x85A0))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_5_VAL_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_5_VAL_ADDR(base) ((base) + (0x85A4))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_6_SRC_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_6_SRC_ADDR(base) ((base) + (0x85B0))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_6_ALARMMODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_6_ALARMMODE_ADDR(base) ((base) + (0x85B4))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_6_VAL_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_6_VAL_ADDR(base) ((base) + (0x85B8))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_7_SRC_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_7_SRC_ADDR(base) ((base) + (0x85C4))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_7_ALARMMODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_7_ALARMMODE_ADDR(base) ((base) + (0x85C8))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_7_VAL_UNION */
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_7_VAL_ADDR(base) ((base) + (0x85CC))



/****************************************************************************
                     (3/9) SYSBUS
 ****************************************************************************/
/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_ID_COREID_ADDR(base) ((base) + (0x0000))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0004))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_PRIORITY_UNION */
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_PRIORITY_ADDR(base) ((base) + (0x0008))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_MODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_MODE_ADDR(base) ((base) + (0x000C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_EXTCONTROL_UNION */
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0018))

/* 寄存器说明：adapter域ID
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAPTER_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAPTER_ID_COREID_ADDR(base) ((base) + (0x1000))

/* 寄存器说明：总线代码版本寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAPTER_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAPTER_ID_REVISIONID_ADDR(base) ((base) + (0x1004))

/* 寄存器说明：Rate Adapter配置寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAPTERRATE_UNION */
#define SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAPTERRATE_ADDR(base) ((base) + (0x1008))

/* 寄存器说明：Rate Adapter bypass寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAP_BYPASS_UNION */
#define SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAP_BYPASS_ADDR(base) ((base) + (0x100C))

/* 寄存器说明：adapter域ID
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAPTER_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAPTER_ID_COREID_ADDR(base) ((base) + (0x1080))

/* 寄存器说明：总线代码版本寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAPTER_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAPTER_ID_REVISIONID_ADDR(base) ((base) + (0x1084))

/* 寄存器说明：Rate Adapter配置寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAPTERRATE_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAPTERRATE_ADDR(base) ((base) + (0x1088))

/* 寄存器说明：Rate Adapter bypass寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAP_BYPASS_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAP_BYPASS_ADDR(base) ((base) + (0x108C))

/* 寄存器说明：adapter域ID
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAPTER_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAPTER_ID_COREID_ADDR(base) ((base) + (0x1100))

/* 寄存器说明：总线代码版本寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAPTER_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAPTER_ID_REVISIONID_ADDR(base) ((base) + (0x1104))

/* 寄存器说明：Rate Adapter配置寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAPTERRATE_UNION */
#define SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAPTERRATE_ADDR(base) ((base) + (0x1108))

/* 寄存器说明：Rate Adapter bypass寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAP_BYPASS_UNION */
#define SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAP_BYPASS_ADDR(base) ((base) + (0x110C))

/* 寄存器说明：adapter域ID
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAPTER_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAPTER_ID_COREID_ADDR(base) ((base) + (0x1180))

/* 寄存器说明：总线代码版本寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAPTER_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAPTER_ID_REVISIONID_ADDR(base) ((base) + (0x1184))

/* 寄存器说明：Rate Adapter配置寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAPTERRATE_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAPTERRATE_ADDR(base) ((base) + (0x1188))

/* 寄存器说明：Rate Adapter bypass寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAP_BYPASS_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAP_BYPASS_ADDR(base) ((base) + (0x118C))

/* 寄存器说明：adapter域ID
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAPTER_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAPTER_ID_COREID_ADDR(base) ((base) + (0x1200))

/* 寄存器说明：总线代码版本寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAPTER_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAPTER_ID_REVISIONID_ADDR(base) ((base) + (0x1204))

/* 寄存器说明：Rate Adapter配置寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAPTERRATE_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAPTERRATE_ADDR(base) ((base) + (0x1208))

/* 寄存器说明：Rate Adapter bypass寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAP_BYPASS_UNION */
#define SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAP_BYPASS_ADDR(base) ((base) + (0x120C))

/* 寄存器说明：adapter域ID
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAPTER_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAPTER_ID_COREID_ADDR(base) ((base) + (0x1280))

/* 寄存器说明：总线代码版本寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAPTER_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAPTER_ID_REVISIONID_ADDR(base) ((base) + (0x1284))

/* 寄存器说明：Rate Adapter配置寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAPTERRATE_UNION */
#define SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAPTERRATE_ADDR(base) ((base) + (0x1288))

/* 寄存器说明：Rate Adapter bypass寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAP_BYPASS_UNION */
#define SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAP_BYPASS_ADDR(base) ((base) + (0x128C))

/* 寄存器说明：adapter域ID
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MMC1_ADAPTER_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC1_ADAPTER_ID_COREID_ADDR(base) ((base) + (0x1300))

/* 寄存器说明：总线代码版本寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MMC1_ADAPTER_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC1_ADAPTER_ID_REVISIONID_ADDR(base) ((base) + (0x1304))

/* 寄存器说明：Rate Adapter配置寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MMC1_ADAPTERRATE_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC1_ADAPTERRATE_ADDR(base) ((base) + (0x1308))

/* 寄存器说明：Rate Adapter bypass寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MMC1_ADAP_BYPASS_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC1_ADAP_BYPASS_ADDR(base) ((base) + (0x130C))

/* 寄存器说明：SYSBUS Err probe域ID
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SYSBUS_ERR_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERR_ID_COREID_ADDR(base) ((base) + (0x1C00))

/* 寄存器说明：总线代码版本寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SYSBUS_ERR_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERR_ID_REVISIONID_ADDR(base) ((base) + (0x1C04))

/* 寄存器说明：SYSBUS Err probe使能
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SYSBUS_FAULTEN_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_FAULTEN_ADDR(base) ((base) + (0x1C08))

/* 寄存器说明：Error log有效指示寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRVLD_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRVLD_ADDR(base)  ((base) + (0x1C0C))

/* 寄存器说明：中断清除寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRCLR_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRCLR_ADDR(base)  ((base) + (0x1C10))

/* 寄存器说明：Error log0
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG0_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG0_ADDR(base) ((base) + (0x1C14))

/* 寄存器说明：Error log1
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG1_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG1_ADDR(base) ((base) + (0x1C18))

/* 寄存器说明：Error log3
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG3_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG3_ADDR(base) ((base) + (0x1C20))

/* 寄存器说明：Error log5
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG5_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG5_ADDR(base) ((base) + (0x1C28))

/* 寄存器说明：Error log7
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG7_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG7_ADDR(base) ((base) + (0x1C30))

/* 寄存器说明：SYSBUS_DDRC Packet probe域ID
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_ID_COREID_ADDR(base) ((base) + (0x2000))

/* 寄存器说明：总线代码版本寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_ID_REVISIONID_ADDR(base) ((base) + (0x2004))

/* 寄存器说明：Packet Probe全局控制寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_MAINCTL_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_MAINCTL_ADDR(base) ((base) + (0x2008))

/* 寄存器说明：Packet Probe使能寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_CFGCTL_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_CFGCTL_ADDR(base) ((base) + (0x200C))

/* 寄存器说明：过滤条件查找表
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_FILTERLUT_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_FILTERLUT_ADDR(base) ((base) + (0x2014))

/* 寄存器说明：统计周期配置寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATPERIOD_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATPERIOD_ADDR(base) ((base) + (0x2024))

/* 寄存器说明：手动带宽统计计时开始使能
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATGO_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATGO_ADDR(base) ((base) + (0x2028))

/* 寄存器说明：统计计数最小告警阈值
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMMIN_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMMIN_ADDR(base) ((base) + (0x202C))

/* 寄存器说明：统计计数器最大告警阈值
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMMAX_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMMAX_ADDR(base) ((base) + (0x2030))

/* 寄存器说明：告警状态寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMSTATUS_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMSTATUS_ADDR(base) ((base) + (0x2034))

/* 寄存器说明：告警状态清除寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMCLR_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMCLR_ADDR(base) ((base) + (0x2038))

/* 寄存器说明：F0的RouteId过滤条件配置
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_ROUTEIDBASE_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_ROUTEIDBASE_ADDR(base) ((base) + (0x2044))

/* 寄存器说明：F0的RouteId过滤条件Mask配置
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_ROUTEIDMASK_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_ROUTEIDMASK_ADDR(base) ((base) + (0x2048))

/* 寄存器说明：F0的地址过滤条件配置
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_ADDRBASE_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_ADDRBASE_ADDR(base) ((base) + (0x204C))

/* 寄存器说明：F0的地址过滤的Mask地址大小配置
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_WINDOWSIZE_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_WINDOWSIZE_ADDR(base) ((base) + (0x2054))

/* 寄存器说明：F0的安全过滤条件配置
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_SECURITYBASE_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_SECURITYBASE_ADDR(base) ((base) + (0x2058))

/* 寄存器说明：F0的安全过滤条件的Mask
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_SECURITYMASK_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_SECURITYMASK_ADDR(base) ((base) + (0x205C))

/* 寄存器说明：F0的Opcode过滤条件配置
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_OPCODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_OPCODE_ADDR(base) ((base) + (0x2060))

/* 寄存器说明：F0的packet状态过滤条件
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_STATUS_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_STATUS_ADDR(base) ((base) + (0x2064))

/* 寄存器说明：F0的包长过滤条件
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_LENGTH_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_LENGTH_ADDR(base) ((base) + (0x2068))

/* 寄存器说明：F0的urgency过滤条件
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_URGENCY_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_URGENCY_ADDR(base) ((base) + (0x206C))

/* 寄存器说明：F0的User过滤条件
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_USERBASE_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_USERBASE_ADDR(base) ((base) + (0x2070))

/* 寄存器说明：F0的User过滤条件Mask
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_USERMASK_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_USERMASK_ADDR(base) ((base) + (0x2074))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_0_SRC_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_0_SRC_ADDR(base) ((base) + (0x2138))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_0_ALARMMODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_0_ALARMMODE_ADDR(base) ((base) + (0x213C))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_0_VAL_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_0_VAL_ADDR(base) ((base) + (0x2140))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_1_SRC_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_1_SRC_ADDR(base) ((base) + (0x214C))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_1_ALARMMODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_1_ALARMMODE_ADDR(base) ((base) + (0x2150))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_1_VAL_UNION */
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_1_VAL_ADDR(base) ((base) + (0x2154))



/****************************************************************************
                     (4/9) CFGBUS
 ****************************************************************************/
/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_ID_COREID_ADDR(base) ((base) + (0x0000))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0004))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_PRIORITY_UNION */
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_PRIORITY_ADDR(base) ((base) + (0x0008))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_MODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_MODE_ADDR(base) ((base) + (0x000C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_EXTCONTROL_UNION */
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0018))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_ID_COREID_ADDR(base) ((base) + (0x0080))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0084))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_PRIORITY_UNION */
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_PRIORITY_ADDR(base) ((base) + (0x0088))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_MODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_MODE_ADDR(base) ((base) + (0x008C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_EXTCONTROL_UNION */
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0098))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_ID_COREID_ADDR(base) ((base) + (0x0100))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0104))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_PRIORITY_UNION */
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_PRIORITY_ADDR(base) ((base) + (0x0108))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_MODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_MODE_ADDR(base) ((base) + (0x010C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_EXTCONTROL_UNION */
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0118))

/* 寄存器说明：CFG_BUS Err probe域ID
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_CFGBUS_ERR_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERR_ID_COREID_ADDR(base) ((base) + (0x1C00))

/* 寄存器说明：总线代码版本寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_CFGBUS_ERR_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERR_ID_REVISIONID_ADDR(base) ((base) + (0x1C04))

/* 寄存器说明：CFG_BUS Err probe使能
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_CFGBUS_FAULTEN_UNION */
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_FAULTEN_ADDR(base) ((base) + (0x1C08))

/* 寄存器说明：Error log有效指示寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRVLD_UNION */
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRVLD_ADDR(base)  ((base) + (0x1C0C))

/* 寄存器说明：中断清除寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRCLR_UNION */
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRCLR_ADDR(base)  ((base) + (0x1C10))

/* 寄存器说明：Error log0
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG0_UNION */
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG0_ADDR(base) ((base) + (0x1C14))

/* 寄存器说明：Error log1
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG1_UNION */
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG1_ADDR(base) ((base) + (0x1C18))

/* 寄存器说明：Error log3
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG3_UNION */
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG3_ADDR(base) ((base) + (0x1C20))

/* 寄存器说明：Error log5
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG5_UNION */
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG5_ADDR(base) ((base) + (0x1C28))

/* 寄存器说明：Error log7
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG7_UNION */
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG7_ADDR(base) ((base) + (0x1C30))



/****************************************************************************
                     (5/9) DMABUS
 ****************************************************************************/
/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_DMAC_QOS_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_ID_COREID_ADDR(base) ((base) + (0x0000))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_DMAC_QOS_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0004))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_DMAC_QOS_PRIORITY_UNION */
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_PRIORITY_ADDR(base) ((base) + (0x0008))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_DMAC_QOS_MODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_MODE_ADDR(base)  ((base) + (0x000C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_DMAC_QOS_EXTCONTROL_UNION */
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0018))

/* 寄存器说明：adapter域ID
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAPTER_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAPTER_ID_COREID_ADDR(base) ((base) + (0x1000))

/* 寄存器说明：总线代码版本寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAPTER_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAPTER_ID_REVISIONID_ADDR(base) ((base) + (0x1004))

/* 寄存器说明：Rate Adapter配置寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAPTERRATE_UNION */
#define SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAPTERRATE_ADDR(base) ((base) + (0x1008))

/* 寄存器说明：Rate Adapter bypass寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAP_BYPASS_UNION */
#define SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAP_BYPASS_ADDR(base) ((base) + (0x100C))

/* 寄存器说明：DMABUS Err probe域ID
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_DMABUS_ERR_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERR_ID_COREID_ADDR(base) ((base) + (0x1C00))

/* 寄存器说明：总线代码版本寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_DMABUS_ERR_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERR_ID_REVISIONID_ADDR(base) ((base) + (0x1C04))

/* 寄存器说明：DMABUS Err probe使能
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_DMABUS_FAULTEN_UNION */
#define SOC_CFG_SYS_NOC_BUS_DMABUS_FAULTEN_ADDR(base) ((base) + (0x1C08))

/* 寄存器说明：Error log有效指示寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_DMABUS_ERRVLD_UNION */
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRVLD_ADDR(base)  ((base) + (0x1C0C))

/* 寄存器说明：中断清除寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_DMABUS_ERRCLR_UNION */
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRCLR_ADDR(base)  ((base) + (0x1C10))

/* 寄存器说明：Error log0
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG0_UNION */
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG0_ADDR(base) ((base) + (0x1C14))

/* 寄存器说明：Error log1
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG1_UNION */
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG1_ADDR(base) ((base) + (0x1C18))

/* 寄存器说明：Error log3
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG3_UNION */
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG3_ADDR(base) ((base) + (0x1C20))

/* 寄存器说明：Error log5
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG5_UNION */
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG5_ADDR(base) ((base) + (0x1C28))

/* 寄存器说明：Error log7
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG7_UNION */
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG7_ADDR(base) ((base) + (0x1C30))



/****************************************************************************
                     (6/9) DBGBUS
 ****************************************************************************/
/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_USB3_QOS_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_ID_COREID_ADDR(base) ((base) + (0x0000))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_USB3_QOS_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0004))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_USB3_QOS_PRIORITY_UNION */
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_PRIORITY_ADDR(base) ((base) + (0x0008))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_USB3_QOS_MODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_MODE_ADDR(base)  ((base) + (0x000C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_USB3_QOS_BANDWIDTH_UNION */
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_BANDWIDTH_ADDR(base) ((base) + (0x0010))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_USB3_QOS_SATURATION_UNION */
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_SATURATION_ADDR(base) ((base) + (0x0014))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_USB3_QOS_EXTCONTROL_UNION */
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0018))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_ID_COREID_ADDR(base) ((base) + (0x0080))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0084))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_PRIORITY_UNION */
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_PRIORITY_ADDR(base) ((base) + (0x0088))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_MODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_MODE_ADDR(base) ((base) + (0x008C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_EXTCONTROL_UNION */
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0098))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_ID_COREID_ADDR(base) ((base) + (0x0100))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0104))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_PRIORITY_UNION */
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_PRIORITY_ADDR(base) ((base) + (0x0108))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_MODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_MODE_ADDR(base) ((base) + (0x010C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_EXTCONTROL_UNION */
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0118))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SOCP_QOS_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_ID_COREID_ADDR(base) ((base) + (0x0180))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SOCP_QOS_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0184))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SOCP_QOS_PRIORITY_UNION */
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_PRIORITY_ADDR(base) ((base) + (0x0188))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SOCP_QOS_MODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_MODE_ADDR(base)  ((base) + (0x018C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_SOCP_QOS_EXTCONTROL_UNION */
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0198))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_ID_COREID_ADDR(base) ((base) + (0x0200))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0204))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_PRIORITY_UNION */
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_PRIORITY_ADDR(base) ((base) + (0x0208))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_MODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_MODE_ADDR(base) ((base) + (0x020C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_EXTCONTROL_UNION */
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0218))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_ID_COREID_ADDR(base) ((base) + (0x0280))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0284))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_PRIORITY_UNION */
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_PRIORITY_ADDR(base) ((base) + (0x0288))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_MODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_MODE_ADDR(base) ((base) + (0x028C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_EXTCONTROL_UNION */
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0298))

/* 寄存器说明：adapter域ID
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAPTER_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAPTER_ID_COREID_ADDR(base) ((base) + (0x1000))

/* 寄存器说明：总线代码版本寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAPTER_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAPTER_ID_REVISIONID_ADDR(base) ((base) + (0x1004))

/* 寄存器说明：Rate Adapter配置寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAPTERRATE_UNION */
#define SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAPTERRATE_ADDR(base) ((base) + (0x1008))

/* 寄存器说明：Rate Adapter bypass寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAP_BYPASS_UNION */
#define SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAP_BYPASS_ADDR(base) ((base) + (0x100C))

/* 寄存器说明：DBGBUS Err probe域ID
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_DBGBUS_ERR_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERR_ID_COREID_ADDR(base) ((base) + (0x1C00))

/* 寄存器说明：总线代码版本寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_DBGBUS_ERR_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERR_ID_REVISIONID_ADDR(base) ((base) + (0x1C04))

/* 寄存器说明：DBGBUS Err probe使能
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_DBGBUS_FAULTEN_UNION */
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_FAULTEN_ADDR(base) ((base) + (0x1C08))

/* 寄存器说明：Error log有效指示寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRVLD_UNION */
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRVLD_ADDR(base)  ((base) + (0x1C0C))

/* 寄存器说明：中断清除寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRCLR_UNION */
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRCLR_ADDR(base)  ((base) + (0x1C10))

/* 寄存器说明：Error log0
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG0_UNION */
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG0_ADDR(base) ((base) + (0x1C14))

/* 寄存器说明：Error log1
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG1_UNION */
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG1_ADDR(base) ((base) + (0x1C18))

/* 寄存器说明：Error log3
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG3_UNION */
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG3_ADDR(base) ((base) + (0x1C20))

/* 寄存器说明：Error log5
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG5_UNION */
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG5_ADDR(base) ((base) + (0x1C28))

/* 寄存器说明：Error log7
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG7_UNION */
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG7_ADDR(base) ((base) + (0x1C30))



/****************************************************************************
                     (7/9) MMC1BUS
 ****************************************************************************/
/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_ID_COREID_ADDR(base) ((base) + (0x0080))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0084))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_PRIORITY_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_PRIORITY_ADDR(base) ((base) + (0x0088))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_MODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_MODE_ADDR(base) ((base) + (0x008C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_EXTCONTROL_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0098))

/* 寄存器说明：MMC1BUS Err probe域ID
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERR_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERR_ID_COREID_ADDR(base) ((base) + (0x1C00))

/* 寄存器说明：总线代码版本寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERR_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERR_ID_REVISIONID_ADDR(base) ((base) + (0x1C04))

/* 寄存器说明：MMC1BUS Err probe使能
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MMC1BUS_FAULTEN_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_FAULTEN_ADDR(base) ((base) + (0x1C08))

/* 寄存器说明：Error log有效指示寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRVLD_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRVLD_ADDR(base) ((base) + (0x1C0C))

/* 寄存器说明：中断清除寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRCLR_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRCLR_ADDR(base) ((base) + (0x1C10))

/* 寄存器说明：Error log0
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG0_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG0_ADDR(base) ((base) + (0x1C14))

/* 寄存器说明：Error log1
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG1_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG1_ADDR(base) ((base) + (0x1C18))

/* 寄存器说明：Error log3
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG3_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG3_ADDR(base) ((base) + (0x1C20))

/* 寄存器说明：Error log5
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG5_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG5_ADDR(base) ((base) + (0x1C28))

/* 寄存器说明：Error log7
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG7_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG7_ADDR(base) ((base) + (0x1C30))



/****************************************************************************
                     (8/9) MMC0BUS 
 ****************************************************************************/
/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_ID_COREID_ADDR(base) ((base) + (0x0000))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0004))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_PRIORITY_UNION */
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_PRIORITY_ADDR(base) ((base) + (0x0008))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_MODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_MODE_ADDR(base) ((base) + (0x000C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_EXTCONTROL_UNION */
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0018))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_ID_COREID_ADDR(base) ((base) + (0x0080))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0084))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_PRIORITY_UNION */
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_PRIORITY_ADDR(base) ((base) + (0x0088))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_MODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_MODE_ADDR(base) ((base) + (0x008C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_EXTCONTROL_UNION */
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0098))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_ID_COREID_ADDR(base) ((base) + (0x0100))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0104))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_PRIORITY_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_PRIORITY_ADDR(base) ((base) + (0x0108))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_MODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_MODE_ADDR(base) ((base) + (0x010C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_EXTCONTROL_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0118))

/* 寄存器说明：adapter域ID
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAPTER_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAPTER_ID_COREID_ADDR(base) ((base) + (0x1000))

/* 寄存器说明：总线代码版本寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAPTER_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAPTER_ID_REVISIONID_ADDR(base) ((base) + (0x1004))

/* 寄存器说明：Rate Adapter配置寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAPTERRATE_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAPTERRATE_ADDR(base) ((base) + (0x1008))

/* 寄存器说明：Rate Adapter bypass寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAP_BYPASS_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAP_BYPASS_ADDR(base) ((base) + (0x100C))

/* 寄存器说明：MMC0BUS Err probe域ID
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERR_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERR_ID_COREID_ADDR(base) ((base) + (0x1C00))

/* 寄存器说明：总线代码版本寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERR_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERR_ID_REVISIONID_ADDR(base) ((base) + (0x1C04))

/* 寄存器说明：MMC0BUS Err probe使能
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MMC0BUS_FAULTEN_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_FAULTEN_ADDR(base) ((base) + (0x1C08))

/* 寄存器说明：Error log有效指示寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRVLD_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRVLD_ADDR(base) ((base) + (0x1C0C))

/* 寄存器说明：中断清除寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRCLR_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRCLR_ADDR(base) ((base) + (0x1C10))

/* 寄存器说明：Error log0
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG0_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG0_ADDR(base) ((base) + (0x1C14))

/* 寄存器说明：Error log1
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG1_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG1_ADDR(base) ((base) + (0x1C18))

/* 寄存器说明：Error log3
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG3_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG3_ADDR(base) ((base) + (0x1C20))

/* 寄存器说明：Error log5
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG5_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG5_ADDR(base) ((base) + (0x1C28))

/* 寄存器说明：Error log7
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG7_UNION */
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG7_ADDR(base) ((base) + (0x1C30))



/****************************************************************************
                     (9/9) IVP32BUS
 ****************************************************************************/
/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_IVP32_QOS_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_ID_COREID_ADDR(base) ((base) + (0x0000))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_IVP32_QOS_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0004))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_IVP32_QOS_PRIORITY_UNION */
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_PRIORITY_ADDR(base) ((base) + (0x0008))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_IVP32_QOS_MODE_UNION */
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_MODE_ADDR(base) ((base) + (0x000C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_IVP32_QOS_EXTCONTROL_UNION */
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0018))

/* 寄存器说明：IVP32 Err probe域ID
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_IVP32_ERR_ID_COREID_UNION */
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERR_ID_COREID_ADDR(base) ((base) + (0x1C00))

/* 寄存器说明：总线代码版本寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_IVP32_ERR_ID_REVISIONID_UNION */
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERR_ID_REVISIONID_ADDR(base) ((base) + (0x1C04))

/* 寄存器说明：IVP32 Err probe使能
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_IVP32_FAULTEN_UNION */
#define SOC_CFG_SYS_NOC_BUS_IVP32_FAULTEN_ADDR(base)  ((base) + (0x1C08))

/* 寄存器说明：Error log有效指示寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_IVP32_ERRVLD_UNION */
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRVLD_ADDR(base)   ((base) + (0x1C0C))

/* 寄存器说明：中断清除寄存器
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_IVP32_ERRCLR_UNION */
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRCLR_ADDR(base)   ((base) + (0x1C10))

/* 寄存器说明：Error log0
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG0_UNION */
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG0_ADDR(base)  ((base) + (0x1C14))

/* 寄存器说明：Error log1
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG1_UNION */
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG1_ADDR(base)  ((base) + (0x1C18))

/* 寄存器说明：Error log3
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG3_UNION */
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG3_ADDR(base)  ((base) + (0x1C20))

/* 寄存器说明：Error log5
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG5_UNION */
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG5_ADDR(base)  ((base) + (0x1C28))

/* 寄存器说明：Error log7
   位域定义UNION结构:  SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG7_UNION */
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG7_ADDR(base)  ((base) + (0x1C30))





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
                     (1/9) MODEMBUS
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM_QOS_ID_COREID_UNION
 结构说明  : MODEM_QOS_ID_COREID 寄存器结构定义。地址偏移量:0x0000，初值:0x1B101004，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MODEM_QOS_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_ID_COREID_coretypeid_START    (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_ID_COREID_coretypeid_END      (7)
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_ID_COREID_corechecksum_START  (8)
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM_QOS_ID_REVISIONID_UNION
 结构说明  : MODEM_QOS_ID_REVISIONID 寄存器结构定义。地址偏移量:0x0004，初值:0x012D5300，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MODEM_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_ID_REVISIONID_userid_START     (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_ID_REVISIONID_userid_END       (7)
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_ID_REVISIONID_flexnocid_START  (8)
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM_QOS_PRIORITY_UNION
 结构说明  : MODEM_QOS_PRIORITY 寄存器结构定义。地址偏移量:0x0008，初值:0x80000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MODEM_QOS_PRIORITY_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_PRIORITY_p0_START        (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_PRIORITY_p0_END          (1)
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_PRIORITY_p1_START        (8)
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_PRIORITY_p1_END          (9)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM_QOS_MODE_UNION
 结构说明  : MODEM_QOS_MODE 寄存器结构定义。地址偏移量:0x000C，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MODEM_QOS_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_MODE_mode_START      (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_MODE_mode_END        (1)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM_QOS_EXTCONTROL_UNION
 结构说明  : MODEM_QOS_EXTCONTROL 寄存器结构定义。地址偏移量:0x0018，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MODEM_QOS_EXTCONTROL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_EXTCONTROL_socketqosen_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_EXTCONTROL_socketqosen_END    (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_EXTCONTROL_extthren_START     (1)
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_EXTCONTROL_extthren_END       (1)
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_EXTCONTROL_intclken_START     (2)
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_EXTCONTROL_intclken_END       (2)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERR_ID_COREID_UNION
 结构说明  : MODEMBUS_ERR_ID_COREID 寄存器结构定义。地址偏移量:0x1C00，初值:0x08DA560D，宽度:32
 寄存器说明: MODEMBUS Err probe域ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_coreid : 32; /* bit[0-31]: error probe的域ID。 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERR_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERR_ID_COREID_id_coreid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERR_ID_COREID_id_coreid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERR_ID_REVISIONID_UNION
 结构说明  : MODEMBUS_ERR_ID_REVISIONID 寄存器结构定义。地址偏移量:0x1C04，初值:0x012D5300，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERR_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERR_ID_REVISIONID_id_revisionid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERR_ID_REVISIONID_id_revisionid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEMBUS_FAULTEN_UNION
 结构说明  : MODEMBUS_FAULTEN 寄存器结构定义。地址偏移量:0x1C08，初值:0x00000000，宽度:32
 寄存器说明: MODEMBUS Err probe使能
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
} SOC_CFG_SYS_NOC_BUS_MODEMBUS_FAULTEN_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_FAULTEN_faulten_START   (0)
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_FAULTEN_faulten_END     (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRVLD_UNION
 结构说明  : MODEMBUS_ERRVLD 寄存器结构定义。地址偏移量:0x1C0C，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRVLD_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRVLD_errvld_START    (0)
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRVLD_errvld_END      (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRCLR_UNION
 结构说明  : MODEMBUS_ERRCLR 寄存器结构定义。地址偏移量:0x1C10，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRCLR_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRCLR_errclr_START    (0)
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRCLR_errclr_END      (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG0_UNION
 结构说明  : MODEMBUS_ERRLOG0 寄存器结构定义。地址偏移量:0x1C14，初值:0x80000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG0_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG0_lock_START      (0)
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG0_lock_END        (0)
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG0_opc_START       (1)
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG0_opc_END         (4)
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG0_errcode_START   (8)
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG0_errcode_END     (10)
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG0_len1_START      (16)
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG0_len1_END        (23)
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG0_format_START    (31)
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG0_format_END      (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG1_UNION
 结构说明  : MODEMBUS_ERRLOG1 寄存器结构定义。地址偏移量:0x1C18，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG1_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG1_errlog1_START   (0)
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG1_errlog1_END     (13)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG3_UNION
 结构说明  : MODEMBUS_ERRLOG3 寄存器结构定义。地址偏移量:0x1C20，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG3_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG3_errlog3_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG3_errlog3_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG5_UNION
 结构说明  : MODEMBUS_ERRLOG5 寄存器结构定义。地址偏移量:0x1C28，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG5_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG5_errlog5_START   (0)
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG5_errlog5_END     (4)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG7_UNION
 结构说明  : MODEMBUS_ERRLOG7 寄存器结构定义。地址偏移量:0x1C30，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG7_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG7_errlog7_START   (0)
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG7_errlog7_END     (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ID_COREID_UNION
 结构说明  : MODEM_TRANS_F_ID_COREID 寄存器结构定义。地址偏移量:0x8000，初值:0x0B84FC09，宽度:32
 寄存器说明: MODEM TransactionStatFilter域ID
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
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ID_COREID_coretypeid_START    (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ID_COREID_coretypeid_END      (7)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ID_COREID_corechecksum_START  (8)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ID_REVISIONID_UNION
 结构说明  : MODEM_TRANS_F_ID_REVISIONID 寄存器结构定义。地址偏移量:0x8004，初值:0x012D5300，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ID_REVISIONID_userid_START     (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ID_REVISIONID_userid_END       (7)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ID_REVISIONID_flexnocid_START  (8)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_MODE_UNION
 结构说明  : MODEM_TRANS_F_MODE 寄存器结构定义。地址偏移量:0x8008，初值:0x00000000，宽度:32
 寄存器说明: MODEM Transaction Probe的Filter工作模式配置寄存器
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
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_MODE_mode_START      (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_MODE_mode_END        (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ADDRBASE_LOW_UNION
 结构说明  : MODEM_TRANS_F_ADDRBASE_LOW 寄存器结构定义。地址偏移量:0x800C，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ADDRBASE_LOW_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ADDRBASE_LOW_addrbase_low_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ADDRBASE_LOW_addrbase_low_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ADDRWINDOWSIZE_UNION
 结构说明  : MODEM_TRANS_F_ADDRWINDOWSIZE 寄存器结构定义。地址偏移量:0x8014，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ADDRWINDOWSIZE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ADDRWINDOWSIZE_addrwindowsize_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ADDRWINDOWSIZE_addrwindowsize_END    (5)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_OPCODE_UNION
 结构说明  : MODEM_TRANS_F_OPCODE 寄存器结构定义。地址偏移量:0x8020，初值:0x00000000，宽度:32
 寄存器说明: MODEM的Transaction Probe的Opcode过滤条件
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
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_OPCODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_OPCODE_rden_START      (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_OPCODE_rden_END        (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_OPCODE_wren_START      (1)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_OPCODE_wren_END        (1)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_USERBASE_UNION
 结构说明  : MODEM_TRANS_F_USERBASE 寄存器结构定义。地址偏移量:0x8024，初值:0x00000000，宽度:32
 寄存器说明: MODEM的Transaction Probe的User过滤条件
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  userbase : 12; /* bit[0-11] : User信号过滤条件 */
        unsigned int  reserved : 20; /* bit[12-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_USERBASE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_USERBASE_userbase_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_USERBASE_userbase_END    (11)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_USERMASK_UNION
 结构说明  : MODEM_TRANS_F_USERMASK 寄存器结构定义。地址偏移量:0x8028，初值:0x00000000，宽度:32
 寄存器说明: MODEM的Transaction Probe的User过滤条件Mask
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  usermask : 12; /* bit[0-11] : 对UserBase进行Mask，选择UserBase中的任意几bit User信号作为过滤条件。
                                                    过滤条件：packet.User & UserMask = UserBase & UserMask。 */
        unsigned int  reserved : 20; /* bit[12-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_USERMASK_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_USERMASK_usermask_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_USERMASK_usermask_END    (11)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_SECURITYBASE_UNION
 结构说明  : MODEM_TRANS_F_SECURITYBASE 寄存器结构定义。地址偏移量:0x802C，初值:0x00000000，宽度:32
 寄存器说明: MODEM的Transaction Probe的安全过滤条件
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
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_SECURITYBASE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_SECURITYBASE_securitybase_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_SECURITYBASE_securitybase_END    (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_SECURITYMASK_UNION
 结构说明  : MODEM_TRANS_F_SECURITYMASK 寄存器结构定义。地址偏移量:0x8030，初值:0x00000000，宽度:32
 寄存器说明: MODEM的Transaction Probe的安全过滤条件Mask
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
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_SECURITYMASK_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_SECURITYMASK_securitymask_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_SECURITYMASK_securitymask_END    (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_ID_COREID_UNION
 结构说明  : MODEM_TRANS_P_ID_COREID 寄存器结构定义。地址偏移量:0x8080，初值:0xC59E110A，宽度:32
 寄存器说明: MODEM TransactionStatProfilter域ID
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
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_ID_COREID_coretypeid_START    (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_ID_COREID_coretypeid_END      (7)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_ID_COREID_corechecksum_START  (8)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_ID_REVISIONID_UNION
 结构说明  : MODEM_TRANS_P_ID_REVISIONID 寄存器结构定义。地址偏移量:0x8084，初值:0x012D5300，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_ID_REVISIONID_userid_START     (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_ID_REVISIONID_userid_END       (7)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_ID_REVISIONID_flexnocid_START  (8)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_EN_UNION
 结构说明  : MODEM_TRANS_P_EN 寄存器结构定义。地址偏移量:0x8088，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_EN_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_EN_en_START        (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_EN_en_END          (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_MODE_UNION
 结构说明  : MODEM_TRANS_P_MODE 寄存器结构定义。地址偏移量:0x808C，初值:0x00000000，宽度:32
 寄存器说明: MODEM Transaction Probe的工作模式配置
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
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_MODE_mode_START      (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_MODE_mode_END        (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_THRESHOLDS_0_0_UNION
 结构说明  : MODEM_TRANS_P_THRESHOLDS_0_0 寄存器结构定义。地址偏移量:0x80AC，初值:0x00000000，宽度:32
 寄存器说明: MODEM Transaction Probe的bin_0配置
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
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_THRESHOLDS_0_0_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_THRESHOLDS_0_0_thresholds_0_0_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_THRESHOLDS_0_0_thresholds_0_0_END    (1)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_THRESHOLDS_0_1_UNION
 结构说明  : MODEM_TRANS_P_THRESHOLDS_0_1 寄存器结构定义。地址偏移量:0x80B0，初值:0x00000000，宽度:32
 寄存器说明: MODEM Transaction Probe的bin_0配置
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
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_THRESHOLDS_0_1_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_THRESHOLDS_0_1_thresholds_0_1_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_THRESHOLDS_0_1_thresholds_0_1_END    (1)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_OVERFLOWSTATUS_UNION
 结构说明  : MODEM_TRANS_P_OVERFLOWSTATUS 寄存器结构定义。地址偏移量:0x80EC，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_OVERFLOWSTATUS_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_OVERFLOWSTATUS_overflowstatus_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_OVERFLOWSTATUS_overflowstatus_END    (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_OVERFLOWRESET_UNION
 结构说明  : MODEM_TRANS_P_OVERFLOWRESET 寄存器结构定义。地址偏移量:0x80F0，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_OVERFLOWRESET_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_OVERFLOWRESET_overflowreset_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_OVERFLOWRESET_overflowreset_END    (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_PENDINGEVENTMODE_UNION
 结构说明  : MODEM_TRANS_P_PENDINGEVENTMODE 寄存器结构定义。地址偏移量:0x80F4，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_PENDINGEVENTMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_PENDINGEVENTMODE_pendingeventmode_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_PENDINGEVENTMODE_pendingeventmode_END    (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_PRESCALER_UNION
 结构说明  : MODEM_TRANS_P_PRESCALER 寄存器结构定义。地址偏移量:0x80F8，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_PRESCALER_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_PRESCALER_prescaler_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_PRESCALER_prescaler_END    (7)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_ID_COREID_UNION
 结构说明  : MODEM_TRANS_M_ID_COREID 寄存器结构定义。地址偏移量:0x8400，初值:0xCA501B06，宽度:32
 寄存器说明: MODEM Transaction probe域ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_coreid : 32; /* bit[0-31]: VcodecBus的Packet Probe的域ID。 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_ID_COREID_id_coreid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_ID_COREID_id_coreid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_ID_REVISIONID_UNION
 结构说明  : MODEM_TRANS_M_ID_REVISIONID 寄存器结构定义。地址偏移量:0x8404，初值:0x012D5300，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_ID_REVISIONID_id_revisionid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_ID_REVISIONID_id_revisionid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_MAINCTL_UNION
 结构说明  : MODEM_TRANS_M_MAINCTL 寄存器结构定义。地址偏移量:0x8408，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_MAINCTL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_MAINCTL_erren_START                      (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_MAINCTL_erren_END                        (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_MAINCTL_traceen_START                    (1)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_MAINCTL_traceen_END                      (1)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_MAINCTL_payloaden_START                  (2)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_MAINCTL_payloaden_END                    (2)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_MAINCTL_staten_START                     (3)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_MAINCTL_staten_END                       (3)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_MAINCTL_alarmen_START                    (4)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_MAINCTL_alarmen_END                      (4)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_MAINCTL_statconddump_START               (5)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_MAINCTL_statconddump_END                 (5)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_MAINCTL_intrusivemode_START              (6)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_MAINCTL_intrusivemode_END                (6)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_MAINCTL_filtbytealwayschainableen_START  (7)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_MAINCTL_filtbytealwayschainableen_END    (7)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_CFGCTL_UNION
 结构说明  : MODEM_TRANS_M_CFGCTL 寄存器结构定义。地址偏移量:0x840C，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_CFGCTL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_CFGCTL_globalen_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_CFGCTL_globalen_END    (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_CFGCTL_active_START    (1)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_CFGCTL_active_END      (1)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATPERIOD_UNION
 结构说明  : MODEM_TRANS_M_STATPERIOD 寄存器结构定义。地址偏移量:0x8424，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATPERIOD_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATPERIOD_statperiod_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATPERIOD_statperiod_END    (4)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATGO_UNION
 结构说明  : MODEM_TRANS_M_STATGO 寄存器结构定义。地址偏移量:0x8428，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATGO_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATGO_statgo_START    (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATGO_statgo_END      (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMMIN_UNION
 结构说明  : MODEM_TRANS_M_STATALARMMIN 寄存器结构定义。地址偏移量:0x842C，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMMIN_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMMIN_statalarmmin_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMMIN_statalarmmin_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMMAX_UNION
 结构说明  : MODEM_TRANS_M_STATALARMMAX 寄存器结构定义。地址偏移量:0x8430，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMMAX_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMMAX_statalarmmax_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMMAX_statalarmmax_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMSTATUS_UNION
 结构说明  : MODEM_TRANS_M_STATALARMSTATUS 寄存器结构定义。地址偏移量:0x8434，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMSTATUS_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMSTATUS_statalarmstatus_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMSTATUS_statalarmstatus_END    (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMCLR_UNION
 结构说明  : MODEM_TRANS_M_STATALARMCLR 寄存器结构定义。地址偏移量:0x8438，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMCLR_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMCLR_statalarmclr_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMCLR_statalarmclr_END    (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_0_SRC_UNION
 结构说明  : MODEM_TRANS_M_COUNTERS_0_SRC 寄存器结构定义。地址偏移量:0x8538，初值:0x00000000，宽度:32
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
                                                         0x20-->Bin 0（delay：0~31；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：32~63；outstanding：2~3）；
                                                         0x22-->Bin 2（delay：64~127；outstanding：4~5）；
                                                         0x23-->Bin 3（delay：128~255；outstanding：8~9）；
                                                         0x24-->Bin 4（delay：>= 256；outstanding：>= 10）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_0_SRC_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_0_SRC_counters_0_src_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_0_SRC_counters_0_src_END    (5)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_0_ALARMMODE_UNION
 结构说明  : MODEM_TRANS_M_COUNTERS_0_ALARMMODE 寄存器结构定义。地址偏移量:0x853C，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_0_ALARMMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_0_ALARMMODE_counters_0_alarmmode_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_0_ALARMMODE_counters_0_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_0_VAL_UNION
 结构说明  : MODEM_TRANS_M_COUNTERS_0_VAL 寄存器结构定义。地址偏移量:0x8540，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_0_val : 12; /* bit[0-11] : 当Counters_0_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 20; /* bit[12-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_0_VAL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_0_VAL_counters_0_val_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_0_VAL_counters_0_val_END    (11)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_1_SRC_UNION
 结构说明  : MODEM_TRANS_M_COUNTERS_1_SRC 寄存器结构定义。地址偏移量:0x854C，初值:0x00000000，宽度:32
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
                                                         0x20-->Bin 0（delay：0~31；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：32~63；outstanding：2~3）；
                                                         0x22-->Bin 2（delay：64~127；outstanding：4~5）；
                                                         0x23-->Bin 3（delay：128~255；outstanding：8~9）；
                                                         0x24-->Bin 4（delay：>= 256；outstanding：>= 10）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_1_SRC_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_1_SRC_counters_1_src_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_1_SRC_counters_1_src_END    (5)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_1_ALARMMODE_UNION
 结构说明  : MODEM_TRANS_M_COUNTERS_1_ALARMMODE 寄存器结构定义。地址偏移量:0x8550，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_1_ALARMMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_1_ALARMMODE_counters_1_alarmmode_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_1_ALARMMODE_counters_1_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_1_VAL_UNION
 结构说明  : MODEM_TRANS_M_COUNTERS_1_VAL 寄存器结构定义。地址偏移量:0x8554，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_1_val : 12; /* bit[0-11] : 当Counters_1_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 20; /* bit[12-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_1_VAL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_1_VAL_counters_1_val_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_1_VAL_counters_1_val_END    (11)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_2_SRC_UNION
 结构说明  : MODEM_TRANS_M_COUNTERS_2_SRC 寄存器结构定义。地址偏移量:0x8560，初值:0x00000000，宽度:32
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
                                                         0x20-->Bin 0（delay：0~31；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：32~63；outstanding：2~3）；
                                                         0x22-->Bin 2（delay：64~127；outstanding：4~5）；
                                                         0x23-->Bin 3（delay：128~255；outstanding：8~9）；
                                                         0x24-->Bin 4（delay：>= 256；outstanding：>= 10）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_2_SRC_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_2_SRC_counters_2_src_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_2_SRC_counters_2_src_END    (5)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_2_ALARMMODE_UNION
 结构说明  : MODEM_TRANS_M_COUNTERS_2_ALARMMODE 寄存器结构定义。地址偏移量:0x8564，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_2_ALARMMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_2_ALARMMODE_counters_2_alarmmode_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_2_ALARMMODE_counters_2_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_2_VAL_UNION
 结构说明  : MODEM_TRANS_M_COUNTERS_2_VAL 寄存器结构定义。地址偏移量:0x8568，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_2_val : 12; /* bit[0-11] : 当Counters_2_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 20; /* bit[12-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_2_VAL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_2_VAL_counters_2_val_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_2_VAL_counters_2_val_END    (11)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_3_SRC_UNION
 结构说明  : MODEM_TRANS_M_COUNTERS_3_SRC 寄存器结构定义。地址偏移量:0x8574，初值:0x00000000，宽度:32
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
                                                         0x20-->Bin 0（delay：0~31；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：32~63；outstanding：2~3）；
                                                         0x22-->Bin 2（delay：64~127；outstanding：4~5）；
                                                         0x23-->Bin 3（delay：128~255；outstanding：8~9）；
                                                         0x24-->Bin 4（delay：>= 256；outstanding：>= 10）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_3_SRC_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_3_SRC_counters_3_src_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_3_SRC_counters_3_src_END    (5)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_3_ALARMMODE_UNION
 结构说明  : MODEM_TRANS_M_COUNTERS_3_ALARMMODE 寄存器结构定义。地址偏移量:0x8578，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_3_ALARMMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_3_ALARMMODE_counters_3_alarmmode_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_3_ALARMMODE_counters_3_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_3_VAL_UNION
 结构说明  : MODEM_TRANS_M_COUNTERS_3_VAL 寄存器结构定义。地址偏移量:0x857C，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_3_val : 12; /* bit[0-11] : 当Counters_3_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 20; /* bit[12-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_3_VAL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_3_VAL_counters_3_val_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_3_VAL_counters_3_val_END    (11)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_4_SRC_UNION
 结构说明  : MODEM_TRANS_M_COUNTERS_4_SRC 寄存器结构定义。地址偏移量:0x8588，初值:0x00000000，宽度:32
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
                                                         0x20-->Bin 0（delay：0~31；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：32~63；outstanding：2~3）；
                                                         0x22-->Bin 2（delay：64~127；outstanding：4~5）；
                                                         0x23-->Bin 3（delay：128~255；outstanding：8~9）；
                                                         0x24-->Bin 4（delay：>= 256；outstanding：>= 10）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_4_SRC_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_4_SRC_counters_4_src_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_4_SRC_counters_4_src_END    (5)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_4_ALARMMODE_UNION
 结构说明  : MODEM_TRANS_M_COUNTERS_4_ALARMMODE 寄存器结构定义。地址偏移量:0x858C，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_4_ALARMMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_4_ALARMMODE_counters_4_alarmmode_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_4_ALARMMODE_counters_4_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_4_VAL_UNION
 结构说明  : MODEM_TRANS_M_COUNTERS_4_VAL 寄存器结构定义。地址偏移量:0x8590，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_4_val : 12; /* bit[0-11] : 当Counters_4_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 20; /* bit[12-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_4_VAL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_4_VAL_counters_4_val_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_4_VAL_counters_4_val_END    (11)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_5_SRC_UNION
 结构说明  : MODEM_TRANS_M_COUNTERS_5_SRC 寄存器结构定义。地址偏移量:0x859C，初值:0x00000000，宽度:32
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
                                                         0x20-->Bin 0（delay：0~31；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：32~63；outstanding：2~3）；
                                                         0x22-->Bin 2（delay：64~127；outstanding：4~5）；
                                                         0x23-->Bin 3（delay：128~255；outstanding：8~9）；
                                                         0x24-->Bin 4（delay：>= 256；outstanding：>= 10）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_5_SRC_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_5_SRC_counters_5_src_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_5_SRC_counters_5_src_END    (5)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_5_ALARMMODE_UNION
 结构说明  : MODEM_TRANS_M_COUNTERS_5_ALARMMODE 寄存器结构定义。地址偏移量:0x85A0，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_5_ALARMMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_5_ALARMMODE_counters_5_alarmmode_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_5_ALARMMODE_counters_5_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_5_VAL_UNION
 结构说明  : MODEM_TRANS_M_COUNTERS_5_VAL 寄存器结构定义。地址偏移量:0x85A4，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_5_val : 12; /* bit[0-11] : 当Counters_5_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 20; /* bit[12-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_5_VAL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_5_VAL_counters_5_val_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_5_VAL_counters_5_val_END    (11)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_6_SRC_UNION
 结构说明  : MODEM_TRANS_M_COUNTERS_6_SRC 寄存器结构定义。地址偏移量:0x85B0，初值:0x00000000，宽度:32
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
                                                         0x20-->Bin 0（delay：0~31；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：32~63；outstanding：2~3）；
                                                         0x22-->Bin 2（delay：64~127；outstanding：4~5）；
                                                         0x23-->Bin 3（delay：128~255；outstanding：8~9）；
                                                         0x24-->Bin 4（delay：>= 256；outstanding：>= 10）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_6_SRC_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_6_SRC_counters_6_src_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_6_SRC_counters_6_src_END    (5)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_6_ALARMMODE_UNION
 结构说明  : MODEM_TRANS_M_COUNTERS_6_ALARMMODE 寄存器结构定义。地址偏移量:0x85B4，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_6_ALARMMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_6_ALARMMODE_counters_6_alarmmode_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_6_ALARMMODE_counters_6_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_6_VAL_UNION
 结构说明  : MODEM_TRANS_M_COUNTERS_6_VAL 寄存器结构定义。地址偏移量:0x85B8，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_6_val : 12; /* bit[0-11] : 当Counters_6_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 20; /* bit[12-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_6_VAL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_6_VAL_counters_6_val_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_6_VAL_counters_6_val_END    (11)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_7_SRC_UNION
 结构说明  : MODEM_TRANS_M_COUNTERS_7_SRC 寄存器结构定义。地址偏移量:0x85C4，初值:0x00000000，宽度:32
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
                                                         0x20-->Bin 0（delay：0~31；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：32~63；outstanding：2~3）；
                                                         0x22-->Bin 2（delay：64~127；outstanding：4~5）；
                                                         0x23-->Bin 3（delay：128~255；outstanding：8~9）；
                                                         0x24-->Bin 4（delay：>= 256；outstanding：>= 10）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_7_SRC_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_7_SRC_counters_7_src_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_7_SRC_counters_7_src_END    (5)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_7_ALARMMODE_UNION
 结构说明  : MODEM_TRANS_M_COUNTERS_7_ALARMMODE 寄存器结构定义。地址偏移量:0x85C8，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_7_ALARMMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_7_ALARMMODE_counters_7_alarmmode_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_7_ALARMMODE_counters_7_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_7_VAL_UNION
 结构说明  : MODEM_TRANS_M_COUNTERS_7_VAL 寄存器结构定义。地址偏移量:0x85CC，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_7_val : 12; /* bit[0-11] : 当Counters_7_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 20; /* bit[12-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_7_VAL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_7_VAL_counters_7_val_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_7_VAL_counters_7_val_END    (11)




/****************************************************************************
                     (2/9) ASPBUS
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_QOS_ID_COREID_UNION
 结构说明  : ASP_QOS_ID_COREID 寄存器结构定义。地址偏移量:0x0000，初值:0xC364FF04，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_ASP_QOS_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_ID_COREID_coretypeid_START    (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_ID_COREID_coretypeid_END      (7)
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_ID_COREID_corechecksum_START  (8)
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_QOS_ID_REVISIONID_UNION
 结构说明  : ASP_QOS_ID_REVISIONID 寄存器结构定义。地址偏移量:0x0004，初值:0x012D5300，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_ASP_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_ID_REVISIONID_userid_START     (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_ID_REVISIONID_userid_END       (7)
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_ID_REVISIONID_flexnocid_START  (8)
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_QOS_PRIORITY_UNION
 结构说明  : ASP_QOS_PRIORITY 寄存器结构定义。地址偏移量:0x0008，初值:0x80000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_ASP_QOS_PRIORITY_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_PRIORITY_p0_START        (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_PRIORITY_p0_END          (1)
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_PRIORITY_p1_START        (8)
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_PRIORITY_p1_END          (9)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_QOS_MODE_UNION
 结构说明  : ASP_QOS_MODE 寄存器结构定义。地址偏移量:0x000C，初值:0x00000002，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_ASP_QOS_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_MODE_mode_START      (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_MODE_mode_END        (1)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_QOS_BANDWIDTH_UNION
 结构说明  : ASP_QOS_BANDWIDTH 寄存器结构定义。地址偏移量:0x0010，初值:0x00000800，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bandwidth : 12; /* bit[0-11] : Defines the bandwidth threshold in 1/256th-byte-per-cycle units. In other words, the desired rate in MBps is divided by frequency in MHz of the NIU, and then multiplied by 256. */
        unsigned int  reserved  : 20; /* bit[12-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_QOS_BANDWIDTH_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_BANDWIDTH_bandwidth_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_BANDWIDTH_bandwidth_END    (11)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_QOS_SATURATION_UNION
 结构说明  : ASP_QOS_SATURATION 寄存器结构定义。地址偏移量:0x0014，初值:0x000003E8，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_ASP_QOS_SATURATION_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_SATURATION_saturation_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_SATURATION_saturation_END    (9)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_QOS_EXTCONTROL_UNION
 结构说明  : ASP_QOS_EXTCONTROL 寄存器结构定义。地址偏移量:0x0018，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_ASP_QOS_EXTCONTROL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_EXTCONTROL_socketqosen_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_EXTCONTROL_socketqosen_END    (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_EXTCONTROL_extthren_START     (1)
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_EXTCONTROL_extthren_END       (1)
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_EXTCONTROL_intclken_START     (2)
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_EXTCONTROL_intclken_END       (2)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ID_COREID_UNION
 结构说明  : ASP_TRANS_F_ID_COREID 寄存器结构定义。地址偏移量:0x8000，初值:0x4104DC09，宽度:32
 寄存器说明: ASP TransactionStatFilter域ID
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
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ID_COREID_coretypeid_START    (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ID_COREID_coretypeid_END      (7)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ID_COREID_corechecksum_START  (8)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ID_REVISIONID_UNION
 结构说明  : ASP_TRANS_F_ID_REVISIONID 寄存器结构定义。地址偏移量:0x8004，初值:0x012D5300，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ID_REVISIONID_userid_START     (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ID_REVISIONID_userid_END       (7)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ID_REVISIONID_flexnocid_START  (8)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_MODE_UNION
 结构说明  : ASP_TRANS_F_MODE 寄存器结构定义。地址偏移量:0x8008，初值:0x00000000，宽度:32
 寄存器说明: ASP Transaction Probe的Filter工作模式配置寄存器
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
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_MODE_mode_START      (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_MODE_mode_END        (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ADDRBASE_LOW_UNION
 结构说明  : ASP_TRANS_F_ADDRBASE_LOW 寄存器结构定义。地址偏移量:0x800C，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ADDRBASE_LOW_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ADDRBASE_LOW_addrbase_low_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ADDRBASE_LOW_addrbase_low_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ADDRWINDOWSIZE_UNION
 结构说明  : ASP_TRANS_F_ADDRWINDOWSIZE 寄存器结构定义。地址偏移量:0x8014，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ADDRWINDOWSIZE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ADDRWINDOWSIZE_addrwindowsize_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ADDRWINDOWSIZE_addrwindowsize_END    (5)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_OPCODE_UNION
 结构说明  : ASP_TRANS_F_OPCODE 寄存器结构定义。地址偏移量:0x8020，初值:0x00000000，宽度:32
 寄存器说明: ASP的Transaction Probe的Opcode过滤条件
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
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_OPCODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_OPCODE_rden_START      (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_OPCODE_rden_END        (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_OPCODE_wren_START      (1)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_OPCODE_wren_END        (1)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_USERBASE_UNION
 结构说明  : ASP_TRANS_F_USERBASE 寄存器结构定义。地址偏移量:0x8024，初值:0x00000000，宽度:32
 寄存器说明: ASP的Transaction Probe的User过滤条件
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  userbase : 12; /* bit[0-11] : User信号过滤条件 */
        unsigned int  reserved : 20; /* bit[12-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_USERBASE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_USERBASE_userbase_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_USERBASE_userbase_END    (11)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_USERMASK_UNION
 结构说明  : ASP_TRANS_F_USERMASK 寄存器结构定义。地址偏移量:0x8028，初值:0x00000000，宽度:32
 寄存器说明: ASP的Transaction Probe的User过滤条件Mask
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  usermask : 12; /* bit[0-11] : 对UserBase进行Mask，选择UserBase中的任意几bit User信号作为过滤条件。
                                                    过滤条件：packet.User & UserMask = UserBase & UserMask。 */
        unsigned int  reserved : 20; /* bit[12-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_USERMASK_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_USERMASK_usermask_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_USERMASK_usermask_END    (11)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_SECURITYBASE_UNION
 结构说明  : ASP_TRANS_F_SECURITYBASE 寄存器结构定义。地址偏移量:0x802C，初值:0x00000000，宽度:32
 寄存器说明: ASP的Transaction Probe的安全过滤条件
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
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_SECURITYBASE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_SECURITYBASE_securitybase_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_SECURITYBASE_securitybase_END    (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_SECURITYMASK_UNION
 结构说明  : ASP_TRANS_F_SECURITYMASK 寄存器结构定义。地址偏移量:0x8030，初值:0x00000000，宽度:32
 寄存器说明: ASP的Transaction Probe的安全过滤条件Mask
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
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_SECURITYMASK_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_SECURITYMASK_securitymask_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_SECURITYMASK_securitymask_END    (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_ID_COREID_UNION
 结构说明  : ASP_TRANS_P_ID_COREID 寄存器结构定义。地址偏移量:0x8080，初值:0x230D050A，宽度:32
 寄存器说明: ASP TransactionStatProfilter域ID
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
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_ID_COREID_coretypeid_START    (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_ID_COREID_coretypeid_END      (7)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_ID_COREID_corechecksum_START  (8)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_ID_REVISIONID_UNION
 结构说明  : ASP_TRANS_P_ID_REVISIONID 寄存器结构定义。地址偏移量:0x8084，初值:0x012D5300，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_ID_REVISIONID_userid_START     (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_ID_REVISIONID_userid_END       (7)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_ID_REVISIONID_flexnocid_START  (8)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_EN_UNION
 结构说明  : ASP_TRANS_P_EN 寄存器结构定义。地址偏移量:0x8088，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_EN_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_EN_en_START        (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_EN_en_END          (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_MODE_UNION
 结构说明  : ASP_TRANS_P_MODE 寄存器结构定义。地址偏移量:0x808C，初值:0x00000000，宽度:32
 寄存器说明: ASP Transaction Probe的工作模式配置
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
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_MODE_mode_START      (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_MODE_mode_END        (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_0_UNION
 结构说明  : ASP_TRANS_P_THRESHOLDS_0_0 寄存器结构定义。地址偏移量:0x80AC，初值:0x00000000，宽度:32
 寄存器说明: ASP Transaction Probe的bin_0配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  thresholds_0_0 : 2;  /* bit[0-1] : 0x0-->选择threshold_0（delay：32；outstanding：2）；
                                                         0x1-->选择threshold_1（delay：64；outstanding：4）；
                                                         0x2-->选择threshold_2（delay：128；outstanding：6）；
                                                         0x3-->选择threshold_3（delay：256；outstanding：10）； */
        unsigned int  reserved       : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_0_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_0_thresholds_0_0_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_0_thresholds_0_0_END    (1)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_1_UNION
 结构说明  : ASP_TRANS_P_THRESHOLDS_0_1 寄存器结构定义。地址偏移量:0x80B0，初值:0x00000000，宽度:32
 寄存器说明: ASP Transaction Probe的bin_1配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  thresholds_0_1 : 2;  /* bit[0-1] : 0x0-->选择threshold_0（delay：32；outstanding：2）；
                                                         0x1-->选择threshold_1（delay：64；outstanding：4）；
                                                         0x2-->选择threshold_2（delay：128；outstanding：6）；
                                                         0x3-->选择threshold_3（delay：256；outstanding：10）； */
        unsigned int  reserved       : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_1_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_1_thresholds_0_1_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_1_thresholds_0_1_END    (1)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_2_UNION
 结构说明  : ASP_TRANS_P_THRESHOLDS_0_2 寄存器结构定义。地址偏移量:0x80B4，初值:0x00000000，宽度:32
 寄存器说明: ASP Transaction Probe的bin_1配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  thresholds_0_2 : 2;  /* bit[0-1] : 0x0-->选择threshold_0（delay：32；outstanding：2）；
                                                         0x1-->选择threshold_1（delay：64；outstanding：4）；
                                                         0x2-->选择threshold_2（delay：128；outstanding：6）；
                                                         0x3-->选择threshold_3（delay：256；outstanding：10）； */
        unsigned int  reserved       : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_2_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_2_thresholds_0_2_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_2_thresholds_0_2_END    (1)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_3_UNION
 结构说明  : ASP_TRANS_P_THRESHOLDS_0_3 寄存器结构定义。地址偏移量:0x80B8，初值:0x00000000，宽度:32
 寄存器说明: ASP Transaction Probe的bin_1配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  thresholds_0_3 : 2;  /* bit[0-1] : 0x0-->选择threshold_0（delay：32；outstanding：2）；
                                                         0x1-->选择threshold_1（delay：64；outstanding：4）；
                                                         0x2-->选择threshold_2（delay：128；outstanding：6）；
                                                         0x3-->选择threshold_3（delay：256；outstanding：10）； */
        unsigned int  reserved       : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_3_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_3_thresholds_0_3_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_3_thresholds_0_3_END    (1)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_OVERFLOWSTATUS_UNION
 结构说明  : ASP_TRANS_P_OVERFLOWSTATUS 寄存器结构定义。地址偏移量:0x80EC，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_OVERFLOWSTATUS_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_OVERFLOWSTATUS_overflowstatus_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_OVERFLOWSTATUS_overflowstatus_END    (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_OVERFLOWRESET_UNION
 结构说明  : ASP_TRANS_P_OVERFLOWRESET 寄存器结构定义。地址偏移量:0x80F0，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_OVERFLOWRESET_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_OVERFLOWRESET_overflowreset_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_OVERFLOWRESET_overflowreset_END    (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_PENDINGEVENTMODE_UNION
 结构说明  : ASP_TRANS_P_PENDINGEVENTMODE 寄存器结构定义。地址偏移量:0x80F4，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_PENDINGEVENTMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_PENDINGEVENTMODE_pendingeventmode_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_PENDINGEVENTMODE_pendingeventmode_END    (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_PRESCALER_UNION
 结构说明  : ASP_TRANS_P_PRESCALER 寄存器结构定义。地址偏移量:0x80F8，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_PRESCALER_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_PRESCALER_prescaler_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_PRESCALER_prescaler_END    (7)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_ID_COREID_UNION
 结构说明  : ASP_TRANS_M_ID_COREID 寄存器结构定义。地址偏移量:0x8400，初值:0xDED6C706，宽度:32
 寄存器说明: ASP Transaction probe域ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_coreid : 32; /* bit[0-31]: VcodecBus的Packet Probe的域ID。 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_ID_COREID_id_coreid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_ID_COREID_id_coreid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_ID_REVISIONID_UNION
 结构说明  : ASP_TRANS_M_ID_REVISIONID 寄存器结构定义。地址偏移量:0x8404，初值:0x012D5300，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_ID_REVISIONID_id_revisionid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_ID_REVISIONID_id_revisionid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_MAINCTL_UNION
 结构说明  : ASP_TRANS_M_MAINCTL 寄存器结构定义。地址偏移量:0x8408，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_MAINCTL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_MAINCTL_erren_START                      (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_MAINCTL_erren_END                        (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_MAINCTL_traceen_START                    (1)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_MAINCTL_traceen_END                      (1)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_MAINCTL_payloaden_START                  (2)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_MAINCTL_payloaden_END                    (2)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_MAINCTL_staten_START                     (3)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_MAINCTL_staten_END                       (3)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_MAINCTL_alarmen_START                    (4)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_MAINCTL_alarmen_END                      (4)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_MAINCTL_statconddump_START               (5)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_MAINCTL_statconddump_END                 (5)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_MAINCTL_intrusivemode_START              (6)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_MAINCTL_intrusivemode_END                (6)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_MAINCTL_filtbytealwayschainableen_START  (7)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_MAINCTL_filtbytealwayschainableen_END    (7)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_CFGCTL_UNION
 结构说明  : ASP_TRANS_M_CFGCTL 寄存器结构定义。地址偏移量:0x840C，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_CFGCTL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_CFGCTL_globalen_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_CFGCTL_globalen_END    (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_CFGCTL_active_START    (1)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_CFGCTL_active_END      (1)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATPERIOD_UNION
 结构说明  : ASP_TRANS_M_STATPERIOD 寄存器结构定义。地址偏移量:0x8424，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATPERIOD_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATPERIOD_statperiod_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATPERIOD_statperiod_END    (4)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATGO_UNION
 结构说明  : ASP_TRANS_M_STATGO 寄存器结构定义。地址偏移量:0x8428，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATGO_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATGO_statgo_START    (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATGO_statgo_END      (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMMIN_UNION
 结构说明  : ASP_TRANS_M_STATALARMMIN 寄存器结构定义。地址偏移量:0x842C，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMMIN_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMMIN_statalarmmin_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMMIN_statalarmmin_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMMAX_UNION
 结构说明  : ASP_TRANS_M_STATALARMMAX 寄存器结构定义。地址偏移量:0x8430，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMMAX_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMMAX_statalarmmax_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMMAX_statalarmmax_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMSTATUS_UNION
 结构说明  : ASP_TRANS_M_STATALARMSTATUS 寄存器结构定义。地址偏移量:0x8434，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMSTATUS_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMSTATUS_statalarmstatus_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMSTATUS_statalarmstatus_END    (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMCLR_UNION
 结构说明  : ASP_TRANS_M_STATALARMCLR 寄存器结构定义。地址偏移量:0x8438，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMCLR_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMCLR_statalarmclr_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMCLR_statalarmclr_END    (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_0_SRC_UNION
 结构说明  : ASP_TRANS_M_COUNTERS_0_SRC 寄存器结构定义。地址偏移量:0x8538，初值:0x00000000，宽度:32
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
                                                         0x20-->Bin 0（delay：0~31；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：32~63；outstanding：2~3）；
                                                         0x22-->Bin 2（delay：64~127；outstanding：4~5）；
                                                         0x23-->Bin 3（delay：128~255；outstanding：8~9）；
                                                         0x24-->Bin 4（delay：>= 256；outstanding：>= 10）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_0_SRC_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_0_SRC_counters_0_src_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_0_SRC_counters_0_src_END    (5)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_0_ALARMMODE_UNION
 结构说明  : ASP_TRANS_M_COUNTERS_0_ALARMMODE 寄存器结构定义。地址偏移量:0x853C，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_0_ALARMMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_0_ALARMMODE_counters_0_alarmmode_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_0_ALARMMODE_counters_0_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_0_VAL_UNION
 结构说明  : ASP_TRANS_M_COUNTERS_0_VAL 寄存器结构定义。地址偏移量:0x8540，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_0_val : 12; /* bit[0-11] : 当Counters_0_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 20; /* bit[12-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_0_VAL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_0_VAL_counters_0_val_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_0_VAL_counters_0_val_END    (11)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_1_SRC_UNION
 结构说明  : ASP_TRANS_M_COUNTERS_1_SRC 寄存器结构定义。地址偏移量:0x854C，初值:0x00000000，宽度:32
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
                                                         0x20-->Bin 0（delay：0~31；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：32~63；outstanding：2~3）；
                                                         0x22-->Bin 2（delay：64~127；outstanding：4~5）；
                                                         0x23-->Bin 3（delay：128~255；outstanding：8~9）；
                                                         0x24-->Bin 4（delay：>= 256；outstanding：>= 10）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_1_SRC_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_1_SRC_counters_1_src_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_1_SRC_counters_1_src_END    (5)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_1_ALARMMODE_UNION
 结构说明  : ASP_TRANS_M_COUNTERS_1_ALARMMODE 寄存器结构定义。地址偏移量:0x8550，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_1_ALARMMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_1_ALARMMODE_counters_1_alarmmode_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_1_ALARMMODE_counters_1_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_1_VAL_UNION
 结构说明  : ASP_TRANS_M_COUNTERS_1_VAL 寄存器结构定义。地址偏移量:0x8554，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_1_val : 12; /* bit[0-11] : 当Counters_1_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 20; /* bit[12-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_1_VAL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_1_VAL_counters_1_val_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_1_VAL_counters_1_val_END    (11)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_2_SRC_UNION
 结构说明  : ASP_TRANS_M_COUNTERS_2_SRC 寄存器结构定义。地址偏移量:0x8560，初值:0x00000000，宽度:32
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
                                                         0x20-->Bin 0（delay：0~31；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：32~63；outstanding：2~3）；
                                                         0x22-->Bin 2（delay：64~127；outstanding：4~5）；
                                                         0x23-->Bin 3（delay：128~255；outstanding：8~9）；
                                                         0x24-->Bin 4（delay：>= 256；outstanding：>= 10）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_2_SRC_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_2_SRC_counters_2_src_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_2_SRC_counters_2_src_END    (5)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_2_ALARMMODE_UNION
 结构说明  : ASP_TRANS_M_COUNTERS_2_ALARMMODE 寄存器结构定义。地址偏移量:0x8564，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_2_ALARMMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_2_ALARMMODE_counters_2_alarmmode_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_2_ALARMMODE_counters_2_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_2_VAL_UNION
 结构说明  : ASP_TRANS_M_COUNTERS_2_VAL 寄存器结构定义。地址偏移量:0x8568，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_2_val : 12; /* bit[0-11] : 当Counters_2_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 20; /* bit[12-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_2_VAL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_2_VAL_counters_2_val_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_2_VAL_counters_2_val_END    (11)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_3_SRC_UNION
 结构说明  : ASP_TRANS_M_COUNTERS_3_SRC 寄存器结构定义。地址偏移量:0x8574，初值:0x00000000，宽度:32
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
                                                         0x20-->Bin 0（delay：0~31；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：32~63；outstanding：2~3）；
                                                         0x22-->Bin 2（delay：64~127；outstanding：4~5）；
                                                         0x23-->Bin 3（delay：128~255；outstanding：8~9）；
                                                         0x24-->Bin 4（delay：>= 256；outstanding：>= 10）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_3_SRC_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_3_SRC_counters_3_src_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_3_SRC_counters_3_src_END    (5)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_3_ALARMMODE_UNION
 结构说明  : ASP_TRANS_M_COUNTERS_3_ALARMMODE 寄存器结构定义。地址偏移量:0x8578，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_3_ALARMMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_3_ALARMMODE_counters_3_alarmmode_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_3_ALARMMODE_counters_3_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_3_VAL_UNION
 结构说明  : ASP_TRANS_M_COUNTERS_3_VAL 寄存器结构定义。地址偏移量:0x857C，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_3_val : 12; /* bit[0-11] : 当Counters_3_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 20; /* bit[12-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_3_VAL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_3_VAL_counters_3_val_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_3_VAL_counters_3_val_END    (11)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_4_SRC_UNION
 结构说明  : ASP_TRANS_M_COUNTERS_4_SRC 寄存器结构定义。地址偏移量:0x8588，初值:0x00000000，宽度:32
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
                                                         0x20-->Bin 0（delay：0~31；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：32~63；outstanding：2~3）；
                                                         0x22-->Bin 2（delay：64~127；outstanding：4~5）；
                                                         0x23-->Bin 3（delay：128~255；outstanding：8~9）；
                                                         0x24-->Bin 4（delay：>= 256；outstanding：>= 10）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_4_SRC_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_4_SRC_counters_4_src_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_4_SRC_counters_4_src_END    (5)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_4_ALARMMODE_UNION
 结构说明  : ASP_TRANS_M_COUNTERS_4_ALARMMODE 寄存器结构定义。地址偏移量:0x858C，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_4_ALARMMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_4_ALARMMODE_counters_4_alarmmode_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_4_ALARMMODE_counters_4_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_4_VAL_UNION
 结构说明  : ASP_TRANS_M_COUNTERS_4_VAL 寄存器结构定义。地址偏移量:0x8590，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_4_val : 12; /* bit[0-11] : 当Counters_4_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 20; /* bit[12-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_4_VAL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_4_VAL_counters_4_val_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_4_VAL_counters_4_val_END    (11)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_5_SRC_UNION
 结构说明  : ASP_TRANS_M_COUNTERS_5_SRC 寄存器结构定义。地址偏移量:0x859C，初值:0x00000000，宽度:32
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
                                                         0x20-->Bin 0（delay：0~31；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：32~63；outstanding：2~3）；
                                                         0x22-->Bin 2（delay：64~127；outstanding：4~5）；
                                                         0x23-->Bin 3（delay：128~255；outstanding：8~9）；
                                                         0x24-->Bin 4（delay：>= 256；outstanding：>= 10）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_5_SRC_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_5_SRC_counters_5_src_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_5_SRC_counters_5_src_END    (5)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_5_ALARMMODE_UNION
 结构说明  : ASP_TRANS_M_COUNTERS_5_ALARMMODE 寄存器结构定义。地址偏移量:0x85A0，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_5_ALARMMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_5_ALARMMODE_counters_5_alarmmode_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_5_ALARMMODE_counters_5_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_5_VAL_UNION
 结构说明  : ASP_TRANS_M_COUNTERS_5_VAL 寄存器结构定义。地址偏移量:0x85A4，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_5_val : 12; /* bit[0-11] : 当Counters_5_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 20; /* bit[12-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_5_VAL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_5_VAL_counters_5_val_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_5_VAL_counters_5_val_END    (11)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_6_SRC_UNION
 结构说明  : ASP_TRANS_M_COUNTERS_6_SRC 寄存器结构定义。地址偏移量:0x85B0，初值:0x00000000，宽度:32
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
                                                         0x20-->Bin 0（delay：0~31；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：32~63；outstanding：2~3）；
                                                         0x22-->Bin 2（delay：64~127；outstanding：4~5）；
                                                         0x23-->Bin 3（delay：128~255；outstanding：8~9）；
                                                         0x24-->Bin 4（delay：>= 256；outstanding：>= 10）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_6_SRC_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_6_SRC_counters_6_src_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_6_SRC_counters_6_src_END    (5)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_6_ALARMMODE_UNION
 结构说明  : ASP_TRANS_M_COUNTERS_6_ALARMMODE 寄存器结构定义。地址偏移量:0x85B4，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_6_ALARMMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_6_ALARMMODE_counters_6_alarmmode_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_6_ALARMMODE_counters_6_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_6_VAL_UNION
 结构说明  : ASP_TRANS_M_COUNTERS_6_VAL 寄存器结构定义。地址偏移量:0x85B8，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_6_val : 12; /* bit[0-11] : 当Counters_6_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 20; /* bit[12-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_6_VAL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_6_VAL_counters_6_val_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_6_VAL_counters_6_val_END    (11)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_7_SRC_UNION
 结构说明  : ASP_TRANS_M_COUNTERS_7_SRC 寄存器结构定义。地址偏移量:0x85C4，初值:0x00000000，宽度:32
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
                                                         0x20-->Bin 0（delay：0~31；outstanding：0~1）；
                                                         0x21-->Bin 1（delay：32~63；outstanding：2~3）；
                                                         0x22-->Bin 2（delay：64~127；outstanding：4~5）；
                                                         0x23-->Bin 3（delay：128~255；outstanding：8~9）；
                                                         0x24-->Bin 4（delay：>= 256；outstanding：>= 10）；
                                                         其它-->保留； */
        unsigned int  reserved       : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_7_SRC_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_7_SRC_counters_7_src_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_7_SRC_counters_7_src_END    (5)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_7_ALARMMODE_UNION
 结构说明  : ASP_TRANS_M_COUNTERS_7_ALARMMODE 寄存器结构定义。地址偏移量:0x85C8，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_7_ALARMMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_7_ALARMMODE_counters_7_alarmmode_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_7_ALARMMODE_counters_7_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_7_VAL_UNION
 结构说明  : ASP_TRANS_M_COUNTERS_7_VAL 寄存器结构定义。地址偏移量:0x85CC，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_7_val : 12; /* bit[0-11] : 当Counters_7_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 20; /* bit[12-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_7_VAL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_7_VAL_counters_7_val_START  (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_7_VAL_counters_7_val_END    (11)




/****************************************************************************
                     (3/9) SYSBUS
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_ID_COREID_UNION
 结构说明  : CCI2SYSBUS_QOS_ID_COREID 寄存器结构定义。地址偏移量:0x0000，初值:0xFF81DF04，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_ID_COREID_coretypeid_START    (0)
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_ID_COREID_coretypeid_END      (7)
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_ID_COREID_corechecksum_START  (8)
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_ID_REVISIONID_UNION
 结构说明  : CCI2SYSBUS_QOS_ID_REVISIONID 寄存器结构定义。地址偏移量:0x0004，初值:0x012D5300，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_ID_REVISIONID_userid_START     (0)
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_ID_REVISIONID_userid_END       (7)
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_ID_REVISIONID_flexnocid_START  (8)
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_PRIORITY_UNION
 结构说明  : CCI2SYSBUS_QOS_PRIORITY 寄存器结构定义。地址偏移量:0x0008，初值:0x80000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_PRIORITY_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_PRIORITY_p0_START        (0)
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_PRIORITY_p0_END          (1)
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_PRIORITY_p1_START        (8)
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_PRIORITY_p1_END          (9)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_MODE_UNION
 结构说明  : CCI2SYSBUS_QOS_MODE 寄存器结构定义。地址偏移量:0x000C，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_MODE_mode_START      (0)
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_MODE_mode_END        (1)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_EXTCONTROL_UNION
 结构说明  : CCI2SYSBUS_QOS_EXTCONTROL 寄存器结构定义。地址偏移量:0x0018，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_EXTCONTROL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_EXTCONTROL_socketqosen_START  (0)
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_EXTCONTROL_socketqosen_END    (0)
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_EXTCONTROL_extthren_START     (1)
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_EXTCONTROL_extthren_END       (1)
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_EXTCONTROL_intclken_START     (2)
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_EXTCONTROL_intclken_END       (2)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAPTER_ID_COREID_UNION
 结构说明  : AOBUS2DDRC_ADAPTER_ID_COREID 寄存器结构定义。地址偏移量:0x1000，初值:0x4995B101，宽度:32
 寄存器说明: adapter域ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_coreid : 32; /* bit[0-31]: RateAdapter的域ID。 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAPTER_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAPTER_ID_COREID_id_coreid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAPTER_ID_COREID_id_coreid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAPTER_ID_REVISIONID_UNION
 结构说明  : AOBUS2DDRC_ADAPTER_ID_REVISIONID 寄存器结构定义。地址偏移量:0x1004，初值:0x012D5300，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAPTER_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAPTER_ID_REVISIONID_id_revisionid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAPTER_ID_REVISIONID_id_revisionid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAPTERRATE_UNION
 结构说明  : AOBUS2DDRC_ADAPTERRATE 寄存器结构定义。地址偏移量:0x1008，初值:0x00000000，宽度:32
 寄存器说明: Rate Adapter配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rate     : 10; /* bit[0-9]  : pre-computed throughout ratio */
        unsigned int  reserved : 22; /* bit[10-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAPTERRATE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAPTERRATE_rate_START      (0)
#define SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAPTERRATE_rate_END        (9)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAP_BYPASS_UNION
 结构说明  : AOBUS2DDRC_ADAP_BYPASS 寄存器结构定义。地址偏移量:0x100C，初值:0x00000000，宽度:32
 寄存器说明: Rate Adapter bypass寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bypass   : 1;  /* bit[0]   : bypass the rate-adapter */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAP_BYPASS_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAP_BYPASS_bypass_START    (0)
#define SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAP_BYPASS_bypass_END      (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAPTER_ID_COREID_UNION
 结构说明  : SYS2CFG_ADAPTER_ID_COREID 寄存器结构定义。地址偏移量:0x1080，初值:0x13DCBD01，宽度:32
 寄存器说明: adapter域ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_coreid : 32; /* bit[0-31]: RateAdapter的域ID。 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAPTER_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAPTER_ID_COREID_id_coreid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAPTER_ID_COREID_id_coreid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAPTER_ID_REVISIONID_UNION
 结构说明  : SYS2CFG_ADAPTER_ID_REVISIONID 寄存器结构定义。地址偏移量:0x1084，初值:0x012D5300，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAPTER_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAPTER_ID_REVISIONID_id_revisionid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAPTER_ID_REVISIONID_id_revisionid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAPTERRATE_UNION
 结构说明  : SYS2CFG_ADAPTERRATE 寄存器结构定义。地址偏移量:0x1088，初值:0x00000000，宽度:32
 寄存器说明: Rate Adapter配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rate     : 10; /* bit[0-9]  : pre-computed throughout ratio */
        unsigned int  reserved : 22; /* bit[10-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAPTERRATE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAPTERRATE_rate_START      (0)
#define SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAPTERRATE_rate_END        (9)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAP_BYPASS_UNION
 结构说明  : SYS2CFG_ADAP_BYPASS 寄存器结构定义。地址偏移量:0x108C，初值:0x00000000，宽度:32
 寄存器说明: Rate Adapter bypass寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bypass   : 1;  /* bit[0]   : bypass the rate-adapter */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAP_BYPASS_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAP_BYPASS_bypass_START    (0)
#define SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAP_BYPASS_bypass_END      (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAPTER_ID_COREID_UNION
 结构说明  : PERI2DDRC_ADAPTER_ID_COREID 寄存器结构定义。地址偏移量:0x1100，初值:0xB46F5701，宽度:32
 寄存器说明: adapter域ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_coreid : 32; /* bit[0-31]: RateAdapter的域ID。 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAPTER_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAPTER_ID_COREID_id_coreid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAPTER_ID_COREID_id_coreid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAPTER_ID_REVISIONID_UNION
 结构说明  : PERI2DDRC_ADAPTER_ID_REVISIONID 寄存器结构定义。地址偏移量:0x1104，初值:0x012D5300，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAPTER_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAPTER_ID_REVISIONID_id_revisionid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAPTER_ID_REVISIONID_id_revisionid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAPTERRATE_UNION
 结构说明  : PERI2DDRC_ADAPTERRATE 寄存器结构定义。地址偏移量:0x1108，初值:0x00000000，宽度:32
 寄存器说明: Rate Adapter配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rate     : 10; /* bit[0-9]  : pre-computed throughout ratio */
        unsigned int  reserved : 22; /* bit[10-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAPTERRATE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAPTERRATE_rate_START      (0)
#define SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAPTERRATE_rate_END        (9)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAP_BYPASS_UNION
 结构说明  : PERI2DDRC_ADAP_BYPASS 寄存器结构定义。地址偏移量:0x110C，初值:0x00000000，宽度:32
 寄存器说明: Rate Adapter bypass寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bypass   : 1;  /* bit[0]   : bypass the rate-adapter */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAP_BYPASS_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAP_BYPASS_bypass_START    (0)
#define SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAP_BYPASS_bypass_END      (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAPTER_ID_COREID_UNION
 结构说明  : SYS2PERI_ADAPTER_ID_COREID 寄存器结构定义。地址偏移量:0x1180，初值:0xF54FB501，宽度:32
 寄存器说明: adapter域ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_coreid : 32; /* bit[0-31]: RateAdapter的域ID。 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAPTER_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAPTER_ID_COREID_id_coreid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAPTER_ID_COREID_id_coreid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAPTER_ID_REVISIONID_UNION
 结构说明  : SYS2PERI_ADAPTER_ID_REVISIONID 寄存器结构定义。地址偏移量:0x1184，初值:0x012D5300，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAPTER_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAPTER_ID_REVISIONID_id_revisionid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAPTER_ID_REVISIONID_id_revisionid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAPTERRATE_UNION
 结构说明  : SYS2PERI_ADAPTERRATE 寄存器结构定义。地址偏移量:0x1188，初值:0x00000000，宽度:32
 寄存器说明: Rate Adapter配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rate     : 10; /* bit[0-9]  : pre-computed throughout ratio */
        unsigned int  reserved : 22; /* bit[10-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAPTERRATE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAPTERRATE_rate_START      (0)
#define SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAPTERRATE_rate_END        (9)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAP_BYPASS_UNION
 结构说明  : SYS2PERI_ADAP_BYPASS 寄存器结构定义。地址偏移量:0x118C，初值:0x00000000，宽度:32
 寄存器说明: Rate Adapter bypass寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bypass   : 1;  /* bit[0]   : bypass the rate-adapter */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAP_BYPASS_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAP_BYPASS_bypass_START    (0)
#define SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAP_BYPASS_bypass_END      (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAPTER_ID_COREID_UNION
 结构说明  : MODEM2DDR_ADAPTER_ID_COREID 寄存器结构定义。地址偏移量:0x1200，初值:0xF7A25201，宽度:32
 寄存器说明: adapter域ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_coreid : 32; /* bit[0-31]: RateAdapter的域ID。 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAPTER_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAPTER_ID_COREID_id_coreid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAPTER_ID_COREID_id_coreid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAPTER_ID_REVISIONID_UNION
 结构说明  : MODEM2DDR_ADAPTER_ID_REVISIONID 寄存器结构定义。地址偏移量:0x1204，初值:0x012D5300，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAPTER_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAPTER_ID_REVISIONID_id_revisionid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAPTER_ID_REVISIONID_id_revisionid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAPTERRATE_UNION
 结构说明  : MODEM2DDR_ADAPTERRATE 寄存器结构定义。地址偏移量:0x1208，初值:0x00000000，宽度:32
 寄存器说明: Rate Adapter配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rate     : 10; /* bit[0-9]  : pre-computed throughout ratio */
        unsigned int  reserved : 22; /* bit[10-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAPTERRATE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAPTERRATE_rate_START      (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAPTERRATE_rate_END        (9)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAP_BYPASS_UNION
 结构说明  : MODEM2DDR_ADAP_BYPASS 寄存器结构定义。地址偏移量:0x120C，初值:0x00000000，宽度:32
 寄存器说明: Rate Adapter bypass寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bypass   : 1;  /* bit[0]   : bypass the rate-adapter */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAP_BYPASS_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAP_BYPASS_bypass_START    (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAP_BYPASS_bypass_END      (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAPTER_ID_COREID_UNION
 结构说明  : CFG2SYS_ADAPTER_ID_COREID 寄存器结构定义。地址偏移量:0x1280，初值:0x14ADFD01，宽度:32
 寄存器说明: adapter域ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_coreid : 32; /* bit[0-31]: RateAdapter的域ID。 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAPTER_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAPTER_ID_COREID_id_coreid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAPTER_ID_COREID_id_coreid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAPTER_ID_REVISIONID_UNION
 结构说明  : CFG2SYS_ADAPTER_ID_REVISIONID 寄存器结构定义。地址偏移量:0x1284，初值:0x012D5300，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAPTER_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAPTER_ID_REVISIONID_id_revisionid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAPTER_ID_REVISIONID_id_revisionid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAPTERRATE_UNION
 结构说明  : CFG2SYS_ADAPTERRATE 寄存器结构定义。地址偏移量:0x1288，初值:0x00000000，宽度:32
 寄存器说明: Rate Adapter配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rate     : 10; /* bit[0-9]  : pre-computed throughout ratio */
        unsigned int  reserved : 22; /* bit[10-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAPTERRATE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAPTERRATE_rate_START      (0)
#define SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAPTERRATE_rate_END        (9)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAP_BYPASS_UNION
 结构说明  : CFG2SYS_ADAP_BYPASS 寄存器结构定义。地址偏移量:0x128C，初值:0x00000000，宽度:32
 寄存器说明: Rate Adapter bypass寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bypass   : 1;  /* bit[0]   : bypass the rate-adapter */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAP_BYPASS_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAP_BYPASS_bypass_START    (0)
#define SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAP_BYPASS_bypass_END      (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MMC1_ADAPTER_ID_COREID_UNION
 结构说明  : MMC1_ADAPTER_ID_COREID 寄存器结构定义。地址偏移量:0x1300，初值:0xE0199F01，宽度:32
 寄存器说明: adapter域ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_coreid : 32; /* bit[0-31]: RateAdapter的域ID。 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC1_ADAPTER_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC1_ADAPTER_ID_COREID_id_coreid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1_ADAPTER_ID_COREID_id_coreid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MMC1_ADAPTER_ID_REVISIONID_UNION
 结构说明  : MMC1_ADAPTER_ID_REVISIONID 寄存器结构定义。地址偏移量:0x1304，初值:0x012D5300，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MMC1_ADAPTER_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC1_ADAPTER_ID_REVISIONID_id_revisionid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1_ADAPTER_ID_REVISIONID_id_revisionid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MMC1_ADAPTERRATE_UNION
 结构说明  : MMC1_ADAPTERRATE 寄存器结构定义。地址偏移量:0x1308，初值:0x00000000，宽度:32
 寄存器说明: Rate Adapter配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rate     : 10; /* bit[0-9]  : pre-computed throughout ratio */
        unsigned int  reserved : 22; /* bit[10-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC1_ADAPTERRATE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC1_ADAPTERRATE_rate_START      (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1_ADAPTERRATE_rate_END        (9)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MMC1_ADAP_BYPASS_UNION
 结构说明  : MMC1_ADAP_BYPASS 寄存器结构定义。地址偏移量:0x130C，初值:0x00000000，宽度:32
 寄存器说明: Rate Adapter bypass寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bypass   : 1;  /* bit[0]   : bypass the rate-adapter */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC1_ADAP_BYPASS_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC1_ADAP_BYPASS_bypass_START    (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1_ADAP_BYPASS_bypass_END      (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SYSBUS_ERR_ID_COREID_UNION
 结构说明  : SYSBUS_ERR_ID_COREID 寄存器结构定义。地址偏移量:0x1C00，初值:0x08DA560D，宽度:32
 寄存器说明: SYSBUS Err probe域ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_coreid : 32; /* bit[0-31]: SYS_BUS的error probe的域ID。 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_ERR_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERR_ID_COREID_id_coreid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERR_ID_COREID_id_coreid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SYSBUS_ERR_ID_REVISIONID_UNION
 结构说明  : SYSBUS_ERR_ID_REVISIONID 寄存器结构定义。地址偏移量:0x1C04，初值:0x012D5300，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_SYSBUS_ERR_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERR_ID_REVISIONID_id_revisionid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERR_ID_REVISIONID_id_revisionid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SYSBUS_FAULTEN_UNION
 结构说明  : SYSBUS_FAULTEN 寄存器结构定义。地址偏移量:0x1C08，初值:0x00000000，宽度:32
 寄存器说明: SYSBUS Err probe使能
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
} SOC_CFG_SYS_NOC_BUS_SYSBUS_FAULTEN_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_FAULTEN_faulten_START   (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_FAULTEN_faulten_END     (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRVLD_UNION
 结构说明  : SYSBUS_ERRVLD 寄存器结构定义。地址偏移量:0x1C0C，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRVLD_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRVLD_errvld_START    (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRVLD_errvld_END      (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRCLR_UNION
 结构说明  : SYSBUS_ERRCLR 寄存器结构定义。地址偏移量:0x1C10，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRCLR_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRCLR_errclr_START    (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRCLR_errclr_END      (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG0_UNION
 结构说明  : SYSBUS_ERRLOG0 寄存器结构定义。地址偏移量:0x1C14，初值:0x80000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG0_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG0_lock_START      (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG0_lock_END        (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG0_opc_START       (1)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG0_opc_END         (4)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG0_errcode_START   (8)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG0_errcode_END     (10)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG0_len1_START      (16)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG0_len1_END        (23)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG0_format_START    (31)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG0_format_END      (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG1_UNION
 结构说明  : SYSBUS_ERRLOG1 寄存器结构定义。地址偏移量:0x1C18，初值:0x00000000，宽度:32
 寄存器说明: Error log1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errlog1  : 22; /* bit[0-21] : RouteId：路由信息，各bit含义如下
                                                    [21:17]-->Initiator Flow ID，用于表示发起访问的master；
                                                    [16:12]-->target Flow ID，用于表示被访问的slave；
                                                    [11:9]-->Target NIU SubRange；
                                                    [8:0]-->Seq ID，Transaction标记； */
        unsigned int  reserved : 10; /* bit[22-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG1_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG1_errlog1_START   (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG1_errlog1_END     (21)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG3_UNION
 结构说明  : SYSBUS_ERRLOG3 寄存器结构定义。地址偏移量:0x1C20，初值:0x00000000，宽度:32
 寄存器说明: Error log3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errlog3  : 31; /* bit[0-30] : 访问地址值 */
        unsigned int  reserved : 1;  /* bit[31-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG3_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG3_errlog3_START   (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG3_errlog3_END     (30)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG5_UNION
 结构说明  : SYSBUS_ERRLOG5 寄存器结构定义。地址偏移量:0x1C28，初值:0x00000000，宽度:32
 寄存器说明: Error log5
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errlog5  : 17; /* bit[0-16] : User信号值 */
        unsigned int  reserved : 15; /* bit[17-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG5_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG5_errlog5_START   (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG5_errlog5_END     (16)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG7_UNION
 结构说明  : SYSBUS_ERRLOG7 寄存器结构定义。地址偏移量:0x1C30，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG7_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG7_errlog7_START   (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG7_errlog7_END     (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_ID_COREID_UNION
 结构说明  : SYSBUS_DDRC_PACKET_ID_COREID 寄存器结构定义。地址偏移量:0x2000，初值:0x3BCD1F06，宽度:32
 寄存器说明: SYSBUS_DDRC Packet probe域ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_coreid : 32; /* bit[0-31]: SYSBUS_DDRC的Packet Probe的域ID。 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_ID_COREID_id_coreid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_ID_COREID_id_coreid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_ID_REVISIONID_UNION
 结构说明  : SYSBUS_DDRC_PACKET_ID_REVISIONID 寄存器结构定义。地址偏移量:0x2004，初值:0x012D5300，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_ID_REVISIONID_id_revisionid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_ID_REVISIONID_id_revisionid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_MAINCTL_UNION
 结构说明  : SYSBUS_DDRC_PACKET_MAINCTL 寄存器结构定义。地址偏移量:0x2008，初值:0x00000000，宽度:32
 寄存器说明: Packet Probe全局控制寄存器
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
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_MAINCTL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_MAINCTL_erren_START                      (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_MAINCTL_erren_END                        (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_MAINCTL_traceen_START                    (1)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_MAINCTL_traceen_END                      (1)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_MAINCTL_payloaden_START                  (2)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_MAINCTL_payloaden_END                    (2)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_MAINCTL_staten_START                     (3)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_MAINCTL_staten_END                       (3)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_MAINCTL_alarmen_START                    (4)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_MAINCTL_alarmen_END                      (4)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_MAINCTL_statconddump_START               (5)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_MAINCTL_statconddump_END                 (5)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_MAINCTL_intrusivemode_START              (6)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_MAINCTL_intrusivemode_END                (6)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_MAINCTL_filtbytealwayschainableen_START  (7)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_MAINCTL_filtbytealwayschainableen_END    (7)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_CFGCTL_UNION
 结构说明  : SYSBUS_DDRC_PACKET_CFGCTL 寄存器结构定义。地址偏移量:0x200C，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_CFGCTL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_CFGCTL_globalen_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_CFGCTL_globalen_END    (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_CFGCTL_active_START    (1)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_CFGCTL_active_END      (1)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_FILTERLUT_UNION
 结构说明  : SYSBUS_DDRC_PACKET_FILTERLUT 寄存器结构定义。地址偏移量:0x2014，初值:0x00000000，宽度:32
 寄存器说明: 过滤条件查找表
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  filterlut : 2;  /* bit[0-1] : 选择过滤条件：
                                                    0x3 reserved
                                                    0x2-->~F0 过滤条件为F0取反；
                                                    0x1-->F0 过滤条件为F0；
                                                    0x0 reserved */
        unsigned int  reserved  : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_FILTERLUT_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_FILTERLUT_filterlut_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_FILTERLUT_filterlut_END    (1)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATPERIOD_UNION
 结构说明  : SYSBUS_DDRC_PACKET_STATPERIOD 寄存器结构定义。地址偏移量:0x2024，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATPERIOD_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATPERIOD_statperiod_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATPERIOD_statperiod_END    (4)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATGO_UNION
 结构说明  : SYSBUS_DDRC_PACKET_STATGO 寄存器结构定义。地址偏移量:0x2028，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATGO_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATGO_statgo_START    (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATGO_statgo_END      (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMMIN_UNION
 结构说明  : SYSBUS_DDRC_PACKET_STATALARMMIN 寄存器结构定义。地址偏移量:0x202C，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMMIN_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMMIN_statalarmmin_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMMIN_statalarmmin_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMMAX_UNION
 结构说明  : SYSBUS_DDRC_PACKET_STATALARMMAX 寄存器结构定义。地址偏移量:0x2030，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMMAX_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMMAX_statalarmmax_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMMAX_statalarmmax_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMSTATUS_UNION
 结构说明  : SYSBUS_DDRC_PACKET_STATALARMSTATUS 寄存器结构定义。地址偏移量:0x2034，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMSTATUS_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMSTATUS_statalarmstatus_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMSTATUS_statalarmstatus_END    (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMCLR_UNION
 结构说明  : SYSBUS_DDRC_PACKET_STATALARMCLR 寄存器结构定义。地址偏移量:0x2038，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMCLR_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMCLR_statalarmclr_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMCLR_statalarmclr_END    (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_ROUTEIDBASE_UNION
 结构说明  : SYSBUS_DDRC_PACKET_F0_ROUTEIDBASE 寄存器结构定义。地址偏移量:0x2044，初值:0x00000000，宽度:32
 寄存器说明: F0的RouteId过滤条件配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  filters_0_routeidbase : 22; /* bit[0-21] : 通过配置routeId可以过滤master到slave的访问通路上的Packet：
                                                                 [21:17]-->initiator flow：用于表示master ID；
                                                                 [16:12]-->target flow：用于表示slave ID；
                                                                 [11:9]-->Target SubRange：用于表示同一个的slave不同的Mapping地址；
                                                                 [8:0]-->SeqIds：用于表示同一条访问通路的不同transaction的ID，建议不把这4bit作为过滤条件； */
        unsigned int  reserved              : 10; /* bit[22-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_ROUTEIDBASE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_ROUTEIDBASE_filters_0_routeidbase_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_ROUTEIDBASE_filters_0_routeidbase_END    (21)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_ROUTEIDMASK_UNION
 结构说明  : SYSBUS_DDRC_PACKET_F0_ROUTEIDMASK 寄存器结构定义。地址偏移量:0x2048，初值:0x00000000，宽度:32
 寄存器说明: F0的RouteId过滤条件Mask配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  filters_0_routeidmask : 22; /* bit[0-21] : 对RouteIdBase进行Mask。
                                                                 例如：过滤条件为initiator flow + target flow，那么配置此寄存器的值为0x3FF000。 */
        unsigned int  reserved              : 10; /* bit[22-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_ROUTEIDMASK_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_ROUTEIDMASK_filters_0_routeidmask_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_ROUTEIDMASK_filters_0_routeidmask_END    (21)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_ADDRBASE_UNION
 结构说明  : SYSBUS_DDRC_PACKET_F0_ADDRBASE 寄存器结构定义。地址偏移量:0x204C，初值:0x00000000，宽度:32
 寄存器说明: F0的地址过滤条件配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  filters_0_addrbase_low : 32; /* bit[0-31]: 地址过滤条件的基地址。 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_ADDRBASE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_ADDRBASE_filters_0_addrbase_low_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_ADDRBASE_filters_0_addrbase_low_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_WINDOWSIZE_UNION
 结构说明  : SYSBUS_DDRC_PACKET_F0_WINDOWSIZE 寄存器结构定义。地址偏移量:0x2054，初值:0x00000000，宽度:32
 寄存器说明: F0的地址过滤的Mask地址大小配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  filters_0_windowsize : 6;  /* bit[0-5] : 地址过滤的Mask窗口大小。
                                                               例如：地址过滤的Mask窗口大小为64MB，WidowSize=log2(64MB)=26，此时，就配置filter_0_windowsize=0x1A；
                                                               Address Mask=~（2^max(WindowSize,packet.len)-1）=0xFC000000（packet.len为NOC内部表示一个packet包长变量的位宽，其值为6~7）；
                                                               过滤条件为：PacketAddress & AddressMask = AddressBase & AddressMask。 */
        unsigned int  reserved             : 26; /* bit[6-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_WINDOWSIZE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_WINDOWSIZE_filters_0_windowsize_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_WINDOWSIZE_filters_0_windowsize_END    (5)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_SECURITYBASE_UNION
 结构说明  : SYSBUS_DDRC_PACKET_F0_SECURITYBASE 寄存器结构定义。地址偏移量:0x2058，初值:0x00000000，宽度:32
 寄存器说明: F0的安全过滤条件配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  filters_0_securitybase : 1;  /* bit[0]   : 0-->表示安全过滤条件；
                                                                 1-->表示非安全过滤条件。 */
        unsigned int  reserved               : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_SECURITYBASE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_SECURITYBASE_filters_0_securitybase_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_SECURITYBASE_filters_0_securitybase_END    (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_SECURITYMASK_UNION
 结构说明  : SYSBUS_DDRC_PACKET_F0_SECURITYMASK 寄存器结构定义。地址偏移量:0x205C，初值:0x00000000，宽度:32
 寄存器说明: F0的安全过滤条件的Mask
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  filters_0_securitymask : 1;  /* bit[0]   : 安全过滤条件：packet.Security & SecurityMask = SecurityBase & SecurityMasks；
                                                                 也就是说当Filters_0_SecurityMask=1时安全过滤条件Filters_0_SecurityBase有效，可以过滤安全或非安全packet；否则，不起过滤作用； */
        unsigned int  reserved               : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_SECURITYMASK_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_SECURITYMASK_filters_0_securitymask_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_SECURITYMASK_filters_0_securitymask_END    (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_OPCODE_UNION
 结构说明  : SYSBUS_DDRC_PACKET_F0_OPCODE 寄存器结构定义。地址偏移量:0x2060，初值:0x00000000，宽度:32
 寄存器说明: F0的Opcode过滤条件配置
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rden     : 1;  /* bit[0]   : 0-->不选择统计读操作packet；
                                                   1-->选择统计读操作packet。 */
        unsigned int  wren     : 1;  /* bit[1]   : 0-->不选择统计写操作packet；
                                                   1-->选择统计写操作packet。 */
        unsigned int  locken   : 1;  /* bit[2]   : 0-->不选择统计exclusive transaction；
                                                   1-->选择统计exclusive transaction。 */
        unsigned int  urgen    : 1;  /* bit[3]   : 0-->不选择统计带有urgency的packet；
                                                   1-->选择统计带有urgency的packet。 */
        unsigned int  reserved : 28; /* bit[4-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_OPCODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_OPCODE_rden_START      (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_OPCODE_rden_END        (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_OPCODE_wren_START      (1)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_OPCODE_wren_END        (1)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_OPCODE_locken_START    (2)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_OPCODE_locken_END      (2)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_OPCODE_urgen_START     (3)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_OPCODE_urgen_END       (3)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_STATUS_UNION
 结构说明  : SYSBUS_DDRC_PACKET_F0_STATUS 寄存器结构定义。地址偏移量:0x2064，初值:0x00000000，宽度:32
 寄存器说明: F0的packet状态过滤条件
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reqen    : 1;  /* bit[0]   : 0-->不选择统计request packet；
                                                   1-->选择统计request packet。 */
        unsigned int  rspen    : 1;  /* bit[1]   : 0-->不选择统计response packet；
                                                   1-->选择统计response packet。 */
        unsigned int  reserved : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_STATUS_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_STATUS_reqen_START     (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_STATUS_reqen_END       (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_STATUS_rspen_START     (1)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_STATUS_rspen_END       (1)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_LENGTH_UNION
 结构说明  : SYSBUS_DDRC_PACKET_F0_LENGTH 寄存器结构定义。地址偏移量:0x2068，初值:0x00000000，宽度:32
 寄存器说明: F0的包长过滤条件
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  filters_0_length : 4;  /* bit[0-3] : 选择统计包长小于等于2^Filters_0_Length的packet */
        unsigned int  reserved         : 28; /* bit[4-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_LENGTH_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_LENGTH_filters_0_length_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_LENGTH_filters_0_length_END    (3)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_URGENCY_UNION
 结构说明  : SYSBUS_DDRC_PACKET_F0_URGENCY 寄存器结构定义。地址偏移量:0x206C，初值:0x00000000，宽度:32
 寄存器说明: F0的urgency过滤条件
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  filters_0_urgency : 2;  /* bit[0-1] : 选择统计urgency 大于等于Filters_0_Urgency的packet。Eg.配置为0，则过滤所有urgency等级的packet。 */
        unsigned int  reserved          : 30; /* bit[2-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_URGENCY_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_URGENCY_filters_0_urgency_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_URGENCY_filters_0_urgency_END    (1)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_USERBASE_UNION
 结构说明  : SYSBUS_DDRC_PACKET_F0_USERBASE 寄存器结构定义。地址偏移量:0x2070，初值:0x00000000，宽度:32
 寄存器说明: F0的User过滤条件
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  filters_0_userbase : 12; /* bit[0-11] : User信号过滤条件 */
        unsigned int  reserved           : 20; /* bit[12-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_USERBASE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_USERBASE_filters_0_userbase_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_USERBASE_filters_0_userbase_END    (11)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_USERMASK_UNION
 结构说明  : SYSBUS_DDRC_PACKET_F0_USERMASK 寄存器结构定义。地址偏移量:0x2074，初值:0x00000000，宽度:32
 寄存器说明: F0的User过滤条件Mask
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  filters_0_usermask : 12; /* bit[0-11] : 对UserBase进行Mask，选择UserBase中的任意几bit User信号作为过滤条件。
                                                              过滤条件：packet.User & UserMask = UserBase & UserMask。 */
        unsigned int  reserved           : 20; /* bit[12-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_USERMASK_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_USERMASK_filters_0_usermask_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_USERMASK_filters_0_usermask_END    (11)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_0_SRC_UNION
 结构说明  : SYSBUS_DDRC_PACKET_COUNTERS_0_SRC 寄存器结构定义。地址偏移量:0x2138，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_0_src : 5;  /* bit[0-4] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x01-->Clock cycles；
                                                         0x02-->IDLE cycles；
                                                         0x03-->Transfer cycles；
                                                         0x04-->Busy cycles；
                                                         0x05-->Wait cycles；
                                                         0x06-->Packets个数统计；
                                                         0x07-->被LUT过滤选中的Packet个数统计；
                                                         0x08-->统计总的bytes数量；
                                                         0x09-->统计Pressure level>0的时钟周期个数；
                                                         0x0A-->统计Pressure level>1的时钟周期个数；
                                                         0x0B-->统计Pressure level>2（Press[2]=1）的时钟周期个数；
                                                         0x0C-->被F0过滤条件选中的Packet数量；
                                                         0x0D-->被F1过滤条件选中的Packet数量；
                                                         0x0E~0x0F-->保留；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x11-->通过LUT过滤统计Packet中的有效Byte数量；
                                                         0x12-->通过LUT过滤统计Packet中的Byte数量（含无效Byte，作用于含byteenable的写操作）；
                                                         0x13-->通过filtersx（当counters_m_src中的m是奇数时，filterx表示filter0；当counters_m_src中的m是偶数时，filterx表示filter0）过滤统计Packet中的有效Byte数量；
                                                         0x14-->通过filtersx（当counters_m_src中的m是奇数时，filterx表示filter0；当counters_m_src中的m是偶数时，filterx表示filter0）过滤统计Packet中的Byte数量（含无效Byte）；
                                                         0x15~0x1F-->保留；
                                                         0x20~0x3F-->保留； */
        unsigned int  reserved       : 27; /* bit[5-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_0_SRC_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_0_SRC_counters_0_src_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_0_SRC_counters_0_src_END    (4)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_0_ALARMMODE_UNION
 结构说明  : SYSBUS_DDRC_PACKET_COUNTERS_0_ALARMMODE 寄存器结构定义。地址偏移量:0x213C，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_0_ALARMMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_0_ALARMMODE_counters_0_alarmmode_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_0_ALARMMODE_counters_0_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_0_VAL_UNION
 结构说明  : SYSBUS_DDRC_PACKET_COUNTERS_0_VAL 寄存器结构定义。地址偏移量:0x2140，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_0_val : 15; /* bit[0-14] : 当Counters_0_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 17; /* bit[15-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_0_VAL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_0_VAL_counters_0_val_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_0_VAL_counters_0_val_END    (14)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_1_SRC_UNION
 结构说明  : SYSBUS_DDRC_PACKET_COUNTERS_1_SRC 寄存器结构定义。地址偏移量:0x214C，初值:0x00000000，宽度:32
 寄存器说明: Counter的统计类型控制寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_1_src : 5;  /* bit[0-4] : 当CfgCtl寄存器中的Active=0时，该寄存器可配置，其它时间均不可配置：
                                                         0x00-->disabled计数器；
                                                         0x01-->Clock cycles；
                                                         0x02-->IDLE cycles；
                                                         0x03-->Transfer cycles；
                                                         0x04-->Busy cycles；
                                                         0x05-->Wait cycles；
                                                         0x06-->Packets个数统计；
                                                         0x07-->被LUT过滤选中的Packet个数统计；
                                                         0x08-->统计总的bytes数量；
                                                         0x09-->统计Pressure level>0的时钟周期个数；
                                                         0x0A-->统计Pressure level>1的时钟周期个数；
                                                         0x0B-->统计Pressure level>2（Press[2]=1）的时钟周期个数；
                                                         0x0C-->被F0过滤条件选中的Packet数量；
                                                         0x0D-->被F1过滤条件选中的Packet数量；
                                                         0x0E~0x0F-->保留；
                                                         0x10-->将counter_2N和counter_2N+1两个统计计数器进行串联，只有标号为奇数统计计数器可被串联，且只能将两个统计计数器进行串联；
                                                         0x11-->通过LUT过滤统计Packet中的有效Byte数量；
                                                         0x12-->通过LUT过滤统计Packet中的Byte数量（含无效Byte，作用于含byteenable的写操作）；
                                                         0x13-->通过filtersx（当counters_m_src中的m是奇数时，filterx表示filter0；当counters_m_src中的m是偶数时，filterx表示filter0）过滤统计Packet中的有效Byte数量；
                                                         0x14-->通过filtersx（当counters_m_src中的m是奇数时，filterx表示filter0；当counters_m_src中的m是偶数时，filterx表示filter0）过滤统计Packet中的Byte数量（含无效Byte）；
                                                         0x15~0x1F-->保留；
                                                         0x20~0x3F-->保留； */
        unsigned int  reserved       : 27; /* bit[5-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_1_SRC_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_1_SRC_counters_1_src_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_1_SRC_counters_1_src_END    (4)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_1_ALARMMODE_UNION
 结构说明  : SYSBUS_DDRC_PACKET_COUNTERS_1_ALARMMODE 寄存器结构定义。地址偏移量:0x2150，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_1_ALARMMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_1_ALARMMODE_counters_1_alarmmode_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_1_ALARMMODE_counters_1_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_1_VAL_UNION
 结构说明  : SYSBUS_DDRC_PACKET_COUNTERS_1_VAL 寄存器结构定义。地址偏移量:0x2154，初值:0x00000000，宽度:32
 寄存器说明: 统计计数器的统计值
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  counters_1_val : 15; /* bit[0-14] : 当Counters_1_Val达到最大之后，会保持不变直到被clear（串联计数器除外）； */
        unsigned int  reserved       : 17; /* bit[15-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_1_VAL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_1_VAL_counters_1_val_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_1_VAL_counters_1_val_END    (14)




/****************************************************************************
                     (4/9) CFGBUS
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_ID_COREID_UNION
 结构说明  : DJTAG_QOS_ID_COREID 寄存器结构定义。地址偏移量:0x0000，初值:0x84797C04，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_ID_COREID_coretypeid_START    (0)
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_ID_COREID_coretypeid_END      (7)
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_ID_COREID_corechecksum_START  (8)
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_ID_REVISIONID_UNION
 结构说明  : DJTAG_QOS_ID_REVISIONID 寄存器结构定义。地址偏移量:0x0004，初值:0x012D5300，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_ID_REVISIONID_userid_START     (0)
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_ID_REVISIONID_userid_END       (7)
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_ID_REVISIONID_flexnocid_START  (8)
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_PRIORITY_UNION
 结构说明  : DJTAG_QOS_PRIORITY 寄存器结构定义。地址偏移量:0x0008，初值:0x80000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_PRIORITY_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_PRIORITY_p0_START        (0)
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_PRIORITY_p0_END          (1)
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_PRIORITY_p1_START        (8)
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_PRIORITY_p1_END          (9)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_MODE_UNION
 结构说明  : DJTAG_QOS_MODE 寄存器结构定义。地址偏移量:0x000C，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_MODE_mode_START      (0)
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_MODE_mode_END        (1)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_EXTCONTROL_UNION
 结构说明  : DJTAG_QOS_EXTCONTROL 寄存器结构定义。地址偏移量:0x0018，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_EXTCONTROL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_EXTCONTROL_socketqosen_START  (0)
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_EXTCONTROL_socketqosen_END    (0)
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_EXTCONTROL_extthren_START     (1)
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_EXTCONTROL_extthren_END       (1)
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_EXTCONTROL_intclken_START     (2)
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_EXTCONTROL_intclken_END       (2)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_ID_COREID_UNION
 结构说明  : A7TOCFG_QOS_ID_COREID 寄存器结构定义。地址偏移量:0x0080，初值:0x4ADBA804，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_ID_COREID_coretypeid_START    (0)
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_ID_COREID_coretypeid_END      (7)
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_ID_COREID_corechecksum_START  (8)
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_ID_REVISIONID_UNION
 结构说明  : A7TOCFG_QOS_ID_REVISIONID 寄存器结构定义。地址偏移量:0x0084，初值:0x012D5300，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_ID_REVISIONID_userid_START     (0)
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_ID_REVISIONID_userid_END       (7)
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_ID_REVISIONID_flexnocid_START  (8)
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_PRIORITY_UNION
 结构说明  : A7TOCFG_QOS_PRIORITY 寄存器结构定义。地址偏移量:0x0088，初值:0x80000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_PRIORITY_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_PRIORITY_p0_START        (0)
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_PRIORITY_p0_END          (1)
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_PRIORITY_p1_START        (8)
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_PRIORITY_p1_END          (9)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_MODE_UNION
 结构说明  : A7TOCFG_QOS_MODE 寄存器结构定义。地址偏移量:0x008C，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_MODE_mode_START      (0)
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_MODE_mode_END        (1)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_EXTCONTROL_UNION
 结构说明  : A7TOCFG_QOS_EXTCONTROL 寄存器结构定义。地址偏移量:0x0098，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_EXTCONTROL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_EXTCONTROL_socketqosen_START  (0)
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_EXTCONTROL_socketqosen_END    (0)
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_EXTCONTROL_extthren_START     (1)
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_EXTCONTROL_extthren_END       (1)
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_EXTCONTROL_intclken_START     (2)
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_EXTCONTROL_intclken_END       (2)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_ID_COREID_UNION
 结构说明  : LPMCU_QOS_ID_COREID 寄存器结构定义。地址偏移量:0x0100，初值:0x6D480D04，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_ID_COREID_coretypeid_START    (0)
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_ID_COREID_coretypeid_END      (7)
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_ID_COREID_corechecksum_START  (8)
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_ID_REVISIONID_UNION
 结构说明  : LPMCU_QOS_ID_REVISIONID 寄存器结构定义。地址偏移量:0x0104，初值:0x012D5300，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_ID_REVISIONID_userid_START     (0)
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_ID_REVISIONID_userid_END       (7)
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_ID_REVISIONID_flexnocid_START  (8)
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_PRIORITY_UNION
 结构说明  : LPMCU_QOS_PRIORITY 寄存器结构定义。地址偏移量:0x0108，初值:0x80000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_PRIORITY_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_PRIORITY_p0_START        (0)
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_PRIORITY_p0_END          (1)
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_PRIORITY_p1_START        (8)
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_PRIORITY_p1_END          (9)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_MODE_UNION
 结构说明  : LPMCU_QOS_MODE 寄存器结构定义。地址偏移量:0x010C，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_MODE_mode_START      (0)
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_MODE_mode_END        (1)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_EXTCONTROL_UNION
 结构说明  : LPMCU_QOS_EXTCONTROL 寄存器结构定义。地址偏移量:0x0118，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_EXTCONTROL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_EXTCONTROL_socketqosen_START  (0)
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_EXTCONTROL_socketqosen_END    (0)
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_EXTCONTROL_extthren_START     (1)
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_EXTCONTROL_extthren_END       (1)
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_EXTCONTROL_intclken_START     (2)
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_EXTCONTROL_intclken_END       (2)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_CFGBUS_ERR_ID_COREID_UNION
 结构说明  : CFGBUS_ERR_ID_COREID 寄存器结构定义。地址偏移量:0x1C00，初值:0x08DA560D，宽度:32
 寄存器说明: CFG_BUS Err probe域ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_coreid : 32; /* bit[0-31]: error probe的域ID。 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_CFGBUS_ERR_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERR_ID_COREID_id_coreid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERR_ID_COREID_id_coreid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_CFGBUS_ERR_ID_REVISIONID_UNION
 结构说明  : CFGBUS_ERR_ID_REVISIONID 寄存器结构定义。地址偏移量:0x1C04，初值:0x012D5300，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_CFGBUS_ERR_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERR_ID_REVISIONID_id_revisionid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERR_ID_REVISIONID_id_revisionid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_CFGBUS_FAULTEN_UNION
 结构说明  : CFGBUS_FAULTEN 寄存器结构定义。地址偏移量:0x1C08，初值:0x00000000，宽度:32
 寄存器说明: CFG_BUS Err probe使能
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
} SOC_CFG_SYS_NOC_BUS_CFGBUS_FAULTEN_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_FAULTEN_faulten_START   (0)
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_FAULTEN_faulten_END     (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRVLD_UNION
 结构说明  : CFGBUS_ERRVLD 寄存器结构定义。地址偏移量:0x1C0C，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRVLD_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRVLD_errvld_START    (0)
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRVLD_errvld_END      (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRCLR_UNION
 结构说明  : CFGBUS_ERRCLR 寄存器结构定义。地址偏移量:0x1C10，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRCLR_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRCLR_errclr_START    (0)
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRCLR_errclr_END      (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG0_UNION
 结构说明  : CFGBUS_ERRLOG0 寄存器结构定义。地址偏移量:0x1C14，初值:0x80000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG0_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG0_lock_START      (0)
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG0_lock_END        (0)
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG0_opc_START       (1)
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG0_opc_END         (4)
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG0_errcode_START   (8)
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG0_errcode_END     (10)
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG0_len1_START      (16)
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG0_len1_END        (23)
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG0_format_START    (31)
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG0_format_END      (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG1_UNION
 结构说明  : CFGBUS_ERRLOG1 寄存器结构定义。地址偏移量:0x1C18，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG1_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG1_errlog1_START   (0)
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG1_errlog1_END     (13)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG3_UNION
 结构说明  : CFGBUS_ERRLOG3 寄存器结构定义。地址偏移量:0x1C20，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG3_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG3_errlog3_START  (0)
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG3_errlog3_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG5_UNION
 结构说明  : CFGBUS_ERRLOG5 寄存器结构定义。地址偏移量:0x1C28，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG5_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG5_errlog5_START   (0)
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG5_errlog5_END     (4)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG7_UNION
 结构说明  : CFGBUS_ERRLOG7 寄存器结构定义。地址偏移量:0x1C30，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG7_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG7_errlog7_START   (0)
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG7_errlog7_END     (0)




/****************************************************************************
                     (5/9) DMABUS
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_DMAC_QOS_ID_COREID_UNION
 结构说明  : DMAC_QOS_ID_COREID 寄存器结构定义。地址偏移量:0x0000，初值:0xD08E8504，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_DMAC_QOS_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_ID_COREID_coretypeid_START    (0)
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_ID_COREID_coretypeid_END      (7)
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_ID_COREID_corechecksum_START  (8)
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_DMAC_QOS_ID_REVISIONID_UNION
 结构说明  : DMAC_QOS_ID_REVISIONID 寄存器结构定义。地址偏移量:0x0004，初值:0x012D5300，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_DMAC_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_ID_REVISIONID_userid_START     (0)
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_ID_REVISIONID_userid_END       (7)
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_ID_REVISIONID_flexnocid_START  (8)
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_DMAC_QOS_PRIORITY_UNION
 结构说明  : DMAC_QOS_PRIORITY 寄存器结构定义。地址偏移量:0x0008，初值:0x80000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_DMAC_QOS_PRIORITY_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_PRIORITY_p0_START        (0)
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_PRIORITY_p0_END          (1)
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_PRIORITY_p1_START        (8)
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_PRIORITY_p1_END          (9)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_DMAC_QOS_MODE_UNION
 结构说明  : DMAC_QOS_MODE 寄存器结构定义。地址偏移量:0x000C，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_DMAC_QOS_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_MODE_mode_START      (0)
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_MODE_mode_END        (1)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_DMAC_QOS_EXTCONTROL_UNION
 结构说明  : DMAC_QOS_EXTCONTROL 寄存器结构定义。地址偏移量:0x0018，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_DMAC_QOS_EXTCONTROL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_EXTCONTROL_socketqosen_START  (0)
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_EXTCONTROL_socketqosen_END    (0)
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_EXTCONTROL_extthren_START     (1)
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_EXTCONTROL_extthren_END       (1)
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_EXTCONTROL_intclken_START     (2)
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_EXTCONTROL_intclken_END       (2)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAPTER_ID_COREID_UNION
 结构说明  : DMA2SYS_ADAPTER_ID_COREID 寄存器结构定义。地址偏移量:0x1000，初值:0x5B785B01，宽度:32
 寄存器说明: adapter域ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_coreid : 32; /* bit[0-31]: RateAdapter的域ID。 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAPTER_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAPTER_ID_COREID_id_coreid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAPTER_ID_COREID_id_coreid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAPTER_ID_REVISIONID_UNION
 结构说明  : DMA2SYS_ADAPTER_ID_REVISIONID 寄存器结构定义。地址偏移量:0x1004，初值:0x012D5300，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAPTER_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAPTER_ID_REVISIONID_id_revisionid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAPTER_ID_REVISIONID_id_revisionid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAPTERRATE_UNION
 结构说明  : DMA2SYS_ADAPTERRATE 寄存器结构定义。地址偏移量:0x1008，初值:0x00000000，宽度:32
 寄存器说明: Rate Adapter配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rate     : 10; /* bit[0-9]  : pre-computed throughout ratio */
        unsigned int  reserved : 22; /* bit[10-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAPTERRATE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAPTERRATE_rate_START      (0)
#define SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAPTERRATE_rate_END        (9)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAP_BYPASS_UNION
 结构说明  : DMA2SYS_ADAP_BYPASS 寄存器结构定义。地址偏移量:0x100C，初值:0x00000000，宽度:32
 寄存器说明: Rate Adapter bypass寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bypass   : 1;  /* bit[0]   : bypass the rate-adapter */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAP_BYPASS_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAP_BYPASS_bypass_START    (0)
#define SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAP_BYPASS_bypass_END      (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_DMABUS_ERR_ID_COREID_UNION
 结构说明  : DMABUS_ERR_ID_COREID 寄存器结构定义。地址偏移量:0x1C00，初值:0x08DA560D，宽度:32
 寄存器说明: DMABUS Err probe域ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_coreid : 32; /* bit[0-31]: error probe的域ID。 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_DMABUS_ERR_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERR_ID_COREID_id_coreid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERR_ID_COREID_id_coreid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_DMABUS_ERR_ID_REVISIONID_UNION
 结构说明  : DMABUS_ERR_ID_REVISIONID 寄存器结构定义。地址偏移量:0x1C04，初值:0x012D5300，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_DMABUS_ERR_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERR_ID_REVISIONID_id_revisionid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERR_ID_REVISIONID_id_revisionid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_DMABUS_FAULTEN_UNION
 结构说明  : DMABUS_FAULTEN 寄存器结构定义。地址偏移量:0x1C08，初值:0x00000000，宽度:32
 寄存器说明: DMABUS Err probe使能
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
} SOC_CFG_SYS_NOC_BUS_DMABUS_FAULTEN_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DMABUS_FAULTEN_faulten_START   (0)
#define SOC_CFG_SYS_NOC_BUS_DMABUS_FAULTEN_faulten_END     (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_DMABUS_ERRVLD_UNION
 结构说明  : DMABUS_ERRVLD 寄存器结构定义。地址偏移量:0x1C0C，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_DMABUS_ERRVLD_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRVLD_errvld_START    (0)
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRVLD_errvld_END      (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_DMABUS_ERRCLR_UNION
 结构说明  : DMABUS_ERRCLR 寄存器结构定义。地址偏移量:0x1C10，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_DMABUS_ERRCLR_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRCLR_errclr_START    (0)
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRCLR_errclr_END      (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG0_UNION
 结构说明  : DMABUS_ERRLOG0 寄存器结构定义。地址偏移量:0x1C14，初值:0x80000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG0_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG0_lock_START      (0)
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG0_lock_END        (0)
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG0_opc_START       (1)
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG0_opc_END         (4)
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG0_errcode_START   (8)
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG0_errcode_END     (10)
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG0_len1_START      (16)
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG0_len1_END        (23)
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG0_format_START    (31)
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG0_format_END      (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG1_UNION
 结构说明  : DMABUS_ERRLOG1 寄存器结构定义。地址偏移量:0x1C18，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG1_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG1_errlog1_START   (0)
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG1_errlog1_END     (13)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG3_UNION
 结构说明  : DMABUS_ERRLOG3 寄存器结构定义。地址偏移量:0x1C20，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG3_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG3_errlog3_START  (0)
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG3_errlog3_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG5_UNION
 结构说明  : DMABUS_ERRLOG5 寄存器结构定义。地址偏移量:0x1C28，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG5_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG5_errlog5_START   (0)
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG5_errlog5_END     (4)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG7_UNION
 结构说明  : DMABUS_ERRLOG7 寄存器结构定义。地址偏移量:0x1C30，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG7_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG7_errlog7_START   (0)
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG7_errlog7_END     (0)




/****************************************************************************
                     (6/9) DBGBUS
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_USB3_QOS_ID_COREID_UNION
 结构说明  : USB3_QOS_ID_COREID 寄存器结构定义。地址偏移量:0x0000，初值:0x28DA6D04，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_USB3_QOS_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_ID_COREID_coretypeid_START    (0)
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_ID_COREID_coretypeid_END      (7)
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_ID_COREID_corechecksum_START  (8)
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_USB3_QOS_ID_REVISIONID_UNION
 结构说明  : USB3_QOS_ID_REVISIONID 寄存器结构定义。地址偏移量:0x0004，初值:0x012D5300，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_USB3_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_ID_REVISIONID_userid_START     (0)
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_ID_REVISIONID_userid_END       (7)
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_ID_REVISIONID_flexnocid_START  (8)
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_USB3_QOS_PRIORITY_UNION
 结构说明  : USB3_QOS_PRIORITY 寄存器结构定义。地址偏移量:0x0008，初值:0x80000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_USB3_QOS_PRIORITY_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_PRIORITY_p0_START        (0)
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_PRIORITY_p0_END          (1)
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_PRIORITY_p1_START        (8)
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_PRIORITY_p1_END          (9)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_USB3_QOS_MODE_UNION
 结构说明  : USB3_QOS_MODE 寄存器结构定义。地址偏移量:0x000C，初值:0x00000001，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_USB3_QOS_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_MODE_mode_START      (0)
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_MODE_mode_END        (1)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_USB3_QOS_BANDWIDTH_UNION
 结构说明  : USB3_QOS_BANDWIDTH 寄存器结构定义。地址偏移量:0x0010，初值:0x0000042A，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bandwidth : 12; /* bit[0-11] : Defines the bandwidth threshold in 1/256th-byte-per-cycle units. In other words, the desired rate in MBps is divided by frequency in MHz of the NIU, and then multiplied by 256. */
        unsigned int  reserved  : 20; /* bit[12-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_USB3_QOS_BANDWIDTH_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_BANDWIDTH_bandwidth_START  (0)
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_BANDWIDTH_bandwidth_END    (11)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_USB3_QOS_SATURATION_UNION
 结构说明  : USB3_QOS_SATURATION 寄存器结构定义。地址偏移量:0x0014，初值:0x000003E8，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_USB3_QOS_SATURATION_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_SATURATION_saturation_START  (0)
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_SATURATION_saturation_END    (9)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_USB3_QOS_EXTCONTROL_UNION
 结构说明  : USB3_QOS_EXTCONTROL 寄存器结构定义。地址偏移量:0x0018，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_USB3_QOS_EXTCONTROL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_EXTCONTROL_socketqosen_START  (0)
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_EXTCONTROL_socketqosen_END    (0)
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_EXTCONTROL_extthren_START     (1)
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_EXTCONTROL_extthren_END       (1)
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_EXTCONTROL_intclken_START     (2)
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_EXTCONTROL_intclken_END       (2)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_ID_COREID_UNION
 结构说明  : SEC_P_QOS_ID_COREID 寄存器结构定义。地址偏移量:0x0080，初值:0x5F143B04，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_ID_COREID_coretypeid_START    (0)
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_ID_COREID_coretypeid_END      (7)
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_ID_COREID_corechecksum_START  (8)
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_ID_REVISIONID_UNION
 结构说明  : SEC_P_QOS_ID_REVISIONID 寄存器结构定义。地址偏移量:0x0084，初值:0x012D5300，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_ID_REVISIONID_userid_START     (0)
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_ID_REVISIONID_userid_END       (7)
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_ID_REVISIONID_flexnocid_START  (8)
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_PRIORITY_UNION
 结构说明  : SEC_P_QOS_PRIORITY 寄存器结构定义。地址偏移量:0x0088，初值:0x80000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_PRIORITY_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_PRIORITY_p0_START        (0)
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_PRIORITY_p0_END          (1)
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_PRIORITY_p1_START        (8)
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_PRIORITY_p1_END          (9)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_MODE_UNION
 结构说明  : SEC_P_QOS_MODE 寄存器结构定义。地址偏移量:0x008C，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_MODE_mode_START      (0)
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_MODE_mode_END        (1)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_EXTCONTROL_UNION
 结构说明  : SEC_P_QOS_EXTCONTROL 寄存器结构定义。地址偏移量:0x0098，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_EXTCONTROL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_EXTCONTROL_socketqosen_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_EXTCONTROL_socketqosen_END    (0)
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_EXTCONTROL_extthren_START     (1)
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_EXTCONTROL_extthren_END       (1)
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_EXTCONTROL_intclken_START     (2)
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_EXTCONTROL_intclken_END       (2)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_ID_COREID_UNION
 结构说明  : SEC_S_QOS_ID_COREID 寄存器结构定义。地址偏移量:0x0100，初值:0x468FF304，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_ID_COREID_coretypeid_START    (0)
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_ID_COREID_coretypeid_END      (7)
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_ID_COREID_corechecksum_START  (8)
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_ID_REVISIONID_UNION
 结构说明  : SEC_S_QOS_ID_REVISIONID 寄存器结构定义。地址偏移量:0x0104，初值:0x012D5300，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_ID_REVISIONID_userid_START     (0)
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_ID_REVISIONID_userid_END       (7)
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_ID_REVISIONID_flexnocid_START  (8)
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_PRIORITY_UNION
 结构说明  : SEC_S_QOS_PRIORITY 寄存器结构定义。地址偏移量:0x0108，初值:0x80000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_PRIORITY_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_PRIORITY_p0_START        (0)
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_PRIORITY_p0_END          (1)
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_PRIORITY_p1_START        (8)
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_PRIORITY_p1_END          (9)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_MODE_UNION
 结构说明  : SEC_S_QOS_MODE 寄存器结构定义。地址偏移量:0x010C，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_MODE_mode_START      (0)
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_MODE_mode_END        (1)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_EXTCONTROL_UNION
 结构说明  : SEC_S_QOS_EXTCONTROL 寄存器结构定义。地址偏移量:0x0118，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_EXTCONTROL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_EXTCONTROL_socketqosen_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_EXTCONTROL_socketqosen_END    (0)
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_EXTCONTROL_extthren_START     (1)
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_EXTCONTROL_extthren_END       (1)
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_EXTCONTROL_intclken_START     (2)
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_EXTCONTROL_intclken_END       (2)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SOCP_QOS_ID_COREID_UNION
 结构说明  : SOCP_QOS_ID_COREID 寄存器结构定义。地址偏移量:0x0180，初值:0xB0A55F04，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_SOCP_QOS_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_ID_COREID_coretypeid_START    (0)
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_ID_COREID_coretypeid_END      (7)
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_ID_COREID_corechecksum_START  (8)
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SOCP_QOS_ID_REVISIONID_UNION
 结构说明  : SOCP_QOS_ID_REVISIONID 寄存器结构定义。地址偏移量:0x0184，初值:0x012D5300，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_SOCP_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_ID_REVISIONID_userid_START     (0)
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_ID_REVISIONID_userid_END       (7)
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_ID_REVISIONID_flexnocid_START  (8)
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SOCP_QOS_PRIORITY_UNION
 结构说明  : SOCP_QOS_PRIORITY 寄存器结构定义。地址偏移量:0x0188，初值:0x80000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_SOCP_QOS_PRIORITY_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_PRIORITY_p0_START        (0)
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_PRIORITY_p0_END          (1)
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_PRIORITY_p1_START        (8)
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_PRIORITY_p1_END          (9)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SOCP_QOS_MODE_UNION
 结构说明  : SOCP_QOS_MODE 寄存器结构定义。地址偏移量:0x018C，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_SOCP_QOS_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_MODE_mode_START      (0)
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_MODE_mode_END        (1)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_SOCP_QOS_EXTCONTROL_UNION
 结构说明  : SOCP_QOS_EXTCONTROL 寄存器结构定义。地址偏移量:0x0198，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_SOCP_QOS_EXTCONTROL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_EXTCONTROL_socketqosen_START  (0)
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_EXTCONTROL_socketqosen_END    (0)
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_EXTCONTROL_extthren_START     (1)
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_EXTCONTROL_extthren_END       (1)
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_EXTCONTROL_intclken_START     (2)
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_EXTCONTROL_intclken_END       (2)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_ID_COREID_UNION
 结构说明  : CSSYS_QOS_ID_COREID 寄存器结构定义。地址偏移量:0x0200，初值:0xE7BD1904，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_ID_COREID_coretypeid_START    (0)
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_ID_COREID_coretypeid_END      (7)
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_ID_COREID_corechecksum_START  (8)
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_ID_REVISIONID_UNION
 结构说明  : CSSYS_QOS_ID_REVISIONID 寄存器结构定义。地址偏移量:0x0204，初值:0x012D5300，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_ID_REVISIONID_userid_START     (0)
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_ID_REVISIONID_userid_END       (7)
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_ID_REVISIONID_flexnocid_START  (8)
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_PRIORITY_UNION
 结构说明  : CSSYS_QOS_PRIORITY 寄存器结构定义。地址偏移量:0x0208，初值:0x80000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_PRIORITY_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_PRIORITY_p0_START        (0)
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_PRIORITY_p0_END          (1)
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_PRIORITY_p1_START        (8)
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_PRIORITY_p1_END          (9)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_MODE_UNION
 结构说明  : CSSYS_QOS_MODE 寄存器结构定义。地址偏移量:0x020C，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_MODE_mode_START      (0)
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_MODE_mode_END        (1)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_EXTCONTROL_UNION
 结构说明  : CSSYS_QOS_EXTCONTROL 寄存器结构定义。地址偏移量:0x0218，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_EXTCONTROL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_EXTCONTROL_socketqosen_START  (0)
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_EXTCONTROL_socketqosen_END    (0)
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_EXTCONTROL_extthren_START     (1)
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_EXTCONTROL_extthren_END       (1)
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_EXTCONTROL_intclken_START     (2)
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_EXTCONTROL_intclken_END       (2)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_ID_COREID_UNION
 结构说明  : PERF_STAT_QOS_ID_COREID 寄存器结构定义。地址偏移量:0x0280，初值:0xA9AEE404，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_ID_COREID_coretypeid_START    (0)
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_ID_COREID_coretypeid_END      (7)
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_ID_COREID_corechecksum_START  (8)
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_ID_REVISIONID_UNION
 结构说明  : PERF_STAT_QOS_ID_REVISIONID 寄存器结构定义。地址偏移量:0x0284，初值:0x012D5300，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_ID_REVISIONID_userid_START     (0)
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_ID_REVISIONID_userid_END       (7)
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_ID_REVISIONID_flexnocid_START  (8)
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_PRIORITY_UNION
 结构说明  : PERF_STAT_QOS_PRIORITY 寄存器结构定义。地址偏移量:0x0288，初值:0x80000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_PRIORITY_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_PRIORITY_p0_START        (0)
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_PRIORITY_p0_END          (1)
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_PRIORITY_p1_START        (8)
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_PRIORITY_p1_END          (9)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_MODE_UNION
 结构说明  : PERF_STAT_QOS_MODE 寄存器结构定义。地址偏移量:0x028C，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_MODE_mode_START      (0)
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_MODE_mode_END        (1)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_EXTCONTROL_UNION
 结构说明  : PERF_STAT_QOS_EXTCONTROL 寄存器结构定义。地址偏移量:0x0298，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_EXTCONTROL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_EXTCONTROL_socketqosen_START  (0)
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_EXTCONTROL_socketqosen_END    (0)
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_EXTCONTROL_extthren_START     (1)
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_EXTCONTROL_extthren_END       (1)
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_EXTCONTROL_intclken_START     (2)
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_EXTCONTROL_intclken_END       (2)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAPTER_ID_COREID_UNION
 结构说明  : DBG2SYS_ADAPTER_ID_COREID 寄存器结构定义。地址偏移量:0x1000，初值:0x223E2901，宽度:32
 寄存器说明: adapter域ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_coreid : 32; /* bit[0-31]: RateAdapter的域ID。 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAPTER_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAPTER_ID_COREID_id_coreid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAPTER_ID_COREID_id_coreid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAPTER_ID_REVISIONID_UNION
 结构说明  : DBG2SYS_ADAPTER_ID_REVISIONID 寄存器结构定义。地址偏移量:0x1004，初值:0x012D5300，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAPTER_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAPTER_ID_REVISIONID_id_revisionid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAPTER_ID_REVISIONID_id_revisionid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAPTERRATE_UNION
 结构说明  : DBG2SYS_ADAPTERRATE 寄存器结构定义。地址偏移量:0x1008，初值:0x00000000，宽度:32
 寄存器说明: Rate Adapter配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rate     : 10; /* bit[0-9]  : pre-computed throughout ratio */
        unsigned int  reserved : 22; /* bit[10-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAPTERRATE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAPTERRATE_rate_START      (0)
#define SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAPTERRATE_rate_END        (9)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAP_BYPASS_UNION
 结构说明  : DBG2SYS_ADAP_BYPASS 寄存器结构定义。地址偏移量:0x100C，初值:0x00000000，宽度:32
 寄存器说明: Rate Adapter bypass寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bypass   : 1;  /* bit[0]   : bypass the rate-adapter */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAP_BYPASS_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAP_BYPASS_bypass_START    (0)
#define SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAP_BYPASS_bypass_END      (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_DBGBUS_ERR_ID_COREID_UNION
 结构说明  : DBGBUS_ERR_ID_COREID 寄存器结构定义。地址偏移量:0x1C00，初值:0x08DA560D，宽度:32
 寄存器说明: DBGBUS Err probe域ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_coreid : 32; /* bit[0-31]: error probe的域ID。 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_DBGBUS_ERR_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERR_ID_COREID_id_coreid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERR_ID_COREID_id_coreid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_DBGBUS_ERR_ID_REVISIONID_UNION
 结构说明  : DBGBUS_ERR_ID_REVISIONID 寄存器结构定义。地址偏移量:0x1C04，初值:0x012D5300，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_DBGBUS_ERR_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERR_ID_REVISIONID_id_revisionid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERR_ID_REVISIONID_id_revisionid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_DBGBUS_FAULTEN_UNION
 结构说明  : DBGBUS_FAULTEN 寄存器结构定义。地址偏移量:0x1C08，初值:0x00000000，宽度:32
 寄存器说明: DBGBUS Err probe使能
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
} SOC_CFG_SYS_NOC_BUS_DBGBUS_FAULTEN_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_FAULTEN_faulten_START   (0)
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_FAULTEN_faulten_END     (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRVLD_UNION
 结构说明  : DBGBUS_ERRVLD 寄存器结构定义。地址偏移量:0x1C0C，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRVLD_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRVLD_errvld_START    (0)
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRVLD_errvld_END      (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRCLR_UNION
 结构说明  : DBGBUS_ERRCLR 寄存器结构定义。地址偏移量:0x1C10，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRCLR_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRCLR_errclr_START    (0)
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRCLR_errclr_END      (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG0_UNION
 结构说明  : DBGBUS_ERRLOG0 寄存器结构定义。地址偏移量:0x1C14，初值:0x80000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG0_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG0_lock_START      (0)
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG0_lock_END        (0)
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG0_opc_START       (1)
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG0_opc_END         (4)
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG0_errcode_START   (8)
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG0_errcode_END     (10)
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG0_len1_START      (16)
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG0_len1_END        (23)
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG0_format_START    (31)
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG0_format_END      (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG1_UNION
 结构说明  : DBGBUS_ERRLOG1 寄存器结构定义。地址偏移量:0x1C18，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG1_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG1_errlog1_START   (0)
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG1_errlog1_END     (13)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG3_UNION
 结构说明  : DBGBUS_ERRLOG3 寄存器结构定义。地址偏移量:0x1C20，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG3_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG3_errlog3_START  (0)
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG3_errlog3_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG5_UNION
 结构说明  : DBGBUS_ERRLOG5 寄存器结构定义。地址偏移量:0x1C28，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG5_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG5_errlog5_START   (0)
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG5_errlog5_END     (4)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG7_UNION
 结构说明  : DBGBUS_ERRLOG7 寄存器结构定义。地址偏移量:0x1C30，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG7_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG7_errlog7_START   (0)
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG7_errlog7_END     (0)




/****************************************************************************
                     (7/9) MMC1BUS
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_ID_COREID_UNION
 结构说明  : MMC1BUS_QOS_ID_COREID 寄存器结构定义。地址偏移量:0x0080，初值:0x6A610C04，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_ID_COREID_coretypeid_START    (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_ID_COREID_coretypeid_END      (7)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_ID_COREID_corechecksum_START  (8)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_ID_REVISIONID_UNION
 结构说明  : MMC1BUS_QOS_ID_REVISIONID 寄存器结构定义。地址偏移量:0x0084，初值:0x012D5300，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_ID_REVISIONID_userid_START     (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_ID_REVISIONID_userid_END       (7)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_ID_REVISIONID_flexnocid_START  (8)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_PRIORITY_UNION
 结构说明  : MMC1BUS_QOS_PRIORITY 寄存器结构定义。地址偏移量:0x0088，初值:0x80000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_PRIORITY_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_PRIORITY_p0_START        (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_PRIORITY_p0_END          (1)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_PRIORITY_p1_START        (8)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_PRIORITY_p1_END          (9)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_MODE_UNION
 结构说明  : MMC1BUS_QOS_MODE 寄存器结构定义。地址偏移量:0x008C，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_MODE_mode_START      (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_MODE_mode_END        (1)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_EXTCONTROL_UNION
 结构说明  : MMC1BUS_QOS_EXTCONTROL 寄存器结构定义。地址偏移量:0x0098，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_EXTCONTROL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_EXTCONTROL_socketqosen_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_EXTCONTROL_socketqosen_END    (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_EXTCONTROL_extthren_START     (1)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_EXTCONTROL_extthren_END       (1)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_EXTCONTROL_intclken_START     (2)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_EXTCONTROL_intclken_END       (2)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERR_ID_COREID_UNION
 结构说明  : MMC1BUS_ERR_ID_COREID 寄存器结构定义。地址偏移量:0x1C00，初值:0x08DA560D，宽度:32
 寄存器说明: MMC1BUS Err probe域ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_coreid : 32; /* bit[0-31]: error probe的域ID。 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERR_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERR_ID_COREID_id_coreid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERR_ID_COREID_id_coreid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERR_ID_REVISIONID_UNION
 结构说明  : MMC1BUS_ERR_ID_REVISIONID 寄存器结构定义。地址偏移量:0x1C04，初值:0x012D5300，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERR_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERR_ID_REVISIONID_id_revisionid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERR_ID_REVISIONID_id_revisionid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MMC1BUS_FAULTEN_UNION
 结构说明  : MMC1BUS_FAULTEN 寄存器结构定义。地址偏移量:0x1C08，初值:0x00000000，宽度:32
 寄存器说明: MMC1BUS Err probe使能
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
} SOC_CFG_SYS_NOC_BUS_MMC1BUS_FAULTEN_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_FAULTEN_faulten_START   (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_FAULTEN_faulten_END     (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRVLD_UNION
 结构说明  : MMC1BUS_ERRVLD 寄存器结构定义。地址偏移量:0x1C0C，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRVLD_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRVLD_errvld_START    (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRVLD_errvld_END      (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRCLR_UNION
 结构说明  : MMC1BUS_ERRCLR 寄存器结构定义。地址偏移量:0x1C10，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRCLR_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRCLR_errclr_START    (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRCLR_errclr_END      (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG0_UNION
 结构说明  : MMC1BUS_ERRLOG0 寄存器结构定义。地址偏移量:0x1C14，初值:0x80000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG0_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG0_lock_START      (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG0_lock_END        (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG0_opc_START       (1)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG0_opc_END         (4)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG0_errcode_START   (8)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG0_errcode_END     (10)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG0_len1_START      (16)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG0_len1_END        (23)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG0_format_START    (31)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG0_format_END      (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG1_UNION
 结构说明  : MMC1BUS_ERRLOG1 寄存器结构定义。地址偏移量:0x1C18，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG1_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG1_errlog1_START   (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG1_errlog1_END     (13)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG3_UNION
 结构说明  : MMC1BUS_ERRLOG3 寄存器结构定义。地址偏移量:0x1C20，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG3_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG3_errlog3_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG3_errlog3_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG5_UNION
 结构说明  : MMC1BUS_ERRLOG5 寄存器结构定义。地址偏移量:0x1C28，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG5_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG5_errlog5_START   (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG5_errlog5_END     (4)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG7_UNION
 结构说明  : MMC1BUS_ERRLOG7 寄存器结构定义。地址偏移量:0x1C30，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG7_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG7_errlog7_START   (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG7_errlog7_END     (0)




/****************************************************************************
                     (8/9) MMC0BUS 
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_ID_COREID_UNION
 结构说明  : EMMC0_QOS_ID_COREID 寄存器结构定义。地址偏移量:0x0000，初值:0xD7836304，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_ID_COREID_coretypeid_START    (0)
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_ID_COREID_coretypeid_END      (7)
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_ID_COREID_corechecksum_START  (8)
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_ID_REVISIONID_UNION
 结构说明  : EMMC0_QOS_ID_REVISIONID 寄存器结构定义。地址偏移量:0x0004，初值:0x012D5300，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_ID_REVISIONID_userid_START     (0)
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_ID_REVISIONID_userid_END       (7)
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_ID_REVISIONID_flexnocid_START  (8)
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_PRIORITY_UNION
 结构说明  : EMMC0_QOS_PRIORITY 寄存器结构定义。地址偏移量:0x0008，初值:0x80000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_PRIORITY_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_PRIORITY_p0_START        (0)
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_PRIORITY_p0_END          (1)
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_PRIORITY_p1_START        (8)
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_PRIORITY_p1_END          (9)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_MODE_UNION
 结构说明  : EMMC0_QOS_MODE 寄存器结构定义。地址偏移量:0x000C，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_MODE_mode_START      (0)
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_MODE_mode_END        (1)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_EXTCONTROL_UNION
 结构说明  : EMMC0_QOS_EXTCONTROL 寄存器结构定义。地址偏移量:0x0018，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_EXTCONTROL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_EXTCONTROL_socketqosen_START  (0)
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_EXTCONTROL_socketqosen_END    (0)
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_EXTCONTROL_extthren_START     (1)
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_EXTCONTROL_extthren_END       (1)
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_EXTCONTROL_intclken_START     (2)
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_EXTCONTROL_intclken_END       (2)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_ID_COREID_UNION
 结构说明  : EMMC1_QOS_ID_COREID 寄存器结构定义。地址偏移量:0x0080，初值:0x7CA53404，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_ID_COREID_coretypeid_START    (0)
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_ID_COREID_coretypeid_END      (7)
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_ID_COREID_corechecksum_START  (8)
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_ID_REVISIONID_UNION
 结构说明  : EMMC1_QOS_ID_REVISIONID 寄存器结构定义。地址偏移量:0x0084，初值:0x012D5300，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_ID_REVISIONID_userid_START     (0)
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_ID_REVISIONID_userid_END       (7)
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_ID_REVISIONID_flexnocid_START  (8)
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_PRIORITY_UNION
 结构说明  : EMMC1_QOS_PRIORITY 寄存器结构定义。地址偏移量:0x0088，初值:0x80000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_PRIORITY_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_PRIORITY_p0_START        (0)
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_PRIORITY_p0_END          (1)
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_PRIORITY_p1_START        (8)
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_PRIORITY_p1_END          (9)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_MODE_UNION
 结构说明  : EMMC1_QOS_MODE 寄存器结构定义。地址偏移量:0x008C，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_MODE_mode_START      (0)
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_MODE_mode_END        (1)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_EXTCONTROL_UNION
 结构说明  : EMMC1_QOS_EXTCONTROL 寄存器结构定义。地址偏移量:0x0098，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_EXTCONTROL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_EXTCONTROL_socketqosen_START  (0)
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_EXTCONTROL_socketqosen_END    (0)
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_EXTCONTROL_extthren_START     (1)
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_EXTCONTROL_extthren_END       (1)
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_EXTCONTROL_intclken_START     (2)
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_EXTCONTROL_intclken_END       (2)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_ID_COREID_UNION
 结构说明  : MMC0BUS_QOS_ID_COREID 寄存器结构定义。地址偏移量:0x0100，初值:0xA11D0C04，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_ID_COREID_coretypeid_START    (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_ID_COREID_coretypeid_END      (7)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_ID_COREID_corechecksum_START  (8)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_ID_REVISIONID_UNION
 结构说明  : MMC0BUS_QOS_ID_REVISIONID 寄存器结构定义。地址偏移量:0x0104，初值:0x012D5300，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_ID_REVISIONID_userid_START     (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_ID_REVISIONID_userid_END       (7)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_ID_REVISIONID_flexnocid_START  (8)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_PRIORITY_UNION
 结构说明  : MMC0BUS_QOS_PRIORITY 寄存器结构定义。地址偏移量:0x0108，初值:0x80000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_PRIORITY_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_PRIORITY_p0_START        (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_PRIORITY_p0_END          (1)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_PRIORITY_p1_START        (8)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_PRIORITY_p1_END          (9)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_MODE_UNION
 结构说明  : MMC0BUS_QOS_MODE 寄存器结构定义。地址偏移量:0x010C，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_MODE_mode_START      (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_MODE_mode_END        (1)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_EXTCONTROL_UNION
 结构说明  : MMC0BUS_QOS_EXTCONTROL 寄存器结构定义。地址偏移量:0x0118，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_EXTCONTROL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_EXTCONTROL_socketqosen_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_EXTCONTROL_socketqosen_END    (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_EXTCONTROL_extthren_START     (1)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_EXTCONTROL_extthren_END       (1)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_EXTCONTROL_intclken_START     (2)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_EXTCONTROL_intclken_END       (2)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAPTER_ID_COREID_UNION
 结构说明  : MMC0BUS_ADAPTER_ID_COREID 寄存器结构定义。地址偏移量:0x1000，初值:0xF33B3F01，宽度:32
 寄存器说明: adapter域ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_coreid : 32; /* bit[0-31]: RateAdapter的域ID。 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAPTER_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAPTER_ID_COREID_id_coreid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAPTER_ID_COREID_id_coreid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAPTER_ID_REVISIONID_UNION
 结构说明  : MMC0BUS_ADAPTER_ID_REVISIONID 寄存器结构定义。地址偏移量:0x1004，初值:0x012D5300，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAPTER_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAPTER_ID_REVISIONID_id_revisionid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAPTER_ID_REVISIONID_id_revisionid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAPTERRATE_UNION
 结构说明  : MMC0BUS_ADAPTERRATE 寄存器结构定义。地址偏移量:0x1008，初值:0x00000000，宽度:32
 寄存器说明: Rate Adapter配置寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rate     : 10; /* bit[0-9]  : pre-computed throughout ratio */
        unsigned int  reserved : 22; /* bit[10-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAPTERRATE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAPTERRATE_rate_START      (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAPTERRATE_rate_END        (9)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAP_BYPASS_UNION
 结构说明  : MMC0BUS_ADAP_BYPASS 寄存器结构定义。地址偏移量:0x100C，初值:0x00000000，宽度:32
 寄存器说明: Rate Adapter bypass寄存器
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bypass   : 1;  /* bit[0]   : bypass the rate-adapter */
        unsigned int  reserved : 31; /* bit[1-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAP_BYPASS_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAP_BYPASS_bypass_START    (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAP_BYPASS_bypass_END      (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERR_ID_COREID_UNION
 结构说明  : MMC0BUS_ERR_ID_COREID 寄存器结构定义。地址偏移量:0x1C00，初值:0x08DA560D，宽度:32
 寄存器说明: MMC0BUS Err probe域ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_coreid : 32; /* bit[0-31]: error probe的域ID。 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERR_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERR_ID_COREID_id_coreid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERR_ID_COREID_id_coreid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERR_ID_REVISIONID_UNION
 结构说明  : MMC0BUS_ERR_ID_REVISIONID 寄存器结构定义。地址偏移量:0x1C04，初值:0x012D5300，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERR_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERR_ID_REVISIONID_id_revisionid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERR_ID_REVISIONID_id_revisionid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MMC0BUS_FAULTEN_UNION
 结构说明  : MMC0BUS_FAULTEN 寄存器结构定义。地址偏移量:0x1C08，初值:0x00000000，宽度:32
 寄存器说明: MMC0BUS Err probe使能
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
} SOC_CFG_SYS_NOC_BUS_MMC0BUS_FAULTEN_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_FAULTEN_faulten_START   (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_FAULTEN_faulten_END     (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRVLD_UNION
 结构说明  : MMC0BUS_ERRVLD 寄存器结构定义。地址偏移量:0x1C0C，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRVLD_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRVLD_errvld_START    (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRVLD_errvld_END      (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRCLR_UNION
 结构说明  : MMC0BUS_ERRCLR 寄存器结构定义。地址偏移量:0x1C10，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRCLR_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRCLR_errclr_START    (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRCLR_errclr_END      (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG0_UNION
 结构说明  : MMC0BUS_ERRLOG0 寄存器结构定义。地址偏移量:0x1C14，初值:0x80000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG0_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG0_lock_START      (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG0_lock_END        (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG0_opc_START       (1)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG0_opc_END         (4)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG0_errcode_START   (8)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG0_errcode_END     (10)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG0_len1_START      (16)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG0_len1_END        (23)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG0_format_START    (31)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG0_format_END      (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG1_UNION
 结构说明  : MMC0BUS_ERRLOG1 寄存器结构定义。地址偏移量:0x1C18，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG1_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG1_errlog1_START   (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG1_errlog1_END     (13)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG3_UNION
 结构说明  : MMC0BUS_ERRLOG3 寄存器结构定义。地址偏移量:0x1C20，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG3_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG3_errlog3_START  (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG3_errlog3_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG5_UNION
 结构说明  : MMC0BUS_ERRLOG5 寄存器结构定义。地址偏移量:0x1C28，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG5_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG5_errlog5_START   (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG5_errlog5_END     (4)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG7_UNION
 结构说明  : MMC0BUS_ERRLOG7 寄存器结构定义。地址偏移量:0x1C30，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG7_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG7_errlog7_START   (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG7_errlog7_END     (0)




/****************************************************************************
                     (9/9) IVP32BUS
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_IVP32_QOS_ID_COREID_UNION
 结构说明  : IVP32_QOS_ID_COREID 寄存器结构定义。地址偏移量:0x0000，初值:0xD6AAAC04，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_IVP32_QOS_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_ID_COREID_coretypeid_START    (0)
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_ID_COREID_coretypeid_END      (7)
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_ID_COREID_corechecksum_START  (8)
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_IVP32_QOS_ID_REVISIONID_UNION
 结构说明  : IVP32_QOS_ID_REVISIONID 寄存器结构定义。地址偏移量:0x0004，初值:0x012D5300，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_IVP32_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_ID_REVISIONID_userid_START     (0)
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_ID_REVISIONID_userid_END       (7)
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_ID_REVISIONID_flexnocid_START  (8)
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_IVP32_QOS_PRIORITY_UNION
 结构说明  : IVP32_QOS_PRIORITY 寄存器结构定义。地址偏移量:0x0008，初值:0x80000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_IVP32_QOS_PRIORITY_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_PRIORITY_p0_START        (0)
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_PRIORITY_p0_END          (1)
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_PRIORITY_p1_START        (8)
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_PRIORITY_p1_END          (9)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_IVP32_QOS_MODE_UNION
 结构说明  : IVP32_QOS_MODE 寄存器结构定义。地址偏移量:0x000C，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_IVP32_QOS_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_MODE_mode_START      (0)
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_MODE_mode_END        (1)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_IVP32_QOS_EXTCONTROL_UNION
 结构说明  : IVP32_QOS_EXTCONTROL 寄存器结构定义。地址偏移量:0x0018，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_IVP32_QOS_EXTCONTROL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_EXTCONTROL_socketqosen_START  (0)
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_EXTCONTROL_socketqosen_END    (0)
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_EXTCONTROL_extthren_START     (1)
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_EXTCONTROL_extthren_END       (1)
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_EXTCONTROL_intclken_START     (2)
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_EXTCONTROL_intclken_END       (2)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_IVP32_ERR_ID_COREID_UNION
 结构说明  : IVP32_ERR_ID_COREID 寄存器结构定义。地址偏移量:0x1C00，初值:0x08DA560D，宽度:32
 寄存器说明: IVP32 Err probe域ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_coreid : 32; /* bit[0-31]: IVP32的error probe的域ID。 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_IVP32_ERR_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERR_ID_COREID_id_coreid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERR_ID_COREID_id_coreid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_IVP32_ERR_ID_REVISIONID_UNION
 结构说明  : IVP32_ERR_ID_REVISIONID 寄存器结构定义。地址偏移量:0x1C04，初值:0x012D5300，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_IVP32_ERR_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERR_ID_REVISIONID_id_revisionid_START  (0)
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERR_ID_REVISIONID_id_revisionid_END    (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_IVP32_FAULTEN_UNION
 结构说明  : IVP32_FAULTEN 寄存器结构定义。地址偏移量:0x1C08，初值:0x00000000，宽度:32
 寄存器说明: IVP32 Err probe使能
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
} SOC_CFG_SYS_NOC_BUS_IVP32_FAULTEN_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_IVP32_FAULTEN_faulten_START   (0)
#define SOC_CFG_SYS_NOC_BUS_IVP32_FAULTEN_faulten_END     (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_IVP32_ERRVLD_UNION
 结构说明  : IVP32_ERRVLD 寄存器结构定义。地址偏移量:0x1C0C，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_IVP32_ERRVLD_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRVLD_errvld_START    (0)
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRVLD_errvld_END      (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_IVP32_ERRCLR_UNION
 结构说明  : IVP32_ERRCLR 寄存器结构定义。地址偏移量:0x1C10，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_IVP32_ERRCLR_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRCLR_errclr_START    (0)
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRCLR_errclr_END      (0)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG0_UNION
 结构说明  : IVP32_ERRLOG0 寄存器结构定义。地址偏移量:0x1C14，初值:0x80000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG0_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG0_lock_START      (0)
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG0_lock_END        (0)
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG0_opc_START       (1)
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG0_opc_END         (4)
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG0_errcode_START   (8)
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG0_errcode_END     (10)
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG0_len1_START      (16)
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG0_len1_END        (23)
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG0_format_START    (31)
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG0_format_END      (31)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG1_UNION
 结构说明  : IVP32_ERRLOG1 寄存器结构定义。地址偏移量:0x1C18，初值:0x00000000，宽度:32
 寄存器说明: Error log1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errlog1  : 22; /* bit[0-21] : RouteId：路由信息，各bit含义如下
                                                    [21:17]-->Initiator Flow ID，用于表示发起访问的master；
                                                    [16:12]-->target Flow ID，用于表示被访问的slave；
                                                    [11:9]-->Target NIU SubRange；
                                                    [8:0]-->Seq ID，Transaction标记； */
        unsigned int  reserved : 10; /* bit[22-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG1_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG1_errlog1_START   (0)
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG1_errlog1_END     (21)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG3_UNION
 结构说明  : IVP32_ERRLOG3 寄存器结构定义。地址偏移量:0x1C20，初值:0x00000000，宽度:32
 寄存器说明: Error log3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errlog3  : 31; /* bit[0-30] : 访问地址值 */
        unsigned int  reserved : 1;  /* bit[31-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG3_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG3_errlog3_START   (0)
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG3_errlog3_END     (30)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG5_UNION
 结构说明  : IVP32_ERRLOG5 寄存器结构定义。地址偏移量:0x1C28，初值:0x00000000，宽度:32
 寄存器说明: Error log5
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  errlog5  : 17; /* bit[0-16] : User信号值 */
        unsigned int  reserved : 15; /* bit[17-31]: 保留 */
    } reg;
} SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG5_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG5_errlog5_START   (0)
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG5_errlog5_END     (16)


/*****************************************************************************
 结构名    : SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG7_UNION
 结构说明  : IVP32_ERRLOG7 寄存器结构定义。地址偏移量:0x1C30，初值:0x00000000，宽度:32
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
} SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG7_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG7_errlog7_START   (0)
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG7_errlog7_END     (0)






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

#endif /* end of soc_cfg_sys_noc_bus_interface.h */
