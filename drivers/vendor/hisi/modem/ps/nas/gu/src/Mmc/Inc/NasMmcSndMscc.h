/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcSndMscc.h
  版 本 号   : 初稿
  作    者   : L00171473
  生成日期   : 2011年7月13日
  最近修改   :
  功能描述   : NasMmcSndMscc.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年7月13日
    作    者   : L00171473
    修改内容   : 创建文件

******************************************************************************/

#ifndef __NASMMCSNDMSCC_H__
#define __NASMMCSNDMSCC_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "Nasrrcinterface.h"
#include  "MmcGmmInterface.h"
#include  "MmcMmInterface.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif
#include  "NasCommDef.h"
/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
#include "MsccMmcInterface.h"
/* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */



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
#if (FEATURE_ON == FEATURE_CSG)
VOS_VOID NAS_MMC_SndMsccUserCsgListAbortCnf(
    MMC_MSCC_CSG_LIST_ABORT_CNF_STRU   *pstCsgListAbortCnf
);
VOS_VOID NAS_MMC_SndMsccUserCsgListSearchCnf(
    MMC_MSCC_CSG_LIST_SEARCH_CNF_STRU  *pstCsgListSearchCnf
);
VOS_VOID NAS_MMC_SndMsccCsgListSearchRej(VOS_VOID);
#endif

/* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
VOS_VOID NAS_MMC_SndMsccUserSpecPlmnSearchCnf(
    NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_ENUM_UINT8         enResult
)
;

VOS_VOID NAS_MMC_SndMsccPlmnSelectionRsltInd(
    NAS_MSCC_PIF_PLMN_SELECTION_RESULT_ENUM_UINT32          enResult,
    VOS_UINT8                                               ucLteCoverFlg
);


/* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

VOS_VOID NAS_MMC_SndMsccPlmnSelectStartInd(VOS_VOID);

VOS_VOID NAS_MMC_SndMsccDetachInd(
    VOS_UINT32                          ulCnDomainId,
    VOS_UINT32                          ulDetachType,
    VOS_UINT32                          ulCause
);




VOS_VOID NAS_MMC_SndMsccAttachCnf(
     VOS_UINT32                           ulCnDomainId,
     NAS_MM_COM_SERVICE_STATUS_ENUM_UINT8 enMsccServiceStatus,
     VOS_UINT32                           ulOpid
);

VOS_VOID NAS_MMC_SndMsccDetachCnf(
    VOS_UINT32                                              ulCnDomainId,
    NAS_MM_COM_SERVICE_STATUS_ENUM_UINT8                    enMsccServiceStatus,
    VOS_UINT32                                              ulOpid,
    NAS_MSCC_PIF_OPER_RESULT_ENUM_UINT32                    enOperRslt
);



VOS_VOID NAS_MMC_SndMsccServiceStatusInd(
    VOS_UINT32                          ulCnDomainId,
    VOS_UINT32                          ulServiceStatus
);

/* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, begin */
VOS_VOID NAS_MMC_SndMsccRegStatusInd(
    VOS_UINT32                          ulCnDomainId,
    NAS_MSCC_PIF_REG_STATE_ENUM_UINT8        enRegStatus
);
VOS_VOID NAS_MMC_SndMsccPlmnReselCnf(
    NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_ENUM_UINT8        enPlmnReselRslt
);

/* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-7, end */
VOS_VOID NAS_Mmc_SndMsccPowerOffCnf(VOS_VOID);

VOS_VOID NAS_Mmc_SndMsccStartCnf(
    VOS_UINT32                          ulResult
);

 /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
VOS_VOID NAS_MMC_SndMsccPlmnListAbortCnf(
    MMC_MSCC_PLMN_LIST_ABORT_CNF_STRU    *pstSndMsccMsg
);


VOS_VOID NAS_MMC_SndMsccPlmnListInd(
    MMC_MSCC_PLMN_LIST_CNF_STRU          *pstSndMsccMsg
);
 /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

