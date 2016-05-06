

#ifndef __NASRABMSMMSGPROC_H__
#define __NASRABMSMMSGPROC_H__


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "EsmRabmInterface.h"
#include  "NasERabmMain.h"
#include  "NasERabmRrcMsgProc.h"

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
/*用来指示激活消息中的承载是否为已经激活的承载*/
#define NAS_ERABM_EPSB_ACT             0
#define NAS_ERABM_EPSB_DEACT           1

/*用来指示等待EPS承载激活临时表中的承载是否全部激活*/
#define NAS_ERABM_WAIT_ALLEPSB_ACT     0
#define NAS_ERABM_WAIT_NOT_ALLEPSB_ACT 1

/*清空Qos参数标识*/
#define NAS_ERABM_QOS_NULL             0
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

extern VOS_VOID NAS_ERABM_ClearEpsbResource( VOS_UINT32 ulEpsbId );
extern VOS_VOID NAS_ERABM_EsmMsgDistr( VOS_VOID *pRcvMsg );
extern VOS_VOID  NAS_ERABM_SrchOnlyActiveAndNoUlTftEpsb( VOS_VOID );
extern VOS_UINT32 NAS_ERABM_GetNewTftPfIndex( VOS_UINT32 * pulNewTftPfIndex );
extern VOS_VOID  NAS_ERABM_RcvRabmEsmActInd(const ESM_ERABM_ACT_IND_STRU *pRcvMsg );
extern VOS_VOID NAS_ERABM_RcvRabmEsmDeactInd(const ESM_ERABM_DEACT_IND_STRU *pRcvMsg );
extern VOS_VOID NAS_ERABM_RcvRabmEsmMdfInd(const ESM_ERABM_MDF_IND_STRU *pRcvMsg );
extern VOS_VOID NAS_ERABM_RcvRabmEsmRelInd( VOS_VOID );
extern VOS_VOID NAS_ERABM_SaveEpsbActInfo(const ESM_ERABM_ACT_IND_STRU *pRcvMsg, VOS_UINT32 ulEpsbId );
extern VOS_VOID NAS_ERABM_SaveUeIpAddr(const ESM_ERABM_ACT_IND_STRU *pRcvMsg, VOS_UINT32 ulEpsbId);
extern VOS_VOID NAS_ERABM_SndRabmEsmBearerStatusReq(const VOS_UINT32 *pulEpsbId,
                                                              VOS_UINT32 ulEpsbIdNum,
                                                              VOS_UINT8 ucSessionId);
extern VOS_VOID NAS_ERABM_SndRabmEsmRelReq( VOS_VOID );

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
extern VOS_VOID NAS_ERABM_SaveEhrpdbActInfo(
    const ESM_ERABM_ACT_IND_STRU       *pRcvMsg
);
extern VOS_VOID NAS_ERABM_RcvRabmEsmClearClBearerNotify(VOS_VOID);
#endif

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

#endif /* end of NasERabmEsmMsgProc.h */
