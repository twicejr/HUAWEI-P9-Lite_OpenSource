/******************************************************************************

                 版权所有 (C), 2001-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : soc_asp_hifi3_interface.h
  版 本 号   : 初稿
  作    者   : Excel2Code
  生成日期   : 2015-03-10 11:18:12
  最近修改   :
  功能描述   : 接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月10日
    作    者   : fWX220878
    修改内容   : 从《Hi3650V100 SOC寄存器手册_ASP_HIFI3.xml》自动生成

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __SOC_ASP_HIFI3_INTERFACE_H__
#define __SOC_ASP_HIFI3_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/****************************************************************************
                     (1/1) register_define
 ****************************************************************************/
/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_HIFI3_TRAXID_UNION */
#define SOC_ASP_HIFI3_TRAXID_ADDR(base)               ((base) + (0x0000))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_HIFI3_TRAXCTRL_UNION */
#define SOC_ASP_HIFI3_TRAXCTRL_ADDR(base)             ((base) + (0x0004))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_HIFI3_TRAXSTAT_UNION */
#define SOC_ASP_HIFI3_TRAXSTAT_ADDR(base)             ((base) + (0x0008))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_HIFI3_TRAXDATA_UNION */
#define SOC_ASP_HIFI3_TRAXDATA_ADDR(base)             ((base) + (0x000C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_HIFI3_TRAXADDR_UNION */
#define SOC_ASP_HIFI3_TRAXADDR_ADDR(base)             ((base) + (0x0010))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_HIFI3_TRIGGERPC_UNION */
#define SOC_ASP_HIFI3_TRIGGERPC_ADDR(base)            ((base) + (0x0014))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_HIFI3_PCMATCHCTRL_UNION */
#define SOC_ASP_HIFI3_PCMATCHCTRL_ADDR(base)          ((base) + (0x0018))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_HIFI3_DELAYCNT_UNION */
#define SOC_ASP_HIFI3_DELAYCNT_ADDR(base)             ((base) + (0x001C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_HIFI3_MEMADDRSTART_UNION */
#define SOC_ASP_HIFI3_MEMADDRSTART_ADDR(base)         ((base) + (0x0020))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_HIFI3_MEMADDREND_UNION */
#define SOC_ASP_HIFI3_MEMADDREND_ADDR(base)           ((base) + (0x0024))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_HIFI3_compressparams_UNION */
#define SOC_ASP_HIFI3_compressparams_ADDR(base)       ((base) + (0x006C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_HIFI3_PMG_UNION */
#define SOC_ASP_HIFI3_PMG_ADDR(base)                  ((base) + (0x1000))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_HIFI3_INTPC_UNION */
#define SOC_ASP_HIFI3_INTPC_ADDR(base)                ((base) + (0x1010))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_HIFI3_perfcounter0_UNION */
#define SOC_ASP_HIFI3_perfcounter0_ADDR(base)         ((base) + (0x1080))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_HIFI3_perfcounter1_UNION */
#define SOC_ASP_HIFI3_perfcounter1_ADDR(base)         ((base) + (0x1084))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_HIFI3_perfcounter2_UNION */
#define SOC_ASP_HIFI3_perfcounter2_ADDR(base)         ((base) + (0x1088))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_HIFI3_perfcounter3_UNION */
#define SOC_ASP_HIFI3_perfcounter3_ADDR(base)         ((base) + (0x108C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_HIFI3_PMCTRL0_UNION */
#define SOC_ASP_HIFI3_PMCTRL0_ADDR(base)              ((base) + (0x1100))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_HIFI3_PMCTRL1_UNION */
#define SOC_ASP_HIFI3_PMCTRL1_ADDR(base)              ((base) + (0x1104))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_HIFI3_PMCTRL2_UNION */
#define SOC_ASP_HIFI3_PMCTRL2_ADDR(base)              ((base) + (0x1108))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_HIFI3_PMCTRL3_UNION */
#define SOC_ASP_HIFI3_PMCTRL3_ADDR(base)              ((base) + (0x110C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_HIFI3_PMSTA0_UNION */
#define SOC_ASP_HIFI3_PMSTA0_ADDR(base)               ((base) + (0x1180))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_HIFI3_PMSTA1_UNION */
#define SOC_ASP_HIFI3_PMSTA1_ADDR(base)               ((base) + (0x1184))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_HIFI3_PMSTA2_UNION */
#define SOC_ASP_HIFI3_PMSTA2_ADDR(base)               ((base) + (0x1188))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_HIFI3_PMSTA3_UNION */
#define SOC_ASP_HIFI3_PMSTA3_ADDR(base)               ((base) + (0x118C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_HIFI3_OCDID_UNION */
#define SOC_ASP_HIFI3_OCDID_ADDR(base)                ((base) + (0x2000))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_HIFI3_DCRCLR_UNION */
#define SOC_ASP_HIFI3_DCRCLR_ADDR(base)               ((base) + (0x2008))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_HIFI3_DCRSET_UNION */
#define SOC_ASP_HIFI3_DCRSET_ADDR(base)               ((base) + (0x200C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_HIFI3_DSR_UNION */
#define SOC_ASP_HIFI3_DSR_ADDR(base)                  ((base) + (0x2010))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_HIFI3_DDR_UNION */
#define SOC_ASP_HIFI3_DDR_ADDR(base)                  ((base) + (0x2014))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_HIFI3_DDREXEC_UNION */
#define SOC_ASP_HIFI3_DDREXEC_ADDR(base)              ((base) + (0x2018))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_HIFI3_DIR0EXEC_UNION */
#define SOC_ASP_HIFI3_DIR0EXEC_ADDR(base)             ((base) + (0x201C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_HIFI3_denugInst0_UNION */
#define SOC_ASP_HIFI3_denugInst0_ADDR(base)           ((base) + (0x2020))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_HIFI3_debugInst1_UNION */
#define SOC_ASP_HIFI3_debugInst1_ADDR(base)           ((base) + (0x2024))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_HIFI3_PWRCTL_UNION */
#define SOC_ASP_HIFI3_PWRCTL_ADDR(base)               ((base) + (0x3020))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_HIFI3_PWRSTAT_UNION */
#define SOC_ASP_HIFI3_PWRSTAT_ADDR(base)              ((base) + (0x3024))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_HIFI3_ERISTAT_UNION */
#define SOC_ASP_HIFI3_ERISTAT_ADDR(base)              ((base) + (0x3028))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_HIFI3_undoRegThID1_UNION */
#define SOC_ASP_HIFI3_undoRegThID1_ADDR(base)         ((base) + (0x3034))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_HIFI3_undocRegBuild_UNION */
#define SOC_ASP_HIFI3_undocRegBuild_ADDR(base)        ((base) + (0x3038))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_HIFI3_undocRegBcid_UNION */
#define SOC_ASP_HIFI3_undocRegBcid_ADDR(base)         ((base) + (0x303C))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_HIFI3_itCtrl_UNION */
#define SOC_ASP_HIFI3_itCtrl_ADDR(base)               ((base) + (0x3F00))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_HIFI3_claimSet_UNION */
#define SOC_ASP_HIFI3_claimSet_ADDR(base)             ((base) + (0x3FA0))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_HIFI3_claimClear_UNION */
#define SOC_ASP_HIFI3_claimClear_ADDR(base)           ((base) + (0x3FA4))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_HIFI3_devId_UNION */
#define SOC_ASP_HIFI3_devId_ADDR(base)                ((base) + (0x3FC8))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_HIFI3_devType_UNION */
#define SOC_ASP_HIFI3_devType_ADDR(base)              ((base) + (0x3FCC))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_HIFI3_peripheralId4_UNION */
#define SOC_ASP_HIFI3_peripheralId4_ADDR(base)        ((base) + (0x3FD0))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_HIFI3_peripheralId5_UNION */
#define SOC_ASP_HIFI3_peripheralId5_ADDR(base)        ((base) + (0x3FD4))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_HIFI3_peripheralId6_UNION */
#define SOC_ASP_HIFI3_peripheralId6_ADDR(base)        ((base) + (0x3FD8))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_HIFI3_peripheralId7_UNION */
#define SOC_ASP_HIFI3_peripheralId7_ADDR(base)        ((base) + (0x3FDC))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_HIFI3_peripheralId0_UNION */
#define SOC_ASP_HIFI3_peripheralId0_ADDR(base)        ((base) + (0x3FE0))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_HIFI3_peripheralId1_UNION */
#define SOC_ASP_HIFI3_peripheralId1_ADDR(base)        ((base) + (0x3FE4))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_HIFI3_peripheralId2_UNION */
#define SOC_ASP_HIFI3_peripheralId2_ADDR(base)        ((base) + (0x3FE8))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_HIFI3_peripheralId3_UNION */
#define SOC_ASP_HIFI3_peripheralId3_ADDR(base)        ((base) + (0x3FEC))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_HIFI3_componentId0_UNION */
#define SOC_ASP_HIFI3_componentId0_ADDR(base)         ((base) + (0x3FF0))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_HIFI3_componentId1_UNION */
#define SOC_ASP_HIFI3_componentId1_ADDR(base)         ((base) + (0x3FF4))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_HIFI3_componentId2_UNION */
#define SOC_ASP_HIFI3_componentId2_ADDR(base)         ((base) + (0x3FF8))

