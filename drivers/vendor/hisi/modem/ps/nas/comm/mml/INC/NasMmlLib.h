/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmlLib.h
  版 本 号   : 初稿
  作    者   : zhoujun 40661
  生成日期   : 2011年7月25日
  最近修改   :
  功能描述   : NasMmlLib.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年7月25日
    作    者   : zhoujun 40661
    修改内容   : 创建文件

******************************************************************************/
#ifndef _NAS_MML_LIB_H_
#define _NAS_MML_LIB_H_
/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "NasMmlCtx.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#include  "MmLmmInterface.h"
#endif


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define NAS_MML_SoftReBoot(ulRebootScean) NAS_MML_SoftReBoot_WithLineNoAndFileID( (__LINE__), (THIS_FILE_ID), (ulRebootScean))

#define NAS_MML_MIN(n1,n2)                                  (((n1) > (n2)) ? (n2):(n1))

/* GUNAS临终遗言的长度 */
#define GUNAS_SAVE_EXC_LOG_LENGTH_MODEM0             (3072)
#define GUNAS_SAVE_EXC_LOG_LENGTH_MODEM1             (3072)
#define GUNAS_SAVE_EXC_LOG_LENGTH_MODEM2             (3072)

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
 结构名    : NAS_MML_MCC_DESC_STRU
 结构说明  : 记录一个国家所有的国家码信息的结构体
 1.日    期   : 2015年9月30日
   作    者   : l00289540
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                ulMccNum;
    VOS_UINT32               *pulMccList;
}NAS_MML_MCC_DESC_STRU;

/*****************************************************************************
 结 构 名  : NAS_MML_SAVE_EXC_LOG_STRU
 结构说明  : 保存NAS复位时的结构，包含NAS MML的全局变量
             总分配内存为3072，目前已用2540
 修改历史  :
  1.日  期   : 2015年11月30日
    作  者   : z00359541
    修改内容 : 新生成结构,DTS2015112803743
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulBeginTag;
    NAS_MML_LOG_EVENT_STATE_STRU        stLogEventState;    
    NAS_MML_SIM_STATUS_STRU             stSimStatus;                            /* SIM卡状态 */
    NAS_MML_SIM_MS_IDENTITY_STRU        stMsIdentity;                           /* MS Identity信息 */
    NAS_MML_SIM_PS_SECURITY_INFO_STRU   stPsSecurity;                           /* PS域的安全参数 */
    NAS_MML_SIM_CS_SECURITY_INFO_STRU   stCsSecurity;                           /* CS域的安全参数 */
    NAS_MML_SIM_NATIVE_CONTENT_STRU     stSimNativeContent;                     /* SIM卡文件中保存的原始内容以便写卡时进行比较 */
    NAS_MML_CALL_MODE_ENUM_UINT8        enCallMode;                             /* ecall模式 */
    VOS_UINT8                           aucReserve[3];
    NAS_MML_MS_3GPP_REL_STRU            stMs3GppRel;                            /* 支持的协议版本 */
    NAS_MML_MS_CAPACILITY_INFO_STRU     stMsCapability;                         /* MS的手机能力 */
    NAS_MML_MS_SYS_CFG_INFO_STRU        stMsSysCfgInfo;                         /* 系统配置信息 */
    NAS_MML_CAMP_PLMN_INFO_STRU         stCampPlmnInfo;                         /* 当前驻留PLMN信息 */
    NAS_MML_CS_DOMAIN_INFO_STRU         stCsDomainInfo;                         /* 当前CS域信息 */
    NAS_MML_PS_DOMAIN_INFO_STRU         stPsDomainInfo;                         /* 当前PS域信息 */
    NAS_MML_MS_BAND_INFO_STRU           stBandInfo;                             /* 当前驻留的BAND信息 */
    NAS_MML_NETWORK_3GPP_REL_STRU       stNetwork3GppRel;                       /* 当前网络的协议版本 */
    NAS_MML_CONN_STATUS_INFO_STRU       stConnStatus;                           /* 当前连接存在状态 */
    NAS_MML_EPS_DOMAIN_INFO_STRU        stEpsDomainInfo;                        /* EPS域信息 */
    NAS_MML_PS_BEARER_CONTEXT_STRU      astPsBearerContext[NAS_MML_MAX_PS_BEARER_NUM];  /* PS承载上下文信息 */
    NAS_MML_IMS_DOMAIN_INFO_STRU        stImsDomainInfo;                        /* IMS域信息 */
    NAS_MML_NO_RF_INFO_STRU             stNoRfInfo;
    NAS_MML_ORIGNAL_REJECT_CAUSE_STRU   stOriginalRejectCause;
    VOS_UINT32                          ulEndTag;
}NAS_MML_SAVE_EXC_LOG_STRU;

/*****************************************************************************
 结构名    : NAS_MML_DISCARD_MSG_STRU
 结构说明  : 复位分析要忽略的消息的结构体
 1.日    期   : 2015年11月30日
   作    者   : z00359541
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_PID                             ulSenderPid;        /* 消息发送方PID */
    VOS_PID                             ulReceiverPid;        /* 消息发送方PID */
    VOS_UINT32                          ulMsgName;          /* 发送消息ID */
}  NAS_MML_DISCARD_MSG_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
VOS_UINT32  NAS_MML_CompareBcchPlmnwithSimPlmn(
   NAS_MML_PLMN_ID_STRU                *pstBccPlmnId,
   NAS_MML_PLMN_ID_STRU                *pstSimPlmnId
);
VOS_UINT32  NAS_MML_GetCsServiceExistFlg( VOS_VOID );


VOS_UINT32  NAS_MML_GetPsServiceExistFlg( VOS_VOID );

VOS_UINT32 NAS_MML_IsMccInDestMccList (
    VOS_UINT32                          ulMcc,
    VOS_UINT32                          ulMccNum,
    VOS_UINT32                         *pulMccList
);


VOS_UINT8 NAS_MML_IsRoamingRejectNoRetryFlgActived(VOS_UINT8 ucCause);

VOS_UINT32  NAS_MML_IsPlmnIdInForbidPlmnList(
   NAS_MML_PLMN_ID_STRU                *pstPlmnId
);

VOS_UINT32  NAS_MML_IsLaiInDestLaiList (
   NAS_MML_LAI_STRU                   *pstLai,
   VOS_UINT32                          ulLaiNum,
   NAS_MML_LAI_STRU                   *pstLaiList
);

VOS_UINT32 NAS_MML_GetLaiIndexInDestLaiList (
    NAS_MML_LAI_STRU                   *pstLai,
    VOS_UINT8                          *pucLaiIdx,
    VOS_UINT8                           ulLaiNum,
    NAS_MML_LAI_STRU                   *pstLaiList
);

VOS_UINT32 NAS_MML_ComparePlmnIdWithHplmn (
   NAS_MML_PLMN_ID_STRU                *pstPlmnId
);

/* Added by s00246516 for L-C互操作项目, 2014-02-12, Begin */
VOS_UINT32 NAS_MML_ComparePlmnIdWithUplmn (
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
);

VOS_UINT32 NAS_MML_ComparePlmnIdWithOplmn (
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
);
/* Added by s00246516 for L-C互操作项目, 2014-02-12, End */

VOS_UINT32  NAS_MML_IsNetRatSupported(
   NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enSpecRat
);

VOS_UINT32 NAS_MML_IsSpecRatInRatList(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enSpecRat,
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatList
);


/* Added by s00246516 for L-C互操作项目, 2014-02-14, Begin */
VOS_UINT32 NAS_MML_IsSpec3Gpp2RatInRatList(
    NAS_MML_3GPP2_RAT_TYPE_ENUM_UINT8   enSpec3Gpp2Rat,
    NAS_MML_3GPP2_RAT_PRIO_STRU        *pst3Gpp2RatList
);
/* Added by s00246516 for L-C互操作项目, 2014-02-14, End */

VOS_UINT32  NAS_MML_IsBcchPlmnIdInDestSimPlmnList (
   NAS_MML_PLMN_ID_STRU               *pstPlmnId,
   VOS_UINT8                           ucPlmnNum,
   NAS_MML_PLMN_ID_STRU               *pstPlmnIdList
);

VOS_UINT32 NAS_MML_IsSimPlmnIdInDestBcchPlmnList (
    NAS_MML_PLMN_ID_STRU               *pstSimPlmnId,
    VOS_UINT8                           ucBcchPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pstBcchPlmnIdList
);



VOS_UINT32 NAS_MML_IsBcchPlmnIdInDestSimPlmnWithRatList (
    NAS_MML_PLMN_ID_STRU               *pstBcchPlmnId,
    VOS_UINT16                          usSimPlmnWithRatNum,
    NAS_MML_SIM_PLMN_WITH_RAT_STRU     *pstSimPlmnWithRatList
);
#if (FEATURE_ON == FEATURE_CSG)
VOS_UINT32 NAS_MML_IsSupportLteCsg(VOS_VOID);
#endif


VOS_UINT32  NAS_MML_IsPlmnIdRoamingAllowed(
   NAS_MML_PLMN_ID_STRU                *pstPlmnId
);

VOS_UINT32  NAS_MML_IsPlmnIdValid(
   NAS_MML_PLMN_ID_STRU                *pstPlmnId
);

VOS_UINT32 NAS_MML_IsBcchPlmnIdInLockPlmnList (
    NAS_MML_PLMN_ID_STRU               *pstBcchPlmnId
);

VOS_UINT32 NAS_MML_IsMccValid(
    VOS_UINT32                          ulMcc
);
VOS_UINT32  NAS_MML_IsRrcConnExist( VOS_VOID );

VOS_UINT32  NAS_MML_IsTmsiValid(VOS_VOID);

