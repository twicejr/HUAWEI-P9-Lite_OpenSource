/************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : usimmglobal.h
  Author      : g00256031
  Version     : V800R001
  Date        : 2015-3-12
  Description : 该头文件定义了---
  History     :
  1.Date:2015-3-13
     Author: g00256031
     Modification:Modify the definition of enum

************************************************************************/

#ifndef __USIMM_GLOBAL_H__
#define __USIMM_GLOBAL_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "usimmbase.h"

#pragma pack(4)

#if (FEATURE_ON == FEATURE_UE_UICC_MULTI_APP_SUPPORT)
/*****************************************************************************
  2 宏定义
*****************************************************************************/

/*******************************************************************************
  3 枚举定义
*******************************************************************************/


/*****************************************************************************
  4 STRUCT定义
*****************************************************************************/


/*****************************************************************************
  5 全局变量声明
*****************************************************************************/
extern USIMM_COMM_CARD_APP_INFO_STRU       g_astUSIMMCardAppInfo[USIMM_CHANNEL_NUMBER_MAX];

/*****************************************************************************
  6 函数声明
*****************************************************************************/

extern VOS_VOID USIMM_CCB_SetTestCardType(
    USIMM_TEST_PHYCARD_TYPE_ENUM_UINT32 enTestCardType);

extern USIMM_TEST_PHYCARD_TYPE_ENUM_UINT32 USIMM_CCB_GetTestCardType(VOS_VOID);

extern VOS_VOID USIMM_CCB_SetCardType(
    USIMM_PHYCARD_TYPE_ENUM_UINT32      enCardType);

extern VOS_VOID USIMM_CCB_SetCardVersion(
    USIMM_PHYCARD_TYPE_ENUM_UINT32      enCardVersion);

extern USIMM_PHYCARD_TYPE_ENUM_UINT32 USIMM_CCB_GetCardVersion(VOS_VOID);

extern USIMM_PHYCARD_TYPE_ENUM_UINT32 USIMM_CCB_GetCardType(VOS_VOID);

extern VOS_VOID USIMM_CCB_SetMainAppType(
    USIMM_CARDAPP_ENUM_UINT32           enMainAppType);

extern USIMM_CARDAPP_ENUM_UINT32 USIMM_CCB_GetMainAppType(VOS_VOID);

extern VOS_VOID USIMM_CCB_SetAppService(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    USIMM_CARD_SERVIC_ENUM_UINT32       enAppService);

extern USIMM_CARD_SERVIC_ENUM_UINT32 USIMM_CCB_GetAppService(
    USIMM_CARDAPP_ENUM_UINT32           enAppType);

extern VOS_VOID USIMM_CCB_SetAppStateChange(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    USIMM_CARD_STATE_CHANGE_ENUM_UINT32 enStateChange);

extern USIMM_CARD_STATE_CHANGE_ENUM_UINT32 USIMM_CCB_GetAppStateChange(
    USIMM_CARDAPP_ENUM_UINT32           enAppType);

extern USIMM_CURFILEINFO_ST* USIMM_CCB_GetCurFileInfo(
    USIMM_CARDAPP_ENUM_UINT32           enAppType);

extern USIMM_EFFCP_ST* USIMM_CCB_GetCurEFInfo(
    USIMM_CARDAPP_ENUM_UINT32           enAppType);

extern USIMM_DFFCP_ST* USIMM_CCB_GetCurDFInfo(
    USIMM_CARDAPP_ENUM_UINT32           enAppType);

extern USIMM_UICC_ADF_INFO_STRU* USIMM_CCB_GetAdfInfoByCH(
    VOS_UINT8                           ucChannelNo);

extern USIMM_COMM_CARD_APP_INFO_STRU *USIMM_CCB_GetAppInfoByCH(
    VOS_UINT8                           ucCHNum);

extern USIMM_CARDAPP_ENUM_UINT32 USIMM_CCB_GetAppTypeByCH(
    VOS_UINT8                           ucCHNum);

extern USIMM_COMM_PIN_INFO_STRU* USIMM_CCB_GetPINInfo(
    USIMM_CARDAPP_ENUM_UINT32           enAppType);

extern USIMM_APP_PIN_INFO_STRU* USIMM_CCB_GetPIN1InfoByRef(
    USIMM_COMM_PIN_ENUM_UINT32          enPinType);

extern USIMM_APP_PIN_INFO_STRU* USIMM_CCB_GetPIN1InfoByApp(
    USIMM_CARDAPP_ENUM_UINT32           enAppType);

extern USIMM_APP_PIN_INFO_STRU* USIMM_CCB_GetPIN2InfoByApp(
    USIMM_CARDAPP_ENUM_UINT32           enAppType);

extern VOS_VOID USIMM_CCB_SetAppFDN(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    USIMM_FDNSTATUS_ENUM_UINT32         enFDNStatus);

