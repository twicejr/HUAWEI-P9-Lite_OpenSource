/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : AtXpdsInterface.h
  版 本 号   : 初稿
  作    者   : 闫志吉
  生成日期   : 2012年6月27日
  最近修改   :
  功能描述   : XPDS模块与AT模块跨核通信消息ID、消息结构声明
  函数列表   :
  修改历史   :
  1.日    期   : 2012年6月27日
    作    者   : Y00213812
    修改内容   : A-GPS项目新增

******************************************************************************/

#ifndef __ATXPDSINTERFACE_H__
#define __ATXPDSINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "PsTypeDef.h"
#include "AtMnInterface.h"

/*****************************************************************************
  2 宏定义
*****************************************************************************/


#define TAF_MSG_CDMA_MAX_SV_NUM                             (12)
#define TAF_MSG_CDMA_MAX_EPH_PRN_NUM                        (32)
#define TAF_MSG_CDMA_MAX_ALM_PRN_NUM                        (32)
#define AT_XPDS_MEID_DATA_LEN                               (7)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : AT_XPDS_MSG_TYPE_ENUM
 结构说明  : AT与XPDS消息接口枚举
1.日    期  : 2012年06月28日
  作    者  : y00213812
  修改内容  : V7R1C50 A_GPS项目新增结构

*****************************************************************************/
enum AT_XPDS_MSG_TYPE_ENUM
{
    /* 消息名称 */                      /* 消息ID */        /* 备注, 生成ASN */

    ID_AT_XPDS_GPS_START_REQ               = 0x0001, /* _H2ASN_MsgChoice AT_XPDS_GPS_START_REQ_STRU */
    ID_XPDS_AT_GPS_START_CNF               = 0x0002, /* _H2ASN_MsgChoice XPDS_AT_RESULT_CNF_STRU */
    ID_AT_XPDS_GPS_CFG_MPC_ADDR_REQ        = 0x0003, /* _H2ASN_MsgChoice AT_XPDS_GPS_CFG_MPC_ADDR_REQ_STRU */
    ID_XPDS_AT_GPS_CFG_MPC_ADDR_CNF        = 0x0004, /* _H2ASN_MsgChoice XPDS_AT_RESULT_CNF_STRU */
    ID_AT_XPDS_GPS_CFG_PDE_ADDR_REQ        = 0x0005, /* _H2ASN_MsgChoice AT_XPDS_GPS_CFG_PDE_ADDR_REQ_STRU */
    ID_XPDS_AT_GPS_CFG_PDE_ADDR_CNF        = 0x0006, /* _H2ASN_MsgChoice XPDS_AT_RESULT_CNF_STRU */
    ID_AT_XPDS_GPS_CFG_POSITION_MODE_REQ   = 0x0007, /* _H2ASN_MsgChoice AT_XPDS_GPS_CFG_POSITION_MODE_REQ_STRU */
    ID_XPDS_AT_GPS_CFG_MODE_CNF            = 0x0008, /* _H2ASN_MsgChoice XPDS_AT_RESULT_CNF_STRU */
    ID_AT_XPDS_GPS_QRY_REFLOC_INFO_REQ     = 0x0009, /* _H2ASN_MsgChoice AT_XPDS_GPS_QRY_REFLOC_INFO_REQ_STRU */
    ID_XPDS_AT_GPS_REFLOC_INFO_CNF         = 0x000a, /* _H2ASN_MsgChoice XPDS_AT_GPS_REFLOC_INFO_CNF_STRU */
    ID_AT_XPDS_GPS_QRY_TIME_INFO_REQ       = 0x000b, /* _H2ASN_MsgChoice AT_XPDS_GPS_QRY_TIME_INFO_REQ_STRU */
    ID_XPDS_AT_GPS_TIME_INFO_IND           = 0x000c, /* _H2ASN_MsgChoice XPDS_AT_GPS_SYNC_TIME_IND_STRU */
    ID_AT_XPDS_GPS_STOP_REQ                = 0x000d, /* _H2ASN_MsgChoice AT_XPDS_GPS_STOP_REQ_STRU */
    ID_XPDS_AT_GPS_STOP_CNF                = 0x000e, /* _H2ASN_MsgChoice XPDS_AT_RESULT_CNF_STRU */

    ID_AT_XPDS_GPS_PRM_INFO_RSP            = 0x1001, /* _H2ASN_MsgChoice AT_XPDS_GPS_PRM_INFO_RSP_STRU */
    ID_AT_XPDS_GPS_POS_INFO_RSP            = 0x1003, /* _H2ASN_MsgChoice AT_XPDS_GPS_POS_INFO_RSP_STRU */
    ID_AT_XPDS_GPS_REPLY_NI_REQ            = 0x1005, /* _H2ASN_MsgChoice AT_XPDS_GPS_REPLY_NI_RSP_STRU */

    ID_XPDS_AT_GPS_ION_INFO_IND            = 0x2002, /* _H2ASN_MsgChoice XPDS_AT_GPS_ION_INFO_IND_STRU */
    ID_XPDS_AT_GPS_EPH_INFO_IND            = 0x2004, /* _H2ASN_MsgChoice XPDS_AT_GPS_EPH_INFO_IND_STRU */
    ID_XPDS_AT_GPS_ALM_INFO_IND            = 0x2006, /* _H2ASN_MsgChoice XPDS_AT_GPS_ALM_INFO_IND_STRU */
    ID_XPDS_AT_GPS_PDE_POSI_INFO_IND       = 0x2008, /* _H2ASN_MsgChoice XPDS_AT_GPS_PDE_POSI_INFO_IND_STRU */
    ID_XPDS_AT_GPS_NI_SESSION_IND          = 0x200a, /* _H2ASN_MsgChoice XPDS_AT_GPS_NI_SESSION_IND_STRU */
    ID_XPDS_AT_GPS_START_REQ               = 0x200c, /* _H2ASN_MsgChoice XPDS_AT_GPS_START_REQ_STRU */
    ID_XPDS_AT_GPS_CANCEL_IND              = 0x200e, /* _H2ASN_MsgChoice XPDS_AT_GPS_CANCEL_IND_STRU */
    ID_XPDS_AT_GPS_ACQ_ASSIST_DATA_IND     = 0x2012, /* _H2ASN_MsgChoice XPDS_AT_GPS_ACQ_ASSIST_DATA_IND_STRU */
    ID_XPDS_AT_GPS_DEL_ASSIST_DATA_IND     = 0x2014, /* _H2ASN_MsgChoice XPDS_AT_GPS_DEL_ASSIST_DATA_IND_STRU */
    ID_XPDS_AT_GPS_ABORT_IND               = 0x2016, /* _H2ASN_MsgChoice XPDS_AT_GPS_ABORT_IND_STRU */
    ID_XPDS_AT_GPS_NI_CP_START             = 0x2018, /* _H2ASN_MsgChoice XPDS_AT_GPS_NI_CP_START_STRU */
    ID_XPDS_AT_GPS_NI_CP_STOP              = 0x201a, /* _H2ASN_MsgChoice XPDS_AT_GPS_NI_CP_STOP_STRU */

