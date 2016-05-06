/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                             ppp_lcp_type.h
 *
 *  Project Code: VISP1.5
 *   Module Name: PPP
 *  Date Created: 2000-04-04
 *        Author: DengYiou
 *   Description: PPP的LCP协议处理模块数据结构
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2000-04-04      DengYiou        Create
 *  2004-07-01      YiAn            Modified for VISP
 *  2006-03-31      ZhuKun          Adjust for D00661
 *  2006-04-21      ZhuKun          Adjust for D00875
 *  2006-05-11      luyao           为支持ARM CPU字节对齐特性，修改结构。
 *
 ************************************************************************/

#ifndef _LCP_TYPE_H_
#define _LCP_TYPE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ppp/include/ppp_api.h"

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
#define LCP_CI_MHF              27  /* MHF */
#define LCP_CI_PREFIXE          26  /* PREFIX-ELISION */
/* End of addition */
/***************/


/* LCP自定义类型 */
#define ECHOREQ         9   /* Echo Request */
#define ECHOREP         10  /* Echo Reply */
#define DISCREQ         11  /* Discard Request */
#define IDENTIFIC       12  /* Identification */
#define TIMEREMAIN      13  /* Time remaining */
/*****************/

/* 用于对应g_cPPP_Debug_LcpOption中的单元 */
#define LCP_TYPENAMEINDEX_MRRU        9        /* the index of LCP CI MRRU */
#define LCP_TYPENAMEINDEX_SSNHF       10       /* the index of LCP CI SSNHF */
#define LCP_TYPENAMEINDEX_DISCR       11       /* the index of LCP CI DISCR */
#define LCP_TYPENAMEINDEX_CALLBACK    12       /* the index of LCP CI CALLBACK */
#define LCP_TYPENAMEINDEX_MHF         13       /* the index of LCP CI MHF */
#define LCP_TYPENAMEINDEX_PREFIXE     14       /* the index of LCP CI PREFIX-ELISION */
/* End of addition */

#define LCP_MAGICNUM_LEN              4        /* the magic number length */
#define LCP_DISCREQ_LEN               12       /* special discard request frame length */

/* 各协商选项长度 */
#define PPP_CILEN_CHAP      5   /* PPP_CILEN_VOID + sizeof(short) + 1 */
#define PPP_CILEN_LQR       8   /* PPP_CILEN_VOID + sizeof(short) + sizeof(long) */
#define PPP_CILEN_DISCR     3   /* PPP_CILEN_VOID + Class. (also the minimum length of Discriminator) */
#define PPP_CILEN_CALLBACK  3   /* PPP_CILEN_VOID + Operation. (also the minimum length of callback) */
/******************/


/* 获取协商选项长度(cilen)宏 */
#define PPP_LENCICHAP(neg)   (neg ? PPP_CILEN_CHAP : 0)
#define PPP_LENCILQR(neg)    (neg ? PPP_CILEN_LQR : 0)
#define PPP_LENCIDISCR(neg)  (neg ? pstGotOptions->discr_len : 0)
#define PPP_LENCALLBACK(neg) (neg ? pstGotOptions->callbacklen : 0)
#define PPP_LENCIPREFIXE(neg) (neg ? pstGotOptions->ucPrefixELen : 0)
/* End of addition */
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
/*Added by f54882, 2007-2-2, HDLC自动侦听非标需求开发*/
#define LCP_DISCR_TELENUM       0x05
#define LCP_DISCR_ANY           0xff
/******** 终端描述符类型 *********/


/* 协商失败后,将LCP down掉 */
#define PPP_LCP_NegotiationDown(pLcpInfo) \
    if (pLcpInfo)\
    { \
      /* 向LCP发送Close事件,即可结束协商  */ \
      PPP_LCP_ReceiveEventFromCore(pLcpInfo, (ULONG)PPP_EVENT_FSM_CLOSE, NULL); \
    }


