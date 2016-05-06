/************************************************************************
 *
 *    Copyright 2003, Huawei Technologies Co. Ltd  India Institute  
 *                     ALL RIGHTS RESERVED                           
 *                                                 
 *----------------------------------------------------------------------*
 *
 *                             natpt_aam.h
 *
 *  Project Code:       VRPv5 
 *  Create Date:        2003-7-10
 *  Author:             arvind   (VRPv5 IPv6 Team) 
 *  Document:
 *  Function Description:
 *  
 *----------------------------------------------------------------------*
 *  Modification History 
 *  DATE        NAME             DESCRIPTION
 *  
 *  2003-11-27    ArvindSaproo  for Defect BYAD02940
 *  2003-12-15    Arvindsaproo  for Defect BYAD06254
 ************************************************************************/





#ifndef _NATPT_AAM_H
#define _NATPT_AAM_H

#ifdef  __cplusplus
extern  "C"{
#endif


/*----------------------------------------------*
 * Macros
 *----------------------------------------------*/
#define NATPT_IS_V6ACLORPREFIX_TO_ADDRGRP_MAPPING(x) \
      ((x & NATPT_ACL6_NUMBER_TO_ADDRGRP) || \
       (x & NATPT_ACL6_NAME_TO_ADDRGRP) || \
       (x & NATPT_V6PREFIX_TO_ADDRGRP))
#define NATPT_IS_V6ACLORPREFIX_TO_INTERFACE_MAPPING(x) \
      ((x & NATPT_ACL6_NUMBER_TO_INTERFACE) || \
       (x & NATPT_ACL6_NAME_TO_INTERFACE) || \
       (x & NATPT_V6PREFIX_TO_INTERFACE))

#define NATPT_IS_ACL_NUM_TO_PREFIX(x)    (x & NATPT_ACL_NUM_TO_PREFIX)
#define NATPT_IS_ACL_NAME_TO_PREFIX(x)   (x & NATPT_ACL_NAME_TO_PREFIX)

/* BYAD06254 - For Queue based PAT port allocation scheme */

#define NATPT_INVALID_PAT_PORT  0
#define NATPT_MAX_PATPORT_QUEUES    25     
#define NATPT_PORTS_PER_PATQUEUE    2048  

/* BYAD06254 end */

#define NATPT_INVALID_ACL_NUMBER         0
#define NATPT_IS_NULL_STRING(str)        (VOS_strcmp(str,"") == 0)


#define NATPT_MAX_POOL_LEN               255
#define NATPT_MIN_NOPAT_POOL_LEN         \
    ((1 == g_stNATPT_LCS_INFO.PAT.ulAvail_Value)? 2 : 1)

#define NATPT_INVALID_POOL_NUMBER        0xffff 
#define NATPT_IS_INVALID_POOL_NUMBER(num) (num == NATPT_INVALID_POOL_NUMBER)

#define NATPT_AAM_PREFIX_UPDATE_UNIT    10
#define NATPT_AAM_V6ACCESS_UPDATE_UNIT  10

#define NATPT_GET_ACTUAL_POOLEND_ADDRESS(addr) \
    ((1 == g_stNATPT_LCS_INFO.PAT.ulAvail_Value)? ((addr) - 1) : (addr))

#define NATPT_PAT_IS_ENABLED \
    ((1 == g_stNATPT_LCS_INFO.PAT.ulAvail_Value)? (1) : (0))

/* Following Macro Obtained from NAT code */
#define GetIntAddrFromIf(pstIf,ulIntAddr)   \
{\
    IPIFADDR_S  *pstIfAddr;\
                                \
    if(pstIf == NULL)\
    {\
        ulIntAddr = 0;\
    }\
    else\
    {\
        pstIfAddr = ((IPIFNET_S *)(pstIf->if_ulIpIf) )->ipif_stIpIfAddrList.ia_v_pNext;\
\
        if(pstIfAddr == NULL)\
        {\
            ulIntAddr = 0;\
        }\
        else\
        {\
            ulIntAddr = VOS_NTOHL(pstIfAddr->ia_stAddr.s_ulAddr);\
        }\
    }\
}

/*-----------------------------------------------*
 * Structure Definitions
 *-----------------------------------------------*/

typedef struct tagNATPT_Download_AddrGrp_Node
{
    ULONG ulStartAddr;
    ULONG ulEndAddr;
    ULONG ulAdressGroupNo;
} NATPT_Download_AddrGrp_Node_S;

typedef struct tagNATPT_Download_AddrGrp_Info
{
    USHORT usCmdSign;
    USHORT usNumParam;
    NATPT_Download_AddrGrp_Node_S astAddrGrp_Node
                                      [NATPT_AAM_ADDRGRP_DOWNLOAD_UNIT];
} NATPT_Download_AddrGrp_Info_S;

typedef struct tagNATPT_Download_v6Access_Node
{
    NATPTv6AclOrPrefix_U unAclOrPrefix;
    ULONG ulStartAddr;
    ULONG ulEndAddr;
    USHORT usPoolNo;
    USHORT usIsPAT;
    ULONG ulMappingType;
    ULONG ulIfIndex;
    CHAR szInterfaceName[IF_MAX_INTERFACE_NAME_LEN+1];
}NATPT_Download_v6Access_Node_S;

typedef struct tagNATPT_Download_v6Access_Info
{
    USHORT usCmdSign;
    USHORT usNumParam;
    NATPT_Download_v6Access_Node_S astV6Access_Node
                                       [NATPT_AAM_V6ACCESS_DOWNLOAD_UNIT];
} NATPT_Download_v6Access_Info_S;

typedef struct tagNATPT_Download_Prefix_Node
{
    IN6ADDR_S stNatPtPrefix;
    ULONG ulPrefixType;
    ULONG ulNextHopAddr;
    ULONG ulIfIndex;
    CHAR szInterfaceName[IF_MAX_INTERFACE_NAME_LEN+ 1];
} NATPT_Download_Prefix_Node_S;

typedef struct tagNATPT_Download_Prefix_Info
{
    USHORT usCmdSign;
    USHORT usNumParam;
    NATPT_Download_Prefix_Node_S astPrefix_Node
                                     [NATPT_AAM_PREFIX_DOWNLOAD_UNIT];
} NATPT_Download_Prefix_Info_S;

typedef struct tagNATPT_Download_v4Access_Node
{
    ULONG ulListNum;
    ULONG ulMappingType;
    IN6ADDR_S stNatPtPrefix;
    CHAR szListName[MAX_ACL_NAME_LEN + 1];
} NATPT_Download_v4Access_Node_S;

typedef struct tagNATPT_Download_v4Access_Info
{
    USHORT usCmdSign;
    USHORT usNumParam;
    NATPT_Download_v4Access_Node_S astV4Access_Node
                                       [NATPT_AAM_V4ACCESS_DOWNLOAD_UNIT];
} NATPT_Download_v4Access_Info_S;

typedef struct tagNATPT_UpdateV6Access_NodeIndexAndAddr
{
    ULONG ulIfIndex;
    ULONG ulV4Addr;
    CHAR szInterfaceName[IF_MAX_INTERFACE_NAME_LEN+1];
} NATPT_UpdateV6Access_NodeIndexAndAddr_S;

typedef struct tagNATPT_UpdatedV6Access_NodeInfo
{
    USHORT usCmdSign;
    USHORT usNumParam;
    NATPT_UpdateV6Access_NodeIndexAndAddr_S astUpdateV6Access_Node
                                      [NATPT_AAM_V6ACCESS_UPDATE_UNIT];
} NATPT_UpdateV6Access_NodeInfo_S;


typedef struct tagNATPT_UpdatedPrefix_NodeIndex
{
    ULONG ulIfIndex;
    CHAR szInterfaceName[IF_MAX_INTERFACE_NAME_LEN+1];
} NATPT_UpdatePrefix_NodeIndex_S;

typedef struct tagNATPT_UpdatedPrefix_NodeInfo
{
    USHORT usCmdSign;
    USHORT usNumParam;
    NATPT_UpdatePrefix_NodeIndex_S astUpdatePrefix_Node
                                      [NATPT_AAM_PREFIX_UPDATE_UNIT];
} NATPT_UpdatePrefix_NodeInfo_S;



/* BYAD06254 - For Queue based PAT port allocation scheme */
typedef struct tagNATPT_PatPortQueueIndex
{
    USHORT* pusQueue;   
    USHORT* pusQueueHead; 
    ULONG   ulPortsUsed;  
} NATPT_PatPortQueueIndex_S;
/* BYAD06254 end */


/*----------------------------------------------*
 * Function Declarations
 *----------------------------------------------*/

ULONG NATPT_AAM_FindFreeAddressInPool(ULONG ulStartAddr, 
                                                ULONG ulEndAddr, 
                                                ULONG *pulFreev4Addr);

ULONG NATPT_IS_VALID_V4HOST_ADDR(ULONG ulV4Addr);


/* BYAD06254 - For Queue based PAT port allocation scheme */
ULONG NATPT_AAM_GetPatPort(USHORT *pusPatPort);
/* BYAD06254 end */

#ifdef  __cplusplus
}
#endif

#endif