extern USIMM_FDNSTATUS_ENUM_UINT32 USIMM_CCB_GetAppFDN(
    USIMM_CARDAPP_ENUM_UINT32           enAppType);

extern VOS_VOID USIMM_CCB_SetAppBDN(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    USIMM_BDNSTATUS_ENUM_UINT32         enBDNStatus);

extern USIMM_BDNSTATUS_ENUM_UINT32 USIMM_CCB_GetAppBDN(
    USIMM_CARDAPP_ENUM_UINT32           enAppType);

extern VOS_VOID USIMM_CCB_SetAppChNO(
    VOS_UINT8                           ucChannelNo,
    USIMM_CARDAPP_ENUM_UINT32           enAppType);

extern VOS_UINT8 USIMM_CCB_GetAppChNO(
    USIMM_CARDAPP_ENUM_UINT32           enAppType);

extern VOS_VOID USIMM_CCB_SetSimPhase(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    USIMM_SIM_PHASE_ENUM_UINT32         enSimPhase);

extern USIMM_SIM_PHASE_ENUM_UINT32 USIMM_CCB_GetSimPhase(
    USIMM_CARDAPP_ENUM_UINT32           enAppType);

extern VOS_UINT32 USIMM_CCB_GetUsimSimulateIsimStatus(VOS_VOID);

extern VOS_VOID USIMM_CCB_SetUsimSimulateIsimStatus(
    VOS_UINT32                          ulStatus);

extern VOS_UINT32 USIMM_CCB_IsCardExist(VOS_VOID);

extern USIMM_POOL_ST* USIMM_CCB_GetFilePoolTotalGlobal(VOS_VOID);

extern USIMM_POOL_ONERECORD_ST* USIMM_CCB_GetPoolFileByIndex(
    VOS_UINT32                          ulFileIndex);

extern VOS_UINT32 USIMM_CCB_GetUsimOpenSpeed(VOS_VOID);

extern VOS_VOID USIMM_CCB_SetUsimOpenSpeed(
    VOS_UINT32                          ulStatus);

extern VOS_VOID USIMM_CCB_SetAIDByApp(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    VOS_UINT32                          ulDataLen,
    VOS_UINT8                           *pucAID);

extern USIMM_AID_INFO_STRU* USIMM_CCB_GetAIDByApp(
    USIMM_CARDAPP_ENUM_UINT32           enAppType);

extern VOS_VOID USIMM_CCB_ClearAIDFcp(
    VOS_UINT8                           ucChannelNo);

extern VOS_VOID USIMM_CCB_SetAIDFcp(
    VOS_UINT8                           ucChannelNo,
    VOS_UINT32                          ulFcpLen,
    VOS_UINT8                           *pucFcp);

extern VOS_VOID USIMM_CCB_ClearResponse(
    VOS_UINT8                           ucChannelNo);

extern VOS_VOID USIMM_CCB_SetResponse(
    VOS_UINT8                           ucChannelNo,
    VOS_UINT32                          ulRspLen,
    VOS_UINT8                           *pucRsp);

extern VOS_VOID USIMM_CCB_GetAIDFcp(
    VOS_UINT8                           ucChannelNo,
    VOS_UINT32                          *pulFcpLen,
    VOS_UINT8                           **ppucFcp);

extern VOS_VOID USIMM_CCB_GetResponse(
    VOS_UINT8                           ucChannelNo,
    VOS_UINT32                          *pulRspLen,
    VOS_UINT8                           **ppucRsp);


extern VOS_VOID  USIMM_T1InitGlobalVar(VOS_VOID);

extern VOS_VOID USIMM_ClearGlobalVar(VOS_VOID);

extern VOS_VOID USIMM_SetGlobalVarDefValue(VOS_VOID);

extern VOS_VOID USIMM_InitPoolGlobal(VOS_VOID);

extern VOS_VOID USIMM_InitConfigGlobal(VOS_VOID);

extern VOS_VOID USIMM_InitOpenSpeed(VOS_VOID);

extern VOS_VOID USIMM_ResetGlobalVar(VOS_VOID);

extern VOS_VOID USIMM_ResetGlobalVarWithCard(VOS_VOID);


extern VOS_VOID USIMM_COMM_ClearAppInfoGlobal(VOS_VOID);

extern VOS_VOID USIMM_COMM_ClearInitCtrlGlobal(VOS_VOID);

extern VOS_VOID USIMM_COMM_InitCommFuncTble(VOS_VOID);

extern VOS_VOID USIMM_COMM_ResetInitListStatus(VOS_VOID);

extern VOS_VOID USIMM_SetTimeOutFlag(
    VOS_BOOL                            bFlag);

extern VOS_BOOL USIMM_GetTimeOutFlag(VOS_VOID);

extern USIMMDL_ERROR_ENUM_UINT32 USIMM_GetT0DLErrorInfo(VOS_VOID);


#else

extern VOS_VOID  USIMM_T1InitGlobalVar(VOS_VOID);

#endif

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of UsimmDL.h*/

