
/************************************************************************
 *                                                                      *
 *                             chap_def.h                               *
 *                                                                      *
 *  Project Code:       VRP3.0                                          *
 *  Create Date:        2000/06/05                                      *
 *  Author:             Zhu Fengzhi                                      *
 *  Modify Date:                                                        *
 *  Document:                                                           *
 *  Function:           PPP的CHAP协议模块私有宏定义                      *
 *  Others:                                                             *
 *----------------------------------------------------------------------*
 *                                                                      *
 * Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc.  *
 *                     ALL RIGHTS RESERVED                              *
 *                                                                      *
 *----------------------------------------------------------------------*
 *                                                                      *
 *   这个文件定义了CHAP协议模块的全部私有宏定义                          *
 *                                                                      *
 ************************************************************************/

#if( VRP_MODULE_LINK_PPP == VRP_YES )

#if( VRP_MODULE_LINK_PPP_CHAP == VRP_YES )

#ifndef      _CHAP_DEF_H_
#define      _CHAP_DEF_H_

#ifdef      __cplusplus
extern "C" {
#endif		/* end of __cplusplus */

/* Code + ID + length */
#define CHAP_HEADERLEN		4

/* CHAP PACKET CODE */
#define	CHAP_PACKET_CODE_CHALLENGE		1
#define CHAP_PACKET_CODE_RESPONSE		2
#define CHAP_PACKET_CODE_SUCCESS		3
#define	CHAP_PACKET_CODE_FAILURE		4

/* CHAP codes.*/
#define CHAP_DIGEST_MD5		5	/* use MD5 algorithm */
#define MD5_SIGNATURE_SIZE	16	/* 16 bytes in a MD5 message digest */

/*	CHAP state */
#define CHAP_STATE_CLIENT_INITIAL		0
#define CHAP_STATE_SERVER_INITIAL		0
#define CHAP_STATE_LISTEN_CHALLENGE	    1
#define CHAP_STATE_SEND_CHALLENGE		1
#define CHAP_STATE_SEND_RESPONSE		2
#define CHAP_STATE_CLIENT_SUCCESS		3
#define CHAP_STATE_SERVER_SUCCESS		3
#define CHAP_STATE_SERVER_FAILED		4
#define CHAP_STATE_CLIENT_FAILED    	4
#define CHAP_STATE_WAITING_AAA          5

/* Challenge lengths (for challenges we send) and other limits. */
#define CHAP_MAX_CHALLENGE_LENGTH    16
#define CHAP_MAX_RESPONSE_LENGTH     16  /* sufficient for MD5 */

/*  Timeouts. */
#define CHAP_DEFTIMEOUT		5000 /* Timeout time in milliseconds */
#define CHAP_DEFTRANSMITS	10	/* max # times to send challenge */
#define CHAP_WAITAAARSPTIMEOUT	20000   /* modified by gxf 20030516  AAA向主备server各发三次请求,每次间隔3s,3*6=18s */
#define CHAP_MAXAUTHTRANSMITS	1	/* max # times to send AUTH msg */
#define CHAP_WAITLNSAUTHTIME         10000;

/*CHAP 来自CORE的事件代码 */
#define CHAP_EVENT_CLIENTLOWERUP	0
#define CHAP_EVENT_SERVERLOWERUP	1
#define	CHAP_EVENT_LOWERDOWN		2

/*CHAP 内部的事件代码 */
#define CHAP_SERVERLOWERUP		0
#define CHAP_CLIENTLOWERUP		1
#define	CHAP_LOWERDOWN			2
#define CHAP_RECEIVECHALLENGE	3
#define	CHAP_RECEIVERESPONSE	4
#define	CHAP_AUTHSUCCESS		5
#define	CHAP_AUTHFAILURE		6
#define	CHAP_RESPONSETIMEOUT	7
#define CHAP_CHALLENGETIMEOUT	8
#define	CHAP_INITIALIZATION		9
#define	CHAP_RECHANLLENGE		10
#define	CHAP_CODEREJECT			11
#define	CHAP_AAARESULT		    12
#define	CHAP_AAARESULTTIMEOUT   13
#define	CHAP_ERROREVENT			14

/*状态代码*/
#define CHAP_CLIENT_STATE		0
#define	CHAP_SERVER_STATE		1

#define PPP_CHAP_AAAAuthFailed(pstChapInfo) \
    {   \
        AAA_AUTHREQ_S *pstMsgTemp = pstChapInfo->pstAAAAuthReqMsg; \
        PPPINFO_S *pstPppInfoTemp = pstChapInfo->pstPppInfo;    \
        if(pstMsgTemp)                                          \
        {                                                   \
            PPP_Free (pstMsgTemp);                              \
            pstChapInfo->pstAAAAuthReqMsg = VOS_NULL_PTR;                                  \
        }                                                   \
        pstChapInfo->ucAuthTransmits = 0 ;                  \
        CHAP_Debug_StateChange(pstPppInfoTemp, CHAP_STATE_SERVER_FAILED, CHAP_SERVER_STATE) ;   \
        pstChapInfo->ucServerState = CHAP_STATE_SERVER_FAILED ; \
        PPP_Core_ReceiveEventFromProtocol (pstPppInfoTemp,PPP_EVENT_CHAPFAILED,VOS_NULL_PTR) ;   \
    }


#ifdef      __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _CHAP_DEF_H_ */

#endif  /* #if( VRP_MODULE_LINK_PPP_CHAP == VRP_YES ) */

#endif	/* #if( VRP_MODULE_LINK_PPP == VRP_YES ) */