/* 将本端支持的所有前缀省略映射填充到报文中 */
#define PPP_PUTPREFIXE(astPrefixE, pPacket,len)\
{ \
    MC_PREFIXE_S *pstPrefixE = NULL;\
    UCHAR         i = 0;\
    UCHAR        *pPacketTemp = NULL;\
    PPP_PUTCHAR( LCP_CI_PREFIXE, pPacket );\
    /* 记录报文中存放选项长度的位置，等后面计算出相应的选项总长度后，再填入该字节 */\
    pPacketTemp = pPacket;\
    PPP_INCPTR(1, pPacket);\
    for ( i = 0; i < MC_PREFIXE_MAX_NUM; i++ )\
    {\
        pstPrefixE = &(astPrefixE[i]);\
        if ( pstPrefixE->ucIsUsedFlag )\
        {\
            PPP_PUTCHAR( pstPrefixE->ucClass, pPacket );\
            PPP_PUTCHAR( pstPrefixE->ucPrefixELen, pPacket );\
            (VOID)TCPIP_Mem_Copy( pPacket, pstPrefixE->ucPrefixELen, pstPrefixE->aucPrefixE, pstPrefixE->ucPrefixELen );\
            PPP_INCPTR( pstPrefixE->ucPrefixELen, pPacket );\
            /* 前缀总长度 += 前缀等级+前缀长度+前缀字段 */\
            len = (UCHAR)( len + pstPrefixE->ucPrefixELen + PPP_CILEN_VOID );\
        }\
    }\
    /* 计算选项长度:选项总长度 = 选项类型+选项长度+前缀总长度 */\
    len = (UCHAR)(len + PPP_CILEN_VOID);\
    /* 在报文中填入选项长度 */\
    PPP_PUTCHAR( len, pPacketTemp ); \
}
/* End of addition */

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
        PPP_PUTSHORT((USHORT)PPP_LQR, pPacket); \
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
        if ((ulLen - 3) > 0) \
        { \
            (VOID)TCPIP_Mem_Copy((char *)pPacket, ulLen - 3, (char *)val2, ulLen - 3); \
        } \
        pPacket += (ulLen - 3); \
    }

#define ADDCIMHF( opt, neg, mhfcode, mhfclass ) \
    if (neg)\
    { \
        PPP_PUTCHAR(opt, pPacket); \
        PPP_PUTCHAR(PPP_CILEN_SHORT, pPacket); \
        PPP_PUTCHAR(mhfcode, pPacket);\
        PPP_PUTCHAR(mhfclass, pPacket);\
    }

/* Req报文中Prefix-Elision选项格式 */
/* 格式1:
   0                 16                     
   +++++++++++++++++++
   |  Type  | Length | 
   +++++++++++++++++++
   格式2:
   0                 16                  32    
   ++++++++++++++++++++++++++++++++++++++++
   |  Type  | Length | Class | PrefixELen |
   ----------------------------------------
   |  Prefix-E field ....                 |
   ----------------------------------------
   |                 ....                 |
   ++++++++++++++++++++++++++++++++++++++++
*/
#define ADDCIPREFIXE( opt, neg, astPrefixE, prefixElen )\
    if (neg)\
    { \
        /* 将记录的选项长度清0 */\
        prefixElen = 0;\
        /* 在REQ报文中填充Prefix-Elision选项 */\
        PPP_PUTPREFIXE(astPrefixE, pPacket, prefixElen);\
    }
/* End of addition */  
/******************************/


/* 分析NAK报文的选项(nakci)宏 */
#define NAKCIVOID(opt, neg, code) \
    if ( pstGotOptions->neg && (ulLen >= PPP_CILEN_VOID) && \
        (PPP_CILEN_VOID == pPacket[1]) && (pPacket[0] == opt) ) \
    { \
        ulLen -= PPP_CILEN_VOID; \
        PPP_INCPTR(PPP_CILEN_VOID, pPacket); \
        stNoOption.neg = 1; \
        code \
    }
#define NAKCICHAP(opt, neg, code) \
    if ( pstGotOptions->neg && (ulLen >= PPP_CILEN_CHAP) && \
        (PPP_CILEN_CHAP == pPacket[1]) && (pPacket[0] == opt) ) \
    { \
        ulLen -= PPP_CILEN_CHAP; \
        PPP_INCPTR(2, pPacket); \
        PPP_GETSHORT(cishort, pPacket); \
        PPP_GETCHAR(cichar, pPacket); \
        stNoOption.neg = 1; \
        code \
    }
#define NAKCISHORT(opt, neg, code) \
    if ( pstGotOptions->neg && (ulLen >= PPP_CILEN_SHORT) && \
        (PPP_CILEN_SHORT == pPacket[1]) && (pPacket[0] == opt) ) \
    { \
        ulLen -= PPP_CILEN_SHORT; \
        PPP_INCPTR(2, pPacket); \
        PPP_GETSHORT(cishort, pPacket); \
        stNoOption.neg = 1; \
        code \
    }
