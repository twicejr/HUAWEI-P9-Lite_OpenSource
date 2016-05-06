


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
#include "PPP/Inc/pppid.h"
#include "PPP/Inc/link.h"
#include "PPP/Inc/pap.h"

#if(FEATURE_ON == FEATURE_PPP)

static const VOS_CHAR * const papcodes[] = {
  "\?\?\?", "REQUEST", "SUCCESS", "FAILURE"
};
#define MAXPAPCODE (sizeof papcodes / sizeof papcodes[0] - 1)


#if 0/*fanzhibin f49086 delete it*/
static void
pap_Req(struct authinfo *authp)
{
  struct bundle *bundle = authp->physical->dl->bundle;
  struct fsmheader lh;
  struct ppp_mbuf *bp;
  VOS_CHAR *cp;
  VOS_INT32 namelen, keylen, plen;

  namelen = strlen(bundle->cfg.auth.name);
  keylen = strlen(bundle->cfg.auth.key);
  plen = namelen + keylen + 2;
  TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "pap_Req: namelen = %d, keylen = %d\n", namelen, keylen);
  log_Printf(LogPHASE, "Pap Output: %s ********\n", bundle->cfg.auth.name);
  if (*bundle->cfg.auth.name == '\0')
    log_Printf(LogWARN, "Sending empty PAP authname!\n");
  lh.code = PAP_REQUEST;
  lh.id = authp->id;
  lh.length = htons(plen + sizeof(struct fsmheader));
  bp = ppp_m_get(plen + sizeof(struct fsmheader));
  PS_MEM_CPY(PPP_MBUF_CTOP(bp), &lh, sizeof(struct fsmheader));
  cp = PPP_MBUF_CTOP(bp) + sizeof(struct fsmheader);
  *cp++ = namelen;
  PS_MEM_CPY(cp, bundle->cfg.auth.name, namelen);
  cp += namelen;
  *cp++ = keylen;
  PS_MEM_CPY(cp, bundle->cfg.auth.key, keylen);
  link_PushPacket(&authp->physical->link, bp,/* bundle,*/
                  LINK_QUEUES(&authp->physical->link) - 1, PROTO_PAP);
}
#endif

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_PAP_C


void
SendPapCode(struct link *l, VOS_CHAR code, VOS_CHAR *message)
{
  struct fsmheader lh;
  struct ppp_mbuf *bp;
  VOS_CHAR *cp;
  VOS_UINT32 plen, mlen;


  lh.code = code;
  lh.id = l->pap.auth.id;
  mlen = VOS_StrNLen(message,20);
  plen = mlen + 1;
  lh.length = (VOS_UINT16)VOS_HTONS(plen + sizeof(struct fsmheader));
  bp = ppp_m_get(plen + PPP_RECIEVE_RESERVE_FOR_HEAD + PPP_RECIEVE_RESERVE_FOR_TAIL + sizeof(struct fsmheader));

  if(bp == VOS_NULL)
  {
        PPP_MNTN_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_WARNING, "no mbuf");
    return;
  }
    /*预留头部*/
    bp->m_offset = PPP_RECIEVE_RESERVE_FOR_HEAD;

    /*头部与尾部都留出来了*/
    bp->m_len = plen + sizeof(struct fsmheader);

  PS_MEM_CPY(PPP_MBUF_CTOP(bp), &lh, sizeof(struct fsmheader));
  cp = PPP_MBUF_CTOP(bp) + sizeof(struct fsmheader);
  /*
   * If our message is longer than 255 bytes, truncate the length to
   * 255 and send the entire message anyway.  Maybe the other end will
   * display it... (see pap_Input() !)
   */
  *cp++ = (VOS_CHAR)(mlen > 255 ? 255 : mlen);
  PS_MEM_CPY(cp, message, mlen);
  PPP_MNTN_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "Pap Output\r\n");

  link_PushPacket(l, bp,/* authp->physical->dl->bundle,*/
                  LINK_QUEUES(l) - 1, PROTO_PAP);
}

