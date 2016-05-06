/********************************************************************
*                          icmp6_sh_pub.h
*  Project Code    : VRP3.0
*  Author          : Mayun  / Mahaveer Jain
*  Create Date     : 2002-8-20
*  Version         :
*  Description     : 本文件是icmp6.h文件
*  Others          :
*---------------------------------------------------------------------
*  Modification History
*  DATE        NAME       DESCRIPTION
*---------------------------------------------------------------------
* 2006-09-14   Alok       Updated for 14 Fly-Check rules adherence
*                         for IPBIRV1R2.IPv6
*---------------------------------------------------------------------
*  Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc.
*                      ALL RIGHTS RESERVED
*********************************************************************/

#ifndef _ICMP6_SH_PUB_H_
#define _ICMP6_SH_PUB_H_

#ifdef  __cplusplus
extern "C"{
#endif

#define IP6_ICMP6_SH_SSA   ((SYSTRC_IPV6_ICMP6_BASE << 8) + 24)
#define IP6_ICMP6_SH_IC    ((SYSTRC_IPV6_ICMP6_BASE << 8) + 23)
#define IP6_ICMP6_SH_CFG   ((SYSTRC_IPV6_ICMP6_BASE << 8) + 22)
#define IP6_ICMP6_SH_INIT  ((SYSTRC_IPV6_ICMP6_BASE << 8) + 21)
#define IP6_ICMP6_SH_MIB   ((SYSTRC_IPV6_ICMP6_BASE << 8) + 25)

/* To remove L4 warning regarding unused function arguments */
#ifndef NO_USE
#define NO_USE(macro_var)     (VOID)(macro_var)
#endif

#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _ICMP6_PUB_H_ */

