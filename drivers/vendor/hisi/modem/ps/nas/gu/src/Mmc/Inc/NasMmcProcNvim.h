/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcProcNvim.h
  版 本 号   : 初稿
  作    者   : z00161729
  生成日期   : 2011年7月14日
  最近修改   :
  功能描述   : NasMmcProcNvim.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年7月14日
    作    者   : z00161729
    修改内容   : 创建文件
  2.日    期   : 2012年03月15日
    作    者   : l00130025
    修改内容   : DTS2012021407803,Eplmn维护修改，删除GMM/MM/MMC关于NVIM_EPLMN的冗余定义
******************************************************************************/
#ifndef _NAS_MMC_PROC_NVIM_H
#define _NAS_MMC_PROC_NVIM_H

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "NasMmlCtx.h"
#include  "NasMmcCtx.h"
#include  "NVIM_Interface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define NAS_MMC_NV_ITEM_ACTIVE          (1)                                     /* NV项激活 */
#define NAS_MMC_NV_ITEM_DEACTIVE        (0)                                     /* NV项未激活 */

/* GPRS GEA 算法支持宏定义 */
#define NAS_MMC_GPRS_GEA1_SUPPORT       (0x01)                                  /* 支持GPRS GEA1算法 */
#define NAS_MMC_GPRS_GEA1_VALUE         (0x80)                                  /* 支持GEA1时的网络能力值 */
#define NAS_MMC_GPRS_GEA2_VALUE         (0x40)                                  /* 支持GEA2时的网络能力值 */
#define NAS_MMC_GPRS_GEA3_VALUE         (0x20)                                  /* 支持GEA3时的网络能力值 */
#define NAS_MMC_GPRS_GEA4_VALUE         (0x10)                                  /* 支持GEA4时的网络能力值 */
#define NAS_MMC_GPRS_GEA5_VALUE         (0x08)                                  /* 支持GEA5时的网络能力值 */
#define NAS_MMC_GPRS_GEA6_VALUE         (0x04)                                  /* 支持GEA6时的网络能力值 */
#define NAS_MMC_GPRS_GEA7_VALUE         (0x02)                                  /* 支持GEA7时的网络能力值 */

#define NAS_MMC_GPRS_GEA2_SUPPORT       (0x02)                                  /* 支持GPRS GEA2算法 */
#define NAS_MMC_GPRS_GEA3_SUPPORT       (0x04)                                  /* 支持GPRS GEA3算法 */
#define NAS_MMC_GPRS_GEA4_SUPPORT       (0x08)                                  /* 支持GPRS GEA4算法 */
#define NAS_MMC_GPRS_GEA5_SUPPORT       (0x10)                                  /* 支持GPRS GEA5算法 */
#define NAS_MMC_GPRS_GEA6_SUPPORT       (0x20)                                  /* 支持GPRS GEA6算法 */
#define NAS_MMC_GPRS_GEA7_SUPPORT       (0x40)                                  /* 支持GPRS GEA7算法 */
#define NAS_MMC_NVIM_MAX_EPLMN_NUM      (16)                                    /* en_NV_Item_EquivalentPlmn NV中等效plmn个数 */
#define NAS_MMC_NVIM_MAX_MCC_SIZE       (3)                                     /* plmn中Mcc最大长度 */
#define NAS_MMC_NVIM_MAX_MNC_SIZE       (3)                                     /* plmn中Mnc最大长度 */
#define NAS_MMC_LOW_BYTE_MASK           (0x0f)

#define NAS_MMC_MAX_USER_CFG_IMSI_PLMN_NUM                  (6)                 /* 用户配置的最多可支持的USIM/SIM卡的个数 */
#define NAS_MMC_MAX_USER_CFG_EHPLMN_NUM                     (6)                 /* 用户配置的EHplmn的个数 */
#define NAS_MMC_MAX_BLACK_LOCK_PLMN_WITH_RAT_NUM            (8)                 /* 禁止接入技术的PLMN ID的最大个数 */

#define NAS_MMC_CMCC_PLMN_LIST                              (4)
#define NAS_MMC_UNICOM_PLMN_LIST                            (3)
#define NAS_MMC_CT_PLMN_LIST                                (2)