VOS_VOID NAS_Mmc_SndMsccPlmnListRej(VOS_VOID);

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))
/* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-16, begin */
VOS_VOID NAS_MMC_SndCbaMsgNetModInd(
    VOS_UINT8                           ucNetWorkMode
);
/* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-16, end */


VOS_VOID  NAS_MMC_SndMsccMsgNoNetWorkInd( VOS_VOID );


#endif



VOS_VOID NAS_MMC_SndMsccMmInfo(
    NAS_MM_INFO_IND_STRU                *pstMmInfo
);

VOS_VOID NAS_MMC_SndMsccCoverageInd(
    VOS_UINT8                               ucType
);

VOS_VOID NAS_MMC_SndMsccDataTranAttri(
    NAS_MSCC_PIF_DATATRAN_ATTRI_ENUM_UINT8                  ucDataTranAttri
);

 /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
VOS_VOID NAS_MMC_SndMsccSysInfo( VOS_VOID );
 /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

/* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, begin */
VOS_VOID NAS_MMC_SndMsccRegResultInd(
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32            enSrvDomain,
    VOS_UINT8                           ucResult,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enRejCause
);

VOS_VOID NAS_MMC_SndMsccServRejRsltInd(
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32            enCnDomainId,
    VOS_UINT16                          usRejCause
);


/* Modified by w00176964 for VoLTE_PhaseIII 项目, 2013-12-13, end */

VOS_VOID NAS_MMC_SndMsccRssiInd(
    MSCC_MMC_SCELL_MEAS_REPORT_TYPE_UN  *punMeasReportType
);


VOS_VOID NAS_MMC_SndAsEquPlmnQueryCnf(
    EQUIVALENT_PLMN_STRU               *pstEquPlmnList,
    VOS_UINT32                          ulOpCurPlmnId,
    NAS_MML_PLMN_ID_STRU               *pstCurPlmnId,
    VOS_UINT32                          ulPid
);

VOS_VOID NAS_MMC_SndRrcPlmnQueryCnf(
    PS_BOOL_ENUM_UINT8                  enQueryWPlmn
);

 /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
VOS_VOID NAS_MMC_SndMsccSysCfgCnf(NAS_MSCC_PIF_SYS_CFG_SET_RESULT_ENUM_UINT32 ulRst);
 /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

VOS_VOID NAS_MMC_SndMsccNetScanCnf(
    MMC_MSCC_NET_SCAN_CNF_STRU             *pstRcvRrmmMsg
);

VOS_VOID NAS_MMC_SndMsccAbortNetScanCnf(
    MMC_MSCC_ABORT_NET_SCAN_CNF_STRU    *pstSndMsccAbortNetScanCnfMsg
);



 /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
VOS_VOID  NAS_MMC_GetCellInfoForMscc(
    NAS_MSCC_PIF_CAMP_CELL_INFO_STRU                    *pstCellInfo
);
 /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

VOS_VOID  NAS_MMC_GetOperPlmnInfoForMscc(
    MMC_TAF_PLMN_LIST_INFO_ST           *pstRptMsccOperList
);

VOS_VOID  NAS_MMC_GetUserPlmnInfoForMscc(
    MMC_TAF_PLMN_LIST_INFO_ST           *pstRptMsccUserList
);

VOS_VOID  NAS_MMC_GetHPlmnInfoForMscc(
    MMC_TAF_PLMN_LIST_INFO_ST           *pstRptMsccHplmnList
);

VOS_VOID  NAS_MMC_GetSelPlmnInfoForMscc(
    MMC_TAF_PLMN_LIST_INFO_ST           *pstRptMsccSelPlmnList
);

/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-16, begin */
/* Deleted by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-16, end */


NAS_MM_COM_SERVICE_STATUS_ENUM_UINT8  NAS_MMC_GetServiceStatusForMscc(
    NAS_MM_COM_SERVICE_DOMAIN_ENUM_UINT8 enSrvDomain
);




VOS_VOID NAS_MMC_SndMsccSpecPlmnSearchAbortCnf(VOS_VOID);