#define NAKCILONG(opt, neg, code) \
    if ( pstGotOptions->neg && (ulLen >= PPP_CILEN_LONG) && \
        (PPP_CILEN_LONG == pPacket[1]) && (pPacket[0] == opt) ) \
    { \
        ulLen -= PPP_CILEN_LONG; \
        PPP_INCPTR(2, pPacket); \
        PPP_GETLONG(cilong, pPacket); \
        stNoOption.neg = 1; \
        code \
    }
#define NAKCILQR(opt, neg, code) \
    if ( pstGotOptions->neg && (ulLen >= PPP_CILEN_LQR) && \
        (PPP_CILEN_LQR == pPacket[1]) && (pPacket[0] == opt) ) \
    { \
        ulLen -= PPP_CILEN_LQR; \
        PPP_INCPTR(2, pPacket); \
        PPP_GETSHORT(cishort, pPacket); \
        PPP_GETLONG(cilong, pPacket); \
        stNoOption.neg = 1; \
        code \
    }
#define NAKCIDISCR(opt, neg, code) \
    if ( pstGotOptions->neg && (ulLen >= PPP_CILEN_DISCR) && \
        (pPacket[0] == opt) ) \
    { \
        UCHAR ucTempLen = pPacket[1]; \
        ulLen -= pPacket[1]; \
        PPP_INCPTR(3, pPacket); \
        if ((ucTempLen > 3) && ((ucTempLen-3) <= PPP_MP_DISCR_MAX_LENGTH))\
        {\
        (VOID)TCPIP_Mem_Copy((char *)(stNoOption.discr_addr), (ULONG)(ucTempLen - 3), (char *)pPacket, (ULONG)(ucTempLen - 3)); \
        }\
        else\
        {\
            goto bad;\
        }\
        stNoOption.neg = 1; \
        code \
    }
#define NAKCICALLBACK(opt, neg) \
    if ( pstGotOptions->neg && \
        (ulLen >= pstGotOptions->callbacklen) && \
        (pPacket[0] == opt) && \
        (pPacket[1] == pstGotOptions->callbacklen) )\
    {\
        ulLen = (ULONG )(ulLen - pstGotOptions->callbacklen); \
        PPP_INCPTR(2, pPacket);\
        PPP_GETCHAR(cichar, pPacket);\
        stTryOption.callbackopr = cichar; \
        (VOID)TCPIP_Mem_Copy((char *)(stTryOption.callbackinfo), (ULONG)(pstGotOptions->callbacklen - 3), (char *)pPacket, (ULONG)(pstGotOptions->callbacklen - 3)); \
        stNoOption.neg = 1;\
    }
/* Modified by z43740: 异常情况下，下次不再协商MHF选项,2006/06/08 */
#define NAKCIMHF(opt, neg, mhfcode, mhfclass) \
    if (pstGotOptions->neg && ulLen >= PPP_CILEN_SHORT && \
        PPP_CILEN_SHORT == pPacket[1] && opt == pPacket[0] ) \
    { \
        ulLen -= PPP_CILEN_SHORT; \
        PPP_INCPTR(PPP_CILEN_VOID, pPacket); \
        PPP_GETCHAR(ucCode, pPacket); \
        PPP_GETCHAR(ucClass, pPacket); \
        /* 如果对端只NAK本端的class值，如果该class值在0~本端希望协商的class值之间，\
           则接受对端NAK的值 */ \
        if ( ucCode == pstWantOptions->ucMhfCode )\
        {\
            if(ucClass > 0 && ucClass <= pstWantOptions->ucMhfClass)\
            {\
                stTryOption.ucMhfCode = ucCode; \
                stTryOption.ucMhfClass = ucClass; \
            }\
            else\
            {\
                stTryOption.neg = 0;\
            }\
        }\
        /* 如果对端NAK了本端code和class值，如果code合法，且class在相应允许的范围内，\
           则接受对端NAK的值 */ \
        else if ( MC_LSN_CODE == ucCode )\
        {\
            if(ucClass > 0 && ucClass <= MC_MAX_LSCLASS)\
            {\
                stTryOption.ucMhfCode = ucCode;\
                stTryOption.ucMhfClass = ucClass; \
            }\
            else\
            {\
                stTryOption.neg = 0;\
            }\
        }\
        else if ( MC_SSN_CODE == ucCode )\
        {\
            if(ucClass > 0 && ucClass <= MC_MAX_SSCLASS)\
            {\
                stTryOption.ucMhfCode = ucCode;\
                stTryOption.ucMhfClass = ucClass; \
            }\
            else\
            {\
                stTryOption.neg = 0;\
            }\
        }\
        else\
        {\
            stTryOption.neg = 0;\
        }\
        stNoOption.neg = 1; \
    }

