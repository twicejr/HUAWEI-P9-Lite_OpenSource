/************************************************************************
 *
 *    Copyright 2003, Huawei Technologies Co. Ltd  India Institute  
 *                     ALL RIGHTS RESERVED                           
 *                                                 
 *----------------------------------------------------------------------*
 *
 *                             natpt_sh_def.h
 *
 *  Project Code:       VRPv5 
 *  Create Date:        2003-7-15
 *  Author:             keshava   (VRPv5 IPv6 Team) 
 *  Document:
 *  Function Description:
 *  
 *----------------------------------------------------------------------*
 *  Modification History 
 *  DATE        NAME             DESCRIPTION
 *  2003-11-13  Archaan P V       For Defect BYAD03928
 *  2003-12-24  Usha              For defect BYAD05918
 *  2003-01-12  Archana P V       For Defect BYAD06698 
 *  2004-01-19  Archana P V       For Defect BYAD06880 
 *  2004-02-13  Archana P V       For Defect BYAD08372
 ************************************************************************/



#ifndef _NATPT_SH_DEF_H
#define _NATPT_SH_DEF_H


#ifdef	__cplusplus
extern	"C"{
#endif


#define u6_addr32  u6_uladdr
/*----------------------------------------------*
 * Global Variables    
 *----------------------------------------------*/
#define NATPT_IF_TYPE (IF_FLAG_ETHERNET | IF_FLAG_SERIAL | IF_FLAG_ASYNC)

#define NATPT_MEMALLOC_FAILURE					0xffff
#define NATPT_INVALID_LONGVALUE						0xffffffff

/*for License CLI enable / disable*/
#define NATPT_DPAT_CHANGE_POS  0
#define NATPT_PAT_CHANGE_POS   1

/* Cmd signs which tell what commands are being executed */
#define NATPT_CMD_ENABLE                        1
#define NATPT_CMD_CONFADDRGRP                   2
#define NATPT_CMD_STATICIPV6IPV4                3
#define NATPT_CMD_STATICIPV4IPV6                4 
#define NATPT_CMD_DYNV6BOUND                    5
#define NATPT_CMD_DYNV4BOUND                    6
#define NATPT_CMD_PREFIX                        7
#define NATPT_CMD_CLEAR                         8
#define NATPT_CMD_SETMAXSESSION                 9
#define NATPT_CMD_DEBUG                         10
#define NATPT_CMD_DISPLAY                       11
#define NATPT_CMD_CONFAGEOUT                	12
#define NATPT_CMD_OPENSESSION					13
#define NATPT_CMD_CLOSESESSION					14
#define NATPT_CMD_DISPLAYSESS                   15
#define NATPT_CMD_DISPLAYSTATS                  16
#define NATPT_CMD_JOINMULTICAST                 17
#define NATPT_CMD_LEAVEMULTICAST                18  
/*Add for defect BYAD03928*/
#define NATPT_CMD_CLEARSTATS                    19
#define NATPT_CMD_TRAFCLASS                     20
/*add for defect BYAD06880*/
#define NATPT_CMD_OPENFRAG						21
#define NATPT_CMD_DISFRAG                       22

/* for defect BYAD11433 */
#define NATPT_CMD_ALLOWPRVADDRESS                  23
/* end of defect BYAD11433 */

/*Added for Defect BYAD06224*/
#define NATPT_MAX_CMD_SIZE                      130
#define NATPT_MAX_IF_CMD_SIZE                   30

/* defined for the Display types */
#define NATPT_SHOW_ALL                          1
#define NATPT_SHOW_ADDRGRP                      2
#define NATPT_SHOW_STATISTICS                   3
#define NATPT_SHOW_AGINGTIME                    4
#define NATPT_SHOW_SESSIONS                     5
#define NATPT_SHOW_ADDRMAPPING                  6
#define NATPT_SHOW_FRAG                         7

/* defined for the different debug */
#define NATPT_DEBUG_EVENT                       1
#define NATPT_DEBUG_PACKET                      2
#define NATPT_DEBUG_ALG                         3


#define NATPT_PAT                               1
#define NATPT_NOPAT                             0


#define NATPT_MINTIMEOUT						5/*Changed for defect BYAD08372*/
#define NATPT_MAXTIMEOUT						600

#define NATPT_MINSESSION						0
#define NATPT_MAXSESSION						50000

#define NATPT_MINADDRGRP						1
#define NATPT_MAXADDRGRP						31

#define NATPT_MINACLNO							1
#define NATPT_MAXACLNO							99

#define NATPT_MINPORT							1
#define NATPT_MAXPORT							65535

/* IPC timeout */
#define NATPT_IPC_TIMEOUT                       5000

#define NATPT_IS_ADDR_PRIVATE(ulAddr) (((ulAddr >= 0xA000000)&&(ulAddr <= 0xAFFFFFF))\
                                                                          ||((ulAddr >= 0xAC100000)&&(ulAddr <= 0xAC1FFFFF))\
                                                                          ||((ulAddr >= 0xC0A80000)&&(ulAddr <= 0xC0A8FFFF)))
