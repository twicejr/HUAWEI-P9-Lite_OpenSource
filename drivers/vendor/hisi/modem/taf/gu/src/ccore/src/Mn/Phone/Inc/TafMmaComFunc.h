/******************************************************************************

                  版权所有 (C), 2005-2015, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafMmaComFunc.h
  版 本 号   : 初稿
  作    者   : f00179208
  生成日期   : 2015年02月09日
  最近修改   :
  功能描述   : TafMmaComFunc.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年02月09日
    作    者   : f00179208
    修改内容   : 创建文件

******************************************************************************/

#ifndef __TAF_MMA_COM_FUNC_H__
#define __TAF_MMA_COM_FUNC_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "TafTypeDef.h"
#include "TafAppMma.h"
#include "TafSdcCtx.h"
#include "MmaMsccInterface.h"
#include "hsm_mma_pif.h"
#include "NasOmTrans.h"
#include "omnvinterface.h"
#include "TafMmaTimerMgmt.h"
#include "TafApsApi.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/

/* 封装OSA申请消息接口 */
#define TAF_MMA_ALLOC_MSG_WITH_HDR(ulMsgLen)\
            PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA, (ulMsgLen))

/* 封装OSA消息头 */
#define TAF_MMA_CFG_MSG_HDR(pstMsg, ulRecvPid, ulMsgId)\
           { \
            ((MSG_HEADER_STRU *)(pstMsg))->ulSenderCpuId   = VOS_LOCAL_CPUID;\
            ((MSG_HEADER_STRU *)(pstMsg))->ulSenderPid     = WUEPS_PID_MMA;\
            ((MSG_HEADER_STRU *)(pstMsg))->ulReceiverCpuId = VOS_LOCAL_CPUID;\
            ((MSG_HEADER_STRU *)(pstMsg))->ulReceiverPid   = (ulRecvPid);\
            ((MSG_HEADER_STRU *)(pstMsg))->ulMsgName       = (ulMsgId); \
           }

/* 封装OSA消息头(MMA内部消息) */
#define TAF_MMA_CFG_INTRA_MSG_HDR(pstMsg, ulMsgId)\
            TAF_MMA_CFG_MSG_HDR(pstMsg, WUEPS_PID_MMA, ulMsgId)

/* 获取OSA消息内容 */
#define TAF_MMA_GET_MSG_ENTITY(pstMsg)\
            ((VOS_VOID *)&(((MSG_HEADER_STRU *)(pstMsg))->ulMsgName))

/* 获取OSA消息长度 */
#define TAF_MMA_GET_MSG_LENGTH(pstMsg)\
            (((MSG_HEADER_STRU *)(pstMsg))->ulLength)

/* 封装OSA消息初始化消息内容接口 */
#define TAF_MMA_CLR_MSG_ENTITY(pstMsg)\
            PS_MEM_SET(TAF_MMA_GET_MSG_ENTITY(pstMsg), 0x0, TAF_MMA_GET_MSG_LENGTH(pstMsg))

/* 封装OSA发送消息接口 */
#define TAF_MMA_SEND_MSG(pstMsg)\
            PS_SEND_MSG(WUEPS_PID_MMA, pstMsg)

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#define TAF_MMA_SESSION_STATUS_MAP_TBL_PTR()           (g_astTafMmaSessionStatusMapTbl)
#define TAF_MMA_SESSION_STATUS_MAP_TBL_SIZE()          (sizeof(g_astTafMmaSessionStatusMapTbl)/sizeof(TAF_MMA_SESSION_STATUS_MAP_STRU))

#define TAF_MMA_CDMA_PHONE_MODE_MAP_TBL_PTR()           (g_astTafMmaCdmaPhoneModeMapTbl)
#define TAF_MMA_CDMA_PHONE_MODE_MAP_TBL_SIZE()          (sizeof(g_astTafMmaCdmaPhoneModeMapTbl)/sizeof(TAF_MMA_CDMA_PHONE_MODE_MAP_STRU))

