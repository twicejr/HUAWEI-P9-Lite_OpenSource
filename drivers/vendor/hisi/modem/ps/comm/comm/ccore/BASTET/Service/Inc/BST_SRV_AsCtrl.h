/******************************************************************************

                  版权所有 (C), 2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_SRV_AsCtrl.h
  版 本 号   : 初稿
  作    者   : d00173029
  生成日期   : 2014年07月01日
  最近修改   :
  功能描述   : 接入层控制相关处理定义
  函数列表   :
  修改历史   :
  1.日    期   : 2014年07月01日
    作    者   : d00173029
    修改内容   : 建立文件

******************************************************************************/
#ifndef __BST_SRV_CTRL_H__
#define __BST_SRV_CTRL_H__
/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "BST_SRV_AsEvnt.h"
#include "BST_OS_Thread.h"
#include "BST_OS_Timer.h"
#include "BST_LIB_List.h"

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack(4)
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define BST_SRV_MakeTaskVid(pid, tid)   ( ( ((BST_UINT32)(pid))<<16 ) | (tid) )
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 枚举定义
*****************************************************************************/

/*****************************************************************************
  5 类/结构定义
*****************************************************************************/
typedef struct
{
    NODE        node;
    BST_UINT32  ulName;
}BST_SRV_VOTEID_STRU;

typedef BST_UINT32                      BST_UINT32;

class BST_SRV_CAsCtrl
    : BST_PUBLIC BST_SRV_CAsRcver, BST_PRIVATE BST_OS_CTimerCb
{
BST_PUBLIC:
    static BST_SRV_CAsCtrl             *GetInstance     ( BST_VOID );
    BST_VOID                            UsingRrcVote    ( BST_UINT32 ulVid );
    BST_VOID                            UsingRrcDeVote  ( BST_UINT32 ulVid );
    BST_BOOL                            Control         (
        BST_DRV_CMD_ENUM_UINT32     enCmd,
        BST_VOID                   *pvData );
BST_PRIVATE:
                                        BST_SRV_CAsCtrl ( BST_VOID );
    virtual                            ~BST_SRV_CAsCtrl ( BST_VOID );
    BST_VOID                            AsEventCallback (
        BST_AS_EVT_ENUM_UINT32      enEvent,
        BST_UINT32                  ulLength,
        BST_VOID                   *pvData);
    BST_VOID                            TimerExpired    (
        BST_OS_TIMERID_T            ulId,
        BST_VOID                   *pvPara );

    BST_VOID                            ProcRrcEvent(
        BST_UINT32                  ulLength,
        BST_VOID                   *pvData );

    BST_VOID ProcDataTrs( BST_VOID );

    LIST                                m_stVoteList;
    BST_OS_TIMERID_T                    m_ulFdTimerId;
    BST_OS_TIMERID_T                    m_ulReportTimerId;
    BST_BOOL                            m_VoteRrcEnableFlag;
    BST_AS_RRC_STATE_ENUM_UINT32        m_ulRrcState;
};
/*****************************************************************************
  6 UNION定义
*****************************************************************************/

/*****************************************************************************
  7 全局变量声明
*****************************************************************************/

/*****************************************************************************
  8 函数声明
*****************************************************************************/

/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack()
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(pop)
#endif

#endif
