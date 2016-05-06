/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXpdsEncode.h
  版 本 号   : 初稿
  作    者   : 谷传征
  生成日期   : 2015年7月13日
  最近修改   :
  功能描述   : Encode head file
  函数列表   :
  修改历史   :
  1.日    期   : 2015年7月13日
    作    者   : g00261581
    修改内容   : CDMA-GPS项目新增

******************************************************************************/

#ifndef __TAFXPDSENCODE_H__
#define __TAFXPDSENCODE_H__

/*****************************************************************************
  1 Header File Include
*****************************************************************************/
#include "TafXpdsCtx.h"
#include "TafXpdsDecode.h"
#include "cas_1x_control_main_nas_pif.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 The Macro Define
*****************************************************************************/

#define TAF_XPDS_RL_BIT_TO_BYTE(NumOfBits)  ((NumOfBits + 7) / 8)
#define TAF_XPDS_RL_MAX_REQ_NUM_IN_ONE_MSG             (8)
#define TAF_XPDS_RL_MAX_RESP_NUM_IN_ONE_MSG            (8)

#define TAF_XPDS_ABS_DIFF(_Number1, _Number2)         (((_Number1 > _Number2) ? (_Number1 - _Number2) : ( _Number2 - _Number1)))

/*****************************************************************************
  3 The Enumeration Define
*****************************************************************************/
enum TAF_XPDS_RL_MSGTYPE_REQ_ENUM
{
    TAF_XPDS_RL_MSGTYPE_REQ_INVALID                    = 0x00,
    TAF_XPDS_RL_MSGTYPE_REQ_LOC_RSP                    = 0x01,  //refer 2.2.4.1.1,
    TAF_XPDS_RL_MSGTYPE_REQ_GPS_ACQ_ASSIST             = 0x04,  //refer 2.2.4.1.3
    TAF_XPDS_RL_MSGTYPE_REQ_GPS_ALM                    = 0x08,
    TAF_XPDS_RL_MSGTYPE_REQ_GPS_EPH                    = 0x09,  //refer 2.2.4.1.5

    TAF_XPDS_RL_MSGTYPE_REQ_EXT_LOC_RESP               = 0x01, //refer 2.2.4.1.8
    TAF_XPDS_RL_MSGTYPE_REQ_ENH_BS_ALMN                = 0x03, //refer 2.2.4.1.9
    TAF_XPDS_RL_MSGTYPE_REQ_GEN_ACQUI_ASSIST           = 0x04, //refer 2.2.4.1.10
    TAF_XPDS_RL_MSGTYPE_REQ_EXT_GPS_SENS_ASSIST        = 0x05, //refer 2.2.4.1.11
    TAF_XPDS_RL_MSGTYPE_REQ_EXT_GPS_EPHI               = 0x09, //refer 2.2.4.1.12
    TAF_XPDS_RL_MSGTYPE_REQ_EXT_GPS_NAV_MSG_BITS       = 0x0A, //refer 2.2.4.1.13
    TAF_XPDS_RL_MSGTYPE_REQ_DGPS_ASSIST                = 0x0F, //refer 2.2.4.1.14

    TAF_XPDS_RL_MSGTYPE_REQ_BUTT                       = 0xFF
};

typedef VOS_UINT8 TAF_XPDS_RL_MSGTYPE_REQ_ENUM_UINT8;

enum TAF_XPDS_RL_MSGTYPE_RESP_ENUM
{
    TAF_XPDS_RL_MSGTYPE_RESP_REJECT                    = 0x00,  //refer 2.2.4.2.1
    TAF_XPDS_RL_MSGTYPE_RESP_PROV_LOC_RESP             = 0x01,  //refer 2.2.4.2.2
    TAF_XPDS_RL_MSGTYPE_RESP_PROV_MS_INFO              = 0x02,  //refer 2.2.4.2.3
    TAF_XPDS_RL_MSGTYPE_RESP_PROV_PSUEDORANG_MEAS      = 0x04,  //refer 2.2.4.2.5
    TAF_XPDS_RL_MSGTYPE_RESP_PROV_PILPHASE_MEAS        = 0x05,  //refer 2.2.4.2.6

