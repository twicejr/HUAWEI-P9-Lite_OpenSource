/*****************************************************************************
 *
 *
 *                Copyright 2008, Huawei Technologies Co. Ltd.
 *                            ALL RIGHTS RESERVED
 *
 *-----------------------------------------------------------------------------
 *
 *                              sfe_acl_statistics_api.h
 *
 *       Version: DOPRA VISP V2R3C01 Firewall
 *   Module Name: ACL
 *  Date Created: 2010-05-25
 *        Author: Anish K Kurian 72338
 *   Description: API declaration for the statistics
 
 *-----------------------------------------------------------------------------
 *  Modification History
 *  DATE             NAME                   DESCRIPTION
 *  ----------------------------------------------------------------------------
 *  2010-05-25   Anish K Kurian 72338          Create
 *
 *  NOTICE:
 *
 ******************************************************************************/

#ifndef __FWCOMMON_STATISTIC_API_H__
#define __FWCOMMON_STATISTIC_API_H__

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */


/**
* @defgroup tagWLS_Stat WLS_STAT_S
* @ingroup WLS White List Structures
* @par Prototype
* @code
* typedef struct tagWLS_Stat
* {
*     UINT64 u64MatchedPkt;
*     UINT64 u64UnMatchedPkt;
*     UINT64 u64ErrPkt;
* }WLS_STAT_S;
* @endcode 
* 
* @par Description
* This structure consists of whitelist statistics variables
*
* @datastruct u64MatchedPkt Indicates number of matched packets.
* @datastruct u64UnMatchedPkt Indicates number of unmatched packets.
* @datastruct u64ErrPkt Indicates number of error packets received in whitelist module.
*/
typedef struct tagWLS_Stat
{
    UINT64 u64MatchedPkt;
    UINT64 u64UnMatchedPkt;
    UINT64 u64ErrPkt;
}WLS_STAT_S;

/*Blacklist statistic structure*/

/**
* @defgroup tagBLS_Stat BLS_STAT_S
* @ingroup BLS Black List Structures
* @par Prototype
* @code
* typedef struct tagBLS_Stat
* {
*     UINT64 u64BlockedPkt;
*     UINT64 u64PassedPkt;
*     UINT64 u64ErrPkt;
*     UINT64 u64DynamicEntry;
* }BLS_STAT_S;
* @endcode 
* 
* @par Description
* This structure consists of blacklist statistics variables.
*
* @datastruct u64BlockedPkt Indicates number of packets blocked in blacklist module.
* @datastruct u64PassedPkt Indicates number of packets passed in blacklist module.
* @datastruct u64ErrPkt Indicates number of error packets received in blacklist module. 
* @datastruct u64DynamicEntry Indicates number of dynamic entries added to blacklist.
*/
typedef struct tagBLS_Stat
{
    UINT64 u64BlockedPkt;
    UINT64 u64PassedPkt;
    UINT64 u64ErrPkt;    
    UINT64 u64DynamicEntry;
}BLS_STAT_S;

/*Attack statistic structure*/



