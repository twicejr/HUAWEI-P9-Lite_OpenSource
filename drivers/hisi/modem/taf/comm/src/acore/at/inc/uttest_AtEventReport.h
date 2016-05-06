/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : uutest_AtEventReport.h
  版 本 号   : 初稿
  作    者   :
  生成日期   : 2012年5月17日
  最近修改   :
  功能描述   : uttest_AtEventReport.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年5月17日
    作    者   : l60609
    修改内容   : 创建文件

******************************************************************************/

#ifndef __TEST_ATEVENTREPORT_H__
#define __TEST_ATEVENTREPORT_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "AtCtx.h"
#include "ATCmdProc.h"
#include "siappstk.h"
#include "PppInterface.h"
#include "AtDataProc.h"
#include "AtEventReport.h"
#include "TafDrvAgent.h"
#include "AtOamInterface.h"
#if( FEATURE_ON == FEATURE_CSD )
#include "AtCsdInterface.h"
#endif
#include "AtInputProc.h"
#include "TafApsApi.h"
#include "FcInterface.h"
#include "AtCmdMsgProc.h"
#include "AppVcApi.h"
#if (FEATURE_VSIM == FEATURE_ON)
#include "AtCmdSimProc.h"
#endif
#include "AtCmdCallProc.h"
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
#define    THIS_FILE_ID        PS_FILE_ID_AT_EVENTREPORT_C


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

#if(FEATURE_ON == FEATURE_LTE)
    extern   VOS_UINT32 g_ulGuOnly;
    extern   VOS_UINT32 g_ulGuTmodeCnfNum;
    extern   VOS_UINT32 g_ulLteIsSend2Dsp;
    extern   VOS_UINT32 g_ulTmodeLteMode;
    extern VOS_UINT32  g_ulGuTmodeCnf;
    extern VOS_UINT32  g_ulLteTmodeCnf;
#endif

    extern AT_MODEM_CTX_STRU                       g_astAtModemCtx[MODEM_ID_BUTT];

    extern TAF_VOID At_MsgProc(MsgBlock* pMsg);
    extern VOS_UINT32  At_PidInit(enum VOS_INIT_PHASE_DEFINE enPhase);

    extern VOS_UINT16 AT_PrintSmsLength(
        MN_MSG_MSG_CODING_ENUM_U8           enMsgCoding,
        VOS_UINT32                          ulLength,
        VOS_UINT8                          *pDst
        );


    extern TAF_UINT32 At_AsciiNum2Num (TAF_UINT8 *pucDst, TAF_UINT8 *pucSrc, TAF_UINT16 usSrcLen);

    extern VOS_UINT32  AT_BcdNumberToAscii(
        const VOS_UINT8                     *pucBcdNumber,
        VOS_UINT8                           ucBcdLen,
        VOS_CHAR                            *pcAsciiNumber
        );


    extern MN_MSG_TS_DATA_INFO_STRU                g_stAtMsgTsDataInfo;

extern VOS_UINT32 atReadCemodeCnfProc(VOS_UINT8   ucIndex,VOS_VOID    *pEvtInfo);
extern VOS_UINT32 atReadLtecsCnfProc(VOS_UINT8   ucIndex,VOS_VOID    *pEvtInfo);
extern VOS_VOID At_AdjustLocalDate(
           TIME_ZONE_TIME_STRU                 *pstUinversalTime,
           VOS_INT8                            cAdjustValue,
           TIME_ZONE_TIME_STRU                 *pstLocalTime
       );
extern TAF_UINT32 At_Ascii2UnicodePrint(TAF_UINT32 MaxLength,TAF_INT8 *headaddr,TAF_UINT8 *pucDst, TAF_UINT8 *pucSrc, TAF_UINT16 usSrcLen);
extern TAF_VOID  At_BufferMsgInTa(
           VOS_UINT8                           ucIndex,
           MN_MSG_EVENT_ENUM_U32               enEvent,
           MN_MSG_EVENT_INFO_STRU              *pstEvent
       );
extern VOS_UINT32 AT_CalcIpv6LanAddrFromIpv6Prefix(
           VOS_UINT8                          *pucPrefix,
           VOS_UINT32                          ulPrefixBitLen,
           VOS_UINT8                          *pucIpv6LanAddr,
           VOS_UINT32                          ulIpv6LanAddrLen
       );
extern VOS_UINT32  AT_CbPrintRange(
           VOS_UINT16                          usLength,
           TAF_CBA_CBMI_RANGE_LIST_STRU              *pstCbMidr
       );
extern TAF_UINT32 At_CcClass2Print(MN_CALL_TYPE_ENUM_U8 enCallType,TAF_UINT8 *pDst);
extern TAF_UINT32 At_CcfcQryReport (
           TAF_SS_CALL_INDEPENDENT_EVENT_STRU  *pEvent,
           TAF_UINT8                           ucIndex
       );
extern VOS_VOID AT_ChangeCbMidsRsp(
           TAF_UINT8                           ucIndex,
           MN_MSG_EVENT_INFO_STRU              *pstEvent
       );
extern VOS_UINT32 At_ChangeSTKCmdNo(VOS_UINT32 ulCmdType, VOS_UINT8 *ucCmdNo );
extern VOS_UINT32 At_ChgMnErrCodeToAt(
           VOS_UINT8                           ucIndex,
           VOS_UINT32                          ulMnErrorCode
       );
extern TAF_UINT32   At_ChgTafErrorCode(TAF_UINT8 ucIndex,TAF_ERROR_CODE_ENUM_UINT32 enTafErrorCode);
extern VOS_VOID AT_ClearDtmfInfo(VOS_UINT32 ulIndex);
extern TAF_VOID At_CmdCnfMsgProc(TAF_UINT8* pData,TAF_UINT16 usLen);
extern VOS_UINT32 AT_ConCallMsgTypeToCuusiMsgType(
           MN_CALL_UUS1_MSG_TYPE_ENUM_U32      enMsgType,
           AT_CUUSI_MSG_TYPE_ENUM_U32          *penCuusiMsgType

       );
