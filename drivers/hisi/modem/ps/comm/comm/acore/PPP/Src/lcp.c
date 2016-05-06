


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
#include "PPP/Inc/ppp_input.h"
#include "PPP/Inc/ppp_atcmd.h"

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_LCP_C

#if(FEATURE_ON == FEATURE_PPP)

/* 保存从NV项中读取的MRU值*/
VOS_UINT16 g_usPppConfigMru = DEF_MRU;

/* for received LQRs */
struct lqrreq {
  struct fsm_opt_hdr hdr;
  VOS_UINT16 proto;        /* Quality protocol */
  VOS_UINT32 period;        /* Reporting interval */
};

VOS_INT32 LcpLayerUp(struct fsm *);
void LcpLayerDown(struct fsm *);
void LcpLayerStart(struct fsm *);
void LcpLayerFinish(struct fsm *);
void LcpInitRestartCounter(struct fsm *, VOS_INT32);
void LcpSendConfigReq(struct fsm *);
void LcpSentTerminateReq(struct fsm *);
void LcpSendTerminateAck(struct fsm *, VOS_CHAR);
void LcpDecodeConfig(struct fsm *, VOS_CHAR *, VOS_CHAR *, VOS_INT32,
                            struct fsm_decode *);

static struct fsm_callbacks lcp_Callbacks = {
  LcpLayerUp,
  LcpLayerDown,
  LcpLayerStart,
  LcpLayerFinish,
  LcpInitRestartCounter,
  LcpSendConfigReq,
  LcpSentTerminateReq,
  LcpSendTerminateAck,
  LcpDecodeConfig,
  fsm_NullRecvResetReq,
  fsm_NullRecvResetAck
};

static const VOS_CHAR * const lcp_TimerNames[] =
  {"LCP restart", "LCP openmode", "LCP stopped"};

#if 0
static const VOS_CHAR *
protoname(VOS_INT32 proto)
{
  static const VOS_CHAR * const cftypes[] = {
    /* Check out the latest ``Assigned numbers'' rfc (1700) */
    VOS_NULL_PTR,
    "MRU",        /* 1: Maximum-Receive-Unit */
    "ACCMAP",        /* 2: Async-Control-Character-Map */
    "AUTHPROTO",    /* 3: Authentication-Protocol */
    "QUALPROTO",    /* 4: Quality-Protocol */
    "MAGICNUM",        /* 5: Magic-Number */
    "RESERVED",        /* 6: RESERVED */
    "PROTOCOMP",    /* 7: Protocol-Field-Compression */
    "ACFCOMP",        /* 8: Address-and-Control-Field-Compression */
    "FCSALT",        /* 9: FCS-Alternatives */
    "SDP",        /* 10: Self-Describing-Pad */
    "NUMMODE",        /* 11: Numbered-Mode */
    "MULTIPROC",    /* 12: Multi-Link-Procedure */
    "CALLBACK",        /* 13: Callback */
    "CONTIME",        /* 14: Connect-Time */
    "COMPFRAME",    /* 15: Compound-Frames */
    "NDE",        /* 16: Nominal-Data-Encapsulation */
    "MRRU",        /* 17: Multilink-MRRU */
    "SHORTSEQ",        /* 18: Multilink-Short-Sequence-Number-Header */
    "ENDDISC",        /* 19: Multilink-Endpoint-Discriminator */
    "PROPRIETRY",    /* 20: Proprietary */
    "DCEID",        /* 21: DCE-Identifier */
    "MULTIPP",        /* 22: Multi-Link-Plus-Procedure */
    "LDBACP",        /* 23: Link Discriminator for BACP */
  };

  if (proto < 0 || proto > sizeof cftypes / sizeof *cftypes ||
      cftypes[proto] == VOS_NULL_PTR)
    return VOS_NULL_PTR/*HexStr(proto, VOS_NULL_PTR, 0)*/;

  return cftypes[proto];
}
#endif



VOS_INT32
lcp_ReportStatus(struct link *l/*struct cmdargs const *arg*/)
{
/*  struct link *l;*/
  struct lcp *lcp;

/*  l = command_ChooseLink(arg);*/
  lcp = &l->lcp;
#if 0/*fanzhibin f49086 delete it*/
  TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "%s: %s [%s]\n"/*, l->name, lcp->fsm.name,
                State2Nam(lcp->fsm.state)*/);
  TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL,
                " his side: MRU %d, ACCMAP %08lx, PROTOCOMP %s, ACFCOMP %s,\n"
                "           MAGIC %08lx, MRRU %u, SHORTSEQ %s, REJECT %04x\n",
                lcp->his_mru, (VOS_UINT32)lcp->his_accmap,
                lcp->his_protocomp ? "on" : "off",
                lcp->his_acfcomp ? "on" : "off",
                (VOS_UINT32)lcp->his_magic, lcp->his_mrru,
                lcp->his_shortseq ? "on" : "off", lcp->his_reject);
  TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL,
                " my  side: MRU %d, ACCMAP %08lx, PROTOCOMP %s, ACFCOMP %s,\n"
                "           MAGIC %08lx, MRRU %u, SHORTSEQ %s, REJECT %04x\n",
                lcp->want_mru, (VOS_UINT32)lcp->want_accmap,
                lcp->want_protocomp ? "on" : "off",
                lcp->want_acfcomp ? "on" : "off",
                (VOS_UINT32)lcp->want_magic, lcp->want_mrru,
                lcp->want_shortseq ? "on" : "off", lcp->my_reject);

  if (lcp->cfg.mru)
    TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "\n Defaults: MRU = %d (max %d), ",
                  lcp->cfg.mru, lcp->cfg.max_mru);
  else
    TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "\n Defaults: MRU = any (max %d), ",
                  lcp->cfg.max_mru);
  if (lcp->cfg.mtu)
    TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "MTU = %d (max %d), ",
                  lcp->cfg.mtu, lcp->cfg.max_mtu);
  else
    TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "MTU = any (max %d), ", lcp->cfg.max_mtu);
  TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "ACCMAP = %08lx\n", (VOS_UINT32)lcp->cfg.accmap);
  TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "           LQR period = %us, ",
                lcp->cfg.lqrperiod);
  TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "Open Mode = %s",
                lcp->cfg.openmode == OPEN_PASSIVE ? "passive" : "active");
  if (lcp->cfg.openmode > 0)
    TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, " (delay %ds)", lcp->cfg.openmode);
  TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "\n           FSM retry = %us, max %u Config"
                " REQ%s, %u Term REQ%s\n", lcp->cfg.fsm.timeout,
                lcp->cfg.fsm.maxreq, lcp->cfg.fsm.maxreq == 1 ? "" : "s",
                lcp->cfg.fsm.maxtrm, lcp->cfg.fsm.maxtrm == 1 ? "" : "s");
  TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "    Ident: %s\n", lcp->cfg.ident);
  TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "\n Negotiation:\n");
  TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "           ACFCOMP =   %s\n",
                command_ShowNegval(lcp->cfg.acfcomp));
  TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "           CHAP =      %s\n",
                command_ShowNegval(lcp->cfg.chap05));
