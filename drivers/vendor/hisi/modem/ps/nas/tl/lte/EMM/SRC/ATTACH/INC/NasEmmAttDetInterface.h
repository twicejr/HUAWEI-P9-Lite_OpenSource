/******************************************************************************

@(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
File name   : NasEmmAttDetInterface.h
Description :
History     :
******************************************************************************/

#ifndef _NASEMMATTDETINTERFACE_H
#define _NASEMMATTDETINTERFACE_H


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include    "vos.h"
#include    "NasEmmcEmmInterface.h"
#include    "LNasStkInterface.h"

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

#define NAS_EMM_GLO_SetDetTypeMo(ulDetType) (g_stEmmDetCtrl.ulDetachTypeMo = ulDetType)
#define NAS_EMM_GLO_SetAttReqType(ulReqType) (g_stEmmAttCtrl.ulAttReqType = ulReqType)
#define NAS_EMM_GLO_SetCnAttReqType(ulReqType) (g_stEmmAttCtrl.ulAttCnType = ulReqType)
#define NAS_EMM_GLO_GetAttReqType()             (g_stEmmAttCtrl.ulAttReqType)
#define NAS_EMM_GLO_GetCnAttReqType()           (g_stEmmAttCtrl.ulAttCnType)
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/


/*****************************************************************************
  5 STRUCT
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;                /* 消息 ID */
    VOS_UINT8                           aucMsgData[4];          /* 整条消息存储 */
}NAS_LMM_INTRA_ATTACH_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;                /* 消息 ID */
    VOS_UINT8                           aucMsgData[4];          /* 整条消息存储 */
}NAS_LMM_INTRA_DETACH_REQ_STRU;



/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_VOID    NAS_EMM_MrrcSendDetAcpMt(VOS_VOID);

/*extern VOS_VOID    NAS_EMM_ProcReAttachReq(VOS_VOID);*/

extern VOS_VOID    NAS_EMM_DetCnDetReqNotReattach(
                               const NAS_EMM_CN_DETACH_REQ_MT_STRU       *pRcvEmmMsg);

extern  VOS_UINT32  NAS_EMM_MsDrgSsNmlSrvMsgAppAttachReq( VOS_UINT32  ulMsgId,
                                                VOS_VOID   *pMsgStru);

extern  VOS_UINT32  NAS_EMM_MsDrgSsPlmnSrcMsgAppAttachReq(VOS_UINT32  ulMsgId,
                                                VOS_VOID   *pMsgStru);
extern  VOS_UINT32  NAS_EMM_MsDrgSsAttemptToAttMsgAppAttachReq(VOS_UINT32  ulMsgId,
                                                VOS_VOID   *pMsgStru);
extern  VOS_UINT32  NAS_EMM_MsDrgSsLimitedSrvMsgAppAttachReq(VOS_UINT32  ulMsgId,
                                                     VOS_VOID   *pMsgStru);
extern  VOS_UINT32  NAS_EMM_MsDrgSsNoImsiMsgAppAttachReq(VOS_UINT32  ulMsgId,
                                                 VOS_VOID   *pMsgStru );
extern  VOS_UINT32  NAS_EMM_MsDrgSsNoCellAvailMsgAppAttachReq(VOS_UINT32  ulMsgId,
                                                      VOS_VOID   *pMsgStru );
extern  VOS_UINT32  NAS_EMM_MsDrgSsAttNeedMsgAppAttachReq(VOS_UINT32  ulMsgId,
                                                  VOS_VOID   *pMsgStru );
extern  VOS_UINT32  NAS_EMM_MsRegInitSsWtEsmPdnRspMsgAppAttachReq(VOS_UINT32  ulMsgId,
                                                         VOS_VOID   *pMsgStru);
extern  VOS_UINT32  NAS_EMM_MsRegInitSsWtCnAttCnfMsgAppAttachReq(VOS_UINT32  ulMsgId,
                                                         VOS_VOID   *pMsgStru  );
