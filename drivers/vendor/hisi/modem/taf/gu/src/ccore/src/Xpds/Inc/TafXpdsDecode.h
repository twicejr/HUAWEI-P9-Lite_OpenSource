/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXpdsDecode.h
  版 本 号   : 初稿
  作    者   : 谷传征
  生成日期   : 2015年7月13日
  最近修改   :
  功能描述   : Decode head file
  函数列表   :
  修改历史   :
  1.日    期   : 2015年7月13日
    作    者   : g00261581
    修改内容   : CDMA-GPS项目新增

******************************************************************************/

#ifndef __TAFXPDSDECODE_H__
#define __TAFXPDSDECODE_H__

/*****************************************************************************
  1 Header File Include
*****************************************************************************/
#include "TafXpdsCtx.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 The Macro Define
*****************************************************************************/
/* Forward link REQ/RSP Type */
#define TAF_XPDS_FL_MSGTYPE_REQ_LOCATION_INFO          (0x01)
#define TAF_XPDS_FL_MSGTYPE_REQ_MS_INFO                (0x02)
#define TAF_XPDS_FL_MSGTYPE_REQ_PSEUDORANGE_MEAS       (0x04)
#define TAF_XPDS_FL_MSGTYPE_REQ_PILOT_PHASE_MEAS       (0x05)
#define TAF_XPDS_FL_MSGTYPE_REQ_CANCELLATION           (0x07)


#define TAF_XPDS_FL_MSGTYPE_RSP_REJECT                 (0x00)
#define TAF_XPDS_FL_MSGTYPE_RSP_PROV_LOCATION_RESPONSE (0x01)
#define TAF_XPDS_FL_MSGTYPE_RSP_PROV_ACQ_ASSISTANCE    (0x04)
#define TAF_XPDS_FL_MSGTYPE_RSP_PROV_GPS_ALMANAC       (0x08)
#define TAF_XPDS_FL_MSGTYPE_RSP_PROV_GPS_EPHEMERIS     (0x09)

#define TAF_XPDS_BURST_TYPE_POS_DET                    (0x05)


/*****************************************************************************
  3 The Enumeration Define
*****************************************************************************/
/*****************************************************************************
 枚举名    : TAF_XPDS_XSMS_MSG_DECODE_RSLT_ENUM
 枚举说明  : XSMS消息解码结果枚举定义
 1.日    期   : 2015年09月06日
   作    者   : y00174758
   修改内容   : 新建
*****************************************************************************/
enum TAF_XPDS_XSMS_MSG_DECODE_RSLT_ENUM
{
    TAF_XPDS_XSMS_MSG_DECODE_RSLT_SUCCESS,
    TAF_XPDS_XSMS_MSG_DECODE_RSLT_UNSUPPORTED_VERSION,
    TAF_XPDS_XSMS_MSG_DECODE_RSLT_ERROR,

    TAF_XPDS_XSMS_MSG_DECODE_RSLT_BUTT,
};
typedef VOS_UINT8 TAF_XPDS_XSMS_MSG_DECODE_RSLT_ENUM_UINT8;


/*****************************************************************************
  4 The Declaration Of The Gloabal Variable
*****************************************************************************/


/*****************************************************************************
  5 The Define Of the Message Header
*****************************************************************************/


/*****************************************************************************
  6 The Define of the Message Name
*****************************************************************************/
typedef VOS_UINT32 (*TAF_XPDS_DecodeReqHandler)(VOS_UINT8 *pcMsgBuff);

typedef VOS_UINT32 (*TAF_XPDS_DecodeRespHandler)(VOS_UINT8 *pcMsgBuff);

/*****************************************************************************
  7 The Struct Define
*****************************************************************************/
/******************************************************************************
 * Name        : TAF_XPDS_DECODE_RESP_HANDLER_STRU
 *
 * Description : request and response message handlers for forward link messages
 *******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMsgType;
    TAF_XPDS_DecodeRespHandler          pfRespHandler;
}TAF_XPDS_DECODE_RESP_HANDLER_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_DECODE_REQ_MSG_HANDLER_STRU
 *
 * Description : request and response message handlers for forward link messages
 *******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMsgType;
    TAF_XPDS_DecodeReqHandler           pfReqHandler;
}TAF_XPDS_DECODE_REQ_MSG_HANDLER_STRU;



/******************************************************************************
 * Name        : TAF_XPDS_DECODE_MSG_TYPE_MAP_DATA_MASK_STRU
 *
 * Description : Strucutre of PDE message type mapping PDE data mask
 *******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMsgType;
    VOS_UINT32                          ulDataMask;
}TAF_XPDS_DECODE_MSG_TYPE_MAP_DATA_MASK_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_FWDLINK_REQ_TIME_OFF_MEAS_STRU
 *
 * Description : Request time offset measurement message. refer 3.2.4.1.4
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucUseTime;       /**< use time , range [0..1]*/
    VOS_UINT8                           ucActionTime;    /**< action time, range [0..1] */
    VOS_UINT8                           aucReserved[2];  /**< padding */
} TAF_XPDS_FWDLINK_REQ_TIME_OFF_MEAS_STRU;


/******************************************************************************
 * Name        : TAF_XPDS_FWDLINK_REQ_EXT_LOC_RESP_STRU
 *
 * Description : Request extended location response message. refer 3.2.4.1.6
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNumOfFixes;     /**< number of fixes, range [1..256] */
    VOS_UINT8                           ucTimeBetFixes;   /**< time between the fixes. [0..255] */
    VOS_UINT8                           ucMaxRespTime;    /**< maximum response time, range [0..7]*/
    VOS_UINT8                           ucFixTypeReq;     /**< fixed type requested or not, range [0..1] */
    VOS_UINT8                           ucQosReqType;     /**< quality of service request type, range [0..1] */
    VOS_UINT8                           ucPrefRespTime;   /**< prefered response time */
    VOS_UINT8                           ucLocUncHC;       /**< requested horizontal location uncertainity, range [0..16] */
    VOS_UINT8                           ucLocUncHCnf;     /**< requested horizontal location uncertainity confidential level, range [0..3] */
    VOS_UINT8                           ucLocUncHCReq;    /**< horizontal location uncertainity eliptical requested or not, range [0..1] */
    VOS_UINT8                           ucHeightReq;      /**< height information requested or not, range [0..1] */
    VOS_UINT8                           ucClkCorGpsReq;   /**< Clock correcction for GPS requested or not, range [0..1] */
    VOS_UINT8                           ucVelocityReq;    /**< Velocity information requested or not, range [0..1] */
    VOS_UINT8                           ucVelUncHCReq;    /**< Velocity information requested - elliptical or not, range [0..1] */
    VOS_UINT8                           aucReserved[3];   /**< padding */
} TAF_XPDS_FWDLINK_REQ_EXT_LOC_RESP_STRU;


/******************************************************************************
 * Name        : TAF_XPDS_FWDLINK_REQ_EXT_MS_INFO_STRU
 *
 * Description : Request extended MS Information message. refer 3.2.4.1.7
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMsCapReq;        /**< MS capability requested or not, range [0..1] */
    VOS_UINT8                           ucGpsRxCapReq;     /**< GPS reciever capability requested or not. [0..1] */
    VOS_UINT8                           ucBandClsCapReq;   /**< band class capability requested or not, range [0..1]*/
    VOS_UINT8                           ucPilotDelSensReq; /**< pilot detection sensitivity requested or not, range [0..1] */
    VOS_UINT8                           ucMsStatusReq;     /**< MS status requested or not,  range [0..1] */
    VOS_UINT8                           aucReserved[3];    /**< padding */
} TAF_XPDS_FWDLINK_REQ_EXT_MS_INFO_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_FWDLINK_REQ_FREQ_INFO_STRU
 *
 * Description : Requested frequency Information structure
 *******************************************************************************/
