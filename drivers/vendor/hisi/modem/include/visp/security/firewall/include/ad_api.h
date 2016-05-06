/*************************************************************************
 *
 *              Copyright 2009, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                              ad_api.h
 *
 *       Version: DOPRA VISP V1R8C02 Firewall
 *   Module Name: Attack defense
 *  Date Created: 2009-08-15
 *        Author: WangHuiwen/106576
 *   Description: the APIs for attack defense module 
 *     Functions: AD_InitCfg
 *                AD_EnableAtkDefendByType
 *                AD_IsEnableAtkDefendByType
 *                AD_EnableAtkDefend
 *                AD_IsEnableAtkDefend
 *                AD_SetAtkMalformPara
 *                AD_GetAtkMalformPara
 *                AD_SetFloodPara
 *                AD_DelFloodPara
 *                AD_SetScanPara
 *                AD_SetScanPara
 *                AD_ShowScanPara
 *                AD_GetScanPara
 *                AD_RateCountTimeOutHandle
 *                AD_ShowGlobalDefenseStatus
 *                AD_ClearStat
 *                AD_GetStat
 *                AD_GetVCPUStat
 *                AD_ShowStat
 *                AD_ShowVCPUStat
 *                AD_IfCfg_OpenList
 *                AD_IfCfg_GetNext
 *                AD_IfCfg_CloseList
 *                AD_ShowIfCfg
 *                AD_GetGlobalFloodPara
 *                AD_ShowGlobalFloodPara
 *                AD_FloodParaIP_OpenList
 *                AD_FloodParaIP_GetNext
 *                AD_FloodParaIP_CloseList
 *                AD_ShowFloodParaIP
 *                AD_ShowAtkMalformPara
 *                AD_SetAtkDebugFlag
 *                AD_GetAtkDebugFlag
 *                AD_ShowAtkDefendDebugging
 *                AD_SetArpMissPara
 *                AD_GetArpMissPara
 *                AD_ShowArpMissPara
 *                AD_SetAtkUserDefined
 *                AD_DelAtkUserDefined
 *                AD_AtkUserDefined_OpenList
 *                AD_AtkUserDefined_GetNext
 *                AD_AtkUserDefined_CloseList
 *                AD_ShowAtkUserDefined
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME                   DESCRIPTION
 *  2009-08-15      WangHuiwen/106576      Create
 *
 ************************************************************************/

#ifndef _AD_API_H_
#define _AD_API_H_