extern  VOS_UINT32  NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgAppAttachReq(VOS_UINT32  ulMsgId,
                                                            VOS_VOID   *pMsgStru  );
extern VOS_UINT32    NAS_EMM_MsRegInitSsWaitRrcDataCnfMsgAppAttachReq(VOS_UINT32  ulMsgId,
                                                            VOS_VOID   *pMsgStru  );
extern  VOS_UINT32  NAS_EMM_MsRegSsNmlSrvMsgAppAttachReq(VOS_UINT32  ulMsgId,
                                                 VOS_VOID   *pMsgStru  );
extern  VOS_UINT32  NAS_EMM_MsRegSsRegAttemptUpdateMmMsgAppAttachReq
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
);
extern  VOS_UINT32  NAS_EMM_MsRegSsAtmpToUpdMsgAppAttachReq(VOS_UINT32  ulMsgId,
                                                    VOS_VOID   *pMsgStru  );
extern  VOS_UINT32  NAS_EMM_MsRegSsLimitedSrvMsgAppAttachReq(VOS_UINT32  ulMsgId,
                                                    VOS_VOID   *pMsgStru  );
extern  VOS_UINT32  NAS_EMM_MsRegSsPlmnSrcMsgAppAttachReq( VOS_UINT32  ulMsgId,
                                                    VOS_VOID   *pMsgStru  );
extern  VOS_UINT32  NAS_EMM_MsRegSsWaitAccessGrantIndMsgAppAttachReq( VOS_UINT32  ulMsgId,
                                                    VOS_VOID   *pMsgStru  );
extern  VOS_UINT32  NAS_EMM_MsRegSsNoCellAvailMsgAppAttachReq( VOS_UINT32  ulMsgId,
                                                    VOS_VOID   *pMsgStru  );
extern VOS_UINT32    NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgAppAttachReq( VOS_UINT32  ulMsgId,
                                                    VOS_VOID   *pMsgStru  );

extern  VOS_UINT32  NAS_EMM_MsDrgInitSsWtCnDetCnfMsgAppAttachReq( VOS_UINT32  ulMsgId,
                                                    VOS_VOID   *pMsgStru  );
extern  VOS_UINT32  NAS_EMM_MsTauInitSsWtCnTauCnfMsgAppAttachReq(VOS_UINT32  ulMsgId,
                                                    VOS_VOID   *pMsgStru );
extern  VOS_UINT32  NAS_EMM_MsSerInitSsWtCnSerCnfMsgAppAttachReq( VOS_UINT32  ulMsgId,
                                                         VOS_VOID   *pMsgStru );
/*extern VOS_VOID    NAS_EMM_AD_BufplmnListFromCnMsg(
                                const NAS_EMM_CN_ATTACH_ACP_STRU         *pRcvEmmMsg);

*/
extern  VOS_UINT32  NAS_EMM_MsRegInitSsWtCnAttCnfMsgCnAttachAcp
                                               (VOS_UINT32  ulMsgId,
                                                VOS_VOID   *pMsgStru);
extern  VOS_UINT32  NAS_EMM_MsRegInitSsWtCnAttCnfMsgCnAttachReject(
                                                VOS_UINT32  ulMsgId,
                                                VOS_VOID   *pMsgStru ) ;



extern  VOS_UINT32  NAS_EMM_MsRegInitSsWtEsmPdnRspMsgEsmPdnRsp(VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru);
extern  VOS_UINT32  NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgEsmBearerCnf(
                                                           VOS_UINT32  ulMsgId,
                                                           VOS_VOID   *pMsgStru);
extern  VOS_UINT32  NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgEsmDataReq(VOS_UINT32  ulMsgId,
                                                         VOS_VOID   *pMsgStru);
extern  VOS_UINT32  NAS_EMM_MsDrgSsNmlSrvMsgEsmEstReq(
                                           VOS_UINT32  ulMsgId,
                                           VOS_VOID   *pMsgStru) ;





extern  VOS_UINT32    NAS_EMM_MsRegSsNmlSrvMsgCnDetachReq(VOS_UINT32  ulMsgId,
                                                VOS_VOID   *pMsgStru );
