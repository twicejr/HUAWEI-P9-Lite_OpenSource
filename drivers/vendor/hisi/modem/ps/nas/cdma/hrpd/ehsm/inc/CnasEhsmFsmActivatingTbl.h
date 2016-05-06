

#ifndef __CNAS_EHSM_FSM_ACTIVATING_TBL_H__
#define __CNAS_EHSM_FSM_ACTIVATING_TBL_H__

/*****************************************************************************
  1 The Include of the header file
*****************************************************************************/
#include "vos.h"
#include "NasFsm.h"


#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif
#endif


#pragma pack(4)

extern NAS_STA_STRU                     g_astCnasEhsmActivatingStaTbl[];
/*****************************************************************************
  2 The Macro Define
*****************************************************************************/
#define CNAS_EHSM_GetActivatingStaTbl()                   (g_astCnasEhsmActivatingStaTbl)


/*****************************************************************************
  3 The Enumeration Define
*****************************************************************************/


enum CNAS_EHSM_ACTIVATING_STA_ENUM
{
    CNAS_EHSM_ACTIVATING_STA_INIT,

    CNAS_EHSM_ACTIVATING_STA_WAIT_HSM_CONN_CNF,

    CNAS_EHSM_ACTIVATING_STA_WAIT_CONN_EST_RETRY_TIME_OUT,

    CNAS_EHSM_ACTIVATING_STA_WAIT_CTTF_PDN_SETUP_CNF,

    CNAS_EHSM_ACTIVATING_STA_WAIT_PDN_RETRY,

    CNAS_EHSM_ACTIVATING_STA_BUTT
};
typedef VOS_UINT32  CNAS_EHSM_ACTIVATING_STA_ENUM_UINT32;


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
VOS_UINT32 CNAS_EHSM_GetActivatingStaTblSize(
    VOS_VOID);

NAS_FSM_DESC_STRU *CNAS_EHSM_GetActivatingFsmDescAddr(
    VOS_VOID);
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

#endif /* end of CnasEhsmActivatingTbl.h */

