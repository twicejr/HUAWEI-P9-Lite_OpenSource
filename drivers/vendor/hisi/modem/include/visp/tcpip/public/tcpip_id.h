/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                             tcpip_id.h
 *
 *  Project Code: VISP1.5
 *   Module Name: Public
 *  Date Created: 2004-06-28
 *        Author: VISP Team
 *   Description: Defines Moudule ID, Sub-module ID, Waitlist ID,
 *                CID & IID, etc. in VISP stack
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2004-06-28      VISP Team       Create
 *  2004-11-15      VISP Team       Redefine all Macro
 *  2006-03-30      VISP Team       Adjust for D00645
 *  2008-01-17      VISP Team       删除头文件中定义的一些SID
 *  2008-08-13      f54882          Modify for BC3D00237
 *
 ************************************************************************/

#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _TCPIP_ID_H
#define _TCPIP_ID_H


/********************************************************/
/*                  define the CID base                 */
/********************************************************/
#ifndef CID_GLOBAL_BASE
#define CID_GLOBAL_BASE     0       /* VRPV5 defined it*/
#endif
#ifndef CID_INTERNAL
#define CID_INTERNAL        100     /* VRPV5 defined it*/
#endif

#define CID_IPV4_BASE       ( (CID_GLOBAL_BASE) + 10*(CID_INTERNAL) ) /* 等待VRPV5R1统一分配 */
#define CID_IPV4V6_BASE     ( (CID_GLOBAL_BASE) + 11*(CID_INTERNAL) ) /* 等待VRPV5R1统一分配 */
#define CID_SEC_BASE        ( (CID_GLOBAL_BASE) + 12*(CID_INTERNAL) ) /* 分配给IR IPSEC/IKE的CID空间 */    
#define CID_VISP_IPV6_BASE  ( (CID_GLOBAL_BASE) + 13*(CID_INTERNAL) ) /* 分配给VISP的IPv6的CID空间 */    

#ifndef CID_IPV6_BASE
#define CID_IPV6_BASE       ((CID_GLOBAL_BASE) + 2*(CID_INTERNAL))    /* 分配给IR IPv6的CID空间 */
#endif

/********************************************************/
/*                  define IID base                     */
/********************************************************/
#ifndef IID_GLOBAL_BASE
#define IID_GLOBAL_BASE     0       /* VRPV5 defined it*/
#endif
#ifndef IID_INTERNAL
#define IID_INTERNAL        1000    /* VRPV5 defined it*/
#endif

#define IID_IPV4_BASE       ( (IID_GLOBAL_BASE) + 10*(IID_INTERNAL) )   /* 等待VRPV5R1统一分配 */
#define IID_IPV4V6_BASE     ( (IID_GLOBAL_BASE) + 11*(IID_INTERNAL) )   /* 等待VRPV5R1统一分配 */
#define IID_SEC_BASE        ( (IID_GLOBAL_BASE) + 12*(IID_INTERNAL) )   /* 分配给IR IPSEC/IKE的IID空间*/    
#define IID_VISP_IPV6_BASE  ( (IID_GLOBAL_BASE) + 13*(IID_INTERNAL) )   /* 分配给VISP的IPv6的IID空间 */

#ifndef IID_IPV6_BASE
#define IID_IPV6_BASE       ((IID_GLOBAL_BASE) + 2*(IID_INTERNAL))      /* 分配给IR IPv6的IID空间 */
#endif

/********************************************************/
/*                  define CID and IID                  */
/********************************************************/

/* IPv4 DHCP Client component, only using out of VRP */
#define CID_IPV4_DHCPC4             ( CID_IPV4_BASE + 1 ) 

#define IID_IPV4_DHCPC4_INTF_FUN    ( IID_IPV4_BASE + 10 )
#define IID_IPV4_DHCPC4_INTF_CFG    ( IID_IPV4_BASE + 11 )
#define IID_IPV4_DHCPC4_INTF_SSA    ( IID_IPV4_BASE + 12 )


/* IPv4 Socket component */
#define CID_IPV4_SOCKET4            ( CID_IPV4_BASE + 2 )

#define IID_IPV4_SOCKET4_INTF_FUN   ( IID_IPV4_BASE + 20 )
#define IID_IPV4_SOCKET4_INTF_CFG   ( IID_IPV4_BASE + 21 )
#define IID_IPV4_SOCKET4_INTF_SSA   ( IID_IPV4_BASE + 22 )


/* IPv4 TCP component */
#define CID_IPV4_TCP4               ( CID_IPV4_BASE + 3 )

#define IID_IPV4_TCP4_INTF_FUN      ( IID_IPV4_BASE + 30 )
#define IID_IPV4_TCP4_INTF_CFG      ( IID_IPV4_BASE + 31 )
#define IID_IPV4_TCP4_INTF_SSA      ( IID_IPV4_BASE + 32 )

/* IPv4 UDP component */
#define CID_IPV4_UDP4               ( CID_IPV4_BASE + 4 )

#define IID_IPV4_UDP4_INTF_FUN      ( IID_IPV4_BASE + 40 )
#define IID_IPV4_UDP4_INTF_CFG      ( IID_IPV4_BASE + 41 )
#define IID_IPV4_UDP4_INTF_SSA      ( IID_IPV4_BASE + 42 )


/* IPv4 RawIP component */
#define CID_IPV4_RAWIP4             ( CID_IPV4_BASE + 5 )

#define IID_IPV4_RAWIP4_INTF_FUN    ( IID_IPV4_BASE + 50 )
#define IID_IPV4_RAWIP4_INTF_CFG    ( IID_IPV4_BASE + 51 )
#define IID_IPV4_RAWIP4_INTF_SSA    ( IID_IPV4_BASE + 52 )


/* IPv4 ICMP component */
#define CID_IPV4_ICMP4              ( CID_IPV4_BASE + 6 )

#define IID_IPV4_ICMP4_INTF_FUN     ( IID_IPV4_BASE + 60 )
#define IID_IPV4_ICMP4_INTF_CFG     ( IID_IPV4_BASE + 61 )
#define IID_IPV4_ICMP4_INTF_SSA     ( IID_IPV4_BASE + 62 )


/* IPv4 Protocol Process component */
#define CID_IPV4_PP4                ( CID_IPV4_BASE + 7 )

#define IID_IPV4_PP4_INTF_FUN       ( IID_IPV4_BASE + 70 )
#define IID_IPV4_PP4_INTF_CFG       ( IID_IPV4_BASE + 71 )
#define IID_IPV4_PP4_INTF_SSA       ( IID_IPV4_BASE + 72 )


/* IPv4 Address Manager component */
#define CID_IPV4_AM4                ( CID_IPV4_BASE + 8 )

#define IID_IPV4_AM4_INTF_FUN       ( IID_IPV4_BASE + 80 )
#define IID_IPV4_AM4_INTF_CFG       ( IID_IPV4_BASE + 81 )
#define IID_IPV4_AM4_INTF_SSA       ( IID_IPV4_BASE + 82 )


/* IPv4 Simple FIB Container component, only using out of VRP*/
#define CID_IPV4_SFIBC4             ( CID_IPV4_BASE + 9 )

#define IID_IPV4_SFIBC4_INTF_FUN    ( IID_IPV4_BASE + 90 )
#define IID_IPV4_SFIBC4_INTF_FIBA   ( IID_IPV4_BASE + 91 )
#define IID_IPV4_SFIBC4_INTF_SSA    ( IID_IPV4_BASE + 92 )
#define IID_IPV4_SFIBC4_INTF_CFG    ( IID_IPV4_BASE + 93 )


#define CID_IPV4_DISTIP                ( CID_IPV4_BASE + 0xA )
#define IID_DIP_INTF_FUN            ( IID_IPV4_BASE + 100 )
#define IID_DIP_INTF_CFG            ( IID_IPV4_BASE + 101 )
#define IID_DIP_INTF_SSA            ( IID_IPV4_BASE + 102 )

/* IPv4 and IPv6 Ping component */
#define CID_COMP_PING               ( CID_IPV4V6_BASE + 1 )

#define IID_COMP_PING_INTF_FUN      ( IID_IPV4V6_BASE + 10 )
#define IID_COMP_PING_INTF_CFG      ( IID_IPV4V6_BASE + 11 )
#define IID_COMP_PING_INTF_SSA      ( IID_IPV4V6_BASE + 12 )


/* IPv4 and IPv6 TraceRoute component */
#define CID_COMP_TRRT               ( CID_IPV4V6_BASE + 2 )

#define IID_COMP_TRRT_INTF_FUN      ( IID_IPV4V6_BASE + 20 )
#define IID_COMP_TRRT_INTF_CFG      ( IID_IPV4V6_BASE + 21 )
#define IID_COMP_TRRT_INTF_SSA      ( IID_IPV4V6_BASE + 22 )


/* IPv4 and IPv6 DNS Client component */
#define CID_COMP_DNSC               ( CID_IPV4V6_BASE + 3 )