/* Nak报文中Prefix-Elision选项格式 */
/* 格式1:
   0                 16                     
   +++++++++++++++++++
   |  Type  | Length | 
   +++++++++++++++++++
   格式2:
   0                 16                  32    
   ++++++++++++++++++++++++++++++++++++++++
   |  Type  | Length | Class | PrefixELen |
   ----------------------------------------
   |  Prefix-E field ....                 |
   ----------------------------------------
   |                 ....                 |
   ++++++++++++++++++++++++++++++++++++++++
*/
#define NAKCIPREFIXE(opt, neg) \
    if ( pstGotOptions->neg \
         && opt == pPacket[0] \
         && pPacket[1] >= PPP_CILEN_VOID \
         && ulLen >= pPacket[1] ) \
    { \
        MC_PREFIXE_S *pstPrefixEInfo = NULL; \
        UCHAR         ucCIClass = 0; \
        UCHAR         ucCIPreELen = 0; \
        /* 在NAK报文中我们接受的前缀省略映射对数 */\
        UCHAR         ucPrefixESum = 0;\
        /* 获取选项长度 */\
        cilen = pPacket[1]; \
        ulLen -= cilen;\
        /* 选项长度减去类型和长度占的两个字节 */\
        cilen -= PPP_CILEN_VOID;\
        PPP_INCPTR( PPP_CILEN_VOID, pPacket ); \
        /* 报文格式1,作为拒绝该选项处理，下次不再协商该选项 */\
        if ( 0 == cilen )\
        {\
            stTryOption.neg_prefixE = 0;\
        }\
        /* 报文格式2 */\
        else\
        {\
            while ( cilen >= PPP_CILEN_VOID ) \
            { \
                PPP_GETCHAR( ucCIClass, pPacket );\
                PPP_GETCHAR( ucCIPreELen, pPacket );\
                /* 剩余选项长度 - 等级和长度所占两字节 - 前缀省略字段长度 */\
                if ((cilen = (SHORT)(cilen - ucCIPreELen - PPP_CILEN_VOID)) < 0)\
                    goto bad;\
                if ( ucCIClass < MC_PREFIXE_MAX_NUM \
                     && ucCIPreELen > 0\
                     && ucCIPreELen <= MC_PREFIXE_MAX_STR \
                   )\
                {\
                    ucPrefixESum++;\
                    pstPrefixEInfo = &(stTryOption.pstPrefixE[ucCIClass]); \
                    pstPrefixEInfo->ucIsUsedFlag = PREFIX_E_IS_USED; \
                    pstPrefixEInfo->ucClass = ucCIClass;\
                    pstPrefixEInfo->ucPrefixELen = ucCIPreELen;\
                    (VOID)TCPIP_Mem_Copy( pstPrefixEInfo->aucPrefixE, MC_PREFIXE_MAX_STR, pPacket, ucCIPreELen );\
                }\
                /* 移动报文指针，解析下一个等级的前缀省略；\
                   如果该等级和省略字段长度不在本端允许范围内，或NAK的前缀长度为0，\
                   也直接解析下一个等级的前缀省略 */\
                PPP_INCPTR( ucCIPreELen, pPacket );\
            }\
            if ( cilen != 0 )\
            {\
                goto bad;\
            }\
            /* 如果NAK报文中的值都不符合本端要求(即本端没有接受任何一个NAK值)，\
               则作为拒绝该选项处理,下次不再协商该选项 */\
            if ( 0 == ucPrefixESum )\
            {\
                stTryOption.neg_prefixE = 0;\
            }\
        }\
        stNoOption.neg_prefixE = 1; \
    }
 /* End of addition */
/******************************/


/* 分析REJ报文的选项(rejci)宏 */
#define REJCIVOID(opt, neg) \
    if ( pstGotOptions->neg && (ulLen >= PPP_CILEN_VOID) && \
        (PPP_CILEN_VOID == pPacket[1]) && (pPacket[0] == opt) ) \
    { \
        ulLen -= PPP_CILEN_VOID; \
        PPP_INCPTR(PPP_CILEN_VOID, pPacket); \
        stTryOption.neg = 0; \
    }

#define REJCISHORT(opt, neg, val) \
    if ( pstGotOptions->neg && (ulLen >= PPP_CILEN_SHORT) && \
        (PPP_CILEN_SHORT == pPacket[1]) && (pPacket[0] == opt) ) \
    { \
        ulLen -= PPP_CILEN_SHORT; \
        PPP_INCPTR(2, pPacket); \
        PPP_GETSHORT(cishort, pPacket); \
        /* Check rejected value. */ \
        if (cishort != val) \
        { \
            goto bad; \
        } \
        stTryOption.neg = 0; \
    }

