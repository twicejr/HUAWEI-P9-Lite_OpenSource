/****************************************************************************/
/*                                                                          */
/*                          ip6_pub.h                                       */
/*                                                                          */
/*  Project Code    : VRP3.0                                                */
/*  Author          :                                                       */
/*  Create Date     :                                                       */
/*  Description     :                                                       */
/*  Others          :                                                       */
/*--------------------------------------------------------------------------*/
/*  Function List   :                                                       */
/*  Name                Function                                            */
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc.     */
/*                      ALL RIGHTS RESERVED                                 */
/*                                                                          */
/****************************************************************************/

#if (VRP_MODULE_IPV6 == VRP_YES)

#ifndef _IP6_PUB_H
#define _IP6_PUB_H

#ifdef __cplusplus
extern "C"{
#endif
#ifndef TCPIP_DOUBLEOS
/************************************************************************
                  ADDR module defination
*************************************************************************/
#define IN6_IS_ADDR_UNSPECIFIED(a)    \
        (((a)->s6_addr32[0] == 0) &&((a)->s6_addr32[1] == 0) && \
         ((a)->s6_addr32[2] == 0) &&((a)->s6_addr32[3] == 0))

/* 判断地址是否相同的宏IN6_ARE_ADDR_EQUAL
   输入：IN6ADDR_S  *a    指向待判断的地址
        IN6ADDR_S  *b    指向待判断的地址
   返回：0——不同    1——相同     */
#define IN6_ARE_ADDR_EQUAL(a,b)    \
                 (((a)->s6_addr32[0] == (b)->s6_addr32[0]) &&    \
                  ((a)->s6_addr32[1] == (b)->s6_addr32[1]) &&    \
                  ((a)->s6_addr32[2] == (b)->s6_addr32[2]) &&    \
                  ((a)->s6_addr32[3] == (b)->s6_addr32[3]))


/* 环回地址判断宏IN6_IS_ADDR_LOOPBACK
   输入：IN6ADDR_S  *a    指向待判断地址的指针
   返回：0——不是环回地址;   1——是环回地址 */
#define IN6_IS_ADDR_LOOPBACK(a)    \
        /*lint -save -e572*/ \
        (((a)->s6_addr32[0] == 0) &&((a)->s6_addr32[1] == 0) && \
         ((a)->s6_addr32[2] == 0) &&((a)->s6_addr32[3] == VOS_HTONL(1)))\
        /*lint -restore*/

/* SockIP_DEV_END, by m41080 2006-06-21 */


/* 链路本地地址判断宏IN6_IS_ADDR_LINKLOCAL
   输入：IN6ADDR_S  *a    指向待判断地址的指针
   返回：0——不是链路本地地址类型;   1——是链路本地地址类型   */
#define IN6_IS_ADDR_LINKLOCAL(a)    \
        (((a)->s6_addr[0] == 0xfe) && (((a)->s6_addr[1] & 0xc0) == 0x80))


/* 站点本地地址判断宏IN6_IS_ADDR_SITELOCAL
   输入：IN6ADDR_S  *a    指向待判断地址的指针
   返回：0——不是站点本地地址类型;   1——是站点本地地址类型 */
#define IN6_IS_ADDR_SITELOCAL(a)    \
        (((a)->s6_addr[0] == 0xfe) && (((a)->s6_addr[1] & 0xc0) == 0xc0))


/* 组播地址判断宏IN6_IS_ADDR_MULTICAST
   输入：IN6ADDR_S  *a    指向待判断地址的指针
   返回：0——不是组播地址类型;   1——是组播地址类型 */
#define IN6_IS_ADDR_MULTICAST(a)    ((a)->s6_addr[0] == 0xff)

#define IN6_IS_ADDR_LINKLOCAL_MULTICAST(a)    \
        (((a)->s6_addr[0] == 0xff) && (((a)->s6_addr[1] & 0x0f) == 0x02))

/* 未指定地址判断宏IN6_IS_ADDR_UNSPECIFIED
   输入：IN6ADDR_S  *a    指向待判断地址的指针
   返回：0——不是未指定地址类型;    1——是组播地址类型 */
#define IN6_IS_ADDR_UNSPECIFIED(a)    \
        (((a)->s6_addr32[0] == 0) &&((a)->s6_addr32[1] == 0) && \
         ((a)->s6_addr32[2] == 0) &&((a)->s6_addr32[3] == 0))


#define IN6_IS_ADDR_SOLICITED_MULTICAST(a)    \
        ( /*lint -e572*/ /*lint -e648*/((a)->s6_addr16[0] == VOS_HTONS(0xff02)) &&((a)->s6_addr32[1] == 0) && \
         ((a)->s6_addr32[2] == VOS_HTONL(1)) &&((a)->s6_addr8[12] == 0xff) /*lint +e572*/ /*lint +e648*/)

/*                 (((a)->s6_addr16[0] == IP6_ADDR_INT16_MLL) && \
             ((a)->s6_addr32[1] == 0) &&  \
            ((a)->s6_addr32[2] == VOS_HTONL(1)) && \
            ((a)->s6_addr8[12] == 0xff))*/


/* 环回地址判断宏IN6_IS_ADDR_LOOPBACK
   输入：IN6ADDR_S  *a    指向待判断地址的指针
   返回：0——不是环回地址;   1——是环回地址 */
#define IN6_IS_ADDR_LOOPBACK(a)    \
        /*lint -save -e572*/ \
        (((a)->s6_addr32[0] == 0) &&((a)->s6_addr32[1] == 0) && \
         ((a)->s6_addr32[2] == 0) &&((a)->s6_addr32[3] == VOS_HTONL(1)))\
        /*lint -save -e572*/


/* 与IPv4地址兼容的IPv6地址判断宏
   输入：IN6ADDR_S  *a    指向待判断地址的指针
   返回：0——不是与IPv4地址兼容的IPv6地址; 1——是与IPv4地址兼容的IPv6地址 */
#define IN6_IS_ADDR_V4COMPAT(a)    \
        (      /*lint -e572*/ /*lint -e648*/((a)->s6_addr32[0] == 0) &&((a)->s6_addr32[1] == 0) && \
         ((a)->s6_addr32[2] == 0) &&((a)->s6_addr32[3] !=0) && \
         ((a)->s6_addr32[3] != VOS_HTONL(1))      /*lint +e572*/ /*lint +e648*/ )


/* 与IPv4地址映射的IPv6地址判断宏
   输入：IN6ADDR_S  *a    指向待判断地址的指针
   返回：0——不是与IPv4地址映射的IPv6地址;  1——是与IPv4地址映射的IPv6地址 */
#define IN6_IS_ADDR_V4MAPPED(a)    \
       (        /*lint -e572*/ /*lint -e648*/((a)->s6_addr32[0] == 0) &&((a)->s6_addr32[1] == 0) && \
        ((a)->s6_addr32[2] == VOS_HTONL(0x0000ffff))         /*lint +e572*/        /*lint +e648*/ )


/* 计算单播地址对应的请求节点组播地址的宏
   根据输入的IPv6单播地址计算与其对应的请求节点组播组地址
   输入：IN6ADDR_S  *a    单播地址指针
   输出：IN6ADDR_S  *b    请求节点组播地址指针   */
#define IP6_GETMULTIADDR_SOLICITEDNODE(a,b)    \
       {  ULONG c = 0xFF020000; \
          ULONG d = 0x1; \
         (b)->s6_addr32[0] = VOS_HTONL(c);    \
         (b)->s6_addr32[1] = 0;    \
         (b)->s6_addr32[2] = VOS_HTONL(d);    \
         (b)->s6_addr32[3] = (a)->s6_addr32[3];    \
         (b)->s6_addr8[12] = 0xff;    }


/* 计算单播地址对应的网络地址的宏
   根据输入的IPv6单播地址以及其前缀掩码计算与其对应的网络地址
   输入：IN6ADDR_S  *a    单播地址指针
        IN6ADDR_S  *b    单播地址前缀掩码指针
   输出：IN6ADDR_S  *c    网络地址指针   */
#define IP6_GETPREFIX_FROMADDRANDMASK(a,b,c)    \
       { (c)->s6_addr32[0] = ((a)->s6_addr32[0]) & ((b)->s6_addr32[0]); \
         (c)->s6_addr32[1] = ((a)->s6_addr32[1]) & ((b)->s6_addr32[1]); \
         (c)->s6_addr32[2] = ((a)->s6_addr32[2]) & ((b)->s6_addr32[2]); \
         (c)->s6_addr32[3] = ((a)->s6_addr32[3]) & ((b)->s6_addr32[3]); }


/* Sachin :- Converting address from Network to Host and host to network byte
order*/

#define IPV6_ADDRESS_NTOH(aul4Addr) \
        {\
           (aul4Addr)[0] = VOS_NTOHL((aul4Addr)[0]);\
           (aul4Addr)[1] = VOS_NTOHL((aul4Addr)[1]);\
           (aul4Addr)[2] = VOS_NTOHL((aul4Addr)[2]);\
           (aul4Addr)[3] = VOS_NTOHL((aul4Addr)[3]);\
        }
/*aul4Addr must be a array that have 4 ULONG element */
#define IPV6_ADDRESS_HTON(aul4Addr) \
        {\
           (aul4Addr)[0] = VOS_HTONL((aul4Addr)[0]);\
           (aul4Addr)[1] = VOS_HTONL((aul4Addr)[1]);\
           (aul4Addr)[2] = VOS_HTONL((aul4Addr)[2]);\
           (aul4Addr)[3] = VOS_HTONL((aul4Addr)[3]);\
        }

/* 常用IPv6地址的宏定义 */
#define IN6ADDR_ANY_INIT \
    {{{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }}}

#define IPV6_NDPACKET      0x00000040
#define IPV6_INDPACKET     0x00000080
#else
/************************************************************************
                  ADDR module defination
*************************************************************************/
#define VRP_IN6_IS_ADDR_UNSPECIFIED(a)    \
        (((a)->s6_addr32[0] == 0) &&((a)->s6_addr32[1] == 0) && \
         ((a)->s6_addr32[2] == 0) &&((a)->s6_addr32[3] == 0))

/* 判断地址是否相同的宏IN6_ARE_ADDR_EQUAL
   输入：IN6ADDR_S  *a    指向待判断的地址
        IN6ADDR_S  *b    指向待判断的地址
   返回：0——不同    1——相同     */
#define VRP_IN6_ARE_ADDR_EQUAL(a,b)    \
                 (((a)->s6_addr32[0] == (b)->s6_addr32[0]) &&    \
                  ((a)->s6_addr32[1] == (b)->s6_addr32[1]) &&    \
                  ((a)->s6_addr32[2] == (b)->s6_addr32[2]) &&    \
                  ((a)->s6_addr32[3] == (b)->s6_addr32[3]))


/* 环回地址判断宏IN6_IS_ADDR_LOOPBACK
   输入：IN6ADDR_S  *a    指向待判断地址的指针
   返回：0——不是环回地址;   1——是环回地址 */
#define VRP_IN6_IS_ADDR_LOOPBACK(a)    \
        /*lint -save -e572*/ \
        (((a)->s6_addr32[0] == 0) &&((a)->s6_addr32[1] == 0) && \
         ((a)->s6_addr32[2] == 0) &&((a)->s6_addr32[3] == VOS_HTONL(1)))\
        /*lint -restore*/

/* SockIP_DEV_END, by m41080 2006-06-21 */


/* 链路本地地址判断宏IN6_IS_ADDR_LINKLOCAL
   输入：IN6ADDR_S  *a    指向待判断地址的指针
   返回：0——不是链路本地地址类型;   1——是链路本地地址类型   */
#define VRP_IN6_IS_ADDR_LINKLOCAL(a)    \
        (((a)->s6_addr[0] == 0xfe) && (((a)->s6_addr[1] & 0xc0) == 0x80))


/* 站点本地地址判断宏IN6_IS_ADDR_SITELOCAL
   输入：IN6ADDR_S  *a    指向待判断地址的指针
   返回：0——不是站点本地地址类型;   1——是站点本地地址类型 */
#define VRP_IN6_IS_ADDR_SITELOCAL(a)    \
        (((a)->s6_addr[0] == 0xfe) && (((a)->s6_addr[1] & 0xc0) == 0xc0))


/* 组播地址判断宏IN6_IS_ADDR_MULTICAST
   输入：IN6ADDR_S  *a    指向待判断地址的指针
   返回：0——不是组播地址类型;   1——是组播地址类型 */
#define VRP_IN6_IS_ADDR_MULTICAST(a)    ((a)->s6_addr[0] == 0xff)

#define VRP_IN6_IS_ADDR_LINKLOCAL_MULTICAST(a)    \
        (((a)->s6_addr[0] == 0xff) && (((a)->s6_addr[1] & 0x0f) == 0x02))

/* 未指定地址判断宏IN6_IS_ADDR_UNSPECIFIED
   输入：IN6ADDR_S  *a    指向待判断地址的指针
   返回：0——不是未指定地址类型;    1——是组播地址类型 */
#define VRP_IN6_IS_ADDR_UNSPECIFIED(a)    \
        (((a)->s6_addr32[0] == 0) &&((a)->s6_addr32[1] == 0) && \
         ((a)->s6_addr32[2] == 0) &&((a)->s6_addr32[3] == 0))


#define VRP_IN6_IS_ADDR_SOLICITED_MULTICAST(a)    \
        (((a)->s6_addr16[0] == VOS_HTONS(0xff02)) &&((a)->s6_addr32[1] == 0) && \
         ((a)->s6_addr32[2] == VOS_HTONL(1)) &&((a)->s6_addr8[12] == 0xff))

/*                 (((a)->s6_addr16[0] == IP6_ADDR_INT16_MLL) && \
             ((a)->s6_addr32[1] == 0) &&  \
            ((a)->s6_addr32[2] == VOS_HTONL(1)) && \
            ((a)->s6_addr8[12] == 0xff))*/


/* 环回地址判断宏IN6_IS_ADDR_LOOPBACK
   输入：IN6ADDR_S  *a    指向待判断地址的指针
   返回：0——不是环回地址;   1——是环回地址 */
#define VRP_IN6_IS_ADDR_LOOPBACK(a)    \
        /*lint -save -e572*/ \
        (((a)->s6_addr32[0] == 0) &&((a)->s6_addr32[1] == 0) && \
         ((a)->s6_addr32[2] == 0) &&((a)->s6_addr32[3] == VOS_HTONL(1)))\
        /*lint -save -e572*/


/* 与IPv4地址兼容的IPv6地址判断宏
   输入：IN6ADDR_S  *a    指向待判断地址的指针
   返回：0——不是与IPv4地址兼容的IPv6地址; 1——是与IPv4地址兼容的IPv6地址 */
#define VRP_IN6_IS_ADDR_V4COMPAT(a)    \
        (((a)->s6_addr32[0] == 0) &&((a)->s6_addr32[1] == 0) && \
         ((a)->s6_addr32[2] == 0) &&((a)->s6_addr32[3] !=0) && \
         ((a)->s6_addr32[3] != VOS_HTONL(1)) )


/* 与IPv4地址映射的IPv6地址判断宏
   输入：IN6ADDR_S  *a    指向待判断地址的指针
   返回：0——不是与IPv4地址映射的IPv6地址;  1——是与IPv4地址映射的IPv6地址 */
#define VRP_IN6_IS_ADDR_V4MAPPED(a)    \
       (((a)->s6_addr32[0] == 0) &&((a)->s6_addr32[1] == 0) && \
        ((a)->s6_addr32[2] == VOS_HTONL(0x0000ffff)) )


/* 计算单播地址对应的请求节点组播地址的宏
   根据输入的IPv6单播地址计算与其对应的请求节点组播组地址
   输入：IN6ADDR_S  *a    单播地址指针
   输出：IN6ADDR_S  *b    请求节点组播地址指针   */
#define VRP_IP6_GETMULTIADDR_SOLICITEDNODE(a,b)    \
       { (b)->s6_addr32[0] = VOS_HTONL(0xFF020000);    \
         (b)->s6_addr32[1] = 0;    \
         (b)->s6_addr32[2] = VOS_HTONL(1);    \
         (b)->s6_addr32[3] = (a)->s6_addr32[3];    \
         (b)->s6_addr8[12] = 0xff;    }


/* 计算单播地址对应的网络地址的宏
   根据输入的IPv6单播地址以及其前缀掩码计算与其对应的网络地址
   输入：IN6ADDR_S  *a    单播地址指针
        IN6ADDR_S  *b    单播地址前缀掩码指针
   输出：IN6ADDR_S  *c    网络地址指针   */
#define VRP_IP6_GETPREFIX_FROMADDRANDMASK(a,b,c)    \
       { (c)->s6_addr32[0] = ((a)->s6_addr32[0]) & ((b)->s6_addr32[0]); \
         (c)->s6_addr32[1] = ((a)->s6_addr32[1]) & ((b)->s6_addr32[1]); \
         (c)->s6_addr32[2] = ((a)->s6_addr32[2]) & ((b)->s6_addr32[2]); \
         (c)->s6_addr32[3] = ((a)->s6_addr32[3]) & ((b)->s6_addr32[3]); }


/* Sachin :- Converting address from Network to Host and host to network byte
order*/

#define VRP_IPV6_ADDRESS_NTOH(aul4Addr) \
        {\
           (aul4Addr)[0] = VOS_NTOHL((aul4Addr)[0]);\
           (aul4Addr)[1] = VOS_NTOHL((aul4Addr)[1]);\
           (aul4Addr)[2] = VOS_NTOHL((aul4Addr)[2]);\
           (aul4Addr)[3] = VOS_NTOHL((aul4Addr)[3]);\
        }
/*aul4Addr must be a array that have 4 ULONG element */
#define VRP_IPV6_ADDRESS_HTON(aul4Addr) \
        {\
           (aul4Addr)[0] = VOS_HTONL((aul4Addr)[0]);\
           (aul4Addr)[1] = VOS_HTONL((aul4Addr)[1]);\
           (aul4Addr)[2] = VOS_HTONL((aul4Addr)[2]);\
           (aul4Addr)[3] = VOS_HTONL((aul4Addr)[3]);\
        }

/* 常用IPv6地址的宏定义 */
#define VRP_IN6ADDR_ANY_INIT \
    {{{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }}}

#define VRP_IPV6_NDPACKET      0x00000040
#define VRP_IPV6_INDPACKET     0x00000080
#endif

#ifdef __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _IP6_TYPE_H_ */

#endif  /* end of VRP_MODULE_IPV6 */
