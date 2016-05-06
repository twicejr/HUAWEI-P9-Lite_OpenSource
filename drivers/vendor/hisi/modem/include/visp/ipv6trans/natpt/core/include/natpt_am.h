/************************************************************************
 *
 *    Copyright 2003, Huawei Technologies Co. Ltd  India Institute  
 *                     ALL RIGHTS RESERVED                           
 *                                                 
 *----------------------------------------------------------------------*
 *
 *                             natpt_am.h
 *
 *  Project Code:       VRPv5 
 *  Create Date:        2003-7-3
 *  Author:                Archana P V  (VRPv5 IPv6 Team) 
 *  Document:
 *  Function Description:
 *  
 *----------------------------------------------------------------------*
 *  Modification History 
 *  DATE        NAME             DESCRIPTION
 *  2003-12-17  Archana PV       For Defect BYAD05088
 *  2003-12-30  Archana PV       For Defect BYAD05041 
 *  2004-01-27  Archana P V      For Defect BYAD07342
 ************************************************************************/




#ifndef _NATPT_AM_H
#define _NATPT_AM_H


#ifdef  __cplusplus
extern  "C"{
#endif

/*----------------------------------------------*
* Macros            
*----------------------------------------------*/
#define NATPT_MAX_V6ADDRMAP_INDEX   256/*Maximum V6 index for address mapping table*/
#define NATPT_MAX_V4ADDRMAP_INDEX   256/*Maximum V4 index for address mapping table*/
#define NATPT_MAX_V6DPAT_INDEX      256/*Maximum V6 index for DPAT hash  table*/
#define NATPT_MAX_V4DPAT_INDEX      256/*Maximum V4 index for DPAT hash  table*/


#define NATPT_MAX_HA_ADDRMAP        20/*Max Addresses that can be packed as a part of the HA message*/
#define NATPT_MAX_SESSION_REFRESH   10000 /*For Defect BYAD05041.Refresh the entire table*/


/* #define NATPT_MAX_FRAG_COUNT 5000*/ 
#define NATPT_MAX_V6SESSION_INDEX 10000/*Maximum V6 index for session mapping table*/
#define NATPT_MAX_V4SESSION_INDEX 10000/*Maximum V6 index for session mapping table*/
#define NATPT_MAX_V6FRAG_INDEX 2048/*Maximum index for Fragmentation hash  table*/
#define NATPT_MAX_DELETE_V4ADDR 10/*Maximum number of deleted addresses list maintained. */

/*Forms the V4 hash index for the Address mapping*/
#define NATPT_V4ADDRMAP_HASH(ulV4Address) (ulV4Address % NATPT_MAX_V4ADDRMAP_INDEX)

/*Forms the V6 hash index for the Address mapping*/
#define NATPT_V6ADDRMAP_HASH(stV6Addr) (((stV6Addr).u6_addr.u6_addr32[0]^(stV6Addr).u6_addr.u6_addr32[1]^\
               (stV6Addr).u6_addr.u6_addr32[2]^(stV6Addr).u6_addr.u6_addr32[3])%NATPT_MAX_V6ADDRMAP_INDEX)
                                        

#define NATPT_V4DPAT_HASH(usPort) (usPort % NATPT_MAX_V4DPAT_INDEX)/*Forms the V4 DPAT index*/

#define NATPT_V6DPAT_HASH(stV6Addr,usPort) ((((stV6Addr).u6_addr.u6_addr32[0]^(stV6Addr).u6_addr.u6_addr32[1]^\
            (stV6Addr).u6_addr.u6_addr32[2]^(stV6Addr).u6_addr.u6_addr32[3]) + usPort)%NATPT_MAX_V6DPAT_INDEX)
                                             

#define NATPT_V4SESSION_HASH(ulV4SAddr,ulV4DAddr,usV4SPort,usV4DPort)  (((ulV4SAddr^ulV4DAddr)+\
                                                usV4SPort + usV4DPort) % NATPT_MAX_V4SESSION_INDEX)


#define NATPT_V6SESSION_HASH(stV6SAddr,stV6DAddr,usV6SPort,usV6DPort) ((((stV6SAddr).u6_addr.u6_addr32[0]^\
                   (stV6SAddr).u6_addr.u6_addr32[1]^(stV6SAddr).u6_addr.u6_addr32[2]^(stV6SAddr).u6_addr.u6_addr32[3]^\
                   (stV6DAddr).u6_addr.u6_addr32[1]^(stV6DAddr).u6_addr.u6_addr32[2]^(stV6DAddr).u6_addr.u6_addr32[3])+\
                    usV6SPort + usV6DPort) % NATPT_MAX_V6SESSION_INDEX)
                    
#define NATPT_FRAG_HASH_INDEX(ulPacketID)((ULONG)((ulPacketID) & 0x7ff))

#define NATPT_IS_SAME_MAPPING(ucFlag1,ucFlag2) ((ucFlag1 & (NATPT_STATIC_BIT| NATPT_SOURCE_DEST_BIT)) ==\
                                                (ucFlag2 & (NATPT_STATIC_BIT| NATPT_SOURCE_DEST_BIT)))

#define NATPT_SMOOTH  0

#define SYSTRC_IPV6_NATPT_MM_BASE 10 /*to be checked  keshava  */
#define NATPT_MM_AM ((SYSTRC_IPV6_NATPT_MM_BASE << 8) + 10) /* to be checked keshava */
#define NATPT_MM_SM ((SYSTRC_IPV6_NATPT_MM_BASE << 8) + 11) /* keshava to be checked */

