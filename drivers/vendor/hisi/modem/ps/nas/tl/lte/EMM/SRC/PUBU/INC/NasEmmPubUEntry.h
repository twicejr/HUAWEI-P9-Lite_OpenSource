/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasEmmPubUEntry.h
    Description :
    History     :
      1.  hanlufeng 41410  Draft Enact
******************************************************************************/
#ifndef _NASEMMPUBUENTRY_H
#define _NASEMMPUBUENTRY_H



/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include    "NasLmmPubMOsa.h"
#include    "NasLmmPubMEntry.h"


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
  2 macro
*****************************************************************************/
#define NAS_EMM_GENERIC_CONTAINER_TYPE_LPP      (1)
#define NAS_EMM_GENERIC_CONTAINER_TYPE_LCS      (2)

#define NAS_EMM_PUB_VOS_MSG_HEADER_LEN  20

#define NAS_EMM_COMP_INTRA_MSG_HEADER(pMsg, ulLen) \
        {\
            (pMsg)->ulSenderCpuId       = VOS_LOCAL_CPUID;\
            (pMsg)->ulSenderPid         = PS_PID_MM;\
            (pMsg)->ulReceiverCpuId     = VOS_LOCAL_CPUID;\
            (pMsg)->ulReceiverPid       = PS_PID_MM;\
            (pMsg)->ulLength            = ulLen;\
        }

#define NAS_EMM_COMP_ESM_MSG_HEADER(pMsg, ulMsgLenthNoHeader)\
        {\
            (pMsg)->ulSenderCpuId       = VOS_LOCAL_CPUID;\
            (pMsg)->ulSenderPid         = PS_PID_MM;\
            (pMsg)->ulReceiverCpuId     = VOS_LOCAL_CPUID;\
            (pMsg)->ulReceiverPid       = PS_PID_ESM;\
            (pMsg)->ulLength            = (ulMsgLenthNoHeader);\
        }


#define NAS_EMM_PUB_INTRAMSG_LENGTH_NO_HEADER(XXX_EMM_MSG_STRU) \
                    (sizeof(XXX_EMM_MSG_STRU) - NAS_EMM_PUB_VOS_MSG_HEADER_LEN)

#define NAS_EMM_PRE_MSG_IS_MM_CN_MSG(ulEventType)\
            (( (VOS_UINT32)NAS_EMM_ET_EMM_RRC_DATA_IND_MM_MSG_BEGIN  <  ulEventType ) && \
            ( (VOS_UINT32)NAS_EMM_ET_EMM_RRC_DATA_IND_MM_MSG_END    >  ulEventType) ) && \
            (NAS_LMM_GET_BT_MD_ET(ulEventType) == NAS_LMM_GET_BT_MD_ET(ID_LRRC_LMM_DATA_IND))


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/



/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  5 STRUCT
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/

extern  VOS_UINT32  NAS_EMM_MsgProcessInFsm(MsgBlock           *pMsg,
                                            VOS_UINT32          ulEventType);
extern  VOS_UINT32  NAS_EMM_MsgPreProcess(  NAS_EMM_EVENT_TYPE_ENUM_UINT32      ulEt,
                                            MsgBlock                           *pMsg );
extern  VOS_VOID    NAS_EMM_SmRabmAbnarmalProc(     VOS_VOID );
extern  VOS_UINT32  NAS_EMM_PUB_SendMmcStartReq(    VOS_UINT32  encause  );
/*extern  VOS_VOID    NAS_EMM_PUB_SendPlmnSearchReq(  VOS_UINT32  ulStartCause );*/
extern  VOS_VOID    NAS_EMM_PUB_SendEsmStatusInd(   VOS_UINT32  stATTACHStatus );
extern  VOS_UINT32  NAS_EMM_PreProcMsgEmmInfo( NAS_EMM_CN_MSG_STRU_UNION  * pCnMsg );
extern  VOS_UINT32  NAS_EMM_PreProcMsgDataInd( VOS_VOID );
extern  VOS_UINT32  NAS_EMM_PreProcMsgEmmStatus( NAS_EMM_CN_MSG_STRU_UNION  * pCnMsg );
extern  VOS_UINT32  NAS_EMM_PreProcMsgDlNasTransport( NAS_EMM_CN_MSG_STRU_UNION  * pMsg );

extern VOS_VOID  NAS_EMM_ProcMsgCsSerNotification(
    NAS_EMM_CN_CS_SER_NOTIFICAIOTN_STRU          *pstCsSerNotification
);


extern  VOS_VOID    NAS_EMM_CompCnEmmStatus( LRRC_LNAS_MSG_STRU    *pEmmStatus,
                                                  VOS_UINT32          *pulIndex,
                                                  VOS_UINT8            ucEmmCause);
extern  VOS_VOID    NAS_EMM_SendMsgEmmStatus( VOS_UINT8 ucRes );
extern  VOS_VOID    NAS_EMM_ReadEmmNvim( VOS_VOID );
extern VOS_UINT32   NAS_LMM_PreProcMmcDisableReq( MsgBlock  *pMsg );
extern VOS_UINT32   NAS_LMM_PreProcMmcEnableReq( MsgBlock  *pMsg );
extern VOS_UINT32   NAS_EMM_PreProcMsgCsSerNotification
(
    NAS_EMM_CN_MSG_STRU_UNION          *pCnMsg
);
extern VOS_UINT32  NAS_EMM_IsBearIsrActBefore
(
    VOS_UINT32      ulEpsId
);
extern VOS_UINT32  NAS_EMM_IsBearIsrActAfter(VOS_VOID);
extern VOS_UINT32  NAS_EMM_PreProcMsgEsmBearModifyReq
(
    MsgBlock *          pMsg
);
extern VOS_UINT32  NAS_EMM_PreProcMsgT3412Exp(MsgBlock *pMsg );
extern VOS_UINT32  NAS_EMM_PreProcMsgT3423Exp(MsgBlock *pMsg );
extern VOS_UINT32  NAS_EMM_PreProcMsgGmmTimerStateNotifyMsg(MsgBlock *pMsg );

extern VOS_UINT32  NAS_LMM_PreProcMmcImsVoiceCapChangeNotify(MsgBlock *    pMsg );
extern VOS_UINT32  NAS_LMM_PreProcMsgSrvccNofify(MsgBlock *    pMsg );

extern VOS_UINT32  NAS_LMM_PreProcDsdsBeginSessionNotify(MsgBlock *          pMsg);
extern VOS_UINT32  NAS_LMM_PreProcDsdsEndSessionNotify(MsgBlock *          pMsg);


#if(VOS_WIN32 == VOS_OS_VER)
/*单板上暂时不导出*/
extern VOS_UINT32  NAS_EMM_PreProcMsgReplay(MsgBlock *          pMsg );
extern VOS_UINT32  NAS_EMM_ExportContextData(VOS_VOID);
extern VOS_VOID    NAS_EMM_PUB_SendEsmExportCtx(VOS_VOID);
#endif

extern VOS_VOID NAS_EMM_LocalDetachErrRecord(
        EMM_ERR_LOG_LOCAL_DETACH_TYPE_ENUM_UINT16       enLocalDetType);

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

#endif /* end of MapsTemplate.h*/

