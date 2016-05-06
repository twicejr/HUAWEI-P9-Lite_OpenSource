/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CdsDebug.h
  版 本 号   : 初稿
  作    者   : y00151394
  生成日期   : 2011年12月12日
  最近修改   :
  功能描述   : 定义CDS统计相关软调
  函数列表   :
  修改历史   :
  1.日    期   : 2011年12月12日
    作    者   : y00151394
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CDS_DEBUG_H__
#define __CDS_DEBUG_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "product_config.h"
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : CDS_FLOW_DEBUG_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : CDS流量上报Debug开关
*****************************************************************************/
enum CDS_FLOW_DEBUG_ENUM
{
    CDS_FLOW_DEBUG_OFF                  = 0,
    CDS_FLOW_DEBUG_DL_ON                = 1,
    CDS_FLOW_DEBUG_UL_ON                = 2,
    CDS_FLOW_DEBUG_ALL_ON               = 3,
    CDS_FLOW_DEBUG_BUTT
};

/*****************************************************************************
   5 STRUCT定义
*****************************************************************************/


/*****************************************************************************
 结构名    : CDS_MODEM_STATS_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 不同Modem的统计信息
*****************************************************************************/
typedef struct
{
    /*GU上行数传信息*/
    VOS_UINT32              ulULGURxPktNum;                  /*上行GU模接收的PKT数量*/
    VOS_UINT32              ulULGUFcFreePktNum;              /*GU上行流控丢包个数*/
    VOS_UINT32              ulULGUSendToRabmNum;             /*GU发送到RABM个数*/
    VOS_UINT32              ulULGUSavePktNum;                /*GU上行缓存包个数*/
    VOS_UINT32              ulULGURabmStateErr;              /*GU上行RABM状态异常*/

    /*GU下行数传信息*/
    VOS_UINT32              ulDLGSMRxSduNum;                 /*接收GSM模下行SDU*/
    VOS_UINT32              ulDLGSMRxImsNum;                 /*GSM下接收IMS数据包个数*/
    VOS_UINT32              ulDLGSMFcFreeSduNum;             /*GSM下流控引起的丢包*/
    VOS_UINT32              ulDLGSMEnQueSucc;                /*入SDU队列成功次数*/
    VOS_UINT32              ulDLGSMEnQueFail;                /*入SDU队列失败次数*/

    VOS_UINT32              ulDLUMTSRxSduNum;                /*接收UMTS模下行SDU*/
    VOS_UINT32              ulDLUMTSRxImsNum;                /*UMTS下接收IMS数据包个数*/
    VOS_UINT32              ulDLUMTSFcFreeSduNum;            /*UMTS下流控引起的丢包*/
    VOS_UINT32              ulDLUMTSDirectFreeSduNum;        /*UMTS下流控引起的丢包*/
    VOS_UINT32              ulDLUMTSEnQueSucc;               /*入SDU队列成功次数*/
    VOS_UINT32              ulDLUMTSEnQueFail;               /*入SDU队列失败次数*/

    /*CDMA下行数传信息*/
    VOS_UINT32              ulDL1xRxSduNum;                  /*接收1x模下行SDU*/
    VOS_UINT32              ulDL1xFcFreeSduNum;              /*1x下流控引起的丢包*/
    VOS_UINT32              ulDL1xDirectFreeSduNum;          /*1x下直接释放的包个数*/
    VOS_UINT32              ulDL1xEnQueSucc;                 /*1x入SDU队列成功次数*/
    VOS_UINT32              ulDL1xEnQueFail;                 /*1x入SDU队列失败次数*/

    VOS_UINT32              ulDLHRPDRxSduNum;                /*接收HRPD模下行SDU*/
    VOS_UINT32              ulDLHRPDFcFreeSduNum;            /*HRPD下流控引起的丢包*/
    VOS_UINT32              ulDLHRPDDirectFreeSduNum;        /*HRPD下流控引起的丢包*/
    VOS_UINT32              ulDLHRPDEnQueSucc;               /*HRPD入SDU队列成功次数*/
    VOS_UINT32              ulDLHRPDEnQueFail;               /*HRPD入SDU队列失败次数*/

    VOS_UINT32              ulLBDLRxSduInGSM;                /*下行GSM模下接收LB SDU个数*/
    VOS_UINT32              ulLBDLRxSduInUMTS;               /*下行UMTS模下接收LB SDU个数*/
    VOS_UINT32              ulLBDLRxSduInCDMA;               /*下行CDMA模下接收LB SDU个数*/

}CDS_MODEM_STATS_INFO_STRU;

/*****************************************************************************
 结构名    : CDS_STATS_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CDS统计量
*****************************************************************************/
typedef struct CDS_STATS_INFO
{
    /*上下行事件统计*/
    VOS_UINT32              ulIpfULIntNum;                   /*收到IPF上行中断次数*/
    VOS_UINT32              ulULProcIpfIntNum;               /*上行处理IPF中断次数*/

    VOS_UINT32              ulUlAdqEmtypIntNum;              /*上行IPF ADQ空中断次数*/
    VOS_UINT32              ulUlProcAdqEmptyIntNum;          /*上行处理IPF ADQ空中断次数*/

    VOS_UINT32              ulIpfDlCallMemFreeNum;           /*下行IPF调用内存释放函数次数*/
    VOS_UINT32              ulIpfDlFreeMemNum;               /*BSP调用回调函数释放内存的个数*/

    VOS_UINT32              ulDL10msTmrTrigEvent;            /*下行10ms周期性定时器触发下行事件次数*/
    VOS_UINT32              ulDL1msIntTrigEvent;             /*LTE 1ms中断触发下行事件次数*/
    VOS_UINT32              ulDLUmtsIntTrigEvent;            /*UMTS DSP中断触发下行事件次数*/
    VOS_UINT32              ulDLCDMAIntTrigEvent;            /*CDMA 中断触发下行事件次数*/
    VOS_UINT32              ulDLProcEventNum;                /*CDS处理下行事件次数*/


    /*上行RD统计信息*/
    VOS_UINT32              ulULIpfRxRDNum;                  /*上行IPF收到RD个数*/
    VOS_UINT32              ulULIpfTransMemFailNum;          /*上行IPF内存转换失败个数*/
    VOS_UINT32              ulULIpfModemIdErrNum;            /*上行IPF ModemId错误次数*/
    VOS_UINT32              ulULIpfFreePktInLB;              /*上行IPF在环回模式下释放的内存*/
    VOS_UINT32              ulULIpfRxNdisPktNum;             /*上行IPF收到NDIS包个数*/
    VOS_UINT32              ulULIpfRxIpPktNum;               /*上行IPF收到IP包(非分片)个数*/
    VOS_UINT32              ulULIpfRxIpSegNum;               /*上行IPF收到IP分片个数*/
    VOS_UINT32              ulULIpfFilterErrNum;             /*上行IPF过滤错误包个数*/

    VOS_UINT32              ulULRecvNdPktNum;                /*上行收到ND包的个数*/
    VOS_UINT32              ulULRecvDhcpPktNum;              /*上行收到DHCP包的个数*/

    /*上行IP包处理*/
    VOS_UINT32              ulULASRxIpPktNum;                /*上行接入层收到的数据包*/
    VOS_UINT32              ulULDirectFreePktNum;            /*上行打桩直接释放的数据包个数*/
    VOS_UINT32              ulULLTERxPktNum;                 /*上行LTE模接收PKT数量*/
    VOS_UINT32              ulUL1xRxPktNum;                  /*上行1x模接收PKT数量*/
    VOS_UINT32              ulULHRPDRxPktNum;                /*上行HRPD模接收PKT数量*/
    VOS_UINT32              ulULGURxPktNum;                  /*上行GU模接收的PKT数量*/
    VOS_UINT32              ulULNULLRxPktNum;                /*上行NULL模接收到的数据*/
    VOS_UINT32              ulULRanModeErrFreeNum;           /*上行接入模式错误释放内存个数*/

    VOS_UINT32              ulULLTEFcFreePktNum;             /*LTE上行流控丢包个数*/
    VOS_UINT32              ulULLTEProcIpSegFail;            /*LTE处理分片包失败个数*/
    VOS_UINT32              ulULLTESendToLPdcpNum;           /*LTE发送到LPDCP个数*/
    VOS_UINT32              ulULLTESavePktNum;               /*LTE上行缓存包个数*/
    VOS_UINT32              ulULLTEERabmStateErr;            /*LTE上行ERABM状态异常释放内存个数*/

    VOS_UINT32              ulULCDMAFcFreePktNum;            /*CDMA上行流控丢包个数*/
    VOS_UINT32              ulUL1xFcFreePktNum;              /*1x上行流控丢包个数*/
    VOS_UINT32              ulUL1xSendToPppNum;              /*1x发送到PPP个数*/
    VOS_UINT32              ulUL1xSendToRlpNum;              /*1x发送到RLP个数*/
    VOS_UINT32              ulUL1xSavePktNum;                /*1x上行缓存包个数*/
    VOS_UINT32              ulUL1xRabStateIna;               /*1x上行RAB状态INACTIVE个数*/
    VOS_UINT32              ulUL1xRabStateErr;               /*1x上行RAB状态异常释放内存个数*/

    VOS_UINT32              ulULHRPDFcFreePktNum;            /*HRPD上行流控丢包个数*/
    VOS_UINT32              ulULHRPDSendToPppNum;            /*HRPD发送到PPP个数*/
    VOS_UINT32              ulULHRPDSavePktNum;              /*HRPD上行缓存包个数*/
    VOS_UINT32              ulULHRPDRabStateIna;             /*HRPD上行RAB状态INACTIVE个数*/
    VOS_UINT32              ulULHRPDRabStateErr;             /*HRPD上行RAB状态异常释放内存个数*/

    VOS_UINT32              ulULGUFcFreePktNum;              /*GU上行流控丢包个数*/
    VOS_UINT32              ulULGUSendToRabmNum;             /*GU发送到RABM个数*/
    VOS_UINT32              ulULGUSavePktNum;                /*GU上行缓存包个数*/
    VOS_UINT32              ulULGURabmStateErr;              /*GU上行RABM状态异常*/

    VOS_UINT32              ulULBuffEnQueSucc;               /*上行缓存数据入队成功次数*/
    VOS_UINT32              ulULBuffEnQueFail;               /*上行缓存数据入队失败*/
    VOS_UINT32              ulULBuffSoftFilterFail;          /*上行发送缓存数据失败个数*/
    VOS_UINT32              ulULBuffSendPktSuccNum;          /*上行发送缓存数据个数*/
    VOS_UINT32              ulULBuffFreePktNum;              /*上行清空缓存数据个数*/

    /*软过滤相关统计量*/
    VOS_UINT32              ulULSoftFilterPktNum;            /*上行软过滤数据包个数*/
    VOS_UINT32              ulULSoftFilterIPv4Num;           /*上行软过滤IPV4数据包个数*/
    VOS_UINT32              ulULSoftFilterIPv6Num;           /*上行软过滤IPV6数据包个数*/
    VOS_UINT32              ulULSoftFilterFailNum;           /*上行软过滤失败个数*/
    VOS_UINT32              ulULSoftFilterIPSegNum;          /*上行软过滤IP分片个数*/
    VOS_UINT32              ulULSoftFilterIPSegSucc;         /*上行软过滤IP分片处理成功个数*/
    VOS_UINT32              ulULSoftFilterIPSegFail;         /*上行软过滤IP分片处理失败个数*/

    /*上行AD信息*/
    VOS_UINT32              ulULADQCfgAdNum;                 /*ADQ配置个数*/
    VOS_UINT32              ulULADQCfgAd0Num;                /*AD0配置个数*/
    VOS_UINT32              ulULADQCfgAd1Num;                /*AD1配置个数*/
    VOS_UINT32              ulULADQAllocMemNum;              /*为ADQ申请的内存个数*/
    VOS_UINT32              ulULADQFreeMemNum;               /*为ADQ配置失败释放的内存个数*/
    VOS_UINT32              ulULADQCfgAdSucc;                /*ADQ配置AD成功次数*/
    VOS_UINT32              ulULADQCfgAdFail;                /*ADQ配置AD失败次数*/
    VOS_UINT32              ulULADQStartEmptyTmrNum;         /*ADQ启动空保护定时器次数*/
    VOS_UINT32              ulULADQStopEmptyTmrNum;          /*ADQ停止空保护定时器次数*/
    VOS_UINT32              ulULADQEmptyTmrTimeoutNum;       /*ADQ空保护定时器超时次数*/
    VOS_UINT32              ulULADQAd0EmptyIntNum;           /*AD0引起空中断次数*/
    VOS_UINT32              ulULADQAd1EmptyIntNum;           /*AD1引起空中断次数*/

    /*下行SDU信息*/
    VOS_UINT32              ulDLGSMRxSduNum;                 /*接收GSM模下行SDU*/
    VOS_UINT32              ulDLGSMRxImsNum;                 /*接收GSM模下行IMS数据包个数*/
    VOS_UINT32              ulDLGSMFcFreeSduNum;             /*GSM下流控引起的丢包*/
    VOS_UINT32              ulDLGSMGetDeftRabIdFail;         /*GSM模获得RABID对应的默认RABID失败*/
    VOS_UINT32              ulDLGSMEnQueSucc;                /*入SDU队列成功次数*/
    VOS_UINT32              ulDLGSMEnQueFail;                /*入SDU队列失败次数*/

    VOS_UINT32              ulDLUMTSRxSduNum;                /*接收UMTS模下行SDU*/
    VOS_UINT32              ulDLUMTSRxImsNum;                /*接收UMTS模下行IMS数据包个数*/
    VOS_UINT32              ulDLUMTSFcFreeSduNum;            /*UMTS下流控引起的丢包*/
    VOS_UINT32              ulDLUMTSDirectFreeSduNum;        /*UMTS下流控引起的丢包*/
    VOS_UINT32              ulDLUMTSGetDeftRabIdFail;        /*UMTS模获得RABID对应的默认RABID失败*/
    VOS_UINT32              ulDLUMTSEnQueSucc;               /*入SDU队列成功次数*/
    VOS_UINT32              ulDLUMTSEnQueFail;               /*入SDU队列失败次数*/

    VOS_UINT32              ulDLLteRxSduNum;                 /*接收LTE模下行SDU*/
    VOS_UINT32              ulDLLteRxSduLenErrNum;           /*接收LTE摸下行SDU长度错误*/
    VOS_UINT32              ulDLLteRxDbgPkt;                 /*接收LTE L2调试数据*/
    VOS_UINT32              ulDLLteRxMbmsSdu;                /*接收MBMS SDU个数*/
    VOS_UINT32              ulDLLteRxImsNum;                 /*接收LTE模下行IMS数据包个数*/
    VOS_UINT32              ulDLLteFcFreeSduNum;             /*LTE下流控引起的丢包*/
    VOS_UINT32              ulDLLteDirectFreeSduNum;         /*GSM下流控引起的丢包*/
    VOS_UINT32              ulDLLteGetEpsbIDFail;            /*LTE模获得DRB对应的EPSBID失败*/
    VOS_UINT32              ulDLLteGetDeftEpsbIDFail;        /*LTE模获得DRB对应的默认EPSBID失败*/
    VOS_UINT32              ulDLLteEnQueSucc;                /*入SDU队列成功次数*/
    VOS_UINT32              ulDLLteEnQueFail;                /*入SDU队列失败次数*/

    VOS_UINT32              ulDL1xRxSduNum;                  /*接收1X模下行SDU*/
    VOS_UINT32              ulDL1xFcFreeSduNum;              /*1X下流控引起的丢包*/
    VOS_UINT32              ulDL1xDirectFreeSduNum;          /*1X下流控引起的丢包*/
    VOS_UINT32              ulDL1xGetRabIDFail;              /*1X模获得DRB对应的RABID失败*/
    VOS_UINT32              ulDL1xGetDeftRabIDFail;          /*1X模获得DRB对应的默认RABID失败*/
    VOS_UINT32              ulDL1xEnQueSucc;                 /*1X入SDU队列成功次数*/
    VOS_UINT32              ulDL1xEnQueFail;                 /*1X入SDU队列失败次数*/

    VOS_UINT32              ulDLHRPDRxSduNum;                /*接收HRPD模下行SDU*/
    VOS_UINT32              ulDLHRPDFcFreeSduNum;            /*HRPD下流控引起的丢包*/
    VOS_UINT32              ulDLHRPDDirectFreeSduNum;        /*HRPD下流控引起的丢包*/
    VOS_UINT32              ulDLHRPDGetRabIDFail;            /*HRPD模获得DRB对应的RABID失败*/
    VOS_UINT32              ulDLHRPDGetDeftRabIDFail;        /*HRPD模获得DRB对应的默认RABID失败*/
    VOS_UINT32              ulDLHRPDEnQueSucc;               /*HRPD入SDU队列成功次数*/
    VOS_UINT32              ulDLHRPDEnQueFail;               /*HRPD入SDU队列失败次数*/

    VOS_UINT32              ulDLEnSduQueSucc;                /*入SDU队列成功次数*/
    VOS_UINT32              ulDLEnSduQueFail;                /*入SDU队列失败次数*/
    VOS_UINT32              ulDLSduTrigEvent;                /*下行SDU触发事件次数*/

    /*下行IPF信息*/
    VOS_UINT32              ulDLIpfSaveSrcMemFail;           /*下行IPF源内存队列不足导致内存*/
    VOS_UINT32              ulDLIpfSaveSrcMemSucc;           /*GU下行保存源内存个数*/
    VOS_UINT32              ulDLIpfFreeSrcMemNum;            /*GU释放源内存个数*/
    VOS_UINT32              ulDLIpfFreeSrcMemErr;            /*释放内存错误*/

    VOS_UINT32              ulDLIpfCfgHaveNoBD;              /*配置下行IPF没有BD次数*/
    VOS_UINT32              ulDLIpfCfgHaveNoCD;              /*配置下行IPF没有CD次数*/
    VOS_UINT32              ulDLIpfCfgCDNotEnough;           /*配置下行IPF CD不够次数*/
    VOS_UINT32              ulDLIpfCfgBDSucc;                /*配置BD成功次数*/
    VOS_UINT32              ulDLIpfCfgBDFail;                /*配置BD失败次数*/
    VOS_UINT32              ulDLIpfCfgBDAllocMemFail;        /*配置BD申请内存失败次数*/
    VOS_UINT32              ulDLIpfCfgBDSduLenErr;           /*配置BD SDU长度错误*/

    /*环回模式数传信息*/
    VOS_UINT32              ulLBDLRxSduInGSM;                 /*下行GSM模下接收LB SDU个数*/
    VOS_UINT32              ulLBDLRxSduInUMTS;                /*下行UMTS模下接收LB SDU个数*/
    VOS_UINT32              ulLBDLRxSduInLte;                 /*下行LTE模下接收LB SDU个数*/
    VOS_UINT32              ulLBDLRxSduInCDMA;                 /*下行CDMA模下接收LB SDU个数*/
    VOS_UINT32              ulLBDLRxSduInNonModeB;            /*下行在非ModemB下收到的SDU*/
    VOS_UINT32              ulLBDLAllocMemFail;               /*环回模式申请内存失败*/
    VOS_UINT32              ulLBDDLEnQueSucc;                 /*环回模式下入队成功次数*/
    VOS_UINT32              ulLBDLEnQueFail;                  /*入队失败次数*/
    VOS_UINT32              ulLBULSoftFilterFail;             /*环回模式上行软过滤失败次数*/
    VOS_UINT32              ulLBUlSendPktNum;                 /*环回模式上行发送数据包个数*/
    VOS_UINT32              ulLBUlClearPktNum;                /*环回模式上行释放数据包个数*/

    /*IMS相关统计量*/
    VOS_UINT32              ulImsULRxFunCallNum;                /*上行接收函数调用次数*/
    VOS_UINT32              ulImsULRxFunParaErr;                /*上行接收函数入参错误次数*/
    VOS_UINT32              ulImsULRxNicPktNum;                 /*接收IMS NIC数据包个数*/
    VOS_UINT32              ulImsULAllocMemFail;                /*上行IMS申请内存失败个数*/
    VOS_UINT32              ulImsULEnQueFail;                   /*上行IMS入队失败个数*/
    VOS_UINT32              ulImsULEnQueSucc;                   /*上行IMS入队成功个数*/
    VOS_UINT32              ulImsULTrigImsEvent;                /*上行触发IMS_PROC事件次数*/
    VOS_UINT32              ulImsULProcImsEvent;                /*上行处理IMS_PROC事件次数*/
    VOS_UINT32              ulImsULSoftFilterFail;              /*上行IMS数据包软过滤失败次数*/
    VOS_UINT32              ulImsULSendToRan;                   /*上行IMS数据包发送到空口个数*/

    VOS_UINT32              ulImsDLRxImsPkt;                    /*下行接收IMS数据包个数*/
    VOS_UINT32              ulImsDLNdPktNum;                    /*下行接收到NDCLIENT数据包个数*/
    VOS_UINT32              ulImsDLAllocMemFail;                /*下行申请内存失败个数*/
    VOS_UINT32              ulImsDLGetDestPortFail;             /*下行获取目的端口号失败个数*/
    VOS_UINT32              ulImsDLSendToNicFail;               /*下行发送到IMS NIC数据包失败个数*/
    VOS_UINT32              ulImsDLSendToNicSucc;               /*下行发送到IMS NIC数据包成功个数*/

    VOS_UINT32              ulImsDLRxUtPkt;                     /*下行接收IMS Ut数据包个数*/
    VOS_UINT32              ulImsDLUtPktProcErrNum;             /*下行IMS Ut数据包处理失败个数*/
    VOS_UINT32              ulImsDLUtPktProcSuccNum;            /*下行IMS Ut数据包处理成功个数*/

    /* 流量统计信息 */
    VOS_UINT32              ulDLFlowDebugFlag;                  /*下行流量Debug开关*/
    VOS_UINT32              ulDLFlowRptThreshold;               /*下行流量上报门限*/
    VOS_UINT32              ulDLFlowInfo;                       /*下行流量Byte计数*/
    VOS_UINT32              ulDLStartSlice;                     /*下行流量统计开始时间*/
    VOS_UINT32              ulDLEndSlice;                       /*下行流量统计结束时间*/

    VOS_UINT32              ulULFlowDebugFlag;                  /*上行流量Debug开关*/
    VOS_UINT32              ulULFlowRptThreshold;               /*上行流量上报门限*/
    VOS_UINT32              ulULFlowInfo;                       /*上行流量Byte计数*/
    VOS_UINT32              ulULStartSlice;                     /*上行流量统计开始时间*/
    VOS_UINT32              ulULEndSlice;                       /*上行流量统计结束时间*/
#if (FEATURE_ON == FEATURE_BASTET)
    /*BASTET相关统计量*/
    VOS_UINT32              ulBstULRxFunCallNum;            /*Bastet调用上行发送次数*/
    VOS_UINT32              ulBstULRxFunParaErr;            /*Bastet上行发送空口参数出错次数*/
    VOS_UINT32              ulBstULRxNicPktNum;             /*Bastet当前网卡状态未知错误次数*/
    VOS_UINT32              ulBstULAllocMemFail;            /*Bastet接收数据申请TTF空间出错次数*/
    VOS_UINT32              ulBstULEnQueFail;               /*Bastet上行数据入队失败次数*/
    VOS_UINT32              ulBstULEnQueSucc;               /*Bastet上行数据入队成功次数*/
    VOS_UINT32              ulBstULTrigBstEvent;            /*Bastet出发上行发送事件次数*/
    VOS_UINT32              ulBstULProcBstEvent;            /*CDS接到Bastet上行处理事件次数*/
    VOS_UINT32              ulBstFwProcBstEvent;            /*CDS接到Bastet转发给AP处理事件次数*/
    VOS_UINT32              ulBstULSoftFilterFail;          /*Bastet数据上行软滤波出错*/
    VOS_UINT32              ulBstULSendToRan;               /*Bastet成功发送到空口数量*/

    VOS_UINT32              ulBstDLRxBstPkt;                /*CDS收到下行属于Bastet代理端口的数据包个数*/
    VOS_UINT32              ulBstDLRxFunParaErr;            /*CDS收到下行Bastet数据包参数出差次数*/
    VOS_UINT32              ulBstDLAllocMemFail;            /*CDS创建下行代理数据包消息失败次数*/
    VOS_UINT32              ulBstDLSendToNicSucc;           /*CDS模块成功向Bastet发送数据包个数*/

    VOS_UINT32              ulBstFw2ApFunParaErr;           /*Bastet转发到AP包参数出错*/
    VOS_UINT32              ulBstFw2ApEnQueFail;            /*Bastet转发包入队出错*/
    VOS_UINT32              ulBstFw2ApEnQueSucc;            /*Bastet转发包入队成功次数*/

    VOS_UINT32              ulBstFilterNidErrNum;           /*CDS模块检测Bastet虚拟网卡状态不可用*/
    VOS_UINT32              ulBstFilterRubbishNum;          /*CDS模块将数据包作为垃圾包直接丢给Bastet个数*/
    VOS_UINT32              ulBstFilterAllocMemFail;        /*CDS过滤识别过程中，申请空间失败次数*/
    VOS_UINT32              ulBstFilterWrongPrtcNum;        /*CDS过滤过程中识别到非UDP,TCP协议次数*/
    VOS_UINT32              ulBstFilterErrorCopyPkt;        /*CDS拷贝缓冲包到MEMORY失败次数*/
    VOS_UINT32              ulBstFilterSuccsCopyPkt;        /*CDS拷贝缓冲包到MEMORY成功次数*/
    VOS_UINT32              ulBstFilterSuccsMachPkt;        /*CDS成功匹配Bastet数据包次数*/
    VOS_UINT32              ulBstFilterNotIpver4Pkt;        /*CDS过滤Bastet端口发现非IPV4包个数*/
    VOS_UINT32              ulBstFilterFragementPkt;        /*CDS过滤Bastet端口发现分片包次数*/
#endif
    CDS_MODEM_STATS_INFO_STRU  astModemStats[MODEM_ID_BUTT + 1];
}CDS_STATS_INFO_STRU;

