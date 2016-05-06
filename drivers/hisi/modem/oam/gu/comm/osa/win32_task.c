/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and 
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may 
 * *    be used to endorse or promote products derived from this software 
 * *    without specific prior written permission.
 * 
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/*****************************************************************************/
/*                                                                           */
/*                Copyright 1999 - 2003, Huawei Tech. Co., Ltd.              */
/*                           ALL RIGHTS RESERVED                             */
/*                                                                           */
/* FileName: win32_task.c                                                    */
/*                                                                           */
/* Author: Yang Xiangqian                                                    */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date: 2006-10                                                             */
/*                                                                           */
/* Description: implement win32 task                                         */
/*                                                                           */
/* Others:                                                                   */
/*                                                                           */
/* History:                                                                  */
/* 1. Date:                                                                  */
/*    Author:                                                                */
/*    Modification: Create this file                                         */
/*                                                                           */
/* 2. Date: 2006-10                                                          */
/*    Author: Xu Cheng                                                       */
/*    Modification: Standardize code                                         */
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


#if (VOS_WIN32 == VOS_OS_VER)


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_V_WIN32_TASK_C


typedef struct
{
    int                 Flag;
    int                 Tid;/* task ID */
    VOS_TASK_ENTRY_TYPE Function;/* the entry of task */
    VOS_UINT32          Priority;
    VOS_UINT32          StackSize;
    VOS_UINT32          Args[VOS_TARG_NUM];/* the argument of the entry */
    HANDLE              Win32Handle;/* maped win32 handle */
    VOS_UINT32          ulWin32ThreadId;/* maped win32 thread id */
    VOS_CHAR            Name[VOS_MAX_LENGTH_TASK_NAME];
    VOS_UINT32          ulEventIsCreate;/* event create or not */
    VOS_UINT32          ulEvents;/* current event */
    VOS_UINT32          ulExpects;/* expected event */
    VOS_UINT32          ulReceives;/* have been received event */
    VOS_UINT32          ulFlags;/* event mode */
    VOS_UINT32          ulFid;/* belong to a FID or not */
} VOS_TASK_CONTROL_BLOCK;

/* the number of task's control block */
VOS_UINT32              vos_TaskCtrlBlkNumber;

/* the start address of task's control block */
VOS_TASK_CONTROL_BLOCK *vos_TaskCtrlBlk;

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
        vos_TaskCtrlBlk[i].Win32Handle= VOS_NULL_PTR;
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
 Function   : VOS_WIN32PriMap
 Description: Map WIN32 priority to OSAL priority
 Calls      :
 Called By  :
 Input      : ulTaskPriority    --  task's priority
 Output     : none
 Return     : task's OSAL priority
 Other      : none
******************************************************************************/
VOS_UINT32 VOS_WIN32PriMap( VOS_UINT32 ulTaskPriority )
{
    ulTaskPriority >>= 5;
    switch(ulTaskPriority)
    {
        case 0:
            ulTaskPriority = (VOS_UINT32) THREAD_PRIORITY_IDLE;
            break;

        case 1:
            ulTaskPriority = (VOS_UINT32) THREAD_PRIORITY_LOWEST;
            break;

        case 2:
            ulTaskPriority = (VOS_UINT32) THREAD_PRIORITY_BELOW_NORMAL;
            break;

        case 3:
            ulTaskPriority = (VOS_UINT32) THREAD_PRIORITY_NORMAL;
            break;


        case 4:
            ulTaskPriority = (VOS_UINT32) THREAD_PRIORITY_ABOVE_NORMAL;
            break;

        case 5:
            ulTaskPriority = (VOS_UINT32) THREAD_PRIORITY_HIGHEST;
            break;

        case 6:
        case 7:
        default:
            ulTaskPriority = (VOS_UINT32) THREAD_PRIORITY_TIME_CRITICAL;
            break;
    }
    return ulTaskPriority;
}

/*****************************************************************************
 Function   : VOS_Win32TaskEntry
 Description: Get current task's ID
 Input      : none
 Output     : none
 Return     : Return task's ID if success or fail information if fail
 Other      : none
 *****************************************************************************/

