/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : Test_AtSetParaCmd.h
  版 本 号   : 初稿
  作    者   :
  生成日期   : 2012年5月17日
  最近修改   :
  功能描述   : Test_AtSetParaCmd.cpp 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年5月17日
    作    者   : l60609
    修改内容   : 创建文件

******************************************************************************/

#ifndef __TEST_ATSETPARACMD_H__
#define __TEST_ATSETPARACMD_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "AtDataProc.h"
#include "siappstk.h"
#include "AppVcApi.h"
#include "mdrv.h"
#include "ATCmdProc.h"
#include "AtCheckFunc.h"
#include "AtParseCmd.h"
#include "PppInterface.h"
#include "AtMsgPrint.h"
#include "Taf_MmiStrParse.h"
#include "siappstk.h"
#include "siapppih.h"
#include "siapppb.h"
#include "UsimPsInterface.h"
#include "MnCallApi.h"
#include "AtPhyInterface.h"
#include "TafAppMma.h"
#include "AtDataProc.h"
#include "TafApsApi.h"
#include "AtInputProc.h"
#include "TafDrvAgent.h"
#include "MnCommApi.h"
#include "Taf_Tafm_Remote.h"
#include "AtCmdMsgProc.h"
#include "MnCallApi.h"
#include "Taf_Tafm_Remote.h"
#include "UsimmApi.h"
#include "AtRabmInterface.h"
#include "AtSndMsg.h"
#include "AtDeviceCmd.h"
#include "AtRnicInterface.h"
#include "AtTafAgentInterface.h"
#include "TafAgentInterface.h"
#include "spysystem.h"

#if (FEATURE_ON==FEATURE_LTE)
#include "msp_nvim.h"
#include "msp_nv_id.h"
#include "msp_nv_def.h"
#include "at_common.h"
#endif

#include "phyoaminterface.h"

#if (FEATURE_ON == FEATURE_VSIM)
#include "AtCmdSimProc.h"
#endif
#if (FEATURE_ON==FEATURE_LTE)
#include "gen_msg.h"
#endif

#include "cpm.h"
#include "AtTestParaCmd.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
/*lint -e767 修改人:罗建 107747;检视人:孙少华65952;原因:Log打印*/
#define    THIS_FILE_ID        PS_FILE_ID_AT_SETPARACMD_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/


/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/
extern AT_PAR_CMD_ELEMENT_STRU              gstU2diagCmdInfo;

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
extern void UT_STUB_INIT(void);

extern VOS_UINT32  At_PidInit(enum VOS_INIT_PHASE_DEFINE enPhase);

extern VOS_UINT32 TAF_PS_SndMsg(
    VOS_UINT32                          ulTaskId,
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pData,
    VOS_UINT32                          ulLength
);

extern VOS_UINT32 AT_FillCalledNumPara(
    VOS_UINT8                          *pucAtPara,
    VOS_UINT16                          usLen,
    MN_CALL_CALLED_NUM_STRU            *pstCalledNum
);

extern VOS_UINT32 AT_FillApdsPara(
    VOS_UINT8                           ucIndex,
    MN_CALL_ORIG_PARAM_STRU            *pstOrigParam
);

#if(FEATURE_ON == FEATURE_LTE)
extern VOS_UINT32 AT_SetLIndCfgReq(VOS_UINT8 ucIndex,L4A_IND_CFG_STRU* pstIndCfgReq);
#endif

extern PPP_DIAL_ERR_CODE_ENUM           gucPppDialErrCodeRpt;

extern VOS_UINT32                              g_ulWifiMode;

extern VOS_BOOL                                g_bSetFlg;

extern VOS_VOID  AT_InitPort(VOS_VOID);

extern unsigned int AtBase64Decode(const void* pcode,const unsigned int code_size,void* out_pdata,
                                   const unsigned int data_size,unsigned int* out_pwrited_data_size);
extern VOS_VOID AtBase64Encode(const VOS_VOID* pdata,const VOS_UINT32 data_size,VOS_VOID* out_pcode);
extern VOS_UINT32 atQryCgeqosPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 atSetCgcontrdpPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 atSetCgeqosPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 atSetCgeqosrdpPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 atSetCgscontrdpPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 atSetCgtftrdpPara(VOS_UINT8 ucIndex);
extern TAF_VOID AtTmodShowDebug();
extern TAF_UINT32 At_AbortCmdProc(TAF_UINT8 ucIndex);
extern VOS_UINT32 AT_ActivateSSReq(
           TAF_UINT8                           ucIndex,
           TAF_SS_ERASESS_REQ_STRU             *pstActivateReq
       );
extern VOS_UINT32 AT_AppCheckDialParam(VOS_VOID);
extern VOS_UINT32 AT_AppCheckPdpStateForDial(VOS_VOID );
extern VOS_UINT32 AT_AppDialDownProc(
           VOS_UINT8                           ucIndex
       );
extern VOS_UINT32 AT_AppDialUpProc(
           VOS_UINT8                           ucIndex
       );
extern VOS_UINT8 AT_AppFindCidForDialDown();
extern VOS_VOID AT_AppReportPdpActiveState(
           VOS_UINT8                           ucIndex,
           AT_PDP_ENTITY_STRU                 *pstAppPdpEntity
       );
extern TAF_UINT32 At_AsciiNum2BcdNum (TAF_UINT8 *pucDst, TAF_UINT8 *pucSrc, TAF_UINT16 usSrcLen);
extern TAF_UINT32 At_AsciiNum2HexString(TAF_UINT8 *pucSrc, TAF_UINT16 *pusSrcLen);
extern TAF_UINT32 At_AsciiNum2Num (TAF_UINT8 *pucDst, TAF_UINT8 *pucSrc, TAF_UINT16 usSrcLen);
extern VOS_UINT32 At_AsciiNum2SimLockImsiStr (
           VOS_UINT8                           *pucDst,
           VOS_UINT8                           *pucSrc,
           VOS_UINT16                          usSrcLen
       );
extern TAF_UINT32 At_AsciiString2HexSimple(TAF_UINT8 *pTextStr,TAF_UINT8 *pucSrc,TAF_UINT16 usSrcLen);
extern TAF_UINT32 At_AsciiString2HexText(SI_STK_TEXT_STRING_STRU *pTextStr,TAF_UINT8 *pucSrc,TAF_UINT16 usSrcLen);
extern TAF_UINT32 At_ChangeCmdResult(TAF_UINT32 resultNo,TAF_UINT8 *cmdResult);
extern TAF_UINT32 At_ChangeSATCmdType(TAF_UINT32 cmdNo, TAF_UINT32 *CmdType);
extern VOS_VOID AT_ChangeSysCfgRatPrio(
           TAF_MMA_RAT_ORDER_STRU             *pstRatOrder,
           AT_SYSCFG_RAT_PRIO_ENUM_UINT8       enAcqorder

       );
extern VOS_UINT32 AT_CheckApnFirstAndLastChar(
           VOS_UINT8                           ucApnCharacter
       );
