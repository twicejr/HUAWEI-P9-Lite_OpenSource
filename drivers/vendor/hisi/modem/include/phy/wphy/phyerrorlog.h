/******************************************************************************

                  版权所有 (C), 2003-2013, 华为技术有限公司

 ******************************************************************************
  文 件 名   : phyerrorlog.h
  版 本 号   : 初稿
  作    者   : 罗青全/57356
  生成日期   : 2013年9月21日
  最近修改   :
  功能描述   : 商用ERRORLOG及工程模式上报使用的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年09月21日
    作    者   : 罗青全/57356
    修改内容   : 创建文件

******************************************************************************/

#ifndef __PHY_ERRORLOG_H__
#define __PHY_ERRORLOG_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "omerrorlog.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/



#define PHY_ERR_LOG_CTRL_LEVEL_NULL             (0)                             /* ErrLog等级未定义*/
#define PHY_ERR_LOG_CTRL_LEVEL_CRITICAL         (1)                             /* ErrLog等级为紧急 */
#define PHY_ERR_LOG_CTRL_LEVEL_MAJOR            (2)                             /* ErrLog等级为重要 */
#define PHY_ERR_LOG_CTRL_LEVEL_MINOR            (3)                             /* ErrLog等级为次要 */
#define PHY_ERR_LOG_CTRL_LEVEL_WARNING          (4)                             /* ErrLog等级为提示 */


/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
 枚举名    : PHY_ERR_LOG_ALM_TYPE_ENUM
 枚举说明  : 故障告警类型
 1.日    期   : 2013年09月23日
   作    者   : luoqingquan
   修改内容   : 新建
*****************************************************************************/
enum PHY_ERR_LOG_ALM_TYPE_ENUM
{
    PHY_ERR_LOG_ALM_TYPE_COMMUNICATION    = 0x00,                               /* 通信 */
    PHY_ERR_LOG_ALM_TYPE_TRAFFIC_QUALITY  = 0x01,                               /* 业务质量 */
    PHY_ERR_LOG_ALM_TYPE_DEAL_WRONG       = 0x02,                               /* 处理出错 */
    PHY_ERR_LOG_ALM_TYPE_DEVICE_FAILURE   = 0x03,                               /* 设备故障 */
    PHY_ERR_LOG_ALM_TYPE_ENV_FAILURE      = 0x04,                               /* 环境故障 */
    PHY_ERR_LOG_ALM_TYPE_BUTT
};
typedef VOS_UINT16 PHY_ERR_LOG_ALM_TYPE_ENUM_UINT16;


/*****************************************************************************
 枚举名    : PHY_ERR_LOG_ALM_ID_ENUM
 枚举说明  : 故障告警ID
 1.日    期   : 2013年09月23日
   作    者   : luoqingquan
   修改内容   : 新建
*****************************************************************************/
enum PHY_ERR_LOG_ALM_ID_ENUM
{
    /* 缓存故障 */
    PHY_ERR_LOG_ALM_WCDMA_OUT_SYNC                      = 0x01,                 /* 失步 */
    PHY_ERR_LOG_ALM_WCDMA_BCCH_FAIL                     = 0x02,                 /* BCCH失败 */
    PHY_ERR_LOG_ALM_WCDMA_RL_FAIL                       = 0x03,                 /* 链路失败 */
    PHY_ERR_LOG_ALM_GSM_DEC_FAIL                        = 0x04,                 /* DSC记录 */
    PHY_ERR_LOG_ALM_GSM_RXLEV_MEAS                      = 0x05,                 /* 处理记录 */
    PHY_ERR_LOG_ALM_GSM_FB_SB_IND                       = 0x06,                 /* 搜索记录 */
    PHY_ERR_LOG_ALM_RING_BUFFER_OVERFLOW                = 0x07,                 /* 环形buffer溢出记录 */
    PHY_ERR_LOG_ALM_TAS_GSM_INFO                        = 0x08,                 /* GSM_TAS关键信息 */
    PHY_ERR_LOG_ALM_TAS_WCDMA_INFO                      = 0x09,                 /* WCDMA_TAS关键信息 */
    PHY_ERR_LOG_ALM_GSM_CS_MR_ERROR                     = 0x0a,                 /* CS测量报告错误 */

    /* 语音类故障告警 */
    PHY_ERR_LOG_ALM_CS_RLB                              = 0x1001,               /* CS 链路质量差 */
    PHY_ERR_LOG_ALM_CS_NO_UL_DATA                       = 0x1002,               /* CS 无上行数据 */
    PHY_ERR_LOG_ALM_GSM_CS_ERROR_DETECT                 = 0x1003,               /* 检测到异常error */
    PHY_ERR_LOG_ALM_GSM_DCXO_SAMPLE_ERR_DETECT          = 0x1004,               /* 检测到DCXO采样点异常的CHR */