#define REJCICHAP(opt, neg, val, digest) \
    if ( pstGotOptions->neg && (ulLen >= PPP_CILEN_CHAP) && \
        (PPP_CILEN_CHAP == pPacket[1]) && (pPacket[0] == opt) ) \
    { \
        ulLen -= PPP_CILEN_CHAP; \
        PPP_INCPTR(2, pPacket); \
        PPP_GETSHORT(cishort, pPacket); \
        PPP_GETCHAR(cichar, pPacket); \
        /* Check rejected value. */ \
        if ((cishort != val) || (cichar != digest)) \
        { \
            goto bad; \
        } \
        stTryOption.neg = 0; \
\
        /*stTryOption.neg_upap = 0; */\
        /*在chap选项被拒时发一次pap选项的请求*/\
    }

#define REJCILONG(opt, neg, val) \
    if ( pstGotOptions->neg && (ulLen >= PPP_CILEN_LONG) && \
        (PPP_CILEN_LONG == pPacket[1]) && (pPacket[0] == opt) ) \
    { \
        ulLen -= PPP_CILEN_LONG; \
        PPP_INCPTR(2, pPacket); \
        PPP_GETLONG(cilong, pPacket); \
        /* Check rejected value. */ \
        if (cilong != val) \
        { \
            goto bad; \
        } \
        stTryOption.neg = 0; \
    }

#define REJCILQR(opt, neg, val) \
    if ( pstGotOptions->neg && (ulLen >= PPP_CILEN_LQR) && \
        (PPP_CILEN_LQR == pPacket[1]) && (pPacket[0] == opt) ) \
    { \
        ulLen -= PPP_CILEN_LQR; \
        PPP_INCPTR(2, pPacket); \
        PPP_GETSHORT(cishort, pPacket); \
        PPP_GETLONG(cilong, pPacket); \
        /* Check rejected value. */ \
        if ((cishort != PPP_LQR) || (cilong != val)) \
        { \
            goto bad; \
        } \
        stTryOption.neg = 0; \
    }

#define REJCIDISCR(opt, neg, classno, discr_len, addr ) \
    if ( pstGotOptions->neg && (ulLen >= PPP_CILEN_DISCR) && \
        (pPacket[1] == discr_len) && (pPacket[0] == opt) && (pPacket[2] == classno) ) \
    { \
        LONG lNotEqual = 0; \
        ulLen -= discr_len; \
        PPP_INCPTR(PPP_CILEN_DISCR, pPacket); \
        (VOID)VOS_Mem_Cmp((VOID*)pPacket, (VOID*)addr, (VOS_UINT32)(discr_len - PPP_CILEN_DISCR), &lNotEqual); \
        PPP_INCPTR((ULONG)(discr_len - PPP_CILEN_DISCR), pPacket); \
        if(lNotEqual) \
        { \
            goto bad; \
        } \
        stTryOption.neg = 0; \
    }
#define REJCICALLBACK(type, neg, cb_len, cb_opr, cb_msg)\
    if(pstGotOptions->neg && (pPacket[0] == type) && (pPacket[1] == cb_len))\
    {\
        ulLen = (ULONG )(ulLen - cb_len); \
        PPP_INCPTR(2, pPacket); \
        PPP_GETCHAR(cichar, pPacket);\
        if(cichar != cb_opr) \
        { \
            goto bad; \
        } \
        if(cb_len - PPP_CILEN_CALLBACK)\
        { \
            LONG lNotEqual = 0; \
            (VOID)VOS_Mem_Cmp((VOID*)cb_msg, (VOID*)pPacket, (VOS_UINT32)(cb_len - PPP_CILEN_CALLBACK), &lNotEqual); \
            PPP_INCPTR((ULONG)(cb_len - PPP_CILEN_CALLBACK), pPacket); \
            if(lNotEqual) \
            { \
                goto bad; \
            } \
        } \
        stTryOption.neg = 0; \
    }
