/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              socktemp.h
*
*  Project Code: VISP1.5
*   Module Name: socket4  
*  Date Created: 2000.4.3
*        Author: chenbin
*   Description: MID definition in socket
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2000-04-03   chenbin         created
*  2006-04-27   l(48769)        根据编程规范，对文件进行规范化整理
*
*******************************************************************************/
#ifndef        _SOCKTEMP_H
#define        _SOCKTEMP_H

#ifdef    __cplusplus
extern    "C"{
#endif

/*Module ID*/
#define mid_SOCKET_CREATETCB  (MID_COMP_SOCKET | 1) /*  0x03920001, SOCKET -- CreateTcb()  0x03920001 */
#define mid_SOCKET_READV     (MID_COMP_SOCKET | 2) /*  0x03920002 SOCKET -- readv() */
#define mid_SOCKET_WRITEV    (MID_COMP_SOCKET | 3) /*  0x03920003SOCKET -- writev() */
#define mid_SOCKET_SO_CREATE    (MID_COMP_SOCKET | 4) /*  0x03920004 SOCKET -- SO_Create() */
#define mid_SOCKET_SO_GETOPT (MID_COMP_SOCKET | 5) /*  0x03920005SOCKET -- SO_GetOpt() */
#define mid_SOCKET_GETHOSTBYADDR (MID_COMP_SOCKET | 6) /*  0x03920006 SOCKET -- gethostbyaddr() */
#define mid_SOCKET_GETHOSTBYNAME (MID_COMP_SOCKET | 7) /*  0x03920007 SOCKET -- gethostbyname() */
#define mid_SOCKET_INPCB_ALLOC (MID_COMP_SOCKET | 8) /*  0x03920008 SOCKET -- INPCB_Alloc() */
#define mid_SOCKET_IN_SETSOCKADDR (MID_COMP_SOCKET | 9) /*  0x03920009 SOCKET -- IN_SetSockAddr() */
#define mid_SOCKET_IN_SETPEERADDR (MID_COMP_SOCKET | 10) /*  0x0392000a SOCKET -- IN_SetPeerAddr() */
#define mid_SOCKET_INPCB_HASHINSERT (MID_COMP_SOCKET | 11) /*  0x03920001b SOCKET -- INPCB_HashInsert() */
#define mid_SOCKET_SO_NEWCONN (MID_COMP_SOCKET | 12) /*  0x0392000c, SOCKET -- SO_NewConn() */
#define mid_SOCKET_SB_APPEDN (MID_COMP_SOCKET | 13) /*  0x0392000d, SOCKET -- SB_Append() */
#define mid_SOCKET_SB_APPENDRECORD (MID_COMP_SOCKET | 14) /*  0x0392000e, SOCKET -- SB_AppendRecord() */
#define mid_SOCKET_SB_APPENDADDR (MID_COMP_SOCKET | 15) /*  0x0392000f, SOCKET -- SB_AppendAddr() */
#define mid_SOCKET_SB_APPENDCONTROL (MID_COMP_SOCKET | 16) /*  0x03920010, SOCKET -- SB_AppendControl() */
#define mid_SOCKET_SB_COMPRESS (MID_COMP_SOCKET | 17) /*  0x03920011, SOCKET -- SB_Compress() */
#define mid_SOCKET_ACCEPT (MID_COMP_SOCKET | 18) /*  0x03920012, SOCKET -- accept() */
#define mid_SOCKET_RECVMSG (MID_COMP_SOCKET | 19) /*  0x03920013, SOCKET -- recvmsg() */
#define mid_SOCKET_SENDMSG (MID_COMP_SOCKET | 20) /*  0x03920014, SOCKET -- sendmsg() */
#define mid_SOCKET_SETSOCKOPT (MID_COMP_SOCKET | 21) /*  0x03920015, SOCKET -- setsockopt() */
#define mid_SOCKET_GETSOCKNAME (MID_COMP_SOCKET | 22) /*  0x03920016, SOCKET -- getsockname() */

#define mid_SOCKET_GETPEERNAME (MID_COMP_SOCKET | 23) /*  0x03920017, SOCKET -- getpeername() */
#define mid_SOCKET_SOCKARGS (MID_COMP_SOCKET | 24) /*  0x03920018, SOCKET -- SockArgs() */
#define mid_SOCKET_SS_FILLMBUF (MID_COMP_SOCKET | 25) /*  0x03920019, SOCKET -- SS_FillMbuf() */
#define mid_SOCKET_SR_MSGOOB (MID_COMP_SOCKET | 26) /*  0x0392001a, SOCKET -- SR_MsgOob() */
#define mid_SOCKET_SR_PROCADDRCON (MID_COMP_SOCKET | 27) /* 0x0392001b, SOCKET -- SR_ProcAddrCon() */
#define mid_SOCKET_SR_PROCDATA (MID_COMP_SOCKET | 28) /*  0x0392001c, SOCKET -- SR_ProcData() */
#define mid_SOCKET_TCBFILEEXPAND (MID_COMP_SOCKET | 29) /*  0x0392001d, SOCKET -- TcbFileExpand() */

#define mid_SOCKET_SOCKET_RESTORE (MID_COMP_SOCKET|46) /*SOCKET -- Socket_Restore */
#define mid_SOCKET_SOCK_BAK (MID_COMP_SOCKET|47) /*SOCKET -- Sock_Bak */
#define mid_SOCKET_SOCK_CLR (MID_COMP_SOCKET|48) /*SOCKET -- Sock_Clr */

#ifdef    __cplusplus
}
#endif

#endif
