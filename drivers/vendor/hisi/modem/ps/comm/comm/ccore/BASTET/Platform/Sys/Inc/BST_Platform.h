/******************************************************************************

                  版权所有 (C), 2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_Platform.h
  版 本 号   : 初稿
  作    者   : d00173029
  生成日期   : 2014年07月01日
  最近修改   :
  功能描述   : 定义、统一引用平台相关处理
  函数列表   :
  修改历史   :
  1.日    期   : 2014年06月04日
    作    者   : d00173029
    修改内容   : 建立文件

******************************************************************************/

#ifndef  __BST_PLATFORM_H__
#define  __BST_PLATFORM_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "BST_Config.h"
#include "BST_Typedefine.h"
#include "BST_OS_Log.h"
#include "BST_SYS_MntnInterface.h"

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack(4)
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define BST_INVALID_SNID                ( 0xFFFFU )

#if (BST_OS_VER == BST_WIN32)
#define BST_OS_S_IN_MIN                 ( 1U )
#else
#define BST_OS_S_IN_MIN                 ( 60U )
#endif

#define BST_OS_MS_IN_S                  ( 1000U )
#define BST_OS_MAX_UINT32               ( 0xFFFFFFFF )
typedef BST_VOID (*BST_OS_THREAD_T)(BST_VOID *pvArg);
#define BST_SYS_SUPPORT_NONE            ( 0x00U )
#define BST_SYS_SUPPORT_TCP_SHORT       ( 0x01U )
#define BST_SYS_SUPPORT_TCP_SHORT_SSL   ( 0x02U )
#define BST_SYS_SUPPORT_TCP_LONG        ( 0x04U )
#define BST_SYS_SUPPORT_TCP_LONG_SSL    ( 0x08U )
#define BST_SYS_SUPPORT_UDP             ( 0x10U )
#define BST_SYS_SUPPORT_UDP_SSL         ( 0x20U )

#define BST_SetThreadInitFlag( ulFlag ) \
                                        {\
                                            g_BstThreadInitFlags |= (ulFlag);\
                                            BST_RLS_LOG1("Bastet Threads 0x%x Init Success", (ulFlag) );\
                                        }

#define BST_GetThreadInitFlag()         ( g_BstThreadInitFlags )
#define BST_ClrThreadInitFlag()         ( g_BstThreadInitFlags = BST_NONE_THERAD_FLAG )

/*定义BASTET处理事件*//*根据DOPRA手册，事件高16位为系统保留，用户使用低16位，OSA的使用待确定*/
#define  BST_CDS_EVENT_BASE             (0x00000000)
#define  BST_CDS_EVENT_RCV_DL_PROC      (BST_CDS_EVENT_BASE | 0x0001)   /*下行RCV触发事件*/


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 枚举定义
*****************************************************************************/

/*****************************************************************************
  6 UNION定义
*****************************************************************************/


/*****************************************************************************
  7 全局变量声明
*****************************************************************************/
extern BST_UINT32 g_BstThreadInitFlags;
/*****************************************************************************
  8 函数声明
*****************************************************************************/
BST_VOID BST_SYS_InitPlatform( BST_VOID );
BST_VOID BST_SYS_ApiSndEvtToBastet( BST_UINT32 ulEvent );
BST_BOOL BST_SYS_ApiGetSupported(BST_VOID);
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