extern  VOS_UINT32  NAS_EMM_MsRegSsLimitedSrvMsgCnDetachReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
);
extern  VOS_UINT32  NAS_EMM_MsRegSsRegAttemptUpdateMmMsgCnDetachReq
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
);
extern VOS_UINT32  NAS_EMM_MsRegSsRegAttemptUpdateMmMsgIntraDetReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
);
extern  VOS_UINT32    NAS_EMM_MsDrgInitSsWtCnDetCnfMsgCnDetachReq(VOS_UINT32  ulMsgId,
                                                        VOS_VOID   *pMsgStru);
extern  VOS_UINT32  NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgCnDetachReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
);

extern  VOS_UINT32    NAS_EMM_MsRegInitMsgCnDetachReq(
                                                VOS_UINT32  ulMsgId,
                                                VOS_VOID   *pMsgStru );
/* leixiantiao 00258641 重构函数降低圈复杂度 2014-7-30 begin */
extern VOS_VOID NAS_EMM_MsTauInitSsWtCnTauCnfMsgCnDetReqCollisionDetProc(const VOS_UINT32 *pvTauRslt);
/* leixiantiao 00258641 重构函数降低圈复杂度 2014-7-30 end */

extern  VOS_UINT32    NAS_EMM_MsTauInitSsWtCnTauCnfMsgCnDetatchReq(VOS_UINT32  ulMsgId,
                                                         VOS_VOID   *pMsgStru);
extern  VOS_UINT32    NAS_EMM_MsSerInitSsWtCnSerCnfMsgCnDetatchReq(VOS_UINT32  ulMsgId,
                                                         VOS_VOID   *pMsgStru);
extern VOS_VOID NAS_EMM_MsRrcConnRelInitSsWaitRrcRelMsgImsiDetachReq
(
    const NAS_EMM_CN_DETACH_REQ_MT_STRU *pstRcvEmmMsg
);
extern  VOS_UINT32    NAS_EMM_MsDrgInitSsWtCnDetCnfMsgCnDetachAcp( VOS_UINT32  ulMsgId,
                                                         VOS_VOID   *pMsgStru);
extern VOS_VOID  NAS_EMM_StartEmergencyAttach( VOS_VOID );
extern VOS_UINT32  NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgCnDetachAcp
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
);
extern VOS_UINT32  NAS_EMM_MsDrgSsLimitedSrvMsgEsmEstReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
);
extern VOS_UINT32  NAS_EMM_MsDrgSsNoImsiMsgEsmEstReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
);
extern VOS_UINT32  NAS_EMM_MsDrgSsAttachNeededMsgEsmEstReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
);
extern VOS_UINT32  NAS_EMM_MsRegSsLimitedSrvMsgEsmDataReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
);
extern VOS_UINT32  NAS_EMM_MsRegInitMsgEsmEstReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
);
extern VOS_UINT32  NAS_EMM_MsDrgSsPlmnSrcMsgMsgEsmEstReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
);
extern VOS_UINT32  NAS_EMM_MsDrgSsNoCellAvailMsgMsgEsmEstReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
);
extern VOS_UINT32  NAS_EMM_MsRegSsNormalMsgMsgEsmEstReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
);
extern VOS_UINT32  NAS_EMM_MsRegSsRegAttemptUpdateMmMsgEsmEstReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
);
extern VOS_UINT32  NAS_EMM_MsDrgSsAttemptToAttMsgEsmEstReq
(
    VOS_UINT32                              ulMsgId,
    VOS_VOID                               *pMsgStru
);
extern  VOS_VOID  NAS_EMM_ProcDetachAuthRej(VOS_UINT32  ulCause);

extern  VOS_UINT32  NAS_EMM_MsDrgInitSsWtCnDetCnfMsgCnCommMsg(VOS_UINT32  ulMsgId,
                                                      VOS_VOID   *pMsgStru );


