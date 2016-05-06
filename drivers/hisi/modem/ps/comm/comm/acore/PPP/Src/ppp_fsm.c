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
 * $FreeBSD: src/usr.sbin/ppp/fsm.c,v 1.69 2002/08/25 13:30:34 charnier Exp $
 */

#include "PPP/Inc/ppp_public.h"
#include "PPP/Inc/layer.h"
#include "PPP/Inc/ppp_mbuf.h"
#include "PPP/Inc/hdlc.h"
#include "PPP/Inc/throughput.h"
#include "PPP/Inc/proto.h"
#include "PPP/Inc/ppp_fsm.h"
#include "PPP/Inc/lcp.h"
#include "PPP/Inc/async.h"
#include "PPP/Inc/auth.h"
#include "PPP/Inc/ipcp.h"
#include "PPP/Inc/link.h"
#include "PPP/Inc/pap.h"
#include "PPP/Inc/ppp_input.h"
#include "PPP/Inc/ppp_atcmd.h"

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_PPP_FSM_C

#if(FEATURE_ON == FEATURE_PPP)

void FsmSendConfigReq(struct fsm *);
void FsmSendTerminateReq(struct fsm *);
void FsmInitRestartCounter(struct fsm *, VOS_INT32);

typedef void (recvfn)(struct fsm *, struct fsmheader *, struct ppp_mbuf *);
static recvfn FsmRecvConfigReq, FsmRecvConfigAck, FsmRecvConfigNak,
              FsmRecvConfigRej, FsmRecvTermReq, FsmRecvTermAck,
              FsmRecvCodeRej, FsmRecvProtoRej, FsmRecvEchoReq,
              FsmRecvEchoRep, FsmRecvDiscReq, FsmRecvIdent,
              FsmRecvTimeRemain, FsmRecvResetReq, FsmRecvResetAck;

static const struct fsmcodedesc {
  recvfn *recv;
  unsigned check_reqid : 1;
  unsigned inc_reqid : 1;
  const VOS_CHAR *name;
} FsmCodes[] = {
  { FsmRecvConfigReq, 0, 0, "ConfigReq"    },
  { FsmRecvConfigAck, 1, 1, "ConfigAck"    },
  { FsmRecvConfigNak, 1, 1, "ConfigNak"    },
  { FsmRecvConfigRej, 1, 1, "ConfigRej"    },
  { FsmRecvTermReq,   0, 0, "TerminateReq" },
  { FsmRecvTermAck,   1, 1, "TerminateAck" },
  { FsmRecvCodeRej,   0, 0, "CodeRej"      },
  { FsmRecvProtoRej,  0, 0, "ProtocolRej"  },
  { FsmRecvEchoReq,   0, 0, "EchoRequest"  },
  { FsmRecvEchoRep,   0, 0, "EchoReply"    },
  { FsmRecvDiscReq,   0, 0, "DiscardReq"   },
  { FsmRecvIdent,     0, 1, "Ident"        },
  { FsmRecvTimeRemain,0, 0, "TimeRemain"   },
  { FsmRecvResetReq,  0, 0, "ResetReq"     },
  { FsmRecvResetAck,  0, 1, "ResetAck"     }
};

const char *
command_ShowNegval(unsigned val)
{
  switch (val&3) {
    case 1: return "disabled & accepted";
    case 2: return "enabled & denied";
    case 3: return "enabled & accepted";
  }
  return "disabled & denied";
}






const VOS_CHAR *
Code2Nam(VOS_UINT32 code)
{
  if (code == 0 || code > sizeof FsmCodes / sizeof FsmCodes[0])
    return "Unknown";
  return FsmCodes[code-1].name;
}

const VOS_CHAR *
State2Nam(VOS_UINT32 state)
{
  static const VOS_CHAR * const StateNames[] = {
    "Initial", "Starting", "Closed", "Stopped", "Closing", "Stopping",
    "Req-Sent", "Ack-Rcvd", "Ack-Sent", "Opened",
  };

  if (state >= sizeof StateNames / sizeof StateNames[0])
    return "unknown";
  return StateNames[state];
}

void
StoppedTimeout(void *v)
{/*
  struct fsm *fp = (struct fsm *)v;

  log_Printf(fp->LogLevel, "%s: Stopped timer expired\n", fp->link->name);
  if (fp->OpenTimer.state == TIMER_RUNNING) {
    log_Printf(LogWARN, "%s: %s: aborting open delay due to stopped timer\n",
              fp->link->name, fp->name);
    timer_Stop(&fp->OpenTimer);
  }
  if (fp->state == ST_STOPPED)
    fsm2initial(fp);*/
}

void
fsm_Init(struct fsm *fp, const VOS_CHAR *name, VOS_UINT16 proto, VOS_INT32 mincode,
         VOS_INT32 maxcode, VOS_INT32 LogLevel,/* struct bundle *bundle,*/
         struct link *l, const struct fsm_parent *parent,
         struct fsm_callbacks *fn, const VOS_CHAR * const timer_names[3])
{
  fp->name = name;
  fp->proto = proto;
  fp->min_code = (VOS_UINT16)mincode;
  fp->max_code = (VOS_UINT16)maxcode;
  fp->state = fp->min_code > CODE_TERMACK ? ST_OPENED : ST_INITIAL;
  fp->reqid = 1;
  fp->restart = 1;
  fp->more.reqs = fp->more.naks = fp->more.rejs = 3;
/*  PS_MEM_SET(&fp->FsmTimer, '\0', sizeof fp->FsmTimer);
  PS_MEM_SET(&fp->OpenTimer, '\0', sizeof fp->OpenTimer);
  PS_MEM_SET(&fp->StoppedTimer, '\0', sizeof fp->StoppedTimer);*/
  fp->LogLevel = LogLevel;
  fp->link = l;
/*  fp->bundle = bundle;*/
  fp->parent = parent;
  fp->fn = fn;
  fp->timer = VOS_NULL;
/*  fp->FsmTimer.name = timer_names[0];
  fp->OpenTimer.name = timer_names[1];
  fp->StoppedTimer.name = timer_names[2];*/
}

