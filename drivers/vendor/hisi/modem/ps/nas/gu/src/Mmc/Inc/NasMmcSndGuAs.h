/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcSndGuAs.h
  版 本 号   : 初稿
  作    者   : w00176964
  生成日期   : 2011年5月9日
  最近修改   :
  功能描述   : 定义MMC发送给GU模的消息处理头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年5月9日
    作    者   : w00176964
    修改内容   : 创建文件

******************************************************************************/
#ifndef _NAS_MMC_SND_GUAS_H_
#define _NAS_MMC_SND_GUAS_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "Nasrrcinterface.h"
#include  "NasMmcCtx.h"
/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
#include "MsccMmcInterface.h"
/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

#include "PsRrmInterface.h"

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
 结构名    : NAS_MMC_AVAIL_PLMN_STRU
 结构说明  : 通知给接入层可用的PLMN信息
  1.日    期   : 2011年7月25日
    作    者   : zhuojun \40661
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                  ulAvailPlmnNum;
    RRC_PLMN_ID_STRU            astAvailPlmnIdList[NAS_RRC_MAX_AVAILPLMN_NUM];       /* PlMN标识 */
}NAS_MMC_AVAIL_PLMN_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
VOS_VOID NAS_MMC_SndAsStartReq(VOS_UINT32 ulReceiverPid);

VOS_VOID NAS_MMC_SndAsPowerOffReq(
    VOS_UINT32                          ulReceiverPid
);

VOS_VOID NAS_MMC_SndAsPlmnAnyCellSrchReq(VOS_UINT32 ulPid);

VOS_VOID NAS_MMC_SndAsSuspendReq(VOS_UINT32 ulPid);

VOS_VOID NAS_MMC_SndAsPlmnSrchStopReq(VOS_UINT32 ulPid);

VOS_VOID NAS_MMC_SndAsPlmnSrchReq(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstPlmnInfo
);

VOS_VOID NAS_MMC_SndGuAsEquPlmnReq(
    NAS_MML_EQUPLMN_INFO_STRU          *pstEplmnInfo,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType
);


VOS_VOID NAS_MMC_SndAsSuspendRelReq(
    VOS_UINT32                          ulReceiverPid
);

/* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
VOS_VOID  NAS_MMC_SndAsSyscfgReq(
    MSCC_MMC_SYS_CFG_SET_REQ_STRU      *pstSysCfgMsg,
    VOS_UINT32                          ulReceiverPid
);
/* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */


VOS_VOID  NAS_MMC_SndAsSuspendRsp(
    RRC_NAS_SUSPEND_RESULT_ENUM_UINT8   enSuspendRslt,
    VOS_UINT32                          ulReceiverPid
);

VOS_VOID NAS_MMC_SndAsResumeRsp(
    VOS_UINT32                          ulReceiverPid
);

VOS_VOID NAS_MMC_SndWasInfoReportReq(VOS_VOID);

VOS_VOID NAS_MMC_SndGasInfoReportReq(VOS_VOID);




VOS_VOID NAS_MMC_BuildForbLaInAsSpecPlmnSearchReqMsg(
    VOS_UINT32                                             *pulForbidLaNum,
    RRC_FORB_LA_STRU                                        aForbLaList[],
    NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU               *pstForbRoamLaInfo
);

VOS_VOID NAS_MMC_BuildAsSpecPlmnSearchReqMsg(
    RRMM_PLMN_SEARCH_REQ_STRU                              *pstMsg,
    NAS_MML_PLMN_LIST_WITH_RAT_STRU                        *pstDestPlmnList,
    NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU               *pstForbRoamLaInfo
);

#if (FEATURE_ON == FEATURE_CSG)
VOS_VOID NAS_MMC_SndAsCsgListSearchReq(
    VOS_UINT32                          ulReceiverPid
);
#endif

VOS_VOID NAS_MMC_SndAsHistoryPlmnSearchReq(
    NAS_MML_PLMN_LIST_WITH_RAT_STRU                        *pstDestPlmnList,
    NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU               *pstForbRoamLaInfo
);

VOS_VOID NAS_MMC_BuildAsHistoryPlmnSearchReqMsg(
    RRMM_PLMN_SEARCH_REQ_STRU                              *pstMsg,
    NAS_MML_PLMN_LIST_WITH_RAT_STRU                        *pstDestPlmnList,
    NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU               *pstForbRoamLaInfo
);


VOS_VOID NAS_MMC_SndAsSpecPlmnSearchReq(
    NAS_MML_PLMN_LIST_WITH_RAT_STRU                        *pstDestPlmnList,
    NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU               *pstForbRoamLaInfo
);

