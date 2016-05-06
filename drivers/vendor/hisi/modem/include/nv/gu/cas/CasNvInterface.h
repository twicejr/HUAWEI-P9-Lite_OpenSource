/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CasNvInterface.h
  版 本 号   : 初稿
  作    者   : w00287212
  生成日期   : 2015年3月24日
  最近修改   :
  功能描述   : CasNvInterface.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年3月24日
    作    者   : w00287212
    修改内容   : 创建文件

******************************************************************************/

#ifndef __CASNVINTERFACE_H__
#define __CASNVINTERFACE_H__


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "PsTypeDef.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define CAS_1X_MAX_RLP_BLOB_LEN                     (15)
#define CAS_1X_MAX_SCH_MO_NUM                       (4)                         /* MS支持的SCH上最大速率的MO个数 */
#define CAS_1X_FCH_DCCH_MAX_MO                      (3)
#define CAS_1X_MAX_SUPPORT_SCH_NUM                  (1)
#define NV_ITEM_CAS_1X_TERMINAL_INFO_SIZE           (16)
#define NV_ITEM_CAS_1X_CAPA_INFO_SIZE               (28)
#define NV_ITEM_CAS_1X_RATE_FEATURE_CAPA_INFO_SIZE  (20)
#define NV_ITEM_CAS_1X_CHANNEL_CFG_CAPA_INFO_SIZE   (52)
#define NV_ITEM_CAS_1X_MO_CAPA_SIZE                 (32)
#define NV_ITEM_CAS_1X_RC_PREF_SIZE                 (4)
#define NV_ITEM_CAS_1X_ENCRYPT_CAPA_SIZE            (4)
#define NV_ITEM_CAS_1X_CELL_THRESHOLD_SIZE          (16)
#define NV_ITEM_CAS_1X_IMSI_TYPE_INFO_SIZE          (4)
#define NV_ITEM_CAS_1X_PROTOCOL_OPTIMIZE_SIZE       (8)
#define NV_ITEM_CPORC_1X_FILTER_COEF_SIZE           (36)        /* 对应NV_ITEM_CPROC_1X_FILTER_COEF */
#define NV_ITEM_CPROC_1X_OPTIMIZE_SWITCH_SIZE       (24)
#define NV_Item_CPROC_1X_NVIM_SM_MPS_THRESHOLD_SIZE (32)
#define NV_ITEM_CPORC_1X_TAS_PARA_SIZE              (40)        /* 对应CPROC_1X_NVIM_TAS_CTRL_STRU */


#define NV_ITEM_CAS_HRPD_AT_REV_SIZE                    (4)
#define NV_ITEM_CDMA_SUPPORT_BANDCLASS_MASK_SIZE        (4)
#define NV_ITEM_CAS_HRPD_CELL_THRESHOLD_SIZE            (4)
#define NV_ITEM_CAS_HRPD_SUSPEND_TIMER_SIZE             (4)
#define NV_ITEM_CAS_HRPD_CONNCLOSE_TO_1X_SWITCH_SIZE    (4)
#define NV_ITEM_CAS_HRPD_C2L_PARA_SIZE                  (8)
#define NV_ITEM_CAS_HRPD_IDLE_HO_PARA_SIZE              (8)
#define NV_ITEM_CAS_HRPD_CFG_PARA_SIZE                  (8)
#define NV_ITEM_CAS_HRPD_TIMER_SIZE                     (16)
#define NV_ITEM_CAS_HRPD_SESSION_CFG_DATA_VALUE_SIZE    (1950)  /* NV中实体大小 */
#define NV_ITEM_CAS_HRPD_SESSION_CFG_DATA_PART1_SIZE    (1972)  /* 第一块NV结构体总大小 */
#define NV_ITEM_CAS_HRPD_SESSION_CFG_DATA_PART2_SIZE    (1964)  /* 第二块NV结构体总大小 */

#define NV_ITEM_CAS_HRPD_SWITCH_PARA_SIZE               (8)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/

/** ****************************************************************************
 * Name        : CAS_1X_FCH_FRAME_SIZE_ENUM_UINT16
 *
 * Description :
 *******************************************************************************/
enum CAS_1X_FCH_FRAME_SIZE_ENUM
{
    CAS_1X_FCH_FRAME_SIZE_20MS        = 0x0000,
    CAS_1X_FCH_FRAME_SIZE_5MS_20MS    = 0x0001,
    CAS_1X_FCH_FRAME_SIZE_BUTT        = 0x0002
};
typedef VOS_UINT16 CAS_1X_FCH_FRAME_SIZE_ENUM_UINT16;

/** ****************************************************************************
 * Name        : CAS_1X_DCCH_FRAME_SIZE_ENUM_UINT16
 *
 * Description :
 *******************************************************************************/
enum CAS_1X_DCCH_FRAME_SIZE_ENUM
{
    CAS_1X_DCCH_FRAME_SIZE_20MS       = 0x0001,
    CAS_1X_DCCH_FRAME_SIZE_5MS        = 0x0002,
    CAS_1X_DCCH_FRAME_SIZE_5MS_20MS   = 0x0003,
    CAS_1X_DCCH_FRAME_SIZE_BUTT       = 0x0004
};
typedef VOS_UINT16 CAS_1X_DCCH_FRAME_SIZE_ENUM_UINT16;

