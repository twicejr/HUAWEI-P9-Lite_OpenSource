

#ifndef __CNAS_HSM_MAIN_H__
#define __CNAS_HSM_MAIN_H__

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
extern VOS_UINT32 CNAS_HSM_ProcessMsgInFsm(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pRcvMsg
);

extern VOS_VOID CNAS_HSM_ProcessBufferMsg(VOS_VOID);

extern VOS_VOID CNAS_HSM_MsgProc (struct MsgCB* pstMsg);

extern VOS_UINT32  CNAS_HSM_InitTask(VOS_VOID);

extern VOS_UINT32 CNAS_HSM_InitPid(
    enum VOS_INIT_PHASE_DEFINE         enInitPhase
);

extern VOS_UINT32 CNAS_HSM_PreProcessMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_VOID CNAS_HSM_ProcessHsmIntMsg(VOS_VOID);




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



