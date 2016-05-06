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
 * $FreeBSD: src/usr.sbin/ppp/ipcp.h,v 1.35 2001/08/14 16:05:51 brian Exp $
 */
#ifndef __PPP_IPCP_H__
#define __PPP_IPCP_H__

#include "PPP/Inc/ppp_fsm.h"
#include "PPP/Inc/ppp_public.h"
#include "PPP/Inc/throughput.h"


#pragma pack(4)
#define    IPCP_MAXCODE    CODE_CODEREJ

#define    TY_IPADDRS    1
#define    TY_COMPPROTO    2
#define    TY_IPADDR    3

/* Domain NameServer and NetBIOS NameServer options */

#define TY_PRIMARY_DNS        129
#define TY_PRIMARY_NBNS        130
#define TY_SECONDARY_DNS    131
#define TY_SECONDARY_NBNS    132
#define TY_ADJUST_NS        119 /* subtract from NS val for REJECT bit */

#define PPP_IPCP_PENDING_TIMER_LEN (1500)


enum
{
    IPCP_NOT_RECEIVE_REQ = 0,
    IPCP_REQ_RECEIVED,
    IPCP_SUCCESS_FROM_GGSN
};


struct ipcp {
  struct fsm fsm;            /* The finite state machine */

  struct {
#if 0 /*fanzhibin f49086 delete it*/
    struct {
      VOS_INT32 slots;            /* Maximum VJ slots */
      unsigned slotcomp : 1;        /* Slot compression */
      unsigned neg : 2;            /* VJ negotiation */
    } vj;

    struct ncprange  my_range;        /* MYADDR spec */
    struct ppp_in_addr   netmask;        /* Iface netmask (unused by most OSs) */
    struct ncprange  peer_range;    /* HISADDR spec */
    struct iplist    peer_list;        /* Ranges of HISADDR values */
#endif
    struct ppp_in_addr   TriggerAddress;    /* Address to suggest in REQ */
    unsigned HaveTriggerAddress : 1;    /* Trigger address specified */

    struct {
      struct ppp_in_addr dns[2];        /* DNS addresses offered */
      unsigned dns_neg : 2;        /* dns negotiation */
      struct ppp_in_addr nbns[2];        /* NetBIOS NS addresses offered */
    } ns;

    struct fsm_retry fsm;        /* frequency to resend requests */
  } cfg;
#if 0 /*fanzhibin f49086 delete it*/
  struct {
    struct slcompress cslc;        /* VJ state */
    struct slstat slstat;        /* VJ statistics */
  } vj;
#endif

  struct {
#if 0 /*fanzhibin f49086 delete it*/
    unsigned resolver : 1;        /* Found resolv.conf ? */
    unsigned writable : 1;        /* Can write resolv.conf ? */
#endif
    struct ppp_in_addr dns[2];        /* Current DNS addresses */
#if 0 /*fanzhibin f49086 delete it*/
    VOS_CHAR *resolv;            /* Contents of resolv.conf */
    VOS_CHAR *resolv_nons;            /* Contents of resolv.conf without ns */
#endif
    } ns;

    /*为了与网络侧之间的交互，特定义该结构*/
    VOS_UINT32 stage;

    VOS_UINT32 IpAddr_neg : 2;

    VOS_UINT32 PriDns_neg : 2;
    VOS_UINT32 SecDns_neg : 2;

    VOS_UINT32 PriNbns_neg : 2;
    VOS_UINT32 SecNbns_neg : 2;

    VOS_UINT32 IpAddrs_neg : 2;
    VOS_UINT32 CompressProto_neg : 2;

    struct ppp_in_addr   PriDnsAddr;
    struct ppp_in_addr   SecDnsAddr;

    struct ppp_in_addr   PriNbnsAddr;
    struct ppp_in_addr   SecNbnsAddr;

    VOS_UINT16 ComressProtoLen;
    VOS_CHAR CompressProto[10];




  unsigned heis1172 : 1;        /* True if he is speaking rfc1172 */

  unsigned peer_req : 1;        /* Any TY_IPADDR REQs from the peer ? */
  struct ppp_in_addr peer_ip;        /* IP address he's willing to use */
  VOS_UINT32 peer_compproto;        /* VJ params he's willing to use */

  struct ppp_in_addr ifmask;        /* Interface netmask */

  struct ppp_in_addr my_ip;            /* IP address I'm willing to use */
  VOS_UINT32 my_compproto;        /* VJ params I'm willing to use */

  VOS_UINT32 peer_reject;        /* Request codes rejected by peer */
  VOS_UINT32 my_reject;            /* Request codes I have rejected */

  struct pppThroughput throughput;    /* throughput statistics */
  struct ppp_mqueue Queue[3];        /* Output packet queues */

  HTIMER				hIpcpPendTimer;		/*等待PDP激活阶段,处理IPCP帧的定时器*/
  struct ppp_mbuf 	     *pstIpcpPendFrame;          /*等待PDP激活阶段,待处理IPCP帧*/

};


#define fsm2ipcp(fp) (fp->proto == PROTO_IPCP ? (struct ipcp *)fp : VOS_NULL_PTR)
#define IPCP_QUEUES(ipcp) (sizeof ipcp->Queue / sizeof ipcp->Queue[0])
#if 0 /*fanzhibin f49086 delete it*/
struct bundle;
#endif

#if 0 /*fanzhibin f49086 delete it*/
struct cmdargs;
struct iface_addr;
#endif
extern void ipcp_Init(struct ipcp *,/* struct bundle *, */struct link *,
                      const struct fsm_parent *);
extern void ipcp_Destroy(struct ipcp *);
extern void ipcp_Setup(struct ipcp *, VOS_UINT32);
extern void ipcp_SetLink(struct ipcp *, struct link *);

extern VOS_UINT32 DecodeAtIndication(struct ipcp* pIpcp,VOS_CHAR* pEchoBuffer,VOS_UINT16 BufferLen);

extern VOS_INT32  ipcp_Show(struct ipcp * /*struct cmdargs const **/);
extern PPP_ZC_STRU *ipcp_Input(/*struct bundle *, */struct link *, PPP_ZC_STRU *);
extern void ipcp_AddInOctets(struct ipcp *, VOS_INT32);
extern void ipcp_AddOutOctets(struct ipcp *, VOS_INT32);
#if 0 /*fanzhibin f49086 delete it*/
extern VOS_INT32  ipcp_UseHisIPaddr(struct bundle *, struct ppp_in_addr);
extern VOS_INT32  ipcp_UseHisaddr(struct bundle *, const VOS_CHAR *, VOS_INT32);
extern VOS_INT32  ipcp_vjset(struct cmdargs const *);
extern void ipcp_IfaceAddrAdded(struct ipcp *, const struct iface_addr *);
extern void ipcp_IfaceAddrDeleted(struct ipcp *, const struct iface_addr *);
extern VOS_INT32  ipcp_InterfaceUp(struct ipcp *);
extern struct ppp_in_addr addr2mask(struct ppp_in_addr);
extern VOS_INT32 ipcp_WriteDNS(struct ipcp *);
extern void ipcp_RestoreDNS(struct ipcp *);
extern void ipcp_LoadDNS(struct ipcp *);
#endif
extern VOS_UINT32 ipcp_QueueLen(struct ipcp *);
extern VOS_INT32 ipcp_PushPacket(struct ipcp *, struct link *);

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#endif /* end of ipcp.h */