/*----------------------------------------------*
 *Enum and Structure Defintions
 *----------------------------------------------*/
/*enum for real time data */
/*Delete for Defect BYAD05088*/

/*structure for address mapping */
typedef  union
{
    char   u6_addr8[16]; /*remove this */
    short  u6_addr16[8]; 
    long   u6_addr32[4]; 
}UNION_IN6_ADDR_U ;


typedef  struct tagNATPT_HA_AddrMapNode
{
    ULONG  ulV4Addr;
    IN6ADDR_S stV6Addr;
    ULONG  ulcount;
    ULONG  ulAgeOut;
    ULONG  ulFlag;
}NATPT_HA_ADDRMAP_NODE_S;

typedef  struct tagNATPT_HA_RealTimeNode
{
    USHORT usType;
    USHORT usFlag;
    ULONG ulV4Address;
    IN6ADDR_S stV6Address;
    ULONG ulSlot;
}NATPT_HA_REALTIME_NODE_S;

typedef struct tagNATPT_HA_AddrMap
{ 
    USHORT usType;
    USHORT usNumOfAddrMap;
    NATPT_HA_ADDRMAP_NODE_S aHAAddrMapNodes[NATPT_MAX_HA_ADDRMAP];
}NATPT_HA_MM_ADDRMAP_S;

typedef struct tagNATPT_HA_MM_TIMER
{
    USHORT usType;
    USHORT usReserved;
    ULONG ulGlobalTimer;
}NATPT_HA_MM_TIMER_S;



typedef struct tagNATPT_DeletedV4Addr
{
    ULONG aulDeletedV4Addr[NATPT_MAX_DELETE_V4ADDR];
    USHORT usNumOfAddr;
}NATPT_DELETED_V4ADDR_S;






/*----------------------------------------------*
 * Function Decalrations
 *----------------------------------------------*/
BOOL_T NATPT_MM_Init_All_HashIndex();
ULONG NATPT_MM_CreateDPATMap(ULONG ulV4Address,
                             IN6ADDR_S stV6Address,
                             USHORT usV4Port , 
                             USHORT usV6Port,
                             UCHAR ucProtocol);
BOOL_T NATPT_AM_IncrementCount (ULONG ulV4Address, IN6ADDR_S   stV6Addr,UCHAR ucFlag,ULONG ulSlot);
BOOL_T NATPT_AM_DecrementCount (ULONG ulV4Address, IN6ADDR_S   stV6Addr,UCHAR ucFlag,ULONG ulSlot);

ULONG NATPT_MM_DeleteAddrMap (ULONG ulV4Addr, 
                                           IN6ADDR_S stV6Address,
                                           UCHAR ucFlag);
ULONG NATPT_MM_DeleteDPATMap(ULONG ulV4Address, 
                                            IN6ADDR_S stV6Address,
                                            USHORT usV4Port , 
                                            USHORT usV6Port,
                                            UCHAR ucProtocol);
BOOL_T NATPT_AM_DeleteAllDynamic();
BOOL_T NATPT_AM_DeleteAll();
BOOL_T NATPT_AM_UnRegisterHash(NATPT_HASH_ADDRMAP_S** ppstStart, 
                               NATPT_HASH_ADDRMAP_S* pstHash, 
                               NATPT_HASH_ADDRMAP_S* pstHashPrev);
BOOL_T NATPT_AM_FreeLinkFromV6Index(NATPT_HASH_ADDRMAP_S* pstHashDel);
ULONG  NATPT_MM_OpenObjectAddrMap(ULONG* pulWaitListHandle);
ULONG  NATPT_MM_CloseObjecAddrMapt(ULONG* pulWaitListHandle);
BOOL_T  NATPT__DeleteAll_AMandAAM();
BOOL_T NATPT_AM_TimerRefresh();
BOOL_T NATPT_SM_TimerRefresh();
ULONG NATPT_MM_UnPackHAData(NATPT_HA_ADDRMAP_NODE_S* pstBackUpNode);

ULONG  NATPT_MM_MGMT_ResetAll();
ULONG NATPT_SM_ObtainTimeOutVal(UCHAR ucPro);
ULONG  NATPT_MM_DeleteFragMap(NATPT_HASH_FRAG_S** ppstStart,
                              NATPT_HASH_FRAG_S* pstHash,
                              NATPT_HASH_FRAG_S* pstPrevHash);
VOID* NATPT_GetNextAddrMapCB(VOID* pstCurAddrMap,VOID** ppstNextAddrMap);
VOID* NATPT_GetNextDPATMapCB(VOID* pstCurDPATMap,VOID** ppstNextDPATMap);
VOID* NATPT_GetNextSessionMapCB(VOID* pstCurSessionMap,VOID** ppstNextSessionMap);
VOID* NATPT_GetNextFragMapCB(VOID* pstCurFragMap,VOID** ppstNextFragMap);
BOOL_T NATPT_SM_IsAddr_Deleted(ULONG ulV4ddr);
BOOL_T  NATPT_SM_DeleteSessionByV6(NATPT_HASH_SESSION_S* pstHashDel);
BOOL_T NATPT_SM_DeleteSessionByV4(NATPT_HASH_SESSION_S** ppstStart, 
                                  NATPT_HASH_SESSION_S* pstHash, 
                                  NATPT_HASH_SESSION_S* pstHashPrev);


#ifdef  __cplusplus
}
#endif

#endif

