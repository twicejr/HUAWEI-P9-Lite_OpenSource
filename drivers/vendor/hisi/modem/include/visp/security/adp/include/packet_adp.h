

#if (NAT_WVISP == 1)

#include "security/wvisp_adapter/include/packet_adp.h"

#elif (NAT_RPU == 1)

#include "security/rpu_adapter/include/packet_adp.h"
#else

#ifndef _PACKET_ADP_H_
#define _PACKET_ADP_H_

#ifdef  __cplusplus
    extern "C"{
#endif

typedef VOID * PKT_HANDLE;   /* packet handle, different product enviroment packet format maybe different */

struct tagFlowContext;

#define IPSAFE_FLOWSTAT_MATCH_MAX 7

/*Data packet flow statistical information surface structure definition*/
typedef struct tagIPSAFE_FLOWSTATISTIC
{    
    UINT16 u16FlowStatNum; /* packet statistics to meet the current number */
    UINT16 u16FlowStat [IPSAFE_FLOWSTAT_MATCH_MAX]; /* packets to meet the flow statistics ID */
} IPSAFE_FLOWSTATISTIC_S;
/* for RPU only support 66 bytes */
typedef struct tagPktContext
{
    struct tagFlowContext *pstFlowContext;  /* Flow context structure*/
    PKT_HANDLE pktHandle;                   /* Packet Handle*/
    INTF_HANDLE intfHandle;                 /* Interface Handle*/
    UINT32 *pu32SrcIP;                      /* source IP pointer*/
    UINT32 *pu32DstIP;                      /* destination IP pointer*/
    UINT16 *pu16SrcPort;                    /* source Port pointer*/
    UINT16 *pu16DstPort;                    /* destination Port pointer*/
    UINT8  *pu8Protocol;                    /* IP header Protocol*/
    UINT16 *pu16IPCheckSum;                 /* IP header check sum*/
    UINT16 *pu16TCPOrUDPCheckSum;           /* transport header checksum*/
    UINT32 *pu32TCPSeqNum;                  /* TCP sequence Number*/
    UINT32 *pu32TCPAckNum;                  /* TCP Acknowledge Number*/
    UINT16 *pu16PktLen;                     /* Packet Len*/
    UINT16 *pu16UDPLen;                     /* Only for UDP packet. Points to the UDP packet length field in UDP Header*/
    VOID*   pPaylodData;                    /* Begining of the Payload data pointer*/
    UINT16   u16FragFlag;                   /* Fragmentation Flag */
    UINT8    u8IPHdrLen;                    /* IP Header Len*/
    UINT8    u8ProHdrLen;                   /* Protocol Header Len*/
    UINT8    u8TCPFlagByte;                 /* TCP Flag*/ 
    UINT8    u8Direction;                   /* packet direction */
    UINT8    u8Res[2];                      /* For 4 byte alignment*/
    
    UINT32  u32VpnIndex;                    /* VPN Index*/
    IPSAFE_IP_S *pstIpHdr;                  /* Pointer to IP header structure*/

    UINT32 u32IsFlowStatistic;              /*Does this packet need flow statistics*/
    IPSAFE_FLOWSTATISTIC_S stFlowStat;      /*Flow Statistics*/
}PKT_CONTEXT_S; 



/*******************************************************************************
*    Func Name: IPSAFE_ADP_GetPktContext
* Date Created: 2010-03-25
*       Author: zhangchunyu(62474)
*      Purpose: Get packet context info by packet handle
*  Description: Get packet context info by packet handle, user need provide packet context memory
*        Input: PKT_HANDLE pktHandle: packet handle<product packet format>
*       Output: 
*       Return: VOID
*      Caution: 
*        Since: V100R008C03
*    Reference: NAT_In
*               NAT_Forward
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-03-25   zhangchunyu(62474)      Create the first version.
*
*******************************************************************************/
VOID * IPSAFE_ADP_GetPktContext(PKT_HANDLE pktHandle);

/*******************************************************************************
*    Func Name: IPSAFE_ADP_PktReplace
* Date Created: 2010-03-25
*       Author: zhangchunyu(62474)
*      Purpose: Replace packet content
*  Description: Replace packet content
*        Input: PKT_HANDLE pktHandle: Packet handle, product interpret the packet<User packet handle>
*               VOID *oldContent: Change old packet begin position<Not null pointer>
*               UINT32 oldLen: Change old length<All int>
*               VOID *newContent: Change new packet begin position<Not null pointer>
*               UINT32 newLen: Change new length<All int>
*       Output: 
*       Return: 0: Success
*               1: Fail
*      Caution: Change contern must be continuous memory
*        Since: V100R008C03
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-03-25   zhangchunyu(62474)      Create the first version.
*
*******************************************************************************/
UINT32 IPSAFE_ADP_PktReplace(PKT_HANDLE pktHandle,
                      VOID *oldContent,
                      UINT32 oldLen,
                      VOID *newContent,
                      UINT32 newLen);

/*******************************************************************************
*    Func Name: IPSAFE_ADP_ACLClassifyPktHandleByNum
* Date Created: 2010-03-29
*       Author: zhangchunyu(62474)
*      Purpose: ACL check packet whether do nat
*  Description: ACL check packet whether do nat
*        Input: PKT_HANDLE pktHandle: packet handle<Not null pointer>
*               UINT32 ulNumber: ACL number group<All int>
*       Output: 
*       Return: 0: Success
*               1: Fail
*      Caution: 
*        Since: V100R008C03
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-03-29   zhangchunyu(62474)      Create the first version.
*
*******************************************************************************/
UINT32 IPSAFE_ADP_ACLClassifyPktHandleByNum(PKT_HANDLE pktHandle, UINT32 ulNumber);

#ifdef  __cplusplus
}
#endif

#endif



#endif

