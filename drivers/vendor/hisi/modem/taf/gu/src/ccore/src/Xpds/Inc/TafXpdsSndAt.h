/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXpdsSndAt.h
  版 本 号   : 初稿
  作    者   : g00256031
  生成日期   : 2015年08月25日
  功能描述   : TafXpdsSndAt.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年08月25日
    作    者   : g00256031
    修改内容   : 创建文件
******************************************************************************/

#ifndef _TAF_XPDS_AND_AT_H_
#define _TAF_XPDS_AND_AT_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "AtMnInterface.h"
#include "AtXpdsInterface.h"
#include "TafXpdsEncode.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/


/*****************************************************************************
  3 枚举定义
*****************************************************************************/


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
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
VOS_VOID TAF_XPDS_SndAtMsg(
    AT_APPCTRL_STRU                    *pAppCtrl,
    VOS_UINT32                          ulMsgId,
    VOS_UINT32                          ulLen,
    VOS_UINT8                          *pData
);

VOS_VOID TAF_XPDS_SndAtMsgNoData(
    AT_APPCTRL_STRU                    *pAppCtrl,
    VOS_UINT32                          ulMsgId
);

VOS_VOID TAF_XPDS_SndAtGpsStartReq(
    AT_APPCTRL_STRU                    *pAppCtrl
);

VOS_VOID TAF_XPDS_SndAtApOpenCagpsDataCall(VOS_VOID);

VOS_VOID TAF_XPDS_SndAtApCloseCagpsDataCall(VOS_VOID);

VOS_VOID TAF_XPDS_SndAtApOpenSocketReq
(
    AT_XPDS_SERVER_MODE_ENUM_UINT32     enServerMode,
    VOS_UINT32                          ulIpAddr,
    VOS_UINT32                          ulPortNum
);

VOS_VOID TAF_XPDS_SndAtApCloseSocketReq
(
    AT_XPDS_SERVER_MODE_ENUM_UINT32     enServerMode,
    VOS_UINT32                          ulIpAddr,
    VOS_UINT32                          ulPortNum
);

VOS_VOID TAF_XPDS_SndAtGpsTimeSyncInfo(
    CAS_XPDS_TIME_SYNC_IND_STRU        *pstRcvSyncTime
);

VOS_VOID TAF_XPDS_SndAtGpsReflocInfoCnf(
    AT_APPCTRL_STRU                    *pstAppCtrl,
    XPDS_AT_GPS_REFLOC_INFO_STRU       *pstRefloc
);

VOS_VOID TAF_XPDS_SndAtApMpcStartPosReq
(
    VOS_VOID
);

VOS_VOID TAF_XPDS_SndAtApMpcPosReportReq
(
    VOS_VOID
);

VOS_VOID TAF_XPDS_SndAtApPdeSessionEndMsg(VOS_VOID);

VOS_VOID TAF_XPDS_SndAtApPdeRejectRsp(
    TAF_XPDS_REVLINK_RSP_REJECT_STRU                       *pstRejInfo
);

VOS_VOID TAF_XPDS_FillMpcStartPosReq
(
    TAF_XPDS_MPC_START_POS_REQ_STRU    *pstStartPosReq
);

VOS_VOID TAF_XPDS_FillMpcPosReportReq
(
    TAF_XPDS_MPC_POS_REPORT_STRU       *pstPosReportReq
);

VOS_VOID TAF_XPDS_SndAtApReverseData
(
    AT_XPDS_SERVER_MODE_ENUM_UINT32     enServerMode,
    const VOS_UINT8                    *pucData,
    VOS_UINT32                          ulLen
);

VOS_VOID TAF_XPDS_SndAtGpsAbortPosInd
(
    XPDS_AT_ABORT_POS_REASON_ENUM_UINT16                    enAbortReason
);

VOS_VOID TAF_XPDS_SndAtGpsStopCnf(VOS_VOID);

VOS_VOID TAF_XPDS_SndAtGpsNiSessionInd(
    TAF_XPDS_RCV_XSMS_POS_REQ_STRU     *pstXsmsMsg
);

VOS_VOID TAF_XPDS_SndAtGpsCancelNiSession(VOS_VOID);

VOS_VOID TAF_XPDS_SndAtGpsAcqAssistData(VOS_VOID);

VOS_VOID TAF_XPDS_SndAtGpsIonInfo(VOS_VOID);

VOS_VOID TAF_XPDS_SndAtGpsEphInfo(VOS_VOID);

VOS_VOID TAF_XPDS_SndAtGpsAlmInfo(VOS_VOID);

VOS_VOID TAF_XPDS_SndAtGpsPositionInfo(VOS_VOID);

VOS_UINT32 TAF_XPDS_CalcTimeInWeek(VOS_UINT32 ulRefTime);

VOS_UINT64 TAF_XPDS_CalcAbsTime(VOS_UINT32 ulRefTime);

VOS_VOID TAF_XPDS_SndAtGpsCpNiStop(
    VOS_VOID
);

VOS_VOID TAF_XPDS_SndAtGpsCpNiStart(
    VOS_VOID
);

VOS_VOID TAF_XPDS_SndAtGpsUtsTestStartReq(
    VOS_UINT32                          ulDataLen,
    VOS_UINT8                          *pucData
);

VOS_VOID TAF_XPDS_SndAtGpsUtsTestStopReq(
    VOS_UINT32                          ulDataLen,
    VOS_UINT8                          *pucData
);

VOS_VOID TAF_XPDS_SetPosReportLocInfo(
    TAF_XPDS_MPC_POS_REPORT_STRU       *pstPosReportReq
);

VOS_VOID TAF_XPDS_SndAtUtsGpsPosInfo(VOS_VOID);

VOS_VOID TAF_XPDS_SndAtOmGpsTestStartReq(
    TAF_XPDS_FIX_MODE_ENUM_UINT8        enFixMode,
    TAF_XPDS_GPS_START_MODE_ENUM_UINT8  enStartMode
);

VOS_VOID TAF_XPDS_SndAtOmGpsTestStopReq(VOS_VOID);

VOS_VOID TAF_XPDS_SndOmStartGpsFixCnf(
    OM_NAS_CDMA_START_GPS_FIX_REQ_STRU *pstMsgStartReq
);

VOS_VOID TAF_XPDS_SndOmStopGpsFixCnf(
    OM_NAS_CDMA_STOP_GPS_FIX_REQ_STRU  *pstMsgStopReq
);

VOS_VOID TAF_XPDS_SndOmGpsFixRsltInd(
    NAS_OM_CDMA_GPS_FIX_RSLT_ENUM_UINT8 enFixRslt
);

VOS_VOID TAF_XPDS_SndOmGpsSignalMsgInd(
    NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_ENUM_UINT8              enMsgType
);

VOS_VOID TAF_XPDS_SndOmGpsFixStartInd(VOS_VOID);

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

#endif /* end of TafXpdsSndAt.h */

