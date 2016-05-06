/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_vcodec_bus_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:23:23
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_VCODEC_BUS.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_VCODEC_BUS_INTERFACE_H__
#define __SOC_VCODEC_BUS_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/3) NOC_PERI_VCODEC
 ****************************************************************************/
/* 寄存器说明：adapter域ID
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_ADAPTER_ID_COREID_UNION */
#define SOC_VCODEC_BUS_VENC_ADAPTER_ID_COREID_ADDR(base) ((base) + (0x1000))

/* 寄存器说明：总线代码版本寄存器
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_ADAPTER_ID_REVISIONID_UNION */
#define SOC_VCODEC_BUS_VENC_ADAPTER_ID_REVISIONID_ADDR(base) ((base) + (0x1004))

/* 寄存器说明：Rate Adapter配置寄存器
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_ADAPTERRATE_UNION */
#define SOC_VCODEC_BUS_VENC_ADAPTERRATE_ADDR(base)    ((base) + (0x1008))

/* 寄存器说明：Rate Adapter bypass寄存器
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_ADAP_BYPASS_UNION */
#define SOC_VCODEC_BUS_VENC_ADAP_BYPASS_ADDR(base)    ((base) + (0x100C))

/* 寄存器说明：adapter域ID
   位域定义UNION结构:  SOC_VCODEC_BUS_VDEC_ADAPTER_ID_COREID_UNION */
#define SOC_VCODEC_BUS_VDEC_ADAPTER_ID_COREID_ADDR(base) ((base) + (0x1080))

/* 寄存器说明：总线代码版本寄存器
   位域定义UNION结构:  SOC_VCODEC_BUS_VDEC_ADAPTER_ID_REVISIONID_UNION */
#define SOC_VCODEC_BUS_VDEC_ADAPTER_ID_REVISIONID_ADDR(base) ((base) + (0x1084))

/* 寄存器说明：Rate Adapter配置寄存器
   位域定义UNION结构:  SOC_VCODEC_BUS_VDEC_ADAPTERRATE_UNION */
#define SOC_VCODEC_BUS_VDEC_ADAPTERRATE_ADDR(base)    ((base) + (0x1088))

/* 寄存器说明：Rate Adapter bypass寄存器
   位域定义UNION结构:  SOC_VCODEC_BUS_VDEC_ADAP_BYPASS_UNION */
#define SOC_VCODEC_BUS_VDEC_ADAP_BYPASS_ADDR(base)    ((base) + (0x108C))

/* 寄存器说明：VCODEC_BUS Err probe域ID
   位域定义UNION结构:  SOC_VCODEC_BUS_ERR_ID_COREID_UNION */
#define SOC_VCODEC_BUS_ERR_ID_COREID_ADDR(base)       ((base) + (0x1C00))

/* 寄存器说明：总线代码版本寄存器
   位域定义UNION结构:  SOC_VCODEC_BUS_ID_REVISIONID_UNION */
#define SOC_VCODEC_BUS_ID_REVISIONID_ADDR(base)       ((base) + (0x1C04))

/* 寄存器说明：VCODEC_BUS Err probe使能
   位域定义UNION结构:  SOC_VCODEC_BUS_FAULTEN_UNION */
#define SOC_VCODEC_BUS_FAULTEN_ADDR(base)             ((base) + (0x1C08))

/* 寄存器说明：Error log有效指示寄存器
   位域定义UNION结构:  SOC_VCODEC_BUS_ERRVLD_UNION */
#define SOC_VCODEC_BUS_ERRVLD_ADDR(base)              ((base) + (0x1C0C))

/* 寄存器说明：中断清除寄存器
   位域定义UNION结构:  SOC_VCODEC_BUS_ERRCLR_UNION */
#define SOC_VCODEC_BUS_ERRCLR_ADDR(base)              ((base) + (0x1C10))

/* 寄存器说明：Error log0
   位域定义UNION结构:  SOC_VCODEC_BUS_ERRLOG0_UNION */
#define SOC_VCODEC_BUS_ERRLOG0_ADDR(base)             ((base) + (0x1C14))

/* 寄存器说明：Error log1
   位域定义UNION结构:  SOC_VCODEC_BUS_ERRLOG1_UNION */
#define SOC_VCODEC_BUS_ERRLOG1_ADDR(base)             ((base) + (0x1C18))

/* 寄存器说明：Error log3
   位域定义UNION结构:  SOC_VCODEC_BUS_ERRLOG3_UNION */
#define SOC_VCODEC_BUS_ERRLOG3_ADDR(base)             ((base) + (0x1C20))

/* 寄存器说明：Error log5
   位域定义UNION结构:  SOC_VCODEC_BUS_ERRLOG5_UNION */
#define SOC_VCODEC_BUS_ERRLOG5_ADDR(base)             ((base) + (0x1C28))

/* 寄存器说明：Error log7
   位域定义UNION结构:  SOC_VCODEC_BUS_ERRLOG7_UNION */
#define SOC_VCODEC_BUS_ERRLOG7_ADDR(base)             ((base) + (0x1C30))



/****************************************************************************
                     (2/3) NOC_VENC
 ****************************************************************************/
/* 寄存器说明：
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_QOS_ID_COREID_UNION */
#define SOC_VCODEC_BUS_VENC_QOS_ID_COREID_ADDR(base)  ((base) + (0x0100))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_QOS_ID_REVISIONID_UNION */
#define SOC_VCODEC_BUS_VENC_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0104))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_QOS_PRIORITY_UNION */
#define SOC_VCODEC_BUS_VENC_QOS_PRIORITY_ADDR(base)   ((base) + (0x0108))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_QOS_MODE_UNION */
#define SOC_VCODEC_BUS_VENC_QOS_MODE_ADDR(base)       ((base) + (0x010C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_QOS_BANDWIDTH_UNION */
#define SOC_VCODEC_BUS_VENC_QOS_BANDWIDTH_ADDR(base)  ((base) + (0x0110))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_QOS_SATURATION_UNION */
#define SOC_VCODEC_BUS_VENC_QOS_SATURATION_ADDR(base) ((base) + (0x0114))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_QOS_EXTCONTROL_UNION */
#define SOC_VCODEC_BUS_VENC_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0118))

