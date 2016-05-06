/*****************************************************************************/
/*                                                                           */
/*                Copyright 1999 - 2003, Huawei Tech. Co., Ltd.              */
/*                           ALL RIGHTS RESERVED                             */
/*                                                                           */
/* FileName: nucleus_task.c                                                  */
/*                                                                           */
/* Author: Xu Cheng                                                          */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date: 2008-03                                                             */
/*                                                                           */
/* Description: implement nuclesu task                                       */
/*                                                                           */
/* Others:                                                                   */
/*                                                                           */
/* History:                                                                  */
/* 1. Date:                                                                  */
/*    Author:                                                                */
/*    Modification: Create this file                                         */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#include "vos_config.h"
#include "v_typdef.h"
#include "v_task.h"
#include "stdlib.h"
#include "stdio.h"
#include "v_IO.h"
#include "v_int.h"
#include "vos_Id.h"
#include "v_sem.h"


#if (VOS_NUCLEUS== VOS_OS_VER)


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_V_NUCLEUS_TASK_C


typedef struct
{
    int                 Flag;
    int                 Tid;/* task ID */
    VOS_TASK_ENTRY_TYPE Function;/* the entry of task */
    VOS_UINT32          Priority;
    VOS_UINT32          StackSize;
    VOS_UINT32          Args[VOS_TARG_NUM];/* the argument of the entry */
    VOS_CHAR            Name[VOS_MAX_LENGTH_TASK_NAME];
    VOS_UINT32          ulEventIsCreate;/* event create or not */
    VOS_UINT32          ulEvents;/* current event */
    VOS_UINT32          ulExpects;/* expected event */
    VOS_UINT32          ulReceives;/* have been received event */
    VOS_UINT32          ulFlags;/* event mode */
    VOS_UINT32          ulFid;/* belong to a FID or not */
    NU_TASK             NuTid;/* maped nuclesu ID */
} VOS_TASK_CONTROL_BLOCK;

/* the number of task's control block */
VOS_UINT32              vos_TaskCtrlBlkNumber;

/* the start address of task's control block */
VOS_TASK_CONTROL_BLOCK *vos_TaskCtrlBlk;

/* supported by lower software begin */
extern VOS_VOID *NU_StackMalloc(VOS_UINT32 size);

extern VOS_VOID NU_StackFree(VOS_VOID *ptr);
/* supported by lower software end */

#define VOS_TASK_CTRL_BUF_SIZE (sizeof(VOS_TASK_CONTROL_BLOCK)*VOS_MAX_TASK_NUMBER)

VOS_CHAR g_acVosTaskCtrlBuf[VOS_TASK_CTRL_BUF_SIZE];

/*****************************************************************************
 Function   : VOS_TaskCtrlBlkInit
 Description: Init task's control block
 Input      : ulTaskCtrlBlkNumber -- number
 Return     : None.
 Other      :
 *****************************************************************************/
VOS_VOID VOS_TaskCtrlBlkInit(VOS_VOID)
{
    int i;

    vos_TaskCtrlBlkNumber = VOS_MAX_TASK_NUMBER;

    vos_TaskCtrlBlk = (VOS_TASK_CONTROL_BLOCK*)g_acVosTaskCtrlBuf;

    for(i=0; i<(int)vos_TaskCtrlBlkNumber; i++)
    {
        vos_TaskCtrlBlk[i].Flag       = VOS_TASK_CTRL_BLK_IDLE;
        vos_TaskCtrlBlk[i].Tid        = i;
        vos_TaskCtrlBlk[i].ulEventIsCreate = VOS_FALSE;
        vos_TaskCtrlBlk[i].ulEvents   = 0;
        vos_TaskCtrlBlk[i].ulExpects  = 0;
        vos_TaskCtrlBlk[i].ulReceives = 0;
        vos_TaskCtrlBlk[i].ulFlags    = VOS_EVENT_NOWAIT;
        vos_TaskCtrlBlk[i].ulFid      = 0xffffffff;
    }
    return;
}

/*****************************************************************************
 Function   : VOS_TaskCtrlBlkGet
 Description: allocate a block
 Input      : void
            : void
 Return     : VOS_OK on success or errno on failure.
 Other      :
 *****************************************************************************/
