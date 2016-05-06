/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXpdsMntn.h
  版 本 号   : 初稿
  作    者   : 谷传征
  生成日期   : 2015年7月13日
  最近修改   :
  功能描述   : CDMA AGPS Mntn header file
  函数列表   :
  修改历史   :
  1.日    期   : 2015年7月13日
    作    者   : g00261581
    修改内容   : CDMA-AGPS项目新增

******************************************************************************/

#ifndef __TAFXPDSMNTN_H__
#define __TAFXPDSMNTN_H__

/*****************************************************************************
  1 Header File Include
*****************************************************************************/
/* Added by wx270776 for OM融合, 2015-6-27, begin */
#include "TafLog.h"
/* Added by wx270776 for OM融合, 2015-6-27, end */

#include "TafXpdsEncode.h"
#include "TafXpdsDecode.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)


/*****************************************************************************
  2 The Macro Define
*****************************************************************************/
#if (VOS_WIN32 == VOS_OS_VER)
#define   XPDS_WARNING_LOG(string)                vos_printf("%s \r\n", string)
#define   XPDS_WARNING1_LOG(string, para1)        vos_printf("%s %d.\r\n", string, para1)
#define   XPDS_WARNING2_LOG(string, para1, para2) vos_printf("%s %d, %d.\r\n", string, para1, para2)

#define   XPDS_ERROR_LOG(string)                  vos_printf("%s \r\n", string)
#define   XPDS_ERROR1_LOG(string, para1)          vos_printf("%s %d.\r\n", string, para1)
#define   XPDS_ERROR2_LOG(string, para1, para2)   vos_printf("%s %d, %d.\r\n", string, para1, para2)
#else
#define   XPDS_WARNING_LOG(string)                TAF_LOG(UEPS_PID_XPDS, 0, PS_PRINT_WARNING,  string)
#define   XPDS_WARNING1_LOG(string, para1)        TAF_LOG1(UEPS_PID_XPDS, 0, PS_PRINT_WARNING,  string, (VOS_INT32)para1)
#define   XPDS_WARNING2_LOG(string, para1, para2) TAF_LOG2(UEPS_PID_XPDS, 0, PS_PRINT_WARNING,  string, (VOS_INT32)para1, (VOS_INT32)para2)

#define   XPDS_ERROR_LOG(string)                  TAF_LOG(UEPS_PID_XPDS, 0, PS_PRINT_ERROR,  string)
#define   XPDS_ERROR1_LOG(string, para1)          TAF_LOG1(UEPS_PID_XPDS, 0, PS_PRINT_ERROR,  string, (VOS_INT32)para1)
#define   XPDS_ERROR2_LOG(string, para1, para2)   TAF_LOG2(UEPS_PID_XPDS, 0, PS_PRINT_ERROR,  string, (VOS_INT32)para1, (VOS_INT32)para2)
#endif

#define TAF_XPDS_MNTN_MSG_ID_BASE                 (0x1000)

/*****************************************************************************
  3 The Enumeration Define
*****************************************************************************/