/*****************************************************************************
 枚举名    :CPROC_1X_NVIM_TAS_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :0表示不支持TAS，1表示支持TAS
*****************************************************************************/
enum CPROC_1X_NVIM_TAS_ENUM
{
    CPROC_1X_NVIM_TAS_DISABLE                = 0,                                /* 不支持TAS */                                                           /* 上行仅存在DPCH */
    CPROC_1X_NVIM_TAS_ENABLE                 = 1,                                /* 支持TAS */                                                             /* 上行存在RACH */
    CPROC_1X_NVIM_TAS_BUTT
};
typedef VOS_UINT16 CPROC_1X_NVIM_TAS_ENUM_UINT16;

/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/


/*****************************************************************************
 结构名    : CAS_1X_MEID_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MEID一共56个bit
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMeidLow;                              /* Low 32 bit of MEID */
    VOS_UINT32                          ulMeidHigh;                             /* High 24 bit of MEID */
}CAS_1X_MEID_STRU;

/*****************************************************************************
 结构名    : CAS_1X_TERMINAL_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 手机规格信息 , not handle it now
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserve[12];                         /* ESN 和 MEID 的结构挪到外层结构 */

    VOS_UINT8                           ucMobMfgCode;                           /* Manufacturer code */
    VOS_UINT8                           ucMobModel;                             /* Model number */
    VOS_UINT16                          usMobFirmRev;                           /* Firmware revision number */
} CAS_1X_NVIM_TERMINAL_INFO_STRU;                                        /* modify as CAS_1X_NVIM_TERMINAL_INFO_STRU */

/*****************************************************************************
 结构名    : CAS_1X_NVIM_CELL_THRESHOLD_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 门限相关信息结构
*****************************************************************************/
typedef struct
{
    VOS_INT16                           sPilotSrchRssiThreshold;                /* PILOT搜索过程中使用非优选频点的RSSI的最低门限 */
    VOS_INT16                           sPrefChanPilotSrchRssiThreshold;        /* PILOT搜索过程中使用优选频点的RSSI的最低门限 */
    VOS_INT8                            cNbrSetStrengthOffset;                  /* 公式中的邻区截距 */
    VOS_INT8                            cRemainSetStrengthOffset;               /* 公式中的剩余集截距 */
    VOS_INT16                           sDiffStrengthK;                         /* 公式中的线性系数 */
    VOS_INT8                            cDropThresh;                            /* 掉网导频门限 单位:db 默认值为:-14db  */
    VOS_UINT8                           ucIdleHoMinThresh;                      /* idle态切换最低门限, 剩余集小区是邻区的2倍，此处配置为邻区门限 单位:1/8dB 默认值为:8 */
    VOS_UINT16                          ulTCandCellLen;                         /* 切换列表元素的定时器时长 单位:ms 默认值为1000 */
    VOS_UINT8                           ucWeakThreshold;                        /* 邻区信号变差的容忍门限，单位: 次，默认值为1次 */
    VOS_UINT8                           aucReserve[3];
} CAS_1X_NVIM_CELL_THRESHOLD_STRU;

/*****************************************************************************
 结构名    : CAS_1X_ENCRYPT_CAPA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 手机加密能力信息
*****************************************************************************/
typedef struct
{
    /* wanglingping:add ucEncryptAlgSupport to this struct */
    VOS_UINT8                           ucEncryptAlgSupport;                    /* Encryption algorithms supported */
    VOS_UINT8                           ucSigEncryptSpt;                        /* Signaling Encryption supported indicator */
    VOS_UINT8                           ucUiEncryptSpt;                         /* User information Encryption supported indicator */
    VOS_UINT8                           aucReserve[1];
} CAS_1X_NVIM_ENCRYPT_CAPA_STRU;

/*****************************************************************************
 结构名    : CAS_1X_FCH_CFG_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : FCH信道能力
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enFchSupport;                           /* Fundamental Channel supported indicator */
    VOS_UINT8                           ucReserve;
    CAS_1X_FCH_FRAME_SIZE_ENUM_UINT16   enFchFrameSize;                         /* Fundamental Channel Frame Size capability indicator */
    VOS_UINT16                          usFwdFchRc;                             /* Fwd Rc,UE支持的所有下行RC,也是FCH信道支持的下行RC */
    VOS_UINT16                          usRevFchRc;                             /* Rev Rc UE支持的所有上行RC,也是FCH信道支持的上行RC */
} CAS_1X_FCH_CFG_INFO_STRU;

/*****************************************************************************
 结构名    : CAS_1X_DCCH_CFG_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DCCH信道能力
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                      enDcchSupport;                      /* Dedicated Control Channel supported indicator */
    VOS_UINT8                               ucReserve;
    CAS_1X_DCCH_FRAME_SIZE_ENUM_UINT16      enDcchFrameSize;                    /* Dedicated Control Channel Frame Size capability */
    VOS_UINT16                              usDcchFwdRc;                        /* DCCH支持的下行RC */
    VOS_UINT16                              usDcchRevRc;                        /* DCCH支持的上行RC */
} CAS_1X_DCCH_CFG_INFO_STRU;

