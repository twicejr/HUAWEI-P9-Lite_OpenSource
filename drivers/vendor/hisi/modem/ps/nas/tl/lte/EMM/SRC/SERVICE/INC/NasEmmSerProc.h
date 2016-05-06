/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasEmmSER.h
    Description :
    History     :
      1.  2008-09-03 周岩 00125190 FILE_CREAT
      2.  hanlufeng 41410  2009-03-11  BA8D01164 把NAS_EMM_INFO_GUTI  修改为
          SER专用的接口
******************************************************************************/

#ifndef _NASEMMSER_H
#define _NASEMMSER_H


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include    "vos.h"
#include    "NasLmmPubMFsm.h"
/*#include    "LRrcLNasInterface.h"*/
#include    "EmmEsmInterface.h"
#include    "NasEmmPubUCnMsgDecode.h"
#include    "EmmTcInterface.h"


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

#define   RRC_NAS_MSG_PRIORTY_LOW           0       /* 消息优先级：Low      */
#define   RRC_NAS_MSG_PRIORTY_HIGH          1       /* 消息优先级：High     */

#define   NAS_EMM_SER_MSG_PS                1       /* 用来指明是PS域*/
#define   NAS_EMM_SER_MSG_CS                0       /* 用来指明是CS域*/

#define   EMM_CN_SECURITY_HEADER_TYPE_SER_REQ       0xC7   /* 1100  0111  */

#define NAS_EMM_ZERO                        0
#define EMM_LEN_MSG_ID                      4                   /* ulMsgId   */
#define EMM_LEN_IE_MSGSIZE_OF_NAS_MSG_STRU  4
#define EMM_LEN_VOS_MSG_HEADER              20
#define EMM_LEN_TAUSER_EST_CAUSE            4
#define EMM_LEN_TAUSER_EST_MSG_TYPE         4

#define EMM_SER_TIMER_NUM                   1

#define NAS_EMM_LEN_CN_MSG_PD_SI            1
#define NAS_EMM_LEN_CN_MSG_SEC_H_TYPE       0
#define NAS_EMM_LEN_CN_MSG_KSI_SEQNUM       1
#define NAS_EMM_LEN_CN_MSG_SHORT_MAC        2

#define NAS_EMM_TAUSER_BIT_SLCT                 1
#define NAS_EMM_TAUSER_BIT_NO_SLCT              0

#define NAS_EMM_SER_MAX_ESM_BUFF_MSG_NUM    11

#define NAS_EMM_TYPE_OF_IDENTITY_TMSI_PTMSI_MTMSI   (0x04)
#define NAS_EMM_EXTENDED_SER_REQ_CSFB_RSP_IEI       (0xB0)

#define NAS_EMM_DISCARD_ERABM_RESET_REQ_MAX_CNT   3

#define EMM_COUNT_DATA_REQ_LEN(NAS_CN_MSG_LEN)\
        (\
            EMM_LEN_MSG_ID              +   \
            EMM_LEN_IE_MSGSIZE_OF_NAS_MSG_STRU  +\
            (NAS_CN_MSG_LEN)+\
            EMM_LEN_TAUSER_EST_CAUSE+\
            EMM_LEN_TAUSER_EST_MSG_TYPE\
        )

#define EMM_COMP_MM_MSG_HEADER(pMsg,ulMsgLenthNoHeader)\
        {\
            (pMsg)->ulSenderCpuId       = VOS_LOCAL_CPUID;\
            (pMsg)->ulSenderPid         = PS_PID_MM;\
            (pMsg)->ulReceiverCpuId     = VOS_LOCAL_CPUID;\
            (pMsg)->ulReceiverPid       = PS_PID_MM;\
            (pMsg)->ulLength            = (ulMsgLenthNoHeader);\
        }

#define EMM_COMP_APP_MSG_HEADER(pMsg,MsgLenthNoHeader)\
        {\
            (pMsg)->ulSenderCpuId       = VOS_LOCAL_CPUID;\
            (pMsg)->ulSenderPid         = PS_PID_MM;\
            (pMsg)->ulReceiverCpuId     = VOS_LOCAL_CPUID;\
            (pMsg)->ulReceiverPid       = PS_PID_APP;\
            (pMsg)->ulLength            = (MsgLenthNoHeader);\
            (pMsg)->usOriginalId        = UE_MODULE_MM_ID;\
            (pMsg)->usTerminalId        = UE_APP_SUBSYS_ID;\
        }

