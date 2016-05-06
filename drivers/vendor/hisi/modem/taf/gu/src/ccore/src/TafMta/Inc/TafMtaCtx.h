/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafMtaCtx.h
  版 本 号   : 初稿
  作    者   : 闫志吉
  生成日期   : 2012年6月27日
  最近修改   :
  功能描述   : MTA模块全局变量声明
  函数列表   :
  修改历史   :
  1.日    期   : 2012年6月27日
    作    者   : Y00213812
    修改内容   : A-GPS项目新增

******************************************************************************/

#ifndef __TAFMTACTX_H__
#define __TAFMTACTX_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "TafMtaTimerMgmt.h"
#include "AtMtaInterface.h"
#include "MtaPhyInterface.h"

#include "NasErrorLog.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
/* 等待消息结果的队列长度。由于起定时器时，会同时保存消息，故该值与TAF_MTA_CTX_MAX_TIMER_NUM一致 */
#define TAF_MTA_MAX_CMD_BUFFER_QUEUE_SIZE                   (5)

#define TAF_MTA_REFCLOCK_DEFAULT_FREQ                       (49152000)
#define TAF_MTA_REFCLOCK_DEFAULT_PRECISION                  (100)

#define TAF_MTA_INVALID_MCC                                 (0x0FFF)

#define TAF_MTA_ISMCOEX_BANDWIDTH_NUM                       (AT_MTA_ISMCOEX_BANDWIDTH_NUM)



/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
 枚举名    : TAF_MTA_WAIT_FREQ_CLT_CNF_FLAG_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 频点收集回复标记枚举
*****************************************************************************/
enum TAF_MTA_WAIT_FREQ_CLT_CNF_FLAG_ENUM
{
    TAF_MTA_WAIT_FREQ_CLT_CNF_FLAG_NULL          = 0x00,
    TAF_MTA_WAIT_FREQ_CLT_CNF_FLAG_GAS           = 0x01,
    TAF_MTA_WAIT_FREQ_CLT_CNF_FLAG_WAS           = 0x02,
    TAF_MTA_WAIT_FREQ_CLT_CNF_FLAG_LRRC          = 0x04,
    TAF_MTA_WAIT_FREQ_CLT_CNF_FLAG_GUL           = 0x07,
    TAF_MTA_WAIT_FREQ_CLT_CNF_FLAG_BUTT
};
typedef VOS_UINT8 TAF_MTA_WAIT_FREQ_CLT_CNF_FLAG_ENUM_UINT8;

/*****************************************************************************
 枚举名    : TAF_MTA_WAIT_NETWORK_INFO_CNF_FLAG_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 网络信息收集回复标记枚举
*****************************************************************************/
enum TAF_MTA_WAIT_NETWORK_INFO_CNF_FLAG_ENUM
{
    TAF_MTA_WAIT_NETWORK_INFO_CNF_FLAG_NULL          = 0x00,
    TAF_MTA_WAIT_NETWORK_INFO_CNF_FLAG_NAS           = 0x01,
    TAF_MTA_WAIT_NETWORK_INFO_CNF_FLAG_PHY           = 0x02,
    TAF_MTA_WAIT_NETWORK_INFO_CNF_FLAG_BUTT
};
typedef VOS_UINT8 TAF_MTA_WAIT_NETWORK_INFO_CNF_FLAG_ENUM_UINT8;

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
结构名    : TAF_MTA_XML_TEXT_STRU
结构说明  : 记录XML码流的内存地址的结构
1.日    期  : 2012年06月28日
  作    者  : y00213812
  修改内容  : V7R1C50 A_GPS项目新增结构
*****************************************************************************/
typedef struct
{
    VOS_CHAR                           *pcBufHead;                              /* 存放XML码流内存的首地址 */
    VOS_CHAR                           *pcBufCur;                               /* 当前空闲内存的首地址 */
}TAF_MTA_XML_TEXT_STRU;