typedef struct
{
    VOS_UINT16                          usCdmaFreq;      /**< cdma frewuency  assignment */
    VOS_UINT8                           ucBandClass;     /**< band class */
    VOS_UINT8                           ucModeInd;       /**< mode indicator, range [0..3]*/
    VOS_UINT8                           ucRptrMeasFReq;  /**< repeater measurement on this frewuency requested */
    VOS_UINT8                           aucReserved[3];  /**< padding */
} TAF_XPDS_FWDLINK_REQ_FREQ_INFO_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_FWDLINK_REQ_GEN_LOC_MEAS_STRU
 *
 * Description : Request general location measurement message. refer 3.2.4.1.8
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                               ucNumOfFix;        /**< numbber of fixes, range [1..256] */
    VOS_UINT8                               ucTimeBetFix;      /**< time between fixes. [0..255] */
    VOS_UINT8                               ucMaxRespTime;     /**< maximum response time, range [0..7]*/
    VOS_UINT8                               ucPrefRespTime;    /**< prefered response time */
    VOS_UINT8                               ucPilotIdReq;      /**< pilot idemtification information requested or not,  range [0..1] */
    VOS_UINT8                               ucPrMeasReq;       /**< psuedorange measurement requested or not, range [0..1] */
    VOS_UINT8                               ucSvCodePhIntReq;  /**< satellite code phase integer code requested or not. [0..1] */
    VOS_UINT8                               ucPPMeasReq;       /**< pilot phase measurement requested or not, range [0..1]*/
    VOS_UINT8                               ucPpMeasDopplReq;  /**< pilot phase psuedo doppler requested or not, range [0..1] */
    VOS_UINT8                               ucRptrMeasReq;     /**< repeater measurement requested or not,  range [0..1] */
    VOS_UINT8                               ucReqFreqListIncl; /**< frequency list included or not, range [0..1] */
    VOS_UINT8                               ucNumOfReqFreq;    /**< number of frequency,  range [0..7] */
    TAF_XPDS_FWDLINK_REQ_FREQ_INFO_STRU     astFreqInfo[TAF_XPDS_FL_REQ_FREQ_MAX];    /**< MS status requested or not,  range [0..1] */
    VOS_UINT8                               ucOffsetReq;       /**< offset  requested or not, range [0..1] */
    VOS_UINT8                               ucShrtOffEnable;   /**< shortened offset period or not,  range [0..1] */
    VOS_UINT8                               ucNumReqOffset;    /**< number of requested transmit time mesurement, range [0..63] */
    VOS_UINT8                               ucOffRefTimeInc;   /**< offset reference time increment,  range [0..7] */
    VOS_UINT16                              usActionTIme;      /**< action time */
    VOS_UINT8                               ucUseTime;         /**< use action time indicator,  range [0..1] */
    VOS_UINT8                               ucReserved;        /**< padding */
} TAF_XPDS_FWDLINK_REQ_GEN_LOC_MEAS_STRU;


/******************************************************************************
 * Name        : TAF_XPDS_FWDLINK_REQ_EXT_CANCEL_STRU
 *
 * Description : Request extended cancellation message. refer 3.2.4.1.9
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCancelType;      /**< cancel type */
    VOS_UINT8                           aucReserved[3];    /**< padding */
} TAF_XPDS_FWDLINK_REQ_EXT_CANCEL_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_FWDLINK_REQ_MSG_DELAY_MEAS_STRU
 *
 * Description : Request messaging delay measurement message. refer 3.2.4.1.10
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMsgSeq;         /**< message sequence number */
    VOS_UINT8                           ucRxTxDelayReq;   /**< recieve to transmit time delay information requested or not., range [0..1]  */
    VOS_UINT8                           aucReserved[2];   /**< padding */
} TAF_XPDS_FWDLINK_REQ_MSG_DELAY_MEAS_STRU;


/******************************************************************************
 * Name        : TAF_XPDS_FWDLINK_REQ_SERV_SYS_INFO_STRU
 *
 * Description : Request serving system information message. refer 3.2.4.1.11
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPilotIdSeq;     /**< pilot identification information requested or not., range [0..1] */
    VOS_UINT8                           ucExtPilotIdSeq;  /**< extended pilot identification information requested or not, range [0..1]  */
    VOS_UINT8                           ucActiveSetSeq;   /**< active set information requested or not, range [0..1]*/
    VOS_UINT8                           ucNeighListReq;   /**< neighbour list information requested or not., range [0..1]  */
    VOS_UINT8                           ucBaseLocSeq;     /**< BS location information requested or not., range [0..1] */
    VOS_UINT8                           aucReserved[3];   /**< padding */
} TAF_XPDS_FWDLINK_REQ_SERV_SYS_INFO_STRU;


/******************************************************************************
 * Name        : TAF_XPDS_FWDLINK_REQ_COARSE_LOC_RESP_STRU
 *
 * Description : Request coarse location response message. refer 3.2.4.1.12
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNumOfFixes;    /**< number of fixes., range [1..256] */
    VOS_UINT8                           ucTimeBetFixes;  /**< time between fixes, range [0..255]  */
    VOS_UINT8                           ucMaxRespTime;   /**< maximum response time */
    VOS_UINT8                           ucReserved;      /**< padding */
} TAF_XPDS_FWDLINK_REQ_COARSE_LOC_RESP_STRU;


/******************************************************************************
 * Name        : TAF_XPDS_FWDLINK_RSP_REJECT_STRU
 *
 * Description : response reject message. refer 3.2.4.2.1
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRejReqType;    /**< number of fixes., range [1..256] */
    VOS_UINT8                           ucRejReason;  /**< time between fixes, range [0..255]  */
    VOS_UINT8                           ucReserved[2];      /**< padding */
} TAF_XPDS_FWDLINK_RSP_REJECT_STRU;


/******************************************************************************
 * Name        : TAF_XPDS_FWDLINK_RSP_BS_CAP_STRU
 *
 * Description : response provide BS capabilities message. refer 3.2.4.2.3
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucBsLsRev;  /**< base station location standard revision number */
    VOS_UINT8                           ucGpscId;   /**< GPS capability indicator  */
    VOS_UINT8                           ucAfltcId;  /**< advanced forward link trilateration capability indicator */
    VOS_UINT8                           ucApdcId;   /**< autonomous position determination capability indicator  */
} TAF_XPDS_FWDLINK_RSP_BS_CAP_STRU;


/******************************************************************************
 * Name        : TAF_XPDS_PILOT_INFO_STRU
 *
 * Description : provide base station almanac message pilot information
 *******************************************************************************/
typedef struct
{
    VOS_UINT16                          usPilotPn;         /**< pilot PN sequence offset */
    VOS_UINT16                          usBaseId;          /**< base station identifier */
    VOS_UINT16                          usTimeCorrec;      /**< GPS reference time correction for pilot PN */
    VOS_UINT16                          usDeltaLat;        /**< difference in lattitude of this BS and reference BS */
    VOS_UINT16                          usDeltaLong;       /**< Rdifference in longitude of this BS and reference BS */
    VOS_UINT16                          usHeight;          /**< padding */
    VOS_UINT8                           ucLocSameAsPrev;   /**< location same as previous or not, range [0..1] */
    VOS_UINT8                           aucReserved[3];    /**< padding */


}TAF_XPDS_BS_ALMA_PILOT_INFO_STRU;


/******************************************************************************
 * Name        : TAF_XPDS_FWDLINK_RSP_BS_ALM_STRU
 *
 * Description : provide  base station almanac message. refer 3.2.4.2.4
 *******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulLatRef;           /**< reference lattitude */
    VOS_UINT32                          ulLongRef;          /**< reference longitude */
    VOS_UINT16                          usHeightRef;        /**< reference height */
    VOS_UINT16                          usRefPn;            /**< reference PN offset */
    VOS_UINT16                          usTimeCorRef;       /**< reference time correction */
    VOS_UINT8                           ucPartNum;          /**< part number */
    VOS_UINT8                           ucTotalParts;       /**< total number of parts */
    VOS_UINT16                          usNumOfPilots;      /**< number of pilots in this part */
    VOS_UINT8                           aucReserve[2];      /**< padding */
    TAF_XPDS_BS_ALMA_PILOT_INFO_STRU    astPilotInfo[TAF_XPDS_FL_ALM_MAX_PILOT];  /**< pilot information */
} TAF_XPDS_FWDLINK_RSP_BS_ALM_STRU;