/*****************************************************************************
 结构名    : CAS_1X_SCH_REC_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :  SCH配置能力信息
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enTurboSpt;                             /* Turbo Coding supported indicator */
    VOS_UINT8                           ucMaxTurboBlockSize;                    /* maximum Turbo Coding block size */
    PS_BOOL_ENUM_UINT8                  enConvSpt;                              /* Convolutional Coding supported indicator */
    VOS_UINT8                           ucMaxConvBlockSize;                     /* maximum Convolutional Coding block size */
    PS_BOOL_ENUM_UINT8                  enFrame40Spt;                           /* 40ms frame indicator */
    PS_BOOL_ENUM_UINT8                  enFrame80Spt;                           /* 80ms frame indicator */
    VOS_UINT8                           ucMaxRate;                              /* Maximum forward supplemental channels rate */
    VOS_UINT8                           ucReserve;
} CAS_1X_SCH_REC_INFO_STRU;

/*****************************************************************************
 结构名    : CAS_1X_SCH_CFG_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : SCH信道能力
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enForSchSupport;                                /* Forward Supplemental Channel supported indicator */
    VOS_UINT8                           ucReserve1;
    VOS_UINT16                          usForSchRcMap;                                  /* Forward Supplemental Channel Radio Configuration capability */
    VOS_UINT8                           ucForSchNum;                                    /* Number of Forward Supplemental Channels */
    VOS_UINT8                           aucReserve2[3];
    CAS_1X_SCH_REC_INFO_STRU            astForSchRecInfo[CAS_1X_MAX_SUPPORT_SCH_NUM];   /* 下行SCH REC INFO */

    PS_BOOL_ENUM_UINT8                  enRevSchSupport;                                /* Reverse Supplemental Channel supported indicator */
    VOS_UINT8                           ucReserve3;
    VOS_UINT16                          usRevSchRcMap;                                  /* Reverse Supplemental Channel Radio Configuration capability */
    VOS_UINT8                           ucRevSchNum;                                    /* Number of Reverse Supplemental Channels */
    VOS_UINT8                           aucReserve4[3];
    CAS_1X_SCH_REC_INFO_STRU            astRevSchRecInfo[CAS_1X_MAX_SUPPORT_SCH_NUM];   /* 上行SCH REC INFO */
} CAS_1X_SCH_CFG_INFO_STRU;

/*****************************************************************************
 结构名    : CAS_1X_NVIM_CHANNEL_CFG_CAPA_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :  信道支持的能力 add a nv id
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enOtdSupport;                           /* OTD supported indcator */
    PS_BOOL_ENUM_UINT8                  enStsSupport;                           /* STS supported indicator */
    PS_BOOL_ENUM_UINT8                  en3XCchSupport;                         /* 3X Common Channel supported */
    VOS_UINT8                           ucReserve;
    CAS_1X_FCH_CFG_INFO_STRU            stFchCfgInfo;                           /* fch 配置信息 */
    CAS_1X_DCCH_CFG_INFO_STRU           stDcchCfgInfo;                          /* dcch 配置信息 */
    CAS_1X_SCH_CFG_INFO_STRU            stSchCfgInfo;                           /* sch 配置信息 */
} CAS_1X_NVIM_CHANNEL_CFG_CAPA_INFO_STRU;

/*****************************************************************************
 结构名    : CAS_1X_FLEX_SPT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :  flex支持能力
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enFlexSupport;                          /* Flexible rate feature supported indicator */
    PS_BOOL_ENUM_UINT8                  enFFchFlexSpt;                          /* Forward Fundamental channel flexible rate feature supported indicator */
    PS_BOOL_ENUM_UINT8                  enRFchFlexSpt;                          /* Reverse Fundamental channel flexible rate feature supported indicator */
    PS_BOOL_ENUM_UINT8                  enFDcchFlexSpt;                         /* Forward Dedicated Control channel flexible rate feature supported indicator */
    PS_BOOL_ENUM_UINT8                  enRDcchFlexSpt;                         /* Reverse Dedicated Control channel flexible rate feature supported indicator */
    PS_BOOL_ENUM_UINT8                  enFSchFlexSpt;                          /* Forward Supplemental channel flexible rate feature supported indicator */
    PS_BOOL_ENUM_UINT8                  enRSchFlexSpt;                          /* Reverse Supplemental channel flexible rate feature supported indicator */
    VOS_UINT8                           ucReserve;
} CAS_1X_FLEX_SPT_INFO_STRU;

/*****************************************************************************
 结构名    : CAS_1X_VAR_SPT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : variable rate feature支持能力
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enVarSupport;                           /* Variable rate feature supported indicator */
    PS_BOOL_ENUM_UINT8                  enFSchVarSpt;                           /* Forward Supplemental Channel Variable Rate supported indicator */
    PS_BOOL_ENUM_UINT8                  enRSchVarSpt;                           /* Reverse Supplemental Channel Variable Rate supported indicator */
    VOS_UINT8                           ucReserve;
    VOS_UINT16                          usMaxSumNumBitsC;                       /* Maximum sum of number of bits corresponding to Convolutional rates in the variable rate set */
    VOS_UINT16                          usMaxSumNumBitsT;                       /* Maximum sum of number of bits corresponding to Turbo Code rates in the variable rate set */
} CAS_1X_VAR_SPT_INFO_STRU;