    /* 业务类故障告警 */
    PHY_ERR_LOG_ALM_WCDMA_TX_POWER_DROP_DETECT          = 0x2001,               /* 检测到发射功率太低 */
    PHY_ERR_LOG_ALM_WCDMA_PILOT_BER_RISE_DETECT         = 0x2002,               /* 检测到pilotber陡升 */
    PHY_ERR_LOG_ALM_WCDMA_RA_INFO_DETECT                = 0x2003,               /* 检测到随机接入上报信息 */
    PHY_ERR_LOG_ALM_WCDMA_DCXO_SAMPLE_ERR_DETECT        = 0x2004,               /* 检测到DCXO采样点异常的CHR */
    PHY_ERR_LOG_ALM_WCDMA_PD_ABNORMAL_DETECT            = 0x2005,               /* 检测到PD检测异常的CHR */

    PHY_ERR_LOG_ALM_ID_BUTT
};
typedef VOS_UINT16 PHY_ERR_LOG_ALM_ID_ENUM_UINT16;


/*****************************************************************************
 枚举名    : PHY_FTM_LOG_ID_ENUM
 枚举说明  : 工程模式上报的功能ID
 1.日    期   : 2013年08月27日
   作    者   : l57356
   修改内容   : 新建
*****************************************************************************/
enum PHY_FTM_LOG_ID_ENUM
{
    PHY_FTM_LOG_ID_WPHY,
    PHY_FTM_LOG_ID_GPHY,

    PHY_FTM_LOG_ID_BUTT,
};
typedef PHY_UINT16 PHY_FTM_LOG_ID_ENUM_UINT16;


/*****************************************************************************
 枚举名    : PHY_WCDMA_RL_OUT_OF_SYNC_REASON_ENUM
 枚举说明  : 注册的域信息
 1.日    期   : 2013年09月21日
   作    者   : l57356
   修改内容   : 新建
*****************************************************************************/
enum PHY_WCDMA_RL_OUT_OF_SYNC_REASON_ENUM
{
    PHY_WCDMA_RL_OUT_OF_SYNC_REASON_DEMOD        = 0x00,                        /* 上报原因为解调 */
    PHY_WCDMA_RL_OUT_OF_SYNC_REASON_DECODE       = 0x01,                        /* 上报原因为译码 */
    PHY_WCDMA_RL_OUT_OF_SYNC_REASON_BUTT
};
typedef VOS_UINT16 PHY_WCDMA_RL_OUT_OF_SYNC_REASON_ENUM_UINT16;



/*****************************************************************************
 枚举名    : PHY_WCDMA_BCCH_FAIL_REASON_ENUM
 枚举说明  : 注册的域信息
 1.日    期   : 2013年09月21日
   作    者   : l57356
   修改内容   : 新建
*****************************************************************************/
enum PHY_WCDMA_BCCH_FAIL_REASON_ENUM
{
    PHY_WCDMA_BCCH_FAIL_REASON_SFN_UPDATE_FAIL   = 0x00,                        /* 上报原因为SFN更新 */
    PHY_WCDMA_BCCH_FAIL_REASON_CRC_ERR           = 0x01,                        /* 上报原因为CRC错误 */
    PHY_WCDMA_BCCH_FAIL_REASON_SCHEDULE_FAIL     = 0x02,                        /* 上报原因为调度错误 */
    PHY_WCDMA_BCCH_FAIL_REASON_WORK_TIME_ERR     = 0x03,                        /* 上报原因为定时错误 */
    PHY_WCDMA_BCCH_FAIL_REASON_BUTT
};
typedef VOS_UINT16 PHY_WCDMA_BCCH_FAIL_REASON_ENUM_UINT16;


/*****************************************************************************
 枚举名    : PHY_GSM_RPT_REASON_ENUM
 枚举说明  : 注册的域信息
 1.日    期   : 2013年09月21日
   作    者   : l57356
   修改内容   : 新建
*****************************************************************************/
enum PHY_GSM_RPT_REASON_ENUM
{
    PHY_GSM_RPT_REASON_DSC                      = 0x00,                         /* 上报原因为DSC错误 */
    PHY_GSM_RPT_REASON_CRC_ERR                  = 0x01,                         /* 上报原因为CRC错误 */
    PHY_GSM_RPT_REASON_BUTT
};
typedef VOS_UINT16 PHY_GSM_RPT_REASON_ENUM_UINT16;


/*****************************************************************************
 枚举名    : PHY_GSM_CS_ERROR_REASON_ENUM
 枚举说明  : CS语音期间告警上报原因
 1.日    期   : 2014年07月07日
   作    者   : j00178524
   修改内容   : 新建
*****************************************************************************/
enum PHY_GSM_CS_ERROR_REASON_ENUM
{
    PHY_GSM_CS_ERROR_RLB            = 0,                         /* CS链路差 */
    PHY_GSM_CS_ERROR_NO_UL_DATA     = 1,                         /* 无上行语音数据 */
    PHY_GSM_CS_ERROR_DETECT         = 2,                         /* 异常error */
    PHY_GSM_CS_ERROR_REASON_BUTT
};
typedef VOS_UINT16 PHY_GSM_CS_ERROR_REASON_ENUM_UINT16;


