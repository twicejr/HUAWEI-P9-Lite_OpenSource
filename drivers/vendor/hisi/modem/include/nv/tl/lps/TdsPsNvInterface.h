/*************************************************************************
* FILE NAME   TdsPsNvInterface.h                  VERSION   1.0.0
*
* COMPONENT                                       PUB
*
* DESCRIPTION
*
* This file define the data structure that used by NVM parameters.
* 海思NV存储的结构体文件
*
* DATA STRUCTURES
*
* [global component data structures defined in this file]
*
* FUNCTIONS
*
* NONE
*
* HISTORY
*
* NAME            DATE             VERSION      REMARKS
* yangyong      2011.09.21       v1.0.0       creation
*
*************************************************************************/
#ifndef TDSPSINTERFACE_H
#define TDSPSINTERFACE_H


/*****************************************************************************
 枚举名    : TRRC_RRC_FUNC_SUPPORT_ENUM
 枚举说明  :
*****************************************************************************/
enum TRRC_RRC_FUNC_SUPPORT_ENUM
{
    TRRC_RRC_FUNC_SUPPORT_NOT = 0,  /*   0 代表不支持?*/
    TRRC_RRC_FUNC_SUPPORT     = 1,  /*   1 代表支持*/
    TRRC_RRC_FUNC_BUTT
};
typedef VOS_UINT8 TRRC_RRC_FUNC_SUPPORT_ENUM_UINT8;

#define TRRC_RRC_MAX_FREQ_BANDS_EUTRA_NV                       16
/*****************************************************************************
 枚举名    : TRRC_MULTI_MODE_RAT_CAPABILITY_ENUM_UINT8
 结构说明  : 是否支持RATCAPABILITY
*****************************************************************************/
/*enum TRRC_RAT_CAPABILITY_SUPPORT_ENUM*/
/*{*/
/*   TRRC_RAT_CAPABILITY_SUPPORT_NOT       = 0,*/
/*    TRRC_RAT_CAPABILITY_SUPPORT           = 1,*/
/*    TRRC_RAT_CAPABILITY_BUTT*/
/*};*/
typedef VOS_UINT8  TRRC_MULTI_MODE_RAT_CAPABILITY_ENUM_NV_UINT8;
/*****************************************************************************
 枚举名    : TRRC_NEED_FOR_IDLE_INTER_ENUM
 结构说明  :
      25.331:TRUE means that the UE requires idle interval in order to perform
             measurements on E-UTRA frequency band indicated by the IE "E-UTRA
             Frequency band"
*****************************************************************************/
/*enum TRRC_NEED_FOR_IDLE_INTER_ENUM*/
/*{*/
/*    TRRC_TRRC_NEED_FOR_IDLE_INTER_ENUM_SUPPORT_NOT       = 0,*/
/*    TRRC_TRRC_NEED_FOR_IDLE_INTER_ENUM_SUPPORT           = 1,*/
/*    TRRC_TRRC_NEED_FOR_IDLE_INTER_ENUM_BUTT*/
/*};*/
typedef VOS_UINT8  TRRC_NEED_FOR_IDLE_INTER_ENUM_NV_UINT8;


typedef struct T_PdcpCapability_Tag
{
  VOS_UINT8   losslessSrnsRelocationSupport;
  VOS_UINT8   supportForRfc2507;

  VOS_UINT8   maxHcContextSpace;
  VOS_UINT8   supportForRfc3095;
  VOS_UINT8   maxRohcContextSessions;
  VOS_UINT8   reserved;
  VOS_UINT16   reverseCompressionDepth;
  VOS_UINT8   sptForRfc3095ContextRelocation;
  VOS_UINT8   sptLosslessDlRlcPduSizeChange;
  VOS_UINT16  reserved1;
}T_PdcpCapability;

typedef struct T_RlcCapability_Tag
{
  VOS_UINT8   totalRlcAmBufferSize;
  VOS_UINT8   maximumRlcWindowSize;
  VOS_UINT8   maximumAmEntityNumber;

  VOS_UINT8   supportofTwoLogicalChannel;
}T_RlcCapability;