#ifndef NODES
  TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "           CHAP80 =    %s\n",
                command_ShowNegval(lcp->cfg.chap80nt));
  TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "           LANMan =    %s\n",
                command_ShowNegval(lcp->cfg.chap80lm));
  TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "           CHAP81 =    %s\n",
                command_ShowNegval(lcp->cfg.chap81));
#endif
  TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "           LQR =       %s\n",
                command_ShowNegval(lcp->cfg.lqr));
  TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "           PAP =       %s\n",
                command_ShowNegval(lcp->cfg.pap));
  TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "           PROTOCOMP = %s\n",
                command_ShowNegval(lcp->cfg.protocomp));
#endif
  return 0;
}

VOS_UINT32
GenerateMagic(void)
{
  /* Generate random number which will be used as magic number */

  static VOS_UINT32 i = 1345;
  i++;
  return i;
}

void
lcp_SetupCallbacks(struct lcp *lcp)
{
  lcp->fsm.fn = &lcp_Callbacks;
#if 0/*fanzhibin f49086 delete it*/
  lcp->fsm.FsmTimer.name = lcp_TimerNames[0];
  lcp->fsm.OpenTimer.name = lcp_TimerNames[1];
  lcp->fsm.StoppedTimer.name = lcp_TimerNames[2];
#endif
}

void
lcp_Init(struct lcp *lcp, /*struct bundle *bundle, */struct link *l,
         const struct fsm_parent *parent)
{
  /* Initialise ourselves */
  VOS_INT32 mincode = parent ? 1 : LCP_MINMPCODE;

  fsm_Init(&lcp->fsm, "LCP", PROTO_LCP, mincode, LCP_MAXCODE,5 /*LogLCP,
           bundle*/, l, parent, &lcp_Callbacks, lcp_TimerNames);

  lcp->cfg.mru = g_usPppConfigMru;
  lcp->cfg.max_mru = MAX_MRU;
  lcp->cfg.mtu = 0;
  lcp->cfg.max_mtu = MAX_MTU;
  lcp->cfg.accmap = 0;
  lcp->cfg.openmode = 1;
  lcp->cfg.lqrperiod = DEF_LQRPERIOD;
  lcp->cfg.fsm.timeout = DEF_FSMRETRY;
  lcp->cfg.fsm.maxreq = DEF_FSMTRIES;
  lcp->cfg.fsm.maxtrm = DEF_FSMTRIES;

  lcp->cfg.acfcomp = NEG_ENABLED|NEG_ACCEPTED;

/* CDMA模式下只有PC拨号才会用到PPPA,此时只支持PAP不支持CHAP */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
  lcp->cfg.chap05 = 0; /* support CHAP */
#else
  lcp->cfg.chap05 = NEG_ENABLED|NEG_ACCEPTED; /* support CHAP */
#endif

#ifndef NODES
  lcp->cfg.chap80nt = 0/*NEG_ACCEPTED*/;
  lcp->cfg.chap80lm = 0;
  lcp->cfg.chap81 = 0/*NEG_ACCEPTED*/;
#endif
  lcp->cfg.lqr = 0/*NEG_ACCEPTED*/;
  lcp->cfg.pap = NEG_ENABLED|NEG_ACCEPTED/*NEG_ACCEPTED*/;
  lcp->cfg.protocomp = NEG_ENABLED|NEG_ACCEPTED;
  *lcp->cfg.ident = '\0';
  lcp->hLcpCloseTimer = VOS_NULL_PTR;

  lcp_Setup(lcp, lcp->cfg.openmode);
}

/*****************************************************************************
 函 数 名  : lcp_Setup
 功能描述  :
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年8月1日
    作    者   : liukai
    修改内容   : 增加对控制Option MRRU和ShortSeq的全局变量的初始化

*****************************************************************************/
void
lcp_Setup(struct lcp *lcp, VOS_INT32 openmode)
{
/*  struct physical *p = link2physical(lcp->fsm.link);*/

  lcp->fsm.open_mode = openmode;

  lcp->his_mru = DEF_MRU;
  lcp->his_mrru = 0;
  lcp->his_magic = 0;
  lcp->his_lqrperiod = 0;
  lcp->his_acfcomp = 0;
  lcp->his_auth = 0;
  lcp->his_authtype = 0;
  lcp->his_callback.opmask = 0;
  lcp->his_shortseq = 0;
  lcp->mru_req = 0;

  if ((lcp->want_mru = lcp->cfg.mru) == 0){
    lcp->want_mru = DEF_MRU;
  }
  lcp->want_mrru = 0;
  lcp->want_shortseq = 0;
/*  lcp->want_mrru = lcp->fsm.bundle->ncp.mp.cfg.mrru;*/
/*  lcp->want_shortseq = IsEnabled(lcp->fsm.bundle->ncp.mp.cfg.shortseq) ? 1 : 0;*/
  lcp->want_acfcomp = IsEnabled(lcp->cfg.acfcomp) ? 1 : 0;

  if (lcp->fsm.parent) {
    lcp->his_accmap = 0xffffffff;
    lcp->want_accmap = lcp->cfg.accmap;
    lcp->his_protocomp = 0;
    lcp->want_protocomp = IsEnabled(lcp->cfg.protocomp) ? 1 : 0;
    lcp->want_magic = GenerateMagic();

    if (IsEnabled(lcp->cfg.chap05)) {
      lcp->want_auth = PROTO_CHAP;
      lcp->want_authtype = 0x05;
#ifndef NODES
    } else if (IsEnabled(lcp->cfg.chap80nt) ||
               IsEnabled(lcp->cfg.chap80lm)) {
      lcp->want_auth = PROTO_CHAP;
      lcp->want_authtype = 0x80;
    } else if (IsEnabled(lcp->cfg.chap81)) {
      lcp->want_auth = PROTO_CHAP;
      lcp->want_authtype = 0x81;
#endif
    } else if (IsEnabled(lcp->cfg.pap)) {
      lcp->want_auth = PROTO_PAP;
      lcp->want_authtype = 0;
    } else {
      lcp->want_auth = 0;
      lcp->want_authtype = 0;
    }
/*
    if (p->type != PHYS_DIRECT)
      PS_MEM_CPY(&lcp->want_callback, &p->dl->cfg.callback,
             sizeof(struct callback));
    else*/
      lcp->want_callback.opmask = 0;
    lcp->want_lqrperiod = IsEnabled(lcp->cfg.lqr) ?
                          lcp->cfg.lqrperiod * 100 : 0;
  } else {
    lcp->his_accmap = lcp->want_accmap = 0;
    lcp->his_protocomp = lcp->want_protocomp = 1;
    lcp->want_magic = 0;
    lcp->want_auth = 0;
    lcp->want_authtype = 0;
    lcp->want_callback.opmask = 0;
    lcp->want_lqrperiod = 0;
  }

  lcp->his_reject = lcp->my_reject = 0;
  lcp->auth_iwait = lcp->auth_ineed = 0;
  lcp->LcpFailedMagic = 0;
}    /* lcp_Setup */

void
LcpInitRestartCounter(struct fsm *fp, VOS_INT32 what)
{
  /* Set fsm timer load */
  struct lcp *lcp = fsm2lcp(fp);
  PPP_MNTN_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "LcpInitRestartCounter");

