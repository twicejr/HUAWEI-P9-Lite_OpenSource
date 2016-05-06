
/************************************************************************
 *                                                                      *
 *                             ipcp_def.h                               *
 *                                                                      *
 *  Project Code:       VRP3.0                                          *
 *  Create Date:        2000/04/04                                      *
 *  Author:             Deng Yi Ou                                      *
 *  Modify Date:                                                        *
 *  Document:                                                           *
 *  Function:           PPP的IPCP协议模块私有宏定义                      *
 *  Others:                                                             *
 *----------------------------------------------------------------------*
 *                                                                      *
 *  Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc. *
 *                      ALL RIGHTS RESERVED                             *
 *                                                                      *
 *----------------------------------------------------------------------*
 *                                                                      *
 *   这个文件定义了IPCP协议模块的全部私有宏定义                          *
 *                                                                      *
 ************************************************************************/

#ifndef      _IPCP_DEF_H_
#define      _IPCP_DEF_H_

#ifdef      __cplusplus
extern "C" {
#endif		/* end of __cplusplus */

/* IPCP协商选项 */
#define IPCP_CI_ADDRS	     1	 /* IP Addresses */
#define IPCP_CI_COMPRESSTYPE 2	 /* Compression Type */
#define	IPCP_CI_ADDR		 3   /* IP Address */
#define IPCP_CI_DNSADDR0     129 /* Primary DNS Server Address */
#define IPCP_CI_NBNSADDR0    130 /* Primary NBNS Server Address */
#define IPCP_CI_DNSADDR1     131 /* Secondary DNS Server Address */
#define IPCP_CI_NBNSADDR1    132 /* Secondary NBNS Server Address */
/***************/

#define MAX_STATES 16        /*  maxslot and slot number compression) */

/* IPCP协商选项长度 */
#define IPCP_CILEN_VOID	2
#define IPCP_CILEN_COMPRESS	4	/* min length for compression protocol opt. */
#define IPCP_CILEN_VJ	6	/* length for RFC1332 Van-Jacobson opt. */
#define IPCP_CILEN_ADDR	6	/* new-style single address option */
#define IPCP_CILEN_ADDRS	10	/* old-style dual address option */
/********************/

/* 获取协商选项长度(cilen)宏 */
#define IPCP_LENCIVJ(neg)   (neg ? IPCP_CILEN_VJ : 0)
#define IPCP_LENCIADDR(neg, old)	(neg ? (old? IPCP_CILEN_ADDRS : IPCP_CILEN_ADDR) : 0)
#define IPCP_LENCIDNSADDR(neg) (neg ? IPCP_CILEN_ADDR : 0)
/*****************************/

/* 协商失败后,将IPCP down掉 */
#define PPP_IPCP_NegotiationDown(pLcpInfo) \
{ \
    /* 向IPCP发送Close事件,即可结束协商  */ \
    PPP_IPCP_ReceiveEventFromCore(pLcpInfo, (LONG)PPP_EVENT_FSM_CLOSE, NULL) ; \
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

#define ADDCIADDR(opt, neg, old, val1, val2) \
if (neg) \
{ \
	long addrlen = (old? IPCP_CILEN_ADDRS: IPCP_CILEN_ADDR); \
	PPP_PUTCHAR(opt, pPacket); \
	PPP_PUTCHAR(addrlen, pPacket); \
    PPP_PUTADDR(val1, pPacket); \
	if (old) \
	{ \
        PPP_PUTADDR(val2, pPacket); \
	} \
}

#define ADDCIDNSADDR(opt,neg,addr) \
if(neg) \
{ \
    PPP_PUTCHAR(opt,pPacket); \
    PPP_PUTCHAR(IPCP_CILEN_ADDR,pPacket); \
    PPP_PUTADDR(addr,pPacket); \
}
/******************************/


/* 分析NAK报文的选项(nakci)宏 */
#define NAKCIADDR(opt, neg, old, code) \
if (pstGotOptions->neg && \
	ulLen >= (cilen = (old? IPCP_CILEN_ADDRS: IPCP_CILEN_ADDR)) && \
	pPacket[1] == cilen && pPacket[0] == opt) \
{ \
	ulLen =ulLen - cilen; \
	PPP_INCPTR(2, pPacket); \
    PPP_GETADDR(ciaddr1, pPacket); \
	if (old)\
    { \
        PPP_GETADDR(ciaddr2, pPacket); \
		stNoOption.old_addrs = 1; \
	}\
	else \
		ciaddr2 = 0; \
	stNoOption.neg = 1; \
	code \
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

#define NAKCIDNSADDR(opt, neg, code ) \
if (pstGotOptions->neg && \
    (( cilen = pPacket[1] ) == IPCP_CILEN_ADDR) && \
    ulLen >= cilen && \
    pPacket[0] == opt) \
{ \
    ulLen -= cilen; \
    PPP_INCPTR(2, pPacket); \
    PPP_GETADDR(ciaddr1, pPacket); \
    stNoOption.neg = 1; \
    code \
}

#define NONEGDNSADDR( neg_dnsaddr, accept_localdnsaddr, ul_addr) \
{ \
    /*lint -e801*/ \
    if (pstGotOptions->neg_dnsaddr || stNoOption.neg_dnsaddr || cilen != IPCP_CILEN_ADDR) \
        goto bad; \
    PPP_GETADDR(ciaddr1, pPacket); \
    if (ciaddr1 && pstGotOptions->accept_localdnsaddr) \
    { \
        stTryOption.ul_addr = ciaddr1; \
        stTryOption.neg_dnsaddr = 1; \
    } \
    stNoOption.neg_dnsaddr = 1; \
    /*lint +e801*/ \
}
/******************************/


/* 分析REJ报文的选项(rejci)宏 */
#define REJCIADDR(opt, neg, old, val1, val2) \
if (pstGotOptions->neg && \
	ulLen >= (cilen = old? IPCP_CILEN_ADDRS: IPCP_CILEN_ADDR) && \
	pPacket[1] == cilen && pPacket[0] == opt) \
{ \
      /*lint -e801*/ \
	ulLen = (ulLen - cilen); \
	PPP_INCPTR(2, pPacket); \
    PPP_GETADDR(cilong, pPacket); \
	/* Check rejected value. */ \
	if (cilong != val1) \
		goto bad; \
	if (old) \
	{ \
        PPP_GETADDR(cilong, pPacket); \
		/* Check rejected value. */ \
		if (cilong != val2) \
		goto bad; \
	} \
    /* because she can't assign us a valid address */ \
	stTryOption.neg = 0; \
	/*lint +e801*/ \
}

#define REJCIVJ(opt, neg, val, maxslot, cflag) \
if (pstGotOptions->neg && \
    (pPacket[1] ==  IPCP_CILEN_VJ) && \
	ulLen >= pPacket[1] && pPacket[0] == opt) \
{ \
     /*line -e801*/ \
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

#define REJCIDNSADDR(opt, neg, addr) \
{ \
    /*lint -e801*/ \
    if (pstGotOptions->neg && \
        ulLen >= IPCP_CILEN_ADDR && \
        pPacket[1] == cilen && pPacket[0] == opt) \
    { \
        ulLen -= cilen; \
        PPP_INCPTR(2, pPacket); \
        PPP_GETADDR(cilong, pPacket); \
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

#define ACKCIADDR(opt, neg, old, val1, val2) \
if (neg) \
{ \
      /*lint -e801*/ \
	LONG addrlen = (old? IPCP_CILEN_ADDRS: IPCP_CILEN_ADDR); \
	ulLen = ulLen - addrlen ; \
	if ((LONG)ulLen < 0) \
	goto bad; \
	PPP_GETCHAR(citype, pPacket); \
	PPP_GETCHAR(cilen, pPacket); \
	if (cilen != addrlen || \
	citype != opt) \
	goto bad; \
    PPP_GETADDR(cilong, pPacket); \
    if (val1 != cilong || !val1 ) \
	goto bad; \
	if (old) \
	{ \
        PPP_GETADDR(cilong, pPacket); \
        if (val2 != cilong || !val2) \
		goto bad; \
	} \
	/*lint +e801*/ \
}

#define ACKCIDNSADDR( opt, neg, addr ) \
if( neg ) \
{ \
    /*lint -e801*/ \
    if(((LONG)(ulLen -= IPCP_CILEN_ADDR) )< 0) \
        goto bad; \
    PPP_GETCHAR(citype ,pPacket); \
    PPP_GETCHAR(cilen, pPacket); \
    if(cilen != IPCP_CILEN_ADDR || citype != opt) \
        goto bad; \
    PPP_GETADDR(cilong, pPacket); \
    if(addr != cilong) \
        goto bad; \
    /*lint +e801*/ \
}
/******************************/


#ifdef      __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _IPCP_DEF_H_ */