typedef struct T_DlTransChCapability_Tag
{
  VOS_UINT8   maxNoBitsReceived;
  VOS_UINT8   maxConvCodeBitsReceived;
  VOS_UINT8   turboDecodingSupport;
  VOS_UINT8   maxSimultaneousTransChs;
  VOS_UINT8   maxSimultaneousCctrchCount;
  VOS_UINT8   maxReceivedTransportBlocks;
  VOS_UINT8   maxNumberOfTfc;
  VOS_UINT8   maxNumberOfTf;
}T_DlTransChCapability;

typedef struct T_UlTransChCapability_Tag
{
  VOS_UINT8   maxNoBitsTransmitted;
  VOS_UINT8   maxConvCodeBitsTransmitted;
  VOS_UINT8   turboEncodingSupport;
  VOS_UINT8   maxSimultaneousTransChs;
  VOS_UINT8   maxSimultaneousCctrchCount;
  VOS_UINT8   maxTransmittedBlocks;
  VOS_UINT8   maxNumberOfTfc;
  VOS_UINT8   maxNumberOfTf;
}T_UlTransChCapability;

typedef struct T_TransportChannelCapability_Tag
{
  T_DlTransChCapability  dlTransChCapability;

  T_UlTransChCapability  ulTransChCapability;

}T_TransportChannelCapability;

typedef struct T_RfCapability_Tag
{
  VOS_UINT8   uePowerClass;

  VOS_UINT8   radioFrequencyBandTddList;
  VOS_UINT8   chipRateCapability;
  VOS_UINT8   reserved;
}T_RfCapability;

typedef struct T_UlPhysChCapability_Tag
{
  VOS_UINT8   maxTsPerSubFrame;

  VOS_UINT8   maxPhysChPerTimeslot;
  VOS_UINT8   minimumSf;
  VOS_UINT8   supportOfPusch;
  VOS_UINT8   supportOf8Psk;

  VOS_UINT8   supportTdd128edch;
  VOS_UINT8   tddEdchPhysicalLayerCategory;
  VOS_UINT8   reserved;
}T_UlPhysChCapability;

typedef struct T_DlPhysChCapability_Tag
{
  VOS_UINT8   maxTsPerSubFrame;
  VOS_UINT8   maxPhysChPerFrame;
  VOS_UINT8   minimumSf;
  VOS_UINT8   supportOfPdsch;
  VOS_UINT8   maxPhysChPerTs;
  VOS_UINT8   supportOf8Psk;

  VOS_UINT8    supportTdd128hsdsch;
  VOS_UINT8    hsdschPhysicalLayerCategory;

  VOS_UINT8   supportMultiCarrierTdd128Hsdsch;
  VOS_UINT8   multiCarrierPhysicalLayerCategory;
  VOS_UINT16  reserved;
}T_DlPhysChCapability;

typedef struct T_PhysicalChannelCapability_Tag
{
  T_DlPhysChCapability   dlPhysChCapability;
  T_UlPhysChCapability   ulPhysChCapability;
}T_PhysicalChannelCapability;


typedef struct T_MultiModeRatCapability_Tag
{
  VOS_UINT8   supportOfGsm;
  VOS_UINT8   supportOfMulticarrier;
  VOS_UINT8   multiModeCapability;

  VOS_UINT8   supportGERANIuRadioAccess;

  VOS_UINT8   supportofUtranToGeranNacc;
  VOS_UINT8   supportOfHandoverToGAN;

  VOS_UINT8   supportofPsHandover;

  VOS_UINT8   supportofPsHandoverToGan;
}T_MultiModeRatCapability;


typedef struct T_SecurityCapability_Tag
{

  VOS_UINT16   cipheringAlgorithmCap;

  VOS_UINT16   integrityProtectionAlgorithmCap;
}T_SecurityCapability;

typedef struct T_PositioningCapability_Tag
{
  VOS_UINT8   standaloneLocMethodsSupported;
  VOS_UINT8   basedOtdoaSupported;
  VOS_UINT8   networkAssistedGpsSupported;
  VOS_UINT8   supportForUeGpsTimingOfCellFrames;
  VOS_UINT8   supportForIpdl;
  VOS_UINT8   rxTxTimeDifferenceType2Capable;
  VOS_UINT8   validityCellPchUraPch;
  VOS_UINT8   sfnSfnType2Capability;

  VOS_UINT8   supportnetworkAssistedGANSS;
  VOS_UINT8   reserved[3];
}T_PositioningCapability;


