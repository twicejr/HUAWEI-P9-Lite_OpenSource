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
 * $FreeBSD: src/usr.sbin/ppp/ipcp.c,v 1.119 2003/06/19 18:55:49 ume Exp $
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
#include "PPP/Inc/pppid.h"
#include "PPP/Inc/link.h"
#include "PPP/Inc/ppp_input.h"
#include "TafNvInterface.h"

#undef REJECTED

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_IPCP_C

#if(FEATURE_ON == FEATURE_PPP)

#define    REJECTED(p, x)    ((p)->peer_reject & (1<<(x)))
#define issep(ch) ((ch) == ' ' || (ch) == '\t')
#define isip(ch) (((ch) >= '0' && (ch) <= '9') || (ch) == '.')

extern VOS_UINT8  g_ucPppConfigWins;

struct compreq {
  VOS_UINT16 proto;
  VOS_CHAR slots;
  VOS_CHAR compcid;
};

VOS_INT32 IpcpLayerUp(struct fsm *);
void IpcpLayerDown(struct fsm *);
void IpcpLayerStart(struct fsm *);
void IpcpLayerFinish(struct fsm *);
void IpcpInitRestartCounter(struct fsm *, VOS_INT32);
void IpcpSendConfigReq(struct fsm *);
void IpcpSentTerminateReq(struct fsm *);
void IpcpSendTerminateAck(struct fsm *, VOS_CHAR);
void IpcpDecodeConfig(struct fsm *, VOS_CHAR *, VOS_CHAR *, VOS_INT32,
                             struct fsm_decode *);

static struct fsm_callbacks ipcp_Callbacks = {
  IpcpLayerUp,
  IpcpLayerDown,
  IpcpLayerStart,
  IpcpLayerFinish,
  IpcpInitRestartCounter,
  IpcpSendConfigReq,
  IpcpSentTerminateReq,
  IpcpSendTerminateAck,
  IpcpDecodeConfig,
  fsm_NullRecvResetReq,
  fsm_NullRecvResetAck
};

const VOS_CHAR *
protoname(VOS_INT32 proto)
{
  static struct {
    VOS_INT32 id;
    const VOS_CHAR *txt;
  } cftypes[] = {
    /* Check out the latest ``Assigned numbers'' rfc (rfc1700.txt) */
    { 1, "IPADDRS" },        /* IP-Addresses */    /* deprecated */
    { 2, "COMPPROTO" },        /* IP-Compression-Protocol */
    { 3, "IPADDR" },        /* IP-Address */
    { 129, "PRIDNS" },        /* 129: Primary DNS Server Address */
    { 130, "PRINBNS" },        /* 130: Primary NBNS Server Address */
    { 131, "SECDNS" },        /* 131: Secondary DNS Server Address */
    { 132, "SECNBNS" }        /* 132: Secondary NBNS Server Address */
  };
  VOS_INT32 f;

  for (f = 0; f < sizeof cftypes / sizeof *cftypes; f++)
    if (cftypes[f].id == proto)
      return cftypes[f].txt;
#if 0 /*fanzhibin f49086 delete it*/
  return NumStr(proto, VOS_NULL_PTR, 0);
#endif
  return "unknow protocol";
}

void
ipcp_AddInOctets(struct ipcp *ipcp, VOS_INT32 n)
{
  throughput_addin(&ipcp->throughput, n);
}

void
ipcp_AddOutOctets(struct ipcp *ipcp, VOS_INT32 n)
{
  throughput_addout(&ipcp->throughput, n);
}
#if 0 /*fanzhibin f49086 delete it*/
void
ipcp_LoadDNS(struct ipcp *ipcp)
{
  VOS_INT32 fd;

  ipcp->ns.dns[0].s_addr = ipcp->ns.dns[1].s_addr = INADDR_NONE;

  if (ipcp->ns.resolv != VOS_NULL_PTR) {
    free(ipcp->ns.resolv);
    ipcp->ns.resolv = VOS_NULL_PTR;
  }
  if (ipcp->ns.resolv_nons != VOS_NULL_PTR) {
    free(ipcp->ns.resolv_nons);
    ipcp->ns.resolv_nons = VOS_NULL_PTR;
  }
  ipcp->ns.resolver = 0;

  if ((fd = open(_PATH_RESCONF, O_RDONLY)) != -1) {
    struct stat st;

    if (fstat(fd, &st) == 0) {
      ssize_t got;

      if ((ipcp->ns.resolv_nons = (VOS_CHAR *)malloc(st.st_size + 1)) == VOS_NULL_PTR)
        log_Printf(LogERROR, "Failed to malloc %lu for %s: %s\n",
                   (unsigned long)st.st_size, _PATH_RESCONF, strerror(errno));
      else if ((ipcp->ns.resolv = (VOS_CHAR *)malloc(st.st_size + 1)) == VOS_NULL_PTR) {
        log_Printf(LogERROR, "Failed(2) to malloc %lu for %s: %s\n",
                   (unsigned long)st.st_size, _PATH_RESCONF, strerror(errno));
        free(ipcp->ns.resolv_nons);
        ipcp->ns.resolv_nons = VOS_NULL_PTR;
      } else if ((got = read(fd, ipcp->ns.resolv, st.st_size)) != st.st_size) {
        if (got == -1)
          log_Printf(LogERROR, "Failed to read %s: %s\n",
                     _PATH_RESCONF, strerror(errno));
        else
          log_Printf(LogERROR, "Failed to read %s, got %lu not %lu\n",
                     _PATH_RESCONF, (unsigned long)got,
                     (unsigned long)st.st_size);
        free(ipcp->ns.resolv_nons);
        ipcp->ns.resolv_nons = VOS_NULL_PTR;
        free(ipcp->ns.resolv);
        ipcp->ns.resolv = VOS_NULL_PTR;
      } else {
        VOS_CHAR *cp, *cp_nons, *ncp, ch;
        VOS_INT32 n;

        ipcp->ns.resolv[st.st_size] = '\0';
        ipcp->ns.resolver = 1;

        cp_nons = ipcp->ns.resolv_nons;
        cp = ipcp->ns.resolv;
        n = 0;

        while ((ncp = strstr(cp, "nameserver")) != VOS_NULL_PTR) {
          if (ncp != cp) {
            PS_MEM_CPY(cp_nons, cp, ncp - cp);
            cp_nons += ncp - cp;
          }
          if ((ncp != cp && ncp[-1] != '\n') || !issep(ncp[10])) {
            PS_MEM_CPY(cp_nons, ncp, 9);
            cp_nons += 9;
            cp = ncp + 9;    /* Can't match "nameserver" at cp... */
            continue;
          }

          for (cp = ncp + 11; issep(*cp); cp++)    /* Skip whitespace */
            ;

          for (ncp = cp; isip(*ncp); ncp++)        /* Jump over IP */
            ;

          ch = *ncp;
          *ncp = '\0';
          if (n < 2 && inet_aton(cp, ipcp->ns.dns))
            n++;
          *ncp = ch;

          if ((cp = strchr(ncp, '\n')) == VOS_NULL_PTR)    /* Point at next line */
            cp = ncp + strlen(ncp);
          else
            cp++;
        }
        strcpy(cp_nons, cp);    /* Copy the end - including the NUL */
        cp_nons += strlen(cp_nons) - 1;
        while (cp_nons >= ipcp->ns.resolv_nons && *cp_nons == '\n')
          *cp_nons-- = '\0';
        if (n == 2 && ipcp->ns.dns[0].s_addr == INADDR_ANY) {
          ipcp->ns.dns[0].s_addr = ipcp->ns.dns[1].s_addr;
          ipcp->ns.dns[1].s_addr = INADDR_ANY;
        }
        bundle_AdjustDNS(ipcp->fsm.bundle);
      }
    } else
      log_Printf(LogERROR, "Failed to stat opened %s: %s\n",
                 _PATH_RESCONF, strerror(errno));

    close(fd);
  }
}

VOS_INT32
ipcp_WriteDNS(struct ipcp *ipcp)
{
  const VOS_CHAR *paddr;
  mode_t mask;
  FILE *fp;

  if (ipcp->ns.dns[0].s_addr == INADDR_ANY &&
      ipcp->ns.dns[1].s_addr == INADDR_ANY) {
    log_Printf(LogIPCP, "%s not modified: All nameservers NAKd\n",
              _PATH_RESCONF);
    return 0;
  }

  if (ipcp->ns.dns[0].s_addr == INADDR_ANY) {
    ipcp->ns.dns[0].s_addr = ipcp->ns.dns[1].s_addr;
    ipcp->ns.dns[1].s_addr = INADDR_ANY;
  }

  mask = umask(022);
  if ((fp = ID0fopen(_PATH_RESCONF, "w")) != VOS_NULL_PTR) {
    umask(mask);
    if (ipcp->ns.resolv_nons)
      fputs(ipcp->ns.resolv_nons, fp);
    paddr = inet_ntoa(ipcp->ns.dns[0]);
    log_Printf(LogIPCP, "Primary nameserver set to %s\n", paddr);
    fprintf(fp, "\nnameserver %s\n", paddr);
    if (ipcp->ns.dns[1].s_addr != INADDR_ANY &&
        ipcp->ns.dns[1].s_addr != INADDR_NONE &&
        ipcp->ns.dns[1].s_addr != ipcp->ns.dns[0].s_addr) {
      paddr = inet_ntoa(ipcp->ns.dns[1]);
      log_Printf(LogIPCP, "Secondary nameserver set to %s\n", paddr);
      fprintf(fp, "nameserver %s\n", paddr);
    }
    if (fclose(fp) == EOF) {
      log_Printf(LogERROR, "write(): Failed updating %s: %s\n", _PATH_RESCONF,
                 strerror(errno));
      return 0;
    }
  } else
    umask(mask);

  return 1;
}

