/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafApsComFunc.h
  版 本 号   : 初稿
  作    者   : h44270
  生成日期   : 2011年12月26日
  最近修改   :
  功能描述   : TafApsComFunc.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年12月26日
    作    者   : h44270
    修改内容   : 创建文件

******************************************************************************/

#ifndef __TAFAPS_COMFUNC_H__
#define __TAFAPS_COMFUNC_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "NasStkInterface.h"
#include "TafApsGetPdpIdList.h"
#include "taf_aps_ppp_pif.h"
#include "hsm_aps_pif.h"
#include "TafSdcCtx.h"
#include "taf_aps_dhcp_pif.h"
#include "ehsm_aps_pif.h"
#include "TafMmaInterface.h"
#include "TafApsSndInternalMsg.h"

#include "NasMmlCtx.h"

#include "UsimPsInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define TAF_APS_GET_SM_ERR_CODE_MAP_TBL_PTR()   (g_astTafApsSmErrCodeMapTbl)
#define TAF_APS_GET_SM_ERR_CODE_MAP_TBL_SIZE()  (sizeof(g_astTafApsSmErrCodeMapTbl)/sizeof(TAF_APS_SM_ERR_CODE_MAP_STRU))

#define TAF_APS_GET_ESM_ERR_CODE_MAP_TBL_PTR()  (g_astTafApsEsmErrCodeMapTbl)
#define TAF_APS_GET_ESM_ERR_CODE_MAP_TBL_SIZE() (sizeof(g_astTafApsEsmErrCodeMapTbl)/sizeof(TAF_APS_ESM_ERR_CODE_MAP_STRU))

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#define TAF_APS_GET_XCC_ERR_CODE_MAP_TBL_PTR()  (g_astTafApsXccErrCodeMapTbl)
#define TAF_APS_GET_XCC_ERR_CODE_MAP_TBL_SIZE() (sizeof(g_astTafApsXccErrCodeMapTbl)/sizeof(TAF_APS_XCC_ERR_CODE_MAP_STRU))

#define TAF_APS_GET_HSM_ERR_CODE_MAP_TBL_PTR()  (g_astTafApsHsmErrCodeMapTbl)
#define TAF_APS_GET_HSM_ERR_CODE_MAP_TBL_SIZE() (sizeof(g_astTafApsHsmErrCodeMapTbl)/sizeof(TAF_APS_HSM_ERR_CODE_MAP_STRU))


#define TAF_APS_GET_EHSM_ERR_CODE_MAP_TBL_PTR()  (g_astTafApsEHsmErrCodeMapTbl)
#define TAF_APS_GET_EHSM_ERR_CODE_MAP_TBL_SIZE() (sizeof(g_astTafApsEHsmErrCodeMapTbl)/sizeof(TAF_APS_EHSM_ERR_CODE_MAP_STRU))
#define TAF_APS_MAX_ORIG_REDIAL_COUNT           (0xff)
#define TAF_APS_3GPD_FILEID_FLAG_MAP_TBL_PTR()  (g_astTafApsFileIdFlagTbl)
#define TAF_APS_3GPD_FILEID_FLAG_MAP_TBL_SIZE() (sizeof(g_astTafApsFileIdFlagTbl)/sizeof(TAF_APS_3GPD_FILEID_FLAG_MAP_STRU))

#endif

/* 封装OSA申请消息接口 */
#define TAF_APS_ALLOC_MSG_WITH_HDR(ulMsgLen)\
            PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF, (ulMsgLen))

/* 封装OSA消息头 */
#define TAF_APS_CFG_MSG_HDR(pstMsg, ulRecvPid, ulMsgId)\
            ((MSG_HEADER_STRU *)(pstMsg))->ulSenderCpuId   = VOS_LOCAL_CPUID;\
            ((MSG_HEADER_STRU *)(pstMsg))->ulSenderPid     = WUEPS_PID_TAF;\
            ((MSG_HEADER_STRU *)(pstMsg))->ulReceiverCpuId = VOS_LOCAL_CPUID;\
            ((MSG_HEADER_STRU *)(pstMsg))->ulReceiverPid   = (ulRecvPid);\
            ((MSG_HEADER_STRU *)(pstMsg))->ulMsgName       = (ulMsgId)