typedef struct T_CompressModeMeasCapability_Tag
{
  VOS_UINT8   tdd128Measurements;
  VOS_UINT8   reserved[3];
}T_CompressModeMeasCapability;

typedef struct T_MeasurementCapability_Tag
{
   T_CompressModeMeasCapability   downlinkCompressMode ;
   T_CompressModeMeasCapability   uplinkCompressMode;
 }T_MeasurementCapability;

typedef struct
{
  VOS_UINT8   supportEutraFdd;
  VOS_UINT8   supportEutraTdd;
  VOS_UINT8   reserved[2];
}T_PreRedirectionInfo;

/*****************************************************************************
 STRUCT    : TRRC_IDLE_INTER_MEAS_CAP_EUTRA_NV_STRU
 结构说明  : UE
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  ulRadioFrequencyBandEUTRA;
    TRRC_NEED_FOR_IDLE_INTER_ENUM_NV_UINT8      enIdleInterval;
    VOS_UINT8                                   ucReceived;
}TRRC_IDLE_INTER_MEAS_CAP_EUTRA_NV_STRU;

/*****************************************************************************
 STRUCT    : TRRC_MULTI_MODE_RAT_CAPABILITY_STRU
 结构说明  :
*****************************************************************************/
typedef struct
{
    TRRC_MULTI_MODE_RAT_CAPABILITY_ENUM_NV_UINT8    enSupportEUTRAFDD;
    TRRC_MULTI_MODE_RAT_CAPABILITY_ENUM_NV_UINT8    enSupportInterRATHOToEUTRAFDD;
    TRRC_MULTI_MODE_RAT_CAPABILITY_ENUM_NV_UINT8    enSupportEUTRATDD;
    TRRC_MULTI_MODE_RAT_CAPABILITY_ENUM_NV_UINT8    enSupportInterRATHOToEUTRATDD;

    VOS_UINT8                                       ucEutraFeatureGroupInd;
    VOS_UINT8                                       aucReceived[3];
}TRRC_MULTI_MODE_RAT_CAPABILITY_NV_STRU;

/*****************************************************************************
 STRUCT    : TRRC_EUTRA_RADIO_ACCESS_CAPABILITY_STRU
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                      ulIdleInterMeasCapNum;
    TRRC_IDLE_INTER_MEAS_CAP_EUTRA_NV_STRU          astIdleIntervalMeasCapEUTRA[TRRC_RRC_MAX_FREQ_BANDS_EUTRA_NV];
    TRRC_MULTI_MODE_RAT_CAPABILITY_NV_STRU          stMultiModeRatCap;
}TRRC_EUTRA_RADIO_ACCESS_CAPABILITY_NV_STRU;
typedef struct T_RadioAccessCapability_Tag
{
  VOS_UINT8               accessStratumReleaseIndicator;
  VOS_UINT8               reserved[3];
  T_PdcpCapability               pdcpCapability;
  T_RlcCapability                rlcCapability;
  T_TransportChannelCapability   trchCapability;
  T_RfCapability                 rfCapability;
  T_PhysicalChannelCapability    physicalChannelCapability;
  T_MultiModeRatCapability       multiModeRatCapability;
  T_SecurityCapability           securityCapability;
  T_PositioningCapability        positioningCapability;

  VOS_UINT8                            supportmeasurementCapability;
  VOS_UINT8                            reserved1[3];
  T_MeasurementCapability       measurementCapability;

  VOS_UINT8    supportDlCapabilityWithSimultaneousHsdschConfig;
  VOS_UINT8    dlCapabilityWithSimultaneousHsdschConfig;

  VOS_UINT8    deviceType;

  VOS_UINT8  supportForSIB11bis;

  VOS_UINT8  supportForFDPCH;

  VOS_UINT8    macEhsSupport;
  VOS_UINT8    supportUeSpecificCapabilityInformationLcrTdd;
  VOS_UINT8    ueSpecificCapabilityInformationLcrTdd;

  VOS_UINT8    supportForEDPCCHPowerBoosting;
  VOS_UINT8    reserved2[3];


  T_PreRedirectionInfo  stPreRediInfo;


  TRRC_RRC_FUNC_SUPPORT_ENUM_UINT8   sysInfoContStoredInd;
  VOS_UINT8    reserved3[3];


  TRRC_EUTRA_RADIO_ACCESS_CAPABILITY_NV_STRU        stEutraRatAccCap;


}T_RadioAccessCapability;

typedef struct  T_GsmCapability_Tag
{
  VOS_UINT8   rGsmSupportedFlag;
  VOS_UINT8   gsm750SupportedFlag;
  VOS_UINT8   gsm850SupportedFlag;
  VOS_UINT8   gsm1900SupportedFlag;
  VOS_UINT8   multibandSupported;
  VOS_UINT8   aucRev[3];
}T_GsmCapability;


typedef struct T_UeCapabilityRequensted_Tag
{
  VOS_UINT8                               interRatNum;
  VOS_UINT8                               uESpecificBehaviourInformation1idle;
  VOS_UINT8                               reserved[2];
  T_GsmCapability          gsmCapability;
  T_RadioAccessCapability          radioAccessCapability;
}T_UeCapabilityRequensted;

typedef struct T_AlfaFilter_Tag
{
    VOS_UINT32                                      ulAlfa;
    VOS_UINT32                                      ulHIrat;
    VOS_UINT32                                      ulHIntra;
    VOS_UINT32                                      ulHInter;

}T_AlfaFilter;

/*************************************************************************/
/*               Dynamic DRV NVM parameters                              */
/*                                                                       */
/*************************************************************************/
typedef struct T_NVM_DSP_CQI_Tag
{
	 VOS_UINT16 cqiReportControl;
	 VOS_UINT16 cqiModulate;
	 VOS_UINT16 cqiTbsizeId;
	 VOS_UINT16 reserved[5];
}T_NVM_DSP_CQI;

typedef struct T_NVM_DSP_UPPOWER_Tag
{
	 VOS_UINT16 upDpchPower;
	 VOS_UINT16 upSichPower;
	 VOS_UINT16 upEpuchPower;
	 VOS_UINT16 upRachPower;
	 VOS_UINT16 upSyncULPower;
	 VOS_UINT16 reserved[5];
}T_NVM_DSP_UPPOWER;

typedef struct T_NVM_DSP_PRESEND_Tag
{
	 VOS_UINT16 dpchPreSendTime;
	 VOS_UINT16 sichPreSendTime;
	 VOS_UINT16 epuchPreSendTime;
	 VOS_UINT16 rachPreSendTime;
	 VOS_UINT16 syncULPreSendTime;
	 VOS_UINT16 reserved[5];
}T_NVM_DSP_PRESEND;

typedef struct T_NVM_DSP_SIR_Tag
{
	 VOS_UINT16 dpchSirDownLimit;
	 VOS_UINT16 dschSirDownLimit;
	 VOS_UINT16 scchSirDownLimit;
	 VOS_UINT16 agchSirDownLimit;
	 VOS_UINT16 reserved[6];
}T_NVM_DSP_SIR;

typedef struct T_NVM_DSP_EXTDATASPACE_Tag
{
	 VOS_UINT32 extDataSpaceAddr;
	 VOS_UINT32 extDataSpaceSize;
	 VOS_UINT16 dpchDataStoreControl;
	 VOS_UINT16 dpchDataH16Addr;
	 VOS_UINT16 dpchDataSize;
	 VOS_UINT16 dschDataStoreControl;
	 VOS_UINT16 dschDataH16Addr;
	 VOS_UINT16 dschDataSize;
	 VOS_UINT16 fpachDataStoreControl;
	 VOS_UINT16 fpachDataH16Addr;
	 VOS_UINT16 fpachDataSize;
	 VOS_UINT16 scchDataStoreControl;
	 VOS_UINT16 scchDataH16Addr;
	 VOS_UINT16 scchDataSize;
	 VOS_UINT16 reserved[6];
}T_NVM_DSP_EXTDATASPACE;


typedef struct T_NVM_DspPara_Tag
{
  VOS_UINT16                    nvmCheckSum;
  VOS_UINT16                    MaxAPCLimitFlag;
  T_NVM_DSP_CQI          nvmCqi;
  T_NVM_DSP_UPPOWER      nvmUpPower;
  T_NVM_DSP_PRESEND      nvmPresend;
  T_NVM_DSP_SIR          nvmSir;
  T_NVM_DSP_EXTDATASPACE nvmExtDataSpace;
}T_NVM_DspPara;


