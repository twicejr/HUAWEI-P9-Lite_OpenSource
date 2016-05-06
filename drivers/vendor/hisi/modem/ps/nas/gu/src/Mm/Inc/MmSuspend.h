/************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : MmSuspend.h
  Author      : sxbo
  Version     : V200R001
  Date        : 2005-08-16
  Description : 该头文件定义了MM模块SuspendProc子模块内部函数和数据结构
  History     :
  1. Date:2005-08-16
     Author: sxbo
     Modification:Create

  2. x51137 2006/5/5 A32D03487
  3.日    期   : 2006年08月09日
    作    者   : 蒋丽萍j60010247
    修改内容   : 问题单A32D03479，在PC机上实现时将#pragma pack(0)和#pragma pack()加编译开关
************************************************************************/

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

/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, begin */
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
/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-12, end */


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