void
ipcp_RestoreDNS(struct ipcp *ipcp)
{
  if (ipcp->ns.resolver) {
    ssize_t got;
    VOS_UINT32 len;
    VOS_INT32 fd;

    if ((fd = ID0open(_PATH_RESCONF, O_WRONLY|O_TRUNC, 0644)) != -1) {
      len = strlen(ipcp->ns.resolv);
      if ((got = write(fd, ipcp->ns.resolv, len)) != len) {
        if (got == -1)
          log_Printf(LogERROR, "Failed rewriting %s: write: %s\n",
                     _PATH_RESCONF, strerror(errno));
        else
          log_Printf(LogERROR, "Failed rewriting %s: wrote %lu of %lu\n",
                     _PATH_RESCONF, (unsigned long)got, (unsigned long)len);
      }
      close(fd);
    } else
      log_Printf(LogERROR, "Failed rewriting %s: open: %s\n", _PATH_RESCONF,
                 strerror(errno));
  } else if (remove(_PATH_RESCONF) == -1)
    log_Printf(LogERROR, "Failed removing %s: %s\n", _PATH_RESCONF,
               strerror(errno));

}

VOS_INT32
ipcp_Show(struct ipcp *ipcp/*struct cmdargs const *arg*/)
{
/*  struct ipcp *ipcp = &arg->bundle->ncp.ipcp;*/

  TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "%s [%s]\n", ipcp->fsm.name,
                State2Nam(ipcp->fsm.state));
  if (ipcp->fsm.state == ST_OPENED) {
    TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, " His side:        %s, %s\n",
                  inet_ntoa(ipcp->peer_ip), vj2asc(ipcp->peer_compproto));
    TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, " My side:         %s, %s\n",
                  inet_ntoa(ipcp->my_ip), vj2asc(ipcp->my_compproto));
    TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, " Queued packets:  %lu\n",
                  (unsigned long)ipcp_QueueLen(ipcp));
  }

  TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "\nDefaults:\n");
  TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, " FSM retry = %us, max %u Config"
                " REQ%s, %u Term REQ%s\n", ipcp->cfg.fsm.timeout,
                ipcp->cfg.fsm.maxreq, ipcp->cfg.fsm.maxreq == 1 ? "" : "s",
                ipcp->cfg.fsm.maxtrm, ipcp->cfg.fsm.maxtrm == 1 ? "" : "s");
  TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, " My Address:      %s\n",
                ncprange_ntoa(&ipcp->cfg.my_range));
  if (ipcp->cfg.HaveTriggerAddress)
    TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, " Trigger address: %s\n",
                  inet_ntoa(ipcp->cfg.TriggerAddress));

  TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, " VJ compression:  %s (%d slots %s slot "
                "compression)\n", command_ShowNegval(ipcp->cfg.vj.neg),
                ipcp->cfg.vj.slots, ipcp->cfg.vj.slotcomp ? "with" : "without");

  if (iplist_isvalid(&ipcp->cfg.peer_list))
    TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, " His Address:     %s\n",
                  ipcp->cfg.peer_list.src);
  else
    TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, " His Address:     %s\n",
                  ncprange_ntoa(&ipcp->cfg.peer_range));

  TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, " DNS:             %s",
                ipcp->cfg.ns.dns[0].s_addr == INADDR_NONE ?
                "none" : inet_ntoa(ipcp->cfg.ns.dns[0]));
  if (ipcp->cfg.ns.dns[1].s_addr != INADDR_NONE)
    TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, ", %s",
                  inet_ntoa(ipcp->cfg.ns.dns[1]));
  TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, ", %s\n",
                command_ShowNegval(ipcp->cfg.ns.dns_neg));
  TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, " Resolver DNS:    %s",
                ipcp->ns.dns[0].s_addr == INADDR_NONE ?
                "none" : inet_ntoa(ipcp->ns.dns[0]));
  if (ipcp->ns.dns[1].s_addr != INADDR_NONE &&
      ipcp->ns.dns[1].s_addr != ipcp->ns.dns[0].s_addr)
    TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, ", %s",
                  inet_ntoa(ipcp->ns.dns[1]));
  TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "\n NetBIOS NS:      %s, ",
                inet_ntoa(ipcp->cfg.ns.nbns[0]));
  TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "%s\n\n",
                inet_ntoa(ipcp->cfg.ns.nbns[1]));

  throughput_disp(&ipcp->throughput, arg->prompt);

  return 0;
}

VOS_INT32
ipcp_vjset(struct cmdargs const *arg)
{
  if (arg->argc != arg->argn+2)
    return -1;
  if (!strcasecmp(arg->argv[arg->argn], "slots")) {
    VOS_INT32 slots;

    slots = atoi(arg->argv[arg->argn+1]);
    if (slots < 4 || slots > 16)
      return 1;
    arg->bundle->ncp.ipcp.cfg.vj.slots = slots;
    return 0;
  } else if (!strcasecmp(arg->argv[arg->argn], "slotcomp")) {
    if (!strcasecmp(arg->argv[arg->argn+1], "on"))
      arg->bundle->ncp.ipcp.cfg.vj.slotcomp = 1;
    else if (!strcasecmp(arg->argv[arg->argn+1], "off"))
      arg->bundle->ncp.ipcp.cfg.vj.slotcomp = 0;
    else
      return 2;
    return 0;
  }
  return -1;
}
#endif
void
ipcp_Init(struct ipcp *ipcp,/* struct bundle *bundle,*/ struct link *l,
          const struct fsm_parent *parent)
{
#if 0 /*fanzhibin f49086 delete it*/
  struct hostent *hp;
  struct ppp_in_addr host;
  VOS_CHAR name[MAXHOSTNAMELEN];
#endif
  static const VOS_CHAR * const timer_names[] =
    {"IPCP restart", "IPCP openmode", "IPCP stopped"};

  fsm_Init(&ipcp->fsm, "IPCP", PROTO_IPCP, 1, IPCP_MAXCODE, 5/*LogIPCP*/,
           /*bundle, */l, parent, &ipcp_Callbacks, timer_names);
#if 0 /*fanzhibin f49086 delete it*/
  ipcp->cfg.vj.slots = DEF_VJ_STATES;
  ipcp->cfg.vj.slotcomp = 1;
  PS_MEM_SET(&ipcp->cfg.my_range, '\0', sizeof ipcp->cfg.my_range);

  host.s_addr = htonl(INADDR_LOOPBACK);
  ipcp->cfg.netmask.s_addr = INADDR_ANY;
  if (gethostname(name, sizeof name) == 0) {
    hp = gethostbyname(name);
    if (hp && hp->h_addrtype == AF_INET && hp->h_length == sizeof host.s_addr)
      PS_MEM_CPY(&host.s_addr, hp->h_addr, sizeof host.s_addr);
  }
  ncprange_setip4(&ipcp->cfg.my_range, host, ipcp->cfg.netmask);
  ncprange_setip4(&ipcp->cfg.peer_range, ipcp->cfg.netmask, ipcp->cfg.netmask);

  iplist_setsrc(&ipcp->cfg.peer_list, "");
#endif

  ipcp->cfg.HaveTriggerAddress = 0;
  ipcp->cfg.ns.dns[0].s_addr = INADDR_NONE;
  ipcp->cfg.ns.dns[1].s_addr = INADDR_NONE;
  ipcp->cfg.ns.dns_neg = 0;
  ipcp->cfg.ns.nbns[0].s_addr = INADDR_ANY;
  ipcp->cfg.ns.nbns[1].s_addr = INADDR_ANY;

  ipcp->cfg.fsm.timeout = DEF_FSMRETRY;
  ipcp->cfg.fsm.maxreq = DEF_FSMTRIES;
  ipcp->cfg.fsm.maxtrm = DEF_FSMTRIES;

  ipcp->hIpcpPendTimer = VOS_NULL_PTR;
  ipcp->pstIpcpPendFrame = VOS_NULL_PTR;

#if 0 /*fanzhibin f49086 delete it*/
  ipcp->cfg.vj.neg = NEG_ENABLED|NEG_ACCEPTED;
  PS_MEM_SET(&ipcp->vj, '\0', sizeof ipcp->vj);

  ipcp->ns.resolv = VOS_NULL_PTR;
  ipcp->ns.resolv_nons = VOS_NULL_PTR;
  ipcp->ns.writable = 1;
  ipcp_LoadDNS(ipcp);
#endif

  throughput_init(&ipcp->throughput, SAMPLE_PERIOD);
  PS_MEM_SET(ipcp->Queue, '\0', sizeof ipcp->Queue);
  ipcp_Setup(ipcp, INADDR_NONE);
}

void
ipcp_Destroy(struct ipcp *ipcp)
{
  throughput_destroy(&ipcp->throughput);
#if 0 /*fanzhibin f49086 delete it*/
  if (ipcp->ns.resolv != VOS_NULL_PTR) {
    free(ipcp->ns.resolv);
    ipcp->ns.resolv = VOS_NULL_PTR;
  }
  if (ipcp->ns.resolv_nons != VOS_NULL_PTR) {
    free(ipcp->ns.resolv_nons);
    ipcp->ns.resolv_nons = VOS_NULL_PTR;
  }
#endif
}

void
ipcp_SetLink(struct ipcp *ipcp, struct link *l)
{
  ipcp->fsm.link = l;
}

