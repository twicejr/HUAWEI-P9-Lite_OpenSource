
/******************************************************************************
*
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*
*------------------------------------------------------------------------------
*    Project Code   : VRP5.0
*    Module Name    : IP6 ND
*    Version        : Initial Draft
*    File Name      : ND_SH_CFG.H
*    Create Date    : 2003/06/25
*    Author         : Santosh G Kulkarni
*    Description    : the interface module of ND
*------------------------------------------------------------------------------
*  Modification History
*
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2003-06-25  Santosh G Kulkarni     Create
   Problem Number : AC4D01354     Author:Moutusi 71680, Date:2006/12/12
   Description    : Brief Description	Padding byte is to  be inserted to make
                    structure alignment
*******************************************************************************/
#ifndef      _ND_FUN_H_
#define      _ND_FUN_H_

#ifdef      __cplusplus
extern "C"{
#endif

#define CFGPARALEN          256
#define TIMEOUTVALUE_1000   1000
#define TIMEOUTVALUE_100    100
#define TIMEOUTVALUE_5000   5000
#define PRIORITY_3          3

/* Begin Reason : Compilation change   Mod:Bharath */

#define SID_ND_GBUILD_S         0x000B
#define SID_ND_BUILD_S          0x000A

#define  ND_OPEN_HANDLE         01
#define  ND_CLOSE_HANDLE        02
#define  ND_GET_NEXT_ENTRY      03
#define  ND_SYNC_GLOBAL_DATA    04

/*Change for def: AC4D01123 by karthik70713 */
#define  ND_ADD_NB_ENTRY        15
#define  ND_DEL_NB_ENTRY        16


/* IPv6 Start  DefectID: SWFD22473   Mod:Bharath   Date : 2006/02/15 */
#define IP6_ND_SET_COMMAND      0
#define IP6_ND_UNDO_COMMAND     1

/* IPv6 End  DefectID: SWFD22473   Mod:Bharath   Date : 2006/02/15 */

/* Only Shell */
#define      IP6_ND_GOTO_NEXT_INTERFACE     11

#define  ND_NUMBER_OF_ENTRIES_FROM_IO       20



/*
Note : The Static Neighbor Entry size will be 128 for both
       Router & IAS product.
*/
#define ND_STATIC_ENTRY_SIZE                128


#define BUFF_19         19
#define BUFF_30         30
#define BUFF_100        100
#define NDSTATELEN      13
#define DISPLAYLLASTATE 15
#define FORDISPLAYSTATE 6
#define AFTERFIRSTBYTE  1
#define AFTERTHIRDBYTE  3
#define STRLEN_24       24
#define STRLEN_25       25
#define STRLEN_27       27 /* Max ipos num length */

#define STRLEN_15       15
#define STRLEN_8        8

#define STRLEN_21       21
#define STRLEN_20       20
#define STRLEN_4        4



/* For converting time units */
#define CONVERT_BETWEEN_SEC_MIN 60

#define IP6_ND_BUFFER 512

#define LEN_64       64

#ifndef LEN_256
#define LEN_256      256
#endif
#define LEN_1024     1024

#define IP6_ND_SH_LOG  IP6ND_SH_LogToIPOSIC

/* Status code for CLI Install - Multiple Template, Same Command */
#define IP6_ND_REGCLI_STAT_ALL_SUCCESS                0
#define IP6_ND_REGCLI_STAT_FIRST_INSTALL_FAILED       1
#define IP6_ND_REGCLI_STAT_ATLEAST_ONE_FAILED         2

#define ND_DEBUG_TEST     0

/* ND MIB structure */
typedef struct tagIP6NDENTRYMSG_S
{
    ULONG          ulMsgType;        /* SET, GET or GET_NEXT   */
    UINTPTR        ulWaitListHandle;
    ULONG          ulIfnetIndex;
    ULONG          ulReserved1;

}IP6NDENTRYMSG_S;

/*Change for def: AC4D01123 by karthik70713 */
typedef struct tagIP6NDADDENTRYMSG_S
{
    IN6ADDR_S       stIn6Addr;
    UCHAR          ucLLAddr[MACADDRLEN];
    USHORT          usReserved;

}IP6ND_ADD_ENTRYMSG_S;

/* ND MIB message format */
typedef struct tagIP6NDSENDMSG_S
{
    ULONG          ulCount;        /* SET, GET or GET_NEXT   */
    UINTPTR        ulWaitListHandle;
    ULONG          ulIfnetIndex;
    ULONG          ulReserved1;

}IP6NDSENDMSG_S;

/* ND Plug in message format */
typedef struct tagIP6NDPLUGIN_S
{
    ULONG       ulMsgType;
    ULONG       ulDebugInfo;
    ULONG       ulVlinkFlag; /* AC4D01411 - Added VlinkFlag for IO board sync */
    UCHAR       ucHopValue;
    UCHAR       ucPad[3];
} IP6NDPLUGIN_S;

/* RPC message format */
typedef struct tagND_NBENTRY_RPC
{
    ULONG ulCount;
    ULONG ulDone;
    VOID *pTemp;
}ND_NBENTRY_RPC;

void IP6_ND_SH_NonVrp_ChangeBuildRun(VOID   *pstIfNet);

ULONG IP6_ND_SH_Display_NeighbourCache(VOID *pdata, CHAR *pszBuf, ULONG ulBufLen);

/* IP6_ND_MALLOC will be used in ND module, to allocate inside ND Module.
   Similarly, IP6_ND_FREE will be used in ND module, only when the corresponding
   memory is allocated by ND module. If the pointer 'ptr' is NULL, then print
   an assert for debugging the bad pointer.*/

#define IP6_ND_MALLOC(ulInfo, ulSize)  TCPIP_Malloc((ulInfo), (ulSize))
#define IP6_ND_FREE(ptr)\
{\
    if (NULL != (ptr))\
    {\
        (VOID)TCPIP_Free((VOID *)ptr);\
        (ptr) = NULL;\
    }\
    else\
    {\
        VOS_DBGASSERT(0);\
    }\
}

ULONG IP6_ND_SH_Display_NBInfo(VOID *pdata, CHAR *pszBuf, ULONG ulBufLen);

#ifdef      __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _ND_H_ */