#define TAF_MMA_SYS_MODE_MAP_TBL_PTR()           (g_astTafMmaSysModeMapTbl)
#define TAF_MMA_SYS_MODE_MAP_TBL_SIZE()          (sizeof(g_astTafMmaSysModeMapTbl)/sizeof(TAF_MMA_SYS_MODE_MAP_STRU))

#define TAF_MMA_SYS_SUBMODE_MAP_TBL_PTR()           (g_astTafMmaSysSubModeMapTbl)
#define TAF_MMA_SYS_SUBMODE_MAP_TBL_SIZE()          (sizeof(g_astTafMmaSysSubModeMapTbl)/sizeof(TAF_MMA_SYS_SUBMODE_MAP_STRU))

#define TAF_MMA_CONVERT_STR_TO_U32_MAX_LEN      (8)

#endif

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : TAF_MMA_RAT_SET_TYPE_ENUM
 枚举说明  : 定义RAT变化类型
 1.日    期   : 2015年04月10日
   作    者   : y00245242
   修改内容   : 新建
*****************************************************************************/
enum TAF_MMA_RAT_SET_TYPE_ENUM
{
    TAF_MMA_RAT_SET_L_ONLY,         /* RAT仅包含L */
    TAF_MMA_RAT_SET_GUL,            /* RAT至少包含G或U */
    TAF_MMA_RAT_SET_CL,             /* RAT至少包含1X或HRPD */

    TAF_MMA_RAT_SET_BUTT
};
typedef VOS_UINT8 TAF_MMA_RAT_SET_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : TAF_MMA_RAT_MODE_TYPE_ENUM_UINT8
 枚举说明  : 定义RAT变化类型
 1.日    期   : 2015年04月10日
   作    者   : y00245242
   修改内容   : 新建
*****************************************************************************/
enum TAF_MMA_RAT_MODE_TYPE_ENUM
{
    TAF_MMA_RAT_MODE_GUL_TO_GUL,
    TAF_MMA_RAT_MODE_GUL_TO_CL,
    TAF_MMA_RAT_MODE_CL_TO_GUL,
    TAF_MMA_RAT_MODE_CL_TO_CL,

    TAF_MMA_RAT_MODE_BUTT
};
typedef VOS_UINT8 TAF_MMA_RAT_MODE_TYPE_ENUM_UINT8;

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
 结构名  : TAF_MMA_SESSION_STATUS_MAP_STRU
 结构说明: CTTF的原因值与APS间的原因值转换表

 修改历史      :
  1.日    期   : 2015年05月26日
    作    者   : h00246512
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    NAS_OM_MMA_HRPD_SESSION_STATUS_ENUM_UINT8   enMmaSessionStatus;
    HSM_MMA_SESSION_STATUS_ENUM_UINT8           enHsmSessionStatus;
    VOS_UINT8                                   aucReserved[2];
} TAF_MMA_SESSION_STATUS_MAP_STRU;
/*****************************************************************************
 结构名  : TAF_MMA_CDMA_PHONE_MODE_MAP_STRU
 结构说明: taf 与 nas om的cdma phone mode转换表

 修改历史      :
  1.日    期   : 2015年05月26日
    作    者   : y00322978
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    NAS_OM_MMA_PHONE_MODE_ENUM_UINT8            enNasOmCdmaPhoneMode;
    TAF_SDC_PHONE_MODE_ENUM_UINT8               enTafCdmaPhoneMode;
    VOS_UINT8                                   aucReserved[2];
} TAF_MMA_CDMA_PHONE_MODE_MAP_STRU;
/*****************************************************************************
 结构名  : TAF_MMA_CDMA_SYS_MODE_MAP_STRU
 结构说明: taf 与 nas om的cdma sys mode转换表

 修改历史      :
  1.日    期   : 2015年05月26日
    作    者   : y00322978
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    NAS_OM_MMA_SYS_MODE_ENUM_UINT8             enNasOmCdmaSysMode;
    TAF_SDC_SYS_MODE_ENUM_UINT8               enTafCdmaSysMode;
    VOS_UINT8                                   aucReserved[2];
} TAF_MMA_SYS_MODE_MAP_STRU;
/*****************************************************************************
 结构名  : TAF_MMA_CDMA_SYS_MODE_MAP_STRU
 结构说明: taf 与 nas om的cdma sys mode转换表

 修改历史      :
  1.日    期   : 2015年05月26日
    作    者   : y00322978
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    NAS_OM_MMA_SYS_SUBMODE_ENUM_UINT8             enNasOmSysSubMode;
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8               enTafSysSubMode;
    VOS_UINT8                                   aucReserved[2];
} TAF_MMA_SYS_SUBMODE_MAP_STRU;
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

VOS_UINT32 TAF_MMA_UpdataVoiceDomain(
    TAF_SDC_VOICE_DOMAIN_ENUM_UINT32    enVoiceDomain
);

#if (FEATURE_IMS == FEATURE_ON)
VOS_UINT32 TAF_MMA_UpdateLteImsSupportFlag(
    VOS_UINT8                           ucFlag
);

VOS_VOID TAF_MMA_TransMsccImsStartResultToTafErrorCode(
    NAS_MSCC_PIF_IMS_START_RESULT_ENUM_UINT32               enResult,
    TAF_ERROR_CODE_ENUM_UINT32                             *penErrorCode
);

VOS_VOID TAF_MMA_TransMsccImsStopResultToTafErrorCode(
    NAS_MSCC_PIF_IMS_STOP_RESULT_ENUM_UINT32                enResult,
    TAF_ERROR_CODE_ENUM_UINT32                             *penErrorCode
);
#endif

VOS_UINT32 TAF_MMA_IsUserSettedSysCfgParaValid(
    TAF_MMA_SYS_CFG_PARA_STRU          *pstSysCfgPara
);

VOS_UINT32  TAF_MMA_IsUserSettedGuBandValid(
    TAF_USER_SET_PREF_BAND64           *pstGuBand
);
#if(FEATURE_ON == FEATURE_LTE)
VOS_UINT32  TAF_MMA_IsUserSettedLBandValid(
    TAF_USER_SET_PREF_BAND64           *pstLBand
);
#endif

#if (FEATURE_ON == FEATURE_PTM)
VOS_VOID TAF_MMA_RatFrequentlySwitchRecord(VOS_VOID);

VOS_VOID TAF_MMA_ReportErrlogOosBegin(
    NAS_ERR_LOG_OOS_CAUSE_ENUM_UINT32   enOosCause,
    NAS_ERR_LOG_OOS_DOMAIN_ENUM_UINT32  enLostDomain
);
VOS_VOID TAF_MMA_ReportErrlogOosEnd(
    NAS_ERR_LOG_OOS_DOMAIN_ENUM_UINT32  enResumeDomain
);
VOS_VOID TAF_MMA_ProcErrlogDomainOosReport(
    TAF_SDC_REG_STATUS_ENUM_UINT8       enOldRegState,
    NAS_MSCC_PIF_REG_STATE_ENUM_UINT8   enNewRegState,
    VOS_UINT32                          ulOosCause,
    NAS_ERR_LOG_OOS_DOMAIN_ENUM_UINT32  enOosDomain
);
VOS_VOID TAF_MMA_ProcErrlogOosReport(
    TAF_SDC_REG_STATUS_ENUM_UINT8       enOldCsRegState,
    TAF_SDC_REG_STATUS_ENUM_UINT8       enOldPsRegState,
    MSCC_MMA_SERVICE_STATUS_IND_STRU   *pstServiceStatus
);
#endif

VOS_VOID TAF_MMA_RecordRegStatusReportFlag(
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32  enCnDomainId,
    NAS_MSCC_PIF_REG_STATE_ENUM_UINT8   enRegState
);
VOS_UINT32 TAF_MMA_IsUsimServiceAvailable(VOS_VOID);

/* 修改函数名 */
VOS_VOID TAF_MMA_UpdateGeoPlmnIdInfo(
    TAF_SDC_PLMN_ID_STRU               *pstPlmnId
);