extern VOS_UINT32 AT_ConCallMsgTypeToCuusuMsgType(
           MN_CALL_UUS1_MSG_TYPE_ENUM_U32      enMsgType,
           AT_CUUSU_MSG_TYPE_ENUM_U32          *penCuusuMsgType

       );
extern VOS_UINT32 AT_ConvertCallError(TAF_CS_CAUSE_ENUM_UINT32 enCause);
extern VOS_VOID AT_ConvertSysCfgRatOrderToStr(
           TAF_MMA_RAT_ORDER_STRU             *pstRatOrder,
           VOS_UINT8                          *pucAcqOrder
       );
extern VOS_VOID At_CsAllCallInfoEvtCnfProc(
           MN_AT_IND_EVT_STRU                 *pstData,
           VOS_UINT16                          usLen
       );
extern TAF_VOID At_CsEventProc(MN_AT_IND_EVT_STRU *pstData,TAF_UINT16 usLen);
extern TAF_VOID At_CsIncomingEvtIndProc(
           TAF_UINT8                           ucIndex,
           MN_CALL_EVENT_ENUM_U32              enEvent,
           MN_CALL_INFO_STRU                   *pstCallInfo
       );
extern TAF_VOID At_CsIncomingEvtOfIncomeStateIndProc(
           TAF_UINT8                           ucIndex,
           MN_CALL_EVENT_ENUM_U32              enEvent,
           MN_CALL_INFO_STRU                   *pstCallInfo
       );
extern TAF_VOID At_CsIncomingEvtOfWaitStateIndProc(
           TAF_UINT8                           ucIndex,
           MN_CALL_EVENT_ENUM_U32              enEvent,
           MN_CALL_INFO_STRU                   *pstCallInfo
       );
extern TAF_VOID At_CsIndProc(
           TAF_UINT8                           ucIndex,
           MN_CALL_EVENT_ENUM_U32              enEvent,
           MN_CALL_INFO_STRU                   *pstCallInfo
       );
extern TAF_VOID At_CsMsgProc(MN_AT_IND_EVT_STRU *pstData,TAF_UINT16 usLen);
extern VOS_VOID  AT_CsRspEvtConnectProc(
           TAF_UINT8                           ucIndex,
           MN_CALL_EVENT_ENUM_U32              enEvent,
           MN_CALL_INFO_STRU                   *pstCallInfo
       );
extern VOS_VOID  AT_CsRspEvtReleasedProc(
           TAF_UINT8                           ucIndex,
           MN_CALL_EVENT_ENUM_U32              enEvent,
           MN_CALL_INFO_STRU                   *pstCallInfo
       );
extern TAF_VOID At_CsRspProc(
           TAF_UINT8                           ucIndex,
           MN_CALL_EVENT_ENUM_U32              enEvent,
           MN_CALL_INFO_STRU                   *pstCallInfo
       );
extern TAF_VOID AT_CsSsNotifyEvtIndProc(
           TAF_UINT8                           ucIndex,
           MN_CALL_EVENT_ENUM_U32              enEvent,
           MN_CALL_INFO_STRU                   *pstCallInfo
       );
extern VOS_VOID AT_CsUus1InfoEvtIndProc(
           VOS_UINT8                           ucIndex,
           MN_CALL_EVENT_ENUM_U32              enEvent,
           MN_CALL_INFO_STRU                   *pstCallInfo
       );
extern TAF_VOID At_DataStatusIndProc(TAF_UINT16  ClientId,
                                         TAF_UINT8      ucDomain,
                                         TAF_UINT8      ucRabId,
                                         TAF_UINT8      ucStatus,
                                         TAF_UINT8      ucCause );
extern TAF_VOID At_DataStatusMsgProc(TAF_UINT8* pData,TAF_UINT16 usLen);
extern TAF_VOID  At_DeleteRspProc(
           TAF_UINT8                           ucIndex,
           MN_MSG_EVENT_INFO_STRU              *pstEvent
       );
extern TAF_VOID  At_DeleteTestRspProc(
           TAF_UINT8                           ucIndex,
           MN_MSG_EVENT_INFO_STRU              *pstEvent
       );
extern VOS_VOID AT_ForwardCbMsgToTe(
           MN_MSG_EVENT_INFO_STRU              *pstEvent
       );
extern TAF_VOID  AT_ForwardDeliverMsgToTe(
           MN_MSG_EVENT_INFO_STRU              *pstEvent,
           MN_MSG_TS_DATA_INFO_STRU            *pstTsDataInfo
       );
extern TAF_VOID At_ForwardMsgToTe(
           MN_MSG_EVENT_ENUM_U32               enEvent,
           MN_MSG_EVENT_INFO_STRU              *pstEvent
       );
extern TAF_VOID At_ForwardMsgToTeInCmt(
           VOS_UINT8                            ucIndex,
           TAF_UINT16                          *pusSendLength,
           MN_MSG_TS_DATA_INFO_STRU            *pstTsDataInfo,
           MN_MSG_EVENT_INFO_STRU              *pstEvent
       );
extern TAF_VOID  AT_ForwardPppMsgToTe(
           MN_MSG_EVENT_INFO_STRU              *pstEvent
       );
extern TAF_VOID  AT_ForwardStatusReportMsgToTe(
           MN_MSG_EVENT_INFO_STRU              *pstEvent,
           MN_MSG_TS_DATA_INFO_STRU            *pstTsDataInfo
       );
extern VOS_UINT32 AT_GetBitMap(
           VOS_UINT32                         *pulBitMap,
           VOS_UINT32                          ulIndex
       );
extern VOS_VOID At_GetCbActiveMidsRspProc(
           TAF_UINT8                           ucIndex,
           MN_MSG_EVENT_INFO_STRU              *pstEvent
       );
extern TAF_UINT8 At_GetClckClassFromBsCode(TAF_SS_BASIC_SERVICE_STRU *pstBs);
extern TAF_VOID At_GetCmmsRspProc(
           TAF_UINT8                           ucIndex,
           MN_MSG_EVENT_INFO_STRU              *pstEvent
       );
