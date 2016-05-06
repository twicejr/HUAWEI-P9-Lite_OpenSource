/******************************************************************************

  Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : TtfNvInterface.h
  Description     : TtfNvInterface.h header file
  History         :

******************************************************************************/

#ifndef __TTFNVINTERFACE_H__
#define __TTFNVINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "vos.h"

/*****************************************************************************
  2 Macro
*****************************************************************************/

#define TTF_MEM_MAX_POOL_NUM                (5)
#define TTF_MEM_MAX_CLUSTER_NUM             (8)

#define FC_UL_RATE_MAX_LEV                  (11)
#define TTF_MEM_POOL_NV_NUM                 (TTF_MEM_MAX_POOL_NUM + 1)
#define FC_ACPU_DRV_ASSEM_NV_LEV            (4)

#define BASTET_HPRTODCH_SUPPORT             (0x01)
#define BASTET_CHNL_LPM_SUPPORT             (0x02)

#define NV_PLATFORM_MAX_RAT_NUM             (7)               /* 接入技术最大值 */


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/

enum FC_MEM_THRESHOLD_LEV_ENUM
{
    FC_MEM_THRESHOLD_LEV_1              = 0,
    FC_MEM_THRESHOLD_LEV_2,
    FC_MEM_THRESHOLD_LEV_3,
    FC_MEM_THRESHOLD_LEV_4,
    FC_MEM_THRESHOLD_LEV_5,
    FC_MEM_THRESHOLD_LEV_6,
    FC_MEM_THRESHOLD_LEV_7,
    FC_MEM_THRESHOLD_LEV_8,
    FC_MEM_THRESHOLD_LEV_BUTT           = 8
};
typedef VOS_UINT32  FC_MEM_THRESHOLD_LEV_ENUM_UINT32;

enum FC_ACPU_DRV_ASSEM_LEV_ENUM
{
    FC_ACPU_DRV_ASSEM_LEV_1             = 0,
    FC_ACPU_DRV_ASSEM_LEV_2,
    FC_ACPU_DRV_ASSEM_LEV_3,
    FC_ACPU_DRV_ASSEM_LEV_4,
    FC_ACPU_DRV_ASSEM_LEV_5             = 4,
    FC_ACPU_DRV_ASSEM_LEV_BUTT          = 5
};
typedef VOS_UINT32  FC_ACPU_DRV_ASSEM_LEV_ENUM_UINT32;

enum RATIO_RESET_TYPE_ENUM
{
    TTF_NODE_RESET_TYPE                 = 0,
    PS_QNODE_RESET_TYPE                 = 1,
    RATIO_RESET_TYPE_BUTT               = 2
};
typedef VOS_UINT32  RATIO_RESET_TYPE_ENUM_UINT32;


/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
*                                                                            *
*                           参数设置消息结构                                 *
*                                                                            *
******************************************************************************/

/*****************************************************************************
 结构名    : TTF_MEM_POOL_CFG_NV_STRU
 结构说明  : TTF_MEM_POOL_CFG_NV结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                      ucClusterCnt;
    VOS_UINT8                      aucReserved[1];
    VOS_UINT16                     ausBlkSize[TTF_MEM_MAX_CLUSTER_NUM];         /* 本级数的大小 */
    VOS_UINT16                     ausBlkCnt[TTF_MEM_MAX_CLUSTER_NUM];          /* 本级个数 */
}TTF_MEM_POOL_CFG_NV_STRU;

/*****************************************************************************
 结构名    : TTF_MEM_SOLUTION_CFG_NV_STRU
 结构说明  : TTF_MEM_SOLUTION_CFG对应的NV结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPoolCnt;
    VOS_UINT8                           ucPoolMask;                             /* 对应内存池是否生效掩码位，bit来标示，1- 生效， 0- 不生效*/
    TTF_MEM_POOL_CFG_NV_STRU            astTtfMemPoolCfgInfo[TTF_MEM_POOL_NV_NUM];
    VOS_UINT8                           aucReserve[2];
}TTF_MEM_SOLUTION_CFG_NV_STRU;

