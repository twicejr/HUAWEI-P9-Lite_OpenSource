/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafSdcLib.h
  版 本 号   : 初稿
  作    者   : s46746
  生成日期   : 2012年12月26日
  最近修改   :
  功能描述   : TafSdcLib.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年12月26日
    作    者   : s46746
    修改内容   : 创建文件

******************************************************************************/
#ifndef _TAF_SDC_LIB_H_
#define _TAF_SDC_LIB_H_
/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "TafSdcCtx.h"

/* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-11, begin */
#include "TafOamInterface.h"
/* Modified by z00161729 for 主动上报AT命令控制下移至C核, 2013-4-11, end */
/* Added by wx270776 for OM融合, 2015-7-25, begin */
#include "TafLog.h"
/* Added by wx270776 for OM融合, 2015-7-25, end */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define PRE_SECOND_TO_TICK                      (100)

#define TAF_SDC_REV_IN_USE_7                    (7)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/
/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-8, begin */
#define TAF_SDC_GET_CURC_RPT_CTRL_STATUS_MAP_TBL_PTR()    (&g_aenTafSdcCurcRptCmdTable[0])
#define TAF_SDC_GET_CURC_RPT_CTRL_STATUS_MAP_TBL_SIZE()   (sizeof(g_aenTafSdcCurcRptCmdTable)/sizeof(TAF_SDC_RPT_CMD_INDEX_ENUM_UINT8))

#define TAF_SDC_GET_UNSOLICITED_RPT_CTRL_STATUS_MAP_TBL_PTR()    (&g_aenTafSdcUnsolicitedRptCmdTable[0])
#define TAF_SDC_GET_UNSOLICITED_RPT_CTRL_STATUS_MAP_TBL_SIZE()   (sizeof(g_aenTafSdcUnsolicitedRptCmdTable)/sizeof(TAF_SDC_RPT_CMD_INDEX_ENUM_UINT8))
/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-8, end */

/* Added by s00217060 for coverity清理, 2014-02-19, begin */
#define TAF_SDC_MIN(n1,n2)                                  (((n1) > (n2)) ? (n2):(n1))
/* Added by s00217060 for coverity清理, 2014-02-19, end */


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
 结构名    : TAF_SDC_LOG_NETWORK_AND_APPNETWORK_CTX_INFO_STRU
 结构说明  :TAF的g_stTafSdcCtx中的NETWORK/APPNETWORK信息可维可测

 修改记录  :
  1.日    期   : 2015年02月11日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseII 项目修改
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;/* 消息头                                   */ /*_H2ASN_Skip*/
    TAF_SDC_NETWORK_INFO_STRU           stNetworkInfo;
    TAF_SDC_APPNETWORK_INFO             stAppNetworkInfo;
}TAF_SDC_LOG_NETWORK_AND_APPNETWORK_CTX_INFO_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern VOS_VOID DIAG_TraceReport(VOS_VOID* pMsg);

VOS_UINT32  TAF_SDC_IsPlatformRatSupported(
    TAF_SDC_PLATFORM_RAT_TYPE_ENUM_UINT8                    enSpecRat
);

VOS_UINT32  TAF_SDC_IsPlatformSupportLte( VOS_VOID );

VOS_UINT32  TAF_SDC_IsPlatformSupportUtran( VOS_VOID );
VOS_UINT32  TAF_SDC_IsPlatformSupportUtranFdd( VOS_VOID );
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
VOS_UINT32  TAF_SDC_IsPlatformSupportUtranTdd( VOS_VOID );
#endif

VOS_UINT32  TAF_SDC_IsPlatformSupportGsm( VOS_VOID );

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_UINT32 TAF_SDC_IsPlatformSupport3Gpp2(VOS_VOID);

VOS_UINT32 TAF_SDC_IsPlatformSupport1x(VOS_VOID);
VOS_UINT32 TAF_SDC_IsPlatformSupportHrpd(VOS_VOID);

#endif

VOS_UINT32 TAF_SDC_IsPlatformSupport3Gpp(VOS_VOID);


/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-3, begin */
VOS_UINT32 TAF_SDC_CheckRptCmdStatus(
    VOS_UINT8                                  *pRptCfg,
    TAF_SDC_CMD_RPT_CTRL_TYPE_ENUM_UINT8        enRptCtrlType,
    TAF_SDC_RPT_CMD_INDEX_ENUM_UINT8            enRptCmdIndex
);
VOS_VOID TAF_SDC_UpdateRptCmdStatus(
    TAF_SDC_RPT_CMD_INDEX_ENUM_UINT8            enRptCmdIndex,
    VOS_UINT32                                  ulRptCmdStatus
);
/* Added by s00217060 for 主动上报AT命令控制下移至C核, 2013-4-3, end */

VOS_UINT32 TAF_SDC_ConvertOamSendPid(
    VOS_UINT32                          ulConvertedSendPid
);

/* Deleted by l00208543 for STK升级, 2013-07-24, begin */
/* Deleted by l00208543 for STK升级, 2013-07-24, end */
VOS_UINT32 TAF_SDC_GetCsSrvExistFlg(VOS_VOID);



/* Added by s00217060 for VoLTE_PhaseI  项目, 2013-08-29, begin */
VOS_UINT32 TAF_SDC_GetImsSupportFlag(VOS_VOID);
/* Added by s00217060 for VoLTE_PhaseI  项目, 2013-08-29, end */

VOS_UINT32 TAF_SDC_IsImsiAvailableInCurrSimStatus(
    TAF_SDC_USIM_STATUS_ENUM_UINT8      enSimStatus
);
#if (FEATURE_ON == FEATURE_PTM)
VOS_UINT32 TAF_SDC_IsErrLogNeedRecord(VOS_UINT16 usLevel);
VOS_VOID TAF_SDC_GetCardImsiFailRecord(
    VOS_UINT32                          ulGetCardImsiRslt,
    VOS_UINT8                          *pucImsi
);
#endif

VOS_UINT32  TAF_CalcTime(
                VOS_UINT32  ulFirTime,
                VOS_UINT32  ulSecTime,
                VOS_UINT32 *pulTotalTime
);

/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-20, begin */
VOS_UINT32 TAF_SDC_IsUsimStausValid(VOS_VOID);

/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-11-20, end */

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-31, begin */
#if (FEATURE_ON == FEATURE_IMS)
VOS_UINT32 TAF_SDC_IsImsVoiceSupportedInUE(VOS_VOID);
VOS_UINT32 TAF_SDC_IsImsVoiceSupportedInNW(VOS_VOID);
#endif
/* Added by w00176964 for VoLTE_PhaseIII 项目, 2013-12-31, end */

/* Added by l00198894 for 新增+ECID命令, 2013-12-10, begin */
VOS_VOID TAF_SDC_PlmnId2Bcd(
    TAF_SDC_PLMN_ID_STRU               *pstPlmnId
);
/* Added by l00198894 for 新增+ECID命令, 2013-12-10, end */


/* Added by s00246516 for L-C互操作项目, 2014-02-14, Begin */
VOS_UINT32 TAF_SDC_IsConfigCLInterWorkCOutside(VOS_VOID);
/* Added by s00246516 for L-C互操作项目, 2014-02-14, End */


VOS_UINT32 TAF_SDC_IsBcchPlmnIdInDestSimPlmnList (
    TAF_SDC_PLMN_ID_STRU               *pstBcchPlmnId,
    VOS_UINT8                           ucSimPlmnNum,
    TAF_SDC_PLMN_ID_STRU               *pstSimPlmnIdList
);
VOS_UINT32 TAF_SDC_ExactlyCompareBcchPlmnwithSimPlmn(
    TAF_SDC_PLMN_ID_STRU                *pstBccPlmnId,
    TAF_SDC_PLMN_ID_STRU                *pstSimPlmnId
);
VOS_UINT32 TAF_SDC_CompareBcchPlmnwithSimPlmn(
    TAF_SDC_PLMN_ID_STRU                *pstBccPlmnId,
    TAF_SDC_PLMN_ID_STRU                *pstSimPlmnId
);