/*****************************************************************************
 枚举名    : PHY_WCDMA_CS_ERROR_REASON_ENUM_UINT16
 枚举说明  : CS语音期间告警上报原因
 1.日    期   : 2014年10月10日
   作    者   : l00184004
   修改内容   : 新建
*****************************************************************************/
enum PHY_WCDMA_CS_ERROR_REASON_ENUM
{
    PHY_WCDMA_CS_ERROR_RLB          = 0,                        /* CS链路差 */
    PHY_WCDMA_CS_ERROR_NO_UL_DATA   = 1,                        /* 无上行语音数据 */
    PHY_WCDMA_CS_ERROR_REASON_BUTT
};

typedef VOS_UINT16 PHY_WCDMA_CS_ERROR_REASON_ENUM_UINT16;
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



/*******************************************************************************
 结构名    : PHY_WCDMA_ERRLOG_FG_INFO_STRU
 结构说明  : WCDMA生成和更新后上报的消息结构体
 1.日    期   : 2013年09月21日
   作    者   : l57356
   修改内容   : 新建
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                  ulFgPos;
    VOS_UINT32                                  ulFgPower;
}PHY_WCDMA_ERRLOG_FG_INFO_STRU;


/*******************************************************************************
 结构名    : PHY_ERRLOG_WCDMA_RL_OUT_OF_SYNC_EVENT_STRU
 结构说明  : WCDMA生成和更新后上报的消息结构体
 1.日    期   : 2013年09月21日
   作    者   : l57356
   修改内容   : 新建
*******************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                      stHeader;
    PHY_WCDMA_RL_OUT_OF_SYNC_REASON_ENUM_UINT16 enRlOutOfSyncReason;
    VOS_INT16                                   sTxPwr;
    VOS_INT16                                   sCQI;
    VOS_INT16                                   sRsv;
    VOS_UINT32                                  ulDemodSyncInfo;
    VOS_UINT32                                  ulDecSyncInfo;
    VOS_UINT32                                  ulDecOutSyncInfo;
    VOS_UINT16                                  usFgEn;
    VOS_UINT16                                  usFgLock;
    PHY_WCDMA_ERRLOG_FG_INFO_STRU               stFgInfo;
}PHY_ERRLOG_WCDMA_RL_OUT_OF_SYNC_EVENT_STRU;



/*******************************************************************************
 结构名    : PHY_ERRLOG_WCDMA_RL_FAIL_EVENT_STRU
 结构说明  : WCDMA生成和更新后上报的消息结构体
 1.日    期   : 2013年09月21日
   作    者   : l57356
   修改内容   : 新建
*******************************************************************************/

typedef struct
{
    OM_ERR_LOG_HEADER_STRU                  stHeader;
    PHY_WCDMA_BCCH_FAIL_REASON_ENUM_UINT16  enBcchFailReason;
    VOS_INT16                               sRsv;
    VOS_UINT16                              usFgEn;
    VOS_UINT16                              usFgLock;
    PHY_WCDMA_ERRLOG_FG_INFO_STRU           astFgInfo[3];
    VOS_UINT16                              usBcchCrcErrNum;
    VOS_UINT16                              usBgSchdlFailNum;
}PHY_ERRLOG_WCDMA_BCCH_FAIL_EVENT_STRU;




/*******************************************************************************
 结构名    : PHY_ERRLOG_WCDMA_RL_FAIL_EVENT_STRU
 结构说明  : WCDMA生成和更新后上报的消息结构体
 1.日    期   : 2013年09月21日
   作    者   : l57356
   修改内容   : 新建
*******************************************************************************/

typedef struct
{
    OM_ERR_LOG_HEADER_STRU                  stHeader;
    VOS_INT16                               sTxPwr;
    VOS_INT16                               sCQI;
    VOS_UINT32                              ulDemodSyncInfo;
    VOS_UINT32                              ulDecSyncInfo;
    VOS_UINT32                              ulDecOutSyncInfo;
    VOS_UINT16                              usFgEn;
    VOS_UINT16                              usFgLock;
    PHY_WCDMA_ERRLOG_FG_INFO_STRU           stFgInfo;
    VOS_UINT16                              uhwGoodSignalDropFlag;              /* 好信号误码标记，如果为1则为好信号误码。否则不是，RSCP和EcN0都会填为0 */
    VOS_INT16                               shwRscp;                            /* RSCP */
    VOS_INT16                               shwEcN0;                            /* EcN0 */
    VOS_UINT16                              usReserved;
}PHY_ERRLOG_WCDMA_RL_FAIL_EVENT_STRU;





