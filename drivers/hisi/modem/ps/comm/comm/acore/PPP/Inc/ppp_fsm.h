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
 * $FreeBSD: src/usr.sbin/ppp/ppp_fsm.h,v 1.27 2002/05/22 21:17:13 brian Exp $
 */
#ifndef __PPP_FSM_H__
#define __PPP_FSM_H__

#include "vos.h"
#include "PPP/Inc/ppp_mbuf.h"

#pragma pack(4)
#define MIN_LQRPERIOD 1        /* Minimum LQR frequency */
#define DEF_LQRPERIOD 30    /* Default LQR frequency */
#define MIN_FSMRETRY 1        /* Minimum FSM retry frequency */
#define DEF_FSMRETRY 3        /* FSM retry frequency */
#define DEF_FSMTRIES 5        /* Default max retries */
#define DEF_FSMAUTHTRIES 3    /* Default max auth retries */
#define PPP_FSM_TIME_INTERVAL   6000

/*
 *  State of machine
 */
#define    ST_INITIAL    0
#define    ST_STARTING    1
#define    ST_CLOSED    2
#define    ST_STOPPED    3
#define    ST_CLOSING    4
#define    ST_STOPPING    5
#define    ST_REQSENT    6
#define    ST_ACKRCVD    7
#define    ST_ACKSENT    8
#define    ST_OPENED    9

#define    ST_MAX        10
#define    ST_UNDEF    -1

#define    MODE_REQ    0
#define    MODE_NAK    1
#define    MODE_REJ    2
#define    MODE_NOP    3
#define    MODE_ACK    4    /* pseudo mode for ccp negotiations */

#define    OPEN_PASSIVE    -1

#define FSM_REQ_TIMER    1
#define FSM_TRM_TIMER    2

#define FSM_OPTLEN    100

struct fsm;


struct fsm_retry {
  VOS_UINT32 timeout;                             /* FSM retry frequency */
  VOS_UINT32 maxreq;                              /* Max Config REQ retries */
  VOS_UINT32 maxtrm;                              /* Max Term REQ retries */
};

struct fsm_decode {
  VOS_CHAR ack[FSM_OPTLEN], *ackend;
  VOS_CHAR nak[FSM_OPTLEN], *nakend;
  VOS_CHAR rej[FSM_OPTLEN], *rejend;
};

struct fsm_callbacks {
  VOS_INT32 (*LayerUp)(struct fsm *);                 /* Layer is now up (tlu) */
  void (*LayerDown)(struct fsm *);              /* About to come down (tld) */
  void (*LayerStart)(struct fsm *);             /* Layer about to start (tls) */
  void (*LayerFinish)(struct fsm *);            /* Layer now down (tlf) */
  void (*InitRestartCounter)(struct fsm *, VOS_INT32);/* Set fsm timer load */
  void (*SendConfigReq)(struct fsm *);          /* Send REQ please */
  void (*SentTerminateReq)(struct fsm *);       /* Term REQ just sent */
  void (*SendTerminateAck)(struct fsm *, VOS_CHAR); /* Send Term ACK please */
  void (*DecodeConfig)(struct fsm *, VOS_CHAR *, VOS_CHAR *, VOS_INT32,
                       struct fsm_decode *);    /* Deal with incoming data */
  VOS_INT32 (*RecvResetReq)(struct fsm *fp);          /* Reset output */
  void (*RecvResetAck)(struct fsm *, VOS_CHAR); /* Reset input */
};

struct fsm_parent {
  void (*LayerStart) (void *, struct fsm *);         /* tls */
  void (*LayerUp) (void *, struct fsm *);            /* tlu */
  void (*LayerDown) (void *, struct fsm *);          /* tld */
  void (*LayerFinish) (void *, struct fsm *);        /* tlf */
  void *object;
};




struct fsm {
  const VOS_CHAR *name;        /* Name of protocol */
  VOS_UINT16 proto;        /* Protocol number */
  VOS_UINT16 min_code;
  VOS_UINT16 max_code;
  VOS_CHAR reqid;            /* Next request id */
  VOS_CHAR  aucReseved[1];
  VOS_INT32 open_mode;        /* Delay before config REQ (-1 forever) */
  VOS_INT32 state;            /* State of the machine */
  VOS_INT32 restart;            /* Restart counter value */
  HTIMER     timer;
  struct {
    VOS_INT32 reqs;            /* Max config REQs before a close() */
    VOS_INT32 naks;            /* Max config NAKs before a close() */
    VOS_INT32 rejs;            /* Max config REJs before a close() */
  } more;

/*fanzhibin f49086 delete it*/
/*  struct pppTimer FsmTimer;    */   /* Restart Timer */
/*  struct pppTimer OpenTimer;*/    /* Delay before opening */

