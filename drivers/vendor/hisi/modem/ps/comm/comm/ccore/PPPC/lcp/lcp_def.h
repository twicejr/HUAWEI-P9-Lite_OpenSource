
/************************************************************************
 *                                                                      *
 *                             lcp_def.h                                *
 *                                                                      *
 *  Project Code:       VRP3.0                                          *
 *  Create Date:        2000/04/04                                      *
 *  Author:             Deng Yi Ou                                      *
 *  Modify Date:                                                        *
 *  Document:                                                           *
 *  Function:           PPP的LCP协议模块私有宏定义                      *
 *  Others:                                                             *
 *----------------------------------------------------------------------*
 *                                                                      *
 *  Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc. *
 *                      ALL RIGHTS RESERVED                             *
 *                                                                      *
 *----------------------------------------------------------------------*
 *                                                                      *
 *   这个文件定义了LCP协议模块的全部私有宏定义                          *
 *                                                                      *
 ************************************************************************/

#ifndef      _LCP_DEF_H_
#define      _LCP_DEF_H_

#ifdef      __cplusplus
extern "C" {
#endif      /* end of __cplusplus */

/* LCP协商选项 */
#define LCP_CI_MRU              1   /* Maximum Receive Unit */
#define LCP_CI_ASYNCMAP         2   /* Async Control Character Map */
#define LCP_CI_AUTHTYPE         3   /* Authentication Type */
#define LCP_CI_QUALITY          4   /* Quality Protocol */
#define LCP_CI_MAGICNUMBER      5   /* Magic Number */
#define LCP_CI_PCOMPRESSION     7   /* Protocol Field Compression */
#define LCP_CI_ACCOMPRESSION    8   /* Address/Control Field Compression */
#define LCP_CI_MRRU             17  /* MRRU */
#define LCP_CI_SSNHF            18  /* Short Sequence Number Header Format */
#define LCP_CI_DISCR            19  /* Endpoint Discriminator */
#define LCP_CI_CALLBACK         13  /* Callback */
/***************/


/* LCP自定义类型 */
#define ECHOREQ         9   /* Echo Request */
#define ECHOREP         10  /* Echo Reply */
#define DISCREQ         11  /* Discard Request */
#define IDENTIFIC       12  /* Identification */
#define TIMEREMAIN      13  /* Time remaining */
/*****************/


/* 各协商选项长度 */
#define PPP_CILEN_CHAP      5   /* PPP_CILEN_VOID + sizeof(short) + 1 */
#define PPP_CILEN_LQR       8   /* PPP_CILEN_VOID + sizeof(short) + sizeof(long) */
#define PPP_CILEN_DISCR     3   /* CLASS + LEN + ADDR */
/******************/


/* 获取协商选项长度(cilen)宏 */
#define PPP_LENCICHAP(neg)  (neg ? PPP_CILEN_CHAP : 0)
#define PPP_LENCILQR(neg)   (neg ? PPP_CILEN_LQR: 0)
#define PPP_LENCIDISCR(neg) (neg ? pstGotOptions->discr_len : 0)
#define PPP_LENCALLBACK(neg) (neg ? pstGotOptions->callbacklen : 0)
/*****************************/

/******** 回呼选项 *********/
#define CB_USER_AUTH        0
#define CB_DIALING_STRING   1
#define CB_LOCATION_ID      2
#define CB_E_164            3
#define CB_DIST_NAME        4
/******** 回呼选项 *********/

/******** 终端描述符类型 *********/
#define LCP_DISCR_NULL          0x00
#define LCP_DISCR_LOCASSIGN     0x01
#define LCP_DISCR_IPADDR        0x02
#define LCP_DISCR_MACADDR       0x03
#define LCP_DISCR_MAGICNUM      0x04
#define LCP_DISCR_ANY           0xff
/******** 终端描述符类型 *********/


/* 协商失败后,将LCP down掉 */
#define PPP_LCP_NegotiationDown(pLcpInfo) \
    if (pLcpInfo)\
    { \
      /* 向LCP发送Close事件,即可结束协商  */ \
      PPP_LCP_ReceiveEventFromCore(pLcpInfo, (VOS_UINT32)PPP_EVENT_FSM_CLOSE, VOS_NULL_PTR) ; \
    }


/* 添加协商选项(addci)宏 */
#define ADDCIVOID(opt, neg) \
    if (neg)\
    { \
        PPP_PUTCHAR(opt, pPacket); \
        PPP_PUTCHAR(PPP_CILEN_VOID, pPacket); \
    }
#define ADDCISHORT(opt, neg, val) \
    if (neg)\
    { \
        PPP_PUTCHAR(opt, pPacket); \
        PPP_PUTCHAR(PPP_CILEN_SHORT, pPacket); \
        PPP_PUTSHORT(val, pPacket); \
    }
#define ADDCICHAP(opt, neg, val, digest) \
    if (neg) \
    { \
        PPP_PUTCHAR(opt, pPacket); \
        PPP_PUTCHAR(PPP_CILEN_CHAP, pPacket); \
        PPP_PUTSHORT(val, pPacket); \
        PPP_PUTCHAR(digest, pPacket); \
    }
#define ADDCILONG(opt, neg, val) \
    if (neg) \
    { \
        PPP_PUTCHAR(opt, pPacket); \
        PPP_PUTCHAR(PPP_CILEN_LONG, pPacket); \
        PPP_PUTLONG(val, pPacket); \
    }
#define ADDCILQR(opt, neg, val) \
    if (neg) \
    { \
        PPP_PUTCHAR(opt, pPacket); \
        PPP_PUTCHAR(PPP_CILEN_LQR, pPacket); \
        PPP_PUTSHORT((VOS_UINT16)PPP_LQR, pPacket); \
        PPP_PUTLONG(val, pPacket); \
    }

#define ADDCIDISCR(opt, neg, classno, discr_len, addr ) \
    if(neg) \
    { \
        int     i; \
        UCHAR  *pAddr; \
        PPP_PUTCHAR(opt, pPacket); \
        PPP_PUTCHAR(discr_len, pPacket); \
        PPP_PUTCHAR(classno, pPacket); \
        pAddr = (UCHAR *)addr; \
        for( i = 0; i < discr_len - 3; i++ ) \
        { \
            PPP_PUTCHAR( pAddr[ i ], pPacket ); \
        } \
    }

#define ADDCICALLBACK(opt, neg, val1, val2, ulLen)\
    if(neg) \
    { \
        PPP_PUTCHAR(opt, pPacket); \
        PPP_PUTCHAR(ulLen, pPacket); \
        PPP_PUTCHAR(val1, pPacket); \
        if(ulLen -3 > 0) \
            (VOID)VOS_MemCpy((char *)pPacket, (char *)val2, ulLen - 3) ; \
        pPacket += ulLen - 3 ; \
    }
/******************************/


/* 分析NAK报文的选项(nakci)宏 */
#define NAKCIVOID(opt, neg, code) \
    if (pstGotOptions->neg &&   ulLen >= PPP_CILEN_VOID && \
        pPacket[1] == PPP_CILEN_VOID && pPacket[0] == opt) \
    { \
        ulLen -= PPP_CILEN_VOID; \
        PPP_INCPTR(PPP_CILEN_VOID, pPacket); \
        stNoOption.neg = 1; \
        code \
    }
#define NAKCICHAP(opt, neg, code) \
    if (pstGotOptions->neg && ulLen >= PPP_CILEN_CHAP && \
        pPacket[1] == PPP_CILEN_CHAP && pPacket[0] == opt) \
    { \
        ulLen -= PPP_CILEN_CHAP; \
        PPP_INCPTR(2, pPacket); \
        PPP_GETSHORT(cishort, pPacket); \
        PPP_GETCHAR(cichar, pPacket); \
        stNoOption.neg = 1; \
        code \
    }
#define NAKCISHORT(opt, neg, code) \
    if (pstGotOptions->neg &&   ulLen >= PPP_CILEN_SHORT && \
        pPacket[1] == PPP_CILEN_SHORT && pPacket[0] == opt) \
    { \
        ulLen -= PPP_CILEN_SHORT; \
        PPP_INCPTR(2, pPacket); \
        PPP_GETSHORT(cishort, pPacket); \
        stNoOption.neg = 1; \
        code \
    }
#define NAKCILONG(opt, neg, code) \
    if (pstGotOptions->neg && ulLen >= PPP_CILEN_LONG && \
        pPacket[1] == PPP_CILEN_LONG && pPacket[0] == opt) \
    { \
        ulLen -= PPP_CILEN_LONG; \
        PPP_INCPTR(2, pPacket); \
        PPP_GETLONG(cilong, pPacket); \
        stNoOption.neg = 1; \
        code \
    }
#define NAKCILQR(opt, neg, code) \
    if (pstGotOptions->neg && ulLen >= PPP_CILEN_LQR && \
        pPacket[1] == PPP_CILEN_LQR && pPacket[0] == opt) \
    { \
        ulLen -= PPP_CILEN_LQR; \
        PPP_INCPTR(2, pPacket); \
        PPP_GETSHORT(cishort, pPacket); \
        PPP_GETLONG(cilong, pPacket); \
        stNoOption.neg = 1; \
        code \
    }
#define NAKCIDISCR(opt, neg, code) \
    if (pstGotOptions->neg && ulLen >= (PPP_CILEN_DISCR) && \
        pPacket[0] == opt ) \
    { \
        ulLen -= pPacket[1]; \
        PPP_INCPTR(3, pPacket); \
        (VOID)VOS_MemCpy((char *)(stNoOption.discr_addr),(char *)pPacket, \
                     (VOS_UINT32)(pPacket[1] - 3)) ; \
        stNoOption.neg = 1; \
        code \
    }
#define NAKCICALLBACK(opt, neg) \
    if(pstGotOptions->neg && \
       ulLen >= pstGotOptions->callbacklen && \
       pPacket[0] == opt && \
       pPacket[1] == pstGotOptions->callbacklen)\
    {\
        ulLen = (VOS_UINT32 )(ulLen - pstGotOptions->callbacklen); \
        PPP_INCPTR(2, pPacket);\
        PPP_GETCHAR(cichar, pPacket);\
        stTryOption.callbackopr = cichar; \
        (VOID)VOS_MemCpy((char *)(stTryOption.callbackinfo),(char *)pPacket, \
                     (VOS_UINT32)(pstGotOptions->callbacklen - 3)) ; \
        stNoOption.neg = 1;\
    }
/******************************/


/* 分析REJ报文的选项(rejci)宏 */
#define REJCIVOID(opt, neg) \
    if (pstGotOptions->neg && ulLen >= PPP_CILEN_VOID && \
        pPacket[1] == PPP_CILEN_VOID && pPacket[0] == opt) \
    { \
        ulLen -= PPP_CILEN_VOID; \
        PPP_INCPTR(PPP_CILEN_VOID, pPacket); \
        stTryOption.neg = 0; \
    }

#define REJCISHORT(opt, neg, val) \
    if (pstGotOptions->neg && ulLen >= PPP_CILEN_SHORT && \
        pPacket[1] == PPP_CILEN_SHORT && pPacket[0] == opt) \
    { \
        /*lint -e801*/ \
        ulLen -= PPP_CILEN_SHORT; \
        PPP_INCPTR(2, pPacket); \
        PPP_GETSHORT(cishort, pPacket); \
        /* Check rejected value. */ \
        if (cishort != val) \
            goto bad; \
        stTryOption.neg = 0; \
        /*lint +e801*/ \
    }

#define REJCICHAP(opt, neg, val, digest) \
    if (pstGotOptions->neg && ulLen >= PPP_CILEN_CHAP && \
        pPacket[1] == PPP_CILEN_CHAP && pPacket[0] == opt) \
    { \
        /*lint -e801*/ \
        ulLen -= PPP_CILEN_CHAP; \
        PPP_INCPTR(2, pPacket); \
        PPP_GETSHORT(cishort, pPacket); \
        PPP_GETCHAR(cichar, pPacket); \
        /* Check rejected value. */ \
        if (cishort != val || cichar != digest) \
            goto bad; \
        stTryOption.neg = 0; \
        stTryOption.neg_upap = 0; \
        /*lint +e801*/ \
    }


#define REJCIPAP(opt, neg, val) \
    if (pstGotOptions->neg && ulLen >= PPP_CILEN_SHORT && \
        pPacket[1] == PPP_CILEN_SHORT && pPacket[0] == opt) \
    { \
        /*lint -e801*/ \
        ulLen -= PPP_CILEN_SHORT; \
        PPP_INCPTR(2, pPacket); \
        PPP_GETSHORT(cishort, pPacket); \
        /* Check rejected value. */ \
        if (cishort != val) \
            goto bad; \
        stTryOption.neg = 0; \
        stTryOption.neg_chap = 0; \
        /*lint +e801*/ \
    }
/*End of liushuang*/

#define REJCILONG(opt, neg, val) \
    if (pstGotOptions->neg && ulLen >= PPP_CILEN_LONG && \
        pPacket[1] == PPP_CILEN_LONG && pPacket[0] == opt) \
    { \
        /*lint -e801*/ \
        ulLen -= PPP_CILEN_LONG; \
        PPP_INCPTR(2, pPacket); \
        PPP_GETLONG(cilong, pPacket); \
        /* Check rejected value. */ \
        if (cilong != val) \
            goto bad; \
        stTryOption.neg = 0; \
        /*lint +e801*/ \
    }

#define REJCILQR(opt, neg, val) \
    if (pstGotOptions->neg && ulLen >= PPP_CILEN_LQR && \
        pPacket[1] == PPP_CILEN_LQR && pPacket[0] == opt) \
    { \
        /*lint -e801*/ \
        ulLen -= PPP_CILEN_LQR; \
        PPP_INCPTR(2, pPacket); \
        PPP_GETSHORT(cishort, pPacket); \
        PPP_GETLONG(cilong, pPacket); \
        /* Check rejected value. */ \
        if (cishort != PPP_LQR || cilong != val) \
            goto bad; \
        stTryOption.neg = 0; \
        /*lint +e801*/ \
    }

#define REJCIDISCR(opt, neg, classno, discr_len, addr ) \
    if (pstGotOptions->neg && ulLen >= PPP_CILEN_DISCR && \
        pPacket[1] == discr_len && pPacket[0] == opt && pPacket[2] == classno) \
    { \
        /*lint -e801*/ \
        LONG lNotEqual ; \
        ulLen -= discr_len; \
        PPP_INCPTR(PPP_CILEN_DISCR, pPacket); \
        lNotEqual = VOS_MemCmp(pPacket, addr, (VOS_UINT32)(discr_len - PPP_CILEN_DISCR)) ; \
        PPP_INCPTR((VOS_UINT32)(discr_len - PPP_CILEN_DISCR), pPacket); \
        if(lNotEqual) \
            goto bad; \
        stTryOption.neg = 0; \
        /*lint +e801*/ \
    }
#define REJCICALLBACK(type, neg, cb_len, cb_opr, cb_msg)\
    if(pstGotOptions->neg && pPacket[0] == type && pPacket[1] == cb_len)\
    {\
        /*lint -e801*/ \
        ulLen = (VOS_UINT32 )(ulLen - cb_len); \
        PPP_INCPTR(2, pPacket); \
        PPP_GETCHAR(cichar, pPacket);\
        if(cichar != cb_opr) goto bad; \
        if(cb_len - 3)\
        { \
            LONG lNotEqual ; \
            lNotEqual = VOS_MemCmp(cb_msg, pPacket, (VOS_UINT32)(cb_len - 3)) ; \
            PPP_INCPTR((VOS_UINT32)(cb_len - 3), pPacket); \
            if(lNotEqual) \
                goto bad; \
        } \
        stTryOption.neg = 0; \
        /*lint +e801*/ \
    }
/******************************/


/* 分析ACK报文的选项(ackci)宏 */
#define ACKCIVOID(opt, neg) \
    if (neg) \
    { \
        /*lint -e801*/ \
        if ((LONG)(ulLen -= PPP_CILEN_VOID) < 0) \
            goto bad; \
        PPP_GETCHAR(citype, pPacket); \
        PPP_GETCHAR(cilen, pPacket); \
        if (cilen != PPP_CILEN_VOID || \
            citype != opt) \
            goto bad; \
            /*lint +e801*/ \
    }
#define ACKCISHORT(opt, neg, val) \
    if (neg) \
    { \
        /*lint -e801*/ \
        if ((LONG)(ulLen -= PPP_CILEN_SHORT) < 0) \
            goto bad; \
        PPP_GETCHAR(citype, pPacket); \
        PPP_GETCHAR(cilen, pPacket); \
        if (cilen != PPP_CILEN_SHORT || \
            citype != opt) \
            goto bad; \
        PPP_GETSHORT(cishort, pPacket); \
        if (cishort != val) \
            goto bad; \
        /*lint +e801*/ \
    }
#define ACKCICHAP(opt, neg, val, digest) \
    if (neg) \
    { \
        /*lint -e801*/ \
        if ((LONG)(ulLen -= PPP_CILEN_CHAP) < 0) \
            goto bad; \
        PPP_GETCHAR(citype, pPacket); \
        PPP_GETCHAR(cilen, pPacket); \
        if (cilen != PPP_CILEN_CHAP || \
            citype != opt) \
            goto bad; \
        PPP_GETSHORT(cishort, pPacket); \
        if (cishort != val) \
            goto bad; \
        PPP_GETCHAR(cichar, pPacket); \
        if (cichar != digest) \
          goto bad; \
        /*lint +e801*/ \
    }
#define ACKCILONG(opt, neg, val) \
    if (neg) \
    { \
        /*lint -e801*/ \
        if ((LONG)(ulLen -= PPP_CILEN_LONG) < 0) \
            goto bad; \
        PPP_GETCHAR(citype, pPacket); \
        PPP_GETCHAR(cilen, pPacket); \
        if (cilen != PPP_CILEN_LONG || \
            citype != opt) \
            goto bad; \
        PPP_GETLONG(cilong, pPacket); \
        if (cilong != val) \
            goto bad; \
        /*lint +e801*/ \
    }
#define ACKCILQR(opt, neg, val) \
    if (neg) \
    { \
        /*lint -e801*/ \
        if ((LONG)(ulLen -= PPP_CILEN_LQR) < 0) \
            goto bad; \
        PPP_GETCHAR(citype, pPacket); \
        PPP_GETCHAR(cilen, pPacket); \
        if (cilen != PPP_CILEN_LQR || \
            citype != opt) \
            goto bad; \
        PPP_GETSHORT(cishort, pPacket); \
        if (cishort != PPP_LQR) \
            goto bad; \
        PPP_GETLONG(cilong, pPacket); \
        if (cilong != val) \
          goto bad; \
          /*lint +e801*/ \
    }
#define ACKCIDISCR(opt, neg, classno, discr_len, addr ) \
    if(neg) \
    { \
        /*lint -e801*/ \
        UCHAR  *pAddr; \
        int     i; \
        if ((LONG)(ulLen -= (discr_len) ) < 0) \
            goto bad; \
        PPP_GETCHAR(citype, pPacket); \
        PPP_GETCHAR(cilen, pPacket); \
        if (cilen != (discr_len) || \
            citype != opt) \
            goto bad; \
        PPP_GETCHAR(cichar, pPacket); \
        if (cichar != classno ) \
            goto bad; \
        pAddr = (UCHAR *)addr; \
        for( i = 0; i < discr_len - PPP_CILEN_DISCR; i++ ) \
        { \
            PPP_GETCHAR(cichar, pPacket); \
            if( pAddr[ i ] != cichar ) \
                goto bad; \
        } \
        /*lint +e801*/ \
    }
#define ACKCALLBACK(opt, neg, val1, val2, val3) \
    if(neg) \
    { \
        /*lint -e801*/ \
        PPP_GETCHAR(citype, pPacket); \
        PPP_GETCHAR(cilen, pPacket); \
        if(cilen != val3  || citype != opt)\
            goto bad; \
        ulLen = (VOS_UINT32)( ulLen - cilen); \
        if((LONG)ulLen < 0) goto bad; \
        PPP_GETCHAR(cichar, pPacket); \
        if(val1 != cichar )\
            goto bad; \
        if(cilen - 3) \
        { \
            LONG lNotEqual ; \
            lNotEqual = VOS_MemCmp(val2, pPacket, (VOS_UINT32)(cilen - 3)) ; \
            PPP_INCPTR((VOS_UINT32)(cilen - 3), pPacket); \
            if(lNotEqual) \
                goto bad; \
        } \
        /*lint +e801*/ \
    }
/******************************/


#ifdef      __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _LCP_DEF_H_ */




