

#ifndef __CNAS_HSM_FSM_CACHED_MSG_PRI_MNMT_H__
#define __CNAS_HSM_FSM_CACHED_MSG_PRI_MNMT_H__

/*****************************************************************************
  1 The Include of the header file
*****************************************************************************/
#include "vos.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 The Macro Define
*****************************************************************************/
#define CNAS_HSM_MSG_PRI_TBL_ITEM(PID, enMsgType, enMsgPri)\
{\
    ((((VOS_UINT16)(PID)) << 16) | (enMsgType)),\
    ((enMsgPri))\
}


/*****************************************************************************
  3 The Enumeration Define
*****************************************************************************/

enum  CNAS_HSM_MSG_PRI_ENUM
{
    CNAS_HSM_MSG_PRI_LVL_0                      = 0x00,
    CNAS_HSM_MSG_PRI_LVL_1                      = 0x01,
    CNAS_HSM_MSG_PRI_LVL_2                      = 0x02,
    CNAS_HSM_MSG_PRI_LVL_BUTT
};
typedef VOS_UINT8 CNAS_HSM_MSG_PRI_ENUM_UINT8;
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


typedef struct
{
    VOS_UINT32                                              ulEventType;
    CNAS_HSM_MSG_PRI_ENUM_UINT8                             enMsgPri;
    VOS_UINT8                                               aucRcv[3];
} CNAS_HSM_MSG_PRI_STRU;

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
CNAS_HSM_MSG_PRI_ENUM_UINT8 CNAS_HSM_FindMsgPri(
    VOS_UINT32                          ulEventType
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

#endif /* end of CnasHsmFsmCachedMsgPriMnmt.h */