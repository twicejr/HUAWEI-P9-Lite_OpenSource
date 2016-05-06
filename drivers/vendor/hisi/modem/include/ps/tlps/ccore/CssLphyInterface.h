/******************************************************************************


        @(#)Copyright(C)2015,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : CssLphyInterface.h
    Description : 描述CSS与Lphy之间的接口
    History     :
      1.  sunbing   265702  2015-03-31  Draft Enact

******************************************************************************/
#ifndef __CSSLPHYINTERFACE_H__
#define __CSSLPHYINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#ifndef LPS_RTT
#include "vos.h"
#include "LPSCommon.h"
#endif
#include "TLPhyInterface.h"


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/

#define CSS_LPHY_MAX_FREQ_NUM    100
#define CSS_LPHY_MSG_HDR                (0x00000B00)         /* PS_MSG_ID_CSS_TO_LPHY_BASE begin with  */
#define LPHY_CSS_MSG_HDR                (0x00001E95)         /* PS_MSG_ID_LPHY_TO_CSS_BASE begin with  */

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/

/*****************************************************************************
 枚举名    : CSS_LPHY_MSG_ID_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : CSS <-> LPHY 接口消息ID
*****************************************************************************/
enum CSS_LPHY_MSG_ID_ENUM
{
    ID_CSS_LPHY_BAND_SCAN_REQ                   = CSS_LPHY_MSG_HDR + 0x00, /* _H2ASN_MsgChoice CSS_LPHY_BAND_SCAN_REQ_STRU */
    ID_CSS_LPHY_STOP_BAND_SCAN_REQ              = CSS_LPHY_MSG_HDR + 0x01, /* _H2ASN_MsgChoice CSS_LPHY_STOP_BAND_SCAN_REQ_STRU */
    ID_CSS_LPHY_SET_WORK_MODE_REQ               = CSS_LPHY_MSG_HDR + 0x02, /* _H2ASN_MsgChoice CSS_LPHY_SET_WORK_MODE_REQ_STRU */
    ID_CSS_LPHY_START_BG_SEARCH_REQ             = CSS_LPHY_MSG_HDR + 0x03, /* _H2ASN_MsgChoice CSS_LPHY_START_BG_SEARCH_REQ_STRU */
    ID_CSS_LPHY_STOP_BG_SEARCH_REQ              = CSS_LPHY_MSG_HDR + 0x04, /* _H2ASN_MsgChoice CSS_LPHY_STOP_BG_SEARCH_REQ_STRU */

    ID_CSS_LPHY_BAND_SCAN_IND                   = LPHY_CSS_MSG_HDR + 0x21, /* _H2ASN_MsgChoice CSS_LPHY_BAND_SCAN_IND_STRU */
    ID_CSS_LPHY_STOP_BAND_SCAN_CNF              = LPHY_CSS_MSG_HDR + 0x22, /* _H2ASN_MsgChoice CSS_LPHY_STOP_BAND_SCAN_CNF_STRU */
    ID_CSS_LPHY_SET_WORK_MODE_CNF               = LPHY_CSS_MSG_HDR + 0x23, /* _H2ASN_MsgChoice CSS_LPHY_SET_WORK_MODE_CNF_STRU */
    ID_CSS_LPHY_START_BG_SEARCH_CNF             = LPHY_CSS_MSG_HDR + 0x24, /* _H2ASN_MsgChoice CSS_LPHY_START_BG_SEARCH_CNF_STRU */
    ID_CSS_LPHY_STOP_BG_SEARCH_CNF              = LPHY_CSS_MSG_HDR + 0x25, /* _H2ASN_MsgChoice CSS_LPHY_STOP_BG_SEARCH_CNF_STRU */

};
typedef  VOS_UINT32  CSS_LPHY_MSG_ID_ENUM_UINT32;