    TAF_XPDS_RL_MSGTYPE_RESP_EXT_REJECT                = 0x00,  //refer 2.2.4.2.9
    TAF_XPDS_RL_MSGTYPE_RESP_PROV_EXT_LOC_RESP         = 0x01,  //refer 2.2.4.2.10
    TAF_XPDS_RL_MSGTYPE_RESP_PROV_EXT_MS_INFO          = 0x02,  //refer 2.2.4.2.11
    TAF_XPDS_RL_MSGTYPE_RESP_PROV_GEN_LOC_MEAS         = 0x04,  //refer 2.2.4.2.12
    TAF_XPDS_RL_MSGTYPE_RESP_PROV_EXT_CANCEL_ACK       = 0x07,  //refer 2.2.4.2.13
    TAF_XPDS_RL_MSGTYPE_RESP_PROV_GPS_COARS_LOC_RESP   = 0x08,  //refer 2.2.4.2.14
    TAF_XPDS_RL_MSGTYPE_RESP_PROV_MSG_DELAY_MEAS       = 0x09,  //refer 2.2.4.2.15
    TAF_XPDS_RL_MSGTYPE_RESP_PROV_BEARING_MEAS         = 0x0A,  //refer 2.2.4.2.16
    TAF_XPDS_RL_MSGTYPE_RESP_PROV_SERV_SYS_INFO        = 0x0B,  //refer 2.2.4.2.17

    TAF_XPDS_RL_MSGTYPE_RESP_BUTT                      = 0xFF
};

typedef VOS_UINT8 TAF_XPDS_RL_MSGTYPE_RESP_ENUM_UINT8;

enum TAF_XPDS_RL_REJ_REASON_ENUM
{
    TAF_XPDS_RL_REJ_REASON_MS_CAP_NOT_SUPPORTED        = 0x00,
    TAF_XPDS_RL_REJ_REASON_NOT_AVAILABLE_OR_DISABLED,

    TAF_XPDS_RL_REJ_REASON_BUTT
};

typedef VOS_UINT8 TAF_XPDS_RL_REJ_REASON_ENUM_UINT8;
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
 结构名    :TAF_XPDS_ENCODE_RL_INFO_STRU
 结构说明  :Information needed when Encoding
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucNumOfReq;
    VOS_UINT8                                               ucNumOfResp;
    VOS_UINT8                                               aucReserve[2];
    TAF_XPDS_RL_MSGTYPE_REQ_ENUM_UINT8                      aucReqType[TAF_XPDS_RL_MAX_REQ_NUM_IN_ONE_MSG];
    TAF_XPDS_RL_MSGTYPE_RESP_ENUM_UINT8                     aucRspType[TAF_XPDS_RL_MAX_RESP_NUM_IN_ONE_MSG];
}TAF_XPDS_ENCODE_RL_INFO_STRU;



