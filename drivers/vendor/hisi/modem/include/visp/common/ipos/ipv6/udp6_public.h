/***********************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*-----------------------------------------------------------------------
*                              Udp6_public.h
*
*    Project Code:  VRP5.0
*    Module Name :  UDP6
*    Create Date :  2003/06/23
*    Author      :  Aparna Shah
*    Description :  To define UDP6 data structures used by external modules
*-----------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------
*  2006-04-11  Aparna Shah    Created for including all public definitions in
*                             this file, for IPOSV1R1
************************************************************************/
#ifndef _UDP6_PUBLIC_H
#define _UDP6_PUBLIC_H

#ifdef  __cplusplus
extern "C"{
#endif

/*MAX_INT to arm allign the enums*/
#define IP6_UDP6_MAX_ENUM_VALUE            0xFFFFFFFF


#define UDP6_SOCK_MAXFILTNUM 5

#define UDP6_SOCK_FILTOK 0
#define UDP6_SOCK_FILTINUSE 1
#define UDP6_SOCK_FILTTOOMUCH 2
#define UDP6_SOCK_FILTNOTFOUND 3
#define UDP6_SOCK_FILTNONE 4
#define UDP6_SOCK_FILTADD 5
#define UDP6_SOCK_ERROR 6
#define UDP6_ERR_SEMOP_ACQUIRELOCK_FAIL 7

#define IPV6UDPTABLE_TBL            5
#define CFGMIB_IPV6UDPLOCALADDRESS  CFG_CMO_DEF(MID_UDP6, IPV6UDPTABLE_TBL, 1)
#define CFGMIB_IPV6UDPLOCALPORT     CFG_CMO_DEF(MID_UDP6, IPV6UDPTABLE_TBL, 2)
#define CFGMIB_IPV6UDPIFINDEX       CFG_CMO_DEF(MID_UDP6, IPV6UDPTABLE_TBL, 3)



#ifdef COMPILING_IR_IPV6_CORE
#pragma pack(1)
#endif

/*UDP6 statistics*/
typedef struct    tagUDP6STAT {
    DULONG dulHCInDatagrams;
    DULONG dulHCOutDatagrams;
                /* input statistics: */
    ULONG ulUdp6s_ipackets;    /* total input packets */
    ULONG ulUdp6s_hdrops;      /* packet shorter than header */
    ULONG ulUdp6s_badsum;      /* checksum error */
    ULONG ulUdp6s_nosum;       /* no checksum */
    ULONG ulUdp6s_badlen;      /* data length larger than packet */
    ULONG ulUdp6s_noport;      /* no socket on port */
    ULONG ulUdp6s_noportmcast; /* of above, arrived as broadcast */
    ULONG ulUdp6s_fullsock;    /* not delivered, input socket full */
    ULONG ulUdp6ps_pcbcachemiss;   /* input packets missing pcb cache */
                /* output statistics: */
    ULONG ulUdp6s_opackets;        /* total output packets */
    ULONG ulUdp6s_ExtPreProc;
    ULONG ulPad;
}UDP6STAT_S;

#ifdef COMPILING_IR_IPV6_CORE
#pragma pack()
#endif

#ifdef COMPILING_IR_IPV6_CORE
#pragma pack(1)
#endif

/*UDP6 MIB connection*/
typedef struct tagIP6_UDP6_MIB_CONN
{
    IN6ADDR_S   stIpv6UdpLocalAddress;
    ULONG  ulIpv6UdpIfIndex;
    USHORT usIpv6UdpLocalPort;
    CHAR chPad[2];
}IP6_UDP6_MIB_CONN_S;

/* UDP6 Header*/
typedef struct tagUDP6HDR
{
    USHORT    usSPort;        /* source port */
    USHORT    usDPort;        /* destination port */
    SHORT     sULen;          /* udp length */
    USHORT    usSum;          /* udp checksum */
}UDP6HDR_S;

#ifdef COMPILING_IR_IPV6_CORE
#pragma pack()
#endif

#define UDP6_SOCK_NOFILTER 0

#ifdef COMPILING_IR_IPV6_CORE
#pragma pack(1)
#endif

/*UDP6 socket debug filter id*/
typedef struct tagUDP6_SOCKDBUGFILT
{
    ULONG   ulTaskId;        /* 存放用户设置的过滤条件中的任务ID   */
    ULONG   ulSockId;        /* 存放用户设置的过滤条件中的套接口号 */
}UDP6_SOCKDBUGFILT_S;

/* UDP6 Debug filter*/
typedef struct tagUDP6_SOCKDBUGFILTRD
{
    UDP6_SOCKDBUGFILT_S stSockDbugFilt[UDP6_SOCK_MAXFILTNUM];
    ULONG          ulFiltCnt;       /* 当前过滤条件的个数 */
}UDP6_SOCKDBUGFILTRD_S;

#ifdef COMPILING_IR_IPV6_CORE
#pragma pack()
#endif

/*End point table avail node*/
typedef struct tagUDP6_ENDPT_TABLE_AVL_NODE
{
    IN6ADDR_S   stUdpEndptTabLocAddr;
    IN6ADDR_S   stUdpEndptTabRemAddr;
    USHORT      usUdpEndptTabLocPort;
    USHORT      usUdpEndptTabRemPort;
    ULONG       ulUdpEndptTabInstance;
    ULONG       ulUdpEndptTabProcess;
} UDP6_ENDPT_TABLE_AVL_NODE_S;

/*MIB return values*/
typedef struct tagUDP6_MIB_RETURN
{
    ULONG       ulUdpMibLocAddrType;
    IN6ADDR_S   stUdpMibLocAddr;
    ULONG       ulUdpMibLocPort;
    ULONG       ulUdpMibRemAddrType;
    IN6ADDR_S   stUdpMibRemAddr;
    ULONG       ulUdpMibRemPort;
    ULONG       ulUdpMibInstance;
    ULONG       ulUdpMibProcess;
} UDP6_MIB_RETURN_S;

#define UDP6_MIB_LOCAL_ADDR_TYPE    2
#define UDP6_MIB_REMOTE_ADDR_TYPE   2

/*MIB specific scalar object values*/
typedef struct tagUDP6_MibScalarStc
{
    ULONG ulUdp6InDatagrams;
    ULONG ulUdp6NoPorts;
    ULONG ulUdp6InErrors;
    ULONG ulUdp6OutDatagrams;
    DULONG dulUdp6HCInDatagrams;
    DULONG dulUdp6HCOutDatagrams;
} UDP6_MibScalarStc;

#define UDP6_MIB_IPV4_ADDR_TYPE    1


#ifdef  __cplusplus
}
#endif

#endif  /* _UDP6_PUBLIC_H*/