VOS_UINT32  NAS_MML_IsPtmsiValid(VOS_VOID);

VOS_UINT32  NAS_MML_IsQuickStartFlg( VOS_VOID );


VOS_UINT32  NAS_MML_GetGsmForbidFlg( VOS_VOID );

VOS_VOID    NAS_MML_InitSimPlmnInfo(
    VOS_UINT32                          ulPlmnNum,
    NAS_MML_SIM_PLMN_WITH_RAT_STRU     *pstPlmnInfo
);

VOS_VOID  NAS_MML_ResumeSimEhplmnList(
    VOS_UINT8                          *pucPlmnNum,
    NAS_MML_SIM_PLMN_WITH_RAT_STRU     *pstPlmnInfo
);
VOS_UINT32 NAS_MML_IsUsimStausValid(VOS_VOID);

VOS_UINT32 NAS_MML_GetRPlmn(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
);

#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32 NAS_MML_GetLteRPlmn(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
);

VOS_UINT32 NAS_MML_IsPlmnIdInCsDomainUnAvailPlmnList(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
);


VOS_VOID NAS_MML_UpdateEpsConnectionStatus(MMC_LMM_CONN_STATE_ENUM_UINT32 enEpsConnState);

VOS_UINT32 NAS_MML_IsTaiInDestTaiList (
    NAS_MML_TAI_STRU                   *pstTai,
    VOS_UINT32                          ulTaiNum,
    NAS_LMM_TAI_STRU                   *pstTaiList
);


/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-15, begin */
VOS_UINT32 NAS_MML_IsSupportLteCapability(VOS_VOID);

/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-15, end */
#endif

VOS_UINT32 NAS_MML_GetGURPlmn(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
);

VOS_UINT32 NAS_MML_GetEfLociPlmn(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
);

VOS_UINT32 NAS_MML_GetPlmnIdxInList (
    NAS_MML_PLMN_ID_STRU               *pstPlmnId,
    VOS_UINT32                          ulPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pstPlmnIdList
);

VOS_UINT32 NAS_MML_DelInvalidPlmnFromList(
    VOS_UINT32                          ulPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pHandlingPlmnList
);

VOS_VOID NAS_MML_DelPlmnsInRefList(
    VOS_UINT8                          *pHandlingPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pHandlingPlmnList,
    VOS_UINT8                           ucRefPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pRefPlmnList
);

VOS_VOID NAS_MML_DelPlmnsNotInRefList(
    VOS_UINT8                          *pHandlingPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pHandlingPlmnList,
    VOS_UINT8                           ucRefPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pRefPlmnList
);

VOS_UINT32 NAS_MML_AddForbPlmn (
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
);

VOS_UINT32 NAS_MML_DelForbPlmn (
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
);

VOS_VOID NAS_MML_AddForbGprsPlmn(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
);

VOS_VOID NAS_MML_DelForbGprsPlmn (
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
);

VOS_VOID NAS_MML_AddForbRoamLa (
    NAS_MML_LAI_STRU                                       *pstLai,
    NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU               *pstForbRoamLaInfo
);


VOS_VOID NAS_MML_AddForbRegLa (
    NAS_MML_LAI_STRU                   *pstLai
);

VOS_UINT32 NAS_MML_DelForbLa (
    NAS_MML_LAI_STRU                   *pstLai,
    NAS_MML_REG_DOMAIN_ENUM_UINT8       enDomain
);

VOS_VOID NAS_MML_DelNotAllowRoamPlmnInList(
    VOS_UINT8                          *pucPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pstPlmnList
);

VOS_UINT32 NAS_MML_DelForbPlmnInList(
    VOS_UINT32                          ulPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pHandlingPlmnList
);


VOS_UINT32 NAS_MML_GetLaiForbType(
    NAS_MML_LAI_STRU                   *pstLai
);

VOS_UINT32 NAS_MML_IsGsmOnlyMode(
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatOrder
);

VOS_UINT32 NAS_MML_IsWcdmaPrioGsm(
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatOrder
);


VOS_UINT32 NAS_MML_IsWcdmaOnlyMode(NAS_MML_PLMN_RAT_PRIO_STRU * pstRatOrder);

VOS_UINT32 NAS_MML_IsLteOnlyMode(
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatOrder
);

VOS_VOID NAS_MML_RemoveRoamPlmnInSrchList(
    VOS_UINT8                          *pPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pstPlmnList
);

VOS_UINT32 NAS_MMC_IsRoam(VOS_VOID);
VOS_UINT32 NAS_MML_IsHplmnInEplmnList(VOS_VOID);
VOS_UINT32 NAS_MML_IsCurrCampPlmnInEplmnList(VOS_VOID);

VOS_UINT32 NAS_MML_IsPlmnInEplmnList(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
);

VOS_UINT32 NAS_MML_IsCampPlmnInfoChanged(
    NAS_MML_CAMP_PLMN_INFO_STRU        *pOldCampInfo,
    NAS_MML_CAMP_PLMN_INFO_STRU        *pNewCampInfo
);