/*****************************************************************************
 结构名    :TAF_MTA_TO_MPC_START_POS_REQ
 结构说明  :MS_MPC_START_POS_REQ的结构体 参考协议(gpsone user plane ms-mpc ch4.2.2.1)
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucVersion;
    TAF_XPDS_MS_TO_MPC_MSG_TYPE_ENUM_UINT8                  enMsgType;
    VOS_UINT16                                              usLen;
    TAF_XPDS_MS_POS_CAPABILITY_ENUM_UINT8                   enMsPosCap;
    TAF_XPDS_APP_TYPE_INDICATOR_ENUM_UINT8                  enAppTypeIndicator;
    VOS_UINT8                                               ucPQoS;
    VOS_UINT8                                               ucCorrelationId;
    VOS_UINT32                                              ulDuration;
    TAF_XPDS_MS_ID_RECORD_STRU                              stMsIdRec;
    VOS_UINT16                                              usSID;
    VOS_UINT16                                              usNID;
    VOS_UINT32                                              ulBaseID;
    VOS_UINT32                                              ulBaseLat;
    VOS_UINT32                                              ulBaseLong;
    VOS_UINT16                                              usRefPn;
    VOS_UINT16                                              usBandClass;
    VOS_UINT32                                              ulCdmaFreq;
    TAF_XPDS_TIME_STAMP_STRU                                stTimeStamp;
    VOS_UINT32                                              ulBrewAppId;
    TAF_XPDS_APP_ID_REC_STRU                                stAppIdRec;
}TAF_XPDS_MPC_START_POS_REQ_STRU;

/*****************************************************************************
 结构名    :TAF_MTA_TO_MPC_POS_REPORT_STRU
 结构说明  :MS_MPC_START_POS_REQ的结构体 参考协议(gpsone user plane ms-mpc ch4.2.2.2)
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucVersion;
    TAF_XPDS_MS_TO_MPC_MSG_TYPE_ENUM_UINT8                  enMsgType;
    VOS_UINT16                                              usLen;
    VOS_UINT16                                              usFixNum;
    VOS_UINT16                                              usCorrelationId;
    TAF_XPDS_MS_ID_RECORD_STRU                              stMsIdRec;
    TAF_XPDS_TIME_STAMP_STRU                                stCellIdTimeStamp;
    VOS_UINT16                                              usSID;
    VOS_UINT16                                              usNID;
    VOS_UINT32                                              ulBaseID;
    VOS_UINT32                                              ulBaseLat;
    VOS_UINT32                                              ulBaseLong;
    VOS_UINT16                                              usRefPn;
    VOS_UINT16                                              usBandClass;
    VOS_UINT32                                              ulCdmaFreq;
    VOS_UINT32                                              ulPosIncFlag;
    TAF_XPDS_TIME_STAMP_STRU                                stPosTimeStamp;
    VOS_INT32                                               lLat;
    VOS_INT32                                               lLong;
    VOS_UINT8                                               ucLocUncrtntyAng;
    VOS_UINT8                                               ucLocUncrtntyA;
    VOS_UINT8                                               ucLocUncrtntyP;
    VOS_UINT8                                               ucVelocityIncl;
    VOS_UINT16                                              usVelocityHor;
    VOS_UINT16                                              usHeading;
    VOS_INT16                                               sVelocityVer;
    VOS_UINT16                                              usHeihtIncl;
    VOS_INT16                                               sHeiht;
    VOS_UINT16                                              usLocUncrtntyV;

}TAF_XPDS_MPC_POS_REPORT_STRU;

/*****************************************************************************
 结构名    :TAF_XPDS_MPC_CANCEL_TRACK_STRU
 结构说明  :MS_MPC_START_POS_REQ的结构体 参考协议(gpsone user plane ms-mpc ch4.2.2.3)
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucVersion;
    TAF_XPDS_MS_TO_MPC_MSG_TYPE_ENUM_UINT8             enMsgType;
    VOS_UINT16                                              usLen;
    VOS_UINT32                                              ulCorrelationId;
    TAF_XPDS_MS_ID_RECORD_STRU                               stMsIdRec;
}TAF_XPDS_MPC_CANCEL_TRACK_STRU;


/******************************************************************************
 * Name        : TAF_XPDS_REVLINK_REQ_GPS_LOC_ASSIS_STRU
 *
 * Description : Request GPS location assistance message. refer 2.2.4.1.4
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCoordinateType; /**< whether cartesian or spherical coordinate, range [0..1] */
    VOS_UINT8                           aucReserved[3];   /**< Reserved */
} TAF_XPDS_REVLINK_REQ_GPS_LOC_ASSIS_STRU;


/******************************************************************************
 * Name        : TAF_XPDS_REVLINK_REQ_GPS_ALM_CORR_STRU
 *
 * Description : Request GPS almanac correction message. refer 2.2.4.1.7
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTimeOfAlm;    /**< time of almanac, range [0..602112] */
    VOS_UINT8                           ucWeekNum;      /**< GPS week number */
} TAF_XPDS_REVLINK_REQ_GPS_ALM_CORR_STRU;


/******************************************************************************
 * Name        : TAF_XPDS_REVLINK_REQ_EXT_GPS_NAV_MSGBITS_STRU
 *
 * Description : Request extended GPS navigation message bits message. refer 2.2.4.1.13
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSubFrm4And5Req;   /**< subframe 4 and 5 requested or not, range [0..1] */
    VOS_UINT8                           aucReserve[3];      /**< reserve */
} TAF_XPDS_REVLINK_REQ_EXT_GPS_NAV_MSGBITS_STRU;


/******************************************************************************
 * Name        : TAF_XPDS_REVLINK_RSP_REJECT_STRU
 *
 * Description : respond reject message. refer 2.2.4.2.1
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRejReqType;    /**< rejacted request type */
    TAF_XPDS_RL_REJ_REASON_ENUM_UINT8   ucRejReason;     /**< reason for rejection  */
    VOS_UINT8                           aucReserve[2];   /**< reserved */
} TAF_XPDS_REVLINK_RSP_REJECT_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_SAT_WEIGHT_INFO_STRU
 *
 * Description : satellite weighting information
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSvPRNNum;     /**< satellite PRN number */
    VOS_UINT8                           ucInvWeiFact;   /**< inverse of weighting factor */
    VOS_UINT8                           aucReserve[2];  /**< pilot phase capability */
} TAF_XPDS_SAT_WEIGHT_INFO_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_REVLINK_RSP_AUTO_MES_WEIFACT_STRU
 *
 * Description : provide autonomous measurement weighting factors message. refer 2.2.4.2.4
 *******************************************************************************/
