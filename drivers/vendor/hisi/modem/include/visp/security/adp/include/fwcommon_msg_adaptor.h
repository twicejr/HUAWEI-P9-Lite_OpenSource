



#if (NAT_WVISP == 1)

#include "security/wvisp_adapter/include/fwcommon_msg_adaptor.h"

#elif (NAT_RPU == 1)

#include "security/rpu_adapter/include/fwcommon_msg_adaptor.h"

#else

#ifndef _FWCOMMON_MSG_ADP_H_
#define _FWCOMMON_MSG_ADP_H_

#ifdef  __cplusplus
    extern "C"{
#endif


/* Intermediate Processing will continue processing and will own the packet
 * PP need to process the packet further
 */
#ifndef IP_PP4_NOT_PROCESSED_BY_INTERMEDIATE
#define IP_PP4_NOT_PROCESSED_BY_INTERMEDIATE              0 
#endif

/* intermediate found the packet has Error, Stack will Destroy the Packet */
#ifndef IP_PP4_INTER_PROCESS_ERROR
#define IP_PP4_INTER_PROCESS_ERROR                        1
#endif

/* Intermediate Processing will continue processing and will own the packet
 * PP do not need to process the packet any more
 */
#ifndef IP_PP4_PROCESSED_BY_INTERMEDIATE
#define IP_PP4_PROCESSED_BY_INTERMEDIATE                  2 
#endif

/*No layer*/
#define  FW_PKT_NO_LAYER   0x00

/*Mac Layer*/
#define  FW_PKT_LAYER_MAC  0x01

/*IP Layer*/
#define  FW_PKT_LAYER_IP   0x02

/*IP and MAC Layer*/
#define  FW_PKT_LAYER_ALL  (FW_PKT_LAYER_MAC|FW_PKT_LAYER_IP)

/*This macro is defined here to get the firewall common packet info from input packet structure. Only mac based info*/
#define FWCOMMON_ADEXT_GETPACKETINFO(boundtype) (FWCOMMON_GetPacketInfo(pstMBuf,&stPacketInfo,boundtype,FW_PKT_LAYER_MAC))

/*This macro is defined here to get the physical address position from the given FWCOMMON_IPPACKETINFO_S structure pointer*/
#define FWCOMMON_PACKETINFO_GET_MACHEADER(pstPacketInfo) ((UINT8*)pstPacketInfo + sizeof(UINT32)*8)
   
/**
* @defgroup tagFW_pkt_type FW_PKT_INOUT_TYPE_E
* @ingroup Packet Adaptor Enums
* @par Prototype
* @code
* typedef enum tagFW_pkt_type
* {
*     FW_INBOUND_TYPE=0x0,
*     FW_OUTBOUND_TYPE,
*     FW_MAX_TYPE
* }FW_PKT_INOUT_TYPE_E;
* @endcode 
* 
* @par Description
* This enum consists of packet type values.
*
* @datastruct FW_INBOUND_TYPE=0x0 Indicates Inbound packet type
* @datastruct FW_OUTBOUND_TYPE Indicates Outbound packe type 
*/
typedef enum tagFW_pkt_type
{
    FW_INBOUND_TYPE = 0x0,
    FW_OUTBOUND_TYPE,
    FW_MAX_TYPE
}FW_PKT_INOUT_TYPE_E;


/**
* @defgroup enumFWCommonMsgAdaptorErrCode FWCOMMON_MSG_ADAPTOR_ERR_CODE_E
* @ingroup Packet Adaptor Enums
* @par Prototype
* @code
* typedef enum enumFWCommonMsgAdaptorErrCode
* {
*   FWCOMMON_MSGADAPTOR_OK = 0,
*   FWCOMMON_MSGADAPTOR_MBUF_SHORTER_THAN_L3 = 0 + 1 ,
*   FWCOMMON_MSGADAPTOR_MBUF_SHORTER_THAN_L4,
*   FWCOMMON_MSGADAPTOR_IPHEDER_LENGTH_INVALID,
*   FWCOMMON_MSGADAPTOR_MBUF_SHORTER_THAN_L2,
*   FWCOMMON_MSGADAPTOR_MBUF_SHORTER_THAN_L2_VLAN,
*   FWCOMMON_MSGADAPTOR_MBUF_SHORTER_THAN_L2_VLAN_SNAP,
*   FWCOMMON_MSGADAPTOR_MBUF_SHORTER_THAN_L2_SNAP,
*   FWCOMMON_MSGADAPTOR_MBUF_LAYER_NOT_ALLOW,
*   FWCOMMON_MSGADAPTOR_INBOUND_PKT_CONTEXT_NULL,
* }FWCOMMON_MSG_ADAPTOR_ERR_CODE_E;
* @endcode 
* 
* @par Description
* This enum defines the Message Adapter error codes
*
* @datastruct FWCOMMON_MSGADAPTOR_OK=0 Indicates operation success.
* @datastruct FWCOMMON_MSGADAPTOR_MBUF_SHORTER_THAN_L3=1 Indicates error occured if packet length is very sort at 
* Layer 3.
* @datastruct FWCOMMON_MSGADAPTOR_MBUF_SHORTER_THAN_L4 Indicates error occured if packet length is very sort at 
* Layer 4.
* @datastruct FWCOMMON_MSGADAPTOR_MBUF_SHORTER_THAN_L2 Indicates error occured if packet length is very sort at Layer2.
* @datastruct FWCOMMON_MSGADAPTOR_MBUF_SHORTER_THAN_L2_VLAN Indicates error if ethernet header 18 bytes are not 
* present. 
* @datastruct FWCOMMON_MSGADAPTOR_MBUF_SHORTER_THAN_L2_VLAN_SNAP Indicates error if ethernet header is not 26 bytes in 
* case of SNAP type.  
* @datastruct FWCOMMON_MSGADAPTOR_MBUF_SHORTER_THAN_L2_SNAP Indicates error if ethernet eader is not 22 bytes in case 
* SNAP type and non ETHII.
* @datastruct FWCOMMON_MSGADAPTOR_MBUF_LAYER_NOT_ALLOW Indiecates error if input layer is not supported or invalid.
* @datastruct FWCOMMON_MSGADAPTOR_INBOUND_PKT_CONTEXT_NULL Indicates error if input packet context is null.
*/
typedef enum enumFWCommonMsgAdaptorErrCode
{
    FWCOMMON_MSGADAPTOR_OK = 0,
    FWCOMMON_MSGADAPTOR_MBUF_SHORTER_THAN_L3 = 0 + 1 ,
    FWCOMMON_MSGADAPTOR_MBUF_SHORTER_THAN_L4,
    FWCOMMON_MSGADAPTOR_IPHEDER_LENGTH_INVALID,
    FWCOMMON_MSGADAPTOR_MBUF_SHORTER_THAN_L2,
    FWCOMMON_MSGADAPTOR_MBUF_SHORTER_THAN_L2_VLAN,
    FWCOMMON_MSGADAPTOR_MBUF_SHORTER_THAN_L2_VLAN_SNAP,
    FWCOMMON_MSGADAPTOR_MBUF_SHORTER_THAN_L2_SNAP,
    FWCOMMON_MSGADAPTOR_MBUF_LAYER_NOT_ALLOW,
    FWCOMMON_MSGADAPTOR_INBOUND_PKT_CONTEXT_NULL,
} FWCOMMON_MSG_ADAPTOR_ERR_CODE_E;


/**
* @defgroup tagFWCOMMON_IPPacketInfo FWCOMMON_IPPACKETINFO_S
* @ingroup Packet adaptor structures
* @par Prototype
* @code
* typedef struct tagFWCOMMON_IPPacketInfo
* {
*     UINT32 u32SIP;           
*     UINT32 u32DIP;           
*     UINT16 u16SP;            
*     UINT16 u16DP;       
*     UINT16 u16FO;            
*     UINT16 u16FM;       
*     UINT8  u8PID;            
*     UINT8  u8PRE;            
*     UINT8  u8TOS;            
*     UINT8  u8DSCP;      
*     UINT32 u32IfIndex;       
*     UINT32 u32IgnoreByte;    
*     UINT32 u32VrfIndex; 
*     union
*     {
*         UINT8 u8Mac[12];     
*         UINT16 u16Mac[6];
*         UINT32 u32Mac[3];
*     } unMac; 
*     UINT16 u16VlanId;
*     UINT16 u16Padding;
*     UINT16 u16MacPayLoadType;
*     UINT8 u8NeedCheckType;   
*     UINT8 u8LayerFlag;  
*     UINT16 u16IPPktTotLen;   
*     UINT8  u8TcpFlag;        
*     UINT8  u8Padding;   
*     UINT8  *pu8ProtoData;    
*     UINT32 u32ProtoDataLen;  
*     UINT8  *pu8MBuf;        
*     UINT64 u64CheckTime;    
*     FWIPSAFE_IP_S *pstIPData; 
* } FWCOMMON_IPPACKETINFO_S, *PFWCOMMON_IPPACKETINFO_S;
*
* 
* @par Description
* This structure ACL Rule information 
*
* @datastruct u32SIP SourceIP
* @datastruct u32DIP DestinationIP
* @datastruct u16SP SourcePort
* @datastruct u16DP DestinationPort
* @datastruct u16FO Fragment offset. Zero if nonfragment or initial fragment.
* @datastruct u16FM reserved. it is used for accurately match before.
* @datastruct u8PID protocol ID for IP payload 
* @datastruct u8PRE Precedenace
* @datastruct u8TOS TOS
* @datastruct u8DSCP DSCP
* @datastruct u32IfIndex Interface Index
* @datastruct u32IgnoreByte the byte used to indicate which field should be ingored
* @datastruct u32VrfIndex VRF Index
* @datastruct unMac Source and Destination Mac
* @datastruct u16VlanId VLANID of the recieved packet
* @datastruct u16Padding Added for Padding
* @datastruct u16MacPayLoadType Protocol ID for MAC payload
* @datastruct u8NeedCheckType Check type for MAC based ACL
* @datastruct u8LayerFlag the layer information for the packet. 0x01: mac layer; 0x02: IP layer; 0x03: both layer
* @datastruct u16IPPktTotLen IP packet total length
* @datastruct u8TcpFlag TCP flag
* @datastruct u8Padding padding
* @datastruct *pu8ProtoData The data pointer from the mac data pointer + 12
* @datastruct u32ProtoDataLen The data length of the protodata
* @datastruct *pu8MBuf the pointer to protocol mbuf data
* @datastruct pstIPData Pointer of IP packet data
*
* @par Note
* If any parameter is added or deleted in this structure FWCOMMON_PACKETINFO_GET_MACHEADER must be adjusted.
*/
typedef struct tagFWCOMMON_IPPacketInfo
{
    UINT32 u32SIP;           
    UINT32 u32DIP;           
    UINT16 u16SP;            
    UINT16 u16DP;            
    UINT16 u16FO;            
    UINT16 u16FM;                
    UINT8  u8PID;            
    UINT8  u8PRE;            
    UINT8  u8TOS;            
    UINT8  u8DSCP;           
    UINT32 u32IfIndex;       
    UINT32 u32IgnoreByte;    
    UINT32 u32VrfIndex;      
    union
    {
        UINT8 u8Mac[12];     
        UINT16 u16Mac[6];
        UINT32 u32Mac[3];
    } unMac; 
    UINT16 u16VlanId;
    UINT16 u16Padding;
    UINT16 u16MacPayLoadType;
    UINT8 u8NeedCheckType; 
    UINT8 u8LayerFlag;     
    UINT16 u16IPPktTotLen; 
    UINT8  u8TcpFlag;      
    UINT8  u8Padding;      
    UINT8  *pu8ProtoData;  
    UINT32 u32ProtoDataLen;    
    UINT8  *pu8MBuf;
    UINT64 u64CheckTime;
    FWIPSAFE_IP_S *pstIPData;           
} FWCOMMON_IPPACKETINFO_S, *PFWCOMMON_IPPACKETINFO_S;

/**
* @defgroup FWCOMMON_GetPacketInfo FWCOMMON_GetPacketInfo
* @ingroup Packet Adaptor
* @par Prototype
* @code
* UINT32 FWCOMMON_GetPacketInfo(VOID* pMBuf,
                                FWCOMMON_IPPACKETINFO_S * pstPackInfo,
                                FW_PKT_INOUT_TYPE_E       enInOutType,
                                UINT32                    u32Layer);
* @endcode 
* 
* @par Description
* This function is used to get the inner packet structure from the input message buffer. 
* 
* @param[in] pMBuf protocol stack message buffer
* @param[in] enInOutType FW_INBOUND_TYPE or FW_OUTBOUND_TYPE
* @param[in] u32Layer for which layer, it is called. It can be FW_PKT_LAYER_MAC, FW_PKT_LAYER_IP.
* @param[out] pstPackInfo inner packet structure. The memory should be allocated by application.
*
* @retval UINT32 Successful [FWCOMMON_MSGADAPTOR_OK|]
* @retval UINT32 Appropriate error code from FWCOMMON_MSG_ADAPTOR_ERR_CODE_E[]
* 
* @par Dependency

* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* FWCOMMON_DestroyPacket
*/ 
extern UINT32 FWCOMMON_GetPacketInfo(VOID*                   pMBuf,
                                     FWCOMMON_IPPACKETINFO_S * pstPackInfo,
                                     FW_PKT_INOUT_TYPE_E       enInOutType,
                                     UINT32                    u32Layer);

/**
* @defgroup FWCOMMON_DestroyPacket FWCOMMON_DestroyPacket
* @ingroup Packet Adaptor
* @par Prototype
* @code
* UINT32 FWCOMMON_DestroyPacket(VOID* pMBuf);
* @endcode 
* 
* @par Description
* Destroy the packet which is rejected by firewall
* 
* @param[in] pMBuf protocol stack message buffer
* 
*
* @retval  [|]
* 
* @par Dependency
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* FWCOMMON_GetPacketInfo
*/ 
void          FWCOMMON_DestroyPacket(VOID* pMBuf);


/*******************************************************************************
* Func Name: IPSAFE_ADP_GetFlowNum
*  Description: Gets the flow number of received packet.
*  Input: VOID* pstMBuf: protocol stack message buffer
*  Output: None.
*  Return: UINT32 : FWIPSAFE_OK - Flow statistics are not needed
*                           Else, Flow statistic number
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-08-06   eswar 72335                Create
*
*******************************************************************************/
UINT32 IPSAFE_ADP_GetFlowNum(VOID* pstMBuf);

/*******************************************************************************
* Func Name: IPSAFE_ADP_GetFlowId
*  Description: Gets the flow number of received packet.
*  Input: VOID* pstMBuf: protocol stack message buffer
*         UINT32 u32FlowStatNum: flow statistics number
*  Output: UINT32 u32TempFlowId: Flow ID for received packet
*  Return: UINT32 : FWIPSAFE_OK - Flow ID sent successfully
*                           Else, Flow ID is not in the range.
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-08-06   eswar 72335                Create
*
*******************************************************************************/
UINT32 IPSAFE_ADP_GetFlowId(VOID* pstMBuf, UINT32 u32FlowStatNum, UINT32 u32TempFlowId);

/*******************************************************************************
* Func Name: IPSAFE_ADP_GetMaxFlows
*  Description: Gets the maximum number of flows.
*  Input: None
*  Output: None
*  Return: UINT32 : FWIPSAFE_OK - Flow statistics are not initialized
*                           Else, Maximum number of flows.
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-08-06   eswar 72335                Create
*
*******************************************************************************/
UINT32 IPSAFE_ADP_GetMaxFlows();

/*******************************************************************************
* Func Name: IPSAFE_ADP_IsFlowIDValid
*  Description: Checks whether the given flow ID is valid or not.
*  Input: UINT32 u32FlowID: Flow ID. 
*  Output: None
*  Return: UINT32 : FWIPSAFE_OK - Given flow ID is valid.
*                           Else, Given flow ID is not valid.
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-08-06   eswar 72335                Create
*
*******************************************************************************/
UINT32 IPSAFE_ADP_IsFlowIDValid(UINT32 u32FlowID);

/*******************************************************************************
* Func Name: IPSAFE_ADP_GetSubNetMaskLen
*  Description: Gets the subnet mask length of destination IP .
*  Input: PFWCOMMON_IPPACKETINFO_S pstPacketInfo: Inner packet structure. 
*  Output: None
*  Return: UINT32 : FWIPSAFE_OK - Not able to get mask as entry is not there in routing table.
*                           Else, Sub net mask length.
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-08-06   eswar 72335                Create
*
*******************************************************************************/
UINT32 IPSAFE_ADP_GetSubNetMaskLen (PFWCOMMON_IPPACKETINFO_S pstPacketInfo);

/**
* @defgroup AD_IPSpoofing_Sh AD_IPSpoofing_Sh
* @ingroup ADF Attack Defense Functions
* @par Prototype
* @code
* UINT32 AD_IPSpoofing_Sh(PFWCOMMON_IPPACKETINFO_S pstPacketInfo);
* @endcode 
* 
* @par Description
* This function will decide whether source IP is spoofed.
* 
* @param[in] pstPacketInfo This parameter is pointer to packet structure.[]
* @param[out]   []
*
* @retval UINT32 No IP Spoofing detected [AD_OK|]
* @retval UINT32 Indicates the source address is a broadcast address [FWCOMMON_MSGADAPTOR_BROADCAST_IPSPOOFING_SH|]
* @retval UINT32 Indicates the source address does not exist in FIB table [FWCOMMON_MSGADAPTOR_IP_NOT_IN_FIB_IPSPOOFING_SH|]
* @retval UINT32 Indicates the received interface of the packet is different with the interface to 
* send a packet to the source IP [FWCOMMON_MSGADAPTOR_INTERFACE_NOT_SAME_IPSPOOFING_SH|]
*
* @par Dependency
* ad_inc.h
* 
* 
* @par Note
* \n
* 
* This function will not check the validation of input parameter, caller to this function should 
* ensure the validation of input.
* 
* 
* @par Related Topics
* None
*/
UINT32 AD_IPSpoofing_Sh(PFWCOMMON_IPPACKETINFO_S pstPacketInfo);

/******************************************************************************
Function        : FWCOMMON_Hook
Description     : This function will hook firewall functions to the layers
Calls           : SFE_RegFuncAclFilterHook
Called By       : 
Input           : 
Output          : 
Return          : UINT32 Hook success
                         Hook failure
Tailorability   : This function can not be tailored
Performance     : 
Others          : None
*******************************************************************************/
UINT32 FWCOMMON_Hook(VOID);

/******************************************************************************
Function        : ACLFW_Hook
Description     : This function will ACL filter.
Input           : 
Output          : 
Return          : UINT32 Hook success
                         Hook failure
Tailorability   : This function can not be tailored
Performance     : 
Others          : None
*******************************************************************************/
UINT32 ACLFW_Hook(VOID);

/******************************************************************************
Function        : IPSAFE_ADP_MbufGetRcvIFIndex
Description     : This function will gets recieved interface index of given packet.
Input           : VOID *pstMbuf: protocol stack message buffer.
                : ULONG ulInIfIndex: variable to store interface index.
Output          : 
Return          : 
Tailorability   : This function can not be tailored
Performance     : 
Others          : None
*******************************************************************************/
VOID IPSAFE_ADP_MbufGetRcvIFIndex(VOID *pstMbuf,ULONG ulInIfIndex);

/*******************************************************************************
*    Func Name: ACL_GetIfNameByIffIndex
* Date Created: 2009-10-27
*       Author: Kurt
*  Description: This function is used to convert input interface index to string 
*        Input: ULONG ulIfIndex: interface index. 
*       Output: CHAR * pszIfName: Interface index as string 
*       Return: Help_ACL_OK
*               Help_ACL_ERR
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-27     Kurt                 create 
*******************************************************************************/
ULONG ACL_GetIfNameByIffIndex(ULONG ulIfIndex, CHAR * pszIfName);


/*===========================================================================*\
    Function    :IPSAFE_ADP_GetIfIndexByFullName
    Description :This function gets interface index for given interface full name
    Return      :ULONG - success/Failure
    Parameters  :
        CHAR *pszIfName - 
        ULONG *pulIfIndex - 
    Note        :
\*===========================================================================*/
ULONG IPSAFE_ADP_GetIfIndexByFullName(CHAR *pszIfName, ULONG *pulIfIndex);

/*===========================================================================*\
    Function    :IPSAFE_ADP_GetVrfIndexByName
    Description :This function gets vrf index for given vrf name
    Return      :ULONG - 
    Parameters  :
        CHAR * pszVrfName - 
        ULONG * pulVrfIndex - 
    Note        :
\*===========================================================================*/
ULONG IPSAFE_ADP_GetVrfIndexByName(CHAR * pszVrfName, ULONG *pulVrfIndex);

/*===========================================================================*\
    Function    :IPSAFE_ADP_GetVrfNameByVrfIndex
    Description :This function gets vrf name for given vrf index
    Return      :ULONG - 
    Parameters  :
        ULONG ulVrfIndex - 
        CHAR * pszVrfName - 
    Note        :
\*===========================================================================*/
ULONG IPSAFE_ADP_GetVrfNameByVrfIndex(ULONG ulVrfIndex, CHAR *pszVrfName);

/*===========================================================================*\
    Function    :IPSAFE_ADP_GetVrfIndexByIfIndex
    Description :This function gets vrf index for given interface index
    visp_cp
    Return      :ULONG - 
    Parameters  :
        ULONG ulIfIndex - 
        ULONG * pulVrfIndex - 
    Note        :
\*===========================================================================*/
ULONG IPSAFE_ADP_GetVrfIndexByIfIndex(ULONG ulIfIndex, ULONG *pulVrfIndex);


#ifdef  __cplusplus
}
#endif




#endif

#endif
