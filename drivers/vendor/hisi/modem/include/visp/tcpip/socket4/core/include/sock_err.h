/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              sock_deb.h
*
*  Project Code: VISP1.5
*   Module Name: socket4
*  Date Created: 2006-4-29
*        Author: l(48769)
*   Description: error NO. for socket,tcp,udp
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  -----------------------------------------------------------------------------
*  2006-04-27   l(48769)        根据编程规范，对文件进行规范化整理
*
*******************************************************************************/
#ifndef _SOCK_ERR_H
#define _SOCK_ERR_H

#ifdef    __cplusplus
extern    "C"{
#endif

#define    EPERM            -1        /* 操作非法  Operation not permitted */
#define    ENOENT           -2        /* 文件或目录不存在  No such file or directory */
#define    ESRCH            -3        /* 过程非法  No such process */
#define    EINTR            -4        /* 系统中断调用失败  Interrupted system call */
#define    EIO              -5        /* 输入/输出错误  Input/output error */
#define    ENXIO            -6        /* 接口设备不存在  Device not configured */
#define    E2BIG            -7        /* 参数列表过长  Argument list too long */
#define    ENOEXEC          -8        /* 格式错误  Exec format error */
#define    EBADF            -9        /* 与iFd相关文件数组元素状态错误(非BUSY)或标记错误(非FREAD|FWRITE)Bad file descriptor */
#define    ECHILD           -10       /* 未找到下一级处理过程  No child processes */
#define    EDEADLK          -11       /* 资源不足  Resource deadlock avoided */
                                      /* 11 was EAGAIN */
#define    ENOMEM           -12       /* 因内存不足不能创建socket  Cannot allocate memory */
#define    EACCES           -13       /* 权限非法  Permission denied */
#define    EFAULT           -14       /* 地址非法  Bad address */
#define    ENOTBLK          -15       /* 必须有块设备  Block device required */
#define    EBUSY            -16       /* 设备忙  Device busy */
#define    EEXIST           -17       /* 文件已存在  File exists */
#define    EXDEV            -18       /* 设备交叉连接  Cross-device link */
#define    ENODEV           -19       /* 设备不支持此操作  Operation not supported by device */
#define    ENOTDIR          -20       /* 不是一个目录  Not a directory */
#define    EISDIR           -21       /* 是一个目录  Is a directory */
#define    EINVALID         -22       /* socket ID不可用  Invalid argument */
#define    ENFILE           -23       /* 在系统中的socket描述符都已经分配完毕  Too many open files in system */
#define    EMFILE           -24       /* socket描述符都已经分配完毕没有可分的描述符  Too many open files */
#define    ENOTTY           -25       /* 设备的IO操作非法  Inappropriate ioctl for device */
#define    ETXTBSY          -26       /* 文件忙  Text file busy */
#define    EFBIG            -27       /* 文件超长  File too large */
#define    ENOSPC           -28       /* 设备内存不足  No space left on device */
#define    ESPIPE           -29       /* 搜索非法  Illegal seek */
#define    EROFS            -30       /* 只读系统  Read-only file system */
#define    EMLINK           -31       /* 连接超限  Too many links */
#define    EPIPE            -32       /* socket状态为SS_CANTSENDMORE原因是应用程序调用close或shutdown关闭socket  Broken pipe */

/* math software */
#define    EDOM             -33        /* Numerical argument out of domain */
#define    ERANGEE          -34        /* Result too large */

/* non-blocking and interrupt i/o */
#define    EAGAIN           -35        /* Resource temporarily unavailable */
#define    EWOULDBLOCK      EAGAIN     /* Operation would block */
#define    EINPROGRESS      -36        /* Operation now in progress */
#define    EALREADY         -37        /* Operation already in progress */

/* ipc/network software -- argument errors */
#define    ENOTSOCK         -38        /* Socket operation on non-socket */
#define    EDESTADDRREQ     -39        /* Destination address required */
#define    EMSGSIZE         -40        /* Message too LONG */
#define    EPROTOTYPE       -41        /* Protocol wrong type for socket */
#define    ENOPROTOOPT      -42        /* Protocol not available */
#define    EPROTONOSUPPORT  -43        /* Protocol not supported */
#define    ESOCKTNOSUPPORT  -44        /* Socket type not supported */
#define    EOPNOTSUPP       -45        /* Operation not supported */
#define    EPFNOSUPPORT     -46        /* Protocol family not supported */
#define    EAFNOSUPPORT     -47        /* Address family not supported by protocol family */
#define    EADDRINUSE       -48        /* Address already in use */
#define    EADDRNOTAVAIL    -49        /* Can't assign requested address */

/* ipc/network software -- operational errors */
#define    ENETDOWN       -50        /* Network is down */
#define    ENETUNREACH    -51        /* Network is unreachable */
#define    ENETRESET      -52        /* Network dropped connection on reset */
#define    ECONNABORTED   -53        /* Software caused connection abort */
#define    ECONNRESET     -54        /* Connection reset by peer */
#define    ENOBUFS        -55        /* No buffer space available */
#define EQDROP            -56        /* Drops a packet because queue us full */
#define    EISCONN        -57        /* Socket is already connected */
#define    ENOTCONN       -58        /* Socket is not connected */
#define    ESHUTDOWN      -59        /* Can't send after socket shutdown */
#define    ETOOMANYREFS   -60        /* Too many references: can't splice */
#define    ETIMEDOUT      -61        /* Operation timed out */
#define    ECONNREFUSED   -62        /* Connection refused */

#define    ELOOP          -63        /* Too many levels of symbolic links */

#define    ENAMETOOLONG   -64        /* File name too long */

/* should be rearranged */
#define    EHOSTDOWN      -65        /* Host is down */
#define    EHOSTUNREACH   -66        /* No route to host */
#define    ENOTEMPTY      -67        /* Directory not empty */

/* quotas & mush */
#define    EPROCLIM       -68        /* Too many processes */
#define    EUSERS         -69        /* Too many users */
#define    EDQUOT         -70          /* Disc quota exceeded */

/* Network File System */
#define    ESTALE         -71        /* Stale NFS file handle */
#define    EREMOTE        -72        /* Too many levels of remote in path */
#define    EBADRPC        -73        /* RPC struct is bad */
#define    ERPCMISMATCH   -74        /* RPC version wrong */
#define    EPROGUNAVAIL   -75        /* RPC prog. not avail */
#define    EPROGMISMATCH  -76        /* Program version wrong */
#define    EPROCUNAVAIL   -77        /* Bad procedure for program */

#define    ENOLCK         -78        /* No locks available */
#define    ENOSYS         -79        /* Function not implemented */

#define    EFTYPE         -80        /* Inappropriate file type or format */
#define    EAUTH          -81        /* Authentication error */
#define    ENEEDAUTH      -82        /* Need authenticator */
#define    ELAST          -83        /* Must be equal largest errno */


/* pseudo-errors returned inside kernel to modify return to process */
#define    ERESTART       -84        /* restart syscall */
#define    EJUSTRETURN    -85        /* don't modify regs, just return    */

#define    ETASKCREATE    -86        /*    don't create task                */
#define    ETASKDELETE    -87        /*    don't delete task                */
#define    ETASKGETID     -88        /*    have not task                    */
#define    EPRISET        -89        /*    can't set pritioy                */

#define    EEVRECEIVE     -90        /*    time is out                        */
#define    EEVSEND        -91        /*    ev_nowait is select                */

#define    EQUCREATE      -92        /*    node's object table full        */
#define    EQUDELETE      -93        /*    delete queue fail                */
#define    EQUSEND        -94        /*    send message fail                */
#define    EQURECEIVE     -95        /*    receive message fail            */

#define    ESMCREATE      -96        /*    sm create fail                    */
#define    ESMDELETE      -97        /*    sm delete fail                    */
#define    ESMP           -98        /*    sm p fail                        */
#define    ESMV           -99        /*    sm v fail                        */

#define    ETCBCHECK      -100        /*    has not find the tcb            */
#define    ETCBCREATE     -101        /*    has not create tcb                */
#define    ETCBDELETE     -102        /*    tcb has not delete                */

#define    ENONBIO        -103
#define    ENOASYNC       -104
#define    ENOSETOWN      -105
#define    ENOGETOWN      -106
#define    ENOFIONBIO     -107
#define    ENOFIOASYNC    -108
#define    ENOFIOBACKCALL -109

#define    ECANTTCB       -107

#define    EUIO           -108

#define    ENOPROTO       -109
#define    ENOMG          -110

#define    EBLOCKING      -111
#define    ENOTUDPSOCK    -112
#define    ETCBINUSE      -113

#define ESNDBUFHIWAT      -114

#define ENOTBOUNDALGIN    -117   /*  Not Boundary algin Error for ARM   2006-5-12   x43050  */
#define EDISABLEDFORTEST  -118    /*  VISP V100R005   2006-4-25   x43050  */

#define EMORECONTROL            -120
#define EVOIDINPCB              -121
#define EVOIDTCPCB              -122
/* zhangfeng, 2004,02,27 */

/* Added for SOCKET HA. When switching or smoothing, this error
 * code will be returned if some socket func is called.
 */
#define EISSWITCHINGORSMOOTHING -123

#define ENOTMULTI               -124
#define EINPUTIF                -125
#define ENOTBIND                -126    /*修改问题单A82D18705，rgx 2007-08-09*/

#define EMD5LEN                 -127  /* MD5 P***W*** length is error */
#define EMD5MBFCONT             -128  /* continue MD5 mbuf failed */
#define EMD5PWDCONF             -129  /* add or modify MD5 P***W*** failed */
#define EMD5WRONMASK             -130  /* add or modify MD5 P***W*** failed due to wrong value of mask */


#define EINVAL            -1

#define EFULLSOCK     -200

#define EGADDR          -201    /*错误的组地址*/
#define ESADDR          -202    /*错误的源地址*/
#define EGOVERFLOW      -203    /*接口上配置的组超过限制*/
#define ESOVERFLOW      -204    /*socket上配置的源地址超过限制*/
#define EBLOCKSOURCE    -205    /*阻止一个本身已经被阻止的源地址（组相同）*/
#define EUNBLOCKSOURCE  -206    /*允许一个本身没有被阻止的源地址（组相同）*/
#define EADDSOURCE      -207    /*增加一个已经存在的源地址（组相同）*/
#define EDROPSOURCE     -208    /*删除一个不存在的源地址（组相同）*/
#define EFILTERMODE     -209    /*多播组过滤模式不允许该操作*/
#define ESOURCELISTNULL -210    /*源列表为空*/
#define EIGMPCOMPNULL   -211    /*IGMP组件为空*/
#define EIFTYPE         -212    /*错误的接口类型*/
#define EIFTHISBORD     -213    /*非本板接口*/
#define EGROUPNULL      -214    /*接口未加入指定多播组*/
#define EINVALIDVRF     -215    /*配置接口与当前的所属的VRF冲突或配置的VRF无效*/
#define ENEEDFRAG       -216    /*IP报文需要分片，但是设置了DF标识*/

#define ESOCKCLOSE      -217    /*socket异常，需要关闭*/

#define ENOREMOTEHOST 1000
#define ENOREMOTEADDR 1001
#define ENOBUF        1002

#define TCP_ISN_TCPCB_ERR 0

#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */


#endif