void
pap_Success(struct link *l)
{
#if 0/*fanzhibin f49086 delete it*/
  struct bundle *bundle = authp->physical->dl->bundle;

  datalink_GotAuthname(authp->physical->dl, authp->in.name);
#ifndef NORADIUS
  if (*bundle->radius.cfg.file && bundle->radius.repstr)
    SendPapCode(authp, PAP_ACK, bundle->radius.repstr);
  else
#endif
#endif
    SendPapCode(l, PAP_ACK, "Greetings!!");
#if 0/*fanzhibin f49086 delete it*/
/*下面这句在改造的时候要添进去*/
  authp->physical->link.lcp.auth_ineed = 0;
  if (Enabled(bundle, OPT_UTMP))
    physical_Login(authp->physical, authp->in.name);
/*下面这句在改造的时候要添进去*/
  if (authp->physical->link.lcp.auth_iwait == 0)
    /*
     * Either I didn't need to authenticate, or I've already been
     * told that I got the answer right.
     */
    datalink_AuthOk(authp->physical->dl);
  #endif
  l->lcp.auth_ineed = 0;
  if(l->lcp.auth_iwait == 0)    /* auth_iwait: 0, authentication to peer is not complete or no need to authentication,
                                              !0, authentication to peer is complete */
    {
        if (PHASE_AUTHENTICATE == l->phase)
        {
          l->phase = PHASE_NETWORK;
          l->ipcp.fsm.state = ST_CLOSED;
          fsm_Open(&(l->ipcp.fsm));
          PPP_MNTN_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "goto ipcp stage!\r\n");
        }
    }


}

void
pap_Failure(struct link *l)
{
  SendPapCode(l, PAP_NAK, "Login incorrect");
/*  datalink_AuthNotOk(authp->physical->dl);*/
}

void
pap_Init(struct pap *pap/*, struct physical *p*/)
{
  auth_Init(&(pap->auth), /*p, */VOS_NULL_PTR,/*pap_Req,*/ pap_Success, pap_Failure);
  PS_MEM_SET(&(pap->RecordData), '\0', sizeof(pap->RecordData));
}

PPP_ZC_STRU *
pap_Input(/*struct bundle *bundle,*/ struct link *l, PPP_ZC_STRU *pstMem)
{
/*  struct physical *p = link2physical(l);*/
#if 0 /* delete for transplant */
  VOS_CHAR nlen, *key;
#endif

  struct authinfo *authp =/* &p->dl*/&(l->pap.auth);
  VOS_CHAR nlen;
  VOS_UINT8 klen;
  const VOS_CHAR *txt;
  VOS_INT32 txtlen;
  struct ppp_mbuf *bp;


  bp = ppp_m_get_from_ttfmem(pstMem);
  PPP_MemFree(pstMem);

  if (VOS_NULL_PTR == bp)
  {
    return VOS_NULL_PTR;
  }

  if (l == VOS_NULL_PTR) {
    PPP_MNTN_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_WARNING, "pap input, Not a physical link - dropped\r\n");
    ppp_m_freem(bp);
    return VOS_NULL_PTR;
  }

  if (/*bundle_Phase(bundle)*/ l->phase!= PHASE_NETWORK &&
      /*bundle_Phase(bundle)*/ l->phase!= PHASE_AUTHENTICATE) {
    PPP_MNTN_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "Unexpected pap input - dropped\r\n");
    ppp_m_freem(bp);
    return VOS_NULL_PTR;
  }

  if ((bp = auth_ReadHeader(authp, bp)) == VOS_NULL_PTR &&
      VOS_NTOHS(authp->in.hdr.length) == 0) {
    PPP_MNTN_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_WARNING, "Pap Input: Truncated header\r\n");
    return VOS_NULL_PTR;
  }

  if (authp->in.hdr.code == 0 || authp->in.hdr.code > MAXPAPCODE) {
    PPP_MNTN_LOG1(PS_PID_APP_PPP, DIAG_MODE_COMM, LOG_LEVEL_WARNING,
                  "Bad PAP code: %d", authp->in.hdr.code);
    ppp_m_freem(bp);
    return VOS_NULL_PTR;
  }

  if (authp->in.hdr.code != PAP_REQUEST && authp->id != authp->in.hdr.id)
    {
    /* Wrong conversation dude ! */
    PPP_MNTN_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_WARNING, "pap input, dropped (got id not equal to previous id)\r\n");
    ppp_m_freem(bp);
    return VOS_NULL_PTR;
    }
  authp->id = authp->in.hdr.id;        /* We respond with this id */

  if (authp->in.hdr.code == PAP_REQUEST)
  {
    /*将config req报文头部拷贝到缓存中*/
    PS_MEM_CPY(l->pap.RecordData.BufRequest,&(authp->in.hdr),sizeof(authp->in.hdr));

    ppp_mbuf_View(bp,(l->pap.RecordData.BufRequest + sizeof(authp->in.hdr)),
                    VOS_NTOHS(authp->in.hdr.length) - sizeof(authp->in.hdr));
    l->pap.RecordData.LenOfRequest = VOS_NTOHS(authp->in.hdr.length);

  }



  if (bp) {
    bp = ppp_mbuf_Read(bp, &nlen, 1);
    if (authp->in.hdr.code == PAP_ACK) {
      /*
       * Don't restrict the length of our acknowledgement freetext to
       * nlen (a one-byte length).  Show the rest of the ack packet
       * instead.  This isn't really part of the protocol.....
       */
      bp = ppp_m_pullup(bp);
      txt = PPP_MBUF_CTOP(bp);
      txtlen = ppp_m_length(bp);
    } else {
      bp = auth_ReadName(authp, bp, nlen);
      txt = authp->in.name;
      txtlen = VOS_StrNLen(authp->in.name,AUTHLEN);
      PPP_MNTN_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "username:");
      PPP_MNTN_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, authp->in.name);
    }
  } else {
    txt = "";
    txtlen = 0;
  }

  PPP_MNTN_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "\r\nPap Input\r\n");

  switch (authp->in.hdr.code) {
    case PAP_REQUEST:
      if (bp == VOS_NULL_PTR) {
        PPP_MNTN_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "Pap Input: No key given !\r\n");
        break;
      }
      bp = ppp_mbuf_Read(bp, &klen, 1);
      if (ppp_m_length(bp) < klen) {
        PPP_MNTN_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_WARNING, "Pap Input: Truncated key !\r\n");
        break;
      }

