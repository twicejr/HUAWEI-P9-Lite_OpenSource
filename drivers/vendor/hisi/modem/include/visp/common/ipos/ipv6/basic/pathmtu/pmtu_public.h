/* **********************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*-----------------------------------------------------------------------
*                              pmtu_public.h
*
*    Project Code:  IPOS IR V1R2
*    Module Name :  pmtu
*    Create Date :  2006/09/23
*    Author      :  Yinyuanbin
*    Description :  To define Addr6 data structures used by external modules
*-----------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------
* 1. 2006-09-23  yinyuanbin    Created for including all public definitions in
*                             this file, for IPOSV1R1
*********************************************************************** */

#ifndef _PMTU_PUBLIC_H
#define _PMTU_PUBLIC_H

#ifdef  __cplusplus
extern "C"{
#endif  /* #ifdef  __cplusplus */

/* ----------------------------------------------*
 *              Macros                          *
 *---------------------------------------------- */
/* Range for mtu */
#define MIN_LINK_PMTU                   1280
#define PMTU_MAX_LINK_PMTU              10000

/* MAX_INT for arm allignment of enum */
#define IP6_PMTU_MAX_ENUM_VALUE                 0xFFFFFFFF

/* Number of minutes usage to be cached to find least used entry */
#define MAX_CATCH_ITEM                      10


/* ERROR Codes returned by config APIs */
#define ADD_NODE_FAILED                                     101
#define DELETE_NODE_FAILED                                  102
#define DELETE_ENTRY_FAILED                                 103
#define NOTIFY_SOCKETS_FAILED                               104
#define IP6_PMTU_ADD_ENTRY_FAILED                           105
#define MAX_CLI_ENTRIES_EXCEEDED                            106
#define MEMORY_ALLOCATION_FAILED                            108
#define PMTU_GADS_GETOBJ_FAILED                             109
#define PMTU_GADS_INVALID_HANDLE_ERROR                      110
#define PMTU_GADS_DELETE_OBJ_ERROR                          111
#define PMTU_GADS_INVALID_MINDEX                            112
#define PMTU_VALIDATE_AGETIME_FAILED                        113
#define PMTU_ICMP_TOO_BIG_NOTIFY_FALIED                     114
#define PMTU_ADD_SOCKETID_ENTRY_FAILED                      115
#define PMTU_TOO_BIG_HANDLING_FAILED                        116
#define NODE_DOES_NOT_EXISTS                                117
#define PMTU_REACHED_MAX_CLI_ENTRIES                        118
#define PMTU_REACHED_MAX_ENTRIES                            119
#define PMTU_MAX_SOCKET_EXCEEDED                            120
#define PMTU_DYNAMIC_ENTRY_CANNOT_DELETE                    121
#define PMTU_ENTRY_CANNOT_CONFIGURED                        122
#define IP6_PMTU_ERR_ENTRY_DOESNOT_EXIST                    123
#define IP6_PMTU_ERR_NULL_INPUT                             124
#define IP6_PMTU_ERR_INVALID_INPUT                          125
#define IP6_PMTU_ERR_HA_MEMALLOCATE_FAIL                    126
#define IP6_PMTU_ERR_HA_REALTIMEBACKUP_FAIL                 127
#define IP6_PMTU_ERR_STATIC_ENTRY_CANNOT_DELETE             128
#define IP6_PMTU_ERR_WAITLIST_UNREGISTER_FAILED             129
#define IP6_PMTU_ERR_GADS_GET_USED_FIRST_FAILED             130
#define IP6_PMTU_ERR_UNALIGNED_ADDRESS                      131
#define IP6_PMTU_ERR_INVALID_INPUT_USING_DEFAULT            132
#define IP6_PMTU_ERR_INVALID_ZONEID                         133
#define PMTU_ERR_INVALID_LINKLOCAL_MULTICAST                134
#define PMTU_ERR_OWN_ADDRESS                                135
#define IP6_PMTU_ERR_INVALID_IP6_ADDRESS                    136
#define IP6_PMTU_ERR_WAITLIST_GET_FAILED                    137

#define IP6_PMTU_ERR_INVALID_PAF_STRING                     138
#define IP6_PMTU_ERR_DEPENDENT_PAF_CONFLICT_LOAD_DEFAULT    139


#define IP6_PMTU_ERR_SEMOP_ACQUIRELOCK_FAIL                 140

/* BEGIN : NDHOST SDV Defect AC4D05549, Anand */
#define IP6_PMTU_ERR_WAITLIST_REGISTER_FAILED               141
#define IP6_PMTU_ERR_WAITLIST_SET_FAILED                    142

/* END : NDHOST SDV Defect AC4D05549, Anand */

/* macros for filling/validating SPECS_RES_VALUE_S */
#define PMTU_CONTROLLED_BY_PAF_LCS      1
#define PMTU_CONTROLLED_BY_PAF          0

/* Default Values */
#define PMTU_DEF_AGE_TIME           10

/* Control Flags for pfIP6_PMTU_DeleteMatchingEntry */
#define ANY_VALUE              0x00
#define CLI_DELETE             0x01
#define TESTABILITY_DELETE     0x02

/* ----------------------------------------------*
 *              Enumerated Data Types           *
 *---------------------------------------------- */

/* PMTU entry type passed as argument for different config APIs */
typedef enum tagIP6_PMTU_Entry_Type
{
    IP6_PMTU_DYNAMIC_ENTRY,
    IP6_PMTU_STATIC_ENTRY,
    IP6_PMTU_ANY_ENTRY,
    IP6_PMTU_ENTRY_TYPE_PAD = IP6_PMTU_MAX_ENUM_VALUE
} IP6_PMTU_Entry_Type_E;

/* ----------------------------------------------*
 *              Data Structures                 *
 *---------------------------------------------- */

/* To send PMTU information to CLI for display */
typedef struct tagPMTUCLIDisplay
{
    IN6ADDR_S stDest_Addr;
    ULONG ulScope_id;   /* zone index */
    ULONG ulPMTU;
    ULONG ulMultiIdex;  /* To get next PMTU entry */
    ULONG ulSocketCount;
    USHORT usAge_time;
    UCHAR ucFlag;   /* Specifies whether it is a CLI configured entry or not */
    UCHAR ucAccess_count[MAX_CATCH_ITEM]; /* Last 10 min info, per minute */
    UCHAR ucTotal_count;  /* Last 10 min Total count */
    USHORT usReserved;
} PMTU_CLI_DISPLAY_S;

typedef struct tagIP6_PMTU_NP_MSG
{
    IN6ADDR_S stDestIP6Addr; /* Destination IPv6 Address */
    ULONG     ulPMTU;        /* PathMTU Value */
    UCHAR     ucType;        /* Flag's bit CLI_DELETE will be set for static entry
                                and reset for dynamic entry */
    UCHAR     ucPad[3];
}IP6_PMTU_NP_MSG_S;


typedef struct tagTCPIP_IP6_TooBigInfo
{
    MBUF_S  *pstMbuf;              /*TOO BIG 报文,偏移ulOffSetToICMP6Header 到ICMP6首部
                                     不允许修改MBUF 里面的数据 且MBUF不能由产品释放*/ 
    ULONG  ulOffSetToICMP6Header;  /*IP和ICMP之间可能有其他扩展，所以要产品自己根据这个偏移长度 转到ICMP6首部。*/
    ULONG  ulVrfIndex;             /* VRF 索引 */
    ULONG  ulRcvIfIndex;           /*入接口索引*/
    ULONG  ulPmtu;                 /* 目的地址的PMTU值 */
    IN6ADDR_S   stDstAddr;         /*目的地址*/
    UCHAR       ucProtocol;        /* 原始报文的协议号 */
    UCHAR       ucReserved[3];
}TCPIP_IP6_TOO_BIG_INFO_S;

typedef struct tagTCPIP_IP6_GET_USER_PMTU_PARA
{
    ULONG  ulVrfIndex;              /*VRF 索引*/
    ULONG  ulOutIfIndex;            /*出接口索引 */
    ULONG  ulLinkMtu;               /*接口MTU*/
    IN6ADDR_S   stDstAddr;          /*目的地址*/
}TCPIP_IP6_GET_USER_PMTU_PARA_S;

typedef struct tagTCPIP_IP6_PTU_USER_HOOK_S
{
    ULONG (*pfIP6SndPktGetPmtuHook)(TCPIP_IP6_GET_USER_PMTU_PARA_S *pstInputPara, ULONG *pulPmtu);
    ULONG (*pfIP6RcvPmtuPktHook)(TCPIP_IP6_TOO_BIG_INFO_S *pstTooBigInfo);
}TCPIP_IP6_PTU_USER_HOOK_S;

#ifdef  __cplusplus
}
#endif  /* #ifdef  __cplusplus */

#endif  /* _PMTU_PUBLIC_H */