/*****************************************************************************
 结构名    : CAS_1X_NVIM_CAPA_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :  capability infomation
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMobPRev;                              /* MOB_P_REV: UE支持的协议版本 */
    PS_BOOL_ENUM_UINT8                  enPacketDataServSupp;                   /* MS supports packet data service */
    PS_BOOL_ENUM_UINT8                  enDeviceInfoMsgSupp;                    /* MS supports the  Device Information Message on the r-csch */
    VOS_UINT8                           ucReserve;
    PS_BOOL_ENUM_UINT8                  enSyncIdReportCapa;                     /* 标识MS是否支持上报SYNC ID */

    PS_BOOL_ENUM_UINT8                  enAccessEntryHo;                        /* Access Entry Handoff Support */
    PS_BOOL_ENUM_UINT8                  enAccessProbeHo;                        /* Access Probe Handoff Support */
    PS_BOOL_ENUM_UINT8                  enAnalogSearch;                         /* Analog Search Support */
    PS_BOOL_ENUM_UINT8                  enHoppingBeacon;                        /* Hopping Beacon Support */
    PS_BOOL_ENUM_UINT8                  enMahHo;                                /* Mobile Assisted Hard Handoff Support */
    PS_BOOL_ENUM_UINT8                  enPuf;                                  /* Location Power Up Function Support */
    PS_BOOL_ENUM_UINT8                  enAnalog553A;                           /* Analog Support */
    PS_BOOL_ENUM_UINT8                  enQpchSupport;                          /* QPCH是否支持的标记 */
    PS_BOOL_ENUM_UINT8                  enBroadCastSupport;                     /* BC是否支持的标记 */

    PS_BOOL_ENUM_UINT8                  enSlottedClass;                         /* Slotted Class, scm第5位 */
    PS_BOOL_ENUM_UINT8                  enSlottedTimer;                         /* Slotted Timer Support */
    PS_BOOL_ENUM_UINT8                  enChsSupport;                           /* Control Hold Mode supported indicator */
    VOS_UINT8                           ucGatingRateSet;                        /* Set of supported Reverse Pilot gating rates */
    PS_BOOL_ENUM_UINT8                  enExtCapIncluded;                       /* Extended Capabilities Included indicator */
    PS_BOOL_ENUM_UINT8                  enMabo;                                 /* Mobile Assisted Burst Operation capability indicator */
    PS_BOOL_ENUM_UINT8                  enSdb;                                  /* Short Data Burst supported indicator */

    VOS_UINT8                           ucCdmaSptOpMode;                        /* UE支持的操作模式 */
    VOS_UINT8                           ucMinPwrCntlStep;                       /* Minimum power control step size */
    PS_BOOL_ENUM_UINT8                  enRevFchGating;                         /* REV_FCH_GATING_REQ */
    VOS_UINT8                           ucGeoLoc;                               /* Geo-location */

    PS_BOOL_ENUM_UINT8                  enTransMode;                            /* Transmission, scm第2位  */
    PS_BOOL_ENUM_UINT8                  enSupportMeid;                          /* Meid support, scm第4位 */
    PS_BOOL_ENUM_UINT8                  enDualmode;                             /* Dual mode, scm第6位 */
} CAS_1X_NVIM_CAPA_INFO_STRU;

/*****************************************************************************
 结构名    : CAS_1X_NVIM_RATE_FEATURE_CAPA_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :  rate feature capability infomation
*****************************************************************************/
typedef struct
{
    CAS_1X_FLEX_SPT_INFO_STRU           stFlexSptInfo;                          /* flex info 支持能力 */
    CAS_1X_VAR_SPT_INFO_STRU            stVarSptInfo;                           /* VAR支持能力 */
    PS_BOOL_ENUM_UINT8                  enCsSupport;                            /* Concurrent Services supported indicator */
    PS_BOOL_ENUM_UINT8                  enFSchLtuTabSpt;                        /* Forward Supplemental Channel Downloadable LTU tables supported indicator */
    PS_BOOL_ENUM_UINT8                  enRSchLtuTabSpt;                        /* Reverse Supplemental Channel Downloadable LTU tables supported indicator */
    VOS_UINT8                           aucReserve2[1];
} CAS_1X_NVIM_RATE_FEATURE_CAPA_INFO_STRU;

/*****************************************************************************
 结构名    : CAS_1X_SCH_MO_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :  SCH支持的MO
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          ausMoForSch[CAS_1X_MAX_SCH_MO_NUM];
    VOS_UINT16                          ausMoRevSch[CAS_1X_MAX_SCH_MO_NUM];
} CAS_1X_SCH_MO_INFO_STRU;

/*****************************************************************************
 结构名    : CAS_1X_FCH_DCCH_MO_LIST_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : FCH DCCH MO能力
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usMoNum;
    VOS_UINT16                          ausMoList[CAS_1X_FCH_DCCH_MAX_MO];
} CAS_1X_FCH_DCCH_MO_LIST_STRU;

/*****************************************************************************
 结构名    : CAS_1X_NVIM_MO_CAPA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MO能力
*****************************************************************************/
typedef struct
{
    CAS_1X_FCH_DCCH_MO_LIST_STRU        stFwdMo;                                /* Fwd Mo,FCH和DCCH支持的下行MO */
    CAS_1X_FCH_DCCH_MO_LIST_STRU        stRevMo;                                /* Rev Mo,FCH和DCCH支持的上行MO */
    CAS_1X_SCH_MO_INFO_STRU             stSchMoInfo;                            /* sch上支持的MO */
}CAS_1X_NVIM_MO_CAPA_STRU;

