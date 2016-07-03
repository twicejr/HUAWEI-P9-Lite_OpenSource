

#ifndef __MN_MSG_EXT_H__
#define __MN_MSG_EXT_H__


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "MnComm.h"
#include  "TafTypeDef.h"
#include  "TafCbaProcTimer.h"
#include  "TafCbaMain.h"
#include "NasSms.h"

#include "TafMmaInterface.h"
#include "TafInternalInterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  1 接口函数声明
*****************************************************************************/
#if ( VOS_WIN32 == VOS_OS_VER )
extern VOS_VOID     USIMM_SendSMSDataInd1(VOS_VOID);
extern VOS_VOID     USIMM_SendSMSDataInd2(VOS_VOID);
#endif

VOS_VOID MN_MSG_ProcAppReqMsg(
    MN_APP_REQ_MSG_STRU                 * pstAppMsg
);

VOS_VOID  TAF_MSG_ProcTafMsg (
    struct MsgCB                       *pstMsg
);

#if (FEATURE_IMS == FEATURE_ON)

VOS_VOID TAF_MSG_RcvImsaRpRpt(SMR_SMT_MO_REPORT_STRU *pstMsg);
VOS_VOID TAF_MSG_ProcImsaMsg(VOS_VOID * pMsg);
#endif


VOS_VOID MN_MSG_Init(VOS_VOID);


VOS_VOID  MN_MSG_RcvUsimSetFileRsp(
    VOS_VOID                            *pMsg
);


VOS_VOID MN_MSG_RcvUsimGetFileRsp(
    VOS_VOID                            *pMsg
);


VOS_VOID MN_MSG_RcvUsimEnvelopeCnf(
        VOS_VOID                            *pMsg
);


VOS_VOID  MN_MSG_RcvUsimRefreshInd(
    VOS_VOID                            *pMsg
);


VOS_VOID MN_MSG_RcvUsimGetMaxRecRsp(
    VOS_VOID                            *pMsg
);


VOS_VOID MN_MSG_ProcTimeoutMsg(
    REL_TIMER_MSG                       * pTmrMsg
);


VOS_VOID MN_MSG_ProcSmsMsg(
    VOS_VOID                            *pMsg
);


VOS_VOID MN_MSG_CfgDataInit(
    MNPH_USIM_STATUS_ENUM_U32         enUsimStatus
);


extern VOS_VOID MN_MSG_SmInitFinish(
    MN_CLIENT_ID_T                      clientId
);


VOS_VOID MN_MSG_FinishMoProc(
    VOS_VOID
);


VOS_VOID MN_MSG_SmspInitFinish(
    MN_CLIENT_ID_T                      clientId
);


extern VOS_VOID MN_MSG_PrintUsimRec(VOS_VOID);


extern VOS_VOID MN_MSG_PrintCurrSmsRec(VOS_VOID);


extern VOS_VOID MN_MSG_PrintEfUstInfo(VOS_VOID);


extern VOS_VOID MN_MSG_PrintMsgMoEntity(VOS_VOID);


extern VOS_VOID MN_MSG_PrintMsgMtEntity(VOS_VOID);


extern VOS_VOID MN_MSG_PrintSmsrInfo(VOS_VOID);


extern VOS_VOID MN_MSG_PrintSmsInfo(VOS_VOID);


extern VOS_VOID MN_MSG_PrintSmspInfo(VOS_VOID);


extern VOS_VOID MN_MSG_PrintSmssInfo(VOS_VOID);


extern VOS_VOID MN_MSG_PrintInterTpMr(VOS_VOID);


extern VOS_VOID MN_MSG_PrintCfgParm(VOS_VOID);


extern VOS_VOID MN_MSG_PrintUsimStatusInfo(VOS_VOID);


extern VOS_VOID MN_MSG_PrintSetUsimRec(VOS_VOID);


extern VOS_VOID MN_MSG_PrintOpId();


extern VOS_VOID MN_MSG_PrintDomainRegFlag(
    VOS_VOID
);


extern VOS_VOID MN_MSG_PrintNetDecodeData(VOS_VOID);


extern VOS_VOID MN_MSG_PrintTafDecodeData(VOS_VOID);


extern VOS_VOID MN_MSG_PrintSrvParamStru(
    MN_MSG_SRV_PARAM_STRU               *pstSrvParam
);


extern VOS_VOID MN_MSG_PrintTimerInfo(VOS_VOID);


VOS_VOID MN_MSG_PrintMoNum(VOS_VOID);


VOS_VOID MN_MSG_PrintMtNum(VOS_VOID);


VOS_VOID NAS_MSG_SndOutsideContextData_Part1(VOS_VOID);


VOS_VOID NAS_MSG_SndOutsideContextData_Part2(VOS_VOID);


VOS_VOID NAS_MSG_SndOutsideContextData_Part3(VOS_VOID);

#ifdef __PS_WIN32_RECUR__

VOS_UINT32 NAS_MSG_RestoreContextData_Part1(struct MsgCB * pMsg);


VOS_UINT32 NAS_MSG_RestoreContextData_Part2(struct MsgCB * pMsg);


VOS_UINT32 NAS_MSG_RestoreContextData_Part3(struct MsgCB * pMsg);

#endif



VOS_VOID MN_MSG_DispatchUsimMsg(struct MsgCB * pstMsg);


VOS_VOID MN_MSG_GetFdnMeCfg(VOS_VOID);


VOS_VOID MN_MSG_ProcFdnCnf(struct MsgCB * pstMsg);


VOS_UINT32 MN_MSG_AppStorageUnavailable(
    MN_MSG_RCVMSG_ACT_ENUM_U8           enRcvSmAct,
    MN_MSG_MEM_FLAG_ENUM_U8             enAppMemStatus,
    VOS_BOOL                           *pbUnavailableFlag
);


VOS_UINT32 MN_MSG_UeStorageUnavailable(
    MN_MSG_MEM_STORE_ENUM_U8            enSmMemStore,
    VOS_BOOL                           *pbUnavailableFlag
);


VOS_UINT32 MN_MSG_IsProtocolSendDomain(VOS_VOID);

VOS_VOID TAF_MSG_RcvMmaCsServiceChangeNotify(
    struct MsgCB                       *pstMsg
);

#if (FEATURE_ON == FEATURE_PTM)
VOS_VOID MN_MSG_FailErrRecord(TAF_MSG_ERROR_ENUM_UINT32 enErrorCode);
#endif
VOS_VOID TAF_MSG_RcvSpmSmmaRsp(
    struct MsgCB                       *pstMsg
);

/* TAF_MSG_SendSpmSmmaInd函数声明已经移到MnMsgSendSpm.h文件中 */


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

#endif /* __MN_MSG_EXT_H__ */