/* 寄存器说明：
   位域定义UNION结构:  SOC_ASP_HIFI3_componentId3_UNION */
#define SOC_ASP_HIFI3_componentId3_ADDR(base)         ((base) + (0x3FFC))





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
                     (1/1) register_define
 ****************************************************************************/
/*****************************************************************************
 结构名    : SOC_ASP_HIFI3_TRAXID_UNION
 结构说明  : TRAXID 寄存器结构定义。地址偏移量:0x0000，初值:0x0D338FF2，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  TRAXID : 32; /* bit[0-31]: TRAX ID Register */
    } reg;
} SOC_ASP_HIFI3_TRAXID_UNION;
#endif
#define SOC_ASP_HIFI3_TRAXID_TRAXID_START  (0)
#define SOC_ASP_HIFI3_TRAXID_TRAXID_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_HIFI3_TRAXCTRL_UNION
 结构说明  : TRAXCTRL 寄存器结构定义。地址偏移量:0x0004，初值:0x80001080，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  traceEnabled                        : 1;  /* bit[0]    : traceEnabled */
        unsigned int  traceStop                           : 1;  /* bit[1]    : traceStop */
        unsigned int  pcMatchEn                           : 1;  /* bit[2]    : pcMatchEn */
        unsigned int  reserved_0                          : 1;  /* bit[3]    : reserved */
        unsigned int  processorTriggerInEn                : 1;  /* bit[4]    : processorTriggerInEn */
        unsigned int  crossTriggerInEn                    : 1;  /* bit[5]    : crossTriggerInEn */
        unsigned int  reserved_1                          : 1;  /* bit[6]    : reserved */
        unsigned int  traceMemOutEn                       : 1;  /* bit[7]    : traceMemOutEn */
        unsigned int  reserved_2                          : 1;  /* bit[8]    : reserved */
        unsigned int  CountUnitIsinst                     : 1;  /* bit[9]    : CountUnitIsinst */
        unsigned int  reserved_3                          : 1;  /* bit[10]   : reserved */
        unsigned int  reserved_4                          : 1;  /* bit[11]   : reserved */
        unsigned int  encodeSyncMessageFreq               : 3;  /* bit[12-14]: encodeSyncMessageFreq */
        unsigned int  reserved_5                          : 1;  /* bit[15]   : reserved */
        unsigned int  processorTriggerOutUponPrimeTrigger : 1;  /* bit[16]   : processorTriggerOutUponPrimeTrigger */
        unsigned int  processorTriggerOutUponZeroCount    : 1;  /* bit[17]   : processorTriggerOutUponZeroCount */
        unsigned int  reserved_6                          : 2;  /* bit[18-19]: reserved */
        unsigned int  CrossTriggerOutUponPrimeTrigger     : 1;  /* bit[20]   : CrossTriggerOutUponPrimeTrigger */
        unsigned int  CrossTriggerOutUponZeroCount        : 1;  /* bit[21]   : CrossTriggerOutUponZeroCount */
        unsigned int  CrossTriggerOutTopology             : 1;  /* bit[22]   : CrossTriggerOutTopology */
        unsigned int  CrossTriggerInAckTopology           : 1;  /* bit[23]   : CrossTriggerInAckTopology */
        unsigned int  TRAXCTRL                            : 8;  /* bit[24-31]: reserved */
    } reg;
} SOC_ASP_HIFI3_TRAXCTRL_UNION;
#endif
#define SOC_ASP_HIFI3_TRAXCTRL_traceEnabled_START                         (0)
#define SOC_ASP_HIFI3_TRAXCTRL_traceEnabled_END                           (0)
#define SOC_ASP_HIFI3_TRAXCTRL_traceStop_START                            (1)
#define SOC_ASP_HIFI3_TRAXCTRL_traceStop_END                              (1)
#define SOC_ASP_HIFI3_TRAXCTRL_pcMatchEn_START                            (2)
#define SOC_ASP_HIFI3_TRAXCTRL_pcMatchEn_END                              (2)
#define SOC_ASP_HIFI3_TRAXCTRL_processorTriggerInEn_START                 (4)
#define SOC_ASP_HIFI3_TRAXCTRL_processorTriggerInEn_END                   (4)
#define SOC_ASP_HIFI3_TRAXCTRL_crossTriggerInEn_START                     (5)
#define SOC_ASP_HIFI3_TRAXCTRL_crossTriggerInEn_END                       (5)
#define SOC_ASP_HIFI3_TRAXCTRL_traceMemOutEn_START                        (7)
#define SOC_ASP_HIFI3_TRAXCTRL_traceMemOutEn_END                          (7)
#define SOC_ASP_HIFI3_TRAXCTRL_CountUnitIsinst_START                      (9)
#define SOC_ASP_HIFI3_TRAXCTRL_CountUnitIsinst_END                        (9)
#define SOC_ASP_HIFI3_TRAXCTRL_encodeSyncMessageFreq_START                (12)
#define SOC_ASP_HIFI3_TRAXCTRL_encodeSyncMessageFreq_END                  (14)
#define SOC_ASP_HIFI3_TRAXCTRL_processorTriggerOutUponPrimeTrigger_START  (16)
#define SOC_ASP_HIFI3_TRAXCTRL_processorTriggerOutUponPrimeTrigger_END    (16)
#define SOC_ASP_HIFI3_TRAXCTRL_processorTriggerOutUponZeroCount_START     (17)
#define SOC_ASP_HIFI3_TRAXCTRL_processorTriggerOutUponZeroCount_END       (17)
#define SOC_ASP_HIFI3_TRAXCTRL_CrossTriggerOutUponPrimeTrigger_START      (20)
#define SOC_ASP_HIFI3_TRAXCTRL_CrossTriggerOutUponPrimeTrigger_END        (20)
#define SOC_ASP_HIFI3_TRAXCTRL_CrossTriggerOutUponZeroCount_START         (21)
#define SOC_ASP_HIFI3_TRAXCTRL_CrossTriggerOutUponZeroCount_END           (21)
#define SOC_ASP_HIFI3_TRAXCTRL_CrossTriggerOutTopology_START              (22)
#define SOC_ASP_HIFI3_TRAXCTRL_CrossTriggerOutTopology_END                (22)
#define SOC_ASP_HIFI3_TRAXCTRL_CrossTriggerInAckTopology_START            (23)
#define SOC_ASP_HIFI3_TRAXCTRL_CrossTriggerInAckTopology_END              (23)
#define SOC_ASP_HIFI3_TRAXCTRL_TRAXCTRL_START                             (24)
#define SOC_ASP_HIFI3_TRAXCTRL_TRAXCTRL_END                               (31)