VOS_UINT32 VOS_TaskCtrlBlkGet(VOS_VOID)
{
    VOS_UINT32       i;
    int              intLockLevel;

    intLockLevel = VOS_SplIMP();

    for(i=0; i<vos_TaskCtrlBlkNumber; i++)
    {
        if(vos_TaskCtrlBlk[i].Flag == VOS_TASK_CTRL_BLK_IDLE)
        {
            vos_TaskCtrlBlk[i].Flag = VOS_TASK_CTRL_BLK_BUSY;

            break;
        }
    }

    VOS_Splx(intLockLevel);

    if( i < vos_TaskCtrlBlkNumber)
    {
        return i;
    }
    else
    {
        Print("# allocate task control block fail.\r\n");

        return(VOS_TASK_CTRL_BLK_NULL);
    }
}

/*****************************************************************************
 Function   : VOS_TaskCtrlBlkFree
 Description: free a block
 Input      : Tid -- task ID
 Return     : VOS_OK on success or errno on failure.
 Other      :
 *****************************************************************************/
VOS_UINT32 VOS_TaskCtrlBlkFree(VOS_UINT32 Tid)
{
    int              intLockLevel;

    if( Tid < vos_TaskCtrlBlkNumber )
    {
        if(vos_TaskCtrlBlk[Tid].Flag == VOS_TASK_CTRL_BLK_IDLE)
        {
            Print("# VOS_TaskCtrlBlkFree free Idle Task.\r\n");

            return VOS_ERR;
        }
        else
        {
            intLockLevel = VOS_SplIMP();
            vos_TaskCtrlBlk[Tid].Flag = VOS_TASK_CTRL_BLK_IDLE;
            VOS_Splx(intLockLevel);

            return VOS_OK;
        }
    }
    else
    {
        Print("# VOS_TaskCtrlBlkFree Error.\r\n");

        return VOS_ERR;
    }
}

/*****************************************************************************
 Function   : VOS_NucleusTaskEntry
 Description: task entry
 Input      : none
 Output     : none
 Return     : Return task's ID if success or fail information if fail
 Other      : none
 *****************************************************************************/
VOS_VOID VOS_NucleusTaskEntry( VOS_UINT32 ulargc, VOS_VOID *pargv )
{
    VOS_TASK_CONTROL_BLOCK     *pstTemp;
    VOS_UINT32      ulPara1;
    VOS_UINT32      ulPara2;
    VOS_UINT32      ulPara3;
    VOS_UINT32      ulPara4;

    pstTemp = (VOS_TASK_CONTROL_BLOCK *)ulargc;


    ulPara1 = pstTemp->Args[0];
    ulPara2 = pstTemp->Args[1];
    ulPara3 = pstTemp->Args[2];
    ulPara4 = pstTemp->Args[3];

    pstTemp->Function( ulPara1, ulPara2, ulPara3, ulPara4 );
}


/*****************************************************************************
 Function   : VOS_CreateTask
 Description: create task with default task mode:
              VOS_T_PREEMPT | VOS_T_NO_TSLICE | VOS_T_SUPV
 Input      : puchName              -- name identify task
              pfnFunc               -- task entry function
              ulPriority            -- task priority
              ulStackSize           -- task stack size
              aulArgs[VOS_TARG_NUM] -- arguments for task
 Output     : pulTaskID             -- task id allocated by dopra
 Return     : result of VOS_CreateTaskEx
 *****************************************************************************/
