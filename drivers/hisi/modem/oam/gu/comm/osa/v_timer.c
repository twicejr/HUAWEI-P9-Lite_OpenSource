

/*****************************************************************************/
/*                                                                           */
/*                Copyright 1999 - 2003, Huawei Tech. Co., Ltd.              */
/*                           ALL RIGHTS RESERVED                             */
/*                                                                           */
/* FileName: v_timer.c                                                       */
/*                                                                           */
/* Author: Yang Xiangqian                                                    */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date: 2006-10                                                             */
/*                                                                           */
/* Description: implement timer                                              */
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
/* 3. Date: 2007-03-03                                                       */
/*    Author: Xu Cheng                                                       */
/*    Modification: A32D09073                                                */
/*                                                                           */
/* 4. Date: 2007-03-10                                                       */
/*    Author: Xu Cheng                                                       */
/*    Modification: A32D07254                                                */
/*                                                                           */
/*****************************************************************************/

#include "v_typdef.h"
#include "v_timer.h"
#include "v_msg.h"
#include "v_task.h"
#include "v_iddef.h"
#include "v_IO.h"
#include "v_id.h"
#include "time.h"
#include "v_sem.h"
#include "mdrv.h"
#include "VosTaskPrioDef.h"


/* LINUX 不支持 */
#if (VOS_VXWORKS== VOS_OS_VER)
#include "stdio.h"
#include "stdlib.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif /* __cpluscplus */
#endif /* __cpluscplus */



/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 modify:x51137; review:h59254; cause:print log */
#define    THIS_FILE_ID        PS_FILE_ID_V_TIMER_C
/*lint +e767 modify:x51137; review:h59254; */


/* the state of Timer */
#define VOS_TIMER_CTRL_BLK_RUNNIG                           0
#define VOS_TIMER_CTRL_BLK_PAUSE                            1
#define VOS_TIMER_CTRL_BLK_STOP                             2

/* the tag of  VOS_TimerCtrlBlkFree */
#define THE_FIRST_TIMER_TAG                                 1
#define THE_SECOND_TIMER_TAG                                2


/* timer task's stack size */
#define VOS_TIMER_TASK_STACK_SIZE                           3072

/* 32 bits*/
#define VOS_TICK_MAX                                        0xffffffff

#define REL_TIMER_MESSAGE_LENGTH    (sizeof(REL_TIMER_MSG)-VOS_MSG_HEAD_LENGTH)

typedef struct VOS_TIMER_CONTROL_STRU
{
    VOS_UINT32      TimerId;/* timer ID */
    VOS_UINT32      ulUsedFlag;/* whether be used or not */
    VOS_PID         Pid;/* who allocate the timer */
    VOS_UINT32      Name;/* timer's name */
    VOS_UINT32      Para;/* timer's paremate */
    VOS_UINT8       aucRsv[4];
    REL_TIMER_FUNC  CallBackFunc;/* timer's callback function */
    HTIMER          *phTm;/* user's pointer which point the real timer room */
    VOS_UINT32      TimeOutValueInMilliSeconds;
    VOS_UINT32      TimeOutValueInTicks;
    /* REL_TIMER_MSG   *message_Ptr; *//* the message which be sent when timer expire */
    struct VOS_TIMER_CONTROL_STRU *next;
    struct VOS_TIMER_CONTROL_STRU *previous;
    VOS_UINT8       Mode;/* timer's mode */
    VOS_UINT8       State;/* timer's state */
    VOS_UINT8       Reserved[2];/* for 4 byte aligned */

#if VOS_YES == VOS_TIMER_CHECK
    VOS_UINT32      ulAllocTick;/* CPU tick of block allocation */
    VOS_UINT32      ulFileID;/* alloc file ID */
    VOS_UINT32      ulLineNo;/* alloc line no. */
#endif
    VOS_UINT32      ulBackUpTimerId;/* timer ID */
} VOS_TIMER_CONTROL_BLOCK;

/* the number of task's control block */
VOS_UINT32                vos_TimerCtrlBlkNumber;

/* the number of free task's control block */
VOS_UINT32                vos_TimerIdleCtrlBlkNumber;

/* the start address of task's control block */
VOS_TIMER_CONTROL_BLOCK   *vos_TimerCtrlBlk;

/* the start address of free task's control block list */
VOS_TIMER_CONTROL_BLOCK   *vos_TimerIdleCtrlBlk;

/* the begin address of timer control block */
VOS_VOID                  *vos_TimerCtrlBlkBegin;

/* the end address of timer control block */
VOS_VOID                  *vos_TimerCtrlBlkEnd;

/* the head of the running timer list */
VOS_TIMER_CONTROL_BLOCK  *vos_Timer_head_Ptr = VOS_NULL_PTR;

/* the task ID of timer's task */
VOS_UINT32               vos_TimerTaskId;

/* the Min usage of timer */
VOS_UINT32               vos_TimerMinTimerIdUsed;

/* record elapsed cpu ticks when system boot */
CPU_TICK_EX              vos_CPU_TICK;

/* record current system time */
SYS_T                    g_SysTime;

#define VOS_TIMER_CTRL_BUF_SIZE (sizeof(VOS_TIMER_CONTROL_BLOCK) * VOS_MAX_TIMER_NUMBER )

VOS_CHAR g_acVosTimerCtrlBuf[VOS_TIMER_CTRL_BUF_SIZE];

#if VOS_YES == VOS_TIMER_CHECK

VOS_VOID VOS_ShowUsed26MTimerInfo( VOS_VOID );

#endif

#if (VOS_WIN32 == VOS_OS_VER)
/* Magnify timer length -> length * g_ulMagnifyTimerLength  */
VOS_UINT32               g_ulMagnifyTimerLength = 1;
#endif

VOS_VOID VOS_TimerDump(VOS_INT lModId, VOS_UINT32 ulFileID, VOS_UINT32 ulLineNo);

/* 自旋锁，用来作Timer的临界资源保护 */
VOS_SPINLOCK                  g_stVosTimerSpinLock;

#if (VOS_YES == VOS_26M_TIMER_ENABLE_SOC_TIMER)

#define VOS_26M_TIMER_ID     (TIMER_ACPU_OM_TCXO_ID)

/* 记录 VOS 26 timer 可维可测信息 */
VOS_TIMER_SOC_TIMER_INFO_STRU g_st26MSocTimerInfo;

/* the semaphore will be given when 26M's interrupt occures */
VOS_SEM                       g_ulVos26MSem;

/*record start value */
VOS_UINT32                    g_ulVos26MStartValue = ELAPESD_TIME_INVAILD;

#endif
extern VOS_VOID OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_ENUM_UINT32 enNumber);
extern VOS_VOID OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_ENUM_UINT32 enNumber, VOS_UINT32 ulSendPid, VOS_UINT32 ulRcvPid, VOS_UINT32 ulMsgName);
extern VOS_VOID OM_OSAEvent(VOS_VOID *pData, VOS_UINT32 ulLength);

#if (VOS_YES == VOS_26M_TIMER_ENABLE_SOC_TIMER)

/*****************************************************************************
 Function   : VOS_26MDualTimerIsr
 Description: ISR of DualTimer
 Input      :
 Return     :
 Other      :
 *****************************************************************************/
VOS_INT32 VOS_26MDualTimerIsr(VOS_INT lPara)
{
    g_st26MSocTimerInfo.ulExpireCount++;

    if ( VOS_OK != mdrv_timer_stop(lPara) )
    {
        g_st26MSocTimerInfo.ulStopErrCount++;
    }

    /*lint -e534*/
    VOS_SmV(g_ulVos26MSem);
    /*lint +e534*/

    return 0;
}

/*****************************************************************************
 Function   : VOS_Stop26MHardTimer
 Description: stop hard timer
 Input      :
 Return     :
 Other      :
 *****************************************************************************/
VOS_VOID VOS_Stop26MHardTimer(VOS_VOID)
{
    g_st26MSocTimerInfo.ulStopCount++;

    if ( VOS_OK != mdrv_timer_stop(VOS_26M_TIMER_ID) )
    {
        g_st26MSocTimerInfo.ulStopErrCount++;
    }

    g_ulVos26MStartValue = ELAPESD_TIME_INVAILD;

    return;
}

/*****************************************************************************
 Function   : StartHardTimer
 Description: start hard timer
 Input      : value -- timer's value.uint is 32K cycle.
 Return     :
 Other      :
 *****************************************************************************/
VOS_VOID VOS_Start26MHardTimer( VOS_UINT32 value )
{
    g_st26MSocTimerInfo.ulStartCount++;

    VOS_Stop26MHardTimer();

    g_ulVos26MStartValue = value;

    if ( VOS_OK != mdrv_timer_start(VOS_26M_TIMER_ID, (FUNCPTR_1)VOS_26MDualTimerIsr, VOS_26M_TIMER_ID, value, TIMER_ONCE_COUNT,TIMER_UNIT_NONE) )
    {
        g_st26MSocTimerInfo.ulStartErrCount++;
    }

    return;
}

/*****************************************************************************
 Function   : GetHardTimerElapsedTime
 Description: get the elapsed time from hard timer
 Input      :
 Return     :
 Other      :
 *****************************************************************************/
VOS_UINT32 VOS_Get26MHardTimerElapsedTime(VOS_VOID)
{
    VOS_UINT32 ulTempValue = 0;

    if ( ELAPESD_TIME_INVAILD == g_ulVos26MStartValue )
    {
        return 0;
    }

    if ( VOS_OK != mdrv_timer_get_rest_time(VOS_26M_TIMER_ID, TIMER_UNIT_NONE, (VOS_UINT*)&ulTempValue) )
    {
        g_st26MSocTimerInfo.ulElapsedErrCount++;
    }

    if ( g_ulVos26MStartValue < ulTempValue )
    {
        g_st26MSocTimerInfo.ulElapsedContentErrCount++;

        return g_ulVos26MStartValue;
    }

    return g_ulVos26MStartValue - ulTempValue;
}

#endif

/*****************************************************************************
 Function   : VOS_TimerCtrlBlkInit
 Description: Init timer's control block
 Input      : ulTimerCtrlBlkNumber -- number
 Return     : None.
 Other      :
 *****************************************************************************/
VOS_UINT32 VOS_TimerCtrlBlkInit(VOS_VOID)
{
    VOS_UINT32                i;

    vos_TimerCtrlBlkNumber  = VOS_MAX_TIMER_NUMBER;
    vos_TimerIdleCtrlBlkNumber = VOS_MAX_TIMER_NUMBER;

    vos_TimerCtrlBlk = (VOS_TIMER_CONTROL_BLOCK*)g_acVosTimerCtrlBuf;

    vos_TimerIdleCtrlBlk = vos_TimerCtrlBlk;
    vos_TimerCtrlBlkBegin = (VOS_VOID *)vos_TimerCtrlBlk;
    vos_TimerCtrlBlkEnd
        = (VOS_VOID*)( (VOS_UINT_PTR)(vos_TimerCtrlBlk)
              + vos_TimerCtrlBlkNumber * sizeof(VOS_TIMER_CONTROL_BLOCK) );

    for(i=0; i<vos_TimerCtrlBlkNumber-1; i++)
    {
        vos_TimerCtrlBlk[i].State        = VOS_TIMER_CTRL_BLK_STOP;
        vos_TimerCtrlBlk[i].ulUsedFlag   = VOS_NOT_USED;
        vos_TimerCtrlBlk[i].TimerId      = i;
        vos_TimerCtrlBlk[i].ulBackUpTimerId = i;
        vos_TimerCtrlBlk[i].phTm         = VOS_NULL_PTR;
        vos_TimerCtrlBlk[i].CallBackFunc = VOS_NULL_PTR;
        vos_TimerCtrlBlk[i].previous     = VOS_NULL_PTR;
        /* vos_TimerCtrlBlk[i].message_Ptr  = VOS_NULL_PTR; */
        vos_TimerCtrlBlk[i].next         = &(vos_TimerCtrlBlk[i+1]);
    }

    vos_TimerCtrlBlk[vos_TimerCtrlBlkNumber-1].State = VOS_TIMER_CTRL_BLK_STOP;
    vos_TimerCtrlBlk[vos_TimerCtrlBlkNumber-1].ulUsedFlag = VOS_NOT_USED;
    vos_TimerCtrlBlk[vos_TimerCtrlBlkNumber-1].TimerId = vos_TimerCtrlBlkNumber-1;
    vos_TimerCtrlBlk[vos_TimerCtrlBlkNumber-1].ulBackUpTimerId  = vos_TimerCtrlBlkNumber-1;
    vos_TimerCtrlBlk[vos_TimerCtrlBlkNumber-1].phTm = VOS_NULL_PTR;
    vos_TimerCtrlBlk[vos_TimerCtrlBlkNumber-1].CallBackFunc = VOS_NULL_PTR;
    vos_TimerCtrlBlk[vos_TimerCtrlBlkNumber-1].previous = VOS_NULL_PTR;
    /* vos_TimerCtrlBlk[vos_TimerCtrlBlkNumber-1].message_Ptr = VOS_NULL_PTR; */
    vos_TimerCtrlBlk[vos_TimerCtrlBlkNumber-1].next = VOS_NULL_PTR;

    vos_TimerMinTimerIdUsed             = vos_TimerCtrlBlkNumber;

    VOS_SpinLockInit(&g_stVosTimerSpinLock);

#if (VOS_YES == VOS_26M_TIMER_ENABLE_SOC_TIMER)
    /*lint -e534*/
    VOS_MemSet(&g_st26MSocTimerInfo, 0x0, sizeof(VOS_TIMER_SOC_TIMER_INFO_STRU));
    /*lint +e534*/

    if( VOS_OK != VOS_SmCreate("26M", 0, VOS_SEMA4_FIFO, &g_ulVos26MSem))
    {
        Print("# 26M timer creat semaphore error.\r\n");

        return VOS_ERR;
    }
#endif

    return VOS_OK;
}