/* 寄存器说明：VENC TransactionStatFilter域ID
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_TRANS_F_ID_COREID_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_F_ID_COREID_ADDR(base) ((base) + (0x8000))

/* 寄存器说明：代码版本
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_TRANS_F_ID_REVISIONID_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_F_ID_REVISIONID_ADDR(base) ((base) + (0x8004))

/* 寄存器说明：VENC Transaction Probe的Filter工作模式配置寄存器
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_TRANS_F_MODE_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_F_MODE_ADDR(base)   ((base) + (0x8008))

/* 寄存器说明：地址过滤基地址
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_TRANS_F_ADDRBASE_LOW_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_F_ADDRBASE_LOW_ADDR(base) ((base) + (0x800C))

/* 寄存器说明：地址过滤基地址
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_TRANS_F_ADDRBASE_HIGH_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_F_ADDRBASE_HIGH_ADDR(base) ((base) + (0x8010))

/* 寄存器说明：地址过滤窗口
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_TRANS_F_ADDRWINDOWSIZE_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_F_ADDRWINDOWSIZE_ADDR(base) ((base) + (0x8014))

/* 寄存器说明：VENC的Transaction Probe的Opcode过滤条件
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_TRANS_F_OPCODE_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_F_OPCODE_ADDR(base) ((base) + (0x8020))

/* 寄存器说明：VENC的Transaction Probe的User过滤条件
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_TRANS_F_USERBASE_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_F_USERBASE_ADDR(base) ((base) + (0x8024))

/* 寄存器说明：VENC的Transaction Probe的User过滤条件Mask
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_TRANS_F_USERMASK_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_F_USERMASK_ADDR(base) ((base) + (0x8028))

/* 寄存器说明：VENC的Transaction Probe的安全过滤条件
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_TRANS_F_SECURITYBASE_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_F_SECURITYBASE_ADDR(base) ((base) + (0x802C))

/* 寄存器说明：VENC的Transaction Probe的安全过滤条件Mask
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_TRANS_F_SECURITYMASK_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_F_SECURITYMASK_ADDR(base) ((base) + (0x8030))

/* 寄存器说明：VENC TransactionStatProfilter域ID
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_TRANS_P_ID_COREID_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_P_ID_COREID_ADDR(base) ((base) + (0x8080))

/* 寄存器说明：代码版本
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_TRANS_P_ID_REVISIONID_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_P_ID_REVISIONID_ADDR(base) ((base) + (0x8084))

/* 寄存器说明：transaction Probe的counter使能配置
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_TRANS_P_EN_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_P_EN_ADDR(base)     ((base) + (0x8088))

/* 寄存器说明：VENC Transaction Probe的工作模式配置
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_TRANS_P_MODE_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_P_MODE_ADDR(base)   ((base) + (0x808C))

/* 寄存器说明：统计计数器溢出状态
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_TRANS_P_OVERFLOWSTATUS_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_P_OVERFLOWSTATUS_ADDR(base) ((base) + (0x80EC))

/* 寄存器说明：统计计数器溢出状态清零
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_TRANS_P_OVERFLOWRESET_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_P_OVERFLOWRESET_ADDR(base) ((base) + (0x80F0))

/* 寄存器说明：outstanding统计技术工作模式配置
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_TRANS_P_PENDINGEVENTMODE_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_P_PENDINGEVENTMODE_ADDR(base) ((base) + (0x80F4))

/* 寄存器说明：latency统计系数配置
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_TRANS_P_PRESCALER_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_P_PRESCALER_ADDR(base) ((base) + (0x80F8))

/* 寄存器说明：VENC Transaction probe域ID
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_TRANS_M_ID_COREID_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_ID_COREID_ADDR(base) ((base) + (0x8400))

/* 寄存器说明：总线代码版本寄存器
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_TRANS_M_ID_REVISIONID_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_ID_REVISIONID_ADDR(base) ((base) + (0x8404))

/* 寄存器说明：Transaction Probe全局控制寄存器
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_TRANS_M_MAINCTL_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_MAINCTL_ADDR(base) ((base) + (0x8408))

/* 寄存器说明：Packet Probe使能寄存器
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_TRANS_M_CFGCTL_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_CFGCTL_ADDR(base) ((base) + (0x840C))

/* 寄存器说明：统计周期配置寄存器
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_TRANS_M_STATPERIOD_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_STATPERIOD_ADDR(base) ((base) + (0x8424))

/* 寄存器说明：手动带宽统计计时开始使能
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_TRANS_M_STATGO_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_STATGO_ADDR(base) ((base) + (0x8428))

/* 寄存器说明：统计计数最小告警阈值
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMMIN_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMMIN_ADDR(base) ((base) + (0x842C))

/* 寄存器说明：统计计数器最大告警阈值
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMMAX_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMMAX_ADDR(base) ((base) + (0x8430))

/* 寄存器说明：告警状态寄存器
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMSTATUS_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMSTATUS_ADDR(base) ((base) + (0x8434))

/* 寄存器说明：告警状态清除寄存器
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMCLR_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMCLR_ADDR(base) ((base) + (0x8438))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_0_SRC_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_0_SRC_ADDR(base) ((base) + (0x8538))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_0_ALARMMODE_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_0_ALARMMODE_ADDR(base) ((base) + (0x853C))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_0_VAL_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_0_VAL_ADDR(base) ((base) + (0x8540))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_1_SRC_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_1_SRC_ADDR(base) ((base) + (0x854C))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_1_ALARMMODE_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_1_ALARMMODE_ADDR(base) ((base) + (0x8550))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_1_VAL_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_1_VAL_ADDR(base) ((base) + (0x8554))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_2_SRC_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_2_SRC_ADDR(base) ((base) + (0x8560))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_2_ALARMMODE_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_2_ALARMMODE_ADDR(base) ((base) + (0x8564))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_2_VAL_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_2_VAL_ADDR(base) ((base) + (0x8568))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_3_SRC_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_3_SRC_ADDR(base) ((base) + (0x8574))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_3_ALARMMODE_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_3_ALARMMODE_ADDR(base) ((base) + (0x8578))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_3_VAL_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_3_VAL_ADDR(base) ((base) + (0x857C))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_4_SRC_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_4_SRC_ADDR(base) ((base) + (0x8588))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_4_ALARMMODE_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_4_ALARMMODE_ADDR(base) ((base) + (0x858C))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_4_VAL_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_4_VAL_ADDR(base) ((base) + (0x8590))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_5_SRC_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_5_SRC_ADDR(base) ((base) + (0x859C))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_5_ALARMMODE_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_5_ALARMMODE_ADDR(base) ((base) + (0x85A0))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_5_VAL_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_5_VAL_ADDR(base) ((base) + (0x85A4))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_6_SRC_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_6_SRC_ADDR(base) ((base) + (0x85B0))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_6_ALARMMODE_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_6_ALARMMODE_ADDR(base) ((base) + (0x85B4))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_6_VAL_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_6_VAL_ADDR(base) ((base) + (0x85B8))

/* 寄存器说明：Counter的统计类型控制寄存器
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_7_SRC_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_7_SRC_ADDR(base) ((base) + (0x85C4))

/* 寄存器说明：告警中断产生配置寄存器
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_7_ALARMMODE_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_7_ALARMMODE_ADDR(base) ((base) + (0x85C8))

/* 寄存器说明：统计计数器的统计值
   位域定义UNION结构:  SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_7_VAL_UNION */
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_7_VAL_ADDR(base) ((base) + (0x85CC))



/****************************************************************************
                     (3/3) NOC_VDEC
 ****************************************************************************/
/* 寄存器说明：
   位域定义UNION结构:  SOC_VCODEC_BUS_VDEC_QOS_ID_COREID_UNION */
