/******************************************************************************

                  版权所有 (C), 2001-2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafMmaProcNvim.h
  版 本 号   : 初稿
  作    者   : w00176964
  生成日期   : 2013年7月9日
  最近修改   :
  功能描述   : TafMmaProcNvim.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年7月9日
    作    者   : W00176964
    修改内容   : 创建文件
******************************************************************************/
#ifndef _TAF_MMA_PROC_NVIM_H
#define _TAF_MMA_PROC_NVIM_H

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "NVIM_Interface.h"
#include "MmaAppLocal.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define NAS_MSCC_NV_ITEM_ACTIVE          (1)                                     /* NV项激活 */
#define NAS_MSCC_NV_ITEM_DEACTIVE        (0)                                     /* NV项未激活 */

/* GPRS GEA 算法支持宏定义 */
#define NAS_MSCC_GPRS_GEA1_SUPPORT       (0x01)                                  /* 支持GPRS GEA1算法 */
#define NAS_MSCC_GPRS_GEA1_VALUE         (0x80)                                  /* 支持GEA1时的网络能力值 */
#define NAS_MSCC_GPRS_GEA2_VALUE         (0x40)                                  /* 支持GEA2时的网络能力值 */
#define NAS_MSCC_GPRS_GEA3_VALUE         (0x20)                                  /* 支持GEA3时的网络能力值 */
#define NAS_MSCC_GPRS_GEA4_VALUE         (0x10)                                  /* 支持GEA4时的网络能力值 */
#define NAS_MSCC_GPRS_GEA5_VALUE         (0x08)                                  /* 支持GEA5时的网络能力值 */
#define NAS_MSCC_GPRS_GEA6_VALUE         (0x04)                                  /* 支持GEA6时的网络能力值 */
#define NAS_MSCC_GPRS_GEA7_VALUE         (0x02)                                  /* 支持GEA7时的网络能力值 */

#define NAS_MSCC_GPRS_GEA2_SUPPORT       (0x02)                                  /* 支持GPRS GEA2算法 */
#define NAS_MSCC_GPRS_GEA3_SUPPORT       (0x04)                                  /* 支持GPRS GEA3算法 */
#define NAS_MSCC_GPRS_GEA4_SUPPORT       (0x08)                                  /* 支持GPRS GEA4算法 */
#define NAS_MSCC_GPRS_GEA5_SUPPORT       (0x10)                                  /* 支持GPRS GEA5算法 */
#define NAS_MSCC_GPRS_GEA6_SUPPORT       (0x20)                                  /* 支持GPRS GEA6算法 */
#define NAS_MSCC_GPRS_GEA7_SUPPORT       (0x40)                                  /* 支持GPRS GEA7算法 */
#define NAS_MSCC_NVIM_MAX_EPLMN_NUM      (16)                                    /* en_NV_Item_EquivalentPlmn NV中等效plmn个数 */
#define NAS_MSCC_NVIM_MAX_MCC_SIZE       (3)                                     /* plmn中Mcc最大长度 */
#define NAS_MSCC_NVIM_MAX_MNC_SIZE       (3)                                     /* plmn中Mnc最大长度 */
#define NAS_MSCC_LOW_BYTE_MASK           (0x0f)

#define NAS_MSCC_MAX_USER_CFG_IMSI_PLMN_NUM                  (6)                 /* 用户配置的最多可支持的USIM/SIM卡的个数 */
#define NAS_MSCC_MAX_USER_CFG_EHPLMN_NUM                     (6)                 /* 用户配置的EHplmn的个数 */
#define NAS_MSCC_MAX_BLACK_LOCK_PLMN_WITH_RAT_NUM            (8)                 /* 禁止接入技术的PLMN ID的最大个数 */

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
VOS_VOID TAF_MMA_ReadUeSupporttedGuBandNvim(VOS_VOID);
VOS_VOID TAF_MMA_ReadForbBandNvim(VOS_VOID);
VOS_UINT32  TAF_MMA_ReadFreqBandNvim(VOS_VOID);
#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID TAF_MMA_ReadNvimUeSupporttedLteBand(VOS_VOID);
VOS_VOID TAF_MMA_ReadUserSetLteBands(VOS_VOID);
#endif
VOS_VOID MMA_UpdateBandNvRefForbBand(VOS_VOID);
VOS_VOID MMA_UpdateForbBandStatusToNV(VOS_VOID);
VOS_VOID TAF_MMA_UpdateUeAllowedBandRange(VOS_VOID);
VOS_VOID TAF_MMA_ReadProductNameNvim(VOS_VOID);
VOS_VOID TAF_MMA_ReadFmridNvim(VOS_VOID);
VOS_VOID TAF_MMA_ReadImeiNvim(VOS_VOID);
VOS_VOID TAF_MMA_ReadSystemAppCofigNvim(VOS_VOID);
VOS_VOID TAF_MMA_ReadNotDisplayLocalNetworkNameNvim(VOS_VOID);
VOS_VOID TAF_MMA_ReadDisplaySpnFlagNvim(VOS_VOID);
VOS_VOID TAF_MMA_ReadEFustServiceCfgNvim(VOS_VOID);
VOS_VOID TAF_MMA_ReadRfAutoTestFlagNvim(VOS_VOID);
VOS_VOID TAF_MMA_ReadFollowonOpenSpeedFlagNvim(VOS_VOID);
VOS_VOID TAF_MMA_ReadUserSettedBandNvim(VOS_VOID);
VOS_VOID TAF_MMA_ReadAccessModeNvim(VOS_VOID);
VOS_VOID TAF_MMA_ReadReportPlmnSupportFlgNvim(VOS_VOID);
VOS_VOID TAF_MMA_ReadRoamingBrokerInfoNvim(VOS_VOID);
VOS_VOID TAF_MMA_ReadRoamCapaNvim(VOS_VOID);
VOS_VOID TAF_MMA_ReadMsClassNvim(VOS_VOID);
VOS_VOID TAF_MMA_ReadPlmnSelectionModeNvim(VOS_VOID);
VOS_UINT32 TAF_MMA_ReadAlphanumericNameByPlmnIdNvim( TAF_PH_OPERATOR_NAME_STRU   *pstOperName);
VOS_VOID TAF_MMA_ReadDeactUsimWhenPoweroffNvim(VOS_VOID);
VOS_VOID TAF_MMA_ReadSimPersonalisationPwdNvim( VOS_VOID );