VOS_VOID NAS_MMC_SndMsccWCipherInfoInd(
    RRMM_CIPHER_INFO_IND_STRU          *pstCipherInfoInd
);

VOS_VOID NAS_MMC_SndMsccGCipherInfoInd(
    MMC_GMM_CIPHER_INFO_IND_STRU       *pstCipherInfoInd
);


VOS_VOID NAS_MMC_SndMsccUserSpecPlmnSearchRej( VOS_VOID );


/* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
VOS_VOID NAS_MMC_SndMsccAcInfoChangeInd(
    VOS_UINT32                          ulCnDomainId,
    NAS_MML_ACCESS_RESTRICTION_STRU    *pstAcInfo
);
/* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */

VOS_VOID NAS_MMC_SndMsccEOPlmnSetCnf(
    VOS_UINT32                          ulRst
);



VOS_VOID NAS_MMC_SndMsccEplmnInfoInd(
    NAS_MML_EQUPLMN_INFO_STRU          *pstEplmnInfo
);



VOS_VOID NAS_MMC_SndMsccUsimAuthFailInd(
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32            enSrvDomain,
    NAS_MML_SIM_AUTH_FAIL_ENUM_UINT16   enRejCause
);

VOS_VOID NAS_MMC_SndMsccCsServiceConnStatusInd(
    VOS_UINT8                           ucCsServiceConnStatusFlag
);

/* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-13, begin */
/*****************************************************************************
 函 数 名  : NAS_MMC_SndMsccNetworkCapabilityInfoInd
 功能描述  : 上报LTE 网络能力参数给MSCC module
 输入参数  : pstRcvMsg -- 消息地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年7月14日
   作    者   : y00245242
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_MMC_SndMsccNetworkCapabilityInfoInd(
    NAS_MSCC_PIF_NW_IMS_VOICE_CAP_ENUM_UINT8                     enNwImsVoCap,
    NAS_MSCC_PIF_NW_EMC_BS_CAP_ENUM_UINT8                        enNwEmcBsCap,
    NAS_MSCC_PIF_LTE_CS_CAPBILITY_ENUM_UINT8                     enLteCsCap
);
/* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-13, end */

/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
VOS_VOID NAS_MMC_SndMsccCampOnInd(
    VOS_UINT8                           ucCampOnFlg
);
/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */

/* Added by s00246516 for L-C互操作项目, 2014-02-12, Begin */
VOS_VOID NAS_MMC_SndMsccAcqCnf(
    NAS_MSCC_PIF_ACQ_RESULT_ENUM_UINT32      enAcqRslt,
    MSCC_MMC_PLMN_ID_STRU                   *pstPlmnId,
    VOS_UINT32                               ulArfcn
);

VOS_VOID NAS_MMC_SndMsccAcqInd(
    NAS_MSCC_PIF_ACQ_RESULT_ENUM_UINT32      enAcqRslt,
    MSCC_MMC_PLMN_ID_STRU                   *pstPlmnId,
    VOS_UINT32                          ulArfcn
);

VOS_VOID NAS_MMC_SndMsccRegCnf(
    MMC_LMM_ATTACH_CL_REG_STATUS_ENUM8  enLmmAttachClRegStatus,
    NAS_MSCC_PIF_REG_RESULT_ENUM_UINT32 enRegRslt,
    MSCC_MMC_PLMN_ID_STRU              *pstPlmnId,
    VOS_UINT32                          ulArfcn
);

VOS_VOID NAS_MMC_SndMsccPowerSaveCnf(
    NAS_MSCC_PIF_POWER_SAVE_RESULT_ENUM_UINT8               enCause
);
/* Added by s00246516 for L-C互操作项目, 2014-02-12, End */

#if (FEATURE_ON == FEATURE_DSDS)
VOS_VOID NAS_MMC_SndMsccSrvAcqCnf(
    NAS_MSCC_PIF_SRV_ACQ_RESULT_ENUM_UINT8   enResult
);
#endif