/*****************************************************************************
 Function   : VOS_TimerCtrlBlkGet
 Description: allocte a block
 Input      : void
 Return     : address
 Other      :
 *****************************************************************************/
VOS_TIMER_CONTROL_BLOCK *VOS_TimerCtrlBlkGet(VOS_UINT32 ulFileID,
                                             VOS_INT32 usLineNo )
{
    /*int                      intLockLevel;*/
    VOS_TIMER_CONTROL_BLOCK  *temp_Timer_Ctrl_Ptr;

    /*intLockLevel = VOS_SplIMP();*/

    if( 0 == vos_TimerIdleCtrlBlkNumber )
    {
        /*VOS_Splx(intLockLevel);*/

        /*lint -e534*/
        VOS_SetErrorNo(VOS_ERRNO_SYSTIMER_FULL);
        /*lint +e534*/

        return((VOS_TIMER_CONTROL_BLOCK*)VOS_NULL_PTR);
    }
    else
    {
        vos_TimerIdleCtrlBlkNumber--;

        temp_Timer_Ctrl_Ptr = vos_TimerIdleCtrlBlk;
        temp_Timer_Ctrl_Ptr->ulUsedFlag = VOS_USED;
        vos_TimerIdleCtrlBlk = vos_TimerIdleCtrlBlk->next;
    }

    /*VOS_Splx(intLockLevel);*/

    /* record the usage of timer control block */
    if ( vos_TimerIdleCtrlBlkNumber < vos_TimerMinTimerIdUsed )
    {
        vos_TimerMinTimerIdUsed = vos_TimerIdleCtrlBlkNumber;
    }

    temp_Timer_Ctrl_Ptr->next = VOS_NULL_PTR;
    temp_Timer_Ctrl_Ptr->previous = VOS_NULL_PTR;

#if VOS_YES == VOS_TIMER_CHECK
    temp_Timer_Ctrl_Ptr->ulFileID = ulFileID;
    temp_Timer_Ctrl_Ptr->ulLineNo = (VOS_UINT32)usLineNo;
    temp_Timer_Ctrl_Ptr->ulAllocTick = VOS_GetSlice();
#endif

    return temp_Timer_Ctrl_Ptr;
}

/*****************************************************************************
 Function   : VOS_TimerCtrlBlkFree
 Description: free a block
 Input      : Ptr -- address
              ucTag -- where call this function.this should be deleted when release
 Return     : void
 Other      :
 *****************************************************************************/
VOS_UINT32 VOS_TimerCtrlBlkFree(VOS_TIMER_CONTROL_BLOCK *Ptr, VOS_UINT8 ucTag )
{
    /*int             intLockLevel;*/

    if ( (VOS_UINT_PTR)Ptr < (VOS_UINT_PTR)vos_TimerCtrlBlkBegin
        || (VOS_UINT_PTR)Ptr > (VOS_UINT_PTR)vos_TimerCtrlBlkEnd )
    {
        return VOS_ERR;
    }

    /*intLockLevel = VOS_SplIMP();*/

    if ( VOS_NOT_USED == Ptr->ulUsedFlag )
    {
        /*VOS_Splx(intLockLevel);*/

        /*lint -e534*/
        VOS_SetErrorNo(VOS_ERRNO_RELTM_FREE_RECEPTION);
        /*lint +e534*/

        return VOS_ERRNO_RELTM_FREE_RECEPTION;
    }

    Ptr->ulUsedFlag = VOS_NOT_USED;
    Ptr->Reserved[0] = ucTag;
    Ptr->next = vos_TimerIdleCtrlBlk;
    vos_TimerIdleCtrlBlk = Ptr;

    vos_TimerIdleCtrlBlkNumber++;

    /*VOS_Splx(intLockLevel);*/

    return VOS_OK;
}

/*****************************************************************************
 Function   : VOS_TimerTaskFunc
 Description: timer task entry
 Input      : void
 Return     : void
 Other      :
 *****************************************************************************/
VOS_VOID VOS_TimerTaskFunc( VOS_UINT32 Para0, VOS_UINT32 Para1,
                            VOS_UINT32 Para2, VOS_UINT32 Para3 )
{
    VOS_TIMER_CONTROL_BLOCK     *head_Ptr;
    /* the timer control which expire */
    VOS_TIMER_CONTROL_BLOCK     *vos_TimerCtrlBlkCurrent;
    /* the timer head control which expire */
    VOS_TIMER_CONTROL_BLOCK     *vos_Timer_expire_head_Ptr = VOS_NULL_PTR;
    VOS_TIMER_CONTROL_BLOCK     *vos_Timer_expire_tail_Ptr = VOS_NULL_PTR;
    VOS_ULONG                    ulLockLevel;
    REL_TIMER_MSG               *pstExpireMsg;
    VOS_UINT32                   ulTempCount;
#if (VOS_YES == VOS_26M_TIMER_ENABLE_SOC_TIMER)
    VOS_UINT32                   ulElapsedCycles;
#endif
    VOS_UINT_PTR                 TempValue;

    vos_CPU_TICK.ulHigh = 0;
    vos_CPU_TICK.ulLow = 0;

    /* here should clear the count SEM when use 10ms INT */

    for(;;)
    {
#if (VOS_YES == VOS_26M_TIMER_ENABLE_SOC_TIMER)
        (VOS_VOID)VOS_SmP(g_ulVos26MSem, 0);
#else
        /* 怀疑delay有问题添加定位信息 */
        OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_4, (VOS_UINT32)(DOPRA_PID_TIMER), (VOS_UINT32)(DOPRA_PID_TIMER), (VOS_UINT32)(DOPRA_PID_TIMER));

        /* SemTake SEM when releas*/
        /*lint -e534*/
        VOS_TaskDelay(9);
        /*lint +e534*/

        OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_4);

        vos_CPU_TICK.ulLow++;

        if ( VOS_TICK_MAX == vos_CPU_TICK.ulLow )
        {
            vos_CPU_TICK.ulHigh++;
            vos_CPU_TICK.ulLow = 0;
        }
#endif

        /*intLockLevel = VOS_SplIMP();*/
        VOS_SpinLockIntLock(&g_stVosTimerSpinLock, ulLockLevel);

#if (VOS_YES == VOS_26M_TIMER_ENABLE_SOC_TIMER)
        ulElapsedCycles = g_ulVos26MStartValue;
        g_ulVos26MStartValue = ELAPESD_TIME_INVAILD;
#endif

        head_Ptr = vos_Timer_head_Ptr;

        if ( head_Ptr != VOS_NULL_PTR)
        {
            /* sub timer value */
#if (VOS_YES == VOS_26M_TIMER_ENABLE_SOC_TIMER)
            head_Ptr->TimeOutValueInTicks -= ulElapsedCycles;
#else
            head_Ptr->TimeOutValueInTicks--;
#endif
            ulTempCount = 0;

            /* check the left timer */
            while ( ( VOS_NULL_PTR != head_Ptr )
                && ( 0 == head_Ptr->TimeOutValueInTicks ) )
            {
                ulTempCount++;
                if ( vos_TimerCtrlBlkNumber < ulTempCount )
                {
                    /*VOS_Splx(intLockLevel);*/
                    VOS_SpinUnlockIntUnlock(&g_stVosTimerSpinLock, ulLockLevel);

                    /*lint -e534*/
                    LogPrint2("# OSA Timer list error.Max %d Count %d.\r\n",
                        (VOS_INT)vos_TimerCtrlBlkNumber, (VOS_INT)ulTempCount);
                    /*lint +e534*/
                    return;
                }

                vos_TimerCtrlBlkCurrent = head_Ptr;

                *(head_Ptr->phTm) = VOS_NULL_PTR;
                /*head_Ptr->State = VOS_TIMER_CTRL_BLK_STOP;*/

                head_Ptr = vos_TimerCtrlBlkCurrent->next;

                vos_TimerCtrlBlkCurrent->next = VOS_NULL_PTR;
                if ( VOS_NULL_PTR == vos_Timer_expire_head_Ptr )
                {
                    vos_Timer_expire_head_Ptr = vos_TimerCtrlBlkCurrent;
                    vos_Timer_expire_tail_Ptr = vos_TimerCtrlBlkCurrent;
                }
                else
                {
                    /*lint -e613*/
                    vos_Timer_expire_tail_Ptr->next = vos_TimerCtrlBlkCurrent;/* [false alarm]: 屏蔽Fortify 错误 */
                    /*lint +e613*/
                    vos_Timer_expire_tail_Ptr = vos_TimerCtrlBlkCurrent;
                }

                vos_Timer_head_Ptr = head_Ptr;
            }

            if ( VOS_NULL_PTR != vos_Timer_head_Ptr )
            {
                vos_Timer_head_Ptr->previous = VOS_NULL_PTR;

#if (VOS_YES == VOS_26M_TIMER_ENABLE_SOC_TIMER)
                if (0 == vos_Timer_head_Ptr->TimeOutValueInTicks)
                {
                    vos_Timer_head_Ptr->TimeOutValueInTicks += 1;
                }

                VOS_Start26MHardTimer(vos_Timer_head_Ptr->TimeOutValueInTicks);
#endif
            }

            /*VOS_Splx(intLockLevel);*/
            VOS_SpinUnlockIntUnlock(&g_stVosTimerSpinLock, ulLockLevel);

            while ( VOS_NULL_PTR != vos_Timer_expire_head_Ptr )
            {
                head_Ptr = vos_Timer_expire_head_Ptr;

                if( VOS_RELTIMER_LOOP == head_Ptr->Mode )
                {
                    /*lint -e534*/
                    if ( VOS_NULL_PTR == head_Ptr->CallBackFunc )
                    {
                        V_Start26MRelTimer(
                            head_Ptr->phTm,
                            head_Ptr->Pid,
                            head_Ptr->TimeOutValueInMilliSeconds,
                            head_Ptr->Name,
                            head_Ptr->Para,
                            VOS_RELTIMER_LOOP,
#if VOS_YES == VOS_TIMER_CHECK
                            head_Ptr->ulFileID,
                            (VOS_INT32)head_Ptr->ulLineNo);
#else
                            VOS_FILE_ID,
                            (VOS_INT32)(__LINE__));
#endif
                    }
                    else
                    {
                         V_Start26MCallBackRelTimer(
                            head_Ptr->phTm,
                            head_Ptr->Pid,
                            head_Ptr->TimeOutValueInMilliSeconds,
                            head_Ptr->Name,
                            head_Ptr->Para,
                            VOS_RELTIMER_LOOP,
                            head_Ptr->CallBackFunc,
#if VOS_YES == VOS_TIMER_CHECK
                            head_Ptr->ulFileID,
                            (VOS_INT32)head_Ptr->ulLineNo);
#else
                            VOS_FILE_ID,
                            (VOS_INT32)(__LINE__));
#endif
                    }
                    /*lint +e534*/
                }

                TempValue = (VOS_UINT_PTR)(vos_Timer_expire_head_Ptr->CallBackFunc);

                /* CallBackFunc需要用32位传入，所以和name互换位置保证数据不丢失 */
                OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_4, (VOS_UINT32)(vos_Timer_expire_head_Ptr->Pid), vos_Timer_expire_head_Ptr->Name, (VOS_UINT32)TempValue);

                if ( VOS_NULL_PTR == vos_Timer_expire_head_Ptr->CallBackFunc )
                {
                    /* Alloc expires's Msg */
                    pstExpireMsg
                        = VOS_TimerPreAllocMsg(vos_Timer_expire_head_Ptr->Pid);

                    if ( VOS_NULL_PTR != pstExpireMsg )
                    {
                        pstExpireMsg->ulName = vos_Timer_expire_head_Ptr->Name;
                        pstExpireMsg->ulPara = vos_Timer_expire_head_Ptr->Para;

                        TempValue            = (VOS_UINT_PTR)(vos_Timer_expire_head_Ptr->TimeOutValueInMilliSeconds);
                        pstExpireMsg->hTm    = (HTIMER)TempValue;

#if (VOS_YES == VOS_TIMER_CHECK)
                        TempValue            = (VOS_UINT_PTR)(vos_Timer_expire_head_Ptr->ulAllocTick);
                        pstExpireMsg->pNext
                            = (struct REL_TIMER_MSG_STRU *)TempValue;

                        TempValue            = (VOS_UINT_PTR)VOS_GetSlice();
                        pstExpireMsg->pPrev
                            = (struct REL_TIMER_MSG_STRU *)TempValue;
#endif

                        if(VOS_OK != VOS_SendMsg( DOPRA_PID_TIMER,
                            pstExpireMsg ))
                        {
                            /*lint -e534*/
                            Print("# OSA Timer task Send Msg Error.\r\n");
                            /*lint +e534*/
                        }
                    }
                }
                else
                {
                   vos_Timer_expire_head_Ptr->CallBackFunc(
                    vos_Timer_expire_head_Ptr->Para,
                    vos_Timer_expire_head_Ptr->Name);
                }

                OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_4);

                vos_Timer_expire_head_Ptr = vos_Timer_expire_head_Ptr->next;

                /* head_Ptr->message_Ptr = VOS_NULL_PTR; */

                VOS_SpinLockIntLock(&g_stVosTimerSpinLock, ulLockLevel);

                /*lint -e534*/
                VOS_TimerCtrlBlkFree(head_Ptr, THE_FIRST_TIMER_TAG);
                /*lint +e534*/

                VOS_SpinUnlockIntUnlock(&g_stVosTimerSpinLock, ulLockLevel);
            }
        }
        else
        {
            /*VOS_Splx(intLockLevel);*/
            VOS_SpinUnlockIntUnlock(&g_stVosTimerSpinLock, ulLockLevel);
        }
    }
}

