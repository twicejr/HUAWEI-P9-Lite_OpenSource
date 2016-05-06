

#ifndef __CNAS_EHSM_PRE_PROC_TBL_H__
#define __CNAS_EHSM_PRE_PROC_TBL_H__

/*****************************************************************************
  1 The Include of the header file
*****************************************************************************/
#include "vos.h"
#include "NasFsm.h"
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
extern NAS_STA_STRU                                         g_astCnasEhsmPreProcStaTbl[];

#define CNAS_EHSM_GetPreProcStaTbl()                        (g_astCnasEhsmPreProcStaTbl)


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

/* To Do: Need to include interfaces for EHSM preproc table */
VOS_UINT32 CNAS_EHSM_GetPreProcStaTblSize(
    VOS_VOID
);

NAS_FSM_DESC_STRU* CNAS_EHSM_GetPreProcDescAddr(
    VOS_VOID
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

#endif /* end of CnasEhsmPreProcTbl.h */



