

#ifndef __CNAS_EHSM_PROC_NVIM_H__
#define __CNAS_EHSM_PROC_NVIM_H__

/*****************************************************************************
  1 The Include of the header file
*****************************************************************************/
#include "vos.h"
#include "CnasEhsmCtx.h"
#include "NVIM_Interface.h"
#include "NasNvInterface.h"
/* To Do: Need to add interface files */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

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
VOS_VOID CNAS_EHSM_InitConnEstRetryInfoNvim (
    CNAS_EHSM_RETRY_CONN_EST_INFO_STRU   *pstRetryConnEstInfoInfo
);

VOS_VOID CNAS_EHSM_InitPdnSetupRetryInfoNvim (
    CNAS_EHSM_RETRY_PDN_SETUP_INFO_STRU  *pstRetryPdnSetupInfoInfo
);

#endif /* FEATURE_UE_MODE_CDMA */

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

#endif /* end of CnasEhsmProcNvim.h */