#define NAS_MCC_NVIM_PHASE_ONE_DEFUALT_SLEEP_TIME_LEN               (1)
#define NAS_MCC_NVIM_PHASE_TWO_DEFAULT_SLEEP_TIME_LEN               (40)
#define NAS_MCC_NVIM_PHASE_ONE_DEFAULT_FULL_BAND_NUM                (1)
#define NAS_MCC_NVIM_PHASE_TWO_DEFAULT_FULL_BAND_NUM                (1)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
enum NAS_MMC_HPLMN_TYPE_ENUM
{
    NAS_MMC_HPLMN_TYPE_CMCC                     = 0,            /*中国移动*/
    NAS_MMC_HPLMN_TYPE_UNICOM                   = 1,            /* 中国联通 */
    NAS_MMC_HPLMN_TYPE_CT                       = 2,            /* 中国电信*/
    NAS_MMC_HPLMN_TYPE_BUTT
};
typedef VOS_UINT8 NAS_MMC_HPLMN_TYPE_ENUM_UINT8;


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
VOS_VOID NAS_MMC_ReadImeisvNvim( VOS_VOID );

VOS_VOID NAS_MMC_ReadLauRejTrigPlmnSearchNvim( VOS_VOID );
VOS_VOID NAS_MMC_ReadLauRejNeedNoRetryWhenCmSrvExistNvim( VOS_VOID );
VOS_VOID NAS_MMC_ReadRoamingRejectNoRetryFlgNvim( VOS_VOID );
VOS_VOID NAS_MMC_ReadSupported3GppReleaseNvim(VOS_VOID);
VOS_VOID NAS_MMC_ReadClassMark1Nvim(VOS_VOID);
VOS_VOID NAS_MMC_ReadClassMark2Nvim(VOS_VOID);
VOS_VOID NAS_MMC_ReadNetworkCapabilityNvim(VOS_VOID);
VOS_VOID  NAS_MMC_ReadMsModeNvim( VOS_VOID );

VOS_VOID NAS_MMC_UpdateNetworkCapabilityGeaValue(VOS_VOID);

VOS_VOID NAS_MMC_ReadUseSingleRplmnFlagNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadRplmnWithRatNvim(VOS_VOID);
VOS_VOID NAS_MMC_ReadNvimLastRplmnRat(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8    *penNvimLastRplmnRat
);

VOS_VOID NAS_MMC_WriteRplmnWithRatNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadEHPlmnSupportNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadUserSetBandNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadSearchHPlmnFlgAutoModeNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadAddEhplmnWhenSrchHplmnNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadSearchHPlmnFlgManualModeNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadSearchHplmnFlgPowerOnNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadEnhancedHPlmnSearchFlagNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadSpecialRoamFlgNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadNetworkNameNvim(VOS_VOID);

VOS_VOID NAS_MMC_WriteEplmnNvim(VOS_VOID);


VOS_VOID NAS_MMC_DeleteEPlmnList( VOS_VOID );


VOS_VOID NAS_MMC_ReadHplmnFirstSearchPeriodNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadDefaultHplmnSrchPeriodNvim(VOS_VOID);

/* Added by c00318887 for file refresh需要触发背景搜, 2015-4-28, begin */
VOS_VOID NAS_MMC_ReadHighPrioPlmnRefreshTriggerBGSearchFlagNvim(VOS_VOID);
/* Added by c00318887 for file refresh需要触发背景搜, 2015-4-28, end */

VOS_VOID NAS_MMC_ReadSrchHplmnTtimerValueNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadWhiteOpeLockPlmnInfoNvim( VOS_VOID );

VOS_VOID NAS_MMC_ReadBlackOperLockPlmnInfoNvim( VOS_VOID );

VOS_VOID NAS_MMC_ReadUserCfgExtEhplmnInfoNvim( VOS_VOID );
VOS_VOID NAS_MMC_ReadDisabledRatPlmnInfoNvim( VOS_VOID );



VOS_UINT8 NAS_MMC_IsRatForbiddenListNvimValid(
    NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_STRU *pstParaValue
);

VOS_VOID NAS_MMC_ReadRatForbiddenListConfigNvim( VOS_VOID );

