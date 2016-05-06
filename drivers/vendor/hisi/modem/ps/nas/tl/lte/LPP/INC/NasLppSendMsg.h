/******************************************************************************

    Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : NasLppSendMsg.h
  Description     : NasLppSendMsg.c header file
  History         :
     1.XiaoJun       2015-7-30     Draft Enact
     2.
******************************************************************************/

#ifndef __NASLPPSENDMSG_H__
#define __NASLPPSENDMSG_H__


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "vos.h"
#include  "LPPLRrcInterface.h"


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*****************************************************************************
  #pragma pack(*)    设置字节对齐方式
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif


/*****************************************************************************
  2 macro
*****************************************************************************/


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/


/*****************************************************************************
   5 STRUCT
*****************************************************************************/
/*****************************************************************************
 结构名称   : LPP_LRRC_GPS_DATA_INFO_STRU
 协议表格   :
 结构说明   : LPP发送给RRC的位置信息数据结构
*****************************************************************************/
typedef struct
{
    /*

    0: 删除数据，RRC清除本地数据
    1: 代表有新数据，覆盖本地数据

    */

    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucGnssDataFlag;

    /* 0:代表没有数据，1:有数据*/
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucHorizontalVelocityFlag;

    /* 0:代表没有数据，1:有数据*/
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucGnssTodMsecFlag;

    /* 0:代表没有数据，1:有数据*/
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                   ucLocationDataFlag;

    VOS_UINT8                                       aucHorizontalVelocityData[LPP_LRRC_MAX_CHORIZONTAL_VELOCITY_DATA_LEN];
    VOS_UINT8                                       aucGnssTodMsecData[LPP_LRRC_MAX_GNSS_TOD_MSEC_DATA_LEN];
    VOS_UINT8                                       aucReserved[2];

    LPP_LRRC_LOCATION_COORDINATES_DATA_STRU         stLocationCoordinatesData;
}LPP_LRRC_GNSS_DATA_INFO_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_VOID NAS_LPP_SndLppLrrcEcidMeasReq
(
    VOS_UINT8                           ucSessionIndx,
    VOS_UINT8                           ucSessionTransIndx,
    LPP_LRRC_LCS_MEAS_CMD_ENUM_UINT8    ucLcsMeasCmd
);
extern VOS_VOID NAS_LPP_SndOtdoaMeasReq
(
    VOS_UINT8                           ucSessionIndx,
    VOS_UINT8                           ucSessionTransIndx,
    LPP_LRRC_LCS_MEAS_CMD_ENUM_UINT8    ucLcsMeasCmd
);
extern VOS_VOID NAS_LPP_SndLppLrrcLocationInfo
(
    MTA_LPP_MEAS_REF_TIME_STRU                             *pstMtaLppMeasRefTime,
    LOC_COM_VELOCITY_STRU                                  *pstVelocityEstimate,
    LOC_COM_COORDINATE_STRU                                *pstLocationEstimate,
    LPP_LRRC_INFO_FLAG_ENUM_UINT8                           ucGnssDataFlag
);
extern VOS_VOID  NAS_LPP_SndIntraLppMsg
(
    VOS_UINT32                                  ulOpId,
    NAS_LPP_MSG_IDENTITY_STRU           *pstLppMsgIdentity,
    NAS_LPP_ERROR_CODE_ENUM_UINT32       enErrorCode
);
extern VOS_UINT8  NAS_LPP_SndUpLppErrorMsg
(
    VOS_UINT32                          ulSessionId,
    NAS_LPP_TRANS_ID_STRU              *pstTransID,
    LPP_COMMON_IES_ERROR_ENUM_UINT8     enErrorCause,
    VOS_BOOL                            enNeedAck,
    VOS_BOOL                            bEndTransaction

);
extern VOS_VOID  NAS_LPP_PreGnssAssistDataParameter
(
    MTA_LPP_GNSS_ASSIST_DATA_REQ_STRU       *pstMtaLppGnssAssistDataReq,
    LPP_REQUEST_ASSIST_DATA_R9_IES_STRU     *pstRequestAsisstDataR9
);
extern VOS_UINT8  NAS_LPP_SndUplinkReqAssistDataMsg
(
    VOS_UINT8                           ucSessionIndx,
    VOS_UINT8                           ucSessionTransIndx,
    VOS_UINT8                           ucTransIndx,
    VOS_BOOL                            enOtdoaAssist,
    VOS_BOOL                            enGnssAssist,
    MTA_LPP_GNSS_ASSIST_DATA_REQ_STRU  *pstMtaLppGnssAssistDataReq
);
extern VOS_UINT8  NAS_LPP_SndUpLppAbortMsg
(
    VOS_UINT8                           ucSessionIndx,
    VOS_UINT8                           ucSessionTransIndx,
    VOS_UINT8                           ucTransIndx,
    LPP_COMMON_IES_ABORT_ENUM_UINT8     enAbortCause,
    VOS_BOOL                            enNeedAck,
    VOS_BOOL                            bEndTransaction
);
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

#endif /* end of NasLppSendMsg.h */
