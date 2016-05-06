

#ifndef __CNAS_EHSM_SND_ESM_H__
#define __CNAS_EHSM_SND_ESM_H__

/*****************************************************************************
  1 The Include of the header file
*****************************************************************************/
#include "vos.h"
#include "ehsm_esm_pif.h"
#include "CnasEhsmCtx.h"
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

/* To Do: Need to include prototypes for sending messages from EHSM to ESM */
VOS_VOID CNAS_EHSM_SndEsmSyncEhrpdPdnInfoInd(
    CNAS_EHSM_EHRPD_PDN_BEAR_INFO_STRU *pstPdnInfo,
    VOS_UINT32                          ulAttachFlag,
    EHSM_ESM_PDN_OPTION_ENUM_UINT32     enPdnOption
);
VOS_VOID CNAS_EHSM_SndEsmClearAllNtf(VOS_VOID);


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

#endif /* end of CnasEhsmSndEsm.h */