#ifdef __cplusplus
extern "C" {
#endif



/**
* @defgroup AD Attack Defense API Reference
* This section contains all the descriptions for functions, enums, and
* structures.
*/

/**
* @defgroup ADF Attack Defense Functions
* @ingroup AD Attack Defense API Reference
* This section contains the functions.
*/


/* Attack type definition */

/**
* @defgroup tagAttackType AD_ATTACK_TYPE_E
* @ingroup ADE Attack Defense Enums
* @par Prototype
* @code
* typedef enum tagAttackType
* {
*     ATCK_OK = 0x00,
*     ATCK_IP_SPOOF = 0x01,
*     ATCK_LAND  = 0x02,
*     ATCK_SMURF = 0x04,
*     ATCK_TCPFLAG = 0x08,
*     ATCK_WINNUKE = 0x10,
*     ATCK_ICMP_REDIRECT = 0x20 ,
*     ATCK_ICMP_UNREACHABLE = 0x40,
*     ATCK_ICMP_TIMESTAMP = 0x80,
*     ATCK_PING_OF_DEATH = 0x100,
*     ATCK_FRAGGLE = 0x200,
*     ATCK_RECORD_ROUTE = 0x400,
*     ATCK_LOOSE_SOURCE_ROUTE = 0x800,
*     ATCK_STRICT_SOURCE_ROUTE = 0x1000,
*     ATCK_IP_SWEEP   = 0x2000,
*     ATCK_PORTSCAN   = 0x4000,
*     ATCK_ARP_FLOOD  = 0x20000,
*     ATCK_ICMP_FLOOD = 0x40000,
*     ATCK_UDP_FLOOD  = 0x80000,
*     ATCK_SYN_FLOOD  = 0x100000,
*     ATCK_ARP_MISS = 0x800000,
*     ATCK_USER_DEFINE = 0x2000000,
*     ATCK_IP_TINY_FRAG = 0x4000000,
*     ATCK_TEARDROP = 0x8000000,
*     ATCK_ALL =   ATCK_IP_SPOOF             | ATCK_LAND
*                 | ATCK_SMURF               | ATCK_TCPFLAG
*                 | ATCK_WINNUKE             | ATCK_ICMP_REDIRECT
*                 | ATCK_ICMP_UNREACHABLE    | ATCK_ICMP_TIMESTAMP
*                 | ATCK_PING_OF_DEATH       | ATCK_FRAGGLE
*                 | ATCK_RECORD_ROUTE        | ATCK_LOOSE_SOURCE_ROUTE
*                 | ATCK_STRICT_SOURCE_ROUTE | ATCK_IP_SWEEP
*                 | ATCK_PORTSCAN            | ATCK_ARP_FLOOD
*                 | ATCK_ICMP_FLOOD          | ATCK_UDP_FLOOD
*                 | ATCK_SYN_FLOOD           | ATCK_ARP_MISS
*                 | ATCK_USER_DEFINE         | ATCK_IP_TINY_FRAG
*                 | ATCK_TEARDROP
* 
* } AD_ATTACK_TYPE_E;
* @endcode 
* 
*
* @par Description
* This enum contains attack types. These types are used while calling the APIs to 
* a)enable/disable an attack
* b)enable/disable dubug logs for an attack
* c)set/get configuration for an attack
* 
* @datastruct ATCK_OK=0x00 Does not indicate any attack type.Used to check the succes/failure of an API.
* @datastruct ATCK_IP_SPOOF=0x01 Indicates IP spoofing attack(Attack Type - Malformed)
* @datastruct ATCK_LAND=0x02 Indicates Land attack(Attack Type - Malformed)
* @datastruct ATCK_SMURF=0x04 Indicates Smurf attack(Attack Type - Malformed)
* @datastruct ATCK_TCPFLAG=0x08 Indicates TCP Flag attack(Attack Type - Malformed)
* @datastruct ATCK_WINNUKE=0x10 Indicates Winnuke attack(Attack Type - Malformed)
* @datastruct ATCK_ICMP_REDIRECT=0x20 Indicates ICMP Redirect attack(Attack Type - Malformed)
* @datastruct ATCK_ICMP_UNREACHABLE=0x40 Indicates ICMP Unreachable attack(Attack Type - Malformed)
* @datastruct ATCK_ICMP_TIMESTAMP=0x80 Indicates ICMP Timestamp attack(Attack Type - Malformed)
* @datastruct ATCK_PING_OF_DEATH=0x100 Indicates Ping of Death attack(Attack Type - Malformed)
* @datastruct ATCK_FRAGGLE=0x200 Indicates Fraggle attack(Attack Type - Malformed)
* @datastruct ATCK_RECORD_ROUTE=0x400 Indicates Record route attack(Attack Type - Malformed)
* @datastruct ATCK_LOOSE_SOURCE_ROUTE=0x800 Indicates Loose source route attack(Attack Type - Malformed)
* @datastruct ATCK_STRICT_SOURCE_ROUTE=0x1000 Indicates Strict source route attack(Attack Type - Malformed)
* @datastruct ATCK_IP_SWEEP=0x2000 Indicates IP sweep attack(Attack Type - Sweep)
* @datastruct ATCK_PORTSCAN=0x4000 Indicates Port Scan attack(Attack Type - Scan)
* @datastruct ATCK_ARP_FLOOD=0x20000 Indicates ARP flood attack(Attack Type - Flooding)
* @datastruct ATCK_ICMP_FLOOD=0x40000 Indicates ICMP flood attack(Attack Type - Flooding)
* @datastruct ATCK_UDP_FLOOD=0x80000 Indicates UDP flood attack(Attack Type - Flooding)
* @datastruct ATCK_SYN_FLOOD=0x100000 Indicates SYN flood attack(Attack Type - Flooding)
* @datastruct ATCK_ARP_MISS=0x800000 Indicates ARP miss attack(Attack Type - ARP Miss)
* @datastruct ATCK_USER_DEFINE=0x2000000 Indicates User defined attack(Attack Type - User Defined)
* @datastruct ATCK_IP_TINY_FRAG=0x4000000 Indicates IP tiny fragment attack(Attack Type - Malformed)
* @datastruct ATCK_TEARDROP=0x8000000 Indicates Teardrop attack(Attack Type - Malformed)
* @datastruct ATCK_ALL Indicates all attacks.
*/

typedef enum tagAttackType
{
    ATCK_OK = 0x00,
    ATCK_IP_SPOOF = 0x01,
    ATCK_LAND  = 0x02,
    ATCK_SMURF = 0x04,
    ATCK_TCPFLAG = 0x08,
    ATCK_WINNUKE = 0x10,
    ATCK_ICMP_REDIRECT = 0x20,
    ATCK_ICMP_UNREACHABLE = 0x40,
    ATCK_ICMP_TIMESTAMP = 0x80,
    ATCK_PING_OF_DEATH = 0x100,
    ATCK_FRAGGLE = 0x200,
    ATCK_RECORD_ROUTE = 0x400,
    ATCK_LOOSE_SOURCE_ROUTE = 0x800,
    ATCK_STRICT_SOURCE_ROUTE = 0x1000,
    ATCK_IP_SWEEP   = 0x2000,
    ATCK_PORTSCAN   = 0x4000,
    ATCK_ARP_FLOOD  = 0x20000,
    ATCK_ICMP_FLOOD = 0x40000,
    ATCK_UDP_FLOOD  = 0x80000,
    ATCK_SYN_FLOOD  = 0x100000,
    ATCK_ARP_MISS = 0x800000,
    ATCK_USER_DEFINE = 0x2000000,
    ATCK_IP_TINY_FRAG = 0x4000000,
    ATCK_TEARDROP = 0x8000000,
    ATCK_ALL =   ATCK_IP_SPOOF             | ATCK_LAND
                | ATCK_SMURF               | ATCK_TCPFLAG
                | ATCK_WINNUKE             | ATCK_ICMP_REDIRECT
                | ATCK_ICMP_UNREACHABLE    | ATCK_ICMP_TIMESTAMP
                | ATCK_PING_OF_DEATH       | ATCK_FRAGGLE
                | ATCK_RECORD_ROUTE        | ATCK_LOOSE_SOURCE_ROUTE
                | ATCK_STRICT_SOURCE_ROUTE | ATCK_IP_SWEEP
                | ATCK_PORTSCAN            | ATCK_ARP_FLOOD
                | ATCK_ICMP_FLOOD          | ATCK_UDP_FLOOD
                | ATCK_SYN_FLOOD           | ATCK_ARP_MISS
                | ATCK_USER_DEFINE         | ATCK_IP_TINY_FRAG
                | ATCK_TEARDROP
} AD_ATTACK_TYPE_E;


/**
* @defgroup tagADMalformPara AD_MALFORM_PARA_S
* @ingroup ADS Attack Defense Structures
* @par Prototype
* @code
* typedef struct tagADMalformPara
* {
*     UINT32 u32EnableLog;
* } AD_MALFORM_PARA_S;
* @endcode 
* 
*
* @par Description
* This structure is used to set/get the configuration of Malformed attacks.
* 
* @datastruct u32EnableLog Indicates whether to log when a configured malformed attack is found.
* If enabled,this will provide the details of the Malformed attack detected.
* The values can be the following:
*	- 1 to enable logging.
*	- 0 to disable logging.
*/
typedef struct tagADMalformPara
{
    UINT32 u32EnableLog;  
} AD_MALFORM_PARA_S;

/* Attack configure object type */
/**
* @defgroup tagADCfgObjType AD_CFG_OBJ_TYPE_E
* @ingroup ADE Attack Defense Enums
* @par Prototype
* @code
* typedef enum tagADCfgObjType AD_CFG_OBJ_TYPE_E
* {
*     AD_PARA_GLOBAL = 0,
*     AD_PARA_IF,
*     AD_PARA_IP,
*     AD_PARA_MAX
* } AD_CFG_OBJ_TYPE_E;
* @endcode 
* 
*
* @par Description
* This indicates the types of configurations for Flooding Attacks. These enum values
* are used while configuring the various Flood attacks.
* 
* @datastruct AD_PARA_GLOBAL=0 Indicates Global configuration.
* @datastruct AD_PARA_IF Indicates Interface based flooding configuration.
* @datastruct AD_PARA_IP Indicates IP based flooding configuration.
* @datastruct AD_PARA_MAX Indicates maximum possible type of configuration.
*/
typedef enum tagADCfgObjType
{
    AD_PARA_GLOBAL = 0,
    AD_PARA_IF,
    AD_PARA_IP,
    AD_PARA_MAX
} AD_CFG_OBJ_TYPE_E;

/**
* @defgroup tagADFloodType AD_FLOOD_TYPE_E
* @ingroup ADE Attack Defense Enums
* @par Prototype
* @code
* typedef enum tagADFloodType
* {
*     AD_ICMP_FLOOD = 0,
*     AD_UDP_FLOOD,
*     AD_SYN_FLOOD,
*     AD_ARP_FLOOD,
*     AD_FLOOD_TYPE_MAX
* } AD_FLOOD_TYPE_E;
* @endcode 
* 
*
* @par Description
* This enum consists of the types of flooding attack. These enums are used while configuring
* each flood attack.
* 
* @datastruct AD_ICMP_FLOOD=0 Indicates ICMP flooding.
* @datastruct AD_UDP_FLOOD Indicates UDP flooding.
* @datastruct AD_SYN_FLOOD Indicates SYN flooding.
* @datastruct AD_ARP_FLOOD Indicates ARP flooding.
* @datastruct AD_FLOOD_TYPE_MAX Indicates maximum possible type of flooding type.
*/
typedef enum tagADFloodType
{
    AD_ICMP_FLOOD = 0,
    AD_UDP_FLOOD,
    AD_SYN_FLOOD,
    AD_ARP_FLOOD,
    AD_FLOOD_TYPE_MAX
} AD_FLOOD_TYPE_E;


typedef struct tagAdFloodPara
{
    UINT32 u32EnableDefense;
    UINT32 u32MaxRate;
    UINT32 u32EnableBlkList;
    UINT32 u32BlkTimeout;
    UINT32 u32EnableLog;
} AD_FLOOD_PARA_S;

/**
* @defgroup tagAdFloodCfg AD_FLOOD_CFG_S
* @ingroup ADS Attack Defense Structures
* @par Prototype
* @code
* typedef struct tagAdFloodCfg
* {
*     UINT32 u32CfgObjType;
*     UINT32 u32CfgObj;
*     AD_FLOOD_PARA_S stFloodPara;
* } AD_FLOOD_CFG_S;
* @endcode 
* 
*
* @par Description
* This structure stores the details of the flood attack defense configuration. This structure is 
* used while setting the configuration of different flood attacks.
* 
* @datastruct u32CfgObjType Indicates the type of configuration. The possible values being global, 
* individual interface, and individual IP.
* @datastruct u32CfgObj Indicates the value for corresponding configuration type, like global, 
* individual interface, and individual IP. It should be in the order of host byte.
* @datastruct stFloodPara Indicates the structure that stores the flood defense parameters.
*/ 
typedef struct tagAdFloodCfg
{
    UINT32 u32CfgObjType;    
    UINT32 u32CfgObj;    
    AD_FLOOD_PARA_S stFloodPara;
} AD_FLOOD_CFG_S;


/**
* @defgroup tagADFloodParaFilter AD_FLOOD_PARA_FILTER_S
* @ingroup ADS Attack Defense Structures
* @par Prototype
* @code
* typedef struct tagADFloodParaFilter
* {
*     UINT32 u32CfgObj;
* }AD_FLOOD_PARA_FILTER_S;
* @endcode 
* 
*
* @par Description
* This structure defines the filter for accessing IP based flood configuration list.
* 
* @datastruct u32CfgObj The configuration object value.
*/ 
typedef struct tagADFloodParaFilter
{    
    UINT32 u32CfgObj;   
}AD_FLOOD_PARA_FILTER_S;

/**
* @defgroup AD_FLOOD_CFG_IP_HASH_ITEM_S
* @ingroup ADS Attack Defense Structures
* @par Prototype
* @code
* typedef struct tagAdFloodCfgIpHashItem
* {
*     AD_FLOOD_PARA_S stSynFloodPara;
*     AD_FLOOD_PARA_S stIcmpFloodPara;
*     AD_FLOOD_PARA_S stUdpFloodPara;
* } AD_FLOOD_CFG_IP_HASH_ITEM_S;
* @endcode 
* 
*
* @par Description
* This structure stores the flood attack IP level configuration. This structure is
* used for getting the IP based configured parameters of the various flood types.
* 
* @datastruct stSynFloodPara Indicates SYN flood parameter.
* @datastruct stIcmpFloodPara Indicates ICMP flood parameter.
* @datastruct stUdpFloodPara Indicates UDP flood parameter.
*/ 
typedef struct tagAdFloodCfgIpHashItem
{
    AD_FLOOD_PARA_S stSynFloodPara;
    AD_FLOOD_PARA_S stIcmpFloodPara;
    AD_FLOOD_PARA_S stUdpFloodPara;
} AD_FLOOD_CFG_IP_HASH_ITEM_S;

/**
* @defgroup tagAdFloodParaIPInfo AD_FLOOD_PARA_IP_INFO_S
* @ingroup ADS Attack Defense Structures
* @par Prototype
* @code
* typedef struct tagAdFloodParaIPInfo
* {
*     UINT32 u32CfgObj;
*     AD_FLOOD_CFG_IP_HASH_ITEM_S stFloodCfg;
* } AD_FLOOD_PARA_IP_INFO_S;
* @endcode 
* 
*
* @par Description
* This structure stores the flood para IP information. This structure is used to get the 
* flood parameters configured for each IP.
* 
* @datastruct u32CfgObj The configuration object.
* @datastruct stFloodCfg Indicates the structure that stores the flood attack IP level configuration 
* types, used in the hash table.
*/ 
typedef struct tagAdFloodParaIPInfo
{
    UINT32 u32CfgObj; 
    AD_FLOOD_CFG_IP_HASH_ITEM_S stFloodCfg;
} AD_FLOOD_PARA_IP_INFO_S;




typedef struct tagAdScanPara
{
    UINT32 u32MaxRate;
    UINT32 u32EnableBlkList;
    UINT32 u32BlkTimeout; 
    UINT32 u32EnableLog;
} AD_SCAN_PARA_S;

/**
* @defgroup tagAtkUserDefinePara AD_USER_DEFINE_PARA_S
* @ingroup ADS Attack Defense Structures
* @par Prototype
* @code
* typedef struct tagAtkUserDefinePara
* {
*     UINT32 u32ID;
*     UINT32 u32SignLen;
*     UINT8 u8Mask[128];
*     UINT8 u8Signature[128];
*     UINT32 u32EnableBlkList;
*     UINT32 u32BlkTimeout;
*     UINT32 u32EnableLog;
* } AD_USER_DEFINE_PARA_S;
* @endcode 
* 
*
* @par Description
* This structure stores the user defined defense parameters.
* 
* @datastruct u32ID Indicates the rule ID. It can range from 1 to 64.
* @datastruct u32SignLen Indicates the length of the feature value in bytes. It should be a multiple of 4.
* The value can range from 4 to 128 bytes.
* @datastruct u8Mask[128] Indicates mask value for user defined attack.
* @datastruct u8Signature[128] Indicates feature value for user defined attack.
* @datastruct u32EnableBlkList Indicates whether to add source IP to blacklist when userdefined attack happens.
* once the IP added to blacklist, firewall will drop all recieved packets from that IP before it reaches
* attack module. It will increase system performance.
* @datastruct u32BlkTimeout Indicates blacklist timeout value. The value ranges from 1 to 1000 minutes. A value 
* of 0 for this parameter indicates that there is no timeout feature.
* @datastruct u32EnableLog Indicates whether to enable log recording or not.
*/ 
typedef struct tagAtkUserDefinePara
{
    UINT32 u32ID;
    UINT32 u32SignLen;
    UINT8 u8Mask[128];
    UINT8 u8Signature[128];
    UINT32 u32EnableBlkList;
    UINT32 u32BlkTimeout;
    UINT32 u32EnableLog;
} AD_USER_DEFINE_PARA_S;

/**
* @defgroup tagAdIfCfgInfo AD_IF_CFG_INFO_S
* @ingroup ADS Attack Defense Structures
* @par Prototype
* @code
* typedef struct tagAdIfCfgInfo
* {
*     UINT32 u32IfIndex;
*     UINT32 u32DefenseEnabled;
*     AD_FLOOD_PARA_S stSynFloodPara;
*     AD_FLOOD_PARA_S stArpFloodPara;
* } AD_IF_CFG_INFO_S;
* @endcode 
* 
*
* @par Description
* This structure stores the Interface level configuration of attack defence. This includes
* enabling/disabling Attack Defense on the Interface as well as configuring
* the flooding parameters on that interface.
* Attack monitoring(for all types of attacks)is done only on the packets that are 
* comming from those interfaces on which the 'Attack defense' is enabled.
* 
* @datastruct u32IfIndex Interface index.
* @datastruct u32DefenseEnabled Indicates whether attack defense is enabled or not.
* @datastruct stSynFloodPara Indicates SYN flood defense.
* @datastruct stArpFloodPara Indicates ARP MISS flood defense.
*/ 
typedef struct tagAdIfCfgInfo
{
    UINT32 u32IfIndex;
    UINT32 u32DefenseEnabled;
    AD_FLOOD_PARA_S stSynFloodPara;
    AD_FLOOD_PARA_S stArpFloodPara;
} AD_IF_CFG_INFO_S;

/**
* @defgroup tagAtkArpMissPara AD_ARP_MISS_PARA_S
* @ingroup ADS Attack Defense Structures
* @par Prototype
* @code
* typedef struct tagAtkArpMissPara
* {
*     UINT32 u32MaxRate;
*     UINT32 u32EnableLog;
* } AD_ARP_MISS_PARA_S;
* @endcode 
* 
*
* @par Description
* This structure stores the ARP MISS defense parameters.
* 
* @datastruct u32MaxRate Indicates the maximum packet rate. The value ranges from 1-1000000.
* @datastruct u32EnableLog Indicates whether to enable the log recording or not.
*/ 
typedef struct tagAtkArpMissPara
{
    UINT32 u32MaxRate;
    UINT32 u32EnableLog;
} AD_ARP_MISS_PARA_S;

/**
* @defgroup enumADERRCODE AD_ERROR_CODE_E
* @ingroup FEC Firewall Error Codes
* @par Prototype
* @code
* typedef enum enumADERRCODE
* {
*     AD_OK = FW_OK,
*     AD_ERR = FWCOMMON_ADMODID + 1,
*     AD_ERR_MALLOC_AD_MALFORM_CFG_S,
*     AD_ERR_ADD_NAME_DB_MALFORM_CFG_S,
*     AD_ERR_MALLOC_AD_CFG_S,
*     AD_ERR_ADD_NAME_DB_AD_CFG_S,
*     AD_HASH_FAIL_IF_CFG_SFE_INIT_CFG,
*     AD_HASH_FAIL_FLOOD_IP_CFG_SFE_INIT_CFG,
*     AD_MALLOC_FAIL_FLOOD_GLOBAL_CFG_SFE_INIT_CFG,
*     AD_ADD_NAME_FAIL_SFE_INIT_CFG,
*     AD_INVALID_INPUT_SFE_ENABLE_ATK_BY_TYPE,
*     AD_CFG_NULL_SFE_ENABLE_ATK_BY_TYPE,
*     AD_INVALID_INPUT_SFE_SET_MALFORM,
*     AD_CFG_NULL_SFE_SET_MALFORM,
*     AD_TYPE_ERR_SFE_SET_MALFORM,
*     AD_IF_CFG_HASH_NULL_SFE_ENABLE_ATK_DEFEND,
*     AD_INVALID_INPUT_SFE_ENABLE_ATK_DEFEND,
*     AD_HASH_TABLE_FULL_SFE_ENABLE_ATK_DEFEND,
*     AD_HASH_FAIL_SFE_ENABLE_ATK_DEFEND,
*     AD_HASH_FAIL_SFE_AD_IS_ENABLE_ATK_DEFEND,
*     AD_INVALID_INPUT_SFE_GET_MALFORM,
*     AD_CFG_NULL_SFE_GET_MALFORM,
*     AD_TYPE_ERR_SFE_GET_MALFORM,
*     AD_INVALID_INPUT_SFE_SET_FLOOD,
*     AD_CFG_NULL_SFE_SET_FLOOD,
*     AD_CFG_OBJ_TYPE_ERR_SFE_SET_FLOOD,
*     AD_HASH_TABLE_FULL_SFE_SET_FLOOD,
*     AD_HASH_FAIL_SFE_SET_FLOOD,
*     AD_BROADCAST_IPSPOOFING_SH,
*     AD_IP_NOT_IN_FIB_IPSPOOFING_SH,
*     AD_INTERFACE_NOT_SAME_IPSPOOFING_SH,
*     AD_INVALID_INPUT_CPY_FLOOD_PARA,
*     AD_INVALID_DEFENSE_SWITCH_CPY_FLOOD_PARA,
*     AD_FLOOD_RATE_OUTRANGE_CPY_FLOOD_PARA,
*     AD_INVALID_BLK_SWITCH_CPY_FLOOD_PARA,
*     AD_FLOOD_BLK_TIMEOUT_OUTRANGE_CPY_FLOOD_PARA,
*     AD_INVALID_LOG_SWITCH_CPY_FLOOD_PARA,
*     AD_INVALID_INPUT_CPY_FLOOD_PARA_TO_IP_HASH_ITEM,
*     AD_FLOOD_TYPE_ERR_CPY_FLOOD_PARA_TO_IP_HASH_ITEM,
*     AD_INVALID_INPUT_CPY_FLOOD_PARA_TO_IF_HASH_ITEM,
*     AD_FLOOD_TYPE_ERR_CPY_FLOOD_PARA_TO_IF_HASH_ITEM,
*     AD_INVALID_INPUT_SET_GLOBAL_FLOOD_PARA,
*     AD_FLOOD_TYPE_ERR_SET_GLOBAL_FLOOD_PARA,
*     AD_CFG_NULL_SFE_DEL_FLOOD,
*     AD_CFG_OBJ_TYPE_ERR_SFE_DEL_FLOOD,
*     AD_HASH_FAIL_SFE_DEL_FLOOD,
*     AD_SCAN_PARA_MALLOC_ERR_SFE_INIT_CFG,
*     AD_SCAN_PARA_ADD_NAME_ERR_SFE_INIT_CFG,
*     AD_SWEEP_PARA_MALLOC_ERR_SFE_INIT_CFG,
*     AD_SWEEP_PARA_ADD_NAME_ERR_SFE_INIT_CFG,
*     AD_CFG_NULL_SFE_SET_SCAN_PARA,
*     AD_NULL_INPUT_SFE_SET_SCAN_PARA,
*     AD_PARA_INVALID_SFE_SET_SCAN_PARA,
*     AD_ATTACK_TYPE_ERR_SFE_SET_SCAN_PARA,
*     AD_CFG_NULL_SFE_GET_SCAN_PARA,
*     AD_NULL_INPUT_SFE_GET_SCAN_PARA,
*     AD_ATTACK_TYPE_ERR_SFE_GET_SCAN_PARA,
*     AD_NULL_INPUT_IS_ENABLE_DEFEND,
*     AD_NULL_INPUT_SFE_IF_OPENLIST,
*     AD_OPEN_FAIL_SFE_IF_OPENLIST,
*     AD_NULL_INPUT_SFE_IF_GETNEXT,
*     AD_GET_FAIL_SFE_IF_GETNEXT,
*     AD_NULL_INPUT_SFE_IF_CLOSELIST,
*     AD_CLOSE_FAIL_SFE_IF_CLOSELIST,
*     AD_CFG_NULL_SFE_GET_GLOBAL_FLOOD_PARA,
*     AD_NULL_INPUT_SFE_GET_GLOBAL_FLOOD_PARA,
*     AD_FLOOD_TYPE_ERR_SFE_GET_GLOBAL_FLOOD_PARA,
*     AD_NULL_INPUT_SFE_FLOODPARAIP_OPENLIST,
*     AD_OPEN_FAIL_SFE_FLOODPARAIP_OPENLIST,
*     AD_NULL_INPUT_SFE_FLOODPARAIP_GETNEXT,
*     AD_GET_FAIL_SFE_FLOODPARAIP_GETNEXT,
*     AD_NULL_INPUT_SFE_FLOODPARAIP_CLOSELIST,
*     AD_CLOSE_FAIL_SFE_FLOODPARAIP_CLOSELIST,
*     AD_ERR_STAT_AD_STATISTICS_NOT_INITIATLIZED_CLEARSTAT,
*     SFE_AD_ERR_STAT_INPUT_NULLPTR_GETSTAT,
*     AD_ERR_STAT_AD_STATISTICS_NOT_INITIATLIZED_GETSTAT,
*     SFE_AD_ERR_STAT_INPUT_NULLPTR_GETVCPUSTAT,
*     AD_ERR_STAT_AD_STATISTICS_NOT_INITIATLIZED_GETVCPUSTAT,
*     SFE_AD_ERR_STAT_INVALID_VCPU_GETVCPUSTAT,
*     AD_STAT_INIT_ERR_SFE_INIT_CFG,
*     AD_USER_DEF_PARA_MALLOC_ERR_SFE_INIT_CFG,
*     AD_USER_DEF_PARA_ADD_NAME_ERR_SFE_INIT_CFG,
*     AD_CFG_NULL_SFE_SET_USER_DEF,
*     AD_NULL_INPUT_SFE_SET_USER_DEF,
*     AD_PARA_INVALID_SFE_SET_USER_DEF,
*     AD_CFG_NULL_SFE_DEL_USER_DEF,
*     AD_PARA_INVALID_SFE_DEL_USER_DEF,
*     AD_RULE_NOT_EXIST_SFE_DEL_USER_DEF,
*     AD_NULL_INPUT_SFE_USER_DEF_OPENLIST,
*     AD_OPEN_FAIL_SFE_USER_DEF_OPENLIST,
*     AD_NULL_INPUT_SFE_USER_DEF_GETNEXT,
*     AD_GET_FAIL_SFE_USER_DEF_GETNEXT,
*     AD_NULL_INPUT_SFE_USER_DEF_CLOSELIST,
*     AD_CLOSE_FAIL_SFE_USER_DEF_CLOSELIST,
*     AD_RATE_COUNT_MALLOC_ERR_SRC_HASH_TABLE_NAMEID,
*     AD_RATE_COUNT_ADD_NAME_ERR_SRC_HASH_TABLE_NAMEID,
*     AD_RATE_COUNT_CREATE_TIMER_ERR_SRC_HASH_TABLE,
*     AD_RATE_COUNT_MALLOC_ERR_DST_HASH_TABLE_NAMEID,
*     AD_RATE_COUNT_ADD_NAME_ERR_DST_HASH_TABLE_NAMEID,
*     AD_RATE_COUNT_CREATE_TIMER_ERR_DST_HASH_TABLE,
*     AD_RATE_COUNT_MALLOC_ERR_IF_HASH_TABLE_NAMEID,
*     AD_RATE_COUNT_ADD_NAME_ERR_IF_HASH_TABLE_NAMEID,
*     AD_RATE_COUNT_CREATE_TIMER_ERR_IF_HASH_TABLE,
*     AD_ARP_MISS_PARA_MALLOC_ERR_SFE_INIT_CFG,
*     AD_ARP_MISS_PARA_ADD_NAME_ERR_SFE_INIT_CFG,
*     AD_ARP_MISS_RATECOUNT_MALLOC_ERR_SFE_INIT_CFG,
*     AD_ARP_MISS_RATECOUNT_ADD_NAME_ERR_SFE_INIT_CFG,
*     AD_CFG_NULL_SFE_SET_ARP_MISS,
*     AD_NULL_INPUT_SFE_SET_ARP_MISS,
*     AD_INVALID_INPUT_SFE_SET_ARP_MISS,
*     AD_CFG_NULL_SFE_GET_ARP_MISS,
*     AD_NULL_INPUT_SFE_GET_ARP_MISS,
*     AD_CFG_NULL_SFE_SET_ATK_DBG_FLG,
*     AD_INVALID_INPUT_SFE_SET_ATK_DBG_FLG,
*     AD_CFG_NULL_SFE_GET_ATK_DBG_FLAG,
*     AD_NULL_INPUT_SFE_GET_ATK_DBG_FLAG,
*     AD_INVALID_INPUT_SFE_GET_ATK_DBG_FLG,
*     AD_DBG_FOR_ATK_MALLOC_ERR_SFE_INIT_CFG,
*     AD_DBG_FOR_ATK_ADD_NAME_ERR_SFE_INIT_CFG,
*     AD_BROADCAST_DST_SMURF_SH,
*     AD_LOOPBACK_DST_SMURF_SH,
*     AD_ILLEGAL_DST_SMURF_SH,
*     AD_DST_SUBNET_OF_CLASS_A_SMURF_SH,
*     AD_DST_SUBNET_OF_CLASS_B_SMURF_SH,
*     AD_DST_SUBNET_OF_CLASS_C_SMURF_SH,
*     AD_MULTICAST_DST_SMURF_SH,
*     AD_DST_SUBNET_BROADCAST_SMURF_SH,
*     AD_DST_INVLID_SMURF_SH,
*     AD_IPADDR_HOST,
*     AD_ERR_GET_IF_CFG_PRECONFIG_FAIL,
*     AD_ERR_GET_FLOOD_CFG_PRECONFIG_FAIL,
*     AD_ERR_MALLOC_AD_MALFORM_CONFIG,
*     AD_ERR_ADD_NAME_DB_AD_MALFORM_CONFIG,
*     AD_ERR_GET_MAX_PKT_SIZE_PRECONFIG_FAIL,
*     AD_ERR_GET_MIN_FRAGMENT_SIZE_PRECONFIG_FAIL,
*     AD_ERR_FLOOD_PARA_VAR_MALLOC_FAIL,
*     AD_ERR_FLOOD_PARA_VAR_ADD_NAME_DB_FAIL,
*     AD_ERR_FLOOD_PARA_VAR_GET_PRECONFIG_FAIL,
*     AD_ERR_GET_MAX_IP_PKTS_HANDLED_PRECONFIG_FAIL,
*     AD_ERR_GET_MAX_FRAGMENTS_HANDLED_PRECONFIG_FAIL,
*     AD_FRAG_TABL_INIT_FAIL_FOR_TEARDROP,
*     AD_TEARDROP_MALLOC_ERR_FRAG_TABLE_NAMEID,
*     AD_TEARDROP_ADD_NAME_ERR_FRAG_TABLE_NAMEID,
*     AD_TEARDROP_CREATE_TIMER_ERR_FRAG_TABLE,
*     AD_INVALID_FLOOD_TYPE_INPUT_SFE_SET_FLOOD,
*     AD_INTERFACE_NOT_CONFIGURED,
*     AD_MAX_ERRCODE
* } AD_ERROR_CODE_E;
* @endcode 
* 
* @par Description
* This enum is used to store the error codes for attack defense module.
* 
* @datastruct AD_OK=FW_OK Indicates normal return.
* @datastruct AD_ERR=FWCOMMON_ADMODID+1 Indicates error.
* @datastruct AD_ERR_MALLOC_AD_MALFORM_CFG_S Indicates allocated shared memory failed.
* @datastruct AD_ERR_ADD_NAME_DB_MALFORM_CFG_S Indicates bind name for shared memory failed.
* @datastruct AD_ERR_MALLOC_AD_CFG_S Indicates allocated shared memory failed.
* @datastruct AD_ERR_ADD_NAME_DB_AD_CFG_S Indicates bind name for shared memory failed.
* @datastruct AD_HASH_FAIL_IF_CFG_SFE_INIT_CFG Indicates hash table operation failed.
* @datastruct AD_HASH_FAIL_FLOOD_IP_CFG_SFE_INIT_CFG Indicates hash table operation failed.
* @datastruct AD_MALLOC_FAIL_FLOOD_GLOBAL_CFG_SFE_INIT_CFG Indicates allocated shared memory failed.
* @datastruct AD_ADD_NAME_FAIL_SFE_INIT_CFG Indicates bind name for shared memory failed.
* @datastruct AD_INVALID_INPUT_SFE_ENABLE_ATK_BY_TYPE Indicates invalid input parameter.
* @datastruct AD_CFG_NULL_SFE_ENABLE_ATK_BY_TYPE Indicates global configuration of AD module not initialized.
* @datastruct AD_INVALID_INPUT_SFE_SET_MALFORM Indicates invalid input parameter.
* @datastruct AD_CFG_NULL_SFE_SET_MALFORM Indicates global configuration of AD module not initialized.
* @datastruct AD_TYPE_ERR_SFE_SET_MALFORM Indicates wrong attack type.
* @datastruct AD_IF_CFG_HASH_NULL_SFE_ENABLE_ATK_DEFEND Indicates global configuration of AD module not initialized.
* @datastruct AD_INVALID_INPUT_SFE_ENABLE_ATK_DEFEND Indicates invalid input parameter.
* @datastruct AD_HASH_TABLE_FULL_SFE_ENABLE_ATK_DEFEND Indicates hash table is full.
* @datastruct AD_HASH_FAIL_SFE_ENABLE_ATK_DEFEND Indicates hash table operation failed.
* @datastruct AD_HASH_FAIL_SFE_AD_IS_ENABLE_ATK_DEFEND Indicates hash table operation failed.
* @datastruct AD_INVALID_INPUT_SFE_GET_MALFORM Indicates invalid input parameter.
* @datastruct AD_CFG_NULL_SFE_GET_MALFORM Indicates global configuration of AD module not initialized.
* @datastruct AD_TYPE_ERR_SFE_GET_MALFORM Indicates wrong attack type.
* @datastruct AD_INVALID_INPUT_SFE_SET_FLOOD Indicates invalid input parameter. 
* @datastruct AD_CFG_NULL_SFE_SET_FLOOD Indicates global configuration of AD module not initialized.
* @datastruct AD_CFG_OBJ_TYPE_ERR_SFE_SET_FLOOD Indicates wrong flooding defense configuration type.
* @datastruct AD_HASH_TABLE_FULL_SFE_SET_FLOOD Indicates hash table is full.
* @datastruct AD_HASH_FAIL_SFE_SET_FLOOD Indicates hash table operation failed.
* @datastruct AD_BROADCAST_IPSPOOFING_SH Indicates address is a broadcast address.
* @datastruct AD_IP_NOT_IN_FIB_IPSPOOFING_SH Indicates address does not exist in FIB.
* @datastruct AD_INTERFACE_NOT_SAME_IPSPOOFING_SH Indicates inbound interface and outbound interface are not same.
* @datastruct AD_INVALID_INPUT_CPY_FLOOD_PARA Indicates invalid input parameter.
* @datastruct AD_INVALID_DEFENSE_SWITCH_CPY_FLOOD_PARA Indicates invalid input parameter.
* @datastruct AD_FLOOD_RATE_OUTRANGE_CPY_FLOOD_PARA Indicates invalid input parameter.
* @datastruct AD_INVALID_BLK_SWITCH_CPY_FLOOD_PARA Indicates invalid input parameter.
* @datastruct AD_FLOOD_BLK_TIMEOUT_OUTRANGE_CPY_FLOOD_PARA Indicates invalid input parameter.
* @datastruct AD_INVALID_LOG_SWITCH_CPY_FLOOD_PARA Indicates invalid input parameter.
* @datastruct AD_INVALID_INPUT_CPY_FLOOD_PARA_TO_IP_HASH_ITEM Indicates invalid input parameter.
* @datastruct AD_FLOOD_TYPE_ERR_CPY_FLOOD_PARA_TO_IP_HASH_ITEM Indicates wrong flooding attack type.
* @datastruct AD_INVALID_INPUT_CPY_FLOOD_PARA_TO_IF_HASH_ITEM Indicates invalid input parameter.
* @datastruct AD_FLOOD_TYPE_ERR_CPY_FLOOD_PARA_TO_IF_HASH_ITEM Indicates wrong flooding attack type.
* @datastruct AD_INVALID_INPUT_SET_GLOBAL_FLOOD_PARA Indicates invalid input parameter.
* @datastruct AD_FLOOD_TYPE_ERR_SET_GLOBAL_FLOOD_PARA Indicates wrong flooding attack type.
* @datastruct AD_CFG_NULL_SFE_DEL_FLOOD Indicates global configuration of AD module not initialized.
* @datastruct AD_CFG_OBJ_TYPE_ERR_SFE_DEL_FLOOD Indicates wrong flooding defense configuration type.
* @datastruct AD_HASH_FAIL_SFE_DEL_FLOOD Indicates hash table operation failed.
* @datastruct AD_SCAN_PARA_MALLOC_ERR_SFE_INIT_CFG Indicates allocation of shared memory for global scan attack defense 
* configuration failed.
* @datastruct AD_SCAN_PARA_ADD_NAME_ERR_SFE_INIT_CFG Indicates bind name for shared memory of global scan attack 
* defense configuration failed.
* @datastruct AD_SWEEP_PARA_MALLOC_ERR_SFE_INIT_CFG Indicates allocation of shared memory for global sweep attack 
* defense configuration failed.
* @datastruct AD_SWEEP_PARA_ADD_NAME_ERR_SFE_INIT_CFG Indicates bind name for shared memory of global sweep attack 
* defense configuration failed.
* @datastruct AD_CFG_NULL_SFE_SET_SCAN_PARA Indicates global configuration for scan or sweep attack defense is not 
* initialized.
* @datastruct AD_NULL_INPUT_SFE_SET_SCAN_PARA Indicates invalid input paramter.
* @datastruct AD_PARA_INVALID_SFE_SET_SCAN_PARA Indicates invalid input paramter.
* @datastruct AD_ATTACK_TYPE_ERR_SFE_SET_SCAN_PARA Indicates wrong attack type.
* @datastruct AD_CFG_NULL_SFE_GET_SCAN_PARA Indicates global configuration for scan or sweep attack defense is not 
* initialized.
* @datastruct AD_NULL_INPUT_SFE_GET_SCAN_PARA Indicates invalid input paramter.
* @datastruct AD_ATTACK_TYPE_ERR_SFE_GET_SCAN_PARA Indicates wrong attack type.
* @datastruct AD_NULL_INPUT_IS_ENABLE_DEFEND Indicates invalid input paramter.
* @datastruct AD_NULL_INPUT_SFE_IF_OPENLIST Indicates NULL pointer as input parameter.
* @datastruct AD_OPEN_FAIL_SFE_IF_OPENLIST Indicates open interface defense configuration list failed.
* @datastruct AD_NULL_INPUT_SFE_IF_GETNEXT Indicates NULL pointer as input parameter.
* @datastruct AD_GET_FAIL_SFE_IF_GETNEXT Indicates get next item of interface defense configuration list failed.
* @datastruct AD_NULL_INPUT_SFE_IF_CLOSELIST Indicates NULL pointer as input parameter.
* @datastruct AD_CLOSE_FAIL_SFE_IF_CLOSELIST Indicates closing interface defense configuration list failed.
* @datastruct AD_CFG_NULL_SFE_GET_GLOBAL_FLOOD_PARA Indicates global configuration for flooding defense is not 
* initialized.
* @datastruct AD_NULL_INPUT_SFE_GET_GLOBAL_FLOOD_PARA Indicates NULL pointer as input parameter.
* @datastruct AD_FLOOD_TYPE_ERR_SFE_GET_GLOBAL_FLOOD_PARA Indicates invalid flooding attack type as input parameter.
* @datastruct AD_NULL_INPUT_SFE_FLOODPARAIP_OPENLIST Indicates NULL pointer as input parameter.
* @datastruct AD_OPEN_FAIL_SFE_FLOODPARAIP_OPENLIST Indicates open IP level flood defense configuration list failed.
* @datastruct AD_NULL_INPUT_SFE_FLOODPARAIP_GETNEXT Indicates NULL pointer as input parameter.
* @datastruct AD_GET_FAIL_SFE_FLOODPARAIP_GETNEXT Indicates get next item in IP level flood defense configuration 
* list failed.
* @datastruct AD_NULL_INPUT_SFE_FLOODPARAIP_CLOSELIST Indicates NULL pointer as input parameter.
* @datastruct AD_CLOSE_FAIL_SFE_FLOODPARAIP_CLOSELIST Indicates closing IP level flood defense configuration list 
* failed.
* @datastruct AD_ERR_STAT_AD_STATISTICS_NOT_INITIATLIZED_CLEARSTAT Indicates global statistics variable is not 
* initialized.
* @datastruct SFE_AD_ERR_STAT_INPUT_NULLPTR_GETSTAT Indicates input statistics pointer is null.
* @datastruct AD_ERR_STAT_AD_STATISTICS_NOT_INITIATLIZED_GETSTAT Indicates global statistics variable is not 
* initialized.
* @datastruct SFE_AD_ERR_STAT_INPUT_NULLPTR_GETVCPUSTAT Indicates input statistics pointer is null.
* @datastruct AD_ERR_STAT_AD_STATISTICS_NOT_INITIATLIZED_GETVCPUSTAT Indicates global statistics variable is not 
* initialized.
* @datastruct SFE_AD_ERR_STAT_INVALID_VCPU_GETVCPUSTAT Indicates invalid VCPU is passed as input.
* @datastruct AD_STAT_INIT_ERR_SFE_INIT_CFG Indicates failed to initialize statistics for attack defense.
* @datastruct AD_USER_DEF_PARA_MALLOC_ERR_SFE_INIT_CFG Indicates malloc for user defined defense global variable failed.
* @datastruct AD_USER_DEF_PARA_ADD_NAME_ERR_SFE_INIT_CFG Indicates bind name for user defined defense global variable 
* failed.
* @datastruct AD_CFG_NULL_SFE_SET_USER_DEF Indicates User defined defense global variable is not initialized.
* @datastruct AD_NULL_INPUT_SFE_SET_USER_DEF Indicates NULL pointer as input parameter while setting user defined 
* defense rule.
* @datastruct AD_PARA_INVALID_SFE_SET_USER_DEF Indicates invalid input parameter while setting user defined defense 
* rule.
* @datastruct AD_CFG_NULL_SFE_DEL_USER_DEF Indicates user defined defense global variable is not initialized.
* @datastruct AD_PARA_INVALID_SFE_DEL_USER_DEF Indicates invalid input parameter while deleting user defined defense 
* rule.
* @datastruct AD_RULE_NOT_EXIST_SFE_DEL_USER_DEF Indicates the user defined defense rule to be deleted does not exist.
* @datastruct AD_NULL_INPUT_SFE_USER_DEF_OPENLIST Indicates NULL pointer as input parameter while opening list of 
* user defined defense rule.
* @datastruct AD_OPEN_FAIL_SFE_USER_DEF_OPENLIST Indicates opening list of user defined defense rule failed.
* @datastruct AD_NULL_INPUT_SFE_USER_DEF_GETNEXT Indicates NULL pointer as input parameter while getting next user 
* defined defense rule.
* @datastruct AD_GET_FAIL_SFE_USER_DEF_GETNEXT Indicates getting next user defined defense rule failed.
* @datastruct AD_NULL_INPUT_SFE_USER_DEF_CLOSELIST Indicates NULL pointer as input parameter while closing list of 
* user defined defense rule.
* @datastruct AD_CLOSE_FAIL_SFE_USER_DEF_CLOSELIST Indicates closing list of user defined defense rule failed.
* @datastruct AD_RATE_COUNT_MALLOC_ERR_SRC_HASH_TABLE_NAMEID Indicates malloc error for initializing source hash table 
* timer name ID.
* @datastruct AD_RATE_COUNT_ADD_NAME_ERR_SRC_HASH_TABLE_NAMEID Indicates error in adding name for initializing source 
* hash table timer name ID.
* @datastruct AD_RATE_COUNT_CREATE_TIMER_ERR_SRC_HASH_TABLE Indicates error in creating timer error for initializing 
* source hash table timer.
* @datastruct AD_RATE_COUNT_MALLOC_ERR_DST_HASH_TABLE_NAMEID Indicates malloc error for initializing destination hash 
* table timer name ID.
* @datastruct AD_RATE_COUNT_ADD_NAME_ERR_DST_HASH_TABLE_NAMEID Indicates error in adding name for initializing 
* destination hash table timer name ID.
* @datastruct AD_RATE_COUNT_CREATE_TIMER_ERR_DST_HASH_TABLE Indicates error in creating timer for initializing 
* destination hash table timer.
* @datastruct AD_RATE_COUNT_MALLOC_ERR_IF_HASH_TABLE_NAMEID Indicates malloc error for initializing interface hash 
* table timer name ID.
* @datastruct AD_RATE_COUNT_ADD_NAME_ERR_IF_HASH_TABLE_NAMEID Indicates error in adding name for initializing interface 
* hash table timer name ID.
* @datastruct AD_RATE_COUNT_CREATE_TIMER_ERR_IF_HASH_TABLE Indicates error in creating timer for initializing interface 
* hash table timer.
* @datastruct AD_ARP_MISS_PARA_MALLOC_ERR_SFE_INIT_CFG Indicates malloc for ARP MISS attack defense global variable 
* failed.
* @datastruct AD_ARP_MISS_PARA_ADD_NAME_ERR_SFE_INIT_CFG Indicates bind name for ARP MISS attack defense global 
* variable failed.
* @datastruct AD_ARP_MISS_RATECOUNT_MALLOC_ERR_SFE_INIT_CFG Indicates malloc for ARP MISS rate count global variable 
* failed.
* @datastruct AD_ARP_MISS_RATECOUNT_ADD_NAME_ERR_SFE_INIT_CFG Indicates bind name for ARP MISS rate count global 
* variable failed.
* @datastruct AD_CFG_NULL_SFE_SET_ARP_MISS Indicates global configuration of ARP MISS attack defense is not initialized.
* @datastruct AD_NULL_INPUT_SFE_SET_ARP_MISS Indicates NULL pointer as input parameter while setting ARP MISS attack 
* defense parameter.
* @datastruct AD_INVALID_INPUT_SFE_SET_ARP_MISS Indicates invalid input parameter while setting ARP MISS attack defense 
* parameter.
* @datastruct AD_CFG_NULL_SFE_GET_ARP_MISS Indicates global configuration of ARP MISS attack defense is not initialized.
* @datastruct AD_NULL_INPUT_SFE_GET_ARP_MISS Indicates NULL pointer as input parameter while getting ARP MISS attack 
* defense parameter.
* @datastruct AD_CFG_NULL_SFE_SET_ATK_DBG_FLG Indicates attack type debug configuration is not initialized.
* @datastruct AD_INVALID_INPUT_SFE_SET_ATK_DBG_FLG Indicates invalid input parameter for SFE_AD_SetAtkDebugFlag.
* @datastruct AD_CFG_NULL_SFE_GET_ATK_DBG_FLAG Indicates attack type debug configuration is not initialized.
* @datastruct AD_NULL_INPUT_SFE_GET_ATK_DBG_FLAG Indicates input parameter is NULL for SFE_AD_GetAtkDebugFlag.
* @datastruct AD_INVALID_INPUT_SFE_GET_ATK_DBG_FLG Indicates invalid input attack type for SFE_AD_GetAtkDebugFlag.
* @datastruct AD_DBG_FOR_ATK_MALLOC_ERR_SFE_INIT_CFG Indicates failed to allocate memory for variable 
* g_pu32ADDebug_share.
* @datastruct AD_DBG_FOR_ATK_ADD_NAME_ERR_SFE_INIT_CFG Indicates name DB addition failed for the variable 
* g_pu32ADDebug_share.
* @datastruct AD_BROADCAST_DST_SMURF_SH Indicates destination IP is broadcasted.
* @datastruct AD_LOOPBACK_DST_SMURF_SH Indicates destination IP is loop back.
* @datastruct AD_ILLEGAL_DST_SMURF_SH Indicates destination IP is illegal.
* @datastruct AD_DST_SUBNET_OF_CLASS_A_SMURF_SH Indicates destination IP is subnet of class A.
* @datastruct AD_DST_SUBNET_OF_CLASS_B_SMURF_SH Indicates destination IP is subnet of class B.
* @datastruct AD_DST_SUBNET_OF_CLASS_C_SMURF_SH Indicates destination IP is subnet of class C.
* @datastruct AD_MULTICAST_DST_SMURF_SH Indicates destination IP is multicasted.
* @datastruct AD_DST_SUBNET_BROADCAST_SMURF_SH Indicates destination IP is subnet broadcasted.
* @datastruct AD_DST_INVLID_SMURF_SH Indicates invalid destination.
* @datastruct AD_IPADDR_HOST Indicates address is proper.
* @datastruct AD_ERR_GET_IF_CFG_PRECONFIG_FAIL Indicates error in getting the interface pre configuration data.
* @datastruct AD_ERR_GET_FLOOD_CFG_PRECONFIG_FAIL Indicates error in getting flood pre configuration data.
* @datastruct AD_ERR_MALLOC_AD_MALFORM_CONFIG Indicates error in allocating memory for Malformed specific configuration structure
* @datastruct AD_ERR_ADD_NAME_DB_AD_MALFORM_CONFIG Indicates bind name for Malformed specific configuration structure failed
* @datastruct AD_ERR_GET_MAX_PKT_SIZE_PRECONFIG_FAIL Indicates getting pre configuration value for maximum packet size failed.
* @datastruct AD_ERR_GET_MIN_FRAGMENT_SIZE_PRECONFIG_FAIL Indicates getting pre configuration value for minimum fragment size failed
* @datastruct AD_ERR_FLOOD_PARA_VAR_MALLOC_FAIL Indicates memory allocation failed for the variable which stores
* number of flood parameters to be considered in flood attack.
* @datastruct AD_ERR_FLOOD_PARA_VAR_ADD_NAME_DB_FAIL Indicates registering name failed for the variable which stores
* number of flood parameters to be considered in flood attack.
* @datastruct AD_ERR_FLOOD_PARA_VAR_GET_PRECONFIG_FAIL Indicates getting pre configured value failed for the variable which stores
* number of flood parameters to be considered in flood attack.
* @datastruct AD_ERR_GET_MAX_IP_PKTS_HANDLED_PRECONFIG_FAIL Indicates getting pre configured value of the varibale 
* which stores the no of IP packets to be analyzed in teardrop attack.
* @datastruct AD_ERR_GET_MAX_FRAGMENTS_HANDLED_PRECONFIG_FAIL Indicates getting pre configured value of the varibale 
* which stores the no of fragments of one IP packet to be analyzed in teardrop attack.
* @datastruct AD_FRAG_TABL_INIT_FAIL_FOR_TEARDROP Indicates initialization of hash failed which stores IP packet data
* in teardrop attack.
* @datastruct AD_TEARDROP_MALLOC_ERR_FRAG_TABLE_NAMEID Indicates allocating memory for fragmentation table
* timer name failed.
* @datastruct AD_TEARDROP_ADD_NAME_ERR_FRAG_TABLE_NAMEID Indicates adding the name of fragmentation table
* timer name to name DB failed.
* @datastruct AD_TEARDROP_CREATE_TIMER_ERR_FRAG_TABLE Indicates craetion of timer for fragmentation table
* failed
* @datastruct AD_INVALID_FLOOD_TYPE_INPUT_SFE_SET_FLOOD Indicates invalid flood type is recieved as input.
* @datastruct AD_INTERFACE_NOT_CONFIGURED Indicates given interface is not configured.
* @datastruct AD_MAX_ERRCODE Indicates the last field of this enum.
*/
typedef enum enumADERRCODE
{
    AD_OK = 0,
    AD_ERR = FWIPSAFE_FW_ATK_BEGIN_RET_CODE +  1,
    AD_ERR_MALLOC_AD_MALFORM_CFG_S,
    AD_ERR_ADD_NAME_DB_MALFORM_CFG_S,
    AD_ERR_MALLOC_AD_CFG_S,
    AD_ERR_ADD_NAME_DB_AD_CFG_S,
    AD_HASH_FAIL_IF_CFG_SFE_INIT_CFG,
    AD_HASH_FAIL_FLOOD_IP_CFG_SFE_INIT_CFG,
    AD_MALLOC_FAIL_FLOOD_GLOBAL_CFG_SFE_INIT_CFG,
    AD_ADD_NAME_FAIL_SFE_INIT_CFG,
    AD_INVALID_INPUT_SFE_ENABLE_ATK_BY_TYPE,
    AD_CFG_NULL_SFE_ENABLE_ATK_BY_TYPE,
    AD_INVALID_INPUT_SFE_SET_MALFORM,
    AD_CFG_NULL_SFE_SET_MALFORM,
    AD_TYPE_ERR_SFE_SET_MALFORM,
    AD_IF_CFG_HASH_NULL_SFE_ENABLE_ATK_DEFEND,
    AD_INVALID_INPUT_SFE_ENABLE_ATK_DEFEND,
    AD_HASH_TABLE_FULL_SFE_ENABLE_ATK_DEFEND,
    AD_HASH_FAIL_SFE_ENABLE_ATK_DEFEND,
    AD_HASH_FAIL_SFE_AD_IS_ENABLE_ATK_DEFEND,
    AD_INVALID_INPUT_SFE_GET_MALFORM,
    AD_CFG_NULL_SFE_GET_MALFORM,
    AD_TYPE_ERR_SFE_GET_MALFORM,
    AD_INVALID_INPUT_SFE_SET_FLOOD,
    AD_CFG_NULL_SFE_SET_FLOOD,
    AD_CFG_OBJ_TYPE_ERR_SFE_SET_FLOOD,
    AD_HASH_TABLE_FULL_SFE_SET_FLOOD,
    AD_HASH_FAIL_SFE_SET_FLOOD,
    AD_BROADCAST_IPSPOOFING_SH,
    AD_IP_NOT_IN_FIB_IPSPOOFING_SH,
    AD_INTERFACE_NOT_SAME_IPSPOOFING_SH,
    AD_INVALID_INPUT_CPY_FLOOD_PARA,
    AD_INVALID_DEFENSE_SWITCH_CPY_FLOOD_PARA,
    AD_FLOOD_RATE_OUTRANGE_CPY_FLOOD_PARA,
    AD_INVALID_BLK_SWITCH_CPY_FLOOD_PARA,
    AD_FLOOD_BLK_TIMEOUT_OUTRANGE_CPY_FLOOD_PARA,
    AD_INVALID_LOG_SWITCH_CPY_FLOOD_PARA,
    AD_INVALID_INPUT_CPY_FLOOD_PARA_TO_IP_HASH_ITEM,
    AD_FLOOD_TYPE_ERR_CPY_FLOOD_PARA_TO_IP_HASH_ITEM,
    AD_INVALID_INPUT_CPY_FLOOD_PARA_TO_IF_HASH_ITEM,
    AD_FLOOD_TYPE_ERR_CPY_FLOOD_PARA_TO_IF_HASH_ITEM,
    AD_INVALID_INPUT_SET_GLOBAL_FLOOD_PARA,
    AD_FLOOD_TYPE_ERR_SET_GLOBAL_FLOOD_PARA,
    AD_CFG_NULL_SFE_DEL_FLOOD,
    AD_CFG_OBJ_TYPE_ERR_SFE_DEL_FLOOD,
    AD_HASH_FAIL_SFE_DEL_FLOOD,
    AD_SCAN_PARA_MALLOC_ERR_SFE_INIT_CFG,
    AD_SCAN_PARA_ADD_NAME_ERR_SFE_INIT_CFG,
    AD_SWEEP_PARA_MALLOC_ERR_SFE_INIT_CFG,
    AD_SWEEP_PARA_ADD_NAME_ERR_SFE_INIT_CFG,
    AD_CFG_NULL_SFE_SET_SCAN_PARA,
    AD_NULL_INPUT_SFE_SET_SCAN_PARA,
    AD_PARA_INVALID_SFE_SET_SCAN_PARA,
    AD_ATTACK_TYPE_ERR_SFE_SET_SCAN_PARA,
    AD_CFG_NULL_SFE_GET_SCAN_PARA,
    AD_NULL_INPUT_SFE_GET_SCAN_PARA,
    AD_ATTACK_TYPE_ERR_SFE_GET_SCAN_PARA,
    AD_NULL_INPUT_IS_ENABLE_DEFEND,
    AD_NULL_INPUT_SFE_IF_OPENLIST,
    AD_OPEN_FAIL_SFE_IF_OPENLIST,
    AD_NULL_INPUT_SFE_IF_GETNEXT,
    AD_GET_FAIL_SFE_IF_GETNEXT,
    AD_NULL_INPUT_SFE_IF_CLOSELIST,
    AD_CLOSE_FAIL_SFE_IF_CLOSELIST,
    AD_CFG_NULL_SFE_GET_GLOBAL_FLOOD_PARA,
    AD_NULL_INPUT_SFE_GET_GLOBAL_FLOOD_PARA,
    AD_FLOOD_TYPE_ERR_SFE_GET_GLOBAL_FLOOD_PARA,
    AD_NULL_INPUT_SFE_FLOODPARAIP_OPENLIST,
    AD_OPEN_FAIL_SFE_FLOODPARAIP_OPENLIST,
    AD_NULL_INPUT_SFE_FLOODPARAIP_GETNEXT,
    AD_GET_FAIL_SFE_FLOODPARAIP_GETNEXT,
    AD_NULL_INPUT_SFE_FLOODPARAIP_CLOSELIST,
    AD_CLOSE_FAIL_SFE_FLOODPARAIP_CLOSELIST,
    
    AD_ERR_STAT_AD_STATISTICS_NOT_INITIATLIZED_CLEARSTAT,
    SFE_AD_ERR_STAT_INPUT_NULLPTR_GETSTAT,
    AD_ERR_STAT_AD_STATISTICS_NOT_INITIATLIZED_GETSTAT,
    SFE_AD_ERR_STAT_INPUT_NULLPTR_GETVCPUSTAT,
    AD_ERR_STAT_AD_STATISTICS_NOT_INITIATLIZED_GETVCPUSTAT,
    SFE_AD_ERR_STAT_INVALID_VCPU_GETVCPUSTAT,

    AD_STAT_INIT_ERR_SFE_INIT_CFG,

    AD_USER_DEF_PARA_MALLOC_ERR_SFE_INIT_CFG,
    AD_USER_DEF_PARA_ADD_NAME_ERR_SFE_INIT_CFG,
    AD_CFG_NULL_SFE_SET_USER_DEF,
    AD_NULL_INPUT_SFE_SET_USER_DEF,
    AD_PARA_INVALID_SFE_SET_USER_DEF,
    AD_CFG_NULL_SFE_DEL_USER_DEF,
    AD_PARA_INVALID_SFE_DEL_USER_DEF,
    AD_RULE_NOT_EXIST_SFE_DEL_USER_DEF,
    AD_NULL_INPUT_SFE_USER_DEF_OPENLIST,
    AD_OPEN_FAIL_SFE_USER_DEF_OPENLIST,
    AD_NULL_INPUT_SFE_USER_DEF_GETNEXT,
    AD_GET_FAIL_SFE_USER_DEF_GETNEXT,
    AD_NULL_INPUT_SFE_USER_DEF_CLOSELIST,
    AD_CLOSE_FAIL_SFE_USER_DEF_CLOSELIST,

    AD_RATE_COUNT_MALLOC_ERR_SRC_HASH_TABLE_NAMEID,
    AD_RATE_COUNT_ADD_NAME_ERR_SRC_HASH_TABLE_NAMEID,
    AD_RATE_COUNT_CREATE_TIMER_ERR_SRC_HASH_TABLE,
    AD_RATE_COUNT_MALLOC_ERR_DST_HASH_TABLE_NAMEID,
    AD_RATE_COUNT_ADD_NAME_ERR_DST_HASH_TABLE_NAMEID,
    AD_RATE_COUNT_CREATE_TIMER_ERR_DST_HASH_TABLE,
    AD_RATE_COUNT_MALLOC_ERR_IF_HASH_TABLE_NAMEID,
    AD_RATE_COUNT_ADD_NAME_ERR_IF_HASH_TABLE_NAMEID,
    AD_RATE_COUNT_CREATE_TIMER_ERR_IF_HASH_TABLE,

    AD_ARP_MISS_PARA_MALLOC_ERR_SFE_INIT_CFG,
    AD_ARP_MISS_PARA_ADD_NAME_ERR_SFE_INIT_CFG,
    AD_ARP_MISS_RATECOUNT_MALLOC_ERR_SFE_INIT_CFG,
    AD_ARP_MISS_RATECOUNT_ADD_NAME_ERR_SFE_INIT_CFG,
    AD_CFG_NULL_SFE_SET_ARP_MISS,
    AD_NULL_INPUT_SFE_SET_ARP_MISS,
    AD_INVALID_INPUT_SFE_SET_ARP_MISS,
    AD_CFG_NULL_SFE_GET_ARP_MISS,
    AD_NULL_INPUT_SFE_GET_ARP_MISS,

    AD_CFG_NULL_SFE_SET_ATK_DBG_FLG,
    AD_INVALID_INPUT_SFE_SET_ATK_DBG_FLG,
    AD_CFG_NULL_SFE_GET_ATK_DBG_FLAG,
    AD_NULL_INPUT_SFE_GET_ATK_DBG_FLAG,
    AD_INVALID_INPUT_SFE_GET_ATK_DBG_FLG,

    AD_DBG_FOR_ATK_MALLOC_ERR_SFE_INIT_CFG,
    AD_DBG_FOR_ATK_ADD_NAME_ERR_SFE_INIT_CFG,
    
    AD_BROADCAST_DST_SMURF_SH,
    AD_LOOPBACK_DST_SMURF_SH,
    AD_ILLEGAL_DST_SMURF_SH,
    AD_DST_SUBNET_OF_CLASS_A_SMURF_SH,
    AD_DST_SUBNET_OF_CLASS_B_SMURF_SH,
    AD_DST_SUBNET_OF_CLASS_C_SMURF_SH,
    AD_MULTICAST_DST_SMURF_SH,
    AD_DST_SUBNET_BROADCAST_SMURF_SH,
    AD_DST_INVLID_SMURF_SH,
    AD_IPADDR_HOST,

    AD_ERR_GET_IF_CFG_PRECONFIG_FAIL,
    AD_ERR_GET_FLOOD_CFG_PRECONFIG_FAIL,

    AD_ERR_MALLOC_AD_MALFORM_CONFIG,
    AD_ERR_ADD_NAME_DB_AD_MALFORM_CONFIG,

    AD_ERR_GET_MAX_PKT_SIZE_PRECONFIG_FAIL,
    AD_ERR_GET_MIN_FRAGMENT_SIZE_PRECONFIG_FAIL,

    AD_ERR_FLOOD_PARA_VAR_MALLOC_FAIL,
    AD_ERR_FLOOD_PARA_VAR_ADD_NAME_DB_FAIL,
    AD_ERR_FLOOD_PARA_VAR_GET_PRECONFIG_FAIL,

    AD_ERR_GET_MAX_IP_PKTS_HANDLED_PRECONFIG_FAIL,
    AD_ERR_GET_MAX_FRAGMENTS_HANDLED_PRECONFIG_FAIL,
    AD_FRAG_TABL_INIT_FAIL_FOR_TEARDROP,
    AD_TEARDROP_MALLOC_ERR_FRAG_TABLE_NAMEID,
    AD_TEARDROP_ADD_NAME_ERR_FRAG_TABLE_NAMEID,
    AD_TEARDROP_CREATE_TIMER_ERR_FRAG_TABLE,

    AD_INVALID_FLOOD_TYPE_INPUT_SFE_SET_FLOOD,
    AD_INTERFACE_NOT_CONFIGURED,

    AD_MAX_ERRCODE

} AD_ERROR_CODE_E;


/**
* @defgroup AD_InitCfg AD_InitCfg
* @ingroup ADF Attack Defense Functions
* @par Prototype
* @code
* extern UINT32 AD_InitCfg();
* @endcode 
* 
* @par Description
* This function is used to initialize global configuration for Attack Defense module.
* 
* @param[in]   []
* @param[out]   []
* 
* @retval UINT32 On Success [AD_OK|]
* @retval UINT32 Indicates failure of malloc upon malformed configuration [AD_ERR_MALLOC_AD_MALFORM_CFG_S|]
* @retval UINT32 Indicates failure of bind name upon malformed configuration [AD_ERR_ADD_NAME_DB_MALFORM_CFG_S|]
* @retval UINT32 Indicates failure of malloc [AD_ERR_MALLOC_AD_CFG_S|]
* @retval UINT32 Indicates failure of bind name [AD_ERR_ADD_NAME_DB_AD_CFG_S|]
* @retval UINT32 Indicates failure to get the pre configuration of maximum no of Interfaces configured in flood attack [AD_ERR_GET_IF_CFG_PRECONFIG_FAIL|]
* @retval UINT32 Indicates failure to get the pre configuration of maximum no of IPs configured in flood attack [AD_ERR_GET_FLOOD_CFG_PRECONFIG_FAIL|]
* @retval UINT32 Indicates hash table operation failed for interface configuration [AD_HASH_FAIL_IF_CFG_SFE_INIT_CFG|]
* @retval UINT32 Indicates hash table operation failed for IP configuration [AD_HASH_FAIL_FLOOD_IP_CFG_SFE_INIT_CFG|]
* @retval UINT32 Indicates allocated shared memory failed for global configuration [AD_MALLOC_FAIL_FLOOD_GLOBAL_CFG_SFE_INIT_CFG|]
* @retval UINT32 Indicates bind name for shared memory failed [AD_ADD_NAME_FAIL_SFE_INIT_CFG|]
* @retval UINT32 Indicates failure of malloc upon scan configuration [AD_SCAN_PARA_MALLOC_ERR_SFE_INIT_CFG|]
* @retval UINT32 Indicates failure of bind name upon scan configuration [AD_SCAN_PARA_ADD_NAME_ERR_SFE_INIT_CFG|]
* @retval UINT32 Indicates failure of malloc upon sweep configuration [AD_SWEEP_PARA_MALLOC_ERR_SFE_INIT_CFG|]
* @retval UINT32 Indicates failure of bind name upon sweep configuration [AD_SWEEP_PARA_ADD_NAME_ERR_SFE_INIT_CFG|]
* @retval UINT32 Indicates failure of malloc upon user defined attack configuration [AD_USER_DEF_PARA_MALLOC_ERR_SFE_INIT_CFG|]
* @retval UINT32 Indicates failure of bind name upon user defined attack configuration [AD_USER_DEF_PARA_ADD_NAME_ERR_SFE_INIT_CFG|]
* @retval UINT32 Indicates failure of malloc upon ARP miss configuration [AD_ARP_MISS_PARA_MALLOC_ERR_SFE_INIT_CFG|]
* @retval UINT32 Indicates failure of bind name upon ARP miss configuration [AD_ARP_MISS_PARA_ADD_NAME_ERR_SFE_INIT_CFG|]
* @retval UINT32 Indicates failure of malloc upon ARP miss flood configuration [AD_ARP_MISS_RATECOUNT_MALLOC_ERR_SFE_INIT_CFG|]
* @retval UINT32 Indicates failure of bind name upon ARP miss flood configuration [AD_ARP_MISS_RATECOUNT_ADD_NAME_ERR_SFE_INIT_CFG|]
* @retval UINT32 Indicates failure of malloc upon debug configuration for all attacks [AD_DBG_FOR_ATK_MALLOC_ERR_SFE_INIT_CFG|]
* @retval UINT32 Indicates failure of bind name upon debug configuration for all attacks [AD_DBG_FOR_ATK_ADD_NAME_ERR_SFE_INIT_CFG|]
* @retval UINT32 Indicates failure of malloc upon malformed parameter configuration [AD_ERR_MALLOC_AD_MALFORM_CONFIG|]
* @retval UINT32 Indicates failure of bind name upon malformed parameter configuration [AD_ERR_ADD_NAME_DB_AD_MALFORM_CONFIG|]
* @retval UINT32 Indicates getting pre configuration value for maximum packet size failed.
* [AD_ERR_GET_MAX_PKT_SIZE_PRECONFIG_FAIL|]
* @retval UINT32 Indicates getting pre configuration value for minimum fragment size failed. 
* [AD_ERR_GET_MIN_FRAGMENT_SIZE_PRECONFIG_FAIL|]
* @retval UINT32 Indicates failure of malloc upon flood parameter configuration [AD_ERR_FLOOD_PARA_VAR_MALLOC_FAIL|]
* @retval UINT32 Indicates failure of bind name upon flood parameter configuration [AD_ERR_FLOOD_PARA_VAR_ADD_NAME_DB_FAIL|]
* @retval UINT32 Indicates getting pre configuration value for flood parameter failed.
* [AD_ERR_FLOOD_PARA_VAR_GET_PRECONFIG_FAIL|]
* @retval UINT32 Indicates getting pre configuration value for maximum packets handled in
* tear drop attack failed. [AD_ERR_GET_MAX_IP_PKTS_HANDLED_PRECONFIG_FAIL|]
* @retval UINT32 Indicates getting pre configuration value for maximum fragments of one packet handled in
* tear drop attack failed. [AD_ERR_GET_MAX_FRAGMENTS_HANDLED_PRECONFIG_FAIL|]
* @retval UINT32 Indicates failure of frag table initialization. [AD_FRAG_TABL_INIT_FAIL_FOR_TEARDROP|]
* @retval UINT32 Indicates failure of malloc upon fragment table creation [AD_TEARDROP_MALLOC_ERR_FRAG_TABLE_NAMEID|]
* @retval UINT32 Indicates failure of bind name upon fragment table creation  [AD_TEARDROP_ADD_NAME_ERR_FRAG_TABLE_NAMEID|]
* @retval UINT32 Indicates failure of timer creation for fragment table. [AD_TEARDROP_CREATE_TIMER_ERR_FRAG_TABLE|]
* @retval UINT32 Indicates failure of statistics initialization for all attacks. [AD_STAT_INIT_ERR_SFE_INIT_CFG|]
*
* @par Dependency
* ad_inc.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related TopicAD_InitCfgs
* None
*/ 
extern UINT32 AD_InitCfg();

/**
* @defgroup AD_EnableAtkDefendByType AD_EnableAtkDefendByType
* @ingroup ADF Attack Defense Functions
* @par Prototype
* @code
* extern UINT32 AD_EnableAtkDefendByType(
*     UINT32 u32Enable,
*     UINT32 u32AtkType 
* );
* @endcode 
* 
* @par Description
* This function is used to enable or disable attack defense by the type of attack.
* 
* @param[in] u32Enable Indicates attack defense has to be enabled or disabled
* [1-Enable/0-Disable]
* @param[in] u32AtkType Indicates the type of attack. For more details, refer AD_ATTACK_TYPE_E. []
* @param[out]   []
* 
* @retval UINT32 On Success [AD_OK|]
* @retval UINT32 Indicates global configuration of AD module not initialized [AD_CFG_NULL_SFE_ENABLE_ATK_BY_TYPE|]
* @retval UINT32 Indicates invalid input parameter [AD_INVALID_INPUT_SFE_ENABLE_ATK_BY_TYPE|]
* 
* @par Dependency
* ad_inc.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* AD_IsEnableAtkDefendByType
*/ 
extern UINT32 AD_EnableAtkDefendByType(
    UINT32 u32Enable,         
    UINT32 u32AtkType   
);


/**
* @defgroup AD_IsEnableAtkDefendByType AD_IsEnableAtkDefendByType
* @ingroup ADF Attack Defense Functions
* @par Prototype
* @code
* extern UINT32 AD_IsEnableAtkDefendByType(UINT32 u32AtkType);
* @endcode 
* 
* @par Description
* This function is used to check whether an attack type defense is enabled or not.
* 
* @param[in] u32AtkType Indicates the type of attack []
* @param[out]   []
* 
* @retval UINT32 Indicates attack defense module is disabled [0|]
* @retval UINT32 Indicates attack defense module is enabled [1|]
* 
* @par Dependency
* ad_inc.h
* 
* 
* @par Note
* \n
* 
*	- You should not pass an invalid u32AtkType to the function.
*	- The value of u32AtkType should between ATCK_IP_SPOOF and ATCK_ALL (excluding ATCK_ALL).
*	- This function will not check the validation of u32AtkType.
*	- The configuration of AD module should be initialized before calling this function.
* 
* 
* @par Related Topics
* AD_EnableAtkDefendByType
*/ 
extern UINT32 AD_IsEnableAtkDefendByType(UINT32 u32AtkType);


/**
* @defgroup AD_EnableAtkDefend AD_EnableAtkDefend
* @ingroup ADF Attack Defense Functions
* @par Prototype
* @code
* extern UINT32 AD_EnableAtkDefend(UINT32 u32Enable,
*                                      UINT32 u32IfIndex);
* @endcode 
* 
* @par Description
* This function is used to enable attack defense on the specified interface.
* 
* @param[in] u32Enable Indicates whether attack defense is enabled or disabled 
* [1-Enabled/0-Disabled]
* @param[in] u32IfIndex Indicates the network interface index []
* @param[out]   []
* 
* @retval UINT32 On Success [AD_OK|]
* @retval UINT32 Indicates global configuration of AD module not initialized 
* [AD_IF_CFG_HASH_NULL_SFE_ENABLE_ATK_DEFEND|]
* @retval UINT32 Indicates invalid input parameter [AD_INVALID_INPUT_SFE_ENABLE_ATK_DEFEND|]
* @retval UINT32 Indicates hash table is full [AD_HASH_TABLE_FULL_SFE_ENABLE_ATK_DEFEND|]
* @retval UINT32 Indicates hash table operation failed [AD_HASH_FAIL_SFE_ENABLE_ATK_DEFEND|]
* 
* @par Dependency
* ad_inc.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* AD_IsEnableAtkDefend
*/ 
extern UINT32 AD_EnableAtkDefend(UINT32 u32Enable,
                              UINT32 u32IfIndex);


/**
* @defgroup AD_IsEnableAtkDefend AD_IsEnableAtkDefend
* @ingroup ADF Attack Defense Functions
* @par Prototype
* @code
* extern UINT32 AD_IsEnableAtkDefend(UINT32 u32IfIndex, UINT32 *pu32IsEnable);
* @endcode 
* 
* @par Description
* This function is used to check whether the attack defense module is enabled 
* or not in certain network interface.
* 
* @param[in] u32IfIndex Indicates the network interface index []
* @param[out] pu32IsEnable Indicates pointer to store the value which tells attack defense is enabled or disabled 
* [1-Enable/0-Disable]
* 
* @retval UINT32 On Success [AD_OK|]
* @retval UINT32 Indicates hash table operation failed [AD_HASH_FAIL_SFE_AD_IS_ENABLE_ATK_DEFEND|]
* @retval UINT32 Indicates recieved null pointer as input [AD_NULL_INPUT_IS_ENABLE_DEFEND|]
* @retval UINT32 Indicates recieved interface is not configured [AD_INTERFACE_NOT_CONFIGURED|]
* 
* @par Dependency
* ad_inc.h
* 
* 
* @par Note
* \n
* 
*	- This function will not check the validity of input parameters. Caller to this function should ensure the validity 
*     of the input parameters.
*	- The global variable should also be initialized by calling the API AD_InitCfg, before calling this function.
* 
* 
* @par Related Topics
* AD_EnableAtkDefend
*/ 
extern UINT32 AD_IsEnableAtkDefend(UINT32 u32IfIndex, UINT32 *pu32IsEnable);


/**
* @defgroup AD_SetAtkMalformPara AD_SetAtkMalformPara
* @ingroup ADF Attack Defense Functions
* @par Prototype
* @code
* extern UINT32 AD_SetAtkMalformPara(
*     UINT32 u32AtkType,
*     AD_MALFORM_PARA_S * pstAtkPara);
* @endcode 
* 
* @par Description
* This function is used to set oafish pkt attack parameter by the type.
* The types of attacks can be the following.
*	- ATCK_IP_SPOOF            : IP spoofing attack
*	- ATCK_LAND                : Land attack
*	- ATCK_SMURF               : Smurf attack
*	- ATCK_TCPFLAG             : TCP Flag attack
*	- ATCK_WINNUKE             : Winnuke attack
*	- ATCK_ICMP_REDIRECT       : ICMP Redirect attack
*	- ATCK_ICMP_UNREACHABLE    : ICMP Unreachable attack
*	- ATCK_ICMP_TIMESTAMP      : ICMP Timestamp attack
*	- ATCK_PING_OF_DEATH       : Ping of Death attack
*	- ATCK_FRAGGLE             : Fraggle attack
*	- ATCK_RECORD_ROUTE        : Record route attack
*	- ATCK_LOOSE_SOURCE_ROUTE  : Loose source route attack
*	- ATCK_STRICT_SOURCE_ROUTE : Strict source route attack
*	- ATCK_IP_TINY_FRAG        : IP tiny fragment attack
*	- ATCK_TEARDROP            : Teardrop attack
*	- ATCK_ALL                 : All the malformed attacks
*  
* @param[in] u32AtkType Indicates the type of attack 
* [ATCK_IP_SPOOF/ATCK_LAND/ATCK_SMURF/ATCK_TCPFLAG/ATCK_WINNUKE/ATCK_ICMP_REDIRECT/ATCK_ICMP_UNREACHABLE/
*ATCK_ICMP_TIMESTAMP/ATCK_PING_OF_DEATH/ATCK_FRAGGLE/ATCK_RECORD_ROUTE/ATCK_LOOSE_SOURCE_ROUTE/
*ATCK_STRICT_SOURCE_ROUTE/ATCK_ALL]
* @param[in] pstAtkPara Indicates structure that contains attack parameters []
* @param[out]   []
* 
* @retval UINT32 On Success [AD_OK|]
* @retval UINT32 Indicates invalid input for attack parameter [AD_INVALID_INPUT_SFE_SET_MALFORM|]
* @retval UINT32 Indicates wrong attack type [AD_TYPE_ERR_SFE_SET_MALFORM|]
* @retval UINT32 Indicates global configuration of AD module not initialized [AD_CFG_NULL_SFE_SET_MALFORM|]
* 
* @par Dependency
* ad_inc.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* AD_GetAtkMalformPara
*/ 
extern UINT32 AD_SetAtkMalformPara(
    UINT32 u32AtkType,                 
    AD_MALFORM_PARA_S * pstAtkPara  
);


/**
* @defgroup AD_GetAtkMalformPara AD_GetAtkMalformPara
* @ingroup ADF Attack Defense Functions
* @par Prototype
* @code
* extern UINT32 AD_GetAtkMalformPara(
*     UINT32 u32AtkType,
*     AD_MALFORM_PARA_S * pstAtkPara
* );
* @endcode 
* 
* @par Description
* This function is used to get the configured parameters for each malformed attack.
* It supports the check for the following types of attack:
*	- ATCK_IP_SPOOF            : IP spoofing attack
*	- ATCK_LAND                : Land attack
*	- ATCK_SMURF               : Smurf attack
*	- ATCK_TCPFLAG             : TCP Flag attack
*	- ATCK_WINNUKE             : Winnuke attack
*	- ATCK_ICMP_REDIRECT       : ICMP Redirect attack
*	- ATCK_ICMP_UNREACHABLE    : ICMP Unreachable attack
*	- ATCK_ICMP_TIMESTAMP      : ICMP Timestamp attack
*	- ATCK_PING_OF_DEATH       : Ping of Death attack
*	- ATCK_FRAGGLE             : Fraggle attack
*	- ATCK_RECORD_ROUTE        : Record route attack
*	- ATCK_LOOSE_SOURCE_ROUTE  : Loose source route attack
*	- ATCK_STRICT_SOURCE_ROUTE : Strict source route attack
*	- ATCK_IP_TINY_FRAG        : IP tiny fragment attack
*	- ATCK_TEARDROP            : Teardrop attack
* 
* @param[in] u32AtkType Indicates the type of atatck whose configuration is needed []
* @param[out] pstAtkPara Indicates the pointer to the structure to store the configured data []
* 
* @retval UINT32 On Success [AD_OK|]
* @retval UINT32 Indicates invalid input parameter [AD_INVALID_INPUT_SFE_GET_MALFORM|]
* @retval UINT32 Indicates wrong attack type [AD_TYPE_ERR_SFE_GET_MALFORM|]
* @retval UINT32 Indicates global configuration of AD module not initialized [AD_CFG_NULL_SFE_GET_MALFORM|]
* 
* @par Dependency
* ad_inc.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* AD_SetAtkMalformPara
*/ 
extern UINT32 AD_GetAtkMalformPara(
    UINT32 u32AtkType,                   
    AD_MALFORM_PARA_S * pstAtkPara  
);


/**
* @defgroup AD_SetFloodPara AD_SetFloodPara
* @ingroup ADF Attack Defense Functions
* @par Prototype
* @code
* extern UINT32 AD_SetFloodPara(UINT32  u32FloodType,
*                            AD_FLOOD_CFG_S * pstFloodCfg);
* @endcode 
* 
* @par Description
* This function is used to set the configuration parameter for flooding attack defense.
* The flooding attack types are:
*	- AD_ICMP_FLOOD
*	- AD_UDP_FLOOD
*	- AD_SYN_FLOOD
*	- AD_ARP_FLOOD
* 
* @param[in] u32FloodType Indicates the type of flooding attack 
* [AD_ICMP_FLOOD/AD_UDP_FLOOD/AD_SYN_FLOOD/AD_ARP_FLOOD]
* @param[in] pstFloodCfg Indicates the structure that contains the flood defense 
* attack parameters []
* @param[out]   []
* 
* @retval UINT32 On Success [AD_OK|]
* @retval UINT32 Indicates invalid input parameter [AD_INVALID_INPUT_SFE_SET_FLOOD|]
* @retval UINT32 Indicates global configuration of AD module is not initialized [AD_CFG_NULL_SFE_SET_FLOOD|]
* @retval UINT32 Indicates Input flood parameter pointer is NULL [AD_INVALID_INPUT_SET_GLOBAL_FLOOD_PARA|]
* @retval UINT32 Indicates wrong flooding attack type [AD_FLOOD_TYPE_ERR_SET_GLOBAL_FLOOD_PARA|]
* @retval UINT32 Indicates invalid input parameter [AD_INVALID_INPUT_CPY_FLOOD_PARA_TO_IF_HASH_ITEM|]
* @retval UINT32 Indicates wrong flooding attack type [AD_FLOOD_TYPE_ERR_CPY_FLOOD_PARA_TO_IF_HASH_ITEM|]
* @retval UINT32 Indicates invalid input parameter [AD_INVALID_INPUT_CPY_FLOOD_PARA_TO_IP_HASH_ITEM|]
* @retval UINT32 Indicates invalid input parameter [AD_INVALID_DEFENSE_SWITCH_CPY_FLOOD_PARA|]
* @retval UINT32 Indicates invalid input parameter [AD_FLOOD_RATE_OUTRANGE_CPY_FLOOD_PARA|]
* @retval UINT32 Indicates invalid input parameter [AD_INVALID_BLK_SWITCH_CPY_FLOOD_PARA|]
* @retval UINT32 Indicates invalid input parameter [AD_FLOOD_BLK_TIMEOUT_OUTRANGE_CPY_FLOOD_PARA|]
* @retval UINT32 Indicates invalid input parameter [AD_INVALID_LOG_SWITCH_CPY_FLOOD_PARA|]
* @retval UINT32 Indicates hash table is full [AD_HASH_TABLE_FULL_SFE_SET_FLOOD|]
* @retval UINT32 Indicates hash table operation failed [AD_HASH_FAIL_SFE_SET_FLOOD|]
* @retval UINT32 Indicates invalid flooding attack type [AD_INVALID_FLOOD_TYPE_INPUT_SFE_SET_FLOOD|]
* 
* @par Dependency
* ad_inc.h
* 
* 
* @par Note
* \n
* 
* Caller to this function can free the memory pointed by pstFloodCfg after
* calling this function.
* 
* 
* @par Related Topics
* AD_DelFloodPara
*/ 
extern UINT32 AD_SetFloodPara(UINT32  u32FloodType,
                           AD_FLOOD_CFG_S* pstFloodCfg);


/**
* @defgroup AD_DelFloodPara AD_DelFloodPara
* @ingroup ADF Attack Defense Functions
* @par Prototype
* @code
* extern UINT32 AD_DelFloodPara(UINT32 u32FloodCfgType, UINT32 u32Key);
* @endcode 
* 
* @par Description
* This function is used to delete configuration parameter for flooding attack defense.
* The flood defense configuration types supported are:
*	- AD_PARA_IF
*	- AD_PARA_IP
* The flood types(AD_ICMP_FLOOD, AD_UDP_FLOOD, AD_SYN_FLOOD, AD_ARP_FLOOD) are not 
* cosidered here. This is because, deleting the configuration of an IP / Interface means
* deleting the settings of all flood types  configured under it.
*
* @param[in] u32FloodCfgType Indicates the type of flood defense
* [AD_PARA_IF/AD_PARA_IP]
* @param[in] u32Key Indicates the key to search the configuration parameter. It can be an address or 
* index of an interface. []
* @param[out]   []
* 
* @retval UINT32 On Success [AD_OK|]
* @retval UINT32 Indicates that the global configuration variable is invalid [AD_CFG_NULL_SFE_DEL_FLOOD|]
* @retval UINT32 Indicates that the attack configuration type input is wrong [AD_CFG_OBJ_TYPE_ERR_SFE_DEL_FLOOD|]
* @retval UINT32 Indicates failure of hash table operation [AD_HASH_FAIL_SFE_DEL_FLOOD|]
* 
* @par Dependency
* ad_inc.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* AD_SetFloodPara
*/ 
extern UINT32 AD_DelFloodPara(UINT32 u32FloodCfgType, UINT32 u32Key);


/**
* @defgroup AD_SetScanPara AD_SetScanPara
* @ingroup ADF Attack Defense Functions
* @par Prototype
* @code
* extern UINT32 AD_SetScanPara(UINT32 u32ScanType, AD_SCAN_PARA_S *pstScanPara);
* @endcode 
* 
* @par Description
* This function is used to set configuration parameter for scan and sweep attack defense. 
* Scan and sweep configuration types supported are:
*	- ATCK_IP_SWEEP
*	- ATCK_PORTSCAN
* 
* @param[in] u32ScanType Indicates the type of configuration parameter for scan and sweep.
* [ATCK_IP_SWEEP/ATCK_PORTSCAN]
* @param[in] pstScanPara Indicates scan and sweep attack defense parameter. For more details, refer AD_SCAN_PARA_S []
* @param[out]   []
* 
* @retval UINT32 On Success [AD_OK|]
* @retval UINT32 Indicates global configuration for scan/sweep attack defense is not initialized 
* [AD_CFG_NULL_SFE_SET_SCAN_PARA|]
* @retval UINT32 Indicates invalid input parameter [AD_NULL_INPUT_SFE_SET_SCAN_PARA|]
* @retval UINT32 Indicates invalid input parameter [AD_PARA_INVALID_SFE_SET_SCAN_PARA|]
* @retval UINT32 Indicates wrong attack type [AD_ATTACK_TYPE_ERR_SFE_SET_SCAN_PARA|]
* 
* @par Dependency
* ad_inc.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* AD_GetScanPara
*/ 
extern UINT32 AD_SetScanPara(UINT32 u32ScanType, AD_SCAN_PARA_S *pstScanPara);


/**
* @defgroup AD_ShowScanPara AD_ShowScanPara
* @ingroup ADF Attack Defense Functions
* @par Prototype
* @code
* extern VOID AD_ShowScanPara();
* @endcode 
* 
* @par Description
* This function is used to display parameter for scan and sweep attack defense on console or
* any other output device.
* 
* @param[in]   []
* @param[out]   []
* 
* @retval VOID This function does not return any value. [|]
* 
* @par Dependency
* ad_inc.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
*	- AD_GetScanPara
*	- AD_SetScanPara
*/
extern VOID AD_ShowScanPara(VOID);


/**
* @defgroup AD_GetScanPara AD_GetScanPara
* @ingroup ADF Attack Defense Functions
* @par Prototype
* @code
* extern UINT32 AD_GetScanPara(UINT32 u32ScanType, AD_SCAN_PARA_S * pstScanPara);
* @endcode 
* 
* @par Description
* This function is used to get the configuration parameter for scan and sweep attack defense.
* The types of scan and sweep attacks supported are:
*	- ATCK_IP_SWEEP
*	- ATCK_PORTSCAN
* 
* @param[in] u32ScanType Indicates the type of scan/sweep attack type. []
* @param[out] pstScanPara Indicates scan/sweep attack defense parameter. For more details, refer AD_SCAN_PARA_S. []
* 
* @retval UINT32 On Success [AD_OK|]
* @retval UINT32 Indicates global configuration for scan/sweep attack defense is not initialized 
* [AD_CFG_NULL_SFE_GET_SCAN_PARA|]
* @retval UINT32 Indicates invalid input parameter [AD_NULL_INPUT_SFE_GET_SCAN_PARA|]
* @retval UINT32 Indicates wrong attack type [AD_ATTACK_TYPE_ERR_SFE_GET_SCAN_PARA|]
* 
* @par Dependency
* ad_inc.h
* 
* 
* @par Note
* \n
* 
* Caller to this function should allocate memory for AD_SCAN_PARA_S, and pass the pointer to the memory 
* to this function. The caller will get a copy of the defense parameter, on successful execution this function.
* 
* 
* @par Related Topics
* AD_SetScanPara
*/
extern UINT32 AD_GetScanPara(UINT32 u32ScanType, AD_SCAN_PARA_S *pstScanPara);

 /**
* @defgroup AD_RateCountTimeOutHandle AD_RateCountTimeOutHandle
* @ingroup ADF Attack Defense Functions
* @par Prototype
* @code
* extern VOID AD_RateCountTimeOutHandle(UINT32 u32Para, UINT32 u32TimerName);
* @endcode 
* 
* @par Description
* This functions is used to timeout handle in RPU environment
* 
* @param[in]   []
* @param[out]   []
* 
* @retval VOID This function does not return any value. [|]
* 
* @par Dependency
* ad_inc.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* None
*/ 
extern VOID AD_RateCountTimeOutHandle(UINT32 u32Para, UINT32 u32TimerName);

/**
* @defgroup AD_ShowGlobalDefenseStatus AD_ShowGlobalDefenseStatus
* @ingroup ADF Attack Defense Functions
* @par Prototype
* @code
* extern VOID AD_ShowGlobalDefenseStatus(VOID);
* @endcode 
* 
* @par Description
* This function is used to show global status of attack defense.
* 
* @param[in]   []
* @param[out]   []
* 
* @retval VOID This function does not return any value. [|]
* 
* @par Dependency
* ad_inc.h
* 
* 
* @par Note
* \n
* 
* The AD module should be initialized before calling this function.
* 
* 
* @par Related Topics
* None
*/
extern VOID AD_ShowGlobalDefenseStatus(VOID);


/**
* @defgroup AD_ClearStat AD_ClearStat
* @ingroup ADF Attack Defense Functions
* @par Prototype
* @code
* extern VOID AD_ClearStat(VOID);
* @endcode 
* 
* @par Description
* This function is used to reset all the statistic variables to zero.
* 
* @param[in]   []
* @param[out]   []
* 
* @retval VOID This function does not return any value. [|]
* 
* @par Dependency
* ad_inc.h
* 
* 
* @par Note
* \n
* 
* The AD module should be initialized before calling this function.
* 
* 
* @par Related Topics
* None
*/
extern VOID AD_ClearStat(VOID);

/**
* @defgroup AD_GetStat AD_GetStat
* @ingroup ADF Attack Defense Functions
* @par Prototype
* @code
* extern UINT32 AD_GetStat( AD_STAT_S * pstADStat);
* @endcode 
* 
* @par Description
* This function is used to return the sum of all the VCPU and all attack statistics.
* 
* @param[in,out] pstADStat It stores statistics of all VCPU and Attack types. []
* 
* @retval UINT32 On success [AD_OK|]
* @retval UINT32 Indicates input statistics pointer is null [SFE_AD_ERR_STAT_INPUT_NULLPTR_GETSTAT|]
* @retval UINT32 Indicates statistics is not initialized [AD_ERR_STAT_AD_STATISTICS_NOT_INITIATLIZED_GETSTAT|]
* 
* @par Dependency
* ad_inc.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* None
*/
extern UINT32 AD_GetStat(AD_STAT_S* pstADStat);

/**
* @defgroup AD_GetVCPUStat AD_GetVCPUStat
* @ingroup ADF Attack Defense Functions
* @par Prototype
* @code
* extern UINT32 AD_GetVCPUStat(UINT32 u32VCPUNum, AD_STAT_S * pstADStat);
* @endcode 
* 
* @par Description
* This function is used to return the statistic of given VCPU number.
* 
* @param[in] u32VCPUNum VCPU number for which the statistics is required. []
* @param[in,out] pstADStat The statistics of all VCPU and attack types will be stored in the 
* input parameter pstADStat []
* 
* @retval UINT32 On success [AD_OK|]
* @retval UINT32 Indicates input VCPU type [SFE_AD_ERR_STAT_INVALID_VCPU_GETVCPUSTAT|]
* @retval UINT32 Indicates input statistics pointer is null [SFE_AD_ERR_STAT_INPUT_NULLPTR_GETVCPUSTAT|]
* @retval UINT32 Indicates global statistics variable not initialized 
* [AD_ERR_STAT_AD_STATISTICS_NOT_INITIATLIZED_GETVCPUSTAT|]
* 
* @par Dependency
* ad_inc.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* None
*/
extern UINT32 AD_GetVCPUStat(UINT32 u32VCPUNum, AD_STAT_S* pstADStat);


/**
* @defgroup AD_ShowStat AD_ShowStat
* @ingroup ADF Attack Defense Functions
* @par Prototype
* @code
* extern VOID AD_ShowStat(VOID);
* @endcode 
* 
* @par Description
* This function is used to show the total statistics.
* 
* @param[in]   []
* @param[out]   []
* 
* @retval VOID This function does not return any value. [|]
* 
* @par Dependency
* ad_inc.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* None
*/
extern VOID AD_ShowStat(VOID);

/**
* @defgroup AD_ShowVCPUStat AD_ShowVCPUStat
* @ingroup ADF Attack Defense Functions
* @par Prototype
* @code
* extern VOID AD_ShowVCPUStat(UINT32 u32VCPUNum);
* @endcode 
* 
* @par Description
* This function is used to show the statistic of given VCPU number.
* 
* @param[in] u32VCPUNum VCPU number for which the statistics is required []
* @param[out]   []
* 
* @retval VOID This function does not return any value. [|]
* 
* @par Dependency
* ad_inc.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* None
*/
extern VOID AD_ShowVCPUStat(UINT32 u32VCPUNum);

/**
* @defgroup AD_IfCfg_OpenList AD_IfCfg_OpenList
* @ingroup ADF Attack Defense Functions
* @par Prototype
* @code
* extern UINT32 AD_IfCfg_OpenList(VOID **ppHandle);
* @endcode 
* 
* @par Description
* This function is used to open the list of interface defense configuration.
* 
* @param[in]   []
* @param[out] ppHandle Indicates handle of interface defense configuration list []
* 
* @retval UINT32 Indicates there are more items [FWCOMMON_ITERATOR_ITEM_EXIST|]
* @retval UINT32 Indicates there are no more items [FWCOMMON_ITERATOR_ITEM_NOT_EXIST|]
* @retval UINT32 Indicates NULL pointer as input parameter [AD_NULL_INPUT_SFE_IF_OPENLIST|]
* @retval UINT32 Indicates opening interface defense configuration list failed [AD_OPEN_FAIL_SFE_IF_OPENLIST|]
* 
* @par Dependency
* ad_inc.h
* 
* 
* @par Note
* \n
* 
* The AD module should be initialized before calling this function.
* 
* 
* @par Related Topics
* None
*/
extern UINT32 AD_IfCfg_OpenList(VOID **ppHandle);


/**
* @defgroup AD_IfCfg_GetNext AD_IfCfg_GetNext
* @ingroup ADF Attack Defense Functions
* @par Prototype
* @code
* extern UINT32 AD_IfCfg_GetNext(VOID *pHandle, AD_IF_CFG_INFO_S * pstIfCfg);
* @endcode 
* 
* @par Description
* This function is used to get next item of interface defense configuration list.
* 
* @param[in] pHandle Indicates handle of interface defense configuration list []
* @param[out] pstIfCfg Indicates pointer to interface defense configuration []
* 
* @retval UINT32 Indicates there are more items [FWCOMMON_ITERATOR_ITEM_EXIST|]
* @retval UINT32 Indicates there are no more items [FWCOMMON_ITERATOR_ITEM_NOT_EXIST|]
* @retval UINT32 Indicates NULL pointer as input parameter [AD_NULL_INPUT_SFE_IF_GETNEXT|]
* @retval UINT32 Indicates getting next item of interface defense configuration list failed 
* [AD_GET_FAIL_SFE_IF_GETNEXT|]
* 
* @par Dependency
* ad_inc.h
* 
* 
* @par Note
* \n
* 
* The AD module should be initialized before calling this function.
* 
* 
* @par Related Topics
* None
*/
extern UINT32 AD_IfCfg_GetNext(VOID *pHandle, AD_IF_CFG_INFO_S* pstIfCfg);


/**
* @defgroup AD_IfCfg_CloseList AD_IfCfg_CloseList
* @ingroup ADF Attack Defense Functions
* @par Prototype
* @code
* extern UINT32 AD_IfCfg_CloseList(VOID *pHandle);
* @endcode 
* 
* @par Description
* This function is used to close the list of interface defense configuration.
* 
* @param[in] pHandle Indicates handle of interface defense configuration list []
* @param[out]   []
* 
* @retval UINT32 Indicates no error occurred for iterator [FWCOMMON_ITERATOR_OK|]
* @retval UINT32 Indicates NULL pointer as input parameter [AD_NULL_INPUT_SFE_IF_CLOSELIST|]
* @retval UINT32 Indicates closing interface defense configuration list failed [AD_CLOSE_FAIL_SFE_IF_CLOSELIST|]
* 
* @par Dependency
* ad_inc.h
* 
* 
* @par Note
* \n
* 
* The AD module should be initialized before calling this function.
* 
* 
* @par Related Topics
* None
*/
extern UINT32 AD_IfCfg_CloseList(VOID *pHandle);


/**
* @defgroup AD_ShowIfCfg AD_ShowIfCfg
* @ingroup ADF Attack Defense Functions
* @par Prototype
* @code
* extern VOID AD_ShowIfCfg(VOID);
* @endcode 
* 
* @par Description
* This function is used to show the content of interface defense configuration list.
* 
* @param[in]   []
* @param[out]   []
* 
* @retval VOID This function does not return any value. [|]
* 
* @par Dependency
* ad_inc.h
* 
* 
* @par Note
* \n
* 
* The AD module should be initialized before calling this function.
* 
* 
* @par Related Topics
* None
*/
extern VOID AD_ShowIfCfg(VOID);

/**
* @defgroup AD_GetGlobalFloodPara AD_GetGlobalFloodPara
* @ingroup ADF Attack Defense Functions
* @par Prototype
* @code
* extern UINT32 AD_GetGlobalFloodPara(UINT32 u32FloodType, AD_FLOOD_PARA_S *pstFloodPara);
* @endcode 
* 
* @par Description
* This function is used to get the global configuration parameter for flooding attack defense.
* The flooding attack types supported are:
*	- AD_ICMP_FLOOD
*	- AD_SYN_FLOOD
*	- AD_UDP_FLOOD
* 
* @param[in] u32FloodType Indicates the flooding attack type [AD_ICMP_FLOOD/AD_SYN_FLOOD/AD_UDP_FLOOD]
* @param[out] pstFloodPara Indicates pointer to flooding defense parameter []
* 
* @retval UINT32 On success [AD_OK|]
* @retval UINT32 Indicates global configuration for flooding defense is not initialized 
* [AD_CFG_NULL_SFE_GET_GLOBAL_FLOOD_PARA|]
* @retval UINT32 Indicates NULL pointer as input parameter [AD_NULL_INPUT_SFE_GET_GLOBAL_FLOOD_PARA|]
* @retval UINT32 Indicates invalid flooding attack type as input parameter 
* [AD_FLOOD_TYPE_ERR_SFE_GET_GLOBAL_FLOOD_PARA|]
* 
* @par Dependency
* ad_inc.h
* 
* 
* @par Note
* \n
* 
* The AD module should be initialized before calling this function.
* 
* 
* @par Related Topics
* None
*/
extern UINT32 AD_GetGlobalFloodPara(UINT32 u32FloodType, AD_FLOOD_PARA_S *pstFloodPara);


/**
* @defgroup AD_ShowGlobalFloodPara AD_ShowGlobalFloodPara
* @ingroup ADF Attack Defense Functions
* @par Prototype
* @code
* extern VOID AD_ShowGlobalFloodPara();
* @endcode 
* 
* @par Description
* This function is used to show the global configuration parameter for flooding attack defense.
* 
* @param[in]   []
* @param[out]   []
* 
* @retval VOID This function does not return any value. [|]
* 
* @par Dependency
* ad_inc.h
* 
* 
* @par Note
* \n
* 
* The AD module should be initialized before calling this function.
* 
* 
* @par Related Topics
* None
*/
extern VOID AD_ShowGlobalFloodPara(VOID);


/**
* @defgroup AD_FloodParaIP_OpenList AD_FloodParaIP_OpenList
* @ingroup ADF Attack Defense Functions
* @par Prototype
* @code
* extern UINT32 AD_FloodParaIP_OpenList(void **ppHandle, AD_FLOOD_PARA_FILTER_S * pstFilter);
* @endcode 
* 
* @par Description
* This function is used to open the IP based flood parameter list.
* 
* @param[in] pstFilter Indicates the filter. It can be NULL. If filter is NULL, this function will 
* get the whole list of IP level flood defense parameter. []
* @param[out] ppHandle Indicates the handle for list. []
* 
* @retval UINT32 Indicates there are more items. [FWCOMMON_ITERATOR_ITEM_EXIST|]
* @retval UINT32 Indicates there are no more items. [FWCOMMON_ITERATOR_ITEM_NOT_EXIST|]
* @retval UINT32 Indicates NULL pointer as input parameter [AD_NULL_INPUT_SFE_FLOODPARAIP_OPENLIST|]
* @retval UINT32 Indicates opening IP level flood defense configuration list failed 
* [AD_OPEN_FAIL_SFE_FLOODPARAIP_OPENLIST|]
* 
* @par Dependency
* ad_inc.h
* 
* 
* @par Note
* \n
* 
* The AD module should be initialized before calling this function.
* 
* 
* @par Related Topics
* None
*/
extern UINT32 AD_FloodParaIP_OpenList(void **ppHandle, AD_FLOOD_PARA_FILTER_S* pstFilter);


/**
* @defgroup AD_FloodParaIP_GetNext AD_FloodParaIP_GetNext
* @ingroup ADF Attack Defense Functions
* @par Prototype
* @code
* extern UINT32 AD_FloodParaIP_GetNext(void *pHandle, AD_FLOOD_PARA_IP_INFO_S * pstFloodParaIPInfo);
* @endcode 
* 
* @par Description
* This function is used to get next entry from the IP based flood parameter list.
* 
* @param[in] pHandle Indicates the handle for list []
* @param[out] pstFloodParaIPInfo Indicates the IP based flood parameter []
* 
* @retval UINT32 Indicates there are more items. [FWCOMMON_ITERATOR_ITEM_EXIST|]
* @retval UINT32 Indicates there are no more items. [FWCOMMON_ITERATOR_ITEM_NOT_EXIST|]
* @retval UINT32 Indicates NULL pointer as input parameter [AD_NULL_INPUT_SFE_FLOODPARAIP_GETNEXT|]
* @retval UINT32 Indicates getting next item in IP level flood defense configuration list failed 
* [AD_GET_FAIL_SFE_FLOODPARAIP_GETNEXT|]
* 
* @par Dependency
* ad_inc.h
* 
* 
* @par Note
* \n
* 
* The AD module should be initialized before calling this function.
* 
* 
* @par Related Topics
* None
*/
extern UINT32 AD_FloodParaIP_GetNext(void *pHandle, AD_FLOOD_PARA_IP_INFO_S* pstFloodParaIPInfo);


/**
* @defgroup AD_FloodParaIP_CloseList AD_FloodParaIP_CloseList
* @ingroup ADF Attack Defense Functions
* @par Prototype
* @code
* extern UINT32 AD_FloodParaIP_CloseList(void *pHandle);
* @endcode 
* 
* @par Description
* This function is used to close IP based flood parameter list.
* 
* @param[in] pHandle Indicates the handle for list []
* @param[out]   []
* 
* @retval UINT32 Indicates no error occurred for iterator [FWCOMMON_ITERATOR_OK|]
* @retval UINT32 Indicates NULL pointer as input parameter [AD_NULL_INPUT_SFE_FLOODPARAIP_CLOSELIST|]
* @retval UINT32 Indicates closing IP level flood defense configuration list failed 
* [AD_CLOSE_FAIL_SFE_FLOODPARAIP_CLOSELIST|]
* 
* @par Dependency
* ad_inc.h
* 
* 
* @par Note
* \n
* 
* The AD module should be initialized before calling this function.
* 
* 
* @par Related Topics
* None
*/
extern UINT32 AD_FloodParaIP_CloseList(void *pHandle);


/**
* @defgroup AD_ShowFloodParaIP AD_ShowFloodParaIP
* @ingroup ADF Attack Defense Functions
* @par Prototype
* @code
* extern VOID AD_ShowFloodParaIP(UINT32 u32IP);
* @endcode 
* 
* @par Description
* This function is used to show IP based flood parameter.
* 
* @param[in] u32IP Indicates the destination IP to be protected from flood attack []
* @param[out]   []
* 
* @retval VOID This function does not return any value. [|]
* 
* @par Dependency
* ad_inc.h
* 
* 
* @par Note
* \n
* 
* The AD module should be initialized before calling this function.
* 
* 
* @par Related Topics
* None
*/
extern VOID AD_ShowFloodParaIP(UINT32 u32IP);


/**
* @defgroup AD_ShowAtkMalformPara AD_ShowAtkMalformPara
* @ingroup ADF Attack Defense Functions
* @par Prototype
* @code
* extern VOID AD_ShowAtkMalformPara();
* @endcode 
* 
* @par Description
* This function is used to show the malform attack defense parameter.
* 
* @param[in]   []
* @param[out]   []
* 
* @retval VOID This function does not return any value. [|]
* 
* @par Dependency
* ad_inc.h
* 
* 
* @par Note
* \n
* 
* The AD module should be initialized before calling this function.
* 
* 
* @par Related Topics
* None
*/
extern VOID AD_ShowAtkMalformPara(VOID);


/**
* @defgroup AD_SetAtkDebugFlag AD_SetAtkDebugFlag
* @ingroup ADF Attack Defense Functions
* @par Prototype
* @code
* UINT32 AD_SetAtkDebugFlag(UINT32 u32DebugFlag, UINT32 u32AtkType);
* @endcode 
* 
* @par Description
* This function enables or disables debug flag for a specific attack type.
* 
* @param[in] u32Enable Indicates whether debug for individual attack type is enabled or disabled.
* It can have the following values:
*	- 1 indicates Enable 
*	- 0 indicates Disable 
* @param[in] u32AtkType Attack type []
* @param[out]   []
* 
* @retval UINT32 On Success [AD_OK|]
* @retval UINT32 Attack type debug configuration not initialized [AD_CFG_NULL_SFE_SET_ATK_DBG_FLG|]
* @retval UINT32 Invalid input parameter [AD_INVALID_INPUT_SFE_SET_ATK_DBG_FLG|]
* 
* @par Dependency
* ad_inc.h
* 
* 
* @par Note
* \n
* 
* The function will change if the enum AD_ATTACK_TYPE_E changes
* 
* 
* @par Related Topics
* None
*/
extern UINT32 AD_SetAtkDebugFlag(UINT32 u32DebugFlag, UINT32 u32AtkType);

/**
* @defgroup AD_GetAtkDebugFlag AD_GetAtkDebugFlag
* @ingroup ADF Attack Defense Functions
* @par Prototype
* @code
* UINT32 AD_GetAtkDebugFlag(UINT32 u32AtkType, UINT32 *pu32DebugFlag);
* @endcode 
* 
* @par Description
* This function gets the debug flag for attack defense.
* 
* @param[in] u32AtkType Attack type []
* @param[out] pu32DebugFlag This parameter can have the following types:
*	- 1 - if debug for the attack type is enabled
*	- 0 - if debug for the attack type is disabled []
* 
* @retval UINT32 On Success [AD_OK|]
* @retval UINT32 Attack type debug configuration not initialized [AD_CFG_NULL_SFE_GET_ATK_DBG_FLAG|]
* @retval UINT32 Indicates input parameter is NULL [AD_NULL_INPUT_SFE_GET_ATK_DBG_FLAG|]
* @retval UINT32 Invalid input attack type [AD_INVALID_INPUT_SFE_GET_ATK_DBG_FLG|]
* 
* @par Dependency
* ad_inc.h
* 
* 
* @par Note
* \n
* 
* The AD module should be initialized before calling this function.
* 
* 
* @par Related Topics
* None
*/
extern UINT32 AD_GetAtkDebugFlag(UINT32 u32AtkType, UINT32 *pu32DebugFlag);

/**
* @defgroup AD_ShowAtkDefendDebugging AD_ShowAtkDefendDebugging
* @ingroup ADF Attack Defense Functions
* @par Prototype
* @code
* VOID AD_ShowAtkDefendDebugging(VOID);
* @endcode 
* 
* @par Description
* This function displays debug status for attack types.
* 
* @param[in]   []
* @param[out]   []
* 
* @retval VOID This function does not return any value. [|]
* 
* @par Dependency
* ad_inc.h
* 
* 
* @par Note
* \n
* 
* The AD module should be initialized before calling this function.
* 
* 
* @par Related Topics
* None
*/
extern VOID AD_ShowAtkDefendDebugging(VOID);


/**
* @defgroup AD_SetArpMissPara AD_SetArpMissPara
* @ingroup ADF Attack Defense Functions
* @par Prototype
* @code
* UINT32 AD_SetArpMissPara(UINT32 u32AtkType, AD_ARP_MISS_PARA_S * pstAtkPara);
* @endcode 
* 
* @par Description
* This function is used to set the configuration for ARP Miss defense.
* 
* @param[in] u32AtkType This parameter is a reserved parameter that can pass any integer value.[]
* @param[in] pstAtkPara This parameter is the pointer to the structure for ARP Miss defense parameter.[]
* @param[out]   []
*
* @retval UINT32 On Success [AD_OK|]
* @retval UINT32 Indicates global configuration of ARP MISS attack defense is not initialized 
* [AD_CFG_NULL_SFE_SET_ARP_MISS|]
* @retval UINT32 Indicates NULL pointer as input parameter while setting ARP MISS attack defense parameter 
* [AD_NULL_INPUT_SFE_SET_ARP_MISS|]
* @retval UINT32 Indicates invalid input parameter while setting ARP MISS attack defense parameter 
* [AD_INVALID_INPUT_SFE_SET_ARP_MISS|]
*
* @par Dependency
* ad_inc.h
* 
* 
* @par Note
* \n
* 
* The AD module should be initialized before calling this function.
* 
* 
* @par Related Topics
* None
*/
extern UINT32 AD_SetArpMissPara(UINT32 u32AtkType,  
                                    AD_ARP_MISS_PARA_S * pstAtkPara);


/**
* @defgroup AD_GetArpMissPara AD_GetArpMissPara
* @ingroup ADF Attack Defense Functions
* @par Prototype
* @code
* UINT32 AD_GetArpMissPara(UINT32 u32AtkType, AD_ARP_MISS_PARA_S * pstAtkPara);
* @endcode 
* 
* @par Description
* This function gets the configuration for ARP Miss defense.
* 
* @param[in] u32AtkType This parameter is a reserved parameter and can pass any integer value.[]
* @param[in] pstAtkPara This parameter is a pointer to the structure for ARP Miss defense parameter.[]
* @param[out]   []
*
* @retval UINT32 On Success [AD_OK|]
* @retval UINT32 Indicates global configuration of ARP MISS attack defense is not initialized 
* [AD_CFG_NULL_SFE_GET_ARP_MISS|]
* @retval UINT32 Indicates NULL pointer as input parameter while getting ARP MISS attack defense parameter 
* [AD_NULL_INPUT_SFE_GET_ARP_MISS|]
*
* @par Dependency
* ad_inc.h
* 
* 
* @par Note
* \n
* 
* The AD module should be initialized before calling this function.
* 
* 
* @par Related Topics
* None
*/
extern UINT32 AD_GetArpMissPara(UINT32 u32AtkType,  
                                    AD_ARP_MISS_PARA_S * pstAtkPara);

/**
* @defgroup AD_ShowArpMissPara AD_ShowArpMissPara
* @ingroup ADF Attack Defense Functions
* @par Prototype
* @code
* VOID AD_ShowArpMissPara(VOID);
* @endcode 
* 
* @par Description
* This function displays the configuration for ARP Miss defense.
* 
* @param[in]   []
* @param[out]   []
*
* @retval VOID This function does not return any value. [|]
*
* @par Dependency
* ad_inc.h
* 
* 
* @par Note
* \n
* 
* The AD module should be initialized before calling this function.
* 
* 
* @par Related Topics
* None
*/
extern VOID AD_ShowArpMissPara();


extern UINT32 AD_SetAtkUserDefined(UINT32 u32AtkType,
    AD_USER_DEFINE_PARA_S * pstAtkPara);

/**
* @defgroup AD_DelAtkUserDefined AD_DelAtkUserDefined
* @ingroup ADF Attack Defense Functions
* @par Prototype
* @code
* UINT32 AD_DelAtkUserDefined(UINT32 u32AtkType, UINT32 u32ID);
* @endcode 
* 
* @par Description
* This function deletes the configuration for user defined attack defense.
* 
* @param[in] u32AtkType This parameter is reseved and can pass any integer value. []
* @param[in] u32ID ID of user defined defense rule. []
* @param[out]   []
* 
* @retval UINT32 On Success [AD_OK|]
* @retval UINT32 Indicates user defined defense global variable is not initialized [AD_CFG_NULL_SFE_DEL_USER_DEF|]
* @retval UINT32 Indicates invalid input parameter while deleting user defined defense rule 
* [AD_PARA_INVALID_SFE_DEL_USER_DEF|]
* @retval UINT32 Indicates the user defined defense rule to be deleted does not exist 
* [AD_RULE_NOT_EXIST_SFE_DEL_USER_DEF|]
* 
* @par Dependency
* ad_inc.h
* 
* 
* @par Note
* \n
* 
* The AD module should be initialized before calling this function.
* 
* 
* @par Related Topics
* None
*/
extern UINT32 AD_DelAtkUserDefined(UINT32 u32AtkType, UINT32 u32ID);

/**
* @defgroup AD_AtkUserDefined_OpenList AD_AtkUserDefined_OpenList
* @ingroup ADF Attack Defense Functions
* @par Prototype
* @code
* UINT32 AD_AtkUserDefined_OpenList(void **ppHandle);
* @endcode 
* 
* @par Description
* This function opens the list of configurations for user defined attack defense.
* 
* @param[in]   []
* @param[out] ppHandle Handle of the list. []
* 
* @retval UINT32 Indicates there are more items [FWCOMMON_ITERATOR_ITEM_EXIST|]
* @retval UINT32 Indicates there are no more items [FWCOMMON_ITERATOR_ITEM_NOT_EXIST|]
* @retval UINT32 Indicates NULL pointer as input parameter while opening list of user defined defense rule 
* [AD_NULL_INPUT_SFE_USER_DEF_OPENLIST|]
* @retval UINT32 Indicates opening list of user defined defense rule failed [AD_OPEN_FAIL_SFE_USER_DEF_OPENLIST|]
* 
* @par Dependency
* ad_inc.h
* 
* 
* @par Note
* \n
* 
* The AD module should be initialized before calling this function.
* 
* 
* @par Related Topics
* None
*/
extern UINT32 AD_AtkUserDefined_OpenList(void **ppHandle);

/**
* @defgroup AD_AtkUserDefined_GetNext AD_AtkUserDefined_GetNext
* @ingroup ADF Attack Defense Functions
* @par Prototype
* @code
* UINT32 AD_AtkUserDefined_GetNext(void * pHandle, AD_USER_DEFINE_PARA_S * pstAtkPara);
* @endcode 
* 
* @par Description
* This function is used to get next item in list of configuration for user defined attack defense
* 
* @param[in] pHandle Handle of the list. []
* @param[out] pstAtkPara Structure for user defined defense parameter. []
* 
* @retval UINT32 Indicates there are more items [FWCOMMON_ITERATOR_ITEM_EXIST|]
* @retval UINT32 Indicates there are no more items [FWCOMMON_ITERATOR_ITEM_NOT_EXIST|]
* @retval UINT32 Indicates NULL pointer as input parameter while getting next user defined defense rule 
* [AD_NULL_INPUT_SFE_USER_DEF_GETNEXT|]
* @retval UINT32 Indicates failed to get next user defined defense rule [AD_GET_FAIL_SFE_USER_DEF_GETNEXT|]
* 
* @par Dependency
* ad_inc.h
* 
* 
* @par Note
* \n
* 
* The AD module should be initialized before calling this function.
* 
* 
* @par Related Topics
* None
*/
extern UINT32 AD_AtkUserDefined_GetNext(void *pHandle, 
    AD_USER_DEFINE_PARA_S * pstAtkPara);


/**
* @defgroup AD_AtkUserDefined_CloseList AD_AtkUserDefined_CloseList
* @ingroup ADF Attack Defense Functions
* @par Prototype
* @code
* UINT32 AD_AtkUserDefined_CloseList(void *pHandle);
* @endcode 
* 
* @par Description
* This function closes the list of configuration for user defined attack defense.
* 
* @param[in] pHandle Handle of the list. []
* @param[out]   []
* 
* @retval UINT32 Indicates no error occurred for iterator [FWCOMMON_ITERATOR_OK|]
* @retval UINT32 Indicates NULL pointer as input parameter while closing list of user defined defense rules 
* [AD_NULL_INPUT_SFE_USER_DEF_CLOSELIST|]
* @retval UINT32 Indicates closing list of user defined defense rule failed [AD_CLOSE_FAIL_SFE_USER_DEF_CLOSELIST|]
* 
* @par Dependency
* ad_inc.h
* 
* 
* @par Note
* \n
* 
* The AD module should be initialized before calling this function.
* 
* 
* @par Related Topics
* None
*/
extern UINT32 AD_AtkUserDefined_CloseList(void *pHandle);

/**
* @defgroup AD_ShowAtkUserDefined AD_ShowAtkUserDefined
* @ingroup ADF Attack Defense Functions
* @par Prototype
* @code
* VOID AD_ShowAtkUserDefined(VOID);
* @endcode 
* 
* @par Description
* This function displays the list of configuration for user defined attack.
* 
* @param[in]   []
* @param[out]   []
* 
* @retval VOID This function does not return any value. [|]
* 
* @par Dependency
* ad_inc.h
* 
* 
* @par Note
* \n
* 
* The AD module should be initialized before calling this function.
* 
* 
* @par Related Topics
* None
*/
extern VOID AD_ShowAtkUserDefined();


/**
* @defgroup AD_RcvBasic AD_RcvBasic
* @ingroup ADF Attack Defense Functions
* @par Prototype
* @code
* UINT32 AD_RcvBasic(VOID *pstMBuf);
* @endcode 
* 
* @par Description
* This function will check all the inbound packets for the 
* basic attacks such as malformed IP spoofing, IP sweep and Port Scan.
* 
* @param[in] pstMBuf Pointer to the packet structure []
* @param[out]   []
* 
* @retval UINT32 Indicating packet should be permitted [IP_PP4_NOT_PROCESSED_BY_INTERMEDIATE|]
* @retval UINT32 Indicating packet should be dropped [IP_PP4_PROCESSED_BY_INTERMEDIATE|]
* 
* @par Dependency
* ad_inc.h
* 
* 
* @par Note
* \n
* 
* The AD module should be initialized before calling this function.
* 
* 
* @par Related Topics
* None
*/
extern UINT32 AD_RcvBasic(VOID *pstMBuf);

/**
* @defgroup AD_SendBasic AD_SendBasic
* @ingroup ADF Attack Defense Functions
* @par Prototype
* @code
* UINT32 AD_SendBasic(VOID *pstMBuf);
* @endcode 
* 
* @par Description
* This function will check all the outbound packets for the 
* basic attacks such as UDP flood, IP spoofing, IP sweep and Port Scan.
* 
* @param[in] pstMBuf Pointer to the packet structure []
* @param[out]   []
* 
* @retval UINT32 Indicating packet should be permitted [IP_PP4_NOT_PROCESSED_BY_INTERMEDIATE|]
* @retval UINT32 Indicating packet should be dropped [IP_PP4_PROCESSED_BY_INTERMEDIATE|]
* 
* @par Dependency
* ad_inc.h
* 
* 
* @par Note
* \n
* 
* The AD module should be initialized before calling this function.
* 
* 
* @par Related Topics
* None
*/
extern UINT32 AD_SendBasic(VOID *pstMBuf);


/**
* @defgroup AD_RcvExtended AD_RcvExtended
* @ingroup ADF Attack Defense Functions
* @par Prototype
* @code
* UINT32 AD_RcvExtended(VOID *pstMBuf);
* @endcode 
* 
* @par Description
* This function will check all the inbound packets for the 
* advanded attacks such as ARP attack.
* 
* @param[in] pstMBuf Pointer to the packet structure []
* @param[out]   []
* 
* @retval UINT32 Indicating packet should be permitted [IP_PP4_NOT_PROCESSED_BY_INTERMEDIATE|]
* @retval UINT32 Indicating packet should be dropped [IP_PP4_PROCESSED_BY_INTERMEDIATE|]
* 
* @par Dependency
* ad_inc.h
* 
* 
* @par Note
* \n
* 
* The AD module should be initialized before calling this function.
* 
* 
* @par Related Topics
* None
*/
extern UINT32 AD_RcvExtended(VOID *pstMBuf);

/**
* @defgroup AD_SendExtended AD_SendExtended
* @ingroup ADF Attack Defense Functions
* @par Prototype
* @code
* UINT32 AD_SendExtended(VOID *pstMBuf);
* @endcode 
* 
* @par Description
* This function will check all the outbound packets for the 
* advanced attacks.
* 
* @param[in] pstMBuf Pointer to the packet structure []
* @param[out]   []
* 
* @retval UINT32 Indicating packet should be permitted [IP_PP4_NOT_PROCESSED_BY_INTERMEDIATE|]
* @retval UINT32 Indicating packet should be dropped [IP_PP4_PROCESSED_BY_INTERMEDIATE|]
* 
* @par Dependency
* ad_inc.h
* 
* 
* @par Note
* \n
* 
* The AD module should be initialized before calling this function.
* 
* 
* @par Related Topics
* None
*/
extern UINT32 AD_SendExtended(VOID *pstMBuf);

#ifdef __cplusplus
}
#endif

#endif  /* end of _AD_API_H_ */