/*****************************************************************************
 Function   : VOS_TimerPreAllocMsg
 Description: allocte timer expire message's memory
 Input      : void
 Return     : address
 Other      :
 *****************************************************************************/
REL_TIMER_MSG *VOS_TimerPreAllocMsg( VOS_PID Pid )
{
    REL_TIMER_MSG   *pMsg;

    pMsg = (REL_TIMER_MSG*)VOS_AllocTimerMsg(Pid, REL_TIMER_MESSAGE_LENGTH );
    if( VOS_NULL_PTR == pMsg )
    {
        /*lint -e534*/
        LogPrint("# VOS_TimerPreAllocMsg Malloc Error.\r\n");
        /*lint +e534*/
        return VOS_NULL_PTR;
    }

    pMsg->ucType          = VOS_RELATIVE_TIMER;
    pMsg->ucValid         = VOS_TM_INVALID_MSG;
    pMsg->Reserved[0]     = 0;
    pMsg->Reserved[1]     = 0;
    pMsg->pNext           = (struct REL_TIMER_MSG_STRU *)VOS_NULL_PTR;
    pMsg->pPrev           = (struct REL_TIMER_MSG_STRU *)VOS_NULL_PTR;

    return pMsg;
}

/*****************************************************************************
 Function   : VOS_TimerTaskCreat
 Description: create timer task
 Input      : void
 Return     : VOS_OK on success or errno on failure.
 Other      :
 *****************************************************************************/
VOS_UINT32 VOS_TimerTaskCreat(VOS_VOID)
{
    VOS_UINT32 TimerArguments[4] = {0,0,0,0};

    return( VOS_CreateTask( "VOS_TIMER",
                            &vos_TimerTaskId,
                            VOS_TimerTaskFunc,
                            COMM_TIMER_TASK_PRIO,
                            VOS_TIMER_TASK_STACK_SIZE,
                            TimerArguments) );
}

/*****************************************************************************
 Function   : Add_Timer_To_List
 Description: add a timer to list
 Input      : Timer -- the tiemr's adddress
 Return     : void
 Other      :
 *****************************************************************************/
VOS_VOID Add_Timer_To_List( VOS_TIMER_CONTROL_BLOCK  *Timer)
{
    VOS_TIMER_CONTROL_BLOCK  *temp_Ptr;
    VOS_TIMER_CONTROL_BLOCK  *pre_temp_Ptr;
    /*int                      intLockLevel;*/
#if (VOS_YES == VOS_26M_TIMER_ENABLE_SOC_TIMER)
    VOS_UINT32               ElapsedCycles = 0;
#endif

    /*intLockLevel = VOS_SplIMP();*/

    if ( VOS_NULL_PTR == vos_Timer_head_Ptr )
    {
        vos_Timer_head_Ptr = Timer;
    }
    else
    {
#if (VOS_YES == VOS_26M_TIMER_ENABLE_SOC_TIMER)
        ElapsedCycles = VOS_Get26MHardTimerElapsedTime();

        Timer->TimeOutValueInTicks += ElapsedCycles;
#endif

        /*  find the location to insert */
        temp_Ptr = pre_temp_Ptr = vos_Timer_head_Ptr;
        while ( (temp_Ptr != VOS_NULL_PTR)
            && (Timer->TimeOutValueInTicks >= temp_Ptr->TimeOutValueInTicks) )
        {
            Timer->TimeOutValueInTicks -= temp_Ptr->TimeOutValueInTicks;
            pre_temp_Ptr = temp_Ptr;
            temp_Ptr = temp_Ptr->next;
        }

        /* insert timer < head timer*/
        if ( temp_Ptr == vos_Timer_head_Ptr )
        {
            Timer->next = vos_Timer_head_Ptr;
            vos_Timer_head_Ptr = Timer;
        }
        else
        {
            Timer->next = temp_Ptr;
            pre_temp_Ptr->next = Timer;
            Timer->previous = pre_temp_Ptr;
        }

        if ( temp_Ptr != VOS_NULL_PTR )
        {
            temp_Ptr->TimeOutValueInTicks
                = temp_Ptr->TimeOutValueInTicks - Timer->TimeOutValueInTicks;
            temp_Ptr->previous = Timer;
        }
    }

#if (VOS_YES == VOS_26M_TIMER_ENABLE_SOC_TIMER)
    /* restart RTC timer */
    if ( vos_Timer_head_Ptr == Timer)
    {
        /* judge timer value when the new timer at head */
        Timer->TimeOutValueInTicks -= ElapsedCycles;

        if (0 == Timer->TimeOutValueInTicks)
        {
            Timer->TimeOutValueInTicks += 1;
        }

        VOS_Start26MHardTimer(Timer->TimeOutValueInTicks);
    }
#endif

    /*VOS_Splx(intLockLevel);*/
}

/*****************************************************************************
 函 数 名  : VOS_CheckTimer
 功能描述  : 检查TIMER是否正确
 输入参数  : HTIMER  *phTm
             VOS_UINT32 ulFileID
             VOS_INT32 usLineNo
 输出参数  : VOS_UINT32 *ulTimerID
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年5月5日
    作    者   : s00207770
    修改内容   : 规避TimerId被修改导致的检查错误发起主动复位

*****************************************************************************/
VOS_UINT32 VOS_CheckTimer( HTIMER  *phTm, VOS_UINT32 *ulTimerID,
                           VOS_UINT32 ulFileID, VOS_INT32 usLineNo )
{
    VOS_TIMER_CONTROL_BLOCK  *Timer;

    if ( ((VOS_UINT_PTR)*phTm >= (VOS_UINT_PTR)vos_TimerCtrlBlkBegin)
        && ((VOS_UINT_PTR)*phTm < (VOS_UINT_PTR)vos_TimerCtrlBlkEnd) )
    {
        Timer = (VOS_TIMER_CONTROL_BLOCK *)(*phTm);

        if ( phTm == Timer->phTm )
        {
            *ulTimerID = Timer->ulBackUpTimerId;

            if ( Timer->ulBackUpTimerId != Timer->TimerId)
            {
                Timer->TimerId = Timer->ulBackUpTimerId;
            }

            return VOS_OK;
        }

        VOS_SIMPLE_FATAL_ERROR(VOS_CHECK_TIMER_ID);
    }
    else
    {
        VOS_ProtectionReboot(VOS_CHECK_TIMER_RANG, (VOS_INT)ulFileID, (VOS_INT)usLineNo, (VOS_CHAR *)phTm, 128);
    }

    return VOS_ERR;
}

/*****************************************************************************
 Function   : V_StartRelTimer
 Description: Allocate and start a relative timer.
 Input      : Pid       -- process ID of application
              ulLength  -- expire time. the metrics is millsecond
              ulName    -- timer name to be pass to application as a parameter
              ulParam   -- additional parameter to be pass to application
              ucMode    -- timer work mode
                           VOS_RELTIMER_LOOP  -- start periodically
                           VOS_RELTIMER_NOLOO -- start once time
              enPrecision -- precision,unit is 0 - 100->0%- 100%
 Output     : phTm      -- timer address which system retuns to application
 Return     : VOS_OK on success and errno on failure
*****************************************************************************/
VOS_UINT32 V_StartRelTimer( HTIMER *phTm, VOS_PID Pid, VOS_UINT32 ulLength,
    VOS_UINT32 ulName, VOS_UINT32 ulParam, VOS_UINT8 ucMode, VOS_TIMER_PRECISION_ENUM_UINT32 enPrecision,
    VOS_UINT32 ulFileID, VOS_INT32 usLineNo)
{
    VOS_TIMER_OM_EVENT_STRU stTimerEvent;

    if( (ucMode != VOS_RELTIMER_LOOP) && (ucMode != VOS_RELTIMER_NOLOOP) )
    {
        /*lint -e534*/
        VOS_SetErrorNo(VOS_ERRNO_RELTM_START_INPUTMODEINVALID);

        LogPrint2( "# VOS_StartRelTimer Error: ucMode.F %d L %d.\r\n",
            (VOS_INT)ulFileID, usLineNo);
        /*lint +e534*/

        VOS_SIMPLE_FATAL_ERROR(START_RELTIMER_FLASE_MODE);

        return(VOS_ERRNO_RELTM_START_INPUTMODEINVALID);
    }

    if ( VOS_NULL_PTR == phTm )
    {
        /*lint -e534*/
        LogPrint2( "# VOS_StartRelTimer Error: phTm null.F %d L %d.\r\n",
            (VOS_INT)ulFileID, usLineNo);
        /*lint +e534*/

        VOS_SIMPLE_FATAL_ERROR(START_RELTIMER_NULL);

        return VOS_ERR;
    }

    if ( ulLength > VOS_TIMER_MAX_LENGTH )
    {
        /*lint -e534*/
        LogPrint2("# Timer's length is too big.F %d L %d.\r\n",
            (VOS_INT)ulFileID, usLineNo);
        /*lint +e534*/

        VOS_SIMPLE_FATAL_ERROR(START_RELTIMER_TOO_BIG);

        return VOS_ERR;
    }

    if ( VOS_TIMER_PRECISION_BUTT <= enPrecision )
    {
        /*lint -e534*/
        LogPrint2("# Timer's Precision is too big.F %d L %d.\r\n",
            (VOS_INT)ulFileID, usLineNo);
        /*lint +e534*/

        VOS_SIMPLE_FATAL_ERROR(START_RELTIMER_PRECISION_TOO_BIG);

        return VOS_ERR;
    }

    if ((VOS_TIMER_PRECISION_100 == enPrecision)
        && (VOS_RELTIMER_LOOP == ucMode))
    {
        /*lint -e534*/
        LogPrint2("# Timer's para is wrong.F %d L %d.\r\n",
            (VOS_INT)ulFileID, usLineNo);
        /*lint +e534*/

        return VOS_ERR;
    }

    if ( ulLength < MILLISECONDS_PER_TICK )
    {
        ulLength = MILLISECONDS_PER_TICK;
    }

#if (VOS_WIN32 == VOS_OS_VER)
    ulLength = ulLength * g_ulMagnifyTimerLength;
#endif

    stTimerEvent.ucAction    = VOS_TIMER_OM_START;
    stTimerEvent.ucMode      = ucMode;
    stTimerEvent.ucType      = VOS_DELTM_ON_TIMEOUTMSG;
    stTimerEvent.Pid         = Pid;
    stTimerEvent.ulLength    = ulLength;
    stTimerEvent.ulName      = ulName;
    stTimerEvent.ulParam     = ulParam;
    stTimerEvent.enPrecision = enPrecision;

    OM_OSAEvent( (VOS_VOID *)&stTimerEvent, sizeof(VOS_TIMER_OM_EVENT_STRU));

#if (VOS_32K_TIMER_ENABLE == VOS_YES)

#if ((VOS_VXWORKS == VOS_OS_VER) || (VOS_NUCLEUS == VOS_OS_VER) \
        || (VOS_LINUX == VOS_OS_VER) || (VOS_RTOSCK == VOS_OS_VER))
    if  ( VOS_TIMER_NO_PRECISION != enPrecision )
    {
        return V_Start32KRelTimer( phTm, Pid, ulLength, ulName, ulParam,
            ucMode, enPrecision, ulFileID, usLineNo);
    }
#endif

#endif

    return V_Start26MRelTimer(phTm, Pid, ulLength, ulName, ulParam,
        ucMode, ulFileID, usLineNo);
}

/*****************************************************************************
 Function   : V_Start26MRelTimer
 Description: Allocate and start a 26M relative timer.
 Input      : Pid       -- process ID of application
              ulLength  -- expire time. the metrics is millsecond
              ulName    -- timer name to be pass to application as a parameter
              ulParam   -- additional parameter to be pass to application
              ucMode    -- timer work mode
                           VOS_RELTIMER_LOOP  -- start periodically
                           VOS_RELTIMER_NOLOO -- start once time
 Output     : phTm      -- timer address which system retuns to application
 Return     : VOS_OK on success and errno on failure
*****************************************************************************/
VOS_UINT32 V_Start26MRelTimer( HTIMER *phTm, VOS_PID Pid, VOS_UINT32 ulLength,
    VOS_UINT32 ulName, VOS_UINT32 ulParam, VOS_UINT8 ucMode,
    VOS_UINT32 ulFileID, VOS_INT32 usLineNo)
{
    VOS_TIMER_CONTROL_BLOCK  *Timer;
    VOS_UINT32               TimerId;
    VOS_ULONG                ulLockLevel;

    /* stop the timer if exists */
    /*intLockLevel = VOS_SplIMP();*/
    VOS_SpinLockIntLock(&g_stVosTimerSpinLock, ulLockLevel);

    if( VOS_NULL_PTR != *phTm )
    {
        if ( VOS_OK == VOS_CheckTimer( phTm, &TimerId, ulFileID, usLineNo ) )
        {
            if ( VOS_OK != V_Stop26MRelTimer(phTm, ulFileID, usLineNo, VOS_NULL_PTR) )
            {
                /*VOS_Splx(intLockLevel);*/
                VOS_SpinUnlockIntUnlock(&g_stVosTimerSpinLock, ulLockLevel);

                VOS_SIMPLE_FATAL_ERROR(START_26M_RELTIMER_FAIL_TO_STOP);

                return VOS_ERR;
            }
        }
    }

    Timer = VOS_TimerCtrlBlkGet(ulFileID, usLineNo);

    if( VOS_NULL_PTR == Timer )
    {
        /*VOS_Splx(intLockLevel);*/
        VOS_SpinUnlockIntUnlock(&g_stVosTimerSpinLock, ulLockLevel);

        /*lint -e534*/
        VOS_SetErrorNo(VOS_ERRNO_RELTM_START_MSGNOTINSTALL);
        /*lint +e534*/

        VOS_TimerDump(START_26M_RELTIMER_FAIL_TO_ALLOCATE, ulFileID, (VOS_UINT32)usLineNo);

        return(VOS_ERRNO_RELTM_START_MSGNOTINSTALL);
    }

    /*if( VOS_NULL_PTR != phTm )
    {
        *phTm = (HTIMER)(&(Timer->TimerId));
    }*/

    Timer->Pid                          = Pid;
    Timer->Name                         = ulName;
    Timer->Para                         = ulParam;
    Timer->Mode                         = ucMode;
    Timer->phTm                         = phTm;
    Timer->TimeOutValueInMilliSeconds   = ulLength;
#if (VOS_YES == VOS_26M_TIMER_ENABLE_SOC_TIMER)

#ifdef FLOAT_SUPPORT
#ifdef V8R1_SINGLECLOCK
    if (UCOM_NV_32K_TYPE_32000 == g_usSingleXO)
    {
        Timer->TimeOutValueInTicks  = (VOS_UINT32)(RTC_SINGLECLOCK_CYCLE_LENGTH * ulLength);
    }
    else
#endif
    {
        Timer->TimeOutValueInTicks  = (VOS_UINT32)(RTC_CYCLE_LENGTH * ulLength);
    }
#else
    Timer->TimeOutValueInTicks = (VOS_UINT32)RTC_MUL_32_DOT_768(ulLength, ulFileID, usLineNo);
#endif

#else
    Timer->TimeOutValueInTicks          = ulLength/MILLISECONDS_PER_TICK;
#endif

    /*Timer->State                        = VOS_TIMER_CTRL_BLK_RUNNIG;*/
    Timer->CallBackFunc                 = VOS_NULL_PTR;
    /*Timer->next                         = VOS_NULL_PTR;*/

    *phTm = (HTIMER)(&(Timer->TimerId));

    /* add the timer to the running list */
    Add_Timer_To_List( Timer );

    /*VOS_Splx(intLockLevel);*/
    VOS_SpinUnlockIntUnlock(&g_stVosTimerSpinLock, ulLockLevel);

    return(VOS_OK);
}