/*********************************************************
 枚举名    : CSS_LPHY_BAND_IND_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : Band指示枚举
**********************************************************/
enum CSS_LPHY_BAND_IND_ENUM
{
    CSS_LPHY_BAND_IND_NONE,
    CSS_LPHY_BAND_IND_1                   = 1 ,
    CSS_LPHY_BAND_IND_2,
    CSS_LPHY_BAND_IND_3,
    CSS_LPHY_BAND_IND_4,
    CSS_LPHY_BAND_IND_5,
    CSS_LPHY_BAND_IND_6,
    CSS_LPHY_BAND_IND_7,
    CSS_LPHY_BAND_IND_8,
    CSS_LPHY_BAND_IND_9,
    CSS_LPHY_BAND_IND_10,
    CSS_LPHY_BAND_IND_11,
    CSS_LPHY_BAND_IND_12,
    CSS_LPHY_BAND_IND_13,
    CSS_LPHY_BAND_IND_14,
    CSS_LPHY_BAND_IND_15,
    CSS_LPHY_BAND_IND_16,
    CSS_LPHY_BAND_IND_17                = 17,
    CSS_LPHY_BAND_IND_18,
    CSS_LPHY_BAND_IND_19,
    CSS_LPHY_BAND_IND_20,
    CSS_LPHY_BAND_IND_21,
    CSS_LPHY_BAND_IND_22,
    CSS_LPHY_BAND_IND_23,
    CSS_LPHY_BAND_IND_24,
    CSS_LPHY_BAND_IND_25,
    CSS_LPHY_BAND_IND_26,
    CSS_LPHY_BAND_IND_27,
    CSS_LPHY_BAND_IND_28,
    CSS_LPHY_BAND_IND_29,
    CSS_LPHY_BAND_IND_30,
    CSS_LPHY_BAND_IND_31,
    CSS_LPHY_BAND_IND_32,
    CSS_LPHY_BAND_IND_33                = 33,
    CSS_LPHY_BAND_IND_34,
    CSS_LPHY_BAND_IND_35,
    CSS_LPHY_BAND_IND_36,
    CSS_LPHY_BAND_IND_37,
    CSS_LPHY_BAND_IND_38,
    CSS_LPHY_BAND_IND_39,
    CSS_LPHY_BAND_IND_40,
    CSS_LPHY_BAND_IND_41,
    CSS_LPHY_BAND_IND_42,
    CSS_LPHY_BAND_IND_43,
//    CSS_LPHY_BAND_IND_64                = 64,

    /* 非标频段begin */
/*    CSS_LPHY_BAND_IND_101  = 101,
    CSS_LPHY_BAND_IND_102  = 102,
    CSS_LPHY_BAND_IND_103  = 103,
    CSS_LPHY_BAND_IND_104  = 104,
    CSS_LPHY_BAND_IND_105  = 105,
    CSS_LPHY_BAND_IND_106  = 106,
    CSS_LPHY_BAND_IND_107  = 107,
    CSS_LPHY_BAND_IND_108  = 108,
    CSS_LPHY_BAND_IND_109  = 109,
    CSS_LPHY_BAND_IND_110  = 110,
    CSS_LPHY_BAND_IND_111  = 111,
    CSS_LPHY_BAND_IND_112  = 112,
    CSS_LPHY_BAND_IND_113  = 113,
    CSS_LPHY_BAND_IND_114  = 114,
    CSS_LPHY_BAND_IND_115  = 115,
    CSS_LPHY_BAND_IND_116  = 116,*/
    /* 非标频段end */

    CSS_LPHY_BAND_IND_BUTT
};
typedef VOS_UINT16 CSS_LPHY_BAND_IND_ENUM_UINT16;

/*****************************************************************************
 枚举名    : CSS_LPHY_WORK_MODE_TYPE_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : LTE RTT工作模式
*****************************************************************************/
enum CSS_LPHY_WORK_MODE_TYPE_ENUM
{
    CSS_LPHY_WORK_MODE_TYPE_ACTIVE                = 0,                         /* LTE处在工作态 */
    CSS_LPHY_WORK_MODE_TYPE_INACTIVE              = 1,                         /* LTE处在测量态 */
    CSS_LPHY_WORK_MODE_TYPE_BUTT
};
typedef VOS_UINT16 CSS_LPHY_WORK_MODE_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : CSS_LPHY_DSDS_RFSHARED_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  :DSDS特性新增，RF shared是否使能
*****************************************************************************/
enum CSS_LPHY_DSDS_RFSHARED_ENUM
{
    CSS_LPHY_DSDS_RFSHARED_DISABLE           = 0,    /* 不启动 */
    CSS_LPHY_DSDS_RFSHARED_ENABLE            = 1,    /* 启动 */
    CSS_LPHY_DSDS_RFSHARED_BUTT
};
typedef VOS_UINT16  CSS_LPHY_DSDS_RFSHARED_ENUM_UINT16;

