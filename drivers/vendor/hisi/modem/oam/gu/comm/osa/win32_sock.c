/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and 
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may 
 * *    be used to endorse or promote products derived from this software 
 * *    without specific prior written permission.
 * 
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/*****************************************************************************/
/*                                                                           */
/*                Copyright 1999 - 2003, Huawei Tech. Co., Ltd.              */
/*                           ALL RIGHTS RESERVED                             */
/*                                                                           */
/* FileName: win32_sock.c                                                    */
/*                                                                           */
/* Author: Yang Xiangqian                                                    */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date: 2006-10                                                             */
/*                                                                           */
/* Description: implement socket                                             */
/*                                                                           */
/* Others:                                                                   */
/*                                                                           */
/* History:                                                                  */
/* 1. Date:                                                                  */
/*    Author:                                                                */
/*    Modification: Create this file                                         */
/*                                                                           */
/* 2. Date: 2006-10                                                          */
/*    Author: Xu Cheng                                                       */
/*    Modification: Standardize code                                         */
/*                                                                           */
/*****************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif /* __cplusplus */
#endif /* __cplusplus */

#include "stdio.h"
#include "v_typdef.h"
#include "v_sock.h"


#if (VOS_WIN32 == VOS_OS_VER)

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_V_WIN32_SOCK_C



/*****************************************************************************
 Function   : VOS_Socket
 Description: creates a socket that is bound to a specific service provider      :
 Called By  :
 Input      : af -- address family specification,can only be AF_INET
              type -- type specification for the new socket,can be:
              SOCK_STREAM  or  SOCK_DATAGRAM
              protocol -- particular protocol to be used with the socket
 Output     :
 Return     : new socket if success or VOS_NULL_LONG if failure
 Other      :
 *****************************************************************************/
VOS_SOCKET VOS_Socket(VOS_INT32 af, VOS_INT32 type, VOS_INT32 protocol)
{
    VOS_SOCKET vsRet;
    SOCKET soRet;

    soRet = socket( (VOS_INT)af , (VOS_INT)type, (VOS_INT)protocol);
    if ( INVALID_SOCKET == soRet )
    {
        vsRet = VOS_NULL_LONG;
    }
    else
    {
        vsRet = (VOS_SOCKET)soRet;
    }

    return vsRet;
}

/*****************************************************************************
 Function   : VOS_Bind
 Description: associates a local address with a socket
 Calls      :
 Called By  :
 Input      : s -- descriptor identifying an unbound socket
              paddr -- address to assign to the socket
              addrlen -- length of the address
 Output     :
 Return     : VOS_NULL_LONG if failure or VOS_OK if success
 Other      :
 *****************************************************************************/
VOS_UINT32 VOS_Bind(VOS_SOCKET s, struct sockaddr *paddr, VOS_INT32 addrlen)
{
    if ( 0 == bind((SOCKET) s , paddr , (VOS_INT)addrlen) )
    {
        return  VOS_OK;
    }
    else
    {
        return VOS_NULL_LONG;
    }
}

/*****************************************************************************
 Function   : VOS_Select
 Description: determines the status of one or more sockets, waiting if necessary,
              to perform synchronous I/O.
 Called By  :
 Input      : s -- identifying a socket to close
              level -- level at which the option is defined
              optname -- socket option for which the value is to be set
              poptval -- pointer to the buffer in which the value for the requested
                         option is to be set
              poptlen -- pointer to the size of the optval buffer
 Output     :
 Return     : total number of socket handles that are ready
              if success or VOS_NULL_LONG if failure
 Other      :
 *****************************************************************************/
VOS_UINT32 VOS_Select(VOS_INT32 width, struct fd_set * preadfds, struct fd_set * pwritefds,
                       struct fd_set * pexceptfds, struct timeval * ptimeout  )
{
    int ReturnValue;

    ReturnValue = select( (VOS_INT)width, preadfds, pwritefds, pexceptfds, ptimeout);
    if( SOCKET_ERROR == ReturnValue )
    {
        return VOS_NULL_LONG;
    }
    else
    {
        return (VOS_UINT32)ReturnValue;
    }
}

/*****************************************************************************
 Function   : VOS_Accept
 Description: accepts an incoming connection attempt on a socket
 Calls      :
 Called By  :
 Input      : s    -- socket that has been placed in a listening state
 Output     : addr -- An optional pointer to a buffer that receives the address
                       of the connecting entity
              addrlen -- A optional pointer to an integer that contains the length
                         of the address addr
 Return     : VOS_NULL_LONG if failure or new socket if success
 Other      :
 *****************************************************************************/
