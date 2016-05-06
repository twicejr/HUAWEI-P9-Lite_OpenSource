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

#ifndef __OSL_THREAD_H
#define __OSL_THREAD_H

#include "osl_common.h"

#ifndef ERROR
#define ERROR (-1)
#endif

#ifndef OK
#define OK (0)
#endif


#ifdef __KERNEL__
#include <linux/kthread.h>
#include <linux/sched.h>
#include <linux/delay.h>

/*此处用于存放任务优先级 ---begin*/
#define  ICC_TASK_PRIVATE_PRI         (91)
#define  ICC_TASK_SHARED_PRI          (90)

/*此处用于存放任务优先级 ---end*/

typedef struct task_struct* OSL_TASK_ID;
typedef void (*OSL_TASK_FUNC)(void* para);
static inline s32  osl_task_init(
			char* name, 
			u32 priority, 
			u32 size, 
			OSL_TASK_FUNC entry, 
			void *para, 
			OSL_TASK_ID* task_id
			)
{
	struct task_struct* tsk;
	struct sched_param	sch_para;

	sch_para.sched_priority = (int)priority;

	tsk =  kthread_run((void*)entry, para, name);
	if (IS_ERR(tsk))
	{
		printk("create kthread %s failed!\n", name);
		return ERROR;
	}
	if (OK != sched_setscheduler(tsk, SCHED_FIFO, &sch_para))
	{
		printk("create kthread %s sched_setscheduler failed!", name);
		return ERROR;
	}
	*task_id =tsk;

	return OK;
}
static __inline__ void osl_task_delay(int ticks )
{
    msleep(ticks);
}


#elif defined(__OS_VXWORKS__)

#include <taskLib.h>
#include <logLib.h>
/*此处用于存放任务优先级 ---begin*/
#define  ICC_TASK_PRIVATE_PRI         (4)
#define  ICC_TASK_SHARED_PRI          (4)

#define OS_MAX_TASK_ID     255
/*此处用于存放任务优先级 ---end*/

#define VX_DEFAULT_PRIORITY      150
#define VX_DEFAULT_STACK_SIZE    8192

#define OSL_TASK_FUNC   FUNCPTR
typedef u32          OSL_TASK_ID;

#define kthread_run(threadfn, data, namefmt)    \
	taskSpawn(namefmt, VX_DEFAULT_PRIORITY, 0, VX_DEFAULT_STACK_SIZE, (OSL_TASK_FUNC)threadfn, (int)data, 0,0,0,0,0,0,0,0,0)

#define kthread_stop(id)    \
do{     \
	(void)taskDelete(id); \
}while(0)
static __inline__ s32 osl_task_init(
            char *        name,         /* name of new task (stored at pStackBase) */
            int           priority,     /* priority of new task */
            int           stackSize,    /* size (bytes) of stack needed plus name */
            OSL_TASK_FUNC       entryPt,      /* entry point of new task */
            void *para,         /* 1st of 10 req'd args to pass to entryPt */            
            OSL_TASK_ID *     tskid
            )    
{
    int tsk;
    tsk = taskSpawn(name,priority,0,stackSize,(OSL_TASK_FUNC)entryPt,(int)para,0,
                0,0,0,0,0,0,0,0);
    if (tsk == ERROR)           /* create failed */
    {
        logMsg("osl_task_init fail name:%s!", (int)name,0,0,0,0,0); /*[false alarm]*/
        return ERROR;
    }
    *tskid = (u32)tsk; /*[false alarm]*/
    return OK;
}
static __inline__ int osl_task_delay(int ticks )
{
    return taskDelay(ticks) ;
}
static __inline__ void osl_task_lock(void)
{
    taskLock() ;
    return;
}
static __inline__ void osl_task_unlock(void)
{
    taskUnlock() ;
    return;
}
static __inline__ int osl_task_delete( OSL_TASK_ID * tskid )
{
    int ret = OK;
    if(*tskid != (OSL_TASK_ID)NULL)
    {
        ret = taskDelete((int)*tskid) ;
        *tskid = (OSL_TASK_ID)NULL;
    }    
    if(ret != OK)
    {
        return ERROR;
    }
    return OK;
}
static __inline__ int osl_task_self(void)
{
    return taskIdSelf() ;
}
static __inline__ int osl_task_name_get(int taskID,char **pName)
{
	*pName = taskName(taskID); 
    if( NULL == *pName )    
    {
        return ERROR;
    }
    return OK;
}