void
NewState(struct fsm *fp, VOS_INT32 new)
{

/*fanzhibin f49086 change it begin*/


#if 0/*fanzhibin f49086 delete it*/
  log_Printf(fp->LogLevel, "%s: State change %s --> %s\n",
             fp->link->name, State2Nam(fp->state), State2Nam(new));
  if (fp->state == ST_STOPPED && fp->StoppedTimer.state == TIMER_RUNNING)
    timer_Stop(&fp->StoppedTimer);
  fp->state = new;
  if ((new >= ST_INITIAL && new <= ST_STOPPED) || (new == ST_OPENED)) {
    timer_Stop(&fp->FsmTimer);
    if (new == ST_STOPPED && fp->StoppedTimer.load) {
      timer_Stop(&fp->StoppedTimer);
      fp->StoppedTimer.func = StoppedTimeout;
      fp->StoppedTimer.arg = (void *) fp;
      timer_Start(&fp->StoppedTimer);
    }
  }
#endif

  PPP_MNTN_LOG1(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "NewState: <1>\r\n",new);
  fp->state = new;
  return;
/*fanzhibin f49086 change it end*/
}


/* BEGIN: changed by fanzhibin 49086, 2006/5/12   PN:A32D03785*/
void
fsm_Output(struct fsm *fp, VOS_CHAR code, VOS_CHAR id, VOS_CHAR *ptr, VOS_INT32 count,
           VOS_INT32 mtype)
{
/* END: changed by fanzhibin 49086, 2006/5/12   PN:A32D03785*/

  VOS_INT32 plen;
  struct fsmheader lh;
  struct ppp_mbuf *bp;


  PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "fsm_Output\r\n");
  plen = sizeof(struct fsmheader) + count;
  lh.code = code;
  lh.id = id;
  lh.length = (VOS_UINT16)VOS_HTONS(plen);

    bp = ppp_m_get(plen + PPP_RECIEVE_RESERVE_FOR_HEAD + PPP_RECIEVE_RESERVE_FOR_TAIL);

  if(bp == VOS_NULL)
  {
        PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_WARNING, "no mbuf\r\n");
        return;
  }
    /*预留头部*/
    bp->m_offset = PPP_RECIEVE_RESERVE_FOR_HEAD;

    /*头部与尾部都留出来了*/
    bp->m_len = plen;

  PS_MEM_CPY(PPP_MBUF_CTOP(bp), &lh, sizeof(struct fsmheader));
  if (count)
  {
    PS_MEM_CPY(PPP_MBUF_CTOP(bp) + sizeof(struct fsmheader), ptr, count);
  }

  link_PushPacket(fp->link, bp, LINK_QUEUES(fp->link) - 1,
                  fp->proto);

  if (code == CODE_CONFIGREJ)
    lcp_SendIdentification(&fp->link->lcp);
}

void
FsmOpenNow(void *v)
{
  struct fsm *fp = (struct fsm *)v;
  PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "FsmOpenNow\r\n");
#if 0/*fanzhibin f49086 delete it*/
  timer_Stop(&fp->OpenTimer);
#endif

  if (fp->state <= ST_STOPPED) {
    if (fp->state != ST_STARTING) {
      /*
       * In practice, we're only here in ST_STOPPED (when delaying the
       * first config request) or ST_CLOSED (when openmode == 0).
       *
       * The ST_STOPPED bit is breaking the RFC already :-(
       *
       * According to the RFC (1661) state transition table, a TLS isn't
       * required for an Open event when state == Closed, but the RFC
       * must be wrong as TLS hasn't yet been called (since the last TLF)
       * ie, Initial gets an `Up' event, Closing gets a RTA etc.
       */
      (*fp->fn->LayerStart)(fp);
      (*fp->parent->LayerStart)(fp->parent->object, fp);
    }
    FsmInitRestartCounter(fp, FSM_REQ_TIMER);
    FsmSendConfigReq(fp);
    NewState(fp, ST_REQSENT);
  }
}

void
fsm_Open(struct fsm *fp)
{
  PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "fsm_Open\r\n");
  switch (fp->state) {
  case ST_INITIAL:
    NewState(fp, ST_STARTING);
    (*fp->fn->LayerStart)(fp);
    (*fp->parent->LayerStart)(fp->parent->object, fp);
    break;
  case ST_CLOSED:
    if (fp->open_mode == OPEN_PASSIVE) {
      NewState(fp, ST_STOPPED);        /* XXX: This is a hack ! */
    } else if (fp->open_mode > 0) {
      if (fp->open_mode > 1)
        PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "Entering STOPPED state for %d seconds\r\n");
      NewState(fp, ST_STOPPED);        /* XXX: This is a not-so-bad hack ! */
/*      timer_Stop(&fp->OpenTimer);
      fp->OpenTimer.load = fp->open_mode * SECTICKS;
      fp->OpenTimer.func = FsmOpenNow;
      fp->OpenTimer.arg = (void *)fp;
      timer_Start(&fp->OpenTimer);*/
    } else
      FsmOpenNow(fp);
    break;
  case ST_STOPPED:        /* XXX: restart option */
  case ST_REQSENT:
  case ST_ACKRCVD:
  case ST_ACKSENT:
  case ST_OPENED:        /* XXX: restart option */
    break;
  case ST_CLOSING:        /* XXX: restart option */
  case ST_STOPPING:        /* XXX: restart option */
    NewState(fp, ST_STOPPING);
    break;
/* BEGIN: changed by fanzhibin 49086, 2006/5/12   PN:A32D03785*/
  default:
    PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "not_exist_state\r\n");

/* END: changed by fanzhibin 49086, 2006/5/12   PN:A32D03785*/
  }
}

void
fsm_Up(struct fsm *fp)
{
  PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "fsm_Up\r\n");
  switch (fp->state) {
  case ST_INITIAL:
    PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL,"FSM: Using  as a transport\r\n");
    NewState(fp, ST_CLOSED);
    break;
  case ST_STARTING:
    FsmInitRestartCounter(fp, FSM_REQ_TIMER);
    FsmSendConfigReq(fp);
    NewState(fp, ST_REQSENT);
    break;
  default:
    PPP_MNTN_LOG1(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, " Up at state:<1>", fp->state);
    break;
  }
}