void
ipcp_Setup(struct ipcp *ipcp, VOS_UINT32 mask)
{
#if 0 /*fanzhibin f49086 delete it*/
  struct iface *iface = ipcp->fsm.bundle->iface;
  struct ncpaddr ipaddr;
  struct ppp_in_addr peer;
  VOS_INT32 pos, n;
#endif


  ipcp->fsm.open_mode = 0;

  ipcp->stage = IPCP_NOT_RECEIVE_REQ;
  ipcp->IpAddr_neg = 0;

  ipcp->PriDns_neg = 0;
  ipcp->SecDns_neg = 0;

  ipcp->PriNbns_neg = 0;
  ipcp->SecNbns_neg = 0;
  ipcp->IpAddrs_neg = 0;
  ipcp->CompressProto_neg = 0;



#if 0 /*fanzhibin f49086 delete it*/
  ipcp->ifmask.s_addr = mask == INADDR_NONE ? ipcp->cfg.netmask.s_addr : mask;

  if (iplist_isvalid(&ipcp->cfg.peer_list)) {
    /* Try to give the peer a previously configured IP address */
    for (n = 0; n < iface->addrs; n++) {
      if (!ncpaddr_getip4(&iface->addr[n].peer, &peer))
        continue;
      if ((pos = iplist_ip2pos(&ipcp->cfg.peer_list, peer)) != -1) {
        ncpaddr_setip4(&ipaddr, iplist_setcurpos(&ipcp->cfg.peer_list, pos));
        break;
      }
    }
    if (n == iface->addrs)
      /* Ok, so none of 'em fit.... pick a random one */
      ncpaddr_setip4(&ipaddr, iplist_setrandpos(&ipcp->cfg.peer_list));

    ncprange_sethost(&ipcp->cfg.peer_range, &ipaddr);
  }
#endif
  ipcp->heis1172 = 0;
  ipcp->peer_req = 0;
#if 0 /*fanzhibin f49086 delete it*/
  ncprange_getip4addr(&ipcp->cfg.peer_range, &ipcp->peer_ip);
#endif
  ipcp->peer_compproto = 0;
#if 0 /*fanzhibin f49086 delete it*/
  if (ipcp->cfg.HaveTriggerAddress) {
    /*
     * Some implementations of PPP require that we send a
     * *special* value as our address, even though the rfc specifies
     * full negotiation (e.g. "0.0.0.0" or Not "0.0.0.0").
     */
    ipcp->my_ip = ipcp->cfg.TriggerAddress;
    log_Printf(LogIPCP, "Using trigger address %s\n",
              inet_ntoa(ipcp->cfg.TriggerAddress));
  } else {
    /*
     * Otherwise, if we've used an IP number before and it's still within
     * the network specified on the ``set ifaddr'' line, we really
     * want to keep that IP number so that we can keep any existing
     * connections that are bound to that IP.
     */
    for (n = 0; n < iface->addrs; n++) {
      ncprange_getaddr(&iface->addr[n].ifa, &ipaddr);
      if (ncprange_contains(&ipcp->cfg.my_range, &ipaddr)) {
        ncpaddr_getip4(&ipaddr, &ipcp->my_ip);
        break;
      }
    }
    if (n == iface->addrs)
      ncprange_getip4addr(&ipcp->cfg.my_range, &ipcp->my_ip);
  }
#endif

#if 0 /*fanzhibin f49086 delete it*/
  if (IsEnabled(ipcp->cfg.vj.neg)
#ifndef NORADIUS
      || (ipcp->fsm.bundle->radius.valid && ipcp->fsm.bundle->radius.vj)
#endif
     )
    ipcp->my_compproto = (PROTO_VJCOMP << 16) +
                         ((ipcp->cfg.vj.slots - 1) << 8) +
                         ipcp->cfg.vj.slotcomp;
  else
    ipcp->my_compproto = 0;
  sl_compress_init(&ipcp->vj.cslc, ipcp->cfg.vj.slots - 1);
#endif
  ipcp->peer_reject = 0;
  ipcp->my_reject = 0;

  /* Copy startup values into ipcp->ns.dns */
  if (ipcp->cfg.ns.dns[0].s_addr != INADDR_NONE)
    PS_MEM_CPY(ipcp->ns.dns, ipcp->cfg.ns.dns, sizeof ipcp->ns.dns);
}
#if 0 /*fanzhibin f49086 delete it*/
static VOS_INT32
numaddresses(struct ppp_in_addr mask)
{
  VOS_UINT32 bit, haddr;
  VOS_INT32 n;

  haddr = ntohl(mask.s_addr);
  bit = 1;
  n = 1;

  do {
    if (!(haddr & bit))
      n <<= 1;
  } while (bit <<= 1);

  return n;
}

static VOS_INT32
ipcp_proxyarp(struct ipcp *ipcp,
              VOS_INT32 (*proxyfun)(struct bundle *, struct ppp_in_addr, VOS_INT32),
              const struct iface_addr *addr)
{
  struct bundle *bundle = ipcp->fsm.bundle;
  struct ppp_in_addr peer, mask, ip;
  VOS_INT32 n, ret, s;

  if (!ncpaddr_getip4(&addr->peer, &peer)) {
    log_Printf(LogERROR, "Oops, ipcp_proxyarp() called with unexpected addr\n");
    return 0;
  }

  if ((s = ID0socket(PF_INET, SOCK_DGRAM, 0)) == -1) {
    log_Printf(LogERROR, "ipcp_proxyarp: socket: %s\n",
               strerror(errno));
    return 0;
  }

  ret = 0;

  if (Enabled(bundle, OPT_PROXYALL)) {
    ncprange_getip4mask(&addr->ifa, &mask);
    if ((n = numaddresses(mask)) > 256) {
      log_Printf(LogWARN, "%s: Too many addresses for proxyall\n",
                 ncprange_ntoa(&addr->ifa));
      return 0;
    }
    ip.s_addr = peer.s_addr & mask.s_addr;
    if (n >= 4) {
      ip.s_addr = htonl(ntohl(ip.s_addr) + 1);
      n -= 2;
    }
    while (n) {
      if (!((ip.s_addr ^ peer.s_addr) & mask.s_addr)) {
        if (!(ret = (*proxyfun)(bundle, ip, s)))
          break;
        n--;
      }
      ip.s_addr = htonl(ntohl(ip.s_addr) + 1);
    }
    ret = !n;
  } else if (Enabled(bundle, OPT_PROXY))
    ret = (*proxyfun)(bundle, peer, s);

  close(s);

  return ret;
}

static VOS_INT32
ipcp_SetIPaddress(struct ipcp *ipcp, struct ppp_in_addr myaddr,
                  struct ppp_in_addr hisaddr)
{
  struct bundle *bundle = ipcp->fsm.bundle;
  struct ncpaddr myncpaddr, hisncpaddr;
  struct ncprange myrange;
  struct ppp_in_addr mask;
  struct sockaddr_storage ssdst, ssgw, ssmask;
  struct sockaddr *sadst, *sagw, *samask;

  sadst = (struct sockaddr *)&ssdst;
  sagw = (struct sockaddr *)&ssgw;
  samask = (struct sockaddr *)&ssmask;

  ncpaddr_setip4(&hisncpaddr, hisaddr);
  ncpaddr_setip4(&myncpaddr, myaddr);
  ncprange_sethost(&myrange, &myncpaddr);

  mask = addr2mask(myaddr);

  if (ipcp->ifmask.s_addr != INADDR_ANY &&
      (ipcp->ifmask.s_addr & mask.s_addr) == mask.s_addr)
    ncprange_setip4mask(&myrange, ipcp->ifmask);

  if (!iface_Add(bundle->iface, &bundle->ncp, &myrange, &hisncpaddr,
                 IFACE_ADD_FIRST|IFACE_FORCE_ADD|IFACE_SYSTEM))
    return 0;

  if (!Enabled(bundle, OPT_IFACEALIAS))
    iface_Clear(bundle->iface, &bundle->ncp, AF_INET,
                IFACE_CLEAR_ALIASES|IFACE_SYSTEM);

  if (bundle->ncp.cfg.sendpipe > 0 || bundle->ncp.cfg.recvpipe > 0) {
    ncprange_getsa(&myrange, &ssgw, &ssmask);
    ncpaddr_getsa(&hisncpaddr, &ssdst);
    rt_Update(bundle, sadst, sagw, samask);
  }

  if (Enabled(bundle, OPT_SROUTES))
    route_Change(bundle, bundle->ncp.route, &myncpaddr, &hisncpaddr);

#ifndef NORADIUS
  if (bundle->radius.valid)
    route_Change(bundle, bundle->radius.routes, &myncpaddr, &hisncpaddr);
#endif

  return 1;    /* Ok */
}