/* Added by w00167002 for L-C互操作项目, 2014-2-14, begin */
VOS_VOID TAF_MMA_ReadLcCtrlNvim( VOS_VOID );
/* Added by w00167002 for L-C互操作项目, 2014-2-14, end */
VOS_VOID TAF_MMA_ReadUeSupporttedCPHSFlagNvim(VOS_VOID);
VOS_VOID  TAF_MMA_ReadPsStartNvim( VOS_VOID );
VOS_VOID  TAF_MMA_ReadCardLockStatusNvim( VOS_VOID );
VOS_VOID  TAF_MMA_ReadSimLockMaxTimesNvim( VOS_VOID );
VOS_VOID  TAF_MMA_ReadSimLockPlmnNvim( VOS_VOID );
VOS_UINT32  TAF_MMA_ReadLastImsiNvim(
    NAS_MMC_NVIM_LAST_IMSI_STRU        *pstLastImsi
);
#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32  TAF_MMA_ReadLastTinInfoNvim(
    NAS_NVIM_TIN_INFO_STRU             *pstTinInfo
);
#endif

VOS_VOID TAF_MMA_WritePlmnSelectionModeNvim(VOS_UINT8 ucReselMode);

VOS_VOID TAF_MMA_UpdateUeBandNvim(VOS_VOID);

#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID TAF_MMA_UpdateUserSetLteBands(VOS_VOID);
#endif

VOS_VOID TAF_MMA_ReadCFreqLockNvim(VOS_VOID);

VOS_VOID TAF_MMA_ReadPlatformRatCap(VOS_VOID);
VOS_VOID TAF_MMA_ReadCcpuResetRecordNvim(VOS_VOID);
VOS_VOID TAF_MMA_ReadGetGeoCfgInfoNvim(VOS_VOID);

#if (FEATURE_ON == FEATURE_IMS)
VOS_UINT32 TAF_MMA_UpdataVoiceDomainNv(
    VOS_UINT32                          ulVoiceDomain
);

VOS_UINT32 TAF_MMA_UpdateLteImsSupportNv(
    VOS_UINT8                           ucFlag
);
#endif


VOS_VOID TAF_MMA_ReadDelayReportServiceStatusCfgNvim(VOS_VOID);
VOS_VOID TAF_MMA_ReadUserCfgExtEhplmnInfoNvim(
    NAS_MMC_NVIM_USER_CFG_EXT_EHPLMN_INFO_STRU             *pstNvimCfgExtEhplmnInfo
);
VOS_VOID TAF_MMA_ReadDplmnNplmnCfgNvim(
    NAS_MMC_NVIM_DPLMN_NPLMN_CFG_STRU                      *pstNvimDPlmnNPlmnCfg
);
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_VOID TAF_MMA_ReadEsnFromNvim( VOS_VOID );
VOS_VOID TAF_MMA_ReadMeidFromNvim( VOS_VOID );
#endif

VOS_VOID TAF_MMA_ReadNonnormalRegStatusMergeCfgNvim( VOS_VOID );
/* Added by j00354216 for C模服务状态优化, 2015-9-30, begin */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_VOID TAF_MMA_ReadDelaySndCLServiceStatusTimeLenNvim(
    VOS_VOID
);

VOS_VOID TAF_MMA_ReadCLDelayReportSrvCfgNvim(VOS_VOID);
#endif
/* Added by j00354216 for C模服务状态优化, 2015-9-30, end */

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