VOS_VOID TAF_MMA_SetAttachAllowFlg(
    TAF_MMA_ATTACH_TYPE_ENUM_UINT8     ulAttachType
);

VOS_UINT32 TAF_MMA_IsRatOrderChange(
    TAF_MMA_RAT_ORDER_STRU             *pstCurrRat,
    TAF_MMA_RAT_ORDER_STRU             *pstLastRat
);
VOS_UINT32 TAF_MMA_GetSysCfgRatFlag(
    TAF_MMA_RAT_ORDER_STRU             *pstRatOrder,
    VOS_UINT32                         *pulRatExistedFlg
);
VOS_VOID TAF_MMA_GetValidUserCfgEhplmnInfo(
    VOS_UINT8                                               ucHplmnMncLen,
    VOS_UINT8                                              *pucImsi,
    VOS_UINT8                                              *pucEhplmnListNum,
    TAF_SDC_PLMN_ID_STRU                                   *pstEhPlmnList,
    NAS_MMC_NVIM_USER_CFG_EXT_EHPLMN_INFO_STRU             *pstNvimCfgExtEhplmnInfo
);
VOS_VOID TAF_MMA_MapCdmaNetworkExistanceSrvStaToSysMode(
    TAF_SDC_NETWORK_EXISTANCE_ENUM_UINT32                   enCdmaNetworkExist,
    TAF_SDC_SYS_MODE_ENUM_UINT8                            *penOutSysMode,
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8                         *penOutSubMode,
    pTafSdcSysmodServiceRegStaUpdateFunc                   *ppTafSdcSysmodServiceRegStaUpdateFunc
);

VOS_VOID TAF_MMA_UpdateSerRegSta_HrpdToNone(
    TAF_SDC_SRV_REG_INFO_STRU          *pstSrvInfo
);

VOS_VOID TAT_MMA_UpdateSerRegSta_HybridTo1x(
    TAF_SDC_SRV_REG_INFO_STRU          *pstSrvInfo
);

VOS_VOID TAF_MMA_UpdateSerRegSta_1xToNone(
    TAF_SDC_SRV_REG_INFO_STRU          *pstSrvInfo
);

VOS_VOID TAF_MMA_UpdateSerRegSta_HybridToHrpd(
    TAF_SDC_SRV_REG_INFO_STRU          *pstSrvInfo
);

VOS_VOID TAF_MMA_UpdateSerRegSta_SvlteToLte(
    TAF_SDC_SRV_REG_INFO_STRU          *pstSrvInfo
);

VOS_VOID TAF_MMA_UpdateSerRegSta_LteToNone(
    TAF_SDC_SRV_REG_INFO_STRU          *pstSrvInfo
);

VOS_VOID TAF_MMA_UpdateSerRegSta_SvlteTo1x(
    TAF_SDC_SRV_REG_INFO_STRU          *pstSrvInfo
);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_VOID TAF_MMA_ChgSysModeAndSrvRegSta(
    TAF_PH_ACCESS_TECH_ENUM_UINT8                           enAct,
    TAF_SDC_SYS_MODE_ENUM_UINT8                             enSysMode,
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8                          enSubMode,
    pTafSdcSysmodServiceRegStaUpdateFunc                    pFuncTafSdcSysmodServiceRegStaUpdate
);

VOS_UINT8 TAF_MMA_MapHsmSessionStatus(
    HSM_MMA_SESSION_STATUS_ENUM_UINT8   enSessionStatus
);
VOS_UINT32 TAF_MMA_QryCdmaStatusInfo(
    NAS_OM_MMA_CDMA_STATUS_COMMON_INFO_STRU                *pstCdmaCommInfo,
    NAS_OM_MMA_1X_SYS_INFO_STRU                            *pst1xSysInfo,
    NAS_OM_MMA_HRPD_SYS_INFO_STRU                          *pstHrpdSysInfo
);
VOS_UINT8 TAF_MMA_MapSysMode(
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode
);
VOS_UINT8 TAF_MMA_MapCdmaPhoneMode(
    TAF_SDC_PHONE_MODE_ENUM_UINT8       enPhoneMode
);
VOS_VOID TAF_MMA_ConvertMeidToUl(
    VOS_UINT8                          *pucMeid,
    VOS_UINT32                         *pMeid,
    VOS_UINT32                         *pMeidCnt
);
VOS_UINT32 TAF_MMA_ConvertUatiToUl(
    VOS_UINT8                          *pstUati
);
VOS_UINT8 TAF_MMA_IsMeidValid(
    NV_MEID_STRU                       *pstMeid
);
VOS_UINT8 TAF_MMA_IsPesnValid(
    NV_PESN_STRU                       *pstPesn
);
VOS_UINT8 TAF_MMA_IsUIMIDValid(
    VOS_UINT8                          *pucEFRUIMID
);
MODEM_ID_ASN_ENUM_UINT16 TAF_MMA_MapModemId(
    MODEM_ID_ENUM_UINT16                enModemId
);
VOS_UINT8 TAF_MMA_MapCdataBearStatus(
    TAF_PS_CDATA_BEAR_STATUS_ENUM_UINT8                     enBearStatus
);
#endif



VOS_UINT8 TAF_MMA_IsSameAsAppServiceStatus(
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enServiceStatus,
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32  enCnDomainId
);
VOS_VOID TAF_MMA_UpdateAppSrvStatusInfo(
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32  enCnDomainId
);

VOS_VOID TAF_MMA_UpdateAppRegStatusInfo(
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32  enCnDomainId
);
VOS_VOID TAF_MMA_UpdateAppNetworkInfo(VOS_VOID);
VOS_VOID TAF_MMA_UpdateAppServPlmnInfo(VOS_VOID);
VOS_VOID TAF_MMA_UpdateAppReportSrvStatus(VOS_VOID);
VOS_VOID TAF_MMA_UpdateAppReportSrvDomain(
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32  enCnDomainId
);
VOS_VOID TAF_MMA_ProcDelayReport(VOS_VOID);
VOS_VOID TAF_MMA_ProcServiceStatusImmediatelyReport(
    MSCC_MMA_SERVICE_STATUS_IND_STRU   *pstServiceStatus
);
VOS_VOID TAF_MMA_ProcServiceStatusNotReport(
    MSCC_MMA_SERVICE_STATUS_IND_STRU   *pstServiceStatus
);

VOS_VOID TAF_MMA_FillActForAtCmdCregInClMode(
    TAF_MMA_QRY_REG_STATUS_TYPE_ENUM_UINT32                 enQryRegStaType,
    TAF_PH_ACCESS_TECH_ENUM_UINT8                          *pucAct
);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_VOID TAF_MMA_UpdateAppSysModeAndSysSubModeInClMode(VOS_VOID);

VOS_VOID TAF_MMA_UpdateAppSysModeAndSysSubModeInClMode1x(
    TAF_SDC_NETWORK_EXISTANCE_ENUM_UINT32                   en1xNetworkExist
);

VOS_VOID TAF_MMA_UpdateAppSysModeAndSysSubModeInClModeHrpd(
    TAF_SDC_NETWORK_EXISTANCE_ENUM_UINT32                   enHrpdNetworkExist
);

VOS_VOID TAF_MMA_UpdateAppSysModeAndSysSubModeInClModeLte(
    TAF_SDC_NETWORK_EXISTANCE_ENUM_UINT32                   enLteNetworkExist
);

