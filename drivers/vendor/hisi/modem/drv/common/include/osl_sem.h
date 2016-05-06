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

#ifndef __OSL_SEM_H
#define __OSL_SEM_H

#include "osl_common.h"

#ifdef __KERNEL__
#include <linux/semaphore.h>

typedef struct semaphore osl_sem_id;

static inline void osl_sem_init(u32 val, osl_sem_id* sem)
{
    sema_init(sem, val);
}

static inline void osl_sem_up(osl_sem_id* sem)
{
	up(sem);
}

static inline void osl_sem_down(osl_sem_id* sem)
{
	//down(sem);
	while(down_interruptible(sem)!=0);
}

static inline int osl_sem_downtimeout(osl_sem_id* sem, long jiffies)
{
	return down_timeout(sem, jiffies);
}

static inline s32 osl_sema_delete(osl_sem_id*sem)
{
	return 0;
}

static inline s32 sema_delete(struct semaphore *sem)
{
	return 0;
}


#elif defined(__OS_VXWORKS__)
#include <semLib.h>

#define OSL_SEM_Q_FIFO		 SEM_Q_FIFO	/* first in first out queue */
#define OSL_SEM_Q_PRIORITY	 SEM_Q_PRIORITY	/* priority sorted queue */
#define OSL_SEM_DELETE_SAFE	 SEM_DELETE_SAFE	/* owner delete safe (mutex opt.) */

typedef SEM_ID osl_sem_id;

static __inline__ void osl_sem_init(u32 val, osl_sem_id* sem)
{
	if(val == 0)
	{
		*sem = semBCreate(SEM_Q_FIFO, SEM_EMPTY);
	}
	else
	{
		*sem = semBCreate(SEM_Q_FIFO, SEM_FULL);
	}
}

static __inline__ void osl_sem_up(osl_sem_id* sem)
{
	semGive(*sem);
}

static __inline__ void osl_sem_down(osl_sem_id* sem)
{
	semTake(*sem, WAIT_FOREVER);
}

static __inline__ int osl_sem_downtimeout(osl_sem_id* sem, long jiffies)
{
	return semTake(*sem, jiffies);
}

static __inline__ s32 osl_sema_delete(osl_sem_id*sem)
{
	return semDelete(*sem);
}

static __inline__ void sema_init(struct semaphore *sem, int val)
{
	if(val == 0)
	{
		sem = semBCreate(SEM_Q_FIFO, SEM_EMPTY);
	}
	else
	{
		sem = semBCreate(SEM_Q_FIFO, SEM_FULL);
	}
}

static __inline__ void up(struct semaphore *sem)
{
	semGive(sem);
}

static __inline__ void down(struct semaphore *sem)
{
	semTake(sem, WAIT_FOREVER);
}

static __inline__ int down_timeout(struct semaphore *sem, long jiffies)
{
	return semTake(sem, jiffies);
}

static __inline__ s32 osl_sem_delete(struct semaphore *sem)
{
	return semDelete(sem);
}
static __inline__ int osl_sem_mcreate (osl_sem_id * mutex, int options)
{
    osl_sem_id semId;
    semId = semMCreate(options);
    if (!semId)     
    {
        return ERROR;
    }
    *mutex = semId;
    return OK;    
}
static __inline__ int osl_sem_bcreate (osl_sem_id *mutex,int count, int options)
{
    osl_sem_id semId;
    semId = semBCreate(options,count);
    if (!semId)
    {
        return  ERROR;
    }
    *mutex = semId;
    return OK;
    
}
static __inline__ int osl_sem_ccreate (osl_sem_id *mutex,int count, int options)
{
    osl_sem_id semId;
    semId = semCCreate(options,count);
    if (!semId)
    {
        return  ERROR;
    }
    *mutex = semId;
    return OK;    
}

#elif defined(__OS_RTOSCK__)
#include "sre_sem.h"
#include "sre_shell.h"

#define SEM_FULL       OS_SEM_FULL
#define SEM_EMPTY      OS_SEM_EMPTY
#define WAIT_FOREVER   OS_WAIT_FOREVER
#define OSL_SEM_INVERSION_SAFE  0x08

