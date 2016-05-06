

#ifndef __NASEMMSERINTERFACE_H__
#define __NASEMMSERINTERFACE_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include    "vos.h"

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

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
enum    NAS_EMM_SER_START_CAUSE_ENUM
{
    NAS_EMM_SER_START_CAUSE_NULL            = 0,

    NAS_EMM_SER_START_CAUSE_RRC_PAGING      = 1,
    NAS_EMM_SER_START_CAUSE_RABM_REEST      = 2,
    NAS_EMM_SER_START_CAUSE_ESM_DATA_REQ    = 3,
    NAS_ESM_SER_START_CAUSE_UPLINK_PENDING  = 4,
    NAS_EMM_SER_START_CAUSE_SMS_EST_REQ     = 5,
    NAS_EMM_SER_START_CAUSE_MO_CSFB_REQ     = 6,
    NAS_EMM_SER_START_CAUSE_MT_CSFB_REQ     = 7,
    NAS_EMM_SER_START_CAUSE_MO_EMERGENCY_CSFB_REQ = 8,
    NAS_EMM_SER_START_CAUSE_ESM_DATA_REQ_EMC= 9,
    NAS_EMM_SER_START_CAUSE_RABM_REEST_EMC  = 10,
    NAS_EMM_SER_START_CAUSE_LPP_EST_REQ     = 11,
    NAS_EMM_SER_START_CAUSE_SS_EST_REQ      = 12,
    NAS_EMM_SER_START_CAUSE_BUTT
};
typedef VOS_UINT8   NAS_EMM_SER_START_CAUSE_ENUM_UINT8;


enum    NAS_EMM_CSFB_RSP_ENUM
{
    NAS_EMM_CSFB_RSP_REJECTED_BY_UE     = 0,
    NAS_EMM_CSFB_RSP_ACCEPTED_BY_UE     = 1,

    NAS_EMM_CSFB_RSP_BUTT
};
typedef VOS_UINT8   NAS_EMM_CSFB_RSP_ENUM_UINT8;

enum    NAS_EMM_CSFB_ABORT_FLAG_ENUM
{
    NAS_EMM_CSFB_ABORT_FLAG_INVALID     = 0,
    NAS_EMM_CSFB_ABORT_FLAG_VALID       = 1,

    NAS_EMM_CSFB_ABORT_FLAG_VALID_BUTT
};
typedef VOS_UINT8  NAS_EMM_CSFB_ABORT_FLAG_ENUM_UINT8;

/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/

extern VOS_UINT32 NAS_EMM_MsSerInitSsWaitCnSerCnfMsgAuthFail(   VOS_UINT32  ulMsgId,
                                                                VOS_VOID   *pMsgStru);

extern VOS_UINT32  NAS_EMM_MsSerInitSsWaitCnSerCnfMsgAuthRej(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru);
extern VOS_UINT32 NAS_EMM_MsSerInitSsWaitCnSerCnfMsgRrcRelInd(   VOS_UINT32  ulMsgId,
                                                                                   VOS_VOID   *pMsgStru
                                                                                );

extern VOS_UINT32 NAS_EMM_MsSerInitSsWaitCnSerCnfMsgTimer3417Exp(  VOS_UINT32  ulMsgId,
                                                                                        VOS_VOID   *pMsgStru
                                                                                    );

extern VOS_UINT32 NAS_EMM_MsSerInitSsWaitCnSerCnfMsgTimer3417ExtExp
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
);

extern VOS_UINT32 NAS_EMM_MsSerInitSsWaitCNSerCnfMsgServiceReject(  VOS_UINT32  ulMsgId,
                                                                                        VOS_VOID   *pMsgStru
                                                                                        );
extern VOS_VOID NAS_EMM_MsSerInitSsWaitCnSerCnfProcMsgAuthRej(VOS_UINT32  ulCause);


extern VOS_UINT32 NAS_EMM_MsSerInitSsWaitCnSerCnfMsgIntraConnectFailInd(   VOS_UINT32  ulMsgId,
                                                         VOS_VOID   *pMsgStru);
extern VOS_UINT32 NAS_EMM_MsRegSsNormalMsgRabmReestReq(VOS_UINT32  ulMsgId,
                                                                            VOS_VOID   *pMsgStru
                                                                            );