VOS_UINT32 VOS_CreateTask( VOS_CHAR * puchName,
                           VOS_UINT32 * pulTaskID,
                           VOS_TASK_ENTRY_TYPE pfnFunc,
                           VOS_UINT32 ulPriority,
                           VOS_UINT32 ulStackSize,
                           VOS_UINT32 aulArgs[VOS_TARG_NUM] )
{
    int             i;
    VOS_UINT32      iTid;
    VOS_CHAR        default_name[8];
    VOS_UCHAR       value;
    VOS_VOID        *pStackStartAddress;

    iTid = VOS_TaskCtrlBlkGet();
    if( iTid == (VOS_UINT32)VOS_TASK_CTRL_BLK_NULL )
    {
        VOS_SetErrorNo(VOS_ERRNO_TASK_CREATE_NOFREETCB);
        return( VOS_ERRNO_TASK_CREATE_NOFREETCB );
    }

    /* caller not use name asign a default name */
    if ( VOS_NULL_PTR == puchName )
    {
        default_name[0]= 't';
        default_name[1]= 'i';
        default_name[2]= 'd';
        default_name[3] = (VOS_CHAR)(48 + iTid/100);
        value = (VOS_UCHAR)(iTid%100);
        default_name[4] = (VOS_CHAR)(48 + value/10);
        default_name[5] = (VOS_CHAR)(48 + value%10);
        default_name[6]= '\0';

        /*lint -e534*/
        VOS_MemCpy(vos_TaskCtrlBlk[iTid].Name, default_name, 7);
        /*lint +e534*/
    }
    else
    {
        for(i=0; i<VOS_MAX_LENGTH_TASK_NAME; i++)
        {
            vos_TaskCtrlBlk[iTid].Name[i]= puchName[i];
        }
        vos_TaskCtrlBlk[iTid].Name[i-1]  = '\0';
    }

    pStackStartAddress = NU_StackMalloc(ulStackSize);
    if ( VOS_NULL_PTR == pStackStartAddress )
    {
        VOS_TaskCtrlBlkFree(iTid);
        VOS_SetErrorNo(VOS_ERRNO_TASK_CREATE_OSALCREATEFAIL);
        return( VOS_ERRNO_TASK_CREATE_OSALCREATEFAIL );
    }

    vos_TaskCtrlBlk[iTid].Function   = pfnFunc;
    vos_TaskCtrlBlk[iTid].Priority   = ulPriority;
    vos_TaskCtrlBlk[iTid].StackSize  = ulStackSize;

    for ( i=0; i<VOS_TARG_NUM; i++ )
    {
        vos_TaskCtrlBlk[iTid].Args[i]    = aulArgs[i];
    }

    if ( NU_SUCCESS
        != NU_Create_Task(&(vos_TaskCtrlBlk[iTid].NuTid), vos_TaskCtrlBlk[iTid].Name,
            VOS_NucleusTaskEntry, (VOS_UINT32)(&(vos_TaskCtrlBlk[iTid])),
            VOS_NULL_PTR, pStackStartAddress, ulStackSize, ulPriority, 0,
            NU_PREEMPT, NU_START) )
    {
        NU_StackFree(pStackStartAddress);
        VOS_TaskCtrlBlkFree(iTid);
        VOS_SetErrorNo(VOS_ERRNO_TASK_CREATE_OSALCREATEFAIL);
        return( VOS_ERRNO_TASK_CREATE_OSALCREATEFAIL );
    }

    *pulTaskID = iTid;

    return VOS_OK;
}

/*****************************************************************************
 Function   : VOS_SuspendTask
 Description: Suspend a task
 Calls      : OSAL_SuspendTask
 Called By  :
 Input      : ulTaskID  --  id of a task
 Output     : none
 Return     : return VOS_OK if success
 Other      : none
 *****************************************************************************/
VOS_UINT32 VOS_SuspendTask( VOS_UINT32 ulTaskID )
{
    if( ulTaskID >= vos_TaskCtrlBlkNumber )
    {
        return(VOS_ERR);
    }

    if ( NU_SUCCESS != NU_Suspend_Task( &(vos_TaskCtrlBlk[ulTaskID].NuTid) ) )
    {
        Print("# Nucleus taskSuspend error.\r\n");
        return(VOS_ERR);
    }

    return(VOS_OK);
}

/*****************************************************************************
 Function   : VOS_ResumeTask
 Description: Resume a task
 Input      : ulTaskID  --  ID of task
 Return     : Return VOS_OK if successd
 *****************************************************************************/
VOS_UINT32 VOS_ResumeTask( VOS_UINT32 ulTaskID )
{
    if( ulTaskID >= vos_TaskCtrlBlkNumber )
    {
        return(VOS_ERR);
    }

    if ( NU_SUCCESS != NU_Resume_Task( &(vos_TaskCtrlBlk[ulTaskID].NuTid) ) )
    {
        Print("# Nucleus taskResume error.\r\n");
        return(VOS_ERR);
    }

    return(VOS_OK);
}

