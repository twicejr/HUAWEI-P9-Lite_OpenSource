/******************************************************************************

                  版权所有(C), 2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BST_SRV_TaskMng.h
  版 本 号   : 初稿
  作    者   : d00173029
  生成日期   : 2014年4月16日
  最近修改   :
  功能描述   : 任务管理器头文件定义
  函数列表   :

  修改历史   :
  1.日    期   : 2014年04月16日
    作    者   : d00173029
    修改内容   : 创建文件

******************************************************************************/

#ifndef __BST_SEV_TASK_MANAGER_H__
#define __BST_SEV_TASK_MANAGER_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "BST_CORE_Task.h"
#include "BST_CORE_Regedit.h"
#include "BST_LIB_SnGenerator.h"
#include "BST_APP_Define.h"
#include "BST_OS_Thread.h"
#include "BST_OS_Sync.h"
#include "BST_DSPP_Define.h"

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack(4)
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define BST_SRV_SYS_THRD_ADDR           ( 0U )
#define BST_SRV_IP_THRD_ADDR            ( BST_SRV_SYS_THRD_ADDR+ BST_CFG_SYS_THRD_NUM )
#define BST_SRV_CHNL_THRD_ADDR          ( BST_SRV_IP_THRD_ADDR + BST_CFG_IP_THRD_NUM )
#define BST_SRV_RT_THRD_ADDR            ( BST_SRV_CHNL_THRD_ADDR + BST_CFG_CHNL_THRD_NUM )
#define BST_SRV_NRT_THRD_ADDR           ( BST_SRV_RT_THRD_ADDR + BST_CFG_RT_THRD_NUM )

#define BST_SRV_APP_THRD_ADDR           ( BST_SRV_RT_THRD_ADDR )

#define BST_SRV_APP_THRD_AMOUNT         ( BST_CFG_RT_THRD_NUM + BST_CFG_NRT_THRD_NUM )

#define BST_SRV_THRD_AMOUNT             ( BST_CFG_SYS_THRD_NUM  \
                                        + BST_CFG_IP_THRD_NUM   \
                                        + BST_CFG_CHNL_THRD_NUM \
                                        + BST_CFG_RT_THRD_NUM   \
                                        + BST_CFG_NRT_THRD_NUM )

#define BST_SRV_APP_TYPE_RT             ( 0U )

#define BST_SRV_APP_TYPE_NRT            ( 1U )

#define BST_SRV_APP_NAME_LEN            ( 25U )
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 结构定义
*****************************************************************************/
typedef struct{
    NODE            node;
    BST_PROCID_T    usProcId;
    BST_TASKID_T    usTaskId;
    BST_CTask      *pcTask;
}BST_SRV_TASK_ITEM_STRU;

typedef struct
{
    BST_OS_MBX_T           *pMsgHandle;
    LIST                    lstTaskTree;
}BST_SRV_THREAD_ITEM_STRU;

/*****************************************************************************
  5 类定义
*****************************************************************************/
class BST_SRV_CTaskMng
{
BST_PUBLIC:
    static BST_SRV_CTaskMng *GetInstance( BST_VOID );

    BST_DSPP_OFSTADDR_T     Assign(
        BST_DSPP_OBJTADDR_T     usObjAddr,
        BST_DSPP_OFSTADDR_T     usOfstAddr,
        BST_OS_MBX_T          **ppstMbox );

    BST_ERR_ENUM_UINT8      Remove(
        BST_DSPP_OBJTADDR_T         usObjAddr,
        BST_DSPP_OFSTADDR_T         usOfstAddr );

    BST_ERR_ENUM_UINT8      RemoveAll( BST_VOID );

    BST_ERR_ENUM_UINT8      Start(
        BST_DSPP_OBJTADDR_T         usObjAddr,
        BST_DSPP_OFSTADDR_T         usOfstAddr );

    BST_ERR_ENUM_UINT8      StartAll( BST_VOID );

    BST_ERR_ENUM_UINT8      Stop(
        BST_DSPP_OBJTADDR_T     usObjAddr,
        BST_DSPP_OFSTADDR_T     usOfstAddr );

    BST_ERR_ENUM_UINT8      StopAll( BST_VOID );

    BST_ERR_ENUM_UINT8      Config(
        BST_DSPP_OBJTADDR_T         usObjAddr,
        BST_DSPP_OFSTADDR_T         usOfstAddr,
        BST_CORE_PID_ENUM_UINT16    enPid,
        BST_DSPP_CMDLEN_T           usLength,
        BST_VOID                   *pData );

    BST_UINT16              Inquire(
        BST_DSPP_OBJTADDR_T         usObjAddr,
        BST_DSPP_OFSTADDR_T         usOfstAddr,
        BST_CORE_PID_ENUM_UINT16    enPid,
        BST_DSPP_CMDLEN_T           usLength,
        BST_VOID                   *pData );

    BST_UINT16              GetLen(
        BST_DSPP_OBJTADDR_T         usObjAddr,
        BST_DSPP_OFSTADDR_T         usOfstAddr,
        BST_CORE_PID_ENUM_UINT16    enPid );

    BST_ERR_ENUM_UINT8      Create(
        BST_DSPP_OBJTADDR_T         usObjAddr,
        BST_DSPP_OFSTADDR_T         usOfstAddr );

   BST_UINT16              GetAppTaskTotle(
        BST_VOID );

BST_PRIVATE:
                                        BST_SRV_CTaskMng( BST_VOID );
    virtual                            ~BST_SRV_CTaskMng( BST_VOID );

    BST_OS_MBX_T                       *AssignToThread(
        BST_PROCID_T                usProcId,
        BST_TASKID_T                usTaskId,
        BST_UINT32                  ulTaskType );

    BST_Lib_CSnGenrator<BST_TASKID_T>  *m_apcTaskIdGnrtor[BST_OBJ_TYPE_MAX];
    BST_CORE_CRegedit                  *m_pcRegedit;
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
extern "C" BST_OS_MBX_T   *BST_SRV_GetSysMsgHandle( BST_VOID );

BST_OS_MBX_T   *BST_SRV_GetTaskMsgHandle(
    BST_PROCID_T    usProcId,
    BST_TASKID_T    usTaskId );

BST_OS_MBX_T   *BST_SRV_GetChnlCtrlHandle(
    BST_UINT32      ulThdNumber );

/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack()
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(pop)
#endif


#endif