/*  fp->FsmTimer.load = lcp->cfg.fsm.timeout * SECTICKS;*/
  switch (what) {
    case FSM_REQ_TIMER:
      fp->restart = lcp->cfg.fsm.maxreq; /* [false alarm]:移植开源代码 */
      break;
    case FSM_TRM_TIMER:
      fp->restart = lcp->cfg.fsm.maxtrm; /* [false alarm]:移植开源代码 */
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
      VOS_StartRelTimer(&(fp->timer),
        PS_PID_APP_PPP,
        PPP_FSM_TIME_INTERVAL,
        PPP_LINK_TO_ID(fp->link),
        fp->link->phase,
        VOS_RELTIMER_NOLOOP,
        VOS_TIMER_PRECISION_0))
  {
        PPP_MNTN_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL,"start reltimer error\r\n");
  }



}

void
LcpSendConfigReq(struct fsm *fp)
{
  /* Send config REQ please */
/*  struct physical *p = link2physical(fp->link);*/
#if 0   /* delete for transplant */
  struct mp *mp;
#endif

  struct lcp *lcp = fsm2lcp(fp);
  VOS_CHAR buff[200];
  struct fsm_opt *o;
  VOS_UINT16 proto;
  VOS_UINT16 maxmru = 0;
/*
  if (!p) {
    log_Printf(LogERROR, "%s: LcpSendConfigReq: Not a physical link !\n",
              fp->link->name);
    return;
  }
*/
  PPP_MNTN_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "LcpSendConfigReq\r\n");
  o = (struct fsm_opt *)buff;
/*
  if (!physical_IsSync(p)) */{
    if (lcp->want_acfcomp && !REJECTED(lcp, TY_ACFCOMP)) /* [false alarm]:移植开源代码 */
      INC_FSM_OPT(TY_ACFCOMP, 2, o);

    if (lcp->want_protocomp && !REJECTED(lcp, TY_PROTOCOMP))
      INC_FSM_OPT(TY_PROTOCOMP, 2, o);

    if (!REJECTED(lcp, TY_ACCMAP)) {

      ua_htonl(&lcp->want_accmap, o->data);
      INC_FSM_OPT(TY_ACCMAP, 6, o);
    }
  }


/*  maxmru = p ? physical_DeviceMTU(p) : 0;*/
  if (lcp->cfg.max_mru && (!maxmru || maxmru > lcp->cfg.max_mru))
    maxmru = lcp->cfg.max_mru;
  if (maxmru && lcp->want_mru > maxmru) {
    PPP_MNTN_LOG2(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "Reducing configured MRU from <1> to <2>\r\n", lcp->want_mru, maxmru);
    lcp->want_mru = maxmru;
  }
  if (!REJECTED(lcp, TY_MRU)) {
    ua_htons(&lcp->want_mru, o->data);
    INC_FSM_OPT(TY_MRU, 4, o);
  }

  if (lcp->want_magic && !REJECTED(lcp, TY_MAGICNUM)) {
    ua_htonl(&lcp->want_magic, o->data);
    INC_FSM_OPT(TY_MAGICNUM, 6, o);
  }

  if (lcp->want_lqrperiod && !REJECTED(lcp, TY_QUALPROTO)) {
    proto = PROTO_LQR;
    ua_htons(&proto, o->data);
    ua_htonl(&lcp->want_lqrperiod, o->data + 2);
    INC_FSM_OPT(TY_QUALPROTO, 8, o);
  }

  switch (lcp->want_auth) {
  case PROTO_PAP:
    proto = PROTO_PAP;
    ua_htons(&proto, o->data);
    INC_FSM_OPT(TY_AUTHPROTO, 4, o);
    break;

  case PROTO_CHAP:
    proto = PROTO_CHAP;
    ua_htons(&proto, o->data);
    o->data[2] = lcp->want_authtype;
    INC_FSM_OPT(TY_AUTHPROTO, 5, o);
    break;
  }

  if (!REJECTED(lcp, TY_CALLBACK)) {
    if (lcp->want_callback.opmask & CALLBACK_BIT(CALLBACK_AUTH)) {
      *o->data = CALLBACK_AUTH;
      INC_FSM_OPT(TY_CALLBACK, 3, o);
    } else if (lcp->want_callback.opmask & CALLBACK_BIT(CALLBACK_CBCP)) {
      *o->data = CALLBACK_CBCP;
      INC_FSM_OPT(TY_CALLBACK, 3, o);
    } else if (lcp->want_callback.opmask & CALLBACK_BIT(CALLBACK_E164)) {
      VOS_INT32 sz = VOS_StrNLen(lcp->want_callback.msg,(SCRIPT_LEN-1));

      if (sz > sizeof o->data - 1) {
        sz = sizeof o->data - 1;
        PPP_MNTN_LOG1(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL,"Truncating E164 data to <1> octets (oops!)\n", sz);
      }
      *o->data = CALLBACK_E164;
      PS_MEM_CPY(o->data + 1, lcp->want_callback.msg, sz);
      INC_FSM_OPT((VOS_UINT8)TY_CALLBACK, (VOS_UINT8)(sz + 3), o);
    }
  }

  if (lcp->want_mrru && !REJECTED(lcp, TY_MRRU)) {
    ua_htons(&lcp->want_mrru, o->data);
    INC_FSM_OPT(TY_MRRU, 4, o);

    if (lcp->want_shortseq && !REJECTED(lcp, TY_SHORTSEQ))
      INC_FSM_OPT(TY_SHORTSEQ, 2, o);
  }
#if 0/*fanzhibin f49086 delete it*/
  mp = &lcp->fsm.bundle->ncp.mp;
  if (mp->cfg.enddisc.class != 0 && IsEnabled(mp->cfg.negenddisc) &&
      !REJECTED(lcp, TY_ENDDISC)) {
    *o->data = mp->cfg.enddisc.class;
    PS_MEM_CPY(o->data+1, mp->cfg.enddisc.address, mp->cfg.enddisc.len);
    INC_FSM_OPT(TY_ENDDISC, mp->cfg.enddisc.len + 3, o);
  }
#endif
  fsm_Output(fp, CODE_CONFIGREQ, fp->reqid, buff, (VOS_CHAR *)o - buff,
             MB_LCPOUT);
}

void
lcp_SendProtoRej(struct lcp *lcp, VOS_CHAR *option, VOS_INT32 count)
{
  /* Don't understand `option' */
  PPP_MNTN_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "lcp_SendProtoRej\r\n");
  fsm_Output(&lcp->fsm, CODE_PROTOREJ, lcp->fsm.reqid, option, count,
             MB_LCPOUT);
}

/*lint -e578 by liukai*/
/*****************************************************************************
 函 数 名  : lcp_SendIdentification
 功能描述  : 向LCP包填写Identification
 输入参数  : lcp - LCP控制结构
 输出参数  : 无
 返 回 值  : 指示是否填写, 未填写 - 0, 填写 - 1
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年5月21日
    作    者   : liukai
    修改内容   : AT2D03379
*****************************************************************************/
VOS_INT32
lcp_SendIdentification(struct lcp *lcp)
{
  static VOS_CHAR id;        /* Use a private id */
  VOS_CHAR msg[DEF_MRU - 3];
  const VOS_CHAR *argv[2];
  VOS_CHAR Outchar = 1;
  VOS_CHAR *exp[2];

  PPP_MNTN_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "lcp_SendIdentification\r\n");
  if (*lcp->cfg.ident == '\0')
    return 0;

  exp[0]  = &Outchar;
  exp[1]  = &Outchar;
  argv[0] = lcp->cfg.ident;
  argv[1] = VOS_NULL_PTR;
