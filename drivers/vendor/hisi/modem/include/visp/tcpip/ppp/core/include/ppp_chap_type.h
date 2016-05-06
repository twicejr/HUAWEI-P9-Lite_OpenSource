/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                             ppp_chap_type.h
 *
 *  Project Code: VISP1.5
 *   Module Name: PPP
 *  Date Created: 2000-06-05
 *        Author: ZhuFengzhi
 *   Description: PPP的CHAP协议处理模块数据结构
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2000-06-05      ZhuFengzhi      Create
 *  2004-07-01      YiAn            Modified for VISP
 *  2006-03-31      ZhuKun          Adjust for D00661
 *  2006-04-21      ZhuKun          Adjust for D00875
 *  2006-05-11      luyao           为支持ARM CPU字节对齐特性，修改结构。
 *
 ************************************************************************/

#ifndef _CHAP_TYPE_H_
#define _CHAP_TYPE_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Code + ID + length */
#define CHAP_HEADERLEN          4

/* CHAP PACKET CODE */
#define CHAP_PACKET_CODE_CHALLENGE              1
#define CHAP_PACKET_CODE_RESPONSE               2
#define CHAP_PACKET_CODE_SUCCESS                3
#define CHAP_PACKET_CODE_FAILURE                4

/* CHAP codes.*/
#define CHAP_DIGEST_MD5         5       /* use MD5 algorithm */
#define MD5_SIGNATURE_SIZE      16      /* 16 bytes in a MD5 message digest */

/* CHAP state */
#define CHAP_STATE_CLIENT_INITIAL               0
#define CHAP_STATE_SERVER_INITIAL               0
#define CHAP_STATE_LISTEN_CHALLENGE             1
#define CHAP_STATE_SEND_CHALLENGE               1
#define CHAP_STATE_SEND_RESPONSE                2
#define CHAP_STATE_CLIENT_SUCCESS               3
#define CHAP_STATE_SERVER_SUCCESS               3
#define CHAP_STATE_SERVER_FAILED                4
#define CHAP_STATE_CLIENT_FAILED                4
#define CHAP_STATE_WAITING_AUTHRESULT           5

/* Challenge lengths (for challenges we send) and other limits. */
#define CHAP_MAX_CHALLENGE_LENGTH    16
#define CHAP_MAX_RESPONSE_LENGTH     16  /* sufficient for MD5 */

/* Timeouts. */
#define CHAP_DEFTIMEOUT         5000     /* Timeout time in milliseconds */
#define CHAP_DEFTRANSMITS       10       /* max # times to send challenge */

/* CHAP 来自CORE的事件代码 */
#define CHAP_EVENT_CLIENTLOWERUP        0
#define CHAP_EVENT_SERVERLOWERUP        1
#define CHAP_EVENT_LOWERDOWN            2

/* CHAP 内部的事件代码 */
#define CHAP_SERVERLOWERUP              0
#define CHAP_CLIENTLOWERUP              1
#define CHAP_LOWERDOWN                  2
#define CHAP_RECEIVECHALLENGE           3
#define CHAP_RECEIVERESPONSE            4
#define CHAP_AUTHSUCCESS                5
#define CHAP_AUTHFAILURE                6
#define CHAP_RESPONSETIMEOUT            7
#define CHAP_CHALLENGETIMEOUT           8
#define CHAP_INITIALIZATION             9
#define CHAP_RECHANLLENGE               10
#define CHAP_CODEREJECT                 11
#define CHAP_AUTHRESULT                 12
#define CHAP_ERROREVENT                 13

/*状态代码*/
#define CHAP_CLIENT_STATE               0
#define CHAP_SERVER_STATE               1

/* CHAP 控制块数据结构定义 */
typedef struct tagPppChapInfo 
{
    PPPINFO_S *pstPppInfo ;             /*PPP控制块指针*/
    
    UCHAR ucClientState;                /* Client 状态*/
    UCHAR szResponse[CHAP_MAX_RESPONSE_LENGTH + 2];   /* 送出的Response 字符串 */
    UCHAR ucRespLen;                    /* Response 长度 */
    UCHAR ucRespId;                     /* Response ID */
    UCHAR ucRespType;                   /* 产生Response 的哈希算法类型 */
    UCHAR ucPadding_1[2]; 
    ULONG ulRespTransmits;              /* 已传送Response次数 */
    ULONG ulRespTimeoutID;              /* 传送Response超时定时器 */
    USHORT usAuthClientFailureTimes;    /* Client端验证失败计数器 */
    
    UCHAR ucServerState;                /* Server 状态 */
    UCHAR szChallenge[CHAP_MAX_CHALLENGE_LENGTH];     /* 送出的Challenge 字符串 */
    UCHAR ucChalLen;                    /* Challenge 长度 */
    UCHAR ucChalId;                     /* Challenge ID */
    UCHAR ucChalType;                   /* 产生Challenge的哈希算法类型 */
    UCHAR ucPadding_2[2]; 
    ULONG ulChalTransmits;              /* 已传送Challenge 次数 */
    ULONG ulChalInterval;               /* 再次验证对端的时间间隔 */
    ULONG ulChalTimeoutID;              /* 传送Challenge超时定时器 */
    USHORT usAuthServerFailureTimes;    /* Server端验证失败定时器 */
    UCHAR ucPadding_3[2]; 
    ULONG ulTimeOutTime;                /* 超时时间 */
    ULONG ulMaxTransmits;               /* 最大传送次数 */
    UCHAR szHostName[PPP_MAXUSERNAMELEN + 2];         /* 主机名 */
    UCHAR szHostPwd[PPP_MAXUSERPWDLEN + 2];           /* pwd */
}PPPCHAPINFO_S;

VOID PPP_CHAP_Init(PPPINFO_S *);
VOID PPP_CHAP_ChallengeTimeout(VOID *);
VOID PPP_CHAP_ResponseTimeout(VOID *);
VOID PPP_CHAP_Rechallenge(VOID *);
VOID PPP_CHAP_ClientLowerUp(PPPINFO_S *);
VOID PPP_CHAP_ServerLowerUp(PPPINFO_S *);
VOID PPP_CHAP_ReceiveEventFromCore (PPPINFO_S *, ULONG , CHAR *);
VOID PPP_CHAP_LowerDown(PPPINFO_S *);
VOID PPP_CHAP_ReceivePacket (PPPINFO_S *, UCHAR* , UCHAR* , ULONG );
VOID PPP_CHAP_ReceiveChallenge(PPPINFO_S *, UCHAR *, UCHAR, ULONG);
VOID PPP_CHAP_ReceiveResponse(PPPINFO_S *, UCHAR *, UCHAR, ULONG);
VOID PPP_CHAP_ReceiveAuthResult(PPPINFO_S *, PPPAUTHMSG_S *);
VOID PPP_CHAP_ReceiveSuccess(PPPINFO_S *, UCHAR);
VOID PPP_CHAP_ReceiveFailure(PPPINFO_S *);
VOID PPP_CHAP_SendChallenge(PPPINFO_S *);
VOID PPP_CHAP_SendStatus(PPPINFO_S *, UCHAR);
VOID PPP_CHAP_GenChallenge(PPPCHAPINFO_S *);
VOID PPP_CHAP_SendResponse(PPPINFO_S *);
VOID PPP_CHAP_ReceiveUnknownCode(PPPINFO_S *);
SHORT PPP_CHAP_GenResponse(PPPAUTHMSG_S *);
VOID PPP_CHAP_DeleteTimer(PPPINFO_S *);

/*CHAP 调试函数 */
VOID CHAP_Debug_Packet(PPPINFO_S*, UCHAR *, ULONG, USHORT, UCHAR );
VOID CHAP_Debug_StateChange(PPPINFO_S *, UCHAR, UCHAR);
VOID CHAP_Debug_Event(PPPINFO_S *, UCHAR);
VOID CHAP_Debug_Error(PPPINFO_S *, USHORT, CHAR *);

#ifdef __cplusplus
}
#endif

#endif      /* end of _CHAP_TYPE_H_ */

