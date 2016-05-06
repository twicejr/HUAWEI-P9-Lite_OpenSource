

#ifndef __CNAS_EHSM_MAIN_H__
#define __CNAS_EHSM_MAIN_H__

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

VOS_UINT32 CNAS_EHSM_PreProcessMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_EHSM_FSM_ProcessEvent(
    VOS_UINT32                          ulCurState,
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pRcvMsg
);

VOS_UINT32 CNAS_EHSM_ProcessMsgInFsm(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_VOID CNAS_EHSM_ProcessBufferMsg(
    VOS_VOID
);

VOS_VOID CNAS_EHSM_MsgProc (
    struct MsgCB*                       pstMsg
);

VOS_UINT32 CNAS_EHSM_RegPreProcFsm(
    VOS_VOID
);

VOS_UINT32 CNAS_EHSM_RegL1MainFsm(
    VOS_VOID
);

VOS_VOID CNAS_EHSM_RegL2Fsm(
    VOS_VOID
);

VOS_VOID  CNAS_EHSM_RegFsm(
    VOS_VOID
);

VOS_UINT32  CNAS_EHSM_InitTask(
    VOS_VOID
);

VOS_UINT32 CNAS_EHSM_InitPid(
    enum VOS_INIT_PHASE_DEFINE         enInitPhase
);
VOS_UINT32  CNAS_EHSM_ProcMsgPrio(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  CNAS_EHSM_PostProcessMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID CNAS_EHSM_MsgProcEntry(
    struct MsgCB                       *pstMsg
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

#endif /* end of CnasEhsmMain.h */