#define EMM_COMP_ERABM_MSG_HEADER(pMsg,ulMsgLenthNoHeader)\
        {\
            (pMsg)->ulSenderCpuId       = VOS_LOCAL_CPUID;\
            (pMsg)->ulSenderPid         = PS_PID_MM;\
            (pMsg)->ulReceiverCpuId     = VOS_LOCAL_CPUID;\
            (pMsg)->ulReceiverPid       = PS_PID_RABM;\
            (pMsg)->ulLength            = (ulMsgLenthNoHeader);\
       }

#define NAS_EMM_COUNT_CN_SER_REQ_LEN         \
        (\
            NAS_EMM_LEN_CN_MSG_PD_SI            +   \
            NAS_EMM_LEN_CN_MSG_SEC_H_TYPE       +   \
            NAS_EMM_LEN_CN_MSG_KSI_SEQNUM       +   \
            NAS_EMM_LEN_CN_MSG_SHORT_MAC         \
        )


/* 得到SER模块的全局变量 */
#define NAS_EMM_SER_GetEmmSERCtrlAddr()                 (&g_stEmmSERCtrlTbl)


/* SER触发原因相关操作，包括得到和保存 */
#define NAS_EMM_SER_GetEmmSERStartCause()                (g_stEmmSERCtrlTbl.ucEmmSERStartCause)
#define NAS_EMM_SER_SaveEmmSERStartCause(SERStartCause)  (NAS_EMM_SER_GetEmmSERStartCause() = (SERStartCause))

#define NAS_EMM_SER_GetEmmSerCsfbRsp()                  (g_stEmmSERCtrlTbl.enEmmSerCsfbRsp)
#define NAS_EMM_SER_SaveEmmSerCsfbRsp(SerCsfbRsp)       (NAS_EMM_SER_GetEmmSerCsfbRsp() = (SerCsfbRsp))

#define NAS_EMM_SER_GetEmmSerCsfbAbortFlag()            (g_stEmmSERCtrlTbl.enEmmSerCsfbAbortFlag)
#define NAS_EMM_SER_SaveEmmSerCsfbAbortFlag(CsfbAbortFlag) (NAS_EMM_SER_GetEmmSerCsfbAbortFlag() = (CsfbAbortFlag))
#define NAS_EMM_SER_GetSsOrLppOpid()                    (g_stEmmSERCtrlTbl.ulSsOrLppOpid)
#define NAS_EMM_SER_SaveSsOrLppOpid(ulOpid)             (NAS_EMM_SER_GetSsOrLppOpid() = (ulOpid))

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/

/*======================= SER控制相关结构 =======================*/
enum    NAS_EMM_SER_RESULT_ENUM
{
    NAS_EMM_SER_RESULT_SUCC             = 0x00,
    NAS_EMM_SER_RESULT_REJ              = 0x01,
    NAS_EMM_SER_RESULT_ABNORMAL         = 0x02,

    NAS_EMM_SER_RESULT_BUTT
};
typedef VOS_UINT8   NAS_EMM_SER_RESULT_ENUM_UINT8;

enum    NAS_EMM_MT_CSFB_TYPE_ENUM
{
    NAS_EMM_MT_CSFB_TYPE_CS_PAGING              = 0x00,
    NAS_EMM_MT_CSFB_TYPE_CS_SER_NOTIFICATION    = 0x01,

    NAS_EMM_MT_CSFB_TYPE_BUTT
};
typedef VOS_UINT8   NAS_EMM_MT_CSFB_TYPE_ENUM_UINT8;
/*****************************************************************************
  5 STRUCT
*****************************************************************************/


/*======================= SER控制结构 =======================*/
typedef struct
{
    NAS_EMM_SER_START_CAUSE_ENUM_UINT8      ucEmmSERStartCause;         /*SER触发原因*/
    NAS_EMM_CSFB_RSP_ENUM_UINT8             enEmmSerCsfbRsp;            /*CSFB RSPONSE*/
    NAS_EMM_CSFB_ABORT_FLAG_ENUM_UINT8      enEmmSerCsfbAbortFlag;      /*CSFB ABORT标识*/
    VOS_UINT8                               aucEmmRsv;                  /*RESERVED*/

    VOS_UINT32                              ulSsOrLppOpid;
}NAS_EMM_SER_CTRL_STRU;