NAS_MML_RRC_SYS_SUBMODE_ENUM_UINT8 NAS_MML_ConvertGprsSupportIndToSysSubMode(
    VOS_UINT8                           ucGprsSupportInd
);

VOS_VOID NAS_MML_SecContext3GTO2G(
    VOS_UINT8                           *pucIk,
    VOS_UINT8                           *pucCk,
    VOS_UINT8                           *pucKc
);

VOS_VOID NAS_MML_SecContext2GTO3G(
    VOS_UINT8                           *pucIk,
    VOS_UINT8                           *pucCk,
    VOS_UINT8                           *pucKc
);
#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID  NAS_MML_ConvertNasPlmnToLMMFormat(
    MMC_LMM_PLMN_ID_STRU               *pLMMPlmn,
    NAS_MML_PLMN_ID_STRU               *pstGUNasPlmn
);

VOS_VOID NAS_MML_ConvertGuMsModeToLteUeOperationMode(
    NAS_MML_MS_MODE_ENUM_UINT8                              enMsMode,
    NAS_MML_LTE_UE_OPERATION_MODE_ENUM_UINT8               *penOpertaionMode
);

VOS_UINT32 NAS_MML_IsCsfbServiceStatusExist(VOS_VOID);

VOS_UINT32 NAS_MML_IsCsfbMoServiceStatusExist(VOS_VOID);

VOS_UINT32 NAS_MML_IsLteOnlyMode(
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatOrder
);

NAS_MML_LTE_UE_OPERATION_MODE_ENUM_UINT8 NAS_MML_GetLteUeOperationMode( VOS_VOID);
#endif
VOS_VOID NAS_MML_SortSpecRatPrioHighest(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enSpecRat,
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList
);

VOS_VOID NAS_MML_SortSpecRatPrioLowest(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enSpecRat,
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList
);
VOS_VOID NAS_MML_DelSpecRatInPrioRatList(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enSpecRat,
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList
);
VOS_UINT32 NAS_MML_ComparePlmnMcc(
    VOS_UINT32                          ulSrcMcc,
    VOS_UINT32                          ulDestMcc
);

VOS_UINT32 NAS_MML_IsIndianMcc(
    VOS_UINT32                          ulMcc
);
VOS_UINT32 NAS_MML_IsNorthAmericanMcc(
    VOS_UINT32                          ulMcc
);
VOS_UINT8 NAS_MML_GetBitValueFromBuffer(
    VOS_UINT8                          *pucDataBuf,
    VOS_UINT32                          ulBitNo
);

VOS_VOID NAS_MML_SetBitValueToBuffer(
    VOS_UINT8                          *pucDataBuf,
    VOS_UINT32                          ulBitNo,
    VOS_UINT8                           ucValue
);
VOS_UINT8 NAS_MML_IsUeSupportImsVoice(VOS_VOID);


NAS_MML_MCC_DESC_STRU * NAS_MML_GetEquivalentMccList(
    VOS_UINT32 ulMcc
);

VOS_UINT32 NAS_MML_IsSpecMccInEquMccList(
    VOS_UINT32 ulMcc,
    NAS_MML_MCC_DESC_STRU *pstMccList
);

VOS_UINT32 NAS_MML_IsPlmnMccBelongToTheSameCountry(
    VOS_UINT32                          ulSrcMcc,
    VOS_UINT32                          ulDestMcc
);

VOS_UINT32 NAS_MML_IsBcchPlmnIdInDestSimBcdPlmnList(
    NAS_MML_PLMN_ID_STRU               *pstBcchPlmnId,
    VOS_UINT8                           ucSimPlmnNum,
    VOS_UINT8                          *pstSimBcdPlmnIdList
);

VOS_UINT32 NAS_MML_IsTheIntersectionOfSpecPlmnListsEmpty(
    VOS_UINT8                           ucSrcPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pstSrcPlmnIdList,
    VOS_UINT8                           ucDstPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pstDstPlmnIdList
);


VOS_UINT32 NAS_MML_IsPlmnIdForbiddenByWhiteBlackList (
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
);


VOS_UINT32 NAS_MML_IsEquPlmnInfoChanged(
    NAS_MML_EQUPLMN_INFO_STRU          *pstSrcEquPlmnInfo
);

VOS_VOID NAS_MML_SoftReBoot_WithLineNoAndFileID(
    VOS_UINT32                          ulLineNO,
    VOS_UINT32                          ulFileID,
    NAS_MML_REBOOT_SCENE_ENUM_UINT8     ucResetScean
);

VOS_VOID NAS_MML_GetMsNetworkCapability(
    NAS_MML_MS_NETWORK_CAPACILITY_STRU  *pstMsNetworkCapbility
);


VOS_UINT8 NAS_MML_IsRaiChanged(VOS_VOID);

#if defined (__PS_WIN32_RECUR__)
VOS_UINT32 NAS_MML_UnCompressData(
    VOS_UINT8                          *pucDest,
    VOS_UINT32                         *pulDestLen,
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulSrcLen
);
#endif
VOS_UINT32	NAS_MML_CompressData(
    VOS_UINT8                          *pucDest,
    VOS_UINT32                         *pulDestLen,
    VOS_UINT8                          *pucSrc,
    VOS_UINT32                          ulSrcLen
);



VOS_UINT32 NAS_MML_IsNetworkRegFailCause(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16 usRegFailCause
);

VOS_UINT32 NAS_MML_IsRegFailCauseNotifyLmm(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  usRegFailCause
);


VOS_UINT32 NAS_MML_IsSndOmPcRecurMsgValid(VOS_VOID);


VOS_VOID NAS_MML_DelEqualPlmnsInForbList(
    VOS_UINT8                          *pEPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pEPlmnList,
    VOS_UINT8                           ucRefPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pRefPlmnList
);

VOS_UINT32 NAS_MML_IsPsBearerExist(VOS_VOID);
VOS_UINT32 NAS_MML_IsPsBearerExistBeforeIsrAct(VOS_UINT8 ucRabId);
VOS_UINT32 NAS_MML_IsPsBearerAfterIsrActExist(VOS_VOID);
VOS_VOID NAS_MML_UpdateAllPsBearIsrFlg(
    NAS_MML_PS_BEARER_ISR_ENUM_UINT8    enPsBearerIsrFlg
);

#if  (FEATURE_ON == FEATURE_LTE)
VOS_VOID NAS_MML_ConvertMmlCsfbStatusToLmmCsfbStatus(
    NAS_MML_CSFB_SERVICE_STATUS_ENUM_UINT8                  enMmlCsfbStatus,
    MM_LMM_CSFB_SERVICE_TYPE_ENUM_UINT32                   *penLmmCsfbStatus
);

VOS_UINT32 NAS_MML_IsLteCapabilityDisabled(
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapStatus,
    VOS_UINT32                                              ulDisableLteRoamFlg
);


VOS_UINT32 NAS_MML_GetCsPsMode1EnableLteTimerLen(VOS_VOID);
#endif

VOS_UINT32 NAS_MML_IsPlmnSupportDam(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
);


VOS_UINT32 NAS_MML_IsImsiHplmnInDamImsiPlmnList(VOS_VOID);


VOS_UINT32 NAS_MML_IsNeedDeleteDisabledPlmnWithValidPeriodInPlmnList (
    NAS_MML_DISABLED_PLMN_WITH_FORBIDDEN_PERIOD_STRU                    *pstDisabledPlmnIdWithRat
);

VOS_UINT32 NAS_MML_IsNeedAddDamPlmnInDisabledPlmnWithForbiddenPeriodList(
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstPlmnWithRat
);

VOS_UINT32 NAS_MML_GetDamDisabledPlmnWithForbiddenPeriodTimeSlice(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstPlmnWithRat
);


VOS_UINT32 NAS_MML_GetFirstAddPlmnIndexInDestDisabledPlmnWithForbiddenPeriodList (
    VOS_UINT32                                              ulDestPlmnNum,
    NAS_MML_DISABLED_PLMN_WITH_FORBIDDEN_PERIOD_STRU       *pstDestPlmnIdList
);

VOS_VOID NAS_MML_AddDisabledRatPlmnWithForbiddenPeriodList(
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstPlmnWithRat,
    VOS_UINT32                                              ulPlmnDisabledInvalidSlice,
    MMC_LMM_DISABLE_LTE_REASON_ENUM_UINT32                  enDisableLteReason
);



VOS_UINT8 NAS_MML_IsCsLaiChanged(VOS_VOID);

VOS_VOID NAS_MML_DelEqualPlmnsInForbList(
    VOS_UINT8                          *pEPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pEPlmnList,
    VOS_UINT8                           ucRefPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pRefPlmnList
);
VOS_UINT8 NAS_MML_CompareLai(
    NAS_MML_LAI_STRU                    *pstCurLai,
    NAS_MML_LAI_STRU                    *pstOldLai
);

/* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-17, begin */
VOS_UINT32 NAS_MML_ExactlyCompareBcchPlmnwithSimPlmn(
    NAS_MML_PLMN_ID_STRU                *pstBccPlmnId,
    NAS_MML_PLMN_ID_STRU                *pstSimPlmnId
);

VOS_UINT32 NAS_MML_IsExistBufferedEmgCall(VOS_VOID);

/* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-17, end */

VOS_VOID NAS_MML_GetValidUserCfgEhplmnInfo(
    VOS_UINT8                          *pucImsi,
    VOS_UINT8                          *pucEhplmnListNum,
    NAS_MML_PLMN_ID_STRU               *pstEhPlmnList
);

VOS_UINT32  NAS_MML_GetRrcSimStatus(VOS_VOID);

VOS_UINT32 NAS_MML_IsBcchPlmnIdWithRatInDestPlmnWithRatList (
    NAS_MML_PLMN_WITH_RAT_STRU         *pstSrcPlmnId,
    VOS_UINT32                          ulDestPlmnNum,
    NAS_MML_PLMN_WITH_RAT_STRU         *pstDestPlmnIdList
);

VOS_UINT32 NAS_MML_IsRatInForbiddenList(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType
);

VOS_UINT32 NAS_MML_IsAllMsRatInForbiddenList (VOS_VOID);

VOS_UINT32 NAS_MML_IsImsiInForbiddenList (VOS_VOID);


#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32 NAS_MML_IsPlatformSupportLte(VOS_VOID);
#endif
VOS_UINT32 NAS_MML_IsPlatformSupportUtranFdd (VOS_VOID);
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
VOS_UINT32 NAS_MML_IsPlatformSupportUtranTdd (VOS_VOID);
#endif

VOS_UINT32 NAS_MML_IsDsdsMultiModemMode(VOS_VOID);

VOS_UINT32 NAS_MML_IsPlatformSupportGsm (VOS_VOID);
VOS_UINT32 NAS_MML_IsPlatformSupportUtran (VOS_VOID);


/* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
VOS_UINT32 NAS_MML_IsAcInfoChanged(
    NAS_MML_ACCESS_RESTRICTION_STRU    *pstOldAcRestrictInfo,
    NAS_MML_ACCESS_RESTRICTION_STRU    *pstNewAcRestrictInfo
);
/* Added by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */

VOS_VOID NAS_MML_Update_Revision_Level(
    VOS_UINT8                          *pucClassMark
);


VOS_VOID NAS_MML_GetSupportBandNum(
    VOS_UINT32                          ulBand,
    VOS_UINT8                          *pucBandNum
);

VOS_VOID NAS_MML_Fill_IE_ClassMark2(
    VOS_UINT8                          *pClassMark2
);


VOS_UINT32  NAS_MML_IsCsServDomainAvail(
    NAS_MML_MS_MODE_ENUM_UINT8          enMsMode
);


VOS_VOID NAS_MML_ConvertOamSendPid(
    VOS_UINT32                         *pulConvertedSendPid
);


#if (FEATURE_ON == FEATURE_PTM)
VOS_UINT32 NAS_MML_IsErrLogNeedRecord(VOS_UINT16 usLevel);

VOS_UINT32 NAS_MML_IsNeedNwSearchInfoRecord(
    VOS_VOID                           *pstMsg
);
VOS_VOID NAS_MML_RecordNwSearchInfo(
    VOS_VOID                           *pstMsg
);

#endif

VOS_UINT32 NAS_MML_IsGutAsPid(VOS_UINT32 ulPid);

VOS_UINT32 NAS_MML_IsAsPid(VOS_UINT32 ulPid);
VOS_VOID NAS_MML_SaveNwSearchReqInfo(
    VOS_VOID                           *pstMsg
);
VOS_VOID  NAS_MML_ConvertSimPlmnToNasPLMN(
    NAS_MML_SIM_FORMAT_PLMN_ID          *pstSimPlmn,
    NAS_MML_PLMN_ID_STRU                *pstNasPlmn
);

VOS_UINT32 NAS_MML_DecodeEmergencyNumList(
    VOS_UINT16                         *pusIndex,
    VOS_UINT8                          *pucRcvMsg,
    VOS_UINT16                          usMsgSize
);

VOS_UINT32 NAS_MML_IsNvimOplmnAvail(VOS_VOID);

/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-21, begin */
VOS_VOID NAS_MML_Fill_IE_TddClassMark3(
    VOS_UINT8                          *pTddClassMark3
);

VOS_VOID NAS_MML_Fill_IE_FddClassMark3(
    VOS_UINT8                          *pFddClassMark3
);

/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-21, end */
VOS_UINT32 NAS_MML_GetLaiIndexInRegFailForbLaList (
    NAS_MML_LAI_STRU                                       *pstLai,
    VOS_UINT8                                              *pucLaiIdx,
    VOS_UINT32                                              ulLaiNum,
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_STRU                 *pstRegFailForbLaList
);

VOS_VOID NAS_MML_AddCustomizedForbLaToDestLaList(
    VOS_UINT8                          *pucDestLaNum ,
    NAS_MML_LAI_STRU                   *pstDestLaList
);

VOS_UINT32 NAS_MML_IsInForbLaWithValidPeriodList(
    NAS_MML_LAI_STRU                    *pstLai
);