extern  VOS_UINT32  NAS_EMM_MsDrgInitSsWtCnDetCnfMsgAuthFail(
                                                VOS_UINT32  ulMsgId,
                                                VOS_VOID   *pMsgStru);
extern VOS_UINT32 NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgEsmDataReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
);

extern VOS_UINT32 NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgTcDataReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
);

extern VOS_UINT32 NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgRabmRelReq
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
);
/*extern VOS_UINT32  NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgAuthFail
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                     *pMsgStru
);*/
extern VOS_UINT32  NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgAuthRej
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                            *pMsgStru
);

extern VOS_VOID    NAS_EMM_SendRejEventToSTK
(   VOS_UINT8 ucCauseCode,
    LNAS_STK_UPDATE_TYPE_ENUM_UINT8          enUpdateType
);

extern VOS_UINT32  NAS_EMM_MsDrgInitSsWtCnDetCnfMsgAuthRej(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru);
extern VOS_UINT32   NAS_EMM_MsDrgInitSsWtCnDetCnfMsgRrcRelInd(
                                                VOS_UINT32  ulMsgId,
                                                VOS_VOID   *pMsgStru);
extern VOS_UINT32  NAS_EMM_MsDrgInitSsWtCnDetCnfMsgIntraConnectFailInd(
                                                VOS_UINT32  ulMsgId,
                                                VOS_VOID   *pMsgStru);
extern VOS_UINT32 NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgIntraConnectFailInd
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
);
extern VOS_UINT32  NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgT3421Exp
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
);

extern  VOS_UINT32  NAS_EMM_MsDrgInitSsWtCnDetCnfMsgT3421Exp( VOS_UINT32  ulMsgId,
                                                      VOS_VOID   *pMsgStru );
extern  VOS_UINT32  NAS_EMM_MsDrgInitSsWtSwitchoffMsgRrcRelInd( VOS_UINT32  ulMsgId,
                                                      VOS_VOID   *pMsgStru );
extern  VOS_UINT32  NAS_EMM_MsRegSsRegNmlSrvMsgIntraDetReq(VOS_UINT32  ulMsgId,
                                                   VOS_VOID   *pMsgStru);
extern  VOS_UINT32    NAS_EMM_MsDrgSsPlmnSrcMsgAppDetachReq(VOS_UINT32  ulMsgId,
                                                 VOS_VOID   *pMsgStru);
extern  VOS_UINT32  NAS_EMM_MsDrgSsAttemptToAttMsgAppDetachReq(VOS_UINT32  ulMsgId,
                                                VOS_VOID   *pMsgStru);
extern  VOS_UINT32  NAS_EMM_MsDrgSsLimitedSrvMsgAppDetachReq(VOS_UINT32  ulMsgId,
                                                     VOS_VOID   *pMsgStru);
extern  VOS_UINT32  NAS_EMM_MsDrgSsNoCellAvailMsgAppDetachReq(VOS_UINT32  ulMsgId,
                                                      VOS_VOID   *pMsgStru );
extern  VOS_UINT32  NAS_EMM_MsDrgSsAttNeedMsgAppDetachReq(VOS_UINT32  ulMsgId,
                                                  VOS_VOID   *pMsgStru );
extern  VOS_UINT32  NAS_EMM_MsRegInitSsWtEsmPdnRspMsgAppDetachReq(VOS_UINT32  ulMsgId,
                                                         VOS_VOID   *pMsgStru);
extern  VOS_UINT32  NAS_EMM_MsRegInitSsWtCnAttCnfMsgAppDetachReq(VOS_UINT32  ulMsgId,
                                                         VOS_VOID   *pMsgStru  );
extern  VOS_UINT32  NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgAppDetachReq(VOS_UINT32  ulMsgId,
                                                            VOS_VOID   *pMsgStru  );
extern  VOS_UINT32  NAS_EMM_MsRegSsNmlSrvMsgAppDetachReq(VOS_UINT32  ulMsgId,
                                                 VOS_VOID   *pMsgStru  );