/*****************************************************************************
  6 UNION定义
*****************************************************************************/


/*****************************************************************************
  7 全局变量声明
*****************************************************************************/
extern   CDS_STATS_INFO_STRU    g_stCdsStats;

/*上下行事件统计*/
#define  CDS_DBG_RECV_UL_IPF_INT(n)                (g_stCdsStats.ulIpfULIntNum += (n))
#define  CDS_DBG_UL_PROC_IPF_INT_NUM(n)            (g_stCdsStats.ulULProcIpfIntNum += (n))
#define  CDS_DBG_UL_RX_ADQ_EMPTY_INT(n)            (g_stCdsStats.ulUlAdqEmtypIntNum += (n))
#define  CDS_DBG_UL_PROC_ADQ_EMPTY_INT_NUM(n)      (g_stCdsStats.ulUlProcAdqEmptyIntNum += (n))
#define  CDS_DBG_RECV_DL_MEMFREE_CB_NUM(n)         (g_stCdsStats.ulIpfDlCallMemFreeNum += (n))
#define  CDS_DBG_DL_FREE_MEM_NUM(n)                (g_stCdsStats.ulIpfDlFreeMemNum += (n))
#define  CDS_DBG_DL_10MS_TMR_TRIG_EVENT(n)         (g_stCdsStats.ulDL10msTmrTrigEvent += (n))
#define  CDS_DBG_DL_LTE_1MS_INT_TRIG_EVENT(n)      (g_stCdsStats.ulDL1msIntTrigEvent += (n))
#define  CDS_DBG_DL_UMTS_INT_TRIG_EVENT(n)         (g_stCdsStats.ulDLUmtsIntTrigEvent += (n))
#define  CDS_DBG_DL_CDMA_INT_TRIG_EVENT(n)         (g_stCdsStats.ulDLCDMAIntTrigEvent += (n))
#define  CDS_DBG_DL_PROC_EVENT_NUM(n)              (g_stCdsStats.ulDLProcEventNum += (n))


