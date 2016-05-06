

#ifndef __NASEMMTAUINTERFACE_H__
#define __NASEMMTAUINTERFACE_H__


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include    "vos.h"
/*#include    "NasLmmPubMOm.h"*/

/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 Macro
*****************************************************************************/


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
enum    NAS_EMM_TAU_START_CAUSE_ENUM
{
    NAS_EMM_TAU_START_CAUSE_DEFAULT              = 0,
    NAS_EMM_TAU_START_CAUSE_T3412EXP                ,
    NAS_EMM_TAU_START_CAUSE_OTHERS                  ,
    NAS_EMM_TAU_START_CAUSE_ESM_EMC_PDN_REQ         ,
    NAS_EMM_TAU_START_CAUSE_VOICE_DOMAIN_CHANGE     ,
    NAS_EMM_TAU_START_CAUSE_BUTT
};
typedef VOS_UINT8   NAS_EMM_TAU_START_CAUSE_ENUM_UINT8;

enum NAS_EMM_T3412_EXP_ENUM
{
    NAS_EMM_T3412_EXP_NO                            = 0,    /* 没有超时 */
    NAS_EMM_T3412_EXP_YES_REG_NO_AVALABLE_CELL      = 1,    /* 在REG+N0_AVALABLE_CELL状态下超时 */
    NAS_EMM_T3412_EXP_YES_OTHER_STATE               = 2,    /* 在非REG+N0_AVALABLE_CELL状态下超时 */

    NAS_EMM_T3412_EXP_BUTT
};
typedef VOS_UINT32 NAS_EMM_T3412_EXP_ENUM_UINT32;

enum NAS_EMM_TRIGGER_TAU_RRC_REL_ENUM
{
    NAS_EMM_TRIGGER_TAU_RRC_REL_NO                  = 0,    /* RRC删除原因不能触发TAU*/
    NAS_EMM_TRIGGER_TAU_RRC_REL_LOAD_BALANCE        = 1,    /* 负载均衡 */
    NAS_EMM_TRIGGER_TAU_RRC_REL_CONN_FAILURE        = 2,    /* RRC Connection failure */

    NAS_EMM_TRIGGER_TAU_RRC_REL_BUTT
};

typedef VOS_UINT32 NAS_EMM_TRIGGER_TAU_RRC_REL_ENUM_UINT32;

enum NAS_EMM_COM_DET_BLO_FLAG_ENUM
{
    NAS_EMM_COM_DET_BLO_NO                          = 0,    /* TAU没有打断联合DETACH */
    NAS_EMM_COM_DET_BLO_YES                         = 1,    /* TAU打断了联合DETACH */

    NAS_EMM_COM_DET_BLO_BUTT
};
typedef VOS_UINT32 NAS_EMM_COM_DET_BLO_FLAG_ENUM_UINT32;
enum NAS_LMM_INTRA_TAU_TYPE_ENUM
{
    NAS_LMM_INTRA_TAU_TYPE_PARA_CHANGE              = 0,    /* 参数变更 */
    NAS_LMM_INTRA_TAU_TYPE_UPDATE_MM                = 1,    /* 重新回到REG+ATTEMPT_TO_UPDATE_MM状态，但3411和3402已停止，需要发起联合TAU */
    NAS_LMM_INTRA_TAU_TYPE_IMSI_ATTACH              = 2,

    NAS_LMM_INTRA_TAU_TYPE_BUTT
};
typedef VOS_UINT32 NAS_LMM_INTRA_TAU_TYPE_ENUM_UINT32;

enum NAS_EMM_IMSI_DETACH_FLAG_ENUM
{
    NAS_EMM_IMSI_DETACH_INVALID                     = 0,
    NAS_EMM_IMSI_DETACH_VALID                       = 1,
    NAS_EMM_IMSI_DETACH_BUTT
};
typedef VOS_UINT8 NAS_EMM_IMSI_DETACH_FLAG_ENUM_UINT8;

