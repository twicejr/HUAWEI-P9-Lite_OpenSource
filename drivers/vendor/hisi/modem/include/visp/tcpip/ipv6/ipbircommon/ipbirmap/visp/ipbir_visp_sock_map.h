#ifndef _IPBIR_VISP_SOCK_MAPP_H_
#define _IPBIR_VISP_SOCK_MAPP_H_

#ifdef    __cplusplus
extern "C"{
#endif

#define IPB_IR_VRP_EVENT_ASOCKETREQ     SE_ASYNC

/* Following Macros will be used for implementing Socket APIs */

#define IPB_IR_SOCK_SOCKET(lFamily, lType, lProtocol) \
    socket(lFamily, lType, lProtocol)


#define IPB_IR_SOCK_BIND(lFd, pvSockAddrin, lAddrLen) \
    bind(lFd, pvSockAddrin, lAddrLen)


#define IPB_IR_SOCK_SETSOCKOPT(lFd, lLevel, lOptName, pcOptVal, lnOptLen) \
    setsockopt(lFd, lLevel, lOptName, pcOptVal, lnOptLen)


#define IPB_IR_SOCK_GETSOCKOPT(lFd, lLevel, lOptName, pcOptVal, plnOptLen) \
    getsockopt(lFd, lLevel, lOptName, pcOptVal, plnOptLen)


#define IPB_IR_SOCK_IOCTL(lFd, ulCmd, pcBuf) \
    ioctl(lFd, ulCmd, pcBuf)


#define IPB_IR_SOCK_SENDMSG(lFd, pvSockMsg, lFlags) \
    sendmsg(lFd, pvSockMsg, lFlags)


#define IPB_IR_SOCK_RECVMSG(lFd, pvSockMsg, lFlags) \
    recvmsg(lFd, pvSockMsg, lFlags)


#define IPB_IR_SOCK_CLOSE(lFd) \
    close(lFd)

#define IPB_IR_SOCK_COPYSOCKET(ulTaskIdFrom, ulTaskIdTo, iFd, iAlterFd) \
    CopySocket(ulTaskIdFrom, ulTaskIdTo, iFd, iAlterFd)

/* End : Rajat Phull, 2007-05-15 */

#ifdef __cplusplus
}
#endif        /* end of __cplusplus */

#endif  /* end of _IPBIR_VISP_SOCK_MAPP_H_ */


