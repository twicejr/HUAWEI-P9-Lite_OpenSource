/***********************************************************************************
 *
 *              Copyright 2006, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                              Sfe_fw_acl_cbb_api.h
 *
 *  Project Code: VISP1.6
 *   Module Name: ACL4
 *  Date Created: 2006-12-31
 *        Author: lijing 52889
 *   Description: ACL CBB对外提供的数据结构定义和函数声明
 *   Version:      1
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2006-12-31      lijing 52889    Create
 *  2008-03-31      mafeng 59090    Modified(修改文件名acl_api.h为acl_cbb_api.h)
 *  2008-10-24      liangjicheng    C02NEWR-ACL   Add IcmpCode IcmpType
 *  2008-11-29      qinyun          Add for BC3D00792
 *                                  DR.129 ACL需提供获取系统配置的规则组信息的接口
 *  2010-02-15   eswar/72335        Changed API description as per functionality for API
                                    ACL_ClearGroup
 ***********************************************************************************/
#ifndef _FW_ACL_CBB_API_H_
#define _FW_ACL_CBB_API_H_

#ifdef  __cplusplus
extern "C" 
{
#endif

/**
* @defgroup accssf ACL Functions
* This sections contains the ACL functions
*/


/**********************************************************
*   用户API声明
***********************************************************/
/* 规则类型配置函数 */

/**
* @defgroup ACL_RegisterUserType ACL_RegisterUserType
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_RegisterUserType(ACL_TYPE_REGISTER_INFO_S *pstRegisterInfo);
* @endcode 
* 
* @par Description
* This function registers the user defined ACL types.
* 
* @param[in] pstRegisterInfo Pointer to the structure containing the basic information of user defined custom types. []
* @param[out]   []
*
* @retval ULONG On success [Help_ACL_OK|]
* @retval ULONG Input argument is NULL [Help_ACL_NULL_POINTER|]
* @retval ULONG Indicates ACL is not initialized successfully [Help_ACL_NOT_INIT|]
* @retval ULONG Indicates invalid rule type number [Help_ACL_TYPE_ID_ERROR|]
* @retval ULONG Indicates that the rule type ID is already in use [Help_ACL_TYPE_ID_EXIST|]
* @retval ULONG Indicates rule type number is out of range [Help_ACL_GROUP_RANGE_ERROR|]
* @retval ULONG Indicates that the rule content size is zero [Help_ACL_CONTENT_SIZEZERO|] 
* @retval ULONG Indicates function pointer is NULL [Help_ACL_FUNC_NULL|]
* @retval ULONG Indicates error in memory allocation for ACL type [Help_ACL_Type_MallocError|]
* @retval ULONG Indicates failed to allocate memory for the rule set [Help_ACL_Group_MallocError|]
* 
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
*	- ACL_UnRegisterUserType
*	- ACL_ManageUserRule
*
*/ 
extern ULONG ACL_RegisterUserType(ACL_TYPE_REGISTER_INFO_S *pstRegisterInfo);




/**
* @defgroup ACL_RegisterExtGroupType ACL_RegisterExtGroupType
* @ingroup access ACL Functions
* @par Prototype
* @code
* ULONG ACL_RegisterExtGroupType (ULONG ulTypeID, ULONG ulLowNo, ULONG ulUpNo);
* @endcode 
* 
* @par Description
* This function registers extended advance ALC group.
* 
* @param[in] ulTypeID ACL type ID. It must be ACL_ADVANCE_RULE_TYPE.[]
*                 ulLowNo ACL type ID lower range. []
*                 ulUpNo ACL type ID upper range. []
* @param[out]   []
*
* @retval ULONG On success [Help_ACL_OK|]
* @par Dependency
* fw_acl_cbb_api.h
* 
*
* @retval On success [Help_ACL_OK|]
* @retval Type ID is not ACL_ADVANCE_RULE_TYPE [Help_ACL_TYPE_ID_ERROR|]
* @retval Extended advance is already registered [Help_ACL_ERR_EXT_ADV_ALREADY_REGISTERED|]
* @retval Group range is not proper [Help_ACL_GROUP_RANGE_ERROR|]
* @retval Malloc error while initialization [Help_ACL_TYPE_ADV_MallocErr|]
* @retval failed to extended hash table for extended advance group [Help_ACL_STAT_ERR_ACL_INIT_SWITCH_STAT_HASHTABLE|]
*
* @par Note
* 1. ACL_RegisterExtGroupType must be called immediately after ACL_Init before adding any group.It must be called only once.
* 2. User type 16 should not be used if ACL_RegisterExtGroupType is being used.
* 3. ACL_RegisterExtGroupType only supports configuration & display for extended advance group. 
* 4. Packet classification is not handled for extended advance group.
* 
* None
* 
*/ 
extern ULONG ACL_RegisterExtGroupType (ULONG ulTypeID, ULONG ulLowNo, ULONG ulUpNo);

/**
* @defgroup ACL_UnRegisterUserType ACL_UnRegisterUserType
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_UnRegisterUserType(ULONG ulTypeID);
* @endcode 
* 
* @par Description
* This function is used to unregister the user defined rule types.
* 
* @param[in] ulTypeID User defined rule type ID [1-16]
* @param[out]   []
* 
* @retval ULONG On success [Help_ACL_OK|]
* @retval ULONG Indicates that the ACL rule type does not exist [Help_ACL_TYPE_NOT_EXIST|]
* @retval ULONG Indicates error in ACL rule type ID [Help_ACL_TYPE_ID_ERROR|]
* 
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
*	- ACL_RegisterUserType
*	- ACL_ManageUserRule
*
*/ 
extern ULONG ACL_UnRegisterUserType(ULONG ulTypeID);


/**
* @defgroup ACL_ModifyGroupNumRange ACL_ModifyGroupNumRange
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_ModifyGroupNumRange (ULONG ulTypeID, ULONG ulLowNo, ULONG ulUpNo);
* @endcode 
* 
* @par Description
* This function modifies the range of an ACL group by setting the upper and lower limits.
* 
* @param[in] ulTypeID The ACL rule type ID. [1-16]
* @param[in] ulLowNo The lower limit of the range. []
* @param[in] ulUpNo The upper limit of the range. []
* @param[out]   []
* 
* @retval ULONG On success [Help_ACL_OK|]
* @retval ULONG Indicates rule type does not exist [Help_ACL_TYPE_NOT_EXIST|]
* @retval ULONG Indicates error in ACL rule type ID [Help_ACL_TYPE_ID_ERROR|]
* @retval ULONG Indicates the range cannot be changed [Help_ACL_GROUP_RANGE_CANOT_CHANGE|]
* @retval ULONG Indicates error in the ACL group range that has been set [Help_ACL_GROUP_RANGE_ERROR|]
* @retval ULONG Indicates failed to allocate memory for the rule set [Help_ACL_Group_MallocError|]
* 
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* It is advisable not to modify the group range dynamically.
* 
* 
* @par Related Topics
* None
*/ 
extern ULONG ACL_ModifyGroupNumRange (ULONG ulTypeID, ULONG ulLowNo, ULONG ulUpNo);


/* 规则组配置函数 */
/**
* @defgroup ACL_AddGroup ACL_AddGroup
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_AddGroup(ULONG ulGroupNum, ULONG ulMatchOrder);
* @endcode 
* 
* @par Description
* This function adds an ACL rule group. Matchorder parameter is used to add the rule. If matchorder is default or 
* configured, it adds the rule as per user's configuration. In auto matchorder, it adds the rule in sorted order of 
* rule's parameters. Auto matchorder is not applicable for MAC based rules.
* 
* @param[in] ulGroupNum ACL Group number. The value for this parameter should lie in between 
* the range for the group numbers provided as the second and third fields of the structure ACL_TYPE_S. []
* @param[in] ulMatchOrder The matching method. It can be one of the following:
*	- Default(0)
*	- Configuration(1)
*	- Auto(2) []
* @param[out]   []
* 
* @retval ULONG On success [Help_ACL_OK|]
* @retval ULONG Indicates invalid rule match order [Help_ACL_MatchOrderErr|]
* @retval ULONG Indicates the group number and the corresponding order does not match [Help_ACL_MatchOrderErr_Snd|]
* @retval ULONG Indicates error in ACL group number [Help_ACL_GroupNumError|]
* @retval ULONG Indicates rule group already exists [Help_ACL_Group_Exist|]
* @retval ULONG Indicates memory operation failure [Help_ACL_MallocError|]
* @retval ULONG Hash search function failed to search the group stat [Help_ACL_ERR_STAT_ADD_GROUP_HASH_SEARCH|]
* @retval ULONG Hash add function failed to add the group stat [Help_ACL_ERR_STAT_ADD_GROUP_HASH_INSERT|]
* 
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
*	- ACL_NoGroup
*	- ACL_ManageGroup
*/ 
extern ULONG ACL_AddGroup(ULONG ulGroupNum, ULONG ulMatchOrder);

/**
* @defgroup ACL_NoGroup ACL_NoGroup
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_NoGroup(BOOL_T bIsAll, ULONG ulGroupNum);
* @endcode 
* 
* @par Description
* This function removes a specific or all the ACL groups. If bISAll is true, 
* then it deletes all the groups. If bISAll is false, then it deletes the
* group with the group number given by ulGroupNum.
* 
* @param[in] bIsAll If this is set to true, then all the groups will be deleted. 
* If it is set to false, then the rule group number indicated by ulGroupNum is deleted. []
* @param[in] ulGroupNum ACL group number that needs to be deleted. The value for this parameter should lie in between 
* the range for the group numbers provided as the second and third fields of the structure ACL_TYPE_S. []
* @param[out]   []
* 
* @retval ULONG On success [Help_ACL_OK|]
* @retval ULONG Indicates the ACL group number does not exist [Help_ACLGroup_Not_Exist|]
* @retval ULONG Indicates error in group number [Help_ACL_GroupNumError|]
* 
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
*	- ACL_ManageGroup
*	- ACL_AddGroup
*
*/ 
extern ULONG ACL_NoGroup(BOOL_T bIsAll, ULONG ulGroupNum);

/**
* @defgroup ACL_NumGroupSetOrder ACL_NumGroupSetOrder
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_NumGroupSetOrder (ULONG ulGroupNum,  ULONG ulMatchOrder);
* @endcode 
* 
* @par Description
* This function sets the rule matching order of the given ACL group.
* 
* @param[in] ulGroupNum ACL group number. The value for this parameter should lie in between 
* the range for the group numbers provided as the second and third fields of the structure ACL_TYPE_S. []
* @param[in] ulMatchOrder Rule match order to be set. It can be one of the following:
*	- Default(0)
*	- Configuration(1)
*	- Auto(2) []
* @param[out]   []
* 
* @retval ULONG On success [Help_ACL_OK|]
* @retval ULONG Indicates error in match order input [Help_ACL_MatchOrderErr|]
* @retval ULONG Indicates the type ID of the ACL group and the 
* input match order does not match [Help_ACL_MatchOrderErr_Snd|]
* @retval ULONG Indicates the ACL group number does not exist [Help_ACLGroup_Not_Exist|]
* @retval ULONG Indicates match order cannot be changed since the group already has rules [Help_ACL_NotChangeMatchOrder|]
* @retval ULONG Indicates error in input group number [Help_ACL_GroupNumError|]
* 
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
*	- ACL_NumGroupSetDesc
*	- ACL_NumGroupSetStep
*
*/ 
extern ULONG ACL_NumGroupSetOrder (ULONG ulGroupNum,  ULONG ulMatchOrder);

/**
* @defgroup ACL_NumGroupSetDesc ACL_NumGroupSetDesc
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_NumGroupSetDesc(BOOL_T bIsNo, ULONG ulGroupNum, CHAR *szDescription);
* @endcode 
* 
* @par Description
* This function sets or modifies the description of the given ACL group.
* 
* @param[in] bIsNo This parameter indicates whether to clear or reset the ACL 
* group description. It can have the following values:
*	- Non-Zero : This will clear the description of the group, if available. 
*	- Zero : This will clear the description, if present and then set the group 
* description as given in the parameter szDescription. []
* @param[in] ulGroupNum ACL rule group number.  The value for this parameter should lie in between 
* the range for the group numbers provided as the second and third fields of the structure ACL_TYPE_S. []
* @param[in] szDescription The description to be added. []
* @param[out]   []
* 
* @retval ULONG On success [Help_ACL_OK|]
* @retval ULONG Indicates rule group does not exist [Help_ACLGroup_Not_Exist|]
* @retval ULONG Indicates error in group number [Help_ACL_GroupNumError|]
* @retval ULONG Indicates description is NULL [Help_ACL_DESCRIPTION_NULL|]
* @retval ULONG Indicates description is more than 128 bytes in length [Help_ACL_DescriptionTooLong|]
* @retval ULONG Indicates memory allocation failure [Help_ACL_MallocError|]
*  
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
*	- ACL_NumGroupSetOrder
*	- ACL_NumGroupSetStep
*
*/ 
extern ULONG ACL_NumGroupSetDesc(BOOL_T bIsNo, ULONG ulGroupNum, CHAR *szDescription);

/**
* @defgroup ACL_NumGroupSetStep ACL_NumGroupSetStep
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_NumGroupSetStep (ULONG ulGroupNum, ULONG ulStep, BOOL_T bIsNo);
* @endcode 
* 
* @par Description
* This function sets or modifies the step value of the rule in ACL group settings 
* and rebuilds the rules by incrementing ulStep value.
* 
* @param[in] ulGroupNum ACL rule group number. The value for this parameter should lie in between 
* the range for the group numbers provided as the second and third fields of the structure ACL_TYPE_S. []
* @param[in] ulStep The step that should be set. [1-20]
* @param[in] bIsNo This parameter indicates whether to reset the group settings 
* to default or to modify it with the value given in the parameter ulStep. It 
* can have the following values:
*	- Non-Zero : This will reset the setting to ACL_DEFAULT_STEP.
*	- Zero : This will modify the setting to the value given in ulStep. []
* @param[out]   []
* 
* @retval ULONG On success [Help_ACL_OK|]
* @retval ULONG Indicates rule group does not exist [Help_ACLGroup_Not_Exist|]
* @retval ULONG Indicates error in step-size value [Help_ACL_ERRSTEP|]
* @retval ULONG Indicates error in group number [Help_ACL_GroupNumError|]
* 
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
*	- ACL_NumGroupSetOrder
*	- ACL_NumGroupSetDesc
*
*/ 
extern ULONG ACL_NumGroupSetStep (ULONG ulGroupNum, ULONG ulStep, BOOL_T bIsNo);


/**
* @defgroup ACL_ManageGroup ACL_ManageGroup
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_ManageGroup(BOOL_T bIsNo, 
*                       ULONG ulGroupNum, 
*                       ULONG ulSetOrder, 
*                       ULONG ulMatchOrder, 
*                       ULONG ulSetStep, 
*                       ULONG ulStep, 
*                       ULONG ulSetDes, 
*                       CHAR *pDescription);
* @endcode 
* 
* @par Description
* This function is used to add, delete or modify an ACL group. Specific combinations 
* of the parameters and their functions are as follows:
*	- bIsNo==1,ulGroupNum==0 Delete all the groups
*	- bIsNo==1,ulGroupNum!=0 Delete a specific group
*	- bIsNo==0,ulGroupNum!=0 Add a new group or modify an existing group
*	- ulSetOrder=0 Do not set match order, ulSetOrder=1 Set the match order
*	- ulSetStep=0 Do not set step, ulSetStep=1 Set step, ulSetStep=2 Restore default values
*	- ulSetDes=0 Do not set description, ulSetDes=1 Set description
* 
* @param[in] bIsNo This parameter is set to delete all the groups or a particular 
* group present. []
* @param[in] ulGroupNum The ACL group number. The value for this parameter should lie in between 
* the range for the group numbers provided as the second and third fields of the structure ACL_TYPE_S. []
* @param[in] ulSetOrder Indicates whether to set the order of matches. It can take the following values: 
*	- 1 - For setting an order
*	- 2 - For using the default order []
* @param[in] ulMatchOrder Rule match order to be set. It can be one of the following:
*	- Default(0)
*	- Configuration(1)
*	- Auto(2) []
* @param[in] ulSetStep Indicates whether to set the step size or restore defaults. It can take the 
* following values: 
*	- 1 - For setting step size
*	- 2 - For using the default step size []
* @param[in] ulStep The step size. [1-20]
* @param[in] ulSetDes Indicates whether to set the description of information or 
* restore defaults. It can take the following values: 
*	- 1 - For setting the description
*	- 2 - For using the default description []
* @param[in] pDescription The description of this particular group. []
* @param[out]   []
* 
* @retval ULONG On success [Help_ACL_OK|]
* @retval ULONG Indicates error in group number [Help_ACL_GroupNumError|]
* @retval ULONG Indicates group number is not present [Help_ACLGroup_Not_Exist|]
* @retval ULONG Indicates error in group number [Help_ACL_GroupNumError|]
* @retval ULONG Indicates error in rule match order [Help_ACL_MatchOrderErr|]
* @retval ULONG Indicates the Type ID of the ACL group and the 
* input match order does not match [Help_ACL_MatchOrderErr_Snd|]
* @retval ULONG Indicates memory allocation failure [Help_ACL_Group_MallocError|]
* @retval ULONG Indicates Hash search function failed to search the group stat[Help_ACL_ERR_STAT_ADD_GROUP_HASH_SEARCH|]
* @retval ULONG Hash add function failed to add the group stat[Help_ACL_ERR_STAT_ADD_GROUP_HASH_INSERT|]
* @retval ULONG Indicates match order cannot be set as DEFAULT order [Help_ACL_NotChangeMatchOrder|]
* @retval ULONG Indicates error in step-size value [Help_ACL_ERRSTEP|]
* @retval ULONG Indicates description is NULL [Help_ACL_DESCRIPTION_NULL|]
* @retval ULONG Indicates description is more than 128 bytes in length [Help_ACL_DescriptionTooLong|]
* @retval ULONG Indicates memory operation failure [Help_ACL_MallocError|]
*
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
*	- ACL_NoGroup
*	- ACL_AddGroup
*
*/ 
extern ULONG ACL_ManageGroup(BOOL_T bIsNo, ULONG ulGroupNum, ULONG ulSetOrder, ULONG ulMatchOrder, 
                              ULONG ulSetStep, ULONG ulStep, ULONG ulSetDes, CHAR *pDescription);


/**
* @defgroup ACL_CreateDelACLGroup ACL_CreateDelACLGroup
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_CreateDelACLGroup(ULONG ulOperType, ULONG ulGroupNumber, ULONG ulMatchOrder);
* @endcode 
* 
* @par Description
* This function creates or deletes an ACL group.
* 
* @param[in] ulOperType It is the type of operation. [0-Delete/1-Add]
* @param[in] ulGroupNumber ACL rule group number. The value for this parameter should lie in between 
* the range for the group numbers provided as the second and third fields of the structure ACL_TYPE_S. []
* @param[in] ulMatchOrder ACL match order. It can be one of the following:
*	- Default(0)
*	- Configuration(1)
*	- Auto(2) []
* @param[out]   []
* 
* @retval ULONG On success [Help_ACL_OK|]
* @retval ULONG Indicates error in operation type [Help_ACL_NotSupportOperType|]
* @retval ULONG Indicates error in group number [Help_ACL_GroupNumError|]
* @retval ULONG Indicates group number is not present [Help_ACLGroup_Not_Exist|]
* @retval ULONG Indicates error in group number [Help_ACL_GroupNumError|]
* @retval ULONG Indicates error in rule match order [Help_ACL_MatchOrderErr|]
* @retval ULONG Indicates the Type ID of the ACL group and the 
* input match order does not match [Help_ACL_MatchOrderErr_Snd|]
* @retval ULONG Indicates memory allocation failure [Help_ACL_Group_MallocError|]
* @retval ULONG Indicates Hash search function failed to search the group stat 
* [Help_ACL_ERR_STAT_ADD_GROUP_HASH_SEARCH|]
* @retval ULONG Hash add function failed to add the group stat[Help_ACL_ERR_STAT_ADD_GROUP_HASH_INSERT|]
* @retval ULONG Indicates match order cannot be set as DEFAULT order [Help_ACL_NotChangeMatchOrder|]
* @retval ULONG Indicates error in step-size value [Help_ACL_ERRSTEP|]
* @retval ULONG Indicates description is NULL [Help_ACL_DESCRIPTION_NULL|]
* @retval ULONG Indicates description is more than 128 bytes in length [Help_ACL_DescriptionTooLong|]
* @retval ULONG Indicates memory operation failure [Help_ACL_MallocError|]
* 
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
*	- ACL_NoGroup
*	- ACL_AddGroup
*
*/ 
extern ULONG ACL_CreateDelACLGroup(ULONG ulOperType, ULONG ulGroupNumber, ULONG ulMatchOrder);


/* Rule Configuration Functions */

extern ULONG ACL_DeleteNode(ULONG ulGroupNum, ULONG ulRuleIndex);

/**
* @defgroup ACL_ManageBasicRule ACL_ManageBasicRule
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_ManageBasicRule(ULONG ulGroupNum, 
*                           ULONG ulRuleIndex, 
*                           ACL_BASIC_RULEINFO_S *pstRuleInfo);
* @endcode 
* 
* @par Description
* This function is used to create a new rule or update an existing rule.
* 
* @param[in] ulGroupNum The ACL group number. The value for this parameter should lie in between 
* the range for the group numbers provided as the second and third fields of the structure ACL_TYPE_S []
* @param[in] ulRuleIndex The rule number [0-0XFFFFFFFF]
* @param[in] pstRuleInfo Pointer to the structure ACL_BASIC_RULEINFO_S which stores 
* the basic ACL rule information []
* @param[out]   []
* 
* @retval ULONG On success [Help_ACL_OK|]
* @retval ULONG RuleInfo argument is NULL or Internal Memory operation fails [Help_ACL_ERR|]
* @retval ULONG Indicates NULL argument [ACLFW_ERR_NULL|]
* @retval ULONG Indicates failure to open ACL interface configuration [ACLFW_ERR_SFE_ACLFW_SECPOLICY_OPEN_INIT|]
* @retval ULONG Indicates end table error [ACLFW_ERR_END_TABLE|]
* @retval ULONG Indicates error in ACL group number [Help_ACL_GroupNumError|]
* @retval ULONG Indicates the ACL group number does not exists [Help_ACLGroup_Not_Exist|]
* @retval ULONG Indicates invalid rule type number [Help_ACL_TYPE_ID_ERROR|]
* @retval ULONG Indicates number of ACL Rule exceeds limit [Help_ACL_AccessListTooMuchRulesNormal|]
* @retval ULONG Indicates number of ACL Rules per group exceeds limit [Help_ACL_AccessInGroup|]
* @retval ULONG Indicates error in step-size value [Help_ACL_ERRSTEP|]
* @retval ULONG Indicates error in VRF operation type [Help_ACL_ActionError|]
* 
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* If the rule index is 0XFFFFFFFF, the match order is considered as auto mode.
* 
* 
* @par Related Topics
*	- ACL_DeleteNode
*	- ACL_ManageAdvanceRule
*	- ACL_ManageIfBasedRule
*	- ACL_ManageExtMacRule
*	- ACL_ManageUserRule
*
*/ 
extern ULONG ACL_ManageBasicRule(ULONG ulGroupNum, ULONG ulRuleIndex, ACL_BASIC_RULEINFO_S *pstRuleInfo);

/**
* @defgroup ACL_ManageAdvanceRule ACL_ManageAdvanceRule
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_ManageAdvanceRule(ULONG ulGroupNum, 
*                             ULONG ulRuleIndex, 
*                             ACL_ADV_RULEINFO_S *pstRuleInfo);
* @endcode 
* 
* @par Description
* This function is used to manage the advanced ACL rules. It can create a new 
* rule or modify an existing rule.
* 
* @param[in] ulGroupNum The ACL group number. The value for this parameter should lie in between 
* the range for the group numbers provided as the second and third fields of the structure ACL_TYPE_S []
* @param[in] ulRuleIndex The rule number [0-0XFFFFFFFF]
* @param[in] pstRuleInfo Pointer to the structure ACL_ADV_RULEINFO_S which stores 
* the advanced ACL rule information []
* @param[out]   []
* 
* @retval ULONG On success [Help_ACL_OK|]
* @retval ULONG Indicates error in input arguments [Help_ACL_ERR|]
* @retval ULONG Indicates error in group number [Help_ACL_GroupNumError|]
* @retval ULONG Indicates group number is not present [Help_ACLGroup_Not_Exist|]
* @retval ULONG Indicates invalid rule type number [Help_ACL_TYPE_ID_ERROR|]
* @retval ULONG Indicates number of ACL Rule exceeds limit [Help_ACL_AccessListTooMuchRulesNormal|]
* @retval ULONG Indicates number of ACL Rules per group exceeds limit [Help_ACL_AccessInGroup|]
* @retval ULONG Indicates error in step-size value [Help_ACL_ERRSTEP|]
* @retval ULONG Indicates rule number does not exist [Help_ACL_Subitem_Number_Not_Exist|]
* @retval ULONG Indicates error in providing new rule Id [Help_ACL_CANOT_GIVEID|]            
* @retval ULONG Indicates error in number of rules in a group [Help_ACL_TooMuchRulesINGroup|] 
* @retval ULONG Indicates error in ACL rule number [Help_ACL_SubIDTooLarge|]
* @retval ULONG Indicates rule already exist [Help_ACL_RULES_EXIST|]
* @retval ULONG Indicates invalid action value [Help_ACL_ActionError|]
* @retval ULONG Indicates invalid port number [Help_ACL_CannotSetPortNum|]
* @retval ULONG Indicates invalid ICMP port number [Help_ACL_ERR_ICMPTYPE|]
* @retval ULONG Indicates invalid precedence value specified [Help_ACL_PreError|]
* @retval ULONG Indicates invalid TOS value specified [Help_ACL_TosError|]
* @retval ULONG Indicates invalid DSCP value specified [Help_ACL_DscpError|]
* 
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* If the rule index is 0XFFFFFFFF, the match order is considered as auto mode.
* 
* 
* @par Related Topics
*	- ACL_ManageBasicRule
*	- ACL_DeleteNode
*	- ACL_ManageIfBasedRule
*	- ACL_ManageExtMacRule
*	- ACL_ManageUserRule
* 
*/ 
extern ULONG ACL_ManageAdvanceRule(ULONG ulGroupNum, ULONG ulRuleIndex, ACL_ADV_RULEINFO_S *pstRuleInfo);

/**
* @defgroup ACL_ManageIfBasedRule ACL_ManageIfBasedRule
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_ManageIfBasedRule(ULONG ulGroupNum, 
*                             ULONG ulRuleIndex, 
*                             ACL_IFBASED_RULEINFO_S *pstRuleInfo);
* @endcode 
* 
* @par Description
* This function manages the interface based rules. It can add a new rule or 
* modify the existing one.
* 
* @param[in] ulGroupNum The ACL group number. The value for this parameter should lie in between 
* the range for the group numbers provided as the second and third fields of the structure ACL_TYPE_S []
* @param[in] ulRuleIndex The rule number [0-0XFFFFFFFF]
* @param[in] pstRuleInfo Pointer to the structure ACL_IFBASED_RULEINFO_S which stores 
* the interface based ACL rule information []
* @param[out]   []
* 
* @retval ULONG On success [Help_ACL_OK|]
* @retval ULONG Indicates error in input arguments or memory operation error [Help_ACL_ERR|]
* @retval ULONG Indicates error in group number [Help_ACL_GroupNumError|]
* @retval ULONG Indicates group number is not present [Help_ACLGroup_Not_Exist|]
* @retval ULONG Indicates invalid rule type number [Help_ACL_TYPE_ID_ERROR|]
* @retval ULONG Indicates number of ACL Rule exceeds limit [Help_ACL_AccessListTooMuchRulesNormal|]
* @retval ULONG Indicates number of ACL Rules per group exceeds limit [Help_ACL_AccessInGroup|]
* @retval ULONG Indicates error in step-size value [Help_ACL_ERRSTEP|]
* @retval ULONG Indicates rule number does not exist [Help_ACL_Subitem_Number_Not_Exist|]
* @retval ULONG Indicates error in providing new rule Id [Help_ACL_CANOT_GIVEID|]            
* @retval ULONG Indicates error in number of rules in a group [Help_ACL_TooMuchRulesINGroup|] 
* @retval ULONG Indicates error in ACL rule number [Help_ACL_SubIDTooLarge|]
* @retval ULONG Indicates error in modifying rule [Help_ACL_NOTMODIFY|]
* @retval ULONG Indicates rule already exist [Help_ACL_RULES_EXIST|]
* 
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* If the rule index is 0XFFFFFFFF, the match order is considered as auto mode.
* 
* 
* @par Related Topics
*	- ACL_ManageBasicRule
*	- ACL_ManageAdvanceRule
*	- ACL_DeleteNode
*	- ACL_ManageExtMacRule
*	- ACL_ManageUserRule
*
*/ 
extern ULONG ACL_ManageIfBasedRule(ULONG ulGroupNum, ULONG ulRuleIndex, ACL_IFBASED_RULEINFO_S *pstRuleInfo);

/**
* @defgroup ACL_ManageExtMacRule ACL_ManageExtMacRule
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_ManageExtMacRule(ULONG ulGroupNum, 
*                            ULONG ulRuleIndex, 
*                            ACL_EXTMAC_RULEINFO_S *pstRuleInfo);
* @endcode 
* 
* @par Description
* This function manages the MAC based rules. It can add a new rule or 
* modify the existing one.
* 
* @param[in] ulGroupNum The ACL group number. The value for this parameter should lie in between 
* the range for the group numbers provided as the second and third fields of the structure ACL_TYPE_S []
* @param[in] ulRuleIndex The rule number [0-0XFFFFFFFF]
* @param[in] pstRuleInfo Pointer to the structure ACL_EXTMAC_RULEINFO_S which stores 
* the MAC based ACL rule information []
* @param[out]   []
* 
* @retval ULONG On success [Help_ACL_OK|]
* @retval ULONG Indicates error in input arguments / memory operation error [Help_ACL_ERR|]
* @retval ULONG Indicates error in group number [Help_ACL_GroupNumError|]
* @retval ULONG Indicates group number is not present [Help_ACLGroup_Not_Exist|]
* @retval ULONG Indicates invalid rule type number [Help_ACL_TYPE_ID_ERROR|]
* @retval ULONG Indicates number of ACL Rule exceeds limit [Help_ACL_AccessListTooMuchRulesNormal|]
* @retval ULONG Indicates number of ACL Rules per group exceeds limit [Help_ACL_AccessInGroup|]
* @retval ULONG Indicates error in step-size value [Help_ACL_ERRSTEP|]
* @retval ULONG Indicates rule number does not exist [Help_ACL_Subitem_Number_Not_Exist|]
* @retval ULONG Indicates error in providing new rule Id [Help_ACL_CANOT_GIVEID|]            
* @retval ULONG Indicates error in number of rules in a group [Help_ACL_TooMuchRulesINGroup|] 
* @retval ULONG Indicates error in ACL rule number [Help_ACL_SubIDTooLarge|]
* @retval ULONG Indicates error in modifying rule [Help_ACL_NOTMODIFY|]
* @retval ULONG Indicates rule already exist [Help_ACL_RULES_EXIST|]
* @retval ULONG Indicates invalid action value [Help_ACL_ActionError|]
* @retval ULONG Indicates rule already exist [Help_ACL_RULES_EXIST|]
* @retval ULONG Indicates frame type error [Help_ACL_FrameTypeError|]
* 
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* If the rule index is 0XFFFFFFFF, the match order is considered as auto mode.
* 
* 
* @par Related Topics
*	- ACL_ManageBasicRule
*	- ACL_ManageAdvanceRule
*	- ACL_ManageIfBasedRule
*	- ACL_DeleteNode
*	- ACL_ManageUserRule
* 
*/ 
extern ULONG ACL_ManageExtMacRule(ULONG ulGroupNum, ULONG ulRuleIndex, ACL_EXTMAC_RULEINFO_S *pstRuleInfo);

/**
* @defgroup ACL_ManageUserRule ACL_ManageUserRule
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_ManageUserRule(ULONG ulGroupNum, 
*                          ULONG ulRuleIndex, 
*                          ULONG ulLog, 
*                          VOID *pContent);
* @endcode 
* 
* @par Description
* This function manages the user-defined rules. It can add a new rule or modify 
* the existing one.
* 
* @param[in] ulGroupNum The ACL group number. The value for this parameter should lie in between 
* the range for the group numbers provided as the second and third fields of the structure ACL_TYPE_S []
* @param[in] ulRuleIndex The rule number [0-0XFFFFFFFF]
* @param[in] ulLog Log information []
* @param[in] pContent The content rules []
* 
* @retval ULONG On success [Help_ACL_OK|]
* @retval ULONG Indicates error in input arguments/memory operation error [Help_ACL_ERR|]
* @retval ULONG Indicates error in group number [Help_ACL_GroupNumError|]
* @retval ULONG Indicates group number is not present [Help_ACLGroup_Not_Exist|]
* @retval ULONG Indicates invalid rule type number [Help_ACL_TYPE_ID_ERROR|]
* @retval ULONG Indicates number of ACL Rule exceeds limit [Help_ACL_AccessListTooMuchRulesNormal|]
* @retval ULONG Indicates number of ACL Rules per group exceeds limit [Help_ACL_AccessInGroup|]
* @retval ULONG Indicates error in step-size value [Help_ACL_ERRSTEP|]
* @retval ULONG Indicates rule number does not exist [Help_ACL_Subitem_Number_Not_Exist|]
* @retval ULONG Indicates error in providing new rule Id [Help_ACL_CANOT_GIVEID|]            
* @retval ULONG Indicates error in number of rules in a group [Help_ACL_TooMuchRulesINGroup|] 
* @retval ULONG Indicates error in ACL rule number [Help_ACL_SubIDTooLarge|]
* @retval ULONG Indicates error in modifying rule [Help_ACL_NOTMODIFY|]
* @retval ULONG Indicates rule already exist [Help_ACL_RULES_EXIST|]
* 
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* If the rule index is 0XFFFFFFFF, the match order is considered as auto mode.
* 
* 
* @par Related Topics
*	- ACL_ManageBasicRule
*	- ACL_ManageAdvanceRule
*	- ACL_ManageIfBasedRule
*	- ACL_ManageExtMacRule
*	- ACL_DeleteNode
* 
*/ 
extern ULONG ACL_ManageUserRule(ULONG ulGroupNum, ULONG ulRuleIndex, ULONG ulLog, VOID *pContent);



/**
* @defgroup ACL_NumberUpdate ACL_NumberUpdate
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_NumberUpdate(ULONG* pulGroupNum);
* @endcode 
* 
* @par Description
* This function is used to map a group number range to its equivalent extended group number range value,
* If the group number is already inside the extended range, this function returns success. 
* The group numbers are converted to its equivalent extended range as below : 
*	- "1-99" -> "2000-2099" 
*	- "100-199" -> "3100-3199" 
*	- "700-799" -> "4000-4099" \n
* If the input group number does not belong to this group number range, then the group number is not converted. 
* 
* @param[in,out] pulGroupNum Pointer to ACL group number []
* 
* @retval ULONG Success [VOS_OK|]
* @retval ULONG Pointer to ACL group number is null [VOS_ERR|]
* 
* @par Dependency
* fw_acl_cbb_api.h
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
extern ULONG ACL_NumberUpdate(ULONG* pulGroupNum);


/* Rule matching functions */
/**
* @defgroup ACL_HaveIt ACL_HaveIt
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_HaveIt(ULONG ulGroupNum, 
*                  VOID *pMatchInfo, 
*                  ULONG *pulRuleIndex, 
*                  BOOL_T *pbLog, 
*                  BOOL_T bIsCount);
* @endcode 
* 
* @par Description
* This function is used to match an ACL rule, and returns the matching rule node number. 
* It also returns whether the log entry is set or not.
* 
* @param[in] ulGroupNum ACL Group to be matched. The value for this parameter should lie in between 
* the range for the group numbers provided as the second and third fields of the structure ACL_TYPE_S. []
* @param[in] pMatchInfo IP Packet header information to be matched. IPPACKETINFO_S structure should be used. []
* @param[in] bIsCount Whether the statistics of rule matching needs to be stored in the ACL Rules or not []
* @param[out] pulRuleIndex ACL rule that matches the current packet info []
* @param[out] pbLog Whether logging is currently enabled for the matching rule. []
* 
* @retval ULONG Indicates rule matched and the matched rules action is "permit". [ACL_PERMIT|]
* @retval ULONG Indicates rule matched and the matched rules action is "deny". [ACL_DENY|]
* @retval ULONG Indicates IP Packet header information does not match with any rule inside the specified group. 
* [ACL_NOTFOUND|]
* 
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
*	- ACL_ClassifyByIpInfo
*	- ACL_ClassifyByIfInfo
*	- ACL_ClassifyByLinkInfo
*	- ACL_ClassifyByIpInfoByVrf
* 
*/ 
extern ULONG ACL_HaveIt(ULONG ulGroupNum, VOID *pMatchInfo, ULONG *pulRuleIndex, BOOL_T *pbLog, BOOL_T bIsCount);


/**
* @defgroup ACL_ClassifyByIpInfo ACL_ClassifyByIpInfo
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_ClassifyByIpInfo (VOID *pPktHdr, 
*                             ULONG ulGroupNum, 
*                             ULONG *pulRuleIndex, 
*                             BOOL_T *pbLog);
* @endcode 
* 
* @par Description
* This function is used to match packets with basic and advance ACL rules. 
* If any rule matches, the function returns the matching rule node number. It also returns whether the log is enabled or not.
* 
* @param[in] pPktHdr Pointer to input packet header []
* @param[in] pulGroupNum Group number. The value for this parameter should lie in between 
* the range for the group numbers provided as the second and third fields of the structure ACL_TYPE_S. []
* @param[out] pulRuleIndex ACL rule that matches the current packet info []
* @param[out] pbLog Whether logging is currently enabled for the matching rule. []
* 
* @retval ULONG Indicates rule matched and the matched rules action is "permit". [ACL_PERMIT|]
* @retval ULONG Indicates rule matched and the matched rules action is "deny". [ACL_DENY|]
* @retval ULONG Indicates IP Packet header information does not match with any rule inside the specified group. 
* [ACL_NOTFOUND|]
*
* 
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
*	- ACL_HaveIt
*	- ACL_ClassifyByIfInfo
*	- ACL_ClassifyByLinkInfo
*	- ACL_ClassifyByIpInfoByVrf
* 
*/ 
extern ULONG ACL_ClassifyByIpInfo (VOID *pPktHdr, ULONG ulGroupNum, ULONG *pulRuleIndex, BOOL_T *pbLog);

/**
* @defgroup ACL_ClassifyByIfInfo ACL_ClassifyByIfInfo
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_ClassifyByIfInfo(ULONG ulInIfIndex, 
*                            ULONG ulOutIfIndex, 
*                            ULONG ulIfType, 
*                            ULONG ulGroupNum, 
*                            ULONG *pulRuleIndex, 
*                            BOOL_T *pbLog);
* @endcode 
* 
* @par Description
* This function is used to match packets with interface based ACL rules. 
* If any rule matches, the function returns the matching rule node number. It also returns whether the log is enabled or not.
* 
* @param[in] ulInIfIndex Inbound interface index []
* @param[in] ulOutIfIndex Outbound interface index []
* @param[in] ulIfType The interface type. It can have the following values:
*    - IPDEBUG_IFIN  - inbound
*    - IPDEBUG_IFOUT - outbound
*    - IPDEBUG_IFANY - either one
*    - IPDEBUG_IFALL - both [IPDEBUG_IFIN-IPDEBUG_IFALL]
* @param[in] ulGroupNum Group number. The value for this parameter should lie in between 
* the range for the group numbers provided as the second and third fields of the structure ACL_TYPE_S. []
* @param[out] pulRuleIndex ACL rule that matches the current packet info []
* @param[out] pbLog Whether logging is currently enabled for the matching rule. []
* 
* @retval ULONG Indicates rule matched and the matched rules action is "permit". [ACL_PERMIT|]
* @retval ULONG Indicates rule matched and the matched rules action is "deny". [ACL_DENY|]
* @retval ULONG Indicates IP Packet header information does not match with any rule inside the specified group. 
* [ACL_NOTFOUND|]
* 
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* If ulIfType is IPDEBUG_IFIN, the function checks ACL for ulInIfIndex only. \n
* \n
* If ulIfType is IPDEBUG_IFOUT, the function checks ACL for ulOutIfIndex only. \n
* \n
* The priority of match for IPDEBUG_IFANY is ACL_PERMIT > ACL_DENY > ACL_NOTFOUND: \n
* 1. If the interfaces ulInIfIndex or ulOutIfIndex matches Permit, the return value is ACL_PERMIT. \n
* 2. If none of the results match Permit, check if any one of the two interfaces matches ACL_DENY. If any one is ACL_DENY, then return value is ACL_DENY. \n
* 3. If the interfaces ulInIfIndex and ulOutIfIndex matches to ACL_NOTFOUND, then return value is ACL_NOTFOUND. \n
* \n
* The sequence of calling for IPDEBUG_IFALL is as follows: \n
* 1. If ACL match on interfaces ulInIfIndex and ulOutIfIndex is Permit, then the return value is ACL_PERMIT. \n
* 2. If ACL match on interfaces ulInIfIndex and ulOutIfIndex is Deny, then the return value is ACL_DENY. \n
* 3. In all other cases, the return value is ACL_NOTFOUND. \n
*  
* 
* 
* @par Related Topics
*	- ACL_ClassifyByIpInfo
*	- ACL_HaveIt
*	- ACL_ClassifyByLinkInfo
*	- ACL_ClassifyByIpInfoByVrf
* 
*/ 
extern ULONG ACL_ClassifyByIfInfo(ULONG ulInIfIndex, ULONG ulOutIfIndex, ULONG ulIfType, ULONG ulGroupNum, 
                                ULONG *pulRuleIndex, BOOL_T *pbLog);

/**
* @defgroup ACL_ClassifyByLinkInfo ACL_ClassifyByLinkInfo
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_ClassifyByLinkInfo (VOID *pPktHdr, 
*                               ULONG ulGroupNum, 
*                               ULONG *pulRuleIndex, 
*                               BOOL_T *pbLog);
* @endcode 
* 
* @par Description
* This function is used to match packets with MAC based ACL rules. 
* If any rule matches, the function returns the matching rule node number. It also returns whether the log is enabled or not. 
* 
* @param[in] pPktHdr Pointer to input packet header []
* @param[in] ulGroupNum Group number. The value for this parameter should lie in between 
* the range for the group numbers provided as the second and third fields of the structure ACL_TYPE_S. []
* @param[out] pulRuleIndex ACL rule that matches the current packet info []
* @param[out] pbLog Whether logging is currently enabled for the matching rule. []
* 
* @retval ULONG Indicates rule matched and the matched rules action is "permit". [ACL_PERMIT|]
* @retval ULONG Indicates rule matched and the matched rules action is "deny". [ACL_DENY|]
* @retval ULONG Indicates IP Packet header information does not match with any rule inside the specified group. 
* [ACL_NOTFOUND|]
* 
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
*	- ACL_ClassifyByIpInfo
*	- ACL_ClassifyByIfInfo
*	- ACL_HaveIt
*	- ACL_ClassifyByIpInfoByVrf
* 
*/ 
extern ULONG ACL_ClassifyByLinkInfo (VOID *pPktHdr, ULONG ulGroupNum, ULONG *pulRuleIndex, BOOL_T *pbLog);

/* Begin:VISP1.7C03 VRF wangchengyang,2009-01-20 */
/**
* @defgroup ACL_ClassifyByIpInfoByVrf ACL_ClassifyByIpInfoByVrf
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_ClassifyByIpInfoByVrf(VOID *pPktHdr, 
*                                 ULONG ulGroupNum, 
*                                 ULONG * pulRuleIndex, 
*                                 BOOL_T* pbLog, 
*                                 ULONG ulVrfIndex);
* @endcode 
* 
* @par Description
* This function is used to match packets with basic and advance ACL rules based on VRF index. 
* If any rule matches, the function returns the matching rule node number. It also
* returns whether the log is enabled or not. 
* 
* @param[in] pPktHdr Pointer to input packet header []
* @param[in] ulGroupNum Group number. The value for this parameter should lie in between 
* the range for the group numbers provided as the second and third fields of the structure ACL_TYPE_S. []
* @param[in] ulVrfIndex VRF index []
* @param[out] pulRuleIndex ACL rule that matches the current packet info []
* @param[out] pbLog Whether logging is currently enabled for the matching rule. []
* 
* @retval ULONG Indicates rule matched and the matched rules action is "permit". [ACL_PERMIT|]
* @retval ULONG Indicates rule matched and the matched rules action is "deny". [ACL_DENY|]
* @retval ULONG Indicates IP Packet header information does not match with any rule inside the specified group. 
* [ACL_NOTFOUND|]
* 
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
*	- ACL_ClassifyByIpInfo
*	- ACL_ClassifyByIfInfo
*	- ACL_ClassifyByLinkInfo
*	- ACL_HaveIt
*
*/ 
extern ULONG ACL_ClassifyByIpInfoByVrf(VOID *pPktHdr, ULONG ulGroupNum, ULONG * pulRuleIndex, BOOL_T* pbLog, ULONG ulVrfIndex);

/* End:VISP1.7C03 VRF wangchengyang,2009-01-20 */


/* Other external interfaces */
/**
* @defgroup ACL_Init ACL_Init
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_Init(ULONG ulMID);
* @endcode 
* 
* @par Description
* This function is used to initialize ACL.
* 
* @param[in] ulMID Module number []
* @param[out]   []
* 
* @retval ULONG On success [Help_ACL_OK|]
* @retval ULONG ACL already initialized [Help_ACL_INIT_ERR|]
* @retval ULONG g_pstSemForACL_share malloc error [Help_ACL_ACC_SEMSHARE_MallocError|]
* @retval ULONG Failed to register lock [Help_ACL_ERR_CreateSm|]
* @retval ULONG Failed to add semaphore shared variable to name DB [Help_ACL_ERR_SEMAPHORE_ADDNAMEDB|]
* @retval ULONG Failed to malloc g_pstAccACL_share global variable [Help_ACL_ACC_SHARE_MallocError|]
* @retval ULONG Failed to add g_pstAccACL_share shared variable to name DB [Help_ACL_ERR_ACC_ADDNAMEDB|]
* @retval ULONG Failed to malloc g_pulAclGroupNumSum_share global variable [Help_ACL_ACLGROUPNUMSUM_SHARE_MallocError|]
* @retval ULONG Failed to add g_pulAclGroupNumSum_share shared variable to name DB [Help_ACL_ERR_ACLGROUPNUMSUM_ADDNAMEDB|]
* @retval ULONG Failed to malloc g_pbFM_share global variable [Help_ACL_FM_SHARE_MallocError|]
* @retval ULONG Failed to add g_pbFM_share shared variable to name DB [Help_ACL_ERR_FM_ADDNAMEDB|]
* @retval ULONG Failed to malloc g_pstACL_share global variable [Help_ACL_GLOBALSTRUCT_SHARE_MallocError|]
* @retval ULONG Failed to malloc basic rule type [Help_ACL_TYPE_BASIC_MallocErr|]
* @retval ULONG Failed to malloc basic acl group [Help_ACL_GROUP_BASIC_MallocErr|]
* @retval ULONG Failed to malloc advance rule type [Help_ACL_TYPE_ADV_MallocErr|]
* @retval ULONG Failed to malloc advance acl group [Help_ACL_GROUP_ADV_MallocErr|]
* @retval ULONG Failed to malloc interface based rule type [Help_ACL_TYPE_IF_MallocErr|]
* @retval ULONG Failed to malloc interface based acl group [Help_ACL_GROUP_IF_MallocErr|]
* @retval ULONG Failed to malloc mac based rule type [Help_ACL_TYPE_MAC_MallocErr|]
* @retval ULONG Failed to malloc mac based ACL group [Help_ACL_GROUP_MAC_MallocErr|]
* @retval ULONG Failed to add g_pstACL_share shared variable to name DB [Help_ACL_ERR_ACLGLOBALSTRUCT_ADDNAMEDB|]
* @retval ULONG Failed to initialize statistics component [Help_ACL_ACL_STAT_INIT|]
* @retval ULONG Failed to malloc ACLFW debug switch [ACLFW_ERR_INIT_DBG_SWITCH_MALLOC|]
* @retval ULONG Failed to add ACLFW debug switch to name DB [ACLFW_ERR_SFE_INIT_DBG_SWITCH_ADDNAMEDB|]
* @retval ULONG Failed to initialize hash table [ACLFW_ERR_HASH_INIT|]
* @retval ULONG Failed to add g_pstACLFWDB_share shared variable to name DB  [ACLFW_ERR_INIT_CFGDB_ADDNAMEDB|]
* @retval ULONG Failed to malloc statistics timer [ACLFW_ERR_ACLFW_CORE_INIT_STAT_TIMER_MALLOC|]
* @retval ULONG Failed to add statistics timer shared variable to name DB [ACLFW_ERR_ACLFW_CORE_INIT_STAT_TIMER_DBADD|]
* @retval ULONG Failed to create statistics timer [ACLFW_ERR_ACLFW_CORE_INIT_STAT_TIMER_CREATE|]
* @retval ULONG Failed to initialize statistics timer [ACLFW_ERR_INIT_STAT_TIMER|]
* @retval ULONG Failed to initialize common Init module [Help_ACL_IPSAFE_INIT_FAIL|]
*
* 
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* This function is used for backward compatibility.
* Module number will be used for module based memory management. 
* Currently, this is not implemented.
* 
* 
* @par Related Topics
* None
*/ 
extern ULONG ACL_Init(ULONG ulMID);

/**
* @defgroup ACL_InitEx ACL_InitEx
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_InitEx(ULONG ulMID);
* @endcode 
* 
* @par Description
* This function is used to initialize ACL.
* 
* @param[in] ulMID Module number []
* @param[out]   []
* 
* @retval ULONG On success [Help_ACL_OK|]
* @retval ULONG ACL already initialized [Help_ACL_INIT_ERR|]
* @retval ULONG g_pstSemForACL_share malloc error [Help_ACL_ACC_SEMSHARE_MallocError|]
* @retval ULONG Failed to register lock [Help_ACL_ERR_CreateSm|]
* @retval ULONG Failed to add semaphore shared variable to name DB [Help_ACL_ERR_SEMAPHORE_ADDNAMEDB|]
* @retval ULONG Failed to malloc g_pstAccACL_share global variable [Help_ACL_ACC_SHARE_MallocError|]
* @retval ULONG Failed to add g_pstAccACL_share shared variable to name DB [Help_ACL_ERR_ACC_ADDNAMEDB|]
* @retval ULONG Failed to malloc g_pulAclGroupNumSum_share global variable [Help_ACL_ACLGROUPNUMSUM_SHARE_MallocError|]
* @retval ULONG Failed to add g_pulAclGroupNumSum_share shared variable to name DB [Help_ACL_ERR_ACLGROUPNUMSUM_ADDNAMEDB|]
* @retval ULONG Failed to malloc g_pbFM_share global variable [Help_ACL_FM_SHARE_MallocError|]
* @retval ULONG Failed to add g_pbFM_share shared variable to name DB [Help_ACL_ERR_FM_ADDNAMEDB|]
* @retval ULONG Failed to malloc g_pstACL_share global variable [Help_ACL_GLOBALSTRUCT_SHARE_MallocError|]
* @retval ULONG Failed to malloc basic rule type [Help_ACL_TYPE_BASIC_MallocErr|]
* @retval ULONG Failed to malloc basic ACL group [Help_ACL_GROUP_BASIC_MallocErr|]
* @retval ULONG Failed to malloc advance rule type [Help_ACL_TYPE_ADV_MallocErr|]
* @retval ULONG Failed to malloc advance ACL group [Help_ACL_GROUP_ADV_MallocErr|]
* @retval ULONG Failed to malloc interface based rule type [Help_ACL_TYPE_IF_MallocErr|]
* @retval ULONG Failed to malloc interface based ACL group [Help_ACL_GROUP_IF_MallocErr|]
* @retval ULONG Failed to malloc MAC based rule type [Help_ACL_TYPE_MAC_MallocErr|]
* @retval ULONG Failed to malloc MAC based ACL group [Help_ACL_GROUP_MAC_MallocErr|]
* @retval ULONG Failed to add g_pstACL_share shared variable to name DB [Help_ACL_ERR_ACLGLOBALSTRUCT_ADDNAMEDB|]
* @retval ULONG Failed to initialize statistics component [Help_ACL_ACL_STAT_INIT|]
* @retval ULONG Failed to malloc ACLFW debug switch [ACLFW_ERR_INIT_DBG_SWITCH_MALLOC|]
* @retval ULONG Failed to add ACLFW debug switch to name DB [ACLFW_ERR_SFE_INIT_DBG_SWITCH_ADDNAMEDB|]
* @retval ULONG Failed to initialize hash table [ACLFW_ERR_HASH_INIT|]
* @retval ULONG Failed to add g_pstACLFWDB_share shared variable to name DB  [ACLFW_ERR_INIT_CFGDB_ADDNAMEDB|]
* @retval ULONG Failed to malloc statistics timer [ACLFW_ERR_ACLFW_CORE_INIT_STAT_TIMER_MALLOC|]
* @retval ULONG Failed to add statistics timer shared variable to name DB [ACLFW_ERR_ACLFW_CORE_INIT_STAT_TIMER_DBADD|]
* @retval ULONG Failed to create statistics timer [ACLFW_ERR_ACLFW_CORE_INIT_STAT_TIMER_CREATE|]
* @retval ULONG Failed to initialize statistics timer [ACLFW_ERR_INIT_STAT_TIMER|]
*
* 
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* This function should only be used by new users.
* Module number will be used for module based memory management. 
* Currently, this is not implemented.
* 
* @par Related Topics
* None
*/ 
extern ULONG ACL_InitEx(ULONG ulMID);


/**
* @defgroup ACL_GetVersion ACL_GetVersion
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_GetVersion(CHAR *szVerInfo);
* @endcode 
* 
* @par Description
* This function gets the version information.
* 
* @param[in,out] szVerInfo Pointer to store the version information string. 
* The string should be of a length of 256 bytes. []
* 
* @retval ULONG On success [Help_ACL_OK|]
* @retval ULONG Indicates error in input arguments [Help_ACL_ERR|]
* 
* @par Dependency
* None
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* ACL_ShowVersion
*
*/ 
extern ULONG ACL_GetVersion(CHAR *szVerInfo);

/**
* @defgroup ACL_ShowVersion ACL_ShowVersion
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* VOID ACL_ShowVersion(VOID);
* @endcode 
* 
* @par Description
* This function displays the ACL version information.
* 
* @param[in]   []
* @param[out]   []
* 
* @retval VOID This function does not return any value. [|]
* 
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* ACL_GetVersion
*
*/ 
extern VOID ACL_ShowVersion(VOID);


/**
* @defgroup ACL_GetTypeID ACL_GetTypeID
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_GetTypeID(CHAR szTypeID[ACL_MAX_TYPEID]);
* @endcode 
* 
* @par Description
* This function gets the Type ID of the rules.
* 
* @param[in]   []
* @param[out] szTypeID[ACL_MAX_TYPEID] Array to get the type ID []
* 
* @retval ULONG On success [Help_ACL_OK|]
* @retval ULONG Indicates error in input arguments [Help_ACL_ERR|]
* 
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* ACL_GetTypeInfo
*
*/ 
extern ULONG ACL_GetTypeID(CHAR szTypeID[ACL_MAX_TYPEID]);

/**
* @defgroup ACL_GetTypeInfo ACL_GetTypeInfo
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_GetTypeInfo(ULONG ulTypeID, ACL_TYPE_INFO_S *pstTypeInfo);
* @endcode 
* 
* @par Description
* This function gets the basic information of the Rule Type ID.
* 
* @param[in] ulTypeID ID of the rule type. [1-16]
* @param[out] pstTypeInfo Pointer to the structure that stores the information
* of the rule type ID given in ulTypeID. []
* 
* @retval ULONG On success [Help_ACL_OK|]
* @retval ULONG Indicates error in input arguments [Help_ACL_ERR|]
* @retval ULONG Indicates rule type does not exist [Help_ACL_TYPE_NOT_EXIST|]
* @retval ULONG Indicates error in ACL rule type ID [Help_ACL_TYPE_ID_ERROR|]
* 
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
*	- ACL_GetTypeID
*	- ACL_GetGroupInfo
*	- ACL_GetRuleInfo
*
*/ 
extern ULONG ACL_GetTypeInfo(ULONG ulTypeID, ACL_TYPE_INFO_S *pstTypeInfo);

/**
* @defgroup ACL_GetGroupInfo ACL_GetGroupInfo
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_GetGroupInfo(ULONG ulGroupNum, ACL_GROUP_INFO_S *pstGroupInfo);
* @endcode 
* 
* @par Description
* This function gets the information of a particular ACL group.
* 
* @param[in] ulGroupNum The ACL group number. The value for this parameter should lie in between 
* the range for the group numbers provided as the second and third fields of the structure ACL_TYPE_S. []
* @param[out] pstGroupInfo Pointer to the structure that stores the group information. []
* 
* @retval ULONG On success [Help_ACL_OK|]
* @retval ULONG Indicates NULL arguments [Help_ACL_ERR|]
* @retval ULONG Indicates error in group number [Help_ACL_GroupNumError|]
* @retval ULONG Indicates rule group does not exist [Help_ACLGroup_Not_Exist|]
* 
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
*	- ACL_GetTypeInfo
*	- ACL_GetRuleInfo
*
*/ 
extern ULONG ACL_GetGroupInfo(ULONG ulGroupNum, ACL_GROUP_INFO_S *pstGroupInfo);


/**
* @defgroup ACL_GetTypeIDByIndex ACL_GetTypeIDByIndex
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_GetTypeIDByIndex(ULONG ulGroupNum, ULONG *pulTypeID);
* @endcode 
* 
* @par Description
* This function gets the Rule Type ID based on the input group number.
* 
* @param[in] ulGroupNum The ACL group number. The value for this parameter should lie in between 
* the range for the group numbers provided as the second and third fields of the structure ACL_TYPE_S. []
* @param[out] pulTypeID Pointer to the type ID. []
* 
* @retval ULONG On success [Help_ACL_OK|]
* @retval ULONG Indicates NULL arguments [Help_ACL_ERR|]
* @retval ULONG Indicates error in group number [Help_ACL_GroupNumError|]
* 
* @par Dependency
* fw_acl_cbb_api.h
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
extern ULONG ACL_GetTypeIDByIndex(ULONG ulGroupNum, ULONG *pulTypeID);


/**
* @defgroup ACL_GetRuleInfo ACL_GetRuleInfo
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_GetRuleInfo(ULONG ulGroupNum, 
*                       ULONG ulRuleIndex, 
*                       ACL_RULE_INFO_S *pstRuleInfo);
* @endcode 
* 
* @par Description
* This function gets the rule information.
* 
* @param[in] ulGroupNum The ACL group number. The value for this parameter should lie in between 
* the range for the group numbers provided as the second and third fields of the structure ACL_TYPE_S. []
* @param[in] ulRuleIndex The index of the ACL rule for which the information 
* is required. []
* @param[out] pstRuleInfo Pointer to the structure that stores the rule 
* information. []
* 
* @retval ULONG On success [Help_ACL_OK|]
* @retval ULONG Indicates NULL arguments [Help_ACL_ERR|]
* @retval ULONG Indicates error in arguments [Help_ACL_CONTENT_NULL|]
* @retval ULONG Indicates error in group number [Help_ACL_GroupNumError|]
* @retval ULONG Indicates rule group does not exist [Help_ACLGroup_Not_Exist|]
* @retval ULONG Indicates rule number does not exist [Help_ACL_Subitem_Number_Not_Exist|]
* 
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
*	- ACL_GetTypeInfo
*	- ACL_GetGroupInfo
*
*/ 
extern ULONG ACL_GetRuleInfo(ULONG ulGroupNum, ULONG ulRuleIndex, ACL_RULE_INFO_S *pstRuleInfo);


/**
* @defgroup ACL_ClearGroup ACL_ClearGroup
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_ClearGroup(BOOL_T bIsAll, ULONG ulGroupNum);
* @endcode 
* 
* @par Description
* This function resets the match count of rules from the given ACL group or all ACL groups.
* 
* @param[in] bIsAll If this flag is set, then it resets the match count of rules from all ACL groups, 
* else it resets the match count of the rules from the ACL group ulGroupNum []
* @param[in] ulGroupNum The ACL group number from which rules should be removed. The value for this parameter should lie in between 
* the range for the group numbers, provided as the second and third fields of the structure ACL_TYPE_S []
* @param[out]   []
* 
* @retval ULONG On success [Help_ACL_OK|]
* @retval ULONG Indicates error in group number [Help_ACL_GroupNumError|]
* @retval ULONG Indicates rule group does not exist [Help_ACLGroup_Not_Exist|]
*
* @par Dependency
* fw_acl_cbb_api.h
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
extern ULONG ACL_ClearGroup(BOOL_T bIsAll, ULONG ulGroupNum);


/**
* @defgroup ACL_GetTotalACLGroups ACL_GetTotalACLGroups
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_GetTotalACLGroups(VOID);
* @endcode 
* 
* @par Description
* This function gets the total number of ACL groups (with and without rules)
* 
* @param[in]   []
* @param[out]   []
* 
* @retval ULONG The total number of ACL groups. [|]
* 
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* ACL_GetACLGroupSum
* ACL_GetACLRuleSum
*
*/ 
ULONG ACL_GetTotalACLGroups(VOID);

/**
* @defgroup ACL_GetACLGroupSum ACL_GetACLGroupSum
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_GetACLGroupSum(VOID);
* @endcode 
* 
* @par Description
* This function gets the total number of ACL groups with rules.
* 
* @param[in]   []
* @param[out]   []
* 
* @retval ULONG The total number of ACL groups. [|]
* 
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* ACL_GetACLRuleSum
*
*/ 
extern ULONG ACL_GetACLGroupSum(VOID);

/**
* @defgroup ACL_GetACLRuleSum ACL_GetACLRuleSum
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_GetACLRuleSum(VOID);
* @endcode 
* 
* @par Description
* This function gets the total number of ACL rules.
* 
* @param[in]   []
* @param[out]   []
* 
* @retval ULONG The total number of ACL rules. [|]
* 
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* ACL_GetACLGroupSum
*
*/ 
extern ULONG ACL_GetACLRuleSum(VOID);

/**
* @defgroup ACL_GroupNumIsValid ACL_GroupNumIsValid
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_GroupNumIsValid(ULONG ulGroupNum);
* @endcode 
* 
* @par Description
* This function checks whether an ACL group, indicated by the group number in 
* the parameter ulGroupNum, is valid or not.
* 
* @param[in] ulGroupNum The ACL group number. The value for this parameter should lie in between 
* the range for the group numbers provided as the second and third fields of the structure ACL_TYPE_S. []
* @param[out]   []
* 
* @retval ULONG On success.Group number is valid [Help_ACL_OK|]
* @retval ULONG On failure. Group number is invalid [Help_ACL_ERR|]
* 
* @par Dependency
* fw_acl_cbb_api.h
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
extern ULONG ACL_GroupNumIsValid(ULONG ulGroupNum);

/**
* @defgroup ACL_CheckGroupRuleExist ACL_CheckGroupRuleExist
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_CheckGroupRuleExist(ULONG ulGroupNum, ULONG ulRuleIndex);
* @endcode 
* 
* @par Description
* This function checks whether the rule, indicated by the parameter ulRuleIndex,
* exists in the ACL group, indicated by the parameter ulGroupNum, or not.
* 
* @param[in] ulGroupNum The ACL group number. The value for this parameter should lie in between 
* the range for the group numbers provided as the second and third fields of the structure ACL_TYPE_S. []
* @param[in] ulRuleIndex The ACL rule index number. []
* @param[out]   []
* 
* @retval ULONG On success [Help_ACL_OK|]
* @retval ULONG Indicates error in group number [Help_ACL_GroupNumError|]
* @retval ULONG Indicates group does not exist [Help_ACLGroup_Not_Exist|]
* @retval ULONG Indicates rule number does not exist [Help_ACL_Subitem_Number_Not_Exist|]
* 
* @par Dependency
* fw_acl_cbb_api.h
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
extern ULONG ACL_CheckGroupRuleExist(ULONG ulGroupNum, ULONG ulRuleIndex);

/**
* @defgroup ACL_GetVrfIndexByGroup ACL_GetVrfIndexByGroup
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_GetVrfIndexByGroup(ULONG ulGroupNum, ULONG *pulVrfIndex);
* @endcode 
* 
* @par Description
* This function gets the VRF index by group number.
* 
* @param[in] ulGroupNum The ACL group number. The value for this parameter should lie in between 
* the range for the group numbers provided as the second and third fields of the structure ACL_TYPE_S. []
* @param[out] pulVrfIndex Pointer to the VRF index []
*
* @retval ULONG On Success [Help_ACL_OK|]
* @retval ULONG Indicates error in input arguments [Help_ACL_ERR|]
* @retval ULONG Indicates invalid group number [Help_ACL_GroupNumError|]
* @retval ULONG Indicates group doe snot exist [Help_ACLGroup_Not_Exist|] 
* @retval ULONG Indicates no rule is present in the group [Help_ACL_NO_RULES_EXIST|]
* 
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* The function ACL_GetVrfIndexByGroup gets the VRF index of the first rule present in the group ulGroupNum.
* It is advisable to use the function ACL_GetVrfIndexByRuleIndex instead of ACL_GetVrfIndexByGroup.
* 
* 
* @par Related Topics
* None
*/ 
extern ULONG ACL_GetVrfIndexByGroup(ULONG ulGroupNum, ULONG *pulVrfIndex);


/**
* @defgroup ACL_GetVrfIndexByRuleIndex ACL_GetVrfIndexByRuleIndex
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_GetVrfIndexByRuleIndex(ULONG ulGroupNum, ULONG ulRuleIndex, ULONG *pulVrfIndex);
* @endcode 
* 
* @par Description
* This function is used to get the vrf index for a specific rule number in a group.
* 
* @param[in] ulGroupNum The ACL group number. The value for this parameter should lie in between 
* the range for the group numbers provided as the second and third fields of the structure ACL_TYPE_S. []
* @param[in] ulRuleIndex Rule Index for which the VRF must be searched. []
* @param[out] pulVrfIndex Pointer to the VRF index []
*
* @retval ULONG On Success [Help_ACL_OK|]
* @retval ULONG Indicates error in input arguments [Help_ACL_ERR|]
* @retval ULONG Indicates invalid group number [Help_ACL_GroupNumError|]
* @retval ULONG Indicates group doe snot exist [Help_ACLGroup_Not_Exist|] 
* @retval ULONG Indicates no rule is present in the group [Help_ACL_NO_RULES_EXIST|]
* 
* @par Dependency
* fw_acl_cbb_api.h
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
extern ULONG ACL_GetVrfIndexByRuleIndex(ULONG ulGroupNum, ULONG ulRuleIndex, ULONG *pulVrfIndex);

/**
* @defgroup ACL_IFDelete ACL_IFDelete
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_IFDelete(ULONG ulIfIndex);
* @endcode 
* 
* @par Description
* This function deletes the interface based ACL rule given by the interface index ulIfIndex.
* 
* @param[in] ulIfIndex The index of the interface. []
* @param[out]   []
* 
* @retval ULONG On success [Help_ACL_OK|]
* @retval ULONG Indicates error in the ACL interface type [Help_ACL_TYPE_NOT_EXIST|]
* 
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* Rules will be deleted, if the interface index matches;  
* else no action is taken and returns Help_ACL_OK
* 
* 
* @par Related Topics
* ACL_DeleteVRF
*
*/ 
extern ULONG ACL_IFDelete(ULONG ulIfIndex);

/**
* @defgroup ACL_SetAclAccelerate ACL_SetAclAccelerate
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* VOID ACL_SetAclAccelerate(BOOL_T EBOOL);
* @endcode 
* 
* @par Description
* This function enables accelerated packet classification algorithm.
* 
* @param[in] EBOOL Indicates whether to enable or disable the accelerated packet 
* classification [BOOL_TRUE/BOOL_FALSE]
* @param[out]   []
* 
* @retval  This function does not return any value. [|]
* 
* @par Dependency
* fw_acl_cbb_api.h
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
*
*/ 
extern VOID ACL_SetAclAccelerate(BOOL_T EBOOL);


/**
* @defgroup ACL_IsAclAccelerate ACL_IsAclAccelerate
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* BOOL_T ACL_IsAclAccelerate(VOID);
* @endcode 
* 
* @par Description
* This function checks whether the ACL is accelerated or not.
* 
* @param[in]   []
* @param[out]   []
* 
* @retval BOOL_T Indicates ACL is accelerated [BOOL_TRUE|]
* @retval BOOL_T Indicates ACL is not accelerated [BOOL_FALSE|]
* 
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
*	- ACL_NoAccelerate
*	- ACL_Accelerate
*
*/ 
extern BOOL_T ACL_IsAclAccelerate(VOID);

/**
* @defgroup ACL_Accelerate ACL_Accelerate
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_Accelerate(AclAccErrCode *pAccErr);
* @endcode 
* 
* @par Description
* This function creates tables for ACL acceleration.
* 
* @param[in]   []
* @param[out] pAccErr Pointer to enum containing the ACL Accelerated error codes. []
* 
* @retval ULONG On success [ACL_RFC_SUCCESS|]
* @retval ULONG The input pointer is NULL [ACL_RFC_ERRORCODESTRUCTURE_NULL_PTR|]
* @retval ULONG Unable to allocate memory for Phase [ACL_RFC_UNABLE_TO_ALLOC_MEM_FOR_PHASE|]
* @retval ULONG Failed to allocate memory [FWCOMMON_RFC_INITCHUNK_MEM_MALLOC_FAIL|]
* @retval ULONG Failed to create memory for Rule [ACL_RFC_UNABLE_TO_ALLOC_MEM_FOR_RULE|]
* @retval ULONG Failed to create memory for Phase [ACL_RFC_UNABLE_TO_ALLOC_MEM_FOR_PHASE|]
* 
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* 1) ACL groups which contain 20 or more rules will be accelerated.\n
* 2) Acceleration applies to basic and advanced groups.\n
* 3) Acceleration applies to the rules which has continuous source/destination IP mask.\n
* 
* 
* @par Related Topics
*	- ACL_IsAclAccelerate
*	- ACL_NoAccelerate
*
*/ 
extern ULONG ACL_Accelerate(AclAccErrCode *pAccErr);



/**
* @defgroup ACL_NoAccelerate ACL_NoAccelerate
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_NoAccelerate(VOID);
* @endcode 
* 
* @par Description
* This function cleans up the RFC tables.
* 
* @param[in]   []
* @param[out]   []
* 
* @retval ULONG On success [Help_ACL_OK|]
* @retval ULONG On failure [Help_ACL_ERR|]
* 
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
*	- ACL_IsAclAccelerate
*	- ACL_Accelerate
*
*/ 
extern ULONG ACL_NoAccelerate(VOID);


/**
* @defgroup ACLFW_SetEnable ACLFW_SetEnable
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACLFW_SetEnable(ULONG ulFlag);
* @endcode 
* 
* @par Description
* This function is used to enable or disable ACL packet classification. By default, 
* ACL packet classification is enabled. 
* 
* @param[in] ulFlag Flag to enable or disable the ACL packet classification [ACL_YES/ACL_NO]
* @param[out]   []
* 
* @retval ULONG  On success [ACLFW_OK|]
* @retval ULONG  ACL is not initialized [ACLFW_ERR_SFE_SETENABLE_INIT|]
* @retval ULONG  Input parameter is invalid. Value is other than ACL_YES/ACL_NO [ACLFW_ERR_PARA|]
*
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
*	- ACLFW_GetEnable
*	- ACLFW_ShowEnable
*/ 
extern  ULONG   ACLFW_SetEnable(ULONG ulFlag);

/**
* @defgroup ACLFW_GetEnable ACLFW_GetEnable
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACLFW_GetEnable(ULONG *pulFlag);
* @endcode 
* 
* @par Description
* This function is used to get the enable or disable status of ACL packet classification. 
* By default ACL packet classification is enabled. 
* 
* @param[in]   []
* @param[out] pulFlag Pointer to ULONG [ACL_YES/ACL_NO|ACL_YES]
* 
* @retval ULONG  On success [ACLFW_OK|]
* @retval ULONG  pulFlag is null pointer [ACLFW_ERR_NULL|]
* @retval ULONG  ACL is not initialized [ACLFW_ERR_SFE_GETENABLE_INIT|]
*
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
*	- ACLFW_SetEnable
*	- ACLFW_ShowEnable
*/ 
extern  ULONG   ACLFW_GetEnable(ULONG *pulFlag);

/**
* @defgroup ACLFW_ShowEnable ACLFW_ShowEnable
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* VOID ACLFW_ShowEnable(VOID);
* @endcode 
* 
* @par Description
* This function is used to display the enabled or disabled status of ACL packet classification. 
* By default, ACL packet classification is enabled. 
* 
* @param[in]   []
* @param[out]   []
* 
* @retval VOID This function does not return any value. [|]
*
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
*	- ACLFW_SetEnable
*	- ACLFW_GetEnable
*/ 
extern  VOID    ACLFW_ShowEnable(VOID);



/**
* @defgroup ACLFW_SetDebug ACLFW_SetDebug
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACLFW_SetDebug(ULONG ulFlag);
* @endcode 
* 
* @par Description
* This function is used to set the debug flag for ACL packet classification. ACL packet classification displays the packet details
* depending on the flag set by user. User can give more than one debug flag using | operator. User can reset the debug flag 
* value by 0.
* User can set the following types of Debug flags.
*	- ACLFW_DBGF_ALL    -- Display all the packets including Error packets and ACL not found packets.
*	- ACLFW_DBGF_IN     -- Display only inbound packets.
*	- ACLFW_DBGF_OUT    -- Display only outbound packets.
*	- ACLFW_DBGF_DENY   -- Display only denied packets.
*	- ACLFW_DBGF_PERMIT -- Display only permit packets.
* 
* 
* @param[in] ulFlag Flag to enable or disable the ACL packet classification []
* @param[out]   []
* 
* @retval ULONG  On success [ACLFW_OK|]
* @retval ULONG  ACL is not initialized [ACLFW_ERR_SFE_SETDEBUG_INIT|]
*
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* This function does not do any input parameter validation.
* 
* 
* @par Related Topics
*	- ACLFW_GetDebug
*	- ACLFW_ShowDebug
*/ 
extern ULONG ACLFW_SetDebug(ULONG ulFlag);

/**
* @defgroup ACLFW_GetDebug ACLFW_GetDebug
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACLFW_GetDebug(ULONG *pulFlag);
* @endcode 
* 
* @par Description
* This function is used to get the debug flag for ACL packet classification set by ACLFW_SetDebug. 
* 
* 
* @param[in]   []
* @param[out] pulFlag Pointer to the flag which contains the detail whether to enable or disable ACL
* packet classification. []
* 
* @retval ULONG  On success [ACLFW_OK|]
* @retval ULONG  ACL is not initialized [ACLFW_ERR_SFE_GETDEBUG_INIT|]
* @retval ULONG  pulFlag is null pointer [ACLFW_ERR_NULL|]
*
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
*	- ACLFW_SetDebug
*	- ACLFW_ShowDebug
*/ 
extern ULONG ACLFW_GetDebug(ULONG *pulFlag);

/**
* @defgroup ACLFW_ShowDebug ACLFW_ShowDebug
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* VOID ACLFW_ShowDebug(VOID);
* @endcode 
* 
* @par Description
* This function is used to display the debug flag status of ACL packet classification. It 
* displays the hexadecimal value of the flag. Depending on the bit set, user can identify which
* debug flag is set.
* 
* 
* @param[in]   []
* @param[out]   []
* 
* @retval VOID This function does not return any value. [|]
*
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
*	- ACLFW_SetDebug
*	- ACLFW_GetDebug
*/
extern VOID ACLFW_ShowDebug(VOID);



/**
* @defgroup ACLFW_ClearStat ACLFW_ClearStat
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* VOID ACLFW_ClearStat(VOID);
* @endcode 
* 
* @par Description
* This function is used to clear the ACL packet classification statistics. 
* 
* @param[in]   []
* @param[out]   []
* 
* @retval VOID This function does not return any value. [|]
* 
* @par Dependency
* fw_acl_cbb_api.h
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
extern VOID ACLFW_ClearStat(VOID);

/**
* @defgroup ACLFW_GetStat ACLFW_GetStat
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACLFW_GetStat(ACLFW_STAT_S *pstStat);
* @endcode 
* 
* @par Description
* This function is used to get the statistics for ACL packet classification. This function
* gets the statistic for all the VCPUs.
* 
* @param[in]   []
* @param[out] pstStat Pointer to statistic structure []
* 
* @retval ULONG On Success [ACLFW_OK|]
* @retval ULONG pstStat is null pointer [ACLFW_ERR_NULL|]
* @retval ULONG Firewall is not initialized [ACLFW_ERR_SFE_GETSTAT_INIT|]
* 
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
*	- ACLFW_ShowStat
*	- ACLFW_GetVCPUStat
*	- ACLFW_GetGroupStat
*/ 
extern ULONG ACLFW_GetStat(ACLFW_STAT_S *pstStat);

/**
* @defgroup ACLFW_ShowStat ACLFW_ShowStat
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* VOID ACLFW_ShowStat(VOID);
* @endcode 
* 
* @par Description
* This function is used to show the statistics for ACL packet classification. This function
* shows the statistics for all the VCPUs.
* 
* @param[in]   []
* @param[out]   []
* 
* @retval VOID This function does not return any value. [|]
* 
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
*	- ACLFW_GetStat
*	- ACLFW_ShowVCPUStat
*	- ACLFW_ShowGroupStat
*/ 

extern VOID ACLFW_ShowStat(VOID);

/**
* @defgroup ACLFW_GetVCPUStat ACLFW_GetVCPUStat
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACLFW_GetVCPUStat(ULONG ulVCPUNum, ACLFW_STAT_S* pstStat);
* @endcode 
* 
* @par Description
* This function is used to get the statistics for the given VCPU number. ulVCPUNum should be less than VCPU_MAX_NUM.
* 
* @param[in] ulVCPUNum VCPU Number [0-31]
* @param[out] pstStat Pointer to statistic structure []
* 
* @retval ULONG On Success [ACLFW_OK|]
* @retval ULONG ulVCPUNum is invalid.  [ACLFW_ERR_SFE_GETVCPUSTAT_VCPU|]
* @retval ULONG pstStat is null pointer [ACLFW_ERR_SFE_GETVCPUSTAT_NULLPTR|]
* @retval ULONG Firewall is not initialized [ACLFW_ERR_SFE_GETVCPUSTAT_INIT|]
* 
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
*	- ACLFW_ShowStat
*	- ACLFW_GetGroupStat
*/ 
extern ULONG ACLFW_GetVCPUStat(ULONG ulVCPUNum, ACLFW_STAT_S* pstStat);

/**
* @defgroup ACLFW_ShowVCPUStat ACLFW_ShowVCPUStat
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* VOID ACLFW_ShowVCPUStat(ULONG ulVCPUNum);
* @endcode 
* 
* @par Description
* This function is used to show the statistics for ACL packet classification for the given VCPU.
* 
* @param[in] ulVCPUNum VCPU Number [0-31]
* @param[out]   []
* 
* @retval VOID This function does not return any value. [|]
* 
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
*	- ACLFW_GetVCPUStat
*	- ACLFW_ShowStat
*	- ACLFW_ShowGroupStat
*/ 
extern VOID ACLFW_ShowVCPUStat(ULONG ulVCPUNum);

/**
* @defgroup ACLFW_GetGroupStat ACLFW_GetGroupStat
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACLFW_GetGroupStat(ULONG ulGroupNum, ACLFW_STAT_S* pstStat);
* @endcode 
* 
* @par Description
* This function is used to get the statistics for the given group number.
* 
* @param[in] ulGroupNum Group Number []
* @param[out] pstStat Pointer to statistic structure []
* 
* @retval ULONG On Success [ACLFW_OK|]
* @retval ULONG pstStat is null pointer [ACLFW_ERR_SFE_GETGROUPSTAT_NULLPTR|]
* @retval ULONG Firewall is not initialized [ACLFW_ERR_SFE_GETGROUPSTAT_INIT|]
* @retval ULONG Error during search [ACLFW_ERR_SFE_ACLFW_GETGROUP_STAT_GROUPNOTFOUND|]
* @retval ULONG No entry found in Hash table during search [FWCOMMON_HASH_TABLE_ITEM_NOT_EXIST|]
* 
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
*	- ACLFW_ShowGroupStat
*	- ACLFW_GetStat
*	- ACLFW_GetVCPUStat
*
*/ 
extern ULONG ACLFW_GetGroupStat(ULONG ulGroupNum, ACLFW_STAT_S* pstStat);

/**
* @defgroup ACLFW_ShowGroupStat ACLFW_ShowGroupStat
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* VOID ACLFW_ShowGroupStat(ULONG ulGroupNum);
* @endcode 
* 
* @par Description
* This function is used to show the statistic for ACL packet classification for given group number.
* 
* @param[in] ulGroupNum ACL Group Number []
* @param[out]   []
* 
* @retval VOID This function does not return any value [|]
* 
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
*	- ACLFW_GetGroupStat
*	- ACLFW_ShowStat
*/ 
extern VOID ACLFW_ShowGroupStat(ULONG ulGroupNum);

/**
* @defgroup ACL_CFG_CheckSubItem ACL_CFG_CheckSubItem
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_CFG_CheckSubItem(ACCESSLISTGROUP_S *pstGroup, ULONG *pulRuleIndex,
*                             BOOL_T bIsNo, BOOL_T *pbIsNew);
* @endcode 
* 
* @par Description
* This function is used to check/get ACL Rule ID. If pbIsNew is true 
* and a valid Rule ID is specified, this function checks whether the Rule ID is already 
* in use. If ACL_INVALID_SUBNO is specified as rule number, this function returns a 
* new Rule ID based on step value of that group. If bIsNo is true, and Rule ID does not 
* exist, this function returns error code Help_ACL_Subitem_Number_Not_Exist. 
* It also sets pbIsNew pointer value based on whether it is a new rule or existing rule.
* 
* @param[in] pstGroup Pointer to ACL Group []
* @param[in] bIsNo To identify whether the node should be deleted. []
* @param[out] pulRuleIndex Pointer to rule id []
* @param[out] pbIsNew To identify whether it is an new rule or existing []
* 
* @retval ULONG On success [Help_ACL_OK|]
* @retval ULONG Indicates error in input arguments / memory operation error [Help_ACL_ERR|]
* @retval ULONG Indicates number of ACL Rule exceeds limit [Help_ACL_AccessListTooMuchRulesNormal|]
* @retval ULONG Indicates rule doe snot exist for deletion [Help_ACL_Subitem_Number_Not_Exist|]
* @retval ULONG Indicates unable to provide new rule Id [Help_ACL_CANOT_GIVEID|]
* @retval ULONG Indicates number of ACL Rules per group exceeds limit [Help_ACL_AccessInGroup|]
* @retval ULONG Indicates rule number does not exist [Help_ACL_Subitem_Number_Not_Exist|]
* @retval ULONG Indicates error in step-size value [Help_ACL_ERRSTEP|]
* @retval ULONG Indicates error in number of rules in a group [Help_ACL_TooMuchRulesINGroup|] 
* @retval ULONG Indicates error in ACL rule number [Help_ACL_SubIDTooLarge|] 
* 
* @par Dependency
* fw_acl_cbb_api.h
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
extern ULONG ACL_CFG_CheckSubItem(ACCESSLISTGROUP_S *pstGroup, ULONG *pulRuleIndex, 
                                     BOOL_T bIsNo, BOOL_T *pbIsNew);

/**
* @defgroup ACL_CFG_MallocRuleNode ACL_CFG_MallocRuleNode
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_CFG_MallocRuleNode( ACCESSLISTGROUP_S *pstGroup, 
*                               VOID **ppRule, 
*                               VOID **ppNode, 
*                               BOOL_T bIsNew, 
*                               ULONG ulRuleIndex);
* @endcode 
* 
* @par Description
* This function is used to allocate memory for an ACL rule.
* 
* @param[in] pstGroup Pointer to ACL Group []
* @param[in] bIsNew TRUE - To identify new rule, FALSE - To identify existing rule []
* @param[in] ulRuleIndex ACL rule number []
* @param[out] ppNode Pointer to a pointer to ACL rule node []
* @param[out] ppRule Pointer to a pointer to ACL rule []
* 
* @retval ULONG On success [Help_ACL_OK|]
* @retval ULONG Indicates error in input arguments / memory operation error [Help_ACL_ERR|]
* 
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
*
* This API should be called before calling ACL_CFG_ManageRuleNode API.
* 
* 
* @par Related Topics
* None
*/ 
extern ULONG ACL_CFG_MallocRuleNode(ACCESSLISTGROUP_S *pstGroup, VOID **ppRule, VOID **ppNode, 
                                       BOOL_T bIsNew, ULONG ulRuleIndex);


/**
* @defgroup ACL_CFG_ManageRuleNode ACL_CFG_ManageRuleNode
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_CFG_ManageRuleNode(ACCESSLISTGROUP_S *pstGroup, ACL_RULE_NODE_S *pRule,
*                               BOOL_T bIsNew, BOOL_T bIsNo);
* @endcode 
* 
* @par Description
* This function is used to add, modify, and delete rule node.
* 
* @param[in] pstGroup Pointer to input ACL Group []
* @param[in] pRule Pointer to input ACL Rule Node []
* @param[in] bIsNew TRUE - To identify new rule, FALSE - To identify existing rule []
* @param[in] bIsNo TRUE - To identify the deleted node, FALSE - To identify the created node []
* @param[out]   []
* 
* @retval ULONG On success [Help_ACL_OK|]
* @retval ULONG Indicates error in input arguments / memory operation error [Help_ACL_ERR|]
* @retval ULONG Indicates unable to modify the rule [Help_ACL_NOTMODIFY|]
* @retval ULONG Indicates rule already exists [Help_ACL_RULES_EXIST|]
* @retval ULONG Indicates rule does not exist for deletion [Help_ACL_Subitem_Number_Not_Exist|]
* @retval ULONG Indicates error in group number [Help_ACL_GroupNumError|]
* @retval ULONG Indicates group number is not present [Help_ACLGroup_Not_Exist|]
* @retval ULONG Indicates rule number does not exist [Help_ACL_Subitem_Number_Not_Exist|]
* @retval ULONG Indicates internal arguments are null pointers [ACLFW_ERR_NULL|]
* @retval ULONG Firewall is not initialized [ACLFW_ERR_SFE_ACLFW_SECPOLICY_OPEN_INIT|] 
* @retval ULONG No configuration entry founds[ACLFW_ERR_END_TABLE|]
* @retval ULONG Failed to register the handle [ACLFW_ERR_IF_TABLE|]
* 
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
*
* This API should be called only after calling ACL_CFG_MallocRuleNode API successfully.
* The new ACL_RULE_NODE_S returned by  ACL_CFG_MallocRuleNode API should be the input to this API.
* 
* 
* @par Related Topics
* None
*/ 
extern ULONG ACL_CFG_ManageRuleNode(ACCESSLISTGROUP_S *pstGroup, ACL_RULE_NODE_S *pRule, 
                                         BOOL_T bIsNew, BOOL_T bIsNo);


/**
* @defgroup ACL_GetFlowOfFirstRule ACL_GetFlowOfFirstRule
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_GetFlowOfFirstRule(ULONG ulListNumber, ACL_Item *pstFlow, ULONG *pulDscp);
* @endcode 
* 
* @par Description 
* This function gets the flow information of the first rule of the specified ACL rule.
* 
* @param[in] ulListNumber List number []
* @param[out] pstFlow Flow Information []
* @param[out] pulDscp DSCP Value []
* 
* @retval ULONG On success [Help_ACL_OK|]
* @retval ULONG Indicates error in input arguments [Help_ACL_ERR|]
* 
* @par Dependency
* fw_acl_cbb_api.h
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
extern ULONG ACL_GetFlowOfFirstRule(ULONG ulListNumber, ACL_Item *pstFlow, ULONG *pulDscp);


/**
* @defgroup ACL_MatchACLItem ACL_MatchACLItem
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* BOOL_T ACL_MatchACLItem(ULONG ulACLNumber, ACL_Item * pstFlow);
* @endcode 
* 
* @par Description
* This function is used to check whether the specified ACL sub-item exists inside the specified group.
* 
* @param[in] ulACLNumber ACL Group number []
* @param[in] pstFlow Pointer to ACL Sub-Item []
* @param[out]   []
* 
* @retval BOOL_T Input ACL Sub-Item exists inside the specified group [BOOL_TRUE|]
* @retval BOOL_T Input ACL Sub-Item does not exist inside the specified group.
*                If the matched ACL Sub-Item have action type as DENY [BOOL_FALSE|]
* 
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* ACL_MatchACLItemWithDSCP
*
*/
extern BOOL_T ACL_MatchACLItem(ULONG ulACLNumber, ACL_Item * pstFlow);


/**
* @defgroup ACL_MatchACLItemWithDSCP ACL_MatchACLItemWithDSCP
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* BOOL_T ACL_MatchACLItemWithDSCP(ULONG ulACLNumber, ACL_Item * pstFlow, UCHAR ucDSCP);
* @endcode 
* 
* @par Description 
* This function matches the ACL item with DSCP value.
* 
* @param[in] ulACLNumber ACL rule number []
* @param[in] pstFlow ACL items provided []
* @param[in] ucDSCP DSCP Value []
* @param[out]   [] 
* 
* @retval ULONG Not matching
*               If the matched ACL Sub-Item have action type as DENY [BOOL_FALSE|]
* @retval ULONG Matching [BOOL_TRUE|]
* 
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* 
* \n
* 
* If user passes ucDSCP as 0xff, ACL should consider no DSCP in packet.
* 
* 
* @par Related Topics
* ACL_MatchACLItem
*
*/
extern BOOL_T ACL_MatchACLItemWithDSCP(ULONG ulACLNumber, ACL_Item * pstFlow, UCHAR ucDSCP);


/**
* @defgroup ACL_IsACLNodeExistByNumber ACL_IsACLNodeExistByNumber
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_IsACLNodeExistByNumber(ULONG ulNumber, ULONG ulSubitem);
* @endcode 
* 
* @par Description
* This function checks whether an ACL rule exists or not.
* 
* @param[in] ulNumber ACL Group number []
* @param[in] ulSubitem ACL Rule number []
* 
* @retval ULONG Rule exist [1|]
* @retval ULONG Rule does not exist or error [0|] 
* 
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* If 0xFFFFFFFF is passed as ACL Rule number, 
* the function checks the existence of ACL Group. If ACL Group exists, 
* the function returns 1.
* 
* 
* @par Related Topics
* None
*/
extern ULONG ACL_IsACLNodeExistByNumber(ULONG ulNumber, ULONG ulSubitem);


/* End: VISP1.7C03 VRF wangchengyang,2009-01-20 */
/**
* @defgroup ACL_GetConfig ACL_GetConfig
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* VOID ACL_GetConfig(ACLCONFIG_S* pstAclconfig);
* @endcode 
* 
* @par Description
* This function is used to get current ACL configuration information. 
*
* @param[in]   []
* @param[out] pstAclconfig pointer to acl configuration structure []
* 
* @retval VOID This function do not return anything [|]
* 
* @par Dependency
* fw_acl_cbb_api.h
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
extern VOID ACL_GetConfig(ACLCONFIG_S* pstAclconfig);

/**
* @defgroup ACL_DeleteVRF ACL_DeleteVRF
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_DeleteVRF(ULONG ulVrfIndex);
* @endcode 
* 
* @par Description
* This function deletes the rules based on VRF index.
* 
* 
* @param[in] ulVrfIndex The VRF index. []
* @param[out]   []
* 
* @retval ULONG On success [Help_ACL_OK|]
* @retval ULONG On failure [Help_ACL_ERR|]
* @retval ULONG No configuration entry founds[ACLFW_ERR_END_TABLE|]
* @retval ULONG Indicates error in ACL group number [Help_ACL_GroupNumError|]
* @retval ULONG Indicates rule group already exists [Help_ACL_Group_Exist|]
* @retval ULONG Indicates rule number does not exist [Help_ACL_Subitem_Number_Not_Exist|]
* 
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* This function is applicable for only Basic and Advanced rules.
* Rules will be deleted, if the vrf index matches; 
* else no action is taken and returns Help_ACL_OK.
* 
* 
* @par Related Topics
* ACL_IFDelete
*
*/
extern ULONG ACL_DeleteVRF(ULONG ulVrfIndex);


/**
* @defgroup ACL_GetRuleMatchMode ACL_GetRuleMatchMode
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_GetRuleMatchMode(VOID);
* @endcode 
* 
* @par Description
* This function is used to get the current rule match mode value.
* 
* @param[in]   []
* @param[out]   []
* 
* @retval ULONG Accurate rule match mode [0|]
* @retval ULONG Standard rule match mode [1|]
* 
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
*	- ACL_SetRuleMatchMode
*	- ACL_ShowRuleMatchMode
*
*/
extern ULONG ACL_GetRuleMatchMode(VOID);


/**
* @defgroup ACL_SetRuleMatchMode ACL_SetRuleMatchMode
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_SetRuleMatchMode(BOOL_T bRuleMatchMode);
* @endcode 
* 
* @par Description
* This function is used to set the rule match mode.
* 
* @param[in] bRuleMatchMode Rule Match mode value. It can have the following values:
*	- 1 - accurate
*	- 0 - standard  []
* @param[out]   []
* 
* @retval ULONG On success [Help_ACL_OK|]
* @retval ULONG Indicates invalid input specified [Help_ACL_ERR|]
* 
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
*	- ACL_ShowRuleMatchMode
*	- ACL_GetRuleMatchMode
*
*/
extern ULONG ACL_SetRuleMatchMode(BOOL_T bRuleMatchMode);


/**
* @defgroup ACL_ShowRuleMatchMode ACL_ShowRuleMatchMode
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* VOID ACL_ShowRuleMatchMode(VOID);
* @endcode 
* 
* @par Description
* This function is used to display the current ACL rule match mode.
* 
* @param[in]   []
* @param[out]   []
* 
* @retval ULONG On success [ACLFW_OK|]
* 
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
*	- ACL_GetRuleMatchMode
*	- ACL_SetRuleMatchMode
*/
extern VOID ACL_ShowRuleMatchMode(VOID);

/**
* @defgroup ACL_ClassifyMBufByItem ACL_ClassifyMBufByItem
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* BOOL_T ACL_ClassifyMBufByItem(VOID* pstMBuf,ACL_Item *pstFlow);
* @endcode 
* 
* @par Description 
* This function is used to determine whether a packet matches with the specified ACL sub-item.  
*
* @param[in] pstMBuf packet structure []
* @param[in] pstFlow ACL Sub-Item []
* @param[out]   []
* 
* @retval BOOL_T Packet matches with the ACL Sub-Item [BOOL_TRUE|]
* @retval BOOL_T Packet does not match with the ACL Sub-Item [BOOL_FALSE|]
* 
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
*	- ACL_ClassifyInMBufByItem
*	- ACL_ClassifyInMBufByItemWithDSCP
*
*/ 
extern BOOL_T ACL_ClassifyMBufByItem(VOID* pstMBuf,ACL_Item *pstFlow);

/**
* @defgroup ACL_GetMatchedACLItem ACL_GetMatchedACLItem
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_GetMatchedACLItem(VOID *pstMBuf,ULONG ulGroupNum, ACL_Item* pstFlow);
* @endcode 
* 
* @par Description
* This function is used to match input packet with ACL rule inside a specific group, and returns the 
* matching rule information, if match result is permit.
* 
* @param[in] pstMBuf Packet structure []
* @param[in] ulGroupNum Group number []
* @param[out] pstFlow ACL sub-item []
* 
* @retval ULONG Packet is permitted to pass [VOS_OK|]
* @retval ULONG Packet is not permitted to pass [VOS_ERR|]
* 
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* ACL_GetMatchedACLItemWithDSCP
*
*/ 
extern ULONG ACL_GetMatchedACLItem(VOID *pstMBuf,ULONG ulGroupNum, ACL_Item* pstFlow);

/**
* @defgroup ACL_GetMatchedACLItemWithDSCP ACL_GetMatchedACLItemWithDSCP
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_GetMatchedACLItemWithDSCP(VOID *pstMBuf, 
*                                     ULONG ulGroupNum, 
*                                     ACL_Item* pstFlow, 
*                                     UCHAR *pucDSCP);
* @endcode 
* 
* @par Description
* This function is used to match packet with ACL rule inside a specific group, and returns the matching 
* rule information and DSCP value, if match result is permit.
*
* @param[in] pstMBuf Packet structure []
* @param[in] ulGroupNum ACL group number []
* @param[out] pstFlow Pointer to ACL sub-item []
* @param[out] pucDSCP Pointer to DSCP value []
* 
* @retval ULONG Success [VOS_OK|]
* @retval ULONG Failure [VOS_ERR|]
* 
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* ACL_GetMatchedACLItem
* 
*/ 
extern ULONG ACL_GetMatchedACLItemWithDSCP(VOID *pstMBuf, ULONG ulGroupNum, ACL_Item* pstFlow, UCHAR *pucDSCP);

/**
* @defgroup ACL_ClassifyInMBufByItem ACL_ClassifyInMBufByItem
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* BOOL_T  ACL_ClassifyInMBufByItem(VOID *pMBuf, ACL_Item *pItem);
* @endcode 
* 
* @par Description 
* This function is used to verify whether input packet matches with the specified ACL sub-item, with 
* source/destination address and source/destination port number reversed.
*
* @param[in] pstMBuf Packet structure []
* @param[in] pstFlow ACL sub-item []
* @param[out]   []
* 
* @retval BOOL_T Packet matches with the ACL Sub-Item [BOOL_TRUE|]
* @retval BOOL_T Packet does not match with the ACL Sub-Item [BOOL_FALSE|]
* 
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
*	- ACL_ClassifyMBufByItem
*	- ACL_ClassifyInMBufByItemWithDSCP
*
*/ 
extern BOOL_T  ACL_ClassifyInMBufByItem(VOID *pMBuf, ACL_Item *pItem);

/**
* @defgroup ACL_ClassifyInMBufByItemWithDSCP ACL_ClassifyInMBufByItemWithDSCP
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* BOOL_T ACL_ClassifyInMBufByItemWithDSCP(VOID *pMBuf, ACL_Item *pItem, UCHAR ucDSCP);
* @endcode 
* 
* @par Description
* This function is used to determine whether a packet matches with the specified ACL sub-item and 
* DSCP value with source/destination address and source/destination port number reversed. 
* 
* @param[in] pMBuf Pointer to packet structure []
* @param[in] pItem Pointer to ACL sub-item []
* @param[in] ucDSCP DSCP value []
* @param[out]   []
* 
* @retval BOOL_T Packet matches with input ACL sub-item and DSCP [BOOL_TRUE|]
* @retval BOOL_T Packet does not match with input ACL sub-item and DSCP [BOOL_FALSE|]
* 
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* If User passes ucDSCP as 0xff, ACL considers no DSCP in packet and DSCP value is not matched. 
* 
* 
* @par Related Topics
*	- ACL_ClassifyMBufByItem
*	- ACL_ClassifyInMBufByItem
* 
*/ 
extern BOOL_T ACL_ClassifyInMBufByItemWithDSCP(VOID *pMBuf, ACL_Item *pItem, UCHAR ucDSCP);

/*Begin 2008-09-10 V1R7C02 同步V1R7C01*/
/**
* @defgroup ACL_ClassifyInMBufByNumber ACL_ClassifyInMBufByNumber
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_ClassifyInMBufByNumber(VOID *pMBuf, ULONG ulGroupNum, ULONG ulIgnore);
* @endcode 
* 
* @par Description
* This function is used to determine whether a packet (pMBuf) matches with a rule inside the 
* specified group, with source/destination address and source/destination port number reversed.
* 
* @param[in] pMBuf Packet structure []
* @param[in] ulGroupNum ACL group number []
* @param[in] ulIgnore Specifies the fields that should be ignored during packet matching.
*                     The list below mentions the fields and their corresponding ulIgnore values :
*                      SOURCE_IP        0x0001     
*                      DESTINATION_IP   0x0002
*                      PROTOCOL_FIELD   0x0004
*                      TOS_VALUE        0x0008
*                      PRECEDANCE_VALUE 0x0010
*                      SOURCE_PORT      0x0020
*                      DESTINATION_PORT 0x0040
*                      DSCP_VALUE       0x0400
*                      VRF_VALUE        0x0080
*
* @param[out]   []
* 
* @retval ULONG Rule matched and the matched rules action is "permit" [ACL_PERMIT|]
* @retval UL0NG Rule matched and the matched rules action is "deny" [ACL_DENY|]
* @retval ULONG IP Packet header information does not match with any rule inside the specified group. [ACL_NOTFOUND|]
* 
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* ACL_SH_ClassifyByIpInfo
*
*/ 
extern ULONG ACL_ClassifyInMBufByNumber(VOID *pMBuf, ULONG ulGroupNum, ULONG ulIgnore);

/**
* @defgroup ACL_SH_ClassifyByIpInfo ACL_SH_ClassifyByIpInfo
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_SH_ClassifyByIpInfo(VOID *pMBuf, 
*                               ULONG ulNumber, 
*                               ULONG *pulRuleIndex, 
*                               BOOL_T *pbLog);
* @endcode 
* 
* @par Description
* This function is used to match packet with ACL rule inside a specified group, and returns the matching 
* rule number and log flag.
*
* @param[in] pMBuf  []
* @param[in] ulNumber Group number  []
* @param[out] pulRuleIndex Pointer to matched rule number []
* @param[out] pbLog Pointer to log flag []
* 
* @retval ULONG Rule matched and the matched rules action is "permit" [ACL_PERMIT|]
* @retval UL0NG Rule matched and the matched rules action is "deny" [ACL_DENY|]
* @retval ULONG IP Packet header information does not match with any rule inside the specified group. [ACL_NOTFOUND|]
* 
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* ACL_ClassifyInMBufByNumber
*
*/ 
extern ULONG ACL_SH_ClassifyByIpInfo(VOID *pMBuf,ULONG ulNumber, ULONG *pulRuleIndex, BOOL_T *pbLog);

/**
* @defgroup ACL_SH_ClassifyByLinkInfo ACL_SH_ClassifyByLinkInfo
* @ingroup accssf ACL Functions
* @par Prototype
* @code
* ULONG ACL_SH_ClassifyByLinkInfo(VOID *pstMbuf, 
*                                 ULONG ulGroupNum, 
*                                 ULONG *pulRuleIndex, 
*                                 BOOL_T *pbLog);
* @endcode 
* 
* @par Description
* This function is used for MAC based rule matching.
* 
* @param[in] pstMbuf Packet structure []
* @param[in] ulGroupNum Group number  []
* @param[out] pulRuleIndex Matched rule index []
* @param[out] pbLog Log flag []
*
* @retval ULONG Permit packet [ACL_PERMIT|]
* @retval ULONG Deny packet [ACL_DENY|]
* @retval ULONG Rule Not matched [ACL_NOTFOUND|]
* 
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* None
* 
* 
* @par Related Topics
* ACL_SH_ClassifyByIpInfo
*
*/ 
extern ULONG   ACL_SH_ClassifyByLinkInfo(VOID *pstMbuf, ULONG ulGroupNum, ULONG *pulRuleIndex, BOOL_T *pbLog);






/**
* @defgroup ACL_SetAdvGroupRange ACL_SetAdvGroupRange
* @ingroup access ACL Functions
* @par Prototype
* @code
* ULONG ACL_SetAdvGroupRange (ULONG ulLowNo, ULONG ulUpNo);
*
* @endcode 
* 
* @par Description
* This function is used only to expand the default Advance Group Range up to 20K. 
* This function is implemented based on special requirement from specific customer 
* in order to support 20K Advance ACL groups and 20K rules in the system. 
* The range of advanced ACL after incoking this function is 3000~22999.
* 
* @param[in] ulLowNo Lower Range []
* @param[in] ulUpNo Upper Range  []
* @param[out] 
*
* @retval  ULONG Range Modified                [Help_ACL_OK]
* @retval  ULONG Range Not Modified            [Help_ACL_ERR]
* @retval  ULONG ACL Rule type does not exists [Help_ACL_TYPE_NOT_EXIST] 
* @retval  ULONG ACL Group ID error            [Help_ACL_TYPE_ID_ERROR] 
* @retval  ULONG ACL Range not changed         [Help_ACL_GROUP_RANGE_CANOT_CHANGE]
* @retval  ULONG Invalid Group Range           [Help_ACL_GROUP_RANGE_ERROR] 
* @retval  ULONG Malloc failed                 [Help_ACL_Group_MallocError] 
* 
* @par Dependency
* fw_acl_cbb_api.h
* 
* 
* @par Note
* \n
* 
* @par Caution
* This function is specially implemented for specific customer requirement. 
* For other products, this function must be disabled. Before calling this API 
* there should be no User Based ACL registered else there is possibility of range 
* overlapping and this API will fail. This API must be invoked immediately after 
* the ACL initialization.

* Better to avoid invoking this function, if already pre-configured ext-mac and 
* user defined ACLs are present in the system. This function may impact the 
* existing configuration. 
* 
* 
* @par Related Topics
*
*
*/ 
ULONG ACL_SetAdvGroupRange (ULONG ulLowNo, ULONG ulUpNo);


#ifdef  __cplusplus
}
#endif
   
#endif