#define NATPT_IS_IPV4_ADDR_LOOPBACK(ulAddr) ((ulAddr >= 0x7F000000)&&(ulAddr <= 0x7FFFFFFF))

#define MAX_GRP_SIZE  16 /* added  by Leon check this */



#define NATPT_MAX_LENGTH					32
/* 
 * V6Address must be a V6 address
 * return value: 
 *      1 -- V6Address is a link-local address
 *      0 -- V6Address isn't a link-local address
 */
#define NATPT_LIB6_IS_ADDRESS_LINKLOCAL( V6Address )    \
    ( 0xFE800000 == (0xFFC00000&((V6Address.u6_addr.u6_addr32[0])) ))

/* 
 * V6Address must be a v6 address
 * return value: 
 *      1 -- V6Address is a site-local address
 *      0 -- V6Address isn't a site-local address
 */
#define NATPT_LIB6_IS_ADDRESS_SITELOCAL( V6Address )    \
    ( 0xFEC00000 == (0xFFC00000&((V6Address.u6_addr.u6_addr32[0])) ))

/* 
 * V6Address must be a V6 address
 * return value: 
 *      1 -- V6Address is a multicast address
 *      0 -- V6Address isn't a multicast address
 */
#define NATPT_LIB6_IS_ADDRESS_MULTICAST( V6Address )    \
    ( 0xFF000000 == (0xFF000000&(V6Address.u6_addr.u6_addr32[0])) )

/* 
 * V6Address must be a V6 address 
 * return value: 
 *      1 -- V6Address is a loopback address
 *      0 -- V6Address isn't a loopback address
 */
#define NATPT_LIB6_IS_ADDRESS_LOOPBACK( V6Address )     \
    ( (0 == V6Address.u6_addr.u6_addr32[0]) \
     && (0 == V6Address.u6_addr.u6_addr32[1]) \
     && (0 == (V6Address.u6_addr.u6_addr32)[2]) \
     && (1 == V6Address.u6_addr.u6_addr32[3]) )

/* 
 * V6Address must be a valid IPV6 address
 * return value: 
 *      1 -- V6Address is a NULL address
 *      0 -- V6Address isn't a NULL address
 */
#define NATPT_LIB6_IS_ADDRESS_NULL( V6Address )         \
    ( (0 == V6Address.u6_addr.u6_addr32[0]) \
     && (0 == V6Address.u6_addr.u6_addr32[1]) \
     && (0 == V6Address.u6_addr.u6_addr32[2]) \
     && (0 == V6Address.u6_addr.u6_addr32[3]) )

#define NATPT_IS_ADDRESS_GLOBAL( pAddress )    \
    ( !((NATPT_LIB6_IS_ADDRESS_MULTICAST(pAddress))\
     ||(NATPT_LIB6_IS_ADDRESS_LOOPBACK(pAddress))\
     ||(NATPT_LIB6_IS_ADDRESS_SITELOCAL(pAddress))\
     ||(NATPT_LIB6_IS_ADDRESS_LINKLOCAL(pAddress))\
     ||(NATPT_LIB6_IS_ADDRESS_NULL(pAddress))) )
/* x must be a V6 address*/
#define NATPT_LIB6_ADDRESS_NTOH(x) \
        {\
           x.u6_addr.u6_addr32[0] = VOS_NTOHL(x.u6_addr.u6_addr32[0]);\
           x.u6_addr.u6_addr32[1] = VOS_NTOHL(x.u6_addr.u6_addr32[1]);\
           x.u6_addr.u6_addr32[2] = VOS_NTOHL(x.u6_addr.u6_addr32[2]);\
           x.u6_addr.u6_addr32[3] = VOS_NTOHL(x.u6_addr.u6_addr32[3]);\
        } 

/* x must be a V6 address*/
#define NATPT_LIB6_ADDRESS_HTON(x) \
        {\
           x.u6_addr.u6_addr32[0] = VOS_HTONL(x.u6_addr.u6_addr32[0]);\
           x.u6_addr.u6_addr32[1] = VOS_HTONL(x.u6_addr.u6_addr32[1]);\
           x.u6_addr.u6_addr32[2] = VOS_HTONL(x.u6_addr.u6_addr32[2]);\
           x.u6_addr.u6_addr32[3] = VOS_HTONL(x.u6_addr.u6_addr32[3]);\
        } 

/* Dest and Src must V6 Addresses*/
#define NATPT_LIB6_ADDRESS_COPY( Dest, Src )     \
    {\
        (Dest).u6_addr.u6_addr32[0] = (Src).u6_addr.u6_addr32[0] ;\
        (Dest).u6_addr.u6_addr32[1] = (Src).u6_addr.u6_addr32[1] ;\
        (Dest).u6_addr.u6_addr32[2] = (Src).u6_addr.u6_addr32[2] ;\
        (Dest).u6_addr.u6_addr32[3] = (Src).u6_addr.u6_addr32[3] ;\
    } 

/* x must be a V6 address*/
#define NATPT_LIB6_ADDRESS_ASSIGN_NTOH(x,y) \
        {\
           (x).u6_addr.u6_addr32[0] = VOS_NTOHL((y).u6_addr.u6_addr32[0]);\
           (x).u6_addr.u6_addr32[1] = VOS_NTOHL((y).u6_addr.u6_addr32[1]);\
           (x).u6_addr.u6_addr32[2] = VOS_NTOHL((y).u6_addr.u6_addr32[2]);\
           (x).u6_addr.u6_addr32[3] = VOS_NTOHL((y).u6_addr.u6_addr32[3]);\
        }
           
    
/* x must be a V6 address*/
#define NATPT_LIB6_ADDRESS_ASSIGN_HTON(x,y) \
        {\
           (x).u6_addr.u6_addr32[0] = VOS_HTONL((y).u6_addr.u6_addr32[0]);\
           (x).u6_addr.u6_addr32[1] = VOS_HTONL((y).u6_addr.u6_addr32[1]);\
           (x).u6_addr.u6_addr32[2] = VOS_HTONL((y).u6_addr.u6_addr32[2]);\
           (x).u6_addr.u6_addr32[3] = VOS_HTONL((y).u6_addr.u6_addr32[3]);\
        }

#define pNATPTInfo pNatPtInformation[g_ulExecInforIndex] /* For VRPV5 App Init */
/*#define pNATInfo pNatInformation[INF_SEC_NAT]*/
/* #define pNATPTInfo pNatPtInformation[INF_NATPT]  */

#define  SYSTRC_IPV6_NATPT_SH_BASE        6
#define NATPT_SHELL_INIT_TRACE  1 

#define NATPT_SHELL_CFG ((SYSTRC_IPV6_NATPT_SH_BASE << 8) + 12)
#define NATPT_HA_SHELL 1 


#ifndef MAKE_TRACE_ID    
#define MAKE_TRACE_ID(fileID)  fileID
#endif

/* Added by arvindsaproo for D19 Sync Version */
/* This macro is used to decide whether to install
   named acl part of "natpt v4bound dynamic..."
   command 
*/   
#define NATPT_NAMED_ACL_EXISTS    VRP_NO
/* End - Addition for D19 Sync Version */

enum enum_NATPT_Plan
 {
    NATPT_Plan0,
    NATPT_Plan1,
    NATPT_Plan2,        
	NATPT_Plan4,
	NATPT_Plan5,
	NATPT_Plan6,
	NATPT_Plan7,
	NATPT_Plan8,
	NATPT_Plan9,
	NATPT_Plan10,
	NATPT_Plan11,
	NATPT_Plan12,
	NATPT_Plan13,
	NATPT_Plan14,	
	NATPT_Plan16,
	NATPT_Plan17,
	NATPT_Plan18,
	NATPT_Plan19,
	NATPT_Plan20,
	NATPT_Plan21,
	NATPT_Plan22,
	NATPT_Plan23,
	NATPT_Plan24,
	NATPT_Plan25,
	NATPT_Plan26,
	NATPT_Plan27,
	NATPT_Plan28,
	NATPT_Plan30,
	NATPT_Plan31,
	NATPT_Plan33,
	NATPT_Plan34,
	NATPT_Plan35,
	NATPT_Plan36,	
	NATPT_Plan37,
	NATPT_Plan38,
	NATPT_Plan39,
	NATPT_Plan40,
	NATPT_Plan41,
	NATPT_Plan43,
	NATPT_Plan44,
	NATPT_Plan45,
	NATPT_Plan46,
	NATPT_Plan47,
	NATPT_Plan48,
	NATPT_Plan49,
	NATPT_Plan50,
	NATPT_Plan51,
	NATPT_Plan52,
	NATPT_Plan53,
	NATPT_Plan54,
	NATPT_Plan55,	
	NATPT_Plan59,
	NATPT_Plan60,
	NATPT_Plan61,
	NATPT_Plan62,
	NATPT_Plan63,
	NATPT_Plan64,	
	NATPT_Plan66,
	NATPT_Plan67,
	NATPT_Plan68,
	NATPT_Plan69,
	NATPT_Plan70,
	NATPT_Plan71,
	NATPT_Plan72,
	NATPT_Plan73,
	NATPT_Plan74,
	NATPT_Plan75,
	NATPT_Plan76,
	NATPT_Plan77,
	/*Add for Defect BYAD03928*/
	NATPT_Plan78,
	NATPT_Plan79,
    NATPT_Plan80,
    /* For defect BYAD04881 */
    NATPT_Plan81,
    NATPT_Plan82,
    NATPT_Plan83,
    /* End of defect BYAD04881 */
    /* for defect BYAD05918 */
    NATPT_Plan84,
    /* End of defect BYAD05918 */
	NATPT_Plan85,
	NATPT_Plan86,
	NATPT_Plan87,	
	NATPT_Plan88,	
	NATPT_Plan89,
	NATPT_Plan90,
	NATPT_Plan91,
    NATPT_Plan_MAX
};



typedef struct tagNATPT_StaticAddrV6V4bound{

    USHORT usCmdSign;
    USHORT usFlag;
    ULONG ulIpv4Addr;
    IN6ADDR_S stIpv6Addr;
    UCHAR ucAddrInfoFlag;
}NatPt_StaticAddrV6V4bound_S;

typedef struct tagNATPT_EnableNat
{
    USHORT usCmdSign;
    USHORT usFlag;
    ULONG ulIfIndex;
}NatPt_Enable_S;