#define SOC_VCODEC_BUS_VDEC_QOS_ID_COREID_ADDR(base)  ((base) + (0x0000))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VCODEC_BUS_VDEC_QOS_ID_REVISIONID_UNION */
#define SOC_VCODEC_BUS_VDEC_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0004))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VCODEC_BUS_VDEC_QOS_PRIORITY_UNION */
#define SOC_VCODEC_BUS_VDEC_QOS_PRIORITY_ADDR(base)   ((base) + (0x0008))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VCODEC_BUS_VDEC_QOS_MODE_UNION */
#define SOC_VCODEC_BUS_VDEC_QOS_MODE_ADDR(base)       ((base) + (0x000C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VCODEC_BUS_VDEC_QOS_BANDWIDTH_UNION */
#define SOC_VCODEC_BUS_VDEC_QOS_BANDWIDTH_ADDR(base)  ((base) + (0x0010))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VCODEC_BUS_VDEC_QOS_SATURATION_UNION */
#define SOC_VCODEC_BUS_VDEC_QOS_SATURATION_ADDR(base) ((base) + (0x0014))

/* 寄存器说明：
   位域定义UNION结构:  SOC_VCODEC_BUS_VDEC_QOS_EXTCONTROL_UNION */
#define SOC_VCODEC_BUS_VDEC_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0018))





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
                     (1/3) NOC_PERI_VCODEC
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_ADAPTER_ID_COREID_UNION
 结构说明  : VENC_ADAPTER_ID_COREID 寄存器结构定义。地址偏移量:0x1000，初值:0xA247F101，宽度:32
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
} SOC_VCODEC_BUS_VENC_ADAPTER_ID_COREID_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_ADAPTER_ID_COREID_id_coreid_START  (0)
#define SOC_VCODEC_BUS_VENC_ADAPTER_ID_COREID_id_coreid_END    (31)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_ADAPTER_ID_REVISIONID_UNION
 结构说明  : VENC_ADAPTER_ID_REVISIONID 寄存器结构定义。地址偏移量:0x1004，初值:0x012D5300，宽度:32
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
} SOC_VCODEC_BUS_VENC_ADAPTER_ID_REVISIONID_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_ADAPTER_ID_REVISIONID_id_revisionid_START  (0)
#define SOC_VCODEC_BUS_VENC_ADAPTER_ID_REVISIONID_id_revisionid_END    (31)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_ADAPTERRATE_UNION
 结构说明  : VENC_ADAPTERRATE 寄存器结构定义。地址偏移量:0x1008，初值:0x00000000，宽度:32
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
} SOC_VCODEC_BUS_VENC_ADAPTERRATE_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_ADAPTERRATE_rate_START      (0)
#define SOC_VCODEC_BUS_VENC_ADAPTERRATE_rate_END        (9)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_ADAP_BYPASS_UNION
 结构说明  : VENC_ADAP_BYPASS 寄存器结构定义。地址偏移量:0x100C，初值:0x00000000，宽度:32
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
} SOC_VCODEC_BUS_VENC_ADAP_BYPASS_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_ADAP_BYPASS_bypass_START    (0)
#define SOC_VCODEC_BUS_VENC_ADAP_BYPASS_bypass_END      (0)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VDEC_ADAPTER_ID_COREID_UNION
 结构说明  : VDEC_ADAPTER_ID_COREID 寄存器结构定义。地址偏移量:0x1080，初值:0x6539FD01，宽度:32
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
} SOC_VCODEC_BUS_VDEC_ADAPTER_ID_COREID_UNION;
#endif
#define SOC_VCODEC_BUS_VDEC_ADAPTER_ID_COREID_id_coreid_START  (0)
#define SOC_VCODEC_BUS_VDEC_ADAPTER_ID_COREID_id_coreid_END    (31)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VDEC_ADAPTER_ID_REVISIONID_UNION
 结构说明  : VDEC_ADAPTER_ID_REVISIONID 寄存器结构定义。地址偏移量:0x1084，初值:0x012D5300，宽度:32
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
} SOC_VCODEC_BUS_VDEC_ADAPTER_ID_REVISIONID_UNION;
#endif
#define SOC_VCODEC_BUS_VDEC_ADAPTER_ID_REVISIONID_id_revisionid_START  (0)
#define SOC_VCODEC_BUS_VDEC_ADAPTER_ID_REVISIONID_id_revisionid_END    (31)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VDEC_ADAPTERRATE_UNION
 结构说明  : VDEC_ADAPTERRATE 寄存器结构定义。地址偏移量:0x1088，初值:0x00000000，宽度:32
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
} SOC_VCODEC_BUS_VDEC_ADAPTERRATE_UNION;
#endif
#define SOC_VCODEC_BUS_VDEC_ADAPTERRATE_rate_START      (0)
#define SOC_VCODEC_BUS_VDEC_ADAPTERRATE_rate_END        (9)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VDEC_ADAP_BYPASS_UNION
 结构说明  : VDEC_ADAP_BYPASS 寄存器结构定义。地址偏移量:0x108C，初值:0x00000000，宽度:32
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
} SOC_VCODEC_BUS_VDEC_ADAP_BYPASS_UNION;
#endif
#define SOC_VCODEC_BUS_VDEC_ADAP_BYPASS_bypass_START    (0)
#define SOC_VCODEC_BUS_VDEC_ADAP_BYPASS_bypass_END      (0)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_ERR_ID_COREID_UNION
 结构说明  : ERR_ID_COREID 寄存器结构定义。地址偏移量:0x1C00，初值:0xA67A1B0D，宽度:32
 寄存器说明: VCODEC_BUS Err probe域ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_coreid : 32; /* bit[0-31]: SYS_BUS的error probe的域ID。 */
    } reg;
} SOC_VCODEC_BUS_ERR_ID_COREID_UNION;
#endif
#define SOC_VCODEC_BUS_ERR_ID_COREID_id_coreid_START  (0)
#define SOC_VCODEC_BUS_ERR_ID_COREID_id_coreid_END    (31)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_ID_REVISIONID_UNION
 结构说明  : ID_REVISIONID 寄存器结构定义。地址偏移量:0x1C04，初值:0x012D5300，宽度:32
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
} SOC_VCODEC_BUS_ID_REVISIONID_UNION;
#endif
#define SOC_VCODEC_BUS_ID_REVISIONID_id_revisionid_START  (0)
#define SOC_VCODEC_BUS_ID_REVISIONID_id_revisionid_END    (31)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_FAULTEN_UNION
 结构说明  : FAULTEN 寄存器结构定义。地址偏移量:0x1C08，初值:0x00000000，宽度:32
 寄存器说明: VCODEC_BUS Err probe使能
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
} SOC_VCODEC_BUS_FAULTEN_UNION;
#endif
#define SOC_VCODEC_BUS_FAULTEN_faulten_START   (0)
#define SOC_VCODEC_BUS_FAULTEN_faulten_END     (0)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_ERRVLD_UNION
 结构说明  : ERRVLD 寄存器结构定义。地址偏移量:0x1C0C，初值:0x00000000，宽度:32
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
} SOC_VCODEC_BUS_ERRVLD_UNION;
#endif
#define SOC_VCODEC_BUS_ERRVLD_errvld_START    (0)
#define SOC_VCODEC_BUS_ERRVLD_errvld_END      (0)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_ERRCLR_UNION
 结构说明  : ERRCLR 寄存器结构定义。地址偏移量:0x1C10，初值:0x00000000，宽度:32
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
} SOC_VCODEC_BUS_ERRCLR_UNION;
#endif
#define SOC_VCODEC_BUS_ERRCLR_errclr_START    (0)
#define SOC_VCODEC_BUS_ERRCLR_errclr_END      (0)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_ERRLOG0_UNION
 结构说明  : ERRLOG0 寄存器结构定义。地址偏移量:0x1C14，初值:0x80000000，宽度:32
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
} SOC_VCODEC_BUS_ERRLOG0_UNION;
#endif
#define SOC_VCODEC_BUS_ERRLOG0_lock_START      (0)
#define SOC_VCODEC_BUS_ERRLOG0_lock_END        (0)
#define SOC_VCODEC_BUS_ERRLOG0_opc_START       (1)
#define SOC_VCODEC_BUS_ERRLOG0_opc_END         (4)
#define SOC_VCODEC_BUS_ERRLOG0_errcode_START   (8)
#define SOC_VCODEC_BUS_ERRLOG0_errcode_END     (10)
#define SOC_VCODEC_BUS_ERRLOG0_len1_START      (16)
#define SOC_VCODEC_BUS_ERRLOG0_len1_END        (23)
#define SOC_VCODEC_BUS_ERRLOG0_format_START    (31)
#define SOC_VCODEC_BUS_ERRLOG0_format_END      (31)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_ERRLOG1_UNION
 结构说明  : ERRLOG1 寄存器结构定义。地址偏移量:0x1C18，初值:0x00000000，宽度:32
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
} SOC_VCODEC_BUS_ERRLOG1_UNION;
#endif
#define SOC_VCODEC_BUS_ERRLOG1_errlog1_START   (0)
#define SOC_VCODEC_BUS_ERRLOG1_errlog1_END     (21)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_ERRLOG3_UNION
 结构说明  : ERRLOG3 寄存器结构定义。地址偏移量:0x1C20，初值:0x00000000，宽度:32
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
} SOC_VCODEC_BUS_ERRLOG3_UNION;
#endif
#define SOC_VCODEC_BUS_ERRLOG3_errlog3_START   (0)
#define SOC_VCODEC_BUS_ERRLOG3_errlog3_END     (30)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_ERRLOG5_UNION
 结构说明  : ERRLOG5 寄存器结构定义。地址偏移量:0x1C28，初值:0x00000000，宽度:32
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
} SOC_VCODEC_BUS_ERRLOG5_UNION;
#endif
#define SOC_VCODEC_BUS_ERRLOG5_errlog5_START   (0)
#define SOC_VCODEC_BUS_ERRLOG5_errlog5_END     (16)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_ERRLOG7_UNION
 结构说明  : ERRLOG7 寄存器结构定义。地址偏移量:0x1C30，初值:0x00000000，宽度:32
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
} SOC_VCODEC_BUS_ERRLOG7_UNION;
#endif
#define SOC_VCODEC_BUS_ERRLOG7_errlog7_START   (0)
#define SOC_VCODEC_BUS_ERRLOG7_errlog7_END     (0)