/******************************************************************************
 * Name        : TAF_XPDS_BS_SV_DR_REC_STRU
 *
 * Description :  GPS satellite data record structure
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           aucNavMsgBits[TAF_XPDS_FL_NAVBITS_MAX]; /**< navigation message bits */
    VOS_UINT8                           ucNumSvDr;         /**< number of GPS satellite in this record */
    VOS_UINT8                           aucReserve[3];     /**< padding */
    VOS_UINT8                           aucSvPrnNum[TAF_XPDS_FL_PRN_MAX];   /**< satellite PRN number */
}TAF_XPDS_BS_SV_DR_REC_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_FWDLINK_RSP_GPS_SEN_ASSIS_STRU
 *
 * Description : provide  GPS sensitivity assistance message. refer 3.2.4.2.6
 *******************************************************************************/
typedef struct
{
    VOS_UINT16                          usRefBitNum;     /**< reference bit numbert */
    VOS_UINT8                           ucNumOfDrP;      /**< number of data records  */
    VOS_UINT8                           ucDrSize;        /**< ddata record size */
    VOS_UINT8                           ucPartNum;       /**< part number of total parts */
    VOS_UINT8                           ucTotalParts;    /**< total number of parts , range [1..8]*/
    VOS_UINT8                           aucReserve[2];   /**< padding */
    TAF_XPDS_BS_SV_DR_REC_STRU          astDataRec[TAF_XPDS_FL_SAT_INFO_MAX];  /**< satellite data record information */
} TAF_XPDS_FWDLINK_RSP_GPS_SEN_ASSIS_STRU;


/******************************************************************************
 * Name        : TAF_XPDS_BS_DELAY_REC_STRU
 *
 * Description :  Gdelay record structure
 *******************************************************************************/
typedef struct
{
    VOS_UINT16                           usPilotPn;        /**< pilot PN */
    VOS_UINT16                           usDelayOneWay;    /**< one way delay */
}TAF_XPDS_BS_DELAY_REC_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_BS_SPH_COOR_SV_STRU
 *
 * Description :  spherical coordinate satellite record
 *******************************************************************************/
typedef struct
{
    VOS_UINT16                           usElevLsb;      /**< LSB's of elevation angle */
    VOS_UINT16                           usAzimuthLsb;   /**< LSB's of azimuth */
    VOS_UINT16                           usSvCodePhFr;   /**< fractional chip of code phase */
    VOS_UINT8                            ucDoppl0Lsb;    /**< 0th order doppler */
    VOS_UINT8                            ucReserved;     /**< number of GPS satellite in this record */
}TAF_XPDS_BS_SPH_COOR_SV_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_FWDLINK_RSP_GPSLOC_ASSIS_SPHR_STRU
 *
 * Description : provide  GPS location assistance spherical coordinates message. refer 3.2.4.2.7
 *******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulLatRef;         /**< reference lattitude */
    VOS_UINT32                          ulLongRef;        /**< reference longitude  */
    VOS_UINT8                           ucHeightRef;      /**< reference height */
    VOS_UINT8                           ucNumOfDly;       /**< number of delays, range [0..7] */
    VOS_UINT8                           ucNumOfSv;        /**< number of GPS satellites , range [0..16]*/
    VOS_UINT8                           ucReserve;        /**< padding */
    TAF_XPDS_BS_DELAY_REC_STRU          astDelayRec[7];   /**< delay record information */
    TAF_XPDS_BS_SPH_COOR_SV_STRU        astSatRec[TAF_XPDS_FL_SAT_INFO_MAX];    /**< satellite spherical record information */
} TAF_XPDS_FWDLINK_RSP_GPSLOC_ASSIS_SPHR_STRU;


/******************************************************************************
 * Name        : TAF_XPDS_BS_CORT_COOR_SV_STRU
 *
 * Description :  cortesian coordinate satellite record
 *******************************************************************************/
typedef struct
{
    VOS_UINT32                           ulSvCoorX;      /**< X coordinate of satellite in ECEF format */
    VOS_UINT32                           ulSvCoorY;      /**< Y coordinate of satellite in ECEF format */
    VOS_UINT32                           ulSvCoorZ;      /**< Z coordinate of satellite in ECEF format */
    VOS_UINT8                            ucDoppl0Lsb;    /**< 0th order doppler */
    VOS_UINT8                            aucReserved[3]; /**< number of GPS satellite in this record */
}TAF_XPDS_BS_CORT_COOR_SV_STRU;


/******************************************************************************
 * Name        : TAF_XPDS_FWDLINK_RSP_GPSLOC_ASSIS_CORT_STRU
 *
 * Description : provide  GPS location assistance cortesian coordinates message. refer 3.2.4.2.8
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNumOfDly;       /**< number of delays, range [0..7] */
    VOS_UINT8                           ucNumOfSv;        /**< number of GPS satellites , range [0..16]*/
    VOS_UINT8                           aucReserve[2];    /**< padding */
    TAF_XPDS_BS_DELAY_REC_STRU          astDelayRec[TAF_XPDS_FL_DELAY_REC_MAX];   /**< delay record information */
    TAF_XPDS_BS_CORT_COOR_SV_STRU       astSatRec[TAF_XPDS_FL_SAT_INFO_MAX];    /**< satellite cortesian record information */
} TAF_XPDS_FWDLINK_RSP_GPSLOC_ASSIS_CORT_STRU;

/******************************************************************************
 * Name        : TAF_XPDS__GPS_NAVBITS_SAT_INFO_STRU
 *
 * Description : navigation bits satellite information
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           aucSubF123[TAF_XPDS_FL_SUBF123_MAX]; /**< sub frame 1, 2, 3 */
    VOS_UINT8                           ucSvPrnNum;      /**< satellite PRN number */
    VOS_UINT8                           aucReserved[2];  /**< reserved */
} TAF_XPDS_GPS_NAVBITS_SAT_INFO_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_FWDLINK_RSP_GPS_NAVBITS_STRU
 *
 * Description : provide  GPS navigation bits message. refer 3.2.4.2.11
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNumOfSvP;        /**< number of satellites, range [0..16] */
    VOS_UINT8                           ucPartNum;         /**< part number */
    VOS_UINT8                           ucTotalParts;      /**< total number of parts */
    VOS_UINT8                           ucSubF45Incl;      /**< sub frame 4 and 5 included or not, range [0..1] */
    VOS_UINT8                           aucSubFr45[TAF_XPDS_FL_SUBF45_MAX];  /**< ionospheric cor parameter, alpha 0 */
    TAF_XPDS_GPS_NAVBITS_SAT_INFO_STRU  astSatInfo[TAF_XPDS_FL_NAVBITS_MAX];    /**< satellite information */
} TAF_XPDS_FWDLINK_RSP_GPS_NAVBITS_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_GPS_ALM_SAT_INFO_STRU
 *
 * Description : GPS almanac satellite information
 *******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulDeltaClk;      /**< correction for clock */
    VOS_UINT16                          usDeltaX;        /**< correction for X coordinate */
    VOS_UINT16                          usDeltaY;        /**< correction for Y coordinate */
    VOS_UINT16                          usDeltaZ;        /**< correction for Z coordinate */
    VOS_UINT8                           ucSvPrnNum;      /**< satellite PRN number */
    VOS_UINT8                           ucDeltaXYZIncl;  /**< correction for XYZ included or not, range [0..1] */
    VOS_UINT8                           ucDeltaX_1;      /**< 1st order correction for X coordinate */
    VOS_UINT8                           ucDeltaY_1;      /**< 1st order correction for Y coordinate */
    VOS_UINT8                           ucDeltaZ_1;      /**< 1st order correction for Z coordinate */
    VOS_UINT8                           ucDeltaClkIncl;  /**<  correction for clock included or not, range [0..1] */
    VOS_UINT8                           ucDeltaClk_1;    /**< 1st order correction for clock */
    VOS_UINT8                           aucReserved[3];  /**< reserved */
} TAF_XPDS_GPS_ALM_SAT_INFO_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_FWDLINK_RSP_GPS_ALMCORR_STRU
 *
 * Description : provide  GPS almanac correction message. refer 3.2.4.2.12
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNumOfSvP;       /**< number of satellites, range [0..16] */
    VOS_UINT8                           ucRefTime;        /**< reference time */
    VOS_UINT8                           ucTOA;            /**< time of almanac */
    VOS_UINT8                           ucWeekNum;        /**< week number */
    VOS_UINT8                           ucPartNum;        /**< part number */
    VOS_UINT8                           ucTotalParts;     /**< total number of parts  */
    VOS_UINT8                           aucReserve[2];    /**< padding */
    TAF_XPDS_GPS_ALM_SAT_INFO_STRU      astSatInfo[TAF_XPDS_FL_NAVBITS_MAX];   /**< satellite information */
} TAF_XPDS_FWDLINK_RSP_GPS_ALMCORR_STRU;