static __inline__ u64 osl_tick_get(void){
	return tickGet();
}
static __inline__ void osl_tick_set(u64 swTick){
	tickSet(swTick);
}
static inline int  osl_task_check(unsigned int taskid) 
{
	return taskIdVerify(taskid);
}

#elif defined(__OS_RTOSCK__)
#include "sre_task.h"
#include <sre_sys.h>
#include <sre_tick.h>
/*此处用于存放任务优先级 ---begin*/
#define  ICC_TASK_PRIVATE_PRI         (4)
#define  ICC_TASK_SHARED_PRI          (4)

#define OS_MAX_TASK_ID     62
/*此处用于存放任务优先级 ---end*/

#define VX_DEFAULT_PRIORITY      63
#define OSL_TASK_FUNC   TSK_ENTRY_FUNC
typedef UINT32          OSL_TASK_ID;

 
 static inline  s32 osl_task_init(
        char *        name,         /* name of new task (stored at pStackBase) */
        int           priority,     /* priority of new task */
        int           stackSize,    /* size (bytes) of stack needed plus name */
        OSL_TASK_FUNC       entryPt,      /* entry point of new task */
        void *para,         /* 1st of 10 req'd args to pass to entryPt */            
        OSL_TASK_ID *     tskid
       )
{
    TSK_INIT_PARAM_S tsk;    
    UINT32 id;
    tsk.pfnTaskEntry  = (OSL_TASK_FUNC)entryPt;
    tsk.uwStackSize   = stackSize;
    tsk.usTaskPrio    = priority;
    tsk.pcName        = name;
    tsk.usQNum        = 0;
    tsk.auwArgs[0]    = (UINT32)para;
    tsk.uwStackAddr   = 0;
    UINT32 ret = SRE_TaskCreate((UINT32 *)&id,&tsk);
    if(ret != OK)
    {
        SRE_Printf("osl_task_init fail name:%s!", name);
        return ERROR;
    }
    *tskid = id; /*[false alarm]*/
    return OK;
}
static inline int osl_task_delay(int ticks )
 {
     return SRE_TaskDelay((unsigned int)ticks);
 }
static inline void osl_task_lock(void)
 {
     SRE_TaskLock();
     return;
 }
 static inline void osl_task_unlock(void)
 {
     SRE_TaskUnlock();
     return;
 }
 static inline int osl_task_delete(OSL_TASK_ID * tskid )
 {
     int ret = OK;
     if(*tskid != 0xffffffff)
     {
         ret = SRE_TaskDelete(*tskid);
         *tskid = 0xffffffff;
     }    
     if(ret != OK)
     {
         return ERROR;
     }
     return OK;
 }
static inline int osl_task_self(void)
{
     unsigned int id;
     int ret;
     ret = SRE_TaskSelf((unsigned int *)&id);
     if(OK == ret)
     {
         return id;
     }
     return ERROR;
 }
static inline int osl_task_name_get(int taskID,char **pName)
{
    if(OK != SRE_TaskNameGet((unsigned int)taskID,pName))    
    {
        return ERROR;
    }
    return OK;
}

#define kthread_stop(id)    \
do{     \
	(void)SRE_TaskDelete(id); \
}while(0)

static inline int  osl_task_check(unsigned int taskid) 
{
	if(TRUE == SRE_TaskIDCheck(taskid))
		return 0;
	else
		return -1;
}

static __inline__ u64 osl_tick_get(void){
	return SRE_TickCountGet();
}
static __inline__ void osl_tick_set(u64 swTick){
	u64* tick_addr=NULL;
	tick_addr = (u64*)SRE_GetTickAddr();
	*tick_addr = swTick;
}

#elif defined(__CMSIS_RTOS) /* rtx(cm3 os) */

/*此处用于存放任务优先级 ---begin*/


/*此处用于存放任务优先级 ---end*/

#endif /* __KERNEL__ */

#endif /* __OSL_THREAD_H */

