

#ifndef __CNAS_HSM_SND_HSD_H__
#define __CNAS_HSM_SND_HSD_H__

/*****************************************************************************
  1 The Include of the header file
*****************************************************************************/
#include "vos.h"
#include "hsm_hsd_pif.h"
#include "CnasHsmCtx.h"
#include "CnasMain.h"

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

VOS_VOID CNAS_HSM_SndHsdHrpdCasStatusInd(
    HSM_HSD_HRPD_CAS_STATUS_ENUM_UINT16           enCasStatus
);
VOS_VOID CNAS_HSM_SndHsdSessionNegResultInd(
    HSM_HSD_SESSION_NEG_RSLT_ENUM_UINT8                     enNegResult,
    VOS_UINT8                                               ucIsNewSession,
    CNAS_HSM_SESSION_RELEASE_TYPE_ENUM_UINT8                enHsmSessionRelType
);

VOS_VOID CNAS_HSM_SndHsdStartCnf(VOS_VOID);

VOS_VOID CNAS_HSM_SndHsdPowerOffCnf(VOS_VOID);

VOS_VOID CNAS_HSM_SndHsdPowerSaveCnf(VOS_VOID);

VOS_VOID CNAS_HSM_SndHsdConnOpenInd(
    HSM_HSD_HRPD_CONN_OPEN_RSLT_ENUM_UINT8                  enConnOpenRslt
);

HSM_HSD_SESSION_RELEASE_TYPE_ENUM_UINT8 CNAS_HSM_ConvertHsmSessionRelTypeToHsdSessionRelType(
    CNAS_HSM_SESSION_RELEASE_TYPE_ENUM_UINT8                enHsmSessionRelType
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











