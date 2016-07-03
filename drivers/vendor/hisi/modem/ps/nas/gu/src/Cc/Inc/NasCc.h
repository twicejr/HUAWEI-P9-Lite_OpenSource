
#ifndef __NASCC_H__
#define __NASCC_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "vos.h"
#include "AtMnInterface.h"

/*****************************************************************************
  2 枚举定义
*****************************************************************************/



/*****************************************************************************
  3 类型定义
*****************************************************************************/

/*****************************************************************************
 3 接口函数声明
*****************************************************************************/

VOS_UINT32  NAS_CC_PidInit(
    enum VOS_INIT_PHASE_DEFINE          enInitPhase
);


VOS_UINT32  WuepsSsPidInit(
    enum VOS_INIT_PHASE_DEFINE          enInitPhase
);

VOS_UINT32  WuepsTcPidInit(
    enum VOS_INIT_PHASE_DEFINE          enInitPhase
);

VOS_UINT32  WuepsSmsPidInit(
    enum VOS_INIT_PHASE_DEFINE          enInitPhase
);



VOS_VOID  NAS_CC_MsgRoute(
    struct MsgCB* pMsg
);

VOS_VOID NAS_CC_ProcessSpecTypeBufferMsg(VOS_UINT32 ulEventType);


extern VOS_VOID Ss_TaskEntry_T( struct MsgCB* pMsg );

extern VOS_VOID Tc_TaskEntry  (struct MsgCB * pRcvMsg);

extern VOS_VOID SMS_TaskEntry  (struct MsgCB * pRcvMsg);


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

#endif /* __NASCC_H__ */

