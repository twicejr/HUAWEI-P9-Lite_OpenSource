


#ifndef _NATPT_PUB_H
#define _NATPT_PUB_H


#ifdef  __cplusplus
extern  "C"{
#endif


/*----------------------------------------------*
 * External Variables            
 *----------------------------------------------*/
#define IP_FIB_AllocValid_VAL 1
#define ACL_PacketFilterWithParam_VAL 2
#define IP_Output_VAL 3
#define ICMP_Error_VAL 4 
#define NATPT_Join_Multicast_VAL 6
#define NATPT_Leave_Multicast_VAL 7
#define NATPT_SendToIPC_VAL 8 
#define NATPT_MBUF_TR_Send_VAL 9
#define NATPT_Multicast_VAL 10
#define NATPT_DebugToIC_VAL 11
#define NATPT_HASetBackupData_VAL 12
#define NATPT_Create_Timer_VAL 13
#define NATPT_Delete_Timer_VAL 14   
#define NATPT_SendToIO_VAL 15
#define NATPT_IS_HA_ENABLE_VAL 16
#define NATPT_RT_BACKUP_SEND_VAL 17
#define NATPT_HA_BatchBackupSend_VAL 18
#define NATPT_getMainboardId_VAL 19
#define NATPT_Shell_HA_MemAllocate_VAL 20




#define NATPT_SYNC 4
#define NATPT_ASYNC 0
#define NATPT_MULTICAST_FLAG 0x00000010
#define NATPT_MAX_NONCOMP_REG_INDEX 100 

#define MAX_IFINDEX_NUM                        20


/* ---------------------------------------------------------
(BYAD05484)
acl_pub.h/acl6_pub.h define 33 as the maximum length of the 
ACL name string. Can't use those macro's here because it 
will lead to whole lot of complilation dependency.Also, NATPT 
code requires the string to be 4 Byte aligned. Hence,defining
the following macro.
Pls note that the code allocates a string of size 
[MAX_ACL_NAME_LEN + 1] which makes it 4 Byte aligned
-----------------------------------------------------------*/
   
#define MAX_ACL_NAME_LEN                       35  

#define IF_MAX_INTERFACE_NAME_LEN                 47
#define NATPT_TCP_FTP_PORT  21/*F*P server port fpr ctrl commands*/ 

#define NATPT_SET_DBGPKT                   0x0001
#define NATPT_SET_DBGEVENT                 0x0002
#define NATPT_SET_DBGALG                   0x0004 
  /* For defect BYAD05918 */
#define NATPT_SET_DBGALL                   0x0040

#define NATPT_SET_INTFDBGPKT               0x0008
#define NATPT_SET_INTFDBGEVENT             0x0010
#define NATPT_SET_INTFDBGALG               0x0020 

/* Natpt Debug Flag */
#define NATPT_SET_DBGFLAG(ucDebug,ucFlag) (ucDebug |= ucFlag)
#define NATPT_RESET_DBGFLAG(ucDebug,ucFlag) (ucDebug &= (~ucFlag))
/* to check if debug flag is set */
#define NATPT_IS_DBGFLAG(ucDebug,ucFlag) (ucDebug & ucFlag)

#define NATPT_IS_DBGFLAG_SET(ucDebug,ucFlag)   (ucDebug & ucFlag)


#define NATPT_IS_DEBUGPKTFLAG_SET(ucDbgPkt)(ucDbgPkt & NATPT_SET_DBGPKT)
#define NATPT_IS_DEBUGEVTFLAG_SET(ucEvtPkt)(ucEvtPkt & NATPT_SET_DBGEVENT)
#define NATPT_IS_DEBUGALGFLAG_SET(ucAlgPkt)(ucAlgPkt & NATPT_SET_DBGALG)
#define NATPT_SET_DEBUGPKTFLAG(ucDbgPkt)(ucDbgPkt |= NATPT_SET_DBGPKT)
#define NATPT_SET_DEBUGEVTFLAG(ucEvtPkt)(ucEvtPkt |= NATPT_SET_DBGEVENT)
#define NATPT_SET_DEBUGALGFLAG(ucAlgPkt)(ucAlgPkt |= NATPT_SET_DBGALG)


#define NATPT_IF_DEBUGEVENTON(pstIf)\
    ((((NATPTIF_S *)pstIf->if_pstNatpt)->usDebugFlag & NATPT_SET_DBGEVENT)\
     ||(NATPT_IS_DEBUGEVTFLAG_SET(g_ucNatptDebugFlag))) 
#define NATPT_IF_DEBUGPKTON(pstIf)\
    ((((NATPTIF_S *)pstIf->if_pstNatpt)->usDebugFlag & NATPT_SET_DBGPKT)\
     ||(NATPT_IS_DEBUGPKTFLAG_SET(g_ucNatptDebugFlag))) 
#define NATPT_IF_DEBUGALGON(pstIf)\
    ((((NATPTIF_S *)pstIf->if_pstNatpt)->usDebugFlag & NATPT_SET_DBGALG)\
     ||(NATPT_IS_DEBUGALGFLAG_SET(g_ucNatptDebugFlag))) 


#define NATPT_STATIC_BIT 1
#define NATPT_DNS_BIT  2
#define NATPT_SOURCE_DEST_BIT 4
#define NATPT_VALID_PORT_BIT 8 /*If this bit is not set the port passed is invalid*/
#define NATPT_SADDR_BIT 128
#define NATPT_DADDR_BIT 64
#define NATPT_PAT_BIT 32
#define NATPT_FINRST_BIT 16
#define NATPT_OLD_BIT    8
#define NATPT_V4DIR_BIT 4

#define NATPT_SET_STATIC(ucFlag) (ucFlag |= NATPT_STATIC_BIT)
#define NATPT_SET_DYNAMIC(ucFlag) (ucFlag &= (~(NATPT_STATIC_BIT)))
#define NATPT_SET_DNS(ucFlag) (ucFlag |= NATPT_DNS_BIT)
#define NATPT_SET_V4SOURCE(ucFlag) (ucFlag |= NATPT_SOURCE_DEST_BIT)
#define NATPT_SET_V4DEST(ucFlag) ( ucFlag &= (~(NATPT_SOURCE_DEST_BIT)))
#define NATPT_SET_PAT(ucFlag)(ucFlag |= NATPT_PAT_BIT)
#define NATPT_SET_SADDR_COUNT(ucFlag)  (ucFlag |= NATPT_SADDR_BIT)
#define NATPT_SET_DADDR_COUNT(ucFlag)  (ucFlag |= NATPT_DADDR_BIT)
#define NATPT_SET_FINFLAG(ucFlag) (ucFlag |= NATPT_FINRST_BIT)
#define NATPT_SET_OLDFLAG(ucFlag) (ucFlag |= NATPT_OLD_BIT)
/*added for defect BYAD04519*/
#define NATPT_SET_V4DIR(ucFlag) (ucFlag |= NATPT_V4DIR_BIT)
#define NATPT_SET_VALID_PORT(ucFlag) (ucFlag |= NATPT_VALID_PORT_BIT)
#define NATPT_RESET_VALID_PORT(ucFlag) (ucFlag &= (~(NATPT_VALID_PORT_BIT)))

#define NATPT_IS_STATIC(ucFlag) (ucFlag & NATPT_STATIC_BIT)
#define NATPT_IS_DYNAMIC(ucFlag) (!(ucFlag & NATPT_STATIC_BIT))
#define NATPT_IS_DNS(ucFlag) (ucFlag & NATPT_DNS_BIT)
#define NATPT_IS_V4SOURCE(ucFlag) (ucFlag & NATPT_SOURCE_DEST_BIT)
#define NATPT_IS_V4DEST(ucFlag) (!(ucFlag & NATPT_SOURCE_DEST_BIT))
#define NATPT_IS_PAT(ucFlag) (ucFlag & NATPT_PAT_BIT)
#define NATPT_IS_SADDR_COUNT(ucFlag) (ucFlag & NATPT_SADDR_BIT)
#define NATPT_IS_DADDR_COUNT(ucFlag) (ucFlag & NATPT_DADDR_BIT)
#define NATPT_IS_FIN_SET(ucFlag) (ucFlag & NATPT_FINRST_BIT)
#define NATPT_IS_OLD(ucFlag) (ucFlag & NATPT_OLD_BIT)
/*added for defect BYAD04519*/
#define NATPT_IS_V4DIR(ucFlag) (ucFlag & NATPT_V4DIR_BIT)
#define NATPT_IS_PORT_VALID(ucFlag)  (ucFlag & NATPT_VALID_PORT_BIT)

#define NATPT_ACL6_NUMBER_TO_ADDRGRP    1
#define NATPT_ACL6_NUMBER_TO_INTERFACE  2

#define NATPT_ACL6_NAME_TO_ADDRGRP      4
#define NATPT_ACL6_NAME_TO_INTERFACE    8

#define NATPT_V6PREFIX_TO_ADDRGRP      16
#define NATPT_V6PREFIX_TO_INTERFACE    32

#define NATPT_GLOBAL_PREFIX             64
#define NATPT_INTERFACE_PREFIX         128  
#define NATPT_INTERFACE_PREFIX_WITH_NEXT_HOP   256

#define NATPT_ACL_NUM_TO_PREFIX          512
#define NATPT_ACL_NAME_TO_PREFIX        1024  
#define NATPT_MAX_DIS_SIZE  40         /*No of session mappings obtained at each request*/
#define NATPT_MAX_ADDRMAP_DIS_SIZE  10 /*No of address mapppings obtained at each request*/

#define NATPT_FAC              0x200
#define NATPT_ALG              0x201
#define NATPT_DNS_ALG      0x202
#define NATPT_ALG_ICMP    0x203
#define NATPT_CORE_INIT   0x204
#define NATPT_COM              0x205  
#define NATPT_SHELL_LCS   0x206
#define NATPT_HA_CORE      0x207
#define NATPT_AAM          0x208
#define NATPT_ALG_FTP      0x209


#define NATPT_IS_ADDR_PRIVATE(ulAddr) (((ulAddr >= 0xA000000)&&(ulAddr <= 0xAFFFFFF))\
                                                                          ||((ulAddr >= 0xAC100000)&&(ulAddr <= 0xAC1FFFFF))\
                                                                          ||((ulAddr >= 0xC0A80000)&&(ulAddr <= 0xC0A8FFFF)))
