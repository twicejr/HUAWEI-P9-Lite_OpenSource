/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              sock_comp.h
*
*  Project Code: VISP1.5
*   Module Name: socket4   
*  Date Created: 2006-4-29
*        Author: l(48769)
*   Description: socket component
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-04-27   l(48769)        根据编程规范，对文件进行规范化整理
*
*******************************************************************************/
#ifndef        _SOCK_COMP_H_
#define        _SOCK_COMP_H_

#ifdef    __cplusplus
extern    "C"{
#endif
/*the fields of INPCB_S*/
typedef enum tageInPcb4Field
{
    IP4_INPCB_NEXT,
    IP4_INPCB_PREV,
    
    IP4_INPCB_LADDR,
    IP4_INPCB_LPORT,
    IP4_INPCB_FADDR,
    IP4_INPCB_FPORT,
    
    IP4_INPCB_PPCB,
    IP4_INPCB_SOCKET,
    
    IP4_INPCB_FLAGS,
    IP4_INPCB_OPTIONS,
    IP4_INPCB_MOPTS,
    IP4_INPCB_HASHHEAD,
    IP4_INPCB_HNEXT,
    
    IP4_INPCB_IP_TTL,
    IP4_INPCB_IP_TOS,
    IP4_INPCB_IPPROTO,

   IP4_INPCB_IP_TOS_TOTAL

}eInPcb4Field;

/*the fields of SOCKET_S*/
typedef enum tageSocket4Field
{            
    IP4_SOCKET_FD,
    IP4_SOCKET_TASK_ID,
    IP4_SOCKET_IPCB,
    IP4_SOCKET_SRC_ADDR,    
    IP4_SOCKET_STATE,
    IP4_SOCKET_KEEPALIVE,
    IP4_SOCKET_LINGER,
    IP4_SOCKET_OOBMARK,
    IP4_SOCKET_OPTIONS,
    IP4_SOCKET_ERROR,
    IP4_SOCKET_INCREASE_DROPPACKETS,
    
    IP4_SOCKET_NEXTHOP_ADDR,    
    IP4_SOCKET_NEXTHOP_OUTIFINDEX,
    
    IP4_SOCKET_RECVBUF,
    IP4_SOCKET_RECVBUF_ACHARS,
    IP4_SOCKET_RECVBUF_HiWAT,
    IP4_SOCKET_RECVBUF_IFNET,
    IP4_SOCKET_RECVBUF_LOWAT,
    
    IP4_SOCKET_SENDBUF,
    IP4_SOCKET_SENDBUF_ACHARS,
    IP4_SOCKET_SENDBUF_FLAG,
    IP4_SOCKET_SENDBUF_HiWAT,
    IP4_SOCKET_SENDBUF_LOWAT,
    IP4_SOCKET_SENDBUF_PMBUF,
    
    IP4_SOCKET_CBDATABUF,
    
    IP4_SOCKET_SENDDATAIF_ADDR,
    IP4_SOCKET_SENDDATAIF_INDEX,    
    
    IP4_SOCKET_VRF_IFINDEX,

    IP4_SOCKET_SENDBUF_BACKUPLEN,
    IP4_SOCKET_HEAD,
    IP4_SOCKET_TRRT_OUTIFINDEX,

    IP4_SOCKET_KEEPIDLE
}eSocket4Field;

#ifdef    __cplusplus
}
#endif

#endif /* _SOCK_COMP_H_  */