/*****************************************************************************
 枚举名    : CNAS_MNTN_MSG_ID_ENUM
 结构说明  : CAGPS模块发送给OM的可维可测消息
  1.日    期   : 2015年07月31日
    作    者   : g00261581
    修改内容   : CAGPS模块发送给OM的可维可测消息
*****************************************************************************/
enum TAF_XPDS_MNTN_MSG_ID_ENUM
{
    ID_TAF_XPDS_MNTN_LOG_FSM_INFO_IND                   = TAF_XPDS_MNTN_MSG_ID_BASE + 1,    /* _H2ASN_MsgChoice TAF_XPDS_MNTN_LOG_FSM_INFO_STRU */
    ID_TAF_XPDS_MNTN_SESSION_BEGIN_IND                  = TAF_XPDS_MNTN_MSG_ID_BASE + 2,    /* _H2ASN_MsgChoice TAF_XPDS_MNTN_SESSION_BEGIN_IND_STRU */
    ID_TAF_XPDS_MNTN_SESSION_END_IND                    = TAF_XPDS_MNTN_MSG_ID_BASE + 3,    /* _H2ASN_MsgChoice TAF_XPDS_MNTN_SESSION_END_IND_STRU */
    ID_TAF_XPDS_MNTN_REVERSE_MSG_INFO_IND               = TAF_XPDS_MNTN_MSG_ID_BASE + 4,    /* _H2ASN_MsgChoice TAF_XPDS_MNTN_REVERSE_MSG_INFO_IND_STRU */
    ID_TAF_XPDS_MNTN_FORWARD_MSG_INFO_IND               = TAF_XPDS_MNTN_MSG_ID_BASE + 5,    /* _H2ASN_MsgChoice TAF_XPDS_MNTN_FORWARD_MSG_INFO_IND_STRU */
    ID_TAF_XPDS_MNTN_PILOT_INFO_CTX_IND                 = TAF_XPDS_MNTN_MSG_ID_BASE + 6,    /* _H2ASN_MsgChoice TAF_XPDS_MNTN_PILOT_INFO_CTX_IND_STRU */
    ID_TAF_XPDS_MNTN_PSEU_RANGE_INFO_CTX_IND            = TAF_XPDS_MNTN_MSG_ID_BASE + 7,    /* _H2ASN_MsgChoice TAF_XPDS_MNTN_PSEU_RANGE_INFO_CTX_IND_STRU */
    ID_TAF_XPDS_MNTN_ASSIST_DATA_CTX_IND                = TAF_XPDS_MNTN_MSG_ID_BASE + 8,    /* _H2ASN_MsgChoice TAF_XPDS_MNTN_ASSIST_DATA_CTX_IND_STRU */
    ID_TAF_XPDS_MNTN_POS_INFO_CTX_IND                   = TAF_XPDS_MNTN_MSG_ID_BASE + 9,    /* _H2ASN_MsgChoice TAF_XPDS_MNTN_POS_INFO_CTX_IND_STRU */
    ID_TAF_XPDS_MNTN_EPH_INFO_CTX_IND                   = TAF_XPDS_MNTN_MSG_ID_BASE + 10,   /* _H2ASN_MsgChoice TAF_XPDS_MNTN_EPH_INFO_CTX_IND_STRU */
    ID_TAF_XPDS_MNTN_ALM_INFO_CTX_IND                   = TAF_XPDS_MNTN_MSG_ID_BASE + 11,   /* _H2ASN_MsgChoice TAF_XPDS_MNTN_ALM_INFO_CTX_IND_STRU */
    ID_TAF_XPDS_MNTN_FORWARD_PDE_HEADER_IND             = TAF_XPDS_MNTN_MSG_ID_BASE + 12,   /* _H2ASN_MsgChoice TAF_XPDS_MNTN_FORWARD_PDE_MSG_HEADER_IND_STRU_STRU */
    ID_TAF_XPDS_MNTN_REVERSE_PDE_HEADER_IND             = TAF_XPDS_MNTN_MSG_ID_BASE + 13,   /* _H2ASN_MsgChoice TAF_XPDS_MNTN_REVERSE_PDE_MSG_HEADER_IND_STRU_STRU */
    ID_TAF_XPDS_MNTN_REVERSE_START_DELIVER_DATA_IND     = TAF_XPDS_MNTN_MSG_ID_BASE + 14,   /* _H2ASN_MsgChoice TAF_XPDS_MNTN_REVERSE_START_DELIVER_DATA_IND_STRU_STRU */
    ID_TAF_XPDS_MNTN_REVERSE_MPC_START_POS_REQ_IND      = TAF_XPDS_MNTN_MSG_ID_BASE + 15,   /* _H2ASN_MsgChoice TAF_XPDS_MNTN_REVERSE_MPC_START_POS_REQ_IND_STRU_STRU */
    ID_TAF_XPDS_MNTN_REVERSE_MPC_POS_REPORT_REQ_IND     = TAF_XPDS_MNTN_MSG_ID_BASE + 16,   /* _H2ASN_MsgChoice TAF_XPDS_MNTN_REVERSE_MPC_POS_REPORT_REQ_IND_STRU_STRU */
    ID_TAF_XPDS_MNTN_REVERSE_PDE_REJ_RSP_IND            = TAF_XPDS_MNTN_MSG_ID_BASE + 17,   /* _H2ASN_MsgChoice TAF_XPDS_MNTN_REVERSE_PDE_REJ_RSP_IND_STRU_STRU */

