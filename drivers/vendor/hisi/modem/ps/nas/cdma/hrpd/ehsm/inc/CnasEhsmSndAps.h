

#ifndef __CNAS_EHSM_SND_APS_H__
#define __CNAS_EHSM_SND_APS_H__

/*****************************************************************************
  1 The Include of the header file
*****************************************************************************/
#include "vos.h"
#include "ehsm_aps_pif.h"


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

/* To Do: Need to include prototypes for sending messages from EHSM to APS */

VOS_VOID CNAS_EHSM_SndApsPdnActivateInd(
    VOS_UINT8                           ucPdnId
);

VOS_VOID CNAS_EHSM_SndApsPdnAttachCnf(
    VOS_UINT8                           ucPdnId,
    EHSM_APS_CAUSE_ENUM_UINT32          enCause
);

VOS_VOID CNAS_EHSM_SndApsLteHandOverToEhrpdInd(
    VOS_UINT8                           ucPdnId,
    EHSM_APS_PDN_OPTION_ENUM_UINT32     enPdnOption
);

VOS_VOID CNAS_EHSM_SndApsPdnActivateCnf(
    VOS_UINT8                           ucCid,
    EHSM_APS_CAUSE_ENUM_UINT32          enCause
);

VOS_VOID CNAS_EHSM_SndApsPdnDeactivateCnf(
    VOS_UINT8                           ucPdnId,
    VOS_UINT8                           ucCid,
    VOS_UINT32                          enCause
);
VOS_VOID CNAS_EHSM_SndApsPdnDeactivateInd(
    VOS_UINT8                   ucPdnId,
    VOS_UINT8                   ucCid,
    VOS_UINT32                  enCause
);


VOS_VOID CNAS_EHSM_SndApsReconnCnf(
    EHSM_APS_CAUSE_ENUM_UINT32          enCause,
    VOS_UINT8                           ucPdnId,
    VOS_UINT8                           ucCid
);

VOS_VOID CNAS_EHSM_SndApsDiscCnf(
    VOS_VOID
);

VOS_VOID CNAS_EHSM_SndApsPdnChgInd(
    EHSM_APS_PDN_CHANGE_INFO_STRU      *pstPdnChgInfo,
    VOS_UINT8                           ucPdnId
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

#endif /* end of CnasEhsmSndAps.h */

