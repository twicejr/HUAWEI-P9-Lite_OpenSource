

#ifndef __CNAS_HSM_SND_AS_H__
#define __CNAS_HSM_SND_AS_H__

/*****************************************************************************
  1 The Include of the header file
*****************************************************************************/
#include "vos.h"
#include "cas_hrpd_sessioncfg_nas_pif.h"
#include "PsCommonDef.h"
#include "cas_hrpd_airlinkmgmt_nas_pif.h"
#include "cas_hrpd_idlestate_nas_pif.h"

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
VOS_VOID CNAS_HSM_SndCasHrpdScpActiveReq(
    CNAS_CAS_HRPD_SCP_ACT_TYPE_ENUM_UINT8                   enActiveType,
    PS_BOOL_ENUM_UINT8                                      enEhrpdFlag
);

VOS_VOID CNAS_HSM_SndCasHrpdScpDeActiveReq(VOS_VOID);

VOS_VOID CNAS_HSM_SndCasHrpdConnCloseReq(VOS_VOID);

VOS_VOID CNAS_HSM_SndCasHrpdSessionSeedNtf(VOS_UINT32 ulSessionSeed);


VOS_VOID CNAS_HSM_SndCasHrpdConnOpenReq(
    CNAS_CAS_HRPD_CONN_OPEN_TYPE_ENUM_UINT8                 enConnType
);

VOS_VOID CNAS_HSM_SndCasHrpdSessionBeginNtf(
    CNAS_CAS_HRPD_SESSION_TYPE_ENUM_UINT16                  enSessionType
);

VOS_VOID CNAS_HSM_SndCasHrpdSessionEndNtf(
    CNAS_CAS_HRPD_SESSION_TYPE_ENUM_UINT16                  enSessionType
);

VOS_VOID CNAS_HSM_SndCasHrpdSlotVoteNtf(
    CNAS_CAS_HRPD_SLOT_VOTE_ENUM_UINT16 enSlotVoteFlag
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

#endif /* end of CnasHsmMain.h */