/******************************************************************************
 * Name        : TAF_XPDS_FWDLINK_RSP_GPS_HEALTH_STRU
 *
 * Description : provide  GPS health information message. refer 3.2.4.2.13
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucBadSvPres;          /**< bad GPS satellite present or not, range [0..1] */
    VOS_UINT8                           ucNumBadSv;           /**< number of bad GPS, range [0..16] */
    VOS_UINT8                           aucReserve[2];        /**< padding */
    VOS_UINT8                           aucBadSvPrnNum[TAF_XPDS_FL_PRN_MAX];   /**< bad GPS PRN numbers */
} TAF_XPDS_FWDLINK_RSP_GPS_HEALTH_STRU;


/******************************************************************************
 * Name        : TAF_XPDS_FWDLINK_RSP_EXT_REJECT_STRU
 *
 * Description : provide extended reject message. refer 3.2.4.2.14
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRejReqType;          /**< rejected request type */
    VOS_UINT8                           ucRejReason;           /**< reason for rejection */
    VOS_UINT8                           ucRetryTimeIncl;       /**< ertry time present or not, range [0..1] */
    VOS_UINT8                           ucRetryTime;           /**< retry time */
} TAF_XPDS_FWDLINK_RSP_EXT_REJECT_STRU;

/** TODO 3.2.4.2.15 **/
/******************************************************************************
 * Name        : TAF_XPDS_FWDLINK_RSP_EXT_LOC_RESP_STRU
 *
 * Description : provide extended location response message. refer 3.2.4.2.15
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucFixTypeIncl;     /**< fix type information included or not, range [0..1] */
    VOS_UINT8                           ucFixType;         /**< fix type , range [0..16] */
    VOS_UINT8                           ucTimeRefIncl;     /**< time reference included or not, range [0..1] */
    VOS_UINT8                           ucLocUncHType;     /**< horizontal location uncertainity type */
    VOS_UINT32                          ulTimeRef;         /**< time reference */
    VOS_UINT32                          ulLattitude;       /**< lattitude  */
    VOS_UINT32                          ulLongitude;       /**< longitude */
    VOS_UINT8                           ucLocUncH;         /**< horizontal location uncertainity , range [0..30]*/
    VOS_UINT8                           ucLocUncHCnf;      /**< horizontal location uncertainity confidential level */
    VOS_UINT8                           ucLocUncAng;       /**< angle of axis of standard error eclipse for horizontal location uncertainity */
    VOS_UINT8                           ucLocUncA;         /**< standard deviation of error along angle specified for Horizontal loc uncertainity */
    VOS_UINT8                           ucLocUncP;         /**< standard deviation of error perpendicular angle specified for Horizontal loc uncertainity */
    VOS_UINT8                           ucHeightIncl;      /**< height information included or not, range [0..1]*/
    VOS_UINT8                           ucLocUncV;         /**< vertical location uncertainity */
    VOS_UINT8                           ucLocUncVCnf;      /**< vertical location uncertainity confidential level */
    VOS_UINT16                          usHeight;          /**< height in meters, range [-500..15883] */
    VOS_UINT16                          usVeloHor;         /**< horizontal velocity magnitude, range [0..511.75]*/
    VOS_UINT16                          usHeading;         /**< heading */
    VOS_UINT8                           ucVeloIncl;        /**< velocity information included or not, range [0..1]*/
    VOS_UINT8                           ucVeloUncHType;    /**< Horizontal velocity uncertainity type */
    VOS_UINT8                           ucVeloUncH;        /**< horizontal velocity uncertainity */
    VOS_UINT8                           ucVeloUncHCnf;     /**< horizontal velocity uncertainity confidence */
    VOS_UINT8                           ucVeloUncAng;      /**< angle of axis of standard error eclipse for horizontal velocity uncertainity */
    VOS_UINT8                           ucVeloUncA;        /**< standard deviation of error along angle specified for Horizontal velocity uncertainity, range [0..16]*/
    VOS_UINT8                           ucVeloUncP;        /**< standard deviation of error perpendicular angle specified for Horizontal velocity uncertainity */
    VOS_UINT8                           ucVeloVertIncl;    /**< vertical velocity included or not, range [0..1] */
    VOS_UINT8                           ucVeloVert;        /**< vertical velocity */
    VOS_UINT8                           ucVeloUncV;        /**< vertical velocity uncertainity */
    VOS_UINT8                           ucVeloUncVCnf;     /**< vertical velocity uncertainity confidential level */
    VOS_UINT8                           ucClockBiasIncl;   /**< clock bias included or not, range [0..1] */
    VOS_UINT8                           ucClockDriftIncl;  /**< clock drift included or not, range [0..1] */
    VOS_UINT8                           ucImprLocSupp;     /**< improved location measurement completed or not, range [0..1]*/
    VOS_UINT32                          ulClockBias;       /**< clock bias */
    VOS_UINT32                          ulClockDrift;      /**< clock drift */
}TAF_XPDS_FWDLINK_RSP_EXT_LOC_RESP_STRU;


/******************************************************************************
 * Name        : TAF_XPDS_FWDLINK_RSP_EXT_BS_CAP_STRU
 *
 * Description : provide extended BS capabilities message. refer 3.2.4.2.16
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucBsLsRev;         /**< base station location standard revision number */
    VOS_UINT8                           ucGpscId;          /**< GPS capability indicator  */
    VOS_UINT8                           ucAfltcId;         /**< advanced forward link trilateration capability indicator */
    VOS_UINT8                           ucApdcId;          /**< autonomous position determination capability indicator  */
    VOS_UINT8                           ucEphLifeExtCap;   /**< ephimeries lif extension capability indicator  */
} TAF_XPDS_FWDLINK_RSP_EXT_BS_CAP_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_ENH_BS_ALM_ANTERANGE_STRU
 *
 * Description : provide extended BS capabilities message. refer 3.2.4.2.16
 *******************************************************************************/
typedef struct
{
    VOS_UINT16                          usAntRange;    /**< antenna range */
    VOS_UINT8                           ucRefRxPow;    /**< reference recieved pilot power  */
    VOS_UINT8                           ucReserved;    /**< padding*/
} TAF_XPDS_ENH_BS_ALM_ANTERANGE_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_EBSA_PIL_TX_TYPE_00_SPEC_STRU
 *
 * Description : PIL_PX_TYPE specific when when type is 00
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           aucSectorId[TAF_XPDS_FL_SEC_ID_LEN];   /**< sector ID **/
    VOS_UINT16                          usPilotPn;          /**< Pilot PN **/
    VOS_UINT16                          usSID;              /**< system ID **/
    VOS_UINT16                          usNID;              /**< network ID **/
    VOS_UINT16                          usBaseId;           /**< base station ID **/
    VOS_UINT8                           ucSidNidAsPrev;     /**< whether SID and NID as previous or not, range [0..1] **/
    VOS_UINT8                           ucUnsolRptrs;       /**< unsolicited reports **/
    VOS_UINT8                           aucReserved[2];     /**< padding **/
}TAF_XPDS_EBSA_PIL_TX_TYPE_00_SPEC_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_EBSA_PIL_TX_TYPE_01_SPEC_STRU
 *
 * Description : PIL_PX_TYPE specific when when type is 01
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           aucRptrId[TAF_XPDS_FL_RPTR_ID_LEN];  /**< Rptr ID **/
    VOS_UINT8                           ucRptrType;     /**< RPTR type **/
    VOS_UINT8                           ucRptrIdIncl;   /**< whether RPTR included or not, range [0..1] **/
    VOS_UINT8                           aucReserved[2]; /**< padding **/
}TAF_XPDS_EBSA_PIL_TX_TYPE_01_SPEC_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_EBSA_PIL_TX_TYPE_SPEC_UNION
 *
 * Description : PIL_PX_TYPE specific data
 *******************************************************************************/
