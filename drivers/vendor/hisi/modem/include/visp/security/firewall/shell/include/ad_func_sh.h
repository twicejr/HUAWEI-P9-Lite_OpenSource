/*************************************************************************
*
*              Copyright 2009, Huawei Technologies Co. Ltd.
*                          ALL RIGHTS RESERVED
*
*-----------------------------------------------------------------------*
*
*                              ad_func_sh.h
*
*       Version: DOPRA VISP V1R8C02 Firewall
*   Module Name: IP Spoofing defense module
*  Date Created: 2009-08-08
*        Author: Eswar(r72335)
*   Description: This file contains the declarations Attack Defence shell functions
*                required for processing inbound/outbound packets.
*     Functions: 
*                AD_IPSpoofing_Sh
*                ATK_CheckIPAddrType
*                AD_IsDst_Broadcast_Sh
*
*-----------------------------------------------------------------------*
*  Modification History
*  DATE            NAME            DESCRIPTION
*  2009-08-08      r72335          Created
************************************************************************/

#ifndef _AD_FUN_SH_H_
#define _AD_FUN_SH_H_

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */


/**
* @defgroup AD_IsDst_Broadcast_Sh AD_IsDst_Broadcast_Sh
* @ingroup ADF Attack Defense Functions
* @par Prototype
* @code
* UINT32 AD_IsDst_Broadcast_Sh(PFWCOMMON_IPPACKETINFO_S pstPacketInfo);
* @endcode 
* 
* @par Description
* This function will check whether destination IP is proper it will do below checks
* 1)Loopback
* 2)Invalid
* 3)Broadcast
* 4)Multicast
* 5)Subnet broadcast.
* 
* @param[in] pstPacketInfo This parameter is pointer to packet structure.[]
* @param[out]   []
*
* @retval UINT32 IP is valid [AD_OK|]
* @retval UINT32 Indicates the address is invalid [ATCK_SMURF_STAT|]
*
* @par Dependency
* ad_inc.h
* 
* 
* @par Note
* \n
* 
* This function will not check the validation of input parameter, caller to this function 
* should ensure the validation of input.
* 
* 
* @par Related Topics
* None
*/
extern UINT32 AD_IsDst_Broadcast_Sh(PFWCOMMON_IPPACKETINFO_S pstPacketInfo);

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
* @retval UINT32 Indicates the source address is a broadcast address [AD_BROADCAST_IPSPOOFING_SH|]
* @retval UINT32 Indicates the source address does not exist in FIB table [AD_IP_NOT_IN_FIB_IPSPOOFING_SH|]
* @retval UINT32 Indicates the received interface of the packet is different with the interface to 
* send a packet to the source IP [AD_INTERFACE_NOT_SAME_IPSPOOFING_SH|]
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
extern UINT32 AD_IPSpoofing_Sh(PFWCOMMON_IPPACKETINFO_S pstPacketInfo);

/**
* @defgroup ATK_CheckIPAddrType ATK_CheckIPAddrType
* @ingroup ADF Attack Defense Functions
* @par Prototype
* @code
* UINT32 ATK_CheckIPAddrType(UINT32 u32DstIpAddr, VOID * pstSendIf);
* @endcode 
* 
* @par Description
* This function will give type of given address (Loopback/Invalid/Broadcast/Subnet broadcast).
* 
* @param[in] u32DstIpAddr address needs to be checked.[]
* @param[out]   []
*
* @retval UINT32 IP is valid [AD_OK|]
* @retval UINT32 Indicates the address is a broadcast address [AD_BROADCAST_IPSPOOFING_SH|]
* @retval UINT32 Indicates the address is loop back address [AD_LOOPBACK_DST_SMURF_SH|]
* @retval UINT32 Indicates the address is illegal [AD_ILLEGAL_DST_SMURF_SH|]
* @retval UINT32 Indicates the address is subnet of class-A [AD_DST_SUBNET_OF_CLASS_A_SMURF_SH|]
* @retval UINT32 Indicates the address is subnet of class-B [AD_DST_SUBNET_OF_CLASS_B_SMURF_SH|]
* @retval UINT32 Indicates the address is subnet of class-C [AD_DST_SUBNET_OF_CLASS_C_SMURF_SH|]
* @retval UINT32 Indicates the address is multicasted [AD_MULTICAST_DST_SMURF_SH|]
* @retval UINT32 Indicates the address is invalid [AD_DST_INVLID_SMURF_SH|]
* @retval UINT32 Indicates the address is a subnet broadcast address [AD_DST_SUBNET_BROADCAST_SMURF_SH|]
*
* @par Dependency
* ad_inc.h
* 
* 
* @par Note
* \n
* 
* This function will not check the validation of input parameter, caller to this function 
* should ensure the validation of input.
* 
* 
* @par Related Topics
* None
*/
UINT32 ATK_CheckIPAddrType(UINT32 u32DstIpAddr, VOID * pstSendIf);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _AD_FUN_SH_H_ */