#if 0/*fanzhibin f49086 delete it*/
  command_Expand(exp, 1, argv, lcp->fsm.bundle, 1, getpid());
#endif
  ua_htonl(&lcp->want_magic, msg);
  VOS_StrNCpy(msg + 4, exp[0], sizeof msg - 5);
  msg[sizeof msg - 1] = '\0';

  fsm_Output(&lcp->fsm, CODE_IDENT, id++, msg, 4 + VOS_StrNLen(msg + 4,DEF_MRU - 10), MB_LCPOUT);
  PPP_MNTN_LOG1(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, " MAGICNUM <1>\r\n", (VOS_INT32)lcp->want_magic);

#if 0/*fanzhibin f49086 delete it*/
  command_Free(1, exp);
#endif
  return 1;
}
/*lint +e578 by liukai*/

void
lcp_RecvIdentification(struct lcp *lcp, VOS_CHAR *data)
{
  PPP_MNTN_LOG1(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "lcp_RecvIdentification,MAGICNUM:<1>\r\n", (VOS_INT32)lcp->his_magic);
}

void
LcpSentTerminateReq(struct fsm *fp)
{
  PPP_MNTN_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "LcpSentTerminateReq\r\n");
  /* Term REQ just sent by FSM */
}

void
LcpSendTerminateAck(struct fsm *fp, VOS_CHAR id)
{
#if 0/*fanzhibin f49086 delete it*/
  /* Send Term ACK please */
  struct physical *p = link2physical(fp->link);

  if (p && p->dl->state == DATALINK_CBCP)
    cbcp_ReceiveTerminateReq(p);
#endif
  PPP_MNTN_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "LcpSendTerminateAck\r\n");
  fsm_Output(fp, CODE_TERMACK, id, VOS_NULL_PTR, 0, MB_LCPOUT);
}

void
LcpLayerStart(struct fsm *fp)
{
  /* We're about to start up ! */
  struct lcp *lcp = fsm2lcp(fp);

  PPP_MNTN_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "LcpLayerStart");
  lcp->LcpFailedMagic = 0; /* [false alarm]:移植开源代码 */
  fp->more.reqs = fp->more.naks = fp->more.rejs = lcp->cfg.fsm.maxreq * 3;
  lcp->mru_req = 0;
}

void
LcpLayerFinish(struct fsm *fp)
{
  VOS_UINT16 usPppId = PPP_LINK_TO_ID(fp->link);

  /* We're now down */
  PPP_MNTN_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "LcpLayerFinish\r\n");



#if (PPP_FEATURE == PPP_FEATURE_PPP)
  /*通知AT进行PDP去激活*/
  PPP_ProcPppRelEvent(usPppId);

  /* 可维可测信息上报*/
  Ppp_EventMntnInfo(usPppId, AT_PPP_RECV_RELEASE_IND);

#else
  PPPoE_PPPReleaseLink();
#endif

  if (VOS_NULL_PTR != fp->link->lcp.hLcpCloseTimer)
  {
      PS_STOP_REL_TIMER(&(fp->link->lcp.hLcpCloseTimer));
      fp->link->lcp.hLcpCloseTimer = VOS_NULL_PTR;
  }

  /*LCP进入Finish,说明PPP和PC间断开已经完成
    需要通知拉管脚信号*/
  PPP_ProcPppDisconnEvent(usPppId);

  /*然后释放该PPP ID*/
  PppFreeId(usPppId);

  return;

}

VOS_INT32
LcpLayerUp(struct fsm *fp)
{

#if 0/*fanzhibin f49086 delete it*/
  /* We're now up */
  struct physical *p = link2physical(fp->link);
  struct lcp *lcp = fsm2lcp(fp);

  TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "%s: LayerUp\n", fp->link->name);
  physical_SetAsyncParams(p, lcp->want_accmap, lcp->his_accmap);

  lqr_Start(lcp);
  hdlc_StartTimer(&p->hdlc);
#endif

  PPP_MNTN_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "LcpLayerUp\r\n");
  fp->more.reqs = fp->more.naks = fp->more.rejs = fp->link->lcp.cfg.fsm.maxreq * 3;

  lcp_SendIdentification(&(fp->link->lcp));
#if 0
  if((fp->link->timer) != VOS_NULL)
  {
      if(VOS_OK != VOS_StopRelTimer(&(fp->link->timer)));
      {
          TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_WARNING, "Stop timer error!");
      }
      fp->link->timer = VOS_NULL;
  }
#endif
  if(fp->link->lcp.want_auth != 0)
  {
      ipcp_Init(&(fp->link->ipcp), fp->link, &parent);
      fp->link->lcp.auth_ineed = fp->link->lcp.want_auth;
      fp->link->lcp.auth_iwait = fp->link->lcp.his_auth;
      fp->link->phase = PHASE_AUTHENTICATE;
      PPP_MNTN_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "goto auth stage\r\n");

      /* added by liukai */
      if (fp->link->lcp.want_auth == PROTO_CHAP)    /* right now just CHAP needs UE to start authentication */
        auth_StartReq(fp->link);
  }
  else    /* added by liukai */
  {
      fp->link->phase = PHASE_NETWORK;
      fp->link->ipcp.fsm.state = ST_CLOSED;
      fsm_Open(&(fp->link->ipcp.fsm));
  }


  return 1;
}

void
LcpLayerDown(struct fsm *fp)
{
#if 0/*fanzhibin f49086 delete it*/
  /* About to come down */
  struct physical *p = link2physical(fp->link);
#endif


  PPP_MNTN_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "LcpLayerDown\r\n");
#if 0/*fanzhibin f49086 delete it*/
  hdlc_StopTimer(&p->hdlc);
#endif
#if 0/*fanzhibin f49086 delete it*/
  lqr_StopTimer(p);
#endif
  lcp_Setup(fsm2lcp(fp), 0);
}
#if 0
static VOS_INT32
E164ok(struct callback *cb, VOS_CHAR *req, VOS_INT32 sz)
{
  VOS_CHAR list[sizeof cb->msg], *next;
  VOS_INT32 len;

  if (!strcmp(cb->msg, "*"))
    return 1;

  strncpy(list, cb->msg, sizeof list - 1);
  list[sizeof list - 1] = '\0';
  for (next = strtok(list, ","); next; next = strtok(VOS_NULL_PTR, ",")) {
    len = strlen(next);
    if (sz == len && !memcmp(list, req, sz))
      return 1;
  }
  return 0;
}
#endif
VOS_INT32
lcp_auth_nak(struct lcp *lcp, struct fsm_decode *dec)
{
  struct fsm_opt nak;

  nak.hdr.id = TY_AUTHPROTO;

  if (IsAccepted(lcp->cfg.pap)) {
    nak.hdr.len = 4;
    nak.data[0] = (VOS_UCHAR)(PROTO_PAP >> 8);
    nak.data[1] = (VOS_UCHAR)PROTO_PAP;
    fsm_nak(dec, &nak);
    return 1;
  }

  nak.hdr.len = 5;
  nak.data[0] = (VOS_UCHAR)(PROTO_CHAP >> 8);
  nak.data[1] = (VOS_UCHAR)PROTO_CHAP;

  if (IsAccepted(lcp->cfg.chap05)) {
    nak.data[2] = 0x05;
    fsm_nak(dec, &nak);
#ifndef NODES
  } else if (IsAccepted(lcp->cfg.chap80nt) ||
             IsAccepted(lcp->cfg.chap80lm)) {
    nak.data[2] = 0x80;
    fsm_nak(dec, &nak);
  } else if (IsAccepted(lcp->cfg.chap81)) {
    nak.data[2] = 0x81;
    fsm_nak(dec, &nak);
#endif
  } else {
    return 0;
  }

  return 1;
}