#define REJCIMHF(opt, neg, mhfcode, mhfclass) \
    if (pstGotOptions->neg && ulLen >= PPP_CILEN_SHORT \
        && PPP_CILEN_SHORT == pPacket[1] && pPacket[0] == opt)\
    { \
        ulLen -= PPP_CILEN_SHORT; \
        PPP_INCPTR(PPP_CILEN_VOID, pPacket); \
        PPP_GETCHAR(cichar, pPacket); \
        if (cichar != mhfcode) \
        {\
            goto bad; \
        }\
        PPP_GETCHAR(cichar, pPacket); \
        if (cichar != mhfclass) \
        {\
            goto bad; \
        }\
        stTryOption.neg = 0; \
        stTryOption.ucMhfCode = 0; \
        stTryOption.ucMhfClass = 0;\
    }

/* Rej报文中Prefix-Elision选项格式 */
/* 格式1:
   0                 16                     
   +++++++++++++++++++
   |  Type  | Length | 
   +++++++++++++++++++
   格式2:
   0                 16                  32    
   ++++++++++++++++++++++++++++++++++++++++
   |  Type  | Length | Class | PrefixELen |
   ----------------------------------------
   |  Prefix-E field ....                 |
   ----------------------------------------
   |                 ....                 |
   ++++++++++++++++++++++++++++++++++++++++
*/
#define REJCIPREFIXE(opt, neg)\
    if ( pstGotOptions->neg && opt == pPacket[0] \
         && pPacket[1] >= PPP_CILEN_VOID && ulLen >= pPacket[1] ) \
    { \
        LONG  lRet = 0;\
        UCHAR ucCiLenTemp = 0;\
        UCHAR aucBufTemp[LEN_256] = {0};\
        UCHAR *pucRejPacket = NULL;\
        pucRejPacket = aucBufTemp;\
        cichar = pPacket[1];\
        ulLen -= (ULONG)cichar;\
        /* 临时组装一个Prefix-Elision选项的REQ报文 \
          (即此临时报文与之前发送的REQ中的Prefix-Elison选项内容一致) \
           以此判定REJ报文中Prefix-Elision选项的内容是否跟REQ报文中的一致 */ \
        PPP_PUTPREFIXE(pstGotOptions->pstPrefixE, pucRejPacket, ucCiLenTemp);\
        /* 如果选项长度就不等于临时组件的REQ报文的选项长度，则直接视为非法报文 */ \
        if ( cichar != ucCiLenTemp ) \
        {\
            goto bad; \
        }\
        /* 比较ACK报文中的该选项内容是否跟临时组件的REQ报文中的一致 */\
        (VOID)VOS_Mem_Cmp( (VOID*)pPacket, (VOID*)aucBufTemp, (VOS_UINT32)cichar, &lRet );\
        if ( lRet )\
        {\
            goto bad; \
        }\
        /* REJ报文中的此选项解析正确，报文指向下一个选项 */ \
        PPP_INCPTR( cichar, pPacket );\
        stTryOption.neg = 0;\
    }
/* End of addition */
/******************************/


/* 分析ACK报文的选项(ackci)宏 */
#define ACKCIVOID(opt, neg) \
    if (neg) \
    { \
        if ((LONG)(ulLen -= PPP_CILEN_VOID) < 0) \
        { \
            goto bad; \
        } \
        PPP_GETCHAR(citype, pPacket); \
        PPP_GETCHAR(cilen, pPacket); \
        if ((cilen != PPP_CILEN_VOID) || (citype != opt)) \
        { \
            goto bad; \
        } \
    }
#define ACKCISHORT(opt, neg, val) \
    if (neg) \
    { \
        if ((LONG)(ulLen -= PPP_CILEN_SHORT) < 0) \
        { \
            goto bad; \
        } \
        PPP_GETCHAR(citype, pPacket); \
        PPP_GETCHAR(cilen, pPacket); \
        if ((cilen != PPP_CILEN_SHORT) || (citype != opt)) \
        { \
            goto bad; \
        } \
        PPP_GETSHORT(cishort, pPacket); \
        if (cishort != val) \
        { \
            goto bad; \
        } \
    }
#define ACKCICHAP(opt, neg, val, digest) \
    if (neg) \
    { \
        if ((LONG)(ulLen -= PPP_CILEN_CHAP) < 0) \
        { \
            goto bad; \
        } \
        PPP_GETCHAR(citype, pPacket); \
        PPP_GETCHAR(cilen, pPacket); \
        if ((cilen != PPP_CILEN_CHAP) || (citype != opt)) \
        { \
            goto bad; \
        } \
        PPP_GETSHORT(cishort, pPacket); \
        if (cishort != val) \
        { \
            goto bad; \
        } \
        PPP_GETCHAR(cichar, pPacket); \
        if (cichar != digest) \
        { \
            goto bad; \
        } \
    }
