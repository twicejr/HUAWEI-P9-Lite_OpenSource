/******************************************************************************

            Copyright 2014, Huawei Technologies Co. Ltd.

 ******************************************************************************
File Name       :   NasMsccMain.h
Author          :   k902809
Version         :
Date            :   2015-02-02
Description     :   Contains interfaces to interact with MSCC Power-off FSM.
Function list   :
History         :
    1) Date :
       Author:
       Modification:
******************************************************************************/


#ifndef _NAS_MSCC_MAIN_H_
#define _NAS_MSCC_MAIN_H_

/*****************************************************************************
  1 Inclusing header files
*****************************************************************************/

#include  "vos.h"
#include  "PsTypeDef.h"
#include  "NasMsccFsmPowerOffTbl.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  1 Global Variales
*****************************************************************************/

/*****************************************************************************
  2 Macro Definitions
*****************************************************************************/
#if (VOS_WIN32 == VOS_OS_VER)
#define NAS_MSCC_TASK_PRIO                                   (137)
#endif
/*****************************************************************************
  3 Enumerations
*****************************************************************************/


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/



/*****************************************************************************
  10 Function declarations
*****************************************************************************/
VOS_UINT32 NAS_MSCC_PreProcessMsg(
        VOS_UINT32                      ulEventType,
        struct MsgCB                   *pstMsg
);

VOS_UINT32 NAS_MSCC_FSM_ProcessEvent(
    VOS_UINT32                          ulCurState,
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pRcvMsg
);

VOS_UINT32 NAS_MSCC_ProcessMsgInFsm(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID NAS_MSCC_ProcessMsccIntMsg( VOS_VOID );

VOS_VOID NAS_MSCC_ProcessBufferMsg( VOS_VOID );

VOS_VOID NAS_MSCC_MsgProc (struct MsgCB*);

VOS_VOID NAS_MSCC_RegPreFsm(VOS_VOID);

VOS_VOID NAS_MSCC_RegMainL1Fsm(VOS_VOID);

VOS_VOID NAS_MSCC_RegL2Fsm(VOS_VOID);

VOS_VOID  NAS_MSCC_RegFsm(VOS_VOID);

VOS_UINT32  NAS_MSCC_InitTask(VOS_VOID);

VOS_UINT32 NAS_MSCC_InitPid(
    enum VOS_INIT_PHASE_DEFINE         enInitPhase
);

VOS_UINT32 NAS_MSCC_PostProcessMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MSCC_ProcMsgPrio(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

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

#endif /* end of NasMsccMain.h */