enum NAS_EMM_TAU_COMPLETE_FLAG_ENUM
{
    NAS_EMM_TAU_COMPLETE_INVALID                     = 0,
    NAS_EMM_TAU_COMPLETE_VALID                       = 1,
    NAS_EMM_TAU_COMPLETE_BUTT
};
typedef VOS_UINT8 NAS_EMM_TAU_COMPLETE_FLAG_ENUM_UINT8;
/*****************************************************************************
  5 STRUCT
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;                /* 消息 ID */
    APP_MM_MSG_TYPE_ENUM_UINT32         ulOmMsgType;            /*OM CMD TYPE*/

    NAS_LMM_INTRA_TAU_TYPE_ENUM_UINT32  enIntraTauType;         /* 内部TAU类型 */
}NAS_LMM_INTRA_TAU_REQ_STRU;


/* LMM给MMC上报TAU结果有参数的函数指针 */
typedef VOS_VOID (*NAS_LMM_SEND_TAU_RESULT_ACT_FUN)(const VOS_VOID*);





/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/


extern VOS_UINT32 NAS_EMM_MsTauInitSsWaitCNCnfMsgT3430Exp(VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru
                               );

extern VOS_UINT32 NAS_EMM_MsTauInitSsWaitCnCnfMsgAuthFail(VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru
                               );
extern VOS_UINT32 NAS_EMM_MsTauInitSsWaitCnCnfMsgAuthRej(
                                                  VOS_UINT32  ulMsgId,
                                                  VOS_VOID   *pMsgStru);
extern VOS_UINT32 NAS_EMM_MsTauInitSsWaitCnCnfMsgRrcRelInd(VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru
                               );
extern VOS_UINT32  NAS_EMM_MsTauInitSsWaitCnCnfMsgDrbSetupInd(
                                                  VOS_UINT32  ulMsgId,
                                                  VOS_VOID   *pMsgStru);
extern VOS_UINT32 NAS_EMM_MsTauInitSsWaitCNCnfMsgIntraConnectFailInd(VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru
                               );

extern VOS_UINT32 NAS_EMM_MsTauInitSsWaitCNCnfMsgTAUAcp(VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru
                               );

extern VOS_UINT32 NAS_EMM_MsTauInitSsWaitCNCnfMsgTAURej(VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru
                               );

extern VOS_VOID   NAS_EMM_MsTauInitSsWaitCnTauCnfProcMsgAuthRej(VOS_UINT32  ulCause);
extern VOS_UINT32 NAS_EMM_MsRegSsNormalMsgSysinfo(VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru
                               );

extern VOS_UINT32  NAS_EMM_MsRegSsRegAttemptUpdateMmMsgSysinfo
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
);
extern VOS_UINT32 NAS_EMM_MsRegSsNormalMsgT3411Exp(VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru
                               );
extern VOS_UINT32 NAS_EMM_MsRegSsRegAttemptUpdateMmMsgT3411Exp
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
);
extern VOS_UINT32 NAS_EMM_MsRegSsRegAttemptUpdateMmMsgT3402Exp
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
);
extern VOS_UINT32 NAS_EMM_MsRegSsNormalMsgT3412Exp(VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru
                               );
extern VOS_UINT32  NAS_EMM_MsRegSsRegAttemptUpdateMmMsgT3412Exp
(
    VOS_UINT32                              ulMsgId,
    VOS_VOID                               *pMsgStru
);
extern VOS_UINT32  NAS_EMM_MsSuspendSsAnyMsgT3412Exp(
                                                VOS_UINT32  ulMsgId,
                                                VOS_VOID   *pMsgStru  );
extern VOS_UINT32 NAS_EMM_MsRegSsAtpUpdataMsgSysinfo(VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru
                               );