extern  VOS_UINT32  NAS_EMM_MsRegSsRegAttemptUpdateMmMsgAppDetachReq
(
    VOS_UINT32  ulMsgId,
    VOS_VOID   *pMsgStru
);
extern  VOS_UINT32  NAS_EMM_MsRegSsAtmpToUpdMsgAppDetachReq(VOS_UINT32  ulMsgId,
                                                    VOS_VOID   *pMsgStru  );
extern  VOS_UINT32  NAS_EMM_MsTauInitSsWtCnTauCnfMsgAppDetachReq(VOS_UINT32  ulMsgId,
                                                    VOS_VOID   *pMsgStru );
extern  VOS_UINT32  NAS_EMM_MsSerInitSsWtCnSerCnfMsgAppDetachReq( VOS_UINT32  ulMsgId,
                                                         VOS_VOID   *pMsgStru );
extern VOS_UINT32   NAS_EMM_MsRegInitSsWtCnAttCnfMsgIntraConncetFailInd(
                                                    VOS_UINT32  ulMsgId,
                                                    VOS_VOID   *pMsgStru );
extern  VOS_UINT32    NAS_EMM_MsRegInitSsWtCnAttCnfMsgAuthFail(
                                                    VOS_UINT32  ulMsgId,
                                                    VOS_VOID   *pMsgStru);
extern VOS_UINT32  NAS_EMM_MsRegInitSsWtCnAttCnfMsgAuthRej(
                                                    VOS_UINT32  ulMsgId,
                                                    VOS_VOID   *pMsgStru );
extern VOS_UINT32     NAS_EMM_MsRegInitSsWtCnAttCnfMsgRrcRelInd(
                                                    VOS_UINT32  ulMsgId,
                                                    VOS_VOID   *pMsgStru);
extern VOS_UINT32  NAS_EMM_MsRegInitSsWtEsmPdnRspMsgRrcRelInd(
                                                    VOS_UINT32  ulMsgId,
                                                    VOS_VOID   *pMsgStru );
extern  VOS_UINT32    NAS_EMM_MsRegInitSsWtCnAttCnfMsgT3410Exp(
                                                    VOS_UINT32  ulMsgId,
                                                    VOS_VOID   *pMsgStru);
extern  VOS_UINT32    NAS_EMM_MsDrgSsAttemptToAttMsgT3411Exp(
                                                    VOS_UINT32  ulMsgId,
                                                    VOS_VOID   *pMsgStru);
extern  VOS_UINT32  NAS_EMM_MsDrgSsAttemptToAttMsgT3402Exp( VOS_UINT32  ulMsgId,
                                                    VOS_VOID   *pMsgStru  );
extern  VOS_UINT32  NAS_EMM_MsDeregSsAttachNeededMsgRrcAccessGrantInd(VOS_UINT32  ulMsgId,
                                                    VOS_VOID   *pMsgStru );
extern VOS_UINT32   NAS_EMM_MsDeregSsAttachNeededMsgMmcSysInfoInd( VOS_UINT32  ulMsgId,
                                                    VOS_VOID   *pMsgStru );

extern  VOS_UINT32  NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgSysInfo(
                                                    VOS_UINT32  ulMsgId,
                                                    VOS_VOID   *pMsgStru);
extern  VOS_UINT32  NAS_EMM_MsRegInitSsWtCnAttCnfMsgSysInfo(
                                                    VOS_UINT32  ulMsgId,
                                                    VOS_VOID   *pMsgStru);
extern  VOS_UINT32  NAS_EMM_MsDrgSsNmlSrvMsgIntraAttReq(
                                                    VOS_UINT32  ulMsgId,
                                                    VOS_VOID   *pMsgStru);
extern VOS_UINT32   NAS_EMM_MsRegSsNmlSrvMsgAuthRej(
                                                    VOS_UINT32 ulMsgId,
                                                    VOS_VOID *pMsgStru);
