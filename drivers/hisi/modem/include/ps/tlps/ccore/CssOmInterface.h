/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : CssOmInterface.h
  版 本 号   : 初稿
  作    者   : w00209181
  生成日期   : 2015年5月25日
  最近修改   :
  功能描述   :
  函数列表   :
  修改历史   :
  1.日    期   : 2015年5月25日
    作    者   : w00209181
    修改内容   : 创建文件

******************************************************************************/
#ifndef __CSSOMINTERFACE_H__
#define __CSSOMINTERFACE_H__


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "CssInterface.h"
#include "CssAtInterface.h"


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define CSS_TIMER_ID_TO_MSG_ID_BASE     (0x20)
#define CSS_OM_MAX_COMM_BAND_NUM           (22)

#define CSS_OM_MAX_NV_MCC_NUM              (3)
#define CSS_OM_MAX_PID_NUM                 (8)
#define CSS_OM_MAX_UPDATE_MCC_NUM          (17)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
    枚举名    : CSS_TIMER_RUN_STA_ENUM
    枚举说明  : 定时器的状态:正在运行,停止
*****************************************************************************/
enum    CSS_TIMER_RUN_STA_ENUM
{
    CSS_TIMER_RUNNING                = 0x00,
    CSS_TIMER_STOPED,
    CSS_TIMER_INVALID,

    CSS_TIMER_BUTT
};
typedef VOS_UINT32   CSS_TIMER_RUN_STA_ENUM_UINT32;

/*****************************************************************************
 结构名    : CSS_MAIN_STATE_ENUM
 结构说明  : CSS层所有并行状态机的主状态的枚举定义
*****************************************************************************/
enum    CSS_OM_MAIN_STATE_ENUM
{
    /*=================== CSS的主状态 ===================*/
    CSS_OM_MS_IDLE                         = 0x0000,
    CSS_OM_MS_SCAN                                 ,           /* 扫频过程中的状态 */
    CSS_OM_MS_STOP_SCAN                            ,           /* 停止扫频过程中状态 */

    CSS_OM_MAIN_STATE_BUTT
};
typedef VOS_UINT16 CSS_OM_MAIN_STATE_ENUM_UINT16;

/*****************************************************************************
 结构名    : CSS_SUB_STATE_ENUM
 结构说明  : CSS层所有并行状态机的子状态的枚举定义
*****************************************************************************/
enum    CSS_OM_SUB_STATE_ENUM
{
    /*=================== CSS的子状态 ===================*/
    CSS_OM_SS_WAIT_START_IND                   = 0x0000,           /* 等待开机的状态，只处理开机消息 */
    CSS_OM_SS_IDLE                                     ,
    CSS_OM_SS_WAIT_SET_WORK_ACTIVE_MODE_CNF            ,           /* 等待设置主模回复状态 */
    CSS_OM_SS_WAIT_START_BG_SRCH_CNF                   ,              /* 等待开始背景搜回复状态 */
    CSS_OM_SS_WAIT_SET_WORK_INACTIVE_MODE_CNF          ,           /* 等待设置从模回复状态 */
    CSS_OM_SS_WAIT_BAND_SCAN_IND                       ,           /* 等待物理层上报扫频结果状态 */
    CSS_OM_SS_WAIT_STOP_SCAN_CNF                       ,           /* 等待物理层上报停止扫频结果状态 */

    CSS_OM_SS_STATE_BUTT
};
typedef VOS_UINT16 CSS_OM_SUB_STATE_ENUM_UINT16;

/*****************************************************************************
 结构名    : CSS_BAND_SCAN_FAIL_REASON_ENUM
 结构说明  :
*****************************************************************************/
enum    CSS_BAND_SCAN_FAIL_REASON_ENUM
{
    CSS_BAND_SCAN_FAIL_REASON_NONE                  = 0x0000,           /* 没有失败原因值 */
    CSS_BAND_SCAN_FAIL_REASON_TYPE_NOT_SUPPORT                                     ,
    CSS_BAND_SCAN_FAIL_REASON_SCANING                       ,           /* 等待设置主模回复状态 */
    CSS_BAND_SCAN_FAIL_REASON_STOP_SCANING                  ,           /* 等待设置从模回复状态 */