/*****************************************************************************
 结构名    : FC_CFG_CPU_STRU
 结构说明  : FC_CFG_CPU结构,CPU流控的门限和配置值
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCpuOverLoadVal;                       /*Range:[0,100]*//* CPU流控门限 */
    VOS_UINT32                          ulCpuUnderLoadVal;                      /*Range:[0,100]*//* CPU解除流控门限 */
    VOS_UINT32                          ulSmoothTimerLen;                       /*Range:[2,1000]*//* CPU流控平滑次数，单位:CPU监控周期 */
    VOS_UINT32                          ulStopAttemptTimerLen;                  /* CPU引发R接口流控后，数传中断时间较长，启动定时器，尝试提前解除，单位: 毫秒，0表示不使用 */
    VOS_UINT32                          ulUmUlRateThreshold;                    /* 空口上行速率门限，高于此门限，认为是数传引起的CPU负载高，需要流控 */
    VOS_UINT32                          ulUmDlRateThreshold;                    /* 空口下行速率门限，高于此门限，认为是数传引起的CPU负载高，需要流控 */
    VOS_UINT32                          ulRmRateThreshold;                      /* E5形态下， WIFI/USB入口处速率门限， 高于此门限，认为是数传引起的CPU负载高，需要流控，单位bps */
} FC_CFG_CPU_STRU;

/*****************************************************************************
 结构名    : FC_CFG_MEM_THRESHOLD_STRU
 结构说明  : FC_CFG_MEM_THRESHOLD结构,MEM流控的门限和配置值
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulSetThreshold;                         /* 启动流控门限 单位字节 */
    VOS_UINT32                          ulStopThreshold;                        /* 停止流控门限 单位字节 */
} FC_CFG_MEM_THRESHOLD_STRU;

/*****************************************************************************
 结构名    : FC_CFG_MEM_THRESHOLD_CST_STRU
 结构说明  : FC_CFG_MEM_THRESHOLD_CST结构,MEM流控的门限和配置值
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulSetThreshold;                         /*Range:[0,4096]*//* 启动流控门限 单位字节 */
    VOS_UINT32                          ulStopThreshold;                        /*Range:[0,4096]*//* 停止流控门限 单位字节 */
} FC_CFG_MEM_THRESHOLD_CST_STRU;


/*****************************************************************************
 结构名    : FC_CFG_UM_UL_RATE_STRU
 结构说明  : FC_CFG_UM_UL_RATE结构,空口上行速率档位
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRateCnt;                              /*Range:[0,11]*//* 上行速率档位个数，最多支持11个档位设置，但是优先级最高为FC_PRI_9，所以使用档位时只有前9档生效 */
    VOS_UINT8                           aucRsv[1];
    VOS_UINT16                          ausRate[FC_UL_RATE_MAX_LEV];            /* 上行速率限制，取值范围[0,65535]，单位bps */
} FC_CFG_UM_UL_RATE_STRU;

/*****************************************************************************
 结构名    : FC_CFG_NV_STRU
 结构说明  : FC_CFG_NV对应的NV结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulFcEnbaleMask;                         /* 流控使能标识 */
    FC_CFG_CPU_STRU                     stFcCfgCpuA;                            /* A核CPU流控门限 */
    VOS_UINT32                          ulFcCfgMemThresholdCnt;                 /*Range:[0,8]*/
    FC_CFG_MEM_THRESHOLD_STRU           stFcCfgMem[FC_MEM_THRESHOLD_LEV_BUTT];  /* A核内存流控门限 */
    FC_CFG_MEM_THRESHOLD_CST_STRU       stFcCfgCst;                             /* CSD业务流控门限 */
    FC_CFG_MEM_THRESHOLD_STRU           stFcCfgGprsMemSize;                     /* G模内存总量流控门限 */
    FC_CFG_MEM_THRESHOLD_STRU           stFcCfgGprsMemCnt;                      /* G模内存块数流控门限 */
    FC_CFG_CPU_STRU                     stFcCfgCpuC;                            /* C核CPU流控门限 */
    FC_CFG_UM_UL_RATE_STRU              stFcCfgUmUlRateForCpu;                  /* C核CPU流控上行速率档位配置 */
    FC_CFG_UM_UL_RATE_STRU              stFcCfgUmUlRateForTmp;                  /* C核温度流控上行行速率档位配置 */
    FC_CFG_MEM_THRESHOLD_STRU           stFcCfgCdmaMemSize;                     /* X模内存总量流控门限 */
    FC_CFG_MEM_THRESHOLD_STRU           stFcCfgCdmaMemCnt;                      /* X模内存块数流控门限 */
} FC_CFG_NV_STRU;

