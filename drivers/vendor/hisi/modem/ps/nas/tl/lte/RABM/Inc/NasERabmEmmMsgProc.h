

#ifndef __NASRABMEMMMSGPROC_H__
#define __NASRABMEMMMSGPROC_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "NasERabmMain.h"
#include  "EmmRabmInterface.h"
#include  "SmEsmInterface.h"
/* leixiantiao begin */
#include  "PsRrmInterface.h"
/* leixiantiao end */
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


/*****************************************************************************
  9 OTHERS
*****************************************************************************/

extern VOS_VOID NAS_ERABM_EmmMsgDistr( VOS_VOID *pRcvMsg );
extern VOS_VOID  NAS_ERABM_RcvRabmEmmReestInd(const EMM_ERABM_REEST_IND_STRU *pRcvMsg );
extern VOS_VOID  NAS_ERABM_RcvRabmEmmRelInd(VOS_VOID);
extern VOS_VOID  NAS_ERABM_RcvRabmEmmRrcConRelInd(EMM_ERABM_RRC_CON_REL_IND_STRU *pRcvMsg);
extern VOS_VOID NAS_ERABM_SndRrmRegisterInd
(
    RRM_PS_TASK_TYPE_ENUM_UINT16       enTaskType
);
extern VOS_VOID NAS_ERABM_SndRrmDeRegisterInd
(
    RRM_PS_TASK_TYPE_ENUM_UINT16       enTaskType
);
extern VOS_VOID NAS_ERABM_SndRabmEmmReestReq
(
    VOS_UINT32                          ulIsEmcType
);
extern VOS_VOID NAS_ERABM_SndRabmEmmDrbSetupInd( VOS_VOID );
extern VOS_VOID NAS_ERABM_SndRabmEmmRelReq( VOS_VOID);
extern VOS_VOID  NAS_ERABM_RcvRabmEmmSuspendInd(const EMM_ERABM_SUSPEND_IND_STRU *pRcvMsg );
extern VOS_VOID  NAS_ERABM_RcvRabmEmmResumeInd(const EMM_ERABM_RESUME_IND_STRU *pRcvMsg );
extern VOS_VOID NAS_ERABM_SndRabmEmmSuspendRsp
(
    EMM_ERABM_RSLT_TYPE_ENUM_UINT32      enRslt
);
extern VOS_VOID NAS_ERABM_SndRabmEmmResumeRsp
(
    EMM_ERABM_RSLT_TYPE_ENUM_UINT32      enRslt
);


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

#endif /* end of NasERabmEmmMsgProc.h */