extern VOS_UINT32 NAS_EMM_MsRegSsLimitedSrvMsgRabmReestReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
);
extern  VOS_UINT32  NAS_EMM_MsRegSsRegAttemptUpdateMmMsgRabmReestReq
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
);
extern VOS_UINT32  NAS_EMM_MsRegSsLimitedSrvMsgRabmRelReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
);
extern VOS_UINT32  NAS_EMM_MsRegSsNormalMsgRabmRelReq( VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru );

extern VOS_UINT32  NAS_EMM_MsRegSsRegAttemptUpdateMmMsgRabmRelReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
);
extern VOS_UINT32 NAS_EMM_MsRegSsNormalMsgEsmDataReq(VOS_UINT32  ulMsgId,
                                                                        VOS_VOID   *pMsgStru
                                                                        );
extern VOS_UINT32  NAS_EMM_MsRegSsNormalMsgSmsEstReq
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
);
extern VOS_UINT32  NAS_EMM_MsRegSsRegAttemptUpdateMmMsgEsmDataReq
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
);
extern VOS_UINT32 NAS_EMM_MsRegInitSsWaitCnAttachCnfMsgEsmDataReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
);

extern VOS_UINT32 NAS_EMM_MsTauInitMsgRabmReestReq(VOS_UINT32  ulMsgId,
                                                                    VOS_VOID   *pMsgStru
                                                                    );

extern VOS_UINT32 NAS_EMM_MsTauInitMsgRrcPagingInd(VOS_UINT32  ulMsgId,
                                                                    VOS_VOID   *pMsgStru
                                                                    );

extern VOS_UINT32 NAS_EMM_MsTauInitMsgEsmdataReq(VOS_UINT32  ulMsgId,
                                                                VOS_VOID   *pMsgStru
                                                                );
extern VOS_UINT32  NAS_EMM_MsTauInitMsgRabmRelReq(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
);

extern VOS_UINT32 NAS_EMM_MsSerInitMsgRabmDrbSetupInd(VOS_UINT32  ulMsgId,
                                                                        VOS_VOID   *pMsgStru
                                                                        );
extern VOS_UINT32  NAS_EMM_MsRegSsNormalMsgTcDataReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
);

extern VOS_UINT32  NAS_EMM_MsRegSsRegAttemptUpdateMmMsgTcDataReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
);

extern VOS_UINT32  NAS_EMM_MsRegInitSsWaitCnAttachCnfMsgTcDataReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
);
extern VOS_UINT32 NAS_EMM_MsSerInitMsgEsmdataReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
);

extern VOS_UINT32 NAS_EMM_EmmMsRegInitSsWaitRrcDataCnfMsgEsmDataReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
);



extern VOS_VOID  NAS_EMM_SER_Init( VOS_VOID );
extern VOS_VOID  NAS_EMM_SER_ClearResource( VOS_VOID );
extern NAS_EMM_SER_START_CAUSE_ENUM_UINT8  NAS_EMM_SER_GetSerStartCause(
                                        VOS_VOID);

extern VOS_UINT32 NAS_EMM_SER_IsCsfbProcedure( VOS_VOID );
extern VOS_UINT32 NAS_EMM_SER_IsMoCsfbProcedure(VOS_VOID);
extern VOS_VOID    NAS_EMM_SER_SendMrrcDataReq_ExtendedServiceReq(VOS_VOID);
extern VOS_UINT32  NAS_EMM_PreProcMsgMmCsfbSerStartNotify( MsgBlock * pMsg );
extern VOS_UINT32  NAS_EMM_PreProcMsgMmCsfbSerAbortNotify( MsgBlock * pMsg );
extern VOS_UINT32  NAS_EMM_MsRegSsNormalMsgMmCsfbSerStartNotify
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
);
extern VOS_UINT32  NAS_EMM_MsRegSsWaitAccessGrantIndMsgMmCsfbSerStartNotify
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
);

#if (FEATURE_LPP == FEATURE_ON)
extern VOS_UINT32  NAS_EMM_MsRegSsNormalMsgLppEstReq
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
);
extern VOS_UINT32  NAS_EMM_MsRegSsRegAttemptUpdateMmMsgLppEstReq
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
);
extern VOS_UINT32  NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgLppEstReq
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
);
extern VOS_UINT32  NAS_EMM_MsRegSsNormalMsgLcsEstReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
);
extern VOS_UINT32  NAS_EMM_MsRegSsRegAttemptUpdateMmMsgLcsEstReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
);
#endif


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

#endif /* end of NasEmmSERInterface.h */