/**
* @defgroup tagAD_type_stat AD_TYPE_STAT_E
* @ingroup ADE Attack Defense Enums
* @par Prototype
* @code
* typedef enum tagAD_type_stat
* {
*     ATCK_NONE = 0,
*     ATCK_IP_SPOOF_STAT,
*     ATCK_LAND_STAT,
*     ATCK_SMURF_STAT,
*     ATCK_IP_SWEEP_STAT,
*     ATCK_PORTSCAN_STAT,
*     ATCK_ARP_FLOOD_STAT,
*     ATCK_ICMP_FLOOD_STAT,
*     ATCK_UDP_FLOOD_STAT,
*     ATCK_SYN_FLOOD_STAT,
*     ATCK_ARP_MISS_STAT,
*     ATCK_USER_DEFINE_STAT,
*     ATCK_TCPFLAG_STAT,
*     ATCK_WINNUKE_STAT,
*     ATCK_PING_OF_DEATH_STAT,
*     ATCK_FRAGGLE_STAT,
*     ATCK_ICMP_REDIRECT_STAT,
*     ATCK_ICMP_UNREACHABLE_STAT,
*     ATCK_ICMP_TIMESTAMP_STAT,
*     ATCK_RECORD_ROUTE_STAT,
*     ATCK_LOOSE_SOURCE_ROUTE_STAT,
*     ATCK_STRICT_SOURCE_ROUTE_STAT,
*     ATCK_IP_TINY_FRAG_STAT,
*     ATCK_TEARDROP_STAT,
*     ATCK_MAX,
* }AD_TYPE_STAT_E;
* @endcode 
* 
*
* @par Description
* This is the enum which is used for statistics and also which is returned by all the attack defense modules.
* 
* @datastruct ATCK_NONE=0 Indicates no attack
* @datastruct ATCK_IP_SPOOF_STAT Indicates IP spoofing attack or its statistics.
* @datastruct ATCK_LAND_STAT Indicates land attack or its statistics.
* @datastruct ATCK_SMURF_STAT Indicates smurf attack or its statistics.
* @datastruct ATCK_IP_SWEEP_STAT Indicates IP sweep attack or its statistics.
* @datastruct ATCK_PORTSCAN_STAT Indicates Port scan attack or its statistics.
* @datastruct ATCK_ARP_FLOOD_STAT Indicates ARP flood attack or its statistics.
* @datastruct ATCK_ICMP_FLOOD_STAT Indicates ICMP flood attack or its statistics.
* @datastruct ATCK_UDP_FLOOD_STAT Indicates UDP flood attack or its statistics.
* @datastruct ATCK_SYN_FLOOD_STAT Indicates SYN flood attack or its statistics.
* @datastruct ATCK_ARP_MISS_STAT Indicates ARP MISS attack or its statistics.
* @datastruct ATCK_USER_DEFINE_STAT Indicates user defined attack or its statistics.
* @datastruct ATCK_TCPFLAG_STAT Indicates TCPFLAG attack or its statistics.
* @datastruct ATCK_WINNUKE_STAT Indicates Winnuke attack or its statistics.
* @datastruct ATCK_PING_OF_DEATH_STAT Indicates Ping of Death attack or its statistics.
* @datastruct ATCK_FRAGGLE_STAT Indicates Fraggle attack or its statistics.
* @datastruct ATCK_ICMP_REDIRECT_STAT Indicates ICMP Redirect attack or its statistics.
* @datastruct ATCK_ICMP_UNREACHABLE_STAT Indicates ICMP Unreachable attack or its statistics.
* @datastruct ATCK_ICMP_TIMESTAMP_STAT Indicates ICMP Timestamp attack or its statistics.
* @datastruct ATCK_RECORD_ROUTE_STAT Indicates Record route attack or its statistics.
* @datastruct ATCK_LOOSE_SOURCE_ROUTE_STAT Indicates Loose source route attack or its statistics.
* @datastruct ATCK_STRICT_SOURCE_ROUTE_STAT Indicates Strict source route attack or its statistics.
* @datastruct ATCK_IP_TINY_FRAG_STAT Indicates IP tiny fragment attack or its statistics.
* @datastruct ATCK_TEARDROP_STAT Indicates Teardrop attack or its statistics.
* @datastruct ATCK_MAX Indicates the last member of this enum. All attack types should be added before this.
*/ 
typedef enum tagAD_type_stat
{
    ATCK_NONE = 0,
    ATCK_IP_SPOOF_STAT,
    ATCK_LAND_STAT,
    ATCK_SMURF_STAT,
    ATCK_IP_SWEEP_STAT,
    ATCK_PORTSCAN_STAT,
    ATCK_ARP_FLOOD_STAT,
    ATCK_ICMP_FLOOD_STAT,
    ATCK_UDP_FLOOD_STAT,
    ATCK_SYN_FLOOD_STAT,
    ATCK_ARP_MISS_STAT,
    ATCK_USER_DEFINE_STAT,
    ATCK_TCPFLAG_STAT,
    ATCK_WINNUKE_STAT,
    ATCK_PING_OF_DEATH_STAT,
    ATCK_FRAGGLE_STAT,
    ATCK_ICMP_REDIRECT_STAT,
    ATCK_ICMP_UNREACHABLE_STAT,
    ATCK_ICMP_TIMESTAMP_STAT,
    ATCK_RECORD_ROUTE_STAT,
    ATCK_LOOSE_SOURCE_ROUTE_STAT,
    ATCK_STRICT_SOURCE_ROUTE_STAT, 
    ATCK_IP_TINY_FRAG_STAT,
    ATCK_TEARDROP_STAT,
    ATCK_MAX,
}AD_TYPE_STAT_E;

