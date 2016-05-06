/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : uttest_AtCmdMsgProc.h
  版 本 号   : 初稿
  作    者   :
  生成日期   : 2012年5月17日
  最近修改   :
  功能描述   : uttest_AtCmdMsgProc.cpp 的头文件
  函数列表   : 
  修改历史   :
  1.日    期   : 2012年5月17日
    作    者   : l60609
    修改内容   : 创建文件

******************************************************************************/

#ifndef __TEST_ATCMDMSGPROC_H__
#define __TEST_ATCMDMSGPROC_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "ATCmdProc.h"
#include "TafAppMma.h"
#include "siapppb.h"
#include "siappstk.h"
#include "AtMsgPrint.h"
#include "mdrv.h"
#include "AtPhyInterface.h"
#include "PppInterface.h"
#include "AtDataProc.h"
#include "AtCmdMsgProc.h"
#include "TafDrvAgent.h"
#include "AtCmdMsgProc.h"
#include "AtEventReport.h"
#include "AtRabmInterface.h" // V3R2和V7R1共用 z40661 c00149739 20111221
#include "AtRnicInterface.h"
#include "AtDeviceCmd.h"
#if (FEATURE_ON==FEATURE_LTE)
#include "msp_nv_def.h"
#include "msp_nv_id.h"
#endif
#include "AtCtx.h"
#include "AtEventReport.h"
#include "AtMtaInterface.h"
#include "ATCmdProc.h"
#include "AtParse.h"
#include "AtInit.h"
#include "OmApi.h"
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
#define    THIS_FILE_ID        PS_FILE_ID_AT_CMDMSGPROC_C
/*lint +e767 修改人:罗建 107747;检视人:sunshaohua*/

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
extern void UT_STUB_INIT(void);

extern VOS_UINT32 AT_CheckSimlockCodeStr(
    DRV_AGENT_PERSONALIZATION_CATEGORY_ENUM_UINT8   enCategory,
    VOS_CHAR                                       *pcStrCode
);

extern VOS_VOID AT_SupportHsdpa(
    AT_NVIM_UE_CAPA_STRU               *pstUECapa,
    VOS_BOOL                           *pbSupportHsdpa
    );

extern VOS_VOID AT_SupportHsupa(
    AT_NVIM_UE_CAPA_STRU               *pstUECapa,
    VOS_BOOL                           *pbSupportHsupa
);

extern VOS_BOOL AT_E5CheckRight(
           VOS_UINT8                           ucIndex,
           VOS_UINT8                          *pucData,
           VOS_UINT16                          usLen
       );
extern TAF_VOID At_EventMsgProc(MN_AT_IND_EVT_STRU *pMsg);
extern VOS_VOID AT_EventReport(
           VOS_UINT32                          ulPid,
           NAS_OM_EVENT_ID_ENUM_UINT16         enEventId,
           VOS_VOID                           *pPara,
           VOS_UINT32                          ulLen
       );
extern VOS_UINT32 AT_FormatAtiCmdQryString(
    MODEM_ID_ENUM_UINT16                enModemId,
    DRV_AGENT_MSID_QRY_CNF_STRU        *pstDrvAgentMsidQryCnf
    );
extern VOS_VOID AT_GetGFeatureInfo(
           AT_FEATURE_SUPPORT_ST              *pstFeATure,
           DRV_AGENT_SFEATURE_QRY_CNF_STRU    *pstATAgentSfeatureQryCnf
       );