extern VOS_UINT32  NAS_EMM_MsRegSsLimitedSrvMsgAuthRej
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                     *pMsgStru
);
extern VOS_UINT32   NAS_EMM_MsRegSsRegAttemptUpdateMmMsgAuthRej
(
    VOS_UINT32 ulMsgId,
    VOS_VOID *pMsgStru
);
extern  VOS_VOID    NAS_EMM_MsRegSsNmlSrvProcMsgAuthRej( VOS_UINT32  ulCause);

extern  VOS_UINT32  NAS_EMM_MsRegInitSsWtEsmPdnRspMsgTimerWtEsmRspExp(
                                                            VOS_UINT32 ulMsgId,
                                                            VOS_VOID * pMsgStru);

extern  VOS_UINT32  NAS_EMM_MsRegInitSsWtEsmBearerCnfMsgTimerWtEsmBearerCnfExp(
                                                            VOS_UINT32 ulMsgId,
                                                            VOS_VOID * pMsgStru);

extern  VOS_VOID    NAS_EMM_EncodeUeNetCapa(    VOS_UINT8                  *pMsg,
                                                NAS_LMM_IE_FORMAT_ENUM_UINT8 ucIeFormat,
                                                VOS_UINT32                 *pulIeLength);

extern VOS_VOID  NAS_EMM_CompMappedGuti
(
    VOS_UINT8   *pMsg,
    VOS_UINT32  *pulIeLength
);
extern  VOS_VOID  NAS_EMM_CompNativeGuti
(
    VOS_UINT8   *pMsg,
    VOS_UINT32  *pulIeLength
);

extern VOS_VOID  NAS_EMM_CompImsi
(
    VOS_UINT8   *pMsg,
    VOS_UINT32  *pulIeLength
);
extern VOS_VOID  NAS_EMM_CompImei
(
    VOS_UINT8                          *pMsg,
    VOS_UINT32                         *pulIeLength
);
extern  VOS_VOID    NAS_EMM_EncodeAdditionalGuti
(
    VOS_UINT8   *pMsg,
    VOS_UINT32  *pulIeLength
);

extern VOS_VOID  NAS_EMM_EncodeLRVTai
(
    VOS_UINT8 *pMsg,
    VOS_UINT32 *pulIeLength
);

extern VOS_VOID  NAS_EMM_EncodeDrxPara
(
    VOS_UINT8 *pMsg,
    VOS_UINT32 *pulIeLength,
    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8      enCnMsgType
);

extern  VOS_VOID    NAS_EMM_EncodePtmsiSignature
(
    VOS_UINT8 *pMsg,
    VOS_UINT32 *pulIeLength
);

VOS_VOID  NAS_EMM_EncodeMsNetworkCapability
(
    VOS_UINT8 *pMsg,
    VOS_UINT32 *pulIeLength,
    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8      enCnMsgType
);

extern  VOS_VOID    NAS_EMM_EncodeLai
(
    VOS_UINT8 *pMsg,
    VOS_UINT32                         *pulIeLength,
    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8      enCnMsgType
);
extern  VOS_VOID    NAS_EMM_EncodeTmsiStatus
(
    VOS_UINT8 *pMsg,
    VOS_UINT32                         *pulIeLength,
    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8      enCnMsgType
);

extern VOS_VOID  NAS_EMM_EncodeMsClassMark2
(
    VOS_UINT8 *pMsg,
    VOS_UINT32                         *pulIeLength,
    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8      enCnMsgType
);

extern VOS_VOID  NAS_EMM_EncodeMsClassMark3
(
    VOS_UINT8 *pMsg,
    VOS_UINT32 *pulIeLength
);

extern VOS_VOID  NAS_EMM_EncodeSupportedCodecs
(
    VOS_UINT8 *pMsg,
    VOS_UINT32 *pulIeLength
);
extern VOS_VOID  NAS_EMM_EncodeAdditionUpdateType
(
    VOS_UINT8 *pMsg,
    VOS_UINT32 *pulIeLength
);

