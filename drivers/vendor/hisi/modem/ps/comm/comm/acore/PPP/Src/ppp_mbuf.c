


#include "PPP/Inc/ppp_public.h"
#include "PPP/Inc/ppp_mbuf.h"

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif


#pragma pack(4)
#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_PPP_MBUF_C
#if(FEATURE_ON == FEATURE_PPP)


static struct memmap {
  struct ppp_mbuf *queue;
  VOS_INT32 fragments;
  VOS_INT32 octets;
} MemMap[MB_MAX + 1];

#if 0 /* 移植优化后，不再做mbuf内存统计，无用代码， */
static unsigned long mbuf_Mallocs, mbuf_Frees;
static const VOS_CHAR *
mbuftype(VOS_INT32 type)
{
  static const VOS_CHAR * const mbufdesc[MB_MAX] = {
    "ip in", "ip out", "ipv6 in", "ipv6 out", "nat in", "nat out",
    "mp in", "mp out", "vj in", "vj out", "icompd in", "icompd out",
    "compd in", "compd out", "lqr in", "lqr out", "echo in", "echo out",
    "proto in", "proto out", "acf in", "acf out", "sync in", "sync out",
    "hdlc in", "hdlc out", "async in", "async out", "cbcp in", "cbcp out",
    "chap in", "chap out", "pap in", "pap out", "ccp in", "ccp out",
    "ipcp in", "ipcp out", "ipv6cp in", "ipv6cp out", "lcp in", "lcp out"
  };

  return type < 0 || type >= MB_MAX ? "unknown" : mbufdesc[type];
}
#endif


VOS_INT32
ppp_m_length(struct ppp_mbuf *bp)
{
  VOS_INT32 len;

  for (len = 0; bp; bp = bp->m_next)
    len += bp->m_len;
  return len;
}


struct ppp_mbuf *
ppp_m_get_Debug(VOS_INT32 m_len, VOS_UINT32 ulFileID, VOS_UINT32 ulLineNum)
{
    struct ppp_mbuf    *bp;

    if (m_len <= 0)
    {
        PPP_MNTN_LOG1(PS_PID_APP_PPP, 0, LOG_LEVEL_WARNING,"Request for ppp_mbuf denied,m_len %d",m_len);
        return VOS_NULL_PTR;
    }

    /*去除对TTFMem.h的依赖*/
    /*bp  = TTF_MALLOC_WITH_FILE_LINE(PS_PID_APP_PPP, sizeof(struct ppp_mbuf) + m_len, ulFileID, (VOS_INT32)ulLineNum);*/

    bp  = VOS_MemAlloc(PS_PID_APP_PPP, DYNAMIC_MEM_PT, sizeof(struct ppp_mbuf) + m_len);

    if (VOS_NULL_PTR == bp)
    {
        return VOS_NULL_PTR;
    }

    PS_MEM_SET(bp, '\0', sizeof(struct ppp_mbuf));
    bp->m_size  = m_len;
    bp->m_len   = m_len;

    return bp;
}

struct ppp_mbuf *
ppp_m_getm(VOS_INT32 m_len)
{
    struct ppp_mbuf    *pRtn;
    struct ppp_mbuf   **ppCurrMem;
    VOS_INT32           lCurrLen;


    if (m_len <= 0)
    {
        PPP_MNTN_LOG1(PS_PID_APP_PPP, 0, LOG_LEVEL_WARNING,
                      "Request for ppp_mbuf denied,m_len %d", m_len);
        return VOS_NULL_PTR;
    }

    if (m_len > (VOS_INT32)M_MAXLEN)
    {
        PPP_MNTN_LOG1(PS_PID_APP_PPP, 0, LOG_LEVEL_WARNING,
                      "Request for ppp_mbuf too long, m_len %d", m_len);
    }

    pRtn        = VOS_NULL_PTR;
    ppCurrMem   = &pRtn;

    while(m_len > 0)
    {
        lCurrLen    = (m_len < (VOS_INT32)M_MAXLEN) ? m_len : (VOS_INT32)M_MAXLEN;
        m_len      -= lCurrLen;

        *ppCurrMem  = ppp_m_get(lCurrLen);

        if (VOS_NULL_PTR == *ppCurrMem)
        {
            PPP_MNTN_LOG1(PS_PID_APP_PPP, 0, LOG_LEVEL_WARNING,
                          "Request for ppp_mbuf denied,ulCurrLen %d", lCurrLen);
            break;
        }

        /* 取当前Mem的下个节点地址，为下一次申请的内存挂接上 */
        ppCurrMem   = &((*ppCurrMem)->m_next);
    }

    return pRtn;
}

struct ppp_mbuf *
ppp_m_free(struct ppp_mbuf *bp)
{
    struct ppp_mbuf    *nbp;

    /* 是返回 m_next还是 m_nextpkt，m_nextpkt是队列里的下一个元素，
    m_next是这个数据的下一段 ，所以应该返回m_next*/
    nbp = bp->m_next;

    VOS_MemFree(PS_PID_APP_PPP, bp);

    return nbp;
}

void
ppp_m_freem(struct ppp_mbuf *bp)
{
  while (bp)
    bp = ppp_m_free(bp);
}

struct ppp_mbuf *
ppp_mbuf_Read(struct ppp_mbuf *bp, void *v, VOS_INT32 len)
{
  VOS_INT32 nb;
  VOS_CHAR *ptr = v;

  while (bp && len > 0) {
    if (len > bp->m_len)
      nb = bp->m_len;
    else
      nb = len;
    if (nb) {
      PS_MEM_CPY(ptr, PPP_MBUF_CTOP(bp), nb);
      ptr += nb;
      bp->m_len -= nb;
      len -= nb;
      bp->m_offset += (VOS_INT16)nb;
    }
    if (bp->m_len == 0)
      bp = ppp_m_free(bp);
  }

  while (bp && bp->m_len == 0)
    bp = ppp_m_free(bp);

  return bp;
}

VOS_INT32
ppp_mbuf_View(struct ppp_mbuf *bp, void *v, VOS_INT32 len)
{
  VOS_INT32 nb, l = len;
  VOS_CHAR *ptr = v;

  while (bp && l > 0) {
    if (l > bp->m_len)
      nb = bp->m_len;
    else
      nb = l;
    PS_MEM_CPY(ptr, PPP_MBUF_CTOP(bp), nb);
    ptr += nb;
    l -= nb;
    bp = bp->m_next;
  }

  return len - l;
}

struct ppp_mbuf *
ppp_m_prepend(struct ppp_mbuf *bp, const void *ptr, VOS_INT32 len, VOS_INT32 extra)
{
  struct ppp_mbuf *head;

  if (bp && bp->m_offset) {
    if (bp->m_offset >= len) {
      bp->m_offset -= (VOS_INT16)len;
      bp->m_len += len;
      PS_MEM_CPY(PPP_MBUF_CTOP(bp), ptr, len);
      return bp;
    }
    len -= bp->m_offset;
    PS_MEM_CPY(bp + 1, (const VOS_CHAR *)ptr + len, bp->m_offset);
    bp->m_len += bp->m_offset;
    bp->m_offset = 0;
  }

  head = ppp_m_get(len + extra);

  if(head != VOS_NULL)
  {

      head->m_offset = (VOS_INT16)extra;
      head->m_len -= extra;
      if (ptr)
        PS_MEM_CPY(PPP_MBUF_CTOP(head), ptr, len);
      head->m_next = bp;
      return head;

  }

  PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_WARNING,"Failed to ppp_m_prepend\r\n");
  return bp;
}


/*从头部或者尾部去掉n个字节，如果为负数，就从尾部去掉*/

struct ppp_mbuf *
ppp_m_adj(struct ppp_mbuf *bp, VOS_INT32 n)
{
  if (n > 0) {
    while (bp) {
      if (n < bp->m_len) {
        bp->m_len -= n;/*fzb:错了，应该是bp->m_len -= n;*/
        bp->m_offset += (VOS_INT16)n;
        return bp;
      }
      n -= bp->m_len;
      bp = ppp_m_free(bp);
    }
  } else {
    if ((n = ppp_m_length(bp) + n) <= 0) {
      ppp_m_freem(bp);
      return VOS_NULL_PTR;
    }
    for (; bp; bp = bp->m_next, n -= bp->m_len)
      if (n < bp->m_len) {
        bp->m_len = n;
        ppp_m_freem(bp->m_next);
        bp->m_next = VOS_NULL_PTR;
        break;
      }
  }

  return bp;
}

void
ppp_mbuf_Write(struct ppp_mbuf *bp, const void *ptr, VOS_INT32 m_len)
{
  VOS_INT32 plen;
  VOS_INT32 nb;

  plen = ppp_m_length(bp);
  if (plen < m_len)
  {
    m_len = plen;
  }

  while (m_len > 0) {
    nb = (m_len < bp->m_len) ? m_len : bp->m_len;
    PS_MEM_CPY(PPP_MBUF_CTOP(bp), ptr, (VOS_UINT32)nb);
    m_len -= bp->m_len;
    bp = bp->m_next;
    ptr = (void *)((VOS_UINT_PTR)ptr + nb);
  }
}

/*fanzhibin f49086 change it begin*/

VOS_INT32
ppp_mbuf_Show(VOS_VOID)
{
  VOS_INT32 i;

  PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL,"Fragments (octets) in use:\r\n");
  for (i = 0; i < MB_MAX; i += 2)
    PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "%10.10s: %04lu (%06lu)\r\n");

  if (i == MB_MAX)
    PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "%10.10s: %04lu (%06lu)\r\n"/*,
                  mbuftype(i), (VOS_UINT32)MemMap[i].fragments,
                  (VOS_UINT32)MemMap[i].octets*/);

  PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "Mallocs: %qu,   Frees: %qu\r\n"/*,
                mbuf_Mallocs, mbuf_Frees*/);

  return 0;
}

/*fanzhibin f49086 change it end*/

struct ppp_mbuf *
ppp_m_dequeue(struct ppp_mqueue *q)
{
  struct ppp_mbuf *bp;

  PPP_MNTN_LOG1(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "ppp_m_dequeue: queue len = <1>", (VOS_INT32)q->len);
  bp = q->top;
  if (bp) {
    q->top = q->top->m_nextpkt;
    q->len--;
    if (q->top == VOS_NULL_PTR) {
      q->last = q->top;
      if (q->len)
    PPP_MNTN_LOG1(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "ppp_m_dequeue: Not zero ",
                   (VOS_UINT32)q->len);
    }
    bp->m_nextpkt = VOS_NULL_PTR;
  }

  return bp;
}

void
ppp_m_enqueue(struct ppp_mqueue *queue, struct ppp_mbuf *bp)
{
  if (bp != VOS_NULL_PTR) {
    if (queue->last) {
      queue->last->m_nextpkt = bp;
      queue->last = bp;
    } else
      queue->last = queue->top = bp;
    queue->len++;
    PPP_MNTN_LOG1(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "ppp_m_enqueue: len = <1>", (VOS_INT32)queue->len);
  }
}

struct ppp_mbuf *
ppp_m_pullup(struct ppp_mbuf *bp)
{
  /* Put it all in one contigous (aligned) ppp_mbuf */

  if (bp != VOS_NULL_PTR) {
    if (bp->m_next != VOS_NULL_PTR) {
      struct ppp_mbuf *nbp;
      VOS_CHAR *cp;

      nbp = ppp_m_get(ppp_m_length(bp));
      if(nbp == VOS_NULL)
        return bp;

      for (cp = PPP_MBUF_CTOP(nbp); bp; bp = ppp_m_free(bp)) {
        PS_MEM_CPY(cp, PPP_MBUF_CTOP(bp), bp->m_len);
        cp += bp->m_len;
      }
      bp = nbp;
    }
#ifndef __i386__    /* Do any other archs not care about alignment ? */
    else if ((bp->m_offset & (sizeof(long) - 1)) != 0) {

/*fanzhibin f49086 change it begin*/
/*函数修改了，参数换了位置*/
      PS_MEM_CPY(bp + 1, PPP_MBUF_CTOP(bp), bp->m_len);
/*fanzhibin f49086 change it end*/

      bp->m_offset = 0;
    }
#endif
  }

  return bp;
}

void
ppp_m_settype(struct ppp_mbuf *bp, VOS_INT32 type)
{
  for (; bp; bp = bp->m_next)
    if (type != bp->m_type) {
      MemMap[bp->m_type].fragments--;
      MemMap[bp->m_type].octets -= bp->m_size;
      bp->m_type = (VOS_INT16)type;
      MemMap[type].fragments++;
      MemMap[type].octets += bp->m_size;
    }
}

struct ppp_mbuf *
ppp_m_append(struct ppp_mbuf *bp, const void *v, VOS_INT32 sz)
{
  struct ppp_mbuf *m = bp;

  if (m) {
    while (m->m_next)
      m = m->m_next;
    if (m->m_size - m->m_len > sz) /*还应该加上m_offset*/
      m->m_len += sz;/*还应该有拷贝操作，由于这个函数不调用，所以没改*/
    else
      m->m_next = ppp_m_prepend(VOS_NULL_PTR, v, sz, 0);
  } else
    bp = ppp_m_prepend(VOS_NULL_PTR, v, sz, 0);

  return bp;
}


struct ppp_mbuf *
ppp_m_get_from_ttfmem(PPP_ZC_STRU *pstMem)
{
    VOS_UINT16          usLen;
    struct ppp_mbuf    *bp;
    PPP_ZC_STRU        *pstCurrMem;
    VOS_CHAR           *pcMbufData;


    if (VOS_NULL_PTR == pstMem)
    {
        return VOS_NULL_PTR;
    }


    usLen   = PPP_ZC_GET_DATA_LEN(pstMem);

    bp      = ppp_m_get(usLen);

    if (VOS_NULL_PTR == bp)
    {
        return VOS_NULL_PTR;
    }

    pstCurrMem  = pstMem;
    pcMbufData  = PPP_MBUF_CTOP(bp);

    /* 目前的零拷贝暂不支持链式 */
    /*
    while (VOS_NULL_PTR != pstCurrMem)
    {
    */
        PS_MEM_CPY(pcMbufData, PPP_ZC_GET_DATA_PTR(pstCurrMem), PPP_ZC_GET_DATA_LEN(pstCurrMem));

        pcMbufData += PPP_ZC_GET_DATA_LEN(pstCurrMem);
    /*
        pstCurrMem  = pstCurrMem->pNext;
    }
    */

    return bp;
}

PPP_ZC_STRU *ppp_m_alloc_ttfmem_from_mbuf(struct ppp_mbuf *bp)
{
    VOS_UINT16  usLen;
    PPP_ZC_STRU *pstMem;


    if (VOS_NULL_PTR == bp)
    {
        return VOS_NULL_PTR;
    }

    usLen   = (VOS_INT16)ppp_m_length(bp);

    if (0 == usLen)
    {
        return VOS_NULL_PTR;

    }

    pstMem  = PPP_MemAlloc(usLen, PPP_ZC_DL_RESERVE_LEN);

    if (VOS_NULL_PTR == pstMem)
    {
        return VOS_NULL_PTR;
    }

    /* 设置零拷贝数据内容长度 */
    PPP_ZC_SET_DATA_LEN(pstMem, usLen);

    ppp_mbuf_View(bp, PPP_ZC_GET_DATA_PTR(pstMem), usLen);

    return pstMem;
} /* ppp_m_ttfmem_alloc_from_mbuf */

#endif /*#if(FEATURE_ON == FEATURE_PPP)*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

