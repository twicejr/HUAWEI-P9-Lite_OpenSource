

#ifndef _TAFAGENTOAMINTERFACE_H_
#define _TAFAGENTOAMINTERFACE_H_

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "vos.h"

#pragma pack(4)

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/



/*****************************************************************************
  3 函数实现
*****************************************************************************/

extern VOS_UINT32  TAF_AGENT_PidInit(enum VOS_INIT_PHASE_DEFINE enPhase);


extern VOS_VOID TAF_AGENT_ProcMsg(MsgBlock* pstMsg);


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

#endif

