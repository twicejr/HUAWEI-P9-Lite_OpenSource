/******************************************************************************

                  版权所有 (C), 2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_SRV_Event.h
  版 本 号   : 初稿
  作    者   : d00173029
  生成日期   : 2014年7月4日
  最近修改   :
  功能描述   : 服务程序事件处理定义
  函数列表   :
  修改历史   :
  1.日    期   : 2014年7月4日
    作    者   : d00173029
    修改内容   : 创建文件

******************************************************************************/

#ifndef __BST_SRV_EVENT_H__
#define __BST_SRV_EVENT_H__
/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "BST_Platform.h"
#include "BST_SRV_Define.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack(4)
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 枚举定义
*****************************************************************************/

/*****************************************************************************
  5 类/结构定义
*****************************************************************************/

/*****************************************************************************
  6 UNION定义
*****************************************************************************/

/*****************************************************************************
  7 全局变量声明
*****************************************************************************/

/*****************************************************************************
  8 函数声明
*****************************************************************************/
BST_UINT32  BST_SRV_ApiSendAsEvent(
    BST_VOID               *pcInAsRcver,
    BST_AS_EVT_ENUM_UINT32  enAsEvent,
    BST_UINT32              ulLength,
    BST_VOID               *pvData );

BST_UINT32 BST_SRV_ApiSendLwipAsEvent(
    BST_VOID               *pcInAsRcver,
    BST_AS_EVT_ENUM_UINT32  enAsEvent,
    BST_UINT32              ulLength,
    BST_VOID               *pvData );

BST_UINT32  BST_SRV_ApiSendPTaskEvent(
    BST_VOID               *pvTask,
    BST_UINT16              enComdId,
    BST_UINT16              usContnt );

BST_UINT32  BST_SRV_ApiSendAcomRxEvent(
    BST_UINT32              ulLength,
    BST_UINT8              *pucData );

BST_UINT32  BST_SRV_ApiSendExpiredEvent(
    BST_VOID               *pstRcvHandle,
    BST_UINT32              ulTimerId );

BST_UINT32  BST_SRV_ApiSendTcpIpEvent(
    BST_VOID               *pstRcver,
    BST_VOID               *pstEvent );

BST_UINT32 BST_SRV_ApiSendDsppEvent(
    BST_UINT32             ulMsgId,
    BST_UINT32             ulApVer,
    BST_UINT32             const ulBufLen,
    BST_VOID              *const pstHeadInfo,
    BST_VOID              *pstRcvHandle );

BST_VOID    BST_SRV_ProcSysEvent(
    BST_EVT_HEAD_STRU      *pstEvent );

BST_VOID    BST_SRV_ProcAppEvent(
    BST_EVT_HEAD_STRU      *pstEvent );

BST_VOID BST_SRV_ProcChnlCtrEvent(
    BST_EVT_HEAD_STRU      *pstEvent );

BST_VOID BST_SRV_EvtProcLwipExpired(
    BST_VOID               *pstLwipMsg );

BST_VOID BST_SRV_EvtProcLwipAsEvent(
    BST_VOID               *pstLwipMsg );

BST_VOID BST_SRV_InitInstance( BST_VOID );

/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack()
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(pop)
#endif

#ifdef __cplusplus
#if    __cplusplus
           }
#endif
#endif


#endif