VOS_UINT32 NAS_MMC_ConvertNvimRatToMmlType(
    NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_ENUM_UINT8            enNvRatType,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                        *penMmlRatType
);



VOS_VOID NAS_MMC_ReadStandardSTKSteeringOfRoamingFlgNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadCsRejSearchSupportFlagNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadAutoAttachNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadPlmnSelectionModeNvim(VOS_VOID);

VOS_VOID NAS_MMC_WritePlmnSelectionModeNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadEquivalentPlmnNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadMaxForbRoamLaNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadGsmForbidAccessInfoNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadRoamBrokerRegisterFailCntNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadPsLociNvim(VOS_VOID);

VOS_VOID NAS_MMC_WritePsLociNvim(
    VOS_UINT8                          *pstPsLocInfo,
    VOS_UINT32                          ulSize
);
VOS_VOID NAS_MMC_ReadRoamCfgInfoNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadDtSingleDomainPlmnSearchNvim(VOS_VOID);

VOS_VOID  NAS_MMC_ReadLastImsiNvim( VOS_VOID );

VOS_VOID NAS_MMC_UpdateLastImsi( VOS_VOID );

#if   (FEATURE_ON == FEATURE_LTE)

VOS_VOID NAS_MMC_ReadTinInfoNvim(VOS_VOID);

VOS_VOID  NAS_MMC_WriteTinInfoNvim(
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType,
    VOS_UINT8                          *pucImsi
);

VOS_VOID NAS_MMC_ReadLteCsServiceConfigNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadHoWaitSysinfoTimeLenNvim(VOS_VOID);

VOS_VOID  NAS_MMC_ReadLNasReleaseNvim(VOS_VOID);

#endif
/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-14, begin */
VOS_VOID NAS_MMC_ReadCsfbEmgCallLaiChgLauFirstNvim(VOS_VOID);
/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-14, end */

VOS_VOID NAS_MMC_ReadLteRoamConfigNvim(VOS_VOID);
VOS_VOID NAS_MMC_ReadDailRejectConfigNvim(VOS_VOID);
VOS_VOID NAS_MMC_ReaducWcdmaPriorityGsmNvim(VOS_VOID);
VOS_VOID NAS_MMC_ReadPsOnlyCsServiceSupportNvim(VOS_VOID);
VOS_VOID NAS_MMC_ReadAPPConfigSupportNvim(VOS_VOID);

/* Modified by z40661 for 泰国AIS特性 2012-05-17, begin */

VOS_VOID NAS_MMC_ReadAisRoamingNvim( VOS_VOID  );

/* Modified by z40661 for 泰国AIS特性 2012-05-17, end */


VOS_VOID NAS_MMC_ReadUserAutoReselCfgNvim(VOS_VOID);


VOS_VOID NAS_MMC_ReadScanCtrlNvim(VOS_VOID);


VOS_VOID NAS_MMC_ReadPrioHplmnActCfgNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadHPlmnSearchRegardLessMccNvim(VOS_VOID);
VOS_VOID NAS_MMC_ReadSingleDomainFailActionListNvim(VOS_VOID);
VOS_VOID NAS_MMC_ReadRegFailNetWorkFailureCustomFlagNvim(VOS_VOID);
VOS_VOID NAS_MMC_ReadActingHPlmnSupportNvim(VOS_VOID);

/* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-13, begin */
VOS_VOID NAS_MMC_ReadPlmnExactlyCompareNvim(VOS_VOID);
/* Added by t00212959 for DCM定制需求和遗留问题, 2012-8-13, end */

VOS_VOID NAS_MMC_ReadCustomizeServiceNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadHplmnRegisterCtrlNvim(VOS_VOID);
VOS_VOID NAS_MMC_ReadCellSignReportCfgNvim( VOS_VOID );

VOS_VOID NAS_MMC_WriteCellSignReportCfgNvim(VOS_UINT8 ucSignThreshold, VOS_UINT8 ucMinRptTimerInterval);