void
LcpDecodeConfig(struct fsm *fp, VOS_CHAR *cp, VOS_CHAR *end, VOS_INT32 mode_type,
                struct fsm_decode *dec)
{
  /* Deal with incoming PROTO_LCP */
#if 0/* delete for transplant */
  VOS_UINT16 mru, phmtu, maxmtu = 0, maxmru = 0, wantmtu, wantmru, proto;
  struct mp *mp;
#endif

  struct lcp *lcp = fsm2lcp(fp);
  VOS_INT32 sz, pos, op, callback_req;
  VOS_UINT8 chap_type;
  VOS_UINT32 magic, accmap;
  VOS_UINT16 mru, maxmtu = 0, maxmru = 0, wantmtu, wantmru, proto;
  struct lqrreq *req;
  VOS_CHAR desc[22];

#if 0/*fanzhibin f49086 delete it*/
  struct physical *p = link2physical(fp->link);
#endif

  struct fsm_opt *opt, nak;
  /*VOS_UINT32 auth_requested = 1;*/

  sz = op = callback_req = 0;

  while (end - cp >= sizeof(opt->hdr)) {
    if ((opt = fsm_readopt(&cp)) == VOS_NULL_PTR)
      break;

    /*VOS_nsprintf(request, sizeof request, " %s[%d]", protoname(opt->hdr.id),opt->hdr.len); */

    switch (opt->hdr.id) {
#if 0/*fanzhibin f49086 delete it*/
    case TY_MRRU:
      mp = &lcp->fsm.bundle->ncp.mp;
      ua_ntohs(opt->data, &mru);
      TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "%s %u\n", request, mru);

      switch (mode_type) {
      case MODE_REQ:
        if (mp->cfg.mrru) {
          if (REJECTED(lcp, TY_MRRU))
            /* Ignore his previous reject so that we REQ next time */
            lcp->his_reject &= ~(1 << opt->hdr.id);

          if (mru > MAX_MRU) {
            /* Push him down to MAX_MRU */
            lcp->his_mrru = MAX_MRU;
            nak.hdr.id = TY_MRRU;
            nak.hdr.len = 4;
            ua_htons(&lcp->his_mrru, nak.data);
            fsm_nak(dec, &nak);
          } else if (mru < MIN_MRU) {
            /* Push him up to MIN_MRU */
            lcp->his_mrru = MIN_MRU;
            nak.hdr.id = TY_MRRU;
            nak.hdr.len = 4;
            ua_htons(&lcp->his_mrru, nak.data);
            fsm_nak(dec, &nak);
          } else {
            lcp->his_mrru = mru;
            fsm_ack(dec, opt);
          }
          break;
        } else {
          fsm_rej(dec, opt);
          lcp->my_reject |= (1 << opt->hdr.id);
        }
        break;
      case MODE_NAK:
        if (mp->cfg.mrru) {
          if (REJECTED(lcp, TY_MRRU))
            /* Must have changed his mind ! */
            lcp->his_reject &= ~(1 << opt->hdr.id);

          if (mru > MAX_MRU)
            lcp->want_mrru = MAX_MRU;
          else if (mru < MIN_MRU)
            lcp->want_mrru = MIN_MRU;
          else
            lcp->want_mrru = mru;
        }
        /* else we honour our config and don't send the suggested REQ */
        break;
      case MODE_REJ:
        lcp->his_reject |= (1 << opt->hdr.id);
        lcp->want_mrru = 0;        /* Ah well, no multilink :-( */
        break;
      }
      break;
#endif
    case TY_MRU:
      lcp->mru_req = 1; /* [false alarm]:移植开源代码 */
      ua_ntohs(opt->data, &mru);
      PPP_MNTN_LOG1(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL,"mru= <1>\r\n", mru);

      switch (mode_type) {
      case MODE_REQ:
#if 0/*fanzhibin f49086 delete it*/
        maxmtu = p ? physical_DeviceMTU(p) : 0;
#endif
        if (lcp->cfg.max_mtu && (!maxmtu || maxmtu > lcp->cfg.max_mtu))
          maxmtu = lcp->cfg.max_mtu;
        wantmtu = lcp->cfg.mtu;
        if (maxmtu && wantmtu > maxmtu) {
          PPP_MNTN_LOG2(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL,
                        "Reducing configured MTU from <1> to <2>\r\n", wantmtu, maxmtu);
          wantmtu = maxmtu;
        }

        if (maxmtu && mru > maxmtu) {
          lcp->his_mru = maxmtu;
          nak.hdr.id = TY_MRU;
          nak.hdr.len = 4;
          ua_htons(&lcp->his_mru, nak.data);
          fsm_nak(dec, &nak);
        } else if (wantmtu && mru < wantmtu) {
          /* Push him up to MTU or MIN_MRU */
          lcp->his_mru = wantmtu;
          nak.hdr.id = TY_MRU;
          nak.hdr.len = 4;
          ua_htons(&lcp->his_mru, nak.data);
          fsm_nak(dec, &nak);
        } else {
          lcp->his_mru = mru;
          fsm_ack(dec, opt);
        }
        break;
      case MODE_NAK:
 #if 0/*fanzhibin f49086 delete it*/
        maxmru = p ? physical_DeviceMTU(p) : 0;
#endif

        if (lcp->cfg.max_mru && (!maxmru || maxmru > lcp->cfg.max_mru))
          maxmru = lcp->cfg.max_mru;
        wantmru = lcp->cfg.mru > maxmru ? maxmru : lcp->cfg.mru;

        if (wantmru && mru > wantmru)
          lcp->want_mru = wantmru;
        else if (mru > maxmru)
          lcp->want_mru = maxmru;
        else if (mru < MIN_MRU)
          lcp->want_mru = MIN_MRU;
        else
          lcp->want_mru = mru;
        break;
      case MODE_REJ:
        lcp->his_reject |= (1 << opt->hdr.id);
        break;
      }
      break;

    case TY_ACCMAP:
      ua_ntohl(opt->data, &accmap);
      PPP_MNTN_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "want accmap\r\n");

      switch (mode_type) {
      case MODE_REQ:
        lcp->his_accmap = accmap; /* [false alarm]:移植开源代码 */
        fsm_ack(dec, opt);
        break;
      case MODE_NAK:
        lcp->want_accmap = accmap; /* [false alarm]:移植开源代码 */
        break;
      case MODE_REJ:
        lcp->his_reject |= (1 << opt->hdr.id); /* [false alarm]:移植开源代码 */
        break;
      }
      break;

