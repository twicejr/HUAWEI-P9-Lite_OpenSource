

#ifndef __CNAS_HSM_FSM_TBL_H__
#define __CNAS_HSM_FSM_TBL_H__

/*****************************************************************************
  1 The Include of the header file
*****************************************************************************/
#include "vos.h"
#include "NasFsm.h"
#include "cas_hrpd_sessioncfg_nas_pif.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 The Macro Define
*****************************************************************************/
extern NAS_STA_STRU                                         g_astCnasHsmFsmStaTbl[];

#define CNAS_HSM_GetFsmStaTbl()                             (g_astCnasHsmFsmStaTbl)

/*****************************************************************************
  3 The Enumeration Define
*****************************************************************************/

enum CNAS_HSM_EVENT_HANDLED_STATUES_ENUM
{
    CNAS_HSM_FSM_EVENT_NOT_HANDLED                              = 0x00,
    CNAS_HSM_FSM_EVENT_HANDLED                                  = 0x01,

    CNAS_HSM_FSM_EVENT_HANDLED_BUTT
};
typedef VOS_UINT32 CNAS_HSM_EVENT_HANDLED_STATUES_ENUM_UINT32;


enum CNAS_HSM_L1_STA_ENUM
{
    CNAS_HSM_L1_STA_NULL                                        = 0x00,

    CNAS_HSM_L1_STA_INACTIVE                                    = 0x01,

    CNAS_HSM_L1_STA_SETUP                                       = 0x02,

    CNAS_HSM_L1_STA_OPEN                                        = 0x03,

    CNAS_HSM_L1_STA_SLAVE                                       = 0x04,


    CNAS_HSM_L1_STA_PREPROC,                                           /* preproc state */

    CNAS_HSM_L1_STA_ID_BUTT

};
typedef VOS_UINT32 CNAS_HSM_L1_STA_ENUM_UINT32;



enum CNAS_HSM_SS_ID_ENUM
{
    CNAS_HSM_SS_VACANT                                      = 0x00,

    /* Session Acitve Procedure SubState */
    CNAS_HSM_SS_SESSION_ACT_INIT,
    CNAS_HSM_SS_SESSION_ACT_WAIT_SCP_ACTIVE_CNF,
    CNAS_HSM_SS_SESSION_ACT_WAIT_PA_RAT_MODE_NTF,

    /* Session Deacitve Procedure SubState */
    CNAS_HSM_SS_SESSION_DEACT_INIT,

    CNAS_HSM_SS_SESSION_DEACT_WAIT_SESSION_CLOSE_SNP_DATA_CNF,
    CNAS_HSM_SS_SESSION_DEACT_WAIT_CONN_CLOSE_IND,
    CNAS_HSM_SS_SESSION_DEACT_WAIT_SCP_DEACTIVE_CNF,

    /* UATI Request Procedure SubState */
    CNAS_HSM_SS_UATI_REQUEST_INIT,
    CNAS_HSM_SS_UATI_REQUEST_WAIT_SNP_DATA_CNF,
    CNAS_HSM_SS_UATI_REQUEST_WAIT_UATI_ASSIGN,

#if 0
    CNAS_HSM_SS_UATI_REQUEST_WAIT_UATI_COMPLETE_SNP_DATA_CNF,
#endif

    /* connetion management Porcedurce SubState */
    CNAS_HSM_SS_CONN_MNMT_INIT,
    CNAS_HSM_SS_CONN_MNMT_WAIT_HRPD_CONN_OPEN_IND,
    CNAS_HSM_SS_CONN_MNMT_WAIT_HRPD_CONN_CLOSE_IND,

    /* switch on read card procedure */
    CNAS_HSM_SS_SWITCH_ON_INIT,
    CNAS_HSM_SS_SWITCH_ON_WAIT_CARD_READ_CNF,

    CNAS_HSM_SS_ID_BUTT
};
typedef VOS_UINT32 CNAS_HSM_SS_ID_ENUM_UINT32;



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
extern VOS_VOID  CNAS_HSM_RegisterFsm(VOS_VOID);
extern VOS_UINT32  CNAS_HSM_GetFsmStaTblSize(VOS_VOID);
extern NAS_FSM_DESC_STRU* CNAS_HSM_GetFsmDescAddr(VOS_VOID);

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

#endif /* end of CnasHsmFsmTbl.h */


