/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasUTRANCTRLFsmPlmnSelectionTbl.h
  版 本 号   : 初稿
  作    者   : w00176964
  生成日期   : 2012年08月4日
  最近修改   :
  功能描述   : NasUTRANCTRLFsmPlmnSelectionTbl.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年08月4日
    作    者   : w00176964
    修改内容   : 创建文件

******************************************************************************/
#ifndef _NAS_UTRANCTRL_FSM_PLMN_SELECTION_TBL_H_
#define _NAS_UTRANCTRL_FSM_PLMN_SELECTION_TBL_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#include  "vos.h"
#include  "PsTypeDef.h"
#include  "NasFsm.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  1 全局变量定义
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)

extern NAS_STA_STRU                            g_astNasUtranCtrlPlmnSelectionStaTbl[];


/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define NAS_UTRANCTRL_GetPlmnSelectionStaTbl()                   (g_astNasUtranCtrlPlmnSelectionStaTbl)


/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
 枚举名    : NAS_UTRANCTRL_PLMN_SELECTION_STA_ENUM_UINT32
 枚举说明  : UTRANCTRL PLMN SELECTION状态机状态枚举定义
 1.日    期   : 2011年8月4日
   作    者   : w00176964
   修改内容   : 新建
*****************************************************************************/
enum NAS_UTRANCTRL_PLMN_SELECTION_STA_ENUM
{
    NAS_UTRANCTRL_PLMN_SELECTION_STA_INIT,                                      /* 搜网状态机初始化状态 */

    NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_PLMN_STOP_CNF_SEARCH_TD,          /* 搜网状态机等待WAS停止搜网回复后去TD下搜网状态 */

    NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_PLMN_STOP_CNF_SEARCH_W,            /* 搜网状态机等待TDRRC停止搜网回后去W下搜网复状态 */

    NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF,                      /* 搜网状态机等待WAS挂起回复状态 */

    NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_SUSPEND_CNF,                    /* 搜网状态机等待TDRRC挂起回复状态 */

    NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_PLMN_SEARCH_CNF,                  /* 搜网状态机等待WAS搜网回复状态 */

    NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_PLMN_SEARCH_CNF,                /* 搜网状态机等待TDRRC搜网回复状态 */

    NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_PLMN_STOP_CNF,                    /* 搜网状态机等待WAS停止搜网回复状态 */

    NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_PLMN_STOP_CNF,                     /* 搜网状态机等待TDRRC停止搜网回复状态 */

    NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF_BACK_TD,              /* 搜网状态机等待回到TD时WAS的挂起回复状态 */

    NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_SUSPEND_CNF_BACK_W,                /* 搜网状态机等待回到W时TDRRC的挂起回复状态 */

    NAS_UTRANCTRL_PLMN_SELECTION_STA_BUTT
};
typedef VOS_UINT32  NAS_UTRANCTRL_PLMN_SELECTION_STA_ENUM_UINT32;

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

VOS_UINT32 NAS_UTRANCTRL_GetPlmnSelectionStaTblSize( VOS_VOID  );


NAS_FSM_DESC_STRU * NAS_UTRANCTRL_GetPlmnSelectionFsmDescAddr(VOS_VOID);
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

#endif /* end of NAS_UTRANCTRLMainFsmTbl.h */