/*****************************************************************************
 Function   : VOS_TaskDelay
 Description: Let the task sleep specified millseconds, only tick precision
 Output     : None
 Input      : ulMillSecs: specified millseconds
 Return     : VOS_OK on success or error code on failed
 *****************************************************************************/
VOS_UINT32 VOS_TaskDelay( VOS_UINT32 ulMillSecs )
{
    NU_Sleep( ulMillSecs/10 + 1);

    return(VOS_OK);
}

/*****************************************************************************
 Function   : VOS_TaskLock
 Description: forbid task attemper.
 Input      : None
 Output     : None
 Return     : VOS_OK on success and others on failure
 Other      : This functin can not be called in interrupt routine.
 *****************************************************************************/
VOS_UINT32 VOS_TaskLock( VOS_VOID )
{
    NU_Change_Preemption( NU_NO_PREEMPT );

    return(VOS_OK);
}

/*****************************************************************************
 Function   : VOS_TaskUnlock
 Description: permit task attemper.
 Input      : None
 Output     : None
 Return     : VOS_OK on success and others on failure
 Other      : This functin can not be called in interrupt routine.
 *****************************************************************************/
VOS_UINT32 VOS_TaskUnlock( VOS_VOID )
{
    NU_Change_Preemption( NU_PREEMPT );

    return(VOS_OK);
}

/*****************************************************************************
 Function   : VOS_DeleteTask
 Description: Delete a task, on some platform this operation is prohibited.
 Input      : ulTaskID -- ID of task to delete, 0 for current task ID
                          VOS_NULL_DWORD means current task exit normally,
                          so only need to free the dopra task resource,
                          do not need to call OSAL_DeleteTask.
 Output     : None
 Return     : VOS_OK on success or error code on failed
 *****************************************************************************/
VOS_UINT32 VOS_DeleteTask( VOS_UINT32 ulTaskID )
{
    return(VOS_OK);
}

/*****************************************************************************
 Function   : VOS_GetCurrentTaskID
 Description: Get current task's ID
 Input      : none
 Output     : none
 Return     : Return task's ID if success or fail information if fail
 Other      : none
 *****************************************************************************/
VOS_UINT32 VOS_GetCurrentTaskID( VOS_VOID )
{
    NU_TASK         *task_ptr;
    VOS_INT         i;
    VOS_INT         intLockLevel;

    task_ptr = NU_Current_Task_Pointer();
    if( VOS_NULL_PTR == task_ptr )
    {
        return( VOS_NULL_LONG );
    }

    intLockLevel = VOS_SplIMP();

    for ( i=0; i<(VOS_INT)vos_TaskCtrlBlkNumber; i++ )
    {
        if( VOS_TASK_CTRL_BLK_BUSY == vos_TaskCtrlBlk[i].Flag )
        {
            if ( task_ptr == &(vos_TaskCtrlBlk[i].NuTid) )
            {
                VOS_Splx(intLockLevel);

                return (VOS_UINT32)i;

            }
        }
    }

    VOS_Splx(intLockLevel);

    /*lint -e534*/
    LogPrint("# VOS_GetCurrentTaskID fatal error.\r\n");
    /*lint +e534*/

    return( VOS_NULL_LONG );
}

/*****************************************************************************
 Function   :VOS_CreateEvent
 Description:Create resource for the Event.
 Calls      :no
 Called By  :Application
 Input      :
            ulTaskID  The Task ID
 Output     :
            NULL
 Return     :
            VOS_OK    when success
            ErrorNo   when failure
 Other      :
 *****************************************************************************/