    ID_XPDS_AT_AP_DATA_CALL_REQ            = 0x3001, /* _H2ASN_MsgChoice XPDS_AT_AP_DATA_CALL_REQ_STRU */
    ID_AT_XPDS_AP_DATA_CALL_STATUS_IND     = 0x3002, /* _H2ASN_MsgChoice AT_XPDS_AP_DATA_CALL_STATUS_IND_STRU */
    ID_XPDS_AT_AP_SERVER_BIND_REQ          = 0x3003, /* _H2ASN_MsgChoice XPDS_AT_AP_SERVER_BIND_REQ_STRU */
    ID_AT_XPDS_AP_SERVER_BIND_STATUS_IND   = 0x3004, /* _H2ASN_MsgChoice AT_XPDS_AP_SERVER_BIND_STATUS_IND_STRU */
    ID_XPDS_AT_AP_REVERSE_DATA_IND         = 0x3005, /* _H2ASN_MsgChoice XPDS_AT_AP_REVERSE_DATA_IND_STRU */
    ID_AT_XPDS_AP_FORWARD_DATA_IND         = 0x3006, /* _H2ASN_MsgChoice AT_XPDS_AP_FORWARD_DATA_IND_STRU */
    ID_AT_XPDS_UTS_TEST_START_REQ          = 0x3007, /* _H2ASN_MsgChoice AT_XPDS_MSG_STRU */
    ID_XPDS_AT_GPS_UTS_TEST_START_REQ      = 0x3008, /* _H2ASN_MsgChoice AT_XPDS_MSG_STRU */
    ID_AT_XPDS_UTS_TEST_STOP_REQ           = 0x3009, /* _H2ASN_MsgChoice AT_XPDS_MSG_STRU */
    ID_XPDS_AT_GPS_UTS_TEST_STOP_REQ       = 0x300a, /* _H2ASN_MsgChoice AT_XPDS_MSG_STRU */

    ID_XPDS_AT_UTS_GPS_POS_INFO_IND        = 0x300b, /* _H2ASN_MsgChoice XPDS_AT_UTS_GPS_POS_INFO_IND_STRU */
    ID_XPDS_AT_GPS_OM_TEST_START_REQ       = 0x300c, /* _H2ASN_MsgChoice XPDS_AT_GPS_OM_TEST_START_REQ_STRU */
    ID_XPDS_AT_GPS_OM_TEST_STOP_REQ        = 0x300d, /* _H2ASN_MsgChoice XPDS_AT_GPS_OM_TEST_STOP_REQ_STRU */

    /* 最后一条消息 */
    ID_AT_XPDS_MSG_TYPE_BUTT

};
typedef VOS_UINT32 AT_XPDS_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : XPDS_AT_RESULT_ENUM
 结构说明  : XPDS向AT回复的结果码枚举
1.日    期  : 2015年08月21日
  作    者  : g00261581
  修改内容  : CDMA A_GPS项目新增结构
*****************************************************************************/
enum XPDS_AT_RESULT_ENUM
{
    /* 与AT模块对应的标准错误码 */
    XPDS_AT_RESULT_NO_ERROR                      = 0x000000,                     /* 消息处理正常 */
    XPDS_AT_RESULT_ERROR,                                                        /* 消息处理出错 */
    XPDS_AT_RESULT_INCORRECT_PARAMETERS,
    XPDS_AT_RESULT_OPTION_TIMEOUT,

    /* 预留对应AT标准命令错误码 */

    XPDS_AT_RESULT_BUTT
};
typedef VOS_UINT32 XPDS_AT_RESULT_ENUM_UINT32;

enum AT_XPDS_AGPS_DATA_CALL_CTRL_ENUM
{
    AT_XPDS_AGPS_DATA_CALL_CTRL_RELEASE,
    AT_XPDS_AGPS_DATA_CALL_CTRL_CONNECT,

    AT_XPDS_AGPS_DATA_CALL_CTRL_BUTT
};
typedef VOS_UINT32 AT_XPDS_AGPS_DATA_CALL_CTRL_ENUM_UINT32;

enum AT_XPDS_SERVER_MODE_ENUM
{
    AT_XPDS_SERVER_MODE_NULL,
    AT_XPDS_SERVER_MODE_MPC,
    AT_XPDS_SERVER_MODE_PDE,
    AT_XPDS_SERVER_MODE_BUTT
};
typedef VOS_UINT32 AT_XPDS_SERVER_MODE_ENUM_UINT32;

enum AT_XPDS_SERVER_BIND_STATUS_ENUM
{
    AT_XPDS_SERVER_BIND_STATUS_IDLE,
    AT_XPDS_SERVER_BIND_STATUS_CONNECT,
    AT_XPDS_SERVER_BIND_STATUS_BUTT
};
typedef VOS_UINT32 AT_XPDS_SERVER_BIND_STATUS_ENUM_UINT32;

enum AT_XPDS_DATA_CALL_STATUS_ENUM
{
    AT_XPDS_DATA_CALL_STATUS_IDLE,
    AT_XPDS_DATA_CALL_STATUS_CONNECT,
    AT_XPDS_DATA_CALL_STATUS_BUTT
};
typedef VOS_UINT32 AT_XPDS_DATA_CALL_STATUS_ENUM_UINT32;


enum XPDS_AT_SYNC_TIME_ENUM
{
    XPDS_AT_SYNC_TIME_NOT_VALID,         /* not valid */
    XPDS_AT_SYNC_TIME_VALID,             /* valid */

    XPDS_AT_SYNC_TIME_BUTT
};
typedef VOS_UINT32 XPDS_AT_SYNC_TIME_ENUM_UINT32;

enum AT_XPDS_REPLY_SYNC_TIME_ENUM
{
    AT_XPDS_REPLY_SYNC_TIME_INFO            = 1,           /* reply time sync info */
    AT_XPDS_REPLY_SYNC_TIME_AND_ASSIST_DATA = 2,           /* reply time sync info and GPS assist data */
    AT_XPDS_REPLY_FORCE_SYNC_TIME           = 3,

    AT_XPDS_REPLY_SYNC_BUTT
};
typedef VOS_UINT8 AT_XPDS_REPLY_SYNC_TIME_ENUM_UINT8;

enum XPDS_AT_ABORT_POS_REASON_ENUM
{
    XPDS_AT_ABORT_POS_REASON_ENUM_MODEM_NOT_START              = 0,
    XPDS_AT_ABORT_POS_REASON_ENUM_PARA_INCORRECT               = 1,
    XPDS_AT_ABORT_POS_REASON_ENUM_DATA_LINK_ERR                = 2,
    XPDS_AT_ABORT_POS_REASON_ENUM_NETWORK_NO_RSP               = 3,
    XPDS_AT_ABORT_POS_REASON_ENUM_BUTT
};
typedef VOS_UINT16 XPDS_AT_ABORT_POS_REASON_ENUM_UINT16;


/** ****************************************************************************
 * Name        : TAF_MSG_CDMA_GPS_FIX_QUALITY_ENUM_UINT8
 *
 * Description :
 *******************************************************************************/
