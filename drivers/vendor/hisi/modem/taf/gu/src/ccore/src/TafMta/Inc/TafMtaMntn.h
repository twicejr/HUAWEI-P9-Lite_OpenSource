/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafMtaMntn.h
  版 本 号   : 初稿
  作    者   : m00217266
  生成日期   : 2013年1月10日
  最近修改   :
  功能描述   : MTA模块处理可维可测功能
  函数列表   :
  修改历史   :
  1.日    期   : 2013年1月10日
    作    者   : m00217266
    修改内容   : DSDA C核项目新增

******************************************************************************/

#ifndef __TAFMTAMMNTN_H__
#define __TAFMTAMMNTN_H__

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
 枚举名    : TAF_MTA_INFO_CLT_RESULT_ENUM
 枚举说明  : 获取信息的结果类型
 1.日    期   : 2015年07月23日
   作    者   : f00179208
   修改内容   : 新建
*****************************************************************************/
enum TAF_MTA_INFO_CLT_RESULT_ENUM
{
    TAF_MTA_INFO_CLT_RESULT_SUCC        = 0x00,      /* 信息收集成功 */
    TAF_MTA_INFO_CLT_RESULT_FAIL        = 0x01,      /* 信息收集失败 */

    TAF_MTA_INFO_CLT_RESULT_BUTT
};
typedef VOS_UINT32  TAF_MTA_INFO_CLT_RESULT_ENUM_U32;


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
typedef struct
{
    VOS_UINT8                           ucPlmnNum;                              /* 频点数目 */
    VOS_UINT8                           aucRsv[3];                              /* 保留位 */
    MNTN_PLMN_ID_STRU                   astPlmnInfo[MTA_RRC_MAX_PLMN_NUM];  /* 频点信息列表 */
}TAF_MTA_INFO_CLT_PLMN_LIST_STRU;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/
/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  10 函数声明
*****************************************************************************/

VOS_VOID TAF_MTA_RcvSetWrrFreqlockReq( VOS_VOID *pMsg );
VOS_VOID TAF_MTA_RcvSetWrrRrcVersionReq( VOS_VOID *pMsg );
VOS_VOID TAF_MTA_RcvSetWrrCellsrhReq( VOS_VOID *pMsg );
VOS_VOID TAF_MTA_RcvQryWrrFreqlockReq( VOS_VOID *pMsg );
VOS_VOID TAF_MTA_RcvQryWrrRrcVersionReq( VOS_VOID *pMsg );
VOS_VOID TAF_MTA_RcvQryWrrCellsrhReq( VOS_VOID *pMsg );
VOS_VOID TAF_MTA_RcvWrrFreqlockSetCnf( VOS_VOID *pWrrCnfMsg );
VOS_VOID TAF_MTA_RcvWrrVersionSetCnf( VOS_VOID *pWrrCnfMsg );
VOS_VOID TAF_MTA_RcvWrrCellsrhSetCnf( VOS_VOID *pWrrCnfMsg );
VOS_VOID TAF_MTA_RcvWrrFreqlockQryCnf( VOS_VOID *pWrrCnfMsg );
VOS_VOID TAF_MTA_RcvWrrVersionQryCnf( VOS_VOID *pWrrCnfMsg );
VOS_VOID TAF_MTA_RcvWrrCellsrhQryCnf( VOS_VOID *pWrrCnfMsg );
VOS_VOID TAF_MTA_RcvTiReqFreqlockSetExpired( VOS_VOID *pMsg );
VOS_VOID TAF_MTA_RcvTiReqRrcVersionSetExpired( VOS_VOID *pMsg );
VOS_VOID TAF_MTA_RcvTiReqCellsrhSetExpired( VOS_VOID * pMsg );
VOS_VOID TAF_MTA_RcvTiReqFreqlockQryExpired( VOS_VOID *pMsg );
VOS_VOID TAF_MTA_RcvTiReqRrcVersionQryExpired( VOS_VOID *pMsg );
VOS_VOID TAF_MTA_RcvTiReqCellsrhQryExpired( VOS_VOID *pMsg );
VOS_UINT32 TAF_MTA_SndWrrSetFreqlockReqMsg( MTA_WRR_FREQLOCK_CTRL_STRU *pFreqlockCtrlPara );
VOS_UINT32 TAF_MTA_SndWrrSetVersionReqMsg(
    VOS_UINT8                           ucRrcVersion
);
VOS_UINT32 TAF_MTA_SndWrrSetCellsrhReqMsg(
    VOS_UINT8                           ucCellSrh
);
VOS_UINT32 TAF_MTA_SndWrrQryFreqlockReqMsg(VOS_VOID);
VOS_UINT32 TAF_MTA_SndWrrQryRrcVersionReqMsg( VOS_VOID );
VOS_UINT32 TAF_MTA_SndWrrQryCellsrhReqMsg( VOS_VOID );

