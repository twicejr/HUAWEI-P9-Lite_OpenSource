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
#ifndef __OSL_IRQ_H
#define __OSL_IRQ_H
#include "product_config.h"

#ifdef __KERNEL__
#include <linux/interrupt.h>

#define OSL_IRQ_FUNC(ret, func, irq, dev)  \
	ret func(int irq, void* dev)
#define osl_free_irq(irq,routine,dev_id) free_irq(irq,(void*)dev_id)

#elif defined(__OS_VXWORKS__)
#include <vxWorks.h>
#include <intLib.h>
#include <logLib.h>
#include <taskLib.h>

#define IRQF_NO_SUSPEND 0
typedef enum {
	IRQ_NONE,
	IRQ_HANDLED
} irqreturn_t;

typedef irqreturn_t (*irq_handler_t)(int, void *);

static void inline int_lock_hook(void)
{
    return;
}

static void inline int_unlock_hook(void)
{
    return;
}


/*该宏传参不准传入__specific_flags名字*/
#define local_irq_save(__specific_flags)	    \
	do \
    {                           \
		__specific_flags = (unsigned long)intLock();			\
	} while (0)

#define local_irq_restore(__specific_flags)   \
	do \
    {                           \
        intUnlock((int)__specific_flags);          \
	} while (0)

#define OSL_IRQ_FUNC(ret, func, irq, dev)  \
	ret func(void* dev)

static __inline__ int request_irq(unsigned int irq, irq_handler_t handler, unsigned long flags,
	    const char *name, void *dev)
{
	int ret = intConnect((VOIDFUNCPTR*)(irq),(VOIDFUNCPTR)handler, (int)dev);
	if(ret != OK)
	{
		logMsg("intConnect irq %d error\n", irq, 0, 0, 0, 0, 0);
		return ret;
	}
	ret = intEnable((int)irq);
	if(ret != OK)
	{
		logMsg("intEnable irq %d error\n", irq, 0, 0, 0, 0, 0);
		return ret;
	}
	return ret;
}

static __inline__ void free_irq(unsigned int irq, void *dev_id)
{
	int ret = intDisable((int)irq);
	if(ret != OK)
	{
		logMsg("intDisable irq %d error\n", irq, 0, 0, 0, 0, 0);
		return;
	}
	ret = intDisconnect((VOIDFUNCPTR*)(irq), (VOIDFUNCPTR)NULL, (int)dev_id);/* [false alarm]:误报 */
	if(ret != OK)
	{
		logMsg("intDisconnect irq %d error\n", irq, 0, 0, 0, 0, 0);
		return;
	}

}
static __inline__ void osl_free_irq(unsigned int irq, irq_handler_t routine,int para)
{
	int ret = intDisable(irq);
	if(ret != OK)
	{
		logMsg("intDisable irq %d error\n", irq, 0, 0, 0, 0, 0);
		return;
	}
	ret = intDisconnect((VOIDFUNCPTR*)(irq), (VOIDFUNCPTR)routine, para);
	if(ret != OK)
	{
		logMsg("intDisconnect irq %d error\n", irq, 0, 0, 0, 0, 0);
		return;
	}
}
static __inline__  int enable_irq(unsigned int irq)
{
    return(intEnable((int)irq));
}
static __inline__ int disable_irq( unsigned int num )
{
    return intDisable ((int)num);
}
static __inline__ int osl_int_connect( unsigned int num, irq_handler_t routine, int parameter )
{
    return intConnect((VOIDFUNCPTR *)num,(VOIDFUNCPTR)routine,parameter);
}
static __inline__ int osl_int_disconnect( unsigned int num, irq_handler_t routine, int parameter )
{
    return intDisconnect((VOIDFUNCPTR *)num,(VOIDFUNCPTR)routine,parameter);
}
static __inline__ unsigned int osl_int_context(void)
{
	return (unsigned int)INT_CONTEXT(); 
}

#elif defined(__CMSIS_RTOS)
#include <ARMCM3.h>

#define IRQF_NO_SUSPEND 0

#define local_irq_save(__specific_flags)	    \
	do {							\
		__specific_flags = __get_PRIMASK(); __disable_irq();			\
	} while (0)

#define local_irq_restore(__specific_flags)   \
	do {                           \
		if(!__specific_flags) __enable_irq();          \
	} while (0)