void
fsm_Down(struct fsm *fp)
{
  PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "fsm_Down\r\n");
  switch (fp->state) {
  case ST_CLOSED:
    NewState(fp, ST_INITIAL);
    break;
  case ST_CLOSING:
    /* This TLF contradicts the RFC (1661), which ``misses it out'' ! */
    (*fp->fn->LayerFinish)(fp);
    NewState(fp, ST_INITIAL);
    (*fp->parent->LayerFinish)(fp->parent->object, fp);
    break;
  case ST_STOPPED:
    NewState(fp, ST_STARTING);
    (*fp->fn->LayerStart)(fp);
    (*fp->parent->LayerStart)(fp->parent->object, fp);
    break;
  case ST_STOPPING:
  case ST_REQSENT:
  case ST_ACKRCVD:
  case ST_ACKSENT:
    NewState(fp, ST_STARTING);
    break;
  case ST_OPENED:
    (*fp->fn->LayerDown)(fp);
    NewState(fp, ST_STARTING);
    (*fp->parent->LayerDown)(fp->parent->object, fp);
    break;
  }
}

void
fsm_Close(struct fsm *fp)
{
  PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "fsm_Close\r\n");
  switch (fp->state) {
  case ST_STARTING:
    (*fp->fn->LayerFinish)(fp);
    NewState(fp, ST_INITIAL);
    (*fp->parent->LayerFinish)(fp->parent->object, fp);
    break;
  case ST_STOPPED:
    NewState(fp, ST_CLOSED);
    break;
  case ST_STOPPING:
    NewState(fp, ST_CLOSING);
    break;
  case ST_OPENED:
    (*fp->fn->LayerDown)(fp);
    if (fp->state == ST_OPENED) {
      FsmInitRestartCounter(fp, FSM_TRM_TIMER);
      FsmSendTerminateReq(fp);
      NewState(fp, ST_CLOSING);
      (*fp->parent->LayerDown)(fp->parent->object, fp);
    }
    break;
  case ST_REQSENT:
  case ST_ACKRCVD:
  case ST_ACKSENT:
    FsmInitRestartCounter(fp, FSM_TRM_TIMER);
    FsmSendTerminateReq(fp);
    NewState(fp, ST_CLOSING);
    break;
  }
}

/*
 *    Send functions
 */
void
FsmSendConfigReq(struct fsm *fp)
{
  PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "FsmSendConfigReq\r\n");
  if (fp->more.reqs-- > 0 && fp->restart-- > 0) {
    (*fp->fn->SendConfigReq)(fp);
/*    timer_Start(&fp->FsmTimer);    */    /* Start restart timer */
  } else {
    if (fp->more.reqs < 0)
      PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "%s: Too many %s REQs sent - abandoning "
                 "negotiation\r\n"/*, fp->link->name, fp->name*/);
    lcp_SendIdentification(&fp->link->lcp);
    fsm_Close(fp);
  }
}

void
FsmSendTerminateReq(struct fsm *fp)
{
  PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "FsmSendTerminateReq\r\n");
  fsm_Output(fp, CODE_TERMREQ, fp->reqid, VOS_NULL_PTR, 0, MB_UNKNOWN);
  (*fp->fn->SentTerminateReq)(fp);
/*  timer_Start(&fp->FsmTimer);    *//* Start restart timer */
  fp->restart--;        /* Decrement restart counter */
}

/*
 *    Timeout actions
 */
void FsmTimeout(void *v,VOS_UINT32 ipcp_or_lcp)
{

  struct fsm *fp = (struct fsm *)v;
  PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "FsmTimeout\r\n");

   if (fp->restart) {
     switch (fp->state) {
     case ST_CLOSING:
     case ST_STOPPING:
       FsmSendTerminateReq(fp);
       break;
     case ST_REQSENT:
     case ST_ACKSENT:
       FsmSendConfigReq(fp);
       break;
     case ST_ACKRCVD:
       FsmSendConfigReq(fp);
       NewState(fp, ST_REQSENT);
       break;
     }

   if(fp->state < ST_OPENED
    &&fp->state > ST_STOPPED)
   {
     if (VOS_OK != VOS_StartRelTimer(&(fp->timer),PS_PID_APP_PPP,
         PPP_FSM_TIME_INTERVAL,PPP_LINK_TO_ID(fp->link),ipcp_or_lcp,
         VOS_RELTIMER_NOLOOP, VOS_TIMER_PRECISION_0))
         {
               PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL,"start reltimer error\r\n");
         }
   }

 /*    timer_Start(&fp->FsmTimer);*/
   } else {
    switch (fp->state) {
    case ST_CLOSING:
      (*fp->fn->LayerFinish)(fp);
      NewState(fp, ST_CLOSED);
      (*fp->parent->LayerFinish)(fp->parent->object, fp);
      break;
    case ST_STOPPING:
      (*fp->fn->LayerFinish)(fp);
      NewState(fp, ST_STOPPED);
      (*fp->parent->LayerFinish)(fp->parent->object, fp);
      break;
    case ST_REQSENT:        /* XXX: 3p */
    case ST_ACKSENT:
    case ST_ACKRCVD:
      (*fp->fn->LayerFinish)(fp);
      NewState(fp, ST_STOPPED);
      (*fp->parent->LayerFinish)(fp->parent->object, fp);
      break;
    }

  }
}

void
FsmInitRestartCounter(struct fsm *fp, VOS_INT32 what)
{/*
  timer_Stop(&fp->FsmTimer);
  fp->FsmTimer.func = FsmTimeout;
  fp->FsmTimer.arg = (void *)fp;*/
  (*fp->fn->InitRestartCounter)(fp, what);
}

/*
 * Actions when receive packets
 */
void FsmRecvConfigReq(struct fsm *fp, struct fsmheader *lhp, struct ppp_mbuf *bp)
/* RCR */
{
  struct fsm_decode dec;
  VOS_INT32 plen, flen;
  VOS_INT32 ackaction = 0;
  VOS_CHAR *cp;
  /* lcp标志或ipcp pdp激活成功的标志, 该标杆在lcp阶段或ipcp pdp激活成功之后置1 */
  VOS_UINT32 lcpOrIpcpAck = 1;

  PPP_REQ_CONFIG_INFO_STRU PppReqConfigInfo;
  VOS_UINT8 SendBuffer[200];

  PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "FsmRecvConfigReq");
  bp = ppp_m_pullup(bp);
  plen = ppp_m_length(bp);
  flen = VOS_NTOHS(lhp->length) - sizeof *lhp;
  if (plen < flen) {
    PPP_MNTN_LOG2(PS_PID_APP_PPP, 0, PS_PRINT_WARNING, "FsmRecvConfigReq: plen %d < flen %d\r\n", plen, flen);
    ppp_m_freem(bp);
    return;
  }

  /* Some things must be done before we Decode the packet */
  switch (fp->state) {
  case ST_OPENED:
    (*fp->fn->LayerDown)(fp);
  }

  dec.ackend = dec.ack;
  dec.nakend = dec.nak;
  dec.rejend = dec.rej;
  cp = PPP_MBUF_CTOP(bp);

  if(fp->link->phase == PHASE_NETWORK)
  {
      /* ipcp阶段，该标志置0 */
      lcpOrIpcpAck = 0;
      switch(fp->link->ipcp.stage)
      {
          case IPCP_NOT_RECEIVE_REQ:
          {
          PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "send info to at\r\n");
          fp->link->ipcp.stage = IPCP_REQ_RECEIVED;

          /* fill authentication data */
          if (PROTO_CHAP == fp->link->lcp.want_auth)
          {
              PppReqConfigInfo.stAuth.ucAuthType = PPP_CHAP_AUTH_TYPE;

              PppReqConfigInfo.stAuth.AuthContent.ChapContent.pChapChallenge
                  = fp->link->chap.RecordData.BufChallenge;
              PppReqConfigInfo.stAuth.AuthContent.ChapContent.usChapChallengeLen
                  = fp->link->chap.RecordData.LenOfChallenge;

              PppReqConfigInfo.stAuth.AuthContent.ChapContent.pChapResponse
                  = fp->link->chap.RecordData.BufResponse;
              PppReqConfigInfo.stAuth.AuthContent.ChapContent.usChapResponseLen
                  = fp->link->chap.RecordData.LenOfResponse;
          }
          else if (PROTO_PAP == fp->link->lcp.want_auth)
          {
              PppReqConfigInfo.stAuth.ucAuthType = PPP_PAP_AUTH_TYPE;

              PppReqConfigInfo.stAuth.AuthContent.PapContent.pPapReq
                  = fp->link->pap.RecordData.BufRequest;
              PppReqConfigInfo.stAuth.AuthContent.PapContent.usPapReqLen
                  = fp->link->pap.RecordData.LenOfRequest;
          }
          else
          {
              PppReqConfigInfo.stAuth.ucAuthType = PPP_NO_AUTH_TYPE;
          }

          /* fill ipcp data */
          PppReqConfigInfo.stIPCP.pIpcp = SendBuffer;
          PppReqConfigInfo.stIPCP.usIpcpLen = (VOS_UINT16)(flen + sizeof(struct fsmheader));

          /*把ipcp config req报文的头拷贝进去*/
          PS_MEM_CPY(SendBuffer,lhp,sizeof(struct fsmheader));
          /*把ipcp config req报文的option拷贝进去*/
          PS_MEM_CPY((SendBuffer + sizeof(struct fsmheader)),cp,flen);

          #if (PPP_FEATURE == PPP_FEATURE_PPP)
          /* 可维可测信息上报*/
          Ppp_RcvConfigInfoReqMntnInfo((VOS_UINT16)PPP_LINK_TO_ID(fp->link), &PppReqConfigInfo);

          /*PDP激活请求，发送用户名、密码还有IPCP数据包*/
          PPP_ProcTeConfigInfo((VOS_UINT16)PPP_LINK_TO_ID(fp->link),&PppReqConfigInfo);
          #else
          PPPoE_PPPSendAuthToGGSN((PPP_ID)(PPP_LINK_TO_ID(fp->link)),&PppReqConfigInfo);
          #endif
          }
          break;

          case IPCP_REQ_RECEIVED:
          {
            PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "have receive ipcp req\r\n");
          }
          break;

          case IPCP_SUCCESS_FROM_GGSN:
          {
            /* ipcp阶段，PDP激活成功该标志置1 */
            lcpOrIpcpAck = 1;
            PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "have receive from ggsn\r\n");
          }
          break;

          default:
          {
            PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "unknow ipcp stage\r\n");
            ppp_m_freem(bp);
            return;
          }
      }


  }

  /* 如果PDP激活未成功,不去解帧,直接回NAK,NAK里面不带任何OPTION项 */
  if (1 == lcpOrIpcpAck)
  {
    (*fp->fn->DecodeConfig)(fp, cp, cp + flen, MODE_REQ, &dec);
  }

  if (flen < sizeof(struct fsm_opt_hdr))
    PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "  [EMPTY]");

  if ((dec.nakend == dec.nak) && (dec.rejend == dec.rej)
     && (1 == lcpOrIpcpAck))
  {
    ackaction = 1;
  }

  /* Check and process easy case */
  switch (fp->state) {
  case ST_INITIAL:
    if (fp->proto == PROTO_CCP && fp->link->lcp.fsm.state == ST_OPENED) {
      /*
       * ccp_SetOpenMode() leaves us in initial if we're disabling
       * & denying everything.
       */
      bp = ppp_m_prepend(bp, lhp, sizeof *lhp, 2);
      bp = proto_Prepend(bp, fp->proto, 0, 0);
      bp = ppp_m_pullup(bp);
      lcp_SendProtoRej(&fp->link->lcp, PPP_MBUF_CTOP(bp), bp->m_len);
      ppp_m_freem(bp);
      return;
    }
    /* Drop through */
  case ST_STARTING:
    ppp_m_freem(bp);
    return;
  case ST_CLOSED:
    (*fp->fn->SendTerminateAck)(fp, lhp->id);
    ppp_m_freem(bp);
    return;
  case ST_CLOSING:
    PPP_MNTN_LOG1(PS_PID_APP_PPP, 0, LOG_LEVEL_WARNING,
                  "Error: Got ConfigReq while state = %d\r\n", fp->state);
  case ST_STOPPING:
    ppp_m_freem(bp);
    return;
  case ST_STOPPED:
    FsmInitRestartCounter(fp, FSM_REQ_TIMER);
    /* Drop through */
  case ST_OPENED:
    FsmSendConfigReq(fp);
    break;
  }

  if (dec.rejend != dec.rej)
    fsm_Output(fp, CODE_CONFIGREJ, lhp->id, dec.rej, dec.rejend - dec.rej,
               MB_UNKNOWN);
  if ((dec.nakend != dec.nak) || (0 == lcpOrIpcpAck))
  {
    fsm_Output(fp, CODE_CONFIGNAK, lhp->id, dec.nak, dec.nakend - dec.nak,
               MB_UNKNOWN);
  }
  if (ackaction)
    fsm_Output(fp, CODE_CONFIGACK, lhp->id, dec.ack, dec.ackend - dec.ack,
               MB_UNKNOWN);

  switch (fp->state) {
  case ST_STOPPED:
      /*
       * According to the RFC (1661) state transition table, a TLS isn't
       * required for a RCR when state == ST_STOPPED, but the RFC
       * must be wrong as TLS hasn't yet been called (since the last TLF)
       */
    (*fp->fn->LayerStart)(fp);
    (*fp->parent->LayerStart)(fp->parent->object, fp);
    /* FALLTHROUGH */

  case ST_OPENED:
    if (ackaction)
      NewState(fp, ST_ACKSENT);
    else
      NewState(fp, ST_REQSENT);
    (*fp->parent->LayerDown)(fp->parent->object, fp);
    break;
  case ST_REQSENT:
    if (ackaction)
      NewState(fp, ST_ACKSENT);
    break;
  case ST_ACKRCVD:
    if (ackaction) {
      NewState(fp, ST_OPENED);
      if ((*fp->fn->LayerUp)(fp))
        (*fp->parent->LayerUp)(fp->parent->object, fp);
      else {
        (*fp->fn->LayerDown)(fp);
        FsmInitRestartCounter(fp, FSM_TRM_TIMER);
        FsmSendTerminateReq(fp);
        NewState(fp, ST_CLOSING);
        lcp_SendIdentification(&fp->link->lcp);
      }
    }
    break;
  case ST_ACKSENT:
    if (!ackaction)
      NewState(fp, ST_REQSENT);
    break;
  }
  ppp_m_freem(bp);

  if (dec.rejend != dec.rej && --fp->more.rejs <= 0) {
    PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "Too many REJs sent - abandoning negotiation\r\n");
    lcp_SendIdentification(&fp->link->lcp);
    fsm_Close(fp);
  }

  if (dec.nakend != dec.nak && --fp->more.naks <= 0) {
    PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "Too many NAKs sent - abandoning negotiation\r\n");
    lcp_SendIdentification(&fp->link->lcp);
    /*fsm_Close(fp); */
  }
}

