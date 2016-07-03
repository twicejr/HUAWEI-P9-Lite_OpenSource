

#ifndef _MM_SUSPEND_H_
#define _MM_SUSPEND_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "MmSelf.h"

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define MM_CONNECT_EXIST                0                   /* MM 连接存在或正在建 MM 连接 */
#define MM_CONNECT_NOT_EXIST            1                   /* MM 连接不存在 */

/*******************************************************************************
  3 枚举定义
*******************************************************************************/

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/
/*模块名＋意义＋HEADER
 */


/*****************************************************************************
  6 消息定义
*****************************************************************************/

/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/
/*Identification 标识：MM_TIMER_ST
Type 类型：
Purpose目的：定时器结构*/
/* ucTimerStatus 取值 */
#define MM_TIMER_STOPPED                0
#define MM_TIMER_START                  1

typedef struct
{
    HTIMER          stTimer;
    VOS_UINT32      ulTimerLength;
    VOS_UINT8       ucTimerStatus;
}MM_TIMER_ST;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

VOS_VOID MM_SaveMsg(const VOS_VOID* pMsg, VOS_UINT8 ucEventId, VOS_UINT32 ulLength);

VOS_VOID MM_SndMsgFuncChg(VOS_VOID);

VOS_VOID MM_RetransferMsg(VOS_VOID);
VOS_VOID MM_Restore(VOS_VOID);

VOS_VOID MM_InsertMsg(VOS_VOID *pMsg, VOS_UINT8 ucEventId);

MM_SUSPEND_MSG_CELL_ST* MM_GetMsg(VOS_VOID);

VOS_VOID MM_RelMsgBuf(VOS_VOID);

VOS_VOID MM_SuspendTimeout(VOS_VOID);

#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID NAS_MM_ProcResumeIndBackToLTE(
    MMCMM_RESUME_IND_STRU              *pstResumeMsg
);
#endif

VOS_VOID NAS_MM_ResumeSuspendInfo(
    MMCMM_RESUME_IND_STRU              *pstResumeMsg
);

VOS_VOID NAS_MM_ProcResumeIndBackToGU(
    MMCMM_RESUME_IND_STRU              *pstResumeMsg
);

VOS_VOID  NAS_MM_ChgStateIntoLMode( VOS_VOID );

#if (FEATURE_ON == FEATURE_IMS)
VOS_VOID NAS_MM_ProcResumeIndBackToGU_Srvcc(VOS_VOID);
#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID NAS_MM_ProcResumeIndBackToLTE_Srvcc(VOS_VOID);
#endif
VOS_VOID NAS_MM_ProcSrvccFail(VOS_VOID);
VOS_VOID NAS_MM_ProcSrvccSuccess(VOS_VOID);
#endif


#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of MmSuspend.h*/