enum TAF_MSG_CDMA_GPS_FIX_QUALITY_ENUM
{
    TAF_MSG_CDMA_GPS_FIX_QUALITY_UNKNOWN                    = 0x00, /**< Fix uses information from GPS satellites only. */
    TAF_MSG_CDMA_GPS_FIX_QUALITY_GPS                        = 0x01, /**< Fix uses information from GPS satellites and also a differential GPS (DGPS) station. */
    TAF_MSG_CDMA_GPS_FIX_QUALITY_DGPS                       = 0x02,
    TAF_MSG_CDMA_GPS_FIX_QUALITY_MAX                        = 0x10,
    TAF_MSG_CDMA_GPS_FIX_QUALITY_ENUM_BUTT                  = 0x11
};
typedef VOS_UINT8 TAF_MSG_CDMA_GPS_FIX_QUALITY_ENUM_UINT8;

/** ****************************************************************************
 * Name        : TAF_MSG_CDMA_GPS_FIX_TYPE_ENUM_UINT8
 *
 * Description :
 *******************************************************************************/
enum TAF_MSG_CDMA_GPS_FIX_TYPE_ENUM
{
    TAF_MSG_CDMA_GPS_FIX_UNKNOWN        = 0x00,
    TAF_MSG_CDMA_GPS_FIX_2D             = 0x01,
    TAF_MSG_CDMA_GPS_FIX_3D             = 0x02,
    TAF_MSG_CDMA_GPS_FIX_TYPE_MAX       = 0x10,
    TAF_MSG_CDMA_GPS_FIX_TYPE_ENUM_BUTT = 0x11
};
typedef VOS_UINT8 TAF_MSG_CDMA_GPS_FIX_TYPE_ENUM_UINT8;

/** ****************************************************************************
 * Name        : TAF_MSG_CDMA_GPS_SELECTION_TYPE_ENUM_UINT8
 *
 * Description :
 *******************************************************************************/
enum TAF_MSG_CDMA_GPS_SELECTION_TYPE_ENUM
{
    TAF_MSG_CDMA_GPS_FIX_SELECTION_UNKNOWN                  = 0x00,
    TAF_MSG_CDMA_GPS_FIX_SELECTION_AUTO                     = 0x01,
    TAF_MSG_CDMA_GPS_FIX_SELECTION_MANUAL                   = 0x02,
    TAF_MSG_CDMA_GPS_FIX_SELECTION_TYPE_MAX                 = 0x10,
    TAF_MSG_CDMA_GPS_SELECTION_TYPE_ENUM_BUTT               = 0x11
};
typedef VOS_UINT8 TAF_MSG_CDMA_GPS_SELECTION_TYPE_ENUM_UINT8;


/** ****************************************************************************
 * Name        : AT_XPDS_GPS_NI_REQ_REPLY_RESULT_ENUM
 *
 * Description :
 *******************************************************************************/
enum AT_XPDS_GPS_NI_REQ_REPLY_RESULT_ENUM
{
    AT_XPDS_GPS_NI_REQ_REPLY_RESULT_REJECT                  = 0,
    AT_XPDS_GPS_NI_REQ_REPLY_RESULT_ACCEPT                  = 1,

    AT_XPDS_GPS_NI_REQ_REPLY_RESULT_ENUM_BUTT
};
typedef VOS_UINT8 AT_XPDS_GPS_NI_REQ_REPLY_RESULT_ENUM_UINT8;

/** ****************************************************************************
 * Name        : AT_XPDS_GPS_NI_REQ_REJECT_TYPE_ENUM
 *
 * Description :
 *******************************************************************************/
enum AT_XPDS_GPS_NI_REQ_REJECT_TYPE_ENUM
{
    AT_XPDS_GPS_NI_REQ_REJECT_TYPE_INVALID                  = 0,
    AT_XPDS_GPS_NI_REQ_REJECT_TYPE_TIMER_OUT                = 1,   /* GPS应答第三方定位请求超时 */
    AT_XPDS_GPS_NI_REQ_REJECT_TYPE_USER_DENIED              = 2,   /* 用户拒绝第三方定位请求 */

    AT_XPDS_GPS_RESP_NI_REQ_REJECT_TYPE_ENUM_BUTT           = 0x11
};
typedef VOS_UINT8 AT_XPDS_GPS_NI_REQ_REJECT_TYPE_ENUM_UINT8;

/*****************************************************************************
枚举名    : TAF_XPDS_CALL_TYPE_ENUM
枚举说明  : 数据上报通道类型

  1.日    期   : 2015年7月20日
    作    者   : g00256031
    修改内容   : 新增枚举
*****************************************************************************/
enum TAF_XPDS_CALL_TYPE_ENUM
{
    TAF_XPDS_USER_PLANE            = 0,
    TAF_XPDS_CTRL_PLANE,
    TAF_XPDS_CALL_BUTT
};
typedef VOS_UINT8 TAF_XPDS_CALL_TYPE_ENUM_UINT8;


/*****************************************************************************
枚举名    : TAF_XPDS_FIX_MODE_ENUM_UINT8
枚举说明  : 数据上报通道类型

  1.日    期   : 2015年7月20日
    作    者   : g00256031
    修改内容   : 新增枚举
*****************************************************************************/
enum TAF_XPDS_FIX_MODE_ENUM
{
    TAF_XPDS_UNKOWN_MODE            = 0,
    TAF_XPDS_MSA_MODE,
    TAF_XPDS_MSB_MODE,
    TAF_XPDS_MSS_MODE,
    TAF_XPDS_AFLT_MODE,
    TAF_XPDS_MODE_BUTT
};
typedef VOS_UINT8 TAF_XPDS_FIX_MODE_ENUM_UINT8;

/** ****************************************************************************
 * Name        : TAF_XPDS_MPC_TO_MS_MSG_TYPE_ENUM_UINT8
 *
 * Description :
 *******************************************************************************/
enum TAF_XPDS_NOTIFT_AND_VERIFY_INDICATOR_ENUM
{
    TAF_XPDS_NOTIFT_AND_VERIFY_INDICATOR_BOTH_NONE      = 0,
    TAF_XPDS_NOTIFT_AND_VERIFY_INDICATOR_BOTH_NEED      = 1,
    TAF_XPDS_NOTIFT_AND_VERIFY_INDICATOR_NOTIFY_ONLY    = 2,

    TAF_XPDS_NOTIFT_AND_VERIFY_INDICATOR_BUTT
};

typedef VOS_UINT8 TAF_XPDS_NOTIFT_AND_VERIFY_INDICATOR_ENUM_UINT8;


/** ****************************************************************************
 * Name        : TAF_XPDS_IS801_MODE_ENUM_UINT8
 *
 * Description :
 *******************************************************************************/
enum TAF_XPDS_IS801_MODE_ENUM
{
    TAF_XPDS_IS801_MODE_MSA_ONLY    = 0,
    TAF_XPDS_IS801_MODE_MSB_ONLY    = 1,
    TAF_XPDS_IS801_MODE_MSA_PREFER  = 2,
    TAF_XPDS_IS801_MODE_MSB_PREFER  = 3,

    TAF_XPDS_IS801_MODE_BUTT
};

typedef VOS_UINT8 TAF_XPDS_IS801_MODE_ENUM_UINT8;

/** ****************************************************************************
 * Name        : TAF_XPDS_POS_TECH_INDICATOR_ENUM_UINT8
 *
 * Description :
 *******************************************************************************/
enum TAF_XPDS_POS_TECH_INDICATOR_ENUM
{
    TAF_XPDS_POS_TECH_INDICATOR_IS801                   = 0,
    TAF_XPDS_POS_TECH_INDICATOR_RETURN_SID_NID          = 1,
    TAF_XPDS_POS_TECH_INDICATOR_NOTIFY_CACHED_POS       = 2,

    TAF_XPDS_POS_TECH_INDICATOR_BUTT
};

typedef VOS_UINT8 TAF_XPDS_POS_TECH_INDICATOR_ENUM_UINT8;

/*****************************************************************************
枚举名    : AT_XPDS_TYPE_ENUM
枚举说明  : 数据上报通道类型

  1.日    期   : 2015年7月20日
    作    者   : g00256031
    修改内容   : 新增枚举
*****************************************************************************/
enum TAF_XPDS_INITIAL_TYPE_ENUM
{
    TAF_XPDS_SI                    = 0,
    TAF_XPDS_NI,
    TAF_XPDS_INITIAL_BUTT
};
typedef VOS_UINT32 TAF_XPDS_INITIAL_TYPE_ENUM_UINT32;

/*****************************************************************************
枚举名    : TAF_XPDS_GPS_START_MODE_ENUM
枚举说明  : GPS启动类型

  1.日    期   : 2015年12月17日
    作    者   : y00174758
    修改内容   : 新增枚举
*****************************************************************************/
enum TAF_XPDS_GPS_START_MODE_ENUM
{
    TAF_XPDS_GPS_START_MODE_COLD,
    TAF_XPDS_GPS_START_MODE_HOT,
    TAF_XPDS_GPS_START_MODE_BUTT
};
typedef VOS_UINT8 TAF_XPDS_GPS_START_MODE_ENUM_UINT8;

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
结构名    : AT_XPDS_MSG_STRU
结构说明  : AT模块与XPDS模块间的消息结构
1.日    期  : 2015年08月21日
  作    者  : g00261581
  修改内容  : CDMA A_GPS项目新增结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;                                /* 消息名 */
    AT_APPCTRL_STRU                     stAppCtrl;
    VOS_UINT8                           aucContent[4];                          /* 消息内容 */
} AT_XPDS_MSG_STRU;

/*******************************************************************************
 结构名    : XPDS_AT_RESULT_CNF_STRU
 结构说明  : AT设置消息操作结果的回复消息结构体
 1.日    期   : 2015年08月21日
   作    者   : g00261581
   修改内容   : 新增结构体
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;       /* 消息名 */
    AT_APPCTRL_STRU                     stAppCtrl;
    XPDS_AT_RESULT_ENUM_UINT32          enResult;      /* 操作结果 */
}XPDS_AT_RESULT_CNF_STRU;

/*******************************************************************************
 结构名    : AT_XPDS_GPS_QRY_REFLOC_INFO_REQ_STRU
 结构说明  :
 1.日    期   : 2015年12月23日
   作    者   : y00174758
   修改内容   : 新增结构体
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;       /* 消息名 */
    AT_APPCTRL_STRU                     stAppCtrl;
}AT_XPDS_GPS_QRY_REFLOC_INFO_REQ_STRU;

/*******************************************************************************
 结构名    : AT_XPDS_RESERVE_STRU
 结构说明  : AT与XPDS消息保留结构体
 1.日    期   : 2015年08月21日
   作    者   : g00261581
   修改内容   : 新增结构体
*******************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserved[4]; /* 保留位 */
}AT_XPDS_RESERVE_STRU;

/** ****************************************************************************
 * Name        : AT_XPDS_GPS_START_REQ_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                                              ulMsgId;
    AT_APPCTRL_STRU                                         stAppCtrl;
    TAF_XPDS_INITIAL_TYPE_ENUM_UINT32                       enAgpsType;   /**< ulAgpsType */ /* 0: SI; 1: NI */
} AT_XPDS_GPS_START_REQ_STRU;


/** ****************************************************************************
 * Name        : AT_XPDS_GPS_STOP_REQ_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                                              ulMsgId;
    AT_APPCTRL_STRU                                         stAppCtrl;
} AT_XPDS_GPS_STOP_REQ_STRU;

/** ****************************************************************************
 * Name        : AT_XPDS_GPS_CFG_MPC_ADDR_REQ_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                                              ulMsgId;
    AT_APPCTRL_STRU                                         stAppCtrl;
    VOS_UINT32                                              ulIpAddr;
    VOS_UINT16                                              usIpPort;
    VOS_UINT16                                              usReserved;
} AT_XPDS_GPS_CFG_MPC_ADDR_REQ_STRU;

/** ****************************************************************************
 * Name        : AT_XPDS_GPS_CFG_PDE_ADDR_REQ_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                                              ulMsgId;
    AT_APPCTRL_STRU                                         stAppCtrl;
    VOS_UINT8                                               ucAddrValid;   /**< 0: not valid, 1: valid */
    VOS_UINT8                                               ucIPType;      /**< 0: ipv4, 1:ipv6 */
    VOS_UINT8                                               ucURLValid;    /**< 0: not valid, 1: valid */
    VOS_UINT8                                               ucReserved;    /**< padding */
    VOS_UINT32                                              ulIp4Addr;
    VOS_UINT32                                              ulIP6Addr[4];
    VOS_UINT32                                              ulPortNum;
    VOS_UINT8                                               aucURLAddr[128];
} AT_XPDS_GPS_CFG_PDE_ADDR_REQ_STRU;

/** ****************************************************************************
 * Name        : AT_XPDS_GPS_CFG_POSITION_MODE_REQ_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                                              ulMsgId;
    AT_APPCTRL_STRU                                         stAppCtrl;
    TAF_XPDS_CALL_TYPE_ENUM_UINT8                           enCallType;       /**< Userplane: 0, Callplane: 1 */
    TAF_XPDS_FIX_MODE_ENUM_UINT8                            enFixMode;        /**< Unkown: 0; MSA: 1, MSB: 2, MSS: 3, AFLT: 4 */
    VOS_UINT16                                              usFixNum;         /**< A value of 1 means is interested in only one fix. A value > 1, multiple fixes with some time in btw the attempts */
    VOS_UINT32                                              ulFixRateTime;    /**< Time, in seconds, between position fix attempts */
    VOS_UINT32                                              ulQosHaccuracy;   /**< Horizontal Accuracy, in meters */
    VOS_UINT32                                              ulQosVaccuracy;   /**< Vertical Acuracy, in meters */
    VOS_UINT32                                              ulQosPerformance; /**< Performance response quality in terms of time, in seconds */
} AT_XPDS_GPS_CFG_POSITION_MODE_REQ_STRU;

/** ****************************************************************************
 * Name        : AT_XPDS_GPS_QRY_TIME_INFO_REQ_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                                              ulMsgId;
    AT_APPCTRL_STRU                                         stAppCtrl;
    AT_XPDS_REPLY_SYNC_TIME_ENUM_UINT8                      enActionType;        /**< 1: reply time sync info, 2: reply time sync info and GPS assist data */
    VOS_UINT8                                               aucReserved[3];      /**< padding */
} AT_XPDS_GPS_QRY_TIME_INFO_REQ_STRU;