/*******************************************************************************
 结构名    : PHY_ERRLOG_GSM_DECODE_FAIL_EVENT_STRU
 结构说明  : GSM生成和更新后上报的消息结构体
 1.日    期   : 2013年09月21日
   作    者   : l57356
   修改内容   : 新建
*******************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                  stHeader;
    PHY_GSM_RPT_REASON_ENUM_UINT16          enRptReason;
    VOS_UINT16                              usArfcn;
    VOS_UINT16                              usRxlev;
    VOS_UINT16                              usDscInitValue;
    VOS_UINT32                              ulCurFn;
    VOS_UINT16                              usAfc;
    VOS_UINT16                              usTxPwr;
    VOS_UINT16                              usCI;
    VOS_INT16                               sToa;
    VOS_UINT32                              ulCarrirIn;
    VOS_UINT32                              ulInterfereIn;
    VOS_UINT32                              ulCarrirOut;
    VOS_UINT32                              ulInterfereOut;
    VOS_UINT32                              ulLsDcValue;
    VOS_UINT32                              ulRemoveDc;
    VOS_UINT32                              ulBurstRemoveDc;
    VOS_UINT32                              aulDemodData[2];
}PHY_ERRLOG_GSM_DECODE_FAIL_EVENT_STRU;




/*******************************************************************************
 结构名    : PHY_ERRLOG_GSM_DECODE_FAIL_EVENT_STRU
 结构说明  : GSM生成和更新后上报的消息结构体
 1.日    期   : 2013年09月21日
   作    者   : l57356
   修改内容   : 新建
*******************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                  stHeader;
    VOS_UINT16                              usArfcn;
    VOS_UINT16                              usAfc;
    VOS_UINT32                              ulCurFn;
    VOS_UINT32                              uwReg5250;
    VOS_UINT32                              uwDrssi;
    VOS_UINT32                              uwFastDrssi;
    VOS_UINT32                              ulLsDcValue;
    VOS_UINT32                              ulRemoveDc;
    VOS_UINT32                              ulBurstRemoveDc;
}PHY_ERRLOG_GSM_RXLEV_MEAS_EVENT_STRU;




/*******************************************************************************
 结构名    : PHY_ERRLOG_GSM_FB_SB_EVENT_STRU
 结构说明  : GSM生成和更新后上报的消息结构体
 1.日    期   : 2013年09月21日
   作    者   : l57356
   修改内容   : 新建
*******************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                  stHeader;
    VOS_UINT16                              usArfcn;
    VOS_UINT16                              usAfc;
    VOS_UINT32                              ulSrchMode;
    VOS_UINT32                              ulRptStatus;
    VOS_UINT32                              ulSbData;
    VOS_UINT32                              ulCurFn;
    VOS_UINT32                              ulReg5250;
    VOS_UINT32                              ulDrssi;
    VOS_UINT32                              ulFastDrssi;
    VOS_UINT32                              ulLsDcValue;
    VOS_UINT32                              ulRemoveDc;
    VOS_UINT32                              ulBurstRemoveDc;
    VOS_UINT32                              aulDemodData[2];
}PHY_ERRLOG_GSM_FB_SB_EVENT_STRU;




/*******************************************************************************
 结构名    : PHY_FTM_WCDMA_DCH_PARA_EVENT_STRU
 结构说明  : WCDMA生成和更新后上报的消息结构体
 1.日    期   : 2013年09月21日
   作    者   : l57356
   修改内容   : 新建
*******************************************************************************/
typedef struct
{
    OM_FTM_HEADER_STRU                      stHeader;
    VOS_INT16                               sTxPwr;
    VOS_INT16                               sCQI;
    VOS_UINT32                              ulErrBlk;
    VOS_UINT32                              ulDecBlk;
}PHY_FTM_WCDMA_DCH_PARA_EVENT_STRU;


/*******************************************************************************
 结构名    : PHY_FTM_GSM_DCH_PARA_EVENT_STRU
 结构说明  : GSM生成和更新后上报的消息结构体
 1.日    期   : 2013年09月21日
   作    者   : l57356
   修改内容   : 新建
*******************************************************************************/
typedef struct
{
    OM_FTM_HEADER_STRU                      stHeader;
    VOS_UINT16                              usTxPwr;
    VOS_UINT16                              usErrBlk;
    VOS_UINT16                              usDecBlk;
    VOS_UINT16                              usResv;
}PHY_FTM_GSM_DCH_PARA_EVENT_STRU;

/*******************************************************************************
 结构名    : PHY_ERRLOG_GSM_CS_RLB_EVENT_STRU
 结构说明  : CS 链路差事件
 1.日    期   : 2014年07月05日
   作    者   : j00178524
   修改内容   : 新建
*******************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                  stHeader;
    PHY_GSM_CS_ERROR_REASON_ENUM_UINT16     enRptReason;
    VOS_UINT16                              usChannelType;                      /* 信道类型 */
    VOS_UINT16                              usAssignRxTs;                       /* 业务时隙 */
    VOS_UINT16                              usRxlev;                            /* 信号强度 */
    VOS_UINT16                              usCIAverage;                        /* CI平均值 */
    VOS_UINT16                              usErrBitSub;                        /* SUB 误bit数量 */
    VOS_UINT16                              usTotalBitSub;                      /* SUB bit统计总量 */
    VOS_UINT16                              usResv;
}PHY_ERRLOG_GSM_CS_RLB_EVENT_STRU;


/*******************************************************************************
 结构名    : PHY_ERRLOG_GSM_CS_NO_UL_DATA_EVENT_STRU
 结构说明  : GSM无上行语音数据时上报的消息结构体
 1.日    期   : 2014年7月5日
   作    者   : lmx
   修改内容   : 新建
*******************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                  stHeader;
    PHY_GSM_CS_ERROR_REASON_ENUM_UINT16     enCsErrorReason;
    VOS_UINT16                              usChannelType;
    VOS_UINT16                              usAssignRxTs;
    VOS_UINT16                              usResv;
    VOS_UINT32                              ulFn;                                   /* 帧号 */
    VOS_UINT32                              ulQb;                                   /* QB 0~4999 */
    VOS_UINT32                              ulTimeSlice;                            /* 发送时刻时戳 */
    VOS_UINT16                              usChanCodeTime;                        /* 上行编码时间, 单位:0.1 ms */
    VOS_UINT16                              usChanDecodeTime;
}PHY_ERRLOG_GSM_CS_NO_UL_DATA_EVENT_STRU;


