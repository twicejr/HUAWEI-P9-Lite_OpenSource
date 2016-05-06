/*-
 * Copyright (c) 1996 - 2001 Brian Somers <brian@Awfulhak.org>
 *          based on work by Toshiharu OHNO <tony-o@iij.ad.jp>
 *                           Internet Initiative Japan, Inc (IIJ)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD: src/usr.sbin/ppp/hdlc.h,v 1.22 2001/06/13 21:52:16 brian Exp $
 */

#ifndef __PPP_HDLC_H__
#define __PPP_HDLC_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#include "vos.h"

/*
 *  Definition for Async HDLC
 */
#pragma pack(4)
#define HDLC_SYN 0x7e        /* SYNC character */
#define HDLC_ESC 0x7d        /* Escape character */
#define HDLC_XOR 0x20        /* Modifier value */

#define    HDLC_ADDR 0xff
#define    HDLC_UI      0x03
/*
 *  Definition for HDLC Frame Check Sequence
 */
#define INITFCS 0xffff        /* Initial value for FCS computation */
#define GOODFCS 0xf0b8        /* Good FCS value */

#define    DEF_MRU        1500
#define    MAX_MRU        2048
#define    MIN_MRU        296

#define    DEF_MTU        0    /* whatever peer says */
#define    MAX_MTU        2048
#define    MIN_MTU        296





struct ppp_mbuf;


struct hdlc {
/*  struct pppTimer ReportTimer;*/

  struct {
    VOS_INT32 badfcs;
    VOS_INT32 badaddr;
    VOS_INT32 badcommand;
    VOS_INT32 unknownproto;
  } laststats, stats;

  struct {
    struct lcp *owner;            /* parent LCP */
/*    struct pppTimer timer;    */    /* When to send */
    VOS_INT32 method;                /* bit-mask for LQM_* from lqr.h */

    VOS_UINT32 OutPackets;        /* Packets sent by me */
    VOS_UINT32 OutOctets;        /* Octets sent by me */
    VOS_UINT32 SaveInPackets;        /* Packets received from peer */
    VOS_UINT32 SaveInDiscards;        /* Discards */
    VOS_UINT32 SaveInErrors;        /* Errors */
    VOS_UINT32 SaveInOctets;        /* Octets received from peer */

    struct {
      VOS_UINT32 OutLQRs;        /* LQRs sent by me */
      VOS_UINT32 SaveInLQRs;        /* LQRs received from peer */
/*      struct lqrdata peer;    */    /* Last LQR from peer */
      VOS_INT32 peer_timeout;            /* peers max lqr timeout */
      VOS_INT32 resent;            /* Resent last packet `resent' times */
    } lqr;

    struct {
      VOS_UINT32 seq_sent;        /* last echo sent */
      VOS_UINT32 seq_recv;        /* last echo received */
    } echo;
  } lqm;
};


extern void hdlc_Init(struct hdlc *, struct lcp *);
extern void hdlc_StartTimer(struct hdlc *);
extern void hdlc_StopTimer(struct hdlc *);

#if 0/*fanzhibin f49086 delete it*/
extern VOS_INT32 hdlc_ReportStatus(struct cmdargs const *);
#endif

extern const VOS_CHAR *hdlc_Protocol2Nam(VOS_UINT16);

#if 0/*fanzhibin f49086 delete it*/
extern void hdlc_DecodePacket(struct bundle *, VOS_UINT16, struct ppp_mbuf *,
                              struct link *);
#endif

extern VOS_UINT16 hdlc_Fcs(VOS_CHAR *, VOS_UINT32);

#if 0/*fanzhibin f49086 delete it*/
extern VOS_INT32 hdlc_Detect(VOS_CHAR const **, VOS_INT32, VOS_INT32);
#endif

extern VOS_INT32 hdlc_WrapperOctets(struct lcp *, VOS_UINT16);

extern struct layer hdlclayer;
#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of hdlc.h */
