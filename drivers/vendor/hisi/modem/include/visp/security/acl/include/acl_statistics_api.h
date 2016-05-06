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

#ifndef __ACL_STATISTICS_API_H__
#define __ACL_STATISTICS_API_H__

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */


/**
* @defgroup ACL_SetFlowStatisticSwitch ACL_SetFlowStatisticSwitch
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* UINT32 ACL_SetFlowStatisticSwitch (UINT32 u32FlowStatSwitch);
* @endcode 
* 
* @par Description
* This function  enables or disables Flow Statistics update.
* 
* @param[in] u32FlowStatSwitch Value for setting the Flow statistics switch []
* [1-Enable/0-Disable]
* @param[out]   []
*
* @retval UINT32 Setting Flow Statistics switch successful [FW_OK|] 
*
* @par Dependency
* acl_statistics_api.h
* 
* 
* @par Note
* \n
*
* Flow Statistics is not supported in Control Plane.
* 
* 
* @par Related Topics
* None
*/
extern UINT32 ACL_SetFlowStatisticSwitch (UINT32 u32FlowStatSwitch);

/**
* @defgroup ACL_GetFlowStatisticSwitch ACL_GetFlowStatisticSwitch
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* UINT32 ACL_GetFlowStatisticSwitch(UINT32* pu32FlowStatSwitch);
* @endcode 
* 
* @par Description
* This function gets the current value of Flow Statistics switch.
* 
* @param[in]   []
* @param[out] pu32FlowStatSwitch Address of location to get the value of Flow Statistics switch []
*
* @retval UINT32 Getting Flow Statistics switch successful [FW_OK|] 
*
* @par Dependency
* acl_statistics_api.h
* 
* 
* @par Note
* \n
* 
* Flow Statistics is not supported in Control Plane.
* 
* 
* @par Related Topics
* None
*/
extern UINT32 ACL_GetFlowStatisticSwitch(UINT32* pu32FlowStatSwitch);

/**
* @defgroup ACL_ShowFlowStatisticSwitch ACL_ShowFlowStatisticSwitch
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* VOID ACL_ShowFlowStatisticSwitch(VOID);
* @endcode 
* 
* @par Description
* This function displays the current value of Flow Statistics switch.
* 
* @param[in]   []
* @param[out]   []
*
* @retval   [|]
*
* @par Dependency
* acl_statistics_api.h
* 
* 
* @par Note
* \n
* 
* Flow Statistics is not supported in Control Plane.
* 
* 
* @par Related Topics
* None
*/
extern VOID ACL_ShowFlowStatisticSwitch(VOID);

/**
* @defgroup ACL_ShowFlowStatisticByFlowId ACL_ShowFlowStatisticByFlowId
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* VOID ACL_ShowFlowStatisticByFlowId(UINT32 u32FlowId);
* @endcode 
* 
* @par Description
* This function displays the Flow Statistics of the given Flow ID.
* 
* @param[in] u32FlowId Flow ID whose statistics is to be displayed []
* @param[out]   []
*
* @retval   [|]
*
* @par Dependency
* acl_statistics_api.h
* 
* 
* @par Note
* \n
* 
* Flow Statistics is not supported in Control Plane.
* 
* 
* @par Related Topics
* None
*/
extern VOID ACL_ShowFlowStatisticByFlowId(UINT32 u32FlowId);


/**
* @defgroup ACL_ClearAllFlowStatistic ACL_ClearAllFlowStatistic
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* UINT32 ACL_ClearAllFlowStatistic(VOID);
* @endcode 
* 
* @par Description
* This function clears the Flow Statistics of all Flow IDs.
* 
* @param[in]   []
* @param[out]   []
*
* @retval UINT32 Clearing Flow Statistics is successful [FW_OK|]
*
* @par Dependency
* acl_statistics_api.h
* 
* 
* @par Note
* \n
* 
* Flow Statistics is not supported in Control Plane.
* 
* 
* @par Related Topics
* None
*/
extern UINT32 ACL_ClearAllFlowStatistic(VOID);