VOS_UINT32 NAS_MML_DeleteExpireValidPeriodPlmnInDisabledRatPlmnList(VOS_VOID);
VOS_VOID NAS_MML_DeleteSpecDisabledPlmnWithValidPeriodInPlmnList(
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstPlmnWithRat
);
VOS_UINT32 NAS_MML_GetPlmnWithRatIndexInDestDisabledPlmnWithForbiddenPeriodList (
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstSrcPlmnId,
    VOS_UINT32                                              ulDestPlmnNum,
    NAS_MML_DISABLED_PLMN_WITH_FORBIDDEN_PERIOD_STRU       *pstDestPlmnIdList
);
VOS_UINT32 NAS_MML_IsNeedAddVoiceNotAvailDisabledPlmnInDisabledPlmnWithForbiddenPeriodList(
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstPlmnWithRat,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enCsRegCause,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enPsRegCause,
    NAS_MML_ADDITION_UPDATE_RSLT_INFO_ENUM_UINT8            enAdditionUpdatRsltInfo
);

VOS_UINT32 NAS_MML_GetDisabledPlmnRejCause42ForbiddenTimeSlice(VOS_VOID);

VOS_UINT32 NAS_MML_GetVoiceNotPreferDisabledPlmnForbiddenTimeSlice(VOS_VOID);

/* Added by n00355355 for 呼叫重建, 2015-9-24, begin */
VOS_VOID NAS_MML_GetMmlCsTransactionStatus(
    NAS_MML_CS_TRANSACTION_ENUM_UINT8                        *penAsCsTransactionsStatus
);

/* Added by n00355355 for 呼叫重建, 2015-9-24, end */

VOS_VOID NAS_MML_DelEqualPlmnsInDisableRatList(
    VOS_UINT8                                              *pucEPlmnNum,
    NAS_MML_PLMN_ID_STRU                                   *pstEPlmnList,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enSpecRat,
    VOS_UINT32                                              ulDisabledRatPlmnNum,
    NAS_MML_DISABLED_PLMN_WITH_FORBIDDEN_PERIOD_STRU       *pstDisabledRatPlmnIdList
);
VOS_UINT32 NAS_MML_IsPlmnIdWithRatInDestDisabledPlmnWithForbiddenPeriodList (
    NAS_MML_PLMN_WITH_RAT_STRU         *pstSrcPlmnId
);



VOS_UINT32 NAS_MML_IsPlmnIdWithRatInDestDisabledPlmnRatList (
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstSrcPlmnId,
    VOS_UINT32                                              ulDestPlmnNum,
    NAS_MML_DISABLED_PLMN_WITH_FORBIDDEN_PERIOD_STRU       *pstDestPlmnIdList
);


VOS_VOID NAS_MML_DelEqualPlmnNotInAllowLteRoamMccList(
    VOS_UINT8                          *pucEPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pstEPlmnList,
    VOS_UINT32                          ulAllowLteRoamMccNum,
    VOS_UINT32                         *pulAllowLteRoamMccList
);
VOS_VOID NAS_MMC_DelDuplicatedPlmnInPlmnList(
    VOS_UINT8                          *pucPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pstPlmnList
);
VOS_VOID NAS_MML_DelForbPlmnInPlmnList(
    VOS_UINT8                          *pucPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pstPlmnList
);
/* Added by s00217060 for VoLTE_PhaseIII  项目, 2013-12-24, end */

/*****************************************************************************
 函 数 名  : NAS_MML_GetCsOnlyDataServiceSupportFlg
 功能描述  : 获取CS ONLY配置下，是否允许发起PS业务的标志
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE 允许发起PS 业务，VOS_FALSE 不允许发起PS 业务
 调用函数  :
 被调函数  :

 修改历史      :
    1.日    期   : 2014年02月13日
      作    者   : f62575
      修改内容   : DTS2014012902032
*****************************************************************************/
VOS_UINT32 NAS_MML_GetCsOnlyDataServiceSupportFlg(VOS_VOID);

VOS_UINT32 NAS_MML_IsPlmnListSrchRslt(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    VOS_UINT32                          enPlmnSrchRslt
);

VOS_UINT32 NAS_MML_IsGetGeoPlmnSrchRslt(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    VOS_UINT32                          enPlmnSrchRslt
);

VOS_UINT32 NAS_MML_IsPrefBandPlmnSrchRslt(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    VOS_UINT32                          enPlmnSrchRslt
);

/* Added by w00176964 for V3R3C60_eCall项目, 2014-4-28, begin */
VOS_UINT32 NAS_MML_IsCampLaiInfoChanged( VOS_VOID );
/* Added by w00176964 for V3R3C60_eCall项目, 2014-4-28, end */

VOS_UINT8 NAS_MML_IsUeSupportIms(VOS_VOID);
VOS_UINT8 NAS_MML_GetMoCallSetupFlg(VOS_VOID);
VOS_UINT8 NAS_MML_GetMoSsSetupFlg(VOS_VOID);
VOS_UINT8 NAS_MML_GetCmServiceSetupFlg( VOS_VOID );
VOS_UINT8 NAS_MML_IsNeedUpdateCallStatusToStart(
    NAS_MML_MO_CALL_STATUS_ENUM_UINT8   enOldCallStatus
);
VOS_UINT32 NAS_MML_Is3Gpp2Rat(
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8            enRatType
);

