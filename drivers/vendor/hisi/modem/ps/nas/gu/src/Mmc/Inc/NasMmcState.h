/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcState.h
  版 本 号   : 初稿
  作    者   : zhoujun /40661
  生成日期   : 2010年11月12日
  最近修改   :
  功能描述   : NasFsm.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2010年11月12日
    作    者   : zhoujun /40661
    修改内容   : 创建文件

******************************************************************************/
#ifndef _NAS_MMC_STATE_H_
#define _NAS_MMC_STATE_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#include  "vos.h"

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
enum NAS_MMC_MAIN_STATE_ENUM
{
    NAS_MMC_SWITCH_ON_END              = 0 ,                                    /* 上电或重启时，在此状态下等待ATTACH要求   */
    NAS_MMC_TRYING_PLMN                    ,                                    /* 尝试注册状态                             */
    NAS_MMC_WAIT_FOR_USER_PLMN_LIST        ,                                    /* 等待搜索PLMN list结果                    */
    NAS_MMC_WAIT_FOR_AS_RESULT             ,                                    /* 等待指定搜索PLMN或suitable cell结果      */
    NAS_MMC_ON_PLMN                        ,                                    /* 指示PS域或CS域至少有一个成功注册         */
    NAS_MMC_LIMIT_SERVICE                  ,                                    /* 此时MS只能提供受限服务                   */
    NAS_MMC_WAIT_FOR_PLMNS                 ,                                    /* 覆盖区丢失后进入此状态                   */
    NAS_MMC_NOT_ON_PLMN                    ,                                    /* 仅用于手动模式，等待用户选择PLMN         */
    NAS_MMC_NULL_STATE                     ,                                    /* MMC关机时进入次状态                      */
    NAS_MMC_SWITCH_ON_INIT                 ,                                    /* 在此状态下初始化MM层和AS层               */
    NAS_MMC_TC_STATE                       ,                                    /* TC测试时迁入此状态                       */
    NAS_MMC_SUSPEND                        ,                                    /* MMC当前在挂起状态                       */
    NAS_MMC_MAIN_STATE_BG                  ,                                    /* MMC当前在BG搜索过程中                       */
    NAS_MMC_WAIT_FOR_INTERNAL_PLMN_LIST    ,                                    /* 等待搜索PLMN list结果                    */
    NAS_MMC_STATE_PRE_PROCESS              ,                                    /* 不进入状态机的处理 */
    NAS_MMC_MAIN_STATE_INVALID_STATE
};
typedef VOS_UINT8  NAS_MMC_MAIN_STATE_ENUM_U8;

enum NAS_MMC_SUB_STATE_ENUM
{
    /* 空状态 */
    NAS_MMC_SUB_STATE_NULL_STATE            = 0,

    /* BG搜索子状态 */
    NAS_MMC_SUB_STATE_BG_WAIT_BG_RESULT     ,                                   /* 等待BG搜索结果 */
    NAS_MMC_SUB_STATE_BG_WAIT_FOR_SPEC_RESULT,                                  /* 等到快速指定PLMN搜索结果 */
    NAS_MMC_SUB_STATE_BG_TRYING_PLMN,                                           /* 正在进行注册过程中 */
    NAS_MMC_SUB_STATE_BG_SUSPEND,                                               /* 正在挂起过程中 */
    NAS_MMC_SUB_STATE_BG_STOP_PLMN_SEARCH,                                      /* 等待接入层的停止停止快速指定搜索的确认 */
    NAS_MMC_SUB_STATE_BG_STOP_BG_SEARCH,                                        /* 等待接入层的停止BG搜索的确认 */
    NAS_MMC_SUB_STATE_BG_WAIT_RRC_REL,                                          /* 等待链接释放 */

    /* 用户列表搜索子状态 */
    NAS_MMC_SUB_STATE_USER_LIST_ALL             ,                               /* 收到系统消息后下发列表搜网在此状态 */
    NAS_MMC_SUB_STATE_USER_LIST_I,                                              /* 在当前模式下列表搜网 */
    NAS_MMC_SUB_STATE_USER_LIST_II,                                             /* 在另外一个模式下列表搜网 */
    NAS_MMC_SUB_STATE_USER_LIST_SUSPEND_FOR_LIST    ,                           /* 挂起接入层到另外一个模式下列表搜网 */
    NAS_MMC_SUB_STATE_USER_LIST_STOP,                                           /* 通知低层列表搜网停止 */

    /* MMC内部列表搜索子状态 */
    NAS_MMC_SUB_STATE_INTERNAL_LIST_ALL,                                        /* 内部列表搜网 */
    NAS_MMC_SUB_STATE_INTERNAL_LIST_STOP                                       /* 停止内部列表搜网 */
};
typedef VOS_UINT16 NAS_MMC_SUB_STATE_ENUM_U16;




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

VOS_UINT32 NAS_MMC_FsmReg( VOS_VOID  );







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

#endif /* end of NasMmcState.h */