typedef struct T_FreBandFAndR7Tag
{
   VOS_UINT8        fFreIndicator;
   VOS_UINT8        radioFrequencyBandTddListR7;
   VOS_UINT8        eFreIndicator;
   VOS_UINT8        reserved;
}T_FreBandFAndR7;

typedef struct T_LocFrequencyinfoTag
{
  VOS_UINT16        freqNum;
  VOS_UINT16        freq[9];
  VOS_UINT16        lockCell;
  VOS_UINT16        reserved;
}T_LocFrequencyinfo;

/* MTC AREA LOST Begin */
typedef struct
{
    VOS_UINT8       		enValidFlag;   /*门限是否有效  */
    VOS_UINT8  			    aucRsv[3]; 	   /*保留位*/
    VOS_INT16               sMtcThresRsrp; /*能量门限，-116~0 */
    VOS_UINT16              usMtcThresCnt; /*计数门限*/
}TDS_MTC_AREA_LOST_THRESHOLD_STRU;
/* MTC AREA LOST End */

typedef struct
{
    VOS_UINT8       		enValidFlag;   /*定时器是否有效  */
    VOS_UINT8  			    aucRsv[3]; 	   /*保留位*/
    VOS_UINT32              ulTdsAreaLostTimeLen; /*定时器时长 sec */
}TDS_MTC_AREA_LOST_TIME_LEN_STRU;

/* MTC RESEL Begin */
typedef struct
{
    VOS_UINT8              enValidFlag;         /* 离网重选功能是否有效  */
    VOS_UINT8              ucFindBchClearFlag;  /* 搜网时清理评估 内部测试使用 */
    VOS_UINT8              ucStateChangeClear;  /* 状态转换时清理评估 内部测试使用  */
    VOS_UINT8              ucReserved;
    VOS_INT32              lMtcLostConThresh;   /* 连接态态的重选门限    */
    VOS_INT32              lMtcLostIdlThresh;   /* IDL态的重选门限       */
    VOS_UINT32             ulTreselLen;         /* 重选定时器时长，单位s */
    VOS_INT32              lThreshMtcGsm;       /* 本地GSM能量门限       */
    VOS_UINT32             ulMtcAvalThresh;     /* 回迁门限              */
    VOS_UINT32             ulMtcAvalTimeLen;    /* 回迁定时器时长        */
    VOS_UINT32             aulReserved[4];      /* 备用 */
} NV_MTC_TDS_RESEL_PARA_STRU;
/* MTC RESEL End */

typedef struct
{
  VOS_UINT8   ucIratRscpthreshold;
  VOS_UINT8   ucIratRscpDifference;
  /* Cell-Reselection optimazation in CELL-FACH when Srx/SNR are lower than the thresholds*/
  VOS_UINT16  usCellReselFachSrxThresh; /* CELL-FACH 重选服务小区能量门限*/
  VOS_UINT16  usCellReselFachSNRThresh;  /* CELL-FACH 重选服务小区信噪比门限*/
  VOS_UINT16  usUsableTimeBand39LTECell; /* BAND39下LTE小区有效时长 单位: s */
  VOS_INT16   sBandScanRssiThres;        /* TDS频段有效rssi阈值，单位:1/64dBm */
  VOS_INT16   sHistoryRssiThres;         /* TDS先验频点有效rssi阈值，单位:1/64dBm */
  VOS_UINT8   ucFrToLteTimerLen;         /* 连接态等待启动FR的定时器时长 */
  VOS_UINT8   ucFrToLteInIdleTimerLen;   /* IDLE态等待启动FR的定时器时长 */
  /* RRC Connection Request failure with V300>N300 */
  VOS_UINT8   ucRrcConnectionReqOPTTimes;  /* 随机接入反复次数，V300>N300为1轮 */
  VOS_UINT8   ucRrcConnectionReqOPTBarTime;/* 满足随机接入优化条件后的惩罚时间 */
  VOS_UINT16  usRsve[26];
}TDS_FEATURE_PARA_STRU;

typedef struct T_NVM_HsupaCtrlPara_Tag
{
  VOS_UINT8   snplIndex;
  VOS_UINT8   uphIndex;
  VOS_UINT8   tebsIndexLimit;
  VOS_UINT8   reserved;
}T_NVM_HsupaCtrlPara;