/** ****************************************************************************
 * Name        : AT_XPDS_GPS_MODEM_PRMDATA_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucSvId;          /**< Satellite vehicle ID */
    VOS_UINT8                                               ucSvCn0;         /**< Satellite C/No. [db-HZ], range [0..63] */
    VOS_UINT8                                               ucMulpathInd;    /**< Pseudorange Multipath Indicator, range [0..3] */
    VOS_UINT8                                               ucPsRmsErr;      /**< Pseudorange RMS Error, Range [0..63] */
    VOS_INT16                                               sPsDopp;         /**< Measured Doppler frequency, in units of 0.2Hz, range [-6553.6..+6553.4] Hz */
    VOS_UINT16                                              usSvCodePhWhole; /**< Satellite code Phase Whole Chips, in units of 1 GPS chip, range [0..1022] */
    VOS_UINT16                                              usSvCodePhFract; /**< Satellite code Phase Fractional Chips, in units of 1/2^10 of GPS chips, range [0.. (2^10-1)/2^10] GPS chips */
    VOS_UINT8                                               aucReserved[2];
} AT_XPDS_GPS_MODEM_PRMDATA_STRU ;

/** ****************************************************************************
 * Name        : AT_XPDS_PRM_INFO_RSP_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                                              ulMsgId;
    AT_APPCTRL_STRU                                         stAppCtrl;
    VOS_UINT8                                               ucPrmValid;                          /**< 0--not valid, 1--valid */
    VOS_UINT8                                               ucMeasTowUnc;                        /**< Measurement GPS Time of Week Uncertainty */
    VOS_UINT8                                               ucMeasNum;                           /**< Number of measurements, Range [0..15] */
    VOS_UINT8                                               ucReserved;                          /**< padding */
    VOS_UINT32                                              ulMeasTow;                           /**< Measurement GPS Time of Week, in units of 1ms */
    AT_XPDS_GPS_MODEM_PRMDATA_STRU                          astMseasData[TAF_MSG_CDMA_MAX_SV_NUM];
} AT_XPDS_GPS_PRM_INFO_RSP_STRU;

/** ****************************************************************************
 * Name        : AT_XPDS_GPS_REPLY_NI_RSP_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                                              ulMsgId;
    AT_APPCTRL_STRU                                         stAppCtrl;
    AT_XPDS_GPS_NI_REQ_REPLY_RESULT_ENUM_UINT8              enReplyResult;       /**< 0: reject, 1: accept */
    AT_XPDS_GPS_NI_REQ_REJECT_TYPE_ENUM_UINT8               enRejReason;         /* 1:用户未应答; 2:用户拒绝定位请求 */
    VOS_UINT8                                               aucReserved[2];      /**< padding */
} AT_XPDS_GPS_REPLY_NI_RSP_STRU;

/** ****************************************************************************
 * Name        : XPDS_AT_GPS_REFLOC_INFO_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucValidRefLoc; /**< 0: Not valid, 1: Valid Time Zone Only,2: Valid Time Zone and BS Location. */
    VOS_UINT8                                               ucReserved;                                          /**< padding */
    VOS_UINT16                                              usSid;         /**< System ID, Range [0..32767] */
    VOS_UINT16                                              usNid;         /**< Network ID, Range [0..65535] */
    VOS_UINT16                                              usBsid;        /**< Base Station ID, Range [0..65535] */
    VOS_UINT32                                              ulTzLat;
    VOS_UINT32                                              ulTzLong;      /**< Time zone Range [-16h ~+15.5h] and specific location is predefined in CBP */
    VOS_UINT32                                              ulBslat;       /**< WGS84 Geodetic Latitude [degrees], latitude from base last registered on */
    VOS_UINT32                                              ulBslong;      /**< WGS84 Geodetic Longitude [degrees], Longitude from base last registered on */
} XPDS_AT_GPS_REFLOC_INFO_STRU;

/** ****************************************************************************
 * Name        : XPDS_AT_GPS_REFLOC_INFO_CNF_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                                              ulMsgId;
    AT_APPCTRL_STRU                                         stAppCtrl;
    XPDS_AT_GPS_REFLOC_INFO_STRU                            stRefLoc;
} XPDS_AT_GPS_REFLOC_INFO_CNF_STRU;

/** ****************************************************************************
 * Name        : XPDS_AT_PDE_POSI_INFO_IND_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    AT_APPCTRL_STRU                     stAppCtrl;
    VOS_UINT8                           ucVelocityIncl;
    VOS_UINT8                           ucHeightIncl;
    VOS_UINT8                           ucClockIncl;
    VOS_UINT8                           ucFixType;
    VOS_INT16                           sLocUncAng;
    VOS_INT16                           sClockDrift;
    VOS_INT32                           lClockBias;
    VOS_INT32                           lLatitude;
    VOS_INT32                           lLongitude;
    VOS_UINT32                          ulLocUncA;
    VOS_UINT32                          ulLocUncP;
    VOS_UINT32                          ulVelocityHor;
    VOS_UINT32                          ulHeading;
    VOS_INT32                           lHeight;
    VOS_INT32                           lVerticalVelo;
    VOS_UINT32                          ulLocUncV;
} XPDS_AT_GPS_PDE_POSI_INFO_IND_STRU;

/** ****************************************************************************
 * Name        : TAF_MSG_CDMA_ACQASSIST_DATA_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSvId;           /**< Satellite Vehicle ID */
    VOS_INT8                            cDoppler1;        /**< Doppler 1st order term Hz/s, BS shall set the field to the two's complement value */
    /* of the 1st order doppler, in units of 1/64 Hz/s, in the range from -1Hz/s to +63/64 Hz/s */
    VOS_UINT8                           ucDoppler_win;    /**< Satellite doppler uncertainty, range [0..4] Please refer to IS801-1 page 4.30 */
    VOS_UINT8                           ucSvCodePhaseInt; /**< Integer number of Code periods that have dlapsed since the latest GPS bit boundary, range [0..19] */
    VOS_UINT8                           ucGpsBitNum;      /**< GPS bit number relative to GPS_TOW, range [0..3] */
    VOS_UINT8                           ucSvCodePhaseWin; /**< Total code phase window, range [0..31] */
    VOS_UINT8                           ucAzimuth;        /**< Satellite Azimuth, in units of 11.25 degrees */
    VOS_UINT8                           ucElevation;      /**< Satellite Elevation, in units of 11.25 degrees */
    VOS_UINT16                          usSvCodePhase;    /**< The GPS Code Phase, range [0..1022] chips */
    VOS_INT16                           sDoppler0;        /**< Doppler 0th order term, in units of 2.5Hz, in the range from -5120Hz to +5117.5 Hz */
} TAF_MSG_CDMA_ACQASSIST_DATA_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    AT_APPCTRL_STRU                     stAppCtrl;
    VOS_UINT32                          ulRefTow;                          /**< GPS time of week in seconds at AA's Time of Application */
    VOS_UINT8                           ucSvNum;                           /**< Number of satellites for which data is available */
    VOS_UINT8                           ucDoppler0Inc;                     /**< Doppler0 field included or not, 0: Not included, 1: included */
    VOS_UINT8                           ucAddDopplerInc;                   /**< Doppler1 field included or not, 0: Not included, 1: included */
    VOS_UINT8                           ucCodePhaseInc;                    /**< Code Phase information included or not, 0: Not included, 1: included */
    VOS_UINT8                           ucaAzEl;                           /**< Azimuth and Elevation angle included or not, 0: Not included, 1: included */
    VOS_UINT8                           aucReserved[3];
    TAF_MSG_CDMA_ACQASSIST_DATA_STRU    astAaData[TAF_MSG_CDMA_MAX_SV_NUM];/**< AA data array */
} XPDS_AT_GPS_ACQ_ASSIST_DATA_IND_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                                              ulMsgId;
    AT_APPCTRL_STRU                                         stAppCtrl;
    TAF_XPDS_INITIAL_TYPE_ENUM_UINT32                       enAgpsMode;
    AT_XPDS_AGPS_DATA_CALL_CTRL_ENUM_UINT32                 enAgpsOper;
} XPDS_AT_AP_DATA_CALL_REQ_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                                              ulMsgId;
    AT_APPCTRL_STRU                                         stAppCtrl;
    AT_XPDS_SERVER_MODE_ENUM_UINT32                         enServerMode;
    AT_XPDS_AGPS_DATA_CALL_CTRL_ENUM_UINT32                 enDataCallCtrl;
    VOS_UINT32                                              ulIpAddr;
    VOS_UINT32                                              ulPortNum;
} XPDS_AT_AP_SERVER_BIND_REQ_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    AT_APPCTRL_STRU                     stAppCtrl;
    AT_XPDS_SERVER_MODE_ENUM_UINT32     enServerMode;
    VOS_UINT32                          ulDataLen;
    VOS_UINT8                           aucData[4];
} XPDS_AT_AP_REVERSE_DATA_IND_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                                              ulMsgId;
    AT_APPCTRL_STRU                                         stAppCtrl;
    AT_XPDS_DATA_CALL_STATUS_ENUM_UINT32                    enChannelState;
} AT_XPDS_AP_DATA_CALL_STATUS_IND_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                                              ulMsgId;
    AT_APPCTRL_STRU                                         stAppCtrl;
    AT_XPDS_SERVER_MODE_ENUM_UINT32                         enServerMode;
    AT_XPDS_SERVER_BIND_STATUS_ENUM_UINT32                  enBindStatus;
} AT_XPDS_AP_SERVER_BIND_STATUS_IND_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    AT_APPCTRL_STRU                     stAppCtrl;
    AT_XPDS_SERVER_MODE_ENUM_UINT32     enServerMode;
    VOS_UINT32                          ulTotalNum;
    VOS_UINT32                          ulCurNum;
    VOS_UINT32                          ulDataLen;
    VOS_UINT8                           aucData[4];
} AT_XPDS_AP_FORWARD_DATA_IND_STRU;


/** ****************************************************************************
 * Name        : AT_XPDS_GPS_SYS_TIME_STRU
 *
 * Description : 系统时间数据结构
 *******************************************************************************/
typedef struct
{
    VOS_UINT16                          usYear;
    VOS_UINT16                          usMonth;
    VOS_UINT16                          usDayOfWeek;
    VOS_UINT16                          usDay;
    VOS_UINT16                          usHour;
    VOS_UINT16                          usMinute;
    VOS_UINT16                          usSecond;
    VOS_UINT16                          usMilliseconds;
    VOS_UINT32                          ulGPSweek;       /**< GPS week as the number of whole weeks since GPS time zero */
    VOS_UINT32                          ulGPSTimeOfWeek; /**< GPS time of week in seconds */
} AT_XPDS_GPS_SYS_TIME_STRU;

/** ****************************************************************************
 * Name        : TAF_MSG_CDMA_GPS_POSITION_ERROR_STRU
 *
 * Description : GPS位置error参数
 *******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulHorizontalErrorAlong;
    VOS_UINT32                          ulHorizontalErrorAngle;
    VOS_UINT32                          ulHorizontalErrorPerp;
    VOS_UINT32                          ulVerticalError;
    VOS_UINT32                          ulHorizontalConfidence;
    VOS_UINT32                          ulHorizontalVelocityError; /**< Horizontal velocity uncertainty in m/s */
    VOS_UINT32                          ulVerticalVelocityError;   /**< Vertical velocity uncertainty in m/s */
    VOS_UINT32                          ulHorinzontalHeadingError; /**< Horizontal heading uncertainty in degrees */
    VOS_UINT32                          ulLatitudeUncertainty;     /**< Latitude uncertainty */
    VOS_UINT32                          ulLongitudeUncertainty;    /**< Longitude Uncertainty */
} TAF_MSG_CDMA_GPS_POSITION_ERROR_STRU;

/** ****************************************************************************
 * Name        : AT_XPDS_GPS_POS_INFO_STRU
 *
 * Description : GPS Module计算出的位置信息数据结构
 *******************************************************************************/
typedef struct
{
    VOS_UINT32                                              ulValidityMask;
    AT_XPDS_GPS_SYS_TIME_STRU                               stUTCTime;
    VOS_INT32                                               lLatitude;                                          /**< in degrees, positive number indicate north latitude */
    VOS_INT32                                               lLongitude;                                         /**< in degrees, positive number indicate east longitude */
    VOS_UINT32                                              ulSpeed;                                             /**< in knots (nautical miles) */
    VOS_UINT32                                              ulHeading;                                           /**< in degrees, a heading of zero is true north */
    VOS_UINT32                                              ulMagneticVariation;                                 /**< the difference between the bearing to true north and the bearing shown on a magnetic compass, positive numbers indicate east */
    VOS_UINT32                                              ulAltitudeWRTSeaLevel;                               /**< in meters, with respect to sea level */
    VOS_UINT32                                              ulAltitudeWRTEllipsoid;                              /**< in meters, with respect to the WGS84 ellipsoid */
    TAF_MSG_CDMA_GPS_FIX_QUALITY_ENUM_UINT8                 enFixQuality;
    TAF_MSG_CDMA_GPS_FIX_TYPE_ENUM_UINT8                    enFixType;
    TAF_MSG_CDMA_GPS_SELECTION_TYPE_ENUM_UINT8              enSelectionType;
    VOS_UINT8                                               ucReserved;                                          /**< padding */
    VOS_UINT32                                              ulPositionDilutionOfPrecision;
    VOS_UINT32                                              ulHorizontalDilutionOfPrecision;
    VOS_UINT32                                              ulVerticalDilutionOfPrecision;
    VOS_UINT16                                              usSatelliteCount;                                    /**< number of satellites used to obtain the position */
    VOS_UINT16                                              usSatellitesUsedPRNs[TAF_MSG_CDMA_MAX_SV_NUM];
    VOS_UINT16                                              usSatellitesInView;
    VOS_UINT16                                              usSatellitesInViewPRNs[TAF_MSG_CDMA_MAX_SV_NUM];
    VOS_INT16                                               sSatellitesInViewElevation[TAF_MSG_CDMA_MAX_SV_NUM];
    VOS_UINT16                                              usSatellitesInViewAzimuth[TAF_MSG_CDMA_MAX_SV_NUM];
    VOS_UINT16                                              usSatellitesInViewSNR[TAF_MSG_CDMA_MAX_SV_NUM];
    TAF_MSG_CDMA_GPS_POSITION_ERROR_STRU                    stGPSPositionError;

    VOS_UINT32                                              ulGPSSessionCount;                                   /**< the number of GPS fixes attempted */
    VOS_UINT32                                              ulNumberOfPositions;                                 /**< the number of positions */
    VOS_UINT32                                              ulHorizontalVelocity;                                /**< Horizontal velocity in m/s */
    VOS_UINT32                                              ulVerticalVelocity;                                  /**< Vertical velocity in m/s */
} AT_XPDS_GPS_POS_INFO_STRU;

/** ****************************************************************************
 * Name        : AT_XPDS_GPS_POS_INFO_RSP_STRU
 *
 * Description : GPS Module计算出的位置信息数据结构
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                                              ulMsgId;
    AT_APPCTRL_STRU                                         stAppCtrl;
    AT_XPDS_GPS_POS_INFO_STRU                               stPosInfo;
} AT_XPDS_GPS_POS_INFO_RSP_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                                              ulMsgId;
    AT_APPCTRL_STRU                                         stAppCtrl;
    VOS_UINT8                                               ucLen;
    TAF_XPDS_NOTIFT_AND_VERIFY_INDICATOR_ENUM_UINT8         enNotificationInd;
    TAF_XPDS_POS_TECH_INDICATOR_ENUM_UINT8                  enPosTechInd;
    VOS_UINT8                                               ucPosQoSInc;
    VOS_UINT8                                               ucPosQoS;
    TAF_XPDS_IS801_MODE_ENUM_UINT8                          enIS801PosMode;
    VOS_UINT8                                               ucCorrelationId;
    VOS_UINT8                                               ucReqIdEncode;
    VOS_UINT8                                               ucReqIdLen;
    TAF_XPDS_CALL_TYPE_ENUM_UINT8                           enCallType;
    VOS_UINT8                                               aucRsv[2];
    VOS_UINT8                                               aucData[256];
    VOS_UINT16                                              usNumOfFixs;
    VOS_UINT16                                              usTimeBetweenFixs;
}XPDS_AT_GPS_NI_SESSION_IND_STRU;

/** ****************************************************************************
 * Name        : XPDS_AT_GPS_START_REQ_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                                              ulMsgId;
    AT_APPCTRL_STRU                                         stAppCtrl;
} XPDS_AT_GPS_START_REQ_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                                              ulMsgId;
    AT_APPCTRL_STRU                                         stAppCtrl;
    VOS_UINT32                                              ulData;/* 默认1 */
}XPDS_AT_GPS_CANCEL_IND_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                                              ulMsgId;
    AT_APPCTRL_STRU                                         stAppCtrl;
    XPDS_AT_ABORT_POS_REASON_ENUM_UINT16                    enAbortReason;
    VOS_UINT16                                              usRsv;
}XPDS_AT_GPS_ABORT_IND_STRU;


/*****************************************************************************
 结构名    : XPDS_AT_GPS_SYNC_TIME_IND_STRU
 结构说明  : XPDS给AT上报SYNC Time消息结构体

  1.日    期   : 2015年07月10日
    作    者   : d00212987
    修改内容    : AGPS迭代1新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    AT_APPCTRL_STRU                     stAppCtrl;
    XPDS_AT_SYNC_TIME_ENUM_UINT32       enResult;
    VOS_UINT32                          aulPulseTime[2];
} XPDS_AT_GPS_SYNC_TIME_IND_STRU;

/*****************************************************************************
 结构名    : XPDS_AT_GPS_ION_INFO_IND_STRU
 结构说明  : XPDS给AT上报ION 消息结构体

  1.日    期   : 2015年07月22日
    作    者   : y00346957
    修改内容   : 迭代14新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    AT_APPCTRL_STRU                     stAppCtrl;
    VOS_UINT8                           ucABParIncl;    /**< Alpha and beta parameters included or not. 0: Not include, 1: included */
    VOS_UINT8                           ucAlpha0;      /**< Ionospheric correction parameter Alpha0 */
    VOS_UINT8                           ucAlpha1;      /**< Ionospheric correction parameter Alpha1 */
    VOS_UINT8                           ucAlpha2;      /**< Ionospheric correction parameter Alpha2 */
    VOS_UINT8                           ucAlpha3;      /**< Ionospheric correction parameter Alpha3 */
    VOS_UINT8                           ucBeta0;       /**< Ionospheric correction parameter Beta0 */
    VOS_UINT8                           ucBeta1;       /**< Ionospheric correction parameter Beta1 */
    VOS_UINT8                           ucBeta2;       /**< Ionospheric correction parameter Beta2 */
    VOS_UINT8                           ucBeta3;       /**< Ionospheric correction parameter Beta3 */
    VOS_UINT8                           aucReserved[3]; /**< padding */
} XPDS_AT_GPS_ION_INFO_IND_STRU;

/*****************************************************************************
 结构名    : XPDS_AT_EPH_DATA_STRU
 结构说明  : XPDS发给AT EPH数据结构体

  1.日    期   : 2015年07月22日
    作    者   : y00174758
    修改内容   : AGPS迭代14新增
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSvId;         /**< Satelite Vehicle ID, Range[1..32] */
    VOS_UINT8                           aucReserved[3];
    VOS_UINT8                           ucAf2;          /**< Apparent satelite clock correction af2 */
    VOS_UINT8                           ucIode;         /**< Issue of data */
    VOS_UINT16                          usToc;          /**< Clock data reference time */
    VOS_UINT16                          usToe;          /**< Ephemeris reference time */
    VOS_UINT16                          usAf1;          /**< Apparent satelite clock correction af1 */
    VOS_UINT16                          usDelta_n;      /**< Mean motion difference from the computed value */
    VOS_UINT16                          usIdot;         /**< Rate of inclination angle, If negative number and Masked with 0xE000 */
    VOS_UINT16                          usCrs;          /**< Amplitude of the sine harmonic correction term to the orbit radius */
    VOS_UINT16                          usCrc;          /**< Amplitude of the cosine harmonic correction term to the orbit radius */
    VOS_UINT16                          usCus;          /**< Amplitude of the sine harmonic correction term to the argument of latitude */
    VOS_UINT16                          usCuc;          /**< Amplitude of the cosine harmonic correction term to the argument of latitude. */
    VOS_UINT16                          usCis;          /**< Amplitude of the sine harmonic correction term to the angle of inclination */
    VOS_UINT16                          usCic;          /**< Amplitude of the cosine harmonic correction term to the angle of inclination */
    VOS_UINT32                          ulAf0;          /**< Apparent satellite clock correction af0,If negative number & Masked w/ 0xFFE00000 */
    VOS_UINT32                          ulM0;           /**< Mean anomaly at the reference time */
    VOS_UINT32                          ulAsqrt;        /**< Square root of the semi-major axis */
    VOS_UINT32                          ulEccentricity; /**< eccentricity */
    VOS_UINT32                          ulIangle;       /**< Inclination angle at the reference time */
    VOS_UINT32                          ulOmega0;       /**< Longitude of ascending node of orbit plane at weekly epoch */
    VOS_UINT32                          ulOmega;        /**< Argument of perigee */
    VOS_UINT32                          ulOmegadot;     /**< Rate of right ascension, If negative number and Masked with 0xFF000000 */
} XPDS_AT_EPH_DATA_STRU;