static struct ppp_in_addr
ChooseHisAddr(struct bundle *bundle, struct ppp_in_addr gw)
{
  struct ppp_in_addr try;
  VOS_UINT32 f;

  for (f = 0; f < bundle->ncp.ipcp.cfg.peer_list.nItems; f++) {
    try = iplist_next(&bundle->ncp.ipcp.cfg.peer_list);
    TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "ChooseHisAddr: Check item %ld (%s)\n",
              f, inet_ntoa(try));
    if (ipcp_SetIPaddress(&bundle->ncp.ipcp, gw, try)) {
      log_Printf(LogIPCP, "Selected IP address %s\n", inet_ntoa(try));
      break;
    }
  }

  if (f == bundle->ncp.ipcp.cfg.peer_list.nItems) {
    TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "ChooseHisAddr: All addresses in use !\n");
    try.s_addr = INADDR_ANY;
  }

  return try;
}
#endif
void
IpcpInitRestartCounter(struct fsm *fp, VOS_INT32 what)
{
  /* Set fsm timer load */
  struct ipcp *ipcp = fsm2ipcp(fp);

/*   fp->FsmTimer.load = ipcp->cfg.fsm.timeout * SECTICKS;*/
  switch (what) {
    case FSM_REQ_TIMER:
      fp->restart = ipcp->cfg.fsm.maxreq; /* [false alarm]:移植开源代码 */
      break;
    case FSM_TRM_TIMER:
      fp->restart = ipcp->cfg.fsm.maxtrm; /* [false alarm]:移植开源代码 */
      break;
    default:
      fp->restart = 1;
      break;
  }

  /*========>A32D12744*/
  if( VOS_NULL_PTR !=(fp->timer) )
  {
      VOS_StopRelTimer(&(fp->timer));
  }
  /*A32D12744<========*/

  if (VOS_OK !=
      VOS_StartRelTimer(&(fp->timer),PS_PID_APP_PPP,PPP_FSM_TIME_INTERVAL,
      PPP_LINK_TO_ID(fp->link),PHASE_NETWORK,VOS_RELTIMER_NOLOOP, VOS_TIMER_PRECISION_0))
  {
        PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL,"start reltimer error\r\n");
  }


}

void
IpcpSendConfigReq(struct fsm *fp)
{
/*因为在3G文档里，不需要向对方发送config帧*/
#if 0 /*fanzhibin f49086 delete it*/
  /* Send config REQ please */
  struct physical *p = link2physical(fp->link);
  struct ipcp *ipcp = fsm2ipcp(fp);
#endif
  VOS_CHAR buff[24];
  struct fsm_opt *o;

  o = (struct fsm_opt *)buff;
#if 0
  if ((p && !physical_IsSync(p)) || !REJECTED(ipcp, TY_IPADDR)) {
    PS_MEM_CPY(o->data, &ipcp->my_ip.s_addr, 4);
    INC_FSM_OPT(TY_IPADDR, 6, o);
  }

  if (ipcp->my_compproto && !REJECTED(ipcp, TY_COMPPROTO)) {
    if (ipcp->heis1172) {
      VOS_UINT16 proto = PROTO_VJCOMP;

      ua_htons(&proto, o->data);
      INC_FSM_OPT(TY_COMPPROTO, 4, o);
    } else {
      struct compreq req;

      req.proto = htons(ipcp->my_compproto >> 16);
      req.slots = (ipcp->my_compproto >> 8) & 255;
      req.compcid = ipcp->my_compproto & 1;
      PS_MEM_CPY(o->data, &req, 4);
      INC_FSM_OPT(TY_COMPPROTO, 6, o);
    }
  }

  if (IsEnabled(ipcp->cfg.ns.dns_neg)) {
    if (!REJECTED(ipcp, TY_PRIMARY_DNS - TY_ADJUST_NS)) {
      PS_MEM_CPY(o->data, &ipcp->ns.dns[0].s_addr, 4);
      INC_FSM_OPT(TY_PRIMARY_DNS, 6, o);
    }

    if (!REJECTED(ipcp, TY_SECONDARY_DNS - TY_ADJUST_NS)) {
      PS_MEM_CPY(o->data, &ipcp->ns.dns[1].s_addr, 4);
      INC_FSM_OPT(TY_SECONDARY_DNS, 6, o);
    }
  }
#endif
  fsm_Output(fp, CODE_CONFIGREQ, fp->reqid, buff, buff - buff,
             MB_IPCPOUT);

}

void
IpcpSentTerminateReq(struct fsm *fp)
{
  /* Term REQ just sent by FSM */
}

void
IpcpSendTerminateAck(struct fsm *fp, VOS_CHAR id)
{
  /* Send Term ACK please */
  fsm_Output(fp, CODE_TERMACK, id, VOS_NULL_PTR, 0, MB_IPCPOUT);
}

void
IpcpLayerStart(struct fsm *fp)
{
  /* We're about to start up ! */
  struct ipcp *ipcp = fsm2ipcp(fp);

  PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "ipcp LayerStart");
  throughput_start(&ipcp->throughput, "IPCP throughput", /* [false alarm]:移植开源代码 */
                   /*Enabled(fp->bundle, OPT_THROUGHPUT)*/1);
  fp->more.reqs = fp->more.naks = fp->more.rejs = ipcp->cfg.fsm.maxreq * 3;
  ipcp->peer_req = 0;
}

void
IpcpLayerFinish(struct fsm *fp)
{
  /* We're now down */
  struct ipcp *ipcp = fsm2ipcp(fp);

  PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "ipcp LayerFinish");
  throughput_stop(&ipcp->throughput); /* [false alarm]:移植开源代码 */

#if 0 /*fanzhibin f49086 delete it*/
  throughput_log(&ipcp->throughput, LogIPCP, VOS_NULL_PTR);
#endif
}
#if 0 /*fanzhibin f49086 delete it*/
/*
 * Called from iface_Add() via ncp_IfaceAddrAdded()
 */
void
ipcp_IfaceAddrAdded(struct ipcp *ipcp, const struct iface_addr *addr)
{
  struct bundle *bundle = ipcp->fsm.bundle;

  if (Enabled(bundle, OPT_PROXY) || Enabled(bundle, OPT_PROXYALL))
    ipcp_proxyarp(ipcp, arp_SetProxy, addr);
}

/*
 * Called from iface_Clear() and iface_Delete() via ncp_IfaceAddrDeleted()
 */