    CSS_BAND_SCAN_FAIL_REASON_BUTT
};
typedef VOS_UINT8 CSS_BAND_SCAN_FAIL_REASON_ENUM_UINT8;


enum CSS_OM_MSG_ID_ENUM
{
    ID_CSS_STATE_CHANGE_IND,                            /* _H2ASN_MsgChoice CSS_STATE_CHANGE_IND_STRU */
    ID_CSS_COMM_BAND_NV_INFO_IND,                       /* _H2ASN_MsgChoice CSS_COMM_BAND_NV_INFO_IND_STRU */
    ID_CSS_RAT_THRESHOLD_INFO_IND,                      /* _H2ASN_MsgChoice CSS_RAT_THRESHOLD_INFO_IND_STRU */
    ID_CSS_BAND_SCAN_RESULT_IND,                        /* _H2ASN_MsgChoice CSS_BAND_SCAN_RESULT_IND_STRU */
    ID_CSS_BAND_SCAN_API_INFO_IND,                      /* _H2ASN_MsgChoice CSS_BAND_SCAN_API_INFO_IND_STRU */
    ID_CSS_UE_SUPORT_BAND_INFO_IND,                     /* _H2ASN_MsgChoice CSS_UE_SUPPORT_BAND_INFO_IND_STRU */
    ID_CSS_BAND_SCAN_ABNORMAL_INFO_IND,

    ID_CSS_OM_GET_ONE_PLMN_PREF_FREQ_RSLT,              /* _H2ASN_MsgChoice CSS_OM_GET_ONE_PLMN_PREF_FREQ_RSLT_STRU */
    ID_CSS_OM_GET_PREF_BAND_RSLT,                       /* _H2ASN_MsgChoice CSS_OM_GET_PREF_BAND_RSLT_STRU */
    ID_CSS_OM_PUB_CLOUD_CONTROL_IND,                    /* _H2ASN_MsgChoice CSS_OM_PUB_CLOUD_CONTROL_IND_STRU */

    ID_TI_CSS_WAIT_FOR_SET_INACTIVE_MODE_CNF    = 0x00 + CSS_TIMER_ID_TO_MSG_ID_BASE, /* _H2ASN_MsgChoice CSS_TIMER_INFO_STRU*/
    ID_TI_CSS_WAIT_FOR_SET_ACTIVE_MODE_CNF      = 0x01 + CSS_TIMER_ID_TO_MSG_ID_BASE, /* _H2ASN_MsgChoice CSS_TIMER_INFO_STRU*/
    ID_TI_CSS_WAIT_FOR_SCAN_IND                 = 0x02 + CSS_TIMER_ID_TO_MSG_ID_BASE, /* _H2ASN_MsgChoice CSS_TIMER_INFO_STRU*/
    ID_TI_CSS_WAIT_FOR_STOP_SCAN_CNF            = 0x03 + CSS_TIMER_ID_TO_MSG_ID_BASE, /* _H2ASN_MsgChoice CSS_TIMER_INFO_STRU*/
    ID_TI_CSS_WAIT_AP_UPDATE_MCC_SET_REQ        = 0x04 + CSS_TIMER_ID_TO_MSG_ID_BASE, /* _H2ASN_MsgChoice CSS_TIMER_INFO_STRU*/
    ID_TI_CSS_WAIT_MMC_OR_AS_UPDATE_MCC_SET_REQ = 0x05 + CSS_TIMER_ID_TO_MSG_ID_BASE, /* _H2ASN_MsgChoice CSS_TIMER_INFO_STRU*/
    ID_TI_CSS_WAIT_START_BG_SERACH_CNF          = 0x06 + CSS_TIMER_ID_TO_MSG_ID_BASE, /* _H2ASN_MsgChoice CSS_TIMER_INFO_STRU*/