/*****************************************************************************
 枚举名    : CSS_LPHY_RESULT_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 物理层原语操作结果数据结构
*****************************************************************************/
enum CSS_LPHY_RESULT_ENUM
{
    CSS_LPHY_RESULT_SUCC                 = 0,                /* 操作成功 */
    CSS_LPHY_RESULT_FAIL ,                                   /* 操作失败 */
    CSS_LPHY_RESULT_BUTT
};
typedef VOS_UINT16    CSS_LPHY_RESULT_ENUM_UINT16;

/*****************************************************************************
 枚举名    : CSS_LPHY_BAND_SCAN_TYPE_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : 扫频类型
*****************************************************************************/
enum CSS_LPHY_BAND_SCAN_TYPE_ENUM
{
    CSS_LPHY_BAND_SCAN_TYPE_INIT                  = 0,                         /* 初始扫频 */
    CSS_LPHY_BAND_SCAN_TYPE_CONT                  = 1,                         /* 后续扫频 */
    CSS_LPHY_BAND_SCAN_TYPE_IRAT                  = 2,                         /* 只有使用该类型的扫频时，物理层才会上报RSSI值 */
    CSS_LPHY_BAND_SCAN_TYPE_BUTT
};
typedef VOS_UINT16 CSS_LPHY_BAND_SCAN_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : CSS_LPHY_LTE_MODE_TYPE_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : LTE模式类型
*****************************************************************************/
enum CSS_LPHY_LTE_MODE_TYPE_ENUM
{
    CSS_LPHY_LTE_MODE_TYPE_FDD                = 0,                             /* LTE FDD 制式 */
    CSS_LPHY_LTE_MODE_TYPE_TDD                = 1,                             /* LTE TDD 制式 */
    CSS_LPHY_LTE_MODE_TYPE_BUTT
};
typedef VOS_UINT16 CSS_LPHY_LTE_MODE_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : CSS_LPHY_RAT_TYPE_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : 系统接入类型
*****************************************************************************/
enum CSS_LPHY_RAT_TYPE_ENUM
{
    CSS_LPHY_RAT_TYPE_LTE                    = 0,                              /* LTE */
    CSS_LPHY_RAT_TYPE_GSM                    = 1,                              /* GSM */
    CSS_LPHY_RAT_TYPE_WCDMA                  = 2,                              /* WCDMA */
    CSS_LPHY_RAT_TYPE_TD_SCDMA               = 3,                              /* TD-SCDMA */
    CSS_LPHY_RAT_TYPE_CDMA                   = 4,                              /* CDMA */

    CSS_LPHY_RAT_TYPE_BUTT
};
typedef VOS_UINT16 CSS_LPHY_RAT_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : CSS_LPHY_BGSCFG_TYPE_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : 指示启动背景搜是正常搜网还是真实背景搜
*****************************************************************************/
enum CSS_LPHY_BGSCFG_TYPE_ENUM
{
    CSS_LPHY_BGSCFG_TYPE_BGS                    = 0,
    CSS_LPHY_BGSCFG_TYPE_DSDS                   = 1,
    CSS_LPHY_BGSCFG_TYPE_BUTT
};
typedef VOS_UINT16 CSS_LPHY_BGSCFG_TYPE_ENUM_UINT16;


/*****************************************************************************
  5 Struct
*****************************************************************************/