/*****************************************************************************
 结构名    : NAS_EMM_SER_ESM_MSG_BUF_STRU
 结构说明  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulEsmMsgCnt;
    VOS_VOID                           *apucEsmMsgBuf[NAS_EMM_SER_MAX_ESM_BUFF_MSG_NUM];
}NAS_EMM_SER_ESM_MSG_BUF_STRU;

typedef VOS_VOID ( * NAS_LMM_SER_REJ_CAUSE_PROC_FUN )( const NAS_EMM_CN_SER_REJ_STRU   *pMsgStru );

typedef struct
{
    NAS_EMM_CN_CAUSE_ENUM_UINT8         enRejCauseVal; /* 拒绝原因值 */
    NAS_LMM_SER_REJ_CAUSE_PROC_FUN      pfRejCauseProcFun; /* 拒绝原因值的处理函数 */
}NAS_LMM_SER_REJ_CAUSE_PROC_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/

extern NAS_EMM_SER_CTRL_STRU            g_stEmmSERCtrlTbl;
extern NAS_EMM_SER_ESM_MSG_BUF_STRU     g_stEmmEsmMsgBuf;
extern NAS_LMM_SER_REJ_CAUSE_PROC_STRU  gstEmmSerRejCauseProcTbl[17];

extern VOS_UINT32        gstEmmSerRejCauseProcTblLen;

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_VOID    NAS_EMM_SER_SendMrrcDataReq_Tcdata
(
    EMM_ETC_DATA_REQ_STRU               *pMsg
);
extern VOS_VOID   NAS_EMM_SER_CompCnServiceReq(  LRRC_LNAS_MSG_STRU   *pNasMsg);
extern VOS_VOID   NAS_EMM_SER_SendMrrcDataReq_ServiceReq(VOS_VOID);
extern VOS_VOID   NAS_EMM_SER_SendMrrcDataReq_ESMdata
(
    EMM_ESM_MSG_STRU                   *pstEsmMsg,
    VOS_UINT32                          ulEsmmmOpId
);
extern VOS_VOID   NAS_EMM_SER_SendRabmReestInd(EMM_ERABM_REEST_STATE_ENUM_UINT32
                                                                enRabmReestState);
extern VOS_VOID   NAS_EMM_SER_AbnormalOver(VOS_VOID);
extern VOS_UINT32 NAS_EMM_SER_CHKFSMStateMsgp(  NAS_EMM_MAIN_STATE_ENUM_UINT16  stMS,
                                                            NAS_EMM_SUB_STATE_ENUM_UINT16   stSS,
                                                            VOS_VOID   *pMsgStru);
extern VOS_VOID   NAS_EMM_SER_RrcRelCause_T3417Exp(VOS_VOID);
extern VOS_VOID   NAS_EMM_SER_RrcRelCause_SERREJ367(VOS_VOID);
/* 新增出参,TAU发起原因 */
extern VOS_UINT32 NAS_EMM_SER_SuccNeedtoContinueTau(NAS_LMM_OM_TAU_START_TYPE_ENUM_UINT32 *pulTauStartType);

extern VOS_UINT32 NAS_EMM_SER_AbnormalNeedtoContinueTau(VOS_VOID);
extern VOS_VOID  NAS_EMM_SER_SERREJ368
(
    const NAS_EMM_CN_SER_REJ_STRU   *pMsgStru
);
extern VOS_VOID  NAS_EMM_SER_SERREJ7
(
    const NAS_EMM_CN_SER_REJ_STRU   *pMsgStru
);
extern VOS_VOID  NAS_EMM_SER_SERREJ8
(
    const NAS_EMM_CN_SER_REJ_STRU   *pMsgStru
);
extern VOS_VOID  NAS_EMM_SER_SERREJ9
(
    const NAS_EMM_CN_SER_REJ_STRU   *pMsgStru
);
extern VOS_VOID  NAS_EMM_SER_SERREJ10
(
    const NAS_EMM_CN_SER_REJ_STRU   *pMsgStru
);
extern VOS_VOID  NAS_EMM_SER_SERREJ11
(
    const NAS_EMM_CN_SER_REJ_STRU   *pMsgStru
);
extern VOS_VOID  NAS_EMM_SER_SERREJ12
(
    const NAS_EMM_CN_SER_REJ_STRU   *pMsgStru
);
extern VOS_VOID  NAS_EMM_SER_SERREJ13
(
    const NAS_EMM_CN_SER_REJ_STRU   *pMsgStru
);
extern VOS_VOID  NAS_EMM_SER_SERREJ15
(
    const NAS_EMM_CN_SER_REJ_STRU   *pMsgStru
);