typedef union
{
    TAF_XPDS_EBSA_PIL_TX_TYPE_00_SPEC_STRU            stPilPxTyp00;   /**< if PIL_PX_TYPE is 00 **/
    TAF_XPDS_EBSA_PIL_TX_TYPE_01_SPEC_STRU            stPilPxTyp01;   /**< if PIL_PX_TYPE is 01 **/
}TAF_XPDS_EBSA_PIL_TX_TYPE_SPEC_UNION;

/******************************************************************************
 * Name        : TAF_XPDS_ENH_BS_ALM_PILOT_INFO_STRU
 *
 * Description :  enhanced base station almanac frequency information
 *******************************************************************************/
typedef struct
{
    VOS_UINT16                              usDeltaLat;          /**< difference in lattitude relative to reference */
    VOS_UINT16                              usDeltaLong;         /**< difference in longitude relative to reference  */
    VOS_UINT16                              usHeight;            /**< height of the antenna */
    VOS_UINT16                              usAvrgTerrHeight;    /**< average terraiin height */
    VOS_UINT16                              usTimeCorr;          /**< time correction */
    VOS_UINT8                               ucPilRecLen;         /**< pilot record length */
    VOS_UINT8                               ucPilTxType;         /**< pilot signal transmission type, range [0..3]  */
    VOS_UINT8                               ucLocAsPrev;         /**< location as previous or not, range [0..1]  */
    VOS_UINT8                               ucLocUncH;           /**< standard deviation of horizontal location error, range [0..16]  */
    VOS_UINT8                               ucHeightIncl;        /**< height information included or not, range [0..1]  */
    VOS_UINT8                               ucAltInfAsPrev;      /**< altitude aiding information as previous or not, range [0..1]  */
    VOS_UINT8                               ucTerrHeightVar;     /**< standard deviation of terrain height, range [0..31] */
    VOS_UINT8                               ucTimeCorrAsPrev;    /**< time correction is as previous or not, range [0..1]  */
    VOS_UINT8                               ucTimeCorrUnc;       /**< standard deviation of time correction error , range [0..16] */
    VOS_UINT8                               ucAntAngInfIncl;     /**< antenna angle information included or not, range [0..1]  */
    VOS_UINT8                               ucAntOpenAng;        /**< antenna opening angle  */
    VOS_UINT8                               ucAntAzimuth;        /**< antenna azimuth  */
    VOS_UINT8                               ucAntRngInfIncl;     /**< antenna range information included or not, range [0..1]  */
    VOS_UINT8                               ucNumOfAnrRngs;      /**< number of antenna ranges, range [0..7]  */
    TAF_XPDS_EBSA_PIL_TX_TYPE_SPEC_UNION    stPilPxTypSpc;       /**< pilot TX specific  */
    TAF_XPDS_ENH_BS_ALM_ANTERANGE_STRU      astAntenaInfo[TAF_XPDS_FL_ANTEN_MAX];    /**<  antenna record  */
} TAF_XPDS_ENH_BS_ALM_PILOT_INFO_STRU;


/******************************************************************************
 * Name        : TAF_XPDS_ENH_BS_ALM_FREQ_INFO_STRU
 *
 * Description :  enhanced base station almanac frequency information
 *******************************************************************************/
typedef struct
{
    VOS_UINT16                          usCdmaFreq;         /**< frequency assignment */
    VOS_UINT16                          usNumOfPilTxF;      /**< number of pilot signal transmitters, range [0..511]  */
    VOS_UINT8                           ucBandClass;        /**< band class */
    VOS_UINT8                           ucModeInd;          /**< mode indicator , range [0..3] */
    VOS_UINT8                           ucPilInfAsPrev;     /**< pilot information as previous or not, range [0..1]  */
    VOS_UINT8                           ucPilotIdIncl;      /**< pilot identification included or not, range [0..1] */
    VOS_UINT8                           ucRptrInfIncl;      /**<  repeater information included or not, range [0..1]  */
    VOS_UINT8                           ucRptrIdLen;        /**< repeater identification length  */
    TAF_XPDS_ENH_BS_ALM_PILOT_INFO_STRU astPilotInfo[TAF_XPDS_FL_ALM_MAX_PILOT];  /**< pilot information record  */
} TAF_XPDS_PROV_ENH_BS_ALM_FREQ_INFO_STRU;


/******************************************************************************
 * Name        : TAF_XPDS_FWDLINK_RSP_ENH_BS_ALM_STRU
 *
 * Description : provide enhanced base station almanac message. refer 3.2.4.2.17
 *******************************************************************************/
typedef struct
{
    VOS_UINT32                              ulLatRef;        /**< reference lattitude */
    VOS_UINT32                              ulLongRef;       /**< reference longitude  */
    VOS_UINT8                               ucPartNum;       /**< part number */
    VOS_UINT8                               ucTotalParts;    /**< total number of parts  */
    VOS_UINT8                               ucNumOfFreqP;    /**< number of frequency record  */
    VOS_UINT8                               ucReserved;      /**< padding  */
    TAF_XPDS_PROV_ENH_BS_ALM_FREQ_INFO_STRU astFreqInfo[TAF_XPDS_FL_FREQ_INFO_MAX]; /**< frequency record  */
} TAF_XPDS_FWDLINK_RSP_ENH_BS_ALM_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_BS_GLOBAL_INFO_REC_STRU
 *
 * Description : global info record structure
 *******************************************************************************/
typedef struct
{
    VOS_UINT32                           ulLatRef;         /**< reference lattitude */
    VOS_UINT32                           ulLongRef;        /**< reference longitude */
    VOS_UINT32                           ulTimeRef;        /**< reference time */
    VOS_UINT16                           usClkBias;        /**< clock bias */
    VOS_UINT8                            ucGlobInfRecLen;  /**< global information record length */
    VOS_UINT8                            ucLocRefIncl;     /**< location reference included or not, range [0..1] */
    VOS_UINT8                            ucLocUncAng;      /**< angle of axis for horizontal location uncertainity */
    VOS_UINT8                            ucLocUncA;        /**< standard deviation of error along angle specified for horz post uncert , range [0..31]*/
    VOS_UINT8                            ucLocUncP;        /**< standard deviation of error perpendicular angle specified for horz post uncert */
    VOS_UINT8                            ucUncVIncl;       /**< vertical iuncertainity included or not, range [0..1] */
    VOS_UINT8                            ucLocUncV;        /**< standard deviation of vertical error , range [0..7]*/
    VOS_UINT8                            ucClockIncl;      /**< whether clock information is as previous or not, range [0..1] */
    VOS_UINT8                            ucMsgSeq;         /**< message sequence number */
    VOS_UINT8                            ucClkBiasUnc;     /**< standard deviation of clock bias error, range [0..31] */
    VOS_UINT8                            ucClkDrftIncl;    /**< whether global information is as previous or not, range [0..1] */
    VOS_UINT8                            ucClkDrift;       /**< clock drift */
    VOS_UINT8                            ucClkDriftUnc;    /**< standard deviation of clock drift error, range [0..7] */
    VOS_UINT8                            ucReserved;       /**< padding */
}TAF_XPDS_BS_GLOBAL_INFO_REC_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_GEN_AQUI_ASSI_SAT_REC_STRU
 *
 * Description : GPS satellite record
 *******************************************************************************/