/*****************************************************************************
 结构名    : SOC_ASP_HIFI3_TRAXSTAT_UNION
 结构说明  : TRAXSTAT 寄存器结构定义。地址偏移量:0x0008，初值:0x00000C00，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  traceActive                : 1;  /* bit[0]    : traceActive */
        unsigned int  primeTrigger               : 1;  /* bit[1]    : primeTrigger */
        unsigned int  pcMatchImputed             : 1;  /* bit[2]    : pcMatchImputed */
        unsigned int  precedingJTAGxsacResult0   : 1;  /* bit[3]    : precedingJTAGxsacResult[0] */
        unsigned int  processTriggerInImputed    : 1;  /* bit[4]    : processTriggerInImputed */
        unsigned int  corssTriggerInImputed      : 1;  /* bit[5]    : corssTriggerInImputed */
        unsigned int  reserved_0                 : 2;  /* bit[6-7]  : reserved */
        unsigned int  reserved_1                 : 5;  /* bit[8-12] : reserved */
        unsigned int  reserved_2                 : 3;  /* bit[13-15]: reserved */
        unsigned int  processorTriggerOut        : 1;  /* bit[16]   : processorTriggerOut */
        unsigned int  crossTriggerOut            : 1;  /* bit[17]   : crossTriggerOut */
        unsigned int  reserved_3                 : 4;  /* bit[18-21]: reserved */
        unsigned int  crossTriggerOutAckTopology : 1;  /* bit[22]   : crossTriggerOutAckTopology */
        unsigned int  crossTriggerInTopology     : 1;  /* bit[23]   : crossTriggerInTopology */
        unsigned int  TRAXSTAT                   : 8;  /* bit[24-31]: reserved */
    } reg;
} SOC_ASP_HIFI3_TRAXSTAT_UNION;
#endif
#define SOC_ASP_HIFI3_TRAXSTAT_traceActive_START                 (0)
#define SOC_ASP_HIFI3_TRAXSTAT_traceActive_END                   (0)
#define SOC_ASP_HIFI3_TRAXSTAT_primeTrigger_START                (1)
#define SOC_ASP_HIFI3_TRAXSTAT_primeTrigger_END                  (1)
#define SOC_ASP_HIFI3_TRAXSTAT_pcMatchImputed_START              (2)
#define SOC_ASP_HIFI3_TRAXSTAT_pcMatchImputed_END                (2)
#define SOC_ASP_HIFI3_TRAXSTAT_precedingJTAGxsacResult0_START    (3)
#define SOC_ASP_HIFI3_TRAXSTAT_precedingJTAGxsacResult0_END      (3)
#define SOC_ASP_HIFI3_TRAXSTAT_processTriggerInImputed_START     (4)
#define SOC_ASP_HIFI3_TRAXSTAT_processTriggerInImputed_END       (4)
#define SOC_ASP_HIFI3_TRAXSTAT_corssTriggerInImputed_START       (5)
#define SOC_ASP_HIFI3_TRAXSTAT_corssTriggerInImputed_END         (5)
#define SOC_ASP_HIFI3_TRAXSTAT_processorTriggerOut_START         (16)
#define SOC_ASP_HIFI3_TRAXSTAT_processorTriggerOut_END           (16)
#define SOC_ASP_HIFI3_TRAXSTAT_crossTriggerOut_START             (17)
#define SOC_ASP_HIFI3_TRAXSTAT_crossTriggerOut_END               (17)
#define SOC_ASP_HIFI3_TRAXSTAT_crossTriggerOutAckTopology_START  (22)
#define SOC_ASP_HIFI3_TRAXSTAT_crossTriggerOutAckTopology_END    (22)
#define SOC_ASP_HIFI3_TRAXSTAT_crossTriggerInTopology_START      (23)
#define SOC_ASP_HIFI3_TRAXSTAT_crossTriggerInTopology_END        (23)
#define SOC_ASP_HIFI3_TRAXSTAT_TRAXSTAT_START                    (24)
#define SOC_ASP_HIFI3_TRAXSTAT_TRAXSTAT_END                      (31)


/*****************************************************************************
 结构名    : SOC_ASP_HIFI3_TRAXDATA_UNION
 结构说明  : TRAXDATA 寄存器结构定义。地址偏移量:0x000C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  TRAXDATA : 32; /* bit[0-31]: TRAX Data Register */
    } reg;
} SOC_ASP_HIFI3_TRAXDATA_UNION;
#endif
#define SOC_ASP_HIFI3_TRAXDATA_TRAXDATA_START  (0)
#define SOC_ASP_HIFI3_TRAXDATA_TRAXDATA_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_HIFI3_TRAXADDR_UNION
 结构说明  : TRAXADDR 寄存器结构定义。地址偏移量:0x0010，初值:0x00000001，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  TRAXADDR : 32; /* bit[0-31]: TRAX Address Register */
    } reg;
} SOC_ASP_HIFI3_TRAXADDR_UNION;
#endif
#define SOC_ASP_HIFI3_TRAXADDR_TRAXADDR_START  (0)
#define SOC_ASP_HIFI3_TRAXADDR_TRAXADDR_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_HIFI3_TRIGGERPC_UNION
 结构说明  : TRIGGERPC 寄存器结构定义。地址偏移量:0x0014，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  TRIGGERPC : 32; /* bit[0-31]: TRAX Stop PC */
    } reg;
} SOC_ASP_HIFI3_TRIGGERPC_UNION;
#endif
#define SOC_ASP_HIFI3_TRIGGERPC_TRIGGERPC_START  (0)
#define SOC_ASP_HIFI3_TRIGGERPC_TRIGGERPC_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_HIFI3_PCMATCHCTRL_UNION
 结构说明  : PCMATCHCTRL 寄存器结构定义。地址偏移量:0x0018，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  PCMATCHCTRL : 32; /* bit[0-31]: TRAX Stop PC Range */
    } reg;
} SOC_ASP_HIFI3_PCMATCHCTRL_UNION;
#endif
#define SOC_ASP_HIFI3_PCMATCHCTRL_PCMATCHCTRL_START  (0)
#define SOC_ASP_HIFI3_PCMATCHCTRL_PCMATCHCTRL_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_HIFI3_DELAYCNT_UNION
 结构说明  : DELAYCNT 寄存器结构定义。地址偏移量:0x001C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  DELAYCNT : 32; /* bit[0-31]: TRAX Post Stop Capture Size */
    } reg;
} SOC_ASP_HIFI3_DELAYCNT_UNION;
#endif
#define SOC_ASP_HIFI3_DELAYCNT_DELAYCNT_START  (0)
#define SOC_ASP_HIFI3_DELAYCNT_DELAYCNT_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_HIFI3_MEMADDRSTART_UNION
 结构说明  : MEMADDRSTART 寄存器结构定义。地址偏移量:0x0020，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  MEMADDRSTART : 32; /* bit[0-31]: Trace memory start address */
    } reg;
} SOC_ASP_HIFI3_MEMADDRSTART_UNION;
#endif
#define SOC_ASP_HIFI3_MEMADDRSTART_MEMADDRSTART_START  (0)
#define SOC_ASP_HIFI3_MEMADDRSTART_MEMADDRSTART_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_HIFI3_MEMADDREND_UNION
 结构说明  : MEMADDREND 寄存器结构定义。地址偏移量:0x0024，初值:0x000003FF，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  MEMADDREND : 32; /* bit[0-31]: Trace memory end address */
    } reg;
} SOC_ASP_HIFI3_MEMADDREND_UNION;
#endif
#define SOC_ASP_HIFI3_MEMADDREND_MEMADDREND_START  (0)
#define SOC_ASP_HIFI3_MEMADDREND_MEMADDREND_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_HIFI3_compressparams_UNION
 结构说明  : compressparams 寄存器结构定义。地址偏移量:0x006C，初值:0x06710671，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cp2 : 16; /* bit[0-15] : cp2[15:0] */
        unsigned int  cp1 : 16; /* bit[16-31]: cp1[15:0] */
    } reg;
} SOC_ASP_HIFI3_compressparams_UNION;
#endif
#define SOC_ASP_HIFI3_compressparams_cp2_START  (0)
#define SOC_ASP_HIFI3_compressparams_cp2_END    (15)
#define SOC_ASP_HIFI3_compressparams_cp1_START  (16)
#define SOC_ASP_HIFI3_compressparams_cp1_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_HIFI3_PMG_UNION
 结构说明  : PMG 寄存器结构定义。地址偏移量:0x1000，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pergloben : 1;  /* bit[0-0] : overall enable for all performance counting */
        unsigned int  PMG       : 31; /* bit[1-31]: reserved */
    } reg;
} SOC_ASP_HIFI3_PMG_UNION;
#endif
#define SOC_ASP_HIFI3_PMG_pergloben_START  (0)
#define SOC_ASP_HIFI3_PMG_pergloben_END    (0)
#define SOC_ASP_HIFI3_PMG_PMG_START        (1)
#define SOC_ASP_HIFI3_PMG_PMG_END          (31)