extern VOS_UINT32  AT_GetImeiValue(
                                   MODEM_ID_ENUM_UINT16                enModemId,
                                   VOS_UINT8 aucImei[TAF_PH_IMEI_LEN + 1]
);
extern VOS_UINT32 AT_GetRxpriErr(DRV_AGENT_ERROR_ENUM_UINT32 enResult);
extern VOS_UINT32 AT_GetSimLockStatus(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_GetWFeatureInfo(
           AT_FEATURE_SUPPORT_ST              *pstFeATure,
           DRV_AGENT_SFEATURE_QRY_CNF_STRU    *pstAtAgentSfeatureQryCnf
       );
extern VOS_VOID  At_GHPAMsgProc(
           MsgBlock                            *pstMsg
       );
extern VOS_VOID  At_HPAMsgProc(
           MsgBlock                            *pstMsg
       );
extern VOS_VOID  At_HpaRfCfgCnfProc(
           HPA_AT_RF_CFG_CNF_STRU              *pstMsg
       );
extern TAF_VOID At_MmaMsgProc(
           MSG_HEADER_STRU                     *pstMsg
       );
extern VOS_VOID AT_ModemMscIndProc(AT_PPP_MODEM_MSC_IND_MSG_STRU *pMsg);
extern TAF_VOID At_MsgProc(MsgBlock* pMsg);
extern VOS_CHAR AT_Num2AsciiNum(VOS_UINT8 ucNum);
extern TAF_VOID At_PbCallBackFunc(SI_PB_EVENT_INFO_STRU  *pEvent);
extern TAF_UINT32 At_PbCNUMCmdPrint(VOS_UINT8 ucIndex,TAF_UINT16 *pusDataLen,TAF_UINT8 *pucData,SI_PB_EVENT_INFO_STRU *pEvent);
extern TAF_UINT32 At_PbCPBR2CmdPrint(VOS_UINT8 ucIndex,TAF_UINT16 *pusDataLen,TAF_UINT8 *pucData,SI_PB_EVENT_INFO_STRU *pEvent);
extern TAF_UINT32 At_PbCPBRCmdPrint(VOS_UINT8 ucIndex,TAF_UINT16 *pusDataLen,TAF_UINT8 *pucData,SI_PB_EVENT_INFO_STRU *pEvent);
extern TAF_VOID At_PbEmailPrint(TAF_UINT8  *pucSrc,
                                TAF_UINT16 usSrcLen,
                                TAF_UINT8  *pucDst,
                                TAF_UINT16 *pusDstLen);
extern TAF_UINT32 At_PbGsmExtToUnicode(TAF_UINT8 ucGsmExtChar, TAF_UINT16 *pusUnicodeChar);
extern TAF_UINT16 At_PbGsmFormatPrint(TAF_UINT16 usMaxLength,
                                      TAF_UINT8  *pucDst,
                                      TAF_UINT8  *pucSrc,
                                      TAF_UINT16 usSrcLen);
extern TAF_VOID At_PbGsmToUnicode(TAF_UINT8  *pucSrc,
                                  TAF_UINT16 usSrcLen,
                                  TAF_UINT8  *pucDst,
                                  TAF_UINT16 *pusDstLen);
extern TAF_UINT32 At_PbOneUnicodeToIra(TAF_UINT16 usUnicodeChar, TAF_UINT8 *pucDst);
extern TAF_UINT32 At_PbReadCnfProc(VOS_UINT8 ucIndex,SI_PB_EVENT_INFO_STRU  *pEvent);
extern TAF_VOID At_PbRecordToUnicode(SI_PB_EVENT_INFO_STRU *pstEvent,
                                     TAF_UINT8             *pucDecode,
                                     TAF_UINT16            *pusDecodeLen);
extern TAF_UINT32 At_PbSCPBRCmdPrint(VOS_UINT8 ucIndex,TAF_UINT16 *pusDataLen,SI_PB_EVENT_INFO_STRU *pEvent);
extern TAF_VOID At_PbSearchCnfProc(VOS_UINT8 ucIndex,SI_PB_EVENT_INFO_STRU  *pEvent);
extern TAF_VOID At_PbUnicode80FormatPrint(TAF_UINT8  *pucSrc,
                                          TAF_UINT16 usSrcLen,
                                          TAF_UINT8  *pucDst,
                                          TAF_UINT16 *pusDstLen);
extern TAF_VOID At_PbUnicode81FormatPrint(TAF_UINT8  *puc81Code,
                                          TAF_UINT8  *pucDst,
                                          TAF_UINT16 *pusDstLen);
extern TAF_VOID At_PbUnicode82FormatPrint(TAF_UINT8  *puc82Code,
                                          TAF_UINT8  *pucDst,
                                          TAF_UINT16 *pusDstLen);
extern TAF_UINT16 At_PbUnicodeToIraFormatPrint(TAF_UINT16 usMaxLength,
                                               TAF_UINT8  *pucDst,
                                               TAF_UINT8  *pucSrc,
                                               TAF_UINT16 usSrcLen);
extern TAF_UINT32 At_Pb_AlaphPrint(TAF_UINT16            *pusDataLen,
                                   SI_PB_EVENT_INFO_STRU *pstEvent,
                                   TAF_UINT8             *pucData);
extern TAF_UINT32 At_Pb_CnumAlaphPrint(TAF_UINT16            *pusDataLen,
                                   SI_PB_EVENT_INFO_STRU *pstEvent,
                                   TAF_UINT8             *pucData);
extern TAF_VOID AT_Pb_NumberPrint(TAF_UINT16 *pusDataLen, SI_PB_EVENT_INFO_STRU *pstEvent, TAF_UINT8 *pucData);
extern TAF_UINT32 At_PB_Unicode2UnicodePrint(TAF_UINT32 MaxLength,TAF_INT8 *headaddr,TAF_UINT8 *pucDst, TAF_UINT8 *pucSrc, TAF_UINT16 usSrcLen);
extern VOS_UINT32 AT_PhoneSimlockInfoPrint(
           DRV_AGENT_PHONESIMLOCKINFO_QRY_CNF_STRU     stPhoneSimlockInfo,
           VOS_UINT8                                   ucIndex,
           VOS_UINT16                                 *pusLength
       );
extern VOS_UINT32  AT_PortCtrlTmpSndMsg(VOS_VOID);
extern TAF_VOID At_PppMsgProc(MSG_HEADER_STRU *pMsg);
extern TAF_VOID At_PppProtocolRelIndProc(AT_PPP_PROTOCOL_REL_IND_MSG_STRU *pMsg);
extern VOS_VOID At_ProcMsgFromCc(VOS_VOID *pMsg);
extern VOS_VOID At_ProcMsgFromDrvAgent(DRV_AGENT_MSG_STRU *pMsg);
extern VOS_VOID At_ProcMsgFromVc(MN_AT_IND_EVT_STRU *pMsg);
extern VOS_UINT32    AT_ProcRabmQryFastDormParaCnf(
           RABM_AT_QRY_FASTDORM_PARA_CNF_STRU     *pstMsg
       );
extern VOS_UINT32    AT_ProcRabmSetFastDormParaCnf(
           RABM_AT_SET_FASTDORM_PARA_CNF_STRU     *pstMsg
       );
extern TAF_VOID AT_RabmMsgProc(
           MSG_HEADER_STRU                    *pstMsg
       );
extern VOS_UINT32 At_RcvAtCcMsgStateQryCnfProc(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvAtMmaUsimStatusInd(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentAntStateIndRsp(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentCellinfoQryRsp(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentChipTempQryRsp(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentFacAuthPubkeySetCnf(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentFreqLockQryCnf(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentFreqLockSetCnf(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentFullHardwareQryRsp(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentGasMntnCmdRsp(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentHardwareQryRsp(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentHukSetCnf(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentIdentifyEndSetCnf(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentIdentifyStartSetCnf(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentMeanRptQryRsp(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentMsidQryCnf(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentNandBadBlockQryRsp(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentNandDevInfoQryRsp(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentNvBackupStatQryRsp(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentNvRestoreManuDefaultRsp(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentOpwordSetCnf(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentPhonePhynumQryCnf(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentPhonePhynumSetCnf(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentPhoneSimlockInfoQryCnf(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentPortAttribSetCnf(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentPortAttribSetQryCnf(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentPortctrlTmpSetCnf(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentQryCellSrhRsp(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentQryGpioplRsp(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentQryNvRestoreRstCnf(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentQryProdtypeRsp(VOS_VOID * pMsg);
extern VOS_UINT32 AT_RcvDrvAgentQryRxdivCnf(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentQryRxpriRsp(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentQrySecuBootFeatureRsp(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentQrySecuBootRsp(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentQrySfeatureRsp(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentQryTbatRsp(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentQryTbatvoltRsp(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentQryVersionRsp(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentRrcVersionQryCnf(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentRrcVersionSetCnf(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentSetAdcRsp(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentSetCellSrhRsp(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentSetDatalockRsp(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentSetFchanRsp(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentSetGpioplRsp(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentSetMaxLockTmsRsp(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentSetNvRestoreCnf(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentSetRxdivCnf(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentSetRxpriRsp(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentSetSecuBootRsp(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentSetSimlockCnf(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentSetSpwordRsp(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentSimlockDataReadQryCnf(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentSimlockDataWriteSetCnf(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentVertimeQryRsp(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentWasMntnCmdRsp(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentYjcxQryCnf(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentYjcxSetCnf(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvMmaCipherInfoQueryCnf(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvMmaCmmSetCmdRsp(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvMmaLocInfoQueryCnf(VOS_VOID *pMsg);

/* Modified by w00167002 for L-C互操作项目, 2014-2-21, begin */
extern VOS_UINT32 AT_RcvMmaOmMaintainInfoInd(
    VOS_VOID                           *pstMsg
);
/* Modified by w00167002 for L-C互操作项目, 2014-2-21, end */
extern VOS_VOID AT_RcvNdisMsg(MsgBlock* pMsg);
extern VOS_UINT32 AT_RcvRnicDialModeCnf(MsgBlock *pstMsg);
extern VOS_UINT32 AT_RcvRnicDsflowRsp(MsgBlock *pstMsg);
extern VOS_UINT32 At_RcvRnicMsg(MsgBlock *pstMsg);

/* Modified by w00167002 for L-C互操作项目, 2014-2-21, begin */
extern VOS_UINT32 AT_RcvSimLockQryRsp(VOS_VOID *pMsg);
/* Modified by w00167002 for L-C互操作项目, 2014-2-21, end */
extern VOS_VOID At_RcvVcMsgQryModeCnfProc(MN_AT_IND_EVT_STRU *pstData);
extern VOS_VOID At_RcvVcMsgQryPortCnfProc(MN_AT_IND_EVT_STRU *pstData);
extern VOS_VOID At_RcvVcMsgSetPortCnfProc(MN_AT_IND_EVT_STRU *pstData);
extern TAF_VOID AT_RestoreClientData(
           NAS_AT_SDT_AT_CLIENT_TABLE_STRU    *pstAtClientData
       );
extern TAF_UINT32 AT_RestoreContextData(
           AT_MSG_STRU                         *pMsg
       );
extern VOS_UINT32  At_RfCfgCnfReturnErrProc(
           VOS_UINT8                           ucIndex
       );
extern VOS_VOID  At_RfCfgCnfReturnSuccProc(
           VOS_UINT8                           ucIndex
       );
extern VOS_VOID  At_RfRssiIndProc(
           HPA_AT_RF_RX_RSSI_IND_STRU          *pstMsg
       );
extern VOS_UINT32 At_SendRfCfgAntSelToHPA(VOS_UINT8 ucDivOrPriOn);
extern VOS_UINT32 AT_SetFchanRspErr(DRV_AGENT_FCHAN_SET_ERROR_ENUM_UINT32  enResult);
extern VOS_UINT32 AT_SetGlobalFchan(VOS_UINT8 ucRATMode);
extern VOS_UINT32 AT_SimlockCodeBcd2Str(
           DRV_AGENT_PERSONALIZATION_CATEGORY_ENUM_UINT8   enCategory,
           VOS_UINT8                                      *pucBcdNum,
           VOS_CHAR                                       *pcStrNum
       );
extern VOS_UINT32 AT_SimlockDataReadPrint(
           DRV_AGENT_SIMLOCKDATAREAD_QRY_CNF_STRU      stSimlockDataRead,
           VOS_UINT8                                   ucIndex,
           VOS_UINT16                                 *pusLength
       );

extern VOS_VOID At_ZeroReplaceBlankInString( VOS_UINT8 *pData, VOS_UINT32 ulLen);
extern VOS_UINT32 WuepsATFidInit(enum VOS_INIT_PHASE_DEFINE ip);


extern AT_ABORT_CMD_PARA_STRU* AT_GetAbortCmdPara(VOS_VOID);

extern VOS_VOID AT_ReportResetCmd(AT_RESET_REPORT_CAUSE_ENUM_UINT32 enCause);



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

#endif /* end of Test_AtCmdMsgProc.h */