/*******************************************************************************
 结构名    : PHY_ERRLOG_GSM_CS_ERROR_DETECT_EVENT_STRU
 结构说明  : 检测到异常error事件
 1.日    期   : 2014年07月05日
   作    者   : j00178524
   修改内容   : 新建
*******************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                  stHeader;
    PHY_GSM_CS_ERROR_REASON_ENUM_UINT16     enRptReason;
    VOS_UINT16                              usChannelType;                      /* 信道类型 */
    VOS_UINT16                              usAssignRxTs;                       /* 业务时隙 */
    VOS_UINT16                              usResv;
}PHY_ERRLOG_GSM_CS_ERROR_DETECT_EVENT_STRU;


/*******************************************************************************
 结构名    : PHY_MNTN_GSM_DCXO_SAMPLE_ERR_EVENT_STRU
 结构说明  : G DCXO样本点异常的CHR
 1.日    期   : 2015年09月19日
   作    者   : w00286360
   修改内容   : 新建
*******************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                  stHeader;
    PHY_INT32                               swFreqErrPpm;                       /* 当前计算的频偏值 */
    PHY_INT16                               shwTemp;                            /* 当前温度，单位0.1度 */
    PHY_INT16                               shwRealA0Value;                     /* 真实的a0 */
    PHY_INT32                               swMinThreshold;                     /* 最小值门限 */
    PHY_INT32                               swMaxThreshold;                     /* 最大值门限 */
    PHY_UINT32                              uwTaskType;                         /* 当前任务类型 */
    PHY_UINT16                              uhwPhyMode;                         /* 物理层的模式 */
    PHY_UINT16                              uhwReserved;
}PHY_MNTN_GSM_DCXO_SAMPLE_ERR_EVENT_STRU;


/*******************************************************************************
 结构名    : PHY_ERRLOG_GSM_CS_RLB_EVENT_STRU
 结构说明  : 环形buffer溢出计数结构
 1.日    期   : 2014年07月05日
   作    者   : j00178524
   修改内容   : 新建
*******************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                  stHeader;
    VOS_UINT32                              ulOverflowCnt;                      /* 环形buffer溢出次数 */
}PHY_ERRLOG_RING_BUFFER_OVERFLOW_EVENT_STRU;

/*******************************************************************************
 结构名    : PHY_ERRLOG_WCDMA_CS_ERROR_RLB_EVENT_STRU
 结构说明  : CS链路质量差事件
 1.日    期   : 2014年10月10日
   作    者   : l00184004
   修改内容   : 新建
*******************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                  stHeader;
    PHY_WCDMA_CS_ERROR_REASON_ENUM_UINT16   enCsErrorReason;                    /* 语音异常告警类型 */
    PHY_UINT16                              uhwChannelType;                     /* 信道类型 */
    PHY_UINT16                              uhwCpichEcN0;                       /* CPICH Ec/N0 */
    PHY_UINT16                              uhwCpichRscp;                       /* CPICH RSCP */
    PHY_UINT16                              uhwSIR;                             /* 语音信道SIR平均值 */
    PHY_UINT16                              uhwCRCErrBlkNum;                    /* CRC错误的语音block数量 */
    PHY_UINT16                              uhwTotalCRCBlkNum;                  /* 语音block统计总量 */
    PHY_UINT16                              uhwErrPilotBitNum;                  /* Pilot bit错误数量 */
    PHY_UINT16                              uhwTotalPilotBitNum;                /* Pilot bit统计总量 */
    PHY_UINT16                              uhwDCHOutOfSyncInd;                 /* DCH out of sync 指示*/
}PHY_ERRLOG_WCDMA_CS_ERROR_RLB_EVENT_STRU;

/*******************************************************************************
 结构名    : PHY_ERRLOG_WCDMA_CS_NO_UL_DATA_EVENT_STRU
 结构说明  : 检测语音数据丢失
 1.日    期   : 2014年07月05日
   作    者   : l00184004
   修改内容   : 新建
*******************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                  stHeader;
    PHY_WCDMA_CS_ERROR_REASON_ENUM_UINT16   enCsErrorReason;                    /* 语音异常告警类型 */
    PHY_UINT16                              uhwChannelType;                     /* 信道类型 */
    PHY_UINT16                              uhwFrameNum;                         /* 最近一次发送语音帧号 */
    PHY_UINT16                              uhwSlotNum;                          /*  最近一次发送语音时隙号*/
    PHY_UINT16                              uhwUlTFCI;                           /*  最近一次发送语音的TFCI值*/
    PHY_UINT16                              uhwReseved;
}PHY_MNTN_WCDMA_CS_ERROR_NO_UL_DATA_EVENT_STRU;