/*****************************************************************************
 结构名    : CPULOAD_CFG_STRU
 结构说明  : CPULOAD_CFG对应的NV结构,CPU流控的门限和配置值
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMonitorTimerLen;
} CPULOAD_CFG_STRU;

typedef struct
{
    VOS_UINT8                          ucHostOutTimeout;    /* PC驱动组包时延 */
    VOS_UINT8                          ucEthTxMinNum;       /* UE驱动下行组包个数 */
    VOS_UINT8                          ucEthTxTimeout;      /* UE驱动下行组包时延 */
    VOS_UINT8                          ucEthRxMinNum;       /* UE驱动上行组包个数 */
    VOS_UINT8                          ucEthRxTimeout;      /* UE驱动上行组包时延 */
    VOS_UINT8                          ucCdsGuDlThres;
    VOS_UINT8                          aucRsv[2];
}FC_DRV_ASSEM_PARA_STRU;

typedef struct
{
    VOS_UINT32                          ulCpuLoad;
    FC_DRV_ASSEM_PARA_STRU              stDrvAssemPara;
}FC_CPU_DRV_ASSEM_PARA_STRU;

/*****************************************************************************
 结构名    : FC_CPU_DRV_ASSEM_PARA_NV_STRU
 结构说明  : FC_CPU_DRV_ASSEM对应的NV结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                              ucEnableMask;
    VOS_UINT8                              ucSmoothCntUpLev;
    VOS_UINT8                              ucSmoothCntDownLev;
    VOS_UINT8                              ucRsv;
    FC_CPU_DRV_ASSEM_PARA_STRU             stCpuDrvAssemPara[FC_ACPU_DRV_ASSEM_NV_LEV];
}FC_CPU_DRV_ASSEM_PARA_NV_STRU;

/*****************************************************************************
 结构名    : WTTF_MACDL_WATERMARK_LEVEL_STRU
 结构说明  : WTTF_MACDL_BBMST_WATER_LEVEL对应的NV结构,BBP译码中断水线等级结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulWaterLevelOne;                        /* 水线界别1 */
    VOS_UINT32                          ulWaterLevelTwo;                        /* 水线界别2 */
    VOS_UINT32                          ulWaterLevelThree;                      /* 水线界别3 */
    VOS_UINT32                          ulWaterLevelFour;                       /* 水线界别4,预留 */
} WTTF_MACDL_WATERMARK_LEVEL_STRU;

/*****************************************************************************
 结构名    : WTTF_MACDL_BBPMST_TB_HEAD_STRU
 结构说明  : WTTF_MACDL_BBMST_TB_HEAD对应的NV结构,BBP译码中断水线等级结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulTBHeadNum;                /* TB头部块个数 */
    VOS_UINT32                          ulTBHeadReserved;           /* TB头部块预留的TB块数，预留3帧，V9R1 30块，V3R3 15块  */
} WTTF_MACDL_BBPMST_TB_HEAD_STRU;

/*****************************************************************************
 结构名    : WTTF_SRB_NOT_SEND_THRESHOLD_STRU
 结构说明  : WTTF_SRB_NOT_SEND_THRESHOLD_STRU对应的NV结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulWttfSrbNotSendThreshold;                /* SRB不发送测量报告的门限 */
} WTTF_SRB_NOT_SEND_THRESHOLD_STRU;


