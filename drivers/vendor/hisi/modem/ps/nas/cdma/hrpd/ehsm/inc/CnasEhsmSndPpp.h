

#ifndef __CNAS_EHSM_SND_PPP_H__
#define __CNAS_EHSM_SND_PPP_H__

/*****************************************************************************
  1 The Include of the header file
*****************************************************************************/
#include "vos.h"
#include "cnas_cttf_ehrpd_ehsm_ppp_pif.h"
#include "ehsm_aps_pif.h"
#include "CnasEhsmSndInternalMsg.h"

/* To Do: Need to add interface file */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 The Macro Define
*****************************************************************************/


/*****************************************************************************
  3 The Enumeration Define
*****************************************************************************/


/*****************************************************************************
  4 The Declaration Of The Gloabal Variable
*****************************************************************************/


/*****************************************************************************
  5 The Define Of the Message Header
*****************************************************************************/


/*****************************************************************************
  6 The Define of the Message Name
*****************************************************************************/


/*****************************************************************************
  7 The Struct Define
*****************************************************************************/


/*****************************************************************************
  8 The Union Define
*****************************************************************************/


/*****************************************************************************
  9 Other Defines
*****************************************************************************/


/*****************************************************************************
  10 The Declaration Of The Function
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/* To Do: Need to include prototypes for sending messages from EHSM to PPP */
VOS_VOID CNAS_EHSM_SndCttfEhrpdPdnConnReq(
    VOS_UINT8                           ucPdnId
);

VOS_VOID CNAS_EHSM_SndCttfEhrpdAttachReq(
    VOS_UINT8                              ucPdnId,
    CNAS_EHSM_ATTACH_REASON_ENUM_UINT32    enAttachReason
);

VOS_VOID CNAS_EHSM_SndCttfEhrpdPdnDiscReq(
    VOS_UINT8                           ucPdnId
);

VOS_VOID CNAS_EHSM_SndCttfEhrpdDetachReq(
    VOS_VOID
);
VOS_VOID CNAS_EHSM_SndCttfEhrpdPdnLocalDiscInd(
    VOS_UINT8                ucPdnId
);
VOS_VOID CNAS_EHSM_SndCttfEhrpdDetachInd(
    VOS_VOID
);

VOS_VOID CNAS_EHSM_SndCttfEhrpdLinkStatusNotify(
    CNAS_CTTF_EHRPD_LINK_STATUS_ENUM_UINT8                  enLinkStatus
);
#endif

#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of CnasEhsmSndPpp.h */