/*****************************************************************************
 结构名    : SOC_ASP_HIFI3_INTPC_UNION
 结构说明  : INTPC 寄存器结构定义。地址偏移量:0x1010，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  INTPC : 32; /* bit[0-31]: PC at cycle of last event that cause interrupt */
    } reg;
} SOC_ASP_HIFI3_INTPC_UNION;
#endif
#define SOC_ASP_HIFI3_INTPC_INTPC_START  (0)
#define SOC_ASP_HIFI3_INTPC_INTPC_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_HIFI3_perfcounter0_UNION
 结构说明  : perfcounter0 寄存器结构定义。地址偏移量:0x1080，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  PM0 : 32; /* bit[0-31]: performanc counter0 values */
    } reg;
} SOC_ASP_HIFI3_perfcounter0_UNION;
#endif
#define SOC_ASP_HIFI3_perfcounter0_PM0_START  (0)
#define SOC_ASP_HIFI3_perfcounter0_PM0_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_HIFI3_perfcounter1_UNION
 结构说明  : perfcounter1 寄存器结构定义。地址偏移量:0x1084，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  PM1 : 32; /* bit[0-31]: performanc counter1 values */
    } reg;
} SOC_ASP_HIFI3_perfcounter1_UNION;
#endif
#define SOC_ASP_HIFI3_perfcounter1_PM1_START  (0)
#define SOC_ASP_HIFI3_perfcounter1_PM1_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_HIFI3_perfcounter2_UNION
 结构说明  : perfcounter2 寄存器结构定义。地址偏移量:0x1088，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  PM2 : 32; /* bit[0-31]: performanc counter2 values */
    } reg;
} SOC_ASP_HIFI3_perfcounter2_UNION;
#endif
#define SOC_ASP_HIFI3_perfcounter2_PM2_START  (0)
#define SOC_ASP_HIFI3_perfcounter2_PM2_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_HIFI3_perfcounter3_UNION
 结构说明  : perfcounter3 寄存器结构定义。地址偏移量:0x108C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  PM3 : 32; /* bit[0-31]: performanc counter3 values */
    } reg;
} SOC_ASP_HIFI3_perfcounter3_UNION;
#endif
#define SOC_ASP_HIFI3_perfcounter3_PM3_START  (0)
#define SOC_ASP_HIFI3_perfcounter3_PM3_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_HIFI3_PMCTRL0_UNION
 结构说明  : PMCTRL0 寄存器结构定义。地址偏移量:0x1100，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  perfIntEn0   : 1;  /* bit[0-0]  : perfIntEn0 */
        unsigned int  reserved_0   : 2;  /* bit[1-2]  : reserved */
        unsigned int  kernelcount0 : 1;  /* bit[3-3]  : kernelcount0 */
        unsigned int  traceLevel0  : 4;  /* bit[4-7]  : traceLevel0 */
        unsigned int  perfSelect0  : 5;  /* bit[8-12] : perfSelect0 */
        unsigned int  reserved_1   : 3;  /* bit[13-15]: reserved */
        unsigned int  perMask0     : 16; /* bit[16-31]: perMask0 */
    } reg;
} SOC_ASP_HIFI3_PMCTRL0_UNION;
#endif
#define SOC_ASP_HIFI3_PMCTRL0_perfIntEn0_START    (0)
#define SOC_ASP_HIFI3_PMCTRL0_perfIntEn0_END      (0)
#define SOC_ASP_HIFI3_PMCTRL0_kernelcount0_START  (3)
#define SOC_ASP_HIFI3_PMCTRL0_kernelcount0_END    (3)
#define SOC_ASP_HIFI3_PMCTRL0_traceLevel0_START   (4)
#define SOC_ASP_HIFI3_PMCTRL0_traceLevel0_END     (7)
#define SOC_ASP_HIFI3_PMCTRL0_perfSelect0_START   (8)
#define SOC_ASP_HIFI3_PMCTRL0_perfSelect0_END     (12)
#define SOC_ASP_HIFI3_PMCTRL0_perMask0_START      (16)
#define SOC_ASP_HIFI3_PMCTRL0_perMask0_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_HIFI3_PMCTRL1_UNION
 结构说明  : PMCTRL1 寄存器结构定义。地址偏移量:0x1104，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  perfIntEn1   : 1;  /* bit[0-0]  : perfIntEn1 */
        unsigned int  reserved_0   : 2;  /* bit[1-2]  : reserved */
        unsigned int  kernelcount1 : 1;  /* bit[3-3]  : kernelcount1 */
        unsigned int  traceLevel1  : 4;  /* bit[4-7]  : traceLevel1 */
        unsigned int  perfSelect1  : 5;  /* bit[8-12] : perfSelect1 */
        unsigned int  reserved_1   : 3;  /* bit[13-15]: reserved */
        unsigned int  perMask1     : 16; /* bit[16-31]: perMask1 */
    } reg;
} SOC_ASP_HIFI3_PMCTRL1_UNION;
#endif
#define SOC_ASP_HIFI3_PMCTRL1_perfIntEn1_START    (0)
#define SOC_ASP_HIFI3_PMCTRL1_perfIntEn1_END      (0)
#define SOC_ASP_HIFI3_PMCTRL1_kernelcount1_START  (3)
#define SOC_ASP_HIFI3_PMCTRL1_kernelcount1_END    (3)
#define SOC_ASP_HIFI3_PMCTRL1_traceLevel1_START   (4)
#define SOC_ASP_HIFI3_PMCTRL1_traceLevel1_END     (7)
#define SOC_ASP_HIFI3_PMCTRL1_perfSelect1_START   (8)
#define SOC_ASP_HIFI3_PMCTRL1_perfSelect1_END     (12)
#define SOC_ASP_HIFI3_PMCTRL1_perMask1_START      (16)
#define SOC_ASP_HIFI3_PMCTRL1_perMask1_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_HIFI3_PMCTRL2_UNION
 结构说明  : PMCTRL2 寄存器结构定义。地址偏移量:0x1108，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  perfIntEn2   : 1;  /* bit[0-0]  : perfIntEn2 */
        unsigned int  reserved_0   : 2;  /* bit[1-2]  : reserved */
        unsigned int  kernelcount2 : 1;  /* bit[3-3]  : kernelcount2 */
        unsigned int  traceLevel2  : 4;  /* bit[4-7]  : traceLevel2 */
        unsigned int  perfSelect2  : 5;  /* bit[8-12] : perfSelect2 */
        unsigned int  reserved_1   : 3;  /* bit[13-15]: reserved */
        unsigned int  perMask2     : 16; /* bit[16-31]: perMask2 */
    } reg;
} SOC_ASP_HIFI3_PMCTRL2_UNION;
#endif
#define SOC_ASP_HIFI3_PMCTRL2_perfIntEn2_START    (0)
#define SOC_ASP_HIFI3_PMCTRL2_perfIntEn2_END      (0)
#define SOC_ASP_HIFI3_PMCTRL2_kernelcount2_START  (3)
#define SOC_ASP_HIFI3_PMCTRL2_kernelcount2_END    (3)
#define SOC_ASP_HIFI3_PMCTRL2_traceLevel2_START   (4)
#define SOC_ASP_HIFI3_PMCTRL2_traceLevel2_END     (7)
#define SOC_ASP_HIFI3_PMCTRL2_perfSelect2_START   (8)
#define SOC_ASP_HIFI3_PMCTRL2_perfSelect2_END     (12)
#define SOC_ASP_HIFI3_PMCTRL2_perMask2_START      (16)
#define SOC_ASP_HIFI3_PMCTRL2_perMask2_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_HIFI3_PMCTRL3_UNION
 结构说明  : PMCTRL3 寄存器结构定义。地址偏移量:0x110C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  perfIntEn3   : 1;  /* bit[0-0]  : perfIntEn3 */
        unsigned int  reserved_0   : 2;  /* bit[1-2]  : reserved */
        unsigned int  kernelcount3 : 1;  /* bit[3-3]  : kernelcount3 */
        unsigned int  traceLevel3  : 4;  /* bit[4-7]  : traceLevel3 */
        unsigned int  perfSelect3  : 5;  /* bit[8-12] : perfSelect3 */
        unsigned int  reserved_1   : 3;  /* bit[13-15]: reserved */
        unsigned int  perMask3     : 16; /* bit[16-31]: perMask3 */
    } reg;
} SOC_ASP_HIFI3_PMCTRL3_UNION;
#endif
#define SOC_ASP_HIFI3_PMCTRL3_perfIntEn3_START    (0)
#define SOC_ASP_HIFI3_PMCTRL3_perfIntEn3_END      (0)
#define SOC_ASP_HIFI3_PMCTRL3_kernelcount3_START  (3)
#define SOC_ASP_HIFI3_PMCTRL3_kernelcount3_END    (3)
#define SOC_ASP_HIFI3_PMCTRL3_traceLevel3_START   (4)
#define SOC_ASP_HIFI3_PMCTRL3_traceLevel3_END     (7)
#define SOC_ASP_HIFI3_PMCTRL3_perfSelect3_START   (8)
#define SOC_ASP_HIFI3_PMCTRL3_perfSelect3_END     (12)
#define SOC_ASP_HIFI3_PMCTRL3_perMask3_START      (16)
#define SOC_ASP_HIFI3_PMCTRL3_perMask3_END        (31)


