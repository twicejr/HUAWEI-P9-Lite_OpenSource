/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MtcCtx.h
  版 本 号   : 初稿
  作    者   : j00174725
  生成日期   : 2013年8月13日
  最近修改   :
  功能描述   : MtcCtx.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年8月13日
    作    者   : j00174725
    修改内容   : 创建文件

******************************************************************************/

#ifndef __MTCCTX_H__
#define __MTCCTX_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "Ps.h"

#include "MtcRrcInterface.h"
#include "MtcMmaInterface.h"
#include "TafMtcInterface.h"
#include "MtaMtcInterface.h"
#include "MtcNasInterface.h"
#include "MtcRcmInterface.h"
/* Add by j00174725 for K3V3 多模多天线特性, 2014-06-16, Begin */
#include "TafMtcApi.h"
/* Add by j00174725 for K3V3 多模多天线特性, 2014-06-16, End */
/* Added by wx270776 for OM融合, 2015-6-27, begin */
#include "TafLog.h"
#include "TafNvInterface.h"
/* Added by wx270776 for OM融合, 2015-6-27, end */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#if (VOS_WIN32 == VOS_OS_VER)
#define MTC_WARNING_LOG(string)                 vos_printf("%s \r\n", string)
#define MTC_WARNING1_LOG(string, para1)         vos_printf("%s %d.\r\n", string, para1)
#define MTC_WARNING2_LOG(string, para1, para2)  vos_printf("%s %d, %d.\r\n", string, para1, para2)

#define MTC_ERROR_LOG(string)                   vos_printf("%s \r\n", string)
#define MTC_ERROR1_LOG(string, para1)           vos_printf("%s %d.\r\n", string, para1)
#define MTC_ERROR2_LOG(string, para1, para2)    vos_printf("%s %d, %d.\r\n", string, para1, para2)
#else
#define MTC_WARNING_LOG(string)                 TAF_LOG(UEPS_PID_MTC, 0, PS_LOG_LEVEL_WARNING,  string)
#define MTC_WARNING1_LOG(string, para1)         TAF_LOG1(UEPS_PID_MTC, 0, PS_LOG_LEVEL_WARNING,  string, (VOS_INT32)para1)
#define MTC_WARNING2_LOG(string, para1, para2)  TAF_LOG2(UEPS_PID_MTC, 0, PS_LOG_LEVEL_WARNING,  string, (VOS_INT32)para1, (VOS_INT32)para2)

#define MTC_ERROR_LOG(string)                   TAF_LOG(UEPS_PID_MTC, 0, PS_LOG_LEVEL_ERROR,  string)
#define MTC_ERROR1_LOG(string, para1)           TAF_LOG1(UEPS_PID_MTC, 0, PS_LOG_LEVEL_ERROR,  string, (VOS_INT32)para1)
#define MTC_ERROR2_LOG(string, para1, para2)    TAF_LOG2(UEPS_PID_MTC, 0, PS_LOG_LEVEL_ERROR,  string, (VOS_INT32)para1, (VOS_INT32)para2)
#endif

/* 将BIT n置位 */
#define MTC_SET_BIT(n)                  ((VOS_UINT32)0x01 << n)
#define MTC_SET_BIT64(n)                ((VOS_UINT64)1 << (n))

#define MTC_INTRUSION_CFG_BIT           MTC_SET_BIT(0)                          /* NV中标识干扰控制的bit位 */

#define MTC_NOTCH_CFG_BIT               MTC_SET_BIT(1)                          /* NV中标识notch控制的bit位 */

#define MTC_RSE_CFG_BIT                 MTC_SET_BIT(4)                          /* NV中标识RSE控制的bit位 */


#define MTC_PS_AUTOMATIC_START              (0)                                 /* 值与NAS_MMA_AUTOMATIC_START保持一致 */
#define MTC_PS_MMA_MANUAL_START             (1)                                 /* 值与NAS_MMA_MANUAL_START保持一致  */

#define MTC_NARROW_BAND_DCS_CFG_BIT     MTC_SET_BIT(2)                          /* NV中标识narrow band dcs控制的bit位 */

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/* Modified by l00198894 for V9R1 Notch Bypass项目, 2013-12-21, begin */
/*****************************************************************************
 枚举名    : MTC_CFG_ENUM
 结构说明  : MTC NV 配置信息

  1.日    期   : 2013年08月13日
    作    者   : j00174725
    修改内容   : 定义MTC和RRC之间的消息
*****************************************************************************/
enum MTC_CFG_ENUM
{
    MTC_CFG_DISABLE                     = 0x00,                                 /* 配置不使能 */
    MTC_CFG_ENABLE                      = 0x01,                                 /* 配置使能 */
    MTC_CFG_BUTT
};
typedef VOS_UINT8  MTC_CFG_ENUM_UINT8;
/* Modified by l00198894 for V9R1 Notch Bypass项目, 2013-12-21, end */

/*****************************************************************************
 枚举名    : MTC_CS_SERVICE_STATE_ENUM
 枚举说明  : CS域服务状态枚举

  1.日    期   : 2013年08月12日
    作    者   : l00198894
    修改内容   : V9R1 干扰控制项目
*****************************************************************************/
enum MTC_CS_SERVICE_STATE_ENUM
{
    MTC_CS_NO_SERVICE         = 0x00,                                           /* CS域无业务 */
    MTC_CS_IN_SERVICE,                                                          /* CS域存在业务 */