VOS_VOID VOS_Win32TaskEntry( VOS_VOID * pulArg )
{
    VOS_TASK_CONTROL_BLOCK     *pstTemp;
    VOS_UINT32      ulPara1;
    VOS_UINT32      ulPara2;
    VOS_UINT32      ulPara3;
    VOS_UINT32      ulPara4;

    pstTemp = (VOS_TASK_CONTROL_BLOCK *)pulArg;


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
    HANDLE          pulTemp;
    VOS_CHAR        default_name[8];
    VOS_UCHAR       value;
    VOS_UINT32      ulOsTaskPriority;

    iTid = VOS_TaskCtrlBlkGet();
    if( iTid == (VOS_UINT32)VOS_TASK_CTRL_BLK_NULL )
    {
        /*lint -e534*/
        VOS_SetErrorNo(VOS_ERRNO_TASK_CREATE_NOFREETCB);
        /*lint +e534*/
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
    }

    *pulTaskID = iTid;

    if ( VOS_NULL_PTR != puchName )
    {
        for(i=0; i<VOS_MAX_LENGTH_TASK_NAME; i++)
        {
            vos_TaskCtrlBlk[iTid].Name[i]= puchName[i];
        }
        vos_TaskCtrlBlk[iTid].Name[i-1]  = '\0';
    }
    else
    {
        vos_TaskCtrlBlk[iTid].Name[0] = default_name[0];
        vos_TaskCtrlBlk[iTid].Name[1] = default_name[1];
        vos_TaskCtrlBlk[iTid].Name[2] = default_name[2];
        vos_TaskCtrlBlk[iTid].Name[3] = default_name[3];
        vos_TaskCtrlBlk[iTid].Name[4] = default_name[4];
        vos_TaskCtrlBlk[iTid].Name[5] = default_name[5];
        vos_TaskCtrlBlk[iTid].Name[6] = default_name[6];
    }

    vos_TaskCtrlBlk[iTid].Function   = pfnFunc;
    vos_TaskCtrlBlk[iTid].Priority   = ulPriority;
    vos_TaskCtrlBlk[iTid].StackSize  = ulStackSize;

    for ( i=0; i<VOS_TARG_NUM; i++ )
    {
        vos_TaskCtrlBlk[iTid].Args[i]    = aulArgs[i];
    }

    pulTemp = CreateThread( VOS_NULL_PTR, ulStackSize,
        ( LPTHREAD_START_ROUTINE )VOS_Win32TaskEntry,
        ( VOS_VOID * )&(vos_TaskCtrlBlk[iTid]), 0,
        &(vos_TaskCtrlBlk[iTid].ulWin32ThreadId)  );

    if( VOS_NULL_PTR == pulTemp )
    {
        VOS_TaskCtrlBlkFree(iTid);
        /*lint -e534*/
        VOS_SetErrorNo(VOS_ERRNO_TASK_CREATE_OSALCREATEFAIL);
        /*lint +e534*/
        return( VOS_ERRNO_TASK_CREATE_OSALCREATEFAIL );
    }

    vos_TaskCtrlBlk[iTid].Win32Handle = pulTemp;

    ulOsTaskPriority = VOS_WIN32PriMap( ulPriority );

    if ( VOS_NULL == SetThreadPriority( pulTemp, (VOS_INT)ulOsTaskPriority ) )
    {
        return VOS_ERR;
    }

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
    HANDLE             pulTemp;

    if( ulTaskID >= vos_TaskCtrlBlkNumber )
    {
        return(VOS_ERR);
    }
    else
    {
        pulTemp = vos_TaskCtrlBlk[ulTaskID].Win32Handle;
        if(VOS_NULL_PTR == pulTemp)
        {
            return(VOS_ERR);
        }
    }

    if ( VOS_NULL_DWORD == SuspendThread( pulTemp ) )
    {
        Print("# taskSuspend error.\r\n");
        return(VOS_ERR);
    }

    return VOS_OK;
}

/*****************************************************************************
 Function   : VOS_ResumeTask
 Description: Resume a task
 Input      : ulTaskID  --  ID of task
 Return     : Return VOS_OK if successd
 *****************************************************************************/
VOS_UINT32 VOS_ResumeTask( VOS_UINT32 ulTaskID )
{
    HANDLE             pulTemp;

    if(ulTaskID >= vos_TaskCtrlBlkNumber)
    {
        return(VOS_ERR);
    }
    else
    {
        pulTemp = vos_TaskCtrlBlk[ulTaskID].Win32Handle;
        if(VOS_NULL_PTR == pulTemp)
        {
            return(VOS_ERR);
        }
    }

    if ( VOS_NULL_DWORD == ResumeThread( pulTemp ) )
    {
        Print("# taskSuspend error.\r\n");
        return(VOS_ERR);
    }

    return VOS_OK;
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
    Sleep( ulMillSecs );
    return VOS_OK;
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
    VOS_SplIMP();

    return VOS_OK;
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
    VOS_Splx(0);

    return VOS_OK;
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
    VOS_UINT32  ulOSID;
    int         i;
    int         intLockLevel;

    ulOSID = ( VOS_UINT32 )GetCurrentThreadId();
    if( VOS_NULL_LONG == ulOSID )
    {
        return( VOS_NULL_LONG );
    }

    intLockLevel = VOS_SplIMP();

    for ( i=0; i<(VOS_INT)vos_TaskCtrlBlkNumber; i++ )
    {
        if( VOS_TASK_CTRL_BLK_BUSY == vos_TaskCtrlBlk[i].Flag )
        {
            if ( ulOSID == vos_TaskCtrlBlk[i].ulWin32ThreadId )
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
 Function   :VOS_UINT32 VOS_CreateEvent( VOS_UINT32 ulTaskID )
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
 Function   :VOS_UINT32 VOS_EventRead( VOS_UINT32 ulEvents,
                            VOS_UINT32 ulFlags,
                            VOS_UINT32  ulTimeOutInMillSec,
                            VOS_UINT32 * pulRetEvents )
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



