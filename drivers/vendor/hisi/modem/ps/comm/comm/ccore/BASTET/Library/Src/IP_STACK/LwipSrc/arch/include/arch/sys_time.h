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
#ifndef __LWIP_REAL_TIMER_H__
#define __LWIP_REAL_TIMER_H__

#include "arch/cc.h"

#ifdef __cplusplus
extern "C" {
#endif

struct tcp_pcb;

#define get_wnd_timer_len( pcb )        ( tcp_persist_backoff[(pcb)->persist_backoff-1] * TCP_SLOW_INTERVAL ) 
#define get_rtx_timer_len( pcb )        ( ((((pcb)->sa >> 3) + (pcb)->sv) << tcp_backoff[(pcb)->nrtx] )* TCP_SLOW_INTERVAL )
#define get_initl_rtx_len( pcb )        ( (((pcb)->sa >> 3) + (pcb)->sv )*TCP_SLOW_INTERVAL )
#define get_ack_timer_len( pcb )        ( TCP_TMR_INTERVAL )
#define get_rfs_timer_len( pcb )        ( TCP_TMR_INTERVAL )
#define flag_remove                     ( 0x01 )
#define flag_reset                      ( 0x02 )
#define flag_nothing                    ( 0x00 )

#define aloc_all_pcb_timer(pcb) \
                    {\
                        (pcb)->wnd_timer_id   = lwip_rt_alloc(pcb);\
                        (pcb)->rtx_timer_id   = lwip_rt_alloc(pcb);\
                        (pcb)->ack_timer_id   = lwip_rt_alloc(pcb);\
                        (pcb)->rfs_timer_id   = lwip_rt_alloc(pcb);\
                        (pcb)->usl_timer_id   = lwip_rt_alloc(pcb);\
                    }

#define free_all_pcb_timer(pcb) \
                    {\
                        lwip_rt_free(((struct tcp_pcb *)(pcb))->wnd_timer_id);\
                        lwip_rt_free(((struct tcp_pcb *)(pcb))->rtx_timer_id);\
                        lwip_rt_free(((struct tcp_pcb *)(pcb))->ack_timer_id);\
                        lwip_rt_free(((struct tcp_pcb *)(pcb))->rfs_timer_id);\
                        lwip_rt_free(((struct tcp_pcb *)(pcb))->usl_timer_id);\
                    }

#define stop_all_pcb_timer(pcb) \
                    {\
                        lwip_rt_stop((pcb)->wnd_timer_id);\
                        lwip_rt_stop((pcb)->rtx_timer_id);\
                        lwip_rt_stop((pcb)->ack_timer_id);\
                        lwip_rt_stop((pcb)->rfs_timer_id);\
                        lwip_rt_stop((pcb)->usl_timer_id);\
                    }
#define declare_pct_timer_struct \
                  timer_id_t wnd_timer_id;\
                  timer_id_t rtx_timer_id;\
                  timer_id_t ack_timer_id;\
                  timer_id_t rfs_timer_id;\
                  timer_id_t usl_timer_id


typedef u32_t        timer_id_t;

timer_id_t lwip_rt_alloc( struct tcp_pcb *pcb );
u32_t lwip_rt_is_running( timer_id_t id );
void  lwip_rt_start( timer_id_t id, u32_t length );
void  lwip_rt_stop( timer_id_t id );
void  lwip_rt_free( timer_id_t id );
void  pcb_timer_out( timer_id_t timer_id, struct tcp_pcb* pcb );

s32_t tcp_wnd_timer_out( struct tcp_pcb *pcb );
s32_t tcp_ack_timer_out( struct tcp_pcb *pcb );
s32_t tcp_rtx_timer_out( struct tcp_pcb *pcb );
s32_t tcp_rfs_timer_out( struct tcp_pcb *pcb );
s32_t tcp_usl_timer_out( struct tcp_pcb *pcb );
s32_t tcp_kal_timer_out( struct tcp_pcb *pcb );
u32_t get_usl_timer_len( struct tcp_pcb *pcb );
void lwip_proc_oos_timer( struct tcp_pcb *pcb );
void lwip_proc_usl_timer( struct tcp_pcb *pcb );
void remove_pcb_in_active( struct tcp_pcb *pcb, u8_t reset_flag );
void remove_pcb_in_wait( struct tcp_pcb *pcb );
struct tcp_pcb *check_pcb_in_set( struct tcp_pcb *pcb_list, struct tcp_pcb *pcb_item ) ;

extern const u8_t tcp_persist_backoff[7];
extern const u8_t tcp_backoff[13];

#ifdef __cplusplus
}
#endif

#endif /* __ARCH_SYS_ARCH_H__ */