    MTC_CS_SERVICE_STATE_BUTT
};
typedef VOS_UINT8 MTC_CS_SERVICE_STATE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : MTC_OPERATOR_CUST_SOLUTION_ENUM
 枚举说明  : 运营商定制方案枚举

  1.日    期   : 2014年01月17日
    作    者   : l00198894
    修改内容   : V9R1C53 C+L 离网重选项目
*****************************************************************************/
enum MTC_OPERATOR_CUST_SOLUTION_ENUM
{
    MTC_OPERATOR_CUST_NONE          = 0x00,                                     /* 无运营商定制方案 */
    MTC_OPERATOR_CUST_CMCC_SVLTE    = 0x01,                                     /* 中移动定制SVLTE特性 */
    MTC_OPERATOR_CUST_CT_LC         = 0x02,                                     /* 中国电信C+L方案 */

    MTC_OPERATOR_CUST_BUTT
};
typedef VOS_UINT8 MTC_OPERATOR_CUST_SOLUTION_ENUM_UINT8;

/*****************************************************************************
 枚举名    : MTC_PS_TRANSFER_CAUSE_ENUM
 结构说明  : MTC模块PS域切换原因值
 1.日    期   : 2013年10月21日
   作    者   : l00198894
   修改内容   : 新增枚举
 2.日    期   : 2013年11月22日
   作    者   : z00161729
   修改内容   : SVLTE优化G-TL ps切换性能修改
*****************************************************************************/
enum MTC_PS_TRANSFER_CAUSE_ENUM
{
    MTC_PS_TRANSFER_CAUSE_AREA_LOST                 = 0,

    MTC_PS_TRANSFER_CAUSE_AREA_AVALIABLE            = 1,

    MTC_PS_TRANSFER_CAUSE_BUTT
};
typedef VOS_UINT8 MTC_PS_TRANSFER_CAUSE_ENUM_UINT8;

/* Add by j00174725 for K3V3 多模多天线特性, 2014-06-16, Begin */
/*****************************************************************************
 枚举名    : MTC_OUTSIDE_MODEM_ENUM
 结构说明  : 外接MODEM ID定义
 1.日    期   : 2014年06月16日
   作    者   : j00174725
   修改内容   : K3V3 多模多天线特性
*****************************************************************************/
enum MTC_OUTSIDE_MODEM_ENUM
{
    MTC_OUTSIDE_MODEM_CDMA              = 0x0000,                              /* 外接CDMA */

    MTC_OUTSIDE_MODEM_BUTT
};
typedef VOS_UINT16 MTC_OUTSIDE_MODEM_ENUM_UINT16;
/* Add by j00174725 for K3V3 多模多天线特性, 2014-06-16, End */

/* Add by j00174725 for RF&LCD INTRUSION, 2014-03-04, GU 结构定义(由上官声长00266224提供) Begin */
/*****************************************************************************
 枚举名    : MTC_BAND_INFO_ENUM
 协议表格  :
 枚举说明  : 频段枚举
*****************************************************************************/
enum MTC_BAND_INFO_ENUM
{
    MTC_FREQ_BAND_NONE = 0,                                                     /*  没有Band */
    MTC_FREQ_BAND1 ,                                                            /*  Band1 */
    MTC_FREQ_BAND2 ,
    MTC_FREQ_BAND3 ,
    MTC_FREQ_BAND4 ,
    MTC_FREQ_BAND5 ,
    MTC_FREQ_BAND6 ,
    MTC_FREQ_BAND7 ,
    MTC_FREQ_BAND8 ,
    MTC_FREQ_BAND9 ,
    MTC_FREQ_BAND10,
    MTC_FREQ_BAND11,
    MTC_FREQ_BAND12,
    MTC_FREQ_BAND13,
    MTC_FREQ_BAND14,
    MTC_FREQ_BAND15,
    MTC_FREQ_BAND16,
    MTC_FREQ_BAND17,
    MTC_FREQ_BAND18,
    MTC_FREQ_BAND19,
    MTC_FREQ_BAND20,

    MTC_FREQ_BAND21,
    MTC_FREQ_BAND22,
    MTC_FREQ_BAND23,
    MTC_FREQ_BAND24,
    MTC_FREQ_BAND25,
    MTC_FREQ_BAND26,
    MTC_FREQ_BAND27,
    MTC_FREQ_BAND28,
    MTC_FREQ_BAND29,
    MTC_FREQ_BAND30,
    MTC_FREQ_BAND31,
    MTC_FREQ_BAND32,
    MTC_FREQ_BAND33 = 33,
    MTC_FREQ_BAND34,
    MTC_FREQ_BAND35,
    MTC_FREQ_BAND36,
    MTC_FREQ_BAND37,
    MTC_FREQ_BAND38,
    MTC_FREQ_BAND39,
    MTC_FREQ_BAND40,
    MTC_FREQ_BAND41,
    MTC_FREQ_BAND42,
    MTC_FREQ_BAND43,
    MTC_FREQ_BAND44,
    MTC_FREQ_BAND64 = 64,