/*****************************************************************************
 结构名    : TAF_MTA_REFCLOCK_INFO_STRU
 结构说明  : 记录GPS参考时钟状态信息的结构

  1.日    期   : 2013年07月22日
    作    者   : l00198894
    修改内容   : V9R1 AGPS
*****************************************************************************/
typedef struct
{
    AT_MTA_CMD_RPT_FLG_ENUM_UINT8       enRptFlg;                               /* 命令上报开关标志 */
    VOS_UINT8                           aucReserved1[3];                        /* 保留位 */
    VOS_UINT32                          ulFreq;                                 /* GPS参考时钟的频率值，单位Hz */
    VOS_UINT32                          ulPrecision;                            /* 当前GPS参考时钟的精度，单位ppb */
    PHY_MTA_REFCLOCK_STATUS_ENUM_UINT16 enStatus;                               /* 时钟频率锁定状态 */
    VOS_UINT8                           aucReserved2[2];                        /* 保留位 */
} TAF_MTA_REFCLOCK_INFO_STRU;

/*****************************************************************************
 结构名    : TAF_MTA_AGPS_CTX_STRU
 结构说明  : 记录AGPS相关功能信息的上下文结构

  1.日    期  : 2012年06月28日
    作    者  : y00213812
    修改内容  : V7R1C50 A_GPS项目新增结构
  1.日    期   : 2013年07月22日
    作    者   : l00198894
    修改内容   : V9R1 AGPS
*****************************************************************************/
typedef struct
{
    TAF_MTA_XML_TEXT_STRU               stXmlText;                              /* 存放XML码流的内存 */
    TAF_MTA_REFCLOCK_INFO_STRU          stRefClockInfo;                         /* GPS参考时钟状态信息 */
    TAF_NVIM_ECID_TL2GSM_CFG_STRU       stEcidCfg;                              /* ECID命令配置 */
}TAF_MTA_AGPS_CTX_STRU;

/*****************************************************************************
 结构名    : TAF_MTA_CMD_BUFFER_STRU
 结构说明  : 缓存命令的信息结构
 1.日    期   : 2012年07月09日
   作    者   : Y00213812
   修改内容   : V7R1C50 A_GPS项目新增结构
*****************************************************************************/
typedef struct
{
    TAF_MTA_TIMER_ID_ENUM_UINT32        enTimerId;
    VOS_UINT8                          *pucMsgInfo;
    VOS_UINT32                          ulMsgInfoLen;
}TAF_MTA_CMD_BUFFER_STRU;

/*****************************************************************************
 结构名    : TAF_MTA_RF_LCD_CTX_STRU
 结构说明  : RF&LCD相关上下文
 1.日    期   : 2014年03月04日
   作    者   : j00174725
   修改内容   : RF&LCD INTRUSION项目新增结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usNewMipiClk;                           /* 保存最新的MIPICLK值 */
    VOS_UINT16                          usReportMipiClk;                        /* 保存已经上报过的的MIPICLK值 */
    VOS_UINT32                          ulTimerInterVal;                        /* 保存MIPICLK上报的时间间隔 */
    VOS_UINT16                          usEnableBitMap;                         /* 使能开关，每个bit代表不同的算法，非0代表使能 */
    VOS_UINT8                           aucReserved2[2];                        /* 保留位 */
}TAF_MTA_RF_LCD_CTX_STRU;


/*****************************************************************************
 结构名    : TAF_NETWORK_INFO_CLT_CTX_STRU
 结构说明  : 网络信息
 1.日    期   : 2015年12月01日
   作    者   : g00322017
   修改内容   : 项目新增结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usCellid;        /* 小区id */
    VOS_UINT16                          usDlFreqInfo;    /* 下行频率 */
    VOS_UINT16                          usUlFreqInfo;    /* 上行频率 */
    VOS_UINT16                          usBandInfo;      /* BAND */
    VOS_INT16                           sRxPower;        /* Rxlev(GSM), RSCP(UMTS,TDS),Rsrp(LTE) */
    VOS_INT16                           sChanelQuality;  /* Rxqual(GSM), EcN0(UMTS), Scale(TDS),RsrQ(LTE) */
    VOS_UINT8                           ucIsExsitRrcConn;
    VOS_UINT8                           aucRsv[3];
    VOS_INT32                           lTxPwr;          /* 上行发射功率, 0.1dBm精度 */
    VOS_UINT32                          ulSavedSlice;    /* 当前上报时间 */
}TAF_NETWORK_INFO_CLT_CTX_STRU;

