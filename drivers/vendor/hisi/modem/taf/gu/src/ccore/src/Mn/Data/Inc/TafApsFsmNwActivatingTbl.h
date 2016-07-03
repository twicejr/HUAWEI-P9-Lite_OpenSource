

#ifndef __TAF_APS_FSM_NWACTIVATING_TBL_H__
#define __TAF_APS_FSM_NWACTIVATING_TBL_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "TafFsm.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
extern TAF_STA_STRU                             g_astTafApsNwActivatingStaTbl[];
#define TAF_APS_GetNwActivatingStaTbl()         (g_astTafApsNwActivatingStaTbl)


/*****************************************************************************
  3 枚举定义
*****************************************************************************/

enum TAF_APS_NW_ACTIVATING_SUBSTA_ENUM
{
    TAF_APS_NW_ACTIVATING_SUBSTA_INIT,                                          /* NW ACTIVATING状态机的初始状态 */
    TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_APP_ANSWER,                               /* 网络发起PDP激活请求，等待APP响应中 */
    TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF,                          /* 网络发起PDP激活请求，APP已响应，等待SM的回复 */
    TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_ESM_CGANS_CNF,                            /* 网络发起PDP激活请求，APP已响应，等待ESM的回复 */
    TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP,                       /* APS向SNDCP发起了激活SNDCP请求，等待SNDCP响应 */
    TAF_APS_NW_ACTIVATING_SUBSTA_BUTT
} ;
typedef VOS_UINT32 TAF_APS_NW_ACTIVATING_SUBSTA_ENUM_UINT32;


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
VOS_UINT32 TAF_APS_GetNwActivatingStaTblSize( VOS_VOID );
TAF_FSM_DESC_STRU * TAF_APS_GetNwActivatingFsmDescAddr( VOS_VOID );








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

#endif /* end of TafApsFsmNwActivating.h */