/****************************************************************************
                     (2/3) NOC_VENC
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_QOS_ID_COREID_UNION
 结构说明  : VENC_QOS_ID_COREID 寄存器结构定义。地址偏移量:0x0100，初值:0x3CB8C104，宽度:32
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
} SOC_VCODEC_BUS_VENC_QOS_ID_COREID_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_QOS_ID_COREID_coretypeid_START    (0)
#define SOC_VCODEC_BUS_VENC_QOS_ID_COREID_coretypeid_END      (7)
#define SOC_VCODEC_BUS_VENC_QOS_ID_COREID_corechecksum_START  (8)
#define SOC_VCODEC_BUS_VENC_QOS_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_QOS_ID_REVISIONID_UNION
 结构说明  : VENC_QOS_ID_REVISIONID 寄存器结构定义。地址偏移量:0x0104，初值:0x012D5300，宽度:32
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
} SOC_VCODEC_BUS_VENC_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_QOS_ID_REVISIONID_userid_START     (0)
#define SOC_VCODEC_BUS_VENC_QOS_ID_REVISIONID_userid_END       (7)
#define SOC_VCODEC_BUS_VENC_QOS_ID_REVISIONID_flexnocid_START  (8)
#define SOC_VCODEC_BUS_VENC_QOS_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_QOS_PRIORITY_UNION
 结构说明  : VENC_QOS_PRIORITY 寄存器结构定义。地址偏移量:0x0108，初值:0x80000003，宽度:32
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
} SOC_VCODEC_BUS_VENC_QOS_PRIORITY_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_QOS_PRIORITY_p0_START        (0)
#define SOC_VCODEC_BUS_VENC_QOS_PRIORITY_p0_END          (1)
#define SOC_VCODEC_BUS_VENC_QOS_PRIORITY_p1_START        (8)
#define SOC_VCODEC_BUS_VENC_QOS_PRIORITY_p1_END          (9)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_QOS_MODE_UNION
 结构说明  : VENC_QOS_MODE 寄存器结构定义。地址偏移量:0x010C，初值:0x00000003，宽度:32
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
} SOC_VCODEC_BUS_VENC_QOS_MODE_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_QOS_MODE_mode_START      (0)
#define SOC_VCODEC_BUS_VENC_QOS_MODE_mode_END        (1)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_QOS_BANDWIDTH_UNION
 结构说明  : VENC_QOS_BANDWIDTH 寄存器结构定义。地址偏移量:0x0110，初值:0x00000640，宽度:32
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
} SOC_VCODEC_BUS_VENC_QOS_BANDWIDTH_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_QOS_BANDWIDTH_bandwidth_START  (0)
#define SOC_VCODEC_BUS_VENC_QOS_BANDWIDTH_bandwidth_END    (12)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_QOS_SATURATION_UNION
 结构说明  : VENC_QOS_SATURATION 寄存器结构定义。地址偏移量:0x0114，初值:0x000003E8，宽度:32
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
} SOC_VCODEC_BUS_VENC_QOS_SATURATION_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_QOS_SATURATION_saturation_START  (0)
#define SOC_VCODEC_BUS_VENC_QOS_SATURATION_saturation_END    (9)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_QOS_EXTCONTROL_UNION
 结构说明  : VENC_QOS_EXTCONTROL 寄存器结构定义。地址偏移量:0x0118，初值:0x00000000，宽度:32
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
} SOC_VCODEC_BUS_VENC_QOS_EXTCONTROL_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_QOS_EXTCONTROL_socketqosen_START  (0)
#define SOC_VCODEC_BUS_VENC_QOS_EXTCONTROL_socketqosen_END    (0)
#define SOC_VCODEC_BUS_VENC_QOS_EXTCONTROL_extthren_START     (1)
#define SOC_VCODEC_BUS_VENC_QOS_EXTCONTROL_extthren_END       (1)
#define SOC_VCODEC_BUS_VENC_QOS_EXTCONTROL_intclken_START     (2)
#define SOC_VCODEC_BUS_VENC_QOS_EXTCONTROL_intclken_END       (2)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_TRANS_F_ID_COREID_UNION
 结构说明  : VENC_TRANS_F_ID_COREID 寄存器结构定义。地址偏移量:0x8000，初值:0xBFA61A09，宽度:32
 寄存器说明: VENC TransactionStatFilter域ID
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
} SOC_VCODEC_BUS_VENC_TRANS_F_ID_COREID_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_F_ID_COREID_coretypeid_START    (0)
#define SOC_VCODEC_BUS_VENC_TRANS_F_ID_COREID_coretypeid_END      (7)
#define SOC_VCODEC_BUS_VENC_TRANS_F_ID_COREID_corechecksum_START  (8)
#define SOC_VCODEC_BUS_VENC_TRANS_F_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_TRANS_F_ID_REVISIONID_UNION
 结构说明  : VENC_TRANS_F_ID_REVISIONID 寄存器结构定义。地址偏移量:0x8004，初值:0x012D5300，宽度:32
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
} SOC_VCODEC_BUS_VENC_TRANS_F_ID_REVISIONID_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_F_ID_REVISIONID_userid_START     (0)
#define SOC_VCODEC_BUS_VENC_TRANS_F_ID_REVISIONID_userid_END       (7)
#define SOC_VCODEC_BUS_VENC_TRANS_F_ID_REVISIONID_flexnocid_START  (8)
#define SOC_VCODEC_BUS_VENC_TRANS_F_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_TRANS_F_MODE_UNION
 结构说明  : VENC_TRANS_F_MODE 寄存器结构定义。地址偏移量:0x8008，初值:0x00000000，宽度:32
 寄存器说明: VENC Transaction Probe的Filter工作模式配置寄存器
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
} SOC_VCODEC_BUS_VENC_TRANS_F_MODE_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_F_MODE_mode_START      (0)
#define SOC_VCODEC_BUS_VENC_TRANS_F_MODE_mode_END        (0)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_TRANS_F_ADDRBASE_LOW_UNION
 结构说明  : VENC_TRANS_F_ADDRBASE_LOW 寄存器结构定义。地址偏移量:0x800C，初值:0x00000000，宽度:32
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
} SOC_VCODEC_BUS_VENC_TRANS_F_ADDRBASE_LOW_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_F_ADDRBASE_LOW_addrbase_low_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_F_ADDRBASE_LOW_addrbase_low_END    (31)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_TRANS_F_ADDRBASE_HIGH_UNION
 结构说明  : VENC_TRANS_F_ADDRBASE_HIGH 寄存器结构定义。地址偏移量:0x8010，初值:0x00000000，宽度:32
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
} SOC_VCODEC_BUS_VENC_TRANS_F_ADDRBASE_HIGH_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_F_ADDRBASE_HIGH_addrbase_high_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_F_ADDRBASE_HIGH_addrbase_high_END    (1)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_TRANS_F_ADDRWINDOWSIZE_UNION
 结构说明  : VENC_TRANS_F_ADDRWINDOWSIZE 寄存器结构定义。地址偏移量:0x8014，初值:0x00000000，宽度:32
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
} SOC_VCODEC_BUS_VENC_TRANS_F_ADDRWINDOWSIZE_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_F_ADDRWINDOWSIZE_addrwindowsize_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_F_ADDRWINDOWSIZE_addrwindowsize_END    (5)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_TRANS_F_OPCODE_UNION
 结构说明  : VENC_TRANS_F_OPCODE 寄存器结构定义。地址偏移量:0x8020，初值:0x00000000，宽度:32
 寄存器说明: VENC的Transaction Probe的Opcode过滤条件
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
} SOC_VCODEC_BUS_VENC_TRANS_F_OPCODE_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_F_OPCODE_rden_START      (0)
#define SOC_VCODEC_BUS_VENC_TRANS_F_OPCODE_rden_END        (0)
#define SOC_VCODEC_BUS_VENC_TRANS_F_OPCODE_wren_START      (1)
#define SOC_VCODEC_BUS_VENC_TRANS_F_OPCODE_wren_END        (1)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_TRANS_F_USERBASE_UNION
 结构说明  : VENC_TRANS_F_USERBASE 寄存器结构定义。地址偏移量:0x8024，初值:0x00000000，宽度:32
 寄存器说明: VENC的Transaction Probe的User过滤条件
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
} SOC_VCODEC_BUS_VENC_TRANS_F_USERBASE_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_F_USERBASE_userbase_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_F_USERBASE_userbase_END    (4)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_TRANS_F_USERMASK_UNION
 结构说明  : VENC_TRANS_F_USERMASK 寄存器结构定义。地址偏移量:0x8028，初值:0x00000000，宽度:32
 寄存器说明: VENC的Transaction Probe的User过滤条件Mask
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
} SOC_VCODEC_BUS_VENC_TRANS_F_USERMASK_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_F_USERMASK_usermask_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_F_USERMASK_usermask_END    (4)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_TRANS_F_SECURITYBASE_UNION
 结构说明  : VENC_TRANS_F_SECURITYBASE 寄存器结构定义。地址偏移量:0x802C，初值:0x00000000，宽度:32
 寄存器说明: VENC的Transaction Probe的安全过滤条件
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
} SOC_VCODEC_BUS_VENC_TRANS_F_SECURITYBASE_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_F_SECURITYBASE_securitybase_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_F_SECURITYBASE_securitybase_END    (0)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_TRANS_F_SECURITYMASK_UNION
 结构说明  : VENC_TRANS_F_SECURITYMASK 寄存器结构定义。地址偏移量:0x8030，初值:0x00000000，宽度:32
 寄存器说明: VENC的Transaction Probe的安全过滤条件Mask
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
} SOC_VCODEC_BUS_VENC_TRANS_F_SECURITYMASK_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_F_SECURITYMASK_securitymask_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_F_SECURITYMASK_securitymask_END    (0)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_TRANS_P_ID_COREID_UNION
 结构说明  : VENC_TRANS_P_ID_COREID 寄存器结构定义。地址偏移量:0x8080，初值:0xB14C6F0A，宽度:32
 寄存器说明: VENC TransactionStatProfilter域ID
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
} SOC_VCODEC_BUS_VENC_TRANS_P_ID_COREID_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_P_ID_COREID_coretypeid_START    (0)
#define SOC_VCODEC_BUS_VENC_TRANS_P_ID_COREID_coretypeid_END      (7)
#define SOC_VCODEC_BUS_VENC_TRANS_P_ID_COREID_corechecksum_START  (8)
#define SOC_VCODEC_BUS_VENC_TRANS_P_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_TRANS_P_ID_REVISIONID_UNION
 结构说明  : VENC_TRANS_P_ID_REVISIONID 寄存器结构定义。地址偏移量:0x8084，初值:0x012D5300，宽度:32
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
} SOC_VCODEC_BUS_VENC_TRANS_P_ID_REVISIONID_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_P_ID_REVISIONID_userid_START     (0)
#define SOC_VCODEC_BUS_VENC_TRANS_P_ID_REVISIONID_userid_END       (7)
#define SOC_VCODEC_BUS_VENC_TRANS_P_ID_REVISIONID_flexnocid_START  (8)
#define SOC_VCODEC_BUS_VENC_TRANS_P_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_TRANS_P_EN_UNION
 结构说明  : VENC_TRANS_P_EN 寄存器结构定义。地址偏移量:0x8088，初值:0x00000000，宽度:32
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
} SOC_VCODEC_BUS_VENC_TRANS_P_EN_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_P_EN_en_START        (0)
#define SOC_VCODEC_BUS_VENC_TRANS_P_EN_en_END          (0)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_TRANS_P_MODE_UNION
 结构说明  : VENC_TRANS_P_MODE 寄存器结构定义。地址偏移量:0x808C，初值:0x00000000，宽度:32
 寄存器说明: VENC Transaction Probe的工作模式配置
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
} SOC_VCODEC_BUS_VENC_TRANS_P_MODE_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_P_MODE_mode_START      (0)
#define SOC_VCODEC_BUS_VENC_TRANS_P_MODE_mode_END        (0)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_TRANS_P_OVERFLOWSTATUS_UNION
 结构说明  : VENC_TRANS_P_OVERFLOWSTATUS 寄存器结构定义。地址偏移量:0x80EC，初值:0x00000000，宽度:32
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
} SOC_VCODEC_BUS_VENC_TRANS_P_OVERFLOWSTATUS_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_P_OVERFLOWSTATUS_overflowstatus_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_P_OVERFLOWSTATUS_overflowstatus_END    (0)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_TRANS_P_OVERFLOWRESET_UNION
 结构说明  : VENC_TRANS_P_OVERFLOWRESET 寄存器结构定义。地址偏移量:0x80F0，初值:0x00000000，宽度:32
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
} SOC_VCODEC_BUS_VENC_TRANS_P_OVERFLOWRESET_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_P_OVERFLOWRESET_overflowreset_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_P_OVERFLOWRESET_overflowreset_END    (0)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_TRANS_P_PENDINGEVENTMODE_UNION
 结构说明  : VENC_TRANS_P_PENDINGEVENTMODE 寄存器结构定义。地址偏移量:0x80F4，初值:0x00000000，宽度:32
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
} SOC_VCODEC_BUS_VENC_TRANS_P_PENDINGEVENTMODE_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_P_PENDINGEVENTMODE_pendingeventmode_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_P_PENDINGEVENTMODE_pendingeventmode_END    (0)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_TRANS_P_PRESCALER_UNION
 结构说明  : VENC_TRANS_P_PRESCALER 寄存器结构定义。地址偏移量:0x80F8，初值:0x00000000，宽度:32
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
} SOC_VCODEC_BUS_VENC_TRANS_P_PRESCALER_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_P_PRESCALER_prescaler_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_P_PRESCALER_prescaler_END    (7)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_TRANS_M_ID_COREID_UNION
 结构说明  : VENC_TRANS_M_ID_COREID 寄存器结构定义。地址偏移量:0x8400，初值:0x4B15C906，宽度:32
 寄存器说明: VENC Transaction probe域ID
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_coreid : 32; /* bit[0-31]: VcodecBus的Packet Probe的域ID。 */
    } reg;
} SOC_VCODEC_BUS_VENC_TRANS_M_ID_COREID_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_ID_COREID_id_coreid_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_ID_COREID_id_coreid_END    (31)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_TRANS_M_ID_REVISIONID_UNION
 结构说明  : VENC_TRANS_M_ID_REVISIONID 寄存器结构定义。地址偏移量:0x8404，初值:0x012D5300，宽度:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_ID_REVISIONID_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_ID_REVISIONID_id_revisionid_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_ID_REVISIONID_id_revisionid_END    (31)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_TRANS_M_MAINCTL_UNION
 结构说明  : VENC_TRANS_M_MAINCTL 寄存器结构定义。地址偏移量:0x8408，初值:0x00000000，宽度:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_MAINCTL_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_MAINCTL_erren_START                      (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_MAINCTL_erren_END                        (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_MAINCTL_traceen_START                    (1)
#define SOC_VCODEC_BUS_VENC_TRANS_M_MAINCTL_traceen_END                      (1)
#define SOC_VCODEC_BUS_VENC_TRANS_M_MAINCTL_payloaden_START                  (2)
#define SOC_VCODEC_BUS_VENC_TRANS_M_MAINCTL_payloaden_END                    (2)
#define SOC_VCODEC_BUS_VENC_TRANS_M_MAINCTL_staten_START                     (3)
#define SOC_VCODEC_BUS_VENC_TRANS_M_MAINCTL_staten_END                       (3)
#define SOC_VCODEC_BUS_VENC_TRANS_M_MAINCTL_alarmen_START                    (4)
#define SOC_VCODEC_BUS_VENC_TRANS_M_MAINCTL_alarmen_END                      (4)
#define SOC_VCODEC_BUS_VENC_TRANS_M_MAINCTL_statconddump_START               (5)
#define SOC_VCODEC_BUS_VENC_TRANS_M_MAINCTL_statconddump_END                 (5)
#define SOC_VCODEC_BUS_VENC_TRANS_M_MAINCTL_intrusivemode_START              (6)
#define SOC_VCODEC_BUS_VENC_TRANS_M_MAINCTL_intrusivemode_END                (6)
#define SOC_VCODEC_BUS_VENC_TRANS_M_MAINCTL_filtbytealwayschainableen_START  (7)
#define SOC_VCODEC_BUS_VENC_TRANS_M_MAINCTL_filtbytealwayschainableen_END    (7)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_TRANS_M_CFGCTL_UNION
 结构说明  : VENC_TRANS_M_CFGCTL 寄存器结构定义。地址偏移量:0x840C，初值:0x00000000，宽度:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_CFGCTL_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_CFGCTL_globalen_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_CFGCTL_globalen_END    (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_CFGCTL_active_START    (1)
#define SOC_VCODEC_BUS_VENC_TRANS_M_CFGCTL_active_END      (1)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_TRANS_M_STATPERIOD_UNION
 结构说明  : VENC_TRANS_M_STATPERIOD 寄存器结构定义。地址偏移量:0x8424，初值:0x00000000，宽度:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_STATPERIOD_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_STATPERIOD_statperiod_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_STATPERIOD_statperiod_END    (4)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_TRANS_M_STATGO_UNION
 结构说明  : VENC_TRANS_M_STATGO 寄存器结构定义。地址偏移量:0x8428，初值:0x00000000，宽度:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_STATGO_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_STATGO_statgo_START    (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_STATGO_statgo_END      (0)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMMIN_UNION
 结构说明  : VENC_TRANS_M_STATALARMMIN 寄存器结构定义。地址偏移量:0x842C，初值:0x00000000，宽度:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMMIN_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMMIN_statalarmmin_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMMIN_statalarmmin_END    (31)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMMAX_UNION
 结构说明  : VENC_TRANS_M_STATALARMMAX 寄存器结构定义。地址偏移量:0x8430，初值:0x00000000，宽度:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMMAX_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMMAX_statalarmmax_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMMAX_statalarmmax_END    (31)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMSTATUS_UNION
 结构说明  : VENC_TRANS_M_STATALARMSTATUS 寄存器结构定义。地址偏移量:0x8434，初值:0x00000000，宽度:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMSTATUS_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMSTATUS_statalarmstatus_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMSTATUS_statalarmstatus_END    (0)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMCLR_UNION
 结构说明  : VENC_TRANS_M_STATALARMCLR 寄存器结构定义。地址偏移量:0x8438，初值:0x00000000，宽度:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMCLR_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMCLR_statalarmclr_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMCLR_statalarmclr_END    (0)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_0_SRC_UNION
 结构说明  : VENC_TRANS_M_COUNTERS_0_SRC 寄存器结构定义。地址偏移量:0x8538，初值:0x00000000，宽度:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_0_SRC_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_0_SRC_counters_0_src_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_0_SRC_counters_0_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_0_ALARMMODE_UNION
 结构说明  : VENC_TRANS_M_COUNTERS_0_ALARMMODE 寄存器结构定义。地址偏移量:0x853C，初值:0x00000000，宽度:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_0_ALARMMODE_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_0_ALARMMODE_counters_0_alarmmode_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_0_ALARMMODE_counters_0_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_0_VAL_UNION
 结构说明  : VENC_TRANS_M_COUNTERS_0_VAL 寄存器结构定义。地址偏移量:0x8540，初值:0x00000000，宽度:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_0_VAL_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_0_VAL_counters_0_val_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_0_VAL_counters_0_val_END    (11)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_1_SRC_UNION
 结构说明  : VENC_TRANS_M_COUNTERS_1_SRC 寄存器结构定义。地址偏移量:0x854C，初值:0x00000000，宽度:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_1_SRC_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_1_SRC_counters_1_src_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_1_SRC_counters_1_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_1_ALARMMODE_UNION
 结构说明  : VENC_TRANS_M_COUNTERS_1_ALARMMODE 寄存器结构定义。地址偏移量:0x8550，初值:0x00000000，宽度:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_1_ALARMMODE_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_1_ALARMMODE_counters_1_alarmmode_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_1_ALARMMODE_counters_1_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_1_VAL_UNION
 结构说明  : VENC_TRANS_M_COUNTERS_1_VAL 寄存器结构定义。地址偏移量:0x8554，初值:0x00000000，宽度:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_1_VAL_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_1_VAL_counters_1_val_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_1_VAL_counters_1_val_END    (11)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_2_SRC_UNION
 结构说明  : VENC_TRANS_M_COUNTERS_2_SRC 寄存器结构定义。地址偏移量:0x8560，初值:0x00000000，宽度:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_2_SRC_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_2_SRC_counters_2_src_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_2_SRC_counters_2_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_2_ALARMMODE_UNION
 结构说明  : VENC_TRANS_M_COUNTERS_2_ALARMMODE 寄存器结构定义。地址偏移量:0x8564，初值:0x00000000，宽度:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_2_ALARMMODE_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_2_ALARMMODE_counters_2_alarmmode_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_2_ALARMMODE_counters_2_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_2_VAL_UNION
 结构说明  : VENC_TRANS_M_COUNTERS_2_VAL 寄存器结构定义。地址偏移量:0x8568，初值:0x00000000，宽度:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_2_VAL_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_2_VAL_counters_2_val_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_2_VAL_counters_2_val_END    (11)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_3_SRC_UNION
 结构说明  : VENC_TRANS_M_COUNTERS_3_SRC 寄存器结构定义。地址偏移量:0x8574，初值:0x00000000，宽度:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_3_SRC_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_3_SRC_counters_3_src_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_3_SRC_counters_3_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_3_ALARMMODE_UNION
 结构说明  : VENC_TRANS_M_COUNTERS_3_ALARMMODE 寄存器结构定义。地址偏移量:0x8578，初值:0x00000000，宽度:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_3_ALARMMODE_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_3_ALARMMODE_counters_3_alarmmode_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_3_ALARMMODE_counters_3_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_3_VAL_UNION
 结构说明  : VENC_TRANS_M_COUNTERS_3_VAL 寄存器结构定义。地址偏移量:0x857C，初值:0x00000000，宽度:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_3_VAL_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_3_VAL_counters_3_val_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_3_VAL_counters_3_val_END    (11)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_4_SRC_UNION
 结构说明  : VENC_TRANS_M_COUNTERS_4_SRC 寄存器结构定义。地址偏移量:0x8588，初值:0x00000000，宽度:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_4_SRC_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_4_SRC_counters_4_src_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_4_SRC_counters_4_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_4_ALARMMODE_UNION
 结构说明  : VENC_TRANS_M_COUNTERS_4_ALARMMODE 寄存器结构定义。地址偏移量:0x858C，初值:0x00000000，宽度:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_4_ALARMMODE_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_4_ALARMMODE_counters_4_alarmmode_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_4_ALARMMODE_counters_4_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_4_VAL_UNION
 结构说明  : VENC_TRANS_M_COUNTERS_4_VAL 寄存器结构定义。地址偏移量:0x8590，初值:0x00000000，宽度:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_4_VAL_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_4_VAL_counters_4_val_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_4_VAL_counters_4_val_END    (11)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_5_SRC_UNION
 结构说明  : VENC_TRANS_M_COUNTERS_5_SRC 寄存器结构定义。地址偏移量:0x859C，初值:0x00000000，宽度:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_5_SRC_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_5_SRC_counters_5_src_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_5_SRC_counters_5_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_5_ALARMMODE_UNION
 结构说明  : VENC_TRANS_M_COUNTERS_5_ALARMMODE 寄存器结构定义。地址偏移量:0x85A0，初值:0x00000000，宽度:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_5_ALARMMODE_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_5_ALARMMODE_counters_5_alarmmode_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_5_ALARMMODE_counters_5_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_5_VAL_UNION
 结构说明  : VENC_TRANS_M_COUNTERS_5_VAL 寄存器结构定义。地址偏移量:0x85A4，初值:0x00000000，宽度:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_5_VAL_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_5_VAL_counters_5_val_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_5_VAL_counters_5_val_END    (11)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_6_SRC_UNION
 结构说明  : VENC_TRANS_M_COUNTERS_6_SRC 寄存器结构定义。地址偏移量:0x85B0，初值:0x00000000，宽度:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_6_SRC_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_6_SRC_counters_6_src_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_6_SRC_counters_6_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_6_ALARMMODE_UNION
 结构说明  : VENC_TRANS_M_COUNTERS_6_ALARMMODE 寄存器结构定义。地址偏移量:0x85B4，初值:0x00000000，宽度:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_6_ALARMMODE_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_6_ALARMMODE_counters_6_alarmmode_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_6_ALARMMODE_counters_6_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_6_VAL_UNION
 结构说明  : VENC_TRANS_M_COUNTERS_6_VAL 寄存器结构定义。地址偏移量:0x85B8，初值:0x00000000，宽度:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_6_VAL_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_6_VAL_counters_6_val_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_6_VAL_counters_6_val_END    (11)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_7_SRC_UNION
 结构说明  : VENC_TRANS_M_COUNTERS_7_SRC 寄存器结构定义。地址偏移量:0x85C4，初值:0x00000000，宽度:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_7_SRC_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_7_SRC_counters_7_src_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_7_SRC_counters_7_src_END    (5)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_7_ALARMMODE_UNION
 结构说明  : VENC_TRANS_M_COUNTERS_7_ALARMMODE 寄存器结构定义。地址偏移量:0x85C8，初值:0x00000000，宽度:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_7_ALARMMODE_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_7_ALARMMODE_counters_7_alarmmode_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_7_ALARMMODE_counters_7_alarmmode_END    (1)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_7_VAL_UNION
 结构说明  : VENC_TRANS_M_COUNTERS_7_VAL 寄存器结构定义。地址偏移量:0x85CC，初值:0x00000000，宽度:32
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
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_7_VAL_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_7_VAL_counters_7_val_START  (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_7_VAL_counters_7_val_END    (11)




/****************************************************************************
                     (3/3) NOC_VDEC
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VDEC_QOS_ID_COREID_UNION
 结构说明  : VDEC_QOS_ID_COREID 寄存器结构定义。地址偏移量:0x0000，初值:0x5A288C04，宽度:32
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
} SOC_VCODEC_BUS_VDEC_QOS_ID_COREID_UNION;
#endif
#define SOC_VCODEC_BUS_VDEC_QOS_ID_COREID_coretypeid_START    (0)
#define SOC_VCODEC_BUS_VDEC_QOS_ID_COREID_coretypeid_END      (7)
#define SOC_VCODEC_BUS_VDEC_QOS_ID_COREID_corechecksum_START  (8)
#define SOC_VCODEC_BUS_VDEC_QOS_ID_COREID_corechecksum_END    (31)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VDEC_QOS_ID_REVISIONID_UNION
 结构说明  : VDEC_QOS_ID_REVISIONID 寄存器结构定义。地址偏移量:0x0004，初值:0x012D5300，宽度:32
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
} SOC_VCODEC_BUS_VDEC_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_VCODEC_BUS_VDEC_QOS_ID_REVISIONID_userid_START     (0)
#define SOC_VCODEC_BUS_VDEC_QOS_ID_REVISIONID_userid_END       (7)
#define SOC_VCODEC_BUS_VDEC_QOS_ID_REVISIONID_flexnocid_START  (8)
#define SOC_VCODEC_BUS_VDEC_QOS_ID_REVISIONID_flexnocid_END    (31)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VDEC_QOS_PRIORITY_UNION
 结构说明  : VDEC_QOS_PRIORITY 寄存器结构定义。地址偏移量:0x0008，初值:0x08000003，宽度:32
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
} SOC_VCODEC_BUS_VDEC_QOS_PRIORITY_UNION;
#endif
#define SOC_VCODEC_BUS_VDEC_QOS_PRIORITY_p0_START        (0)
#define SOC_VCODEC_BUS_VDEC_QOS_PRIORITY_p0_END          (1)
#define SOC_VCODEC_BUS_VDEC_QOS_PRIORITY_p1_START        (8)
#define SOC_VCODEC_BUS_VDEC_QOS_PRIORITY_p1_END          (9)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VDEC_QOS_MODE_UNION
 结构说明  : VDEC_QOS_MODE 寄存器结构定义。地址偏移量:0x000C，初值:0x00000003，宽度:32
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
} SOC_VCODEC_BUS_VDEC_QOS_MODE_UNION;
#endif
#define SOC_VCODEC_BUS_VDEC_QOS_MODE_mode_START      (0)
#define SOC_VCODEC_BUS_VDEC_QOS_MODE_mode_END        (1)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VDEC_QOS_BANDWIDTH_UNION
 结构说明  : VDEC_QOS_BANDWIDTH 寄存器结构定义。地址偏移量:0x0010，初值:0x000005D0，宽度:32
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
} SOC_VCODEC_BUS_VDEC_QOS_BANDWIDTH_UNION;
#endif
#define SOC_VCODEC_BUS_VDEC_QOS_BANDWIDTH_bandwidth_START  (0)
#define SOC_VCODEC_BUS_VDEC_QOS_BANDWIDTH_bandwidth_END    (12)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VDEC_QOS_SATURATION_UNION
 结构说明  : VDEC_QOS_SATURATION 寄存器结构定义。地址偏移量:0x0014，初值:0x000003E8，宽度:32
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
} SOC_VCODEC_BUS_VDEC_QOS_SATURATION_UNION;
#endif
#define SOC_VCODEC_BUS_VDEC_QOS_SATURATION_saturation_START  (0)
#define SOC_VCODEC_BUS_VDEC_QOS_SATURATION_saturation_END    (9)


/*****************************************************************************
 结构名    : SOC_VCODEC_BUS_VDEC_QOS_EXTCONTROL_UNION
 结构说明  : VDEC_QOS_EXTCONTROL 寄存器结构定义。地址偏移量:0x0018，初值:0x00000000，宽度:32
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
} SOC_VCODEC_BUS_VDEC_QOS_EXTCONTROL_UNION;
#endif
#define SOC_VCODEC_BUS_VDEC_QOS_EXTCONTROL_socketqosen_START  (0)
#define SOC_VCODEC_BUS_VDEC_QOS_EXTCONTROL_socketqosen_END    (0)
#define SOC_VCODEC_BUS_VDEC_QOS_EXTCONTROL_extthren_START     (1)
#define SOC_VCODEC_BUS_VDEC_QOS_EXTCONTROL_extthren_END       (1)
#define SOC_VCODEC_BUS_VDEC_QOS_EXTCONTROL_intclken_START     (2)
#define SOC_VCODEC_BUS_VDEC_QOS_EXTCONTROL_intclken_END       (2)






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

#endif /* end of soc_vcodec_bus_interface.h */