extern VOS_UINT32 AT_CheckApnFormat(
           VOS_UINT8                          *pucApn,
           VOS_UINT16                          usApnLen
       );
extern TAF_UINT32  At_CheckAtDPin(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_CheckCcfcParaValid( VOS_VOID  );
extern TAF_UINT32 At_CheckCpinPara();
extern TAF_UINT32 At_CheckDataState(TAF_UINT8 ucDataMode);
extern TAF_UINT32 At_CheckDialString(TAF_UINT8 *pData, TAF_UINT16 usLen);
extern VOS_VOID At_CheckDialStrPara(VOS_VOID);
extern VOS_UINT32 At_CheckDtmfPara();
extern VOS_UINT32 AT_CheckIpv6Capability(
    VOS_UINT8                           ucPdpType
    );
extern TAF_UINT32 At_CheckNameUCS2Code(TAF_UINT8 *pucData, TAF_UINT16 *pusLen);
extern VOS_UINT32  At_CheckNdisIpv4AddrPara(
           VOS_UINT8                          *pData,
           VOS_UINT16                          usLen);
extern TAF_UINT32  At_CheckNumLen(TAF_UINT16 usMax,TAF_UINT16 usLen);
extern TAF_UINT32 At_CheckPBString(TAF_UINT8 *pData, TAF_UINT16 *pusLen);
extern VOS_UINT32 AT_CheckPhonePhyNumPara(DRV_AGENT_PH_PHYNUM_TYPE_ENUM_UINT8 *penSetType);
extern VOS_UINT32 AT_CheckPhyNumPara(AT_PHYNUM_TYPE_ENUM_UINT32 *penSetType);
extern VOS_UINT32 AT_CheckPortTypePara(
           VOS_UINT8                           ucFirstParaCount,
           VOS_UINT8                          *pucFirstPort,
           VOS_UINT8                           ucSecParaCount,
           VOS_UINT8                          *pucSecPort
       );
extern VOS_UINT32 At_CheckRepeatedRatOrder(
           AT_SYSCFGEX_RAT_ORDER_STRU         *pstSyscfgExRatOrder
       );
extern VOS_UINT32 At_CheckRxDivOrRxPriCmdPara();
extern  VOS_UINT32 At_CheckRxdivOrRxpriParaIfSupported(
            VOS_UINT16                         *pusSetBands,
            VOS_UINT16                         usBands
        );

/* Modified by w00167002 for L-C互操作项目, 2014-2-17, begin */
extern VOS_UINT32 AT_CheckSysCfgExPara(
           TAF_MMA_SYS_CFG_PARA_STRU         *pstSysCfgExSetPara
       );
/* Modified by w00167002 for L-C互操作项目, 2014-2-17, end */
extern VOS_UINT32 At_CheckSysCfgExRatTypeValid(
           VOS_UINT8                           ucRatOrder
       );
extern TAF_UINT32  At_CheckUssdNumLen(
                                      VOS_UINT8                           ucIndex,
                                      TAF_SS_DATA_CODING_SCHEME           dcs,
                                      TAF_UINT16                          usLen
                                      );
extern VOS_UINT32 AT_CloseSpecificPort(VOS_UINT8 ucPort);
extern VOS_UINT32 AT_ConvertCpamRatOrderPara(
    VOS_UINT8                           ucClientId,
    MN_MMA_CPAM_RAT_TYPE_ENUM_UINT8     enMode,
    MN_MMA_CPAM_RAT_PRIO_ENUM_UINT8     enAcqorder,
    TAF_MMA_RAT_ORDER_STRU             *pstRatOrder,
    AT_SYSCFG_RAT_PRIO_ENUM_UINT8      *penSyscfgRatPrio
    );
extern VOS_UINT32  At_ConvertSDErrToAtErrCode(VOS_UINT32 ulSDOprtErr);
extern VOS_UINT32 AT_ConvertSysCfgExBandPara(
           VOS_UINT8                          *pucPara,
           VOS_UINT16                          usLen,
           TAF_USER_SET_PREF_BAND64           *pstPrefBandPara
       );
extern VOS_VOID At_ConvertSysCfgExRat(
                                      VOS_UINT8                           ucClientId,
                                      AT_SYSCFGEX_RAT_ORDER_STRU         *pstSysCfgExRatOrder,
                                      TAF_MMA_RAT_ORDER_STRU             *pstRatOrder
                                      );
extern VOS_UINT32 AT_ConvertSysCfgExRatOrderPara(
           TAF_MMA_RAT_ORDER_STRU             *pstSysCfgExRatOrder
       );
extern VOS_UINT32 AT_ConvertSysCfgRatOrderPara(
    VOS_UINT8                           ucClientId,
    AT_SYSCFG_RAT_TYPE_ENUM_UINT8       enRatMode,
    AT_SYSCFG_RAT_PRIO_ENUM_UINT8       enAcqorder,
    TAF_MMA_RAT_ORDER_STRU             *pstSysCfgRatOrder
);
extern VOS_UINT32 AT_CountSpecCharInString(
           VOS_UINT8                          *pucData,
           VOS_UINT16                          usLen,
           VOS_UINT8                           ucChar
       );
extern VOS_UINT32 At_CovertAtParaToSimlockPlmnInfo(
           VOS_UINT32                          ulParaCnt,
           AT_PARSE_PARA_TYPE_STRU             *pstParalist,
           TAF_CUSTOM_SIM_LOCK_PLMN_INFO_STRU  *pstSimLockPlmnInfo
       );
extern VOS_UINT32 At_CovertUserSetRxDivOrRxPriParaToMsInternal(
           VOS_UINT32 ulSetDivLowBands,
           VOS_UINT32 ulSetDivHighBands,
           VOS_UINT16 *pusSetDivBands
                       );
extern TAF_UINT32  At_CrsmApduParaCheck(VOS_VOID);
extern TAF_UINT32  At_CrsmFilePathCheck(TAF_UINT16 usEfId, TAF_UINT8 *pucFilePath, TAF_UINT16 *pusPathLen);
extern TAF_UINT32 At_CrsmFilePathParse(TAF_SIM_RESTRIC_ACCESS_STRU *pstCommand);
extern VOS_UINT32 At_CrsmParaGetRspCheck(TAF_SIM_RESTRIC_ACCESS_STRU *pstCommand);
extern TAF_UINT32 At_CrsmParaReadBinaryCheck (TAF_SIM_RESTRIC_ACCESS_STRU *pstCommand);
extern TAF_UINT32 At_CrsmParaReadRecordCheck(TAF_SIM_RESTRIC_ACCESS_STRU *pstCommand);
extern TAF_UINT32 At_CrsmParaStatusCheck (TAF_SIM_RESTRIC_ACCESS_STRU *pstCommand);
extern VOS_UINT32 At_CrsmParaUpdateBinaryCheck (TAF_SIM_RESTRIC_ACCESS_STRU *pstCommand);
extern VOS_UINT32 At_CrsmParaUpdateRecordCheck (TAF_SIM_RESTRIC_ACCESS_STRU *pstCommand);
extern PPP_AUTH_TYPE_ENUM_UINT8 AT_CtrlGetPDPAuthType(
           VOS_UINT32                          Value,
           VOS_UINT16                          usTotalLen
       );
extern VOS_UINT32 AT_DeactivateSSReq(
           TAF_UINT8                           ucIndex,
           TAF_SS_ERASESS_REQ_STRU             *pstEraseReq
       );
extern VOS_UINT32 AT_DecodeFacAuthPubkeyPara(AT_FACAUTHPUBKEY_SET_REQ_STRU *pstFacAuthPubKey);
extern VOS_UINT32 At_DialNumByIndexFromPb(VOS_UINT8              ucIndex,
                                                   SI_PB_EVENT_INFO_STRU  *pEvent);
extern VOS_UINT32 AT_DialProc(
           VOS_UINT8                           ucIndex
       );
extern VOS_UINT32 AT_EraseSSReq(
           TAF_UINT8                           ucIndex,
           TAF_SS_ERASESS_REQ_STRU             *pstEraseSSReq
       );
extern VOS_UINT32 AT_FillTftIpAddr(
           VOS_UINT8                          *pData,
           VOS_UINT16                          usLen,
           TAF_TFT_EXT_STRU                   *pstTftInfo
       );
extern VOS_UINT32 AT_FillTftIpv4Addr(
           VOS_UINT8                          *pucData,
           VOS_UINT16                          usLen,
           TAF_TFT_EXT_STRU                   *pstTftInfo
       );
extern VOS_UINT32 AT_FillTftIpv6Addr(
           VOS_UINT8                          *pucData,
           VOS_UINT16                          usLen,
           TAF_TFT_EXT_STRU                   *pstTftInfo
       );
extern VOS_BOOL At_FistScanSetPortPara(
           VOS_UINT16                          *pusSemiIndex,
           VOS_UINT8                           *pucInputString,
           VOS_UINT16                          usInputLen
       );
extern VOS_UINT32 AT_GetAppDialParam(
           TAF_PS_DIAL_PARA_STRU              *pstDialParaInfo
       );
extern TAF_UINT32 At_GetBandPara(TAF_UINT8 *nptr,TAF_UINT16 usLen,TAF_USER_SET_PREF_BAND64 * pStBand);
extern TAF_UINT8 At_GetDspLoadMode(VOS_UINT32 ulRatMode);
extern VOS_VOID AT_GetGuAccessPrioNvim (
                                        MODEM_ID_ENUM_UINT16                enModemId,
                                        AT_SYSCFG_RAT_PRIO_ENUM_UINT8      *penAcqorder
                                        );
extern TAF_UINT32  At_GetMeanRpt( TAF_UINT8 ucIndex );
extern VOS_UINT32 AT_GetNdisDialParam(
           TAF_PS_DIAL_PARA_STRU              *pstDialParaInfo
       );
extern VOS_UINT32 AT_GetOperatorNameFromParam(
           VOS_UINT16                         *usOperNameLen,
           VOS_CHAR                           *pucOperName,
           VOS_UINT16                          usBufSize,
           VOS_UINT32                          ulFormatType
       );
extern VOS_UINT32  At_GetParaCnt(
           VOS_UINT8                           *pucData,
           VOS_UINT16                          usLen
       );
extern VOS_VOID AT_GetRatOrderNvim(
                                   MODEM_ID_ENUM_UINT16                enModemId,
                                   TAF_MMA_RAT_ORDER_STRU             *pstSysCfgRatOrder,
                                   VOS_UINT8                           ucUserSptLteFlag
                                   );
extern VOS_UINT32 At_GetSmsStorage(
           VOS_UINT8                           ucIndex,
           MN_MSG_MEM_STORE_ENUM_U8            enMemReadorDelete,
           MN_MSG_MEM_STORE_ENUM_U8            enMemSendorWrite,
           MN_MSG_MEM_STORE_ENUM_U8            enMemRcv
       );
extern TAF_SS_CODE AT_GetSsCodeFromCfccPara( VOS_VOID  );
extern VOS_UINT32 At_GetTmodeFromNV();
extern VOS_UINT32 At_GetUserSetRxDivOrRxPriParaNum(
                       VOS_UINT32      *pulSetDivLowBands,
                       VOS_UINT32      *pulSetDivHighBands
                       );
extern TAF_UINT32 At_Gsm7BitFormat(TAF_UINT8   *pucSrc,
                                   TAF_UINT16  usSrcLen,
                                   TAF_UINT8   *pucDst,
                                   TAF_UINT8   *pucDstLen);
extern VOS_UINT32  AT_InterrogateSSReq(
           TAF_UINT8                           ucIndex,
           TAF_SS_ERASESS_REQ_STRU             *pstInterrogateReq
       );
extern VOS_BOOL At_IsArrayContentValueEquToPara(
           VOS_UINT8                           ucValue,
           VOS_UINT32                          ulArrLen,
           VOS_UINT8                           aucContent[]
        );
extern VOS_BOOL At_IsAvailableSetPortPara(
           VOS_UINT8                           *pucInputString,
           VOS_UINT16                          usInputLen,
           VOS_UINT8                           *pucFirstPort,
           VOS_UINT8                           *pucSecPort
       );
extern VOS_UINT32 AT_IsSupportGMode(
           TAF_MMA_RAT_ORDER_STRU             *pstRatOrder
       );
extern VOS_UINT32 AT_IsSupportLMode(
           TAF_MMA_RAT_ORDER_STRU             *pstRatOrder
       );
extern VOS_UINT32 AT_IsSupportWMode(
           TAF_MMA_RAT_ORDER_STRU             *pstRatOrder
       );
extern VOS_UINT8 At_JudgeIfIsPsCall(VOS_VOID);
extern VOS_UINT32 AT_NdisCheckActingStateForDial(VOS_VOID );
extern VOS_UINT32 AT_NdisDialDownProc(
           VOS_UINT8                           ucIndex
       );
extern VOS_UINT32 AT_NdisDialUpProc(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_NdisDupProc(VOS_UINT8 ucIndex);
extern VOS_UINT8 AT_NdisFindCidForDialDown(VOS_VOID);
extern VOS_UINT32  At_NdisIpv4AddParaProc(
           VOS_UINT8                          *pData,
           VOS_UINT16                          usLen,
           VOS_UINT8                          *pDesData,
           VOS_UINT32                         *pulFlag
       );
extern VOS_UINT32 AT_NidsCheckDialParam(VOS_VOID);
extern TAF_UINT32 At_OneUnicodeToGsm(TAF_UINT16 usSrc, TAF_UINT8 *pucDst, TAF_UINT16 *pusDstLen);
extern VOS_UINT32 AT_OpenSpecificPort(VOS_UINT8 ucPort);
extern VOS_UINT32 AT_ParseCbParm(
           VOS_UINT8                           *pucInPara,
           TAF_CBA_CBMI_RANGE_LIST_STRU              *pstCbRange
       );
extern TAF_BOOL At_ParseChldPara(
           TAF_UINT32                          ulParaValue,
           MN_CALL_SUPS_PARAM_STRU            *pstCallSupsCmd
           );
extern TAF_BOOL At_ParseSingleChldPara(
           TAF_UINT32                          ulParaValue,
           MN_CALL_SUPS_PARAM_STRU            *pstCallSupsCmd
           );
extern TAF_UINT32 At_PbAlphaTagProc(SI_PB_RECORD_STRU *pstRecord, AT_PARSE_PARA_TYPE_STRU stAtParaList);
extern TAF_UINT32 At_PbDeleteProc(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_PbEmailTransferToGsm(TAF_UINT8  *pucSrc,
                                          TAF_UINT16 usSrcLen,
                                          TAF_UINT8  *pucDst,
                                          TAF_UINT16 *pusDstLen);
extern TAF_VOID At_PbIraToUnicode(TAF_UINT8  *pucSrc,
                                  TAF_UINT16 usSrcLen,
                                  TAF_UINT8  *pucDst,
                                  TAF_UINT16 *pusDstLen);
extern TAF_VOID At_PbUnicodeParse(TAF_UINT8  *pucSrc,
                                  TAF_UINT16 usSrcLen,
                                  TAF_UINT32 *pulAlphaTagType,
                                  TAF_UINT16 *pusDstLen,
                                  TAF_UINT16 *pusCodeBase);
extern TAF_UINT32 At_PbUnicodeTransfer(TAF_UINT8           *pucSrc,
                                       TAF_UINT16          usSrcLen,
                                       SI_PB_RECORD_STRU   *pstRecord,
                                       TAF_UINT16          usCodeBase);
extern VOS_VOID AT_PhSendRestoreFactParm( VOS_VOID );
extern VOS_VOID AT_PhSendRestoreFactParmNoReset( VOS_VOID );
extern VOS_UINT32  AT_PhyNumIsNull(
                                   MODEM_ID_ENUM_UINT16                enModemId,
                                   AT_PHYNUM_TYPE_ENUM_UINT32          enSetType,
                                   VOS_BOOL                           *pbPhyNumIsNull
                                   );
extern TAF_UINT32 At_PortSwitchSndMsg (TAF_UINT32 ulSwitchMode);
extern VOS_VOID AT_PrintWifibPowerInfo(
           AT_WIFI_INFO_STRU                  *pstWifiInfo,
           VOS_UINT8                           ucWifiMode,
           VOS_UINT8                           ucIndex
       );
extern VOS_VOID AT_PrintWifiChannelInfo(
           AT_WIFI_INFO_STRU                  *pstWifiInfo,
           VOS_UINT8                           ucIndex
       );
extern VOS_VOID AT_PrintWifigPowerInfo(
           AT_WIFI_INFO_STRU                  *pstWifiInfo,
           VOS_UINT8                           ucWifiMode,
           VOS_UINT8                           ucIndex
       );
extern VOS_VOID AT_PrintWifinPowerInfo(
           AT_WIFI_INFO_STRU                  *pstWifiInfo,
           VOS_UINT8                           ucWifiMode,
           VOS_UINT8                           ucIndex
       );
extern VOS_VOID AT_PrintWifiPowerInfo(
           AT_WIFI_INFO_STRU                  *pstWifiInfo,
           VOS_UINT8                           ucIndex
       );
extern VOS_UINT32 AT_ProcCscbWithParm(
           TAF_UINT8                           ucIndex,
           TAF_CBA_CBMI_RANGE_LIST_STRU              *pstCbmirList
       );

extern TAF_UINT32  At_PsDPara(TAF_UINT8 ucIndex);
extern VOS_UINT32 AT_ReadActiveMessage(
                                       MODEM_ID_ENUM_UINT16                enModemId,
                                       MN_MSG_ACTIVE_MESSAGE_STRU         *pstActiveMessage
                                       );
extern VOS_VOID AT_ReadRoamCfgInfoNvim(VOS_VOID);
extern VOS_UINT32 AT_ReadValueFromNvim(const NV_ID_ENUM_U16 enNVItemType,
                                                VOS_VOID *pData, VOS_UINT32 usDataLen);
extern VOS_UINT32 AT_RegisterSSReq(
           TAF_UINT8                           ucIndex,
           TAF_SS_REGISTERSS_REQ_STRU          *pstRegisterReq
       );
extern VOS_UINT32 AT_RsfrSimLockProc(VOS_UINT8* pgcSrcData, VOS_UINT16* pusLen);
extern VOS_VOID AT_RsfwSimLockProc(VOS_UINT8 *pucData, VOS_UINT16 usLen);
extern VOS_UINT32 At_SaveRxDivPara(
               VOS_UINT16                      usSetDivBands,
               VOS_UINT8                       ucRxDivCfg
               );
extern VOS_BOOL At_SaveSetPortFirstPara(
           VOS_UINT8                           ucFirstParaCount,
           VOS_UINT8                           *pucFirstPort,
           VOS_UINT8                           *pucInputString
       );
extern VOS_BOOL At_SaveSetPortSecPara(
           VOS_UINT8                           ucSecParaCount,
           VOS_UINT8                           *pucSecPort,
           VOS_UINT8                           aucSecPara[AT_SETPORT_PARA_MAX_LEN][3]
       );
extern VOS_UINT32 At_SDOprtRead(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_SDOprtWrtEraseFmt(TAF_UINT8 ucIndex);
extern VOS_BOOL At_SecScanSetPortFirstPara(
           VOS_UINT16                          usSemiIndex,
           VOS_UINT8                           *pucFirstParaCount,
           VOS_UINT8                           *pucInputString,
           VOS_UINT16                          usInputLen
       );
extern VOS_BOOL At_SecScanSetPortSecPara(
           VOS_UINT16                          usSemiIndex,
           VOS_UINT8                           *pucSecParaCount,
           VOS_UINT8                           aucSecPara[AT_SETPORT_PARA_MAX_LEN][3],
           VOS_UINT8                           *pucInputString,
           VOS_UINT16                          usInputLen
       );
extern VOS_UINT32  At_SendContinuesWaveOnToHPA(
           VOS_UINT8                           ucCtrlType,
           VOS_UINT16                          usPower
       );
extern VOS_UINT32  At_SendRxOnOffToGHPA(
                                        VOS_UINT8                           ucIndex,
                                        VOS_UINT32                          ulRxSwitch
                                        );
extern VOS_UINT32 At_SendRxOnOffToHPA(
           VOS_UINT32                          ulRxSwitch
       );
extern VOS_UINT32  At_SendTxOnOffToGHPA(
                                        VOS_UINT8                           ucIndex,
                                        VOS_UINT8                           ucSwitch
                                        );
extern TAF_UINT32  At_SendTxOnOffToHPA(TAF_UINT8 ucSwitch);
extern TAF_UINT32 At_SetAdcTempPara(TAF_UINT8 ucIndex);
extern VOS_UINT32  AT_SetAlsPara( TAF_UINT8 ucIndex );
extern TAF_UINT32 At_SetAmpCPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetAmpDPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetAmpSPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetAPara(TAF_UINT8 ucIndex);
extern VOS_UINT32 AT_SetApbatlvlPara( VOS_UINT8 ucIndex );
extern VOS_UINT32 At_SetAppDialModePara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetApRptPortSelectPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetApRptSrvUrlPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetApXmlInfoTypePara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetApXmlRptFlagPara(VOS_UINT8 ucIndex);
extern TAF_UINT32 At_SetAt2OmPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetAuthdataPara (TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetAutoAttach(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetBOOTPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetBsn(TAF_UINT8 ucIndex);
extern VOS_UINT32 At_SetCallSrvPara(VOS_UINT8 ucIndex);
extern TAF_UINT32 At_SetCardlockPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCardModePara(TAF_UINT8 ucIndex);
extern VOS_UINT32 At_SetCbcPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_SetCbndPara(VOS_UINT8 ucIndex);
extern TAF_UINT32 At_SetCbstPara(TAF_UINT8 ucIndex);
extern VOS_UINT32  AT_SetCccPara( TAF_UINT8 ucIndex );
extern TAF_UINT32 At_SetCcfcPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetCcinPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetCcugPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetCcwaPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetCdtmfePara(
           TAF_UINT8                           ucIndex
       );
extern TAF_UINT32 At_SetCdtmfsPara(
           TAF_UINT8                           ucIndex
       );
extern VOS_UINT32 AT_SetCdurPara(VOS_UINT8 ucIndex);
extern TAF_UINT32 At_SetCeerPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetCellInfoPara(TAF_UINT8 ucIndex);
extern VOS_UINT32 At_SetCellSearch(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetCeregPara(VOS_UINT8 ucIndex);
extern TAF_UINT32 At_SetCfunPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 AT_SetCgactPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 AT_SetCgansPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetCGasPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetCgattPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 AT_SetCgautoPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetCgcattPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetCgclassPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 AT_SetCgcmodPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetCgdataPara(TAF_UINT8 ucIndex);
extern VOS_UINT32 AT_SetCgdcontPara(VOS_UINT8 ucIndex);
extern TAF_UINT32 AT_SetCgdnsPara(TAF_UINT8 ucIndex);
extern VOS_UINT32 AT_SetCgdscontPara(VOS_UINT8 ucIndex);
extern TAF_UINT32 AT_SetCgeqminPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 AT_SetCgeqnegPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 AT_SetCgeqreqPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetCgmiPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetCgmmPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetCgmrPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 AT_SetCgpaddrPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetCgregPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetCgsmsPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetCgsnPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 AT_SetCgtftPara(TAF_UINT8 ucIndex);
extern VOS_UINT32 AT_SetChdataPara(VOS_UINT8 ucIndex);
extern TAF_UINT32 At_SetChldPara(TAF_UINT8 ucIndex);
extern VOS_UINT32 AT_SetChrgEnablePara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_SetChupPara(VOS_UINT8 ucIndex);
extern TAF_UINT32 At_SetCimiPara(TAF_UINT8 ucIndex);
extern VOS_UINT32 At_SetCLACPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_SetClccPara(VOS_UINT8 ucIndex);
extern TAF_UINT32 At_SetClckPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetClipPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetClirPara(TAF_UINT8 ucIndex);
extern VOS_UINT32 At_SetClvlPara(VOS_UINT8 ucIndex);
extern TAF_UINT32 At_SetCmeePara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetCmgcPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetCmgdPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetCmgfPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetCmgiPara (TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetCmglPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetCmgrPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetCmgsPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetCmgwPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetCmlckPara (TAF_UINT8 ucIndex);
extern VOS_UINT32 At_SetCmmiPara(VOS_UINT8 ucIndex);
extern TAF_UINT32   At_SetCmmPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetCmmsPara(
           TAF_UINT8                           ucIndex
       );
extern TAF_UINT32 At_SetCmmtPara (TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetCmodPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetCmsrPara (TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetCmssPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetCmstPara(TAF_UINT8 ucIndex);
extern VOS_UINT32 At_SetCmStubPara(VOS_UINT8 ucIndex);
extern TAF_UINT32 At_SetCnmaPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetCnmiPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetCnumPara(TAF_UINT8 ucIndex);
extern VOS_UINT32 At_SetColpPara(VOS_UINT8 ucIndex);
extern TAF_UINT32 At_SetCommDebugPara(TAF_UINT8 ucIndex);
extern VOS_VOID At_SetCopsActPara(
           TAF_MMA_RAT_TYPE_ENUM_UINT8        *penPhRat,
           VOS_UINT16                          usParaLen,
           VOS_UINT32                          ulParaValue
       );
extern VOS_UINT32 At_SetCopsPara(TAF_UINT8 ucIndex);
extern VOS_UINT32 At_SetCpamPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_SetCpasPara(VOS_UINT8 ucIndex);
extern TAF_UINT32 At_SetCpbfPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetCpbr2Para(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetCpbrPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetCpbsPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetCpbwPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetCpbwPara2(TAF_UINT8 ucIndex);
extern VOS_UINT32 At_SetCpdwPara(VOS_UINT8 ucIndex);
extern TAF_UINT32 At_SetCpin2Para(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetCpinPara(TAF_UINT8 ucIndex);
extern VOS_UINT32 At_SetCplsPara(VOS_UINT8 ucIndex);
extern TAF_UINT32 At_SetCpmsPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetCPNNPara(TAF_UINT8 ucIndex);
extern VOS_UINT32 At_SetCpolPara(VOS_UINT8 ucIndex);
extern TAF_UINT32 At_SetCpwdPara(TAF_UINT8 ucIndex);
extern VOS_UINT32 AT_SetCpwordPara ( VOS_UINT8  ucIndex );
extern TAF_UINT32 At_SetCrcPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetCregPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetCrpnPara (TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetCrsmPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetCscaPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetCscbPara(
           TAF_UINT8                           ucIndex
       );
extern TAF_UINT32 At_SetCscsPara(TAF_UINT8 ucIndex);
extern VOS_UINT32 At_SetCsdfltPara(VOS_UINT8 ucIndex);
extern TAF_UINT32 At_SetCsdhPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetCsenPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetCsimPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetCsmnPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetCsmpPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetCsmsPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetCsndPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetCSNR(TAF_UINT8 ucIndex);
extern VOS_UINT32  AT_SetCsqlvlExtPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetCsqlvlPara( VOS_UINT8 ucIndex );
extern TAF_UINT32 At_SetCsqPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetCssnPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetCstaPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetCstcPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetCstrPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetCtfrPara(TAF_UINT8 ucIndex);
extern TAF_UINT32  At_SetCtzrPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetCurcPara(TAF_UINT8 ucIndex);
extern VOS_UINT32 At_SetCusdPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_SetCustomizeItemToDefaultVal(
           AT_CUSTOMIZE_ITEM_DFLT_ENUM_UINT8   enCustomizeItem
       );
extern VOS_UINT32 At_SetCuus1Para(
           VOS_UINT8                           ucIndex
       );
extern VOS_UINT32   At_SetCvoicePara (VOS_UINT8 ucIndex);
extern TAF_UINT32 At_SetCwasPara(TAF_UINT8 ucIndex);
extern VOS_UINT32  At_SetDataLock(VOS_UINT8 ucIndex );
extern VOS_UINT32 At_SetDdsetexPara (VOS_UINT8 ucIndex);
extern VOS_VOID AT_SetDefaultRatPrioList(
           MODEM_ID_ENUM_UINT16                enModemId,
           TAF_MMA_RAT_ORDER_STRU             *pstSysCfgRatOrder,
           VOS_UINT8                           ucUserSptLteFlag
       );
extern TAF_UINT32 At_SetDhcpPara (TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetDial98Para(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetDial99Para(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetDialGprsPara(
           TAF_UINT8                           ucIndex,
           TAF_UINT8                           ucCid,
           TAF_GPRS_ACTIVE_TYPE_UINT8          enActiveType
       );
extern TAF_VOID At_SetDialIGPara(TAF_UINT8 ucIndex,TAF_UINT8 ucParaIndex,TAF_UINT8 *pClir, MN_CALL_CUG_CFG_STRU *pstCcug);
extern TAF_UINT32   At_SetDialModePara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetDialNumPara(TAF_UINT8 ucIndex,MN_CALL_TYPE_ENUM_U8 CallType);
extern TAF_UINT32 At_SetDialVoiceIndexPara(TAF_UINT8 ucIndex, MN_CALL_TYPE_ENUM_U8 enCallType);
extern TAF_UINT32 At_SetDialVoiceMemPara(TAF_UINT8 ucIndex, MN_CALL_TYPE_ENUM_U8 CallType);
extern TAF_UINT32 At_SetDialVoiceNamePara(TAF_UINT8 ucIndex,MN_CALL_TYPE_ENUM_U8 CallType);
extern VOS_UINT32 AT_SetDislogPara ( VOS_UINT8 ucIndex );
extern TAF_UINT32 At_SetDMmiNumWithClirPara(
           TAF_UINT8                         ucIndex,
           MN_CALL_CLIR_CFG_ENUM_U8          enClirType,
           TAF_INT8                         *pcStrNum,
           TAF_UINT32                        ulStrLen
       );
extern TAF_UINT32 At_SetDMmiPara(TAF_UINT8 ucIndex);
extern VOS_UINT32  At_SetDnsPrim(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetDnsQueryPara(VOS_UINT8 ucIndex);
extern VOS_UINT32  At_SetDnsSnd(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetDockPara (VOS_UINT8 ucIndex);
extern VOS_UINT32   At_SetDpaCat(VOS_UINT8 ucIndex);
extern TAF_UINT32 At_SetDPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 AT_SetDsFlowClrPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 AT_SetDsFlowQryPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 AT_SetDsFlowRptPara(TAF_UINT8 ucIndex);
extern VOS_UINT32 At_SetDtmfPara(VOS_UINT8 ucIndex);
extern TAF_UINT32 AT_SetDwinsPara(TAF_UINT8 ucIndex);
extern VOS_UINT32 AT_SetEcioCfgPara ( VOS_UINT8 ucIndex );
extern TAF_UINT32 At_SetEPara(TAF_UINT8 ucIndex);
extern VOS_UINT32 AT_SetFacAuthPubkeyPara(
           VOS_UINT8                           ucIndex,
           AT_FACAUTHPUBKEY_SET_REQ_STRU      *pstFacAuthPubKey
       );
extern VOS_UINT32 AT_SetFacInfoPara(
           VOS_UINT8                          ucIndex
       );
extern VOS_UINT32 AT_SetFastDormPara(VOS_UINT8 ucIndex);
extern TAF_UINT32  At_SetFChanPara(TAF_UINT8 ucIndex );
extern TAF_UINT32  AT_SetFDac(TAF_UINT8 ucIndex );
extern VOS_UINT32 At_SetFHVerPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_SetFlnaPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_SetFpaPara(VOS_UINT8 ucIndex);
extern TAF_UINT32 At_SetFPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetFPlmnPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetFreqLock(TAF_UINT8 ucIndex);
extern VOS_UINT32  At_SetFRxonPara(VOS_UINT8 ucIndex);
extern TAF_UINT32  At_SetFTxonPara(TAF_UINT8 ucIndex );
extern VOS_UINT32 AT_SetFwavePara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_SetGcapPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetGcfIndPara (TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetGetportmodePara (TAF_UINT8 ucIndex);
extern VOS_UINT32  At_SetGlastErrPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetGodloadPara( VOS_UINT8 ucIndex );
extern VOS_UINT32 At_SetGpioPara (VOS_UINT8 ucIndex);
extern VOS_UINT32 At_SetGPIOPL(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetGTimerPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_SetHPara(VOS_UINT8 ucIndex);
extern TAF_UINT32 At_SetHSPara(TAF_UINT8 ucIndex);
extern VOS_UINT32   At_SetHspaSpt(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetHukPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_SetHwVerPara(VOS_UINT8 ucIndex);
extern TAF_UINT32 At_SetIccidPara(TAF_UINT8 ucIndex);
extern VOS_UINT32 AT_SetIdentifyEndPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetIdentifyStartPara(VOS_UINT8 ucIndex);
extern TAF_UINT32 At_SetImeiPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetImsichgPara(TAF_UINT8 ucIndex);
extern VOS_UINT32  At_SetInfoRBU(VOS_UINT8 ucIndex );
extern VOS_UINT32  At_SetInfoRRS(VOS_UINT8 ucIndex );
extern VOS_UINT32 At_SetMaxLockTimes(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetMDatePara(
           VOS_UINT8                           ucIndex
       );
extern VOS_UINT32 AT_SetMemInfoPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetMemStatusPara(VOS_UINT8 ucIndex);
extern TAF_UINT32 At_SetModePara(TAF_UINT8 ucIndex);
extern VOS_UINT32 At_SetMsIdInfo(TAF_UINT8 ucIndex);
extern VOS_UINT32  At_SetNdisAddPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetNdisdupPara (VOS_UINT8 ucIndex);
extern TAF_UINT32 At_SetNumTypePara(TAF_UINT8 *pucDst, TAF_UINT8 *pucSrc, TAF_UINT16 usSrcLen);
extern VOS_UINT32 AT_SetNvBackUpPara( VOS_UINT8 ucIndex );
extern VOS_UINT32 AT_SetNvimPara ( VOS_UINT8 ucIndex );
extern VOS_UINT32 At_SetNvRestorePara( VOS_UINT8 ucIndex );
extern VOS_UINT32  AT_SetNvRststtsPara( VOS_UINT8 ucIndex );
extern VOS_UINT32 AT_SetOpenportPara( VOS_UINT8 ucIndex );
extern TAF_UINT32 At_SetOPLPara (TAF_UINT8 ucIndex);
extern VOS_UINT32 AT_SetOpwordPara ( VOS_UINT8  ucIndex );
extern VOS_UINT32 AT_SetOpwordParaForApModem ( VOS_UINT8  ucIndex );
extern TAF_UINT32 At_SetParaCmd(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetPcscInfo(TAF_UINT8 ucIndex);
extern VOS_UINT32 AT_SetPdprofmodPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetPdpStub( VOS_UINT8 ucIndex );
extern VOS_UINT32 At_SetPfverPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetPhonePhynumPara(VOS_UINT8 ucIndex);
extern VOS_UINT32  AT_SetPhyNumPara(VOS_UINT8 ucIndex);
extern TAF_UINT32 At_SetpidPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetPNNPara(TAF_UINT8 ucIndex);
extern VOS_UINT32 At_SetPort(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetPortAttribSetPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetPortCtrlTmpPara(VOS_UINT8 ucIndex);
extern TAF_UINT32   At_SetPortSelPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetPPara(TAF_UINT8 ucIndex);
extern VOS_UINT32 AT_SetProdNamePara(VOS_UINT8 ucIndex);
extern TAF_UINT32 At_SetQcdmgPara(TAF_UINT8 ucIndex);
extern VOS_UINT32   At_SetQosPara(VOS_UINT8 ucIndex);
extern TAF_UINT32 At_SetQPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetQuickStart(TAF_UINT8 ucIndex);
extern VOS_UINT32 At_SetResetPara( VOS_UINT8 ucIndex  );
extern VOS_UINT32  AT_SetRplmnStub( VOS_UINT8 ucIndex );
extern TAF_UINT32 At_SetRRCVersion(TAF_UINT8 ucIndex);
extern VOS_UINT32 AT_SetRscpCfgPara ( VOS_UINT8 ucIndex );
extern VOS_UINT32 AT_SetRsfrPara(VOS_UINT8 ucIndex);
extern VOS_VOID AT_SetRsfrVersionCnf(VOS_UINT8 ucIndex, VOS_UINT8* pucData, VOS_UINT32 ulLen);
extern VOS_UINT32 AT_SetRsfwPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetRsrpCfgPara ( VOS_UINT8 ucIndex );
extern TAF_UINT32 At_SetRssiPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 AT_SetRstriggerPara(
           TAF_UINT8                           ucIndex
       );
extern VOS_UINT32 At_SetRxDiv(VOS_UINT8 ucIndex);
extern TAF_UINT32 At_SetS0Para(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetS3Para(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetS4Para(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetS5Para(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetS6Para(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetS7Para(TAF_UINT8 ucIndex);
extern VOS_UINT32 AT_SetSARReduction(VOS_UINT8 ucIndex);
extern TAF_UINT32 At_SetScidPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetScpbrPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetScpbwPara(TAF_UINT8 ucIndex);
extern VOS_UINT32  At_SetSD(VOS_UINT8 ucIndex);
extern VOS_UINT32  AT_SetSdloadPara(VOS_UINT8 ucIndex);
extern VOS_UINT32   At_SetSDomainPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_SetSecuBootPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_SetSfm(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetShellPara ( VOS_UINT8 ucIndex );
extern VOS_UINT32 AT_SetSimlockDataWritePara(
           VOS_UINT8                           ucIndex,
           AT_SIMLOCKDATAWRITE_SET_REQ_STRU   *pstSimlockDataWrite
       );
extern VOS_UINT32 At_SetSimLockPlmnInfo(
           VOS_UINT8                           ucIndex,
           VOS_UINT32                          ulParaCnt,
           AT_PARSE_PARA_TYPE_STRU             *pstParalist
       );
extern TAF_UINT32 At_SetSimstPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetSnPara(TAF_UINT8 ucIndex);
extern TAF_UINT32   At_SetSPNPara(TAF_UINT8 ucIndex);
extern VOS_UINT32 AT_SetSpwordPara(VOS_UINT8 ucIndex);
extern TAF_UINT32 At_SetSrvstPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetStgiPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetStgrPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetStsfPara(TAF_UINT8 ucIndex);
extern VOS_VOID AT_SetSubAddrAttribute(
           TAF_SS_SUBADDRTYPE                  *pSubAddrType,
           TAF_UINT8                           *pucFwdToSubAddr
       );
extern VOS_UINT32 AT_SetSysCfgExPara(
           VOS_UINT8                           ucIndex
       );
extern VOS_UINT32 At_SetSysCfgPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_SetSystemInfo(TAF_UINT8 ucIndex);
extern VOS_UINT32 At_SetSystemInfoEx(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetTestPara(TAF_UINT8 ucIndex);
extern VOS_UINT32 AT_SetTestScreenPara(VOS_UINT8 ucIndex);
extern TAF_UINT32  At_SetTimePara(TAF_UINT8 ucIndex);
extern VOS_UINT32 AT_SetTmmiPara(VOS_UINT8 ucIndex);
extern TAF_UINT32  At_SetTModePara(TAF_UINT8 ucIndex );
extern TAF_UINT32 At_SetTPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetTrigPara (TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetU2DiagPara(TAF_UINT8 ucIndex);
extern VOS_UINT32 At_SetUsbSwitchPara (VOS_UINT8 ucIndex);
extern TAF_UINT32 AT_SetUSIMPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetUssdModePara(TAF_UINT8 ucIndex);
extern VOS_UINT32 AT_SetVertime ( VOS_UINT8 ucIndex );
extern VOS_UINT32 At_SetVMSETPara(VOS_UINT8 ucIndex);
extern TAF_UINT32 At_SetVPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetVtsPara(TAF_UINT8 ucIndex);
extern VOS_UINT32 AT_SetWebPwdPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetWiFiBandPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetWiFiEnablePara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetWiFiFreqPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetWifiGlobalMacPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetWifiInfoPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetWiFiKeyPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetWiFiLogPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetWiFiModePara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetWiFiPacketPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetWifiPaRangePara (VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetWiFiPowerPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetWiFiRatePara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetWiFiRxPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetWiFiSsidPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetWiFiTxPara(VOS_UINT8 ucIndex);
extern TAF_UINT32 At_SetXPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetYjcxPara (TAF_UINT8 ucIndex);
extern TAF_UINT32 At_SetZPara(TAF_UINT8 ucIndex);
extern VOS_VOID AT_ShowCccRst(
           NAS_CC_STATE_INFO_STRU              *pstCcState,
           VOS_UINT16                          *pusLength
       );
extern TAF_UINT32 At_SsPrint2Class(TAF_SS_BASIC_SERVICE_STRU *pBsService,TAF_UINT8 ucClass);
extern TAF_VOID At_SsPrint2Code(TAF_SS_CODE *pSsCode,TAF_UINT8 ucType);

extern TAF_UINT32 At_StgiGetInput(TAF_UINT8 ucIndex,SI_STK_TERMINAL_RSP_STRU *pRsp);
extern TAF_UINT32 At_StgiGetKey(TAF_UINT8 ucIndex, SI_STK_TERMINAL_RSP_STRU *pRsp);
extern TAF_UINT32 At_StgiSelectItem(TAF_UINT8 ucIndex,SI_STK_TERMINAL_RSP_STRU *pRsp);
extern TAF_UINT32 At_StgrSelMenu(TAF_UINT8 ucIndex);

extern VOS_BOOL at_TmodeIsGuSingle(VOS_VOID);
extern VOS_BOOL at_TmodeIsLteSingle(VOS_VOID);
extern VOS_BOOL at_TmodeIsMultiMode(VOS_VOID);
extern VOS_UINT32 AT_TransferWifiRate(
           VOS_UINT32                          ulInRate,
           VOS_UINT32                         *pulOutRate
       );
extern TAF_UINT32 At_UnicodePrint2Ascii(TAF_UINT8 *pucDst, TAF_UINT8 *pucSrc, TAF_UINT16 usSrcLen);
extern TAF_UINT32 At_UnicodePrint2Unicode(TAF_UINT8 *pData,TAF_UINT16 *pLen);
extern TAF_VOID At_UnicodeTransferTo80(TAF_UINT8 *pucSrc, TAF_UINT16 usSrcLen, TAF_UINT8 *pucDst);
extern TAF_UINT32 At_UnicodeTransferTo81(const TAF_UINT8 *pucData,
                                         TAF_UINT16      usLen,
                                         TAF_UINT16      usCodeBase,
                                         TAF_UINT8       *pucDest);
extern TAF_UINT32 At_UnicodeTransferTo81CalcLength(const TAF_UINT8 *pucData,
                                                   TAF_UINT16      usLen,
                                                   TAF_UINT16      *pusBaseCode,
                                                   TAF_UINT16      *pusDstLen);
extern TAF_UINT32 At_UnicodeTransferTo82(const TAF_UINT8 *pucData,
                                         TAF_UINT16      usLen,
                                         TAF_UINT16      usCodeBase,
                                         TAF_UINT8       *pucDest);
extern TAF_UINT32 At_UnicodeTransferTo82CalcLength(const TAF_UINT8 *pucData,
                                                   TAF_UINT16      usLen,
                                                   TAF_UINT16      *pusBaseCode,
                                                   TAF_UINT16      *pusDstLen);
extern TAF_UINT32 At_UnicodeTransferToGsm(TAF_UINT8 *pucSrc, TAF_UINT16 usSrcLen, TAF_UINT8 *pucDst);
extern TAF_UINT32 At_UnicodeTransferToGsmCalcLength(TAF_UINT8  *pucSrc,
                                                    TAF_UINT16 usSrcLen,
                                                    TAF_UINT16 *pusDstLen);
extern VOS_UINT32 AT_UpdateImei(
           VOS_UINT8                           aucImei[],
           VOS_UINT16                          usImeiLength
       );
extern TAF_UINT32 At_UpdateMsgRcvAct(
           TAF_UINT8                           ucIndex,
           AT_CSMS_MSG_VERSION_ENUM_U8         ucCsmsVersion,
           AT_CNMI_MT_TYPE                     CnmiMtType,
           AT_CNMI_DS_TYPE                     CnmiDsType
       );
extern VOS_UINT32 AT_UpdateSvn(
           VOS_UINT8                           aucSvn[],
           VOS_UINT16                          usSvnLength
       );
extern VOS_UINT32 At_WriteAccessModeNVToDefault(
           AT_CUSTOMIZE_ITEM_DFLT_ENUM_UINT8   enCustomizeItem
       );
extern VOS_UINT32 At_WriteCustomizeSrvNVToDefault(
           AT_CUSTOMIZE_ITEM_DFLT_ENUM_UINT8   enCustomizeItem
       );
extern VOS_UINT32 At_WriteDpaCatToNV(UINT8 ucDpaRate);
extern VOS_UINT32 At_WriteGprsActTimerNVToDefault(
           AT_CUSTOMIZE_ITEM_DFLT_ENUM_UINT8   enCustomizeItem
       );
extern VOS_UINT32 At_WriteMsClassNVToDefault(
           AT_CUSTOMIZE_ITEM_DFLT_ENUM_UINT8   enCustomizeItem
       );
extern VOS_UINT32 At_WriteRadioAccessCapaNVToDefault(
           AT_CUSTOMIZE_ITEM_DFLT_ENUM_UINT8   enCustomizeItem
       );
extern VOS_UINT32 AT_WriteRrcVerToNV(VOS_UINT8 ucSrcWcdmaRRC);
extern VOS_UINT32 At_WriteSimLockNVToDefault(
           AT_CUSTOMIZE_ITEM_DFLT_ENUM_UINT8   enCustomizeItem
       );
extern VOS_UINT32 At_WriteSnPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_WriteTrafficClassTypeNVToDefault(
           AT_CUSTOMIZE_ITEM_DFLT_ENUM_UINT8   enCustomizeItem
       );
extern VOS_UINT32 At_WriteUsbStatusNVToDefault(
           AT_CUSTOMIZE_ITEM_DFLT_ENUM_UINT8   enCustomizeItem
       );
extern VOS_UINT32 At_WriteWifiNVToDefault(
           AT_CUSTOMIZE_ITEM_DFLT_ENUM_UINT8   enCustomizeItem
       );
extern VOS_UCHAR ToBase64Char(const VOS_UCHAR code6bit);

extern VOS_UINT32 AT_CheckBodySarWcdmaPara(
        AT_BODYSARWCDMA_SET_PARA_STRU      *pstBodySarWcdmaPara);

extern VOS_UINT32 AT_FillBodySarWcdmaPara(
        AT_BODYSARWCDMA_SET_PARA_STRU      *pstBodySarWcdmaPara,
        MTA_BODY_SAR_PARA_STRU             *pstBodySarPara);

extern VOS_UINT32 AT_CheckBodySarGsmPara(
        AT_BODYSARGSM_SET_PARA_STRU        *pstBodySarGsmPara);

extern VOS_VOID AT_FillBodySarGsmPara(
        AT_BODYSARGSM_SET_PARA_STRU        *pstBodySarGsmPara,
        MTA_BODY_SAR_PARA_STRU             *pstBodySarPara);
extern VOS_VOID AT_ResetParseVariable();


#if 0
extern int WIFI_GET_PA_MODE(void);

extern int WIFI_SET_PA_MODE(int wifiPaMode);
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

#endif /* end of Test_AtSetParaCmd.h */