/*******************************************************************************
 结构名    : PHY_MNTN_WCDMA_TX_POWER_DROP_EVENT_STRU
 结构说明  : 检测发射功率太低
 1.日    期   : 2015年01月17日
   作    者   : w00286360
   修改内容   : 新建
*******************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                  stHeader;
    PHY_INT16                               shwTxPwr;                           /* 当前发射功率，单位0.1dBm */
    PHY_UINT16                              uhwReseved;
}PHY_MNTN_WCDMA_TX_POWER_DROP_EVENT_STRU;

/*******************************************************************************
 结构名    : PHY_MNTN_WCDMA_PILOT_BER_RISE_EVENT_STRU
 结构说明  : pilot ber抬升的事件
 1.日    期   : 2015年01月17日
   作    者   : w00286360
   修改内容   : 新建
*******************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                  stHeader;
    PHY_UINT16                              uhwPrePilotBer;                     /* 前个窗内的pilot ber，50表示50% */
    PHY_UINT16                              uhwCurrPilotBer;                    /* 后个窗内的pilot ber，10表示10% */
}PHY_MNTN_WCDMA_PILOT_BER_RISE_EVENT_STRU;


/*******************************************************************************
 结构名    : PHY_MNTN_WCDMA_FACH_RA_FAIL_EVENT_STRU
 结构说明  : 随机接入的异常失败检测
 1.日    期   : 2015年01月17日
   作    者   : w00286360
   修改内容   : 新建
*******************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                  stHeader;
    PHY_INT16                               shwRscp;                            /* 随机接入失败时的RSCP 1dBm */
    PHY_INT16                               shwEcn0;                            /* 随机接入失败是的ECN0 1dB */
}PHY_MNTN_WCDMA_FACH_RA_FAIL_EVENT_STRU;


/*******************************************************************************
 结构名    : PHY_MNTN_GOOD_SNR_NOACK_INFO_STRU
 结构说明  : 随机接入的结果检测
 1.日    期   : 2015年01月17日
   作    者   : w00286360
   修改内容   : 新建
*******************************************************************************/
typedef struct
{
    UPHY_BOOL_ENUM_UINT16                   enGoodSnrNoAckFlag;                 /* 是否出现好信号随机接入失败的标记 */
    PHY_INT16                               shwRscp;                            /* 随机接入失败时的RSCP 1dBm */
    PHY_INT16                               shwEcn0;                            /* 随机接入失败是的ECN0 1dB */
    PHY_UINT16                              uhwReserved;
}PHY_MNTN_GOOD_SNR_NOACK_INFO_STRU;


/*******************************************************************************
 结构名    : PHY_MNTN_WCDMA_FACH_RA_INFO_EVENT_STRU
 结构说明  : 随机接入的结果检测
 1.日    期   : 2015年01月17日
   作    者   : w00286360
   修改内容   : 新建
*******************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                  stHeader;
    PHY_UINT16                              uhwFreq;
    PHY_UINT16                              uhwPriScramCode;
    PHY_UINT16                              uhwAckNum;
    PHY_UINT16                              uhwNAckNum;
    PHY_UINT16                              uhwNoAckNum;
    PHY_INT16                               shwPrachInitialTxPower;             /* Preamble初始功率控制,单位dBm */
    PHY_UINT16                              uhwPowerRampStep;                   /* 相邻两个Preamble的功率差值,单位dB */
    PHY_UINT16                              uhwPreambleRetryMax;                /* 一次随机过程发送Preamble的最大允许次数 */
    PHY_INT16                               shwRscp;                            /* 随机接入失败时的RSCP 1dBm */
    PHY_INT16                               shwEcn0;                            /* 随机接入失败是的ECN0 1dB */
    PHY_MNTN_GOOD_SNR_NOACK_INFO_STRU       stGoodSnrNoAck;
}PHY_MNTN_WCDMA_FACH_RA_INFO_EVENT_STRU;



/*******************************************************************************
 结构名    : PHY_ERRLOG_WCDMA_TAS_INFO_STRU
 结构说明  : 上报最近一次天线切换tas关键信息
 1.日    期   : 2015年01月06日
   作    者   : c00242732
   修改内容   : 新建
*******************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                  stHeader;
    PHY_UINT32                              uwAntSwitchSlice;                   /* 天线切换时间戳 */
    PHY_UINT16                              uhwDpdtStatus;                      /* 切换后dpdt状态 */
    PHY_INT16                               shwDeltaValue;                      /* 天线能量差值单位0.125dBm */
    PHY_INT16                               shwCurrAntRscp;                     /* 当前天线能量值单位0.125dBm */
    PHY_UINT16                              uhwSignalState;                     /* 信号good/poor状态 */
    PHY_UINT16                              uhwHappyState;                      /* 物理层happy/unhappy状态 */
    PHY_UINT16                              uhwRrcState;                        /* 系统定时状态:idle/dch */
    PHY_UINT16                              uhwAuthorizeFlag;                   /* W物理层授权状态 */
    PHY_UINT16                              uhwAgentSwitchFlag;                 /* 是否为代理切换 */
}PHY_ERRLOG_WCDMA_TAS_INFO_STRU;