extern VOS_UINT8 At_GetDaysForEachMonth(
           VOS_UINT8                               ucYear,
           VOS_UINT8                               ucMonth
       );
extern VOS_UINT32 AT_GetLCStartTime(VOS_VOID);
extern VOS_UINT32 At_GetLocalTime(VOS_UINT8 *pucLTZ,TIME_ZONE_TIME_STRU *pstLocalTime);
extern VOS_VOID AT_GetOnlyGURatOrder(
           TAF_MMA_RAT_ORDER_STRU             *pstRatOrder
       );
extern VOS_UINT16 AT_GetOperNameLengthForCops(
           TAF_CHAR                            *pstr,
           TAF_UINT8                           ucMaxLen
       );
extern TAF_UINT8 At_GetSsCode(
           MN_CALL_SS_NOTIFY_CODE_ENUM_U8      enCode,
           MN_CALL_STATE_ENUM_U8               enCallState
       );
extern VOS_UINT32  AT_GetSubSysModeName(
           MN_PH_SUB_SYS_MODE_EX_ENUM_U8       enSubSysMode,
           VOS_CHAR                           *pucSubSysModeName
       );
extern VOS_UINT32  AT_GetSysModeName(
           MN_PH_SYS_MODE_EX_ENUM_U8           enSysMode,
           VOS_CHAR                           *pucSysModeName
       );
extern TAF_VOID At_HandleSmtBuffer(
                                   VOS_UINT8                           ucIndex,
                                   AT_CNMI_BFR_TYPE                    ucBfrType
                                   );
extern VOS_UINT32 AT_Hex2AsciiStrLowHalfFirst(
           VOS_UINT32                          ulMaxLength,
           VOS_INT8                            *pcHeadaddr,
           VOS_UINT8                           *pucDst,
           VOS_UINT8                           *pucSrc,
           VOS_UINT16                          usSrcLen
       );
extern TAF_UINT32 At_HexAlpha2AsciiString(TAF_UINT32 MaxLength,TAF_INT8 *headaddr,TAF_UINT8 *pucDst,TAF_UINT8 *pucSrc,TAF_UINT16 usSrcLen);
extern TAF_UINT32 At_HexString2AsciiNumPrint(TAF_UINT32 MaxLength,TAF_INT8 *headaddr,TAF_UINT8 *pucDst, TAF_UINT8 *pucSrc, TAF_UINT16 usSrcLen);
extern TAF_UINT32 At_HexText2AsciiStringSimple(TAF_UINT32 MaxLength,TAF_INT8 *headaddr,TAF_UINT8 *pucDst,TAF_UINT32 ulLen,TAF_UINT8 *pucStr);
extern VOS_BOOL  AT_IsFindVedioModemStatus(
           TAF_UINT8                           ucIndex,
           MN_CALL_TYPE_ENUM_U8                enCallType
       );
extern TAF_UINT8 At_IsOplRecPrintable(TAF_PH_USIM_OPL_RECORD * pstOplRec);

extern TAF_VOID  At_ListRspProc(
           TAF_UINT8                           ucIndex,
           MN_MSG_EVENT_INFO_STRU              *pstEvent
       );
extern TAF_UINT32 At_MsgPduInd(
           MN_MSG_BCD_ADDR_STRU                *pstScAddr,
           MN_MSG_RAW_TS_DATA_STRU             *pstPdu,
           TAF_UINT8                           *pucDst
       );
extern TAF_VOID At_PbMsgProc(MsgBlock* pMsg);
extern TAF_VOID At_PbRspProc(TAF_UINT8 ucIndex,SI_PB_EVENT_INFO_STRU *pEvent);
extern TAF_VOID At_PhEventProc(TAF_UINT8* pData,TAF_UINT16 usLen);
extern TAF_VOID At_PhIndProc(TAF_UINT8 ucIndex,TAF_PHONE_EVENT_INFO_STRU  *pEvent);
extern TAF_VOID At_PhMsgProc(TAF_UINT8* pData,TAF_UINT16 usLen);

extern AT_RRETURN_CODE_ENUM AT_PhnEvtPlmnList(
    VOS_UINT8                           ucIndex,
    TAF_PHONE_EVENT_INFO_STRU          *pstEvent
);

extern VOS_VOID AT_PhnEvtTestCpol(
           TAF_UINT8                           ucIndex,
           TAF_PHONE_EVENT_INFO_STRU          *pEvent
       );


extern TAF_VOID At_PhPlmnListProc(TAF_UINT8* pData,TAF_UINT16 usLen);
extern TAF_UINT32 At_PhReadCreg(TAF_PH_REG_STATE_STRU  *pPara,TAF_UINT8 *pDst);
extern TAF_VOID At_PhRspProc(TAF_UINT8 ucIndex,TAF_PHONE_EVENT_INFO_STRU  *pEvent);
extern VOS_VOID AT_PhSendNeedPuk( VOS_UINT16 usModemID );
extern VOS_VOID AT_PhSendPinReady( VOS_UINT16 usModemID );
extern VOS_VOID  AT_PhSendRoaming( VOS_UINT8 ucTmpRoamStatus );
extern VOS_VOID AT_PhSendSimLocked( VOS_VOID );
extern VOS_BOOL AT_PH_IsPlmnValid(TAF_PLMN_ID_STRU *pstPlmnId);
extern TAF_VOID At_PIHMsgProc(MsgBlock* pMsg);
extern TAF_VOID At_PIHRspProc(TAF_UINT8 ucIndex, SI_PIH_EVENT_INFO_STRU *pEvent);
extern VOS_VOID AT_PrcoPsEvtErrCode(
           VOS_UINT8                           ucIndex,
           TAF_PS_CAUSE_ENUM_UINT32            enCuase

       );
extern TAF_UINT32 At_PrintMmTimeInfo(
                                     VOS_UINT8                           ucIndex,
                                     TAF_MMA_TIME_CHANGE_IND_STRU       *pMsg,
                                     TAF_UINT8                          *pDst
                                     );