/*****************************************************************************
 结构名    : NF_EXT_NV_STRU
 结构说明  : NETFILTER_HOOK_MASK对应的NV结构,设置勾包点的NV项，预留5种掩码组合:
             ulNvValue1~ulNvValue5, 每个掩码取值范围为0-FFFFFFFF,
             其中掩码位为1则代表该掩码位对应的钩子函数可能会被注册到内核中
*****************************************************************************/
typedef struct
{
    VOS_UINT32          ulNetfilterPara1;
    VOS_UINT32          ulNetfilterPara2;
    VOS_UINT32          ulNetfilterPara3;
    VOS_UINT32          ulNetfilterPara4;
    VOS_UINT32          ulNetfilterPara5;
}NF_EXT_NV_STRU;

/*****************************************************************************
 结构名    : EXT_TEBS_FLAG_NV_STRU
 结构说明  : NV_Ext_Tebs_Flag对应的NV结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32          ulExtTebsFlag;
}EXT_TEBS_FLAG_NV_STRU;

/*****************************************************************************
 结构名    : TCP_ACK_DELETE_FLG_NV_STRU
 结构说明  : NV_TCP_ACK_Delete_Flg对应的NV结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32          ulTcpAckDeleteFlg;
}TCP_ACK_DELETE_FLG_NV_STRU;

/*****************************************************************************
 结构名    : HUAWEI_IRAN_OPEN_PAGE_I_NV_STRU
 结构说明  : HUAWEI_IRAN_OPEN_PAGE_I_NV结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16          usHuaweiIranOpenPageI;      /*Range:[0,1]*/
    VOS_UINT8           aucReserve[2];
}HUAWEI_IRAN_OPEN_PAGE_I_NV_STRU;

/*****************************************************************************
 结构名    : GCF_TYPE_CONTENT_NV_STRU
 结构说明  : GCFTypeContent对应的NV结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32          ulGcfTypeContent;
}GCF_TYPE_CONTENT_NV_STRU;

/*****************************************************************************
 结构名    : W_RF8960_BER_TEST_NV_STRU
 结构说明  : W_RF8960_BER_Test对应的NV结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32          ulRlc8960RFBerTestFlag;
}W_RF8960_BER_TEST_NV_STRU;

/*****************************************************************************
 结构名    : LAPDM_RAND_BIT_NV_STRU
 结构说明  : LAPDM_RAND_BIT对应的NV结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16          usLapdmRandBit;         /*Range:[0,1]*/
    VOS_UINT8           aucReserve[2];
}LAPDM_RAND_BIT_NV_STRU;

/*****************************************************************************
 结构名    : CBS_W_DRX_SWITCH_NV_STRU
 结构说明  : CBS_W_DRX_Switch对应的NV结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32          ulCbsWDrxSwitch;
}CBS_W_DRX_SWITCH_NV_STRU;

/*****************************************************************************
 结构名    : CBS_W_WAIT_NEW_CBS_MSG_TIMER_NV_STRU
 结构说明  : CBS_W_WaitNewCBSMsgTimer对应的NV结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32          ulCbsWWaitNewCbsMsgTimer;
}CBS_W_WAIT_NEW_CBS_MSG_TIMER_NV_STRU;

/*****************************************************************************
 结构名    : CBS_W_WAIT_SHED_MSG_TIMER_NV_STRU
 结构说明  : CBS_W_WaitShedMsgTimer对应的NV结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32          ulCbsWWaitShedMsgTimer;
}CBS_W_WAIT_SHED_MSG_TIMER_NV_STRU;

/*****************************************************************************
 结构名    : FC_QOS_STRU
 结构说明  : FC_QOS_STRU 打桩使用结构,目前代码中已经不使用，为了保持NV结构不变化
*****************************************************************************/

typedef struct
{
    VOS_UINT32          ulULKBitRate;
    VOS_UINT32          ulDLKBitRate;
}FC_QOS_STRU;