#elif defined(__OS_RTOSCK__)
#include "sre_base.h"
#include "sre_hwi.h"
#include "sre_shell.h"
#include "sre_sys.h"

#define IRQF_NO_SUSPEND 0
typedef enum {
    IRQ_NONE,
    IRQ_HANDLED
} irqreturn_t;
typedef irqreturn_t (*irq_handler_t)(void *);

#define OSL_IRQ_FUNC(ret, func, irq, arg)  \
	ret func(void *arg)

#ifndef OK
#define OK                  (0)
#endif

#ifndef ERROR
#define ERROR               (1)
#endif


/*该宏传参不准传入__specific_flags名字*/
/*
*参数类型
*unsigned long __specific_flags
*/
#define local_irq_save(__specific_flags)	    \
	do \
    {                           \
		__specific_flags = (unsigned long)SRE_IntLock();			\
	} while (0)
/*
*参数类型
*unsigned long __specific_flags
*/
#define local_irq_restore(__specific_flags)   \
	do \
    {                           \
        SRE_IntRestore((unsigned int)__specific_flags);          \
	} while (0)
	

static inline int request_irq(unsigned int irq, irq_handler_t handler, unsigned long flags,
        const char *name, void *arg)
{
    UINT32 ret = SRE_HwiSetAttr((HWI_HANDLE_T)(irq), SRE_HWI_PRIORITY0, OS_HWI_MODE_ENGROSS);
    ret = SRE_HwiCreate((HWI_HANDLE_T)(irq),(HWI_PROC_FUNC)handler, (HWI_ARG_T)arg);
    if(ret != OK)
    {
        SRE_Printf("SRE_HwiCreate irq %d errorNO 0x%x\n", irq, ret);
        return ret;
    }
    ret = SRE_HwiEnable((HWI_HANDLE_T)irq);
    if(ret != OK)
    {
        SRE_Printf("SRE_HwiEnable irq %d errorNO 0x%x\n", irq,ret);
        return ret;
    }
    return ret;
}

static inline void free_irq(unsigned int irq, void *arg)
{
    UINTPTR ret = SRE_HwiDisable((HWI_HANDLE_T)irq);
    if(ret != OK)
    {
        SRE_Printf("SRE_HwiDisable irq %d errorNO 0x%x\n", irq, ret);
        return;
    }
    ret = SRE_HwiDelete((HWI_HANDLE_T)irq);/* [false alarm]:误报 */
    if(ret != OK)
    {
        SRE_Printf("SRE_HwiDelete irq %d errorNO 0x%x\n", irq, ret);
        return;
    }

}
static inline void osl_free_irq(unsigned int irq, irq_handler_t routine,int para)
{
    UINTPTR ret = SRE_HwiDisable((HWI_HANDLE_T)irq);
    if(ret != OK)
    {
        SRE_Printf("SRE_HwiDisable irq %d error\n", irq);
        return;
    }
    ret = SRE_HwiDelete((HWI_HANDLE_T)irq);/* [false alarm]:误报 */
    if(ret != OK)
    {
        SRE_Printf("SRE_HwiDelete irq %d error\n", irq);
        return;
    }
}

static inline  int enable_irq(unsigned int irq)
{
    return SRE_HwiEnable((HWI_HANDLE_T)irq);
}
static inline int disable_irq( unsigned int num )
{
    if(OS_ERRNO_HWI_NUM_INVALID == SRE_HwiDisable((HWI_HANDLE_T)num))
    {
        return ERROR;
    }
    return OK;
}
static inline int osl_int_connect( unsigned int num, irq_handler_t routine, int parameter )
{
    SRE_HwiSetAttr((HWI_HANDLE_T)num, SRE_HWI_PRIORITY0, OS_HWI_MODE_ENGROSS);
    return SRE_HwiCreate((HWI_HANDLE_T)num,(HWI_PROC_FUNC)routine,parameter);
}
static inline int osl_int_disconnect( unsigned int num, irq_handler_t routine, int parameter )
{
    return SRE_HwiDelete((HWI_HANDLE_T)num);
}
static inline unsigned int osl_int_context(void)
{
	OS_THREAD_TYPE_E ret;
	ret = SRE_CurThreadType();
    if(SYS_HWI == ret ||(SYS_SWI == ret))
    {
		return 1;
	}
	else
	{
		return 0;
	}
}


#endif /* __KERNEL__ */

#endif