/*上行IPF RD统计量*/
#define  CDS_DBG_UL_IPF_RX_RD_NUM(n)                (g_stCdsStats.ulULIpfRxRDNum += (n))
#define  CDS_DBG_UL_IPF_TRANS_MEM_FAIL_NUM(n)       (g_stCdsStats.ulULIpfTransMemFailNum += (n))
#define  CDS_DBG_UL_IPF_MODEMID_ERROR_NUM(n)        (g_stCdsStats.ulULIpfModemIdErrNum += (n))
#define  CDS_DBG_UL_IPF_FREE_PKT_IN_LB(n)           (g_stCdsStats.ulULIpfFreePktInLB += (n))
#define  CDS_DBG_UL_IPF_RX_IP_PKT_NUM(n)            (g_stCdsStats.ulULIpfRxIpPktNum += (n))
#define  CDS_DBG_UL_IPF_RX_IP_SEG_NUM(n)            (g_stCdsStats.ulULIpfRxIpSegNum += (n))
#define  CDS_DBG_UL_IPF_RX_NDIS_PKT_NUM(n)          (g_stCdsStats.ulULIpfRxNdisPktNum += (n))
#define  CDS_DBG_UL_IPF_FILTER_ERROR_NUM(n)         (g_stCdsStats.ulULIpfFilterErrNum += (n))

#define  CDS_DBG_UL_RECV_ND_PKT_NUM(n)              (g_stCdsStats.ulULRecvNdPktNum += (n))

/*上行AD统计量*/
#define  CDS_DBG_UL_ADQ_ALLOC_MEM_NUM(n)            (g_stCdsStats.ulULADQAllocMemNum += (n))
#define  CDS_DBG_UL_ADQ_FREE_MEM_NUM(n)             (g_stCdsStats.ulULADQFreeMemNum  += (n))
#define  CDS_DBG_UL_ADQ_CFG_ADQ_SUCC_NUM(n)         (g_stCdsStats.ulULADQCfgAdSucc += (n))
#define  CDS_DBG_UL_ADQ_CFG_ADQ_FAIL_NUM(n)         (g_stCdsStats.ulULADQCfgAdFail += (n))
#define  CDS_DBG_UL_ADQ_CFG_AD_NUM(n)               (g_stCdsStats.ulULADQCfgAdNum += (n))
#define  CDS_DBG_UL_ADQ_CFG_AD0_NUM(n)              (g_stCdsStats.ulULADQCfgAd0Num += (n))
#define  CDS_DBG_UL_ADQ_CFG_AD1_NUM(n)              (g_stCdsStats.ulULADQCfgAd1Num += (n))
#define  CDS_DBG_UL_ADQ_START_EMPTY_TMR_NUM(n)      (g_stCdsStats.ulULADQStartEmptyTmrNum += (n))
#define  CDS_DBG_UL_ADQ_STOP_EMPTY_TMR_NUM(n)       (g_stCdsStats.ulULADQStopEmptyTmrNum  += (n))
#define  CDS_DBG_UL_ADQ_EMPTY_TMR_TIMEOUT_NUM(n)    (g_stCdsStats.ulULADQEmptyTmrTimeoutNum  += (n))
#define  CDS_DBG_UL_ADQ_AD0_EMPTY_INT_NUM(n)        (g_stCdsStats.ulULADQAd0EmptyIntNum += (n))
#define  CDS_DBG_UL_ADQ_AD1_EMPTY_INT_NUM(n)        (g_stCdsStats.ulULADQAd1EmptyIntNum  += (n))


/*下行IPF统计量*/
#define  CDS_DBG_DL_IPF_CFG_HAVE_NO_CD(n)           (g_stCdsStats.ulDLIpfCfgHaveNoCD += (n))
#define  CDS_DBG_DL_IPF_CFG_HAVE_NO_BD(n)           (g_stCdsStats.ulDLIpfCfgHaveNoBD += (n))
#define  CDS_DBG_DL_IPF_CFG_CD_NOT_ENOUGH(n)        (g_stCdsStats.ulDLIpfCfgCDNotEnough += (n))
#define  CDS_DBG_DL_IPF_CFG_BD_SUCC_NUM(n)          (g_stCdsStats.ulDLIpfCfgBDSucc += (n))
#define  CDS_DBG_DL_IPF_CFG_BD_FAIL_NUM(n)          (g_stCdsStats.ulDLIpfCfgBDFail += (n))
/*桥接模式*/
#define  CDS_DBG_DL_IPF_SAVE_SRCMEM_FAIL_NUM(n)     (g_stCdsStats.ulDLIpfSaveSrcMemFail   += (n))
#define  CDS_DBG_DL_IPF_SAVE_SRCMEM_SUCC_NUM(n)     (g_stCdsStats.ulDLIpfSaveSrcMemSucc += (n))
#define  CDS_DBG_DL_IPF_FREE_SRCMEM_NUM(n)          (g_stCdsStats.ulDLIpfFreeSrcMemNum   += (n))
#define  CDS_DBG_DL_IPF_FREE_SRCMEM_ERROR(n)        (g_stCdsStats.ulDLIpfFreeSrcMemErr   += (n))
/*非桥接模式*/
#define  CDS_DBG_DL_IPF_CFG_BD_ALLOC_MEM_FAIL(n)    (g_stCdsStats.ulDLIpfCfgBDAllocMemFail += (n))
#define  CDS_DBG_DL_IPF_CFG_BD_SDU_LEN_ERROR(n)     (g_stCdsStats.ulDLIpfCfgBDSduLenErr += (n))


