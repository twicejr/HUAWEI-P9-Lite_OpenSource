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
 * $FreeBSD: src/usr.sbin/ppp/hdlc.c,v 1.49 2002/08/27 20:11:57 brian Exp $
 */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#include "PPP/Inc/ppp_public.h"
#include "PPP/Inc/layer.h"
#include "PPP/Inc/ppp_mbuf.h"
#include "PPP/Inc/ppp_fsm.h"
#include "PPP/Inc/hdlc.h"
#include "PPP/Inc/throughput.h"
#include "PPP/Inc/lcp.h"
#include "PPP/Inc/async.h"
#include "PPP/Inc/auth.h"
#include "PPP/Inc/ipcp.h"
#include "PPP/Inc/pppid.h"
#include "PPP/Inc/link.h"

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_HDLC_C

#if(FEATURE_ON == FEATURE_PPP)

VOS_UINT16 const fcstab[256] = {
   /* 00 */ 0x0000, 0x1189, 0x2312, 0x329b, 0x4624, 0x57ad, 0x6536, 0x74bf,
   /* 08 */ 0x8c48, 0x9dc1, 0xaf5a, 0xbed3, 0xca6c, 0xdbe5, 0xe97e, 0xf8f7,
   /* 10 */ 0x1081, 0x0108, 0x3393, 0x221a, 0x56a5, 0x472c, 0x75b7, 0x643e,
   /* 18 */ 0x9cc9, 0x8d40, 0xbfdb, 0xae52, 0xdaed, 0xcb64, 0xf9ff, 0xe876,
   /* 20 */ 0x2102, 0x308b, 0x0210, 0x1399, 0x6726, 0x76af, 0x4434, 0x55bd,
   /* 28 */ 0xad4a, 0xbcc3, 0x8e58, 0x9fd1, 0xeb6e, 0xfae7, 0xc87c, 0xd9f5,
   /* 30 */ 0x3183, 0x200a, 0x1291, 0x0318, 0x77a7, 0x662e, 0x54b5, 0x453c,
   /* 38 */ 0xbdcb, 0xac42, 0x9ed9, 0x8f50, 0xfbef, 0xea66, 0xd8fd, 0xc974,
   /* 40 */ 0x4204, 0x538d, 0x6116, 0x709f, 0x0420, 0x15a9, 0x2732, 0x36bb,
   /* 48 */ 0xce4c, 0xdfc5, 0xed5e, 0xfcd7, 0x8868, 0x99e1, 0xab7a, 0xbaf3,
   /* 50 */ 0x5285, 0x430c, 0x7197, 0x601e, 0x14a1, 0x0528, 0x37b3, 0x263a,
   /* 58 */ 0xdecd, 0xcf44, 0xfddf, 0xec56, 0x98e9, 0x8960, 0xbbfb, 0xaa72,
   /* 60 */ 0x6306, 0x728f, 0x4014, 0x519d, 0x2522, 0x34ab, 0x0630, 0x17b9,
   /* 68 */ 0xef4e, 0xfec7, 0xcc5c, 0xddd5, 0xa96a, 0xb8e3, 0x8a78, 0x9bf1,
   /* 70 */ 0x7387, 0x620e, 0x5095, 0x411c, 0x35a3, 0x242a, 0x16b1, 0x0738,
   /* 78 */ 0xffcf, 0xee46, 0xdcdd, 0xcd54, 0xb9eb, 0xa862, 0x9af9, 0x8b70,
   /* 80 */ 0x8408, 0x9581, 0xa71a, 0xb693, 0xc22c, 0xd3a5, 0xe13e, 0xf0b7,
   /* 88 */ 0x0840, 0x19c9, 0x2b52, 0x3adb, 0x4e64, 0x5fed, 0x6d76, 0x7cff,
   /* 90 */ 0x9489, 0x8500, 0xb79b, 0xa612, 0xd2ad, 0xc324, 0xf1bf, 0xe036,
   /* 98 */ 0x18c1, 0x0948, 0x3bd3, 0x2a5a, 0x5ee5, 0x4f6c, 0x7df7, 0x6c7e,
   /* a0 */ 0xa50a, 0xb483, 0x8618, 0x9791, 0xe32e, 0xf2a7, 0xc03c, 0xd1b5,
   /* a8 */ 0x2942, 0x38cb, 0x0a50, 0x1bd9, 0x6f66, 0x7eef, 0x4c74, 0x5dfd,
   /* b0 */ 0xb58b, 0xa402, 0x9699, 0x8710, 0xf3af, 0xe226, 0xd0bd, 0xc134,
   /* b8 */ 0x39c3, 0x284a, 0x1ad1, 0x0b58, 0x7fe7, 0x6e6e, 0x5cf5, 0x4d7c,
   /* c0 */ 0xc60c, 0xd785, 0xe51e, 0xf497, 0x8028, 0x91a1, 0xa33a, 0xb2b3,
   /* c8 */ 0x4a44, 0x5bcd, 0x6956, 0x78df, 0x0c60, 0x1de9, 0x2f72, 0x3efb,
   /* d0 */ 0xd68d, 0xc704, 0xf59f, 0xe416, 0x90a9, 0x8120, 0xb3bb, 0xa232,
   /* d8 */ 0x5ac5, 0x4b4c, 0x79d7, 0x685e, 0x1ce1, 0x0d68, 0x3ff3, 0x2e7a,
   /* e0 */ 0xe70e, 0xf687, 0xc41c, 0xd595, 0xa12a, 0xb0a3, 0x8238, 0x93b1,
   /* e8 */ 0x6b46, 0x7acf, 0x4854, 0x59dd, 0x2d62, 0x3ceb, 0x0e70, 0x1ff9,
   /* f0 */ 0xf78f, 0xe606, 0xd49d, 0xc514, 0xb1ab, 0xa022, 0x92b9, 0x8330,
   /* f8 */ 0x7bc7, 0x6a4e, 0x58d5, 0x495c, 0x3de3, 0x2c6a, 0x1ef1, 0x0f78
};