#if (FEATURE_ON == FEATURE_LTE)
extern VOS_UINT32 NAS_MML_IsImsiInLteOos2GPrefPlmnSelCfg(VOS_VOID);
extern VOS_UINT32 NAS_MML_IsNeedSortRatPrioForLteOos2GPrefPlmnSel(
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList
);
extern VOS_UINT32 NAS_MML_IsLastCampedPlmnIdRoam(VOS_VOID);
#endif

VOS_UINT32 NAS_MML_IsGULModeConfigured(VOS_VOID);

VOS_UINT32 NAS_MML_IsCLModeSupportedInRatList(
    NAS_MSCC_PIF_RAT_PRIO_STRU         *pstRatPrioList
);

VOS_VOID NAS_MML_GetNewRatFromRatList(
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstOriRatList,
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstNewRatList,
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstOutputRatList
);

/*****************************************************************************
 函 数 名  : NAS_MML_GetSmsFilterFlg
 功能描述  : 提供给接入层获取过滤功能是否打开的Nv
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE: 需要进行过滤
             VOS_FALSE:不需要进行过滤
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月17日
    作    者   : h00313353
    修改内容   : 新生成函数
*****************************************************************************/
extern VOS_UINT32 NAS_MML_GetSmsFilterFlg( VOS_VOID );

extern VOS_UINT8 NAS_MML_GetCsfbMoCallSetupFlg(VOS_VOID);

extern VOS_UINT8 NAS_MML_GetCsfbMoSsSetupFlg(VOS_VOID);

extern VOS_VOID NAS_MML_SetCsfbMtPagingTimerStatus(
    NAS_MML_MT_CSFB_PAGING_TIMER_STATUS_ENUM_UINT8  enStatus
);

extern NAS_MML_MT_CSFB_PAGING_TIMER_STATUS_ENUM_UINT8 NAS_MML_GetCsfbMtPagingTimerStatus(VOS_VOID);

extern VOS_UINT8 NAS_MML_GetCsfbMoSetupFlg(VOS_VOID);

VOS_UINT32 NAS_MML_IsPidUnderGunas(
    VOS_UINT32                          ulPid
);

VOS_UINT32 NAS_MML_IsNeedDiscardMsg(
    VOS_UINT32                          ulSenderPid,
    VOS_UINT32                          ulReceiverPid,
    VOS_UINT32                          ulMsgName
);


VOS_UINT32 NAS_MML_IsCurrGURatMode(VOS_VOID);

VOS_UINT32 NAS_MML_IsNeedTriggerPlmnSearchWhenRemoveCustomizedFrobLa(VOS_VOID);

VOS_VOID NAS_MML_StartCustomizedForbLaTimer(VOS_VOID);

VOS_UINT16 NAS_MML_GetForbLaWithValidPeriodTimerLen(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enRegFailCause,
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_CFG_INFO_LIST_STRU   *pstForbLaWithValidPeriodCfg
);

VOS_UINT32 NAS_MML_IsCustomizedForbLaTimerExpired(
    VOS_UINT32                                              ulDuration,
    VOS_UINT32                                              ulPeriod
);

VOS_UINT16 NAS_MML_GetCustomizedForbLaPunishTimeLen(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16                      enRegFailCause,
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_CFG_INFO_LIST_STRU   *pstForbLaWithValidPeriodCfg
);

VOS_UINT32 NAS_MMC_GetCustomizedForbLaLeftTimeLen(
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_STRU       *pstLaWithValidPeriod
);

VOS_UINT32 NAS_MML_CompareLac(
    NAS_MML_LAI_STRU                    *pstCurLai,
    NAS_MML_LAI_STRU                    *pstOldLai
);

VOS_VOID NAS_MML_DeleteLaFromForbLaWithValidPeriodList(
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_LIST_STRU            *pstForbLaWithValidPeriod,
    VOS_UINT32                                              ulIndex
);

VOS_UINT32 NAS_MML_IsNeedProtectionBeforeDeleteCustomizedForbLa(
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_LIST_STRU            *pstForbLaWithValidPeriod,
    VOS_UINT32                                              ulIndex
);

VOS_UINT32 NAS_MML_DeleteExpiredLaFromForbLaWithValidPeriodList(
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_LIST_STRU            *pstForbLaWithValidPeriod
);

VOS_UINT32 NAS_MML_GetLaiIndexInForbLaWithValidPeriodList(
    NAS_MML_LAI_STRU                                       *pstCurrCampLai,
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_LIST_STRU            *pstForbLaWithValidPeriod
);

VOS_UINT32 NAS_MML_AddCsRegFailLaIntoForbLaListWithValidPeriod(
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_CFG_INFO_STRU        *pstForbLaWithValidPeriodCfgInfo
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

#endif /* end of NasMmlLib.h */