/*******************************************************************************
 结构名    : PHY_ERRLOG_GSM_TAS_INFO_STRU
 结构说明  : 上报最近一次天线切换tas关键信息
 1.日    期   : 2015年01月07日
   作    者   : m00251053
   修改内容   : 新建
*******************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                  stHeader;
    PHY_UINT16                              uhwConnDpdtStatus;                  /* 连接态切换后DPDT状态 */
    PHY_UINT16                              uhwConnTasState;                    /* 连接态MAS算法阶段: Estimate/Compare/Delay */

    PHY_UINT32                              uwWholeSwitchSlice;                 /* 整轮切换时间戳 */
    PHY_UINT16                              uhwWholeSwitchBand;                 /* 整轮切换频段 */
    PHY_UINT16                              uhwWholeSwitchDirection;            /* 整轮切换时DPDT状态从何处切到何处  (ex: 0x23 = 从ant2切到ant3)*/
    PHY_INT16                               shwWholeSwitchBefRSSI;              /* 整轮切换前接收RSSI */
    PHY_INT16                               shwWholeSwitchAftRSSI;              /* 整轮切换后接收RSSI */
    PHY_INT16                               shwWholeSwitchBefTxPower;           /* 整轮切换前发射功率 */
    PHY_INT16                               shwWholeSwitchAftTxPower;           /* 整轮切换后发射功率 */

    PHY_UINT32                              uwSwitchSlice;                      /* 单次切换时间戳 */
    PHY_UINT16                              uhwSwitchRoundCount;                /* 单次切换时比较阶段  (ex: 0x23 = Round2 Count3) */
    PHY_UINT16                              uhwSwitchDirection;                 /* 单次切换时DPDT状态从何处切到何处  (ex: 0x23 = 从ant2切到ant3) */
    PHY_INT16                               shwSwitchBefRSSI;                   /* 单次切换前接收RSSI 单位1dBm */
    PHY_INT16                               shwSwitchAftRSSI;                   /* 单次切换后接收RSSI 单位1dBm */
    PHY_INT16                               shwSwitchBefTxPower;                /* 单次切换前发射功率 单位0.1dBm */
    PHY_INT16                               shwSwitchAftTxPower;                /* 单次切换后发射功率 单位0.1dBm */

    PHY_UINT32                              uwCompareSlice;                     /* 比较阶段时间戳 */
    PHY_UINT16                              uhwCompareBand;                     /* 比较阶段band */
    PHY_INT16                               shwCompareAnt0RSSI;                 /* 比较阶段天线0接收RSSI 单位1dBm */
    PHY_INT16                               shwCompareAnt1RSSI;                 /* 比较阶段天线1接收RSSI 单位1dBm */
    PHY_INT16                               shwCompareAnt2RSSI;                 /* 比较阶段天线2接收RSSI 单位1dBm */
    PHY_INT16                               shwCompareAnt3RSSI;                 /* 比较阶段天线3接收RSSI 单位1dBm */

    PHY_UINT16                              uhwNonConnDpdtStatus;               /* 非连接态切换后DPDT状态 */
    PHY_UINT16                              uhwNonConnTasAlgo;                  /* 非连接态TAS切换算法: Idle/Access/Searching/Agent */
    PHY_UINT16                              uhwIdleSwitchStatus;                /* 切换後是否变成Happy */

    PHY_UINT16                              uhwAuthorizeFlag;                   /* 最新TAS授权状态 TAS=0,MAS=0/TAS=1,MAS=0/TAS=0,MAS=1/TAS=1,MAS=1 */
    PHY_UINT16                              uhwIdleHappyState;                  /* 最新Idle Happy状态: Happy/Unhappy */
    PHY_UINT16                              uhwSignalState;                     /* 最新信号状态: Good/Poor */

    PHY_UINT16                              uhwRlfAuthorizeFlag;                /* RLF时TAS授权状态 */
}PHY_ERRLOG_GSM_TAS_INFO_STRU;


