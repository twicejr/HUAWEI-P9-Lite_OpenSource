/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafMtaMbms.h
  版 本 号   : 初稿
  作    者   : w00316404
  生成日期   : 2015年5月22日
  最近修改   :
  功能描述   : MTA模块处理MBMS特性功能
  函数列表   :
  修改历史   :
  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : eMBMS项目新增

******************************************************************************/

#ifndef __TAFMTAMBMS_H__
#define __TAFMTAMBMS_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"

#include "MtaRrcInterface.h"
#include "TafMtaPhy.h"



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

#if((FEATURE_ON == FEATURE_LTE) && (FEATURE_ON == FEATURE_LTE_MBMS))
VOS_VOID TAF_MTA_RcvAtMBMSServiceOptionSetReq(
    VOS_VOID                           *pMsg
);
VOS_VOID TAF_MTA_SndLrrcSetMBMSServiceOptionReqMsg(
    VOS_UINT8                           ucMBMSServiceOption
);
VOS_VOID TAF_MTA_RcvLrrcMBMSServiceOptionSetCnf(
    VOS_VOID                           *pLrrcCnfMsg
);
VOS_VOID TAF_MTA_RcvTiWaitLrrcSetMBMSServiceOption(
    VOS_VOID                           *pMsg
);
VOS_VOID TAF_MTA_SndLrrcSetMBMSPreferenceReqMsg(
    VOS_UINT8                           ucMBMSCastMode
);
VOS_VOID TAF_MTA_RcvAtMBMSPreferenceSetReq(
    VOS_VOID                           *pMsg
);
VOS_VOID TAF_MTA_RcvLrrcMBMSPreferenceSetCnf(
    VOS_VOID                           *pLrrcCnfMsg
);
VOS_VOID TAF_MTA_RcvTiWaitLrrcSetMBMSPreference(
    VOS_VOID                           *pMsg
);
VOS_VOID TAF_MTA_SndLrrcQrySIB16NetworkTimeReqMsg(VOS_VOID);
VOS_VOID TAF_MTA_RcvAtSIB16NetworkTimeQryReq(
    VOS_VOID                           *pMsg
);
VOS_VOID TAF_MTA_RcvLrrcMBMSSIB16NetworkTimeQryCnf(
    VOS_VOID                           *pLrrcCnfMsg
);
VOS_VOID TAF_MTA_RcvTiWaitLrrcQrySIB16NetworkTime(
    VOS_VOID                           *pMsg
);
VOS_VOID TAF_MTA_SndLrrcQryBSSISignalLevelReqMsg(VOS_VOID);
VOS_VOID TAF_MTA_RcvAtBSSISignalLevelQryReq(
    VOS_VOID                           *pMsg
);
VOS_VOID TAF_MTA_RcvLrrcMBMSBSSISignalLevelQryCnf(
    VOS_VOID                           *pLrrcCnfMsg
);
VOS_VOID TAF_MTA_RcvTiWaitLrrcQryBSSISignalLevel(
    VOS_VOID                           *pMsg
);
VOS_VOID TAF_MTA_SndLrrcQryNetworkInfoReqMsg(VOS_VOID);
VOS_VOID TAF_MTA_RcvAtNetworkInfoQryReq(
    VOS_VOID                           *pMsg
);
VOS_VOID TAF_MTA_RcvLrrcMBMSNetworkInfoQryCnf(
    VOS_VOID                           *pLrrcCnfMsg
);
VOS_VOID TAF_MTA_RcvTiWaitLrrcQryNetworkInfo(
    VOS_VOID                           *pMsg
);
VOS_VOID TAF_MTA_SndLrrcQryEMBMSStatusReqMsg(VOS_VOID);
VOS_VOID TAF_MTA_RcvAtEMBMSStatusQryReq(
    VOS_VOID                           *pMsg
);
VOS_VOID TAF_MTA_RcvLrrcEMBMSStatusQryCnf(
    VOS_VOID                           *pLrrcCnfMsg
);
VOS_VOID TAF_MTA_RcvTiWaitLrrcQryEMBMSStatus(
    VOS_VOID                           *pMsg
);
VOS_VOID TAF_MTA_SndLrrcSetMBMSUnsolicitedCfgReqMsg(
    VOS_UINT8                           ucMBMSUnsolicitedCfg
);
VOS_VOID TAF_MTA_RcvAtMBMSUnsolicitedCfgSetReq(
    VOS_VOID                           *pMsg
);
VOS_VOID TAF_MTA_RcvLrrcMBMSUnsolicitedCfgSetCnf(
    VOS_VOID                           *pLrrcCnfMsg
);
VOS_VOID TAF_MTA_RcvTiWaitLrrcSetMBMSUnsolicitedCfg(
    VOS_VOID                           *pMsg
);
VOS_VOID TAF_MTA_RcvLrrcMBMSServiceEventInd(
    VOS_VOID                           *pMsg
);
VOS_VOID TAF_MTA_SndLrrcSetInterestListReqMsg(
    AT_MTA_MBMS_INTERESTLIST_SET_REQ_STRU           *pstMBMSInterestList
);
VOS_VOID TAF_MTA_RcvAtMBMSInterestListSetReq(
    VOS_VOID                           *pMsg
);
VOS_VOID TAF_MTA_RcvLrrcInterestListSetCnf(
    VOS_VOID                           *pLrrcCnfMsg
);
VOS_VOID TAF_MTA_RcvTiWaitLrrcSetInterestList(
    VOS_VOID                           *pMsg
);
VOS_VOID TAF_MTA_SndLrrcSetMBMSServiceStateReqMsg(
    AT_MTA_MBMS_SERVICE_STATE_SET_REQ_STRU      *pstMBMSServiceState
);
VOS_VOID TAF_MTA_RcvAtMBMSServiceStateSetReq(
    VOS_VOID                           *pMsg
);
VOS_VOID TAF_MTA_RcvLrrcMBMSServiceStateSetCnf(
    VOS_VOID                           *pLrrcCnfMsg
);
VOS_VOID TAF_MTA_RcvTiWaitLrrcSetMBMSServiceState(
    VOS_VOID                           *pMsg
);
VOS_VOID TAF_MTA_SndLrrcQryAvlServiceListReqMsg(VOS_VOID);
VOS_VOID TAF_MTA_RcvAtMBMSAvlServiceListQryReq(
    VOS_VOID                           *pMsg
);
VOS_VOID TAF_MTA_RcvLrrcMBMSAvlServiceListQryCnf(
    VOS_VOID                           *pLrrcCnfMsg
);
VOS_VOID TAF_MTA_RcvTiWaitLrrcQryAvlServiceList(
    VOS_VOID                           *pMsg
);
#endif



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