typedef struct
{
    VOS_UINT16                          usTimeRefCdma;      /**< CDMA system time */
    VOS_UINT8                           ucDGPSFlag;         /**< differencial GPS flag */
    VOS_UINT8                           ucNumOfSV;          /**< number of GPS satellites in solution */
    VOS_UINT8                           ucGpsWeight;        /**< ratio of GPS weight to total weight */
    VOS_UINT8                           aucReserve[3];      /**< padding */
    TAF_XPDS_SAT_WEIGHT_INFO_STRU       astSatWeiInfo[TAF_XPDS_RL_SAT_INFO_MAX];  /**< satellite weight record */
}TAF_XPDS_REVLINK_RSP_AUTO_MES_WEIFACT_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_REVLINK_RSP_TIME_OFF_MEAS_STRU
 *
 * Description : provide time offset measurement message. refer 2.2.4.2.7
 *******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulTimeRefMs;        /**< time of validity of the parameters reported */
    VOS_UINT16                          usRefPN;            /**< time reference PN sequence offset */
    VOS_UINT16                          usMobileSysOffset;  /**< mobile station system time offset */
}TAF_XPDS_REVLINK_RSP_TIME_OFF_MEAS_STRU;


/******************************************************************************
 * Name        : TAF_XPDS_REVLINK_RSP_CANCEL_ACK_STRU
 *
 * Description : provide cancellation acknowledgement message. refer 2.2.4.2.8
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCacelTypeAck;        /**< cancellation type */
    VOS_UINT8                           ucNoOutReq;            /**< whether outstanding request is there or not, range [0..1] */
}TAF_XPDS_REVLINK_RSP_CANCEL_ACK_STRU;

/*****************************************************************************
  8 The Union Define
*****************************************************************************/


/*****************************************************************************
  9 Other Defines
*****************************************************************************/


/*****************************************************************************
  10 The Declaration Of The Function
*****************************************************************************/
extern VOS_VOID TAF_XPDS_EncodePackIntegerIntoArray(
    VOS_UINT32                          ulInputNum,
    VOS_UINT16                         *pusCurBitPos,
    VOS_UINT8                           ucBitsNum,
    VOS_UINT8                          *pucData
);

extern VOS_UINT32 TAF_XPDS_EncodeXsmsMpcRejPosReq(
    TAF_XPDS_XSMS_REJ_POS_REQ_STRU     *pstRejPosReq,
    VOS_UINT32                         *pulDataLen,
    VOS_UINT8                          *pucData
);

extern VOS_UINT32 TAF_XPDS_EncodeXsmsMpcCancelPosNotifty(
    TAF_XPDS_XSMS_CANCEL_POS_NOTIFICATION_STRU             *pstCancelNotify,
    VOS_UINT32                                             *pulDataLen,
    VOS_UINT8                                              *pucData
);

extern VOS_VOID TAF_XPDS_EncodeMpcStartPosReq(
    TAF_XPDS_MPC_START_POS_REQ_STRU    *pstMpcStartReq,
    VOS_UINT32                         *pulDataLen,
    VOS_UINT8                          *pucData
);


extern VOS_VOID TAF_XPDS_EncodeSetValue(
    VOS_UINT32                          ulValueToSet,
    VOS_UINT8                           ucNumOfBits,
    VOS_UINT32                         *pulTotalBitsPrc,
    VOS_UINT8                          *pcCurrBuf,
    VOS_UINT32                         *pulCurIdx
);

VOS_VOID TAF_XPDS_EncodeReqGpsAlmanac(
    VOS_UINT8                          *pcDestBuf,
    VOS_UINT32                         *pulLength
);

VOS_VOID TAF_XPDS_EncodeReqGpsAcqAssist(
    TAF_XPDS_REVLINK_REQ_GPS_ACQ_ASSIST_STRU               *pstGpsAcqAssist,
    VOS_UINT8                                              *pcDestBuf,
    VOS_UINT32                                             *pulLength
);