/*****************************************************************************
 结构名    : CAS_1X_NVIM_RC_PREF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RC PREF能力
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucForRcPref;                            /* FOR_RC_PREF */
    VOS_UINT8                           ucRevRcPref;                            /* REV_RC_PREF */
    VOS_UINT8                           aucReserve[2];
}CAS_1X_NVIM_RC_PREF_STRU;

/*****************************************************************************
 结构名    : CAS_1X_NVIM_IMSI_TYPE_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : Imsi_T programmed标志 3508
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enProgrammedImsiT;                      /* IMSI_T programmed or not*/
    VOS_UINT8                           aucReserve[3];
}CAS_1X_NVIM_IMSI_TYPE_INFO_STRU;

/*****************************************************************************
 结构名    : CAS_1X_NVIM_PROTOCOL_OPTIMIZE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 协议优化选项 3509
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enSaveSystemInfo;                       /* 是否缓存系统消息，默认值为TRUE, 默认缓存 */
    VOS_UINT8                           ucTaddDelta;                            /* Tadd增量系数 单位:0.5db 默认值为0 */
    VOS_UINT8                           ucTdropDelta;                           /* Tdrop增量系数 单位:0.5db 默认值为0 */
    VOS_UINT8                           ucTSysReselLen;                         /* 系统重选延时定时器时长 单位: s 默认值为16, 0表示不使用延时定时器 */
    VOS_UINT16                          usRschApplyTime;                        /* 提前申请RSCH时间，默认为400ms */
    VOS_UINT16                          usTOhmMsgRcvLen;                        /* 当前服务小区系统消息接收的定时器时长 单位:s 默认值为600 */
}CAS_1X_NVIM_PROTOCOL_OPTIMIZE_STRU;

/*****************************************************************************
 结构名    : CPROC_1X_NVIM_FILTER_COEF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CPROC 滤波系数,CAS 维护
*****************************************************************************/
typedef struct
{
    /* SF continuous */
    VOS_UINT16                          usSfContMpsAlphaEc;
    VOS_UINT16                          usSfContMpsAlphaEcIo;

    VOS_UINT16                          usSfContMeasAlphaEc;
    VOS_UINT16                          usSfContMeasAlphaEcIo;

    /* CF TCH */
    VOS_UINT16                          usCfContTchAlphaEc;
    VOS_UINT16                          usCfContTchAlphaEcIo;

    /* SF DRX */
    VOS_UINT16                          usSfDrxMpsOsAlphaEc;
    VOS_UINT16                          usSfDrxMpsOsAlphaEcIo;

    VOS_UINT16                          usSfDrxMpsContAlphaEc;
    VOS_UINT16                          usSfDrxMpsContAlphaEcIo;

    VOS_UINT16                          usSfDrxMeasAlphaEc;
    VOS_UINT16                          usSfDrxMeasAlphaEcIo;

    /* CF DRX */
    VOS_UINT16                          usCfDrxMeasAlphaEc;
    VOS_UINT16                          usCfDrxMeasAlphaEcIo;

    /* ilde continuous(reserve) */
    VOS_UINT16                          usSfContIdleMpsAlphaEc;
    VOS_UINT16                          usSfContIdleMpsAlphaEcIo;

    VOS_UINT16                          usSfContIdleMeasAlphaEc;
    VOS_UINT16                          usSfContIdleMeasAlphaEcIo;

}CPROC_1X_NVIM_FILTER_COEF_STRU;

/*****************************************************************************
 结构名    : CPROC_1X_NVIM_PILOT_SEARCH_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : Pilot search 参数
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwVaildPilotThres;                     /* 搜网阶段判断导频是否有效的门限。根据导频MPS测量的ECNO进行判断，如果导频ECNO大于此门限，
                                                                                   认为该导频有效，在该导频下解SYNC，如果低于此门限，根据2轮MPS的平均值判断导频是否有效 */
    VOS_INT16                           shwVaildPilotAverageThres;              /* 搜网阶段导频平均ECNO的判断门限。如果导频的单次MPS ECNO不超过有效门限，对导频进行MPS 多轮，
                                                                                   如果导频的平均ECNO 大于此门限，认为导频有效，否则认为此导频无效                     */
    VOS_UINT16                          uhwMaxPNNumDoMps;                       /* 搜网阶段MPS测量的相位个数。MPS测量的相位个数取此值和PILOT SEARCH IND上报的PNPhase Num 中的较小值 */
    VOS_UINT16                          uhwMaxMpsLoopsTime;                     /* 搜网阶段MPS测量的轮数。如果所有相位单次MPS测量ECNO不超过有效门限，则对所有相位测量该值定义的轮数 */
    VOS_UINT16                          uhwMaxPSTimeIfNoPnPhaseNum;             /* 单频点PILOT SEARCH 最大次数。*/
    VOS_UINT16                          usReserve1;
}CPROC_1X_NVIM_PILOT_SEARCH_PARA_STRU;

/*****************************************************************************
 结构名    : CPROC_1X_NVIM_OPTIMIZE_SWITCH_STRU
 协议表格  : C.S0005 Table D-2.
 ASN.1描述 :
 结构说明  : CPROC 1X 优化开关, 3511
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucN2mHuaweiConfigValue;                /*N2m自定义配置值*/
    VOS_UINT8                               ucN3mHuaweiConfigValue;                /*N3m自定义配置值*/
    CPROC_1X_NVIM_PILOT_SEARCH_PARA_STRU    stPsPara;
    VOS_UINT8                               aucReserved[10];
}CPROC_1X_NVIM_OPTIMIZE_SWITCH_STRU;
/*****************************************************************************
 结构名    : CPROC_1X_MPS_REF_PN_THRESHOLD_STRU；
 协议表格  :
 ASN.1描述 :
 结构说明  : Threshold for refrence PN change.
*****************************************************************************/
typedef struct
{
    VOS_INT16                           sRemoveOldRefPNThreshold;   /* Threshold for changing to a new reference */
    VOS_UINT16                          usNewRefPNThreshold;        /* Threshold above reference EcNo before changing reference */
    VOS_UINT16                          usNewRefPNCount;            /* Number of times above threshold berfore changing reference */
    VOS_UINT16                          usReserved;
}CPROC_1X_MPS_REF_PN_THRESHOLD_STRU;

/*****************************************************************************
 结构名    : CPROC_1X_NVIM_SM_MPS_THRESHOLD_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : Threshold for mps.
*****************************************************************************/
typedef struct
{
    CPROC_1X_MPS_REF_PN_THRESHOLD_STRU  stCproc1xMpsRefPNThreshold; /* Threshold for refrence PN change. */
    VOS_UINT16                              usReserved[12];
}CPROC_1X_NVIM_SM_MPS_THRESHOLD_STRU;

/*****************************************************************************
 结构名    : CPROC_1X_NVIM_TAS_SEARCHING_STATE_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 1X TAS物理层搜网流程所需门限值
*****************************************************************************/
typedef struct
{
    VOS_INT16                               shwGoodRssiThres;                   /* 属于好信号RSSI门限值(单位为0.125dbm) */
    VOS_UINT16                              usReserve1;
}CPROC_1X_NVIM_TAS_SEARCHING_STATE_PARA_STRU;

/*****************************************************************************
 结构名    : CPROC_1X_NVIM_TAS_PHY_STATE_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 1X TAS物理层状态上报所需门限值，
             联调X模专用，后续考虑复用，对用户的nv个数越少越好
*****************************************************************************/
typedef struct
{
    VOS_INT16                               shwGoodRscpThres;                   /* 属于好信号RSCP门限值(单位为0.125dbm)，复用GU */
    VOS_INT16                               shwPoorRscpThres;                   /* 属于差信号RSCP门限值(单位为0.125dbm)，复用GU */
    VOS_INT16                               shwGoodEcIoThres;                   /* 属于好信号EcIo门限值(单位为0.125db)，X模专用 */
    VOS_INT16                               shwPoorEcIoThres;                   /* 属于差信号EcIo门限值(单位为0.125db)，X模专用，后续考虑复用，对用户的nv个数越少越好 */
    VOS_UINT16                              uhwSFailNum;                        /* S准则连续失败次数，复用GU */
    VOS_UINT16                              uhwSPassNum;                        /* S准则连续成功次数，复用GU */
}CPROC_1X_NVIM_TAS_PHY_STATE_PARA_STRU;

/*****************************************************************************
 结构名    : CPROC_1X_NVIM_TAS_BLIND_MEAS_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TAS盲切测量的控制参量，
             联调X模专用，后续考虑复用，对用户的nv个数越少越好
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwStateOneTime;                    /* 阶段一比较时间 */
    VOS_INT16                               shwWorstRscpValue;                  /* 最差RSCP信号门限值 */
    VOS_INT16                               shwWorseRscpValue;                  /* 较差RSCP信号门限值 */
    VOS_UINT16                              uhwDeltaRscpValue;                  /* 手握导致信号强度下降判决门限 */
    VOS_UINT16                              uhwStateTwoTime;                    /* 阶段二比较时间 */
    VOS_UINT16                              uhwDeltaRscpValuetest;              /* 保留字段 */
    VOS_UINT16                              auhwFrozenTime[4];                  /* 天线切换冻结保护时间, Ta Tb Tc Td */
}CPROC_1X_NVIM_TAS_BLIND_MEAS_STRU;



