/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMsccSndMma.h
  版 本 号   : 初稿
  作    者   : y00245242
  生成日期   : 2015年01月27日
  最近修改   :
  功能描述   : NasMsccSndMma.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年01月27日
    作    者   : y00245242
    修改内容   : 创建文件

******************************************************************************/

#ifndef __NAS_MSCC_SND_MMA_H__
#define __NAS_MSCC_SND_MMA_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "MsccMmcInterface.h"
#include "MmaMsccInterface.h"
#include "xsd_mscc_pif.h"
#include "hsd_mscc_pif.h"

#include "NasMsccCtx.h"

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
VOS_VOID NAS_MSCC_SndMmaImsVoiceCapInd(
    VOS_UINT8                           ucImsVoiceAvail
);

VOS_VOID NAS_MSCC_SndMmaNetworkCapabilityInfoInd(
    MMC_MSCC_NETWORK_CAPABILITY_INFO_IND_STRU              *pstNwCapInfoInd
);

VOS_VOID NAS_MSCC_SndMmaRegResultInd(
    MMC_MSCC_REG_RESULT_IND_STRU       *pstRegResultInd
);

VOS_VOID NAS_MSCC_SndMma3gppSysInfoInd(
    MMC_MSCC_SYS_INFO_IND_STRU         *pstSysInfoInd
);

VOS_VOID NAS_MSCC_SndMmaServiceStatusInd(
    MMC_MSCC_SERVICE_STATUS_IND_STRU   *pstSrvStatusInd
);

VOS_VOID NAS_MSCC_SndMmaUserSpecPlmnSearchRej( VOS_VOID );

VOS_VOID NAS_MSCC_SndMmaAcInfoChangeInd(
    MMC_MSCC_AC_INFO_CHANGE_IND_STRU  *pstMsg
);
VOS_VOID NAS_MSCC_SndMmaEplmnInfoInd(
    MMC_MSCC_EPLMN_INFO_IND_STRU       *pstMsg
);


VOS_VOID NAS_MSCC_SndMmaEOPlmnSetCnf(
    MMC_MSCC_EOPLMN_SET_CNF_STRU       *pstMsg
);

VOS_VOID NAS_MSCC_SndMmaCampOnInd(
    MMC_MSCC_CAMP_ON_IND_STRU_STRU     *pstMsg
);
VOS_VOID NAS_MSCC_SndMmaWCipherInfo(
    MMC_MSCC_UMTS_CIPHER_INFO_IND_STRU *pstMsg
);
VOS_VOID NAS_MSCC_SndMmaGCipherInfo(
    MMC_MSCC_GPRS_CIPHER_INFO_IND_STRU *pstMsg
);

VOS_VOID NAS_MSCC_SndMmaAcqCnf(
    MMC_MSCC_ACQ_CNF_STRU              *pstMsg
);

VOS_VOID NAS_MSCC_SndMmaAcqInd(
    MMC_MSCC_ACQ_IND_STRU               *pstMsg
);

VOS_VOID NAS_MSCC_SndMmaRegCnf(
    MMC_MSCC_REG_CNF_STRU              *pstMsg
);
VOS_VOID NAS_MSCC_SndMmaPowerSaveCnf(
    MMC_MSCC_POWER_SAVE_CNF_STRU       *pstMsg
);

VOS_VOID NAS_MSCC_SndMmaPsServiceConnStatusInd(
    MMC_MSCC_PS_SERVICE_CONN_STATUS_IND_STRU               *pstMsg
);

VOS_VOID NAS_MSCC_SndMmaRfAvailInd(
    NAS_MSCC_PIF_RF_AVAILABLE_IND_STRU  *pstMsg
);

VOS_VOID NAS_MSCC_SndMmaPlmnListCnf(
    MMC_MSCC_PLMN_LIST_CNF_STRU        *pstMsg
);

VOS_VOID NAS_MSCC_SndMmaPlmnListRej(
    MMC_MSCC_PLMN_LIST_REJ_STRU        *pstMsg
);

VOS_VOID NAS_MSCC_SndMmaPlmnSpecialSelCnf(
   MMC_MSCC_PLMN_SPECIAL_SEL_CNF_STRU  *pstMsg
);

VOS_VOID NAS_MSCC_SndMmaPlmnSpecialSelRej(
  MMC_MSCC_PLMN_SPECIAL_SEL_REJ_STRU   *pstMsg
);

VOS_VOID NAS_MSCC_SndMmaPlmnReselCnf(
  NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_ENUM_UINT8           enResult
);

VOS_VOID NAS_MSCC_SndMmaRssiInd(
    MMC_MSCC_RSSI_IND_STRU             *pstMsg
);

VOS_VOID NAS_MSCC_SndMmaMmInfo(
    MMC_MSCC_MM_INFO_IND_STRU          *pstMsg
);

VOS_VOID NAS_MSCC_SndMmaSystemAcquireStartInd(
    MSCC_MMA_ACQ_SYS_TYPE_ENUM_UINT32   enSysType
);

VOS_VOID NAS_MSCC_SndMmaDataTranAttri(
    MMC_MSCC_DATATRAN_ATTRI_IND_STRU   *pstMsg
);

VOS_VOID NAS_MSCC_SndMmaCoverageInd(
    MMC_MSCC_COVERAGE_AREA_IND_STRU    *pstMsg
);

VOS_VOID NAS_MSCC_SndMmaNetScanCnf(
    MSCC_MMA_NET_SCAN_CNF_STRU          *pstMsg
);

VOS_VOID NAS_MSCC_SndMmaAbortNetScanCnf(
    MMC_MSCC_ABORT_NET_SCAN_CNF_STRU    *pstMsg
);

VOS_VOID NAS_MSCC_SndMmaUsimAuthFailInd(
    MMC_MSCC_USIM_AUTH_FAIL_IND_STRU   *pstMsg
);

VOS_VOID NAS_MSCC_SndMmaCsServiceConnStatusInd(
    MMC_MSCC_CS_SERVICE_CONN_STATUS_IND_STRU               *pstMsg
);

VOS_UINT32 NAS_MSCC_SndMmaServRejRsltInd(
    MMC_MSCC_SERV_REJ_IND_STRU         * pstMsg
);

VOS_VOID NAS_MSCC_SndMmaAttachCnf(
     MMC_MSCC_ATTACH_CNF_STRU          *pstMsg
);

VOS_VOID NAS_MSCC_SndMmaDetachInd(
    MMC_MSCC_DETACH_IND_STRU           *pstMsg
);

VOS_VOID NAS_MSCC_SndMmaDetachCnf(
    MMC_MSCC_DETACH_CNF_STRU           *pstMsg
);

VOS_VOID NAS_MSCC_SndMmaSysCfgCnf(
    NAS_MSCC_PIF_SYS_CFG_SET_RESULT_ENUM_UINT32      ulSysCfgCnfRst
);

VOS_VOID NAS_MSCC_SndMmaPlmnListAbortCnf(
    MSCC_MMA_PLMN_LIST_ABORT_CNF_STRU    *pstMmcPlmnListAbortCnf
);

VOS_VOID NAS_MSCC_SndMmaSpecPlmnSearchAbortCnf(
    MMC_MSCC_SPEC_PLMN_SEARCH_ABORT_CNF_STRU               *pstMsg
);

#if (FEATURE_ON == FEATURE_CSG)
VOS_VOID NAS_MSCC_SndMmaCsgListAbortCnf(
    MMC_MSCC_CSG_LIST_ABORT_CNF_STRU   *pstMsg
);
VOS_VOID NAS_MSCC_SndMmaCsgListSearchCnf(
    MMC_MSCC_CSG_LIST_SEARCH_CNF_STRU  *pstMsg
);
VOS_VOID NAS_MSCC_SndMmaCsgListRej(
    MMC_MSCC_CSG_LIST_REJ_STRU         *pstMsg
);

#endif

VOS_VOID NAS_MSCC_SndMmaGetGeoCnf(
    NAS_MSCC_NO_CARD_INIT_SEARCH_LOC_STRU                  *pstNoCardInitSearchLocInfo
);

VOS_VOID NAS_MSCC_SndMmaStopGetGeoCnf(
    MMC_MSCC_STOP_GET_GEO_CNF_STRU     *pstMsg
);

VOS_VOID NAS_MSCC_SndMmaDplmnSetCnf(
    MMC_MSCC_DPLMN_SET_CNF_STRU        *pstMsg
);

VOS_VOID NAS_MSCC_SndMmaSrvAcqCnf(
    MMC_MSCC_SRV_ACQ_CNF_STRU          *pstMsg
);


VOS_VOID NAS_MSCC_SndMmaSwitchOnRsltCnf(
    NAS_MSCC_PIF_START_RESULT_ENUM_UINT32                   ulRslt
);

VOS_VOID NAS_MSCC_SndMmaPowerOffRsltCnf(VOS_VOID);

VOS_VOID NAS_MSCC_SndMmaSystemAcquireEndInd(
    MSCC_MMA_SYSTEM_ACQUIRE_RESULT_ENUM_UINT32              enResult,
    MSCC_MMA_ACQ_SYS_TYPE_ENUM_UINT32                       enAcqSysType,
    MSCC_MMA_CL_SYSTEM_ACQUIRE_RESULT_TYPE_ENUM_UINT32      enAcqRsltType
);