VOS_UINT32 TAF_SDC_ExactlyCompareBcchPlmnwithSimPlmn_WithWildcard(
    TAF_SDC_PLMN_ID_STRU                *pstBccPlmnId,
    TAF_SDC_PLMN_ID_STRU                *pstSimPlmnId,
    VOS_CHAR                             cWildcard
);

TAF_SDC_FILE_TYPE_ENUM_UINT8  TAF_SDC_GetOplFileType(VOS_VOID);
TAF_SDC_FILE_TYPE_ENUM_UINT8  TAF_SDC_GetPnnFileType(VOS_VOID);
TAF_SDC_SPDI_FILE_INFO_STRU* TAF_SDC_GetSpdiFileInfo(VOS_VOID);
VOS_VOID TAF_SDC_ConvertPlmnId2NasStyle(
    TAF_SDC_PLMN_ID_STRU               *pstPlmnId
);


/* Added by w00167002 for L-C互操作项目, 2014-2-17, begin */
VOS_UINT32 TAF_SDC_IsLteOnlyMode(
    TAF_SDC_RAT_PRIO_STRU              *pstRatOrder
);
/* Added by w00167002 for L-C互操作项目, 2014-2-17, end */

VOS_UINT32 TAF_SDC_CheckDtmfKey(
    VOS_CHAR                           *pckey
);

VOS_UINT32 TAF_SDC_IsCsNormalService(VOS_VOID);

VOS_UINT32 TAF_SDC_IsPlatformSupportHybrid(VOS_VOID);

VOS_UINT32 TAF_SDC_IsImsSrvExist(VOID);


VOS_UINT8 TAF_SDC_IsCurrentNormalServiceStatus(void);

VOS_UINT8 TAF_SDC_IsCurrentNormalRegStatus(void);

VOS_VOID TAF_MMA_UpdateRoamFlag(
    TAF_SDC_REG_STATUS_ENUM_UINT8      enRegState
);

VOS_UINT32 TAF_SDC_IsAppSepcDomainRegStaChg(
    TAF_SDC_SERVICE_DOMAIN_ENUM_UINT8   enCnDomainId,
    TAF_SDC_REG_STATUS_ENUM_UINT8       enRegState
);


VOS_UINT32 TAF_SDC_ExactlyCompareBcchPlmnwithSimPlmn(
    TAF_SDC_PLMN_ID_STRU                *pstBccPlmnId,
    TAF_SDC_PLMN_ID_STRU                *pstSimPlmnId
);
VOS_UINT32 TAF_SDC_CompareBcchPlmnwithSimPlmn(
    TAF_SDC_PLMN_ID_STRU                *pstBccPlmnId,
    TAF_SDC_PLMN_ID_STRU                *pstSimPlmnId
);

VOS_UINT32 TAF_SDC_CompareBcchMccwithSimMcc_WithWildcard(
    VOS_UINT32                          ulBcchMcc,
    VOS_UINT32                          ulSimMcc,
    VOS_CHAR                            cWildcard,
    VOS_UINT8                           ucExactlyCmpFlg
);
VOS_UINT32 TAF_SDC_CompareBcchMncLow2ByteWithSimMnclowLow2Byte_WithWildcard(
    VOS_UINT32                          ulBcchMnc,
    VOS_UINT32                          ulSimMnc,
    VOS_CHAR                            cWildcard,
    VOS_UINT8                           ucExactlyCmpFlg
);
VOS_UINT32 TAF_SDC_CompareBcchMncwithSimMnc_WithWildcard(
    TAF_SDC_PLMN_ID_STRU               *pstBccPlmnId,
    TAF_SDC_PLMN_ID_STRU               *pstSimPlmnId,
    VOS_CHAR                            cWildcard,
    VOS_UINT8                           ucExactlyCmpFlg
);
VOS_UINT32 TAF_SDC_CompareBcchMnc3BytewithSimMnc3Byte(
    TAF_SDC_PLMN_ID_STRU               *pstBccPlmnId,
    TAF_SDC_PLMN_ID_STRU               *pstSimPlmnId,
    VOS_UINT8                           ucExactlyCmpFlg
);