/**
* @defgroup tagAD_Stat_Var AD_STAT_S
* @ingroup ADS Attack Defense Structures
* @par Prototype
* @code
* typedef struct tagAD_Stat_Var
* {
*     UINT64 au64PassedPktBasic[FW_MAX_TYPE];
*     UINT64 au64PassedPktExtended[FW_MAX_TYPE];
*     UINT64 au64ErrPkt[FW_MAX_TYPE];
*     UINT64 au64BlockedPkt[FW_MAX_TYPE][ATCK_MAX];
* }AD_STAT_S;
* @endcode 
* 
* @par Description
* This structure consists of attack module statistics variables
*
* @datastruct au64PassedPktBasic Indicates number of packets passed in basic attack module.
* @datastruct au64PassedPktExtended Indicates number of packets passed in extended attack module.
* @datastruct au64ErrPkt Indicates number of error packets received in attack module. 
* @datastruct au64BlockedPkt Indicates number of packets dropped in attack module.
*/
typedef struct tagAD_Stat_Var
{
    UINT64 au64PassedPktBasic[FW_MAX_TYPE];
    UINT64 au64PassedPktExtended[FW_MAX_TYPE];
    UINT64 au64ErrPkt[FW_MAX_TYPE];
    UINT64 au64BlockedPkt[FW_MAX_TYPE][ATCK_MAX];
}AD_STAT_S;



/**
* @defgroup FWCOMMON_SetFlowStatisticSwitch FWCOMMON_SetFlowStatisticSwitch
* @ingroup FWIF Firewall Interface Functions
* @par Prototype
* @code
* UINT32 FWCOMMON_SetFlowStatisticSwitch (UINT32 u32FlowStatSwitch);
* @endcode 
* 
* @par Description
* This function will enable / disable Flow Statistics updation.
* 
* @param[in] u32FlowStatSwitch Value for setting the Flow statistics switch []
* [1-Enable/0-Disable]
* @param[out]   []
*
* @retval UINT32 Setting Flow Statistics switch successful [FW_OK|] 
*
* @par Dependency
* None
* 
* 
* @par Note
* Flow Statistics is not supported in Control Plane
* \n
* 
* None
* 
* 
* @par Related Topics
* None
*/
extern UINT32 FWCOMMON_SetFlowStatisticSwitch (UINT32 u32FlowStatSwitch);

/**
* @defgroup FWCOMMON_GetFlowStatisticSwitch FWCOMMON_GetFlowStatisticSwitch
* @ingroup FWIF Firewall Interface Functions
* @par Prototype
* @code
* UINT32 FWCOMMON_GetFlowStatisticSwitch(UINT32* pu32FlowStatSwitch);
* @endcode 
* 
* @par Description
* This function will get the current value of Flow Statistics switch.
* 
* @param[in]   []
* @param[out] pu32FlowStatSwitch Address of location to get the value of Flow Statistics switch []
*
* @retval UINT32 Getting Flow Statistics switch successful [FW_OK|] 
*
* @par Dependency
* None
* 
* 
* @par Note
* Flow Statistics is not supported in Control Plane
* \n
* 
* None
* 
* 
* @par Related Topics
* None
*/
extern UINT32 FWCOMMON_GetFlowStatisticSwitch(UINT32* pu32FlowStatSwitch);

