/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                            ppp_ipcp_type.h
 *
 *  Project Code: VISP1.5
 *   Module Name: PPP
 *  Date Created: 2000-04-04
 *        Author: DengYiou
 *   Description: PPP的IPCP协议处理模块数据结构
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2000-04-04      DengYiou        Create
 *  2004-07-15      YiAn            Modified for VISP
 *  2006-03-31      ZhuKun          Adjust for D00661
 *  2006-04-21      ZhuKun          Adjust for D00875
 *  2006-05-11      luyao           为支持ARM CPU字节对齐特性，修改结构。
 *  2006-05-13      l48923          Delete useless code
 *
 ************************************************************************/

#ifndef _IPCP_TYPE_H_
#define _IPCP_TYPE_H_

#ifdef __cplusplus
extern "C" {
#endif

/* IPCP协商选项 */
#define IPCP_CI_ADDRS        1   /* IP Addresses */
#define IPCP_CI_COMPRESSTYPE 2   /* Compression Type */
#define IPCP_CI_ADDR         3   /* Address */
#define IPCP_CI_DNSADDR0     129 /* Primary DNS Server Address */
#define IPCP_CI_NBNSADDR0    130 /* Primary NBNS Server Address */
#define IPCP_CI_DNSADDR1     131 /* Secondary DNS Server Address */
#define IPCP_CI_NBNSADDR1    132 /* Secondary NBNS Server Address */

/* IPHC选项的长度分为两个部分: 基本长度，子选项长度,子选项的长度不固定 */
#define IPCP_CILEN_IPHC             14  /* IPHC CI的基本长度 */

/***************/

#define MAX_STATES 16        /*  maxslot and slot number compression) */

/* IPCP协商选项长度 */
#define IPCP_CILEN_VOID     2   /* ci type + ci length */
#define IPCP_CILEN_COMPRESS 4   /* min length for compression protocol opt. */
#define IPCP_CILEN_VJ       6   /* length for RFC1332 Van-Jacobson opt. */
#define IPCP_CILEN_ADDR     6   /* new-style single address option */
#define IPCP_CILEN_ADDRS    10  /* old-style dual address option */
/********************/

/* 获取协商选项长度(cilen)宏 */
#define IPCP_LENCIVJ(neg)           (neg ? IPCP_CILEN_VJ : 0)
#define IPCP_LENCIADDR(neg, old)    (neg ? (old? IPCP_CILEN_ADDRS : IPCP_CILEN_ADDR) : 0)
#define IPCP_LENCIDNSADDR(neg)      (neg ? IPCP_CILEN_ADDR : 0)

#define IPCP_LENCIIPHC2(ulNegoSubOptions,ucRtpCompression,ucCompressType) \
    (ulNegoSubOptions ? (IPCP_CILEN_IPHC + PPP_IPCP_GetIPHCSubOptsLen(ucRtpCompression,ucCompressType)) : IPCP_CILEN_IPHC)

#define IPCP_LENCIIPHC(neg_vj, neg_iphc,ulNegoSubOptions,ucRtpCompression,ucCompressType) \
    (neg_iphc ? ( IPCP_LENCIIPHC2(ulNegoSubOptions,ucRtpCompression,ucCompressType) ) : (neg_vj ? IPCP_CILEN_VJ : 0) )

/*****************************/
/*为了不停留在closed状态，close事件后紧接着发一open事件，使状态机最终停留在stopped状态。Z34981,2003/11/04*/
/* 协商失败后,将IPCP down掉 */
#define PPP_IPCP_NegotiationDown(pLcpInfo) \
{ \
    /* 向IPCP发送Close事件,即可结束协商  */ \
    PPP_IPCP_ReceiveEventFromCore(pLcpInfo, (ULONG)PPP_EVENT_FSM_CLOSE, NULL); \
    PPP_IPCP_ReceiveEventFromCore(pLcpInfo, (ULONG)PPP_EVENT_FSM_OPEN, NULL); \
}


/* 添加协商选项(addci)宏 */
/* 修改原因: 删除旧的子选项处理代码，修改代码以支持RFC3544规定的子选项*/
/*Modified by z43740: 为了消除pclint告警，增加局部变量usIPHC,2005/10/25*/
#define ADDCIIPHC(opt, neg_iphc, neg_vj, val, maxslotindex, cflag, us_tcp_space, \
us_non_tcp_space, us_f_max_period, us_f_max_time, us_max_header, \
ulNegoSuboptions, ucRtpCompression, ucCompressType) \
if(neg_iphc) \
{ \
    USHORT usIPHC = PPP_IPHC; \
    PPP_PUTCHAR(opt, pPacket); \
    PPP_PUTCHAR(IPCP_LENCIIPHC2(ulNegoSuboptions,ucRtpCompression,ucCompressType), pPacket); \
    PPP_PUTSHORT(usIPHC, pPacket); \
    PPP_PUTSHORT(us_tcp_space, pPacket); \
    PPP_PUTSHORT(us_non_tcp_space, pPacket); \
    PPP_PUTSHORT(us_f_max_period, pPacket); \
    PPP_PUTSHORT(us_f_max_time, pPacket); \
    PPP_PUTSHORT(us_max_header, pPacket); \
    if (ulNegoSuboptions) \
    { \
        pPacket = PPP_IPCP_AddIPHCSubOpts(pPacket,ucRtpCompression,ucCompressType); \
    } \
} \
else if(neg_vj) \
{ \
    PPP_PUTCHAR(opt, pPacket); \
    PPP_PUTCHAR(IPCP_CILEN_VJ, pPacket); \
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
    PPP_PUTLONG(val1, pPacket); \
    if (old) \
    { \
        PPP_PUTLONG(val2, pPacket); \
    } \
}

#define ADDCIDNSADDR(opt,neg,addr) \
if(neg) \
{ \
    PPP_PUTCHAR(opt,pPacket); \
    PPP_PUTCHAR(IPCP_CILEN_ADDR,pPacket); \
    PPP_PUTLONG(addr,pPacket); \
}
/******************************/


/* 分析NAK报文的选项(nakci)宏 */
#define NAKCIADDR(opt, neg, old, code) \
if ( pstGotOptions->neg && \
    (ulLen >= (cilen = (old? IPCP_CILEN_ADDRS: IPCP_CILEN_ADDR))) && \
    (pPacket[1] == cilen) && (pPacket[0] == opt) ) \
{ \
    ulLen =ulLen - cilen; \
    PPP_INCPTR(2, pPacket); \
    PPP_GETLONG(ciaddr1, pPacket); \
    if (old)\
    { \
        PPP_GETLONG(ciaddr2, pPacket); \
        stNoOption.old_addrs = 1; \
    }\
    else \
    { \
        ciaddr2 = 0; \
    }\
    stNoOption.neg = 1; \
    code \
}

#define NAKCIVJ(opt, neg, code) \
if ( pstGotOptions->neg && \
    (((cilen = pPacket[1]) == IPCP_CILEN_COMPRESS) || (IPCP_CILEN_VJ == cilen)) && \
    (ulLen >= cilen) && (pPacket[0] == opt) )\
{ \
    ulLen = (ulLen - cilen); \
    PPP_INCPTR(2, pPacket); \
    PPP_GETSHORT(cishort, pPacket); \
    stNoOption.neg = 1; \
    code \
}

