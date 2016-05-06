

#if (NAT_WVISP == 1)

#include "security/wvisp_adapter/include/fw_acl_adp.h"

#elif (NAT_RPU == 1)

#include "security/rpu_adapter/include/fw_acl_adp.h"
#else

#ifndef _FW_ACL_ADP_H_
#define _FW_ACL_ADP_H_

#ifdef  __cplusplus
extern "C"{
#endif

#ifndef ACL_DENY
#define ACL_DENY            0 
#endif

#ifndef ACL_PERMIT
#define ACL_PERMIT          1
#endif

#ifndef ACL_NOTFOUND
#define ACL_NOTFOUND        2
#endif

#ifndef ACL_BAS_MIN_EXT
#define ACL_BAS_MIN_EXT     2000
#endif

#ifndef ACL_ADV_MAX_EXT
#define ACL_ADV_MAX_EXT     3999
#endif

/**
* @defgroup tagIPPacketInfo IPPACKETINFO_S/PIPPACKETINFO_S
* @ingroup ACLS ACL Structures
* @par Prototype
* @code
* typedef struct tagIPPacketInfo 
* {
*    ULONG ulSIP;
*    ULONG ulDIP;
*    USHORT usSP;
*    USHORT usDP;
*    BOOL_T bFO;
*    BOOL_T bFM;
*    UCHAR ucPID;
*    UCHAR ucPRE;
*    UCHAR ucTOS;
*    UCHAR ucDSCP;
*    ULONG ulIfIndex;
*    ULONG ulIgnoreByte;
*    ULONG ulVrfIndex;
* } IPPACKETINFO_S, *PIPPACKETINFO_S;
* @endcode 
* 
* @par Description
* This structure consists of IP packet information.
* 
* @datastruct ulSIP Indicates source address
* @datastruct ulDIP Indicates destination address
* @datastruct usSP Indicates source port number
* @datastruct usDP Indicates destination port number
* @datastruct bFO Indicates whether packet is fragmented
* @datastruct bFM Indicates whether packet filtering mode is used or not
* @datastruct ucPID Indicates protocol ID
* @datastruct ucPRE Indicates precedence value
* @datastruct ucTOS Indicates TOS value
* @datastruct ucDSCP Indicates DSCP value
* @datastruct ulIfIndex Indicates interface index value
* @datastruct ulIgnoreByte Indicates the byte used to indicate which field should be ingored
* @datastruct ulVrfIndex Indicates VRF index value
*/

/* This structure is used to store information extracted from the IP packet */

#ifndef IPSAFE_IPPACKETINFO_S
#define IPSAFE_IPPACKETINFO_S

typedef struct tagIPPacketInfo 
{
    ULONG ulSIP;              /* Source address */            
    ULONG ulDIP;              /* Destination address */ 
    USHORT usSP;             /* Source port number or ICMP Type */            
    USHORT usDP;             /* Destination port number or ICMP Type*/            
    BOOL_T bFO;               /* non initial fragment flag */
    BOOL_T bFM;               /* reserved. it is used for accurately match before. */
    UCHAR ucPID;             /* Protocol Number  */            
    UCHAR ucPRE;             /* precedence */          
    UCHAR ucTOS;             /* TOS value  */
    UCHAR ucDSCP;           /* DSCP Value */ 
    ULONG ulIfIndex;        /* Interface Index */
    ULONG ulIgnoreByte;     /* the byte used to indicate which field should be ingored */

    /* Begin:VISP1.7C03 VRF wangchengyang,2009-01-20 */
    ULONG ulVrfIndex;           /* Vrf index */
    /* Begin:VISP1.7C03 VRF wangchengyang,2009-01-20 */
} IPPACKETINFO_S, *PIPPACKETINFO_S;

#endif


UINT32 IPSAFE_ADP_ACL_HaveIt(ULONG ulGroupNum, VOID *pMatchInfo, ULONG *pulRuleIndex, BOOL_T *pbLog, BOOL_T bIsCount);

/*******************************************************************************
*    Func Name: IPSAFE_ADP_ACL_ValidateGrp
* Date Created: 2010-06-08
*       Author: Eswar
*  Description: Validate for basic and adavanced acl group
*        Input: ULONG ulGroupNum: ACL group number
*       Output: 
*       Return: UINT32: 0 - Group is valid
*                       1 - Group is invalid
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-08   Eswar      Create the first version.
*
*******************************************************************************/
UINT32 IPSAFE_ADP_ACL_ValidateBasicAdvGrp(UINT32 u32GroupNumber);

#ifdef  __cplusplus
}
#endif

#endif



#endif