typedef struct T_NVM_FlowCtrlPara_Tag
{
  VOS_UINT8   flowControlOpenDoor;
  VOS_UINT8   flowControlCloseDoor;
  VOS_UINT16  reserved;
}T_NVM_FlowCtrlPara;

typedef struct T_NVM_NetSelectMode_Tag
{
  VOS_UINT8                          mode;
  VOS_UINT8                          acqOrder;
  VOS_UINT8                          reserved[2];
}T_NVM_NetSelectMode;

typedef struct  T_CellDesc_NV_Tag
{
  VOS_UINT16       frequency;
  VOS_UINT8        syncId;
  VOS_UINT8        basicMidamble;
}T_CellDesc_NV;

typedef struct T_NVM_BaList_Tag
{
  VOS_UINT8                          ucNum;
  VOS_UINT8                          reserved[3];
  T_CellDesc_NV                      BaList[16];
}T_NVM_Balist;
/* TRRC CHANGE FOR BA end */
/*****************************************************************************
 结构名    : TDS_NV_CUSTOMIZE_CS_SERVICE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 从NV中读取出表示用户定义的业务开关
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              ulStatus;
    VOS_UINT32                              ulDestCustSrv;
} TDS_NV_CUSTOMIZE_CS_SERVICE_STRU;

typedef struct
{
    VOS_UINT32                          ulNullTimerControl;

    VOS_UINT32                          ulEngRRMTestFlag;

    VOS_UINT32                          ulEQPOut;
}TDS_NV_ENG_NULLTIMER_CONTROL_TESTFLAG_EQPOUT_STRU;

 /*****************************************************************************
 结构名    : TDS_NV_BSIC_FRAME_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 按照 bsic配置请求和偷帧优化方案，增加配置bsic_req和fream_req
             相关参数门限
*****************************************************************************/
 typedef struct
{
    VOS_UINT32        ulFuncFlag;         /* bsic和fream优化功能开关，开关开则如下参数才有效: 0-关闭，1-打开，默认开 */
    VOS_INT16         sRssiBsicThreold;   /* 实际使用中*8.bsic重配时优先配置RSSI超过该门限的小区，若没有则走远流程配大于-102db的小区 */
    VOS_INT8          cRscp3aThreold;     /* 若网侧未配3a则服务小区徐满足此门限或者若配置了3c当G测量满足3c(未配不判断)才会偷帧*/
    VOS_UINT8         ucFrameLength;      /* 物理层偷帧长度 */
    VOS_UINT8         ucResv[4];          /* 保留位 */
}TDS_NV_BSIC_FRAME_PARA_STRU;

/*****************************************************************************
结构名    : TDS_NV_MEAS_IMPROVE_PARA_STRU
协议表格  :
ASN.1描述 :
结构说明  : 协议栈的和协议功能相关的开关的结构体
*****************************************************************************/
typedef struct
{
 VOS_UINT8           ucSwitchFlag;               /* 优化功能控制开关:1-开;0-关 */
 VOS_INT8            cTd_Threshold_CS_Only;      /* 仅有CS业务时Tds服务小区评判门限,默认值:-97db */
 VOS_INT8            cTd_Threshold;              /* PS||CS+PS业务时Tds服务小区评判门限,默认值:-100db  */
 VOS_INT8            cIrat_Threshold;            /* Irat小区测量值评判门限,默认值:-90db */
}TDS_NV_MEAS_IMPROVE_PARA_STRU;
 /*****************************************************************************
  结构名    : TRRC_NV_NOT_TO_LTE_STRU
  协议表格  :
  ASN.1描述 :
  结构说明  : NOT TO LTE NV
 *****************************************************************************/
 typedef struct
 {
   VOS_UINT32          ulTdsNotCampLteLen;
 }TRRC_NV_NOT_TO_LTE_STRU;
  /*****************************************************************************
  结构名    : TDS_NV_CELL_SEARCH_TIME_STRU
  协议表格  :
  ASN.1描述 :
  结构说明  :  指定搜搜网时间结构体
 *****************************************************************************/
 typedef struct
 {
    VOS_UINT32        ulSuccAvgTime;
    VOS_UINT32        ulSuccCnt;
    VOS_UINT32        ulFailAvgTime;
    VOS_UINT32        ulFailCnt;
 }TDS_NV_CELL_SEARCH_TIME_STRU;
#endif