extern TAF_UINT16 At_PrintReportData(
           TAF_UINT32                          MaxLength,
           TAF_INT8                            *headaddr,
           MN_MSG_MSG_CODING_ENUM_U8           enMsgCoding,
           TAF_UINT8                           *pucDst,
           TAF_UINT8                           *pucSrc,
           TAF_UINT16                          usSrcLen
       );
extern TAF_UINT32 At_PrintTimeZoneInfo(
           NAS_MM_INFO_IND_STRU                *pstMmInfo,
           TAF_UINT8                           *pDst
       );
extern VOS_VOID At_ProcSetClccResult(
           VOS_UINT8                           ucNumOfCalls,
           MN_CALL_INFO_QRY_CNF_STRU          *pstCallInfos,
           VOS_UINT8                           ucIndex
       );
extern VOS_UINT32 At_ProcVcGetVolumeEvent(
           VOS_UINT8                           ucIndex,
           APP_VC_EVENT_INFO_STRU             *pstVcEvt
       );
extern VOS_VOID At_QryAlsCnf(MN_AT_IND_EVT_STRU *pstData);
extern VOS_VOID    At_QryCpinRspProc(
           VOS_UINT8       ucIndex,
           TAF_PH_PIN_TYPE ucPinType,
           VOS_UINT16     *pusLength
       );
extern VOS_VOID AT_QryCscaRspProc(
           VOS_UINT8                           ucIndex,
           MN_MSG_EVENT_INFO_STRU             *pstEvent
       );
extern TAF_VOID At_QryMsgProc(TAF_UINT8* pData,TAF_UINT16 usLen);
extern VOS_VOID  AT_QryParaAnQueryProc(
           VOS_UINT8                           ucIndex,
           VOS_UINT8                           OpId,
           VOS_VOID                           *pPara
       );


extern VOS_VOID  AT_QryParaHomePlmnProc(
           VOS_UINT8                           ucIndex,
           VOS_UINT8                           OpId,
           VOS_VOID                           *pPara
       );


extern TAF_VOID At_QryParaRspCbndProc(
           TAF_UINT8                           ucIndex,
           TAF_UINT8                           OpId,
           TAF_VOID                            *pPara
       );
extern TAF_VOID At_QryParaRspCellRoamProc(
           TAF_UINT8                           ucIndex,
           TAF_UINT8                           OpId,
           TAF_VOID                            *pPara
       );
extern VOS_VOID AT_QryParaRspCeregProc(
           VOS_UINT8                           ucIndex,
           VOS_UINT8                           ucOpId,
           VOS_VOID                           *pPara
       );
extern TAF_VOID At_QryParaRspCfplmnProc(
           TAF_UINT8                           ucIndex,
           TAF_UINT8                           OpId,
           TAF_VOID                            *pPara
       );

extern TAF_VOID At_QryParaRspCgclassProc(
           TAF_UINT8                           ucIndex,
           TAF_UINT8                           OpId,
           TAF_VOID                            *pPara
       );

extern TAF_VOID At_QryParaRspCgmiProc(
           TAF_UINT8                           ucIndex,
           TAF_UINT8                           OpId,
           TAF_VOID                            *pPara
       );
extern TAF_VOID At_QryParaRspCgmmProc(
           TAF_UINT8                           ucIndex,
           TAF_UINT8                           OpId,
           TAF_VOID                            *pPara
       );
extern TAF_VOID At_QryParaRspCgmrProc(
           TAF_UINT8                           ucIndex,
           TAF_UINT8                           OpId,
           TAF_VOID                            *pPara
       );

extern TAF_VOID At_QryParaRspCgregProc(
           TAF_UINT8                           ucIndex,
           TAF_UINT8                           OpId,
           TAF_VOID                            *pPara
       );
extern TAF_VOID At_QryParaRspCimiProc(
           TAF_UINT8                           ucIndex,
           TAF_UINT8                           OpId,
           TAF_VOID                            *pPara
       );
extern TAF_VOID At_QryParaRspCopsProc(
           TAF_UINT8                           ucIndex,
           TAF_UINT8                           OpId,
           TAF_VOID                            *pPara
       );

extern TAF_VOID At_QryParaRspCPnnProc(
           TAF_UINT8                           ucIndex,
           TAF_UINT8                           OpId,
           TAF_VOID                            *pPara
       );

extern TAF_VOID At_QryParaRspCregProc(
           TAF_UINT8                           ucIndex,
           TAF_UINT8                           OpId,
           TAF_VOID                            *pPara
       );




extern TAF_VOID At_QryParaRspIccidProc(
           TAF_UINT8                           ucIndex,
           TAF_UINT8                           OpId,
           TAF_VOID                            *pPara
       );

extern TAF_VOID At_QryParaRspOplProc(
           TAF_UINT8                           ucIndex,
           TAF_UINT8                           OpId,
           TAF_VOID                            *pPara
       );
extern TAF_VOID At_QryParaRspPnnProc(
           TAF_UINT8                           ucIndex,
           TAF_UINT8                           OpId,
           TAF_VOID                            *pPara
       );


extern TAF_VOID At_QryParaRspProc  (
           TAF_UINT8                           ucIndex,
           TAF_UINT8                           OpId,
           TAF_PARA_TYPE                       QueryType,
           TAF_UINT16                          usErrorCode,
           TAF_VOID                            *pPara
       );
extern VOS_VOID  AT_QryParaRspSysinfoExProc(
           VOS_UINT8                           ucIndex,
           VOS_UINT8                           OpId,
           VOS_VOID                           *pPara
       );
extern TAF_VOID At_QryParaRspSysinfoProc(
           TAF_UINT8                           ucIndex,
           TAF_UINT8                           OpId,
           TAF_VOID                            *pPara
       );
extern TAF_VOID At_QryRspUsimRangeProc(
           TAF_UINT8                           ucIndex,
           TAF_UINT8                           OpId,
           TAF_VOID                            *pPara
       );