    /* 非标频段begin */
    MTC_FREQ_BAND101 = 101,
    MTC_FREQ_BAND102 = 102,
    MTC_FREQ_BAND103 = 103,
    MTC_FREQ_BAND104 = 104,
    MTC_FREQ_BAND105 = 105,
    MTC_FREQ_BAND106 = 106,
    MTC_FREQ_BAND107 = 107,
    MTC_FREQ_BAND108 = 108,
    MTC_FREQ_BAND109 = 109,
    MTC_FREQ_BAND110 = 110,
    MTC_FREQ_BAND111 = 111,
    MTC_FREQ_BAND112 = 112,
    MTC_FREQ_BAND113 = 113,
    MTC_FREQ_BAND114 = 114,
    MTC_FREQ_BAND115 = 115,
    MTC_FREQ_BAND116 = 116,

    /* 非标频段end */
    MTC_FREQ_BAND_BUTT = 0xFFFF
};
typedef VOS_UINT16 MTC_BAND_INFO_ENUM_UINT16;

/* Add by j00174725 for RF&LCD INTRUSION, 2014-03-04, GU 结构定义(由上官声长00266224提供) End */


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/

/*****************************************************************************
 结构名    : MTC_RF_INTRUSION_CFG_STRU
 结构说明  : MTC模块干扰控制结构

  1.日    期   : 2014年3月24日
    作    者   : A00165503
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIntrusionCfg      : 1;
    VOS_UINT8                           ucNotchBypass       : 1;
    VOS_UINT8                           ucNarrowBandDcsCfg  : 1;
    VOS_UINT8                           ucTlRfCtrlCfg       : 1;
    VOS_UINT8                           ucReserved          : 4;

    VOS_UINT8                           aucAdditonCfg[3];

} MTC_RF_INTRUSION_CFG_STRU;

/*****************************************************************************
 结构名    : MTC_INTRUSION_CTX_STRU
 结构说明  : MTC模块干扰裁决相关的上下文结构

  1.日    期   : 2013年08月12日
    作    者   : j00174725
    修改内容   : V9R1 干扰控制项目
*****************************************************************************/
typedef struct
{
    MTC_NV_RF_INTRUSION_CFG_STRU        stIntrusionCfg;                         /* 保存RF INTRUSION NV配置信息 */
    PS_BOOL_ENUM_UINT8                  enNotchEnableFlag;

    PS_BOOL_ENUM_UINT8                  enNarrowDcsEnableFlag;                  /* 记录NarrowDcs状态 */

    PS_BOOL_ENUM_UINT8                  enTlRfCtrlEnableFlag;

    PS_BOOL_ENUM_UINT8                  enRseCfg;                               /* 记录已经下发过的RSE配置 */
}MTC_INTRUSION_CTX_STRU;

/*****************************************************************************
 结构名    : MTC_MODEM_SERVICE_INFO_STRU
 结构说明  : MTC模块记录Modem当前服务信息结构体

  1.日    期   : 2013年08月12日
    作    者   : j00174725
    修改内容   : V9R1 干扰控制项目
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCallSrvExistFlg;                      /* Modem是否存在呼叫服务 */
    VOS_UINT8                           ucSmsSrvExistFlg;                       /* Modem是否存在短信业务 */
    VOS_UINT8                           ucSsSrvExistFlg;                        /* Modem是否存在补充业务 */
    VOS_UINT8                           aucReserved1[1];
}MTC_MODEM_SERVICE_INFO_STRU;

/*****************************************************************************
 结构名    : MTC_MODEM_PS_DOMAIN_INFO_STRU
 结构说明  : Modem当前PS域信息
 1.日    期   : 2014年01月17日
   作    者   : l00198894
   修改内容   : V9R1C53 C+L 离网重选项目
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPsSupportFlg;                         /* 当前PS域是否支持GPRS接入 */
    VOS_UINT8                           ucPsAttachAllowFlg;                     /* PS域是否允许注册,VOS_TRUE:允许PS域注册,VOS_FALSE:不允许PS域注册 */

    VOS_UINT8                           aucReserved1[2];
}MTC_MODEM_PS_DOMAIN_INFO_STRU;

/*****************************************************************************
 结构名    : MTC_MODEM_NETWORK_INFO_STRU
 结构说明  : Modem当前驻留网络信息
 1.日    期   : 2014年01月17日
   作    者   : l00198894
   修改内容   : V9R1C53 C+L 离网重选项目
*****************************************************************************/
typedef struct
{
    MTC_MMA_PLMN_ID_STRU                stPlmnId;                               /* Modem当前驻留网络 */
    MTC_MODEM_PS_DOMAIN_INFO_STRU       stPsDomainInfo;                         /* Modem当前PS域信息 */

    VOS_UINT8                           ucIsForbiddenPlmnFlag;                  /* Modem当前驻留网络是否为禁止网络标识 */
    VOS_UINT8                           aucReserved1[3];
}MTC_MODEM_NETWORK_INFO_STRU;