typedef struct tagNATPT_StaticAddrV4V6bound{
    USHORT usCmdSign;
    USHORT usFlag;
    ULONG ulIpv4Addr;
    IN6ADDR_S stIpv6Addr;
    USHORT usIpv4Port;
    USHORT usIpv6Port;
    UCHAR ucProtocolType;
	UCHAR ucAddrInfoFlag;
} NatPt_StaticAddrV4V6bound_S;

typedef struct tagNATPT_TimeOut{
    USHORT usCmdSign;
    USHORT usReserved;
    ULONG ulTimerType;  
    ULONG ulTimeoutValue;
    }NatPt_Timeout_S;

typedef struct tagNATPT_setMaxSession{
    USHORT usCmdSign;
    USHORT usFlag;
    ULONG ulMaxSession;
}NatPt_SetMaxSession_S;

typedef struct tagNATPT_Debug
{
    USHORT       usCmdSign;
	USHORT		 usFlag;
	ULONG 		 ulIfIndex;
    UCHAR        ucDebugSign;  
}NatPt_Cmd_Debug_S;

/* for defect BYAD04881 */
typedef struct tagNATPT_TraffClass
{
    USHORT       usCmdSign;
	USHORT		 usFlag;
	UCHAR        ucTrafFlag;
}NatPt_Cmd_TraffClass_S;
/* end of defect BYAD04881 */

typedef struct tagNATPT_ConfAddrGrp
{
    USHORT  usCmdSign;
    USHORT  usFlag;
    USHORT   usGroupNumber;
    USHORT usReserv;
    ULONG   ulStartIpv4Addr;
    ULONG   ulEndIpv4Addr;
}NatPt_Cmd_ConfAddrGrp_S;

typedef struct tagNATPT_DynV6Bound
{
    USHORT usCmdSign;
    USHORT usFlag;
    IN6ADDR_S stPrefix;
    USHORT usAddrGrpNo;
	USHORT usPATFlag;
	ULONG ulIfIndex;
	ULONG ulAclNo;
	ULONG ulMappingType;
    ULONG ulIfV4Addr;
    CHAR szAclName[IF_MAX_INTERFACE_NAME_LEN +1];
    CHAR szIfName[IF_MAX_INTERFACE_NAME_LEN +1];

}NatPt_Cmd_DynV6Bound_S;

typedef struct tagNATPT_DynV4Bound
{
    USHORT usCmdSign;
    USHORT usFlag;
    IN6ADDR_S stPrefix;
    ULONG ulAclNo;
	ULONG ulMappingType;
    CHAR szAclName[IF_MAX_INTERFACE_NAME_LEN +1];
}NatPt_Cmd_DynV4Bound_S;

typedef struct tagNATPT_Prefix
{
    USHORT usCmdSign;
    USHORT usFlag;
    IN6ADDR_S stPrefix;
    ULONG ulIfIndex;
    ULONG ulNxtHopAddr;
    ULONG ulPrefixType;
    CHAR szIfName[IF_MAX_INTERFACE_NAME_LEN +1];
}NatPt_Cmd_Prefix_S;
typedef struct tagNATPT_Clear
{
    USHORT usCmdSign;
    USHORT usReserv;
}NatPt_Cmd_Clear_S;

typedef struct tagNATPT_OpenSess
{
    USHORT usCmdSign;
    USHORT usReserv;
	ULONG ulWaitListId;
	ULONG ulIndex;
}NatPt_OpenSess_S;
typedef struct tagNATPT_CloseSess
{
    USHORT usCmdSign;
    USHORT usReserv;
	ULONG ulWaitListId;
}NatPt_CloseSess_S;

/* for defect BYAD11433 */
typedef struct tagNATPT_AllowPrvAddr
{
    USHORT usCmdSign;
    USHORT usFlag;
}NatPt_Cmd_AllowPrvAddress;
/* end of defect BYAD11433 */

#ifdef	__cplusplus
}
#endif

#endif
