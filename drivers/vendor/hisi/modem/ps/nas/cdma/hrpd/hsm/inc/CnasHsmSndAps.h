

#ifndef __CNAS_HSM_SND_APS_H__
#define __CNAS_HSM_SND_APS_H__

/*****************************************************************************
  1 The Include of the header file
*****************************************************************************/
#include "vos.h"
#include "cas_hrpd_airlinkmgmt_nas_pif.h"
#include "hsm_hlu_pif.h"
#include "CnasHsmComFunc.h"
#include "hsm_aps_pif.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 The Macro Define
*****************************************************************************/
#define CNAS_HSM_CALL_ID_INVALID        ( 0xff )


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


VOS_VOID CNAS_HSM_SndApsOrigCnf(
    VOS_UINT8                           ucCallId,
    HSM_APS_CAUSE_ENUM_UINT32           enApsCallRslt
);

VOS_VOID CNAS_HSM_SndApsConnInd(
    VOS_UINT8                           ucCallId
);

VOS_VOID CNAS_HSM_SndApsDiscCnf(
    VOS_UINT8                           ucCallId,
    HSM_APS_CAUSE_ENUM_UINT32           enCause
);

VOS_VOID CNAS_HSM_SndApsDiscInd(
    VOS_UINT8                           ucCallId,
    HSM_APS_CAUSE_ENUM_UINT32           enCause
);

VOS_VOID CNAS_HSM_SndApsHandOffCnf(
    HSM_APS_CAUSE_ENUM_UINT32           enCause
);

VOS_VOID CNAS_HSM_SndApsLocChngdInd(
    CNAS_HSM_CONST  HLU_HSM_LOC_CHANGED_IND_STRU           *pstHluLocChngMsg
);

VOS_VOID CNAS_HSM_SndApsHrpdAvailableInd(VOS_VOID);

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

#endif /* end of CnasHsmSndAps.h */