/*******************************************************************************
 结构名    : MTC_MODEM_MIPICLK_BITMAP_STRU
 结构说明  : 当前服务小区的频率和存在的服务

 1.日    期   : 2014年03月05日
   作    者   : Y00213812
   修改内容   : 新生成
*******************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enCsExistFlag;
    PS_BOOL_ENUM_UINT8                  enPsExistFlag;

    VOS_UINT16                          usScellBitMap;
    VOS_UINT16                          usHoppingBitMap;
    VOS_UINT16                          usNcellBitMap;
}MTC_MODEM_MIPICLK_BITMAP_STRU;

/* Add by j00174725 for K3V3 多模多天线特性, 2014-06-16, Begin */
/*******************************************************************************
 结构名    : MTC_MODEM_CONN_STATE_INFO_STRU
 结构说明  : modem 连接状态信息

 1.日    期   : 2014年06月16日
   作    者   : j00174725
   修改内容   : K3V3 多模多天线特性
 2.日    期   : 2014年09月4日
   作    者   : j00174725
   修改内容   : DTS2015082406288
 3.日    期   : 2014年09月19日
   作    者   : j00174725
   修改内容   : DTS2015091108014
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCsSessionInfo;
    VOS_UINT32                          ulPsSessionInfo;
    VOS_UINT8                           ucCsSrvConnInfo;
    VOS_UINT8                           ucPsSrvConnInfo;
    VOS_UINT8                           aucReserved[2];
}MTC_MODEM_CONN_STATE_INFO_STRU;

/*******************************************************************************
 结构名    : MTC_MODEM_RAT_CONFIG_STRU
 结构说明  : modem 接入制式配置信息

  1.日    期   : 2015年10月21日
    作    者   : h00313353
    修改内容   : Iteration 19 TAS
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIsGuExist;                            /* Rat配置中是否包含GU */
    VOS_UINT8                           ucIsLteExist;                           /* Rat配置中是否包含LTE */
    VOS_UINT8                           ucIs1xExist;                            /* Rat配置中是否包含1X */
    VOS_UINT8                           ucIsHrpdExist;                          /* Rat配置中是否包含HRPD */
} MTC_MODEM_RAT_CONFIG_STRU;

/*******************************************************************************
 结构名    : MTC_OUTSIDE_MODEM_CONN_STATE_INFO_STRU
 结构说明  : 外挂modem 连接状态信息

 1.日    期   : 2015年09月18日
   作    者   : j00174725
   修改内容   : K3V3 多模多天线特性
*******************************************************************************/
typedef struct
{
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enCsSrvConnState;
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enPsSrvConnState;
    VOS_UINT8                           aucReserved[2];
}MTC_OUTSIDE_MODEM_CONN_STATE_INFO_STRU;


/*******************************************************************************
 结构名    : MTC_OUTSIDE_MODEM_INFO_STRU
 结构说明  : 外接modem信息

 1.日    期   : 2014年06月16日
   作    者   : j00174725
   修改内容   : K3V3 多模多天线特性
 2.日    期   : 2014年09月18日
   作    者   : j00174725
   修改内容   : DTS2015091108014
*******************************************************************************/
typedef struct
{
    MTC_OUTSIDE_MODEM_CONN_STATE_INFO_STRU  stConnStateInfo;
    MTC_MODEM_POWER_STATE_ENUM_UINT8        enPowerState;
    VOS_UINT8                               aucReserved1[3];
    TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16   enUsimmState;
    VOS_UINT8                               aucReserved2[2];
} MTC_OUTSIDE_MODEM_INFO_STRU;

/*****************************************************************************
 结构名    : MTC_BAND_INFO_MSG_BUF_STRU
 结构说明  : 用于缓存接入层发过来的BAND_INFO消息

  1.日    期   : 2015年10月29日
    作    者   : j00174725
    修改内容   : DTS2015102706654
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                              enExitBufMsgFlag;
    VOS_UINT8                                       aucRsv[3];
    RRC_MTC_INTRUSION_BAND_INFO_IND_STRU            stIntrusionBandInfoMsg;
}MTC_BAND_INFO_MSG_BUF_STRU;

/*****************************************************************************
 结构名    : MTC_USING_FREQ_MSG_BUF_STRU
 结构说明  : 用于缓存邻区消息

  1.日    期   : 2015年10月29日
    作    者   : j00174725
    修改内容   : DTS2015102706654
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                              enExitBufMsgFlag;
    VOS_UINT8                                       aucRsv[3];
    RRC_MTC_USING_FREQ_IND_STRU                     stUsingFreqInfoMsg;
}MTC_USING_FREQ_MSG_BUF_STRU;

/*****************************************************************************
 结构名    : MTC_MSG_BUF_STRU
 结构说明  : 用于缓存BAND消息或者邻区消息

  1.日    期   : 2015年10月29日
    作    者   : j00174725
    修改内容   : DTS2015102706654
*****************************************************************************/
typedef struct
{
    MTC_BAND_INFO_MSG_BUF_STRU          stBufBandInfoMsg;
    MTC_USING_FREQ_MSG_BUF_STRU         stBufUsingFreqInfoMsg;
}MTC_MSG_BUF_STRU;