/**
* @defgroup ACL_GetMaxFlows ACL_GetMaxFlows
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* UINT32 ACL_GetMaxFlows(VOID);
* @endcode 
* 
* @par Description
* This function gets the maximum number of flows used to initialize flow statistics.
* 
* @param[in]   []
* @param[out]   []
*
* @retval UINT32 Maximum number of flows [|]
*
* @par Dependency
* acl_statistics_api.h
* 
* 
* @par Note
* \n
* 
* Flow Statistics is not supported in Control Plane.
* 
* 
* @par Related Topics
* None
*/

extern UINT32 ACL_GetMaxFlows(VOID);

/**
* @defgroup ACL_ShowAllFlowStatistic ACL_ShowAllFlowStatistic
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* VOID ACL_ShowAllFlowStatistic(VOID);
* @endcode 
* 
* @par Description
* This function displays the Flow Statistics of all the Flow IDs.
* 
* @param[in]   []
* @param[out]   []
*
* @retval   [|]
*
* @par Dependency
* acl_statistics_api.h
* 
* 
* @par Note
* \n
* 
* Flow Statistics is not supported in Control Plane.
* 
* 
* @par Related Topics
* None
*/
extern VOID ACL_ShowAllFlowStatistic(VOID);

/**
* @defgroup ACLFW_SetVCPUStatisticSwitch ACLFW_SetVCPUStatisticSwitch
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* UINT32 ACLFW_SetVCPUStatisticSwitch(UINT32 u32FWStatSwitch);
* @endcode 
* 
* @par Description
* This function sets the ACL VCPU statistics switch.
* 
* @param[in] u32FWStatSwitch Value for statistics switch []
* @param[out]   []
*
* @retval UINT32 Setting the statistics switch success  [FW_OK|] 
* @retval UINT32 Invalid value passed for the statistics switch  [FWCOMMON_DEBUG_SFE_SETFWSTATISTICSWITCH_INVALID_SWITCH|] 
* @retval UINT32 The global variable for the statistics switch is not initialized [FWCOMMON_DEBUG_SFE_SETFWSTATISTICSWITCH_NULL_SWITCH|] 
*
* @par Dependency
* acl_statistics_api.h
* 
* 
* @par Note
* \n
* 
* The configuration of ACL should be initialized before calling this function.
* 
* 
* @par Related Topics
* None
*/ 
extern UINT32 ACLFW_SetVCPUStatisticSwitch(UINT32 u32FWStatSwitch);

/**
* @defgroup ACLFW_GetVCPUStatisticSwitch ACLFW_GetVCPUStatisticSwitch
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* UINT32 ACLFW_GetVCPUStatisticSwitch(UINT32* pu32FWStatSwitch);
* @endcode 
* 
* @par Description
* This function gets the value of ACL VCPU statistics switch.
* 
* @param[in]   []
* @param[out] pu32FWStatSwitch Pointer to the statistics switch variable []
*
* @retval UINT32 Setting the statistics switch success  [FW_OK|] 
* @retval UINT32 NULL pointer passed as argument  [FWCOMMON_DEBUG_SFE_GETFWSTATISTICSWITCH_NULLPTR|] 
* @retval UINT32 The global variable for the statistics switch is not initialized [FWCOMMON_DEBUG_SFE_GETFWSTATISTICSWITCH_NULL_SWITCH|] 
*
* @par Dependency
* acl_statistics_api.h
* 
* 
* @par Note
* \n
* 
* The configuration of ACL module should be initialized before calling this function.
* 
* 
* @par Related Topics
* None
*/ 
extern UINT32 ACLFW_GetVCPUStatisticSwitch(UINT32* pu32FWStatSwitch);

/**
* @defgroup ACLFW_ShowVCPUStatisticSwitch ACLFW_ShowVCPUStatisticSwitch
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* VOID ACLFW_ShowVCPUStatisticSwitch(VOID);
* @endcode 
* 
* @par Description
* This function displays the value of ACL statistics switch.
* 
* @param[in]   []
* @param[out]   []
*
* @retval   [|] 
*
* @par Dependency
* acl_statistics_api.h
* 
* 
* @par Note
* \n
* 
* The configuration of ACL module should be initialized before calling this function.
* 
* 
* @par Related Topics
* None
*/ 
extern VOID ACLFW_ShowVCPUStatisticSwitch(VOID);



#ifdef __cplusplus 
}
#endif /* __cplusplus */

#endif /* __ACL_STATISTICS_API_H__ */