#define OSL_SEM_Q_FIFO		 SEM_MODE_FIFO	/* first in first out queue */
#define OSL_SEM_Q_PRIORITY	 SEM_MODE_PRIOR	/* priority sorted queue */
#define OSL_SEM_DELETE_SAFE	 0x0	/* owner delete safe (mutex opt.) RTOSCK no this*/

typedef  SEM_HANDLE_T osl_sem_id;

static inline void osl_sem_init(u32 val, osl_sem_id* mutex)
{        
    osl_sem_id semId;
    UINT32 ret = OK;
    if(val != SEM_FULL)
    {
        ret = SRE_SemBCreate(val, &semId, SEM_MODE_PRIOR);         
    }    
    else
    {
        ret = SRE_SemCCreate(SEM_FULL, &semId, SEM_MODE_PRIOR);        
        SRE_SemCMaxCountSet(semId,SEM_FULL);        
    }
    
    if(ret != SRE_OK)
    {
        SRE_Printf("osl_sem_init fail!\n");
        return;
    }
    *mutex = semId;
    return;
}

static inline void osl_sem_up(osl_sem_id* sem)
{
	SRE_SemPost(*sem);
}

static inline void osl_sem_down(osl_sem_id* sem)
{
	SRE_SemPend(*sem, WAIT_FOREVER);
}

static inline int osl_sem_downtimeout(osl_sem_id* sem, long jiffies)
{
	return SRE_SemPend(*sem, jiffies);
}

static inline s32 osl_sema_delete(osl_sem_id*sem)
{
	return SRE_SemDelete(*sem);
}

struct semaphore{
    SEM_HANDLE_T handle;
};

static inline void sema_init(struct semaphore *sem, int val)
{
    UINT32 ret = OK;
    if(val != SEM_FULL)
    {
        ret = SRE_SemBCreate(val, &(sem->handle), SEM_MODE_PRIOR);         
    }    
    else
    {
        ret = SRE_SemCCreate(SEM_FULL, &(sem->handle), SEM_MODE_PRIOR);        
        SRE_SemCMaxCountSet(sem->handle,SEM_FULL);        
    }
    
    if(ret != SRE_OK)
    {
        SRE_Printf("sema_init fail!\n");
    }
}

static inline void up(struct semaphore *sem)
{
	SRE_SemPost(sem->handle);
}

static inline void down(struct semaphore *sem)
{
	SRE_SemPend(sem->handle, WAIT_FOREVER);
}

static inline int down_timeout(struct semaphore *sem, long jiffies)
{
	return SRE_SemPend(sem->handle, (UINT32)jiffies);
}

static inline s32 osl_sem_delete(struct semaphore *sem)
{
	return SRE_SemDelete(sem->handle);
}
static inline int osl_sem_mcreate (osl_sem_id * mutex, int options)
{
    osl_sem_id semId;
    UINT32 ret = OK;
    if(options&OSL_SEM_INVERSION_SAFE)
    {
        ret = SRE_SemBCreate(SEM_FULL, &semId, (OS_SEM_MODE_E)(options&~OSL_SEM_INVERSION_SAFE));       
    }
    else
    {
        ret = SRE_SemCCreate(SEM_FULL, &semId, (OS_SEM_MODE_E)options); 
        SRE_SemCMaxCountSet(semId,SEM_FULL);        
    } 
    if(ret != OK)
    {
        return ERROR;
    }
    *mutex = semId;
    return OK;    
}
static inline int osl_sem_bcreate (osl_sem_id *mutex,int count, int options)
{
    osl_sem_id semId;
    UINT32 ret = OK;
    if(count != SEM_FULL)
    {
        ret = SRE_SemBCreate(count, &semId, (OS_SEM_MODE_E)options);         
    }    
    else
    {
        ret = SRE_SemCCreate(SEM_FULL, &semId, (OS_SEM_MODE_E)options);        
        SRE_SemCMaxCountSet(semId,SEM_FULL);        
    } 
    if(ret != OK)
    {
        return  ERROR;
    }
    *mutex = semId;
    return OK;    
}
 static inline int osl_sem_ccreate (osl_sem_id *mutex,int count, int options)
{
    osl_sem_id semId;
    unsigned int ret = OK;
    ret = SRE_SemCCreate(count, &semId, (OS_SEM_MODE_E)options); 
    if(ret != SRE_OK)
    {
        return  ERROR;
    }
    *mutex = semId;
    return OK;    
}

#else

#endif /* __KERNEL__ */

#endif