typedef struct
{
    VOS_UINT16                          usSvCodePh;        /**< GPS code phase */
    VOS_UINT16                          usDoppler0;        /**< 0th order doppler */
    VOS_UINT16                          usDoppler1;        /**< 1st order doppler */
    VOS_UINT16                          usDoppler2;        /**< 2nd order doppler  */
    VOS_UINT8                           ucPRNNum;          /**< satellite PRN number */
    VOS_UINT8                           ucSvCodePhInt;     /**< integer number of code periods */
    VOS_UINT8                           ucGpsBitNum;       /**< 2 leaset significant bits of bit number */
    VOS_UINT8                           ucSvCodePhWin;     /**< total code phase window, range [0..31]  */
    VOS_UINT8                           ucDopplerWin;      /**< satellite doppler window size, range [0..4] */
    VOS_UINT8                           ucSvOpModeLen;     /**< satellite operationg mode indicate length, range [0..3] */
    VOS_UINT8                           ucGpsFreq;         /**< PRN number specific fields */
    VOS_UINT8                           ucL2cMode;         /**< PRN number specific fields */
    VOS_UINT8                           ucAzimuthSv;       /**< azimuth of GPS satellite */
    VOS_UINT8                           ucElevationSv;     /**< elevation angle of GPS satellite  */
    VOS_UINT8                           ucSvHealthInd;     /**< GPS satellite health indicator  */
    VOS_UINT8                           ucReserved;        /**< padding  */
} TAF_XPDS_GEN_AQUI_ASSI_SAT_REC_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_GAA_PIL_TX_TYPE_00_SPEC_STRU
 *
 * Description : PIL_PX_TYPE specific when when type is 00
 *******************************************************************************/
typedef struct
{
    VOS_UINT16                          usPilotPn;          /**< Pilot PN **/
    VOS_UINT8                           ucUnsolRptrs;       /**< unsolicited reports **/
    VOS_UINT8                           ucReserved;        /**< padding **/
}TAF_XPDS_GAA_PIL_TX_TYPE_00_SPEC_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_GAA_PIL_TX_TYPE_01_SPEC_STRU
 *
 * Description : PIL_PX_TYPE specific when when type is 01
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           aucRptrId[TAF_XPDS_FL_RPTR_ID_LEN];  /**< Rptr ID **/
    VOS_UINT8                           ucRptrType;     /**< RPTR type **/
    VOS_UINT8                           ucRptrIdIncl;   /**< whether RPTR included or not, range [0..1] **/
    VOS_UINT8                           aucReserved[2]; /**< padding **/
}TAF_XPDS_GAA_PIL_TX_TYPE_01_SPEC_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_GAA_PIL_TX_TYPE_SPEC_UNION
 *
 * Description : PIL_PX_TYPE specific data
 *******************************************************************************/
typedef union
{
    TAF_XPDS_GAA_PIL_TX_TYPE_00_SPEC_STRU            stPilPxTyp00;   /**< if PIL_PX_TYPE is 00 **/
    TAF_XPDS_GAA_PIL_TX_TYPE_01_SPEC_STRU            stPilPxTyp01;   /**< if PIL_PX_TYPE is 01 **/
}TAF_XPDS_GAA_PIL_TX_TYPE_SPEC_UNION;

/******************************************************************************
 * Name        : TAF_XPDS_GEN_AQUI_ASSI_PIL_REC_STRU
 *
 * Description : pilot record
 *******************************************************************************/
typedef struct
{
    VOS_UINT16                          usDistance;       /**< distance to the pilot signal transmitter */
    VOS_UINT8                           ucPilRecLen;      /**< pilot record length */
    VOS_UINT8                           ucPilTxType;      /**< pilot signal transmission type, range [0..3] */
    VOS_UINT8                           ucLocAsPrev;      /**<location as previous or not, range [0..1] */
    VOS_UINT8                           ucAzimuth;        /**< azimuth of pilot signal  */
    VOS_UINT8                           ucTimeCorAsPrev;  /**< time correction as previous or not, range [0..1] */
    VOS_UINT8                           ucTimeCorr;       /**< time correction */
    VOS_UINT8                           ucTimeCorrUnc;    /**< standard deviation of time correction error */
    VOS_UINT8                           aucReserve[3];    /**< padding */
    TAF_XPDS_GAA_PIL_TX_TYPE_SPEC_UNION stPilTxTypSpc;    /**< pilot specific information */
} TAF_XPDS_GEN_AQUI_ASSI_PIL_REC_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_GEN_AQUI_ASSI_FREQ_REC_STRU
 *
 * Description : frequency record
 *******************************************************************************/
typedef struct
{
    VOS_UINT16                          usCdmaFreq;        /**< frequency assignment */
    VOS_UINT8                           ucBandCls;         /**< band class */
    VOS_UINT8                           ucModeInd;         /**< mode indicator */
    VOS_UINT8                           ucPilInfAsPrev;    /**< pilot information as previous */
    VOS_UINT8                           ucRptrInfIncl;     /**< repeator information included or not, range [0..1]  */
    VOS_UINT8                           ucRptrIdLen;       /**< repeator identification length */
    VOS_UINT8                           ucNumOfPilTxF;     /**< number of pilot signal, range [0..63] */
    TAF_XPDS_GEN_AQUI_ASSI_PIL_REC_STRU astPilotRec[TAF_XPDS_FL_ASSI_PILREC_MAX];
} TAF_XPDS_GEN_AQUI_ASSI_FREQ_REC_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_FWDLINK_RSP_GEN_AQUI_ASSI_STRU
 *
 * Description : provide general aquisition assitance message. refer 3.2.4.2.18
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                               ucPartNum;             /**< part number */
    VOS_UINT8                               ucTotalParts;          /**< total number of parts */
    VOS_UINT8                               ucGlobInfoAsPrev;      /**< global information present is as previous or not, range [0..1] */
    VOS_UINT8                               ucReserved;            /**< padding  */
    TAF_XPDS_BS_GLOBAL_INFO_REC_STRU        stGlobInfo;            /**< global information record  */
    VOS_UINT8                               ucSvInfInclP;          /**< satellite information included or not, range [0..1] */
    VOS_UINT8                               ucCodePhWinIncl;       /**< code phase search window information included or not, range [0..1] */
    VOS_UINT8                               ucDopp2Incl;           /**< 2nd deviation of doppler included or not, range [0..1] */
    VOS_UINT8                               ucDoppWinIncl;         /**< doppler window information included or not, range [0..1]  */
    VOS_UINT8                               ucSvOpModeIncl;        /**< satellite operation mode included or not, range [0..1] */
    VOS_UINT8                               ucAzElIncl;            /**< azimuth and elevation angle include or not, range [0..1] */
    VOS_UINT8                               ucSvHealthIncl;        /**< GPS satellite health information included or not, range [0..1] */
    VOS_UINT8                               ucNumOfSvP;            /**< number of satellite records, range [0..16]  */
    TAF_XPDS_GEN_AQUI_ASSI_SAT_REC_STRU     astSatRec[TAF_XPDS_FL_SAT_INFO_MAX];         /**< satellite records  */
    VOS_UINT8                               ucBsInfInclP;          /**< BS information included or not, range [0..1] */
    VOS_UINT8                               ucNumOfFreqP;          /**< number of frequency record, range [0..16] */
    VOS_UINT8                               aucReserve1[2];            /**<   */
    TAF_XPDS_GEN_AQUI_ASSI_FREQ_REC_STRU    astFreqRec[TAF_XPDS_FL_SAT_INFO_MAX];
} TAF_XPDS_FWDLINK_RSP_GEN_AQUI_ASSI_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_GPS_NAV_DATA_REC_INFO_STRU
 *
 * Description : navigation data record information
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNavMsgForm;       /**< navigation message format, range [0..4] */
    VOS_UINT8                           ucNumOfSvDr;        /**< number of sattelite PRN record, rannge [0..16] */
    VOS_UINT8                           aucReserve[2];      /**< padding */
    VOS_UINT8                           aucNavMsgBits[TAF_XPDS_FL_NAVBITS_MAX * 2]; /**< padding */
    VOS_UINT8                           aucPRNNum[TAF_XPDS_FL_PRN_MAX];      /**< satellite PRN numbers */
} TAF_XPDS_GPS_NAV_DATA_REC_INFO_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_FWDLINK_RSP_EXTGPS_SENASSI_STRU
 *
 * Description : provide  extended GPS sensitivity assistence message. refer 3.2.4.2.19
 *******************************************************************************/