extern VOS_VOID  NAS_EMM_EncodeVoiceDomainAndUsageSetting
(
    VOS_UINT8 *pMsg,
    VOS_UINT32 *pulIeLength
);
extern VOS_VOID  NAS_EMM_EncodeGutiType
(
    VOS_UINT8 *pMsg,
    VOS_UINT32      *pulIeLength
);
extern  VOS_VOID    NAS_EMM_AppSendDetIndMt
(
    const NAS_EMM_CN_DETACH_REQ_MT_STRU   *pRcvEmmMsg
);
extern VOS_VOID  NAS_EMM_MmcSendDetIndLocal
(
    MMC_LMM_L_LOCAL_DETACH_TYPE_ENUM_UINT32 ulLocDetType
);

extern  VOS_VOID    NAS_EMM_EsmSendDataInd(const NAS_EMM_CN_MSGCON_STRU *pstEsmBearerReq);
extern  VOS_VOID    NAS_EMM_SendDetachForPowerOffReq(VOS_VOID);
extern  VOS_VOID    NAS_EMM_DetProcEnterForbTA(VOS_VOID);
extern  VOS_VOID    NAS_EMM_ImsiDetProcEnterForbTA( VOS_VOID );
extern  VOS_UINT32  NAS_EMM_MsRegSsAnyMsgAppStopReq(
                    VOS_UINT32                              ulMsgId,
                    VOS_VOID                                *pMsg );

extern  VOS_UINT32  NAS_EMM_MsAnyStateSsAnySateEsmBearStatusReq( VOS_VOID *pstMsg );
/*extern  VOS_VOID    NAS_EMM_InitAttachWhenAttempToAttach( VOS_VOID );*/
/*extern  VOS_UINT32  NAS_EMM_AttGetAttachAttempCounterNum(VOS_VOID);*/
extern  VOS_VOID    NAS_EMM_AttResetAttAttempCounter(VOS_VOID);
extern  VOS_VOID    NAS_EMM_AppSendDetCnf
(
    MMC_LMM_DETACH_RSLT_ENUM_UINT32 ulAppRslt
);
extern  VOS_UINT32  NAS_EMM_EmmMsRegInitSsWaitEsmBearerCnfMsgRrcRelInd(
                                                  VOS_UINT32  ulMsgId,
                                                  VOS_VOID   *pMsgStru);
extern  VOS_UINT32  NAS_EMM_CountMrrcDataReqLen(VOS_UINT32 ulNasCnMsgLen);
extern  VOS_VOID    NAS_EMM_AD_Reattach(VOS_VOID );
extern VOS_UINT32 NAS_EMM_Attach_IsTimerRunning(VOS_VOID );

extern  VOS_UINT32  NAS_EMM_EmmMsRegInitSsWaitRrcDataCnfMsgTmrRrcDataCnfExp(
                                                  VOS_UINT32  ulMsgId,
                                                  VOS_VOID   *pMsgStru  );

extern  VOS_UINT32  NAS_EMM_EmmMsRegInitSsWaitRrcDataCnfMsgRrcRelInd(
                                                  VOS_UINT32  ulMsgId,
                                                  VOS_VOID   *pMsgStru  );

extern  VOS_UINT32  NAS_EMM_EmmMsRegInitSsWaitRrcDataCnfMsgSysInfo(
                                                    VOS_UINT32      ulMsgId,
                                                    VOS_VOID        *pMsgStru  );

extern  VOS_UINT32  NAS_EMM_EmmMsRegInitSsWaitRrcDataCnfMsgAppDetachReq(
                                                 VOS_UINT32  ulMsgId,
                                                 VOS_VOID   *pMsgStru );
extern  VOS_UINT32  NAS_EMM_MsRegSsWaitAccessGrantIndMsgAppDetachReq(VOS_UINT32  ulMsgId,
                                                 VOS_VOID   *pMsgStru);
extern  VOS_UINT32  NAS_EMM_MsRrcConnRelInitSsWaitRrcRelMsgAppDetachReq(VOS_UINT32  ulMsgId,
                                                 VOS_VOID   *pMsgStru);
extern  VOS_UINT32  NAS_EMM_MsRegSsLimitedSrvMsgAppDetachReq( VOS_UINT32  ulMsgId,
                                                 VOS_VOID   *pMsgStru );
