/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasEsmTimerMsgProc.h
    Description :
    History     :
     1.丁丽 00128736      2008-09-01  Draft Enact
     2.祝义强 00138739    2008-09-10
     3.孙兵 49683         2009-01-06  BA8D00870
     4.杨茜惠 00135146    2009-03-06  Modify  BA8D01127
******************************************************************************/

#ifndef _NASESMTIMERPROC_H
#define _NASESMTIMERPROC_H

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include    "vos.h"
#include    "NasEsmPublic.h"
#include    "NasCommBuffer.h"

/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*****************************************************************************
  #pragma pack(*)    设置字节对齐方式
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/
/*定时器最大超时次数*/
#define TI_NAS_ESM_T3482_TIMER_MAX_EXP_NUM                  5
#define TI_NAS_ESM_T3492_TIMER_MAX_EXP_NUM                  5
#define TI_NAS_ESM_T3480_TIMER_MAX_EXP_NUM                  5
#define TI_NAS_ESM_T3481_TIMER_MAX_EXP_NUM                  5


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/



/*****************************************************************************
  5 STRUCT
*****************************************************************************/

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_VOID    NAS_ESM_ProcTimerMsgT3480Exp(const VOS_VOID * pMsg);
extern VOS_VOID    NAS_ESM_ProcTimerMsgT3481Exp(const VOS_VOID * pMsg);
extern VOS_VOID    NAS_ESM_ProcTimerMsgT3492Exp(const VOS_VOID * pMsg);
extern VOS_VOID    NAS_ESM_ProcTimerMsgT3482Exp(const VOS_VOID * pMsg);
extern VOS_VOID NAS_ESM_TimerMsgDistr(const VOS_VOID *pRcvMsg );
extern VOS_VOID NAS_ESM_ProcTimerMsgWaitAppCnfExp(const VOS_VOID * pMsg);
extern VOS_VOID NAS_ESM_ProcTimerMsgWaitPtiInvaidExp(const VOS_VOID * pMsg);
extern VOS_VOID NAS_ESM_ProcTimerMsgAttachBearerReestExp(const VOS_VOID * pMsg);
extern VOS_VOID NAS_ESM_ProcTimerMsgDeferRelNonEmcExp(const VOS_VOID * pMsg);





/*****************************************************************************
  9 OTHERS
*****************************************************************************/



#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of NasEsmTimerMsgProc.h*/