void
ipcp_IfaceAddrDeleted(struct ipcp *ipcp, const struct iface_addr *addr)
{
  struct bundle *bundle = ipcp->fsm.bundle;

  if (Enabled(bundle, OPT_PROXY) || Enabled(bundle, OPT_PROXYALL))
    ipcp_proxyarp(ipcp, arp_ClearProxy, addr);
}
#endif
void
IpcpLayerDown(struct fsm *fp)
{
#if 0 /*fanzhibin f49086 delete it*/
  /* About to come down */
  struct ipcp *ipcp = fsm2ipcp(fp);
  static VOS_INT32 recursing;
  VOS_CHAR addr[16];

  if (!recursing++) {
    snprintf(addr, sizeof addr, "%s", inet_ntoa(ipcp->my_ip));
    log_Printf(LogIPCP, "%s: LayerDown: %s\n", fp->link->name, addr);

#ifndef NORADIUS
    radius_Account(&fp->bundle->radius, &fp->bundle->radacct,
                   fp->bundle->links, RAD_STOP, &ipcp->throughput);

  if (fp->bundle->radius.cfg.file && fp->bundle->radius.filterid)
    system_Select(fp->bundle, fp->bundle->radius.filterid, LINKDOWNFILE,
                  VOS_NULL_PTR, VOS_NULL_PTR);
#endif

    /*
     * XXX this stuff should really live in the FSM.  Our config should
     * associate executable sections in files with events.
     */
    if (system_Select(fp->bundle, addr, LINKDOWNFILE, VOS_NULL_PTR, VOS_NULL_PTR) < 0) {
      if (bundle_GetLabel(fp->bundle)) {
         if (system_Select(fp->bundle, bundle_GetLabel(fp->bundle),
                          LINKDOWNFILE, VOS_NULL_PTR, VOS_NULL_PTR) < 0)
         system_Select(fp->bundle, "MYADDR", LINKDOWNFILE, VOS_NULL_PTR, VOS_NULL_PTR);
      } else
        system_Select(fp->bundle, "MYADDR", LINKDOWNFILE, VOS_NULL_PTR, VOS_NULL_PTR);
    }

    ipcp_Setup(ipcp, INADDR_NONE);
  }
  recursing--;
#endif
}
#if 0 /*fanzhibin f49086 delete it*/
VOS_INT32
ipcp_InterfaceUp(struct ipcp *ipcp)
{
  if (!ipcp_SetIPaddress(ipcp, ipcp->my_ip, ipcp->peer_ip)) {
    log_Printf(LogERROR, "ipcp_InterfaceUp: unable to set ip address\n");
    return 0;
  }

  if (!iface_SetFlags(ipcp->fsm.bundle->iface->name, IFF_UP)) {
    log_Printf(LogERROR, "ipcp_InterfaceUp: Can't set the IFF_UP flag on %s\n",
               ipcp->fsm.bundle->iface->name);
    return 0;
  }

#ifndef NONAT
  if (ipcp->fsm.bundle->NatEnabled)
    PacketAliasSetAddress(ipcp->my_ip);
#endif

  return 1;
}
#endif
VOS_INT32
IpcpLayerUp(struct fsm *fp)
{
  /* We're now up */
  struct ipcp *ipcp = fsm2ipcp(fp);

#if 0/*fanzhibin f49086 delete it*/
  VOS_CHAR tbuff[16];
  log_Printf(LogIPCP, "%s: LayerUp.\n", fp->link->name);
  snprintf(tbuff, sizeof tbuff, "%s", inet_ntoa(ipcp->my_ip));
  log_Printf(LogIPCP, "myaddr %s hisaddr = %s\n",
             tbuff, inet_ntoa(ipcp->peer_ip));

  if (ipcp->peer_compproto >> 16 == PROTO_VJCOMP)
    sl_compress_init(&ipcp->vj.cslc, (ipcp->peer_compproto >> 8) & 255);

  if (!ipcp_InterfaceUp(ipcp))
    return 0;

#ifndef NORADIUS
  radius_Account_Set_Ip(&fp->bundle->radacct, &ipcp->peer_ip, &ipcp->ifmask);
  radius_Account(&fp->bundle->radius, &fp->bundle->radacct, fp->bundle->links,
                 RAD_START, &ipcp->throughput);

  if (fp->bundle->radius.cfg.file && fp->bundle->radius.filterid)
    system_Select(fp->bundle, fp->bundle->radius.filterid, LINKUPFILE,
                  VOS_NULL_PTR, VOS_NULL_PTR);
#endif

  /*
   * XXX this stuff should really live in the FSM.  Our config should
   * associate executable sections in files with events.
   */
  if (system_Select(fp->bundle, tbuff, LINKUPFILE, VOS_NULL_PTR, VOS_NULL_PTR) < 0) {
    if (bundle_GetLabel(fp->bundle)) {
      if (system_Select(fp->bundle, bundle_GetLabel(fp->bundle),
                       LINKUPFILE, VOS_NULL_PTR, VOS_NULL_PTR) < 0)
        system_Select(fp->bundle, "MYADDR", LINKUPFILE, VOS_NULL_PTR, VOS_NULL_PTR);
    } else
      system_Select(fp->bundle, "MYADDR", LINKUPFILE, VOS_NULL_PTR, VOS_NULL_PTR);
  }
#endif
  fp->more.reqs = fp->more.naks = fp->more.rejs = ipcp->cfg.fsm.maxreq * 3; /* [false alarm]:移植开源代码 */
#if 0/*fanzhibin f49086 delete it*/
  log_DisplayPrompts();
#endif
  return 1;
}
#if 0 /*fanzhibin f49086 delete it*/
static void
ipcp_ValidateReq(struct ipcp *ipcp, struct ppp_in_addr ip, struct fsm_decode *dec)
{
  struct bundle *bundle = ipcp->fsm.bundle;
  struct iface *iface = bundle->iface;
  struct ppp_in_addr myaddr, peer;
  VOS_INT32 n;

  if (iplist_isvalid(&ipcp->cfg.peer_list)) {
    ncprange_getip4addr(&ipcp->cfg.my_range, &myaddr);
    if (ip.s_addr == INADDR_ANY ||
        iplist_ip2pos(&ipcp->cfg.peer_list, ip) < 0 ||
        !ipcp_SetIPaddress(ipcp, myaddr, ip)) {
      log_Printf(LogIPCP, "%s: Address invalid or already in use\n",
                 inet_ntoa(ip));
      /*
       * If we've already had a valid address configured for the peer,
       * try NAKing with that so that we don't have to upset things
       * too much.
       */
      for (n = 0; n < iface->addrs; n++) {
        if (!ncpaddr_getip4(&iface->addr[n].peer, &peer))
          continue;
        if (iplist_ip2pos(&ipcp->cfg.peer_list, peer) >= 0) {
          ipcp->peer_ip = peer;
          break;
        }
      }

      if (n == iface->addrs) {
        /* Just pick an IP number from our list */
        ipcp->peer_ip = ChooseHisAddr(bundle, myaddr);
      }

      if (ipcp->peer_ip.s_addr == INADDR_ANY) {
        *dec->rejend++ = TY_IPADDR;
        *dec->rejend++ = 6;
        PS_MEM_CPY(dec->rejend, &ip.s_addr, 4);
        dec->rejend += 4;
      } else {
        *dec->nakend++ = TY_IPADDR;
        *dec->nakend++ = 6;
        PS_MEM_CPY(dec->nakend, &ipcp->peer_ip.s_addr, 4);
        dec->nakend += 4;
      }
      return;
    }
  } else if (ip.s_addr == INADDR_ANY ||
             !ncprange_containsip4(&ipcp->cfg.peer_range, ip)) {
    /*
     * If the destination address is not acceptable, NAK with what we
     * want to use.
     */
    *dec->nakend++ = TY_IPADDR;
    *dec->nakend++ = 6;
    for (n = 0; n < iface->addrs; n++)
      if (ncprange_contains(&ipcp->cfg.peer_range, &iface->addr[n].peer)) {
        /* We prefer the already-configured address */
        ncpaddr_getip4addr(&iface->addr[n].peer, (VOS_UINT32 *)dec->nakend);
        break;
      }

    if (n == iface->addrs)
      PS_MEM_CPY(dec->nakend, &ipcp->peer_ip.s_addr, 4);

    dec->nakend += 4;
    return;
  }

  ipcp->peer_ip = ip;
  *dec->ackend++ = TY_IPADDR;
  *dec->ackend++ = 6;
  PS_MEM_CPY(dec->ackend, &ip.s_addr, 4);
  dec->ackend += 4;
}
#endif


/*****************************************************************************
 Prototype      : StringCompare
 Description    : 对于两个字符串比较他们从头起的一段。

 Input          : ---两个字符串的首地址与比较的长度
 Output         : ---
 Return Value   : ---相等返回VOS_OK，否则返回VOS_ERR
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-12-31
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32 StringCompare(VOS_CHAR* pString1,VOS_VOID* pString2,VOS_UINT16 len)
{
    VOS_INT32 i;
    VOS_CHAR* pString3 = (VOS_CHAR*)pString2;

    for(i=0;i<len;i++)
    {
            if(*(pString1+i) != *(pString3+i))
            return VOS_ERR;
    }
    return VOS_OK;
}

/*****************************************************************************
 Prototype      : DecodeAtIndication
 Description    : 解析从AT接收到的ACK与NAK报文。

 Input          : ---pIpcp:指向该报文所在的ipcp结构
                  ---pEchoBuffer:指向接收到的来自AT的ACK或NAK报文的首地址
                  ---BufferLen:指向接收到的来自AT的ACK或NAK报文的长度
 Output         : ---
 Return Value   : ---成功返回VOS_OK，否则返回VOS_ERR
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-12-31
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32
DecodeAtIndication(struct ipcp* pIpcp,VOS_CHAR* pEchoBuffer,VOS_UINT16 BufferLen)
{
    struct fsm_opt *opt;
    VOS_UINT16 Len = 0;

    PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "decode at indication\r\n");

    while(Len < BufferLen)
    {
        opt = (struct fsm_opt *)(pEchoBuffer + Len);
        if (opt->hdr.len < sizeof(struct fsm_opt_hdr))
            {
                PPP_MNTN_LOG1(PS_PID_APP_PPP, 0, LOG_LEVEL_WARNING,
                              "Bad option length = %f\r\n", opt->hdr.len);
                return VOS_ERR;
            }

        switch (opt->hdr.id)
            {
                case TY_IPADDR:
                    PS_MEM_CPY(&(pIpcp->peer_ip.s_addr), opt->data, (opt->hdr.len-2));
                    pIpcp->IpAddr_neg |= NEG_ACCEPTED;
                    break;

                case TY_COMPPROTO:
                    PS_MEM_CPY(pIpcp->CompressProto, opt->data, (opt->hdr.len-2));
                    pIpcp->ComressProtoLen = (opt->hdr.len-2);
                    pIpcp->CompressProto_neg|= NEG_ACCEPTED;
                    break;

                case TY_IPADDRS:
                    break;

                case TY_PRIMARY_NBNS:
                    if (WINS_CONFIG_ENABLE == g_ucPppConfigWins)
                    {
                        PS_MEM_CPY(&(pIpcp->PriNbnsAddr.s_addr), opt->data, (opt->hdr.len-2));
                        pIpcp->PriNbns_neg |= NEG_ACCEPTED;
                    }
                    break;

                case TY_SECONDARY_NBNS:
                    if (WINS_CONFIG_ENABLE == g_ucPppConfigWins)
                    {
                        PS_MEM_CPY(&(pIpcp->SecNbnsAddr.s_addr), opt->data, (opt->hdr.len-2));
                        pIpcp->SecNbns_neg |= NEG_ACCEPTED;
                    }
                    break;

                case TY_PRIMARY_DNS:
                    PS_MEM_CPY(&(pIpcp->PriDnsAddr.s_addr), opt->data, (opt->hdr.len-2));
                    pIpcp->PriDns_neg |= NEG_ACCEPTED;
                    break;

                case TY_SECONDARY_DNS:
                    PS_MEM_CPY(&(pIpcp->SecDnsAddr.s_addr), opt->data, (opt->hdr.len-2));
                    pIpcp->SecDns_neg |= NEG_ACCEPTED;
                    break;

                default:
                    break;
            }
        Len += (VOS_UINT16)(opt->hdr.len);
    }

    return VOS_OK;
}


void
IpcpDecodeConfig(struct fsm *fp, VOS_CHAR *cp, VOS_CHAR *end, VOS_INT32 mode_type,
                 struct fsm_decode *dec)
{
  /* Deal with incoming PROTO_IPCP */
#if 0 /*fanzhibin f49086 delete it*/
  struct ncpaddr ncpaddr;
  VOS_UINT32 compproto;
  struct compreq *pcomp;
  struct ppp_in_addr ipaddr, dstipaddr, have_ip;
  VOS_CHAR tbuff[100], tbuff2[100];
  struct fsm_opt *opt, nak;
#endif
  struct ipcp *ipcp = fsm2ipcp(fp);
  VOS_INT32 gotdnsnak;
  struct ppp_in_addr ipaddr;
  struct fsm_opt *opt;

  gotdnsnak = 0;

  while (end - cp >= sizeof(opt->hdr)) {
    if ((opt = fsm_readopt(&cp)) == VOS_NULL_PTR)
      break;

    /*VOS_nsprintf(tbuff, sizeof tbuff, " %s[%d]", protoname(opt->hdr.id),opt->hdr.len); */

    switch (opt->hdr.id) {
    case TY_IPADDR:        /* RFC1332 */

      switch (mode_type) {
      case MODE_REQ:
        ipcp->peer_req = 1; /* [false alarm]:移植开源代码 */

        if (!IsAccepted(ipcp->IpAddr_neg))
        {
          PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "ipcp:ip address rej!\r\n");
        }
        else
        {
            if(VOS_OK != StringCompare(opt->data,&(ipcp->peer_ip.s_addr),sizeof(struct ppp_in_addr)))
            {
                PS_MEM_CPY(opt->data, &(ipcp->peer_ip.s_addr), sizeof(struct ppp_in_addr));
                fsm_nak(dec, opt);
                PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "ipcp:ip address nak!\r\n");
            }
            else
            {
                fsm_ack(dec, opt);
                PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "ipcp:ip address ack!\r\n");
            }
        }