extern  VOS_UINT32  NAS_EMM_MsRegSsLimitedSrvMsgIntraDetReq
(
    VOS_UINT32                         ulMsgId,
    VOS_VOID                          *pMsgStru
);
extern  VOS_UINT32  NAS_EMM_MsRegSsNoCellAvailMsgAppDetachReq( VOS_UINT32  ulMsgId,
                                                 VOS_VOID   *pMsgStru);
extern  VOS_UINT32  NAS_EMM_MsRegSsPlmnSrcMsgAppDetachReq(VOS_UINT32  ulMsgId,
                                                 VOS_VOID   *pMsgStru );
extern  VOS_UINT32  NAS_EMM_SendIntraAttachReq(VOS_VOID);
/*extern  VOS_VOID  NAS_EMM_SendAppDetachResult
(
    MMC_LMM_DETACH_RSLT_ENUM_UINT32 ulDetachRslt
);*/
extern  VOS_VOID    NAS_EMM_Attach_ClearResourse(VOS_VOID);
extern  VOS_VOID    NAS_EMM_Detach_ClearResourse(VOS_VOID);
extern  VOS_VOID    NAS_EMM_AppSendAttSucc( VOS_VOID );
extern VOS_VOID    NAS_EMM_AppSendAttSuccWithoutPara(VOS_VOID);
extern VOS_VOID    NAS_EMM_AppSendAttRej(VOS_VOID);
extern VOS_VOID    NAS_EMM_AppSendAttTimerExp(VOS_VOID);
extern VOS_VOID    NAS_EMM_AppSendAttOtherType
(
    MMC_LMM_ATTACH_RSLT_ENUM_UINT32     ulAttRslt
);
extern VOS_VOID NAS_EMM_AppSendAttFailWithPara(VOS_VOID);
extern VOS_VOID NAS_EMM_AppSendAttFailWithAllPara( VOS_VOID );
extern VOS_VOID NAS_EMM_AttGuAttachRst( MsgBlock * pMsg );
extern VOS_VOID NAS_EMM_DetGuAttachRst( VOS_VOID * pMsg );
extern VOS_VOID NAS_EMM_AppSendAttRejEpsOnly( VOS_VOID );
extern VOS_VOID    NAS_EMM_AppSendAttRstInTau(MMC_LMM_ATTACH_RSLT_ENUM_UINT32 ulAttRst);
extern VOS_VOID  NAS_EMM_AppSendAttRsltForb
(
    EMMC_EMM_FORBIDDEN_INFO_ENUM_UINT32 ulForbInfo
);
extern VOS_UINT32 NAS_EMM_SndAttachReqFailProc(VOS_VOID* pMsg,VOS_UINT32 *pulIsDelBuff);

extern VOS_UINT32 NAS_EMM_SndEsmMsgFailProc(VOS_VOID* pMsg,VOS_UINT32 *pulIsDelBuff);
extern VOS_UINT32 NAS_EMM_SndEsmMsgSuccProc(VOS_VOID* pMsg);
extern VOS_VOID  NAS_EMM_EncodeTmsiBasedNriContainer
(
    VOS_UINT8 *pMsg,
    VOS_UINT32 *pulIeLength
);

extern VOS_UINT32  NAS_EMM_MsRegSsNmlSrvOrUpdateMm3440IsRuningMsgCnDetachReq
                                (NAS_EMM_CN_DETACH_REQ_MT_STRU       *pRcvEmmMsg);
extern VOS_VOID NAS_EMM_MsRegSsNmlSrvOrUpdateMm3440IsRuningMsgImsiDetachReq
(
    const NAS_EMM_CN_DETACH_REQ_MT_STRU *pstRcvEmmMsg
);
extern VOS_VOID NAS_EMM_MsRegSsNmlSrvOrUpdateMm3440IsRuningMsgNotReattach2DetachReq
(
    const NAS_EMM_CN_DETACH_REQ_MT_STRU *pstRcvEmmMsg
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

#endif