/*****************************************************************************
 结构名    : SOC_ASP_HIFI3_PMSTA0_UNION
 结构说明  : PMSTA0 寄存器结构定义。地址偏移量:0x1180，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  perfverflow0     : 1;  /* bit[0-0] : perOverflow0 */
        unsigned int  reserved_0       : 3;  /* bit[1-3] : reserved */
        unsigned int  perfIntAsserted0 : 1;  /* bit[4-4] : perfIntAsserted0 */
        unsigned int  reserved_1       : 27; /* bit[5-31]: performance counter0 status register */
    } reg;
} SOC_ASP_HIFI3_PMSTA0_UNION;
#endif
#define SOC_ASP_HIFI3_PMSTA0_perfverflow0_START      (0)
#define SOC_ASP_HIFI3_PMSTA0_perfverflow0_END        (0)
#define SOC_ASP_HIFI3_PMSTA0_perfIntAsserted0_START  (4)
#define SOC_ASP_HIFI3_PMSTA0_perfIntAsserted0_END    (4)


/*****************************************************************************
 结构名    : SOC_ASP_HIFI3_PMSTA1_UNION
 结构说明  : PMSTA1 寄存器结构定义。地址偏移量:0x1184，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  perfverflow1     : 1;  /* bit[0-0] : perOverflow1 */
        unsigned int  reserved_0       : 3;  /* bit[1-3] : reserved */
        unsigned int  perfIntAsserted1 : 1;  /* bit[4-4] : perfIntAsserted1 */
        unsigned int  reserved_1       : 27; /* bit[5-31]: performance counter1 status register */
    } reg;
} SOC_ASP_HIFI3_PMSTA1_UNION;
#endif
#define SOC_ASP_HIFI3_PMSTA1_perfverflow1_START      (0)
#define SOC_ASP_HIFI3_PMSTA1_perfverflow1_END        (0)
#define SOC_ASP_HIFI3_PMSTA1_perfIntAsserted1_START  (4)
#define SOC_ASP_HIFI3_PMSTA1_perfIntAsserted1_END    (4)


/*****************************************************************************
 结构名    : SOC_ASP_HIFI3_PMSTA2_UNION
 结构说明  : PMSTA2 寄存器结构定义。地址偏移量:0x1188，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  perfverflow2     : 1;  /* bit[0-0] : perOverflow2 */
        unsigned int  reserved_0       : 3;  /* bit[1-3] : reserved */
        unsigned int  perfIntAsserted2 : 1;  /* bit[4-4] : perfIntAsserted2 */
        unsigned int  reserved_1       : 27; /* bit[5-31]: performance counter2 status register */
    } reg;
} SOC_ASP_HIFI3_PMSTA2_UNION;
#endif
#define SOC_ASP_HIFI3_PMSTA2_perfverflow2_START      (0)
#define SOC_ASP_HIFI3_PMSTA2_perfverflow2_END        (0)
#define SOC_ASP_HIFI3_PMSTA2_perfIntAsserted2_START  (4)
#define SOC_ASP_HIFI3_PMSTA2_perfIntAsserted2_END    (4)


/*****************************************************************************
 结构名    : SOC_ASP_HIFI3_PMSTA3_UNION
 结构说明  : PMSTA3 寄存器结构定义。地址偏移量:0x118C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  perfverflow3     : 1;  /* bit[0-0] : perOverflow3 */
        unsigned int  reserved_0       : 3;  /* bit[1-3] : reserved */
        unsigned int  perfIntAsserted3 : 1;  /* bit[4-4] : perfIntAsserted3 */
        unsigned int  reserved_1       : 27; /* bit[5-31]: performance counter3 status register */
    } reg;
} SOC_ASP_HIFI3_PMSTA3_UNION;
#endif
#define SOC_ASP_HIFI3_PMSTA3_perfverflow3_START      (0)
#define SOC_ASP_HIFI3_PMSTA3_perfverflow3_END        (0)
#define SOC_ASP_HIFI3_PMSTA3_perfIntAsserted3_START  (4)
#define SOC_ASP_HIFI3_PMSTA3_perfIntAsserted3_END    (4)


/*****************************************************************************
 结构名    : SOC_ASP_HIFI3_OCDID_UNION
 结构说明  : OCDID 寄存器结构定义。地址偏移量:0x2000，初值:0x0D338FF2，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  OCDID : 32; /* bit[0-31]: ID register */
    } reg;
} SOC_ASP_HIFI3_OCDID_UNION;
#endif
#define SOC_ASP_HIFI3_OCDID_OCDID_START  (0)
#define SOC_ASP_HIFI3_OCDID_OCDID_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_HIFI3_DCRCLR_UNION
 结构说明  : DCRCLR 寄存器结构定义。地址偏移量:0x2008，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  enableOCD          : 1;  /* bit[0-0]  : enableOCD */
        unsigned int  hostDebugInterrupt : 1;  /* bit[1-1]  : hostDebugInterrupt */
        unsigned int  induceOCDoverride  : 1;  /* bit[2-2]  : induceOCDoverride */
        unsigned int  reserved_0         : 13; /* bit[3-15] : reserved */
        unsigned int  extDbgIntEn        : 1;  /* bit[16-16]: extDbgIntEn */
        unsigned int  xOCDModePulseEn    : 1;  /* bit[17-17]: xOCDModePulseEn */
        unsigned int  reserved_1         : 6;  /* bit[18-23]: reserved */
        unsigned int  breakOutTopology   : 1;  /* bit[24-24]: breakOutTopology */
        unsigned int  breakInAckTopology : 1;  /* bit[25-25]: breakInAckTopology */
        unsigned int  reserved_2         : 6;  /* bit[26-31]: debug control register,wtite to clear */
    } reg;
} SOC_ASP_HIFI3_DCRCLR_UNION;
#endif
#define SOC_ASP_HIFI3_DCRCLR_enableOCD_START           (0)
#define SOC_ASP_HIFI3_DCRCLR_enableOCD_END             (0)
#define SOC_ASP_HIFI3_DCRCLR_hostDebugInterrupt_START  (1)
#define SOC_ASP_HIFI3_DCRCLR_hostDebugInterrupt_END    (1)
#define SOC_ASP_HIFI3_DCRCLR_induceOCDoverride_START   (2)
#define SOC_ASP_HIFI3_DCRCLR_induceOCDoverride_END     (2)
#define SOC_ASP_HIFI3_DCRCLR_extDbgIntEn_START         (16)
#define SOC_ASP_HIFI3_DCRCLR_extDbgIntEn_END           (16)
#define SOC_ASP_HIFI3_DCRCLR_xOCDModePulseEn_START     (17)
#define SOC_ASP_HIFI3_DCRCLR_xOCDModePulseEn_END       (17)
#define SOC_ASP_HIFI3_DCRCLR_breakOutTopology_START    (24)
#define SOC_ASP_HIFI3_DCRCLR_breakOutTopology_END      (24)
#define SOC_ASP_HIFI3_DCRCLR_breakInAckTopology_START  (25)
#define SOC_ASP_HIFI3_DCRCLR_breakInAckTopology_END    (25)