VOS_VOID TAF_MTA_RcvAtSetNCellMonitorReq(
    VOS_VOID                           *pMsg
);
VOS_VOID TAF_MTA_RcvAtQryNCellMonitorReq(
    VOS_VOID                           *pMsg
);
VOS_VOID TAF_MTA_RcvRrcSetNCellMonitorCnf(
    VOS_VOID                           *pMsg
);
VOS_VOID TAF_MTA_RcvRrcQryNCellMonitorCnf(
    VOS_VOID                           *pMsg
);
VOS_VOID TAF_MTA_RcvRrcNCellMonitorInd(
    VOS_VOID                           *pMsg
);
VOS_UINT32 TAF_MTA_SndGrrNCellMonitorSetReq(
    VOS_UINT8                         ucRptCmdStatus
);
VOS_UINT32 TAF_MTA_SndGrrNCellMonitorQryReq(VOS_VOID);

VOS_VOID TAF_MTA_RcvNasAreaLostInd(
    VOS_VOID                           *pMsg
);

VOS_VOID TAF_MTA_RcvTafAgentGetAntStateReq(
    VOS_VOID                           *pMsg
);

#if (FEATURE_ON == FEATURE_PTM)
VOS_VOID TAF_MTA_SndAcpuOmErrLogRptCnf(
    VOS_CHAR                           *pbuffer,
    VOS_UINT32                          ulBufUseLen
);
VOS_VOID TAF_MTA_RcvAcpuOmErrLogRptReq(
    VOS_VOID                           *pMsg
);
VOS_VOID TAF_MTA_RcvAcpuOmErrLogCtrlInd(
    VOS_VOID                           *pMsg
);
VOS_VOID TAF_MTA_SndAcpuOmInfoCltRptCnf(
    VOS_VOID                           *pMsg,
    VOS_UINT32                          ulLenth
);
VOS_VOID TAF_MTA_SndAcpuOmFreqBandQryCnf(
    TAF_MTA_INFO_CLT_RESULT_ENUM_U32    enCltResult
);
VOS_VOID TAF_MTA_RcvAcpuOmFreqBandQryReq(
    VOS_VOID                           *pMsg
);
VOS_VOID TAF_MTA_RcvAcpuOmInfoCltRptReq(
    VOS_VOID                           *pMsg
);
VOS_VOID TAF_MTA_SndRrcPlmnFreqQryReq(
    VOS_VOID                           *pData,
    VOS_UINT32                          ulReceiverPid
);
VOS_VOID TAF_MTA_RcvGasPlmnFreqQryCnf(
    VOS_VOID                           *pMsg
);
VOS_VOID TAF_MTA_RcvWrrPlmnFreqQryCnf(
    VOS_VOID                           *pMsg
);
#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID TAF_MTA_RcvLrrcPlmnFreqQryCnf(
    VOS_VOID                           *pMsg
);
#endif
VOS_VOID TAF_MTA_SndAcpuOmNetworkInfoQryCnf(
    TAF_MTA_INFO_CLT_RESULT_ENUM_U32    enCltResult
);
VOS_VOID TAF_MTA_RcvAcpuOmNetworkInfoQryReq(
    VOS_VOID                           *pMsg
);
VOS_VOID TAF_MTA_SndPhyChrInfoQryReq(
    VOS_UINT32                          ulReceiverPid
);
VOS_VOID TAF_MTA_RcvPhyChrInfoQryCnf(
    VOS_VOID                           *pMsg
);
VOS_VOID TAF_MTA_RcvTiWaitNetworkInfoQryCnfExpired(
    VOS_VOID                           *pstMsg
);

VOS_VOID TAF_MTA_SndNasChrInfoQryReq(
    VOS_UINT32                          ulReceiverPid
);
VOS_VOID TAF_MTA_RcvNasGetNasChrInfoCnf(
    VOS_VOID                           *pMsg
);

VOS_VOID TAF_MTA_RcvTiWaitFreqCltQryCnfExpired(
    VOS_VOID                           *pstMsg
);

#endif


#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32 TAF_MTA_SndTLrrcSetDpdtTestFlagNtfMsg(
    AT_MTA_SET_DPDTTEST_FLAG_REQ_STRU  *pstSetDpdtFlagReq
);

VOS_UINT32 TAF_MTA_SndTLrrcSetDpdtValueNtfMsg(
    AT_MTA_SET_DPDT_VALUE_REQ_STRU     *pstSetDpdtReq
);

VOS_UINT32 TAF_MTA_SndTLrrcQryDpdtValueReqMsg(
    AT_MTA_QRY_DPDT_VALUE_REQ_STRU     *pstSetDpdtReq
);

VOS_VOID TAF_MTA_RcvTLrrcDpdtValueQryCnf(VOS_VOID *pMsg);

VOS_UINT32 TAF_MTA_SndLrrcSetFrReqMsg(
    struct MsgCB                       *pstMsg
);
VOS_VOID TAF_MTA_RcvAtSetFrReq(
    VOS_VOID                           *pstMsg
);
VOS_VOID TAF_MTA_RcvLrrcSetFrCnf(
    VOS_VOID                           *pstMsg
);
VOS_VOID TAF_MTA_RcvTiWaitLrrcSetFrCnfExpired(
    VOS_VOID                           *pstMsg
);
#endif