VOS_VOID TAF_XPDS_EncodeReqLocRsp(
    TAF_XPDS_REVLINK_REQ_LOC_RSP_STRU                      *pstReqLocRsp,
    VOS_UINT8                                              *pcDestBuf,
    VOS_UINT32                                             *pulLength
);

VOS_VOID TAF_XPDS_EncodeReqGpsEphimeries(
    TAF_XPDS_REVLINK_REQ_GPS_EPH_STRU  *pstReqEph,
    VOS_UINT8                          *pucDestBuf,
    VOS_UINT32                         *pulLength
);

VOS_VOID TAF_XPDS_EncodeReject(
    TAF_XPDS_REVLINK_RSP_REJECT_STRU   *pstReject,
    VOS_UINT8                          *pcDestBuf,
    VOS_UINT32                         *pulLength
);

VOS_VOID TAF_XPDS_EncodeProvMsInfo(
    VOS_UINT8                          *pcDestBuf,
    VOS_UINT32                         *pulLength
);

VOS_VOID TAF_XPDS_EncodeProvLocRsp(
    TAF_XPDS_REVLINK_RSP_LOC_INFO_STRU *pstLocResp,
    VOS_UINT8                          *pcDestBuf,
    VOS_UINT32                         *pulLength
);

VOS_VOID TAF_XPDS_EncodeProvPseudoRangMeas(
    TAF_XPDS_REVLINK_RSP_PSEU_RANGE_MEAS_STRU              *pstProvPr,
    VOS_UINT8                                              *pcDestBuf,
    VOS_UINT32                                             *pulLength
);

VOS_VOID TAF_XPDS_EncodeStartDeliverData(
    TAF_XPDS_START_DELV_DATA_STRU      *pstStartDl,
    VOS_UINT8                          *pcDestBuf,
    VOS_UINT32                         *pulLength
);

VOS_VOID TAF_XPDS_EncodePdMsgHeader(
    TAF_XPDS_PD_MSG_HEADER_STRU        *pstPdMsgHeader,
    VOS_UINT8                          *pucMsgBuff,
    VOS_UINT32                         *pulLength
);

extern VOS_VOID TAF_XPDS_EncodeMpcPosReportReq(
    TAF_XPDS_MPC_POS_REPORT_STRU       *pstMpcPosReportReq,
    VOS_UINT32                         *pulDataLen,
    VOS_UINT8                          *pucData
);

VOS_VOID TAF_XPDS_EncodeProvPilotPhaseMeas
(
    TAF_XPDS_REVLINK_RSP_PILOT_PHASE_MEAS_STRU             *pstProvPp,
    VOS_UINT8                                              *pucDestBuf,
    VOS_UINT32                                             *pulLength
);

VOS_UINT32 TAF_XPDS_EncodeMpcCancelTrTrackReq(
    TAF_XPDS_MPC_CANCEL_TRACK_STRU     *pstMpcCancelTrack,
    VOS_UINT32                         *pulDataLen,
    VOS_UINT8                          *pucData
);

VOS_VOID TAF_XPDS_EncodeReverseReqs(
    TAF_XPDS_ENCODE_RL_INFO_STRU       *pstEncodeRlInfo,
    VOS_UINT8                          *pucMsgBuff,
    VOS_UINT32                         *pulLength
);

VOS_VOID TAF_XPDS_EncodeReverseRsps(
    TAF_XPDS_ENCODE_RL_INFO_STRU       *pstEncodeRlInfo,
    VOS_UINT8                          *pucMsgBuff,
    VOS_UINT32                         *pulLength
);

VOS_VOID TAF_XPDS_EncodeReverseMsg(
    TAF_XPDS_ENCODE_RL_INFO_STRU       *pstEncodeRlInfo,
    VOS_UINT8                          *pcDestBuf,
    VOS_UINT32                         *pulLength
);

VOS_UINT32 TAF_XPDS_EncodeDataBurstMsg(
    TAF_XPDS_DATA_BURST_MSG_STRU       *pstDataBurst,
    VOS_UINT8                          *pucDestBuf,
    VOS_UINT32                         *pulLength
);

extern VOS_VOID TAF_XPDS_EncodeMsIdRec(
    TAF_XPDS_MS_ID_RECORD_STRU           *pstMsIdRec
);

VOS_VOID TAF_XPDS_GetMsIdRecFromCard(
    VOS_UINT8                          *paucData
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