typedef struct
{
    VOS_UINT16                              usRefBitNum;       /**< reference bit number */
    VOS_UINT8                               ucPartNum;         /**< part number */
    VOS_UINT8                               ucTotalParts;      /**< total number of parts */
    VOS_UINT8                               ucNavMsgFormIncl;  /**< navigation message format information iuncluded or not, range [0..1] */
    VOS_UINT8                               ucNavBitLen;       /**< navigation message bit length */
    VOS_UINT8                               ucNumOfDrP;        /**< number of data records, range [1..16] */
    VOS_UINT8                               ucReserved;        /**< padding */
    TAF_XPDS_GPS_NAV_DATA_REC_INFO_STRU     astDataRec[TAF_XPDS_FL_DATREC_NUM];    /**< data records */

}TAF_XPDS_FWDLINK_RSP_EXTGPS_SENASSI_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_GPS_NAVBITS_FRAME_INFO_STRU
 *
 * Description : navigation bits frame information
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           aucSubF45[TAF_XPDS_NAVBITS_SUB45_SIZE]; /**< sub frame 4, 5 */
    VOS_UINT8                           ucFrameNum;    /**< frame number */
} TAF_XPDS_GPS_NAVBITS_FRAME_INFO_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_FWDLINK_RSP_EXTGPS_NAVBITS_STRU
 *
 * Description : provide  extended GPS navigation bits message. refer 3.2.4.2.20
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                               ucPartNum;        /**< part number */
    VOS_UINT8                               ucTotalParts;     /**< total number of parts  */
    VOS_UINT8                               ucNumOfSvP;       /**< total number of satellites */
    VOS_UINT8                               ucNumOfFrP;       /**< number of frames, range [0..31] */
    TAF_XPDS_GPS_NAVBITS_SAT_INFO_STRU      astSatInfo[TAF_XPDS_FL_EXTBITS_NAV_SAT_SIZE];   /**< satellite information */
    TAF_XPDS_GPS_NAVBITS_FRAME_INFO_STRU    astFrameInfo[TAF_XPDS_FL_EXTBITS_NAV_FRAM_SIZE]; /**< frame information */
}TAF_XPDS_FWDLINK_RSP_EXTGPS_NAVBITS_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_EXTGPS_SAT_INFO_STRU
 *
 * Description :  Extended GPS almanac correction satellite information
 *******************************************************************************/
typedef struct
{
    VOS_UINT32                           ulDeltaClk;       /**< correction for clock */
    VOS_UINT16                           usDeltaClk_1;     /**< 1st order correction for clock  */
    VOS_UINT16                           usDeltaClk_2;     /**< 3nd order correction for clock */
    VOS_UINT16                           usDeltaX;         /**< correction for X coordinate  */
    VOS_UINT16                           usDeltaY;         /**< correction for Y coordinate */
    VOS_UINT16                           usDeltaZ;         /**< correction for Z coordinate */
    VOS_UINT16                           usDeltaX_1;       /**< 1st order correction for X coordinate */
    VOS_UINT16                           usDeltaY_1;       /**< 1st order correction for Y coordinate */
    VOS_UINT16                           usDeltaZ_1;       /**< 1st order correction for Z coordinate */
    VOS_UINT8                            ucDeltaX_2;       /**< 2nd order correction for X coordinate  */
    VOS_UINT8                            ucDeltaY_2;       /**< 2nd order correction for Y coordinate */
    VOS_UINT8                            ucDeltaZ_2;       /**< 2nd order correction for Z coordinate */
    VOS_UINT8                            ucSvPrnNum;       /**< satellite ORN number */
    VOS_UINT8                            ucDeltaXYZIncl;   /**< correction for XYZ include or not, range [0..1] */
    VOS_UINT8                            ucDeltaClkIncl;   /**< correction for clock include or not, range [0..1] */
    VOS_UINT8                            aucReserved[2];   /**< padding */
} TAF_XPDS_EXTGPS_SAT_INFO_STRU;


/******************************************************************************
 * Name        : TAF_XPDS_FWDLINK_RSP_EXTGPS_ALMCORR_STRU
 *
 * Description : provide Extended GPS almanac correction message. refer 3.2.4.2.21
 *******************************************************************************/
typedef struct
{
    VOS_UINT16                           usTimeRef;       /**< reference time */
    VOS_UINT8                            ucPartNum;       /**< part number  */
    VOS_UINT8                            ucTotalParts;    /**< total number of parts present */
    VOS_UINT8                            ucWeekNum;       /**< GPS week number, range [0..255] */
    VOS_UINT8                            ucTOA;           /**< time of almanac */
    VOS_UINT8                            ucNumOfSvP;      /**< number of satellites in this part, range [1..16] */
    VOS_UINT8                            ucReserved;      /**< padding */
    TAF_XPDS_EXTGPS_SAT_INFO_STRU        astSatInfo[TAF_XPDS_FL_SAT_INFO_MAX];  /**< satellite information */
} TAF_XPDS_FWDLINK_RSP_EXTGPS_ALMCORR_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_FWDLINK_RSP_EXTGPS_HEALTH_STRU
 *
 * Description : provide Extended GPS health information message. refer 3.2.4.2.22
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                            ucBadSvPres;         /**< bad satellite information present or not, range [0..1] */
    VOS_UINT8                            ucNumOfBadSv;        /**< number of bad satellites, range [0..16]  */
    VOS_UINT8                            aucReserve[2];       /**< padding */
    VOS_UINT8                            aucSatPrnNum[TAF_XPDS_FL_PRN_MAX];    /**< satellite PRN numbers */
} TAF_XPDS_FWDLINK_RSP_EXTGPS_HEALTH_STRU;


/******************************************************************************
 * Name        : TAF_XPDS_FWDLINK_RSP_GPS_COARLOC_STRU
 *
 * Description : provide GPS coarse location assitance message. refer 3.2.4.2.23
 *******************************************************************************/
typedef struct
{
    VOS_UINT16                           usRefLat;         /**< reference lattitude */
    VOS_UINT16                           usRefLong;        /**< reference longitude  */
} TAF_XPDS_FWDLINK_RSP_GPS_COARLOC_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_FWDLINK_RSP_GPS_COARAQUI_STRU
 *
 * Description : provide GPS coarse aquisition assitance message. refer 3.2.4.2.24
 *******************************************************************************/
typedef struct
{
    VOS_UINT32                           ulSatVisList;         /**< visible satellite list */
} TAF_XPDS_FWDLINK_RSP_GPS_COARAQUI_STRU;


/******************************************************************************
 * Name        : TAF_XPDS_DGPS_ASSIS_SAT_INFO_STRU
 *
 * Description :DGPS assistance satellite information
 *******************************************************************************/
typedef struct
{
    VOS_UINT16                          usPRC;          /**< psuedorange correction */
    VOS_UINT8                           ucSatId;        /**< satellite ID code */
    VOS_UINT8                           ucIode;         /**< issue of data */
    VOS_UINT8                           ucUDRE;         /**< user differencial range error, range [0..3] */
    VOS_UINT8                           ucRRC;          /**< psuedorange rate correction */
    VOS_UINT8                           aucReserve[2];  /**< padding */
} TAF_XPDS_DGPS_ASSIS_SAT_INFO_STRU;


/******************************************************************************
 * Name        : TAF_XPDS_FWDLINK_RSP_DGPS_ASSIS_STRU
 *
 * Description : provide DGPS assistence message. refer 3.2.4.2.26
 *******************************************************************************/
typedef struct
{
    VOS_UINT32                          ulGpsTow;        /**< GPS time of week */
    VOS_UINT8                           ucStatHealth;    /**< status or health, range [0..7] */
    VOS_UINT8                           ucNumOfStat;     /**< number of GPS satellites, range [0..16] */
    VOS_UINT8                           aucReserved[2];
    TAF_XPDS_DGPS_ASSIS_SAT_INFO_STRU   astSatInfo[TAF_XPDS_FL_SAT_INFO_MAX];  /**< satellite information list */
} TAF_XPDS_FWDLINK_RSP_DGPS_ASSIS_STRU;

