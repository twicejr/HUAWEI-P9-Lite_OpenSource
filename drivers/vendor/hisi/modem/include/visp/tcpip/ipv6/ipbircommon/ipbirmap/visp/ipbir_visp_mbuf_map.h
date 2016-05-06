/***********************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*-----------------------------------------------------------------------
*                              ipbir_visp_mbuf_map.h
*
*    Project Code:  IPOS IR V1R2
*    Version     :  Initial Draft
*    Module Name :  IPB IR
*    Create Date :  2006/08/23
*    Author      :  IPv6 Team
*    Description :  To define VISP specific MBUF macros
*-----------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------
*  2006-08-23  IPv6 Team   Created for defining VISP related MBUF macros
************************************************************************/

#ifndef _IPB_IR_VISP_MBUF_MAPP_H_
#define _IPB_IR_VISP_MBUF_MAPP_H_


#ifdef  __cplusplus
extern "C"{
#endif


ULONG VRPAdapt_MBUF_Get_Tag_EthernetInfo_MacAddr(VOID*pstMBuf,
                                                 UCHAR *pucSrcMacAddress,
                                                 UCHAR  *pucDesMacAddress,
                                                 USHORT usMacAddrLen);







#define IPB_IR_MBUF_ASSIGN_SEND_AT_INDEX(pstMBufM, ulSendAtIndexM)\
        MBUF_ASSIGN_SEND_AT_INDEX(pstMBufM, ulSendAtIndexM)

#define IPB_IR_MBUF_ASSIGN_SEND_IFNET_INDEX(pstMBufM, ulSendIfnetIndexM)\
        MBUF_ASSIGN_SEND_IFNET_INDEX(pstMBufM, ulSendIfnetIndexM)

/*MBUF related */
#define IPB_IR_MBUF_GET_IPV6_NEXTHOPADDR(pstMbuf) \
    ((IN6ADDR_S *)MBUF_GET_IPV6_NEXTHOPADDR(pstMbuf))

#define IPB_IR_MBUF_ASSIGN_IPV6_NEXTHOPADDR(pstMbuf, addr) \
    MBUF_ASSIGN_IPV6_NEXTHOPADDR(pstMbuf, addr)

/* Reason : Compilation change   Mod:Bharath */
#define IPB_IR_MBUF_ASSIGN_IPV6_NEXTHOPMACADDR(pstMbuf,SzMac)\
    MBUF_ASSIGN_IPV6_NEXTHOPMACADDR(pstMbuf,SzMac)

/* Reason : Compilation change   Mod:Bharath */
#define IPB_IR_MBUF_MAKE_MEMORY_CONTINUOUS(pstMBufM, ulLengthM,\
                                                ulModuleIDM, ulResultM)\
    MBUF_MAKE_MEMORY_CONTINUOUS(pstMBufM, ulLengthM, ulModuleIDM, ulResultM)

#define IPB_IR_MBUF_MTOD(pstMBufM, DataTypeM) \
    MBUF_MTOD(pstMBufM, DataTypeM)

#define IPB_IR_FREE_MBUF_CHAIN(pstMbuf) \
    FREE_MBUF_CHAIN(pstMbuf)

#define IPB_IR_MBUF_GET_RECEIVE_IFNET_INDEX(pstMBufM) \
    MBUF_GET_RECEIVE_IFNET_INDEX(pstMBufM)

#define IPB_IR_MBUF_GET_SEND_AT_INDEX(pstMBufM) \
    MBUF_GET_SEND_AT_INDEX(pstMBufM)

#define IPB_IR_MBUF_GET_SEND_IFNET_INDEX(pstMBufM) \
    MBUF_GET_SEND_IFNET_INDEX(pstMBufM)

#define IPB_IR_MBUF_GET_TOTAL_DATA_LENGTH(pstMBufM) \
    MBUF_GET_TOTAL_DATA_LENGTH(pstMBufM)

#define IPB_IR_MBUF_CLEAR_FLAG(pstMBufM, ulFlagM) \
    MBUF_CLEAR_FLAG(pstMBufM, ulFlagM)

#define IPB_IR_MBUF_FLAG_MULTICAST \
    MBUF_FLAG_MULTICAST

#define IPB_IR_MBUF_TYPE_DATA \
    MBUF_TYPE_DATA

/*#define  IPB_IR_MBUF_TR_ICMP6_DELIVEREDTOUP \
             MBUF_TR_ICMP6_DELIVEREDTOUP*/


/*Functions */

#define IPB_IR_MBUF_DESTROY( pstMbuf) \
    MBUF_Destroy(pstMbuf)


#define IPB_IR_MBUF_CREATEFORCONTROLPACKET(ulReserveHeadSpace, ulLength, ulType, \
                ulModuleID) \
    MBUF_CreateForControlPacket(ulReserveHeadSpace, ulLength, ulType,ulModuleID)

#define IPB_IR_MBUF_COPYDATAFROMMBUFTOBUFFER(pstMBuf, ulOffset, ulLength, \
                pucBuffer) \
    MBUF_CopyDataFromMBufToBuffer(pstMBuf, ulOffset, ulLength, pucBuffer)

#define IPB_IR_MBUF_CUTTAIL(pstMBuf, ulLength) \
    MBUF_CutTail(pstMBuf, ulLength)


#define  IPB_IR_MBUF_RAWCOPY(pstMbuf, ulOffset, ulLength, ulReserveHeadSpace,\
    ulModuleID) \
    MBUF_RawCopy(pstMbuf, ulOffset, ulLength, ulReserveHeadSpace,ulModuleID)

/*Removed by wan,VISP don't support mbuf tr for distributed system, 2006-12-02*/
/*#define IPB_IR_MBUF_TR_SEND(pstMBuf, ulReceiverBoardId,  ulReceiverId, \
                ulAttachMessage) \
    MBUF_TR_SEND(pstMBuf, ulReceiverBoardId,  ulReceiverId, ulAttachMessage)*/

/*Maruthi : modified ON 2006 sep 04*/
/*#define IPB_IR_MBUF_TR_REGISTERRECEIVER(ulReceiverId,pucReceiverQueueNameA, \
                               pfReceiverNotifyFunction )\
    MBUF_TR_REGISTERRECEIVER(ulReceiverId,pucReceiverQueueNameA, pfReceiverNotifyFunction )*/


#define IPB_IR_MBUF_CONCATENATE(pstDestinationMBuf, pstSourceMBuf, ulModuleID) \
    MBUF_Concatenate(pstDestinationMBuf, pstSourceMBuf, ulModuleID)

#define IPB_IR_MBUF_APPENDMEMORYSPACE(pstMBuf, ulLength, ulModuleID) \
    MBUF_AppendMemorySpace (pstMBuf, ulLength, ulModuleID)

/*This API should be provided in system  */
#define IPB_IR_MBUF_GET_TAG_NETWORK_IP6_PACKET_TYPE(pstMbuf) \
    ((MBUF_IP6_PACKET_INFO_S *)MBUF_GET_TAG_NETWORK_IP6_PTR(pstMbuf))->ulIpPktType

#define IPB_IR_MBUF_SET_TAG_NETWORK_IP6_PACKET_TYPE(pstMbuf, ulPktType) \
{\
    ((MBUF_IP6_PACKET_INFO_S *)MBUF_GET_TAG_NETWORK_IP6_PTR(pstMbuf))->ulIpPktType = (ulPktType);\
}


 #define IPB_IR_MBUF_ASSIGN_RECEIVE_IFNET_INDEX(pstMBufM, ulReceiveIfnetIndexM) \
    MBUF_ASSIGN_RECEIVE_IFNET_INDEX(pstMBufM, ulReceiveIfnetIndexM)

#define IPB_IR_MBUF_COPYDATAFROMBUFFERTOMBUF(pstMBuf, ulOffset,  ulLength,  pucBuffer, \
            ulModuleID) \
    MBUF_CopyDataFromBufferToMBuf(pstMBuf, ulOffset,  ulLength,  pucBuffer, ulModuleID)

#define IPB_IR_MBUF_CREATEBYCOPYBUFFER(pstMBuf, ulOffset,  ulLength,  pucBuffer, \
            ulModuleID) \
    MBUF_CreateByCopyBuffer(pstMBuf, ulOffset,  ulLength,  pucBuffer, ulModuleID)

#define IPB_IR_MBUF_CUT_HEAD(pstMBufM, ulLengthM) \
    MBUF_CUT_HEAD(pstMBufM, ulLengthM)

#define  IPB_IR_MBUF_PREPEND_MEMORY_SPACE(pstMBufM, ulLengthM, ulModuleIDM, ulResultM)\
    MBUF_PREPEND_MEMORY_SPACE(pstMBufM, ulLengthM, ulModuleIDM, ulResultM)

#define IPB_IR_MBUF_CUTPART(pstMbuf, ulOffset, ulLength) \
    MBUF_CutPart(pstMbuf, ulOffset, ulLength)

#define IPB_IR_MBUF_REFERENCECOPY(pstMbuf, ulOffset, ulLength, ulModuleID) \
    MBUF_ReferenceCopy(pstMbuf, ulOffset, ulLength, ulModuleID)

#define IPB_IR_MBUF_NEATCONCATENATE_CHAIN(pstMbuf,ulModuleID) \
    MBUF_NeatConcatenate_Chain(pstMbuf,ulModuleID)


/*Changed by karthik: To set the Encapsulated IPSEC6 flag in MBUF AM Flag*/
#define IPB_IR_MBUF_SET_AMFLAG(pstMBufM, ulFlagM)\
            MBUF_SET_AMFLAG(pstMBufM, ulFlagM)

/* Here we do nothing as IPSEC6 is not supported in VISP and the FLAG is
  required only for IPSEC6*/

/* This flag has to be moved to IPOS_MBUF.H later TBDONE*/
#define MBUF_AMFLAG_IPSEC6_ENCAPSULATED_IPV6    0x00000200



#define IPB_IR_MBUF_GET_TAG_ETHERNETINFO_MACADDR(pstMBuf, pucSrcMacAddress, pucDesMacAddress, usMacLen) \
     VRPAdapt_MBUF_Get_Tag_EthernetInfo_MacAddr(pstMBuf, pucSrcMacAddress, pucDesMacAddress, usMacLen)



#define IPB_IR_MBUF_GET_DATA_BLOCK_DESC(pstMBufM) \
            MBUF_GET_DATA_BLOCK_DESC(pstMBufM)

#define IPB_IR_MBUF_ASSIGN_QUEUE_ID(pstMBufM, ulQueIDM) \
            MBUF_ASSIGN_QUEUE_ID(pstMBufM, ulQueIDM)

#define IPB_IR_MBUF_GET_FLAG(pstMBufM)    MBUF_GET_FLAG(pstMBufM)

#define IPB_IR_MBUF_SET_FLAG(pstMBufM, ulFlagM) \
            MBUF_SET_FLAG(pstMBufM, ulFlagM)

/*NO VPN support in VISP */
#define IPB_IR_MBUF_GET_TAG_MPLS_VPNID(psMBufM, ulXId)
#define IPB_IR_MBUF_SET_TAG_MPLS_VPNID(psMBufM, ulXId)

#define IPB_IR_MBUF_FLAG_CONF    MBUF_FLAG_CONF  /*for ipsec, packet has been encrypted*/
#define IPB_IR_MBUF_FLAG_AUTH          MBUF_FLAG_AUTH  /*for ipsec, packet has been authenticated*/
#define IPB_IR_MBUF_FLAG_ENCAPSULATED  MBUF_FLAG_ENCAPSULATED  /*for ipsec outbound packet*/
#define IPB_IR_MBUF_AMFLAG_DECAPSULATED MBUF_AMFLAG_DECAPSULATED


#define IPB_IR_MBUF_ADJUST_DB(pstMBufM)
    
/*Commented by Prateek for change in MBUF structure*/
#if (VRP_YES == TCPIP_IN_VRP)
    MBUF_ADJUST_DB(pstMBufM)
#endif

/* Include Product Header files - Based on the selected Product */
#if (IPB_IR_PRODUCT_TYPE == IPB_IR_PRODUCT_VISP)

#include "ipbircommon/ipbirmap/visp/visp/ipbir_visp_mbuf.h"

#elif (IPB_IR_PRODUCT_TYPE == IPB_IR_PRODUCT_NODE_B)

#include "ipbircommon/ipbirmap/visp/nodeb/ipbir_nodeb_mbuf.h"

#else /* Unknown product */

/* Unknown product */
#error Unknown Product, Please select a product in ipbir_product.h and build

#endif

#ifdef __cplusplus
}
#endif /* end of __cplusplus */

#endif /* end of _IPB_IR_VISP_MBUF_MAPP_H_ */