/**
* @defgroup FWCOMMON_ShowFlowStatisticSwitch FWCOMMON_ShowFlowStatisticSwitch
* @ingroup FWIF Firewall Interface Functions
* @par Prototype
* @code
* VOID FWCOMMON_ShowFlowStatisticSwitch(VOID);
* @endcode 
* 
* @par Description
* This function will display the current value of Flow Statistics switch.
* 
* @param[in]   []
* @param[out]   []
*
* @retval  [|]
*
* @par Dependency
* None
* 
* 
* @par Note
* Flow Statistics is not supported in Control Plane
* \n
* 
* None
* 
* 
* @par Related Topics
* None
*/
extern VOID FWCOMMON_ShowFlowStatisticSwitch(VOID);

/**
* @defgroup FWCOMMON_ShowFlowStatisticByFlowId FWCOMMON_ShowFlowStatisticByFlowId
* @ingroup FWIF Firewall Interface Functions
* @par Prototype
* @code
* VOID FWCOMMON_ShowFlowStatisticByFlowId(UINT32 u32FlowId);
* @endcode 
* 
* @par Description
* This function will display the Flow Statistics of the given Flow ID.
* 
* @param[in] u32FlowId Flow ID whose statistics is to be displayed[]
* @param[out]   []
*
* @retval  [|]
*
* @par Dependency
* None
* 
* 
* @par Note
* Flow Statistics is not supported in Control Plane
* \n
* 
* None
* 
* 
* @par Related Topics
* None
*/
extern VOID FWCOMMON_ShowFlowStatisticByFlowId(UINT32 u32FlowId);


/**
* @defgroup FWCOMMON_ClearAllFlowStatistic FWCOMMON_ClearAllFlowStatistic
* @ingroup FWIF Firewall Interface Functions
* @par Prototype
* @code
* UINT32 FWCOMMON_ClearAllFlowStatistic(VOID);
* @endcode 
* 
* @par Description
* This function will clear the Flow Statistics of all Flow IDs.
* 
* @param[in]   []
* @param[out]   []
*
* @retval UINT32 Clearing Flow Statistics is successful [FW_OK|]
*
* @par Dependency
* None
* 
* 
* @par Note
* Flow Statistics is not supported in Control Plane
* \n
* 
* None
* 
* 
* @par Related Topics
* None
*/
extern UINT32 FWCOMMON_ClearAllFlowStatistic(VOID);


/**
* @defgroup FWCOMMON_GetMaxFlows FWCOMMON_GetMaxFlows
* @ingroup FWIF Firewall Interface Functions
* @par Prototype
* @code
* UINT32 FWCOMMON_GetMaxFlows(VOID);
* @endcode 
* 
* @par Description
* This function will get the maximum number of flows, used in initializing Flow Statistics.
* 
* @param[in]   []
* @param[out]   []
*
* @retval UINT32 Maximum number of flows [|]
*
* @par Dependency
* None
* 
* 
* @par Note
* Flow Statistics is not supported in Control Plane
* \n
* 
* None
* 
* 
* @par Related Topics
* None
*/
extern UINT32 FWCOMMON_GetMaxFlows(VOID);

/**
* @defgroup FWCOMMON_ShowAllFlowStatistic FWCOMMON_ShowAllFlowStatistic
* @ingroup FWIF Firewall Interface Functions
* @par Prototype
* @code
* VOID FWCOMMON_ShowAllFlowStatistic(VOID);
* @endcode 
* 
* @par Description
* This function will display the Flow Statistics of all the Flow IDs.
* 
* @param[in]   []
* @param[out]   []
*
* @retval  [|]
*
* @par Dependency
* None
* 
* 
* @par Note
* Flow Statistics is not supported in Control Plane
* \n
* 
* None
* 
* 
* @par Related Topics
* None
*/
extern VOID FWCOMMON_ShowAllFlowStatistic(VOID);