    ID_CSS_INTRA_MSG_BUTT
};
typedef VOS_UINT32 CSS_OM_MSG_ID_ENUM_UINT32;

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
 结构名     : CSS_OM_BAND_PARA_STRU
 协议表格   :
 ASN.1描述  :
 结构说明   : 配置的BAND，以及该BAND对应的接入技术
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           bitOpLteSupport: 1;
    VOS_UINT8                           bitOpTdsSupport: 1;
    VOS_UINT8                           bitOpWcdmaSupport: 1;
    VOS_UINT8                           bitOpGsmSupport: 1;
    VOS_UINT8                           bitOpSpare: 4;

    VOS_UINT8                           ucBandInd;
    VOS_UINT8                           aucReserved[2];
} CSS_OM_BAND_PARA_STRU;

/*****************************************************************************
 结构名     : CSS_NV_COMM_BAND_CONFIG_STRU
 协议表格   :
 ASN.1描述  :
 结构说明   : 配置的COMM BAND信息时
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucBandNum;
    VOS_UINT8                           aucRsv[3];
    CSS_OM_BAND_PARA_STRU               astBand[CSS_NV_MAX_COMM_BAND_NUM];
} CSS_OM_COMM_BAND_CONFIG_STRU;

/*****************************************************************************
 结构名     : CSS_OM_RSSI_THRESHOLD_STRU
 协议表格   :
 ASN.1描述  :
 结构说明   : 各接入技术对应的可驻留门限以及高能量门限
*****************************************************************************/
typedef struct
{
    VOS_INT16                                   sGHighRssiThresHold;/* G模对应的高能量门限值 */
    VOS_INT16                                   sGLowRssiThresHold;/* G模对应的可驻留能量门限值 */
    VOS_INT16                                   sWHighRssiThresHold;/* W模对应的高能量门限值 */
    VOS_INT16                                   sWLowRssiThresHold;/* W模对应的可驻留能量门限值 */
    VOS_INT16                                   sLHighRssiThresHold;/* L模对应的高能量门限值 */
    VOS_INT16                                   sLLowRssiThresHold;/* L模对应的可驻留能量门限值 */
} CSS_OM_RSSI_THRESHOLD_STRU;

/*****************************************************************************
 结构名    : CSS_TIMER_INFO_STRU
 结构说明  : log出CSS定时器运行情况
 1.日    期   : 2015年05月25日
   作    者   : w0209181
   修改内容   : 新建

*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                              ulMsgId;
    CSS_TIMER_RUN_STA_ENUM_UINT32           enTimerStatus;   /* 定时器状态*/

    VOS_UINT16                              usTimerId;       /* 定时器ID*/
    VOS_UINT16                              usRsv;
    VOS_UINT32                              ulTimerRemainLen;/* 定时器的时长 */
}CSS_TIMER_INFO_STRU;

/*****************************************************************************
 结构名    : CSS_STATE_CHANGE_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CSS_STATE_CHANGE_IND对应的结构体，
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CSS_OM_MSG_ID_ENUM_UINT32                          ulMsgId;                    /*消息名称*/
    CSS_OM_MAIN_STATE_ENUM_UINT16                      enPreMainState;     /* 转状态之前的主状态 */
    CSS_OM_SUB_STATE_ENUM_UINT16                       enPreSubState;      /* 转状态之前的子状态 */
    CSS_OM_MAIN_STATE_ENUM_UINT16                      enCurMainState;     /* 转状态之后的主状态 */
    CSS_OM_SUB_STATE_ENUM_UINT16                       enCurSubState;      /* 转状态之后的子状态 */
}CSS_STATE_CHANGE_IND_STRU;