#if 0 /*fanzhibin f49086 delete it*/
        ipcp_ValidateReq(ipcp, ipaddr, dec);
#endif
        break;
#if 0 /*fanzhibin f49086 delete it*/
      case MODE_NAK:
        if (ncprange_containsip4(&ipcp->cfg.my_range, ipaddr)) {
          /* Use address suggested by peer */
          snprintf(tbuff2, sizeof tbuff2, "%s changing address: %s ", tbuff,
                   inet_ntoa(ipcp->my_ip));
          log_Printf(LogIPCP, "%s --> %s\n", tbuff2, inet_ntoa(ipaddr));
          ipcp->my_ip = ipaddr;
          ncpaddr_setip4(&ncpaddr, ipcp->my_ip);
          bundle_AdjustFilters(fp->bundle, &ncpaddr, VOS_NULL_PTR);
        } else {
          log_Printf(log_IsKept(LogIPCP) ? LogIPCP : LogPHASE,
                    "%s: Unacceptable address!\n", inet_ntoa(ipaddr));
          fsm_Close(&ipcp->fsm);
        }
        break;

      case MODE_REJ:
        ipcp->peer_reject |= (1 << opt->hdr.id);
        break;
#endif
      }
      break;

    case TY_COMPPROTO:
#if 0 /*fanzhibin f49086 delete it*/
      pcomp = (struct compreq *)opt->data;
      compproto = (ntohs(pcomp->proto) << 16) + (pcomp->slots << 8) +
                  pcomp->compcid;
      log_Printf(LogIPCP, "%s %s\n", tbuff, vj2asc(compproto));
#endif
      switch (mode_type) {
      case MODE_REQ:

        if (!IsAccepted(ipcp->CompressProto_neg)) /* [false alarm]:移植开源代码 */
        {
          if (fp->link->ipcp.stage == IPCP_SUCCESS_FROM_GGSN)
          {
              fsm_rej(dec, opt);
              PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "ipcp:CompressPro rej!\r\n");
          }
          else
          {
              fsm_nak(dec, opt);
              PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "ipcp:CompressPro nak(no neg)!\r\n");
          }
        }
        else
        {
            if(VOS_OK != StringCompare(opt->data,ipcp->CompressProto,ipcp->ComressProtoLen))
            {
                PS_MEM_CPY(opt->data, ipcp->CompressProto, ipcp->ComressProtoLen);
                fsm_nak(dec, opt);
                PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "ipcp:CompressPro nak!\r\n");
            }
            else
            {
                fsm_ack(dec, opt);
                PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "ipcp:CompressPro ack!\r\n");
            }
        }

#if 0 /*fanzhibin f49086 delete it*/
        if (!IsAccepted(ipcp->cfg.vj.neg))
          fsm_rej(dec, opt);
        else {
          switch (opt->hdr.len) {
          case 4:        /* RFC1172 */
            if (ntohs(pcomp->proto) == PROTO_VJCOMP) {
              log_Printf(LogWARN, "Peer is speaking RFC1172 compression "
                         "protocol !\n");
              ipcp->heis1172 = 1;
              ipcp->peer_compproto = compproto;
              fsm_ack(dec, opt);
            } else {
              pcomp->proto = htons(PROTO_VJCOMP);
              nak.hdr.id = TY_COMPPROTO;
              nak.hdr.len = 4;
              PS_MEM_CPY(nak.data, &pcomp, 2);
              fsm_nak(dec, &nak);
            }
            break;
          case 6:        /* RFC1332 */
            if (ntohs(pcomp->proto) == PROTO_VJCOMP) {
              if (pcomp->slots <= MAX_VJ_STATES
                  && pcomp->slots >= MIN_VJ_STATES) {
                /* Ok, we can do that */
                ipcp->peer_compproto = compproto;
                ipcp->heis1172 = 0;
                fsm_ack(dec, opt);
              } else {
                /* Get as close as we can to what he wants */
                ipcp->heis1172 = 0;
                pcomp->slots = pcomp->slots < MIN_VJ_STATES ?
                               MIN_VJ_STATES : MAX_VJ_STATES;
                nak.hdr.id = TY_COMPPROTO;
                nak.hdr.len = 4;
                PS_MEM_CPY(nak.data, &pcomp, 2);
                fsm_nak(dec, &nak);
              }
            } else {
              /* What we really want */
              pcomp->proto = htons(PROTO_VJCOMP);
              pcomp->slots = DEF_VJ_STATES;
              pcomp->compcid = 1;
              nak.hdr.id = TY_COMPPROTO;
              nak.hdr.len = 6;
              PS_MEM_CPY(nak.data, &pcomp, sizeof pcomp);
              fsm_nak(dec, &nak);
            }
            break;
          default:
            fsm_rej(dec, opt);
            break;
          }
}
#endif

        break;
#if 0 /*fanzhibin f49086 delete it*/
      case MODE_NAK:
        if (ntohs(pcomp->proto) == PROTO_VJCOMP) {
          if (pcomp->slots > MAX_VJ_STATES)
            pcomp->slots = MAX_VJ_STATES;
          else if (pcomp->slots < MIN_VJ_STATES)
            pcomp->slots = MIN_VJ_STATES;
          compproto = (ntohs(pcomp->proto) << 16) + (pcomp->slots << 8) +
                      pcomp->compcid;
        } else
          compproto = 0;
        log_Printf(LogIPCP, "%s changing compproto: %08x --> %08x\n",
                   tbuff, ipcp->my_compproto, compproto);
        ipcp->my_compproto = compproto;
        break;

      case MODE_REJ:
        ipcp->peer_reject |= (1 << opt->hdr.id);
        break;
#endif
      }

      break;



    case TY_IPADDRS:        /* RFC1172 */
#if 0 /*fanzhibin f49086 delete it*/
      PS_MEM_CPY(&ipaddr.s_addr, opt->data, 4);
      PS_MEM_CPY(&dstipaddr.s_addr, opt->data + 4, 4);
      snprintf(tbuff2, sizeof tbuff2, "%s %s,", tbuff, inet_ntoa(ipaddr));
      log_Printf(LogIPCP, "%s %s\n", tbuff2, inet_ntoa(dstipaddr));
#endif
      switch (mode_type) {
      case MODE_REQ:
        fsm_nak(dec, opt);
        PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "ipcp:ipaddrs rej!\r\n");
        break;

      case MODE_NAK:
      case MODE_REJ:
        break;
      }
      break;

    case TY_PRIMARY_NBNS:    /* M$ NetBIOS nameserver hack (rfc1877) */

      switch (mode_type) {
      case MODE_REQ:
        if (!IsAccepted(ipcp->PriNbns_neg)) /* [false alarm]:移植开源代码 */
        {
          if (fp->link->ipcp.stage == IPCP_SUCCESS_FROM_GGSN)
          {
              fsm_rej(dec, opt);
              PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "ipcp:pri_nbns rej!\r\n");
          }
          else
          {
              fsm_nak(dec, opt);
              PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "ipcp:pri_nbns nak(no neg)!\r\n");
          }
        }
        else
        {
            if(VOS_OK != StringCompare(opt->data,&(ipcp->PriNbnsAddr.s_addr),sizeof(struct ppp_in_addr)))
            {
                PS_MEM_CPY(opt->data, &(ipcp->PriNbnsAddr.s_addr),sizeof(struct ppp_in_addr));
                fsm_nak(dec, opt);
                PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "ipcp:pri_nbns nak!\r\n");
            }
            else
            {
                fsm_ack(dec, opt);
                PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "ipcp:pri_nbns ack!\r\n");
            }
        }

        break;

      case MODE_NAK:
      case MODE_REJ:
        break;
      }
      break;

    case TY_SECONDARY_NBNS:

      switch (mode_type) {
      case MODE_REQ:
        if (!IsAccepted(ipcp->SecNbns_neg)) /* [false alarm]:移植开源代码 */
        {
          if (fp->link->ipcp.stage == IPCP_SUCCESS_FROM_GGSN)
          {
              fsm_rej(dec, opt);
              PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "ipcp:sec_nbns rej!\r\n");
          }
          else
          {
              fsm_nak(dec, opt);
              PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "ipcp:sec_nbns nak(no neg)!\r\n");
          }
        }
        else
        {
            if(VOS_OK != StringCompare(opt->data,&(ipcp->SecNbnsAddr.s_addr),sizeof(struct ppp_in_addr)))
            {
                PS_MEM_CPY(opt->data, &(ipcp->SecNbnsAddr.s_addr),sizeof(struct ppp_in_addr));
                fsm_nak(dec, opt);
                PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "ipcp:sec_nbns nak!\r\n");
            }
            else
            {
                fsm_ack(dec, opt);
                PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "ipcp:sec_nbns ack!\r\n");
            }
        }

        break;

      case MODE_NAK:
      case MODE_REJ:
        break;
      }
      break;

    case TY_PRIMARY_DNS:    /* primary dns */