    ID_TAF_XPDS_MNTN_BUTT
};
typedef VOS_UINT32 TAF_XPDS_MNTN_MSG_ID_ENUM_UINT32;


/*****************************************************************************
  4 The Declaration Of The Gloabal Variable
*****************************************************************************/


/*****************************************************************************
  5 The Define Of the Message Header
*****************************************************************************/


/*****************************************************************************
  6 The Define of the Message Name
*****************************************************************************/


/*****************************************************************************
  7 The Struct Define
*****************************************************************************/

/*****************************************************************************
 结构名    : TAF_XPDS_MNTN_LOG_FSM_INFO_STRU
 结构说明  : ID_TAF_XPDS_MNTN_LOG_FSM_INFO_STRU的消息结构
 1.日    期   : 2015年08月22日
   作    者   : g00256031
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头 */    /* _H2ASN_Skip */
    TAF_XPDS_MNTN_MSG_ID_ENUM_UINT32    enMsgId;                                /* 消息ID */    /* _H2ASN_Skip */
    VOS_UINT32                          ulModuleId;                             /* Module Id */
    VOS_UINT32                          ulCurFsmId;
    VOS_UINT32                          ulCurFsmState;
}TAF_XPDS_MNTN_LOG_FSM_INFO_STRU;

/*****************************************************************************
 结构名    : TAF_XPDS_MNTN_SESSION_BEGIN_IND_STRU
 结构说明  : ID_TAF_XPDS_MNTN_SESSION_BEGIN_IND的消息结构
 1.日    期   : 2015年07月31日
   作    者   : g00261581
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                                  /* 消息头 */    /* _H2ASN_Skip */
    TAF_XPDS_MNTN_MSG_ID_ENUM_UINT32                        enMsgId;                                /* 消息ID */    /* _H2ASN_Skip */
    TAF_XPDS_CFG_INFO_STRU                                  stCagpsCfg;
}TAF_XPDS_MNTN_SESSION_BEGIN_IND_STRU;

/*****************************************************************************
 结构名    : TAF_XPDS_MNTN_SESSION_END_IND_STRU
 结构说明  : ID_TAF_XPDS_MNTN_SESSION_END_IND的消息结构
 1.日    期   : 2015年07月31日
   作    者   : g00261581
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                                  /* 消息头 */    /* _H2ASN_Skip */
    TAF_XPDS_MNTN_MSG_ID_ENUM_UINT32                        enMsgId;                                /* 消息ID */    /* _H2ASN_Skip */
    VOS_UINT8                                               aucReserved[4];
}TAF_XPDS_MNTN_SESSION_END_IND_STRU;

/*****************************************************************************
 结构名    : TAF_XPDS_MNTN_REVERSE_MSG_INFO_IND_STRU
 结构说明  : ID_TAF_XPDS_MNTN_REVERSE_MSG_INFO_IND的消息结构
 1.日    期   : 2015年07月31日
   作    者   : g00261581
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                                  /* 消息头 */    /* _H2ASN_Skip */
    TAF_XPDS_MNTN_MSG_ID_ENUM_UINT32                   enMsgId;                                /* 消息ID */    /* _H2ASN_Skip */
    TAF_XPDS_ENCODE_RL_INFO_STRU                       stRlMsgInfo;
}TAF_XPDS_MNTN_REVERSE_MSG_INFO_IND_STRU;

