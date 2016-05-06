
#ifndef _POLICY_RT_API_H_
#define _POLICY_RT_API_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagPOLICYRT_CFGPOLICY
{
    ULONG ulPolicyID;      /* Policy group number */
    ULONG ulVrfIndex;      /* VRF Index */
    UCHAR ucActionType;    /* Policy type, currently only supports Permit */
    UCHAR ucOper;          /* Operation Mode
                             0--Delete
                             1--Create */
    UCHAR ucRes[2];
}POLICYRT_CFG_POLICY_S;


typedef struct tagPOLICYRT_CFGNODE
{
    ULONG ulPolicyID;      /* Policy group number */
    ULONG ulVrfIndex;      /* VRF Index */
    ULONG ulNodeID;        /* Node ID, the effective range */
    UCHAR ucOper;          /* Operation Mode
                             0--Delete
                             1--Create */
    UCHAR ucRes[3];
}POLICYRT_CFG_NODE_S;

typedef struct tagPOLICYRT_CFGMATCH
{
    ULONG ulPolicyID;      /* Policy group number */
    ULONG ulVrfIndex;      /* VRF Index */
    ULONG ulNodeID;        /* Node Id, effective range */
    UCHAR ucMatchType;     /* Match type, currently only supports ACL rule group
                             0--Specifies the ACL rule group */
    UCHAR ucOper;          /* Operation Mode
                              0--Delete
                              1--Create OR Update */
    UCHAR ucRes[2];
    ULONG ulAclGroup;  /* Effective ACL rule group number, by the product warranty */
}POLICYRT_CFG_MATCH_S;

typedef struct tagPOLICYRT_CFGAPPLY
{
    ULONG ulPolicyID;      /* Policy group number */
    ULONG ulVrfIndex;      /* VRF Index */
    ULONG ulNodeID;        /* Node Id, effective range */
    UCHAR ucApplyType;     /* Apply Type
                              0--Specify the interface type
                              1--Specify the Nexthop Type ，当前版本无效 (Current version Invalid) */
    UCHAR ucOper;          /* Operation Mode
                              0--Delete
                              1--Create OR Update */
    UCHAR ucRes[2];
    ULONG ulIfIndex;       /* The interface index, 'ucApplyType' to 0 Effective
                              Supports only Eth, Trunk, PPP, MP, VI Interface Type */
    ULONG ulUserData;      /* Custom data, validity guaranteed by the user. */
    ULONG ulNextHop;       /* Next-hop Addr，The host sequencer，当前版本无效 (Current version Invalid) */
}POLICYRT_CFG_APPLY_S;

typedef struct tagPOLICYRT_FIN_CFG
{
    ULONG ulPolicyID;      /* Policy group number [0 ~ 2] */
    ULONG ulVrfIndex;      /* VRF Index  [1 ~ 1024] */
    ULONG ulNodeID;        /* Node Id, effective range [1 ~ 32640] */
}POLICYRT_FIN_CFG_S;

typedef struct tagPOLICYRT_ADMINODE
{
    ULONG ulPolicyID;      /* Policy group number [0 ~ 2] */
    ULONG ulVrfIndex;      /*VRF Index  [1 ~ 1024]*/
    ULONG ulNodeID;        /* Node Id, effective range [1 ~ 32640] */
    UCHAR ucAdmin;         /*操作字
                             0--To enable /Disable
                             1--Enable*/
    UCHAR ucRes[3];
}POLICYRT_ADMIN_NODE_S;

typedef struct tagPOLICYRT_FILTER
{
    ULONG ulPolicyID;      /* Policy group number */
    ULONG ulVrfIndex;      /* VRF Index */
}POLICYRT_FILTER_S;

typedef struct tagPOLICYRT_GETENTRY
{
    ULONG ulPolicyID;      /* Policy group number */
    ULONG ulVrfIndex;      /* VRF Index */
    ULONG ulNodeID;        /* Node Id，Effective Range [1 ~ 32640] */
    ULONG ulAclGroup;      /* ACL rule group number
                             0--This item is not configured Match */
    ULONG ulIfApply;       /* Apply the interface type items
                              0--This item is not configured Apply */
    ULONG ulUserData;      /* Custom Data */
    ULONG ulNextHopApply;  /* Apply the next hop type of item
                              0--Configure the Apply entry indicates NO */
    ULONG ulNextHopApplyIf;/* Apply for the next hop entry padded outgoing interface  results */
    ULONG ulMatchCountLow32; /* Output: Node hits*/
    ULONG ulMatchCountHigh32;

    UCHAR ucAdmin;         /* Operation Word, non-enabled state is enabled.*/

    UCHAR ucActive;        /* Marked effect
                              0--Not effective, is not issued to the NP
                              1--Effective has been issued to the NP */
    UCHAR ucRes[2];
}POLICYRT_GET_ENTRY_S;


ULONG TCPIP_PolicyRtCfgPolicy(POLICYRT_CFG_POLICY_S *pstPolicy);


ULONG TCPIP_PolicyRtCfgNode(POLICYRT_CFG_NODE_S *pstNode);


ULONG TCPIP_PolicyRtCfgMatch(POLICYRT_CFG_MATCH_S *pstMatch);


ULONG TCPIP_PolicyRtCfgApply(POLICYRT_CFG_APPLY_S * pstApply);


ULONG TCPIP_PolicyRtFinishConfig(POLICYRT_FIN_CFG_S *pstLoad);


ULONG TCPIP_PolicyRtAdminNode(POLICYRT_ADMIN_NODE_S *pstNode);



ULONG TCPIP_PolicyRtOpenTable(ULONG *pulHandle,POLICYRT_FILTER_S *pstFilter);


ULONG TCPIP_PolicyRtGetTable(ULONG ulHandle,POLICYRT_GET_ENTRY_S *pstEntry);


ULONG TCPIP_PolicyRtCloseTable(ULONG ulHandle);


ULONG TCPIP_PolicyRtShowTable(ULONG ulPolicy,ULONG ulVrfIndex);

/*******************************************************************************
*    Func Name: TCPIP_GetOutIfindexBySourceIP
* Date Created: 2014-05-27
*       Author: c00902193
*  Description: This API will search the policy entry database based on source address and VRF
*                    Index. When matches the any entry, return the corresponding the out-if index 
*                    to the user.
*        Input: UONG ulVrfIndex：VRF Index of the given source address
*                  ULONG ulSrcIP: Source address
*       Output: ULONG *pulOutIfIndex: out-if index matched with source IP.
*       Return: VOS_OK / VOS_ERR
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-05-27   c00902193               Create
*
*******************************************************************************/
ULONG TCPIP_GetOutIfindexBySourceIP(ULONG ulVrfIndex, ULONG ulSrcIP, ULONG *pulOutIfIndex);
#ifdef __cplusplus
}
#endif   /* end of __cplusplus */

#endif   /* end of _POLICY_RT_API_H_ */