/*****************************************************************************
 结构名    : CSS_LPHY_FREQ_BAND_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 频带信息数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16              usFreqBegin;
    VOS_UINT16              usFreqEnd;
}CSS_LPHY_FREQ_RANGE_INFO_STRU;


/*****************************************************************************
 结构名    : CSS_LPHY_BAND_SCAN_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 协议栈指示物理层扫频数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                  /*_H2ASN_Skip*/
    CSS_LPHY_MSG_ID_ENUM_UINT32                     ulMsgId;                        /*_H2ASN_Skip*/     /* 原语消息ID */
    VOS_UINT16                                      usOpId;                         /* 操作标识符 */
    VOS_UINT16                                      bitOpLteSupport: 1;             /* enBandInd是否支持L制式*/
    VOS_UINT16                                      bitOpWcdmaSupport: 1;           /* enBandInd是否支持G制式*/
    VOS_UINT16                                      bitOpGsmSupport: 1;             /* enBandInd是否支持W制式*/
    VOS_UINT16                                      bitOpTdsSupport: 1;             /* enBandInd是否支持T制式*/
    VOS_UINT16                                      bitOpSpace: 12;                 /* 保留字段 */
    CSS_LPHY_BAND_SCAN_TYPE_ENUM_UINT16             enBandScanType;                 /* 扫频类型 */
    VOS_UINT16                                      usRsv;
    CSS_LPHY_BAND_IND_ENUM_UINT16                   enBandInd;                      /* 频带指示 */
    CSS_LPHY_LTE_MODE_TYPE_ENUM_UINT16              enLteModeType;                  /* 指示频点所属的制式类型, FDD或TDD */
    CSS_LPHY_FREQ_RANGE_INFO_STRU                   stFreqRangeInfo;                /* 频段信息 */
}CSS_LPHY_BAND_SCAN_REQ_STRU;

/*****************************************************************************
 结构名    : CSS_LPHY_STOP_BAND_SCAN_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 协议栈指示物理层停止扫频数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                  /*_H2ASN_Skip*/
    CSS_LPHY_MSG_ID_ENUM_UINT32                     ulMsgId;                        /*_H2ASN_Skip*/     /* 原语消息ID */
    VOS_UINT16                                      usOpId;                         /* 操作标识符 */
    VOS_UINT16                                      usRsv;
}CSS_LPHY_STOP_BAND_SCAN_REQ_STRU;

/*****************************************************************************
 结构名    : CSS_LPHY_FREQ_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 频率和能量结果数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usCentralFreq;      /* 中心频点 */
    VOS_INT16                                   lRssi;              /* RSSI的值 */
}CSS_LPHY_FREQ_INFO_STRU;

/*****************************************************************************
 结构名    : CSS_LPHY_BAND_SCAN_RESULT_LIST_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 扫频结果数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      bitOpLteSupport: 1;             /* enBandInd是否支持L制式*/
    VOS_UINT16                                      bitOpWcdmaSupport: 1;           /* enBandInd是否支持G制式*/
    VOS_UINT16                                      bitOpGsmSupport: 1;             /* enBandInd是否支持W制式*/
    VOS_UINT16                                      bitOpTdsSupport: 1;             /* enBandInd是否支持T制式*/
    VOS_UINT16                                      bitOpSpace: 12;                 /* 保留字段 */
    VOS_UINT16                                      usRsv;
    CSS_LPHY_BAND_IND_ENUM_UINT16                   enBandInd;                      /* 频带指示 */
    VOS_UINT16                                      usFreqRangeNum;                 /* 物理层上报的频率数目 */
    CSS_LPHY_FREQ_INFO_STRU                         astFreqScanResult[CSS_LPHY_MAX_FREQ_NUM];          /* 频段信息 */
}CSS_LPHY_BAND_SCAN_RESULT_LIST_STRU;

/*****************************************************************************
 结构名    : CSS_LPHY_BAND_SCAN_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 物理层指示扫频结果数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    CSS_LPHY_MSG_ID_ENUM_UINT32                   ulMsgId;                      /*_H2ASN_Skip*/     /* 原语消息ID */
    VOS_UINT16                                    usOpId;                       /* 操作标识符 */
    VOS_UINT16                                    usNoRfValid;                  /* DSDS特性NORF指示 */
    CSS_LPHY_BAND_SCAN_RESULT_LIST_STRU           stBandScanResult;             /* 扫频结果 */
}CSS_LPHY_BAND_SCAN_IND_STRU;

/*****************************************************************************
 结构名    : CSS_LPHY_SET_WORK_MODE_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CSS_LPHY_SET_WORK_MODE_REQ_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    CSS_LPHY_MSG_ID_ENUM_UINT32               ulMsgId;                          /*_H2ASN_Skip*/
    VOS_UINT16                                usOpId;
    CSS_LPHY_WORK_MODE_TYPE_ENUM_UINT16       enWorkModeType;                   /* 指示LTE工作模式，0:处于工作态，1:处于测量态 */
    VOS_UINT16                                usRsv;
    CSS_LPHY_DSDS_RFSHARED_ENUM_UINT16        enDsdsRfShardFlg;
}CSS_LPHY_SET_WORK_MODE_REQ_STRU;

/*****************************************************************************
 结构名    : CSS_LPHY_STOP_BAND_SCAN_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CSS_LPHY_STOP_BAND_SCAN_CNF_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    CSS_LPHY_MSG_ID_ENUM_UINT32               ulMsgId;                          /*_H2ASN_Skip*/
    VOS_UINT16                                usOpId;
    CSS_LPHY_RESULT_ENUM_UINT16               enStopBandScanRslt;
}CSS_LPHY_STOP_BAND_SCAN_CNF_STRU;

/*****************************************************************************
 结构名    : CSS_LPHY_SET_WORK_MODE_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CSS_LPHY_SET_WORK_MODE_CNF_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    CSS_LPHY_MSG_ID_ENUM_UINT32               ulMsgId;                          /*_H2ASN_Skip*/
    VOS_UINT16                                usOpId;
    CSS_LPHY_RESULT_ENUM_UINT16               enWorkModeCfgRslt;
}CSS_LPHY_SET_WORK_MODE_CNF_STRU;

/*****************************************************************************
 结构名    : CSS_LPHY_START_BG_SEARCH_REQ_STRU
 协议表格  :
 ASN.1描述 : 在背景搜索开始时下发该原语
 结构说明  : ID_CSS_LPHY_START_BG_SEARCH_REQ消息结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    CSS_LPHY_MSG_ID_ENUM_UINT32                   ulMsgId;                      /*_H2ASN_Skip*/
    VOS_UINT16                                    usOpId;
    CSS_LPHY_RAT_TYPE_ENUM_UINT16                 enStartBGSearchRat;           /* L主模时，此处填写BG搜哪个模式；L从模时，此处固定填写为L模 */
    CSS_LPHY_BGSCFG_TYPE_ENUM_UINT16              enBsgCfgType;                 /*DSDS新增*/
    VOS_UINT16                                    usRsv;
}CSS_LPHY_START_BG_SEARCH_REQ_STRU;

/*****************************************************************************
 结构名    : CSS_LPHY_BG_SEARCH_START_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CSS_LPHY_BG_SEARCH_START_CNF_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    CSS_LPHY_MSG_ID_ENUM_UINT32                   ulMsgId;                      /*_H2ASN_Skip*/
    VOS_UINT16                                    usOpId;
    CSS_LPHY_RESULT_ENUM_UINT16                   enResult;
}CSS_LPHY_START_BG_SEARCH_CNF_STRU;

/*****************************************************************************
 结构名    : CSS_LPHY_STOP_BG_SEARCH_REQ_STRU
 协议表格  : 在背景搜索或者是背景搜索挂起时，dsp收到该请求后需要停止背景搜索
 ASN.1描述 :
 结构说明  : CSS_LPHY_STOP_BG_SEARCH_REQ_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    CSS_LPHY_MSG_ID_ENUM_UINT32                   ulMsgId;                      /*_H2ASN_Skip*/
    VOS_UINT16                                    usOpId;
    VOS_UINT8                                     aucRsv[2];
}CSS_LPHY_STOP_BG_SEARCH_REQ_STRU;

/*****************************************************************************
 结构名    : CSS_LPHY_STOP_BG_SEARCH_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CSS_LPHY_STOP_BG_SEARCH_CNF_STRU数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    CSS_LPHY_MSG_ID_ENUM_UINT32                   ulMsgId;                      /*_H2ASN_Skip*/
    VOS_UINT16                                    usOpId;
    CSS_LPHY_RESULT_ENUM_UINT16                   enResult;
}CSS_LPHY_STOP_BG_SEARCH_CNF_STRU;



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

#endif /* end of 发送模块+接收模块+Interface.h */



