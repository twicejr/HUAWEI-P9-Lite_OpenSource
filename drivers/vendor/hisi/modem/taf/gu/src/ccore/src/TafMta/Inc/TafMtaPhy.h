/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafMtaPhy.h
  版 本 号   : 初稿
  作    者   :
  生成日期   : 2013年03月11日
  最近修改   :
  功能描述   : TafMtaPhy.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年03月11日
    作    者   :
    修改内容   : 创建文件

******************************************************************************/

#ifndef __TAFMTAPHY_H__
#define __TAFMTAPHY_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "TafMtaCtx.h"
#include "MtaPhyInterface.h"

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
VOS_VOID TAF_MTA_RcvAtBodySarSetReq(VOS_VOID *pMsg);

VOS_VOID TAF_MTA_RcvPhyBodySarSetCnf(VOS_VOID *pMsg);

VOS_VOID TAF_MTA_RcvTiWaitPhySetBodySarExpired(VOS_VOID *pMsg);

VOS_VOID TAF_MTA_SndPhyEmergencyCallStatus(
    MTA_PHY_EMERGENCY_CALL_STATUS_ENUM_UINT16               enState
);

VOS_VOID TAF_MTA_RcvTiWaitGrrSetNCellMonitorExpired(VOS_VOID *pMsg);
VOS_VOID TAF_MTA_RcvTiWaitGrrQryNCellMonitorExpired(VOS_VOID *pMsg);

VOS_VOID TAF_MTA_RcvAtSetHandleDectReq(
    VOS_VOID                           *pMsg
);

VOS_VOID TAF_MTA_RcvAtQryHandleDectReq(
    VOS_VOID                           *pMsg
);

VOS_UINT32 TAF_MTA_SndPhySetHandleDectReqMsg(
    VOS_UINT16                          usHandleType
);

VOS_UINT32 TAF_MTA_SndPhyQryHandleDectReqMsg(VOS_VOID);

VOS_VOID TAF_MTA_RcvPhyHandleDectSetCnf(
    VOS_VOID                           *pMsg
);

VOS_VOID TAF_MTA_RcvPhyHandleDectQryCnf(
    VOS_VOID                           *pMsg
);

VOS_VOID TAF_MTA_RcvTiWaitPhySetHandleDectExpired(
    VOS_VOID                           *pMsg
);

VOS_VOID TAF_MTA_RcvTiWaitPhyQryHandleDectExpired(
    VOS_VOID                           *pMsg
);

VOS_UINT32 TAF_MTA_CheckRatModeTypeValid(
    AT_MTA_CMD_RATMODE_ENUM_UINT8       enRatMode
);

VOS_VOID TAF_MTA_RcvAtSetDpdtTestFlagReq(
    VOS_VOID                           *pMsg
);

VOS_VOID TAF_MTA_RcvAtSetDpdtValueReq(
    VOS_VOID                           *pMsg
);

VOS_VOID TAF_MTA_RcvAtQryDpdtValueReq(
    VOS_VOID                           *pMsg
);

VOS_VOID TAF_MTA_RcvGuPhyQryDpdtValueCnf(
    VOS_VOID                           *pMsg
);

VOS_VOID TAF_MTA_RcvTiReqDpdtValueQryExpired(
    VOS_VOID                           *pMsg
);


#if(FEATURE_ON == FEATURE_LTE)
#if 0
VOS_VOID TAF_MTA_SndLphySetIsmCoexReqMsg(
    AT_MTA_LTE_WIFI_COEX_SET_REQ_STRU           *pstCoexPara
);
VOS_VOID TAF_MTA_RcvLphyIsmCoexSetCnf(
    VOS_VOID                           *pLphyCnfMsg
);
#endif
VOS_VOID TAF_MTA_RcvAtIsmCoexSetReq(
    VOS_VOID                           *pMsg
);
VOS_VOID TAF_MTA_RcvTiWaitSetIsmCoexList(
    VOS_VOID                           *pMsg
);
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_UINT32 TAF_MTA_SndCtasSetDpdtTestFlagNtfMsg(
    AT_MTA_SET_DPDTTEST_FLAG_REQ_STRU  *pstSetDpdtFlagReq
);

VOS_UINT32 TAF_MTA_SndCtasSetDpdtValueNtfMsg(
    AT_MTA_SET_DPDT_VALUE_REQ_STRU     *pstSetDpdtReq
);

VOS_UINT32 TAF_MTA_SndCtasQryDpdtValueReqMsg(
    AT_MTA_QRY_DPDT_VALUE_REQ_STRU     *pstQryDpdtReq
);

VOS_VOID TAF_MTA_RcvCtasQryDpdtValueCnf(
    VOS_VOID                           *pMsg
);
#endif

VOS_VOID TAF_MTA_RcvAtRficSsiRdQryReq(VOS_VOID *pMsg);
VOS_VOID TAF_MTA_RcvTlPhyRficSsiRdInd(VOS_VOID *pMsg);

VOS_VOID TAF_MTA_SndRcmAfcClkAndXoCoEfQryReq(
    VOS_VOID
);


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

#endif /* end of TafMtaSecure.h */