/*****************************************************************************
 结构名    : CSS_STATE_CHANGE_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CSS_STATE_CHANGE_IND对应的结构体，
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CSS_OM_MSG_ID_ENUM_UINT32               ulMsgId;                    /*消息名称*/
    VOS_UINT32                              ulFileName;
    VOS_UINT32                              ulLineNo;
    CSS_OM_MAIN_STATE_ENUM_UINT16           enCurMainState;     /* 转状态之后的主状态 */
    CSS_OM_SUB_STATE_ENUM_UINT16            enCurSubState;      /* 转状态之后的子状态 */
    CSS_BAND_SCAN_FAIL_REASON_ENUM_UINT8    enBandScanFailReason;   /* 扫频失败的原因值 */
    VOS_UINT8                               ucPara1;
    VOS_UINT8                               ucPara2;
    VOS_UINT8                               ucRsv;
}CSS_BAND_SCAN_ABNORMAL_INFO_IND_STRU;


/*****************************************************************************
 结构名    : CSS_COMM_BAND_NV_INFO_IND_STRU
 协议表格  : NV配置的COMM BAND信息
 ASN.1描述 :
 结构说明  : CSS_COMM_BAND_NV_INFO_IND对应的结构体，
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CSS_OM_MSG_ID_ENUM_UINT32                       ulMsgId;                    /*消息名称*/
    CSS_OM_COMM_BAND_CONFIG_STRU                    stCommBandInfo;
}CSS_COMM_BAND_NV_INFO_IND_STRU;

/*****************************************************************************
 结构名    : CSS_COMM_BAND_NV_INFO_IND_STRU
 协议表格  : NV配置的COMM BAND信息
 ASN.1描述 :
 结构说明  : CSS_COMM_BAND_NV_INFO_IND对应的结构体，
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CSS_OM_MSG_ID_ENUM_UINT32                       ulMsgId;                    /*消息名称*/
    CSS_OM_RSSI_THRESHOLD_STRU                      stBandThresholdInfo;
}CSS_RAT_THRESHOLD_INFO_IND_STRU;

/*****************************************************************************
 结构名    : CSS_OM_BAND_SCAN_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    CSS_BAND_IND_ENUM_UINT16                    enBandInd;                          /* 频带指示 */
    VOS_UINT8                                   ucFreqNum;                          /* 物理层上报的频段数目 */
    VOS_UINT8                                   ucDynMemSize;                       /* 该BAND下动态内存的大小 */
    CSS_FREQ_RANGE_STRU                         astFreqScanResult[CSS_MAX_BAND_FREQ_RANGE_NUM];          /* 频段信息 */
}CSS_OM_BAND_SCAN_INFO_STRU;


/*****************************************************************************
 结构名    : CSS_OM_BAND_SCAN_LIST_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usDynMemSize;
    VOS_UINT8                                       ucBandNum;
    VOS_UINT8                                       aucReserve;
    CSS_OM_BAND_SCAN_INFO_STRU                      astScanRange[CSS_MAX_BAND_NUM];
}CSS_OM_BAND_SCAN_LIST_INFO_STRU;


/*****************************************************************************
 结构名    : CSS_BAND_SCAN_RESULT_IND_STRU
 协议表格  : 本地最终存储的扫频结果
 ASN.1描述 :
 结构说明  : CSS_BAND_SCAN_RESULT_IND对应的结构体，
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CSS_OM_MSG_ID_ENUM_UINT32                        ulMsgId;                    /*消息名称*/
    CSS_OM_BAND_SCAN_LIST_INFO_STRU                  stBandScanResult;
}CSS_BAND_SCAN_RESULT_IND_STRU;

