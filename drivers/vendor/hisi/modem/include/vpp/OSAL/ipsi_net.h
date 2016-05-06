/**
Copyright(C) 2007, Huawei Tech. India Pvt. Ltd.
            ALL RIGHTS RESERVED

FileNmae   : ipsi_net.h
version    : 1
Author     : Jayaraghavendran K
Created on : 2006-12-29
Description: This file contains all the network related functions.
History:<author>   <date>          <desc>
*/

#ifndef __IPSI_NET_H_
#define __IPSI_NET_H_

#include "ipsi_types.h"
#include "ipsi_time.h"

#ifdef  __cplusplus
extern "C" {
#endif

//errors
#define IPSI_NOTINITIALISED     (-20) 
#define IPSI_ENETDOWN           (-21)
#define IPSI_EACCES             (-22)
#define IPSI_EINTR              (-23)
#define IPSI_EINPROGRESS        (-24)
#define IPSI_EFAULT             (-25)
#define IPSI_ENETRESET          (-26)
#define IPSI_ENOBUFS            (-27)
#define IPSI_ENOTCONN           (-28)
#define IPSI_ENOTSOCK           (-29)
#define IPSI_EOPNOTSUPP         (-30)
#define IPSI_ESHUTDOWN          (-31)
#define IPSI_EWOULDBLOCK        (-32)
#define IPSI_EMSGSIZE           (-33)
#define IPSI_EHOSTUNREACH       (-34)
#define IPSI_EINVAL             (-35)
#define IPSI_ECONNABORTED       (-36)
#define IPSI_ECONNRESET         (-37)
#define IPSI_ETIMEDOUT          (-38)
#define IPSI_SYS_UNKNOWN_ERROR  (-39)
#define IPSI_SOCK_CLOSED        (-40)
#define IPSI_TIMEOUT_ERROR      (-41)
#define IPSI_SYS_CLOCK_ERROR (-42)

/**
    @typedef    'void *' is abstracted as ipsi_sock_id_t and is used as socket
                id type in all the socket related functions.
*/
typedef void* ipsi_sock_id_t;
typedef void* ipsi_sock_addr_t;


/**
    @brief          The ipsi_recv function is used to receive messages on a 
                    connected socket.

    @param[in]      s       The socket ID.
    @param[in]      buf     The buffer where the message is to be received
    @param[in]      len     The size of the buffer
    @retval         int     Number of bytes received On Success.
                     0      On Broken Connection.
                    -1      On Failure.
*/
IPSILINKDLL int ipsi_recv(ipsi_sock_id_t s, void *buf, size_t len);


/**
    @brief          The ipsi_send function is used to send messages 
                    on a connected socket.

    @param[in]      s       The socket ID.
    @param[in]      buf     The buffer containing the message to be sent
    @param[in]      len        The size of the buffer
    @retval         int     Number of bytes sent On Success.
                    -1      On Failure.
*/
IPSILINKDLL int ipsi_send(ipsi_sock_id_t s, const void *msg, size_t len);


/**
    @brief          The ipsi_sockclose function is used to close a socket.

    @param[in]      s       The ID of the socket to be closed.
    @retval         0       On Success.
                   -1       On Failure.
*/
IPSILINKDLL int ipsi_sockclose(ipsi_sock_id_t s);

/**
    @brief          ipsi_get_last_socket_error function returns the 
                    last network error that occurred. When a particular Windows 
                    Sockets function indicates that an error has occurred,
                    this function should be called to retrieve the 
                    appropriate error code.

    @para[in]       none

    @retval         Integer that indicates the error code.
*/
IPSILINKDLL int ipsi_get_last_socket_error(void);

/**
    @brief          ipsi_clear_socket_error function will set the error code 
                    to Zero.

    @param          None

    @retval         None
*/
IPSILINKDLL void ipsi_clear_socket_error(void);


/**
    @brief          The ipsi_recvfrom function is used to receive messages 
                    in UDP socket

    @param[in]      s       The socket ID.
    @param[in]      buf     The buffer where the message is to be received
    @param[in]      len     The size of the buffer
    @param[in]      flags     flag used in recv
    @param[in]      from     message received from address
    @param[in]      fromlen     address len
    @retval         int     Number of bytes received On Success.
                     0      On Broken Connection.
                    -1      On Failure.
*/
IPSILINKDLL int ipsi_recvfrom(ipsi_sock_id_t s, void *buf, size_t len,
                              int flags,void *from,void *fromlen,int *pErrno);

/**
    @brief          The ipsi_recvfrom function is used to receive messages 
                    in UDP socket

    @param[in]      s       The socket ID.
    @param[in]      buf     The buffer where the message is to be received
    @param[in]      len     The size of the buffer
    @param[in]      flags     flag used in recv
    @param[in]      from     message received from address
    @param[in]      fromlen     address len
    @param[in]      timeout     the maximum time to wait on the socket    
    @param[out]      pErrno     Error number in case of error in receive.
    @retval         int     Number of bytes received On Success.
                     0      On Broken Connection.
                    -1      On Failure.
*/
IPSILINKDLL int ipsi_recvfrom_timeout(ipsi_sock_id_t s, void *buf, size_t len,
                                      int flags,void *from,void *fromlen,
                                      IPSI_TIMEVAL_S *timeout, int *pErrno);

/**
    @brief          The ipsi_sendto function is used to send messages in udp 
                    socket

    @param[in]      s       The socket ID.
    @param[in]      buf     The buffer containing the message to be sent
    @param[in]      len     The size of the buffer
    @param[in]      flags     flag used in send
    @param[in]      to     message send to address
    @param[in]      tolen     address len
    @retval         int     Number of bytes sent On Success.
                    -1      On Failure.
*/
IPSILINKDLL int ipsi_sendto(ipsi_sock_id_t s, const void *msg, size_t len,
                            int flags,void *to,size_t tolen,int *pErrno);

/**
    @brief          The ipsi_getsockopt function is used to get socket option

    @param[in]      s       The socket ID.
    @param[in]      level       level used in get socket.
    @param[in]      optname       option name.
    @param[in]      optval       option value.
    @param[in]      optlen       option length.
    @retval         int     Get socket option.
                    -1      On Failure.
*/

IPSILINKDLL int ipsi_getsockopt(ipsi_sock_id_t s,int level,
                                int optname,void *optval,void *optlen);

/**
    @brief          The ipsi_getsockopt function is used to mtu from the socket

    @param[in]      s       The socket ID.
    @param[in]      mtuval       mtu value.
    @param[in]      mtulen       mtu length.
    @retval         int     Get socket option.
                    -1      On Failure.
*/
IPSILINKDLL int ipsi_getsockmtu(ipsi_sock_id_t s, void *mtuval, void *mtulen);

/**
    @brief          The ipsi_setsockopt function is used to set socket option

    @param[in]      s       The socket ID.
    @param[in]      level       level used in get socket.
    @param[in]      optname       option name.
    @param[in]      optval       option value.
    @param[in]      optlen       option length.
    @retval         int     Set socket option
                    -1      On Failure.
*/

IPSILINKDLL int ipsi_setsockopt(ipsi_sock_id_t s,int level,int optname,
                                    void *optval,int optlen);
IPSILINKDLL ipsi_sock_id_t ipsi_socket(int af, int type, int protocol);

IPSILINKDLL int ipsi_bind(ipsi_sock_id_t sockfd,
                                ipsi_sock_addr_t addr,int namelen);

IPSILINKDLL int ipsi_connect(ipsi_sock_id_t sockfd,
                                ipsi_sock_addr_t *addr,int namelen);

IPSILINKDLL int ipsi_ioctlsocket(ipsi_sock_id_t sockfd,long cmd,
                                    unsigned long *parg);

IPSILINKDLL int ipsi_send_ex(ipsi_sock_id_t sockfd, const void *msg,
                                size_t len,int flags);

IPSILINKDLL int ipsi_recv_ex(ipsi_sock_id_t sockfd, void *buf,
                                size_t len,int flags);

IPSILINKDLL int ipsi_select(int nfds,void* readfds,
                            void* writefds,void* exceptfds,
                            void* timeout);

IPSILINKDLL int ipsi_select_ex(int nfds,void* readfds,
                            void* writefds,void* exceptfds,
                            void* timeout);

#ifdef  __cplusplus
}
#endif
#endif

