/*******************************************************************************
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              sfib6_sh_rm.h
*
* Project Code: VISPV100R005
*  Module Name: SFIB6
* Date Created: 2004-08-25
*       Author: Zhang Hongyan
*  Description: define macro、struct and function in the rm.
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                DESCRIPTION
*  -----------------------------------------------------------------------------
*  2004-08-25   Zhang Hongyan       Create
*  2006-03-30   Jiangtao            Adjust for D00645
*  2006-04-21   Jiangtao            Adjust for D00858
*
*******************************************************************************/

#include "tcpip/public/tcpip_config.h"

#ifdef    __cplusplus
extern    "C"{
#endif

#ifndef _SFIB6_RM_H
#define _SFIB6_RM_H

#include "tcpip/ifnet/include/if_def.h"
#include "common/ipos/ipv6/basic/icmp6/icmp6_public.h"
#include "common/ipos/ipv6/basic/addrmng/addr_public.h"
#include "tcpip/ipv6/sfib6/include/sfib6_api.h"

#define SFIB6_DEF_RIB_MAXNUM     64
#define SFIB6_DEF_SRM_VLINK      1
#define SFIB6_CFG_RIB_MAXNUM     1024

#define SFIB6_ROUTE_STATIC       1
#define SFIB6_ROUTE_DHCP         2
#define SFIB6_ROUTE_INTER_NET    3
#define SFIB6_ROUTE_INTER_HOST   4
#define SFIB6_ROUTE_LOOPBACK     5
#define SFIB6_ROUTE_VLINK        6

#define FIB6_NETRT_DEF_PRIORITY    0

#define FIB6_RT_MAX_PRIORITY    255

/**********************type defination here**********************************/
typedef struct tagSFIB6_RT_ENTRY
{
    ULONG  aulRt_Dest[4];
    ULONG  ulRt_Dest_PrefLen;
    ULONG  aulRt_Nexthop[4];
    ULONG  ulRt_Flags;              /* route flags -RTF_GATEWAY, RTF_HOST */
    ULONG  ulRt_IfIndex;            /* index of outgoing interface */
    ULONG  ulRt_ATIndex;            /* index of virtual link between ulRt_Loc_IfIndex */
    ULONG  ulRt_Slot;               /* slot num of outgoing interface */
    /*ULONG  aulRt_Loc[4];          */
    /*ULONG      ulRt_Loc_PrefLen;     commented by h39666 for ipv6 not use  04-12-20*/
    ULONG  ulRt_Loc_IfIndex;
    /* Begin:VISP V3R2C10 VRF chandra , 2014-03-18 */
    ULONG ulVrf6Index;    
    /* End:VISP V3R2C10 VRF chandra , 2014-03-18 */    
    ULONG  ulLabel;                 /* Inner label */
    ULONG  ulToken;                 /* >=1 - > indicates MPLS tunnel, 0 - indicates normal forwarding
                                       V6 stack will decide MPLS forwarding/normal forwarding based on this */
    USHORT usRt_Proto;              /* type of the entry: static, dhcp, host , or net */
    BOOL_T bUse;
    CHAR   szRt_OutIfName[MAX_IF_NAME_LENGTH + 1]; /*记录静态路由的出接口名 */
    ULONG   ulRtPri;            /* route priority */
    UCHAR  ucUserNextHopFlag;       /* 配置IPv6静态路由时是否指定next-hop,0不指定,1指定 */
    UCHAR  ucUserOutIfFlag;         /* 配置IPv6静态路由时是否指定出接口,0不指定,1指定 */
    UCHAR  ucPad[2];
} SFIB6_RT_ENTRY_S;


typedef struct tagFIB6_FILTER_KEY
{
    ULONG ulVrfIndex;                                  /*VRF Index*/
    UINTPTR ulWaitlist;                                  /*Waitlist handle*/
    ULONG ulFilterType;                                /*Type of the filter applied.*/
}FIB6_FILTER_KEY_S;

/* End of Added by pengbinquan pKF34550, 2011/02/18   问题单号:DTS2011022100676 */

typedef VOID (*Rm6_NextNetEntry_Get_FUNC)(SFIB6_RT_ENTRY_S **pstRtEntry);
typedef VOID (*Rm6_NetEntry_Free_FUNC)(SFIB6_RT_ENTRY_S *pstRtEntry);

/*主机序，从子网前缀长度得到网络号*/
#define SFIB6_GET_SUBNET_ADDRESS( pSubnet, pAddress, ulPrefixLength )     \
{\
    VOS_DBGASSERT( NULL != (pSubnet) );\
    VOS_DBGASSERT( NULL != (pAddress) );\
    VOS_DBGASSERT( sizeof(ULONG) == sizeof(*pSubnet) );\
    VOS_DBGASSERT( sizeof(ULONG) == sizeof(*pAddress) );\
    if ( 128 > (ulPrefixLength) )\
    {\
        ULONG ulMaxLoop     = (ulPrefixLength)/32;\
        ULONG ulLoop        = 0;\
        ULONG ulTestBit     = 0;\
        FIB6_SET_ADDRESS_NULL((pSubnet));\
        for ( ; ulLoop < ulMaxLoop; ulLoop++ )\
        {\
            (pSubnet)[ulLoop] = (pAddress)[ulLoop];\
        }\
        for ( ulLoop = 0; ulLoop < (ulPrefixLength)%32; ulLoop++ )\
        {\
            ulTestBit |= 0x80000000 >> ulLoop;\
        }\
        (pSubnet)[ulMaxLoop] = ((pAddress)[ulMaxLoop]) & ulTestBit;\
    }\
    else if ( 128 == (ulPrefixLength))\
    {\
        (pSubnet)[0] = (pAddress)[0];\
        (pSubnet)[1] = (pAddress)[1];\
        (pSubnet)[2] = (pAddress)[2];\
        (pSubnet)[3] = (pAddress)[3];\
    }\
    else \
    {\
        VOS_DBGASSERT( 0 );\
    }\
}
#define SFIB6_DELETE_ROUTE_FROM_FIB(stRtMsg,pstRtEntry)\
{\
    if (pstRtEntry->ulRt_Flags & FIB6_RTF_UP)\
    {\
        FIB6_COPY_RTENTRY_TO_RTMSG(&stRtMsg, pstRtEntry);\
        stRtMsg.usType = FIB6_RTMSG_DEL;\
        (VOID)g_pstFibAComFUNTable->pfIP6_FIB_KRTMsgSend(&stRtMsg);\
        pstRtEntry->ulRt_Flags &= ~FIB6_RTF_UP;\
    }\
    TCPIP_LOG_FIXLEN(RUN_LOG_VISP_0C54, TCPIP_LOG_LEVEL_DEBUG, LOG_TYPE_RUN,\
                "TCPIP SFIB6 LOG:The IPv6 route has been changed!\n", 0, 0, 0, 0);\
}

#define SFIB6_ADD_ROUTE_TO_FIB(stRtMsg,pstRtEntry)\
{\
    if ((BOOL_TRUE == SFIB6_RM_IfIsLinkUp(pstRtEntry->ulRt_IfIndex))\
        && (BOOL_FALSE == SFIB6_RM_DstAddrIsSame(pstRtEntry->ulVrf6Index, (IN6ADDR_S *)(pstRtEntry->aulRt_Dest), pstRtEntry->ulRt_Dest_PrefLen)))\
    {\
        stRtMsg.usType = FIB6_RTMSG_ADD;\
        pstRtEntry->ulRt_Flags |= FIB6_RTF_UP;\
        FIB6_COPY_RTENTRY_TO_RTMSG(&stRtMsg, pstRtEntry);\
        (VOID)g_pstFibAComFUNTable->pfIP6_FIB_KRTMsgSend(&stRtMsg);\
    }\
}\


#define FIB6_HOST_ROUTE_PREFIX      128


/*by q62011 for V3R2C00 coverity，改为函数调用，增加接口控制块的空指针的判断*/
/*#define SFIB6_BROADCASTIF_DIRECTROUTE(ulFlags, ulIfIdx)  ((IF_ISBROADCAST(IF_GetIfByIndex(ulIfIdx)))\
                                                           &&(0 == (ulFlags & FIB6_RTF_GATEWAY)))*/

/*判断地址是否是全球单播地址*/
#define SFIB6_ADDR6_IS_IPV6_GLOBAL_UNI(addr)                                    \
          (((addr)[0] != 0xFF) &&                                             \
           (((addr)[0] != 0xFE) || (((addr)[1] & 0x80) == 0x00)) &&           \
           (((addr)[0] != 0) ||                                               \
            ((addr)[1] != 0) ||                                               \
            ((addr)[2] != 0) ||                                               \
            ((addr)[3] != 0) ||                                               \
            ((addr)[4] != 0) ||                                               \
            ((addr)[5] != 0) ||                                               \
            ((addr)[6] != 0) ||                                               \
            ((addr)[7] != 0) ||                                               \
            ((addr)[8] != 0) ||                                               \
            ((addr)[9] != 0) ||                                               \
            ((addr)[10] != 0) ||                                              \
            ((addr)[11] != 0) ||                                              \
            ((addr)[12] != 0) ||                                              \
            ((addr)[13] != 0) ||                                              \
            ((addr)[14] != 0) ||                                              \
            (((addr)[15] != 0) && ((addr)[15] != 1))))



/******************************************************
               SFIB和AM6的接口消息
******************************************************/
#define SFIB_AM6_NEW_ADDRESS 0
#define SFIB_AM6_DEL_ADDRESS 1

/******************************************************
               SFIB和IFNET的VLINK接口消息
******************************************************/
#define SFIB_VLINK6_NEW 0
#define SFIB_VLINK6_DEL 1

typedef struct tagSFIB_VLINK6_IFNETMSG
{
    ULONG ulIfnetIndex;     /* Ifnet Index of the phy Interface */
    ULONG ulVlinkIndex;     /* Vlink Index is Zero for Phy Msg  */
    ULONG ulPeerAddr[4];    /* Peer Address of Vlink            */
    ULONG ulMsgType;        /* Message Type                     */
} SFIB_VLINK6_IFNETMSG_S;


#define COPY_ONE_ROUTE6_TO_USER(pstRtEntry,pstRtEntryTmp,ulIndex)    \
{\
    (pstRtEntry)->ulRt_Dest[0] = (pstRtEntryTmp)->aulRt_Dest[0];\
    (pstRtEntry)->ulRt_Dest[1] = (pstRtEntryTmp)->aulRt_Dest[1];\
    (pstRtEntry)->ulRt_Dest[2] = (pstRtEntryTmp)->aulRt_Dest[2];\
    (pstRtEntry)->ulRt_Dest[3] = (pstRtEntryTmp)->aulRt_Dest[3];\
    (pstRtEntry)->ulRt_Dest_PrefLen = (pstRtEntryTmp)->ulRt_Dest_PrefLen;\
    (pstRtEntry)->ulRt_Nexthop[0] = (pstRtEntryTmp)->aulRt_Nexthop[0];\
    (pstRtEntry)->ulRt_Nexthop[1] = (pstRtEntryTmp)->aulRt_Nexthop[1];\
    (pstRtEntry)->ulRt_Nexthop[2] = (pstRtEntryTmp)->aulRt_Nexthop[2];\
    (pstRtEntry)->ulRt_Nexthop[3] = (pstRtEntryTmp)->aulRt_Nexthop[3];\
    (pstRtEntry)->ulRt_Flags = (pstRtEntryTmp)->ulRt_Flags;\
    (pstRtEntry)->ulRt_IfIndex = (pstRtEntryTmp)->ulRt_IfIndex;\
    (pstRtEntry)->ulRt_ATIndex = (pstRtEntryTmp)->ulRt_ATIndex;\
    (pstRtEntry)->ulRt_Slot = (pstRtEntryTmp)->ulRt_Slot;\
    (pstRtEntry)->ulRt_Proto = (pstRtEntryTmp)->ulProto;\
    (pstRtEntry)->ulRt_TimeStamp = (pstRtEntryTmp)->ulRt_TimeStamp;\
    (pstRtEntry)->ulCacheEntryIndex = (pstRtEntryTmp)->ulCacheEntryIndex;\
    (pstRtEntry)->ulRTPri = (pstRtEntryTmp)->ulRtPri;\
    (pstRtEntry)->ulVrfIndex = (ulIndex);\
}\



/*End of Added by limin00188004, 2011/8/12   问题单号:C06新需求 */
ULONG IP6_RIB_OpenRib6Table (UINTPTR *pulHandle, CHAR * pszVrfName);
ULONG IP6_RIB_CloseObject_RIB (UINTPTR ulHandle);
ULONG IP6_RIB_GetRib6Entry (UINTPTR ulHandle, SFIB6_RT_ENTRY_S *pstRIBData);
/*End of Added by limin00188004, 2011/8/12   问题单号:C06新需求 */


/********************** extern  and inner   function ********************************/
BOOL_T SFIB6_RM_IfIsLinkUp(ULONG ulIfIndex);
ULONG SFIB6_RM_RtTblInit(ULONG ulZoneId);
VOID SFIB6_RM_RtTblClr(ULONG ulZoneId);
/* Begin:VISP V3R2C10 VRF chandra , 2014-03-18 */
/* VOID   SFIB6_InterfaceUp(ULONG ulIfIndex); */
VOID   SFIB6_InterfaceUp(ULONG ulZoneId, ULONG ulIfIndex);
/* VOID   SFIB6_InterfaceDown(ULONG ulIfIndex); */
VOID   SFIB6_InterfaceDown(ULONG ulZoneId, ULONG ulIfIndex);

/* VOID   SFIB6_RM_GetNextRoute(SFIB6_RT_ENTRY_S **ppstRtEntry); */
VOID SFIB6_RM_GetNextRoute(ULONG ulZoneId, SFIB6_RT_ENTRY_S **ppstRtEntry);
/* VOID   SFIB6_RM_NewRoute(SFIB6_RT_ENTRY_S **ppstRtEntry); */
VOID SFIB6_RM_NewRoute(ULONG ulZoneId, SFIB6_RT_ENTRY_S **ppstRtEntry);
/* End:VISP V3R2C10 VRF chandra , 2014-03-18 */
VOID   SFIB6_RM_FreeRoute(SFIB6_RT_ENTRY_S *pstRtEntry);


/* Begin:VISP V3R2C10 VRF chandra , 2014-03-18 */
/* ULONG SFIB6_AddRt(TCPIP_RT6_S *pstStaticRouter); */
ULONG SFIB6_AddRt(ULONG unZoneId, TCPIP_RT6_S *pstStaticRouter);
/* ULONG SFIB6_DelRt(TCPIP_RT6_S *pstStaticRouter); */
ULONG SFIB6_DelRt(ULONG unZoneId, TCPIP_RT6_S *pstStaticRouter);

/* ULONG SFIB6_AddRoute(TCPIP_RT6_S *pstStaticRouter) */
ULONG SFIB6_AddRoute(ULONG ulZoneId, TCPIP_RT6_S *pstStaticRouter);
/* ULONG SFIB6_DelRoute(TCPIP_RT6_S *pstStaticRouter); */
ULONG SFIB6_DelRoute(ULONG ulZoneId, TCPIP_RT6_S *pstStaticRouter);
/* End:VISP V3R2C10 VRF chandra , 2014-03-18 */

ULONG  SFIB6_Update_InterfaceAddress(SFIB_AM6_MSG_S *pMsg);
/* Begin:VISP V3R2C10 VRF chandra , 2014-03-18 */
/* VOID   SFIB6_AddInterfaceAddress(IN6ADDR_S *pstIn6Addr, ULONG ulMaskLen, ULONG ulIfIndex); */
VOID   SFIB6_AddInterfaceAddress(ULONG ulZoneId, IN6ADDR_S *pstIn6Addr, ULONG ulMaskLen, ULONG ulIfIndex);
/* VOID SFIB6_DelInterfaceAddress(IN6ADDR_S * pstIn6Addr, ULONG ulMaskLen, ULONG ulIfIndex) */
VOID SFIB6_DelInterfaceAddress(ULONG ulZoneId, IN6ADDR_S * pstIn6Addr, ULONG ulMaskLen, ULONG ulIfIndex);
/* VOID   SFIB6_Add_LinkLocal_Address(); */
VOID   SFIB6_Add_LinkLocal_Address(ULONG ulZoneId, IFNET_S *pIf);
/* VOID   SFIB6_Del_LinkLocal_Address(); */
VOID   SFIB6_Del_LinkLocal_Address(ULONG ulZoneId);
/* VOID SFIB6_IF_HaveLinkLocalAddr(ULONG ulIfIndex, UCHAR ucIfStatus) ;*/
VOID SFIB6_IF_HaveLinkLocalAddr(ULONG ulZoneId, ULONG ulIfIndex, UCHAR ucIfStatus);
/* End:VISP V3R2C10 VRF chandra , 2014-03-18 */

BOOL_T SFIB6_RM_StaticRouteValid(IN6ADDR_S * pstGateway, ULONG ulIfIndex);
BOOL_T SFIB6_RM_AddrIsOwn(IN6ADDR_S * pstNexthop, ULONG ulIfIndex);

/* Begin:VISP V3R2C10 VRF chandra , 2014-03-18 */
VOID SFIB6_RM_GetIntAddr(ULONG ulZoneId, ULONG ulIfIndex, ULONG ulIntIp6Addr32[4]);

/* BOOL_T SFIB6_RM_DstAddrIsSame(IN6ADDR_S *  pstDstAddr, ULONG ulMaskLen) ;*/
BOOL_T SFIB6_RM_DstAddrIsSame(ULONG ulZoneId, IN6ADDR_S *  pstDstAddr, ULONG ulMaskLen);
/* ULONG SFIB6_RM_DelSameStaticRoute(IN6ADDR_S *  pstDstAddr, ULONG ulMaskLen); */
ULONG  SFIB6_RM_DelSameStaticRoute(ULONG ulZoneId, IN6ADDR_S *  pstDstAddr, ULONG ulMaskLen);
/* ULONG  SFIB6_RM_AddSameStaticRoute(IN6ADDR_S *  pstDstAddr, ULONG ulMaskLen); */
ULONG  SFIB6_RM_AddSameStaticRoute(ULONG ulZoneId, IN6ADDR_S *  pstDstAddr, ULONG ulMaskLen);
/* End:VISP V3R2C10 VRF chandra , 2014-03-18 */

/* extern ULONG TCPIP_Get_PreConfigPara(VISP_PRECFG_VALUE_S *pstComPara); */

VOID SFIB6_ShowFIB(VOID);
VOID SFIB6_ShowFIBByVrf(ULONG ulZoneId);
VOID DCLRTM_ShowFIB6(ULONG ulZoneId);
/* Begin:VISP V3R2C10 VRF chandra , 2014-03-18 */
/* VOID SFIB6_ShowRIB(VOID) */
VOID SFIB6_ShowRIB(ULONG ulZoneId);
/* End:VISP V3R2C10 VRF chandra , 2014-03-18 */
ULONG SFIB6_ExactEnable(TCPIP_CFG_RT_EXACT_S  *pstRtMsg);
ULONG SFIB6_ExactDisable(TCPIP_CFG_RT_EXACT_S  *pstRtMsg);
ULONG SFIB6_EnableRt6ByIfNextHop(TCPIP_CFG_RT_BYNH_S  *pstRtMsg);
ULONG SFIB6_DisableRt6ByIfNextHop(TCPIP_CFG_RT_BYNH_S  *pstRtMsg);
ULONG SFIB6_Route_Check(TCPIP_CFG_RT_EXACT_S *pstRtMsg);

ULONG SFIB6_Check_IfType(ULONG ulIfIndex);
/* Begin:VISP V3R2C10 VRF chandra , 2014-03-18 */
/* ULONG SFIB6_AddNetRt(TCPIP_NET_RT6_S *pstNetRouter); */
ULONG SFIB6_AddNetRt(ULONG ulZoneId, TCPIP_NET_RT6_S *pstNetRouter);
/* ULONG SFIB6_DelNetRt(TCPIP_NET_RT6_S *pstNetRouter); */
ULONG SFIB6_DelNetRt(ULONG ulZoneId, TCPIP_NET_RT6_S *pstNetRouter);
/* ULONG SFIB6_AddNetRoute(TCPIP_NET_RT6_S *pstNetRouter); */
ULONG SFIB6_AddNetRoute(ULONG ulZoneId, TCPIP_NET_RT6_S *pstNetRouter);
/* ULONG SFIB6_DelNetRoute(TCPIP_NET_RT6_S *pstNetRouter); */
ULONG SFIB6_DelNetRoute(ULONG ulZoneId, TCPIP_NET_RT6_S *pstNetRouter);
/* VOID SFIB6_Update_StaticRt_AddNetRt(TCPIP_NET_RT6_S *pstNetRouter); */
VOID SFIB6_Update_StaticRt_AddNetRt(ULONG ulZoneId, TCPIP_NET_RT6_S *pstNetRouter);
/* End:VISP V3R2C10 VRF chandra , 2014-03-18 */

VOID SFIB6_Update_StaticRt_DelNetRt(TCPIP_NET_RT6_S *pstNetRouter);
/* Begin:VISP V3R2C10 VRF chandra , 2014-03-18 */
/* BOOL_T SFIB6_RM_Addr_IsSameNetWork(ULONG ulRtNexthop[LEN_4], ULONG ulIfIndex); */
BOOL_T SFIB6_RM_Addr_IsSameNetWork(ULONG ulZoneId, ULONG ulRtNexthop[LEN_4], ULONG ulIfIndex);
/* ULONG SFIB6_Add_StRoute_With_NextHop(TCPIP_RT6_S *pstStaticRouter); */
ULONG SFIB6_Add_StRoute_With_Intf(ULONG ulZoneId, TCPIP_RT6_S *pstStaticRouter);
/* ULONG SFIB6_Add_StRoute_With_NextHop(TCPIP_RT6_S *pstStaticRouter); */
ULONG SFIB6_Add_StRoute_With_NextHop(ULONG ulZoneId, TCPIP_RT6_S *pstStaticRouter);
/* ULONG SFIB6_Add_StRoute_With_NextHop(TCPIP_RT6_S *pstStaticRouter); */
ULONG SFIB6_Add_StRoute_With_Both(ULONG ulZoneId, TCPIP_RT6_S *pstStaticRouter);
/* End:VISP V3R2C10 VRF chandra , 2014-03-18 */

ULONG SFIB6_Global_Addr_Check(ULONG ulIfIndex,IN6ADDR_S *pstGateway);

ULONG RM_Check_IfType(ULONG ulIfIndex);
ULONG RM_Check_AddNetRt_Exist(TCPIP_NET_RT6_S *pstNetRouter);
/* Begin:VISP V3R2C10 VRF chandra , 2014-03-18 */
/* ULONG SFIB6_NetRt_UpCheck(TCPIP_NET_RT6_S *pstNetRouter); */
ULONG SFIB6_NetRt_UpCheck(ULONG unZoneId, TCPIP_NET_RT6_S *pstNetRouter);
/* End:VISP V3R2C10 VRF chandra , 2014-03-18 */

#endif /*#ifndef _SFIB6_RM_H*/

#ifdef    __cplusplus
}
#endif