#define NATPT_IS_IPV4_ADDR_LOOPBACK(ulAddr) ((ulAddr >= 0x7F000000)&&(ulAddr <= 0x7FFFFFFF))


#define NATPT_AAM_ADDRGRP_DOWNLOAD_UNIT  32
#define NATPT_AAM_V6ACCESS_DOWNLOAD_UNIT 7
#define NATPT_AAM_PREFIX_DOWNLOAD_UNIT   10
#define NATPT_AAM_V4ACCESS_DOWNLOAD_UNIT 12


/* defined to indicate whether Enable or Undo operation */
#define NATPT_UNDO                              0
#define NATPT_ENABLE                       0x0001          /* Flag to indicate Natpt enable */
#define NATPT_DISENABLE                    0x0000          /* Flag to indicate undo natpt enable */ 





#define NATPT_TRAFFICCLASS                0x01     
#define NATPT_TOS                         0x02

#define NATPT_SET_TRAFFICCLASS(ucTrafFlag)(ucTrafFlag |= NATPT_TRAFFICCLASS)
#define NATPT_SET_TOS(ucTrafFlag) (ucTrafFlag |= NATPT_TOS)

#define NATPT_RESET_TRAFFICCLASS(ucTrafFlag) (ucTrafFlag &= (~(NATPT_TRAFFICCLASS)))
#define NATPT_RESET_TOS(ucTrafFlag)(ucTrafFlag &= (~(NATPT_TOS)))