/*环回模式数传处理*/
#define  CDS_DBG_LB_DL_RX_SDU_FROM_GSM(n)           (g_stCdsStats.ulLBDLRxSduInGSM  += (n))
#define  CDS_DBG_LB_DL_RX_SDU_FROM_UMTS(n)          (g_stCdsStats.ulLBDLRxSduInUMTS  += (n))
#define  CDS_DBG_LB_DL_RX_SDU_FROM_LTE(n)           (g_stCdsStats.ulLBDLRxSduInLte  += (n))
#define  CDS_DBG_LB_DL_RX_SDU_FROM_CDMA(n)           (g_stCdsStats.ulLBDLRxSduInCDMA  += (n))
#define  CDS_DBG_LB_DL_RX_SDU_IN_NO_MODE_B(n)       (g_stCdsStats.ulLBDLRxSduInNonModeB  += (n))
#define  CDS_DBG_LB_DL_ALLOC_MEM_FAIL(n)            (g_stCdsStats.ulLBDLAllocMemFail += (n))
#define  CDS_DBG_LB_DL_ENQUE_SUCC_NUM(n)            (g_stCdsStats.ulLBDDLEnQueSucc += (n))
#define  CDS_DBG_LB_DL_ENQUE_FAIL_NUM(n)            (g_stCdsStats.ulLBDLEnQueFail += (n))
#define  CDS_DBG_LB_UL_SOFT_FILTER_FAIL_NUM(n)      (g_stCdsStats.ulLBULSoftFilterFail += (n))
#define  CDS_DBG_LB_UL_SEND_PKT_NUM(n)              (g_stCdsStats.ulLBUlSendPktNum += (n))
#define  CDS_DBG_LB_UL_CLEAR_PKT_NUM(n)             (g_stCdsStats.ulLBUlClearPktNum += (n))


/*上行IP包处理统计量*/
#define  CDS_DBG_UL_AS_RX_IP_PKT_NUM(n)             (g_stCdsStats.ulULASRxIpPktNum += (n))
#define  CDS_DBG_UL_DIRECT_FREE_PKT_NUM(n)          (g_stCdsStats.ulULDirectFreePktNum += (n))
#define  CDS_DBG_UL_LTE_RX_PKT_NUM(n)               (g_stCdsStats.ulULLTERxPktNum += (n))
#define  CDS_DBG_UL_CDMA_RX_PKT_NUM(enRanMode,n)    (enRanMode == APS_CDS_MODE_1X?(g_stCdsStats.ulUL1xRxPktNum += (n)):(g_stCdsStats.ulULHRPDRxPktNum += (n)))
#define  CDS_DBG_UL_GU_RX_PKT_NUM(n)                (g_stCdsStats.ulULGURxPktNum  += (n))
#define  CDS_DBG_UL_NULL_RX_PKT_NUM(n)              (g_stCdsStats.ulULNULLRxPktNum  += (n))
#define  CDS_DBG_UL_RAN_MODE_ERROR_FREE_NUM(n)      (g_stCdsStats.ulULRanModeErrFreeNum  += (n))
/*LTE模上行统计量*/
#define  CDS_DBG_UL_LTE_FC_FREE_PKT_NUM(n)          (g_stCdsStats.ulULLTEFcFreePktNum += (n))
#define  CDS_DBG_UL_LTE_PROC_IPSEG_FAIL_NUM(n)      (g_stCdsStats.ulULLTEProcIpSegFail += (n))
#define  CDS_DBG_UL_LTE_SEND_TO_LPDCP_NUM(n)        (g_stCdsStats.ulULLTESendToLPdcpNum += (n))
#define  CDS_DBG_UL_LTE_SAVE_PKT_NUM(n)             (g_stCdsStats.ulULLTESavePktNum  += (n))
#define  CDS_DBG_UL_LTE_ERABM_STATE_ERROR(n)        (g_stCdsStats.ulULLTEERabmStateErr += (n))
/*CDMA 上行统计量*/
#define  CDS_DBG_UL_CDMA_FC_FREE_PKT_NUM(enRanMode,n)    (enRanMode == APS_CDS_MODE_1X?(g_stCdsStats.ulUL1xFcFreePktNum += (n)):(g_stCdsStats.ulULHRPDFcFreePktNum += (n)))
#define  CDS_DBG_UL_1X_SEND_TO_RLP_NUM(n)                (g_stCdsStats.ulUL1xSendToRlpNum += (n))
#define  CDS_DBG_UL_CDMA_SEND_TO_PPP_NUM(ulRanMode,n)    (ulRanMode == APS_CDS_MODE_1X?(g_stCdsStats.ulUL1xSendToPppNum += (n)):(g_stCdsStats.ulULHRPDSendToPppNum += (n)))
#define  CDS_DBG_UL_CDMA_SAVE_PKT_NUM(ulRanMode,n)       (ulRanMode == APS_CDS_MODE_1X?(g_stCdsStats.ulUL1xSavePktNum  += (n)):(g_stCdsStats.ulULHRPDSavePktNum  += (n)))
#define  CDS_DBG_UL_CDMA_RAB_STATE_INACTIVE(ulRanMode,n) (ulRanMode == APS_CDS_MODE_1X?(g_stCdsStats.ulUL1xRabStateIna += (n)):(g_stCdsStats.ulULHRPDRabStateIna += (n)))
#define  CDS_DBG_UL_CDMA_RAB_STATE_ERROR(ulRanMode,n)    (ulRanMode == APS_CDS_MODE_1X?(g_stCdsStats.ulUL1xRabStateErr += (n)):(g_stCdsStats.ulULHRPDRabStateErr += (n)))

/*上行IP包处理统计量*/
#define  CDS_DBG_UL_RECV_DHCP_PKT_NUM(n)            (g_stCdsStats.ulULRecvDhcpPktNum += (n))
/*GU模上行统计量*/
#define  CDS_DBG_UL_GU_FC_FREE_PKT_NUM(n)           (g_stCdsStats.ulULGUFcFreePktNum += (n))
#define  CDS_DBG_UL_GU_SEND_TO_RABM_NUM(n)          (g_stCdsStats.ulULGUSendToRabmNum  += (n))
#define  CDS_DBG_UL_GU_SAVE_PKT_NUM(n)              (g_stCdsStats.ulULGUSavePktNum  += (n))
#define  CDS_DBG_UL_GU_RABM_STATE_ERROR(n)          (g_stCdsStats.ulULGURabmStateErr += (n))
/*上行缓存统计量*/
#define  CDS_DBG_UL_BUFF_EN_QUE_SUCC_NUM(n)         (g_stCdsStats.ulULBuffEnQueSucc += (n))
#define  CDS_DBG_UL_BUFF_EN_QUE_FAIL_NUM(n)         (g_stCdsStats.ulULBuffEnQueFail += (n))
#define  CDS_DBG_UL_BUFF_SOFT_FILTER_FAIL_NUM(n)    (g_stCdsStats.ulULBuffSoftFilterFail += (n))
#define  CDS_DBG_UL_BUFF_SEND_PKT_SUCC_NUM(n)       (g_stCdsStats.ulULBuffSendPktSuccNum += (n))
#define  CDS_DBG_UL_BUFF_FREE_PKT_NUM(n)            (g_stCdsStats.ulULBuffFreePktNum += (n))

/*软过滤相关统计量*/
#define  CDS_DBG_UL_SOFT_FILTER_PKT_NUM(n)          (g_stCdsStats.ulULSoftFilterPktNum += (n))
#define  CDS_DBG_UL_SOFT_FILTER_IPV4_PKT_NUM(n)     (g_stCdsStats.ulULSoftFilterIPv4Num += (n))
#define  CDS_DBG_UL_SOFT_FILTER_IPV6_PKT_NUM(n)     (g_stCdsStats.ulULSoftFilterIPv6Num += (n))
#define  CDS_DBG_UL_SOFT_FILTER_FAIL_NUM(n)         (g_stCdsStats.ulULSoftFilterFailNum += (n))
#define  CDS_DBG_UL_SOFT_FILTER_IPSEG_PKT_NUM(n)    (g_stCdsStats.ulULSoftFilterIPSegNum += (n))
#define  CDS_DBG_UL_SOFT_FILTER_IPSEG_SUCC_NUM(n)   (g_stCdsStats.ulULSoftFilterIPSegSucc += (n))
#define  CDS_DBG_UL_SOFT_FILTER_IPSEG_FAIL_NUM(n)   (g_stCdsStats.ulULSoftFilterIPSegFail += (n))


