

#ifndef __TAF_X_CALL_MAIN_H__
#define __TAF_X_CALL_MAIN_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "v_timer.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/


/*****************************************************************************
  3 枚举定义
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
typedef VOS_VOID (*TAF_XCALL_MSG_PROC_FUNC)(VOS_VOID* pMsg);


typedef struct
{
    VOS_UINT32                          ulMsgType;                              /* TAF XCALL 接收消息ID */
    TAF_XCALL_MSG_PROC_FUNC             pProcMsgFunc;
}TAF_XCALL_MSG_PROC_STRU;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/


#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_VOID TAF_XCALL_ProcAppReqMsg(struct MsgCB* pstMsg);
VOS_VOID TAF_XCALL_ProcXccMsg(struct MsgCB* pstMsg);
VOS_VOID TAF_XCALL_ProcVcMsg(struct MsgCB* pstMsg);
VOS_VOID TAF_XCALL_ProcMmaMsg(struct MsgCB* pstMsg);

VOS_VOID TAF_XCALL_ProcTimerOutMsg(
    REL_TIMER_MSG                      *pTmrMsg
);

VOS_VOID TAF_XCALL_ProcUsimMsg(struct MsgCB* pstMsg);


#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
VOS_VOID TAF_XCALL_ProcXsmsMsg(struct MsgCB* pstMsg);
#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT_TEST_MODE)
VOS_VOID TAF_XCALL_ProcCttfMsg(struct MsgCB* pstMsg);
#endif
#endif
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

#endif /* end of TafXCallMain.h */

