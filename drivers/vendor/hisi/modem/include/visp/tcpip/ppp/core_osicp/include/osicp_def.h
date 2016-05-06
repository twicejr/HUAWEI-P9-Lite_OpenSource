/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                              osicp_d.c
 *
 *  Project Code: VISPV1R6C03
 *   Module Name: osicp
 *  Date Created: 2007-07-11
 *        Author: Zhangchunyu
 *   Description: PPP的OSICP协议模块私有宏定义  
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2007-07-11      Zhangchunyu        Create
 *
 *************************************************************************/

#ifndef      _OSICP_DEF_H_
#define      _OSICP_DEF_H_

#ifdef      __cplusplus
extern "C" {
#endif		/* end of __cplusplus */

#define MID_OSICP     g_stOSICPModInfo.ulMID_OSICP

/* Align_NPDU缺省值 */
#define OSICP_DEFAULT_ALIGN_NPDU 1
/******************************/

/* OSICP协商选项 */
#define OSICP_CI_ALIGN_NPDU     1 /* Align-NPDU */
/******************************/

/* OSICP协商选项长度 */
#define OSICP_CILEN_ALIGN_NPDU 3

/******************************/

/* 获取协商选项长度(cilen)宏 */
#define OSICP_LENCIALIGN_NPDU(neg)   (neg ? OSICP_CILEN_ALIGN_NPDU : 0)
/******************************/

/* 协商失败后,将OSICP down掉 */
#define PPP_OSICP_NEGOTIATIONDOWN(pOsicpInfo) \
{ \
    /* 向OSICP发送Close事件,即可结束协商  */ \
    PPP_OSICP_ReceiveEventFromCore(pOsicpInfo, (LONG)PPP_EVENT_FSM_CLOSE, NULL) ; \
    PPP_OSICP_ReceiveEventFromCore(pOsicpInfo, (LONG)PPP_EVENT_FSM_OPEN, NULL) ; \
}

/******************************/
/* 添加协商选项(addci)宏 */
#define ADDCIALIGN_NPDU(opt, neg, ucAlignment) \
{if (neg) \
{ \
    PPP_PUTCHAR(opt, pPacket); \
    PPP_PUTCHAR( OSICP_CILEN_ALIGN_NPDU, pPacket); \
    PPP_PUTCHAR(ucAlignment, pPacket); \
}}

/******************************/


/* 分析NAK报文的选项(nakci)宏 */
#define NAKCIALIGN_NPDU(opt, neg) \
   {if ((pstGotOptions->neg)&& \
        (OSICP_CILEN_ALIGN_NPDU ==(cilen = pPacket[1])) && \
        (ulLen >= ((ULONG)cilen)) && (pPacket[0] == opt))\
    { \
        ulLen = (ulLen - ((ULONG)cilen)); \
        PPP_INCPTR(2, pPacket); \
        PPP_GETCHAR(cichar, pPacket); \
        stNoOption.neg = 1; \
        stTryOption.ucAlign_NPDU = cichar; \
    }}
/******************************/


/* 分析REJ报文的选项(rejci)宏 */
#define REJCIALIGN_NPDU(opt, neg, val) \
    {if ((pstGotOptions->neg) && (ulLen >= OSICP_CILEN_ALIGN_NPDU) && \
    (OSICP_CILEN_ALIGN_NPDU == pPacket[1]) && (pPacket[0] == opt)) \
    { \
        ulLen -= OSICP_CILEN_ALIGN_NPDU; \
        PPP_INCPTR(2, pPacket); \
        PPP_GETCHAR(cichar, pPacket); \
        /* Check rejected value. */ \
        if (cichar != val) \
            goto bad; \
        stTryOption.neg = 0; \
    }}
/******************************/


/* 分析ACK报文的选项(ackci)宏 */
#define ACKCIALIGN_NPDU(opt, neg, val) \
    {if (neg) \
    { \
    if ((LONG)(ulLen -= OSICP_CILEN_ALIGN_NPDU) < 0) \
        goto bad; \
    PPP_GETCHAR(citype, pPacket); \
    PPP_GETCHAR(cilen, pPacket); \
    if (cilen != OSICP_CILEN_ALIGN_NPDU || \
        citype != opt) \
        goto bad; \
    PPP_GETCHAR(cichar, pPacket); \
    if (cichar != val) \
        goto bad; \
    }}
/******************************/


#ifdef      __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _OSICP_DEF_H_ */





