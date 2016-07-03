


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#ifndef __NASMMCFSMSWITCHON_H__
#define __NASMMCFSMSWITCHON_H__

#include  "vos.h"
#include "NasMmlCtx.h"






#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)


#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
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


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/

VOS_UINT32 NAS_UTRANCTRL_RcvWasStartCnf_SwitchOn_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 NAS_UTRANCTRL_RcvTdStartCnf_SwitchOn_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32  NAS_UTRANCTRL_RcvWasStartCnf_SwitchOn_WaitWasStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  NAS_UTRANCTRL_RcvTdStartCnf_SwitchOn_WaitWasStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_UTRANCTRL_RcvTiWaitWasStartCnfExpired_SwitchOn_WaitWasStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_UTRANCTRL_RcvTdStartCnf_SwitchOn_WaitTdStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_UTRANCTRL_RcvWasStartCnf_SwitchOn_WaitTdStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  NAS_UTRANCTRL_RcvTiWaitTdStartCnfExpired_SwitchOn_WaitTdStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#endif  /* end of #if (FEATURE_ON == FEATURE_UE_MODE_TDS) */


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