/* 子选项的处理: 
   1.对于本端不协商子选项的情况下，不判断子选项长度是否大于0，也不对子选项做解析处理。
   这是因为如果对端协商子选项，在特定的情况下，NAK报文中会包含子选项，这是正常的处理。
   由于本端不协商子选项，那么再次发送的协商报文中将仍然不带子选项，对端无法同意，仍
   将会NAK。这种情况下，可以知道双方是否协商子选项设置不一致，应该不再协商IPHC选项。
   
   2.如果本端协商子选项，应该调用PPP_IPCP_ParseIPHCSubOpts函数解析子选项，如果子选项
   长度为0，那么RtpCompression和CompressType都被置为0。这种情况下对端不协商(Enhanced)
   RTP Compression子选项，本端协商RTP Compression情况时出现。
*/
#define NAKCIIPHC(opt, neg_iphc, neg_vj, ulNegoSubOptions,code) \
if ( pstGotOptions->neg_iphc && PPP_CHECK_CI_IPHC_LEN(pPacket[1]) \
    && (ulLen >= pPacket[1]) && (pPacket[0] == opt) ) \
{ \
    cilen = pPacket[1]; \
    ulLen = (ulLen - cilen);\
    PPP_INCPTR(2, pPacket); \
    PPP_GETSHORT(cishort, pPacket); \
    if (PPP_IPHC == cishort) \
    { \
        PPP_GETSHORT(cishort, pPacket); \
        stTryOption.us_tcp_space = cishort; \
        PPP_GETSHORT(cishort, pPacket); \
        stTryOption.us_non_tcp_space = cishort; \
        PPP_GETSHORT(cishort, pPacket);\
        stTryOption.us_f_max_period = cishort; \
        PPP_GETSHORT(cishort, pPacket); \
        stTryOption.us_f_max_time = cishort; \
        PPP_GETSHORT(cishort, pPacket);\
        stTryOption.us_max_header = cishort; \
        if ( !(ulNegoSubOptions) ) \
        { \
            if ((cilen - IPCP_CILEN_IPHC) > 0) \
            { \
                stTryOption.neg_iphc = 0; \
            } \
        } \
        else \
        { \
            if (VOS_OK != PPP_IPCP_ParseIPHCSubOpts(&(pPacket), (USHORT)(cilen - IPCP_CILEN_IPHC), \
                                             &(stTryOption.ucRtpCompression), &(stTryOption.ucCompressType)) ) \
            { \
                goto bad; \
            } \
        } \
        stNoOption.neg_iphc = 1; \
    }\
    else \
    { \
        stTryOption.neg_iphc = 0; \
    } \
} \
else if ( pstGotOptions->neg_vj && \
          (((cilen = pPacket[1]) == IPCP_CILEN_COMPRESS) || (IPCP_CILEN_VJ == cilen)) && \
          (ulLen >= cilen) && \
          (pPacket[0] == opt) ) \
{ \
    ulLen -= cilen; \
    PPP_INCPTR(2, pPacket); \
    PPP_GETSHORT(cishort,pPacket); \
    stNoOption.neg_vj = 1; \
    code \
}

#define NAKCIDNSADDR(opt, neg, code ) \
if ( pstGotOptions->neg && \
    ((cilen = pPacket[1]) == IPCP_CILEN_ADDR) && \
    (ulLen >= cilen) && \
    (pPacket[0] == opt) ) \
{ \
    ulLen -= cilen; \
    PPP_INCPTR(2, pPacket); \
    PPP_GETLONG(ciaddr1, pPacket); \
    stNoOption.neg = 1; \
    code \
}

#define NONEGDNSADDR( neg_dnsaddr, accept_localdnsaddr, ul_addr) \
{ \
    if (pstGotOptions->neg_dnsaddr || stNoOption.neg_dnsaddr || (cilen != IPCP_CILEN_ADDR)) \
    { \
        goto bad; \
    } \
    PPP_GETLONG(ciaddr1, pPacket); \
    if (ciaddr1 && pstGotOptions->accept_localdnsaddr) \
    { \
        stTryOption.ul_addr = ciaddr1; \
        stTryOption.neg_dnsaddr = 1; \
    } \
    stNoOption.neg_dnsaddr = 1; \
}
/******************************/


/* 分析REJ报文的选项(rejci)宏 */
#define REJCIADDR(opt, neg, old, val1, val2) \
if ( pstGotOptions->neg && \
    (ulLen >= (cilen = old? IPCP_CILEN_ADDRS: IPCP_CILEN_ADDR)) && \
    (pPacket[1] == cilen) && (pPacket[0] == opt) ) \
{ \
    ulLen = (ulLen - cilen); \
    PPP_INCPTR(2, pPacket); \
    PPP_GETLONG(cilong, pPacket); \
    /* Check rejected value. */ \
    if (cilong != val1) \
    { \
        goto bad; \
    } \
    if (old) \
    { \
        PPP_GETLONG(cilong, pPacket); \
        /* Check rejected value. */ \
        if (cilong != val2) \
        { \
            goto bad; \
        } \
    } \
    /* because she can't assign us a valid address */ \
    stTryOption.neg = 0; \
}

#define REJCIVJ(opt, neg, val, maxslot, cflag) \
if ( pstGotOptions->neg && \
    (IPCP_CILEN_VJ == pPacket[1]) && \
    (ulLen >= pPacket[1]) && (pPacket[0] == opt) ) \
{ \
    ulLen = (ulLen - pPacket[1]); \
    PPP_INCPTR(2, pPacket); \
    PPP_GETSHORT(cishort, pPacket); \
    /* Check rejected value. */  \
    if (cishort != val) \
    { \
        goto bad; \
    } \
    PPP_GETCHAR(cimaxslotindex, pPacket); \
    if (cimaxslotindex != maxslot) \
    { \
        goto bad; \
    } \
    PPP_GETCHAR(ciflag, pPacket); \
    if (ciflag != cflag) \
    { \
        goto bad; \
    } \
    stTryOption.neg = 0; \
}

/* Modified by z43740 for BC3D02007: ACK/REJ报文选项需要和Request报文中选项保持一致,2009-09-09 */
#define REJCIIPHC(opt, neg_iphc, neg_vj, val, maxslot, cflag, us_tcp_space, us_non_tcp_space, \
    us_f_max_period, us_f_max_time, us_max_header, ulNegoSubOptions, ucRtpCompression, ucCompressType) \
if(pstGotOptions->neg_iphc && (pPacket[0] == opt)) \
{ \
    USHORT usSubOptLen = 0; \
    USHORT usIPHCOptionLen = 0; \
    usIPHCOptionLen =IPCP_LENCIIPHC2(ulNegoSubOptions,ucRtpCompression,ucCompressType); \
    if ((pPacket[1] != usIPHCOptionLen) || (pPacket[1] > ulLen)) \
    { \
        goto bad; \
    } \
    ulLen = (ulLen - pPacket[1]); \
    usSubOptLen = pPacket[1] - IPCP_CILEN_IPHC; \
    PPP_INCPTR(2, pPacket); \
    PPP_GETSHORT(cishort, pPacket); \
    if (cishort != PPP_IPHC) \
    { \
        goto bad; \
    } \
    PPP_GETSHORT(cishort, pPacket); \
    if(us_tcp_space != cishort) \
    { \
        goto bad; \
    } \
    PPP_GETSHORT(cishort, pPacket); \
    if(us_non_tcp_space != cishort) \
    { \
        goto bad; \
    } \
    PPP_GETSHORT(cishort, pPacket); \
    if(us_f_max_period != cishort) \
    { \
        goto bad; \
    } \
    PPP_GETSHORT(cishort, pPacket); \
    if(us_f_max_time != cishort) \
    { \
        goto bad; \
    } \
    PPP_GETSHORT(cishort, pPacket); \
    if(us_max_header != cishort) \
    { \
        goto bad; \
    } \
    if ( !(ulNegoSubOptions) ) \
    { \
        if (usSubOptLen > 0) \
        { \
            goto bad; \
        } \
    } \
    else \
    { \
        UCHAR ucTempRtpCompression = 0; \
        UCHAR ucTempCompressType = 0; \
        if ( VOS_OK != PPP_IPCP_ParseIPHCSubOpts(&(pPacket), usSubOptLen, &(ucTempRtpCompression), &(ucTempCompressType)) ) \
        { \
            goto bad; \
        } \
        else \
        { \
            if ((ucTempRtpCompression != ucRtpCompression) || (ucTempCompressType != ucCompressType)) \
            { \
                goto bad; \
            } \
        } \
    } \
    stTryOption.neg_iphc = 0; \
} \
else if ( pstGotOptions->neg_vj && \
         (IPCP_CILEN_VJ == pPacket[1]) && \
         (ulLen >= pPacket[1]) && (pPacket[0] == opt) ) \
{ \
    ulLen = (ulLen - pPacket[1]); \
    PPP_INCPTR(2, pPacket); \
    PPP_GETSHORT(cishort, pPacket); \
    /* Check rejected value. */  \
    if (cishort != (val)) \
    { \
        goto bad; \
    } \
    PPP_GETCHAR(cimaxslotindex, pPacket); \
    if (cimaxslotindex != maxslot) \
    { \
        goto bad; \
    } \
    PPP_GETCHAR(ciflag, pPacket); \
    if (ciflag != cflag) \
    { \
        goto bad; \
    } \
    stTryOption.neg_vj = 0; \
}
/* End of modification for IPHC suboptions,2005/09/19*/


