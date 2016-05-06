/*****************************************************************************/
/*                                                                           */
/*                Copyright 1999 - 2003, Huawei Tech. Co., Ltd.              */
/*                           ALL RIGHTS RESERVED                             */
/*                                                                           */
/* FileName: v_sock.c                                                        */
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

/* LINUX 不支持 */
#if (VOS_VXWORKS== VOS_OS_VER)
#include "stdio.h"
#endif

#include "v_typdef.h"
#include "v_sock.h"


#if (VOS_VXWORKS == VOS_OS_VER) 

#include "selectLib.h"

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 modify:x51137; review:h59254; cause:print log */
#define    THIS_FILE_ID        PS_FILE_ID_V_SOCK_C
/*lint +e767 modify:x51137; review:h59254; */


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
    return socket( (int)af, (int)type, (int)protocol );
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
    if ( OK == bind( s, paddr, addrlen ) )
    {
        return VOS_OK;
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
    
    ReturnValue = select( width, preadfds, pwritefds, pexceptfds, ptimeout );

    if ( ERROR == ReturnValue ) 
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
    int ReturnValue;
    
    ReturnValue = accept(s, paddr, (int *)paddrlen);
    
    if ( ERROR == ReturnValue ) 
    {
        return (VOS_SOCKET)VOS_NULL_LONG;
    }
    else
    {
        return (VOS_SOCKET)ReturnValue;        
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
    
    ReturnValue = recv(s, buf, len, flags);
    
    
    if ( ERROR == ReturnValue ) 
    {
        return VOS_NULL_LONG;
    }
    else
    {
        return (VOS_UINT32)ReturnValue;        
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
    if ( ERROR == close( (int)s ) )
    {
        return VOS_NULL_LONG;    
    }
    else
    {
        return VOS_OK;
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
    if (  ERROR == send(s, buf, len, flags ) )
    {
        return VOS_ERR;
    }
    else
    {
        return VOS_OK;
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
    if ( OK == listen(s, (VOS_INT32)backlog) )
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
    if ( ERROR == ioctl (s, cmd, *parg) )
    {
        return VOS_NULL_LONG;
    }
    else
    {
        return VOS_OK;
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



