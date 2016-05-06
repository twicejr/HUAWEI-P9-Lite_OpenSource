/******************************************************************************

                  版权所有 (C), 2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_SysMntnInterface.h
  版 本 号   : 初稿
  作    者   : s00211350
  生成日期   : 2014年09月16日
  最近修改   :
  功能描述   : Bastet可维可测对外处理公共接口
  函数列表   :

  修改历史   :
  1.日    期   : 2014年09月16日
    作    者   : s00211350
    修改内容   : 创建文件

******************************************************************************/

#ifndef __BST_SYSMNTN_ITF_H__
#define __BST_SYSMNTN_ITF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "BST_Typedefine.h"

#if (BST_OS_VER != BST_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define BST_DBG_INITIAL()   BST_SYS_MntnInit()

#define BST_DBG_CONFIG_LOCAL_IP( aucLocalIp, usBufLen ) \
    BST_SYS_MntnCofigLoacalIpAddress( (BST_UINT8 *)aucLocalIp,\
                                      (BST_UINT16)usBufLen )

#define BST_DBG_ADD_TASK( usType, usTaskId )    \
    BST_SYS_MntnAddTask( (BST_UINT16)usType,    \
                         (BST_UINT16)usTaskId )

#define BST_DBG_UPDATE_STATE( usType, usTaskId, usState )   \
    BST_SYS_MntnUpdateState( (BST_UINT16)usType,            \
                             (BST_UINT16)usTaskId,          \
                             (BST_UINT16)usState )

#define BST_DBG_UPDATE_IP_INFO( usType, usTaskId, pstIpInfo )   \
    BST_SYS_MntnUpdateIpInfo( (BST_UINT16)usType,               \
                              (BST_UINT16)usTaskId,             \
                              pstIpInfo )

#define BST_DBG_UPDATE_CYC_LEN( usType, usTaskId, usCycleLen )  \
    BST_SYS_MntnUpdateCycleLen( (BST_UINT16)usType,             \
                                (BST_UINT16)usTaskId,           \
                                (BST_UINT16)usCycleLen )

#define BST_DBG_UPDATE_SUC_NUM( usType, usTaskId )      \
    BST_SYS_MntnUpdateSuccNum( (BST_UINT16)usType,      \
                               (BST_UINT16)usTaskId )

#define BST_DBG_UPDATE_ERR_NUM( usType, usTaskId )      \
    BST_SYS_MntnUpdateErrorNum( (BST_UINT16)usType,     \
                                (BST_UINT16)usTaskId )

#define BST_DBG_UPDATE_TX_FLOW( usLocalPort,ulTxFlow )  \
    BST_SYS_MntnUpdateTxFlow( (BST_UINT16)usLocalPort,  \
                              (BST_UINT32)ulTxFlow )

#define BST_DBG_UPDATE_RX_FLOW( usLocalPort,ulRxFlow )  \
    BST_SYS_MntnUpdateRxFlow( (BST_UINT16)usLocalPort,  \
                              (BST_UINT32)ulRxFlow )

#define BST_DBG_RMV_TASK( usType, usTaskId )    \
    BST_SYS_MntnRemoveTask( (BST_UINT16)usType, \
                            (BST_UINT16)usTaskId )

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 枚举定义
*****************************************************************************/

/*****************************************************************************
  5 STRUCT定义
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
BST_VOID BST_SYS_MntnInit( BST_VOID );

BST_VOID BST_SYS_MntnCofigLoacalIpAddress(
    BST_UINT8  *aucLocalIp,
    BST_UINT16  usBufLen );

BST_VOID BST_SYS_MntnAddTask(
    BST_UINT16  usType,
    BST_UINT16  usTaskId );

BST_VOID BST_SYS_MntnUpdateState(
    BST_UINT16  usType,
    BST_UINT16  usTaskId,
    BST_UINT16  usState );

BST_VOID BST_SYS_MntnUpdateIpInfo(
    BST_UINT16  usType,
    BST_UINT16  usTaskId,
    BST_VOID   *pstIpInfo );

BST_VOID BST_SYS_MntnUpdateCycleLen(
    BST_UINT16  usType,
    BST_UINT16  usTaskId,
    BST_UINT16  usCycleLen );

BST_VOID BST_SYS_MntnUpdateSuccNum(
    BST_UINT16  usType,
    BST_UINT16  usTaskId );

BST_VOID BST_SYS_MntnUpdateErrorNum(
    BST_UINT16  usType,
    BST_UINT16  usTaskId );

BST_VOID BST_SYS_MntnUpdateTxFlow(
    BST_UINT16  usLocalPort,
    BST_UINT32  ulTxFlow );

BST_VOID BST_SYS_MntnUpdateRxFlow(
    BST_UINT16  usLocalPort,
    BST_UINT32  ulRxFlow );

BST_VOID BST_SYS_MntnRemoveTask(
    BST_UINT16  usType,
    BST_UINT16  usTaskId );

/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

#if (BST_OS_VER != BST_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