/* Add by j00174725 for K3V3 多模多天线特性, 2014-06-16, Begin */
/*****************************************************************************
 结构名    : MTC_MODEM_INFO_STRU
 结构说明  : MTC模块保存Modem状态信息

  1.日    期   : 2013年08月12日
    作    者   : j00174725
    修改内容   : V9R1 干扰控制项目

  2.日    期   : 2014年01月17日
    作    者   : l00198894
    修改内容   : C+L项目修改

  3.日    期   : 2014年1月23日
    作    者   : z00161729
    修改内容   : DTS2014012305088:svlte特性开启卡无效场景mtc无需上报pstransfer:0

  4.日    期   : 2014年3月24日
    作    者   : A00165503
    修改内容   : B39&B32 Intrusion

  4.日    期   : 2015年5月15日
    作    者   : wx270776
    修改内容   : TAS环回测试: 增加环回状态
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucRatCap;                           /* Modem的接入技术能力值 */
    MTC_MODEM_POWER_STATE_ENUM_UINT8        enPowerState;                       /* Modem的开关机状态 */
    MTC_RATMODE_ENUM_UINT8                  enRatMode;                          /* Modem当前的模式类型 */
    VOS_UINT8                               ucUsimValidFlag;                    /* modem当前卡是否有效，1:卡有效；0:卡无效 */

    MTC_MODEM_SERVICE_INFO_STRU             stSrvInfo;                          /* Modem当前服务信息 */
    RRC_MTC_MS_BAND_INFO_STRU               stCurBandInfo;                      /* Modem当前的频段信息 */

    RRC_MTC_MS_BAND_INFO_STRU               stNCellBandInfo;                      /* Modem的临区Band信息， 目前只记录GU模时的TL临区Band信息 */

    RRC_MTC_MS_BAND_INFO_STRU               stSerCellBandInfo;                  /* Modem当前驻留到的频段信息 */

    MTC_MODEM_NETWORK_INFO_STRU             stNetworkInfo;                      /* Modem当前驻留网络信息 */

    MTC_MODEM_MIPICLK_BITMAP_STRU           stRfCellInfo;                       /* Modem当前的BITMAP状态 */

    /* Add by j00174725 for K3V3 多模多天线特性, 2014-06-16, Begin */
    MTC_MODEM_CONN_STATE_INFO_STRU          stConnStateInfo;                    /* Modem当前连接状态 */

    MTC_MODEM_RAT_CONFIG_STRU               stRatCfg;                           /* modem 接入制式配置信息 */

    TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16   enUsimState;                        /* Usim卡状态 */
    TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16   enCsimState;                        /* Csim卡状态 */
    MTC_MODEM_POWER_STATE_ENUM_UINT8        enImsaState;                        /* Modem的IMSA开关机状态 */

    MTC_MODEM_IMS_VOICE_CAP_ENUM_UINT8      enImsVoiceCap;
    /* Add by j00174725 for K3V3 多模多天线特性, 2014-06-16, End */


    MTC_RCM_TC_STATUS_ENUM_UINT16           enTcStatus;                         /* 记录TAS环回测试状态 */
    MTC_GSM_CELLINFO_EX_STRU                stGsmCellInfoEx;                    /* GSM小区扩展信息(不区分modem) */

    MTC_MSG_BUF_STRU                        stBufMsg;
}MTC_MODEM_INFO_STRU;

/*****************************************************************************
 结构名    : MTC_PS_TRANSFER_CTX_STRU
 结构说明  : MTC模块PS域迁移相关的上下文结构

  1.日    期   : 2014年01月17日
    作    者   : l00198894
    修改内容   : V9R1C53 C+L 离网重选项目
*****************************************************************************/
typedef struct
{
    MTC_NV_PS_TRANSFER_CFG_STRU         stPsTransferCfg;                        /* 保存PS TRANSFER NV配置信息 */

    /* Added by Y00213812 for 主动离网重选, 2014-04-10, begin */
    MTC_PS_TRANSFER_CAUSE_ENUM_UINT8    enRrcCause;
    MTC_PS_TRANSFER_CAUSE_ENUM_UINT8    enReportCause;
    VOS_UINT8                           aucRsve[2];
    /* Added by Y00213812 for 主动离网重选, 2014-04-10, end */
}MTC_PS_TRANSFER_CTX_STRU;

/*******************************************************************************
 结构名    : MTC_RF_LCD_MIPICLK_FREQ_STRU
 结构说明  : 记录MIPICLK与其影响频率的结构体
  1.日    期   : 2014年03月04日
    作    者   : j00174725
    修改内容   : RF&LCD INTRUSION项目
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulAvailNum;                             /* 有效频率个数 */
    VOS_UINT32                          ulMipiClk;                              /* MipiClk值 */
    VOS_UINT32                          aulFreq[MTC_RF_LCD_MIPICLK_FREQ_MAX_NUM];/* ulMipiClk值影响的频率表 */
}MTC_RF_LCD_MIPICLK_FREQ_STRU;

/*****************************************************************************
 结构名    : MTC_RF_LCD_INTRUSION_CTX_STRU
 结构说明  : MTC模块RF&LCD干扰相关的上下文结构

  1.日    期   : 2014年03月04日
    作    者   : j00174725
    修改内容   : RF&LCD 干扰规避项目
*****************************************************************************/
typedef struct
{
    /* Modified by Y00213812 for 主动离网重选, 2014-04-10, begin */
    VOS_UINT8                           ucAvailFreqListNum;                     /* 有效的astRfLcdFreqList个数 */
    VOS_UINT8                           aucReserved[1];
    VOS_UINT16                          usMipiClkBitMap;                        /* MIPICLK位图 */
    /* Modified by Y00213812 for 主动离网重选, 2014-04-10, end */
    VOS_UINT32                          ulMipiClkReportModemId;                 /* 保存MipiClk主动上报到那个modem的MTA */
    VOS_UINT16                          usFreqWidth;                            /* 带宽 单位100KHZ */
    VOS_UINT16                          usEnableBitMap;
    MTC_RF_LCD_MIPICLK_FREQ_STRU        astRfLcdFreqList[MTC_RF_LCD_MIPICLK_MAX_NUM];
}MTC_RF_LCD_INTRUSION_CTX_STRU;

/*****************************************************************************
 结构名    : MTC_CONTEXT_STRU
 结构说明  : MTC模块的上下文结构

  1.日    期   : 2013年08月12日
    作    者   : j00174725
    修改内容   : V9R1 干扰控制项目

  2.日    期   : 2014年01月17日
    作    者   : l00198894
    修改内容   : V9R1C53 C+L 离网重选项目
*****************************************************************************/
typedef struct
{
    MTC_MODEM_INFO_STRU                 astModemInfo[MODEM_ID_BUTT];            /* MTC模块保存Modem状态信息 */

    MTC_INTRUSION_CTX_STRU              stIntrusionCtx;                         /* 干扰控制上下文 */

    MTC_PS_TRANSFER_CTX_STRU            stPsTransferCtx;                        /* PS域迁移上下文 */

    MTC_OPERATOR_CUST_SOLUTION_ENUM_UINT8   enOperatorCustSolution;             /* 运营商定制方案 */

    VOS_UINT8                           ucReserved[2];
    MODEM_ID_ENUM_UINT16                enCdmaModemId;                          /* CDMA ModemId */

    MTC_RF_LCD_INTRUSION_CTX_STRU       stRfLcdIntrusionCtx;

    /* Add by j00174725 for K3V3 多模多天线特性, 2014-06-16, Begin */
    MTC_OUTSIDE_MODEM_INFO_STRU         astOutSideModemInfo[MTC_OUTSIDE_MODEM_BUTT];/* 外接modem 信息 */
    /* Add by j00174725 for K3V3 多模多天线特性, 2014-06-16, End */

    /* 后续可能会扩展其它功能 */

}MTC_CONTEXT_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/

/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  10 函数声明
*****************************************************************************/
MTC_CONTEXT_STRU* MTC_GetCtxAddr(VOS_VOID);

MTC_INTRUSION_CTX_STRU* MTC_GetIntrusionCtxAddr(VOS_VOID);

MTC_MODEM_INFO_STRU* MTC_GetModemCtxAddr(MODEM_ID_ENUM_UINT16 enModemId);

VOS_VOID MTC_InitIntrusionCtx(VOS_VOID);

VOS_UINT32 MTC_IsSupportRatType(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_RATMODE_ENUM_UINT8              enRatMode
);

VOS_VOID MTC_InitModemCtx(VOS_VOID);

VOS_VOID MTC_InitCtx(VOS_VOID);

MTC_CFG_ENUM_UINT8 MTC_GetIntrusionCfg(VOS_VOID);

VOS_VOID MTC_SetModemPowerState(MODEM_ID_ENUM_UINT16 enModemId, MTC_MODEM_POWER_STATE_ENUM_UINT8 enState);

MTC_MODEM_POWER_STATE_ENUM_UINT8 MTC_GetModemPowerState(MODEM_ID_ENUM_UINT16 enModemId);

VOS_VOID MTC_SetModemRatMode(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_RATMODE_ENUM_UINT8              enRatMode
);

VOS_VOID MTC_SetModemImsaState(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_MODEM_POWER_STATE_ENUM_UINT8    enState);

MTC_MODEM_POWER_STATE_ENUM_UINT8 MTC_GetModemImsaState(MODEM_ID_ENUM_UINT16 enModemId);

VOS_VOID MTC_SetModemImsVoiceCap(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_MODEM_IMS_VOICE_CAP_ENUM_UINT8  enState
);
MTC_MODEM_IMS_VOICE_CAP_ENUM_UINT8 MTC_GetModemImsVoiceCap(
    MODEM_ID_ENUM_UINT16                enModemId
);

MTC_RATMODE_ENUM_UINT8 MTC_GetModemRatMode(MODEM_ID_ENUM_UINT16 enModemId);

VOS_VOID MTC_SetModemCallSrvExistFlg(
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT8                           ucFlg
);

VOS_VOID MTC_SetModemSmsSrvExistFlg(
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT8                           ucFlg
);

VOS_VOID MTC_SetModemSsSrvExistFlg(
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT8                           ucFlg
);

MTC_CS_SERVICE_STATE_ENUM_UINT8 MTC_GetModemCsSrvExistFlg(
    MODEM_ID_ENUM_UINT16                enModemId
);

RRC_MTC_MS_BAND_INFO_STRU* MTC_GetModemCurBandInfo(
    MODEM_ID_ENUM_UINT16                enModemId
);

VOS_UINT8 MTC_GetModemUsimValidFlag(MODEM_ID_ENUM_UINT16 enModemId);
VOS_VOID MTC_SetModemUsimValidFlag(
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT8                           ucUsimValidStatus
);

VOS_VOID MTC_ResetModemInfo(MODEM_ID_ENUM_UINT16 enModemId);

VOS_VOID MTC_SetNotchEnalbeFlag(PS_BOOL_ENUM_UINT8 enFlag);
PS_BOOL_ENUM_UINT8 MTC_GetNotchEnalbeFlag(VOS_VOID);
MTC_CFG_ENUM_UINT8 MTC_GetNotchCfg(VOS_VOID);

RRC_MTC_MS_BAND_INFO_STRU* MTC_GetModemSerCellBandInfo(
    MODEM_ID_ENUM_UINT16                enModemId
);
MTC_CFG_ENUM_UINT8 MTC_GetTlRfCtrlCfg(VOS_VOID);
VOS_VOID MTC_SetTlRfCtrlEnalbeFlag(PS_BOOL_ENUM_UINT8 enFlag);
PS_BOOL_ENUM_UINT8 MTC_GetTlRfCtrlEnalbeFlag(VOS_VOID);

VOS_VOID MTC_InitPsTransferCtx(VOS_VOID);

VOS_VOID MTC_InitOperatorCustSolution(VOS_VOID);

MTC_PS_TRANSFER_ENUM_UINT8 MTC_GetPsTransferCfg(VOS_VOID);

MTC_PS_TRANSFER_CTX_STRU* MTC_GetPsTransferCtxAddr(VOS_VOID);

MTC_MODEM_NETWORK_INFO_STRU* MTC_GetModemNetworkInfoAddr(
    MODEM_ID_ENUM_UINT16                enModemId);

MTC_OPERATOR_CUST_SOLUTION_ENUM_UINT8 MTC_GetOperatorCustSolution(VOS_VOID);

VOS_VOID MTC_SetOperatorCustSolution(
    MTC_OPERATOR_CUST_SOLUTION_ENUM_UINT8   enOperatorCustSolution);


VOS_VOID MTC_SetNarrowDcsEnalbeFlag(PS_BOOL_ENUM_UINT8 enFlag);
PS_BOOL_ENUM_UINT8 MTC_GetNarrowDcsEnalbeFlag(VOS_VOID);
MTC_CFG_ENUM_UINT8 MTC_GetNarrowBandDcsCfg(VOS_VOID);

MTC_RF_LCD_INTRUSION_CTX_STRU* MTC_GetRfLcdIntrusionCtxAddr(VOS_VOID);
MTC_CFG_ENUM_UINT8 MTC_GetRfLcdIntrusionCfg(VOS_VOID);
VOS_VOID MTC_InitRfLcdIntrusionCtx(VOS_VOID);
VOS_VOID MTC_ReadRfLcdCfgNv(VOS_VOID);
VOS_UINT32 MTC_GetMipiClkRcvPid(VOS_VOID);
MTC_MODEM_MIPICLK_BITMAP_STRU* MTC_GetRfCellInfoAddr(
    MODEM_ID_ENUM_UINT16                enModemId
);
VOS_UINT16 MTC_GetMipiClkBitMap(VOS_VOID);
VOS_VOID MTC_InitRfCellInfo(MODEM_ID_ENUM_UINT16 enModemId);
MTC_RF_LCD_INTRUSION_CTX_STRU* MTC_GetRfLcdIntrusionCtxAddr(VOS_VOID);

MTC_CFG_ENUM_UINT8 MTC_GetRseSupportCfg(VOS_VOID);

PS_BOOL_ENUM_UINT8 MTC_GetRseCfgValue(VOS_VOID);

VOS_VOID MTC_SetRseCfgValue(PS_BOOL_ENUM_UINT8 enValue);


/* Add by j00174725 for K3V3 多模多天线特性, 2014-06-16, Begin */
VOS_VOID MTC_SetCsTypeInfo(
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT8                           ucCsTypeInfo,
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enCsSrvConnState
);

VOS_UINT8 MTC_GetCsTypeInfo(
    MODEM_ID_ENUM_UINT16                enModemId
);

TAF_MTC_SRV_CONN_STATE_ENUM_UINT8 MTC_GetCsSrvState(
    MODEM_ID_ENUM_UINT16                enModemId
);

VOS_VOID MTC_SetPsTypeInfo(
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT8                           ucPsTypeInfo,
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enPsSrvConnState
);

VOS_UINT8 MTC_GetPsTypeInfo(
    MODEM_ID_ENUM_UINT16                enModemId
);

TAF_MTC_SRV_CONN_STATE_ENUM_UINT8 MTC_GetPsSrvState(
    MODEM_ID_ENUM_UINT16                enModemId
);


