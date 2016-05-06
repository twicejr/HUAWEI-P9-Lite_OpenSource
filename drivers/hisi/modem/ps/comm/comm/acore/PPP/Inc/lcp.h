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
 * $FreeBSD: src/usr.sbin/ppp/lcp.h,v 1.30 2002/04/16 23:57:09 brian Exp $
 */
#ifndef __PPP_LCP_H__
#define __PPP_LCP_H__

#include  "PPP/Inc/ppp_fsm.h"
#include  "PPP/Inc/hdlc.h"
#include  "PPP/Inc/ppp_public.h"

#pragma pack(4)
/* callback::opmask values */
#define CALLBACK_AUTH        (0)
#define CALLBACK_DIALSTRING    (1)    /* Don't do this */
#define CALLBACK_LOCATION    (2)    /* Don't do this */
#define CALLBACK_E164        (3)
#define CALLBACK_NAME        (4)    /* Don't do this */
#define CALLBACK_CBCP        (6)
#define CALLBACK_NONE        (14)    /* No callback is ok */

#define CALLBACK_BIT(n) ((n) < 0 ? 0 : 1 << (n))


struct callback {
  VOS_INT32 opmask;            /* want these types of callback */
  VOS_CHAR msg[SCRIPT_LEN];        /* with this data (E.164) */
};

#define    REJECTED(p, x)    ((p)->his_reject & (1<<(x)))

extern VOS_UINT16 g_usPppConfigMru;


struct lcp {
  struct fsm fsm;        /* The finite state machine */
  VOS_UINT16 his_mru;        /* Peers maximum packet size */
  VOS_UINT16 his_mrru;        /* Peers maximum reassembled packet size (MP) */
  VOS_UINT32 his_accmap;        /* Peeers async VOS_CHAR control map */
  VOS_UINT32 his_magic;        /* Peers magic number */
  VOS_UINT32 his_lqrperiod;    /* Peers LQR frequency (100ths of seconds) */
  VOS_UINT16 his_auth;        /* Peer wants this type of authentication */
#if 0    /* in BSD type is u_short, but I prefer to use VOS_UINT8 noted by liukai */
  VOS_CHAR his_authtype;        /* Fifth octet of REQ/NAK/REJ */
#else
  VOS_UINT8 his_authtype;        /* Fifth octet of REQ/NAK/REJ */
#endif
  VOS_UINT8 aucReserved[5];
  struct callback his_callback;    /* Peer wants callback ? */
  unsigned his_shortseq : 1;    /* Peer would like only 12bit seqs (MP) */
  unsigned his_protocomp : 1;    /* Does peer do Protocol field compression */
  unsigned his_acfcomp : 1;    /* Does peer do addr & cntrl fld compression */
  unsigned mru_req : 1;        /* Has the peer requested an MRU */

  VOS_UINT16 want_mru;        /* Our maximum packet size */
  VOS_UINT16 want_mrru;        /* Our maximum reassembled packet size (MP) */
  VOS_UINT32 want_accmap;    /* Our async VOS_CHAR control map */
  VOS_UINT32 want_magic;        /* Our magic number */
  VOS_UINT32 want_lqrperiod;    /* Our LQR frequency (100ths of seconds) */
  VOS_UINT16 want_auth;        /* We want this type of authentication */
#if 0    /* in BSD, type is u_char, so use VOS_UINT8 by liukai */
  VOS_CHAR want_authtype;        /* Fifth octet of REQ/NAK/REJ */
#else
  VOS_UINT8 want_authtype;    /* Fifth octet of REQ/NAK/REJ */
#endif
  VOS_UINT8 aucReserved2[1];
  struct callback want_callback;/* We want callback ? */
  unsigned want_shortseq : 1;    /* I'd like only 12bit seqs (MP) */
  unsigned want_protocomp : 1;    /* Do we do protocol field compression */
  unsigned want_acfcomp : 1;    /* Do we do addr & cntrl fld compression */