extern VOS_UINT32 NAS_EMM_MsRegSsNmlSrvMsgAuthFail(
                                                    VOS_UINT32 ulMsgId,
                                                    VOS_VOID *pMsgStru);
extern VOS_UINT32  NAS_EMM_MsRegSsLimitedSrvMsgAuthFail
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
);
extern VOS_UINT32  NAS_EMM_MsRegSsRegAttemptUpdateMmMsgAuthFail
(
    VOS_UINT32 ulMsgId,
    VOS_VOID *pMsgStru
);
extern VOS_UINT32 NAS_EMM_MsRegSsNmlSrvMsgRrcRelInd(
                                                    VOS_UINT32 ulMsgId,
                                                    VOS_VOID *pMsgStru);

extern VOS_UINT32  NAS_EMM_MsRegSsRegAttemptUpdateMmMsgRrcRelInd
(
    VOS_UINT32 ulMsgId,
    VOS_VOID *pMsgStru
);
extern VOS_UINT32 NAS_EMM_MsRegSsAtpUpdataMsgT3411Exp(VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru
                               );

extern VOS_UINT32 NAS_EMM_MsRegSsAtpUpdataMsgT3402Exp(VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru
                               );
extern VOS_UINT32 NAS_EMM_MsRegSsAtpUpdataMsgT3346Exp
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
);
extern VOS_UINT32 NAS_EMM_MsRegSsSomeStateMsgEsmDataReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
);
extern VOS_UINT32  NAS_EMM_MsRegSsLimitSRMsgSysinfo(VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru
                               );

extern VOS_UINT32  NAS_EMM_MsRegSsPLMNSearchMsgSysinfo(VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru
                               );


extern VOS_UINT32  NAS_EMM_MsRegSsWaitAccessGrantIndMsgRrcGrantInd(VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru
                               );
extern VOS_UINT32  NAS_EMM_MsRegSsWaitAccessGrantIndMsgSysinfoInd( VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru );
extern VOS_UINT32  NAS_EMM_MsRegSsWaitAccessGrantIndMsgIntraTauReq( VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru );
extern VOS_UINT32  NAS_EMM_MsRegSsWaitAccessGrantIndMsgBearerStatusReq(
                                                    VOS_UINT32  ulMsgId,
                                                    VOS_VOID   *pMsgStru );
extern VOS_UINT32  NAS_EMM_MsRegSsWaitAccessGrantIndMsgT3412Exp(  VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru);
extern VOS_UINT32  NAS_EMM_MsRegSsWaitAccessGrantIndMsgT3411Exp( VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru );
extern VOS_UINT32 NAS_EMM_MsRegSsNocellMsgSysinfo(VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru
                               );

extern VOS_UINT32 NAS_EMM_MsDeRegInitSsWaitCNDetachCnfMsgSysinfo(VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru
                               );
extern VOS_UINT32 NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgSysinfo
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
);

extern VOS_UINT32 NAS_EMM_MsTauInitSsWaitCNCnfMsgSysinfo(VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru
                               );

extern VOS_UINT32 NAS_EMM_MsSerInitSsWaitCNCnfMsgSysinfo(VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru
                               );

extern VOS_UINT32 NAS_EMM_MsRegSsNormalServiceMsgIntraTauReq(VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru);
extern VOS_UINT32  NAS_EMM_MsRegSsNormalMsgBearerStatusReq( VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru );

extern VOS_UINT32  NAS_EMM_MsRegSsRegAttemptUpdateMmMsgBearerStatusReq
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
);
extern VOS_UINT32  NAS_EMM_MsTauInitSsWaitCnCnfMsgBearerStatusReq(
                                                    VOS_UINT32  ulMsgId,
                                                    VOS_VOID   *pMsgStru );

extern VOS_UINT32  NAS_EMM_MsRegSsAnyStatusMsgT3412Exp( VOS_UINT32  ulMsgId,
                                                    VOS_VOID   *pMsgStru );