void
FsmRecvConfigAck(struct fsm *fp, struct fsmheader *lhp, struct ppp_mbuf *bp)
/* RCA */
{
  struct fsm_decode dec;
  VOS_INT32 plen, flen;
  VOS_CHAR *cp;

  PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL,"FsmRecvConfigAck\r\n");
  plen = ppp_m_length(bp);
  flen = VOS_NTOHS(lhp->length) - sizeof *lhp;
  if (plen < flen) {
    ppp_m_freem(bp);
    return;
  }

  bp = ppp_m_pullup(bp);
  dec.ackend = dec.ack;
  dec.nakend = dec.nak;
  dec.rejend = dec.rej;
  cp = PPP_MBUF_CTOP(bp);
  (*fp->fn->DecodeConfig)(fp, cp, cp + flen, MODE_ACK, &dec);
  if (flen < sizeof(struct fsm_opt_hdr))
    PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "  [EMPTY]\r\n");

  switch (fp->state) {
    case ST_CLOSED:
    case ST_STOPPED:
    (*fp->fn->SendTerminateAck)(fp, lhp->id);
    break;
  case ST_CLOSING:
  case ST_STOPPING:
    break;
  case ST_REQSENT:
    FsmInitRestartCounter(fp, FSM_REQ_TIMER);
    NewState(fp, ST_ACKRCVD);
    break;
  case ST_ACKRCVD:
    FsmSendConfigReq(fp);
    NewState(fp, ST_REQSENT);
    break;
  case ST_ACKSENT:
    FsmInitRestartCounter(fp, FSM_REQ_TIMER);
    NewState(fp, ST_OPENED);
    if ((*fp->fn->LayerUp)(fp))
      (*fp->parent->LayerUp)(fp->parent->object, fp);
    else {
      (*fp->fn->LayerDown)(fp);
      FsmInitRestartCounter(fp, FSM_TRM_TIMER);
      FsmSendTerminateReq(fp);
      NewState(fp, ST_CLOSING);
      lcp_SendIdentification(&fp->link->lcp);
    }
    break;
  case ST_OPENED:
    (*fp->fn->LayerDown)(fp);
    FsmSendConfigReq(fp);
    NewState(fp, ST_REQSENT);
    (*fp->parent->LayerDown)(fp->parent->object, fp);
    break;
  }
  ppp_m_freem(bp);
}

void
FsmRecvConfigNak(struct fsm *fp, struct fsmheader *lhp, struct ppp_mbuf *bp)
/* RCN */
{
  struct fsm_decode dec;
  VOS_INT32 plen, flen;
  VOS_CHAR *cp;

  PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "FsmRecvConfigNak\r\n");

  plen = ppp_m_length(bp);
  flen = VOS_NTOHS(lhp->length) - sizeof *lhp;
  if (plen < flen) {
    ppp_m_freem(bp);
    return;
  }

  /*
   * Check and process easy case
   */
  switch (fp->state) {
  case ST_INITIAL:
  case ST_STARTING:
    PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "starting\r\n");
    ppp_m_freem(bp);
    return;
  case ST_CLOSED:
  case ST_STOPPED:
    (*fp->fn->SendTerminateAck)(fp, lhp->id);
    ppp_m_freem(bp);
    return;
  case ST_CLOSING:
  case ST_STOPPING:
    ppp_m_freem(bp);
    return;
  }

  bp = ppp_m_pullup(bp);
  dec.ackend = dec.ack;
  dec.nakend = dec.nak;
  dec.rejend = dec.rej;
  cp = PPP_MBUF_CTOP(bp);
  (*fp->fn->DecodeConfig)(fp, cp, cp + flen, MODE_NAK, &dec);
  if (flen < sizeof(struct fsm_opt_hdr))
    PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "  [EMPTY]\n");

  switch (fp->state) {
  case ST_REQSENT:
  case ST_ACKSENT:
    FsmInitRestartCounter(fp, FSM_REQ_TIMER);
    FsmSendConfigReq(fp);
    break;
  case ST_OPENED:
    (*fp->fn->LayerDown)(fp);
    FsmSendConfigReq(fp);
    NewState(fp, ST_REQSENT);
    (*fp->parent->LayerDown)(fp->parent->object, fp);
    break;
  case ST_ACKRCVD:
    FsmSendConfigReq(fp);
    NewState(fp, ST_REQSENT);
    break;
  }

  ppp_m_freem(bp);
}

void
FsmRecvTermReq(struct fsm *fp, struct fsmheader *lhp, struct ppp_mbuf *bp)
/* RTR */
{
  PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "FsmRecvTermReq\r\n");

  switch (fp->state) {
  case ST_INITIAL:
  case ST_STARTING:
    PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "state=init or starting\r\n");
    break;
  case ST_CLOSED:
  case ST_STOPPED:
  case ST_CLOSING:
  case ST_STOPPING:
  case ST_REQSENT:
    (*fp->fn->SendTerminateAck)(fp, lhp->id);
    break;
  case ST_ACKRCVD:
  case ST_ACKSENT:
    (*fp->fn->SendTerminateAck)(fp, lhp->id);
    NewState(fp, ST_REQSENT);
    break;
  case ST_OPENED:
    (*fp->fn->LayerDown)(fp);
    (*fp->fn->SendTerminateAck)(fp, lhp->id);
    FsmInitRestartCounter(fp, FSM_TRM_TIMER);
/*    timer_Start(&fp->FsmTimer);        */    /* Start restart timer */
    fp->restart = 0;
    NewState(fp, ST_STOPPING);
    (*fp->parent->LayerDown)(fp->parent->object, fp);
    /* A delayed ST_STOPPED is now scheduled */
    if (fp == &(fp->link->lcp.fsm))    /* if rx-ed LCP-Terminate, after tx Terminate-Ack, change link state */
    {
        fp->link->phase = PHASE_TERMINATE;
    }

    #if (PPP_FEATURE == PPP_FEATURE_PPP)
    /*通知AT进行PDP去激活*/
    PPP_ProcPppRelEvent((VOS_UINT16)PPP_LINK_TO_ID(fp->link));
    #endif

    break;
  }
  ppp_m_freem(bp);
}

void
FsmRecvTermAck(struct fsm *fp, struct fsmheader *lhp, struct ppp_mbuf *bp)
/* RTA */
{
  PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "FsmRecvTermAck\r\n");

  switch (fp->state) {
  case ST_CLOSING:
    (*fp->fn->LayerFinish)(fp);
    NewState(fp, ST_CLOSED);
    (*fp->parent->LayerFinish)(fp->parent->object, fp);
    break;
  case ST_STOPPING:
    (*fp->fn->LayerFinish)(fp);
    NewState(fp, ST_STOPPED);
    (*fp->parent->LayerFinish)(fp->parent->object, fp);
    break;
  case ST_ACKRCVD:
    NewState(fp, ST_REQSENT);
    break;
  case ST_OPENED:
    (*fp->fn->LayerDown)(fp);
    FsmSendConfigReq(fp);
    NewState(fp, ST_REQSENT);
    (*fp->parent->LayerDown)(fp->parent->object, fp);
    break;
  }
  ppp_m_freem(bp);
}

void
FsmRecvConfigRej(struct fsm *fp, struct fsmheader *lhp, struct ppp_mbuf *bp)
/* RCJ */
{

  struct fsm_decode dec;
  VOS_INT32 plen, flen;
  VOS_CHAR *cp;
  PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "FsmRecvConfigRej\r\n");
  plen = ppp_m_length(bp);
  flen = VOS_NTOHS(lhp->length) - sizeof *lhp;
  if (plen < flen) {
    ppp_m_freem(bp);
    return;
  }

  lcp_SendIdentification(&fp->link->lcp);

  /*
   * Check and process easy case
   */
  switch (fp->state) {
  case ST_INITIAL:
  case ST_STARTING:
    PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "starting\r\n");
    ppp_m_freem(bp);
    return;
  case ST_CLOSED:
  case ST_STOPPED:
    (*fp->fn->SendTerminateAck)(fp, lhp->id);
    ppp_m_freem(bp);
    return;
  case ST_CLOSING:
  case ST_STOPPING:
    ppp_m_freem(bp);
    return;
  }

  bp = ppp_m_pullup(bp);
  dec.ackend = dec.ack;
  dec.nakend = dec.nak;
  dec.rejend = dec.rej;
  cp = PPP_MBUF_CTOP(bp);
  (*fp->fn->DecodeConfig)(fp, cp, cp + flen, MODE_REJ, &dec);
  if (flen < sizeof(struct fsm_opt_hdr))
    PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "[EMPTY]\r\n");

  switch (fp->state) {
  case ST_REQSENT:
  case ST_ACKSENT:
    FsmInitRestartCounter(fp, FSM_REQ_TIMER);
    FsmSendConfigReq(fp);
    break;
  case ST_OPENED:
    (*fp->fn->LayerDown)(fp);
    FsmSendConfigReq(fp);
    NewState(fp, ST_REQSENT);
    (*fp->parent->LayerDown)(fp->parent->object, fp);
    break;
  case ST_ACKRCVD:
    FsmSendConfigReq(fp);
    NewState(fp, ST_REQSENT);
    break;
  }
  ppp_m_freem(bp);
}

void
FsmRecvCodeRej(struct fsm *fp, struct fsmheader *lhp, struct ppp_mbuf *bp)
{
  PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "FsmRecvCodeRej\r\n");
  ppp_m_freem(bp);
}