/*下行SDU统计量*/
#define  CDS_DBG_DL_GSM_RX_SDU_NUM(n)               (g_stCdsStats.ulDLGSMRxSduNum += (n))
#define  CDS_DBG_DL_GSM_RX_IMS_PKT_NUM(n)           (g_stCdsStats.ulDLGSMRxImsNum += (n))
#define  CDS_DBG_DL_GSM_FC_FREE_SDU_NUM(n)          (g_stCdsStats.ulDLGSMFcFreeSduNum += (n))
#define  CDS_DBG_DL_GSM_ENQUE_SUCC_NUM(n)           (g_stCdsStats.ulDLGSMEnQueSucc += (n))
#define  CDS_DBG_DL_GSM_ENQUE_FAIL_NUM(n)           (g_stCdsStats.ulDLGSMEnQueFail += (n))
#define  CDS_DBG_DL_GSM_GET_DEFT_RABID_FAIL(n)      (g_stCdsStats.ulDLGSMGetDeftRabIdFail += (n))

#define  CDS_DBG_DL_UMTS_RX_SDU_NUM(n)              (g_stCdsStats.ulDLUMTSRxSduNum += (n))
#define  CDS_DBG_DL_UMTS_RX_IMS_PKT_NUM(n)          (g_stCdsStats.ulDLUMTSRxImsNum += (n))
#define  CDS_DBG_DL_UMTS_FC_FREE_SDU_NUM(n)         (g_stCdsStats.ulDLUMTSFcFreeSduNum += (n))
#define  CDS_DBG_DL_UMTS_DIRECT_FREE_SDU_NUM(n)     (g_stCdsStats.ulDLUMTSDirectFreeSduNum += (n))
#define  CDS_DBG_DL_UMTS_ENQUE_SUCC_NUM(n)          (g_stCdsStats.ulDLUMTSEnQueSucc += (n))
#define  CDS_DBG_DL_UMTS_ENQUE_FAIL_NUM(n)          (g_stCdsStats.ulDLUMTSEnQueFail += (n))
#define  CDS_DBG_DL_UMTS_GET_DEFT_RABID_FAIL(n)     (g_stCdsStats.ulDLUMTSGetDeftRabIdFail += (n))

#define  CDS_DBG_DL_LTE_RX_SDU_NUM(n)               (g_stCdsStats.ulDLLteRxSduNum += (n))
#define  CDS_DBG_DL_LTE_RX_SDU_LEN_ERR_NUM(n)       (g_stCdsStats.ulDLLteRxSduLenErrNum += (n))
#define  CDS_DBG_DL_LTE_RX_IMS_PKT_NUM(n)           (g_stCdsStats.ulDLLteRxImsNum += (n))
#define  CDS_DBG_DL_LTE_RX_DBG_PKT_NUM(n)           (g_stCdsStats.ulDLLteRxDbgPkt  += (n))
#define  CDS_DBG_DL_LTE_RX_MBMS_SDU_NUM(n)          (g_stCdsStats.ulDLLteRxMbmsSdu  += (n))
#define  CDS_DBG_DL_LTE_FC_FREE_SDU_NUM(n)          (g_stCdsStats.ulDLLteFcFreeSduNum += (n))
#define  CDS_DBG_DL_LTE_DIRECT_FREE_SDU_NUM(n)      (g_stCdsStats.ulDLLteDirectFreeSduNum += (n))
#define  CDS_DBG_DL_LTE_GET_EPSBID_FAIL(n)          (g_stCdsStats.ulDLLteGetEpsbIDFail += (n))
#define  CDS_DBG_DL_LTE_GET_DEFT_EPSBID_FAIL(n)     (g_stCdsStats.ulDLLteGetDeftEpsbIDFail += (n))
#define  CDS_DBG_DL_LTE_ENQUE_SUCC_NUM(n)           (g_stCdsStats.ulDLLteEnQueSucc += (n))
#define  CDS_DBG_DL_LTE_ENQUE_FAIL_NUM(n)           (g_stCdsStats.ulDLLteEnQueFail += (n))

#define  CDS_DBG_DL_CDMA_RX_SDU_NUM(enRanMode,n)                (enRanMode == APS_CDS_MODE_1X?(g_stCdsStats.ulDL1xRxSduNum += (n)):(g_stCdsStats.ulDLHRPDRxSduNum += (n)))
#define  CDS_DBG_DL_CDMA_FC_FREE_SDU_NUM(enRanMode,n)           (enRanMode == APS_CDS_MODE_1X?(g_stCdsStats.ulDL1xFcFreeSduNum += (n)):(g_stCdsStats.ulDLHRPDFcFreeSduNum += (n)))
#define  CDS_DBG_DL_CDMA_DIRECT_FREE_SDU_NUM(enRanMode,n)       (enRanMode == APS_CDS_MODE_1X?(g_stCdsStats.ulDL1xDirectFreeSduNum += (n)):(g_stCdsStats.ulDLHRPDDirectFreeSduNum += (n)))
#define  CDS_DBG_DL_CDMA_GET_RABID_FAIL(enRanMode,n)            (enRanMode == APS_CDS_MODE_1X?(g_stCdsStats.ulDL1xGetRabIDFail += (n)):(g_stCdsStats.ulDLHRPDGetRabIDFail += (n)))
#define  CDS_DBG_DL_CDMA_GET_DEFT_RABID_FAIL(enRanMode,n)       (enRanMode == APS_CDS_MODE_1X?(g_stCdsStats.ulDL1xGetDeftRabIDFail += (n)):(g_stCdsStats.ulDLHRPDGetDeftRabIDFail += (n)))
#define  CDS_DBG_DL_CDMA_ENQUE_SUCC_NUM(enRanMode,n)            (enRanMode == APS_CDS_MODE_1X?(g_stCdsStats.ulDL1xEnQueSucc += (n)):(g_stCdsStats.ulDLHRPDEnQueSucc += (n)))
#define  CDS_DBG_DL_CDMA_ENQUE_FAIL_NUM(enRanMode,n)            (enRanMode == APS_CDS_MODE_1X?(g_stCdsStats.ulDL1xEnQueFail += (n)):(g_stCdsStats.ulDLHRPDEnQueFail += (n)))

#define  CDS_DBG_DL_1X_RX_SDU_NUM(n)                (g_stCdsStats.ulDL1xRxSduNum += (n))
#define  CDS_DBG_DL_1X_FC_FREE_SDU_NUM(n)           (g_stCdsStats.ulDL1xFcFreeSduNum += (n))
#define  CDS_DBG_DL_1X_DIRECT_FREE_SDU_NUM(n)       (g_stCdsStats.ulDL1xDirectFreeSduNum += (n))
#define  CDS_DBG_DL_1X_GET_RABID_FAIL(n)            (g_stCdsStats.ulDL1xGetRabIDFail += (n))
#define  CDS_DBG_DL_1X_GET_DEFT_RABID_FAIL(n)       (g_stCdsStats.ulDL1xGetDeftRabIDFail += (n))
#define  CDS_DBG_DL_1X_ENQUE_SUCC_NUM(n)            (g_stCdsStats.ulDL1xEnQueSucc += (n))
#define  CDS_DBG_DL_1X_ENQUE_FAIL_NUM(n)            (g_stCdsStats.ulDL1xEnQueFail += (n))

#define  CDS_DBG_DL_HRPD_RX_SDU_NUM(n)              (g_stCdsStats.ulDLHRPDRxSduNum += (n))
#define  CDS_DBG_DL_HRPD_FC_FREE_SDU_NUM(n)         (g_stCdsStats.ulDLHRPDFcFreeSduNum += (n))
#define  CDS_DBG_DL_HRPD_DIRECT_FREE_SDU_NUM(n)     (g_stCdsStats.ulDLHRPDDirectFreeSduNum += (n))
#define  CDS_DBG_DL_HRPD_GET_RABID_FAIL(n)          (g_stCdsStats.ulDLHRPDGetRabIDFail += (n))
#define  CDS_DBG_DL_HRPD_GET_DEFT_RABID_FAIL(n)     (g_stCdsStats.ulDLHRPDGetDeftRabIDFail += (n))
#define  CDS_DBG_DL_HRPD_ENQUE_SUCC_NUM(n)          (g_stCdsStats.ulDLHRPDEnQueSucc += (n))
#define  CDS_DBG_DL_HRPD_ENQUE_FAIL_NUM(n)          (g_stCdsStats.ulDLHRPDEnQueFail += (n))

#define  CDS_DBG_DL_EN_SDU_QUEUE_SUCC_NUM(n)        (g_stCdsStats.ulDLEnSduQueSucc  += (n))
#define  CDS_DBG_DL_EN_SDU_QUEUE_FAIL_NUM(n)        (g_stCdsStats.ulDLEnSduQueFail  += (n))
#define  CDS_DBG_DL_SDU_TRIGGER_EVENT_NUM(n)        (g_stCdsStats.ulDLSduTrigEvent += (n))


/*IMS相关统计量*/
#define  CDS_DBG_IMS_UL_RX_FUN_CALL_NUM(n)          (g_stCdsStats.ulImsULRxFunCallNum += (n))
#define  CDS_DBG_IMS_UL_RX_FUN_PARA_ERR(n)          (g_stCdsStats.ulImsULRxFunParaErr += (n))
#define  CDS_DBG_IMS_UL_RX_NIC_PKT_NUM(n)           (g_stCdsStats.ulImsULRxNicPktNum += (n))
#define  CDS_DBG_IMS_UL_ALLOC_MEM_FAIL_NUM(n)       (g_stCdsStats.ulImsULAllocMemFail += (n))
#define  CDS_DBG_IMS_UL_EN_QUE_FAIL_NUM(n)          (g_stCdsStats.ulImsULEnQueFail += (n))
#define  CDS_DBG_IMS_UL_EN_QUE_SUCC_NUM(n)          (g_stCdsStats.ulImsULEnQueSucc += (n))
#define  CDS_DBG_IMS_UL_TRIGGER_IMS_EVENT_NUM(n)    (g_stCdsStats.ulImsULTrigImsEvent += (n))
#define  CDS_DBG_IMS_UL_PROC_IMS_EVENT_NUM(n)       (g_stCdsStats.ulImsULProcImsEvent += (n))
#define  CDS_DBG_IMS_UL_SOFT_FILTER_FAIL_NUM(n)     (g_stCdsStats.ulImsULSoftFilterFail += (n))
#define  CDS_DBG_IMS_UL_SEND_PKT_TO_RAN_NUM(n)      (g_stCdsStats.ulImsULSendToRan += (n))

#define  CDS_DBG_IMS_DL_RX_IMS_PKT_NUM(n)           (g_stCdsStats.ulImsDLRxImsPkt += (n))
#define  CDS_DBG_IMS_DL_RX_ND_PKT_NUM(n)            (g_stCdsStats.ulImsDLNdPktNum += (n))
#define  CDS_DBG_IMS_DL_ALLOC_MEM_FAIL_NUM(n)       (g_stCdsStats.ulImsDLAllocMemFail += (n))
#define  CDS_DBG_IMS_DL_GET_DEST_PORT_FAIL_NUM(n)   (g_stCdsStats.ulImsDLGetDestPortFail += (n))
#define  CDS_DBG_IMS_DL_SEND_TO_NIC_SUCC_NUM(n)     (g_stCdsStats.ulImsDLSendToNicSucc += (n))
#define  CDS_DBG_IMS_DL_SEND_TO_NIC_FAIL_NUM(n)     (g_stCdsStats.ulImsDLSendToNicFail += (n))

#define  CDS_DBG_IMS_DL_RX_IMS_Ut_PKT_NUM(n)        (g_stCdsStats.ulImsDLRxUtPkt += (n))
#define  CDS_DBG_IMS_DL_Ut_PKT_PROC_ERR_NUM(n)      (g_stCdsStats.ulImsDLUtPktProcErrNum += (n))
#define  CDS_DBG_IMS_DL_Ut_PKT_PROC_SUCC_NUM(n)     (g_stCdsStats.ulImsDLUtPktProcSuccNum += (n))

/*Modem GU上行统计量*/
#define  CDS_DBG_MODEM_UL_GU_RX_PKT_NUM(ModemId,n)                (g_stCdsStats.astModemStats[ModemId].ulULGURxPktNum  += (n))
#define  CDS_DBG_MODEM_UL_GU_FC_FREE_PKT_NUM(ModemId,n)           (g_stCdsStats.astModemStats[ModemId].ulULGUFcFreePktNum += (n))
#define  CDS_DBG_MODEM_UL_GU_SEND_TO_RABM_NUM(ModemId,n)          (g_stCdsStats.astModemStats[ModemId].ulULGUSendToRabmNum  += (n))
#define  CDS_DBG_MODEM_UL_GU_SAVE_PKT_NUM(ModemId,n)              (g_stCdsStats.astModemStats[ModemId].ulULGUSavePktNum  += (n))
#define  CDS_DBG_MODEM_UL_GU_RABM_STATE_ERROR(ModemId,n)          (g_stCdsStats.astModemStats[ModemId].ulULGURabmStateErr += (n))

/*Modem GU下行统计量*/
#define  CDS_DBG_MODEM_DL_GSM_RX_SDU_NUM(ModemId,n)               (g_stCdsStats.astModemStats[ModemId].ulDLGSMRxSduNum += (n))
#define  CDS_DBG_MODEM_DL_GSM_RX_IMS_PKT_NUM(ModemId,n)           (g_stCdsStats.astModemStats[ModemId].ulDLGSMRxImsNum += (n))
#define  CDS_DBG_MODEM_ID_LB_DL_RX_SDU_FROM_GSM(ModemId,n)        (g_stCdsStats.astModemStats[ModemId].ulLBDLRxSduInGSM  += (n))
#define  CDS_DBG_MODEM_DL_GSM_FC_FREE_SDU_NUM(ModemId,n)          (g_stCdsStats.astModemStats[ModemId].ulDLGSMFcFreeSduNum += (n))
#define  CDS_DBG_MODEM_DL_GSM_ENQUE_SUCC_NUM(ModemId,n)           (g_stCdsStats.astModemStats[ModemId].ulDLGSMEnQueSucc += (n))
#define  CDS_DBG_MODEM_DL_GSM_ENQUE_FAIL_NUM(ModemId,n)           (g_stCdsStats.astModemStats[ModemId].ulDLGSMEnQueFail += (n))

#define  CDS_DBG_MODEM_DL_UMTS_RX_SDU_NUM(ModemId,n)              (g_stCdsStats.astModemStats[ModemId].ulDLUMTSRxSduNum += (n))
#define  CDS_DBG_MODEM_DL_UMTS_RX_IMS_PKT_NUM(ModemId,n)          (g_stCdsStats.astModemStats[ModemId].ulDLUMTSRxImsNum += (n))
#define  CDS_DBG_MODEM_ID_LB_DL_RX_SDU_FROM_UMTS(ModemId,n)       (g_stCdsStats.astModemStats[ModemId].ulLBDLRxSduInGSM  += (n))
#define  CDS_DBG_MODEM_DL_UMTS_FC_FREE_SDU_NUM(ModemId,n)         (g_stCdsStats.astModemStats[ModemId].ulDLUMTSFcFreeSduNum += (n))
#define  CDS_DBG_MODEM_DL_UMTS_DIRECT_FREE_SDU_NUM(ModemId,n)     (g_stCdsStats.astModemStats[ModemId].ulDLUMTSDirectFreeSduNum += (n))
#define  CDS_DBG_MODEM_DL_UMTS_ENQUE_SUCC_NUM(ModemId,n)          (g_stCdsStats.astModemStats[ModemId].ulDLUMTSEnQueSucc += (n))
#define  CDS_DBG_MODEM_DL_UMTS_ENQUE_FAIL_NUM(ModemId,n)          (g_stCdsStats.astModemStats[ModemId].ulDLUMTSEnQueFail += (n))

#if (FEATURE_ON == FEATURE_BASTET)
/*Bst相关统计量*/
#define  CDS_DBG_BST_UL_RX_FUN_CALL_NUM(n)                        (g_stCdsStats.ulBstULRxFunCallNum += (n))
#define  CDS_DBG_BST_UL_RX_FUN_PARA_ERR(n)                        (g_stCdsStats.ulBstULRxFunParaErr += (n))
#define  CDS_DBG_BST_UL_RX_NIC_PKT_NUM(n)                         (g_stCdsStats.ulBstULRxNicPktNum += (n))
#define  CDS_DBG_BST_UL_ALLOC_MEM_FAIL_NUM(n)                     (g_stCdsStats.ulBstULAllocMemFail += (n))
#define  CDS_DBG_BST_UL_EN_QUE_FAIL_NUM(n)                        (g_stCdsStats.ulBstULEnQueFail += (n))
#define  CDS_DBG_BST_UL_EN_QUE_SUCC_NUM(n)                        (g_stCdsStats.ulBstULEnQueSucc += (n))
#define  CDS_DBG_BST_UL_TRIGGER_BST_EVENT_NUM(n)                  (g_stCdsStats.ulBstULTrigBstEvent += (n))
#define  CDS_DBG_BST_UL_PROC_BST_EVENT_NUM(n)                     (g_stCdsStats.ulBstULProcBstEvent += (n))
#define  CDS_DBG_BST_FW_PROC_BST_EVENT_NUM(n)                     (g_stCdsStats.ulBstFwProcBstEvent += (n))