/*****************************************************************************
 结构名    : XPDS_AT_GPS_EPH_INFO_IND_STRU
 结构说明  : XPDS发给AT EPH信息指示结构体

  1.日    期   : 2015年07月22日
    作    者   : y00174758
    修改内容   : AGPS迭代14新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    AT_APPCTRL_STRU                     stAppCtrl;
    VOS_UINT8                           ucSvNum;                                 /**< Number of SVs,Range [1..32] */
    VOS_UINT8                           aucReserved[3];
    XPDS_AT_EPH_DATA_STRU               astEphData[TAF_MSG_CDMA_MAX_EPH_PRN_NUM];
} XPDS_AT_GPS_EPH_INFO_IND_STRU;


/*****************************************************************************
 结构名    : XPDS_AT_ALM_DATA_STRU
 结构说明  : XPDS发给AT ALM数据结构体

  1.日    期   : 2015年07月22日
    作    者   : y00174758
    修改内容   : AGPS迭代14新增
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSvId;             /**< Satelite vehicle id, Range [1..32] */
    VOS_UINT8                           ucReserved;
    VOS_UINT16                          usDeltai;           /**< Correction to inclination */
    VOS_UINT16                          usAf0;              /**< Apparent satellite clock correction af0. If negative number and Masked with 0xF800 */
    VOS_UINT16                          usAf1;              /**< Apparent satellite clock correction af1. If negative number and Masked with 0xF800 */
    VOS_UINT16                          usOmegadot;         /**< rate of right ascension */
    VOS_UINT16                          usEccentricity;     /**< Eccentricity */
    VOS_UINT32                          ulAsqrt;            /**< Square root of the semi-major axis */
    VOS_UINT32                          ulOmega_0;          /**< Longitude of ascending node of orbit plane. If negative number and Masked with 0xFF000000 */
    VOS_UINT32                          ulOmega;            /**< Argument of perigee. If negative number and Masked with 0xFF000000 */
    VOS_UINT32                          ulM0;               /**< Mean anoaly at reference time. If negative number and Masked with 0xFF000000 */
} XPDS_AT_ALM_DATA_STRU;


/*****************************************************************************
 结构名    : XPDS_AT_GPS_ALM_INFO_IND_STRU
 结构说明  : XPDS发给AT ALM信息指示结构体

  1.日    期   : 2015年07月22日
    作    者   : y00174758
    修改内容   : AGPS迭代14新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    AT_APPCTRL_STRU                     stAppCtrl;
    VOS_UINT8                           ucSvNum;                                    /**< Number of SVs, Range [1..32] */
    VOS_UINT8                           ucWeekNum;                                  /**< GPS week number, Range [0..255] */
    VOS_UINT8                           ucToa;                                      /**< Time of almanac, in units of 4096 seconds, Range [0..602112] */
    VOS_UINT8                           ucReserved;
    XPDS_AT_ALM_DATA_STRU               astAlmData[TAF_MSG_CDMA_MAX_ALM_PRN_NUM];   /**< Set Max 32 PRNs, 5 + (27 * 32)= 869 bytes */
} XPDS_AT_GPS_ALM_INFO_IND_STRU;

/*****************************************************************************
 结构名    : XPDS_AT_GPS_DEL_ASSIST_DATA_IND_STRU
 结构说明  : XPDS发给AT 删除辅助数据指示结构体

  1.日    期   : 2015年07月25日
    作    者   : t00323010
    修改内容   : AGPS迭代14新增
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulDeleteFlag;                            /* 1:删除辅助数据 */
} XPDS_AT_GPS_DEL_ASSIST_DATA_IND_STRU;

/*****************************************************************************
 结构名    : XPDS_AT_GPS_NI_CP_START
 结构说明  :

  1.日    期   : 2015年07月25日
    作    者   : C00299064
    修改内容   : AGPS迭代2新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    AT_APPCTRL_STRU                     stAppCtrl;
    VOS_UINT32                          ulStartCode;                            /* 0:默认开启 */
} XPDS_AT_GPS_NI_CP_START_STRU;

/*****************************************************************************
 结构名    : XPDS_AT_GPS_NI_CP_STOP_STRU
 结构说明  :

  1.日    期   : 2015年07月25日
    作    者   : C00299064
    修改内容   : AGPS迭代2新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    AT_APPCTRL_STRU                     stAppCtrl;
    VOS_UINT32                          ulStartCode;                            /* 0:默认开启 */
} XPDS_AT_GPS_NI_CP_STOP_STRU;

/*****************************************************************************
 结构名    : XPDS_AT_UTS_GPS_POS_INFO_IND_STRU
 结构说明  :

  1.日    期   : 2015年12月22日
    作    者   : y00174758
    修改内容   : AGPS迭代2新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    AT_APPCTRL_STRU                     stAppCtrl;
    AT_XPDS_GPS_POS_INFO_STRU           stPosInfo;
} XPDS_AT_UTS_GPS_POS_INFO_IND_STRU;

/*****************************************************************************
 结构名    : XPDS_AT_GPS_OM_TEST_START_REQ_STRU
 结构说明  :

  1.日    期   : 2015年12月17日
    作    者   : y00174758
    修改内容   : AGPS迭代2新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    AT_APPCTRL_STRU                     stAppCtrl;
    TAF_XPDS_FIX_MODE_ENUM_UINT8        enFixMode;        /**< Unkown: 0; MSA: 1, MSB: 2, MSS: 3, AFLT: 4 */
    TAF_XPDS_GPS_START_MODE_ENUM_UINT8  enStartMode;
    VOS_UINT8                           aucRsv[2];
} XPDS_AT_GPS_OM_TEST_START_REQ_STRU;

/*****************************************************************************
 结构名    : XPDS_AT_GPS_OM_TEST_STOP_REQ_STRU
 结构说明  :

  1.日    期   : 2015年12月17日
    作    者   : y00174758
    修改内容   : AGPS迭代2新增
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    AT_APPCTRL_STRU                     stAppCtrl;
} XPDS_AT_GPS_OM_TEST_STOP_REQ_STRU;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/
/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  H2ASN顶级消息结构定义
*****************************************************************************/
typedef struct
{
    AT_XPDS_MSG_TYPE_ENUM_UINT32        ulMsgId;                                /*_H2ASN_MsgChoice_Export AT_XPDS_MSG_TYPE_ENUM_UINT32*/
    AT_APPCTRL_STRU                     stAppCtrl;
    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          AT_XPDS_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}AT_XPDS_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    AT_XPDS_MSG_DATA                     stMsgData;
}AtXpdsInterface_MSG;

/*****************************************************************************
  10 函数声明
*****************************************************************************/


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

