

#ifndef __NASRABMRRCMSGPROC_H__
#define __NASRABMRRCMSGPROC_H__


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "LRrcLNasInterface.h"
#include  "NasERabmMain.h"
#include  "NasERabmEmmMsgProc.h"

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


#define NAS_ERABM_RCVRBREL(ulEpsbId)  NAS_ERABM_RcvRbSetupFail(ulEpsbId)




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
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_VOID  NAS_ERABM_InformEsmBearerStatus( VOS_UINT8 ucSessionId );
extern VOS_VOID  NAS_ERABM_RcvRabmRrcRabInd(const LRRC_LRABM_RAB_IND_STRU *pRcvMsg );
extern VOS_VOID  NAS_ERABM_RcvRabmRrcStatusInd(const LRRC_LRABM_STATUS_IND_STRU *pRcvMsg );
extern VOS_VOID  NAS_ERABM_RcvRabmRrcStatusMsgProc( VOS_UINT32 ulRabCnt,
                                                                    VOS_UINT32 ulStatus,
                                                                    const VOS_UINT32 *pulEpsbId);
extern VOS_VOID NAS_ERABM_RcvRbRelease( VOS_UINT32 ulEpsbId );
extern VOS_VOID  NAS_ERABM_RcvRbSetupFail( VOS_UINT32 ulEpsbId );
extern VOS_VOID NAS_ERABM_RcvRbSetupSucc( VOS_UINT32 ulEpsbId, VOS_UINT32 ulRbId );
VOS_VOID NAS_ERABM_RcvRbReconfig( VOS_UINT32 ulEpsbId, VOS_UINT32 ulRbId );
extern VOS_VOID NAS_ERABM_RrcMsgDistr( VOS_VOID *pRcvMsg );
extern VOS_VOID NAS_ERABM_SndRabmRrcQosUpdateReq( VOS_VOID );
extern VOS_VOID NAS_ERABM_SndRabmRrcRabRsp(const VOS_UINT32* pulRabId,
                                                         VOS_UINT32 ulRabCnt);
extern VOS_VOID  NAS_ERABM_SndRabmRrcStatusRsp( VOS_UINT32 ulResult );
extern VOS_UINT32  NAS_ERABM_HasDrbWithoutRelatingEpsBear( VOS_VOID );
extern VOS_UINT32  NAS_ERABM_IsAllActtiveBearerWithoutDrb( VOS_VOID );
extern VOS_VOID  NAS_ERABM_RrcRabIndResultProc
(
    PS_BOOL_ENUM_UINT8                  enIsRecSetupSucc,
    PS_BOOL_ENUM_UINT8                  enIsRecSetupFail,
    PS_BOOL_ENUM_UINT8                  enIsRecRelease
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

#endif /* end of NasERabmRrcMsgProc.h */

