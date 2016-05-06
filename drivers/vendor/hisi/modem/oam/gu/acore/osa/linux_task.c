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
/* FileName: linux_task.c                                                    */
/*                                                                           */
/* Author: Xu Cheng                                                          */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date: 2011-07                                                             */
/*                                                                           */
/* Description: implement Linux task                                         */
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

#include "vos_config.h"
#include "v_typdef.h"
#include "v_task.h"
#include "v_IO.h"
#include "v_int.h"
#include "vos_Id.h"
#include "v_sem.h"
#include "v_private.h"
#include "mdrv.h"
#include <linux/kthread.h>

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#if (VOS_LINUX == VOS_OS_VER)


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 modify:x51137; review:h59254; cause:print log */
#define    THIS_FILE_ID        PS_FILE_ID_V_TASK_C
/*lint +e767 modify:x51137; review:h59254; */


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
    pid_t               ulLinuxThreadId;/* maped Linux thread id */
    VOS_UINT8           aucRsv[4];
} VOS_TASK_CONTROL_BLOCK;

/* the number of task's control block */
VOS_UINT32              vos_TaskCtrlBlkNumber;

/* the start address of task's control block */
VOS_TASK_CONTROL_BLOCK *vos_TaskCtrlBlk;

#define VOS_TASK_CTRL_BUF_SIZE (sizeof(VOS_TASK_CONTROL_BLOCK)*VOS_MAX_TASK_NUMBER)

VOS_UINT32 g_acVosTaskCtrlBuf[VOS_TASK_CTRL_BUF_SIZE/4];

typedef VOS_INT (*LINUX_START_ROUTINE)( VOS_VOID * );

/* 自旋锁，用来作task的临界资源保护 */
VOS_SPINLOCK             g_stVosTaskSpinLock;


struct semaphore         g_stVosTaskRunSem;

VOS_VOID VOS_LinuxTaskEntry( VOS_VOID * pulArg );

/*****************************************************************************
 Function   : VOS_TaskPrintCtrlBlkInfo
 Description: record debug info
 Input      : void
            : void
 Return     : void
 Other      :
 *****************************************************************************/
VOS_VOID VOS_TaskPrintCtrlBlkInfo(VOS_VOID)
{
    VOS_CHAR         *pcBuff;

    pcBuff = (VOS_CHAR *)VOS_EXCH_MEM_MALLOC(VOS_DUMP_MEM_TOTAL_SIZE);

    if (VOS_NULL_PTR == pcBuff)
    {
        return;
    }

    /*lint -e534*/
    VOS_MemCpy(pcBuff, (VOS_CHAR *)g_acVosTaskCtrlBuf, VOS_TASK_CTRL_BUF_SIZE);
    /*lint +e534*/

    return;
}

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
        vos_TaskCtrlBlk[i].ulLinuxThreadId = 0;
        vos_TaskCtrlBlk[i].ulEventIsCreate = VOS_FALSE;
        vos_TaskCtrlBlk[i].ulEvents   = 0;
        vos_TaskCtrlBlk[i].ulExpects  = 0;
        vos_TaskCtrlBlk[i].ulReceives = 0;
        vos_TaskCtrlBlk[i].ulFlags    = VOS_EVENT_NOWAIT;
        vos_TaskCtrlBlk[i].ulFid      = 0xffffffff;
    }

    VOS_SpinLockInit(&g_stVosTaskSpinLock);

    sema_init(&g_stVosTaskRunSem, 0);

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
    VOS_UINT32              i;
    VOS_ULONG               ulLockLevel;

    /*intLockLevel = VOS_SplIMP();*/
    VOS_SpinLockIntLock(&g_stVosTaskSpinLock, ulLockLevel);

    for(i=0; i<vos_TaskCtrlBlkNumber; i++)
    {
        if(vos_TaskCtrlBlk[i].Flag == VOS_TASK_CTRL_BLK_IDLE)
        {
            vos_TaskCtrlBlk[i].Flag = VOS_TASK_CTRL_BLK_BUSY;

            break;
        }
    }

    /*VOS_Splx(intLockLevel);*/
    VOS_SpinUnlockIntUnlock(&g_stVosTaskSpinLock, ulLockLevel);

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
    VOS_ULONG               ulLockLevel;

    if( Tid < vos_TaskCtrlBlkNumber )
    {
        if(vos_TaskCtrlBlk[Tid].Flag == VOS_TASK_CTRL_BLK_IDLE)
        {
            Print("# VOS_TaskCtrlBlkFree free Idle Task.\r\n");

            return VOS_ERR;
        }
        else
        {
            /* intLockLevel = VOS_SplIMP(); */
            VOS_SpinLockIntLock(&g_stVosTaskSpinLock, ulLockLevel);

            vos_TaskCtrlBlk[Tid].Flag = VOS_TASK_CTRL_BLK_IDLE;

            VOS_SpinUnlockIntUnlock(&g_stVosTaskSpinLock, ulLockLevel);
            /*VOS_Splx(intLockLevel);*/

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
 Function   : VOS_LinuxTaskEntry
 Description: linux task's entry
 Input      : none
 Output     : none
 Return     : none
 Other      : none
 *****************************************************************************/

VOS_VOID VOS_LinuxTaskEntry( VOS_VOID * pulArg )
{
    VOS_TASK_CONTROL_BLOCK      *pstTemp;
    VOS_UINT32                  ulPara1;
    VOS_UINT32                  ulPara2;
    VOS_UINT32                  ulPara3;
    VOS_UINT32                  ulPara4;

    pstTemp = (VOS_TASK_CONTROL_BLOCK *)pulArg;

    ulPara1 = pstTemp->Args[0];
    ulPara2 = pstTemp->Args[1];
    ulPara3 = pstTemp->Args[2];
    ulPara4 = pstTemp->Args[3];

    /* ulPara4为全F代表为FID任务或FID自处理任务等待OSA启动完毕后再正常运行 */
    if (VOS_NULL_DWORD == ulPara4)
    {
        down(&g_stVosTaskRunSem);
    }
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
    int                  i;
    VOS_UINT32           iTid;
    VOS_CHAR             default_name[8] = {0};
    VOS_UCHAR            value;
    VOS_INT_PTR          lFuncAddr;
    struct task_struct  *tsk;
    struct sched_param   param;

    iTid = VOS_TaskCtrlBlkGet();
    if( iTid == (VOS_UINT32)VOS_TASK_CTRL_BLK_NULL )
    {
        VOS_TaskPrintCtrlBlkInfo();

        lFuncAddr = (VOS_INT_PTR)pfnFunc;

        VOS_ProtectionReboot(OSA_ALLOC_TASK_CONTROL_ERROR, (VOS_INT)vos_TaskCtrlBlkNumber, (VOS_INT)lFuncAddr, VOS_NULL_PTR, 0);

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

    tsk = kthread_run( (LINUX_START_ROUTINE)VOS_LinuxTaskEntry,
        ( VOS_VOID * )&(vos_TaskCtrlBlk[iTid]), vos_TaskCtrlBlk[iTid].Name);

    if (tsk == VOS_NULL)
    {
        VOS_TaskPrintCtrlBlkInfo();

        VOS_ProtectionReboot(OSA_CREATE_TASK_ERROR, (VOS_INT)(__LINE__), (VOS_INT)iTid, VOS_NULL_PTR, 0);

        VOS_TaskCtrlBlkFree(iTid);
        VOS_SetErrorNo(VOS_ERRNO_TASK_CREATE_OSALCREATEFAIL);
        return( VOS_ERRNO_TASK_CREATE_OSALCREATEFAIL );
    }

    vos_TaskCtrlBlk[iTid].ulLinuxThreadId = tsk->pid;

    param.sched_priority = ulPriority;

    if (VOS_NULL != sched_setscheduler(tsk, SCHED_FIFO, &param))
    {
        /*lint -e534*/
        vos_printf("\r\nVOS_CreateTask: Creat Task %s ID %d sched_setscheduler Error", puchName, iTid);
        /*lint +e534*/

        VOS_TaskPrintCtrlBlkInfo();

        VOS_ProtectionReboot(OSA_SET_TASK_PRI_ERROR, (VOS_INT)ulPriority, (VOS_INT)iTid, (VOS_CHAR *)tsk, sizeof(struct task_struct));

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
    struct task_struct    *tsk;
    pid_t                 ulTemp;

    if( ulTaskID >= vos_TaskCtrlBlkNumber )
    {
        return(VOS_ERR);
    }

    ulTemp = vos_TaskCtrlBlk[ulTaskID].ulLinuxThreadId;

    tsk = pid_task(find_vpid(ulTemp), PIDTYPE_PID);

    if ( VOS_NULL_PTR == tsk)
    {
        return(VOS_ERR);
    }

    if ( tsk->pid != ulTemp )
    {
        printk("susupend find task to set pri fail.\r\n");
        return VOS_ERR;
    }

    set_task_state(tsk, TASK_UNINTERRUPTIBLE);

    if (tsk == current)
    {
        schedule();
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
    pid_t                  ulTemp;
    struct task_struct     *tsk;

    if(ulTaskID >= vos_TaskCtrlBlkNumber)
    {
        return(VOS_ERR);
    }

    ulTemp = vos_TaskCtrlBlk[ulTaskID].ulLinuxThreadId;

    tsk = pid_task(find_vpid(ulTemp), PIDTYPE_PID);

    if ( VOS_NULL_PTR == tsk)
    {
        return(VOS_ERR);
    }

    if ( tsk->pid != ulTemp )
    {
        printk("resume find task to set pri fail.\r\n");
        return VOS_ERR;
    }

    /*set_task_state(tsk, TASK_RUNNING);*/

    wake_up_process(tsk);

    return VOS_OK;
}

/*****************************************************************************
 Function   : VOS_RunTask
 Description: wake up all FID's task & selftask.
 Output     : None
 Input      : None
 Return     : None
 *****************************************************************************/
VOS_VOID VOS_RunTask(VOS_VOID)
{
    int i;

    for(i = 0; i < VOS_MAX_TASK_NUMBER; i++)
    {
        up(&g_stVosTaskRunSem);
    }

    return;
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
    set_current_state(TASK_UNINTERRUPTIBLE);

    (VOS_VOID)schedule_timeout((((ulMillSecs)*HZ)/1000)+1);

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
    preempt_disable();

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
    preempt_enable();

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
    /*lint -e534*/
    vos_printf("\r\nVOS_DeleteTask: Delete Task %x", ulTaskID);
    /*lint +e534*/

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
    pid_t               ulOSID;
    int                 i;
    VOS_ULONG           ulLockLevel;

    ulOSID = current->pid;

    /*intLockLevel = VOS_SplIMP();*/
    VOS_SpinLockIntLock(&g_stVosTaskSpinLock, ulLockLevel);

    for ( i=0; i<(VOS_INT)vos_TaskCtrlBlkNumber; i++ )
    {
        if( VOS_TASK_CTRL_BLK_BUSY == vos_TaskCtrlBlk[i].Flag )
        {
            if ( ulOSID == vos_TaskCtrlBlk[i].ulLinuxThreadId )
            {
                /*VOS_Splx(intLockLevel);*/
                VOS_SpinUnlockIntUnlock(&g_stVosTaskSpinLock, ulLockLevel);

                return (VOS_UINT32)i;

            }
        }
    }

    /*VOS_Splx(intLockLevel);*/
    VOS_SpinUnlockIntUnlock(&g_stVosTaskSpinLock, ulLockLevel);

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
#if (VOS_YES == VOS_CHECK_PARA)
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
#endif

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
    VOS_ULONG                ulLockLevel;
    VOS_UINT32               ulTempQueue;
    VOS_SEM                  ulTempSem;

    if ( VOS_OK != VOS_CheckEvent(ulTaskID) )
    {
        /*lint -e534*/
        LogPrint("# VOS_EventWrite EVENT not exist.\r\n");
        /*lint +e534*/
        return VOS_ERR;
    }

    /*intLockLevel = VOS_SplIMP();*/
    VOS_SpinLockIntLock(&g_stVosTaskSpinLock, ulLockLevel);

    vos_TaskCtrlBlk[ulTaskID].ulEvents |= ulEvents;

    /*VOS_Splx( intLockLevel );*/
    VOS_SpinUnlockIntUnlock(&g_stVosTaskSpinLock, ulLockLevel);

    ulTempQueue = VOS_GetQueueIDFromFid(vos_TaskCtrlBlk[ulTaskID].ulFid);
#if (VOS_YES == VOS_CHECK_PARA)
    if ( 0xffffffff == ulTempQueue )
    {
        return VOS_ERR;
    }
#endif

    ulTempSem = VOS_GetSemIDFromQueue(ulTempQueue);
#if (VOS_YES == VOS_CHECK_PARA)
    if ( 0xffffffff == ulTempSem )
    {
        return VOS_ERR;
    }
#endif

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
    VOS_ULONG      ulLockLevel;
    VOS_UINT32     ulTempEvent;

    ulTaskSelf = VOS_GetCurrentTaskID();
#if (VOS_YES == VOS_CHECK_PARA)
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
#endif

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
#if (VOS_YES == VOS_CHECK_PARA)
    if ( 0xffffffff == ulTempQueue )
    {
        return VOS_ERR;
    }
#endif

    ulTempSem = VOS_GetSemIDFromQueue(ulTempQueue);
#if (VOS_YES == VOS_CHECK_PARA)
    if ( 0xffffffff == ulTempSem )
    {
        return VOS_ERR;
    }
#endif

    if( VOS_OK != VOS_SmP( ulTempSem, ulTimeOutInMillSec ) )
    {
        Print("# VOS_EventRead error.\r\n");
        return VOS_ERR;
    }

    /*intLockLevel = VOS_SplIMP();*/
    VOS_SpinLockIntLock(&g_stVosTaskSpinLock, ulLockLevel);

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

    /*VOS_Splx( intLockLevel );*/
    VOS_SpinUnlockIntUnlock(&g_stVosTaskSpinLock, ulLockLevel);

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
#if (VOS_YES == VOS_CHECK_PARA)
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
#endif

    return VOS_GetQueueIDFromFid(vos_TaskCtrlBlk[ulTid].ulFid);
}

/*****************************************************************************
 Function   : VOS_GetTCBFromTID
 Description: get linux thread id from OSA Tid.
 Input      : ulTid

 Return     : linux thread id
 *****************************************************************************/
VOS_UINT32 VOS_GetTCBFromTID(VOS_UINT32 ulTid)
{
    return (VOS_UINT32)vos_TaskCtrlBlk[ulTid].ulLinuxThreadId;
}


#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