/*******************************************************************************
 结构名    : PHY_ERRLOG_WCDMA_MAS_INFO_STRU
 结构说明  : 上报最近一次天线切换tas关键信息
 1.日    期   : 2015年11月4日
   作    者   : w00181973
   修改内容   : 新建
*******************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                  stHeader;

    PHY_UINT16                              uhwConnDpdtStatus;                  /* 连接态TAS、MAS状态 */
    PHY_UINT16                              uhwConnDpdtAlgo;                    /* 0: Nonblind; 1:Blind */
    PHY_UINT16                              uhwConnTasState;                    /* MAS(TAS) 当前STATE */
    PHY_UINT16                              uhwRsv3;                            /* 四字节对齐 */

    PHY_UINT32                              uwWholeSwitchSlice;                 /* 整轮切换时间戳 */
    PHY_UINT16                              uhwWholeSwitchBand;                 /* 整轮切换时所在BAND */
    PHY_UINT16                              uhwWholeSwitchDirection;            /* 整轮切换方向(从何天线开始,在何天线结束) */
    PHY_INT16                               shwWholeSwitchBefRSCP;              /* 整轮切换开始时接收RSCP能量 */
    PHY_INT16                               shwWholeSwitchAftRSCP;              /* 整轮切换结束时接收RSCP能量 */
    PHY_INT16                               shwWholeSwitchBefTxPower;           /* 整轮切换开始时发射功率 */
    PHY_INT16                               shwWholeSwitchAftTxPower;           /* 整轮切换结束时发射功率 */

    PHY_UINT32                              uwSingleSwitchSlice;                /* 单次切换开始时间戳 */
    PHY_UINT16                              uhwSingleSwitchRoundCount;          /* 单次切换所在轮数 */
    PHY_UINT16                              uhwSingleSwitchDirection;           /* 单次切换方向(从何天线开始,在何天线结束) */
    PHY_INT16                               shwSingleSwitchBefRSCP;             /* 单次切换开始时接收RSCP能量 */
    PHY_INT16                               shwSingleSwitchAftRSCP;             /* 单次切换结束时接收RSCP能量 */
    PHY_INT16                               shwSingleSwitchBefTxPower;          /* 单次切换开始时发射功率 */
    PHY_INT16                               shwSingleSwitchAftTxPower;          /* 单次切换结束时发射功率 */

    PHY_UINT32                              uwCompareSlice;                     /* 比较时间戳 */
    PHY_UINT16                              uhwCompareBand;                     /* 比较所在BAND */
    PHY_INT16                               shwCompareAnt0RSCP;                 /* 天线0能量 */
    PHY_INT16                               shwCompareAnt1RSCP;                 /* 天线1能量 */
    PHY_INT16                               shwCompareAnt2RSCP;                 /* 天线2能量 */
    PHY_INT16                               shwCompareAnt3RSCP;                 /* 天线3能量 */

    PHY_UINT16                              uhwNonConnDpdtStatus;               /* 非连接态TAS、MAS状态 */
    PHY_UINT16                              uhwNonConnDpdtAlgo;                 /* 非连接态算法 */
    PHY_UINT16                              uhwIdleSwitchStatus;                /* IDLE态切换天线后，有没有变HAPPY */

    PHY_UINT16                              uhwAuthorizeFlag;                   /* TAS授权信息 */
    PHY_UINT16                              uhwIdleHappyState;                  /* IDLE态是否HAPPY:0,unhappy; 1,hapy */
    PHY_UINT16                              uhwSignalState;                     /* SIGNAL是否GOOD:0,poor; 1,good */
    PHY_UINT16                              uhwRsv6;                            /* 四字节对齐 */

    PHY_UINT16                              uhwRlfAuthorizeFlag;                /* RL FAIL时TAS授权信息 */
}PHY_ERRLOG_WCDMA_MAS_INFO_STRU;

/*******************************************************************************
 结构名    : PHY_ERRLOG_GSM_MEASUREMENT_REPORT_ERROR_STRU
 结构说明  : 测量报告错误
 1.日    期   : 2015年03月09日
   作    者   : j00178524
   修改内容   : 新建
*******************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU              stHeader;
    VOS_UINT16                          usStrongNcellBsicUnknown;               /* 未同步上的强邻区 */
    VOS_UINT16                          usStrongNcellRxlev;                     /* 未同步上的强邻区的测量值 */
}PHY_ERRLOG_GSM_MEASUREMENT_REPORT_ERROR_STRU;

/*******************************************************************************
 结构名    : PHY_MNTN_WCDMA_DCXO_SAMPLE_ERR_EVENT_STRU
 结构说明  : W DCXO样本点异常的CHR
 1.日    期   : 2015年09月19日
   作    者   : w00286360
   修改内容   : 新建
*******************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                  stHeader;
    PHY_UINT16                              uhwFreq;                            /* 当前工作频点号 */
    PHY_UINT16                              uhwAfcValue;                        /* AFC上报值 */
    PHY_INT32                               swFreqErrPpm;                       /* 当前计算的频偏值 */
    PHY_INT16                               shwTemp;                            /* 当前温度，单位0.1度 */
    PHY_UINT16                              uhwRrcState;                        /* 当前W RRC状态，0:FREE态;1:CPICH态;2:FACH态;3:DPCH态 */
    PHY_INT32                               swMinThreshold;                     /* 最小值的门限 */
    PHY_INT32                               swMaxThreshold;                     /* 最大值的门限 */
    PHY_INT16                               shwRealA0Value;                     /* 真实的A0 */
    PHY_UINT16                              uhwReserved;
}PHY_MNTN_WCDMA_DCXO_SAMPLE_ERR_EVENT_STRU;

/*******************************************************************************
 结构名    : PHY_MNTN_WCDMA_PD_ABNORMAL_EVENT_STRU
 结构说明  : 检测PD异常
 1.日    期   : 2016年01月05日
   作    者   : l00241951
   修改内容   : 新建
*******************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                  stHeader;
    VOS_INT32                               swPdErrorAver;                      /* PD检测误差平均值，单位0.1dBm */
    VOS_INT32                               swPdErrorTemp;                      /* PD检测误差瞬时值，单位0.1dBm */
    VOS_INT16                               shwTxAvrgPwr;                       /* 发射功率平均值 */
    VOS_INT16                               shwFilterDpcchPwr;                  /* 发射功率平均值 */
}PHY_MNTN_WCDMA_PD_ABNORMAL_EVENT_STRU;

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

#endif /* end of phyerrorlog.h */