#define NATPT_IS_TRAFFICCLASS_SET(ucTrafFlag) (ucTrafFlag & NATPT_TRAFFICCLASS)
#define NATPT_IS_TOS_SET(ucTrafFlag) (ucTrafFlag & NATPT_TOS)
/* End of defect BYAD04881 */

   

/* The Defined values for the timout entities */
#define NATPT_TCP                               6
#define NATPT_UDP                               17
#define NATPT_ICMP                              1
#define NATPT_ICMPV6                            58/*Add for defect BYAD01596*/
#define NATPT_DNS                               4
#define NATPT_SYN                               5
#define NATPT_FINRST                            9
#define NATPT_FRAG                              7
#define NATPT_DEFAULTTIME                       8

/*Added for Defect BYAD06698*/
#define NATPT_ALLSESS                           100 /*To indicate display all sessions*/
 
#define NATPT_BASE_PORT                  12288

/*Maximum number of address mappings that can be packed into one download message*/
#define NATPT_MAX_ADDRMAP_DOWNLOAD  40

/*Maximum number of DPAT mappings that can be packed into one download message*/      
#define NATPT_MAX_DPAT_DOWNLOAD     20
#define NATPT_TIMER_VALUE         1000/* Added by Desh */
#define NATPT_TCPTIMEOUT          86400/*Modified for defect BYAD03058*/
#define NATPT_UDPTIMEOUT          40
#define NATPT_ICMPTIMEOUT         20
#define NATPT_SYNTIMEOUT          240/*check this */   
#define NATPT_FIN_RSTTIMEOUT      5
#define NATPT_DNSTIMEOUT          10
#define NATPT_FRAGTIMEOUT         5
#define NATPT_DEFAULTTIMEOUT      5

#define NATPT_IP_ADD              0x1
#define NATPT_IP_DEL              0x2

#define NATPT_TRUE 1 
#define NATPT_FALSE 0 

#define NATPT_V4PKT_HANDLED               0x00000001     /* This flag is set in Mbuf after the pkt is translated and
                                                              before sending to stack */
#define NATPT_V4PKT_TRANSLATED            0x00000002      /* This flag indicates that the pkt is translated */                                                              
#define NATPT_V6PKT_HANDLED               0x00000004     /* This flag is set in Mbuf after the pkt is translated and
                                                              before sending to stack */                                                              
#define NATPT_V6PKT_TRANSLATED            0x00000008      /* This flag indicates that the pkt is translated */
#define NATPT_V6PKT_FRAGHDRADDED          0x00000010     /* Indicates that NATPT has added the Fragment Header to the translated IPv6 p/k (BYAD04518) */

/* used in ICMP_Error */
#define MBUF_SET_NATPT_FLAG(pstMbuf, ulFlag)(pstMbuf->stUserTagData.ulNatPtFlag |= ulFlag)
#define MBUF_GET_NATPT_FLAG(pstMbuf)(pstMbuf->stUserTagData.ulNatPtFlag)
#define MBUF_IS_NATPT_FLAG_SET(pstMbuf, ulFlag)(pstMbuf->stUserTagData.ulNatPtFlag & ulFlag )   


/*----------------------------------------------*
 * Type Define    
 *----------------------------------------------*/