extern VOS_UINT32  NAS_EMM_MsRegSsNoVailableCellMsgT3412Exp
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                     *pMsgStru
);
extern VOS_UINT32  NAS_EMM_MsRegSsSomeStatusMsgIntraTauReq( VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru );
extern VOS_UINT32  NAS_EMM_MsRegSsSomeStateMsgBearerStatusReq( VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru );

extern VOS_VOID    NAS_EMM_TAU_MsRegMsgRelInd( LRRC_LNAS_REL_CAUSE_ENUM_UINT32   enRelCause );

extern VOS_VOID  NAS_EMM_TAU_CollisionServiceProc
(
    NAS_LMM_SEND_TAU_RESULT_ACT_FUN     pfTauRslt,
    const VOS_VOID                     *pvPara,
    VOS_UINT8                           ucRatChange
);
extern VOS_VOID  NAS_EMM_TAU_CollisionDetachProc( VOS_VOID );

extern VOS_VOID  NAS_EMM_TAU_Init(VOS_VOID );
extern VOS_VOID  NAS_EMM_TAU_ClearResouce( VOS_VOID );
extern VOS_VOID  NAS_EMM_FreeTauDyn( VOS_VOID );
extern NAS_EMM_TAU_START_CAUSE_ENUM_UINT8  NAS_EMM_TAU_GetTauStartCause(VOS_VOID);

extern VOS_VOID  NAS_EMM_ClearBarResouce(VOS_VOID);

extern VOS_VOID  NAS_EMM_MmcSendTauActionResultIndOthertype
(
    const VOS_VOID  *pvTauRslt
);
extern VOS_VOID  NAS_EMM_MsRegSsNmlSrvProcMsgRrcRelInd( VOS_UINT32 ulCause );
extern VOS_VOID  NAS_EMM_MsRegSsRegAttemptUpdateMmProcMsgRrcRelInd
(
    VOS_UINT32                          ulCause
);

extern VOS_VOID   NAS_EMM_TAU_IsUplinkPending( VOS_VOID );
extern VOS_VOID    NAS_EMM_RegBarCommProc( VOS_VOID );
extern VOS_UINT32  NAS_LMM_PreProcIntraTauReq
(
    MsgBlock                           *pMsg
);
/*extern VOS_VOID    NAS_EMM_TAU_TimerRunningStateChng( NAS_LMM_STATE_TI_ENUM_UINT16 enStateTimerId );*/
extern VOS_VOID  NAS_EMM_TAU_SuspendInitClearResouce( VOS_VOID );
extern VOS_UINT32 NAS_EMM_TAU_CanTriggerComTauWithIMSI(VOS_VOID);
extern NAS_EMM_IMSI_DETACH_FLAG_ENUM_UINT8  NAS_EMM_TAU_GetImsiDetachFlag( VOS_VOID );
extern VOS_VOID NAS_EMM_TAU_SetImsiDetachFlag
(
    NAS_EMM_IMSI_DETACH_FLAG_ENUM_UINT8 enImsiDetachFlag
);
extern VOS_VOID  NAS_EMM_EmcPndReqTauAbnormalCommProc
(
    NAS_LMM_SEND_TAU_RESULT_ACT_FUN     pfTauRslt,
    const VOS_VOID                     *pvPara,
    NAS_EMM_SUB_STATE_ENUM_UINT16       ucSs
);


extern VOS_VOID NAS_EMM_ProcHoWaitSysInfoBufferMsg( VOS_VOID );
extern VOS_VOID NAS_EMM_ExtSerReqRetranProc(VOS_UINT32 ulOpid);
extern VOS_VOID NAS_EMM_ProcNoRfWaitSysInfoBufferMsg( VOS_VOID );

VOS_VOID NAS_EMM_ProcConnRelWaitSysInfoBufferMsg( VOS_VOID );




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

#endif /* end of NasEmmTAUInterface.h */