/*****************************************************************************
 结构名    : TAF_XPDS_MNTN_FORWARD_MSG_INFO_IND_STRU
 结构说明  : ID_TAF_XPDS_MNTN_FORWARD_MSG_INFO_IND的消息结构
 1.日    期   : 2015年07月31日
   作    者   : g00261581
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                                  /* 消息头 */    /* _H2ASN_Skip */
    TAF_XPDS_MNTN_MSG_ID_ENUM_UINT32                   enMsgId;                                /* 消息ID */    /* _H2ASN_Skip */
    TAF_XPDS_FWDLINK_REQ_RESP_FLAG_STRU                stReqRespFlag;
    VOS_UINT32                                         ulPdeDataMask;
}TAF_XPDS_MNTN_FORWARD_MSG_INFO_IND_STRU;

typedef struct
{
    VOS_UINT32                          ulTimeRefMS;         /**< time of validity of the parameters reported */
    VOS_UINT16                          usCdmaFreq;          /**< frequency assignment */
    VOS_UINT16                          usBaseId;            /**< base station identifier */
    VOS_UINT16                          usSID;               /**< system identification number */
    VOS_UINT16                          usNID;               /**< network identification number */
    VOS_UINT16                          usRefPn;             /**< reference PN sequence offset */
    VOS_UINT8                           ucTotalRxPow;        /**< total recieved power */
    VOS_UINT8                           ucPartNum;           /**< part number among total parts */
    VOS_INT16                           sMobSysTOffst;       /**< mobile station system time offset */
    VOS_UINT8                           ucOffsetIncl;        /**< whether offset included or not, range [0..1] */
    VOS_UINT8                           ucTotalParts;        /**< total number of parts */
    VOS_UINT8                           ucNumOfPilotP;       /**< number of pilots in this part */
    VOS_UINT8                           ucAddPilotIncl;      /**< additional pilots included or not, range [0..1] */
    VOS_UINT8                           ucAddBandClass;      /**< additional band class */
    VOS_UINT8                           ucAddTotRxPow;       /**< total recieved power on additional frequency */
    VOS_UINT16                          usAddCdmaFreq;       /**< additional frequency assignement */
    VOS_UINT8                           ucNumOfAddPilotP;    /**< number of additional pilots */
    VOS_UINT8                           ucRefPilotStrgth;    /**< pilot strength */
    VOS_UINT8                           ucBandClass;         /**< band class */
    VOS_UINT8                           aucReserve[3];       /**< padding */
    TAF_XPDS_PILOT_INFO_STRU            astPilotRec[TAF_XPDS_RL_PHASE_PILREC_MAX];     /**< pilot record */
    TAF_XPDS_PILOT_INFO_STRU            astAddPilotRec[TAF_XPDS_RL_PHASE_PILREC_MAX];
} TAF_XPDS_MNTN_PILOT_INFO_STRU;

/*****************************************************************************
 结构名    : TAF_XPDS_MNTN_PILOT_INFO_CTX_IND_STRU
 结构说明  : ID_TAF_XPDS_MNTN_PILOT_INFO_CTX_IND的消息结构
 1.日    期   : 2015年07月31日
   作    者   : g00261581
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                                  /* 消息头 */    /* _H2ASN_Skip */
    TAF_XPDS_MNTN_MSG_ID_ENUM_UINT32                   enMsgId;                                /* 消息ID */    /* _H2ASN_Skip */
    TAF_XPDS_MNTN_PILOT_INFO_STRU                      stPilotInfo;                            /* Get Info From CAS, And need to send to PDE */
}TAF_XPDS_MNTN_PILOT_INFO_CTX_IND_STRU;