VOS_VOID NAS_MMC_SndMsccRfAvailInd(
    VOS_UINT8                           ucRfAvail
);

/* Add by s00217060 for K3V3 多模多天线特性, 2014-06-27, Begin */
VOS_VOID NAS_MMC_SndMsccPsServiceConnStatusInd(
    VOS_UINT8                                       ucPsServiceConnStatusFlag,
    MSCC_MMC_PS_SIGNALING_TYPE_ENUM_UINT8           enPsSigType
);
/* Add by s00217060 for K3V3 多模多天线特性, 2014-06-27, End */


VOS_VOID  NAS_MMC_SndMsccMsgLmmCellSignInfoInd(
    MSCC_MMC_SCELL_MEAS_REPORT_TYPE_UN  *punMeasReportType,
    MSCC_MMC_LMM_CELL_SIGN_INFO_STRU     *pstRssiValueInfo
);

extern VOS_VOID NAS_MMC_SndMsccCFPlmnSetCnf(
    NAS_MSCC_PIF_CFPLMN_OPER_RESULT_ENUM_UINT32             enRslt
);
extern VOS_VOID NAS_MMC_SndMsccCFPlmnQueryCnf(
    NAS_MSCC_PIF_CFPLMN_OPER_RESULT_ENUM_UINT32             enRslt,
    NAS_MSCC_PIF_CFPLMN_LIST_STRU                          *pstCFPlmnListInfo
);

VOS_VOID NAS_MMC_SndMsccGetGeoCnf(
    NAS_MSCC_PIF_PLMN_ID_STRU          *pstPlmnId
);
VOS_VOID NAS_MMC_SndMsccStopGetGeoCnf(VOS_VOID);

VOS_VOID NAS_MMC_SndMsccDplmnSetCnf(
    VOS_UINT32                         ulRslt,
    TAF_MMA_CTRL_STRU                 *pstCtrl
);

VOS_VOID NAS_MMC_SndMsccPrefPlmnSetCnf(
    NAS_MSCC_PIF_PREF_PLMN_OPER_RESULT_ENUM_UINT32          enRslt
);

VOS_VOID NAS_MMC_SndMmcUpdateUplmnNotify( VOS_VOID );

VOS_VOID NAS_MMC_SndMsccBgSearchCnf(
    MMC_LMM_BG_SRCH_RLT_ENUM_UINT32  enRlst,
    VOS_UINT8                        ucHrpdSysNum,
    LMM_MMC_HRPD_SYS_STRU           *pstHrpdSysList
);
VOS_VOID NAS_MMC_SndMsccStopBgSearchCnf(VOS_VOID);

VOS_VOID NAS_MMC_SndMsccPrefPlmnInfoInd(
    NAS_MSCC_PIF_PREF_PLMN_TYPE_ENUM_UINT8                  enPrefPlmnType
);

VOS_VOID NAS_MMC_SndMsccMmssLteUnAvailableInd(
    MSCC_MMC_MMSS_LTE_UNAVIALBLE_REASON_ENUM_UINT8          enReason
);

VOS_VOID NAS_MMC_SndMsccQueryPlmnPriClassCnf(
    NAS_MSCC_PIF_PLMN_PRI_CLASS_LIST_INFO_STRU             *pstPlmnPriClassListInfo
);


VOS_VOID NAS_MMC_SndMsccSrchedPlmnInfo(
    const MMC_MSCC_SRCHED_PLMN_INFO_IND_STRU  *pstMmcSrchedPlmnINfo
);

VOS_VOID NAS_MMC_SndMsccInterSysStartInd(
    NAS_MSCC_PIF_INTERSYS_CAUSE_ENUM_UINT32                 enInterSysCause,
    VOS_RATMODE_ENUM_UINT32                                 enOrignRatMode,
    VOS_RATMODE_ENUM_UINT32                                 enDestRatMode
);


VOS_VOID NAS_MMC_SndMsccInterSysEndInd(
    VOS_RATMODE_ENUM_UINT32             enCurrRatMode
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

#endif /* end of NasMmcSndMscc.h */