VOS_SOCKET VOS_Accept( VOS_SOCKET s, struct sockaddr *paddr, VOS_INT32 *paddrlen )
{
    SOCKET soRet;

    soRet = accept( (SOCKET)(s) , paddr , (VOS_INT*)paddrlen);
    if( INVALID_SOCKET == soRet )
    {
        return VOS_NULL_LONG;
    }
    else
    {
        return (VOS_SOCKET)soRet;
    }
}

/*****************************************************************************
 Function   : VOS_Recv
 Description: receives data from a connected socket Calls      :
 Called By  :
 Input      : s -- descriptor identifying a connected socket
              len -- length of the buffer
              flags -- flag specifying the way in which the call is made
                       can be constructed by or-ing the following values:
                       MSG_OOB & MSG_PEEK
 Output     : buf -- buffer for the incoming data
 Return     : the number of bytes received if success or VOS_NULL_LONG if failure
 Other      :
 *****************************************************************************/
VOS_UINT32 VOS_Recv(VOS_SOCKET s, VOS_CHAR * buf, VOS_INT32 len, VOS_INT32 flags)
{
    int ReturnValue;

    ReturnValue = recv( (SOCKET)s , buf, (VOS_INT)len, (VOS_INT)flags);
    if ( SOCKET_ERROR == ReturnValue )
    {
        return VOS_NULL_LONG;
    }
    else
    {
        return (VOS_UINT32 )ReturnValue;
    }

}

/*****************************************************************************
 Function   : VOS_CloseSocket
 Description: closes an existing socket
 Called By  :
 Input      : s -- identifying a socket to close
 Output     :
 Return     : VOS_OK if success or VOS_NULL_LONG if failure
 Other      :
 *****************************************************************************/
VOS_UINT32 VOS_CloseSocket(VOS_SOCKET s)
{
    if ( 0 == closesocket((SOCKET) s ) )
    {
        return VOS_OK;
    }
    else
    {
        return VOS_NULL_LONG;
    }
}

/*****************************************************************************
 Function   : VOS_Send
 Description: sends data on a connected socket      :
 Called By  :
 Input      : s -- descriptor identifying a connected socket
              buf -- buffer containing the data to be transmitted
              len -- length of the buffer
              flags -- flag specifying the way in which the call is made
                       flags can be constructed by or-ing the following values:
                       MSG_OOB & MSG_DONTROUT
 Output     :
 Return     : the number of bytes sent if success or VOS_NULL_LONG if failure
 Other      :
 *****************************************************************************/
VOS_UINT32 VOS_Send(VOS_SOCKET s, VOS_CHAR * buf, VOS_INT32 len, VOS_INT32 flags)
{
    int ReturnValue;

    ReturnValue = send( (SOCKET)s , buf, (VOS_INT)len, (VOS_INT)flags);
    if( SOCKET_ERROR == ReturnValue)
    {
        return VOS_NULL_LONG;
    }
    else
    {
        return (VOS_UINT32)ReturnValue;
    }
}

/*****************************************************************************
 Function   : VOS_Listen
 Description: places a socket a state where it is listening for an incoming connection
 Calls      :
 Called By  :
 Input      : s -- descriptor identifying a bound, unconnected socket
              backlog -- maximum length of the queue of pending connections
 Output     :
 Return     : VOS_NULL_LONG if failure or VOS_OK if success
 Other      :
 *****************************************************************************/
VOS_UINT32 VOS_Listen( VOS_SOCKET s, VOS_INT32 backlog )
{
    if ( 0 == listen( (SOCKET)s , (VOS_INT)backlog) )
    {
        return VOS_OK;
    }
    else
    {
        return VOS_NULL_LONG;
    }
}

/*****************************************************************************
 Function   : VOS_IoctlSocket
 Description: controls the I/O mode of a socket
 Called By  :
 Input      : s -- identifying a socket to close
              cmd -- command to perform on the socket
              parg -- pointer to a parameter for cmd
 Output     :
 Return     : VOS_OK if success or VOS_NULL_LONG if failure
 Other      :
 *****************************************************************************/
VOS_UINT32 VOS_IoctlSocket( VOS_SOCKET s, VOS_INT32  cmd, VOS_INT32 *parg )
{
    if ( 0 == ioctlsocket( (SOCKET)s, (VOS_INT32)cmd, (VOS_UINT32 *)parg ))
    {
        return  VOS_OK;
    }
    else
    {
        return VOS_NULL_LONG;
    }
}

/*****************************************************************************
 Function   : VOS_SocketInit
 Description: Initialization for later use
 Calls      :
 Called By  :
 Input      :
 Output     :
 Return     : VOS_OK if success or VOS_NULL_LONG if failure
 Other      :
 *****************************************************************************/
VOS_UINT32 VOS_SocketInit(VOS_VOID)
{
    return VOS_OK;
}


#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */




