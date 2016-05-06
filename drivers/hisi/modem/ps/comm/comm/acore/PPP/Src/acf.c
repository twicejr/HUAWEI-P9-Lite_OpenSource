/*-
 * Copyright (c) 1999 Brian Somers <brian@Awfulhak.org>
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
 * $FreeBSD: src/usr.sbin/ppp/acf.c,v 1.5 2000/07/19 02:10:30 brian Exp $
 */


#include "PppInterface.h"
#include "PPP/Inc/ppp_public.h"
#include "PPP/Inc/layer.h"
#include "PPP/Inc/ppp_fsm.h"
#include "PPP/Inc/ppp_mbuf.h"
#include "PPP/Inc/acf.h"
#include "PPP/Inc/proto.h"
#include "PPP/Inc/throughput.h"
#include "PPP/Inc/hdlc.h"
#include "PPP/Inc/lcp.h"
#include "PPP/Inc/async.h"
#include "PPP/Inc/auth.h"
#include "PPP/Inc/ipcp.h"
#include "PPP/Inc/pppid.h"
#include "PPP/Inc/link.h"

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767  修改人: z57034; 检视人: g45205 原因简述: 打点日志文件宏ID定义 */
#define    THIS_FILE_ID        PS_FILE_ID_ACF_C
/*lint +e767  修改人: z57034; 检视人: g45205 */


#if(FEATURE_ON == FEATURE_PPP)

VOS_INT32
acf_WrapperOctets(struct lcp *lcp, VOS_UINT16 proto)
{
  return ( (proto == PROTO_LCP) || (lcp->his_acfcomp == 0)) ? 2 : 0;
}

struct ppp_mbuf *
acf_LayerPush(/*struct bundle *b, */struct link *l, struct ppp_mbuf *bp,
              VOS_INT32 pri, VOS_UINT16 *proto)
{
  const VOS_UCHAR cp[2] = { HDLC_ADDR, HDLC_UI };

  if ( (*proto == PROTO_LCP) || (l->lcp.his_acfcomp == 0) ) {
    bp = ppp_m_prepend(bp, cp, 2, 0);
  }

  return bp;
}

PPP_ZC_STRU *acf_LayerPull(/*struct bundle *b, */struct link *l, PPP_ZC_STRU *pstMem, VOS_UINT16 *pusProto)
{
    VOS_UINT32  ulRst;
    VOS_UCHAR   cp[2] = {0, 0};


    ulRst = PPP_MemGet(pstMem, 0, cp, 2);

    if (PS_SUCC == ulRst)
    {
        if (!l->lcp.want_acfcomp)
        {
            /* We expect the packet not to be compressed */
            PPP_MemCutHeadData(&pstMem, cp, 2);

            if (cp[0] != HDLC_ADDR)
            {
                l->hdlc.lqm.SaveInErrors++;
                l->hdlc.stats.badaddr++;
                PPP_MNTN_LOG1(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "acf_LayerPull: addr:%c ", cp[0]);
                PPP_MemFree(pstMem);

                return VOS_NULL_PTR;
            }

            if (cp[1] != HDLC_UI)
            {
                l->hdlc.lqm.SaveInErrors++;
                l->hdlc.stats.badcommand++;
                PPP_MNTN_LOG1(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "acf_LayerPull: control :%d", cp[1]);
                PPP_MemFree(pstMem);

                return VOS_NULL_PTR;
            }
        }
        else if ( (cp[0] == HDLC_ADDR) && (cp[1] == HDLC_UI) )
        {
            /*
            * We can receive compressed packets, but the peer still sends
            * uncompressed packets (or maybe this is a PROTO_LCP packet) !
            */
            PPP_MemCutHeadData(&pstMem, cp, 2);
        }
        else
        {
            ;
        }
    }

    return pstMem;
} /* acf_LayerPull */


struct layer acflayer = { LAYER_ACF, "acf", acf_LayerPush, acf_LayerPull };

#endif /* #if(FEATURE_ON == FEATURE_PPP) */