/*****************************************************************************
 结构名    : CPU_FLOW_CTRL_CONFIG_NV_STRU
 结构说明  : CPU_FLOW_CTRL_CONFIG_STRU对应的NV结构，已废弃，打桩提供
*****************************************************************************/
typedef struct
{
    VOS_UINT32          ulFuncMask;
    VOS_UINT32          ulCpuOverLoadVal;
    VOS_UINT32          ulCpuUnderLoadVal;
    FC_QOS_STRU         astQos1[2];
    FC_QOS_STRU         astQos2[2];
    FC_QOS_STRU         stUmtsEhsUlLimitForDlHighRate;
    FC_QOS_STRU         stUmtsHslULimitForDlHighRate;
    FC_QOS_STRU         stUlLimitForDlLowRate;
    VOS_UINT32          ulRItfDlkBitRate;
    VOS_UINT32          ulRItfRate;
    VOS_UINT32          ulWaitQosTimeLen;
    VOS_UINT32          ulSmoothTimerLen;
    VOS_UINT32          ulRItfSetTimerLen;
    VOS_UINT32          ulCpuFlowCtrlEnable;
    VOS_UINT32          aulRsv[2];
}CPU_FLOW_CTRL_CONFIG_NV_STRU;

/*****************************************************************************
 结构名    : R_ITF_FLOW_CTRL_CONFIG_STRU
 结构说明  : R_ITF_FLOW_CTRL_CONFIG_STRU对应的NV结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32              ulRateDismatchUsbEnable;
    VOS_UINT32              ulRateDismatchWifiEnable;
} R_ITF_FLOW_CTRL_CONFIG_STRU;

/*****************************************************************************
 结构名    : TFC_POWER_FUN_ENABLE_NV_STRU
 结构说明  : TFC_POWER_FUN_ENABLE对应的NV结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32          ulTfcPowerFunEnable;
}TFC_POWER_FUN_ENABLE_NV_STRU;

/*****************************************************************************
结构名    : PPP_CONFIG_MRU_TYPE_NV_STRU
结构说明  : PPP_CONFIG_MRU_Type对应的NV结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                           usPppConfigType;   /*Range:[296,1500]*/
    VOS_UINT8                            aucReserve[2];
}PPP_CONFIG_MRU_TYPE_NV_STRU;

/*****************************************************************************
 结构名    : FC_CDS_DL_CONFIG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 定义CDS下行丢包流控配置结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32          ulDiscardThres;         /* CDS下行队列丢包门限 */
    VOS_UINT32          ulDiscardRate;          /* 丢包率 */
} FC_CDS_DL_CONFIG_STRU;

/*****************************************************************************
 结构名    : QOS_FC_CONFIG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 定义QOS流控配置结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32          ulPktCntLimit;              /* 触发QoS流控包数 */
    VOS_UINT32          ulTimerLen;                 /* 触发QoS流控时长 */
    VOS_UINT32          ulRandomDiscardRate;        /* 随机丢包率 */
    VOS_UINT32          ulDiscardRate;              /* 丢包率 */
    VOS_UINT32          ulWarningThres;             /* 警告阈值，除必须保留的承载外全部置为丢包状态 */
    VOS_UINT32          ulDiscardThres;             /* 丢包阈值，从低优先级承载开始置承载为丢包状态 */
    VOS_UINT32          ulRandomDiscardThres;       /* 随机丢包阈值，从低优先级承载开始置承载为随机丢包状态 */
    VOS_UINT32          ulRestoreThres;             /* 恢复阈值，从高优先级承载开始逐渐恢复承载数传 */
} QOS_FC_CONFIG_STRU;

typedef struct
{
    VOS_UINT32              ulFcEnableMask;         /* 流控开关 */
                                                    /* bit0 QoS流控是否使能 */
                                                    /* bit1 最高优先级承载是否流控 */
                                                    /* bit2 CDS下行流控是否使能 */
                                                    /* bit3 最高优先级承载是否不丢包 */
    QOS_FC_CONFIG_STRU      stQosFcConfig;
    FC_CDS_DL_CONFIG_STRU   stFcCdsDlConfig;
}FLOWCTRL_CDS_CONFIG_STRU;