#if 0/*fanzhibin f49086 delete it*/
      if ((key = VOS_MemAlloc(PS_PID_APP_PPP, DYNAMIC_DOPRA_MEM_PT,klen+1)) == VOS_NULL_PTR) {
        TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_ERROR, "Pap Input: Out of memory !\n");
        break;
      }
      bp = ppp_mbuf_Read(bp, key, klen);
      key[klen] = '\0';


#ifndef NORADIUS
      if (*bundle->radius.cfg.file) {
        if (!radius_Authenticate(&bundle->radius, authp, authp->in.name,
                                 key, strlen(key), VOS_NULL_PTR, 0))
          pap_Failure(authp);
      } else
#endif
/*下面这句在改造的时候要添进去*/
      if (auth_Validate(bundle, authp->in.name, key, p))
        pap_Success(authp);
      else
        pap_Failure(authp);

      VOS_MemFree(PS_PID_APP_PPP,key);
#endif

      if (klen > sizeof l->pap.RecordData.password- 1)
      {
        PPP_MNTN_LOG1(PS_PID_APP_PPP, DIAG_MODE_COMM, LOG_LEVEL_WARNING,
                      "auth_ReadPassword: PassWord too long,len= %d", klen);
      }
      else {
        if (klen > ppp_m_length(bp))
        {
          PPP_MNTN_LOG1(PS_PID_APP_PPP, DIAG_MODE_COMM, LOG_LEVEL_WARNING,
                        "auth_ReadPassword: Short packet, pass_len = %d", klen);
        }
        else {
          bp = ppp_mbuf_Read(bp, l->pap.RecordData.password, klen);
          l->pap.RecordData.password[klen] = '\0';
          PPP_MNTN_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "password:");
          PPP_MNTN_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, l->pap.RecordData.password);

        }
      }

      pap_Success(l);

      break;

    case PAP_ACK:
#if 0/*fanzhibin f49086 delete it*/
      auth_StopTimer(authp);
      if (p->link.lcp.auth_iwait == PROTO_PAP) {
        p->link.lcp.auth_iwait = 0;
        if (p->link.lcp.auth_ineed == 0)
          /*
           * We've succeeded in our ``login''
           * If we're not expecting  the peer to authenticate (or he already
           * has), proceed to network phase.
           */
          datalink_AuthOk(p->dl);
      }
#endif
      break;

    case PAP_NAK:

#if 0/*fanzhibin f49086 delete it*/
      auth_StopTimer(authp);
      datalink_AuthNotOk(p->dl);
#endif

      break;
  }

  ppp_m_freem(bp);
  return VOS_NULL_PTR;
}

#endif /* #if(FEATURE_ON == FEATURE_PPP) */