#define IID_COMP_DNSC_INTF_FUN      ( IID_IPV4V6_BASE + 30 )
#define IID_COMP_DNSC_INTF_CFG      ( IID_IPV4V6_BASE + 31 )
#define IID_COMP_DNSC_INTF_SSA      ( IID_IPV4V6_BASE + 32 )


/* IPv4 and IPv6 Simple FIBAgent component, only using out of VRP */
#define CID_COMP_SFIBA              ( CID_IPV4V6_BASE + 4 ) 

#define IID_COMP_SFIBA_INTF_FUN     ( IID_IPV4V6_BASE + 40 )
#define IID_COMP_SFIBA_INTF_CFG     ( IID_IPV4V6_BASE + 41 )
#define IID_COMP_SFIBA_INTF_SSA     ( IID_IPV4V6_BASE + 42 )


/* IFNET component, only using out of VRP */
#define CID_COMP_IFNET              ( CID_IPV4V6_BASE + 5 ) 

#define IID_COMP_IFNET_INTF_FUN     ( IID_IPV4V6_BASE + 50 )
#define IID_COMP_IFNET_INTF_CFG     ( IID_IPV4V6_BASE + 51 )
#define IID_COMP_IFNET_INTF_SSA     ( IID_IPV4V6_BASE + 52 )
#define IID_COMP_IFNET_INTF_PUB     ( IID_IPV4V6_BASE + 53 )


/* Etherner&ARP protocol component, only using out of VRP */
#define CID_COMP_ETHARP             ( CID_IPV4V6_BASE + 6 )

#define IID_COMP_ETHARP_INTF_FUN    ( IID_IPV4V6_BASE + 60 )
#define IID_COMP_ETHARP_INTF_CFG    ( IID_IPV4V6_BASE + 61 )
#define IID_COMP_ETHARP_INTF_SSA    ( IID_IPV4V6_BASE + 62 )
#define IID_COMP_ETHARP_INTF_IFG    IID_COMP_IFNET_INTF_PUB


/* PPP protocol component, only using out of VRP */
#define CID_COMP_PPP                ( CID_IPV4V6_BASE + 7 )

#define IID_COMP_PPP_INTF_FUN       ( IID_IPV4V6_BASE + 70 )
#define IID_COMP_PPP_INTF_CFG       ( IID_IPV4V6_BASE + 71 )
#define IID_COMP_PPP_INTF_SSA       ( IID_IPV4V6_BASE + 72 )
#define IID_COMP_PPP_INTF_IFG       IID_COMP_IFNET_INTF_PUB



#define CID_COMP_ATK                ( CID_IPV4V6_BASE + 8 )

#define IID_COMP_ATK_INTF_FUN       ( IID_IPV4V6_BASE + 80 )
#define IID_COMP_ATK_INTF_CFG       ( IID_IPV4V6_BASE + 81 )
#define IID_COMP_ATK_INTF_IFG       IID_COMP_IFNET_INTF_PUB

#define CID_COMP_IPHC               ( CID_IPV4V6_BASE + 9 )

#define IID_COMP_IPHC_INTF_FUN      ( IID_IPV4V6_BASE + 90 )
#define IID_COMP_IPHC_INTF_CFG      ( IID_IPV4V6_BASE + 91 )
#define IID_COMP_IPHC_INTF_SSA      ( IID_IPV4V6_BASE + 92 )


#define CID_COMP_POEC               ( CID_IPV4V6_BASE + 10)

#define IID_COMP_POEC_INTF_FUN      ( IID_IPV4V6_BASE + 100 )   
#define IID_COMP_POEC_INTF_CFG      ( IID_IPV4V6_BASE + 101 )   
#define IID_COMP_POEC_INTF_SSA      ( IID_IPV4V6_BASE + 102 )   


/*Component ID declaration for MP*/
#define CID_COMP_MP                 ( CID_IPV4V6_BASE + 11 )

/*interface IDs declaration*/
#define IID_COMP_MP_INTF_FUN        ( IID_IPV4V6_BASE + 111 )
#define IID_COMP_MP_INTF_CFG        ( IID_IPV4V6_BASE + 112 )
#define IID_COMP_MP_INTF_SSA        ( IID_IPV4V6_BASE + 113 )

/* Component ID declaration for PPPMUX */
#define CID_COMP_PPPMUX             ( CID_IPV4V6_BASE + 12 )

/*interface IDs declaration*/
#define IID_COMP_PPPMUX_INTF_FUN    ( IID_IPV4V6_BASE + 121 )
#define IID_COMP_PPPMUX_INTF_CFG    ( IID_IPV4V6_BASE + 122 )
#define IID_COMP_PPPMUX_INTF_SSA    ( IID_IPV4V6_BASE + 123 )


/* Component ID declaration for TRUNK */
#define CID_COMP_TRUNK              ( CID_IPV4V6_BASE + 13 )

/*interface IDs declaration*/
#define IID_COMP_TRUNK_INTF_FUN     ( IID_IPV4V6_BASE + 131 )
#define IID_COMP_TRUNK_INTF_CFG     ( IID_IPV4V6_BASE + 132 )
#define IID_COMP_TRUNK_INTF_SSA     ( IID_IPV4V6_BASE + 133 )

/* Component ID declaration for POES */
#define CID_COMP_POES             ( CID_IPV4V6_BASE + 14 )

/*interface IDs declaration*/
#define IID_COMP_POES_INTF_FUN   ( IID_IPV4V6_BASE + 141 )
#define IID_COMP_POES_INTF_CFG   ( IID_IPV4V6_BASE + 142 )
#define IID_COMP_POES_INTF_SSA   ( IID_IPV4V6_BASE + 143 )

/* Component ID declaration for DHCP4R */
#define CID_COMP_DHCP4R             ( CID_IPV4V6_BASE + 15 )

/*interface IDs declaration*/
#define IID_COMP_DHCP4R_INTF_FUN    ( IID_IPV4V6_BASE + 151 )
#define IID_COMP_DHCP4R_INTF_CFG    ( IID_IPV4V6_BASE + 152 )
#define IID_COMP_DHCP4R_INTF_SSA    ( IID_IPV4V6_BASE + 153 )

/* Component ID declaration for OSICP */
#define CID_COMP_OSICP             ( CID_IPV4V6_BASE + 16 )

/*interface IDs declaration*/
#define IID_COMP_OSICP_INTF_FUN    ( IID_IPV4V6_BASE + 161 )
#define IID_COMP_OSICP_INTF_CFG    ( IID_IPV4V6_BASE + 162 )
#define IID_COMP_OSICP_INTF_SSA    ( IID_IPV4V6_BASE + 163 )


/* Component ID declaration for OAM3AH */
#define CID_COMP_OAM3AH             ( CID_IPV4V6_BASE + 17 )

/*interface IDs declaration*/
#define IID_COMP_OAM3AH_INTF_FUN    ( IID_IPV4V6_BASE + 171 )
#define IID_COMP_OAM3AH_INTF_CFG    ( IID_IPV4V6_BASE + 172 )
#define IID_COMP_OAM3AH_INTF_SSA    ( IID_IPV4V6_BASE + 173 )

/* Component ID declaration for OAM1AG */
#define CID_COMP_OAM1AG             ( CID_IPV4V6_BASE + 18 )

/*interface IDs declaration*/
#define IID_COMP_OAM1AG_INTF_FUN    ( IID_IPV4V6_BASE + 181 )
#define IID_COMP_OAM1AG_INTF_CFG    ( IID_IPV4V6_BASE + 182 )
#define IID_COMP_OAM1AG_INTF_SSA    ( IID_IPV4V6_BASE + 183 )
/*VISPV1R7,z62531*/
/* Component ID declaration for IGMP */
#define CID_COMP_IGMP            ( CID_IPV4V6_BASE + 21 )

/*interface IDs declaration*/
#define IID_COMP_IGMP_INTF_FUN    ( IID_IPV4V6_BASE + 211 )
#define IID_COMP_IGMP_INTF_CFG    ( IID_IPV4V6_BASE + 212 )
#define IID_COMP_IGMP_INTF_SSA    ( IID_IPV4V6_BASE + 213 )

/* VISPV1R7C03 */
/* Component ID declaration for L2IF */
#define CID_COMP_L2IF             ( CID_IPV4V6_BASE + 22 )

/*interface IDs declaration*/
#define IID_COMP_L2IF_INTF_FUN    ( IID_IPV4V6_BASE + 221 )
#define IID_COMP_L2IF_INTF_CFG    ( IID_IPV4V6_BASE + 222 )
#define IID_COMP_L2IF_INTF_SSA    ( IID_IPV4V6_BASE + 223 )