#define REJCIDNSADDR(opt, neg, addr) \
{ \
    if ( pstGotOptions->neg && \
        (ulLen >= IPCP_CILEN_ADDR) && \
        (pPacket[1] == cilen) && (pPacket[0] == opt) ) \
    { \
        ulLen -= cilen; \
        PPP_INCPTR(2, pPacket); \
        PPP_GETLONG(cilong, pPacket); \
        if (cilong != pstGotOptions->addr) \
        { \
            goto bad; \
        } \
        stTryOption.neg = 0; \
    } \
}
/******************************/


/* 分析ACK报文的选项(ackci)宏 */
#define ACKCIVJ(opt, neg, val, maxslotindex, cflag) \
if (neg) \
{ \
    long vjlen =  IPCP_CILEN_VJ; \
    if ((LONG)(ulLen = (ulLen - vjlen)) < 0) \
    { \
        goto bad; \
    } \
    PPP_GETCHAR(citype, pPacket); \
    PPP_GETCHAR(cilen, pPacket); \
    if ((cilen != vjlen) || (citype != opt))  \
    { \
        goto bad; \
    } \
    PPP_GETSHORT(cishort, pPacket); \
    if (cishort != val) \
    { \
        goto bad; \
    } \
    PPP_GETCHAR(cimaxslotindex, pPacket); \
    if (cimaxslotindex != maxslotindex) \
    { \
        goto bad; \
    } \
    PPP_GETCHAR(cicflag, pPacket); \
    if (cicflag != cflag) \
    { \
        goto bad; \
    } \
}

/* 修改原因: 删除旧的子选项处理代码，修改代码以支持RFC3544规定的子选项*/
/* Modified by z43740 for BC3D02007: ACK/REJ报文选项需要和Request报文中选项保持一致,2009-09-09 */
/* Modified by y00176567, at 2011-05-27. 修改原因: 消除VC三级告警 */
/* 将函数PPP_IPCP_ParseIPHCSubOpts的第二个参数类型转换成(USHORT)，以和该函数原型定义类型保持一致 */
#define ACKCIIPHC(opt, neg_iphc, neg_vj, val, maxslotindex, cflag \
        , tcp_space, none_tcp_space, f_max_period, f_max_time, max_header \
        , ulNegoSubOptions,ucRtpCompression,ucCompressType) \