/**
* @defgroup SFE_FWCOMMON_SetFWStatisticSwitch SFE_FWCOMMON_SetFWStatisticSwitch
* @ingroup FWIF Firewall Interface Functions
* @par Prototype
* @code
* UINT32 SFE_FWCOMMON_SetFWStatisticSwitch (UINT32 u32FWStatSwitch);
* @endcode 
* 
* @par Description
* This function sets the Firewall statistics switch.
* 
* @param[in] u32FWStatSwitch Value for statistics switch []
* @param[out]   []
*
* @retval UINT32 Setting the statistics switch success  [FW_OK|] 
* @retval UINT32 Invalid value passed for the statistics switch  [FWCOMMON_DEBUG_SFE_SETFWSTATISTICSWITCH_INVALID_SWITCH|] 
* @retval UINT32 The global variable for the statistics switch is not initialized [FWCOMMON_DEBUG_SFE_SETFWSTATISTICSWITCH_NULL_SWITCH|] 
*
* @par Dependency
* Fwcommon_var.h
* 
* 
* @par Note
* \n
* 
*	- The configuration of firewall module should be initialized before 
* calling this function.
* 
* 
* @par Related Topics
* None
*/ 
extern UINT32 FWCOMMON_SetFWStatisticSwitch (UINT32 u32FWStatSwitch);

/**
* @defgroup SFE_FWCOMMON_GetFWStatisticSwitch SFE_FWCOMMON_GetFWStatisticSwitch
* @ingroup FWIF Firewall Interface Functions
* @par Prototype
* @code
* UINT32 SFE_FWCOMMON_GetFWStatisticSwitch(UINT32* pu32FWStatSwitch);
* @endcode 
* 
* @par Description
* This function gets the value of Firewall statistics switch.
* 
* @param[in]   []
* @param[out] pu32FWStatSwitch Pointer to the statistics switch variable []
*
* @retval UINT32 Setting the statistics switch success  [FW_OK|] 
* @retval UINT32 NULL pointer passed as argument  [FWCOMMON_DEBUG_SFE_GETFWSTATISTICSWITCH_NULLPTR|] 
* @retval UINT32 The global variable for the statistics switch is not initialized [FWCOMMON_DEBUG_SFE_GETFWSTATISTICSWITCH_NULL_SWITCH|] 
*
* @par Dependency
* Fwcommon_var.h
* 
* 
* @par Note
* \n
* 
*	- The configuration of firewall module should be initialized before 
* calling this function.
* 
* 
* @par Related Topics
* None
*/ 
extern UINT32 FWCOMMON_GetFWStatisticSwitch(UINT32* pu32FWStatSwitch);

/**
* @defgroup SFE_FWCOMMON_ShowFWStatisticSwitch SFE_FWCOMMON_ShowFWStatisticSwitch
* @ingroup FWIF Firewall Interface Functions
* @par Prototype
* @code
* VOID SFE_FWCOMMON_ShowFWStatisticSwitch(VOID);
* @endcode 
* 
* @par Description
* This function displays the value of Firewall statistics switch.
* 
* @param[in]   []
* @param[out]   []
*
* @retval  [|] 
*
* @par Dependency
* Fwcommon_var.h
* 
* 
* @par Note
* \n
* 
*	- The configuration of firewall module should be initialized before 
* calling this function.
* 
* 
* @par Related Topics
* None
*/ 
extern VOID FWCOMMON_ShowFWStatisticSwitch(VOID);


#ifdef __cplusplus 
}
#endif /* __cplusplus */

#endif /* __ACL_STATISTICS_API_H__ */


