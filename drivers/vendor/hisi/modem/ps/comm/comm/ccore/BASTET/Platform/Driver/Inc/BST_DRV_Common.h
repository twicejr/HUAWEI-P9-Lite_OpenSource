/******************************************************************************

                  版权所有 (C), 2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_DRV_TEMPLATE.h
  版 本 号   : 初稿
  作    者   : d00173029
  生成日期   : 2014年06月26日
  最近修改   :
  功能描述   : 差异化平台驱动模版
  函数列表   :
  修改历史   :
  1.日    期   : 2014年06月26日
    作    者   : d00173029
    修改内容   : 建立文件

******************************************************************************/

#ifndef __BST_DRV_TEMPLATE_H__
#define __BST_DRV_TEMPLATE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "BST_Platform.h"

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack(4)
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/
typedef BST_ERR_ENUM_UINT8  (*BST_DRV_INIT_T)   ( BST_VOID    *pvArg );
typedef BST_ERR_ENUM_UINT8  (*BST_DRV_WRITE_T)  ( BST_UINT32   ulLength,
                                                  BST_UINT8   *pucData );
typedef BST_UINT32          (*BST_DRV_READ_T)   ( BST_UINT32   ulLength,
                                                  BST_UINT8   *pucData );
typedef BST_ERR_ENUM_UINT8  (*BST_DRV_IOCTRL_T) ( BST_UINT32   ulCmd,
                                                  BST_VOID    *pvData );

#define BST_DRV_IsDeviceInited( pstDevice )     ( BST_TRUE == (pstDevice)->ulIsInited )
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 枚举定义
*****************************************************************************/
enum BST_DRV_TYPE_ENUM
{
    BST_DRV_TYPE_NETDEVICE              = 1,
    BST_DRV_TYPE_RADIO,
    BST_DRV_TYPE_ACOM,
    BST_DRV_TYPE_BUTT
};
typedef BST_UINT8                       BST_DRV_TYPE_ENUM_UINT8;

#define BST_DRV_CMD_LOCAL_ADDR          ( 1U )
#define BST_DRV_CMD_RESET               ( 2U )
#define BST_DRV_CMD_RESUME_TO_AP        ( 3U )
#define BST_DRV_CMD_SET_BEARER          ( 4U )
#define BST_DRV_CMD_NET_DOWN            ( 5U )
#define BST_DRV_CMD_NET_PKT_MODE        ( 6U )
#define BST_DRV_CMD_FREE_PACKET_ITEM    ( 7U )
#define BST_DRV_CMD_RELEASE_RRC         ( 8U )
#define BST_DRV_CMD_SET_NET_TIMESTAMP   ( 9U )
#define BST_DRV_CMD_GET_NET_TIMESTAMP   ( 10U )
#define BST_DRV_CMD_GET_AS_STATE        ( 11U )
#define BST_DRV_CMD_SET_RRC_STATE       ( 12U )
#define BST_DRV_CMD_SET_REPORT_FLAG     ( 13U )
#define BST_DRV_CMD_GET_REPORT_FLAG     ( 14U )
#define BST_DRV_CMD_GET_NET_STATE       ( 15U )
#define BST_DRV_CMD_SET_TRFC_FLOW_LMT   ( 16U )
#define BST_DRV_CMD_GET_RAT_MODE        ( 17U )
#define BST_DRV_CMD_SET_TX_ENABLE       ( 18U )
#define BST_DRV_CMD_SET_RX_ENABLE       ( 19U )
#define BST_DRV_CMD_SET_MODEM_RABID     ( 20U )
#define BST_DRV_CMD_NET_UNKOWN          ( 21U )
#define BST_DRV_CMD_HPR_DATA_FINISH     ( 22U )
#define BST_DRV_CMD_GET_CONGESTION      ( 23U )
#define BST_DRV_CMD_BUTT                ( 24U )

typedef BST_UINT32                      BST_DRV_CMD_ENUM_UINT32;
/*****************************************************************************
  5 类/结构定义
*****************************************************************************/
typedef struct{
    BST_DRV_INIT_T                      pfInit;
    BST_DRV_WRITE_T                     pfWrite;
    BST_DRV_READ_T                      pfRead;
    BST_DRV_IOCTRL_T                    pfIoCtrl;
    BST_UINT32                          ulIsInited;
}BST_DRV_STRU;
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


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif
