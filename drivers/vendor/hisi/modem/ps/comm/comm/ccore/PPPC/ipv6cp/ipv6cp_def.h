
/************************************************************************
*                                                                      *
*                             ipv6cp_def.h                                *
*                                                                      *
*  Project Code:       IPV6CP .1                                          *
*  Create Date:        2009/12/29                                      *
*  Author:             z00129699                                      *
*  Modify Date:                                                        *
 *  Document:                                                           *
 *  Function:           PPP的IPv6CP协议模块私有宏定义                      *
 *  Others:                                                             *
 *----------------------------------------------------------------------*
 *                                                                      *
 *                                                                      *
 *----------------------------------------------------------------------*
 *                                                                      *
 *   这个文件定义了IPv6CP协议模块的全部私有宏定义                          *
 *                                                                      *
 ************************************************************************/

#ifndef      _IPV6CP_DEF_H_
#define      _IPV6CP_DEF_H_

#ifdef      __cplusplus
extern "C" {
#endif		/* end of __cplusplus */

/* IPCP协商选项 */
#define IPCP_CI_ADDRS	     1	 /* IP Addresses */
#define IPCP_CI_COMPRESSTYPE 2	 /* Compression Type */
#define	IPV6CP_CI_ADDR		 1   /* IPV6 Address */
#define IPCP_CI_DNSADDR0     129 /* Primary DNS Server Address */
#define IPCP_CI_NBNSADDR0    130 /* Primary NBNS Server Address */
#define IPCP_CI_DNSADDR1     131 /* Secondary DNS Server Address */
#define IPCP_CI_NBNSADDR1    132 /* Secondary NBNS Server Address */
/***************/

#define MAX_STATES 16        /*  maxslot and slot number compression) */

/* IPCP协商选项长度 */
#define IPCP_CILEN_VOID	2
#define IPCP_CILEN_COMPRESS	4	/* min length for compression protocol opt. */
#define IPV6CP_CILEN_VJ	6	/* length for RFC1332 Van-Jacobson opt. */
#define IPV6CP_CILEN_ADDR  10/* IPV6 single address option */
/********************/

/* 获取协商选项长度(cilen)宏 */
#define IPV6CP_LENCIVJ(neg)   (neg ? IPV6CP_CILEN_VJ : 0)
#define IPV6CP_LENCIADDR(neg, old)	(neg ? IPV6CP_CILEN_ADDR : 0)
#define IPV6CP_LENCIDNSADDR(neg) (neg ? IPV6CP_CILEN_ADDR : 0)
/*****************************/

/* 协商失败后,将IPCP down掉 */
#define PPP_IPV6CP_NegotiationDown(pIpv6cpInfo) \
{ \
    /* 向IPCP发送Close事件,即可结束协商  */ \
    PPP_IPV6CP_ReceiveEventFromCore(pIpv6cpInfo, (LONG)PPP_EVENT_FSM_CLOSE, NULL) ; \
}


/* 添加协商选项(addci)宏 */
#define ADDCIVJ(opt, neg, val, maxslotindex, cflag) \
if (neg) \
{ \
	PPP_PUTCHAR(opt, pPacket); \
    PPP_PUTCHAR( IPCP_CILEN_VJ, pPacket); \
	PPP_PUTSHORT(val, pPacket); \
    PPP_PUTCHAR(maxslotindex, pPacket); \
    PPP_PUTCHAR(cflag, pPacket); \
}

#define ADDCIADDRV6(opt, neg, old, val1, val2) \
if (neg) \
{ \
	long addrlen = IPV6CP_CILEN_ADDR; \
	PPP_PUTCHAR(opt, pPacket); \
	PPP_PUTCHAR(addrlen, pPacket); \
    PPP_PUTCHARPTR(val1, pPacket,IPV6_ADDR_LEN); \
}

#define ADDCIDNSADDRV6(opt,neg,addr) \
if(neg) \
{ \
    PPP_PUTCHAR(opt,pPacket); \
    PPP_PUTCHAR(IPCP_CILEN_ADDR,pPacket); \
    PPP_PUTLONG(addr,pPacket); \
}
/******************************/


/* 分析NAK报文的选项(nakci)宏 */
#define NAKCIADDRV6(opt, neg, old, code) \
if (pstGotOptions->neg && \
    (ulLen >= (cilen = (old? IPCP_CILEN_ADDRS: IPV6CP_CILEN_ADDR))) && \
    (pPacket[1] == cilen && pPacket[0] == opt)) \
{ \
    ulLen =ulLen - cilen; \
    PPP_INCPTR(2, pPacket); \
    PPP_GETCHARPTR(ciaddr1, pPacket, IPV6_ADDR_LEN); \
    PPP_MemSet((void *)ciaddr2, 0, IPV6_ADDR_LEN); \
    stNoOption.neg = 1; \
    code; \
 }

#define NAKCIVJ(opt, neg, code) \
if (pstGotOptions->neg && \
	((cilen = pPacket[1]) == IPCP_CILEN_COMPRESS || cilen == IPCP_CILEN_VJ) && \
	ulLen >= cilen &&	pPacket[0] == opt)\
{ \
	ulLen = (ulLen - cilen); \
	PPP_INCPTR(2, pPacket); \
	PPP_GETSHORT(cishort, pPacket); \
    stNoOption.neg = 1; \
	code \
}

#define NAKCIDNSADDRV6(opt, neg, code ) \
if (pstGotOptions->neg && \
    (( cilen = pPacket[1] ) == IPCP_CILEN_ADDR) && \
    ulLen >= cilen && \
    pPacket[0] == opt) \
{ \
    ulLen -= cilen; \
    PPP_INCPTR(2, pPacket); \
    PPP_GETLONG(uladdr1, pPacket); \
    stNoOption.neg = 1; \
    code \
}

#define NONEGDNSADDRV6( neg_dnsaddr, accept_localdnsaddr, ul_addr) \
{ \
    if (pstGotOptions->neg_dnsaddr || stNoOption.neg_dnsaddr || cilen != IPCP_CILEN_ADDR) \
        goto bad; \
    PPP_GETLONG(uladdr1, pPacket); \
    if (uladdr1 && pstGotOptions->accept_localdnsaddr) \
    { \
        stTryOption.ul_addr = uladdr1; \
        stTryOption.neg_dnsaddr = 1; \
    } \
    stNoOption.neg_dnsaddr = 1; \
}
/******************************/


/* 分析REJ报文的选项(rejci)宏 */
#define REJCIADDRV6(opt, neg, old, val1, val2) \
if (pstGotOptions->neg && \
    ulLen >= (cilen = old? IPCP_CILEN_ADDRS: IPV6CP_CILEN_ADDR) && \
    pPacket[1] == cilen && pPacket[0] == opt) \
{ \
    /*lint -e801*/ \
    ulLen = (ulLen - cilen); \
    PPP_INCPTR(2, pPacket); \
    PPP_GETCHARPTR(ciaddr, pPacket, IPV6_ADDR_LEN); \
    /* Check rejected value. */ \
    if (VOS_MemCmp((void*)ciaddr, (void*)val1, IPV6_ADDR_LEN)) \
        goto bad; \
    stTryOption.neg = 0; \
    /*lint +e801*/ \
}

#define REJCIVJ(opt, neg, val, maxslot, cflag) \
if (pstGotOptions->neg && \
    (pPacket[1] ==  IPCP_CILEN_VJ) && \
	ulLen >= pPacket[1] && pPacket[0] == opt) \
{ \
      /*lint -e801*/ \
	ulLen = (ulLen - pPacket[1]); \
	PPP_INCPTR(2, pPacket); \
	PPP_GETSHORT(cishort, pPacket); \
	/* Check rejected value. */  \
	if (cishort != val) \
	goto bad; \
    PPP_GETCHAR(cimaxslotindex, pPacket); \
    if (cimaxslotindex != maxslot) \
    goto bad; \
    PPP_GETCHAR(ciflag, pPacket); \
    if (ciflag != cflag) \
    goto bad; \
	stTryOption.neg = 0; \
    /*lint +e801*/ \
}

#define REJCIDNSADDRV6(opt, neg, addr) \
{ \
    /*lint -e801*/ \
    if (pstGotOptions->neg && \
        ulLen >= IPCP_CILEN_ADDR && \
        pPacket[1] == cilen && pPacket[0] == opt) \
    { \
        ulLen -= cilen; \
        PPP_INCPTR(2, pPacket); \
        PPP_GETLONG(cilong, pPacket); \
        if (cilong != pstGotOptions->addr) \
            goto bad; \
        stTryOption.neg = 0; \
    } \
    /*lint +e801*/ \
}
/******************************/


/* 分析ACK报文的选项(ackci)宏 */
#define ACKCIVJ(opt, neg, val, maxslotindex, cflag) \
if (neg) \
{ \
    /*lint -e801*/ \
    long vjlen =  IPCP_CILEN_VJ; \
	if ((LONG)(ulLen = (ulLen - vjlen)) < 0) \
        goto bad; \
	PPP_GETCHAR(citype, pPacket); \
	PPP_GETCHAR(cilen, pPacket); \
	if (cilen != vjlen || \
	citype != opt)  \
        goto bad; \
	PPP_GETSHORT(cishort, pPacket); \
	if (cishort != val) \
        goto bad; \
    PPP_GETCHAR(cimaxslotindex, pPacket); \
    if (cimaxslotindex != maxslotindex) \
        goto bad; \
    PPP_GETCHAR(cicflag, pPacket); \
    if (cicflag != cflag) \
        goto bad; \
    /*lint +e801*/ \
}

#define ACKCIADDRV6(opt, neg, old, val1, val2) \
if (neg) \
{ \
    /*lint -e801*/ \
    LONG addrlen = (old? IPCP_CILEN_ADDRS: IPV6CP_CILEN_ADDR); \
    ulLen = ulLen - addrlen ; \
    if ((LONG)ulLen < 0) \
    goto bad; \
    PPP_GETCHAR(citype, pPacket); \
    PPP_GETCHAR(cilen, pPacket); \
    if (cilen != addrlen || \
    citype != opt) \
    goto bad; \
    PPP_GETCHARPTR(ciusINid, pPacket,IPV6_ADDR_LEN); \
    /*lint +e801*/ \
}

#define ACKCIDNSADDRV6( opt, neg, addr ) \
if( neg ) \
{ \
    /*lint -e801*/ \
    if(((LONG)(ulLen -= IPCP_CILEN_ADDR) )< 0) \
        goto bad; \
    PPP_GETCHAR(citype ,pPacket); \
    PPP_GETCHAR(cilen, pPacket); \
    if(cilen != IPCP_CILEN_ADDR || citype != opt) \
        goto bad; \
    PPP_GETLONG(cilong, pPacket); \
    if(addr != cilong) \
        goto bad; \
    /*lint +e801*/ \
}
/******************************/


#ifdef      __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _IPCP_DEF_H_ */





