/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafSpmComFunc.h
  版 本 号   : 初稿
  作    者   : w00176964
  生成日期   : 2013年12月16日
  最近修改   :
  功能描述   : TafSpmComFunc.c的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年12月16日
    作    者   : w00176964
    修改内容   : 创建文件

******************************************************************************/
#ifndef _TAF_SPM_COM_FUNC_H_
#define _TAF_SPM_COM_FUNC_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "PsTypeDef.h"

#include "TafSpmCtx.h"
#include "TafSdcCtx.h"
#include "MnCallApi.h"
#if (FEATURE_ON == FEATURE_IMS)
#include "SpmImsaInterface.h"
#endif

#include "TafInternalInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define MN_CALL_MAX_ASCII_NUM_LEN    (MN_CALL_MAX_BCD_NUM_LEN * 2)

#define TAF_SPM_ECONF_GET_INDEX_FROM_PARA(ulPara)       ((ulPara >> 16) & VOS_NULL_WORD)

#define TAF_SPM_ECONF_SET_SEND_PARA(ulIndex, usClient)  ((VOS_UINT32)((ulIndex << 16) | (VOS_UINT32)usClient))




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
VOS_UINT32  TAF_SPM_IsNetworkEmergencyNum(
    MN_CALL_CALLED_NUM_STRU             *pstDialNum,
    VOS_UINT32                          *pulEmerCatExist,
    VOS_UINT8                           *pucEmerCategory
);
VOS_UINT32  TAF_SPM_IsAppCustomEmergencyNum(
    MN_CALL_CALLED_NUM_STRU             *pstDialNum,
    VOS_UINT32                          *pulEmerCatExist,
    VOS_UINT8                           *pucEmerCategory
);
VOS_UINT32  TAF_SPM_IsUsimEmergencyNum(
    MN_CALL_CALLED_NUM_STRU            *pstDialNum,
    VOS_UINT32                         *pulEmcCatExist,
    VOS_UINT8                          *pucEmerCategory
);

VOS_UINT32 TAF_SPM_GetBcCallType(
    VOS_UINT32                          bExistBc,
    VOS_UINT32                          ulBcLength,
    VOS_UINT8                          *pucBc,
    MN_CALL_TYPE_ENUM_U8               *penCallType
);

VOS_UINT32 TAF_SPM_IsPhoneEmergencyNum(
    MN_CALL_CALLED_NUM_STRU            *pstDialNum
);

VOS_UINT32  TAF_SPM_IsEmergencyNum(
    MN_CALL_CALLED_NUM_STRU            *pstDialNum,
    VOS_UINT32                          ulCheckEfecc,
    MN_CALL_EMERGENCY_CAT_STRU         *pstEmergencyCat
);

VOS_UINT32 TAF_SPM_IsUsimServiceAvailable(VOS_VOID);
TAF_SPM_SRV_REQ_TYPE_ENUM_UINT8 TAF_SPM_GetServiceRequestTypeWithAtClient(
    struct MsgCB                       *pstMsg
);
TAF_SPM_SRV_REQ_TYPE_ENUM_UINT8 TAF_SPM_GetServiceRequestTypeWithStkClient(
    struct MsgCB                       *pstMsg
);
TAF_SPM_SRV_REQ_TYPE_ENUM_UINT8 TAF_SPM_GetServiceRequestTypeWithTafClient(
    struct MsgCB                       *pstMsg
);

VOS_VOID TAF_SPM_ConvertSrvTypeToMma(
    TAF_SPM_SRV_REQ_TYPE_ENUM_UINT8     enSpmSrvReq,
    TAF_MMA_SRV_TYPE_ENUM_UINT8        *pucMmaSrvType
);


TAF_SPM_SRV_REQ_TYPE_ENUM_UINT8 TAF_SPM_GetServiceRequestType(
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_IsUssdServiceType(
    VOS_UINT32                          ulEventType
);
#if (FEATURE_ON == FEATURE_IMS)

VOS_VOID TAF_SPM_SendTafAgentGetCallInfoCnf(
    IMSA_SPM_CALL_GET_CALL_INFO_CNF_STRU    *pstImsaMsg
);
VOS_VOID TAF_SPM_SendAtGetCallInfoCnf(
    IMSA_SPM_CALL_GET_CALL_INFO_CNF_STRU    *pstImsaMsg
);
#endif

VOS_VOID TAF_SPM_GetCallInfoFromFsmEntryMsg(
    MN_CALL_CALLED_NUM_STRU            *pstDialNumber,
    MN_CALL_TYPE_ENUM_U8               *penCallType,
    MN_CALL_MODE_ENUM_U8               *penCallMode,
    MN_CALL_CS_DATA_CFG_STRU           *pstDataCfg
);


VOS_UINT32 TAF_SPM_IsNeedCheckFdn(VOS_VOID);

VOS_UINT32 TAF_SPM_IsNeedCallControl(VOS_VOID);

/* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-1-15, begin */
VOS_UINT32 TAF_SPM_IsUESupportMoCallType(
    MN_CALL_TYPE_ENUM_U8                enCallType
);
/* Added by w00176964 for VoLTE_PhaseIII 项目, 2014-1-15, end */

#if (FEATURE_ON == FEATURE_IMS)
VOS_VOID TAF_SPM_ProcSmsRptEvent(TAF_SPM_MSG_REPORT_IND_STRU  *pstMsgReportInd);

VOS_VOID TAF_SPM_SendAtEconfDialCnf(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId,
    MN_CALL_ID_T                        ucCallId,
    TAF_CS_CAUSE_ENUM_UINT32            enCause
);

VOS_VOID TAF_SPM_SendAtGetEconfCallInfoCnf(
    IMSA_SPM_CALL_GET_ECONF_CALLED_INFO_CNF_STRU   *pstImsaMsg
);

VOS_VOID TAF_SPM_ParseEconfDailInfoFromMsg(
    struct MsgCB                       *pstAppMsg
);

VOS_VOID TAF_SPM_SendEconfNotifyInd(
    MN_OPERATION_ID_T                   ucOpId,
    VOS_UINT8                           ucNumOfCalls,
    TAF_CALL_ECONF_INFO_PARAM_STRU     *pstCallInfo
);

VOS_VOID TAF_SPM_ReportEconfCheckRslt(VOS_VOID);

VOS_VOID TAF_SPM_RecordEconfCheckRslt(
    VOS_UINT32                          ulIndex,
    VOS_UINT32                          ulResult
);

VOS_VOID TAF_SPM_SetEconfPreRslt(
    TAF_CS_CAUSE_ENUM_UINT32            enCause
);

VOS_UINT32 TAF_SPM_ProcEconfCheckResult(VOS_VOID);


#endif

/* Added by w00176964 for V3R3C60_eCall项目, 2014-5-4, begin */
#if (FEATURE_ON == FEATURE_ECALL)
VOS_VOID TAF_SPM_ReadEcallNumber(
    VOS_UINT8                           ucFdnRecordNum,
    VOS_UINT8                           ucSdnRecordNum
);

#if (FEATURE_IMS == FEATURE_ON)
VOS_UINT32 TAF_SPM_IsImsCallTypeEmgencyCall(VOS_VOID);

VOS_VOID TAF_SPM_SndImsRelAllCall(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId
);
#endif

#endif
/* Added by w00176964 for V3R3C60_eCall项目, 2014-5-4, end */

VOS_UINT32  TAF_SPM_IsEmergencyNum_CDMA(
    MN_CALL_CALLED_NUM_STRU            *pstDialNum,
    VOS_UINT32                         *pulEmcCatExist,
    VOS_UINT8                          *pucEmerCategory
);
VOS_UINT32  TAF_SPM_IsUsimEmergencyNum_CDMA(
    MN_CALL_CALLED_NUM_STRU            *pstDialNum,
    VOS_UINT32                         *pulEmcCatExist,
    VOS_UINT8                          *pucEmerCategory
);



VOS_UINT32 TAF_SPM_GetRfAvailInfo(
    TAF_SPM_SRV_REQ_TYPE_ENUM_UINT8     enSrvReqType,
    TAF_MMA_SRV_ACQ_RAT_LIST_STRU      *pstSrvAcqRatList
);

VOS_UINT32 TAF_SPM_IsSimServiceAvailable(
    TAF_SDC_USIM_STATUS_ENUM_UINT8      enSimStatus
);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_UINT32 TAF_SPM_IsCsimServiceAvailable(VOS_VOID);

VOS_UINT32 TAF_SPM_IsPhoneEmergencyNum_CDMA(
    MN_CALL_CALLED_NUM_STRU            *pstDialNum
);
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

#endif /* end of TafSpmComFunc.h */