VOS_VOID TAF_MMA_UpdateAppCsSrvInfoInClMode(VOS_VOID);

VOS_VOID TAF_MMA_UpdateAppPsSrvInfoInClMode(VOS_VOID);

VOS_VOID TAF_MMA_SndCsRegStatusInClMode(VOS_VOID);

VOS_VOID TAF_MMA_Report1xSidInClMode(
    VOS_INT32                          lSid
);

VOS_VOID TAF_MMA_Report1xSigQulityInClMode(VOS_VOID);

VOS_VOID TAF_MMA_DelayReportCsReferCmdInClMode(VOS_VOID);

VOS_VOID TAF_MMA_SndPsRegStatusInClMode(VOS_VOID);


VOS_UINT8 TAF_MMA_IsDelayReportFeatureActiveInClMode(VOS_VOID);

VOS_UINT32 TAF_MMA_IsNeedDelayReportServiceStatusInClMode(VOS_VOID);

VOS_UINT32 TAF_MMA_IsNeedDelayReportCsRegStatusInClMode(VOS_VOID);

VOS_UINT32 TAF_MMA_IsNeedDelayReportPsRegStatusInClMode(VOS_VOID);

VOS_VOID TAF_MMA_StopDelayReportSeriveStatusTimerInClMode(
    TAF_MMA_TIMER_ID_ENUM_UINT32        enDelayTimerId
);

VOS_VOID TAF_MMA_UpdateServiceDomainInClMode(
    TAF_SDC_SYS_MODE_ENUM_UINT8        enSysMode
);

VOS_VOID TAF_MMA_DelayReportPsCmdInClMode(VOS_VOID);

VOS_VOID TAF_MMA_ReportHdrSigQulityInClMode(VOS_VOID);

VOS_VOID TAF_MMA_UpdateAppServiceDomainInClMode(
    TAF_SDC_SYS_MODE_ENUM_UINT8        enSysMode
);

VOS_VOID TAF_MMA_ConvertUimidToUl(
    VOS_UINT8                          *pucUimid,
    VOS_UINT32                         *pulUimidHigh,
    VOS_UINT32                         *pulUimidLow
);

VOS_VOID TAF_MMA_ConvertImsiToUl(
    VOS_UINT8                          *pucImsi,
    VOS_UINT32                         *pulImsiHigh,
    VOS_UINT32                         *pulImsiLow
);
VOS_VOID TAF_MMA_Report1xLocinfoInClMode(VOS_VOID);
TAF_ERROR_CODE_ENUM_UINT32 TAF_MMA_ConvertCsimCardStatusToTafErrorCode(
    TAF_SDC_USIM_STATUS_ENUM_UINT8      enCsimStatus
);
#endif

VOS_VOID TAF_MMA_UpdateReportService(VOS_VOID);

VOS_UINT32 TAF_MMA_IsUserOperate(VOS_VOID);

VOS_VOID TAF_MMA_ProcMsccSystemAcquireEndInd3GppType(
    MSCC_MMA_SYSTEM_ACQUIRE_END_IND_STRU    *pstSysAcqEndInd
);

VOS_VOID TAF_MMA_UpdateRatPrioFromClToGul(
    TAF_MMA_RAT_ORDER_STRU          *pstSndRatPrioList
);


VOS_UINT32 TAF_MMA_IsNeedProcessSystemAcquireResult(
    MSCC_MMA_SYSTEM_ACQUIRE_RESULT_ENUM_UINT32              enResult
);

TAF_MMA_RAT_MODE_TYPE_ENUM_UINT8 TAF_MMA_GetRatModeChangeType(
    TAF_MMA_RAT_ORDER_STRU             *pstCurrRat,
    TAF_MMA_RAT_ORDER_STRU             *pstLastRat
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

#endif /* end of TafMmaFsmImsSwitch.h */