extern VOS_UINT32 NAS_EMM_SndServiceReqFailProc(VOS_VOID* pMsg,VOS_UINT32 *pulIsDelBuff);

extern VOS_UINT32 NAS_EMM_SndExtendedServiceReqFailProc(VOS_VOID* pMsg,VOS_UINT32 *pulIsDelBuff);


extern VOS_UINT32 NAS_EMM_SndExtendedServiceReqSuccProc(VOS_VOID* pMsg);

extern VOS_VOID  NAS_EMM_SER_SERREJ18
(
    const NAS_EMM_CN_SER_REJ_STRU   *pMsgStru
);
/* leixiantiao 00258641 降低圈复杂度 begin */
#if(FEATURE_ON == FEATURE_CSG)
extern VOS_VOID NAS_EMM_SER_SERREJ25
(
    const NAS_EMM_CN_SER_REJ_STRU   *pMsgStru
);
#endif
extern VOS_VOID  NAS_EMM_SER_SERREJ22
(
    const NAS_EMM_CN_SER_REJ_STRU   *pMsgStru
);
extern VOS_VOID NAS_EMM_SER_SERREJ35
(
    const NAS_EMM_CN_SER_REJ_STRU   *pMsgStru
);
/* leixiantiao 00258641 降低圈复杂度 end */


extern VOS_VOID  NAS_EMM_SER_SERREJ40
(
    const NAS_EMM_CN_SER_REJ_STRU   *pMsgStru
);

extern VOS_VOID  NAS_EMM_SER_SERREJ39
(
    const NAS_EMM_CN_SER_REJ_STRU   *pMsgStru
);
extern VOS_VOID  NAS_EMM_SER_SERREJ42
(
    const NAS_EMM_CN_SER_REJ_STRU   *pMsgStru
);
extern VOS_VOID   NAS_EMM_SER_RcvRrcRelInd(VOS_VOID);
extern VOS_VOID   NAS_EMM_SER_RcvServiceRejectMsg(NAS_EMM_CN_SER_REJ_STRU   *pMsgStru);
extern VOS_VOID   NAS_EMM_SER_ServiceReqRejectOtherCause(VOS_VOID );
extern VOS_VOID   NAS_EMM_SerClearEsmDataBuf( VOS_VOID );

extern VOS_UINT32 NAS_EMM_SER_IsNotEmergencyCsfb(VOS_VOID);
extern VOS_VOID    NAS_EMM_SER_RcvRabmReestReq
(
    VOS_UINT32                          ulIsEmcType
);
extern VOS_VOID   NAS_EMM_SER_RcvRrcStmsiPagingInd(VOS_VOID);
extern VOS_VOID   NAS_EMM_SER_RcvRrcCsPagingInd
(
    LRRC_LNAS_PAGING_UE_ID_ENUM_UINT32 enPagingUeId
);

extern VOS_UINT32 NAS_EMM_SER_CsDomainNotRegProcNormalCsfb(VOS_VOID);
extern VOS_UINT32 NAS_EMM_SER_CheckCsfbNeedHighPrioStore(VOS_VOID);
extern VOS_UINT32 NAS_EMM_SER_CheckCsfbNeedLowPrioStore(MM_LMM_CSFB_SERVICE_TYPE_ENUM_UINT32          enCsfbSrvTyp);
extern VOS_UINT32 NAS_EMM_SER_VerifyNormalCsfb(VOS_VOID);

extern VOS_UINT32 NAS_EMM_SER_VerifyMtCsfb( VOS_VOID );
extern VOS_UINT32 NAS_EMM_SER_VerifyCsfb(MM_LMM_CSFB_SERVICE_TYPE_ENUM_UINT32  enCsfbSrvType);

extern VOS_VOID  NAS_EMM_MmSendCsfbSerPaingInd
(
    NAS_EMM_MT_CSFB_TYPE_ENUM_UINT8     enMtCsfbType,
    const NAS_EMM_CN_CS_SER_NOTIFICAIOTN_STRU *pstCsSerNotification,
    LRRC_LNAS_PAGING_UE_ID_ENUM_UINT32 enPagingUeId
);