#if 0 /*fanzhibin f49086 delete it*/
      PS_MEM_CPY(&ipaddr.s_addr, opt->data, 4);
      PS_MEM_CPY(&dstipaddr.s_addr, opt->data + 4, 4);
      snprintf(tbuff2, sizeof tbuff2, "%s %s,", tbuff, inet_ntoa(ipaddr));
      log_Printf(LogIPCP, "%s %s\n", tbuff2, inet_ntoa(dstipaddr));
#endif
      switch (mode_type) {
      case MODE_REQ:
        if (!IsAccepted(ipcp->PriDns_neg)) /* [false alarm]:移植开源代码 */
        {
            if (fp->link->ipcp.stage == IPCP_SUCCESS_FROM_GGSN)
            {
                fsm_rej(dec, opt);
                PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "ipcp:pri_dns rej!\r\n");
            }
            else
            {
                fsm_nak(dec, opt);
                PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "ipcp:pri_dns nak(no neg)!\r\n");
            }
        }
        else
        {
            if(VOS_OK != StringCompare(opt->data,&(ipcp->PriDnsAddr.s_addr),sizeof(struct ppp_in_addr)))
            {
                PS_MEM_CPY(opt->data, &(ipcp->PriDnsAddr.s_addr),sizeof(struct ppp_in_addr));
                fsm_nak(dec, opt);
                PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "ipcp:pri_dns nak!\r\n");
            }
            else
            {
                fsm_ack(dec, opt);
                PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "ipcp:pri_dns ack!\r\n");
            }
        }

        break;

      case MODE_NAK:
      case MODE_REJ:
        break;
      }
      break;

    case TY_SECONDARY_DNS:    /* primary dns */
 #if 0 /*fanzhibin f49086 delete it*/
      PS_MEM_CPY(&ipaddr.s_addr, opt->data, 4);
      PS_MEM_CPY(&dstipaddr.s_addr, opt->data + 4, 4);
      snprintf(tbuff2, sizeof tbuff2, "%s %s,", tbuff, inet_ntoa(ipaddr));
      log_Printf(LogIPCP, "%s %s\n", tbuff2, inet_ntoa(dstipaddr));
#endif
      switch (mode_type) {
      case MODE_REQ:
        if (!IsAccepted(ipcp->SecDns_neg)) /* [false alarm]:移植开源代码 */
        {
            if (fp->link->ipcp.stage == IPCP_SUCCESS_FROM_GGSN)
            {
                fsm_rej(dec, opt);
                PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "ipcp:sec_dns rej!\r\n");
            }
            else
            {
                fsm_nak(dec, opt);
                PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "ipcp:sec_dns nak(no neg)!\r\n");
            }
        }
        else
        {
            if(VOS_OK != StringCompare(opt->data,&(ipcp->SecDnsAddr.s_addr),sizeof(struct ppp_in_addr)))
            {
                PS_MEM_CPY(opt->data, &(ipcp->SecDnsAddr.s_addr),sizeof(struct ppp_in_addr));
                fsm_nak(dec, opt);
                PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "ipcp:sec_dns nak!\r\n");
            }
            else
            {
                fsm_ack(dec, opt);
                PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "ipcp:sec_dns ack!\r\n");
            }
        }

        break;

      case MODE_NAK:
      case MODE_REJ:
        break;
      }
      break;



#if 0 /*fanzhibin f49086 delete it*/
    case TY_PRIMARY_DNS:    /* DNS negotiation (rfc1877) */
    case TY_SECONDARY_DNS:
      PS_MEM_CPY(&ipaddr.s_addr, opt->data, 4);
      TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "%s %s\n"/*, tbuff, inet_ntoa(ipaddr)*/);


      switch (mode_type) {
      case MODE_REQ:



        if (!IsAccepted(ipcp->cfg.ns.dns_neg)) {
          ipcp->my_reject |= (1 << (opt->hdr.id - TY_ADJUST_NS));
          fsm_rej(dec, opt);
          break;
        }
        have_ip = ipcp->ns.dns[opt->hdr.id == TY_PRIMARY_DNS ? 0 : 1];

        if (opt->hdr.id == TY_PRIMARY_DNS && ipaddr.s_addr != have_ip.s_addr &&
            ipaddr.s_addr == ipcp->ns.dns[1].s_addr) {
          /* Swap 'em 'round */
          ipcp->ns.dns[0] = ipcp->ns.dns[1];
          ipcp->ns.dns[1] = have_ip;
          have_ip = ipcp->ns.dns[0];
        }

        if (ipaddr.s_addr != have_ip.s_addr) {
          /*
           * The client has got the DNS stuff wrong (first request) so
           * we'll tell 'em how it is
           */
          nak.hdr.id = opt->hdr.id;
          nak.hdr.len = 6;
          PS_MEM_CPY(nak.data, &have_ip.s_addr, 4);
          fsm_nak(dec, &nak);
        } else {
          /*
           * Otherwise they have it right (this time) so we send an ack packet
           * back confirming it... end of story
           */
          fsm_ack(dec, opt);
        }

        break;


      case MODE_NAK:
        if (IsEnabled(ipcp->cfg.ns.dns_neg)) {
          gotdnsnak = 1;
          PS_MEM_CPY(&ipcp->ns.dns[opt->hdr.id == TY_PRIMARY_DNS ? 0 : 1].s_addr,
                 opt->data, 4);
        }
        break;

      case MODE_REJ:        /* Can't do much, stop asking */
        ipcp->peer_reject |= (1 << (opt->hdr.id - TY_ADJUST_NS));
        break;

      }
      break;
#endif


#if 0 /*fanzhibin f49086 delete it*/
    case TY_PRIMARY_NBNS:    /* M$ NetBIOS nameserver hack (rfc1877) */
    case TY_SECONDARY_NBNS:
      PS_MEM_CPY(&ipaddr.s_addr, opt->data, 4);
      log_Printf(LogIPCP, "%s %s\n", tbuff, inet_ntoa(ipaddr));

      switch (mode_type) {
      case MODE_REQ:
        have_ip.s_addr =
          ipcp->cfg.ns.nbns[opt->hdr.id == TY_PRIMARY_NBNS ? 0 : 1].s_addr;

        if (have_ip.s_addr == INADDR_ANY) {
          log_Printf(LogIPCP, "NBNS REQ - rejected - nbns not set\n");
          ipcp->my_reject |= (1 << (opt->hdr.id - TY_ADJUST_NS));
          fsm_rej(dec, opt);
          break;
        }

        if (ipaddr.s_addr != have_ip.s_addr) {
          nak.hdr.id = opt->hdr.id;
          nak.hdr.len = 6;
          PS_MEM_CPY(nak.data, &have_ip.s_addr, 4);
          fsm_nak(dec, &nak);
        } else
          fsm_ack(dec, opt);
        break;

      case MODE_NAK:
        log_Printf(LogIPCP, "MS NBNS req %d - NAK\?\?\n", opt->hdr.id);
        break;

      case MODE_REJ:
        log_Printf(LogIPCP, "MS NBNS req %d - REJ\?\?\n", opt->hdr.id);
        break;
      }
      break;
#endif
    default:
      if (mode_type != MODE_NOP) {
        ipcp->my_reject |= (1 << opt->hdr.id); /* [false alarm]:移植开源代码 */
        fsm_rej(dec, opt);
      }
      break;
    }
  }
#if 0 /*fanzhibin f49086 delete it*/
  if (gotdnsnak) {
    if (ipcp->ns.writable) {
      TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "Updating resolver\n");
      if (!ipcp_WriteDNS(ipcp)) {
        ipcp->peer_reject |= (1 << (TY_PRIMARY_DNS - TY_ADJUST_NS));
        ipcp->peer_reject |= (1 << (TY_SECONDARY_DNS - TY_ADJUST_NS));
      } else
        bundle_AdjustDNS(fp->bundle);
    } else {
      TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "Not updating resolver (readonly)\n");
      bundle_AdjustDNS(fp->bundle);
    }
  }
#endif


  if (mode_type != MODE_NOP) {
    if (mode_type == MODE_REQ && !ipcp->peer_req) { /* [false alarm]:移植开源代码 */
      if (dec->rejend == dec->rej && dec->nakend == dec->nak) {
        /*
         * Pretend the peer has requested an IP.
         * We do this to ensure that we only send one NAK if the only
         * reason for the NAK is because the peer isn't sending a
         * TY_IPADDR REQ.  This stops us from repeatedly trying to tell
         * the peer that we have to have an IP address on their end.
         */
        ipcp->peer_req = 1;
      }
      ipaddr.s_addr = INADDR_ANY;
#if 0 /*fanzhibin f49086 delete it*/
      ipcp_ValidateReq(ipcp, ipaddr, dec);
#endif
    }
    fsm_opt_normalise(dec);
  }

}
#if 0
static const VOS_CHAR * const PhaseNames[] = {
  "Dead", "Establish", "Authenticate", "Network", "Terminate"
};
#endif


