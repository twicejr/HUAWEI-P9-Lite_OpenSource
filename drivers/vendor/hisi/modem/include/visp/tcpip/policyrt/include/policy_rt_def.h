/*******************************************************************************
*
*
*                Copyright 2013, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              policy_rt_def.h
*
*  Project Code: VISPV300R002
*   Module Name: POLICY RT 
*  Date Created: 2013-08-12
*        Author: Chandra
*   Description: Policy route related APIs declarations and data structures are 
*                defined in th file.
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  -----------------------------------------------------------------------------
*  2013-08-12   Chandra    Create
*
*******************************************************************************/
#ifndef _POLICY_RT_DEF_H_
#define _POLICY_RT_DEF_H_

#ifdef __cplusplus
extern "C" {
#endif


/* enums for 'ulEventType' */
typedef enum tagPOLICY_RT_ERR
{
    POLCYRT_ERR_MEM_ALLOC_ININIT =  (MID_COMP_POLICYRT + 1),
    POLCYRT_SHELL_ERR_IF_CFG,
    POLICYRT_ERR_NULL_INPUT,
    POLICYRT_ERR_NOT_INIT,		
    POLICYRT_ERR_INVALID_VRF_INDX,
    POLICYRT_ERR_INVALID_POLICY_INDX,
    POLICYRT_ERR_INVALID_POLICY_GROUP_OPER,
    POLICYRT_ERR_INVALID_GROUP_ACTION,
    POLICYRT_ERR_MAX_POLICIES_CONFGURED,
    POLCYRT_ERR_GROUP_MEM_ALLOC,
    POLICYRT_ERR_GRP_NOT_EXIST,
    POLICYRT_ERR_INVALID_POLICY_NODE_OPER,
    POLICYRT_ERR_INVALID_NODE_ID,
    POLICYRT_ERR_NODE_EXIST,
    POLICYRT_ERR_MAX_POLICY_NODES_CONFGURED,
    POLICYRT_ERR_NODE_NOT_EXIST,
    POLICYRT_ERR_INVALID_MATCH_TYPE,
    POLICYRT_ERR_INVALID_MATCH_OPER,
    POLICYRT_ERR_DEL_MATCH_NOT_EXIST,
    POLICYRT_ERR_INVALID_APPLY_TYPE,
    POLICYRT_ERR_INVALID_APPLY_OPER,
    POLICYRT_ERR_INVALID_APPLY_INTF_TYPE,
    POLICYRT_ERR_DEL_APPLY_ITEM_NOT_EXIST,
    POLICYRT_ERR_INTF_NOT_EXIST,
    POLICYRT_ERR_OPEN_WAIT_LIST_FAIL,
    POLICYRT_ERR_GET_WAIT_LIST_FAIL,
    POLICYRT_ERR_WAIT_LIST_END,
    POLICYRT_ERR_WAIT_LIST_CLOSE_FAIL,
    POLCYRT_SHELL_ERR_VRF_CFG,
    POLCYRT_SHELL_ERR_AM4_CFG,
    POLICYRT_ERR_INVALID_ADMIN_STATUS,

    POLICY_RT_ERR_MAX
}POLICY_RT_ERR_E;


#define POLICY_RT_PERMIT 1

/* Maximum valid node ID */
#define POLICY_RT_MIN_NODE_ID 1
#define POLICY_RT_MAX_NODE_ID  32640

/* Definitions for node status */
#define POLICY_RT_NODE_ACTIVE 1
#define POLICY_RT_NODE_NON_ACTIVE 0

/* Definition for node AdminStatus */
#define POLICY_RT_NODE_ENABLE 1
#define POLICY_RT_NODE_DISABLE 0

/* Define for match type */
#define POLICY_RT_MATCH_ACL  0

/* Apply item valid types */
#define POLICY_RT_APPL_IFINDEX  0
#define POLICY_RT_APPL_NEXTHOP  1

/* This version supports only policy group 0,1 & 2. In future any change in number of groups, 
    need to change below macros accrodingly */
#define POLICYRT_MIN_POLICY_INDEX 0
#define POLICYRT_MAX_POLICY_INDEX 2

#define POLICYRT_OPER_DEL 0
#define POLICYRT_OPER_ADD 1

#ifdef __cplusplus
}
#endif   /* end of __cplusplus */

#endif   /* end of _POLICY_RT_DEF_H_ */



