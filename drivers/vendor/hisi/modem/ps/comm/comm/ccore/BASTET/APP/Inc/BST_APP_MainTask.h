/******************************************************************************

                  版权所有 (C), 2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : SysMainProc.h
  版 本 号   : 初稿
  作    者   : d00173029
  生成日期   : 2014年4月16日
  最近修改   :
  功能描述   : Bastet 方案的主控制类
  函数列表   :
  修改历史   :
  1.日    期   : 2014年04月16日
    作    者   : d00173029
    修改内容   : 创建文件

******************************************************************************/

#ifndef __BST_APP_MAINTASK_H__
#define __BST_APP_MAINTASK_H__
/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "BST_SRV_AsEvnt.h"
#include "BST_DSPP_Report.h"
#include "BST_CORE_NPTask.h"
#include "BST_DRV_Net.h"
#include "BST_SRV_Define.h"

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack(4)
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define BST_APP_TASK_TRFCFLOW_COUNT_SIZE \
                                        ( BST_OS_SIZEOF( BST_UINT16 ) )

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
    BST_PROCID_T                usProcId;
    BST_TASKID_T                usTaskId;
    BST_IP_TRAFFIC_FLOW_STRU    strFlowInfo;
}BST_APP_TASK_TRFCFLOW_STRU;

typedef struct
{
    NODE                        node;
    BST_CORE_CNPTask           *pcNpTask;
}BST_APP_NPTASK_NODE_STRU;


class BST_APP_CMainTask :
    BST_PUBLIC BST_CTask, BST_PUBLIC BST_CORE_CAPACallBack, BST_PUBLIC BST_SRV_CAsRcver
{
BST_PUBLIC:
    static BST_APP_CMainTask   *GetInstance( BST_VOID );

    BST_VOID    Attach( BST_CORE_CNPTask *pC_NPTask );

    BST_VOID    Detach( BST_CORE_CNPTask *pC_NPTask );

    BST_ERR_ENUM_UINT8  TrafficOverFlow( BST_UINT32 ulRealFlowValue );

    BST_VOID    Entry ( BST_VOID );
BST_PRIVATE:
                BST_APP_CMainTask(
        BST_PROCID_T                usInProcID,
        BST_TASKID_T                usInTaskID );
               ~BST_APP_CMainTask( BST_VOID );

    BST_VOID    AsEventCallback(
        BST_AS_EVT_ENUM_UINT32        enEvent,
        BST_UINT32                    ulLength,
        BST_VOID                     *pData );

    BST_UINT16  Inquired(
        BST_CORE_PID_ENUM_UINT16      enParamId,
        BST_UINT16                    usDataSize,
        BST_VOID                     *const pData );

    BST_ERR_ENUM_UINT8  Configed(
        BST_CORE_PID_ENUM_UINT16      enParamId,
        BST_UINT16                    usLen,
        const BST_VOID               *const pData,
        BST_UINT8                   **pucNewAddr );

    BST_ERR_ENUM_UINT8  SaveLocalIp( NET_DRV_LOCAL_IP_INFO_STRU   *pstLocalMsg );

    BST_ERR_ENUM_UINT8  ConfigNetState( BST_NET_STATE_STRU *pstNetState );

    BST_VOID    Start( BST_VOID );

    BST_VOID    Stop( BST_VOID );

    BST_VOID    Remove( BST_VOID );

    BST_UINT16  GetTotalTrFlow(
        BST_UINT8           pucBuf[],
        BST_UINT16          usBufLen );

    LIST                                m_stNpTaskList;
    NET_DRV_LOCAL_IP_INFO_STRU          m_LocalIpInfo;
    BST_UINT32                          m_ulApSleepState;
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