/*****************************************************************************
 结构名    : CPROC_1X_NVIM_TAS_CTRL_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 1x TAS算法控制参量
*****************************************************************************/
typedef struct
{
    CPROC_1X_NVIM_TAS_ENUM_UINT16               enCproc1xTasSupprot;                /* 是否支持TAS，BBIT之后与GU复用 */
    VOS_UINT16                                  uwReserve;
    CPROC_1X_NVIM_TAS_SEARCHING_STATE_PARA_STRU stTasSearchingStatePara;            /* TAS搜网相关的控制参量 */
    CPROC_1X_NVIM_TAS_PHY_STATE_PARA_STRU       stTasPhyStatePara;                  /* 物理层状态上报参数门限 */
    CPROC_1X_NVIM_TAS_BLIND_MEAS_STRU           stTasBlindCtrl;                     /* TAS盲切测量的控制参量 */
}CPROC_1X_NVIM_TAS_CTRL_STRU;


/*****************************************************************************
 结构名    : CAS_HRPD_NVIM_REV_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : EVDO终端版本信息 3600
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enSuppOnlyDo0;                          /* 是否只支持DO0版本 */
    PS_BOOL_ENUM_UINT8                  enSuppDoaWithMfpa;                      /* 是否支持DOA版本，应用类型只支持MFPA */
    PS_BOOL_ENUM_UINT8                  enSuppDoaWithEmfpa;                     /* 是否支持DOA版本，应用类型支持MFPA和EMPA */
    PS_BOOL_ENUM_UINT8                  enSuppDoaEhrpd;                         /* 是否支持eHRPD */
}CAS_HRPD_NVIM_REV_INFO_STRU;

/*****************************************************************************
 结构名    : CAS_CDMA_NVIM_SUPPORT_BANDCLASS_MASK_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 终端支持的频段能力掩码  3601
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulSupportBandclassMask;               /* 终端支持的频段能力掩码，每bit表示是否支持对应的频段能力，比如0x00000001表示只支持频段0 */
}CAS_CDMA_NVIM_SUPPORT_BANDCLASS_MASK_STRU;

/*****************************************************************************
 结构名    : CAS_HRPD_NVIM_CELL_THRESHOLD_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 搜网门限相关信息结构  3602
*****************************************************************************/
typedef struct
{
    VOS_INT16                           sPilotSrchRssiThreshold;              /* Pilot Srch Rssi Threshold */
    VOS_UINT8                           aucReserve[2];
}CAS_HRPD_NVIM_CELL_THRESHOLD_STRU;

/*****************************************************************************
 结构名    : CAS_HRPD_NVIM_SUSPEND_TIMER_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 挂起定时器时长 3603
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usConnSuspendTimerLength;             /* AT进入挂起模式时，挂起定时器的时长，单位为ms */
    VOS_UINT8                           aucReserve[2];
}CAS_HRPD_NVIM_SUSPEND_TIMER_STRU;

/*****************************************************************************
 结构名    : CAS_HRPD_NVIM_CONNCLOSE_TO_1X_SWITCH_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DO到1x切换开关    3604
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enDO21XSwitch;                        /* 当HRPD连接态能量值低于sStrengthThresholdTo1x时，是否断开HRPD连接 */
    VOS_UINT8                           ucReserve;
    VOS_INT16                           sStrengthThresholdTo1x;               /* 连接态时激活集能量值监控门限，低于该门限，EVDO主动发起连接关闭，切换到1x */
}CAS_HRPD_NVIM_CONNCLOSE_TO_1X_SWITCH_STRU;



/*****************************************************************************
 结构名    : CAS_HRPD_C2L_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HRPD到LTE重选相关的参数  3605
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulLteReselectTimerLen;                /* EVDO到LTE的重选时间 */
    VOS_INT16                           sHrpdQualityThreshold;                /* Hrpd Quality Threshold value, CL互操作使用，DO能建立业务信道的门限 */
    PS_BOOL_ENUM_UINT8                  enSortEUTRAFreqByOhmOrder;            /* 是否根据otherRatNeighbor list消息中的频点顺序，对要重选的频点进行排序 */
    VOS_UINT8                           ucReserve;
}CAS_HRPD_NVIM_C2L_STRU;

/*****************************************************************************
 结构名    : CAS_HRPD_NVIM_IDLE_HO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HRPD版本信息   3606
*****************************************************************************/
typedef struct
{
    VOS_INT8                            cIdleHoOffset;                          /* idle ho 参数f */
    VOS_INT8                            cIdleHoStrengthK;                       /* idle ho 参数k */
    VOS_INT8                            cIdleHoThresh;                          /* idle ho 参数y */
    VOS_UINT8                           ucReserve;
    VOS_UINT16                          usTimeLength;                           /* 监控时常,单位ms */
    VOS_INT8                            cIdleHoActSetThresh;                    /* idle ho激活集门限 */
    VOS_INT8                            cIdleHoCndSetThresh;                    /* idle ho候选集门限 */
}CAS_HRPD_NVIM_IDLE_HO_STRU;

/*****************************************************************************
 结构名    : CAS_HRPD_NVIM_CFG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HRPD配置协商相关参数  3607
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulHscpAnPhaseTimerLength;             /* 配置协商AT协商阶段的保护定时器时长 */
    VOS_UINT8                           ucCfgMsgSendTimes;                    /* 配置协商过程中，ConfigurationRequest消息的发送次数，默认值为1 */
    VOS_UINT8                           ucKeyResponseTimeout;                 /* KeyResponse消息中的Timeout字段，单位为秒 */
    VOS_UINT8                           ucSuppItatProtocol;                   /* eAT发起初始配置协商时，是否携带Irat的协议子类型 */
    VOS_UINT8                           ucReserve;
}CAS_HRPD_NVIM_CFG_STRU;