    case TY_AUTHPROTO:
      ua_ntohs(opt->data, &proto);
      chap_type = opt->hdr.len == 5 ? opt->data[2] : 0;

      PPP_MNTN_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "want auth\r\n");

      switch (mode_type) {
      case MODE_REQ:
        /*auth_requested = 0;*/
        switch (proto) {
        case PROTO_PAP:
          if (opt->hdr.len == 4 && IsAccepted(lcp->cfg.pap)) { /* [false alarm]:移植开源代码 */
            lcp->his_auth = proto;
            lcp->his_authtype = 0;
            fsm_ack(dec, opt);
          } else if (!lcp_auth_nak(lcp, dec)) {
            lcp->my_reject |= (1 << opt->hdr.id); /* [false alarm]:移植开源代码 */
            fsm_rej(dec, opt);
          }
          break;

        case PROTO_CHAP:
          if ((chap_type == 0x05 && IsAccepted(lcp->cfg.chap05))    /* chap_type: 0x05, use MD5 *//* [false alarm]:移植开源代码 */
#ifndef NODES
              || (chap_type == 0x80 && (IsAccepted(lcp->cfg.chap80nt) || /* [false alarm]:移植开源代码 */
                                   (IsAccepted(lcp->cfg.chap80lm))))
              || (chap_type == 0x81 && IsAccepted(lcp->cfg.chap81)) /* [false alarm]:移植开源代码 */
#endif
             ) {
            lcp->his_auth = proto;
            lcp->his_authtype = chap_type;
            fsm_ack(dec, opt);
          } else {
#ifdef NODES
            if (chap_type == 0x80) {
              PPP_MNTN_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_WARNING, "CHAP 0x80 not available without DES\r\n");
            } else if (chap_type == 0x81) {
              PPP_MNTN_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_WARNING, "CHAP 0x81 not available without DES\r\n");
            } else
#endif
            if (chap_type != 0x05)
              PPP_MNTN_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_WARNING, "%s not supported\r\n"/*,
                         Auth2Nam(PROTO_CHAP, chap_type)*/);

            if (!lcp_auth_nak(lcp, dec)) {
              lcp->my_reject |= (1 << opt->hdr.id); /* [false alarm]:移植开源代码 */
              fsm_rej(dec, opt);
            }
          }
          break;

        default:
          PPP_MNTN_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "not recognised\r\n");
          if (!lcp_auth_nak(lcp, dec)) {
            lcp->my_reject |= (1 << opt->hdr.id); /* [false alarm]:移植开源代码 */
            fsm_rej(dec, opt);
          }
          break;
        }
        break;

      case MODE_NAK:
        switch (proto) {
        case PROTO_PAP:
          if (IsEnabled(lcp->cfg.pap)) { /* [false alarm]:移植开源代码 */
            lcp->want_auth = PROTO_PAP;
            lcp->want_authtype = 0;
          } else {
            PPP_MNTN_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "Peer will only send PAP (not enabled)\r\n");
            lcp->his_reject |= (1 << opt->hdr.id);
          }
          break;
        case PROTO_CHAP:
          if (chap_type == 0x05 && IsEnabled(lcp->cfg.chap05)) { /* [false alarm]:移植开源代码 */
            lcp->want_auth = PROTO_CHAP;
            lcp->want_authtype = 0x05;
#ifndef NODES
          } else if (chap_type == 0x80 && (IsEnabled(lcp->cfg.chap80nt) ||  /* [false alarm]:移植开源代码 */
                                           IsEnabled(lcp->cfg.chap80lm))) {
            lcp->want_auth = PROTO_CHAP;
            lcp->want_authtype = 0x80;
          } else if (chap_type == 0x81 && IsEnabled(lcp->cfg.chap81)) { /* [false alarm]:移植开源代码 */
            lcp->want_auth = PROTO_CHAP;
            lcp->want_authtype = 0x81;
#endif
          } else {
#ifdef NODES
            if (chap_type == 0x80) {
              PPP_MNTN_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "Peer will only send MSCHAP\r\n");
            } else if (chap_type == 0x81) {
              PPP_MNTN_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "Peer will only send MSCHAPV2\r\n");
            } else
#endif
            PPP_MNTN_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "Peer will only send\r\n");
            lcp->his_reject |= (1 << opt->hdr.id); /* [false alarm]:移植开源代码 */
	     /*如果支持CHAP,但CHAP的算法UE不支持,则改为使用PAP验证*/
	     lcp->want_auth = PROTO_PAP;
            lcp->want_authtype = 0;

          }
          break;
        default:
          /* We've been NAK'd with something we don't understand :-( */
          lcp->his_reject |= (1 << opt->hdr.id); /* [false alarm]:移植开源代码 */
          break;
        }
        break;

      case MODE_REJ:
        lcp->his_reject |= (1 << opt->hdr.id); /* [false alarm]:移植开源代码 */
        PPP_MNTN_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "Peer will not auth by our way\r\n");
        lcp->want_auth = 0;
        break;
      }
      break;

    case TY_QUALPROTO:
      req = (struct lqrreq *)opt;
      PPP_MNTN_LOG2(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL,
                    "proto <1>;interval <2>\r\n",
                    (VOS_INT32)VOS_NTOHS(req->proto), (VOS_INT32)(VOS_NTOHL(req->period) * 10));
      switch (mode_type) {
      case MODE_REQ:
        if (VOS_NTOHS(req->proto) != PROTO_LQR || !IsAccepted(lcp->cfg.lqr)) { /* [false alarm]:移植开源代码 */
          fsm_rej(dec, opt);
          lcp->my_reject |= (1 << opt->hdr.id); /* [false alarm]:移植开源代码 */
        } else {
          lcp->his_lqrperiod = VOS_NTOHL(req->period);
          if (lcp->his_lqrperiod < MIN_LQRPERIOD * 100)
            lcp->his_lqrperiod = MIN_LQRPERIOD * 100;
          req->period = VOS_HTONL(lcp->his_lqrperiod);
          fsm_ack(dec, opt);
        }
        break;
      case MODE_NAK:
        lcp->want_lqrperiod = VOS_NTOHL(req->period); /* [false alarm]:移植开源代码 */
        break;
      case MODE_REJ:
        lcp->his_reject |= (1 << opt->hdr.id); /* [false alarm]:移植开源代码 */
        break;
      }
      break;

    case TY_MAGICNUM:
      ua_ntohl(opt->data, &magic);
      PPP_MNTN_LOG1(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "magic number <1>\r\n", (VOS_INT32)magic);

      switch (mode_type) {
      case MODE_REQ:
        if (lcp->want_magic) { /* [false alarm]:移植开源代码 */
          /* Validate magic number */
          if (magic == lcp->want_magic) {

#if 0/*fanzhibin f49086 delete it*/
            sigset_t emptyset;
#endif
            PPP_MNTN_LOG2(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL,"Magic is same <1> <2>\r\n", (VOS_INT32)magic, ++lcp->LcpFailedMagic);
            lcp->want_magic = GenerateMagic();
            fsm_nak(dec, opt);

#if 0/*fanzhibin f49086 delete it*/
            ualarm(TICKUNIT * (4 + 4 * lcp->LcpFailedMagic), 0);
            sigemptyset(&emptyset);
            sigsuspend(&emptyset);
#endif

          } else {
            lcp->his_magic = magic;
            lcp->LcpFailedMagic = 0;
            fsm_ack(dec, opt);
          }
        } else {
          lcp->my_reject |= (1 << opt->hdr.id);
          fsm_rej(dec, opt);
        }
        break;
      case MODE_NAK:
        PPP_MNTN_LOG1(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, " Magic <1> is NAKed!\r\n", (VOS_INT32)magic);
        lcp->want_magic = GenerateMagic(); /* [false alarm]:移植开源代码 */
        break;
      case MODE_REJ:
        PPP_MNTN_LOG1(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, " Magic <1> is REJected!\r\n", (VOS_INT32)magic);
        lcp->want_magic = 0; /* [false alarm]:移植开源代码 */
        lcp->his_reject |= (1 << opt->hdr.id);
        break;
      }
      break;

    case TY_PROTOCOMP:
      PPP_MNTN_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "proto compress\r\n");

      switch (mode_type) {
      case MODE_REQ:
        if (IsAccepted(lcp->cfg.protocomp)) { /* [false alarm]:移植开源代码 */
          lcp->his_protocomp = 1;
          fsm_ack(dec, opt);
        } else {
#ifdef OLDMST
          /* MorningStar before v1.3 needs NAK */
          fsm_nak(dec, opt);
#else
          fsm_rej(dec, opt);
          lcp->my_reject |= (1 << opt->hdr.id);
#endif
        }
        break;
      case MODE_NAK:
      case MODE_REJ:
        lcp->want_protocomp = 0; /* [false alarm]:移植开源代码 */
        lcp->his_reject |= (1 << opt->hdr.id);
        break;
      }
      break;

    case TY_ACFCOMP:
      PPP_MNTN_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "acf compress\r\n");
      switch (mode_type) {
      case MODE_REQ:
        if (IsAccepted(lcp->cfg.acfcomp)) { /* [false alarm]:移植开源代码 */
          lcp->his_acfcomp = 1;
          fsm_ack(dec, opt);
        } else {
#ifdef OLDMST
          /* MorningStar before v1.3 needs NAK */
          fsm_nak(dec, opt);
#else
          fsm_rej(dec, opt);
          lcp->my_reject |= (1 << opt->hdr.id);
#endif
        }
        break;
      case MODE_NAK:
      case MODE_REJ:
        lcp->want_acfcomp = 0; /* [false alarm]:移植开源代码 */
        lcp->his_reject |= (1 << opt->hdr.id);
        break;
      }
      break;

    case TY_SDP:
      PPP_MNTN_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "sdp\r\n");
      switch (mode_type) {
      case MODE_REQ:
      case MODE_NAK:
      case MODE_REJ:
        break;
      }
      break;
#if 0/*fanzhibin f49086 delete it*/
    case TY_CALLBACK:
      if (opt->hdr.len == 2)
        op = CALLBACK_NONE;
      else
        op = (VOS_INT32)opt->data[0];
      sz = opt->hdr.len - 3;
      switch (op) {
        case CALLBACK_AUTH:
          TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "%s Auth\n", request);
          break;
        case CALLBACK_DIALSTRING:
          TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "%s Dialstring %.*s\n", request, sz,
                     opt->data + 1);
          break;
        case CALLBACK_LOCATION:
          TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "%s Location %.*s\n", request, sz, opt->data + 1);
          break;
        case CALLBACK_E164:
          TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "%s E.164 (%.*s)\n", request, sz, opt->data + 1);
          break;
        case CALLBACK_NAME:
          TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "%s Name %.*s\n", request, sz, opt->data + 1);
          break;
        case CALLBACK_CBCP:
          TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "%s CBCP\n", request);
          break;
        default:
          TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "%s \?\?\?\n", request);
          break;
      }

      switch (mode_type) {
      case MODE_REQ:
        callback_req = 1;
        if (p->type != PHYS_DIRECT) {
          fsm_rej(dec, opt);
          lcp->my_reject |= (1 << opt->hdr.id);
        }
        nak.hdr.id = opt->hdr.id;
        nak.hdr.len = 3;
        if ((p->dl->cfg.callback.opmask & CALLBACK_BIT(op)) &&
            (op != CALLBACK_AUTH || p->link.lcp.want_auth) &&
            (op != CALLBACK_E164 ||
             E164ok(&p->dl->cfg.callback, opt->data + 1, sz))) {
          lcp->his_callback.opmask = CALLBACK_BIT(op);
          if (sz > sizeof lcp->his_callback.msg - 1) {
            sz = sizeof lcp->his_callback.msg - 1;
            TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_WARNING, "Truncating option arg to %d octets\n", sz);
          }
          PS_MEM_CPY(lcp->his_callback.msg, opt->data + 1, sz);
          lcp->his_callback.msg[sz] = '\0';
          fsm_ack(dec, opt);
        } else if ((p->dl->cfg.callback.opmask & CALLBACK_BIT(CALLBACK_AUTH)) &&
                    p->link.lcp.auth_ineed) {
          nak.data[0] = CALLBACK_AUTH;
          fsm_nak(dec, &nak);
        } else if (p->dl->cfg.callback.opmask & CALLBACK_BIT(CALLBACK_CBCP)) {
          nak.data[0] = CALLBACK_CBCP;
          fsm_nak(dec, &nak);
        } else if (p->dl->cfg.callback.opmask & CALLBACK_BIT(CALLBACK_E164)) {
          nak.data[0] = CALLBACK_E164;
          fsm_nak(dec, &nak);
        } else if (p->dl->cfg.callback.opmask & CALLBACK_BIT(CALLBACK_AUTH)) {
          TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_WARNING, "Cannot insist on auth callback without"
                     " PAP or CHAP enabled !\n");
          nak.data[0] = 2;
          fsm_nak(dec, &nak);
        } else {
          lcp->my_reject |= (1 << opt->hdr.id);
          fsm_rej(dec, opt);
        }
        break;
      case MODE_NAK:
        /* We don't do what he NAKs with, we do things in our preferred order */
        if (lcp->want_callback.opmask & CALLBACK_BIT(CALLBACK_AUTH))
          lcp->want_callback.opmask &= ~CALLBACK_BIT(CALLBACK_AUTH);
        else if (lcp->want_callback.opmask & CALLBACK_BIT(CALLBACK_CBCP))
          lcp->want_callback.opmask &= ~CALLBACK_BIT(CALLBACK_CBCP);
        else if (lcp->want_callback.opmask & CALLBACK_BIT(CALLBACK_E164))
          lcp->want_callback.opmask &= ~CALLBACK_BIT(CALLBACK_E164);
        if (lcp->want_callback.opmask == CALLBACK_BIT(CALLBACK_NONE)) {
          TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "Peer NAKd all callbacks, trying none\n");
          lcp->want_callback.opmask = 0;
        } else if (!lcp->want_callback.opmask) {
          TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "Peer NAKd last configured callback\n");
          fsm_Close(&lcp->fsm);
        }
        break;
      case MODE_REJ:
        if (lcp->want_callback.opmask & CALLBACK_BIT(CALLBACK_NONE)) {
          lcp->his_reject |= (1 << opt->hdr.id);
          lcp->want_callback.opmask = 0;
        } else {
          TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "Peer rejected *required* callback\n");
          fsm_Close(&lcp->fsm);
        }
        break;
      }
      break;

    case TY_SHORTSEQ:
      mp = &lcp->fsm.bundle->ncp.mp;
      TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "%s\n", request);

      switch (mode_type) {
      case MODE_REQ:
        if (lcp->want_mrru && IsAccepted(mp->cfg.shortseq)) {
          lcp->his_shortseq = 1;
          fsm_ack(dec, opt);
        } else {
          fsm_rej(dec, opt);
          lcp->my_reject |= (1 << opt->hdr.id);
        }
        break;
      case MODE_NAK:
        /*
         * He's trying to get us to ask for VOS_INT16 sequence numbers.
         * We ignore the NAK and honour our configuration file instead.
         */
        break;
      case MODE_REJ:
        lcp->his_reject |= (1 << opt->hdr.id);
        lcp->want_shortseq = 0;        /* For when we hit MP */
        break;
      }
      break;

    case TY_ENDDISC:
      mp = &lcp->fsm.bundle->ncp.mp;
      TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "%s %s\n", request,
                 mp_Enddisc(opt->data[0], opt->data + 1, opt->hdr.len - 3));
      switch (mode_type) {
      case MODE_REQ:
        if (!p) {
          TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, " ENDDISC rejected - not a physical link\n");
          fsm_rej(dec, opt);
          lcp->my_reject |= (1 << opt->hdr.id);
        } else if (!IsAccepted(mp->cfg.negenddisc)) {
          lcp->my_reject |= (1 << opt->hdr.id);
          fsm_rej(dec, opt);
        } else if (opt->hdr.len - 3 < sizeof p->dl->peer.enddisc.address &&
                   opt->data[0] <= MAX_ENDDISC_CLASS) {
          p->dl->peer.enddisc.class = opt->data[0];
          p->dl->peer.enddisc.len = opt->hdr.len - 3;
          PS_MEM_CPY(p->dl->peer.enddisc.address, opt->data + 1, opt->hdr.len - 3);
          p->dl->peer.enddisc.address[opt->hdr.len - 3] = '\0';
          /* XXX: If mp->active, compare and NAK with mp->peer ? */
          fsm_ack(dec, opt);
        } else {
          if (opt->data[0] > MAX_ENDDISC_CLASS)
            TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL," ENDDISC rejected - unrecognised class %d\n",
                      opt->data[0]);
          else
            TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, " ENDDISC rejected - local max length is %ld\n",
                      (long)(sizeof p->dl->peer.enddisc.address - 1));
          fsm_rej(dec, opt);
          lcp->my_reject |= (1 << opt->hdr.id);
        }
        break;

      case MODE_NAK:    /* Treat this as a REJ, we don't vary our disc (yet) */
      case MODE_REJ:
        lcp->his_reject |= (1 << opt->hdr.id);
        break;
      }
      break;