/*****************************************************************************
 结构名    : CSS_BAND_SCAN_API_INFO_IND_STRU
 协议表格  : 接入层调用API来获取扫频结果的信息
 ASN.1描述 :
 结构说明  : CSS_BAND_SCAN_API_INFO_IND对应的结构体，
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CSS_OM_MSG_ID_ENUM_UINT32                       ulMsgId;                    /*消息名称*/
    CSS_RAT_COVERAGE_STRU                           stRatCoverage;
    CSS_BAND_SCAN_LIST_INFO_STRU                    stBandScanResult;
}CSS_BAND_SCAN_API_INFO_IND_STRU;
/*******************************************************************************
 结构名    :CSS_GSM_BAND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : union GSM_BAND_SET_UN成员stBitBand定义
             bit位置1表示该频段有效
1.日    期 : 2012年3月6日
  作    者 : w00176964
  修改内容 : 修改GSM的频段为32位的,便于以后扩展
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          BandGsm450      :1;
    VOS_UINT32                          BandGsm480      :1;
    VOS_UINT32                          BandGsm850      :1;
    VOS_UINT32                          BandGsmP900     :1;
    VOS_UINT32                          BandGsmR900     :1;
    VOS_UINT32                          BandGsmE900     :1;
    VOS_UINT32                          BandGsm1800     :1;
    VOS_UINT32                          BandGsm1900     :1;
    VOS_UINT32                          BandGsm700      :1;
    VOS_UINT32                          BandSpare23     :23;
}CSS_GSM_BAND_STRU;
/*******************************************************************************
 结构名    : CSS_WCDMA_BAND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : union WCDMA_BAND_SET_UN成员stBitBand定义
             bit位置1表示该频段有效
1.日    期 : 2012年3月6日
  作    者 : w00176964
  修改内容 : 修改WCDMA的频段为32位的,支持W下band19
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          BandWCDMA_I_2100      :1;
    VOS_UINT32                          BandWCDMA_II_1900     :1;
    VOS_UINT32                          BandWCDMA_III_1800    :1;
    VOS_UINT32                          BandWCDMA_IV_1700     :1;
    VOS_UINT32                          BandWCDMA_V_850       :1;
    VOS_UINT32                          BandWCDMA_VI_800      :1;
    VOS_UINT32                          BandWCDMA_VII_2600    :1;
    VOS_UINT32                          BandWCDMA_VIII_900    :1;
    VOS_UINT32                          BandWCDMA_IX_J1700    :1;
    VOS_UINT32                          BandSpareBand10       :1;
    VOS_UINT32                          BandWCDMA_XI_1500     :1;
    VOS_UINT32                          BandSpare7            :7;
    VOS_UINT32                          BandWCDMA_XIX_850     :1;
    VOS_UINT32                          BandSpare13           :13;
}CSS_WCDMA_BAND_STRU;

/*******************************************************************************
  结构名    : CSS_GSM_BAND_SET_UN
 结构说明  : GSM支持band能力
 1.日    期: 2015年5月27日
   作    者: w00209181
   修改内容: 新增
*******************************************************************************/
typedef union
{
    VOS_UINT32                          ulBand;

    CSS_GSM_BAND_STRU                       stBitBand;
}CSS_GSM_BAND_SET_UN;
/*******************************************************************************
  结构名    : CSS_WCDMA_BAND_SET_UN
 结构说明  : WCDMA支持band能力
 1.日    期: 2015年5月27日
   作    者: w00209181
   修改内容: 新增
*******************************************************************************/
typedef union
{
    VOS_UINT32                          ulBand;

    CSS_WCDMA_BAND_STRU                     stBitBand;
}CSS_WCDMA_BAND_SET_UN;

/*******************************************************************************
 结构名    : LTE_BAND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LTE的频段定义,aulLteBand[0]代表低32,aulLteBand[1]代表高32个Band,
            例如 用户设置Band1,Band3,则aulLteBand[0]=0x05,aulLteBand[1]=0x00
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          aulLteBand[2];
}CSS_LTE_BAND_STRU;

/*****************************************************************************
 结构名    : CSS_UE_SUPPORT_FREQ_BAND_STRU
 结构说明  : ue 支持band能力
 1.日    期: 2015年5月27日
   作    者: w00209181
   修改内容: 新增
*****************************************************************************/
typedef struct
{
    CSS_WCDMA_BAND_SET_UN                   unWcdmaBand;                            /* wcdma当前设置支持的频段 */
    CSS_GSM_BAND_SET_UN                     unGsmBand;                              /* gsm当前设置支持的频段 */
    CSS_LTE_BAND_STRU                       stLteBand;                              /* lte当前设置支持的频段 */
}CSS_UE_SUPPORT_FREQ_BAND_STRU;