VOS_UINT32 TAF_SDC_IsVailidWildcard(
    VOS_CHAR                            cWildcard
);

VOS_VOID TAF_SDC_HexToAsciiOfPlmnByte(
    VOS_UINT8                            ucSrc,
    VOS_UINT8                           *pucDst
);

VOS_UINT32 TAF_SDC_CompareBcchPlmnwithSimPlmn_WithWildcard(
    TAF_SDC_PLMN_ID_STRU               *pstBccPlmnId,
    TAF_SDC_PLMN_ID_STRU               *pstSimPlmnId,
    VOS_CHAR                            cWildcard
);

VOS_UINT32  TAF_SDC_IsOperNameTypeSupport(
    TAF_SDC_OPER_NAME_TYPE_ENUM_UINT8   enOperNameType
);

VOS_VOID  TAF_SDC_ConvertSimPlmnToNasPLMN(
    TAF_SDC_SIM_FORMAT_PLMN_ID          *pstSimPlmn,
    TAF_SDC_PLMN_ID_STRU                *pstNasPlmn
);

TAF_SDC_PLMN_ID_STRU  TAF_SDC_GetImsiHomePlmn(
    VOS_UINT8                          *pucImsi,
    VOS_UINT8                           ucUsimMncLenth
);

VOS_UINT32 TAF_SDC_IsSysCfgRatSupportHrpdAndLte(VOS_VOID);

VOS_UINT32 TAF_SDC_IsPlmnIdValid(
    TAF_SDC_PLMN_ID_STRU               *pstPlmnId
);
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_UINT32 TAF_SDC_IsConfigCLMode(VOS_VOID);
VOS_UINT32 TAF_SDC_Is1xOnlyMode(VOS_VOID);

VOS_UINT32 TAF_SDC_Get1xConcurrentSupportedFlag(VOS_VOID);

#endif


TAF_SDC_PLATFORM_RAT_TYPE_ENUM_UINT8 TAF_SDC_ConvertNvPlatformRatToTafType(
    PLATFORM_RAT_TYPE_ENUM_UINT16       enNvPlatformRatCap
);

VOS_UINT32 TAF_SDC_IsPlatformRatCapNvimValid(
    PLATAFORM_RAT_CAPABILITY_STRU      *pstNvPlatformRatCap
);


VOS_UINT32 TAF_SDC_IsSyscfgSupportSpecRat(
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode
);

VOS_UINT32 TAF_SDC_IsSyscfgSupport3gppRat(VOS_VOID);


VOS_UINT32 TAF_SDC_IsNeedReportRegStatusWhenNonnormalService(
    TAF_SDC_SERVICE_DOMAIN_ENUM_UINT8   enCnDomainId,
    TAF_SDC_REG_STATUS_ENUM_UINT8       enRegState
);

VOS_UINT32 TAF_SDC_IsSpecRatInRatList(
    TAF_MMA_RAT_TYPE_ENUM_UINT8         enRatType,
    TAF_MMA_RAT_ORDER_STRU             *pstRatList
);
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_UINT32 TAF_SDC_CovertCimisNumToBcd(VOS_UINT32 ulSrcValude, VOS_UINT32 ulCodeMode);
VOS_UINT32 TAF_SDC_ConvertCImsiBcdCode(
    VOS_UINT8                           *pucCIMSI,
    VOS_UINT8                           *pucStrCIMSI);
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

#endif /* end of TafSdcLib.h */