typedef struct tagV4PseudoHdr_S
{
    ULONG  ulV4SAddr;
    ULONG  ulV4DAddr;
    UCHAR  ucReserved;
    UCHAR  ucProtocol;
    USHORT usLength;
}NATPT_V4PSEUDOHDR_S;

typedef struct tagV6PseudoHdr_S
{
    IN6ADDR_S stV6DAddr;
    IN6ADDR_S stV6SAddr;
    ULONG ulLength;
    UCHAR ucZero[3];
    UCHAR  ucNextHdr;  
}NATPT_V6PSEUDOHDR_S;


/* For defect BYAD07830 */
typedef struct tagNatptDownLoadIntf_S
{
    USHORT usCmdSign;
    USHORT usCount;
    ULONG  ulIfIndex[MAX_IFINDEX_NUM];
    UCHAR  ucDebugFlag;
    UCHAR  szReserved[3];
}NATPT_DOWNLOAD_INTF_S;
/* end of defect BYAD07830 */

/* for defect BYAD04881 */
typedef struct tagNatptDownLoadTrafClass_S
{
    USHORT usCmdSign;
    UCHAR  ucTraffFlag;
}NATPT_DOWNLOAD_TRAFCLASS_S;
/* end of defect BYAD04881 */

/* Structure of natpt enable list.*/
typedef struct tagNatptIndexList_S
{
    struct tagNatptIndexList_S *pstNextIndex;
    ULONG ulIfIndex;
}NATPT_INDEXLIST_S;

/* Structure of natpt enable list by slot. This structure is maintained only
   on the main board(in dist arch) and in centralized arch */
typedef struct tagNatptEnableBySlot_S
{
    struct tagNatptEnableBySlot_S *pstNextSlot;
    NATPT_INDEXLIST_S *pstIntfIndex;
    ULONG ulSlotNum;
    USHORT usIntfCount;
}NATPT_ENABLEBYSLOT_S;

/*structure for session mapping */
typedef struct tagNATPT_Hash_Session
{
    USHORT usV4SPort; 
    USHORT usV6SPort;
    USHORT usV4DPort;
    USHORT usV6DPort;
    ULONG ulV4SAddr;
    IN6ADDR_S stV6SAddr;
    ULONG ulV4DAddr;
    IN6ADDR_S stV6DAddr;
    ULONG ulDeadTime;
    struct tagNATPT_Hash_Session* pstV4Next;
    struct tagNATPT_Hash_Session* pstV6Next;
    UCHAR ucFlag;
    UCHAR ucPro;
    USHORT usReserved;/*For 4 byte allignment*/
    VOID* pExtData;/*Add for F*P-ALG support*/
}NATPT_HASH_SESSION_S;


/*Added for F*P-ALG support by Archana PV (70282)*/

typedef  struct  tagNatptHashSeq
{
    LONG lV4Offset;
    LONG lV6Offset;
} NATPT_HASHSEQ_S;



typedef struct  tagNATPT_Timeout
{
    ULONG ulTcp;
    ULONG ulUdp;
    ULONG ulIcmp;
    ULONG ulDns;
    ULONG ulSyn;
    ULONG ulFinRst;
    ULONG ulFrag;
    ULONG ulDefault;
}NATPT_TIMEOUT_S;


/*structure for address mapping */
typedef struct tagNATPT_Hash_AddrMap
{
    ULONG ulV4Addr;
    IN6ADDR_S stV6Addr;
    ULONG ulCount;
    ULONG ulAgeOut;
    struct tagNATPT_Hash_AddrMap* pstV4MapNext;
    struct tagNATPT_Hash_AddrMap* pstV6MapNext;
    UCHAR ucFlag;
    UCHAR szReserved[3]; /* BYAD06193 - Align to 4 byte boundary */
}NATPT_HASH_ADDRMAP_S;


/*structure for DPAT mapping*/
typedef struct tagNATPT_Hash_DPAT
{
    USHORT usV4DPort;
    USHORT usV6DPort;
    ULONG ulV4DAddr;
    IN6ADDR_S stV6DAddr;
    struct tagNATPT_Hash_DPAT* pstV4DPATNext;
    struct tagNATPT_Hash_DPAT* pstV6DPATNext;
    UCHAR ucProtocol;
    UCHAR szReserved[3]; /* BYAD06193 - Align to 4 byte boundary */
}NATPT_HASH_DPAT_S;

/*structure for fragmentation mapping*/
typedef struct tagNATPT_Hash_FRAG
{
    ULONG ulV4SAddr;
    IN6ADDR_S stV6SAddr;
    ULONG ulV4DAddr;
    IN6ADDR_S stV6DAddr;
    ULONG ulDeadTime;
    struct tagNATPT_Hash_FRAG * pNext;
    ULONG ulPacketID;
    MBUF_S *pstFirstMBuf;
    UCHAR ucFlag;
    UCHAR szReserved[3];
}NATPT_HASH_FRAG_S;

typedef struct tagNATPT_SMStats
{
    ULONG ulActiveSession;
    ULONG ulDeadSession;
    ULONG ulHits;
    ULONG ulMisses;
    /*For Defect BYAD04227*/
    ULONG ulActiveFragSession;
    ULONG ulDeadFragSession;
    ULONG ulFragHits;
    ULONG ulFragMisses;
}NATPT_SM_STATS_S;


typedef struct tagNATPT_AddrGrp
{
    ULONG ulStartAddr; 
    ULONG ulEndAddr;  
    struct tagNATPT_AddrGrp *pstNextAG; 
    USHORT usAdressGroupNo; 
} NATPTAddrGroupIndex_S;

typedef union tagNATPT_V6AclOrPrefix
{
    ULONG ulListNum;
    CHAR szListName[MAX_ACL_NAME_LEN + 1];
    IN6ADDR_S stNatPtPrefix;
} NATPTv6AclOrPrefix_U;


typedef struct tagNATPT_V6Access
{
    NATPTv6AclOrPrefix_U unAclOrPrefix;
    ULONG ulStartAddr;
    ULONG ulEndAddr;
    USHORT usPoolNo;
    USHORT usIsPAT;
    ULONG ulIfIndex;
    ULONG ulMappingType;    
    struct tagNATPT_V6Access *pstNext;    
    CHAR szInterfaceName[IF_MAX_INTERFACE_NAME_LEN +1];
} NATPTv6Access_S;


typedef struct tagNATPT_V4Access
{
    ULONG ulListNum;
    ULONG ulMappingType;
    IN6ADDR_S stNatPtPrefix;
    struct tagNATPT_V4Access *pstNext;
    CHAR szListName[MAX_ACL_NAME_LEN + 1];
} NATPTv4Access_S;

typedef struct tagNATPT_PrefixInfo
{
    IN6ADDR_S stNatPtPrefix;
    ULONG ulNextHopAddr;
    ULONG ulPrefixType;
    ULONG ulIfIndex;
    struct tagNATPT_PrefixInfo *pstNext;
    CHAR szInterfaceName[IF_MAX_INTERFACE_NAME_LEN +1];
} NATPTPrefixInfo_S;

typedef    struct tagNATPT_MOD_INFO_S
{
    ULONG ulModuleID;
}NATPT_MOD_INFO_S;

typedef struct tagNATPT_OneAddrInfo
{
    ULONG  ulV4Addr;
    IN6ADDR_S stV6Addr;
    ULONG ulFlag;
}NATPT_ONEADDR_INFO_S;


typedef  struct tagNATPT_OneDpatInfo
{
    USHORT usV4Dport;
    USHORT usV6Dport;
    ULONG  ulV4DAddr;
    IN6ADDR_S stV6DAddr;
    USHORT usPro;/*should this be made USHORT*/
    USHORT usReserved;
} NATPT_ONEDPAT_INFO_S;


typedef struct tagNATPT_DownloadAllAddrInfo
{
    USHORT usCmdSign;
    USHORT  usNumAddrMap;
    NATPT_ONEADDR_INFO_S aAddrMapInfo[NATPT_MAX_ADDRMAP_DOWNLOAD];
}NATPT_DOWNLOAD_ADDRINFO_S;

typedef struct tagNATPT_DownloadDPATINFO
{
    USHORT     usCmdSign;
    USHORT    usNumAddrMap;
    NATPT_ONEDPAT_INFO_S aDPATnfo[NATPT_MAX_DPAT_DOWNLOAD];
}NATPT_DOWNLOAD_DPATINFO_S;
 
typedef struct tagNATPT_SendPoolNumAndV6SAddr
{
    USHORT usCmdSign;
    USHORT usPoolNum;
    IN6ADDR_S stV6SrcAddr;
    UCHAR ucIsDNS;
} NATPTSendPoolNumAndV6SAddr_S;

typedef struct tagNATPT_RcvFreeV4Addr
{
    ULONG ulRetStatus;
    ULONG ulFreeV4Addr;
} NATPTRcvFreeV4Addr_S;

typedef struct tagNATPT_MMCommon
{
    USHORT usCmdsign;
    USHORT usFlag;
    ULONG ulV4Addr;
    IN6ADDR_S stV6Addr;
}NATPT_MM_COMMON_S;

typedef struct tagNATPT_NotifyAddrChange
{
    USHORT usCmdSign;
    USHORT usEvent;
    ULONG  ulIfIndex;
    ULONG  ulNewV4Addr;
} NATPTNotifyAddrChange_S;

/* added for IPC */
typedef struct tagNATPT_DISSESS
{
    USHORT usCmdSign;
    USHORT usReserv;
    ULONG ulWaitListId;     
    ULONG ulNoOfEntryWnted;
    ULONG ulNoOfEntryRtn;
    ULONG ulPro;
    NATPT_HASH_SESSION_S stSessionBuffer[NATPT_MAX_DIS_SIZE];
}NatPt_Display_Sess_S;

/*Added for Defect BYAD06880*/
typedef struct tagNATPT_DISFRAG
{
    USHORT usCmdSign;
    USHORT usReserv;
    ULONG ulWaitListId;     
    ULONG ulNoOfEntryWnted;
    ULONG ulNoOfEntryRtn;
    NATPT_HASH_FRAG_S stFragBuffer[NATPT_MAX_DIS_SIZE];
}NatPt_Display_Frag_S;

typedef struct tagNATPT_DisplayStat
{
    USHORT usCmdSign;
    USHORT usReserv;
    NATPT_SM_STATS_S stStats;
    
}NatPt_DisplayStat_S;

typedef struct tagNATPT_Download_SessionInfo
{
    USHORT usCmdSign;          
    USHORT usReserved;    
    ULONG ulTcp;
    ULONG ulUdp;
    ULONG ulIcmp;
    ULONG ulDns;
    ULONG ulSyn;
    ULONG ulFinRst;
    ULONG ulFrag;
    ULONG ulMaxSession;
    ULONG ulConfigState;/*Whether configured by the user or not*/
} NATPT_DOWNLOAD_SESSIONINFO_S;

/*Moved from natpt_core.c*/
typedef  struct tagNATPT_LCS_INFO_S
{
   SPECS_RES_VALUE_S  MAX_ADDR_MAP;
   SPECS_RES_VALUE_S  MAX_SESSIONS;
   SPECS_RES_VALUE_S  MAX_DPAT_MAP;
   SPECS_FUN_VALUE_S  PAT;
   SPECS_FUN_VALUE_S  DPAT ;
} NATPT_LCS_INFO_S;

typedef VOID (*PFNATPT_TIMER_FUNC)(VOID *);

typedef  struct  tagNATPT_NonCompINT_S
{
    ULONG (*pfIP_FIB_AllocValid)(ROUTE_S *pRo );
    VOID  (*pfACL_PacketFilterWithParam)(UCHAR protocol, ULONG ulListNumber,
                                         ULONG srcaddr, ULONG dstaddr, ULONG *iRet); 
    ULONG (*pfACL_PacketFilterWithParamByName)(UCHAR protocol, 
                                               CHAR *szListName, ULONG srcaddr,
                                               ULONG dstaddr,ULONG *iRet); 
    ULONG (*pfIP_Output)(MBUF_S *pstMBuf, MBUF_S *pstMOpt, ROUTE_S *pstRo, 
                         LONG lFlags, IPMOPTIONS_S *pstIpMo);
    VOID  (*pfICMP_Error)(MBUF_S *pstMBuf, LONG ltype, LONG lcode, 
                          ULONG ulnlDest, IFNET_S *pstIfNet ); 
  /*  ULONG (*pfNATPT_HASetBackupData)(UCHAR *pucData , ULONG ulLength); */
    ULONG (*pfNATPT_HA_RTBackupSend)(UCHAR *, ULONG);
    ULONG (*pfNATPT_HA_BatchBackupSend)(UCHAR* pucData, ULONG ulLength);
    VOID* (*pfNATPT_Shell_HA_MemAllocate)(ULONG ulPayloadSize);
    ULONG (*pfNATPT_Shell_HA_MemFree) (VOID* pData);
    ULONG (*pfNATPT_getMainboardId)();  
    ULONG (*pfNATPT_Join_Multicast)(ULONG ulNode);
    ULONG (*pfNATPT_Leave_Multicast)(ULONG ulNode);
    ULONG (*pfNATPT_SendToIPC)(UCHAR* pucData, ULONG ulLength, ULONG ulNode, 
                             ULONG ulMode, UCHAR* pucRecv, ULONG ulRecvlength);
    ULONG (*pfNATPT_MBUF_TR_Send)(MBUF_S* pstMbuf, ULONG ulNode,
                                  ULONG ulAttachMessage);
    ULONG (*pfNATPT_Multicast)(UCHAR* pucData,ULONG ulLength, ULONG ulMode, 
                               UCHAR* pucRecv, ULONG ulRecvlength);
    /* 
    Commented out by arvindsaproo for NATPT Over Tunnel Support.
    Was getting compilation errror because of this prototype...
    replaced it by the one following it.
    ULONG (*pfNATPT_Create_Timer)(VOID (*pfTimerFunc)(VOID *), ULONG *);
    */
    ULONG (*pfNATPT_Create_Timer)(PFNATPT_TIMER_FUNC pfTimerFunc, ULONG *pulRetTimerID);
    /* End - Modification for NATPT Over Tunnel Support */
    
    ULONG (*pfNATPT_Delete_Timer)(ULONG );
    VOID  (*pfNATPT_DebugToIC)(CHAR *szString, ULONG ulLevel);
    ULONG (*pfNATPT_Is_Ha_Enable)();  
    /*Added for Defect BYAD05088*/
    ULONG (*pfNATPT_Sh_SetLcsAvailValue)(CHAR* szLcsKey, ULONG ulAvailValue);

} NATPT_NonCompINT_S;



/*----------------------------------------------*
 * NATPT help & Error information's index:    
 *----------------------------------------------*/
enum enumNATPTLCSEvent
{
    NATPT_LCS_UPDATE_DISABLE,
    NATPT_LCS_UPDATE_ENABLE
};

enum enumNATPTInfo
{
    /* Help Info of Addr Grp */
    Help_NATPT_ADDRGRPINFOR = 0,
    Help_NATPT_NOADDRGRP,    
    Help_NATPT_NATADDRGRPIS,  
    Help_NATPT_DYNV6ADDRGRPINFOR,
    Help_NATPT_DYNACLADDRGRPINFORNP,
    Help_NATPT_DYNACLADDRGRPINFORP,
    Help_NATPT_DYNACLNADDRGRPINFORNP,
    Help_NATPT_DYNACLNADDRGRPINFORP,
    Help_NATPT_DYNPREFIXADDRGRPINFORP,
    Help_NATPT_DYNPREFIXADDRGRPINFORNP,
    Help_NATPT_DYNPREFIXIFADDRGRPINFOR,
    Help_NATPT_DYNACLIFINFOR,
    Help_NATPT_DYNACLNIFINFOR,
    Help_NATPT_NODYNV6ADDRGRP,
    Help_NATPT_DYNV4ADDRGRPINFOR,
    Help_NATPT_DYNV4ACLPREFIXINFOR,
    Help_NATPT_DYNV4ACLNPREFIXINFOR,
    Help_NATPT_NODYNV4ADDRGRP,

    /* prefix Info */
    Help_NATPT_PREFIXPROMPT,
    Help_NATPT_PREFIXSUBPROMPT,
    Help_NATPT_GPREFIXINFO,
    Help_NATPT_INTPREFIXINFO,
    Help_NATPT_INTNHPREFIXINFO,
    
    /* Help for timeout cmd */
    Help_NATPT_TIMEINFOR,
    Help_NATPT_TIMEOUTIS,  
    Help_NATPT_STATSINFOR,
    Help_NATPT_STATSINTINFOR,
    Help_NATPT_ADDRMAPV6STATICPROMPT,
/*    Help_NATPT_ADDRMAPV6STATICSUBPROMPT,*/
    Help_NATPT_ADDRMAPV6SUBPROMPT,
    Help_NATPT_ADDRMAPV6STATICINFOR,
/*    Help_NATPT_ADDRMAPV6PROMPT,
    Help_NATPT_ADDRMAPV6SUBPROMPT,
    Help_NATPT_ADDRMAPV6INFOR,*/
    Help_NATPT_ADDRMAPV4PROMPT,
    Help_NATPT_ADDRMAPV4SUBPROMPT,
    Help_NATPT_ADDRMAPV4INFOR,
    Help_NATPT_SESSMAPPROMPT,
    Help_NATPT_SESSMAPSUBPROMPT,
    Help_NATPT_SESSMAPINFOR,
    Help_NATPT_FRAGMAPPROMPT,
    Help_NATPT_FRAGMAPSUBPROMPT,
    Help_NATPT_FRAGMAPINFOR,
    
    /*Added for Defect BYAD04473*/
    NATPT_SUCCESS_UNDO,
    /* Error codes w.r.t Address Pool Configuration*/   
    NATPT_ERR_AAM_POOL_NOTEXIST,
    NATPT_ERR_AAM_POOL_USED,
    NATPT_ERR_AAM_POOL_ENDSMALL,
    NATPT_ERR_AAM_POOL_TOOLONG,
    NATPT_ERR_AAM_POOL_EXIST,
    NATPT_ERR_AAM_POOL_ADDRESSOVERLAP,
    NATPT_ERR_AAM_INTERNALPROCESSINGFAIL,

    /* Error codes w.r.t V6 Mapping */
    NATPT_ERR_AAM_V6MAPPING_NOTEXIST,
    NATPT_ERR_AAM_V6MAPPING_USED,
    NATPT_ERR_AAM_V6MAPPING_EXIST,
    NATPT_ERR_AAM_V6MAPPING_POOLMAPPEDTO,
    NATPT_ERR_AAM_V6MAPPING_INTMAPPEDTO,
    NATPT_ERR_AAM_V6MAPPING_ACLMAPPED,
    NATPT_ERR_AAM_V6MAPPING_PREFIXMAPPED,
    NATPT_ERR_AAM_V6MAPPING_PATNOTSUPPORTED,
    NATPT_ERR_AAM_V6MAPPING_POOLSMALL,    
    NATPT_ERR_AAM_V6MAPPING_POOLNOTEXIST,
    NATPT_ERR_AAM_V6MAPPING_UNCONFIGUREDPREFIX,
    /* Error codes w.r.t V4 Mapping */
    NATPT_ERR_AAM_V4MAPPING_NOTEXIST,
    NATPT_ERR_AAM_V4MAPPING_EXIST ,
    NATPT_ERR_AAM_V4MAPPING_PREFIXMAPPEDTO,
    NATPT_ERR_AAM_V4MAPPING_ACLMAPPED,
    NATPT_ERR_AAM_V4MAPPING_UNCONFIGUREDPREFIX,
    NATPT_ERR_AAM_V4MAPPING_INTERFACEPREFIX,
    NATPT_ERR_AAM_PREFIX_NOTEXIST,
    NATPT_ERR_AAM_PREFIX_USED,
    NATPT_ERR_AAM_PREFIX_EXIST,
    NATPT_ERR_AAM_INTERFACEPREFIX_EXIST,
    /* Error Codes w.r.t NATPT Management */
    NATPT_ERR_MGMT_INTFALREADYENABLED ,
    NATPT_ERR_MGMT_INTFNOTENABLED ,
    NATPT_WARN_MGMT_DBGALREADYENABLED,
    NATPT_WARN_MGMT_DBGNOTENABLED,
    NATPT_ERR_MGMT_INVALID_IFNET,     
    NATPT_ERR_SYNCMULT_FAIL,          
    NATPT_ERR_JOINMULT_FAIL,          
    NATPT_ERR_DOWNLOAD_FAIL,          
    NATPT_ERR_LEAVEMULT_FAIL,         
    /* Error codes W.r.t AM */
    NATPT_ERR_MM_ADDRMAP_NOEXIST, 
    NATPT_ERR_MM_ADDRMAP_EXISTS, 
    NATPT_ERR_ADDRESS_PAT,
    NATPT_ERR_MM_ADDRESS_NOTCREATED,
    NATPT_ERR_INVALID_INPUT,
    NATPT_ERR_MM_NOTDELETE_DYNAMIC,
    NATPT_LCS_OFF,
    /* Error codes in Shell */
    NATPT_ERROR_SYNCFAILURE,
    NATPT_ERR_CREATETIMER_FAIL,