/*****************************************************************************
 结构名    : MTA_LRRC_COEX_PARA_STRU
 结构说明  : LTE&WIFI共存参数结构体

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
typedef AT_MTA_COEX_PARA_STRU TAF_MTA_COEX_PARA_STRU;

/*****************************************************************************
 结构名    : TAF_MTA_INFO_CLT_CTX_STRU
 结构说明  : 信息收集相关上下文
 1.日    期   : 2015年07月22日
   作    者   : y00270069
   修改内容   : 项目新增结构
*****************************************************************************/
typedef struct
{
    NAS_INFO_CLT_CLOUD_FREQ_BAND_EVENT_STRU    *pstFreqInfoCltCtx;
    TAF_NETWORK_INFO_CLT_CTX_STRU               stNetworkInfo;
    VOS_UINT8                                   ucWaitFreqCltCnfFlag;
    VOS_UINT8                                   ucWaitNetworkInfoCnfFlag;
    VOS_UINT8                                   aucRsv[2];
}TAF_MTA_INFO_CLT_CTX_STRU;

/*****************************************************************************
 结构名    : TAF_MTA_NETMON_GSM_INFO_STRU
 结构说明  : GSM查询时相关信息
 1.日    期   : 2015年10月19日
   作    者   : zwx247453
   修改内容   : 项目新增结构
*****************************************************************************/
typedef struct
{
    MTA_AT_NETMON_GSM_STATE_ENUM_UINT32         enNetMonGsmState;               /* GSM 查询所处在的查询状态 */
    MTA_AT_NETMON_CELL_INFO_STRU                stNetMonCellInfoCnf;            /* GSM 小区信息的全局变量 */
}TAF_MTA_NETMON_GSM_INFO_STRU;

/*****************************************************************************
 结构名    : TAF_MTA_CONTEXT_STRU
 结构说明  : TAF MTA 模块运行上下文
1.日    期  : 2012年06月28日
  作    者  : y00213812
  修改内容  : V7R1C50 A_GPS项目新增结构

*****************************************************************************/
typedef struct
{
    /* 记录AGPS XML码流的上下文资源 */
    TAF_MTA_AGPS_CTX_STRU           stAgpsCtx;

    /* MTA当前正在运行的定时器资源 */
    TAF_MTA_TIMER_CTX_STRU          astTimerCtx[TAF_MTA_CTX_MAX_TIMER_NUM];

    /* MTA命令消息缓存 */
    TAF_MTA_CMD_BUFFER_STRU         astCmdBufferQueue[TAF_MTA_MAX_CMD_BUFFER_QUEUE_SIZE];

    TAF_MTA_RF_LCD_CTX_STRU         stMtaRfLcdCtx;

#if(FEATURE_ON == FEATURE_LTE)
    TAF_MTA_COEX_PARA_STRU           astIsmCoex[TAF_MTA_ISMCOEX_BANDWIDTH_NUM];
#endif

    TAF_MTA_INFO_CLT_CTX_STRU       stInfoCltCtx;

    TAF_MTA_NETMON_GSM_INFO_STRU   stNetmonGsmInfo;

}TAF_MTA_CONTEXT_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/
/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern TAF_MTA_AGPS_CTX_STRU*  TAF_MTA_GetMtaAgpsCtxAddr( VOS_VOID );

extern TAF_MTA_CONTEXT_STRU*  TAF_MTA_GetMtaCtxAddr( VOS_VOID );

extern TAF_MTA_TIMER_CTX_STRU*  TAF_MTA_GetTimerCtxAddr( VOS_VOID );

extern VOS_VOID  TAF_MTA_InitCmdBufferQueue(
            TAF_MTA_CMD_BUFFER_STRU            *pstCmdBufferQueue);

extern TAF_MTA_CMD_BUFFER_STRU  *TAF_MTA_GetCmdBufferQueueAddr( VOS_VOID );

extern VOS_VOID  TAF_MTA_DelItemInCmdBufferQueue(
            TAF_MTA_TIMER_ID_ENUM_UINT32        enTimerId);

extern VOS_VOID  TAF_MTA_SaveItemInCmdBufferQueue(
            TAF_MTA_TIMER_ID_ENUM_UINT32        enTimerId,
            VOS_UINT8                          *pucMsgInfo,
            VOS_UINT32                          ulMsgInfoLen);