/*****************************************************************************
 结构名    : TAF_XPDS_MNTN_PSEU_RANGE_INFO_CTX_IND_STRU
 结构说明  : ID_TAF_XPDS_MNTN_PSEU_RANGE_INFO_CTX_IND的消息结构
 1.日    期   : 2015年07月31日
   作    者   : g00261581
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                                  /* 消息头 */    /* _H2ASN_Skip */
    TAF_XPDS_MNTN_MSG_ID_ENUM_UINT32                   enMsgId;                                /* 消息ID */    /* _H2ASN_Skip */
    TAF_XPDS_REVLINK_RSP_PSEU_RANGE_MEAS_STRU          stRspPrmInfo;                           /* Get Info From GPS, And need to send to PDE */
}TAF_XPDS_MNTN_PSEU_RANGE_INFO_CTX_IND_STRU;

/*****************************************************************************
 结构名    : TAF_XPDS_MNTN_ASSIST_DATA_CTX_IND_STRU
 结构说明  : ID_TAF_XPDS_MNTN_ASSIST_DATA_CTX_IND的消息结构
 1.日    期   : 2015年07月31日
   作    者   : g00261581
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                                  /* 消息头 */    /* _H2ASN_Skip */
    TAF_XPDS_MNTN_MSG_ID_ENUM_UINT32                   enMsgId;                                /* 消息ID */    /* _H2ASN_Skip */
    TAF_XPDS_FWDLINK_RSP_GPS_ACQ_ASSIST_STRU           stProvAcqAssist;
}TAF_XPDS_MNTN_ASSIST_DATA_CTX_IND_STRU;

/*****************************************************************************
 结构名    : TAF_XPDS_MNTN_POS_INFO_CTX_IND_STRU
 结构说明  : ID_TAF_XPDS_MNTN_POS_INFO_CTX_IND的消息结构
 1.日    期   : 2015年07月31日
   作    者   : g00261581
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                                                  /* 消息头 */    /* _H2ASN_Skip */
    TAF_XPDS_MNTN_MSG_ID_ENUM_UINT32                   enMsgId;                                /* 消息ID */    /* _H2ASN_Skip */
    TAF_XPDS_FWDLINK_RSP_LOC_RESP_STRU                 stProvLocRsp;
}TAF_XPDS_MNTN_POS_INFO_CTX_IND_STRU;

/*****************************************************************************
 结构名    : TAF_XPDS_MNTN_EPH_INFO_CTX_IND_STRU
 结构说明  : ID_TAF_XPDS_MNTN_EPH_INFO_CTX_IND的消息结构
 1.日    期   : 2015年08月03日
   作    者   : y00174758
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                  /* 消息头 */    /* _H2ASN_Skip */
    TAF_XPDS_MNTN_MSG_ID_ENUM_UINT32    enMsgId;    /* 消息ID */    /* _H2ASN_Skip */
    TAF_XPDS_FWDLINK_RSP_GPS_EPH_STRU   stProvEph;
}TAF_XPDS_MNTN_EPH_INFO_CTX_IND_STRU;

/*****************************************************************************
 结构名    : TAF_XPDS_MNTN_ALM_INFO_CTX_IND_STRU
 结构说明  : ID_TAF_XPDS_MNTN_ALM_INFO_CTX_IND的消息结构
 1.日    期   : 2015年08月03日
   作    者   : y00174758
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                  /* 消息头 */    /* _H2ASN_Skip */
    TAF_XPDS_MNTN_MSG_ID_ENUM_UINT32    enMsgId;    /* 消息ID */    /* _H2ASN_Skip */
    TAF_XPDS_FWDLINK_RSP_GPS_ALM_STRU   stProvAlm;
}TAF_XPDS_MNTN_ALM_INFO_CTX_IND_STRU;

/*****************************************************************************
 结构名    : TAF_XPDS_MNTN_FORWARD_PDE_MSG_HEADER_IND_STRU_STRU
 结构说明  : ID_TAF_XPDS_MNTN_FORWARD_PDE_HEADER_INFO_IND的消息结构
 1.日    期   : 2015年09月25日
   作    者   : y00174758
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                  /* 消息头 */    /* _H2ASN_Skip */
    TAF_XPDS_MNTN_MSG_ID_ENUM_UINT32    enMsgId;    /* 消息ID */    /* _H2ASN_Skip */
    TAF_XPDS_PD_MSG_HEADER_STRU         stPdMsgHeader;
}TAF_XPDS_MNTN_FORWARD_PDE_MSG_HEADER_IND_STRU_STRU;

