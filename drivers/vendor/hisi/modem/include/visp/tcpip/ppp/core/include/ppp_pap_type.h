/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                             ppp_pap_type.h
 *
 *  Project Code: VISP1.5
 *   Module Name: PPP
 *  Date Created: 2000-06-01
 *        Author: ZhuFengzhi
 *   Description: PPP的PAP协议处理模块数据结构
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2000-06-01      ZhuFengzhi      Create
 *  2004-07-01      YiAn            Modified for VISP
 *  2006-03-31      ZhuKun          Adjust for D00661
 *  2006-04-21      ZhuKun          Adjust for D00875
 *  2006-05-11      luyao           为支持ARM CPU字节对齐特性，修改结构。
 *
 ************************************************************************/

#ifndef _PAP_TYPE_H_
#define _PAP_TYPE_H_

#ifdef __cplusplus
extern "C" {
#endif


/* Code + ID + length */
#define PAP_HEADERLEN   (sizeof (UCHAR) + sizeof (UCHAR) + sizeof (USHORT))


/* PAP 数据帧代码 codes. */
#define PAP_AUTHREQ     1       /* Authenticate-Request */
#define PAP_AUTHACK     2       /* Authenticate-Ack */
#define PAP_AUTHNAK     3       /* Authenticate-Nak */

/*PAP 状态机中状态值 */
#define PAP_STATE_CLIENT_INITIAL        0
#define PAP_STATE_SERVER_INITIAL        0
#define PAP_STATE_SEND_AUTHREQ          1
#define PAP_STATE_SERVER_LISTEN         1
#define PAP_STATE_SERVER_SUCCESS        2
#define PAP_STATE_CLIENT_SUCCESS        2
#define PAP_STATE_SERVER_FAILED         3
#define PAP_STATE_CLIENT_FAILED         3
#define PAP_STATE_WAIT_AUTH             4

/*PAP 来自CORE的事件代码 */
#define PAP_EVENT_CLIENTLOWERUP         0
#define PAP_EVENT_SERVERLOWERUP         1
#define PAP_EVENT_LOWERDOWN             2

/*PAP 等待对端验证最长时间 */
#define PAP_WAITREQUESTTIMEOUT  60000   

/*PAP 内部的事件代码 */
#define PAP_INITIALIZATION              0
#define PAP_SERVERLOWERUP               1
#define PAP_CLIENTLOWERUP               2
#define PAP_LOWERDOWN                   3
#define PAP_RECEIVEREQUEST              4
#define PAP_AUTHRESULT                  5
#define PAP_RECEIVEACK                  6
#define PAP_RECEIVENAK                  7
#define PAP_REQUESTTIMEOUT              8
#define PAP_CODEREJECT                  9
#define PAP_WAITREQTIMEOUT              10
#define PAP_ERROREVENT                  11

/*状态代码*/
#define CLIENT_STATE            0
#define SERVER_STATE            1

/* PAP 控制块数据结构定义*/
typedef struct tagPppPapInfo
{
    PPPINFO_S *pstPppInfo;                      /* PPP 控制块指针*/

    UCHAR ucServerState;                        /* Server 状态 */
    UCHAR ucPadding_1[3]; 
    ULONG ulServerTimeoutID;                    /* Server 超时定时器 ID */
    USHORT usAuthServerFailureTimes;            /* 远端验证失败次数*/
    UCHAR ucPadding_2[2]; 
    ULONG ulWaitReqTimeout;                     /* 等待对端验证超时时间 */
    UCHAR ucPeerId;                             /* 当前对端验证请求包ID */

    UCHAR ucClientState;                        /* Client 状态 */
    UCHAR ucPadding_3[2]; 
    ULONG ulClientTimeoutID;                    /* Client 超时定时器 ID*/
    USHORT usAuthClientFailureTimes;            /* 本端验证失败次数*/
    UCHAR ucPadding_4[2]; 
    ULONG ulSendReqTimeout;                     /* 验证请求超时重传时间 */
    UCHAR ucTransmits;                          /* 传送验证请求的次数*/
    UCHAR ucPadding_5[3]; 
    ULONG ulMaxTransmits;                       /* 验证请求最大传送次数 */
    UCHAR ucId;                                 /* 当前本地验证请求包的ID*/
    UCHAR szPapUsrName[PPP_MAXUSERNAMELEN + 2]; /* 用户名 */
    UCHAR szPapUsrPwd[PPP_MAXUSERPWDLEN + 2];   /* 用户pwd */
    UCHAR ucPadding_6[3]; 
}PPPPAPINFO_S;

/*debug函数*/
VOID PAP_Debug_Packet(PPPINFO_S*, UCHAR *, ULONG, USHORT, UCHAR);
VOID PAP_Debug_StateChange(PPPINFO_S *, UCHAR, UCHAR);
VOID PAP_Debug_Event(PPPINFO_S*, UCHAR);
VOID PAP_Debug_Error(PPPINFO_S *, USHORT, CHAR *);

VOID PPP_PAP_SendAuthReqTimeout(VOID *);
VOID PPP_PAP_ReceiveAuthReq(PPPINFO_S *, UCHAR *, UCHAR, ULONG);
VOID PPP_PAP_ReceiveAuthAck(PPPINFO_S *, UCHAR *, UCHAR, ULONG);
VOID PPP_PAP_SendAuthReq(PPPINFO_S *);
VOID PPP_PAP_ReceiveAuthNak(PPPINFO_S *, UCHAR *, UCHAR, ULONG);
VOID PPP_PAP_SendResponse(PPPINFO_S *, UCHAR, UCHAR, char *, USHORT);
/* 接口函数 */
VOID PPP_PAP_Init(PPPINFO_S *);
VOID PPP_PAP_ReceiveEventFromCore (PPPINFO_S *, ULONG, char *);
VOID PPP_PAP_ReceivePacket (PPPINFO_S *, UCHAR* , UCHAR*, ULONG);

/*内部处理函数*/
VOID PPP_PAP_ClientLowerUp(PPPINFO_S *);
VOID PPP_PAP_ServerLowerUp(PPPINFO_S *);
VOID PPP_PAP_LowerDown(PPPINFO_S *);
VOID PPP_PAP_ReceiveUnknownCode(PPPINFO_S *);
VOID PPP_PAP_ReceiveAuthResult(PPPINFO_S * , PPPAUTHMSG_S *);
VOID PPP_PAP_WaitReqTimeout(VOID *);
VOID PPP_PAP_DeleteTimer(PPPINFO_S *);

#ifdef __cplusplus
}
#endif

#endif /* end of _PAP_TYPE_H_ */