/*****************************************************************************
 Function   : Del_Timer_From_List
 Description: del a timer from list
 Input      : Timer -- the timer's address
 Return     : void
 Other      :
 *****************************************************************************/
VOS_VOID Del_Timer_From_List( VOS_TIMER_CONTROL_BLOCK  *Timer)
{
#if (VOS_YES == VOS_26M_TIMER_ENABLE_SOC_TIMER)
     VOS_BOOL                  bIsHead = VOS_FALSE;
#endif
    /*int                      intLockLevel;*/

    /*intLockLevel = VOS_SplIMP();*/

    /* deletet this timer from list */
    if ( Timer == vos_Timer_head_Ptr )
    {
#if (VOS_YES == VOS_26M_TIMER_ENABLE_SOC_TIMER)
        bIsHead = VOS_TRUE;
#endif

        vos_Timer_head_Ptr = Timer->next;
        if ( VOS_NULL_PTR != vos_Timer_head_Ptr )
        {
            vos_Timer_head_Ptr->previous = VOS_NULL_PTR;
        }
    }
    else
    {
        (Timer->previous)->next = Timer->next;
        if ( VOS_NULL_PTR != Timer->next )
        {
            (Timer->next)->previous = Timer->previous;
        }
    }

    /* adjust the time_val after this timer */
    if ( Timer->next != NULL )
    {
        Timer->next->TimeOutValueInTicks += Timer->TimeOutValueInTicks;

#if (VOS_YES == VOS_26M_TIMER_ENABLE_SOC_TIMER)
        if (VOS_TRUE == bIsHead)
        {
            Timer->next->TimeOutValueInTicks -= VOS_Get26MHardTimerElapsedTime();

            if (0 == Timer->next->TimeOutValueInTicks)
            {
                Timer->next->TimeOutValueInTicks += 1;
            }

            VOS_Start26MHardTimer(Timer->next->TimeOutValueInTicks);
        }
#endif
    }

#if (VOS_YES == VOS_26M_TIMER_ENABLE_SOC_TIMER)
    /* Stop soc timer if no timer */
    if ( VOS_NULL_PTR == vos_Timer_head_Ptr )
    {
        VOS_Stop26MHardTimer();
    }
#endif

    /*VOS_Splx(intLockLevel);*/
}

/*****************************************************************************
 Function   : V_Stop26MRelTimer
 Description: stop a relative timer which was previously started.
 Input      : phTm -- where store the timer to be stopped
 Return     :  VOS_OK on success or errno on failure
 *****************************************************************************/
VOS_UINT32 V_Stop26MRelTimer( HTIMER *phTm, VOS_UINT32 ulFileID, VOS_INT32 lLineNo, VOS_TIMER_OM_EVENT_STRU *pstEvent )
{
    VOS_UINT32               TimerId;
    VOS_TIMER_CONTROL_BLOCK  *Timer;
    /*int                      intLockLevel;*/

    /*intLockLevel = VOS_SplIMP();*/

    if( VOS_NULL_PTR == *phTm )
    {
        /*VOS_Splx(intLockLevel);*/

        return VOS_OK;
    }

    if ( VOS_OK != VOS_CheckTimer( phTm, &TimerId, ulFileID, lLineNo ) )
    {
        /*VOS_Splx(intLockLevel);*/

        /*lint -e534*/
        VOS_SetErrorNo(VOS_ERRNO_RELTM_STOP_TIMERINVALID);
        /*lint +e534*/
        return(VOS_ERRNO_RELTM_STOP_TIMERINVALID);
    }

    Timer   = &vos_TimerCtrlBlk[TimerId];

    /* del the timer from the running list */
    Del_Timer_From_List( Timer );

    *(Timer->phTm) = VOS_NULL_PTR;

     /* OM */
    if ( VOS_NULL_PTR != pstEvent )
    {
        pstEvent->ucMode      = Timer->Mode;
        pstEvent->Pid         = Timer->Pid;
        pstEvent->ulLength    = Timer->TimeOutValueInMilliSeconds;
        pstEvent->ulName      = Timer->Name;
        pstEvent->ulParam     = Timer->Para;
        pstEvent->enPrecision = VOS_TIMER_NO_PRECISION;
    }

    /*VOS_Splx(intLockLevel);*/

    /*Timer->State = VOS_TIMER_CTRL_BLK_STOP;*/

    return VOS_TimerCtrlBlkFree(Timer, THE_SECOND_TIMER_TAG);
}

/*****************************************************************************
 Function   : V_StopRelTimer
 Description: stop a relative timer which was previously started.
 Input      : phTm -- where store the timer to be stopped
 Return     :  VOS_OK on success or errno on failure
 *****************************************************************************/
VOS_UINT32 V_StopRelTimer( HTIMER *phTm, VOS_UINT32 ulFileID, VOS_INT32 usLineNo )
{
    VOS_ULONG                ulLockLevel;
    VOS_UINT32               ulReturn;
    VOS_TIMER_OM_EVENT_STRU  stTimerEvent;

    if( VOS_NULL_PTR == phTm )
    {
        /*lint -e534*/
        VOS_SetErrorNo(VOS_ERRNO_RELTM_STOP_INPUTISNULL);
        /*lint +e534*/
        return(VOS_ERRNO_RELTM_STOP_INPUTISNULL);
    }

    /*intLockLevel = VOS_SplIMP();*/
    VOS_SpinLockIntLock(&g_stVosTimerSpinLock, ulLockLevel);

    if ( VOS_TRUE != VOS_Is26MTimer(phTm) )
    {
        ulReturn = R_Stop32KTimer(phTm, ulFileID, usLineNo, &stTimerEvent);
    }
    else
    {
        ulReturn = V_Stop26MRelTimer(phTm, ulFileID, usLineNo, &stTimerEvent);
    }

    /*VOS_Splx(intLockLevel);*/
    VOS_SpinUnlockIntUnlock(&g_stVosTimerSpinLock, ulLockLevel);

    stTimerEvent.ucAction = VOS_TIMER_OM_STOP;
    stTimerEvent.ucResult = (VOS_UINT8)ulReturn;

    OM_OSAEvent( (VOS_VOID *)&stTimerEvent, sizeof(VOS_TIMER_OM_EVENT_STRU));

    return ulReturn;
}

/*****************************************************************************
 Function   : V_RestartRelTimer
 Description: Restart a relative timer which was previously started
 Input      : phTm -- where store timer ID to be restarted
 Return     : VOS_OK on success or errno on failure.
 Other      : the properties of timer should not be changed,
              but timer ID could have been changed
 *****************************************************************************/
VOS_UINT32 V_RestartRelTimer( HTIMER *phTm, VOS_UINT32 ulFileID,
                              VOS_INT32 usLineNo )
{
    VOS_UINT32               TimerId;
    VOS_TIMER_CONTROL_BLOCK  *Timer;
    VOS_ULONG                ulLockLevel;
    VOS_UINT32               ulReturn;
    VOS_TIMER_OM_EVENT_STRU  stTimerEvent;

    if( VOS_NULL_PTR == phTm )
    {
        /*lint -e534*/
        Print( "# VOS_RestartRelTimer Error: phTm null.");
        /*lint +e534*/

        VOS_SIMPLE_FATAL_ERROR(RESTART_RELTIMER_NULL);

        /*lint -e534*/
        VOS_SetErrorNo(VOS_ERRNO_RELTM_RESTART_INPUTISNULL);
        /*lint +e534*/
        return(VOS_ERRNO_RELTM_RESTART_INPUTISNULL);
    }

    /*intLockLevel = VOS_SplIMP();*/
    VOS_SpinLockIntLock(&g_stVosTimerSpinLock, ulLockLevel);

    if ( VOS_TRUE != VOS_Is26MTimer(phTm) )
    {
        ulReturn = R_Restart32KRelTimer(phTm, ulFileID, usLineNo);

        /*VOS_Splx(intLockLevel);*/
        VOS_SpinUnlockIntUnlock(&g_stVosTimerSpinLock, ulLockLevel);

        return ulReturn;
    }

    if( VOS_NULL_PTR == *phTm )
    {
        /*VOS_Splx(intLockLevel);*/
        VOS_SpinUnlockIntUnlock(&g_stVosTimerSpinLock, ulLockLevel);

        /*lint -e534*/
        VOS_SetErrorNo(VOS_ERRNO_RELTM_RESTART_TIMERINVALID);
        /*lint +e534*/

        VOS_SIMPLE_FATAL_ERROR(RESTART_RELTIMER_NOT_RUNNING);

        return(VOS_ERRNO_RELTM_RESTART_TIMERINVALID);
    }

    if ( VOS_OK != VOS_CheckTimer( phTm, &TimerId, ulFileID, usLineNo ) )
    {
        /*VOS_Splx(intLockLevel);*/
        VOS_SpinUnlockIntUnlock(&g_stVosTimerSpinLock, ulLockLevel);

        /*lint -e534*/
        VOS_SetErrorNo(VOS_ERRNO_RELTM_RESTART_TIMERINVALID);
        /*lint +e534*/

        VOS_SIMPLE_FATAL_ERROR(RESTART_RELTIMER_FAIL_TO_CHECK);

        return(VOS_ERRNO_RELTM_RESTART_TIMERINVALID);
    }

    Timer   = &vos_TimerCtrlBlk[TimerId];

    /* Del the old timer but not free timer control block */
    Del_Timer_From_List( Timer );
#if (VOS_YES == VOS_26M_TIMER_ENABLE_SOC_TIMER)

#ifdef FLOAT_SUPPORT
#ifdef V8R1_SINGLECLOCK
    if (UCOM_NV_32K_TYPE_32000 == g_usSingleXO)
    {
        Timer->TimeOutValueInTicks
            = (VOS_UINT32)(RTC_SINGLECLOCK_CYCLE_LENGTH * Timer->TimeOutValueInMilliSeconds);
    }
    else
#endif
    {
        Timer->TimeOutValueInTicks
            = (VOS_UINT32)(RTC_CYCLE_LENGTH * Timer->TimeOutValueInMilliSeconds);
    }
#else
    Timer->TimeOutValueInTicks = (VOS_UINT32)RTC_MUL_32_DOT_768(Timer->TimeOutValueInMilliSeconds, ulFileID, usLineNo);
#endif

#else
    /* reset timer value */
    Timer->TimeOutValueInTicks
        = Timer->TimeOutValueInMilliSeconds/MILLISECONDS_PER_TICK;
#endif

    Timer->next = VOS_NULL_PTR;
    Timer->previous = VOS_NULL_PTR;

    /* add the new timer to list */
    Add_Timer_To_List( Timer );

    /*VOS_Splx(intLockLevel);*/
    VOS_SpinUnlockIntUnlock(&g_stVosTimerSpinLock, ulLockLevel);

    stTimerEvent.ucAction = VOS_TIMER_OM_RESTART;
    stTimerEvent.ucResult = (VOS_UINT8)VOS_OK;

    OM_OSAEvent( (VOS_VOID *)&stTimerEvent, sizeof(VOS_TIMER_OM_EVENT_STRU));

    return VOS_OK;
}

