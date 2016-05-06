/******************************************************************************
*
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*
*------------------------------------------------------------------------------
*    Project Code   : VRP5.0
*    Module Name    : IP6 ND
*    Version        : Initial Draft
*    File Name      : ND_SH_CMO.H
*    Create Date    : 2003/06/25
*    Author         : Santosh G Kulkarni
*    Description    : the CMO interface module of ND
*------------------------------------------------------------------------------
*  Modification History
*
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2003-06-25  Santosh G Kulkarni     Create
*******************************************************************************/
#ifndef _ND_CMO_H_
#define    _ND_CMO_H_

#ifdef _cplusplus
extern "C"{
#endif

#define  ND_SHOWNB_BUFFER_LENGTH   2048

#define TBL_ND_NDMSGMFLAG 0x11
#define TBL_ND_NDMSGOFLAG  0x12
#define TBL_ND_NDMSGREACHABLETIME  0x13
#define  TBL_ND_NDMSGRAPROC  0x14
#define TBL_ND_NDMSGHOPLIMIT 0x15
#define TBL_ND_NDMSGNSINTERVAL  0x16
#define TBL_ND_NDMSGDADATTEMPT 0x17
#define TBL_ND_DISPLAY 0x18
#define TBL_ND_DEBUG 0x09
#define TBL_ND_NDADDSTATICNB 0x0A
#define TBL_ND_NDRESETNB 0x0B
#define TBL_ND_NDVLINK6  0x0C
#define TBL_ND_NDCACHECLEAN     0x0D
#define TBL_ND_NDSETGLOBALFLAG  0x0E

#define TBL_ND_SHOW_COM_VERSION  0x19
#define TBL_ND_SHOW_LOG          0x1A

/*
   IAS changes Start : [* THIS SHOULD BE REMOVED AFTER TESTING *]
        Register CLI for configuring VLAN ID and Port index of receving
        buffer.
*/
#define TBL_ND_IAS_SET_VLANID_PORTINDEX  0x1B
#define TBL_ND_IAS_SET_ERROR             0x1C

/* IAS changes End */

/* ipv6 nd ManageFlag */
#define CMO_IP6_ND_MFLAGIFINDEX    CFG_CMO_DEF(MID_ND, TBL_ND_NDMSGMFLAG, 0)
#define CMO_IP6_ND_NDMANAGEFLAG_NO  CFG_CMO_DEF(MID_ND, TBL_ND_NDMSGMFLAG, 1)

/* ipv6 nd OtherFlag */
#define CMO_IP6_ND_OFLAGIFINDEX     CFG_CMO_DEF(MID_ND, TBL_ND_NDMSGOFLAG, 0)
#define CMO_IP6_ND_NDOTHERFLAG_NO   CFG_CMO_DEF(MID_ND, TBL_ND_NDMSGOFLAG, 1)

/* ipv6 nd Reachabletime */
#define CMO_IP6_ND_NDREACHABLETIME     \
                   CFG_CMO_DEF(MID_ND, TBL_ND_NDMSGREACHABLETIME, 0)
#define CMO_IP6_ND_NDREACHABLETIMEVALUE \
                   CFG_CMO_DEF(MID_ND, TBL_ND_NDMSGREACHABLETIME, 1)
#define CMO_IP6_ND_NDREACHABLETIMEIFINDEX \
                   CFG_CMO_DEF(MID_ND, TBL_ND_NDMSGREACHABLETIME, 2)
#define CMO_IP6_ND_NDREACHABLETIME_NO \
                   CFG_CMO_DEF(MID_ND, TBL_ND_NDMSGREACHABLETIME, 3)

/* ipv6 nd rainterval */
#define CMO_IP6_ND_NDRAINTERVAL       CFG_CMO_DEF(MID_ND, TBL_ND_NDMSGRAPROC, 0)
#define CMO_IP6_ND_NDRAINTERVALVALUE  CFG_CMO_DEF(MID_ND, TBL_ND_NDMSGRAPROC, 1)
#define CMO_IP6_ND_NDRAINTERVALIFINDEX \
                                      CFG_CMO_DEF(MID_ND, TBL_ND_NDMSGRAPROC, 2)
#define CMO_IP6_ND_NDRAINTERVAL_NO    CFG_CMO_DEF(MID_ND, TBL_ND_NDMSGRAPROC, 3)

/* ipv6 nd Defaulttime */
#define CMO_IP6_ND_NDDEFAULTTIME      CFG_CMO_DEF(MID_ND, TBL_ND_NDMSGRAPROC, 4)
#define CMO_IP6_ND_NDDEFAULTTIMEVALUE CFG_CMO_DEF(MID_ND, TBL_ND_NDMSGRAPROC, 5)
#define CMO_IP6_ND_NDDEFAULTTIMEIFINDEX \
                                      CFG_CMO_DEF(MID_ND, TBL_ND_NDMSGRAPROC, 6)
#define CMO_IP6_ND_NDDEFAULTTIME_NO   CFG_CMO_DEF(MID_ND, TBL_ND_NDMSGRAPROC, 7)

/* ipv6 nd HopLimit */
#define CMO_IP6_ND_NDHOPLIMIT       CFG_CMO_DEF(MID_ND, TBL_ND_NDMSGHOPLIMIT, 0)
#define CMO_IP6_ND_NDHOPLIMITVALUE  CFG_CMO_DEF(MID_ND, TBL_ND_NDMSGHOPLIMIT, 1)

#define CMO_IP6_ND_NDHOPLIMIT_NO    CFG_CMO_DEF(MID_ND, TBL_ND_NDMSGHOPLIMIT, 2)

#define CMO_IP6_ND_NDVLINK       CFG_CMO_DEF(MID_ND, TBL_ND_NDVLINK6, 0)
#define CMO_IP6_ND_NDVLINK_NO CFG_CMO_DEF(MID_ND, TBL_ND_NDVLINK6, 1)

#define CMO_IP6_ND_CACHECLEAN     CFG_CMO_DEF(MID_ND, TBL_ND_NDCACHECLEAN, 0)

#define CMO_IP6_ND_SETGLOBAL      CFG_CMO_DEF(MID_ND, TBL_ND_NDSETGLOBALFLAG, 0)

/* ipv6 nd Suppress_RA */
#define CMO_IP6_ND_ND_RA_NO       CFG_CMO_DEF(MID_ND, TBL_ND_NDMSGRAPROC, 8)
#define CMO_IP6_ND_RA_IFINDEX     CFG_CMO_DEF(MID_ND, TBL_ND_NDMSGRAPROC, 9)

/* ipv6 nd dadattempt */
#define CMO_IP6_ND_NDDAD          CFG_CMO_DEF(MID_ND, TBL_ND_NDMSGDADATTEMPT, 0)
#define CMO_IP6_ND_NDDADATTEMPT   CFG_CMO_DEF(MID_ND, TBL_ND_NDMSGDADATTEMPT, 1)
#define CMO_ND_ND_DADATTEMPTVALUE CFG_CMO_DEF(MID_ND, TBL_ND_NDMSGDADATTEMPT, 2)
#define CMO_IP6_ND_NDDADATTEMPTINDEX \
                                  CFG_CMO_DEF(MID_ND, TBL_ND_NDMSGDADATTEMPT, 3)
#define CMO_IP6_ND_NDDADATTEMPT_NO \
                                  CFG_CMO_DEF(MID_ND, TBL_ND_NDMSGDADATTEMPT, 4)

/* ipv6 nd nsinterval */
#define CMO_IP6_ND_NDNSINTERVAL   CFG_CMO_DEF(MID_ND, TBL_ND_NDMSGNSINTERVAL, 0)
#define CMO_IP6_ND_NDNSINTERVALVALUE \
                                  CFG_CMO_DEF(MID_ND, TBL_ND_NDMSGNSINTERVAL, 1)
#define CMO_IP6_ND_NDNSINTERVALIFINDEX \
                                  CFG_CMO_DEF(MID_ND, TBL_ND_NDMSGNSINTERVAL, 2)
#define CMO_IP6_ND_NDNSINTERVAL_NO \
                                  CFG_CMO_DEF(MID_ND, TBL_ND_NDMSGNSINTERVAL, 3)

/* ipv6 nd prefix-advertisement */
#define CMO_IP6_ND_NDPREFIXADV   CFG_CMO_DEF(MID_ND, TBL_ND_NDMSGRAPROC, 10)
#define CMO_IP6_ND_NDPREFIX      CFG_CMO_DEF(MID_ND, TBL_ND_NDMSGRAPROC, 11)
#define CMO_IP6_ND_PREFIXLENGTH  CFG_CMO_DEF(MID_ND, TBL_ND_NDMSGRAPROC, 12)
#define CMO_IP6_ND_NDVALIDTIME   CFG_CMO_DEF(MID_ND, TBL_ND_NDMSGRAPROC, 13)
#define CMO_IP6_ND_NDPREFEREDTIME CFG_CMO_DEF(MID_ND, TBL_ND_NDMSGRAPROC, 14)
#define CMO_IP6_ND_NDONLINKFLAG  CFG_CMO_DEF(MID_ND, TBL_ND_NDMSGRAPROC, 15)
#define CMO_IP6_ND_NDAUTOCONFFLAG    CFG_CMO_DEF(MID_ND, TBL_ND_NDMSGRAPROC, 16)
#define CMO_IP6_ND_NDPREFIXIFINDEX   CFG_CMO_DEF(MID_ND, TBL_ND_NDMSGRAPROC, 17)
#define CMO_IP6_ND_NO                CFG_CMO_DEF(MID_ND, TBL_ND_NDMSGRAPROC, 18)

#define CMO_IP6_ND_ND_RA_HALT CFG_CMO_DEF(MID_ND, TBL_ND_NDMSGRAPROC, 19)

/* Begin : Defect ID: BYAD12218,     Modifier:Rajesh,   Date:2004/9/13
        Reason   : To config Minimum RA interval.*/
#define CMO_IP6_ND_NDRA_MININTERVAL  CFG_CMO_DEF(MID_ND, TBL_ND_NDMSGRAPROC, 20)
#define CMO_IP6_ND_NDRA_MININTERVALVALUE \
                                     CFG_CMO_DEF(MID_ND, TBL_ND_NDMSGRAPROC, 21)

/* Display IPV6 neighbour */
#define CMO_IP6_ND_DISPLAYNEIGHBOR     CFG_CMO_DEF(MID_ND, TBL_ND_DISPLAY, 0)
#define CMO_IP6_ND_DISPLAYINTERFACETYPE   CFG_CMO_DEF(MID_ND, TBL_ND_DISPLAY, 1)
#define CMO_IP6_ND_DISPLAYINTERFACENUM    CFG_CMO_DEF(MID_ND, TBL_ND_DISPLAY, 2)
#define CMO_IP6_ND_DISPLAYINTERFACENAME   CFG_CMO_DEF(MID_ND, TBL_ND_DISPLAY,3)

/* debug ipv6 ND */
#define CMO_IP6_ND_DEBUG             CFG_CMO_DEF(MID_ND, TBL_ND_DEBUG, 0)
#define CMO_IP6_ND_DEBUG_NO          CFG_CMO_DEF(MID_ND, TBL_ND_DEBUG, 1)

#define CMO_IP6_ND_STATIC_ADDRESS   CFG_CMO_DEF(MID_ND, TBL_ND_NDADDSTATICNB, 0)
#define CMO_IP6_ND_HARDWARE_ADDRESS CFG_CMO_DEF(MID_ND, TBL_ND_NDADDSTATICNB, 1)
#define CMO_IP6_ND_STATICINDEX CFG_CMO_DEF(MID_ND, TBL_ND_NDADDSTATICNB, 2)
#define CMO_IP6_ND_STATIC_NB_NO    CFG_CMO_DEF(MID_ND, TBL_ND_NDADDSTATICNB, 3)

/*
    IAS changes Start :
    VLAN ID and Port name need to be passed for static neighbor entry
    addition if product is IAS.
*/
#define CMO_IP6_ND_VLAN_ID          CFG_CMO_DEF(MID_ND, TBL_ND_NDADDSTATICNB,4)
#define CMO_IP6_ND_PORT_NAME        CFG_CMO_DEF(MID_ND, TBL_ND_NDADDSTATICNB,5)

/* IAS changes End */

#define CMO_IP6_ND_RESET_ALL            CFG_CMO_DEF(MID_ND, TBL_ND_NDRESETNB, 1)
#define CMO_IP6_ND_RESET_STATIC         CFG_CMO_DEF(MID_ND, TBL_ND_NDRESETNB, 2)
#define CMO_IP6_ND_RESET_DYNAMIC        CFG_CMO_DEF(MID_ND, TBL_ND_NDRESETNB, 3)

#define CMO_IP6_ND_RESETINTERFACETYPE   CFG_CMO_DEF(MID_ND, TBL_ND_NDRESETNB, 4)
#define CMO_IP6_ND_RESETINTERFACENUM    CFG_CMO_DEF(MID_ND, TBL_ND_NDRESETNB, 5)
#define CMO_IP6_ND_RESETINTERFACENAME   CFG_CMO_DEF(MID_ND, TBL_ND_NDRESETNB,6)

/*
   IAS changes Start : [* THIS SHOULD BE REMOVED AFTER TESTING *]
        Register CLI for configuring VLAN ID and Port index of receving
        buffer.
*/
#define CMO_IP6_ND_IAS_VLANID           \
                CFG_CMO_DEF(MID_ND, TBL_ND_IAS_SET_VLANID_PORTINDEX, 0)
#define CMO_IP6_ND_IAS_PORTINDEX        \
                CFG_CMO_DEF(MID_ND, TBL_ND_IAS_SET_VLANID_PORTINDEX, 1)
#define CMO_IP6_ND_IAS_SET_ERROR_START  \
                CFG_CMO_DEF(MID_ND, TBL_ND_IAS_SET_ERROR, 0)

/* IAS changes End */

/* ND CMO message types for different ND Commands */
enum enum_ND
{
    ND_all = 0,
    ND_KeyWord_IP,
    ND_KeyWord_ND,
    ND_KeyWord_DEBUGND,
    ND_managed_config_flag,
    ND_other_config_flag,
    ND_RA_Keyword,
    ND_Auto_Config_KeyWord,
    ND_KeyWord_NUD,
    ND_HardAddr,
    ND_static,
    ND_dynamic,
    ND_Neighbor,
    ND_ReachableTime,
    ND_ReachableValue,
    ND_RAInterval,
    ND_RAIntervalValue,

    /* Begin : Defect ID: BYAD12218,     Modifier:Rajesh,   Date:2004/9/13
       Reason   : To config Minimum RA interval.*/
    ND_RA_MinInterval,
    ND_RA_MinIntervalValue,
    ND_router_default_time,
    ND_DefaultValue,
    ND_HopLimt,
    ND_HopLimitValue,
    ND_Prefix_advertisement,

    ND_Prefix_advertisement_Prefix_1_T0_128,
    ND_Prefix_advertisement_Prefix_1_T0_64,
    ND_Prefix_advertisement_Prefixlen,

    ND_Prefix_advertisement_Validtime,
    ND_Prefix_advertisement_Prefreedtime,
    ND_Prefix_advertisement_Onlinkflag,
    ND_Prefix_advertisement_AutoConfFlag,
    ND_ns_interval,
    ND_NSIntervalValue,
    ND_dad,
    ND_dadattempts,
    ND_DADAttemptValue,
    ND_Display_Neighbor,
    ND_Ip6Address,

    /* Add by SurajR (72063) on 26-Feb-2007 */
    ND_Ip6Prefix,

    ND_NSWord,
    ND_RA_Halt,
    ND_Display_InterfaceType,
    ND_Display_InterfaceNum,
    ND_Display_InterfaceName,
    ND_MTU_MTU,
    ND_MTU_MTUVALUE,
    ND_VLINK,
    ND_VLINK_ENABLE,
    ND_Keyword_Cache,
    ND_CacheDel_Size,
    ND_Keyword_SetGlobal,
    ND_SetGlobal_Value,
    ND_CMDELEMENT_SHOWCOM,
    ND_CMDELEMENT_SHOWCOMVER,
    ND_CMDELEMENT_SHOWCOMVERND,
    ND_CMDELEMENT_SHOWCOMTESTVER,
    ND_CMDELEMENT_SHOWCOMTESTVERND,

    /*
        IAS changes Start :
        VLAN ID and Port name need to be passed for static neighbor entry
        addition if product is IAS.
    */

    /* Added by SurajR (72063) as per OMSE comment */
    ND_VId,

    ND_VlanId,
    ND_PortName,

    /* IAS changes End */

    IP6_ENUM_VALUE_PAD = IP6_ND_MAX_ENUM_VALUE
};

#define IPV6IFTABLE_TBL       0x2

#define CFGMIB_IPV6IFINDEX     CFG_CMO_DEF(MID_IP6_ADDR, IPV6IFTABLE_TBL, 1)
#define CFGMIB_IPV6IFDESCR     CFG_CMO_DEF(MID_IP6_ADDR, IPV6IFTABLE_TBL, 2)
#define CFGMIB_IPV6IFLOWERLAYER   CFG_CMO_DEF(MID_IP6_ADDR, IPV6IFTABLE_TBL, 3)
#define CFGMIB_IPV6IFEFFECTIVEMTU CFG_CMO_DEF(MID_IP6_ADDR, IPV6IFTABLE_TBL, 4)
#define CFGMIB_IPV6IFREASMMAXSIZE CFG_CMO_DEF(MID_IP6_ADDR, IPV6IFTABLE_TBL, 5)
#define CFGMIB_IPV6IFIDENTIFIER   CFG_CMO_DEF(MID_IP6_ADDR, IPV6IFTABLE_TBL, 6)
#define CFGMIB_IPV6IFIDENTIFIERLENGTH \
     CFG_CMO_DEF(MID_IP6_ADDR, IPV6IFTABLE_TBL, 7)
#define CFGMIB_IPV6IFPHYSICALADDRESS \
     CFG_CMO_DEF(MID_IP6_ADDR, IPV6IFTABLE_TBL, 8)
#define CFGMIB_IPV6IFADMINSTATUS  CFG_CMO_DEF(MID_IP6_ADDR, IPV6IFTABLE_TBL, 9)
#define CFGMIB_IPV6IFOPERSTATUS   CFG_CMO_DEF(MID_IP6_ADDR, IPV6IFTABLE_TBL, 10)
#define CFGMIB_IPV6IFLASTCHANGE   CFG_CMO_DEF(MID_IP6_ADDR, IPV6IFTABLE_TBL, 11)

#define IPV6ADDRPREFIXTABLE_TBL 0x3
#define CFGMIB_IPV6ADDRPREFIX   \
    CFG_CMO_DEF(MID_ND, IPV6ADDRPREFIXTABLE_TBL, 1)
#define CFGMIB_IPV6ADDRPREFIXLENGTH \
    CFG_CMO_DEF(MID_ND, IPV6ADDRPREFIXTABLE_TBL, 2)
#define CFGMIB_IPV6ADDRPREFIXONLINKFLAG \
    CFG_CMO_DEF(MID_ND, IPV6ADDRPREFIXTABLE_TBL, 3)
#define CFGMIB_IPV6ADDRPREFIXAUTONOMOUSFLAG \
    CFG_CMO_DEF(MID_ND, IPV6ADDRPREFIXTABLE_TBL, 4)
#define CFGMIB_IPV6ADDRPREFIXADVPREFERREDLIFETIME  \
    CFG_CMO_DEF(MID_ND, IPV6ADDRPREFIXTABLE_TBL, 5)
#define CFGMIB_IPV6ADDRPREFIXADVVALIDLIFETIME  \
    CFG_CMO_DEF(MID_ND, IPV6ADDRPREFIXTABLE_TBL, 6)

#define IPV6NETTOMEDIATABLE_TBL 0x6
#define CFGMIB_IPV6NETTOMEDIANETADDRESS  \
    CFG_CMO_DEF(MID_ND, IPV6NETTOMEDIATABLE_TBL, 1)
#define CFGMIB_IPV6NETTOMEDIAPHYSADDRESS \
    CFG_CMO_DEF(MID_ND, IPV6NETTOMEDIATABLE_TBL, 2)
#define CFGMIB_IPV6NETTOMEDIATYPE  \
    CFG_CMO_DEF(MID_ND, IPV6NETTOMEDIATABLE_TBL, 3)
#define CFGMIB_IPV6IFNETTOMEDIASTATE  \
    CFG_CMO_DEF(MID_ND, IPV6NETTOMEDIATABLE_TBL, 4)
#define CFGMIB_IPV6IFNETTOMEDIALASTUPDATED \
    CFG_CMO_DEF(MID_ND, IPV6NETTOMEDIATABLE_TBL, 5)
#define CFGMIB_IPV6NETTOMEDIAVALID \
    CFG_CMO_DEF(MID_ND, IPV6NETTOMEDIATABLE_TBL, 6)

#define IPV6ADDRTABLE_TBL     0x4
#define CFGMIB_IPV6ADDRADDRESS  \
    CFG_CMO_DEF(MID_IP6_ADDR, IPV6ADDRTABLE_TBL, 1)
#define CFGMIB_IPV6ADDRPFXLENGTH \
    CFG_CMO_DEF(MID_IP6_ADDR, IPV6ADDRTABLE_TBL, 2)
#define CFGMIB_IPV6ADDRTYPE  \
    CFG_CMO_DEF(MID_IP6_ADDR, IPV6ADDRTABLE_TBL, 3)
#define CFGMIB_IPV6ADDRANYCASTFLAG  \
    CFG_CMO_DEF(MID_IP6_ADDR, IPV6ADDRTABLE_TBL, 4)
#define CFGMIB_IPV6ADDRSTATUS   \
    CFG_CMO_DEF(MID_IP6_ADDR, IPV6ADDRTABLE_TBL, 5)



#define CMO_ND_SHOW_COM_VERSION      \
                  CFG_CMO_DEF(MID_ND, TBL_ND_SHOW_COM_VERSION, 1)
#define CMO_ND_SHOW_COM_TEST_VERSION \
                  CFG_CMO_DEF(MID_ND, TBL_ND_SHOW_COM_VERSION, 2)

#define CMO_IP6_ND_SHOW_LOG     CFG_CMO_DEF(MID_ND, TBL_ND_SHOW_LOG,1)

#ifdef _cplusplus
}
#endif/* end of __cplusplus */

#endif    /* end of _ND_CMO_H_ */
