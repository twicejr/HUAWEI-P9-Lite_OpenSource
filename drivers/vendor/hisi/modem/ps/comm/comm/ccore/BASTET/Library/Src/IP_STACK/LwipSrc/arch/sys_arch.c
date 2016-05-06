
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

/*
 * Wed Apr 17 16:05:29 EDT 2002 (James Roth)
 *
 *  - Fixed an unlikely sys_thread_new() race condition.
 *
 *  - Made current_thread() work with threads which where
 *    not created with sys_thread_new().  This includes
 *    the main thread and threads made with pthread_create().
 *
 *  - Catch overflows where more than SYS_MBOX_SIZE messages
 *    are waiting to be read.  The sys_mbox_post() routine
 *    will block until there is more room instead of just
 *    leaking messages.
 */

#include "BST_Platform.h"
#include "BST_OS_Thread.h"
#include "BST_OS_Sync.h"
#include "BST_OS_Timer.h"
#include "BST_DRV_Net.h"
#include "BST_IP_PreProc.h"
#include "lwip/debug.h"
#include "arch/sys_arch.h"
#include "lwip/stats.h" 
#include "lwip/sys.h"
#include "lwip/sio.h"
#include "BST_SRV_Event.h"

#define THIS_FILE_ID               PS_FILE_ID_BST_LWIP_SYS_ARCH_C

static BST_OS_SPINLOCK_T    g_LwipSpinLock;
extern BST_OS_MBX_T        *g_pBstLwipThreadMbx;
extern void                *get_socket_rcver(int s);
extern int                  get_fd_by_pcb( struct tcp_pcb *pcb);
void sys_init(void)
{
}

BST_VOID BST_IP_LwipLockInit( BST_VOID )
{
    BST_OS_InitSpinLock( &g_LwipSpinLock );
}
err_t sys_sem_new(sys_sem_t *sem, u8_t count)
{
    BST_ASSERT_NULL_RTN(sem, ERR_MEM);
   *sem                                 = BST_OS_CreateSem( BST_NULL_PTR, count );
    if( BST_NULL_PTR == *sem )
    {
        return ERR_MEM;
    }
    return ERR_OK;
}

void sys_sem_free(sys_sem_t *sem)
{
    BST_OS_DeleteSem( *sem );
}

void sys_sem_signal(sys_sem_t *sem)
{
    BST_OS_SendSem( *sem );
}

u32_t sys_arch_sem_wait(sys_sem_t *sem, u32_t timeout)
{
    BST_UINT32      ulWaitTimeMs;
    BST_UINT32      ulExpierTime;
    
    if( 0 == timeout )
    {
        ulExpierTime                    = (BST_UINT32)BST_OS_SYS_FOREVER;
    }
    else
    {
        ulExpierTime                    = timeout;
    }

    ulWaitTimeMs                        = BST_OS_RecvSem( *sem, ulExpierTime );
    if( BST_OS_SYS_TIMEOUT == ulWaitTimeMs )
    {
        return SYS_ARCH_TIMEOUT;
    }
    else
    {
        return( ulWaitTimeMs );
    }
}

int sys_sem_valid(sys_sem_t *sem)
{
    if( BST_NULL_PTR == sem )
    {
        return lwip_sys_invalid;
    }
    if( BST_NULL_PTR == (*( (BST_OS_SEM_STRU **)sem ))->stHandle )
    {
        return lwip_sys_invalid;
    }
    return( lwip_sys_valid );
}

void sys_sem_set_invalid(sys_sem_t *sem)
{
    if( BST_NULL_PTR == sem )
    {
        return;
    }
    *sem                                = BST_NULL_PTR;
}

err_t sys_mbox_new(sys_mbox_t *mbox, int size)
{
    BST_ASSERT_NULL_RTN(mbox, ERR_MEM);
   *mbox                                = BST_OS_CreateMbx( BST_NULL_PTR, (BST_UINT32)size );
    return ERR_OK;
}

void sys_mbox_free(sys_mbox_t *mbox)
{
    BST_OS_DeleteMbx( *mbox );
}

void sys_mbox_post(sys_mbox_t *mbox, void *msg)
{
    BST_OS_SendMail(*mbox, msg);
}

err_t sys_mbox_trypost(sys_mbox_t *mbox, void *msg)
{
    BST_UINT32                          ulRst;
    ulRst                               = BST_OS_SendMail(*mbox, msg);
    if( BST_NO_ERROR_MSG == ulRst )
    {
        return ERR_OK;
    }
    else
    {
        return ERR_MEM;
    }
}

u32_t sys_arch_mbox_fetch(sys_mbox_t *mbox, void **msg, u32_t timeout)
{
    BST_UINT32                          ulWaitTimeMs;
    BST_UINT32                          ulExpierTime;

    if( 0 == timeout )
    {
        ulExpierTime                    = (BST_UINT32)BST_OS_SYS_FOREVER;
    }
    else
    {
        ulExpierTime                    = timeout;
    }

    ulWaitTimeMs                        = BST_OS_RecvMail( *mbox, msg, ulExpierTime );
    if( BST_OS_SYS_TIMEOUT == ulWaitTimeMs )
    {
        return SYS_ARCH_TIMEOUT;
    }
    else
    {
        return( ulWaitTimeMs );
    }    
}