/*****************************************************************************
 Function     : V_GetRelTmRemainTime
 Description  : get left time
 Input Param  : phTm
 Output       : pulTick
 Return Value : VOS_OK on success or errno on failure
*****************************************************************************/
VOS_UINT32 V_GetRelTmRemainTime( HTIMER * phTm, VOS_UINT32 * pulTick,
                                 VOS_UINT32 ulFileID, VOS_INT32 usLineNo )
{
    VOS_UINT32                  TimerId;
    VOS_UINT32                  remain_value = 0;
    VOS_TIMER_CONTROL_BLOCK     *head_Ptr;
    VOS_TIMER_CONTROL_BLOCK     *temp_Ptr;
    VOS_ULONG                   ulLockLevel;
    VOS_UINT32                  ulTempTick;

    if( VOS_NULL_PTR == phTm )
    {
        /*lint -e534*/
        Print2("# VOS_GetRelTmRemainTime Error: phTm null.F %d L %d.\r\n",
            (VOS_INT)ulFileID, usLineNo);

        VOS_SetErrorNo(VOS_ERRNO_RELTM_STOP_INPUTISNULL);
        /*lint +e534*/
        return(VOS_ERRNO_RELTM_STOP_INPUTISNULL);
    }

    /*intLockLevel = VOS_SplIMP();*/
    VOS_SpinLockIntLock(&g_stVosTimerSpinLock, ulLockLevel);

    if ( VOS_TRUE != VOS_Is26MTimer(phTm) )
    {
        if ( VOS_OK == R_Get32KRelTmRemainTime(phTm, &ulTempTick,
            ulFileID, usLineNo) )
        {
            *pulTick = ulTempTick/MILLISECONDS_PER_TICK;

            /*VOS_Splx(intLockLevel);*/
            VOS_SpinUnlockIntUnlock(&g_stVosTimerSpinLock, ulLockLevel);

            return VOS_OK;

        }

        /*VOS_Splx(intLockLevel);*/
        VOS_SpinUnlockIntUnlock(&g_stVosTimerSpinLock, ulLockLevel);

        return VOS_ERR;
    }

    if( VOS_NULL_PTR == *phTm )
    {
        /*VOS_Splx(intLockLevel);*/
        VOS_SpinUnlockIntUnlock(&g_stVosTimerSpinLock, ulLockLevel);

        /*lint -e534*/
        VOS_SetErrorNo(VOS_ERRNO_RELTM_STOP_INPUTISNULL);
        /*lint +e534*/
        return(VOS_ERRNO_RELTM_STOP_INPUTISNULL);
    }

    if ( VOS_OK != VOS_CheckTimer( phTm, &TimerId, ulFileID, usLineNo ) )
    {
        /*VOS_Splx(intLockLevel);*/
        VOS_SpinUnlockIntUnlock(&g_stVosTimerSpinLock, ulLockLevel);

        /*lint -e534*/
        VOS_SetErrorNo(VOS_ERRNO_RELTM_STOP_TIMERINVALID);
        /*lint +e534*/
        return(VOS_ERRNO_RELTM_STOP_TIMERINVALID);
    }

    head_Ptr = vos_Timer_head_Ptr;

    while ( (VOS_NULL_PTR != head_Ptr) && (head_Ptr->TimerId != TimerId) )
    {
        remain_value += (head_Ptr->TimeOutValueInTicks);

        temp_Ptr = head_Ptr;
        head_Ptr = temp_Ptr->next;
    }

    if ( (VOS_NULL_PTR == head_Ptr) || ( head_Ptr->TimerId != TimerId) )
    {
        /*VOS_Splx(intLockLevel);*/
        VOS_SpinUnlockIntUnlock(&g_stVosTimerSpinLock, ulLockLevel);

        return VOS_ERR;
    }
    else
    {
        remain_value += (head_Ptr->TimeOutValueInTicks);

#if (VOS_YES == VOS_26M_TIMER_ENABLE_SOC_TIMER)
        ulTempTick = VOS_Get26MHardTimerElapsedTime();

#ifdef FLOAT_SUPPORT
#ifdef V8R1_SINGLECLOCK
        if (UCOM_NV_32K_TYPE_32000 == g_usSingleXO)
        {
            *pulTick
                = (VOS_UINT32)(( (remain_value - ulTempTick) / RTC_SINGLECLOCK_CYCLE_LENGTH )/MILLISECONDS_PER_TICK);
        }
        else
#endif
        {
            *pulTick
                = (VOS_UINT32)(( (remain_value - ulTempTick) / RTC_CYCLE_LENGTH )/MILLISECONDS_PER_TICK);
        }
#else
        *pulTick
            = (VOS_UINT32)(RTC_DIV_32_DOT_768((remain_value - ulTempTick), ulFileID, usLineNo)/MILLISECONDS_PER_TICK);
#endif

#else
        *pulTick = remain_value;
#endif

        /*VOS_Splx(intLockLevel);*/
        VOS_SpinUnlockIntUnlock(&g_stVosTimerSpinLock, ulLockLevel);

        return(VOS_OK);
    }
}

/*****************************************************************************
 Function   : VOS_Is26MTimer
 Description: Check time is 32K or 26M.
 Input      : phTm     -- Point to timer to check
 Return     : VOS_TRUE  -- Valid
              VOS_FALSE -- Not Valid
 *****************************************************************************/
VOS_BOOL VOS_Is26MTimer( HTIMER *phTm )
{
    /*int                      intLockLevel;*/

    /*intLockLevel = VOS_SplIMP();*/

    if ( ((VOS_UINT_PTR)*phTm >= (VOS_UINT_PTR)vos_TimerCtrlBlkBegin)
        && ((VOS_UINT_PTR)*phTm < (VOS_UINT_PTR)vos_TimerCtrlBlkEnd) )
    {
        /*VOS_Splx(intLockLevel);*/

        return VOS_TRUE;
    }

    /*VOS_Splx(intLockLevel);*/

    return VOS_FALSE;
}

#if ((VOS_VXWORKS == VOS_OS_VER) || (VOS_NUCLEUS== VOS_OS_VER))

/*****************************************************************************
 Function   : OSAL_TmGet
 Description: get system time
 Input      : pSysTime -- system
 Return     : VOS_OK on success or errno on failure.
 Other      :
 *****************************************************************************/
VOS_UINT32 OSAL_TmGet( SYS_T * pSysTime )
{
    time_t      timer;
    struct tm  *tblock;
    VOS_INT32   lReturnCode;

    if( VOS_NULL_PTR == pSysTime )
    {
        return VOS_ERR;
    }

    lReturnCode = ( VOS_INT32 )time( &timer );

    if( -1 == lReturnCode )
    {
        pSysTime->uwYear   = 0;
        pSysTime->ucMonth  = 0;
        pSysTime->ucDate   = 0;
        pSysTime->ucHour   = 0;
        pSysTime->ucMinute = 0;
        pSysTime->ucSecond = 0;

        return VOS_ERR;
    }

    tblock = localtime( &timer );

    pSysTime->uwYear   = ( VOS_UINT16 )tblock->tm_year + 1900;
    pSysTime->ucMonth  = ( VOS_UINT8 )tblock->tm_mon + 1;
    pSysTime->ucDate   = ( VOS_UINT8 )tblock->tm_mday;
    pSysTime->ucHour   = ( VOS_UINT8 )tblock->tm_hour;
    pSysTime->ucMinute = ( VOS_UINT8 )tblock->tm_min;
    pSysTime->ucSecond = ( VOS_UINT8 )tblock->tm_sec;
    return VOS_OK;
}

#endif

#if (VOS_WIN32 == VOS_OS_VER)

/*****************************************************************************
 Function   : OSAL_TmGet()
 Description: To get the date and times of commercial operation
 Input      : None
 Output     : pSysTime -- Pointer to store the date and times
 Return     : VOS_OK on success or errno on failure
 *****************************************************************************/
VOS_UINT32 OSAL_TmGet( SYS_T * pSysTime )
{
    struct tm * tblock;
    time_t timer;

    if( VOS_NULL_PTR == pSysTime )
    {
        return VOS_ERR;
    }

    time( &timer );
    tblock = localtime( &timer );

    if( VOS_NULL_PTR == tblock )
    {
        return VOS_ERR;
    }

    pSysTime->uwYear   = ( VOS_UINT16 )( tblock->tm_year + 1900 );
    pSysTime->ucMonth  = ( VOS_UINT8 )( tblock->tm_mon + 1 );
    pSysTime->ucDate   = ( VOS_UINT8 )( tblock->tm_mday );
    pSysTime->ucHour   = ( VOS_UINT8 )( tblock->tm_hour );
    pSysTime->ucMinute = ( VOS_UINT8 )( tblock->tm_min );
    pSysTime->ucSecond = ( VOS_UINT8 )( tblock->tm_sec );

    return VOS_OK;
}

#endif

#if ( (VOS_WIN32 == VOS_OS_VER) || ( VOS_VXWORKS == VOS_OS_VER ) || (VOS_NUCLEUS== VOS_OS_VER) )

#ifndef DMT
/*****************************************************************************
 Function   : VOS_GetSysTime
 Description: Get the system time
 Input      : None
 Output     : pSysTime -- If this function is returned successfully,
                          pSysTime will be the system date/time/week day
 Return     : VOS_OK on success, Error code on failure
 *****************************************************************************/
VOS_UINT32 VOS_GetSysTime( SYS_T *pSysTime )
{
    VOS_UINT32  ulTmpDate1, ulTmpDate2;

    if( VOS_NULL_PTR == pSysTime )
    {
        /*lint -e534*/
        VOS_SetErrorNo(VOS_ERRNO_SYSTIME_GETSYST_INPUTPARAISNULL);
        /*lint +e534*/
        return VOS_ERRNO_SYSTIME_GETSYST_INPUTPARAISNULL;
    }

    if ( VOS_OK != OSAL_TmGet(&g_SysTime) )
    {
        return VOS_ERR;
    }

    pSysTime->uwYear   = g_SysTime.uwYear;
    pSysTime->ucMonth  = g_SysTime.ucMonth;
    pSysTime->ucDate   = g_SysTime.ucDate;
    pSysTime->ucHour   = g_SysTime.ucHour;
    pSysTime->ucMinute = g_SysTime.ucMinute;
    pSysTime->ucSecond = g_SysTime.ucSecond;

    /*lint -e701 */
    ulTmpDate1 = ( pSysTime->uwYear << 16 )
        + ( pSysTime->ucMonth << 8 ) + pSysTime->ucDate;
    ulTmpDate2 = ( g_SysTime.uwYear << 16 )
        + ( g_SysTime.ucMonth << 8 ) + g_SysTime.ucDate;
    /*lint +e701 */

    if ( ulTmpDate1 > ulTmpDate2 )
    {
        pSysTime->ucWeek = ( g_SysTime.ucWeek + 1 ) % 7;
    }
    else if ( ulTmpDate1 < ulTmpDate2 )
    {
        pSysTime->ucWeek = ( g_SysTime.ucWeek + 6 ) % 7;
    }
    else
    {
        pSysTime->ucWeek = g_SysTime.ucWeek ;
    }

    return VOS_OK;
}
#endif /* DMT */

#endif

#if (VOS_RTOSCK == VOS_OS_VER)

/*****************************************************************************
 Function   : VOS_GetSysTime
 Description: Get the system time
 Input      : None
 Output     : pSysTime -- If this function is returned successfully,
                          pSysTime will be the system date/time/week day
 Return     : VOS_OK on success, Error code on failure
 *****************************************************************************/
VOS_UINT32 VOS_GetSysTime( SYS_T *pSysTime )
{
    /* There is no time API in RTOSck OS.*/
    return VOS_OK;
}

#endif

#if (VOS_LINUX == VOS_OS_VER)

/* Nonzero if YEAR is a leap year (every 4 years,
   except every 100th isn't, and every 400th is).  */

#define    __isleap(year)  \
    ((year) % 4 == 0 && ((year) % 100 != 0 || (year) % 400 == 0))