/*****************************************************************************
 结构名    : TAF_XPDS_MNTN_REVERSE_PDE_MSG_HEADER_IND_STRU_STRU
 结构说明  : ID_TAF_XPDS_MNTN_REVERSE_PDE_HEADER_INFO_IND的消息结构
 1.日    期   : 2015年09月25日
   作    者   : y00174758
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                  /* 消息头 */    /* _H2ASN_Skip */
    TAF_XPDS_MNTN_MSG_ID_ENUM_UINT32    enMsgId;    /* 消息ID */    /* _H2ASN_Skip */
    TAF_XPDS_PD_MSG_HEADER_STRU         stPdMsgHeader;
}TAF_XPDS_MNTN_REVERSE_PDE_MSG_HEADER_IND_STRU_STRU;

/*****************************************************************************
 结构名    : TAF_XPDS_MNTN_REVERSE_START_DELIVER_DATA_IND_STRU_STRU
 结构说明  : ID_TAF_XPDS_MNTN_REVERSE_START_DELIVER_DATA_IND的消息结构
 1.日    期   : 2015年09月25日
   作    者   : y00174758
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                  /* 消息头 */    /* _H2ASN_Skip */
    TAF_XPDS_MNTN_MSG_ID_ENUM_UINT32    enMsgId;    /* 消息ID */    /* _H2ASN_Skip */
    TAF_XPDS_START_DELV_DATA_STRU       stStartDelvData;
}TAF_XPDS_MNTN_REVERSE_START_DELIVER_DATA_IND_STRU_STRU;

/*****************************************************************************
 结构名    : TAF_XPDS_MNTN_REVERSE_MPC_START_POS_REQ_IND_STRU_STRU
 结构说明  : ID_TAF_XPDS_MNTN_REVERSE_MPC_START_POS_REQ_IND的消息结构
 1.日    期   : 2015年09月25日
   作    者   : y00174758
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                  /* 消息头 */    /* _H2ASN_Skip */
    TAF_XPDS_MNTN_MSG_ID_ENUM_UINT32    enMsgId;    /* 消息ID */    /* _H2ASN_Skip */
    TAF_XPDS_MPC_START_POS_REQ_STRU     stStartPosReq;
}TAF_XPDS_MNTN_REVERSE_MPC_START_POS_REQ_IND_STRU_STRU;

/*****************************************************************************
 结构名    : TAF_XPDS_MNTN_REVERSE_MPC_POS_REPORT_REQ_IND_STRU_STRU
 结构说明  : ID_TAF_XPDS_MNTN_REVERSE_MPC_POS_REPORT_REQ_IND的消息结构
 1.日    期   : 2015年09月25日
   作    者   : y00174758
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                  /* 消息头 */    /* _H2ASN_Skip */
    TAF_XPDS_MNTN_MSG_ID_ENUM_UINT32    enMsgId;    /* 消息ID */    /* _H2ASN_Skip */
    TAF_XPDS_MPC_POS_REPORT_STRU        stPosReportReq;
}TAF_XPDS_MNTN_REVERSE_MPC_POS_REPORT_REQ_IND_STRU_STRU;

/*****************************************************************************
 结构名    : TAF_XPDS_MNTN_REVERSE_PDE_REJ_RSP_IND_STRU_STRU
 结构说明  : ID_TAF_XPDS_MNTN_REVERSE_PDE_REJ_RSP_IND的消息结构
 1.日    期   : 2015年09月25日
   作    者   : y00174758
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                  /* 消息头 */    /* _H2ASN_Skip */
    TAF_XPDS_MNTN_MSG_ID_ENUM_UINT32    enMsgId;    /* 消息ID */    /* _H2ASN_Skip */
    TAF_XPDS_REVLINK_RSP_REJECT_STRU    stRejInfo;
}TAF_XPDS_MNTN_REVERSE_PDE_REJ_RSP_IND_STRU_STRU;