/*****************************************************************************
 结构名    : CAS_HRPD_NVIM_TIMER_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :  HRPD Timer类NV定义
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usConnectCloseDelayTimerLength;       /* 等待ConnectionClose消息发出时长，单位为ms */
    VOS_UINT16                          usWaitRfOccupyResApplyCnfTimerLength; /* 在短抢过程中等待RF资源申请相应时长，单位:ms */
    VOS_UINT16                          usWaitCprocNoRfIndTimerLength;        /* Cproc上报NO_RF_IND后等待RF_IND时长，单位:ms */
    VOS_UINT16                          usWaitInitSrchRfResApplycnfTimerLength; /* 在搜网过程中等待RF资源申请时长，单位:ms */
    VOS_UINT16                          usReserve4;
    VOS_UINT16                          usReserve5;
    VOS_UINT16                          usReserve6;
    VOS_UINT16                          usReserve7;
}CAS_HRPD_NVIM_TIMER_STRU;

/*****************************************************************************
 结构名    : CAS_HRPD_NVIM_SESSION_CFG_DATA_PART1_STRU
 协议表格  :
 ASN.1描述 : 每块NV最大存储1.95K字节，配置协商属性比较多，
             所以用两部分NV存储配置协商属性，此结构为第一部分NV
 结构说明  : HRPD 配置协商完成后属性列表 NV定义
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enPersonalityTblListValid;              /* Personality列表是否有效 */
    PS_BOOL_ENUM_UINT8                  enPart2Valid;                           /* 第二部分NV是否存储Personality */
    VOS_UINT16                          usPersonalityNum;                       /* 当前有效Personality的套数 */
    VOS_UINT16                          usPersonalityIdx;                       /* 当前在使用的Personality的下标 */
    VOS_UINT16                          usSessionToken;
    VOS_UINT16                          usPart1Length;                          /* 第一部分有效数据长度 */
    VOS_UINT16                          usReserve1;
    VOS_UINT16                          usReserve2;
    VOS_UINT16                          usReserve3;
    VOS_UINT16                          usReserve4;
    VOS_UINT16                          usReserve5;
    VOS_UINT16                          usReserve6;
    VOS_UINT8                           aucPart1Value[NV_ITEM_CAS_HRPD_SESSION_CFG_DATA_VALUE_SIZE];  /* 数据实体 */
}CAS_HRPD_NVIM_SESSION_CFG_DATA_PART1_STRU;

/*****************************************************************************
 结构名    : CAS_HRPD_NVIM_SESSION_CFG_DATA_PART2_STRU
 协议表格  :
 ASN.1描述 : 每块NV最大存储1.95K字节，配置协商属性比较多，
             所以用两部分NV存储配置协商属性，此结构为第二部分NV
 结构说明  : HRPD 配置协商完成后属性列表 NV定义
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPart2Length;                          /* 第二部分有效数据长度 */
    VOS_UINT16                          usReserve1;
    VOS_UINT16                          usReserve2;
    VOS_UINT16                          usReserve3;
    VOS_UINT16                          usReserve4;
    VOS_UINT16                          usReserve5;
    VOS_UINT16                          usReserve6;
    VOS_UINT8                           aucPart2Value[NV_ITEM_CAS_HRPD_SESSION_CFG_DATA_VALUE_SIZE];/* 数据实体 */
}CAS_HRPD_NVIM_SESSION_CFG_DATA_PART2_STRU;


/*****************************************************************************
 结构名    : CAS_HRPD_NVIM_SWITCH_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HRPD开关参数    3611
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enInterFreqMeasThresJudgeSwitch;        /* 异频测量启动是否判断门限开关 0:表示开关关闭，此时在空闲态和连接态，只要有异频邻区都会下发测量配置测，
                                                                                   1:表示开关打开，此时在空闲态不测异频邻区，在连接态，如果候选集和相邻集中有异频邻区，并且
                                                                                   激活集和候选集中的同频频点能量值都小于-5db的门限时，才启动异频测量，否则不则异频*/
    PS_BOOL_ENUM_UINT8                  enSlotModeSwitch;                       /* 时隙模式开关，1表示开关打开 */
    PS_BOOL_ENUM_UINT8                  enScpDeactiveInitOhmSwitch;             /* SCP去激活初始化OHM开关，1表示开关打开 */
    PS_BOOL_ENUM_UINT8                  enConnOpenSndRuSwitch;                  /* 连接建立上报RU开关，1表示开关打开 */
    PS_BOOL_ENUM_UINT8                  enIdleHoFromCndAndNbrSwitch;            /* 空闲态切换从候选集和相邻集选择的开关，1表示开关打开 */
    VOS_UINT8                           ucReserve5;
    VOS_UINT8                           ucReserve6;
    VOS_UINT8                           ucReserve7;
}CAS_HRPD_NVIM_SWITCH_PARA_STRU;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/


#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of CasNvInterface.h */