if(neg_iphc) \
{ \
    PPP_GETCHAR(citype, pPacket); \
    PPP_GETCHAR(cilen, pPacket); \
    if ((LONG)(ulLen = (ulLen - cilen)) < 0) \
    { \
        goto bad; \
    } \
    if ((cilen != IPCP_LENCIIPHC2(ulNegoSubOptions,ucRtpCompression,ucCompressType)) || (citype != opt))  \
    { \
        goto bad; \
    } \
    PPP_GETSHORT(cishort, pPacket); \
    if (cishort != (val)) \
    { \
        goto bad; \
    } \
    PPP_GETSHORT(cishort, pPacket); \
    if (tcp_space != cishort) \
    { \
        goto bad; \
    } \
    PPP_GETSHORT(cishort, pPacket); \
    if (none_tcp_space != cishort) \
    { \
        goto bad; \
    } \
    PPP_GETSHORT(cishort, pPacket); \
    if (f_max_period != cishort) \
    { \
        goto bad; \
    } \
    PPP_GETSHORT(cishort, pPacket); \
    if (f_max_time != cishort) \
    { \
        goto bad; \
    } \
    PPP_GETSHORT(cishort, pPacket); \
    if (max_header != cishort) \
    { \
        goto bad; \
    } \
    if ( !(ulNegoSubOptions) ) \
    { \
        if ((cilen - IPCP_CILEN_IPHC) > 0) \
        { \
            goto bad; \
        } \
    } \
    else \
    { \
        UCHAR ucTempRtpCompression = 0; \
        UCHAR ucTempCompressType = 0; \
        if ( VOS_OK != PPP_IPCP_ParseIPHCSubOpts(&(pPacket), (USHORT)(cilen - IPCP_CILEN_IPHC), \
                                                &(ucTempRtpCompression), &(ucTempCompressType)) ) \
        { \
            goto bad; \
        } \
        else \
        { \
            if ((ucTempRtpCompression != ucRtpCompression) || (ucTempCompressType != ucCompressType)) \
            { \
                goto bad; \
            } \
        } \
    } \
} \
else if (neg_vj) \
{ \
    long vjlen =  IPCP_CILEN_VJ; \
    if ((LONG)(ulLen = (ulLen - vjlen)) < 0) \
    { \
        goto bad; \
    } \
    PPP_GETCHAR(citype, pPacket); \
    PPP_GETCHAR(cilen, pPacket); \
    if ((cilen != vjlen) || (citype != opt))  \
    { \
        goto bad; \
    } \
    PPP_GETSHORT(cishort, pPacket); \
    if (cishort != ( val )) \
    { \
        goto bad; \
    } \
    PPP_GETCHAR(cimaxslotindex, pPacket); \
    if (cimaxslotindex != maxslotindex) \
    { \
        goto bad; \
    } \
    PPP_GETCHAR(cicflag, pPacket); \
    if (cicflag != cflag) \
    { \
        goto bad; \
    } \
}
/* End of modification for IPHC suboptions,2005/09/19 */

#define ACKCIADDR(opt, neg, old, val1, val2) \
if (neg) \
{ \
    LONG addrlen = (old? IPCP_CILEN_ADDRS: IPCP_CILEN_ADDR); \
    ulLen = ulLen - addrlen ; \
    if ((LONG)ulLen < 0) \
    { \
        goto bad; \
    } \
    PPP_GETCHAR(citype, pPacket); \
    PPP_GETCHAR(cilen, pPacket); \
    if ((cilen != addrlen) || (citype != opt)) \
    { \
        goto bad; \
    } \
    PPP_GETLONG(cilong, pPacket); \
    if ((val1 != cilong) || !val1 ) \
    { \
        goto bad; \
    } \
    if (old) \
    { \
        PPP_GETLONG(cilong, pPacket); \
        if ((val2 != cilong) || !val2) \
        { \
            goto bad; \
        } \
    } \
}

#define ACKCIDNSADDR( opt, neg, addr ) \
if( neg ) \
{ \
    if(((LONG)(ulLen -= IPCP_CILEN_ADDR) )< 0) \
    { \
        goto bad; \
    } \
    PPP_GETCHAR(citype ,pPacket); \
    PPP_GETCHAR(cilen, pPacket); \
    if((cilen != IPCP_CILEN_ADDR) || (citype != opt)) \
    { \
        goto bad; \
    } \
    PPP_GETLONG(cilong, pPacket); \
    if(addr != cilong) \
    { \
        goto bad; \
    } \
}

