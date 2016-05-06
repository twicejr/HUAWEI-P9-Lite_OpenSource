/*
 * Copyright (c) 2001-2003 Swedish Institute of Computer Science.
 * All rights reserved. 
 * 
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED 
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT 
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT 
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 * 
 * Author: Adam Dunkels <adam@sics.se>
 *
 */

#ifndef __ARCH_SYS_ARCH_H__
#define __ARCH_SYS_ARCH_H__

#include "BST_Platform.h"
#include "BST_IP_Define.h"

#define lwip_sys_valid                  ( 1 )
#define lwip_sys_invalid                ( 0 )
#define LWIP_COMPAT_MUTEX               ( 1 )
#define SYS_SEM_NULL                    ( BST_NULL_PTR )
#define SYS_MBOX_NULL                   ( BST_NULL_PTR )

typedef BST_VOID*                       sys_sem_t;
typedef BST_VOID*                       sys_mbox_t;
typedef BST_VOID                        sys_thread_t;
void bastet_lwip_event( s32_t fd, u32_t lwip_event, err_t err );
void bastet_lwip_event_acked(
     BST_VOID *pFlag,
     u32_t lwip_event,
     err_t err,
     u32_t ulMinAckNo,
     u32_t ulMaxAckNo );

int sys_mbox_valid(sys_mbox_t *mbox);
void sys_mbox_set_invalid(sys_mbox_t *mbox);
int sys_sem_valid(sys_sem_t *sem);
void sys_sem_set_invalid(sys_sem_t *sem);
u32_t sys_timestamp(void);
void arch_free(void *rmem);

//typedef void (*lwip_thread_fn)(void *arg);

/*HANDLE is used for sys_sem_t but we won't include windows.h 
void sys_init(void);
err_t sys_sem_new(sys_sem_t *sem, u8_t count);
void sys_sem_free(sys_sem_t *sem);
void sys_sem_signal(sys_sem_t *sem);
u32_t sys_arch_sem_wait(sys_sem_t *sem, u32_t timeout);
int sys_sem_valid(sys_sem_t *sem);
void sys_sem_set_invalid(sys_sem_t *sem);
err_t sys_mbox_new(sys_mbox_t *mbox, int size);

void sys_mbox_free(sys_mbox_t *mbox);
void sys_mbox_post(sys_mbox_t *mbox, void *msg);
err_t sys_mbox_trypost(sys_mbox_t *mbox, void *msg);
u32_t sys_arch_mbox_fetch(sys_mbox_t *mbox, void **msg, u32_t timeout);
u32_t sys_arch_mbox_tryfetch(sys_mbox_t *mbox, void **msg);
int sys_mbox_valid(sys_mbox_t *mbox);
void sys_mbox_set_invalid(sys_mbox_t *mbox);
sys_thread_t sys_thread_new(const char *name, lwip_thread_fn thread, void *arg, int stacksize, int prio);
sys_prot_t sys_arch_protect(void);
void sys_arch_unprotect(sys_prot_t pval);
u32_t sys_now(void);

 DWORD (thread id) is used for sys_thread_t but we won't include windows.h */

#endif /* __ARCH_SYS_ARCH_H__ */