/******************************************************************************
 * Name        : TAF_XPDS_GPS_REALTIME_SAT_INFO_STRU
 *
 * Description :GPS real time satellite information
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSatId;        /**< satellite ID code */
    VOS_UINT8                           ucAPrc;         /**< adjusted psuedorange correction, range [0..3] */
    VOS_UINT8                           aucReserve[2];  /**< padding */
} TAF_XPDS_GPS_REALTIME_SAT_INFO_STRU;


/******************************************************************************
 * Name        : TAF_XPDS_FWDLINK_RSP_GPS_REALTIME_INTE_STRU
 *
 * Description : provide GPS realtime integrity information message. refer 3.2.4.2.26
 *******************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIntegrityType;    /**< type of real time integrity data present */
    VOS_UINT8                           ucFaultySvPres;     /**< faulty GPS satellites present or not, range [0..1] */
    VOS_UINT8                           ucNumOfFaultSv;     /**< number of faulty satellites, range [0..16] */
    VOS_UINT8                           ucNSAT;             /**< number of satellite record , range [0..16] */
    VOS_UINT8                           ucASTAT;            /**< adjusted state of satellite, range [0..3] */
    VOS_UINT8                           aucReserve[3];      /**< padding */
    VOS_UINT8                           aucFaultSvPrn[TAF_XPDS_FL_PRN_MAX];  /**< PRN number of faulty satellites */
    TAF_XPDS_GPS_REALTIME_SAT_INFO_STRU astSatInfo[TAF_XPDS_FL_SAT_INFO_MAX];     /**< satellite information list */
} TAF_XPDS_FWDLINK_RSP_GPS_REALTIME_INTE_STRU;

/*****************************************************************************
  8 The Union Define
*****************************************************************************/


/*****************************************************************************
  9 Other Defines
*****************************************************************************/


/*****************************************************************************
  10 The Declaration Of The Function
*****************************************************************************/
extern VOS_UINT32 TAF_XPDS_DecodeMpcStartPosRsp(
        VOS_UINT32                          ulDataLen,
        VOS_UINT8                          *pucData,
        TAF_XPDS_MPC_START_POS_RSP_STRU    *pstStartPosRsp
);

extern VOS_UINT8 TAF_XPDS_DecodeGetOneBitFromOneByte(
    VOS_UINT8                           ucBuffer,
    VOS_UINT8                           ucBitPos
);

extern VOS_UINT32 TAF_XPDS_DecodeGetBitsFromBytes(
    VOS_UINT8                          *pucBuffer,
    VOS_UINT16                          usBitPos,
    VOS_UINT8                           ucBitNum
);

extern VOS_UINT32 TAF_XPDS_DecodeMpcPosReportRsp(
    VOS_UINT32                          ulDataLen,
    VOS_UINT8                          *pucData,
    TAF_XPDS_MPC_POS_REPORT_RSP_STRU   *pstPosReportRsp
);

extern VOS_UINT32 TAF_XPDS_DecodeXsmsMpcPosReq(
    VOS_UINT32                           ulDataLen,
    VOS_UINT8                           *pucData,
    TAF_XPDS_RCV_XSMS_POS_REQ_STRU      *pstPosReportRsp
);

extern TAF_XPDS_XSMS_MSG_DECODE_RSLT_ENUM_UINT8 TAF_XPDS_DecodeXsmsRcvMsg(
    VOS_UINT32                          ulDataLen,
    VOS_UINT8                          *pucData,
    TAF_XPDS_RCV_XSMS_MSG_STRU         *pstXsmsMsg
);


VOS_UINT32 TAF_XPDS_DecodeProvGpsEphimeries(
    VOS_UINT8                              *pucHeadBuf
);

extern VOS_UINT32 TAF_XPDS_DecodePdeAddr(
    VOS_UINT32                          ulDataLen,
    VOS_UINT8                          *pucData,
    VOS_UINT16                         *pusBytePos,
    TAF_XPDS_PDE_ADDR_STRU             *pstPdeAddr
);

extern VOS_UINT32 TAF_XPDS_DecodeProvGpsAlmanac(
    VOS_UINT8                              *pucHeadBuf
);

extern VOS_UINT32 TAF_XPDS_DecodeProvGpsAcqAssist(
    VOS_UINT8                              *pucHeadBuf
);

extern VOS_UINT32 TAF_XPDS_DecodeProvLocResp(
    VOS_UINT8                              *pucHeadBuf
);

extern VOS_UINT32 TAF_XPDS_DecodeReject(
    VOS_UINT8                              *pucHeadBuf
);

extern VOS_UINT32 TAF_XPDS_DecodeRequestCancellation(
    VOS_UINT8                          *pcHeadBuf
);

extern VOS_UINT32 TAF_XPDS_DecodeRequestPilotPhaseMeas(
    VOS_UINT8                          *pcHeadBuf
);

extern VOS_UINT32 TAF_XPDS_DecodeRequestLocResp(
    VOS_UINT8                          *pcHeadBuf
);


extern VOS_UINT32 TAF_XPDS_DecodeRequestPseudoRangeMeas(
    VOS_UINT8                          *pcHeadBuf
);

VOS_UINT32 TAF_XPDS_DecodeRequestMsInfo(
    VOS_UINT8                          *pucHeadBuf
);

extern VOS_UINT32 TAF_XPDS_DecodeOnePdeMsg(
    VOS_UINT8                          *pucOneMsgBuf,
    VOS_UINT32                         *pulOutDataMask
);

extern VOS_UINT32 TAF_XPDS_DecodeReqInfo(
    VOS_UINT8                          *pucOneMsgBuf,
    TAF_XPDS_PD_MSG_HEADER_STRU        *pstPdMsgHeader,
    VOS_UINT32                         *pulOutDataMask
);

extern VOS_UINT32 TAF_XPDS_DecodeRespInfo(
    VOS_UINT8                          *pucOneMsgBuf,
    TAF_XPDS_PD_MSG_HEADER_STRU        *pstPdMsgHeader,
    VOS_UINT32                         *pulOutDataMask
);

extern VOS_UINT32 TAF_XPDS_DecodeGetRespIndex(
    VOS_UINT8                          *pucOneMsgBuf,
    TAF_XPDS_PD_MSG_HEADER_STRU        *pstPdeMsgHeader
);

extern VOS_UINT32 TAF_XPDS_DecodePdeHeaderInfo(
    VOS_UINT8                          *pucHeadBuf,
    TAF_XPDS_PD_MSG_HEADER_STRU        *pstPdeMsgHeader
);

extern TAF_XPDS_DecodeReqHandler TAF_XPDS_DecodeGetReqHandler(
    VOS_UINT32                          ulReqType
);

extern TAF_XPDS_DecodeRespHandler TAF_XPDS_DecodeGetRespHandler(
    VOS_UINT32                          ulRespType
);

VOS_UINT32 TAF_XPDS_DecodeGetPdeDataMaskByRespType(
    VOS_UINT32                          ulRespType
);

VOS_UINT32 TAF_XPDS_DecodeGetPdeDataMaskByReqType(
    VOS_UINT32                          ulRespType
);

extern VOS_UINT32 TAF_XPDS_DecodeGetValue(
    VOS_UINT8                           ucNumOfBits,
    VOS_UINT32                         *pulTotalBitsPrc,
    VOS_UINT8                          *pucCurrBuf,
    VOS_UINT32                         *pulCurIdx
);

extern VOS_UINT8 TAF_XPDS_GetMaskValue(
    VOS_UINT8                           ucBitsLeft
);


VOS_UINT32 TAF_XPDS_DecodeForwardPdeData(
    VOS_UINT8                          *pucMsgBuf,
    VOS_UINT32                          ulTotLength,
    VOS_UINT32                         *pulOutDataMask
);

extern VOS_UINT32 TAF_XPDS_DecodeDataBurstMsg(
    TAF_XPDS_DATA_BURST_MSG_STRU       *pstDataBurMsg,
    VOS_UINT8                          *pcBurstMsg
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