/* How many days are in each month.  */
const unsigned short int __mon_lengths[2][12] =
{
    /* Normal years.  */
    { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },

    /* Leap years.  */
    { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
};

#define    SECS_PER_HOUR   (60 * 60)

#define    SECS_PER_DAY    (SECS_PER_HOUR * 24)

/*****************************************************************************
 Function   : OSAL_gmtime
 Description: Get the system time
 Input      : None
 Output     :
 Return     :
 *****************************************************************************/
SYS_T *OSAL_gmtime(const time_t *pSec)
{
   static SYS_T tbuf;

   register long days, seconds_left;

   register int y;

   register int days_per_year;

   const unsigned short int *ip;

   days = *pSec/ SECS_PER_DAY;

   seconds_left = *pSec%SECS_PER_DAY;

   while ( 0 > seconds_left )
   {
       seconds_left += SECS_PER_DAY;
       --days;
   }

   while (seconds_left >= SECS_PER_DAY)
   {
       seconds_left -= SECS_PER_DAY;
       ++days;
   }

   tbuf.ucHour = seconds_left/SECS_PER_HOUR;

   seconds_left %= SECS_PER_HOUR;

   tbuf.ucMinute = seconds_left/60;

   tbuf.ucSecond = seconds_left%60;

   /* January 1, 1970 was a Thursday.  */
   tbuf.ucWeek = (4 + days) % 7;

   y = 1970;

   while (days >= (days_per_year = __isleap(y) ? 366 : 365))
   {
       ++y;
       days -= days_per_year;
   }

   while (days < 0)
   {
       --y;
       days += __isleap(y) ? 366 : 365;
   }

   tbuf.uwYear = y;

   ip = __mon_lengths[__isleap(y)];

   for (y = 0; days >= ip[y]; ++y)
   {
        days -= ip[y];
   }

   tbuf.ucMonth = y + 1;

   tbuf.ucDate = days;

   return &tbuf;
}


/*****************************************************************************
 Function   : VOS_GetSysTime
 Description: Get the system time
 Input      : None
 Output     : pSysTime -- If this function is returned successfully,
                          pSysTime will be the system date/time/week day
 Return     : VOS_OK on success, Error code on failure
 *****************************************************************************/
VOS_UINT32 VOS_GetSysTime( SYS_T *pSysTime )
{
    struct timeval tv;

    SYS_T *pSysTimeSrc;

    if( VOS_NULL_PTR == pSysTime )
    {
        /*lint -e534*/
        VOS_SetErrorNo(VOS_ERRNO_SYSTIME_GETSYST_INPUTPARAISNULL);
        /*lint +e534*/
        return VOS_ERRNO_SYSTIME_GETSYST_INPUTPARAISNULL;
    }

    do_gettimeofday(&tv);

    pSysTimeSrc = OSAL_gmtime(&tv.tv_sec);

    memcpy(pSysTime, pSysTimeSrc, sizeof(SYS_T));

    return VOS_OK;
}

#endif

#if (VOS_RTOSCK == VOS_OS_VER)
VOS_UINT32 VOS_GetTick( VOS_VOID )
{
    return (VOS_UINT32)SRE_TickCountGet();
}
#endif

#if (VOS_VXWORKS == VOS_OS_VER)

extern VOS_UINT32 tickGet (VOS_VOID);

VOS_UINT32 VOS_GetTick( VOS_VOID )
{
    /*return vos_CPU_TICK.ulLow;*/

    return tickGet();
}

#endif

#if (VOS_WIN32 == VOS_OS_VER)
#ifndef DMT
VOS_UINT32 VOS_GetTick( VOS_VOID )
{
    return vos_CPU_TICK.ulLow;
}
#endif /* DMT */
#endif

#if ( VOS_LINUX == VOS_OS_VER )
VOS_UINT32 VOS_GetTick( VOS_VOID )
{
    return (VOS_UINT32)jiffies;
}
#endif


#if (VOS_NUCLEUS == VOS_OS_VER)

extern VOS_UINT32 NU_Retrieve_Clock(VOS_VOID);

VOS_UINT32 VOS_GetTick( VOS_VOID )
{
    /*return vos_CPU_TICK.ulLow;*/

    return NU_Retrieve_Clock();
}

#endif

/*****************************************************************************
 Function   : VOS_MaxDate
 Description: Get the max date for a specific Month & Year
 Input      : uwYear  -- Year
              usMonth -- Month
 Return     : The max date
 *****************************************************************************/
VOS_UINT8 VOS_MaxDate( VOS_UINT16 uwYear, VOS_UINT8 usMonth )
{
    VOS_UINT8  usMaxDate;

    switch( usMonth )
    {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            usMaxDate = 31;
            break;

        case 4:
        case 6:
        case 9:
        case 11:
            usMaxDate = 30;
            break;

        case 2:
            if (VOS_IsLeap(uwYear))
            {
                usMaxDate = 29;
            }
            else
            {
                usMaxDate = 28;
            }
            break;

        default:
            usMaxDate = 31;
            break;
    }

    return( usMaxDate );
}

/*****************************************************************************
 Function   : VOS_IsSysTimeValid
 Description: Check systime is Valid or not.
 Input      : pSysTime  -- Point to systime to check
 Return     : VOS_TRUE  -- Valid
              VOS_FALSE -- Not Valid
 *****************************************************************************/
VOS_BOOL VOS_IsSysTimeValid( SYS_T *pSysTime )
{
    if( VOS_NULL_PTR == pSysTime )
    {
        return VOS_FALSE;
    }

    if(  pSysTime->uwYear   <  1970 || pSysTime->ucDate   >  31
      || pSysTime->ucDate   == 0    || pSysTime->ucMonth  == 0
      || pSysTime->ucMonth  >  12   || pSysTime->ucHour   >  23
      || pSysTime->ucMinute >  59   || pSysTime->ucSecond >  59 )
    {
        return VOS_FALSE;
    }

    if( pSysTime->ucDate > VOS_MaxDate(pSysTime->uwYear, pSysTime->ucMonth))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

enum Comp_Time_Result
{
    COMP_TIME_ERROR,        /* Compare result: error        */
    COMP_TIME_LT,           /* Compare result: less than    */
    COMP_TIME_EQ ,          /* Compare result: equal to     */
    COMP_TIME_GT            /* Compare result: Greater than */
};

/*****************************************************************************
 Function   : VOS_IsDateValid
 Description: Check Date is Valid or not.
 Input      : pDate     -- Point to date to check
 Return     : VOS_TRUE  -- Valid
              VOS_FALSE -- Not Valid
 *****************************************************************************/
VOS_BOOL VOS_IsDateValid( DATE_T *pDate )
{
    if( VOS_NULL_PTR == pDate )
    {
        return VOS_FALSE;
    }

    if(  pDate->uwYear   <  1970 || pDate->ucDate   >  31
      || pDate->ucDate   == 0    || pDate->ucMonth  == 0
      || pDate->ucMonth  >  12 )
    {
        return VOS_FALSE;
    }

    if( pDate->ucDate > VOS_MaxDate(pDate->uwYear, pDate->ucMonth))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 Function   : VOS_CompareSysDate
 Description: Compare two system dates
 Input      : pFirstTm  -- The date 1 to be compared
              pSecondTm -- The date 2 to be compared
 Return     : Compare result, see to Comp_Time_Result
 *****************************************************************************/
enum Comp_Time_Result NEAR VOS_CompareSysDate( SYS_T *pFirstTm, SYS_T * pSecondTm )
{
    VOS_UINT32  ulFirstDay = 0;
    VOS_UINT32  ulSecondDay = 0;
    DATE_T      stSecondDate;
    DATE_T      stFirstDate;

    if( pFirstTm == VOS_NULL_PTR )
    {
        return (COMP_TIME_ERROR);
    }

    if( pSecondTm == VOS_NULL_PTR )
    {
        return (COMP_TIME_ERROR);
    }

    stFirstDate.uwYear  = pFirstTm->uwYear;
    stFirstDate.ucMonth = pFirstTm->ucMonth;
    stFirstDate.ucDate  = pFirstTm->ucDate;

    stSecondDate.uwYear  = pSecondTm->uwYear;
    stSecondDate.ucMonth = pSecondTm->ucMonth;
    stSecondDate.ucDate  = pSecondTm->ucDate;

    if( VOS_TRUE != VOS_IsDateValid( &stFirstDate ) )
    {
        return (COMP_TIME_ERROR);
    }

    if( VOS_TRUE != VOS_IsDateValid( &stSecondDate ) )
    {
        return (COMP_TIME_ERROR);
    }

    /*lint -e701 */
    ulFirstDay = ((pFirstTm->uwYear)<<16)|((pFirstTm->ucMonth)<<8)|(pFirstTm->ucDate);

    ulSecondDay = ((pSecondTm->uwYear)<<16)|((pSecondTm->ucMonth)<<8)|(pSecondTm->ucDate);
    /*lint +e701 */

    if( ulFirstDay == ulSecondDay )
    {
        return (COMP_TIME_EQ);
    }
    else
    {
        if( ulFirstDay > ulSecondDay )
        {
            return (COMP_TIME_GT);
        }
        else
        {
            return (COMP_TIME_LT);
        }
    }
}

/*****************************************************************************
 Function   : VOS_CalRelativeDay
 Description: Calculate the number of days between two system dates
 Input      : pFirstTm  -- The time 1 to be compared
              pSecondTm -- The time 2 to be compared
 Return     : The number of days between two system dates.
              If 0xFFFFFFFF is returned, it indicates that the date 1 is less
              than date 2, or the input date is invalid, or the input pointer
              has not been initialized.
 *****************************************************************************/
VOS_UINT32 VOS_CalRelativeDay( SYS_T * pFirstTm, SYS_T * pSecondTm )
{
    VOS_UINT16  ulTempYear;
    VOS_UINT16  ulTempMonth;
    VOS_UINT32  ulDayDifference = VOS_NULL_LONG;

    if( pFirstTm == VOS_NULL_PTR )
    {
        return ulDayDifference;
    }

    if( pSecondTm == VOS_NULL_PTR )
    {
        return ulDayDifference;
    }

    switch( VOS_CompareSysDate( pFirstTm, pSecondTm ) )
    {
        case COMP_TIME_LT :
            break;

        case COMP_TIME_EQ :
            ulDayDifference = 0;
            break;

        case COMP_TIME_GT :
            if( pFirstTm ->uwYear == pSecondTm ->uwYear )
            {
                if( pFirstTm ->ucMonth == pSecondTm ->ucMonth )
                {
                    ulDayDifference = pFirstTm ->ucDate - pSecondTm ->ucDate;
                }
                else
                {
                    ulDayDifference = VOS_MaxDate(pSecondTm ->uwYear, pSecondTm ->ucMonth)
                                      - pSecondTm ->ucDate;       /*leave days in the month*/
                    ulTempMonth = (VOS_UINT16)(pSecondTm ->ucMonth + 1);

                    while(ulTempMonth < pFirstTm ->ucMonth)
                    {
                        ulDayDifference += VOS_MaxDate(pSecondTm ->uwYear,(VOS_UINT8)ulTempMonth);
                        ulTempMonth ++;
                    }

                    ulDayDifference += pFirstTm ->ucDate;
                }
            }
            else    /* if(pFirstTm.uwYear > pSecondTm.uwYear) */
            {
                ulDayDifference = VOS_MaxDate(pSecondTm ->uwYear, pSecondTm ->ucMonth)
                                  - pSecondTm ->ucDate;     /*left days in the month*/
                ulTempMonth = (VOS_UINT16)(pSecondTm ->ucMonth + 1);

                while( ulTempMonth <= 12)
                {
                    ulDayDifference += VOS_MaxDate(pSecondTm ->uwYear, (VOS_UINT8)ulTempMonth);
                    ulTempMonth ++;
                }
                      /*left days in the uwYear*/
                for(ulTempYear = (VOS_UINT16)(pSecondTm ->uwYear+1); ulTempYear < pFirstTm ->uwYear; ulTempYear ++)
                {
                    for(ulTempMonth = 1; ulTempMonth <= 12; ulTempMonth ++)
                    {
                        ulDayDifference += VOS_MaxDate(ulTempYear, (VOS_UINT8)ulTempMonth);
                    }
                }      /*discrepancy years*/

                for(ulTempMonth=1; ulTempMonth < pFirstTm ->ucMonth; ulTempMonth ++)
                {
                    ulDayDifference += VOS_MaxDate(pFirstTm ->uwYear, (VOS_UINT8)ulTempMonth);
                }      /*  already pass days in the first year */

                ulDayDifference += pFirstTm ->ucDate;
            }       /* end else */

            break;
       case COMP_TIME_ERROR:
               break;
       default :
            break;
    }/* end of switch */

    return (ulDayDifference);
}

#ifndef DMT
/*****************************************************************************
 Function   : VOS_CalRelativeSec
 Description: Calculate the number of seconds between two system dates
 Input      : pFirstTm    -- The date 1 to be compared
              pSecondTm   -- The date 2 to be compared
 Output     : RelativeSec -- The number of seconds between two system dates
 Return     : VOS_OK on success or VOS_NULL_LONG on failure
 *****************************************************************************/
VOS_UINT32 VOS_CalRelativeSec(  SYS_T *pFirstTm,
                                SYS_T *pSecondTm,
                                VOS_UINT32 *RelativeSec )
{
   VOS_UINT32  ulSecond1;
   VOS_UINT32  ulSecond2;
   VOS_UINT32  ulRelativeDay;

    if( pFirstTm == VOS_NULL_PTR )
    {
        /*lint -e534*/
        VOS_SetErrorNo(VOS_ERRNO_SYSTIME_CALSEC_INPUTPARA1ISNULL);
        /*lint +e534*/
        return VOS_ERRNO_SYSTIME_CALSEC_INPUTPARA1ISNULL;
    }

    if( pSecondTm == VOS_NULL_PTR )
    {
        /*lint -e534*/
        VOS_SetErrorNo(VOS_ERRNO_SYSTIME_CALSEC_INPUTPARA2ISNULL);
        /*lint +e534*/
        return VOS_ERRNO_SYSTIME_CALSEC_INPUTPARA2ISNULL;
    }

    if( VOS_TRUE != VOS_IsSysTimeValid( pFirstTm ) )
    {
        /*lint -e534*/
        VOS_SetErrorNo(VOS_ERRNO_SYSTIME_CMPDATE_INPUTDATE1INVALID);
        /*lint +e534*/
        return VOS_ERRNO_SYSTIME_CMPDATE_INPUTDATE1INVALID;
    }

    if( VOS_TRUE != VOS_IsSysTimeValid( pSecondTm ) )
    {
        /*lint -e534*/
        VOS_SetErrorNo(VOS_ERRNO_SYSTIME_CMPDATE_INPUTDATE2INVALID);
        /*lint +e534*/
        return VOS_ERRNO_SYSTIME_CMPDATE_INPUTDATE2INVALID;
    }

    if( VOS_NULL_PTR == RelativeSec )
    {
        /*lint -e534*/
        VOS_SetErrorNo(VOS_ERRNO_SYSTIME_CALSEC_INPUTPARA3ISNULL);
        /*lint +e534*/
        return VOS_ERRNO_SYSTIME_CALSEC_INPUTPARA3ISNULL;
    }

    if( (pFirstTm->uwYear - pSecondTm->uwYear) > 135)
    {
        /*lint -e534*/
        VOS_SetErrorNo(VOS_ERRNO_SYSTIME_CALSEC_DATAOVERFLOW);
        /*lint +e534*/
        return VOS_ERRNO_SYSTIME_CALSEC_DATAOVERFLOW;
    }

    ulRelativeDay = VOS_CalRelativeDay(pFirstTm, pSecondTm);
    if( ulRelativeDay == VOS_NULL_LONG )
    {
        /*lint -e534*/
        VOS_SetErrorNo(VOS_ERRNO_SYSTIME_CALSEC_CALDAYERROR);
        /*lint +e534*/
        return VOS_ERRNO_SYSTIME_CALSEC_CALDAYERROR;
    }

    ulSecond1 = pFirstTm ->ucHour * 3600
              + pFirstTm ->ucMinute * 60
              + pFirstTm ->ucSecond;

    ulSecond2 = pSecondTm ->ucHour * 3600
              + pSecondTm ->ucMinute * 60
              + pSecondTm ->ucSecond;

    if( ( ulRelativeDay == 0 ) && ( ulSecond2 > ulSecond1 ) )
    {
        *RelativeSec = 0;
        /*lint -e534*/
        VOS_SetErrorNo(VOS_ERRNO_SYSTIME_CALSEC_INPUT1LESSTHAN2);
        /*lint +e534*/
        return VOS_ERRNO_SYSTIME_CALSEC_INPUT1LESSTHAN2;
    }

    *RelativeSec = ulRelativeDay * 24 * 3600;
    *RelativeSec += (ulSecond1 - ulSecond2);

    return VOS_OK;
}

#endif /* DMT */

/*****************************************************************************
 Function   : V_StartCallBackRelTimer
 Description: allocate and start a relative timer using callback function.
 Input      : Pid           -- process ID of application
              ulLength       -- expire time. unit is millsecond
              ulName         -- timer name to be pass to app as a parameter
              ulParam        -- additional parameter to be pass to app
              ucMode         -- timer work mode
                                VOS_RELTIMER_LOOP  -- start periodically
                                VOS_RELTIMER_NOLOO -- start once time
              TimeOutRoutine -- Callback function when time out
              enPrecision    -- precision,unit is 0 - 100->0%- 100%
 Output     : phTm           -- timer pointer which system retuns to app
 Return     : VOS_OK on success and errno on failure
 *****************************************************************************/
VOS_UINT32 V_StartCallBackRelTimer( HTIMER *phTm, VOS_PID Pid,
    VOS_UINT32 ulLength, VOS_UINT32 ulName, VOS_UINT32 ulParam,
    VOS_UINT8 ucMode, REL_TIMER_FUNC TimeOutRoutine, VOS_TIMER_PRECISION_ENUM_UINT32 enPrecision,
    VOS_UINT32 ulFileID, VOS_INT32 usLineNo)
{
    VOS_TIMER_OM_EVENT_STRU stTimerEvent;

    if( (ucMode != VOS_RELTIMER_LOOP) && (ucMode != VOS_RELTIMER_NOLOOP) )
    {
        /*lint -e534*/
        VOS_SetErrorNo(VOS_ERRNO_RELTM_START_INPUTMODEINVALID);

        LogPrint2( "# VOS_StartCallBackRelTimer Error: ucMode.F %d L %d.\r\n",
            (VOS_INT)ulFileID, usLineNo);
        /*lint +e534*/

        VOS_SIMPLE_FATAL_ERROR(START_CALLBACK_RELTIMER_FALSE_MODE);

        return(VOS_ERRNO_RELTM_START_INPUTMODEINVALID);
    }

    if ( VOS_NULL_PTR == phTm )
    {
        /*lint -e534*/
        LogPrint2( "# VOS_StartCallBackRelTimer Error: phTm null.F %d L %d.\r\n",
            (VOS_INT)ulFileID, usLineNo);
        /*lint +e534*/

        VOS_SIMPLE_FATAL_ERROR(START_CALLBACK_RELTIMER_NULL);

        return VOS_ERR;
    }

    if ( ulLength > VOS_TIMER_MAX_LENGTH )
    {
        /*lint -e534*/
        LogPrint2("# Timer's length is too big.F %d L %d.\r\n",
            (VOS_INT)ulFileID,usLineNo);
        /*lint +e534*/

        VOS_SIMPLE_FATAL_ERROR(START_CALLBACK_RELTIMER_TOO_BIG);

        return VOS_ERR;
    }

    if ( VOS_NULL_PTR == TimeOutRoutine )
    {
        /*lint -e534*/
        LogPrint2("# Timer no callback.F %d L %d.\r\n",
            (VOS_INT)ulFileID,usLineNo);
        /*lint +e534*/

        VOS_SIMPLE_FATAL_ERROR(START_CALLBACK_RELTIMER_FUN_NULL);

        return VOS_ERR;
    }

    if ( VOS_TIMER_PRECISION_BUTT <= enPrecision )
    {
        /*lint -e534*/
        LogPrint2("# Timer's Precision is too big.F %d L %d.\r\n",
            (VOS_INT)ulFileID, usLineNo);
        /*lint +e534*/

        VOS_SIMPLE_FATAL_ERROR(START_CALLBACK_RELTIMER_PRECISION_TOO_BIG);

        return VOS_ERR;
    }

    if ( ulLength < MILLISECONDS_PER_TICK )
    {
        ulLength = MILLISECONDS_PER_TICK;
    }

#if (VOS_WIN32 == VOS_OS_VER)
    ulLength = ulLength * g_ulMagnifyTimerLength;
#endif

    stTimerEvent.ucAction    = VOS_TIMER_OM_START;
    stTimerEvent.ucMode      = ucMode;
    stTimerEvent.ucType      = VOS_RELTIMER_CALLBACK;
    stTimerEvent.Pid         = Pid;
    stTimerEvent.ulLength    = ulLength;
    stTimerEvent.ulName      = ulName;
    stTimerEvent.ulParam     = ulParam;
    stTimerEvent.enPrecision = enPrecision;

    OM_OSAEvent( (VOS_VOID *)&stTimerEvent, sizeof(VOS_TIMER_OM_EVENT_STRU));

#if (VOS_32K_TIMER_ENABLE == VOS_YES)

#if ((VOS_VXWORKS == VOS_OS_VER) || (VOS_NUCLEUS == VOS_OS_VER) \
        || (VOS_LINUX == VOS_OS_VER) || (VOS_RTOSCK == VOS_OS_VER))
    if  ( VOS_TIMER_NO_PRECISION != enPrecision )
    {
        return V_Start32KCallBackRelTimer(phTm, Pid, ulLength, ulName,
            ulParam, ucMode, TimeOutRoutine, enPrecision, ulFileID, usLineNo);
    }
#endif

#endif

    return V_Start26MCallBackRelTimer(phTm, Pid, ulLength, ulName,
        ulParam, ucMode, TimeOutRoutine, ulFileID, usLineNo);
}

/*****************************************************************************
 Function   : V_Start26MCallBackRelTimer
 Description: allocate and start a 26M relative timer using callback function.
 Input      : Pid           -- process ID of application
              ulLength       -- expire time. unit is millsecond
              ulName         -- timer name to be pass to app as a parameter
              ulParam        -- additional parameter to be pass to app
              ucMode         -- timer work mode
                                VOS_RELTIMER_LOOP  -- start periodically
                                VOS_RELTIMER_NOLOO -- start once time
              TimeOutRoutine -- Callback function when time out
 Output     : phTm           -- timer pointer which system retuns to app
 Return     : VOS_OK on success and errno on failure
 *****************************************************************************/
VOS_UINT32 V_Start26MCallBackRelTimer( HTIMER *phTm, VOS_PID Pid,
    VOS_UINT32 ulLength, VOS_UINT32 ulName, VOS_UINT32 ulParam,
    VOS_UINT8 ucMode, REL_TIMER_FUNC TimeOutRoutine,
    VOS_UINT32 ulFileID, VOS_INT32 usLineNo)
{
    VOS_TIMER_CONTROL_BLOCK  *Timer;
    VOS_UINT32               TimerId;
    VOS_ULONG                ulLockLevel;

    /* stop the timer if exists */
    /*intLockLevel = VOS_SplIMP();*/
    VOS_SpinLockIntLock(&g_stVosTimerSpinLock, ulLockLevel);

    if( VOS_NULL_PTR != *phTm )
    {
        if ( VOS_OK == VOS_CheckTimer( phTm, &TimerId, ulFileID, usLineNo ) )
        {
            if ( VOS_OK != V_Stop26MRelTimer(phTm, ulFileID, usLineNo, VOS_NULL_PTR) )
            {
                /*VOS_Splx(intLockLevel);*/
                VOS_SpinUnlockIntUnlock(&g_stVosTimerSpinLock, ulLockLevel);

                VOS_SIMPLE_FATAL_ERROR(START_CALLBACK_RELTIMER_FAIL_TO_STOP);

                return VOS_ERR;
            }
        }
    }

    Timer = VOS_TimerCtrlBlkGet(ulFileID, usLineNo);
    if(Timer == VOS_NULL_PTR)
    {
        /*VOS_Splx(intLockLevel);*/
        VOS_SpinUnlockIntUnlock(&g_stVosTimerSpinLock, ulLockLevel);

        /*lint -e534*/
        VOS_SetErrorNo(VOS_ERRNO_RELTM_START_MSGNOTINSTALL);
        /*lint +e534*/

        VOS_TimerDump(START_CALLBACK_RELTIMER_FAIL_TO_ALLOCATE, ulFileID, (VOS_UINT32)usLineNo);

        return(VOS_ERRNO_RELTM_START_MSGNOTINSTALL);
    }

    /*if(phTm != VOS_NULL_PTR)
    {
        *phTm = (HTIMER)(&(Timer->TimerId));
    }*/

    Timer->Pid                          = Pid;
    Timer->Name                         = ulName;
    Timer->Para                         = ulParam;
    Timer->Mode                         = ucMode;
    Timer->phTm                         = phTm;
    Timer->TimeOutValueInMilliSeconds   = ulLength;
#if (VOS_YES == VOS_26M_TIMER_ENABLE_SOC_TIMER)

#ifdef FLOAT_SUPPORT
#ifdef V8R1_SINGLECLOCK
    if (UCOM_NV_32K_TYPE_32000 == g_usSingleXO)
    {
        Timer->TimeOutValueInTicks  = (VOS_UINT32)(RTC_SINGLECLOCK_CYCLE_LENGTH * ulLength);
    }
    else
#endif
    {
        Timer->TimeOutValueInTicks  = (VOS_UINT32)(RTC_CYCLE_LENGTH * ulLength);
    }
#else
    Timer->TimeOutValueInTicks = (VOS_UINT32)RTC_MUL_32_DOT_768(ulLength, ulFileID, usLineNo);
#endif

#else
    Timer->TimeOutValueInTicks          = ulLength/MILLISECONDS_PER_TICK;
#endif
    /*Timer->State                        = VOS_TIMER_CTRL_BLK_RUNNIG;*/
    Timer->CallBackFunc                 = TimeOutRoutine;
    /* Timer->message_Ptr                  = VOS_NULL_PTR; */
    /*Timer->next                         = VOS_NULL_PTR;*/

    *phTm = (HTIMER)(&(Timer->TimerId));

    Add_Timer_To_List( Timer );

    /*VOS_Splx(intLockLevel);*/
    VOS_SpinUnlockIntUnlock(&g_stVosTimerSpinLock, ulLockLevel);

    return(VOS_OK);
}


/*****************************************************************************
 Function   : VOS_TmTickToMillSec
 Description: Convert ticks to milliseconds
 Input      : ulTicks -- The Ticks to be converted
 Return     : The milliseconds converted from the Ticks specified by the
              parameter ulTicks. If the returned value is 0xFFFFFFFF,
              it indicates the conversion error that may be caused by
              conversion flow.
 *****************************************************************************/
VOS_UINT32 VOS_TmTickToMillSec( VOS_UINT32 ulTicks )
{
    VOS_UINT32 ulTempMillSec;

#if ( 0 == MILLISECONDS_PER_TICK )
    ulTempMillSec = VOS_NULL_DWORD;

    /*lint -e534*/
    VOS_SetErrorNo( VOS_ERRNO_SYSTIME_TK2MS_MSECPERTICKISZERO );
    /*lint +e534*/
#else
    if( ulTicks > ( VOS_NULL_DWORD / MILLISECONDS_PER_TICK ) )
    {
        ulTempMillSec = VOS_NULL_DWORD;
        /*lint -e534*/
        VOS_SetErrorNo( VOS_ERRNO_SYSTIME_TK2MS_INPUTTICKISTOOBIG );
        /*lint +e534*/
    }
    else
    {
        ulTempMillSec = ulTicks * MILLISECONDS_PER_TICK;
    }
#endif

    return ulTempMillSec;
}

#ifndef DMT
/*****************************************************************************
 Function   : VOS_TmSec2DateTime
 Description: Convert the number of seconds to the dates
 Input      : ulSec      -- The seconds set by the user
              pstRetDate -- The current date, in the format of Y/M/D (31-16/15-8/7-0)
              pstRetTime -- The current time, in the format of h/m/s (31-16/15-8/7-0)
 Output     : None
 Return     : None
 ******************************************************************************/
VOS_VOID VOS_Tm_Sec2DateTime( VOS_UINT32 ulSec,
                              VOS_UINT32 *pulRetDate,
                              VOS_UINT32 *pulRetTime )
{
    VOS_UINT32 dmsize[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    VOS_UINT32 ulYear;
    VOS_UINT32 ulMonth;
    VOS_UINT32 ulTempSec;
    VOS_UINT32 ulHour, ulMin;
    VOS_UINT32 ulTemp = ulSec;

    if( VOS_NULL_PTR == pulRetDate )
    {
        /*lint -e534*/
        VOS_SetErrorNo( VOS_ERRNO_SYSTIME_S2TIME_INPUTPARA2ISNULL );
        /*lint +e534*/
        return;
    }

    if( VOS_NULL_PTR == pulRetTime )
    {
        /*lint -e534*/
        VOS_SetErrorNo( VOS_ERRNO_SYSTIME_S2TIME_INPUTPARA3ISNULL );
        /*lint +e534*/
        return;
    }

    /*year*/
    for( ulYear = 1970;; )
    {
        ulTempSec = ( VOS_IsLeap( ulYear ) ? 366 : 365 ) * 24 * 60 * 60;
        if( ulTemp >= ulTempSec )
        {
            ulYear ++;
            ulTemp -= ulTempSec;
        }
        else
        {
            break;
        }
    }

    /*month*/
    for( ulMonth = 1;; )
    {
        ulTempSec = (VOS_UINT32 )( ( VOS_IsLeap( ulYear ) && ( ulMonth == 2 ) ) ? \
                    ( dmsize[ulMonth] + 1 ) : dmsize[ulMonth] ) * 24 * 60 * 60;
        if( ulTemp >= ulTempSec )
        {
            ulMonth ++;
            ulTemp -= ulTempSec;
        }
        else
        {
            break;
        }
    }
    *pulRetDate = ( ulYear << 16 ) | ( ulMonth<<8 ) | \
        ( ulTemp / ( 24 * 60 * 60 ) + 1 );

    ulTemp %= ( 24 * 60 * 60 );

    ulHour = ulTemp/ ( 60 * 60 );
    ulTemp %= ( 60 * 60 );

    ulMin = ulTemp / 60;
    ulTemp %= 60;

    *pulRetTime = ( ulHour << 16 ) | ( ulMin << 8 ) | ulTemp;

    return;
}
#endif /* DMT */

/*****************************************************************************
 Function   : VOS_IsTimeValid
 Description: Check time is Valid or not.
 Input      : pTime     -- Point to time to check
 Return     : VOS_TRUE  -- Valid
              VOS_FALSE -- Not Valid
 *****************************************************************************/
VOS_BOOL VOS_IsTimeValid( TIME_T *pTime )
{
    if( VOS_NULL_PTR == pTime )
    {
        /*lint -e534*/
        VOS_SetErrorNo( VOS_ERRNO_SYSTIME_VALIDTIME_INPUTISNULL );
        /*lint +e534*/
        return VOS_FALSE;
    }

    if( pTime->ucHour >  23 || pTime->ucMinute > 59 || pTime->ucSecond > 59 )
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 Function   : VOS_SysSecsSince1970
 Description: Get the number of seconds that have elapsed since
              1970/1/1-00:00:00 by inputting the current system date and time.
 Input      : pDate         -- The system date
              pTime         -- The system time
              ulMillSecs    -- The number of milliseconds that have elapsed
 Output     : pulRetSecHigh -- The high 32 bits of the number of seconds that
                               have elapsed since 1970/1/1-00:00:00
              pulRetSecLow  -- The low 32 bits of the number of seconds that
                               have elapsed since 1970/1/1-00:00:00
 Return     : VOS_OK on success, Error code on failure
 *****************************************************************************/
VOS_UINT32 VOS_SysSecsSince1970( DATE_T *pDate,
                                 TIME_T *pTime,
                                 VOS_UINT32 ulMillSecs,
                                 VOS_UINT32 *pulRetSecHigh,
                                 VOS_UINT32 *pulRetSecLow )
{
    VOS_UINT16 dmsize[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    VOS_UINT32 ulTemp  = 0;

    VOS_UINT32 ulYear;
    VOS_UINT32 ulMonth;
    VOS_UINT32 ulDay;
    VOS_UINT32 ulHour;
    VOS_UINT32 ulMin;
    VOS_UINT32 ulSec;

    if( VOS_NULL_PTR == pDate )
    {
        /*lint -e534*/
        VOS_SetErrorNo( VOS_ERRNO_SYSTIME_SEC1970_INPUTPARA1ISNULL );
        /*lint +e534*/
        return VOS_ERRNO_SYSTIME_SEC1970_INPUTPARA1ISNULL;
    }

    if( VOS_NULL_PTR == pTime )
    {
        /*lint -e534*/
        VOS_SetErrorNo( VOS_ERRNO_SYSTIME_SEC1970_INPUTPARA2ISNULL );
        /*lint +e534*/
        return VOS_ERRNO_SYSTIME_SEC1970_INPUTPARA2ISNULL;
    }

    if( VOS_NULL_PTR == pulRetSecHigh )
    {
        /*lint -e534*/
        VOS_SetErrorNo( VOS_ERRNO_SYSTIME_SEC1970_INPUTPARA4ISNULL );
        /*lint +e534*/
        return VOS_ERRNO_SYSTIME_SEC1970_INPUTPARA4ISNULL;
    }

    if( VOS_NULL_PTR == pulRetSecLow )
    {
        /*lint -e534*/
        VOS_SetErrorNo( VOS_ERRNO_SYSTIME_SEC1970_INPUTPARA5ISNULL );
        /*lint +e534*/
        return VOS_ERRNO_SYSTIME_SEC1970_INPUTPARA5ISNULL;
    }

    if( VOS_TRUE != VOS_IsDateValid( pDate ) )
    {
        /*lint -e534*/
        VOS_SetErrorNo( VOS_ERRNO_SYSTIME_SEC1970_INPUTDATEINVALID );
        /*lint +e534*/
        return VOS_ERRNO_SYSTIME_SEC1970_INPUTDATEINVALID;
    }

    if( VOS_TRUE != VOS_IsTimeValid( pTime ) )
    {
        /*lint -e534*/
        VOS_SetErrorNo( VOS_ERRNO_SYSTIME_SEC1970_INPUTTIMEINVALID );
        /*lint +e534*/
        return VOS_ERRNO_SYSTIME_SEC1970_INPUTTIMEINVALID;
    }

    if( ulMillSecs >= 1000 )
    {
        /*lint -e534*/
        VOS_SetErrorNo( VOS_ERRNO_SYSTIME_SEC1970_INPUTMILLSECSINVALID );
        /*lint +e534*/
        return VOS_ERRNO_SYSTIME_SEC1970_INPUTMILLSECSINVALID;
    }

    ulYear  = pDate->uwYear;
    ulMonth = pDate->ucMonth;
    ulDay   = pDate->ucDate;
    ulHour  = pTime->ucHour;
    ulMin   = pTime->ucMinute;
    ulSec   = pTime->ucSecond;

    if( VOS_IsLeap(ulYear) && ulMonth > 2)
    {
        ++ulTemp;
    }

    if( ulYear >1970 )
    {
        for( --ulYear; ulYear >= 1970; --ulYear )
        {
            ulTemp += VOS_IsLeap(ulYear) ? 366 : 365;
        }
    }

    while ( --ulMonth )
    {
        ulTemp += dmsize[ulMonth];
    }

    ulTemp += ulDay - 1;

    ulTemp  = 24 * ulTemp + ulHour;
    /*lint -e534*/
    VOS_64Multi32(0, ulTemp, 3600, pulRetSecHigh, pulRetSecLow);
    /*lint +e534*/
    if( *pulRetSecLow  > (VOS_UINT32)(0xFFFFFFFF - (ulMin * 60 + ulSec)))
    {
        (*pulRetSecHigh) ++;
        (*pulRetSecLow) += ulMin * 60 + ulSec;
    }
    else
    {
        (*pulRetSecLow) += ulMin * 60 + ulSec;
    }

    return( VOS_OK );
}

/*****************************************************************************
 Function   : VOS_Is26MTimerRunning
 Description: a 26M timer is running or not
 Input      : void
 Return     : true or false
 Other      :
 *****************************************************************************/
VOS_UINT32 VOS_Is26MTimerRunning( VOS_VOID )
{
    if ( VOS_NULL_PTR != vos_Timer_head_Ptr )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 Function   : VOS_show_Timer_info
 Description: print the usage info of timer
 Input      : void
 Return     : void
 Other      :
 *****************************************************************************/
VOS_VOID VOS_show_Timer_info( VOS_VOID )
{
    /*lint -e534*/
    vos_printf("Max be used timer is %x.\r\n",
        vos_TimerCtrlBlkNumber - vos_TimerMinTimerIdUsed);
    /*lint +e534*/
}

/*****************************************************************************
 Function   : VOS_CalcTimerInfo
 Description: print the usage info of timer
 Input      : void
 Return     : void
 Other      :
 *****************************************************************************/
VOS_BOOL VOS_CalcTimerInfo(VOS_VOID)
{
    if ( VOS_UPPER_TIMER_NUMBER > vos_TimerMinTimerIdUsed )
    {
        vos_TimerMinTimerIdUsed = vos_TimerCtrlBlkNumber;
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

#if VOS_YES == VOS_TIMER_CHECK

/*****************************************************************************
 Function   : VOS_ShowUsed26MTimerInfo
 Description: print the usage info of 26M timer's control block
 Input      : void
 Return     : void
 Other      :
 *****************************************************************************/
VOS_VOID VOS_ShowUsed26MTimerInfo( VOS_VOID )
{
    VOS_ULONG                    ulLockLevel;
    VOS_TIMER_CONTROL_BLOCK     *pstTimer;

    /*lint -e534*/
    LogPrint("# VOS_ShowUsed26MTimerInfo:");
    /*lint +e534*/

    /*nIntLockLevel = VOS_SplIMP();*/
    VOS_SpinLockIntLock(&g_stVosTimerSpinLock, ulLockLevel);

    pstTimer = vos_Timer_head_Ptr;
    while( VOS_NULL_PTR != pstTimer )
    {
        /*lint -e534*/
        LogPrint6("# F %d L %d P %d N %d R %d T %d.\r\n",
               (VOS_INT)pstTimer->ulFileID,
               (VOS_INT)pstTimer->ulLineNo,
               (VOS_INT)pstTimer->Pid,
               (VOS_INT)pstTimer->Name,
               (VOS_INT)pstTimer->Para,
               (VOS_INT)pstTimer->ulAllocTick);
        /*lint +e534*/

        pstTimer = pstTimer->next;
    }

    /*VOS_Splx(nIntLockLevel);*/
    VOS_SpinUnlockIntUnlock(&g_stVosTimerSpinLock, ulLockLevel);

    return;
}

#endif

#if (VOS_WIN32 == VOS_OS_VER)
VOS_VOID VOS_MagnifyTimerLength(VOS_UINT32 ulRatio )
{
    g_ulMagnifyTimerLength = ulRatio;
}
#endif

/*****************************************************************************
 Function   : VOS_TimerDump
 Description: Record the info of used timer when UE reboots.
 Input      : lModId     - Reboot reason.
              ulFileID
              ulLineNo
 Return     : void
 Other      :
 *****************************************************************************/
VOS_VOID VOS_TimerDump(VOS_INT lModId, VOS_UINT32 ulFileID, VOS_UINT32 ulLineNo)
{
    VOS_ULONG                 ulLockLevel;
    VOS_UINT32               *pulDumpBuffer;
    VOS_TIMER_CONTROL_BLOCK  *pstTimer;

    pulDumpBuffer = (VOS_UINT32*)VOS_EXCH_MEM_MALLOC(VOS_DUMP_MEM_TOTAL_SIZE);

    if (VOS_NULL_PTR == pulDumpBuffer)
    {
        VOS_ProtectionReboot(lModId, (VOS_INT)ulFileID, (VOS_INT)ulLineNo,
                             (VOS_CHAR *)&vos_TimerMinTimerIdUsed, sizeof(vos_TimerMinTimerIdUsed));
        return;
    }

    /*intLockLevel = VOS_SplIMP();*/
    VOS_SpinLockIntLock(&g_stVosTimerSpinLock, ulLockLevel);

    pstTimer = vos_Timer_head_Ptr;
    while( VOS_NULL_PTR != pstTimer )
    {
        *(pulDumpBuffer++) = pstTimer->Pid;
        *(pulDumpBuffer++) = pstTimer->Name;
#if VOS_YES == VOS_TIMER_CHECK
        *(pulDumpBuffer++) = pstTimer->ulFileID;
        *(pulDumpBuffer++) = pstTimer->ulLineNo;
#endif
        pstTimer = pstTimer->next;
    }

    /*VOS_Splx(intLockLevel);*/
    VOS_SpinUnlockIntUnlock(&g_stVosTimerSpinLock, ulLockLevel);

    VOS_ProtectionReboot(lModId, (VOS_INT)ulFileID, (VOS_INT)ulLineNo,
                         (VOS_CHAR *)&vos_TimerMinTimerIdUsed, sizeof(vos_TimerMinTimerIdUsed));

    return;
}

#if (VOS_YES == VOS_26M_TIMER_ENABLE_SOC_TIMER)

/*****************************************************************************
 Function   : Show26MTimerLog
 Description:
 Input      : VOID
 Return     : VOID
 Other      :
 *****************************************************************************/
VOS_VOID Show26MTimerLog( VOS_VOID )
{
    /*lint -e534*/
    vos_printf("g_st26MSocTimerInfo.ulStartCount = %d. (call DRV Start timer num)\r\n",
                g_st26MSocTimerInfo.ulStartCount);
    vos_printf("g_st26MSocTimerInfo.ulStopCount =  %d. (call DRV Stop timer num)\r\n",
                g_st26MSocTimerInfo.ulStopCount);
    vos_printf("g_st26MSocTimerInfo.ulExpireCount = %d. (receive DRV ISR of DualTimer num)\r\n",
                g_st26MSocTimerInfo.ulExpireCount);
    vos_printf("g_st26MSocTimerInfo.ulStartErrCount = %d. (call DRV Stop timer err num)\r\n",
                g_st26MSocTimerInfo.ulStartErrCount);
    vos_printf("g_st26MSocTimerInfo.ulStopErrCount = %d. (call DRV Start timer err num)\r\n",
                g_st26MSocTimerInfo.ulStopErrCount);
    vos_printf("g_st26MSocTimerInfo.ulElapsedErrCount = %d. (call DRV get rest timer num)\r\n",
                g_st26MSocTimerInfo.ulElapsedErrCount);
    vos_printf("g_st26MSocTimerInfo.ulElapsedContentErrCount = %d. (call DRV get rest timer err num)\r\n",
                g_st26MSocTimerInfo.ulElapsedContentErrCount);
    /*lint +e534*/
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

