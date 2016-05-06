/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              sock_def.h
*
*  Project Code: VISP1.5
*   Module Name: socket4  
*  Date Created: 2006-11-14
*        Author: wangtao(60012929)
*   Description: the private macro
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2006-11-14   wangtao(60012929)       Create
*
*******************************************************************************/

#ifndef _SOCK_DEF_H
#define _SOCK_DEF_H

#ifdef    __cplusplus
extern    "C"{
#endif

/*****************************************************
* the macro fro socket, they are define in .c
*****************************************************/
#ifndef INADDR_NONE
#define  INADDR_NONE     0XFFFFFFFF    /* no address, used in tool.c */
#endif

/*****************************************************
* the macro fro tcp,udp, they are define in .c
*****************************************************/
/* used in TCPInput(), it is the second of 24 days */
#define TCP_PAWS_IDLE   (24 * 24 * 60 * 60 * PR_SLOWHZ)    
/* Comparisons of timestamps */
#define TSTMP_LT(a,b)   ((LONG)((a)-(b)) < 0)
#define TSTMP_GEQ(a,b)  ((LONG)((a)-(b)) >= 0)

/* 
 * 由于tcp中增加了新的选项,选项的总长度可能达到40字节,
 * 因此定义的字符串 长度由32修改为41, TCP MD5 authentication, 
 * zhangfeng, 2002,07,20 
 */
#define MAX_TCPOPTLEN     /* 32 */ 41 /* max # bytes that go in options */

/* 判断是否vrrp的多播地址，224.0.0.18 主机字节序 */
#define SOCK_IS_VRRPR_ADDR(MultiAddr)  (0xe0000012 == MultiAddr)   

#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */


#endif