void
hdlc_Init(struct hdlc *hdlc, struct lcp *lcp)
{
  PS_MEM_SET(hdlc, '\0', sizeof(struct hdlc));
  hdlc->lqm.owner = lcp;
}

/*
 *  HDLC FCS computation. Read RFC 1171 Appendix B and CCITT X.25 section
 *  2.27 for further details.
 */
VOS_UINT16
hdlc_Fcs(VOS_CHAR *cp, VOS_UINT32 len)
{
  VOS_UINT16 fcs = INITFCS;

  while (len--)
    fcs = (fcs >> 8) ^ fcstab[(fcs ^ *cp++) & 0xff];

  return fcs;
}

VOS_UINT16
HdlcFcsBuf(VOS_UINT16 fcs, struct ppp_mbuf *m)
{
  VOS_INT32 len;
  VOS_CHAR *pos, *end;

  len = ppp_m_length(m);
  pos = PPP_MBUF_CTOP(m);
  end = pos + m->m_len;
  while (len--) {
    fcs = (fcs >> 8) ^ fcstab[(fcs ^ *pos++) & 0xff]; /* [false alarm]:移植开源代码 */
    if (pos == end && len) {
      m = m->m_next;
      pos = PPP_MBUF_CTOP(m);
      end = pos + m->m_len;
    }
  }
  return (fcs);
}

VOS_INT32
hdlc_WrapperOctets(struct lcp *lcp, VOS_UINT16 proto)
{
  return 2;
}

struct ppp_mbuf *
hdlc_LayerPush(/*struct bundle *bundle, */struct link *l, struct ppp_mbuf *bp,
               VOS_INT32 pri, VOS_UINT16 *proto)
{
#if 0    /* fcs calculating operation has moved to routine async_LayerPush */
  struct ppp_mbuf *last;
  VOS_CHAR *cp;
  VOS_UINT16 fcs;

  fcs = HdlcFcsBuf(INITFCS, bp);
  fcs = ~fcs;

  for (last = bp; last->m_next; last = last->m_next)
    ;

  if (last->m_size - last->m_offset - last->m_len >= 2) {
    cp = PPP_MBUF_CTOP(last) + last->m_len;
    last->m_len += 2;
  } else {
    struct ppp_mbuf *tail = ppp_m_get(2);
    last->m_next = tail;
    cp = PPP_MBUF_CTOP(tail);
  }

 if(cp != VOS_NULL)
 {

  *cp++ = fcs & 0377;        /* Low byte first (nothing like consistency) */
  *cp++ = fcs >> 8;
 }
#endif

  return bp;
}

PPP_ZC_STRU *hdlc_LayerPull(/*struct bundle *b, */struct link *l, PPP_ZC_STRU *pstMem,
               VOS_UINT16 *pusProto)
{
/* fcs calculating operation has moved to routine async_LayerPull */
/*  struct physical *p = link2physical(l);*/
  VOS_UINT16    usFcs;
  VOS_UINT16    usLen;


  usLen = PPP_ZC_GET_DATA_LEN(pstMem);

/* rfc1662 section 4.3 */
  if (usLen < 4)
  {
    PPP_MemFree(pstMem);

    return VOS_NULL_PTR;
  }

  usFcs = hdlc_Fcs(PPP_ZC_GET_DATA_PTR(pstMem), usLen);

  PPP_MNTN_LOG1(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "hdlc_LayerPull: fcs = <1>\r\n",usFcs);

  if (usFcs != GOODFCS)
  {
    l->hdlc.lqm.SaveInErrors++;
    l->hdlc.stats.badfcs++;
    PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_WARNING, "bad hdlc fcs\r\n");
    PPP_MemFree(pstMem);

    return VOS_NULL_PTR;
  }

  PPP_MemCutTailData(&pstMem, (VOS_UINT8 *)(&usFcs), 2, PPP_ZC_UL_RESERVE_LEN);

  return pstMem;
}

void
hdlc_StartTimer(struct hdlc *hdlc)
{

}

void
hdlc_StopTimer(struct hdlc *hdlc)
{

}

struct layer hdlclayer = { LAYER_HDLC, "hdlc", hdlc_LayerPush, hdlc_LayerPull };

#endif /* #if(FEATURE_ON == FEATURE_PPP) */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif