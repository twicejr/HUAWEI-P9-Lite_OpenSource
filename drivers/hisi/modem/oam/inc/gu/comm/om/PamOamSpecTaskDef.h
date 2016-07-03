



/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"

#ifndef __OM_SPECTASK_DEF_H__
#define __OM_SPECTASK_DEF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  3 HPA的任务定义
*****************************************************************************/

/*HPA的任务栈定义*/
#define     HPA_DELIVER_TASK_STACK_SIZE     (2560)

#define     HPA_TRANSFER_TASK_STACK_SIZE    (8192)

#define     OM_BBP_DBG_TASK_STACK_SIZE      (4096)


/*****************************************************************************
  5 Pc Voice 的任务定义
*****************************************************************************/

#define     PCV_TRANS_TASK_PRIORITY         (VOS_PRIORITY_P2)

#define     PCV_TRANS_TASK_STACK_SIZE       (4096)


/*****************************************************************************
  7 OM Sleep 的任务定义
*****************************************************************************/

#define     GSLEEP_TASK_STACK_SIZE          (2048)

#define     WSLEEP_TASK_STACK_SIZE          (2048)

/*****************************************************************************
  8 SCM RCV 的任务定义
*****************************************************************************/

#define     SCM_OM_CFG_TASK_STACK_SIZE      (8096)

#define     SCM_CBT_REQ_TASK_STACK_SIZE     (8096)

/*****************************************************************************
  9 CBT socket 的任务定义
*****************************************************************************/

#define     CBT_SOCKET_TASK_STACK_SIZE      (8096)


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

#endif /* end of __OM_SPECTASK_DEF_H__ */