/* Component ID declaration for VRRP */
#define CID_COMP_VRRP             ( CID_IPV4V6_BASE + 23 )
/*interface IDs declaration*/
#define IID_COMP_VRRP_INTF_FUN    ( IID_IPV4V6_BASE + 231 )
#define IID_COMP_VRRP_INTF_CFG    ( IID_IPV4V6_BASE + 232 )
#define IID_COMP_VRRP_INTF_SSA    ( IID_IPV4V6_BASE + 233 )

/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
/* Component ID declaration for IGMP */
#define CID_COMP_VRF            ( CID_IPV4V6_BASE + 24 )

/*interface IDs declaration*/
#define IID_COMP_VRF_INTF_FUN    ( IID_IPV4V6_BASE + 241 )
#define IID_COMP_VRF_INTF_CFG    ( IID_IPV4V6_BASE + 242 )
#define IID_COMP_VRF_INTF_SSA    ( IID_IPV4V6_BASE + 243 )
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

/* Begin:VISP1.8C03 SYNCE r62469 , 2009-12-21 */
#define CID_COMP_SYNCE            ( CID_IPV4V6_BASE + 25)

/*interface IDs declaration*/
#define IID_COMP_SYNCE_INTF_FUN    ( IID_IPV4V6_BASE + 251 )
#define IID_COMP_SYNCE_INTF_CFG    ( IID_IPV4V6_BASE + 252 )
#define IID_COMP_SYNCE_INTF_SSA    ( IID_IPV4V6_BASE + 253 )
/* End:VISP1.8C03 SYNCE r62469 , 2009-12-21 */

/*添加同NSR相关的组件ID*/
#define CID_COMP_NSR                  ( CID_IPV4V6_BASE + 26 )

/*interface IDs declaration*/
#define IID_COMP_NSR_INTF_FUN    ( IID_IPV4V6_BASE + 261 )
#define IID_COMP_NSR_INTF_CFG    ( IID_IPV4V6_BASE + 262 )
#define IID_COMP_NSR_INTF_SSA    ( IID_IPV4V6_BASE + 263 )


/*====================IPV6相关CID/IID=============================*/

/* Component ID declaration for PPMNG  */
#define CID_IPV6_PPMNG              (CID_VISP_IPV6_BASE)

/* Interface IDs declaration */
#define IID_IPV6_PPMNG_INTF_CFG     (IID_VISP_IPV6_BASE)    
#define IID_IPV6_PPMNG_INTF_SSA     (IID_VISP_IPV6_BASE + 1)  
#define IID_IPV6_PPMNG_INTF_FUN     (IID_VISP_IPV6_BASE + 2)


/* IPv6 Socket component */
#define CID_IPV6_SOCKET6            (CID_VISP_IPV6_BASE + 1)

#define IID_IPV6_SOCKET6_INTF_FUN   (IID_VISP_IPV6_BASE + 10)
#define IID_IPV6_SOCKET6_INTF_CFG   (IID_VISP_IPV6_BASE + 11)
#define IID_IPV6_SOCKET6_INTF_SSA   (IID_VISP_IPV6_BASE + 12)


/* IPv6 Simple FIB Container component, only using out of VRP*/
#define CID_IPV6_SFIBC6             (CID_VISP_IPV6_BASE + 2 ) 

#define IID_IPV6_SFIBC6_INTF_FUN    (IID_VISP_IPV6_BASE + 20)
#define IID_IPV6_SFIBC6_INTF_FIBA   (IID_VISP_IPV6_BASE + 21)
#define IID_IPV6_SFIBC6_INTF_SSA    (IID_VISP_IPV6_BASE + 22)
#define IID_IPV6_SFIBC6_INTF_CFG    (IID_VISP_IPV6_BASE + 23)

/* VRF6 Component*/
#define CID_IPV6_VRF6            ( CID_VISP_IPV6_BASE + 3 )

#define IID_IPV6_VRF6_INTF_FUN   ( IID_VISP_IPV6_BASE + 30 )
#define IID_COMP_VRF6_INTF_FUN    ( IID_VISP_IPV6_BASE + 30 )
#define IID_COMP_VRF6_INTF_CFG    ( IID_VISP_IPV6_BASE + 31 )
#define IID_COMP_VRF6_INTF_SSA    ( IID_IPV4V6_BASE + 32 )


/*==============================================================*/

/*******************************************************
                    MID
  模块ID(即MID)主要用于在申请内存、注册消息队列、注册命令行等的时
  候区分各个模块。VISP项目的模块ID的命名规则为：MID_COMP_模块名
  MID取值必须是ULONG的高2个字节.
  
  注：VISP项目的MID不能与VRPV5的其它模块的MID冲突, 见vos_id.h文
        件。VISP项目的MID在此处定义
*******************************************************/
#define MID_COMP_BASE               0x0E000000   /*VISP部分定义的MID值*/
#define MID_COMP_BASE6              0x0E800000   /*IR及IPV6定义的MID值*/


/* 允许修改模块名.如果增加MID,则每个MID的递增单位是0x00010000,修改需要同步修改TCPIP_MidInfo_IPV4字符串信息 */
#define MID_COMP_PING               ( MID_COMP_BASE + 0x00010000 )
#define MID_COMP_TRRT               ( MID_COMP_BASE + 0x00020000 )
#define MID_COMP_DNSC               ( MID_COMP_BASE + 0x00030000 )
#define MID_COMP_DHCPC4             ( MID_COMP_BASE + 0x00040000 )
#define MID_COMP_SOCKET             ( MID_COMP_BASE + 0x00050000 )
#define MID_COMP_TCP4               ( MID_COMP_BASE + 0x00060000 )
#define MID_COMP_UDP4               ( MID_COMP_BASE + 0x00070000 )
#define MID_COMP_RAWIP4             ( MID_COMP_BASE + 0x00080000 )
#define MID_COMP_ICMP4              ( MID_COMP_BASE + 0x00090000 )
#define MID_COMP_PP4                ( MID_COMP_BASE + 0x000a0000 )
#define MID_COMP_AM4                ( MID_COMP_BASE + 0x000b0000 )
#define MID_COMP_SFIB               ( MID_COMP_BASE + 0x000c0000 )
#define MID_COMP_IFNET              ( MID_COMP_BASE + 0x000d0000 )
#define MID_COMP_ETHARP             ( MID_COMP_BASE + 0x000e0000 )
#define MID_COMP_PPP                ( MID_COMP_BASE + 0x000f0000 )
#define MID_COMP_ACL4               ( MID_COMP_BASE + 0x00100000 )
#define MID_COMP_ATTACK             ( MID_COMP_BASE + 0x00110000 )
#define MID_COMP_SECMAIN            ( MID_COMP_BASE + 0x00120000 )
#define MID_COMP_SECSTAT            ( MID_COMP_BASE + 0x00130000 )
#define MID_COMP_WAITLIST           ( MID_COMP_BASE + 0x00140000 )
#define MID_COMP_COM                ( MID_COMP_BASE + 0x00150000 )
#define MID_COMP_FIBA               ( MID_COMP_BASE + 0x00160000 )
#define MID_COMP_FIBC4              ( MID_COMP_BASE + 0x00170000 )
#define MID_COMP_PPP_STAC           ( MID_COMP_BASE + 0x00180000 )
#define MID_COMP_PPP_STAC_HASH      ( MID_COMP_BASE + 0x00190000 )
#define MID_COMP_PPP_VJCOMP         ( MID_COMP_BASE + 0x001a0000 )
#define MID_COMP_IPHC               ( MID_COMP_BASE + 0x001b0000 )
#define MID_COMP_PPPOE_CLIENT       ( MID_COMP_BASE + 0x001c0000 )
#define MID_COMP_MP                 ( MID_COMP_BASE + 0x001d0000 )
#define MID_COMP_PPPMUX             ( MID_COMP_BASE + 0x001e0000 )
#define MID_COMP_PUBLIC             ( MID_COMP_BASE + 0x001f0000 )
#define MID_COMP_TRUNK              ( MID_COMP_BASE + 0x00200000 )
#define MID_COMP_HA                 ( MID_COMP_BASE + 0x00210000 )
#define MID_COMP_BFD                ( MID_COMP_BASE + 0x00220000 )
#define MID_COMP_POES               ( MID_COMP_BASE + 0x00230000 )
#define MID_COMP_DHCP4R             ( MID_COMP_BASE + 0x00240000 )
#define MID_COMP_OSICP              ( MID_COMP_BASE + 0x00250000 )
#define MID_COMP_MBUF               ( MID_COMP_BASE + 0x00260000 )
#define MID_COMP_GADS               ( MID_COMP_BASE + 0x00270000 )
#define MID_COMP_OAM3AH             ( MID_COMP_BASE + 0x00280000 )
#define MID_COMP_OAM1AG             ( MID_COMP_BASE + 0x00290000 )
#define MID_COMP_IGMP               ( MID_COMP_BASE + 0x002a0000 )

/*Added by l61496  ,模块ID以及错误码整改*/
#define MID_COMP_DCL                ( MID_COMP_BASE + 0x002b0000 )
#define MID_COMP_I3AGENT            ( MID_COMP_BASE + 0x002c0000 )
#define MID_COMP_MIB                ( MID_COMP_BASE + 0x002d0000 )
#define MID_COMP_RIP                ( MID_COMP_BASE + 0x002e0000 )
#define MID_COMP_OSPF               ( MID_COMP_BASE + 0x002f0000 )
#define MID_COMP_RTM                ( MID_COMP_BASE + 0x00300000 )
#define MID_COMP_DIAGNOSE           ( MID_COMP_BASE + 0x00310000 )
#define MID_COMP_RTP                ( MID_COMP_BASE + 0x00320000 )
#define MID_COMP_VLINK              ( MID_COMP_BASE + 0x00330000 )
#define MID_COMP_IPOA               ( MID_COMP_BASE + 0x00340000 )
#define MID_COMP_VLAN               ( MID_COMP_BASE + 0x00350000 )
#define MID_COMP_BFDEXT             ( MID_COMP_BASE + 0x00360000 )
#define MID_COMP_PTP                ( MID_COMP_BASE + 0x00370000 )
#define MID_COMP_L2IF               ( MID_COMP_BASE + 0x00380000 )

/* VISPV1R7C03,为支持NP下发失败对外通知新增子模块ID, 注意: 该ID只用于L2IF模块NP下发失败通知 */
#define MID_COMP_L2IF_VLAN          ( MID_COMP_L2IF + 0x1000 )
#define MID_COMP_L2IF_PORT          ( MID_COMP_L2IF + 0x2000 )
#define MID_COMP_L2IF_MAC           ( MID_COMP_L2IF + 0x3000 )
#define MID_COMP_L2IF_QINQ          ( MID_COMP_L2IF + 0x4000 )

#define MID_COMP_MSTP               ( MID_COMP_BASE + 0x00390000 )
#define MID_COMP_VRRP               ( MID_COMP_BASE + 0x003a0000 )

#define MID_COMP_VRF                ( MID_COMP_BASE + 0x003b0000 )
#define MID_COMP_ACL6               ( MID_COMP_BASE + 0x003c0000 )
#define MID_COMP_OSPFV3             ( MID_COMP_BASE + 0x003d0000 )
#define MID_COMP_RIPNG              ( MID_COMP_BASE + 0x003e0000 )

#define MID_COMP_BLS                ( MID_COMP_BASE + 0x003f0000 )
#define MID_COMP_WLS                ( MID_COMP_BASE + 0x00400000 )
#define MID_COMP_FIREWALL           ( MID_COMP_BASE + 0x00410000 )

#define MID_COMP_GR                 ( MID_COMP_BASE + 0x00420000 )
/* Begin:VISP1.8C03 SYNCE r62469 , 2009-12-21 */
#define MID_COMP_SYNCE              ( MID_COMP_BASE + 0x00430000 )
/* End:VISP1.8C03 SYNCE r62469 , 2009-12-21 */

/*Start TWAMP addition*/
#define MID_COMP_TWAMP          ( MID_COMP_BASE + 0x00440000 )
/*END TWAMP addition*/

/*Start POLICYRT addition*/
#define MID_COMP_POLICYRT          ( MID_COMP_BASE + 0x00450000 )
/*END POLICYRT addition*/

/*NSR组件模块ID*/
#define MID_COMP_NSR          ( MID_COMP_BASE + 0x00460000 )

/*LLDP组建模块ID*/
#define MID_COMP_LLDP               ( MID_COMP_BASE + 0x00470000 )

/*Added by dutianyi00217007，for PTPV2*/
#define MID_COMP_PTPV2              ( MID_COMP_BASE + 0x00480000 )

#define MID_COMP_DISTIP               ( MID_COMP_BASE + 0x00490000 )

/* Added by a00900892，on 03-08-2014 for IP attack statistics module. */
#define MID_COMP_ATK                ( MID_COMP_BASE + 0x004A0000 )

/* Added by LY(57500) for A82D13999, IR模块ID使用VISP统一提供的模块ID, 修改需要同步修改TCPIP_MidInfo_IPV6*/
#define MID_COMP_PPMNG              ( MID_COMP_BASE6 + 0x00000000 )
#define MID_COMP_SOCK6              ( MID_COMP_BASE6 + 0x00010000 )
#define MID_COMP_FIBC6              ( MID_COMP_BASE6 + 0x00020000 ) 
#define MID_COMP_TCP6               ( MID_COMP_BASE6 + 0x00030000 )
#define MID_COMP_ADDRMNG            ( MID_COMP_BASE6 + 0x00040000 )
#define MID_COMP_ICMP6              ( MID_COMP_BASE6 + 0x00050000 )
#define MID_COMP_ND                 ( MID_COMP_BASE6 + 0x00060000 )
#define MID_COMP_RIP6               ( MID_COMP_BASE6 + 0x00070000 )
#define MID_COMP_UDP6               ( MID_COMP_BASE6 + 0x00080000 )
#define MID_COMP_PMTU               ( MID_COMP_BASE6 + 0x00090000 )
#define MID_COMP_DHCP6C             ( MID_COMP_BASE6 + 0x000a0000 )
#define MID_COMP_DHCP6R             ( MID_COMP_BASE6 + 0x000b0000 )
#define MID_COMP_IPSEC              ( MID_COMP_BASE6 + 0x000c0000 )
#define MID_COMP_IKE                ( MID_COMP_BASE6 + 0x000d0000 )
#define MID_COMP_UTIL               ( MID_COMP_BASE6 + 0x000e0000 )
#define MID_COMP_TWL                ( MID_COMP_BASE6 + 0x000F0000 )
#define MID_COMP_EAP                ( MID_COMP_BASE6 + 0x00100000 )

#define MID_COMP_VRF6                ( MID_COMP_BASE6 + 0x00200000 )

/*注: 新增和修改MID时，请保证MID编号的连续性, 另外请同步更新TCPIP_MidInfo_EN*/

/* 上面定义MID_COMP_*** 的方式是为了与VISP其他模块ID方式统一,而下面使用的
*  MID_*** 方式是给IR使用的，他们内部使用的是这个宏名字
*  注意: 下面这部分宏只在给IR的tcpip_id.h头文件中定义,不在VISP自用的tcpip_id.h(即本文件)中定义，
*  否则visp编译时这些宏会与vos_id.h中定义一致，导致编译时产生大量warning
*/
/* End Add by LY(57500) for A82D13999, IR模块ID使用VISP统一提供的模块ID, 2007-4-18 */

/*******************************************************
                   Waitlist ID   
   VISP定义的WAITLIST值从100开始,请IR定义时从1000开始 
********************************************************/
#define WAITLIST_COMP_BASE               100     /*分配VISP WAITLIST空间*/
#define WAITLIST_COMP_IR_BASE            1000    /*分配IR WAITLIST空间*/

#define WAITLIST_UNICASTADDR                    WAITLIST_COMP_IR_BASE + 1
/*End of addition by wn for VISPV1R7 Integration*/

/* VISP各个模块自行定义Waitlist ID */
#define WAITLIST_COMP_ARP_ENTRY         ( WAITLIST_COMP_BASE + 1 )
#define WAITLIST_COMP_DNS_CACHE_S       ( WAITLIST_COMP_BASE + 2 )
#define WAITLIST_COMP_TYPE_VOS_RADIX    ( WAITLIST_COMP_BASE + 3 )
#define WAITLIST_COMP_SOCK_HEADCACHE    ( WAITLIST_COMP_BASE + 4 )
#define WAITLIST_COMP_AM4_Addr          ( WAITLIST_COMP_BASE + 5 )
#define WAITLIST_COMP_ACL               ( WAITLIST_COMP_BASE + 6 )
#define WAITLIST_COMP_PPP_INFO          ( WAITLIST_COMP_BASE + 7 )
#define WAITLIST_COMP_IFNET_CONFIG      ( WAITLIST_COMP_BASE + 8 )
#define WAITLIST_COMP_MP_USERINFO       ( WAITLIST_COMP_BASE + 9 )
#define WAITLIST_COMP_PPPMUX_INFO       ( WAITLIST_COMP_BASE + 10 )
#define WAITLIST_COMP_MTSOFT_MAINTYPE   ( WAITLIST_COMP_BASE + 11 )
#define WAITLIST_COMP_DEVICE_MAINTYPE   ( WAITLIST_COMP_BASE + 12 )
#define WAITLIST_COMP_DHCP_CFG_INFO     ( WAITLIST_COMP_BASE + 13 )
#define WAITLIST_COMP_DHCP_SESSION_INFO ( WAITLIST_COMP_BASE + 14 )
#define WAITLIST_COMP_POESCB            ( WAITLIST_COMP_BASE + 15 )
#define WAITLIST_COMP_DHCP4R_CFG_INFO   ( WAITLIST_COMP_BASE + 16 )
#define WAITLIST_COMP_MP_MPGROUP        ( WAITLIST_COMP_BASE + 17 )
#define WAITLIST_COMP_OAM3AH_PORTINFO   ( WAITLIST_COMP_BASE + 18 )
#define WAITLIST_COMP_L2IF_FDB          ( WAITLIST_COMP_BASE + 19 )
#define WAITLIST_COMP_L2TRANS           ( WAITLIST_COMP_BASE + 20 )
#define WAITLIST_COMP_ARPGUARD_DYNAMIC  ( WAITLIST_COMP_BASE + 21 )
#define WAITLIST_COMP_ARPGUARD_STATIC   ( WAITLIST_COMP_BASE + 22 )
#define WAITLIST_COMP_VRF               ( WAITLIST_COMP_BASE + 23 )
#define WAITLIST_COMP_ETHALAN           ( WAITLIST_COMP_BASE + 24 )
/* Begin:VISP1.8C03 SYNCE r62469 , 2009-12-21 */
#define WAITLIST_COMP_SYNCE_IFINFO      ( WAITLIST_COMP_BASE + 25 )
/* End:VISP1.8C03 SYNCE r62469 , 2009-12-21 */
/* Add by y00176567/z00171897, at 2011-06-29. 修改原因: 增加VLAN一致性告警显示功能 */
#define WAITLIST_COMP_ETHVLAN_CONSISTENCY_WARNING_IFINFO      ( WAITLIST_COMP_BASE + 26 )
#define WAITLIST_COMP_IGMP_CONFIG      ( WAITLIST_COMP_BASE + 27)
#define WAITLIST_COMP_TWAMP_CTTRL_SESS (WAITLIST_COMP_BASE + 28)
#define WAITLIST_COMP_POLICY_ROUTE (WAITLIST_COMP_BASE + 29)

#define WAITLIST_COMP_ARP_IPCONFLICT (WAITLIST_COMP_BASE + 30)

/* Add by d00217007, 2014-01-27, TCP维测接口,查询监听socket */
/* Q0队列 */
#define WAITLIST_COMP_SOCK_LISTENSOCKQ0 (WAITLIST_COMP_BASE + 31)
/* Q队列 */
#define WAITLIST_COMP_SOCK_LISTENSOCKQ (WAITLIST_COMP_BASE + 32)


/**********************************************************
               DEBUG信息的类型宏定义
               VISP DEBUG信息统一划分为3个等级
**********************************************************/
#define IC_INFO_LOG             1
#define IC_INFO_TRAP            2
#define IC_INFO_DEBUG           3

#define TCPIP_IC_INFO_LOG       1
#define TCPIP_IC_INFO_TRAP      2
#define TCPIP_IC_INFO_DEBUG     3

/* Wanghui add, D00645: Define length MACRO, to remove magic numbers */
#define LEN_4        4
#define LEN_8        8
#define LEN_16       16
#define LEN_32       32
#define LEN_64       64
#define LEN_128      128
#define LEN_192      192
#define LEN_256      256
#define LEN_512      512
#define LEN_1024     1024
#define LEN_2048     2048
#define LEN_4096     4096

/************************************************************
              VISP预配置参数类型定义
************************************************************/
/************************************************************
预配置值说明(Adjusted by z62474 for A82D12602, 2007/04/02)：
预配置值必须大于等于0，不可以为负值；
若预配置了负值-X(X>0)时，在使用时被认为是(0xFFFFFFFF-X+1)；
当配置值超出允许范围时，系统仍使用缺省默认值；
注意: 如果有修改预配置(新增项/删除项/修改枚举名)枚举值，则必须同步 TCPIP_PreConfigKeyInfo_EN.
************************************************************/
typedef enum TCPIP_PRECONFIG_INFO_Etag
{
    /*一个接口下最大静态ARP表项数量。默认值:512,可配置值1~4096。*/
    ETH_MAX_STATIC_ARP,  /* 0 */

    /*一个接口下最大动态ARP表项数量。默认值:256,可配置值1~65536。*/
    ETH_MAX_DYNAM_ARP,   /* 1 */

    /*最大路由表项数目。默认值:64,可配置值1~1024。*/
    SFIB_SRM_ROUTE_NUM,  /* 2 */

    /*是否处理IFNET上报的VLINK消息而生成对端路由。默认值:1,处理。可配置值:0,不处理；1,处理*/
    SFIB_SRM_VLINK,      /* 3 */

    /*最大路由表项数目。默认值:64,可配置值1~1024。*/
    SFIB6_SRM_ROUTE_NUM, /* 4 */

    /*是否处理IFNET上报的VLINK6消息生成对端路由。默认值:1,处理。可配置值:0,不处理；1,处理*/
    SFIB6_SRM_VLINK,     /* 5 */

    /*Request报文的重传次数。默认值:5,可配置值1~10。*/
    PPP_CFG_CONFREQS,    /* 6 */

    /*配置缺省同异步转换字符集。默认值:0xffffffff (所有控制字都转换) */
    PPP_CFG_DEFAULT_ACCM,/* 7 */

    /*配置缺省MRU。默认值:1500,可配置值46~2000。*/
    PPP_CFG_DEFAULT_MRU, /* 8 */

    /*配置: 缺省Echo超时时间(单位: 毫秒)。默认值:10000,可配置值:1~30000*/
    PPP_CFG_ECHO_TIMEOUT,/* 9 */

    /*PPP组件是否需要CHAP支持。默认值:0,不需要。可配置值:0,不需要；1，需要。*/
    PPP_CFG_NEED_CHAP,   /* 10 */

    /*配置缺省是否需要LCP协商。默认值:1,需要。可配置值:0,不需要；1，需要。*/
    PPP_CFG_NEED_LCP,    /* 11 */

    /*第一次协商不成功以后，是否等待一定时间后继续循环协商。默认值:1,需要。可配置值:0,不需要；1,需要。*/
    PPP_CFG_NEED_LOOPNEGO,/* 12 */

    /*配置缺省是否需要NCP协商。默认值:1,需要。可配置值:0,不需要；1,需要。*/
    PPP_CFG_NEED_NCP,     /* 13 */

    /*PPP组件是否需要PAP支持。默认值:0,不需要。可配置值:0,不需要；1,需要。*/
    PPP_CFG_NEED_PAP,     /* 14 */

    /*配置: 一次协商的超时时间(单位: 毫秒)。默认值:6000,可配置值:1~30000*/
    PPP_CFG_NEGO_TIMEOUT, /* 15 */

    /*一个运行节点最大PPP控制块数, 一般与接口数相同。默认值:64,可配置值1~4096*/
    PPP_CFG_MAX_CTLNUM,   /* 16 */

    /*PPP模块初始化时是否创建异步报文队列，默认值:PPP_NO_ASYQUE(否),
    可配置值:PPP_NO_ASYQUE(否), PPP_NEED_ASYQUE(需要)*/
    PPP_CFG_NEED_ASYQUE,  /* 17 */

    /*设置TCP格式的最大CID值。默认值:15,可配置值:3-255*/
    PPP_CFG_TCP_SPACE,    /* 18 */

    /*设置非TCP格式的最大CID值。默认值:15,可配置值:3-65535*/
    PPP_CFG_NON_TCP_SPACE,/* 19 */

    /*设置是否协商(Enhanced) RTP Compression子选项。默认值:1。可配置值:0,不协商；1，协商*/
    PPP_CFG_RTP_COMPRESSION,/* 20 */

    /*设置是否协商只压缩TCP/非TCP报文压缩子选项*/
    /*默认值:0。可配置值:0，压缩全部报文, 1，只压缩非TCP报文；2，压缩TCP报文，3，全部不压缩*/
    PPP_CFG_COMPRESS_TYPE,  /* 21 */

    /*设置采用何种选路策略, 可配置值: 0 ~ 5, 默认值为1(选择最近添加的等价路由项)，超过范围取默认值*/
    SFIB4_CFG_ROUTE_BALANCE,/* 22 */

    /*设置采用何种选路策略, 可配置值: 0 ~ 2, 默认值为1(选择最近添加的等价路由项)，超过范围取默认值*/
    SFIB6_CFG_ROUTE_BALANCE,/* 23 */

    /*接收报文时是否先与本机地址比较的开关。打开则在接收报文先与本机地址链比较，
     有相同就直接上交给运输层处理。默认值:0(否)；可配置值:0(否), 1(是)*/
    PP4_CFG_DIRECTLOOKUPIP, /* 24 */

    /*配置:以下3个键值为MBUF CACHE的head,DBD,DB数目,配置值必须是2的n次方*/
    MBUF_CFG_HEAD_CACHE_NUM,/*默认值128，配置值在1到4096之间，超过范围取默认值*/  /* 25 */
    MBUF_CFG_DBD_CACHE_NUM, /*默认值128，配置值在1到4096之间，超过范围取默认值*/  /* 26 */
    MBUF_CFG_DB_CACHE_NUM,  /*默认值128，配置值在1到8192之间，超过范围取默认值*/  /* 27 */

    /*是否对MBUF CACHE进行共享数据互斥保护, 默认值:1(是)；可配置值:0,否; 1,是*/
    MBUF_CFG_CACHE_LOCK,    /* 28 */

    /*配置TCPCB是否缓存下一跳和出接口信息。默认值:1(是)；可配置值:0,否；1,是*/
    TCP4_CFG_NEED_CACHE,    /* 29 */

    /*SOCKRUN任务优先级。取值范围1~255，默认值100。*/
    SKT_TASK_SOCK_PRIO,     /* 30 */

    /*SOCKRUN任务堆栈大小。取值范围8K~64K，默认值为16K。*/
    SKT_TASK_SOCK_STACKSIZE,/* 31 */

    /*实现光网络OSP的定制需求，OSP使用光网络自己的RM模块，而非VISP SFIB的SimpleRM特性。*/
    /*实现SGSN的动态路由协议需求，SGSN用户使用DCL RTM模块，而非VISP SFIB的SimpleRM特性。*/
    /*1 - 使用VISP SimpleRM模块， 0 - 使用光网络的RM模块，2 - 使用DCL RTM模块。默认值为1，即使用VISP SimpleRM。*/
    SFIB_SRM_CFG_ENABLE,    /* 32 */

    /*是否需要使用第三方任务，取值:VRP_YES(需要)，VRP_NO(不需要).默认值:VRP_NO*/
    TCPIP_CFG_NEED_SWITCHTASK, /* 33 */

    /*第三方任务的优先级,取值:VOS_T_PRIORITY_IDLE到VOS_T_PRIORITY_ABOVE_NORMAL，默认为VRP_TASK_DELAY_PRIO*/
    TCPIP_CFG_SWITCHTASK_PRIOR,/* 34 */

    /*是否使能全局SOCKET, 取值:1-使能, 0-不使能; 默认值: VRP_YES(使能)*/
    SKT_GLOBAL_SOCKET_EN,      /* 35 */

    /*是否使用TCP发送处理优化, 取值:1-使用, 0-不使用; 默认值: VRP_NO(不使用)*/
    TCP4_OUTPUT_OPTIMIZE,      /* 36 */

    /*实现光网络定制需求，是否使能双OSPF特性，取值: 1-使能，0-不使能；默认值:VRP_NO(不使能) */
    RAWIP_DOUBLE_OSPF,         /* 37 */

    /*是否需要使用MPQOS，取值:VRP_YES(需要)，VRP_NO(不需要)，默认值:VRP_NO*/
    TCPIP_CFG_NEED_MPQOS,      /* 38 */

    /*是否使能IP队列调度优化，取值:0-不使能, 1-使能; 默认值: 0 */
    ETH_IPINPUT_OPTIMIZE,      /* 39 */

    /*是否使能UDP发送流程优化，使能后将不支持跨板DHCP Relay, 取值:0-不使能, 1-使能; 默认值: 0 */
    UDP4_OUTPUT_OPTIMIZE,      /* 40 */

    /*按照模块使能HA功能:0-不使能，1:使能基本模块，2:使能ETH模块，4:使能PPP模块......0xffffffff-使能全部模块HA功能 */
    TCPIP_NEED_ENABLE_HA,      /* 41 */ 

    /*HA是否备份动态ARP表项，1-备份，0-不备份*/
    ETHARP_HA_DYNA_ARP,        /* 42 */

    /*接口physical地址的设置方式，0-发送免费ARP,1-直接设置(主备一致，倒换后生效),2-主备一致，备份后立即生效 */
    ETHARP_HA_SETMAC_METHOD,   /* 43 */

    /*Add for UDP6&RawIP6 source cache,0-不使能,1-使能, 默认值:0*/
    IPV6_IR_HEADCACHE,         /* 44 */

    /*Add for TCP6 next-hop and output interface cache,0-不使能,1-使能, 默认值:0*/
    TCP6_CFG_NEED_CACHE,       /* 45 */

    /*Add for TCP6 output optimize,0-不使能,1-使能, 默认值:0*/
    TCP6_OUTPUT_OPTIMIZE,      /* 46 */

    /* Trunk模块系统优先级 */
    TRUNK_SYS_PRI,             /* 47 */
    
    /* DHCP4R使能配置模式, 0-接口模式，1-全局模式 ,2-光网络自动模式 */
    DHCP4R_CFG_MODE,          /* 48 */

    /* 路由表下发NP模式,1-下发最优,0-全部下,默认为0*/
    SFIB_NP_UPDATEMODE,              /* 49 */
    
    /* IPHC是否在NP模式,1-NP模式,0-非NP模式 默认为0*/
    PPP_CFG_IPHC_NP_SWITCH, /* 50 */

    TCPIP_ENABLE_CACHEDPKT,          /* 51 报文缓存功能 0-不使能,1-使能, 默认值:1*/
    
    SFIB_ROUTE_SUBNET_BROADCAST,     /* 52 子网广播路由，0-不使能，1-使能，默认值:0*/

    /* 是否协商OSICP直接上报UP,1协商,0不协商 */
    PPP_CFG_NEED_OSICP,              /* 53 */

    /* 是否使能HA无损升级 0-不使能, 1-使能, 默认值:0 */
    TCPIP_ENABLE_HA_UPDATE,          /* 54 */

    /* 3ah np模式 */
    OAM3AH_NP_MODE,                  /* 55 3AH NP模式,0-VISP软件模式,1-半NP,2-全NP */   
    
    OAM1AG_NP_MODE,                  /*56,1ag np 模式,0-软件模式,1-半NP模式,2-全NP模式*/
    
    IF_CFG_3DIMENSION_ENABLE,        /*57配置接口维数，0-一维接口，1-分步式3维接口，2-集中式三维接口；默认值为0*/

    PPP_CFG_IPHC_UNIDIRECTION,       /* 58, 是否支持IPHC单向处理 0-不使能, 1-使能, 默认值:0*/

    IGMP_CFG_IFS_NUMS,               /* 59, 每个接口加入的多播组达到满规格时，支持配置IGMP的接口总个数 */

    IF_CFG_MULTIGRP_NUMS,            /* 60, 一个接口配置多播组的个数*/

    /*DHCP Client地址配置模式*/
    DHCP4C_ADDR_CFG_MODE,            /*61  0：DHCP CLient获取地址不能为相同网段; 1：可以为相同网段*/

    PTP_CFG_TASK_PRI,                /*62, PTP任务优先级,默认100,范围0~255*/

    PTP_CFG_DEV_TYPE,                /*63, PTP时钟设备类型,默认0,范围0~5: 0-OC,1-E2ETC,2-P2PTC,3-OC+E2ETC,4-OC+P2PTC,5-BC目前不支持,为保留*/

    PTP_CFG_SOFT_MODE,               /*64, PTP时钟组件的软件模式,默认1: 0-纯软模式,1-PTP管理 FPGA同步模式*/

    OAM3AH_LINKEVENT_FRAME_ACT,      /* 65  3AH 错帧或错帧秒实现方式; 0-VISP实现; 1-外层(NP/驱动)实现; 默认值 0 */
    /*ETHARP 地址冲突检测处理模式,默认为0*/
    ETHARP_IP_CONFLICT_MODE,        /*66  0：由外部模块处理(处理函数通过TCPIP_RegFuncDealIpConflictHook注册);
                                          1：由VISP自行处理; */
    PPP_CHAP_CLIENT_CHECKUSER,      /*67 Chap Client端是否验证Server发送过来的USER NAME 0:不验证  1:验证, 默认为0 */                                      

    /* 3AH 错帧周期事件窗口值配置模式;取值如下:
       0-配置的错帧周期事件的窗口值为时间值,下发到驱动后,由驱动换算为该时间内的最小尺寸帧数目作为错帧周期事件的窗口值; 
       1-配置的错帧周期事件的窗口值为帧数目,即在一定时间内驱动能够接收的最小尺寸帧数目; 
       默认值:0   */
    OAM3AH_ERR_FRMPRD_EVENT_SETMODE,      /* 68 */

    /* 3AH 错误符号周期事件窗口值配置模式;取值如下:
   0-配置的错误符号周期事件的窗口值为时间值,下发到驱动后,由驱动换算为该时间内能接收的符号数作为错误符号周期事件的窗口值; 
   1-配置的错误符号周期事件的窗口值为符号数,即在一定时间内驱动能够接收的符号数; 
   默认值:0   */
    OAM3AH_ERR_SYMPRD_EVENT_SETMODE,      /* 69 */

    DCL_DIAG_MOMORY_TRACE,           /* 70 是否使能DCL提供的内存追踪功能，默认不使能。
                                        此功能可以记录DCL中各模块的内存分配使用情况 */
    VLINK_ROUTE_PRIORITY,            /* 71 预配置VLINK路由的优先级,默认值为0,取值范围为0--255 */

    IPC_ROUTE_CFG_ENABLE,           /* 72 支持IPC路由下发失效的使能配置，默认值为0-不使能，取值范围0--1*/

    RTM_CFG_ATM_TYPE,                    /* 73 ATM接口类型的静态路由使能配置，默认值为0-不使能，取值范围0--1*/

    IPC_VLINK_ROUTE_NOTIFY_ENABLE,  /* 74 支持VLINK路由上报通知DCL,默认值为0-不使能，取值范围0--1*/
    
    L2IF_CFG_ML_NUM,                /* 75 L2IF ML数目,默认4096，可配置0-16k */
    L2IF_CFG_STATIC_FDB_NUM,        /* 76 L2IF 静态FDB配置数目,默认128,可配置0-1024 */

    NCP_NEED_MP_HEAD,                /* 77,NCP报文是否需要封装MP头部，默认为1，表明封装MP头部，0表示不封装MP头部*/
    
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    VRF_CFG_MAX_INSTANCE_NUM,       /* 78 最大VRF实例个数，默认值为1，取值范围1~1024，*/
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

    /* VISP1.8.1 支持1AG标准协议开发*/
    OAM1AG_DEFAULT_VERSION,          /* 79 1AG默认使用的版本号, 取值范围:0~1。0 : 表示使用Draft7版本的1AG协议; 1表示使用标准版本的1AG协议. 默认值为0,即Draft7  */
    
    BFD_IPV6_ENABLE,                 /* 80,默认不使用IPv6 BFD, 0--不使用,1---使用*/
    
    ETH_ARP_NOTNET_REPLY,           /* 81 ETHARP不回复不同网段的ARP请求,缺省回应0，可设置不回应1 */
    PPPMUX_NP_MODE,                 /* 82 在NP模式下不启动PMUX任务，缺省0启动，可设置为1不启动 */

    SFIB_UPDATE_FIB_NP_MODE,         /* 83 VISP路由变更后，通知NP路由更新的模式。0，原有模式，先增后删。1，新增模式，先删后增 */

    ARP_GUARD_BLACK_EXPIRE_TIME,     /* 84,ARP黑名单老化时间,默认20分钟,取值范围5分钟到20分钟 */

    ETH_STATICARP_DOWNLOAD,          /* 85 配置(添加删除更新)静态ARP下发NP, 0-不下发 1-下发 默认值0 */

    ETH_ARPMISS_NOTNET_TIMEOUT,      /* 86 用户上报ARP MISS,如果地址和接口不是同一网段哑元老化时间, 0~300s,默认是0,即等待超时定时器 */

    ETHARP_CHECK_PKT_SRCMAC,         /* 87 是否检查ETH报文的源MAC,1为检查,0为不检查,默认为1 , 2 :src mac will be checked inside ARP packet**/

    /* Added by z43740 for for BC3D01909: 支持使用系统定时器,2009-08-16 */
    PPP_CFG_GLOBAL_TIMER,            /* 88,PPP定时器模式，缺省全局模式1，可设置为单独模式0 */
    /* End of addition */

    SFIB6_NP_UPDATEMODE,              /* 89 路由表下发NP模式,1-下发最优,0-全部下,默认为0*/
    SFIB6_UPDATE_FIB_NP_MODE,        /* 90 VISP路由变更后，通知NP路由更新的模式。0，原有模式，先增后删。1，新增模式，先删后增 */

    /*Added by eswar*/
    /*Pre configuration IDs for firewall module*/
    FW_WLS_MAX_RULE,        /* 91 Maximum number of rules for whitelist*/

    FW_BLS_MAX_RULE,        /* 92 Maximum number of rules for blacklist*/

    FW_AD_IF_CFG_MAX_RULE,    /* 93 Maximum number of interface based attack rules*/

    FW_AD_FLOOD_CFG_MAX_RULE,    /* 94 Maximum number flood based atrack rules*/

    FW_ACLFW_MAX_IFINDEX,    /* 95 Maximum number interface indexes binding with acl group*/

    FW_ACL_RFC_MAX_MEM_USE,    /* 96 Maximum memory usage for acl rfc*/

    FW_ENABLE_MAC_BASE_ACL_FILTER,    /* 97 To enable/disable mac based acl filter*/
    /*End of addition*/

    /* 为支持RPU特殊应用场景增加该预配置 */
    ETHARP_FREEARP_REPLY_UNICAST,            /* 98, 是否对地址冲突的免费ARP采用单播应答，缺省为0(广播)，1(单播) */

    PPI_DOWNLOAD_MODE_FOR_SGSN,      /* 99 PPI下发模式,1为SGSN模式:BFD会话删除时只下发BFD_PPI_USER_DELETE,
                                     不下发BFD_PPI_SESSION_DELETE ; 成员端口从Trunk移除时，不对外上报告警
                                     0为缺省模式:BFD会话删除时下发BFD_PPI_USER_DELETE和BFD_PPI_SESSION_DELETE ;
                                     成员端口从Trunk移除时，对外上报告警*/
    

    TCPIP_SOCK_TIMER_QUE_LEN,        /* 100 支持预配置SOCK任务定时器队列的长度 */
    PTP_IPV6_ENABLE,        /*101 使能PTP IPv6；1: 使能；0: 去使能*/
    SYNCE_DEFAULT_QL,                    /*102 同步以太默认配置值*/                                 
    TCP_SYN_USE_CONFIG_TOS,         /* 103 TCP三次握手时，不使用对端报文中携带的TOS值，而是使用本端配置的TOS值 */
    SOCK_RAND_PORT_ENHANCE,         /* 104 优化SOCKET随机端口的生成方式 */
    BFD_MULTI_HOP_TTL,                     /* 105  SGSN需求，支持预配置BFD多跳会话的发送方向报文的TTL取值b00177000 2011-01-15 */
    BFD_TOTAL_SESSION_NUM,          /* 106  BFD total session number 缺省为512~5120，根据产品需要设置*/
    OSPF_DEFUALT_COST,              /*107  OSPF 接口默认 COST值*/
    OSPF_DEFAULT_PRIORITY,          /*108  OSPF 接口默认 DR优先级*/
    PPP_IPCP_SUBOPTION_AUTO_ADAPT,    /*109  PPP IP-Compression-Protocol 子选项自适应协商IPHC: 
                                          0表示不自适应协商;1表示自适应协商，但仅在本端未使能IPHC子选项协商的情况下有效!! */
    TCPIP_TRACE_ROUTE_USE_DIP_FOR_SIP, /* 110 0:ICMP响应的源地址是入接口最匹配的地址，1:ICMP响应的源地址是接收到的报文的目的IP*/
    /* Add for V2R3C07, by z00208058/w00207740, at 2012-4-16. 修改原因: TRUNK LACP下移需求开发 */
    TRUNK_NP_MODE,                  /*111 Lacp保活模式: 1,由NP收发lacp报文；0，由协议栈收发 */
    /*Added by z00208058/w00207740, BFD会话规格扩展, 2012/5/8 */
    BFD_MAX_SESSION_NUM,            /*112  BFD会话规格扩展1000~5120*/

    /*Added by limin00188004, LLDP任务优先级可配置, 2012/10/12   问题单号:DTS2012101007308 */
    LLDP_CFG_TASK_PRI,              /*113  LLDP任务优先级,默认100,范围0~255*/
    /* End of Added by limin00188004, 2012/10/12   问题单号:DTS2012101007308 */

    SOCK_BIND_MAX_PORT,             /*114  socket  端口号最大值预配置，默认50000，范围50000~65535*/
    OAM3AH_BOARD_STATE,             /* 115 是否使用3AH与接口状态联动功能 */
    TRUNK_LB_TONEUP,                /* 116 Trunk子链路环回增强  默认为0，不增强 范围0和1*/
    ETHATRP_EXPIRE_UPDATEMODE,     /*117  Distinguish between main interface and sub interface for setting the expire time value and also the effect of the change on existing Arp entries
                                                    Range:[0,2] 0:Main-interface mode with affecting existing entries(SGSN) 1: Sub interface mode with affecting existing entries(HERT) 2: subinterface mode without affecting existing entries(MCCP)*/             
    TCPIP_HA_KEEPALIVE, /* 118 : 0(缺省值):不启动HA通道保活功能, 1-5:启动HA通道保活功能保护周期(s) */
    ETHIF_MAX_NUM,      /*119 可创建的最大接口数，默认4096，范围4096~65535*/
    ETHIF_UPDATE_TIMER_PERIOD,      /*120 ARP 定时器更新周期 ，范围100~5000ms*/
    OAM1AG_CC_ENABLE_MODE,         /*121  ￡?·??§0-1, ??è??a0:??·￠±íê????ˉ   1 ???ˉì?2aDèòaμ￥?à????*/ 
    SKT_TASK_SOCK_LINUX_STACKSIZE, /* 122 linux??è???????′óD??￡è??μ·??§8K~16M￡???è??μ?a8M*/
    
    ETH_ARP_PPI_UPDATE_ON_REF,    /*123 Product has to use this key in pre-config if refreshed expire time and fake ARP entry has to be updated on NP using PPI*/

    ETHARP_EXPIRETIME,   /*124, Using this user can set the expiry time, Entry will not be deleted within this time if ARP Response is not recieved*/
    SUBIF_MAX_VIDNUM,   /* 125,Maximum VLAN ID */
    LINK_IO_CTL_QUEUE_LENGTH,    /*126,底层链路控制信息消息队列大小预配置,默认为1024,该队列消息是SOCK RUN任务处理,DTS2013052902550*/	
    ETHARP_ARP_PKTS_ONETIME,     /*127 ARP报文一次处理的个数，默认40个，最大1000个*/
    LLDP_ADD_PORT_MODE,  /*128,提供预配置，可以由产品将接口添加到LLDP的端口表，默认VISP在创建接口时联动添加,DTS*/
    ETHARP_MAX_SYS_DYNAM_ARP,    /*129 配置系统级动态APR个数 */
    TCP_LAND_ATTACK_SWITCH,      /*130 TCP LAND防攻击开关，VRP_NO表示关闭，VRP_YES表示打开，默认VRP_NO:0 关闭*/
    ETH_ARP_DEL_DELAY_TIME,      /* 131 是否支持接口物理down延迟删除接口下的ARP表项 0:不支持;1-5:延迟时间 */
    /*Added by guojianjun178934, NSR功能预配置项, 2012/11/26   问题单号:20121126_NSR_01 */
    NSR_OSPF_ENABLE,          /*132 是否使能OSPF NSR, 0-不使能, 1-使能, 默认值:0*/
    NSR_CFG_TASK_PRI,         /*133  NSR任务优先级,默认100,范围0~255*/
    /* End of Added by guojianjun178934, 2012/11/26   问题单号:20121126_NSR_01 */
    /*Added by w00207740, NSR TRUNK,NSR功能裁剪宏, 2013/8/2 */
    TRUNK_NSR_FEATURE,              /* 134 TRUNK NSR特性裁剪宏 */
    BFD_NSR_FEATURE,                /* 135 BFD NSR特性裁剪宏 */
    OAM1AG_MD_NUM,              /*136 内存优化支持预配置MD个数 */
    OAM1AG_MA_NUM,              /*137 内存优化支持预配置MA个数 */
    OAM1AG_MEP_NUM,             /*138 内存优化支持预配置MEP个数 */
    OAM1AG_RMEP_NUM,            /*139 内存优化支持预配置RMEP个数 */
    PLC_ROUTE_MAX_POLICY_VRF,
    PLC_ROUTE_MAX_POLICY_NODE,

    NSR_ENABLE,                 /*142 是否使能NSR, 0-不使能, 1-使能, 默认值:0*/
    /*Added by zhoushisong202096, 支持MBUF预留长度可扩展, 2013/11/25 */
    MBUF_CFG_USER_RESERVE_SPACE,    /*143 支持MBUF预留长度可扩展宏*/
    /*Added by w00207740, Trunk Msp大规格需求,若此处最大规格有变，需要修改IF_Sh_RegIFClass中if_ulEndNum、if_ulMaxNum字段 2014/1/9 */
    TRUNK_IFNUM_MAX,                /*144 支持可配置Trunk最大接口数目，默认32，范围32~128*/
    /*Added by fengjing209023, TCP4,6 cookie开关 2014/1/21 */
    TCP4_COOKIE_SWITCH,             /*145 TCP4 COOKIE开关 */
    TCP6_COOKIE_SWITCH,             /*146 TCP6 COOKIE开关 */

    /*Added by fengjing209023, MAC功能开关 2014/3/21 */
    MAC_CHANGE_IP6_STATE_SWITCH,    /*147 MAC功能开关 */  
    /*Added by fengjing209023, MAC功能开关 2014/3/21 */

    /*add by wuling 00201943 for IPv6协议DOWN不下发邻居删除PPI 2014-03-25 :S-IP-003-IPv6-008--start*/
    IP6_DOWN_NO_PPI_DEL_ND,  /*148*/
    /*add by wuling 00201943 for IPv6协议DOWN不下发邻居删除PPI 2014-03-25 :S-IP-003-IPv6-008--end*/
    
    ETH_STATICARP_REF_DIFFNET,   /* 149 在不使能严格学习的场景下不同网段的ARP报文是否刷新静态ARP表项(0 刷新ARP表项 1 不刷新) */
    ARP_STRICT_LEARN_SWITCH_MODE, /* 150 ARP严格学习全局模式和接口模式配置开关(0全局模式 1接口模式，默认0) */

    IPV4_ADDR_SUPPORT_32BITS_MASK_SWITCH, /* 151 IPV4地址支持32位掩码，不支持RTM路由模式 */

    IPV4_ADDR_SUPPORT_SAME_SUBNET, /* 152 IPV4地址支持不同接口同网段地址配置(0 不支持 1 支持，默认不支持)
                                          cation:1.此配置当前只支持SRM模式,DCL模式仍不支持。*/

    TCPIP_ICMP_REFLECT_SRCIP_WITH_DSTIP, /*153 CSEC扫描安全问题，0:默认值，不对ICMP响应源IP做安全保护;
                                                            1:对ICMP响应源IP做安全保护，源地址
                                                              是接收到的报文的目的IP */

    SKT_TASK_DHCP4R_PRIO,       /*154 DHCP4R任务优先级,默认值:100,范围1~255*/

    SFIB_ROUTE_CACHE_SWITCH,    /*155 路由缓存开关，0-关闭，1-打开，默认值:1*/

    /* Added by fengjing209023 for DTS2014061301920 BALONG DAD优化需求，打开后不做DAD和initial delay */
    IPV6_ND_NO_DAD_SWITCH,      /*156 不做DAD开关，0-关闭，1-打开，默认值:0 当前只支持在主机模式 */

    /*Added by guojianjun178934, 【SIT-集成测试-公共基础】预配置值在V3各版本中不统一, 2014/11/11   问题单号:DTS2014111000166 */
    /*所有版本预配置项需要保持一致，当前修改：在C10基础上新增C20配置项*/
    /* Added by fengjing209023 for 全局动态黑名单规格 */
    ARP_BLACKLIST_SYS_MAXNUM,   /*157 控制整个系统的动态黑名单个数，范围[0,256000]，默认为0表示不做限制。 */
    
    BFD4_PORT_SHOW_SWITCH,      /*158 BFD是否对外显示端口，0-不显示，1-显示，默认值:1 对外显示 */

    DHCP4R_PORT_OPEN_SWITCH,    /*159 DHCP4R是否对外开启端口，0-不开启，1-开启，默认值:1 对外开启 */

    PTP_PORT_OPEN_SPECIFIC_SWITCH,/*160 PTP是否对外开启端口，0-不开启，1-开启，默认值:1 对外开启 
                                        CAUTION: 仅针对光网 *specific */

    /*tcp异步消息socket应该默认保持前向兼容*/
    SOCK_FIOASYNC_COMPLIANCE_SWITCH, /*161 TCP4/TCP6子socket是否继承父socket异步消息属性，0-继承; 1-不继承; 默认0继承 */

    LLDP_INTERFACE_AND_NEIGBOR_MAX_NUM,         /*162 LLDP maximum supported interface */
    
    ETHARP_SWAP_POLICY_SWITCH, /*163 ARP规格满情况下的原有替换策略,默认为1即保持原有的替换策略,0时关闭替换策略*/

    IP_INPUT_TYPE,                  /*164 分布式socket的IP接收开关 */
    
    ACLFW6_MAX_IFINDEX,         /*165 Maximum interface Index supported for acl6 firewall*/

    IPV6_ADDR_SUPPORT_SAME_SUBNET,    /* 166 Set as 1 to support same subnet address on multiple interface */
    /* End of Added by guojianjun178934, 2014/11/11   问题单号:DTS2014111000166 */

    /* Added by caiqizheng for S-IP-C20-005-VRF.001 */
    RTM_SCK_COM_SWITCH,    /*167 动态路由模式下SCK组件裁剪开关，0-关闭，1-打开，默认值:1*/

    DNS_QUERY_TIMEOUT_VALUE,   /**< 设置用户指定的DNS服务器端超时时间，单位秒。取值范围[1, 5]，默认值5 */
    /* End */

    TCP_REASS_MAXSEG,   /* 169 TCP重组的最大段数目 */
    TCPIP_MAX_COM_PARA_NUM           /* 枚举边界值，新增预配置项时必须在此之前定义 */

    /* 注意: 如果有修改预配置(新增项/删除项/修改枚举名)枚举值，则必须同步 TCPIP_PreConfigKeyInfo_EN. */
}TCPIP_PRECONFIG_INFO_E;


#endif  /* end of _TCPIP_ID_H_ */

#ifdef  __cplusplus
}
#endif

