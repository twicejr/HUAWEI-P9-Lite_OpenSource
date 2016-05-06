
#ifndef __NASEMMPLMN_H__
#define __NASEMMPLMN_H__


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "AppMmInterface.h"
#include  "LRrcLNasInterface.h"
#include  "NasEmmcEmmInterface.h"
#include  "NasEmmMrrcPubInterface.h"
#include  "NasEmmAttDetInterface.h"
#include  "NasLmmPubMFsm.h"
#include  "NasLmmPubMIntraMsg.h"
#include  "NasEmmPlmnPublic.h"
/*#include  "NasMmcSim.h"*/
#include  "NasEmmDetachAppMsgProcess.h"
#include  "NasEmmMrrc.h"


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  #pragma pack(*)    设置字节对齐方式
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 Macro
*****************************************************************************/
#define NAS_EMM_PLMN_10_MSG_IN_QUEUE      10

#define NAS_EMM_SAVE_START_INFO(stEmmStartInfo)\
        {\
            NAS_EMM_GetTransceiverType()        = stEmmStartInfo.ulTransceiverType;\
            NAS_LMM_GetCurGsmPrio()             = stEmmStartInfo.aucRatPrioList[NAS_LMM_RAT_TYPE_GSM];\
            NAS_LMM_GetCurWcdmaPrio()           = stEmmStartInfo.aucRatPrioList[NAS_LMM_RAT_TYPE_WCDMA];\
            NAS_LMM_GetCurLtePrio ()            = stEmmStartInfo.aucRatPrioList[NAS_LMM_RAT_TYPE_LTE];\
            NAS_LMM_GetCurCdma1xPrio()           = stEmmStartInfo.aucRatPrioList[NAS_LMM_RAT_TYPE_CDMA1X];\
            NAS_LMM_GetCurHrpdPrio ()            = stEmmStartInfo.aucRatPrioList[NAS_LMM_RAT_TYPE_HRPD];\
        }


#define NAS_EMM_SET_LRRCLMM_INF_USIM_STATE(ulLrrcLmmcInfUsimState)\
        {\
            if(NAS_LMM_SIM_STATUS_AVAILABLE == NAS_LMM_GetSimState())\
            {\
                ulLrrcLmmcInfUsimState = LRRC_LNAS_USIM_PRESENT;\
            }\
            else\
            {\
                ulLrrcLmmcInfUsimState = LRRC_LNAS_USIM_ABSENT;\
            }\
        }

#define NAS_EMM_PLMN_SRCH_NO_IMSI_TRUE              VOS_TRUE
#define NAS_EMM_PLMN_SRCH_NO_IMSI_FALSE            VOS_FALSE


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/


/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
 结构名    : RRC_MM_STOP_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC_MM_STOP_REQ_STRU的数据结构
*****************************************************************************/
typedef LRRC_LMM_POWER_OFF_REQ_STRU       RRC_MM_STOP_REQ_STRU;

/*****************************************************************************
 结构名    : RRC_MM_STOP_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RRC_MM_STOP_CNF_STRU的数据结构
*****************************************************************************/
typedef LRRC_LMM_POWER_OFF_CNF_STRU       RRC_MM_STOP_CNF_STRU;


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/


extern VOS_UINT32  NAS_EMM_PLMN_SendAppStartCnf(
                           VOS_UINT32                              ulAppRslt ,
                           VOS_UINT32                              ulOpId);
extern VOS_UINT32  NAS_EMM_PLMN_SendAppStopCnf(
                           VOS_UINT32                              ulAppMmStopParam,
                           VOS_UINT32                              ulOpId);
extern VOS_UINT32  NAS_EMM_PLMN_SendMmcStartReq(
                           VOS_UINT32                              ulStartCause );
extern VOS_UINT32  NAS_EMM_PLMN_SendMmcStopReq( VOS_VOID );
extern VOS_UINT32  NAS_EMM_PLMN_SendRrcStartReq( VOS_VOID );
extern VOS_UINT32  NAS_EMM_PLMN_SendRrcStopReq( VOS_VOID );
extern VOS_VOID    NAS_EMM_PLMN_SendEmmEsmStautsInd(EMM_ESM_ATTACH_STATUS_ENUM_UINT32 ulStatRst);
extern VOS_VOID    NAS_EMM_PLMN_ImsiPagingProc(VOS_VOID);
extern VOS_VOID    NAS_EMM_PLMN_STmsiPagingProc(VOS_VOID);

extern VOS_UINT32  NAS_EMM_PLMN_SendMmcStartReq(
                    VOS_UINT32                              ulStartCause );
extern VOS_VOID NAS_EMM_ReadImsiErr( VOS_VOID );
/*
extern VOS_VOID  NAS_EMM_SendMmcErrInd( VOS_VOID );*/
extern VOS_UINT32  NAS_EMM_MmcStartCheck(
                    const MMC_LMM_START_REQ_STRU          *pstAppStartReq,
                          NAS_EMM_START_INFO_STRU         *pstEmmStartInfo);
extern VOS_UINT32  NAS_EMM_StartRatIsExist(const MMC_LMM_START_REQ_STRU *pstAppStartReq);
extern VOS_UINT32  NAS_EMM_lteRatIsOnlyExist(VOS_VOID);
extern VOS_UINT32 NAS_EMM_MsDrgSsNoImsiMsgSysInfoInd(
                                    VOS_UINT32              ulMsgId,
                                    VOS_VOID               *pMsg );
extern VOS_VOID    NAS_EMM_AppSendAttRstDefaultReqType
(
    MMC_LMM_ATTACH_RSLT_ENUM_UINT32     ulAttRslt
);
extern VOS_VOID NAS_EMM_PLMN_CsPagingProc(LRRC_LNAS_PAGING_UE_ID_ENUM_UINT32 enPagingUeId);

extern VOS_VOID NAS_EMM_PagingErrRecord
(
    EMM_OM_ERRLOG_PAGING_ENUM_UINT16  enPagingType,
    EMM_OM_LMM_PAGING_FAIL_CAUSE_ENUM_UINT8 enPagingFailCause
);
extern VOS_VOID    NAS_EMM_EsmSendStartNotifyInd (VOS_VOID);

extern VOS_VOID NAS_EMM_SndAcpuOmFaultErrLogInd(
    VOS_VOID                           *pData,
    VOS_UINT32                          ulDataLen,
    LNAS_OM_ERRLOG_ALM_ID_ENUM_UINT16   usAlmId
);
extern VOS_VOID NAS_EMM_ImprovePerformceeErrReport
(
    EMM_OM_ERRLOG_IMPROVEMENT_TYPE_ENUM_UINT16  enImproveType
);
/*****************************************************************************
  9 OTHERS
*****************************************************************************/










#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of NasEmmPlmn.h */