/*****************************************************************************
 结构名    : CSS_BAND_SCAN_API_INFO_IND_STRU
 协议表格  : 接入层调用API来获取扫频结果的信息
 ASN.1描述 :
 结构说明  : CSS_BAND_SCAN_API_INFO_IND对应的结构体，
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CSS_OM_MSG_ID_ENUM_UINT32                       ulMsgId;                    /*消息名称*/
    CSS_UE_SUPPORT_FREQ_BAND_STRU                   stUeSupportBand;
}CSS_UE_SUPPORT_BAND_INFO_IND_STRU;

typedef struct
{
    VOS_UINT8                           aucMccId[2];
    VOS_UINT8                           aucRsv[2];
}CSS_OM_MCC_ID_STRU;

typedef struct
{
    VOS_INT32                           phTimer;            /* Timer句柄 */
    VOS_UINT16                          usName;             /* 即 IMSA_TIMER_ID_ENUM_UINT16*/
    VOS_UINT16                          usPara;             /* 即 IMSA_TIMER_ID_ENUM_UINT16*/
    VOS_UINT8                           ucMode;             /* timer work mode
                                                               VOS_RELTIMER_LOOP   -- start periodically
                                                               VOS_RELTIMER_NOLOOP -- start once time */
    VOS_UINT8                           ucResv[3];
    VOS_UINT32                          ulTimerLen;         /* Timer时长(UNIT: ms) */
}CSS_OM_TIMER_STRU;


typedef struct
{
    VOS_UINT32                          ulPid;
    VOS_UINT16                          usMccNum;                         /* 正在更新的MCC总个数 */
    VOS_UINT8                           ucIsUpdating;
    VOS_UINT8                           aucUpdated[CSS_OM_MAX_UPDATE_MCC_NUM];/* 是否已经更新 */
    CSS_OM_MCC_ID_STRU                  astMcc[CSS_OM_MAX_UPDATE_MCC_NUM];   /* 正在更新的MCC列表 */
    CSS_OM_TIMER_STRU                   stTimer;
}CSS_OM_MCC_UPDATE_STRU;



typedef struct
{
    VOS_UINT8                                     ucMccNum;
    VOS_UINT8                                     aucRsv[3];
    VOS_UINT32                                    pstHead;
    VOS_UINT32                                    pstTail;
}CSS_OM_PUB_PREF_FREQ_INFO_STRU;


typedef struct
{
    VOS_UINT8                           ucCloudEnable;
    VOS_UINT8                           ucPrefFreqEnable;                 /*是否从云端获取频点信息*/
    VOS_UINT8                           aucRsv[1];

    VOS_UINT8                           aucVersion[MCC_INFO_VERSION_LEN];
    VOS_UINT32                          ulMemUsedLen; 
    CSS_OM_MCC_ID_STRU                  astNvMcc[CSS_OM_MAX_NV_MCC_NUM];
    CSS_OM_MCC_UPDATE_STRU              astMccUpdate[CSS_OM_MAX_PID_NUM];
    CSS_OM_MCC_UPDATE_STRU              stApMccUpdate;
    CSS_OM_PUB_PREF_FREQ_INFO_STRU      stPrefMccList;                    /* 用来保存预置频点和频段 */
}CSS_OM_CLOUD_PUB_CONTROL_STRU;



/*****************************************************************************
 结构名     : CSS_OM_AS_GET_PREF_FREQ_INFO_STRU
 协议表格   :
 ASN.1描述  :
 结构说明   : ID_CSS_OM_AS_GET_PREF_FREQ_INFO_IND对应的结构体，
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CSS_OM_MSG_ID_ENUM_UINT32                     ulMsgId;                    /*消息名称*/

    CSS_RESULT_ENUM_UINT32                        ulResult;

    CSS_RAT_TYPE_ENUM_UINT8                       enRat;
    VOS_UINT8                                     aucRsv[3];
    VOS_UINT32                                    ulPlmnIdNum;
    CSS_PLMN_ID_STRU                              astPlmn[CSS_MAX_PLMN_ID_NUM];
    CSS_PREF_FREQ_INFO_STRU                       astPrefFreq[CSS_MAX_PLMN_ID_NUM];
}CSS_OM_AS_GET_PREF_FREQ_INFO_STRU;