/*****************************************************************************
结构名    : BMC_CBS_MSG_READ_NV_STRU
结构说明  : BMC_CBS_MSG_READ_NV_STRU对应的NV结构
*****************************************************************************/

typedef struct
{
    VOS_UINT8               ucDisableReadAdvised;    /*Range:[0,1]*//*当调度消息中消息描述类型为advised时，对应DRX周期内消息是否接受； PS_FALSE为不接受，PS_TRUE为接受*/
    VOS_UINT8               ucDisableReadOptional;   /*Range:[0,1]*//*当调度消息中消息描述类型为optional时，对应DRX周期内消息是否接受；PS_FALSE为不接受，PS_TRUE为接受*/
    VOS_UINT8               ucReserved[2];
}BMC_CBS_MSG_READ_NV_STRU;


/*****************************************************************************
结构名    : NV_MODEM_RF_SHARE_CFG_STRU
结构说明  : NV_MODEM_RF_SHARE_CFG对应的NV结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usSupportFlag;      /*Range:[0,1]*//* 功能是否支持标记 */
    VOS_UINT16                          usGSMRFID;          /* GSM接入模式RFID信息 */
    VOS_UINT16                          usWCDMARFID;        /* WCDMA接入模式RFID信息 */
    VOS_UINT16                          usTDSRFID;          /* TD-SCDMA接入模式RFID信息 */
    VOS_UINT16                          usLTERFID;          /* LTE接入模式RFID信息 */
    VOS_UINT16                          usCDMARFID;         /* CMDA接入模式RFID信息 */
    VOS_UINT16                          usEVDORFID;         /* CDMA EVDO接入模式RFID信息 */
    VOS_UINT16                          usReserved;
} NV_MODEM_RF_SHARE_CFG_STRU;


/*****************************************************************************
结构名    : NV_MODEM_RF_SHARE_CFG_EX_STRU
结构说明  : NV_MODEM_RF_SHARE_CFG_EX_STRU对应的NV结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulProfileTypeId;     /* 读取en_NV_Item_TRI_MODE_FEM_PROFILE_ID获取ulProfileId,
                                                               对应于取下面组数中哪一套配置 */
    NV_MODEM_RF_SHARE_CFG_STRU          astNvModemRfShareCfg[8];
}NV_MODEM_RF_SHARE_CFG_EX_STRU;

/*****************************************************************************
结构名    : PLATFORM_RAT_TYPE_ENUM
结构说明  : 接入技术

  1.日    期   : 2015年4月27日
    作    者   : g00260269
    修改内容   : 创建
*******************************************************************************/
enum NV_PLATFORM_RAT_TYPE_ENUM
{
    NV_PLATFORM_RAT_GSM,                                                       /*GSM接入技术 */
    NV_PLATFORM_RAT_WCDMA,                                                     /* WCDMA接入技术 */
    NV_PLATFORM_RAT_LTE,                                                       /* LTE接入技术 */
    NV_PLATFORM_RAT_TDS,                                                       /* TDS接入技术 */
    NV_PLATFORM_RAT_1X,                                                        /* CDMA-1X接入技术 */
    NV_PLATFORM_RAT_EVDO,                                                      /* CDMA-EV_DO接入技术 */

    NV_PLATFORM_RAT_BUTT
};
typedef VOS_UINT16 NV_PLATFORM_RAT_TYPE_ENUM_UINT16;

/*****************************************************************************
结构名    : NV_PLATAFORM_RAT_CAPABILITY_STRU
结构说明  : 平台支持的接入技术

  1.日    期   : 2015年4月27日
    作    者   : g00260269
    修改内容   : 创建
*******************************************************************************/
typedef struct
{
    VOS_UINT16                           usRatNum;                          /* 接入技术的数目*/
    NV_PLATFORM_RAT_TYPE_ENUM_UINT16     aenRatList[NV_PLATFORM_MAX_RAT_NUM];  /* 接入技术 */
}NV_PLATAFORM_RAT_CAPABILITY_STRU;