VOS_VOID Ppp_ProcConfigInfoInd(VOS_UINT16 usPppId)
{
    PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL,"Ppp_ProcConfigInfoInd begain\r\n");

    /* 可维可测信息上报*/
    Ppp_EventMntnInfo(usPppId, PPP_CONFIG_INFO_PROC_NOTIFY);

    /* PPP ID非法*/
    if((usPppId < 1)
           ||(usPppId > PPP_MAX_ID_NUM))
    {
    	PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL,"PppId out of range!\r\n");
    	return ;
    }

	/*定时器关闭*/
	if (VOS_NULL_PTR != (PPP_LINK(usPppId)->ipcp.hIpcpPendTimer))
	{
		PS_STOP_REL_TIMER(&(PPP_LINK(usPppId)->ipcp.hIpcpPendTimer));
		PPP_LINK(usPppId)->ipcp.hIpcpPendTimer = VOS_NULL_PTR;
	}


	/*处理待处理IPCP帧*/
	if (VOS_NULL_PTR != (PPP_LINK(usPppId)->ipcp.pstIpcpPendFrame))
	{
		if (PHASE_NETWORK != PPP_LINK(usPppId)->phase )
		{
			/* 如果当前不是IPCP阶段则直接丢弃待处理帧返回*/
			ppp_m_freem(PPP_LINK(usPppId)->ipcp.pstIpcpPendFrame);
		}
		else
		{
			/* 如果是IPCP阶段,则直接处理*/
			fsm_Input(&(PPP_LINK(usPppId)->ipcp.fsm), PPP_LINK(usPppId)->ipcp.pstIpcpPendFrame);
		}

		/*待处理IPCP帧置空*/
		PPP_LINK(usPppId)->ipcp.pstIpcpPendFrame = VOS_NULL_PTR;
	}

	return;
}


extern PPP_ZC_STRU *
ipcp_Input(/*struct bundle *bundle, */struct link *l, PPP_ZC_STRU *pstMem)
{
	struct ppp_mbuf 	*bp        = VOS_NULL_PTR;
	VOS_UINT32		 ulRtn     = VOS_OK;
       VOS_UINT8		 ucCode = 0;

	bp = ppp_m_get_from_ttfmem(pstMem);

    PPP_MemFree(pstMem);

	if (VOS_NULL_PTR == bp)
	{
		return VOS_NULL_PTR;
	}

	/* 如果当前还不是IPCP阶段则直接丢弃返回*/
	if (PHASE_NETWORK != l->phase )
	{
		if (l->phase < PHASE_NETWORK)
		{
            PPP_MNTN_LOG1(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL,
                          "Error: Unexpected IPCP in phase %d\r\n",(VOS_INT32)l->phase);
		}

		ppp_m_freem(bp);
		return VOS_NULL_PTR;
	}
	/*else if ( l->phase == PHASE_NETWORK) 后续是当前为IPCP阶段的处理*/


	/*如果不是IPCP Config Request则应该立即处理*/
  	ppp_mbuf_View(bp, &ucCode, sizeof (ucCode));
	if (ucCode != CODE_CONFIGREQ)
	{
		fsm_Input(&(l->ipcp.fsm), bp);
		return VOS_NULL_PTR;
	}
	/*else if (ucCode == CODE_CONFIGREQ) 后续是IPCP Config Request的处理*/


	/*释放待处理帧,收到新的IPCP Config Request帧,则说明老的帧已经失效*/
	if (VOS_NULL_PTR  != l->ipcp.pstIpcpPendFrame)
	{
		ppp_m_freem(l->ipcp.pstIpcpPendFrame);
		l->ipcp.pstIpcpPendFrame = VOS_NULL_PTR;
	}


	/*网侧已经激活或还未开始激活,则直接处理并返回*/
	if ( IPCP_SUCCESS_FROM_GGSN == l->ipcp.stage
		|| IPCP_NOT_RECEIVE_REQ  == l->ipcp.stage)
	{
		fsm_Input(&(l->ipcp.fsm), bp);
		return VOS_NULL_PTR;
	}
	/*else if (l->ipcp.stage != IPCP_SUCCESS_FROM_GGSN) 后续是当前为PDP未激活阶段的处理*/


	/*网侧在等待激活,则起定时器,并保存待处理包*/
	if (VOS_NULL_PTR == l->ipcp.hIpcpPendTimer)
	{
		/*====================*/ /* 启动定时器 */
        ulRtn = VOS_StartRelTimer(&(l->ipcp.hIpcpPendTimer),  PS_PID_APP_PPP,
			PPP_IPCP_PENDING_TIMER_LEN,  PPP_LINK_TO_ID(l),  PHASE_PDP_ACT_PENDING,  VOS_RELTIMER_NOLOOP,VOS_TIMER_PRECISION_0);
	}


	/*起定时器失败,则立即处理*/
	if (VOS_OK != ulRtn)
	{
		fsm_Input(&(l->ipcp.fsm), bp);
		return VOS_NULL_PTR;
	}


	l->ipcp.pstIpcpPendFrame = bp;

	return VOS_NULL_PTR;
}

#if 0 /*fanzhibin f49086 delete it*/
VOS_INT32
ipcp_UseHisIPaddr(struct bundle *bundle, struct ppp_in_addr hisaddr)
{
  struct ipcp *ipcp = &bundle->ncp.ipcp;
  struct ppp_in_addr myaddr;

  PS_MEM_SET(&ipcp->cfg.peer_range, '\0', sizeof ipcp->cfg.peer_range);
  iplist_reset(&ipcp->cfg.peer_list);
  ipcp->peer_ip = hisaddr;
  ncprange_setip4host(&ipcp->cfg.peer_range, hisaddr);
  ncprange_getip4addr(&ipcp->cfg.my_range, &myaddr);

  return ipcp_SetIPaddress(ipcp, myaddr, hisaddr);
}

VOS_INT32
ipcp_UseHisaddr(struct bundle *bundle, const VOS_CHAR *hisaddr, VOS_INT32 setaddr)
{
  struct ppp_in_addr myaddr;
  struct ncp *ncp = &bundle->ncp;
  struct ipcp *ipcp = &ncp->ipcp;
  struct ncpaddr ncpaddr;

  /* Use `hisaddr' for the peers address (set iface if `setaddr') */
  PS_MEM_SET(&ipcp->cfg.peer_range, '\0', sizeof ipcp->cfg.peer_range);
  iplist_reset(&ipcp->cfg.peer_list);
  if (strpbrk(hisaddr, ",-")) {
    iplist_setsrc(&ipcp->cfg.peer_list, hisaddr);
    if (iplist_isvalid(&ipcp->cfg.peer_list)) {
      iplist_setrandpos(&ipcp->cfg.peer_list);
      ipcp->peer_ip = ChooseHisAddr(bundle, ipcp->my_ip);
      if (ipcp->peer_ip.s_addr == INADDR_ANY) {
        log_Printf(LogWARN, "%s: None available !\n", ipcp->cfg.peer_list.src);
        return 0;
      }
      ncprange_setip4host(&ipcp->cfg.peer_range, ipcp->peer_ip);
    } else {
      log_Printf(LogWARN, "%s: Invalid range !\n", hisaddr);
      return 0;
    }
  } else if (ncprange_aton(&ipcp->cfg.peer_range, ncp, hisaddr) != 0) {
    if (ncprange_family(&ipcp->cfg.my_range) != AF_INET) {
      log_Printf(LogWARN, "%s: Not an AF_INET address !\n", hisaddr);
      return 0;
    }
    ncprange_getip4addr(&ipcp->cfg.my_range, &myaddr);
    ncprange_getip4addr(&ipcp->cfg.peer_range, &ipcp->peer_ip);

    if (setaddr && !ipcp_SetIPaddress(ipcp, myaddr, ipcp->peer_ip))
      return 0;
  } else
    return 0;

  ncpaddr_setip4(&ncpaddr, ipcp->peer_ip);
  bundle_AdjustFilters(bundle, VOS_NULL_PTR, &ncpaddr);

  return 1;    /* Ok */
}

struct ppp_in_addr
addr2mask(struct ppp_in_addr addr)
{
  VOS_UINT32 haddr = ntohl(addr.s_addr);

  haddr = IN_CLASSA(haddr) ? IN_CLASSA_NET :
          IN_CLASSB(haddr) ? IN_CLASSB_NET :
          IN_CLASSC_NET;
  addr.s_addr = htonl(haddr);

  return addr;
}
#endif
VOS_UINT32
ipcp_QueueLen(struct ipcp *ipcp)
{
  struct ppp_mqueue *q;
  VOS_UINT32 result;

  result = 0;
  for (q = ipcp->Queue; q < ipcp->Queue + IPCP_QUEUES(ipcp); q++)
    result += q->len;

  return result;
}

VOS_INT32
ipcp_PushPacket(struct ipcp *ipcp, struct link *l)
{
#if 0 /*fanzhibin f49086 delete it*/
  struct bundle *bundle = ipcp->fsm.bundle;
  unsigned alivesecs = 0;
#endif
  struct ppp_mqueue *queue;
  struct ppp_mbuf *bp;
  VOS_INT32 m_len;
  VOS_UINT32 secs = 0;

  if (ipcp->fsm.state != ST_OPENED)
    return 0;
#if 0 /*fanzhibin f49086 delete it*/
  /*
   * If ccp is not open but is required, do nothing.
   */
  if (l->ccp.fsm.state != ST_OPENED && ccp_Required(&l->ccp)) {
    log_Printf(LogPHASE, "%s: Not transmitting... waiting for CCP\n", l->name);
    return 0;
  }
#endif
  queue = ipcp->Queue + IPCP_QUEUES(ipcp) - 1;
  do {
    if (queue->top) {
      bp = ppp_m_dequeue(queue);
      bp = ppp_mbuf_Read(bp, &secs, sizeof secs);
      bp = ppp_m_pullup(bp);
      m_len = ppp_m_length(bp);

      link_PushPacket(l, bp,/* bundle, */0, PROTO_IPCP);
      ipcp_AddOutOctets(ipcp, m_len);
      return 1;
    }
  } while (queue-- != ipcp->Queue);

  return 0;
}

#endif /* #if(FEATURE_ON == FEATURE_PPP) */