void
FsmRecvProtoRej(struct fsm *fp, struct fsmheader *lhp, struct ppp_mbuf *bp)
{
/*  struct physical *p = link2physical(fp->link);*/
  VOS_UINT16 proto;
  PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "FsmRecvProtoRej\r\n");
  if (ppp_m_length(bp) < 2) {
    ppp_m_freem(bp);
    return;
  }
  bp = ppp_mbuf_Read(bp, &proto, 2);
  proto = VOS_NTOHS(proto);
  PPP_MNTN_LOG1(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "Protocol was rejected <1>\r\n",proto);

  switch (proto) {
  case PROTO_LQR:
 /*   if (p)
      lqr_Stop(p, LQM_LQR);
    else
      log_Printf(LogERROR, "%s: FsmRecvProtoRej: Not a physical link !\n",
                fp->link->name);*/
    break;
  case PROTO_CCP:
#if 0 /*fanzhibin f49086 delete it*/
    if (fp->proto == PROTO_LCP) {
      fp = &fp->link->ccp.fsm;
      /* Despite the RFC (1661), don't do an out-of-place TLF */
       (*fp->fn->LayerFinish)(fp);
      switch (fp->state) {
      case ST_CLOSED:
      case ST_CLOSING:
        NewState(fp, ST_CLOSED);
        break;
      default:
        NewState(fp, ST_STOPPED);
        break;
      }
      /* See above */
      /* (*fp->parent->LayerFinish)(fp->parent->object, fp); */
    }
#endif
    break;
  case PROTO_IPCP:
    if (fp->proto == PROTO_LCP) {
      PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "%s: IPCP protocol reject closes IPCP !\r\n"/*,
                fp->link->name*/);
/*      fsm_Close(&fp->bundle->ncp.ipcp.fsm);*/
    }
    break;
#ifndef NOINET6
#ifndef NI_WITHSCOPEID
#define NI_WITHSCOPEID 0
#endif
  case PROTO_IPV6CP:
    if (fp->proto == PROTO_LCP) {
      PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "IPV6CP protocol reject closes IPV6CP");
/*      fsm_Close(&fp->bundle->ncp.ipv6cp.fsm);*/
    }
    break;
#endif
  case PROTO_MP:
    if (fp->proto == PROTO_LCP) {
      struct lcp *lcp = fsm2lcp(fp);

      if (lcp->want_mrru && lcp->his_mrru) { /* [false alarm]:移植开源代码 */
        PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "MP protocol reject is fatal\r\n");
        fsm_Close(fp);
      }
    }
    break;
  }
  ppp_m_freem(bp);
}

void
FsmRecvEchoReq(struct fsm *fp, struct fsmheader *lhp, struct ppp_mbuf *bp)
{
  struct lcp *lcp = fsm2lcp(fp);
  VOS_CHAR *cp;
  VOS_UINT32 magic;
  PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "FsmRecvEchoReq");
  bp = ppp_m_pullup(bp);

  if (lcp && VOS_NTOHS(lhp->length) - sizeof *lhp >= 4) {
    cp = PPP_MBUF_CTOP(bp);
    ua_ntohl(cp, &magic); /* [false alarm]:移植开源代码 */
    if (magic != lcp->his_magic) {
      PPP_MNTN_LOG2(PS_PID_APP_PPP, 0, LOG_LEVEL_WARNING,
                    "magic wrong,magic %d;his magic %d\r\n",
                    (VOS_INT32)magic,(VOS_INT32)lcp->his_magic);
      /* XXX: We should send terminate request */
    }
    if (fp->state == ST_OPENED) {
      ua_htonl(&lcp->want_magic, cp);  /* local magic */
      fsm_Output(fp, CODE_ECHOREP, lhp->id, cp,
                 VOS_NTOHS(lhp->length) - sizeof *lhp, MB_ECHOOUT);
    }
  }
  ppp_m_freem(bp);
}

void
FsmRecvEchoRep(struct fsm *fp, struct fsmheader *lhp, struct ppp_mbuf *bp)
{
  void *plcp;
  PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "FsmRecvEchoRep\r\n");
  plcp = fsm2lcp(fp);
  if (VOS_NULL_PTR == plcp)
  {
    PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "FsmRecvEchoRep::lcp is null.\r\n");
  }
  ppp_m_freem(bp);
}

void
FsmRecvDiscReq(struct fsm *fp, struct fsmheader *lhp, struct ppp_mbuf *bp)
{
  PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "FsmRecvDiscReq\r\n");
  ppp_m_freem(bp);
}

void
FsmRecvIdent(struct fsm *fp, struct fsmheader *lhp, struct ppp_mbuf *bp)
{
#if 0
  VOS_UINT32 magic;
  VOS_UINT16 len;
  VOS_CHAR *cp;
#endif

  PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "FsmRecvIdent\r\n");

#if 0
  /* ident流程现在不用 */
  len = VOS_NTOHS(lhp->length) - sizeof *lhp;
  if (len >= 4) {
    bp = ppp_m_pullup(ppp_m_append(bp, "", 1));
    cp = PPP_MBUF_CTOP(bp);
    ua_ntohl(cp, &magic);

    if (magic != fp->link->lcp.his_magic)
       PPP_MNTN_LOG2(PS_PID_APP_PPP, 0, LOG_LEVEL_WARNING,
                    "magic is wrong %d %d\r\n",(VOS_INT32)magic,
                    (VOS_INT32)fp->link->lcp.his_magic);
    cp[len] = '\0';
    lcp_RecvIdentification(&fp->link->lcp, cp + 4);
  }
#endif

  ppp_m_freem(bp);
}

void
FsmRecvTimeRemain(struct fsm *fp, struct fsmheader *lhp, struct ppp_mbuf *bp)
{
  PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "FsmRecvTimeRemain\r\n");
  ppp_m_freem(bp);
}

void
FsmRecvResetReq(struct fsm *fp, struct fsmheader *lhp, struct ppp_mbuf *bp)
{
  PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "FsmRecvResetReq\r\n");
  if ((*fp->fn->RecvResetReq)(fp)) {
    /*
     * All sendable compressed packets are queued in the first (lowest
     * priority) modem output queue.... dump 'em to the priority queue
     * so that they arrive at the peer before our ResetAck.
     */
    link_SequenceQueue(fp->link);
    fsm_Output(fp, CODE_RESETACK, lhp->id, VOS_NULL_PTR, 0, MB_CCPOUT);
  }
  ppp_m_freem(bp);
}

void
FsmRecvResetAck(struct fsm *fp, struct fsmheader *lhp, struct ppp_mbuf *bp)
{
  PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "FsmRecvResetAck\r\n");
  (*fp->fn->RecvResetAck)(fp, lhp->id);
  ppp_m_freem(bp);
}