extern VOS_VOID At_QryUus1Cnf(MN_AT_IND_EVT_STRU *pstData);
extern VOS_VOID AT_RcvCdurQryRsp(
           VOS_UINT8                           ucIndex,
           MN_CALL_EVENT_ENUM_U32              enEvent,
           MN_CALL_INFO_STRU                  *pstCallInfo
       );
extern VOS_UINT32 AT_RcvDrvAgentAppdmverQryRsp(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentAuthorityIdQryRsp(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentAuthorityVerQryRsp(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentAuthVerQryRsp(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentCpnnQryRsp(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentCpnnTestRsp(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentCpuloadQryRsp(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentDloadInfoQryRsp(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentDloadverQryRsp(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentFlashInfoQryRsp(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentGodloadSetRsp(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentHkAdcGetRsp(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentHwnatQryRsp(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentImsiChgQryRsp(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentInfoRbuSetRsp(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentInfoRrsSetRsp(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentMemInfoQryRsp(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentMfreelocksizeQryRsp(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentNvBackupSetRsp(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentPfverQryRsp(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentSdloadSetRsp(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvDrvAgentTseLrfSetRsp(VOS_VOID *pMsg);
extern VOS_UINT32 AT_RcvTafPsCallEvtCallAnswerCnf(
           VOS_UINT8                           ucIndex,
           VOS_VOID                           *pEvtInfo
       );
extern VOS_UINT32 AT_RcvTafPsCallEvtCallEndCnf(
           VOS_UINT8                           ucIndex,
           VOS_VOID                           *pEvtInfo
       );
extern VOS_UINT32 AT_RcvTafPsCallEvtCallHangupCnf(
           VOS_UINT8                           ucIndex,
           VOS_VOID                           *pEvtInfo
       );
extern VOS_UINT32 AT_RcvTafPsCallEvtCallModifyCnf(
           VOS_UINT8                           ucIndex,
           VOS_VOID                           *pEvtInfo
       );
extern VOS_UINT32 AT_RcvTafPsCallEvtCallOrigCnf(
           VOS_UINT8                           ucIndex,
           VOS_VOID                           *pEvtInfo
       );
extern VOS_UINT32 AT_RcvTafPsCallEvtPdpActivateCnf(
           VOS_UINT8                           ucIndex,
           VOS_VOID                           *pEvtInfo
       );
extern VOS_UINT32 AT_RcvTafPsCallEvtPdpManageInd(
           VOS_UINT8                           ucIndex,
           VOS_VOID                           *pEvtInfo
       );
extern VOS_UINT32 AT_RcvTafPsCallEvtPdpActivateRej(
           VOS_UINT8                           ucIndex,
           VOS_VOID                           *pEvtInfo
       );
extern VOS_UINT32 AT_RcvTafPsCallEvtPdpActivateInd(
           VOS_UINT8                           ucIndex,
           VOS_VOID                           *pEvtInfo
       );
extern VOS_UINT32 AT_RcvTafPsCallEvtPdpDeactivateCnf(
           VOS_UINT8                           ucIndex,
           VOS_VOID                           *pEvtInfo
       );
extern VOS_UINT32 AT_RcvTafPsCallEvtPdpDeactivatedInd(
           VOS_UINT8                           ucIndex,
           VOS_VOID                           *pEvtInfo
       );
extern VOS_UINT32 AT_RcvTafPsCallEvtPdpModifiedInd(
           VOS_UINT8                           ucIndex,
           VOS_VOID                           *pEvtInfo
       );
extern VOS_UINT32 AT_RcvTafPsCallEvtPdpModifyCnf(
           VOS_UINT8                           ucIndex,
           VOS_VOID                           *pEvtInfo
       );
extern VOS_UINT32 AT_RcvTafPsCallEvtPdpModifyRej(
           VOS_UINT8                           ucIndex,
           VOS_VOID                           *pEvtInfo
       );

extern VOS_VOID AT_RcvTafPsEvt(
           TAF_PS_EVT_STRU                     *pstEvt
       );
extern VOS_UINT32 AT_RcvTafPsEvtCgactQryCnf(
           VOS_UINT8                           ucIndex,
           VOS_VOID                           *pEvtInfo
       );
extern VOS_UINT32 AT_RcvTafPsEvtCgeqnegTestCnf(
           VOS_UINT8                           ucIndex,
           VOS_VOID                           *pEvtInfo
       );
extern VOS_UINT32 AT_RcvTafPsEvtClearDsFlowInfoCnf(
           VOS_UINT8                           ucIndex,
           VOS_VOID                           *pEvtInfo
       );
extern VOS_UINT32 AT_RcvTafPsEvtConfigDsFlowRptCnf(
           VOS_UINT8                           ucIndex,
           VOS_VOID                           *pEvtInfo
       );
extern VOS_UINT32 AT_RcvTafPsEvtGetAnsModeInfoCnf(
           VOS_UINT8                           ucIndex,
           VOS_VOID                           *pEvtInfo
       );
extern VOS_UINT32 AT_RcvTafPsEvtGetAuthDataInfoCnf(
           VOS_UINT8                           ucIndex,
           VOS_VOID                           *pEvtInfo
       );
extern VOS_UINT32 AT_RcvTafPsEvtGetDsFlowInfoCnf(
           VOS_UINT8                           ucIndex,
           VOS_VOID                           *pEvtInfo
       );
extern VOS_UINT32 AT_RcvTafPsEvtGetDynamicEpsQosInfoCnf(
           VOS_UINT8                           ucIndex,
           VOS_VOID                           *pEvtInfo
       );
extern VOS_UINT32 AT_RcvTafPsEvtGetDynamicPrimPdpContextInfoCnf(
           VOS_UINT8                           ucIndex,
           VOS_VOID                           *pEvtInfo
       );
extern VOS_UINT32 AT_RcvTafPsEvtGetDynamicSecPdpContextInfoCnf(
           VOS_UINT8                           ucIndex,
           VOS_VOID                           *pEvtInfo
       );
extern VOS_UINT32 AT_RcvTafPsEvtGetDynamicTftInfoCnf(
           VOS_UINT8                           ucIndex,
           VOS_VOID                           *pEvtInfo
       );
extern VOS_UINT32 AT_RcvTafPsEvtGetDynamicUmtsQosInfoCnf(
           VOS_UINT8                           ucIndex,
           VOS_VOID                           *pEvtInfo
       );
extern VOS_UINT32 AT_RcvTafPsEvtGetEpsQosInfoCnf(
           VOS_UINT8                           ucIndex,
           VOS_VOID                           *pEvtInfo
       );
extern VOS_UINT32 AT_RcvTafPsEvtGetGprsActiveTypeCnf(
           VOS_UINT8                           ucIndex,
           VOS_VOID                           *pEvtInfo
       );
extern VOS_UINT32 AT_RcvTafPsEvtGetPdpContextInfoCnf(
           VOS_UINT8                           ucIndex,
           VOS_VOID                           *pEvtInfo
       );
extern VOS_UINT32 AT_RcvTafPsEvtGetPdpDnsInfoCnf(
           VOS_UINT8                           ucIndex,
           VOS_VOID                           *pEvtInfo
       );
extern VOS_UINT32 AT_RcvTafPsEvtGetPdpIpAddrInfoCnf(
           VOS_UINT8                           ucIndex,
           VOS_VOID                           *pEvtInfo
       );
extern VOS_UINT32 AT_RcvTafPsEvtGetPdpStateCnf(
           VOS_UINT8                           ucIndex,
           VOS_VOID                           *pEvtInfo
       );
extern VOS_UINT32 AT_RcvTafPsEvtGetPrimPdpContextInfoCnf(
           VOS_UINT8                           ucIndex,
           VOS_VOID                           *pEvtInfo
       );
extern VOS_UINT32 AT_RcvTafPsEvtGetSecPdpContextInfoCnf(
           VOS_UINT8                           ucIndex,
           VOS_VOID                           *pEvtInfo
       );
extern VOS_UINT32 AT_RcvTafPsEvtGetTftInfoCnf(
           VOS_UINT8                           ucIndex,
           VOS_VOID                           *pEvtInfo
       );
extern VOS_UINT32 AT_RcvTafPsEvtGetUmtsQosInfoCnf(
           VOS_UINT8                           ucIndex,
           VOS_VOID                           *pEvtInfo
       );
extern VOS_UINT32 AT_RcvTafPsEvtGetUmtsQosMinInfoCnf(
           VOS_UINT8                           ucIndex,
           VOS_VOID                           *pEvtInfo
       );
extern VOS_UINT32 AT_RcvTafPsEvtPdpActInd(
           VOS_UINT8                           ucIndex,
           VOS_VOID                           *pEvtInfo
       );
extern VOS_UINT32 AT_RcvTafPsEvtPdpDisconnectInd(
           VOS_UINT8                           ucIndex,
           VOS_VOID                           *pEvtInfo
       );
extern VOS_UINT32 AT_RcvTafPsEvtPppDialOrigCnf(
           VOS_UINT8                           ucIndex,
           VOS_VOID                           *pEvtInfo
       );
extern VOS_UINT32 AT_RcvTafPsEvtReportDsFlowInd(
           VOS_UINT8                           ucIndex,
           VOS_VOID                           *pEvtInfo
       );
extern VOS_UINT32 AT_RcvTafPsEvtReportRaInfo(
           VOS_UINT8                           ucIndex,
           VOS_VOID                           *pEvtInfo
       );
extern VOS_UINT32 AT_RcvTafPsEvtSetAnsModeInfoCnf(
           VOS_UINT8                           ucIndex,
           VOS_VOID                           *pEvtInfo
       );
extern VOS_UINT32 AT_RcvTafPsEvtSetAuthDataInfoCnf(
           VOS_UINT8                           ucIndex,
           VOS_VOID                           *pEvtInfo
       );
extern VOS_UINT32 AT_RcvTafPsEvtGetDynamicDnsInfoCnf(
           VOS_UINT8                           ucIndex,
           VOS_VOID                           *pEvtInfo
       );
extern VOS_UINT32 AT_RcvTafPsEvtSetEpsQosInfoCnf(
           VOS_UINT8                           ucIndex,
           VOS_VOID                           *pEvtInfo
       );
extern VOS_UINT32 AT_RcvTafPsEvtSetPdpDnsInfoCnf(
           VOS_UINT8                           ucIndex,
           VOS_VOID                           *pEvtInfo
       );
extern VOS_UINT32 AT_RcvTafPsEvtSetPdprofInfoCnf(
           VOS_UINT8                           ucIndex,
           VOS_VOID                           *pEvtInfo
       );
extern VOS_UINT32 AT_RcvTafPsEvtSetPdpStateCnf(
           VOS_UINT8                           ucIndex,
           VOS_VOID                           *pEvtInfo
       );
extern VOS_UINT32 AT_RcvTafPsEvtSetPrimPdpContextInfoCnf(
           VOS_UINT8                           ucIndex,
           VOS_VOID                           *pEvtInfo
       );
extern VOS_UINT32 AT_RcvTafPsEvtSetSecPdpContextInfoCnf(
           VOS_UINT8                           ucIndex,
           VOS_VOID                           *pEvtInfo
       );
extern VOS_UINT32 AT_RcvTafPsEvtSetTftInfoCnf(
           VOS_UINT8                           ucIndex,
           VOS_VOID                           *pEvtInfo
       );
extern VOS_UINT32 AT_RcvTafPsEvtSetUmtsQosInfoCnf(
           VOS_UINT8                           ucIndex,
           VOS_VOID                           *pEvtInfo
       );
extern VOS_UINT32 AT_RcvTafPsEvtSetUmtsQosMinInfoCnf(
           VOS_UINT8                           ucIndex,
           VOS_VOID                           *pEvtInfo
       );
extern TAF_UINT32 At_ReadNumTypePara(TAF_UINT8 *pucDst,TAF_UINT8 *pucSrc);
extern TAF_VOID At_ReadRspProc(
           TAF_UINT8                           ucIndex,
           MN_MSG_EVENT_INFO_STRU              *pstEvent
       );
extern VOS_VOID AT_ReportCeregResult(
    VOS_UINT8                           ucIndex,
    TAF_PHONE_EVENT_INFO_STRU          *pstEvent,
    VOS_UINT16                         *pusLength
);

/* Modified by w00167002 for L-C互操作项目, 2014-2-17, begin */
extern VOS_VOID AT_ReportSysCfgExQryCmdResult(
           TAF_MMA_SYS_CFG_PARA_STRU          *pstSysCfg,
           VOS_UINT8                           ucIndex,
           VOS_UINT16                         *pusLength
       );
extern VOS_VOID AT_ReportSysCfgQryCmdResult(
           TAF_MMA_SYS_CFG_PARA_STRU          *pstSysCfg,
           VOS_UINT8                           ucIndex,
           VOS_UINT16                         *pusLength
       );
/* Modified by w00167002 for L-C互操作项目, 2014-2-17, end */
#if( FEATURE_ON == FEATURE_CSD )
extern VOS_UINT32 AT_SendCsdCallStateInd(AT_CSD_CALL_TYPE_STATE_ENUM_UINT16 enCallState);
#endif
extern TAF_VOID At_SendSmRspProc(
           TAF_UINT8                           ucIndex,
           MN_MSG_EVENT_INFO_STRU              *pstEvent
       );
extern VOS_VOID At_SetAlsCnf(MN_AT_IND_EVT_STRU *pstData);
extern TAF_VOID At_SetCmmsRspProc(
           TAF_UINT8                           ucIndex,
           MN_MSG_EVENT_INFO_STRU              *pstEvent
       );
extern TAF_VOID At_SetCnmaRspProc(
           TAF_UINT8                           ucIndex,
           MN_MSG_EVENT_INFO_STRU              *pstEvent
       );
extern TAF_VOID At_SetCscaCsmpRspProc(
           TAF_UINT8                           ucIndex,
           MN_MSG_EVENT_INFO_STRU              *pstEvent
       );
extern VOS_VOID AT_SetMemStatusRspProc(
           VOS_UINT8                           ucIndex,
           MN_MSG_EVENT_INFO_STRU             *pstEvent
       );
extern TAF_VOID At_SetMsgProc(TAF_UINT8* pData,TAF_UINT16 usLen);
extern TAF_VOID At_SetParaRspProc( TAF_UINT8 ucIndex,
                                             TAF_UINT8 OpId,
                                             TAF_PARA_SET_RESULT Result,
                                             TAF_PARA_TYPE ParaType,
                                             TAF_VOID *pPara);
extern TAF_VOID At_SetRcvPathRspProc(
           TAF_UINT8                           ucIndex,
           MN_MSG_EVENT_INFO_STRU              *pstEvent
       );
extern VOS_VOID At_SetUus1Cnf(MN_AT_IND_EVT_STRU *pstData);
extern VOS_VOID At_SmsDeliverCbmProc(
           TAF_UINT8                           ucIndex,
           MN_MSG_EVENT_INFO_STRU              *pstEvent
       );
extern VOS_VOID At_SmsDeliverErrProc(
           VOS_UINT8                           ucIndex,
           MN_MSG_EVENT_INFO_STRU              *pstEvent
       );
extern VOS_VOID At_SmsDeliverProc(
           TAF_UINT8                           ucIndex,
           MN_MSG_EVENT_INFO_STRU              *pstEvent
       );
extern TAF_VOID At_SmsInitResultProc(
           TAF_UINT8                           ucIndex,
           MN_MSG_EVENT_INFO_STRU              *pEvent
       );
extern VOS_VOID At_SmsInitSmspResultProc(
           TAF_UINT8                           ucIndex,
           MN_MSG_EVENT_INFO_STRU              *pstEvent
       );
extern VOS_VOID AT_SmsListIndex(
           VOS_UINT16                          usLength,
           MN_MSG_DELETE_TEST_EVT_INFO_STRU   *pstPara,
           VOS_UINT16                         *pusPrintOffSet
       );
extern TAF_VOID At_SmsModSmStatusRspProc(
           TAF_UINT8                           ucIndex,
           MN_MSG_EVENT_INFO_STRU              *pstEvent
       );
extern TAF_VOID At_SmsMsgProc(MN_AT_IND_EVT_STRU *pstData,TAF_UINT16 usLen);
extern VOS_VOID At_SmsRcvMsgPathChangeProc(
           TAF_UINT8                           ucIndex,
           MN_MSG_EVENT_INFO_STRU              *pstEvent
       );
extern TAF_VOID At_SmsRspNop(
           TAF_UINT8                           ucIndex,
           MN_MSG_EVENT_INFO_STRU              *pstEvent
       );
extern VOS_VOID At_SmsSrvParmChangeProc(
           TAF_UINT8                           ucIndex,
           MN_MSG_EVENT_INFO_STRU              *pstEvent
       );
extern VOS_VOID At_SmsStorageExceedProc(
           TAF_UINT8                           ucIndex,
           MN_MSG_EVENT_INFO_STRU              *pstEvent
       );
extern VOS_VOID At_SmsStorageListProc(
           TAF_UINT8                           ucIndex,
           MN_MSG_EVENT_INFO_STRU              *pstEvent
       );
extern VOS_VOID At_SmsStubRspProc(
           VOS_UINT8                           ucIndex,
           MN_MSG_EVENT_INFO_STRU             *pstEvent
       );
extern TAF_UINT32 At_SsClass2Print(TAF_UINT8 ucClass);
extern TAF_VOID At_SsIndProc(TAF_UINT8  ucIndex,TAF_SS_CALL_INDEPENDENT_EVENT_STRU  *pEvent);
extern TAF_VOID At_SsMsgProc(TAF_UINT8* pData,TAF_UINT16 usLen);
extern TAF_UINT32 At_SsRspCusdProc(
           TAF_UINT8                           ucIndex,
           TAF_SS_CALL_INDEPENDENT_EVENT_STRU  *pEvent
       );
extern TAF_VOID At_SsRspInterrogateCcbsCnfProc(
           TAF_UINT8                           ucIndex,
           TAF_SS_CALL_INDEPENDENT_EVENT_STRU  *pEvent,
           TAF_UINT32                          *pulResult,
           TAF_UINT16                          *pusLength
       );
extern TAF_VOID At_SsRspInterrogateCnfCcwaProc(
           TAF_UINT8                           ucIndex,
           TAF_SS_CALL_INDEPENDENT_EVENT_STRU  *pEvent,
           TAF_UINT32                          *pulResult,
           TAF_UINT16                          *pusLength
       );
extern TAF_VOID At_SsRspInterrogateCnfClckProc(
           TAF_UINT8                           ucIndex,
           TAF_SS_CALL_INDEPENDENT_EVENT_STRU  *pEvent,
           TAF_UINT32                          *pulResult,
           TAF_UINT16                          *pusLength
       );
extern TAF_VOID At_SsRspInterrogateCnfClipProc(
           TAF_UINT8                           ucIndex,
           TAF_SS_CALL_INDEPENDENT_EVENT_STRU  *pEvent,
           TAF_UINT32                          *pulResult,
           TAF_UINT16                          *pusLength
       );
extern TAF_VOID At_SsRspInterrogateCnfClirProc(
           TAF_UINT8                           ucIndex,
           TAF_SS_CALL_INDEPENDENT_EVENT_STRU  *pEvent,
           TAF_UINT32                          *pulResult,
           TAF_UINT16                          *pusLength
       );
extern TAF_VOID At_SsRspInterrogateCnfCmmiProc(
           TAF_UINT8                           ucIndex,
           TAF_SS_CALL_INDEPENDENT_EVENT_STRU  *pEvent,
           TAF_UINT32                          *pulResult,
           TAF_UINT16                          *pusLength
       );
extern TAF_VOID At_SsRspInterrogateCnfColpProc(
           TAF_UINT8                           ucIndex,
           TAF_SS_CALL_INDEPENDENT_EVENT_STRU  *pEvent,
           TAF_UINT32                          *pulResult,
           TAF_UINT16                          *pusLength
       );
extern TAF_VOID At_SsRspInterrogateCnfProc(
           TAF_UINT8                           ucIndex,
           TAF_SS_CALL_INDEPENDENT_EVENT_STRU  *pEvent,
           TAF_UINT32                          *pulResult,
           TAF_UINT16                          *pusLength
       );
extern TAF_VOID At_SsRspProc(TAF_UINT8  ucIndex,TAF_SS_CALL_INDEPENDENT_EVENT_STRU  *pEvent);
extern TAF_VOID At_SsRspUssdProc(
           TAF_UINT8                           ucIndex,
           TAF_SS_CALL_INDEPENDENT_EVENT_STRU  *pEvent,
           TAF_UINT16                          *pusLength
       );
extern VOS_UINT32 At_StaRptPduInd(
           MN_MSG_BCD_ADDR_STRU                *pstScAddr,
           MN_MSG_RAW_TS_DATA_STRU             *pstPdu,
           VOS_UINT8                           *pucDst
       );
extern TAF_VOID At_STKCMDDataPrintSimple(TAF_UINT8 ucIndex,SI_STK_EVENT_INFO_STRU *pEvent);
extern TAF_VOID At_STKCMDSWPrintSimple(TAF_UINT8 ucIndex,STK_CALLBACK_EVENT STKCBEvent,SI_STK_SW_INFO_STRU *pSw);
extern VOS_UINT32 At_STKCMDTypePrint(TAF_UINT8 ucIndex,TAF_UINT32 SatType, TAF_UINT32 EventType);
extern TAF_VOID AT_STKCnfMsgProc(MN_APP_STK_AT_CNF_STRU *pstSTKCnfMsg);
extern TAF_VOID At_STKMsgProc(MsgBlock* pMsg);
extern TAF_VOID AT_STKPrintMsgProc(MN_APP_STK_AT_DATAPRINT_STRU *pstSTKPrintMsg);
extern TAF_VOID At_TAFPbMsgProc(TAF_UINT8* pData,TAF_UINT16 usLen);
extern TAF_UINT32 At_Unicode2UnicodePrint(TAF_UINT32 MaxLength,TAF_INT8 *headaddr,TAF_UINT8 *pucDst, TAF_UINT8 *pucSrc, TAF_UINT16 usSrcLen);
extern TAF_UINT16 At_UnicodeFormatPrint(const TAF_UINT8 *pSrc, TAF_UINT8 *pDest, TAF_UINT32 Dcs);
extern VOS_VOID At_UniversalTime2LocalTime(
           TIME_ZONE_TIME_STRU                 *pstUinversalTime,
           TIME_ZONE_TIME_STRU                 *pstLocalTime
       );
extern VOS_VOID At_VcEventProc(
           VOS_UINT8                           ucIndex,
           APP_VC_EVENT_INFO_STRU              *pstVcEvt,
           APP_VC_EVENT_ENUM_U32               enEvent
       );
extern TAF_VOID At_VcMsgProc(MN_AT_IND_EVT_STRU *pstData,TAF_UINT16 usLen);
extern TAF_VOID At_WriteSmRspProc(
           TAF_UINT8                           ucIndex,
           MN_MSG_EVENT_INFO_STRU              *pstEvent
       );



/* Added by w00176964 for VoLTE_PhaseI项目, 2013-8-6, begin */

extern VOS_VOID At_RcvMmaPsInitResultIndProc(
    TAF_UINT8                           ucIndex,
    TAF_PHONE_EVENT_INFO_STRU          *pEvent
    );
/* Added by w00176964 for VoLTE_PhaseI项目, 2013-8-6, end */



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

#endif /* end of Test_AtEventReport.h */