/*****************************************************************************
 结构名     : CSS_OM_AS_GET_PREF_BAND_INFO_STRU
 协议表格   :
 ASN.1描述  :
 结构说明   : ID_CSS_OM_AS_GET_PREF_BAND_INFO_IND对应的结构体，
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CSS_OM_MSG_ID_ENUM_UINT32                     ulMsgId;                    /*消息名称*/

    CSS_RESULT_ENUM_UINT32                        ulResult;

    CSS_RAT_TYPE_ENUM_UINT8                       enRat;
    VOS_UINT8                                     aucRsv[3];
    VOS_UINT32                                    ulPlmnIdNum;
    CSS_PLMN_ID_STRU                              astPlmn[CSS_MAX_PLMN_ID_NUM];
    CSS_PREF_BAND_INFO_STRU                       astPrefBand[CSS_MAX_PLMN_ID_NUM];
}CSS_OM_AS_GET_PREF_BAND_INFO_STRU;


/*****************************************************************************
 结构名     : CSS_OM_GET_ONE_PLMN_PREF_FREQ_RSLT_STRU
 协议表格   :
 ASN.1描述  :
 结构说明   : ID_CSS_OM_GET_ONE_PLMN_PREF_FREQ_RSLT对应的结构体，
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CSS_OM_MSG_ID_ENUM_UINT32                     ulMsgId;                    /*消息名称*/
    CSS_RAT_TYPE_ENUM_UINT8                       enRat;
    VOS_UINT8                                     ucRslt;
    VOS_UINT8                                     ucRsv;
    VOS_UINT8                                     ucPlmnInNum;
    CSS_PLMN_ID_STRU                              astPlmn[CSS_MAX_PREF_PLMN_NUM];
    CSS_PREF_FREQ_INFO_STRU                       stPrefFreq;
}CSS_OM_GET_ONE_PLMN_PREF_FREQ_RSLT_STRU;

/*****************************************************************************
 结构名     : CSS_OM_GET_PREF_BAND_RSLT_STRU
 协议表格   :
 ASN.1描述  :
 结构说明   : ID_CSS_OM_GET_PREF_BAND_RSLT对应的结构体，
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CSS_OM_MSG_ID_ENUM_UINT32                     ulMsgId;                    /*消息名称*/
    CSS_RAT_TYPE_ENUM_UINT8                       enRat;
    VOS_UINT8                                     ucRslt;
    VOS_UINT8                                     ucRsv;
    VOS_UINT8                                     ucPlmnInNum;
    CSS_PLMN_ID_STRU                              astPlmn[CSS_MAX_PREF_PLMN_NUM];
    VOS_UINT32                                    aulResult[CSS_MAX_PREF_PLMN_NUM];
    VOS_UINT32                                    ulPlmnOutNum;
    CSS_PREF_BAND_INFO_STRU                       astPrefBand[CSS_MAX_PREF_PLMN_NUM];
}CSS_OM_GET_PREF_BAND_RSLT_STRU;


/*****************************************************************************
 结构名     : CSS_OM_PUB_CLOUD_CONTROL_IND_STRU
 协议表格   :
 ASN.1描述  :
 结构说明   : ID_CSS_OM_PUB_CLOUD_CONTROL_IND对应的结构体，
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CSS_OM_MSG_ID_ENUM_UINT32                     ulMsgId;                    /*消息名称*/
    CSS_OM_CLOUD_PUB_CONTROL_STRU                 stPubCloudCtrl;
}CSS_OM_PUB_CLOUD_CONTROL_IND_STRU;





typedef struct
{
    VOS_UINT32                          ulMsgId;                                /*_H2ASN_MsgChoice_Export CSS_OM_MSG_ID_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          CSS_OM_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}CSS_OM_INTERFACE_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    CSS_OM_INTERFACE_MSG_DATA           stMsgData;
} CssOmInterface_MSG;


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

#endif /* end of ComInterface.h */