#endif
    default:
      sz = (sizeof desc - 2) / 2;
      if (sz > opt->hdr.len - 2)
        sz = opt->hdr.len - 2;
      pos = 0;
      desc[0] = sz ? ' ' : '\0';
      for (pos = 0; sz--; pos++)
        sprintf(desc+(pos<<1)+1, "%02x", opt->data[pos]);

      PPP_MNTN_LOG1(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "unknow option code %d\r\n",opt->hdr.id);

      if (mode_type == MODE_REQ) {
        fsm_rej(dec, opt);
        lcp->my_reject |= (1 << opt->hdr.id); /* [false alarm]:移植开源代码 */
      }
      break;
    }
  }

  if (mode_type != MODE_NOP) {
#if 0/*fanzhibin f49086 delete it*/
    if (mode_type == MODE_REQ && p && p->type == PHYS_DIRECT &&
        p->dl->cfg.callback.opmask && !callback_req &&
        !(p->dl->cfg.callback.opmask & CALLBACK_BIT(CALLBACK_NONE))) {
      /* We *REQUIRE* that the peer requests callback */
      nak.hdr.id = TY_CALLBACK;
      nak.hdr.len = 3;
      if ((p->dl->cfg.callback.opmask & CALLBACK_BIT(CALLBACK_AUTH)) &&
          p->link.lcp.want_auth)
        nak.data[0] = CALLBACK_AUTH;
      else if (p->dl->cfg.callback.opmask & CALLBACK_BIT(CALLBACK_CBCP))
        nak.data[0] = CALLBACK_CBCP;
      else if (p->dl->cfg.callback.opmask & CALLBACK_BIT(CALLBACK_E164))
        nak.data[0] = CALLBACK_E164;
      else {
        TTF_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_WARNING, "Cannot insist on auth callback without"
                   " PAP or CHAP enabled !\n");
        nak.hdr.len = 2;    /* XXX: Silly ! */
      }
      fsm_nak(dec, &nak);
    }
#endif

#if 0
  if (mode_type == MODE_REQ
      && IsAccepted(lcp->cfg.pap)
      && auth_requested)
      {
          nak.hdr.id = TY_AUTHPROTO;
          nak.hdr.len = 4;
          nak.data[0] = (PROTO_PAP>>8) &0xff;
          nak.data[1] = PROTO_PAP &0xff;
          fsm_nak(dec, &nak);

          TTF_LOG2(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "must be pap",nak.data[0],nak.data[1]);
      }
 #endif

    if (mode_type == MODE_REQ && !lcp->mru_req) { /* [false alarm]:移植开源代码 */
      mru = DEF_MRU;
#if 0/*fanzhibin f49086 delete it*/
      phmtu = p ? physical_DeviceMTU(p) : 0;
      if (phmtu && mru > phmtu)
        mru = phmtu;
      if (mru > lcp->cfg.max_mtu)
        mru = lcp->cfg.max_mtu;
#endif
      if (mru < DEF_MRU) {
        /* Don't let the peer use the default MRU */
        lcp->his_mru = lcp->cfg.mtu && lcp->cfg.mtu < mru ? lcp->cfg.mtu : mru;
        nak.hdr.id = TY_MRU;
        nak.hdr.len = 4;
        ua_htons(&lcp->his_mru, nak.data);
        fsm_nak(dec, &nak);
        lcp->mru_req = 1;    /* Don't keep NAK'ing this */
      }
    }
    fsm_opt_normalise(dec);
  }
}

extern PPP_ZC_STRU *
lcp_Input(/*struct bundle *bundle, */struct link *l, PPP_ZC_STRU *pstMem)
{
  struct ppp_mbuf *bp;


  bp = ppp_m_get_from_ttfmem(pstMem);

  PPP_MemFree(pstMem);

  if (VOS_NULL_PTR == bp)
  {
    return VOS_NULL_PTR;
  }

  /* Got PROTO_LCP from link */
  PPP_MNTN_LOG(PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_NORMAL, "lcp_Input\r\n");
  fsm_Input(&l->lcp.fsm, bp);
  return VOS_NULL_PTR;
}

#endif /* #if(FEATURE_ON == FEATURE_PPP) */