VOS_VOID NAS_MSCC_SndMmaHrpdServiceStatusInd(
    MSCC_MMA_HRPD_SERVICE_STATUS_ENUM_UINT32                enHrpdSrvSta,
    VOS_UINT8                                               ucIsNewSession,
    VOS_UINT8                                               ucIsEhrpdSupport,
    MSCC_MMA_HRPD_SESSION_RELEASE_TYPE_ENUM_UINT32          enCurrSessionRelType
);

VOS_VOID NAS_MSCC_SndMmaHrpdOverheadMsgInd(
    HSD_MSCC_OVERHEAD_MSG_IND_STRU     *pstMsccOhmMsgs
);



extern VOS_VOID NAS_MSCC_SndMmaCFPlmnSetCnf(
    MMC_MSCC_CFPLMN_SET_CNF_STRU       *pstMsg
);
extern VOS_VOID NAS_MSCC_SndMmaCFPlmnQueryCnf(
    MMC_MSCC_CFPLMN_QUERY_CNF_STRU     *pstMsg
);

VOS_VOID NAS_MSCC_SndMmaPrefPlmnQueryCnf(
    MMC_MSCC_PREF_PLMN_QUERY_CNF_STRU  *pstMsg
);

VOS_VOID NAS_MSCC_SndMmaPrefPlmnSetCnf(
    MMC_MSCC_PREF_PLMN_SET_CNF_STRU  *pstMsg
);

VOS_VOID NAS_MSCC_SndMmaCdmacsqSetCnf(
    XSD_MSCC_CDMACSQ_SET_CNF_STRU      *pstMsg
);

VOS_VOID NAS_MSCC_SndMmaCdmacsqSignalQualityInd(
   XSD_MSCC_CDMACSQ_IND_STRU           *pstMsg
);

VOS_VOID NAS_MSCC_SndMma1xSystemServiceInfoInd(
    XSD_MSCC_1X_SYSTEM_SERVICE_INFO_IND_STRU                *pstMsg
);

VOS_VOID NAS_MSCC_SndMmaLmmCellSignInfoReportInd(
    MMC_MSCC_LMM_CELL_SIGN_INFO_REPORT_IND_STRU            *pstMsg
);


VOS_VOID NAS_MSCC_SndMma1xSystemTimeInd(
    XSD_MSCC_1X_SYSTEM_TIME_IND_STRU   *pstMsg
);

VOS_VOID NAS_MSCC_SndMmaUeStatusInd(
    VOS_UINT8                           ucUeMainState,
    VOS_UINT8                           ucUeSubState
);



#if (FEATURE_ON == FEATURE_IMS)
VOS_VOID NAS_MSCC_SndMmaImsStartCnf(
    NAS_MSCC_PIF_IMS_START_RESULT_ENUM_UINT32               enResult
);

VOS_VOID NAS_MSCC_SndMmaImsStopCnf(
    NAS_MSCC_PIF_IMS_STOP_RESULT_ENUM_UINT32                enResult
);

VOS_VOID NAS_MSCC_SndMmaImsSwitchStateInd(
    NAS_MSCC_PIF_IMS_SWITCH_STATE_ENUM_UINT8                enImsSwitch
);
#endif


#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)



VOS_VOID NAS_MSCC_SndMmaSidNidInd(
    VOS_UINT16                          usSid,
    VOS_UINT16                          usNid
);

VOS_VOID NAS_MSCC_SndMmaSyncServiceAvailInd(
    MSCC_MMA_SYNC_SERVICE_AVAIL_IND_STRU                   *pstSyncSrvAvailInd
);

VOS_VOID NAS_MSCC_SndMmaHdrcsqSetCnf(
    HSD_MSCC_HDR_CSQ_SET_CNF_STRU      *pstHsdSetCnf
);

VOS_VOID NAS_MSCC_SndMmaHdrcsqSignalQualityInd(
   MSCC_MMA_HDR_CSQ_IND_STRU           *pstMsg
);

VOS_VOID NAS_MSCC_SndMmaDataCallRedialSysAcqInd(
   NAS_MSCC_PIF_ACQUIRED_RESULT_ENUM_UINT32    enRslt,
   VOS_UINT8                                   ucIsEhrpdSupport
);

VOS_VOID NAS_MSCC_SndMmaEmcCallBackInd(
   NAS_MSCC_PIF_EMC_CALLBACK_MODE_ENUM_UINT32               enCallBackMode
);

#endif

VOS_VOID NAS_MSCC_SndMmaSrchedPlmnInfo(
    MMC_MSCC_SRCHED_PLMN_INFO_IND_STRU                     *pstMsg
);

VOS_VOID NAS_MSCC_SndMmaHandsetInfoQryCnf(
    MSCC_MMA_HANDSET_INFO_QRY_CNF_STRU                     *pstInfo
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

#endif /* end of NasMsccSndMma.h */