MTC_OUTSIDE_MODEM_INFO_STRU* MTC_GetOutSideModemCtxAddr(
    MTC_OUTSIDE_MODEM_ENUM_UINT16       enModemId
);

VOS_VOID MTC_SetOutSideCsConnStateInfo(
    MTC_OUTSIDE_MODEM_ENUM_UINT16       enModemId,
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enConnSt
);

TAF_MTC_SRV_CONN_STATE_ENUM_UINT8 MTC_GetOutSideCsConnStateInfo(
    MTC_OUTSIDE_MODEM_ENUM_UINT16       enModemId
);

VOS_VOID MTC_SetOutSidePsConnStateInfo(
    MTC_OUTSIDE_MODEM_ENUM_UINT16       enModemId,
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enConnSt
);

TAF_MTC_SRV_CONN_STATE_ENUM_UINT8 MTC_GetOutSidePsConnStateInfo(
    MTC_OUTSIDE_MODEM_ENUM_UINT16       enModemId
);

VOS_VOID MTC_SetOutSideModemPowerState(
    MTC_OUTSIDE_MODEM_ENUM_UINT16       enModemId,
    MTC_MODEM_POWER_STATE_ENUM_UINT8    enPowerStatus
);

MTC_MODEM_POWER_STATE_ENUM_UINT8 MTC_GetOutSideModemPowerState(
    MTC_OUTSIDE_MODEM_ENUM_UINT16       enModemId
);

VOS_VOID MTC_SetUsimStateInfo(
    MODEM_ID_ENUM_UINT16                    enModemId,
    TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16   enUsimState
);

TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16 MTC_GetUsimStateInfo(
    MODEM_ID_ENUM_UINT16                enModemId
);

TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16 MTC_GetCsimStateInfo(
    MODEM_ID_ENUM_UINT16                enModemId
);

MTC_MODEM_RAT_CONFIG_STRU* MTC_GetRatCfgByModemId(
    MODEM_ID_ENUM_UINT16                enModemId
);

VOS_VOID MTC_SetRatCfgByModemId(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_MODEM_RAT_CONFIG_STRU          *pstRatCfg
);

VOS_VOID MTC_SetCsimStateInfo(
    MODEM_ID_ENUM_UINT16                    enModemId,
    TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16   enCsimState
);

VOS_VOID MTC_SetOutSideModemUsimmState(
    MTC_OUTSIDE_MODEM_ENUM_UINT16           enModemId,
    TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16   enUsimmStatus
);

TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16 MTC_GetOutSideModemUsimmState(
    MTC_OUTSIDE_MODEM_ENUM_UINT16       enModemId
);

/* Add by j00174725 for K3V3 多模多天线特性, 2014-06-16, End */

MTC_GSM_CELLINFO_EX_STRU* MTC_GetModemGsmCellInfoEx(
    MODEM_ID_ENUM_UINT16                enModemId
);

MTC_RCM_TC_STATUS_ENUM_UINT16 MTC_GetCurrentTcStatus(
    MODEM_ID_ENUM_UINT16                enModemId
);

VOS_VOID MTC_SetCurrentTcStatus(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_RCM_TC_STATUS_ENUM_UINT16       enTcStatus
);

VOS_VOID MTC_SetCsSessionInfo(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_SESSION_TYPE_ENUM_UINT8         enSessionType
);
VOS_VOID MTC_ClearCsSessionInfo(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_SESSION_TYPE_ENUM_UINT8         enSessionType
);

VOS_VOID MTC_ClearPsSessionInfo(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_SESSION_TYPE_ENUM_UINT8         enSessionType
);

VOS_UINT32 MTC_GetCsSessionInfo(
    MODEM_ID_ENUM_UINT16                enModemId
);

VOS_UINT32 MTC_GetPsSessionInfo(
    MODEM_ID_ENUM_UINT16                enModemId
);


VOS_VOID MTC_SetPsSessionInfo(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_SESSION_TYPE_ENUM_UINT8         enSessionType
);

PS_BOOL_ENUM_UINT8 MTC_IsCsSessionInfoExit(
    MODEM_ID_ENUM_UINT16                enModemId
);
PS_BOOL_ENUM_UINT8 MTC_IsPsSessionInfoExit(
    MODEM_ID_ENUM_UINT16                enModemId
);

VOS_VOID MTC_ResetModemCurBandInfo(
    MODEM_ID_ENUM_UINT16                enModemId
);

RRC_MTC_MS_BAND_INFO_STRU* MTC_GetModemNCellBandInfo(
    MODEM_ID_ENUM_UINT16                enModemId
);

VOS_VOID MTC_SetModemNCellBandInfo(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_BAND_INFO_ENUM_UINT16           enBandNum
);

VOS_VOID MTC_ResetNCellBandInfo(
    MODEM_ID_ENUM_UINT16                enModemId
);

MTC_MSG_BUF_STRU* MTC_GetBufAddr(
    MODEM_ID_ENUM_UINT16                enModemId
);

VOS_VOID MTC_ParsePlatFormRat(
    VOS_UINT8                          *pucRat,
    PLATAFORM_RAT_CAPABILITY_STRU      *pstPlatFormRat
);


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

#endif /* end of MtcCtx.h */