extern VOS_VOID    NAS_EMM_SER_SendMrrcDataReq_ExtendedServiceReq(VOS_VOID);
extern VOS_VOID  NAS_EMM_MmSendCsfbSerEndInd
(
    MM_LMM_CSFB_SERVICE_RSLT_ENUM_UINT32     enCsfbSrvRslt,
    NAS_EMM_CN_CAUSE_ENUM_UINT8              ucEMMCnCause
);
extern VOS_VOID   NAS_EMM_SER_RcvEsmDataReq(VOS_VOID   *pMsgStru);
extern VOS_VOID   NAS_EMM_SER_SaveEsmMsg(const EMM_ESM_DATA_REQ_STRU  *pMsgStru);
extern VOS_VOID NAS_EMM_SER_DeleteEsmMsg
(
    VOS_UINT32                          ulOpid
);
extern VOS_VOID   NAS_EMM_SER_RcvRabmDrbSetupInd(const VOS_VOID   *pMsgStru);
extern VOS_BOOL   NAS_EMM_SER_IsSameEsmMsgInBuf(const EMM_ESM_DATA_REQ_STRU  *pMsgStru);
extern VOS_VOID   NAS_EMM_SER_SndEsmBufMsg( VOS_VOID );
extern VOS_VOID   NAS_EMM_FreeSerDyn( VOS_VOID );

extern VOS_VOID  NAS_EMM_MmcSendSerResultIndRej
(
    NAS_EMM_CN_CAUSE_ENUM_UINT8       ucCnCause
);
extern VOS_VOID  NAS_EMM_MmcSendSerResultIndOtherType
(
    MMC_LMM_SERVICE_RSLT_ENUM_UINT32    ulSerRslt
);

extern VOS_VOID  NAS_EMM_MmcSendSerResultIndT3417Exp(VOS_VOID);

extern VOS_VOID NAS_EMM_TranStateRegNormalServiceOrRegUpdateMm(VOS_VOID);
extern VOS_VOID    NAS_EMM_CompCnExtendedSerReqMoNasMsg
(
    VOS_UINT8                          *pucCnMsg,
    VOS_UINT32                         *pulIndex
);
extern VOS_VOID NAS_EMM_RestartSerProcedural(VOS_VOID);

extern VOS_VOID NAS_EMM_TranStatePsNormalServiceOrPsLimitService(VOS_VOID);

extern VOS_VOID  NAS_EMM_EmcPndReqSerAbnormalCommProc
(
    NAS_EMM_SUB_STATE_ENUM_UINT16       ucSs
);
extern VOS_VOID  NAS_EMM_MsSerInitSsWaitCnSerCnfProcMsgRrcRelInd( VOS_UINT32 ulCause);
extern VOS_VOID NAS_EMM_ExtSerReqRetranProc(VOS_UINT32 ulOpid);

extern VOS_VOID NAS_EMM_LocalDetachErrRecord(
        EMM_ERR_LOG_LOCAL_DETACH_TYPE_ENUM_UINT16       enLocalDetType);

extern VOS_VOID  NAS_EMM_SER_CServiceCountProc(VOS_VOID);
extern VOS_VOID    NAS_EMM_SER_RegAttempToUpdateMmRcvRrcCsPagingInd
(
    LRRC_LNAS_PAGING_UE_ID_ENUM_UINT32 enPagingUeId
);
extern VOS_UINT32 NAS_EMM_MsSerInitPreProcMmNormalCsfbNotifyMsg
(
    MM_LMM_CSFB_SERVICE_TYPE_ENUM_UINT32  enCsfbSrvTyp
);
extern VOS_UINT32  NAS_EMM_MsRegSsAttempToUpdateMmMsgMmCsfbSerStartNotify
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
);
extern VOS_UINT32 NAS_EMM_SER_VerifyCsfbFailNormalCsfbNotifyMsgProc(VOS_VOID);

extern VOS_VOID NAS_EMM_ProcHoRetransESRMsg(VOS_VOID);
extern VOS_VOID NAS_EMM_SndLrrcLmmCsfbNotify(LRRC_LNAS_CSFB_STATUS_ENUM_UINT16 enCsfbStatus);

extern VOS_VOID  NAS_EMM_SER_TbackoffProc(VOS_VOID);
extern VOS_UINT32  NAS_EMM_IsSerConditionSatisfied(VOS_VOID);

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