#define  CDS_DBG_BST_UL_SOFT_FILTER_FAIL_NUM(n)                   (g_stCdsStats.ulBstULSoftFilterFail += (n))
#define  CDS_DBG_BST_UL_SEND_PKT_TO_RAN_NUM(n)                    (g_stCdsStats.ulBstULSendToRan += (n))

#define  CDS_DBG_BST_DL_RX_BST_PKT_NUM(n)                         (g_stCdsStats.ulBstDLRxBstPkt += (n))
#define  CDS_DBG_BST_DL_RX_FUN_PARA_ERR(n)                        (g_stCdsStats.ulBstDLRxFunParaErr += (n))
#define  CDS_DBG_BST_DL_ALLOC_MEM_FAIL_NUM(n)                     (g_stCdsStats.ulBstDLAllocMemFail += (n))
#define  CDS_DBG_BST_DL_SEND_TO_NIC_SUCC_NUM(n)                   (g_stCdsStats.ulBstDLSendToNicSucc += (n))

#define  CDS_DBG_BST_FW2AP_FUN_PARA_ERR(n)                        (g_stCdsStats.ulBstFw2ApFunParaErr += (n))
#define  CDS_DBG_BST_FW2AP_QUE_FAIL_NUM(n)                        (g_stCdsStats.ulBstFw2ApEnQueFail += (n))
#define  CDS_DBG_BST_FW2AP_QUE_SUCC_NUM(n)                        (g_stCdsStats.ulBstFw2ApEnQueSucc += (n))

#define  CDS_DBG_BST_FILTER_NID_ERR_NUM(n)                        (g_stCdsStats.ulBstFilterNidErrNum += (n))
#define  CDS_DBG_BST_FILTER_RUBBISH_NUM(n)                        (g_stCdsStats.ulBstFilterRubbishNum += (n))
#define  CDS_DBG_BST_FILTER_ALLOC_MEM_FAIL_NUM(n)                 (g_stCdsStats.ulBstFilterAllocMemFail += (n))
#define  CDS_DBG_BST_FILTER_ERROR_COPY_PKT_NUM(n)                 (g_stCdsStats.ulBstFilterErrorCopyPkt += (n))
#define  CDS_DBG_BST_FILTER_WRONG_PROTOCOL_NUM(n)                 (g_stCdsStats.ulBstFilterWrongPrtcNum += (n))
#define  CDS_DBG_BST_FILTER_SUCCS_COPY_PKT_NUM(n)                 (g_stCdsStats.ulBstFilterSuccsCopyPkt += (n))
#define  CDS_DBG_BST_FILTER_SUCCS_MACH_PKT_NUM(n)                 (g_stCdsStats.ulBstFilterSuccsMachPkt += (n))
#define  CDS_DBG_BST_FILTER_NOT_IPVER4_PKT_NUM(n)                 (g_stCdsStats.ulBstFilterNotIpver4Pkt += (n))
#define  CDS_DBG_BST_FILTER_FRAGEMENTD_PKT_NUM(n)                 (g_stCdsStats.ulBstFilterFragementPkt += (n))
#endif
/*Modem CDMA下行统计量*/
#define  CDS_DBG_MODEM_DL_CDMA_RX_SDU_NUM(ModemId,enRanMode,n)                (enRanMode == APS_CDS_MODE_1X?(g_stCdsStats.astModemStats[ModemId].ulDL1xRxSduNum += (n)):(g_stCdsStats.astModemStats[ModemId].ulDLHRPDRxSduNum += (n)))
#define  CDS_DBG_MODEM_DL_CDMA_FC_FREE_SDU_NUM(ModemId,enRanMode,n)           (enRanMode == APS_CDS_MODE_1X?(g_stCdsStats.astModemStats[ModemId].ulDL1xFcFreeSduNum += (n)):(g_stCdsStats.astModemStats[ModemId].ulDLHRPDFcFreeSduNum += (n)))
#define  CDS_DBG_MODEM_DL_CDMA_DIRECT_FREE_SDU_NUM(ModemId,enRanMode,n)       (enRanMode == APS_CDS_MODE_1X?(g_stCdsStats.astModemStats[ModemId].ulDL1xDirectFreeSduNum += (n)):(g_stCdsStats.astModemStats[ModemId].ulDLHRPDDirectFreeSduNum += (n)))
#define  CDS_DBG_MODEM_DL_CDMA_ENQUE_SUCC_NUM(ModemId,enRanMode,n)            (enRanMode == APS_CDS_MODE_1X?(g_stCdsStats.astModemStats[ModemId].ulDL1xEnQueSucc += (n)):(g_stCdsStats.astModemStats[ModemId].ulDLHRPDEnQueSucc += (n)))
#define  CDS_DBG_MODEM_DL_CDMA_ENQUE_FAIL_NUM(ModemId,enRanMode,n)            (enRanMode == APS_CDS_MODE_1X?(g_stCdsStats.astModemStats[ModemId].ulDL1xEnQueFail += (n)):(g_stCdsStats.astModemStats[ModemId].ulDLHRPDEnQueFail += (n)))

#define  CDS_DBG_MODEM_DL_1X_RX_SDU_NUM(ModemId,n)                (g_stCdsStats.astModemStats[ModemId].ulDL1xRxSduNum += (n))
#define  CDS_DBG_MODEM_DL_1X_FC_FREE_SDU_NUM(ModemId,n)           (g_stCdsStats.astModemStats[ModemId].ulDL1xFcFreeSduNum += (n))
#define  CDS_DBG_MODEM_DL_1X_DIRECT_FREE_SDU_NUM(ModemId,n)       (g_stCdsStats.astModemStats[ModemId].ulDL1xDirectFreeSduNum += (n))
#define  CDS_DBG_MODEM_DL_1X_ENQUE_SUCC_NUM(ModemId,n)            (g_stCdsStats.astModemStats[ModemId].ulDL1xEnQueSucc += (n))
#define  CDS_DBG_MODEM_DL_1X_ENQUE_FAIL_NUM(ModemId,n)            (g_stCdsStats.astModemStats[ModemId].ulDL1xEnQueFail += (n))

#define  CDS_DBG_MODEM_DL_HRPD_RX_SDU_NUM(ModemId,n)              (g_stCdsStats.astModemStats[ModemId].ulDLHRPDRxSduNum += (n))
#define  CDS_DBG_MODEM_DL_HRPD_FC_FREE_SDU_NUM(ModemId,n)         (g_stCdsStats.astModemStats[ModemId].ulDLHRPDFcFreeSduNum += (n))
#define  CDS_DBG_MODEM_DL_HRPD_DIRECT_FREE_SDU_NUM(ModemId,n)     (g_stCdsStats.astModemStats[ModemId].ulDLHRPDDirectFreeSduNum += (n))
#define  CDS_DBG_MODEM_DL_HRPD_ENQUE_SUCC_NUM(ModemId,n)          (g_stCdsStats.astModemStats[ModemId].ulDLHRPDEnQueSucc += (n))
#define  CDS_DBG_MODEM_DL_HRPD_ENQUE_FAIL_NUM(ModemId,n)          (g_stCdsStats.astModemStats[ModemId].ulDLHRPDEnQueFail += (n))
/*****************************************************************************
  8 函数声明
*****************************************************************************/
extern VOS_VOID Cds_LomTraceRcvUlData(VOS_VOID);
extern VOS_VOID Cds_LomTraceSendDlData(VOS_VOID);
extern VOS_VOID CDS_DLFlowAdd(VOS_UINT32  ulSduLen);
extern VOS_VOID CDS_ULFlowAdd(VOS_UINT32  ulSduLen);
VOS_VOID CDS_SetFlowDebugFlag(VOS_UINT32  ulFlowDebugFlag);
VOS_VOID CDS_SetFlowDLRptThreshold(VOS_UINT32  ulFlowDLRptThreshold);
VOS_VOID CDS_SetFlowULRptThreshold(VOS_UINT32  ulFlowULRptThreshold);

/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif

