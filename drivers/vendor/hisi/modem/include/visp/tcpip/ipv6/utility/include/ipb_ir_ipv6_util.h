/******************************************************************************

  Copyright (C), 2001-2011, Huawei Tech. Co., Ltd.

 ******************************************************************************
  File Name     : ipb_ir_ipv6_util.h
  Version       : Initial Draft
  Author        : Prabhu H 71185
  Project Code  : IPB IR V1R2
  Created       : 2006/8/30
  Last Modified :
  Description   : Utility macros and definitions used in IPv6 module
  Function List :
  History       :
  1.Date        : 2006/8/30
    Author      : Prabhu H 71185
    Modification: Created file for IPBIRV100R002.IP.E001

******************************************************************************/

#ifndef _IPB_IR_IPV6_UTIL_H
#define _IPB_IR_IPV6_UTIL_H

#ifdef _cplusplus
extern "C"{
#endif

/*****************************************************************************
 Prototype    : IN6_ADDR_CMP
 Description  : Compares 2 IN6ADDR_S structure elements
 Input        : a - IN6ADDR_S structure
                b - IN6ADDR_S structure
 Output       : None
 Return Value : Returns 0, if two address are equal;
                Returns -1, if 'a' is lesser than 'b';
                Returns 1, if 'a' is greater than 'b';

  History        :
  1.Date         : 2006/8/30
    Author       : Prabhu H 71185
    Modification : Created Macro for IPBIRV100R002.IP.E001

*****************************************************************************/
#if (VRP_BIG_ENDIAN == VRP_YES)
#define IN6_ADDR_CMP(a,b)   \
        (((a)->s6_addr32[0] == (b)->s6_addr32[0]) ? \
        (((a)->s6_addr32[1] == (b)->s6_addr32[1]) ? \
        (((a)->s6_addr32[2] == (b)->s6_addr32[2]) ? \
        (((a)->s6_addr32[3] == (b)->s6_addr32[3]) ? 0 : \
        (((a)->s6_addr32[3] < (b)->s6_addr32[3]) ? -1 : 1)) : \
        (((a)->s6_addr32[2] < (b)->s6_addr32[2]) ? -1 : 1)) : \
        (((a)->s6_addr32[1] < (b)->s6_addr32[1]) ? -1 : 1)) : \
        (((a)->s6_addr32[0] < (b)->s6_addr32[0]) ? -1 : 1))
#else
#define IN6_ADDR_CMP(a,b)   \
    (((a)->s6_addr8[0] == (b)->s6_addr8[0]) ? \
    (((a)->s6_addr8[1] == (b)->s6_addr8[1]) ? \
    (((a)->s6_addr8[2] == (b)->s6_addr8[2]) ? \
    (((a)->s6_addr8[3] == (b)->s6_addr8[3]) ? \
    (((a)->s6_addr8[4] == (b)->s6_addr8[4]) ? \
    (((a)->s6_addr8[5] == (b)->s6_addr8[5]) ? \
    (((a)->s6_addr8[6] == (b)->s6_addr8[6]) ? \
    (((a)->s6_addr8[7] == (b)->s6_addr8[7]) ? \
    (((a)->s6_addr8[8] == (b)->s6_addr8[8]) ? \
    (((a)->s6_addr8[9] == (b)->s6_addr8[9]) ? \
    (((a)->s6_addr8[10] == (b)->s6_addr8[10]) ? \
    (((a)->s6_addr8[11] == (b)->s6_addr8[11]) ? \
    (((a)->s6_addr8[12] == (b)->s6_addr8[12]) ? \
    (((a)->s6_addr8[13] == (b)->s6_addr8[13]) ? \
    (((a)->s6_addr8[14] == (b)->s6_addr8[14]) ? \
    (((a)->s6_addr8[15] == (b)->s6_addr8[15]) ? 0 : \
    (((a)->s6_addr8[15] < (b)->s6_addr8[15]) ? -1 : 1)) : \
    (((a)->s6_addr8[14] < (b)->s6_addr8[14]) ? -1 : 1)) : \
    (((a)->s6_addr8[13] < (b)->s6_addr8[13]) ? -1 : 1)) : \
    (((a)->s6_addr8[12] < (b)->s6_addr8[12]) ? -1 : 1)) : \
    (((a)->s6_addr8[11] < (b)->s6_addr8[11]) ? -1 : 1)) : \
    (((a)->s6_addr8[10] < (b)->s6_addr8[10]) ? -1 : 1)) : \
    (((a)->s6_addr8[9] < (b)->s6_addr8[9]) ? -1 : 1)) : \
    (((a)->s6_addr8[8] < (b)->s6_addr8[8]) ? -1 : 1)) : \
    (((a)->s6_addr8[7] < (b)->s6_addr8[7]) ? -1 : 1)) : \
    (((a)->s6_addr8[6] < (b)->s6_addr8[6]) ? -1 : 1)) : \
    (((a)->s6_addr8[5] < (b)->s6_addr8[5]) ? -1 : 1)) : \
    (((a)->s6_addr8[4] < (b)->s6_addr8[4]) ? -1 : 1)) : \
    (((a)->s6_addr8[3] < (b)->s6_addr8[3]) ? -1 : 1)) : \
    (((a)->s6_addr8[2] < (b)->s6_addr8[2]) ? -1 : 1)) : \
    (((a)->s6_addr8[1] < (b)->s6_addr8[1]) ? -1 : 1)) : \
    (((a)->s6_addr8[0] < (b)->s6_addr8[0]) ? -1 : 1))
#endif

/*****************************************************************************
 Prototype    : DULONG_SELFADD
 Description  : Increments value of DULONG variable by 1
 Input        : dulResult - DULONG variable
 Output       : None
 Return Value : None

  History        :
  1.Date         : 2006/8/30
    Author       : Prabhu H 71185
    Modification : Created Macro for IPBIRV100R002.IP.E001

*****************************************************************************/
#if (TCPIP_IN_VRP == VRP_YES) /*Add by wan temp for built*/
#define DULONG_SELFADD(dulResult) \
{\
    (dulResult).ulLo++; \
    if (0 == (dulResult).ulLo) \
    {\
        (dulResult).ulHi++; \
    }\
}
#endif

#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif /* _IPB_IR_IPV6_UTIL_H */