/*****************************************************************************
  8 The Union Define
*****************************************************************************/


/*****************************************************************************
  9 Other Defines
*****************************************************************************/
/*****************************************************************************
  H2ASN顶级消息结构定义
*****************************************************************************/
typedef struct
{
    TAF_XPDS_MNTN_MSG_ID_ENUM_UINT32                enMsgId;          /* _H2ASN_MsgChoice_Export TAF_XPDS_MNTN_MSG_ID_ENUM_UINT32 */

    VOS_UINT8                                       aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          TAF_XPDS_MNTN_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}TAF_XPDS_MNTN_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    TAF_XPDS_MNTN_MSG_DATA                   stMsgData;
}TafXpdsMntn_MSG;


/*****************************************************************************
  10 The Declaration Of The Function
*****************************************************************************/
VOS_VOID TAF_XPDS_MNTN_LogFsmInfo(
    VOS_UINT32                          ulPid,
    VOS_UINT32                          ulFsmId,
    VOS_UINT32                          ulFsmState
);

VOS_VOID  TAF_XPDS_MNTN_TraceIntMsg(
    VOS_UINT32                          ulModuleId,
    VOS_UINT32                          ulLength,
    VOS_VOID                           *pstMsg
);

VOS_VOID TAF_XPDS_MNTN_TraceSessionBeginIndMsg(VOS_VOID);

VOS_VOID TAF_XPDS_MNTN_TraceSessionEndIndMsg(VOS_VOID);

VOS_VOID TAF_XPDS_MNTN_TraceReverseMsgInfoIndMsg(
    TAF_XPDS_ENCODE_RL_INFO_STRU  *pstRlMsgInfo
);

VOS_VOID TAF_XPDS_MNTN_TraceForwardMsgInfoIndMsg(
    VOS_UINT32                          ulPdeDataMask
);

VOS_VOID TAF_XPDS_MNTN_TracePilotPhaseInfoCtxIndMsg(VOS_VOID);

VOS_VOID TAF_XPDS_MNTN_TracePseuRangeInfoCtxIndMsg(VOS_VOID);

VOS_VOID TAF_XPDS_MNTN_TraceAssistDataCtxIndMsg(VOS_VOID);

VOS_VOID TAF_XPDS_MNTN_TraceLocationInfoCtxIndMsg(VOS_VOID);

VOS_VOID TAF_XPDS_MNTN_TraceEphInfoCtxIndMsg(VOS_VOID);

VOS_VOID TAF_XPDS_MNTN_TraceAlmInfoCtxIndMsg(VOS_VOID);

VOS_VOID TAF_XPDS_MNTN_TraceForwardPdeHeaderInfo(VOS_VOID);


VOS_VOID TAF_XPDS_MNTN_TraceReverseStartDeliverData(
    TAF_XPDS_START_DELV_DATA_STRU      *pstStartDelvData
);

VOS_VOID TAF_XPDS_MNTN_TraceReverseMpcStartPosReq(
    TAF_XPDS_MPC_START_POS_REQ_STRU    *pstStartPosReq
);

VOS_VOID TAF_XPDS_MNTN_TraceReverseMpcPosReportReq(
    TAF_XPDS_MPC_POS_REPORT_STRU       *pstPosReportReq
);

VOS_VOID TAF_XPDS_MNTN_TraceReversePdeRejRsp(
    TAF_XPDS_REVLINK_RSP_REJECT_STRU   *pstRejInfo
);

VOS_VOID TAF_XPDS_MNTN_TraceReversePdeHeaderInfo(
    TAF_XPDS_PD_MSG_HEADER_STRU        *pstPdMsgHeader
);

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