/*****************************************************************************
结构名    : BASTET_SUPPORT_FLG_STRU
结构说明  : BASTET_SUPPORT_FLG_STRU结构
  1.日    期   : 2014年11月22日
    作    者   : z00128442
    修改内容   : 新增bastet配置nv
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActiveFlg;        /* 是否激活功能 */
    VOS_UINT8                           ucHookFlg;          /* Bastet钩包模式 */
    VOS_UINT8                           aucSubFun[2];
}BASTET_SUPPORT_FLG_STRU;

/*****************************************************************************
结构名    : NV_CTTF_BOOL_ENUM_UINT8
结构说明  :

  1.日    期   : 2015年9月9日
    作    者   : c00309867
    修改内容   : 创建
*******************************************************************************/
enum NV_CTTF_BOOL_ENUM
{
    NV_CTTF_BOOL_FALSE,                /* 条件为真 */
    NV_CTTF_BOOL_TRUE,               /* 条件为假 */
    NV_CTTF_BOOL_BUTT
};
typedef VOS_UINT8 NV_CTTF_BOOL_ENUM_UINT8;

/*****************************************************************************
结构名    : NV_SUPPORT_PROBE_INIT_ADJ_CFG_STRU
结构说明  : NV_SUPPORT_PROBE_INIT_ADJ_CFG_STRU结构
  1.日    期   : 2015年9月0日
    作    者   : c00309867
    修改内容   : 新增nv
*****************************************************************************/
typedef struct
{
    NV_CTTF_BOOL_ENUM_UINT8             enSupportFlg;                   /* 是否支持通过NV项配置cProbeInitialAdjust。NV_CTTF_BOOL_TRUE:不支持；NV_CTTF_BOOL_TRUE支持*/
    VOS_INT8                            cProbeInitialAdjust;            /* cProbeInitialAdjust的值 */
    VOS_UINT8                           aucSubFun[2];
}NV_CTTF_PROBE_INIT_POWER_CTRL_STRU;


/*****************************************************************************
结构名    : TTF_PPPC_NVIM_CONFIG_OPTIONS_STRU
结构说明  : TTF_PPPC_NVIM_CONFIG_OPTIONS_STRU结构
  1.日    期   : 2015年08月29日
    作    者   : w00316385
    修改内容   : 新增配置nv
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usMru;                  /* PPP帧最大接收单元长度 */
    VOS_UINT8                           ucReserved;
    VOS_UINT8                           ucCaveEnable;           /* PPP接入鉴权CAVE算法开关，0不支持，1支持 */
    VOS_UINT32                          ulPppInactTimerLen;     /* MAX PPP Inactive Timer时长，单位s */
}TTF_PPPC_NVIM_CONFIG_OPTIONS_STRU;

/*****************************************************************************
结构名    : NV_TTF_NODE_RESET_CTRL_STRU
结构说明  : NV_TTF_NODE_RESET_CTRL_STRU结构
  1.日    期   : 2016年01月26日
    作    者   : m00314743
    修改内容   : 新增nv
*****************************************************************************/
typedef struct
{
    NV_CTTF_BOOL_ENUM_UINT8             enResetEnable;                  /* TTF_Node主动复位时能 */
    VOS_UINT8                           ucFailPercent;             /* 申请失败比例门限，达到时主动复位 */
    VOS_UINT16                          usTotalStat;               /* 节点申请统计总次数 */
}NV_RATIO_RESET_CTRL_STRU;

/*****************************************************************************
结构名    : NV_NODE_RESET_CTRL_STRU
结构说明  : NV_NODE_RESET_CTRL_STRU结构
  1.日    期   : 2016年01月26日
    作    者   : m00314743
    修改内容   : 新增nv
*****************************************************************************/
typedef struct
{
    NV_RATIO_RESET_CTRL_STRU                  astNvResetCtrl[RATIO_RESET_TYPE_BUTT];
}NV_NODE_RESET_CTRL_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/


/*****************************************************************************
  9 OTHERS
*****************************************************************************/
















#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of TtfNvInterface.h */