#define PPP_CHECK_CI_IPHC_LEN(cilen) \
( ((14 == cilen) || (16 == cilen) || (17 == cilen) || (19 == cilen) || (20 == cilen) || (22 == cilen)) ? VRP_YES : VRP_NO )
/* End of addition for IPHC,2005/09/19*/

/******************************/



typedef struct tagPppIpcpInfo
{
    PPPINFO_S *pstPppInfo ;            /* PPP控制块指针 */
    PPPFSM_S  stFsm;                   /* IPCP协议状态机 */
    PPP_IPCP_OPTION_S stGotOptions;    /* 已经协商到的我的选项 */
    PPP_IPCP_OPTION_S stHisOptions;    /* 已经协商到的对方的选项 */
    PPP_IPCP_OPTION_S stWantOptions;   /* 我希望与对方协商的我的选项 */
    PPP_IPCP_OPTION_S stAllowOptions;  /* 允许与对方协商的我的选项 */
} PPPIPCPINFO_S ;

/* 接口函数 */
VOID PPP_IPCP_Init(PPPINFO_S *, ULONG, ULONG);
VOID PPP_IPCP_ReceiveEventFromCore (VOID *, ULONG , char *);
VOID PPP_IPCP_ReceivePacket (VOID *, UCHAR* , UCHAR* , ULONG );

/* 回调函数 */
VOID PPP_IPCP_resetci(PPPFSM_S *f);
USHORT PPP_IPCP_cilen(PPPFSM_S *);
VOID PPP_IPCP_addci(PPPFSM_S *, UCHAR *);
USHORT PPP_IPCP_ackci(PPPFSM_S *, UCHAR *, ULONG);
USHORT PPP_IPCP_nakci(PPPFSM_S *, UCHAR *, ULONG);
USHORT PPP_IPCP_rejci(PPPFSM_S *, UCHAR *, ULONG);
UCHAR PPP_IPCP_reqci(PPPFSM_S *, UCHAR *, ULONG *);
VOID PPP_IPCP_up(PPPFSM_S *);
VOID PPP_IPCP_down(PPPFSM_S *);
VOID PPP_IPCP_finished(PPPFSM_S *);
VOID PPP_IPCP_starting(PPPFSM_S *);

/* 内部函数 */
ULONG PPP_IPCP_UpResetCi(PPPINFO_S *) ;
ULONG PPP_IPCP_upcheck(PPPFSM_S *pstFsm);

USHORT PPP_IPCP_GetIPHCSubOptsLen(UCHAR ucRtpCompression,UCHAR ucCompressType);
ULONG PPP_IPCP_ParseIPHCSubOpts(UCHAR** pszSubOptions, 
                                USHORT usLen, 
                                UCHAR* pucRtpCompression, 
                                UCHAR* pucCompressType);
UCHAR* PPP_IPCP_AddIPHCSubOpts(UCHAR* pszPacket, 
                               UCHAR  ucRtpCompression, 
                               UCHAR  ucCompressType);
VOID PPP_IPCP_Reqci_Adjust(UCHAR** pszPacket, 
                           UCHAR** pszNextCi,
                           USHORT* pusCiLen, 
                           USHORT usLeftLen, 
                           USHORT usTcpSpace,
                           USHORT usNonTcpSpace,
                           USHORT usFMaxPeriod,
                           USHORT usFMaxTime,
                           USHORT usMaxHeader,
                           UCHAR ucRtpCompression, 
                           UCHAR ucCompressType);

extern ULONG PPP_IPCP_IPHCInit(PPPINFO_S *pstPppInfo,PPP_IPCP_OPTION_S *pstGotOptions,PPP_IPCP_OPTION_S *pstHisOptions);
/* Add for DTS2011042101452, by z00166124, at 2011-04-21. 修改原因: IPCP定时器传入接口索引指针 */
VOID PPP_IPCP_FSM_TimeOut(VOID *pIfIndex);
VOID PPP_IPCP_Ncp_Reset(VOID * pIfIndex);

/* End of addition for IPHC,2005/09/19*/

#ifdef __cplusplus
}
#endif

#endif

