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
 *         Simon Goldschmidt
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <lwip/opt.h>
#include <lwip/arch.h>
#include <lwip/stats.h>
#include <lwip/sys.h>
#include "arch/sys_time.h"
#include "lwip/tcp.h"
#include "lwip/tcp_impl.h"
#include "BST_OS_Timer.h"

extern sys_mbox_t mbox;
void    memp_free_no_timer(memp_t type, void *mem);

timer_id_t lwip_rt_alloc( struct tcp_pcb *pcb )
{
    timer_id_t   retval;
    if( NULL == pcb )
    {
        return 0;
    }
    retval = (timer_id_t)BST_OS_TimerCreate( (BST_OS_TIMER_CB_T)&pcb_timer_out, pcb, mbox);
    return retval; 
}

u32_t lwip_rt_is_running( timer_id_t id )
{

    if( BST_TRUE == BST_OS_TimerIsStop( id ) )
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void  lwip_rt_start( timer_id_t id, u32_t length )
{
    if( 0 == length )
    {
       return;
    }
    BST_OS_TimerStart( id, length );
}

void  lwip_rt_stop( timer_id_t id )
{
    BST_OS_TimerStop( id );
}

void  lwip_rt_free( timer_id_t id )
{
    BST_OS_TimerRemove( id );
}
void pcb_timer_out( timer_id_t timer_id, struct tcp_pcb* pcb )
{
    s32_t   rmv_rst_flag = flag_nothing;
    SYS_ARCH_DECL_PROTECT(lev);


    if( NULL == pcb )
    {
        return;
    }
    BST_DBG_LOG2("lwip timerout1, id = %d pcb_state= %d", timer_id, pcb->state );

    SYS_ARCH_PROTECT(lev);
    if( pcb->wnd_timer_id == timer_id )
    {
        rmv_rst_flag = tcp_wnd_timer_out(pcb);
    }
    else if( pcb->ack_timer_id == timer_id )
    {
        rmv_rst_flag = tcp_ack_timer_out(pcb);
    }
    else if( pcb->rtx_timer_id == timer_id )
    {
        rmv_rst_flag = tcp_rtx_timer_out(pcb);  //OK
    }
    else if( pcb->rfs_timer_id == timer_id )
    {
        rmv_rst_flag = tcp_rfs_timer_out(pcb);
    }
    else if( pcb->usl_timer_id == timer_id )
    {
        rmv_rst_flag = tcp_usl_timer_out(pcb);
    }

    else
    {
        rmv_rst_flag = flag_nothing;
    }
    BST_DBG_LOG2("lwip timerout2, rmv_rst_flag = %d pcb_state= %d", rmv_rst_flag, pcb->state );

    if( rmv_rst_flag )
    {
        remove_pcb_in_active(pcb, rmv_rst_flag & flag_remove);
    }
    SYS_ARCH_UNPROTECT(lev);
}

s32_t tcp_wnd_timer_out( struct tcp_pcb *pcb ) 
{
    BST_DBG_LOG("lwip tcp_wnd_timer_out");

    if( NULL == check_pcb_in_set( tcp_active_pcbs, pcb ) )
    {
        return flag_nothing;
    }

    tcp_zero_window_probe(pcb);
    if (pcb->persist_backoff < sizeof(tcp_persist_backoff)) 
    {
        pcb->persist_backoff++;
        lwip_rt_start( pcb->wnd_timer_id, get_wnd_timer_len(pcb));
    }
    return flag_nothing;
}

//原 fasttmr 里的第一个条件，遇到 TF_ACK_DELAY 要将它发送出去。
s32_t tcp_ack_timer_out( struct tcp_pcb *pcb ) 
{
    BST_DBG_LOG("lwip tcp_ack_timer_out !!!!");
    if (pcb->flags & TF_ACK_DELAY)
    {
        LWIP_DEBUGF(TCP_DEBUG, ("tcp_fasttmr: delayed ACK"));
        (pcb)->flags |= TF_ACK_NOW;
        tcp_output(pcb);
        pcb->flags &= ~(TF_ACK_DELAY | TF_ACK_NOW);
    }
    return flag_nothing;
}

s32_t tcp_rtx_timer_out( struct tcp_pcb *pcb ) 
{
    u16_t eff_wnd;
    u32_t len;

    BST_DBG_LOG("lwip tcp_rtx_timer_out");
    if( NULL == check_pcb_in_set( tcp_active_pcbs, pcb ) )
    {
        return flag_nothing;
    }

    if (pcb->state == SYN_SENT && pcb->nrtx == TCP_SYNMAXRTX) 
    {
        //LWIP_DEBUGF(TCP_DEBUG, ("tcp_slowtmr: max SYN retries reached"));
        BST_DBG_LOG("tcp_slowtmr: max SYN retries reached");
        return( flag_remove );
    }
    else if (pcb->nrtx == TCP_MAXRTX) 
    {
        //LWIP_DEBUGF(TCP_DEBUG, ("tcp_slowtmr: max DATA retries reached"));
        BST_DBG_LOG("tcp_slowtmr: max DATA retries reached");
        return( flag_remove );
    }

    if (pcb->unacked != NULL) 
    {
        /* Time for a retransmission. */
        LWIP_DEBUGF(TCP_RTO_DEBUG, ("tcp_slowtmr: rtime %"S16_F
                                  " pcb->rto %"S16_F"",
                                  pcb->rtime, pcb->rto));

        /* Double retransmission time-out unless we are trying to
        * connect to somebody (i.e., we are in SYN_SENT). */
        if (pcb->state != SYN_SENT) {
            /*lint -e701 -e702 -e734*/
            pcb->rto = ((pcb->sa >> 3) + pcb->sv) << tcp_backoff[pcb->nrtx];
            /*lint +e701 +e702 +e734*/
        }
        /*lint -e701 -e702*/
        len = get_rtx_timer_len(pcb);
        /*lint +e701 +e702*/
        /* Reset the retransmission timer. */
        lwip_rt_start( pcb->rtx_timer_id, len );

        /* Reduce congestion window and ssthresh. */
        eff_wnd = LWIP_MIN(pcb->cwnd, pcb->snd_wnd);
        pcb->ssthresh = eff_wnd >> 1;
        if (pcb->ssthresh < (pcb->mss << 1)) {
        pcb->ssthresh = (u16_t)(pcb->mss << 1);
        }
        pcb->cwnd = pcb->mss;
        LWIP_DEBUGF(TCP_CWND_DEBUG, ("tcp_slowtmr: cwnd %"U16_F
                                   " ssthresh %"U16_F"",
                                   pcb->cwnd, pcb->ssthresh));

        /* The following needs to be called AFTER cwnd is set to one
         mss - STJ */
        tcp_rexmit_rto(pcb);
    }
    return flag_nothing;
}

//fasttmr 里第二个条件
s32_t tcp_rfs_timer_out( struct tcp_pcb *pcb ) 
{
    BST_DBG_LOG("lwip tcp_rfs_timer_out!!!");
    if( NULL != check_pcb_in_set( tcp_active_pcbs, pcb ) )
    {
        tcp_process_refused_data(pcb);
    }
    return flag_nothing;
}

s32_t tcp_usl_timer_out( struct tcp_pcb *pcb ) 
{
    BST_DBG_LOG("lwip tcp_usl_timer_out!!!");

    if( NULL == pcb )
    {
        return( flag_nothing );
    }
    switch( pcb->state )
    {
        case ESTABLISHED:
            if( NULL != pcb->ooseq )
            {
              tcp_segs_free(pcb->ooseq);
              pcb->ooseq = NULL;
              LWIP_DEBUGF(TCP_CWND_DEBUG, ("tcp_slowtmr: dropping OOSEQ queued data"));
              return( flag_nothing );
            }
            return( flag_nothing );

       case FIN_WAIT_2:
       case SYN_RCVD:
       case LAST_ACK:
            return( flag_remove );

       case TIME_WAIT:
            if( NULL != tcp_tw_pcbs )
            {
                remove_pcb_in_wait( pcb );
            }
            return( flag_nothing );

       default:
            return( flag_nothing );
    }
}

struct tcp_pcb *check_pcb_in_set( struct tcp_pcb *pcb_list, struct tcp_pcb *pcb_item ) 
{
    struct tcp_pcb *tmp_pcb;

    if( ( NULL == pcb_list ) || ( NULL == pcb_item ) )
    {
        return NULL;
    }
    for(tmp_pcb = pcb_list; tmp_pcb != NULL; tmp_pcb = tmp_pcb->next)
    {
        if( tmp_pcb == pcb_item )
        {
            return pcb_item;
        }
    }
    return NULL;
}

void remove_pcb_in_active( struct tcp_pcb *pcb, u8_t reset_flag )
{
    void           *err_arg;
    tcp_err_fn      err_fn;

    if( NULL == check_pcb_in_set( tcp_active_pcbs, pcb ) )
    {
        return;
    }

    tcp_pcb_purge(pcb);
    /* Remove PCB from tcp_active_pcbs list. */
    TCP_RMV( &tcp_active_pcbs, pcb );

    if ( reset_flag&flag_reset )
    {
        tcp_rst(pcb->snd_nxt, pcb->rcv_nxt, &pcb->local_ip, &pcb->remote_ip,
                pcb->local_port, pcb->remote_port);
    }

    err_fn  = pcb->errf;

    err_arg = pcb->callback_arg;

    free_all_pcb_timer(pcb);
#if MEM_USE_POOLS
    memp_free_no_timer(MEMP_TCP_PCB, pcb);
#else
    memp_free(MEMP_TCP_PCB,pcb);
#endif
    TCP_EVENT_ERR(err_fn, err_arg, ERR_ABRT);
}

void remove_pcb_in_wait( struct tcp_pcb *pcb )
{
    if( NULL == check_pcb_in_set( tcp_tw_pcbs, pcb ) )
    {
        return;
    }

    tcp_pcb_purge(pcb);
    /* Remove PCB from tcp_tw_pcbs list. */
    TCP_RMV( &tcp_tw_pcbs, pcb );

    free_all_pcb_timer(pcb);
#if MEM_USE_POOLS
    memp_free_no_timer(MEMP_TCP_PCB, pcb);
#else
    //mem_free(pcb);
    memp_free(MEMP_TCP_PCB,pcb);
#endif
}

void lwip_proc_usl_timer( struct tcp_pcb *pcb )
{
    u32_t timer_len;
    if( NULL == pcb )
    {
        return;
    }
    timer_len = get_usl_timer_len( pcb );
    
    if( 0 == timer_len )
    {
        if( lwip_rt_is_running(pcb->usl_timer_id) )
        {
            lwip_rt_stop(pcb->usl_timer_id);
        }  
    }
    lwip_rt_start(pcb->usl_timer_id, timer_len);
}

void lwip_proc_oos_timer( struct tcp_pcb *pcb )
{
    if( ESTABLISHED != pcb->state )
    {
        return;
    }
    if( NULL == pcb->ooseq )
    {
        if( lwip_rt_is_running(pcb->usl_timer_id) )
        {
            lwip_rt_stop(pcb->usl_timer_id);
        }  
    }
    else
    {
        if( lwip_rt_is_running(pcb->usl_timer_id) )
        {
            return;
        }
        else
        {
        /*lint -e387 -e391 -e571*/
            lwip_rt_start(pcb->usl_timer_id, (u32_t)((pcb)->rto * TCP_SLOW_INTERVAL) );
        /*lint +e387 +e391 +e571*/
        }
    }
}

u32_t get_usl_timer_len( struct tcp_pcb *pcb )
{
    switch( pcb->state )
    {
        case FIN_WAIT_2:
            if (pcb->flags & TF_RXCLOSED)
            {
                BST_DBG_LOG2( "lwip_sys_timer: Get FIN_WAIT_2 Timer, state=%u, Length=%d ms",
                              pcb->state, TCP_FIN_WAIT_TIMEOUT );
                return( TCP_FIN_WAIT_TIMEOUT );
            }
            else
            {
                BST_RLS_LOG( "lwip_sys_timer: Didn't Get FIN_WAIT Timer: TF_RXCLOSED" );
                return 0;
            }

       case SYN_RCVD:
            BST_DBG_LOG1( "lwip_sys_timer: Get SYN_RCVD Timer, Length=%d ms",
                          TCP_SYN_RCVD_TIMEOUT );
            return( TCP_SYN_RCVD_TIMEOUT );

       case LAST_ACK:
            BST_DBG_LOG1( "lwip_sys_timer: Get LAST_ACK Timer, Length=%d ms",
                           2*TCP_MSL );
            return( 2*TCP_MSL );

       case TIME_WAIT:
            BST_DBG_LOG1( "lwip_sys_timer: Get TIME_WAIT Timer, Length=%d ms",
                           2*TCP_MSL );
            return( 2*TCP_MSL );

       default:
            BST_DBG_LOG1( "lwip_sys_timer: Didn't Get Usual Timer, State=%u",
                          pcb->state );
            return 0;
    }
}

