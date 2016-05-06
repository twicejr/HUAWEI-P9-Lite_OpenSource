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
 * $FreeBSD: src/usr.sbin/ppp/ppp_mbuf.h,v 1.27 2001/08/14 16:05:51 brian Exp $
 */
#ifndef __PPP_MBUF_H__
#define __PPP_MBUF_H__

#include "PPP/Inc/ppp_public.h"

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif

#pragma pack(4)

struct ppp_mbuf {
  VOS_INT32 m_size;        /* size allocated (excluding header) */
  VOS_INT32 m_len;            /* available byte count in buffer */
  VOS_INT16 m_offset;        /* offset from header end to start position */
  VOS_INT16 m_type;            /* MB_* below */
  VOS_UINT8 aucReserve[4];
  struct ppp_mbuf *m_next;        /* link to next ppp_mbuf */
  struct ppp_mbuf *m_nextpkt;    /* link to next packet */
  /* buffer space is malloc()d directly after the header */
};

struct ppp_mqueue {
  struct ppp_mbuf *top;
  struct ppp_mbuf *last;
  VOS_INT32 len;
  VOS_UINT8 aucReserve[4];
};


#define PPP_MBUF_CTOP(bp) \
    ((bp) ? ((VOS_CHAR *)((bp)+1) + (bp)->m_offset) : VOS_NULL_PTR)


#define CONST_MBUF_CTOP(bp) \
    ((bp) ? (const VOS_CHAR *)((bp)+1) + (bp)->m_offset : VOS_NULL_PTR)

#define MB_IPIN        0
#define MB_IPOUT    1
#define MB_IPV6IN    2
#define MB_IPV6OUT    3
#define MB_NATIN    4
#define MB_NATOUT    5
#define MB_MPIN        6
#define MB_MPOUT    7
#define MB_VJIN        8
#define MB_VJOUT    9
#define MB_ICOMPDIN    10
#define MB_ICOMPDOUT    11
#define MB_COMPDIN    12
#define MB_COMPDOUT    13
#define MB_LQRIN    14
#define MB_LQROUT    15
#define MB_ECHOIN    16
#define MB_ECHOOUT    17
#define MB_PROTOIN    18
#define MB_PROTOOUT    19
#define MB_ACFIN    20
#define MB_ACFOUT    21
#define MB_SYNCIN    22
#define MB_SYNCOUT    23
#define MB_HDLCIN    24
#define MB_HDLCOUT    25
#define MB_ASYNCIN    26
#define MB_ASYNCOUT    27
#define MB_CBCPIN    28
#define MB_CBCPOUT    29
#define MB_CHAPIN    30
#define MB_CHAPOUT    31
#define MB_PAPIN    32
#define MB_PAPOUT    33
#define MB_CCPIN    34
#define MB_CCPOUT    35
#define MB_IPCPIN    36
#define MB_IPCPOUT    37
#define MB_IPV6CPIN    38
#define MB_IPV6CPOUT    39
#define MB_LCPIN    40
#define MB_LCPOUT    41
#define MB_UNKNOWN    42
#define MB_MAX        MB_UNKNOWN

#define M_MAXLEN    (4352 - sizeof(struct ppp_mbuf))    /* > HDLCSIZE */


extern VOS_INT32 ppp_m_length(struct ppp_mbuf *);
extern struct ppp_mbuf *ppp_m_get_Debug(VOS_INT32 m_len, VOS_UINT32 ulFileID, VOS_UINT32 ulLineNum);
extern struct ppp_mbuf *ppp_m_getm(VOS_INT32 m_len);
extern struct ppp_mbuf *ppp_m_get_from_ttfmem(PPP_ZC_STRU *pstMem);
extern PPP_ZC_STRU *ppp_m_alloc_ttfmem_from_mbuf(struct ppp_mbuf *bp);
extern struct ppp_mbuf *ppp_m_free(struct ppp_mbuf *);
extern void ppp_m_freem(struct ppp_mbuf *);
extern void ppp_mbuf_Write(struct ppp_mbuf *, const void *, VOS_INT32);
extern struct ppp_mbuf *ppp_mbuf_Read(struct ppp_mbuf *, void *, VOS_INT32);
extern VOS_INT32 ppp_mbuf_View(struct ppp_mbuf *, void *, VOS_INT32);
extern struct ppp_mbuf *ppp_m_prepend(struct ppp_mbuf *, const void *, VOS_INT32, VOS_INT32);
extern struct ppp_mbuf *ppp_m_adj(struct ppp_mbuf *, VOS_INT32);
extern struct ppp_mbuf *ppp_m_pullup(struct ppp_mbuf *);
extern void ppp_m_settype(struct ppp_mbuf *, VOS_INT32);
extern struct ppp_mbuf *ppp_m_append(struct ppp_mbuf *, const void *, VOS_INT32);

extern VOS_INT32 ppp_mbuf_Show(VOS_VOID);

extern void ppp_m_enqueue(struct ppp_mqueue *, struct ppp_mbuf *);
extern struct ppp_mbuf *ppp_m_dequeue(struct ppp_mqueue *);

#define ppp_m_get(m_len)    \
    ppp_m_get_Debug(m_len, THIS_FILE_ID, __LINE__)

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

#endif /* end of ppp_mbuf.h */