/*****************************************************************************
 结构名    : SOC_ASP_HIFI3_DCRSET_UNION
 结构说明  : DCRSET 寄存器结构定义。地址偏移量:0x200C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  enableOCD          : 1;  /* bit[0-0]  : enableOCD */
        unsigned int  hostDebugInterrupt : 1;  /* bit[1-1]  : hostDebugInterrupt */
        unsigned int  induceOCDoverride  : 1;  /* bit[2-2]  : induceOCDoverride */
        unsigned int  reserved_0         : 13; /* bit[3-15] : reserved */
        unsigned int  extDbgIntEn        : 1;  /* bit[16-16]: extDbgIntEn */
        unsigned int  xOCDModePulseEn    : 1;  /* bit[17-17]: xOCDModePulseEn */
        unsigned int  reserved_1         : 6;  /* bit[18-23]: reserved */
        unsigned int  breakOutTopology   : 1;  /* bit[24-24]: breakOutTopology */
        unsigned int  breakInAckTopology : 1;  /* bit[25-25]: breakInAckTopology */
        unsigned int  DCRSET             : 6;  /* bit[26-31]: debug control register,wtite to set */
    } reg;
} SOC_ASP_HIFI3_DCRSET_UNION;
#endif
#define SOC_ASP_HIFI3_DCRSET_enableOCD_START           (0)
#define SOC_ASP_HIFI3_DCRSET_enableOCD_END             (0)
#define SOC_ASP_HIFI3_DCRSET_hostDebugInterrupt_START  (1)
#define SOC_ASP_HIFI3_DCRSET_hostDebugInterrupt_END    (1)
#define SOC_ASP_HIFI3_DCRSET_induceOCDoverride_START   (2)
#define SOC_ASP_HIFI3_DCRSET_induceOCDoverride_END     (2)
#define SOC_ASP_HIFI3_DCRSET_extDbgIntEn_START         (16)
#define SOC_ASP_HIFI3_DCRSET_extDbgIntEn_END           (16)
#define SOC_ASP_HIFI3_DCRSET_xOCDModePulseEn_START     (17)
#define SOC_ASP_HIFI3_DCRSET_xOCDModePulseEn_END       (17)
#define SOC_ASP_HIFI3_DCRSET_breakOutTopology_START    (24)
#define SOC_ASP_HIFI3_DCRSET_breakOutTopology_END      (24)
#define SOC_ASP_HIFI3_DCRSET_breakInAckTopology_START  (25)
#define SOC_ASP_HIFI3_DCRSET_breakInAckTopology_END    (25)
#define SOC_ASP_HIFI3_DCRSET_DCRSET_START              (26)
#define SOC_ASP_HIFI3_DCRSET_DCRSET_END                (31)


/*****************************************************************************
 结构名    : SOC_ASP_HIFI3_DSR_UNION
 结构说明  : DSR 寄存器结构定义。地址偏移量:0x2010，初值:0x02000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  execDone           : 1;  /* bit[0-0]  : execDone */
        unsigned int  exeException       : 1;  /* bit[1-1]  : exeException */
        unsigned int  exeBusy            : 1;  /* bit[2-2]  : exeBusy */
        unsigned int  execOverrun        : 1;  /* bit[3-3]  : execOverrun */
        unsigned int  ocdDtopped         : 1;  /* bit[4-4]  : ocdDtopped */
        unsigned int  reserved_0         : 5;  /* bit[5-9]  : reserved */
        unsigned int  corewroteDDR       : 1;  /* bit[10-10]: corewroteDDR */
        unsigned int  coreReadDDR        : 1;  /* bit[11-11]: coreReadDDR */
        unsigned int  reserved_1         : 2;  /* bit[12-13]: reserved */
        unsigned int  hostWroteDDR       : 1;  /* bit[14-14]: hostWroteDDR */
        unsigned int  hostReadDDR        : 1;  /* bit[15-15]: hostReadDDR */
        unsigned int  debugPendBreakin   : 1;  /* bit[16-16]: debugPendBreakin */
        unsigned int  debugpendhost      : 1;  /* bit[17-17]: debugpendhost */
        unsigned int  debugpendtrax      : 1;  /* bit[18-18]: debugPendTrax */
        unsigned int  reserved_2         : 1;  /* bit[19-19]: reserved */
        unsigned int  debugIntBreakin    : 1;  /* bit[20-20]: debugIntBreakin */
        unsigned int  debugIntHost       : 1;  /* bit[21-21]: debugIntHost */
        unsigned int  debugIntTrax       : 1;  /* bit[22-22]: debugIntTrax */
        unsigned int  reserved_3         : 2;  /* bit[23-24]: reserved */
        unsigned int  beakOutAckTopology : 1;  /* bit[25-25]: beakOutAckTopology */
        unsigned int  breakInTopology    : 1;  /* bit[26-26]: breakInTopology */
        unsigned int  reserved_4         : 5;  /* bit[27-31]: debug status register */
    } reg;
} SOC_ASP_HIFI3_DSR_UNION;
#endif
#define SOC_ASP_HIFI3_DSR_execDone_START            (0)
#define SOC_ASP_HIFI3_DSR_execDone_END              (0)
#define SOC_ASP_HIFI3_DSR_exeException_START        (1)
#define SOC_ASP_HIFI3_DSR_exeException_END          (1)
#define SOC_ASP_HIFI3_DSR_exeBusy_START             (2)
#define SOC_ASP_HIFI3_DSR_exeBusy_END               (2)
#define SOC_ASP_HIFI3_DSR_execOverrun_START         (3)
#define SOC_ASP_HIFI3_DSR_execOverrun_END           (3)
#define SOC_ASP_HIFI3_DSR_ocdDtopped_START          (4)
#define SOC_ASP_HIFI3_DSR_ocdDtopped_END            (4)
#define SOC_ASP_HIFI3_DSR_corewroteDDR_START        (10)
#define SOC_ASP_HIFI3_DSR_corewroteDDR_END          (10)
#define SOC_ASP_HIFI3_DSR_coreReadDDR_START         (11)
#define SOC_ASP_HIFI3_DSR_coreReadDDR_END           (11)
#define SOC_ASP_HIFI3_DSR_hostWroteDDR_START        (14)
#define SOC_ASP_HIFI3_DSR_hostWroteDDR_END          (14)
#define SOC_ASP_HIFI3_DSR_hostReadDDR_START         (15)
#define SOC_ASP_HIFI3_DSR_hostReadDDR_END           (15)
#define SOC_ASP_HIFI3_DSR_debugPendBreakin_START    (16)
#define SOC_ASP_HIFI3_DSR_debugPendBreakin_END      (16)
#define SOC_ASP_HIFI3_DSR_debugpendhost_START       (17)
#define SOC_ASP_HIFI3_DSR_debugpendhost_END         (17)
#define SOC_ASP_HIFI3_DSR_debugpendtrax_START       (18)
#define SOC_ASP_HIFI3_DSR_debugpendtrax_END         (18)
#define SOC_ASP_HIFI3_DSR_debugIntBreakin_START     (20)
#define SOC_ASP_HIFI3_DSR_debugIntBreakin_END       (20)
#define SOC_ASP_HIFI3_DSR_debugIntHost_START        (21)
#define SOC_ASP_HIFI3_DSR_debugIntHost_END          (21)
#define SOC_ASP_HIFI3_DSR_debugIntTrax_START        (22)
#define SOC_ASP_HIFI3_DSR_debugIntTrax_END          (22)
#define SOC_ASP_HIFI3_DSR_beakOutAckTopology_START  (25)
#define SOC_ASP_HIFI3_DSR_beakOutAckTopology_END    (25)
#define SOC_ASP_HIFI3_DSR_breakInTopology_START     (26)
#define SOC_ASP_HIFI3_DSR_breakInTopology_END       (26)


/*****************************************************************************
 结构名    : SOC_ASP_HIFI3_DDR_UNION
 结构说明  : DDR 寄存器结构定义。地址偏移量:0x2014，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  DDR : 32; /* bit[0-31]: debug data register */
    } reg;
} SOC_ASP_HIFI3_DDR_UNION;
#endif
#define SOC_ASP_HIFI3_DDR_DDR_START  (0)
#define SOC_ASP_HIFI3_DDR_DDR_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_HIFI3_DDREXEC_UNION
 结构说明  : DDREXEC 寄存器结构定义。地址偏移量:0x2018，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  DDREXEC : 32; /* bit[0-31]: alias DDR, execute DIR when accessed  */
    } reg;
} SOC_ASP_HIFI3_DDREXEC_UNION;
#endif
#define SOC_ASP_HIFI3_DDREXEC_DDREXEC_START  (0)
#define SOC_ASP_HIFI3_DDREXEC_DDREXEC_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_HIFI3_DIR0EXEC_UNION
 结构说明  : DIR0EXEC 寄存器结构定义。地址偏移量:0x201C，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  DIR0EXEC : 32; /* bit[0-31]: alias DIR0, execute instruction when written  */
    } reg;
} SOC_ASP_HIFI3_DIR0EXEC_UNION;
#endif
#define SOC_ASP_HIFI3_DIR0EXEC_DIR0EXEC_START  (0)
#define SOC_ASP_HIFI3_DIR0EXEC_DIR0EXEC_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_HIFI3_denugInst0_UNION
 结构说明  : denugInst0 寄存器结构定义。地址偏移量:0x2020，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  denugInst0 : 32; /* bit[0-31]: denugInst0 */
    } reg;
} SOC_ASP_HIFI3_denugInst0_UNION;
#endif
#define SOC_ASP_HIFI3_denugInst0_denugInst0_START  (0)
#define SOC_ASP_HIFI3_denugInst0_denugInst0_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_HIFI3_debugInst1_UNION
 结构说明  : debugInst1 寄存器结构定义。地址偏移量:0x2024，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  debugInst1 : 32; /* bit[0-31]: debugInst1 */
    } reg;
} SOC_ASP_HIFI3_debugInst1_UNION;
#endif
#define SOC_ASP_HIFI3_debugInst1_debugInst1_START  (0)
#define SOC_ASP_HIFI3_debugInst1_debugInst1_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_HIFI3_PWRCTL_UNION
 结构说明  : PWRCTL 寄存器结构定义。地址偏移量:0x3020，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0    : 16; /* bit[0-15] : reserved */
        unsigned int  apbcorereset  : 1;  /* bit[16-16]: setting to 1 asserts reset to the core */
        unsigned int  reserved_1    : 11; /* bit[17-27]: reserved */
        unsigned int  apbdebugreset : 1;  /* bit[28-28]: setting to 1 assert reset to debug module */
        unsigned int  pwrctl        : 3;  /* bit[29-31]: power and reset control */
    } reg;
} SOC_ASP_HIFI3_PWRCTL_UNION;
#endif
#define SOC_ASP_HIFI3_PWRCTL_apbcorereset_START   (16)
#define SOC_ASP_HIFI3_PWRCTL_apbcorereset_END     (16)
#define SOC_ASP_HIFI3_PWRCTL_apbdebugreset_START  (28)
#define SOC_ASP_HIFI3_PWRCTL_apbdebugreset_END    (28)
#define SOC_ASP_HIFI3_PWRCTL_pwrctl_START         (29)
#define SOC_ASP_HIFI3_PWRCTL_pwrctl_END           (31)


/*****************************************************************************
 结构名    : SOC_ASP_HIFI3_PWRSTAT_UNION
 结构说明  : PWRSTAT 寄存器结构定义。地址偏移量:0x3024，初值:0x30011111，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0       : 16; /* bit[0-15] : reserved */
        unsigned int  apbcorewasreset  : 1;  /* bit[16-16]: apb core was reset */
        unsigned int  reserved_1       : 11; /* bit[17-27]: reserved */
        unsigned int  apbdebugwasreset : 1;  /* bit[28-28]: apbdebug was reset */
        unsigned int  PWRSTAT          : 3;  /* bit[29-31]: power and reset status */
    } reg;
} SOC_ASP_HIFI3_PWRSTAT_UNION;
#endif
#define SOC_ASP_HIFI3_PWRSTAT_apbcorewasreset_START   (16)
#define SOC_ASP_HIFI3_PWRSTAT_apbcorewasreset_END     (16)
#define SOC_ASP_HIFI3_PWRSTAT_apbdebugwasreset_START  (28)
#define SOC_ASP_HIFI3_PWRSTAT_apbdebugwasreset_END    (28)
#define SOC_ASP_HIFI3_PWRSTAT_PWRSTAT_START           (29)
#define SOC_ASP_HIFI3_PWRSTAT_PWRSTAT_END             (31)


/*****************************************************************************
 结构名    : SOC_ASP_HIFI3_ERISTAT_UNION
 结构说明  : ERISTAT 寄存器结构定义。地址偏移量:0x3028，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stickyErriWrResult : 1;  /* bit[0-0] : stickyErriWrResult */
        unsigned int  reserved           : 31; /* bit[1-31]: ERI transaction status */
    } reg;
} SOC_ASP_HIFI3_ERISTAT_UNION;
#endif
#define SOC_ASP_HIFI3_ERISTAT_stickyErriWrResult_START  (0)
#define SOC_ASP_HIFI3_ERISTAT_stickyErriWrResult_END    (0)


/*****************************************************************************
 结构名    : SOC_ASP_HIFI3_undoRegThID1_UNION
 结构说明  : undoRegThID1 寄存器结构定义。地址偏移量:0x3034，初值:0x19450671，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  undoRegThID1 : 32; /* bit[0-31]: undoRegThID1 */
    } reg;
} SOC_ASP_HIFI3_undoRegThID1_UNION;
#endif
#define SOC_ASP_HIFI3_undoRegThID1_undoRegThID1_START  (0)
#define SOC_ASP_HIFI3_undoRegThID1_undoRegThID1_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_HIFI3_undocRegBuild_UNION
 结构说明  : undocRegBuild 寄存器结构定义。地址偏移量:0x3038，初值:0x00050671，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  undocRegBuild : 32; /* bit[0-31]: undocRegBuild */
    } reg;
} SOC_ASP_HIFI3_undocRegBuild_UNION;
#endif
#define SOC_ASP_HIFI3_undocRegBuild_undocRegBuild_START  (0)
#define SOC_ASP_HIFI3_undocRegBuild_undocRegBuild_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_HIFI3_undocRegBcid_UNION
 结构说明  : undocRegBcid 寄存器结构定义。地址偏移量:0x303C，初值:0x000023B3，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  undocRegBcid : 32; /* bit[0-31]: undocRegBcid */
    } reg;
} SOC_ASP_HIFI3_undocRegBcid_UNION;
#endif
#define SOC_ASP_HIFI3_undocRegBcid_undocRegBcid_START  (0)
#define SOC_ASP_HIFI3_undocRegBcid_undocRegBcid_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_HIFI3_itCtrl_UNION
 结构说明  : itCtrl 寄存器结构定义。地址偏移量:0x3F00，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  itCtrl   : 1;  /* bit[0-0] : itCtrl */
        unsigned int  reserved : 31; /* bit[1-31]: reserved */
    } reg;
} SOC_ASP_HIFI3_itCtrl_UNION;
#endif
#define SOC_ASP_HIFI3_itCtrl_itCtrl_START    (0)
#define SOC_ASP_HIFI3_itCtrl_itCtrl_END      (0)