    /* for defect BYAD04881 */
     /* Error codes w.r.t. Traf Class */
    NATPT_ERR_PT_INVALIDTRAFFLAG,
    NATPT_ERR_PT_TOS_TURNOFF,
    NATPT_ERR_PT_TRAFFICCLASS_TURNOFF,
    NATPT_ERR_PT_NO_TOS_TURNOFF,
    NATPT_ERR_PT_NO_TRAFFICCLASS_TURNOFF,
    /* end of defect BYAD04881 */

    
    NATPT_NO_MAPPING,
    NATPT_NO_SESS,
    NATPT_ERR_MALLOCFAIL,
    NATPT_INVALID_PARAM,
    NATPT_FAILURE,
    NATPT_MAPPING_END,
    /*Add for defect BYAD09118*/
    NATPT_RESET_ONGOING
};

enum NATPT_State_HA
{
    NATPT_HSB_NORMAL= 0,
    NATPT_HSB_NOTREADY, 
    NATPT_HSB_BATCHBACKUP_ON
};

enum NATPT_HA_BACKUP_TYPE
{
    NATPT_HSB_BATCH = 0,
    NATPT_HSB_REALTIME,
    NATPT_HSB_PERIODIC,
    NATPT_SMOOTH_INSIDE,
    NATPT_SMOOTH_ACROSS
};


  
#define NATPT_SUCCESS 0
#define NATPT_ERROR 1


/*----------------------------------------------*
 * Function Declaration    
 *----------------------------------------------*/

enum enumNATPTMDSIGN
{
    /** enumNATPTMDSIGN should starts from 25 . 1 to 25 is resevered for CLI CMD SIGN */

    NATPT_AAM_NOTIFY_ADDRCHANGE = 25 ,
    NATPT_SEND_POOLNUM_AND_V6SADDR ,
    NATPT_AAM_DOWNLOAD_ADDRGRP,
    NATPT_AAM_DOWNLOAD_V6ACCESS,
    NATPT_AAM_DOWNLOAD_PREFIX ,
    NATPT_AAM_DOWNLOAD_V4ACCESS,
    NATPT_V6ACCESS_INDEX_AND_ADDR_UPDATE,
    NATPT_PREFIX_INDEX_UPDATE,
    

/* Check with Usha for destirnbuted  */
    NATPT_CMD_INTERFACE_DELETE,
    NATPT_CMD_DELINTF_FROMLIST,
    NATPT_CMD_DELETE_ALL ,
    NATPT_CMD_DOWNLOAD_INTFLIST,
    NATPT_ADDRMAP_DOWNLOAD,
    NATPT_CMD_BOARD_PLUGOUT,
    NATPT_CMD_ADDINTF_TOLIST,
    /* for defect BYAD04881 */
    NATPT_CMD_DOWNLOAD_TRAFCLASS,
    /* for defect BYAD07830 */
    NATPT_CMD_NODEBUGALL,

    
/* Archana */
    NATPT_CMD_DELETE_ADDRMAP,
    NATPT_CMD_DOWNLOAD_ADDRMAP,
    NATPT_CMD_DOWNLOAD_DPAT,
    NATPT_CMD_DOWNLOAD_SESSIONINFO,
    NATPT_CMD_INC_COUNT,
    NATPT_CMD_DEC_COUNT,
    NATPT_CMD_AM_UNDOEN,
    NATPT_CMD_CREATE_MAP,
    NATPT_CMD_AM_CLEAR_DYNAMIC
};

#ifdef  __cplusplus
}
#endif


#endif