/* 封装OSA消息头(TAF内部消息) */
#define TAF_APS_CFG_INTRA_MSG_HDR(pstMsg, ulMsgId)\
            TAF_APS_CFG_MSG_HDR(pstMsg, WUEPS_PID_TAF, ulMsgId)

/* 封装OSA消息头(SKT消息) */
#define TAF_APS_CFG_STK_MSG_HDR(pstMsg, ulMsgId)\
            TAF_APS_CFG_MSG_HDR(pstMsg, MAPS_STK_PID, ulMsgId)

/* 封装OSA消息头(ESM消息) */
#define TAF_APS_CFG_ESM_MSG_HDR(pstMsg, ulMsgId)\
            TAF_APS_CFG_MSG_HDR(pstMsg, PS_PID_ESM, ulMsgId)

/* 获取OSA消息内容 */
#define TAF_APS_GET_MSG_ENTITY(pstMsg)\
            ((VOS_VOID *)&(((MSG_HEADER_STRU *)(pstMsg))->ulMsgName))

/* 获取OSA消息长度 */
#define TAF_APS_GET_MSG_LENGTH(pstMsg)\
            (((MSG_HEADER_STRU *)(pstMsg))->ulLength)

/* 封装OSA发送消息接口 */
#define TAF_APS_SEND_MSG(pstMsg)\
            if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstMsg))\
            {\
                TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SEND_MSG: Send message fail!");\
            }



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
extern VOS_UINT8 NAS_MML_GetPsAttachAllowFlg(VOS_VOID);

extern NAS_MML_TIMER_INFO_ENUM_UINT8 NAS_MML_GetT3402Status(VOS_VOID);

VOS_UINT32   TAF_APS_AllocPdpId(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT8                           ucCid,
    VOS_UINT8                          *pucPdpId
);
VOS_UINT32   TAF_APS_IsPdpIdValid(
    VOS_UINT8                           ucPdpId
);

VOS_UINT8 TAF_APS_GetCidValue(
    VOS_UINT32                          ulBearerActivateFlg,
    VOS_UINT8                          *pucCidList
);

VOS_UINT32 TAF_APS_CheckCidDefinedCtx(
    VOS_UINT8                           ucCid
)
;
VOS_UINT8   TAF_APS_GetPdpIdByNsapi(
    VOS_UINT8                           ucNsapi
);
VOS_UINT8 TAF_APS_GetPdpIdByLlcSapi(
    VOS_UINT8                           ucLlcSapi
);

VOS_UINT32 TAF_APS_CheckBearerPdpTypeSuitable(
    VOS_UINT8                           ucDefaultPdpType,
    TAF_PDP_TYPE_ENUM_UINT8             enUserPdpType
);

VOS_VOID TAF_APS_String2Hex(
    VOS_UINT8                          *pucStr,
    VOS_UINT16                          usStrLen,
    VOS_UINT32                         *pulResult
);
VOS_UINT8   TAF_APS_GetPdpIdByCid(
    VOS_UINT8                           ucCid
);
VOS_UINT8 TAF_APS_GetPdpIdByEpsbId(VOS_UINT32 ulEpsbId);

VOS_UINT8   TAF_APS_GetPdpEntOpId(
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid
);

VOS_UINT32   TAF_APS_GetPdpEntModuleId(
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid
);

VOS_UINT8  TAF_APS_GetPdpIdByDefaultCid (VOS_VOID);

VOS_VOID TAF_APS_SetPdpEntClientId (
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid,
    VOS_UINT16                          usClientId
);
VOS_VOID TAF_APS_SetPdpEntOpId (
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid,
    VOS_UINT8                           ucOpId
);
VOS_UINT32  TAF_APS_GetTiFromPdpId(
    VOS_UINT8                           ucPdpId,
    SM_TAF_TRANS_ID_STRU               *pstTi
);
VOS_UINT32  TAF_APS_GetPdpIdFromTi(
    SM_TAF_TRANS_ID_STRU               *pstTi,
    VOS_UINT8                          *pucPdpId
);
VOS_VOID  TAF_APS_SetPdpEntityTi(
    VOS_UINT8                           ucPdpId,
    SM_TAF_TRANS_ID_STRU               *pstTis
);
VOS_UINT8 TAF_APS_GetCidFromLteBitCid(
    VOS_UINT32                          ulBitCid
);

VOS_UINT32  TAF_APS_GetActivedCid(
    VOS_UINT8                           *pucActivedCid
);

VOS_UINT32 TAF_APS_Ipv4AddrAtoi(
    VOS_CHAR                           *pcString,
    VOS_UINT8                          *pucNumber
);

VOS_UINT32 TAF_APS_ValidatePdpType(
    TAF_PDP_TYPE_ENUM_UINT8             enPdpTypeReq,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpTypeCnf
);

VOS_UINT32 TAF_APS_Ipv4AddrItoa(
    VOS_CHAR                           *pcString,
    VOS_UINT8                          *pucNumber
);

VOS_UINT8 TAF_APS_ConverUserDefPdpTypeToApsEntityPdpType (
    TAF_PDP_TYPE_ENUM_UINT8             enUserPdpType,
    VOS_UINT8                           ucDefaultPdpType
);

TAF_APS_RAT_TYPE_ENUM_UINT32 TAF_APS_ConvertMmcRatType (
    MMC_APS_RAT_TYPE_ENUM_UINT32       enRatType
);

TAF_APS_RAT_TYPE_ENUM_UINT32 TAF_APS_ConvertMmaRatType (
    MMA_TAF_RAT_TYPE_ENUM_UINT32       enRatType
);

TAF_APS_RAT_TYPE_ENUM_UINT32 TAF_APS_ConvertMmaRatTypeToApsRatType (
    TAF_MMA_RAT_TYPE_ENUM_UINT8         enRatType
);

TAF_APS_RAT_TYPE_ENUM_UINT32 TAF_APS_ConvertMmaClServiceToApsRatType (
    MMA_TAF_RAT_TYPE_ENUM_UINT32       enRatType
);


VOS_VOID TAF_APS_GetSpecPdpLinkedPdpInfo (
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList,
    VOS_UINT8                           ucNsapi
);

extern TAF_APS_USER_CONN_STATUS_ENUM_UINT8 TAF_APS_GetUserConnStatus(VOS_VOID);

TAF_PS_CAUSE_ENUM_UINT32 TAF_APS_MapSmCause(
    SM_TAF_CAUSE_ENUM_UINT16            enSmCause
);

#if (FEATURE_ON == FEATURE_LTE)
TAF_PS_CAUSE_ENUM_UINT32 TAF_APS_MapEsmCause(
    VOS_UINT32                          ulEsmCause
);
#endif

TAF_PDP_TYPE_ENUM_UINT8 TAF_APS_ConvertPdpType(VOS_UINT8 ucPdpTypeNum);

/* Added by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, begin */
VOS_UINT32 TAF_APS_GetCtrlHdrFromCmdBufferQueue(
    TAF_CTRL_STRU                      *pstCtrl,
    TAF_APS_TIMER_ID_ENUM_UINT32        enTimer,
    VOS_UINT32                          ulPara
);
/* Added by Y00213812 for VoLTE_PhaseI 项目, 2013-07-08, end */

#if (FEATURE_ON == FEATURE_PTM)
VOS_VOID TAF_APS_PsCallFailErrRecord(TAF_PS_CAUSE_ENUM_UINT32 enCause);
#endif

VOS_VOID TAF_APS_SetPdpEntModuleId (
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid,
    VOS_UINT32                          ulModuleId
);

VOS_VOID TAF_APS_SetPdpEntCidValue (
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid
);

VOS_VOID TAF_APS_RmvPdpEntClientInfo (
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid,
    TAF_APS_BITCID_INFO_STRU           *pstBitCid
);

VOS_VOID   TAF_APS_SetPdpEntClientInfo(
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid,
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);

VOS_VOID   TAF_APS_AddPdpEntClientInfo(
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid,
    CONST TAF_CTRL_STRU                *pstCtrl
);

VOS_VOID TAF_APS_SetPdpEntBitCidMask (
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid
);
VOS_VOID TAF_APS_RmvPdpEntBitCidMask (
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid
);

VOS_UINT32 TAF_APS_IsPdpEntBitCidMaskExit (
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid
);

#if (FEATURE_ON == FEATURE_IMS)
VOS_UINT32 TAF_APS_CheckImsBearerByCid (
    VOS_UINT8                           ucCid
);

VOS_UINT32 TAF_APS_CheckImsBearerByRabId (
    VOS_UINT32                          ulRabId
);

VOS_VOID TAF_APS_GetImsBearerCid (
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                          *pucCid
);
#endif

VOS_VOID TAF_APS_GetPdpEntBitCidInfo(
    VOS_UINT8                           ucPdpId,
    TAF_APS_BITCID_INFO_STRU                    *pstCid
);

VOS_VOID TAF_APS_SetPdpEntAttachBearerFlag (
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucFlag
);

VOS_UINT8 TAF_APS_GetPdpEntAttachBearerFlag (
    VOS_UINT8                           ucPdpId
);

VOS_VOID   TAF_APS_SetPsCallEvtCtrl(
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid,
    TAF_CTRL_STRU                      *pstCtrl
);

VOS_INT32 TAF_APS_CompareApn(
    const VOS_UINT8                 aucBearerApn[],
    VOS_UINT8                       ucBearerApnLen,
    const VOS_UINT8                 aucUserApn[],
    VOS_UINT8                       ucUserApnLen
);

VOS_VOID TAF_APS_SetPdpEntDialPdpType(
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
);

VOS_UINT8 TAF_APS_GetPdpEntDialPdpType(
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid
);

VOS_UINT32 TAF_APS_MatchCallWithAllBearer(
    CONST TAF_CTRL_STRU                *pstCtrl,
    CONST TAF_APS_MATCH_PARAM_STRU     *pstMatchParam,
    VOS_UINT8                          *pucPdpId
);

VOS_UINT16   TAF_APS_GetPdpEntClientId(
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid
);

VOS_VOID TAF_APS_SetPdpEntModDialInfo (
    VOS_UINT8                           ucPdpId,
    TAF_APS_PDP_MOD_DIAL_STRU          *pstModDial
);

VOS_VOID TAF_APS_GetPdpEntModDialInfo (
    VOS_UINT8                           ucPdpId,
    TAF_APS_PDP_MOD_DIAL_STRU          *pstModDial
);

VOS_VOID TAF_APS_SetPdpEntAddrType(
    VOS_UINT8                           ucPdpId,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
);

VOS_UINT32 TAF_APS_IsAnyBearerExist(VOS_VOID);

#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32 TAF_APS_IsAttachBearerExist(VOS_VOID);
VOS_UINT32 TAF_APS_IsPdnCntxtValid(TAF_APS_PDN_CONTEXT_STRU *pstPdnCntx);
VOS_UINT32 TAF_APS_IsPdnCntxtDefault(TAF_APS_PDN_CONTEXT_STRU *pstPdnCntx);
VOS_UINT32 TAF_APS_IsAnyOtherNormalPdnActive(TAF_APS_PDN_CONTEXT_STRU *pstPdnCntx);
VOS_UINT32 TAF_APS_IsPdnCntxtTeardownAllowed(TAF_APS_PDN_CONTEXT_STRU *pstPdnCntxt);
#endif

VOS_UINT8 TAF_APS_GetAttachAllowFlg(VOS_VOID);

VOS_UINT8 TAF_APS_IsT3402Running(VOS_VOID);

VOS_VOID TAF_APS_GenMatchParamByCidInfo(
    CONST TAF_PDP_TABLE_STRU           *pstPdpTblInfo,
    TAF_APS_MATCH_PARAM_STRU           *pstMatchParam
);

VOS_VOID TAF_APS_GenMatchParamByDailInfo(
    CONST TAF_PS_DIAL_PARA_STRU        *pstDialParaInfo,
    TAF_APS_MATCH_PARAM_STRU           *pstMatchParam
);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
TAF_PS_CAUSE_ENUM_UINT32 TAF_APS_MapXccCause(
    TAF_XCC_CAUSE_ENUM_UINT32           enXccCause
);

VOS_VOID TAF_APS_SetPdpEntSo (
    VOS_UINT8                           ucPdpId,
    TAF_APS_CDATA_SO_TYPE_ENUM_UINT16   enSo
);

TAF_APS_CDATA_SO_TYPE_ENUM_UINT16 TAF_APS_GetPdpEntSo (
    VOS_UINT8                           ucPdpId
);


VOS_VOID TAF_APS_SetPdpEntConRef (
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucConRef
);

VOS_VOID TAF_APS_SetPdpEntConnectId (
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucConnectId
);



VOS_VOID TAF_APS_SetPdpEntPppState (
    VOS_UINT8                           ucPdpId,
    TAF_APS_CDATA_PPP_STATE_ENUM_UINT8  enPppState
);

TAF_APS_CDATA_PPP_STATE_ENUM_UINT8 TAF_APS_GetPdpEntPppState (
    VOS_UINT8                           ucPdpId
);
VOS_UINT8   TAF_APS_GetPdpIdByConRef(
    VOS_UINT8                           ucConRef
);

VOS_UINT8   TAF_APS_GetPdpIdByCallId(
    VOS_UINT8                           ucCallId
);



VOS_VOID TAF_APS_SetPdpEntCdsServiceIndFlag (
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucFlag
);

VOS_UINT8 TAF_APS_GetPdpEntCdsServiceIndFlag (
    VOS_UINT8                           ucPdpId
);

VOS_UINT32 TAF_APS_IsNeedSilentRedial(
    TAF_PS_CAUSE_ENUM_UINT32            enCause,
    TAF_APS_RAT_TYPE_ENUM_UINT32        enRatMode
);

VOS_UINT32 TAF_APS_IsNeedRedial1xSystemAcquire(
    TAF_PS_CAUSE_ENUM_UINT32            enCause,
    VOS_INT32                           lRssi
);

VOS_VOID TAF_APS_CdataOrigRedialCount(
    VOS_UINT8                           ucPdpId,
    TAF_XCC_FAIL_LAYER_ENUM_UINT8       enFailLayer
);

VOS_UINT32 TAF_APS_IsNeedRedialHrpdSystemAcquire(
    TAF_PS_CAUSE_ENUM_UINT32            enCause
);


VOS_VOID TAF_APS_SetPdpEntL2ErrReOrigFlag (
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucIsL2ErrReOrig
);

VOS_VOID TAF_APS_SetPdpEntReOrigCount (
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucL2ErrReOrigCount
);

VOS_UINT8 TAF_APS_GetPdpEntReOrigCount (
    VOS_UINT8                           ucPdpId
);

VOS_UINT32 TAF_APS_Is1xRedialCause(
    TAF_PS_CAUSE_ENUM_UINT32                enCause,
    TAF_APS_CDATA_REDIAL_TYPE_ENUM_UINT8    enType
);


VOS_VOID TAF_APS_PdpEntityEnterDormant(
    VOS_UINT8                           ucPdpId,
    VOS_UINT32                          ulIsNeedStartTimer
);

VOS_VOID TAF_APS_SetPdpEntSrId (
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucSrId
);
VOS_UINT8 TAF_APS_GetPdpEntSrId (
    VOS_UINT8                           ucPdpId
);

VOS_VOID TAF_APS_UpdataCdataIpv4Addr(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    PPP_APS_ACT_CNF_STRU               *pstPppActCnf
);

VOS_VOID TAF_APS_UpdataCdataIpv6Addr(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    PPP_APS_ACT_CNF_STRU               *pstPppActCnf
);

TAF_PS_CAUSE_ENUM_UINT32 TAF_APS_MapHsmCause(
    HSM_APS_CAUSE_ENUM_UINT32           enhHsmCause
);

VOS_UINT8 TAF_APS_IsHrpdRedialCause(
    TAF_PS_CAUSE_ENUM_UINT32            enCause
);

VOS_UINT8 TAF_APS_IsNeedRedialImmediately(
    TAF_CS_CAUSE_ENUM_UINT32            enCause,
    VOS_INT32                           lRssi
);

TAF_PS_CDATA_BEAR_STATUS_ENUM_UINT8 TAF_APS_MapCdataBearStatus(
    VOS_UINT8                           ucPdnId
);


VOS_UINT8   TAF_APS_GetPdpIdByPndId(
    VOS_UINT8                           ucPdnId
);
TAF_PS_CDATA_BEAR_STATUS_ENUM_UINT8 TAF_APS_GetCdataEhrpdSvcSta(
    VOS_UINT8                           ucPdpId
);



VOS_VOID TAF_APS_AddCauseForCdataDoalStackDailNotSuport(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstPdpActCnfEvt,
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid
);

TAF_APS_CDATA_REDIAL_TYPE_ENUM_UINT8 TAF_APS_IsNeedRedialEventType(
    VOS_UINT32            ulEventType
);



VOS_UINT32 TAF_APS_IsAllowCdataEsting(
    TAF_APS_RAT_TYPE_ENUM_UINT32        enRatType
);

VOS_UINT8 TAF_APS_GetDrsValueByScene(
    VOS_UINT32                          ulEventType
);

VOS_UINT8 TAF_APS_IsRedialCallFromDormantState(
    VOS_UINT8                           ucPdnId
);

VOS_VOID TAF_APS_SetPdpEntCdataEstFailCause(
    VOS_UINT8                           ucPdnId,
    TAF_APS_RAT_TYPE_ENUM_UINT32        enRatType
);

VOS_UINT32  TAF_APS_IsNeedNotifyCdsModeChange(
    TAF_APS_RAT_TYPE_ENUM_UINT32        enRatType,
    TAF_APS_RAT_TYPE_ENUM_UINT32        enDataSerMode
);

VOS_UINT32 TAF_APS_IsHybridMode(VOS_VOID);

TAF_APS_CDATA_PS_STATE_ENUM_UINT8 AT_APS_ConvertPsCdataStatusToCsdCdataStatus(
    TAF_PS_CDATA_BEAR_STATUS_ENUM_UINT8                     enPsCdataStatus
);

VOS_VOID TAF_APS_SetCdmaAirLinkStatus(
    VOS_UINT8                                   ucPdpId,
    TAF_APS_CDATA_AIR_LINK_STATUS_ENUM_UINT8    enAirLinkStatus
);

TAF_APS_CDATA_AIR_LINK_STATUS_ENUM_UINT8 TAF_APS_GetCdmaAirLinkStatus(
    VOS_UINT8                           ucPdpId
);

VOS_VOID TAF_APS_SetDoQuickAcqProtectFlag(
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucHrpdCallSysAcqFlag
);

VOS_UINT8 TAF_APS_GetDoQuickAcqProtectFlag(
    VOS_UINT8                           ucPdpId
);



TAF_APS_PPP_AUTH_TYPE_ENUM_UINT8 TAF_APS_MapApsAuthTypeToPpp(
    TAF_PDP_AUTH_TYPE_ENUM_UINT8        enTafPdpAuthType
);
VOS_VOID TAF_APS_Read3GpdSipCapaFileCnf(
    USIMM_READFILE_CNF_STRU            *pUsimTafMsg
);
VOS_VOID TAF_APS_Read3GpdSipUppFileCnf(
    USIMM_READFILE_CNF_STRU            *pUsimTafMsg
);
VOS_VOID TAF_APS_Read3GpdSipStatusFileCnf(
    USIMM_READFILE_CNF_STRU            *pUsimTafMsg
);
VOS_VOID TAF_APS_Read3GpdSipPapSsFileCnf(
    USIMM_READFILE_CNF_STRU            *pUsimTafMsg
);
VOS_UINT8 TAF_APS_Parse3GpdSingleSipSsContent(
    VOS_UINT8                          *pucSrcAddr,
    VOS_UINT8                           ucOffsetPos,
    VOS_UINT8                           ucPapSsIndex,
    VOS_UINT8                          *pucSingleSsContentBitLen
);
VOS_UINT8 TAF_APS_ParseSipPapSsLen(
    VOS_UINT8                          *pucSrcAddr,
    VOS_UINT8                           ucOffsetPos,
    VOS_UINT8                          *pucSslen,
    VOS_UINT8                           ucPapSsIndex
);
VOS_VOID TAF_APS_ParseSipPapSsStr(
    VOS_UINT8                          *pucSrcAddr,
    VOS_UINT8                           ucOffsetPos,
    VOS_UINT8                           ucSsLen,
    VOS_UINT8                           ucPapSsIndex
);
VOS_UINT32 TAF_APS_Get3GpdPppSipPapSsInfoFromCard(
    TAF_APS_3GPD_SIP_INFO_STRU         *pst3GpdSipInfo
);
VOS_UINT32 TAF_APS_Get3GpdPppSipNaiInfoFromCard(
    TAF_APS_3GPD_SIP_INFO_STRU         *pst3GpdSipInfo
);
TAF_APS_READ_SIM_FILES_CNF_ENUM_UINT32 TAF_APS_Map3GpdFileIdAndFlag(
    USIMM_DEF_FILEID_ENUM_UINT32          usEfId
);
TAF_PDP_AUTH_TYPE_ENUM_UINT8 TAF_APS_Map3GpdAuthTypeToPpp(
    TAF_APS_3GPD_SIP_PPP_AUTH_ALGORITHM_ENUM_UINT8        en3GpdAuthType
);

EHSM_APS_AUTH_TYPE_ENUM_UINT8 TAF_APS_MapApsAuthTypeToEhsm(
    TAF_PDP_AUTH_TYPE_ENUM_UINT8        enTafPdpAuthType
);
VOS_UINT8 TAF_APS_MapEhsmPdnTypeToAps(
    EHSM_APS_PDN_TYPE_ENUM_UINT8        enPdnType
);
VOS_UINT8 TAF_APS_MapPppPdnTypeToAps(
    TAF_APS_PPP_ADDR_TYPE_ENUM_UINT8                        enPdnType
);

VOS_VOID TAF_APS_LocalReleaseAll(VOS_VOID);

VOS_UINT32 TAF_APS_IsSyscfgCdmaModeChange(
    TAF_MMA_RAT_ORDER_STRU             *pstOldRatOrder,
    TAF_MMA_RAT_ORDER_STRU             *pstNewRatOrder
);

#endif

TAF_SDC_SERVICE_STATUS_ENUM_UINT8 TAF_APS_Get1XServiceStatus(VOS_VOID);

TAF_SDC_SERVICE_STATUS_ENUM_UINT8 TAF_APS_GetHrpdServiceStatus(VOS_VOID);

TAF_PS_CAUSE_ENUM_UINT32 TAF_APS_MapEhsmCause(
    EHSM_APS_CAUSE_ENUM_UINT32          enEhsmCause
);

VOS_VOID TAF_APS_SetPdpEntCdataPdnId (
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucPdnId
);

VOS_UINT8 TAF_APS_GetPdpEntCdataPdnId(
    VOS_UINT8                           ucPdpId
);

VOS_VOID TAF_APS_UpdateCdataEhsmPdnInfo (
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    EHSM_APS_PDN_ADDR_STRU             *pstPdnAddr,
    EHSM_APS_APN_STRU                  *pstApn,
    EHSM_APS_DNS_IPV4_STRU             *pstIpv4Dns
);

VOS_VOID TAF_APS_UpdateCdataIpv4Dns(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    DHCP_APS_DNS_IPV4_CNF_STRU         *pstDhcpDnsIpv4Cnf
);

VOS_VOID TAF_APS_UpdateCdataIpv6Dns(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    MN_APS_PDP_IPV6_DNS_STRU           *pstPdpIpv6Dns
);

VOS_VOID TAF_APS_SndExternalModulePsRatTypeNtf(
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrCdataServiceMode
);

VOS_VOID TAF_APS_RcvSequenceProcessDhcpNdclient(
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid
);

VOS_VOID TAF_APS_ProcCdataDhcpNegotiateFail(
    VOS_UINT8                                     ucPdpId,
    TAF_APS_INTER_END_CALL_REASON_ENUM_UINT8      enEndReason
);

VOS_VOID TAF_APS_ProcModifyReq_LteHandoverToEhrpdScene(
    VOS_UINT8                                               ucPdpId,
    EHSM_APS_LTE_HANDOVER_TO_EHRPD_IND_STRU                *pstLteHandoverInd
);
VOS_VOID TAF_APS_ProcPdnInfoChg_LteHandoverToEhrpdScene(
    VOS_UINT8                                               ucPdpId,
    EHSM_APS_LTE_HANDOVER_TO_EHRPD_IND_STRU                *pstLteHandoverInd,
    VOS_UINT32                                             *pulIsNeedDeactPdn
);

VOS_UINT8 TAF_APS_IsExistXcallOrXsmsOpreation(VOS_VOID);


VOS_VOID TAF_APS_LocalReleaseProc(
    VOS_UINT8                           ucPdpId
);

VOS_UINT8 TAF_APS_IsCdataLocalReleaseCause(
    TAF_PS_CAUSE_ENUM_UINT32                enCause
);

VOS_VOID TAF_APS_SetPdpEntCdataPsState (
    VOS_UINT8                           ucPdpId,
    TAF_APS_CDATA_PS_STATE_ENUM_UINT8   enPsState
);

TAF_APS_CDATA_PS_STATE_ENUM_UINT8 TAF_APS_GetPdpEntCdataPsState (
    VOS_UINT8                           ucPdpId
);


VOS_RATMODE_ENUM_UINT32 TAF_APS_MapRatType2VosRatMode(
    TAF_APS_RAT_TYPE_ENUM_UINT32        enRatType
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

#endif /* end of TafApsCtx.h */