VOS_VOID NAS_MMC_ReadPlatformRatCapNvim( VOS_VOID );
VOS_UINT32 NAS_MMC_IsPlatformRatCapNvimValid(
    PLATAFORM_RAT_CAPABILITY_STRU              *pstNvPlatformRatCap
);
VOS_UINT32 NAS_MMC_ConvertNvimTypePlatformRatCapToNasType(
    PLATFORM_RAT_TYPE_ENUM_UINT16                       enNvPlatformRatCap,
    NAS_MML_PLATFORM_RAT_TYPE_ENUM_UINT8               *penNasPlatformRatCap
);

/* Added by w00176964 for 短信支持能力和UC2能力NV优化, 2013-3-11, begin */
VOS_VOID NAS_MMC_ReadUcs2CustomizationNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadCloseSmsCapabilityConfigNvim(VOS_VOID);
/* Added by w00176964 for 短信支持能力和UC2能力NV优化, 2013-3-11, end */

VOS_VOID NAS_MMC_ReadH3gCtrlNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadSvlteSupportFlagNvim( VOS_VOID );

VOS_VOID NAS_MMC_ReadPsTransferCfgNvim( VOS_VOID );

VOS_VOID NAS_MMC_ReadDamCfgNvim(VOS_VOID);

#if  (FEATURE_ON == FEATURE_LTE)
VOS_VOID NAS_MMC_ReadEnableLteTimerLenNvim(VOS_VOID);

/* Added by c00318887 for 移植T3402 , 2015-6-17, begin */
VOS_VOID NAS_MMC_ReadDisableLteStartT3402EnableLteCfgNvim(VOS_VOID);
/* Added by c00318887 for 移植T3402 , 2015-6-17, end */

VOS_VOID NAS_MMC_ReadCsfbRauFollowOnFlgNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadLteCustomMccInfoNvim(VOS_VOID);

#if (FEATURE_ON == FEATURE_CSG)
VOS_VOID NAS_MMC_ReadCsgCfgNvim(VOS_VOID);
#endif
#endif
VOS_VOID  NAS_MMC_ReadIsrSupportNvim( VOS_VOID );

VOS_VOID NAS_MMC_ReadRefreshRplmnWhenEplmnInvalidCfgNvim(VOS_VOID);

#if (FEATURE_ON == FEATURE_PTM)
VOS_VOID NAS_MMC_ReadErrlogCtrlInfoNvim(VOS_VOID);
VOS_VOID NAS_MMC_ReadErrlogNwSrchRecordcfgNvim(VOS_VOID);
#endif


VOS_VOID NAS_MMC_ReadDsdaPlmnSearchEnhancedCfgNvim(VOS_VOID);


VOS_VOID NAS_MMC_ReadRoamPlmnSelectionSortCfgNvim(VOS_VOID);


VOS_VOID NAS_MMC_ReadNonOosPlmnSearchFeatureSupportCfgNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadOosPlmnSearchStrategyCfgNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadGetGeoCfgInfoNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadUserCfgOPlmnInfoNvim(VOS_VOID);
VOS_VOID NAS_MMC_ReadAccBarPlmnSearchNvim(VOS_VOID);

#if (FEATURE_ON == FEATURE_DSDS)
VOS_VOID NAS_MMC_ReadModemRfShareCfgNvim(VOS_VOID);
VOS_VOID NAS_MMC_ReadDsdsEndSessionDelayNvim(VOS_VOID);
#endif

VOS_VOID NAS_MMC_ReadUmtsCodecTypeNvim(VOS_VOID);
VOS_VOID NAS_MMC_ReadMedCodecTypeNvim(VOS_VOID);


VOS_VOID NAS_MMC_ReadWgRfMainBandNvim( VOS_VOID );

VOS_VOID NAS_MMC_ReadImsVoiceMMEnableNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadLcCtrlParaNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadLteDisabledUseLteInfoFlagNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadCsOnlyDataServiceSupportNvim( VOS_VOID );

VOS_VOID NAS_MMC_ReadIgnoreAuthRejFlgNvim(VOS_VOID);
VOS_VOID NAS_MMC_ReadHighPrioRatHplmnTimerCfgNvim( VOS_VOID  );
VOS_VOID NAS_MMC_ReadSBMCustomDualIMSIConfigNvim(VOS_VOID);
VOS_VOID NAS_MMC_ReadRPLMNConfigNvim(VOS_VOID);
#if  (FEATURE_ON == FEATURE_LTE)
VOS_VOID NAS_MMC_ReadUltraFlashCsfbSupportFlgNvim(VOS_VOID);
VOS_VOID NAS_MMC_ReadSrvccSupportFlgNvim(VOS_VOID);
#endif

VOS_VOID NAS_MMC_Read3GPP2UplmnNotPrefFlgNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadSyscfgTriPlmnSrchCfgNvim(VOS_VOID);

VOS_VOID  NAS_MMC_ReadDplmnNplmnInfoNvim(VOS_VOID);
VOS_VOID NAS_MMC_WriteSelfLearnDplmnNplmnToNvim(
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo
);

VOS_VOID NAS_MMC_WriteApPresetAndSelfLearnDplmnNplmnToNvim(
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo
);

VOS_VOID NAS_MMC_ReadDplmnNplmnCfgNvim(
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo
);

VOS_VOID NAS_MMC_ReadFirstPresetDplmnNplmnCfgNvim(VOS_VOID);
VOS_VOID NAS_MMC_ReadSecondPresetDplmnNplmnCfgNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadSelfLearnDplmnNplmnCfgNvim(
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                     *pstDPlmnNPlmnCfgInfo
);

VOS_VOID NAS_MMC_UpdateDplmnNplmnCfgNvim(
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo
);

VOS_VOID NAS_MMC_UpdateApPresetDplmnToFirstPresetDplmnNplmnCfgNvim(
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo
);

VOS_VOID NAS_MMC_UpdateApPresetDplmnToSecondPresetDplmnNplmnCfgNvim(
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo
);

VOS_VOID NAS_MMC_UpdateSelfLearnDplmnNplmnToSelfLearnDplmnNplmnCfgNvim(
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                      *pstDPlmnNPlmnCfgInfo
);

extern VOS_VOID  NAS_MMC_ReadChangeNwCauseCfgNvim(VOS_VOID );

extern VOS_VOID NAS_MMC_ReadRelPsSignalConCfgNvim(VOS_VOID);

#if  (FEATURE_ON == FEATURE_LTE)
extern VOS_VOID NAS_MMC_ReadLteRejCause14CfgNvim(VOS_VOID);
#endif

VOS_VOID NAS_MMC_ReadDsdsActiveModemModeNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadCsmoSupportedCfgNvim(VOS_VOID);

#if  (FEATURE_ON == FEATURE_IMS)
VOS_VOID NAS_MMC_ReadImsRatSupportNvim(VOS_VOID);
VOS_VOID NAS_MMC_ReadImsCapNvim(VOS_VOID);
VOS_VOID NAS_MMC_ReadUssdOnImsNvim(VOS_VOID);
#endif

VOS_VOID NAS_MMC_ReadT3212TimerCfgNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadPsRegFailMaxTimesTrigLauOnceFlgNvim(VOS_VOID);
VOS_VOID NAS_MMC_ReadKeepSrchHplmnEvenRejByCause13Nvim(VOS_VOID);
VOS_VOID NAS_MMC_ReadEpsRejByCause14InVplmnAllowPsRegFlgNvim(VOS_VOID);
VOS_VOID NAS_MMC_ReadCarryEplmnWhenSrchRplmnCfgNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadRoamDisplayCfgNvim(VOS_VOID);

#if (FEATURE_ON == FEATURE_LTE)
extern VOS_VOID NAS_MMC_ReadLteOos2GPrefPlmnSelCfgNvim(VOS_VOID);
#endif

VOS_VOID NAS_MMC_ReadProtectMtCsfbPagingProcedureLenNvim(VOS_VOID);

/* added by y00176023 for DTS2015091602371 澳电低优先级ANYCELL搜LTE定制, 2015-9-17, begin */
VOS_VOID NAS_MMC_ReadLowPrioAnycellsearchLteCfgNvim(VOS_VOID);
/* added by y00176023 for DTS2015091602371 澳电低优先级ANYCELL搜LTE定制, 2015-9-17, end */

VOS_VOID NAS_MMC_ReadCsRegFailForbLaTimeCfgNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadKeepCsForbInfoWhenPsRegSuccCfgNvim(VOS_VOID);

VOS_VOID NAS_MMC_ReadClearCksnCfgNvim(VOS_VOID);

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
