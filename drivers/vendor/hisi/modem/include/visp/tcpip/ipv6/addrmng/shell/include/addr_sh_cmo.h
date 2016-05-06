/**********************************************************************
*                                                                     *
*                      addr_sh_cmo.h                                  *
*                                                                     *
*  Project Code  :     VRP3.1                                         *
*  Create Date   :     2002-8-14                                      *
*  Version       :     IPBIRV100R003.IPv6.E001                        *
*  Author        :     luoli                                          *
*  Modify Date   :                                                    *
*  Document      :     IPv6地址模块所使用的信息                       *
*  Function      :                                                    *
*  Others        :
*  DATE        NAME             DESCRIPTION                           *
*
*---------------------------------------------------------------------*
*                                                                     *
*      Copyright 2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc. *
*                      ALL RIGHTS RESERVED                            *
*                                                                     *
**********************************************************************/
#ifndef _ADDR_SH_CMO_H_
#define _ADDR_SH_CMO_H_


#ifdef __cplusplus
extern "C" {
#endif

#define TBL_IP6_ADDR    0x10
#define TBL_IP6_AUTOCFG  0x11
#define TBL_IP6_MTU  0x12

#define TBL_IP6_SHOWINTF             0x13

/* Show ipv6 interface CMOs*/
#define CMO_IP6_ADDR_SHOWINTF_INTF     \
    CFG_CMO_DEF(MID_IP6_ADDR, TBL_IP6_SHOWINTF, 0)
#define CMO_IP6_ADDR_SHOWINTF_IFTYPE   \
    CFG_CMO_DEF(MID_IP6_ADDR, TBL_IP6_SHOWINTF, 1)
#define CMO_IP6_ADDR_SHOWINTF_IFNUM    \
    CFG_CMO_DEF(MID_IP6_ADDR, TBL_IP6_SHOWINTF, 2)
#define CMO_IP6_ADDR_SHOWINTF_IFNAME   \
    CFG_CMO_DEF(MID_IP6_ADDR, TBL_IP6_SHOWINTF, 3)


#define CMO_IP6ADDRESS         CFG_CMO_DEF(MID_IP6_ADDR, TBL_IP6_ADDR, 1)
#define CMO_IP6PREFIX          CFG_CMO_DEF(MID_IP6_ADDR, TBL_IP6_ADDR, 2)
#define CMO_IP6PREFIXLENGTH    CFG_CMO_DEF(MID_IP6_ADDR, TBL_IP6_ADDR, 3)
#define CMO_IP6ADDRIFINDEX     CFG_CMO_DEF(MID_IP6_ADDR, TBL_IP6_ADDR, 4)
#define CMO_IP6LINKLOCAL       CFG_CMO_DEF(MID_IP6_ADDR, TBL_IP6_ADDR, 5)
#define CMO_IP6EUI             CFG_CMO_DEF(MID_IP6_ADDR, TBL_IP6_ADDR, 6)
#define CMO_IP6ADDRNO          CFG_CMO_DEF(MID_IP6_ADDR, TBL_IP6_ADDR, 7)

#define CMO_IP6_ADDR_MTU_VALUE    CFG_CMO_DEF(MID_IP6_ADDR, TBL_IP6_MTU, 1)
#define CMO_IP6_ADDR_MTU_NO       CFG_CMO_DEF(MID_IP6_ADDR, TBL_IP6_MTU, 2)
#define CMO_IP6_ADDR_MTU_IFINDX   CFG_CMO_DEF(MID_IP6_ADDR, TBL_IP6_MTU, 3)

#define CMO_IP6AUTOCFGIFINDEX     CFG_CMO_DEF(MID_IP6_ADDR, TBL_IP6_AUTOCFG, 1)
#define CMO_IP6UNDOAUTOCFG        CFG_CMO_DEF(MID_IP6_ADDR, TBL_IP6_AUTOCFG, 2)

#define TBL_IP6_DEBUG_CMD  0x15
#define CMO_IP6_ADDR_DEBUG_ONOFF    \
    CFG_CMO_DEF(MID_IP6_ADDR, TBL_IP6_DEBUG_CMD, 1)
#define CMO_IP6_ADDR_DEBUG_LEVEL    \
    CFG_CMO_DEF(MID_IP6_ADDR, TBL_IP6_DEBUG_CMD, 2)

#define TBL_IP6_ADDR_LOG_CMD    0x16
#define CMO_IP6_ADDR_SHOW_LOG       \
    CFG_CMO_DEF(MID_IP6_ADDR, TBL_IP6_ADDR_LOG_CMD, 1)

/*Added for MIB*/
#define IPV6MIBOBJECTS_TBL   0x1
#define CFGMIB_IPV6FORWARDING  \
    CFG_CMO_DEF(MID_IP6_ADDR, IPV6MIBOBJECTS_TBL, 1)
#define CFGMIB_IPV6DEFAULTHOPLIMIT  \
    CFG_CMO_DEF(MID_IP6_ADDR, IPV6MIBOBJECTS_TBL, 2)
#define CFGMIB_IPV6INTERFACES  \
    CFG_CMO_DEF(MID_IP6_ADDR, IPV6MIBOBJECTS_TBL, 3)
#define CFGMIB_IPV6IFTABLELASTCHANGE   \
    CFG_CMO_DEF(MID_IP6_ADDR, IPV6MIBOBJECTS_TBL, 4)

#define IPV6IFTABLE_TBL            0x2
#define CFGMIB_IPV6IFINDEX         CFG_CMO_DEF(MID_IP6_ADDR, IPV6IFTABLE_TBL, 1)
#define CFGMIB_IPV6IFDESCR         CFG_CMO_DEF(MID_IP6_ADDR, IPV6IFTABLE_TBL, 2)
#define CFGMIB_IPV6IFLOWERLAYER    CFG_CMO_DEF(MID_IP6_ADDR, IPV6IFTABLE_TBL, 3)
#define CFGMIB_IPV6IFEFFECTIVEMTU  CFG_CMO_DEF(MID_IP6_ADDR, IPV6IFTABLE_TBL, 4)
#define CFGMIB_IPV6IFREASMMAXSIZE  CFG_CMO_DEF(MID_IP6_ADDR, IPV6IFTABLE_TBL, 5)
#define CFGMIB_IPV6IFIDENTIFIER    CFG_CMO_DEF(MID_IP6_ADDR, IPV6IFTABLE_TBL, 6)
#define CFGMIB_IPV6IFIDENTIFIERLENGTH  \
                                   CFG_CMO_DEF(MID_IP6_ADDR, IPV6IFTABLE_TBL, 7)
#define CFGMIB_IPV6IFPHYSICALADDRESS  \
                                  CFG_CMO_DEF(MID_IP6_ADDR, IPV6IFTABLE_TBL, 8)
#define CFGMIB_IPV6IFADMINSTATUS  CFG_CMO_DEF(MID_IP6_ADDR, IPV6IFTABLE_TBL, 9)
#define CFGMIB_IPV6IFOPERSTATUS   CFG_CMO_DEF(MID_IP6_ADDR, IPV6IFTABLE_TBL, 10)
#define CFGMIB_IPV6IFLASTCHANGE   CFG_CMO_DEF(MID_IP6_ADDR, IPV6IFTABLE_TBL, 11)

#define IPV6ADDRTABLE_TBL        0x4
#define CFGMIB_IPV6ADDRADDRESS   CFG_CMO_DEF(MID_IP6_ADDR, IPV6ADDRTABLE_TBL, 1)
#define CFGMIB_IPV6ADDRPFXLENGTH CFG_CMO_DEF(MID_IP6_ADDR, IPV6ADDRTABLE_TBL, 2)
#define CFGMIB_IPV6ADDRTYPE      CFG_CMO_DEF(MID_IP6_ADDR, IPV6ADDRTABLE_TBL, 3)
#define CFGMIB_IPV6ADDRANYCASTFLAG   \
                                 CFG_CMO_DEF(MID_IP6_ADDR, IPV6ADDRTABLE_TBL, 4)
#define CFGMIB_IPV6ADDRSTATUS    CFG_CMO_DEF(MID_IP6_ADDR, IPV6ADDRTABLE_TBL, 5)

#define IP6_ADDR_LOGID_DEF(LogId)   \
                  IC_INFOID_DEF(MID_IP6_ADDR, IC_INFO_LOG, LogId)
#define IP6_ADDR_DBGID_DEF(DbgId)    \
                  IC_INFOID_DEF(MID_IP6_ADDR, IC_INFO_DEBUG, DbgId)

#define TBL_ADDR_SHOW_COM_VERSION  0x19

#define CMO_ADDR_SHOW_COM_VERSION      \
                  CFG_CMO_DEF( MID_IP6_ADDR, TBL_ADDR_SHOW_COM_VERSION, 1)
#define CMO_ADDR_SHOW_COM_TEST_VERSION \
                  CFG_CMO_DEF( MID_IP6_ADDR, TBL_ADDR_SHOW_COM_VERSION, 2)


#define TBL_ADDR_SHOW_ADDR_ON_ROUTER  0x20

#define CMO_ADDR_SHOW_ADDR      \
                  CFG_CMO_DEF( MID_IP6_ADDR, TBL_ADDR_SHOW_ADDR_ON_ROUTER, 1)


/* Status code for CLI Install - Multiple Template, Same Command */
#define IP6_ADDR_REGCLI_STAT_ALL_SUCCESS                0
#define IP6_ADDR_REGCLI_STAT_FIRST_INSTALL_FAILED       1
#define IP6_ADDR_REGCLI_STAT_ATLEAST_ONE_FAILED         2

#ifdef __cplusplus
}
#endif/* end of __cplusplus */

#endif/* end of _ADDR_SH_CMO_H_ */