extern TAF_MTA_CMD_BUFFER_STRU  *TAF_MTA_GetItemFromCmdBufferQueue(
            TAF_MTA_TIMER_ID_ENUM_UINT32                enTimerId);


extern VOS_VOID TAF_MTA_InitRefClockInfo(
    TAF_MTA_REFCLOCK_INFO_STRU         *pstRefClockInfo
);

extern TAF_MTA_REFCLOCK_INFO_STRU* TAF_MTA_GetRefClockInfo(VOS_VOID);

VOS_VOID  TAF_MTA_InitRfLcdIntrusionCtx(
    TAF_MTA_RF_LCD_CTX_STRU            *pstRfLcdCtx
);
TAF_MTA_RF_LCD_CTX_STRU* TAF_MTA_GetRfLcdCtxAddr( VOS_VOID );


VOS_VOID TAF_MTA_InitEcidCfg(
    TAF_NVIM_ECID_TL2GSM_CFG_STRU      *pstEcidCfg);

TAF_NVIM_ECID_TL2GSM_CFG_STRU* TAF_MTA_GetEcidCfg(VOS_VOID);

#if(FEATURE_ON == FEATURE_LTE)
TAF_MTA_COEX_PARA_STRU*  TAF_MTA_GetIsmCoexAddr( VOS_VOID );
VOS_VOID  TAF_MTA_InitIsmCoex(
    TAF_MTA_COEX_PARA_STRU              *pstMtaCoexPara
);
#endif
#if (FEATURE_ON == FEATURE_PTM)
VOS_VOID  TAF_MMA_InitInfoCltCtx(
    TAF_MTA_INFO_CLT_CTX_STRU          *pstInfoCltCtx
);
VOS_VOID  TAF_MMA_AllocFreqInfoCltCtx(VOS_VOID);
VOS_VOID  TAF_MMA_FreeFreqInfoCltCtx(VOS_VOID);
TAF_MTA_INFO_CLT_CTX_STRU*  TAF_MTA_GetInfoCltAddr(VOS_VOID);
VOS_UINT8 TAF_MTA_GetWaitFreqCltCnfFlag(VOS_VOID);
VOS_VOID TAF_MTA_SetWaitFreqCltCnfFlag(
    TAF_MTA_WAIT_FREQ_CLT_CNF_FLAG_ENUM_UINT8    enFreqCltCnf
);
VOS_VOID TAF_MTA_ClrWaitFreqCltCnfFlag(
    TAF_MTA_WAIT_FREQ_CLT_CNF_FLAG_ENUM_UINT8    enFreqCltCnf
);
VOS_VOID TAF_MTA_ClrAllWaitFreqCltCnfFlag(VOS_VOID);
VOS_VOID  TAF_MMA_ClearNetworkInfo(VOS_VOID);
VOS_VOID TAF_MTA_ClrAllWaitNetworkInfoCnfFlag(VOS_VOID);
VOS_UINT8 TAF_MTA_GetWaitNetworkInfoCnfFlag(VOS_VOID);
VOS_VOID TAF_MTA_SetWaitNetworkInfoCnfFlag(
    TAF_MTA_WAIT_NETWORK_INFO_CNF_FLAG_ENUM_UINT8           enNetworkInfoCltCnfFlag
);
VOS_VOID TAF_MTA_ClrWaitNetworkInfoCnfFlag(
    TAF_MTA_WAIT_NETWORK_INFO_CNF_FLAG_ENUM_UINT8           enNetworkInfoCltCnfFlag
);
#endif

VOS_VOID  TAF_MTA_InitNetmonGsmInfo(
    TAF_MTA_NETMON_GSM_INFO_STRU       *pstNetmonGsmInfo
);
MTA_AT_NETMON_GSM_STATE_ENUM_UINT32  TAF_MTA_GetNetmonGsmState(VOS_VOID);
VOS_VOID  TAF_MTA_SetNetmonGsmState(
    MTA_AT_NETMON_GSM_STATE_ENUM_UINT32 enNetMonGsmState
);
MTA_AT_NETMON_CELL_INFO_STRU*  TAF_MTA_GetNetmonCellInfo(VOS_VOID);

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif


