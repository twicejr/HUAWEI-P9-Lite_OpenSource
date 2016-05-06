/*************************************************************************
 *
 *              Copyright 2009, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 *
 *-----------------------------------------------------------------------*
 *
 *                              fwcommon_preconfig_adaptor.c
 *
 *  Project Code: DOPRA VISP V1R8C02 Firewall
 *   Module Name: fwcommon pre configuration adaptor functions
 *  Date Created: 2009-12-24
 *        Author: Ramalingeswara Reddy 72335
 *   Description: Header file for Providing preconfiguration functions for firewall.
 *
 *   Version : 1
 FWCOMMON_GetPreConfPara
 FWCOMMON_SetPreConfPara
  
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME                          DESCRIPTION
 *  2009-12-24      Ramalingeswara Reddy 72335    Create

 ************************************************************************/
#ifndef _FWCOMMON_PRECONFIG_ADAPTOR_H_
#define _FWCOMMON_PRECONFIG_ADAPTOR_H_

#ifdef  __cplusplus
extern "C" {
#endif

/**
* @defgroup ACLPreConf ACL Pre Configuration
* This section contains the pre-configuration APIs.
*/

/**
* @defgroup ACLPreConfS ACL Pre Configuration Structure
* @ingroup ACLPreConf ACL Pre Configuration
* This section contains the pre-configuration structure.
*/

/**
* @defgroup ACLPreConfE ACL Pre Configuration Enum
* @ingroup ACLPreConf ACL Pre Configuration
* This section contains the pre-configuration enum.
*/

/**
* @defgroup ACLPreConfF ACL Pre Configuration Functions
* @ingroup ACLPreConf ACL Pre Configuration
* This section contains the pre-configuration functions.
*/

/**
* @defgroup tagIPSAFE_PRECFG_VALUE IPSAFE_PRECFG_VALUE_S
* @ingroup ACLPreConfS ACL Pre Configuration Structure
* @par Prototype
* @code
* typedef struct tagIPSAFE_PRECFG_VALUE
* {
*    UINT32 u32Key;
*    UINT32 u32CfgValue;
*    UINT32 u32MinValue;
*    UINT32 u32MaxValue;
* }IPSAFE_PRECFG_VALUE_S;
* @endcode 
* 
* @par Description
* This structure stores the detail of the key ID which needs to be configured, along with 
* the current configuration value, and the maximum and minimum possible values for the 
* corresponding key ID.
*
* @datastruct u32Key The key ID for which the value needs to be configured. It can be 
* any value from IPSAFE_PRECONFIG_INFO_E
* @datastruct u32CfgValue Current configuration value. It can be either the default 
* value (if not already configured) or the user-configured value.
* @datastruct u32MinValue Minimum configurable value for this key.
* @datastruct u32MaxValue Maximum configurable value for this key.
*/
typedef struct tagIPSAFE_PRECFG_VALUE
{
    UINT32 u32Key;       /* Key ID */
    UINT32 u32CfgValue;  /* Current Configuration value */
    UINT32 u32MinValue;  /* Minimum configuration value for this key */
    UINT32 u32MaxValue;  /* Maximum configuration value for this key */
}IPSAFE_PRECFG_VALUE_S;

/**
* @defgroup IPSAFE_PRECONFIG_INFO_Etag IPSAFE_PRECONFIG_INFO_E
* @ingroup ACLPreConfE ACL Pre Configuration Enum
* @par Prototype
* @code
* typedef enum IPSAFE_PRECONFIG_INFO_Etag
* {
*     FIREWALL_WLS_MAX_RULE,
*     FIREWALL_BLS_MAX_RULE,
*     FIREWALL_AD_IF_CFG_MAX_RULE,
*     FIREWALL_AD_FLOOD_CFG_MAX_RULE,
*     FIREWALL_ACLFW_MAX_IFINDEX,
*     FIREWALL_ACL_RFC_MAX_MEM_USE,
*     FIREWALL_ENABLE_MAC_BASE_ACL_FILTER,
*     FIREWALL_AD_MAX_PKT_SIZE,
*     FIREWALL_AD_MIN_FRAGMENT_SIZE,
*     FIREWALL_AD_FLOOD_PARA,
*     FIREWALL_AD_TEARDROP_MAX_PKT,
*     FIREWALL_AD_TEARDROP_MAX_FRAGMENT,
*     IPSAFE_MAX_PRECFG_NUM
* }IPSAFE_PRECONFIG_INFO_E;
* @endcode 
* 
* @par Description
* This enum consists of the pre-configuration IDs of the IPSAFE module.
*
* @datastruct FIREWALL_WLS_MAX_RULE Maximum number of rules for whitelist
* @datastruct FIREWALL_BLS_MAX_RULE Maximum number of rules for blacklist
* @datastruct FIREWALL_AD_IF_CFG_MAX_RULE Maximum number of interface based attack rules
* @datastruct FIREWALL_AD_FLOOD_CFG_MAX_RULE Maximum number of flood based attack rule
* @datastruct FIREWALL_ACLFW_MAX_IFINDEX Maximum number of interface indexes binding with ACL group
* @datastruct FIREWALL_ACL_RFC_MAX_MEM_USE Maximum memory usage for ACL RFC
* @datastruct FIREWALL_ENABLE_MAC_BASE_ACL_FILTER To enable or disable MAC based ACL filter
* @datastruct FIREWALL_AD_MAX_PKT_SIZE Maximum packet size for ping of death attack
* @datastruct FIREWALL_AD_MIN_FRAGMENT_SIZE Minimum fragment size for IP tiny fragment attack
* @datastruct FIREWALL_AD_FLOOD_PARA Number of parameters to be considered in flood attack 
*	- 0 - Flood is based on only destination IP
*	- 1 - Flood is based on destination IP and destination Port
* @datastruct FIREWALL_AD_TEARDROP_MAX_PKT Maximum number of fragmented packets which 
* can be analyzed in teardrop attack
* @datastruct FIREWALL_AD_TEARDROP_MAX_FRAGMENT Maximum number of fragments which can be
* analyzed of one packet in teardrop attack
* @datastruct IPSAFE_MAX_PRECFG_NUM Maximum possible ID number for IPSAFE modules.
*/
typedef enum IPSAFE_PRECONFIG_INFO_Etag
{
    /*Pre configuration IDs for ipsafe module*/
    FIREWALL_WLS_MAX_RULE,        /* 0 Maximum number of rules for whitelist*/

    FIREWALL_BLS_MAX_RULE,        /* 1 Maximum number of rules for blacklist*/

    FIREWALL_AD_IF_CFG_MAX_RULE,    /* 2 Maximum number of interface based attack rules*/

    FIREWALL_AD_FLOOD_CFG_MAX_RULE,    /* 3 Maximum number flood based attack rules*/

    FIREWALL_ACLFW_MAX_IFINDEX,    /* 4 Maximum number interface indexes binding with ACL group*/

    FIREWALL_ACL_RFC_MAX_MEM_USE,    /* 5 Maximum memory usage for ACL rfc*/

    FIREWALL_ENABLE_MAC_BASE_ACL_FILTER,    /* 6 To enable/disable mac based ACL filter*/

    FIREWALL_AD_MAX_PKT_SIZE,    /* 7 Maximum packet size for Ping of death attack*/

    FIREWALL_AD_MIN_FRAGMENT_SIZE,    /* 8 Minimum fragment size IP tiny fragment attack*/

    FIREWALL_AD_FLOOD_PARA,    /* 9 Number of parameters to be considered in flood attack
                                                          0 - Flood is based on only destination IP
                                                          1 - Flood is based on destination IP and destination Port*/

    FIREWALL_AD_TEARDROP_MAX_PKT,    /* 10 Maximum number of fragmented packets 
                                       can be analyzed in teardrop attack*/

    FIREWALL_AD_TEARDROP_MAX_FRAGMENT,    /* 11 Maximum number of fragments can be
                                            analyzed of one packet in teardrop attack*/

    IPSAFE_MAX_PRECFG_NUM           
}IPSAFE_PRECONFIG_INFO_E;



/**
* @defgroup IPSAFE_ADP_SetPreConfPara IPSAFE_ADP_SetPreConfPara
* @ingroup ACLPreConfF ACL Pre Configuration Functions
* @par Prototype
* @code
* UINT32 IPSAFE_ADP_SetPreConfPara(UINT32 u32Key, UINT32 u32Val);
* @endcode 
* 
* @par Description
* This function is used to set pre-configuration for some firewall parameters. Pre-configuration
* can be done before initializing the firewall.
* 
* @param[in] u32Key Key to identify the parameter for which configuration needs to be done []
* @param[in] u32Val Value to be configured []
* @param[out]   []
* 
* @retval UINT32 Setting pre-configuration is success [FW_OK|]
* @retval UINT32 Failed to set pre-configuration [IPSAFE_SET_INVALID_VALUE|]
* 
* 
*
* @par Note
* The parameters which can be pre-configured are FWCOMMON_WLS_MAX_RULE, FWCOMMON_BLS_MAX_RULE
* FWCOMMON_AD_IF_CFG_MAX_RULE, FWCOMMON_AD_FLOOD_CFG_MAX_RULE, FWCOMMON_ACLFW_MAX_IFINDEX
* FWCOMMON_ACL_RFC_MAX_MEM_USE FWCOMMON_ENABLE_MAC_BASE_ACL_FILTER FIREWALL_AD_MAX_PKT_SIZE
* FIREWALL_AD_MIN_FRAGMENT_SIZE and FIREWALL_AD_FLOOD_PARA
* 
* @par Related Topics
* FWCOMMON_GetPreConfPara
*/

UINT32 IPSAFE_ADP_SetPreConfPara(UINT32 u32Key, UINT32 u32Val);

/**
* @defgroup IPSAFE_ADP_GetPreConfPara IPSAFE_ADP_GetPreConfPara
* @ingroup ACLPreConfF ACL Pre Configuration Functions
* @par Prototype
* @code
* UINT32 IPSAFE_ADP_GetPreConfPara(UINT32 u32Key, UINT32 *pu32Val);
* @endcode 
* 
* @par Description
* This function is used to get pre-configured value of some firewall parameters.
* 
* @param[in] u32Key Key to identify the parameter for which configured value is needed []
* @param[out] *puu32Val To store the configured value []
* 
* @retval UINT32 Getting configured value is success [FW_OK|]
* @retval UINT32 Received null pointer as input [IPSAFE_VAL_NULL_PTR|]
* @retval UINT32 Failed to get configured value [IPSAFE_GET_INVALID_KEY|]
* 
* @par Note
* The parameter values which can be obtained by this API are FWCOMMON_WLS_MAX_RULE, FWCOMMON_BLS_MAX_RULE
* FWCOMMON_AD_IF_CFG_MAX_RULE, FWCOMMON_AD_FLOOD_CFG_MAX_RULE, FWCOMMON_ACLFW_MAX_IFINDEX
* FWCOMMON_ACL_RFC_MAX_MEM_USE FWCOMMON_ENABLE_MAC_BASE_ACL_FILTER FIREWALL_AD_MAX_PKT_SIZE
* FIREWALL_AD_MIN_FRAGMENT_SIZE and FIREWALL_AD_FLOOD_PARA
* 
* @par Related Topics
* IPSAFE_ADP_SetPreConfPara
*/

UINT32 IPSAFE_ADP_GetPreConfPara(UINT32 u32Key, UINT32 *pu32Val);

#ifdef  __cplusplus
}
#endif

#endif