u32_t sys_arch_mbox_tryfetch(sys_mbox_t *mbox, void **msg)
{
    BST_UINT32                          ulMailAmount;
    BST_UINT32                          ulWaitTimeMs;

    ulMailAmount                        = BST_OS_GetMailAmount(*mbox);
    if( 0 == ulMailAmount )
    {
        return SYS_MBOX_EMPTY;
    }

    ulWaitTimeMs                        = BST_OS_RecvMail( *mbox, msg, 1 );
    if( BST_OS_SYS_TIMEOUT == ulWaitTimeMs )
    {
        return SYS_MBOX_EMPTY;
    }
    else
    {
        return( 1 );
    }    
}

int sys_mbox_valid(sys_mbox_t *mbox)
{
    if( BST_NULL_PTR == mbox )
    {
        return lwip_sys_invalid;
    }
    if( BST_NULL_PTR == *mbox )
    {
        return lwip_sys_invalid;
    }
    if( BST_NULL_PTR == (*( (BST_OS_MBX_T **)mbox) )->hSem )
    {
        return lwip_sys_invalid;
    }
    return( lwip_sys_valid );
}

void sys_mbox_set_invalid(sys_mbox_t *mbox)
{
    *mbox       = BST_NULL_PTR;
}
sys_thread_t sys_thread_new(const char *name, lwip_thread_fn thread, void *arg, int stacksize, int prio)
{
    BST_OS_SendMail( g_pBstLwipThreadMbx, thread );
}
sys_prot_t sys_arch_protect(void)
{
    return ( BST_OS_SpinLock( &g_LwipSpinLock ) );
}
void sys_arch_unprotect(sys_prot_t pval)
{
    BST_OS_SpinUnLock( &g_LwipSpinLock, pval );
}

u32_t sys_now(void)
{
    return ( BST_OS_TimerNowMs() );
}

u32_t sys_timestamp(void)
{
    BST_DRV_STRU                       *pNetDrvHandle;
    BST_UINT32                          ulTimeStamp;
    BST_BOOL                            bNetState;
    pNetDrvHandle                       = BST_DRV_NetGetDvcHandle();
    pNetDrvHandle->pfIoCtrl( BST_DRV_CMD_GET_NET_STATE, &bNetState );

    if ( BST_IP_IsMirroredTimeStampUsed()
    && ( BST_FALSE == bNetState ) )
    {
        return BST_IP_GetMirroredTimeStamp();
    }

    if( BST_NULL_PTR == pNetDrvHandle->pfIoCtrl )
    {
        return ( BST_OS_TimerNowMs() );
    }
    pNetDrvHandle->pfIoCtrl( BST_DRV_CMD_GET_NET_TIMESTAMP, &ulTimeStamp );
    return ulTimeStamp;
}

void bastet_lwip_event( s32_t fd, u32_t lwip_event, err_t err )
{
    BST_IP_EVENT_STRU   stEvent;
    BST_OS_MBX_T       *rcver;

    rcver               = (BST_OS_MBX_T *)get_socket_rcver( fd );
    if( NULL == rcver )
    {
        return;
    }
    stEvent.lErrMsg     = err;
    stEvent.lFd         = fd;
    stEvent.ulMsgId     = lwip_event;
    BST_SRV_ApiSendTcpIpEvent( rcver, &stEvent );
}
void bastet_lwip_event_acked(
    BST_VOID *pFlag,
    u32_t lwip_event,
    err_t err,
    u32_t ulMinAckNo,
    u32_t ulMaxAckNo )
{
    BST_IP_EVENT_STRU   stEvent;
    BST_OS_MBX_T       *rcver;
    BST_INT32           fd;
    struct tcp_pcb     *pcb;
    pcb                 = (struct tcp_pcb *)pFlag;
    fd                  = get_fd_by_pcb(pcb);

    rcver               = (BST_OS_MBX_T *)get_socket_rcver( fd );
    if ( NULL == rcver )
    {
        return;
    }
    stEvent.lErrMsg     = err;
    stEvent.lFd         = fd;
    stEvent.ulMsgId     = lwip_event;
    stEvent.ulMinNumber = ulMinAckNo;
    stEvent.ulMaxNumber = ulMaxAckNo;
    BST_SRV_ApiSendTcpIpEvent( rcver, &stEvent );
}

u32_t sys_jiffies(void)
{
    return ( BST_OS_TimerNowMs() );
}
sio_fd_t sio_open(u8_t devnum)
{
    return BST_NULL_PTR;
}
u32_t sio_write(sio_fd_t fd, u8_t *data, u32_t len)
{
    BST_DRV_WRITE_T         pfWrite;
    if ( BST_IP_IsLwipNull(fd) )
    {
        return 0;
    }
    pfWrite                 = ( BST_DRV_WRITE_T )fd;
    pfWrite( len, data );
    return len;
}
/*lint -e438*/
void arch_free(void *rmem)
{
    BST_OS_StaticMemFree((BST_VOID**)(&(rmem)));
}
/*lint +e438*/
///////////////////////////////////////////////////////////////////////////////////////////////

