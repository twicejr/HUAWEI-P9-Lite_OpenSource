/******************************************************************************

                  版权所有 (C), 2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_OS_Sync.h
  版 本 号   : 初稿
  作    者   : d00173029
  生成日期   : 2014年06月26日
  最近修改   :
  功能描述   : 定义操作系统线程通信邮箱、信号量
  函数列表   :
  修改历史   :
  1.日    期   : 2014年06月28日
    作    者   : d00173029
    修改内容   : 建立文件

******************************************************************************/

#ifndef __BST_OS_SYNC_H__
#define __BST_OS_SYNC_H__


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "BST_Platform.h"
#include "BST_PAL_Sync.h"
#include "BST_LIB_List.h"

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack(4)
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define BST_OS_SYS_FOREVER              ( BST_PAL_SYS_FOREVER )
#define BST_OS_SYS_NOWAIT               BST_PAL_SYS_NOWAIT
#define BST_OS_SYS_TIMEOUT              ( 0xFFFFFFFFU )
#define BST_OS_SYS_IsSemValid(sem)      BST_PAL_IsSemInValid(sem)
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 枚举定义
*****************************************************************************/

/*****************************************************************************
  5 类/结构定义
*****************************************************************************/
typedef BST_OS_PAL_SEM_T                BST_OS_SEM_T;

typedef struct
{
    BST_OS_SEM_T                        stHandle;
#ifdef BST_OS_SIGNAL_COUNTER
    BST_UINT32                          ulCounter;
#endif
    BST_VOID                           *pvArg;
}BST_OS_SEM_STRU;

typedef struct
{
    BST_OS_SEM_STRU                    *hSem;
    LIST                                hList;
    BST_UINT32                          ulSize;
}BST_OS_MBX_T;

typedef struct
{
    NODE                                stNode;
    BST_VOID                           *ulContent;
}BST_OS_MAIL_T;

/*****************************************************************************
  6 UNION定义
*****************************************************************************/

/*****************************************************************************
  7 全局变量声明
*****************************************************************************/

/*****************************************************************************
  8 函数声明
*****************************************************************************/
BST_OS_SEM_STRU    *BST_OS_CreateSem(
    BST_VOID           *pvArg,
    BST_UINT32          ulInitCnt );
BST_UINT32          BST_OS_RecvSem(
    BST_OS_SEM_STRU    *pstSemHandle,
    BST_UINT32          ulTimeOut );

BST_ERR_ENUM_UINT8  BST_OS_SendSem(
    BST_OS_SEM_STRU    *pstSemHandle );

BST_ERR_ENUM_UINT8  BST_OS_DeleteSem(
    BST_OS_SEM_STRU    *pstSemHandle );

BST_OS_MBX_T       *BST_OS_CreateMbx(
    BST_VOID           *pvArg,
    BST_UINT32          ulSize );

BST_ERR_ENUM_UINT8  BST_OS_SendMail(
    BST_OS_MBX_T       *pstMbx,
    BST_VOID           *pMsg );

BST_UINT32          BST_OS_RecvMail(
    BST_OS_MBX_T       *pstMbx,
    BST_VOID          **pMsg,
    BST_UINT32          ulExTime );

BST_ERR_ENUM_UINT8  BST_OS_DeleteMbx(
    BST_OS_MBX_T       *pstMbx );

BST_UINT32          BST_OS_GetMailAmount(
    BST_OS_MBX_T       *pstMbx );

BST_UINT32          BST_OS_PeekMail(
    BST_OS_MBX_T       *pstMbx,
    BST_VOID          **pMsg );
/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack()
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(pop)
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif
