


#ifndef __NASLPPEMMMSGPROC_H__
#define __NASLPPEMMMSGPROC_H__


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include    "vos.h"
#include    "NasLppPublic.h"
#include    "LppMtaInterface.h"

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

#define NAS_LPP_LOW_LAYER_FAIL_RE_REST_TIME_LEN     2000
#define NAS_LPP_3411_FAIL_RE_REST_TIME_LEN          10000


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
extern VOS_VOID NAS_LPP_EmmMsgDistr( VOS_VOID *pRcvMsg );

extern VOS_VOID  NAS_LPP_ResendUplinkMsg
(
    VOS_UINT32                          ulSessionId,
    NAS_LPP_TRANS_ID_STRU               *pstTransId );

extern VOS_VOID  NAS_LPP_SaveLppMsgHead
(
    NAS_LPP_MSG_HEAD_STRU              *pstMsgHead,
    LPP_MESSAGE_STRU                   *pstLppMsgBuff
);
extern VOS_VOID NAS_LPP_LppLmmEstReq( VOS_VOID );
extern VOS_VOID NAS_LPP_GNSSCapReq
(
    VOS_VOID
);
extern VOS_UINT32  NAS_LPP_GetRefEarfcnFromOtdoaAssis( LPP_OTDOA_REF_CELL_INFO_STRU  *pstOtdoaRefCellInfo );
extern VOS_UINT8 NAS_LPP_SndUplinkProvideCapbilityMsg
(
    NAS_LPP_MSG_HEAD_STRU              *pstLppMsgHead,
    VOS_UINT32                          ulSessionId,
    VOS_UINT8                           ucTransIndx
);
extern VOS_VOID  NAS_LPP_CreatNewTransAndReqAssistData
(
    VOS_UINT8                               ucSessionIndx,
    VOS_BOOL                                enOtdoaAssist,
    VOS_BOOL                                enGnssAssist,
    MTA_LPP_GNSS_ASSIST_DATA_REQ_STRU      *pstMtaLppGnssAssistDataReq
);
extern VOS_VOID NAS_LPP_SendUplinkMsg
(
    VOS_UINT32                          ulSessionId,
    VOS_UINT32                          ulLppMsgLen,
    VOS_UINT8                          *pucEncodeOutMsg,
    NAS_LPP_MSG_IDENTITY_STRU          *pstLppMsgIdentity
);
extern VOS_VOID  NAS_LPP_ConnFailHandle(VOS_VOID);
extern NAS_LPP_USER_PLANE_ENTITY_STRU*  NAS_LPP_GetLppUpEntityCtx( VOS_VOID );
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











































