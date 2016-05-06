/******************************************************************************


        @(#)Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : CssProcCommMsg.h
    Description : CSS处理Comm消息的头文件
    History     :
      1.wangchen 00209181   2015-05-14  Draft Enact


******************************************************************************/

#ifndef __CSSPROCCOMMMSG_H__
#define __CSSPROCCOMMMSG_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/

#include    "vos.h"
#include    "CssInterface.h"
#include    "CssPublic.h"
#include    "PsCommonDef.h"

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
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_VOID CSS_ProcCommMsgStopBandScanReq
(
    const CSS_STOP_BAND_SCAN_REQ_STRU *pstStopBandScanReq
);

extern VOS_VOID CSS_ProcCommMsg(const VOS_VOID *pRcvMsg);

extern VOS_VOID CSS_ProcCommMsgBandScanReq
(
    const CSS_MULTI_BAND_SCAN_REQ_STRU  *pRcvMsg
);
extern VOS_VOID CSS_ProcCommMsgCurrGeoInd
(
    const CSS_CURR_GEO_IND_STRU *pstCurrGeoInd
);
extern VOS_VOID CSS_SndCurrGeoRsp(VOS_UINT32 ulPid, CSS_RESULT_ENUM_UINT32 enRslt);

extern VOS_VOID CSS_SndCommMsgBandScanCnf
(
    VOS_UINT32                                      ulReceiverPid,
    VOS_UINT32                                      ulOpid,
    CSS_MULTI_BAND_SCAN_RESULT_ENUM_UINT8           enResult
);
extern VOS_VOID CSS_SndMsgAsStopBandScanCnf
(
    VOS_UINT32                                      ulReceiverPid,
    CSS_RESULT_ENUM_UINT32                          enResult
);
extern VOS_VOID CSS_SndMsgAsBandScanCnf
(
    VOS_UINT32                                      ulReceiverPid,
    VOS_UINT32                                      ulOpid,
    CSS_MULTI_BAND_SCAN_RESULT_ENUM_UINT8           enResult
);
extern VOS_VOID CSS_SndAsBandScanRslt
(
    VOS_UINT32                                    ulReceiverPid,
    VOS_UINT32                                    ulOpid
);
extern VOS_VOID CSS_SndMsgAsBandScanInd
(
    const CSS_AS_BAND_SCAN_RSLT_STRU             *pstBandRslt,
    VOS_UINT8                                     ucIsEnd,
    VOS_UINT32                                    ulReceiverPid,
    VOS_UINT32                                    ulOpid
);


extern VOS_VOID CSS_AsBandScanReqMsgSave
(
    const CSS_AS_BAND_SCAN_REQ_STRU              *pstBandScanReq
);
extern VOS_VOID CSS_AsStopBandScanReqMsgSave
(
    const CSS_AS_STOP_BAND_SCAN_REQ_STRU         *pstAsStopBandScanReq
);
extern VOS_VOID CSS_ProcMsgAsBandScanReq
(
    const CSS_AS_BAND_SCAN_REQ_STRU              *pRcvMsg
);
extern VOS_VOID CSS_ProcMsgAsStopBandScanReq
(
    const CSS_AS_STOP_BAND_SCAN_REQ_STRU  *pRcvMsg
);

extern VOS_VOID CSS_SndCommMsgStopBandScanCnf
(
    VOS_UINT32                                      ulReceiverPid,
    CSS_RESULT_ENUM_UINT32                          enResult
);
extern VOS_VOID  CSS_JudgeRssiExistType
(
    CSS_COVERAGE_TYPE_ENUM_UINT8                    *penGsmCoverageType,
    CSS_COVERAGE_TYPE_ENUM_UINT8                    *penUmtsFddCoverageType,
    CSS_COVERAGE_TYPE_ENUM_UINT8                    *penLteCoverageType
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

#endif /* end of CssProcLmmMsg.h */