/*****************************************************************************
 结构名    : SOC_ASP_HIFI3_claimSet_UNION
 结构说明  : claimSet 寄存器结构定义。地址偏移量:0x3FA0，初值:0x0000FFFF，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  claimSet : 32; /* bit[0-31]: claimSet */
    } reg;
} SOC_ASP_HIFI3_claimSet_UNION;
#endif
#define SOC_ASP_HIFI3_claimSet_claimSet_START  (0)
#define SOC_ASP_HIFI3_claimSet_claimSet_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_HIFI3_claimClear_UNION
 结构说明  : claimClear 寄存器结构定义。地址偏移量:0x3FA4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  claimClear : 32; /* bit[0-31]: claimClear */
    } reg;
} SOC_ASP_HIFI3_claimClear_UNION;
#endif
#define SOC_ASP_HIFI3_claimClear_claimClear_START  (0)
#define SOC_ASP_HIFI3_claimClear_claimClear_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_HIFI3_devId_UNION
 结构说明  : devId 寄存器结构定义。地址偏移量:0x3FC8，初值:0x120034E5，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  devId : 32; /* bit[0-31]: devId */
    } reg;
} SOC_ASP_HIFI3_devId_UNION;
#endif
#define SOC_ASP_HIFI3_devId_devId_START  (0)
#define SOC_ASP_HIFI3_devId_devId_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_HIFI3_devType_UNION
 结构说明  : devType 寄存器结构定义。地址偏移量:0x3FCC，初值:0x00000013，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  devType : 32; /* bit[0-31]: devType */
    } reg;
} SOC_ASP_HIFI3_devType_UNION;
#endif
#define SOC_ASP_HIFI3_devType_devType_START  (0)
#define SOC_ASP_HIFI3_devType_devType_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_HIFI3_peripheralId4_UNION
 结构说明  : peripheralId4 寄存器结构定义。地址偏移量:0x3FD0，初值:0x00000024，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  peripheralId4 : 32; /* bit[0-31]: peripheralId4 */
    } reg;
} SOC_ASP_HIFI3_peripheralId4_UNION;
#endif
#define SOC_ASP_HIFI3_peripheralId4_peripheralId4_START  (0)
#define SOC_ASP_HIFI3_peripheralId4_peripheralId4_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_HIFI3_peripheralId5_UNION
 结构说明  : peripheralId5 寄存器结构定义。地址偏移量:0x3FD4，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  peripheralId5 : 32; /* bit[0-31]: peripheralId5 */
    } reg;
} SOC_ASP_HIFI3_peripheralId5_UNION;
#endif
#define SOC_ASP_HIFI3_peripheralId5_peripheralId5_START  (0)
#define SOC_ASP_HIFI3_peripheralId5_peripheralId5_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_HIFI3_peripheralId6_UNION
 结构说明  : peripheralId6 寄存器结构定义。地址偏移量:0x3FD8，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  peripheralId6 : 32; /* bit[0-31]: peripheralId6 */
    } reg;
} SOC_ASP_HIFI3_peripheralId6_UNION;
#endif
#define SOC_ASP_HIFI3_peripheralId6_peripheralId6_START  (0)
#define SOC_ASP_HIFI3_peripheralId6_peripheralId6_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_HIFI3_peripheralId7_UNION
 结构说明  : peripheralId7 寄存器结构定义。地址偏移量:0x3FDC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  peripheralId7 : 32; /* bit[0-31]: peripheralId7 */
    } reg;
} SOC_ASP_HIFI3_peripheralId7_UNION;
#endif
#define SOC_ASP_HIFI3_peripheralId7_peripheralId7_START  (0)
#define SOC_ASP_HIFI3_peripheralId7_peripheralId7_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_HIFI3_peripheralId0_UNION
 结构说明  : peripheralId0 寄存器结构定义。地址偏移量:0x3FE0，初值:0x00000003，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  peripheralId0 : 32; /* bit[0-31]: peripheralId0 */
    } reg;
} SOC_ASP_HIFI3_peripheralId0_UNION;
#endif
#define SOC_ASP_HIFI3_peripheralId0_peripheralId0_START  (0)
#define SOC_ASP_HIFI3_peripheralId0_peripheralId0_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_HIFI3_peripheralId1_UNION
 结构说明  : peripheralId1 寄存器结构定义。地址偏移量:0x3FE4，初值:0x00000021，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  peripheralId1 : 32; /* bit[0-31]: peripheralId1 */
    } reg;
} SOC_ASP_HIFI3_peripheralId1_UNION;
#endif
#define SOC_ASP_HIFI3_peripheralId1_peripheralId1_START  (0)
#define SOC_ASP_HIFI3_peripheralId1_peripheralId1_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_HIFI3_peripheralId2_UNION
 结构说明  : peripheralId2 寄存器结构定义。地址偏移量:0x3FE8，初值:0x0000000F，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  peripheralId2 : 32; /* bit[0-31]: peripheralId2 */
    } reg;
} SOC_ASP_HIFI3_peripheralId2_UNION;
#endif
#define SOC_ASP_HIFI3_peripheralId2_peripheralId2_START  (0)
#define SOC_ASP_HIFI3_peripheralId2_peripheralId2_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_HIFI3_peripheralId3_UNION
 结构说明  : peripheralId3 寄存器结构定义。地址偏移量:0x3FEC，初值:0x00000000，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  peripheralId3 : 32; /* bit[0-31]: peripheralId3 */
    } reg;
} SOC_ASP_HIFI3_peripheralId3_UNION;
#endif
#define SOC_ASP_HIFI3_peripheralId3_peripheralId3_START  (0)
#define SOC_ASP_HIFI3_peripheralId3_peripheralId3_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_HIFI3_componentId0_UNION
 结构说明  : componentId0 寄存器结构定义。地址偏移量:0x3FF0，初值:0x0000000D，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  componentId0 : 32; /* bit[0-31]: componentId0 */
    } reg;
} SOC_ASP_HIFI3_componentId0_UNION;
#endif
#define SOC_ASP_HIFI3_componentId0_componentId0_START  (0)
#define SOC_ASP_HIFI3_componentId0_componentId0_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_HIFI3_componentId1_UNION
 结构说明  : componentId1 寄存器结构定义。地址偏移量:0x3FF4，初值:0x00000090，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  componentId1 : 32; /* bit[0-31]: componentId1 */
    } reg;
} SOC_ASP_HIFI3_componentId1_UNION;
#endif
#define SOC_ASP_HIFI3_componentId1_componentId1_START  (0)
#define SOC_ASP_HIFI3_componentId1_componentId1_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_HIFI3_componentId2_UNION
 结构说明  : componentId2 寄存器结构定义。地址偏移量:0x3FF8，初值:0x00000005，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  componentId2 : 32; /* bit[0-31]: componentId2 */
    } reg;
} SOC_ASP_HIFI3_componentId2_UNION;
#endif
#define SOC_ASP_HIFI3_componentId2_componentId2_START  (0)
#define SOC_ASP_HIFI3_componentId2_componentId2_END    (31)


/*****************************************************************************
 结构名    : SOC_ASP_HIFI3_componentId3_UNION
 结构说明  : componentId3 寄存器结构定义。地址偏移量:0x3FFC，初值:0x000000B1，宽度:32
 寄存器说明: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  componentId3 : 32; /* bit[0-31]: componentId3 */
    } reg;
} SOC_ASP_HIFI3_componentId3_UNION;
#endif
#define SOC_ASP_HIFI3_componentId3_componentId3_START  (0)
#define SOC_ASP_HIFI3_componentId3_componentId3_END    (31)






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

#endif /* end of soc_asp_hifi3_interface.h */