#define ACKCILONG(opt, neg, val) \
    if (neg) \
    { \
        if ((LONG)(ulLen -= PPP_CILEN_LONG) < 0) \
        { \
            goto bad; \
        } \
        PPP_GETCHAR(citype, pPacket); \
        PPP_GETCHAR(cilen, pPacket); \
        if ((cilen != PPP_CILEN_LONG) || (citype != opt)) \
        { \
            goto bad; \
        } \
        PPP_GETLONG(cilong, pPacket); \
        if (cilong != val) \
        { \
            goto bad; \
        } \
    }
#define ACKCILQR(opt, neg, val) \
    if (neg) \
    { \
        if ((LONG)(ulLen -= PPP_CILEN_LQR) < 0) \
        { \
            goto bad; \
        } \
        PPP_GETCHAR(citype, pPacket); \
        PPP_GETCHAR(cilen, pPacket); \
        if ((cilen != PPP_CILEN_LQR) || (citype != opt)) \
        { \
            goto bad; \
        } \
        PPP_GETSHORT(cishort, pPacket); \
        if (cishort != PPP_LQR) \
        { \
            goto bad; \
        } \
        PPP_GETLONG(cilong, pPacket); \
        if (cilong != val) \
        { \
            goto bad; \
        } \
    }
#define ACKCIDISCR(opt, neg, classno, discr_len, addr ) \
    if(neg) \
    { \
        UCHAR  *pAddr; \
        int     i; \
        if ((LONG)(ulLen -= (discr_len)) < 0) \
        { \
            goto bad; \
        } \
        PPP_GETCHAR(citype, pPacket); \
        PPP_GETCHAR(cilen, pPacket); \
        if ((cilen != (discr_len)) || (citype != opt)) \
        { \
            goto bad; \
        } \
        PPP_GETCHAR(cichar, pPacket); \
        if (cichar != classno ) \
        { \
            goto bad; \
        } \
        pAddr = (UCHAR *)addr; \
        for( i = 0; i < discr_len - PPP_CILEN_DISCR; i++ ) \
        { \
            PPP_GETCHAR(cichar, pPacket); \
            if( pAddr[ i ] != cichar ) \
            { \
                goto bad; \
            } \
        } \
    }
#define ACKCALLBACK(opt, neg, val1, val2, val3) \
    if(neg) \
    { \
        PPP_GETCHAR(citype, pPacket); \
        PPP_GETCHAR(cilen, pPacket); \
        if((cilen != val3) || (citype != opt))\
        { \
            goto bad; \
        } \
        ulLen = (ULONG)(ulLen - cilen); \
        if((LONG)ulLen < 0) \
        { \
            goto bad; \
        } \
        PPP_GETCHAR(cichar, pPacket); \
        if(val1 != cichar)\
        { \
            goto bad; \
        } \
        if(cilen - 3) \
        { \
            LONG lNotEqual = 0; \
            (VOID)VOS_Mem_Cmp((VOID*)val2, (VOID*)pPacket, (VOS_UINT32)(cilen - 3), &lNotEqual); \
            PPP_INCPTR((ULONG)(cilen - 3), pPacket); \
            if(lNotEqual) \
            { \
                goto bad; \
            } \
        } \
    }

#define ACKCIMHF(opt, neg, mhfcode, mhfclass) \
    if (neg) \
    { \
        if ((LONG)(ulLen -= PPP_CILEN_SHORT) < 0) \
        {\
            goto bad; \
        }\
        PPP_GETCHAR(citype, pPacket); \
        PPP_GETCHAR(cilen, pPacket); \
        if (PPP_CILEN_SHORT != cilen || citype != opt) \
        {\
            goto bad; \
        }\
        PPP_GETCHAR(cichar, pPacket); \
        if (cichar != mhfcode) \
        {\
            goto bad; \
        }\
        PPP_GETCHAR(cichar, pPacket); \
        if (cichar != mhfclass) \
        {\
            goto bad; \
        }\
    }

/* Ack报文中Prefix-Elision选项格式 */
/* 0                 16                  32    
   ++++++++++++++++++++++++++++++++++++++++
   |  Type  | Length | Class | PrefixELen |
   ----------------------------------------
   |  Prefix-E field ....                 |
   ----------------------------------------
   |                 ....                 |
   ++++++++++++++++++++++++++++++++++++++++
*/
#define ACKCIPREFIXE( opt, neg, astPrefixE ) \
    if (neg)\
    { \
        LONG  lRet = 0;\
        UCHAR ucCiLenTemp = 0;\
        UCHAR aucBufTemp[LEN_256] = {0};\
        UCHAR *pucAckPacket = NULL;\
        pucAckPacket = aucBufTemp;\
        citype = pPacket[0];\
        cilen = pPacket[1];\
        if ((LONG)(ulLen -= cilen) < 0 || citype != opt ) \
        {\
            goto bad; \
        }\
        /* 临时组装一个Prefix-Elision选项的REQ报文(即此报文与发送的REQ中的Prefix-Elison选项内容一致) \
           来确定ACK报文中Prefix-Elision选项的内容是否跟REQ报文中的一致 */ \
        PPP_PUTPREFIXE(astPrefixE, pucAckPacket, ucCiLenTemp);\
        /* 如果选项长度就不等于临时组件的REQ报文的选项长度，则直接视为非法报文 */ \
        if ( cilen != ucCiLenTemp ) \
        {\
            goto bad; \
        }\
        /* 比较ACK报文中的该选项内容是否跟临时组件的REQ报文中的一致 */\
        (VOID)VOS_Mem_Cmp( (VOID*)pPacket, (VOID*)aucBufTemp, (VOS_UINT32)cilen, &lRet );\
        if ( lRet )\
        {\
            goto bad; \
        }\
        /* ACK报文中的此选项解析正确，报文指向下一个选项 */ \
        PPP_INCPTR( cilen, pPacket );\
    }
/* End of addition */
/******************************/




typedef struct tagPppLcpInfo
{
    PPPINFO_S *pstPppInfo;            /* PPP控制块指针 */
    PPPFSM_S  stFsm;                  /* LCP协议状态机 */
    PPP_LCP_OPTION_S stGotOptions;    /* 已经与对方协商成功的我的选项 */
    PPP_LCP_OPTION_S stHisOptions;    /* 已经与我协商成功的对方的选项 */
    PPP_LCP_OPTION_S stWantOptions;   /* 我希望与对方协商的我的选项 */
    PPP_LCP_OPTION_S stAllowOptions;  /* 允许对方与我协商的我的选项 */
} PPPLCPINFO_S;

/* 接口函数 */
VOID PPP_LCP_Init(PPPINFO_S *);
VOID PPP_LCP_ReceiveEventFromCore (VOID *pstLcpInfo, ULONG ulCmd, char *pPara);
VOID PPP_LCP_ReceivePacket (VOID *pstLcpInfo, UCHAR* pHead, UCHAR* pPacket, ULONG ulLen);

/* 回调函数 */
VOID PPP_LCP_resetci(PPPFSM_S *f);
USHORT PPP_LCP_cilen(PPPFSM_S *);
VOID PPP_LCP_addci(PPPFSM_S *, UCHAR *);
USHORT PPP_LCP_ackci(PPPFSM_S *, UCHAR *, ULONG);
USHORT PPP_LCP_nakci(PPPFSM_S *, UCHAR *, ULONG);
USHORT PPP_LCP_rejci(PPPFSM_S *, UCHAR *, ULONG);
UCHAR PPP_LCP_reqci(PPPFSM_S *, UCHAR *, ULONG *);
USHORT PPP_LCP_extcode(PPPFSM_S *, UCHAR, UCHAR, UCHAR *, UCHAR *, ULONG);
VOID PPP_LCP_up(PPPFSM_S *);
VOID PPP_LCP_down(PPPFSM_S *);
VOID PPP_LCP_finished(PPPFSM_S *);
VOID PPP_LCP_starting(PPPFSM_S *);

/* 内部处理函数 */
VOID PPP_LCP_SendEchoRequest(PPPFSM_S *);
VOID PPP_LCP_ReceiveEchoReply(PPPFSM_S *, UCHAR, UCHAR *, ULONG);
VOID PPP_LCP_EchoTimeOut(VOID *);
ULONG PPP_LCP_UpResetCi(PPPINFO_S *);
ULONG PPP_LCP_upcheck(PPPFSM_S *pstFsm);

VOID PPP_LCP_ReceiveDiscReq(PPPFSM_S *pstFsm, UCHAR ucId, UCHAR *pPacket, ULONG ulLen);
/* Add for DTS2011042101452, by z00166124, at 2011-04-21. 修改原因: 定时器传入接口索引指针 */
VOID PPP_Ncp_Reset(VOID * pstFsm);
VOID PPP_LCP_FSM_TimeOut(VOID *pIfIndex);

#ifdef __cplusplus
}
#endif

#endif
