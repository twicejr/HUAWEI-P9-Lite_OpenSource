/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              macro.h
*
*  Project Code: VISP1.5
*   Module Name: socket4  
*  Date Created: 2006-4-29
*        Author: l(48769)
*   Description: socket macro definition
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-04-27   l(48769)        根据编程规范，对文件进行规范化整理
*
*******************************************************************************/
#ifndef        _MACRO_H
#define        _MACRO_H

#ifdef    __cplusplus
extern    "C"{
#endif

#ifndef TYPEDEF_TASK_T
#define TYPEDEF_TASK_T
typedef ULONG    task_t;
#endif

#define        CCTIMEO            60

#define        SRTIMEO            0

#define        SSTACK            0x1000
#define        USTACK            0x1000

#ifndef        SIGPIPE
#define        SIGPIPE            13
#endif

#define        SIGURG             16
#define        SIGIO              18

/* BYAD06469 -- xiaoqingsong 29316, 
 * With around 4k CRLSP's,on disabling RSVP on interface, some CRLSP's remain in remote routers.*
 * IP queue length is not enough, old value is 1800, modified to 5000 *
 */
#define        SBMAX        (8192*1024L)

/* #define  FILENUM      20 */
/*x36317 SOCKET预配置:最大的SOCKET数2004-7-23*/
#define     FILENUM         (g_stSOCK4ModInfo.ulSKT_MAX_SOCK_N)
/* Modify for DTS2011031503749, by yuehaitao171195, at 2011-03-17. 修改原因: TSleep
   阻塞时并没有持有信号量，此时如果其他任务创建了多个socket，则socket可能扩充文件描述符，导致TSleep返回后访问野内存 */
#define     EXPANDNUM       FILENUM

/*used by f_ucState*/
#define        BUSY            1
#define        IDLE            0

/*used by f_ucType*/
#define         DTYPE_VNODE        0x01
#define         DTYPE_SOCKET       0x02
#define         DTYPE_PARENT       0x04

/*used by f_ucFlags*/
#define        FREAD             0x01
#define        FWRITE            0x02

#define        D_FILE            0x01
#define        D_SOCK            0x02

#define        BLOCK              1
#define        NOBLOCK            0

/*socket events*/
#define         SE_CONNECT  0x0001
#define         SE_CLOSE    0x0002
#define         SE_LOCKWAIT 0x0004
#define         SE_WAIT     0x0008
#define         SE_SEL      0x0010
#define         SE_ASYNSOCK SE_ASYNC
#define         SE_SP       0x0040

/*used by select collision flags */
#define            SI_COLL        1

/*---------------------------------------------------------------------*/
/* the following are used by socmd.c                                   */
/*---------------------------------------------------------------------*/
#define        MAXHOSTNUM      50
#define        HostNameLen           (IP_HOSTNAME_LEN+1)  /* modify by x36530 trace to D08067 */
#define        IPADDRMAXLEN    19
#define        ADDITIONCHAR    3
#define        HOSTNAMELEN    HostNameLen
/*Added by zhaobiao for ip host command*/
#define         MAXHOSTADDRNO   8

#define        HOSTINFOSTRLEN        (HOSTNAMELEN+IPADDRMAXLEN+ADDITIONCHAR)

#define         TCP_SOCKET      0
#define         UDP_SOCKET      1
#define         RAWIP_SOCKET    2 

#define         SOCK_PERMINENT_OK 0

/*FOR del host */
#define DELHOSTBYNAME        0
#define DELHOSTBYNAMEADDR    1

#define SOCKET_SENDBUF   1
#define SOCKET_RECVBUF   2


#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */

#endif