void
fsm_Input(struct fsm *fp, struct ppp_mbuf *bp)
{
  VOS_INT32 len;
  struct fsmheader lh;
  const struct fsmcodedesc *codep;

  PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "fsm_Input\r\n");
  len = ppp_m_length(bp);
  if (len < sizeof(struct fsmheader)) {
    ppp_m_freem(bp);
    return;
  }
  bp = ppp_mbuf_Read(bp, &lh, sizeof lh);

  if (VOS_NTOHS(lh.length) > len) {
     PPP_MNTN_LOG2(PS_PID_APP_PPP, 0, LOG_LEVEL_WARNING,
                    "Got bytes %d;byte payload %d\r\n",
                    len, (VOS_INT32)VOS_NTOHS(lh.length));
    ppp_m_freem(bp);
    return;
  }

  if (lh.code < fp->min_code || lh.code > fp->max_code ||
      lh.code > sizeof FsmCodes / sizeof *FsmCodes) {
    /*
     * Use a private id.  This is really a response-type packet, but we
     * MUST send a unique id for each REQ....
     */
    static VOS_CHAR id;

    bp = ppp_m_prepend(bp, &lh, sizeof lh, 0);
    bp = ppp_m_pullup(bp);
    /*
       由于PPP state machine存在open->stopping后不闭环问题,
       经代码分析目前能够进入此分支的情况只有一个过程, 收到PC的code, UE不支持,
       UE发出Code-Reject, PC发出Terminate, UE发送Terminate-Ack,
       之后UE中PPP state machine始终停在stopping状态, 不闭环, 将导致用户拨号总是失败,
       直到用户PC重启
       如果要修正此问题, 目前PPP的定时器机制可能需要重新设计, 改动比较大,
       而且发生此错误的概率比较低, 故暂不修改, 仅是通过LOG把这种情况甄别出来
    */
    PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_ERROR, "UE sent Code-Reject!\r\n");
    fsm_Output(fp, CODE_CODEREJ, id++, PPP_MBUF_CTOP(bp), bp->m_len, MB_UNKNOWN);
    ppp_m_freem(bp);
    return;
  }

  codep = FsmCodes + lh.code - 1;
  if (lh.id != fp->reqid && codep->check_reqid/* &&
      Enabled(fp->bundle, OPT_IDCHECK)*/) {
    PPP_MNTN_LOG2(PS_PID_APP_PPP, 0, LOG_LEVEL_WARNING,"id %d,reqid %d\r\n", lh.id, fp->reqid);
    ppp_m_freem(bp);
    return;
  }

  PPP_MNTN_LOG1(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "state <1> ",fp->state);

  if (codep->inc_reqid && (lh.id == fp->reqid ||
      (/*!Enabled(fp->bundle, OPT_IDCHECK) && */codep->check_reqid)))
    fp->reqid++;    /* That's the end of that ``exchange''.... */

  (*codep->recv)(fp, &lh, bp);
}

VOS_INT32
fsm_NullRecvResetReq(struct fsm *fp)
{
  PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "received unexpected reset req\r\n");
  return 1;
}

void
fsm_NullRecvResetAck(struct fsm *fp, VOS_CHAR id)
{
  PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "received unexpected reset ack\r\n");
}

void
fsm_Reopen(struct fsm *fp)
{
  if (fp->state == ST_OPENED) {
    (*fp->fn->LayerDown)(fp);
    FsmInitRestartCounter(fp, FSM_REQ_TIMER);
    FsmSendConfigReq(fp);
    NewState(fp, ST_REQSENT);
    (*fp->parent->LayerDown)(fp->parent->object, fp);
  }
}

void
fsm2initial(struct fsm *fp)
{/*
  timer_Stop(&fp->FsmTimer);
  timer_Stop(&fp->OpenTimer);
  timer_Stop(&fp->StoppedTimer);*/
  if (fp->state == ST_STOPPED)
    fsm_Close(fp);
  if (fp->state > ST_INITIAL)
    fsm_Down(fp);
  if (fp->state > ST_INITIAL)
    fsm_Close(fp);
}

struct fsm_opt *
fsm_readopt(VOS_CHAR **cp)
{
  struct fsm_opt *o = (struct fsm_opt *)*cp;

  if (o->hdr.len < sizeof(struct fsm_opt_hdr)) {
    PPP_MNTN_LOG1(PS_PID_APP_PPP, 0, PS_PRINT_WARNING, "Bad option length", o->hdr.len);
    return VOS_NULL_PTR;
  }

  *cp += o->hdr.len;

  if (o->hdr.len > sizeof(struct fsm_opt)) {
     PPP_MNTN_LOG2(PS_PID_APP_PPP, 0, LOG_LEVEL_WARNING,
                   "Warning: Truncating option length from %d to %d:\r\n",
                    o->hdr.len, (VOS_INT32)sizeof(struct fsm_opt));
    o->hdr.len = sizeof(struct fsm_opt);
  }

  return o;
}

VOS_INT32
fsm_opt(VOS_CHAR *opt, VOS_INT32 optlen, const struct fsm_opt *o)
{
  VOS_INT32 cplen = o->hdr.len;

  if (optlen < sizeof(struct fsm_opt_hdr))
    optlen = 0;

  if (cplen > optlen)
  {
    PPP_MNTN_LOG2(PS_PID_APP_PPP, 0, LOG_LEVEL_WARNING,
                  "Can't REJ length %d - trunating to %d:\r\n",
                  cplen, optlen);
    cplen = optlen;
  }
  PS_MEM_CPY(opt, o, cplen);
  if (cplen)
    opt[1] = (VOS_CHAR)cplen;

  return cplen;
}

void
fsm_rej(struct fsm_decode *dec, const struct fsm_opt *o)
{
  if (!dec)
    return;
  dec->rejend += fsm_opt(dec->rejend, FSM_OPTLEN - (dec->rejend - dec->rej), o);
}

void
fsm_ack(struct fsm_decode *dec, const struct fsm_opt *o)
{
  if (!dec)
    return;
  dec->ackend += fsm_opt(dec->ackend, FSM_OPTLEN - (dec->ackend - dec->ack), o);
}

void
fsm_nak(struct fsm_decode *dec, const struct fsm_opt *o)
{
  if (!dec)
    return;
  dec->nakend += fsm_opt(dec->nakend, FSM_OPTLEN - (dec->nakend - dec->nak), o);
}

void
fsm_opt_normalise(struct fsm_decode *dec)
{
  if (dec->rejend != dec->rej) {
    /* rejects are preferred */
    dec->ackend = dec->ack;
    dec->nakend = dec->nak;
  } else if (dec->nakend != dec->nak)
    /* then NAKs */
    dec->ackend = dec->ack;
}

#endif /* #if(FEATURE_ON == FEATURE_PPP) */

