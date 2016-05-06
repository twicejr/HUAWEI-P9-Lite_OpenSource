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

 
#ifndef _IP6_PUB_H
#define _IP6_PUB_H

#ifdef __cplusplus
extern "C"{
#endif

#include "ipv6/ppmng/core/include/ppmng_pub.h"
#include "ipv6/ppmng/core/include/ppmng_proto_mgnt.h"

/* IPv6 address数据结构
   该结构定义了IPv6地址的内容。
   描述了IPv6地址128bit的具体内容，采用共用体来方便对地址字段的操作 */

/* 判断地址是否相同的宏IN6_ARE_ADDR_EQUAL
   输入：IN6ADDR_S  *a    指向待判断的地址
        IN6ADDR_S  *b    指向待判断的地址
   返回：0——不同    1——相同     */
#define IN6_ARE_ADDR_EQUAL(a,b)    \
                 (((a)->s6_addr32[0] == (b)->s6_addr32[0]) &&    \
                  ((a)->s6_addr32[1] == (b)->s6_addr32[1]) &&    \
                  ((a)->s6_addr32[2] == (b)->s6_addr32[2]) &&    \
                  ((a)->s6_addr32[3] == (b)->s6_addr32[3]))

#define IN6_IS_ADDR_MULTICAST(a)    ((a)->s6_addr[0] == 0xff)

#ifdef __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _IP6_TYPE_H_ */