VOS_VOID TAF_MTA_RcvAtPhyInitReq(VOS_VOID * pMsg);
VOS_VOID TAF_MTA_RcvPhyInitCnf(VOS_VOID * pMsg);
VOS_VOID TAF_MTA_RcvTiPhyInitExpired(VOS_VOID *pMsg);

VOS_VOID TAF_MTA_RcvAtSetJamDetectReq(
    VOS_VOID                           *pMsg
);

VOS_UINT32 TAF_MTA_SndGrrSetJamDetectReq(
    AT_MTA_SET_JAM_DETECT_REQ_STRU     *pstSetJdrReq
);

VOS_VOID TAF_MTA_RcvRrcJamDetectCnf(
    VOS_VOID                           *pMsg
);

VOS_VOID TAF_MTA_RcvRrcJamDetectInd(
    VOS_VOID                           *pMsg
);

VOS_VOID TAF_MTA_RcvTiWaitGrrSetJamDetectExpired(VOS_VOID *pMsg);

VOS_VOID TAF_MTA_RcvAtSetFreqLockReq(
    VOS_VOID                           *pMsg
);

VOS_UINT32 TAF_MTA_SndRrcSetFreqLockReq(
    AT_MTA_SET_FREQ_LOCK_REQ_STRU      *pstSetFreqLockReq
);

VOS_VOID TAF_MTA_RcvRrcCheckFreqValidityCnf(
    VOS_VOID                           *pMsg
);

VOS_VOID TAF_MTA_RcvTiWaitRrcCheckFreqValidityExpired(VOS_VOID *pMsg);

VOS_VOID TAF_MTA_RcvAtSetGFreqLockReq(
    VOS_VOID                           *pMsg
);

VOS_VOID TAF_MTA_RcvGasSetFreqLockCnf(
    VOS_VOID                           *pMsg
);

VOS_UINT32 TAF_MTA_SndGasSetFreqLockReq(
    AT_MTA_SET_GSM_FREQLOCK_REQ_STRU   *pstSetGFreqLockReq
);

VOS_VOID TAF_MTA_RcvTiWaitGasSetGFreqLockExpired(
    VOS_VOID                           *pMsg
);

VOS_VOID TAF_MTA_RcvGphyXpassInfoInd(
    VOS_VOID                            *pMsg
);

VOS_VOID TAF_MTA_RcvWphyXpassInfoInd(
    VOS_VOID                            *pMsg
);

VOS_UINT32 TAF_MTA_GetXpassInfoRptCtl(VOS_VOID);

VOS_VOID TAF_MTA_RcvAtSetFemctrlReq(
    VOS_VOID                           *pMsg
);

#if(FEATURE_ON == FEATURE_LTE)
VOS_VOID TAF_MTA_SndLrrcSetLowPowerConsumptionReqMsg(
    VOS_UINT8                           ucLowPowerConsumption
);
VOS_VOID TAF_MTA_RcvAtLteLowPowerConsumptionSetReq(
    VOS_VOID                           *pMsg
);
VOS_VOID TAF_MTA_RcvLrrcLowPowerConsumptionSetCnf(
    VOS_VOID                           *pLrrcCnfMsg
);
VOS_VOID TAF_MTA_RcvTiWaitLrrcSetLowPowerConsumption(
    VOS_VOID                           *pMsg
);
VOS_VOID TAF_MTA_SndLrrcSetIsmCoexReqMsg(
    AT_MTA_LTE_WIFI_COEX_SET_REQ_STRU           *pstCoexPara
);
VOS_VOID TAF_MTA_RcvLrrcIsmCoexSetCnf(
    VOS_VOID                           *pLrrcCnfMsg
);
VOS_VOID TAF_MTA_RcvAtIsmCoexQryReq(
    VOS_VOID                           *pMsg
);
#endif

VOS_VOID TAF_MTA_RcvAtUECenterSetReq(VOS_VOID *pMsg);
VOS_VOID TAF_MTA_SndLnasUECenterSetReq(
    AT_MTA_SET_UE_CENTER_REQ_STRU *pstAtMtaUECenterSetReq
);
VOS_VOID TAF_MTA_RcvLnasUECenterSetCnf(VOS_VOID *pMsg);
VOS_VOID TAF_MTA_RcvTiWaitLnasUECenterSetExpired(
    VOS_VOID                           *pMsg
);
VOS_VOID TAF_MTA_RcvAtUECenterQryReq(VOS_VOID *pMsg);
VOS_VOID TAF_MTA_SndLnasUECenterQryReq(VOS_VOID);
VOS_VOID TAF_MTA_RcvLnasUECenterQryCnf(VOS_VOID *pMsg);
VOS_VOID TAF_MTA_RcvTiWaitLnasUECenterQryExpired(
    VOS_VOID                           *pMsg
);

#if (FEATURE_ON == FEATURE_TDS_WCDMA_DYNAMIC_LOAD)
VOS_VOID TAF_MTA_RcvCcbtLoadPsRrcReq(
    VOS_VOID                           *pstMsg
);

VOS_VOID TAF_MTA_RcvCcbtQryPsRrcLoadStatusReq(
    VOS_VOID                           *pstMsg
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