  /*
   * This timer times the ST_STOPPED state out after the given value
   * (specified via "set stopped ...").  Although this isn't specified in the
   * rfc, the rfc *does* say that "the application may use higher level
   * timers to avoid deadlock". The StoppedTimer takes effect when the other
   * side ABENDs rather than going into ST_ACKSENT (and sending the ACK),
   * causing ppp to time out and drop into ST_STOPPED.  At this point,
   * nothing will change this state :-(
   */
/*fanzhibin f49086 delete it*/
/*  struct pppTimer StoppedTimer;*/
  VOS_INT32 LogLevel;

  /* The link layer active with this FSM (may be our bundle below) */
  struct link *link;


#if 0/*fanzhibin f49086 delete it*/
  /* Our high-level link */
  struct bundle *bundle;
#endif

  const struct fsm_parent *parent;
  const struct fsm_callbacks *fn;
};

struct fsmheader {
  VOS_CHAR code;            /* Request code */
  VOS_CHAR id;            /* Identification */
  VOS_UINT16 length;        /* Length of packet */
};

#define    CODE_CONFIGREQ    1
#define    CODE_CONFIGACK    2
#define    CODE_CONFIGNAK    3
#define    CODE_CONFIGREJ    4
#define    CODE_TERMREQ    5
#define    CODE_TERMACK    6
#define    CODE_CODEREJ    7
#define    CODE_PROTOREJ    8
#define    CODE_ECHOREQ    9    /* Used in LCP */
#define    CODE_ECHOREP    10    /* Used in LCP */
#define    CODE_DISCREQ    11
#define    CODE_IDENT    12    /* Used in LCP Extension */
#define    CODE_TIMEREM    13    /* Used in LCP Extension */
#define    CODE_RESETREQ    14    /* Used in CCP */
#define    CODE_RESETACK    15    /* Used in CCP */

struct fsm_opt_hdr {
  VOS_UINT8 id;
  VOS_UINT8 len;
};

#define MAX_FSM_OPT_LEN 52
struct fsm_opt {
  struct fsm_opt_hdr hdr;
#if 0    /* in BSD, type is u_char, so use VOS_UINT8 by liukai */
  VOS_CHAR data[MAX_FSM_OPT_LEN-2];
#else
  VOS_UINT8 data[MAX_FSM_OPT_LEN-2];
#endif
};

#define INC_FSM_OPT(ty, length, o)                      \
  do {                                                  \
    (o)->hdr.id = (ty);                                 \
    (o)->hdr.len = (length);                            \
    (o) = (struct fsm_opt *)((VOS_CHAR *)(o) + (length)); \
  } while (0)

/*fanzhibin f49086 change it begin*/
extern const char *command_ShowNegval(unsigned val);
/*fanzhibin f49086 change it begin*/

extern void FsmTimeout(void *,VOS_UINT32);


extern void fsm_Init(struct fsm *, const VOS_CHAR *, VOS_UINT16, VOS_INT32, VOS_INT32, VOS_INT32,
                     /*struct bundle *, */struct link *, const  struct fsm_parent *,
                     struct fsm_callbacks *, const VOS_CHAR * const [3]);
extern void fsm_Output(struct fsm *, VOS_CHAR, VOS_CHAR, VOS_CHAR *, VOS_INT32, VOS_INT32);
extern void fsm_Open(struct fsm *);
extern void fsm_Up(struct fsm *);
extern void fsm_Down(struct fsm *);
extern void fsm_Input(struct fsm *, struct ppp_mbuf *);
extern void fsm_Close(struct fsm *);
extern VOS_INT32 fsm_NullRecvResetReq(struct fsm *);
extern void fsm_NullRecvResetAck(struct fsm *, VOS_CHAR);
extern void fsm_Reopen(struct fsm *);
extern void fsm2initial(struct fsm *);
extern const VOS_CHAR *State2Nam(VOS_UINT32);
extern struct fsm_opt *fsm_readopt(VOS_CHAR **);
extern void fsm_rej(struct fsm_decode *, const struct fsm_opt *);
extern void fsm_ack(struct fsm_decode *, const struct fsm_opt *);
extern void fsm_nak(struct fsm_decode *, const struct fsm_opt *);
extern void fsm_opt_normalise(struct fsm_decode *);
#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#endif /* end of ppp_fsm.h */