VOS_UINT32 VOS_CreateEvent( VOS_UINT32 ulTaskID )
{
    if ( VOS_TASK_CTRL_BLK_IDLE == vos_TaskCtrlBlk[ulTaskID].Flag )
    {
        return VOS_ERR;
    }

    vos_TaskCtrlBlk[ulTaskID].ulEventIsCreate = VOS_TRUE;
    vos_TaskCtrlBlk[ulTaskID].ulEvents   = 0;
    vos_TaskCtrlBlk[ulTaskID].ulExpects  = 0;
    vos_TaskCtrlBlk[ulTaskID].ulReceives = 0;
    vos_TaskCtrlBlk[ulTaskID].ulFlags    = VOS_EVENT_NOWAIT;

    return VOS_OK;
}

/*****************************************************************************
 Function   : VOS_CheckEvent
 Description: checke a event exists or not
 Input      : none
 Output     : none
 Return     : VOS_OK or VOS_ERR
 Other      : none
 *****************************************************************************/
VOS_UINT32 VOS_CheckEvent( VOS_UINT32 ulTaskID )
{
    if ( VOS_TASK_CTRL_BLK_IDLE == vos_TaskCtrlBlk[ulTaskID].Flag )
    {
        return VOS_ERR;
    }

    if ( VOS_FALSE == vos_TaskCtrlBlk[ulTaskID].ulEventIsCreate )
    {
        return VOS_ERR;
    }

    if ( 0xffffffff == vos_TaskCtrlBlk[ulTaskID].ulFid )
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 Function   : VOS_RecordFIDTIDInfo
 Description: record corresponding of FID&TID
 Input      : none
 Output     : none
 Return     : VOS_OK or VOS_ERR
 Other      : none
 *****************************************************************************/
VOS_UINT32 VOS_RecordFIDTIDInfo( VOS_UINT32 ulFid, VOS_UINT32 ulTid )
{
    vos_TaskCtrlBlk[ulTid].ulFid = ulFid;

    return VOS_OK;
}

/*****************************************************************************
 Function   :VOS_UINT32   VOS_EventWrite( VOS_UINT32 ulTaskID, VOS_UINT32 ulEvents )
 Description:Send Event to the TaskID.
 Calls      :VOS_TRACE_SEND_EVENT(), VOS_CheckTaskIDValid(),VOS_SplIMP(),VOS_Splx()
 Called By  :Application
 Input      :ulTaskID, ulEvents
 Output     :NULL
 Return     :
            VOS_OK   when sucess
            ERRNO   when fail
 Other      :
 *****************************************************************************/
VOS_UINT32 VOS_EventWrite( VOS_UINT32 ulTaskID, VOS_UINT32 ulEvents )
{
    /* the functin should be full later */
    int                      intLockLevel;
    VOS_UINT32               ulTempQueue;
    VOS_SEM                  ulTempSem;

    if ( VOS_OK != VOS_CheckEvent(ulTaskID) )
    {
        /*lint -e534*/
        LogPrint("# VOS_EventWrite EVENT not exist.\r\n");
        /*lint +e534*/
        return VOS_ERR;
    }

    intLockLevel = VOS_SplIMP();

    vos_TaskCtrlBlk[ulTaskID].ulEvents |= ulEvents;

    VOS_Splx( intLockLevel );

    ulTempQueue = VOS_GetQueueIDFromFid(vos_TaskCtrlBlk[ulTaskID].ulFid);
    if ( 0xffffffff == ulTempQueue )
    {
        return VOS_ERR;
    }

    ulTempSem = VOS_GetSemIDFromQueue(ulTempQueue);
    if ( 0xffffffff == ulTempSem )
    {
        return VOS_ERR;
    }

    if ( VOS_OK != VOS_SmV( ulTempSem ) )
    {
        /*lint -e534*/
        LogPrint("# VOS_EventWrite error.\r\n");
        /*lint +e534*/

        return VOS_ERR;
    }
    else
    {
        return VOS_OK;
    }
}

/*****************************************************************************
 Function   :VOS_EventRead
 Description:Read event
 Calls      :VOS_TRACE_SEND_EVENT(),VOS_GetCurrentTaskID(),
             VOS_SplIMP(),VOS_Splx(),VOS_Dispater()
 Called By  :Application
 Input      :
            ulEvents    the expect event, while 0 refers to check event only,
                        NOT get it while return.
            ulFlags     the Flags, refers to WAIT or NOWAIT, ANY or ALL, etc.
            ulTimeOutInMillSec  the deadline while WAIT for event
 Output     :pulRetEvents       the received Event.
 Return     :
            VOS_OK when sucess
            ERRNO when failure
 Other      :
 *****************************************************************************/
VOS_UINT32 VOS_EventRead( VOS_UINT32 ulEvents,
                          VOS_UINT32 ulFlags,
                          VOS_UINT32 ulTimeOutInMillSec,
                          VOS_UINT32 *pulRetEvents )
{
    /* the functin should be full later */
    VOS_UINT32     ulTaskSelf;       /*Self task ID*/
    VOS_UINT32     ulTempQueue;
    VOS_SEM        ulTempSem;
    int            intLockLevel;
    VOS_UINT32     ulTempEvent;

    ulTaskSelf = VOS_GetCurrentTaskID();

    if ( 0xffffffff == ulTaskSelf )
    {
        return VOS_ERR;
    }

    if( VOS_EVENT_NOWAIT & ulFlags )
    {
        /*lint -e534*/
        LogPrint("# OSA don't support VOS_EVENT_NOWAIT.\r\n");
        /*lint +e534*/

        VOS_SuspendTask(ulTaskSelf);

        return VOS_ERR;
    }

    if( !(VOS_EVENT_ANY & ulFlags) )
    {
        /*lint -e534*/
        LogPrint("# OSA don't support VOS_EVENT_ALL.\r\n");
        /*lint +e534*/

        VOS_SuspendTask(ulTaskSelf);

        return VOS_ERR;
    }

    if( 0 == ulEvents )
    {
        /*lint -e534*/
        LogPrint("# OSA don't support event = 0.\r\n");
        /*lint +e534*/

        VOS_SuspendTask(ulTaskSelf);

        return VOS_ERR;
    }

    if ( VOS_OK != VOS_CheckEvent(ulTaskSelf) )
    {
        /*lint -e534*/
        LogPrint("# VOS_EventRead EVENT not exist.\r\n");
        /*lint +e534*/

        VOS_SuspendTask(ulTaskSelf);

        return VOS_ERR;
    }

    ulTempQueue = VOS_GetQueueIDFromFid(vos_TaskCtrlBlk[ulTaskSelf].ulFid);
    if ( 0xffffffff == ulTempQueue )
    {
        return VOS_ERR;
    }

    ulTempSem = VOS_GetSemIDFromQueue(ulTempQueue);
    if ( 0xffffffff == ulTempSem )
    {
        return VOS_ERR;
    }

    if( VOS_OK != VOS_SmP( ulTempSem, ulTimeOutInMillSec ) )
    {
        Print("# VOS_EventRead error.\r\n");
        return VOS_ERR;
    }

    intLockLevel = VOS_SplIMP();

    ulTempEvent = vos_TaskCtrlBlk[ulTaskSelf].ulEvents & ulEvents;

    if (  ulTempEvent )
    {
        vos_TaskCtrlBlk[ulTaskSelf].ulEvents &= ~ulTempEvent;
        *pulRetEvents  = ulTempEvent;
    }
    else
    {
        *pulRetEvents = VOS_MSG_SYNC_EVENT;
    }

    VOS_Splx( intLockLevel );

    return VOS_OK;
}

/*****************************************************************************
 Function   : VOS_GetQueueIDFromTID
 Description: get the queue ID of a TId
 Input      : ulFID      -- Function module Identifier

 Return     : the queue ID
 *****************************************************************************/
VOS_UINT32 VOS_GetQueueIDFromTID(VOS_UINT32 ulTid)
{
    if ( ulTid >= vos_TaskCtrlBlkNumber )
    {
        /*lint -e534*/
        LogPrint("VOS_GetQueueIDFromTID TID invaild.\r\n");
        /*lint +e534*/

        return 0xffffffff;
    }

    if ( 0xffffffff == vos_TaskCtrlBlk[ulTid].ulFid )
    {
        /*lint -e534*/
        LogPrint("VOS_GetQueueIDFromTID FID invaild.\r\n");
        /*lint +e534*/

        return 0xffffffff;
    }

    return VOS_GetQueueIDFromFid(vos_TaskCtrlBlk[ulTid].ulFid);
}


#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