VOS_VOID NAS_MMC_SndAsSpecPlmnSearchReq_PlmnSelection(
    NAS_MML_PLMN_LIST_WITH_RAT_STRU                        *pstDestPlmnList,
    NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU               *pstForbRoamLaInfo
);




VOS_VOID NAS_MMC_BuildAsPrefBandPlmnSearchReqMsg(
    RRMM_PLMN_SEARCH_REQ_STRU                              *pstMsg,
    NAS_MML_PLMN_LIST_WITH_RAT_STRU                        *pstDestPlmnList,
    NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU               *pstForbRoamLaInfo
);
VOS_VOID NAS_MMC_SndAsPrefBandPlmnSearchReq(
    NAS_MML_PLMN_LIST_WITH_RAT_STRU                        *pstDestPlmnList,
    NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU               *pstForbRoamLaInfo
);

VOS_VOID NAS_MMC_SndAsNcellSpecPlmnSearchReq(
    NAS_MMC_TDS_NCELL_INFO_STRU        *pstTdsNcellInfo,
    NAS_MML_EQUPLMN_INFO_STRU          *pstOtherModemEplmnInfo
);

VOS_VOID NAS_MMC_SndAsPlmnListReq(
    VOS_UINT32                          ulReceiverPid
);


VOS_VOID NAS_MMC_SndRrMmRelReq(
    RRC_NAS_CN_DOMAIN_TYPE_ENUM_UINT32  ulCnDomain
);

VOS_VOID NAS_MMC_SndAsFastPlmnSearchReq(
    VOS_UINT32                          ulReceiverPid,
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
);

VOS_VOID NAS_MMC_SndAsBgPlmnSearchReq(
    VOS_UINT32                          ulReceiverPid,
    NAS_MML_PLMN_WITH_RAT_STRU         *pstPlmnId
);

VOS_VOID NAS_MMC_SndAsBgStopPlmnSearchReq(
    VOS_UINT32                          ulReceiverPid
);
VOS_VOID NAS_MMC_SndAsGetGeoPlmnSearchReq(
    VOS_UINT32                          ulReceiverPid
);
VOS_VOID NAS_MMC_SndAsStopGetGeoPlmnSearchReq(
    VOS_UINT32                          ulReceiverPid
);

VOS_VOID NAS_MMC_SndAsNasCommInfoChangeReq(
    VOS_UINT32                          ulReceiverPid,
    NAS_COMM_INFO_STRU                 *pstNasComInfo
);

VOS_VOID NAS_MMC_SndAsNasUsimStatus(
    RRC_NAS_USIM_STATUS_ENUM_UINT32     enUsimStatus
);


VOS_VOID NAS_MMC_SndAsLteCapabilityStatus(
    VOS_UINT32                                              ulReceiverPid,
    RRC_NAS_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus
);

VOS_VOID NAS_MMC_SndAsRatCapabilityStatusChangeInfo(VOS_VOID);


VOS_VOID   NAS_MMC_SndRrMmCellSelReq(
    VOS_UINT8                           ucSrhType
);



VOS_VOID  NAS_MMC_SndGuAsUeOocStatus(
    VOS_UINT32                          ulReceiverPid
);



/* NAS_MMC_RcvRrMmGetTransactionReq_PreProc移到MM处理 */


VOS_VOID NAS_MMC_SndAsHplmnReq(
    VOS_UINT32                          ulReceiverPid
);

VOS_VOID NAS_MMC_SndAsNetScanReq(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    MSCC_MMC_NET_SCAN_REQ_STRU         *pstNetScanReq
);

VOS_VOID NAS_MMC_SndAsNetScanStopReq(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
);



#if (FEATURE_ON == FEATURE_DSDS)
VOS_VOID NAS_MMC_SndRrmRegisterInd(
    MODEM_ID_ENUM_UINT16               enModemId,
    RRM_PS_TASK_TYPE_ENUM_UINT16       enTaskType,
    VOS_RATMODE_ENUM_UINT32            enRatType
);

VOS_VOID NAS_MMC_SndRrmDeRegisterInd(
    MODEM_ID_ENUM_UINT16               enModemId,
    RRM_PS_TASK_TYPE_ENUM_UINT16       enTaskType,
    VOS_RATMODE_ENUM_UINT32            enRatType
);
VOS_VOID NAS_MMC_SndAsEndSessionNotify(
    VOS_UINT32                          ulReceiverPid,
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enSessionType,
    VOS_UINT32                          ulDelayTime
);
VOS_VOID NAS_MMC_SndAsBeginSessionNotify(
    VOS_UINT32                          ulReceiverPid,
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enSessionType
)
;


#endif


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

#endif