  VOS_UINT32 his_reject;        /* Request codes rejected by peer */
  VOS_UINT32 my_reject;        /* Request codes I have rejected */

  VOS_UINT16 auth_iwait;        /* I must authenticate to the peer */
  VOS_UINT16 auth_ineed;        /* I require that the peer authenticates */

  VOS_INT32 LcpFailedMagic;        /* Number of `magic is same' errors */
  HTIMER    hLcpCloseTimer;        /*PPP握手结束定时器*/

  struct {
    VOS_UINT16 mru;        /* Preferred MRU value */
    VOS_UINT16 max_mru;        /* Preferred MRU value */
    VOS_UINT16 mtu;        /* Preferred MTU */
    VOS_UINT16 max_mtu;        /* Preferred MTU */
    VOS_UINT32 accmap;        /* Initial ACCMAP value */
    VOS_INT32 openmode;        /* when to start CFG REQs */
    VOS_UINT32 lqrperiod;    /* LQR frequency (seconds) */
    struct fsm_retry fsm;    /* How often/frequently to resend requests */
    unsigned acfcomp : 2;    /* Address & Control Field Compression neg */
    unsigned chap05 : 2;    /* Challenge Handshake Authentication proto */
#ifndef NODES
    unsigned chap80nt : 2;    /* Microsoft (NT) CHAP */
    unsigned chap80lm : 2;    /* Microsoft (LANMan) CHAP */
    unsigned chap81 : 2;    /* Microsoft CHAP v2 */
#endif
    unsigned lqr : 2;        /* Link Quality Report */
    unsigned pap : 2;        /* Password Authentication protocol */
    unsigned protocomp : 2;    /* Protocol field compression */
    VOS_CHAR ident[DEF_MRU - 7];    /* SendIdentification() data */
    VOS_UINT8 aucReseved3[3];
  } cfg;
};

#define    LCP_MAXCODE    CODE_IDENT
#define    LCP_MINMPCODE    CODE_CODEREJ

#define    TY_MRU        1    /* Maximum-Receive-Unit */
#define    TY_ACCMAP    2    /* Async-Control-Character-Map */
#define    TY_AUTHPROTO    3    /* Authentication-Protocol */
#define    TY_QUALPROTO    4    /* Quality-Protocol */
#define    TY_MAGICNUM    5    /* Magic-Number */
#define    TY_RESERVED    6    /* RESERVED */
#define    TY_PROTOCOMP    7    /* Protocol-Field-Compression */
#define    TY_ACFCOMP    8    /* Address-and-Control-Field-Compression */
#define    TY_FCSALT    9    /* FCS-Alternatives */
#define    TY_SDP        10    /* Self-Describing-Padding */
#define    TY_CALLBACK    13    /* Callback */
#define    TY_CFRAMES    15    /* Compound-frames */
#define    TY_MRRU        17    /* Max Reconstructed Receive Unit (MP) */
#define    TY_SHORTSEQ    18    /* Want VOS_INT16 seqs (12bit) please (see mp.h) */
#define    TY_ENDDISC    19    /* Endpoint discriminator */


#define fsm2lcp(fp) (fp->proto == PROTO_LCP ? (struct lcp *)fp : VOS_NULL_PTR)

extern void lcp_Init(struct lcp *,/* struct bundle *,*/ struct link *,
                     const struct fsm_parent *);
extern void lcp_Setup(struct lcp *, VOS_INT32);

extern void lcp_SendProtoRej(struct lcp *, VOS_CHAR *, VOS_INT32);
extern VOS_INT32 lcp_SendIdentification(struct lcp *);
extern void lcp_RecvIdentification(struct lcp *, VOS_CHAR *);
extern VOS_INT32 lcp_ReportStatus(struct link *);
extern PPP_ZC_STRU *lcp_Input(/*struct bundle *,*/ struct link *, PPP_ZC_STRU *);
extern void lcp_SetupCallbacks(struct lcp *);
#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#endif /* end of Lcp.h */

